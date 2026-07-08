#include <iostream>
#include <vector>
#include <memory>

using namespace std;

class Device{

    private:
        int id;
        string name;
        bool isActive;
    public: 
        Device(int i, string n, bool a);
        virtual ~Device() { }
        virtual void doActivity() = 0;
        int getID();
        string getName();
        void getActive();
        void setActive(bool status);

};

Device::Device(int i, string n, bool a){

    this->id = i;
    this->name = n;
    this->isActive = a;

}

int Device::getID(){

    return this->id;
}

string Device::getName(){

    return this->name;
}

void Device::getActive(){

    if(this->isActive == 0){
        cout << name << " je vypnuté." << endl;
    } else {
        cout << name << " je zapnuté" << endl;
    }

}

void Device::setActive(bool status){

    this->isActive = status;

} 

class Electronics : public Device{

    private:
        int energyUsage;
    
    public: 
        Electronics(int i, string n, bool a, int e);
        virtual~ Electronics() { } 
        void getUsage();

};

Electronics::Electronics(int i, string n, bool a, int e) : Device(i, n, a){

    this->energyUsage = e;

}

void Electronics::getUsage(){

    cout << "Spotřeba " << this->getName() << " je " << this->energyUsage  << "kWh."<< endl;

}


class SmartLight : public Electronics { 

    private: 
        int jas;
        string barva;

    public: 
        SmartLight(int i, string n, bool a, int e,  int j, string b);
        ~SmartLight() { }
        void doActivity();
        void getJas();
        void getColour();
        void setJas(int j);

};

SmartLight::SmartLight(int i, string n, bool a, int e, int j,  string b) : Electronics(i, n, a, e){

    this->jas = j;
    this->barva = b;

}

void SmartLight::getJas(){

    cout << "Jas " << this->getName() << " je " << this->jas << "%." << endl;
}

void SmartLight::getColour(){

    cout << "Barva " << this->getName() << " je " << this->barva << endl;
    
}

void SmartLight::doActivity(){

    cout << "Světlo " << this->getName() << " svítí na " << this->jas << "% a má barvu " << this->barva << endl;
} 

void SmartLight::setJas(int j){

    this->jas = j;
}

class Termostat : public Electronics {

    private: 
        int currentTemp;
        int targetTemp;

    public: 
        Termostat(int i, string n, bool a, int e, int c, int t);
        ~Termostat() { }
        void doActivity();

};

Termostat::Termostat(int i, string n, bool a, int e, int c, int t) : Electronics(i, n, a, e){

    this->currentTemp = c;
    this->targetTemp = t;

}

void Termostat::doActivity(){

    cout << "Termostat " << this->getName() << " má teplotu " << this->currentTemp << " stupňů." << endl;
    cout << "Cílová teplota je " << this->targetTemp << " stupňů." << endl; 
}

class Room {

    private:
        string name;
        vector<Device*> device;

    public:
        Room(string name);
        ~Room();
        void addDevice(Device* d);
        bool turnEverythingOff();
        void performActivities();

};  

Room::Room(string n){

    this->name = n;

}

Room::~Room(){

    for(Device* d : device){
        delete d;
    }


}

void Room::addDevice(Device* d){ 

    this->device.push_back(d);

}



bool Room::turnEverythingOff(){

    for(auto &d : device){
        d->setActive(false);
    }
    cout << "Všechna zařízení v místnosti " << name << " jsou vypnutá." << endl;

    return true;
}

void Room::performActivities(){

    cout << endl;
    cout << "--- Aktivita v místnosti " << name << " ---" << endl;
    cout << endl;
    for(auto &d : device){
        d->doActivity();
    }
}

class User {

    private:
        string name;
        string role;

    public: 
        User(string n, string r);
        void control(Device* d);
        void control(Device* d, int value);

};

User::User(string n, string r){ 

    this->name = n;
    this->role = r;

}

void User::control(Device *d){
    cout << "Uživatel " << this->name << " ovládá zařízení " << d->getName() << endl;
    d->doActivity();
}

void User::control(Device *d, int value){

    if(auto light = dynamic_cast<SmartLight*>(d)){
        cout << "Uživatel " << name << " nastavuje světlo " << d->getName() << " na " << value << "% jasu." << endl;
        light->setJas(value);
    }
}

class CentralControler{

    private: 
        vector<Room*> room;
    
    public:
        ~CentralControler();
        void addRoom(Room* r);
        void runAllActivities();

};

CentralControler::~CentralControler(){

    for(Room* r : room){
        delete r;
    }
}

void CentralControler::addRoom(Room* r){ 

    this->room.push_back(move(r));

}

void CentralControler::runAllActivities(){

    for (auto &r : this->room) {
        r->performActivities();
    }

}

int main() {

    CentralControler* mujDomov = new CentralControler();

    // User
    vector<User*> user;
    user.push_back(new User("Jan Novák", "Admin"));
    user.push_back(new User("Petr Svoboda", "Uživatel"));
    user.push_back(new User("Eva Malá", "Uživatel"));

    // Room
    Room* obyvak = new Room("Obývák");
    Room* kuchyn = new Room("Kuchyň");
    Room* loznice = new Room("Ložnice");

    // naplneni roomek
    obyvak->addDevice(new SmartLight(1, "Hlavní Lustr", true, 10, 80, "Oranžová"));
    obyvak->addDevice(new Termostat(2, "Termostat Obývák", true, 30, 22, 24));
    
    kuchyn->addDevice(new SmartLight(3, "Světlo nad linkou", true, 5, 100, "Bílá"));
    kuchyn->addDevice(new Termostat(4, "Termostat Kuchyň", true, 20, 20, 21));
    
    loznice->addDevice(new SmartLight(5, "Noční lampička", false, 2, 30, "Žlutá"));
    loznice->addDevice(new Termostat(6, "Termostat Ložnice", true, 15, 19, 20));

    //pridani mistnosti
    mujDomov->addRoom(obyvak);
    mujDomov->addRoom(kuchyn);
    mujDomov->addRoom(loznice);
    
    SmartLight* testing_light = new SmartLight(7, "Light", false, 5, 20, "Modrá");
    Termostat* testing_termostat = new Termostat(8, "Termostat", true, 2, 18, 20);

    user[1]->control(testing_termostat);

    // Přetížení 
    user[0]->control(testing_light);
    testing_light->getJas();
    user[0]->control(testing_light, 12);
    
    testing_light->getJas();
    
    testing_light->getColour();

    testing_light->getUsage();

    testing_light->setActive(1);
    testing_light->getActive();
    

    // Použití metod CentralControler
    cout << "\nSpuštění všech aktivit v domě:" << endl;
    mujDomov->runAllActivities();


    cout << "\nVypínání místnosti:" << endl;
    kuchyn->turnEverythingOff();

    delete mujDomov;
    for (User* u : user) {
        delete u;
    }

    return 0;
}