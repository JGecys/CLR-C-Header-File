// GUIEssentials.h

#pragma once

#include <string>

using namespace System;
using namespace System::Collections;
using namespace std;

namespace GUIEssentials {

	public ref class Settings
	{
	private:
		static String^ _fileName;
		static Hashtable^ _parameters;
		static bool _isLoaded = false;

	public:
		static bool LoadFile(String^ file);
		static bool SaveCurrent();

		static int TryGetInt(String^ key);
		static float TryGetFloat(String^ key);
		static String^ TryGetString(String^ key);

		static void SetValue(String^ key, String^ value);

		static ICollection^ GetKeys();
		static ICollection^ GetValues();
	};

	static String^ stdToString(string s);
	static string StringToStd(String^ s);
}