<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
	STB0899 Multistandard Frontend driver
	Copyright (C) Manu Abraham (abraham.manu@gmail.com)

	Copyright (C) ST Microelectronics

*/

#समावेश <linux/init.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>

#समावेश <linux/dvb/frontend.h>
#समावेश <media/dvb_frontend.h>

#समावेश "stb0899_drv.h"
#समावेश "stb0899_priv.h"
#समावेश "stb0899_reg.h"

/* Max transfer size करोne by I2C transfer functions */
#घोषणा MAX_XFER_SIZE  64

अटल अचिन्हित पूर्णांक verbose = 0;//1;
module_param(verbose, पूर्णांक, 0644);

/* C/N in dB/10, NIRM/NIRL */
अटल स्थिर काष्ठा stb0899_tab stb0899_cn_tab[] = अणु
	अणु 200,	2600 पूर्ण,
	अणु 190,	2700 पूर्ण,
	अणु 180,	2860 पूर्ण,
	अणु 170,	3020 पूर्ण,
	अणु 160,	3210 पूर्ण,
	अणु 150,	3440 पूर्ण,
	अणु 140,	3710 पूर्ण,
	अणु 130,	4010 पूर्ण,
	अणु 120,	4360 पूर्ण,
	अणु 110,	4740 पूर्ण,
	अणु 100,	5190 पूर्ण,
	अणु 90,	5670 पूर्ण,
	अणु 80,	6200 पूर्ण,
	अणु 70,	6770 पूर्ण,
	अणु 60,	7360 पूर्ण,
	अणु 50,	7970 पूर्ण,
	अणु 40,	8250 पूर्ण,
	अणु 30,	9000 पूर्ण,
	अणु 20,	9450 पूर्ण,
	अणु 15,	9600 पूर्ण,
पूर्ण;

/* DVB-S AGCIQ_VALUE vs. संकेत level in dBm/10.
 * As measured, connected to a modulator.
 * -8.0 to -50.0 dBm directly connected,
 * -52.0 to -74.8 with extra attenuation.
 * Cut-off to AGCIQ_VALUE = 0x80 below -74.8dBm.
 * Crude linear extrapolation below -84.8dBm and above -8.0dBm.
 */
अटल स्थिर काष्ठा stb0899_tab stb0899_dvbsrf_tab[] = अणु
	अणु -750,	-128 पूर्ण,
	अणु -748,	 -94 पूर्ण,
	अणु -745,	 -92 पूर्ण,
	अणु -735,	 -90 पूर्ण,
	अणु -720,	 -87 पूर्ण,
	अणु -670,	 -77 पूर्ण,
	अणु -640,	 -70 पूर्ण,
	अणु -610,	 -62 पूर्ण,
	अणु -600,	 -60 पूर्ण,
	अणु -590,	 -56 पूर्ण,
	अणु -560,	 -41 पूर्ण,
	अणु -540,	 -25 पूर्ण,
	अणु -530,	 -17 पूर्ण,
	अणु -520,	 -11 पूर्ण,
	अणु -500,	   1 पूर्ण,
	अणु -490,	   6 पूर्ण,
	अणु -480,	  10 पूर्ण,
	अणु -440,	  22 पूर्ण,
	अणु -420,	  27 पूर्ण,
	अणु -400,	  31 पूर्ण,
	अणु -380,	  34 पूर्ण,
	अणु -340,	  40 पूर्ण,
	अणु -320,	  43 पूर्ण,
	अणु -280,	  48 पूर्ण,
	अणु -250,	  52 पूर्ण,
	अणु -230,	  55 पूर्ण,
	अणु -180,	  61 पूर्ण,
	अणु -140,	  66 पूर्ण,
	अणु  -90,	  73 पूर्ण,
	अणु  -80,	  74 पूर्ण,
	अणु  500,	 127 पूर्ण
पूर्ण;

/* DVB-S2 IF_AGC_GAIN vs. संकेत level in dBm/10.
 * As measured, connected to a modulator.
 * -8.0 to -50.1 dBm directly connected,
 * -53.0 to -76.6 with extra attenuation.
 * Cut-off to IF_AGC_GAIN = 0x3fff below -76.6dBm.
 * Crude linear extrapolation below -76.6dBm and above -8.0dBm.
 */
अटल स्थिर काष्ठा stb0899_tab stb0899_dvbs2rf_tab[] = अणु
	अणु  700,	    0 पूर्ण,
	अणु  -80,	 3217 पूर्ण,
	अणु -150,	 3893 पूर्ण,
	अणु -190,	 4217 पूर्ण,
	अणु -240,	 4621 पूर्ण,
	अणु -280,	 4945 पूर्ण,
	अणु -320,	 5273 पूर्ण,
	अणु -350,	 5545 पूर्ण,
	अणु -370,	 5741 पूर्ण,
	अणु -410,	 6147 पूर्ण,
	अणु -450,	 6671 पूर्ण,
	अणु -490,	 7413 पूर्ण,
	अणु -501,	 7665 पूर्ण,
	अणु -530,	 8767 पूर्ण,
	अणु -560,	10219 पूर्ण,
	अणु -580,	10939 पूर्ण,
	अणु -590,	11518 पूर्ण,
	अणु -600,	11723 पूर्ण,
	अणु -650,	12659 पूर्ण,
	अणु -690,	13219 पूर्ण,
	अणु -730,	13645 पूर्ण,
	अणु -750,	13909 पूर्ण,
	अणु -766,	14153 पूर्ण,
	अणु -950,	16383 पूर्ण
पूर्ण;

/* DVB-S2 Es/N0 quant in dB/100 vs पढ़ो value * 100*/
अटल काष्ठा stb0899_tab stb0899_quant_tab[] = अणु
	अणु    0,	    0 पूर्ण,
	अणु    0,	  100 पूर्ण,
	अणु  600,	  200 पूर्ण,
	अणु  950,	  299 पूर्ण,
	अणु 1200,	  398 पूर्ण,
	अणु 1400,	  501 पूर्ण,
	अणु 1560,	  603 पूर्ण,
	अणु 1690,	  700 पूर्ण,
	अणु 1810,	  804 पूर्ण,
	अणु 1910,	  902 पूर्ण,
	अणु 2000,	 1000 पूर्ण,
	अणु 2080,	 1096 पूर्ण,
	अणु 2160,	 1202 पूर्ण,
	अणु 2230,	 1303 पूर्ण,
	अणु 2350,	 1496 पूर्ण,
	अणु 2410,	 1603 पूर्ण,
	अणु 2460,	 1698 पूर्ण,
	अणु 2510,	 1799 पूर्ण,
	अणु 2600,	 1995 पूर्ण,
	अणु 2650,	 2113 पूर्ण,
	अणु 2690,  2213 पूर्ण,
	अणु 2720,	 2291 पूर्ण,
	अणु 2760,	 2399 पूर्ण,
	अणु 2800,	 2512 पूर्ण,
	अणु 2860,	 2692 पूर्ण,
	अणु 2930,	 2917 पूर्ण,
	अणु 2960,	 3020 पूर्ण,
	अणु 3010,	 3199 पूर्ण,
	अणु 3040,	 3311 पूर्ण,
	अणु 3060,	 3388 पूर्ण,
	अणु 3120,	 3631 पूर्ण,
	अणु 3190,	 3936 पूर्ण,
	अणु 3400,	 5012 पूर्ण,
	अणु 3610,	 6383 पूर्ण,
	अणु 3800,	 7943 पूर्ण,
	अणु 4210,	12735 पूर्ण,
	अणु 4500,	17783 पूर्ण,
	अणु 4690,	22131 पूर्ण,
	अणु 4810,	25410 पूर्ण
पूर्ण;

/* DVB-S2 Es/N0 estimate in dB/100 vs पढ़ो value */
अटल काष्ठा stb0899_tab stb0899_est_tab[] = अणु
	अणु    0,	     0 पूर्ण,
	अणु    0,	     1 पूर्ण,
	अणु  301,	     2 पूर्ण,
	अणु 1204,	    16 पूर्ण,
	अणु 1806,	    64 पूर्ण,
	अणु 2408,	   256 पूर्ण,
	अणु 2709,	   512 पूर्ण,
	अणु 3010,	  1023 पूर्ण,
	अणु 3311,	  2046 पूर्ण,
	अणु 3612,	  4093 पूर्ण,
	अणु 3823,	  6653 पूर्ण,
	अणु 3913,	  8185 पूर्ण,
	अणु 4010,	 10233 पूर्ण,
	अणु 4107,	 12794 पूर्ण,
	अणु 4214,	 16368 पूर्ण,
	अणु 4266,	 18450 पूर्ण,
	अणु 4311,	 20464 पूर्ण,
	अणु 4353,	 22542 पूर्ण,
	अणु 4391,	 24604 पूर्ण,
	अणु 4425,	 26607 पूर्ण,
	अणु 4457,	 28642 पूर्ण,
	अणु 4487,	 30690 पूर्ण,
	अणु 4515,	 32734 पूर्ण,
	अणु 4612,	 40926 पूर्ण,
	अणु 4692,	 49204 पूर्ण,
	अणु 4816,	 65464 पूर्ण,
	अणु 4913,	 81846 पूर्ण,
	अणु 4993,	 98401 पूर्ण,
	अणु 5060,	114815 पूर्ण,
	अणु 5118,	131220 पूर्ण,
	अणु 5200,	158489 पूर्ण,
	अणु 5300,	199526 पूर्ण,
	अणु 5400,	251189 पूर्ण,
	अणु 5500,	316228 पूर्ण,
	अणु 5600,	398107 पूर्ण,
	अणु 5720,	524807 पूर्ण,
	अणु 5721,	526017 पूर्ण,
