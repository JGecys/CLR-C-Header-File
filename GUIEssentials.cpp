#include <fstream>

#include "GUIEssentials.h"

using namespace GUIEssentials;
using namespace System;
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
	try{
		int value = int::Parse((String^)_parameters[key]);
		return value;
	}
	catch (ArgumentNullException^ nll){
		throw nll;
	}
	catch (FormatException^ format){
		throw format;
	}
	catch (OverflowException^ overflow){
		throw overflow;
	}
	return 0;

}
float Settings::TryGetFloat(String^ key){
	try{
		float value = float::Parse((String^)_parameters[key]);
		return value;
	}
	catch (ArgumentNullException^ nll){
		throw nll;
	}
	catch (FormatException^ format){
		throw format;
	}
	catch (OverflowException^ overflow){
		throw overflow;
	}
	return 0;
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


DialogResult MessageShow::Show(String^ Msg,
	String^ Title,
	MessageBoxButtons buttons,
	MessageBoxIcon icon){
	return MessageBox::Show(Msg, Title, buttons, icon);
}

DialogResult MessageShow::Show(String^ Msg){
	return MessageShow::Show(Msg, "Info", MessageBoxButtons::OK, MessageBoxIcon::None);
}

DialogResult MessageShow::Show(String^ Msg,
	String^ Title){
	return MessageShow::Show(Msg, Title, MessageBoxButtons::OK, MessageBoxIcon::None);
}

DialogResult MessageShow::Show(String^ Msg,
	String^ Title,
	MessageBoxButtons buttons){
	return MessageShow::Show(Msg, Title, buttons, MessageBoxIcon::None);
}