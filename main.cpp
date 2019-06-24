/******************************************************
Aufgabe Nr./Task No.: H4
Nachname/Last,Family Name: GIRYES
Vorname/First,Given Name: MANAL
Uni-Email: manal.giryes@stud.uni-due.de
Studiengang/Course of Studies: ISE CE
*******************************************************/

#include <iostream>
#include <iomanip>
using namespace std;

class Timepoint {

private:

    unsigned int dayOFYear, year, time;

    static const int days[];

public:

    Timepoint(unsigned day=31,unsigned month=12,unsigned year1=9999,unsigned h=23,unsigned m=59){

        dayOFYear=day+days[month-1];

        year=year1;

        time=h*60+m;

    }

    unsigned &get_dayOFYear(){

        return dayOFYear;

    }

     Timepoint operator ++(void){

        if(dayOFYear<365) {
            dayOFYear++;
        }else {
            dayOFYear=1;year++;
        }
            return *this;

    }

    friend istream& operator>>(istream& hi,Timepoint & haha){

        unsigned int day, month, year, h,m;

        char point;

        //cout<<"valid until:";

        hi>>day>>point>>month>>point>>year>>h>>point>>m;

        haha = *new Timepoint(day, month, year, h, m);

        //haha.time=h*60+m;

        return hi;

    }

    friend ostream& operator<<(ostream& bye,Timepoint haha){

        unsigned int h,m,month=12,day=31;

        h=haha.time/60;

        m=haha.time%60;


        int i = 0;
        while(haha.dayOFYear>days[i])

        {

            if(haha.dayOFYear<=days[i+1]){

                month=i+1;

                day=haha.dayOFYear-days[i];

                break;

            }

            i++;
        }

        bye<<setfill('0')<<setw(4)<<haha.year<<"-"<<setw(2) <<month<<"-"<<setw(2)<<day<<"T"<<setw(2)<<h<<"-"<<setw(2) <<m;

        return bye;

    }
};

class License{

private:

    int no;

    string issuer;

    Timepoint validUntil;

public:

    License(){};

    License(int no1, string issuer1,Timepoint& validUntil1){

        no=no1;

        issuer=issuer1;

        validUntil=validUntil1;

    }

    int get_no(){

        return no;

    }

    string get_issuer(){

        return issuer;

    }

    Timepoint &get_ValidUntil(){

        return validUntil;
    }

    friend ostream& operator<<(ostream& out,License &ro5sa){

        out<<"issuer of the license\t"<<ro5sa.issuer;

        out<<"number of the license\t"<<ro5sa.no;

        out<<"Valid until\t"<<ro5sa.validUntil;

        return out;

    }

};

class Driver{

private:

    string name;

    License license;

public:

    Driver(){

        int no;

        string issuer;

        Timepoint validUntil;

        cout<<"name of the driver:";

        cin>>name;

        cout<<"issuer of the license:";

        cin>>issuer;

        cout<<"number of the license:";

        cin>>no;

        cout<<"Valid until:";

        cin>>validUntil;

        license = *new License(no, issuer, validUntil);

    }

    string get_name(){

        return name;

    }

    License get_license(){

        return license;

    }

    friend ostream& operator<<(ostream& out,Driver driver){

        out<<driver.name<<" ("<<driver.get_license().get_issuer()<<' '<<driver.get_license().get_no()<<", valid until "<<driver.get_license().get_ValidUntil()<<")";

        return out;

    }
};

class Vehicle{

private:

    string model,plate;

    float price24h;

public:

    Vehicle(string Model,string Plate,float price){

        model=Model;

        plate=Plate;

        price24h=price;

    }

    string get_model(){

        return model;}

    string get_plate(){

        return plate;}

    float get_price(int numday){

        return numday*(float)price24h;
    }

    void set_price(float price){

        price24h=price;}

    virtual void print()=0;
};

class scooter:public Vehicle{

public:

    scooter(string model,string plate):Vehicle( model, plate,9.99){}

    virtual void print(){

        cout<<"scooter\t"<<get_model()<<"  (plate:"<<get_plate()<<")";

    }

};

class Car:public Vehicle{

private:

    bool navigation;

public:

    Car(string model, string plate, float price24h=29.99,bool navigation=true):Vehicle( model, plate,price24h),navigation(navigation){}

    virtual bool has_aircondition()=0;

    bool has_navigation(){

        return navigation;}

    virtual void print(){

        cout<<"\t"<<get_model()<<"  (plate:"<<get_plate()<<")";

        if(has_navigation()){

            cout<<" navigation "<<" ";

        }

        if(has_aircondition()){

            cout<<" air conditioner ";

        }

    }
};

class Cabrio:public Car{

public:

    Cabrio (string model,string plate, float price24h=99.9):Car(model,plate,price24h,false){};

    bool virtual has_aircondition(){

        return false;}

    virtual void print(){

        cout<<"Cabrio\t";Car::print();

    }
};

class Limousine: public Car{

private:

    bool aircondition;

public:

