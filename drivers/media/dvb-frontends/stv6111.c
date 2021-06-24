<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Driver क्रम the ST STV6111 tuner
 *
 * Copyright (C) 2014 Digital Devices GmbH
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

#समावेश "stv6111.h"

#समावेश <media/dvb_frontend.h>

काष्ठा stv अणु
	काष्ठा i2c_adapter *i2c;
	u8 adr;

	u8 reg[11];
	u32 ref_freq;
	u32 frequency;
पूर्ण;

काष्ठा slookup अणु
	s16 value;
	u16 reg_value;
पूर्ण;

अटल स्थिर काष्ठा slookup lnagain_nf_lookup[] = अणु
	/* Gain *100dB // Reg */
	अणु 2572,	0 पूर्ण,
	अणु 2575, 1 पूर्ण,
	अणु 2580, 2 पूर्ण,
	अणु 2588, 3 पूर्ण,
	अणु 2596, 4 पूर्ण,
	अणु 2611, 5 पूर्ण,
	अणु 2633, 6 पूर्ण,
	अणु 2664, 7 पूर्ण,
	अणु 2701, 8 पूर्ण,
	अणु 2753, 9 पूर्ण,
	अणु 2816, 10 पूर्ण,
	अणु 2902, 11 पूर्ण,
	अणु 2995, 12 पूर्ण,
	अणु 3104, 13 पूर्ण,
	अणु 3215, 14 पूर्ण,
	अणु 3337, 15 पूर्ण,
	अणु 3492, 16 पूर्ण,
	अणु 3614, 17 पूर्ण,
	अणु 3731, 18 पूर्ण,
	अणु 3861, 19 पूर्ण,
	अणु 3988, 20 पूर्ण,
	अणु 4124, 21 पूर्ण,
	अणु 4253, 22 पूर्ण,
	अणु 4386,	23 पूर्ण,
	अणु 4505,	24 पूर्ण,
	अणु 4623,	25 पूर्ण,
	अणु 4726,	26 पूर्ण,
	अणु 4821,	27 पूर्ण,
	अणु 4903,	28 पूर्ण,
	अणु 4979,	29 पूर्ण,
	अणु 5045,	30 पूर्ण,
	अणु 5102,	31 पूर्ण
पूर्ण;

अटल स्थिर काष्ठा slookup lnagain_iip3_lookup[] = अणु
	/* Gain *100dB // reg */
	अणु 1548,	0 पूर्ण,
	अणु 1552,	1 पूर्ण,
	अणु 1569,	2 पूर्ण,
	अणु 1565,	3 पूर्ण,
	अणु 1577,	4 पूर्ण,
	अणु 1594,	5 पूर्ण,
	अणु 1627,	6 पूर्ण,
	अणु 1656,	7 पूर्ण,
	अणु 1700,	8 पूर्ण,
	अणु 1748,	9 पूर्ण,
	अणु 1805,	10 पूर्ण,
	अणु 1896,	11 पूर्ण,
	अणु 1995,	12 पूर्ण,
	अणु 2113,	13 पूर्ण,
	अणु 2233,	14 पूर्ण,
	अणु 2366,	15 पूर्ण,
	अणु 2543,	16 पूर्ण,
	अणु 2687,	17 पूर्ण,
	अणु 2842,	18 पूर्ण,
	अणु 2999,	19 पूर्ण,
	अणु 3167,	20 पूर्ण,
	अणु 3342,	21 पूर्ण,
	अणु 3507,	22 पूर्ण,
	अणु 3679,	23 पूर्ण,
	अणु 3827,	24 पूर्ण,
	अणु 3970,	25 पूर्ण,
	अणु 4094,	26 पूर्ण,
	अणु 4210,	27 पूर्ण,
	अणु 4308,	28 पूर्ण,
	अणु 4396,	29 पूर्ण,
	अणु 4468,	30 पूर्ण,
	अणु 4535,	31 पूर्ण
पूर्ण;

