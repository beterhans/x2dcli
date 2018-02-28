// X2DCLI.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <locale.h>

#include <windows.h>
#include <conio.h> 

#include <public.h>
#include <vjoyinterface.h>
#pragma comment(lib, "vJoyInterface.lib") 

#include <Xinput.h>
#pragma comment(lib, "XInput.lib") 

using namespace std;



int main()
{
	//Local
	setlocale(LC_ALL, "en_US.UTF-8");

	// Pre check
#ifdef __APPLE__ && __MACH__
	cout << "This is a Mac." << endl;
	string st_cmd_clear = "clear";
#endif

#ifdef _WIN32 || _WIN16 || MSDOS || __DOS__
	//system("chcp 65001");
	cout << "This is a Windows PC." << endl;
	string st_cmd_clear = "cls";
#endif

#ifdef __linux__
	cout << "This is a Linux Box." << endl;
	string st_cmd_clear = "clear";
#endif

//Parameters
	//cout << "argc = " << argc << endl;// 1 is no Parameter 2 is 1 Parameter
	//cout << "argv[0] = " << argv[0] << endl; // this is the command itself
	//cout << "argv[1] = " << argv[1] << endl; // this is the first parameter.

	int runmode = 0;// 0 is normal 1 is press left 2 is press right.
	cout << "X2DCLI aka. XInput to DirectInput CLI version\nby Beterhans\nbeter_hans@hotmail.com\nVersion 1.01\n\n";

	cout << "\nTo Run the programe -> type 0 or\njust Auto Press Left Trigger -> type 1 or\njust Auto Press Right Trigger -> type 2\n\n";
	cin >> runmode;
	cout << "\nYou choosed runmode " << runmode << endl;

	if (runmode == 0 || runmode == 1 || runmode == 2)
	{
		cout << "Run Mode " << runmode << endl;
	}
	else
	{
		cout << "\nWrong argument! only use 0 1 or 2\n";
		return(-1);
	};

	//Vjoy ---------------------------------------------------
	// Test vjoy installed

	if (!vJoyEnabled())
	{
		cout << "Failed Getting vJoy attributes.\n";
		return -2;
	}
	else
	{
		cout << "\nvJoy is installed\n";
	};

	// Test selected Device
	int DevID;
	cout << "Input the vJoy device you want to use?\n";
	cin >> DevID;


	VjdStat status = GetVJDStatus(DevID);
	switch (status)
	{
	case VJD_STAT_OWN:
		cout << DevID << " vJoy device is already owned by this feeder\n";
		break;
	case VJD_STAT_FREE:
		cout << DevID << " vJoy device is free\n";
		break;
	case VJD_STAT_BUSY:
		cout << DevID << " vJoy device is already owned by another feeder\nCannot continue\n";
		return -3;
	case VJD_STAT_MISS:
		cout << DevID << " vJoy device is not installed or disabled\nCannot continue\n";
		return -4;
	default:
		cout << DevID << "vJoy device general error\nCannot continue\n";
		return -1;
	};

	// Check capability of the Device
	cout << "vJoy " << DevID << " Have " << GetVJDAxisExist(DevID, HID_USAGE_SL0) << " Slide 0\n";
	cout << "vJoy " << DevID << " Have " << GetVJDAxisExist(DevID, HID_USAGE_SL1) << " Slide 1\n";

	if (GetVJDAxisExist(DevID, HID_USAGE_SL0) && GetVJDAxisExist(DevID, HID_USAGE_SL1))
	{
		cout << "You have two sliders in vjoy No." << DevID << endl;
	}
	else
	{
		cout << "You Don't have two sliders in vJoy No." << DevID << endl;
		return -1;
	};
	
	//Acquire the device
	if ((status == VJD_STAT_OWN) || ((status == VJD_STAT_FREE) && (!AcquireVJD(DevID))))
	{
		cout << "Failed to acquire vJoy device No." << DevID << endl;
		return -1;
	}
	else
	{
		cout << "Acquired: vJoy device No." << DevID << endl;
	}

	// Change vJoy value
	cout << "updating vJoy No." << DevID << endl;
	ResetVJD(DevID);

	// Getting Value from Xinput device
	long X_L_Trigger;
	long X_R_Trigger;
	long i = 0;


	//End of vJoy init ----------------------------------------------------

	// Auto move triggers
	if (runmode == 1)
	{
		cout << "\n\nStart to Press Left Trigger.\nPress Any key to exit\n\n";
		while (_kbhit() == 0)
		{
			X_L_Trigger = 1 + i;
			SetAxis(X_L_Trigger, DevID, HID_USAGE_SL0);
			if(i != 0)
			{
				i = 0;
			}
			else 
			{
				i = 32767;
			};
			Sleep(250);
		}

		cout << "\nYou Pressed Key: " << _getch() << endl;
		return(0);
	};

	if (runmode == 2)
	{
		cout << "\n\nStart to Press Right Trigger.\nPress Any key to exit\n\n";
		while (_kbhit() == 0)
		{
			X_R_Trigger = 1 + i;
			SetAxis(X_R_Trigger, DevID, HID_USAGE_SL1);
			if (i != 0)
			{
				i = 0;
			}
			else
			{
				i = 32767;
			};
			Sleep(250);
		}

		cout << "\nYou Pressed Key: " << _getch() << endl;
		return(0);
	};


	// Xinput ---------------------------------------------------------------------
	if(runmode == 0)//No Argument is been entered.
	{
	cout << "\n\n\n";
	cout << "Which XInput Device You are using?\nXbox360 or XboxOne Controller have a Ring of Green light\nUpper Left is 1 Upper Right is 2 Down and etc..\ntype from 1 to 4\n" << endl;
	
	int GamePad_change_buff;
	int XDevID;
	cin >> XDevID;
	XDevID = XDevID - 1;

	DWORD dwResult;
	XINPUT_STATE xinp_state; //use xinp_state as an instance to call XINPUT_STATE structure
	ZeroMemory(&xinp_state, sizeof(XINPUT_STATE));

	// Check Xinput device
	dwResult = XInputGetState(XDevID, &xinp_state);
		if (dwResult == ERROR_SUCCESS)//ERROR_SUCCESS is 0 you can also use 0 instead the ERROR_SUCCESS
		{
			cout << "Controller " << XDevID + 1 << " is connected \n";
			cout << "Error code of State is " << XInputGetState(XDevID, &xinp_state) << endl;
			cout << "XDevID(+1) = " << XDevID + 1 << " state address is " << &xinp_state << endl;
			cout << "xinp_state.Gamepad.bLeftTrigger  = " << (long)xinp_state.Gamepad.bLeftTrigger << endl;//it's a byte need convert to digital
			cout << "xinp_state.Gamepad.bRightTrigger = " << (long)xinp_state.Gamepad.bRightTrigger << endl;//it's a byte need convert to digital
			cout << "dwPacketNumber = " << xinp_state.dwPacketNumber << endl;//If the number did not change means nobody touch the controller.
			cout << "xinp_state.Gamepad.wButtons = " << xinp_state.Gamepad.wButtons << endl << endl;
			GamePad_change_buff = xinp_state.Gamepad.wButtons;
		}
		else
		{
			cout << "Controller " << XDevID + 1 << " is NOT connected \n";
			return(-1);
		};


	// Loop to feed
		cout << "\n\nStart to Transfer data to vJoy\nPress Any key to exit\n\n";
		while ( _kbhit() == 0 )
		{
			dwResult = XInputGetState(XDevID, &xinp_state);
			X_L_Trigger = ((long)xinp_state.Gamepad.bLeftTrigger + 1) * 128;
			X_R_Trigger = ((long)xinp_state.Gamepad.bRightTrigger + 1) * 128;
			SetAxis(X_L_Trigger, DevID, HID_USAGE_SL0);
			SetAxis(X_R_Trigger, DevID, HID_USAGE_SL1);				
			//cout << "X_L_Trigger = " << X_L_Trigger << endl;
			//cout << "X_R_Trigger = " << X_R_Trigger << endl;
			Sleep(8);
		}

		cout << "\nYou Pressed Key: " << _getch() << endl;
	};

	// End actions
	RelinquishVJD(DevID);
	cout << "Released vJoy Device No." << DevID << endl;

    return 0;
}

