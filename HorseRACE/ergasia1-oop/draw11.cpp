#include <iostream>
#include <cstdlib> // atoi
#include "horse.cpp"
#include <vector>
#include <random>
#include <chrono>
#include <algorithm>
#include <bits/stdc++.h>

#define DNF 1000
using namespace std::chrono;
using namespace std;

void draw(vector<int> &positions, int horses, int rounds)
{
    for (int i = 0; i < horses; i++)
    {
        cout << "|";
        for (int j = 0; j <= rounds; j++)
        {
            if (j == positions[i])
                cout << i + 1;
            else
                cout << ".";
        }
        cout << "|" << endl;
    }
}

void press_any_key()
{
    cout << "Press Any Key....";
    cin.get();
    cout << endl
         << endl;
}

int main(int argc, char *argv[])
{
    int wallet;
    int bet_amount;
    int selected_horse;

    int rank = 1;
    vector<::pair<horse, int>> standings;
    vector<horse> horses;
    // cmd lines arguments

    int ho = 4;
    int counter = 0;
    int rounds = 10;
    vector<int> positions;
    if (argc == 3)

    {

        ho = atoi(argv[1]);

        rounds = atoi(argv[2]);
    }
    if (ho <= 10 && rounds <= 20)
    {
        unsigned seed = chrono::steady_clock::now().time_since_epoch().count();
        auto random_number_generator = default_random_engine{seed};
        uniform_int_distribution<int> dist(50, 100);
        uniform_real_distribution<double> dista(0.0, 100.0);
        double random = dista(mt);
        vector<string> horse_names = {"Blitz", "Bolt", "Goliath", "Hercules", "Rogue", "Danger", "Raider", "Storm", "Nitro", "Hulk"};
        auto rng = default_random_engine{seed};
        shuffle(begin(horse_names), end(horse_names), rng);

        for (int j = 0; j < ho; j++)

        {
            int i = j + 1;
            int startup_speed = dist(random_number_generator);
            int power = dist(random_number_generator);
            int stamina = dist(random_number_generator);
            horse h_horse = horse(i, horse_names[j], power, startup_speed, stamina);
            horses.push_back(h_horse);
            standings.push_back(make_pair(h_horse, DNF));
            positions.push_back(0);
        }

        unsigned int size = horses.size();

        for (unsigned int i = 0; i < size; i++)
        {
            cout << horses[i].get_id() << " " << horses[i].get_name() << "  "
                 << "power=" << horses[i].get_power() << "  "
                 << "stamina=" << horses[i].get_stamina() << " "
                 << "startup_speed=" << horses[i].get_startup_speed() << endl;

            cout << random << endl;
        }

        const int roundsex = rounds * 2;
        bool canbemoved;
        /*
        cout<<"Give total amount"<<endl;
        cin>>wallet;
        

        cout << "select horse for betting:" << endl;
        cin >> selected_horse;
        
        cout << "Give bet amount:" << endl;
        cin >> bet_amount;
        */
        cout << "press any key to continue" << endl;
        cin.get();

        for (int r = 1; r <= roundsex; r++)
        {

            for (int i = 0; i < ho; i++)
            {

                canbemoved = horses[i].move_forward(r, random);
                if (positions[i] == rounds)
                {

                    if (standings[i].second == DNF)
                    {
                        standings[i].second = rank;
                        counter++;
                        rank++;
                    }
                    continue;
                }

                if (canbemoved)
                {
                    positions[i]++;
                }
            }
            if (counter == ho)
                break;
            for (unsigned int i = 0; i < size; i++)
            {
                cout << horses[i].get_id() << " " << horses[i].get_name() << "  "
                     << "power=" << horses[i].get_power() << "  "
                     << "stamina=" << horses[i].get_stamina() << " "
                     << "startup_speed=" << horses[i].get_startup_speed() << endl;

                cout << random << endl;
            }

            draw(positions, ho, rounds);
            cout << "press any key to continue";
            cin.get();
        }
        cout << "====== Standings =======" << endl;
        sort(standings.begin(), standings.end(), [](pair<horse, int> &p1, pair<horse, int> &p2)
             { return p1.second < p2.second; });
        for (int i = 0; i < standings.size(); i++)

        {
            cout << standings[i].first.get_name() << "->" << (standings[i].second == 1000 ? "DNF" : to_string(standings[i].second)) << endl;
        }
        cout << endl;
    /*
            int temp1=standings[0].first.get_id();
            int temp2=standings[1].first.get_id();
            int temp3=standings[2].first.get_id();

    

            if (horses[selected_horse].get_id() == temp1)
            {

                wallet += bet_amount * 2;
                
            }
            else if (horses[selected_horse].get_id() == temp2 || horses[selected_horse].get_id() == temp3)
            {
               
            }
            else
                wallet -= bet_amount;
        
        */

        
    }
    else
        cout << "Wrong number of arguments" << endl;
}