अटल स्थिर काष्ठा slookup gain_rfagc_lookup[] = अणु
	/* Gain *100dB // reg */
	अणु 4870,	0x3000 पूर्ण,
	अणु 4850,	0x3C00 पूर्ण,
	अणु 4800,	0x4500 पूर्ण,
	अणु 4750,	0x4800 पूर्ण,
	अणु 4700,	0x4B00 पूर्ण,
	अणु 4650,	0x4D00 पूर्ण,
	अणु 4600,	0x4F00 पूर्ण,
	अणु 4550,	0x5100 पूर्ण,
	अणु 4500,	0x5200 पूर्ण,
	अणु 4420,	0x5500 पूर्ण,
	अणु 4316,	0x5800 पूर्ण,
	अणु 4200,	0x5B00 पूर्ण,
	अणु 4119,	0x5D00 पूर्ण,
	अणु 3999,	0x6000 पूर्ण,
	अणु 3950,	0x6100 पूर्ण,
	अणु 3876,	0x6300 पूर्ण,
	अणु 3755,	0x6600 पूर्ण,
	अणु 3641,	0x6900 पूर्ण,
	अणु 3567,	0x6B00 पूर्ण,
	अणु 3425,	0x6F00 पूर्ण,
	अणु 3350,	0x7100 पूर्ण,
	अणु 3236,	0x7400 पूर्ण,
	अणु 3118,	0x7700 पूर्ण,
	अणु 3004,	0x7A00 पूर्ण,
	अणु 2917,	0x7C00 पूर्ण,
	अणु 2776,	0x7F00 पूर्ण,
	अणु 2635,	0x8200 पूर्ण,
	अणु 2516,	0x8500 पूर्ण,
	अणु 2406,	0x8800 पूर्ण,
	अणु 2290,	0x8B00 पूर्ण,
	अणु 2170,	0x8E00 पूर्ण,
	अणु 2073,	0x9100 पूर्ण,
	अणु 1949,	0x9400 पूर्ण,
	अणु 1836,	0x9700 पूर्ण,
	अणु 1712,	0x9A00 पूर्ण,
	अणु 1631,	0x9C00 पूर्ण,
	अणु 1515,	0x9F00 पूर्ण,
	अणु 1400,	0xA200 पूर्ण,
	अणु 1323,	0xA400 पूर्ण,
	अणु 1203,	0xA700 पूर्ण,
	अणु 1091,	0xAA00 पूर्ण,
	अणु 1011,	0xAC00 पूर्ण,
	अणु 904,	0xAF00 पूर्ण,
	अणु 787,	0xB200 पूर्ण,
	अणु 685,	0xB500 पूर्ण,
	अणु 571,	0xB800 पूर्ण,
	अणु 464,	0xBB00 पूर्ण,
	अणु 374,	0xBE00 पूर्ण,
	अणु 275,	0xC200 पूर्ण,
	अणु 181,	0xC600 पूर्ण,
	अणु 102,	0xCC00 पूर्ण,
	अणु 49,	0xD900 पूर्ण
पूर्ण;

/*
 * This table is 6 dB too low comapred to the others (probably created with
 * a dअगरferent BB_MAG setting)
 */
