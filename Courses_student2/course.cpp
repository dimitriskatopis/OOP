#include "course.hpp"

Course::Course(string c, int s, string t, int cr) :code(c), semester(s), title(t), credits(cr) {}




int Course::get_semesterr() { return this->semester; }
string Course::get_title() { return this->title; }



string Course::get_code()const
{
    return this->code;
}


int Course::get_credits()
{
    return this->credits;
}