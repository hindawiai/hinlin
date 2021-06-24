<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
   Driver क्रम the Spase sp887x demodulator
*/

/*
 * This driver needs बाह्यal firmware. Please use the command
 * "<kerneldir>/scripts/get_dvb_firmware sp887x" to
 * करोwnload/extract it, and then copy it to /usr/lib/hotplug/firmware
 * or /lib/firmware (depending on configuration of firmware hotplug).
 */
#घोषणा SP887X_DEFAULT_FIRMWARE "dvb-fe-sp887x.fw"

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/firmware.h>
#समावेश <linux/माला.स>
#समावेश <linux/slab.h>

#समावेश <media/dvb_frontend.h>
#समावेश "sp887x.h"


काष्ठा sp887x_state अणु
	काष्ठा i2c_adapter* i2c;
	स्थिर काष्ठा sp887x_config* config;
	काष्ठा dvb_frontend frontend;

	/* demodulator निजी data */
	u8 initialised:1;
पूर्ण;

अटल पूर्णांक debug;
#घोषणा dprपूर्णांकk(args...) \
	करो अणु \
		अगर (debug) prपूर्णांकk(KERN_DEBUG "sp887x: " args); \
	पूर्ण जबतक (0)

अटल पूर्णांक i2c_ग_लिखोbytes (काष्ठा sp887x_state* state, u8 *buf, u8 len)
अणु
	काष्ठा i2c_msg msg = अणु .addr = state->config->demod_address, .flags = 0, .buf = buf, .len = len पूर्ण;
	पूर्णांक err;

	अगर ((err = i2c_transfer (state->i2c, &msg, 1)) != 1) अणु
		prपूर्णांकk ("%s: i2c write error (addr %02x, err == %i)\n",
			__func__, state->config->demod_address, err);
		वापस -EREMOTEIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sp887x_ग_लिखोreg (काष्ठा sp887x_state* state, u16 reg, u16 data)
अणु
	u8 b0 [] = अणु reg >> 8 , reg & 0xff, data >> 8, data & 0xff पूर्ण;
	काष्ठा i2c_msg msg = अणु .addr = state->config->demod_address, .flags = 0, .buf = b0, .len = 4 पूर्ण;
	पूर्णांक ret;

	अगर ((ret = i2c_transfer(state->i2c, &msg, 1)) != 1) अणु
		/*
		 *  in हाल of soft reset we ignore ACK errors...
		 */
		अगर (!(reg == 0xf1a && data == 0x000 &&
			(ret == -EREMOTEIO || ret == -EFAULT)))
		अणु
			prपूर्णांकk("%s: writereg error (reg %03x, data %03x, ret == %i)\n",
			       __func__, reg & 0xffff, data & 0xffff, ret);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sp887x_पढ़ोreg (काष्ठा sp887x_state* state, u16 reg)
अणु
	u8 b0 [] = अणु reg >> 8 , reg & 0xff पूर्ण;
	u8 b1 [2];
	पूर्णांक ret;
	काष्ठा i2c_msg msg[] = अणुअणु .addr = state->config->demod_address, .flags = 0, .buf = b0, .len = 2 पूर्ण,
			 अणु .addr = state->config->demod_address, .flags = I2C_M_RD, .buf = b1, .len = 2 पूर्णपूर्ण;

	अगर ((ret = i2c_transfer(state->i2c, msg, 2)) != 2) अणु
		prपूर्णांकk("%s: readreg error (ret == %i)\n", __func__, ret);
		वापस -1;
	पूर्ण

	वापस (((b1[0] << 8) | b1[1]) & 0xfff);
पूर्ण

अटल व्योम sp887x_microcontroller_stop (काष्ठा sp887x_state* state)
अणु
	dprपूर्णांकk("%s\n", __func__);
	sp887x_ग_लिखोreg(state, 0xf08, 0x000);
	sp887x_ग_लिखोreg(state, 0xf09, 0x000);

	/* microcontroller STOP */
	sp887x_ग_लिखोreg(state, 0xf00, 0x000);
पूर्ण

