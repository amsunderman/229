#ifndef SIMULATION
#define SIMULATION

#ifndef STRING
#define STRING
#include <string>
#endif

using namespace std;

class Simulation
{
    private:
        string name;
        int generation;
        int startGen;

    public:
        Simulation();
        void setName(string name);
        void setGen(int gen);
        void setStartGen(int sGen);
        string getName();
        int getGen();
        int getStartGen();
};

#endif
