<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
    Samsung S5H1411 VSB/QAM demodulator driver

    Copyright (C) 2008 Steven Toth <stoth@linuxtv.org>


*/

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/माला.स>
#समावेश <linux/slab.h>
#समावेश <linux/delay.h>
#समावेश <media/dvb_frontend.h>
#समावेश "s5h1411.h"

काष्ठा s5h1411_state अणु

	काष्ठा i2c_adapter *i2c;

	/* configuration settings */
	स्थिर काष्ठा s5h1411_config *config;

	काष्ठा dvb_frontend frontend;

	क्रमागत fe_modulation current_modulation;
	अचिन्हित पूर्णांक first_tune:1;

	u32 current_frequency;
	पूर्णांक अगर_freq;

	u8 inversion;
पूर्ण;

अटल पूर्णांक debug;

#घोषणा dprपूर्णांकk(arg...) करो अणु	\
	अगर (debug)		\
		prपूर्णांकk(arg);	\
पूर्ण जबतक (0)

/* Register values to initialise the demod, शेषs to VSB */
अटल काष्ठा init_tab अणु
	u8	addr;
	u8	reg;
	u16	data;
पूर्ण init_tab[] = अणु
	अणु S5H1411_I2C_TOP_ADDR, 0x00, 0x0071, पूर्ण,
	अणु S5H1411_I2C_TOP_ADDR, 0x08, 0x0047, पूर्ण,
	अणु S5H1411_I2C_TOP_ADDR, 0x1c, 0x0400, पूर्ण,
	अणु S5H1411_I2C_TOP_ADDR, 0x1e, 0x0370, पूर्ण,
	अणु S5H1411_I2C_TOP_ADDR, 0x1f, 0x342c, पूर्ण,
	अणु S5H1411_I2C_TOP_ADDR, 0x24, 0x0231, पूर्ण,
	अणु S5H1411_I2C_TOP_ADDR, 0x25, 0x1011, पूर्ण,
	अणु S5H1411_I2C_TOP_ADDR, 0x26, 0x0f07, पूर्ण,
	अणु S5H1411_I2C_TOP_ADDR, 0x27, 0x0f04, पूर्ण,
	अणु S5H1411_I2C_TOP_ADDR, 0x28, 0x070f, पूर्ण,
	अणु S5H1411_I2C_TOP_ADDR, 0x29, 0x2820, पूर्ण,
	अणु S5H1411_I2C_TOP_ADDR, 0x2a, 0x102e, पूर्ण,
	अणु S5H1411_I2C_TOP_ADDR, 0x2b, 0x0220, पूर्ण,
	अणु S5H1411_I2C_TOP_ADDR, 0x2e, 0x0d0e, पूर्ण,
	अणु S5H1411_I2C_TOP_ADDR, 0x2f, 0x1013, पूर्ण,
	अणु S5H1411_I2C_TOP_ADDR, 0x31, 0x171b, पूर्ण,
	अणु S5H1411_I2C_TOP_ADDR, 0x32, 0x0e0f, पूर्ण,
	अणु S5H1411_I2C_TOP_ADDR, 0x33, 0x0f10, पूर्ण,
	अणु S5H1411_I2C_TOP_ADDR, 0x34, 0x170e, पूर्ण,
	अणु S5H1411_I2C_TOP_ADDR, 0x35, 0x4b10, पूर्ण,
	अणु S5H1411_I2C_TOP_ADDR, 0x36, 0x0f17, पूर्ण,
	अणु S5H1411_I2C_TOP_ADDR, 0x3c, 0x1577, पूर्ण,
	अणु S5H1411_I2C_TOP_ADDR, 0x3d, 0x081a, पूर्ण,
	अणु S5H1411_I2C_TOP_ADDR, 0x3e, 0x77ee, पूर्ण,
	अणु S5H1411_I2C_TOP_ADDR, 0x40, 0x1e09, पूर्ण,
	अणु S5H1411_I2C_TOP_ADDR, 0x41, 0x0f0c, पूर्ण,
	अणु S5H1411_I2C_TOP_ADDR, 0x42, 0x1f10, पूर्ण,
	अणु S5H1411_I2C_TOP_ADDR, 0x4d, 0x0509, पूर्ण,
	अणु S5H1411_I2C_TOP_ADDR, 0x4e, 0x0a00, पूर्ण,
	अणु S5H1411_I2C_TOP_ADDR, 0x50, 0x0000, पूर्ण,
	अणु S5H1411_I2C_TOP_ADDR, 0x5b, 0x0000, पूर्ण,
	अणु S5H1411_I2C_TOP_ADDR, 0x5c, 0x0008, पूर्ण,
	अणु S5H1411_I2C_TOP_ADDR, 0x57, 0x1101, पूर्ण,
	अणु S5H1411_I2C_TOP_ADDR, 0x65, 0x007c, पूर्ण,
	अणु S5H1411_I2C_TOP_ADDR, 0x68, 0x0512, पूर्ण,
	अणु S5H1411_I2C_TOP_ADDR, 0x69, 0x0258, पूर्ण,
	अणु S5H1411_I2C_TOP_ADDR, 0x70, 0x0004, पूर्ण,
	अणु S5H1411_I2C_TOP_ADDR, 0x71, 0x0007, पूर्ण,
	अणु S5H1411_I2C_TOP_ADDR, 0x76, 0x00a9, पूर्ण,
	अणु S5H1411_I2C_TOP_ADDR, 0x78, 0x3141, पूर्ण,
	अणु S5H1411_I2C_TOP_ADDR, 0x7a, 0x3141, पूर्ण,
	अणु S5H1411_I2C_TOP_ADDR, 0xb3, 0x8003, पूर्ण,
	अणु S5H1411_I2C_TOP_ADDR, 0xb5, 0xa6bb, पूर्ण,
	अणु S5H1411_I2C_TOP_ADDR, 0xb6, 0x0609, पूर्ण,
	अणु S5H1411_I2C_TOP_ADDR, 0xb7, 0x2f06, पूर्ण,
	अणु S5H1411_I2C_TOP_ADDR, 0xb8, 0x003f, पूर्ण,
	अणु S5H1411_I2C_TOP_ADDR, 0xb9, 0x2700, पूर्ण,
	अणु S5H1411_I2C_TOP_ADDR, 0xba, 0xfac8, पूर्ण,
	अणु S5H1411_I2C_TOP_ADDR, 0xbe, 0x1003, पूर्ण,
	अणु S5H1411_I2C_TOP_ADDR, 0xbf, 0x103f, पूर्ण,
	अणु S5H1411_I2C_TOP_ADDR, 0xce, 0x2000, पूर्ण,
	अणु S5H1411_I2C_TOP_ADDR, 0xcf, 0x0800, पूर्ण,
	अणु S5H1411_I2C_TOP_ADDR, 0xd0, 0x0800, पूर्ण,
	अणु S5H1411_I2C_TOP_ADDR, 0xd1, 0x0400, पूर्ण,
	अणु S5H1411_I2C_TOP_ADDR, 0xd2, 0x0800, पूर्ण,
	अणु S5H1411_I2C_TOP_ADDR, 0xd3, 0x2000, पूर्ण,
	अणु S5H1411_I2C_TOP_ADDR, 0xd4, 0x3000, पूर्ण,
	अणु S5H1411_I2C_TOP_ADDR, 0xdb, 0x4a9b, पूर्ण,
	अणु S5H1411_I2C_TOP_ADDR, 0xdc, 0x1000, पूर्ण,
	अणु S5H1411_I2C_TOP_ADDR, 0xde, 0x0001, पूर्ण,
	अणु S5H1411_I2C_TOP_ADDR, 0xdf, 0x0000, पूर्ण,
	अणु S5H1411_I2C_TOP_ADDR, 0xe3, 0x0301, पूर्ण,
	अणु S5H1411_I2C_QAM_ADDR, 0xf3, 0x0000, पूर्ण,
	अणु S5H1411_I2C_QAM_ADDR, 0xf3, 0x0001, पूर्ण,
	अणु S5H1411_I2C_QAM_ADDR, 0x08, 0x0600, पूर्ण,
	अणु S5H1411_I2C_QAM_ADDR, 0x18, 0x4201, पूर्ण,
	अणु S5H1411_I2C_QAM_ADDR, 0x1e, 0x6476, पूर्ण,
	अणु S5H1411_I2C_QAM_ADDR, 0x21, 0x0830, पूर्ण,
	अणु S5H1411_I2C_QAM_ADDR, 0x0c, 0x5679, पूर्ण,
	अणु S5H1411_I2C_QAM_ADDR, 0x0d, 0x579b, पूर्ण,
	अणु S5H1411_I2C_QAM_ADDR, 0x24, 0x0102, पूर्ण,
	अणु S5H1411_I2C_QAM_ADDR, 0x31, 0x7488, पूर्ण,
	अणु S5H1411_I2C_QAM_ADDR, 0x32, 0x0a08, पूर्ण,
	अणु S5H1411_I2C_QAM_ADDR, 0x3d, 0x8689, पूर्ण,
	अणु S5H1411_I2C_QAM_ADDR, 0x49, 0x0048, पूर्ण,
	अणु S5H1411_I2C_QAM_ADDR, 0x57, 0x2012, पूर्ण,
	अणु S5H1411_I2C_QAM_ADDR, 0x5d, 0x7676, पूर्ण,
	अणु S5H1411_I2C_QAM_ADDR, 0x04, 0x0400, पूर्ण,
	अणु S5H1411_I2C_QAM_ADDR, 0x58, 0x00c0, पूर्ण,
	अणु S5H1411_I2C_QAM_ADDR, 0x5b, 0x0100, पूर्ण,
