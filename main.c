/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <stdio.h>
#include <string.h>
int index=10;
isoprator(char x){
    switch(x){
        case '+':return 1;
        case '-':return 1;
        case '*':return 1;
        case '/':return 1;
        default:return 0;
    }
}
void parse(char *str){
    char num[5];
    int nums[5];
    char charindex=0;
    char oprators[5];
    int operatorindex=0;
    int numindex=0;
    for(int j=0;j<index;j++){//j not i as we use i in different place
        if(isoprator(str[j])==0){
            num[charindex]=str[j];
            charindex++;
        }
        else{

            int x;
            sscanf(num, "%d", &x);
            //printf("\nThe value of x : %d", x);
            nums[numindex]=x;
            numindex++;
            for(int k=0;k<=charindex;k++)
                num[k]="";
            //num[0]='\0';
            charindex=0;

            if(oprators[operatorindex-1]=='*'){
                    nums[numindex-2]=nums[numindex-2]*nums[numindex-1];
                    numindex--;
                    operatorindex--;
                }
                else if(oprators[operatorindex-1]=='/'){
                    nums[numindex-2]=nums[numindex-2]/nums[numindex-1];
                    numindex--;
                    operatorindex--;
                }
                else if(oprators[operatorindex-1]=='-'){
                    nums[numindex-1]=nums[numindex-1]*-1;
                }

            oprators[operatorindex]=str[j];
            operatorindex++;
        }
        if(j==(index-1)){
            //num is added to num in the first if
            int x;
            sscanf(num, "%d", &x);
            //printf("\nThe value of x : %d", x);
            nums[numindex]=x;
            numindex++;
            if(oprators[operatorindex-1]=='-'){
                nums[numindex-1]=nums[numindex-1]*-1;
            }
        }

    }

    for(int m=operatorindex;m>0;m--){
        if((oprators[m-1]=='+')||(oprators[m-1]=='-')){
            nums[numindex-2]=nums[numindex-2]+nums[numindex-1];
            numindex--;
            operatorindex--;
        }
        /*else if(oprators[m-1]=='-'){
            nums[numindex-2]=nums[numindex-2]+nums[numindex-1];
            numindex--;
            operatorindex--;
        }*/
        else if(oprators[m-1]=='*'){
            nums[numindex-2]=nums[numindex-2]*nums[numindex-1];
            numindex--;
            operatorindex--;
        }
        else if(oprators[m-1]=='/'){
            nums[numindex-2]=nums[numindex-2]/nums[numindex-1];
            numindex--;
            operatorindex--;
        }
    }
    if(oprators[operatorindex-1]=='+'){
    printf("\nthhe opators : %c",oprators[operatorindex-1]);
    }
    for(int l=0;l<numindex;l++){
        printf("\n num is : %d",nums[l]);
    }
}

int main()
{
    unsigned char str2[4][4] = {	{'7','8','9','/'},
								{'4','5','6','*'},
								{'1','2','3','-'},
								{' ','0','=','+'}};
    char str[]="12*4+5-1*4";
    //strncat(str,&str2[2][0],1);
    //strncat(str,&str2[2][0],1);
    //strncat(str,&str2[3][3],1);
    //strncat(str,&str2[2][1],1);
    //strncat(str,&str2[2][2],1);
    //strncat(str,&str2[2][2],1);
    parse(str);
    //printf(oprators);
    return 0;
}
