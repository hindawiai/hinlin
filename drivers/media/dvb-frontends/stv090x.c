<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
	STV0900/0903 Multistandard Broadcast Frontend driver
	Copyright (C) Manu Abraham <abraham.manu@gmail.com>

	Copyright (C) ST Microelectronics

*/

#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/माला.स>
#समावेश <linux/slab.h>
#समावेश <linux/mutex.h>

#समावेश <linux/dvb/frontend.h>
#समावेश <media/dvb_frontend.h>

#समावेश "stv6110x.h" /* क्रम demodulator पूर्णांकernal modes */

#समावेश "stv090x_reg.h"
#समावेश "stv090x.h"
#समावेश "stv090x_priv.h"

/* Max transfer size करोne by I2C transfer functions */
#घोषणा MAX_XFER_SIZE  64

अटल अचिन्हित पूर्णांक verbose;
module_param(verbose, पूर्णांक, 0644);

/* पूर्णांकernal params node */
काष्ठा stv090x_dev अणु
	/* poपूर्णांकer क्रम पूर्णांकernal params, one क्रम each pair of demods */
	काष्ठा stv090x_पूर्णांकernal		*पूर्णांकernal;
	काष्ठा stv090x_dev		*next_dev;
पूर्ण;

/* first पूर्णांकernal params */
अटल काष्ठा stv090x_dev *stv090x_first_dev;

/* find chip by i2c adapter and i2c address */
अटल काष्ठा stv090x_dev *find_dev(काष्ठा i2c_adapter *i2c_adap,
					u8 i2c_addr)
अणु
	काष्ठा stv090x_dev *temp_dev = stv090x_first_dev;

	/*
	 Search of the last stv0900 chip or
	 find it by i2c adapter and i2c address */
	जबतक ((temp_dev != शून्य) &&
		((temp_dev->पूर्णांकernal->i2c_adap != i2c_adap) ||
		(temp_dev->पूर्णांकernal->i2c_addr != i2c_addr))) अणु

		temp_dev = temp_dev->next_dev;
	पूर्ण

	वापस temp_dev;
पूर्ण

/* deallocating chip */
अटल व्योम हटाओ_dev(काष्ठा stv090x_पूर्णांकernal *पूर्णांकernal)
अणु
	काष्ठा stv090x_dev *prev_dev = stv090x_first_dev;
	काष्ठा stv090x_dev *del_dev = find_dev(पूर्णांकernal->i2c_adap,
						पूर्णांकernal->i2c_addr);

	अगर (del_dev != शून्य) अणु
		अगर (del_dev == stv090x_first_dev) अणु
			stv090x_first_dev = del_dev->next_dev;
		पूर्ण अन्यथा अणु
			जबतक (prev_dev->next_dev != del_dev)
				prev_dev = prev_dev->next_dev;

			prev_dev->next_dev = del_dev->next_dev;
		पूर्ण

		kमुक्त(del_dev);
	पूर्ण
पूर्ण

/* allocating new chip */
अटल काष्ठा stv090x_dev *append_पूर्णांकernal(काष्ठा stv090x_पूर्णांकernal *पूर्णांकernal)
अणु
	काष्ठा stv090x_dev *new_dev;
	काष्ठा stv090x_dev *temp_dev;

	new_dev = kदो_स्मृति(माप(काष्ठा stv090x_dev), GFP_KERNEL);
	अगर (new_dev != शून्य) अणु
		new_dev->पूर्णांकernal = पूर्णांकernal;
		new_dev->next_dev = शून्य;

		/* append to list */
		अगर (stv090x_first_dev == शून्य) अणु
			stv090x_first_dev = new_dev;
		पूर्ण अन्यथा अणु
			temp_dev = stv090x_first_dev;
			जबतक (temp_dev->next_dev != शून्य)
				temp_dev = temp_dev->next_dev;

			temp_dev->next_dev = new_dev;
		पूर्ण
	पूर्ण

	वापस new_dev;
पूर्ण


/* DVBS1 and DSS C/N Lookup table */
अटल स्थिर काष्ठा stv090x_tab stv090x_s1cn_tab[] = अणु
	अणु   0, 8917 पूर्ण, /*  0.0dB */
	अणु   5, 8801 पूर्ण, /*  0.5dB */
	अणु  10, 8667 पूर्ण, /*  1.0dB */
	अणु  15, 8522 पूर्ण, /*  1.5dB */
	अणु  20, 8355 पूर्ण, /*  2.0dB */
	अणु  25, 8175 पूर्ण, /*  2.5dB */
	अणु  30, 7979 पूर्ण, /*  3.0dB */
	अणु  35, 7763 पूर्ण, /*  3.5dB */
	अणु  40, 7530 पूर्ण, /*  4.0dB */
	अणु  45, 7282 पूर्ण, /*  4.5dB */
	अणु  50, 7026 पूर्ण, /*  5.0dB */
	अणु  55, 6781 पूर्ण, /*  5.5dB */
	अणु  60, 6514 पूर्ण, /*  6.0dB */
	अणु  65, 6241 पूर्ण, /*  6.5dB */
	अणु  70, 5965 पूर्ण, /*  7.0dB */
	अणु  75, 5690 पूर्ण, /*  7.5dB */
	अणु  80, 5424 पूर्ण, /*  8.0dB */
	अणु  85, 5161 पूर्ण, /*  8.5dB */
	अणु  90, 4902 पूर्ण, /*  9.0dB */
	अणु  95, 4654 पूर्ण, /*  9.5dB */
	अणु 100, 4417 पूर्ण, /* 10.0dB */
	अणु 105, 4186 पूर्ण, /* 10.5dB */
	अणु 110, 3968 पूर्ण, /* 11.0dB */
	अणु 115, 3757 पूर्ण, /* 11.5dB */
	अणु 120, 3558 पूर्ण, /* 12.0dB */
	अणु 125, 3366 पूर्ण, /* 12.5dB */
	अणु 130, 3185 पूर्ण, /* 13.0dB */
	अणु 135, 3012 पूर्ण, /* 13.5dB */
	अणु 140, 2850 पूर्ण, /* 14.0dB */
	अणु 145, 2698 पूर्ण, /* 14.5dB */
	अणु 150, 2550 पूर्ण, /* 15.0dB */
	अणु 160, 2283 पूर्ण, /* 16.0dB */
	अणु 170, 2042 पूर्ण, /* 17.0dB */
	अणु 180, 1827 पूर्ण, /* 18.0dB */
	अणु 190, 1636 पूर्ण, /* 19.0dB */
	अणु 200, 1466 पूर्ण, /* 20.0dB */
	अणु 210, 1315 पूर्ण, /* 21.0dB */
	अणु 220, 1181 पूर्ण, /* 22.0dB */
	अणु 230, 1064 पूर्ण, /* 23.0dB */
	अणु 240,	960 पूर्ण, /* 24.0dB */
	अणु 250,	869 पूर्ण, /* 25.0dB */
	अणु 260,	792 पूर्ण, /* 26.0dB */
	अणु 270,	724 पूर्ण, /* 27.0dB */
	अणु 280,	665 पूर्ण, /* 28.0dB */
	अणु 290,	616 पूर्ण, /* 29.0dB */
	अणु 300,	573 पूर्ण, /* 30.0dB */
	अणु 310,	537 पूर्ण, /* 31.0dB */
	अणु 320,	507 पूर्ण, /* 32.0dB */
	अणु 330,	483 पूर्ण, /* 33.0dB */
	अणु 400,	398 पूर्ण, /* 40.0dB */
	अणु 450,	381 पूर्ण, /* 45.0dB */
	अणु 500,	377 पूर्ण  /* 50.0dB */
पूर्ण;

/* DVBS2 C/N Lookup table */
अटल स्थिर काष्ठा stv090x_tab stv090x_s2cn_tab[] = अणु
	अणु -30, 13348 पूर्ण, /* -3.0dB */
	अणु -20, 12640 पूर्ण, /* -2d.0B */
	अणु -10, 11883 पूर्ण, /* -1.0dB */
	अणु   0, 11101 पूर्ण, /* -0.0dB */
	अणु   5, 10718 पूर्ण, /*  0.5dB */
	अणु  10, 10339 पूर्ण, /*  1.0dB */
	अणु  15,  9947 पूर्ण, /*  1.5dB */
	अणु  20,  9552 पूर्ण, /*  2.0dB */
	अणु  25,  9183 पूर्ण, /*  2.5dB */
	अणु  30,  8799 पूर्ण, /*  3.0dB */
	अणु  35,  8422 पूर्ण, /*  3.5dB */
	अणु  40,  8062 पूर्ण, /*  4.0dB */
	अणु  45,  7707 पूर्ण, /*  4.5dB */
	अणु  50,  7353 पूर्ण, /*  5.0dB */
	अणु  55,  7025 पूर्ण, /*  5.5dB */
	अणु  60,  6684 पूर्ण, /*  6.0dB */
	अणु  65,  6331 पूर्ण, /*  6.5dB */
	अणु  70,  6036 पूर्ण, /*  7.0dB */
	अणु  75,  5727 पूर्ण, /*  7.5dB */
	अणु  80,  5437 पूर्ण, /*  8.0dB */
	अणु  85,  5164 पूर्ण, /*  8.5dB */
	अणु  90,  4902 पूर्ण, /*  9.0dB */
	अणु  95,  4653 पूर्ण, /*  9.5dB */
	अणु 100,  4408 पूर्ण, /* 10.0dB */
	अणु 105,  4187 पूर्ण, /* 10.5dB */
	अणु 110,  3961 पूर्ण, /* 11.0dB */
	अणु 115,  3751 पूर्ण, /* 11.5dB */
	अणु 120,  3558 पूर्ण, /* 12.0dB */
	अणु 125,  3368 पूर्ण, /* 12.5dB */
	अणु 130,  3191 पूर्ण, /* 13.0dB */
	अणु 135,  3017 पूर्ण, /* 13.5dB */
	अणु 140,  2862 पूर्ण, /* 14.0dB */
	अणु 145,  2710 पूर्ण, /* 14.5dB */
	अणु 150,  2565 पूर्ण, /* 15.0dB */
	अणु 160,  2300 पूर्ण, /* 16.0dB */
	अणु 170,  2058 पूर्ण, /* 17.0dB */
	अणु 180,  1849 पूर्ण, /* 18.0dB */
	अणु 190,  1663 पूर्ण, /* 19.0dB */
	अणु 200,  1495 पूर्ण, /* 20.0dB */
	अणु 210,  1349 पूर्ण, /* 21.0dB */
	अणु 220,  1222 पूर्ण, /* 22.0dB */
	अणु 230,  1110 पूर्ण, /* 23.0dB */
	अणु 240,  1011 पूर्ण, /* 24.0dB */
	अणु 250,   925 पूर्ण, /* 25.0dB */
	अणु 260,   853 पूर्ण, /* 26.0dB */
	अणु 270,   789 पूर्ण, /* 27.0dB */
	अणु 280,   734 पूर्ण, /* 28.0dB */
	अणु 290,   690 पूर्ण, /* 29.0dB */
	अणु 300,   650 पूर्ण, /* 30.0dB */
	अणु 310,   619 पूर्ण, /* 31.0dB */
	अणु 320,   593 पूर्ण, /* 32.0dB */
	अणु 330,   571 पूर्ण, /* 33.0dB */
	अणु 400,   498 पूर्ण, /* 40.0dB */
	अणु 450,	 484 पूर्ण, /* 45.0dB */
	अणु 500,	 481 पूर्ण	/* 50.0dB */
पूर्ण;

/* RF level C/N lookup table */
अटल स्थिर काष्ठा stv090x_tab stv090x_rf_tab[] = अणु
	अणु  -5, 0xcaa1 पूर्ण, /*  -5dBm */
	अणु -10, 0xc229 पूर्ण, /* -10dBm */
	अणु -15, 0xbb08 पूर्ण, /* -15dBm */
	अणु -20, 0xb4bc पूर्ण, /* -20dBm */
	अणु -25, 0xad5a पूर्ण, /* -25dBm */
	अणु -30, 0xa298 पूर्ण, /* -30dBm */
	अणु -35, 0x98a8 पूर्ण, /* -35dBm */
	अणु -40, 0x8389 पूर्ण, /* -40dBm */
	अणु -45, 0x59be पूर्ण, /* -45dBm */
	अणु -50, 0x3a14 पूर्ण, /* -50dBm */
	अणु -55, 0x2d11 पूर्ण, /* -55dBm */
	अणु -60, 0x210d पूर्ण, /* -60dBm */
	अणु -65, 0xa14f पूर्ण, /* -65dBm */
	अणु -70, 0x07aa पूर्ण	 /* -70dBm */
पूर्ण;


अटल काष्ठा stv090x_reg stv0900_initval[] = अणु

	अणु STV090x_OUTCFG,		0x00 पूर्ण,
	अणु STV090x_MODECFG,		0xff पूर्ण,
	अणु STV090x_AGCRF1CFG,		0x11 पूर्ण,
	अणु STV090x_AGCRF2CFG,		0x13 पूर्ण,
	अणु STV090x_TSGENERAL1X,		0x14 पूर्ण,
	अणु STV090x_TSTTNR2,		0x21 पूर्ण,
	अणु STV090x_TSTTNR4,		0x21 पूर्ण,
	अणु STV090x_P2_DISTXCTL,		0x22 पूर्ण,
	अणु STV090x_P2_F22TX,		0xc0 पूर्ण,
	अणु STV090x_P2_F22RX,		0xc0 पूर्ण,
	अणु STV090x_P2_DISRXCTL,		0x00 पूर्ण,
	अणु STV090x_P2_DMDCFGMD,		0xF9 पूर्ण,
	अणु STV090x_P2_DEMOD,		0x08 पूर्ण,
	अणु STV090x_P2_DMDCFG3,		0xc4 पूर्ण,
	अणु STV090x_P2_CARFREQ,		0xed पूर्ण,
	अणु STV090x_P2_LDT,		0xd0 पूर्ण,
	अणु STV090x_P2_LDT2,		0xb8 पूर्ण,
	अणु STV090x_P2_TMGCFG,		0xd2 पूर्ण,
	अणु STV090x_P2_TMGTHRISE,		0x20 पूर्ण,
	अणु STV090x_P1_TMGCFG,		0xd2 पूर्ण,

	अणु STV090x_P2_TMGTHFALL,		0x00 पूर्ण,
	अणु STV090x_P2_FECSPY,		0x88 पूर्ण,
	अणु STV090x_P2_FSPYDATA,		0x3a पूर्ण,
	अणु STV090x_P2_FBERCPT4,		0x00 पूर्ण,
	अणु STV090x_P2_FSPYBER,		0x10 पूर्ण,
	अणु STV090x_P2_ERRCTRL1,		0x35 पूर्ण,
	अणु STV090x_P2_ERRCTRL2,		0xc1 पूर्ण,
	अणु STV090x_P2_CFRICFG,		0xf8 पूर्ण,
	अणु STV090x_P2_NOSCFG,		0x1c पूर्ण,
	अणु STV090x_P2_DMDTOM,		0x20 पूर्ण,
	अणु STV090x_P2_CORRELMANT,	0x70 पूर्ण,
	अणु STV090x_P2_CORRELABS,		0x88 पूर्ण,
	अणु STV090x_P2_AGC2O,		0x5b पूर्ण,
	अणु STV090x_P2_AGC2REF,		0x38 पूर्ण,
	अणु STV090x_P2_CARCFG,		0xe4 पूर्ण,
	अणु STV090x_P2_ACLC,		0x1A पूर्ण,
	अणु STV090x_P2_BCLC,		0x09 पूर्ण,
	अणु STV090x_P2_CARHDR,		0x08 पूर्ण,
	अणु STV090x_P2_KREFTMG,		0xc1 पूर्ण,
	अणु STV090x_P2_SFRUPRATIO,	0xf0 पूर्ण,
	अणु STV090x_P2_SFRLOWRATIO,	0x70 पूर्ण,
	अणु STV090x_P2_SFRSTEP,		0x58 पूर्ण,
	अणु STV090x_P2_TMGCFG2,		0x01 पूर्ण,
	अणु STV090x_P2_CAR2CFG,		0x26 पूर्ण,
	अणु STV090x_P2_BCLC2S2Q,		0x86 पूर्ण,
	अणु STV090x_P2_BCLC2S28,		0x86 पूर्ण,
	अणु STV090x_P2_SMAPCOEF7,		0x77 पूर्ण,
	अणु STV090x_P2_SMAPCOEF6,		0x85 पूर्ण,
	अणु STV090x_P2_SMAPCOEF5,		0x77 पूर्ण,
	अणु STV090x_P2_TSCFGL,		0x20 पूर्ण,
	अणु STV090x_P2_DMDCFG2,		0x3b पूर्ण,
	अणु STV090x_P2_MODCODLST0,	0xff पूर्ण,
	अणु STV090x_P2_MODCODLST1,	0xff पूर्ण,
	अणु STV090x_P2_MODCODLST2,	0xff पूर्ण,
	अणु STV090x_P2_MODCODLST3,	0xff पूर्ण,
	अणु STV090x_P2_MODCODLST4,	0xff पूर्ण,
	अणु STV090x_P2_MODCODLST5,	0xff पूर्ण,
	अणु STV090x_P2_MODCODLST6,	0xff पूर्ण,
	अणु STV090x_P2_MODCODLST7,	0xcc पूर्ण,
	अणु STV090x_P2_MODCODLST8,	0xcc पूर्ण,
	अणु STV090x_P2_MODCODLST9,	0xcc पूर्ण,
	अणु STV090x_P2_MODCODLSTA,	0xcc पूर्ण,
	अणु STV090x_P2_MODCODLSTB,	0xcc पूर्ण,
	अणु STV090x_P2_MODCODLSTC,	0xcc पूर्ण,
	अणु STV090x_P2_MODCODLSTD,	0xcc पूर्ण,
	अणु STV090x_P2_MODCODLSTE,	0xcc पूर्ण,
	अणु STV090x_P2_MODCODLSTF,	0xcf पूर्ण,
	अणु STV090x_P1_DISTXCTL,		0x22 पूर्ण,
	अणु STV090x_P1_F22TX,		0xc0 पूर्ण,
	अणु STV090x_P1_F22RX,		0xc0 पूर्ण,
	अणु STV090x_P1_DISRXCTL,		0x00 पूर्ण,
	अणु STV090x_P1_DMDCFGMD,		0xf9 पूर्ण,
	अणु STV090x_P1_DEMOD,		0x08 पूर्ण,
	अणु STV090x_P1_DMDCFG3,		0xc4 पूर्ण,
	अणु STV090x_P1_DMDTOM,		0x20 पूर्ण,
	अणु STV090x_P1_CARFREQ,		0xed पूर्ण,
	अणु STV090x_P1_LDT,		0xd0 पूर्ण,
	अणु STV090x_P1_LDT2,		0xb8 पूर्ण,
	अणु STV090x_P1_TMGCFG,		0xd2 पूर्ण,
	अणु STV090x_P1_TMGTHRISE,		0x20 पूर्ण,
	अणु STV090x_P1_TMGTHFALL,		0x00 पूर्ण,
	अणु STV090x_P1_SFRUPRATIO,	0xf0 पूर्ण,
	अणु STV090x_P1_SFRLOWRATIO,	0x70 पूर्ण,
	अणु STV090x_P1_TSCFGL,		0x20 पूर्ण,
	अणु STV090x_P1_FECSPY,		0x88 पूर्ण,
	अणु STV090x_P1_FSPYDATA,		0x3a पूर्ण,
	अणु STV090x_P1_FBERCPT4,		0x00 पूर्ण,
	अणु STV090x_P1_FSPYBER,		0x10 पूर्ण,
	अणु STV090x_P1_ERRCTRL1,		0x35 पूर्ण,
	अणु STV090x_P1_ERRCTRL2,		0xc1 पूर्ण,
	अणु STV090x_P1_CFRICFG,		0xf8 पूर्ण,
	अणु STV090x_P1_NOSCFG,		0x1c पूर्ण,
	अणु STV090x_P1_CORRELMANT,	0x70 पूर्ण,
	अणु STV090x_P1_CORRELABS,		0x88 पूर्ण,
	अणु STV090x_P1_AGC2O,		0x5b पूर्ण,
	अणु STV090x_P1_AGC2REF,		0x38 पूर्ण,
	अणु STV090x_P1_CARCFG,		0xe4 पूर्ण,
	अणु STV090x_P1_ACLC,		0x1A पूर्ण,
	अणु STV090x_P1_BCLC,		0x09 पूर्ण,
	अणु STV090x_P1_CARHDR,		0x08 पूर्ण,
	अणु STV090x_P1_KREFTMG,		0xc1 पूर्ण,
	अणु STV090x_P1_SFRSTEP,		0x58 पूर्ण,
	अणु STV090x_P1_TMGCFG2,		0x01 पूर्ण,
	अणु STV090x_P1_CAR2CFG,		0x26 पूर्ण,
	अणु STV090x_P1_BCLC2S2Q,		0x86 पूर्ण,
	अणु STV090x_P1_BCLC2S28,		0x86 पूर्ण,
	अणु STV090x_P1_SMAPCOEF7,		0x77 पूर्ण,
	अणु STV090x_P1_SMAPCOEF6,		0x85 पूर्ण,
	अणु STV090x_P1_SMAPCOEF5,		0x77 पूर्ण,
	अणु STV090x_P1_DMDCFG2,		0x3b पूर्ण,
	अणु STV090x_P1_MODCODLST0,	0xff पूर्ण,
	अणु STV090x_P1_MODCODLST1,	0xff पूर्ण,
	अणु STV090x_P1_MODCODLST2,	0xff पूर्ण,
	अणु STV090x_P1_MODCODLST3,	0xff पूर्ण,
	अणु STV090x_P1_MODCODLST4,	0xff पूर्ण,
	अणु STV090x_P1_MODCODLST5,	0xff पूर्ण,
	अणु STV090x_P1_MODCODLST6,	0xff पूर्ण,
	अणु STV090x_P1_MODCODLST7,	0xcc पूर्ण,
	अणु STV090x_P1_MODCODLST8,	0xcc पूर्ण,
	अणु STV090x_P1_MODCODLST9,	0xcc पूर्ण,
	अणु STV090x_P1_MODCODLSTA,	0xcc पूर्ण,
	अणु STV090x_P1_MODCODLSTB,	0xcc पूर्ण,
	अणु STV090x_P1_MODCODLSTC,	0xcc पूर्ण,
	अणु STV090x_P1_MODCODLSTD,	0xcc पूर्ण,
	अणु STV090x_P1_MODCODLSTE,	0xcc पूर्ण,
	अणु STV090x_P1_MODCODLSTF,	0xcf पूर्ण,
	अणु STV090x_GENCFG,		0x1d पूर्ण,
	अणु STV090x_NBITER_NF4,		0x37 पूर्ण,
	अणु STV090x_NBITER_NF5,		0x29 पूर्ण,
	अणु STV090x_NBITER_NF6,		0x37 पूर्ण,
	अणु STV090x_NBITER_NF7,		0x33 पूर्ण,
	अणु STV090x_NBITER_NF8,		0x31 पूर्ण,
	अणु STV090x_NBITER_NF9,		0x2f पूर्ण,
	अणु STV090x_NBITER_NF10,		0x39 पूर्ण,
	अणु STV090x_NBITER_NF11,		0x3a पूर्ण,
	अणु STV090x_NBITER_NF12,		0x29 पूर्ण,
	अणु STV090x_NBITER_NF13,		0x37 पूर्ण,
	अणु STV090x_NBITER_NF14,		0x33 पूर्ण,
	अणु STV090x_NBITER_NF15,		0x2f पूर्ण,
	अणु STV090x_NBITER_NF16,		0x39 पूर्ण,
	अणु STV090x_NBITER_NF17,		0x3a पूर्ण,
	अणु STV090x_NBITERNOERR,		0x04 पूर्ण,
	अणु STV090x_GAINLLR_NF4,		0x0C पूर्ण,
	अणु STV090x_GAINLLR_NF5,		0x0F पूर्ण,
	अणु STV090x_GAINLLR_NF6,		0x11 पूर्ण,
	अणु STV090x_GAINLLR_NF7,		0x14 पूर्ण,
	अणु STV090x_GAINLLR_NF8,		0x17 पूर्ण,
	अणु STV090x_GAINLLR_NF9,		0x19 पूर्ण,
	अणु STV090x_GAINLLR_NF10,		0x20 पूर्ण,
	अणु STV090x_GAINLLR_NF11,		0x21 पूर्ण,
	अणु STV090x_GAINLLR_NF12,		0x0D पूर्ण,
	अणु STV090x_GAINLLR_NF13,		0x0F पूर्ण,
	अणु STV090x_GAINLLR_NF14,		0x13 पूर्ण,
	अणु STV090x_GAINLLR_NF15,		0x1A पूर्ण,
	अणु STV090x_GAINLLR_NF16,		0x1F पूर्ण,
	अणु STV090x_GAINLLR_NF17,		0x21 पूर्ण,
	अणु STV090x_RCCFGH,		0x20 पूर्ण,
	अणु STV090x_P1_FECM,		0x01 पूर्ण, /* disable DSS modes */
	अणु STV090x_P2_FECM,		0x01 पूर्ण, /* disable DSS modes */
	अणु STV090x_P1_PRVIT,		0x2F पूर्ण, /* disable PR 6/7 */
	अणु STV090x_P2_PRVIT,		0x2F पूर्ण, /* disable PR 6/7 */
पूर्ण;

अटल काष्ठा stv090x_reg stv0903_initval[] = अणु
	अणु STV090x_OUTCFG,		0x00 पूर्ण,
	अणु STV090x_AGCRF1CFG,		0x11 पूर्ण,
	अणु STV090x_STOPCLK1,		0x48 पूर्ण,
	अणु STV090x_STOPCLK2,		0x14 पूर्ण,
	अणु STV090x_TSTTNR1,		0x27 पूर्ण,
	अणु STV090x_TSTTNR2,		0x21 पूर्ण,
	अणु STV090x_P1_DISTXCTL,		0x22 पूर्ण,
	अणु STV090x_P1_F22TX,		0xc0 पूर्ण,
	अणु STV090x_P1_F22RX,		0xc0 पूर्ण,
	अणु STV090x_P1_DISRXCTL,		0x00 पूर्ण,
	अणु STV090x_P1_DMDCFGMD,		0xF9 पूर्ण,
	अणु STV090x_P1_DEMOD,		0x08 पूर्ण,
	अणु STV090x_P1_DMDCFG3,		0xc4 पूर्ण,
	अणु STV090x_P1_CARFREQ,		0xed पूर्ण,
	अणु STV090x_P1_TNRCFG2,		0x82 पूर्ण,
	अणु STV090x_P1_LDT,		0xd0 पूर्ण,
	अणु STV090x_P1_LDT2,		0xb8 पूर्ण,
	अणु STV090x_P1_TMGCFG,		0xd2 पूर्ण,
	अणु STV090x_P1_TMGTHRISE,		0x20 पूर्ण,
	अणु STV090x_P1_TMGTHFALL,		0x00 पूर्ण,
	अणु STV090x_P1_SFRUPRATIO,	0xf0 पूर्ण,
	अणु STV090x_P1_SFRLOWRATIO,	0x70 पूर्ण,
	अणु STV090x_P1_TSCFGL,		0x20 पूर्ण,
	अणु STV090x_P1_FECSPY,		0x88 पूर्ण,
	अणु STV090x_P1_FSPYDATA,		0x3a पूर्ण,
	अणु STV090x_P1_FBERCPT4,		0x00 पूर्ण,
	अणु STV090x_P1_FSPYBER,		0x10 पूर्ण,
	अणु STV090x_P1_ERRCTRL1,		0x35 पूर्ण,
	अणु STV090x_P1_ERRCTRL2,		0xc1 पूर्ण,
	अणु STV090x_P1_CFRICFG,		0xf8 पूर्ण,
	अणु STV090x_P1_NOSCFG,		0x1c पूर्ण,
	अणु STV090x_P1_DMDTOM,		0x20 पूर्ण,
	अणु STV090x_P1_CORRELMANT,	0x70 पूर्ण,
	अणु STV090x_P1_CORRELABS,		0x88 पूर्ण,
	अणु STV090x_P1_AGC2O,		0x5b पूर्ण,
	अणु STV090x_P1_AGC2REF,		0x38 पूर्ण,
	अणु STV090x_P1_CARCFG,		0xe4 पूर्ण,
	अणु STV090x_P1_ACLC,		0x1A पूर्ण,
	अणु STV090x_P1_BCLC,		0x09 पूर्ण,
	अणु STV090x_P1_CARHDR,		0x08 पूर्ण,
	अणु STV090x_P1_KREFTMG,		0xc1 पूर्ण,
	अणु STV090x_P1_SFRSTEP,		0x58 पूर्ण,
	अणु STV090x_P1_TMGCFG2,		0x01 पूर्ण,
	अणु STV090x_P1_CAR2CFG,		0x26 पूर्ण,
	अणु STV090x_P1_BCLC2S2Q,		0x86 पूर्ण,
	अणु STV090x_P1_BCLC2S28,		0x86 पूर्ण,
	अणु STV090x_P1_SMAPCOEF7,		0x77 पूर्ण,
	अणु STV090x_P1_SMAPCOEF6,		0x85 पूर्ण,
	अणु STV090x_P1_SMAPCOEF5,		0x77 पूर्ण,
	अणु STV090x_P1_DMDCFG2,		0x3b पूर्ण,
	अणु STV090x_P1_MODCODLST0,	0xff पूर्ण,
	अणु STV090x_P1_MODCODLST1,	0xff पूर्ण,
	अणु STV090x_P1_MODCODLST2,	0xff पूर्ण,
	अणु STV090x_P1_MODCODLST3,	0xff पूर्ण,
	अणु STV090x_P1_MODCODLST4,	0xff पूर्ण,
	अणु STV090x_P1_MODCODLST5,	0xff पूर्ण,
	अणु STV090x_P1_MODCODLST6,	0xff पूर्ण,
	अणु STV090x_P1_MODCODLST7,	0xcc पूर्ण,
	अणु STV090x_P1_MODCODLST8,	0xcc पूर्ण,
	अणु STV090x_P1_MODCODLST9,	0xcc पूर्ण,
	अणु STV090x_P1_MODCODLSTA,	0xcc पूर्ण,
	अणु STV090x_P1_MODCODLSTB,	0xcc पूर्ण,
	अणु STV090x_P1_MODCODLSTC,	0xcc पूर्ण,
	अणु STV090x_P1_MODCODLSTD,	0xcc पूर्ण,
	अणु STV090x_P1_MODCODLSTE,	0xcc पूर्ण,
	अणु STV090x_P1_MODCODLSTF,	0xcf पूर्ण,
	अणु STV090x_GENCFG,		0x1c पूर्ण,
	अणु STV090x_NBITER_NF4,		0x37 पूर्ण,
	अणु STV090x_NBITER_NF5,		0x29 पूर्ण,
	अणु STV090x_NBITER_NF6,		0x37 पूर्ण,
	अणु STV090x_NBITER_NF7,		0x33 पूर्ण,
	अणु STV090x_NBITER_NF8,		0x31 पूर्ण,
	अणु STV090x_NBITER_NF9,		0x2f पूर्ण,
	अणु STV090x_NBITER_NF10,		0x39 पूर्ण,
	अणु STV090x_NBITER_NF11,		0x3a पूर्ण,
	अणु STV090x_NBITER_NF12,		0x29 पूर्ण,
	अणु STV090x_NBITER_NF13,		0x37 पूर्ण,
	अणु STV090x_NBITER_NF14,		0x33 पूर्ण,
	अणु STV090x_NBITER_NF15,		0x2f पूर्ण,
	अणु STV090x_NBITER_NF16,		0x39 पूर्ण,
	अणु STV090x_NBITER_NF17,		0x3a पूर्ण,
	अणु STV090x_NBITERNOERR,		0x04 पूर्ण,
	अणु STV090x_GAINLLR_NF4,		0x0C पूर्ण,
	अणु STV090x_GAINLLR_NF5,		0x0F पूर्ण,
	अणु STV090x_GAINLLR_NF6,		0x11 पूर्ण,
	अणु STV090x_GAINLLR_NF7,		0x14 पूर्ण,
	अणु STV090x_GAINLLR_NF8,		0x17 पूर्ण,
	अणु STV090x_GAINLLR_NF9,		0x19 पूर्ण,
	अणु STV090x_GAINLLR_NF10,		0x20 पूर्ण,
	अणु STV090x_GAINLLR_NF11,		0x21 पूर्ण,
	अणु STV090x_GAINLLR_NF12,		0x0D पूर्ण,
	अणु STV090x_GAINLLR_NF13,		0x0F पूर्ण,
	अणु STV090x_GAINLLR_NF14,		0x13 पूर्ण,
	अणु STV090x_GAINLLR_NF15,		0x1A पूर्ण,
	अणु STV090x_GAINLLR_NF16,		0x1F पूर्ण,
	अणु STV090x_GAINLLR_NF17,		0x21 पूर्ण,
	अणु STV090x_RCCFGH,		0x20 पूर्ण,
	अणु STV090x_P1_FECM,		0x01 पूर्ण, /*disable the DSS mode */
	अणु STV090x_P1_PRVIT,		0x2f पूर्ण  /*disable puncture rate 6/7*/
