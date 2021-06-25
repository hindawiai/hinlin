<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *    Support क्रम AltoBeam GB20600 (a.k.a DMB-TH) demodulator
 *    ATBM8830, ATBM8831
 *
 *    Copyright (C) 2009 David T.L. Wong <davidtlwong@gmail.com>
 */

#समावेश <यंत्र/भाग64.h>
#समावेश <media/dvb_frontend.h>

#समावेश "atbm8830.h"
#समावेश "atbm8830_priv.h"

#घोषणा dprपूर्णांकk(args...) \
	करो अणु \
		अगर (debug) \
			prपूर्णांकk(KERN_DEBUG "atbm8830: " args); \
	पूर्ण जबतक (0)

अटल पूर्णांक debug;

module_param(debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug, "Turn on/off frontend debugging (default:off).");

अटल पूर्णांक atbm8830_ग_लिखो_reg(काष्ठा atbm_state *priv, u16 reg, u8 data)
अणु
	पूर्णांक ret = 0;
	u8 dev_addr;
	u8 buf1[] = अणु reg >> 8, reg & 0xFF पूर्ण;
	u8 buf2[] = अणु data पूर्ण;
	काष्ठा i2c_msg msg1 = अणु .flags = 0, .buf = buf1, .len = 2 पूर्ण;
	काष्ठा i2c_msg msg2 = अणु .flags = 0, .buf = buf2, .len = 1 पूर्ण;

	dev_addr = priv->config->demod_address;
	msg1.addr = dev_addr;
	msg2.addr = dev_addr;

	अगर (debug >= 2)
		dprपूर्णांकk("%s: reg=0x%04X, data=0x%02X\n", __func__, reg, data);

	ret = i2c_transfer(priv->i2c, &msg1, 1);
	अगर (ret != 1)
		वापस -EIO;

	ret = i2c_transfer(priv->i2c, &msg2, 1);
	वापस (ret != 1) ? -EIO : 0;
पूर्ण

अटल पूर्णांक atbm8830_पढ़ो_reg(काष्ठा atbm_state *priv, u16 reg, u8 *p_data)
अणु
	पूर्णांक ret;
	u8 dev_addr;

	u8 buf1[] = अणु reg >> 8, reg & 0xFF पूर्ण;
	u8 buf2[] = अणु 0 पूर्ण;
	काष्ठा i2c_msg msg1 = अणु .flags = 0, .buf = buf1, .len = 2 पूर्ण;
	काष्ठा i2c_msg msg2 = अणु .flags = I2C_M_RD, .buf = buf2, .len = 1 पूर्ण;

	dev_addr = priv->config->demod_address;
	msg1.addr = dev_addr;
	msg2.addr = dev_addr;

	ret = i2c_transfer(priv->i2c, &msg1, 1);
	अगर (ret != 1) अणु
		dprपूर्णांकk("%s: error reg=0x%04x, ret=%i\n", __func__, reg, ret);
		वापस -EIO;
	पूर्ण

	ret = i2c_transfer(priv->i2c, &msg2, 1);
	अगर (ret != 1)
		वापस -EIO;

	*p_data = buf2[0];
	अगर (debug >= 2)
		dprपूर्णांकk("%s: reg=0x%04X, data=0x%02X\n",
			__func__, reg, buf2[0]);

	वापस 0;
पूर्ण

/* Lock रेजिस्टर latch so that multi-रेजिस्टर पढ़ो is atomic */
अटल अंतरभूत पूर्णांक atbm8830_reglatch_lock(काष्ठा atbm_state *priv, पूर्णांक lock)
अणु
	वापस atbm8830_ग_लिखो_reg(priv, REG_READ_LATCH, lock ? 1 : 0);
पूर्ण

