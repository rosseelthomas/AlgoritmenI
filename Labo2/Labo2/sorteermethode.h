#ifndef __SORTEERMETHODE
#define __SORTEERMETHODE

#include <iostream>
    using std::endl;
    using std::cout;
#include <vector>
	using std::vector;
#include <algorithm>   // voor sort()-methode uit STL
#include <cmath>

template <typename T>
class Sorteermethode{
	public:
		virtual void operator()(vector<T> & v) const = 0;
};

/*
 *   STANDARD TEMPLATE LIBRARY SORT
 */
template <typename T>
class STLSort : public Sorteermethode<T>{
	public:
		void operator()(vector<T> & v) const;
};

template <typename T>
void STLSort<T>::operator()(vector<T> & v) const{
	sort(v.begin(),v.end());
}

/*
 *   INSERTION SORT
 */
template <typename T>
class InsertionSort : public Sorteermethode<T>{
	public:
		void operator()(vector<T> & v) const;	
};

template <typename T>
void insertionsort(vector<T> &v, int begin, int end){

    for(int i=begin+1; i<=end; i++){
        T h = v[i];
        int j=i-1;
        while(j>=0 && h<v[j]){
            v[j+1] = v[j];
            j--;
        }
        v[j+1] = h;
    }
}

template <typename T>
void InsertionSort<T>::operator()(vector<T> & v) const{
    insertionsort(v,0, v.size()-1);
}



/*
 *   SHELLSORT
 */
 
template <typename T>
class ShellSort : public Sorteermethode<T>{
	public:
    void operator()(vector<T> & v) const{
        
        
        int k = 7;
        while(k>=1){
        
            for(int i=k; i<v.size();++i){
                int h = v[i];
                int j = i-k;
                while(j>=0 && h<v[j]){
                    v[j+k] = v[j];
                    j-=k;
                }
                v[j+k] = h;
            
            }
            k--;
        }
    
    
    }
};


template <typename T>
void maakHeap(vector<T> &v, int ouder, int heapsize){
    
    int indexkind1 = 2*ouder +1;
    int indexkind2 = 2*ouder +2;
    
    
    if(indexkind2<=heapsize-1){
        //ouder heeft 2 kinderen
        int grootstekind = (v[indexkind1]>v[indexkind2])?indexkind1:indexkind2;
        if(v[ouder]<v[grootstekind]){
            iter_swap(v.begin()+ouder, v.begin() + grootstekind);
            maakHeap(v, grootstekind, heapsize);
        }
    
    }else if(indexkind1<=heapsize-1){
        //ouder heeft 1 kind
        if(v[ouder]<v[indexkind1]){
            iter_swap(v.begin()+ouder, v.begin() +  indexkind1);
            maakHeap(v, indexkind1, heapsize);
        }
    }


}




/*
 *  HEAPSORT
 */
template <typename T>
class HeapSort : public Sorteermethode<T>{
public:
    void operator()(vector<T> & v) const{
    
        for(int heapsize = v.size();heapsize>0;heapsize--){
            
            for(int i = std::floor(heapsize/2)-1;i>=0;i--){
                maakHeap(v, i,heapsize);
            }
            iter_swap(v.begin(), v.begin() +  heapsize-1);
            
            
        }
        
        
        
        
    
    }
    
    
};

/*
 * MERGESORT
 */



template <typename T>
void merge(vector<T> &v,int l, int m,int r,  vector<T> &h){
    
    for(int i=l;i<=m;++i){
        h[i-l]=v[i];
    }
    int indexv = m+1;
    int indexh=0;
    int invoeg = l;
    while(invoeg<=r){
        if(indexv>r){
            // rechtertabel leeg (in v)
            for(int i=indexh;i<=m-l;++i){
                v[invoeg] =h[i];
                invoeg++;
            }
        
        }else if(indexh>m-l){
            //linkertabel leeg (in h)
            invoeg = r+1;
        }else if(h[indexh]<v[indexv]){
            //element in h groter, dus v invoegen
            v[invoeg] = h[indexh];
            indexh++;
            invoeg++;
            
        }else{
            //element in v groter, dus h invoegen
            v[invoeg] = v[indexv];
            indexv++;
            invoeg++;
        
        }
    
    }
    
    
    
}

template <typename T>
void mergesort(vector<T> &v,int l, int r, vector<T> &h){
   
    if(l<r){
        int m = l+floor((r-l)/2);
        mergesort(v,l,m,h);
        mergesort(v,m+1,r,h);
        merge(v,l,m,r,h);
        
    }
    
}


template <typename T>
class MergeSort : public Sorteermethode<T>{
public:
    void operator()(vector<T> & v) const{
        vector<T> h(v.size()/2);
        mergesort(v,0,v.size()-1,h);
    }
    
    
};

/*
 * QUICKSORT
 */

template <typename T>
void quicksort(vector<T> & v, int l, int r){

    if(l<r){
    T pivot = v[r];
    int i = l; int j=r;
    while(v[i]<pivot){
        ++i;
    }
    
    while(i<j){
        T hulp = v[i];
        v[i]=v[j];
        v[j]=hulp;
        i++;
        while(v[i]<pivot){
            ++i;
        }
        j--;
        while(v[j]>pivot){
            --j;
        }
        
    
    }
    quicksort(v, l, j-1);
    quicksort(v, j, r);
    }

}

template <typename T>
class QuickSort : public Sorteermethode<T>{
public:
    void operator()(vector<T> & v) const{
        quicksort(v, 0, v.size()-1);
    }
    
    
};



template <typename T>
void fancyquicksort(vector<T> & v, int begin, int end){
    
    
    
    if(end>(begin+10)){
        T p1 = v[begin];
        T p2 = v[end];
        if(p2<p1) {iter_swap(v.begin() + begin, v.begin() +  end); T t = p1;p1=p2;p2=t;}
        
        int k = begin+1;
        int m = k;
        int g = end;
        
        while(m<g){
            if(v[m] < p1){
                iter_swap(v.begin() + m, v.begin() +  k);k++;m++;
            }else if(v[m]>p2){
                iter_swap(v.begin() + m, v.begin() +  g-1);g--;
            }else{
                ++m;
            }
                    }
        iter_swap(v.begin() +begin , v.begin() +  k-1);
        iter_swap(v.begin() + end, v.begin() +  m);
        fancyquicksort(v, begin, k-2);
        fancyquicksort(v, k, g-1);
        fancyquicksort(v, g+1, end);

        
    
    
    }else if(end>begin){
        insertionsort(v,  begin,  end);
    }
    
    
}

template <typename T>
class FancyQuickSort : public InsertionSort<T>{
public:
    void operator()(vector<T> & v) const{
        fancyquicksort(v, 0, v.size()-1);
    }

};




#endif 
