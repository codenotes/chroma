// simpleChroma.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"


// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"


#include "targetver.h"



using namespace std;
//! \example ChromaSDKImpl.cpp


#include "ChromaSDKImpl.h"

#ifdef _WIN64
#define CHROMASDKDLL        _T("RzChromaSDK64.dll")
#else
#define CHROMASDKDLL        _T("RzChromaSDK.dll")
#endif

using namespace ChromaSDK;
using namespace ChromaSDK::Keyboard;
using namespace ChromaSDK::Keypad;
using namespace ChromaSDK::Mouse;
using namespace ChromaSDK::Mousepad;
using namespace ChromaSDK::Headset;

typedef RZRESULT(*INIT)(void);
typedef RZRESULT(*UNINIT)(void);
typedef RZRESULT(*CREATEEFFECT)(RZDEVICEID DeviceId, ChromaSDK::EFFECT_TYPE Effect, PRZPARAM pParam, RZEFFECTID *pEffectId);
typedef RZRESULT(*CREATEKEYBOARDEFFECT)(ChromaSDK::Keyboard::EFFECT_TYPE Effect, PRZPARAM pParam, RZEFFECTID *pEffectId);
typedef RZRESULT(*CREATEHEADSETEFFECT)(ChromaSDK::Headset::EFFECT_TYPE Effect, PRZPARAM pParam, RZEFFECTID *pEffectId);
typedef RZRESULT(*CREATEMOUSEPADEFFECT)(ChromaSDK::Mousepad::EFFECT_TYPE Effect, PRZPARAM pParam, RZEFFECTID *pEffectId);
typedef RZRESULT(*CREATEMOUSEEFFECT)(ChromaSDK::Mouse::EFFECT_TYPE Effect, PRZPARAM pParam, RZEFFECTID *pEffectId);
typedef RZRESULT(*CREATEKEYPADEFFECT)(ChromaSDK::Keypad::EFFECT_TYPE Effect, PRZPARAM pParam, RZEFFECTID *pEffectId);
typedef RZRESULT(*SETEFFECT)(RZEFFECTID EffectId);
typedef RZRESULT(*DELETEEFFECT)(RZEFFECTID EffectId);
typedef RZRESULT(*REGISTEREVENTNOTIFICATION)(HWND hWnd);
typedef RZRESULT(*UNREGISTEREVENTNOTIFICATION)(void);
typedef RZRESULT(*QUERYDEVICE)(RZDEVICEID DeviceId, ChromaSDK::DEVICE_INFO_TYPE &DeviceInfo);

INIT Init = NULL;
UNINIT UnInit = NULL;
CREATEEFFECT CreateEffect = NULL;
CREATEKEYBOARDEFFECT CreateKeyboardEffect = NULL;
CREATEMOUSEEFFECT CreateMouseEffect = NULL;
CREATEHEADSETEFFECT CreateHeadsetEffect = NULL;
CREATEMOUSEPADEFFECT CreateMousepadEffect = NULL;
CREATEKEYPADEFFECT CreateKeypadEffect = NULL;
SETEFFECT SetEffect = NULL;
DELETEEFFECT DeleteEffect = NULL;
QUERYDEVICE QueryDevice = NULL;

DWORD WINAPI Thread_LoadingAnimationOnKeyboard(LPVOID lpParameter)
{
	if (CreateKeyboardEffect)
	{
		// Loading animation
		ChromaSDK::Keyboard::CUSTOM_EFFECT_TYPE Effect = {};

		RZEFFECTID Frame1 = GUID_NULL;
		RZEFFECTID Frame2 = GUID_NULL;
		RZEFFECTID Frame3 = GUID_NULL;
		RZEFFECTID Frame4 = GUID_NULL;
		RZEFFECTID Frame5 = GUID_NULL;
		RZEFFECTID Frame6 = GUID_NULL;

		// Create the animation frames if not created
		for (UINT r = 0; r<ChromaSDK::Keyboard::MAX_ROW; r++)
		{
			for (UINT c = 0; c<3; c++)
			{
				Effect.Color[r][c] = ORANGE;
			}
		}

		CreateKeyboardEffect(ChromaSDK::Keyboard::CHROMA_CUSTOM, &Effect, &Frame1);

		for (UINT r = 0; r<ChromaSDK::Keyboard::MAX_ROW; r++)
		{
			for (UINT c = 0; c<6; c++)
			{
				Effect.Color[r][c] = ORANGE;
			}
		}

		CreateKeyboardEffect(ChromaSDK::Keyboard::CHROMA_CUSTOM, &Effect, &Frame2);

		for (UINT r = 0; r<ChromaSDK::Keyboard::MAX_ROW; r++)
		{
			for (UINT c = 0; c<9; c++)
			{
				Effect.Color[r][c] = ORANGE;
			}
		}

		CreateKeyboardEffect(ChromaSDK::Keyboard::CHROMA_CUSTOM, &Effect, &Frame3);

		for (UINT r = 0; r<ChromaSDK::Keyboard::MAX_ROW; r++)
		{
			for (UINT c = 0; c<12; c++)
			{
				Effect.Color[r][c] = ORANGE;
			}
		}

		CreateKeyboardEffect(ChromaSDK::Keyboard::CHROMA_CUSTOM, &Effect, &Frame4);

		for (UINT r = 0; r<ChromaSDK::Keyboard::MAX_ROW; r++)
		{
			for (UINT c = 0; c<15; c++)
			{
				Effect.Color[r][c] = ORANGE;
			}
		}

		CreateKeyboardEffect(ChromaSDK::Keyboard::CHROMA_CUSTOM, &Effect, &Frame5);

		for (UINT r = 0; r<ChromaSDK::Keyboard::MAX_ROW; r++)
		{
			for (UINT c = 0; c<18; c++)
			{
				Effect.Color[r][c] = ORANGE;
			}
		}

		CreateKeyboardEffect(ChromaSDK::Keyboard::CHROMA_CUSTOM, &Effect, &Frame6);

		// Play the animation
		SetEffect(Frame1);
		Sleep(100);
		SetEffect(Frame2);
		Sleep(100);
		SetEffect(Frame3);
		Sleep(100);
		SetEffect(Frame4);
		Sleep(100);
		SetEffect(Frame5);
		Sleep(100);
		SetEffect(Frame6);
		Sleep(100);

		ChromaSDK::Keyboard::STATIC_EFFECT_TYPE StaticEffect = {};
		StaticEffect.Color = ORANGE;

		CreateKeyboardEffect(ChromaSDK::Keyboard::CHROMA_STATIC, &StaticEffect, NULL);
	}

	return 0;
}

DWORD WINAPI Thread_LoadingAnimationOnMousepad(LPVOID lpParameter)
{
	if (CreateMousepadEffect)
	{
		CreateMousepadEffect(ChromaSDK::Mousepad::CHROMA_NONE, NULL, NULL);
		Sleep(100);

		ChromaSDK::Mousepad::CUSTOM_EFFECT_TYPE CustomEffect = {};
		for (UINT i = ChromaSDK::Mousepad::MAX_LEDS - 1; i>0; --i)
		{
			CustomEffect.Color[i] = ORANGE;

			CreateMousepadEffect(ChromaSDK::Mousepad::CHROMA_CUSTOM, &CustomEffect, NULL);

			Sleep(50);
		}
	}

	return 0;
}

DWORD WINAPI Thread_LoadingAnimationOnMice(LPVOID lpParameter)
{
	if (CreateMouseEffect)
	{
		ChromaSDK::Mouse::CUSTOM_EFFECT_TYPE CustomEffect = {};

		for (UINT i = 0; i<7; i++)
		{
			CustomEffect.Color[RZLED_SIDE_STRIP7 - i] = ORANGE;
			CustomEffect.Color[RZLED_SIDE_STRIP14 - i] = ORANGE;

			if (i == 2)
			{
				CustomEffect.Color[RZLED_LOGO] = ORANGE;
			}
			else if (i == 6)
			{
				CustomEffect.Color[RZLED_SCROLLWHEEL] = ORANGE;
			}

			CreateMouseEffect(ChromaSDK::Mouse::CHROMA_CUSTOM, &CustomEffect, NULL);

			Sleep(50);
		}
	}

	return 0;
}

DWORD WINAPI Thread_LoadingAnimationOnKeypad(LPVOID lpParameter)
{
	RZDEVICEID DeviceId = GUID_NULL;
	PTSTR szDevice = (PTSTR)lpParameter;
	if (_tcsicmp(szDevice, _T("Orbweaver")) == 0)
	{
		DeviceId = ORBWEAVER_CHROMA;
	}
	else if (_tcsicmp(szDevice, _T("Tartarus")) == 0)
	{
		DeviceId = TARTARUS_CHROMA;
	}

	if (CreateKeypadEffect)
	{
		ChromaSDK::Keypad::CUSTOM_EFFECT_TYPE Effect = {};

		RZEFFECTID Frame0 = GUID_NULL;
		RZEFFECTID Frame1 = GUID_NULL;
		RZEFFECTID Frame2 = GUID_NULL;
		RZEFFECTID Frame3 = GUID_NULL;
		RZEFFECTID Frame4 = GUID_NULL;
		RZEFFECTID Frame5 = GUID_NULL;

		if (DeviceId == ORBWEAVER_CHROMA)    // Create effects for Orbweaver)
		{
			CreateEffect(DeviceId, ChromaSDK::CHROMA_NONE, NULL, &Frame0);

			for (UINT i = 0; i<1; i++)
			{
				for (UINT j = 0; j<ChromaSDK::Keypad::MAX_ROW; j++)
				{
					Effect.Color[j][i] = ORANGE;
				}
			}

			CreateEffect(DeviceId, ChromaSDK::CHROMA_CUSTOM, &Effect, &Frame1);

			for (UINT i = 0; i<2; i++)
			{
				for (UINT j = 0; j<ChromaSDK::Keypad::MAX_ROW; j++)
				{
					Effect.Color[j][i] = ORANGE;
				}
			}

			CreateEffect(DeviceId, ChromaSDK::CHROMA_CUSTOM, &Effect, &Frame2);

			for (UINT i = 0; i<3; i++)
			{
				for (UINT j = 0; j<ChromaSDK::Keypad::MAX_ROW; j++)
				{
					Effect.Color[j][i] = ORANGE;
				}
			}

			CreateEffect(DeviceId, ChromaSDK::CHROMA_CUSTOM, &Effect, &Frame3);

			for (UINT i = 0; i<4; i++)
			{
				for (UINT j = 0; j<ChromaSDK::Keypad::MAX_ROW; j++)
				{
					Effect.Color[j][i] = ORANGE;
				}
			}

			CreateEffect(DeviceId, ChromaSDK::CHROMA_CUSTOM, &Effect, &Frame4);

			for (UINT i = 0; i<5; i++)
			{
				for (UINT j = 0; j<ChromaSDK::Keypad::MAX_ROW; j++)
				{
					Effect.Color[j][i] = ORANGE;
				}
			}

			CreateEffect(DeviceId, ChromaSDK::CHROMA_CUSTOM, &Effect, &Frame5);
		}
		else if (DeviceId == TARTARUS_CHROMA)    // Create effect for Tartarus
		{
			CreateEffect(DeviceId, ChromaSDK::CHROMA_NONE, NULL, &Frame0);

			Effect.Color[0][0] = RGB((255.0 / 100.0*0.2), ((165.0 / 100.0)*0.2), 00);     // Orange with 20% brightness

			CreateEffect(DeviceId, ChromaSDK::CHROMA_CUSTOM, &Effect, &Frame1);

			Effect.Color[0][0] = RGB((255.0 / 100.0*0.4), ((165.0 / 100.0)*0.4), 00);     // Orange with 40% brightness

			CreateEffect(DeviceId, ChromaSDK::CHROMA_CUSTOM, &Effect, &Frame2);

			Effect.Color[0][0] = RGB((255.0 / 100.0*0.6), ((165.0 / 100.0)*0.6), 00);     // Orange with 60% brightness

			CreateEffect(DeviceId, ChromaSDK::CHROMA_CUSTOM, &Effect, &Frame3);

			Effect.Color[0][0] = RGB((255.0 / 100.0*0.8), ((165.0 / 100.0)*0.8), 00);     // Orange with 80% brightness

			CreateEffect(DeviceId, ChromaSDK::CHROMA_CUSTOM, &Effect, &Frame4);

			Effect.Color[0][0] = ORANGE;                                            // Orange with 100% brightness

			CreateEffect(DeviceId, ChromaSDK::CHROMA_CUSTOM, &Effect, &Frame5);
		}

		// Play the animation
		SetEffect(Frame0);
		Sleep(100);
		SetEffect(Frame1);
		Sleep(100);
		SetEffect(Frame2);
		Sleep(100);
		SetEffect(Frame3);
		Sleep(100);
		SetEffect(Frame4);
		Sleep(100);
		SetEffect(Frame5);
	}

	return 0;
}

