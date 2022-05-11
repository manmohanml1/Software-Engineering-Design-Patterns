
#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

class Component;
class Observable{//Interface Observable which acts as Subject
public:
    virtual void attach(Component* c){}// We attach observers which we want to keep track of. Here the observers are in Component.
    virtual void detach(const int index){}//We detach using index number of the list of observers.
    virtual void notify(){}
};
class Component: public Observable// We have this as an interface(Component) for creating composite pattern and also this as an observer.
{
private:
    std::vector<Component*> comps;//To maintain a list of observers
    std::string Name;// To give name to the hierarchy
public:
  virtual ~Component() {}

  virtual Component *getChild( int )
  {
    return 0;
  }
  virtual void attach( Component* coms )//We attach observers which we want to keep track of. Here the observers are in Component.
  {
    comps.push_back(coms);// We add an observer the list of observers.
  }
  virtual void detach( const int index )//We detach using index number of the list of observers.
  {
    comps.erase( comps.begin() + index );// We remove an observer the list of observers.
  }
  virtual void add( Component * ) { /* ... */ }// We add a new sub-node either leaf or composite using this.
  virtual void remove( int ) { /* ... */ }// We remove an existing sub-node either leaf or composite using this.
  virtual void notify(){ // We notify the updates to the list of observers.
    for ( unsigned int i = 0; i < comps.size(); i++ )
    {
      comps.at( i )->update( this );
    }
  }
  virtual void operation() = 0;// We perform some operations.
  virtual void update(Component* c){}// We display updates from this.
  virtual std::string getname(){// We display the name of this object call.
        return Name;
  }
};

/*
 * Composite
 * defines behavior of the components having children
 * and store child components
 */
class Composite : public Component // Acts as a child to component and is used for making hierarchy and also used as Subject and Observer.
{
public:
  ~Composite()//Destructor to remove Composite object
  {
    for ( unsigned int i = 0; i < children.size(); i++ )
    {
      delete children[ i ];
    }
  }

  Composite(std::string s){
      Name = s;
      std::cout<<Name<<endl;// Displays the name of the Composite object created in Hierarchy.
  }

  Component *getChild( const unsigned int index )// It is used to get child index number from list of component objects.
  {
    return children[ index ];
  }

  void add( Component* component )// Adds new leaf or sub-node.
  {
    children.push_back( component );// We add the new child to the list of component objects.
  }

  void remove( const unsigned int index )// We remove the exsisting child from the list of component objects.
  {
    Component *child = children[ index ];
    children.erase( children.begin() + index );
    delete child;
  }

  void operation()// We perform some operations in all the children in the list of component objects.
  {
    for ( unsigned int i = 0; i < children.size(); i++ )
    {
      children[ i ]->operation();
    }
  }
  virtual void update(Component* c){// We use this function for printing out the information gotten by ListServers.
  std::cout<<"\nThis is a message from ListServer received by: "<<Name<<endl;
  }
  virtual void attach( Component* coms )// We use this function to observe different observers.
  {
    comps.push_back(coms);
  }
  virtual void detach( const int index )// We use this function to remove observing an observer.
  {
    comps.erase( comps.begin() + index );
  }
  virtual void notify(){// We notify the updates to the list of observers.
    for ( unsigned int i = 0; i < comps.size(); i++ )
    {
      comps.at( i )->update( this );
    }
  }
  std::string getname(){// We display the name of this object call.
  return Name;
  }
  std::vector<Component*> children;// We use this to store newly create child nodes. (List of Component objects)
  std::vector<Component*> comps;// We use this as a list of observers.(List of Component objects)
private:

  std::string Name;// We store the name of the nodes in hierarchy.
};

/*
 * Leaf
 * defines the behavior for the elements in the composition,
 * it has no children
 */
class Leaf : public Component// Leaf of an tree in hierarchy.
{
public:
  Leaf(std::string s){// We use it to store the name of the Leaf node.
  Name = s;
  std::cout<<Name<<endl;// We display the node name.
  }
  Leaf(){
  std::cout<<"\n Created"<<endl;
  }
  ~Leaf() {}

  virtual void operation()// We perform some operation on the Leaf.
  {
    std::cout << "Leaf "<< id <<" operation" << std::endl;
  }
  std::string getname(){// We use it to get the name of the leaf node.
  return Name;
  }
private:
  int id;
  std::string Name;
};