पूर्ण;

/* VSB SNR lookup table */
अटल काष्ठा vsb_snr_tab अणु
	u16	val;
	u16	data;
पूर्ण vsb_snr_tab[] = अणु
	अणु  0x39f, 300, पूर्ण,
	अणु  0x39b, 295, पूर्ण,
	अणु  0x397, 290, पूर्ण,
	अणु  0x394, 285, पूर्ण,
	अणु  0x38f, 280, पूर्ण,
	अणु  0x38b, 275, पूर्ण,
	अणु  0x387, 270, पूर्ण,
	अणु  0x382, 265, पूर्ण,
	अणु  0x37d, 260, पूर्ण,
	अणु  0x377, 255, पूर्ण,
	अणु  0x370, 250, पूर्ण,
	अणु  0x36a, 245, पूर्ण,
	अणु  0x364, 240, पूर्ण,
	अणु  0x35b, 235, पूर्ण,
	अणु  0x353, 230, पूर्ण,
	अणु  0x349, 225, पूर्ण,
	अणु  0x340, 320, पूर्ण,
	अणु  0x337, 215, पूर्ण,
	अणु  0x327, 210, पूर्ण,
	अणु  0x31b, 205, पूर्ण,
	अणु  0x310, 200, पूर्ण,
	अणु  0x302, 195, पूर्ण,
	अणु  0x2f3, 190, पूर्ण,
	अणु  0x2e4, 185, पूर्ण,
	अणु  0x2d7, 180, पूर्ण,
	अणु  0x2cd, 175, पूर्ण,
	अणु  0x2bb, 170, पूर्ण,
	अणु  0x2a9, 165, पूर्ण,
	अणु  0x29e, 160, पूर्ण,
	अणु  0x284, 155, पूर्ण,
	अणु  0x27a, 150, पूर्ण,
	अणु  0x260, 145, पूर्ण,
	अणु  0x23a, 140, पूर्ण,
	अणु  0x224, 135, पूर्ण,
	अणु  0x213, 130, पूर्ण,
	अणु  0x204, 125, पूर्ण,
	अणु  0x1fe, 120, पूर्ण,
	अणु      0,   0, पूर्ण,