CChromaSDKImpl::CChromaSDKImpl() :m_ChromaSDKModule(NULL)
{
}

CChromaSDKImpl::~CChromaSDKImpl()
{
}

BOOL CChromaSDKImpl::Initialize()
{
	if (m_ChromaSDKModule == NULL)
	{
		m_ChromaSDKModule = LoadLibrary(CHROMASDKDLL);
		if (m_ChromaSDKModule == NULL)
		{
			ASSERT(GetLastError() == ERROR_SUCCESS);
			return FALSE;
		}
	}

	if (Init == NULL)
	{
		RZRESULT Result = RZRESULT_INVALID;
		Init = (INIT)GetProcAddress(m_ChromaSDKModule, "Init");
		if (Init)
		{
			Result = Init();
			if (Result == RZRESULT_SUCCESS)
			{
				CreateEffect = (CREATEEFFECT)GetProcAddress(m_ChromaSDKModule, "CreateEffect");
				CreateKeyboardEffect = (CREATEKEYBOARDEFFECT)GetProcAddress(m_ChromaSDKModule, "CreateKeyboardEffect");
				CreateMouseEffect = (CREATEMOUSEEFFECT)GetProcAddress(m_ChromaSDKModule, "CreateMouseEffect");
				CreateHeadsetEffect = (CREATEHEADSETEFFECT)GetProcAddress(m_ChromaSDKModule, "CreateHeadsetEffect");
				CreateMousepadEffect = (CREATEMOUSEPADEFFECT)GetProcAddress(m_ChromaSDKModule, "CreateMousepadEffect");
				CreateKeypadEffect = (CREATEKEYPADEFFECT)GetProcAddress(m_ChromaSDKModule, "CreateKeypadEffect");
				SetEffect = (SETEFFECT)GetProcAddress(m_ChromaSDKModule, "SetEffect");
				DeleteEffect = (DELETEEFFECT)GetProcAddress(m_ChromaSDKModule, "DeleteEffect");
				QueryDevice = (QUERYDEVICE)GetProcAddress(m_ChromaSDKModule, "QueryDevice");

				if (CreateEffect &&
					CreateKeyboardEffect &&
					CreateMouseEffect &&
					CreateHeadsetEffect &&
					CreateMousepadEffect &&
					CreateKeypadEffect &&
					SetEffect &&
					DeleteEffect &&
					QueryDevice)
				{
					return TRUE;
				}
				else
				{
					return FALSE;
				}
			}
		}
	}

	return TRUE;
}

BOOL CChromaSDKImpl::UnInitialize()
{
	if (m_ChromaSDKModule != NULL)
	{
		RZRESULT Result = RZRESULT_INVALID;
		UNINIT UnInit = (UNINIT)GetProcAddress(m_ChromaSDKModule, "UnInit");
		if (UnInit)
		{
			Result = UnInit();
			ASSERT(Result == RZRESULT_SUCCESS);
		}

		FreeLibrary(m_ChromaSDKModule);
		m_ChromaSDKModule = NULL;

		return TRUE;
	}

	return FALSE;
}

void CChromaSDKImpl::PlayLoadingAnimation(UINT DeviceType)
{
	HANDLE hWorkerThread = NULL;
	switch (DeviceType)
	{
	case 1:
		hWorkerThread = CreateThread(NULL, 0, Thread_LoadingAnimationOnKeyboard, this, 0, NULL);
		CloseHandle(hWorkerThread);
		break;
	case 2:
		hWorkerThread = CreateThread(NULL, 0, Thread_LoadingAnimationOnMousepad, this, 0, NULL);
		CloseHandle(hWorkerThread);
		break;
	case 3:
		hWorkerThread = CreateThread(NULL, 0, Thread_LoadingAnimationOnMice, this, 0, NULL);
		CloseHandle(hWorkerThread);
		break;
	case 4:
		break;
	case 5:
		hWorkerThread = CreateThread(NULL, 0, Thread_LoadingAnimationOnKeypad, _T("Orbweaver"), 0, NULL);
		CloseHandle(hWorkerThread);
		hWorkerThread = CreateThread(NULL, 0, Thread_LoadingAnimationOnKeypad, _T("Tartarus"), 0, NULL);
		CloseHandle(hWorkerThread);
		break;
	}
}

void CChromaSDKImpl::ShowKeys(UINT DeviceType, UINT NumKeys, UINT VKey[], COLORREF Color)
{
	RZRESULT Result = RZRESULT_INVALID;

	switch (DeviceType)
	{
	case 1:
		if (CreateKeyboardEffect)
		{
			ChromaSDK::Keyboard::CUSTOM_EFFECT_TYPE Effect = {};

			for (UINT i = 0; i<NumKeys; i++)
			{
				switch (VKey[i])
				{
				case 0x41: Effect.Color[HIBYTE(RZKEY_A)][LOBYTE(RZKEY_A)] = Color; break;
				case 0x42: Effect.Color[HIBYTE(RZKEY_B)][LOBYTE(RZKEY_B)] = Color; break;
				case 0x43: Effect.Color[HIBYTE(RZKEY_C)][LOBYTE(RZKEY_C)] = Color; break;
				case 0x44: Effect.Color[HIBYTE(RZKEY_D)][LOBYTE(RZKEY_D)] = Color; break;
				case 0x45: Effect.Color[HIBYTE(RZKEY_E)][LOBYTE(RZKEY_E)] = Color; break;
				case 0x46: Effect.Color[HIBYTE(RZKEY_F)][LOBYTE(RZKEY_F)] = Color; break;
				case 0x47: Effect.Color[HIBYTE(RZKEY_G)][LOBYTE(RZKEY_G)] = Color; break;
				case 0x48: Effect.Color[HIBYTE(RZKEY_H)][LOBYTE(RZKEY_H)] = Color; break;
				case 0x49: Effect.Color[HIBYTE(RZKEY_I)][LOBYTE(RZKEY_I)] = Color; break;
				case 0x4A: Effect.Color[HIBYTE(RZKEY_J)][LOBYTE(RZKEY_J)] = Color; break;
				case 0x4B: Effect.Color[HIBYTE(RZKEY_K)][LOBYTE(RZKEY_K)] = Color; break;
				case 0x4C: Effect.Color[HIBYTE(RZKEY_L)][LOBYTE(RZKEY_L)] = Color; break;
				case 0x4D: Effect.Color[HIBYTE(RZKEY_M)][LOBYTE(RZKEY_M)] = Color; break;
				case 0x4E: Effect.Color[HIBYTE(RZKEY_N)][LOBYTE(RZKEY_N)] = Color; break;
				case 0x4F: Effect.Color[HIBYTE(RZKEY_O)][LOBYTE(RZKEY_O)] = Color; break;
				case 0x50: Effect.Color[HIBYTE(RZKEY_P)][LOBYTE(RZKEY_P)] = Color; break;
				case 0x51: Effect.Color[HIBYTE(RZKEY_Q)][LOBYTE(RZKEY_Q)] = Color; break;
				case 0x52: Effect.Color[HIBYTE(RZKEY_R)][LOBYTE(RZKEY_R)] = Color; break;
				case 0x53: Effect.Color[HIBYTE(RZKEY_S)][LOBYTE(RZKEY_S)] = Color; break;
				case 0x54: Effect.Color[HIBYTE(RZKEY_T)][LOBYTE(RZKEY_T)] = Color; break;
				case 0x55: Effect.Color[HIBYTE(RZKEY_U)][LOBYTE(RZKEY_U)] = Color; break;
				case 0x56: Effect.Color[HIBYTE(RZKEY_V)][LOBYTE(RZKEY_V)] = Color; break;
				case 0x57: Effect.Color[HIBYTE(RZKEY_W)][LOBYTE(RZKEY_W)] = Color; break;
				case 0x58: Effect.Color[HIBYTE(RZKEY_X)][LOBYTE(RZKEY_X)] = Color; break;
				case 0x59: Effect.Color[HIBYTE(RZKEY_Y)][LOBYTE(RZKEY_Y)] = Color; break;
				case 0x5A: Effect.Color[HIBYTE(RZKEY_Z)][LOBYTE(RZKEY_Z)] = Color; break;
				case VK_LCONTROL: Effect.Color[HIBYTE(RZKEY_LCTRL)][LOBYTE(RZKEY_LCTRL)] = Color; break;
				case VK_LSHIFT: Effect.Color[HIBYTE(RZKEY_LSHIFT)][LOBYTE(RZKEY_LSHIFT)] = Color; break;
				case VK_SPACE: Effect.Color[HIBYTE(RZKEY_SPACE)][LOBYTE(RZKEY_SPACE)] = Color; break;
				}
			}

			Result = CreateKeyboardEffect(ChromaSDK::Keyboard::CHROMA_CUSTOM, &Effect, NULL);

			ASSERT(Result == RZRESULT_SUCCESS);
		}
		break;
	case 5:
		if (CreateKeypadEffect)
		{
			ChromaSDK::Keypad::CUSTOM_EFFECT_TYPE Effect = {};

			for (UINT i = 0; i<NumKeys; i++)
			{
				switch (VKey[i])
				{
				case 0x41: Effect.Color[2][1] = Color; break;
				case 0x44: Effect.Color[2][3] = Color; break;
				case 0x53: Effect.Color[2][2] = Color; break;
				case 0x57: Effect.Color[1][2] = Color; break;
				}
			}

			Result = CreateKeypadEffect(ChromaSDK::Keypad::CHROMA_CUSTOM, &Effect, NULL);

			ASSERT(Result == RZRESULT_SUCCESS);
		}
		break;
	}
}

