// This is the main DLL file.

#pragma once

#include <fstream>
#include <msclr/marshal_cppstd.h>

#include "GUIEssentials.h"

using namespace GUIEssentials;
using namespace std;

bool Settings::LoadFile(String^ file){
	_fileName = file;

	ofstream fo(StringToStd(file), fstream::app);
	fo << "";
	fo.close();

	ifstream fi(StringToStd(file));

	if (!fi.is_open())
		return false;

	_parameters = gcnew Hashtable();

	string key, value;
	while (!fi.eof()){
		fi >> key >> value;

		String^ Key = stdToString(key);
		String^ Value = stdToString(value);

		SetValue(Key, Value);

	}

	fi.close();

	_isLoaded = true;
	return true;
}

bool Settings::SaveCurrent()
{
	ofstream fo(StringToStd(_fileName));

	if (!fo.is_open())
		return false;

	

	for each (String^ key in _parameters->Keys){
		if (key != ""){
			auto value = _parameters[key];


			string Key = StringToStd(key);
			string Value = StringToStd((String^)value);

			fo << Key << ' ' << Value << endl;
		}
	}

	fo.close();
	return true;
}


int Settings::TryGetInt(String^ key){
	int value;
	int::TryParse((String^)_parameters[key], value);
	return value;

}
float Settings::TryGetFloat(String^ key){
	float value;
	float::TryParse((String^)_parameters[key], value);
	return value;
}
String^ Settings::TryGetString(String^ key){
	return (String^) _parameters[key];
}



void Settings::SetValue(String^ key, String^ value){
	if (_parameters->ContainsKey(key)){
		_parameters[key] = value;
	}
	else{
		_parameters->Add(key, value);
	}
}



ICollection^ Settings::GetKeys(){
	return _parameters->Keys;
}
ICollection^ Settings::GetValues(){
	return _parameters->Values;
}



static String^ GUIEssentials::stdToString(string s){
	return msclr::interop::marshal_as< String^ >(s);
}

static string GUIEssentials::StringToStd(String^ s){
	return msclr::interop::marshal_as< string >(s);

}