पूर्ण;

/* QAM64 SNR lookup table */
अटल काष्ठा qam64_snr_tab अणु
	u16	val;
	u16	data;
पूर्ण qam64_snr_tab[] = अणु
	अणु  0x0001,   0, पूर्ण,
	अणु  0x0af0, 300, पूर्ण,
	अणु  0x0d80, 290, पूर्ण,
	अणु  0x10a0, 280, पूर्ण,
	अणु  0x14b5, 270, पूर्ण,
	अणु  0x1590, 268, पूर्ण,
	अणु  0x1680, 266, पूर्ण,
	अणु  0x17b0, 264, पूर्ण,
	अणु  0x18c0, 262, पूर्ण,
	अणु  0x19b0, 260, पूर्ण,
	अणु  0x1ad0, 258, पूर्ण,
	अणु  0x1d00, 256, पूर्ण,
	अणु  0x1da0, 254, पूर्ण,
	अणु  0x1ef0, 252, पूर्ण,
	अणु  0x2050, 250, पूर्ण,
	अणु  0x20f0, 249, पूर्ण,
	अणु  0x21d0, 248, पूर्ण,
	अणु  0x22b0, 247, पूर्ण,
	अणु  0x23a0, 246, पूर्ण,
	अणु  0x2470, 245, पूर्ण,
	अणु  0x24f0, 244, पूर्ण,
	अणु  0x25a0, 243, पूर्ण,
	अणु  0x26c0, 242, पूर्ण,
	अणु  0x27b0, 241, पूर्ण,
	अणु  0x28d0, 240, पूर्ण,
	अणु  0x29b0, 239, पूर्ण,
	अणु  0x2ad0, 238, पूर्ण,
	अणु  0x2ba0, 237, पूर्ण,
	अणु  0x2c80, 236, पूर्ण,
	अणु  0x2d20, 235, पूर्ण,
	अणु  0x2e00, 234, पूर्ण,
	अणु  0x2f10, 233, पूर्ण,
	अणु  0x3050, 232, पूर्ण,
	अणु  0x3190, 231, पूर्ण,
	अणु  0x3300, 230, पूर्ण,
	अणु  0x3340, 229, पूर्ण,
	अणु  0x3200, 228, पूर्ण,
	अणु  0x3550, 227, पूर्ण,
	अणु  0x3610, 226, पूर्ण,
	अणु  0x3600, 225, पूर्ण,
	अणु  0x3700, 224, पूर्ण,
	अणु  0x3800, 223, पूर्ण,
	अणु  0x3920, 222, पूर्ण,
	अणु  0x3a20, 221, पूर्ण,
	अणु  0x3b30, 220, पूर्ण,
	अणु  0x3d00, 219, पूर्ण,
	अणु  0x3e00, 218, पूर्ण,
	अणु  0x4000, 217, पूर्ण,
	अणु  0x4100, 216, पूर्ण,
	अणु  0x4300, 215, पूर्ण,
	अणु  0x4400, 214, पूर्ण,
	अणु  0x4600, 213, पूर्ण,
	अणु  0x4700, 212, पूर्ण,
	अणु  0x4800, 211, पूर्ण,
	अणु  0x4a00, 210, पूर्ण,
	अणु  0x4b00, 209, पूर्ण,
	अणु  0x4d00, 208, पूर्ण,
	अणु  0x4f00, 207, पूर्ण,
	अणु  0x5050, 206, पूर्ण,
	अणु  0x5200, 205, पूर्ण,
	अणु  0x53c0, 204, पूर्ण,
	अणु  0x5450, 203, पूर्ण,
	अणु  0x5650, 202, पूर्ण,
	अणु  0x5820, 201, पूर्ण,
	अणु  0x6000, 200, पूर्ण,
	अणु  0xffff,   0, पूर्ण,
पूर्ण;

/* QAM256 SNR lookup table */
अटल काष्ठा qam256_snr_tab अणु
	u16	val;
	u16	data;
