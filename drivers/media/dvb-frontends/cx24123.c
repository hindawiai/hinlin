<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *   Conexant cx24123/cx24109 - DVB QPSK Satellite demod/tuner driver
 *
 *   Copyright (C) 2005 Steven Toth <stoth@linuxtv.org>
 *
 *   Support क्रम KWorld DVB-S 100 by Vadim Catana <skystar@molकरोva.cc>
 *
 *   Support क्रम CX24123/CX24113-NIM by Patrick Boettcher <pb@linuxtv.org>
 */

#समावेश <linux/slab.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <यंत्र/भाग64.h>

#समावेश <media/dvb_frontend.h>
#समावेश "cx24123.h"

#घोषणा XTAL 10111000

अटल पूर्णांक क्रमce_band;
module_param(क्रमce_band, पूर्णांक, 0644);
MODULE_PARM_DESC(क्रमce_band, "Force a specific band select "\
	"(1-9, default:off).");

अटल पूर्णांक debug;
module_param(debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug, "Activates frontend debugging (default:0)");

#घोषणा info(args...) करो अणु prपूर्णांकk(KERN_INFO "CX24123: " args); पूर्ण जबतक (0)
#घोषणा err(args...)  करो अणु prपूर्णांकk(KERN_ERR  "CX24123: " args); पूर्ण जबतक (0)

#घोषणा dprपूर्णांकk(args...) \
	करो अणु \
		अगर (debug) अणु \
			prपूर्णांकk(KERN_DEBUG "CX24123: %s: ", __func__); \
			prपूर्णांकk(args); \
		पूर्ण \
	पूर्ण जबतक (0)

काष्ठा cx24123_state अणु
	काष्ठा i2c_adapter *i2c;
	स्थिर काष्ठा cx24123_config *config;

	काष्ठा dvb_frontend frontend;

	/* Some PLL specअगरics क्रम tuning */
	u32 VCAarg;
	u32 VGAarg;
	u32 bandselectarg;
	u32 pllarg;
	u32 FILTune;

	काष्ठा i2c_adapter tuner_i2c_adapter;

	u8 demod_rev;

	/* The Demod/Tuner can't easily provide these, we cache them */
	u32 currentfreq;
	u32 currentsymbolrate;
पूर्ण;

/* Various tuner शेषs need to be established क्रम a given symbol rate Sps */
अटल काष्ठा cx24123_AGC_val अणु
	u32 symbolrate_low;
	u32 symbolrate_high;
	u32 VCAprogdata;
	u32 VGAprogdata;
	u32 FILTune;
पूर्ण cx24123_AGC_vals[] =
अणु
	अणु
		.symbolrate_low		= 1000000,
		.symbolrate_high	= 4999999,
		/* the specs recommend other values क्रम VGA offsets,
		   but tests show they are wrong */
		.VGAprogdata		= (1 << 19) | (0x180 << 9) | 0x1e0,
		.VCAprogdata		= (2 << 19) | (0x07 << 9) | 0x07,
		.FILTune		= 0x27f /* 0.41 V */
	पूर्ण,
	अणु
		.symbolrate_low		=  5000000,
		.symbolrate_high	= 14999999,
		.VGAprogdata		= (1 << 19) | (0x180 << 9) | 0x1e0,
		.VCAprogdata		= (2 << 19) | (0x07 << 9) | 0x1f,
		.FILTune		= 0x317 /* 0.90 V */
	पूर्ण,
	अणु
		.symbolrate_low		= 15000000,
		.symbolrate_high	= 45000000,
		.VGAprogdata		= (1 << 19) | (0x100 << 9) | 0x180,
		.VCAprogdata		= (2 << 19) | (0x07 << 9) | 0x3f,
		.FILTune		= 0x145 /* 2.70 V */
	पूर्ण,
पूर्ण;

/*
 * Various tuner शेषs need to be established क्रम a given frequency kHz.
 * fixme: The bounds on the bands करो not match the करोc in real lअगरe.
 * fixme: Some of them have been moved, other might need adjusपंचांगent.
 */
अटल काष्ठा cx24123_bandselect_val अणु
	u32 freq_low;
	u32 freq_high;
	u32 VCOभागider;
	u32 progdata;
पूर्ण cx24123_bandselect_vals[] =
अणु
	/* band 1 */
	अणु
		.freq_low	= 950000,
		.freq_high	= 1074999,
		.VCOभागider	= 4,
		.progdata	= (0 << 19) | (0 << 9) | 0x40,
	पूर्ण,

	/* band 2 */
	अणु
		.freq_low	= 1075000,
		.freq_high	= 1177999,
		.VCOभागider	= 4,
		.progdata	= (0 << 19) | (0 << 9) | 0x80,
	पूर्ण,

	/* band 3 */
	अणु
		.freq_low	= 1178000,
		.freq_high	= 1295999,
		.VCOभागider	= 2,
		.progdata	= (0 << 19) | (1 << 9) | 0x01,
	पूर्ण,

	/* band 4 */
	अणु
		.freq_low	= 1296000,
		.freq_high	= 1431999,
		.VCOभागider	= 2,
		.progdata	= (0 << 19) | (1 << 9) | 0x02,
	पूर्ण,

	/* band 5 */
	अणु
		.freq_low	= 1432000,
		.freq_high	= 1575999,
		.VCOभागider	= 2,
		.progdata	= (0 << 19) | (1 << 9) | 0x04,
	पूर्ण,

	/* band 6 */
	अणु
		.freq_low	= 1576000,
		.freq_high	= 1717999,
		.VCOभागider	= 2,
		.progdata	= (0 << 19) | (1 << 9) | 0x08,
	पूर्ण,

	/* band 7 */
	अणु
		.freq_low	= 1718000,
		.freq_high	= 1855999,
		.VCOभागider	= 2,
		.progdata	= (0 << 19) | (1 << 9) | 0x10,
	पूर्ण,

	/* band 8 */
	अणु
		.freq_low	= 1856000,
		.freq_high	= 2035999,
		.VCOभागider	= 2,
		.progdata	= (0 << 19) | (1 << 9) | 0x20,
	पूर्ण,

	/* band 9 */
	अणु
		.freq_low	= 2036000,
		.freq_high	= 2150000,
		.VCOभागider	= 2,
		.progdata	= (0 << 19) | (1 << 9) | 0x40,
	पूर्ण,