void CChromaSDKImpl::ShowLevel(UINT DeviceType, UINT Hp, UINT Ammo)
{
	switch (DeviceType)
	{
	case 1:
		if (CreateKeyboardEffect)
		{
			RZRESULT Result = RZRESULT_INVALID;
			ChromaSDK::Keyboard::CUSTOM_EFFECT_TYPE Effect;

			// Initialize the array by setting to black.
			ZeroMemory(&Effect, sizeof(ChromaSDK::Keyboard::CUSTOM_EFFECT_TYPE));

			// Function keys as health
			UINT RemainingHealth = UINT(Hp / 100.0 * 12.0); // 12 function keys

			COLORREF HpColor = RGB((((12 - RemainingHealth) / 12.0) * 255), ((RemainingHealth / 12.0) * 255), 0);

			for (UINT i = 0; i<RemainingHealth; i++)
			{
				// F1 key starts from row 0, column 3 to column column 15
				Effect.Color[0][3 + i] = HpColor;
			}

			// Number keys as ammo
			UINT RemainingAmmo = UINT(Ammo / 100.0 * 10.0); // 10 number keys

			for (UINT i = 0; i<RemainingAmmo; i++)
			{
				// Number keys starts from row 1, column 2 to column 12
				Effect.Color[1][2 + i] = YELLOW;
			}

			Result = CreateKeyboardEffect(ChromaSDK::Keyboard::CHROMA_CUSTOM, &Effect, NULL);

			ASSERT(Result == RZRESULT_SUCCESS);
		}
		break;
	case 2:
		if (CreateMousepadEffect)
		{
			ChromaSDK::Mousepad::CUSTOM_EFFECT_TYPE Effect = {};

			FLOAT RemainingHealth = FLOAT((FLOAT)Hp / 100.0 * 5.0); // 5 LEDs on the left.

			COLORREF HpColor;
			if (RemainingHealth == 0.0)
			{
				HpColor = RED;

				Effect.Color[10] = HpColor;
				Effect.Color[11] = HpColor;
				Effect.Color[12] = HpColor;
				Effect.Color[13] = HpColor;
				Effect.Color[14] = HpColor;
			}
			else
			{
				HpColor = RGB((((5 - RemainingHealth) / 5.0) * 255), ((RemainingHealth / 5.0) * 255), 0);

				for (UINT i = 0; i<RemainingHealth; i++)
				{
					// Display Hp on the left side of the mouse mat.
					Effect.Color[10 + i] = HpColor;
				}
			}

			// Number keys as ammo
			UINT RemainingAmmo = UINT(Ammo / 100.0 * 5.0); // 5 LEDs on the right.

			for (UINT i = 0; i<RemainingAmmo; i++)
			{
				// Display ammo/mana on the right side.
				Effect.Color[4 - i] = YELLOW;
			}

			CreateMousepadEffect(ChromaSDK::Mousepad::CHROMA_CUSTOM, &Effect, NULL);
		}
		break;
	case 3:
		if (CreateMouseEffect)
		{
			ChromaSDK::Mouse::CUSTOM_EFFECT_TYPE Effect = {};

			UINT RemainingHealth = UINT(Hp / 100.0 * 7.0); // 7 LEDs on the left.

			COLORREF HpColor = RGB((((5 - RemainingHealth) / 5.0) * 255), ((RemainingHealth / 5.0) * 255), 0);

			// Display Hp on the left side of the mouse.
			for (UINT i = 0; i<RemainingHealth; i++)
			{
				Effect.Color[RZLED_SIDE_STRIP7 - i] = HpColor;
			}

			UINT RemainingAmmo = UINT(Ammo / 100.0 * 7.0); // 7 LEDs on the right.

														   // Display ammo/mana on the right side of the mouse.
			for (UINT i = 0; i<RemainingAmmo; i++)
			{
				Effect.Color[RZLED_SIDE_STRIP14 - i] = YELLOW;
			}

			CreateMouseEffect(ChromaSDK::Mouse::CHROMA_CUSTOM, &Effect, NULL);
		}
		break;
	case 4:
		if (CreateHeadsetEffect)
		{
			ChromaSDK::Headset::STATIC_EFFECT_TYPE Effect = {};
			Effect.Color = RGB((255 - ((Hp / 100.0) * 255.0)), ((Hp / 100.0) * 255.0), 0);

			CreateHeadsetEffect(ChromaSDK::Headset::CHROMA_STATIC, &Effect, NULL);
		}
		break;
	case 5:
		if (CreateKeypadEffect)
		{
			ChromaSDK::Keypad::CUSTOM_EFFECT_TYPE Effect = {};

			FLOAT RemainingHealth = FLOAT((FLOAT)Hp / 100.0 * 5.0); // 5 keys.

			COLORREF HpColor = RGB((((5 - RemainingHealth) / 5.0) * 255), ((RemainingHealth / 5.0) * 255), 0);

			// Display Hp on keypads.
			for (UINT i = 0; i<RemainingHealth; i++)
			{
				Effect.Color[0][i] = HpColor;
			}

			UINT RemainingAmmo = UINT(Ammo / 100.0 * 5.0); // 5 keys.

														   // Display ammo/mana on the last row.
			for (UINT i = 0; i<RemainingAmmo; i++)
			{
				Effect.Color[3][i] = YELLOW;
			}

			CreateKeypadEffect(ChromaSDK::Keypad::CHROMA_CUSTOM, &Effect, NULL);
		}
		break;
	}
}

void CChromaSDKImpl::ShowAlert(UINT DeviceType, COLORREF Color)
{
	RZEFFECTID Alert = GUID_NULL;
	RZEFFECTID NoAlert = GUID_NULL;

	switch (DeviceType)
	{
	case 1:
		if (CreateKeyboardEffect)
		{
			ChromaSDK::Keyboard::STATIC_EFFECT_TYPE StaticEffect = {};
			StaticEffect.Color = Color;

			CreateKeyboardEffect(ChromaSDK::Keyboard::CHROMA_STATIC, &StaticEffect, &Alert);
			CreateKeyboardEffect(ChromaSDK::Keyboard::CHROMA_NONE, NULL, &NoAlert);

			for (UINT t = 0; t<3; t++)
			{
				SetEffect(Alert);
				Sleep(200);

				SetEffect(NoAlert);
				Sleep(200);
			}

			DeleteEffect(Alert);
			DeleteEffect(NoAlert);
		}
		break;
	case 2:
		if (CreateMousepadEffect)
		{
			ChromaSDK::Mousepad::STATIC_EFFECT_TYPE StaticEffect = {};
			StaticEffect.Color = Color;

			CreateMousepadEffect(ChromaSDK::Mousepad::CHROMA_STATIC, &StaticEffect, &Alert);
			CreateMousepadEffect(ChromaSDK::Mousepad::CHROMA_NONE, NULL, &NoAlert);

			for (UINT t = 0; t<3; t++)
			{
				SetEffect(Alert);
				Sleep(200);

				SetEffect(NoAlert);
				Sleep(200);
			}

			DeleteEffect(Alert);
			DeleteEffect(NoAlert);
		}
		break;
	case 3:
		if (CreateMouseEffect)
		{
			ChromaSDK::Mouse::STATIC_EFFECT_TYPE StaticEffect = {};
			StaticEffect.LEDId = RZLED_ALL;
			StaticEffect.Color = Color;

			ChromaSDK::Mouse::NO_EFFECT_TYPE NoEffect = {};
			NoEffect.LEDId = RZLED_ALL;

			CreateMouseEffect(ChromaSDK::Mouse::CHROMA_STATIC, &StaticEffect, &Alert);
			CreateMouseEffect(ChromaSDK::Mouse::CHROMA_NONE, &NoEffect, &NoAlert);

			for (UINT t = 0; t<3; t++)
			{
				SetEffect(Alert);
				Sleep(200);

				SetEffect(NoAlert);
				Sleep(200);
			}

			DeleteEffect(Alert);
			DeleteEffect(NoAlert);
		}
		break;
	case 4:
		if (CreateHeadsetEffect)
		{
			ChromaSDK::Headset::STATIC_EFFECT_TYPE Effect = {};
			Effect.Color = Color;

			CreateHeadsetEffect(ChromaSDK::Headset::CHROMA_STATIC, &Effect, &Alert);
			CreateHeadsetEffect(ChromaSDK::Headset::CHROMA_NONE, NULL, &NoAlert);

			for (UINT t = 0; t<3; t++)
			{
				SetEffect(Alert);
				Sleep(200);

				SetEffect(NoAlert);
				Sleep(200);
			}

			DeleteEffect(Alert);
			DeleteEffect(NoAlert);
		}
		break;
	case 5:
		if (CreateKeypadEffect)
		{
			ChromaSDK::Keypad::CUSTOM_EFFECT_TYPE Effect = {};

			CreateKeypadEffect(ChromaSDK::Keypad::CHROMA_NONE, NULL, &NoAlert);

			for (UINT i = 0; i<ChromaSDK::Keypad::MAX_ROW; i++)
			{
				for (UINT j = 0; j<ChromaSDK::Keypad::MAX_COLUMN; j++)
				{
					Effect.Color[i][j] = Color;
				}
			}

			CreateKeypadEffect(ChromaSDK::Keypad::CHROMA_CUSTOM, &Effect, &Alert);

			for (UINT t = 0; t<3; t++)
			{
				SetEffect(Alert);
				Sleep(200);

				SetEffect(NoAlert);
				Sleep(200);
			}
		}
		break;
	}
}