अटल स्थिर काष्ठा slookup gain_channel_agc_nf_lookup[] = अणु
	/* Gain *100dB // reg */
	अणु 7082,	0x3000 पूर्ण,
	अणु 7052,	0x4000 पूर्ण,
	अणु 7007,	0x4600 पूर्ण,
	अणु 6954,	0x4A00 पूर्ण,
	अणु 6909,	0x4D00 पूर्ण,
	अणु 6833,	0x5100 पूर्ण,
	अणु 6753,	0x5400 पूर्ण,
	अणु 6659,	0x5700 पूर्ण,
	अणु 6561,	0x5A00 पूर्ण,
	अणु 6472,	0x5C00 पूर्ण,
	अणु 6366,	0x5F00 पूर्ण,
	अणु 6259,	0x6100 पूर्ण,
	अणु 6151,	0x6400 पूर्ण,
	अणु 6026,	0x6700 पूर्ण,
	अणु 5920,	0x6900 पूर्ण,
	अणु 5835,	0x6B00 पूर्ण,
	अणु 5770,	0x6C00 पूर्ण,
	अणु 5681,	0x6E00 पूर्ण,
	अणु 5596,	0x7000 पूर्ण,
	अणु 5503,	0x7200 पूर्ण,
	अणु 5429,	0x7300 पूर्ण,
	अणु 5319,	0x7500 पूर्ण,
	अणु 5220,	0x7700 पूर्ण,
	अणु 5111,	0x7900 पूर्ण,
	अणु 4983,	0x7B00 पूर्ण,
	अणु 4876,	0x7D00 पूर्ण,
	अणु 4755,	0x7F00 पूर्ण,
	अणु 4635,	0x8100 पूर्ण,
	अणु 4499,	0x8300 पूर्ण,
	अणु 4405,	0x8500 पूर्ण,
	अणु 4323,	0x8600 पूर्ण,
	अणु 4233,	0x8800 पूर्ण,
	अणु 4156,	0x8A00 पूर्ण,
	अणु 4038,	0x8C00 पूर्ण,
	अणु 3935,	0x8E00 पूर्ण,
	अणु 3823,	0x9000 पूर्ण,
	अणु 3712,	0x9200 पूर्ण,
	अणु 3601,	0x9500 पूर्ण,
	अणु 3511,	0x9700 पूर्ण,
	अणु 3413,	0x9900 पूर्ण,
	अणु 3309,	0x9B00 पूर्ण,
	अणु 3213,	0x9D00 पूर्ण,
	अणु 3088,	0x9F00 पूर्ण,
	अणु 2992,	0xA100 पूर्ण,
	अणु 2878,	0xA400 पूर्ण,
	अणु 2769,	0xA700 पूर्ण,
	अणु 2645,	0xAA00 पूर्ण,
	अणु 2538,	0xAD00 पूर्ण,
	अणु 2441,	0xB000 पूर्ण,
	अणु 2350,	0xB600 पूर्ण,
	अणु 2237,	0xBA00 पूर्ण,
	अणु 2137,	0xBF00 पूर्ण,
	अणु 2039,	0xC500 पूर्ण,
	अणु 1938,	0xDF00 पूर्ण,
	अणु 1927,	0xFF00 पूर्ण
पूर्ण;

अटल स्थिर काष्ठा slookup gain_channel_agc_iip3_lookup[] = अणु
	/* Gain *100dB // reg */
	अणु 7070,	0x3000 पूर्ण,
	अणु 7028,	0x4000 पूर्ण,
	अणु 7019,	0x4600 पूर्ण,
	अणु 6900,	0x4A00 पूर्ण,
	अणु 6811,	0x4D00 पूर्ण,
	अणु 6763,	0x5100 पूर्ण,
	अणु 6690,	0x5400 पूर्ण,
	अणु 6644,	0x5700 पूर्ण,
	अणु 6617,	0x5A00 पूर्ण,
	अणु 6598,	0x5C00 पूर्ण,
	अणु 6462,	0x5F00 पूर्ण,
	अणु 6348,	0x6100 पूर्ण,
	अणु 6197,	0x6400 पूर्ण,
	अणु 6154,	0x6700 पूर्ण,
	अणु 6098,	0x6900 पूर्ण,
	अणु 5893,	0x6B00 पूर्ण,
	अणु 5812,	0x6C00 पूर्ण,
	अणु 5773,	0x6E00 पूर्ण,
	अणु 5723,	0x7000 पूर्ण,
	अणु 5661,	0x7200 पूर्ण,
	अणु 5579,	0x7300 पूर्ण,
	अणु 5460,	0x7500 पूर्ण,
	अणु 5308,	0x7700 पूर्ण,
	अणु 5099,	0x7900 पूर्ण,
	अणु 4910,	0x7B00 पूर्ण,
	अणु 4800,	0x7D00 पूर्ण,
	अणु 4785,	0x7F00 पूर्ण,
	अणु 4635,	0x8100 पूर्ण,
	अणु 4466,	0x8300 पूर्ण,
	अणु 4314,	0x8500 पूर्ण,
	अणु 4295,	0x8600 पूर्ण,
	अणु 4144,	0x8800 पूर्ण,
	अणु 3920,	0x8A00 पूर्ण,
	अणु 3889,	0x8C00 पूर्ण,
	अणु 3771,	0x8E00 पूर्ण,
	अणु 3655,	0x9000 पूर्ण,
	अणु 3446,	0x9200 पूर्ण,
	अणु 3298,	0x9500 पूर्ण,
	अणु 3083,	0x9700 पूर्ण,
	अणु 3015,	0x9900 पूर्ण,
	अणु 2833,	0x9B00 पूर्ण,
	अणु 2746,	0x9D00 पूर्ण,
	अणु 2632,	0x9F00 पूर्ण,
	अणु 2598,	0xA100 पूर्ण,
	अणु 2480,	0xA400 पूर्ण,
	अणु 2236,	0xA700 पूर्ण,
	अणु 2171,	0xAA00 पूर्ण,
	अणु 2060,	0xAD00 पूर्ण,
	अणु 1999,	0xB000 पूर्ण,
	अणु 1974,	0xB600 पूर्ण,
	अणु 1820,	0xBA00 पूर्ण,
	अणु 1741,	0xBF00 पूर्ण,
	अणु 1655,	0xC500 पूर्ण,
	अणु 1444,	0xDF00 पूर्ण,
	अणु 1325,	0xFF00 पूर्ण,