पूर्ण;

अटल काष्ठा अणु
	u8 reg;
	u8 data;
पूर्ण cx24123_regdata[] =
अणु
	अणु0x00, 0x03पूर्ण, /* Reset प्रणाली */
	अणु0x00, 0x00पूर्ण, /* Clear reset */
	अणु0x03, 0x07पूर्ण, /* QPSK, DVB, Auto Acquisition (शेष) */
	अणु0x04, 0x10पूर्ण, /* MPEG */
	अणु0x05, 0x04पूर्ण, /* MPEG */
	अणु0x06, 0x31पूर्ण, /* MPEG (शेष) */
	अणु0x0b, 0x00पूर्ण, /* Freq search start poपूर्णांक (शेष) */
	अणु0x0c, 0x00पूर्ण, /* Demodulator sample gain (शेष) */
	अणु0x0d, 0x7fपूर्ण, /* Force driver to shअगरt until the maximum (+-10 MHz) */
	अणु0x0e, 0x03पूर्ण, /* Default non-inverted, FEC 3/4 (शेष) */
	अणु0x0f, 0xfeपूर्ण, /* FEC search mask (all supported codes) */
	अणु0x10, 0x01पूर्ण, /* Default search inversion, no repeat (शेष) */
	अणु0x16, 0x00पूर्ण, /* Enable पढ़ोing of frequency */
	अणु0x17, 0x01पूर्ण, /* Enable EsNO Ready Counter */
	अणु0x1c, 0x80पूर्ण, /* Enable error counter */
	अणु0x20, 0x00पूर्ण, /* Tuner burst घड़ी rate = 500KHz */
	अणु0x21, 0x15पूर्ण, /* Tuner burst mode, word length = 0x15 */
	अणु0x28, 0x00पूर्ण, /* Enable FILTERV with positive pol., DiSEqC 2.x off */
	अणु0x29, 0x00पूर्ण, /* DiSEqC LNB_DC off */
	अणु0x2a, 0xb0पूर्ण, /* DiSEqC Parameters (शेष) */
	अणु0x2b, 0x73पूर्ण, /* DiSEqC Tone Frequency (शेष) */
	अणु0x2c, 0x00पूर्ण, /* DiSEqC Message (0x2c - 0x31) */
	अणु0x2d, 0x00पूर्ण,
	अणु0x2e, 0x00पूर्ण,
	अणु0x2f, 0x00पूर्ण,
	अणु0x30, 0x00पूर्ण,
	अणु0x31, 0x00पूर्ण,
	अणु0x32, 0x8cपूर्ण, /* DiSEqC Parameters (शेष) */
	अणु0x33, 0x00पूर्ण, /* Interrupts off (0x33 - 0x34) */
	अणु0x34, 0x00पूर्ण,
	अणु0x35, 0x03पूर्ण, /* DiSEqC Tone Amplitude (शेष) */
	अणु0x36, 0x02पूर्ण, /* DiSEqC Parameters (शेष) */
	अणु0x37, 0x3aपूर्ण, /* DiSEqC Parameters (शेष) */
	अणु0x3a, 0x00पूर्ण, /* Enable AGC accumulator (क्रम संकेत strength) */
	अणु0x44, 0x00पूर्ण, /* Constellation (शेष) */
	अणु0x45, 0x00पूर्ण, /* Symbol count (शेष) */
	अणु0x46, 0x0dपूर्ण, /* Symbol rate estimator on (शेष) */
	अणु0x56, 0xc1पूर्ण, /* Error Counter = Viterbi BER */
	अणु0x57, 0xffपूर्ण, /* Error Counter Winकरोw (शेष) */
	अणु0x5c, 0x20पूर्ण, /* Acquisition AFC Expiration winकरोw (शेष is 0x10) */
	अणु0x67, 0x83पूर्ण, /* Non-DCII symbol घड़ी */
पूर्ण;

अटल पूर्णांक cx24123_i2c_ग_लिखोreg(काष्ठा cx24123_state *state,
	u8 i2c_addr, पूर्णांक reg, पूर्णांक data)
अणु
	u8 buf[] = अणु reg, data पूर्ण;
	काष्ठा i2c_msg msg = अणु
		.addr = i2c_addr, .flags = 0, .buf = buf, .len = 2
	पूर्ण;
	पूर्णांक err;

	/* prपूर्णांकk(KERN_DEBUG "wr(%02x): %02x %02x\n", i2c_addr, reg, data); */

	err = i2c_transfer(state->i2c, &msg, 1);
	अगर (err != 1) अणु
		prपूर्णांकk("%s: writereg error(err == %i, reg == 0x%02x, data == 0x%02x)\n",
		       __func__, err, reg, data);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cx24123_i2c_पढ़ोreg(काष्ठा cx24123_state *state, u8 i2c_addr, u8 reg)
अणु
	पूर्णांक ret;
	u8 b = 0;
	काष्ठा i2c_msg msg[] = अणु
		अणु .addr = i2c_addr, .flags = 0, .buf = &reg, .len = 1 पूर्ण,
		अणु .addr = i2c_addr, .flags = I2C_M_RD, .buf = &b, .len = 1 पूर्ण
	पूर्ण;

	ret = i2c_transfer(state->i2c, msg, 2);

	अगर (ret != 2) अणु
		err("%s: reg=0x%x (error=%d)\n", __func__, reg, ret);
		वापस ret;
	पूर्ण

	/* prपूर्णांकk(KERN_DEBUG "rd(%02x): %02x %02x\n", i2c_addr, reg, b); */

	वापस b;