पूर्ण;

अटल पूर्णांक _stb0899_पढ़ो_reg(काष्ठा stb0899_state *state, अचिन्हित पूर्णांक reg)
अणु
	पूर्णांक ret;

	u8 b0[] = अणु reg >> 8, reg & 0xff पूर्ण;
	u8 buf;

	काष्ठा i2c_msg msg[] = अणु
		अणु
			.addr	= state->config->demod_address,
			.flags	= 0,
			.buf	= b0,
			.len	= 2
		पूर्ण,अणु
			.addr	= state->config->demod_address,
			.flags	= I2C_M_RD,
			.buf	= &buf,
			.len	= 1
		पूर्ण
	पूर्ण;

	ret = i2c_transfer(state->i2c, msg, 2);
	अगर (ret != 2) अणु
		अगर (ret != -ERESTARTSYS)
			dprपूर्णांकk(state->verbose, FE_ERROR, 1,
				"Read error, Reg=[0x%02x], Status=%d",
				reg, ret);

		वापस ret < 0 ? ret : -EREMOTEIO;
	पूर्ण
	अगर (unlikely(*state->verbose >= FE_DEBUGREG))
		dprपूर्णांकk(state->verbose, FE_ERROR, 1, "Reg=[0x%02x], data=%02x",
			reg, buf);

	वापस (अचिन्हित पूर्णांक)buf;
पूर्ण

पूर्णांक stb0899_पढ़ो_reg(काष्ठा stb0899_state *state, अचिन्हित पूर्णांक reg)
अणु
	पूर्णांक result;

	result = _stb0899_पढ़ो_reg(state, reg);
	/*
	 * Bug ID 9:
	 * access to 0xf2xx/0xf6xx
	 * must be followed by पढ़ो from 0xf2ff/0xf6ff.
	 */
	अगर ((reg != 0xf2ff) && (reg != 0xf6ff) &&
	    (((reg & 0xff00) == 0xf200) || ((reg & 0xff00) == 0xf600)))
		_stb0899_पढ़ो_reg(state, (reg | 0x00ff));

	वापस result;
पूर्ण

u32 _stb0899_पढ़ो_s2reg(काष्ठा stb0899_state *state,
			u32 stb0899_i2cdev,
			u32 stb0899_base_addr,
			u16 stb0899_reg_offset)
अणु
	पूर्णांक status;
	u32 data;
	u8 buf[7] = अणु 0 पूर्ण;
	u16 पंचांगpaddr;

	u8 buf_0[] = अणु
		GETBYTE(stb0899_i2cdev, BYTE1),		/* 0xf3	S2 Base Address (MSB)	*/
		GETBYTE(stb0899_i2cdev, BYTE0),		/* 0xfc	S2 Base Address (LSB)	*/
		GETBYTE(stb0899_base_addr, BYTE0),	/* 0x00	Base Address (LSB)	*/
		GETBYTE(stb0899_base_addr, BYTE1),	/* 0x04	Base Address (LSB)	*/
		GETBYTE(stb0899_base_addr, BYTE2),	/* 0x00	Base Address (MSB)	*/
		GETBYTE(stb0899_base_addr, BYTE3),	/* 0x00	Base Address (MSB)	*/
	पूर्ण;
	u8 buf_1[] = अणु
		0x00,	/* 0xf3	Reg Offset	*/
		0x00,	/* 0x44	Reg Offset	*/
	पूर्ण;

	काष्ठा i2c_msg msg_0 = अणु
		.addr	= state->config->demod_address,
		.flags	= 0,
		.buf	= buf_0,
		.len	= 6
	पूर्ण;

	काष्ठा i2c_msg msg_1 = अणु
		.addr	= state->config->demod_address,
		.flags	= 0,
		.buf	= buf_1,
		.len	= 2
	पूर्ण;

	काष्ठा i2c_msg msg_r = अणु
		.addr	= state->config->demod_address,
		.flags	= I2C_M_RD,
		.buf	= buf,
		.len	= 4
	पूर्ण;

	पंचांगpaddr = stb0899_reg_offset & 0xff00;
	अगर (!(stb0899_reg_offset & 0x8))
		पंचांगpaddr = stb0899_reg_offset | 0x20;

	buf_1[0] = GETBYTE(पंचांगpaddr, BYTE1);
	buf_1[1] = GETBYTE(पंचांगpaddr, BYTE0);

	status = i2c_transfer(state->i2c, &msg_0, 1);
	अगर (status < 1) अणु
		अगर (status != -ERESTARTSYS)
			prपूर्णांकk(KERN_ERR "%s ERR(1), Device=[0x%04x], Base address=[0x%08x], Offset=[0x%04x], Status=%d\n",
			       __func__, stb0899_i2cdev, stb0899_base_addr, stb0899_reg_offset, status);

		जाओ err;
	पूर्ण

	/* Dummy	*/
	status = i2c_transfer(state->i2c, &msg_1, 1);
	अगर (status < 1)
		जाओ err;

	status = i2c_transfer(state->i2c, &msg_r, 1);
	अगर (status < 1)
		जाओ err;

	buf_1[0] = GETBYTE(stb0899_reg_offset, BYTE1);
	buf_1[1] = GETBYTE(stb0899_reg_offset, BYTE0);

	/* Actual	*/
	status = i2c_transfer(state->i2c, &msg_1, 1);
	अगर (status < 1) अणु
		अगर (status != -ERESTARTSYS)
			prपूर्णांकk(KERN_ERR "%s ERR(2), Device=[0x%04x], Base address=[0x%08x], Offset=[0x%04x], Status=%d\n",
			       __func__, stb0899_i2cdev, stb0899_base_addr, stb0899_reg_offset, status);
		जाओ err;
	पूर्ण

	status = i2c_transfer(state->i2c, &msg_r, 1);
	अगर (status < 1) अणु
		अगर (status != -ERESTARTSYS)
			prपूर्णांकk(KERN_ERR "%s ERR(3), Device=[0x%04x], Base address=[0x%08x], Offset=[0x%04x], Status=%d\n",
			       __func__, stb0899_i2cdev, stb0899_base_addr, stb0899_reg_offset, status);
		वापस status < 0 ? status : -EREMOTEIO;
	पूर्ण

	data = MAKEWORD32(buf[3], buf[2], buf[1], buf[0]);
	अगर (unlikely(*state->verbose >= FE_DEBUGREG))
		prपूर्णांकk(KERN_DEBUG "%s Device=[0x%04x], Base address=[0x%08x], Offset=[0x%04x], Data=[0x%08x]\n",
		       __func__, stb0899_i2cdev, stb0899_base_addr, stb0899_reg_offset, data);

	वापस data;

err:
	वापस status < 0 ? status : -EREMOTEIO;
पूर्ण

पूर्णांक stb0899_ग_लिखो_s2reg(काष्ठा stb0899_state *state,
			u32 stb0899_i2cdev,
			u32 stb0899_base_addr,
			u16 stb0899_reg_offset,
			u32 stb0899_data)
अणु
	पूर्णांक status;

	/* Base Address Setup	*/
	u8 buf_0[] = अणु
		GETBYTE(stb0899_i2cdev, BYTE1),		/* 0xf3	S2 Base Address (MSB)	*/
		GETBYTE(stb0899_i2cdev, BYTE0),		/* 0xfc	S2 Base Address (LSB)	*/
		GETBYTE(stb0899_base_addr, BYTE0),	/* 0x00	Base Address (LSB)	*/
		GETBYTE(stb0899_base_addr, BYTE1),	/* 0x04	Base Address (LSB)	*/
		GETBYTE(stb0899_base_addr, BYTE2),	/* 0x00	Base Address (MSB)	*/
		GETBYTE(stb0899_base_addr, BYTE3),	/* 0x00	Base Address (MSB)	*/
	पूर्ण;
	u8 buf_1[] = अणु
		0x00,	/* 0xf3	Reg Offset	*/
		0x00,	/* 0x44	Reg Offset	*/
		0x00,	/* data			*/
		0x00,	/* data			*/
		0x00,	/* data			*/
		0x00,	/* data			*/
	पूर्ण;

	काष्ठा i2c_msg msg_0 = अणु
		.addr	= state->config->demod_address,
		.flags	= 0,
		.buf	= buf_0,
		.len	= 6
	पूर्ण;

	काष्ठा i2c_msg msg_1 = अणु
		.addr	= state->config->demod_address,
		.flags	= 0,
		.buf	= buf_1,
		.len	= 6
	पूर्ण;

	buf_1[0] = GETBYTE(stb0899_reg_offset, BYTE1);
	buf_1[1] = GETBYTE(stb0899_reg_offset, BYTE0);
	buf_1[2] = GETBYTE(stb0899_data, BYTE0);
	buf_1[3] = GETBYTE(stb0899_data, BYTE1);
	buf_1[4] = GETBYTE(stb0899_data, BYTE2);
	buf_1[5] = GETBYTE(stb0899_data, BYTE3);

	अगर (unlikely(*state->verbose >= FE_DEBUGREG))
		prपूर्णांकk(KERN_DEBUG "%s Device=[0x%04x], Base Address=[0x%08x], Offset=[0x%04x], Data=[0x%08x]\n",
		       __func__, stb0899_i2cdev, stb0899_base_addr, stb0899_reg_offset, stb0899_data);

	status = i2c_transfer(state->i2c, &msg_0, 1);
	अगर (unlikely(status < 1)) अणु
		अगर (status != -ERESTARTSYS)
			prपूर्णांकk(KERN_ERR "%s ERR (1), Device=[0x%04x], Base Address=[0x%08x], Offset=[0x%04x], Data=[0x%08x], status=%d\n",
			       __func__, stb0899_i2cdev, stb0899_base_addr, stb0899_reg_offset, stb0899_data, status);
		जाओ err;
	पूर्ण
	status = i2c_transfer(state->i2c, &msg_1, 1);
	अगर (unlikely(status < 1)) अणु
		अगर (status != -ERESTARTSYS)
			prपूर्णांकk(KERN_ERR "%s ERR (2), Device=[0x%04x], Base Address=[0x%08x], Offset=[0x%04x], Data=[0x%08x], status=%d\n",
			       __func__, stb0899_i2cdev, stb0899_base_addr, stb0899_reg_offset, stb0899_data, status);

		वापस status < 0 ? status : -EREMOTEIO;
	पूर्ण

	वापस 0;

