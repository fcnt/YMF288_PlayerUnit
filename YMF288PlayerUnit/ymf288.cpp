/*
  YMF288 driver for YMF288 Player Unit
   License: GNU General Public License V3

 (C) Copyright 2015 TaisukeWatanabe(@fcneet)

  【参考資料】
  ・YMF288-M ピン配列＆回路 (http://d.hatena.ne.jp/m_yanase/20131007/1381151650)
  ・YMF288変換基板+Arduinoで簡易S98プレーヤを作る（その1～2）
    (http://d.hatena.ne.jp/m_yanase/20130910/1378810438)
  ・S98v3フォーマット（http://www.vesta.dti.ne.jp/~tsato/soft_s98v3.html）
  ・S98プレイヤを作ってみる（http://risky-safety.org/zinnia/sdl/works/fmgen/s98sdl/）
 
*/

#include <avr/io.h>
#include <avr/pgmspace.h>
#include "Arduino.h"
#include "ymf288.h"

YMF288_DRV::YMF288_DRV()
{
}

/* !ポートの初期設定とYMF288のリセットを行う。
	最初に必ず呼ぶ必要あり。
 */
YMF288_DRV::begin()
{
	int i;
	for(i = D0; i < 8; i++)
	{
		pinMode(i, OUTPUT);
	}
	
	pinMode(RST, OUTPUT);
	pinMode(A0_, OUTPUT);
	pinMode(A1_, OUTPUT);
	pinMode(WR, OUTPUT);
	pinMode(CS, OUTPUT);
	
	reset();
	
	return;
}
  
/* !YMF288のリセットを行う。
 */
void YMF288_DRV::reset()
{
	digitalWrite(RST, LOW);  // モジュールリセット
	delayMicroseconds(100); // min. 25us
	digitalWrite(RST, HIGH);
	delay(100);
	digitalWrite(WR, LOW);
	
	return;
}

// レジスタライト
void YMF288_DRV::reg_write(unsigned char ifadr, unsigned char adr, unsigned char dat)
{
	_law_write(ifadr, adr, dat);

	switch(adr)	// データライト後のWait
	{
		case 0x28:	// FM Address 0x28
		{
			delayMicroseconds(25);  // min: 24us wait
			break;
		}
		case 0x10:	// RHYTHM Address 0x10
		{
			delayMicroseconds(23);  // min: 22us wait
			break;
		}
		default:	// Other Address
		{
			delayMicroseconds(2);  // min.1.9us wait
		}
	}
	
	return;
}

/* !データライトのためのローレベルポート操作関数。非公開。
 */
void YMF288_DRV::_write_data(unsigned char dat)
{
	PORTD = (PORTD&0B00000000)|(dat);  // ポートD0-D7へ出力データセット
	return;
}

/* !データをライトするための一連のポート操作を含んだ関数。非公開。
 */
void YMF288_DRV::_law_write(unsigned char ifadr, unsigned char adr, unsigned char dat)
{
	A0_LOW;					// A0 LOW(Address Bus set)
	A1_WRITE(ifadr);		// A1 Set
    
    _write_data(adr);		// Address set
    CS_LOW;					// CS LOW
    delayMicroseconds(1);	// min: 200ns wait
    CS_HIGH;				// CS HIGH
    delayMicroseconds(2);	//  min: 1.9us wait
    
    A0_HIGH;				// A0 HIGH(Address Bus set)
    _write_data(dat);		// Data set
    CS_LOW;					// CS LOW
    delayMicroseconds(1);	// min: 200ns wait
    CS_HIGH;				// CS HIGH
    
    return;
}