पूर्ण

#घोषणा cx24123_पढ़ोreg(state, reg) \
	cx24123_i2c_पढ़ोreg(state, state->config->demod_address, reg)
#घोषणा cx24123_ग_लिखोreg(state, reg, val) \
	cx24123_i2c_ग_लिखोreg(state, state->config->demod_address, reg, val)

अटल पूर्णांक cx24123_set_inversion(काष्ठा cx24123_state *state,
				 क्रमागत fe_spectral_inversion inversion)
अणु
	u8 nom_reg = cx24123_पढ़ोreg(state, 0x0e);
	u8 स्वतः_reg = cx24123_पढ़ोreg(state, 0x10);

	चयन (inversion) अणु
	हाल INVERSION_OFF:
		dprपूर्णांकk("inversion off\n");
		cx24123_ग_लिखोreg(state, 0x0e, nom_reg & ~0x80);
		cx24123_ग_लिखोreg(state, 0x10, स्वतः_reg | 0x80);
		अवरोध;
	हाल INVERSION_ON:
		dprपूर्णांकk("inversion on\n");
		cx24123_ग_लिखोreg(state, 0x0e, nom_reg | 0x80);
		cx24123_ग_लिखोreg(state, 0x10, स्वतः_reg | 0x80);
		अवरोध;
	हाल INVERSION_AUTO:
		dprपूर्णांकk("inversion auto\n");
		cx24123_ग_लिखोreg(state, 0x10, स्वतः_reg & ~0x80);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cx24123_get_inversion(काष्ठा cx24123_state *state,
				 क्रमागत fe_spectral_inversion *inversion)
अणु
	u8 val;

	val = cx24123_पढ़ोreg(state, 0x1b) >> 7;

	अगर (val == 0) अणु
		dprपूर्णांकk("read inversion off\n");
		*inversion = INVERSION_OFF;
	पूर्ण अन्यथा अणु
		dprपूर्णांकk("read inversion on\n");
		*inversion = INVERSION_ON;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cx24123_set_fec(काष्ठा cx24123_state *state, क्रमागत fe_code_rate fec)
अणु
	u8 nom_reg = cx24123_पढ़ोreg(state, 0x0e) & ~0x07;

	अगर (((पूर्णांक)fec < FEC_NONE) || (fec > FEC_AUTO))
		fec = FEC_AUTO;

	/* Set the soft decision threshold */
	अगर (fec == FEC_1_2)
		cx24123_ग_लिखोreg(state, 0x43,
			cx24123_पढ़ोreg(state, 0x43) | 0x01);
	अन्यथा
		cx24123_ग_लिखोreg(state, 0x43,
			cx24123_पढ़ोreg(state, 0x43) & ~0x01);

	चयन (fec) अणु
	हाल FEC_1_2:
		dprपूर्णांकk("set FEC to 1/2\n");
		cx24123_ग_लिखोreg(state, 0x0e, nom_reg | 0x01);
		cx24123_ग_लिखोreg(state, 0x0f, 0x02);
		अवरोध;
	हाल FEC_2_3:
		dprपूर्णांकk("set FEC to 2/3\n");
		cx24123_ग_लिखोreg(state, 0x0e, nom_reg | 0x02);
		cx24123_ग_लिखोreg(state, 0x0f, 0x04);
		अवरोध;
	हाल FEC_3_4:
		dprपूर्णांकk("set FEC to 3/4\n");
		cx24123_ग_लिखोreg(state, 0x0e, nom_reg | 0x03);
		cx24123_ग_लिखोreg(state, 0x0f, 0x08);
		अवरोध;
	हाल FEC_4_5:
		dprपूर्णांकk("set FEC to 4/5\n");
		cx24123_ग_लिखोreg(state, 0x0e, nom_reg | 0x04);
		cx24123_ग_लिखोreg(state, 0x0f, 0x10);
		अवरोध;
	हाल FEC_5_6:
		dprपूर्णांकk("set FEC to 5/6\n");
		cx24123_ग_लिखोreg(state, 0x0e, nom_reg | 0x05);
		cx24123_ग_लिखोreg(state, 0x0f, 0x20);
		अवरोध;
	हाल FEC_6_7:
		dprपूर्णांकk("set FEC to 6/7\n");
		cx24123_ग_लिखोreg(state, 0x0e, nom_reg | 0x06);
		cx24123_ग_लिखोreg(state, 0x0f, 0x40);
		अवरोध;
	हाल FEC_7_8:
		dprपूर्णांकk("set FEC to 7/8\n");
		cx24123_ग_लिखोreg(state, 0x0e, nom_reg | 0x07);
		cx24123_ग_लिखोreg(state, 0x0f, 0x80);
		अवरोध;
	हाल FEC_AUTO:
		dprपूर्णांकk("set FEC to auto\n");
		cx24123_ग_लिखोreg(state, 0x0f, 0xfe);
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cx24123_get_fec(काष्ठा cx24123_state *state, क्रमागत fe_code_rate *fec)
अणु
	पूर्णांक ret;

	ret = cx24123_पढ़ोreg(state, 0x1b);
	अगर (ret < 0)
		वापस ret;
	ret = ret & 0x07;

	चयन (ret) अणु
	हाल 1:
		*fec = FEC_1_2;
		अवरोध;
	हाल 2:
		*fec = FEC_2_3;
		अवरोध;
	हाल 3:
		*fec = FEC_3_4;
		अवरोध;
	हाल 4:
		*fec = FEC_4_5;
		अवरोध;
	हाल 5:
		*fec = FEC_5_6;
		अवरोध;
	हाल 6:
		*fec = FEC_6_7;
		अवरोध;
	हाल 7:
		*fec = FEC_7_8;
		अवरोध;
	शेष:
		/* this can happen when there's no lock */
		*fec = FEC_NONE;
	पूर्ण

	वापस 0;
पूर्ण