अटल पूर्णांक set_osc_freq(काष्ठा atbm_state *priv, u32 freq /*in kHz*/)
अणु
	u32 val;
	u64 t;

	/* 0x100000 * freq / 30.4MHz */
	t = (u64)0x100000 * freq;
	करो_भाग(t, 30400);
	val = t;

	atbm8830_ग_लिखो_reg(priv, REG_OSC_CLK, val);
	atbm8830_ग_लिखो_reg(priv, REG_OSC_CLK + 1, val >> 8);
	atbm8830_ग_लिखो_reg(priv, REG_OSC_CLK + 2, val >> 16);

	वापस 0;
पूर्ण

अटल पूर्णांक set_अगर_freq(काष्ठा atbm_state *priv, u32 freq /*in kHz*/)
अणु

	u32 fs = priv->config->osc_clk_freq;
	u64 t;
	u32 val;
	u8 dat;

	अगर (freq != 0) अणु
		/* 2 * PI * (freq - fs) / fs * (2 ^ 22) */
		t = (u64) 2 * 31416 * (freq - fs);
		t <<= 22;
		करो_भाग(t, fs);
		करो_भाग(t, 1000);
		val = t;

		atbm8830_ग_लिखो_reg(priv, REG_TUNER_BASEBAND, 1);
		atbm8830_ग_लिखो_reg(priv, REG_IF_FREQ, val);
		atbm8830_ग_लिखो_reg(priv, REG_IF_FREQ+1, val >> 8);
		atbm8830_ग_लिखो_reg(priv, REG_IF_FREQ+2, val >> 16);

		atbm8830_पढ़ो_reg(priv, REG_ADC_CONFIG, &dat);
		dat &= 0xFC;
		atbm8830_ग_लिखो_reg(priv, REG_ADC_CONFIG, dat);
	पूर्ण अन्यथा अणु
		/* Zero IF */
		atbm8830_ग_लिखो_reg(priv, REG_TUNER_BASEBAND, 0);

		atbm8830_पढ़ो_reg(priv, REG_ADC_CONFIG, &dat);
		dat &= 0xFC;
		dat |= 0x02;
		atbm8830_ग_लिखो_reg(priv, REG_ADC_CONFIG, dat);

		अगर (priv->config->zअगर_swap_iq)
			atbm8830_ग_लिखो_reg(priv, REG_SWAP_I_Q, 0x03);
		अन्यथा
			atbm8830_ग_लिखो_reg(priv, REG_SWAP_I_Q, 0x01);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक is_locked(काष्ठा atbm_state *priv, u8 *locked)
अणु
	u8 status;

	atbm8830_पढ़ो_reg(priv, REG_LOCK_STATUS, &status);

	अगर (locked != शून्य)
		*locked = (status == 1);
	वापस 0;
पूर्ण

अटल पूर्णांक set_agc_config(काष्ठा atbm_state *priv,
	u8 min, u8 max, u8 hold_loop)
अणु
	/* no effect अगर both min and max are zero */
	अगर (!min && !max)
	    वापस 0;

	atbm8830_ग_लिखो_reg(priv, REG_AGC_MIN, min);
	atbm8830_ग_लिखो_reg(priv, REG_AGC_MAX, max);
	atbm8830_ग_लिखो_reg(priv, REG_AGC_HOLD_LOOP, hold_loop);

	वापस 0;
पूर्ण

अटल पूर्णांक set_अटल_channel_mode(काष्ठा atbm_state *priv)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 5; i++)
		atbm8830_ग_लिखो_reg(priv, 0x099B + i, 0x08);

	atbm8830_ग_लिखो_reg(priv, 0x095B, 0x7F);
	atbm8830_ग_लिखो_reg(priv, 0x09CB, 0x01);
	atbm8830_ग_लिखो_reg(priv, 0x09CC, 0x7F);
	atbm8830_ग_लिखो_reg(priv, 0x09CD, 0x7F);
	atbm8830_ग_लिखो_reg(priv, 0x0E01, 0x20);

	/* For single carrier */
	atbm8830_ग_लिखो_reg(priv, 0x0B03, 0x0A);
	atbm8830_ग_लिखो_reg(priv, 0x0935, 0x10);
	atbm8830_ग_लिखो_reg(priv, 0x0936, 0x08);
	atbm8830_ग_लिखो_reg(priv, 0x093E, 0x08);
	atbm8830_ग_लिखो_reg(priv, 0x096E, 0x06);

	/* frame_count_max0 */
	atbm8830_ग_लिखो_reg(priv, 0x0B09, 0x00);
	/* frame_count_max1 */
	atbm8830_ग_लिखो_reg(priv, 0x0B0A, 0x08);

	वापस 0;
