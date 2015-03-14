//C++11-compatibele lijst. Ontbrekende elementen: move en copy, iterator
#ifndef __LIJST11_H
#define __LIJST11_H
//
// speciale code voor debuggen
//
#define DEBUG
//
//
//speciale code voor iteratoren
//#define ITERATOR




#include <iostream>
#include <memory>
#include <algorithm>
using namespace std;
using std::endl;
using std::ostream;

template<class T>
class Lijstknoop;
template<class T>
class Lijst;

template<class T>
using Lijstknoopptr=std::unique_ptr<Lijstknoop<T> >;
template<class T>
ostream& operator<<(ostream& os, const Lijst<T>& l);

template<class T>
class Lijst : private Lijstknoopptr < T > {
public:
	//toekenning, constructoren
	//overname constructoren van unique_ptr
	using Lijstknoopptr<T>::Lijstknoopptr;

	//default constructor
	Lijst() :std::unique_ptr<Lijstknoop<T>>(){}
	//constructor zoals je kan doen bij unique_ptr
	Lijst(Lijstknoop<T>* obj) :Lijstknoopptr<T>(obj){}
	//move constructor
	Lijst(Lijst&& l){
		this->swap(l);
		l.reset();
	}
	//shallow copy constructor -> kan niet bij unique pointers
	/*Lijst(const Lijst& l){

	}*/
	//deepcopy constructor
	Lijst(const Lijst<T>& l)
	{
		if (l){
			Lijst<T>* nieuw = new Lijst<T>();
			Lijst<T>* lijstloper = nieuw;
			const Lijst<T>* loper = &l;
			while (*loper){ //loop lijst af, maak nieuwe lijstknoop en voeg toe
				Lijstknoop<T>* nieuweknoop = new Lijstknoop<T>(loper->get()->sl);
				Lijstknoopptr<T> ptr(nieuweknoop);
				(*lijstloper) = std::move(ptr);
				lijstloper = &(lijstloper->get()->volgend);
				loper = &(loper->get()->volgend);
			}

			*this = std::move(*nieuw);
		}

	}

	//Lijst& operator=(const Lijst&) (deepcopy)
	Lijst& operator=(const Lijst<T>& l){
		if (this != &l){
			Lijst<T>* nieuwelijst = new Lijst<T>(l);

			*this = std::move(*nieuwelijst);
		}
		return *this;
	}

	Lijst& operator=(const Lijstknoopptr<T>& l){
		if (this != &l){
			Lijstknoop<T>* nieuweknoop = new Lijstknoop<T>((l.get()->sl));
			Lijstknoopptr<T> t(nieuweknoop);
			*this = std::move(t);
		}
		return *this;
	}
	//Lijst& operator=(Lijst&& l) (move)
	Lijst& operator=(Lijst<T>&& l){
		if (this != &l){
			//switch resources from l to this
			this->swap(l);
			//remove resources from l
			l.reset();
		}
		return *this;
	}

	Lijst& operator=(Lijstknoopptr<T>&& l){
		if (this != &l){
			//switch resources from l to this
			this->swap(l);
			//remove resources from l
			l.reset();
		}
		return *this;
	}

	// te doen....

	//operaties
	//duplicaten zijn toegelaten.
public: void voegToe(const T& getal);
		//geefaantal geeft het aantal keer dat de sleutel voorkomt.
		//gebruikt de zoekfunctie om door de lijst te lopen!
		//zonder argument: geef lengte lijst
public: int geefaantal(const T&) const;
public: int geefaantal() const;
		//verwijder verwijdert slechts het eerste exemplaar met de gegeven
		//T, en geeft geen fout als de T niet gevonden wordt.
		//gebruik de zoekfunctie om door de lijst te lopen!
public: void verwijder(const T&);
		//verwijder eerste knoop.
public: void verwijderEerste();
public: void insertionsort();
		// zoek geeft een pointer naar de Lijst die de sleutelwaarde bevat,
		// en geeft een pointer naar de lege lijst op het einde als de sleutel niet
		// voorkomt.
protected: const Lijst* zoek(const T&) const;
protected: Lijst* zoek(const T&);
		   //preconditie zoekgesorteerd: lijst is gesorteerd
		   //teruggeefwaarde: wijst naar Lijst waar sl staat/zou moeten staan.
protected: Lijst<T>* zoekGesorteerd(const T& sl);
		   //public: void insertionsort();


