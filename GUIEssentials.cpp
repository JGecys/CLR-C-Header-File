#include <fstream>

#include "GUIEssentials.h"

using namespace GUIEssentials;
using namespace std;

bool Settings::LoadFile(String^ file){
	_isSaved = true;
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

		if (_parameters->ContainsKey(Key)){
			_parameters[Key] = Value;
		}
		else{
			_parameters->Add(Key, Value);
		}

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

	_isSaved = true;

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
	_isSaved = false;
	if (_parameters->ContainsKey(key)){
		_parameters[key] = value;
	}
	else{
		_parameters->Add(key, value);
	}
}

bool Settings::HasKey(String^ key){
	return _parameters->ContainsKey(key);
}



ICollection^ Settings::GetKeys(){
	return _parameters->Keys;
}
ICollection^ Settings::GetValues(){
	return _parameters->Values;
}


DialogResult MessageShow::ShowOk(String^ Msg, String^ Title){
	return MessageBox::Show(Title, Msg, MessageBoxButtons::OK);
}


DialogResult MessageShow::ShowYesNo(String^ Msg, String^ Title){
	return MessageBox::Show(Title, Msg, MessageBoxButtons::YesNo);
}

DialogResult MessageShow::ShowYesNoCancel(String^ Msg, String^ Title){
	return MessageBox::Show(Title, Msg, MessageBoxButtons::YesNoCancel);
}