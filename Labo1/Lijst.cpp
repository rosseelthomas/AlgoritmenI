#include <iostream>
using namespace std;

namespace Lijsten{

// Lijst

template <typename T>
class Lijstknoop;

template <typename T>
class Lijst{
   public:
      Lijst();
      Lijst(const Lijst &l);
      ~Lijst();
    Lijst<T>* zoek_gerangschikt(const T& d);
    
      Lijst<T>& operator=(const Lijst<T> &l);
      void voeg_toe_vooraan(const T &d);
      void insertion_sort();
    void print();
   //private:
      Lijstknoop<T>* k;
};

template <typename T>
Lijst<T>::Lijst(){
   k=0;
}
    
    
    template <typename T>
    void Lijst<T>::print(){
        
        Lijst<T>* wijzer = this;
        while(wijzer->k!=0){
            cout << wijzer->k->data << " ";
            wijzer->k=wijzer->k->opv.k;
        }
    }

template <typename T>
Lijst<T>::Lijst(const Lijst &l){
   Lijst* p = this;
   Lijstknoop<T>* q = l.k;
   while(q != 0){
      p->k = new Lijstknoop<T>(q->data);
      p = &(p->k->opv);
      q = q->opv.k;
   }
}

template <typename T>
Lijst<T>::~Lijst(){
   delete k;
}
    
    template <typename T>
    void Lijst<T>::insertion_sort(){
      
        Lijst<T> sorted;
        Lijst<T>* ptr = this;
        while(ptr->k!=nullptr){
           
            Lijst<T>* ptr3 = sorted.zoek_gerangschikt(ptr->k->data);
            Lijstknoop<T>* temp = ptr3->k;
            ptr3->k=ptr->k;
            ptr->k=ptr->k->opv.k;
            ptr3->k->opv.k=temp;
            
            
        
        }
        this->k=sorted.k;
        sorted.k=nullptr;
        
        
        
    }
    
    
  

template <typename T>
Lijst<T>& Lijst<T>::operator=(const Lijst<T> &l){
   if(this != &l){
      delete k;
      Lijst* p = this;
      Lijstknoop<T>* q = l.k;
      while(q != 0){
         p->k = new Lijstknoop<T>(q->data);
         p = &(p->k->opv);
         q = q->opv.k;
      }          
   }
   return *this;
}

template <typename T>
void Lijst<T>::voeg_toe_vooraan(const T &d){
   Lijstknoop<T>* h=k;
   k = new Lijstknoop<T>(d);
   k->opv.k = h;
}
    
    template <typename T>
    Lijst<T>* Lijst<T>::zoek_gerangschikt(const T &d){
        Lijst<T>* ptr = this;
        while(ptr->k!=nullptr && ptr->k->data<d){
            ptr = &(ptr->k->opv);
        }
        return ptr;
    }
   
// Lijstknoop

template <typename T>
class Lijstknoop{
   friend class Lijst<T>;
   public:
      Lijstknoop(const T &d = T());
   //private:
      T data;
      Lijst<T> opv;
};

template <typename T>
Lijstknoop<T>::Lijstknoop(const T &d) : data(d) {}

} // namespace Lijsten

int main(){

    Lijsten::Lijst<int> l;
    l.voeg_toe_vooraan(6);
    l.voeg_toe_vooraan(9);
    l.voeg_toe_vooraan(3);
    //l.print();
    l.insertion_sort();
    l.print();
    
    
}