void CChromaSDKImpl::ShowGauge(UINT DeviceType, UINT Level)
{
	switch (DeviceType)
	{
	case 1:
		if (CreateKeyboardEffect)
		{
			RZRESULT Result = RZRESULT_INVALID;

			UINT Gauge = UINT(Level / 100.0 * 18.0);

			ChromaSDK::Keyboard::CUSTOM_EFFECT_TYPE Effect = {};
			switch (Gauge)
			{
			case 0:
				Effect.Color[HIBYTE(RZKEY_NUMPAD8)][LOBYTE(RZKEY_NUMPAD8)] = BLACK;
				Effect.Color[HIBYTE(RZKEY_NUMPAD9)][LOBYTE(RZKEY_NUMPAD9)] = BLACK;
				Effect.Color[HIBYTE(RZKEY_NUMPAD6)][LOBYTE(RZKEY_NUMPAD6)] = BLACK;
				Effect.Color[HIBYTE(RZKEY_NUMPAD3)][LOBYTE(RZKEY_NUMPAD3)] = BLACK;
				Effect.Color[HIBYTE(RZKEY_NUMPAD2)][LOBYTE(RZKEY_NUMPAD2)] = BLACK;
				Effect.Color[HIBYTE(RZKEY_NUMPAD1)][LOBYTE(RZKEY_NUMPAD1)] = BLACK;
				Effect.Color[HIBYTE(RZKEY_NUMPAD4)][LOBYTE(RZKEY_NUMPAD4)] = BLACK;
				Effect.Color[HIBYTE(RZKEY_NUMPAD7)][LOBYTE(RZKEY_NUMPAD7)] = BLACK;
				Effect.Color[HIBYTE(RZKEY_NUMPAD5)][LOBYTE(RZKEY_NUMPAD5)] = BLACK;
				break;
			case 1:
				Effect.Color[HIBYTE(RZKEY_NUMPAD8)][LOBYTE(RZKEY_NUMPAD8)] = GREY;
				Effect.Color[HIBYTE(RZKEY_NUMPAD9)][LOBYTE(RZKEY_NUMPAD9)] = BLACK;
				Effect.Color[HIBYTE(RZKEY_NUMPAD6)][LOBYTE(RZKEY_NUMPAD6)] = BLACK;
				Effect.Color[HIBYTE(RZKEY_NUMPAD3)][LOBYTE(RZKEY_NUMPAD3)] = BLACK;
				Effect.Color[HIBYTE(RZKEY_NUMPAD2)][LOBYTE(RZKEY_NUMPAD2)] = BLACK;
				Effect.Color[HIBYTE(RZKEY_NUMPAD1)][LOBYTE(RZKEY_NUMPAD1)] = BLACK;
				Effect.Color[HIBYTE(RZKEY_NUMPAD4)][LOBYTE(RZKEY_NUMPAD4)] = BLACK;
				Effect.Color[HIBYTE(RZKEY_NUMPAD7)][LOBYTE(RZKEY_NUMPAD7)] = BLACK;
				Effect.Color[HIBYTE(RZKEY_NUMPAD5)][LOBYTE(RZKEY_NUMPAD5)] = BLACK;
				break;
			case 2:
				Effect.Color[HIBYTE(RZKEY_NUMPAD8)][LOBYTE(RZKEY_NUMPAD8)] = GREY;
				Effect.Color[HIBYTE(RZKEY_NUMPAD9)][LOBYTE(RZKEY_NUMPAD9)] = GREY;
				Effect.Color[HIBYTE(RZKEY_NUMPAD6)][LOBYTE(RZKEY_NUMPAD6)] = BLACK;
				Effect.Color[HIBYTE(RZKEY_NUMPAD3)][LOBYTE(RZKEY_NUMPAD3)] = BLACK;
				Effect.Color[HIBYTE(RZKEY_NUMPAD2)][LOBYTE(RZKEY_NUMPAD2)] = BLACK;
				Effect.Color[HIBYTE(RZKEY_NUMPAD1)][LOBYTE(RZKEY_NUMPAD1)] = BLACK;
				Effect.Color[HIBYTE(RZKEY_NUMPAD4)][LOBYTE(RZKEY_NUMPAD4)] = BLACK;
				Effect.Color[HIBYTE(RZKEY_NUMPAD7)][LOBYTE(RZKEY_NUMPAD7)] = BLACK;
				Effect.Color[HIBYTE(RZKEY_NUMPAD5)][LOBYTE(RZKEY_NUMPAD5)] = BLACK;
				break;
			case 3:
				Effect.Color[HIBYTE(RZKEY_NUMPAD8)][LOBYTE(RZKEY_NUMPAD8)] = GREY;
				Effect.Color[HIBYTE(RZKEY_NUMPAD9)][LOBYTE(RZKEY_NUMPAD9)] = GREY;
				Effect.Color[HIBYTE(RZKEY_NUMPAD6)][LOBYTE(RZKEY_NUMPAD6)] = GREY;
				Effect.Color[HIBYTE(RZKEY_NUMPAD3)][LOBYTE(RZKEY_NUMPAD3)] = BLACK;
				Effect.Color[HIBYTE(RZKEY_NUMPAD2)][LOBYTE(RZKEY_NUMPAD2)] = BLACK;
				Effect.Color[HIBYTE(RZKEY_NUMPAD1)][LOBYTE(RZKEY_NUMPAD1)] = BLACK;
				Effect.Color[HIBYTE(RZKEY_NUMPAD4)][LOBYTE(RZKEY_NUMPAD4)] = BLACK;
				Effect.Color[HIBYTE(RZKEY_NUMPAD7)][LOBYTE(RZKEY_NUMPAD7)] = BLACK;
				Effect.Color[HIBYTE(RZKEY_NUMPAD5)][LOBYTE(RZKEY_NUMPAD5)] = BLACK;
				break;
			case 4:
				Effect.Color[HIBYTE(RZKEY_NUMPAD8)][LOBYTE(RZKEY_NUMPAD8)] = GREY;
				Effect.Color[HIBYTE(RZKEY_NUMPAD9)][LOBYTE(RZKEY_NUMPAD9)] = GREY;
				Effect.Color[HIBYTE(RZKEY_NUMPAD6)][LOBYTE(RZKEY_NUMPAD6)] = GREY;
				Effect.Color[HIBYTE(RZKEY_NUMPAD3)][LOBYTE(RZKEY_NUMPAD3)] = GREY;
				Effect.Color[HIBYTE(RZKEY_NUMPAD2)][LOBYTE(RZKEY_NUMPAD2)] = BLACK;
				Effect.Color[HIBYTE(RZKEY_NUMPAD1)][LOBYTE(RZKEY_NUMPAD1)] = BLACK;
				Effect.Color[HIBYTE(RZKEY_NUMPAD4)][LOBYTE(RZKEY_NUMPAD4)] = BLACK;
				Effect.Color[HIBYTE(RZKEY_NUMPAD7)][LOBYTE(RZKEY_NUMPAD7)] = BLACK;
				Effect.Color[HIBYTE(RZKEY_NUMPAD5)][LOBYTE(RZKEY_NUMPAD5)] = BLACK;
				break;
			case 5:
				Effect.Color[HIBYTE(RZKEY_NUMPAD8)][LOBYTE(RZKEY_NUMPAD8)] = GREY;
				Effect.Color[HIBYTE(RZKEY_NUMPAD9)][LOBYTE(RZKEY_NUMPAD9)] = GREY;
				Effect.Color[HIBYTE(RZKEY_NUMPAD6)][LOBYTE(RZKEY_NUMPAD6)] = GREY;
				Effect.Color[HIBYTE(RZKEY_NUMPAD3)][LOBYTE(RZKEY_NUMPAD3)] = GREY;
				Effect.Color[HIBYTE(RZKEY_NUMPAD2)][LOBYTE(RZKEY_NUMPAD2)] = GREY;
				Effect.Color[HIBYTE(RZKEY_NUMPAD1)][LOBYTE(RZKEY_NUMPAD1)] = BLACK;
				Effect.Color[HIBYTE(RZKEY_NUMPAD4)][LOBYTE(RZKEY_NUMPAD4)] = BLACK;
				Effect.Color[HIBYTE(RZKEY_NUMPAD7)][LOBYTE(RZKEY_NUMPAD7)] = BLACK;
				Effect.Color[HIBYTE(RZKEY_NUMPAD5)][LOBYTE(RZKEY_NUMPAD5)] = BLACK;
				break;
			case 6:
				Effect.Color[HIBYTE(RZKEY_NUMPAD8)][LOBYTE(RZKEY_NUMPAD8)] = GREY;
				Effect.Color[HIBYTE(RZKEY_NUMPAD9)][LOBYTE(RZKEY_NUMPAD9)] = GREY;
				Effect.Color[HIBYTE(RZKEY_NUMPAD6)][LOBYTE(RZKEY_NUMPAD6)] = GREY;
				Effect.Color[HIBYTE(RZKEY_NUMPAD3)][LOBYTE(RZKEY_NUMPAD3)] = GREY;
				Effect.Color[HIBYTE(RZKEY_NUMPAD2)][LOBYTE(RZKEY_NUMPAD2)] = GREY;
				Effect.Color[HIBYTE(RZKEY_NUMPAD1)][LOBYTE(RZKEY_NUMPAD1)] = GREY;
				Effect.Color[HIBYTE(RZKEY_NUMPAD4)][LOBYTE(RZKEY_NUMPAD4)] = BLACK;
				Effect.Color[HIBYTE(RZKEY_NUMPAD7)][LOBYTE(RZKEY_NUMPAD7)] = BLACK;
				Effect.Color[HIBYTE(RZKEY_NUMPAD5)][LOBYTE(RZKEY_NUMPAD5)] = BLACK;
				break;
			case 7:
				Effect.Color[HIBYTE(RZKEY_NUMPAD8)][LOBYTE(RZKEY_NUMPAD8)] = GREY;
				Effect.Color[HIBYTE(RZKEY_NUMPAD9)][LOBYTE(RZKEY_NUMPAD9)] = GREY;
				Effect.Color[HIBYTE(RZKEY_NUMPAD6)][LOBYTE(RZKEY_NUMPAD6)] = GREY;
				Effect.Color[HIBYTE(RZKEY_NUMPAD3)][LOBYTE(RZKEY_NUMPAD3)] = GREY;
				Effect.Color[HIBYTE(RZKEY_NUMPAD2)][LOBYTE(RZKEY_NUMPAD2)] = GREY;
				Effect.Color[HIBYTE(RZKEY_NUMPAD1)][LOBYTE(RZKEY_NUMPAD1)] = GREY;
				Effect.Color[HIBYTE(RZKEY_NUMPAD4)][LOBYTE(RZKEY_NUMPAD4)] = GREY;
				Effect.Color[HIBYTE(RZKEY_NUMPAD7)][LOBYTE(RZKEY_NUMPAD7)] = BLACK;
				Effect.Color[HIBYTE(RZKEY_NUMPAD5)][LOBYTE(RZKEY_NUMPAD5)] = BLACK;
				break;
			case 8:
				Effect.Color[HIBYTE(RZKEY_NUMPAD8)][LOBYTE(RZKEY_NUMPAD8)] = GREY;
				Effect.Color[HIBYTE(RZKEY_NUMPAD9)][LOBYTE(RZKEY_NUMPAD9)] = GREY;
				Effect.Color[HIBYTE(RZKEY_NUMPAD6)][LOBYTE(RZKEY_NUMPAD6)] = GREY;
				Effect.Color[HIBYTE(RZKEY_NUMPAD3)][LOBYTE(RZKEY_NUMPAD3)] = GREY;
				Effect.Color[HIBYTE(RZKEY_NUMPAD2)][LOBYTE(RZKEY_NUMPAD2)] = GREY;
				Effect.Color[HIBYTE(RZKEY_NUMPAD1)][LOBYTE(RZKEY_NUMPAD1)] = GREY;
				Effect.Color[HIBYTE(RZKEY_NUMPAD4)][LOBYTE(RZKEY_NUMPAD4)] = GREY;
				Effect.Color[HIBYTE(RZKEY_NUMPAD7)][LOBYTE(RZKEY_NUMPAD7)] = GREY;
				Effect.Color[HIBYTE(RZKEY_NUMPAD5)][LOBYTE(RZKEY_NUMPAD5)] = BLACK;
				break;
			case 9:
				Effect.Color[HIBYTE(RZKEY_NUMPAD8)][LOBYTE(RZKEY_NUMPAD8)] = GREY;
				Effect.Color[HIBYTE(RZKEY_NUMPAD9)][LOBYTE(RZKEY_NUMPAD9)] = GREY;
				Effect.Color[HIBYTE(RZKEY_NUMPAD6)][LOBYTE(RZKEY_NUMPAD6)] = GREY;
				Effect.Color[HIBYTE(RZKEY_NUMPAD3)][LOBYTE(RZKEY_NUMPAD3)] = GREY;
				Effect.Color[HIBYTE(RZKEY_NUMPAD2)][LOBYTE(RZKEY_NUMPAD2)] = GREY;
				Effect.Color[HIBYTE(RZKEY_NUMPAD1)][LOBYTE(RZKEY_NUMPAD1)] = GREY;
				Effect.Color[HIBYTE(RZKEY_NUMPAD4)][LOBYTE(RZKEY_NUMPAD4)] = GREY;
				Effect.Color[HIBYTE(RZKEY_NUMPAD7)][LOBYTE(RZKEY_NUMPAD7)] = GREY;
				Effect.Color[HIBYTE(RZKEY_NUMPAD5)][LOBYTE(RZKEY_NUMPAD5)] = GREY;
				break;
			case 10:
				Effect.Color[HIBYTE(RZKEY_NUMPAD8)][LOBYTE(RZKEY_NUMPAD8)] = YELLOW;
				Effect.Color[HIBYTE(RZKEY_NUMPAD9)][LOBYTE(RZKEY_NUMPAD9)] = GREY;
				Effect.Color[HIBYTE(RZKEY_NUMPAD6)][LOBYTE(RZKEY_NUMPAD6)] = GREY;
				Effect.Color[HIBYTE(RZKEY_NUMPAD3)][LOBYTE(RZKEY_NUMPAD3)] = GREY;
				Effect.Color[HIBYTE(RZKEY_NUMPAD2)][LOBYTE(RZKEY_NUMPAD2)] = GREY;
				Effect.Color[HIBYTE(RZKEY_NUMPAD1)][LOBYTE(RZKEY_NUMPAD1)] = GREY;
				Effect.Color[HIBYTE(RZKEY_NUMPAD4)][LOBYTE(RZKEY_NUMPAD4)] = GREY;
				Effect.Color[HIBYTE(RZKEY_NUMPAD7)][LOBYTE(RZKEY_NUMPAD7)] = GREY;
				Effect.Color[HIBYTE(RZKEY_NUMPAD5)][LOBYTE(RZKEY_NUMPAD5)] = GREY;
				break;
			case 11:
				Effect.Color[HIBYTE(RZKEY_NUMPAD8)][LOBYTE(RZKEY_NUMPAD8)] = YELLOW;
				Effect.Color[HIBYTE(RZKEY_NUMPAD9)][LOBYTE(RZKEY_NUMPAD9)] = YELLOW;
				Effect.Color[HIBYTE(RZKEY_NUMPAD6)][LOBYTE(RZKEY_NUMPAD6)] = GREY;
				Effect.Color[HIBYTE(RZKEY_NUMPAD3)][LOBYTE(RZKEY_NUMPAD3)] = GREY;
				Effect.Color[HIBYTE(RZKEY_NUMPAD2)][LOBYTE(RZKEY_NUMPAD2)] = GREY;
				Effect.Color[HIBYTE(RZKEY_NUMPAD1)][LOBYTE(RZKEY_NUMPAD1)] = GREY;
				Effect.Color[HIBYTE(RZKEY_NUMPAD4)][LOBYTE(RZKEY_NUMPAD4)] = GREY;
				Effect.Color[HIBYTE(RZKEY_NUMPAD7)][LOBYTE(RZKEY_NUMPAD7)] = GREY;
				Effect.Color[HIBYTE(RZKEY_NUMPAD5)][LOBYTE(RZKEY_NUMPAD5)] = GREY;
				break;
			case 12:
				Effect.Color[HIBYTE(RZKEY_NUMPAD8)][LOBYTE(RZKEY_NUMPAD8)] = YELLOW;
				Effect.Color[HIBYTE(RZKEY_NUMPAD9)][LOBYTE(RZKEY_NUMPAD9)] = YELLOW;
				Effect.Color[HIBYTE(RZKEY_NUMPAD6)][LOBYTE(RZKEY_NUMPAD6)] = YELLOW;
				Effect.Color[HIBYTE(RZKEY_NUMPAD3)][LOBYTE(RZKEY_NUMPAD3)] = GREY;
				Effect.Color[HIBYTE(RZKEY_NUMPAD2)][LOBYTE(RZKEY_NUMPAD2)] = GREY;
				Effect.Color[HIBYTE(RZKEY_NUMPAD1)][LOBYTE(RZKEY_NUMPAD1)] = GREY;
				Effect.Color[HIBYTE(RZKEY_NUMPAD4)][LOBYTE(RZKEY_NUMPAD4)] = GREY;
				Effect.Color[HIBYTE(RZKEY_NUMPAD7)][LOBYTE(RZKEY_NUMPAD7)] = GREY;
				Effect.Color[HIBYTE(RZKEY_NUMPAD5)][LOBYTE(RZKEY_NUMPAD5)] = GREY;
				break;
			case 13:
				Effect.Color[HIBYTE(RZKEY_NUMPAD8)][LOBYTE(RZKEY_NUMPAD8)] = YELLOW;
				Effect.Color[HIBYTE(RZKEY_NUMPAD9)][LOBYTE(RZKEY_NUMPAD9)] = YELLOW;
				Effect.Color[HIBYTE(RZKEY_NUMPAD6)][LOBYTE(RZKEY_NUMPAD6)] = YELLOW;
				Effect.Color[HIBYTE(RZKEY_NUMPAD3)][LOBYTE(RZKEY_NUMPAD3)] = YELLOW;
				Effect.Color[HIBYTE(RZKEY_NUMPAD2)][LOBYTE(RZKEY_NUMPAD2)] = GREY;
				Effect.Color[HIBYTE(RZKEY_NUMPAD1)][LOBYTE(RZKEY_NUMPAD1)] = GREY;
				Effect.Color[HIBYTE(RZKEY_NUMPAD4)][LOBYTE(RZKEY_NUMPAD4)] = GREY;
				Effect.Color[HIBYTE(RZKEY_NUMPAD7)][LOBYTE(RZKEY_NUMPAD7)] = GREY;
				Effect.Color[HIBYTE(RZKEY_NUMPAD5)][LOBYTE(RZKEY_NUMPAD5)] = GREY;
				break;
			case 14:
				Effect.Color[HIBYTE(RZKEY_NUMPAD8)][LOBYTE(RZKEY_NUMPAD8)] = YELLOW;
				Effect.Color[HIBYTE(RZKEY_NUMPAD9)][LOBYTE(RZKEY_NUMPAD9)] = YELLOW;
				Effect.Color[HIBYTE(RZKEY_NUMPAD6)][LOBYTE(RZKEY_NUMPAD6)] = YELLOW;
				Effect.Color[HIBYTE(RZKEY_NUMPAD3)][LOBYTE(RZKEY_NUMPAD3)] = YELLOW;
				Effect.Color[HIBYTE(RZKEY_NUMPAD2)][LOBYTE(RZKEY_NUMPAD2)] = YELLOW;
				Effect.Color[HIBYTE(RZKEY_NUMPAD1)][LOBYTE(RZKEY_NUMPAD1)] = GREY;
				Effect.Color[HIBYTE(RZKEY_NUMPAD4)][LOBYTE(RZKEY_NUMPAD4)] = GREY;
				Effect.Color[HIBYTE(RZKEY_NUMPAD7)][LOBYTE(RZKEY_NUMPAD7)] = GREY;
				Effect.Color[HIBYTE(RZKEY_NUMPAD5)][LOBYTE(RZKEY_NUMPAD5)] = GREY;
				break;
			case 15:
				Effect.Color[HIBYTE(RZKEY_NUMPAD8)][LOBYTE(RZKEY_NUMPAD8)] = YELLOW;
				Effect.Color[HIBYTE(RZKEY_NUMPAD9)][LOBYTE(RZKEY_NUMPAD9)] = YELLOW;
				Effect.Color[HIBYTE(RZKEY_NUMPAD6)][LOBYTE(RZKEY_NUMPAD6)] = YELLOW;
				Effect.Color[HIBYTE(RZKEY_NUMPAD3)][LOBYTE(RZKEY_NUMPAD3)] = YELLOW;
				Effect.Color[HIBYTE(RZKEY_NUMPAD2)][LOBYTE(RZKEY_NUMPAD2)] = YELLOW;
				Effect.Color[HIBYTE(RZKEY_NUMPAD1)][LOBYTE(RZKEY_NUMPAD1)] = YELLOW;
				Effect.Color[HIBYTE(RZKEY_NUMPAD4)][LOBYTE(RZKEY_NUMPAD4)] = GREY;
				Effect.Color[HIBYTE(RZKEY_NUMPAD7)][LOBYTE(RZKEY_NUMPAD7)] = GREY;
				Effect.Color[HIBYTE(RZKEY_NUMPAD5)][LOBYTE(RZKEY_NUMPAD5)] = GREY;
				break;
			case 16:
				Effect.Color[HIBYTE(RZKEY_NUMPAD8)][LOBYTE(RZKEY_NUMPAD8)] = YELLOW;
				Effect.Color[HIBYTE(RZKEY_NUMPAD9)][LOBYTE(RZKEY_NUMPAD9)] = YELLOW;
				Effect.Color[HIBYTE(RZKEY_NUMPAD6)][LOBYTE(RZKEY_NUMPAD6)] = YELLOW;
				Effect.Color[HIBYTE(RZKEY_NUMPAD3)][LOBYTE(RZKEY_NUMPAD3)] = YELLOW;
				Effect.Color[HIBYTE(RZKEY_NUMPAD2)][LOBYTE(RZKEY_NUMPAD2)] = YELLOW;
				Effect.Color[HIBYTE(RZKEY_NUMPAD1)][LOBYTE(RZKEY_NUMPAD1)] = YELLOW;
				Effect.Color[HIBYTE(RZKEY_NUMPAD4)][LOBYTE(RZKEY_NUMPAD4)] = YELLOW;
				Effect.Color[HIBYTE(RZKEY_NUMPAD7)][LOBYTE(RZKEY_NUMPAD7)] = GREY;
				Effect.Color[HIBYTE(RZKEY_NUMPAD5)][LOBYTE(RZKEY_NUMPAD5)] = GREY;
				break;
			case 17:
				Effect.Color[HIBYTE(RZKEY_NUMPAD8)][LOBYTE(RZKEY_NUMPAD8)] = YELLOW;
				Effect.Color[HIBYTE(RZKEY_NUMPAD9)][LOBYTE(RZKEY_NUMPAD9)] = YELLOW;
				Effect.Color[HIBYTE(RZKEY_NUMPAD6)][LOBYTE(RZKEY_NUMPAD6)] = YELLOW;
				Effect.Color[HIBYTE(RZKEY_NUMPAD3)][LOBYTE(RZKEY_NUMPAD3)] = YELLOW;
				Effect.Color[HIBYTE(RZKEY_NUMPAD2)][LOBYTE(RZKEY_NUMPAD2)] = YELLOW;
				Effect.Color[HIBYTE(RZKEY_NUMPAD1)][LOBYTE(RZKEY_NUMPAD1)] = YELLOW;
				Effect.Color[HIBYTE(RZKEY_NUMPAD4)][LOBYTE(RZKEY_NUMPAD4)] = YELLOW;
				Effect.Color[HIBYTE(RZKEY_NUMPAD7)][LOBYTE(RZKEY_NUMPAD7)] = YELLOW;
				Effect.Color[HIBYTE(RZKEY_NUMPAD5)][LOBYTE(RZKEY_NUMPAD5)] = GREY;
				break;
			case 18:
				Effect.Color[HIBYTE(RZKEY_NUMPAD8)][LOBYTE(RZKEY_NUMPAD8)] = YELLOW;
				Effect.Color[HIBYTE(RZKEY_NUMPAD9)][LOBYTE(RZKEY_NUMPAD9)] = YELLOW;
				Effect.Color[HIBYTE(RZKEY_NUMPAD6)][LOBYTE(RZKEY_NUMPAD6)] = YELLOW;
				Effect.Color[HIBYTE(RZKEY_NUMPAD3)][LOBYTE(RZKEY_NUMPAD3)] = YELLOW;
				Effect.Color[HIBYTE(RZKEY_NUMPAD2)][LOBYTE(RZKEY_NUMPAD2)] = YELLOW;
				Effect.Color[HIBYTE(RZKEY_NUMPAD1)][LOBYTE(RZKEY_NUMPAD1)] = YELLOW;
				Effect.Color[HIBYTE(RZKEY_NUMPAD4)][LOBYTE(RZKEY_NUMPAD4)] = YELLOW;
				Effect.Color[HIBYTE(RZKEY_NUMPAD7)][LOBYTE(RZKEY_NUMPAD7)] = YELLOW;
				Effect.Color[HIBYTE(RZKEY_NUMPAD5)][LOBYTE(RZKEY_NUMPAD5)] = YELLOW;
				break;
			}

			Result = CreateKeyboardEffect(ChromaSDK::Keyboard::CHROMA_CUSTOM, &Effect, NULL);

			ASSERT(Result == RZRESULT_SUCCESS);
		}
		break;
	case 2:
		if (CreateMousepadEffect)
		{
			UINT Gauge = UINT(Level / 100.0 * 15.0);

			ChromaSDK::Mousepad::CUSTOM_EFFECT_TYPE Effect = {};

			for (UINT i = 0; i<Gauge; i++)
			{
				Effect.Color[i] = RED;
			}

			CreateMousepadEffect(ChromaSDK::Mousepad::CHROMA_CUSTOM, &Effect, NULL);
		}
		break;
	case 5:
		if (CreateKeypadEffect)
		{
			ChromaSDK::Keypad::CUSTOM_EFFECT_TYPE Effect = {};

			UINT Gauge = UINT(Level / 100.0 * 14.0);

			switch (Gauge)
			{
			case 1:
				Effect.Color[0][0] = YELLOW;
				break;
			case 2:
				Effect.Color[0][0] = YELLOW;
				Effect.Color[0][1] = YELLOW;
				break;
			case 3:
				Effect.Color[0][0] = YELLOW;
				Effect.Color[0][1] = YELLOW;
				Effect.Color[0][2] = YELLOW;
				break;
			case 4:
				Effect.Color[0][0] = YELLOW;
				Effect.Color[0][1] = YELLOW;
				Effect.Color[0][2] = YELLOW;
				Effect.Color[0][3] = YELLOW;
				break;
			case 5:
				Effect.Color[0][0] = YELLOW;
				Effect.Color[0][1] = YELLOW;
				Effect.Color[0][2] = YELLOW;
				Effect.Color[0][3] = YELLOW;
				Effect.Color[0][4] = YELLOW;
				break;
			case 6:
				Effect.Color[0][0] = YELLOW;
				Effect.Color[0][1] = YELLOW;
				Effect.Color[0][2] = YELLOW;
				Effect.Color[0][3] = YELLOW;
				Effect.Color[0][4] = YELLOW;
				Effect.Color[1][4] = YELLOW;
				break;
			case 7:
				Effect.Color[0][0] = YELLOW;
				Effect.Color[0][1] = YELLOW;
				Effect.Color[0][2] = YELLOW;
				Effect.Color[0][3] = YELLOW;
				Effect.Color[0][4] = YELLOW;
				Effect.Color[1][4] = YELLOW;
				Effect.Color[2][4] = YELLOW;
				break;
			case 8:
				Effect.Color[0][0] = YELLOW;
				Effect.Color[0][1] = YELLOW;
				Effect.Color[0][2] = YELLOW;
				Effect.Color[0][3] = YELLOW;
				Effect.Color[0][4] = YELLOW;
				Effect.Color[1][4] = YELLOW;
				Effect.Color[2][4] = YELLOW;
				Effect.Color[3][4] = YELLOW;
				break;
			case 9:
				Effect.Color[0][0] = YELLOW;
				Effect.Color[0][1] = YELLOW;
				Effect.Color[0][2] = YELLOW;
				Effect.Color[0][3] = YELLOW;
				Effect.Color[0][4] = YELLOW;
				Effect.Color[1][4] = YELLOW;
				Effect.Color[2][4] = YELLOW;
				Effect.Color[3][4] = YELLOW;
				Effect.Color[3][3] = YELLOW;
				break;
			case 10:
				Effect.Color[0][0] = YELLOW;
				Effect.Color[0][1] = YELLOW;
				Effect.Color[0][2] = YELLOW;
				Effect.Color[0][3] = YELLOW;
				Effect.Color[0][4] = YELLOW;
				Effect.Color[1][4] = YELLOW;
				Effect.Color[2][4] = YELLOW;
				Effect.Color[3][4] = YELLOW;
				Effect.Color[3][3] = YELLOW;
				Effect.Color[3][2] = YELLOW;
				break;
			case 11:
				Effect.Color[0][0] = YELLOW;
				Effect.Color[0][1] = YELLOW;
				Effect.Color[0][2] = YELLOW;
				Effect.Color[0][3] = YELLOW;
				Effect.Color[0][4] = YELLOW;
				Effect.Color[1][4] = YELLOW;
				Effect.Color[2][4] = YELLOW;
				Effect.Color[3][4] = YELLOW;
				Effect.Color[3][3] = YELLOW;
				Effect.Color[3][2] = YELLOW;
				Effect.Color[3][1] = YELLOW;
				break;
			case 12:
				Effect.Color[0][0] = YELLOW;
				Effect.Color[0][1] = YELLOW;
				Effect.Color[0][2] = YELLOW;
				Effect.Color[0][3] = YELLOW;
				Effect.Color[0][4] = YELLOW;
				Effect.Color[1][4] = YELLOW;
				Effect.Color[2][4] = YELLOW;
				Effect.Color[3][4] = YELLOW;
				Effect.Color[3][3] = YELLOW;
				Effect.Color[3][2] = YELLOW;
				Effect.Color[3][1] = YELLOW;
				Effect.Color[3][0] = YELLOW;
				break;
			case 13:
				Effect.Color[0][0] = YELLOW;
				Effect.Color[0][1] = YELLOW;
				Effect.Color[0][2] = YELLOW;
				Effect.Color[0][3] = YELLOW;
				Effect.Color[0][4] = YELLOW;
				Effect.Color[1][4] = YELLOW;
				Effect.Color[2][4] = YELLOW;
				Effect.Color[3][4] = YELLOW;
				Effect.Color[3][3] = YELLOW;
				Effect.Color[3][2] = YELLOW;
				Effect.Color[3][1] = YELLOW;
				Effect.Color[3][0] = YELLOW;
				Effect.Color[2][0] = YELLOW;
				break;
			case 14:
				Effect.Color[0][0] = YELLOW;
				Effect.Color[0][1] = YELLOW;
				Effect.Color[0][2] = YELLOW;
				Effect.Color[0][3] = YELLOW;
				Effect.Color[0][4] = YELLOW;
				Effect.Color[1][4] = YELLOW;
				Effect.Color[2][4] = YELLOW;
				Effect.Color[3][4] = YELLOW;
				Effect.Color[3][3] = YELLOW;
				Effect.Color[3][2] = YELLOW;
				Effect.Color[3][1] = YELLOW;
				Effect.Color[3][0] = YELLOW;
				Effect.Color[2][0] = YELLOW;
				Effect.Color[1][0] = YELLOW;
				break;
			}

			CreateKeypadEffect(ChromaSDK::Keypad::CHROMA_CUSTOM, &Effect, NULL);
		}
		break;
	}
}