अटल व्योम sp887x_microcontroller_start (काष्ठा sp887x_state* state)
अणु
	dprपूर्णांकk("%s\n", __func__);
	sp887x_ग_लिखोreg(state, 0xf08, 0x000);
	sp887x_ग_लिखोreg(state, 0xf09, 0x000);

	/* microcontroller START */
	sp887x_ग_लिखोreg(state, 0xf00, 0x001);
पूर्ण

अटल व्योम sp887x_setup_agc (काष्ठा sp887x_state* state)
अणु
	/* setup AGC parameters */
	dprपूर्णांकk("%s\n", __func__);
	sp887x_ग_लिखोreg(state, 0x33c, 0x054);
	sp887x_ग_लिखोreg(state, 0x33b, 0x04c);
	sp887x_ग_लिखोreg(state, 0x328, 0x000);
	sp887x_ग_लिखोreg(state, 0x327, 0x005);
	sp887x_ग_लिखोreg(state, 0x326, 0x001);
	sp887x_ग_लिखोreg(state, 0x325, 0x001);
	sp887x_ग_लिखोreg(state, 0x324, 0x001);
	sp887x_ग_लिखोreg(state, 0x318, 0x050);
	sp887x_ग_लिखोreg(state, 0x317, 0x3fe);
	sp887x_ग_लिखोreg(state, 0x316, 0x001);
	sp887x_ग_लिखोreg(state, 0x313, 0x005);
	sp887x_ग_लिखोreg(state, 0x312, 0x002);
	sp887x_ग_लिखोreg(state, 0x306, 0x000);
	sp887x_ग_लिखोreg(state, 0x303, 0x000);
पूर्ण

#घोषणा BLOCKSIZE 30
#घोषणा FW_SIZE 0x4000
/*
 *  load firmware and setup MPEG पूर्णांकerface...
 */
अटल पूर्णांक sp887x_initial_setup (काष्ठा dvb_frontend* fe, स्थिर काष्ठा firmware *fw)
अणु
	काष्ठा sp887x_state* state = fe->demodulator_priv;
	u8 buf [BLOCKSIZE + 2];
	पूर्णांक i;
	पूर्णांक fw_size = fw->size;
	स्थिर अचिन्हित अक्षर *mem = fw->data;

	dprपूर्णांकk("%s\n", __func__);

	/* ignore the first 10 bytes, then we expect 0x4000 bytes of firmware */
	अगर (fw_size < FW_SIZE + 10)
		वापस -ENODEV;

	mem = fw->data + 10;

	/* soft reset */
	sp887x_ग_लिखोreg(state, 0xf1a, 0x000);

	sp887x_microcontroller_stop (state);

	prपूर्णांकk ("%s: firmware upload... ", __func__);

	/* setup ग_लिखो poपूर्णांकer to -1 (end of memory) */
	/* bit 0x8000 in address is set to enable 13bit mode */
	sp887x_ग_लिखोreg(state, 0x8f08, 0x1fff);

	/* dummy ग_लिखो (wrap around to start of memory) */
	sp887x_ग_लिखोreg(state, 0x8f0a, 0x0000);

	क्रम (i = 0; i < FW_SIZE; i += BLOCKSIZE) अणु
		पूर्णांक c = BLOCKSIZE;
		पूर्णांक err;

		अगर (c > FW_SIZE - i)
			c = FW_SIZE - i;

		/* bit 0x8000 in address is set to enable 13bit mode */
		/* bit 0x4000 enables multibyte पढ़ो/ग_लिखो transfers */
		/* ग_लिखो रेजिस्टर is 0xf0a */
		buf[0] = 0xcf;
		buf[1] = 0x0a;

		स_नकल(&buf[2], mem + i, c);

		अगर ((err = i2c_ग_लिखोbytes (state, buf, c+2)) < 0) अणु
			prपूर्णांकk ("failed.\n");
			prपूर्णांकk ("%s: i2c error (err == %i)\n", __func__, err);
			वापस err;
		पूर्ण
	पूर्ण

	/* करोn't ग_लिखो RS bytes between packets */
	sp887x_ग_लिखोreg(state, 0xc13, 0x001);

	/* suppress घड़ी अगर (!data_valid) */
	sp887x_ग_लिखोreg(state, 0xc14, 0x000);

	/* setup MPEG पूर्णांकerface... */
	sp887x_ग_लिखोreg(state, 0xc1a, 0x872);
	sp887x_ग_लिखोreg(state, 0xc1b, 0x001);
	sp887x_ग_लिखोreg(state, 0xc1c, 0x000); /* parallel mode (serial mode == 1) */
	sp887x_ग_लिखोreg(state, 0xc1a, 0x871);

	/* ADC mode, 2 क्रम MT8872, 3 क्रम SP8870/SP8871 */
	sp887x_ग_लिखोreg(state, 0x301, 0x002);

	sp887x_setup_agc(state);

	/* bit 0x010: enable data valid संकेत */
	sp887x_ग_लिखोreg(state, 0xd00, 0x010);
	sp887x_ग_लिखोreg(state, 0x0d1, 0x000);
	वापस 0;
