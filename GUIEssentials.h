#pragma once

#include <string>
#include <msclr/marshal_cppstd.h>

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
		static bool HasKey(String^ key);

		static ICollection^ GetKeys();
		static ICollection^ GetValues();

		static bool isSaved(){ return _isSaved; }
	};


	public ref class MessageShow{
	public:
		/** Shows generalMessage*/
		static DialogResult Show(String^ Msg,
			String^ Title,
			MessageBoxButtons buttons,
			MessageBoxIcon icon);

		static DialogResult Show(String^ Msg);

		static DialogResult Show(String^ Msg,
			String^ Title);

		static DialogResult Show(String^ Msg,
			String^ Title,
			MessageBoxButtons buttons);
	};

	static String^ stdToString(string s){
		return msclr::interop::marshal_as< String^ >(s);
	}
	static string StringToStd(String^ s){
		return msclr::interop::marshal_as< string >(s);
	}
}