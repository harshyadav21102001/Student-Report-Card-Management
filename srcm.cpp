#include<bits/stdc++.h>
using namespace std;
class Student{
    public:
        int roll; // stores roll
        char name[100];
        float mat , sci , ssci , eng , hin;
        float cgpa;
        char gmat , gsci , gssci , geng , ghin;
        char return_grade(float);
        void result();
        int give_roll();
        void input_info();
        void show();
        void report_card();
};
char Student :: return_grade(float ok){
    if(ok>=9.50) return 'O';
    else if(ok>=9.0) return 'A';
    else if(ok>=8.0) return 'B';
    else if(ok>=7.0) return 'C';
    else if(ok>=6.0) return 'D';
    else if(ok>=5.0) return 'E';
    else return 'F';
}
void Student:: result(){
    cgpa = (hin + eng + sci + ssci + mat)/5;
    ghin = return_grade(hin);
    geng = return_grade(eng);
    gsci = return_grade(sci);
    gssci = return_grade(ssci);
    gmat = return_grade(mat);
}
void Student :: input_info(){
    cout << "Enter Name     :  ";
    cin >> ws;
    cin.getline(name,100);
    cout << "Enter Roll No. :  ";
    cin >> roll;
    cout << "Enter Grade Points For English          : ";
    cin >> eng;
    cout << "Enter Grade Points For Maths            : ";
    cin >> mat;
    cout << "Enter Grade Points For Science          : ";
    cin >> sci;
    cout << "Enter Grade Points For Social Science   : ";
    cin >> ssci;
    cout << "Enter Grade Points For Hindi            : ";
    cin >> hin;
    result();    // calculates the results on the basis of Inputs
}
void Student :: show(){
    cout << "Roll Number \t:" << roll << endl;
    cout << "Name of the Student   "<<name <<endl;
    cout <<"Subject          \t Points \t Grade"<<endl;
    cout <<"English           \t "<<eng<<" \t "<<geng<<endl;
    cout <<"Mathematics       \t "<<mat<<" \t "<<gmat<<endl;
    cout <<"Science           \t "<<sci<<" \t "<<gsci<<endl;
    cout <<"Social Science    \t "<<ssci<<" \t "<<gssci<<endl;
    cout <<"Hindi             \t "<<hin<<" \t "<<ghin<<endl;
    cout<<"\n\n\n OVERALL CGPA OF STUDENT IS \t:"<<cgpa<<endl;
    cin.ignore();
    cin.get();

}
void Student :: report_card(){
    cout << roll << "\t\t" << name << "\t\t" << cgpa << "\n";
}
int Student :: give_roll(){
    return roll;
}
void enter_record(){
    Student S;
    ofstream Ofile;
    Ofile.open("student.dat",ios::binary|ios::app);
    S.input_info();
    Ofile.write(reinterpret_cast<char *> (&S),sizeof(Student));
    Ofile.close();
    cout << " \n Record Entered Succesfully \n ";
    cin.ignore();
    cin.get();
}
void display(){

    Student S;
    ifstream Ifile;
    Ifile.open("student.dat",ios::binary);
    if(!Ifile){
        cout << "Failed To Open File !! : Press Any Key To Continue \n";
        return;
    } else {
        cout << " \n \n Total Records \n \n ";
        while(Ifile.read(reinterpret_cast<char *> (&S),sizeof(Student))){
            S.show();
            cout << endl ;
        }
        Ifile.close();
    }
}
void search(int r){
    Student S;
    ifstream Ifile;
    Ifile.open("student.dat",ios::binary);
    if(!Ifile){
        cout << "Failed To Open File !! : Press Any Key To Continue \n";
        cin.ignore();
        cin.get();
        return;
    } else {
        bool found = 0;
        while(Ifile.read(reinterpret_cast<char *>(&S),sizeof(Student))){
            if(S.give_roll()==r) {
                S.show();
                found = 1;
            }
        }
        if(found==0){
            cout << "Record Not Found !! : Press Any Key to Return !";
        }
        Ifile.close();
    }
    cin.ignore();
    cin.get();
}
void modify(int r){
    bool found = 0;
    Student S;
    fstream Ifile;
    Ifile.open("student.dat",ios::binary | ios::out | ios::in);
    if(!Ifile){
        cout << "Failed To Open File !! : Press Any Key To Continue \n";
        return;
    } else {
        while(!(Ifile.eof()) and found==0){
            Ifile.read(reinterpret_cast<char *> (&S), sizeof(Student));
            if(S.give_roll()==r){
                S.show();
                cout << "Enter New Updated Details of Students \n";
                S.input_info();
                int position= (-1)*static_cast<int>(sizeof(S));
                Ifile.seekp(position,ios::cur);
                Ifile.write(reinterpret_cast<char *>(&S),sizeof(Student));
                cout << "Record Updated \n";
                found = 1;
                break;
            }
        }
        Ifile.close();
        if(found==0){
            cout << "\n Record Not Found \n Enter Any Key !!";
        }
        cin.ignore();
        cin.get();
    }
}
void del(int n){
    int flag=0;
    Student st;
    ifstream inFile;
    inFile.open("student.dat",ios::binary);
    if(!inFile)
    {
        cout<<"File could not be open !! Press any Key...";
        cin.ignore();
        cin.get();
        return;
    }
    ofstream outFile;
    outFile.open("Temp.dat",ios::out);
    inFile.seekg(0,ios::beg);
    while(inFile.read(reinterpret_cast<char *> (&st), sizeof(Student)))
    {
        if(st.give_roll()!= n)
        {
            outFile.write(reinterpret_cast<char *> (&st), sizeof(Student));
        }
        if (st.give_roll() == n){
            flag=1;
        }
    }
    outFile.close();
    inFile.close();
    remove("student.dat");
    rename("Temp.dat","student.dat");

    if(flag==1){
        cout<<"\n\n\tRecord Deleted ..";
    }
    else{
        cout<<"\n\n\t\t---Unable to delete--- \n\n\t\t---Record not found--- ";
    }

    cin.ignore();
    cin.get();
}

