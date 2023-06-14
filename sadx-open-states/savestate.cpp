#include "pch.h"
#include "savestate.h"

SaveState::SaveState()
{
	initialised = false;
}

void SaveState::Save()
{
	data.POSITION = EntityData1Ptrs[0]->Position;
	data.ROTATION = EntityData1Ptrs[0]->Rotation;
	data.SPEED = CharObj2Ptrs[0]->Speed;
	data.HOVER_FRAMES = CharObj2Ptrs[0]->JumpTime;

	data.LIVES = Lives;
	data.RINGS = Rings;

	data.TIME_FRAMES = TimeFrames;
	data.TIME_SECONDS = TimeSeconds;
	data.TIME_MINUTES = TimeMinutes;

	data.ACTION = EntityData1Ptrs[0]->Action;
	data.NEXT_ACTION = EntityData1Ptrs[0]->NextAction;
	data.UNKNOWN_ENTITY_DATA1 = EntityData1Ptrs[0]->Unknown;
	data.STATUS = EntityData1Ptrs[0]->Status;
	data.INVULNERABLE_TIME = EntityData1Ptrs[0]->InvulnerableTime;

	data.FREECAM_XROT = FreeCamXRotation;
	data.FREECAM_YROT = FreeCamYRotation;
	data.CAMERA_POSITION = Camera_Data1->Position;
	data.CAMERA_ROTATION = Camera_Data1->Rotation;

	data.CURRENT_LEVEL = CurrentLevel;
	data.CURRENT_ACT = CurrentAct;
	data.CURRENT_CHARACTER = CurrentCharacter;

	AnimThing tempAnimData = CharObj2Ptrs[0]->AnimationThing;
	memcpy(&(data.ANIMATION_DATA), &tempAnimData, sizeof(PartialAnimThing));

	PrintDebug("%f\n", data.POSITION.x);
	PrintDebug("%d\n", data.ROTATION.y);
	PrintDebug("%f\n", data.SPEED.y);
	PrintDebug("%d\n", data.HOVER_FRAMES);
	PrintDebug("%d\n", data.LIVES);
	PrintDebug("%d\n", data.RINGS);
	PrintDebug("%d\n", data.ACTION);
	PrintDebug("%d\n", data.NEXT_ACTION);
	PrintDebug("%d\n", data.STATUS);
	PrintDebug("%d\n", data.INVULNERABLE_TIME);
	PrintDebug("%d\n", data.FREECAM_XROT);
	PrintDebug("%d\n", data.FREECAM_YROT);
	PrintDebug("%f\n", data.CAMERA_POSITION.x);
	PrintDebug("%d\n", data.CURRENT_LEVEL);
	PrintDebug("%d\n", data.CURRENT_ACT);
	PrintDebug("%d\n", data.CURRENT_CHARACTER);
	PrintDebug("%d\n", data.ANIMATION_DATA.Frame);
}

void SaveState::Load()
{
	PositionPlayer(0, data.POSITION.x, data.POSITION.y, data.POSITION.z);
	EntityData1Ptrs[0]->Rotation = data.ROTATION;
	CharObj2Ptrs[0]->Speed = data.SPEED;
	CharObj2Ptrs[0]->JumpTime = data.HOVER_FRAMES;

	Lives = data.LIVES;
	Rings = data.RINGS;

	TimeFrames = data.TIME_FRAMES;
	TimeSeconds = data.TIME_SECONDS;
	TimeMinutes = data.TIME_MINUTES;

	EntityData1Ptrs[0]->Action = data.ACTION;
	EntityData1Ptrs[0]->NextAction = data.NEXT_ACTION;
	EntityData1Ptrs[0]->Unknown = data.UNKNOWN_ENTITY_DATA1;
	EntityData1Ptrs[0]->Status = data.STATUS;
	EntityData1Ptrs[0]->InvulnerableTime = data.INVULNERABLE_TIME;

	FreeCamXRotation = data.FREECAM_XROT;
	FreeCamYRotation = data.FREECAM_YROT;
	Camera_Data1->Position = data.CAMERA_POSITION;
	Camera_Data1->Rotation = data.CAMERA_ROTATION;

	memcpy(&(CharObj2Ptrs[0]->AnimationThing), &(data.ANIMATION_DATA), sizeof(PartialAnimThing));
}