#ifndef __BACKTRACKFLEX_H
#define __BACKTRACKFLEX_H
#include <iostream>
#include <fstream>
#include <stdio.h>
using std::ostream;
//using std::cerr;
#include <vector>
using std::vector;
//De klasse Backtrackflex zoekt een vector van knopen die een oplossing biedt voor een gegeven
//probleem. Wat er met deze oplossing moet gedaan worden staat in de functie verwerk.
//Backtrackflex kan ingesteld worden zodat hij juist 1 oplossing zoekt, of zodat
//hij alle oplossingen zoekt.
//
//Ze is flexibeler dan backtrack, omdat het toevoegen/wegnemen van elementen
//aan/van deeloplossing kan overschreven worden.

template <class knoop>
class Backtrackflex{
public:
    Backtrackflex();

    //als opgeroepen met zoekalle=true worden alle oplossingen gezocht
    void losop(bool zoekalle);                                                                 
protected:
    void losop(bool& gedaan,bool zoekalle);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                         

    //de volgende functies moeten misschien aangepast voor specifieke problemen.
    virtual void voegtoeaandeeloplossing(knoop& element);
    virtual void verwijderuitdeeloplossing();                                              
    
/**********************************************************************

De onderstaande functies moeten ingevuld worden voor specifieke problemen.

   
***************************************************************************/
//controle geeft true terug als de vector deeloplossing een oplossing bevat.
    virtual bool controle()=0;
//verwerk: afhandeling van een oplossing die opgeslagen is in deeloplossing.
    virtual void verwerk()=0;
//geefverdere: geef verzameling verderzettingen van de deeloplossing.
    vector<knoop>& geefverdere()=0;
//Opgelet: deeloplossing is een vector van *pointers* naar knopen; de knopen zelf zitten
// in de vector mogelijkheid die lokaal gedeclareerd wordt in losop
    vector<knoop*> deeloplossing;
};


template <class knoop>
Backtrackflex<knoop>::Backtrackflex(){
        deeloplossing.clear();
}

template <class knoop>
void Backtrackflex<knoop>::losop(bool zoekalle){
    bool gedaan=false;
    losop(gedaan,zoekalle);
}

template <class knoop>
void Backtrackflex<knoop>::losop(bool& gedaan,bool zoekalle){
    if (controle()){//oplossing gevonden
        verwerk();
        if (!zoekalle)
            gedaan=true;
    }
//bij sommige problemen kan een oplossing nog verlengd worden tot een langere oplossing
//daarom moet het volgend stuk code ook worden uitgevoerd als we een oplossing hebben.
   if (!gedaan){
//noot: het werken met referenties naar elementen van een vector is alleen veilig als de
//vector onveranderlijk is.
        const vector<knoop> mogelijkheid(geefverdere());
        int i=0;
        while (i<mogelijkheid.size() && !gedaan){
            voegtoeaandeeloplossing(mogelijkheid[i]);
            losop(gedaan,zoekalle);
            verwijderuitdeeloplossing();
            i++;
        }
    }
}

template <class knoop>
void Backtrackflex<knoop>::voegtoeaandeeloplossing(knoop& element){
    deeloplossing.push_back(&element);
}

template <class knoop>
void Backtrackflex<knoop>::verwijderuitdeeloplossing(){
    deeloplossing.resize(deeloplossing.size()-1);
}
#endif