पूर्ण;

अटल अंतरभूत u32 muद_भाग32(u32 a, u32 b, u32 c)
अणु
	u64 पंचांगp64;

	पंचांगp64 = (u64)a * (u64)b;
	करो_भाग(पंचांगp64, c);

	वापस (u32)पंचांगp64;
पूर्ण

अटल पूर्णांक i2c_पढ़ो(काष्ठा i2c_adapter *adap,
		    u8 adr, u8 *msg, पूर्णांक len, u8 *answ, पूर्णांक alen)
अणु
	काष्ठा i2c_msg msgs[2] = अणु अणु .addr = adr, .flags = 0,
				     .buf = msg, .len = lenपूर्ण,
				   अणु .addr = adr, .flags = I2C_M_RD,
				     .buf = answ, .len = alen पूर्ण पूर्ण;
	अगर (i2c_transfer(adap, msgs, 2) != 2) अणु
		dev_err(&adap->dev, "i2c read error\n");
		वापस -EIO;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक i2c_ग_लिखो(काष्ठा i2c_adapter *adap, u8 adr, u8 *data, पूर्णांक len)
अणु
	काष्ठा i2c_msg msg = अणु.addr = adr, .flags = 0,
			      .buf = data, .len = lenपूर्ण;

	अगर (i2c_transfer(adap, &msg, 1) != 1) अणु
		dev_err(&adap->dev, "i2c write error\n");
		वापस -EIO;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक ग_लिखो_regs(काष्ठा stv *state, पूर्णांक reg, पूर्णांक len)
अणु
	u8 d[12];

	स_नकल(&d[1], &state->reg[reg], len);
	d[0] = reg;
	वापस i2c_ग_लिखो(state->i2c, state->adr, d, len + 1);
पूर्ण

अटल पूर्णांक ग_लिखो_reg(काष्ठा stv *state, u8 reg, u8 val)
अणु
	u8 d[2] = अणुreg, valपूर्ण;

	वापस i2c_ग_लिखो(state->i2c, state->adr, d, 2);
पूर्ण

अटल पूर्णांक पढ़ो_reg(काष्ठा stv *state, u8 reg, u8 *val)
अणु
	वापस i2c_पढ़ो(state->i2c, state->adr, &reg, 1, val, 1);
पूर्ण

अटल पूर्णांक रुको_क्रम_call_करोne(काष्ठा stv *state, u8 mask)
अणु
	पूर्णांक status = 0;
	u32 lock_retry_count = 10;

	जबतक (lock_retry_count > 0) अणु
		u8 regval;

		status = पढ़ो_reg(state, 9, &regval);
		अगर (status < 0)
			वापस status;

		अगर ((regval & mask) == 0)
			अवरोध;
		usleep_range(4000, 6000);
		lock_retry_count -= 1;

		status = -EIO;
	पूर्ण
	वापस status;
पूर्ण

