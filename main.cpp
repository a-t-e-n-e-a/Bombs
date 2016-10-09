#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <cfloat>
#include <list>

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

coordinates& getPosition(coordinates origin, int nbTours, coordinates cible){
    int EN_MOVE_RADIUS=500;
	coordinates result=coordinates(-1,-1);
	if (result.x == origin.x) {
	  result.x = origin.x;
	  result.y = origin.y > cible.y ? origin.y - EN_MOVE_RADIUS : origin.y + EN_MOVE_RADIUS;
	} 
	else {
	  double m =  1.0*(cible.y - origin.y) /  (cible.x - origin.x);
	  double c = 500.0 / (sqrt(1 + m*m));
	  result.x = floor(origin.x + c);
	    if (abs(origin.x - cible.x) < abs(result.x - cible.x)) {
	      result.x = floor(origin.x - c);
	    }
	    result.y = floor((result.x - origin.x) * m + origin.y);
	  }
	  cerr << "*** New pos is : " << result.x << " " << result.y;
	  return result;
};

double distance(coordinates c0, enemy c1){
	return sqrt((c0.x-c1.x)*(c0.x-c1.x)+(c0.y-c1.y)*(c0.y-c1.y));
}

list<int>& dangerousEnemies(coordinates me, map<int, enemy> &enemis){
    list<int> result;
    int dist;
    for (std::map<int,enemy>::iterator enemy=enemis.begin(); enemy!=enemis.end(); ++enemy){
    		dist=distance(me,enemy->second);
    		if (dist<3000) {
    		    result.push_back(enemy->first);
    		    cerr << "enemy : " << enemy->first << " is too close" << endl;
    		}
    }
}

map<int,int> & findTargetsET(map<int, enemy> &enemis, map<int, coordinates> &dataPoints){
	map<int,int> resultET;
	double dist;
	for (std::map<int,enemy>::iterator enemy=enemis.begin(); enemy!=enemis.end(); ++enemy){
		double min = DBL_MAX;
		int id = -1;
		for (std::map<int,coordinates>::iterator data=dataPoints.begin(); data!=dataPoints.end(); ++data){
			dist=distance(data->second,enemy->second);
			if(dist < min) 
			{
			    min=dist;
			    id = data->first;
			}
		}
		resultET.emplace(enemy->first,id);
		cerr << "enemy : " <<enemy->first << " cible : " <<id << endl;
	}
	
}

bool runAway(list<int> &killers, map<int, enemy> &enemis, map<int,int> &ET,  map<int, coordinates> &dataPoints, coordinates me){
	map<int,coordinates> nextKillerPositions;
	for(int killer : killers){
		coordinates nextP;
		coordinates actualP(enemis.at(killer).x,enemis.at(killer).y);
		coordinates enemy(enemis.at(killer).x,enemis.at(killer).y);
		nextP=getPosition(enemy, 1, dataPoints.at(ET.at(killer)) );
		double dist=distance(me,enemis.at(killer));
		if (dist < 2000){
			nextKillerPositions.emplace(killer,nextP);
		}
	}
	if (nextKillerPositions.empty()) return false;
	else if (nextKillerPositions.size()<2 )//&& ) add dps data
	{
		cout << "SHOOT "<< nextKillerPositions.begin()->first << endl;
		return true;
	}
	else {
	    cerr << "I'm dead" << endl;/*
		int x=0;
		int y=0;
		int i=0;
		for(std::map<int,coordinates>::iterator killer=nextKillerPosition.begin(); killer!=nextKillerPosition.end(); ++killer){
			x+=(killer->second).x;
			y+=(killer->second).y;
			i++;
		}
		x=x/i;
		y=y/i;
		coordinates* destiny;
		//destiny=&getPosition(me, 2, coordinates cible){
		//cout "MOVE" <<*/ 
	}
}

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
        dataPoints.clear();
        for (int i = 0; i < dataCount; i++) {
            cin >> dataId >> dataX >> dataY; cin.ignore();
            coordinates coord = coordinates(dataX, dataY);
            dataPoints.emplace(dataId, coord);
        }
        int enemyCount;
        int enemyId;
        cin >> enemyCount; cin.ignore();
        bool finish=false;
        enemis.clear();
        for (int i = 0; i < enemyCount; i++) {
            int enemyX;
            int enemyY;
            int enemyLife;
            cin >> enemyId >> enemyX >> enemyY >> enemyLife; cin.ignore();
			enemy nemesis=enemy(enemyX, enemyY, enemyLife);
            enemis.emplace(enemyId, nemesis);
            /*if (finish==false && ((me.x-enemyX)*(me.x-enemyX) + (me.y-enemyY)*(me.y-enemyY)) <3000*3000){
                cerr << "AAAAAAAAAAAAAAAAAAAAAAA"<< endl;
                cout << "SHOOT "<< enemyId << endl;
                finish=true;
                
            }*/
        }
        map<int,int> enemyTarget;
        enemyTarget=findTargetsET(enemis, dataPoints);
        list<int> danger;
        danger=dangerousEnemies(me, enemis);
        finish=runAway(danger, enemis, enemyTarget, dataPoints, me);
        
        // Write an action using cout. DON'T FORGET THE "<< endl"
        // To debug: cerr << "Debug messages..." << endl;
        if(enemyCount && finish==false) 
        {
            cout << "SHOOT "<< enemyId << endl;
        }
        else if (finish==false)
        {
            cout << "MOVE " << dataX << " " << dataY << endl; 
        }
        //cout << "MOVE 8000 4500" << endl; // MOVE x y or SHOOT id
    }
}