void CChromaSDKImpl::ShowBitmap(UINT DeviceType, HBITMAP hBitmap)
{
	HWND hDesktopWin = GetDesktopWindow();
	HDC hDesktopDC = ::GetDC(hDesktopWin);
	if (hDesktopDC)
	{
		HDC hDestDC = ::CreateCompatibleDC(hDesktopDC);

		::SelectObject(hDestDC, hBitmap);

		BITMAP bm;
		::GetObject(hBitmap, sizeof(bm), &bm);

		BITMAPINFOHEADER bmi = { 0 };
		bmi.biSize = sizeof(BITMAPINFOHEADER);
		bmi.biPlanes = bm.bmPlanes;
		bmi.biBitCount = bm.bmBitsPixel;

		if (DeviceType == 1)
		{
			bmi.biWidth = ChromaSDK::Keyboard::MAX_COLUMN;
			bmi.biHeight = ChromaSDK::Keyboard::MAX_ROW;
		}
		else if (DeviceType == 5)
		{
			bmi.biWidth = ChromaSDK::Keypad::MAX_COLUMN;
			bmi.biHeight = ChromaSDK::Keypad::MAX_ROW;
		}

		bmi.biCompression = BI_RGB;
		bmi.biSizeImage = 0;

		BYTE *pBits = NULL;
		pBits = (BYTE*)malloc(4 * bmi.biWidth * bmi.biHeight);
		ZeroMemory(pBits, (4 * bmi.biWidth * bmi.biHeight));

		if ((DeviceType == 1) && CreateKeyboardEffect)
		{
			ChromaSDK::Keyboard::CUSTOM_EFFECT_TYPE Effect = {};
			for (UINT i = 0; i<ChromaSDK::Keyboard::MAX_ROW; i++)
			{
				// Get ths RGB bits for each row
				::GetDIBits(hDestDC, hBitmap, i, 1, pBits, (BITMAPINFO*)&bmi, DIB_RGB_COLORS);

				COLORREF *pColor = (COLORREF*)pBits;

				for (UINT j = 0; j<ChromaSDK::Keyboard::MAX_COLUMN; j++)
				{
					// Fill up the array
					Effect.Color[i][j] = RGB(GetBValue(*pColor), GetGValue(*pColor), GetRValue(*pColor));
					pColor++;
				}
			}

			// Set the effect
			CreateKeyboardEffect(ChromaSDK::Keyboard::CHROMA_CUSTOM, &Effect, NULL);
		}
		else if ((DeviceType == 5) && CreateKeypadEffect)
		{
			ChromaSDK::Keypad::CUSTOM_EFFECT_TYPE Effect = {};
			for (UINT i = 0; i<ChromaSDK::Keypad::MAX_ROW; i++)
			{
				// Get ths RGB bits for each row
				::GetDIBits(hDestDC, hBitmap, i, 1, pBits, (BITMAPINFO*)&bmi, DIB_RGB_COLORS);

				COLORREF *pColor = (COLORREF*)pBits;

				for (UINT j = 0; j<ChromaSDK::Keypad::MAX_COLUMN; j++)
				{
					// Fill up the array
					Effect.Color[i][j] = RGB(GetBValue(*pColor), GetGValue(*pColor), GetRValue(*pColor));
					pColor++;
				}
			}

			// Set the effect
			CreateKeypadEffect(ChromaSDK::Keypad::CHROMA_CUSTOM, &Effect, NULL);
		}

		free(pBits);

		// Free memories.
		::DeleteDC(hDestDC);

		::ReleaseDC(hDesktopWin, hDesktopDC);
	}
}

