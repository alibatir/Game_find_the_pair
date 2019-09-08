#ifndef MYBUTTONGROUP_H
#define MYBUTTONGROUP_H

#include <QButtonGroup>
#include <QPushButton>
#include <QLabel>
#include <QMessageBox>
#include <string>
#include <QString>
#include <thread>
#include <chrono>
#include <unistd.h>
#include <QApplication>
#include <QTableWidget>
#include <QLabel>
#include <ctime>
#include <random>
#include <QWidget>
#include <time.h>
#include <iostream>

using namespace std;

//Derived Class from QButtonGroup
class MyButtonGroup: public QButtonGroup
{
  Q_OBJECT
  public:
    static QPushButton * mybtns[4][6];
    static QString mybtnletter[4][6];
    static QString prevLetter ;
    static int prevId1, prevId2 ;
    static bool clicked ;
    static QTableWidget * mytable ;
    static QPushButton * reset ;
    static QLabel * triesNum;
    static QLabel * pairsNum;
    static int countTry ;
    static int countPair;
    static QWidget * _parent;

    MyButtonGroup(QWidget* parent) //MyButtonGroup constructor
    {
      this->setParent(parent);
      //connect buttonClicked signal to our custom slot 'buttonClick'
      connect(this , SIGNAL(buttonClicked(QAbstractButton*)),this,SLOT(buttonClick(QAbstractButton*)));
    }
    ~ MyButtonGroup(){}// destructor
    public slots:

    //Slot method that is called when one of buttons in QButtonGroup is clicked
    // Take argument as QAbstacrionButton which is clicked button
    void buttonClick(QAbstractButton* but )
    {
        if(but == reset){    // looks for clicked button is reset button
            vector<QString> letterShuffle ; //vector of QString to used when reset button is clicked
            //assign -1 to previous ids while starting new game
            prevId1 = -1 ;
            prevId2 = -1 ;

            clicked = false ;

            //nested for loop to assign all letter cards(buttons) as "X" while starting new game
            for(int i=0 ; i<4 ; i++){
                for(int j=0 ; j<6 ; j++){
                    mybtns[i][j]->setText("X"); //setting text for each button as "X"
                    mybtns[i][j]->setEnabled(true); //set enable true for making button clickable
                    letterShuffle.push_back(mybtnletter[i][j]); // shuffle the array to assign letters to buttons randomly
                }
            }
            random_shuffle(letterShuffle.begin(),letterShuffle.end());  // shuffle the vector to assign letters to buttons randomly

            //nested for loop to assign new shuffled letter vector to letter array(mybtnletter)
            for(int i=0 ; i<4 ; i++){
                for(int j=0 ; j<6 ; j++){
                    mybtnletter[i][j] = letterShuffle.back();
                    letterShuffle.erase(letterShuffle.end()-1);
                }
            }
              countTry=0;
              countPair=0;
              triesNum->setText("0");
              pairsNum->setText("0");
            return ;
        }
        //if the button is letter it finds the button from letter array
       for(int i=0 ; i<4 ; i++){
           for(int j=0 ; j<6 ; j++){
               if(but==mybtns[i][j])
               {
                    if(prevId1 == i && prevId2 == j){ //if same button is clicked it breaks the loop
                       break;
                   }
                   if(!clicked){  //if button is clicked

                   but->setText(mybtnletter[i][j]); // setting text letter from letter array to that butotn

                   clicked = !clicked ; // change clicked flag
                   prevLetter = mybtnletter[i][j]; // store the clicked letter in prev

                   //stores clicked button's ids
                   prevId1 = i ;
                   prevId2 = j ;
                   }
                   else{
                       clicked = !clicked ;
                           //compares the letters with first one that we stored  , if they match increment the player's score
                       if(prevLetter.compare(mybtnletter[i][j]) == 0 ){
                           but->setText(""); //set text empty if letters are matched
                           but->setEnabled(false);  // set enabled false to prevent button clicked
                           mybtns[prevId1][prevId2]->setEnabled(false); // set enabled false to prevent button clicked
                            mybtns[prevId1][prevId2]->setText(""); //set text empty if letters are matched

                            //count number of pair
                             countPair++;
                             QString s = QString::number(countPair); //convert int to string
                             pairsNum->setText(s);
                             //count number of try
                              countTry++;
                              QString s2 = QString::number(countTry); //convert int to string
                              triesNum->setText(s2);
                       }
                       else{
                           but->setText(mybtnletter[i][j]); // set text to button from letter array
                           QApplication::processEvents(); //process events

                           usleep(400000); //using time sleep to see the two cards open a little time
                           but->setText("X"); // set text "X" to that button if cards do not match
                           if(prevId1 != -1 && prevId2 != -1)
                                mybtns[prevId1][prevId2]->setText("X"); // set text "X" to other button if cards dont match
                           prevLetter = " "; // assign the empty prev string for new round

                           //count number of try
                            countTry++;
                            QString s3 = QString::number(countTry); //convert int to string
                            triesNum->setText(s3);
                       }
                       //assign -1 to previous ids  for new round
                        prevId1 = -1 ;
                        prevId2 = -1 ;
                   }
               }
           }
       }

}
};
#endif
