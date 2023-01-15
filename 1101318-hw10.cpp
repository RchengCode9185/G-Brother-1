// This program reads a binary file,
// updates grades previously written to the file,
// adds new grades in the file,
// and deletes data previously stored in the file.

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <string>
using namespace std;

struct StudentData //�`�@36��byte
{
   char studentId[ 8 ];
   char lastName[ 12 ];
   char firstName[ 12 ];
   int grade;
};
//////////////////////////////   2      3     4      5  //�Ochoice�ѼơA�ëDint
enum class Choices{ PRINT = 1, UPDATE, NEW, DELETE, END };
                               
// enable user to input menu choice
Choices enterChoice();

// create text file for printing
void createTextFile( fstream &readFromFile );

// update grade in record
void updateRecord( fstream &updateFile );

// add a new grade in record
void newRecord( fstream &insertInFile );

// delete an existing record
void deleteRecord( fstream &deleteFromFile );

// obtain student ID from user
void getID( const char * const prompt, char studentId[] );

int main()
{
   // open file for reading and writing
   fstream inOutGrade( "grades.dat", ios::in | ios::out | ios::binary );
   
   // exit program if fstream cannot open file
   if( !inOutGrade )
   {
      cerr << "File could not be opened." << endl;
      system( "pause" );
      exit( 1 );
   }

   Choices choice; // store user choice

   // enable user to specify action
   while( ( choice = enterChoice() ) != Choices::END ) //�ϥΪ̿�J���Ѽ� != Choices�Ѽƪ�end
   {
      switch( choice )
      {
      case Choices::PRINT:
         createTextFile( inOutGrade ); // create text file from binary file
         break;
      case Choices::UPDATE:
         updateRecord( inOutGrade ); // update grade
         break;
      case Choices::NEW:
         newRecord( inOutGrade ); // add a new grade
         break;
      case Choices::DELETE:
         deleteRecord( inOutGrade ); // delete existing record
         break;
      default:
         cerr << "Incorrect choice" << endl;
         break;
      }
      ////////////////////////////////////////
      //�n��position (�}�l��0�A������-1)
      //??????????????�p�Gclear()�Aseekg()�|�ܦh��????????????
      inOutGrade.clear(); 
      inOutGrade.seekg(0);
      inOutGrade.seekp(0);
      ////////////////////////////////////////
      cout << endl;
   }

   inOutGrade.close();

   system( "pause" );
}

// enable user to input menu choice
Choices enterChoice()
{
   // display available options
   cout << "Enter your choice" << endl
      << "1 - store a text file of all students' information" << endl
      << "    called \"grades.txt\" for printing" << endl
      << "2 - update a student's grade" << endl
      << "3 - add a student's grade" << endl
      << "4 - delete a student's information" << endl
      << "5 - end program\n? ";

   int menuChoice;
   cin >> menuChoice;
   return static_cast< Choices >( menuChoice ); //�q��L��Jint�A�A�নchoice�Ѽ�
}

// create text file for printing
void createTextFile( fstream &readFromFile ) //(1)  //���ͤ@�Ӥ�r��grade.txt�A�æb��X�����]�L�X�� 
{                                                   //�C��s�@�Ӹ�ơA�N�n�إߤ@��                                             
    ////////////////////////////////////////      
    //Ūbinary file:
    StudentData student;
    //�@�����q�G����Ū36��byte��student
    readFromFile.read(reinterpret_cast<char*>(&student), sizeof(StudentData)); 

    //�إ�text file:
    ofstream outFile("grades.txt", ios::out);
    if (!outFile)
    {
        cerr << "File could not be opened\n";
        system("pause");
        exit(1);
    }

    while (!readFromFile.eof()) //end of file �AŪ��̫�@�檺�U�@��(�Ÿ��)�A�^��true
    {
        if (student.studentId[0] != '\0') //���O�Ÿ�T�~�L�X
        {
            //�L�X�@��P��
            cout << setw(9) << left << student.studentId
                << setw(12) << student.lastName
                << setw(13) << student.firstName
                << setw(5) << right << student.grade << endl;
            //********  �g�J�@��P�Ƕitext file    ************* 
            outFile << left << setw(9) << student.studentId
                << setw(12) << student.lastName
                << setw(13) << student.firstName
                << setw(5) << right << student.grade << endl;         
        }    
        //���UŪ�U�@��P��
        readFromFile.read(reinterpret_cast<char*>(&student), sizeof(StudentData));
    }
    
    //����text file
    outFile.close(); 
    ////////////////////////////////////////
}

