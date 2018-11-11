// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own.
// TODO: remove this comment header!

#include <cctype>
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include "console.h"
#include "filelib.h"
#include "grid.h"
#include "gwindow.h"
#include "simpio.h"
#include "strlib.h"
#include "lifegui.h"

using namespace std;

void createGrid(Grid<bool>& colony, Grid<bool>& colonyCopy, string Fname, int& rows, int& columns);
void GridUpdate(Grid<bool>& colony, Grid<bool>& colonyCopy);
void animateGrid(const Grid<bool>& colony , int rows, int columns , LifeGUI& gui );
bool lookForNeighbours(int& x, int& y, const Grid<bool>& colony);
int upperLeft(int x ,int y, const Grid<bool>& colony);
int up(int x ,int y, const Grid<bool>& colony);
int upperRight(int x ,int y, const Grid<bool>& colony);
int left(int x ,int y, const Grid<bool>& colony);
int right(int x ,int y, const Grid<bool>& colony);
int lowerLeft(int x ,int y, const Grid<bool>& colony);
int down(int x ,int y, const Grid<bool>& colony);
int lowerRight(int x ,int y, const Grid<bool>& colony);


int main() {

    Grid<bool> colony;    //Assigned Grid depending on the original file
    Grid<bool> colonyCopy; //Buffer for processed data
    LifeGUI gui;       // GUI constructor
    string filename;
    bool wrapOption;
    char action;
    int rows;
    int columns;

    createGrid(colony, colonyCopy, filename, rows, columns);


    while(true){
        animateGrid(colony, rows, columns, gui);
        GridUpdate(colony, colonyCopy);

    }
    //cout << " Colony " << colony << endl;
    //cout << " ColonyCopy " << colonyCopy << endl;
    wrapOption = getYesOrNo("do you want to wrap around the cell world? Yes | No ");
    cout << "a | animate - t | tick - q | quit" << endl;
    action = getchar();
    return 0;

}

//***** this method creates the grid according to the input file*****

 void createGrid(Grid<bool>& colony, Grid<bool>& colonyCopy, string Fname, int& rows, int& columns){

     int deadCell = '-';                                                                       //dead cell token to read
     int aliveCell = 'X';                                                                      // alive cell token
     ifstream stream;                                                                          //input stream for file
     string newLine;                                                                          //line that's read from the input file, used as a buffer

      cout << "Please select the action that you want to perform." << endl;
            Fname = getLine("Please enter the filename.");                                     //we store the name of the file in Fname string

            stream.open(Fname);                                                                //we open the file **adjustment needed --> loop nd file verification
            stream >> rows;                                                                    //we store the number of rows and columns specified from the file
            stream >> columns;
            colony.resize( rows, columns );                                                    // with both variables declared we resize the grid
            colonyCopy.resize( rows, columns );


            for(int i = 0; i < rows; i++){
                stream >> newLine;                                                            // we pick every line here

                for(int j = 0; j < columns; j++){                                             // and scan each one of the characters
                    bool value;                                                               // this boolean is used to store the status of the character
                    int token = newLine[j];                                                   // current scanned character

                    if(token == deadCell)                                                     //here we compare if it's a dead or an alive cell
                        value = false;

                        else if(token == aliveCell) {
                            value = true;
                            }

                    colony[i][j] = value;                                                 //we add the boolean value to the grid
                }
               }
            cout << colony << endl;                                                       //***********************+++DEBUG


}
//**********************************This method takes care of the grid update according to the colony rules*****************************************************************+

 void GridUpdate(Grid<bool>& colony, Grid<bool>& colonyCopy ){

     int gridRowsY = 0;
     int gridColumnsX = 1;
 //    cout<< " x " << gridColumnsX << " y " << gridRowsY << " <- coordinates "  << endl;
     lookForNeighbours(gridColumnsX, gridRowsY, colony);
     int maxX = colony.nCols;
     int maxY = colony.nRows;

     for(int Ypos = 0; Ypos < maxY; Ypos++){
         for(int Xpos = 0; Xpos < maxX; Xpos++){
           bool cellState = lookForNeighbours(Ypos, Xpos, colony);
           colonyCopy[Ypos][Xpos] = cellState;

         }
     }

     colony = colonyCopy;

 }




