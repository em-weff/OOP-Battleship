#include <string>
#include <vector>
#include "point.cpp"
using namespace std;

class Ship{
  private:
    int size;
    char orientation;
    bool sunk;
    string shipType;
    char boardSymbol;
    vector<Point> location;
  public:
    Ship();
    Ship(char orient, string name, int size, vector<Point> location);

    void setSunk(bool condition);
    void setBoardSymbol(char set);

    bool getSunk();
    int getSize();
    vector<Point> getLocation();
    char getOrientation();
    char getBoardSymbol();
    string getShipType();

    bool hit(Point locationToCheck);
};