अटल व्योम init_state(काष्ठा stv *state)
अणु
	u32 clkभाग = 0;
	u32 agcmode = 0;
	u32 agcref = 2;
	u32 agcset = 0xffffffff;
	u32 bbmode = 0xffffffff;

	state->reg[0] = 0x08;
	state->reg[1] = 0x41;
	state->reg[2] = 0x8f;
	state->reg[3] = 0x00;
	state->reg[4] = 0xce;
	state->reg[5] = 0x54;
	state->reg[6] = 0x55;
	state->reg[7] = 0x45;
	state->reg[8] = 0x46;
	state->reg[9] = 0xbd;
	state->reg[10] = 0x11;

	state->ref_freq = 16000;

	अगर (clkभाग <= 3)
		state->reg[0x00] |= (clkभाग & 0x03);
	अगर (agcmode <= 3) अणु
		state->reg[0x03] |= (agcmode << 5);
		अगर (agcmode == 0x01)
			state->reg[0x01] |= 0x30;
	पूर्ण
	अगर (bbmode <= 3)
		state->reg[0x01] = (state->reg[0x01] & ~0x30) | (bbmode << 4);
	अगर (agcref <= 7)
		state->reg[0x03] |= agcref;
	अगर (agcset <= 31)
		state->reg[0x02] = (state->reg[0x02] & ~0x1F) | agcset | 0x40;
पूर्ण

अटल पूर्णांक attach_init(काष्ठा stv *state)
अणु
	अगर (ग_लिखो_regs(state, 0, 11))
		वापस -ENODEV;
	वापस 0;
पूर्ण

अटल व्योम release(काष्ठा dvb_frontend *fe)
अणु
	kमुक्त(fe->tuner_priv);
	fe->tuner_priv = शून्य;
पूर्ण

अटल पूर्णांक set_bandwidth(काष्ठा dvb_frontend *fe, u32 cutoff_frequency)
अणु
	काष्ठा stv *state = fe->tuner_priv;
	u32 index = (cutoff_frequency + 999999) / 1000000;
	पूर्णांक stat = 0;

	अगर (index < 6)
		index = 6;
	अगर (index > 50)
		index = 50;
	अगर ((state->reg[0x08] & ~0xFC) == ((index - 6) << 2))
		वापस 0;

	state->reg[0x08] = (state->reg[0x08] & ~0xFC) | ((index - 6) << 2);
	state->reg[0x09] = (state->reg[0x09] & ~0x0C) | 0x08;
	अगर (fe->ops.i2c_gate_ctrl)
		stat = fe->ops.i2c_gate_ctrl(fe, 1);
	अगर (!stat) अणु
		ग_लिखो_regs(state, 0x08, 2);
		रुको_क्रम_call_करोne(state, 0x08);
	पूर्ण
	अगर (fe->ops.i2c_gate_ctrl && !stat)
		fe->ops.i2c_gate_ctrl(fe, 0);
	वापस stat;
पूर्ण