int main()
{
  int choice = 0, chL = 0, chN = 0, chS = 0;// we use these for choices in the menu.
  int Cno = 0, Dno = 0, Fno = 0, Sno = 0;// We use these for keeping an counter for College Name, Department Name, Faculty Name, and Student Name.
  bool m = true;// We use this to keep the menu always running.
  std::vector<Component*> cmps, dmps, fmps, smps;// We use this to create a Dynamic List of different Colleges, Departments, Faculty, and Student records.
  string Dname, Mname, Cname, Fname, Sname;// We use this string to store names of different Colleges, Departments, Faculty, and Student from client.
  unordered_map<std::string,int> nameC, nameD, nameF, nameS;// We use this to store the different Colleges, Departments, Faculty, and Student names as the key and their values.
  Component* composite = new Composite("FS");// We use this object to store our University and as the root of our hierarchy.

  while(m){
  std::cout<<"\n Choose the option from 1) Do you want to create a new College?"<<endl;
  std::cout<<" 2) Do you want to create a Department in an existing college?"<<endl;
  std::cout<<" 3)Do you want to add members to an existing Department?"<<endl;
  std::cout<<" 4)Do you want to display the FS hierarchy"<<endl;
  std::cout<<" 5)Do you want to subscribe to the existing ListServers?"<<endl;
  std::cout<<" 6)Do you want to unsubscribe to the existing ListServers?"<<endl;
  std::cout<<" 7)Do you want to remove existing Colleges, Departments, Faculties or Students?"<<endl;
  std::cout<<" 10)Exit"<<endl;
  std::cin>>choice;
  if(choice==1){// To create a new college.
    std::cout<<"\n Enter the name of the College you want to add:";
    std::cin>>Cname;
    nameC[Cname]=Cno;// We store the college name in the unorderedmap
    std::cout<<"\n College Name:";
    cmps.push_back(new Composite(Cname));// we create an object of type Composite and store the name of College in it.
    composite->add(cmps[Cno]);// We add it in the tree as a sub-node of FS.
    Cno++;// We increase the counter to maintain the number of colleges we create.

  }else if(choice==2){
    std::cout<<"\n Enter the name of the College you want to add the department in:";
    std::cin>>Cname;
    std::cout<<"\n Enter the name of the Department you want to add:";
    std::cin>>Dname;
    nameD[Dname] = Dno;// We store the department name in the unorderedmap
    std::cout<<"\n Department Name:";
    dmps.push_back(new Composite(Dname));// we create an object of type Department and store the name of Department in it.
    cmps[nameC[Cname]]->add(dmps[Dno]);// We add it in the tree as a sub-node of the college.
    Dno++;// We increase the counter to maintain the number of Departments we create.

  }else if(choice==3){
    std::cout<<"\n Enter the name of the Department you want to add the member in:";
    std::cin>>Dname;
    std::cout<<"\n Do you want to enter a member who is a 1)faculty or 2)student?";
    std::cin>>chS;
    if(chS==1){
        std::cout<<"\n Enter the name of the faculty:";
        std::cin>>Fname;
        nameF[Fname]=Fno;// We store the Faculty name in the unorderedmap
        std::cout<<"\n Faculty Name:";
        fmps.push_back(new Composite(Fname));// we create an object of type faculty and store the name of faculty in it.
        dmps[nameD[Dname]]->add(fmps[Fno]);// We add it in the tree as a sub-node of the department.
        Fno++;// We increase the counter to maintain the number of faculties we create.

    } else if(chS==2){
        std::cout<<"\n Enter the name of the student:";
        std::cin>>Sname;
        nameS[Sname]=Sno;// We store the Fstudent name in the unorderedmap
        std::cout<<"\n Student Name:";
        smps.push_back(new Composite(Sname));// we create an object of type student and store the name of student in it.
        dmps[nameD[Dname]]->add(smps[Sno]);// We add it in the tree as a sub-node of the department.
        Sno++;// We increase the counter to maintain the number of students we create.

    }
  }else if(choice==4)// Use for Displaying the hierarchy.
  {
      std::cout<<"\nUniversity Name:"<<composite->getname()<<endl;
      if(Cno>0){
        for(int i = 0; i< Cno; i++){
          std::cout<<" College "<<i+1<<" Name:"<<cmps[i]->getname()<<endl;
        }
      }
      if(Dno>0){
          for(int j = 0; j< Dno; j++){
            std::cout<<" Department "<<j+1<<" Name:"<<dmps[j]->getname()<<endl;
          }
      }
      if(Fno>0){
        for(int k = 0; k< Fno; k++){
          std::cout<<" Faculty "<<k+1<<" Name:"<<fmps[k]->getname()<<endl;
        }
      }
      if(Sno>0){
        for(int l = 0; l< Sno; l++){
            std::cout<<" Student "<<l+1<<" Name:"<<smps[l]->getname()<<endl;
        }
      }
  }else if(choice==5){// Used to subscribe to ListServers.
        std::cout<<"\n Choose the ListServers you want to subscribe to: 1) FS ListServers 2) College ListServers 3) Department ListServers";
        std::cin>>chL;
        if(chL==1){// Used to subscribe to FS ListServers.
            if(Cno>0){
                for(int i = 0; i< Cno; i++){
                    composite->attach(cmps[i]);// Adding colleges to FS ListServer.
                }
              }
              if(Dno>0){
                  for(int j = 0; j< Dno; j++){
                    composite->attach(dmps[j]);// Adding departments to FS ListServer.
                  }
              }
              if(Fno>0){
                for(int k = 0; k< Fno; k++){
                  composite->attach(fmps[k]);// Adding faculties to FS ListServer.
                }
              }
              if(Sno>0){
                for(int l = 0; l< Sno; l++){
                    composite->attach(smps[l]);// Adding students to FS ListServer.
                }
              }
            std::cout<<"\n All the Colleges, Departments, Faculties and Students are now subscribed to the FS ListServer."<<endl;
            std::cout<<"\n Do you want to notify this? 1) Yes 2)No"<<endl;
            std::cin>>chN;
            if(chN==1){
                composite->notify();// Display all the subscribed members in FS ListServers.
                chN=0;
            } else{
                chN=0;
            }
        } else if(chL==2){// Used to subscribe to College ListServers.
            std::cout<<"\n Enter the name of the College you want to add the ListServer for:";
            std::cin>>Cname;
              if(Dno>0){
                  for(int j = 0; j< Dno; j++){
                    cmps[nameC[Cname]]->attach(dmps[j]);// Adding departments to College ListServer.
                  }
              }
              if(Fno>0){
                for(int k = 0; k< Fno; k++){
                  cmps[nameC[Cname]]->attach(fmps[k]);// Adding faculties to College ListServer.
                }
              }
              if(Sno>0){
                for(int l = 0; l< Sno; l++){
                    cmps[nameC[Cname]]->attach(smps[l]);// Adding students to College ListServer.
                }
              }
            std::cout<<"\n All the Departments, Faculties and Students are now subscribed to the "<<Cname<<" ListServer."<<endl;
            std::cout<<"\n Do you want to notify this? 1) Yes 2)No"<<endl;
            std::cin>>chN;
            if(chN==1){
                cmps[nameC[Cname]]->notify();
                chN=0;
            } else{
                chN=0;
            }
        }else if(chL==3){// Used to subscribe to Department ListServers.
            std::cout<<"\n Enter the name of the Department you want to add the ListServer for:";
            std::cin>>Dname;
              if(Fno>0){
                for(int k = 0; k< Fno; k++){
                  dmps[nameD[Dname]]->attach(fmps[k]);// Adding faculties to Department ListServer.
                }
              }
              if(Sno>0){
                for(int l = 0; l< Sno; l++){
                    dmps[nameD[Dname]]->attach(smps[l]);// Adding students to Department ListServer.
                }
              }
            std::cout<<"\n All the Faculties and Students are now subscribed to the "<<Dname<<" ListServer."<<endl;
            std::cout<<"\n Do you want to notify this? 1) Yes 2)No"<<endl;
            std::cin>>chN;
            if(chN==1){
                dmps[nameD[Dname]]->notify();
                chN=0;
            } else{
                chN=0;
            }
        }else{
            std::cout<<"\n Wrong choice"<<endl;
        }
  }else if(choice==6){// Used to unsubscribe from ListServers.
        std::cout<<"\n Choose the ListServers you want to unsubscribe to: 1) FS ListServers 2) College ListServers 3) Department ListServers";
        std::cin>>chL;
        if(chL==1){//Unsubscribe to FS ListServer
                std::cout<<"\n Choose either 1)faculty or 2)student who wants to unsubscribe. "<<endl;
                std::cin>>chS;
            if(chS==1){// Unsubscribe a faculty
                std::cout<<"\n Enter the name of the Faculty who wants to unsubscribe:"<<endl;
                std::cin>>Fname;
                composite->detach(nameF[Fname]+Cno+Dno);
                std::cout<<Fname<<" is now unsubscribed to the FS ListServer."<<endl;
                std::cout<<"\n Do you want to check by seeing who are subscribed to this ListServer? 1) Yes 2)No"<<endl;
                std::cin>>chN;
                if(chN==1){
                    composite->notify();
                    chN=0;
                } else{
                    chN=0;
                }
            } else if(chS==2){// Unsubscribe a student
                std::cout<<"\n Enter the name of the Student who wants to unsubscribe:"<<endl;
                std::cin>>Sname;
                composite->detach(nameS[Sname]+Cno+Dno+Fno);
                std::cout<<Sname<<" is now unsubscribed to the FS ListServer."<<endl;
                std::cout<<"\n Do you want to check by seeing who are subscribed to this ListServer? 1) Yes 2)No"<<endl;
                std::cin>>chN;
                if(chN==1){
                    composite->notify();
                    chN=0;
                } else{
                    chN=0;
                }
            } else{
                std::cout<<"\n Wrong choice"<<endl;
            }
        } else if(chL==2){//Unsubscribe to College ListServer
                std::cout<<"\n Enter the name of the College ListServer from which you want to unsubscribe from:"<<endl;
                std::cin>>Cname;
                std::cout<<"\n Choose either 1)faculty or 2)student who wants to unsubscribe. "<<endl;
                std::cin>>chS;
            if(chS==1){// Unsubscribe a faculty
                std::cout<<"\n Enter the name of the Faculty who wants to unsubscribe:"<<endl;
                std::cin>>Fname;
                cmps[nameC[Cname]]->detach(nameF[Fname]+Dno);
                std::cout<<Fname<<" is now unsubscribed to the "<<Cname<<" ListServer."<<endl;
                std::cout<<"\n Do you want to check by seeing who are subscribed to this ListServer? 1) Yes 2)No"<<endl;
                std::cin>>chN;
                if(chN==1){
                    cmps[nameC[Cname]]->notify();
                    chN=0;
                } else{
                    chN=0;
                }
            } else if(chS==2){// Unsubscribe a student
                std::cout<<"\n Enter the name of the Student who wants to unsubscribe:"<<endl;
                std::cin>>Sname;
                cmps[nameC[Cname]]->detach(nameS[Sname]+Dno+Fno);
                std::cout<<Sname<<" is now unsubscribed to the "<<Cname<<" ListServer."<<endl;
                std::cout<<"\n Do you want to check by seeing who are subscribed to this ListServer? 1) Yes 2)No"<<endl;
                std::cin>>chN;
                if(chN==1){
                    cmps[nameC[Cname]]->notify();
                    chN=0;
                } else{
                    chN=0;
                }
            } else{
                std::cout<<"\n Wrong choice"<<endl;
            }
        }else if(chL==3){//Unsubscribe to Department ListServer
                std::cout<<"\n Enter the name of the Department ListServer from which you want to unsubscribe from:"<<endl;
                std::cin>>Dname;
                std::cout<<"\n Choose either 1)faculty or 2)student who wants to unsubscribe. "<<endl;
                std::cin>>chS;
                if(chS==1){// Unsubscribe a faculty
                    std::cout<<"\n Enter the name of the Faculty who wants to unsubscribe:"<<endl;
                    std::cin>>Fname;
                    dmps[nameD[Dname]]->detach(nameF[Fname]);
                    std::cout<<Fname<<" is now unsubscribed to the "<<Dname<<" ListServer."<<endl;
                    std::cout<<"\n Do you want to check by seeing who are subscribed to this ListServer? 1) Yes 2)No"<<endl;
                    std::cin>>chN;
                    if(chN==1){
                        dmps[nameD[Dname]]->notify();
                        chN=0;
                    } else{
                        chN=0;
                    }
                } else if(chS==2){// Unsubscribe a student
                    std::cout<<"\n Enter the name of the Student who wants to unsubscribe:"<<endl;
                    std::cin>>Sname;
                    dmps[nameD[Dname]]->detach(nameS[Sname]+Dno+Fno);
                    std::cout<<Sname<<" is now unsubscribed to the "<<Dname<<" ListServer."<<endl;
                    std::cout<<"\n Do you want to check by seeing who are subscribed to this ListServer? 1) Yes 2)No"<<endl;
                    std::cin>>chN;
                    if(chN==1){
                        dmps[nameD[Dname]]->notify();
                        chN=0;
                    } else{
                        chN=0;
                    }
                } else{
                    std::cout<<"\n Wrong choice"<<endl;
                }
        }else{
            std::cout<<"\n Wrong choice"<<endl;
        }
  }else if(choice==7){// Used to remove Department or Members.
    std::cout<<"\n Choose which you want to remove: 1)Department 2)Members"<<endl;
    std::cin>>chL;
    if(chL==1){
        std::cout<<"\n Enter the existing college you want to remove the department from:"<<endl;
        std::cin>>Cname;
        std::cout<<"\n Enter the existing department you want to remove:"<<endl;
        std::cin>>Dname;
        cmps[nameC[Cname]]->remove(nameD[Dname]);//Delete department from college
        dmps.erase(dmps.begin()+ nameD[Dname]);//Delete department from the list of department.
        composite->detach(nameD[Dname]+Cno);//Unsubscribe from FS ListServer
        cmps[nameC[Cname]]->detach(nameD[Dname]);//Unsubscribe from College ListServer
        std::cout<<Dname<<" is now removed from "<<Cname<<" College."<<endl;
        std::cout<<"\n Do you want to notify this to "<<Cname<<" ListServer? 1) Yes 2)No"<<endl;
        std::cin>>chN;
            if(chN==1){
                cmps[nameC[Cname]]->notify();
                chN=0;
            } else{
                chN=0;
            }
    }else if(chL==2){
        std::cout<<"\n Enter the existing department you want to remove members from:"<<endl;
        std::cin>>Dname;
        std::cout<<"\n Choose either the 1)Faculty 2)Student you want to remove:"<<endl;
        std::cin>>chS;
        if(chS==1){
            std::cout<<"\n Enter the name of the existing Faculty you want to remove:"<<endl;
            std::cin>>Fname;
            dmps[nameD[Dname]]->remove(nameF[Fname]);//Delete Faculty from department
            fmps.erase(fmps.begin()+ nameF[Fname]);//Delete Faculty from the list of Faculty
            composite->detach(nameF[Fname]+Cno+Dno);//Unsubscribe from FS ListServer
            dmps[nameD[Dname]]->detach(nameF[Fname]);//Unsubscribe from Department ListServer
            std::cout<<Fname<<" is now removed from "<<Dname<<" Department."<<endl;
            std::cout<<"\n Do you want to notify this to "<<Dname<<" ListServer? 1) Yes 2)No"<<endl;
            std::cin>>chN;
                if(chN==1){
                    dmps[nameD[Dname]]->notify();
                    chN=0;
                } else{
                    chN=0;
                }
        } else if(chS==2){
            std::cout<<"\n Enter the name of the existing Student you want to remove:"<<endl;
            std::cin>>Sname;
            dmps[nameD[Dname]]->remove(nameS[Sname]);//Delete student from department
            smps.erase(smps.begin()+ nameS[Sname]);//Delete student from the list of student
            composite->detach(nameS[Sname]+Cno+Dno+Fno);//Unsubscribe from FS ListServer
            dmps[nameD[Dname]]->detach(nameS[Sname]+Fno);//Unsubscribe from Department ListServer
            std::cout<<Sname<<" is now removed from "<<Dname<<" Department."<<endl;
            std::cout<<"\n Do you want to notify this to "<<Dname<<" ListServer? 1) Yes 2)No"<<endl;
            std::cin>>chN;
                if(chN==1){
                    dmps[nameD[Dname]]->notify();
                    chN=0;
                } else{
                    chN=0;
                }
        } else{
            std::cout<<"\n Wrong choice"<<endl;
        }
  } else{
        std::cout<<"\n Wrong choice"<<endl;
    }
  }else if(choice==10){
    m = false;//Exit
  }
  }


  return 0;
}
