#include <iostream>
#include <map>
using namespace std;
//boolean Layout = false;
enum Direction {North, South, East, West};//An Enummeration function having different Directions of the rooms.

//MapSite abstraction having Enter as it's polymorphic function.
class MapSite {
public:
virtual void Enter() = 0;
};

// Room class inherits from MapSite and has Room Number, Getters/Setters, SetSide and also Room constructor.
class Room : public MapSite {
private:
    MapSite* sides[4];
    int roomNumber;
public:
    Room(int roomNo){
    roomNumber = roomNo;
    }
    MapSite* GetSide(Direction d) const{
    return sides[d];
    }
    int GetRoomNo() const{
    return roomNumber;
    };
    void SetSide(Direction d, MapSite* m){
    sides[d] = m;
    }
    virtual void Enter()
    {
        std::cout<<"You have entered room: "<< roomNumber<<endl;
    }
};

//EnchantedRoom class inherits from Room and has Enchanted Room in it.
class EnchantedRoom : public Room {
public: EnchantedRoom(int roomNo);
virtual void Enter(){
std::cout<<"You have entered a enchanted room."<<endl;
}
};

//BombRoom class inherits from Room and has a Bomb inside the Room.
class BombRoom : public Room {
public: BombRoom(int roomNo);
virtual void Enter(){
std::cout<<"You have entered a room with a bomb."<<endl;
}
};

// Door class inherits from MapSite and has Room Numbers to which are connected, from which room to which room the door is connected.
class Door : public MapSite {
private:
    Room* room1;
    Room* room2;
    bool isOpen = false;
public:
    Door(Room* room_1, Room* room_2){
        room1 = room_1;
        room2 = room_2;
    }
    virtual void Enter(){
        if(isOpen){
             std::cout<<"You have passed through this door "<<endl;
        } else {
            std::cout<<"This door needs to be opened before passing through it. "<<endl;
        }
    }
    Room* OtherSideFrom(Room* room){
        if(room == room1){
            return room2;
        } else if(room == room2){
            return room1;
        } else {return 0;}
    }
};

//EnchantedDoor class inherits from Door and has Enchanted Door in it.
class EnchantedDoor : public Door {
public:
    EnchantedDoor(Room* room_1, Room* room_2);
    virtual void Enter(){
    std::cout<<"This is an Enchanted Door."<<endl;
    }
};

//BombDoor class inherits from Door and has a Door with a bomb attached to it.
class BombDoor : public Door {
public:
    BombDoor(Room* room_1, Room* room_2);
    virtual void Enter(){
    std::cout<<"This is a Door with a bomb attached to it."<<endl;
    }
};

//GlassDoor class inherits from Door and has Glass Door in it.
class GlassDoor : public Door {
public:
    GlassDoor(Room* room_1, Room* room_2);
    virtual void Enter(){
    std::cout<<"This is a Glass Door."<<endl;
    }
};

//Maze class has the AddRoom function to add rooms to a maze.
class Maze {
private:
    map<int, Room*> rooms;
public:
    Maze(){};
void AddRoom(Room* h){
 rooms[h->GetRoomNo()] = h;
}
Room* RoomNo(Room* j){
return rooms[j->GetRoomNo()];
}
};

//Maze Abstract Factory which has the MakeMaze, MakeRoom, MakeDoor functions in it.
 class MazeFactory{
public:
MazeFactory(){};
virtual Maze* MakeMaze() const {return new Maze; }
virtual Room* MakeRoom (int n) const{ return new Room (n); }
virtual Door* MakeDoor(Room *r1, Room *r2) const{ return new Door ( r1, r2 ); }
};

//Enchanted Maze Factory class inherits from MazeFactory and has MakeRoom, which creates an Enchanted Room, MakeDoor, which creates an Enchanted Door in it.
class EnchantedMazeFactory :  public MazeFactory{
private: int nroom;
public:
    EnchantedMazeFactory(int RoomNo){nroom = RoomNo;}
virtual Room* MakeRoom(int n) const{ return new EnchantedRoom(n); }
virtual Door* MakeDoor(Room* r1, Room* r2 ) const{ return new EnchantedDoor( r1, r2); }
};

