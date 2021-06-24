<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/* z0194a.h Sharp z0194a tuner support
*
* Copyright (C) 2008 Igor M. Liplianin (liplianin@me.by)
*
* see Documentation/driver-api/media/drivers/dvb-usb.rst क्रम more inक्रमmation
*/

#अगर_अघोषित Z0194A
#घोषणा Z0194A

अटल पूर्णांक sharp_z0194a_set_symbol_rate(काष्ठा dvb_frontend *fe,
					 u32 srate, u32 ratio)
अणु
	u8 aclk = 0;
	u8 bclk = 0;

	अगर (srate < 1500000) अणु
		aclk = 0xb7; bclk = 0x47; पूर्ण
	अन्यथा अगर (srate < 3000000) अणु
		aclk = 0xb7; bclk = 0x4b; पूर्ण
	अन्यथा अगर (srate < 7000000) अणु
		aclk = 0xb7; bclk = 0x4f; पूर्ण
	अन्यथा अगर (srate < 14000000) अणु
		aclk = 0xb7; bclk = 0x53; पूर्ण
	अन्यथा अगर (srate < 30000000) अणु
		aclk = 0xb6; bclk = 0x53; पूर्ण
	अन्यथा अगर (srate < 45000000) अणु
		aclk = 0xb4; bclk = 0x51; पूर्ण

	stv0299_ग_लिखोreg(fe, 0x13, aclk);
	stv0299_ग_लिखोreg(fe, 0x14, bclk);
	stv0299_ग_लिखोreg(fe, 0x1f, (ratio >> 16) & 0xff);
	stv0299_ग_लिखोreg(fe, 0x20, (ratio >> 8) & 0xff);
	stv0299_ग_लिखोreg(fe, 0x21, (ratio) & 0xf0);

	वापस 0;
पूर्ण

अटल u8 sharp_z0194a_inittab[] = अणु
	0x01, 0x15,
	0x02, 0x30,
	0x03, 0x00,
	0x04, 0x7d,   /* F22FR = 0x7d, F22 = f_VCO / 128 / 0x7d = 22 kHz */
	0x05, 0x35,   /* I2CT = 0, SCLT = 1, SDAT = 1 */
	0x06, 0x40,   /* DAC not used, set to high impendance mode */
	0x07, 0x00,   /* DAC LSB */
	0x08, 0x40,   /* DiSEqC off, LNB घातer on OP2/LOCK pin on */
	0x09, 0x00,   /* FIFO */
	0x0c, 0x51,   /* OP1 ctl = Normal, OP1 val = 1 (LNB Power ON) */
	0x0d, 0x82,   /* DC offset compensation = ON, beta_agc1 = 2 */
	0x0e, 0x23,   /* alpha_पंचांगg = 2, beta_पंचांगg = 3 */
	0x10, 0x3f,   /* AGC2  0x3d */
	0x11, 0x84,
	0x12, 0xb9,
	0x15, 0xc9,   /* lock detector threshold */
	0x16, 0x00,
	0x17, 0x00,
	0x18, 0x00,
	0x19, 0x00,
	0x1a, 0x00,
	0x1f, 0x50,
	0x20, 0x00,
	0x21, 0x00,
	0x22, 0x00,
	0x23, 0x00,
	0x28, 0x00,  /* out imp: normal  out type: parallel FEC mode:0 */
	0x29, 0x1e,  /* 1/2 threshold */
	0x2a, 0x14,  /* 2/3 threshold */
	0x2b, 0x0f,  /* 3/4 threshold */
	0x2c, 0x09,  /* 5/6 threshold */
	0x2d, 0x05,  /* 7/8 threshold */
	0x2e, 0x01,
	0x31, 0x1f,  /* test all FECs */
	0x32, 0x19,  /* viterbi and synchro search */
	0x33, 0xfc,  /* rs control */
	0x34, 0x93,  /* error control */
	0x0f, 0x52,
	0xff, 0xff
पूर्ण;

#पूर्ण_अगर
