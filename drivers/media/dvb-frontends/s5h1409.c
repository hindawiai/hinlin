<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
    Samsung S5H1409 VSB/QAM demodulator driver

    Copyright (C) 2006 Steven Toth <stoth@linuxtv.org>


*/

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/माला.स>
#समावेश <linux/slab.h>
#समावेश <linux/delay.h>
#समावेश <media/dvb_frontend.h>
#समावेश "s5h1409.h"

काष्ठा s5h1409_state अणु

	काष्ठा i2c_adapter *i2c;

	/* configuration settings */
	स्थिर काष्ठा s5h1409_config *config;

	काष्ठा dvb_frontend frontend;

	/* previous uncorrected block counter */
	क्रमागत fe_modulation current_modulation;

	u32 current_frequency;
	पूर्णांक अगर_freq;

	u32 is_qam_locked;

	/* QAM tuning state goes through the following state transitions */
#घोषणा QAM_STATE_UNTUNED 0
#घोषणा QAM_STATE_TUNING_STARTED 1
#घोषणा QAM_STATE_INTERLEAVE_SET 2
#घोषणा QAM_STATE_QAM_OPTIMIZED_L1 3
#घोषणा QAM_STATE_QAM_OPTIMIZED_L2 4
#घोषणा QAM_STATE_QAM_OPTIMIZED_L3 5
	u8  qam_state;
पूर्ण;

अटल पूर्णांक debug;
module_param(debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug, "Enable verbose debug messages");

#घोषणा dprपूर्णांकk	अगर (debug) prपूर्णांकk

/* Register values to initialise the demod, this will set VSB by शेष */
अटल काष्ठा init_tab अणु
	u8	reg;
	u16	data;
पूर्ण init_tab[] = अणु
	अणु 0x00, 0x0071, पूर्ण,
	अणु 0x01, 0x3213, पूर्ण,
	अणु 0x09, 0x0025, पूर्ण,
	अणु 0x1c, 0x001d, पूर्ण,
	अणु 0x1f, 0x002d, पूर्ण,
	अणु 0x20, 0x001d, पूर्ण,
	अणु 0x22, 0x0022, पूर्ण,
	अणु 0x23, 0x0020, पूर्ण,
	अणु 0x29, 0x110f, पूर्ण,
	अणु 0x2a, 0x10b4, पूर्ण,
	अणु 0x2b, 0x10ae, पूर्ण,
	अणु 0x2c, 0x0031, पूर्ण,
	अणु 0x31, 0x010d, पूर्ण,
	अणु 0x32, 0x0100, पूर्ण,
	अणु 0x44, 0x0510, पूर्ण,
	अणु 0x54, 0x0104, पूर्ण,
	अणु 0x58, 0x2222, पूर्ण,
	अणु 0x59, 0x1162, पूर्ण,
	अणु 0x5a, 0x3211, पूर्ण,
	अणु 0x5d, 0x0370, पूर्ण,
	अणु 0x5e, 0x0296, पूर्ण,
	अणु 0x61, 0x0010, पूर्ण,
	अणु 0x63, 0x4a00, पूर्ण,
	अणु 0x65, 0x0800, पूर्ण,
	अणु 0x71, 0x0003, पूर्ण,
	अणु 0x72, 0x0470, पूर्ण,
	अणु 0x81, 0x0002, पूर्ण,
	अणु 0x82, 0x0600, पूर्ण,
	अणु 0x86, 0x0002, पूर्ण,
	अणु 0x8a, 0x2c38, पूर्ण,
	अणु 0x8b, 0x2a37, पूर्ण,
	अणु 0x92, 0x302f, पूर्ण,
	अणु 0x93, 0x3332, पूर्ण,
	अणु 0x96, 0x000c, पूर्ण,
	अणु 0x99, 0x0101, पूर्ण,
	अणु 0x9c, 0x2e37, पूर्ण,
	अणु 0x9d, 0x2c37, पूर्ण,
	अणु 0x9e, 0x2c37, पूर्ण,
	अणु 0xab, 0x0100, पूर्ण,
	अणु 0xac, 0x1003, पूर्ण,
	अणु 0xad, 0x103f, पूर्ण,
	अणु 0xe2, 0x0100, पूर्ण,
	अणु 0xe3, 0x1000, पूर्ण,
	अणु 0x28, 0x1010, पूर्ण,
	अणु 0xb1, 0x000e, पूर्ण,
पूर्ण;

/* VSB SNR lookup table */
अटल काष्ठा vsb_snr_tab अणु
	u16	val;
	u16	data;