		   //uitschrijven: voor elke knoop de T-waarde, gescheiden door komma's
		   friend ostream& operator<< <>(ostream& os, const Lijst& l);
public: void schrijf(ostream & os) const;
		//iterator; gaat ervan uit dat alles const is
public: class iterator{
public:
	iterator(Lijstknoop<T>* l = 0);
	const T& operator*() const;
	const iterator& operator++();
	bool operator!=(const iterator& i);
};
		iterator begin() const;
		iterator end() const;

};


template<class T>
class Lijstknoop{
	friend class Lijst < T > ;
public:
	Lijst<T> volgend;
	Lijstknoop(const T&);
	~Lijstknoop();
protected:
	T sl;
#ifdef DEBUG
public:
	static bool controle(int gemaakt, int verwijderd);
protected:
	static int aantalGemaakt;
	static int aantalVerwijderd;
#endif
};

template<class T>
int Lijstknoop<T>::aantalGemaakt = 0;
template<class T>
int Lijstknoop<T>::aantalVerwijderd = 0;

template<class T>
Lijstknoop<T>::Lijstknoop(const T& _sl) :sl(_sl){
	//    std::cerr<<"Knoop met sleutel "<<sl<<" wordt gemaakt\n";
	aantalGemaakt++;
}

template<class T>
Lijstknoop<T>::~Lijstknoop(){
	//    std::cerr<<"Knoop met sleutel "<<sl<<" wordt verwijderd\n";
	aantalVerwijderd++;
}
#ifdef DEBUG
template<class T>
bool Lijstknoop<T>::controle(int gemaakt, int verwijderd){
	if (aantalGemaakt == gemaakt && aantalVerwijderd == verwijderd)
		return true;
	else{
		std::cerr << "Fout bij controle:\n";
		std::cerr << "Aantal gemaakte knopen   : " << aantalGemaakt << " (moet zijn: " << gemaakt << ")\n";
		std::cerr << "Aantal verwijderde knopen: " << aantalVerwijderd << " (moet zijn: " << verwijderd << ")\n";
		throw "Mislukte controle";
	};

};
#endif

template<class T>
ostream& operator<<(ostream& os, const Lijst<T>& l){
#ifdef ITERATOR
	for (auto sleutel : l)
		os << sleutel << ", ";
#else
	if (l.get()){
		os << l.get()->sl << ", ";
		os << l.get()->volgend;
	}
#endif
	return os;
}

template<class T>
void Lijst<T>::schrijf(ostream & os) const{
#ifdef ITERATOR
	if (this->get() != 0){
		os << this->get()->sl;
		std::for_each(++begin(), end(), [&](const T& sl){ os << " . " << sl; });
	}
#else
	Lijstknoop<T>* kn = this->get();
	if (kn != 0){
		os << kn->sl;
		kn = kn->volgend.get();
	};
	while (kn != 0){
		os << " . " << kn->sl;
		kn = kn->volgend.get();
	};
#endif
}

template<class T> 
void Lijst<T>::voegToe(const T& getal){
	//	Lijstknoopptr<T> nieuw(new Lijstknoop<T>(sl));
	//	Lijstknoopptr<T>::swap(nieuw->volgend);
	//	*this = std::move(nieuw);

	Lijstknoop<T>* nieuw = new Lijstknoop<T>(getal);
	Lijstknoopptr<T> verwijzing(nieuw);
	//verwissel de pointer die in de superklasse stond met die in nieuw->volgend 
	//(Lijst is ook een unique_ptr)
	Lijstknoopptr<T>::swap(nieuw->volgend);
	//nieuw->volgend krijgt de waarde waar je superklasse naar wees en superklasse verwijst naar niets meer
	//komt overeen met vooraan iets toevoegen aan gelinkte lijst en pointers verleggen
	//We moeten nog de unique_ptr van de superklasse instellen op het nieuwe object
	*this = std::move(verwijzing);
}