अटल पूर्णांक set_lof(काष्ठा stv *state, u32 local_frequency, u32 cutoff_frequency)
अणु
	u32 index = (cutoff_frequency + 999999) / 1000000;
	u32 frequency = (local_frequency + 500) / 1000;
	u32 p = 1, psel = 0, fvco, भाग, frac;
	u8 icp, पंचांगp;

	अगर (index < 6)
		index = 6;
	अगर (index > 50)
		index = 50;

	अगर (frequency <= 1300000) अणु
		p =  4;
		psel = 1;
	पूर्ण अन्यथा अणु
		p =  2;
		psel = 0;
	पूर्ण
	fvco = frequency * p;
	भाग = fvco / state->ref_freq;
	frac = fvco % state->ref_freq;
	frac = muद_भाग32(frac, 0x40000, state->ref_freq);

	icp = 0;
	अगर (fvco < 2700000)
		icp = 0;
	अन्यथा अगर (fvco < 2950000)
		icp = 1;
	अन्यथा अगर (fvco < 3300000)
		icp = 2;
	अन्यथा अगर (fvco < 3700000)
		icp = 3;
	अन्यथा अगर (fvco < 4200000)
		icp = 5;
	अन्यथा अगर (fvco < 4800000)
		icp = 6;
	अन्यथा
		icp = 7;

	state->reg[0x02] |= 0x80; /* LNA IIP3 Mode */

	state->reg[0x03] = (state->reg[0x03] & ~0x80) | (psel << 7);
	state->reg[0x04] = (भाग & 0xFF);
	state->reg[0x05] = (((भाग >> 8) & 0x01) | ((frac & 0x7F) << 1)) & 0xff;
	state->reg[0x06] = ((frac >> 7) & 0xFF);
	state->reg[0x07] = (state->reg[0x07] & ~0x07) | ((frac >> 15) & 0x07);
	state->reg[0x07] = (state->reg[0x07] & ~0xE0) | (icp << 5);

	state->reg[0x08] = (state->reg[0x08] & ~0xFC) | ((index - 6) << 2);
	/* Start cal vco,CF */
	state->reg[0x09] = (state->reg[0x09] & ~0x0C) | 0x0C;
	ग_लिखो_regs(state, 2, 8);

	रुको_क्रम_call_करोne(state, 0x0C);

	usleep_range(10000, 12000);

	पढ़ो_reg(state, 0x03, &पंचांगp);
	अगर (पंचांगp & 0x10)	अणु
		state->reg[0x02] &= ~0x80; /* LNA NF Mode */
		ग_लिखो_regs(state, 2, 1);
	पूर्ण
	पढ़ो_reg(state, 0x08, &पंचांगp);

	state->frequency = frequency;

	वापस 0;
पूर्ण

