<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Samsung s5h1432 DVB-T demodulator driver
 *
 *  Copyright (C) 2009 Bill Liu <Bill.Liu@Conexant.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/माला.स>
#समावेश <linux/slab.h>
#समावेश <linux/delay.h>
#समावेश <media/dvb_frontend.h>
#समावेश "s5h1432.h"

काष्ठा s5h1432_state अणु

	काष्ठा i2c_adapter *i2c;

	/* configuration settings */
	स्थिर काष्ठा s5h1432_config *config;

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

अटल पूर्णांक s5h1432_ग_लिखोreg(काष्ठा s5h1432_state *state,
			    u8 addr, u8 reg, u8 data)
अणु
	पूर्णांक ret;
	u8 buf[] = अणु reg, data पूर्ण;

	काष्ठा i2c_msg msg = अणु.addr = addr, .flags = 0, .buf = buf, .len = 2 पूर्ण;

	ret = i2c_transfer(state->i2c, &msg, 1);

	अगर (ret != 1)
		prपूर्णांकk(KERN_ERR "%s: writereg error 0x%02x 0x%02x 0x%04x, ret == %i)\n",
		       __func__, addr, reg, data, ret);

	वापस (ret != 1) ? -1 : 0;
पूर्ण

अटल u8 s5h1432_पढ़ोreg(काष्ठा s5h1432_state *state, u8 addr, u8 reg)
अणु
	पूर्णांक ret;
	u8 b0[] = अणु reg पूर्ण;
	u8 b1[] = अणु 0 पूर्ण;

	काष्ठा i2c_msg msg[] = अणु
		अणु.addr = addr, .flags = 0, .buf = b0, .len = 1पूर्ण,
		अणु.addr = addr, .flags = I2C_M_RD, .buf = b1, .len = 1पूर्ण
	पूर्ण;

	ret = i2c_transfer(state->i2c, msg, 2);

	अगर (ret != 2)
		prपूर्णांकk(KERN_ERR "%s: readreg error (ret == %i)\n",
		       __func__, ret);
	वापस b1[0];
पूर्ण

अटल पूर्णांक s5h1432_sleep(काष्ठा dvb_frontend *fe)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक s5h1432_set_channel_bandwidth(काष्ठा dvb_frontend *fe,
					 u32 bandwidth)
अणु
	काष्ठा s5h1432_state *state = fe->demodulator_priv;

	u8 reg = 0;

	/* Register [0x2E] bit 3:2 : 8MHz = 0; 7MHz = 1; 6MHz = 2 */
	reg = s5h1432_पढ़ोreg(state, S5H1432_I2C_TOP_ADDR, 0x2E);
	reg &= ~(0x0C);
	चयन (bandwidth) अणु
	हाल 6:
		reg |= 0x08;
		अवरोध;
	हाल 7:
		reg |= 0x04;
		अवरोध;
	हाल 8:
		reg |= 0x00;
		अवरोध;
	शेष:
		वापस 0;
	पूर्ण
	s5h1432_ग_लिखोreg(state, S5H1432_I2C_TOP_ADDR, 0x2E, reg);
	वापस 1;
पूर्ण