पूर्ण qam256_snr_tab[] = अणु
	अणु  0x0001,   0, पूर्ण,
	अणु  0x0970, 400, पूर्ण,
	अणु  0x0a90, 390, पूर्ण,
	अणु  0x0b90, 380, पूर्ण,
	अणु  0x0d90, 370, पूर्ण,
	अणु  0x0ff0, 360, पूर्ण,
	अणु  0x1240, 350, पूर्ण,
	अणु  0x1345, 348, पूर्ण,
	अणु  0x13c0, 346, पूर्ण,
	अणु  0x14c0, 344, पूर्ण,
	अणु  0x1500, 342, पूर्ण,
	अणु  0x1610, 340, पूर्ण,
	अणु  0x1700, 338, पूर्ण,
	अणु  0x1800, 336, पूर्ण,
	अणु  0x18b0, 334, पूर्ण,
	अणु  0x1900, 332, पूर्ण,
	अणु  0x1ab0, 330, पूर्ण,
	अणु  0x1bc0, 328, पूर्ण,
	अणु  0x1cb0, 326, पूर्ण,
	अणु  0x1db0, 324, पूर्ण,
	अणु  0x1eb0, 322, पूर्ण,
	अणु  0x2030, 320, पूर्ण,
	अणु  0x2200, 318, पूर्ण,
	अणु  0x2280, 316, पूर्ण,
	अणु  0x2410, 314, पूर्ण,
	अणु  0x25b0, 312, पूर्ण,
	अणु  0x27a0, 310, पूर्ण,
	अणु  0x2840, 308, पूर्ण,
	अणु  0x29d0, 306, पूर्ण,
	अणु  0x2b10, 304, पूर्ण,
	अणु  0x2d30, 302, पूर्ण,
	अणु  0x2f20, 300, पूर्ण,
	अणु  0x30c0, 298, पूर्ण,
	अणु  0x3260, 297, पूर्ण,
	अणु  0x32c0, 296, पूर्ण,
	अणु  0x3300, 295, पूर्ण,
	अणु  0x33b0, 294, पूर्ण,
	अणु  0x34b0, 293, पूर्ण,
	अणु  0x35a0, 292, पूर्ण,
	अणु  0x3650, 291, पूर्ण,
	अणु  0x3800, 290, पूर्ण,
	अणु  0x3900, 289, पूर्ण,
	अणु  0x3a50, 288, पूर्ण,
	अणु  0x3b30, 287, पूर्ण,
	अणु  0x3cb0, 286, पूर्ण,
	अणु  0x3e20, 285, पूर्ण,
	अणु  0x3fa0, 284, पूर्ण,
	अणु  0x40a0, 283, पूर्ण,
	अणु  0x41c0, 282, पूर्ण,
	अणु  0x42f0, 281, पूर्ण,
	अणु  0x44a0, 280, पूर्ण,
	अणु  0x4600, 279, पूर्ण,
	अणु  0x47b0, 278, पूर्ण,
	अणु  0x4900, 277, पूर्ण,
	अणु  0x4a00, 276, पूर्ण,
	अणु  0x4ba0, 275, पूर्ण,
	अणु  0x4d00, 274, पूर्ण,
	अणु  0x4f00, 273, पूर्ण,
	अणु  0x5000, 272, पूर्ण,
	अणु  0x51f0, 272, पूर्ण,
	अणु  0x53a0, 270, पूर्ण,
	अणु  0x5520, 269, पूर्ण,
	अणु  0x5700, 268, पूर्ण,
	अणु  0x5800, 267, पूर्ण,
	अणु  0x5a00, 266, पूर्ण,
	अणु  0x5c00, 265, पूर्ण,
	अणु  0x5d00, 264, पूर्ण,
	अणु  0x5f00, 263, पूर्ण,
	अणु  0x6000, 262, पूर्ण,
	अणु  0x6200, 261, पूर्ण,
	अणु  0x6400, 260, पूर्ण,
	अणु  0xffff,   0, पूर्ण,
पूर्ण;

/* 8 bit रेजिस्टरs, 16 bit values */
अटल पूर्णांक s5h1411_ग_लिखोreg(काष्ठा s5h1411_state *state,
	u8 addr, u8 reg, u16 data)
अणु
	पूर्णांक ret;
	u8 buf[] = अणु reg, data >> 8,  data & 0xff पूर्ण;

	काष्ठा i2c_msg msg = अणु .addr = addr, .flags = 0, .buf = buf, .len = 3 पूर्ण;

	ret = i2c_transfer(state->i2c, &msg, 1);

	अगर (ret != 1)
		prपूर्णांकk(KERN_ERR "%s: writereg error 0x%02x 0x%02x 0x%04x, ret == %i)\n",
		       __func__, addr, reg, data, ret);

	वापस (ret != 1) ? -1 : 0;
पूर्ण

अटल u16 s5h1411_पढ़ोreg(काष्ठा s5h1411_state *state, u8 addr, u8 reg)
अणु
	पूर्णांक ret;
	u8 b0[] = अणु reg पूर्ण;
	u8 b1[] = अणु 0, 0 पूर्ण;

	काष्ठा i2c_msg msg[] = अणु
		अणु .addr = addr, .flags = 0, .buf = b0, .len = 1 पूर्ण,
		अणु .addr = addr, .flags = I2C_M_RD, .buf = b1, .len = 2 पूर्ण पूर्ण;

	ret = i2c_transfer(state->i2c, msg, 2);

	अगर (ret != 2)
		prपूर्णांकk(KERN_ERR "%s: readreg error (ret == %i)\n",
			__func__, ret);
	वापस (b1[0] << 8) | b1[1];
पूर्ण

