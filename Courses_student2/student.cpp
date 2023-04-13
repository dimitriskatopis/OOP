#include "student.hpp"





student::student(int _id, int _am, std::string _name, int _semester, int _ects) : id(_id), am(_am), name(_name), semester(_semester), ects(_ects) {}

int student::get_id() const { return this->id; }
int student::get_am()const { return this->am; }
std::string student::get_name()const { return this->name; }
int student::get_semester()const { return this->semester; }
int student::get_ects()const { return this->ects; }
void student::set_id(int ID) { this->id = ID; }
void student::set_name(string namee) { this->name = namee; }
void student::set_sem(int sem) { this->semester = sem; }
void student::set_ects(int ECTS) { this->ects = ECTS; }
void student::set_ects_left(int ECTS) { this->ects_left = ECTS; }
int student::get_ects_left()
{
    return this->ects_left;
}

bool student::is_course_valid(const Course& c)
{
    for (auto& course : this->submited_courses)
    {
        if (c.get_code() == course.get_code())
        {
            return false;
        }
    }
    return true;
}
void student::sub_ects(Course& c)
{
    this->ects_left -= c.get_credits();

}
void student::add_course(Course& c)
{

    this->submited_courses.push_back(c);
}

vector <Course> student::get_courses1()
{
    return this->submited_courses;
}
void student::show()
{
    for (auto& course : this->submited_courses)
    {
        cout << course.get_title() << endl;
    }
}