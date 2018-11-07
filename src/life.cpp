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

void createGrid(Grid<bool>& colony, string Fname, int& rows, int& columns);

void animateGrid(const Grid<bool>& colony , int rows, int columns , LifeGUI& gui );

int main() {


    Grid<bool> colony;    //Assigned Grid depending on the original file

    Grid<bool> colonyCopy; //Buffer for processed data

    LifeGUI gui;       // GUI objects constructor

    string filename;



        bool wrapOption;

        char action;

        int rows;

        int columns;





    createGrid(colony, filename, rows, columns);

    animateGrid(colony, rows, columns, gui);

    wrapOption = getYesOrNo("do you want to wrap around the cell world? Yes | No ");

    cout << "a | animate - t | tick - q | quit" << endl;

    action = getchar();

    return 0;

}

//***** this method creates the grid according to the input file*****

 void createGrid(Grid<bool>& colony, string Fname, int& rows, int& columns){

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

//************************++++HERE WE UPDATE THE GUI************************************************************************

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