// update grade in record
void updateRecord( fstream &updateFile ) //(2)   //�p�G�S�H Student ID 1111444 is empty. 
{                                                //���Z�p�G�O-1�]����ק� Student ID 1111433 has no grade
                                                 //�ק令-1�p�P�⦨�Z�R��
   char studentId[ 8 ];
   getID( "\nEnter student ID to update", studentId );
   ////////////////////////////////////////
   cout << endl;

   //*****�Z�Ůy��(�ĴX�ӦP��)*****(�Ʀr�r������)
   int inClassId = 10 * (studentId[5] - '0') + (studentId[6] - '0'); //��0��ASCII�t�o����

   //Ū�@��P�Ǹ����:
   StudentData student; 
   //*****�]Ū����m*****(position�q0�}�l�A�ҥH-1)
   updateFile.seekg((inClassId - 1) * sizeof(StudentData));
   updateFile.read(reinterpret_cast<char*>(&student), sizeof(StudentData));

   //��Ƥw�g�R��(ID�O�Ŧr��):
   if (student.studentId[0] == '\0')
   {
       cout << "Student ID " << studentId << " is empty." << endl;
       return;
   }
   //�p�G�٨S�����Z:
   if (student.grade == -1)
   {
       cout << "Student ID " << studentId << " has no grade." << endl;
       return;
   }

   //���L�X�쥻�����
   cout << left << setw(9) << student.studentId
       << left << setw(12) << student.lastName
       << left << setw(13) << student.firstName
       << setw(5) << student.grade
       << endl << endl;

   //��J���Z:
   cout << "Enter grade: ";
   cin >> student.grade;
   cout << endl;

   //�g�@��P�Ǹ���� �л\ �쥻����P�Ǫ����:
   //�]�m�g�J����m
   updateFile.seekp((inClassId - 1) * sizeof(StudentData));
   updateFile.write(reinterpret_cast<const char*>(&student), sizeof(StudentData));

   //�L�X:
   cout << left << setw(9) << student.studentId
       << left << setw(12) << student.lastName
       << left << setw(13) << student.firstName
       << setw(5) << student.grade
       << endl;
   

   ////////////////////////////////////////
}

// add a new grade in record
void newRecord( fstream &insertInFile ) //(3) //�p�G�S�H Student ID 1111444 is empty. 
{                                             //�����쥻�S�����Z(-1)
   char studentId[ 8 ];
   getID( "\nEnter student ID to add", studentId );
   //////////////////////////////////////// 
   cout << endl;
        
   int inClassId = 10 * (studentId[5] - '0') + (studentId[6] - '0');//��0��ASCII�t�o����

   //Ū�@��P�Ǹ����:
   //�]Ū����m
   StudentData student;
   insertInFile.seekg((inClassId - 1) * sizeof(StudentData));
   insertInFile.read(reinterpret_cast<char*>(&student), sizeof(StudentData));

   //��Ƥw�g�R��(ID�O�Ŧr��):
   if (student.studentId[0] == '\0')
   {
       cout << "Student ID " << studentId << " is empty." << endl;
       return;
   }

   //��J���Z:
   cout << "Enter grade: ";
   cin >> student.grade;
   cout << endl;
   
   //�g�@��P�Ǹ����:
   //�]�m�g�J����m
   insertInFile.seekp((inClassId - 1) * sizeof(StudentData));
   insertInFile.write(reinterpret_cast<const char*>(&student), sizeof(StudentData));

   //�L�X:
   cout << left << setw(9) << student.studentId
       << left << setw(12) << student.lastName
       << left << setw(13) << student.firstName
       << setw(5) << student.grade
       << endl; 
   ////////////////////////////////////////
}

// delete an existing record
void deleteRecord( fstream &deleteFromFile ) //(4) //�p�G�S�H Student ID 1111444 is empty.
{
   char studentId[ 8 ];
   getID( "\nEnter student ID to delete", studentId );
   ////////////////////////////////////////
   cout << endl;  

   int inClassId = 10 * (studentId[5] - '0') + (studentId[6] - '0'); //��0��ASCII�t�o����

   //Ū�@��P�Ǹ����:
   //�]Ū����m
   StudentData student;
   deleteFromFile.seekg((inClassId - 1) * sizeof(StudentData)); 
   deleteFromFile.read(reinterpret_cast<char*>(&student), sizeof(StudentData));

   //��Ƥw�g�R��(ID�O�Ŧr��):
   if (student.studentId[0] == '\0')
   {
       cout << "Student ID " << studentId << " is empty." << endl;
       return;
   } 

   //�M�Ū���(�ǥ�):  
   student.studentId[0] = '\0';
   student.lastName[0] = '\0';
   student.firstName[0] = '\0';
   student.grade = -1;

   //�g�@��P�Ǹ����:
   //�]�m�g�J����m
   deleteFromFile.seekp((inClassId - 1) * sizeof(StudentData));
   deleteFromFile.write(reinterpret_cast<const char*>(&student), sizeof(StudentData));

   cout << "Student ID " << studentId << " deleted." << endl;

   ////////////////////////////////////////
}

// obtain student ID from user
void getID( const char * const prompt, char studentId[] )
{
   do
   {
      cout << prompt << " ( 1111401 - 1111450 ): ";
      cin >> studentId;
   } while( strcmp( studentId, "1111401" ) == -1 || strcmp( studentId, "1111450" ) == 1 ); //�p��o�ӽd��N����
}