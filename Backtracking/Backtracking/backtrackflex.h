#ifndef __BACKTRACKFLEX_H
#define __BACKTRACKFLEX_H
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <stdio.h>
#include <iostream>
#include <fstream>
using std::ostream;
//using std::cerr;
#include <vector>
using std::vector;
//De klasse Backtrackflex zoekt een vector van knopen die een oplossing biedt voor een gegeven
//probleem. Wat er met deze oplossing moet gedaan worden staat in de functie verwerk.
//Backtrackflex kan ingesteld worden zodat hij juist 1 oplossing zoekt, of zodat
//hij alle oplossingen zoekt.
//
//Hij is flexibeler dan backtrack, omdat het toevoegen/wegnemen van elementen
//aan/van deeloplossing kan overschreven worden.




template <class knoop>
class Backtrackflex{
public:
    Backtrackflex();
    
    //als opgeroepen met zoekalle=true worden alle oplossingen gezocht
    void losOp(bool zoekalle);
protected:
    void losOp(bool& gedaan,bool zoekalle);
    
    //de volgende functies moeten misschien aangepast voor specifieke problemen.
    virtual void voegToeAanDeeloplossing(knoop& element);
    virtual void verwijderUitDeeloplossing();
    
    /**********************************************************************
     
     De onderstaande functies moeten ingevuld worden voor specifieke problemen.
     
     
     ***************************************************************************/
    vector<knoop*> deeloplossing;
   
    
    //controle geeft true terug als de vector deeloplossing een oplossing bevat.
    virtual bool controle(){
        
        for(int z=0;z<10;++z){
        vector<int> t(5);
        for(int i=0;i<t.size();++i){
            t[i] = rand() % 100;
        }
        
        for(int i=0;i<deeloplossing.size();++i){
            
            if(t[deeloplossing[i]->first] > t[deeloplossing[i]->second]){
            
            int temp = t[deeloplossing[i]->first];
            t[deeloplossing[i]->first] = t[deeloplossing[i]->second];
            t[deeloplossing[i]->second] = temp;
                
            }
        }
        
        for(int i=0;i<t.size()-1;++i){
            if (t[i]>t[i+1]) return false;
        }
        }
        return true;
    
    
    }
    //verwerk: afhandeling van een oplossing die opgeslagen is in deeloplossing.
    virtual void verwerk(){
        for(int i=0;i<deeloplossing.size();++i){
            
            std::cout << "als " << deeloplossing[i]->first << " > " << deeloplossing[i]->second << " , dan swappen"<<std::endl;
        }
    
    }
    //geefVerdere: geef verzameling verderzettingen van de deeloplossing.
    vector<knoop>& geefVerdere(){
        vector<vector<bool>> swaps(5, vector<bool>(5));
        vector<knoop> *verder = new vector<knoop>;
        for(int i=0;i<deeloplossing.size();++i){
            
            swaps[deeloplossing[i]->first][deeloplossing[i]->second]=true;
        }
        
        for(int j=1;j<5;++j){
            for(int i=0;i<j;++i){
                if(!swaps[i][j]){
                    knoop* k = new knoop;
                    k->first = i;
                    k->second = j;
                    (*verder).push_back( *k);
                }
            }
        }
        return *verder;
        
        
    
    }
    //Opgelet: deeloplossing is een vector van *pointers* naar knopen; de knopen zelf zitten
    // in de vector mogelijkheid die lokaal gedeclareerd wordt in losOp
    
};


template <class knoop>
Backtrackflex<knoop>::Backtrackflex(){
    deeloplossing.clear();
    
    
}

template <class knoop>
void Backtrackflex<knoop>::losOp(bool zoekalle){
    bool gedaan=false;
    losOp(gedaan,zoekalle);
}

template <class knoop>
void Backtrackflex<knoop>::losOp(bool& gedaan,bool zoekalle){
    //std::cout << "los op" << std::endl;
    if (controle()){//oplossing gevonden
        verwerk();
        if (!zoekalle)
            gedaan=true;
    }
    //bij sommige problemen kan een oplossing nog verlengd worden tot een langere oplossing
    //daarom moet het volgend stuk code ook worden uitgevoerd als we een oplossing hebben.
    if (!gedaan){
        //std::cout << "niet gedaan" << std::endl;
        //noot: het werken met referenties naar elementen van een vector is alleen veilig als de
        //vector onveranderlijk is.
         vector<knoop> mogelijkheid(geefVerdere());
        int i=0;
        while (i<mogelijkheid.size() && !gedaan){
            voegToeAanDeeloplossing(mogelijkheid[i]);
            losOp(gedaan,zoekalle);
            verwijderUitDeeloplossing();
            i++;
        }
        
    }
}

template <class knoop>
void Backtrackflex<knoop>::voegToeAanDeeloplossing(knoop& element){
    deeloplossing.push_back(&element);
}

template <class knoop>
void Backtrackflex<knoop>::verwijderUitDeeloplossing(){
    deeloplossing.resize(deeloplossing.size()-1);
}
#endif