void result(){
    system("cls");
    Student S;
    ifstream file;
    file.open("student.dat",ios::binary);
    if(!file){
        cout << "Failed To Open File !! : Press Any Key To Continue \n";
        cin.ignore();
        cin.get();
        return;
    }
    cout << "\t \t Overall Result \n\n";
    cout << "Roll No.   \tName\t\t CGPA\n";
    while(file.read(reinterpret_cast<char *>(&S),sizeof(Student))){
        S.report_card();
    }
    file.close();
    cin.ignore();
    cin.get();
}
void overall(){
    char choice;
    int se;
    cout << " Student Report Card \n \nMenu:\n\n1. Class Result\n\n2. Individual Report\n\n3. Return To Main Menu\n \n";
    cin >> choice;
    switch(choice){
        case '1' : result();
            break;
        case '2' : cout << "Enter Roll Number Of the Student : ";
            cin >> se;
            search(se);
        case '3' : break;
        default : cout << "Wrong Choice \n" ;
    }
}
void main_menu(){
    int choice;
    system("cls");
    cout << "\n \n ---------------------------------------------------------------------- \n";
    cout << "\t\t\t STUDENT REPORT CARD PROJECT\n\n\n";
    cout << "\n \n ---------------------------------------------------------------------- \n";
    cout << "\n MENU \n \n";
    cout << "\n 1: Create Student Record\n";
    cout << "\n 2: Display All Records\n";
    cout << "\n 3: Search Student By Roll Number \n";
    cout << "\n 4: Modify Report Card\n";
    cout << "\n 5: Delete Student Record\n";
    cout << "\n 6: Return To Main Menu\n";
    cin >> choice;
    switch(choice){
        case 1: enter_record();
            break;
        case 2: display();
            break;
        case 3: 
        int roll;
            cout << "Enter Roll Number \n";
            cin >> roll;
            search(roll);
            break;
        case 4:
        cout <<" Enter Current Roll Number \n";
            cin >> roll;
            modify(roll);
            break;
        case 5:
            cout << "Enter Roll Number \n";
            cin >> roll;
            del(roll);
            break;
        case 6: return;
        defualt : return;
    }
}
int main(){
    int choice;
    do{
        system("cls");
        cout << "\n \n \t\t WELCOME Graphic Era University\n \n";
        cout << "\t\t Menu\n";
        cout << "\t\t 1: Result Menu\n";
        cout << "\t\t 2: Entry/Edit Menu\n";
        cout << "\t\t 3: Exit\n";
        cout << "\t\t\t\t Made By Aditya Chaudhary\n";
        cout << "\t\t";
        cin >> choice;
        switch(choice){
            case 1: overall();
                break;
            case 2: main_menu();
                break;
            case 3:exit(0);
            default: cout << "Wrong Submission\n";
        }
    }while(choice!=3);
    return 0;
}