अटल पूर्णांक s5h1432_set_IF(काष्ठा dvb_frontend *fe, u32 अगरFreqHz)
अणु
	काष्ठा s5h1432_state *state = fe->demodulator_priv;

	चयन (अगरFreqHz) अणु
	हाल TAIWAN_HI_IF_FREQ_44_MHZ:
		s5h1432_ग_लिखोreg(state, S5H1432_I2C_TOP_ADDR, 0xe4, 0x55);
		s5h1432_ग_लिखोreg(state, S5H1432_I2C_TOP_ADDR, 0xe5, 0x55);
		s5h1432_ग_लिखोreg(state, S5H1432_I2C_TOP_ADDR, 0xe7, 0x15);
		अवरोध;
	हाल EUROPE_HI_IF_FREQ_36_MHZ:
		s5h1432_ग_लिखोreg(state, S5H1432_I2C_TOP_ADDR, 0xe4, 0x00);
		s5h1432_ग_लिखोreg(state, S5H1432_I2C_TOP_ADDR, 0xe5, 0x00);
		s5h1432_ग_लिखोreg(state, S5H1432_I2C_TOP_ADDR, 0xe7, 0x40);
		अवरोध;
	हाल IF_FREQ_6_MHZ:
		s5h1432_ग_लिखोreg(state, S5H1432_I2C_TOP_ADDR, 0xe4, 0x00);
		s5h1432_ग_लिखोreg(state, S5H1432_I2C_TOP_ADDR, 0xe5, 0x00);
		s5h1432_ग_लिखोreg(state, S5H1432_I2C_TOP_ADDR, 0xe7, 0xe0);
		अवरोध;
	हाल IF_FREQ_3poपूर्णांक3_MHZ:
		s5h1432_ग_लिखोreg(state, S5H1432_I2C_TOP_ADDR, 0xe4, 0x66);
		s5h1432_ग_लिखोreg(state, S5H1432_I2C_TOP_ADDR, 0xe5, 0x66);
		s5h1432_ग_लिखोreg(state, S5H1432_I2C_TOP_ADDR, 0xe7, 0xEE);
		अवरोध;
	हाल IF_FREQ_3poपूर्णांक5_MHZ:
		s5h1432_ग_लिखोreg(state, S5H1432_I2C_TOP_ADDR, 0xe4, 0x55);
		s5h1432_ग_लिखोreg(state, S5H1432_I2C_TOP_ADDR, 0xe5, 0x55);
		s5h1432_ग_लिखोreg(state, S5H1432_I2C_TOP_ADDR, 0xe7, 0xED);
		अवरोध;
	हाल IF_FREQ_4_MHZ:
		s5h1432_ग_लिखोreg(state, S5H1432_I2C_TOP_ADDR, 0xe4, 0xAA);
		s5h1432_ग_लिखोreg(state, S5H1432_I2C_TOP_ADDR, 0xe5, 0xAA);
		s5h1432_ग_लिखोreg(state, S5H1432_I2C_TOP_ADDR, 0xe7, 0xEA);
		अवरोध;
	शेष:
		अणु
			u32 value = 0;
			value = (u32) (((48000 - (अगरFreqHz / 1000)) * 512 *
					(u32) 32768) / (48 * 1000));
			prपूर्णांकk(KERN_INFO
			       "Default IFFreq %d :reg value = 0x%x\n",
			       अगरFreqHz, value);
			s5h1432_ग_लिखोreg(state, S5H1432_I2C_TOP_ADDR, 0xe4,
					 (u8) value & 0xFF);
			s5h1432_ग_लिखोreg(state, S5H1432_I2C_TOP_ADDR, 0xe5,
					 (u8) (value >> 8) & 0xFF);
			s5h1432_ग_लिखोreg(state, S5H1432_I2C_TOP_ADDR, 0xe7,
					 (u8) (value >> 16) & 0xFF);
			अवरोध;
		पूर्ण

	पूर्ण

	वापस 1;
पूर्ण

