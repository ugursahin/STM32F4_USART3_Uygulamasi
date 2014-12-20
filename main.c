/****************************************************************************************************************************
*Tarih: 20.12.2014
*Yazar: Ugur SAHIN
*Konu :	USART3
*Cihaz: STM32F4 Discovery
*Aciklama: Bu proje www.ugursahin.tk için hazirlanmistir.
*Proje Hakkinda detayli bilgi ve daha fazlasi icin lutfen blogumu ziyaret edin. 
****************************************************************************************************************************/

#include <stm32f4xx.h>  // Islemci header dosyalasi

char Data;  // gelen datayi yazacagimiz degisken

void usatInit(void);            	 // Seri haberlesme birimini hazirlayacak olan fonksiyonun prototipi
char WaitChar(void);								 //	Seriden gelecek Karakteri okuyacagimiz fonksiyonun prototipi
void SendChar(char Tx) ;   	 //	Seriden gonderecegimiz karakteri yazacagimiz fonksiyon prototipi


int main(void)                     // Zorunlu ana fonksiyonumuz
{
	usatInit();     // Usart3'u kuracak fonksiyonu cagirdik.
	USART3->CR1|=0x0000200C; // Usart'i Transmitter ve Receiver'i aktif ettik.
	
	
	while(1)  // Sonsuz dongumuz
	{
		Data = WaitChar();         // Gelen Karakteri Oku
		SendChar(Data + 1);		// ASCII Tablosudaki bir sonraki karakteri gönder
		SendChar(0x0A);					// Alt Satira Gec
		
	}
	
}

void usatInit(void)
{

	RCC->APB1ENR |= 0x00040000;  		// USART3'ün Clockunu aktif ettik.
	RCC->APB1RSTR |=0x00040000;			// USART3'ü RESET Moduna ald1k.
	GPIOB->MODER|=0x2AA00000;				// Pinler AF moduna alindi.
	GPIOB->AFR[1] |= 0x07777700;		// Her bir Pin icin AF7 Secildi.
	RCC->APB1RSTR&=~0x00040000;			// USART3 RESET Modundan cikarildi.
	USART3->SR&=~0X03FF;						// USART3 Status Register'i sifirlandi.
	USART3->BRR = 0x1117;						// USART3 BAUDRATE 9600		
	
}

void SendChar(char data)   
{
   while(!(USART3->SR&0x80));      // Giden Veri Buffer'i dolu ise bekle
   USART3->DR=data;					
}

char WaitChar(void)
{
	 char received;
   while(!(USART3->SR&0x20));      // Gelen Veri Buffer'i bos ise bekle
	 received=USART3->DR;
   return(received);
} 