err:
	वापस status < 0 ? status : -EREMOTEIO;
पूर्ण

पूर्णांक stb0899_पढ़ो_regs(काष्ठा stb0899_state *state, अचिन्हित पूर्णांक reg, u8 *buf, u32 count)
अणु
	पूर्णांक status;

	u8 b0[] = अणु reg >> 8, reg & 0xff पूर्ण;

	काष्ठा i2c_msg msg[] = अणु
		अणु
			.addr	= state->config->demod_address,
			.flags	= 0,
			.buf	= b0,
			.len	= 2
		पूर्ण,अणु
			.addr	= state->config->demod_address,
			.flags	= I2C_M_RD,
			.buf	= buf,
			.len	= count
		पूर्ण
	पूर्ण;

	status = i2c_transfer(state->i2c, msg, 2);
	अगर (status != 2) अणु
		अगर (status != -ERESTARTSYS)
			prपूर्णांकk(KERN_ERR "%s Read error, Reg=[0x%04x], Count=%u, Status=%d\n",
			       __func__, reg, count, status);
		जाओ err;
	पूर्ण
	/*
	 * Bug ID 9:
	 * access to 0xf2xx/0xf6xx
	 * must be followed by पढ़ो from 0xf2ff/0xf6ff.
	 */
	अगर ((reg != 0xf2ff) && (reg != 0xf6ff) &&
	    (((reg & 0xff00) == 0xf200) || ((reg & 0xff00) == 0xf600)))
		_stb0899_पढ़ो_reg(state, (reg | 0x00ff));

	dprपूर्णांकk(state->verbose, FE_DEBUGREG, 1,
		"%s [0x%04x]: %*ph", __func__, reg, count, buf);

	वापस 0;
err:
	वापस status < 0 ? status : -EREMOTEIO;
पूर्ण

पूर्णांक stb0899_ग_लिखो_regs(काष्ठा stb0899_state *state, अचिन्हित पूर्णांक reg, u8 *data, u32 count)
अणु
	पूर्णांक ret;
	u8 buf[MAX_XFER_SIZE];
	काष्ठा i2c_msg i2c_msg = अणु
		.addr	= state->config->demod_address,
		.flags	= 0,
		.buf	= buf,
		.len	= 2 + count
	पूर्ण;

	अगर (2 + count > माप(buf)) अणु
		prपूर्णांकk(KERN_WARNING
		       "%s: i2c wr reg=%04x: len=%d is too big!\n",
		       KBUILD_MODNAME, reg, count);
		वापस -EINVAL;
	पूर्ण

	buf[0] = reg >> 8;
	buf[1] = reg & 0xff;
	स_नकल(&buf[2], data, count);

	dprपूर्णांकk(state->verbose, FE_DEBUGREG, 1,
		"%s [0x%04x]: %*ph", __func__, reg, count, data);
	ret = i2c_transfer(state->i2c, &i2c_msg, 1);

	/*
	 * Bug ID 9:
	 * access to 0xf2xx/0xf6xx
	 * must be followed by पढ़ो from 0xf2ff/0xf6ff.
	 */
	अगर ((((reg & 0xff00) == 0xf200) || ((reg & 0xff00) == 0xf600)))
		stb0899_पढ़ो_reg(state, (reg | 0x00ff));

	अगर (ret != 1) अणु
		अगर (ret != -ERESTARTSYS)
			dprपूर्णांकk(state->verbose, FE_ERROR, 1, "Reg=[0x%04x], Data=[0x%02x ...], Count=%u, Status=%d",
				reg, data[0], count, ret);
		वापस ret < 0 ? ret : -EREMOTEIO;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक stb0899_ग_लिखो_reg(काष्ठा stb0899_state *state, अचिन्हित पूर्णांक reg, u8 data)
अणु
	u8 पंचांगp = data;
	वापस stb0899_ग_लिखो_regs(state, reg, &पंचांगp, 1);
पूर्ण

/*
 * stb0899_get_mclk
 * Get STB0899 master घड़ी frequency
 * ExtClk: बाह्यal घड़ी frequency (Hz)
 */
अटल u32 stb0899_get_mclk(काष्ठा stb0899_state *state)
अणु
	u32 mclk = 0, भाग = 0;

	भाग = stb0899_पढ़ो_reg(state, STB0899_NCOARSE);
	mclk = (भाग + 1) * state->config->xtal_freq / 6;
	dprपूर्णांकk(state->verbose, FE_DEBUG, 1, "div=%d, mclk=%d", भाग, mclk);

	वापस mclk;
पूर्ण

/*
 * stb0899_set_mclk
 * Set STB0899 master Clock frequency
 * Mclk: demodulator master घड़ी
 * ExtClk: बाह्यal घड़ी frequency (Hz)
 */
अटल व्योम stb0899_set_mclk(काष्ठा stb0899_state *state, u32 Mclk)
अणु
	काष्ठा stb0899_पूर्णांकernal *पूर्णांकernal = &state->पूर्णांकernal;
	u8 mभाग = 0;

	dprपूर्णांकk(state->verbose, FE_DEBUG, 1, "state->config=%p", state->config);
	mभाग = ((6 * Mclk) / state->config->xtal_freq) - 1;
	dprपूर्णांकk(state->verbose, FE_DEBUG, 1, "mdiv=%d", mभाग);

	stb0899_ग_लिखो_reg(state, STB0899_NCOARSE, mभाग);
	पूर्णांकernal->master_clk = stb0899_get_mclk(state);

	dprपूर्णांकk(state->verbose, FE_DEBUG, 1, "MasterCLOCK=%d", पूर्णांकernal->master_clk);
पूर्ण

