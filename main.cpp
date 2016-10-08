#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

/**
 * Shoot enemies before they collect all the incriminating data!
 * The closer you are to an enemy, the more damage you do but don't get too close or you'll get killed.
 **/
struct coordinates{
  int x; 
  int y;
  coordinates(int ix, int iy){
  x=ix;
  y=iy;
  }
  coordinates(){
  x=-1;
  y=-1;
  }
}; 

struct enemy{
  int x; 
  int y;
  int life;
  enemy(int ix, int iy, int il){
  x=ix;
  y=iy;
  life=il;
  }
};

int main()
{
    coordinates me;
    map<int, enemy> enemis;
    map<int, coordinates> dataPoints;
    // game loop
    while (1) {
        int x;
        int y;
        cin >> x >> y; cin.ignore();
        me.x=x;
        me.y=y;
        int dataCount;
            int dataId;
            int dataX;
            int dataY;
        cin >> dataCount; cin.ignore();
        for (int i = 0; i < dataCount; i++) {
            cin >> dataId >> dataX >> dataY; cin.ignore();
            coordinates coord = coordinates(dataX, dataY);
            dataPoints.emplace(dataId, coord);
        }
        int enemyCount;
        int enemyId;
        cin >> enemyCount; cin.ignore();
        bool finish=false;
        for (int i = 0; i < enemyCount; i++) {
            int enemyX;
            int enemyY;
            int enemyLife;
            cin >> enemyId >> enemyX >> enemyY >> enemyLife; cin.ignore();
			enemy nemesis=enemy(enemyX, enemyY, enemyLife);
            enemis.emplace(enemyId, nemesis);
            if (finish==false && ((me.x-enemyX)*(me.x-enemyX) + (me.y-enemyY)*(me.y-enemyY)) <3000*3000){
                cerr << "AAAAAAAAAAAAAAAAAAAAAAA"<< endl;
                cout << "SHOOT "<< enemyId << endl;
                finish=true;
                
            }
        }
        
        
        // Write an action using cout. DON'T FORGET THE "<< endl"
        // To debug: cerr << "Debug messages..." << endl;
        if(enemyCount && finish==false) 
        {
            cout << "SHOOT "<< enemyId << endl;
        }
        else 
        {
            cout << "MOVE " << dataX << " " << dataY << endl; 
        }
        //cout << "MOVE 8000 4500" << endl; // MOVE x y or SHOOT id
    }
