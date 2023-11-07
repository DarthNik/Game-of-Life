#include <stdio.h>
#include <unistd.h> //for sleep


#define Length 40 //length of map
#define Wide 20 // wide of map

char alive = '*'; //alive cell
char dead = ' '; //dead cell


// function of copying previous condition of map to new
void copy(char map[Wide][Length], char field[Wide][Length]){
    for(int i = 0; i < Wide; i++){
        for(int j = 0; j < Length; j++){
            map[i][j] = field[i][j];
        }
    }
}

// function of drawing our map
void display(char field[Wide][Length]){
    for(int i = 0; i < Wide; i++){
        for(int j = 0; j < Length; j++){
            printf("%c", field[i][j]);
        }
        printf("\n");
    }
    sleep(1);
}


// creating our map
void create(char field[Wide][Length]){
    for(int i = 0; i < Wide; i++){
        for(int j = 0; j < Length; j++){
            field[i][j]=dead;
        }
    }

    //creating frames
    for (int i = 1; i < Length - 1; i++){ 
        field[0][i]='-';
        field[Wide-1][i]='-';
    }
    for(int j = 1; j < Wide - 1; j++){
        field[j][0]='|';
        field[j][Length-1]='|';

    }

    //creating corners of frames
    field[0][0]='+'; 
    field[0][Length-1]='+';
    field[Wide-1][0]='+';
    field[Wide-1][Length-1]='+';

    //creating of alive cells
    field[2][32]=alive;
    field[2][33]=alive;
    field[3][32]=alive;
    field[3][34]=alive;
    field[4][33]=alive;
    field[4][35]=alive;
    field[5][34]=alive;
    field[5][35]=alive;
    field[4][5]=alive; 
    field[5][4]=alive;
    field[6][5]=alive;
    field[5][5]=alive;
    field[5][6]=alive;
    field[10][15]=alive;
    field[11][16]=alive;
    field[11][14]=alive;
    field[12][17]=alive;
    field[12][13]=alive;
    field[13][14]=alive;
    field[13][16]=alive;
    field[14][15]=alive; 
} 

// count of neighbours
int neighbours(char field[Wide][Length], int line, int column){
    int count = 0;
    int r = 1; //radius of searching
    for(int i = (line - r); i <= (line + r); i++){
        for(int j = (column - r); j <= (column + r); j++){
            if (field[i][j] == alive)
                count++;
        }
    }
    return count-(field[line][column] == alive);
}


int main(){
    char map[Wide][Length]; //create an array for map
    char prev_map[Wide][Length]; // an array for previous condition of map
    create(map);
    copy(prev_map, map);

    for(;;){
        display(map);
        for(int i = 1; i < Wide - 1; i++){
            for(int j = 1; j < Length - 1; j++){
                int neighbour = neighbours(map, i, j);
                if (map[i][j] == alive){
                    if ((neighbour >= 2) && (neighbour <= 3))
                        prev_map[i][j] = alive;
                    else
                        prev_map[i][j] = dead;   
                }
                if(map[i][j] == dead){
                    if(neighbour == 3)
                        prev_map[i][j] = alive;
                    else
                        prev_map[i][j] = dead;
                }  
            }
        }
        copy(map, prev_map);
    }
    return 0;
}