पूर्ण;

अटल पूर्णांक configure_reg0xc05(काष्ठा dtv_frontend_properties *p, u16 *reg0xc05)
अणु
	पूर्णांक known_parameters = 1;

	*reg0xc05 = 0x000;

	चयन (p->modulation) अणु
	हाल QPSK:
		अवरोध;
	हाल QAM_16:
		*reg0xc05 |= (1 << 10);
		अवरोध;
	हाल QAM_64:
		*reg0xc05 |= (2 << 10);
		अवरोध;
	हाल QAM_AUTO:
		known_parameters = 0;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (p->hierarchy) अणु
	हाल HIERARCHY_NONE:
		अवरोध;
	हाल HIERARCHY_1:
		*reg0xc05 |= (1 << 7);
		अवरोध;
	हाल HIERARCHY_2:
		*reg0xc05 |= (2 << 7);
		अवरोध;
	हाल HIERARCHY_4:
		*reg0xc05 |= (3 << 7);
		अवरोध;
	हाल HIERARCHY_AUTO:
		known_parameters = 0;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (p->code_rate_HP) अणु
	हाल FEC_1_2:
		अवरोध;
	हाल FEC_2_3:
		*reg0xc05 |= (1 << 3);
		अवरोध;
	हाल FEC_3_4:
		*reg0xc05 |= (2 << 3);
		अवरोध;
	हाल FEC_5_6:
		*reg0xc05 |= (3 << 3);
		अवरोध;
	हाल FEC_7_8:
		*reg0xc05 |= (4 << 3);
		अवरोध;
	हाल FEC_AUTO:
		known_parameters = 0;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (known_parameters)
		*reg0xc05 |= (2 << 1);	/* use specअगरied parameters */
	अन्यथा
		*reg0xc05 |= (1 << 1);	/* enable स्वतःprobing */

	वापस 0;
पूर्ण

/*
 *  estimates भागision of two 24bit numbers,
 *  derived from the ves1820/stv0299 driver code
 */
अटल व्योम भागide (पूर्णांक n, पूर्णांक d, पूर्णांक *quotient_i, पूर्णांक *quotient_f)
अणु
	अचिन्हित पूर्णांक q, r;

	r = (n % d) << 8;
	q = (r / d);

	अगर (quotient_i)
		*quotient_i = q;

	अगर (quotient_f) अणु
		r = (r % d) << 8;
		q = (q << 8) | (r / d);
		r = (r % d) << 8;
		*quotient_f = (q << 8) | (r / d);
	पूर्ण
पूर्ण

अटल व्योम sp887x_correct_offsets (काष्ठा sp887x_state* state,
				    काष्ठा dtv_frontend_properties *p,
				    पूर्णांक actual_freq)
