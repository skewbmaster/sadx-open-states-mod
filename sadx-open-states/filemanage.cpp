#pragma once

#include "pch.h"
#include "savestate.h"
#include <iostream>
#include <fstream>

constexpr char STATEFILEVERSION = 4;

std::string FilePath;

void DeserialiseStates(std::string filepath, SaveState* states)
{
	FilePath = filepath;

	std::ifstream File;
	File.open(filepath, std::ios::in | std::ios::binary);
	
	if (File)
	{
		char version;
		char stateCount;

		File.read(&version, sizeof(char));
		File.read(&stateCount, sizeof(char));

		for (char i = 0; i < stateCount; i++)
		{
			char index;
			File.read(&index, sizeof(char));

			states[index].initialised = true;
			
			File.read((char*) &(states[index].data), sizeof(SaveStateData));
		}
	}
	else
	{
		PrintDebug("No states file exists or couldn't be loaded.\n");
	}
	PrintDebug("%f\n", states[0].data.POSITION.x);
	PrintDebug("%d\n", states[0].data.ROTATION.y);
	PrintDebug("%f\n", states[0].data.SPEED.y);
	PrintDebug("%d\n", states[0].data.HOVER_FRAMES);
	PrintDebug("%d\n", states[0].data.LIVES);
	PrintDebug("%d\n", states[0].data.RINGS);
	PrintDebug("%d\n", states[0].data.ACTION);
	PrintDebug("%d\n", states[0].data.NEXT_ACTION);
	PrintDebug("%d\n", states[0].data.STATUS);
	PrintDebug("%d\n", states[0].data.INVULNERABLE_TIME);
	PrintDebug("%d\n", states[0].data.FREECAM_XROT);
	PrintDebug("%d\n", states[0].data.FREECAM_YROT);
	PrintDebug("%f\n", states[0].data.CAMERA_POSITION.x);
	PrintDebug("%d\n", states[0].data.CURRENT_LEVEL);
	PrintDebug("%d\n", states[0].data.CURRENT_ACT);
	PrintDebug("%d\n", states[0].data.CURRENT_CHARACTER);
	PrintDebug("%f\n", states[0].data.ANIMATION_DATA.Frame);
}

void SerialiseStates(SaveState* states)
{
	std::ofstream File;
	File.open(FilePath, std::ios::out | std::ios::binary);

	if (File)
	{
		char stateCount = 0;

		File.write(&STATEFILEVERSION, sizeof(char)); // Version number (4 at the point of mod creation)
		File.seekp(2 * sizeof(char)); // Skip the next byte for number of initialised states

		for (char i = 0; i < 10; i++)
		{
			if (!states[i].initialised)
			{
				continue;
			}

			File.write(&i, sizeof(char)); // Write current index
			File.write((char*) &states[i].data, sizeof(SaveStateData));
			
			stateCount++;
		}

		File.seekp(sizeof(char)); // Go back to 2nd byte
		File.write(&stateCount, sizeof(char)); // and write state count
	}
	else
	{
		PrintDebug("States file could not be created or opened.\n");
	}
}