पूर्ण vsb_snr_tab[] = अणु
	अणु  924, 300, पूर्ण,
	अणु  923, 300, पूर्ण,
	अणु  918, 295, पूर्ण,
	अणु  915, 290, पूर्ण,
	अणु  911, 285, पूर्ण,
	अणु  906, 280, पूर्ण,
	अणु  901, 275, पूर्ण,
	अणु  896, 270, पूर्ण,
	अणु  891, 265, पूर्ण,
	अणु  885, 260, पूर्ण,
	अणु  879, 255, पूर्ण,
	अणु  873, 250, पूर्ण,
	अणु  864, 245, पूर्ण,
	अणु  858, 240, पूर्ण,
	अणु  850, 235, पूर्ण,
	अणु  841, 230, पूर्ण,
	अणु  832, 225, पूर्ण,
	अणु  823, 220, पूर्ण,
	अणु  812, 215, पूर्ण,
	अणु  802, 210, पूर्ण,
	अणु  788, 205, पूर्ण,
	अणु  778, 200, पूर्ण,
	अणु  767, 195, पूर्ण,
	अणु  753, 190, पूर्ण,
	अणु  740, 185, पूर्ण,
	अणु  725, 180, पूर्ण,
	अणु  707, 175, पूर्ण,
	अणु  689, 170, पूर्ण,
	अणु  671, 165, पूर्ण,
	अणु  656, 160, पूर्ण,
	अणु  637, 155, पूर्ण,
	अणु  616, 150, पूर्ण,
	अणु  542, 145, पूर्ण,
	अणु  519, 140, पूर्ण,
	अणु  507, 135, पूर्ण,
	अणु  497, 130, पूर्ण,
	अणु  492, 125, पूर्ण,
	अणु  474, 120, पूर्ण,
	अणु  300, 111, पूर्ण,
	अणु    0,   0, पूर्ण,
पूर्ण;

/* QAM64 SNR lookup table */
अटल काष्ठा qam64_snr_tab अणु
	u16	val;
	u16	data;
पूर्ण qam64_snr_tab[] = अणु
	अणु    1,   0, पूर्ण,
	अणु   12, 300, पूर्ण,
	अणु   15, 290, पूर्ण,
	अणु   18, 280, पूर्ण,
	अणु   22, 270, पूर्ण,
	अणु   23, 268, पूर्ण,
	अणु   24, 266, पूर्ण,
	अणु   25, 264, पूर्ण,
	अणु   27, 262, पूर्ण,
	अणु   28, 260, पूर्ण,
	अणु   29, 258, पूर्ण,
	अणु   30, 256, पूर्ण,
	अणु   32, 254, पूर्ण,
	अणु   33, 252, पूर्ण,
	अणु   34, 250, पूर्ण,
	अणु   35, 249, पूर्ण,
	अणु   36, 248, पूर्ण,
	अणु   37, 247, पूर्ण,
	अणु   38, 246, पूर्ण,
	अणु   39, 245, पूर्ण,
	अणु   40, 244, पूर्ण,
	अणु   41, 243, पूर्ण,
	अणु   42, 241, पूर्ण,
	अणु   43, 240, पूर्ण,
	अणु   44, 239, पूर्ण,
	अणु   45, 238, पूर्ण,
	अणु   46, 237, पूर्ण,
	अणु   47, 236, पूर्ण,
	अणु   48, 235, पूर्ण,
	अणु   49, 234, पूर्ण,
	अणु   50, 233, पूर्ण,
	अणु   51, 232, पूर्ण,
	अणु   52, 231, पूर्ण,
	अणु   53, 230, पूर्ण,
	अणु   55, 229, पूर्ण,
	अणु   56, 228, पूर्ण,
	अणु   57, 227, पूर्ण,
	अणु   58, 226, पूर्ण,
	अणु   59, 225, पूर्ण,
	अणु   60, 224, पूर्ण,
	अणु   62, 223, पूर्ण,
	अणु   63, 222, पूर्ण,
	अणु   65, 221, पूर्ण,
	अणु   66, 220, पूर्ण,
	अणु   68, 219, पूर्ण,
	अणु   69, 218, पूर्ण,
	अणु   70, 217, पूर्ण,
	अणु   72, 216, पूर्ण,
	अणु   73, 215, पूर्ण,
	अणु   75, 214, पूर्ण,
	अणु   76, 213, पूर्ण,
	अणु   78, 212, पूर्ण,
	अणु   80, 211, पूर्ण,
	अणु   81, 210, पूर्ण,
	अणु   83, 209, पूर्ण,
	अणु   84, 208, पूर्ण,
	अणु   85, 207, पूर्ण,
	अणु   87, 206, पूर्ण,
	अणु   89, 205, पूर्ण,
	अणु   91, 204, पूर्ण,
	अणु   93, 203, पूर्ण,
	अणु   95, 202, पूर्ण,
	अणु   96, 201, पूर्ण,
	अणु  104, 200, पूर्ण,
	अणु  255,   0, पूर्ण,
पूर्ण;

/* QAM256 SNR lookup table */
अटल काष्ठा qam256_snr_tab अणु
	u16	val;
	u16	data;
