#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
int main()
{
    int width;
    int height;
    int myId;
    cin >> width >> height >> myId; cin.ignore();
    srand (time(NULL));
    int myx, myy, bombs;
    int nextx=rand() % 6 + 3;
    int nexty=rand() % 4 + 3; 

    // game loop
    while (1) {
        for (int i = 0; i < height; i++) {
            string row;
            getline(cin, row);
            

 
        }
        int entities;
        
        cin >> entities; cin.ignore();
        for (int i = 0; i < entities; i++) {
            int entityType;
            int owner;
            int x;
            int y;
            int param1;
            int param2;
            cin >> entityType >> owner >> x >> y >> param1 >> param2; cin.ignore();
            //cerr << entityType << owner << x >> y >> param1 >> param2; cin.ignore();
            if (owner==myId && entityType==0){
                myx=x;
                myy=y;
                bombs=param1;
            }
                
        }
        
        if (abs(nextx-myx)<2 && abs(nexty-myy)<2 && bombs>0){
            cout << "BOMB " << nextx <<" "<< nexty << endl;
            nextx=rand() % 12;
            nexty=rand() % 6; 
        }
        else cout << "MOVE "<< nextx <<" "<< nexty << endl;
        // Write an action using cout. DON'T FORGET THE "<< endl"
        // To debug: cerr << "Debug messages..." << endl;

    }
}