//Bomb Maze Factory class inherits from MazeFactory and has MakeRoom, which creates a Bomb Room, MakeDoor, which creates a Bomb Door in it.
class BombMazeFactory :  public MazeFactory{
public:
    BombMazeFactory(){};
virtual Room* MakeRoom(int n) const{ return new BombRoom(n); }
virtual Door* MakeDoor(Room* r1, Room* r2 ) const{ return new BombDoor( r1, r2); }
};

//BombEnchanted Maze Factory class inherits from MazeFactory and has MakeRoom, which creates a Bomb Room, MakeDoor, which creates an Enchanted Door in it.
class BombEnchantedMazeFactory :  public MazeFactory{
public:
    BombEnchantedMazeFactory(){};
virtual Room* MakeRoom(int n) const{ return new BombRoom(n); }
virtual Door* MakeDoor(Room* r1, Room* r2 ) const{ return new EnchantedDoor( r1, r2); }
};

//EnchantedBomb Maze Factory class inherits from MazeFactory and has MakeRoom, which creates an Enchanted Room, MakeDoor, which creates a Bomb Door in it.
class EnchantedBombMazeFactory :  public MazeFactory{
public:
    EnchantedBombMazeFactory(){};
virtual Room* MakeRoom(int n) const{ return new EnchantedRoom(n); }
virtual Door* MakeDoor(Room* r1, Room* r2 ) const{ return new BombDoor( r1, r2); }
};

//EnchantedGlass Maze Factory class inherits from MazeFactory and has MakeRoom, which creates an Enchanted Room, MakeDoor, which creates a Glass Door in it.
class EnchantedGlassMazeFactory :  public MazeFactory{
public:
    EnchantedGlassMazeFactory(){};
virtual Room* MakeRoom(int n) const{ return new EnchantedRoom(n); }
virtual Door* MakeDoor(Room* r1, Room* r2 ) const{ return new GlassDoor( r1, r2); }
};

//BombGlass Maze Factory class inherits from MazeFactory and has MakeRoom, which creates a Bomb Room, MakeDoor, which creates a Glass Door in it.
class BombGlassMazeFactory :  public MazeFactory{
public:
    BombGlassMazeFactory(){};
virtual Room* MakeRoom(int n) const{ return new BombRoom(n); }
virtual Door* MakeDoor(Room* r1, Room* r2 ) const{ return new GlassDoor( r1, r2); }
};

// MazeGame class having CreateMaze function.
class MazeGame{
private:

public:
        MazeGame(){};
   Maze* CreateMaze(MazeFactory* factory);
};

//MazeGame creates a Maze and gets and sets rooms/doors and assigns them directions of doors.
Maze* MazeGame::CreateMaze (MazeFactory* factory){
Maze* aMaze = factory->MakeMaze();
Room* r1 = factory->MakeRoom(1);
Room* r2 = factory->MakeRoom(2);
Door* aDoor = factory->MakeDoor ( r1, r2);
aMaze->AddRoom(r1);
aMaze->AddRoom(r2);
r1->SetSide(North, aDoor);
r1->SetSide(East, aDoor);
r1->SetSide(South, aDoor);
r1->SetSide(West, aDoor);
r2->SetSide(North, aDoor);
r2->SetSide(East, aDoor);
r2->SetSide(South, aDoor);
r2->SetSide(West, aDoor);
std::cout<<"You have created a Maze"<<endl;
return aMaze;
};

//Main function through which the entire code runs from.
int main(){
    int number_room, choice;
    MazeGame* game = new MazeGame();
    MazeFactory* factory = new MazeFactory();
    game->CreateMaze(factory);

return 0;
}
