#include<bits/stdc++.h>
using namespace std;

class Passenger{
public:
    string name;
    int age;
    Passenger(string n,int a):name(n),age(a){}//constructor
};
class coach{
protected:
    string coachType;
    vector<Passenger> confirmed;
    vector<Passenger> waitingList;
public:
    coach(string type): coachType(type){}
    virtual void bookTicket(Passenger p);
    virtual void CancelTicket(string name);
    virtual void status();
    virtual void chart();

};
void coach :: bookTicket(Passenger p){
    if(confirmed.size()<60){
        confirmed.push_back(p);
        cout<< "Ticket confirmed for"<<p.name << "in "<< coachType << ".\n";
    }
    else if(waitingList.size()<10){
        waitingList.push_back(p);
        cout<< "Added to waiting list :"<< p.name << "in "<< coachType << ".\n";
    }
    else{
        cout<< "No seats or waiting list available.\n";
    }
}
void coach :: CancelTicket(string name){
    for(auto it =confirmed.begin();it!=confirmed.end();++it){
        if(it->name==name){
        confirmed.erase(it);
            cout<< "Ticket cancelled for" << name << "from "<< coachType<< ".\n";
            if(!waitingList.empty()){
                confirmed.push_back(waitingList.front());
                waitingList.erase(waitingList.begin());
            }
            return;
        }
    }
    for(auto it = waitingList.begin();it !=waitingList.end();++it){
        if(it->name==name){
            waitingList.erase(it);
            cout<< name<< "removed from waitingList in "<< coachType <<".\n";
            return;
        }
    }
    cout<< "Passenger not found.\n";
}

void coach :: status(){
    cout<< "coach: "<< coachType << "\n";
    cout<<"confirmed tickets: "<<confirmed.size()<< "\n";
    cout<<"waitinglist: "<< waitingList.size()<<"\n";
}
void coach::chart(){
    cout<<"-----Booking chart for "<< coachType<<"-----\n";
    int seat =1;
    for(auto& p: confirmed){
        cout<<"seat " << seat++ <<  ": "<<p.name <<", Age: "<<  p.age << "\n";
    }
    int wl=1;
    for(auto& p : waitingList){
        cout<< "wl" << wl++ << ": "<< p.name<< ", age: "<< p.age << "\n";
    }
}
class AC : public coach{
public:
    AC(): coach("AC"){}
};
class NonAC : public coach {
public:
    NonAC():coach("Non-AC"){}
};
class Seater: public coach{
public:
    Seater():coach("Seater"){}
};
int main(){
    AC ac;//object
    NonAC nonac;
    Seater seater;
    int choice;
    do{
        cout<< "\n1. Booking \n2. Cancellation \n3. Status \n4. Chart \n5. Exit\n";
        cin >>choice;

    string name;
    int age,coachType;
    coach* selected =nullptr;
    if(choice>=1 && choice<=2){
        cout<< "Enter coach (1-AC, 2-NonAC, 3-Seater): ";
        cin >> coachType;

    }
    cout<< "Enter name: ";
    cin>> name;
    if(choice==1){
        cout<<"Enter age: ";
        cin>> age;
    }
    if(coachType==1) selected= &ac;
    else if(coachType==2) selected= &nonac;
    else if(coachType==3) selected= &seater;

    switch(choice){
        case 1:
        selected->bookTicket(Passenger(name,age));
        break;
        case 2:
        selected->CancelTicket(name);
        break;
        case 3:
            ac.status();nonac.status(),seater.status();
            break;
        case 4:
            ac.chart();nonac.chart(),seater.chart();
            break;
        case 5:
            cout<<"Good bye !\n"; break;
        default:
        cout<< "Invalid choice.\n";
    }

    }while(choice!=5);
}


