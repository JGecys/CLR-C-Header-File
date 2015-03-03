#include <fstream>

#include "GUIEssentials.h"

using namespace GUIEssentials;
using namespace System;
using namespace std;

#pragma region Settings

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

#pragma endregion

#pragma region MessageShow
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
#pragma endregion

#pragma region DinaminisMasyvas

GUIEssentials::DinaminisMasyvas::DinaminisMasyvas() : n(0), nMax(Cd), Matrica(NULL){
	Matrica = new Object[nMax];
}
GUIEssentials::DinaminisMasyvas::DinaminisMasyvas(Object * O, size_type n), n(n), nMax(n){
	Matrica = O;
}
GUIEssentials::DinaminisMasyvas::DinaminisMasyvas(const DinaminisMasyvas & other){
	n = other.n;
	nMax = other.nMax;
	Masyvas = new Object[nMax];
	for (size_type i = 0; i < n; i++){
		Masyvas[i] = other.Masyvas[i];
	}
}
GUIEssentials::DinaminisMasyvas::~DinaminisMasyvas(){
	Isvalyti();
}

template<class Object>
void GUIEssentials::DinaminisMasyvas<Object>::Isvalyti(){
	n = nMax = 0;
	if (Masyvas)
		delete[] Masyvas;
	Masyvas = NULL;
}


template<class Object>
void GUIEssentials::DinaminisMasyvas<Object>::KeistiDydi(size_type dydis){
	if (dydis > nMax){
		Object * naujasMasyvas = new Object[dydis];
		for (size_tyoe i = 0; i < n; i++){
			naujasMasyvas[i] = Masyvas[i];
		}
		delete[] Masyvas;
		Masyvas = naujasMasyvas;
	}
	else{
		Object * naujasMasyvas = new Object[dydis];
		for (size_tyoe i = 0; i < dydis; i++){
			naujasMasyvas[i] = Masyvas[i];
		}
		delete[] Masyvas;
		Masyvas = naujasMasyvas;
		if (n > dydis){
			n = dydis;
		}
	}
	nMax = dydis;
}


template<class Object>
Object * GUIEssentials::DinaminisMasyvas<Object>::Pradzia(){
	if (n == 0){
		return NULL;
	}
	Object * rodykle;
	rodykle = &Masyvas[0];
	return rodykle;
}

template<class Object>
Object * GUIEssentials::DinaminisMasyvas<Object>::Pabaiga(){
	if (n == 0){
		return NULL;
	}
	Object * rodykle;
	rodykle = &Masyvas[n - 1];
	return rodykle;
}

template<class Object>
size_type GUIEssentials::DinaminisMasyvas<Object>::ImtiN() const{
	return n;
}


template<class Object>
Object GUIEssentials::DinaminisMasyvas<Object>::Imti(size_type i) const{
	return Masyvas[i];
}

template<class Object>
void GUIEssentials::DinaminisMasyvas<Object>::Deti(Object obj){
	if (n == nMax) KeistiDydi(nMax + Cd);
	Masyvas[n++] = obj;
}

template<class Object>
void GUIEssentials::DinaminisMasyvas<Object>::Iterpti(size_type i, Object obj){
	if (n == nMax) KeistiDydi(nMax + Cd);
	if (n == 0) return;
	for (size_type j = n; j >= i; j--){
		Masyvas[j + 1] = Masyvas[j];
	}
	Masyvas[i] = obj;
}

template<class Object>
void GUIEssentials::DinaminisMasyvas<Object>::Istrynti(size_type i){
	if (n == 1){
		Isvalyti();
		return;
	}
	if (n - nMax < Cd) KeistiDydi(nMax - Cd);
	if (n == 0) return;
	n--;
	for (size_type j = i; j < n; j++){
		Masyvas[j] = Masyvas[j + 1];
	}
}

template<class Object>
void GUIEssentials::DinaminisMasyvas<Object>::Istrynti(Object obj){
	size_type i = RastiOjektoIndeksa(obj);
	if ( i > -1 )
		Istrynti(i);
}

template<class Object>
Object & GUIEssentials::DinaminisMasyvas<Object>::operator [] (const size_type & i){
	return Masyvas[i];
}

template<class Object>
DinaminisMasyvas<Object> & GUIEssentials::DinaminisMasyvas<Object>::operator = (const DinaminisMasyvas<Object> & other){
	Isvalyti();
	n = other.n;
	nMax = other.nMax;
	Masyvas = new Object[nMax];
	for (size_type i = 0; i < n; i++){
		Masyvas[i] = other.Masyvas[i];
	}
	return *this;
}

template<class Object>
DinaminisMasyvas GUIEssentials::DinaminisMasyvas<Object>::operator + (const DinaminisMasyvas<Object> & other){
	size_type Dydis = nMax + other.nMax
	Object* naujas = new Object[Dydis];
	for (size_type i = 0; i < n; i++){
		naujas[i] = Masyvas[i];
	}

	for (size_type i = 0; i < other.n; i++){
		naujas[n + i] = other.Masyvas[i];
	}

	DinaminisMasyvas<Object> Mas(naujas, Dydis);
	return Mas;
}


#pragma endregion