/*
   4x4 Keypad Interfacing with ATmega16/32
   http://www.electronicwings.com
 */ 
#include "LCD16x2_4bit.h"
#include <avr/io.h>
#include <util/delay.h>

#include <stdio.h>
#include <string.h>
#include <math.h>

#define KEY_PRT 	PORTA
#define KEY_DDR		DDRA
#define KEY_PIN		PINA

char keypad[4][4] = {	{'7','8','9','/'},
								{'4','5','6','*'},
								{'1','2','3','-'},
								{' ','0','=','+'}};

unsigned char colloc, rowloc;

//char str[]="";
char str[15];
int index=0;
float result=0;

void LCD_Clear()
{
	LCD_Command (0x01);		/* Clear display */
	_delay_ms(2);
	LCD_Command (0x80);		/* Cursor at home position */
}

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
	result=nums[0];
}

char keyfind()
{
	while(1)
	{
		KEY_DDR = 0xF0;           /* set port direction as input-output */
		KEY_PRT = 0xFF;
		KEY_PRT &= 0x0F;
		do
		{
			KEY_PRT &= 0x0F;      /* mask PORT for column read only*/ 
			asm("NOP");
			colloc = (KEY_PIN & 0x0F); /* read status of column */
		}while(colloc != 0x0F);
		
		do
		{
			/*do
			{
				_delay_ms(20);             /* 20ms key debounce time 
				colloc = (KEY_PIN & 0x0F); /* read status of column 
				}while(colloc == 0x0F);        /* check for any key press */
				
				_delay_ms (40);	            /* 20 ms key debounce time */
				colloc = (KEY_PIN & 0x0F);
			}while(colloc == 0x0F);

	/* now check for rows */
		KEY_PRT = 0xEF;            /* check for pressed key in 1st row */
		asm("NOP");
		colloc = (KEY_PIN & 0x0F);
		if(colloc != 0x0F)
		{
			rowloc = 0;
			break;
		}

		KEY_PRT = 0xDF;			  /* check for pressed key in 2nd row */
		asm("NOP");
		colloc = (KEY_PIN & 0x0F);
		if(colloc != 0x0F)
		{
			rowloc = 1;
			break;
		}
		
		KEY_PRT = 0xBF;			  /* check for pressed key in 3rd row */
		asm("NOP");
		colloc = (KEY_PIN & 0x0F);
		if(colloc != 0x0F)
		{
			rowloc = 2;
			break;
		}

		KEY_PRT = 0x7F;			  /* check for pressed key in 4th row */
		asm("NOP");
		colloc = (KEY_PIN & 0x0F);
		if(colloc != 0x0F)
		{
			rowloc = 3;
			break;
		}
	}

	if(colloc == 0x0E){
		if(rowloc==3){
			for(int i=0;i<15;i++){
				str[i]=' ';
				index=0;
				result=0;
				//LCD_Clear();
			}
		}else{
		//strncat(str,&keypad[rowloc][0],1);
		str[index]=keypad[rowloc][0];
		index++;
		return(keypad[rowloc][0]);}}
	else if(colloc == 0x0D){
		//strncat(str,&keypad[rowloc][1],1);
		str[index]=keypad[rowloc][1];
		index++;
		return(keypad[rowloc][1]);}
	else if(colloc == 0x0B){
		if(rowloc == 3){
			parse(&str);
		}
		else{
		//strncat(str,&keypad[rowloc][2],1);
		str[index]=keypad[rowloc][2];
		index++;
		return(keypad[rowloc][2]);}
		}
	else{
		//strncat(str,&keypad[rowloc][3],1);
		str[index]=keypad[rowloc][3];
		index++;
		return(keypad[rowloc][3]);
		}
}

int main(void)
{
	LCD_Init();
	

    while(1)
	{
		LCD_String_xy(1,0,str);
		LCD_Command(0xc0);
		keyfind();//should run this for power the keypad and takeing the reads
		//LCD_String(str); }            /* Display which key is pressed LCD_Char(keyfind());*/
		if(index==9){
			LCD_Char(str[2]);//keyfind()
		}
		char buf[10];
		//int wid=floor(log10(128))+4;
		sprintf(buf, "%.3f", result);
		LCD_String(buf);
	}
}