    Limousine(string model, string plate, float price24h=149.90, bool aircondition=true):Car (model,plate,price24h), aircondition(aircondition){};

    bool virtual has_aircondition(){

        return aircondition;}

    virtual void print(){

        cout<<"Limousine\t";Car::print();

    }

};

class Rental{

private:

    const int no;

    Timepoint from;

    int days;

    Vehicle& vehicle;

    Driver driver;

    Driver *additionalDriver;

    static int last_no;

public:

    Rental(Vehicle &vehicle1,Timepoint time,Driver driver1,int day=1, Driver* driver2=NULL):vehicle(vehicle1),no(++last_no), days(day), additionalDriver(driver2), driver(driver1){
        from=time;
    }

    Timepoint get_from(){

        return from;

    }

    Timepoint get_until(){

        int i; Timepoint until=from;
        for(i=0;i<days;i++){
            ++until;
        }
        return until;

    }

    void print(){

        cout<<"\nVEHICLE RENTAL"<<endl;

        cout<<"rental no.:\t"<<no<<endl;

        cout<<"Vehicle:\t";vehicle.print();cout<<endl;

        cout<<"from:\t"<<get_from()<<endl;

        cout<<"until:\t"<<get_until()<<endl;

        cout<<"driver:\t"<<driver;

        if(additionalDriver!=NULL)

        {

            cout<<"\nadditional driver: "<<*additionalDriver;

        }

        cout<<"\nprice for rental: "<<vehicle.get_price(days)<<" EUR";

    }

};

class Schedule{

private:

    Vehicle *vehicle;

    Rental *year[365];

public:

    Schedule(Vehicle *vehicle1):vehicle(vehicle1){

        for(int i=0;i<365;i++)

        {

            year[i]=NULL;

        }

    }

    Vehicle *get_vehicle(){

        return vehicle;

    }

    bool isFree(Timepoint time,int days){
        int mod;
        for(int i=time.get_dayOFYear();i<time.get_dayOFYear()+days;i++) {
            mod=i%365;
            if(year[mod]!=NULL) return false;
        }

        return true;

    }

    void Book(Timepoint time,int days,Driver driver,Driver *adddriver=NULL){
        Timepoint manal = time;
        int samuel;

        Rental *rbook = new Rental(*vehicle, manal, driver, days, adddriver);



        for(int i=0;i<days;i++)

        {

            samuel=time.get_dayOFYear()+i;

            int checking;

            checking=samuel%365;

            year[checking]=rbook;

        }

    }

    void print(){

        Rental* manal = NULL;
        cout<<"SCHEDULE"<<endl;
        vehicle->print();
        int i=0;
        while(i<365)
        {
            if(year[i]!=NULL)
            {
                if(year[i]!=manal) {

                    year[i]->print();

                    manal=year[i];

                }

            }
            i++;
        }
    }

};

int Rental::last_no=0;

const int Timepoint::days[]={0,31,59,90,120,151,181,212,243,273,304,334,365};

int main()

{
    Timepoint zeit;
    Schedule *cars[4];
    int ch,no,days;



    cars[0]=new Schedule(new scooter("BMW C 650 GT","DU-BC 65"));

    cars[1]=new Schedule(new Cabrio("BMW i8 Roadstar","DU-BR 8"));

    cars[2]=new Schedule(new Limousine("Mercedes C 350 e","DU-MC 1",129 ));

    cars[3]=new Schedule(new Limousine("Mercedes E 350 e","DU-ME 2",189,false));



    Driver* add= nullptr;

    cout<<"VEHICLE RENTAL AGENCY"<<endl;

    while(1) {

        cout << endl << "0  end" << endl;

        cout << "1  new rental" << endl;

        cout << "2  print rentals" << endl;

        cin >> ch;
        switch (ch) {

            case 0:
                return 0;
                break;
            case 1: {
                char CHAR;
                cout << "choose vehicle:";

                cout << endl;
                int i=0;
                while(i<4) {

                    cout << i + 1 << "\t";
                    cars[i]->get_vehicle()->print();
                    cout << endl;
                    i++;

                }

                cout << endl;
                cin >> no;
                cout << "day of rental:";
                cin >> zeit;
                cout << "number of days:";
                cin >> days;
                if (cars[no-1]->isFree(zeit, days)) {
                    cout << "input data vehicle and driver" << endl;
                    Driver drv;
                    cout << "additional driver? y/n ";
                    cin >> CHAR;
                    if (CHAR == 'y') {

                        add = new Driver();

                    }

                    cout << "booked" << endl;

                    cars[no-1]->Book(zeit, days, drv, add);

                } else {
                    cout << "sorry, vehicle already booked" << endl;
                }
                break;
            }


            case 2: {

                cout << "choose vehicle:";

                cout << endl;
                int i=0;
                while(i<4) {

                    cout << i + 1 << "\t";
                    cars[i]->get_vehicle()->print();
                    cout << endl;
                    i++;

                }

                cout << endl;

                cin >> no;
                cars[no-1]->print();
                cout << endl;
                break;
            }
        }
    }
    return 0;

}
