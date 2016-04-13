#include <windows.h>
#include <strsafe.h>
#include <stdio.h>
#include <mmdeviceapi.h>

#include "AudioMasterMind.h"
#include "boost\log\trivial.hpp"
#include <memory>
#include <functional>
#include "Endpointvolume.h"
#include <exception>


namespace remote {
	AudioMasterMind::AudioMasterMind()
	{
	}


	AudioMasterMind::~AudioMasterMind()
	{
	}

	void AudioMasterMind::printDevices() 
	{
		CoInitialize(NULL);

		IMMDeviceEnumerator* deviceEnumeratorPtr = NULL;
		HRESULT hr = CoCreateInstance(
			__uuidof(MMDeviceEnumerator), NULL, CLSCTX_ALL,
			__uuidof(IMMDeviceEnumerator),
			(void**)&deviceEnumeratorPtr
		);

		if (FAILED(hr)) 
		{
			BOOST_LOG_TRIVIAL(error) << "Failed to create IMMDeviceEnumerator hr:" << hr;
			return;
		}

		IMMDeviceCollection* deviceCollectionPtr = NULL;
		hr = deviceEnumeratorPtr->EnumAudioEndpoints(eAll, DEVICE_STATEMASK_ALL, &deviceCollectionPtr);

		if (FAILED(hr)) 
		{
			BOOST_LOG_TRIVIAL(error) << "Failed to enumerate audio endpoints ";
			return;
		}

		UINT deviceCount = 0;
		hr = deviceCollectionPtr->GetCount(&deviceCount);

		if (FAILED(hr)) 
		{
			BOOST_LOG_TRIVIAL(error) << "Failed to get the count of devices";
			return;
		}

		BOOST_LOG_TRIVIAL(info) << "Device Count is: " << deviceCount;


		for (unsigned int i = 0; i < deviceCount; ++i) 
		{
			IMMDevice* devicePtr = NULL;
			hr = deviceCollectionPtr->Item(i, &devicePtr);
			if (FAILED(hr))
			{
				BOOST_LOG_TRIVIAL(error) << "Failed to get item no. " << i;
				return;
			}

			printDevice(devicePtr);

		}


	}

	void AudioMasterMind::start()
	{
		auto activeDevices = getActiveDevices();
		
		auto hr = activeDevices[0]->Activate(__uuidof(IAudioEndpointVolume), CLSCTX_ALL, NULL, (void**)&audioDevice);
		if (FAILED(hr))
		{
			BOOST_LOG_TRIVIAL(error) << "Faild to activate the device: " << hr;
			throw std::logic_error("Failed to activate the device");
		}
	}

	void AudioMasterMind::terminate()
	{
		audioDevice->Release();
	}

	float AudioMasterMind::getMasterVolumeScalar()
	{
		float masterVolumeScalar = 0;
		auto hr = audioDevice->GetMasterVolumeLevelScalar(&masterVolumeScalar);
		if (FAILED(hr))
		{
			BOOST_LOG_TRIVIAL(error) << "Faild to get the master volume level as sclalar: " << hr;
			throw std::logic_error("Faild to get the master volume level as sclalar");
		}
		return masterVolumeScalar;
	}

	void AudioMasterMind::setMasterVolumeScalar(float scalar)
	{
		auto hr = audioDevice->SetMasterVolumeLevelScalar(scalar, NULL);
		if(FAILED(hr))
		{
			BOOST_LOG_TRIVIAL(error) << "Failed to set master volume level as scalar";
			throw std::logic_error{" Failed to set master volume level as scalar "};
		}
	}

	void AudioMasterMind::toggleMute()
	{	
		BOOST_LOG_TRIVIAL(info) << "Toggle Mute";
		BOOL muted;
		auto hr = audioDevice->GetMute(&muted);
		if (FAILED(hr))
		{
			BOOST_LOG_TRIVIAL(error) << "Failed to get the mute state";
			throw std::logic_error{ "Failed to get the mute state" };
		}
		hr = audioDevice->SetMute(!muted,NULL);
		if (FAILED(hr))
		{
			BOOST_LOG_TRIVIAL(error) << "Failed to toggle the mute state";
			throw std::logic_error{ "Failed to toggle the mute state" };
		}

	}

	void AudioMasterMind::volumeUp()
	{
		BOOST_LOG_TRIVIAL(info) << "Volume up";
		auto hr = audioDevice->VolumeStepUp(NULL);
		if (FAILED(hr))
		{
			BOOST_LOG_TRIVIAL(error) << "Failed to set a volume step up";
			throw std::logic_error{ " Failed to set a volume step down " };
		}
	}