अटल पूर्णांक s5h1411_softreset(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा s5h1411_state *state = fe->demodulator_priv;

	dprपूर्णांकk("%s()\n", __func__);

	s5h1411_ग_लिखोreg(state, S5H1411_I2C_TOP_ADDR, 0xf7, 0);
	s5h1411_ग_लिखोreg(state, S5H1411_I2C_TOP_ADDR, 0xf7, 1);
	वापस 0;
पूर्ण

अटल पूर्णांक s5h1411_set_अगर_freq(काष्ठा dvb_frontend *fe, पूर्णांक KHz)
अणु
	काष्ठा s5h1411_state *state = fe->demodulator_priv;

	dprपूर्णांकk("%s(%d KHz)\n", __func__, KHz);

	चयन (KHz) अणु
	हाल 3250:
		s5h1411_ग_लिखोreg(state, S5H1411_I2C_TOP_ADDR, 0x38, 0x10d5);
		s5h1411_ग_लिखोreg(state, S5H1411_I2C_TOP_ADDR, 0x39, 0x5342);
		s5h1411_ग_लिखोreg(state, S5H1411_I2C_QAM_ADDR, 0x2c, 0x10d9);
		अवरोध;
	हाल 3500:
		s5h1411_ग_लिखोreg(state, S5H1411_I2C_TOP_ADDR, 0x38, 0x1225);
		s5h1411_ग_लिखोreg(state, S5H1411_I2C_TOP_ADDR, 0x39, 0x1e96);
		s5h1411_ग_लिखोreg(state, S5H1411_I2C_QAM_ADDR, 0x2c, 0x1225);
		अवरोध;
	हाल 4000:
		s5h1411_ग_लिखोreg(state, S5H1411_I2C_TOP_ADDR, 0x38, 0x14bc);
		s5h1411_ग_लिखोreg(state, S5H1411_I2C_TOP_ADDR, 0x39, 0xb53e);
		s5h1411_ग_लिखोreg(state, S5H1411_I2C_QAM_ADDR, 0x2c, 0x14bd);
		अवरोध;
	शेष:
		dprपूर्णांकk("%s(%d KHz) Invalid, defaulting to 5380\n",
			__func__, KHz);
		fallthrough;
	हाल 5380:
	हाल 44000:
		s5h1411_ग_लिखोreg(state, S5H1411_I2C_TOP_ADDR, 0x38, 0x1be4);
		s5h1411_ग_लिखोreg(state, S5H1411_I2C_TOP_ADDR, 0x39, 0x3655);
		s5h1411_ग_लिखोreg(state, S5H1411_I2C_QAM_ADDR, 0x2c, 0x1be4);
		अवरोध;
	पूर्ण

	state->अगर_freq = KHz;

	वापस 0;
पूर्ण

अटल पूर्णांक s5h1411_set_mpeg_timing(काष्ठा dvb_frontend *fe, पूर्णांक mode)
अणु
	काष्ठा s5h1411_state *state = fe->demodulator_priv;
	u16 val;

	dprपूर्णांकk("%s(%d)\n", __func__, mode);

	val = s5h1411_पढ़ोreg(state, S5H1411_I2C_TOP_ADDR, 0xbe) & 0xcfff;
	चयन (mode) अणु
	हाल S5H1411_MPEGTIMING_CONTINUOUS_INVERTING_CLOCK:
		val |= 0x0000;
		अवरोध;
	हाल S5H1411_MPEGTIMING_CONTINUOUS_NONINVERTING_CLOCK:
		dprपूर्णांकk("%s(%d) Mode1 or Defaulting\n", __func__, mode);
		val |= 0x1000;
		अवरोध;
	हाल S5H1411_MPEGTIMING_NONCONTINUOUS_INVERTING_CLOCK:
		val |= 0x2000;
		अवरोध;
	हाल S5H1411_MPEGTIMING_NONCONTINUOUS_NONINVERTING_CLOCK:
		val |= 0x3000;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* Configure MPEG Signal Timing अक्षरactistics */
	वापस s5h1411_ग_लिखोreg(state, S5H1411_I2C_TOP_ADDR, 0xbe, val);
पूर्ण

अटल पूर्णांक s5h1411_set_spectralinversion(काष्ठा dvb_frontend *fe, पूर्णांक inversion)
अणु
	काष्ठा s5h1411_state *state = fe->demodulator_priv;
	u16 val;

	dprपूर्णांकk("%s(%d)\n", __func__, inversion);
	val = s5h1411_पढ़ोreg(state, S5H1411_I2C_TOP_ADDR, 0x24) & ~0x1000;

	अगर (inversion == 1)
		val |= 0x1000; /* Inverted */

	state->inversion = inversion;
	वापस s5h1411_ग_लिखोreg(state, S5H1411_I2C_TOP_ADDR, 0x24, val);
पूर्ण

अटल पूर्णांक s5h1411_set_serialmode(काष्ठा dvb_frontend *fe, पूर्णांक serial)
अणु
	काष्ठा s5h1411_state *state = fe->demodulator_priv;
	u16 val;

	dprपूर्णांकk("%s(%d)\n", __func__, serial);
	val = s5h1411_पढ़ोreg(state, S5H1411_I2C_TOP_ADDR, 0xbd) & ~0x100;

	अगर (serial == 1)
		val |= 0x100;

	वापस s5h1411_ग_लिखोreg(state, S5H1411_I2C_TOP_ADDR, 0xbd, val);
पूर्ण

अटल पूर्णांक s5h1411_enable_modulation(काष्ठा dvb_frontend *fe,
				     क्रमागत fe_modulation m)
अणु
	काष्ठा s5h1411_state *state = fe->demodulator_priv;

	dprपूर्णांकk("%s(0x%08x)\n", __func__, m);

	अगर ((state->first_tune == 0) && (m == state->current_modulation)) अणु
		dprपूर्णांकk("%s() Already at desired modulation.  Skipping...\n",
			__func__);
		वापस 0;
	पूर्ण

	चयन (m) अणु
	हाल VSB_8:
		dprपूर्णांकk("%s() VSB_8\n", __func__);
		s5h1411_set_अगर_freq(fe, state->config->vsb_अगर);
		s5h1411_ग_लिखोreg(state, S5H1411_I2C_TOP_ADDR, 0x00, 0x71);
		s5h1411_ग_लिखोreg(state, S5H1411_I2C_TOP_ADDR, 0xf6, 0x00);
		s5h1411_ग_लिखोreg(state, S5H1411_I2C_TOP_ADDR, 0xcd, 0xf1);
		अवरोध;
	हाल QAM_64:
	हाल QAM_256:
	हाल QAM_AUTO:
		dprपूर्णांकk("%s() QAM_AUTO (64/256)\n", __func__);
		s5h1411_set_अगर_freq(fe, state->config->qam_अगर);
		s5h1411_ग_लिखोreg(state, S5H1411_I2C_TOP_ADDR, 0x00, 0x0171);
		s5h1411_ग_लिखोreg(state, S5H1411_I2C_TOP_ADDR, 0xf6, 0x0001);
		s5h1411_ग_लिखोreg(state, S5H1411_I2C_QAM_ADDR, 0x16, 0x1101);
		s5h1411_ग_लिखोreg(state, S5H1411_I2C_TOP_ADDR, 0xcd, 0x00f0);
		अवरोध;
	शेष:
		dprपूर्णांकk("%s() Invalid modulation\n", __func__);
		वापस -EINVAL;
	पूर्ण

	state->current_modulation = m;
	state->first_tune = 0;
	s5h1411_softreset(fe);

	वापस 0;
पूर्ण

अटल पूर्णांक s5h1411_i2c_gate_ctrl(काष्ठा dvb_frontend *fe, पूर्णांक enable)
अणु
	काष्ठा s5h1411_state *state = fe->demodulator_priv;

	dprपूर्णांकk("%s(%d)\n", __func__, enable);

	अगर (enable)
		वापस s5h1411_ग_लिखोreg(state, S5H1411_I2C_TOP_ADDR, 0xf5, 1);
	अन्यथा
		वापस s5h1411_ग_लिखोreg(state, S5H1411_I2C_TOP_ADDR, 0xf5, 0);
पूर्ण

अटल पूर्णांक s5h1411_set_gpio(काष्ठा dvb_frontend *fe, पूर्णांक enable)
अणु
	काष्ठा s5h1411_state *state = fe->demodulator_priv;
	u16 val;

	dprपूर्णांकk("%s(%d)\n", __func__, enable);

	val = s5h1411_पढ़ोreg(state, S5H1411_I2C_TOP_ADDR, 0xe0) & ~0x02;

	अगर (enable)
		वापस s5h1411_ग_लिखोreg(state, S5H1411_I2C_TOP_ADDR, 0xe0,
				val | 0x02);
	अन्यथा
		वापस s5h1411_ग_लिखोreg(state, S5H1411_I2C_TOP_ADDR, 0xe0, val);
पूर्ण

अटल पूर्णांक s5h1411_set_घातerstate(काष्ठा dvb_frontend *fe, पूर्णांक enable)
अणु
	काष्ठा s5h1411_state *state = fe->demodulator_priv;

	dprपूर्णांकk("%s(%d)\n", __func__, enable);

	अगर (enable)
		s5h1411_ग_लिखोreg(state, S5H1411_I2C_TOP_ADDR, 0xf4, 1);
	अन्यथा अणु
		s5h1411_ग_लिखोreg(state, S5H1411_I2C_TOP_ADDR, 0xf4, 0);
		s5h1411_softreset(fe);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक s5h1411_sleep(काष्ठा dvb_frontend *fe)
अणु
	वापस s5h1411_set_घातerstate(fe, 1);
पूर्ण

अटल पूर्णांक s5h1411_रेजिस्टर_reset(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा s5h1411_state *state = fe->demodulator_priv;

	dprपूर्णांकk("%s()\n", __func__);

	वापस s5h1411_ग_लिखोreg(state, S5H1411_I2C_TOP_ADDR, 0xf3, 0);
पूर्ण

/* Talk to the demod, set the FEC, GUARD, QAM settings etc */
अटल पूर्णांक s5h1411_set_frontend(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dtv_frontend_properties *p = &fe->dtv_property_cache;
	काष्ठा s5h1411_state *state = fe->demodulator_priv;

	dprपूर्णांकk("%s(frequency=%d)\n", __func__, p->frequency);

	s5h1411_softreset(fe);

	state->current_frequency = p->frequency;

	s5h1411_enable_modulation(fe, p->modulation);

	अगर (fe->ops.tuner_ops.set_params) अणु
		अगर (fe->ops.i2c_gate_ctrl)
			fe->ops.i2c_gate_ctrl(fe, 1);

		fe->ops.tuner_ops.set_params(fe);

		अगर (fe->ops.i2c_gate_ctrl)
			fe->ops.i2c_gate_ctrl(fe, 0);
	पूर्ण

	/* Issue a reset to the demod so it knows to resync against the
	   newly tuned frequency */
	s5h1411_softreset(fe);

	वापस 0;
पूर्ण

/* Reset the demod hardware and reset all of the configuration रेजिस्टरs
   to a शेष state. */
अटल पूर्णांक s5h1411_init(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा s5h1411_state *state = fe->demodulator_priv;
	पूर्णांक i;

	dprपूर्णांकk("%s()\n", __func__);

	s5h1411_set_घातerstate(fe, 0);
	s5h1411_रेजिस्टर_reset(fe);

	क्रम (i = 0; i < ARRAY_SIZE(init_tab); i++)
		s5h1411_ग_लिखोreg(state, init_tab[i].addr,
			init_tab[i].reg,
			init_tab[i].data);

	/* The datasheet says that after initialisation, VSB is शेष */
	state->current_modulation = VSB_8;

	/* Although the datasheet says it's in VSB, empirical evidence
	   shows problems getting lock on the first tuning request.  Make
	   sure we call enable_modulation the first समय around */
	state->first_tune = 1;

	अगर (state->config->output_mode == S5H1411_SERIAL_OUTPUT)
		/* Serial */
		s5h1411_set_serialmode(fe, 1);
	अन्यथा
		/* Parallel */
		s5h1411_set_serialmode(fe, 0);

	s5h1411_set_spectralinversion(fe, state->config->inversion);
	s5h1411_set_अगर_freq(fe, state->config->vsb_अगर);
	s5h1411_set_gpio(fe, state->config->gpio);
	s5h1411_set_mpeg_timing(fe, state->config->mpeg_timing);
	s5h1411_softreset(fe);

	/* Note: Leaving the I2C gate बंदd. */
	s5h1411_i2c_gate_ctrl(fe, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक s5h1411_पढ़ो_status(काष्ठा dvb_frontend *fe, क्रमागत fe_status *status)
अणु
	काष्ठा s5h1411_state *state = fe->demodulator_priv;
	u16 reg;
	u32 tuner_status = 0;

	*status = 0;

	/* Register F2 bit 15 = Master Lock, हटाओd */

	चयन (state->current_modulation) अणु
	हाल QAM_64:
	हाल QAM_256:
		reg = s5h1411_पढ़ोreg(state, S5H1411_I2C_TOP_ADDR, 0xf0);
		अगर (reg & 0x10) /* QAM FEC Lock */
			*status |= FE_HAS_SYNC | FE_HAS_LOCK;
		अगर (reg & 0x100) /* QAM EQ Lock */
			*status |= FE_HAS_VITERBI | FE_HAS_CARRIER | FE_HAS_SIGNAL;

		अवरोध;
	हाल VSB_8:
		reg = s5h1411_पढ़ोreg(state, S5H1411_I2C_TOP_ADDR, 0xf2);
		अगर (reg & 0x1000) /* FEC Lock */
			*status |= FE_HAS_SYNC | FE_HAS_LOCK;
		अगर (reg & 0x2000) /* EQ Lock */
			*status |= FE_HAS_VITERBI | FE_HAS_CARRIER | FE_HAS_SIGNAL;

		reg = s5h1411_पढ़ोreg(state, S5H1411_I2C_TOP_ADDR, 0x53);
		अगर (reg & 0x1) /* AFC Lock */
			*status |= FE_HAS_SIGNAL;

		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (state->config->status_mode) अणु
	हाल S5H1411_DEMODLOCKING:
		अगर (*status & FE_HAS_VITERBI)
			*status |= FE_HAS_CARRIER | FE_HAS_SIGNAL;
		अवरोध;
	हाल S5H1411_TUNERLOCKING:
		/* Get the tuner status */
		अगर (fe->ops.tuner_ops.get_status) अणु
			अगर (fe->ops.i2c_gate_ctrl)
				fe->ops.i2c_gate_ctrl(fe, 1);

			fe->ops.tuner_ops.get_status(fe, &tuner_status);

			अगर (fe->ops.i2c_gate_ctrl)
				fe->ops.i2c_gate_ctrl(fe, 0);
		पूर्ण
		अगर (tuner_status)
			*status |= FE_HAS_CARRIER | FE_HAS_SIGNAL;
		अवरोध;
	पूर्ण

	dprपूर्णांकk("%s() status 0x%08x\n", __func__, *status);

	वापस 0;
पूर्ण

अटल पूर्णांक s5h1411_qam256_lookup_snr(काष्ठा dvb_frontend *fe, u16 *snr, u16 v)
अणु
	पूर्णांक i, ret = -EINVAL;
	dprपूर्णांकk("%s()\n", __func__);

	क्रम (i = 0; i < ARRAY_SIZE(qam256_snr_tab); i++) अणु
		अगर (v < qam256_snr_tab[i].val) अणु
			*snr = qam256_snr_tab[i].data;
			ret = 0;
			अवरोध;
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक s5h1411_qam64_lookup_snr(काष्ठा dvb_frontend *fe, u16 *snr, u16 v)
अणु
	पूर्णांक i, ret = -EINVAL;
	dprपूर्णांकk("%s()\n", __func__);

	क्रम (i = 0; i < ARRAY_SIZE(qam64_snr_tab); i++) अणु
		अगर (v < qam64_snr_tab[i].val) अणु
			*snr = qam64_snr_tab[i].data;
			ret = 0;
			अवरोध;
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक s5h1411_vsb_lookup_snr(काष्ठा dvb_frontend *fe, u16 *snr, u16 v)
अणु
	पूर्णांक i, ret = -EINVAL;
	dprपूर्णांकk("%s()\n", __func__);

	क्रम (i = 0; i < ARRAY_SIZE(vsb_snr_tab); i++) अणु
		अगर (v > vsb_snr_tab[i].val) अणु
			*snr = vsb_snr_tab[i].data;
			ret = 0;
			अवरोध;
		पूर्ण
	पूर्ण
	dprपूर्णांकk("%s() snr=%d\n", __func__, *snr);
	वापस ret;
पूर्ण

अटल पूर्णांक s5h1411_पढ़ो_snr(काष्ठा dvb_frontend *fe, u16 *snr)
अणु
	काष्ठा s5h1411_state *state = fe->demodulator_priv;
	u16 reg;
	dprपूर्णांकk("%s()\n", __func__);

	चयन (state->current_modulation) अणु
	हाल QAM_64:
		reg = s5h1411_पढ़ोreg(state, S5H1411_I2C_TOP_ADDR, 0xf1);
		वापस s5h1411_qam64_lookup_snr(fe, snr, reg);
	हाल QAM_256:
		reg = s5h1411_पढ़ोreg(state, S5H1411_I2C_TOP_ADDR, 0xf1);
		वापस s5h1411_qam256_lookup_snr(fe, snr, reg);
	हाल VSB_8:
		reg = s5h1411_पढ़ोreg(state, S5H1411_I2C_TOP_ADDR,
			0xf2) & 0x3ff;
		वापस s5h1411_vsb_lookup_snr(fe, snr, reg);
	शेष:
		अवरोध;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक s5h1411_पढ़ो_संकेत_strength(काष्ठा dvb_frontend *fe,
	u16 *संकेत_strength)
अणु
	/* borrowed from lgdt330x.c
	 *
	 * Calculate strength from SNR up to 35dB
	 * Even though the SNR can go higher than 35dB,
	 * there is some comक्रमt factor in having a range of
	 * strong संकेतs that can show at 100%
	 */
	u16 snr;
	u32 पंचांगp;
	पूर्णांक ret = s5h1411_पढ़ो_snr(fe, &snr);

	*संकेत_strength = 0;

	अगर (0 == ret) अणु
		/* The following calculation method was chosen
		 * purely क्रम the sake of code re-use from the
		 * other demod drivers that use this method */

		/* Convert from SNR in dB * 10 to 8.24 fixed-poपूर्णांक */
		पंचांगp = (snr * ((1 << 24) / 10));

		/* Convert from 8.24 fixed-poपूर्णांक to
		 * scale the range 0 - 35*2^24 पूर्णांकo 0 - 65535*/
		अगर (पंचांगp >= 8960 * 0x10000)
			*संकेत_strength = 0xffff;
		अन्यथा
			*संकेत_strength = पंचांगp / 8960;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक s5h1411_पढ़ो_ucblocks(काष्ठा dvb_frontend *fe, u32 *ucblocks)
अणु
	काष्ठा s5h1411_state *state = fe->demodulator_priv;

	*ucblocks = s5h1411_पढ़ोreg(state, S5H1411_I2C_TOP_ADDR, 0xc9);

	वापस 0;
पूर्ण

अटल पूर्णांक s5h1411_पढ़ो_ber(काष्ठा dvb_frontend *fe, u32 *ber)
अणु
	वापस s5h1411_पढ़ो_ucblocks(fe, ber);
पूर्ण

अटल पूर्णांक s5h1411_get_frontend(काष्ठा dvb_frontend *fe,
				काष्ठा dtv_frontend_properties *p)
अणु
	काष्ठा s5h1411_state *state = fe->demodulator_priv;

	p->frequency = state->current_frequency;
	p->modulation = state->current_modulation;

	वापस 0;
पूर्ण

अटल पूर्णांक s5h1411_get_tune_settings(काष्ठा dvb_frontend *fe,
				     काष्ठा dvb_frontend_tune_settings *tune)
अणु
	tune->min_delay_ms = 1000;
	वापस 0;
पूर्ण

अटल व्योम s5h1411_release(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा s5h1411_state *state = fe->demodulator_priv;
	kमुक्त(state);
पूर्ण

अटल स्थिर काष्ठा dvb_frontend_ops s5h1411_ops;

काष्ठा dvb_frontend *s5h1411_attach(स्थिर काष्ठा s5h1411_config *config,
				    काष्ठा i2c_adapter *i2c)
अणु
	काष्ठा s5h1411_state *state = शून्य;
	u16 reg;

	/* allocate memory क्रम the पूर्णांकernal state */
	state = kzalloc(माप(काष्ठा s5h1411_state), GFP_KERNEL);
	अगर (state == शून्य)
		जाओ error;

	/* setup the state */
	state->config = config;
	state->i2c = i2c;
	state->current_modulation = VSB_8;
	state->inversion = state->config->inversion;

	/* check अगर the demod exists */
	reg = s5h1411_पढ़ोreg(state, S5H1411_I2C_TOP_ADDR, 0x05);
	अगर (reg != 0x0066)
		जाओ error;

	/* create dvb_frontend */
	स_नकल(&state->frontend.ops, &s5h1411_ops,
	       माप(काष्ठा dvb_frontend_ops));

	state->frontend.demodulator_priv = state;

	अगर (s5h1411_init(&state->frontend) != 0) अणु
		prपूर्णांकk(KERN_ERR "%s: Failed to initialize correctly\n",
			__func__);
		जाओ error;
	पूर्ण

	/* Note: Leaving the I2C gate खोलो here. */
	s5h1411_ग_लिखोreg(state, S5H1411_I2C_TOP_ADDR, 0xf5, 1);

	/* Put the device पूर्णांकo low-घातer mode until first use */
	s5h1411_set_घातerstate(&state->frontend, 1);

	वापस &state->frontend;

error:
	kमुक्त(state);
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(s5h1411_attach);

अटल स्थिर काष्ठा dvb_frontend_ops s5h1411_ops = अणु
	.delsys = अणु SYS_ATSC, SYS_DVBC_ANNEX_B पूर्ण,
	.info = अणु
		.name			= "Samsung S5H1411 QAM/8VSB Frontend",
		.frequency_min_hz	=  54 * MHz,
		.frequency_max_hz	= 858 * MHz,
		.frequency_stepsize_hz	= 62500,
		.caps = FE_CAN_QAM_64 | FE_CAN_QAM_256 | FE_CAN_8VSB
	पूर्ण,

	.init                 = s5h1411_init,
	.sleep                = s5h1411_sleep,
	.i2c_gate_ctrl        = s5h1411_i2c_gate_ctrl,
	.set_frontend         = s5h1411_set_frontend,
	.get_frontend         = s5h1411_get_frontend,
	.get_tune_settings    = s5h1411_get_tune_settings,
	.पढ़ो_status          = s5h1411_पढ़ो_status,
	.पढ़ो_ber             = s5h1411_पढ़ो_ber,
	.पढ़ो_संकेत_strength = s5h1411_पढ़ो_संकेत_strength,
	.पढ़ो_snr             = s5h1411_पढ़ो_snr,
	.पढ़ो_ucblocks        = s5h1411_पढ़ो_ucblocks,
	.release              = s5h1411_release,
पूर्ण;

module_param(debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug, "Enable verbose debug messages");

MODULE_DESCRIPTION("Samsung S5H1411 QAM-B/ATSC Demodulator driver");
MODULE_AUTHOR("Steven Toth");
MODULE_LICENSE("GPL");
