<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Driver क्रम the ST STV0910 DVB-S/S2 demodulator.
 *
 * Copyright (C) 2014-2015 Ralph Metzler <rjkm@metzlerbros.de>
 *                         Marcus Metzler <mocm@metzlerbros.de>
 *                         developed क्रम Digital Devices GmbH
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License
 * version 2 only, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/firmware.h>
#समावेश <linux/i2c.h>
#समावेश <यंत्र/भाग64.h>

#समावेश <media/dvb_frontend.h>
#समावेश "stv0910.h"
#समावेश "stv0910_regs.h"

#घोषणा EXT_CLOCK    30000000
#घोषणा TUNING_DELAY 200
#घोषणा BER_SRC_S    0x20
#घोषणा BER_SRC_S2   0x20

अटल LIST_HEAD(stvlist);

क्रमागत receive_mode अणु RCVMODE_NONE, RCVMODE_DVBS, RCVMODE_DVBS2, RCVMODE_AUTO पूर्ण;

क्रमागत dvbs2_fectype अणु DVBS2_64K, DVBS2_16K पूर्ण;

क्रमागत dvbs2_mod_cod अणु
	DVBS2_DUMMY_PLF, DVBS2_QPSK_1_4, DVBS2_QPSK_1_3, DVBS2_QPSK_2_5,
	DVBS2_QPSK_1_2, DVBS2_QPSK_3_5, DVBS2_QPSK_2_3,	DVBS2_QPSK_3_4,
	DVBS2_QPSK_4_5,	DVBS2_QPSK_5_6,	DVBS2_QPSK_8_9,	DVBS2_QPSK_9_10,
	DVBS2_8PSK_3_5,	DVBS2_8PSK_2_3,	DVBS2_8PSK_3_4,	DVBS2_8PSK_5_6,
	DVBS2_8PSK_8_9,	DVBS2_8PSK_9_10, DVBS2_16APSK_2_3, DVBS2_16APSK_3_4,
	DVBS2_16APSK_4_5, DVBS2_16APSK_5_6, DVBS2_16APSK_8_9, DVBS2_16APSK_9_10,
	DVBS2_32APSK_3_4, DVBS2_32APSK_4_5, DVBS2_32APSK_5_6, DVBS2_32APSK_8_9,
	DVBS2_32APSK_9_10
पूर्ण;

क्रमागत fe_stv0910_mod_cod अणु
	FE_DUMMY_PLF, FE_QPSK_14, FE_QPSK_13, FE_QPSK_25,
	FE_QPSK_12, FE_QPSK_35, FE_QPSK_23, FE_QPSK_34,
	FE_QPSK_45, FE_QPSK_56, FE_QPSK_89, FE_QPSK_910,
	FE_8PSK_35, FE_8PSK_23, FE_8PSK_34, FE_8PSK_56,
	FE_8PSK_89, FE_8PSK_910, FE_16APSK_23, FE_16APSK_34,
	FE_16APSK_45, FE_16APSK_56, FE_16APSK_89, FE_16APSK_910,
	FE_32APSK_34, FE_32APSK_45, FE_32APSK_56, FE_32APSK_89,
	FE_32APSK_910
पूर्ण;

क्रमागत fe_stv0910_roll_off अणु FE_SAT_35, FE_SAT_25, FE_SAT_20, FE_SAT_15 पूर्ण;

अटल अंतरभूत u32 muद_भाग32(u32 a, u32 b, u32 c)
अणु
	u64 पंचांगp64;

	पंचांगp64 = (u64)a * (u64)b;
	करो_भाग(पंचांगp64, c);

	वापस (u32)पंचांगp64;
पूर्ण

काष्ठा stv_base अणु
	काष्ठा list_head     stvlist;

	u8                   adr;
	काष्ठा i2c_adapter  *i2c;
	काष्ठा mutex         i2c_lock; /* shared I2C access protect */
	काष्ठा mutex         reg_lock; /* shared रेजिस्टर ग_लिखो protect */
	पूर्णांक                  count;

	u32                  extclk;
	u32                  mclk;
पूर्ण;

काष्ठा stv अणु
	काष्ठा stv_base     *base;
	काष्ठा dvb_frontend  fe;
	पूर्णांक                  nr;
	u16                  regoff;
	u8                   i2crpt;
	u8                   tscfgh;
	u8                   tsgeneral;
	u8                   tsspeed;
	u8                   single;
	अचिन्हित दीर्घ        tune_समय;

	s32                  search_range;
	u32                  started;
	u32                  demod_lock_समय;
	क्रमागत receive_mode    receive_mode;
	u32                  demod_समयout;
	u32                  fec_समयout;
	u32                  first_समय_lock;
	u8                   demod_bits;
	u32                  symbol_rate;

	u8                       last_viterbi_rate;
	क्रमागत fe_code_rate        puncture_rate;
	क्रमागत fe_stv0910_mod_cod  mod_cod;
	क्रमागत dvbs2_fectype       fectype;
	u32                      pilots;
	क्रमागत fe_stv0910_roll_off feroll_off;

	पूर्णांक   is_standard_broadcast;
	पूर्णांक   is_vcm;

	u32   cur_scrambling_code;

	u32   last_bernumerator;
	u32   last_berdenominator;
	u8    berscale;

	u8    vth[6];
पूर्ण;

काष्ठा sinit_table अणु
	u16  address;
	u8   data;
पूर्ण;

काष्ठा slookup अणु
	s16  value;
	u32  reg_value;
पूर्ण;

अटल पूर्णांक ग_लिखो_reg(काष्ठा stv *state, u16 reg, u8 val)
अणु
	काष्ठा i2c_adapter *adap = state->base->i2c;
	u8 data[3] = अणुreg >> 8, reg & 0xff, valपूर्ण;
	काष्ठा i2c_msg msg = अणु.addr = state->base->adr, .flags = 0,
			      .buf = data, .len = 3पूर्ण;

	अगर (i2c_transfer(adap, &msg, 1) != 1) अणु
		dev_warn(&adap->dev, "i2c write error ([%02x] %04x: %02x)\n",
			 state->base->adr, reg, val);
		वापस -EIO;
	पूर्ण
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक i2c_पढ़ो_regs16(काष्ठा i2c_adapter *adapter, u8 adr,
				  u16 reg, u8 *val, पूर्णांक count)
अणु
	u8 msg[2] = अणुreg >> 8, reg & 0xffपूर्ण;
	काष्ठा i2c_msg msgs[2] = अणुअणु.addr = adr, .flags = 0,
				   .buf  = msg, .len   = 2पूर्ण,
				  अणु.addr = adr, .flags = I2C_M_RD,
				   .buf  = val, .len   = count पूर्ण पूर्ण;

	अगर (i2c_transfer(adapter, msgs, 2) != 2) अणु
		dev_warn(&adapter->dev, "i2c read error ([%02x] %04x)\n",
			 adr, reg);
		वापस -EIO;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक पढ़ो_reg(काष्ठा stv *state, u16 reg, u8 *val)
अणु
	वापस i2c_पढ़ो_regs16(state->base->i2c, state->base->adr,
			       reg, val, 1);
पूर्ण

अटल पूर्णांक पढ़ो_regs(काष्ठा stv *state, u16 reg, u8 *val, पूर्णांक len)
अणु
	वापस i2c_पढ़ो_regs16(state->base->i2c, state->base->adr,
			       reg, val, len);
पूर्ण

अटल पूर्णांक ग_लिखो_shared_reg(काष्ठा stv *state, u16 reg, u8 mask, u8 val)
अणु
	पूर्णांक status;
	u8 पंचांगp;

	mutex_lock(&state->base->reg_lock);
	status = पढ़ो_reg(state, reg, &पंचांगp);
	अगर (!status)
		status = ग_लिखो_reg(state, reg, (पंचांगp & ~mask) | (val & mask));
	mutex_unlock(&state->base->reg_lock);
	वापस status;
पूर्ण

अटल पूर्णांक ग_लिखो_field(काष्ठा stv *state, u32 field, u8 val)
अणु
	पूर्णांक status;
	u8 shअगरt, mask, old, new;

	status = पढ़ो_reg(state, field >> 16, &old);
	अगर (status)
		वापस status;
	mask = field & 0xff;
	shअगरt = (field >> 12) & 0xf;
	new = ((val << shअगरt) & mask) | (old & ~mask);
	अगर (new == old)
		वापस 0;
	वापस ग_लिखो_reg(state, field >> 16, new);
पूर्ण

