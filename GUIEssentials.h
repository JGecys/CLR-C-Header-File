// GUIEssentials.h

#pragma once

#include <string>

using namespace System;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace std;

namespace GUIEssentials {

	public ref class Settings
	{
	private:
		static String^ _fileName;
		static Hashtable^ _parameters;
		static bool _isLoaded = false;
		static bool _isSaved;

	public:
		static bool LoadFile(String^ file);
		static bool SaveCurrent();

		static int TryGetInt(String^ key);
		static float TryGetFloat(String^ key);
		static String^ TryGetString(String^ key);

		static void SetValue(String^ key, String^ value);

		static ICollection^ GetKeys();
		static ICollection^ GetValues();

		static bool isSaved(){ return _isSaved; }
	};


	public ref class MessageShow{
	public:
		/** Shows Message with Single button OK and no callback*/
		static DialogResult ShowOk(String^ Msg, String^ Title);
		/** Shows Message with 2 buttons: Yes/No;*/
		static DialogResult ShowYesNo(String^ Msg, String^ Title);
		/** Shows Message with 3 buttons: Yes/No/Cancel;*/
		static DialogResult ShowYesNoCancel(String^ Msg, String^ Title)
	};

	static String^ stdToString(string s);
	static string StringToStd(String^ s);
}