अणु
	अटल स्थिर u32 srate_correction [] = अणु 1879617, 4544878, 8098561 पूर्ण;
	पूर्णांक bw_index;
	पूर्णांक freq_offset = actual_freq - p->frequency;
	पूर्णांक sysघड़ी = 61003; //[kHz]
	पूर्णांक अगरreq = 36000000;
	पूर्णांक freq;
	पूर्णांक frequency_shअगरt;

	चयन (p->bandwidth_hz) अणु
	शेष:
	हाल 8000000:
		bw_index = 0;
		अवरोध;
	हाल 7000000:
		bw_index = 1;
		अवरोध;
	हाल 6000000:
		bw_index = 2;
		अवरोध;
	पूर्ण

	अगर (p->inversion == INVERSION_ON)
		freq = अगरreq - freq_offset;
	अन्यथा
		freq = अगरreq + freq_offset;

	भागide(freq / 333, sysघड़ी, शून्य, &frequency_shअगरt);

	अगर (p->inversion == INVERSION_ON)
		frequency_shअगरt = -frequency_shअगरt;

	/* sample rate correction */
	sp887x_ग_लिखोreg(state, 0x319, srate_correction[bw_index] >> 12);
	sp887x_ग_लिखोreg(state, 0x31a, srate_correction[bw_index] & 0xfff);

	/* carrier offset correction */
	sp887x_ग_लिखोreg(state, 0x309, frequency_shअगरt >> 12);
	sp887x_ग_लिखोreg(state, 0x30a, frequency_shअगरt & 0xfff);
पूर्ण