पूर्ण;

अटल काष्ठा stv090x_reg stv0900_cut20_val[] = अणु

	अणु STV090x_P2_DMDCFG3,		0xe8 पूर्ण,
	अणु STV090x_P2_DMDCFG4,		0x10 पूर्ण,
	अणु STV090x_P2_CARFREQ,		0x38 पूर्ण,
	अणु STV090x_P2_CARHDR,		0x20 पूर्ण,
	अणु STV090x_P2_KREFTMG,		0x5a पूर्ण,
	अणु STV090x_P2_SMAPCOEF7,		0x06 पूर्ण,
	अणु STV090x_P2_SMAPCOEF6,		0x00 पूर्ण,
	अणु STV090x_P2_SMAPCOEF5,		0x04 पूर्ण,
	अणु STV090x_P2_NOSCFG,		0x0c पूर्ण,
	अणु STV090x_P1_DMDCFG3,		0xe8 पूर्ण,
	अणु STV090x_P1_DMDCFG4,		0x10 पूर्ण,
	अणु STV090x_P1_CARFREQ,		0x38 पूर्ण,
	अणु STV090x_P1_CARHDR,		0x20 पूर्ण,
	अणु STV090x_P1_KREFTMG,		0x5a पूर्ण,
	अणु STV090x_P1_SMAPCOEF7,		0x06 पूर्ण,
	अणु STV090x_P1_SMAPCOEF6,		0x00 पूर्ण,
	अणु STV090x_P1_SMAPCOEF5,		0x04 पूर्ण,
	अणु STV090x_P1_NOSCFG,		0x0c पूर्ण,
	अणु STV090x_GAINLLR_NF4,		0x21 पूर्ण,
	अणु STV090x_GAINLLR_NF5,		0x21 पूर्ण,
	अणु STV090x_GAINLLR_NF6,		0x20 पूर्ण,
	अणु STV090x_GAINLLR_NF7,		0x1F पूर्ण,
	अणु STV090x_GAINLLR_NF8,		0x1E पूर्ण,
	अणु STV090x_GAINLLR_NF9,		0x1E पूर्ण,
	अणु STV090x_GAINLLR_NF10,		0x1D पूर्ण,
	अणु STV090x_GAINLLR_NF11,		0x1B पूर्ण,
	अणु STV090x_GAINLLR_NF12,		0x20 पूर्ण,
	अणु STV090x_GAINLLR_NF13,		0x20 पूर्ण,
	अणु STV090x_GAINLLR_NF14,		0x20 पूर्ण,
	अणु STV090x_GAINLLR_NF15,		0x20 पूर्ण,
	अणु STV090x_GAINLLR_NF16,		0x20 पूर्ण,
	अणु STV090x_GAINLLR_NF17,		0x21 पूर्ण,
पूर्ण;

अटल काष्ठा stv090x_reg stv0903_cut20_val[] = अणु
	अणु STV090x_P1_DMDCFG3,		0xe8 पूर्ण,
	अणु STV090x_P1_DMDCFG4,		0x10 पूर्ण,
	अणु STV090x_P1_CARFREQ,		0x38 पूर्ण,
	अणु STV090x_P1_CARHDR,		0x20 पूर्ण,
	अणु STV090x_P1_KREFTMG,		0x5a पूर्ण,
	अणु STV090x_P1_SMAPCOEF7,		0x06 पूर्ण,
	अणु STV090x_P1_SMAPCOEF6,		0x00 पूर्ण,
	अणु STV090x_P1_SMAPCOEF5,		0x04 पूर्ण,
	अणु STV090x_P1_NOSCFG,		0x0c पूर्ण,
	अणु STV090x_GAINLLR_NF4,		0x21 पूर्ण,
	अणु STV090x_GAINLLR_NF5,		0x21 पूर्ण,
	अणु STV090x_GAINLLR_NF6,		0x20 पूर्ण,
	अणु STV090x_GAINLLR_NF7,		0x1F पूर्ण,
	अणु STV090x_GAINLLR_NF8,		0x1E पूर्ण,
	अणु STV090x_GAINLLR_NF9,		0x1E पूर्ण,
	अणु STV090x_GAINLLR_NF10,		0x1D पूर्ण,
	अणु STV090x_GAINLLR_NF11,		0x1B पूर्ण,
	अणु STV090x_GAINLLR_NF12,		0x20 पूर्ण,
	अणु STV090x_GAINLLR_NF13,		0x20 पूर्ण,
	अणु STV090x_GAINLLR_NF14,		0x20 पूर्ण,
	अणु STV090x_GAINLLR_NF15,		0x20 पूर्ण,
	अणु STV090x_GAINLLR_NF16,		0x20 पूर्ण,
	अणु STV090x_GAINLLR_NF17,		0x21 पूर्ण
पूर्ण;

/* Cut 2.0 Long Frame Tracking CR loop */
अटल काष्ठा stv090x_दीर्घ_frame_crloop stv090x_s2_crl_cut20[] = अणु
	/* MODCOD  2MPon 2MPoff 5MPon 5MPoff 10MPon 10MPoff 20MPon 20MPoff 30MPon 30MPoff */
	अणु STV090x_QPSK_12,  0x1f, 0x3f, 0x1e, 0x3f, 0x3d, 0x1f, 0x3d, 0x3e, 0x3d, 0x1e पूर्ण,
	अणु STV090x_QPSK_35,  0x2f, 0x3f, 0x2e, 0x2f, 0x3d, 0x0f, 0x0e, 0x2e, 0x3d, 0x0e पूर्ण,
	अणु STV090x_QPSK_23,  0x2f, 0x3f, 0x2e, 0x2f, 0x0e, 0x0f, 0x0e, 0x1e, 0x3d, 0x3d पूर्ण,
	अणु STV090x_QPSK_34,  0x3f, 0x3f, 0x3e, 0x1f, 0x0e, 0x3e, 0x0e, 0x1e, 0x3d, 0x3d पूर्ण,
	अणु STV090x_QPSK_45,  0x3f, 0x3f, 0x3e, 0x1f, 0x0e, 0x3e, 0x0e, 0x1e, 0x3d, 0x3d पूर्ण,
	अणु STV090x_QPSK_56,  0x3f, 0x3f, 0x3e, 0x1f, 0x0e, 0x3e, 0x0e, 0x1e, 0x3d, 0x3d पूर्ण,
	अणु STV090x_QPSK_89,  0x3f, 0x3f, 0x3e, 0x1f, 0x1e, 0x3e, 0x0e, 0x1e, 0x3d, 0x3d पूर्ण,
	अणु STV090x_QPSK_910, 0x3f, 0x3f, 0x3e, 0x1f, 0x1e, 0x3e, 0x0e, 0x1e, 0x3d, 0x3d पूर्ण,
	अणु STV090x_8PSK_35,  0x3c, 0x3e, 0x1c, 0x2e, 0x0c, 0x1e, 0x2b, 0x2d, 0x1b, 0x1d पूर्ण,
	अणु STV090x_8PSK_23,  0x1d, 0x3e, 0x3c, 0x2e, 0x2c, 0x1e, 0x0c, 0x2d, 0x2b, 0x1d पूर्ण,
	अणु STV090x_8PSK_34,  0x0e, 0x3e, 0x3d, 0x2e, 0x0d, 0x1e, 0x2c, 0x2d, 0x0c, 0x1d पूर्ण,
	अणु STV090x_8PSK_56,  0x2e, 0x3e, 0x1e, 0x2e, 0x2d, 0x1e, 0x3c, 0x2d, 0x2c, 0x1d पूर्ण,
	अणु STV090x_8PSK_89,  0x3e, 0x3e, 0x1e, 0x2e, 0x3d, 0x1e, 0x0d, 0x2d, 0x3c, 0x1d पूर्ण,
	अणु STV090x_8PSK_910, 0x3e, 0x3e, 0x1e, 0x2e, 0x3d, 0x1e, 0x1d, 0x2d, 0x0d, 0x1d पूर्ण
पूर्ण;

/* Cut 3.0 Long Frame Tracking CR loop */
अटल	काष्ठा stv090x_दीर्घ_frame_crloop stv090x_s2_crl_cut30[] = अणु
	/* MODCOD  2MPon 2MPoff 5MPon 5MPoff 10MPon 10MPoff 20MPon 20MPoff 30MPon 30MPoff */
	अणु STV090x_QPSK_12,  0x3c, 0x2c, 0x0c, 0x2c, 0x1b, 0x2c, 0x1b, 0x1c, 0x0b, 0x3b पूर्ण,
	अणु STV090x_QPSK_35,  0x0d, 0x0d, 0x0c, 0x0d, 0x1b, 0x3c, 0x1b, 0x1c, 0x0b, 0x3b पूर्ण,
	अणु STV090x_QPSK_23,  0x1d, 0x0d, 0x0c, 0x1d, 0x2b, 0x3c, 0x1b, 0x1c, 0x0b, 0x3b पूर्ण,
	अणु STV090x_QPSK_34,  0x1d, 0x1d, 0x0c, 0x1d, 0x2b, 0x3c, 0x1b, 0x1c, 0x0b, 0x3b पूर्ण,
	अणु STV090x_QPSK_45,  0x2d, 0x1d, 0x1c, 0x1d, 0x2b, 0x3c, 0x2b, 0x0c, 0x1b, 0x3b पूर्ण,
	अणु STV090x_QPSK_56,  0x2d, 0x1d, 0x1c, 0x1d, 0x2b, 0x3c, 0x2b, 0x0c, 0x1b, 0x3b पूर्ण,
	अणु STV090x_QPSK_89,  0x3d, 0x2d, 0x1c, 0x1d, 0x3b, 0x3c, 0x2b, 0x0c, 0x1b, 0x3b पूर्ण,
	अणु STV090x_QPSK_910, 0x3d, 0x2d, 0x1c, 0x1d, 0x3b, 0x3c, 0x2b, 0x0c, 0x1b, 0x3b पूर्ण,
	अणु STV090x_8PSK_35,  0x39, 0x29, 0x39, 0x19, 0x19, 0x19, 0x19, 0x19, 0x09, 0x19 पूर्ण,
	अणु STV090x_8PSK_23,  0x2a, 0x39, 0x1a, 0x0a, 0x39, 0x0a, 0x29, 0x39, 0x29, 0x0a पूर्ण,
	अणु STV090x_8PSK_34,  0x2b, 0x3a, 0x1b, 0x1b, 0x3a, 0x1b, 0x1a, 0x0b, 0x1a, 0x3a पूर्ण,
	अणु STV090x_8PSK_56,  0x0c, 0x1b, 0x3b, 0x3b, 0x1b, 0x3b, 0x3a, 0x3b, 0x3a, 0x1b पूर्ण,
	अणु STV090x_8PSK_89,  0x0d, 0x3c, 0x2c, 0x2c, 0x2b, 0x0c, 0x0b, 0x3b, 0x0b, 0x1b पूर्ण,
	अणु STV090x_8PSK_910, 0x0d, 0x0d, 0x2c, 0x3c, 0x3b, 0x1c, 0x0b, 0x3b, 0x0b, 0x1b पूर्ण
पूर्ण;

/* Cut 2.0 Long Frame Tracking CR Loop */
अटल काष्ठा stv090x_दीर्घ_frame_crloop stv090x_s2_apsk_crl_cut20[] = अणु
	/* MODCOD  2MPon 2MPoff 5MPon 5MPoff 10MPon 10MPoff 20MPon 20MPoff 30MPon 30MPoff */
	अणु STV090x_16APSK_23,  0x0c, 0x0c, 0x0c, 0x0c, 0x1d, 0x0c, 0x3c, 0x0c, 0x2c, 0x0c पूर्ण,
	अणु STV090x_16APSK_34,  0x0c, 0x0c, 0x0c, 0x0c, 0x0e, 0x0c, 0x2d, 0x0c, 0x1d, 0x0c पूर्ण,
	अणु STV090x_16APSK_45,  0x0c, 0x0c, 0x0c, 0x0c, 0x1e, 0x0c, 0x3d, 0x0c, 0x2d, 0x0c पूर्ण,
	अणु STV090x_16APSK_56,  0x0c, 0x0c, 0x0c, 0x0c, 0x1e, 0x0c, 0x3d, 0x0c, 0x2d, 0x0c पूर्ण,
	अणु STV090x_16APSK_89,  0x0c, 0x0c, 0x0c, 0x0c, 0x2e, 0x0c, 0x0e, 0x0c, 0x3d, 0x0c पूर्ण,
	अणु STV090x_16APSK_910, 0x0c, 0x0c, 0x0c, 0x0c, 0x2e, 0x0c, 0x0e, 0x0c, 0x3d, 0x0c पूर्ण,
	अणु STV090x_32APSK_34,  0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c पूर्ण,
	अणु STV090x_32APSK_45,  0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c पूर्ण,
	अणु STV090x_32APSK_56,  0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c पूर्ण,
	अणु STV090x_32APSK_89,  0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c पूर्ण,
	अणु STV090x_32APSK_910, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c पूर्ण
पूर्ण;

/* Cut 3.0 Long Frame Tracking CR Loop */
अटल काष्ठा stv090x_दीर्घ_frame_crloop	stv090x_s2_apsk_crl_cut30[] = अणु
	/* MODCOD  2MPon 2MPoff 5MPon 5MPoff 10MPon 10MPoff 20MPon 20MPoff 30MPon 30MPoff */
	अणु STV090x_16APSK_23,  0x0a, 0x0a, 0x0a, 0x0a, 0x1a, 0x0a, 0x3a, 0x0a, 0x2a, 0x0a पूर्ण,
	अणु STV090x_16APSK_34,  0x0a, 0x0a, 0x0a, 0x0a, 0x0b, 0x0a, 0x3b, 0x0a, 0x1b, 0x0a पूर्ण,
	अणु STV090x_16APSK_45,  0x0a, 0x0a, 0x0a, 0x0a, 0x1b, 0x0a, 0x3b, 0x0a, 0x2b, 0x0a पूर्ण,
	अणु STV090x_16APSK_56,  0x0a, 0x0a, 0x0a, 0x0a, 0x1b, 0x0a, 0x3b, 0x0a, 0x2b, 0x0a पूर्ण,
	अणु STV090x_16APSK_89,  0x0a, 0x0a, 0x0a, 0x0a, 0x2b, 0x0a, 0x0c, 0x0a, 0x3b, 0x0a पूर्ण,
	अणु STV090x_16APSK_910, 0x0a, 0x0a, 0x0a, 0x0a, 0x2b, 0x0a, 0x0c, 0x0a, 0x3b, 0x0a पूर्ण,
	अणु STV090x_32APSK_34,  0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a पूर्ण,
	अणु STV090x_32APSK_45,  0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a पूर्ण,
	अणु STV090x_32APSK_56,  0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a पूर्ण,
	अणु STV090x_32APSK_89,  0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a पूर्ण,
	अणु STV090x_32APSK_910, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a पूर्ण
पूर्ण;

अटल काष्ठा stv090x_दीर्घ_frame_crloop stv090x_s2_lowqpsk_crl_cut20[] = अणु
	/* MODCOD  2MPon 2MPoff 5MPon 5MPoff 10MPon 10MPoff 20MPon 20MPoff 30MPon 30MPoff */
	अणु STV090x_QPSK_14,  0x0f, 0x3f, 0x0e, 0x3f, 0x2d, 0x2f, 0x2d, 0x1f, 0x3d, 0x3e पूर्ण,
	अणु STV090x_QPSK_13,  0x0f, 0x3f, 0x0e, 0x3f, 0x2d, 0x2f, 0x3d, 0x0f, 0x3d, 0x2e पूर्ण,
	अणु STV090x_QPSK_25,  0x1f, 0x3f, 0x1e, 0x3f, 0x3d, 0x1f, 0x3d, 0x3e, 0x3d, 0x2e पूर्ण
पूर्ण;

अटल काष्ठा stv090x_दीर्घ_frame_crloop	stv090x_s2_lowqpsk_crl_cut30[] = अणु
	/* MODCOD  2MPon 2MPoff 5MPon 5MPoff 10MPon 10MPoff 20MPon 20MPoff 30MPon 30MPoff */
	अणु STV090x_QPSK_14,  0x0c, 0x3c, 0x0b, 0x3c, 0x2a, 0x2c, 0x2a, 0x1c, 0x3a, 0x3b पूर्ण,
	अणु STV090x_QPSK_13,  0x0c, 0x3c, 0x0b, 0x3c, 0x2a, 0x2c, 0x3a, 0x0c, 0x3a, 0x2b पूर्ण,
	अणु STV090x_QPSK_25,  0x1c, 0x3c, 0x1b, 0x3c, 0x3a, 0x1c, 0x3a, 0x3b, 0x3a, 0x2b पूर्ण
पूर्ण;

/* Cut 2.0 Short Frame Tracking CR Loop */
अटल काष्ठा stv090x_लघु_frame_crloop stv090x_s2_लघु_crl_cut20[] = अणु
	/* MODCOD	  2M    5M    10M   20M   30M */
	अणु STV090x_QPSK,   0x2f, 0x2e, 0x0e, 0x0e, 0x3d पूर्ण,
	अणु STV090x_8PSK,   0x3e, 0x0e, 0x2d, 0x0d, 0x3c पूर्ण,
	अणु STV090x_16APSK, 0x1e, 0x1e, 0x1e, 0x3d, 0x2d पूर्ण,
	अणु STV090x_32APSK, 0x1e, 0x1e, 0x1e, 0x3d, 0x2d पूर्ण
पूर्ण;

/* Cut 3.0 Short Frame Tracking CR Loop */
अटल काष्ठा stv090x_लघु_frame_crloop stv090x_s2_लघु_crl_cut30[] = अणु
	/* MODCOD	  2M	5M    10M   20M	  30M */
	अणु STV090x_QPSK,   0x2C, 0x2B, 0x0B, 0x0B, 0x3A पूर्ण,
	अणु STV090x_8PSK,   0x3B, 0x0B, 0x2A, 0x0A, 0x39 पूर्ण,
	अणु STV090x_16APSK, 0x1B, 0x1B, 0x1B, 0x3A, 0x2A पूर्ण,
	अणु STV090x_32APSK, 0x1B, 0x1B, 0x1B, 0x3A, 0x2A पूर्ण
पूर्ण;

अटल अंतरभूत s32 comp2(s32 __x, s32 __width)
अणु
	अगर (__width == 32)
		वापस __x;
	अन्यथा
		वापस (__x >= (1 << (__width - 1))) ? (__x - (1 << __width)) : __x;
पूर्ण

अटल पूर्णांक stv090x_पढ़ो_reg(काष्ठा stv090x_state *state, अचिन्हित पूर्णांक reg)
अणु
	स्थिर काष्ठा stv090x_config *config = state->config;
	पूर्णांक ret;

	u8 b0[] = अणु reg >> 8, reg & 0xff पूर्ण;
	u8 buf;

	काष्ठा i2c_msg msg[] = अणु
		अणु .addr	= config->address, .flags	= 0,		.buf = b0,   .len = 2 पूर्ण,
		अणु .addr	= config->address, .flags	= I2C_M_RD,	.buf = &buf, .len = 1 पूर्ण
	पूर्ण;

	ret = i2c_transfer(state->i2c, msg, 2);
	अगर (ret != 2) अणु
		अगर (ret != -ERESTARTSYS)
			dprपूर्णांकk(FE_ERROR, 1,
				"Read error, Reg=[0x%02x], Status=%d",
				reg, ret);

		वापस ret < 0 ? ret : -EREMOTEIO;
	पूर्ण
	अगर (unlikely(*state->verbose >= FE_DEBUGREG))
		dprपूर्णांकk(FE_ERROR, 1, "Reg=[0x%02x], data=%02x",
			reg, buf);

	वापस (अचिन्हित पूर्णांक) buf;
पूर्ण

अटल पूर्णांक stv090x_ग_लिखो_regs(काष्ठा stv090x_state *state, अचिन्हित पूर्णांक reg, u8 *data, u32 count)
अणु
	स्थिर काष्ठा stv090x_config *config = state->config;
	पूर्णांक ret;
	u8 buf[MAX_XFER_SIZE];
	काष्ठा i2c_msg i2c_msg = अणु .addr = config->address, .flags = 0, .buf = buf, .len = 2 + count पूर्ण;

	अगर (2 + count > माप(buf)) अणु
		prपूर्णांकk(KERN_WARNING
		       "%s: i2c wr reg=%04x: len=%d is too big!\n",
		       KBUILD_MODNAME, reg, count);
		वापस -EINVAL;
	पूर्ण

	buf[0] = reg >> 8;
	buf[1] = reg & 0xff;
	स_नकल(&buf[2], data, count);

	dprपूर्णांकk(FE_DEBUGREG, 1, "%s [0x%04x]: %*ph",
		__func__, reg, count, data);

	ret = i2c_transfer(state->i2c, &i2c_msg, 1);
	अगर (ret != 1) अणु
		अगर (ret != -ERESTARTSYS)
			dprपूर्णांकk(FE_ERROR, 1, "Reg=[0x%04x], Data=[0x%02x ...], Count=%u, Status=%d",
				reg, data[0], count, ret);
		वापस ret < 0 ? ret : -EREMOTEIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक stv090x_ग_लिखो_reg(काष्ठा stv090x_state *state, अचिन्हित पूर्णांक reg, u8 data)
अणु
	u8 पंचांगp = data; /* see gcc.gnu.org/bugzilla/show_bug.cgi?id=81715 */

	वापस stv090x_ग_लिखो_regs(state, reg, &पंचांगp, 1);
पूर्ण

अटल पूर्णांक stv090x_i2c_gate_ctrl(काष्ठा stv090x_state *state, पूर्णांक enable)
अणु
	u32 reg;

	/*
	 * NOTE! A lock is used as a FSM to control the state in which
	 * access is serialized between two tuners on the same demod.
	 * This has nothing to करो with a lock to protect a critical section
	 * which may in some other हालs be confused with protecting I/O
	 * access to the demodulator gate.
	 * In हाल of any error, the lock is unlocked and निकास within the
	 * relevant operations themselves.
	 */
	अगर (enable) अणु
		अगर (state->config->tuner_i2c_lock)
			state->config->tuner_i2c_lock(&state->frontend, 1);
		अन्यथा
			mutex_lock(&state->पूर्णांकernal->tuner_lock);
	पूर्ण

	reg = STV090x_READ_DEMOD(state, I2CRPT);
	अगर (enable) अणु
		dprपूर्णांकk(FE_DEBUG, 1, "Enable Gate");
		STV090x_SETFIELD_Px(reg, I2CT_ON_FIELD, 1);
		अगर (STV090x_WRITE_DEMOD(state, I2CRPT, reg) < 0)
			जाओ err;

	पूर्ण अन्यथा अणु
		dprपूर्णांकk(FE_DEBUG, 1, "Disable Gate");
		STV090x_SETFIELD_Px(reg, I2CT_ON_FIELD, 0);
		अगर ((STV090x_WRITE_DEMOD(state, I2CRPT, reg)) < 0)
			जाओ err;
	पूर्ण

	अगर (!enable) अणु
		अगर (state->config->tuner_i2c_lock)
			state->config->tuner_i2c_lock(&state->frontend, 0);
		अन्यथा
			mutex_unlock(&state->पूर्णांकernal->tuner_lock);
	पूर्ण

	वापस 0;
err:
	dprपूर्णांकk(FE_ERROR, 1, "I/O error");
	अगर (state->config->tuner_i2c_lock)
		state->config->tuner_i2c_lock(&state->frontend, 0);
	अन्यथा
		mutex_unlock(&state->पूर्णांकernal->tuner_lock);
	वापस -1;
पूर्ण

अटल व्योम stv090x_get_lock_पंचांगg(काष्ठा stv090x_state *state)
अणु
	चयन (state->algo) अणु
	हाल STV090x_BLIND_SEARCH:
		dprपूर्णांकk(FE_DEBUG, 1, "Blind Search");
		अगर (state->srate <= 1500000) अणु  /*10Msps< SR <=15Msps*/
			state->DemodTimeout = 1500;
			state->FecTimeout = 400;
		पूर्ण अन्यथा अगर (state->srate <= 5000000) अणु  /*10Msps< SR <=15Msps*/
			state->DemodTimeout = 1000;
			state->FecTimeout = 300;
		पूर्ण अन्यथा अणु  /*SR >20Msps*/
			state->DemodTimeout = 700;
			state->FecTimeout = 100;
		पूर्ण
		अवरोध;

	हाल STV090x_COLD_SEARCH:
	हाल STV090x_WARM_SEARCH:
	शेष:
		dprपूर्णांकk(FE_DEBUG, 1, "Normal Search");
		अगर (state->srate <= 1000000) अणु  /*SR <=1Msps*/
			state->DemodTimeout = 4500;
			state->FecTimeout = 1700;
		पूर्ण अन्यथा अगर (state->srate <= 2000000) अणु /*1Msps < SR <= 2Msps */
			state->DemodTimeout = 2500;
			state->FecTimeout = 1100;
		पूर्ण अन्यथा अगर (state->srate <= 5000000) अणु /*2Msps < SR <= 5Msps */
			state->DemodTimeout = 1000;
			state->FecTimeout = 550;
		पूर्ण अन्यथा अगर (state->srate <= 10000000) अणु /*5Msps < SR <= 10Msps */
			state->DemodTimeout = 700;
			state->FecTimeout = 250;
		पूर्ण अन्यथा अगर (state->srate <= 20000000) अणु /*10Msps < SR <= 20Msps */
			state->DemodTimeout = 400;
			state->FecTimeout = 130;
		पूर्ण अन्यथा अणु   /*SR >20Msps*/
			state->DemodTimeout = 300;
			state->FecTimeout = 100;
		पूर्ण
		अवरोध;
	पूर्ण

	अगर (state->algo == STV090x_WARM_SEARCH)
		state->DemodTimeout /= 2;
पूर्ण

अटल पूर्णांक stv090x_set_srate(काष्ठा stv090x_state *state, u32 srate)
अणु
	u32 sym;

	अगर (srate > 60000000) अणु
		sym  = (srate << 4); /* SR * 2^16 / master_clk */
		sym /= (state->पूर्णांकernal->mclk >> 12);
	पूर्ण अन्यथा अगर (srate > 6000000) अणु
		sym  = (srate << 6);
		sym /= (state->पूर्णांकernal->mclk >> 10);
	पूर्ण अन्यथा अणु
		sym  = (srate << 9);
		sym /= (state->पूर्णांकernal->mclk >> 7);
	पूर्ण

	अगर (STV090x_WRITE_DEMOD(state, SFRINIT1, (sym >> 8) & 0x7f) < 0) /* MSB */
		जाओ err;
	अगर (STV090x_WRITE_DEMOD(state, SFRINIT0, (sym & 0xff)) < 0) /* LSB */
		जाओ err;

	वापस 0;
err:
	dprपूर्णांकk(FE_ERROR, 1, "I/O error");
	वापस -1;
पूर्ण

अटल पूर्णांक stv090x_set_max_srate(काष्ठा stv090x_state *state, u32 clk, u32 srate)
अणु
	u32 sym;

	srate = 105 * (srate / 100);
	अगर (srate > 60000000) अणु
		sym  = (srate << 4); /* SR * 2^16 / master_clk */
		sym /= (state->पूर्णांकernal->mclk >> 12);
	पूर्ण अन्यथा अगर (srate > 6000000) अणु
		sym  = (srate << 6);
		sym /= (state->पूर्णांकernal->mclk >> 10);
	पूर्ण अन्यथा अणु
		sym  = (srate << 9);
		sym /= (state->पूर्णांकernal->mclk >> 7);
	पूर्ण

	अगर (sym < 0x7fff) अणु
		अगर (STV090x_WRITE_DEMOD(state, SFRUP1, (sym >> 8) & 0x7f) < 0) /* MSB */
			जाओ err;
		अगर (STV090x_WRITE_DEMOD(state, SFRUP0, sym & 0xff) < 0) /* LSB */
			जाओ err;
	पूर्ण अन्यथा अणु
		अगर (STV090x_WRITE_DEMOD(state, SFRUP1, 0x7f) < 0) /* MSB */
			जाओ err;
		अगर (STV090x_WRITE_DEMOD(state, SFRUP0, 0xff) < 0) /* LSB */
			जाओ err;
	पूर्ण

	वापस 0;
err:
	dprपूर्णांकk(FE_ERROR, 1, "I/O error");
	वापस -1;
पूर्ण

