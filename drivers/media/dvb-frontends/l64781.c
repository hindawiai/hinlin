<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
    driver क्रम LSI L64781 COFDM demodulator

    Copyright (C) 2001 Holger Waechtler क्रम Convergence Integrated Media GmbH
		       Marko Kohtala <marko.kohtala@luukku.com>


*/

#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/माला.स>
#समावेश <linux/slab.h>
#समावेश <media/dvb_frontend.h>
#समावेश "l64781.h"


काष्ठा l64781_state अणु
	काष्ठा i2c_adapter* i2c;
	स्थिर काष्ठा l64781_config* config;
	काष्ठा dvb_frontend frontend;

	/* निजी demodulator data */
	अचिन्हित पूर्णांक first:1;
पूर्ण;

#घोषणा dprपूर्णांकk(args...) \
	करो अणु \
		अगर (debug) prपूर्णांकk(KERN_DEBUG "l64781: " args); \
	पूर्ण जबतक (0)

अटल पूर्णांक debug;

module_param(debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug, "Turn on/off frontend debugging (default:off).");


अटल पूर्णांक l64781_ग_लिखोreg (काष्ठा l64781_state* state, u8 reg, u8 data)
अणु
	पूर्णांक ret;
	u8 buf [] = अणु reg, data पूर्ण;
	काष्ठा i2c_msg msg = अणु .addr = state->config->demod_address, .flags = 0, .buf = buf, .len = 2 पूर्ण;

	अगर ((ret = i2c_transfer(state->i2c, &msg, 1)) != 1)
		dprपूर्णांकk ("%s: write_reg error (reg == %02x) = %02x!\n",
			 __func__, reg, ret);

	वापस (ret != 1) ? -1 : 0;
पूर्ण

अटल पूर्णांक l64781_पढ़ोreg (काष्ठा l64781_state* state, u8 reg)
अणु
	पूर्णांक ret;
	u8 b0 [] = अणु reg पूर्ण;
	u8 b1 [] = अणु 0 पूर्ण;
	काष्ठा i2c_msg msg [] = अणु अणु .addr = state->config->demod_address, .flags = 0, .buf = b0, .len = 1 पूर्ण,
			   अणु .addr = state->config->demod_address, .flags = I2C_M_RD, .buf = b1, .len = 1 पूर्ण पूर्ण;

	ret = i2c_transfer(state->i2c, msg, 2);

	अगर (ret != 2) वापस ret;

	वापस b1[0];
पूर्ण

अटल व्योम apply_tps (काष्ठा l64781_state* state)
अणु
	l64781_ग_लिखोreg (state, 0x2a, 0x00);
	l64781_ग_लिखोreg (state, 0x2a, 0x01);

	/* This here is a little bit questionable because it enables
	   the स्वतःmatic update of TPS रेजिस्टरs. I think we'd need to
	   handle the IRQ from FE to update some other रेजिस्टरs as
	   well, or at least implement some magic to tuning to correct
	   to the TPS received from transmission. */
	l64781_ग_लिखोreg (state, 0x2a, 0x02);
पूर्ण


अटल व्योम reset_afc (काष्ठा l64781_state* state)
अणु
	/* Set AFC stall क्रम the AFC_INIT_FRQ setting, TIM_STALL क्रम
	   timing offset */
	l64781_ग_लिखोreg (state, 0x07, 0x9e); /* stall AFC */
	l64781_ग_लिखोreg (state, 0x08, 0);    /* AFC INIT FREQ */
	l64781_ग_लिखोreg (state, 0x09, 0);
	l64781_ग_लिखोreg (state, 0x0a, 0);
	l64781_ग_लिखोreg (state, 0x07, 0x8e);
	l64781_ग_लिखोreg (state, 0x0e, 0);    /* AGC gain to zero in beginning */
	l64781_ग_लिखोreg (state, 0x11, 0x80); /* stall TIM */
	l64781_ग_लिखोreg (state, 0x10, 0);    /* TIM_OFFSET_LSB */
	l64781_ग_लिखोreg (state, 0x12, 0);
	l64781_ग_लिखोreg (state, 0x13, 0);
	l64781_ग_लिखोreg (state, 0x11, 0x00);
