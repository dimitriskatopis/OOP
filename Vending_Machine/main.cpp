#include <iostream>
#include <map>
#include <windows.h>
#include "vm.hpp"

using namespace std;

int menu()
{
    system("cls");
    int vchoice;
    cout<<"=== Λίστα Επιλογών ==="<<endl;
    cout<<"1. Καφές 1.5 ευρώ"<<endl;
    cout<<"2. Καφές με γάλα 1.8 ευρώ"<<endl;
    cout<<"3. Σοκολάτα 2.1 ευρώ"<<endl;
    cout<<"4. Σοκολάτα με γάλα 2.4 ευρώ"<<endl;
    cout<<"5. Τροφοδότηση"<<endl;
    cout<<"-1. Έξοδος"<<endl;
    cout<<"Διάλεξε επιλογή:";
    cin>>vchoice;
    return vchoice;
}


int main(int argc,char **argv)
{
    SetConsoleOutputCP(65001);
    string product;
    bool has_milk,exit_flag=false;
    int vchoice;
    Vending_Machine vm;
    while(1)
    {
        vchoice=menu();
        switch(vchoice)
        {
            case 1:
                product="coffee";
                has_milk=false;
                vm.payout(product,has_milk);
                break;
            case 2:
                product="coffee";
                has_milk=true;
                vm.payout(product,has_milk);
                break;
            case 3:
                product="chocolate";
                has_milk=false;
                vm.payout(product,has_milk);
                break;
            case 4:
                product="chocolate";
                has_milk=true;
                vm.payout(product,has_milk);
                break;
            case 5:
                vm.refill();
                system("pause");
                break;
            case -1:
                exit_flag=true;
                break;
            default:
                cerr<<"Μη διαθέσιμη επιλογή:"<<vchoice<<". Δοκιμάστε μία από τις διαθέσιμες επιλογές[-1,1-5]"<<endl;
                system("pause");
                break;
        }
        if(exit_flag)
        {
            break;
        }
    }
    cout<<vm<<endl;
    return EXIT_SUCCESS;
}