//************************++++HERE WE UPDATE THE GUI*************************************************************************************************************************


 void animateGrid(const Grid<bool>& colony ,int rows, int columns , LifeGUI& theGUI){

     theGUI.resize(rows,columns);                                                         //the gui gets resized depending on the file
     for(int i = 0; i < rows; i++){                                                       //here we scan each row and column of thw grid
         for(int j = 0; j < columns; j++){
             bool value;                                                                  //temporary storage for the cell value
             value = colony[i][j];                                                        //value of the coordinte (todo -> optimize)
             theGUI.drawCell(i,j,value);                                                  //cell redraw
         }
     }



 }

 //**************Scans each one of the neighbours of the cell and storages the alues in a vector*****

 bool lookForNeighbours(int& x, int& y, const Grid<bool>& colony ){

    //cout << "neighBours" << endl;

    Vector<int> locations[8];    // locations of all cells get storaged here
    locations->insert( 0,
                       upperLeft(x , y, colony));  //scan first position and store in the array, the same with all the other values up to the lower left cell
    locations->insert( 1,
                       up(x , y, colony));
    locations->insert( 2,
                       upperRight(x , y, colony));
    locations->insert( 3,
                       left(x , y, colony));
    locations->insert( 4,
                       right(x , y, colony));
    locations->insert( 5,
                       lowerLeft(x , y, colony));
    locations->insert( 6,
                       down(x , y, colony));
    locations->insert( 7,
                       lowerRight(x , y, colony));
        int numberOfNeighbours = 0;                                                                                        // variable to store all the neighbours
        for(int count = 0; count < locations->size(); count++){                                                            //loop through the lovation values
                                                                    int cellValue = locations->get(count);
                                                                    numberOfNeighbours = numberOfNeighbours + cellValue;   //we add the values progressively
                                                               }
     //  cout << "current cell Value: " << colony[x][y] << endl;
        if(numberOfNeighbours == 3){

                                    return true;                                                                          //if there are more than three neighbours, the cell is alive
                                                        }
            else if(numberOfNeighbours == 2 && colony[x][y] == true){
                             return true;
                             }

                else if(numberOfNeighbours > 4){
                                     return false;
                                     }


                            else{   return false;                                                                          //if not, then is dead
                                                        }
 }


 int lowerLeft(int x ,int y, const Grid<bool>& colony){                                                                    //need to optimize this redundant code (?)
    int cellScanX = x - 1;
    int cellScanY = y + 1;
     if (colony.inBounds( cellScanX, cellScanY)){
      bool isAlive = colony.get(cellScanX ,cellScanY);
       // debug  cout << cellScanX  << " y " << cellScanY << " present " << isAlive << endl;
         if(isAlive)return 1;
             else return 0;
    }
    else {return 0;
          cout << "cell not present "  << endl;
           }

 }

 int down(int x ,int y, const Grid<bool>& colony){
     int cellScanX = x ;
     int cellScanY = y + 1;
      if (colony.inBounds( cellScanX, cellScanY)){
     bool isAlive = colony.get(cellScanX ,cellScanY);
    // cout << cellScanX  << " y " << cellScanY << " present " << isAlive << endl;
     if(isAlive)return 1;
         else return 0;
     }
      else {return 0;}
 }

 int lowerRight(int x ,int y, const Grid<bool>& colony){
     int cellScanX = x + 1;
     int cellScanY = y + 1;
      if (colony.inBounds( cellScanX, cellScanY)){
     bool isAlive = colony.get(cellScanX, cellScanY);
    // cout << cellScanX  << " y " << cellScanY << " present " << isAlive << endl;
     if(isAlive)return 1;
         else return 0;
     }
      else {return 0;}
 }

 int left(int x ,int y, const Grid<bool>& colony){
     int cellScanX = x - 1;
     int cellScanY = y;
      if (colony.inBounds( cellScanX, cellScanY)){
     bool isAlive = colony.get(cellScanX, cellScanY);
     //cout << cellScanX  << " y " << cellScanY << " present " << isAlive << endl;
     if(isAlive)return 1;
         else return 0;
     }
      else {return 0;}
 }

 int right(int x ,int y, const Grid<bool>& colony){
     int cellScanX = x + 1;
     int cellScanY = y;
      if (colony.inBounds( cellScanX, cellScanY)){
     bool isAlive = colony.get(cellScanX, cellScanY);
    // cout << cellScanX  << " y " << cellScanY << " present " << isAlive << endl;
     if(isAlive)return 1;
         else return 0;
     }
      else {return 0;}
 }

 int upperLeft(int x ,int y, const Grid<bool>& colony){
     int cellScanX = x - 1;
     int cellScanY = y - 1;
      if (colony.inBounds( cellScanX, cellScanY)){
     bool isAlive = colony.get(cellScanX, cellScanY);
    // cout << cellScanX  << " y " << cellScanY << " present " << isAlive << endl;
     if(isAlive) return 1;
         else return 0;
     }
      else {return 0;}
 }

 int up(int x ,int y, const Grid<bool>& colony){
     int cellScanX = x;
     int cellScanY = y - 1;
      if (colony.inBounds( cellScanX, cellScanY)){
     bool isAlive = colony.get(cellScanX, cellScanY);
    // cout << cellScanX  << " y " << cellScanY << " present " << isAlive << endl;
     if(isAlive) return 1;
         else return 0;
     }
      else {return 0;}
 }

 int upperRight(int x ,int y, const Grid<bool>& colony){
     int cellScanX = x + 1;
     int cellScanY = y - 1;
      if (colony.inBounds( cellScanX, cellScanY)){
     bool isAlive = colony.get(cellScanX, cellScanY);
    // cout << cellScanX  << " y " << cellScanY << " present " << isAlive << endl;
     if(isAlive)
         return 1;
         else return 0;
     }
      else {return 0;}
 }