अटल पूर्णांक stv090x_set_min_srate(काष्ठा stv090x_state *state, u32 clk, u32 srate)
अणु
	u32 sym;

	srate = 95 * (srate / 100);
	अगर (srate > 60000000) अणु
		sym  = (srate << 4); /* SR * 2^16 / master_clk */
		sym /= (state->पूर्णांकernal->mclk >> 12);
	पूर्ण अन्यथा अगर (srate > 6000000) अणु
		sym  = (srate << 6);
		sym /= (state->पूर्णांकernal->mclk >> 10);
	पूर्ण अन्यथा अणु
		sym  = (srate << 9);
		sym /= (state->पूर्णांकernal->mclk >> 7);
	पूर्ण

	अगर (STV090x_WRITE_DEMOD(state, SFRLOW1, ((sym >> 8) & 0x7f)) < 0) /* MSB */
		जाओ err;
	अगर (STV090x_WRITE_DEMOD(state, SFRLOW0, (sym & 0xff)) < 0) /* LSB */
		जाओ err;
	वापस 0;
err:
	dprपूर्णांकk(FE_ERROR, 1, "I/O error");
	वापस -1;
पूर्ण

अटल u32 stv090x_car_width(u32 srate, क्रमागत stv090x_rolloff rolloff)
अणु
	u32 ro;

	चयन (rolloff) अणु
	हाल STV090x_RO_20:
		ro = 20;
		अवरोध;
	हाल STV090x_RO_25:
		ro = 25;
		अवरोध;
	हाल STV090x_RO_35:
	शेष:
		ro = 35;
		अवरोध;
	पूर्ण

	वापस srate + (srate * ro) / 100;
पूर्ण

अटल पूर्णांक stv090x_set_vit_thacq(काष्ठा stv090x_state *state)
अणु
	अगर (STV090x_WRITE_DEMOD(state, VTH12, 0x96) < 0)
		जाओ err;
	अगर (STV090x_WRITE_DEMOD(state, VTH23, 0x64) < 0)
		जाओ err;
	अगर (STV090x_WRITE_DEMOD(state, VTH34, 0x36) < 0)
		जाओ err;
	अगर (STV090x_WRITE_DEMOD(state, VTH56, 0x23) < 0)
		जाओ err;
	अगर (STV090x_WRITE_DEMOD(state, VTH67, 0x1e) < 0)
		जाओ err;
	अगर (STV090x_WRITE_DEMOD(state, VTH78, 0x19) < 0)
		जाओ err;
	वापस 0;
err:
	dprपूर्णांकk(FE_ERROR, 1, "I/O error");
	वापस -1;
पूर्ण

अटल पूर्णांक stv090x_set_vit_thtracq(काष्ठा stv090x_state *state)
अणु
	अगर (STV090x_WRITE_DEMOD(state, VTH12, 0xd0) < 0)
		जाओ err;
	अगर (STV090x_WRITE_DEMOD(state, VTH23, 0x7d) < 0)
		जाओ err;
	अगर (STV090x_WRITE_DEMOD(state, VTH34, 0x53) < 0)
		जाओ err;
	अगर (STV090x_WRITE_DEMOD(state, VTH56, 0x2f) < 0)
		जाओ err;
	अगर (STV090x_WRITE_DEMOD(state, VTH67, 0x24) < 0)
		जाओ err;
	अगर (STV090x_WRITE_DEMOD(state, VTH78, 0x1f) < 0)
		जाओ err;
	वापस 0;
err:
	dprपूर्णांकk(FE_ERROR, 1, "I/O error");
	वापस -1;
पूर्ण

अटल पूर्णांक stv090x_set_viterbi(काष्ठा stv090x_state *state)
अणु
	चयन (state->search_mode) अणु
	हाल STV090x_SEARCH_AUTO:
		अगर (STV090x_WRITE_DEMOD(state, FECM, 0x10) < 0) /* DVB-S and DVB-S2 */
			जाओ err;
		अगर (STV090x_WRITE_DEMOD(state, PRVIT, 0x3f) < 0) /* all puncture rate */
			जाओ err;
		अवरोध;
	हाल STV090x_SEARCH_DVBS1:
		अगर (STV090x_WRITE_DEMOD(state, FECM, 0x00) < 0) /* disable DSS */
			जाओ err;
		चयन (state->fec) अणु
		हाल STV090x_PR12:
			अगर (STV090x_WRITE_DEMOD(state, PRVIT, 0x01) < 0)
				जाओ err;
			अवरोध;

		हाल STV090x_PR23:
			अगर (STV090x_WRITE_DEMOD(state, PRVIT, 0x02) < 0)
				जाओ err;
			अवरोध;

		हाल STV090x_PR34:
			अगर (STV090x_WRITE_DEMOD(state, PRVIT, 0x04) < 0)
				जाओ err;
			अवरोध;

		हाल STV090x_PR56:
			अगर (STV090x_WRITE_DEMOD(state, PRVIT, 0x08) < 0)
				जाओ err;
			अवरोध;

		हाल STV090x_PR78:
			अगर (STV090x_WRITE_DEMOD(state, PRVIT, 0x20) < 0)
				जाओ err;
			अवरोध;

		शेष:
			अगर (STV090x_WRITE_DEMOD(state, PRVIT, 0x2f) < 0) /* all */
				जाओ err;
			अवरोध;
		पूर्ण
		अवरोध;
	हाल STV090x_SEARCH_DSS:
		अगर (STV090x_WRITE_DEMOD(state, FECM, 0x80) < 0)
			जाओ err;
		चयन (state->fec) अणु
		हाल STV090x_PR12:
			अगर (STV090x_WRITE_DEMOD(state, PRVIT, 0x01) < 0)
				जाओ err;
			अवरोध;

		हाल STV090x_PR23:
			अगर (STV090x_WRITE_DEMOD(state, PRVIT, 0x02) < 0)
				जाओ err;
			अवरोध;

		हाल STV090x_PR67:
			अगर (STV090x_WRITE_DEMOD(state, PRVIT, 0x10) < 0)
				जाओ err;
			अवरोध;

		शेष:
			अगर (STV090x_WRITE_DEMOD(state, PRVIT, 0x13) < 0) /* 1/2, 2/3, 6/7 */
				जाओ err;
			अवरोध;
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस 0;
err:
	dprपूर्णांकk(FE_ERROR, 1, "I/O error");
	वापस -1;
पूर्ण

अटल पूर्णांक stv090x_stop_modcod(काष्ठा stv090x_state *state)
अणु
	अगर (STV090x_WRITE_DEMOD(state, MODCODLST0, 0xff) < 0)
		जाओ err;
	अगर (STV090x_WRITE_DEMOD(state, MODCODLST1, 0xff) < 0)
		जाओ err;
	अगर (STV090x_WRITE_DEMOD(state, MODCODLST2, 0xff) < 0)
		जाओ err;
	अगर (STV090x_WRITE_DEMOD(state, MODCODLST3, 0xff) < 0)
		जाओ err;
	अगर (STV090x_WRITE_DEMOD(state, MODCODLST4, 0xff) < 0)
		जाओ err;
	अगर (STV090x_WRITE_DEMOD(state, MODCODLST5, 0xff) < 0)
		जाओ err;
	अगर (STV090x_WRITE_DEMOD(state, MODCODLST6, 0xff) < 0)
		जाओ err;
	अगर (STV090x_WRITE_DEMOD(state, MODCODLST7, 0xff) < 0)
		जाओ err;
	अगर (STV090x_WRITE_DEMOD(state, MODCODLST8, 0xff) < 0)
		जाओ err;
	अगर (STV090x_WRITE_DEMOD(state, MODCODLST9, 0xff) < 0)
		जाओ err;
	अगर (STV090x_WRITE_DEMOD(state, MODCODLSTA, 0xff) < 0)
		जाओ err;
	अगर (STV090x_WRITE_DEMOD(state, MODCODLSTB, 0xff) < 0)
		जाओ err;
	अगर (STV090x_WRITE_DEMOD(state, MODCODLSTC, 0xff) < 0)
		जाओ err;
	अगर (STV090x_WRITE_DEMOD(state, MODCODLSTD, 0xff) < 0)
		जाओ err;
	अगर (STV090x_WRITE_DEMOD(state, MODCODLSTE, 0xff) < 0)
		जाओ err;
	अगर (STV090x_WRITE_DEMOD(state, MODCODLSTF, 0xff) < 0)
		जाओ err;
	वापस 0;
err:
	dprपूर्णांकk(FE_ERROR, 1, "I/O error");
	वापस -1;
पूर्ण

अटल पूर्णांक stv090x_activate_modcod(काष्ठा stv090x_state *state)
अणु
	अगर (STV090x_WRITE_DEMOD(state, MODCODLST0, 0xff) < 0)
		जाओ err;
	अगर (STV090x_WRITE_DEMOD(state, MODCODLST1, 0xfc) < 0)
		जाओ err;
	अगर (STV090x_WRITE_DEMOD(state, MODCODLST2, 0xcc) < 0)
		जाओ err;
	अगर (STV090x_WRITE_DEMOD(state, MODCODLST3, 0xcc) < 0)
		जाओ err;
	अगर (STV090x_WRITE_DEMOD(state, MODCODLST4, 0xcc) < 0)
		जाओ err;
	अगर (STV090x_WRITE_DEMOD(state, MODCODLST5, 0xcc) < 0)
		जाओ err;
	अगर (STV090x_WRITE_DEMOD(state, MODCODLST6, 0xcc) < 0)
		जाओ err;
	अगर (STV090x_WRITE_DEMOD(state, MODCODLST7, 0xcc) < 0)
		जाओ err;
	अगर (STV090x_WRITE_DEMOD(state, MODCODLST8, 0xcc) < 0)
		जाओ err;
	अगर (STV090x_WRITE_DEMOD(state, MODCODLST9, 0xcc) < 0)
		जाओ err;
	अगर (STV090x_WRITE_DEMOD(state, MODCODLSTA, 0xcc) < 0)
		जाओ err;
	अगर (STV090x_WRITE_DEMOD(state, MODCODLSTB, 0xcc) < 0)
		जाओ err;
	अगर (STV090x_WRITE_DEMOD(state, MODCODLSTC, 0xcc) < 0)
		जाओ err;
	अगर (STV090x_WRITE_DEMOD(state, MODCODLSTD, 0xcc) < 0)
		जाओ err;
	अगर (STV090x_WRITE_DEMOD(state, MODCODLSTE, 0xcc) < 0)
		जाओ err;
	अगर (STV090x_WRITE_DEMOD(state, MODCODLSTF, 0xcf) < 0)
		जाओ err;

	वापस 0;
err:
	dprपूर्णांकk(FE_ERROR, 1, "I/O error");
	वापस -1;
पूर्ण

अटल पूर्णांक stv090x_activate_modcod_single(काष्ठा stv090x_state *state)
अणु

	अगर (STV090x_WRITE_DEMOD(state, MODCODLST0, 0xff) < 0)
		जाओ err;
	अगर (STV090x_WRITE_DEMOD(state, MODCODLST1, 0xf0) < 0)
		जाओ err;
	अगर (STV090x_WRITE_DEMOD(state, MODCODLST2, 0x00) < 0)
		जाओ err;
	अगर (STV090x_WRITE_DEMOD(state, MODCODLST3, 0x00) < 0)
		जाओ err;
	अगर (STV090x_WRITE_DEMOD(state, MODCODLST4, 0x00) < 0)
		जाओ err;
	अगर (STV090x_WRITE_DEMOD(state, MODCODLST5, 0x00) < 0)
		जाओ err;
	अगर (STV090x_WRITE_DEMOD(state, MODCODLST6, 0x00) < 0)
		जाओ err;
	अगर (STV090x_WRITE_DEMOD(state, MODCODLST7, 0x00) < 0)
		जाओ err;
	अगर (STV090x_WRITE_DEMOD(state, MODCODLST8, 0x00) < 0)
		जाओ err;
	अगर (STV090x_WRITE_DEMOD(state, MODCODLST9, 0x00) < 0)
		जाओ err;
	अगर (STV090x_WRITE_DEMOD(state, MODCODLSTA, 0x00) < 0)
		जाओ err;
	अगर (STV090x_WRITE_DEMOD(state, MODCODLSTB, 0x00) < 0)
		जाओ err;
	अगर (STV090x_WRITE_DEMOD(state, MODCODLSTC, 0x00) < 0)
		जाओ err;
	अगर (STV090x_WRITE_DEMOD(state, MODCODLSTD, 0x00) < 0)
		जाओ err;
	अगर (STV090x_WRITE_DEMOD(state, MODCODLSTE, 0x00) < 0)
		जाओ err;
	अगर (STV090x_WRITE_DEMOD(state, MODCODLSTF, 0x0f) < 0)
		जाओ err;

	वापस 0;

err:
	dprपूर्णांकk(FE_ERROR, 1, "I/O error");
	वापस -1;
पूर्ण

अटल पूर्णांक stv090x_vitclk_ctl(काष्ठा stv090x_state *state, पूर्णांक enable)
अणु
	u32 reg;

	चयन (state->demod) अणु
	हाल STV090x_DEMODULATOR_0:
		mutex_lock(&state->पूर्णांकernal->demod_lock);
		reg = stv090x_पढ़ो_reg(state, STV090x_STOPCLK2);
		STV090x_SETFIELD(reg, STOP_CLKVIT1_FIELD, enable);
		अगर (stv090x_ग_लिखो_reg(state, STV090x_STOPCLK2, reg) < 0)
			जाओ err;
		mutex_unlock(&state->पूर्णांकernal->demod_lock);
		अवरोध;

	हाल STV090x_DEMODULATOR_1:
		mutex_lock(&state->पूर्णांकernal->demod_lock);
		reg = stv090x_पढ़ो_reg(state, STV090x_STOPCLK2);
		STV090x_SETFIELD(reg, STOP_CLKVIT2_FIELD, enable);
		अगर (stv090x_ग_लिखो_reg(state, STV090x_STOPCLK2, reg) < 0)
			जाओ err;
		mutex_unlock(&state->पूर्णांकernal->demod_lock);
		अवरोध;

	शेष:
		dprपूर्णांकk(FE_ERROR, 1, "Wrong demodulator!");
		अवरोध;
	पूर्ण
	वापस 0;
err:
	mutex_unlock(&state->पूर्णांकernal->demod_lock);
	dprपूर्णांकk(FE_ERROR, 1, "I/O error");
	वापस -1;
पूर्ण

अटल पूर्णांक stv090x_dvbs_track_crl(काष्ठा stv090x_state *state)
अणु
	अगर (state->पूर्णांकernal->dev_ver >= 0x30) अणु
		/* Set ACLC BCLC optimised value vs SR */
		अगर (state->srate >= 15000000) अणु
			अगर (STV090x_WRITE_DEMOD(state, ACLC, 0x2b) < 0)
				जाओ err;
			अगर (STV090x_WRITE_DEMOD(state, BCLC, 0x1a) < 0)
				जाओ err;
		पूर्ण अन्यथा अगर ((state->srate >= 7000000) && (15000000 > state->srate)) अणु
			अगर (STV090x_WRITE_DEMOD(state, ACLC, 0x0c) < 0)
				जाओ err;
			अगर (STV090x_WRITE_DEMOD(state, BCLC, 0x1b) < 0)
				जाओ err;
		पूर्ण अन्यथा अगर (state->srate < 7000000) अणु
			अगर (STV090x_WRITE_DEMOD(state, ACLC, 0x2c) < 0)
				जाओ err;
			अगर (STV090x_WRITE_DEMOD(state, BCLC, 0x1c) < 0)
				जाओ err;
		पूर्ण

	पूर्ण अन्यथा अणु
		/* Cut 2.0 */
		अगर (STV090x_WRITE_DEMOD(state, ACLC, 0x1a) < 0)
			जाओ err;
		अगर (STV090x_WRITE_DEMOD(state, BCLC, 0x09) < 0)
			जाओ err;
	पूर्ण
	वापस 0;
err:
	dprपूर्णांकk(FE_ERROR, 1, "I/O error");
	वापस -1;
पूर्ण

अटल पूर्णांक stv090x_delivery_search(काष्ठा stv090x_state *state)
अणु
	u32 reg;

	चयन (state->search_mode) अणु
	हाल STV090x_SEARCH_DVBS1:
	हाल STV090x_SEARCH_DSS:
		reg = STV090x_READ_DEMOD(state, DMDCFGMD);
		STV090x_SETFIELD_Px(reg, DVBS1_ENABLE_FIELD, 1);
		STV090x_SETFIELD_Px(reg, DVBS2_ENABLE_FIELD, 0);
		अगर (STV090x_WRITE_DEMOD(state, DMDCFGMD, reg) < 0)
			जाओ err;

		/* Activate Viterbi decoder in legacy search,
		 * करो not use FRESVIT1, might impact VITERBI2
		 */
		अगर (stv090x_vitclk_ctl(state, 0) < 0)
			जाओ err;

		अगर (stv090x_dvbs_track_crl(state) < 0)
			जाओ err;

		अगर (STV090x_WRITE_DEMOD(state, CAR2CFG, 0x22) < 0) /* disable DVB-S2 */
			जाओ err;

		अगर (stv090x_set_vit_thacq(state) < 0)
			जाओ err;
		अगर (stv090x_set_viterbi(state) < 0)
			जाओ err;
		अवरोध;

	हाल STV090x_SEARCH_DVBS2:
		reg = STV090x_READ_DEMOD(state, DMDCFGMD);
		STV090x_SETFIELD_Px(reg, DVBS1_ENABLE_FIELD, 0);
		STV090x_SETFIELD_Px(reg, DVBS2_ENABLE_FIELD, 0);
		अगर (STV090x_WRITE_DEMOD(state, DMDCFGMD, reg) < 0)
			जाओ err;
		STV090x_SETFIELD_Px(reg, DVBS1_ENABLE_FIELD, 1);
		STV090x_SETFIELD_Px(reg, DVBS2_ENABLE_FIELD, 1);
		अगर (STV090x_WRITE_DEMOD(state, DMDCFGMD, reg) < 0)
			जाओ err;

		अगर (stv090x_vitclk_ctl(state, 1) < 0)
			जाओ err;

		अगर (STV090x_WRITE_DEMOD(state, ACLC, 0x1a) < 0) /* stop DVB-S CR loop */
			जाओ err;
		अगर (STV090x_WRITE_DEMOD(state, BCLC, 0x09) < 0)
			जाओ err;

		अगर (state->पूर्णांकernal->dev_ver <= 0x20) अणु
			/* enable S2 carrier loop */
			अगर (STV090x_WRITE_DEMOD(state, CAR2CFG, 0x26) < 0)
				जाओ err;
		पूर्ण अन्यथा अणु
			/* > Cut 3: Stop carrier 3 */
			अगर (STV090x_WRITE_DEMOD(state, CAR2CFG, 0x66) < 0)
				जाओ err;
		पूर्ण

		अगर (state->demod_mode != STV090x_SINGLE) अणु
			/* Cut 2: enable link during search */
			अगर (stv090x_activate_modcod(state) < 0)
				जाओ err;
		पूर्ण अन्यथा अणु
			/* Single demodulator
			 * Authorize SHORT and LONG frames,
			 * QPSK, 8PSK, 16APSK and 32APSK
			 */
			अगर (stv090x_activate_modcod_single(state) < 0)
				जाओ err;
		पूर्ण

		अगर (stv090x_set_vit_thtracq(state) < 0)
			जाओ err;
		अवरोध;

	हाल STV090x_SEARCH_AUTO:
	शेष:
		/* enable DVB-S2 and DVB-S2 in Auto MODE */
		reg = STV090x_READ_DEMOD(state, DMDCFGMD);
		STV090x_SETFIELD_Px(reg, DVBS1_ENABLE_FIELD, 0);
		STV090x_SETFIELD_Px(reg, DVBS2_ENABLE_FIELD, 0);
		अगर (STV090x_WRITE_DEMOD(state, DMDCFGMD, reg) < 0)
			जाओ err;
		STV090x_SETFIELD_Px(reg, DVBS1_ENABLE_FIELD, 1);
		STV090x_SETFIELD_Px(reg, DVBS2_ENABLE_FIELD, 1);
		अगर (STV090x_WRITE_DEMOD(state, DMDCFGMD, reg) < 0)
			जाओ err;

		अगर (stv090x_vitclk_ctl(state, 0) < 0)
			जाओ err;

		अगर (stv090x_dvbs_track_crl(state) < 0)
			जाओ err;

		अगर (state->पूर्णांकernal->dev_ver <= 0x20) अणु
			/* enable S2 carrier loop */
			अगर (STV090x_WRITE_DEMOD(state, CAR2CFG, 0x26) < 0)
				जाओ err;
		पूर्ण अन्यथा अणु
			/* > Cut 3: Stop carrier 3 */
			अगर (STV090x_WRITE_DEMOD(state, CAR2CFG, 0x66) < 0)
				जाओ err;
		पूर्ण

		अगर (state->demod_mode != STV090x_SINGLE) अणु
			/* Cut 2: enable link during search */
			अगर (stv090x_activate_modcod(state) < 0)
				जाओ err;
		पूर्ण अन्यथा अणु
			/* Single demodulator
			 * Authorize SHORT and LONG frames,
			 * QPSK, 8PSK, 16APSK and 32APSK
			 */
			अगर (stv090x_activate_modcod_single(state) < 0)
				जाओ err;
		पूर्ण

		अगर (stv090x_set_vit_thacq(state) < 0)
			जाओ err;

		अगर (stv090x_set_viterbi(state) < 0)
			जाओ err;
		अवरोध;
	पूर्ण
	वापस 0;
err:
	dprपूर्णांकk(FE_ERROR, 1, "I/O error");
	वापस -1;
पूर्ण

अटल पूर्णांक stv090x_start_search(काष्ठा stv090x_state *state)
अणु
	u32 reg, freq_असल;
	s16 freq;

	/* Reset demodulator */
	reg = STV090x_READ_DEMOD(state, DMDISTATE);
	STV090x_SETFIELD_Px(reg, I2C_DEMOD_MODE_FIELD, 0x1f);
	अगर (STV090x_WRITE_DEMOD(state, DMDISTATE, reg) < 0)
		जाओ err;

	अगर (state->पूर्णांकernal->dev_ver <= 0x20) अणु
		अगर (state->srate <= 5000000) अणु
			अगर (STV090x_WRITE_DEMOD(state, CARCFG, 0x44) < 0)
				जाओ err;
			अगर (STV090x_WRITE_DEMOD(state, CFRUP1, 0x0f) < 0)
				जाओ err;
			अगर (STV090x_WRITE_DEMOD(state, CFRUP0, 0xff) < 0)
				जाओ err;
			अगर (STV090x_WRITE_DEMOD(state, CFRLOW1, 0xf0) < 0)
				जाओ err;
			अगर (STV090x_WRITE_DEMOD(state, CFRLOW0, 0x00) < 0)
				जाओ err;

			/*enlarge the timing bandwidth क्रम Low SR*/
			अगर (STV090x_WRITE_DEMOD(state, RTCS2, 0x68) < 0)
				जाओ err;
		पूर्ण अन्यथा अणु
			/* If the symbol rate is >5 Msps
			Set The carrier search up and low to स्वतः mode */
			अगर (STV090x_WRITE_DEMOD(state, CARCFG, 0xc4) < 0)
				जाओ err;
			/*reduce the timing bandwidth क्रम high SR*/
			अगर (STV090x_WRITE_DEMOD(state, RTCS2, 0x44) < 0)
				जाओ err;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* >= Cut 3 */
		अगर (state->srate <= 5000000) अणु
			/* enlarge the timing bandwidth क्रम Low SR */
			STV090x_WRITE_DEMOD(state, RTCS2, 0x68);
		पूर्ण अन्यथा अणु
			/* reduce timing bandwidth क्रम high SR */
			STV090x_WRITE_DEMOD(state, RTCS2, 0x44);
		पूर्ण

		/* Set CFR min and max to manual mode */
		STV090x_WRITE_DEMOD(state, CARCFG, 0x46);

		अगर (state->algo == STV090x_WARM_SEARCH) अणु
			/* WARM Start
			 * CFR min = -1MHz,
			 * CFR max = +1MHz
			 */
			freq_असल  = 1000 << 16;
			freq_असल /= (state->पूर्णांकernal->mclk / 1000);
			freq      = (s16) freq_असल;
		पूर्ण अन्यथा अणु
			/* COLD Start
			 * CFR min =- (SearchRange / 2 + 600KHz)
			 * CFR max = +(SearchRange / 2 + 600KHz)
			 * (600KHz क्रम the tuner step size)
			 */
			freq_असल  = (state->search_range / 2000) + 600;
			freq_असल  = freq_असल << 16;
			freq_असल /= (state->पूर्णांकernal->mclk / 1000);
			freq      = (s16) freq_असल;
		पूर्ण

		अगर (STV090x_WRITE_DEMOD(state, CFRUP1, MSB(freq)) < 0)
			जाओ err;
		अगर (STV090x_WRITE_DEMOD(state, CFRUP0, LSB(freq)) < 0)
			जाओ err;

		freq *= -1;

		अगर (STV090x_WRITE_DEMOD(state, CFRLOW1, MSB(freq)) < 0)
			जाओ err;
		अगर (STV090x_WRITE_DEMOD(state, CFRLOW0, LSB(freq)) < 0)
			जाओ err;

	पूर्ण

	अगर (STV090x_WRITE_DEMOD(state, CFRINIT1, 0) < 0)
		जाओ err;
	अगर (STV090x_WRITE_DEMOD(state, CFRINIT0, 0) < 0)
		जाओ err;

	अगर (state->पूर्णांकernal->dev_ver >= 0x20) अणु
		अगर (STV090x_WRITE_DEMOD(state, EQUALCFG, 0x41) < 0)
			जाओ err;
		अगर (STV090x_WRITE_DEMOD(state, FFECFG, 0x41) < 0)
			जाओ err;

		अगर ((state->search_mode == STV090x_SEARCH_DVBS1)	||
			(state->search_mode == STV090x_SEARCH_DSS)	||
			(state->search_mode == STV090x_SEARCH_AUTO)) अणु

			अगर (STV090x_WRITE_DEMOD(state, VITSCALE, 0x82) < 0)
				जाओ err;
			अगर (STV090x_WRITE_DEMOD(state, VAVSRVIT, 0x00) < 0)
				जाओ err;
		पूर्ण
	पूर्ण

	अगर (STV090x_WRITE_DEMOD(state, SFRSTEP, 0x00) < 0)
		जाओ err;
	अगर (STV090x_WRITE_DEMOD(state, TMGTHRISE, 0xe0) < 0)
		जाओ err;
	अगर (STV090x_WRITE_DEMOD(state, TMGTHFALL, 0xc0) < 0)
		जाओ err;

	reg = STV090x_READ_DEMOD(state, DMDCFGMD);
	STV090x_SETFIELD_Px(reg, SCAN_ENABLE_FIELD, 0);
	STV090x_SETFIELD_Px(reg, CFR_AUTOSCAN_FIELD, 0);
	अगर (STV090x_WRITE_DEMOD(state, DMDCFGMD, reg) < 0)
		जाओ err;
	reg = STV090x_READ_DEMOD(state, DMDCFG2);
	STV090x_SETFIELD_Px(reg, S1S2_SEQUENTIAL_FIELD, 0x0);
	अगर (STV090x_WRITE_DEMOD(state, DMDCFG2, reg) < 0)
		जाओ err;

	अगर (STV090x_WRITE_DEMOD(state, RTC, 0x88) < 0)
		जाओ err;

	अगर (state->पूर्णांकernal->dev_ver >= 0x20) अणु
		/*Frequency offset detector setting*/
		अगर (state->srate < 2000000) अणु
			अगर (state->पूर्णांकernal->dev_ver <= 0x20) अणु
				/* Cut 2 */
				अगर (STV090x_WRITE_DEMOD(state, CARFREQ, 0x39) < 0)
					जाओ err;
			पूर्ण अन्यथा अणु
				/* Cut 3 */
				अगर (STV090x_WRITE_DEMOD(state, CARFREQ, 0x89) < 0)
					जाओ err;
			पूर्ण
			अगर (STV090x_WRITE_DEMOD(state, CARHDR, 0x40) < 0)
				जाओ err;
		पूर्ण अन्यथा अगर (state->srate < 10000000) अणु
			अगर (STV090x_WRITE_DEMOD(state, CARFREQ, 0x4c) < 0)
				जाओ err;
			अगर (STV090x_WRITE_DEMOD(state, CARHDR, 0x20) < 0)
				जाओ err;
		पूर्ण अन्यथा अणु
			अगर (STV090x_WRITE_DEMOD(state, CARFREQ, 0x4b) < 0)
				जाओ err;
			अगर (STV090x_WRITE_DEMOD(state, CARHDR, 0x20) < 0)
				जाओ err;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (state->srate < 10000000) अणु
			अगर (STV090x_WRITE_DEMOD(state, CARFREQ, 0xef) < 0)
				जाओ err;
		पूर्ण अन्यथा अणु
			अगर (STV090x_WRITE_DEMOD(state, CARFREQ, 0xed) < 0)
				जाओ err;
		पूर्ण
	पूर्ण

	चयन (state->algo) अणु
	हाल STV090x_WARM_SEARCH:
		/* The symbol rate and the exact
		 * carrier Frequency are known
		 */
		अगर (STV090x_WRITE_DEMOD(state, DMDISTATE, 0x1f) < 0)
			जाओ err;
		अगर (STV090x_WRITE_DEMOD(state, DMDISTATE, 0x18) < 0)
			जाओ err;
		अवरोध;

	हाल STV090x_COLD_SEARCH:
		/* The symbol rate is known */
		अगर (STV090x_WRITE_DEMOD(state, DMDISTATE, 0x1f) < 0)
			जाओ err;
		अगर (STV090x_WRITE_DEMOD(state, DMDISTATE, 0x15) < 0)
			जाओ err;
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण
	वापस 0;
err:
	dprपूर्णांकk(FE_ERROR, 1, "I/O error");
	वापस -1;
पूर्ण

