#include <mybuttongroup.h>
QPushButton *MyButtonGroup::mybtns[4][6] ;
bool MyButtonGroup::clicked = false ;
int MyButtonGroup::prevId1 = -1;
int MyButtonGroup::prevId2 = -1;
QString MyButtonGroup::mybtnletter[4][6];
QString MyButtonGroup::prevLetter = "";
QPushButton * MyButtonGroup::reset ;
QTableWidget * MyButtonGroup::mytable ;
QLabel * MyButtonGroup::triesNum ;
QLabel * MyButtonGroup::pairsNum ;
int MyButtonGroup::countTry = 0 ;
int MyButtonGroup::countPair = 0 ;
