#include <wx/wx.h>
#include <wx/listctrl.h>
#include "student.hpp"
#include <fstream>
#include <sstream>
#include <windows.h>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>



#define MAX_INPUT_LENGTH 255
#pragma execution_character_set("utf-8")



using namespace std;


namespace app
{
    vector <student> students;
    vector <Course> courses;


};


class Frame :public wxFrame {
private:
    wxListCtrl* studentsctrl;
    wxListCtrl* lessonsctrl;
    wxBoxSizer* sizer;
    vector <student> students;
    vector <Course> courses;
    void create_students_list(wxWindow* parent)
    {
        auto size = this->GetSize();
        this->studentsctrl = new wxListCtrl(parent, wxID_ANY, wxDefaultPosition, wxSize(size.GetWidth() * 0.45, size.GetHeight() * 0.45), wxLC_REPORT);
        this->studentsctrl->SetFont(wxFont(11, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
        this->studentsctrl->SetBackgroundColour(wxColor("#a88fb3"));
        this->studentsctrl->InsertColumn(0, wxT("Id"), wxLIST_FORMAT_CENTER, size.GetWidth() * 0.45 / 12);
        this->studentsctrl->InsertColumn(1, wxT("AM"), wxLIST_FORMAT_CENTER, size.GetWidth() * 0.45 / 4);
        this->studentsctrl->InsertColumn(2, wxT("ΟΝΟΜΑ"), wxLIST_FORMAT_CENTER, size.GetWidth() * 0.45 / 4);
        this->studentsctrl->InsertColumn(3, wxT("ΕΞΑΜΗΝΟ"), wxLIST_FORMAT_CENTER, size.GetWidth() * 0.45 / 4);
        this->studentsctrl->InsertColumn(4, wxT("Δ. ΜΟΝΑΔΕΣ"), wxLIST_FORMAT_CENTER, size.GetWidth() * 0.45 / 4);
        for (int i = 0, t = this->students.size(); i < t; i++)
        {
            // Προσθήκη νέου αντικειμένου στην λίστα
            wxListItem it;
            it.SetAlign(wxLIST_FORMAT_CENTER);
            this->studentsctrl->InsertItem(i, it);

            // Προσθήκη φοιτητή στό αντικείμενο
            this->studentsctrl->SetItem(i, 0, wxString(to_string(this->students.at(i).get_id())));
            this->studentsctrl->SetItem(i, 1, wxString(to_string(this->students.at(i).get_am())));
            this->studentsctrl->SetItem(i, 2, wxString(this->students.at(i).get_name()));
            this->studentsctrl->SetItem(i, 3, wxString(to_string(this->students.at(i).get_semester())));
            this->studentsctrl->SetItem(i, 4, wxString(to_string(this->students.at(i).get_ects())));
        }
    }

    void create_lessons_list(wxWindow* parent)
    {
        auto size = this->GetSize();
        this->lessonsctrl = new wxListCtrl(parent, wxID_ANY, wxDefaultPosition, wxSize(size.GetWidth() * 0.45, size.GetHeight() * 0.45), wxLC_REPORT);
        this->lessonsctrl->SetFont(wxFont(11, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
        this->lessonsctrl->SetBackgroundColour(wxColor("#a88fb3"));
        this->lessonsctrl->InsertColumn(0, wxT("ΚΩΔΙΚΟΣ"), wxLIST_FORMAT_CENTER, size.GetWidth() * 0.45 / 4);
        this->lessonsctrl->InsertColumn(1, wxT("ΤΙΤΛΟΣ"), wxLIST_FORMAT_CENTER, size.GetWidth() * 0.45 / 4);
        this->lessonsctrl->InsertColumn(2, wxT("ΕΞΑΜΗΝΟ"), wxLIST_FORMAT_CENTER, size.GetWidth() * 0.45 / 4);
        this->lessonsctrl->InsertColumn(3, wxT("Δ. ΜΟΝΑΔΕΣ"), wxLIST_FORMAT_CENTER, size.GetWidth() * 0.45 / 4);

        //Προσθήκη μαθημάτων στην λίστα
        for (int i = 0, t = this->courses.size(); i < t; i++)
        {
            wxListItem it;
            it.SetAlign(wxLIST_FORMAT_CENTER);
            this->lessonsctrl->InsertItem(i, it);

            this->lessonsctrl->SetItem(i, 0, wxString(wxString::FromUTF8(this->courses.at(i).get_code())));
            this->lessonsctrl->SetItem(i, 1, wxString(wxString::FromUTF8(this->courses.at(i).get_title())));
            this->lessonsctrl->SetItem(i, 2, wxString(wxString::FromUTF8(to_string(this->courses.at(i).get_semesterr()))));
            this->lessonsctrl->SetItem(i, 3, wxString(wxString::FromUTF8(to_string(this->courses.at(i).get_credits()))));
        }
    }

    void panel1()
    {
        auto size = this->GetSize();
        wxPanel* panel = new wxPanel(this, wxID_ANY);
        wxStaticText* text = new wxStaticText(panel, wxID_ANY, wxT("ΦΟΙΤΗΤΕΣ"), wxDefaultPosition, wxSize(size.GetWidth() * 0.22, size.GetHeight() * 0.05), wxTEXT_ALIGNMENT_CENTER);
        text->SetFont(wxFont(15, wxFONTFAMILY_ROMAN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
        text->SetForegroundColour(wxColor("#701682"));
        this->create_students_list(panel);
        wxButton* button = new wxButton(panel, wxID_ANY, wxT("ΕΜΦΑΝΙΣΗ ΜΑΘΗΜΑΤΩΝ"), wxDefaultPosition, wxSize(150, 30));
        button->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &Frame::showlessons, this);
        wxBoxSizer* panelsizer = new wxBoxSizer(wxVERTICAL);
        panelsizer->AddSpacer(15);
        panelsizer->Add(text, 0, wxALIGN_CENTER);
        panelsizer->AddSpacer(15);
        panelsizer->Add(this->studentsctrl, 0, wxALIGN_CENTER);
        panelsizer->AddSpacer(15);
        panelsizer->Add(button, 0, wxALIGN_CENTER);
        panel->SetSizer(panelsizer);
        this->sizer->Add(panel);
    }

    void panel2()
    {
        auto size = this->GetSize();
        wxBoxSizer* bx = new wxBoxSizer(wxVERTICAL);
        wxPanel* panel = new wxPanel(this, wxID_ANY);
        wxStaticText* text = new wxStaticText(panel, wxID_ANY, wxT("ΜΑΘΗΜΑΤΑ"), wxDefaultPosition, wxSize(size.GetWidth() * 0.22, size.GetHeight() * 0.05), wxTEXT_ALIGNMENT_CENTER);
        text->SetFont(wxFont(15, wxFONTFAMILY_ROMAN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
        text->SetForegroundColour(wxColor("#701682"));
        this->create_lessons_list(panel);
        bx->AddSpacer(15);
        bx->Add(text, 0, wxALIGN_CENTER);
        bx->AddSpacer(15);
        bx->Add(this->lessonsctrl, 0, wxALIGN_CENTER);
        panel->SetSizer(bx);
        this->sizer->Add(panel);

    }

   

public:
    Frame(vector <student>& sts, vector <Course>& crs) :wxFrame(nullptr, wxID_ANY, wxT("ΣΥΣΤΗΜΑ ΔΙΑΧΕΙΡΗΣΗΣ ΦΟΙΤΗΤΩΝ"), wxDefaultPosition, wxSize(800, 600))
    {
       
        this->students = sts;
        this->courses = crs;
        this->SetMinSize(wxSize(800, 600));
        this->SetMaxSize(wxSize(800, 600));
        this->SetBackgroundColour(wxColor("#ebe2e1"));
        this->sizer = new wxBoxSizer(wxHORIZONTAL);
        this->sizer->AddSpacer(16);
        this->panel1();
        this->sizer->AddSpacer(16);
        this->panel2();
        this->SetSizer(this->sizer);
    }
    ~Frame() {}
  


    void showlessons(wxCommandEvent& ev)
    {

        auto it = this->studentsctrl->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
        auto student_id = std::stoi(std::string(this->studentsctrl->GetItemText(it)));
        auto studentitr = std::find_if(this->students.begin(), this->students.end(), [&](student& s) {return s.get_id() == student_id; });

        vector <Course> submited_courses = studentitr->get_courses1();
        if (submited_courses.empty())
        {
            std::string message2 = "ΔΕΝ ΥΠΑΡΧΟΥΝ ΔΗΛΩΜΕΝΑ ΜΑΘΗΜΑΤΑ";
            wxMessageBox(wxString(wxString::FromUTF8(message2)), wxT("ΔΗΛΩΜΕΝΑ ΜΑΘΗΜΑΤΑ"), wxICON_INFORMATION);
        }
        else {
            vector<string> message1;
            for (int i = 0; i < submited_courses.size(); i++)

            {
                message1.push_back((submited_courses[i].get_title()));
            }
            std::string message;
            
            message = std::accumulate(std::begin(message1) + 1, std::end(message1), message1[0],
                [](std::string s0, std::string const& s1) { return s0 += "\n" + s1; });
            wxMessageBox(wxString(wxString::FromUTF8(message)), wxT("ΔΗΛΩΜΕΝΑ ΜΑΘΗΜΑΤΑ"), wxICON_INFORMATION);
        }

    }
    
};


class App :public wxApp {
public:
    bool OnInit()wxOVERRIDE
    {
        Frame* f = new Frame(app::students, app::courses);
        f->Show(true);
        return true;
    }
};

wxIMPLEMENT_APP_NO_MAIN(App);



void displaystudents(vector<student>& students)
{

    unsigned int size = students.size();

    for (unsigned int i = 0; i < size; i++)
    {
        cout << students[i].get_id() << " ";
        cout << students[i].get_am() << " " << endl;
        cout << students[i].get_name() << "  " << endl;

        cout << "Semester: " << students[i].get_semester() << "  " << endl;
        cout << "ECTS: " << students[i].get_ects() << endl;
        cout << endl;
    }
}

int main(int argc, char** argv)

{
    
    SetConsoleOutputCP(65001);

    vector<student> students;
    vector<Course> courses;
    
    //Περναμε τα μαθηματα απο το αρχειο dit_uoi_course.txt στον πινακα courses της κλασης Course
    string filename = "dit_uoi_course.txt";
    fstream fs;
    fs.open(filename, ios::in);
    if (!fs.is_open())
    {
        cerr << "File " << filename << " does not exist" << endl;
        return 1;
    }
    string line, word;
    bool first_line = true;
    vector<string> data;
    while (getline(fs, line))
    {
        if (first_line)
        {
            first_line = false;
            continue;
        }
        data.clear();
        stringstream ss(line);
        while (getline(ss, word, ','))
        {
            data.push_back(word);
        }
        courses.push_back(Course(data[0], stoi(data[1]), data[2], stoi(data[3])));
    }
    fs.close();

    cout << endl;
    //Μενου επιλογων 
    cout << "1. Εισαγωγή νέου φοιτητή" << endl;
    cout << "2. Ενημέρωση στοιχείων φοιτητή" << endl;
    cout << "3. Διαγραφή φοιτητή" << endl;
    cout << "4. Δήλωση μαθήματος" << endl;
    cout << "5. Εμφάνιση δηλώσεων ανά φοιτητή (GUI)" << endl;
    cout << "0. Έξοδος" << endl;
    //Δημιουργια μεταβλητων στην main για να τις περασουμε στον constructor και να τις περασουμε μετα και στους setters
    int choice;
    int idd=0;
    int amm;
    string namee;
    int sem;
    int ECTS;
    int student_selected;
    
    while (1)
    {

        cout << "Δωσε επιλογή " << endl;
        cin >> choice;

        if (choice == 1)
        {
            do {
                cout << "Δώσε AM φοιτητή:" << endl;;
                cin >> amm;
                bool student_exists; //Ελεγχος αν υπαρχει ηδη ο αριθμος μητρωου 
                while (1)
                {
                    student_exists = false;
                    for (auto student : students)
                    {
                        if (student.get_am() == amm)
                        {
                            student_exists = true;
                            break;
                        }
                    }
                    if (!student_exists)
                    {
                        break;
                    }

                    cout << "Το ΑΜ:" << amm << " υπάρχει ήδη στο σύστημα!Εισάγεται ένα έγκυρο ΑΜ:";
                    cin >> amm;
                }
            } while (amm < 0);
            cout << "Δωσε ονοματεπωνυμο : " << endl;
            cin.ignore();
            getline(cin, namee);
            do
            {
                cout << "Δωσε εξαμηνο στο οποιο βρισκεσαι :  " << endl;
                cin >> sem;
            } while (sem < 0 || sem > 8);
            do 
            {
                cout << "Δωσε διδακτικες μοναδες: " << endl;
                cin >> ECTS;
            } while (ECTS < 0); 
         
            student S_student = student(idd, amm, namee, sem, ECTS);
            students.push_back(S_student);
            cout << endl;
            cout << endl;
              idd++;
        }

        else if (choice == 2)
        {
            cout << endl;
            cout << endl;

            displaystudents(students);

            cout << "Επελεξε εναν φοιτητη για ενημερωση των στοιχειων του :" << endl;
            cin >> student_selected;
            // Έλεγχος εγκυρότητας επιλεγμένης θέσης σε πίνακα students.
            while (student_selected < 0 || student_selected >= students.size())
            {
                cout << "Μη έγκυρη επιλογή!Επέλεξε αριθμό από [0-" << students.size() - 1 << "]:";
                cin >> student_selected;
            }
           
            for (int i = 0; i < students.size(); i++)
            {
                if (student_selected == students[i].get_id())
                {
                    cout << "Αλλαξε το ονομα :" << endl;
                    cin.ignore();
                    getline(cin, namee);
                    students[i].set_name(namee);
                    do
                    {
                        cout << "Αλλαξε το εξαμηνο :" << endl;
                        cin >> sem;
                        students[i].set_sem(sem);
                    } while (sem < 0 || sem>8);
                    do
                    {
                        cout << "Αλλαξε τα ects :  " << endl;
                        cin >> ECTS;
                        students[i].set_ects(ECTS);
                    } while (ECTS < 0);
                }
            }
        }

        else if (choice == 3)
        {
            if (students.empty())
            {
                cout << "Δεν υπαρχουν δηλωμενοι μαθητες" << endl;
            }
            else {
                displaystudents(students);
                cout << "Επελεξε τον φοιτητη που θες να διαγραψεις : " << endl;
                cin >> student_selected;
                // Έλεγχος εγκυρότητας επιλεγμένης θέσης σε πίνακα students.
                while (student_selected < 0 || student_selected >= students.size())
                {
                    cout << "Μη έγκυρη επιλογή!Επέλεξε αριθμό από [0-" << students.size() - 1 << "]:";
                    cin >> student_selected;
                }
                
                
                students.erase(std::remove_if(students.begin(), students.end(), [&student_selected](const student& student) -> bool
                    { return student.get_id() == student_selected; }),
                    students.end());
                //Αλλαγη του id των φοιτητων αφου διαγραφει καποιος
                for (int i = student_selected; i < students.size(); i++)
                {
                    students[i].set_id(i);
                }

            }
        }
        else if (choice == 4)
        {
        if (students.empty())
        {
            cout << "Δεν υπαρχουν δηλωμενοι μαθητες" << endl;
        }
        else {

            displaystudents(students);
            cout << "Επελεξε φοιτητή:";
            cin >> student_selected;
            // Έλεγχος εγκυρότητας επιλεγμένης θέσης σε πίνακα students.
            while (student_selected <0 || student_selected >= students.size())
            {
                cout << "Μη έγκυρη επιλογή!Επέλεξε αριθμό από [0-" << students.size() - 1 << "]:";
                cin >> student_selected;
            }

            vector<Course> student_available_courses;
            //Περναμε τα ects σε τοπικη μεταβλητη για να τα βαλουμε στα ects left και να αφαιρουνται καταλληλα
            int ECTSS = students[student_selected].get_ects();
            students[student_selected].set_ects_left(ECTSS);

            for (auto& course : courses)
            {

                if (students[student_selected].get_semester() % 2 == course.get_semesterr() % 2 && students[student_selected].get_semester() >= course.get_semesterr() && students[student_selected].get_ects_left() >= course.get_credits() && students[student_selected].is_course_valid(course))
                {
                    student_available_courses.push_back(course);
                }
            }
            int course_choice;
            if (student_available_courses.empty())
            {
                cout << "Δεν υπαρχουν διαθεσιμα υπολοιπα μαθηματα για δηλωση" << endl;
            }
            else {
                for (int i = 0; i < student_available_courses.size(); i++)
                {
                    cout << i << "." << student_available_courses[i].get_title() << endl;
                }

                do
                {
                    cout << "Διάλεξε μάθημα:";
                    cin >> course_choice;
                    while (course_choice < 0 || course_choice >= student_available_courses.size())
                    {
                        cout << "Μη έγκυρη επιλογή[0-" << student_available_courses.size() - 1 << "]:";
                        cin >> course_choice;
                    }

                    students[student_selected].sub_ects(student_available_courses[course_choice]);
                    students[student_selected].add_course(student_available_courses[course_choice]);

                } while (students[student_selected].get_ects_left() > 0);
            }
            
        }
        }
        else if(choice == 5)
        {
        app::students = students;
        app::courses = courses;
        
        wxEntry(argc, argv);
        
        }
        else if (choice == 0)
        {
        return 0;
        }
        else
        cout << "Δεν υπαρχει αυτη η επιλογη" << endl;
    }
    return 0;
}