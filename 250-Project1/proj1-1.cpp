#include <iostream>
#include <map>
using namespace std;
bool Layout = false;
enum Direction {North, South, East, West};//An Enum function having different Directions of the rooms.

//MapSite abstraction having Enter as it's polymorphic function.
class MapSite {
public:
virtual void Enter() = 0;//Polymorphic function Enter()
};

// Room class inherits from MapSite and has Room Number, Getters/Setters, SetSide and also Room constructor.
class Room : public MapSite {
private:
    MapSite* sides[4];
    int roomNumber;
public:// Constructor assigns the room number
    Room(int roomNo){
    roomNumber = roomNo;
    std::cout<<"\nYou have created a new room: "<<roomNumber<<endl;
    }
    MapSite* GetSide(Direction d) const{//GetSide Direction.
    return sides[d];
    }
    int GetRoomNo() const{//Get Room Number
    return roomNumber;
    };
    void SetSide(Direction d, MapSite* m){//SetSide
    sides[d] = m;
    }
    virtual void Enter()
    {
        std::cout<<"You have entered room: "<< roomNumber<<endl;
    }
};

//EnchantedRoom class inherits from Room and has Enchanted Room in it.
class EnchantedRoom : public Room {
private: int rooms_n;
public: EnchantedRoom(int roomNo);//Enchanted Room
virtual void Enter(){
std::cout<<"You have entered an enchanted room."<<endl;
}
};