अटल पूर्णांक stv090x_get_agc2_min_level(काष्ठा stv090x_state *state)
अणु
	u32 agc2_min = 0xffff, agc2 = 0, freq_init, freq_step, reg;
	s32 i, j, steps, dir;

	अगर (STV090x_WRITE_DEMOD(state, AGC2REF, 0x38) < 0)
		जाओ err;
	reg = STV090x_READ_DEMOD(state, DMDCFGMD);
	STV090x_SETFIELD_Px(reg, SCAN_ENABLE_FIELD, 0);
	STV090x_SETFIELD_Px(reg, CFR_AUTOSCAN_FIELD, 0);
	अगर (STV090x_WRITE_DEMOD(state, DMDCFGMD, reg) < 0)
		जाओ err;

	अगर (STV090x_WRITE_DEMOD(state, SFRUP1, 0x83) < 0) /* SR = 65 Msps Max */
		जाओ err;
	अगर (STV090x_WRITE_DEMOD(state, SFRUP0, 0xc0) < 0)
		जाओ err;
	अगर (STV090x_WRITE_DEMOD(state, SFRLOW1, 0x82) < 0) /* SR= 400 ksps Min */
		जाओ err;
	अगर (STV090x_WRITE_DEMOD(state, SFRLOW0, 0xa0) < 0)
		जाओ err;
	अगर (STV090x_WRITE_DEMOD(state, DMDTOM, 0x00) < 0) /* stop acq @ coarse carrier state */
		जाओ err;
	अगर (stv090x_set_srate(state, 1000000) < 0)
		जाओ err;

	steps  = state->search_range / 1000000;
	अगर (steps <= 0)
		steps = 1;

	dir = 1;
	freq_step = (1000000 * 256) / (state->पूर्णांकernal->mclk / 256);
	freq_init = 0;

	क्रम (i = 0; i < steps; i++) अणु
		अगर (dir > 0)
			freq_init = freq_init + (freq_step * i);
		अन्यथा
			freq_init = freq_init - (freq_step * i);

		dir *= -1;

		अगर (STV090x_WRITE_DEMOD(state, DMDISTATE, 0x5c) < 0) /* Demod RESET */
			जाओ err;
		अगर (STV090x_WRITE_DEMOD(state, CFRINIT1, (freq_init >> 8) & 0xff) < 0)
			जाओ err;
		अगर (STV090x_WRITE_DEMOD(state, CFRINIT0, freq_init & 0xff) < 0)
			जाओ err;
		अगर (STV090x_WRITE_DEMOD(state, DMDISTATE, 0x58) < 0) /* Demod RESET */
			जाओ err;
		msleep(10);

		agc2 = 0;
		क्रम (j = 0; j < 10; j++) अणु
			agc2 += (STV090x_READ_DEMOD(state, AGC2I1) << 8) |
				STV090x_READ_DEMOD(state, AGC2I0);
		पूर्ण
		agc2 /= 10;
		अगर (agc2 < agc2_min)
			agc2_min = agc2;
	पूर्ण

	वापस agc2_min;
err:
	dprपूर्णांकk(FE_ERROR, 1, "I/O error");
	वापस -1;
पूर्ण

अटल u32 stv090x_get_srate(काष्ठा stv090x_state *state, u32 clk)
अणु
	u8 r3, r2, r1, r0;
	s32 srate, पूर्णांक_1, पूर्णांक_2, पंचांगp_1, पंचांगp_2;

	r3 = STV090x_READ_DEMOD(state, SFR3);
	r2 = STV090x_READ_DEMOD(state, SFR2);
	r1 = STV090x_READ_DEMOD(state, SFR1);
	r0 = STV090x_READ_DEMOD(state, SFR0);

	srate = ((r3 << 24) | (r2 << 16) | (r1 <<  8) | r0);

	पूर्णांक_1 = clk >> 16;
	पूर्णांक_2 = srate >> 16;

	पंचांगp_1 = clk % 0x10000;
	पंचांगp_2 = srate % 0x10000;

	srate = (पूर्णांक_1 * पूर्णांक_2) +
		((पूर्णांक_1 * पंचांगp_2) >> 16) +
		((पूर्णांक_2 * पंचांगp_1) >> 16);

	वापस srate;
पूर्ण

अटल u32 stv090x_srate_srch_coarse(काष्ठा stv090x_state *state)
अणु
	काष्ठा dvb_frontend *fe = &state->frontend;

	पूर्णांक पंचांगg_lock = 0, i;
	s32 पंचांगg_cpt = 0, dir = 1, steps, cur_step = 0, freq;
	u32 srate_coarse = 0, agc2 = 0, car_step = 1200, reg;
	u32 agc2th;

	अगर (state->पूर्णांकernal->dev_ver >= 0x30)
		agc2th = 0x2e00;
	अन्यथा
		agc2th = 0x1f00;

	reg = STV090x_READ_DEMOD(state, DMDISTATE);
	STV090x_SETFIELD_Px(reg, I2C_DEMOD_MODE_FIELD, 0x1f); /* Demod RESET */
	अगर (STV090x_WRITE_DEMOD(state, DMDISTATE, reg) < 0)
		जाओ err;
	अगर (STV090x_WRITE_DEMOD(state, TMGCFG, 0x12) < 0)
		जाओ err;
	अगर (STV090x_WRITE_DEMOD(state, TMGCFG2, 0xc0) < 0)
		जाओ err;
	अगर (STV090x_WRITE_DEMOD(state, TMGTHRISE, 0xf0) < 0)
		जाओ err;
	अगर (STV090x_WRITE_DEMOD(state, TMGTHFALL, 0xe0) < 0)
		जाओ err;
	reg = STV090x_READ_DEMOD(state, DMDCFGMD);
	STV090x_SETFIELD_Px(reg, SCAN_ENABLE_FIELD, 1);
	STV090x_SETFIELD_Px(reg, CFR_AUTOSCAN_FIELD, 0);
	अगर (STV090x_WRITE_DEMOD(state, DMDCFGMD, reg) < 0)
		जाओ err;

	अगर (STV090x_WRITE_DEMOD(state, SFRUP1, 0x83) < 0)
		जाओ err;
	अगर (STV090x_WRITE_DEMOD(state, SFRUP0, 0xc0) < 0)
		जाओ err;
	अगर (STV090x_WRITE_DEMOD(state, SFRLOW1, 0x82) < 0)
		जाओ err;
	अगर (STV090x_WRITE_DEMOD(state, SFRLOW0, 0xa0) < 0)
		जाओ err;
	अगर (STV090x_WRITE_DEMOD(state, DMDTOM, 0x00) < 0)
		जाओ err;
	अगर (STV090x_WRITE_DEMOD(state, AGC2REF, 0x50) < 0)
		जाओ err;

	अगर (state->पूर्णांकernal->dev_ver >= 0x30) अणु
		अगर (STV090x_WRITE_DEMOD(state, CARFREQ, 0x99) < 0)
			जाओ err;
		अगर (STV090x_WRITE_DEMOD(state, SFRSTEP, 0x98) < 0)
			जाओ err;

	पूर्ण अन्यथा अगर (state->पूर्णांकernal->dev_ver >= 0x20) अणु
		अगर (STV090x_WRITE_DEMOD(state, CARFREQ, 0x6a) < 0)
			जाओ err;
		अगर (STV090x_WRITE_DEMOD(state, SFRSTEP, 0x95) < 0)
			जाओ err;
	पूर्ण

	अगर (state->srate <= 2000000)
		car_step = 1000;
	अन्यथा अगर (state->srate <= 5000000)
		car_step = 2000;
	अन्यथा अगर (state->srate <= 12000000)
		car_step = 3000;
	अन्यथा
		car_step = 5000;

	steps  = -1 + ((state->search_range / 1000) / car_step);
	steps /= 2;
	steps  = (2 * steps) + 1;
	अगर (steps < 0)
		steps = 1;
	अन्यथा अगर (steps > 10) अणु
		steps = 11;
		car_step = (state->search_range / 1000) / 10;
	पूर्ण
	cur_step = 0;
	dir = 1;
	freq = state->frequency;

	जबतक ((!पंचांगg_lock) && (cur_step < steps)) अणु
		अगर (STV090x_WRITE_DEMOD(state, DMDISTATE, 0x5f) < 0) /* Demod RESET */
			जाओ err;
		अगर (STV090x_WRITE_DEMOD(state, CFRINIT1, 0x00) < 0)
			जाओ err;
		अगर (STV090x_WRITE_DEMOD(state, CFRINIT0, 0x00) < 0)
			जाओ err;
		अगर (STV090x_WRITE_DEMOD(state, SFRINIT1, 0x00) < 0)
			जाओ err;
		अगर (STV090x_WRITE_DEMOD(state, SFRINIT0, 0x00) < 0)
			जाओ err;
		/* trigger acquisition */
		अगर (STV090x_WRITE_DEMOD(state, DMDISTATE, 0x40) < 0)
			जाओ err;
		msleep(50);
		क्रम (i = 0; i < 10; i++) अणु
			reg = STV090x_READ_DEMOD(state, DSTATUS);
			अगर (STV090x_GETFIELD_Px(reg, TMGLOCK_QUALITY_FIELD) >= 2)
				पंचांगg_cpt++;
			agc2 += (STV090x_READ_DEMOD(state, AGC2I1) << 8) |
				STV090x_READ_DEMOD(state, AGC2I0);
		पूर्ण
		agc2 /= 10;
		srate_coarse = stv090x_get_srate(state, state->पूर्णांकernal->mclk);
		cur_step++;
		dir *= -1;
		अगर ((पंचांगg_cpt >= 5) && (agc2 < agc2th) &&
		    (srate_coarse < 50000000) && (srate_coarse > 850000))
			पंचांगg_lock = 1;
		अन्यथा अगर (cur_step < steps) अणु
			अगर (dir > 0)
				freq += cur_step * car_step;
			अन्यथा
				freq -= cur_step * car_step;

			/* Setup tuner */
			अगर (stv090x_i2c_gate_ctrl(state, 1) < 0)
				जाओ err;

			अगर (state->config->tuner_set_frequency) अणु
				अगर (state->config->tuner_set_frequency(fe, freq) < 0)
					जाओ err_gateoff;
			पूर्ण

			अगर (state->config->tuner_set_bandwidth) अणु
				अगर (state->config->tuner_set_bandwidth(fe, state->tuner_bw) < 0)
					जाओ err_gateoff;
			पूर्ण

			अगर (stv090x_i2c_gate_ctrl(state, 0) < 0)
				जाओ err;

			msleep(50);

			अगर (stv090x_i2c_gate_ctrl(state, 1) < 0)
				जाओ err;

			अगर (state->config->tuner_get_status) अणु
				अगर (state->config->tuner_get_status(fe, &reg) < 0)
					जाओ err_gateoff;
			पूर्ण

			अगर (reg)
				dprपूर्णांकk(FE_DEBUG, 1, "Tuner phase locked");
			अन्यथा
				dprपूर्णांकk(FE_DEBUG, 1, "Tuner unlocked");

			अगर (stv090x_i2c_gate_ctrl(state, 0) < 0)
				जाओ err;

		पूर्ण
	पूर्ण
	अगर (!पंचांगg_lock)
		srate_coarse = 0;
	अन्यथा
		srate_coarse = stv090x_get_srate(state, state->पूर्णांकernal->mclk);

	वापस srate_coarse;

err_gateoff:
	stv090x_i2c_gate_ctrl(state, 0);
err:
	dprपूर्णांकk(FE_ERROR, 1, "I/O error");
	वापस -1;
पूर्ण

अटल u32 stv090x_srate_srch_fine(काष्ठा stv090x_state *state)
अणु
	u32 srate_coarse, freq_coarse, sym, reg;

	srate_coarse = stv090x_get_srate(state, state->पूर्णांकernal->mclk);
	freq_coarse  = STV090x_READ_DEMOD(state, CFR2) << 8;
	freq_coarse |= STV090x_READ_DEMOD(state, CFR1);
	sym = 13 * (srate_coarse / 10); /* SFRUP = SFR + 30% */

	अगर (sym < state->srate)
		srate_coarse = 0;
	अन्यथा अणु
		अगर (STV090x_WRITE_DEMOD(state, DMDISTATE, 0x1f) < 0) /* Demod RESET */
			जाओ err;
		अगर (STV090x_WRITE_DEMOD(state, TMGCFG2, 0xc1) < 0)
			जाओ err;
		अगर (STV090x_WRITE_DEMOD(state, TMGTHRISE, 0x20) < 0)
			जाओ err;
		अगर (STV090x_WRITE_DEMOD(state, TMGTHFALL, 0x00) < 0)
			जाओ err;
		अगर (STV090x_WRITE_DEMOD(state, TMGCFG, 0xd2) < 0)
			जाओ err;
		reg = STV090x_READ_DEMOD(state, DMDCFGMD);
		STV090x_SETFIELD_Px(reg, CFR_AUTOSCAN_FIELD, 0x00);
		अगर (STV090x_WRITE_DEMOD(state, DMDCFGMD, reg) < 0)
			जाओ err;

		अगर (STV090x_WRITE_DEMOD(state, AGC2REF, 0x38) < 0)
			जाओ err;

		अगर (state->पूर्णांकernal->dev_ver >= 0x30) अणु
			अगर (STV090x_WRITE_DEMOD(state, CARFREQ, 0x79) < 0)
				जाओ err;
		पूर्ण अन्यथा अगर (state->पूर्णांकernal->dev_ver >= 0x20) अणु
			अगर (STV090x_WRITE_DEMOD(state, CARFREQ, 0x49) < 0)
				जाओ err;
		पूर्ण

		अगर (srate_coarse > 3000000) अणु
			sym  = 13 * (srate_coarse / 10); /* SFRUP = SFR + 30% */
			sym  = (sym / 1000) * 65536;
			sym /= (state->पूर्णांकernal->mclk / 1000);
			अगर (STV090x_WRITE_DEMOD(state, SFRUP1, (sym >> 8) & 0x7f) < 0)
				जाओ err;
			अगर (STV090x_WRITE_DEMOD(state, SFRUP0, sym & 0xff) < 0)
				जाओ err;
			sym  = 10 * (srate_coarse / 13); /* SFRLOW = SFR - 30% */
			sym  = (sym / 1000) * 65536;
			sym /= (state->पूर्णांकernal->mclk / 1000);
			अगर (STV090x_WRITE_DEMOD(state, SFRLOW1, (sym >> 8) & 0x7f) < 0)
				जाओ err;
			अगर (STV090x_WRITE_DEMOD(state, SFRLOW0, sym & 0xff) < 0)
				जाओ err;
			sym  = (srate_coarse / 1000) * 65536;
			sym /= (state->पूर्णांकernal->mclk / 1000);
			अगर (STV090x_WRITE_DEMOD(state, SFRINIT1, (sym >> 8) & 0xff) < 0)
				जाओ err;
			अगर (STV090x_WRITE_DEMOD(state, SFRINIT0, sym & 0xff) < 0)
				जाओ err;
		पूर्ण अन्यथा अणु
			sym  = 13 * (srate_coarse / 10); /* SFRUP = SFR + 30% */
			sym  = (sym / 100) * 65536;
			sym /= (state->पूर्णांकernal->mclk / 100);
			अगर (STV090x_WRITE_DEMOD(state, SFRUP1, (sym >> 8) & 0x7f) < 0)
				जाओ err;
			अगर (STV090x_WRITE_DEMOD(state, SFRUP0, sym & 0xff) < 0)
				जाओ err;
			sym  = 10 * (srate_coarse / 14); /* SFRLOW = SFR - 30% */
			sym  = (sym / 100) * 65536;
			sym /= (state->पूर्णांकernal->mclk / 100);
			अगर (STV090x_WRITE_DEMOD(state, SFRLOW1, (sym >> 8) & 0x7f) < 0)
				जाओ err;
			अगर (STV090x_WRITE_DEMOD(state, SFRLOW0, sym & 0xff) < 0)
				जाओ err;
			sym  = (srate_coarse / 100) * 65536;
			sym /= (state->पूर्णांकernal->mclk / 100);
			अगर (STV090x_WRITE_DEMOD(state, SFRINIT1, (sym >> 8) & 0xff) < 0)
				जाओ err;
			अगर (STV090x_WRITE_DEMOD(state, SFRINIT0, sym & 0xff) < 0)
				जाओ err;
		पूर्ण
		अगर (STV090x_WRITE_DEMOD(state, DMDTOM, 0x20) < 0)
			जाओ err;
		अगर (STV090x_WRITE_DEMOD(state, CFRINIT1, (freq_coarse >> 8) & 0xff) < 0)
			जाओ err;
		अगर (STV090x_WRITE_DEMOD(state, CFRINIT0, freq_coarse & 0xff) < 0)
			जाओ err;
		अगर (STV090x_WRITE_DEMOD(state, DMDISTATE, 0x15) < 0) /* trigger acquisition */
			जाओ err;
	पूर्ण

	वापस srate_coarse;

err:
	dprपूर्णांकk(FE_ERROR, 1, "I/O error");
	वापस -1;
पूर्ण

अटल पूर्णांक stv090x_get_dmdlock(काष्ठा stv090x_state *state, s32 समयout)
अणु
	s32 समयr = 0, lock = 0;
	u32 reg;
	u8 stat;

	जबतक ((समयr < समयout) && (!lock)) अणु
		reg = STV090x_READ_DEMOD(state, DMDSTATE);
		stat = STV090x_GETFIELD_Px(reg, HEADER_MODE_FIELD);

		चयन (stat) अणु
		हाल 0: /* searching */
		हाल 1: /* first PLH detected */
		शेष:
			dprपूर्णांकk(FE_DEBUG, 1, "Demodulator searching ..");
			lock = 0;
			अवरोध;
		हाल 2: /* DVB-S2 mode */
		हाल 3: /* DVB-S1/legacy mode */
			reg = STV090x_READ_DEMOD(state, DSTATUS);
			lock = STV090x_GETFIELD_Px(reg, LOCK_DEFINITIF_FIELD);
			अवरोध;
		पूर्ण

		अगर (!lock)
			msleep(10);
		अन्यथा
			dprपूर्णांकk(FE_DEBUG, 1, "Demodulator acquired LOCK");

		समयr += 10;
	पूर्ण
	वापस lock;
पूर्ण

अटल पूर्णांक stv090x_blind_search(काष्ठा stv090x_state *state)
अणु
	u32 agc2, reg, srate_coarse;
	s32 cpt_fail, agc2_ovflw, i;
	u8 k_ref, k_max, k_min;
	पूर्णांक coarse_fail = 0;
	पूर्णांक lock;

	k_max = 110;
	k_min = 10;

	agc2 = stv090x_get_agc2_min_level(state);

	अगर (agc2 > STV090x_SEARCH_AGC2_TH(state->पूर्णांकernal->dev_ver)) अणु
		lock = 0;
	पूर्ण अन्यथा अणु

		अगर (state->पूर्णांकernal->dev_ver <= 0x20) अणु
			अगर (STV090x_WRITE_DEMOD(state, CARCFG, 0xc4) < 0)
				जाओ err;
		पूर्ण अन्यथा अणु
			/* > Cut 3 */
			अगर (STV090x_WRITE_DEMOD(state, CARCFG, 0x06) < 0)
				जाओ err;
		पूर्ण

		अगर (STV090x_WRITE_DEMOD(state, RTCS2, 0x44) < 0)
			जाओ err;

		अगर (state->पूर्णांकernal->dev_ver >= 0x20) अणु
			अगर (STV090x_WRITE_DEMOD(state, EQUALCFG, 0x41) < 0)
				जाओ err;
			अगर (STV090x_WRITE_DEMOD(state, FFECFG, 0x41) < 0)
				जाओ err;
			अगर (STV090x_WRITE_DEMOD(state, VITSCALE, 0x82) < 0)
				जाओ err;
			अगर (STV090x_WRITE_DEMOD(state, VAVSRVIT, 0x00) < 0) /* set viterbi hysteresis */
				जाओ err;
		पूर्ण

		k_ref = k_max;
		करो अणु
			अगर (STV090x_WRITE_DEMOD(state, KREFTMG, k_ref) < 0)
				जाओ err;
			अगर (stv090x_srate_srch_coarse(state) != 0) अणु
				srate_coarse = stv090x_srate_srch_fine(state);
				अगर (srate_coarse != 0) अणु
					stv090x_get_lock_पंचांगg(state);
					lock = stv090x_get_dmdlock(state,
							state->DemodTimeout);
				पूर्ण अन्यथा अणु
					lock = 0;
				पूर्ण
			पूर्ण अन्यथा अणु
				cpt_fail = 0;
				agc2_ovflw = 0;
				क्रम (i = 0; i < 10; i++) अणु
					agc2 += (STV090x_READ_DEMOD(state, AGC2I1) << 8) |
						STV090x_READ_DEMOD(state, AGC2I0);
					अगर (agc2 >= 0xff00)
						agc2_ovflw++;
					reg = STV090x_READ_DEMOD(state, DSTATUS2);
					अगर ((STV090x_GETFIELD_Px(reg, CFR_OVERFLOW_FIELD) == 0x01) &&
					    (STV090x_GETFIELD_Px(reg, DEMOD_DELOCK_FIELD) == 0x01))

						cpt_fail++;
				पूर्ण
				अगर ((cpt_fail > 7) || (agc2_ovflw > 7))
					coarse_fail = 1;

				lock = 0;
			पूर्ण
			k_ref -= 20;
		पूर्ण जबतक ((k_ref >= k_min) && (!lock) && (!coarse_fail));
	पूर्ण

	वापस lock;

err:
	dprपूर्णांकk(FE_ERROR, 1, "I/O error");
	वापस -1;
पूर्ण

अटल पूर्णांक stv090x_chk_पंचांगg(काष्ठा stv090x_state *state)
अणु
	u32 reg;
	s32 पंचांगg_cpt = 0, i;
	u8 freq, पंचांगg_thh, पंचांगg_thl;
	पूर्णांक पंचांगg_lock = 0;

	freq = STV090x_READ_DEMOD(state, CARFREQ);
	पंचांगg_thh = STV090x_READ_DEMOD(state, TMGTHRISE);
	पंचांगg_thl = STV090x_READ_DEMOD(state, TMGTHFALL);
	अगर (STV090x_WRITE_DEMOD(state, TMGTHRISE, 0x20) < 0)
		जाओ err;
	अगर (STV090x_WRITE_DEMOD(state, TMGTHFALL, 0x00) < 0)
		जाओ err;

	reg = STV090x_READ_DEMOD(state, DMDCFGMD);
	STV090x_SETFIELD_Px(reg, CFR_AUTOSCAN_FIELD, 0x00); /* stop carrier offset search */
	अगर (STV090x_WRITE_DEMOD(state, DMDCFGMD, reg) < 0)
		जाओ err;
	अगर (STV090x_WRITE_DEMOD(state, RTC, 0x80) < 0)
		जाओ err;

	अगर (STV090x_WRITE_DEMOD(state, RTCS2, 0x40) < 0)
		जाओ err;
	अगर (STV090x_WRITE_DEMOD(state, CARFREQ, 0x00) < 0)
		जाओ err;

	अगर (STV090x_WRITE_DEMOD(state, CFRINIT1, 0x00) < 0) /* set car ofset to 0 */
		जाओ err;
	अगर (STV090x_WRITE_DEMOD(state, CFRINIT0, 0x00) < 0)
		जाओ err;
	अगर (STV090x_WRITE_DEMOD(state, AGC2REF, 0x65) < 0)
		जाओ err;

	अगर (STV090x_WRITE_DEMOD(state, DMDISTATE, 0x18) < 0) /* trigger acquisition */
		जाओ err;
	msleep(10);

	क्रम (i = 0; i < 10; i++) अणु
		reg = STV090x_READ_DEMOD(state, DSTATUS);
		अगर (STV090x_GETFIELD_Px(reg, TMGLOCK_QUALITY_FIELD) >= 2)
			पंचांगg_cpt++;
		msleep(1);
	पूर्ण
	अगर (पंचांगg_cpt >= 3)
		पंचांगg_lock = 1;

	अगर (STV090x_WRITE_DEMOD(state, AGC2REF, 0x38) < 0)
		जाओ err;
	अगर (STV090x_WRITE_DEMOD(state, RTC, 0x88) < 0) /* DVB-S1 timing */
		जाओ err;
	अगर (STV090x_WRITE_DEMOD(state, RTCS2, 0x68) < 0) /* DVB-S2 timing */
		जाओ err;

	अगर (STV090x_WRITE_DEMOD(state, CARFREQ, freq) < 0)
		जाओ err;
	अगर (STV090x_WRITE_DEMOD(state, TMGTHRISE, पंचांगg_thh) < 0)
		जाओ err;
	अगर (STV090x_WRITE_DEMOD(state, TMGTHFALL, पंचांगg_thl) < 0)
		जाओ err;

	वापस	पंचांगg_lock;

err:
	dprपूर्णांकk(FE_ERROR, 1, "I/O error");
	वापस -1;
पूर्ण

अटल पूर्णांक stv090x_get_coldlock(काष्ठा stv090x_state *state, s32 समयout_dmd)
अणु
	काष्ठा dvb_frontend *fe = &state->frontend;

	u32 reg;
	s32 car_step, steps, cur_step, dir, freq, समयout_lock;
	पूर्णांक lock;

	अगर (state->srate >= 10000000)
		समयout_lock = समयout_dmd / 3;
	अन्यथा
		समयout_lock = समयout_dmd / 2;

	lock = stv090x_get_dmdlock(state, समयout_lock); /* cold start रुको */
	अगर (lock)
		वापस lock;

	अगर (state->srate >= 10000000) अणु
		अगर (stv090x_chk_पंचांगg(state)) अणु
			अगर (STV090x_WRITE_DEMOD(state, DMDISTATE, 0x1f) < 0)
				जाओ err;
			अगर (STV090x_WRITE_DEMOD(state, DMDISTATE, 0x15) < 0)
				जाओ err;
			वापस stv090x_get_dmdlock(state, समयout_dmd);
		पूर्ण
		वापस 0;
	पूर्ण

	अगर (state->srate <= 4000000)
		car_step = 1000;
	अन्यथा अगर (state->srate <= 7000000)
		car_step = 2000;
	अन्यथा अगर (state->srate <= 10000000)
		car_step = 3000;
	अन्यथा
		car_step = 5000;

	steps  = (state->search_range / 1000) / car_step;
	steps /= 2;
	steps  = 2 * (steps + 1);
	अगर (steps < 0)
		steps = 2;
	अन्यथा अगर (steps > 12)
		steps = 12;

	cur_step = 1;
	dir = 1;

	freq = state->frequency;
	state->tuner_bw = stv090x_car_width(state->srate, state->rolloff) + state->srate;
	जबतक ((cur_step <= steps) && (!lock)) अणु
		अगर (dir > 0)
			freq += cur_step * car_step;
		अन्यथा
			freq -= cur_step * car_step;

		/* Setup tuner */
		अगर (stv090x_i2c_gate_ctrl(state, 1) < 0)
			जाओ err;

		अगर (state->config->tuner_set_frequency) अणु
			अगर (state->config->tuner_set_frequency(fe, freq) < 0)
				जाओ err_gateoff;
		पूर्ण

		अगर (state->config->tuner_set_bandwidth) अणु
			अगर (state->config->tuner_set_bandwidth(fe, state->tuner_bw) < 0)
				जाओ err_gateoff;
		पूर्ण

		अगर (stv090x_i2c_gate_ctrl(state, 0) < 0)
			जाओ err;

		msleep(50);

		अगर (stv090x_i2c_gate_ctrl(state, 1) < 0)
			जाओ err;

		अगर (state->config->tuner_get_status) अणु
			अगर (state->config->tuner_get_status(fe, &reg) < 0)
				जाओ err_gateoff;
			अगर (reg)
				dprपूर्णांकk(FE_DEBUG, 1, "Tuner phase locked");
			अन्यथा
				dprपूर्णांकk(FE_DEBUG, 1, "Tuner unlocked");
		पूर्ण

		अगर (stv090x_i2c_gate_ctrl(state, 0) < 0)
			जाओ err;

		STV090x_WRITE_DEMOD(state, DMDISTATE, 0x1c);
		अगर (STV090x_WRITE_DEMOD(state, CFRINIT1, 0x00) < 0)
			जाओ err;
		अगर (STV090x_WRITE_DEMOD(state, CFRINIT0, 0x00) < 0)
			जाओ err;
		अगर (STV090x_WRITE_DEMOD(state, DMDISTATE, 0x1f) < 0)
			जाओ err;
		अगर (STV090x_WRITE_DEMOD(state, DMDISTATE, 0x15) < 0)
			जाओ err;
		lock = stv090x_get_dmdlock(state, (समयout_dmd / 3));

		dir *= -1;
		cur_step++;
	पूर्ण

	वापस lock;

err_gateoff:
	stv090x_i2c_gate_ctrl(state, 0);
err:
	dprपूर्णांकk(FE_ERROR, 1, "I/O error");
	वापस -1;
पूर्ण

अटल पूर्णांक stv090x_get_loop_params(काष्ठा stv090x_state *state, s32 *freq_inc, s32 *समयout_sw, s32 *steps)
अणु
	s32 समयout, inc, steps_max, srate, car_max;

	srate = state->srate;
	car_max = state->search_range / 1000;
	car_max += car_max / 10;
	car_max  = 65536 * (car_max / 2);
	car_max /= (state->पूर्णांकernal->mclk / 1000);

	अगर (car_max > 0x4000)
		car_max = 0x4000 ; /* maxcarrier should be<= +-1/4 Mclk */

	inc  = srate;
	inc /= state->पूर्णांकernal->mclk / 1000;
	inc *= 256;
	inc *= 256;
	inc /= 1000;

	चयन (state->search_mode) अणु
	हाल STV090x_SEARCH_DVBS1:
	हाल STV090x_SEARCH_DSS:
		inc *= 3; /* freq step = 3% of srate */
		समयout = 20;
		अवरोध;

	हाल STV090x_SEARCH_DVBS2:
		inc *= 4;
		समयout = 25;
		अवरोध;

	हाल STV090x_SEARCH_AUTO:
	शेष:
		inc *= 3;
		समयout = 25;
		अवरोध;
	पूर्ण
	inc /= 100;
	अगर ((inc > car_max) || (inc < 0))
		inc = car_max / 2; /* increment <= 1/8 Mclk */

	समयout *= 27500; /* 27.5 Msps reference */
	अगर (srate > 0)
		समयout /= (srate / 1000);

	अगर ((समयout > 100) || (समयout < 0))
		समयout = 100;

	steps_max = (car_max / inc) + 1; /* min steps = 3 */
	अगर ((steps_max > 100) || (steps_max < 0)) अणु
		steps_max = 100; /* max steps <= 100 */
		inc = car_max / steps_max;
	पूर्ण
	*freq_inc = inc;
	*समयout_sw = समयout;
	*steps = steps_max;

	वापस 0;
पूर्ण

अटल पूर्णांक stv090x_chk_संकेत(काष्ठा stv090x_state *state)
अणु
	s32 offst_car, agc2, car_max;
	पूर्णांक no_संकेत;

	offst_car  = STV090x_READ_DEMOD(state, CFR2) << 8;
	offst_car |= STV090x_READ_DEMOD(state, CFR1);
	offst_car = comp2(offst_car, 16);

	agc2  = STV090x_READ_DEMOD(state, AGC2I1) << 8;
	agc2 |= STV090x_READ_DEMOD(state, AGC2I0);
	car_max = state->search_range / 1000;

	car_max += (car_max / 10); /* 10% margin */
	car_max  = (65536 * car_max / 2);
	car_max /= state->पूर्णांकernal->mclk / 1000;

	अगर (car_max > 0x4000)
		car_max = 0x4000;

	अगर ((agc2 > 0x2000) || (offst_car > 2 * car_max) || (offst_car < -2 * car_max)) अणु
		no_संकेत = 1;
		dprपूर्णांकk(FE_DEBUG, 1, "No Signal");
	पूर्ण अन्यथा अणु
		no_संकेत = 0;
		dprपूर्णांकk(FE_DEBUG, 1, "Found Signal");
	पूर्ण

	वापस no_संकेत;
पूर्ण