पूर्ण qam256_snr_tab[] = अणु
	अणु    1,   0, पूर्ण,
	अणु   12, 400, पूर्ण,
	अणु   13, 390, पूर्ण,
	अणु   15, 380, पूर्ण,
	अणु   17, 360, पूर्ण,
	अणु   19, 350, पूर्ण,
	अणु   22, 348, पूर्ण,
	अणु   23, 346, पूर्ण,
	अणु   24, 344, पूर्ण,
	अणु   25, 342, पूर्ण,
	अणु   26, 340, पूर्ण,
	अणु   27, 336, पूर्ण,
	अणु   28, 334, पूर्ण,
	अणु   29, 332, पूर्ण,
	अणु   30, 330, पूर्ण,
	अणु   31, 328, पूर्ण,
	अणु   32, 326, पूर्ण,
	अणु   33, 325, पूर्ण,
	अणु   34, 322, पूर्ण,
	अणु   35, 320, पूर्ण,
	अणु   37, 318, पूर्ण,
	अणु   39, 316, पूर्ण,
	अणु   40, 314, पूर्ण,
	अणु   41, 312, पूर्ण,
	अणु   42, 310, पूर्ण,
	अणु   43, 308, पूर्ण,
	अणु   46, 306, पूर्ण,
	अणु   47, 304, पूर्ण,
	अणु   49, 302, पूर्ण,
	अणु   51, 300, पूर्ण,
	अणु   53, 298, पूर्ण,
	अणु   54, 297, पूर्ण,
	अणु   55, 296, पूर्ण,
	अणु   56, 295, पूर्ण,
	अणु   57, 294, पूर्ण,
	अणु   59, 293, पूर्ण,
	अणु   60, 292, पूर्ण,
	अणु   61, 291, पूर्ण,
	अणु   63, 290, पूर्ण,
	अणु   64, 289, पूर्ण,
	अणु   65, 288, पूर्ण,
	अणु   66, 287, पूर्ण,
	अणु   68, 286, पूर्ण,
	अणु   69, 285, पूर्ण,
	अणु   71, 284, पूर्ण,
	अणु   72, 283, पूर्ण,
	अणु   74, 282, पूर्ण,
	अणु   75, 281, पूर्ण,
	अणु   76, 280, पूर्ण,
	अणु   77, 279, पूर्ण,
	अणु   78, 278, पूर्ण,
	अणु   81, 277, पूर्ण,
	अणु   83, 276, पूर्ण,
	अणु   84, 275, पूर्ण,
	अणु   86, 274, पूर्ण,
	अणु   87, 273, पूर्ण,
	अणु   89, 272, पूर्ण,
	अणु   90, 271, पूर्ण,
	अणु   92, 270, पूर्ण,
	अणु   93, 269, पूर्ण,
	अणु   95, 268, पूर्ण,
	अणु   96, 267, पूर्ण,
	अणु   98, 266, पूर्ण,
	अणु  100, 265, पूर्ण,
	अणु  102, 264, पूर्ण,
	अणु  104, 263, पूर्ण,
	अणु  105, 262, पूर्ण,
	अणु  106, 261, पूर्ण,
	अणु  110, 260, पूर्ण,
	अणु  255,   0, पूर्ण,
पूर्ण;

/* 8 bit रेजिस्टरs, 16 bit values */
अटल पूर्णांक s5h1409_ग_लिखोreg(काष्ठा s5h1409_state *state, u8 reg, u16 data)
अणु
	पूर्णांक ret;
	u8 buf[] = अणु reg, data >> 8,  data & 0xff पूर्ण;

	काष्ठा i2c_msg msg = अणु .addr = state->config->demod_address,
			       .flags = 0, .buf = buf, .len = 3 पूर्ण;

	ret = i2c_transfer(state->i2c, &msg, 1);

	अगर (ret != 1)
		prपूर्णांकk(KERN_ERR "%s: error (reg == 0x%02x, val == 0x%04x, ret == %i)\n",
		       __func__, reg, data, ret);

	वापस (ret != 1) ? -1 : 0;
पूर्ण

अटल u16 s5h1409_पढ़ोreg(काष्ठा s5h1409_state *state, u8 reg)
अणु
	पूर्णांक ret;
	u8 b0[] = अणु reg पूर्ण;
	u8 b1[] = अणु 0, 0 पूर्ण;

	काष्ठा i2c_msg msg[] = अणु
		अणु .addr = state->config->demod_address, .flags = 0,
		  .buf = b0, .len = 1 पूर्ण,
		अणु .addr = state->config->demod_address, .flags = I2C_M_RD,
		  .buf = b1, .len = 2 पूर्ण पूर्ण;

	ret = i2c_transfer(state->i2c, msg, 2);

	अगर (ret != 2)
		prपूर्णांकk("%s: readreg error (ret == %i)\n", __func__, ret);
	वापस (b1[0] << 8) | b1[1];
पूर्ण

