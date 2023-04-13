
#include <iostream>
#include <string>
#include <vector>
#include "course.hpp"

using namespace std;

class student //Δημιουργια κλασσης μαθητη για τα σtοιχεια του φοιτητη
{
private:
    int id; // Το id χρησιμοποιειται για λογους ευρεσης του μαθητη και αριθμησης των φοιτητων 
    int am;
    string name;
    int semester;
    int ects;
    int ects_left;
    vector<Course> submited_courses; // Δημιορυγια πινακα για τα μαθηματα που δηλωνει ο φοιτητης 


public:



    student(int _id, int _am, string _name, int _semester, int _ects);//constructor
    ~student() {}
    int get_id()const;
    int get_am()const;
    string  get_name()const;
    int get_semester()const;
    int get_ects()const;
    int get_ects_left();
    vector <Course> get_courses1();
    //setters για το να μπορουμε να αλλαζουμε τα στοιχεια των φοιτητων 
    void set_name(string namee);
    void set_sem(int sem);
    void set_ects(int ECTS);
    void set_ects_left(int ECTS);
    void set_id(int ID);
    bool is_course_valid(const Course& c);
    void sub_ects(Course& c);//αφαιρεση των ects καθε φορα που επιλεγται ενα μαθημα 
    void add_course(Course& c);
    
    void show();//δοκιμαστικη συναρτηση για να ελεγχουμε αν περνανε τα μαθηματα στα δηλωμενα μαθηματα
    

};