अटल पूर्णांक stv090x_search_car_loop(काष्ठा stv090x_state *state, s32 inc, s32 समयout, पूर्णांक zigzag, s32 steps_max)
अणु
	पूर्णांक no_संकेत, lock = 0;
	s32 cpt_step = 0, offst_freq, car_max;
	u32 reg;

	car_max  = state->search_range / 1000;
	car_max += (car_max / 10);
	car_max  = (65536 * car_max / 2);
	car_max /= (state->पूर्णांकernal->mclk / 1000);
	अगर (car_max > 0x4000)
		car_max = 0x4000;

	अगर (zigzag)
		offst_freq = 0;
	अन्यथा
		offst_freq = -car_max + inc;

	करो अणु
		अगर (STV090x_WRITE_DEMOD(state, DMDISTATE, 0x1c) < 0)
			जाओ err;
		अगर (STV090x_WRITE_DEMOD(state, CFRINIT1, ((offst_freq / 256) & 0xff)) < 0)
			जाओ err;
		अगर (STV090x_WRITE_DEMOD(state, CFRINIT0, offst_freq & 0xff) < 0)
			जाओ err;
		अगर (STV090x_WRITE_DEMOD(state, DMDISTATE, 0x18) < 0)
			जाओ err;

		reg = STV090x_READ_DEMOD(state, PDELCTRL1);
		STV090x_SETFIELD_Px(reg, ALGOSWRST_FIELD, 0x1); /* stop DVB-S2 packet delin */
		अगर (STV090x_WRITE_DEMOD(state, PDELCTRL1, reg) < 0)
			जाओ err;

		अगर (zigzag) अणु
			अगर (offst_freq >= 0)
				offst_freq = -offst_freq - 2 * inc;
			अन्यथा
				offst_freq = -offst_freq;
		पूर्ण अन्यथा अणु
			offst_freq += 2 * inc;
		पूर्ण

		cpt_step++;

		lock = stv090x_get_dmdlock(state, समयout);
		no_संकेत = stv090x_chk_संकेत(state);

	पूर्ण जबतक ((!lock) &&
		 (!no_संकेत) &&
		  ((offst_freq - inc) < car_max) &&
		  ((offst_freq + inc) > -car_max) &&
		  (cpt_step < steps_max));

	reg = STV090x_READ_DEMOD(state, PDELCTRL1);
	STV090x_SETFIELD_Px(reg, ALGOSWRST_FIELD, 0);
	अगर (STV090x_WRITE_DEMOD(state, PDELCTRL1, reg) < 0)
			जाओ err;

	वापस lock;
err:
	dprपूर्णांकk(FE_ERROR, 1, "I/O error");
	वापस -1;
पूर्ण

अटल पूर्णांक stv090x_sw_algo(काष्ठा stv090x_state *state)
अणु
	पूर्णांक no_संकेत, zigzag, lock = 0;
	u32 reg;

	s32 dvbs2_fly_wheel;
	s32 inc, समयout_step, trials, steps_max;

	/* get params */
	stv090x_get_loop_params(state, &inc, &समयout_step, &steps_max);

	चयन (state->search_mode) अणु
	हाल STV090x_SEARCH_DVBS1:
	हाल STV090x_SEARCH_DSS:
		/* accelerate the frequency detector */
		अगर (state->पूर्णांकernal->dev_ver >= 0x20) अणु
			अगर (STV090x_WRITE_DEMOD(state, CARFREQ, 0x3B) < 0)
				जाओ err;
		पूर्ण

		अगर (STV090x_WRITE_DEMOD(state, DMDCFGMD, 0x49) < 0)
			जाओ err;
		zigzag = 0;
		अवरोध;

	हाल STV090x_SEARCH_DVBS2:
		अगर (state->पूर्णांकernal->dev_ver >= 0x20) अणु
			अगर (STV090x_WRITE_DEMOD(state, CORRELABS, 0x79) < 0)
				जाओ err;
		पूर्ण

		अगर (STV090x_WRITE_DEMOD(state, DMDCFGMD, 0x89) < 0)
			जाओ err;
		zigzag = 1;
		अवरोध;

	हाल STV090x_SEARCH_AUTO:
	शेष:
		/* accelerate the frequency detector */
		अगर (state->पूर्णांकernal->dev_ver >= 0x20) अणु
			अगर (STV090x_WRITE_DEMOD(state, CARFREQ, 0x3b) < 0)
				जाओ err;
			अगर (STV090x_WRITE_DEMOD(state, CORRELABS, 0x79) < 0)
				जाओ err;
		पूर्ण

		अगर (STV090x_WRITE_DEMOD(state, DMDCFGMD, 0xc9) < 0)
			जाओ err;
		zigzag = 0;
		अवरोध;
	पूर्ण

	trials = 0;
	करो अणु
		lock = stv090x_search_car_loop(state, inc, समयout_step, zigzag, steps_max);
		no_संकेत = stv090x_chk_संकेत(state);
		trials++;

		/*run the SW search 2 बार maximum*/
		अगर (lock || no_संकेत || (trials == 2)) अणु
			/*Check अगर the demod is not losing lock in DVBS2*/
			अगर (state->पूर्णांकernal->dev_ver >= 0x20) अणु
				अगर (STV090x_WRITE_DEMOD(state, CARFREQ, 0x49) < 0)
					जाओ err;
				अगर (STV090x_WRITE_DEMOD(state, CORRELABS, 0x9e) < 0)
					जाओ err;
			पूर्ण

			reg = STV090x_READ_DEMOD(state, DMDSTATE);
			अगर ((lock) && (STV090x_GETFIELD_Px(reg, HEADER_MODE_FIELD) == STV090x_DVBS2)) अणु
				/*Check अगर the demod is not losing lock in DVBS2*/
				msleep(समयout_step);
				reg = STV090x_READ_DEMOD(state, DMDFLYW);
				dvbs2_fly_wheel = STV090x_GETFIELD_Px(reg, FLYWHEEL_CPT_FIELD);
				अगर (dvbs2_fly_wheel < 0xd) अणु	 /*अगर correct frames is decrementing */
					msleep(समयout_step);
					reg = STV090x_READ_DEMOD(state, DMDFLYW);
					dvbs2_fly_wheel = STV090x_GETFIELD_Px(reg, FLYWHEEL_CPT_FIELD);
				पूर्ण
				अगर (dvbs2_fly_wheel < 0xd) अणु
					/*FALSE lock, The demod is losing lock */
					lock = 0;
					अगर (trials < 2) अणु
						अगर (state->पूर्णांकernal->dev_ver >= 0x20) अणु
							अगर (STV090x_WRITE_DEMOD(state, CORRELABS, 0x79) < 0)
								जाओ err;
						पूर्ण

						अगर (STV090x_WRITE_DEMOD(state, DMDCFGMD, 0x89) < 0)
							जाओ err;
					पूर्ण
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण जबतक ((!lock) && (trials < 2) && (!no_संकेत));

	वापस lock;
err:
	dprपूर्णांकk(FE_ERROR, 1, "I/O error");
	वापस -1;
पूर्ण

अटल क्रमागत stv090x_delsys stv090x_get_std(काष्ठा stv090x_state *state)
अणु
	u32 reg;
	क्रमागत stv090x_delsys delsys;

	reg = STV090x_READ_DEMOD(state, DMDSTATE);
	अगर (STV090x_GETFIELD_Px(reg, HEADER_MODE_FIELD) == 2)
		delsys = STV090x_DVBS2;
	अन्यथा अगर (STV090x_GETFIELD_Px(reg, HEADER_MODE_FIELD) == 3) अणु
		reg = STV090x_READ_DEMOD(state, FECM);
		अगर (STV090x_GETFIELD_Px(reg, DSS_DVB_FIELD) == 1)
			delsys = STV090x_DSS;
		अन्यथा
			delsys = STV090x_DVBS1;
	पूर्ण अन्यथा अणु
		delsys = STV090x_ERROR;
	पूर्ण

	वापस delsys;
पूर्ण

/* in Hz */
अटल s32 stv090x_get_car_freq(काष्ठा stv090x_state *state, u32 mclk)
अणु
	s32 derot, पूर्णांक_1, पूर्णांक_2, पंचांगp_1, पंचांगp_2;

	derot  = STV090x_READ_DEMOD(state, CFR2) << 16;
	derot |= STV090x_READ_DEMOD(state, CFR1) <<  8;
	derot |= STV090x_READ_DEMOD(state, CFR0);

	derot = comp2(derot, 24);
	पूर्णांक_1 = mclk >> 12;
	पूर्णांक_2 = derot >> 12;

	/* carrier_frequency = MasterClock * Reg / 2^24 */
	पंचांगp_1 = mclk % 0x1000;
	पंचांगp_2 = derot % 0x1000;

	derot = (पूर्णांक_1 * पूर्णांक_2) +
		((पूर्णांक_1 * पंचांगp_2) >> 12) +
		((पूर्णांक_2 * पंचांगp_1) >> 12);

	वापस derot;
पूर्ण

अटल पूर्णांक stv090x_get_viterbi(काष्ठा stv090x_state *state)
अणु
	u32 reg, rate;

	reg = STV090x_READ_DEMOD(state, VITCURPUN);
	rate = STV090x_GETFIELD_Px(reg, VIT_CURPUN_FIELD);

	चयन (rate) अणु
	हाल 13:
		state->fec = STV090x_PR12;
		अवरोध;

	हाल 18:
		state->fec = STV090x_PR23;
		अवरोध;

	हाल 21:
		state->fec = STV090x_PR34;
		अवरोध;

	हाल 24:
		state->fec = STV090x_PR56;
		अवरोध;

	हाल 25:
		state->fec = STV090x_PR67;
		अवरोध;

	हाल 26:
		state->fec = STV090x_PR78;
		अवरोध;

	शेष:
		state->fec = STV090x_PRERR;
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल क्रमागत stv090x_संकेत_state stv090x_get_sig_params(काष्ठा stv090x_state *state)
अणु
	काष्ठा dvb_frontend *fe = &state->frontend;

	u8 पंचांगg;
	u32 reg;
	s32 i = 0, offst_freq;

	msleep(5);

	अगर (state->algo == STV090x_BLIND_SEARCH) अणु
		पंचांगg = STV090x_READ_DEMOD(state, TMGREG2);
		STV090x_WRITE_DEMOD(state, SFRSTEP, 0x5c);
		जबतक ((i <= 50) && (पंचांगg != 0) && (पंचांगg != 0xff)) अणु
			पंचांगg = STV090x_READ_DEMOD(state, TMGREG2);
			msleep(5);
			i += 5;
		पूर्ण
	पूर्ण
	state->delsys = stv090x_get_std(state);

	अगर (stv090x_i2c_gate_ctrl(state, 1) < 0)
		जाओ err;

	अगर (state->config->tuner_get_frequency) अणु
		अगर (state->config->tuner_get_frequency(fe, &state->frequency) < 0)
			जाओ err_gateoff;
	पूर्ण

	अगर (stv090x_i2c_gate_ctrl(state, 0) < 0)
		जाओ err;

	offst_freq = stv090x_get_car_freq(state, state->पूर्णांकernal->mclk) / 1000;
	state->frequency += offst_freq;

	अगर (stv090x_get_viterbi(state) < 0)
		जाओ err;

	reg = STV090x_READ_DEMOD(state, DMDMODCOD);
	state->modcod = STV090x_GETFIELD_Px(reg, DEMOD_MODCOD_FIELD);
	state->pilots = STV090x_GETFIELD_Px(reg, DEMOD_TYPE_FIELD) & 0x01;
	state->frame_len = STV090x_GETFIELD_Px(reg, DEMOD_TYPE_FIELD) >> 1;
	reg = STV090x_READ_DEMOD(state, TMGOBS);
	state->rolloff = STV090x_GETFIELD_Px(reg, ROLLOFF_STATUS_FIELD);
	reg = STV090x_READ_DEMOD(state, FECM);
	state->inversion = STV090x_GETFIELD_Px(reg, IQINV_FIELD);

	अगर ((state->algo == STV090x_BLIND_SEARCH) || (state->srate < 10000000)) अणु

		अगर (stv090x_i2c_gate_ctrl(state, 1) < 0)
			जाओ err;

		अगर (state->config->tuner_get_frequency) अणु
			अगर (state->config->tuner_get_frequency(fe, &state->frequency) < 0)
				जाओ err_gateoff;
		पूर्ण

		अगर (stv090x_i2c_gate_ctrl(state, 0) < 0)
			जाओ err;

		अगर (असल(offst_freq) <= ((state->search_range / 2000) + 500))
			वापस STV090x_RANGEOK;
		अन्यथा अगर (असल(offst_freq) <= (stv090x_car_width(state->srate, state->rolloff) / 2000))
			वापस STV090x_RANGEOK;
	पूर्ण अन्यथा अणु
		अगर (असल(offst_freq) <= ((state->search_range / 2000) + 500))
			वापस STV090x_RANGEOK;
	पूर्ण

	वापस STV090x_OUTOFRANGE;

err_gateoff:
	stv090x_i2c_gate_ctrl(state, 0);
err:
	dprपूर्णांकk(FE_ERROR, 1, "I/O error");
	वापस -1;
पूर्ण

अटल u32 stv090x_get_पंचांगgoffst(काष्ठा stv090x_state *state, u32 srate)
अणु
	s32 offst_पंचांगg;

	offst_पंचांगg  = STV090x_READ_DEMOD(state, TMGREG2) << 16;
	offst_पंचांगg |= STV090x_READ_DEMOD(state, TMGREG1) <<  8;
	offst_पंचांगg |= STV090x_READ_DEMOD(state, TMGREG0);

	offst_पंचांगg = comp2(offst_पंचांगg, 24); /* 2's complement */
	अगर (!offst_पंचांगg)
		offst_पंचांगg = 1;

	offst_पंचांगg  = ((s32) srate * 10) / ((s32) 0x1000000 / offst_पंचांगg);
	offst_पंचांगg /= 320;

	वापस offst_पंचांगg;
पूर्ण

अटल u8 stv090x_optimize_carloop(काष्ठा stv090x_state *state, क्रमागत stv090x_modcod modcod, s32 pilots)
अणु
	u8 aclc = 0x29;
	s32 i;
	काष्ठा stv090x_दीर्घ_frame_crloop *car_loop, *car_loop_qpsk_low, *car_loop_apsk_low;

	अगर (state->पूर्णांकernal->dev_ver == 0x20) अणु
		car_loop		= stv090x_s2_crl_cut20;
		car_loop_qpsk_low	= stv090x_s2_lowqpsk_crl_cut20;
		car_loop_apsk_low	= stv090x_s2_apsk_crl_cut20;
	पूर्ण अन्यथा अणु
		/* >= Cut 3 */
		car_loop		= stv090x_s2_crl_cut30;
		car_loop_qpsk_low	= stv090x_s2_lowqpsk_crl_cut30;
		car_loop_apsk_low	= stv090x_s2_apsk_crl_cut30;
	पूर्ण

	अगर (modcod < STV090x_QPSK_12) अणु
		i = 0;
		जबतक ((i < 3) && (modcod != car_loop_qpsk_low[i].modcod))
			i++;

		अगर (i >= 3)
			i = 2;

	पूर्ण अन्यथा अणु
		i = 0;
		जबतक ((i < 14) && (modcod != car_loop[i].modcod))
			i++;

		अगर (i >= 14) अणु
			i = 0;
			जबतक ((i < 11) && (modcod != car_loop_apsk_low[i].modcod))
				i++;

			अगर (i >= 11)
				i = 10;
		पूर्ण
	पूर्ण

	अगर (modcod <= STV090x_QPSK_25) अणु
		अगर (pilots) अणु
			अगर (state->srate <= 3000000)
				aclc = car_loop_qpsk_low[i].crl_pilots_on_2;
			अन्यथा अगर (state->srate <= 7000000)
				aclc = car_loop_qpsk_low[i].crl_pilots_on_5;
			अन्यथा अगर (state->srate <= 15000000)
				aclc = car_loop_qpsk_low[i].crl_pilots_on_10;
			अन्यथा अगर (state->srate <= 25000000)
				aclc = car_loop_qpsk_low[i].crl_pilots_on_20;
			अन्यथा
				aclc = car_loop_qpsk_low[i].crl_pilots_on_30;
		पूर्ण अन्यथा अणु
			अगर (state->srate <= 3000000)
				aclc = car_loop_qpsk_low[i].crl_pilots_off_2;
			अन्यथा अगर (state->srate <= 7000000)
				aclc = car_loop_qpsk_low[i].crl_pilots_off_5;
			अन्यथा अगर (state->srate <= 15000000)
				aclc = car_loop_qpsk_low[i].crl_pilots_off_10;
			अन्यथा अगर (state->srate <= 25000000)
				aclc = car_loop_qpsk_low[i].crl_pilots_off_20;
			अन्यथा
				aclc = car_loop_qpsk_low[i].crl_pilots_off_30;
		पूर्ण

	पूर्ण अन्यथा अगर (modcod <= STV090x_8PSK_910) अणु
		अगर (pilots) अणु
			अगर (state->srate <= 3000000)
				aclc = car_loop[i].crl_pilots_on_2;
			अन्यथा अगर (state->srate <= 7000000)
				aclc = car_loop[i].crl_pilots_on_5;
			अन्यथा अगर (state->srate <= 15000000)
				aclc = car_loop[i].crl_pilots_on_10;
			अन्यथा अगर (state->srate <= 25000000)
				aclc = car_loop[i].crl_pilots_on_20;
			अन्यथा
				aclc = car_loop[i].crl_pilots_on_30;
		पूर्ण अन्यथा अणु
			अगर (state->srate <= 3000000)
				aclc = car_loop[i].crl_pilots_off_2;
			अन्यथा अगर (state->srate <= 7000000)
				aclc = car_loop[i].crl_pilots_off_5;
			अन्यथा अगर (state->srate <= 15000000)
				aclc = car_loop[i].crl_pilots_off_10;
			अन्यथा अगर (state->srate <= 25000000)
				aclc = car_loop[i].crl_pilots_off_20;
			अन्यथा
				aclc = car_loop[i].crl_pilots_off_30;
		पूर्ण
	पूर्ण अन्यथा अणु /* 16APSK and 32APSK */
		/*
		 * This should never happen in practice, except अगर
		 * something is really wrong at the car_loop table.
		 */
		अगर (i >= 11)
			i = 10;
		अगर (state->srate <= 3000000)
			aclc = car_loop_apsk_low[i].crl_pilots_on_2;
		अन्यथा अगर (state->srate <= 7000000)
			aclc = car_loop_apsk_low[i].crl_pilots_on_5;
		अन्यथा अगर (state->srate <= 15000000)
			aclc = car_loop_apsk_low[i].crl_pilots_on_10;
		अन्यथा अगर (state->srate <= 25000000)
			aclc = car_loop_apsk_low[i].crl_pilots_on_20;
		अन्यथा
			aclc = car_loop_apsk_low[i].crl_pilots_on_30;
	पूर्ण

	वापस aclc;
पूर्ण

अटल u8 stv090x_optimize_carloop_लघु(काष्ठा stv090x_state *state)
अणु
	काष्ठा stv090x_लघु_frame_crloop *लघु_crl = शून्य;
	s32 index = 0;
	u8 aclc = 0x0b;

	चयन (state->modulation) अणु
	हाल STV090x_QPSK:
	शेष:
		index = 0;
		अवरोध;
	हाल STV090x_8PSK:
		index = 1;
		अवरोध;
	हाल STV090x_16APSK:
		index = 2;
		अवरोध;
	हाल STV090x_32APSK:
		index = 3;
		अवरोध;
	पूर्ण

	अगर (state->पूर्णांकernal->dev_ver >= 0x30) अणु
		/* Cut 3.0 and up */
		लघु_crl = stv090x_s2_लघु_crl_cut30;
	पूर्ण अन्यथा अणु
		/* Cut 2.0 and up: we करोn't support cuts older than 2.0 */
		लघु_crl = stv090x_s2_लघु_crl_cut20;
	पूर्ण

	अगर (state->srate <= 3000000)
		aclc = लघु_crl[index].crl_2;
	अन्यथा अगर (state->srate <= 7000000)
		aclc = लघु_crl[index].crl_5;
	अन्यथा अगर (state->srate <= 15000000)
		aclc = लघु_crl[index].crl_10;
	अन्यथा अगर (state->srate <= 25000000)
		aclc = लघु_crl[index].crl_20;
	अन्यथा
		aclc = लघु_crl[index].crl_30;

	वापस aclc;
पूर्ण

अटल पूर्णांक stv090x_optimize_track(काष्ठा stv090x_state *state)
अणु
	काष्ठा dvb_frontend *fe = &state->frontend;

	क्रमागत stv090x_modcod modcod;

	s32 srate, pilots, aclc, f_1, f_0, i = 0, blind_tune = 0;
	u32 reg;

	srate  = stv090x_get_srate(state, state->पूर्णांकernal->mclk);
	srate += stv090x_get_पंचांगgoffst(state, srate);

	चयन (state->delsys) अणु
	हाल STV090x_DVBS1:
	हाल STV090x_DSS:
		अगर (state->search_mode == STV090x_SEARCH_AUTO) अणु
			reg = STV090x_READ_DEMOD(state, DMDCFGMD);
			STV090x_SETFIELD_Px(reg, DVBS1_ENABLE_FIELD, 1);
			STV090x_SETFIELD_Px(reg, DVBS2_ENABLE_FIELD, 0);
			अगर (STV090x_WRITE_DEMOD(state, DMDCFGMD, reg) < 0)
				जाओ err;
		पूर्ण
		reg = STV090x_READ_DEMOD(state, DEMOD);
		STV090x_SETFIELD_Px(reg, ROLLOFF_CONTROL_FIELD, state->rolloff);
		STV090x_SETFIELD_Px(reg, MANUAL_SXROLLOFF_FIELD, 0x01);
		अगर (STV090x_WRITE_DEMOD(state, DEMOD, reg) < 0)
			जाओ err;

		अगर (state->पूर्णांकernal->dev_ver >= 0x30) अणु
			अगर (stv090x_get_viterbi(state) < 0)
				जाओ err;

			अगर (state->fec == STV090x_PR12) अणु
				अगर (STV090x_WRITE_DEMOD(state, GAUSSR0, 0x98) < 0)
					जाओ err;
				अगर (STV090x_WRITE_DEMOD(state, CCIR0, 0x18) < 0)
					जाओ err;
			पूर्ण अन्यथा अणु
				अगर (STV090x_WRITE_DEMOD(state, GAUSSR0, 0x18) < 0)
					जाओ err;
				अगर (STV090x_WRITE_DEMOD(state, CCIR0, 0x18) < 0)
					जाओ err;
			पूर्ण
		पूर्ण

		अगर (STV090x_WRITE_DEMOD(state, ERRCTRL1, 0x75) < 0)
			जाओ err;
		अवरोध;

	हाल STV090x_DVBS2:
		reg = STV090x_READ_DEMOD(state, DMDCFGMD);
		STV090x_SETFIELD_Px(reg, DVBS1_ENABLE_FIELD, 0);
		STV090x_SETFIELD_Px(reg, DVBS2_ENABLE_FIELD, 1);
		अगर (STV090x_WRITE_DEMOD(state, DMDCFGMD, reg) < 0)
			जाओ err;
		अगर (state->पूर्णांकernal->dev_ver >= 0x30) अणु
			अगर (STV090x_WRITE_DEMOD(state, ACLC, 0) < 0)
				जाओ err;
			अगर (STV090x_WRITE_DEMOD(state, BCLC, 0) < 0)
				जाओ err;
		पूर्ण
		अगर (state->frame_len == STV090x_LONG_FRAME) अणु
			reg = STV090x_READ_DEMOD(state, DMDMODCOD);
			modcod = STV090x_GETFIELD_Px(reg, DEMOD_MODCOD_FIELD);
			pilots = STV090x_GETFIELD_Px(reg, DEMOD_TYPE_FIELD) & 0x01;
			aclc = stv090x_optimize_carloop(state, modcod, pilots);
			अगर (modcod <= STV090x_QPSK_910) अणु
				STV090x_WRITE_DEMOD(state, ACLC2S2Q, aclc);
			पूर्ण अन्यथा अगर (modcod <= STV090x_8PSK_910) अणु
				अगर (STV090x_WRITE_DEMOD(state, ACLC2S2Q, 0x2a) < 0)
					जाओ err;
				अगर (STV090x_WRITE_DEMOD(state, ACLC2S28, aclc) < 0)
					जाओ err;
			पूर्ण
			अगर ((state->demod_mode == STV090x_SINGLE) && (modcod > STV090x_8PSK_910)) अणु
				अगर (modcod <= STV090x_16APSK_910) अणु
					अगर (STV090x_WRITE_DEMOD(state, ACLC2S2Q, 0x2a) < 0)
						जाओ err;
					अगर (STV090x_WRITE_DEMOD(state, ACLC2S216A, aclc) < 0)
						जाओ err;
				पूर्ण अन्यथा अणु
					अगर (STV090x_WRITE_DEMOD(state, ACLC2S2Q, 0x2a) < 0)
						जाओ err;
					अगर (STV090x_WRITE_DEMOD(state, ACLC2S232A, aclc) < 0)
						जाओ err;
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा अणु
			/*Carrier loop setting क्रम लघु frame*/
			aclc = stv090x_optimize_carloop_लघु(state);
			अगर (state->modulation == STV090x_QPSK) अणु
				अगर (STV090x_WRITE_DEMOD(state, ACLC2S2Q, aclc) < 0)
					जाओ err;
			पूर्ण अन्यथा अगर (state->modulation == STV090x_8PSK) अणु
				अगर (STV090x_WRITE_DEMOD(state, ACLC2S2Q, 0x2a) < 0)
					जाओ err;
				अगर (STV090x_WRITE_DEMOD(state, ACLC2S28, aclc) < 0)
					जाओ err;
			पूर्ण अन्यथा अगर (state->modulation == STV090x_16APSK) अणु
				अगर (STV090x_WRITE_DEMOD(state, ACLC2S2Q, 0x2a) < 0)
					जाओ err;
				अगर (STV090x_WRITE_DEMOD(state, ACLC2S216A, aclc) < 0)
					जाओ err;
			पूर्ण अन्यथा अगर (state->modulation == STV090x_32APSK)  अणु
				अगर (STV090x_WRITE_DEMOD(state, ACLC2S2Q, 0x2a) < 0)
					जाओ err;
				अगर (STV090x_WRITE_DEMOD(state, ACLC2S232A, aclc) < 0)
					जाओ err;
			पूर्ण
		पूर्ण

		STV090x_WRITE_DEMOD(state, ERRCTRL1, 0x67); /* PER */
		अवरोध;

	हाल STV090x_ERROR:
	शेष:
		reg = STV090x_READ_DEMOD(state, DMDCFGMD);
		STV090x_SETFIELD_Px(reg, DVBS1_ENABLE_FIELD, 1);
		STV090x_SETFIELD_Px(reg, DVBS2_ENABLE_FIELD, 1);
		अगर (STV090x_WRITE_DEMOD(state, DMDCFGMD, reg) < 0)
			जाओ err;
		अवरोध;
	पूर्ण

	f_1 = STV090x_READ_DEMOD(state, CFR2);
	f_0 = STV090x_READ_DEMOD(state, CFR1);
	reg = STV090x_READ_DEMOD(state, TMGOBS);

	अगर (state->algo == STV090x_BLIND_SEARCH) अणु
		STV090x_WRITE_DEMOD(state, SFRSTEP, 0x00);
		reg = STV090x_READ_DEMOD(state, DMDCFGMD);
		STV090x_SETFIELD_Px(reg, SCAN_ENABLE_FIELD, 0x00);
		STV090x_SETFIELD_Px(reg, CFR_AUTOSCAN_FIELD, 0x00);
		अगर (STV090x_WRITE_DEMOD(state, DMDCFGMD, reg) < 0)
			जाओ err;
		अगर (STV090x_WRITE_DEMOD(state, TMGCFG2, 0xc1) < 0)
			जाओ err;

		अगर (stv090x_set_srate(state, srate) < 0)
			जाओ err;
		blind_tune = 1;

		अगर (stv090x_dvbs_track_crl(state) < 0)
			जाओ err;
	पूर्ण

	अगर (state->पूर्णांकernal->dev_ver >= 0x20) अणु
		अगर ((state->search_mode == STV090x_SEARCH_DVBS1)	||
		    (state->search_mode == STV090x_SEARCH_DSS)		||
		    (state->search_mode == STV090x_SEARCH_AUTO)) अणु

			अगर (STV090x_WRITE_DEMOD(state, VAVSRVIT, 0x0a) < 0)
				जाओ err;
			अगर (STV090x_WRITE_DEMOD(state, VITSCALE, 0x00) < 0)
				जाओ err;
		पूर्ण
	पूर्ण

	अगर (STV090x_WRITE_DEMOD(state, AGC2REF, 0x38) < 0)
		जाओ err;

	/* AUTO tracking MODE */
	अगर (STV090x_WRITE_DEMOD(state, SFRUP1, 0x80) < 0)
		जाओ err;
	/* AUTO tracking MODE */
	अगर (STV090x_WRITE_DEMOD(state, SFRLOW1, 0x80) < 0)
		जाओ err;

	अगर ((state->पूर्णांकernal->dev_ver >= 0x20) || (blind_tune == 1) ||
	    (state->srate < 10000000)) अणु
		/* update initial carrier freq with the found freq offset */
		अगर (STV090x_WRITE_DEMOD(state, CFRINIT1, f_1) < 0)
			जाओ err;
		अगर (STV090x_WRITE_DEMOD(state, CFRINIT0, f_0) < 0)
			जाओ err;
		state->tuner_bw = stv090x_car_width(srate, state->rolloff) + 10000000;

		अगर ((state->पूर्णांकernal->dev_ver >= 0x20) || (blind_tune == 1)) अणु

			अगर (state->algo != STV090x_WARM_SEARCH) अणु

				अगर (stv090x_i2c_gate_ctrl(state, 1) < 0)
					जाओ err;

				अगर (state->config->tuner_set_bandwidth) अणु
					अगर (state->config->tuner_set_bandwidth(fe, state->tuner_bw) < 0)
						जाओ err_gateoff;
				पूर्ण

				अगर (stv090x_i2c_gate_ctrl(state, 0) < 0)
					जाओ err;

			पूर्ण
		पूर्ण
		अगर ((state->algo == STV090x_BLIND_SEARCH) || (state->srate < 10000000))
			msleep(50); /* blind search: रुको 50ms क्रम SR stabilization */
		अन्यथा
			msleep(5);

		stv090x_get_lock_पंचांगg(state);

		अगर (!(stv090x_get_dmdlock(state, (state->DemodTimeout / 2)))) अणु
			अगर (STV090x_WRITE_DEMOD(state, DMDISTATE, 0x1f) < 0)
				जाओ err;
			अगर (STV090x_WRITE_DEMOD(state, CFRINIT1, f_1) < 0)
				जाओ err;
			अगर (STV090x_WRITE_DEMOD(state, CFRINIT0, f_0) < 0)
				जाओ err;
			अगर (STV090x_WRITE_DEMOD(state, DMDISTATE, 0x18) < 0)
				जाओ err;

			i = 0;

			जबतक ((!(stv090x_get_dmdlock(state, (state->DemodTimeout / 2)))) && (i <= 2)) अणु

				अगर (STV090x_WRITE_DEMOD(state, DMDISTATE, 0x1f) < 0)
					जाओ err;
				अगर (STV090x_WRITE_DEMOD(state, CFRINIT1, f_1) < 0)
					जाओ err;
				अगर (STV090x_WRITE_DEMOD(state, CFRINIT0, f_0) < 0)
					जाओ err;
				अगर (STV090x_WRITE_DEMOD(state, DMDISTATE, 0x18) < 0)
					जाओ err;
				i++;
			पूर्ण
		पूर्ण

	पूर्ण

	अगर (state->पूर्णांकernal->dev_ver >= 0x20) अणु
		अगर (STV090x_WRITE_DEMOD(state, CARFREQ, 0x49) < 0)
			जाओ err;
	पूर्ण

	अगर ((state->delsys == STV090x_DVBS1) || (state->delsys == STV090x_DSS))
		stv090x_set_vit_thtracq(state);

	वापस 0;