// zoek geeft een pointer naar de Lijst die de sleutelwaarde bevat,
// en geeft een pointer naar de lege lijst op het einde als de sleutel niet
// voorkomt.
template<class T> const Lijst<T>* Lijst<T>::zoek(const T& getal) const{
	const Lijst* ptr = this;
	//get() geeft een pointer terug naar het object waarnaar de unique_ptr wijst
	while (ptr != 0 && ptr->get()->sl != getal){
		ptr = &(ptr->get()->volgend);
	}
	return ptr;
}
template<class T> Lijst<T>* Lijst<T>::zoek(const T& getal){
	Lijst* ptr = this;
	//get() geeft een pointer terug naar het object waarnaar de unique_ptr wijst
	while (*ptr && ptr->get()->sl != getal){
		ptr = &(ptr->get()->volgend);
	}
	return ptr;
}

//geefaantal geeft het aantal keer dat de sleutel voorkomt.
//gebruikt de zoekfunctie om door de lijst te lopen!
//zonder argument: geef lengte lijst
template<class T> int Lijst<T>::geefaantal(const T& getal) const{
	int aantal = 0;
	Lijst* ptr = zoek(getal);
	while (ptr != 0){
		aantal++;
		ptr = ptr->zoek(getal);
	}
	return aantal;
}
template<class T> int Lijst<T>::geefaantal() const{
	int aantal = 0;
	Lijst* ptr = this;
	while (ptr != 0){
		aantal++;
		ptr = &(ptr->get()->volgend);
	}
	return aantal;
}

//verwijder verwijdert slechts het eerste exemplaar met de gegeven
//T, en geeft geen fout als de T niet gevonden wordt.
//gebruik de zoekfunctie om door de lijst te lopen!
template<class T> void Lijst<T>::verwijder(const T& getal){
	Lijst* ptr = zoek(getal);
	if (ptr != 0 && *ptr){
		//gevonden
		//de ptr moet verwijzen naar volgend element
		//stap 1 -> de pointer verplaatsen naar een nieuwe unique_ptr (move)
		//stap 2 -> het object waar je ptr naar verwees deleten (reset)
		//stap 3 -> je pointer laten verwijzen naar de nieuwe unique_ptr (swap)
		//Lijstknoopptr<T> staart(std::move(this->get()->volgend));
		//		this->reset();
		//		Lijstknoopptr<T>::swap(staart);
		Lijst<T> nieuw(move(ptr->get()->volgend));
		ptr->reset();
		ptr->swap(nieuw);
	}
}
//verwijder eerste knoop.
template<class T> void Lijst<T>::verwijderEerste(){
	verwijder(this->get()->sl);
}
template<class T> void Lijst<T>::insertionsort(){

	//2 lijsten, 1 gesorteerd, 1 niet gesorteerd
	Lijst<T> ongesort(std::move(*this));
	while (ongesort){
		//		Lijst *plaats = zoekGesorteerd(ongesorteerd.get()->sl);
		//		Lijstknoopptr<T> dummy = std::move(ongesorteerd);
		//		//vermits ongesorteerd een nullpointer is, is het equivalent van volgende lijnen ongeveer
		//		//ongesorteerd=std::move(dummy.get()->volgend);
		//		//std::swap(*plaats,dummy.get()->volgend);
		//		std::swap(ongesorteerd, dummy.get()->volgend);
		//		dummy.get()->volgend = std::move(*plaats);
		//		*plaats = std::move(dummy);

		Lijst<T>* plaats = this->zoekGesorteerd(ongesort.get()->sl);
		//je kent de plaats
		Lijst<T> element(std::move(ongesort));
		//element bevat nu de ongesorteerde lijst, ongesort verwijst naar niets
		ongesort.swap(element.get()->volgend);
		//ongesort wijst nu naar de volgende in de lijst, element bevat enkel de sleutel met als volgende niets
		//plaats is een pointer naar de lijst waar het element moet komen
		//lijstknoop die plaats beheert moet naar de lijst van het element gaan
		//de plaats moet naar het element wijzen
		element.get()->volgend = std::move(*plaats);
		*plaats = std::move(element);


	}
}