पूर्ण

अटल पूर्णांक set_ts_config(काष्ठा atbm_state *priv)
अणु
	स्थिर काष्ठा atbm8830_config *cfg = priv->config;

	/*Set parallel/serial ts mode*/
	atbm8830_ग_लिखो_reg(priv, REG_TS_SERIAL, cfg->serial_ts ? 1 : 0);
	atbm8830_ग_लिखो_reg(priv, REG_TS_CLK_MODE, cfg->serial_ts ? 1 : 0);
	/*Set ts sampling edge*/
	atbm8830_ग_लिखो_reg(priv, REG_TS_SAMPLE_EDGE,
		cfg->ts_sampling_edge ? 1 : 0);
	/*Set ts घड़ी मुक्तrun*/
	atbm8830_ग_लिखो_reg(priv, REG_TS_CLK_FREERUN,
		cfg->ts_clk_gated ? 0 : 1);

	वापस 0;
पूर्ण

अटल पूर्णांक atbm8830_init(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा atbm_state *priv = fe->demodulator_priv;
	स्थिर काष्ठा atbm8830_config *cfg = priv->config;

	/*Set oscillator frequency*/
	set_osc_freq(priv, cfg->osc_clk_freq);

	/*Set IF frequency*/
	set_अगर_freq(priv, cfg->अगर_freq);

	/*Set AGC Config*/
	set_agc_config(priv, cfg->agc_min, cfg->agc_max,
		cfg->agc_hold_loop);

	/*Set अटल channel mode*/
	set_अटल_channel_mode(priv);

	set_ts_config(priv);
	/*Turn off DSP reset*/
	atbm8830_ग_लिखो_reg(priv, 0x000A, 0);

	/*SW version test*/
	atbm8830_ग_लिखो_reg(priv, 0x020C, 11);

	/* Run */
	atbm8830_ग_लिखो_reg(priv, REG_DEMOD_RUN, 1);

	वापस 0;
पूर्ण


अटल व्योम atbm8830_release(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा atbm_state *state = fe->demodulator_priv;
	dprपूर्णांकk("%s\n", __func__);

	kमुक्त(state);
पूर्ण

अटल पूर्णांक atbm8830_set_fe(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा atbm_state *priv = fe->demodulator_priv;
	पूर्णांक i;
	u8 locked = 0;
	dprपूर्णांकk("%s\n", __func__);

	/* set frequency */
	अगर (fe->ops.tuner_ops.set_params) अणु
		अगर (fe->ops.i2c_gate_ctrl)
			fe->ops.i2c_gate_ctrl(fe, 1);
		fe->ops.tuner_ops.set_params(fe);
		अगर (fe->ops.i2c_gate_ctrl)
			fe->ops.i2c_gate_ctrl(fe, 0);
	पूर्ण

	/* start स्वतः lock */
	क्रम (i = 0; i < 10; i++) अणु
		mdelay(100);
		dprपूर्णांकk("Try %d\n", i);
		is_locked(priv, &locked);
		अगर (locked != 0) अणु
			dprपूर्णांकk("ATBM8830 locked!\n");
			अवरोध;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक atbm8830_get_fe(काष्ठा dvb_frontend *fe,
			   काष्ठा dtv_frontend_properties *c)
अणु
	dprपूर्णांकk("%s\n", __func__);

	/* TODO: get real पढ़ोings from device */
	/* inversion status */
	c->inversion = INVERSION_OFF;

	/* bandwidth */
	c->bandwidth_hz = 8000000;

	c->code_rate_HP = FEC_AUTO;
	c->code_rate_LP = FEC_AUTO;

	c->modulation = QAM_AUTO;

	/* transmission mode */
	c->transmission_mode = TRANSMISSION_MODE_AUTO;

	/* guard पूर्णांकerval */
	c->guard_पूर्णांकerval = GUARD_INTERVAL_AUTO;

	/* hierarchy */
	c->hierarchy = HIERARCHY_NONE;

	वापस 0;
पूर्ण

अटल पूर्णांक atbm8830_get_tune_settings(काष्ठा dvb_frontend *fe,
	काष्ठा dvb_frontend_tune_settings *fesettings)
अणु
	fesettings->min_delay_ms = 0;
	fesettings->step_size = 0;
	fesettings->max_drअगरt = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक atbm8830_पढ़ो_status(काष्ठा dvb_frontend *fe,
				क्रमागत fe_status *fe_status)
अणु
	काष्ठा atbm_state *priv = fe->demodulator_priv;
	u8 locked = 0;
	u8 agc_locked = 0;

	dprपूर्णांकk("%s\n", __func__);
	*fe_status = 0;

	is_locked(priv, &locked);
	अगर (locked) अणु
		*fe_status |= FE_HAS_SIGNAL | FE_HAS_CARRIER |
			FE_HAS_VITERBI | FE_HAS_SYNC | FE_HAS_LOCK;
	पूर्ण
	dprपूर्णांकk("%s: fe_status=0x%x\n", __func__, *fe_status);

	atbm8830_पढ़ो_reg(priv, REG_AGC_LOCK, &agc_locked);
	dprपूर्णांकk("AGC Lock: %d\n", agc_locked);

	वापस 0;
पूर्ण

अटल पूर्णांक atbm8830_पढ़ो_ber(काष्ठा dvb_frontend *fe, u32 *ber)
अणु
	काष्ठा atbm_state *priv = fe->demodulator_priv;
	u32 frame_err;
	u8 t;

	dprपूर्णांकk("%s\n", __func__);

	atbm8830_reglatch_lock(priv, 1);

	atbm8830_पढ़ो_reg(priv, REG_FRAME_ERR_CNT + 1, &t);
	frame_err = t & 0x7F;
	frame_err <<= 8;
	atbm8830_पढ़ो_reg(priv, REG_FRAME_ERR_CNT, &t);
	frame_err |= t;

	atbm8830_reglatch_lock(priv, 0);

	*ber = frame_err * 100 / 32767;

	dprपूर्णांकk("%s: ber=0x%x\n", __func__, *ber);
	वापस 0;
पूर्ण

अटल पूर्णांक atbm8830_पढ़ो_संकेत_strength(काष्ठा dvb_frontend *fe, u16 *संकेत)
अणु
	काष्ठा atbm_state *priv = fe->demodulator_priv;
	u32 pwm;
	u8 t;

	dprपूर्णांकk("%s\n", __func__);
	atbm8830_reglatch_lock(priv, 1);

	atbm8830_पढ़ो_reg(priv, REG_AGC_PWM_VAL + 1, &t);
	pwm = t & 0x03;
	pwm <<= 8;
	atbm8830_पढ़ो_reg(priv, REG_AGC_PWM_VAL, &t);
	pwm |= t;

	atbm8830_reglatch_lock(priv, 0);

	dprपूर्णांकk("AGC PWM = 0x%02X\n", pwm);
	pwm = 0x400 - pwm;

	*संकेत = pwm * 0x10000 / 0x400;

	वापस 0;
पूर्ण

अटल पूर्णांक atbm8830_पढ़ो_snr(काष्ठा dvb_frontend *fe, u16 *snr)
अणु
	dprपूर्णांकk("%s\n", __func__);
	*snr = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक atbm8830_पढ़ो_ucblocks(काष्ठा dvb_frontend *fe, u32 *ucblocks)
अणु
	dprपूर्णांकk("%s\n", __func__);
	*ucblocks = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक atbm8830_i2c_gate_ctrl(काष्ठा dvb_frontend *fe, पूर्णांक enable)
अणु
	काष्ठा atbm_state *priv = fe->demodulator_priv;

	वापस atbm8830_ग_लिखो_reg(priv, REG_I2C_GATE, enable ? 1 : 0);
पूर्ण

अटल स्थिर काष्ठा dvb_frontend_ops atbm8830_ops = अणु
	.delsys = अणु SYS_DTMB पूर्ण,
	.info = अणु
		.name = "AltoBeam ATBM8830/8831 DMB-TH",
		.frequency_min_hz = 474 * MHz,
		.frequency_max_hz = 858 * MHz,
		.frequency_stepsize_hz = 10 * kHz,
		.caps =
			FE_CAN_FEC_AUTO |
			FE_CAN_QAM_AUTO |
			FE_CAN_TRANSMISSION_MODE_AUTO |
			FE_CAN_GUARD_INTERVAL_AUTO
	पूर्ण,

	.release = atbm8830_release,

	.init = atbm8830_init,
	.sleep = शून्य,
	.ग_लिखो = शून्य,
	.i2c_gate_ctrl = atbm8830_i2c_gate_ctrl,

	.set_frontend = atbm8830_set_fe,
	.get_frontend = atbm8830_get_fe,
	.get_tune_settings = atbm8830_get_tune_settings,

	.पढ़ो_status = atbm8830_पढ़ो_status,
	.पढ़ो_ber = atbm8830_पढ़ो_ber,
	.पढ़ो_संकेत_strength = atbm8830_पढ़ो_संकेत_strength,
	.पढ़ो_snr = atbm8830_पढ़ो_snr,
	.पढ़ो_ucblocks = atbm8830_पढ़ो_ucblocks,
पूर्ण;

काष्ठा dvb_frontend *atbm8830_attach(स्थिर काष्ठा atbm8830_config *config,
	काष्ठा i2c_adapter *i2c)
अणु
	काष्ठा atbm_state *priv = शून्य;
	u8 data = 0;

	dprपूर्णांकk("%s()\n", __func__);

	अगर (config == शून्य || i2c == शून्य)
		वापस शून्य;

	priv = kzalloc(माप(काष्ठा atbm_state), GFP_KERNEL);
	अगर (priv == शून्य)
		जाओ error_out;

	priv->config = config;
	priv->i2c = i2c;

	/* check अगर the demod is there */
	अगर (atbm8830_पढ़ो_reg(priv, REG_CHIP_ID, &data) != 0) अणु
		dprपूर्णांकk("%s atbm8830/8831 not found at i2c addr 0x%02X\n",
			__func__, priv->config->demod_address);
		जाओ error_out;
	पूर्ण
	dprपूर्णांकk("atbm8830 chip id: 0x%02X\n", data);

	स_नकल(&priv->frontend.ops, &atbm8830_ops,
	       माप(काष्ठा dvb_frontend_ops));
	priv->frontend.demodulator_priv = priv;

	atbm8830_init(&priv->frontend);

	atbm8830_i2c_gate_ctrl(&priv->frontend, 1);

	वापस &priv->frontend;

error_out:
	dprपूर्णांकk("%s() error_out\n", __func__);
	kमुक्त(priv);
	वापस शून्य;

पूर्ण
EXPORT_SYMBOL(atbm8830_attach);

MODULE_DESCRIPTION("AltoBeam ATBM8830/8831 GB20600 demodulator driver");
MODULE_AUTHOR("David T. L. Wong <davidtlwong@gmail.com>");
MODULE_LICENSE("GPL");
