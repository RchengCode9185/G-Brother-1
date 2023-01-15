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

struct StudentData //總共36個byte
{
   char studentId[ 8 ];
   char lastName[ 12 ];
   char firstName[ 12 ];
   int grade;
};
//////////////////////////////   2      3     4      5  //是choice參數，並非int
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
   while( ( choice = enterChoice() ) != Choices::END ) //使用者輸入的參數 != Choices參數的end
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
      //要改position (開始為0，結束為-1)
      //??????????????如果clear()，seekg()會變多少????????????
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
   return static_cast< Choices >( menuChoice ); //從鍵盤輸入int，再轉成choice參數
}

// create text file for printing
void createTextFile( fstream &readFromFile ) //(1)  //產生一個文字檔grade.txt，並在輸出視窗也印出來 
{                                                   //每更新一個資料，就要建立一次                                             
    ////////////////////////////////////////      
    //讀binary file:
    StudentData student;
    //一次先從二元檔讀36個byte給student
    readFromFile.read(reinterpret_cast<char*>(&student), sizeof(StudentData)); 

    //建立text file:
    ofstream outFile("grades.txt", ios::out);
    if (!outFile)
    {
        cerr << "File could not be opened\n";
        system("pause");
        exit(1);
    }

    while (!readFromFile.eof()) //end of file ，讀到最後一行的下一行(空資料)，回傳true
    {
        if (student.studentId[0] != '\0') //不是空資訊才印出
        {
            //印出一位同學
            cout << setw(9) << left << student.studentId
                << setw(12) << student.lastName
                << setw(13) << student.firstName
                << setw(5) << right << student.grade << endl;
            //********  寫入一位同學進text file    ************* 
            outFile << left << setw(9) << student.studentId
                << setw(12) << student.lastName
                << setw(13) << student.firstName
                << setw(5) << right << student.grade << endl;         
        }    
        //往下讀下一位同學
        readFromFile.read(reinterpret_cast<char*>(&student), sizeof(StudentData));
    }
    
    //關閉text file
    outFile.close(); 
    ////////////////////////////////////////
}

// update grade in record
void updateRecord( fstream &updateFile ) //(2)   //如果沒人 Student ID 1111444 is empty. 
{                                                //成績如果是-1也不能修改 Student ID 1111433 has no grade
                                                 //修改成-1如同把成績刪掉
   char studentId[ 8 ];
   getID( "\nEnter student ID to update", studentId );
   ////////////////////////////////////////
   cout << endl;

   //*****班級座號(第幾個同學)*****(數字字元轉整數)
   int inClassId = 10 * (studentId[5] - '0') + (studentId[6] - '0'); //跟0的ASCII差得到整數

   //讀一位同學資料檔:
   StudentData student; 
   //*****設讀的位置*****(position從0開始，所以-1)
   updateFile.seekg((inClassId - 1) * sizeof(StudentData));
   updateFile.read(reinterpret_cast<char*>(&student), sizeof(StudentData));

   //資料已經刪除(ID是空字元):
   if (student.studentId[0] == '\0')
   {
       cout << "Student ID " << studentId << " is empty." << endl;
       return;
   }
   //如果還沒有成績:
   if (student.grade == -1)
   {
       cout << "Student ID " << studentId << " has no grade." << endl;
       return;
   }

   //先印出原本的資料
   cout << left << setw(9) << student.studentId
       << left << setw(12) << student.lastName
       << left << setw(13) << student.firstName
       << setw(5) << student.grade
       << endl << endl;

   //輸入成績:
   cout << "Enter grade: ";
   cin >> student.grade;
   cout << endl;

   //寫一位同學資料檔 覆蓋 原本那位同學的資料:
   //設置寫入的位置
   updateFile.seekp((inClassId - 1) * sizeof(StudentData));
   updateFile.write(reinterpret_cast<const char*>(&student), sizeof(StudentData));

   //印出:
   cout << left << setw(9) << student.studentId
       << left << setw(12) << student.lastName
       << left << setw(13) << student.firstName
       << setw(5) << student.grade
       << endl;
   

   ////////////////////////////////////////
}

// add a new grade in record
void newRecord( fstream &insertInFile ) //(3) //如果沒人 Student ID 1111444 is empty. 
{                                             //必須原本沒有成績(-1)
   char studentId[ 8 ];
   getID( "\nEnter student ID to add", studentId );
   //////////////////////////////////////// 
   cout << endl;
        
   int inClassId = 10 * (studentId[5] - '0') + (studentId[6] - '0');//跟0的ASCII差得到整數

   //讀一位同學資料檔:
   //設讀的位置
   StudentData student;
   insertInFile.seekg((inClassId - 1) * sizeof(StudentData));
   insertInFile.read(reinterpret_cast<char*>(&student), sizeof(StudentData));

   //資料已經刪除(ID是空字元):
   if (student.studentId[0] == '\0')
   {
       cout << "Student ID " << studentId << " is empty." << endl;
       return;
   }

   //輸入成績:
   cout << "Enter grade: ";
   cin >> student.grade;
   cout << endl;
   
   //寫一位同學資料檔:
   //設置寫入的位置
   insertInFile.seekp((inClassId - 1) * sizeof(StudentData));
   insertInFile.write(reinterpret_cast<const char*>(&student), sizeof(StudentData));

   //印出:
   cout << left << setw(9) << student.studentId
       << left << setw(12) << student.lastName
       << left << setw(13) << student.firstName
       << setw(5) << student.grade
       << endl; 
   ////////////////////////////////////////
}

// delete an existing record
void deleteRecord( fstream &deleteFromFile ) //(4) //如果沒人 Student ID 1111444 is empty.
{
   char studentId[ 8 ];
   getID( "\nEnter student ID to delete", studentId );
   ////////////////////////////////////////
   cout << endl;  

   int inClassId = 10 * (studentId[5] - '0') + (studentId[6] - '0'); //跟0的ASCII差得到整數

   //讀一位同學資料檔:
   //設讀的位置
   StudentData student;
   deleteFromFile.seekg((inClassId - 1) * sizeof(StudentData)); 
   deleteFromFile.read(reinterpret_cast<char*>(&student), sizeof(StudentData));

   //資料已經刪除(ID是空字元):
   if (student.studentId[0] == '\0')
   {
       cout << "Student ID " << studentId << " is empty." << endl;
       return;
   } 

   //清空物件(學生):  
   student.studentId[0] = '\0';
   student.lastName[0] = '\0';
   student.firstName[0] = '\0';
   student.grade = -1;

   //寫一位同學資料檔:
   //設置寫入的位置
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
   } while( strcmp( studentId, "1111401" ) == -1 || strcmp( studentId, "1111450" ) == 1 ); //小於這個範圍就重來
}