//BombRoom class inherits from Room and has a Bomb inside the Room.
class BombRoom : public Room {
public: BombRoom(int roomNo);//Bomb in the Room
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
    Door(Room* room_1, Room* room_2){//Door connecting 2 rooms.
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
    Room* OtherSideFrom(Room* room){//Otherside of a room
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
    EnchantedDoor(Room* room_1, Room* room_2);// Enchanted Door
    virtual void Enter(){
    std::cout<<"This is an Enchanted Door."<<endl;
    }
};

//BombDoor class inherits from Door and has a Door with a bomb attached to it.
class BombDoor : public Door {
public:
    BombDoor(Room* room_1, Room* room_2);// Bomb attached to a door
    virtual void Enter(){
    std::cout<<"This is a Door with a bomb attached to it."<<endl;
    }
};

//GlassDoor class inherits from Door and has Glass Door in it.
class GlassDoor : public Door {
public:
    GlassDoor(Room* room_1, Room* room_2);// Glass Door
    virtual void Enter(){
    std::cout<<"This is a Glass Door."<<endl;
    }
};

//Maze class has the AddRoom function to add rooms to a maze.
class Maze {
private:
    map<int, Room*> rooms;// Map objects of a room.

public:
    Maze(){};
    Room* m[10][10];
void AddRoom(Room* h){// Add room
 rooms[h->GetRoomNo()] = h;
 h->Enter();
}
Room* RoomNo(Room* j){
return rooms[j->GetRoomNo()];

}
};

//Maze Abstract Factory which has the MakeMaze, MakeRoom, MakeDoor functions in it.
 class MazeFactory{
public:
MazeFactory(){};
virtual Maze* MakeMaze() const {return new Maze; }// Make Maze
virtual Room* MakeRoom (int n) const{ return new Room(n); }// Make Room
virtual Door* MakeDoor(Room *r1, Room *r2) const{ return new Door ( r1, r2 ); }// Make Door
};

//Enchanted Maze Factory class inherits from MazeFactory and has MakeRoom, which creates an Enchanted Room, MakeDoor, which creates an Enchanted Door in it.
class EnchantedMazeFactory :  public MazeFactory{
private: int nroom;
public:
    EnchantedMazeFactory(){}// Enchanted Maze Factory
virtual Maze* MakeMaze() const {return new Maze; }// Make Maze
virtual Room* MakeRoom(int n) const{ return new EnchantedRoom(n); }
virtual Door* MakeDoor(Room* r1, Room* r2 ) const{ return new EnchantedDoor( r1, r2); }
};

//Bomb Maze Factory class inherits from MazeFactory and has MakeRoom, which creates a Bomb Room, MakeDoor, which creates a Bomb Door in it.
class BombMazeFactory :  public MazeFactory{
public:
    BombMazeFactory(){};// Bomb Maze Factory
virtual Room* MakeRoom(int n) const{ return new BombRoom(n); }
virtual Door* MakeDoor(Room* r1, Room* r2 ) const{ return new BombDoor( r1, r2); }
};

//BombEnchanted Maze Factory class inherits from MazeFactory and has MakeRoom, which creates a Bomb Room, MakeDoor, which creates an Enchanted Door in it.
class BombEnchantedMazeFactory :  public MazeFactory{
public:
    BombEnchantedMazeFactory(){};// Bomb Enchanted Maze Factory
virtual Room* MakeRoom(int n) const{ return new BombRoom(n); }
virtual Door* MakeDoor(Room* r1, Room* r2 ) const{ return new EnchantedDoor( r1, r2); }
};

//EnchantedBomb Maze Factory class inherits from MazeFactory and has MakeRoom, which creates an Enchanted Room, MakeDoor, which creates a Bomb Door in it.
class EnchantedBombMazeFactory :  public MazeFactory{
    private: int norm;
public:
    EnchantedBombMazeFactory(int numrm){norm = numrm;};// Enchanted Bomb Maze Factory
virtual Room* MakeRoom(int n) const{ return new EnchantedRoom(norm); }
virtual Door* MakeDoor(Room* r1, Room* r2 ) const{ return new BombDoor( r1, r2); }
};

//EnchantedGlass Maze Factory class inherits from MazeFactory and has MakeRoom, which creates an Enchanted Room, MakeDoor, which creates a Glass Door in it.
class EnchantedGlassMazeFactory :  public MazeFactory{
public:
    EnchantedGlassMazeFactory(){};// Enchanted Glass Maze Factory
virtual Room* MakeRoom(int n) const{ return new EnchantedRoom(n); }
virtual Door* MakeDoor(Room* r1, Room* r2 ) const{ return new GlassDoor( r1, r2); }
};

//BombGlass Maze Factory class inherits from MazeFactory and has MakeRoom, which creates a Bomb Room, MakeDoor, which creates a Glass Door in it.
class BombGlassMazeFactory :  public MazeFactory{
public:
    BombGlassMazeFactory(){};// Bomb Glass Maze Factory
virtual Room* MakeRoom(int n) const{ return new BombRoom(n); }
virtual Door* MakeDoor(Room* r1, Room* r2 ) const{ return new GlassDoor( r1, r2); }
};

// MazeGame class having CreateMaze function.
class MazeGame{
private:
int numroom;
Room* matrix[10][10];
Door* aDoor[10][10];
public:
        MazeGame(int RoomNos){
            numroom=RoomNos;
        }
        int l = (numroom * 2) + 1;
   Maze* CreateMaze(MazeFactory* factory);
};

//MazeGame creates a Maze and gets and sets rooms/doors and assigns them directions of doors.
Maze* MazeGame::CreateMaze (MazeFactory* factory){
Maze* aMaze = factory->MakeMaze();
for(int i = 0; i<numroom; i++){
    for(int j = 0; j<numroom; j++){
        aMaze->m[i][j] = {(factory->MakeRoom(j))};
        aMaze->AddRoom(aMaze->m[i][j]);
    }
    for(int j = 0; j<numroom-1;j++){
        Door* aDoor[i][j] = {factory->MakeDoor(aMaze->m[i][j],aMaze->m[i][j+1])};
    }
}

//Layout 1 logic taking in a Matrix of objects of rooms in Maze class.
if(Layout==false){
    for(int i = 0; i<numroom; i++){
        for(int j = 0; j<numroom;j++){
            aMaze->m[i][j]->SetSide(North, aDoor[i][j]);
            aMaze->m[i][j]->SetSide(East, aDoor[i][j]);
            aMaze->m[i][j]->SetSide(South, aDoor[i][j]);
            aMaze->m[i][j]->SetSide(West, aDoor[i][j]);
        }
    }
}
//Layout 2 logic taking in a Matrix of objects of rooms in Maze class.
else{
    for(int i = 0; i<numroom; i=i+2){
        for(int j = 1; j<numroom; j=j+2){
            aMaze->m[i][j]->SetSide(East, aDoor[i][j]);
            aMaze->m[i][j]->SetSide(West, aDoor[i][j]);
        }
    }
    for(int i = 1; i<numroom; i=i+2){
        for(int j = 0; j<numroom; j=j+2){
            aMaze->m[i][j]->SetSide(North, aDoor[i][j]);
            aMaze->m[i][j]->SetSide(South, aDoor[i][j]);
        }
    }
}
std::cout<<"\nYou have created a Maze"<<endl;
return aMaze;
};

//To print the Layout of the Maze
void print(int n, bool c){
int m = (n * 2) + 1;
if(c == false){
    for(int i = 1; i < m + 1; i ++){
            for(int j = 1; j < m + 1; j++){
                if(i%2 == 0){
                    if(j%2 == 0){
                        std::cout<<" ";
                    }else {
                        std::cout<<"|";
                    }
                }else {
                    if(j%2 == 0){
                        std::cout<<"-";
                    }else {
                        std::cout<<" ";
                    }
                }
            }
            std::cout<<endl;
        }
        std::cout<<"\nThis is the Maze where all rooms have doors."<<endl;
} else{
for(int i = 1; i < m + 1; i ++){
            for(int j = 1; j < m + 1; j++){
                if(i%2 == 0){
                    if(j%2 == 0){
                        std::cout<<" ";
                    }else {
                        if(j==1||j==m){
                        std::cout<<"|";
                        } else if(i%4!=0){
                        std::cout<<":";
                        } else{
                            std::cout<<"|";
                        }
                    }
                }else {
                    if(j%2 == 0){
                        if(i==1||i==m){
                        std::cout<<"-";
                        } else if(j%4!=0){
                        std::cout<<"^";
                        } else{
                        std::cout<<"-";
                        }
                    }else {
                        std::cout<<" ";
                    }
                }
            }
            std::cout<<endl;
        }
        std::cout<<"\nThis is the Maze where for each odd row, each even Room has WEST and EAST doors. For each even row, each odd Room has NORTH and SOUTH doors."<<endl;
}
}

//Main function through which the entire code runs from.
int main(){
    int number_room, choice, m;
    std::cout<<"Enter the number of rooms:"<<endl;
    std::cin>>number_room;
    std::cout<<"Enter the layout from the choice below\n 1. Layout 1 - All rooms have 4 doors \n 2. For each odd row, each even Room has WEST and EAST doors. For each even row, each odd Room has NORTH and SOUTH doors. "<<endl;
    std::cin>>choice;
    m = (number_room * 2) + 1;
    if(choice == 1){
        Layout = false;
    } else if(choice == 2){
        Layout = true;
    } else{
        std::cout<<"Please retry again."<<endl;
    }
    print(number_room, Layout);
    MazeGame* game = new MazeGame(number_room);
    MazeFactory* factory = new MazeFactory();
    game->CreateMaze(factory);
return 0;
}