void CChromaSDKImpl::ShowDamageEffect(UINT DeviceType)
{
	switch (DeviceType)
	{
	case 1:
		if (CreateKeyboardEffect)
		{
			RZRESULT Result = RZRESULT_INVALID;
			ChromaSDK::Keyboard::STATIC_EFFECT_TYPE HitEffect = {};
			HitEffect.Color = RED;

			// Flash red quickly
			CreateKeyboardEffect(ChromaSDK::Keyboard::CHROMA_STATIC, &HitEffect, NULL);
			Sleep(50);
			CreateKeyboardEffect(ChromaSDK::Keyboard::CHROMA_NONE, NULL, NULL);
		}
		break;
	case 2:
		if (CreateMousepadEffect)
		{
			ChromaSDK::Mousepad::STATIC_EFFECT_TYPE Effect = {};
			Effect.Color = RED;

			CreateMousepadEffect(ChromaSDK::Mousepad::CHROMA_STATIC, &Effect, NULL);
			Sleep(50);
			CreateMousepadEffect(ChromaSDK::Mousepad::CHROMA_NONE, NULL, NULL);
		}
		break;
	case 3:
		if (CreateMouseEffect)
		{
			ChromaSDK::Mouse::STATIC_EFFECT_TYPE Effect = {};
			Effect.LEDId = RZLED_ALL;
			Effect.Color = RED;

			ChromaSDK::Mouse::STATIC_EFFECT_TYPE NoEffect = {};
			NoEffect.LEDId = RZLED_ALL;

			CreateMouseEffect(ChromaSDK::Mouse::CHROMA_STATIC, &Effect, NULL);
			Sleep(50);
			CreateMouseEffect(ChromaSDK::Mouse::CHROMA_NONE, &NoEffect, NULL);
		}
		break;
	case 4:
		if (CreateHeadsetEffect)
		{
			ChromaSDK::Headset::STATIC_EFFECT_TYPE Effect = {};
			Effect.Color = RED;

			CreateHeadsetEffect(ChromaSDK::Headset::CHROMA_STATIC, &Effect, NULL);
			Sleep(50);
			CreateHeadsetEffect(ChromaSDK::Headset::CHROMA_NONE, NULL, NULL);
		}
		break;
	}
}

