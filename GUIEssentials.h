#pragma once

#include <string>
#include <msclr/marshal_cppstd.h>

using namespace System;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace std;

namespace GUIEssentials {

	/**
	* @typedef	unsigned int size_type
	*
	* @brief	Dinaminio masyvo dydzio tipas
	*/
	typedef unsigned int size_type;

	template < class Ob >
	class DinaminisMasyvas{
	public:
		/** @brief	Dinaminis masyvas didinamas po Cd elementu. */
		const static size_type Cd = 10;
	private:
		/**
		 * @brief	Randa ojekto indeksa.
		 *
		 * @param	obj	Objektas, kurio indekso iesko.
		 *
		 * @return	Objekto indexas.
		 */
		size_type RastiOjektoIndeksa(const Ob & obj);
	protected:
		/** @brief	Dinaminis masyvas. */
		Ob *Masyvas;
		/** @brief	Dinaminio masyvo dydziai. */
		size_type n, nMax;
	public:

		/**
		 * @brief	Tuscias Konstruktorius.
		 */
		DinaminisMasyvas() : n(0), nMax(Cd), Masyvas(NULL){
			Masyvas = new Ob[nMax];
		}

		/**
		 * @fn	DinaminisMasyvas::DinaminisMasyvas(Ob *O, size_type n);
		 *
		 * @brief	Konstruktorius.
		 *
		 * @param [in,out]	O	Jei ne NULL, sukuria Objekta su siuo dinaminiu masyvu.
		 * @param	n		 	Dinaminio masyvo dydis.
		 */

		DinaminisMasyvas(Ob *O, size_type n) : n(n), nMax(n){
			Masyvas = O;
		}

		/**
		 * @brief	Kopijavimo konstruktorius.
		 *
		 * @param	other	Objektas, kuri kopijuoja.
		 */

		DinaminisMasyvas(const DinaminisMasyvas & other){
			n = other.n;
			nMax = other.nMax;
			Masyvas = new Ob[nMax];
			for (size_type i = 0; i < n; i++){
				Masyvas[i] = other.Masyvas[i];
			}
		}

		/**
		 * @brief	Destruktorius.
		 */

		~DinaminisMasyvas(){
			Isvalyti();
		}

		/**
		 * @brief	Atlaisvina dinaminio masyvo atminti.
		 */
		void Isvalyti(){
			n = nMax = 0;
			if (Masyvas)
				delete[] Masyvas;
			Masyvas = NULL;
		}
		/**
		 * @brief	Padidina/sumazina dinamini masyva.
		 *
		 * @param	dydis	Dinaminio masyvo dydis.
		 */
		void KeistiDydi(size_type dydis){
			if (dydis > nMax){
				Ob * naujasMasyvas = new Ob[dydis];
				for (size_type i = 0; i < n; i++){
					naujasMasyvas[i] = Masyvas[i];
				}
				delete[] Masyvas;
				Masyvas = naujasMasyvas;
			}
			else{
				Ob * naujasMasyvas = new Ob[dydis];
				for (size_type i = 0; i < dydis; i++){
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

		/**
		 * @brief	Grazina rodykle i pirma masyvo elementa.
		 *
		 * @return	null jei tuscia, kitu atveju pirmas masyvo objektas.
		 */
		Ob * Pradzia(){
			if (n == 0){
				return NULL;
			}
			Ob * rodykle;
			rodykle = &Masyvas[0];
			return rodykle;
		}
		/**
		 * @brief	Grazina rodykle i paskutini masyvo elementa.
		 *
		 * @return	null jei tuscia, kitu atveju paskutinis masyvo objektas.
		 */
		Ob * Pabaiga(){
			if (n == 0){
				return NULL;
			}
			Ob * rodykle;
			rodykle = &Masyvas[n - 1];
			return rodykle;
		}
		/**
		 * @return	Dinaminio masyvo dydi..
		 */
		size_type ImtiN() const{
			return n;
		}

		/**
		 * @brief	Grazina i-taji elementa;
		 *
		 * @param	i	Elemento indeksas.
		 *
		 * @return	i-taji elementa.
		 */
		Ob Imti(size_type i) const{
			return Masyvas[i];
		}

		/**
		 * @brief	Prideda nauja objekta
		 *
		 * @param	obj	Objektas, kuri ideda.
		 */
		void Deti(Ob obj){
			if (n == nMax) KeistiDydi(nMax + Cd);
			Masyvas[n++] = obj;
		}

		/**
		 * @brief	Iterptia objekta i dinamini masyva.
		 *
		 * @param	i  	I kuria vieta iterpiamos objektas.
		 * @param	obj	Iterpiamas objektas.
		 */
		void Iterpti(size_type i, Ob obj){
			if (n == nMax) KeistiDydi(nMax + Cd);
			if (n == 0) return;
			for (size_type j = n; j >= i; j--){
				Masyvas[j + 1] = Masyvas[j];
			}
			Masyvas[i] = obj;
		}

		/**
		 * @brief	Istrina objekta i pozicijoje
		 *
		 * @param	i	Objekto pozicija
		 */
		void Istrynti(size_type i){
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

		/**\
		 * @brief	Istrina objekta
		 *
		 * @param	obj Objektas.
		 */
		void Istrynti(Ob obj){
			size_type i = RastiOjektoIndeksa(obj);
			if (i > -1)
				Istrynti(i);
		}

		/**
		 * @brief	Masyvo operatorius
		 *
		 * @param	i	Indeksas
		 *
		 * @return	The indexed value.
		 */
		Ob & operator [] (const size_type & i){
			return Masyvas[i];
		}

		/**
		 * @brief	Priskyrimo operatorius
		 *
		 * @param	other	Kitas objektas.
		 *
		 * @return	Objekto kopija
		 */
		DinaminisMasyvas<Ob> & operator = (const DinaminisMasyvas<Ob> & other){
			Isvalyti();
			n = other.n;
			nMax = other.nMax;
			Masyvas = new Ob[nMax];
			for (size_type i = 0; i < n; i++){
				Masyvas[i] = other.Masyvas[i];
			}
			return *this;
		}

		/**
		 * @brief	Sujungia 2  to pacio tipo dinaminius masyvus
		 *
		 * @param	other	Kitas dinaminis masyvas
		 *
		 * @return	Sujungtas masyvas.
		 */
		DinaminisMasyvas<Ob> operator + (const DinaminisMasyvas<Ob> & other){
			size_type Dydis = nMax + other.nMax
				Ob* naujas = new Ob[Dydis];
			for (size_type i = 0; i < n; i++){
				naujas[i] = Masyvas[i];
			}

			for (size_type i = 0; i < other.n; i++){
				naujas[n + i] = other.Masyvas[i];
			}

			DinaminisMasyvas<Ob> Mas(naujas, Dydis);
			return Mas;
		}
	};

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