अटल पूर्णांक sp887x_setup_frontend_parameters(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dtv_frontend_properties *p = &fe->dtv_property_cache;
	काष्ठा sp887x_state* state = fe->demodulator_priv;
	अचिन्हित actual_freq;
	पूर्णांक err;
	u16 val, reg0xc05;

	अगर (p->bandwidth_hz != 8000000 &&
	    p->bandwidth_hz != 7000000 &&
	    p->bandwidth_hz != 6000000)
		वापस -EINVAL;

	अगर ((err = configure_reg0xc05(p, &reg0xc05)))
		वापस err;

	sp887x_microcontroller_stop(state);

	/* setup the PLL */
	अगर (fe->ops.tuner_ops.set_params) अणु
		fe->ops.tuner_ops.set_params(fe);
		अगर (fe->ops.i2c_gate_ctrl) fe->ops.i2c_gate_ctrl(fe, 0);
	पूर्ण
	अगर (fe->ops.tuner_ops.get_frequency) अणु
		fe->ops.tuner_ops.get_frequency(fe, &actual_freq);
		अगर (fe->ops.i2c_gate_ctrl) fe->ops.i2c_gate_ctrl(fe, 0);
	पूर्ण अन्यथा अणु
		actual_freq = p->frequency;
	पूर्ण

	/* पढ़ो status reg in order to clear <pending irqs */
	sp887x_पढ़ोreg(state, 0x200);

	sp887x_correct_offsets(state, p, actual_freq);

	/* filter क्रम 6/7/8 Mhz channel */
	अगर (p->bandwidth_hz == 6000000)
		val = 2;
	अन्यथा अगर (p->bandwidth_hz == 7000000)
		val = 1;
	अन्यथा
		val = 0;

	sp887x_ग_लिखोreg(state, 0x311, val);

	/* scan order: 2k first = 0, 8k first = 1 */
	अगर (p->transmission_mode == TRANSMISSION_MODE_2K)
		sp887x_ग_लिखोreg(state, 0x338, 0x000);
	अन्यथा
		sp887x_ग_लिखोreg(state, 0x338, 0x001);

	sp887x_ग_लिखोreg(state, 0xc05, reg0xc05);

	अगर (p->bandwidth_hz == 6000000)
		val = 2 << 3;
	अन्यथा अगर (p->bandwidth_hz == 7000000)
		val = 3 << 3;
	अन्यथा
		val = 0 << 3;

	/* enable OFDM and SAW bits as lock indicators in sync रेजिस्टर 0xf17,
	 * optimize algorithm क्रम given bandwidth...
	 */
	sp887x_ग_लिखोreg(state, 0xf14, 0x160 | val);
	sp887x_ग_लिखोreg(state, 0xf15, 0x000);

	sp887x_microcontroller_start(state);
	वापस 0;
पूर्ण

अटल पूर्णांक sp887x_पढ़ो_status(काष्ठा dvb_frontend *fe, क्रमागत fe_status *status)
अणु
	काष्ठा sp887x_state* state = fe->demodulator_priv;
	u16 snr12 = sp887x_पढ़ोreg(state, 0xf16);
	u16 sync0x200 = sp887x_पढ़ोreg(state, 0x200);
	u16 sync0xf17 = sp887x_पढ़ोreg(state, 0xf17);

	*status = 0;

	अगर (snr12 > 0x00f)
		*status |= FE_HAS_SIGNAL;

	//अगर (sync0x200 & 0x004)
	//	*status |= FE_HAS_SYNC | FE_HAS_CARRIER;

	//अगर (sync0x200 & 0x008)
	//	*status |= FE_HAS_VITERBI;

	अगर ((sync0xf17 & 0x00f) == 0x002) अणु
		*status |= FE_HAS_LOCK;
		*status |= FE_HAS_VITERBI | FE_HAS_SYNC | FE_HAS_CARRIER;
	पूर्ण

	अगर (sync0x200 & 0x001) अणु	/* tuner adjusपंचांगent requested...*/
		पूर्णांक steps = (sync0x200 >> 4) & 0x00f;
		अगर (steps & 0x008)
			steps = -steps;
		dprपूर्णांकk("sp887x: implement tuner adjustment (%+i steps)!!\n",
		       steps);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sp887x_पढ़ो_ber(काष्ठा dvb_frontend* fe, u32* ber)
अणु
	काष्ठा sp887x_state* state = fe->demodulator_priv;

	*ber = (sp887x_पढ़ोreg(state, 0xc08) & 0x3f) |
	       (sp887x_पढ़ोreg(state, 0xc07) << 6);
	sp887x_ग_लिखोreg(state, 0xc08, 0x000);
	sp887x_ग_लिखोreg(state, 0xc07, 0x000);
	अगर (*ber >= 0x3fff0)
		*ber = ~0;

	वापस 0;
पूर्ण

अटल पूर्णांक sp887x_पढ़ो_संकेत_strength(काष्ठा dvb_frontend* fe, u16* strength)
अणु
	काष्ठा sp887x_state* state = fe->demodulator_priv;

	u16 snr12 = sp887x_पढ़ोreg(state, 0xf16);
	u32 संकेत = 3 * (snr12 << 4);
	*strength = (संकेत < 0xffff) ? संकेत : 0xffff;

	वापस 0;
पूर्ण

अटल पूर्णांक sp887x_पढ़ो_snr(काष्ठा dvb_frontend* fe, u16* snr)
अणु
	काष्ठा sp887x_state* state = fe->demodulator_priv;

	u16 snr12 = sp887x_पढ़ोreg(state, 0xf16);
	*snr = (snr12 << 4) | (snr12 >> 8);

	वापस 0;
पूर्ण

अटल पूर्णांक sp887x_पढ़ो_ucblocks(काष्ठा dvb_frontend* fe, u32* ucblocks)
अणु
	काष्ठा sp887x_state* state = fe->demodulator_priv;

	*ucblocks = sp887x_पढ़ोreg(state, 0xc0c);
	अगर (*ucblocks == 0xfff)
		*ucblocks = ~0;

	वापस 0;
पूर्ण

अटल पूर्णांक sp887x_i2c_gate_ctrl(काष्ठा dvb_frontend* fe, पूर्णांक enable)
अणु
	काष्ठा sp887x_state* state = fe->demodulator_priv;

	अगर (enable) अणु
		वापस sp887x_ग_लिखोreg(state, 0x206, 0x001);
	पूर्ण अन्यथा अणु
		वापस sp887x_ग_लिखोreg(state, 0x206, 0x000);
	पूर्ण
पूर्ण

अटल पूर्णांक sp887x_sleep(काष्ठा dvb_frontend* fe)
अणु
	काष्ठा sp887x_state* state = fe->demodulator_priv;

	/* tristate TS output and disable पूर्णांकerface pins */
	sp887x_ग_लिखोreg(state, 0xc18, 0x000);

	वापस 0;
पूर्ण

अटल पूर्णांक sp887x_init(काष्ठा dvb_frontend* fe)
अणु
	काष्ठा sp887x_state* state = fe->demodulator_priv;
	स्थिर काष्ठा firmware *fw = शून्य;
	पूर्णांक ret;

	अगर (!state->initialised) अणु
		/* request the firmware, this will block until someone uploads it */
		prपूर्णांकk("sp887x: waiting for firmware upload (%s)...\n", SP887X_DEFAULT_FIRMWARE);
		ret = state->config->request_firmware(fe, &fw, SP887X_DEFAULT_FIRMWARE);
		अगर (ret) अणु
			prपूर्णांकk("sp887x: no firmware upload (timeout or file not found?)\n");
			वापस ret;
		पूर्ण

		ret = sp887x_initial_setup(fe, fw);
		release_firmware(fw);
		अगर (ret) अणु
			prपूर्णांकk("sp887x: writing firmware to device failed\n");
			वापस ret;
		पूर्ण
		prपूर्णांकk("sp887x: firmware upload complete\n");
		state->initialised = 1;
	पूर्ण

	/* enable TS output and पूर्णांकerface pins */
	sp887x_ग_लिखोreg(state, 0xc18, 0x00d);

	वापस 0;
पूर्ण

अटल पूर्णांक sp887x_get_tune_settings(काष्ठा dvb_frontend* fe, काष्ठा dvb_frontend_tune_settings* fesettings)
अणु
	fesettings->min_delay_ms = 350;
	fesettings->step_size = 166666*2;
	fesettings->max_drअगरt = (166666*2)+1;
	वापस 0;
पूर्ण

अटल व्योम sp887x_release(काष्ठा dvb_frontend* fe)
अणु
	काष्ठा sp887x_state* state = fe->demodulator_priv;
	kमुक्त(state);
पूर्ण

अटल स्थिर काष्ठा dvb_frontend_ops sp887x_ops;

काष्ठा dvb_frontend* sp887x_attach(स्थिर काष्ठा sp887x_config* config,
				   काष्ठा i2c_adapter* i2c)
अणु
	काष्ठा sp887x_state* state = शून्य;

	/* allocate memory क्रम the पूर्णांकernal state */
	state = kzalloc(माप(काष्ठा sp887x_state), GFP_KERNEL);
	अगर (state == शून्य) जाओ error;

	/* setup the state */
	state->config = config;
	state->i2c = i2c;
	state->initialised = 0;

	/* check अगर the demod is there */
	अगर (sp887x_पढ़ोreg(state, 0x0200) < 0) जाओ error;

	/* create dvb_frontend */
	स_नकल(&state->frontend.ops, &sp887x_ops, माप(काष्ठा dvb_frontend_ops));
	state->frontend.demodulator_priv = state;
	वापस &state->frontend;

error:
	kमुक्त(state);
	वापस शून्य;
पूर्ण

अटल स्थिर काष्ठा dvb_frontend_ops sp887x_ops = अणु
	.delsys = अणु SYS_DVBT पूर्ण,
	.info = अणु
		.name = "Spase SP887x DVB-T",
		.frequency_min_hz =  50500 * kHz,
		.frequency_max_hz = 858000 * kHz,
		.frequency_stepsize_hz = 166666,
		.caps = FE_CAN_FEC_1_2 | FE_CAN_FEC_2_3 | FE_CAN_FEC_3_4 |
			FE_CAN_FEC_5_6 | FE_CAN_FEC_7_8 | FE_CAN_FEC_AUTO |
			FE_CAN_QPSK | FE_CAN_QAM_16 | FE_CAN_QAM_64 |
			FE_CAN_RECOVER
	पूर्ण,

	.release = sp887x_release,

	.init = sp887x_init,
	.sleep = sp887x_sleep,
	.i2c_gate_ctrl = sp887x_i2c_gate_ctrl,

	.set_frontend = sp887x_setup_frontend_parameters,
	.get_tune_settings = sp887x_get_tune_settings,

	.पढ़ो_status = sp887x_पढ़ो_status,
	.पढ़ो_ber = sp887x_पढ़ो_ber,
	.पढ़ो_संकेत_strength = sp887x_पढ़ो_संकेत_strength,
	.पढ़ो_snr = sp887x_पढ़ो_snr,
	.पढ़ो_ucblocks = sp887x_पढ़ो_ucblocks,
पूर्ण;

module_param(debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug, "Turn on/off frontend debugging (default:off).");

MODULE_DESCRIPTION("Spase sp887x DVB-T demodulator driver");
MODULE_LICENSE("GPL");

EXPORT_SYMBOL(sp887x_attach);