अटल पूर्णांक set_params(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा stv *state = fe->tuner_priv;
	काष्ठा dtv_frontend_properties *p = &fe->dtv_property_cache;
	u32 freq, cutoff;
	पूर्णांक stat = 0;

	अगर (p->delivery_प्रणाली != SYS_DVBS && p->delivery_प्रणाली != SYS_DVBS2)
		वापस -EINVAL;

	freq = p->frequency * 1000;
	cutoff = 5000000 + muद_भाग32(p->symbol_rate, 135, 200);

	अगर (fe->ops.i2c_gate_ctrl)
		stat = fe->ops.i2c_gate_ctrl(fe, 1);
	अगर (!stat)
		set_lof(state, freq, cutoff);
	अगर (fe->ops.i2c_gate_ctrl && !stat)
		fe->ops.i2c_gate_ctrl(fe, 0);
	वापस 0;
पूर्ण

अटल s32 table_lookup(स्थिर काष्ठा slookup *table,
			पूर्णांक table_size, u16 reg_value)
अणु
	s32 gain;
	s32 reg_dअगरf;
	पूर्णांक imin = 0;
	पूर्णांक imax = table_size - 1;
	पूर्णांक i;

	/* Assumes Table[0].RegValue < Table[imax].RegValue */
	अगर (reg_value <= table[0].reg_value) अणु
		gain = table[0].value;
	पूर्ण अन्यथा अगर (reg_value >= table[imax].reg_value) अणु
		gain = table[imax].value;
	पूर्ण अन्यथा अणु
		जबतक ((imax - imin) > 1) अणु
			i = (imax + imin) / 2;
			अगर ((table[imin].reg_value <= reg_value) &&
			    (reg_value <= table[i].reg_value))
				imax = i;
			अन्यथा
				imin = i;
		पूर्ण
		reg_dअगरf = table[imax].reg_value - table[imin].reg_value;
		gain = table[imin].value;
		अगर (reg_dअगरf != 0)
			gain += ((s32)(reg_value - table[imin].reg_value) *
				(s32)(table[imax].value
				- table[imin].value)) / reg_dअगरf;
	पूर्ण
	वापस gain;
पूर्ण

अटल पूर्णांक get_rf_strength(काष्ठा dvb_frontend *fe, u16 *st)
अणु
	काष्ठा stv *state = fe->tuner_priv;
	u16 rfagc = *st;
	s32 gain;

	अगर ((state->reg[0x03] & 0x60) == 0) अणु
		/* RF Mode, Read AGC ADC */
		u8 reg = 0;
		पूर्णांक stat = 0;

		अगर (fe->ops.i2c_gate_ctrl)
			stat = fe->ops.i2c_gate_ctrl(fe, 1);
		अगर (!stat) अणु
			ग_लिखो_reg(state, 0x02, state->reg[0x02] | 0x20);
			पढ़ो_reg(state, 2, &reg);
			अगर (reg & 0x20)
				पढ़ो_reg(state, 2, &reg);
		पूर्ण
		अगर (fe->ops.i2c_gate_ctrl && !stat)
			fe->ops.i2c_gate_ctrl(fe, 0);

		अगर ((state->reg[0x02] & 0x80) == 0)
			/* NF */
			gain = table_lookup(lnagain_nf_lookup,
					    ARRAY_SIZE(lnagain_nf_lookup),
					    reg & 0x1F);
		अन्यथा
			/* IIP3 */
			gain = table_lookup(lnagain_iip3_lookup,
					    ARRAY_SIZE(lnagain_iip3_lookup),
					    reg & 0x1F);

		gain += table_lookup(gain_rfagc_lookup,
				     ARRAY_SIZE(gain_rfagc_lookup), rfagc);

		gain -= 2400;
	पूर्ण अन्यथा अणु
		/* Channel Mode */
		अगर ((state->reg[0x02] & 0x80) == 0) अणु
			/* NF */
			gain = table_lookup(
				gain_channel_agc_nf_lookup,
				ARRAY_SIZE(gain_channel_agc_nf_lookup), rfagc);

			gain += 600;
		पूर्ण अन्यथा अणु
			/* IIP3 */
			gain = table_lookup(
				gain_channel_agc_iip3_lookup,
				ARRAY_SIZE(gain_channel_agc_iip3_lookup),
				rfagc);
		पूर्ण
	पूर्ण

	अगर (state->frequency > 0)
		/* Tilt correction ( 0.00016 dB/MHz ) */
		gain -= ((((s32)(state->frequency / 1000) - 1550) * 2) / 12);

	/* + (BBGain * 10); */
	gain +=  (s32)((state->reg[0x01] & 0xC0) >> 6) * 600 - 1300;

	अगर (gain < 0)
		gain = 0;
	अन्यथा अगर (gain > 10000)
		gain = 10000;

	*st = 10000 - gain;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dvb_tuner_ops tuner_ops = अणु
	.info = अणु
		.name		= "ST STV6111",
		.frequency_min_hz =  950 * MHz,
		.frequency_max_hz = 2150 * MHz,
	पूर्ण,
	.set_params		= set_params,
	.release		= release,
	.get_rf_strength	= get_rf_strength,
	.set_bandwidth		= set_bandwidth,
पूर्ण;

काष्ठा dvb_frontend *stv6111_attach(काष्ठा dvb_frontend *fe,
				    काष्ठा i2c_adapter *i2c, u8 adr)
अणु
	काष्ठा stv *state;
	पूर्णांक stat = -ENODEV;
	पूर्णांक gatestat = 0;

	state = kzalloc(माप(*state), GFP_KERNEL);
	अगर (!state)
		वापस शून्य;
	state->adr = adr;
	state->i2c = i2c;
	स_नकल(&fe->ops.tuner_ops, &tuner_ops, माप(काष्ठा dvb_tuner_ops));
	init_state(state);

	अगर (fe->ops.i2c_gate_ctrl)
		gatestat = fe->ops.i2c_gate_ctrl(fe, 1);
	अगर (!gatestat)
		stat = attach_init(state);
	अगर (fe->ops.i2c_gate_ctrl && !gatestat)
		fe->ops.i2c_gate_ctrl(fe, 0);
	अगर (stat < 0) अणु
		kमुक्त(state);
		वापस शून्य;
	पूर्ण
	fe->tuner_priv = state;
	वापस fe;
पूर्ण
EXPORT_SYMBOL_GPL(stv6111_attach);

MODULE_DESCRIPTION("ST STV6111 satellite tuner driver");
MODULE_AUTHOR("Ralph Metzler, Manfred Voelkel");
MODULE_LICENSE("GPL v2");