//preconditie zoekgesorteerd: lijst is gesorteerd
//teruggeefwaarde: wijst naar Lijst waar sl staat/zou moeten staan.
template<class T> Lijst<T>* Lijst<T>::zoekGesorteerd(const T& sl){
	//Geeft de pointer naar de lijst terug waarvoor geld dat de lijstknoop zijn sleutel > is dan de gezochte sleutel

	Lijst* ptr = this;
	while (*ptr && ptr->get()->sl < sl){
		ptr = &(ptr->get()->volgend);
	}
	return ptr;
	//Als ptr == 0 dan moet de sleutel helemaal op het einde toegevoegd worden
}

//oplossing:

//
//template<class T>
//const Lijst<T>* Lijst<T>::zoek(const T& sl) const{
//	const Lijst<T>* pl = this;
//	while (*pl && pl->get()->sl != sl)
//		pl = &(pl->get()->volgend);
//	return pl;
//}
//template<class T>
//int Lijst<T>::geefaantal(const T& sl) const{
//	const Lijst<T>* plaats = zoek(sl);
//	//noot: plaats==0 is false zelfs als plaats een nulpointer is
//	if (*plaats)
//		return 1 + plaats->get()->volgend.geefaantal(sl);
//	else
//		return 0;
//};
//
//template<class T>
//int Lijst<T>::geefaantal() const{
//	if (*this)
//		return 1 + this->get()->volgend.geefaantal();
//	else
//		return 0;
//};
//
//template<class T>
//Lijst<T>* Lijst<T>::zoek(const T& sl){
//	Lijst* pl = this;
//	while (*pl && pl->get()->sl != sl)
//		pl = &(pl->get()->volgend);
//	return pl;
//}
//
//template<class T>
//void Lijst<T>::voegToe(const T& sl){
//	Lijstknoopptr<T> nieuw(new Lijstknoop<T>(sl));
//	Lijstknoopptr<T>::swap(nieuw->volgend);
//	*this = std::move(nieuw);
//}
//
//template<class T>
//void Lijst<T>::verwijderEerste(){
//	if (this->get() != 0){
//		Lijstknoopptr<T> staart(std::move(this->get()->volgend));
//		this->reset();
//		Lijstknoopptr<T>::swap(staart);
//	}
//}
//
//template<class T>
//void Lijst<T>::verwijder(const T& sl){
//	zoek(sl)->verwijderEerste();
//}
//
//template<class T>
//Lijst<T>* Lijst<T>::zoekGesorteerd(const T& sl){
//	Lijst* plaats = this;
//	while (*plaats && plaats->get()->sl < sl)
//		plaats = &plaats->get()->volgend;
//	return plaats;
//};
//
//template<class T>
//void Lijst<T>::insertionsort(){
//	Lijstknoopptr<T> ongesorteerd = std::move(*this);
//	while (ongesorteerd){
//		Lijst *plaats = zoekGesorteerd(ongesorteerd.get()->sl);
//		Lijstknoopptr<T> dummy = std::move(ongesorteerd);
//		//vermits ongesorteerd een nullpointer is, is het equivalent van volgende lijnen ongeveer
//		//ongesorteerd=std::move(dummy.get()->volgend);
//		//std::swap(*plaats,dummy.get()->volgend);
//		std::swap(ongesorteerd, dummy.get()->volgend);
//		dummy.get()->volgend = std::move(*plaats);
//		*plaats = std::move(dummy);
//
//	};
//
//
//};
#endif