अटल पूर्णांक stb0899_postproc(काष्ठा stb0899_state *state, u8 ctl, पूर्णांक enable)
अणु
	काष्ठा stb0899_config *config		= state->config;
	स्थिर काष्ठा stb0899_postproc *postproc	= config->postproc;

	/* post process event */
	अगर (postproc) अणु
		अगर (enable) अणु
			अगर (postproc[ctl].level == STB0899_GPIOPULLUP)
				stb0899_ग_लिखो_reg(state, postproc[ctl].gpio, 0x02);
			अन्यथा
				stb0899_ग_लिखो_reg(state, postproc[ctl].gpio, 0x82);
		पूर्ण अन्यथा अणु
			अगर (postproc[ctl].level == STB0899_GPIOPULLUP)
				stb0899_ग_लिखो_reg(state, postproc[ctl].gpio, 0x82);
			अन्यथा
				stb0899_ग_लिखो_reg(state, postproc[ctl].gpio, 0x02);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम stb0899_detach(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा stb0899_state *state = fe->demodulator_priv;

	/* post process event */
	stb0899_postproc(state, STB0899_POSTPROC_GPIO_POWER, 0);
पूर्ण

अटल व्योम stb0899_release(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा stb0899_state *state = fe->demodulator_priv;

	dprपूर्णांकk(state->verbose, FE_DEBUG, 1, "Release Frontend");
	kमुक्त(state);
पूर्ण

/*
 * stb0899_get_alpha
 * वापस: rolloff
 */
अटल पूर्णांक stb0899_get_alpha(काष्ठा stb0899_state *state)
अणु
	u8 mode_coeff;

	mode_coeff = stb0899_पढ़ो_reg(state, STB0899_DEMOD);

	अगर (STB0899_GETFIELD(MODECOEFF, mode_coeff) == 1)
		वापस 20;
	अन्यथा
		वापस 35;
पूर्ण

/*
 * stb0899_init_calc
 */
अटल व्योम stb0899_init_calc(काष्ठा stb0899_state *state)
अणु
	काष्ठा stb0899_पूर्णांकernal *पूर्णांकernal = &state->पूर्णांकernal;
	पूर्णांक master_clk;
	u8 agc[2];
	u32 reg;

	/* Read रेजिस्टरs (in burst mode)	*/
	stb0899_पढ़ो_regs(state, STB0899_AGC1REF, agc, 2); /* AGC1R and AGC2O	*/

	/* Initial calculations	*/
	master_clk			= stb0899_get_mclk(state);
	पूर्णांकernal->t_agc1		= 0;
	पूर्णांकernal->t_agc2		= 0;
	पूर्णांकernal->master_clk		= master_clk;
	पूर्णांकernal->mclk			= master_clk / 65536L;
	पूर्णांकernal->rolloff		= stb0899_get_alpha(state);

	/* DVBS2 Initial calculations	*/
	/* Set AGC value to the middle	*/
	पूर्णांकernal->agc_gain		= 8154;
	reg = STB0899_READ_S2REG(STB0899_S2DEMOD, IF_AGC_CNTRL);
	STB0899_SETFIELD_VAL(IF_GAIN_INIT, reg, पूर्णांकernal->agc_gain);
	stb0899_ग_लिखो_s2reg(state, STB0899_S2DEMOD, STB0899_BASE_IF_AGC_CNTRL, STB0899_OFF0_IF_AGC_CNTRL, reg);

	reg = STB0899_READ_S2REG(STB0899_S2DEMOD, RRC_ALPHA);
	पूर्णांकernal->rrc_alpha		= STB0899_GETFIELD(RRC_ALPHA, reg);

	पूर्णांकernal->center_freq		= 0;
	पूर्णांकernal->av_frame_coarse	= 10;
	पूर्णांकernal->av_frame_fine		= 20;
	पूर्णांकernal->step_size		= 2;
/*
	अगर ((pParams->SpectralInv == FE_IQ_NORMAL) || (pParams->SpectralInv == FE_IQ_AUTO))
		pParams->IQLocked = 0;
	अन्यथा
		pParams->IQLocked = 1;
*/
पूर्ण

अटल पूर्णांक stb0899_रुको_diseqc_fअगरo_empty(काष्ठा stb0899_state *state, पूर्णांक समयout)
अणु
	u8 reg = 0;
	अचिन्हित दीर्घ start = jअगरfies;

	जबतक (1) अणु
		reg = stb0899_पढ़ो_reg(state, STB0899_DISSTATUS);
		अगर (!STB0899_GETFIELD(FIFOFULL, reg))
			अवरोध;
		अगर (समय_after(jअगरfies, start + समयout)) अणु
			dprपूर्णांकk(state->verbose, FE_ERROR, 1, "timed out !!");
			वापस -ETIMEDOUT;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक stb0899_send_diseqc_msg(काष्ठा dvb_frontend *fe, काष्ठा dvb_diseqc_master_cmd *cmd)
अणु
	काष्ठा stb0899_state *state = fe->demodulator_priv;
	u8 reg, i;

	अगर (cmd->msg_len > माप(cmd->msg))
		वापस -EINVAL;

	/* enable FIFO preअक्षरge	*/
	reg = stb0899_पढ़ो_reg(state, STB0899_DISCNTRL1);
	STB0899_SETFIELD_VAL(DISPRECHARGE, reg, 1);
	stb0899_ग_लिखो_reg(state, STB0899_DISCNTRL1, reg);
	क्रम (i = 0; i < cmd->msg_len; i++) अणु
		/* रुको क्रम FIFO empty	*/
		अगर (stb0899_रुको_diseqc_fअगरo_empty(state, 100) < 0)
			वापस -ETIMEDOUT;

		stb0899_ग_लिखो_reg(state, STB0899_DISFIFO, cmd->msg[i]);
	पूर्ण
	reg = stb0899_पढ़ो_reg(state, STB0899_DISCNTRL1);
	STB0899_SETFIELD_VAL(DISPRECHARGE, reg, 0);
	stb0899_ग_लिखो_reg(state, STB0899_DISCNTRL1, reg);
	msleep(100);
	वापस 0;
पूर्ण

अटल पूर्णांक stb0899_रुको_diseqc_rxidle(काष्ठा stb0899_state *state, पूर्णांक समयout)
अणु
	u8 reg = 0;
	अचिन्हित दीर्घ start = jअगरfies;

	जबतक (!STB0899_GETFIELD(RXEND, reg)) अणु
		reg = stb0899_पढ़ो_reg(state, STB0899_DISRX_ST0);
		अगर (समय_after(jअगरfies, start + समयout)) अणु
			dprपूर्णांकk(state->verbose, FE_ERROR, 1, "timed out!!");
			वापस -ETIMEDOUT;
		पूर्ण
		msleep(10);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक stb0899_recv_slave_reply(काष्ठा dvb_frontend *fe, काष्ठा dvb_diseqc_slave_reply *reply)
अणु
	काष्ठा stb0899_state *state = fe->demodulator_priv;
	u8 reg, length = 0, i;
	पूर्णांक result;

	अगर (stb0899_रुको_diseqc_rxidle(state, 100) < 0)
		वापस -ETIMEDOUT;

	reg = stb0899_पढ़ो_reg(state, STB0899_DISRX_ST0);
	अगर (STB0899_GETFIELD(RXEND, reg)) अणु

		reg = stb0899_पढ़ो_reg(state, STB0899_DISRX_ST1);
		length = STB0899_GETFIELD(FIFOBYTENBR, reg);

		अगर (length > माप (reply->msg)) अणु
			result = -EOVERFLOW;
			जाओ निकास;
		पूर्ण
		reply->msg_len = length;

		/* extract data */
		क्रम (i = 0; i < length; i++)
			reply->msg[i] = stb0899_पढ़ो_reg(state, STB0899_DISFIFO);
	पूर्ण

	वापस 0;
निकास:

	वापस result;
पूर्ण

अटल पूर्णांक stb0899_रुको_diseqc_txidle(काष्ठा stb0899_state *state, पूर्णांक समयout)
अणु
	u8 reg = 0;
	अचिन्हित दीर्घ start = jअगरfies;

	जबतक (!STB0899_GETFIELD(TXIDLE, reg)) अणु
		reg = stb0899_पढ़ो_reg(state, STB0899_DISSTATUS);
		अगर (समय_after(jअगरfies, start + समयout)) अणु
			dprपूर्णांकk(state->verbose, FE_ERROR, 1, "timed out!!");
			वापस -ETIMEDOUT;
		पूर्ण
		msleep(10);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक stb0899_send_diseqc_burst(काष्ठा dvb_frontend *fe,
				     क्रमागत fe_sec_mini_cmd burst)
अणु
	काष्ठा stb0899_state *state = fe->demodulator_priv;
	u8 reg, old_state;

	/* रुको क्रम diseqc idle	*/
	अगर (stb0899_रुको_diseqc_txidle(state, 100) < 0)
		वापस -ETIMEDOUT;

	reg = stb0899_पढ़ो_reg(state, STB0899_DISCNTRL1);
	old_state = reg;
	/* set to burst mode	*/
	STB0899_SETFIELD_VAL(DISEQCMODE, reg, 0x03);
	STB0899_SETFIELD_VAL(DISPRECHARGE, reg, 0x01);
	stb0899_ग_लिखो_reg(state, STB0899_DISCNTRL1, reg);
	चयन (burst) अणु
	हाल SEC_MINI_A:
		/* unmodulated	*/
		stb0899_ग_लिखो_reg(state, STB0899_DISFIFO, 0x00);
		अवरोध;
	हाल SEC_MINI_B:
		/* modulated	*/
		stb0899_ग_लिखो_reg(state, STB0899_DISFIFO, 0xff);
		अवरोध;
	पूर्ण
	reg = stb0899_पढ़ो_reg(state, STB0899_DISCNTRL1);
	STB0899_SETFIELD_VAL(DISPRECHARGE, reg, 0x00);
	stb0899_ग_लिखो_reg(state, STB0899_DISCNTRL1, reg);
	/* रुको क्रम diseqc idle	*/
	अगर (stb0899_रुको_diseqc_txidle(state, 100) < 0)
		वापस -ETIMEDOUT;

	/* restore state	*/
	stb0899_ग_लिखो_reg(state, STB0899_DISCNTRL1, old_state);

	वापस 0;
पूर्ण

अटल पूर्णांक stb0899_diseqc_init(काष्ठा stb0899_state *state)
अणु
/*
	काष्ठा dvb_diseqc_slave_reply rx_data;
*/
	u8 f22_tx, reg;

	u32 mclk, tx_freq = 22000;/* count = 0, i; */
	reg = stb0899_पढ़ो_reg(state, STB0899_DISCNTRL2);
	STB0899_SETFIELD_VAL(ONECHIP_TRX, reg, 0);
	stb0899_ग_लिखो_reg(state, STB0899_DISCNTRL2, reg);

	/* disable Tx spy	*/
	reg = stb0899_पढ़ो_reg(state, STB0899_DISCNTRL1);
	STB0899_SETFIELD_VAL(DISEQCRESET, reg, 1);
	stb0899_ग_लिखो_reg(state, STB0899_DISCNTRL1, reg);

	reg = stb0899_पढ़ो_reg(state, STB0899_DISCNTRL1);
	STB0899_SETFIELD_VAL(DISEQCRESET, reg, 0);
	stb0899_ग_लिखो_reg(state, STB0899_DISCNTRL1, reg);

	mclk = stb0899_get_mclk(state);
	f22_tx = mclk / (tx_freq * 32);
	stb0899_ग_लिखो_reg(state, STB0899_DISF22, f22_tx); /* DiSEqC Tx freq	*/
	state->rx_freq = 20000;

	वापस 0;
पूर्ण

अटल पूर्णांक stb0899_sleep(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा stb0899_state *state = fe->demodulator_priv;
/*
	u8 reg;
*/
	dprपूर्णांकk(state->verbose, FE_DEBUG, 1, "Going to Sleep .. (Really tired .. :-))");
	/* post process event */
	stb0899_postproc(state, STB0899_POSTPROC_GPIO_POWER, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक stb0899_wakeup(काष्ठा dvb_frontend *fe)
अणु
	पूर्णांक rc;
	काष्ठा stb0899_state *state = fe->demodulator_priv;

	अगर ((rc = stb0899_ग_लिखो_reg(state, STB0899_SYNTCTRL, STB0899_SELOSCI)))
		वापस rc;
	/* Activate all घड़ीs; DVB-S2 रेजिस्टरs are inaccessible otherwise. */
	अगर ((rc = stb0899_ग_लिखो_reg(state, STB0899_STOPCLK1, 0x00)))
		वापस rc;
	अगर ((rc = stb0899_ग_लिखो_reg(state, STB0899_STOPCLK2, 0x00)))
		वापस rc;

	/* post process event */
	stb0899_postproc(state, STB0899_POSTPROC_GPIO_POWER, 1);

	वापस 0;
पूर्ण

अटल पूर्णांक stb0899_init(काष्ठा dvb_frontend *fe)
अणु
	पूर्णांक i;
	काष्ठा stb0899_state *state = fe->demodulator_priv;
	काष्ठा stb0899_config *config = state->config;

	dprपूर्णांकk(state->verbose, FE_DEBUG, 1, "Initializing STB0899 ... ");

	/* init device		*/
	dprपूर्णांकk(state->verbose, FE_DEBUG, 1, "init device");
	क्रम (i = 0; config->init_dev[i].address != 0xffff; i++)
		stb0899_ग_लिखो_reg(state, config->init_dev[i].address, config->init_dev[i].data);

	dprपूर्णांकk(state->verbose, FE_DEBUG, 1, "init S2 demod");
	/* init S2 demod	*/
	क्रम (i = 0; config->init_s2_demod[i].offset != 0xffff; i++)
		stb0899_ग_लिखो_s2reg(state, STB0899_S2DEMOD,
				    config->init_s2_demod[i].base_address,
				    config->init_s2_demod[i].offset,
				    config->init_s2_demod[i].data);

	dprपूर्णांकk(state->verbose, FE_DEBUG, 1, "init S1 demod");
	/* init S1 demod	*/
	क्रम (i = 0; config->init_s1_demod[i].address != 0xffff; i++)
		stb0899_ग_लिखो_reg(state, config->init_s1_demod[i].address, config->init_s1_demod[i].data);

	dprपूर्णांकk(state->verbose, FE_DEBUG, 1, "init S2 FEC");
	/* init S2 fec		*/
	क्रम (i = 0; config->init_s2_fec[i].offset != 0xffff; i++)
		stb0899_ग_लिखो_s2reg(state, STB0899_S2FEC,
				    config->init_s2_fec[i].base_address,
				    config->init_s2_fec[i].offset,
				    config->init_s2_fec[i].data);

	dprपूर्णांकk(state->verbose, FE_DEBUG, 1, "init TST");
	/* init test		*/
	क्रम (i = 0; config->init_tst[i].address != 0xffff; i++)
		stb0899_ग_लिखो_reg(state, config->init_tst[i].address, config->init_tst[i].data);

	stb0899_init_calc(state);
	stb0899_diseqc_init(state);

	वापस 0;
पूर्ण

अटल पूर्णांक stb0899_table_lookup(स्थिर काष्ठा stb0899_tab *tab, पूर्णांक max, पूर्णांक val)
अणु
	पूर्णांक res = 0;
	पूर्णांक min = 0, med;

	अगर (val < tab[min].पढ़ो)
		res = tab[min].real;
	अन्यथा अगर (val >= tab[max].पढ़ो)
		res = tab[max].real;
	अन्यथा अणु
		जबतक ((max - min) > 1) अणु
			med = (max + min) / 2;
			अगर (val >= tab[min].पढ़ो && val < tab[med].पढ़ो)
				max = med;
			अन्यथा
				min = med;
		पूर्ण
		res = ((val - tab[min].पढ़ो) *
		       (tab[max].real - tab[min].real) /
		       (tab[max].पढ़ो - tab[min].पढ़ो)) +
			tab[min].real;
	पूर्ण

	वापस res;
पूर्ण

अटल पूर्णांक stb0899_पढ़ो_संकेत_strength(काष्ठा dvb_frontend *fe, u16 *strength)
अणु
	काष्ठा stb0899_state *state		= fe->demodulator_priv;
	काष्ठा stb0899_पूर्णांकernal *पूर्णांकernal	= &state->पूर्णांकernal;

	पूर्णांक val;
	u32 reg;
	*strength = 0;
	चयन (state->delsys) अणु
	हाल SYS_DVBS:
	हाल SYS_DSS:
		अगर (पूर्णांकernal->lock) अणु
			reg  = stb0899_पढ़ो_reg(state, STB0899_VSTATUS);
			अगर (STB0899_GETFIELD(VSTATUS_LOCKEDVIT, reg)) अणु

				reg = stb0899_पढ़ो_reg(state, STB0899_AGCIQIN);
				val = (s32)(s8)STB0899_GETFIELD(AGCIQVALUE, reg);

				*strength = stb0899_table_lookup(stb0899_dvbsrf_tab, ARRAY_SIZE(stb0899_dvbsrf_tab) - 1, val);
				*strength += 750;
				dprपूर्णांकk(state->verbose, FE_DEBUG, 1, "AGCIQVALUE = 0x%02x, C = %d * 0.1 dBm",
					val & 0xff, *strength);
			पूर्ण
		पूर्ण
		अवरोध;
	हाल SYS_DVBS2:
		अगर (पूर्णांकernal->lock) अणु
			reg = STB0899_READ_S2REG(STB0899_S2DEMOD, IF_AGC_GAIN);
			val = STB0899_GETFIELD(IF_AGC_GAIN, reg);

			*strength = stb0899_table_lookup(stb0899_dvbs2rf_tab, ARRAY_SIZE(stb0899_dvbs2rf_tab) - 1, val);
			*strength += 950;
			dprपूर्णांकk(state->verbose, FE_DEBUG, 1, "IF_AGC_GAIN = 0x%04x, C = %d * 0.1 dBm",
				val & 0x3fff, *strength);
		पूर्ण
		अवरोध;
	शेष:
		dprपूर्णांकk(state->verbose, FE_DEBUG, 1, "Unsupported delivery system");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक stb0899_पढ़ो_snr(काष्ठा dvb_frontend *fe, u16 *snr)
अणु
	काष्ठा stb0899_state *state		= fe->demodulator_priv;
	काष्ठा stb0899_पूर्णांकernal *पूर्णांकernal	= &state->पूर्णांकernal;

	अचिन्हित पूर्णांक val, quant, quantn = -1, est, estn = -1;
	u8 buf[2];
	u32 reg;

	*snr = 0;
	reg  = stb0899_पढ़ो_reg(state, STB0899_VSTATUS);
	चयन (state->delsys) अणु
	हाल SYS_DVBS:
	हाल SYS_DSS:
		अगर (पूर्णांकernal->lock) अणु
			अगर (STB0899_GETFIELD(VSTATUS_LOCKEDVIT, reg)) अणु

				stb0899_पढ़ो_regs(state, STB0899_NIRM, buf, 2);
				val = MAKEWORD16(buf[0], buf[1]);

				*snr = stb0899_table_lookup(stb0899_cn_tab, ARRAY_SIZE(stb0899_cn_tab) - 1, val);
				dprपूर्णांकk(state->verbose, FE_DEBUG, 1, "NIR = 0x%02x%02x = %u, C/N = %d * 0.1 dBm\n",
					buf[0], buf[1], val, *snr);
			पूर्ण
		पूर्ण
		अवरोध;
	हाल SYS_DVBS2:
		अगर (पूर्णांकernal->lock) अणु
			reg = STB0899_READ_S2REG(STB0899_S2DEMOD, UWP_CNTRL1);
			quant = STB0899_GETFIELD(UWP_ESN0_QUANT, reg);
			reg = STB0899_READ_S2REG(STB0899_S2DEMOD, UWP_STAT2);
			est = STB0899_GETFIELD(ESN0_EST, reg);
			अगर (est == 1)
				val = 301; /* C/N = 30.1 dB */
			अन्यथा अगर (est == 2)
				val = 270; /* C/N = 27.0 dB */
			अन्यथा अणु
				/* quantn = 100 * log(quant^2) */
				quantn = stb0899_table_lookup(stb0899_quant_tab, ARRAY_SIZE(stb0899_quant_tab) - 1, quant * 100);
				/* estn = 100 * log(est) */
				estn = stb0899_table_lookup(stb0899_est_tab, ARRAY_SIZE(stb0899_est_tab) - 1, est);
				/* snr(dBm/10) = -10*(log(est)-log(quant^2)) => snr(dBm/10) = (100*log(quant^2)-100*log(est))/10 */
				val = (quantn - estn) / 10;
			पूर्ण
			*snr = val;
			dprपूर्णांकk(state->verbose, FE_DEBUG, 1, "Es/N0 quant = %d (%d) estimate = %u (%d), C/N = %d * 0.1 dBm",
				quant, quantn, est, estn, val);
		पूर्ण
		अवरोध;
	शेष:
		dprपूर्णांकk(state->verbose, FE_DEBUG, 1, "Unsupported delivery system");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक stb0899_पढ़ो_status(काष्ठा dvb_frontend *fe, क्रमागत fe_status *status)
अणु
	काष्ठा stb0899_state *state		= fe->demodulator_priv;
	काष्ठा stb0899_पूर्णांकernal *पूर्णांकernal	= &state->पूर्णांकernal;
	u8 reg;
	*status = 0;

	चयन (state->delsys) अणु
	हाल SYS_DVBS:
	हाल SYS_DSS:
		dprपूर्णांकk(state->verbose, FE_DEBUG, 1, "Delivery system DVB-S/DSS");
		अगर (पूर्णांकernal->lock) अणु
			reg  = stb0899_पढ़ो_reg(state, STB0899_VSTATUS);
			अगर (STB0899_GETFIELD(VSTATUS_LOCKEDVIT, reg)) अणु
				dprपूर्णांकk(state->verbose, FE_DEBUG, 1, "--------> FE_HAS_CARRIER | FE_HAS_LOCK");
				*status |= FE_HAS_SIGNAL | FE_HAS_CARRIER | FE_HAS_LOCK;

				reg = stb0899_पढ़ो_reg(state, STB0899_PLPARM);
				अगर (STB0899_GETFIELD(VITCURPUN, reg)) अणु
					dprपूर्णांकk(state->verbose, FE_DEBUG, 1, "--------> FE_HAS_VITERBI | FE_HAS_SYNC");
					*status |= FE_HAS_VITERBI | FE_HAS_SYNC;
					/* post process event */
					stb0899_postproc(state, STB0899_POSTPROC_GPIO_LOCK, 1);
				पूर्ण
			पूर्ण
		पूर्ण
		अवरोध;
	हाल SYS_DVBS2:
		dprपूर्णांकk(state->verbose, FE_DEBUG, 1, "Delivery system DVB-S2");
		अगर (पूर्णांकernal->lock) अणु
			reg = STB0899_READ_S2REG(STB0899_S2DEMOD, DMD_STAT2);
			अगर (STB0899_GETFIELD(UWP_LOCK, reg) && STB0899_GETFIELD(CSM_LOCK, reg)) अणु
				*status |= FE_HAS_CARRIER;
				dprपूर्णांकk(state->verbose, FE_DEBUG, 1,
					"UWP & CSM Lock ! ---> DVB-S2 FE_HAS_CARRIER");

				reg = stb0899_पढ़ो_reg(state, STB0899_CFGPDELSTATUS1);
				अगर (STB0899_GETFIELD(CFGPDELSTATUS_LOCK, reg)) अणु
					*status |= FE_HAS_LOCK;
					dprपूर्णांकk(state->verbose, FE_DEBUG, 1,
						"Packet Delineator Locked ! -----> DVB-S2 FE_HAS_LOCK");

				पूर्ण
				अगर (STB0899_GETFIELD(CONTINUOUS_STREAM, reg)) अणु
					*status |= FE_HAS_VITERBI;
					dprपूर्णांकk(state->verbose, FE_DEBUG, 1,
						"Packet Delineator found VITERBI ! -----> DVB-S2 FE_HAS_VITERBI");
				पूर्ण
				अगर (STB0899_GETFIELD(ACCEPTED_STREAM, reg)) अणु
					*status |= FE_HAS_SYNC;
					dprपूर्णांकk(state->verbose, FE_DEBUG, 1,
						"Packet Delineator found SYNC ! -----> DVB-S2 FE_HAS_SYNC");
					/* post process event */
					stb0899_postproc(state, STB0899_POSTPROC_GPIO_LOCK, 1);
				पूर्ण
			पूर्ण
		पूर्ण
		अवरोध;
	शेष:
		dprपूर्णांकk(state->verbose, FE_DEBUG, 1, "Unsupported delivery system");
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * stb0899_get_error
 * viterbi error क्रम DVB-S/DSS
 * packet error क्रम DVB-S2
 * Bit Error Rate or Packet Error Rate * 10 ^ 7
 */
अटल पूर्णांक stb0899_पढ़ो_ber(काष्ठा dvb_frontend *fe, u32 *ber)
अणु
	काष्ठा stb0899_state *state		= fe->demodulator_priv;
	काष्ठा stb0899_पूर्णांकernal *पूर्णांकernal	= &state->पूर्णांकernal;

	u8  lsb, msb;

	*ber = 0;

	चयन (state->delsys) अणु
	हाल SYS_DVBS:
	हाल SYS_DSS:
		अगर (पूर्णांकernal->lock) अणु
			lsb = stb0899_पढ़ो_reg(state, STB0899_ECNT1L);
			msb = stb0899_पढ़ो_reg(state, STB0899_ECNT1M);
			*ber = MAKEWORD16(msb, lsb);
			/* Viterbi Check	*/
			अगर (STB0899_GETFIELD(VSTATUS_PRFVIT, पूर्णांकernal->v_status)) अणु
				/* Error Rate		*/
				*ber *= 9766;
				/* ber = ber * 10 ^ 7	*/
				*ber /= (-1 + (1 << (2 * STB0899_GETFIELD(NOE, पूर्णांकernal->err_ctrl))));
				*ber /= 8;
			पूर्ण
		पूर्ण
		अवरोध;
	हाल SYS_DVBS2:
		अगर (पूर्णांकernal->lock) अणु
			lsb = stb0899_पढ़ो_reg(state, STB0899_ECNT1L);
			msb = stb0899_पढ़ो_reg(state, STB0899_ECNT1M);
			*ber = MAKEWORD16(msb, lsb);
			/* ber = ber * 10 ^ 7	*/
			*ber *= 10000000;
			*ber /= (-1 + (1 << (4 + 2 * STB0899_GETFIELD(NOE, पूर्णांकernal->err_ctrl))));
		पूर्ण
		अवरोध;
	शेष:
		dprपूर्णांकk(state->verbose, FE_DEBUG, 1, "Unsupported delivery system");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक stb0899_set_voltage(काष्ठा dvb_frontend *fe,
			       क्रमागत fe_sec_voltage voltage)
अणु
	काष्ठा stb0899_state *state = fe->demodulator_priv;

	चयन (voltage) अणु
	हाल SEC_VOLTAGE_13:
		stb0899_ग_लिखो_reg(state, STB0899_GPIO00CFG, 0x82);
		stb0899_ग_लिखो_reg(state, STB0899_GPIO01CFG, 0x02);
		stb0899_ग_लिखो_reg(state, STB0899_GPIO02CFG, 0x00);
		अवरोध;
	हाल SEC_VOLTAGE_18:
		stb0899_ग_लिखो_reg(state, STB0899_GPIO00CFG, 0x02);
		stb0899_ग_लिखो_reg(state, STB0899_GPIO01CFG, 0x02);
		stb0899_ग_लिखो_reg(state, STB0899_GPIO02CFG, 0x82);
		अवरोध;
	हाल SEC_VOLTAGE_OFF:
		stb0899_ग_लिखो_reg(state, STB0899_GPIO00CFG, 0x82);
		stb0899_ग_लिखो_reg(state, STB0899_GPIO01CFG, 0x82);
		stb0899_ग_लिखो_reg(state, STB0899_GPIO02CFG, 0x82);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक stb0899_set_tone(काष्ठा dvb_frontend *fe, क्रमागत fe_sec_tone_mode tone)
अणु
	काष्ठा stb0899_state *state = fe->demodulator_priv;
	काष्ठा stb0899_पूर्णांकernal *पूर्णांकernal = &state->पूर्णांकernal;

	u8 भाग, reg;

	/* रुको क्रम diseqc idle	*/
	अगर (stb0899_रुको_diseqc_txidle(state, 100) < 0)
		वापस -ETIMEDOUT;

	चयन (tone) अणु
	हाल SEC_TONE_ON:
		भाग = (पूर्णांकernal->master_clk / 100) / 5632;
		भाग = (भाग + 5) / 10;
		stb0899_ग_लिखो_reg(state, STB0899_DISEQCOCFG, 0x66);
		reg = stb0899_पढ़ो_reg(state, STB0899_ACRPRESC);
		STB0899_SETFIELD_VAL(ACRPRESC, reg, 0x03);
		stb0899_ग_लिखो_reg(state, STB0899_ACRPRESC, reg);
		stb0899_ग_लिखो_reg(state, STB0899_ACRDIV1, भाग);
		अवरोध;
	हाल SEC_TONE_OFF:
		stb0899_ग_लिखो_reg(state, STB0899_DISEQCOCFG, 0x20);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक stb0899_i2c_gate_ctrl(काष्ठा dvb_frontend *fe, पूर्णांक enable)
अणु
	पूर्णांक i2c_stat;
	काष्ठा stb0899_state *state = fe->demodulator_priv;

	i2c_stat = stb0899_पढ़ो_reg(state, STB0899_I2CRPT);
	अगर (i2c_stat < 0)
		जाओ err;

	अगर (enable) अणु
		dprपूर्णांकk(state->verbose, FE_DEBUG, 1, "Enabling I2C Repeater ...");
		i2c_stat |=  STB0899_I2CTON;
		अगर (stb0899_ग_लिखो_reg(state, STB0899_I2CRPT, i2c_stat) < 0)
			जाओ err;
	पूर्ण अन्यथा अणु
		dprपूर्णांकk(state->verbose, FE_DEBUG, 1, "Disabling I2C Repeater ...");
		i2c_stat &= ~STB0899_I2CTON;
		अगर (stb0899_ग_लिखो_reg(state, STB0899_I2CRPT, i2c_stat) < 0)
			जाओ err;
	पूर्ण
	वापस 0;
err:
	dprपूर्णांकk(state->verbose, FE_ERROR, 1, "I2C Repeater control failed");
	वापस -EREMOTEIO;
पूर्ण


अटल अंतरभूत व्योम CONVERT32(u32 x, अक्षर *str)
अणु
	*str++	= (x >> 24) & 0xff;
	*str++	= (x >> 16) & 0xff;
	*str++	= (x >>  8) & 0xff;
	*str++	= (x >>  0) & 0xff;
	*str	= '\0';
पूर्ण

अटल पूर्णांक stb0899_get_dev_id(काष्ठा stb0899_state *state)
अणु
	u8 chip_id, release;
	u16 id;
	u32 demod_ver = 0, fec_ver = 0;
	अक्षर demod_str[5] = अणु 0 पूर्ण;
	अक्षर fec_str[5] = अणु 0 पूर्ण;

	id = stb0899_पढ़ो_reg(state, STB0899_DEV_ID);
	dprपूर्णांकk(state->verbose, FE_DEBUG, 1, "ID reg=[0x%02x]", id);
	chip_id = STB0899_GETFIELD(CHIP_ID, id);
	release = STB0899_GETFIELD(CHIP_REL, id);

	dprपूर्णांकk(state->verbose, FE_ERROR, 1, "Device ID=[%d], Release=[%d]",
		chip_id, release);

	CONVERT32(STB0899_READ_S2REG(STB0899_S2DEMOD, DMD_CORE_ID), (अक्षर *)&demod_str);

	demod_ver = STB0899_READ_S2REG(STB0899_S2DEMOD, DMD_VERSION_ID);
	dprपूर्णांकk(state->verbose, FE_ERROR, 1, "Demodulator Core ID=[%s], Version=[%d]", (अक्षर *) &demod_str, demod_ver);
	CONVERT32(STB0899_READ_S2REG(STB0899_S2FEC, FEC_CORE_ID_REG), (अक्षर *)&fec_str);
	fec_ver = STB0899_READ_S2REG(STB0899_S2FEC, FEC_VER_ID_REG);
	अगर (! (chip_id > 0)) अणु
		dprपूर्णांकk(state->verbose, FE_ERROR, 1, "couldn't find a STB 0899");

		वापस -ENODEV;
	पूर्ण
	dprपूर्णांकk(state->verbose, FE_ERROR, 1, "FEC Core ID=[%s], Version=[%d]", (अक्षर*) &fec_str, fec_ver);

	वापस 0;
पूर्ण

अटल व्योम stb0899_set_delivery(काष्ठा stb0899_state *state)
अणु
	u8 reg;
	u8 stop_clk[2];

	stop_clk[0] = stb0899_पढ़ो_reg(state, STB0899_STOPCLK1);
	stop_clk[1] = stb0899_पढ़ो_reg(state, STB0899_STOPCLK2);

	चयन (state->delsys) अणु
	हाल SYS_DVBS:
		dprपूर्णांकk(state->verbose, FE_DEBUG, 1, "Delivery System -- DVB-S");
		/* FECM/Viterbi ON	*/
		reg = stb0899_पढ़ो_reg(state, STB0899_FECM);
		STB0899_SETFIELD_VAL(FECM_RSVD0, reg, 0);
		STB0899_SETFIELD_VAL(FECM_VITERBI_ON, reg, 1);
		stb0899_ग_लिखो_reg(state, STB0899_FECM, reg);

		stb0899_ग_लिखो_reg(state, STB0899_RSULC, 0xb1);
		stb0899_ग_लिखो_reg(state, STB0899_TSULC, 0x40);
		stb0899_ग_लिखो_reg(state, STB0899_RSLLC, 0x42);
		stb0899_ग_लिखो_reg(state, STB0899_TSLPL, 0x12);

		reg = stb0899_पढ़ो_reg(state, STB0899_TSTRES);
		STB0899_SETFIELD_VAL(FRESLDPC, reg, 1);
		stb0899_ग_लिखो_reg(state, STB0899_TSTRES, reg);

		STB0899_SETFIELD_VAL(STOP_CHK8PSK, stop_clk[0], 1);
		STB0899_SETFIELD_VAL(STOP_CKFEC108, stop_clk[0], 1);
		STB0899_SETFIELD_VAL(STOP_CKFEC216, stop_clk[0], 1);

		STB0899_SETFIELD_VAL(STOP_CKPKDLIN108, stop_clk[1], 1);
		STB0899_SETFIELD_VAL(STOP_CKPKDLIN216, stop_clk[1], 1);

		STB0899_SETFIELD_VAL(STOP_CKINTBUF216, stop_clk[0], 1);
		STB0899_SETFIELD_VAL(STOP_CKCORE216, stop_clk[0], 0);

		STB0899_SETFIELD_VAL(STOP_CKS2DMD108, stop_clk[1], 1);
		अवरोध;
	हाल SYS_DVBS2:
		/* FECM/Viterbi OFF	*/
		reg = stb0899_पढ़ो_reg(state, STB0899_FECM);
		STB0899_SETFIELD_VAL(FECM_RSVD0, reg, 0);
		STB0899_SETFIELD_VAL(FECM_VITERBI_ON, reg, 0);
		stb0899_ग_लिखो_reg(state, STB0899_FECM, reg);

		stb0899_ग_लिखो_reg(state, STB0899_RSULC, 0xb1);
		stb0899_ग_लिखो_reg(state, STB0899_TSULC, 0x42);
		stb0899_ग_लिखो_reg(state, STB0899_RSLLC, 0x40);
		stb0899_ग_लिखो_reg(state, STB0899_TSLPL, 0x02);

		reg = stb0899_पढ़ो_reg(state, STB0899_TSTRES);
		STB0899_SETFIELD_VAL(FRESLDPC, reg, 0);
		stb0899_ग_लिखो_reg(state, STB0899_TSTRES, reg);

		STB0899_SETFIELD_VAL(STOP_CHK8PSK, stop_clk[0], 1);
		STB0899_SETFIELD_VAL(STOP_CKFEC108, stop_clk[0], 0);
		STB0899_SETFIELD_VAL(STOP_CKFEC216, stop_clk[0], 0);

		STB0899_SETFIELD_VAL(STOP_CKPKDLIN108, stop_clk[1], 0);
		STB0899_SETFIELD_VAL(STOP_CKPKDLIN216, stop_clk[1], 0);

		STB0899_SETFIELD_VAL(STOP_CKINTBUF216, stop_clk[0], 0);
		STB0899_SETFIELD_VAL(STOP_CKCORE216, stop_clk[0], 0);

		STB0899_SETFIELD_VAL(STOP_CKS2DMD108, stop_clk[1], 0);
		अवरोध;
	हाल SYS_DSS:
		/* FECM/Viterbi ON	*/
		reg = stb0899_पढ़ो_reg(state, STB0899_FECM);
		STB0899_SETFIELD_VAL(FECM_RSVD0, reg, 1);
		STB0899_SETFIELD_VAL(FECM_VITERBI_ON, reg, 1);
		stb0899_ग_लिखो_reg(state, STB0899_FECM, reg);

		stb0899_ग_लिखो_reg(state, STB0899_RSULC, 0xa1);
		stb0899_ग_लिखो_reg(state, STB0899_TSULC, 0x61);
		stb0899_ग_लिखो_reg(state, STB0899_RSLLC, 0x42);

		reg = stb0899_पढ़ो_reg(state, STB0899_TSTRES);
		STB0899_SETFIELD_VAL(FRESLDPC, reg, 1);
		stb0899_ग_लिखो_reg(state, STB0899_TSTRES, reg);

		STB0899_SETFIELD_VAL(STOP_CHK8PSK, stop_clk[0], 1);
		STB0899_SETFIELD_VAL(STOP_CKFEC108, stop_clk[0], 1);
		STB0899_SETFIELD_VAL(STOP_CKFEC216, stop_clk[0], 1);

		STB0899_SETFIELD_VAL(STOP_CKPKDLIN108, stop_clk[1], 1);
		STB0899_SETFIELD_VAL(STOP_CKPKDLIN216, stop_clk[1], 1);

		STB0899_SETFIELD_VAL(STOP_CKCORE216, stop_clk[0], 0);

		STB0899_SETFIELD_VAL(STOP_CKS2DMD108, stop_clk[1], 1);
		अवरोध;
	शेष:
		dprपूर्णांकk(state->verbose, FE_ERROR, 1, "Unsupported delivery system");
		अवरोध;
	पूर्ण
	STB0899_SETFIELD_VAL(STOP_CKADCI108, stop_clk[0], 0);
	stb0899_ग_लिखो_regs(state, STB0899_STOPCLK1, stop_clk, 2);
पूर्ण

/*
 * stb0899_set_iterations
 * set the LDPC iteration scale function
 */
अटल व्योम stb0899_set_iterations(काष्ठा stb0899_state *state)
अणु
	काष्ठा stb0899_पूर्णांकernal *पूर्णांकernal = &state->पूर्णांकernal;
	काष्ठा stb0899_config *config = state->config;

	s32 iter_scale;
	u32 reg;

	iter_scale = 17 * (पूर्णांकernal->master_clk / 1000);
	iter_scale += 410000;
	iter_scale /= (पूर्णांकernal->srate / 1000000);
	iter_scale /= 1000;

	अगर (iter_scale > config->ldpc_max_iter)
		iter_scale = config->ldpc_max_iter;

	reg = STB0899_READ_S2REG(STB0899_S2FEC, MAX_ITER);
	STB0899_SETFIELD_VAL(MAX_ITERATIONS, reg, iter_scale);
	stb0899_ग_लिखो_s2reg(state, STB0899_S2FEC, STB0899_BASE_MAX_ITER, STB0899_OFF0_MAX_ITER, reg);
पूर्ण

अटल क्रमागत dvbfe_search stb0899_search(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा stb0899_state *state = fe->demodulator_priv;
	काष्ठा stb0899_params *i_params = &state->params;
	काष्ठा stb0899_पूर्णांकernal *पूर्णांकernal = &state->पूर्णांकernal;
	काष्ठा stb0899_config *config = state->config;
	काष्ठा dtv_frontend_properties *props = &fe->dtv_property_cache;

	u32 SearchRange, gain;

	i_params->freq	= props->frequency;
	i_params->srate = props->symbol_rate;
	state->delsys = props->delivery_प्रणाली;
	dprपूर्णांकk(state->verbose, FE_DEBUG, 1, "delivery system=%d", state->delsys);

	SearchRange = 10000000;
	dprपूर्णांकk(state->verbose, FE_DEBUG, 1, "Frequency=%d, Srate=%d", i_params->freq, i_params->srate);
	/* checking Search Range is meaningless क्रम a fixed 3 Mhz			*/
	अगर (INRANGE(i_params->srate, 1000000, 45000000)) अणु
		dprपूर्णांकk(state->verbose, FE_DEBUG, 1, "Parameters IN RANGE");
		stb0899_set_delivery(state);

		अगर (state->config->tuner_set_rfsiggain) अणु
			अगर (पूर्णांकernal->srate > 15000000)
				gain =  8; /* 15Mb < srate < 45Mb, gain = 8dB	*/
			अन्यथा अगर (पूर्णांकernal->srate > 5000000)
				gain = 12; /*  5Mb < srate < 15Mb, gain = 12dB	*/
			अन्यथा
				gain = 14; /*  1Mb < srate <  5Mb, gain = 14db	*/
			state->config->tuner_set_rfsiggain(fe, gain);
		पूर्ण

		अगर (i_params->srate <= 5000000)
			stb0899_set_mclk(state, config->lo_clk);
		अन्यथा
			stb0899_set_mclk(state, config->hi_clk);

		चयन (state->delsys) अणु
		हाल SYS_DVBS:
		हाल SYS_DSS:
			dprपूर्णांकk(state->verbose, FE_DEBUG, 1, "DVB-S delivery system");
			पूर्णांकernal->freq	= i_params->freq;
			पूर्णांकernal->srate	= i_params->srate;
			/*
			 * search = user search range +
			 *	    500Khz +
			 *	    2 * Tuner_step_size +
			 *	    10% of the symbol rate
			 */
			पूर्णांकernal->srch_range	= SearchRange + 1500000 + (i_params->srate / 5);
			पूर्णांकernal->derot_percent	= 30;

			/* What to करो क्रम tuners having no bandwidth setup ?	*/
			/* enable tuner I/O */
			stb0899_i2c_gate_ctrl(&state->frontend, 1);

			अगर (state->config->tuner_set_bandwidth)
				state->config->tuner_set_bandwidth(fe, (13 * (stb0899_carr_width(state) + SearchRange)) / 10);
			अगर (state->config->tuner_get_bandwidth)
				state->config->tuner_get_bandwidth(fe, &पूर्णांकernal->tuner_bw);

			/* disable tuner I/O */
			stb0899_i2c_gate_ctrl(&state->frontend, 0);

			/* Set DVB-S1 AGC		*/
			stb0899_ग_लिखो_reg(state, STB0899_AGCRFCFG, 0x11);

			/* Run the search algorithm	*/
			dprपूर्णांकk(state->verbose, FE_DEBUG, 1, "running DVB-S search algo ..");
			अगर (stb0899_dvbs_algo(state)	== RANGEOK) अणु
				पूर्णांकernal->lock		= 1;
				dprपूर्णांकk(state->verbose, FE_DEBUG, 1,
					"-------------------------------------> DVB-S LOCK !");

//				stb0899_ग_लिखो_reg(state, STB0899_ERRCTRL1, 0x3d); /* Viterbi Errors	*/
//				पूर्णांकernal->v_status = stb0899_पढ़ो_reg(state, STB0899_VSTATUS);
//				पूर्णांकernal->err_ctrl = stb0899_पढ़ो_reg(state, STB0899_ERRCTRL1);
//				dprपूर्णांकk(state->verbose, FE_DEBUG, 1, "VSTATUS=0x%02x", पूर्णांकernal->v_status);
//				dprपूर्णांकk(state->verbose, FE_DEBUG, 1, "ERR_CTRL=0x%02x", पूर्णांकernal->err_ctrl);

				वापस DVBFE_ALGO_SEARCH_SUCCESS;
			पूर्ण अन्यथा अणु
				पूर्णांकernal->lock		= 0;

				वापस DVBFE_ALGO_SEARCH_FAILED;
			पूर्ण
			अवरोध;
		हाल SYS_DVBS2:
			पूर्णांकernal->freq			= i_params->freq;
			पूर्णांकernal->srate			= i_params->srate;
			पूर्णांकernal->srch_range		= SearchRange;

			/* enable tuner I/O */
			stb0899_i2c_gate_ctrl(&state->frontend, 1);

			अगर (state->config->tuner_set_bandwidth)
				state->config->tuner_set_bandwidth(fe, (stb0899_carr_width(state) + SearchRange));
			अगर (state->config->tuner_get_bandwidth)
				state->config->tuner_get_bandwidth(fe, &पूर्णांकernal->tuner_bw);

			/* disable tuner I/O */
			stb0899_i2c_gate_ctrl(&state->frontend, 0);

//			pParams->SpectralInv		= pSearch->IQ_Inversion;

			/* Set DVB-S2 AGC		*/
			stb0899_ग_लिखो_reg(state, STB0899_AGCRFCFG, 0x1c);

			/* Set IterScale =f(MCLK,SYMB)	*/
			stb0899_set_iterations(state);

			/* Run the search algorithm	*/
			dprपूर्णांकk(state->verbose, FE_DEBUG, 1, "running DVB-S2 search algo ..");
			अगर (stb0899_dvbs2_algo(state)	== DVBS2_FEC_LOCK) अणु
				पूर्णांकernal->lock		= 1;
				dprपूर्णांकk(state->verbose, FE_DEBUG, 1,
					"-------------------------------------> DVB-S2 LOCK !");

//				stb0899_ग_लिखो_reg(state, STB0899_ERRCTRL1, 0xb6); /* Packet Errors	*/
//				पूर्णांकernal->v_status = stb0899_पढ़ो_reg(state, STB0899_VSTATUS);
//				पूर्णांकernal->err_ctrl = stb0899_पढ़ो_reg(state, STB0899_ERRCTRL1);

				वापस DVBFE_ALGO_SEARCH_SUCCESS;
			पूर्ण अन्यथा अणु
				पूर्णांकernal->lock		= 0;

				वापस DVBFE_ALGO_SEARCH_FAILED;
			पूर्ण
			अवरोध;
		शेष:
			dprपूर्णांकk(state->verbose, FE_ERROR, 1, "Unsupported delivery system");
			वापस DVBFE_ALGO_SEARCH_INVALID;
		पूर्ण
	पूर्ण

	वापस DVBFE_ALGO_SEARCH_ERROR;
पूर्ण

अटल पूर्णांक stb0899_get_frontend(काष्ठा dvb_frontend *fe,
				काष्ठा dtv_frontend_properties *p)
अणु
	काष्ठा stb0899_state *state		= fe->demodulator_priv;
	काष्ठा stb0899_पूर्णांकernal *पूर्णांकernal	= &state->पूर्णांकernal;

	dprपूर्णांकk(state->verbose, FE_DEBUG, 1, "Get params");
	p->symbol_rate = पूर्णांकernal->srate;
	p->frequency = पूर्णांकernal->freq;

	वापस 0;
पूर्ण

अटल क्रमागत dvbfe_algo stb0899_frontend_algo(काष्ठा dvb_frontend *fe)
अणु
	वापस DVBFE_ALGO_CUSTOM;
पूर्ण

अटल स्थिर काष्ठा dvb_frontend_ops stb0899_ops = अणु
	.delsys = अणु SYS_DVBS, SYS_DVBS2, SYS_DSS पूर्ण,
	.info = अणु
		.name			= "STB0899 Multistandard",
		.frequency_min_hz	=  950 * MHz,
		.frequency_max_hz	= 2150 * MHz,
		.symbol_rate_min	=  5000000,
		.symbol_rate_max	= 45000000,

		.caps			= FE_CAN_INVERSION_AUTO	|
					  FE_CAN_FEC_AUTO	|
					  FE_CAN_2G_MODULATION	|
					  FE_CAN_QPSK
	पूर्ण,

	.detach				= stb0899_detach,
	.release			= stb0899_release,
	.init				= stb0899_init,
	.sleep				= stb0899_sleep,
//	.wakeup				= stb0899_wakeup,

	.i2c_gate_ctrl			= stb0899_i2c_gate_ctrl,

	.get_frontend_algo		= stb0899_frontend_algo,
	.search				= stb0899_search,
	.get_frontend                   = stb0899_get_frontend,


	.पढ़ो_status			= stb0899_पढ़ो_status,
	.पढ़ो_snr			= stb0899_पढ़ो_snr,
	.पढ़ो_संकेत_strength		= stb0899_पढ़ो_संकेत_strength,
	.पढ़ो_ber			= stb0899_पढ़ो_ber,

	.set_voltage			= stb0899_set_voltage,
	.set_tone			= stb0899_set_tone,

	.diseqc_send_master_cmd		= stb0899_send_diseqc_msg,
	.diseqc_recv_slave_reply	= stb0899_recv_slave_reply,
	.diseqc_send_burst		= stb0899_send_diseqc_burst,
पूर्ण;

काष्ठा dvb_frontend *stb0899_attach(काष्ठा stb0899_config *config, काष्ठा i2c_adapter *i2c)
अणु
	काष्ठा stb0899_state *state = शून्य;

	state = kzalloc(माप (काष्ठा stb0899_state), GFP_KERNEL);
	अगर (state == शून्य)
		जाओ error;

	state->verbose				= &verbose;
	state->config				= config;
	state->i2c				= i2c;
	state->frontend.ops			= stb0899_ops;
	state->frontend.demodulator_priv	= state;
	/* use configured inversion as शेष -- we'll later स्वतःdetect inversion */
	state->पूर्णांकernal.inversion		= config->inversion;

	stb0899_wakeup(&state->frontend);
	अगर (stb0899_get_dev_id(state) == -ENODEV) अणु
		prपूर्णांकk("%s: Exiting .. !\n", __func__);
		जाओ error;
	पूर्ण

	prपूर्णांकk("%s: Attaching STB0899 \n", __func__);
	वापस &state->frontend;

error:
	kमुक्त(state);
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(stb0899_attach);
MODULE_PARM_DESC(verbose, "Set Verbosity level");
MODULE_AUTHOR("Manu Abraham");
MODULE_DESCRIPTION("STB0899 Multi-Std frontend");
MODULE_LICENSE("GPL");
