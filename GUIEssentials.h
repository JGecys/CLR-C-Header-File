#pragma once

#include <string>
#include <msclr/marshal_cppstd.h>

using namespace System;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace std;

namespace GUIEssentials {

	template<class Object>
	public class DinaminisMasyvas{
	public:
		/**
		 * @typedef	unsigned int size_type
		 *
		 * @brief	Dinaminio masyvo dydzio tipas
		 */
		typedef unsigned int size_type;
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
		size_type RastiOjektoIndeksa(const Object & obj);
	protected:
		/** @brief	Dinaminis masyvas. */
		Object *Masyvas;
		/** @brief	Dinaminio masyvo dydziai. */
		size_type n, nMax;
	public:

		/**
		 * @brief	Tuscias Konstruktorius.
		 */
		DinaminisMasyvas();

		/**
		 * @fn	DinaminisMasyvas::DinaminisMasyvas(Object *O, size_type n);
		 *
		 * @brief	Konstruktorius.
		 *
		 * @param [in,out]	O	Jei ne NULL, sukuria Objekta su siuo dinaminiu masyvu.
		 * @param	n		 	Dinaminio masyvo dydis.
		 */

		DinaminisMasyvas(Object *O, size_type n);

		/**
		 * @brief	Kopijavimo konstruktorius.
		 *
		 * @param	other	Objektas, kuri kopijuoja.
		 */

		DinaminisMasyvas(const DinaminisMasyvas & other);

		/**
		 * @brief	Destruktorius.
		 */

		~DinaminisMasyvas();

		/**
		 * @brief	Atlaisvina dinaminio masyvo atminti.
		 */
		void Isvalyti();
		/**
		 * @brief	Padidina/sumazina dinamini masyva.
		 *
		 * @param	dydis	Dinaminio masyvo dydis.
		 */
		void KeistiDydi(size_type dydis);

		/**
		 * @brief	Grazina rodykle i pirma masyvo elementa.
		 *
		 * @return	null jei tuscia, kitu atveju pirmas masyvo objektas.
		 */
		Object * Pradzia();
		/**
		 * @brief	Grazina rodykle i paskutini masyvo elementa.
		 *
		 * @return	null jei tuscia, kitu atveju paskutinis masyvo objektas.
		 */
		Object * Pabaiga();

		/**
		 * @return	Dinaminio masyvo dydi..
		 */
		size_type ImtiN() const;

		/**
		 * @brief	Grazina i-taji elementa;
		 *
		 * @param	i	Elemento indeksas.
		 *
		 * @return	i-taji elementa.
		 */

		Object Imti(size_type i) const;

		/**
		 * @brief	Prideda nauja objekta
		 *
		 * @param	obj	Objektas, kuri ideda.
		 */

		void Deti(Object obj);

		/**
		 * @brief	Iterptia objekta i dinamini masyva.
		 *
		 * @param	i  	I kuria vieta iterpiamos objektas.
		 * @param	obj	Iterpiamas objektas.
		 */

		void Iterpti(size_type i, Object obj);

		/**
		 * @brief	Istrina objekta i pozicijoje
		 *
		 * @param	i	Objekto pozicija
		 */

		void Istrynti(size_type i);

		/**\
		 * @brief	Istrina objekta
		 *
		 * @param	obj Objektas.
		 */

		void Istrynti(Object obj);

		/**
		 * @brief	Masyvo operatorius
		 *
		 * @param	i	Indeksas
		 *
		 * @return	The indexed value.
		 */

		Object & operator [] (const size_type & i);

		/**
		 * @brief	Priskyrimo operatorius
		 *
		 * @param	other	Kitas objektas.
		 *
		 * @return	Objekto kopija
		 */

		DinaminisMasyvas<Object> & operator = (const DinaminisMasyvas<Object> & other);

		/**
		 * @brief	Sujungia 2  to pacio tipo dinaminius masyvus
		 *
		 * @param	other	Kitas dinaminis masyvas
		 *
		 * @return	Sujungtas masyvas.
		 */

		DinaminisMasyvas operator + (const DinaminisMasyvas<Object> & other);
	}

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