	void AudioMasterMind::volumeDown()
	{
		BOOST_LOG_TRIVIAL(info) << "Volume down";
		auto hr = audioDevice->VolumeStepUp(NULL);
		if (FAILED(hr))
		{
			BOOST_LOG_TRIVIAL(error) << "Failed to set a volume step down";
			throw std::logic_error{ "Failed to set a volume step down" };
		}
	}

	
	void AudioMasterMind::printDevice(IMMDevice* devicePtr)
	{
		LPWSTR deviceIdStr = NULL;
		
		auto hr = devicePtr->GetId(&deviceIdStr);
		if (FAILED(hr))
		{
			BOOST_LOG_TRIVIAL(error) << "Failed to get devices ID hr:" << hr;
			return;
		}

		BOOST_LOG_TRIVIAL(info) << "Device ID: " << deviceIdStr;


		DWORD deviceState;
		hr = devicePtr->GetState(&deviceState);

		if (FAILED(hr)) 
		{
			BOOST_LOG_TRIVIAL(error) << "Failed to get devices state: " << hr;
			return;
		}

		switch(deviceState)
		{
			case DEVICE_STATE_ACTIVE:
				BOOST_LOG_TRIVIAL(info) << "Device State: ACTIVE";
				break;
			case DEVICE_STATE_DISABLED:
				BOOST_LOG_TRIVIAL(info) << "Device State: DISABLED";
				break;
			case DEVICE_STATE_NOTPRESENT:
				BOOST_LOG_TRIVIAL(info) << "Device State: NOT PRESENT";
				break;
			case DEVICE_STATE_UNPLUGGED :
				BOOST_LOG_TRIVIAL(info) << "Device State: UNPLUGGED";
				break;
		}

		

		IPropertyStore* devicePropertyStorePtr = NULL;
		hr = devicePtr->OpenPropertyStore(STGM_READ, &devicePropertyStorePtr);

		if (FAILED(hr))
		{
			BOOST_LOG_TRIVIAL(error) << "Failed to open device property store: " << hr;
			return;
		}

		

	}

	std::vector<IMMDevice*> AudioMasterMind::getActiveDevices()
	{
		CoInitialize(NULL);

		IMMDeviceEnumerator* deviceEnumeratorPtr = NULL;
		HRESULT hr = CoCreateInstance(
			__uuidof(MMDeviceEnumerator), NULL, CLSCTX_ALL,
			__uuidof(IMMDeviceEnumerator),
			(void**)&deviceEnumeratorPtr
		);

		if (FAILED(hr))
		{
			BOOST_LOG_TRIVIAL(error) << "Failed to create IMMDeviceEnumerator hr:" << hr;
			throw std::logic_error{ "Failed to create IMMDeviceEnumerator" };
		}

		IMMDeviceCollection* deviceCollectionPtr = NULL;
		hr = deviceEnumeratorPtr->EnumAudioEndpoints(eAll, DEVICE_STATEMASK_ALL, &deviceCollectionPtr);

		if (FAILED(hr))
		{
			BOOST_LOG_TRIVIAL(error) << "Failed to enumerate audio endpoints ";
			throw std::logic_error{ "Failed to enumerate audio endpoints" };
			
		}

		UINT deviceCount = 0;
		hr = deviceCollectionPtr->GetCount(&deviceCount);

		if (FAILED(hr))
		{
			BOOST_LOG_TRIVIAL(error) << "Failed to get the count of devices";
			throw std::logic_error{ "Failed to get Device count" };
			
		}

		BOOST_LOG_TRIVIAL(info) << "Device Count is: " << deviceCount;

		std::vector<IMMDevice*> activeDevices;

		for (unsigned int i = 0; i < deviceCount; ++i)
		{
			IMMDevice* devicePtr = NULL;
			hr = deviceCollectionPtr->Item(i, &devicePtr);
			if (FAILED(hr))
			{
				BOOST_LOG_TRIVIAL(error) << "Failed to get device no. " << i;
				throw std::logic_error{ "Failed to get Device Ptr" };
			}

			DWORD deviceState;
			hr = devicePtr->GetState(&deviceState);

			if (FAILED(hr))
			{
				BOOST_LOG_TRIVIAL(error) << "Failed to get devices state: " << hr;
				throw std::logic_error{ "Failed to get Device State" };
				
			}
			

			if (deviceState == DEVICE_STATE_ACTIVE)
			{
				activeDevices.push_back(devicePtr);
			}

		}
		return activeDevices;

	}
}