अटल पूर्णांक s5h1409_softreset(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा s5h1409_state *state = fe->demodulator_priv;

	dprपूर्णांकk("%s()\n", __func__);

	s5h1409_ग_लिखोreg(state, 0xf5, 0);
	s5h1409_ग_लिखोreg(state, 0xf5, 1);
	state->is_qam_locked = 0;
	state->qam_state = QAM_STATE_UNTUNED;
	वापस 0;
पूर्ण

#घोषणा S5H1409_VSB_IF_FREQ 5380
#घोषणा S5H1409_QAM_IF_FREQ (state->config->qam_अगर)

अटल पूर्णांक s5h1409_set_अगर_freq(काष्ठा dvb_frontend *fe, पूर्णांक KHz)
अणु
	काष्ठा s5h1409_state *state = fe->demodulator_priv;

	dprपूर्णांकk("%s(%d KHz)\n", __func__, KHz);

	चयन (KHz) अणु
	हाल 4000:
		s5h1409_ग_लिखोreg(state, 0x87, 0x014b);
		s5h1409_ग_लिखोreg(state, 0x88, 0x0cb5);
		s5h1409_ग_लिखोreg(state, 0x89, 0x03e2);
		अवरोध;
	हाल 5380:
	हाल 44000:
	शेष:
		s5h1409_ग_लिखोreg(state, 0x87, 0x01be);
		s5h1409_ग_लिखोreg(state, 0x88, 0x0436);
		s5h1409_ग_लिखोreg(state, 0x89, 0x054d);
		अवरोध;
	पूर्ण
	state->अगर_freq = KHz;

	वापस 0;
पूर्ण

अटल पूर्णांक s5h1409_set_spectralinversion(काष्ठा dvb_frontend *fe, पूर्णांक inverted)
अणु
	काष्ठा s5h1409_state *state = fe->demodulator_priv;

	dprपूर्णांकk("%s(%d)\n", __func__, inverted);

	अगर (inverted == 1)
		वापस s5h1409_ग_लिखोreg(state, 0x1b, 0x1101); /* Inverted */
	अन्यथा
		वापस s5h1409_ग_लिखोreg(state, 0x1b, 0x0110); /* Normal */
पूर्ण

अटल पूर्णांक s5h1409_enable_modulation(काष्ठा dvb_frontend *fe,
				     क्रमागत fe_modulation m)
अणु
	काष्ठा s5h1409_state *state = fe->demodulator_priv;

	dprपूर्णांकk("%s(0x%08x)\n", __func__, m);

	चयन (m) अणु
	हाल VSB_8:
		dprपूर्णांकk("%s() VSB_8\n", __func__);
		अगर (state->अगर_freq != S5H1409_VSB_IF_FREQ)
			s5h1409_set_अगर_freq(fe, S5H1409_VSB_IF_FREQ);
		s5h1409_ग_लिखोreg(state, 0xf4, 0);
		अवरोध;
	हाल QAM_64:
	हाल QAM_256:
	हाल QAM_AUTO:
		dprपूर्णांकk("%s() QAM_AUTO (64/256)\n", __func__);
		अगर (state->अगर_freq != S5H1409_QAM_IF_FREQ)
			s5h1409_set_अगर_freq(fe, S5H1409_QAM_IF_FREQ);
		s5h1409_ग_लिखोreg(state, 0xf4, 1);
		s5h1409_ग_लिखोreg(state, 0x85, 0x110);
		अवरोध;
	शेष:
		dprपूर्णांकk("%s() Invalid modulation\n", __func__);
		वापस -EINVAL;
	पूर्ण

	state->current_modulation = m;
	s5h1409_softreset(fe);

	वापस 0;
पूर्ण

अटल पूर्णांक s5h1409_i2c_gate_ctrl(काष्ठा dvb_frontend *fe, पूर्णांक enable)
अणु
	काष्ठा s5h1409_state *state = fe->demodulator_priv;

	dprपूर्णांकk("%s(%d)\n", __func__, enable);

	अगर (enable)
		वापस s5h1409_ग_लिखोreg(state, 0xf3, 1);
	अन्यथा
		वापस s5h1409_ग_लिखोreg(state, 0xf3, 0);
पूर्ण

अटल पूर्णांक s5h1409_set_gpio(काष्ठा dvb_frontend *fe, पूर्णांक enable)
अणु
	काष्ठा s5h1409_state *state = fe->demodulator_priv;

	dprपूर्णांकk("%s(%d)\n", __func__, enable);

	अगर (enable)
		वापस s5h1409_ग_लिखोreg(state, 0xe3,
			s5h1409_पढ़ोreg(state, 0xe3) | 0x1100);
	अन्यथा
		वापस s5h1409_ग_लिखोreg(state, 0xe3,
			s5h1409_पढ़ोreg(state, 0xe3) & 0xfeff);
पूर्ण

अटल पूर्णांक s5h1409_sleep(काष्ठा dvb_frontend *fe, पूर्णांक enable)
अणु
	काष्ठा s5h1409_state *state = fe->demodulator_priv;

	dprपूर्णांकk("%s(%d)\n", __func__, enable);

	वापस s5h1409_ग_लिखोreg(state, 0xf2, enable);
पूर्ण

अटल पूर्णांक s5h1409_रेजिस्टर_reset(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा s5h1409_state *state = fe->demodulator_priv;

	dprपूर्णांकk("%s()\n", __func__);

	वापस s5h1409_ग_लिखोreg(state, 0xfa, 0);
पूर्ण

अटल व्योम s5h1409_set_qam_amhum_mode(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा s5h1409_state *state = fe->demodulator_priv;
	u16 reg;

	अगर (state->qam_state < QAM_STATE_INTERLEAVE_SET) अणु
		/* We should not perक्रमm amhum optimization until
		   the पूर्णांकerleave mode has been configured */
		वापस;
	पूर्ण

	अगर (state->qam_state == QAM_STATE_QAM_OPTIMIZED_L3) अणु
		/* We've alपढ़ोy reached the maximum optimization level, so
		   करोn't bother banging on the status रेजिस्टरs */
		वापस;
	पूर्ण

	/* QAM EQ lock check */
	reg = s5h1409_पढ़ोreg(state, 0xf0);

	अगर ((reg >> 13) & 0x1) अणु
		reg &= 0xff;

		s5h1409_ग_लिखोreg(state, 0x96, 0x000c);
		अगर (reg < 0x68) अणु
			अगर (state->qam_state < QAM_STATE_QAM_OPTIMIZED_L3) अणु
				dprपूर्णांकk("%s() setting QAM state to OPT_L3\n",
					__func__);
				s5h1409_ग_लिखोreg(state, 0x93, 0x3130);
				s5h1409_ग_लिखोreg(state, 0x9e, 0x2836);
				state->qam_state = QAM_STATE_QAM_OPTIMIZED_L3;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (state->qam_state < QAM_STATE_QAM_OPTIMIZED_L2) अणु
				dprपूर्णांकk("%s() setting QAM state to OPT_L2\n",
					__func__);
				s5h1409_ग_लिखोreg(state, 0x93, 0x3332);
				s5h1409_ग_लिखोreg(state, 0x9e, 0x2c37);
				state->qam_state = QAM_STATE_QAM_OPTIMIZED_L2;
			पूर्ण
		पूर्ण

	पूर्ण अन्यथा अणु
		अगर (state->qam_state < QAM_STATE_QAM_OPTIMIZED_L1) अणु
			dprपूर्णांकk("%s() setting QAM state to OPT_L1\n", __func__);
			s5h1409_ग_लिखोreg(state, 0x96, 0x0008);
			s5h1409_ग_लिखोreg(state, 0x93, 0x3332);
			s5h1409_ग_लिखोreg(state, 0x9e, 0x2c37);
			state->qam_state = QAM_STATE_QAM_OPTIMIZED_L1;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम s5h1409_set_qam_amhum_mode_legacy(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा s5h1409_state *state = fe->demodulator_priv;
	u16 reg;

	अगर (state->is_qam_locked)
		वापस;

	/* QAM EQ lock check */
	reg = s5h1409_पढ़ोreg(state, 0xf0);

	अगर ((reg >> 13) & 0x1) अणु

		state->is_qam_locked = 1;
		reg &= 0xff;

		s5h1409_ग_लिखोreg(state, 0x96, 0x00c);
		अगर ((reg < 0x38) || (reg > 0x68)) अणु
			s5h1409_ग_लिखोreg(state, 0x93, 0x3332);
			s5h1409_ग_लिखोreg(state, 0x9e, 0x2c37);
		पूर्ण अन्यथा अणु
			s5h1409_ग_लिखोreg(state, 0x93, 0x3130);
			s5h1409_ग_लिखोreg(state, 0x9e, 0x2836);
		पूर्ण

	पूर्ण अन्यथा अणु
		s5h1409_ग_लिखोreg(state, 0x96, 0x0008);
		s5h1409_ग_लिखोreg(state, 0x93, 0x3332);
		s5h1409_ग_लिखोreg(state, 0x9e, 0x2c37);
	पूर्ण
पूर्ण

अटल व्योम s5h1409_set_qam_पूर्णांकerleave_mode(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा s5h1409_state *state = fe->demodulator_priv;
	u16 reg, reg1, reg2;

	अगर (state->qam_state >= QAM_STATE_INTERLEAVE_SET) अणु
		/* We've करोne the optimization alपढ़ोy */
		वापस;
	पूर्ण

	reg = s5h1409_पढ़ोreg(state, 0xf1);

	/* Master lock */
	अगर ((reg >> 15) & 0x1) अणु
		अगर (state->qam_state == QAM_STATE_UNTUNED ||
		    state->qam_state == QAM_STATE_TUNING_STARTED) अणु
			dprपूर्णांकk("%s() setting QAM state to INTERLEAVE_SET\n",
				__func__);
			reg1 = s5h1409_पढ़ोreg(state, 0xb2);
			reg2 = s5h1409_पढ़ोreg(state, 0xad);

			s5h1409_ग_लिखोreg(state, 0x96, 0x0020);
			s5h1409_ग_लिखोreg(state, 0xad,
				(((reg1 & 0xf000) >> 4) | (reg2 & 0xf0ff)));
			state->qam_state = QAM_STATE_INTERLEAVE_SET;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (state->qam_state == QAM_STATE_UNTUNED) अणु
			dprपूर्णांकk("%s() setting QAM state to TUNING_STARTED\n",
				__func__);
			s5h1409_ग_लिखोreg(state, 0x96, 0x08);
			s5h1409_ग_लिखोreg(state, 0xab,
				s5h1409_पढ़ोreg(state, 0xab) | 0x1001);
			state->qam_state = QAM_STATE_TUNING_STARTED;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम s5h1409_set_qam_पूर्णांकerleave_mode_legacy(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा s5h1409_state *state = fe->demodulator_priv;
	u16 reg, reg1, reg2;

	reg = s5h1409_पढ़ोreg(state, 0xf1);

	/* Master lock */
	अगर ((reg >> 15) & 0x1) अणु
		अगर (state->qam_state != 2) अणु
			state->qam_state = 2;
			reg1 = s5h1409_पढ़ोreg(state, 0xb2);
			reg2 = s5h1409_पढ़ोreg(state, 0xad);

			s5h1409_ग_लिखोreg(state, 0x96, 0x20);
			s5h1409_ग_लिखोreg(state, 0xad,
				(((reg1 & 0xf000) >> 4) | (reg2 & 0xf0ff)));
			s5h1409_ग_लिखोreg(state, 0xab,
				s5h1409_पढ़ोreg(state, 0xab) & 0xeffe);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (state->qam_state != 1) अणु
			state->qam_state = 1;
			s5h1409_ग_लिखोreg(state, 0x96, 0x08);
			s5h1409_ग_लिखोreg(state, 0xab,
				s5h1409_पढ़ोreg(state, 0xab) | 0x1001);
		पूर्ण
	पूर्ण
पूर्ण

/* Talk to the demod, set the FEC, GUARD, QAM settings etc */
अटल पूर्णांक s5h1409_set_frontend(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dtv_frontend_properties *p = &fe->dtv_property_cache;
	काष्ठा s5h1409_state *state = fe->demodulator_priv;

	dprपूर्णांकk("%s(frequency=%d)\n", __func__, p->frequency);

	s5h1409_softreset(fe);

	state->current_frequency = p->frequency;

	s5h1409_enable_modulation(fe, p->modulation);

	अगर (fe->ops.tuner_ops.set_params) अणु
		अगर (fe->ops.i2c_gate_ctrl)
			fe->ops.i2c_gate_ctrl(fe, 1);
		fe->ops.tuner_ops.set_params(fe);
		अगर (fe->ops.i2c_gate_ctrl)
			fe->ops.i2c_gate_ctrl(fe, 0);
	पूर्ण

	/* Issue a reset to the demod so it knows to resync against the
	   newly tuned frequency */
	s5h1409_softreset(fe);

	/* Optimize the demod क्रम QAM */
	अगर (state->current_modulation != VSB_8) अणु
		/* This almost certainly applies to all boards, but क्रम now
		   only करो it क्रम the HVR-1600.  Once the other boards are
		   tested, the "legacy" versions can just go away */
		अगर (state->config->hvr1600_opt == S5H1409_HVR1600_OPTIMIZE) अणु
			s5h1409_set_qam_पूर्णांकerleave_mode(fe);
			s5h1409_set_qam_amhum_mode(fe);
		पूर्ण अन्यथा अणु
			s5h1409_set_qam_amhum_mode_legacy(fe);
			s5h1409_set_qam_पूर्णांकerleave_mode_legacy(fe);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक s5h1409_set_mpeg_timing(काष्ठा dvb_frontend *fe, पूर्णांक mode)
अणु
	काष्ठा s5h1409_state *state = fe->demodulator_priv;
	u16 val;

	dprपूर्णांकk("%s(%d)\n", __func__, mode);

	val = s5h1409_पढ़ोreg(state, 0xac) & 0xcfff;
	चयन (mode) अणु
	हाल S5H1409_MPEGTIMING_CONTINUOUS_INVERTING_CLOCK:
		val |= 0x0000;
		अवरोध;
	हाल S5H1409_MPEGTIMING_CONTINUOUS_NONINVERTING_CLOCK:
		dprपूर्णांकk("%s(%d) Mode1 or Defaulting\n", __func__, mode);
		val |= 0x1000;
		अवरोध;
	हाल S5H1409_MPEGTIMING_NONCONTINUOUS_INVERTING_CLOCK:
		val |= 0x2000;
		अवरोध;
	हाल S5H1409_MPEGTIMING_NONCONTINUOUS_NONINVERTING_CLOCK:
		val |= 0x3000;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* Configure MPEG Signal Timing अक्षरactistics */
	वापस s5h1409_ग_लिखोreg(state, 0xac, val);
पूर्ण

/* Reset the demod hardware and reset all of the configuration रेजिस्टरs
   to a शेष state. */
अटल पूर्णांक s5h1409_init(काष्ठा dvb_frontend *fe)
अणु
	पूर्णांक i;

	काष्ठा s5h1409_state *state = fe->demodulator_priv;
	dprपूर्णांकk("%s()\n", __func__);

	s5h1409_sleep(fe, 0);
	s5h1409_रेजिस्टर_reset(fe);

	क्रम (i = 0; i < ARRAY_SIZE(init_tab); i++)
		s5h1409_ग_लिखोreg(state, init_tab[i].reg, init_tab[i].data);

	/* The datasheet says that after initialisation, VSB is शेष */
	state->current_modulation = VSB_8;

	/* Optimize क्रम the HVR-1600 अगर appropriate.  Note that some of these
	   may get folded पूर्णांकo the generic हाल after testing with other
	   devices */
	अगर (state->config->hvr1600_opt == S5H1409_HVR1600_OPTIMIZE) अणु
		/* VSB AGC REF */
		s5h1409_ग_लिखोreg(state, 0x09, 0x0050);

		/* Unknown but Winकरोws driver करोes it... */
		s5h1409_ग_लिखोreg(state, 0x21, 0x0001);
		s5h1409_ग_लिखोreg(state, 0x50, 0x030e);

		/* QAM AGC REF */
		s5h1409_ग_लिखोreg(state, 0x82, 0x0800);
	पूर्ण

	अगर (state->config->output_mode == S5H1409_SERIAL_OUTPUT)
		s5h1409_ग_लिखोreg(state, 0xab,
			s5h1409_पढ़ोreg(state, 0xab) | 0x100); /* Serial */
	अन्यथा
		s5h1409_ग_लिखोreg(state, 0xab,
			s5h1409_पढ़ोreg(state, 0xab) & 0xfeff); /* Parallel */

	s5h1409_set_spectralinversion(fe, state->config->inversion);
	s5h1409_set_अगर_freq(fe, state->अगर_freq);
	s5h1409_set_gpio(fe, state->config->gpio);
	s5h1409_set_mpeg_timing(fe, state->config->mpeg_timing);
	s5h1409_softreset(fe);

	/* Note: Leaving the I2C gate बंदd. */
	s5h1409_i2c_gate_ctrl(fe, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक s5h1409_पढ़ो_status(काष्ठा dvb_frontend *fe, क्रमागत fe_status *status)
अणु
	काष्ठा s5h1409_state *state = fe->demodulator_priv;
	u16 reg;
	u32 tuner_status = 0;

	*status = 0;

	/* Optimize the demod क्रम QAM */
	अगर (state->current_modulation != VSB_8) अणु
		/* This almost certainly applies to all boards, but क्रम now
		   only करो it क्रम the HVR-1600.  Once the other boards are
		   tested, the "legacy" versions can just go away */
		अगर (state->config->hvr1600_opt == S5H1409_HVR1600_OPTIMIZE) अणु
			s5h1409_set_qam_पूर्णांकerleave_mode(fe);
			s5h1409_set_qam_amhum_mode(fe);
		पूर्ण
	पूर्ण

	/* Get the demodulator status */
	reg = s5h1409_पढ़ोreg(state, 0xf1);
	अगर (reg & 0x1000)
		*status |= FE_HAS_VITERBI;
	अगर (reg & 0x8000)
		*status |= FE_HAS_LOCK | FE_HAS_SYNC;

	चयन (state->config->status_mode) अणु
	हाल S5H1409_DEMODLOCKING:
		अगर (*status & FE_HAS_VITERBI)
			*status |= FE_HAS_CARRIER | FE_HAS_SIGNAL;
		अवरोध;
	हाल S5H1409_TUNERLOCKING:
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

अटल पूर्णांक s5h1409_qam256_lookup_snr(काष्ठा dvb_frontend *fe, u16 *snr, u16 v)
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

अटल पूर्णांक s5h1409_qam64_lookup_snr(काष्ठा dvb_frontend *fe, u16 *snr, u16 v)
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

अटल पूर्णांक s5h1409_vsb_lookup_snr(काष्ठा dvb_frontend *fe, u16 *snr, u16 v)
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

अटल पूर्णांक s5h1409_पढ़ो_snr(काष्ठा dvb_frontend *fe, u16 *snr)
अणु
	काष्ठा s5h1409_state *state = fe->demodulator_priv;
	u16 reg;
	dprपूर्णांकk("%s()\n", __func__);

	चयन (state->current_modulation) अणु
	हाल QAM_64:
		reg = s5h1409_पढ़ोreg(state, 0xf0) & 0xff;
		वापस s5h1409_qam64_lookup_snr(fe, snr, reg);
	हाल QAM_256:
		reg = s5h1409_पढ़ोreg(state, 0xf0) & 0xff;
		वापस s5h1409_qam256_lookup_snr(fe, snr, reg);
	हाल VSB_8:
		reg = s5h1409_पढ़ोreg(state, 0xf1) & 0x3ff;
		वापस s5h1409_vsb_lookup_snr(fe, snr, reg);
	शेष:
		अवरोध;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक s5h1409_पढ़ो_संकेत_strength(काष्ठा dvb_frontend *fe,
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
	पूर्णांक ret = s5h1409_पढ़ो_snr(fe, &snr);

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

अटल पूर्णांक s5h1409_पढ़ो_ucblocks(काष्ठा dvb_frontend *fe, u32 *ucblocks)
अणु
	काष्ठा s5h1409_state *state = fe->demodulator_priv;

	*ucblocks = s5h1409_पढ़ोreg(state, 0xb5);

	वापस 0;
पूर्ण

अटल पूर्णांक s5h1409_पढ़ो_ber(काष्ठा dvb_frontend *fe, u32 *ber)
अणु
	वापस s5h1409_पढ़ो_ucblocks(fe, ber);
पूर्ण

अटल पूर्णांक s5h1409_get_frontend(काष्ठा dvb_frontend *fe,
				काष्ठा dtv_frontend_properties *p)
अणु
	काष्ठा s5h1409_state *state = fe->demodulator_priv;

	p->frequency = state->current_frequency;
	p->modulation = state->current_modulation;

	वापस 0;
पूर्ण

अटल पूर्णांक s5h1409_get_tune_settings(काष्ठा dvb_frontend *fe,
				     काष्ठा dvb_frontend_tune_settings *tune)
अणु
	tune->min_delay_ms = 1000;
	वापस 0;
पूर्ण

अटल व्योम s5h1409_release(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा s5h1409_state *state = fe->demodulator_priv;
	kमुक्त(state);
पूर्ण

अटल स्थिर काष्ठा dvb_frontend_ops s5h1409_ops;

काष्ठा dvb_frontend *s5h1409_attach(स्थिर काष्ठा s5h1409_config *config,
				    काष्ठा i2c_adapter *i2c)
अणु
	काष्ठा s5h1409_state *state = शून्य;
	u16 reg;

	/* allocate memory क्रम the पूर्णांकernal state */
	state = kzalloc(माप(काष्ठा s5h1409_state), GFP_KERNEL);
	अगर (state == शून्य)
		जाओ error;

	/* setup the state */
	state->config = config;
	state->i2c = i2c;
	state->current_modulation = 0;
	state->अगर_freq = S5H1409_VSB_IF_FREQ;

	/* check अगर the demod exists */
	reg = s5h1409_पढ़ोreg(state, 0x04);
	अगर ((reg != 0x0066) && (reg != 0x007f))
		जाओ error;

	/* create dvb_frontend */
	स_नकल(&state->frontend.ops, &s5h1409_ops,
	       माप(काष्ठा dvb_frontend_ops));
	state->frontend.demodulator_priv = state;

	अगर (s5h1409_init(&state->frontend) != 0) अणु
		prपूर्णांकk(KERN_ERR "%s: Failed to initialize correctly\n",
			__func__);
		जाओ error;
	पूर्ण

	/* Note: Leaving the I2C gate खोलो here. */
	s5h1409_i2c_gate_ctrl(&state->frontend, 1);

	वापस &state->frontend;

error:
	kमुक्त(state);
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(s5h1409_attach);

अटल स्थिर काष्ठा dvb_frontend_ops s5h1409_ops = अणु
	.delsys = अणु SYS_ATSC, SYS_DVBC_ANNEX_B पूर्ण,
	.info = अणु
		.name			= "Samsung S5H1409 QAM/8VSB Frontend",
		.frequency_min_hz	=  54 * MHz,
		.frequency_max_hz	= 858 * MHz,
		.frequency_stepsize_hz	= 62500,
		.caps = FE_CAN_QAM_64 | FE_CAN_QAM_256 | FE_CAN_8VSB
	पूर्ण,

	.init                 = s5h1409_init,
	.i2c_gate_ctrl        = s5h1409_i2c_gate_ctrl,
	.set_frontend         = s5h1409_set_frontend,
	.get_frontend         = s5h1409_get_frontend,
	.get_tune_settings    = s5h1409_get_tune_settings,
	.पढ़ो_status          = s5h1409_पढ़ो_status,
	.पढ़ो_ber             = s5h1409_पढ़ो_ber,
	.पढ़ो_संकेत_strength = s5h1409_पढ़ो_संकेत_strength,
	.पढ़ो_snr             = s5h1409_पढ़ो_snr,
	.पढ़ो_ucblocks        = s5h1409_पढ़ो_ucblocks,
	.release              = s5h1409_release,
पूर्ण;

MODULE_DESCRIPTION("Samsung S5H1409 QAM-B/ATSC Demodulator driver");
MODULE_AUTHOR("Steven Toth");
MODULE_LICENSE("GPL");