/* Talk to the demod, set the FEC, GUARD, QAM settings etc */
अटल पूर्णांक s5h1432_set_frontend(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dtv_frontend_properties *p = &fe->dtv_property_cache;
	u32 dvb_bandwidth = 8;
	काष्ठा s5h1432_state *state = fe->demodulator_priv;

	अगर (p->frequency == state->current_frequency) अणु
		/*current_frequency = p->frequency; */
		/*state->current_frequency = p->frequency; */
	पूर्ण अन्यथा अणु
		fe->ops.tuner_ops.set_params(fe);
		msleep(300);
		s5h1432_set_channel_bandwidth(fe, dvb_bandwidth);
		चयन (p->bandwidth_hz) अणु
		हाल 6000000:
			dvb_bandwidth = 6;
			s5h1432_set_IF(fe, IF_FREQ_4_MHZ);
			अवरोध;
		हाल 7000000:
			dvb_bandwidth = 7;
			s5h1432_set_IF(fe, IF_FREQ_4_MHZ);
			अवरोध;
		हाल 8000000:
			dvb_bandwidth = 8;
			s5h1432_set_IF(fe, IF_FREQ_4_MHZ);
			अवरोध;
		शेष:
			वापस 0;
		पूर्ण
		/*fe->ops.tuner_ops.set_params(fe); */
/*Soft Reset chip*/
		msleep(30);
		s5h1432_ग_लिखोreg(state, S5H1432_I2C_TOP_ADDR, 0x09, 0x1a);
		msleep(30);
		s5h1432_ग_लिखोreg(state, S5H1432_I2C_TOP_ADDR, 0x09, 0x1b);

		s5h1432_set_channel_bandwidth(fe, dvb_bandwidth);
		चयन (p->bandwidth_hz) अणु
		हाल 6000000:
			dvb_bandwidth = 6;
			s5h1432_set_IF(fe, IF_FREQ_4_MHZ);
			अवरोध;
		हाल 7000000:
			dvb_bandwidth = 7;
			s5h1432_set_IF(fe, IF_FREQ_4_MHZ);
			अवरोध;
		हाल 8000000:
			dvb_bandwidth = 8;
			s5h1432_set_IF(fe, IF_FREQ_4_MHZ);
			अवरोध;
		शेष:
			वापस 0;
		पूर्ण
		/*fe->ops.tuner_ops.set_params(fe); */
		/*Soft Reset chip*/
		msleep(30);
		s5h1432_ग_लिखोreg(state, S5H1432_I2C_TOP_ADDR, 0x09, 0x1a);
		msleep(30);
		s5h1432_ग_लिखोreg(state, S5H1432_I2C_TOP_ADDR, 0x09, 0x1b);

	पूर्ण

	state->current_frequency = p->frequency;

	वापस 0;
पूर्ण

अटल पूर्णांक s5h1432_init(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा s5h1432_state *state = fe->demodulator_priv;

	u8 reg = 0;
	state->current_frequency = 0;
	prपूर्णांकk(KERN_INFO " s5h1432_init().\n");

	/*Set VSB mode as शेष, this also करोes a soft reset */
	/*Initialize रेजिस्टरs */

	s5h1432_ग_लिखोreg(state, S5H1432_I2C_TOP_ADDR, 0x04, 0xa8);
	s5h1432_ग_लिखोreg(state, S5H1432_I2C_TOP_ADDR, 0x05, 0x01);
	s5h1432_ग_लिखोreg(state, S5H1432_I2C_TOP_ADDR, 0x07, 0x70);
	s5h1432_ग_लिखोreg(state, S5H1432_I2C_TOP_ADDR, 0x19, 0x80);
	s5h1432_ग_लिखोreg(state, S5H1432_I2C_TOP_ADDR, 0x1b, 0x9D);
	s5h1432_ग_लिखोreg(state, S5H1432_I2C_TOP_ADDR, 0x1c, 0x30);
	s5h1432_ग_लिखोreg(state, S5H1432_I2C_TOP_ADDR, 0x1d, 0x20);
	s5h1432_ग_लिखोreg(state, S5H1432_I2C_TOP_ADDR, 0x1e, 0x1B);
	s5h1432_ग_लिखोreg(state, S5H1432_I2C_TOP_ADDR, 0x2e, 0x40);
	s5h1432_ग_लिखोreg(state, S5H1432_I2C_TOP_ADDR, 0x42, 0x84);
	s5h1432_ग_लिखोreg(state, S5H1432_I2C_TOP_ADDR, 0x50, 0x5a);
	s5h1432_ग_लिखोreg(state, S5H1432_I2C_TOP_ADDR, 0x5a, 0xd3);
	s5h1432_ग_लिखोreg(state, S5H1432_I2C_TOP_ADDR, 0x68, 0x50);
	s5h1432_ग_लिखोreg(state, S5H1432_I2C_TOP_ADDR, 0xb8, 0x3c);
	s5h1432_ग_लिखोreg(state, S5H1432_I2C_TOP_ADDR, 0xc4, 0x10);
	s5h1432_ग_लिखोreg(state, S5H1432_I2C_TOP_ADDR, 0xcc, 0x9c);
	s5h1432_ग_लिखोreg(state, S5H1432_I2C_TOP_ADDR, 0xDA, 0x00);
	s5h1432_ग_लिखोreg(state, S5H1432_I2C_TOP_ADDR, 0xe1, 0x94);
	/* s5h1432_ग_लिखोreg(state, S5H1432_I2C_TOP_ADDR, 0xf4, 0xa1); */
	s5h1432_ग_लिखोreg(state, S5H1432_I2C_TOP_ADDR, 0xf9, 0x00);

	/*For NXP tuner*/

	/*Set 3.3MHz as शेष IF frequency */
	s5h1432_ग_लिखोreg(state, S5H1432_I2C_TOP_ADDR, 0xe4, 0x66);
	s5h1432_ग_लिखोreg(state, S5H1432_I2C_TOP_ADDR, 0xe5, 0x66);
	s5h1432_ग_लिखोreg(state, S5H1432_I2C_TOP_ADDR, 0xe7, 0xEE);
	/* Set reg 0x1E to get the full dynamic range */
	s5h1432_ग_लिखोreg(state, S5H1432_I2C_TOP_ADDR, 0x1e, 0x31);

	/* Mode setting in demod */
	reg = s5h1432_पढ़ोreg(state, S5H1432_I2C_TOP_ADDR, 0x42);
	reg |= 0x80;
	s5h1432_ग_लिखोreg(state, S5H1432_I2C_TOP_ADDR, 0x42, reg);
	/* Serial mode */

	/* Soft Reset chip */

	s5h1432_ग_लिखोreg(state, S5H1432_I2C_TOP_ADDR, 0x09, 0x1a);
	msleep(30);
	s5h1432_ग_लिखोreg(state, S5H1432_I2C_TOP_ADDR, 0x09, 0x1b);


	वापस 0;
पूर्ण

अटल पूर्णांक s5h1432_पढ़ो_status(काष्ठा dvb_frontend *fe, क्रमागत fe_status *status)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक s5h1432_पढ़ो_संकेत_strength(काष्ठा dvb_frontend *fe,
					u16 *संकेत_strength)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक s5h1432_पढ़ो_snr(काष्ठा dvb_frontend *fe, u16 *snr)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक s5h1432_पढ़ो_ucblocks(काष्ठा dvb_frontend *fe, u32 *ucblocks)
अणु

	वापस 0;
पूर्ण

अटल पूर्णांक s5h1432_पढ़ो_ber(काष्ठा dvb_frontend *fe, u32 *ber)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक s5h1432_get_tune_settings(काष्ठा dvb_frontend *fe,
				     काष्ठा dvb_frontend_tune_settings *tune)
अणु
	वापस 0;
पूर्ण

अटल व्योम s5h1432_release(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा s5h1432_state *state = fe->demodulator_priv;
	kमुक्त(state);
पूर्ण

अटल स्थिर काष्ठा dvb_frontend_ops s5h1432_ops;

काष्ठा dvb_frontend *s5h1432_attach(स्थिर काष्ठा s5h1432_config *config,
				    काष्ठा i2c_adapter *i2c)
अणु
	काष्ठा s5h1432_state *state = शून्य;

	prपूर्णांकk(KERN_INFO " Enter s5h1432_attach(). attach success!\n");
	/* allocate memory क्रम the पूर्णांकernal state */
	state = kदो_स्मृति(माप(काष्ठा s5h1432_state), GFP_KERNEL);
	अगर (!state)
		वापस शून्य;

	/* setup the state */
	state->config = config;
	state->i2c = i2c;
	state->current_modulation = QAM_16;
	state->inversion = state->config->inversion;

	/* create dvb_frontend */
	स_नकल(&state->frontend.ops, &s5h1432_ops,
	       माप(काष्ठा dvb_frontend_ops));

	state->frontend.demodulator_priv = state;

	वापस &state->frontend;
पूर्ण
EXPORT_SYMBOL(s5h1432_attach);

अटल स्थिर काष्ठा dvb_frontend_ops s5h1432_ops = अणु
	.delsys = अणु SYS_DVBT पूर्ण,
	.info = अणु
		 .name = "Samsung s5h1432 DVB-T Frontend",
		 .frequency_min_hz = 177 * MHz,
		 .frequency_max_hz = 858 * MHz,
		 .frequency_stepsize_hz = 166666,
		 .caps = FE_CAN_FEC_1_2 | FE_CAN_FEC_2_3 | FE_CAN_FEC_3_4 |
		 FE_CAN_FEC_5_6 | FE_CAN_FEC_7_8 | FE_CAN_FEC_AUTO |
		 FE_CAN_QPSK | FE_CAN_QAM_16 | FE_CAN_QAM_64 | FE_CAN_QAM_AUTO |
		 FE_CAN_HIERARCHY_AUTO | FE_CAN_GUARD_INTERVAL_AUTO |
		 FE_CAN_TRANSMISSION_MODE_AUTO | FE_CAN_RECOVERपूर्ण,

	.init = s5h1432_init,
	.sleep = s5h1432_sleep,
	.set_frontend = s5h1432_set_frontend,
	.get_tune_settings = s5h1432_get_tune_settings,
	.पढ़ो_status = s5h1432_पढ़ो_status,
	.पढ़ो_ber = s5h1432_पढ़ो_ber,
	.पढ़ो_संकेत_strength = s5h1432_पढ़ो_संकेत_strength,
	.पढ़ो_snr = s5h1432_पढ़ो_snr,
	.पढ़ो_ucblocks = s5h1432_पढ़ो_ucblocks,
	.release = s5h1432_release,
पूर्ण;

module_param(debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug, "Enable verbose debug messages");

MODULE_DESCRIPTION("Samsung s5h1432 DVB-T Demodulator driver");
MODULE_AUTHOR("Bill Liu");
MODULE_LICENSE("GPL");