#घोषणा SET_FIELD(_reg, _val)					\
	ग_लिखो_field(state, state->nr ? FSTV0910_P2_##_reg :	\
		    FSTV0910_P1_##_reg, _val)

#घोषणा SET_REG(_reg, _val)					\
	ग_लिखो_reg(state, state->nr ? RSTV0910_P2_##_reg :	\
		  RSTV0910_P1_##_reg, _val)

#घोषणा GET_REG(_reg, _val)					\
	पढ़ो_reg(state, state->nr ? RSTV0910_P2_##_reg :	\
		 RSTV0910_P1_##_reg, _val)

अटल स्थिर काष्ठा slookup s1_sn_lookup[] = अणु
	अणु   0,    9242  पूर्ण, /* C/N=   0dB */
	अणु   5,    9105  पूर्ण, /* C/N= 0.5dB */
	अणु  10,    8950  पूर्ण, /* C/N= 1.0dB */
	अणु  15,    8780  पूर्ण, /* C/N= 1.5dB */
	अणु  20,    8566  पूर्ण, /* C/N= 2.0dB */
	अणु  25,    8366  पूर्ण, /* C/N= 2.5dB */
	अणु  30,    8146  पूर्ण, /* C/N= 3.0dB */
	अणु  35,    7908  पूर्ण, /* C/N= 3.5dB */
	अणु  40,    7666  पूर्ण, /* C/N= 4.0dB */
	अणु  45,    7405  पूर्ण, /* C/N= 4.5dB */
	अणु  50,    7136  पूर्ण, /* C/N= 5.0dB */
	अणु  55,    6861  पूर्ण, /* C/N= 5.5dB */
	अणु  60,    6576  पूर्ण, /* C/N= 6.0dB */
	अणु  65,    6330  पूर्ण, /* C/N= 6.5dB */
	अणु  70,    6048  पूर्ण, /* C/N= 7.0dB */
	अणु  75,    5768  पूर्ण, /* C/N= 7.5dB */
	अणु  80,    5492  पूर्ण, /* C/N= 8.0dB */
	अणु  85,    5224  पूर्ण, /* C/N= 8.5dB */
	अणु  90,    4959  पूर्ण, /* C/N= 9.0dB */
	अणु  95,    4709  पूर्ण, /* C/N= 9.5dB */
	अणु  100,   4467  पूर्ण, /* C/N=10.0dB */
	अणु  105,   4236  पूर्ण, /* C/N=10.5dB */
	अणु  110,   4013  पूर्ण, /* C/N=11.0dB */
	अणु  115,   3800  पूर्ण, /* C/N=11.5dB */
	अणु  120,   3598  पूर्ण, /* C/N=12.0dB */
	अणु  125,   3406  पूर्ण, /* C/N=12.5dB */
	अणु  130,   3225  पूर्ण, /* C/N=13.0dB */
	अणु  135,   3052  पूर्ण, /* C/N=13.5dB */
	अणु  140,   2889  पूर्ण, /* C/N=14.0dB */
	अणु  145,   2733  पूर्ण, /* C/N=14.5dB */
	अणु  150,   2587  पूर्ण, /* C/N=15.0dB */
	अणु  160,   2318  पूर्ण, /* C/N=16.0dB */
	अणु  170,   2077  पूर्ण, /* C/N=17.0dB */
	अणु  180,   1862  पूर्ण, /* C/N=18.0dB */
	अणु  190,   1670  पूर्ण, /* C/N=19.0dB */
	अणु  200,   1499  पूर्ण, /* C/N=20.0dB */
	अणु  210,   1347  पूर्ण, /* C/N=21.0dB */
	अणु  220,   1213  पूर्ण, /* C/N=22.0dB */
	अणु  230,   1095  पूर्ण, /* C/N=23.0dB */
	अणु  240,    992  पूर्ण, /* C/N=24.0dB */
	अणु  250,    900  पूर्ण, /* C/N=25.0dB */
	अणु  260,    826  पूर्ण, /* C/N=26.0dB */
	अणु  270,    758  पूर्ण, /* C/N=27.0dB */
	अणु  280,    702  पूर्ण, /* C/N=28.0dB */
	अणु  290,    653  पूर्ण, /* C/N=29.0dB */
	अणु  300,    613  पूर्ण, /* C/N=30.0dB */
	अणु  310,    579  पूर्ण, /* C/N=31.0dB */
	अणु  320,    550  पूर्ण, /* C/N=32.0dB */
	अणु  330,    526  पूर्ण, /* C/N=33.0dB */
	अणु  350,    490  पूर्ण, /* C/N=33.0dB */
	अणु  400,    445  पूर्ण, /* C/N=40.0dB */
	अणु  450,    430  पूर्ण, /* C/N=45.0dB */
	अणु  500,    426  पूर्ण, /* C/N=50.0dB */
	अणु  510,    425  पूर्ण  /* C/N=51.0dB */
पूर्ण;

अटल स्थिर काष्ठा slookup s2_sn_lookup[] = अणु
	अणु  -30,  13950  पूर्ण, /* C/N=-2.5dB */
	अणु  -25,  13580  पूर्ण, /* C/N=-2.5dB */
	अणु  -20,  13150  पूर्ण, /* C/N=-2.0dB */
	अणु  -15,  12760  पूर्ण, /* C/N=-1.5dB */
	अणु  -10,  12345  पूर्ण, /* C/N=-1.0dB */
	अणु   -5,  11900  पूर्ण, /* C/N=-0.5dB */
	अणु    0,  11520  पूर्ण, /* C/N=   0dB */
	अणु    5,  11080  पूर्ण, /* C/N= 0.5dB */
	अणु   10,  10630  पूर्ण, /* C/N= 1.0dB */
	अणु   15,  10210  पूर्ण, /* C/N= 1.5dB */
	अणु   20,   9790  पूर्ण, /* C/N= 2.0dB */
	अणु   25,   9390  पूर्ण, /* C/N= 2.5dB */
	अणु   30,   8970  पूर्ण, /* C/N= 3.0dB */
	अणु   35,   8575  पूर्ण, /* C/N= 3.5dB */
	अणु   40,   8180  पूर्ण, /* C/N= 4.0dB */
	अणु   45,   7800  पूर्ण, /* C/N= 4.5dB */
	अणु   50,   7430  पूर्ण, /* C/N= 5.0dB */
	अणु   55,   7080  पूर्ण, /* C/N= 5.5dB */
	अणु   60,   6720  पूर्ण, /* C/N= 6.0dB */
	अणु   65,   6320  पूर्ण, /* C/N= 6.5dB */
	अणु   70,   6060  पूर्ण, /* C/N= 7.0dB */
	अणु   75,   5760  पूर्ण, /* C/N= 7.5dB */
	अणु   80,   5480  पूर्ण, /* C/N= 8.0dB */
	अणु   85,   5200  पूर्ण, /* C/N= 8.5dB */
	अणु   90,   4930  पूर्ण, /* C/N= 9.0dB */
	अणु   95,   4680  पूर्ण, /* C/N= 9.5dB */
	अणु  100,   4425  पूर्ण, /* C/N=10.0dB */
	अणु  105,   4210  पूर्ण, /* C/N=10.5dB */
	अणु  110,   3980  पूर्ण, /* C/N=11.0dB */
	अणु  115,   3765  पूर्ण, /* C/N=11.5dB */
	अणु  120,   3570  पूर्ण, /* C/N=12.0dB */
	अणु  125,   3315  पूर्ण, /* C/N=12.5dB */
	अणु  130,   3140  पूर्ण, /* C/N=13.0dB */
	अणु  135,   2980  पूर्ण, /* C/N=13.5dB */
	अणु  140,   2820  पूर्ण, /* C/N=14.0dB */
	अणु  145,   2670  पूर्ण, /* C/N=14.5dB */
	अणु  150,   2535  पूर्ण, /* C/N=15.0dB */
	अणु  160,   2270  पूर्ण, /* C/N=16.0dB */
	अणु  170,   2035  पूर्ण, /* C/N=17.0dB */
	अणु  180,   1825  पूर्ण, /* C/N=18.0dB */
	अणु  190,   1650  पूर्ण, /* C/N=19.0dB */
	अणु  200,   1485  पूर्ण, /* C/N=20.0dB */
	अणु  210,   1340  पूर्ण, /* C/N=21.0dB */
	अणु  220,   1212  पूर्ण, /* C/N=22.0dB */
	अणु  230,   1100  पूर्ण, /* C/N=23.0dB */
	अणु  240,   1000  पूर्ण, /* C/N=24.0dB */
	अणु  250,    910  पूर्ण, /* C/N=25.0dB */
	अणु  260,    836  पूर्ण, /* C/N=26.0dB */
	अणु  270,    772  पूर्ण, /* C/N=27.0dB */
	अणु  280,    718  पूर्ण, /* C/N=28.0dB */
	अणु  290,    671  पूर्ण, /* C/N=29.0dB */
	अणु  300,    635  पूर्ण, /* C/N=30.0dB */
	अणु  310,    602  पूर्ण, /* C/N=31.0dB */
	अणु  320,    575  पूर्ण, /* C/N=32.0dB */
	अणु  330,    550  पूर्ण, /* C/N=33.0dB */
	अणु  350,    517  पूर्ण, /* C/N=35.0dB */
	अणु  400,    480  पूर्ण, /* C/N=40.0dB */
	अणु  450,    466  पूर्ण, /* C/N=45.0dB */
	अणु  500,    464  पूर्ण, /* C/N=50.0dB */
	अणु  510,    463  पूर्ण, /* C/N=51.0dB */
पूर्ण;

अटल स्थिर काष्ठा slookup padc_lookup[] = अणु
	अणु    0,  118000 पूर्ण, /* PADC= +0dBm */
	अणु -100,  93600  पूर्ण, /* PADC= -1dBm */
	अणु -200,  74500  पूर्ण, /* PADC= -2dBm */
	अणु -300,  59100  पूर्ण, /* PADC= -3dBm */
	अणु -400,  47000  पूर्ण, /* PADC= -4dBm */
	अणु -500,  37300  पूर्ण, /* PADC= -5dBm */
	अणु -600,  29650  पूर्ण, /* PADC= -6dBm */
	अणु -700,  23520  पूर्ण, /* PADC= -7dBm */
	अणु -900,  14850  पूर्ण, /* PADC= -9dBm */
	अणु -1100, 9380   पूर्ण, /* PADC=-11dBm */
	अणु -1300, 5910   पूर्ण, /* PADC=-13dBm */
	अणु -1500, 3730   पूर्ण, /* PADC=-15dBm */
	अणु -1700, 2354   पूर्ण, /* PADC=-17dBm */
	अणु -1900, 1485   पूर्ण, /* PADC=-19dBm */
	अणु -2000, 1179   पूर्ण, /* PADC=-20dBm */
	अणु -2100, 1000   पूर्ण, /* PADC=-21dBm */
पूर्ण;

/*********************************************************************
 * Tracking carrier loop carrier QPSK 1/4 to 8PSK 9/10 दीर्घ Frame
 *********************************************************************/
अटल स्थिर u8 s2car_loop[] =	अणु
	/*
	 * Modcod  2MPon 2MPoff 5MPon 5MPoff 10MPon 10MPoff
	 * 20MPon 20MPoff 30MPon 30MPoff
	 */

	/* FE_QPSK_14  */
	0x0C,  0x3C,  0x0B,  0x3C,  0x2A,  0x2C,  0x2A,  0x1C,  0x3A,  0x3B,
	/* FE_QPSK_13  */
	0x0C,  0x3C,  0x0B,  0x3C,  0x2A,  0x2C,  0x3A,  0x0C,  0x3A,  0x2B,
	/* FE_QPSK_25  */
	0x1C,  0x3C,  0x1B,  0x3C,  0x3A,  0x1C,  0x3A,  0x3B,  0x3A,  0x2B,
	/* FE_QPSK_12  */
	0x0C,  0x1C,  0x2B,  0x1C,  0x0B,  0x2C,  0x0B,  0x0C,  0x2A,  0x2B,
	/* FE_QPSK_35  */
	0x1C,  0x1C,  0x2B,  0x1C,  0x0B,  0x2C,  0x0B,  0x0C,  0x2A,  0x2B,
	/* FE_QPSK_23  */
	0x2C,  0x2C,  0x2B,  0x1C,  0x0B,  0x2C,  0x0B,  0x0C,  0x2A,  0x2B,
	/* FE_QPSK_34  */
	0x3C,  0x2C,  0x3B,  0x2C,  0x1B,  0x1C,  0x1B,  0x3B,  0x3A,  0x1B,
	/* FE_QPSK_45  */
	0x0D,  0x3C,  0x3B,  0x2C,  0x1B,  0x1C,  0x1B,  0x3B,  0x3A,  0x1B,
	/* FE_QPSK_56  */
	0x1D,  0x3C,  0x0C,  0x2C,  0x2B,  0x1C,  0x1B,  0x3B,  0x0B,  0x1B,
	/* FE_QPSK_89  */
	0x3D,  0x0D,  0x0C,  0x2C,  0x2B,  0x0C,  0x2B,  0x2B,  0x0B,  0x0B,
	/* FE_QPSK_910 */
	0x1E,  0x0D,  0x1C,  0x2C,  0x3B,  0x0C,  0x2B,  0x2B,  0x1B,  0x0B,
	/* FE_8PSK_35  */
	0x28,  0x09,  0x28,  0x09,  0x28,  0x09,  0x28,  0x08,  0x28,  0x27,
	/* FE_8PSK_23  */
	0x19,  0x29,  0x19,  0x29,  0x19,  0x29,  0x38,  0x19,  0x28,  0x09,
	/* FE_8PSK_34  */
	0x1A,  0x0B,  0x1A,  0x3A,  0x0A,  0x2A,  0x39,  0x2A,  0x39,  0x1A,
	/* FE_8PSK_56  */
	0x2B,  0x2B,  0x1B,  0x1B,  0x0B,  0x1B,  0x1A,  0x0B,  0x1A,  0x1A,
	/* FE_8PSK_89  */
	0x0C,  0x0C,  0x3B,  0x3B,  0x1B,  0x1B,  0x2A,  0x0B,  0x2A,  0x2A,
	/* FE_8PSK_910 */
	0x0C,  0x1C,  0x0C,  0x3B,  0x2B,  0x1B,  0x3A,  0x0B,  0x2A,  0x2A,

	/**********************************************************************
	 * Tracking carrier loop carrier 16APSK 2/3 to 32APSK 9/10 दीर्घ Frame
	 **********************************************************************/

	/*
	 * Modcod 2MPon  2MPoff 5MPon 5MPoff 10MPon 10MPoff 20MPon
	 * 20MPoff 30MPon 30MPoff
	 */

	/* FE_16APSK_23  */
	0x0A,  0x0A,  0x0A,  0x0A,  0x1A,  0x0A,  0x39,  0x0A,  0x29,  0x0A,
	/* FE_16APSK_34  */
	0x0A,  0x0A,  0x0A,  0x0A,  0x0B,  0x0A,  0x2A,  0x0A,  0x1A,  0x0A,
	/* FE_16APSK_45  */
	0x0A,  0x0A,  0x0A,  0x0A,  0x1B,  0x0A,  0x3A,  0x0A,  0x2A,  0x0A,
	/* FE_16APSK_56  */
	0x0A,  0x0A,  0x0A,  0x0A,  0x1B,  0x0A,  0x3A,  0x0A,  0x2A,  0x0A,
	/* FE_16APSK_89  */
	0x0A,  0x0A,  0x0A,  0x0A,  0x2B,  0x0A,  0x0B,  0x0A,  0x3A,  0x0A,
	/* FE_16APSK_910 */
	0x0A,  0x0A,  0x0A,  0x0A,  0x2B,  0x0A,  0x0B,  0x0A,  0x3A,  0x0A,
	/* FE_32APSK_34  */
	0x09,  0x09,  0x09,  0x09,  0x09,  0x09,  0x09,  0x09,  0x09,  0x09,
	/* FE_32APSK_45  */
	0x09,  0x09,  0x09,  0x09,  0x09,  0x09,  0x09,  0x09,  0x09,  0x09,
	/* FE_32APSK_56  */
	0x09,  0x09,  0x09,  0x09,  0x09,  0x09,  0x09,  0x09,  0x09,  0x09,
	/* FE_32APSK_89  */
	0x09,  0x09,  0x09,  0x09,  0x09,  0x09,  0x09,  0x09,  0x09,  0x09,
	/* FE_32APSK_910 */
	0x09,  0x09,  0x09,  0x09,  0x09,  0x09,  0x09,  0x09,  0x09,  0x09,
पूर्ण;

अटल u8 get_optim_cloop(काष्ठा stv *state,
			  क्रमागत fe_stv0910_mod_cod mod_cod, u32 pilots)
अणु
	पूर्णांक i = 0;

	अगर (mod_cod >= FE_32APSK_910)
		i = ((पूर्णांक)FE_32APSK_910 - (पूर्णांक)FE_QPSK_14) * 10;
	अन्यथा अगर (mod_cod >= FE_QPSK_14)
		i = ((पूर्णांक)mod_cod - (पूर्णांक)FE_QPSK_14) * 10;

	अगर (state->symbol_rate <= 3000000)
		i += 0;
	अन्यथा अगर (state->symbol_rate <=  7000000)
		i += 2;
	अन्यथा अगर (state->symbol_rate <= 15000000)
		i += 4;
	अन्यथा अगर (state->symbol_rate <= 25000000)
		i += 6;
	अन्यथा
		i += 8;

	अगर (!pilots)
		i += 1;

	वापस s2car_loop[i];
पूर्ण

अटल पूर्णांक get_cur_symbol_rate(काष्ठा stv *state, u32 *p_symbol_rate)
अणु
	पूर्णांक status = 0;
	u8 symb_freq0;
	u8 symb_freq1;
	u8 symb_freq2;
	u8 symb_freq3;
	u8 tim_offs0;
	u8 tim_offs1;
	u8 tim_offs2;
	u32 symbol_rate;
	s32 timing_offset;

	*p_symbol_rate = 0;
	अगर (!state->started)
		वापस status;

	पढ़ो_reg(state, RSTV0910_P2_SFR3 + state->regoff, &symb_freq3);
	पढ़ो_reg(state, RSTV0910_P2_SFR2 + state->regoff, &symb_freq2);
	पढ़ो_reg(state, RSTV0910_P2_SFR1 + state->regoff, &symb_freq1);
	पढ़ो_reg(state, RSTV0910_P2_SFR0 + state->regoff, &symb_freq0);
	पढ़ो_reg(state, RSTV0910_P2_TMGREG2 + state->regoff, &tim_offs2);
	पढ़ो_reg(state, RSTV0910_P2_TMGREG1 + state->regoff, &tim_offs1);
	पढ़ो_reg(state, RSTV0910_P2_TMGREG0 + state->regoff, &tim_offs0);

	symbol_rate = ((u32)symb_freq3 << 24) | ((u32)symb_freq2 << 16) |
		((u32)symb_freq1 << 8) | (u32)symb_freq0;
	timing_offset = ((u32)tim_offs2 << 16) | ((u32)tim_offs1 << 8) |
		(u32)tim_offs0;

	अगर ((timing_offset & (1 << 23)) != 0)
		timing_offset |= 0xFF000000; /* Sign extent */

	symbol_rate = (u32)(((u64)symbol_rate * state->base->mclk) >> 32);
	timing_offset = (s32)(((s64)symbol_rate * (s64)timing_offset) >> 29);

	*p_symbol_rate = symbol_rate + timing_offset;

	वापस 0;
पूर्ण

अटल पूर्णांक get_संकेत_parameters(काष्ठा stv *state)
अणु
	u8 पंचांगp;

	अगर (!state->started)
		वापस -EINVAL;

	अगर (state->receive_mode == RCVMODE_DVBS2) अणु
		पढ़ो_reg(state, RSTV0910_P2_DMDMODCOD + state->regoff, &पंचांगp);
		state->mod_cod = (क्रमागत fe_stv0910_mod_cod)((पंचांगp & 0x7c) >> 2);
		state->pilots = (पंचांगp & 0x01) != 0;
		state->fectype = (क्रमागत dvbs2_fectype)((पंचांगp & 0x02) >> 1);

	पूर्ण अन्यथा अगर (state->receive_mode == RCVMODE_DVBS) अणु
		पढ़ो_reg(state, RSTV0910_P2_VITCURPUN + state->regoff, &पंचांगp);
		state->puncture_rate = FEC_NONE;
		चयन (पंचांगp & 0x1F) अणु
		हाल 0x0d:
			state->puncture_rate = FEC_1_2;
			अवरोध;
		हाल 0x12:
			state->puncture_rate = FEC_2_3;
			अवरोध;
		हाल 0x15:
			state->puncture_rate = FEC_3_4;
			अवरोध;
		हाल 0x18:
			state->puncture_rate = FEC_5_6;
			अवरोध;
		हाल 0x1a:
			state->puncture_rate = FEC_7_8;
			अवरोध;
		पूर्ण
		state->is_vcm = 0;
		state->is_standard_broadcast = 1;
		state->feroll_off = FE_SAT_35;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक tracking_optimization(काष्ठा stv *state)
अणु
	u8 पंचांगp;

	पढ़ो_reg(state, RSTV0910_P2_DMDCFGMD + state->regoff, &पंचांगp);
	पंचांगp &= ~0xC0;

	चयन (state->receive_mode) अणु
	हाल RCVMODE_DVBS:
		पंचांगp |= 0x40;
		अवरोध;
	हाल RCVMODE_DVBS2:
		पंचांगp |= 0x80;
		अवरोध;
	शेष:
		पंचांगp |= 0xC0;
		अवरोध;
	पूर्ण
	ग_लिखो_reg(state, RSTV0910_P2_DMDCFGMD + state->regoff, पंचांगp);

	अगर (state->receive_mode == RCVMODE_DVBS2) अणु
		/* Disable Reed-Solomon */
		ग_लिखो_shared_reg(state,
				 RSTV0910_TSTTSRS, state->nr ? 0x02 : 0x01,
				 0x03);

		अगर (state->fectype == DVBS2_64K) अणु
			u8 aclc = get_optim_cloop(state, state->mod_cod,
						  state->pilots);

			अगर (state->mod_cod <= FE_QPSK_910) अणु
				ग_लिखो_reg(state, RSTV0910_P2_ACLC2S2Q +
					  state->regoff, aclc);
			पूर्ण अन्यथा अगर (state->mod_cod <= FE_8PSK_910) अणु
				ग_लिखो_reg(state, RSTV0910_P2_ACLC2S2Q +
					  state->regoff, 0x2a);
				ग_लिखो_reg(state, RSTV0910_P2_ACLC2S28 +
					  state->regoff, aclc);
			पूर्ण अन्यथा अगर (state->mod_cod <= FE_16APSK_910) अणु
				ग_लिखो_reg(state, RSTV0910_P2_ACLC2S2Q +
					  state->regoff, 0x2a);
				ग_लिखो_reg(state, RSTV0910_P2_ACLC2S216A +
					  state->regoff, aclc);
			पूर्ण अन्यथा अगर (state->mod_cod <= FE_32APSK_910) अणु
				ग_लिखो_reg(state, RSTV0910_P2_ACLC2S2Q +
					  state->regoff, 0x2a);
				ग_लिखो_reg(state, RSTV0910_P2_ACLC2S232A +
					  state->regoff, aclc);
			पूर्ण
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल s32 table_lookup(स्थिर काष्ठा slookup *table,
			पूर्णांक table_size, u32 reg_value)
अणु
	s32 value;
	पूर्णांक imin = 0;
	पूर्णांक imax = table_size - 1;
	पूर्णांक i;
	s32 reg_dअगरf;

	/* Assumes Table[0].RegValue > Table[imax].RegValue */
	अगर (reg_value >= table[0].reg_value) अणु
		value = table[0].value;
	पूर्ण अन्यथा अगर (reg_value <= table[imax].reg_value) अणु
		value = table[imax].value;
	पूर्ण अन्यथा अणु
		जबतक ((imax - imin) > 1) अणु
			i = (imax + imin) / 2;
			अगर ((table[imin].reg_value >= reg_value) &&
			    (reg_value >= table[i].reg_value))
				imax = i;
			अन्यथा
				imin = i;
		पूर्ण

		reg_dअगरf = table[imax].reg_value - table[imin].reg_value;
		value = table[imin].value;
		अगर (reg_dअगरf != 0)
			value += ((s32)(reg_value - table[imin].reg_value) *
				  (s32)(table[imax].value
					- table[imin].value))
					/ (reg_dअगरf);
	पूर्ण

	वापस value;
पूर्ण

अटल पूर्णांक get_संकेत_to_noise(काष्ठा stv *state, s32 *संकेत_to_noise)
अणु
	u8 data0;
	u8 data1;
	u16 data;
	पूर्णांक n_lookup;
	स्थिर काष्ठा slookup *lookup;

	*संकेत_to_noise = 0;

	अगर (!state->started)
		वापस -EINVAL;

	अगर (state->receive_mode == RCVMODE_DVBS2) अणु
		पढ़ो_reg(state, RSTV0910_P2_NNOSPLHT1 + state->regoff,
			 &data1);
		पढ़ो_reg(state, RSTV0910_P2_NNOSPLHT0 + state->regoff,
			 &data0);
		n_lookup = ARRAY_SIZE(s2_sn_lookup);
		lookup = s2_sn_lookup;
	पूर्ण अन्यथा अणु
		पढ़ो_reg(state, RSTV0910_P2_NNOSDATAT1 + state->regoff,
			 &data1);
		पढ़ो_reg(state, RSTV0910_P2_NNOSDATAT0 + state->regoff,
			 &data0);
		n_lookup = ARRAY_SIZE(s1_sn_lookup);
		lookup = s1_sn_lookup;
	पूर्ण
	data = (((u16)data1) << 8) | (u16)data0;
	*संकेत_to_noise = table_lookup(lookup, n_lookup, data);
	वापस 0;
पूर्ण

अटल पूर्णांक get_bit_error_rate_s(काष्ठा stv *state, u32 *bernumerator,
				u32 *berdenominator)
अणु
	u8 regs[3];

	पूर्णांक status = पढ़ो_regs(state,
			       RSTV0910_P2_ERRCNT12 + state->regoff,
			       regs, 3);

	अगर (status)
		वापस -EINVAL;

	अगर ((regs[0] & 0x80) == 0) अणु
		state->last_berdenominator = 1ULL << ((state->berscale * 2) +
						     10 + 3);
		state->last_bernumerator = ((u32)(regs[0] & 0x7F) << 16) |
			((u32)regs[1] << 8) | regs[2];
		अगर (state->last_bernumerator < 256 && state->berscale < 6) अणु
			state->berscale += 1;
			status = ग_लिखो_reg(state, RSTV0910_P2_ERRCTRL1 +
					   state->regoff,
					   0x20 | state->berscale);
		पूर्ण अन्यथा अगर (state->last_bernumerator > 1024 &&
			   state->berscale > 2) अणु
			state->berscale -= 1;
			status = ग_लिखो_reg(state, RSTV0910_P2_ERRCTRL1 +
					   state->regoff, 0x20 |
					   state->berscale);
		पूर्ण
	पूर्ण
	*bernumerator = state->last_bernumerator;
	*berdenominator = state->last_berdenominator;
	वापस 0;
पूर्ण

अटल u32 dvbs2_nbch(क्रमागत dvbs2_mod_cod mod_cod, क्रमागत dvbs2_fectype fectype)
अणु
	अटल स्थिर u32 nbch[][2] = अणु
		अणु    0,     0पूर्ण, /* DUMMY_PLF   */
		अणु16200,  3240पूर्ण, /* QPSK_1_4,   */
		अणु21600,  5400पूर्ण, /* QPSK_1_3,   */
		अणु25920,  6480पूर्ण, /* QPSK_2_5,   */
		अणु32400,  7200पूर्ण, /* QPSK_1_2,   */
		अणु38880,  9720पूर्ण, /* QPSK_3_5,   */
		अणु43200, 10800पूर्ण, /* QPSK_2_3,   */
		अणु48600, 11880पूर्ण, /* QPSK_3_4,   */
		अणु51840, 12600पूर्ण, /* QPSK_4_5,   */
		अणु54000, 13320पूर्ण, /* QPSK_5_6,   */
		अणु57600, 14400पूर्ण, /* QPSK_8_9,   */
		अणु58320, 16000पूर्ण, /* QPSK_9_10,  */
		अणु43200,  9720पूर्ण, /* 8PSK_3_5,   */
		अणु48600, 10800पूर्ण, /* 8PSK_2_3,   */
		अणु51840, 11880पूर्ण, /* 8PSK_3_4,   */
		अणु54000, 13320पूर्ण, /* 8PSK_5_6,   */
		अणु57600, 14400पूर्ण, /* 8PSK_8_9,   */
		अणु58320, 16000पूर्ण, /* 8PSK_9_10,  */
		अणु43200, 10800पूर्ण, /* 16APSK_2_3, */
		अणु48600, 11880पूर्ण, /* 16APSK_3_4, */
		अणु51840, 12600पूर्ण, /* 16APSK_4_5, */
		अणु54000, 13320पूर्ण, /* 16APSK_5_6, */
		अणु57600, 14400पूर्ण, /* 16APSK_8_9, */
		अणु58320, 16000पूर्ण, /* 16APSK_9_10 */
		अणु48600, 11880पूर्ण, /* 32APSK_3_4, */
		अणु51840, 12600पूर्ण, /* 32APSK_4_5, */
		अणु54000, 13320पूर्ण, /* 32APSK_5_6, */
		अणु57600, 14400पूर्ण, /* 32APSK_8_9, */
		अणु58320, 16000पूर्ण, /* 32APSK_9_10 */
	पूर्ण;

	अगर (mod_cod >= DVBS2_QPSK_1_4 &&
	    mod_cod <= DVBS2_32APSK_9_10 && fectype <= DVBS2_16K)
		वापस nbch[mod_cod][fectype];
	वापस 64800;
पूर्ण

अटल पूर्णांक get_bit_error_rate_s2(काष्ठा stv *state, u32 *bernumerator,
				 u32 *berdenominator)
अणु
	u8 regs[3];

	पूर्णांक status = पढ़ो_regs(state, RSTV0910_P2_ERRCNT12 + state->regoff,
			       regs, 3);

	अगर (status)
		वापस -EINVAL;

	अगर ((regs[0] & 0x80) == 0) अणु
		state->last_berdenominator =
			dvbs2_nbch((क्रमागत dvbs2_mod_cod)state->mod_cod,
				   state->fectype) <<
			(state->berscale * 2);
		state->last_bernumerator = (((u32)regs[0] & 0x7F) << 16) |
			((u32)regs[1] << 8) | regs[2];
		अगर (state->last_bernumerator < 256 && state->berscale < 6) अणु
			state->berscale += 1;
			ग_लिखो_reg(state, RSTV0910_P2_ERRCTRL1 + state->regoff,
				  0x20 | state->berscale);
		पूर्ण अन्यथा अगर (state->last_bernumerator > 1024 &&
			   state->berscale > 2) अणु
			state->berscale -= 1;
			ग_लिखो_reg(state, RSTV0910_P2_ERRCTRL1 + state->regoff,
				  0x20 | state->berscale);
		पूर्ण
	पूर्ण
	*bernumerator = state->last_bernumerator;
	*berdenominator = state->last_berdenominator;
	वापस status;
पूर्ण

अटल पूर्णांक get_bit_error_rate(काष्ठा stv *state, u32 *bernumerator,
			      u32 *berdenominator)
अणु
	*bernumerator = 0;
	*berdenominator = 1;

	चयन (state->receive_mode) अणु
	हाल RCVMODE_DVBS:
		वापस get_bit_error_rate_s(state,
					    bernumerator, berdenominator);
	हाल RCVMODE_DVBS2:
		वापस get_bit_error_rate_s2(state,
					     bernumerator, berdenominator);
	शेष:
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक set_mघड़ी(काष्ठा stv *state, u32 master_घड़ी)
अणु
	u32 idf = 1;
	u32 odf = 4;
	u32 quartz = state->base->extclk / 1000000;
	u32 fphi = master_घड़ी / 1000000;
	u32 nभाग = (fphi * odf * idf) / quartz;
	u32 cp = 7;
	u32 fvco;

	अगर (nभाग >= 7 && nभाग <= 71)
		cp = 7;
	अन्यथा अगर (nभाग >=  72 && nभाग <=  79)
		cp = 8;
	अन्यथा अगर (nभाग >=  80 && nभाग <=  87)
		cp = 9;
	अन्यथा अगर (nभाग >=  88 && nभाग <=  95)
		cp = 10;
	अन्यथा अगर (nभाग >=  96 && nभाग <= 103)
		cp = 11;
	अन्यथा अगर (nभाग >= 104 && nभाग <= 111)
		cp = 12;
	अन्यथा अगर (nभाग >= 112 && nभाग <= 119)
		cp = 13;
	अन्यथा अगर (nभाग >= 120 && nभाग <= 127)
		cp = 14;
	अन्यथा अगर (nभाग >= 128 && nभाग <= 135)
		cp = 15;
	अन्यथा अगर (nभाग >= 136 && nभाग <= 143)
		cp = 16;
	अन्यथा अगर (nभाग >= 144 && nभाग <= 151)
		cp = 17;
	अन्यथा अगर (nभाग >= 152 && nभाग <= 159)
		cp = 18;
	अन्यथा अगर (nभाग >= 160 && nभाग <= 167)
		cp = 19;
	अन्यथा अगर (nभाग >= 168 && nभाग <= 175)
		cp = 20;
	अन्यथा अगर (nभाग >= 176 && nभाग <= 183)
		cp = 21;
	अन्यथा अगर (nभाग >= 184 && nभाग <= 191)
		cp = 22;
	अन्यथा अगर (nभाग >= 192 && nभाग <= 199)
		cp = 23;
	अन्यथा अगर (nभाग >= 200 && nभाग <= 207)
		cp = 24;
	अन्यथा अगर (nभाग >= 208 && nभाग <= 215)
		cp = 25;
	अन्यथा अगर (nभाग >= 216 && nभाग <= 223)
		cp = 26;
	अन्यथा अगर (nभाग >= 224 && nभाग <= 225)
		cp = 27;

	ग_लिखो_reg(state, RSTV0910_NCOARSE, (cp << 3) | idf);
	ग_लिखो_reg(state, RSTV0910_NCOARSE2, odf);
	ग_लिखो_reg(state, RSTV0910_NCOARSE1, nभाग);

	fvco = (quartz * 2 * nभाग) / idf;
	state->base->mclk = fvco / (2 * odf) * 1000000;

	वापस 0;
पूर्ण

अटल पूर्णांक stop(काष्ठा stv *state)
अणु
	अगर (state->started) अणु
		u8 पंचांगp;

		ग_लिखो_reg(state, RSTV0910_P2_TSCFGH + state->regoff,
			  state->tscfgh | 0x01);
		पढ़ो_reg(state, RSTV0910_P2_PDELCTRL1 + state->regoff, &पंचांगp);
		पंचांगp &= ~0x01; /* release reset DVBS2 packet delin */
		ग_लिखो_reg(state, RSTV0910_P2_PDELCTRL1 + state->regoff, पंचांगp);
		/* Blind optim*/
		ग_लिखो_reg(state, RSTV0910_P2_AGC2O + state->regoff, 0x5B);
		/* Stop the demod */
		ग_लिखो_reg(state, RSTV0910_P2_DMDISTATE + state->regoff, 0x5c);
		state->started = 0;
	पूर्ण
	state->receive_mode = RCVMODE_NONE;
	वापस 0;
पूर्ण

अटल व्योम set_pls(काष्ठा stv *state, u32 pls_code)
अणु
	अगर (pls_code == state->cur_scrambling_code)
		वापस;

	/* PLROOT2 bit 2 = gold code */
	ग_लिखो_reg(state, RSTV0910_P2_PLROOT0 + state->regoff,
		  pls_code & 0xff);
	ग_लिखो_reg(state, RSTV0910_P2_PLROOT1 + state->regoff,
		  (pls_code >> 8) & 0xff);
	ग_लिखो_reg(state, RSTV0910_P2_PLROOT2 + state->regoff,
		  0x04 | ((pls_code >> 16) & 0x03));
	state->cur_scrambling_code = pls_code;
पूर्ण

अटल व्योम set_isi(काष्ठा stv *state, u32 isi)
अणु
	अगर (isi == NO_STREAM_ID_FILTER)
		वापस;
	अगर (isi == 0x80000000) अणु
		SET_FIELD(FORCE_CONTINUOUS, 1);
		SET_FIELD(TSOUT_NOSYNC, 1);
	पूर्ण अन्यथा अणु
		SET_FIELD(FILTER_EN, 1);
		ग_लिखो_reg(state, RSTV0910_P2_ISIENTRY + state->regoff,
			  isi & 0xff);
		ग_लिखो_reg(state, RSTV0910_P2_ISIBITENA + state->regoff, 0xff);
	पूर्ण
	SET_FIELD(ALGOSWRST, 1);
	SET_FIELD(ALGOSWRST, 0);
पूर्ण

अटल व्योम set_stream_modes(काष्ठा stv *state,
			     काष्ठा dtv_frontend_properties *p)
अणु
	set_isi(state, p->stream_id);
	set_pls(state, p->scrambling_sequence_index);
पूर्ण

अटल पूर्णांक init_search_param(काष्ठा stv *state,
			     काष्ठा dtv_frontend_properties *p)
अणु
	SET_FIELD(FORCE_CONTINUOUS, 0);
	SET_FIELD(FRAME_MODE, 0);
	SET_FIELD(FILTER_EN, 0);
	SET_FIELD(TSOUT_NOSYNC, 0);
	SET_FIELD(TSFIFO_EMBINDVB, 0);
	SET_FIELD(TSDEL_SYNCBYTE, 0);
	SET_REG(UPLCCST0, 0xe0);
	SET_FIELD(TSINS_TOKEN, 0);
	SET_FIELD(HYSTERESIS_THRESHOLD, 0);
	SET_FIELD(ISIOBS_MODE, 1);

	set_stream_modes(state, p);
	वापस 0;
पूर्ण

अटल पूर्णांक enable_puncture_rate(काष्ठा stv *state, क्रमागत fe_code_rate rate)
अणु
	u8 val;

	चयन (rate) अणु
	हाल FEC_1_2:
		val = 0x01;
		अवरोध;
	हाल FEC_2_3:
		val = 0x02;
		अवरोध;
	हाल FEC_3_4:
		val = 0x04;
		अवरोध;
	हाल FEC_5_6:
		val = 0x08;
		अवरोध;
	हाल FEC_7_8:
		val = 0x20;
		अवरोध;
	हाल FEC_NONE:
	शेष:
		val = 0x2f;
		अवरोध;
	पूर्ण

	वापस ग_लिखो_reg(state, RSTV0910_P2_PRVIT + state->regoff, val);
पूर्ण

अटल पूर्णांक set_vth_शेष(काष्ठा stv *state)
अणु
	state->vth[0] = 0xd7;
	state->vth[1] = 0x85;
	state->vth[2] = 0x58;
	state->vth[3] = 0x3a;
	state->vth[4] = 0x34;
	state->vth[5] = 0x28;
	ग_लिखो_reg(state, RSTV0910_P2_VTH12 + state->regoff + 0, state->vth[0]);
	ग_लिखो_reg(state, RSTV0910_P2_VTH12 + state->regoff + 1, state->vth[1]);
	ग_लिखो_reg(state, RSTV0910_P2_VTH12 + state->regoff + 2, state->vth[2]);
	ग_लिखो_reg(state, RSTV0910_P2_VTH12 + state->regoff + 3, state->vth[3]);
	ग_लिखो_reg(state, RSTV0910_P2_VTH12 + state->regoff + 4, state->vth[4]);
	ग_लिखो_reg(state, RSTV0910_P2_VTH12 + state->regoff + 5, state->vth[5]);
	वापस 0;
पूर्ण

अटल पूर्णांक set_vth(काष्ठा stv *state)
अणु
	अटल स्थिर काष्ठा slookup vthlookup_table[] = अणु
		अणु250,	8780पूर्ण, /* C/N= 1.5dB */
		अणु100,	7405पूर्ण, /* C/N= 4.5dB */
		अणु40,	6330पूर्ण, /* C/N= 6.5dB */
		अणु12,	5224पूर्ण, /* C/N= 8.5dB */
		अणु5,	4236पूर्ण  /* C/N=10.5dB */
	पूर्ण;

	पूर्णांक i;
	u8 पंचांगp[2];
	पूर्णांक status = पढ़ो_regs(state,
			       RSTV0910_P2_NNOSDATAT1 + state->regoff,
			       पंचांगp, 2);
	u16 reg_value = (पंचांगp[0] << 8) | पंचांगp[1];
	s32 vth = table_lookup(vthlookup_table, ARRAY_SIZE(vthlookup_table),
			      reg_value);

	क्रम (i = 0; i < 6; i += 1)
		अगर (state->vth[i] > vth)
			state->vth[i] = vth;

	ग_लिखो_reg(state, RSTV0910_P2_VTH12 + state->regoff + 0, state->vth[0]);
	ग_लिखो_reg(state, RSTV0910_P2_VTH12 + state->regoff + 1, state->vth[1]);
	ग_लिखो_reg(state, RSTV0910_P2_VTH12 + state->regoff + 2, state->vth[2]);
	ग_लिखो_reg(state, RSTV0910_P2_VTH12 + state->regoff + 3, state->vth[3]);
	ग_लिखो_reg(state, RSTV0910_P2_VTH12 + state->regoff + 4, state->vth[4]);
	ग_लिखो_reg(state, RSTV0910_P2_VTH12 + state->regoff + 5, state->vth[5]);
	वापस status;
पूर्ण

अटल पूर्णांक start(काष्ठा stv *state, काष्ठा dtv_frontend_properties *p)
अणु
	s32 freq;
	u8  reg_dmdcfgmd;
	u16 symb;

	अगर (p->symbol_rate < 100000 || p->symbol_rate > 70000000)
		वापस -EINVAL;

	state->receive_mode = RCVMODE_NONE;
	state->demod_lock_समय = 0;

	/* Demod Stop */
	अगर (state->started)
		ग_लिखो_reg(state, RSTV0910_P2_DMDISTATE + state->regoff, 0x5C);

	init_search_param(state, p);

	अगर (p->symbol_rate <= 1000000) अणु /* SR <=1Msps */
		state->demod_समयout = 3000;
		state->fec_समयout = 2000;
	पूर्ण अन्यथा अगर (p->symbol_rate <= 2000000) अणु /* 1Msps < SR <=2Msps */
		state->demod_समयout = 2500;
		state->fec_समयout = 1300;
	पूर्ण अन्यथा अगर (p->symbol_rate <= 5000000) अणु /* 2Msps< SR <=5Msps */
		state->demod_समयout = 1000;
		state->fec_समयout = 650;
	पूर्ण अन्यथा अगर (p->symbol_rate <= 10000000) अणु /* 5Msps< SR <=10Msps */
		state->demod_समयout = 700;
		state->fec_समयout = 350;
	पूर्ण अन्यथा अगर (p->symbol_rate < 20000000) अणु /* 10Msps< SR <=20Msps */
		state->demod_समयout = 400;
		state->fec_समयout = 200;
	पूर्ण अन्यथा अणु /* SR >=20Msps */
		state->demod_समयout = 300;
		state->fec_समयout = 200;
	पूर्ण

	/* Set the Init Symbol rate */
	symb = muद_भाग32(p->symbol_rate, 65536, state->base->mclk);
	ग_लिखो_reg(state, RSTV0910_P2_SFRINIT1 + state->regoff,
		  ((symb >> 8) & 0x7F));
	ग_लिखो_reg(state, RSTV0910_P2_SFRINIT0 + state->regoff, (symb & 0xFF));

	state->demod_bits |= 0x80;
	ग_लिखो_reg(state, RSTV0910_P2_DEMOD + state->regoff, state->demod_bits);

	/* FE_STV0910_SetSearchStandard */
	पढ़ो_reg(state, RSTV0910_P2_DMDCFGMD + state->regoff, &reg_dmdcfgmd);
	ग_लिखो_reg(state, RSTV0910_P2_DMDCFGMD + state->regoff,
		  reg_dmdcfgmd |= 0xC0);

	ग_लिखो_shared_reg(state,
			 RSTV0910_TSTTSRS, state->nr ? 0x02 : 0x01, 0x00);

	/* Disable DSS */
	ग_लिखो_reg(state, RSTV0910_P2_FECM  + state->regoff, 0x00);
	ग_लिखो_reg(state, RSTV0910_P2_PRVIT + state->regoff, 0x2F);

	enable_puncture_rate(state, FEC_NONE);

	/* 8PSK 3/5, 8PSK 2/3 Poff tracking optimization WA */
	ग_लिखो_reg(state, RSTV0910_P2_ACLC2S2Q + state->regoff, 0x0B);
	ग_लिखो_reg(state, RSTV0910_P2_ACLC2S28 + state->regoff, 0x0A);
	ग_लिखो_reg(state, RSTV0910_P2_BCLC2S2Q + state->regoff, 0x84);
	ग_लिखो_reg(state, RSTV0910_P2_BCLC2S28 + state->regoff, 0x84);
	ग_लिखो_reg(state, RSTV0910_P2_CARHDR + state->regoff, 0x1C);
	ग_लिखो_reg(state, RSTV0910_P2_CARFREQ + state->regoff, 0x79);

	ग_लिखो_reg(state, RSTV0910_P2_ACLC2S216A + state->regoff, 0x29);
	ग_लिखो_reg(state, RSTV0910_P2_ACLC2S232A + state->regoff, 0x09);
	ग_लिखो_reg(state, RSTV0910_P2_BCLC2S216A + state->regoff, 0x84);
	ग_लिखो_reg(state, RSTV0910_P2_BCLC2S232A + state->regoff, 0x84);

	/*
	 * Reset CAR3, bug DVBS2->DVBS1 lock
	 * Note: The bit is only pulsed -> no lock on shared रेजिस्टर needed
	 */
	ग_लिखो_reg(state, RSTV0910_TSTRES0, state->nr ? 0x04 : 0x08);
	ग_लिखो_reg(state, RSTV0910_TSTRES0, 0);

	set_vth_शेष(state);
	/* Reset demod */
	ग_लिखो_reg(state, RSTV0910_P2_DMDISTATE + state->regoff, 0x1F);

	ग_लिखो_reg(state, RSTV0910_P2_CARCFG + state->regoff, 0x46);

	अगर (p->symbol_rate <= 5000000)
		freq = (state->search_range / 2000) + 80;
	अन्यथा
		freq = (state->search_range / 2000) + 1600;
	freq = (freq << 16) / (state->base->mclk / 1000);

	ग_लिखो_reg(state, RSTV0910_P2_CFRUP1 + state->regoff,
		  (freq >> 8) & 0xff);
	ग_लिखो_reg(state, RSTV0910_P2_CFRUP0 + state->regoff, (freq & 0xff));
	/* CFR Low Setting */
	freq = -freq;
	ग_लिखो_reg(state, RSTV0910_P2_CFRLOW1 + state->regoff,
		  (freq >> 8) & 0xff);
	ग_लिखो_reg(state, RSTV0910_P2_CFRLOW0 + state->regoff, (freq & 0xff));

	/* init the demod frequency offset to 0 */
	ग_लिखो_reg(state, RSTV0910_P2_CFRINIT1 + state->regoff, 0);
	ग_लिखो_reg(state, RSTV0910_P2_CFRINIT0 + state->regoff, 0);

	ग_लिखो_reg(state, RSTV0910_P2_DMDISTATE + state->regoff, 0x1F);
	/* Trigger acq */
	ग_लिखो_reg(state, RSTV0910_P2_DMDISTATE + state->regoff, 0x15);

	state->demod_lock_समय += TUNING_DELAY;
	state->started = 1;

	वापस 0;
पूर्ण

अटल पूर्णांक init_diseqc(काष्ठा stv *state)
अणु
	u16 offs = state->nr ? 0x40 : 0; /* Address offset */
	u8 freq = ((state->base->mclk + 11000 * 32) / (22000 * 32));

	/* Disable receiver */
	ग_लिखो_reg(state, RSTV0910_P1_DISRXCFG + offs, 0x00);
	ग_लिखो_reg(state, RSTV0910_P1_DISTXCFG + offs, 0xBA); /* Reset = 1 */
	ग_लिखो_reg(state, RSTV0910_P1_DISTXCFG + offs, 0x3A); /* Reset = 0 */
	ग_लिखो_reg(state, RSTV0910_P1_DISTXF22 + offs, freq);
	वापस 0;
पूर्ण

अटल पूर्णांक probe(काष्ठा stv *state)
अणु
	u8 id;

	state->receive_mode = RCVMODE_NONE;
	state->started = 0;

	अगर (पढ़ो_reg(state, RSTV0910_MID, &id) < 0)
		वापस -ENODEV;

	अगर (id != 0x51)
		वापस -EINVAL;

	/* Configure the I2C repeater to off */
	ग_लिखो_reg(state, RSTV0910_P1_I2CRPT, 0x24);
	/* Configure the I2C repeater to off */
	ग_लिखो_reg(state, RSTV0910_P2_I2CRPT, 0x24);
	/* Set the I2C to oversampling ratio */
	ग_लिखो_reg(state, RSTV0910_I2CCFG, 0x88); /* state->i2ccfg */

	ग_लिखो_reg(state, RSTV0910_OUTCFG,    0x00); /* OUTCFG */
	ग_लिखो_reg(state, RSTV0910_PADCFG,    0x05); /* RFAGC Pads Dev = 05 */
	ग_लिखो_reg(state, RSTV0910_SYNTCTRL,  0x02); /* SYNTCTRL */
	ग_लिखो_reg(state, RSTV0910_TSGENERAL, state->tsgeneral); /* TSGENERAL */
	ग_लिखो_reg(state, RSTV0910_CFGEXT,    0x02); /* CFGEXT */

	अगर (state->single)
		ग_लिखो_reg(state, RSTV0910_GENCFG, 0x14); /* GENCFG */
	अन्यथा
		ग_लिखो_reg(state, RSTV0910_GENCFG, 0x15); /* GENCFG */

	ग_लिखो_reg(state, RSTV0910_P1_TNRCFG2, 0x02); /* IQSWAP = 0 */
	ग_लिखो_reg(state, RSTV0910_P2_TNRCFG2, 0x82); /* IQSWAP = 1 */

	ग_लिखो_reg(state, RSTV0910_P1_CAR3CFG, 0x02);
	ग_लिखो_reg(state, RSTV0910_P2_CAR3CFG, 0x02);
	ग_लिखो_reg(state, RSTV0910_P1_DMDCFG4, 0x04);
	ग_लिखो_reg(state, RSTV0910_P2_DMDCFG4, 0x04);

	ग_लिखो_reg(state, RSTV0910_TSTRES0, 0x80); /* LDPC Reset */
	ग_लिखो_reg(state, RSTV0910_TSTRES0, 0x00);

	ग_लिखो_reg(state, RSTV0910_P1_TSPIDFLT1, 0x00);
	ग_लिखो_reg(state, RSTV0910_P2_TSPIDFLT1, 0x00);

	ग_लिखो_reg(state, RSTV0910_P1_TMGCFG2, 0x80);
	ग_लिखो_reg(state, RSTV0910_P2_TMGCFG2, 0x80);

	set_mघड़ी(state, 135000000);

	/* TS output */
	ग_लिखो_reg(state, RSTV0910_P1_TSCFGH, state->tscfgh | 0x01);
	ग_लिखो_reg(state, RSTV0910_P1_TSCFGH, state->tscfgh);
	ग_लिखो_reg(state, RSTV0910_P1_TSCFGM, 0xC0); /* Manual speed */
	ग_लिखो_reg(state, RSTV0910_P1_TSCFGL, 0x20);

	ग_लिखो_reg(state, RSTV0910_P1_TSSPEED, state->tsspeed);

	ग_लिखो_reg(state, RSTV0910_P2_TSCFGH, state->tscfgh | 0x01);
	ग_लिखो_reg(state, RSTV0910_P2_TSCFGH, state->tscfgh);
	ग_लिखो_reg(state, RSTV0910_P2_TSCFGM, 0xC0); /* Manual speed */
	ग_लिखो_reg(state, RSTV0910_P2_TSCFGL, 0x20);

	ग_लिखो_reg(state, RSTV0910_P2_TSSPEED, state->tsspeed);

	/* Reset stream merger */
	ग_लिखो_reg(state, RSTV0910_P1_TSCFGH, state->tscfgh | 0x01);
	ग_लिखो_reg(state, RSTV0910_P2_TSCFGH, state->tscfgh | 0x01);
	ग_लिखो_reg(state, RSTV0910_P1_TSCFGH, state->tscfgh);
	ग_लिखो_reg(state, RSTV0910_P2_TSCFGH, state->tscfgh);

	ग_लिखो_reg(state, RSTV0910_P1_I2CRPT, state->i2crpt);
	ग_लिखो_reg(state, RSTV0910_P2_I2CRPT, state->i2crpt);

	ग_लिखो_reg(state, RSTV0910_P1_TSINSDELM, 0x17);
	ग_लिखो_reg(state, RSTV0910_P1_TSINSDELL, 0xff);

	ग_लिखो_reg(state, RSTV0910_P2_TSINSDELM, 0x17);
	ग_लिखो_reg(state, RSTV0910_P2_TSINSDELL, 0xff);

	init_diseqc(state);
	वापस 0;
पूर्ण

अटल पूर्णांक gate_ctrl(काष्ठा dvb_frontend *fe, पूर्णांक enable)
अणु
	काष्ठा stv *state = fe->demodulator_priv;
	u8 i2crpt = state->i2crpt & ~0x86;

	/*
	 * mutex_lock note: Concurrent I2C gate bus accesses must be
	 * prevented (STV0910 = dual demod on a single IC with a single I2C
	 * gate/bus, and two tuners attached), similar to most (अगर not all)
	 * other I2C host पूर्णांकerfaces/buses.
	 *
	 * enable=1 (खोलो I2C gate) will grab the lock
	 * enable=0 (बंद I2C gate) releases the lock
	 */

	अगर (enable) अणु
		mutex_lock(&state->base->i2c_lock);
		i2crpt |= 0x80;
	पूर्ण अन्यथा अणु
		i2crpt |= 0x02;
	पूर्ण

	अगर (ग_लिखो_reg(state, state->nr ? RSTV0910_P2_I2CRPT :
		      RSTV0910_P1_I2CRPT, i2crpt) < 0) अणु
		/* करोn't hold the I2C bus lock on failure */
		अगर (!WARN_ON(!mutex_is_locked(&state->base->i2c_lock)))
			mutex_unlock(&state->base->i2c_lock);
		dev_err(&state->base->i2c->dev,
			"%s() write_reg failure (enable=%d)\n",
			__func__, enable);
		वापस -EIO;
	पूर्ण

	state->i2crpt = i2crpt;

	अगर (!enable)
		अगर (!WARN_ON(!mutex_is_locked(&state->base->i2c_lock)))
			mutex_unlock(&state->base->i2c_lock);
	वापस 0;
पूर्ण

अटल व्योम release(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा stv *state = fe->demodulator_priv;

	state->base->count--;
	अगर (state->base->count == 0) अणु
		list_del(&state->base->stvlist);
		kमुक्त(state->base);
	पूर्ण
	kमुक्त(state);
पूर्ण

अटल पूर्णांक set_parameters(काष्ठा dvb_frontend *fe)
अणु
	पूर्णांक stat = 0;
	काष्ठा stv *state = fe->demodulator_priv;
	काष्ठा dtv_frontend_properties *p = &fe->dtv_property_cache;

	stop(state);
	अगर (fe->ops.tuner_ops.set_params)
		fe->ops.tuner_ops.set_params(fe);
	state->symbol_rate = p->symbol_rate;
	stat = start(state, p);
	वापस stat;
पूर्ण

अटल पूर्णांक manage_matype_info(काष्ठा stv *state)
अणु
	अगर (!state->started)
		वापस -EINVAL;
	अगर (state->receive_mode == RCVMODE_DVBS2) अणु
		u8 bbheader[2];

		पढ़ो_regs(state, RSTV0910_P2_MATSTR1 + state->regoff,
			  bbheader, 2);
		state->feroll_off =
			(क्रमागत fe_stv0910_roll_off)(bbheader[0] & 0x03);
		state->is_vcm = (bbheader[0] & 0x10) == 0;
		state->is_standard_broadcast = (bbheader[0] & 0xFC) == 0xF0;
	पूर्ण अन्यथा अगर (state->receive_mode == RCVMODE_DVBS) अणु
		state->is_vcm = 0;
		state->is_standard_broadcast = 1;
		state->feroll_off = FE_SAT_35;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक पढ़ो_snr(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा stv *state = fe->demodulator_priv;
	काष्ठा dtv_frontend_properties *p = &fe->dtv_property_cache;
	s32 snrval;

	अगर (!get_संकेत_to_noise(state, &snrval)) अणु
		p->cnr.stat[0].scale = FE_SCALE_DECIBEL;
		p->cnr.stat[0].svalue = 100 * snrval; /* fix scale */
	पूर्ण अन्यथा अणु
		p->cnr.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक पढ़ो_ber(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा stv *state = fe->demodulator_priv;
	काष्ठा dtv_frontend_properties *p = &fe->dtv_property_cache;
	u32 n, d;

	get_bit_error_rate(state, &n, &d);

	p->pre_bit_error.stat[0].scale = FE_SCALE_COUNTER;
	p->pre_bit_error.stat[0].uvalue = n;
	p->pre_bit_count.stat[0].scale = FE_SCALE_COUNTER;
	p->pre_bit_count.stat[0].uvalue = d;

	वापस 0;
पूर्ण

अटल व्योम पढ़ो_संकेत_strength(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा stv *state = fe->demodulator_priv;
	काष्ठा dtv_frontend_properties *p = &state->fe.dtv_property_cache;
	u8 reg[2];
	u16 agc;
	s32 padc, घातer = 0;
	पूर्णांक i;

	पढ़ो_regs(state, RSTV0910_P2_AGCIQIN1 + state->regoff, reg, 2);

	agc = (((u32)reg[0]) << 8) | reg[1];

	क्रम (i = 0; i < 5; i += 1) अणु
		पढ़ो_regs(state, RSTV0910_P2_POWERI + state->regoff, reg, 2);
		घातer += (u32)reg[0] * (u32)reg[0]
			+ (u32)reg[1] * (u32)reg[1];
		usleep_range(3000, 4000);
	पूर्ण
	घातer /= 5;

	padc = table_lookup(padc_lookup, ARRAY_SIZE(padc_lookup), घातer) + 352;

	p->strength.stat[0].scale = FE_SCALE_DECIBEL;
	p->strength.stat[0].svalue = (padc - agc);
पूर्ण

अटल पूर्णांक पढ़ो_status(काष्ठा dvb_frontend *fe, क्रमागत fe_status *status)
अणु
	काष्ठा stv *state = fe->demodulator_priv;
	काष्ठा dtv_frontend_properties *p = &fe->dtv_property_cache;
	u8 dmd_state = 0;
	u8 dstatus  = 0;
	क्रमागत receive_mode cur_receive_mode = RCVMODE_NONE;
	u32 feघड़ी = 0;

	*status = 0;

	पढ़ो_reg(state, RSTV0910_P2_DMDSTATE + state->regoff, &dmd_state);

	अगर (dmd_state & 0x40) अणु
		पढ़ो_reg(state, RSTV0910_P2_DSTATUS + state->regoff, &dstatus);
		अगर (dstatus & 0x08)
			cur_receive_mode = (dmd_state & 0x20) ?
				RCVMODE_DVBS : RCVMODE_DVBS2;
	पूर्ण
	अगर (cur_receive_mode == RCVMODE_NONE) अणु
		set_vth(state);

		/* reset संकेत statistics */
		p->strength.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
		p->cnr.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
		p->pre_bit_error.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
		p->pre_bit_count.stat[0].scale = FE_SCALE_NOT_AVAILABLE;

		वापस 0;
	पूर्ण

	*status |= (FE_HAS_SIGNAL
		| FE_HAS_CARRIER
		| FE_HAS_VITERBI
		| FE_HAS_SYNC);

	अगर (state->receive_mode == RCVMODE_NONE) अणु
		state->receive_mode = cur_receive_mode;
		state->demod_lock_समय = jअगरfies;
		state->first_समय_lock = 1;

		get_संकेत_parameters(state);
		tracking_optimization(state);

		ग_लिखो_reg(state, RSTV0910_P2_TSCFGH + state->regoff,
			  state->tscfgh);
		usleep_range(3000, 4000);
		ग_लिखो_reg(state, RSTV0910_P2_TSCFGH + state->regoff,
			  state->tscfgh | 0x01);
		ग_लिखो_reg(state, RSTV0910_P2_TSCFGH + state->regoff,
			  state->tscfgh);
	पूर्ण
	अगर (dmd_state & 0x40) अणु
		अगर (state->receive_mode == RCVMODE_DVBS2) अणु
			u8 pdelstatus;

			पढ़ो_reg(state,
				 RSTV0910_P2_PDELSTATUS1 + state->regoff,
				 &pdelstatus);
			feघड़ी = (pdelstatus & 0x02) != 0;
		पूर्ण अन्यथा अणु
			u8 vstatus;

			पढ़ो_reg(state,
				 RSTV0910_P2_VSTATUSVIT + state->regoff,
				 &vstatus);
			feघड़ी = (vstatus & 0x08) != 0;
		पूर्ण
	पूर्ण

	अगर (feघड़ी) अणु
		*status |= FE_HAS_LOCK;

		अगर (state->first_समय_lock) अणु
			u8 पंचांगp;

			state->first_समय_lock = 0;

			manage_matype_info(state);

			अगर (state->receive_mode == RCVMODE_DVBS2) अणु
				/*
				 * FSTV0910_P2_MANUALSX_ROLLOFF,
				 * FSTV0910_P2_MANUALS2_ROLLOFF = 0
				 */
				state->demod_bits &= ~0x84;
				ग_लिखो_reg(state,
					  RSTV0910_P2_DEMOD + state->regoff,
					  state->demod_bits);
				पढ़ो_reg(state,
					 RSTV0910_P2_PDELCTRL2 + state->regoff,
					 &पंचांगp);
				/* reset DVBS2 packet delinator error counter */
				पंचांगp |= 0x40;
				ग_लिखो_reg(state,
					  RSTV0910_P2_PDELCTRL2 + state->regoff,
					  पंचांगp);
				/* reset DVBS2 packet delinator error counter */
				पंचांगp &= ~0x40;
				ग_लिखो_reg(state,
					  RSTV0910_P2_PDELCTRL2 + state->regoff,
					  पंचांगp);

				state->berscale = 2;
				state->last_bernumerator = 0;
				state->last_berdenominator = 1;
				/* क्रमce to PRE BCH Rate */
				ग_लिखो_reg(state,
					  RSTV0910_P2_ERRCTRL1 + state->regoff,
					  BER_SRC_S2 | state->berscale);
			पूर्ण अन्यथा अणु
				state->berscale = 2;
				state->last_bernumerator = 0;
				state->last_berdenominator = 1;
				/* क्रमce to PRE RS Rate */
				ग_लिखो_reg(state,
					  RSTV0910_P2_ERRCTRL1 + state->regoff,
					  BER_SRC_S | state->berscale);
			पूर्ण
			/* Reset the Total packet counter */
			ग_लिखो_reg(state,
				  RSTV0910_P2_FBERCPT4 + state->regoff, 0x00);
			/*
			 * Reset the packet Error counter2 (and Set it to
			 * infinite error count mode)
			 */
			ग_लिखो_reg(state,
				  RSTV0910_P2_ERRCTRL2 + state->regoff, 0xc1);

			set_vth_शेष(state);
			अगर (state->receive_mode == RCVMODE_DVBS)
				enable_puncture_rate(state,
						     state->puncture_rate);
		पूर्ण

		/* Use highest संकेतed ModCod क्रम quality */
		अगर (state->is_vcm) अणु
			u8 पंचांगp;
			क्रमागत fe_stv0910_mod_cod mod_cod;

			पढ़ो_reg(state, RSTV0910_P2_DMDMODCOD + state->regoff,
				 &पंचांगp);
			mod_cod = (क्रमागत fe_stv0910_mod_cod)((पंचांगp & 0x7c) >> 2);

			अगर (mod_cod > state->mod_cod)
				state->mod_cod = mod_cod;
		पूर्ण
	पूर्ण

	/* पढ़ो संकेत statistics */

	/* पढ़ो संकेत strength */
	पढ़ो_संकेत_strength(fe);

	/* पढ़ो carrier/noise on FE_HAS_CARRIER */
	अगर (*status & FE_HAS_CARRIER)
		पढ़ो_snr(fe);
	अन्यथा
		p->cnr.stat[0].scale = FE_SCALE_NOT_AVAILABLE;

	/* पढ़ो ber */
	अगर (*status & FE_HAS_VITERBI) अणु
		पढ़ो_ber(fe);
	पूर्ण अन्यथा अणु
		p->pre_bit_error.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
		p->pre_bit_count.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक get_frontend(काष्ठा dvb_frontend *fe,
			काष्ठा dtv_frontend_properties *p)
अणु
	काष्ठा stv *state = fe->demodulator_priv;
	u8 पंचांगp;
	u32 symbolrate;

	अगर (state->receive_mode == RCVMODE_DVBS2) अणु
		u32 mc;
		स्थिर क्रमागत fe_modulation modcod2mod[0x20] = अणु
			QPSK, QPSK, QPSK, QPSK,
			QPSK, QPSK, QPSK, QPSK,
			QPSK, QPSK, QPSK, QPSK,
			PSK_8, PSK_8, PSK_8, PSK_8,
			PSK_8, PSK_8, APSK_16, APSK_16,
			APSK_16, APSK_16, APSK_16, APSK_16,
			APSK_32, APSK_32, APSK_32, APSK_32,
			APSK_32,
		पूर्ण;
		स्थिर क्रमागत fe_code_rate modcod2fec[0x20] = अणु
			FEC_NONE, FEC_NONE, FEC_NONE, FEC_2_5,
			FEC_1_2, FEC_3_5, FEC_2_3, FEC_3_4,
			FEC_4_5, FEC_5_6, FEC_8_9, FEC_9_10,
			FEC_3_5, FEC_2_3, FEC_3_4, FEC_5_6,
			FEC_8_9, FEC_9_10, FEC_2_3, FEC_3_4,
			FEC_4_5, FEC_5_6, FEC_8_9, FEC_9_10,
			FEC_3_4, FEC_4_5, FEC_5_6, FEC_8_9,
			FEC_9_10
		पूर्ण;
		पढ़ो_reg(state, RSTV0910_P2_DMDMODCOD + state->regoff, &पंचांगp);
		mc = ((पंचांगp & 0x7c) >> 2);
		p->pilot = (पंचांगp & 0x01) ? PILOT_ON : PILOT_OFF;
		p->modulation = modcod2mod[mc];
		p->fec_inner = modcod2fec[mc];
	पूर्ण अन्यथा अगर (state->receive_mode == RCVMODE_DVBS) अणु
		पढ़ो_reg(state, RSTV0910_P2_VITCURPUN + state->regoff, &पंचांगp);
		चयन (पंचांगp & 0x1F) अणु
		हाल 0x0d:
			p->fec_inner = FEC_1_2;
			अवरोध;
		हाल 0x12:
			p->fec_inner = FEC_2_3;
			अवरोध;
		हाल 0x15:
			p->fec_inner = FEC_3_4;
			अवरोध;
		हाल 0x18:
			p->fec_inner = FEC_5_6;
			अवरोध;
		हाल 0x1a:
			p->fec_inner = FEC_7_8;
			अवरोध;
		शेष:
			p->fec_inner = FEC_NONE;
			अवरोध;
		पूर्ण
		p->rolloff = ROLLOFF_35;
	पूर्ण

	अगर (state->receive_mode != RCVMODE_NONE) अणु
		get_cur_symbol_rate(state, &symbolrate);
		p->symbol_rate = symbolrate;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक tune(काष्ठा dvb_frontend *fe, bool re_tune,
		अचिन्हित पूर्णांक mode_flags,
		अचिन्हित पूर्णांक *delay, क्रमागत fe_status *status)
अणु
	काष्ठा stv *state = fe->demodulator_priv;
	पूर्णांक r;

	अगर (re_tune) अणु
		r = set_parameters(fe);
		अगर (r)
			वापस r;
		state->tune_समय = jअगरfies;
	पूर्ण

	r = पढ़ो_status(fe, status);
	अगर (r)
		वापस r;

	अगर (*status & FE_HAS_LOCK)
		वापस 0;
	*delay = HZ;

	वापस 0;
पूर्ण

अटल क्रमागत dvbfe_algo get_algo(काष्ठा dvb_frontend *fe)
अणु
	वापस DVBFE_ALGO_HW;
पूर्ण

अटल पूर्णांक set_tone(काष्ठा dvb_frontend *fe, क्रमागत fe_sec_tone_mode tone)
अणु
	काष्ठा stv *state = fe->demodulator_priv;
	u16 offs = state->nr ? 0x40 : 0;

	चयन (tone) अणु
	हाल SEC_TONE_ON:
		वापस ग_लिखो_reg(state, RSTV0910_P1_DISTXCFG + offs, 0x38);
	हाल SEC_TONE_OFF:
		वापस ग_लिखो_reg(state, RSTV0910_P1_DISTXCFG + offs, 0x3a);
	शेष:
		अवरोध;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक रुको_dis(काष्ठा stv *state, u8 flag, u8 val)
अणु
	पूर्णांक i;
	u8 stat;
	u16 offs = state->nr ? 0x40 : 0;

	क्रम (i = 0; i < 10; i++) अणु
		पढ़ो_reg(state, RSTV0910_P1_DISTXSTATUS + offs, &stat);
		अगर ((stat & flag) == val)
			वापस 0;
		usleep_range(10000, 11000);
	पूर्ण
	वापस -ETIMEDOUT;
पूर्ण

अटल पूर्णांक send_master_cmd(काष्ठा dvb_frontend *fe,
			   काष्ठा dvb_diseqc_master_cmd *cmd)
अणु
	काष्ठा stv *state = fe->demodulator_priv;
	पूर्णांक i;

	SET_FIELD(DISEQC_MODE, 2);
	SET_FIELD(DIS_PRECHARGE, 1);
	क्रम (i = 0; i < cmd->msg_len; i++) अणु
		रुको_dis(state, 0x40, 0x00);
		SET_REG(DISTXFIFO, cmd->msg[i]);
	पूर्ण
	SET_FIELD(DIS_PRECHARGE, 0);
	रुको_dis(state, 0x20, 0x20);
	वापस 0;
पूर्ण

अटल पूर्णांक send_burst(काष्ठा dvb_frontend *fe, क्रमागत fe_sec_mini_cmd burst)
अणु
	काष्ठा stv *state = fe->demodulator_priv;
	u8 value;

	अगर (burst == SEC_MINI_A) अणु
		SET_FIELD(DISEQC_MODE, 3);
		value = 0x00;
	पूर्ण अन्यथा अणु
		SET_FIELD(DISEQC_MODE, 2);
		value = 0xFF;
	पूर्ण

	SET_FIELD(DIS_PRECHARGE, 1);
	रुको_dis(state, 0x40, 0x00);
	SET_REG(DISTXFIFO, value);
	SET_FIELD(DIS_PRECHARGE, 0);
	रुको_dis(state, 0x20, 0x20);

	वापस 0;
पूर्ण

अटल पूर्णांक sleep(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा stv *state = fe->demodulator_priv;

	stop(state);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dvb_frontend_ops stv0910_ops = अणु
	.delsys = अणु SYS_DVBS, SYS_DVBS2, SYS_DSS पूर्ण,
	.info = अणु
		.name			= "ST STV0910",
		.frequency_min_hz	=  950 * MHz,
		.frequency_max_hz	= 2150 * MHz,
		.symbol_rate_min	= 100000,
		.symbol_rate_max	= 70000000,
		.caps			= FE_CAN_INVERSION_AUTO |
					  FE_CAN_FEC_AUTO       |
					  FE_CAN_QPSK           |
					  FE_CAN_2G_MODULATION  |
					  FE_CAN_MULTISTREAM
	पूर्ण,
	.sleep				= sleep,
	.release			= release,
	.i2c_gate_ctrl			= gate_ctrl,
	.set_frontend			= set_parameters,
	.get_frontend_algo		= get_algo,
	.get_frontend			= get_frontend,
	.tune				= tune,
	.पढ़ो_status			= पढ़ो_status,
	.set_tone			= set_tone,

	.diseqc_send_master_cmd		= send_master_cmd,
	.diseqc_send_burst		= send_burst,
पूर्ण;

अटल काष्ठा stv_base *match_base(काष्ठा i2c_adapter *i2c, u8 adr)
अणु
	काष्ठा stv_base *p;

	list_क्रम_each_entry(p, &stvlist, stvlist)
		अगर (p->i2c == i2c && p->adr == adr)
			वापस p;
	वापस शून्य;
पूर्ण

अटल व्योम stv0910_init_stats(काष्ठा stv *state)
अणु
	काष्ठा dtv_frontend_properties *p = &state->fe.dtv_property_cache;

	p->strength.len = 1;
	p->strength.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	p->cnr.len = 1;
	p->cnr.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	p->pre_bit_error.len = 1;
	p->pre_bit_error.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	p->pre_bit_count.len = 1;
	p->pre_bit_count.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
पूर्ण

काष्ठा dvb_frontend *stv0910_attach(काष्ठा i2c_adapter *i2c,
				    काष्ठा stv0910_cfg *cfg,
				    पूर्णांक nr)
अणु
	काष्ठा stv *state;
	काष्ठा stv_base *base;

	state = kzalloc(माप(*state), GFP_KERNEL);
	अगर (!state)
		वापस शून्य;

	state->tscfgh = 0x20 | (cfg->parallel ? 0 : 0x40);
	state->tsgeneral = (cfg->parallel == 2) ? 0x02 : 0x00;
	state->i2crpt = 0x0A | ((cfg->rptlvl & 0x07) << 4);
	/* use safe tsspeed value अगर unspecअगरied through stv0910_cfg */
	state->tsspeed = (cfg->tsspeed ? cfg->tsspeed : 0x28);
	state->nr = nr;
	state->regoff = state->nr ? 0 : 0x200;
	state->search_range = 16000000;
	state->demod_bits = 0x10; /* Inversion : Auto with reset to 0 */
	state->receive_mode = RCVMODE_NONE;
	state->cur_scrambling_code = (~0U);
	state->single = cfg->single ? 1 : 0;

	base = match_base(i2c, cfg->adr);
	अगर (base) अणु
		base->count++;
		state->base = base;
	पूर्ण अन्यथा अणु
		base = kzalloc(माप(*base), GFP_KERNEL);
		अगर (!base)
			जाओ fail;
		base->i2c = i2c;
		base->adr = cfg->adr;
		base->count = 1;
		base->extclk = cfg->clk ? cfg->clk : 30000000;

		mutex_init(&base->i2c_lock);
		mutex_init(&base->reg_lock);
		state->base = base;
		अगर (probe(state) < 0) अणु
			dev_info(&i2c->dev, "No demod found at adr %02X on %s\n",
				 cfg->adr, dev_name(&i2c->dev));
			kमुक्त(base);
			जाओ fail;
		पूर्ण
		list_add(&base->stvlist, &stvlist);
	पूर्ण
	state->fe.ops = stv0910_ops;
	state->fe.demodulator_priv = state;
	state->nr = nr;

	dev_info(&i2c->dev, "%s demod found at adr %02X on %s\n",
		 state->fe.ops.info.name, cfg->adr, dev_name(&i2c->dev));

	stv0910_init_stats(state);

	वापस &state->fe;

fail:
	kमुक्त(state);
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(stv0910_attach);

MODULE_DESCRIPTION("ST STV0910 multistandard frontend driver");
MODULE_AUTHOR("Ralph and Marcus Metzler, Manfred Voelkel");
MODULE_LICENSE("GPL v2");
