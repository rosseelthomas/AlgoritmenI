#ifndef __CHRONO
#define __CHRONO

#include <ctime>

class Chrono{
    public:
       Chrono();
       void start();
       void stop();
       double tijd() const;
    private:
       clock_t begin, einde;       
};

Chrono::Chrono(){}

void Chrono::start(){
   begin = clock();
}

void Chrono::stop(){
   einde = clock();
}

double Chrono::tijd() const{
   return static_cast<double>(einde - begin) / CLOCKS_PER_SEC;
}

#endif
