//
// Created by Maryam Baig on 2/11/23.
//
#include <iostream>
using namespace std;
#include <string>
#include <fstream>
#include <vector>
#include "stack.h"
#include <cstdlib> //to generate a random number

//struct to store different elements of each node/coordinate in the maze
struct node{
    bool visited;
    int x,y, left,right,up,down;
    node(){
        x=0;
        y=0;
        left=1;
        right=1;
        up=1;
        down=1;
        visited=false;

    }
    node(int cx, int cy):
            x(cx),y(cy),left(1),right(1),up(1),down(1),visited(false){}
};

//returns a vector of possible neighbors (that have not been visited) that current coordinates has
//and edits a vector of possible directions it can go to according to what neighbours it can go to
vector<node> PossibleNeighbours( int x,int y,int rows,int columns,vector<vector<node>>&MAZE, vector<int>& d){
    vector<node> temp;
    if(x-1>=0 ){

        node element((x-1),y);
        //left
        element.down=MAZE[x-1][y].down;
        element.up=MAZE[x-1][y].up;
        element.right=MAZE[x-1][y].right;
        element.left=MAZE[x-1][y].left;
        if(!MAZE[x - 1][y].visited){
            temp.push_back(element);
            d.push_back(3);
        }


    }
    if( y-1>=0){
        node element(x,(y-1));
        //down
        element.down=MAZE[x][y-1].down;
        element.up=MAZE[x][y-1].up;
        element.right=MAZE[x][y-1].right;
        element.left=MAZE[x][y-1].left;
        if(!MAZE[x][y - 1].visited){
            temp.push_back(element);
            d.push_back(0);
        }

    }
    if(x+1<rows){
        node element((x+1),y);
        //right
        element.down=MAZE[x+1][y].down;
        element.up=MAZE[x+1][y].up;
        element.right=MAZE[x+1][y].right;
        element.left=MAZE[x+1][y].left;
        if(!MAZE[x + 1][y].visited){
            temp.push_back(element);
            d.push_back(2);
        }

    }
    if(y+1<columns){
        node element(x,(y+1));
        //up
        element.down=MAZE[x][y+1].down;
        element.up=MAZE[x][y+1].up;
        element.right=MAZE[x][y+1].right;
        element.left=MAZE[x][y+1].left;
        if(!MAZE[x][y + 1].visited){
            temp.push_back(element);
            d.push_back(1);
        }

    }
    return temp;
}
//checks if all nodes have been visited
bool Endloop(vector<vector<node>>&MAZE, int rows, int columns){
    for(int i=0;i<rows;i++){
        for(int j=0;j<columns;j++){
            if (!MAZE[i][j].visited){
                return false;
            }
        }
    }
    return true;
}
//checks which direction that node can go in (according to which wall is knocked down) to generate a path
vector<string> pdirection(vector<vector<node>>&MAZE,int x,int y)
{
    vector<string> d;
    if(MAZE[x][y].down==0 && MAZE[x][y-1].visited){
        d.push_back("D");
    }
    if(MAZE[x][y].up==0 && MAZE[x][y+1].visited){
        d.push_back("U");
    }
    if(MAZE[x][y].left==0 && MAZE[x-1][y].visited){
        d.push_back("L");
    }
    if(MAZE[x][y].right==0 && MAZE[x+1][y].visited){
        d.push_back("R");
    }
    return d;
}
// write in file recursively so that entry points are on top and exit points are on the bottom
void writeToFile(ofstream& file, Stack<int>& p) {
    if (p.isEmpty()) {
        return; // stop when the stack is empty
    }

    string coordinates = to_string(p.topx())+" "+to_string(p.topy())+"\n";
    p.pop();
    writeToFile(file, p);
    file << coordinates << "\n";
}
int main() {
    int rows, columns, mazeNo;
    cout<<"Enter the number of mazes: ";
    cin>>mazeNo;
    cout<<"Enter the number of rows and columns (M and N): ";
    cin>> columns>>rows;

    vector<vector<vector<node>>> Allmazes; //to store each maze created
    for(int k=1;k<=mazeNo;k++)
    {
        //create maze txt file
        string filename="maze_"+to_string(k)+".txt";
        //empty maze
        vector<vector<node>> maze(rows,vector<node>(columns,node()));
        //intialize coordinates
        for(int i=0; i<rows;i++){
            for(int j=0;j<columns;j++){
                maze[i][j].x=i;
                maze[i][j].y=j;
            }
        }
        //empty stack
        Stack<int> mazeStack;
        //push starting coordinates and set as visited
        mazeStack.push(0,0);
        maze[0][0].visited=true;

        //while there is atleast one node that is not visited
        while(!Endloop(maze, rows, columns)){
            vector<node> neighbours;
            vector<int> direction; //possible directions according to neighbors
            neighbours= PossibleNeighbours(mazeStack.topx(),mazeStack.topy(),rows,columns,maze,direction);
            int nsize=neighbours.size(); //how many neighbors
            int currentx,currenty;

            if(nsize>0){ //if neighbors exist

                currentx=mazeStack.topx();
                currenty=mazeStack.topy();

                int directionidx= rand()%nsize;//pick a random direction
                int val=direction[directionidx];
                if(val==3 && !maze[currentx-1][currenty].visited ){
                    maze[currentx][currenty].left=0;
                    maze[currentx-1][currenty].right=0;
                    maze[currentx-1][currenty].visited=true;
                    mazeStack.push(currentx-1,currenty);

                }
                else if(val==2 && !maze[currentx+1][currenty].visited ){
                    maze[currentx][currenty].right=0;
                    maze[currentx+1][currenty].left=0;
                    maze[currentx+1][currenty].visited=true;
                    mazeStack.push(currentx+1,currenty);

                }
                else if(val==1 && !maze[currentx][currenty+1].visited ){
                    maze[currentx][currenty].up=0;
                    maze[currentx][currenty+1].down=0;
                    maze[currentx][currenty+1].visited=true;
                    mazeStack.push(currentx,currenty+1);

                }
                else if( val==0&& !maze[currentx][currenty-1].visited ){
                    maze[currentx][currenty].down=0;
                    maze[currentx][currenty-1].up=0;
                    maze[currentx][currenty-1].visited=true;
                    mazeStack.push(currentx,currenty-1);

                }


            }
            else{ //if no neighbors, backtrack until we get a node with neighbors
                while(nsize==0){
                    mazeStack.pop();
                    if(mazeStack.isEmpty()){
                        break; //if we backtrack until starting node/empty stack that means maze is created
                    }
                    neighbours= PossibleNeighbours(mazeStack.topx(),mazeStack.topy(),rows,columns,maze,direction);
                    nsize=neighbours.size();
                }

            }
            neighbours.clear();//empty neighbors vector
            direction.clear(); //empty direction vector

        }

        Allmazes.push_back(maze);//store all mazes
        ofstream file(filename);
        file << columns<<" "<<rows<<"\n";
        for(int i=0;i<columns;i++){
            for(int j=0;j<rows;j++){
                file << "x=" << maze[j][i].x << " y=" << maze[j][i].y << " l=" << maze[j][i].left <<
                     " r=" << maze[j][i].right << " u=" << maze[j][i].up <<
                     " d=" << maze[j][i].down << "\n";
            }
        }
        file.close();
    }

    cout <<"All mazes are generated."<<endl<<endl<<"Enter a maze ID between 1 to "<<to_string(mazeNo)<<" inclusive to find a path: ";
    int mazeID ,entryx,entryy,exitx,exity;

    cin >> mazeID;
    cout <<"Enter x and y coordinates of the entry points (x,y) or (column,row): "<<endl;
    cin >> entryx >>entryy;
    cout <<"Enter x and y coordinates of the exit points (x,y) or (column,row): "<<endl;
    cin >> exitx >>exity;
    //empty path stack
    Stack<int> path;
    //vector to store possible direction according to which wall is knocked down
    vector<string> direction;
    //retrive maze that user wants
    vector<vector<node>> maze1=Allmazes[mazeID-1];
    //push entry points
    path.push(entryx,entryy);
    //at the end of maze creation all nodes visited = true so change them to false to mark they have been visited for the path
    maze1[entryx][entryy].visited=false;
    //check which directions are zero in maze, randomly select a direction, keep moving until new coordinates==exitx and exity
    bool pathFound=false;

    while(!pathFound){
        int x=path.topx(),y=path.topy();
        direction= pdirection(maze1,path.topx(),path.topy());
        if(direction.size()==0){ //backtrack if no direction to move in
            while(direction.size()==0){
                path.pop(); // remove backtracked nodes from the path generated
                if(path.isEmpty()){
                    path.push(entryx,entryy);//if we back track till the stack is empty start again from the entry points
                }
                direction= pdirection(maze1,path.topx(),path.topy());
            }
        }
        else{
            int r=rand()%direction.size();
            if(direction[r]=="L" ){
                if(maze1[x-1][y].visited){
                    path.push(x-1,y);
                    maze1[x-1][y].visited=false;
                }
            }
            else if(direction[r]=="R" ){
                if(maze1[x+1][y].visited){
                    path.push(x+1,y);
                    maze1[x+1][y].visited=false;
                }
            }
            else if(direction[r]=="U" ){
                if(maze1[x][y+1].visited){
                    path.push(x,y+1);
                    maze1[x][y+1].visited=false;
                }
            }
            else if(direction[r]=="D"  ){
                if(maze1[x][y-1].visited){
                    path.push(x,y-1);
                    maze1[x][y-1].visited=false;
                }
            }
        }


        if(path.topx()==exitx && path.topy()==exity){
            pathFound=true;
        }
        direction.clear();
    }
    string filename2="maze_"+to_string(mazeID)+"_path_"+to_string(entryx)+"_"+to_string(entryy)+"_"+to_string(exitx)+"_"+to_string(exity)+"_";
    ofstream file2(filename2);
    while(!path.isEmpty()){
        writeToFile( file2, path);
    }
    file2.close();
    Allmazes.clear();

    return 0;
}