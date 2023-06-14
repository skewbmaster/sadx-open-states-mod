#include "pch.h"
#include "savestate.h"

#include <cstdlib>
#include <string>

NJS_VECTOR PositionLockTEST = {88,0,1500};

static char* InjectNewMem;

static SaveState SaveStates[10] = { SaveState() };
static int CurrentSaveState = 0;

static bool LoadedCamera;

EntityData1 copything;
NJS_VECTOR copycamdelta;
int camdata;
NJS_VECTOR camerapos;
Rotation3 camerarot;
int cameramode;

_camcontwk oldCamContWk;

uint32_t gearRotation;

int savestateMessageTimer = 0;
std::string savestateMessage = "";

void DeserialiseStates(std::string filepath, SaveState* states);
void SerialiseStates(SaveState* states);

void InterruptCameraDelta()
{
	if (LoadedCamera)
	{
		CameraPositionDelta.x = 0;
		CameraPositionDelta.y = 0;
		CameraPositionDelta.z = 0;
		LoadedCamera = false;
	}
	else
	{
		SetCameraPositionDelta();
	}
}

extern "C"
{
	// Executed at startup, contains helperFunctions and the path to your mod (useful for getting the config file.)
	// This is where we override functions, replace static data, etc.
	__declspec(dllexport) void __cdecl Init(const char* path, const HelperFunctions& helperFunctions)
	{
		//DeserialiseStates(std::string(path) + "\\save.states", SaveStates);

		LoadedCamera = false;

		InjectNewMem = (char*)malloc(40);
		PrintDebug("Newmem Location: %X\n", InjectNewMem);

		WriteJump((void*)0x4380E3, InjectNewMem); // Replace SetCameraPositionDelta call to jump to new malloced memory
		WriteCall(InjectNewMem, InterruptCameraDelta); // Call our function from this dll
		WriteJump((void*)(InjectNewMem + 5), (void*)0x4380E8); // Return to Camera_Main

		PrintDebug("Current save slot: %d\n",CurrentSaveState);
	}

	// Executed every running frame of SADX
	__declspec(dllexport) void __cdecl OnFrame()
	{
		
	}

	// Executed before the game processes input
	__declspec(dllexport) void __cdecl OnInput()
	{
		ObjectMaster* gearsTask = ObjectListThing[3];

		if (GetLevelAndAct() == LevelAndActIDs_HotShelter2)
		{
			gearsTask = ObjectListThing[3];

		}

		if (ControllerPointers[0]->PressedButtons & Buttons_Left && IsIngame() && GameState == 15)
		{
			SaveStates[CurrentSaveState].initialised = true;
			SaveStates[CurrentSaveState].Save();
			copything = CameraStructThing;
			
			while (gearsTask->MainSub != (ObjectFuncPtr)0x59FA40)
			{
				gearsTask = gearsTask->Next;
			}

			gearRotation = gearsTask->Data1->Rotation.z;

			//copycamdelta = CameraPositionDelta;
			//camdata = CurrentCamData_;

			//cameramode = GetCameraMode();

			//oldCamContWk = cameraControlWork;

			//SerialiseStates(SaveStates);
		}
		else if (ControllerPointers[0]->PressedButtons & Buttons_Right)
		{
			if (SaveStates[CurrentSaveState].initialised && IsIngame() && GameState == 15)
			{
				SaveStates[CurrentSaveState].Load();
				CameraStructThing = copything;
				//CameraPositionDelta = copycamdelta;
				//CurrentCamData_ = camdata;

				//SetCameraMode(cameramode);

				while (gearsTask->MainSub != (ObjectFuncPtr)0x59FA40)
				{
					gearsTask = gearsTask->Next;
				}

				gearsTask->Data1->Rotation.z = gearRotation;

				cameraControlWork = oldCamContWk;

				LoadedCamera = true;
			}
		}
		else if (ControllerPointers[0]->PressedButtons & Buttons_Up)
		{
			CurrentSaveState++;
			savestateMessageTimer = 
		}
		else if (ControllerPointers[0]->PressedButtons & Buttons_Down)
		{
			CurrentSaveState--;
		}

		CurrentSaveState %= 10;
	}

	// Executed when the game processes input
	__declspec(dllexport) void __cdecl OnControl()
	{
		if (FrameCounter == 90)
		{
			//copything = EntityData1Ptrs[0]->CollisionInfo[0];
			//copything = _nj_camera_;
		}

		if (FrameCounter > 120)
		{
			//PrintDebug("%f, %f, %f\n", EntityData2Ptrs[0]->VelocityDirection.x, EntityData2Ptrs[0]->VelocityDirection.y, EntityData2Ptrs[0]->VelocityDirection.z);
			//PrintDebug("%d\n", EntityData2Ptrs[0]->SomeCollisionVector);
			//EntityData1Ptrs[0]->CollisionInfo[0] = copything;
			//njSetCamera(&copything);
		}
	}

	// Executed when the window size changes
	/*__declspec(dllexport) void __cdecl OnRenderDeviceReset()
	{
		
	}

	// Executed when the game fails to render the scene
	__declspec(dllexport) void __cdecl OnRenderDeviceLost()
	{
		
	}

	// Executed before the game starts rendering the scene
	__declspec(dllexport) void __cdecl OnRenderSceneStart()
	{
		
	}

	// Executed when the game finishes rendering the scene
	__declspec(dllexport) void __cdecl OnRenderSceneEnd()
	{
		
	}*/

	// Executed after every mod has been initialized, mainly used to check if a specific mod is also enabled.
	/*__declspec(dllexport) void __cdecl OnInitEnd()
	{

	}*/

	// Executed when the game is about to terminate
	__declspec(dllexport) void __cdecl OnExit()
	{
	}

	__declspec(dllexport) ModInfo SADXModInfo = { ModLoaderVer }; // This is needed for the Mod Loader to recognize the DLL.
}