err_gateoff:
	stv090x_i2c_gate_ctrl(state, 0);
err:
	dprपूर्णांकk(FE_ERROR, 1, "I/O error");
	वापस -1;
पूर्ण

अटल पूर्णांक stv090x_get_feघड़ी(काष्ठा stv090x_state *state, s32 समयout)
अणु
	s32 समयr = 0, lock = 0, stat;
	u32 reg;

	जबतक ((समयr < समयout) && (!lock)) अणु
		reg = STV090x_READ_DEMOD(state, DMDSTATE);
		stat = STV090x_GETFIELD_Px(reg, HEADER_MODE_FIELD);

		चयन (stat) अणु
		हाल 0: /* searching */
		हाल 1: /* first PLH detected */
		शेष:
			lock = 0;
			अवरोध;

		हाल 2: /* DVB-S2 mode */
			reg = STV090x_READ_DEMOD(state, PDELSTATUS1);
			lock = STV090x_GETFIELD_Px(reg, PKTDELIN_LOCK_FIELD);
			अवरोध;

		हाल 3: /* DVB-S1/legacy mode */
			reg = STV090x_READ_DEMOD(state, VSTATUSVIT);
			lock = STV090x_GETFIELD_Px(reg, LOCKEDVIT_FIELD);
			अवरोध;
		पूर्ण
		अगर (!lock) अणु
			msleep(10);
			समयr += 10;
		पूर्ण
	पूर्ण
	वापस lock;
पूर्ण

अटल पूर्णांक stv090x_get_lock(काष्ठा stv090x_state *state, s32 समयout_dmd, s32 समयout_fec)
अणु
	u32 reg;
	s32 समयr = 0;
	पूर्णांक lock;

	lock = stv090x_get_dmdlock(state, समयout_dmd);
	अगर (lock)
		lock = stv090x_get_feघड़ी(state, समयout_fec);

	अगर (lock) अणु
		lock = 0;

		जबतक ((समयr < समयout_fec) && (!lock)) अणु
			reg = STV090x_READ_DEMOD(state, TSSTATUS);
			lock = STV090x_GETFIELD_Px(reg, TSFIFO_LINEOK_FIELD);
			msleep(1);
			समयr++;
		पूर्ण
	पूर्ण

	वापस lock;
पूर्ण

अटल पूर्णांक stv090x_set_s2rolloff(काष्ठा stv090x_state *state)
अणु
	u32 reg;

	अगर (state->पूर्णांकernal->dev_ver <= 0x20) अणु
		/* rolloff to स्वतः mode अगर DVBS2 */
		reg = STV090x_READ_DEMOD(state, DEMOD);
		STV090x_SETFIELD_Px(reg, MANUAL_SXROLLOFF_FIELD, 0x00);
		अगर (STV090x_WRITE_DEMOD(state, DEMOD, reg) < 0)
			जाओ err;
	पूर्ण अन्यथा अणु
		/* DVB-S2 rolloff to स्वतः mode अगर DVBS2 */
		reg = STV090x_READ_DEMOD(state, DEMOD);
		STV090x_SETFIELD_Px(reg, MANUAL_S2ROLLOFF_FIELD, 0x00);
		अगर (STV090x_WRITE_DEMOD(state, DEMOD, reg) < 0)
			जाओ err;
	पूर्ण
	वापस 0;
err:
	dprपूर्णांकk(FE_ERROR, 1, "I/O error");
	वापस -1;
पूर्ण


अटल क्रमागत stv090x_संकेत_state stv090x_algo(काष्ठा stv090x_state *state)
अणु
	काष्ठा dvb_frontend *fe = &state->frontend;
	क्रमागत stv090x_संकेत_state संकेत_state = STV090x_NOCARRIER;
	u32 reg;
	s32 agc1_घातer, घातer_iq = 0, i;
	पूर्णांक lock = 0, low_sr = 0;

	reg = STV090x_READ_DEMOD(state, TSCFGH);
	STV090x_SETFIELD_Px(reg, RST_HWARE_FIELD, 1); /* Stop path 1 stream merger */
	अगर (STV090x_WRITE_DEMOD(state, TSCFGH, reg) < 0)
		जाओ err;

	अगर (STV090x_WRITE_DEMOD(state, DMDISTATE, 0x5c) < 0) /* Demod stop */
		जाओ err;

	अगर (state->पूर्णांकernal->dev_ver >= 0x20) अणु
		अगर (state->srate > 5000000) अणु
			अगर (STV090x_WRITE_DEMOD(state, CORRELABS, 0x9e) < 0)
				जाओ err;
		पूर्ण अन्यथा अणु
			अगर (STV090x_WRITE_DEMOD(state, CORRELABS, 0x82) < 0)
				जाओ err;
		पूर्ण
	पूर्ण

	stv090x_get_lock_पंचांगg(state);

	अगर (state->algo == STV090x_BLIND_SEARCH) अणु
		state->tuner_bw = 2 * 36000000; /* wide bw क्रम unknown srate */
		अगर (STV090x_WRITE_DEMOD(state, TMGCFG2, 0xc0) < 0) /* wider srate scan */
			जाओ err;
		अगर (STV090x_WRITE_DEMOD(state, CORRELMANT, 0x70) < 0)
			जाओ err;
		अगर (stv090x_set_srate(state, 1000000) < 0) /* initial srate = 1Msps */
			जाओ err;
	पूर्ण अन्यथा अणु
		/* known srate */
		अगर (STV090x_WRITE_DEMOD(state, DMDTOM, 0x20) < 0)
			जाओ err;
		अगर (STV090x_WRITE_DEMOD(state, TMGCFG, 0xd2) < 0)
			जाओ err;

		अगर (state->srate < 2000000) अणु
			/* SR < 2MSPS */
			अगर (STV090x_WRITE_DEMOD(state, CORRELMANT, 0x63) < 0)
				जाओ err;
		पूर्ण अन्यथा अणु
			/* SR >= 2Msps */
			अगर (STV090x_WRITE_DEMOD(state, CORRELMANT, 0x70) < 0)
				जाओ err;
		पूर्ण

		अगर (STV090x_WRITE_DEMOD(state, AGC2REF, 0x38) < 0)
			जाओ err;

		अगर (state->पूर्णांकernal->dev_ver >= 0x20) अणु
			अगर (STV090x_WRITE_DEMOD(state, KREFTMG, 0x5a) < 0)
				जाओ err;
			अगर (state->algo == STV090x_COLD_SEARCH)
				state->tuner_bw = (15 * (stv090x_car_width(state->srate, state->rolloff) + 10000000)) / 10;
			अन्यथा अगर (state->algo == STV090x_WARM_SEARCH)
				state->tuner_bw = stv090x_car_width(state->srate, state->rolloff) + 10000000;
		पूर्ण

		/* अगर cold start or warm  (Symbolrate is known)
		 * use a Narrow symbol rate scan range
		 */
		अगर (STV090x_WRITE_DEMOD(state, TMGCFG2, 0xc1) < 0) /* narrow srate scan */
			जाओ err;

		अगर (stv090x_set_srate(state, state->srate) < 0)
			जाओ err;

		अगर (stv090x_set_max_srate(state, state->पूर्णांकernal->mclk,
					  state->srate) < 0)
			जाओ err;
		अगर (stv090x_set_min_srate(state, state->पूर्णांकernal->mclk,
					  state->srate) < 0)
			जाओ err;

		अगर (state->srate >= 10000000)
			low_sr = 0;
		अन्यथा
			low_sr = 1;
	पूर्ण

	/* Setup tuner */
	अगर (stv090x_i2c_gate_ctrl(state, 1) < 0)
		जाओ err;

	अगर (state->config->tuner_set_bbgain) अणु
		reg = state->config->tuner_bbgain;
		अगर (reg == 0)
			reg = 10; /* शेष: 10dB */
		अगर (state->config->tuner_set_bbgain(fe, reg) < 0)
			जाओ err_gateoff;
	पूर्ण

	अगर (state->config->tuner_set_frequency) अणु
		अगर (state->config->tuner_set_frequency(fe, state->frequency) < 0)
			जाओ err_gateoff;
	पूर्ण

	अगर (state->config->tuner_set_bandwidth) अणु
		अगर (state->config->tuner_set_bandwidth(fe, state->tuner_bw) < 0)
			जाओ err_gateoff;
	पूर्ण

	अगर (stv090x_i2c_gate_ctrl(state, 0) < 0)
		जाओ err;

	msleep(50);

	अगर (state->config->tuner_get_status) अणु
		अगर (stv090x_i2c_gate_ctrl(state, 1) < 0)
			जाओ err;
		अगर (state->config->tuner_get_status(fe, &reg) < 0)
			जाओ err_gateoff;
		अगर (stv090x_i2c_gate_ctrl(state, 0) < 0)
			जाओ err;

		अगर (reg)
			dprपूर्णांकk(FE_DEBUG, 1, "Tuner phase locked");
		अन्यथा अणु
			dprपूर्णांकk(FE_DEBUG, 1, "Tuner unlocked");
			वापस STV090x_NOCARRIER;
		पूर्ण
	पूर्ण

	msleep(10);
	agc1_घातer = MAKEWORD16(STV090x_READ_DEMOD(state, AGCIQIN1),
				STV090x_READ_DEMOD(state, AGCIQIN0));

	अगर (agc1_घातer == 0) अणु
		/* If AGC1 पूर्णांकegrator value is 0
		 * then पढ़ो POWERI, POWERQ
		 */
		क्रम (i = 0; i < 5; i++) अणु
			घातer_iq += (STV090x_READ_DEMOD(state, POWERI) +
				     STV090x_READ_DEMOD(state, POWERQ)) >> 1;
		पूर्ण
		घातer_iq /= 5;
	पूर्ण

	अगर ((agc1_घातer == 0) && (घातer_iq < STV090x_IQPOWER_THRESHOLD)) अणु
		dprपूर्णांकk(FE_ERROR, 1, "No Signal: POWER_IQ=0x%02x", घातer_iq);
		lock = 0;
		संकेत_state = STV090x_NOAGC1;
	पूर्ण अन्यथा अणु
		reg = STV090x_READ_DEMOD(state, DEMOD);
		STV090x_SETFIELD_Px(reg, SPECINV_CONTROL_FIELD, state->inversion);

		अगर (state->पूर्णांकernal->dev_ver <= 0x20) अणु
			/* rolloff to स्वतः mode अगर DVBS2 */
			STV090x_SETFIELD_Px(reg, MANUAL_SXROLLOFF_FIELD, 1);
		पूर्ण अन्यथा अणु
			/* DVB-S2 rolloff to स्वतः mode अगर DVBS2 */
			STV090x_SETFIELD_Px(reg, MANUAL_S2ROLLOFF_FIELD, 1);
		पूर्ण
		अगर (STV090x_WRITE_DEMOD(state, DEMOD, reg) < 0)
			जाओ err;

		अगर (stv090x_delivery_search(state) < 0)
			जाओ err;

		अगर (state->algo != STV090x_BLIND_SEARCH) अणु
			अगर (stv090x_start_search(state) < 0)
				जाओ err;
		पूर्ण
	पूर्ण

	अगर (संकेत_state == STV090x_NOAGC1)
		वापस संकेत_state;

	अगर (state->algo == STV090x_BLIND_SEARCH)
		lock = stv090x_blind_search(state);

	अन्यथा अगर (state->algo == STV090x_COLD_SEARCH)
		lock = stv090x_get_coldlock(state, state->DemodTimeout);

	अन्यथा अगर (state->algo == STV090x_WARM_SEARCH)
		lock = stv090x_get_dmdlock(state, state->DemodTimeout);

	अगर ((!lock) && (state->algo == STV090x_COLD_SEARCH)) अणु
		अगर (!low_sr) अणु
			अगर (stv090x_chk_पंचांगg(state))
				lock = stv090x_sw_algo(state);
		पूर्ण
	पूर्ण

	अगर (lock)
		संकेत_state = stv090x_get_sig_params(state);

	अगर ((lock) && (संकेत_state == STV090x_RANGEOK)) अणु /* संकेत within Range */
		stv090x_optimize_track(state);

		अगर (state->पूर्णांकernal->dev_ver >= 0x20) अणु
			/* >= Cut 2.0 :release TS reset after
			 * demod lock and optimized Tracking
			 */
			reg = STV090x_READ_DEMOD(state, TSCFGH);
			STV090x_SETFIELD_Px(reg, RST_HWARE_FIELD, 0); /* release merger reset */
			अगर (STV090x_WRITE_DEMOD(state, TSCFGH, reg) < 0)
				जाओ err;

			msleep(3);

			STV090x_SETFIELD_Px(reg, RST_HWARE_FIELD, 1); /* merger reset */
			अगर (STV090x_WRITE_DEMOD(state, TSCFGH, reg) < 0)
				जाओ err;

			STV090x_SETFIELD_Px(reg, RST_HWARE_FIELD, 0); /* release merger reset */
			अगर (STV090x_WRITE_DEMOD(state, TSCFGH, reg) < 0)
				जाओ err;
		पूर्ण

		lock = stv090x_get_lock(state, state->FecTimeout,
				state->FecTimeout);
		अगर (lock) अणु
			अगर (state->delsys == STV090x_DVBS2) अणु
				stv090x_set_s2rolloff(state);

				reg = STV090x_READ_DEMOD(state, PDELCTRL2);
				STV090x_SETFIELD_Px(reg, RESET_UPKO_COUNT, 1);
				अगर (STV090x_WRITE_DEMOD(state, PDELCTRL2, reg) < 0)
					जाओ err;
				/* Reset DVBS2 packet delinator error counter */
				reg = STV090x_READ_DEMOD(state, PDELCTRL2);
				STV090x_SETFIELD_Px(reg, RESET_UPKO_COUNT, 0);
				अगर (STV090x_WRITE_DEMOD(state, PDELCTRL2, reg) < 0)
					जाओ err;

				अगर (STV090x_WRITE_DEMOD(state, ERRCTRL1, 0x67) < 0) /* PER */
					जाओ err;
			पूर्ण अन्यथा अणु
				अगर (STV090x_WRITE_DEMOD(state, ERRCTRL1, 0x75) < 0)
					जाओ err;
			पूर्ण
			/* Reset the Total packet counter */
			अगर (STV090x_WRITE_DEMOD(state, FBERCPT4, 0x00) < 0)
				जाओ err;
			/* Reset the packet Error counter2 */
			अगर (STV090x_WRITE_DEMOD(state, ERRCTRL2, 0xc1) < 0)
				जाओ err;
		पूर्ण अन्यथा अणु
			संकेत_state = STV090x_NODATA;
			stv090x_chk_संकेत(state);
		पूर्ण
	पूर्ण
	वापस संकेत_state;

err_gateoff:
	stv090x_i2c_gate_ctrl(state, 0);
err:
	dprपूर्णांकk(FE_ERROR, 1, "I/O error");
	वापस -1;
पूर्ण

अटल पूर्णांक stv090x_set_pls(काष्ठा stv090x_state *state, u32 pls_code)
अणु
	dprपूर्णांकk(FE_DEBUG, 1, "Set Gold PLS code %d", pls_code);
	अगर (STV090x_WRITE_DEMOD(state, PLROOT0, pls_code & 0xff) < 0)
		जाओ err;
	अगर (STV090x_WRITE_DEMOD(state, PLROOT1, (pls_code >> 8) & 0xff) < 0)
		जाओ err;
	अगर (STV090x_WRITE_DEMOD(state, PLROOT2, 0x04 | (pls_code >> 16)) < 0)
		जाओ err;
	वापस 0;
err:
	dprपूर्णांकk(FE_ERROR, 1, "I/O error");
	वापस -1;
पूर्ण

अटल पूर्णांक stv090x_set_mis(काष्ठा stv090x_state *state, पूर्णांक mis)
अणु
	u32 reg;

	अगर (mis < 0 || mis > 255) अणु
		dprपूर्णांकk(FE_DEBUG, 1, "Disable MIS filtering");
		reg = STV090x_READ_DEMOD(state, PDELCTRL1);
		STV090x_SETFIELD_Px(reg, FILTER_EN_FIELD, 0x00);
		अगर (STV090x_WRITE_DEMOD(state, PDELCTRL1, reg) < 0)
			जाओ err;
	पूर्ण अन्यथा अणु
		dprपूर्णांकk(FE_DEBUG, 1, "Enable MIS filtering - %d", mis);
		reg = STV090x_READ_DEMOD(state, PDELCTRL1);
		STV090x_SETFIELD_Px(reg, FILTER_EN_FIELD, 0x01);
		अगर (STV090x_WRITE_DEMOD(state, PDELCTRL1, reg) < 0)
			जाओ err;
		अगर (STV090x_WRITE_DEMOD(state, ISIENTRY, mis) < 0)
			जाओ err;
		अगर (STV090x_WRITE_DEMOD(state, ISIBITENA, 0xff) < 0)
			जाओ err;
	पूर्ण
	वापस 0;
err:
	dprपूर्णांकk(FE_ERROR, 1, "I/O error");
	वापस -1;
पूर्ण

