// student management system with file handlingI in c++ 

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <conio.h>
#include <cstdlib> 
#include <string>   
#include <regex>


using namespace std;
// email verification pattern
bool Emailcheck(string email)
{
    const regex pattern("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");
    return regex_match(email, pattern);
}
class student
{
private:
    string name, roll_no, course, address, email_id;
    long long int contact_no;

public:
    void menu();
    void insert();
    void display();
    void modify();
    void search();
    void deleted();
};
// Project Menu
void student::menu() // add student details
{
menustart:
    int choices;
    char x;
    system("cls");

    cout << "\t\t\t--------------------------" << endl;
    cout << "\t\t\t|STUDENT MANAGEMENT SYSTEM |" << endl;
    cout << "\t\t\t--------------------------" << endl;
    cout << "\t\t\t 1.Enter New Record" << endl;
    cout << "\t\t\t 2.Display Record" << endl;
    cout << "\t\t\t 3.Modify Record" << endl;
    cout << "\t\t\t 4.Search Record" << endl;
    cout << "\t\t\t 5.Delete Record" << endl;
    cout << "\t\t\t 6.Exit\n" << endl;

    cout << "\t\t\t------------------------------" << endl;
    cout << "\t\t\tChoose option:[1/2/3/4/5/6]" << endl;
    cout << "\t\t\t------------------------------" << endl;
    cout << "Enter Your Choose";
    cin >> choices;

    switch (choices)
    {
    case 1:
        do
        {
            insert();
            cout << "\n\t\t\t Add another student Record(Y,N):";
            cin >> x;
        } while (x == 'y' || x == 'Y');

        break;
    case 2:
        display();
        break;
    case 3:
        modify();
        break;
    case 4:
        search();
        break;
    case 5:
        deleted();
        break;
    case 6:
        exit(0);
    default:
        cout << "\n\t\t\t Invalid choice....Please try again..";
    }
    getch();
    goto menustart;
}
void student::insert() // ADD STUDENT DETAILS
{
    system("cls");
    fstream file;
    cout << "\n-------------------------------------------------------------------------------------------------------";
    cout << "\n----------------------------------------Add  Student Details-------------------------------------------" << endl;
    cout << "\t\t\tEnter Name: ";
    cin >> name;
    cout << "\t\t\tEnter Roll no: ";
    cin >> roll_no;
    cout << "\t\t\tEnter Course: ";
    cin >> course;
 email:
    cout << "\t\t\tEnter Email Id(name@gmail.com): ";
    cin >> email_id;
    if (Emailcheck(email_id))
    {
        cout << "\t\t\t Your Email-Id is valid" << endl;
    }
    else
    {
        cout << "\t\t\t Your Email-ID is Invalid" << endl; 
        goto email;
    } 
 
    cout<< "\t\t\tEnter contact:"; 
    cin>> contact_no;
    cout << "\t\t\tEnter Address : ";
    cin >> address;
    file.open("studentRecord.txt", ios::app | ios::out);
    file << " " << name << " " << roll_no << " " << course << " " << email_id << " " << contact_no << " " << address << "\n";
    file.close();
}
void student::display() //display data of student
{
    system("cls");
    fstream file;
    int total = 0;
    cout << "\n-------------------------------------------------------------------------------------------------------";
    cout << "\n----------------------------------------Student Record Table-------------------------------------------" << endl;
    file.open("studentRecord.txt", ios::in);
    if (!file)
    {
        cout << "\n\t\t\t No Data is Present....";
        file.close();
    }
    else
    {
        file >> name >> roll_no >> course >> email_id >> contact_no >> address;
        while (!file.eof())
        {
            cout << "\n\n\t\t Student No.: " << total++ << endl;
            cout << "\t\t Student Name:" << name << endl;
            cout << "\t\t Student Roll no: " << roll_no << endl;
            cout << "\t\t Student course:" << course << endl;
            cout << "\t\t Student Email id:" << email_id << endl;
            cout << "\t\t Student Address:" << address << endl;
            file >> name >> roll_no >> course >> email_id >> contact_no >> address;
        }
        if (total == 0)
        {
            cout << "\n\t\t\t No Data is present.....";
        }
    

    file.close(); 
    }
}
void student::modify()
{
    system("cls");
    fstream file, file1;
    string rollno;
    int found = 0;
    cout << "\n-------------------------------------------------------------------------------------------------------";
    cout << "\n----------------------------------------Student Modify Details-------------------------------------------" << endl;
    file.open("studentRecord.txt", ios::in);
    if (!file)
    {
        cout << "\n\t\t\t No Data is present......";
        file.close();
    }
    else
    {
        cout << "\n Enter Roll no of student which you want to modify";
        cin >> rollno;
        file1.open("Record.txt", ios::app | ios::out);
        file >> name >> roll_no >> course >> email_id >> contact_no >> address;
        while (!file.eof())
        {
            if (rollno != roll_no)
            {

                file1 << " " << name << " " << roll_no << " " << course << " " << email_id << " " << contact_no << " " << address << "\n";
            }
            else
            {
                cout << "\t\t\tEnter Name: ";
                cin >> name;
                cout << "\t\t\tEnter Roll no: ";
                cin >> roll_no;
                cout << "\t\t\tEnter Course: ";
                cin >> course;
            email:
                cout << "\t\t\tEnter Email Id(name@gmail.com): ";
                cin >> email_id;
                if (Emailcheck(email_id))
                {
                    cout << "\t\t\t Your Email-Id is Valid" << endl;
                }
                else
                {
                    cout << "\t\t\t Your Email-Id is InValid" << endl;
                    goto email;
                }
                cout << "\t\t\tEnter Contact No: ";
                cin >> contact_no;
                cout << "\t\t\tEnter Address : ";
                cin >> address;
                file1 << " " << name << " " << roll_no << " " << course << " " << email_id << " " << contact_no << " " << address << "\n";
                found++;
            }

            file >> name >> roll_no >> course >> email_id >> contact_no >> address;
            if (found == 0)
            {
                cout << "\n\t\t\t Student RollNo. Not found....";
            }
        }
        file1.close();
        file.close();
        remove("studentRecord.txt");
        rename("Record.txt", "studnetRecord.txt");
    }
}
void student::search() // search data of student
{
    system("cls");
    fstream file;
    int found = 0;
    file.open("studentRecord.txt", ios::in);
    if (!file)
    {
        cout << "\n-------------------------------------------------------------------------------------------------------" << endl;
        cout << "------------------------------------- Student Search Data --------------------------------------------" << endl;
        cout << "\n\t\t\tNo Data is Present... " << endl;
        
    }
    else
    {
        string rollno;
        cout << "\n-------------------------------------------------------------------------------------------------------" << endl;
        cout << "------------------------------------- Student Search Table --------------------------------------------" << endl;
        cout << "\nEnter Roll No. of Student which you want to search: ";
        cin >> rollno;
        file >> name >> roll_no >> course >> email_id >> contact_no >> address;
        while (!file.eof())
        {
            if (rollno == roll_no)
            {
                cout << "\n\n\t\t\tName: " << name << "\n";
                cout << "\t\t\tRoll No.: " << roll_no << "\n";
                cout << "\t\t\tCourse: " << course << "\n";
                cout << "\t\t\tEmail Id: " << email_id << "\n";
                cout << "\t\t\tContact No.: " << contact_no << "\n";
                cout << "\t\t\tAddress: " << address << "\n";
                found++;
            }
            file >> name >> roll_no >> course >> email_id >> contact_no >> address;
            if (found == 0)
            {
                cout << "\n\t\t\t Student Roll NO. Not Found....";
            }
        }
        file.close();
    }
}
void student::deleted()
{
    system("cls");
    fstream file, file1;
    string rollno;
    int found = 0;
    cout << "\n-------------------------------------------------------------------------------------------------------" << endl;
    cout << "------------------------------------- Student Search Data --------------------------------------------" << endl;
    file.open("studentRecord.txt", ios::in);
    if (!file)
    {
        cout << "\n\t\t\t No Data is present......";
        file.close();
    }
    else
    {
        cout << "<\n Enter Roll No.of student which you want to delete data:";
        cin >> rollno;
        file1.open("Record,txt", ios::app | ios::out);
        file >> name >> roll_no >> course >> email_id >> contact_no >> address;
        while (!file.eof())
        {
            if (rollno != roll_no)
            {
                file1 << " " << name << " " << roll_no << " " << course << " " << email_id << " " << contact_no << " " << address << "\n";
            }
            else
            {
                found++;
                cout << "\n\t\t\tSuccessfully Delete Data";
            }
            file >> name >> roll_no >> course >> email_id >> contact_no >> address;
        }
        if (found == 0)
        {
            cout << "\n\t\t\t Student Roll NO. Not Found....";
        }
        file1.close();
        file.close();
        remove("studentRecord.txt");
        rename("record.txt", "studentRecord.txt");
    }
}

int main()
{
    student project;
    project.menu();
    return 0;
}
