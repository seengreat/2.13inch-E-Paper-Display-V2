#include "stm32f10x.h"
#include "delay.h"
#include "sys.h"
#include "2in13_epd.h"
#include "Ap_213demo.h"	
#include "epd_gui.h"
#include "fonts.h"
#include "usart.h"	

/****************************
* PB12-----SPI2_NSS
* PB13-----SPI2_SCK
* PB15-----SPI2_MOSI
* PA8------DC
* PA11-----RST
* PA12-----BUSY
***************************/
/******************************
 * image :
 * 0------------> y (1~250) 
 * |
 * |
 * |
 * |
 * x (1~122)
 * 
 * */

unsigned char image[4000];//Define canvas space  

//Tips//
/*
1.When the e-paper is refreshed in full screen, the picture flicker is a normal phenomenon, and the main function is to clear the display afterimage in the previous picture.
2.When the partial refresh is performed, the screen does not flash.
3.After the e-paper is refreshed, you need to put it into sleep mode, please do not delete the sleep command.
4.Please do not take out the electronic paper when power is on.
5.Wake up from sleep, need to re-initialize the e-paper.
6.When you need to transplant the driver, you only need to change the corresponding IO. The BUSY pin is the input mode and the others are the output mode.
*/
int	main(void)
{
		unsigned char Fen_L,Fen_H,Miao_L,Miao_H;
		Uart1Init(115200,0,0);
		printf("\r\n-- 2.13inch epaper demo --\r\n");
		printf("STM32F103C8T6\r\n");
		delay_init();	    	     //Delay function initialization
		NVIC_Configuration(); 	//Set NVIC interrupt grouping 2
		EPD_GPIO_Init();       //EPD GPIO  initialization
		while(1)
		{
				/************Fast picture display(1.5s)*******************/
				EPD_HW_Init_Fast(); //EPD init Fast
				EPD_WhiteScreen_ALL_Fast(gImage_0);//EPD_picture0 need 2.07s
			  TEST_PIN = 0;
				EPD_DeepSleep();//EPD_DeepSleep,Sleep instruction is necessary, please do not delete!!!
				delay_s(2); //2s	
					
				//Clear
				EPD_HW_Init_Fast(); //EPD init
				EPD_WhiteScreen_ALL_Fast(gImage_1);//EPD_picture1	need 2.07s			
				EPD_DeepSleep();//EPD_DeepSleep,Sleep instruction is necessary, please do not delete!!!
				delay_s(2); //2s	

//		//////////////////////Partial refresh time demo/////////////////////////////////////
				EPD_HW_Init(); //Electronic paper initialization	
				EPD_WhiteScreen_White(); //Show all white need 2.08s
				EPD_SetRAMValue_BaseMap(gImage_basemap); //Partial refresh background color 2.1s	 				
				for(Fen_H=0;Fen_H<6;Fen_H++)
				{
						for(Fen_L=0;Fen_L<10;Fen_L++)
						{
								for(Miao_H=0;Miao_H<6;Miao_H++) 	
								{
										for(Miao_L=0;Miao_L<10;Miao_L++)
										{
                         //EPD_Dis_Part_myself function need 650~670ms											

												 EPD_Dis_Part_myself(40,188,Num[Miao_L],  //x-A,y-A,DATA-A
																	40,156,Num[Miao_H],         //x-B,y-B,DATA-B
																	40,114,gImage_numdot,      //x-C,y-C,DATA-C
																	40,74,Num[Fen_L],         //x-D,y-D,DATA-D
																	40,42,Num[Fen_H],32,64);	 //x-E,y-E,DATA-E,Resolution 32*64 
													delay_ms(500);
													if((Fen_L==0)&&(Miao_H==1)&&(Miao_L==0))
																   goto Clear;					
										}
							  }		
						}
			  }
		
////////////////////////////////////////////////////////////////////////	
			//Clear screen
		Clear:
				EPD_HW_Init(); //Electronic paper initialization
				EPD_WhiteScreen_White(); //Show all white
				EPD_DeepSleep();  //Enter deep sleep,Sleep instruction is necessary, please do not delete!!!
				delay_s(2);	
			
				
				
			///////////////////////////GUI///////////////////////////////////////////////////////////////////////////////////
			 //Data initialization settings
				Image_Init(image, EPD_WIDTH, EPD_HEIGHT, 0, WHITE); //Set screen size and display orientation
//				Gui_SelectImage(image);//Set the virtual canvas data storage location

				/**************Drawing**********************/
				EPD_HW_Init_GUI(); //EPD init GUI
				Gui_Clear(WHITE);
				//Point   
				Gui_Draw_Point(1, 1, BLACK, PIXEL_1X1, DOT_STYLE_DFT);
				Gui_Draw_Point(15, 3, BLACK, PIXEL_2X2, DOT_STYLE_DFT);
				Gui_Draw_Point(40, 5, BLACK, PIXEL_3X3, DOT_STYLE_DFT);
				Gui_Draw_Point(55, 5, BLACK, PIXEL_4X4, DOT_STYLE_DFT);
				//Line
				Gui_Draw_Line(5, 5, 110, 30, BLACK, PIXEL_1X1, SOLID);
				Gui_Draw_Line(30, 5, 30, 45, BLACK, PIXEL_1X1, SOLID);
				//Rectangle
				Gui_Draw_Rectangle(5, 15, 45, 55, BLACK, EMPTY, PIXEL_1X1);
				Gui_Draw_Rectangle(5, 75, 45, 110, BLACK, FULL, PIXEL_1X1);
				//Circle
				Gui_Draw_Circle(25, 150, 18, BLACK, EMPTY, PIXEL_1X1);
				Gui_Draw_Circle(25, 216, 18, BLACK, FULL, PIXEL_1X1);
				Gui_Draw_Str(50, 30, "abcdefg", &Font12, WHITE, BLACK); //7*12
				Gui_Draw_Str(50,100, "ABCabc012345", &Font16, WHITE, BLACK); //11*16
				Gui_Draw_Str(70, 40, "2.13\" E-Paper", &Font20, WHITE, BLACK); //14*20
				Gui_Draw_Str(94, 45, "SEENGREAT", &Font24, WHITE, BLACK); //17*24
				TEST_PIN = 1;
				EPD_Display(image);//display imag
				TEST_PIN = 0;
				EPD_DeepSleep();//EPD_DeepSleep,Sleep instruction is necessary, please do not delete!!!
				delay_s(2); //2s					
			
				//Clear screen
				EPD_HW_Init(); //Electronic paper initialization
				EPD_WhiteScreen_White(); //Show all white
				EPD_DeepSleep();  //Enter deep sleep,Sleep instruction is necessary, please do not delete!!!
				delay_s(2);		

				while(1);		

	  }
}	