अटल क्रमागत dvbfe_search stv090x_search(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा stv090x_state *state = fe->demodulator_priv;
	काष्ठा dtv_frontend_properties *props = &fe->dtv_property_cache;

	अगर (props->frequency == 0)
		वापस DVBFE_ALGO_SEARCH_INVALID;

	चयन (props->delivery_प्रणाली) अणु
	हाल SYS_DSS:
		state->delsys = STV090x_DSS;
		अवरोध;
	हाल SYS_DVBS:
		state->delsys = STV090x_DVBS1;
		अवरोध;
	हाल SYS_DVBS2:
		state->delsys = STV090x_DVBS2;
		अवरोध;
	शेष:
		वापस DVBFE_ALGO_SEARCH_INVALID;
	पूर्ण

	state->frequency = props->frequency;
	state->srate = props->symbol_rate;
	state->search_mode = STV090x_SEARCH_AUTO;
	state->algo = STV090x_COLD_SEARCH;
	state->fec = STV090x_PRERR;
	अगर (state->srate > 10000000) अणु
		dprपूर्णांकk(FE_DEBUG, 1, "Search range: 10 MHz");
		state->search_range = 10000000;
	पूर्ण अन्यथा अणु
		dprपूर्णांकk(FE_DEBUG, 1, "Search range: 5 MHz");
		state->search_range = 5000000;
	पूर्ण

	stv090x_set_pls(state, props->scrambling_sequence_index);
	stv090x_set_mis(state, props->stream_id);

	अगर (stv090x_algo(state) == STV090x_RANGEOK) अणु
		dprपूर्णांकk(FE_DEBUG, 1, "Search success!");
		वापस DVBFE_ALGO_SEARCH_SUCCESS;
	पूर्ण अन्यथा अणु
		dprपूर्णांकk(FE_DEBUG, 1, "Search failed!");
		वापस DVBFE_ALGO_SEARCH_FAILED;
	पूर्ण

	वापस DVBFE_ALGO_SEARCH_ERROR;
पूर्ण

अटल पूर्णांक stv090x_पढ़ो_status(काष्ठा dvb_frontend *fe, क्रमागत fe_status *status)
अणु
	काष्ठा stv090x_state *state = fe->demodulator_priv;
	u32 reg, dstatus;
	u8 search_state;

	*status = 0;

	dstatus = STV090x_READ_DEMOD(state, DSTATUS);
	अगर (STV090x_GETFIELD_Px(dstatus, CAR_LOCK_FIELD))
		*status |= FE_HAS_SIGNAL | FE_HAS_CARRIER;

	reg = STV090x_READ_DEMOD(state, DMDSTATE);
	search_state = STV090x_GETFIELD_Px(reg, HEADER_MODE_FIELD);

	चयन (search_state) अणु
	हाल 0: /* searching */
	हाल 1: /* first PLH detected */
	शेष:
		dprपूर्णांकk(FE_DEBUG, 1, "Status: Unlocked (Searching ..)");
		अवरोध;

	हाल 2: /* DVB-S2 mode */
		dprपूर्णांकk(FE_DEBUG, 1, "Delivery system: DVB-S2");
		अगर (STV090x_GETFIELD_Px(dstatus, LOCK_DEFINITIF_FIELD)) अणु
			reg = STV090x_READ_DEMOD(state, PDELSTATUS1);
			अगर (STV090x_GETFIELD_Px(reg, PKTDELIN_LOCK_FIELD)) अणु
				*status |= FE_HAS_VITERBI;
				reg = STV090x_READ_DEMOD(state, TSSTATUS);
				अगर (STV090x_GETFIELD_Px(reg, TSFIFO_LINEOK_FIELD))
					*status |= FE_HAS_SYNC | FE_HAS_LOCK;
			पूर्ण
		पूर्ण
		अवरोध;

	हाल 3: /* DVB-S1/legacy mode */
		dprपूर्णांकk(FE_DEBUG, 1, "Delivery system: DVB-S");
		अगर (STV090x_GETFIELD_Px(dstatus, LOCK_DEFINITIF_FIELD)) अणु
			reg = STV090x_READ_DEMOD(state, VSTATUSVIT);
			अगर (STV090x_GETFIELD_Px(reg, LOCKEDVIT_FIELD)) अणु
				*status |= FE_HAS_VITERBI;
				reg = STV090x_READ_DEMOD(state, TSSTATUS);
				अगर (STV090x_GETFIELD_Px(reg, TSFIFO_LINEOK_FIELD))
					*status |= FE_HAS_SYNC | FE_HAS_LOCK;
			पूर्ण
		पूर्ण
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक stv090x_पढ़ो_per(काष्ठा dvb_frontend *fe, u32 *per)
अणु
	काष्ठा stv090x_state *state = fe->demodulator_priv;

	s32 count_4, count_3, count_2, count_1, count_0, count;
	u32 reg, h, m, l;
	क्रमागत fe_status status;

	stv090x_पढ़ो_status(fe, &status);
	अगर (!(status & FE_HAS_LOCK)) अणु
		*per = 1 << 23; /* Max PER */
	पूर्ण अन्यथा अणु
		/* Counter 2 */
		reg = STV090x_READ_DEMOD(state, ERRCNT22);
		h = STV090x_GETFIELD_Px(reg, ERR_CNT2_FIELD);

		reg = STV090x_READ_DEMOD(state, ERRCNT21);
		m = STV090x_GETFIELD_Px(reg, ERR_CNT21_FIELD);

		reg = STV090x_READ_DEMOD(state, ERRCNT20);
		l = STV090x_GETFIELD_Px(reg, ERR_CNT20_FIELD);

		*per = ((h << 16) | (m << 8) | l);

		count_4 = STV090x_READ_DEMOD(state, FBERCPT4);
		count_3 = STV090x_READ_DEMOD(state, FBERCPT3);
		count_2 = STV090x_READ_DEMOD(state, FBERCPT2);
		count_1 = STV090x_READ_DEMOD(state, FBERCPT1);
		count_0 = STV090x_READ_DEMOD(state, FBERCPT0);

		अगर ((!count_4) && (!count_3)) अणु
			count  = (count_2 & 0xff) << 16;
			count |= (count_1 & 0xff) <<  8;
			count |=  count_0 & 0xff;
		पूर्ण अन्यथा अणु
			count = 1 << 24;
		पूर्ण
		अगर (count == 0)
			*per = 1;
	पूर्ण
	अगर (STV090x_WRITE_DEMOD(state, FBERCPT4, 0) < 0)
		जाओ err;
	अगर (STV090x_WRITE_DEMOD(state, ERRCTRL2, 0xc1) < 0)
		जाओ err;

	वापस 0;
err:
	dprपूर्णांकk(FE_ERROR, 1, "I/O error");
	वापस -1;
पूर्ण

अटल पूर्णांक stv090x_table_lookup(स्थिर काष्ठा stv090x_tab *tab, पूर्णांक max, पूर्णांक val)
अणु
	पूर्णांक res = 0;
	पूर्णांक min = 0, med;

	अगर ((val >= tab[min].पढ़ो && val < tab[max].पढ़ो) ||
	    (val >= tab[max].पढ़ो && val < tab[min].पढ़ो)) अणु
		जबतक ((max - min) > 1) अणु
			med = (max + min) / 2;
			अगर ((val >= tab[min].पढ़ो && val < tab[med].पढ़ो) ||
			    (val >= tab[med].पढ़ो && val < tab[min].पढ़ो))
				max = med;
			अन्यथा
				min = med;
		पूर्ण
		res = ((val - tab[min].पढ़ो) *
		       (tab[max].real - tab[min].real) /
		       (tab[max].पढ़ो - tab[min].पढ़ो)) +
			tab[min].real;
	पूर्ण अन्यथा अणु
		अगर (tab[min].पढ़ो < tab[max].पढ़ो) अणु
			अगर (val < tab[min].पढ़ो)
				res = tab[min].real;
			अन्यथा अगर (val >= tab[max].पढ़ो)
				res = tab[max].real;
		पूर्ण अन्यथा अणु
			अगर (val >= tab[min].पढ़ो)
				res = tab[min].real;
			अन्यथा अगर (val < tab[max].पढ़ो)
				res = tab[max].real;
		पूर्ण
	पूर्ण

	वापस res;
पूर्ण

अटल पूर्णांक stv090x_पढ़ो_संकेत_strength(काष्ठा dvb_frontend *fe, u16 *strength)
अणु
	काष्ठा stv090x_state *state = fe->demodulator_priv;
	u32 reg;
	s32 agc_0, agc_1, agc;
	s32 str;

	reg = STV090x_READ_DEMOD(state, AGCIQIN1);
	agc_1 = STV090x_GETFIELD_Px(reg, AGCIQ_VALUE_FIELD);
	reg = STV090x_READ_DEMOD(state, AGCIQIN0);
	agc_0 = STV090x_GETFIELD_Px(reg, AGCIQ_VALUE_FIELD);
	agc = MAKEWORD16(agc_1, agc_0);

	str = stv090x_table_lookup(stv090x_rf_tab,
		ARRAY_SIZE(stv090x_rf_tab) - 1, agc);
	अगर (agc > stv090x_rf_tab[0].पढ़ो)
		str = 0;
	अन्यथा अगर (agc < stv090x_rf_tab[ARRAY_SIZE(stv090x_rf_tab) - 1].पढ़ो)
		str = -100;
	*strength = (str + 100) * 0xFFFF / 100;

	वापस 0;
पूर्ण

अटल पूर्णांक stv090x_पढ़ो_cnr(काष्ठा dvb_frontend *fe, u16 *cnr)
अणु
	काष्ठा stv090x_state *state = fe->demodulator_priv;
	u32 reg_0, reg_1, reg, i;
	s32 val_0, val_1, val = 0;
	u8 lock_f;
	s32 भाग;
	u32 last;

	चयन (state->delsys) अणु
	हाल STV090x_DVBS2:
		reg = STV090x_READ_DEMOD(state, DSTATUS);
		lock_f = STV090x_GETFIELD_Px(reg, LOCK_DEFINITIF_FIELD);
		अगर (lock_f) अणु
			msleep(5);
			क्रम (i = 0; i < 16; i++) अणु
				reg_1 = STV090x_READ_DEMOD(state, NNOSPLHT1);
				val_1 = STV090x_GETFIELD_Px(reg_1, NOSPLHT_NORMED_FIELD);
				reg_0 = STV090x_READ_DEMOD(state, NNOSPLHT0);
				val_0 = STV090x_GETFIELD_Px(reg_0, NOSPLHT_NORMED_FIELD);
				val  += MAKEWORD16(val_1, val_0);
				msleep(1);
			पूर्ण
			val /= 16;
			last = ARRAY_SIZE(stv090x_s2cn_tab) - 1;
			भाग = stv090x_s2cn_tab[last].real -
			      stv090x_s2cn_tab[3].real;
			val = stv090x_table_lookup(stv090x_s2cn_tab, last, val);
			अगर (val < 0)
				val = 0;
			*cnr = val * 0xFFFF / भाग;
		पूर्ण
		अवरोध;

	हाल STV090x_DVBS1:
	हाल STV090x_DSS:
		reg = STV090x_READ_DEMOD(state, DSTATUS);
		lock_f = STV090x_GETFIELD_Px(reg, LOCK_DEFINITIF_FIELD);
		अगर (lock_f) अणु
			msleep(5);
			क्रम (i = 0; i < 16; i++) अणु
				reg_1 = STV090x_READ_DEMOD(state, NOSDATAT1);
				val_1 = STV090x_GETFIELD_Px(reg_1, NOSDATAT_UNNORMED_FIELD);
				reg_0 = STV090x_READ_DEMOD(state, NOSDATAT0);
				val_0 = STV090x_GETFIELD_Px(reg_0, NOSDATAT_UNNORMED_FIELD);
				val  += MAKEWORD16(val_1, val_0);
				msleep(1);
			पूर्ण
			val /= 16;
			last = ARRAY_SIZE(stv090x_s1cn_tab) - 1;
			भाग = stv090x_s1cn_tab[last].real -
			      stv090x_s1cn_tab[0].real;
			val = stv090x_table_lookup(stv090x_s1cn_tab, last, val);
			*cnr = val * 0xFFFF / भाग;
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक stv090x_set_tone(काष्ठा dvb_frontend *fe, क्रमागत fe_sec_tone_mode tone)
अणु
	काष्ठा stv090x_state *state = fe->demodulator_priv;
	u32 reg;

	reg = STV090x_READ_DEMOD(state, DISTXCTL);
	चयन (tone) अणु
	हाल SEC_TONE_ON:
		STV090x_SETFIELD_Px(reg, DISTX_MODE_FIELD, 0);
		STV090x_SETFIELD_Px(reg, DISEQC_RESET_FIELD, 1);
		अगर (STV090x_WRITE_DEMOD(state, DISTXCTL, reg) < 0)
			जाओ err;
		STV090x_SETFIELD_Px(reg, DISEQC_RESET_FIELD, 0);
		अगर (STV090x_WRITE_DEMOD(state, DISTXCTL, reg) < 0)
			जाओ err;
		अवरोध;

	हाल SEC_TONE_OFF:
		STV090x_SETFIELD_Px(reg, DISTX_MODE_FIELD, 0);
		STV090x_SETFIELD_Px(reg, DISEQC_RESET_FIELD, 1);
		अगर (STV090x_WRITE_DEMOD(state, DISTXCTL, reg) < 0)
			जाओ err;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
err:
	dprपूर्णांकk(FE_ERROR, 1, "I/O error");
	वापस -1;
पूर्ण


अटल क्रमागत dvbfe_algo stv090x_frontend_algo(काष्ठा dvb_frontend *fe)
अणु
	वापस DVBFE_ALGO_CUSTOM;
पूर्ण

अटल पूर्णांक stv090x_send_diseqc_msg(काष्ठा dvb_frontend *fe, काष्ठा dvb_diseqc_master_cmd *cmd)
अणु
	काष्ठा stv090x_state *state = fe->demodulator_priv;
	u32 reg, idle = 0, fअगरo_full = 1;
	पूर्णांक i;

	reg = STV090x_READ_DEMOD(state, DISTXCTL);

	STV090x_SETFIELD_Px(reg, DISTX_MODE_FIELD,
		(state->config->diseqc_envelope_mode) ? 4 : 2);
	STV090x_SETFIELD_Px(reg, DISEQC_RESET_FIELD, 1);
	अगर (STV090x_WRITE_DEMOD(state, DISTXCTL, reg) < 0)
		जाओ err;
	STV090x_SETFIELD_Px(reg, DISEQC_RESET_FIELD, 0);
	अगर (STV090x_WRITE_DEMOD(state, DISTXCTL, reg) < 0)
		जाओ err;

	STV090x_SETFIELD_Px(reg, DIS_PRECHARGE_FIELD, 1);
	अगर (STV090x_WRITE_DEMOD(state, DISTXCTL, reg) < 0)
		जाओ err;

	क्रम (i = 0; i < cmd->msg_len; i++) अणु

		जबतक (fअगरo_full) अणु
			reg = STV090x_READ_DEMOD(state, DISTXSTATUS);
			fअगरo_full = STV090x_GETFIELD_Px(reg, FIFO_FULL_FIELD);
		पूर्ण

		अगर (STV090x_WRITE_DEMOD(state, DISTXDATA, cmd->msg[i]) < 0)
			जाओ err;
	पूर्ण
	reg = STV090x_READ_DEMOD(state, DISTXCTL);
	STV090x_SETFIELD_Px(reg, DIS_PRECHARGE_FIELD, 0);
	अगर (STV090x_WRITE_DEMOD(state, DISTXCTL, reg) < 0)
		जाओ err;

	i = 0;

	जबतक ((!idle) && (i < 10)) अणु
		reg = STV090x_READ_DEMOD(state, DISTXSTATUS);
		idle = STV090x_GETFIELD_Px(reg, TX_IDLE_FIELD);
		msleep(10);
		i++;
	पूर्ण

	वापस 0;
err:
	dprपूर्णांकk(FE_ERROR, 1, "I/O error");
	वापस -1;
पूर्ण

अटल पूर्णांक stv090x_send_diseqc_burst(काष्ठा dvb_frontend *fe,
				     क्रमागत fe_sec_mini_cmd burst)
अणु
	काष्ठा stv090x_state *state = fe->demodulator_priv;
	u32 reg, idle = 0, fअगरo_full = 1;
	u8 mode, value;
	पूर्णांक i;

	reg = STV090x_READ_DEMOD(state, DISTXCTL);

	अगर (burst == SEC_MINI_A) अणु
		mode = (state->config->diseqc_envelope_mode) ? 5 : 3;
		value = 0x00;
	पूर्ण अन्यथा अणु
		mode = (state->config->diseqc_envelope_mode) ? 4 : 2;
		value = 0xFF;
	पूर्ण

	STV090x_SETFIELD_Px(reg, DISTX_MODE_FIELD, mode);
	STV090x_SETFIELD_Px(reg, DISEQC_RESET_FIELD, 1);
	अगर (STV090x_WRITE_DEMOD(state, DISTXCTL, reg) < 0)
		जाओ err;
	STV090x_SETFIELD_Px(reg, DISEQC_RESET_FIELD, 0);
	अगर (STV090x_WRITE_DEMOD(state, DISTXCTL, reg) < 0)
		जाओ err;

	STV090x_SETFIELD_Px(reg, DIS_PRECHARGE_FIELD, 1);
	अगर (STV090x_WRITE_DEMOD(state, DISTXCTL, reg) < 0)
		जाओ err;

	जबतक (fअगरo_full) अणु
		reg = STV090x_READ_DEMOD(state, DISTXSTATUS);
		fअगरo_full = STV090x_GETFIELD_Px(reg, FIFO_FULL_FIELD);
	पूर्ण

	अगर (STV090x_WRITE_DEMOD(state, DISTXDATA, value) < 0)
		जाओ err;

	reg = STV090x_READ_DEMOD(state, DISTXCTL);
	STV090x_SETFIELD_Px(reg, DIS_PRECHARGE_FIELD, 0);
	अगर (STV090x_WRITE_DEMOD(state, DISTXCTL, reg) < 0)
		जाओ err;

	i = 0;

	जबतक ((!idle) && (i < 10)) अणु
		reg = STV090x_READ_DEMOD(state, DISTXSTATUS);
		idle = STV090x_GETFIELD_Px(reg, TX_IDLE_FIELD);
		msleep(10);
		i++;
	पूर्ण

	वापस 0;
err:
	dprपूर्णांकk(FE_ERROR, 1, "I/O error");
	वापस -1;
पूर्ण

अटल पूर्णांक stv090x_recv_slave_reply(काष्ठा dvb_frontend *fe, काष्ठा dvb_diseqc_slave_reply *reply)
अणु
	काष्ठा stv090x_state *state = fe->demodulator_priv;
	u32 reg = 0, i = 0, rx_end = 0;

	जबतक ((rx_end != 1) && (i < 10)) अणु
		msleep(10);
		i++;
		reg = STV090x_READ_DEMOD(state, DISRX_ST0);
		rx_end = STV090x_GETFIELD_Px(reg, RX_END_FIELD);
	पूर्ण

	अगर (rx_end) अणु
		reply->msg_len = STV090x_GETFIELD_Px(reg, FIFO_BYTENBR_FIELD);
		क्रम (i = 0; i < reply->msg_len; i++)
			reply->msg[i] = STV090x_READ_DEMOD(state, DISRXDATA);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक stv090x_sleep(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा stv090x_state *state = fe->demodulator_priv;
	u32 reg;
	u8 full_standby = 0;

	अगर (stv090x_i2c_gate_ctrl(state, 1) < 0)
		जाओ err;

	अगर (state->config->tuner_sleep) अणु
		अगर (state->config->tuner_sleep(fe) < 0)
			जाओ err_gateoff;
	पूर्ण

	अगर (stv090x_i2c_gate_ctrl(state, 0) < 0)
		जाओ err;

	dprपूर्णांकk(FE_DEBUG, 1, "Set %s(%d) to sleep",
		state->device == STV0900 ? "STV0900" : "STV0903",
		state->demod);

	mutex_lock(&state->पूर्णांकernal->demod_lock);

	चयन (state->demod) अणु
	हाल STV090x_DEMODULATOR_0:
		/* घातer off ADC 1 */
		reg = stv090x_पढ़ो_reg(state, STV090x_TSTTNR1);
		STV090x_SETFIELD(reg, ADC1_PON_FIELD, 0);
		अगर (stv090x_ग_लिखो_reg(state, STV090x_TSTTNR1, reg) < 0)
			जाओ err_unlock;
		/* घातer off DiSEqC 1 */
		reg = stv090x_पढ़ो_reg(state, STV090x_TSTTNR2);
		STV090x_SETFIELD(reg, DISEQC1_PON_FIELD, 0);
		अगर (stv090x_ग_लिखो_reg(state, STV090x_TSTTNR2, reg) < 0)
			जाओ err_unlock;

		/* check whether path 2 is alपढ़ोy sleeping, that is when
		   ADC2 is off */
		reg = stv090x_पढ़ो_reg(state, STV090x_TSTTNR3);
		अगर (STV090x_GETFIELD(reg, ADC2_PON_FIELD) == 0)
			full_standby = 1;

		/* stop घड़ीs */
		reg = stv090x_पढ़ो_reg(state, STV090x_STOPCLK1);
		/* packet delineator 1 घड़ी */
		STV090x_SETFIELD(reg, STOP_CLKPKDT1_FIELD, 1);
		/* ADC 1 घड़ी */
		STV090x_SETFIELD(reg, STOP_CLKADCI1_FIELD, 1);
		/* FEC घड़ी is shared between the two paths, only stop it
		   when full standby is possible */
		अगर (full_standby)
			STV090x_SETFIELD(reg, STOP_CLKFEC_FIELD, 1);
		अगर (stv090x_ग_लिखो_reg(state, STV090x_STOPCLK1, reg) < 0)
			जाओ err_unlock;
		reg = stv090x_पढ़ो_reg(state, STV090x_STOPCLK2);
		/* sampling 1 घड़ी */
		STV090x_SETFIELD(reg, STOP_CLKSAMP1_FIELD, 1);
		/* viterbi 1 घड़ी */
		STV090x_SETFIELD(reg, STOP_CLKVIT1_FIELD, 1);
		/* TS घड़ी is shared between the two paths, only stop it
		   when full standby is possible */
		अगर (full_standby)
			STV090x_SETFIELD(reg, STOP_CLKTS_FIELD, 1);
		अगर (stv090x_ग_लिखो_reg(state, STV090x_STOPCLK2, reg) < 0)
			जाओ err_unlock;
		अवरोध;

	हाल STV090x_DEMODULATOR_1:
		/* घातer off ADC 2 */
		reg = stv090x_पढ़ो_reg(state, STV090x_TSTTNR3);
		STV090x_SETFIELD(reg, ADC2_PON_FIELD, 0);
		अगर (stv090x_ग_लिखो_reg(state, STV090x_TSTTNR3, reg) < 0)
			जाओ err_unlock;
		/* घातer off DiSEqC 2 */
		reg = stv090x_पढ़ो_reg(state, STV090x_TSTTNR4);
		STV090x_SETFIELD(reg, DISEQC2_PON_FIELD, 0);
		अगर (stv090x_ग_लिखो_reg(state, STV090x_TSTTNR4, reg) < 0)
			जाओ err_unlock;

		/* check whether path 1 is alपढ़ोy sleeping, that is when
		   ADC1 is off */
		reg = stv090x_पढ़ो_reg(state, STV090x_TSTTNR1);
		अगर (STV090x_GETFIELD(reg, ADC1_PON_FIELD) == 0)
			full_standby = 1;

		/* stop घड़ीs */
		reg = stv090x_पढ़ो_reg(state, STV090x_STOPCLK1);
		/* packet delineator 2 घड़ी */
		STV090x_SETFIELD(reg, STOP_CLKPKDT2_FIELD, 1);
		/* ADC 2 घड़ी */
		STV090x_SETFIELD(reg, STOP_CLKADCI2_FIELD, 1);
		/* FEC घड़ी is shared between the two paths, only stop it
		   when full standby is possible */
		अगर (full_standby)
			STV090x_SETFIELD(reg, STOP_CLKFEC_FIELD, 1);
		अगर (stv090x_ग_लिखो_reg(state, STV090x_STOPCLK1, reg) < 0)
			जाओ err_unlock;
		reg = stv090x_पढ़ो_reg(state, STV090x_STOPCLK2);
		/* sampling 2 घड़ी */
		STV090x_SETFIELD(reg, STOP_CLKSAMP2_FIELD, 1);
		/* viterbi 2 घड़ी */
		STV090x_SETFIELD(reg, STOP_CLKVIT2_FIELD, 1);
		/* TS घड़ी is shared between the two paths, only stop it
		   when full standby is possible */
		अगर (full_standby)
			STV090x_SETFIELD(reg, STOP_CLKTS_FIELD, 1);
		अगर (stv090x_ग_लिखो_reg(state, STV090x_STOPCLK2, reg) < 0)
			जाओ err_unlock;
		अवरोध;

	शेष:
		dprपूर्णांकk(FE_ERROR, 1, "Wrong demodulator!");
		अवरोध;
	पूर्ण

	अगर (full_standby) अणु
		/* general घातer off */
		reg = stv090x_पढ़ो_reg(state, STV090x_SYNTCTRL);
		STV090x_SETFIELD(reg, STANDBY_FIELD, 0x01);
		अगर (stv090x_ग_लिखो_reg(state, STV090x_SYNTCTRL, reg) < 0)
			जाओ err_unlock;
	पूर्ण

	mutex_unlock(&state->पूर्णांकernal->demod_lock);
	वापस 0;

err_gateoff:
	stv090x_i2c_gate_ctrl(state, 0);
	जाओ err;
err_unlock:
	mutex_unlock(&state->पूर्णांकernal->demod_lock);
err:
	dprपूर्णांकk(FE_ERROR, 1, "I/O error");
	वापस -1;
पूर्ण

अटल पूर्णांक stv090x_wakeup(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा stv090x_state *state = fe->demodulator_priv;
	u32 reg;

	dprपूर्णांकk(FE_DEBUG, 1, "Wake %s(%d) from standby",
		state->device == STV0900 ? "STV0900" : "STV0903",
		state->demod);

	mutex_lock(&state->पूर्णांकernal->demod_lock);

	/* general घातer on */
	reg = stv090x_पढ़ो_reg(state, STV090x_SYNTCTRL);
	STV090x_SETFIELD(reg, STANDBY_FIELD, 0x00);
	अगर (stv090x_ग_लिखो_reg(state, STV090x_SYNTCTRL, reg) < 0)
		जाओ err;

	चयन (state->demod) अणु
	हाल STV090x_DEMODULATOR_0:
		/* घातer on ADC 1 */
		reg = stv090x_पढ़ो_reg(state, STV090x_TSTTNR1);
		STV090x_SETFIELD(reg, ADC1_PON_FIELD, 1);
		अगर (stv090x_ग_लिखो_reg(state, STV090x_TSTTNR1, reg) < 0)
			जाओ err;
		/* घातer on DiSEqC 1 */
		reg = stv090x_पढ़ो_reg(state, STV090x_TSTTNR2);
		STV090x_SETFIELD(reg, DISEQC1_PON_FIELD, 1);
		अगर (stv090x_ग_लिखो_reg(state, STV090x_TSTTNR2, reg) < 0)
			जाओ err;

		/* activate घड़ीs */
		reg = stv090x_पढ़ो_reg(state, STV090x_STOPCLK1);
		/* packet delineator 1 घड़ी */
		STV090x_SETFIELD(reg, STOP_CLKPKDT1_FIELD, 0);
		/* ADC 1 घड़ी */
		STV090x_SETFIELD(reg, STOP_CLKADCI1_FIELD, 0);
		/* FEC घड़ी */
		STV090x_SETFIELD(reg, STOP_CLKFEC_FIELD, 0);
		अगर (stv090x_ग_लिखो_reg(state, STV090x_STOPCLK1, reg) < 0)
			जाओ err;
		reg = stv090x_पढ़ो_reg(state, STV090x_STOPCLK2);
		/* sampling 1 घड़ी */
		STV090x_SETFIELD(reg, STOP_CLKSAMP1_FIELD, 0);
		/* viterbi 1 घड़ी */
		STV090x_SETFIELD(reg, STOP_CLKVIT1_FIELD, 0);
		/* TS घड़ी */
		STV090x_SETFIELD(reg, STOP_CLKTS_FIELD, 0);
		अगर (stv090x_ग_लिखो_reg(state, STV090x_STOPCLK2, reg) < 0)
			जाओ err;
		अवरोध;

	हाल STV090x_DEMODULATOR_1:
		/* घातer on ADC 2 */
		reg = stv090x_पढ़ो_reg(state, STV090x_TSTTNR3);
		STV090x_SETFIELD(reg, ADC2_PON_FIELD, 1);
		अगर (stv090x_ग_लिखो_reg(state, STV090x_TSTTNR3, reg) < 0)
			जाओ err;
		/* घातer on DiSEqC 2 */
		reg = stv090x_पढ़ो_reg(state, STV090x_TSTTNR4);
		STV090x_SETFIELD(reg, DISEQC2_PON_FIELD, 1);
		अगर (stv090x_ग_लिखो_reg(state, STV090x_TSTTNR4, reg) < 0)
			जाओ err;

		/* activate घड़ीs */
		reg = stv090x_पढ़ो_reg(state, STV090x_STOPCLK1);
		/* packet delineator 2 घड़ी */
		STV090x_SETFIELD(reg, STOP_CLKPKDT2_FIELD, 0);
		/* ADC 2 घड़ी */
		STV090x_SETFIELD(reg, STOP_CLKADCI2_FIELD, 0);
		/* FEC घड़ी */
		STV090x_SETFIELD(reg, STOP_CLKFEC_FIELD, 0);
		अगर (stv090x_ग_लिखो_reg(state, STV090x_STOPCLK1, reg) < 0)
			जाओ err;
		reg = stv090x_पढ़ो_reg(state, STV090x_STOPCLK2);
		/* sampling 2 घड़ी */
		STV090x_SETFIELD(reg, STOP_CLKSAMP2_FIELD, 0);
		/* viterbi 2 घड़ी */
		STV090x_SETFIELD(reg, STOP_CLKVIT2_FIELD, 0);
		/* TS घड़ी */
		STV090x_SETFIELD(reg, STOP_CLKTS_FIELD, 0);
		अगर (stv090x_ग_लिखो_reg(state, STV090x_STOPCLK2, reg) < 0)
			जाओ err;
		अवरोध;

	शेष:
		dprपूर्णांकk(FE_ERROR, 1, "Wrong demodulator!");
		अवरोध;
	पूर्ण

	mutex_unlock(&state->पूर्णांकernal->demod_lock);
	वापस 0;
err:
	mutex_unlock(&state->पूर्णांकernal->demod_lock);
	dprपूर्णांकk(FE_ERROR, 1, "I/O error");
	वापस -1;
पूर्ण

अटल व्योम stv090x_release(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा stv090x_state *state = fe->demodulator_priv;

	state->पूर्णांकernal->num_used--;
	अगर (state->पूर्णांकernal->num_used <= 0) अणु

		dprपूर्णांकk(FE_ERROR, 1, "Actually removing");

		हटाओ_dev(state->पूर्णांकernal);
		kमुक्त(state->पूर्णांकernal);
	पूर्ण

	kमुक्त(state);
पूर्ण

अटल पूर्णांक stv090x_ldpc_mode(काष्ठा stv090x_state *state, क्रमागत stv090x_mode ldpc_mode)
अणु
	u32 reg = 0;

	reg = stv090x_पढ़ो_reg(state, STV090x_GENCFG);

	चयन (ldpc_mode) अणु
	हाल STV090x_DUAL:
	शेष:
		अगर ((state->demod_mode != STV090x_DUAL) || (STV090x_GETFIELD(reg, DDEMOD_FIELD) != 1)) अणु
			/* set LDPC to dual mode */
			अगर (stv090x_ग_लिखो_reg(state, STV090x_GENCFG, 0x1d) < 0)
				जाओ err;

			state->demod_mode = STV090x_DUAL;

			reg = stv090x_पढ़ो_reg(state, STV090x_TSTRES0);
			STV090x_SETFIELD(reg, FRESFEC_FIELD, 0x1);
			अगर (stv090x_ग_लिखो_reg(state, STV090x_TSTRES0, reg) < 0)
				जाओ err;
			STV090x_SETFIELD(reg, FRESFEC_FIELD, 0x0);
			अगर (stv090x_ग_लिखो_reg(state, STV090x_TSTRES0, reg) < 0)
				जाओ err;

			अगर (STV090x_WRITE_DEMOD(state, MODCODLST0, 0xff) < 0)
				जाओ err;
			अगर (STV090x_WRITE_DEMOD(state, MODCODLST1, 0xff) < 0)
				जाओ err;
			अगर (STV090x_WRITE_DEMOD(state, MODCODLST2, 0xff) < 0)
				जाओ err;
			अगर (STV090x_WRITE_DEMOD(state, MODCODLST3, 0xff) < 0)
				जाओ err;
			अगर (STV090x_WRITE_DEMOD(state, MODCODLST4, 0xff) < 0)
				जाओ err;
			अगर (STV090x_WRITE_DEMOD(state, MODCODLST5, 0xff) < 0)
				जाओ err;
			अगर (STV090x_WRITE_DEMOD(state, MODCODLST6, 0xff) < 0)
				जाओ err;

			अगर (STV090x_WRITE_DEMOD(state, MODCODLST7, 0xcc) < 0)
				जाओ err;
			अगर (STV090x_WRITE_DEMOD(state, MODCODLST8, 0xcc) < 0)
				जाओ err;
			अगर (STV090x_WRITE_DEMOD(state, MODCODLST9, 0xcc) < 0)
				जाओ err;
			अगर (STV090x_WRITE_DEMOD(state, MODCODLSTA, 0xcc) < 0)
				जाओ err;
			अगर (STV090x_WRITE_DEMOD(state, MODCODLSTB, 0xcc) < 0)
				जाओ err;
			अगर (STV090x_WRITE_DEMOD(state, MODCODLSTC, 0xcc) < 0)
				जाओ err;
			अगर (STV090x_WRITE_DEMOD(state, MODCODLSTD, 0xcc) < 0)
				जाओ err;

			अगर (STV090x_WRITE_DEMOD(state, MODCODLSTE, 0xff) < 0)
				जाओ err;
			अगर (STV090x_WRITE_DEMOD(state, MODCODLSTF, 0xcf) < 0)
				जाओ err;
		पूर्ण
		अवरोध;

	हाल STV090x_SINGLE:
		अगर (stv090x_stop_modcod(state) < 0)
			जाओ err;
		अगर (stv090x_activate_modcod_single(state) < 0)
			जाओ err;

		अगर (state->demod == STV090x_DEMODULATOR_1) अणु
			अगर (stv090x_ग_लिखो_reg(state, STV090x_GENCFG, 0x06) < 0) /* path 2 */
				जाओ err;
		पूर्ण अन्यथा अणु
			अगर (stv090x_ग_लिखो_reg(state, STV090x_GENCFG, 0x04) < 0) /* path 1 */
				जाओ err;
		पूर्ण

		reg = stv090x_पढ़ो_reg(state, STV090x_TSTRES0);
		STV090x_SETFIELD(reg, FRESFEC_FIELD, 0x1);
		अगर (stv090x_ग_लिखो_reg(state, STV090x_TSTRES0, reg) < 0)
			जाओ err;
		STV090x_SETFIELD(reg, FRESFEC_FIELD, 0x0);
		अगर (stv090x_ग_लिखो_reg(state, STV090x_TSTRES0, reg) < 0)
			जाओ err;

		reg = STV090x_READ_DEMOD(state, PDELCTRL1);
		STV090x_SETFIELD_Px(reg, ALGOSWRST_FIELD, 0x01);
		अगर (STV090x_WRITE_DEMOD(state, PDELCTRL1, reg) < 0)
			जाओ err;
		STV090x_SETFIELD_Px(reg, ALGOSWRST_FIELD, 0x00);
		अगर (STV090x_WRITE_DEMOD(state, PDELCTRL1, reg) < 0)
			जाओ err;
		अवरोध;
	पूर्ण

	वापस 0;
err:
	dprपूर्णांकk(FE_ERROR, 1, "I/O error");
	वापस -1;
पूर्ण

/* वापस (Hz), clk in Hz*/
अटल u32 stv090x_get_mclk(काष्ठा stv090x_state *state)
अणु
	स्थिर काष्ठा stv090x_config *config = state->config;
	u32 भाग, reg;
	u8 ratio;

	भाग = stv090x_पढ़ो_reg(state, STV090x_NCOARSE);
	reg = stv090x_पढ़ो_reg(state, STV090x_SYNTCTRL);
	ratio = STV090x_GETFIELD(reg, SELX1RATIO_FIELD) ? 4 : 6;

	वापस (भाग + 1) * config->xtal / ratio; /* kHz */
पूर्ण

अटल पूर्णांक stv090x_set_mclk(काष्ठा stv090x_state *state, u32 mclk, u32 clk)
अणु
	स्थिर काष्ठा stv090x_config *config = state->config;
	u32 reg, भाग, clk_sel;

	reg = stv090x_पढ़ो_reg(state, STV090x_SYNTCTRL);
	clk_sel = ((STV090x_GETFIELD(reg, SELX1RATIO_FIELD) == 1) ? 4 : 6);

	भाग = ((clk_sel * mclk) / config->xtal) - 1;

	reg = stv090x_पढ़ो_reg(state, STV090x_NCOARSE);
	STV090x_SETFIELD(reg, M_DIV_FIELD, भाग);
	अगर (stv090x_ग_लिखो_reg(state, STV090x_NCOARSE, reg) < 0)
		जाओ err;

	state->पूर्णांकernal->mclk = stv090x_get_mclk(state);

	/*Set the DiseqC frequency to 22KHz */
	भाग = state->पूर्णांकernal->mclk / 704000;
	अगर (STV090x_WRITE_DEMOD(state, F22TX, भाग) < 0)
		जाओ err;
	अगर (STV090x_WRITE_DEMOD(state, F22RX, भाग) < 0)
		जाओ err;

	वापस 0;
err:
	dprपूर्णांकk(FE_ERROR, 1, "I/O error");
	वापस -1;
पूर्ण

अटल पूर्णांक stv0900_set_tspath(काष्ठा stv090x_state *state)
अणु
	u32 reg;

	अगर (state->पूर्णांकernal->dev_ver >= 0x20) अणु
		चयन (state->config->ts1_mode) अणु
		हाल STV090x_TSMODE_PARALLEL_PUNCTURED:
		हाल STV090x_TSMODE_DVBCI:
			चयन (state->config->ts2_mode) अणु
			हाल STV090x_TSMODE_SERIAL_PUNCTURED:
			हाल STV090x_TSMODE_SERIAL_CONTINUOUS:
			शेष:
				stv090x_ग_लिखो_reg(state, STV090x_TSGENERAL, 0x00);
				अवरोध;

			हाल STV090x_TSMODE_PARALLEL_PUNCTURED:
			हाल STV090x_TSMODE_DVBCI:
				अगर (stv090x_ग_लिखो_reg(state, STV090x_TSGENERAL, 0x06) < 0) /* Mux'd stream mode */
					जाओ err;
				reg = stv090x_पढ़ो_reg(state, STV090x_P1_TSCFGM);
				STV090x_SETFIELD_Px(reg, TSFIFO_MANSPEED_FIELD, 3);
				अगर (stv090x_ग_लिखो_reg(state, STV090x_P1_TSCFGM, reg) < 0)
					जाओ err;
				reg = stv090x_पढ़ो_reg(state, STV090x_P2_TSCFGM);
				STV090x_SETFIELD_Px(reg, TSFIFO_MANSPEED_FIELD, 3);
				अगर (stv090x_ग_लिखो_reg(state, STV090x_P2_TSCFGM, reg) < 0)
					जाओ err;
				अगर (stv090x_ग_लिखो_reg(state, STV090x_P1_TSSPEED, 0x14) < 0)
					जाओ err;
				अगर (stv090x_ग_लिखो_reg(state, STV090x_P2_TSSPEED, 0x28) < 0)
					जाओ err;
				अवरोध;
			पूर्ण
			अवरोध;

		हाल STV090x_TSMODE_SERIAL_PUNCTURED:
		हाल STV090x_TSMODE_SERIAL_CONTINUOUS:
		शेष:
			चयन (state->config->ts2_mode) अणु
			हाल STV090x_TSMODE_SERIAL_PUNCTURED:
			हाल STV090x_TSMODE_SERIAL_CONTINUOUS:
			शेष:
				अगर (stv090x_ग_लिखो_reg(state, STV090x_TSGENERAL, 0x0c) < 0)
					जाओ err;
				अवरोध;

			हाल STV090x_TSMODE_PARALLEL_PUNCTURED:
			हाल STV090x_TSMODE_DVBCI:
				अगर (stv090x_ग_लिखो_reg(state, STV090x_TSGENERAL, 0x0a) < 0)
					जाओ err;
				अवरोध;
			पूर्ण
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		चयन (state->config->ts1_mode) अणु
		हाल STV090x_TSMODE_PARALLEL_PUNCTURED:
		हाल STV090x_TSMODE_DVBCI:
			चयन (state->config->ts2_mode) अणु
			हाल STV090x_TSMODE_SERIAL_PUNCTURED:
			हाल STV090x_TSMODE_SERIAL_CONTINUOUS:
			शेष:
				stv090x_ग_लिखो_reg(state, STV090x_TSGENERAL1X, 0x10);
				अवरोध;

			हाल STV090x_TSMODE_PARALLEL_PUNCTURED:
			हाल STV090x_TSMODE_DVBCI:
				stv090x_ग_लिखो_reg(state, STV090x_TSGENERAL1X, 0x16);
				reg = stv090x_पढ़ो_reg(state, STV090x_P1_TSCFGM);
				STV090x_SETFIELD_Px(reg, TSFIFO_MANSPEED_FIELD, 3);
				अगर (stv090x_ग_लिखो_reg(state, STV090x_P1_TSCFGM, reg) < 0)
					जाओ err;
				reg = stv090x_पढ़ो_reg(state, STV090x_P1_TSCFGM);
				STV090x_SETFIELD_Px(reg, TSFIFO_MANSPEED_FIELD, 0);
				अगर (stv090x_ग_लिखो_reg(state, STV090x_P1_TSCFGM, reg) < 0)
					जाओ err;
				अगर (stv090x_ग_लिखो_reg(state, STV090x_P1_TSSPEED, 0x14) < 0)
					जाओ err;
				अगर (stv090x_ग_लिखो_reg(state, STV090x_P2_TSSPEED, 0x28) < 0)
					जाओ err;
				अवरोध;
			पूर्ण
			अवरोध;

		हाल STV090x_TSMODE_SERIAL_PUNCTURED:
		हाल STV090x_TSMODE_SERIAL_CONTINUOUS:
		शेष:
			चयन (state->config->ts2_mode) अणु
			हाल STV090x_TSMODE_SERIAL_PUNCTURED:
			हाल STV090x_TSMODE_SERIAL_CONTINUOUS:
			शेष:
				stv090x_ग_लिखो_reg(state, STV090x_TSGENERAL1X, 0x14);
				अवरोध;

			हाल STV090x_TSMODE_PARALLEL_PUNCTURED:
			हाल STV090x_TSMODE_DVBCI:
				stv090x_ग_लिखो_reg(state, STV090x_TSGENERAL1X, 0x12);
				अवरोध;
			पूर्ण
			अवरोध;
		पूर्ण
	पूर्ण

	चयन (state->config->ts1_mode) अणु
	हाल STV090x_TSMODE_PARALLEL_PUNCTURED:
		reg = stv090x_पढ़ो_reg(state, STV090x_P1_TSCFGH);
		STV090x_SETFIELD_Px(reg, TSFIFO_TEIUPDATE_FIELD, state->config->ts1_tei);
		STV090x_SETFIELD_Px(reg, TSFIFO_SERIAL_FIELD, 0x00);
		STV090x_SETFIELD_Px(reg, TSFIFO_DVBCI_FIELD, 0x00);
		अगर (stv090x_ग_लिखो_reg(state, STV090x_P1_TSCFGH, reg) < 0)
			जाओ err;
		अवरोध;

	हाल STV090x_TSMODE_DVBCI:
		reg = stv090x_पढ़ो_reg(state, STV090x_P1_TSCFGH);
		STV090x_SETFIELD_Px(reg, TSFIFO_TEIUPDATE_FIELD, state->config->ts1_tei);
		STV090x_SETFIELD_Px(reg, TSFIFO_SERIAL_FIELD, 0x00);
		STV090x_SETFIELD_Px(reg, TSFIFO_DVBCI_FIELD, 0x01);
		अगर (stv090x_ग_लिखो_reg(state, STV090x_P1_TSCFGH, reg) < 0)
			जाओ err;
		अवरोध;

	हाल STV090x_TSMODE_SERIAL_PUNCTURED:
		reg = stv090x_पढ़ो_reg(state, STV090x_P1_TSCFGH);
		STV090x_SETFIELD_Px(reg, TSFIFO_TEIUPDATE_FIELD, state->config->ts1_tei);
		STV090x_SETFIELD_Px(reg, TSFIFO_SERIAL_FIELD, 0x01);
		STV090x_SETFIELD_Px(reg, TSFIFO_DVBCI_FIELD, 0x00);
		अगर (stv090x_ग_लिखो_reg(state, STV090x_P1_TSCFGH, reg) < 0)
			जाओ err;
		अवरोध;

	हाल STV090x_TSMODE_SERIAL_CONTINUOUS:
		reg = stv090x_पढ़ो_reg(state, STV090x_P1_TSCFGH);
		STV090x_SETFIELD_Px(reg, TSFIFO_TEIUPDATE_FIELD, state->config->ts1_tei);
		STV090x_SETFIELD_Px(reg, TSFIFO_SERIAL_FIELD, 0x01);
		STV090x_SETFIELD_Px(reg, TSFIFO_DVBCI_FIELD, 0x01);
		अगर (stv090x_ग_लिखो_reg(state, STV090x_P1_TSCFGH, reg) < 0)
			जाओ err;
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	चयन (state->config->ts2_mode) अणु
	हाल STV090x_TSMODE_PARALLEL_PUNCTURED:
		reg = stv090x_पढ़ो_reg(state, STV090x_P2_TSCFGH);
		STV090x_SETFIELD_Px(reg, TSFIFO_TEIUPDATE_FIELD, state->config->ts2_tei);
		STV090x_SETFIELD_Px(reg, TSFIFO_SERIAL_FIELD, 0x00);
		STV090x_SETFIELD_Px(reg, TSFIFO_DVBCI_FIELD, 0x00);
		अगर (stv090x_ग_लिखो_reg(state, STV090x_P2_TSCFGH, reg) < 0)
			जाओ err;
		अवरोध;

	हाल STV090x_TSMODE_DVBCI:
		reg = stv090x_पढ़ो_reg(state, STV090x_P2_TSCFGH);
		STV090x_SETFIELD_Px(reg, TSFIFO_TEIUPDATE_FIELD, state->config->ts2_tei);
		STV090x_SETFIELD_Px(reg, TSFIFO_SERIAL_FIELD, 0x00);
		STV090x_SETFIELD_Px(reg, TSFIFO_DVBCI_FIELD, 0x01);
		अगर (stv090x_ग_लिखो_reg(state, STV090x_P2_TSCFGH, reg) < 0)
			जाओ err;
		अवरोध;

	हाल STV090x_TSMODE_SERIAL_PUNCTURED:
		reg = stv090x_पढ़ो_reg(state, STV090x_P2_TSCFGH);
		STV090x_SETFIELD_Px(reg, TSFIFO_TEIUPDATE_FIELD, state->config->ts2_tei);
		STV090x_SETFIELD_Px(reg, TSFIFO_SERIAL_FIELD, 0x01);
		STV090x_SETFIELD_Px(reg, TSFIFO_DVBCI_FIELD, 0x00);
		अगर (stv090x_ग_लिखो_reg(state, STV090x_P2_TSCFGH, reg) < 0)
			जाओ err;
		अवरोध;

	हाल STV090x_TSMODE_SERIAL_CONTINUOUS:
		reg = stv090x_पढ़ो_reg(state, STV090x_P2_TSCFGH);
		STV090x_SETFIELD_Px(reg, TSFIFO_TEIUPDATE_FIELD, state->config->ts2_tei);
		STV090x_SETFIELD_Px(reg, TSFIFO_SERIAL_FIELD, 0x01);
		STV090x_SETFIELD_Px(reg, TSFIFO_DVBCI_FIELD, 0x01);
		अगर (stv090x_ग_लिखो_reg(state, STV090x_P2_TSCFGH, reg) < 0)
			जाओ err;
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	अगर (state->config->ts1_clk > 0) अणु
		u32 speed;

		चयन (state->config->ts1_mode) अणु
		हाल STV090x_TSMODE_PARALLEL_PUNCTURED:
		हाल STV090x_TSMODE_DVBCI:
		शेष:
			speed = state->पूर्णांकernal->mclk /
				(state->config->ts1_clk / 4);
			अगर (speed < 0x08)
				speed = 0x08;
			अगर (speed > 0xFF)
				speed = 0xFF;
			अवरोध;
		हाल STV090x_TSMODE_SERIAL_PUNCTURED:
		हाल STV090x_TSMODE_SERIAL_CONTINUOUS:
			speed = state->पूर्णांकernal->mclk /
				(state->config->ts1_clk / 32);
			अगर (speed < 0x20)
				speed = 0x20;
			अगर (speed > 0xFF)
				speed = 0xFF;
			अवरोध;
		पूर्ण
		reg = stv090x_पढ़ो_reg(state, STV090x_P1_TSCFGM);
		STV090x_SETFIELD_Px(reg, TSFIFO_MANSPEED_FIELD, 3);
		अगर (stv090x_ग_लिखो_reg(state, STV090x_P1_TSCFGM, reg) < 0)
			जाओ err;
		अगर (stv090x_ग_लिखो_reg(state, STV090x_P1_TSSPEED, speed) < 0)
			जाओ err;
	पूर्ण

	अगर (state->config->ts2_clk > 0) अणु
		u32 speed;

		चयन (state->config->ts2_mode) अणु
		हाल STV090x_TSMODE_PARALLEL_PUNCTURED:
		हाल STV090x_TSMODE_DVBCI:
		शेष:
			speed = state->पूर्णांकernal->mclk /
				(state->config->ts2_clk / 4);
			अगर (speed < 0x08)
				speed = 0x08;
			अगर (speed > 0xFF)
				speed = 0xFF;
			अवरोध;
		हाल STV090x_TSMODE_SERIAL_PUNCTURED:
		हाल STV090x_TSMODE_SERIAL_CONTINUOUS:
			speed = state->पूर्णांकernal->mclk /
				(state->config->ts2_clk / 32);
			अगर (speed < 0x20)
				speed = 0x20;
			अगर (speed > 0xFF)
				speed = 0xFF;
			अवरोध;
		पूर्ण
		reg = stv090x_पढ़ो_reg(state, STV090x_P2_TSCFGM);
		STV090x_SETFIELD_Px(reg, TSFIFO_MANSPEED_FIELD, 3);
		अगर (stv090x_ग_लिखो_reg(state, STV090x_P2_TSCFGM, reg) < 0)
			जाओ err;
		अगर (stv090x_ग_लिखो_reg(state, STV090x_P2_TSSPEED, speed) < 0)
			जाओ err;
	पूर्ण

	reg = stv090x_पढ़ो_reg(state, STV090x_P2_TSCFGH);
	STV090x_SETFIELD_Px(reg, RST_HWARE_FIELD, 0x01);
	अगर (stv090x_ग_लिखो_reg(state, STV090x_P2_TSCFGH, reg) < 0)
		जाओ err;
	STV090x_SETFIELD_Px(reg, RST_HWARE_FIELD, 0x00);
	अगर (stv090x_ग_लिखो_reg(state, STV090x_P2_TSCFGH, reg) < 0)
		जाओ err;

	reg = stv090x_पढ़ो_reg(state, STV090x_P1_TSCFGH);
	STV090x_SETFIELD_Px(reg, RST_HWARE_FIELD, 0x01);
	अगर (stv090x_ग_लिखो_reg(state, STV090x_P1_TSCFGH, reg) < 0)
		जाओ err;
	STV090x_SETFIELD_Px(reg, RST_HWARE_FIELD, 0x00);
	अगर (stv090x_ग_लिखो_reg(state, STV090x_P1_TSCFGH, reg) < 0)
		जाओ err;

	वापस 0;
err:
	dprपूर्णांकk(FE_ERROR, 1, "I/O error");
	वापस -1;
पूर्ण

अटल पूर्णांक stv0903_set_tspath(काष्ठा stv090x_state *state)
अणु
	u32 reg;

	अगर (state->पूर्णांकernal->dev_ver >= 0x20) अणु
		चयन (state->config->ts1_mode) अणु
		हाल STV090x_TSMODE_PARALLEL_PUNCTURED:
		हाल STV090x_TSMODE_DVBCI:
			stv090x_ग_लिखो_reg(state, STV090x_TSGENERAL, 0x00);
			अवरोध;

		हाल STV090x_TSMODE_SERIAL_PUNCTURED:
		हाल STV090x_TSMODE_SERIAL_CONTINUOUS:
		शेष:
			stv090x_ग_लिखो_reg(state, STV090x_TSGENERAL, 0x0c);
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		चयन (state->config->ts1_mode) अणु
		हाल STV090x_TSMODE_PARALLEL_PUNCTURED:
		हाल STV090x_TSMODE_DVBCI:
			stv090x_ग_लिखो_reg(state, STV090x_TSGENERAL1X, 0x10);
			अवरोध;

		हाल STV090x_TSMODE_SERIAL_PUNCTURED:
		हाल STV090x_TSMODE_SERIAL_CONTINUOUS:
		शेष:
			stv090x_ग_लिखो_reg(state, STV090x_TSGENERAL1X, 0x14);
			अवरोध;
		पूर्ण
	पूर्ण

	चयन (state->config->ts1_mode) अणु
	हाल STV090x_TSMODE_PARALLEL_PUNCTURED:
		reg = stv090x_पढ़ो_reg(state, STV090x_P1_TSCFGH);
		STV090x_SETFIELD_Px(reg, TSFIFO_SERIAL_FIELD, 0x00);
		STV090x_SETFIELD_Px(reg, TSFIFO_DVBCI_FIELD, 0x00);
		अगर (stv090x_ग_लिखो_reg(state, STV090x_P1_TSCFGH, reg) < 0)
			जाओ err;
		अवरोध;

	हाल STV090x_TSMODE_DVBCI:
		reg = stv090x_पढ़ो_reg(state, STV090x_P1_TSCFGH);
		STV090x_SETFIELD_Px(reg, TSFIFO_SERIAL_FIELD, 0x00);
		STV090x_SETFIELD_Px(reg, TSFIFO_DVBCI_FIELD, 0x01);
		अगर (stv090x_ग_लिखो_reg(state, STV090x_P1_TSCFGH, reg) < 0)
			जाओ err;
		अवरोध;

	हाल STV090x_TSMODE_SERIAL_PUNCTURED:
		reg = stv090x_पढ़ो_reg(state, STV090x_P1_TSCFGH);
		STV090x_SETFIELD_Px(reg, TSFIFO_SERIAL_FIELD, 0x01);
		STV090x_SETFIELD_Px(reg, TSFIFO_DVBCI_FIELD, 0x00);
		अगर (stv090x_ग_लिखो_reg(state, STV090x_P1_TSCFGH, reg) < 0)
			जाओ err;
		अवरोध;

	हाल STV090x_TSMODE_SERIAL_CONTINUOUS:
		reg = stv090x_पढ़ो_reg(state, STV090x_P1_TSCFGH);
		STV090x_SETFIELD_Px(reg, TSFIFO_SERIAL_FIELD, 0x01);
		STV090x_SETFIELD_Px(reg, TSFIFO_DVBCI_FIELD, 0x01);
		अगर (stv090x_ग_लिखो_reg(state, STV090x_P1_TSCFGH, reg) < 0)
			जाओ err;
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	अगर (state->config->ts1_clk > 0) अणु
		u32 speed;

		चयन (state->config->ts1_mode) अणु
		हाल STV090x_TSMODE_PARALLEL_PUNCTURED:
		हाल STV090x_TSMODE_DVBCI:
		शेष:
			speed = state->पूर्णांकernal->mclk /
				(state->config->ts1_clk / 4);
			अगर (speed < 0x08)
				speed = 0x08;
			अगर (speed > 0xFF)
				speed = 0xFF;
			अवरोध;
		हाल STV090x_TSMODE_SERIAL_PUNCTURED:
		हाल STV090x_TSMODE_SERIAL_CONTINUOUS:
			speed = state->पूर्णांकernal->mclk /
				(state->config->ts1_clk / 32);
			अगर (speed < 0x20)
				speed = 0x20;
			अगर (speed > 0xFF)
				speed = 0xFF;
			अवरोध;
		पूर्ण
		reg = stv090x_पढ़ो_reg(state, STV090x_P1_TSCFGM);
		STV090x_SETFIELD_Px(reg, TSFIFO_MANSPEED_FIELD, 3);
		अगर (stv090x_ग_लिखो_reg(state, STV090x_P1_TSCFGM, reg) < 0)
			जाओ err;
		अगर (stv090x_ग_लिखो_reg(state, STV090x_P1_TSSPEED, speed) < 0)
			जाओ err;
	पूर्ण

	reg = stv090x_पढ़ो_reg(state, STV090x_P1_TSCFGH);
	STV090x_SETFIELD_Px(reg, RST_HWARE_FIELD, 0x01);
	अगर (stv090x_ग_लिखो_reg(state, STV090x_P1_TSCFGH, reg) < 0)
		जाओ err;
	STV090x_SETFIELD_Px(reg, RST_HWARE_FIELD, 0x00);
	अगर (stv090x_ग_लिखो_reg(state, STV090x_P1_TSCFGH, reg) < 0)
		जाओ err;

	वापस 0;
err:
	dprपूर्णांकk(FE_ERROR, 1, "I/O error");
	वापस -1;
पूर्ण

अटल पूर्णांक stv090x_init(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा stv090x_state *state = fe->demodulator_priv;
	स्थिर काष्ठा stv090x_config *config = state->config;
	u32 reg;

	अगर (state->पूर्णांकernal->mclk == 0) अणु
		/* call tuner init to configure the tuner's घड़ी output
		   भागider directly beक्रमe setting up the master घड़ी of
		   the stv090x. */
		अगर (stv090x_i2c_gate_ctrl(state, 1) < 0)
			जाओ err;

		अगर (config->tuner_init) अणु
			अगर (config->tuner_init(fe) < 0)
				जाओ err_gateoff;
		पूर्ण

		अगर (stv090x_i2c_gate_ctrl(state, 0) < 0)
			जाओ err;

		stv090x_set_mclk(state, 135000000, config->xtal); /* 135 Mhz */
		msleep(5);
		अगर (stv090x_ग_लिखो_reg(state, STV090x_SYNTCTRL,
				      0x20 | config->clk_mode) < 0)
			जाओ err;
		stv090x_get_mclk(state);
	पूर्ण

	अगर (stv090x_wakeup(fe) < 0) अणु
		dprपूर्णांकk(FE_ERROR, 1, "Error waking device");
		जाओ err;
	पूर्ण

	अगर (stv090x_ldpc_mode(state, state->demod_mode) < 0)
		जाओ err;

	reg = STV090x_READ_DEMOD(state, TNRCFG2);
	STV090x_SETFIELD_Px(reg, TUN_IQSWAP_FIELD, state->inversion);
	अगर (STV090x_WRITE_DEMOD(state, TNRCFG2, reg) < 0)
		जाओ err;
	reg = STV090x_READ_DEMOD(state, DEMOD);
	STV090x_SETFIELD_Px(reg, ROLLOFF_CONTROL_FIELD, state->rolloff);
	अगर (STV090x_WRITE_DEMOD(state, DEMOD, reg) < 0)
		जाओ err;

	अगर (stv090x_i2c_gate_ctrl(state, 1) < 0)
		जाओ err;

	अगर (config->tuner_set_mode) अणु
		अगर (config->tuner_set_mode(fe, TUNER_WAKE) < 0)
			जाओ err_gateoff;
	पूर्ण

	अगर (config->tuner_init) अणु
		अगर (config->tuner_init(fe) < 0)
			जाओ err_gateoff;
	पूर्ण

	अगर (stv090x_i2c_gate_ctrl(state, 0) < 0)
		जाओ err;

	अगर (state->device == STV0900) अणु
		अगर (stv0900_set_tspath(state) < 0)
			जाओ err;
	पूर्ण अन्यथा अणु
		अगर (stv0903_set_tspath(state) < 0)
			जाओ err;
	पूर्ण

	वापस 0;

err_gateoff:
	stv090x_i2c_gate_ctrl(state, 0);
err:
	dprपूर्णांकk(FE_ERROR, 1, "I/O error");
	वापस -1;
पूर्ण

अटल पूर्णांक stv090x_setup(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा stv090x_state *state = fe->demodulator_priv;
	स्थिर काष्ठा stv090x_config *config = state->config;
	स्थिर काष्ठा stv090x_reg *stv090x_initval = शून्य;
	स्थिर काष्ठा stv090x_reg *stv090x_cut20_val = शून्य;
	अचिन्हित दीर्घ t1_size = 0, t2_size = 0;
	u32 reg = 0;

	पूर्णांक i;

	अगर (state->device == STV0900) अणु
		dprपूर्णांकk(FE_DEBUG, 1, "Initializing STV0900");
		stv090x_initval = stv0900_initval;
		t1_size = ARRAY_SIZE(stv0900_initval);
		stv090x_cut20_val = stv0900_cut20_val;
		t2_size = ARRAY_SIZE(stv0900_cut20_val);
	पूर्ण अन्यथा अगर (state->device == STV0903) अणु
		dprपूर्णांकk(FE_DEBUG, 1, "Initializing STV0903");
		stv090x_initval = stv0903_initval;
		t1_size = ARRAY_SIZE(stv0903_initval);
		stv090x_cut20_val = stv0903_cut20_val;
		t2_size = ARRAY_SIZE(stv0903_cut20_val);
	पूर्ण

	/* STV090x init */

	/* Stop Demod */
	अगर (stv090x_ग_लिखो_reg(state, STV090x_P1_DMDISTATE, 0x5c) < 0)
		जाओ err;
	अगर (state->device == STV0900)
		अगर (stv090x_ग_लिखो_reg(state, STV090x_P2_DMDISTATE, 0x5c) < 0)
			जाओ err;

	msleep(5);

	/* Set No Tuner Mode */
	अगर (stv090x_ग_लिखो_reg(state, STV090x_P1_TNRCFG, 0x6c) < 0)
		जाओ err;
	अगर (state->device == STV0900)
		अगर (stv090x_ग_लिखो_reg(state, STV090x_P2_TNRCFG, 0x6c) < 0)
			जाओ err;

	/* I2C repeater OFF */
	STV090x_SETFIELD_Px(reg, ENARPT_LEVEL_FIELD, config->repeater_level);
	अगर (stv090x_ग_लिखो_reg(state, STV090x_P1_I2CRPT, reg) < 0)
		जाओ err;
	अगर (state->device == STV0900)
		अगर (stv090x_ग_लिखो_reg(state, STV090x_P2_I2CRPT, reg) < 0)
			जाओ err;

	अगर (stv090x_ग_लिखो_reg(state, STV090x_NCOARSE, 0x13) < 0) /* set PLL भागider */
		जाओ err;
	msleep(5);
	अगर (stv090x_ग_लिखो_reg(state, STV090x_I2CCFG, 0x08) < 0) /* 1/41 oversampling */
		जाओ err;
	अगर (stv090x_ग_लिखो_reg(state, STV090x_SYNTCTRL, 0x20 | config->clk_mode) < 0) /* enable PLL */
		जाओ err;
	msleep(5);

	/* ग_लिखो initval */
	dprपूर्णांकk(FE_DEBUG, 1, "Setting up initial values");
	क्रम (i = 0; i < t1_size; i++) अणु
		अगर (stv090x_ग_लिखो_reg(state, stv090x_initval[i].addr, stv090x_initval[i].data) < 0)
			जाओ err;
	पूर्ण

	state->पूर्णांकernal->dev_ver = stv090x_पढ़ो_reg(state, STV090x_MID);
	अगर (state->पूर्णांकernal->dev_ver >= 0x20) अणु
		अगर (stv090x_ग_लिखो_reg(state, STV090x_TSGENERAL, 0x0c) < 0)
			जाओ err;

		/* ग_लिखो cut20_val*/
		dprपूर्णांकk(FE_DEBUG, 1, "Setting up Cut 2.0 initial values");
		क्रम (i = 0; i < t2_size; i++) अणु
			अगर (stv090x_ग_लिखो_reg(state, stv090x_cut20_val[i].addr, stv090x_cut20_val[i].data) < 0)
				जाओ err;
		पूर्ण

	पूर्ण अन्यथा अगर (state->पूर्णांकernal->dev_ver < 0x20) अणु
		dprपूर्णांकk(FE_ERROR, 1, "ERROR: Unsupported Cut: 0x%02x!",
			state->पूर्णांकernal->dev_ver);

		जाओ err;
	पूर्ण अन्यथा अगर (state->पूर्णांकernal->dev_ver > 0x30) अणु
		/* we shouldn't bail out from here */
		dprपूर्णांकk(FE_ERROR, 1, "INFO: Cut: 0x%02x probably incomplete support!",
			state->पूर्णांकernal->dev_ver);
	पूर्ण

	/* ADC1 range */
	reg = stv090x_पढ़ो_reg(state, STV090x_TSTTNR1);
	STV090x_SETFIELD(reg, ADC1_INMODE_FIELD,
		(config->adc1_range == STV090x_ADC_1Vpp) ? 0 : 1);
	अगर (stv090x_ग_लिखो_reg(state, STV090x_TSTTNR1, reg) < 0)
		जाओ err;

	/* ADC2 range */
	reg = stv090x_पढ़ो_reg(state, STV090x_TSTTNR3);
	STV090x_SETFIELD(reg, ADC2_INMODE_FIELD,
		(config->adc2_range == STV090x_ADC_1Vpp) ? 0 : 1);
	अगर (stv090x_ग_लिखो_reg(state, STV090x_TSTTNR3, reg) < 0)
		जाओ err;

	अगर (stv090x_ग_लिखो_reg(state, STV090x_TSTRES0, 0x80) < 0)
		जाओ err;
	अगर (stv090x_ग_लिखो_reg(state, STV090x_TSTRES0, 0x00) < 0)
		जाओ err;

	वापस 0;
err:
	dprपूर्णांकk(FE_ERROR, 1, "I/O error");
	वापस -1;
पूर्ण

अटल पूर्णांक stv090x_set_gpio(काष्ठा dvb_frontend *fe, u8 gpio, u8 dir,
			    u8 value, u8 xor_value)
अणु
	काष्ठा stv090x_state *state = fe->demodulator_priv;
	u8 reg = 0;

	STV090x_SETFIELD(reg, GPIOx_OPD_FIELD, dir);
	STV090x_SETFIELD(reg, GPIOx_CONFIG_FIELD, value);
	STV090x_SETFIELD(reg, GPIOx_XOR_FIELD, xor_value);

	वापस stv090x_ग_लिखो_reg(state, STV090x_GPIOxCFG(gpio), reg);
पूर्ण

अटल पूर्णांक stv090x_setup_compound(काष्ठा stv090x_state *state)
अणु
	काष्ठा stv090x_dev *temp_पूर्णांक;

	temp_पूर्णांक = find_dev(state->i2c,
			    state->config->address);

	अगर (temp_पूर्णांक && state->demod_mode == STV090x_DUAL) अणु
		state->पूर्णांकernal = temp_पूर्णांक->पूर्णांकernal;
		state->पूर्णांकernal->num_used++;
		dprपूर्णांकk(FE_INFO, 1, "Found Internal Structure!");
	पूर्ण अन्यथा अणु
		state->पूर्णांकernal = kदो_स्मृति(माप(*state->पूर्णांकernal), GFP_KERNEL);
		अगर (!state->पूर्णांकernal)
			जाओ error;
		temp_पूर्णांक = append_पूर्णांकernal(state->पूर्णांकernal);
		अगर (!temp_पूर्णांक) अणु
			kमुक्त(state->पूर्णांकernal);
			जाओ error;
		पूर्ण
		state->पूर्णांकernal->num_used = 1;
		state->पूर्णांकernal->mclk = 0;
		state->पूर्णांकernal->dev_ver = 0;
		state->पूर्णांकernal->i2c_adap = state->i2c;
		state->पूर्णांकernal->i2c_addr = state->config->address;
		dprपूर्णांकk(FE_INFO, 1, "Create New Internal Structure!");

		mutex_init(&state->पूर्णांकernal->demod_lock);
		mutex_init(&state->पूर्णांकernal->tuner_lock);

		अगर (stv090x_setup(&state->frontend) < 0) अणु
			dprपूर्णांकk(FE_ERROR, 1, "Error setting up device");
			जाओ err_हटाओ;
		पूर्ण
	पूर्ण

	अगर (state->पूर्णांकernal->dev_ver >= 0x30)
		state->frontend.ops.info.caps |= FE_CAN_MULTISTREAM;

	/* workaround क्रम stuck DiSEqC output */
	अगर (state->config->diseqc_envelope_mode)
		stv090x_send_diseqc_burst(&state->frontend, SEC_MINI_A);

	state->config->set_gpio = stv090x_set_gpio;

	dprपूर्णांकk(FE_ERROR, 1, "Probing %s demodulator(%d) Cut=0x%02x",
		state->device == STV0900 ? "STV0900" : "STV0903",
		state->config->demod,
		state->पूर्णांकernal->dev_ver);

	वापस 0;

error:
	वापस -ENOMEM;
err_हटाओ:
	हटाओ_dev(state->पूर्णांकernal);
	kमुक्त(state->पूर्णांकernal);
	वापस -ENODEV;
पूर्ण

अटल स्थिर काष्ठा dvb_frontend_ops stv090x_ops = अणु
	.delsys = अणु SYS_DVBS, SYS_DVBS2, SYS_DSS पूर्ण,
	.info = अणु
		.name			= "STV090x Multistandard",
		.frequency_min_hz	=  950 * MHz,
		.frequency_max_hz	= 2150 * MHz,
		.symbol_rate_min	= 1000000,
		.symbol_rate_max	= 45000000,
		.caps			= FE_CAN_INVERSION_AUTO |
					  FE_CAN_FEC_AUTO       |
					  FE_CAN_QPSK           |
					  FE_CAN_2G_MODULATION
	पूर्ण,

	.release			= stv090x_release,
	.init				= stv090x_init,

	.sleep				= stv090x_sleep,
	.get_frontend_algo		= stv090x_frontend_algo,

	.diseqc_send_master_cmd		= stv090x_send_diseqc_msg,
	.diseqc_send_burst		= stv090x_send_diseqc_burst,
	.diseqc_recv_slave_reply	= stv090x_recv_slave_reply,
	.set_tone			= stv090x_set_tone,

	.search				= stv090x_search,
	.पढ़ो_status			= stv090x_पढ़ो_status,
	.पढ़ो_ber			= stv090x_पढ़ो_per,
	.पढ़ो_संकेत_strength		= stv090x_पढ़ो_संकेत_strength,
	.पढ़ो_snr			= stv090x_पढ़ो_cnr,
पूर्ण;

अटल काष्ठा dvb_frontend *stv090x_get_dvb_frontend(काष्ठा i2c_client *client)
अणु
	काष्ठा stv090x_state *state = i2c_get_clientdata(client);

	dev_dbg(&client->dev, "\n");

	वापस &state->frontend;
पूर्ण

अटल पूर्णांक stv090x_probe(काष्ठा i2c_client *client,
			 स्थिर काष्ठा i2c_device_id *id)
अणु
	पूर्णांक ret = 0;
	काष्ठा stv090x_config *config = client->dev.platक्रमm_data;

	काष्ठा stv090x_state *state = शून्य;

	state = kzalloc(माप(*state), GFP_KERNEL);
	अगर (!state) अणु
		ret = -ENOMEM;
		जाओ error;
	पूर्ण

	state->verbose				= &verbose;
	state->config				= config;
	state->i2c				= client->adapter;
	state->frontend.ops			= stv090x_ops;
	state->frontend.demodulator_priv	= state;
	state->demod				= config->demod;
						/* Single or Dual mode */
	state->demod_mode			= config->demod_mode;
	state->device				= config->device;
						/* शेष */
	state->rolloff				= STV090x_RO_35;

	ret = stv090x_setup_compound(state);
	अगर (ret)
		जाओ error;

	i2c_set_clientdata(client, state);

	/* setup callbacks */
	config->get_dvb_frontend = stv090x_get_dvb_frontend;

	वापस 0;

error:
	kमुक्त(state);
	वापस ret;
पूर्ण

अटल पूर्णांक stv090x_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा stv090x_state *state = i2c_get_clientdata(client);

	stv090x_release(&state->frontend);
	वापस 0;
पूर्ण

काष्ठा dvb_frontend *stv090x_attach(काष्ठा stv090x_config *config,
				    काष्ठा i2c_adapter *i2c,
				    क्रमागत stv090x_demodulator demod)
अणु
	पूर्णांक ret = 0;
	काष्ठा stv090x_state *state = शून्य;

	state = kzalloc(माप(*state), GFP_KERNEL);
	अगर (!state)
		जाओ error;

	state->verbose				= &verbose;
	state->config				= config;
	state->i2c				= i2c;
	state->frontend.ops			= stv090x_ops;
	state->frontend.demodulator_priv	= state;
	state->demod				= demod;
						/* Single or Dual mode */
	state->demod_mode			= config->demod_mode;
	state->device				= config->device;
						/* शेष */
	state->rolloff				= STV090x_RO_35;

	ret = stv090x_setup_compound(state);
	अगर (ret)
		जाओ error;

	वापस &state->frontend;

error:
	kमुक्त(state);
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(stv090x_attach);

अटल स्थिर काष्ठा i2c_device_id stv090x_id_table[] = अणु
	अणु"stv090x", 0पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, stv090x_id_table);

अटल काष्ठा i2c_driver stv090x_driver = अणु
	.driver = अणु
		.name	= "stv090x",
		.suppress_bind_attrs = true,
	पूर्ण,
	.probe		= stv090x_probe,
	.हटाओ		= stv090x_हटाओ,
	.id_table	= stv090x_id_table,
पूर्ण;

module_i2c_driver(stv090x_driver);

MODULE_PARM_DESC(verbose, "Set Verbosity level");
MODULE_AUTHOR("Manu Abraham");
MODULE_DESCRIPTION("STV090x Multi-Std Broadcast frontend");
MODULE_LICENSE("GPL");