/* Approximation of बंदst पूर्णांकeger of log2(a/b). It actually gives the
   lowest पूर्णांकeger i such that 2^i >= round(a/b) */
अटल u32 cx24123_पूर्णांक_log2(u32 a, u32 b)
अणु
	u32 exp, nearest = 0;
	u32 भाग = a / b;
	अगर (a % b >= b / 2)
		++भाग;
	अगर (भाग < (1UL << 31)) अणु
		क्रम (exp = 1; भाग > exp; nearest++)
			exp += exp;
	पूर्ण
	वापस nearest;
पूर्ण

अटल पूर्णांक cx24123_set_symbolrate(काष्ठा cx24123_state *state, u32 srate)
अणु
	u64 पंचांगp;
	u32 sample_rate, ratio, sample_gain;
	u8 pll_mult;

	/*  check अगर symbol rate is within limits */
	अगर ((srate > state->frontend.ops.info.symbol_rate_max) ||
	    (srate < state->frontend.ops.info.symbol_rate_min))
		वापस -EOPNOTSUPP;

	/* choose the sampling rate high enough क्रम the required operation,
	   जबतक optimizing the घातer consumed by the demodulator */
	अगर (srate < (XTAL*2)/2)
		pll_mult = 2;
	अन्यथा अगर (srate < (XTAL*3)/2)
		pll_mult = 3;
	अन्यथा अगर (srate < (XTAL*4)/2)
		pll_mult = 4;
	अन्यथा अगर (srate < (XTAL*5)/2)
		pll_mult = 5;
	अन्यथा अगर (srate < (XTAL*6)/2)
		pll_mult = 6;
	अन्यथा अगर (srate < (XTAL*7)/2)
		pll_mult = 7;
	अन्यथा अगर (srate < (XTAL*8)/2)
		pll_mult = 8;
	अन्यथा
		pll_mult = 9;


	sample_rate = pll_mult * XTAL;

	/* SYSSymbolRate[21:0] = (srate << 23) / sample_rate */

	पंचांगp = ((u64)srate) << 23;
	करो_भाग(पंचांगp, sample_rate);
	ratio = (u32) पंचांगp;

	cx24123_ग_लिखोreg(state, 0x01, pll_mult * 6);

	cx24123_ग_लिखोreg(state, 0x08, (ratio >> 16) & 0x3f);
	cx24123_ग_लिखोreg(state, 0x09, (ratio >> 8) & 0xff);
	cx24123_ग_लिखोreg(state, 0x0a, ratio & 0xff);

	/* also set the demodulator sample gain */
	sample_gain = cx24123_पूर्णांक_log2(sample_rate, srate);
	पंचांगp = cx24123_पढ़ोreg(state, 0x0c) & ~0xe0;
	cx24123_ग_लिखोreg(state, 0x0c, पंचांगp | sample_gain << 5);

	dprपूर्णांकk("srate=%d, ratio=0x%08x, sample_rate=%i sample_gain=%d\n",
		srate, ratio, sample_rate, sample_gain);

	वापस 0;
पूर्ण

/*
 * Based on the required frequency and symbolrate, the tuner AGC has
 * to be configured and the correct band selected.
 * Calculate those values.
 */