void CChromaSDKImpl::ShowColor(UINT DeviceType, COLORREF Color)
{
	switch (DeviceType)
	{
	case 1:
		if (CreateKeyboardEffect)
		{
			ChromaSDK::Keyboard::STATIC_EFFECT_TYPE Effect = {};
			Effect.Color = Color;

			RZRESULT Result = CreateKeyboardEffect(ChromaSDK::Keyboard::CHROMA_STATIC, &Effect, NULL);

			ASSERT(Result == RZRESULT_SUCCESS);
		}
		break;
	case 4:
		if (CreateHeadsetEffect)
		{
			ChromaSDK::Headset::STATIC_EFFECT_TYPE Effect = {};
			Effect.Color = Color;

			RZRESULT Result = CreateHeadsetEffect(ChromaSDK::Headset::CHROMA_STATIC, &Effect, NULL);

			ASSERT(Result == RZRESULT_SUCCESS);
		}
	case 5:
		if (CreateKeypadEffect)
		{
			ChromaSDK::Keypad::CUSTOM_EFFECT_TYPE Effect = {};

			for (UINT i = 0; i<ChromaSDK::Keypad::MAX_ROW; i++)
			{
				for (UINT j = 0; j<ChromaSDK::Keypad::MAX_COLUMN; j++)
				{
					Effect.Color[i][j] = Color;
				}
			}

			RZRESULT Result = CreateKeypadEffect(ChromaSDK::Keypad::CHROMA_CUSTOM, &Effect, NULL);

			ASSERT(Result == RZRESULT_SUCCESS);
		}
	}
}

void CChromaSDKImpl::ResetEffects(UINT DeviceType)
{
	switch (DeviceType)
	{
	case 0:
		if (CreateKeyboardEffect)
		{
			CreateKeyboardEffect(ChromaSDK::Keyboard::CHROMA_NONE, NULL, NULL);
		}

		if (CreateMousepadEffect)
		{
			CreateMousepadEffect(ChromaSDK::Mousepad::CHROMA_NONE, NULL, NULL);
		}

		if (CreateMouseEffect)
		{
			CreateMouseEffect(ChromaSDK::Mouse::CHROMA_NONE, NULL, NULL);
		}

		if (CreateHeadsetEffect)
		{
			CreateHeadsetEffect(ChromaSDK::Headset::CHROMA_NONE, NULL, NULL);
		}

		if (CreateKeypadEffect)
		{
			CreateKeypadEffect(ChromaSDK::Keypad::CHROMA_NONE, NULL, NULL);
		}
		break;
	case 1:
		if (CreateKeyboardEffect)
		{
			CreateKeyboardEffect(ChromaSDK::Keyboard::CHROMA_NONE, NULL, NULL);
		}
		break;
	case 2:
		if (CreateMousepadEffect)
		{
			CreateMousepadEffect(ChromaSDK::Mousepad::CHROMA_NONE, NULL, NULL);
		}
		break;
	case 3:
		if (CreateMouseEffect)
		{
			CreateMouseEffect(ChromaSDK::Mouse::CHROMA_NONE, NULL, NULL);
		}
		break;
	case 4:
		if (CreateHeadsetEffect)
		{
			CreateHeadsetEffect(ChromaSDK::Headset::CHROMA_NONE, NULL, NULL);
		}
		break;
	case 5:
		if (CreateKeypadEffect)
		{
			CreateKeypadEffect(ChromaSDK::Keypad::CHROMA_NONE, NULL, NULL);
		}
		break;
	}
}

BOOL CChromaSDKImpl::IsDeviceConnected(RZDEVICEID DeviceId)
{
	if (QueryDevice != NULL)
	{
		ChromaSDK::DEVICE_INFO_TYPE DeviceInfo = {};
		RZRESULT Result = QueryDevice(DeviceId, DeviceInfo);

		ASSERT(Result == RZRESULT_SUCCESS);

		return DeviceInfo.Connected;
	}

	return FALSE;
}




