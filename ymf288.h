/*
  YMF288 driver for YMF288 Player Unit
   License: GNU General Public License V3

 (C) Copyright 2015 TaisukeWatanabe(@fcneet)
*/

// �s����`
#define	D0		0		// D0
#define	RST		8		// Reset
#define	A0_		17;		// A0
#define	A1_		18;		// A1
#define	WR		15;		// Read Enable
#define	CS		14;		// Chip Select

// �s������}�N��
#define	A0_LOW			PORTC = (PORTC & ~0B01000);
#define	A0_HIGH			PORTC = (PORTC |  0B01000);
#define A1_WRITE(ifadr)	PORTC = (PORTC & ~0B10000) | (ifadr << 4);
#define	CS_LOW			PORTC = (PORTC & ~0B00001);
#define CS_HIGH			PORTC = (PORTC |  0B00001);

// �N���X YMF288_DRV �錾
class YMF288_DRV{
public:
	// �R���X�g���N�^
	YMF288_DRV();
	// �|�[�g�ݒ�&�`�b�v������
	void begin();
	// ���W���[�����Z�b�g
	void reset();
	// ���W�X�^���C�g
	void reg_write(unsigned char ifadr, unsigned char adr, unsigned char dat);

private:
	// �f�[�^���C�g
	void _write_data(unsigned char dat);
	// ���[���x���|�[�g���C�g
	void _law_write(unsigned char ifadr, unsigned char adr, unsigned char dat);
};

