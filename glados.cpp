#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main() {
    FILE *fr, *fw;
    int H, W, R, C, i;
    char** M;

    char verso=0;
    char x,y;
    char posti_fatti[100][100];
    char result=0; //1=cycling  2=free  3=stuck

    for(int a=0;a<100;a++){
        for(int b=0;b<100;b++){
            posti_fatti[a][b]=0;
        }
    }


    fr = fopen("input.txt", "r");
    fw = fopen("output.txt", "w");
    assert(4 == fscanf(fr, "%d %d %d %d", &H, &W, &R, &C));
    M = (char**) malloc(H * sizeof(char*));
    for(i=0; i<H; i++) {
        M[i] = (char*) malloc((W + 1) * sizeof(char));
        assert(1 == fscanf(fr, "%s", M[i]));
    }

    // insert your code here
    x=C;
    y=R;
    result=0;
    while (result ==0)
    {
        switch(verso){
            case 0:
                if(M[y][x+1]!='#'){
                    x++;
                    verso= 1;
                }else{
                    if(M[y-1][x]!='#'){
                        y--;
                        verso= 0;
                    }else{
                        if(M[y][x-1]!='#'){
                            x--;
                            verso= 3;
                        }else{
                            y++;
                            verso= 2;
                        }
                    }
                }
            break;
            case 1:
                if(M[y+1][x]!='#'){
                    y++;
                    verso= 2;
                }else{
                    if(M[y][x+1]!='#'){
                        x++;
                        verso= 1;
                    }else{
                        if(M[y-1][x]!='#'){
                            y--;
                            verso= 0;
                        }else{
                            x--;
                            verso= 3;
                        }
                    }
                }
            break;
            case 2:
                if(M[y][x-1]!='#'){
                    x--;
                    verso= 3;
                }else{
                    if(M[y+1][x]!='#'){
                        y++;
                        verso= 2;
                    }else{
                        if(M[y][x-1]!='#'){
                            x--;
                            verso= 1;
                        }else{
                            y--;
                            verso= 0;
                        }
                    }

                }
            break;
            case 3:
                if(M[y-1][x]!='#'){
                    y--;
                    verso= 0;
                }else{
                    if(M[y][x-1]!='#'){
                        x--;
                        verso= 3;
                    }else{
                        if(M[y+1][x]!='#'){
                            y++;
                            verso= 2;
                        }else{
                            x++;
                            verso= 1;
                        }
                    }

                }
            break;
       }
       if(R==y&&C==x){
            result=1;
            continue;
       }
        if(M[y][x]=='0'){
            result= 2;
            continue;
        }
        if(M[y][x]=='@'){
            result= 3;
            continue;
        }
        //printf("%d %d %d\n",verso,x,y);
    }
    switch(result){
        case 1:
            fprintf(fw, "cycling");
        break;
        case 2:
            fprintf(fw, "free");
        break;
        case 3:
            fprintf(fw, "stuck");
        break;
    }
    fclose(fr);
    fclose(fw);
    return 0;
}
