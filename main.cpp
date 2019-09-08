#include <QApplication>
#include <QMainWindow>
#include <QHBoxLayout>
#include "mybuttongroup.h"
#include <vector>
#include <time.h>
#include <stdlib.h>
#include <stack>
#include <iostream>
#include <QTableWidgetItem>
#include <QHeaderView>
#include <QLabel>
#include <ctime>

int main(int argc, char *argv[])
{
    QApplication Qapp(argc, argv);
    QMainWindow *window = new QMainWindow();
    window->resize(600, 300);
    QWidget *centralWidget = new QWidget(window);
    //vector for storing letters as QString
    vector<QString> letterVec = {"A","A","B","B","C","C","D","D","E","E","F","F",
                                 "G","G","H","H","I","I","J","J","K","K","L","L"};
    //stack for letters as QString to push randomly from vector of letter
    stack<QString> letterStack ;

    MyButtonGroup* group = new MyButtonGroup(centralWidget);

    int size  = letterVec.size();
    for(int i= 0 ; i<size ; i++){           // for loop to push letter QString stack from vector
        int index = rand()%size;                    //get random index according to vector size
        letterStack.push(letterVec[index]);         //get letter with random index of vector of QString and push it to stack
        letterVec.erase(letterVec.begin() + index);     //delete the letter of the index in vector
        i=-1 ;
        size-- ;
    }

    QTableWidget *table = new QTableWidget();
    MyButtonGroup::mytable = table ;      //Assign table pointer to mytable from MyButtonGroup
    QTableWidgetItem *tableItem ;
    table->verticalHeader()->setVisible(false);     // set invisible to vertical header of table to remove numbers
    table->horizontalHeader()->setVisible(false);

    table->setRowCount(5);
    table->setColumnCount(6);

    table->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding); //set size policy for cells in table
    QPushButton *reset = new QPushButton("Reset"); //QPushButton pointer for reset
    MyButtonGroup::reset = reset; //Assign reset pointer to reset QPushButton from MyButtonGroup

    QLabel *triesNum =new QLabel("0");
    MyButtonGroup::triesNum = triesNum;
    QLabel *pairsNum =new QLabel("0");
    MyButtonGroup::pairsNum = pairsNum;

    QLabel *pairs =new QLabel("Pairs");
    QLabel *tries =new QLabel("Tries");
    QLabel *resetLabel =new QLabel("Reset");

    table->setRowCount(5);
    table->setColumnCount(6);
    table->setCellWidget(0,0,pairs);
    table->setCellWidget(0,1,pairsNum);
    table->setCellWidget(0,2,tries);
    table->setCellWidget(0,3,triesNum);
    table->setCellWidget(0,4,resetLabel);

    table->cellWidget(0,0)->resize(50,50);
    table->setSpan(0,4,1,2);

    table->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    table->setIndexWidget(table->model()->index(0, 4), reset);
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    table->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    // for loop to set table item for created buttons above in specific coordinates
    for (int i = 0; i < 3; ++i) {
            tableItem= new QTableWidgetItem();
            table->setItem(i,5,tableItem);
        }
    table->setCellWidget(0,5,reset);

    // add reset button to MyGroupButton
    group->addButton(reset);
    //for loop to set item to table in specific locations
    for (int i = 0; i < 2; ++i) {
        tableItem= new QTableWidgetItem();
        table->setItem(i+1,0,tableItem);
        tableItem= new QTableWidgetItem();
        table->setItem(0,i+1,tableItem);
        }

    //add QPushButtons to table with nested for loop
    for(int i=0 ; i<4 ; i++){
        for(int j=0 ; j<6 ; j++){
            QPushButton * buttonX = new QPushButton("X",centralWidget); //QPushButton pointers with text "X"
            tableItem= new QTableWidgetItem();//initalize new QTableWidgetItem in every loop
            buttonX->setStyleSheet("color: black;"
                                    "background-color: rgb(230,230,230);"
                                    "selection-color: rgb(230,230,230);"
                                    "selection-background-color: rgb(230,230,230);");

            MyButtonGroup::mybtnletter[i][j] = letterStack.top(); // add the letters from randomly pushed stack to array from MyButtonGroup class
            letterStack.pop(); // pop letter that assigned to array above from stack

            MyButtonGroup::mybtns[i][j] = buttonX ; // add buttons to array from MyButtonGroup

            table->setItem(i+1,j,tableItem); //set table item to table
            table->setCellWidget(i+1, j, buttonX); // add buttons to table
            group->addButton(buttonX); // add buttons to MyButtonGroup class to identify which button is clicked

            if(letterStack.empty()) // if stack is empty breaks the loop
                break;
        }
    }
    window->setCentralWidget(table);
    window->show();

    return Qapp.exec();
}
