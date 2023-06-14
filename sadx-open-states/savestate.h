#pragma once

#pragma pack(push, 1)
struct PartialAnimThing
{
	short State;
	short field_2;
	short Index;
	short LastIndex;
	short LastIndex2;
	short field_A;
	short field_C;
	short field_E;
	float Frame;
	int dword14;
};

struct SaveStateData
{
	NJS_VECTOR POSITION;
	Rotation3 ROTATION;
	NJS_VECTOR SPEED;
	short HOVER_FRAMES;

	int16_t RINGS;
	char LIVES;

	char TIME_FRAMES;
	char TIME_SECONDS;
	char TIME_MINUTES;

	char ACTION;
	char NEXT_ACTION;
	char UNKNOWN_ENTITY_DATA1;
	short STATUS;
	short INVULNERABLE_TIME;

	PartialAnimThing ANIMATION_DATA;

	uint32_t FREECAM_XROT; 
	uint32_t FREECAM_YROT;
	NJS_VECTOR CAMERA_POSITION;
	Rotation3 CAMERA_ROTATION;

	int CURRENT_ACT;
	int16_t CURRENT_LEVEL;
	short CURRENT_CHARACTER;
};
#pragma pack(pop)

class SaveState
{
public:
	SaveStateData data;
	bool initialised;

	SaveState();

	void Save();
	void Load();
	
};

