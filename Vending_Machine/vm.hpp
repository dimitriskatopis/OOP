#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <ctime>
#include <sstream>


using namespace std;

// https://stackoverflow.com/questions/997946/how-to-get-current-time-and-date-in-c
const std::string currentDateTime(); 

class Vending_Machine
{
    private:
        map <string,double> products;
        map <string,int> quantity;
        map <double,int> coin_buffer;
        double total_check;
        double temporary_amount;
        vector <string> vending_machine_memory;

    public:
        static map <string,string> products_in_greek;
        Vending_Machine();
       ~Vending_Machine();
        bool coin_insert();
        void payout(string product,bool has_milk=false);
        void reduce_quantity(const string product);
        void refill();
        friend ostream &operator<<(ostream &os,const Vending_Machine &vm);  
        void change();
};