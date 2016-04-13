#pragma once

struct IPropertyStore;
struct IMMDevice;
struct IAudioEndpointVolume;
#include <vector>
namespace remote {
	class AudioMasterMind
	{
	public:
		AudioMasterMind();
		~AudioMasterMind();

		void printDevices();
		
		void start();

		void terminate();

		float getMasterVolumeScalar();

		void setMasterVolumeScalar(float scalar);

		void toggleMute();

		void volumeUp();

		void volumeDown();

	private:
		std::vector<IMMDevice*> getActiveDevices();
		IAudioEndpointVolume* audioDevice = nullptr;
		void printDevice(IMMDevice* devicePtr);

	};

}