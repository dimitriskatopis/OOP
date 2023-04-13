#pragma once
#include <iostream>

using namespace std;

class Course  //Δημιουργια κλασης για τα μαθηματα 
{
private:
    // kωδικός, τίτλος, εξάμηνο διδασκαλίας και διδακτικές μονάδες
    string code;
    int semester;
    string title;
    int credits;
public:
    Course(string c, int s, string t, int cr);
    //getters
    int get_semesterr();
    string get_code()const;
    int get_credits();
    string get_title();
};
