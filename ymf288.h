/*
  YMF288 driver for YMF288 Player Unit
   License: GNU General Public License V3

 (C) Copyright 2015 TaisukeWatanabe(@fcneet)
*/

// ピン定義
#define	D0		0		// D0
#define	RST		8		// Reset
#define	A0_		17;		// A0
#define	A1_		18;		// A1
#define	WR		15;		// Read Enable
#define	CS		14;		// Chip Select

// ピン操作マクロ
#define	A0_LOW			PORTC = (PORTC & ~0B01000);
#define	A0_HIGH			PORTC = (PORTC |  0B01000);
#define A1_WRITE(ifadr)	PORTC = (PORTC & ~0B10000) | (ifadr << 4);
#define	CS_LOW			PORTC = (PORTC & ~0B00001);
#define CS_HIGH			PORTC = (PORTC |  0B00001);

// クラス YMF288_DRV 宣言
class YMF288_DRV{
public:
	// コンストラクタ
	YMF288_DRV();
	// ポート設定&チップ初期化
	void begin();
	// モジュールリセット
	void reset();
	// レジスタライト
	void reg_write(unsigned char ifadr, unsigned char adr, unsigned char dat);

private:
	// データライト
	void _write_data(unsigned char dat);
	// ローレベルポートライト
	void _law_write(unsigned char ifadr, unsigned char adr, unsigned char dat);
};