अटल पूर्णांक cx24123_pll_calculate(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dtv_frontend_properties *p = &fe->dtv_property_cache;
	काष्ठा cx24123_state *state = fe->demodulator_priv;
	u32 nभाग = 0, aभाग = 0, vco_भाग = 0;
	पूर्णांक i = 0;
	पूर्णांक pump = 2;
	पूर्णांक band = 0;
	पूर्णांक num_bands = ARRAY_SIZE(cx24123_bandselect_vals);
	काष्ठा cx24123_bandselect_val *bsv = शून्य;
	काष्ठा cx24123_AGC_val *agcv = शून्य;

	/* Defaults क्रम low freq, low rate */
	state->VCAarg = cx24123_AGC_vals[0].VCAprogdata;
	state->VGAarg = cx24123_AGC_vals[0].VGAprogdata;
	state->bandselectarg = cx24123_bandselect_vals[0].progdata;
	vco_भाग = cx24123_bandselect_vals[0].VCOभागider;

	/* For the given symbol rate, determine the VCA, VGA and
	 * FILTUNE programming bits */
	क्रम (i = 0; i < ARRAY_SIZE(cx24123_AGC_vals); i++) अणु
		agcv = &cx24123_AGC_vals[i];
		अगर ((agcv->symbolrate_low <= p->symbol_rate) &&
		    (agcv->symbolrate_high >= p->symbol_rate)) अणु
			state->VCAarg = agcv->VCAprogdata;
			state->VGAarg = agcv->VGAprogdata;
			state->FILTune = agcv->FILTune;
		पूर्ण
	पूर्ण

	/* determine the band to use */
	अगर (क्रमce_band < 1 || क्रमce_band > num_bands) अणु
		क्रम (i = 0; i < num_bands; i++) अणु
			bsv = &cx24123_bandselect_vals[i];
			अगर ((bsv->freq_low <= p->frequency) &&
				(bsv->freq_high >= p->frequency))
				band = i;
		पूर्ण
	पूर्ण अन्यथा
		band = क्रमce_band - 1;

	state->bandselectarg = cx24123_bandselect_vals[band].progdata;
	vco_भाग = cx24123_bandselect_vals[band].VCOभागider;

	/* determine the अक्षरge pump current */
	अगर (p->frequency < (cx24123_bandselect_vals[band].freq_low +
		cx24123_bandselect_vals[band].freq_high) / 2)
		pump = 0x01;
	अन्यथा
		pump = 0x02;

	/* Determine the N/A भागiders क्रम the requested lband freq (in kHz). */
	/* Note: the reference भागider R=10, frequency is in KHz,
	 * XTAL is in Hz */
	nभाग = (((p->frequency * vco_भाग * 10) /
		(2 * XTAL / 1000)) / 32) & 0x1ff;
	aभाग = (((p->frequency * vco_भाग * 10) /
		(2 * XTAL / 1000)) % 32) & 0x1f;

	अगर (aभाग == 0 && nभाग > 0)
		nभाग--;

	/* control bits 11, refभाग 11, अक्षरge pump polarity 1,
	 * अक्षरge pump current, nभाग, aभाग */
	state->pllarg = (3 << 19) | (3 << 17) | (1 << 16) |
		(pump << 14) | (nभाग << 5) | aभाग;

	वापस 0;
पूर्ण

/*
 * Tuner data is 21 bits दीर्घ, must be left-aligned in data.
 * Tuner cx24109 is written through a dedicated 3wire पूर्णांकerface
 * on the demod chip.
 */
अटल पूर्णांक cx24123_pll_ग_लिखोreg(काष्ठा dvb_frontend *fe, u32 data)
अणु
	काष्ठा cx24123_state *state = fe->demodulator_priv;
	अचिन्हित दीर्घ समयout;

	dprपूर्णांकk("pll writereg called, data=0x%08x\n", data);

	/* align the 21 bytes पूर्णांकo to bit23 boundary */
	data = data << 3;

	/* Reset the demod pll word length to 0x15 bits */
	cx24123_ग_लिखोreg(state, 0x21, 0x15);

	/* ग_लिखो the msb 8 bits, रुको क्रम the send to be completed */
	समयout = jअगरfies + msecs_to_jअगरfies(40);
	cx24123_ग_लिखोreg(state, 0x22, (data >> 16) & 0xff);
	जबतक ((cx24123_पढ़ोreg(state, 0x20) & 0x40) == 0) अणु
		अगर (समय_after(jअगरfies, समयout)) अणु
			err("%s:  demodulator is not responding, "\
				"possibly hung, aborting.\n", __func__);
			वापस -EREMOTEIO;
		पूर्ण
		msleep(10);
	पूर्ण

	/* send another 8 bytes, रुको क्रम the send to be completed */
	समयout = jअगरfies + msecs_to_jअगरfies(40);
	cx24123_ग_लिखोreg(state, 0x22, (data >> 8) & 0xff);
	जबतक ((cx24123_पढ़ोreg(state, 0x20) & 0x40) == 0) अणु
		अगर (समय_after(jअगरfies, समयout)) अणु
			err("%s:  demodulator is not responding, "\
				"possibly hung, aborting.\n", __func__);
			वापस -EREMOTEIO;
		पूर्ण
		msleep(10);
	पूर्ण

	/* send the lower 5 bits of this byte, padded with 3 LBB,
	 * रुको क्रम the send to be completed */
	समयout = jअगरfies + msecs_to_jअगरfies(40);
	cx24123_ग_लिखोreg(state, 0x22, (data) & 0xff);
	जबतक ((cx24123_पढ़ोreg(state, 0x20) & 0x80)) अणु
		अगर (समय_after(jअगरfies, समयout)) अणु
			err("%s:  demodulator is not responding," \
				"possibly hung, aborting.\n", __func__);
			वापस -EREMOTEIO;
		पूर्ण
		msleep(10);
	पूर्ण

	/* Trigger the demod to configure the tuner */
	cx24123_ग_लिखोreg(state, 0x20, cx24123_पढ़ोreg(state, 0x20) | 2);
	cx24123_ग_लिखोreg(state, 0x20, cx24123_पढ़ोreg(state, 0x20) & 0xfd);

	वापस 0;
पूर्ण

अटल पूर्णांक cx24123_pll_tune(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dtv_frontend_properties *p = &fe->dtv_property_cache;
	काष्ठा cx24123_state *state = fe->demodulator_priv;
	u8 val;

	dprपूर्णांकk("frequency=%i\n", p->frequency);

	अगर (cx24123_pll_calculate(fe) != 0) अणु
		err("%s: cx24123_pll_calculate failed\n", __func__);
		वापस -EINVAL;
	पूर्ण

	/* Write the new VCO/VGA */
	cx24123_pll_ग_लिखोreg(fe, state->VCAarg);
	cx24123_pll_ग_लिखोreg(fe, state->VGAarg);

	/* Write the new bandselect and pll args */
	cx24123_pll_ग_लिखोreg(fe, state->bandselectarg);
	cx24123_pll_ग_लिखोreg(fe, state->pllarg);

	/* set the FILTUNE voltage */
	val = cx24123_पढ़ोreg(state, 0x28) & ~0x3;
	cx24123_ग_लिखोreg(state, 0x27, state->FILTune >> 2);
	cx24123_ग_लिखोreg(state, 0x28, val | (state->FILTune & 0x3));

	dprपूर्णांकk("pll tune VCA=%d, band=%d, pll=%d\n", state->VCAarg,
			state->bandselectarg, state->pllarg);

	वापस 0;
पूर्ण


/*
 * 0x23:
 *    [7:7] = BTI enabled
 *    [6:6] = I2C repeater enabled
 *    [5:5] = I2C repeater start
 *    [0:0] = BTI start
 */

/* mode == 1 -> i2c-repeater, 0 -> bti */
अटल पूर्णांक cx24123_repeater_mode(काष्ठा cx24123_state *state, u8 mode, u8 start)
अणु
	u8 r = cx24123_पढ़ोreg(state, 0x23) & 0x1e;
	अगर (mode)
		r |= (1 << 6) | (start << 5);
	अन्यथा
		r |= (1 << 7) | (start);
	वापस cx24123_ग_लिखोreg(state, 0x23, r);
पूर्ण

अटल पूर्णांक cx24123_initfe(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा cx24123_state *state = fe->demodulator_priv;
	पूर्णांक i;

	dprपूर्णांकk("init frontend\n");

	/* Configure the demod to a good set of शेषs */
	क्रम (i = 0; i < ARRAY_SIZE(cx24123_regdata); i++)
		cx24123_ग_लिखोreg(state, cx24123_regdata[i].reg,
			cx24123_regdata[i].data);

	/* Set the LNB polarity */
	अगर (state->config->lnb_polarity)
		cx24123_ग_लिखोreg(state, 0x32,
			cx24123_पढ़ोreg(state, 0x32) | 0x02);

	अगर (state->config->करोnt_use_pll)
		cx24123_repeater_mode(state, 1, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक cx24123_set_voltage(काष्ठा dvb_frontend *fe,
			       क्रमागत fe_sec_voltage voltage)
अणु
	काष्ठा cx24123_state *state = fe->demodulator_priv;
	u8 val;

	val = cx24123_पढ़ोreg(state, 0x29) & ~0x40;

	चयन (voltage) अणु
	हाल SEC_VOLTAGE_13:
		dprपूर्णांकk("setting voltage 13V\n");
		वापस cx24123_ग_लिखोreg(state, 0x29, val & 0x7f);
	हाल SEC_VOLTAGE_18:
		dprपूर्णांकk("setting voltage 18V\n");
		वापस cx24123_ग_लिखोreg(state, 0x29, val | 0x80);
	हाल SEC_VOLTAGE_OFF:
		/* alपढ़ोy handled in cx88-dvb */
		वापस 0;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/* रुको क्रम diseqc queue to become पढ़ोy (or समयout) */
अटल व्योम cx24123_रुको_क्रम_diseqc(काष्ठा cx24123_state *state)
अणु
	अचिन्हित दीर्घ समयout = jअगरfies + msecs_to_jअगरfies(200);
	जबतक (!(cx24123_पढ़ोreg(state, 0x29) & 0x40)) अणु
		अगर (समय_after(jअगरfies, समयout)) अणु
			err("%s: diseqc queue not ready, " \
				"command may be lost.\n", __func__);
			अवरोध;
		पूर्ण
		msleep(10);
	पूर्ण
पूर्ण

अटल पूर्णांक cx24123_send_diseqc_msg(काष्ठा dvb_frontend *fe,
	काष्ठा dvb_diseqc_master_cmd *cmd)
अणु
	काष्ठा cx24123_state *state = fe->demodulator_priv;
	पूर्णांक i, val, tone;

	dprपूर्णांकk("\n");

	/* stop continuous tone अगर enabled */
	tone = cx24123_पढ़ोreg(state, 0x29);
	अगर (tone & 0x10)
		cx24123_ग_लिखोreg(state, 0x29, tone & ~0x50);

	/* रुको क्रम diseqc queue पढ़ोy */
	cx24123_रुको_क्रम_diseqc(state);

	/* select tone mode */
	cx24123_ग_लिखोreg(state, 0x2a, cx24123_पढ़ोreg(state, 0x2a) & 0xfb);

	क्रम (i = 0; i < cmd->msg_len; i++)
		cx24123_ग_लिखोreg(state, 0x2C + i, cmd->msg[i]);

	val = cx24123_पढ़ोreg(state, 0x29);
	cx24123_ग_लिखोreg(state, 0x29, ((val & 0x90) | 0x40) |
		((cmd->msg_len-3) & 3));

	/* रुको क्रम diseqc message to finish sending */
	cx24123_रुको_क्रम_diseqc(state);

	/* restart continuous tone अगर enabled */
	अगर (tone & 0x10)
		cx24123_ग_लिखोreg(state, 0x29, tone & ~0x40);

	वापस 0;
पूर्ण

अटल पूर्णांक cx24123_diseqc_send_burst(काष्ठा dvb_frontend *fe,
				     क्रमागत fe_sec_mini_cmd burst)
अणु
	काष्ठा cx24123_state *state = fe->demodulator_priv;
	पूर्णांक val, tone;

	dprपूर्णांकk("\n");

	/* stop continuous tone अगर enabled */
	tone = cx24123_पढ़ोreg(state, 0x29);
	अगर (tone & 0x10)
		cx24123_ग_लिखोreg(state, 0x29, tone & ~0x50);

	/* रुको क्रम diseqc queue पढ़ोy */
	cx24123_रुको_क्रम_diseqc(state);

	/* select tone mode */
	cx24123_ग_लिखोreg(state, 0x2a, cx24123_पढ़ोreg(state, 0x2a) | 0x4);
	msleep(30);
	val = cx24123_पढ़ोreg(state, 0x29);
	अगर (burst == SEC_MINI_A)
		cx24123_ग_लिखोreg(state, 0x29, ((val & 0x90) | 0x40 | 0x00));
	अन्यथा अगर (burst == SEC_MINI_B)
		cx24123_ग_लिखोreg(state, 0x29, ((val & 0x90) | 0x40 | 0x08));
	अन्यथा
		वापस -EINVAL;

	cx24123_रुको_क्रम_diseqc(state);
	cx24123_ग_लिखोreg(state, 0x2a, cx24123_पढ़ोreg(state, 0x2a) & 0xfb);

	/* restart continuous tone अगर enabled */
	अगर (tone & 0x10)
		cx24123_ग_लिखोreg(state, 0x29, tone & ~0x40);

	वापस 0;
पूर्ण

अटल पूर्णांक cx24123_पढ़ो_status(काष्ठा dvb_frontend *fe, क्रमागत fe_status *status)
अणु
	काष्ठा cx24123_state *state = fe->demodulator_priv;
	पूर्णांक sync = cx24123_पढ़ोreg(state, 0x14);

	*status = 0;
	अगर (state->config->करोnt_use_pll) अणु
		u32 tun_status = 0;
		अगर (fe->ops.tuner_ops.get_status)
			fe->ops.tuner_ops.get_status(fe, &tun_status);
		अगर (tun_status & TUNER_STATUS_LOCKED)
			*status |= FE_HAS_SIGNAL;
	पूर्ण अन्यथा अणु
		पूर्णांक lock = cx24123_पढ़ोreg(state, 0x20);
		अगर (lock & 0x01)
			*status |= FE_HAS_SIGNAL;
	पूर्ण

	अगर (sync & 0x02)
		*status |= FE_HAS_CARRIER;	/* Phase locked */
	अगर (sync & 0x04)
		*status |= FE_HAS_VITERBI;

	/* Reed-Solomon Status */
	अगर (sync & 0x08)
		*status |= FE_HAS_SYNC;
	अगर (sync & 0x80)
		*status |= FE_HAS_LOCK;		/*Full Sync */

	वापस 0;
पूर्ण

/*
 * Configured to वापस the measurement of errors in blocks,
 * because no UCBLOCKS value is available, so this value द्विगुनs up
 * to satisfy both measurements.
 */
अटल पूर्णांक cx24123_पढ़ो_ber(काष्ठा dvb_frontend *fe, u32 *ber)
अणु
	काष्ठा cx24123_state *state = fe->demodulator_priv;

	/* The true bit error rate is this value भागided by
	   the winकरोw size (set as 256 * 255) */
	*ber = ((cx24123_पढ़ोreg(state, 0x1c) & 0x3f) << 16) |
		(cx24123_पढ़ोreg(state, 0x1d) << 8 |
		 cx24123_पढ़ोreg(state, 0x1e));

	dprपूर्णांकk("BER = %d\n", *ber);

	वापस 0;
पूर्ण

अटल पूर्णांक cx24123_पढ़ो_संकेत_strength(काष्ठा dvb_frontend *fe,
	u16 *संकेत_strength)
अणु
	काष्ठा cx24123_state *state = fe->demodulator_priv;

	/* larger = better */
	*संकेत_strength = cx24123_पढ़ोreg(state, 0x3b) << 8;

	dprपूर्णांकk("Signal strength = %d\n", *संकेत_strength);

	वापस 0;
पूर्ण

अटल पूर्णांक cx24123_पढ़ो_snr(काष्ठा dvb_frontend *fe, u16 *snr)
अणु
	काष्ठा cx24123_state *state = fe->demodulator_priv;

	/* Inverted raw Es/N0 count, totally bogus but better than the
	   BER threshold. */
	*snr = 65535 - (((u16)cx24123_पढ़ोreg(state, 0x18) << 8) |
			 (u16)cx24123_पढ़ोreg(state, 0x19));

	dprपूर्णांकk("read S/N index = %d\n", *snr);

	वापस 0;
पूर्ण

अटल पूर्णांक cx24123_set_frontend(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा cx24123_state *state = fe->demodulator_priv;
	काष्ठा dtv_frontend_properties *p = &fe->dtv_property_cache;

	dprपूर्णांकk("\n");

	अगर (state->config->set_ts_params)
		state->config->set_ts_params(fe, 0);

	state->currentfreq = p->frequency;
	state->currentsymbolrate = p->symbol_rate;

	cx24123_set_inversion(state, p->inversion);
	cx24123_set_fec(state, p->fec_inner);
	cx24123_set_symbolrate(state, p->symbol_rate);

	अगर (!state->config->करोnt_use_pll)
		cx24123_pll_tune(fe);
	अन्यथा अगर (fe->ops.tuner_ops.set_params)
		fe->ops.tuner_ops.set_params(fe);
	अन्यथा
		err("it seems I don't have a tuner...");

	/* Enable स्वतःmatic acquisition and reset cycle */
	cx24123_ग_लिखोreg(state, 0x03, (cx24123_पढ़ोreg(state, 0x03) | 0x07));
	cx24123_ग_लिखोreg(state, 0x00, 0x10);
	cx24123_ग_लिखोreg(state, 0x00, 0);

	अगर (state->config->agc_callback)
		state->config->agc_callback(fe);

	वापस 0;
पूर्ण

अटल पूर्णांक cx24123_get_frontend(काष्ठा dvb_frontend *fe,
				काष्ठा dtv_frontend_properties *p)
अणु
	काष्ठा cx24123_state *state = fe->demodulator_priv;

	dprपूर्णांकk("\n");

	अगर (cx24123_get_inversion(state, &p->inversion) != 0) अणु
		err("%s: Failed to get inversion status\n", __func__);
		वापस -EREMOTEIO;
	पूर्ण
	अगर (cx24123_get_fec(state, &p->fec_inner) != 0) अणु
		err("%s: Failed to get fec status\n", __func__);
		वापस -EREMOTEIO;
	पूर्ण
	p->frequency = state->currentfreq;
	p->symbol_rate = state->currentsymbolrate;

	वापस 0;
पूर्ण

अटल पूर्णांक cx24123_set_tone(काष्ठा dvb_frontend *fe, क्रमागत fe_sec_tone_mode tone)
अणु
	काष्ठा cx24123_state *state = fe->demodulator_priv;
	u8 val;

	/* रुको क्रम diseqc queue पढ़ोy */
	cx24123_रुको_क्रम_diseqc(state);

	val = cx24123_पढ़ोreg(state, 0x29) & ~0x40;

	चयन (tone) अणु
	हाल SEC_TONE_ON:
		dprपूर्णांकk("setting tone on\n");
		वापस cx24123_ग_लिखोreg(state, 0x29, val | 0x10);
	हाल SEC_TONE_OFF:
		dprपूर्णांकk("setting tone off\n");
		वापस cx24123_ग_लिखोreg(state, 0x29, val & 0xef);
	शेष:
		err("CASE reached default with tone=%d\n", tone);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cx24123_tune(काष्ठा dvb_frontend *fe,
			bool re_tune,
			अचिन्हित पूर्णांक mode_flags,
			अचिन्हित पूर्णांक *delay,
			क्रमागत fe_status *status)
अणु
	पूर्णांक retval = 0;

	अगर (re_tune)
		retval = cx24123_set_frontend(fe);

	अगर (!(mode_flags & FE_TUNE_MODE_ONESHOT))
		cx24123_पढ़ो_status(fe, status);
	*delay = HZ/10;

	वापस retval;
पूर्ण

अटल क्रमागत dvbfe_algo cx24123_get_algo(काष्ठा dvb_frontend *fe)
अणु
	वापस DVBFE_ALGO_HW;
पूर्ण

अटल व्योम cx24123_release(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा cx24123_state *state = fe->demodulator_priv;
	dprपूर्णांकk("\n");
	i2c_del_adapter(&state->tuner_i2c_adapter);
	kमुक्त(state);
पूर्ण

अटल पूर्णांक cx24123_tuner_i2c_tuner_xfer(काष्ठा i2c_adapter *i2c_adap,
	काष्ठा i2c_msg msg[], पूर्णांक num)
अणु
	काष्ठा cx24123_state *state = i2c_get_adapdata(i2c_adap);
	/* this repeater बंदs after the first stop */
	cx24123_repeater_mode(state, 1, 1);
	वापस i2c_transfer(state->i2c, msg, num);
पूर्ण

अटल u32 cx24123_tuner_i2c_func(काष्ठा i2c_adapter *adapter)
अणु
	वापस I2C_FUNC_I2C;
पूर्ण

अटल स्थिर काष्ठा i2c_algorithm cx24123_tuner_i2c_algo = अणु
	.master_xfer   = cx24123_tuner_i2c_tuner_xfer,
	.functionality = cx24123_tuner_i2c_func,
पूर्ण;

काष्ठा i2c_adapter *
	cx24123_get_tuner_i2c_adapter(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा cx24123_state *state = fe->demodulator_priv;
	वापस &state->tuner_i2c_adapter;
पूर्ण
EXPORT_SYMBOL(cx24123_get_tuner_i2c_adapter);

अटल स्थिर काष्ठा dvb_frontend_ops cx24123_ops;

काष्ठा dvb_frontend *cx24123_attach(स्थिर काष्ठा cx24123_config *config,
				    काष्ठा i2c_adapter *i2c)
अणु
	/* allocate memory क्रम the पूर्णांकernal state */
	काष्ठा cx24123_state *state =
		kzalloc(माप(काष्ठा cx24123_state), GFP_KERNEL);

	dprपूर्णांकk("\n");
	अगर (state == शून्य) अणु
		err("Unable to kzalloc\n");
		जाओ error;
	पूर्ण

	/* setup the state */
	state->config = config;
	state->i2c = i2c;

	/* check अगर the demod is there */
	state->demod_rev = cx24123_पढ़ोreg(state, 0x00);
	चयन (state->demod_rev) अणु
	हाल 0xe1:
		info("detected CX24123C\n");
		अवरोध;
	हाल 0xd1:
		info("detected CX24123\n");
		अवरोध;
	शेष:
		err("wrong demod revision: %x\n", state->demod_rev);
		जाओ error;
	पूर्ण

	/* create dvb_frontend */
	स_नकल(&state->frontend.ops, &cx24123_ops,
		माप(काष्ठा dvb_frontend_ops));
	state->frontend.demodulator_priv = state;

	/* create tuner i2c adapter */
	अगर (config->करोnt_use_pll)
		cx24123_repeater_mode(state, 1, 0);

	strscpy(state->tuner_i2c_adapter.name, "CX24123 tuner I2C bus",
		माप(state->tuner_i2c_adapter.name));
	state->tuner_i2c_adapter.algo      = &cx24123_tuner_i2c_algo;
	state->tuner_i2c_adapter.algo_data = शून्य;
	state->tuner_i2c_adapter.dev.parent = i2c->dev.parent;
	i2c_set_adapdata(&state->tuner_i2c_adapter, state);
	अगर (i2c_add_adapter(&state->tuner_i2c_adapter) < 0) अणु
		err("tuner i2c bus could not be initialized\n");
		जाओ error;
	पूर्ण

	वापस &state->frontend;

error:
	kमुक्त(state);

	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(cx24123_attach);

अटल स्थिर काष्ठा dvb_frontend_ops cx24123_ops = अणु
	.delsys = अणु SYS_DVBS पूर्ण,
	.info = अणु
		.name = "Conexant CX24123/CX24109",
		.frequency_min_hz =  950 * MHz,
		.frequency_max_hz = 2150 * MHz,
		.frequency_stepsize_hz = 1011 * kHz,
		.frequency_tolerance_hz = 5 * MHz,
		.symbol_rate_min = 1000000,
		.symbol_rate_max = 45000000,
		.caps = FE_CAN_INVERSION_AUTO |
			FE_CAN_FEC_1_2 | FE_CAN_FEC_2_3 | FE_CAN_FEC_3_4 |
			FE_CAN_FEC_4_5 | FE_CAN_FEC_5_6 | FE_CAN_FEC_6_7 |
			FE_CAN_FEC_7_8 | FE_CAN_FEC_AUTO |
			FE_CAN_QPSK | FE_CAN_RECOVER
	पूर्ण,

	.release = cx24123_release,

	.init = cx24123_initfe,
	.set_frontend = cx24123_set_frontend,
	.get_frontend = cx24123_get_frontend,
	.पढ़ो_status = cx24123_पढ़ो_status,
	.पढ़ो_ber = cx24123_पढ़ो_ber,
	.पढ़ो_संकेत_strength = cx24123_पढ़ो_संकेत_strength,
	.पढ़ो_snr = cx24123_पढ़ो_snr,
	.diseqc_send_master_cmd = cx24123_send_diseqc_msg,
	.diseqc_send_burst = cx24123_diseqc_send_burst,
	.set_tone = cx24123_set_tone,
	.set_voltage = cx24123_set_voltage,
	.tune = cx24123_tune,
	.get_frontend_algo = cx24123_get_algo,
पूर्ण;

MODULE_DESCRIPTION("DVB Frontend module for Conexant " \
	"CX24123/CX24109/CX24113 hardware");
MODULE_AUTHOR("Steven Toth");
MODULE_LICENSE("GPL");