int CChromaSDKImpl::returnCode(const char * keyname)
{

	static std::map<std::string, int> maps =
	{ { "ESC", 0x0001 },                 /*!< Esc */
	{ "F1",0x0003 },                  /*!< F1 */
	{ "F2",0x0004 },                  /*!< F2 */
	{ "F3",0x0005 },                  /*!< F3 */
	{ "F4",0x0006 },                  /*!< F4 */
	{ "F5",0x0007 },                  /*!< F5 */
	{ "F6",0x0008 },                  /*!< F6 */
	{ "F7",0x0009 },                  /*!< F7 */
	{ "F8",0x000A },                  /*!< F8 */
	{ "F9",0x000B },                  /*!< F9 */
	{ "F10",0x000C },                 /*!< F10 */
	{ "F11",0x000D },                 /*!< F11 */
	{ "F12",0x000E },                 /*!< F12 */
	{ "1",0x0102 },                   /*!< 1 */
	{ "2",0x0103 },                   /*!< 2 */
	{ "3",0x0104 },                   /*!< 3 */
	{ "4",0x0105 },                   /*!< 4 */
	{ "5",0x0106 },                   /*!< 5 */
	{ "6",0x0107 },                   /*!< 6 */
	{ "7",0x0108 },                   /*!< 7 */
	{ "8",0x0109 },                   /*!< 8 */
	{ "9",0x010A },                   /*!< 9 */
	{ "0",0x010B },                   /*!< 0 */
	{ "A",0x0302 },                   /*!< A */
	{ "B",0x0407 },                   /*!< B */
	{ "C",0x0405 },                   /*!< C */
	{ "D",0x0304 },                   /*!< D */
	{ "E",0x0204 },                   /*!< E */
	{ "F",0x0305 },                   /*!< F */
	{ "G",0x0306 },                   /*!< G */
	{ "H",0x0307 },                   /*!< H */
	{ "I",0x0209 },                   /*!< I */
	{ "J",0x0308 },                   /*!< J */
	{ "K",0x0309 },                   /*!< K */
	{ "L",0x030A },                   /*!< L */
	{ "M",0x0409 },                   /*!< M */
	{ "N",0x0408 },                   /*!< N */
	{ "O",0x020A },                   /*!< O */
	{ "P",0x020B },                   /*!< P */
	{ "Q",0x0202 },                   /*!< Q */
	{ "R",0x0205 },                   /*!< R */
	{ "S",0x0303 },                   /*!< S */
	{ "T",0x0206 },                   /*!< T */
	{ "U",0x0208 },                   /*!< U */
	{ "V",0x0406 },                   /*!< V */
	{ "W",0x0203 },                   /*!< W */
	{ "X",0x0404 },                   /*!< X */
	{ "Y",0x0207 },                   /*!< Y */
	{ "Z",0x0403 },                   /*!< Z */
	{ "NUMLOCK",0x0112 },             /*!< Numlock */
	{ "NUMPAD0",0x0513 },             /*!< Numpad 0 */
	{ "NUMPAD1",0x0412 },             /*!< Numpad 1 */
	{ "NUMPAD2",0x0413 },             /*!< Numpad 2 */
	{ "NUMPAD3",0x0414 },             /*!< Numpad 3 */
	{ "NUMPAD4",0x0312 },             /*!< Numpad 4 */
	{ "NUMPAD5",0x0313 },             /*!< Numpad 5 */
	{ "NUMPAD6",0x0314 },             /*!< Numpad 6 */
	{ "NUMPAD7",0x0212 },             /*!< Numpad 7 */
	{ "NUMPAD8",0x0213 },             /*!< Numpad 8 */
	{ "NUMPAD9",0x0214 },             /*!< Numpad 9*/
	{ "NUMPAD_DIVIDE",0x0113 },       /*!< Divide */
	{ "NUMPAD_MULTIPLY",0x0114 },     /*!< Multiply */
	{ "NUMPAD_SUBTRACT",0x0115 },      /*!< Subtract */
	{ "NUMPAD_ADD",0x0215 },          /*!< Add */
	{ "NUMPAD_ENTER",0x0415 },        /*!< Enter */
	{ "NUMPAD_DECIMAL",0x0514 },      /*!< Decimal */
	{ "PRINTSCREEN",0x000F },         /*!< Print Screen */
	{ "SCROLL",0x0010 },              /*!< Scroll Lock */
	{ "PAUSE",0x0011 },               /*!< Pause */
	{ "INSERT",0x010F },              /*!< Insert */
	{ "HOME",0x0110 },                /*!< Home */
	{ "PAGEUP",0x0111 },              /*!< Page Up */
	{ "DELETE",0x020f },              /*!< Delete */
	{ "END",0x0210 },                 /*!< End */
	{ "PAGEDOWN",0x0211 },            /*!< Page Down */
	{ "UP",0x0410 },                  /*!< Up */
	{ "LEFT",0x050F },                /*!< Left */
	{ "DOWN",0x0510 },                /*!< Down */
	{ "RIGHT",0x0511 },               /*!< Right */
	{ "TAB",0x0201 },                 /*!< Tab */
	{ "CAPSLOCK",0x0301 },            /*!< Caps Lock*/
	{ "BACKSPACE",0x010E },           /*!<  Backspace */
	{ "ENTER",0x030E },               /*!< Enter */
	{ "LCTRL",0x0501 },               /*!< Left Control*/
	{ "LWIN",0x0502 },                /*!< Left Window */
	{ "LALT",0x0503 },                /*!< Left Alt */
	{ "SPACE",0x0507 },               /*!< Spacebar */
	{ "RALT",0x050B },                /*!< Right Alt */
	{ "FN",0x050C },                  /*!< 'Fn' function key. */
	{ "RMENU",0x050D },               /*!< Right Menu */
	{ "RCTRL",0x050E },               /*!< Right Control */
	{ "LSHIFT",0x0401 },              /*!< Left Shift */
	{ "RSHIFT",0x040E },              /*!< Right Shift */
	{ "MACRO1",0x0100 },              /*!< Macro Key 1*/
	{ "MACRO2",0x0200 },              /*!< Macro Key 2*/
	{ "MACRO3",0x0300 },              /*!< Macro Key 3 */
	{ "MACRO4",0x0400 },              /*!< Macro Key 4*/
	{ "MACRO5",0x0500 },              /*!< Macro Key 5 */
	{ "~",0x0101 },               /*!< ~  tilde. ??/?? */
	{ "-",0x010C },               /*!< -  minus. */
	{ "=",0x010D },               /*!<", equal. */
	{ "[",0x020C },               /*!< [  left sqaure bracket. */
	{ "]",0x020D },               /*!< ]  right square bracket. */
	{ "\\",0x020E },               /*!< \  backslash. */
	{ ";",0x030B },               /*!< ;  semi-colon. */
	{ "`",0x030C },               /*!< '  apostrophe. */
	{ ",",0x040A },               /*!< ,  comma. */
	{ ".",0x040B },              /*!< .  period. */
	{ "/",0x040C },              /*!< /  forward slash. */
	{ "#",0x030D },               /*!< # */
	{ "BACKSLASH2",0x0402 },               /*!< \ */
	{ "JPN_1",0x0015 },               /*!< � */
	{ "JPN_2",0x040D },               /*!< / */
	{ "JPN_3",0x0504 },               /*!< ??? */
	{ "JPN_4",0x0509 },               /*!< ?? */
	{ "JPN_5",0x050A },               /*!< ????/???? */
	{ "KOR_1",0x0015 },               /*!< | */
	{ "KOR_2",0x030D },
	{ "KOR_3",0x0402 },
	{ "KOR_4",0x040D },
	{ "KOR_5",0x0504 },               /*!< ?? */
	{ "KOR_6",0x0509 },               /*!< ?/? */
	{ "KOR_7",0x050A },
	{ "INVALID",0xFFFF } };            /*!< Invalid keys. */


	if (maps.find(keyname) != maps.end())
		return maps[keyname];
	else
		return 0;

}

bool CChromaSDKImpl::setKeys(std::map<std::string, DWORD> arg)
{


	ChromaSDK::Keyboard::CUSTOM_EFFECT_TYPE Effect = {};

	for (auto &s : arg)
	{

		int code = returnCode(s.first.c_str());
		if (!code)
		{
			printf("bad code\n");
			continue;

		}
		Effect.Color[HIBYTE(code)][LOBYTE(code)] = s.second;

	}
	CreateKeyboardEffect(ChromaSDK::Keyboard::CHROMA_CUSTOM, &Effect, NULL);


}

bool CChromaSDKImpl::setKey(const char * keyname, DWORD color)
{

	int code = returnCode(keyname);
	if (!code)
		return false;
	ChromaSDK::Keyboard::CUSTOM_EFFECT_TYPE Effect = {};
	Effect.Color[HIBYTE(code)][LOBYTE(code)] = color;
	CreateKeyboardEffect(ChromaSDK::Keyboard::CHROMA_CUSTOM, &Effect, NULL);





}

CChromaSDKImpl * gChroma;


extern "C"
{

	//std::map<std::string, DWORD> x = {
	//	{ "E", RGB(0, 0, 255) },
	//	{ ";", RGB(255, 0, 255) }
	//};

	_declspec(dllexport) void ChromaUninitialize()
	{
		gChroma->UnInitialize();
		delete gChroma;
		gChroma = 0;


	}


	_declspec(dllexport) void ChromaReset()
	{

		CreateKeyboardEffect(ChromaSDK::Keyboard::CHROMA_NONE, NULL, NULL);

	}


	_declspec(dllexport) bool ChromaSendKeyColors(std::map<std::string, DWORD> & commands)
	{
		

		if (!gChroma)
		{
			gChroma = new CChromaSDKImpl();

			gChroma->Initialize();

			if (!gChroma->IsDeviceConnected(BLACKWIDOW_CHROMA))
			{
				return false;
			}


		}

		gChroma->setKeys(commands);

		return true;


	}



}


int main()
{
	CChromaSDKImpl c;
	c.Initialize();

	if (c.IsDeviceConnected(BLACKWIDOW_CHROMA))
	{
		cout << "it is" << endl;
	}


	//c.setKey("E", RGB(0, 0, 255));
	//c.setKey("H", RGB(0, 0, 255));

	std::map<std::string, DWORD> x = {
		{ "E", RGB(0, 0, 255) },
		{ ";", RGB(255, 0, 255) }
	};

	c.setKeys(x);

	//while (true)
	//{

	//	//GetKeyState();
	//	//cin >> val;
	//		UINT VKeys2[7] = { { 0x3b} };     // W,A,S,D, Left Control, Left Shift, Spacebar
	//		c.ShowKeys(1, 1, VKeys2, RGB(0, 255, 0));
	//}
	//c.ShowColor(1, RGB(0, 255, 0));


	std::cin.ignore();

	return 0;
}
