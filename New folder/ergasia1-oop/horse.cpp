#include "horse.hpp"

mt19937 mt(steady_clock::now().time_since_epoch().count());

horse::horse(int h_id,std::string h_name,int h_startup_speed,int h_power,int h_stamina):id(h_id),name(h_name),power(h_power),startup_speed(h_startup_speed),stamina(h_stamina) {}


std::string horse::get_name()const {return this->name;}
int horse::get_power()const {return this-> power;}
int horse::get_id()const {return this->id;}
int horse::get_stamina()const {return this-> stamina;}
int horse::get_startup_speed()const {return this ->startup_speed;}
bool horse::move_forward(int step,double random_factor)
{
    if(step==1)
    {
        if(this->startup_speed>random_factor)
        {
            return true;
        }
    }
    else if(step>=2 && step<=8)
    {
        if(this->power>random_factor)
        {
            return true;
        }
    }
    else
    {
        double aver=(double)(this->power+this->stamina)/2;
        if(aver>random_factor)
        {
            return true;
        }
    }
    return false;
}