पूर्ण

अटल पूर्णांक reset_and_configure (काष्ठा l64781_state* state)
अणु
	u8 buf [] = अणु 0x06 पूर्ण;
	काष्ठा i2c_msg msg = अणु .addr = 0x00, .flags = 0, .buf = buf, .len = 1 पूर्ण;
	// NOTE: this is correct in writing to address 0x00

	वापस (i2c_transfer(state->i2c, &msg, 1) == 1) ? 0 : -ENODEV;
पूर्ण

अटल पूर्णांक apply_frontend_param(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dtv_frontend_properties *p = &fe->dtv_property_cache;
	काष्ठा l64781_state* state = fe->demodulator_priv;
	/* The coderates क्रम FEC_NONE, FEC_4_5 and FEC_FEC_6_7 are arbitrary */
	अटल स्थिर u8 fec_tab[] = अणु 7, 0, 1, 2, 9, 3, 10, 4 पूर्ण;
	/* QPSK, QAM_16, QAM_64 */
	अटल स्थिर u8 qam_tab [] = अणु 2, 4, 0, 6 पूर्ण;
	अटल स्थिर u8 guard_tab [] = अणु 1, 2, 4, 8 पूर्ण;
	/* The Grundig 29504-401.04 Tuner comes with 18.432MHz crystal. */
	अटल स्थिर u32 ppm = 8000;
	u32 ddfs_offset_fixed;
/*	u32 ddfs_offset_variable = 0x6000-((1000000UL+ppm)/ */
/*			bw_tab[p->bandWidth]<<10)/15625; */
	u32 init_freq;
	u32 spi_bias;
	u8 val0x04;
	u8 val0x05;
	u8 val0x06;
	पूर्णांक bw;

	चयन (p->bandwidth_hz) अणु
	हाल 8000000:
		bw = 8;
		अवरोध;
	हाल 7000000:
		bw = 7;
		अवरोध;
	हाल 6000000:
		bw = 6;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (fe->ops.tuner_ops.set_params) अणु
		fe->ops.tuner_ops.set_params(fe);
		अगर (fe->ops.i2c_gate_ctrl) fe->ops.i2c_gate_ctrl(fe, 0);
	पूर्ण

	अगर (p->inversion != INVERSION_ON &&
	    p->inversion != INVERSION_OFF)
		वापस -EINVAL;

	अगर (p->code_rate_HP != FEC_1_2 && p->code_rate_HP != FEC_2_3 &&
	    p->code_rate_HP != FEC_3_4 && p->code_rate_HP != FEC_5_6 &&
	    p->code_rate_HP != FEC_7_8)
		वापस -EINVAL;

	अगर (p->hierarchy != HIERARCHY_NONE &&
	    (p->code_rate_LP != FEC_1_2 && p->code_rate_LP != FEC_2_3 &&
	     p->code_rate_LP != FEC_3_4 && p->code_rate_LP != FEC_5_6 &&
	     p->code_rate_LP != FEC_7_8))
		वापस -EINVAL;

	अगर (p->modulation != QPSK && p->modulation != QAM_16 &&
	    p->modulation != QAM_64)
		वापस -EINVAL;

	अगर (p->transmission_mode != TRANSMISSION_MODE_2K &&
	    p->transmission_mode != TRANSMISSION_MODE_8K)
		वापस -EINVAL;

	अगर ((पूर्णांक)p->guard_पूर्णांकerval < GUARD_INTERVAL_1_32 ||
	    p->guard_पूर्णांकerval > GUARD_INTERVAL_1_4)
		वापस -EINVAL;

	अगर ((पूर्णांक)p->hierarchy < HIERARCHY_NONE ||
	    p->hierarchy > HIERARCHY_4)
		वापस -EINVAL;

	ddfs_offset_fixed = 0x4000-(ppm<<16)/bw/1000000;

	/* This works up to 20000 ppm, it overflows अगर too large ppm! */
	init_freq = (((8UL<<25) + (8UL<<19) / 25*ppm / (15625/25)) /
			bw & 0xFFFFFF);

	/* SPI bias calculation is slightly modअगरied to fit in 32bit */
	/* will work क्रम high ppm only... */
	spi_bias = 378 * (1 << 10);
	spi_bias *= 16;
	spi_bias *= bw;
	spi_bias *= qam_tab[p->modulation];
	spi_bias /= p->code_rate_HP + 1;
	spi_bias /= (guard_tab[p->guard_पूर्णांकerval] + 32);
	spi_bias *= 1000;
	spi_bias /= 1000 + ppm/1000;
	spi_bias *= p->code_rate_HP;

	val0x04 = (p->transmission_mode << 2) | p->guard_पूर्णांकerval;
	val0x05 = fec_tab[p->code_rate_HP];

	अगर (p->hierarchy != HIERARCHY_NONE)
		val0x05 |= (p->code_rate_LP - FEC_1_2) << 3;

	val0x06 = (p->hierarchy << 2) | p->modulation;

	l64781_ग_लिखोreg (state, 0x04, val0x04);
	l64781_ग_लिखोreg (state, 0x05, val0x05);
	l64781_ग_लिखोreg (state, 0x06, val0x06);

	reset_afc (state);

	/* Technical manual section 2.6.1, TIM_IIR_GAIN optimal values */
	l64781_ग_लिखोreg (state, 0x15,
			 p->transmission_mode == TRANSMISSION_MODE_2K ? 1 : 3);
	l64781_ग_लिखोreg (state, 0x16, init_freq & 0xff);
	l64781_ग_लिखोreg (state, 0x17, (init_freq >> 8) & 0xff);
	l64781_ग_लिखोreg (state, 0x18, (init_freq >> 16) & 0xff);

	l64781_ग_लिखोreg (state, 0x1b, spi_bias & 0xff);
	l64781_ग_लिखोreg (state, 0x1c, (spi_bias >> 8) & 0xff);
	l64781_ग_लिखोreg (state, 0x1d, ((spi_bias >> 16) & 0x7f) |
		(p->inversion == INVERSION_ON ? 0x80 : 0x00));

	l64781_ग_लिखोreg (state, 0x22, ddfs_offset_fixed & 0xff);
	l64781_ग_लिखोreg (state, 0x23, (ddfs_offset_fixed >> 8) & 0x3f);

	l64781_पढ़ोreg (state, 0x00);  /*  clear पूर्णांकerrupt रेजिस्टरs... */
	l64781_पढ़ोreg (state, 0x01);  /*  dto. */

	apply_tps (state);

	वापस 0;
पूर्ण

अटल पूर्णांक get_frontend(काष्ठा dvb_frontend *fe,
			काष्ठा dtv_frontend_properties *p)
अणु
	काष्ठा l64781_state* state = fe->demodulator_priv;
	पूर्णांक पंचांगp;


	पंचांगp = l64781_पढ़ोreg(state, 0x04);
	चयन(पंचांगp & 3) अणु
	हाल 0:
		p->guard_पूर्णांकerval = GUARD_INTERVAL_1_32;
		अवरोध;
	हाल 1:
		p->guard_पूर्णांकerval = GUARD_INTERVAL_1_16;
		अवरोध;
	हाल 2:
		p->guard_पूर्णांकerval = GUARD_INTERVAL_1_8;
		अवरोध;
	हाल 3:
		p->guard_पूर्णांकerval = GUARD_INTERVAL_1_4;
		अवरोध;
	पूर्ण
	चयन((पंचांगp >> 2) & 3) अणु
	हाल 0:
		p->transmission_mode = TRANSMISSION_MODE_2K;
		अवरोध;
	हाल 1:
		p->transmission_mode = TRANSMISSION_MODE_8K;
		अवरोध;
	शेष:
		prपूर्णांकk(KERN_WARNING "Unexpected value for transmission_mode\n");
	पूर्ण

	पंचांगp = l64781_पढ़ोreg(state, 0x05);
	चयन(पंचांगp & 7) अणु
	हाल 0:
		p->code_rate_HP = FEC_1_2;
		अवरोध;
	हाल 1:
		p->code_rate_HP = FEC_2_3;
		अवरोध;
	हाल 2:
		p->code_rate_HP = FEC_3_4;
		अवरोध;
	हाल 3:
		p->code_rate_HP = FEC_5_6;
		अवरोध;
	हाल 4:
		p->code_rate_HP = FEC_7_8;
		अवरोध;
	शेष:
		prपूर्णांकk("Unexpected value for code_rate_HP\n");
	पूर्ण
	चयन((पंचांगp >> 3) & 7) अणु
	हाल 0:
		p->code_rate_LP = FEC_1_2;
		अवरोध;
	हाल 1:
		p->code_rate_LP = FEC_2_3;
		अवरोध;
	हाल 2:
		p->code_rate_LP = FEC_3_4;
		अवरोध;
	हाल 3:
		p->code_rate_LP = FEC_5_6;
		अवरोध;
	हाल 4:
		p->code_rate_LP = FEC_7_8;
		अवरोध;
	शेष:
		prपूर्णांकk("Unexpected value for code_rate_LP\n");
	पूर्ण

	पंचांगp = l64781_पढ़ोreg(state, 0x06);
	चयन(पंचांगp & 3) अणु
	हाल 0:
		p->modulation = QPSK;
		अवरोध;
	हाल 1:
		p->modulation = QAM_16;
		अवरोध;
	हाल 2:
		p->modulation = QAM_64;
		अवरोध;
	शेष:
		prपूर्णांकk(KERN_WARNING "Unexpected value for modulation\n");
	पूर्ण
	चयन((पंचांगp >> 2) & 7) अणु
	हाल 0:
		p->hierarchy = HIERARCHY_NONE;
		अवरोध;
	हाल 1:
		p->hierarchy = HIERARCHY_1;
		अवरोध;
	हाल 2:
		p->hierarchy = HIERARCHY_2;
		अवरोध;
	हाल 3:
		p->hierarchy = HIERARCHY_4;
		अवरोध;
	शेष:
		prपूर्णांकk("Unexpected value for hierarchy\n");
	पूर्ण


	पंचांगp = l64781_पढ़ोreg (state, 0x1d);
	p->inversion = (पंचांगp & 0x80) ? INVERSION_ON : INVERSION_OFF;

	पंचांगp = (पूर्णांक) (l64781_पढ़ोreg (state, 0x08) |
		     (l64781_पढ़ोreg (state, 0x09) << 8) |
		     (l64781_पढ़ोreg (state, 0x0a) << 16));
	p->frequency += पंचांगp;

	वापस 0;
पूर्ण

अटल पूर्णांक l64781_पढ़ो_status(काष्ठा dvb_frontend *fe, क्रमागत fe_status *status)
अणु
	काष्ठा l64781_state* state = fe->demodulator_priv;
	पूर्णांक sync = l64781_पढ़ोreg (state, 0x32);
	पूर्णांक gain = l64781_पढ़ोreg (state, 0x0e);

	l64781_पढ़ोreg (state, 0x00);  /*  clear पूर्णांकerrupt रेजिस्टरs... */
	l64781_पढ़ोreg (state, 0x01);  /*  dto. */

	*status = 0;

	अगर (gain > 5)
		*status |= FE_HAS_SIGNAL;

	अगर (sync & 0x02) /* VCXO locked, this criteria should be ok */
		*status |= FE_HAS_CARRIER;

	अगर (sync & 0x20)
		*status |= FE_HAS_VITERBI;

	अगर (sync & 0x40)
		*status |= FE_HAS_SYNC;

	अगर (sync == 0x7f)
		*status |= FE_HAS_LOCK;

	वापस 0;
पूर्ण

अटल पूर्णांक l64781_पढ़ो_ber(काष्ठा dvb_frontend* fe, u32* ber)
अणु
	काष्ठा l64781_state* state = fe->demodulator_priv;

	/*   XXX FIXME: set up counting period (reg 0x26...0x28)
	 */
	*ber = l64781_पढ़ोreg (state, 0x39)
	    | (l64781_पढ़ोreg (state, 0x3a) << 8);

	वापस 0;
पूर्ण

अटल पूर्णांक l64781_पढ़ो_संकेत_strength(काष्ठा dvb_frontend* fe, u16* संकेत_strength)
अणु
	काष्ठा l64781_state* state = fe->demodulator_priv;

	u8 gain = l64781_पढ़ोreg (state, 0x0e);
	*संकेत_strength = (gain << 8) | gain;

	वापस 0;
पूर्ण

अटल पूर्णांक l64781_पढ़ो_snr(काष्ठा dvb_frontend* fe, u16* snr)
अणु
	काष्ठा l64781_state* state = fe->demodulator_priv;

	u8 avg_quality = 0xff - l64781_पढ़ोreg (state, 0x33);
	*snr = (avg_quality << 8) | avg_quality; /* not exact, but...*/

	वापस 0;
पूर्ण

अटल पूर्णांक l64781_पढ़ो_ucblocks(काष्ठा dvb_frontend* fe, u32* ucblocks)
अणु
	काष्ठा l64781_state* state = fe->demodulator_priv;

	*ucblocks = l64781_पढ़ोreg (state, 0x37)
	   | (l64781_पढ़ोreg (state, 0x38) << 8);

	वापस 0;
पूर्ण

अटल पूर्णांक l64781_sleep(काष्ठा dvb_frontend* fe)
अणु
	काष्ठा l64781_state* state = fe->demodulator_priv;

	/* Power करोwn */
	वापस l64781_ग_लिखोreg (state, 0x3e, 0x5a);
पूर्ण

अटल पूर्णांक l64781_init(काष्ठा dvb_frontend* fe)
अणु
	काष्ठा l64781_state* state = fe->demodulator_priv;

	reset_and_configure (state);

	/* Power up */
	l64781_ग_लिखोreg (state, 0x3e, 0xa5);

	/* Reset hard */
	l64781_ग_लिखोreg (state, 0x2a, 0x04);
	l64781_ग_लिखोreg (state, 0x2a, 0x00);

	/* Set tuner specअगरic things */
	/* AFC_POL, set also in reset_afc */
	l64781_ग_लिखोreg (state, 0x07, 0x8e);

	/* Use पूर्णांकernal ADC */
	l64781_ग_लिखोreg (state, 0x0b, 0x81);

	/* AGC loop gain, and polarity is positive */
	l64781_ग_लिखोreg (state, 0x0c, 0x84);

	/* Internal ADC outमाला_दो two's complement */
	l64781_ग_लिखोreg (state, 0x0d, 0x8c);

	/* With ppm=8000, it seems the DTR_SENSITIVITY will result in
	   value of 2 with all possible bandwidths and guard
	   पूर्णांकervals, which is the initial value anyway. */
	/*l64781_ग_लिखोreg (state, 0x19, 0x92);*/

	/* Everything is two's complement, soft bit and CSI_OUT too */
	l64781_ग_लिखोreg (state, 0x1e, 0x09);

	/* delay a bit after first init attempt */
	अगर (state->first) अणु
		state->first = 0;
		msleep(200);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक l64781_get_tune_settings(काष्ठा dvb_frontend* fe,
				    काष्ठा dvb_frontend_tune_settings* fesettings)
अणु
	fesettings->min_delay_ms = 4000;
	fesettings->step_size = 0;
	fesettings->max_drअगरt = 0;
	वापस 0;
पूर्ण

अटल व्योम l64781_release(काष्ठा dvb_frontend* fe)
अणु
	काष्ठा l64781_state* state = fe->demodulator_priv;
	kमुक्त(state);
पूर्ण

अटल स्थिर काष्ठा dvb_frontend_ops l64781_ops;

काष्ठा dvb_frontend* l64781_attach(स्थिर काष्ठा l64781_config* config,
				   काष्ठा i2c_adapter* i2c)
अणु
	काष्ठा l64781_state* state = शून्य;
	पूर्णांक reg0x3e = -1;
	u8 b0 [] = अणु 0x1a पूर्ण;
	u8 b1 [] = अणु 0x00 पूर्ण;
	काष्ठा i2c_msg msg [] = अणु अणु .addr = config->demod_address, .flags = 0, .buf = b0, .len = 1 पूर्ण,
			   अणु .addr = config->demod_address, .flags = I2C_M_RD, .buf = b1, .len = 1 पूर्ण पूर्ण;

	/* allocate memory क्रम the पूर्णांकernal state */
	state = kzalloc(माप(काष्ठा l64781_state), GFP_KERNEL);
	अगर (state == शून्य) जाओ error;

	/* setup the state */
	state->config = config;
	state->i2c = i2c;
	state->first = 1;

	/*
	 *  the L64781 won't show up beक्रमe we send the reset_and_configure()
	 *  broadcast. If nothing responds there is no L64781 on the bus...
	 */
	अगर (reset_and_configure(state) < 0) अणु
		dprपूर्णांकk("No response to reset and configure broadcast...\n");
		जाओ error;
	पूर्ण

	/* The chip always responds to पढ़ोs */
	अगर (i2c_transfer(state->i2c, msg, 2) != 2) अणु
		dprपूर्णांकk("No response to read on I2C bus\n");
		जाओ error;
	पूर्ण

	/* Save current रेजिस्टर contents क्रम bailout */
	reg0x3e = l64781_पढ़ोreg(state, 0x3e);

	/* Reading the POWER_DOWN रेजिस्टर always वापसs 0 */
	अगर (reg0x3e != 0) अणु
		dprपूर्णांकk("Device doesn't look like L64781\n");
		जाओ error;
	पूर्ण

	/* Turn the chip off */
	l64781_ग_लिखोreg (state, 0x3e, 0x5a);

	/* Responds to all पढ़ोs with 0 */
	अगर (l64781_पढ़ोreg(state, 0x1a) != 0) अणु
		dprपूर्णांकk("Read 1 returned unexpected value\n");
		जाओ error;
	पूर्ण

	/* Turn the chip on */
	l64781_ग_लिखोreg (state, 0x3e, 0xa5);

	/* Responds with रेजिस्टर शेष value */
	अगर (l64781_पढ़ोreg(state, 0x1a) != 0xa1) अणु
		dprपूर्णांकk("Read 2 returned unexpected value\n");
		जाओ error;
	पूर्ण

	/* create dvb_frontend */
	स_नकल(&state->frontend.ops, &l64781_ops, माप(काष्ठा dvb_frontend_ops));
	state->frontend.demodulator_priv = state;
	वापस &state->frontend;

error:
	अगर (reg0x3e >= 0)
		l64781_ग_लिखोreg (state, 0x3e, reg0x3e);  /* restore reg 0x3e */
	kमुक्त(state);
	वापस शून्य;
पूर्ण

अटल स्थिर काष्ठा dvb_frontend_ops l64781_ops = अणु
	.delsys = अणु SYS_DVBT पूर्ण,
	.info = अणु
		.name = "LSI L64781 DVB-T",
	/*	.frequency_min_hz = ???,*/
	/*	.frequency_max_hz = ???,*/
		.frequency_stepsize_hz = 166666,
	/*      .symbol_rate_tolerance = ???,*/
		.caps = FE_CAN_FEC_1_2 | FE_CAN_FEC_2_3 | FE_CAN_FEC_3_4 |
		      FE_CAN_FEC_5_6 | FE_CAN_FEC_7_8 |
		      FE_CAN_QPSK | FE_CAN_QAM_16 | FE_CAN_QAM_64 |
		      FE_CAN_MUTE_TS
	पूर्ण,

	.release = l64781_release,

	.init = l64781_init,
	.sleep = l64781_sleep,

	.set_frontend = apply_frontend_param,
	.get_frontend = get_frontend,
	.get_tune_settings = l64781_get_tune_settings,

	.पढ़ो_status = l64781_पढ़ो_status,
	.पढ़ो_ber = l64781_पढ़ो_ber,
	.पढ़ो_संकेत_strength = l64781_पढ़ो_संकेत_strength,
	.पढ़ो_snr = l64781_पढ़ो_snr,
	.पढ़ो_ucblocks = l64781_पढ़ो_ucblocks,
पूर्ण;

MODULE_DESCRIPTION("LSI L64781 DVB-T Demodulator driver");
MODULE_AUTHOR("Holger Waechtler, Marko Kohtala");
MODULE_LICENSE("GPL");

EXPORT_SYMBOL(l64781_attach);
