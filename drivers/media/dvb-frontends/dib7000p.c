<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Linux-DVB Driver क्रम DiBcom's second generation DiB7000P (PC).
 *
 * Copyright (C) 2005-7 DiBcom (http://www.dibcom.fr/)
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/i2c.h>
#समावेश <linux/mutex.h>
#समावेश <यंत्र/भाग64.h>

#समावेश <media/dvb_गणित.स>
#समावेश <media/dvb_frontend.h>

#समावेश "dib7000p.h"

अटल पूर्णांक debug;
module_param(debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug, "turn on debugging (default: 0)");

अटल पूर्णांक buggy_sfn_workaround;
module_param(buggy_sfn_workaround, पूर्णांक, 0644);
MODULE_PARM_DESC(buggy_sfn_workaround, "Enable work-around for buggy SFNs (default: 0)");

#घोषणा dprपूर्णांकk(fmt, arg...) करो अणु					\
	अगर (debug)							\
		prपूर्णांकk(KERN_DEBUG pr_fmt("%s: " fmt),			\
		       __func__, ##arg);				\
पूर्ण जबतक (0)

काष्ठा i2c_device अणु
	काष्ठा i2c_adapter *i2c_adap;
	u8 i2c_addr;
पूर्ण;

काष्ठा dib7000p_state अणु
	काष्ठा dvb_frontend demod;
	काष्ठा dib7000p_config cfg;

	u8 i2c_addr;
	काष्ठा i2c_adapter *i2c_adap;

	काष्ठा dibx000_i2c_master i2c_master;

	u16 wbd_ref;

	u8 current_band;
	u32 current_bandwidth;
	काष्ठा dibx000_agc_config *current_agc;
	u32 timf;

	u8 भाग_क्रमce_off:1;
	u8 भाग_state:1;
	u16 भाग_sync_रुको;

	u8 agc_state;

	u16 gpio_dir;
	u16 gpio_val;

	u8 sfn_workaround_active:1;

#घोषणा SOC7090 0x7090
	u16 version;

	u16 tuner_enable;
	काष्ठा i2c_adapter dib7090_tuner_adap;

	/* क्रम the I2C transfer */
	काष्ठा i2c_msg msg[2];
	u8 i2c_ग_लिखो_buffer[4];
	u8 i2c_पढ़ो_buffer[2];
	काष्ठा mutex i2c_buffer_lock;

	u8 input_mode_mpeg;

	/* क्रम DVBv5 stats */
	s64 old_ucb;
	अचिन्हित दीर्घ per_jअगरfies_stats;
	अचिन्हित दीर्घ ber_jअगरfies_stats;
	अचिन्हित दीर्घ get_stats_समय;
पूर्ण;

क्रमागत dib7000p_घातer_mode अणु
	DIB7000P_POWER_ALL = 0,
	DIB7000P_POWER_ANALOG_ADC,
	DIB7000P_POWER_INTERFACE_ONLY,
पूर्ण;

/* dib7090 specअगरic functions */
अटल पूर्णांक dib7090_set_output_mode(काष्ठा dvb_frontend *fe, पूर्णांक mode);
अटल पूर्णांक dib7090_set_भागersity_in(काष्ठा dvb_frontend *fe, पूर्णांक onoff);
अटल व्योम dib7090_setDibTxMux(काष्ठा dib7000p_state *state, पूर्णांक mode);
अटल व्योम dib7090_setHostBusMux(काष्ठा dib7000p_state *state, पूर्णांक mode);

अटल u16 dib7000p_पढ़ो_word(काष्ठा dib7000p_state *state, u16 reg)
अणु
	u16 ret;

	अगर (mutex_lock_पूर्णांकerruptible(&state->i2c_buffer_lock) < 0) अणु
		dprपूर्णांकk("could not acquire lock\n");
		वापस 0;
	पूर्ण

	state->i2c_ग_लिखो_buffer[0] = reg >> 8;
	state->i2c_ग_लिखो_buffer[1] = reg & 0xff;

	स_रखो(state->msg, 0, 2 * माप(काष्ठा i2c_msg));
	state->msg[0].addr = state->i2c_addr >> 1;
	state->msg[0].flags = 0;
	state->msg[0].buf = state->i2c_ग_लिखो_buffer;
	state->msg[0].len = 2;
	state->msg[1].addr = state->i2c_addr >> 1;
	state->msg[1].flags = I2C_M_RD;
	state->msg[1].buf = state->i2c_पढ़ो_buffer;
	state->msg[1].len = 2;

	अगर (i2c_transfer(state->i2c_adap, state->msg, 2) != 2)
		dprपूर्णांकk("i2c read error on %d\n", reg);

	ret = (state->i2c_पढ़ो_buffer[0] << 8) | state->i2c_पढ़ो_buffer[1];
	mutex_unlock(&state->i2c_buffer_lock);
	वापस ret;
पूर्ण

अटल पूर्णांक dib7000p_ग_लिखो_word(काष्ठा dib7000p_state *state, u16 reg, u16 val)
अणु
	पूर्णांक ret;

	अगर (mutex_lock_पूर्णांकerruptible(&state->i2c_buffer_lock) < 0) अणु
		dprपूर्णांकk("could not acquire lock\n");
		वापस -EINVAL;
	पूर्ण

	state->i2c_ग_लिखो_buffer[0] = (reg >> 8) & 0xff;
	state->i2c_ग_लिखो_buffer[1] = reg & 0xff;
	state->i2c_ग_लिखो_buffer[2] = (val >> 8) & 0xff;
	state->i2c_ग_लिखो_buffer[3] = val & 0xff;

	स_रखो(&state->msg[0], 0, माप(काष्ठा i2c_msg));
	state->msg[0].addr = state->i2c_addr >> 1;
	state->msg[0].flags = 0;
	state->msg[0].buf = state->i2c_ग_लिखो_buffer;
	state->msg[0].len = 4;

	ret = (i2c_transfer(state->i2c_adap, state->msg, 1) != 1 ?
			-EREMOTEIO : 0);
	mutex_unlock(&state->i2c_buffer_lock);
	वापस ret;
पूर्ण

अटल व्योम dib7000p_ग_लिखो_tab(काष्ठा dib7000p_state *state, u16 * buf)
अणु
	u16 l = 0, r, *n;
	n = buf;
	l = *n++;
	जबतक (l) अणु
		r = *n++;

		करो अणु
			dib7000p_ग_लिखो_word(state, r, *n++);
			r++;
		पूर्ण जबतक (--l);
		l = *n++;
	पूर्ण
पूर्ण

अटल पूर्णांक dib7000p_set_output_mode(काष्ठा dib7000p_state *state, पूर्णांक mode)
अणु
	पूर्णांक ret = 0;
	u16 outreg, fअगरo_threshold, smo_mode;

	outreg = 0;
	fअगरo_threshold = 1792;
	smo_mode = (dib7000p_पढ़ो_word(state, 235) & 0x0050) | (1 << 1);

	dprपूर्णांकk("setting output mode for demod %p to %d\n", &state->demod, mode);

	चयन (mode) अणु
	हाल OUTMODE_MPEG2_PAR_GATED_CLK:
		outreg = (1 << 10);	/* 0x0400 */
		अवरोध;
	हाल OUTMODE_MPEG2_PAR_CONT_CLK:
		outreg = (1 << 10) | (1 << 6);	/* 0x0440 */
		अवरोध;
	हाल OUTMODE_MPEG2_SERIAL:
		outreg = (1 << 10) | (2 << 6) | (0 << 1);	/* 0x0480 */
		अवरोध;
	हाल OUTMODE_DIVERSITY:
		अगर (state->cfg.hostbus_भागersity)
			outreg = (1 << 10) | (4 << 6);	/* 0x0500 */
		अन्यथा
			outreg = (1 << 11);
		अवरोध;
	हाल OUTMODE_MPEG2_FIFO:
		smo_mode |= (3 << 1);
		fअगरo_threshold = 512;
		outreg = (1 << 10) | (5 << 6);
		अवरोध;
	हाल OUTMODE_ANALOG_ADC:
		outreg = (1 << 10) | (3 << 6);
		अवरोध;
	हाल OUTMODE_HIGH_Z:
		outreg = 0;
		अवरोध;
	शेष:
		dprपूर्णांकk("Unhandled output_mode passed to be set for demod %p\n", &state->demod);
		अवरोध;
	पूर्ण

	अगर (state->cfg.output_mpeg2_in_188_bytes)
		smo_mode |= (1 << 5);

	ret |= dib7000p_ग_लिखो_word(state, 235, smo_mode);
	ret |= dib7000p_ग_लिखो_word(state, 236, fअगरo_threshold);	/* synchronous ख_पढ़ो */
	अगर (state->version != SOC7090)
		ret |= dib7000p_ग_लिखो_word(state, 1286, outreg);	/* P_Div_active */

	वापस ret;
पूर्ण

अटल पूर्णांक dib7000p_set_भागersity_in(काष्ठा dvb_frontend *demod, पूर्णांक onoff)
अणु
	काष्ठा dib7000p_state *state = demod->demodulator_priv;

	अगर (state->भाग_क्रमce_off) अणु
		dprपूर्णांकk("diversity combination deactivated - forced by COFDM parameters\n");
		onoff = 0;
		dib7000p_ग_लिखो_word(state, 207, 0);
	पूर्ण अन्यथा
		dib7000p_ग_लिखो_word(state, 207, (state->भाग_sync_रुको << 4) | (1 << 2) | (2 << 0));

	state->भाग_state = (u8) onoff;

	अगर (onoff) अणु
		dib7000p_ग_लिखो_word(state, 204, 6);
		dib7000p_ग_लिखो_word(state, 205, 16);
		/* P_dvsy_sync_mode = 0, P_dvsy_sync_enable=1, P_dvcb_comb_mode=2 */
	पूर्ण अन्यथा अणु
		dib7000p_ग_लिखो_word(state, 204, 1);
		dib7000p_ग_लिखो_word(state, 205, 0);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक dib7000p_set_घातer_mode(काष्ठा dib7000p_state *state, क्रमागत dib7000p_घातer_mode mode)
अणु
	/* by शेष everything is घातered off */
	u16 reg_774 = 0x3fff, reg_775 = 0xffff, reg_776 = 0x0007, reg_899 = 0x0003, reg_1280 = (0xfe00) | (dib7000p_पढ़ो_word(state, 1280) & 0x01ff);

	/* now, depending on the requested mode, we घातer on */
	चयन (mode) अणु
		/* घातer up everything in the demod */
	हाल DIB7000P_POWER_ALL:
		reg_774 = 0x0000;
		reg_775 = 0x0000;
		reg_776 = 0x0;
		reg_899 = 0x0;
		अगर (state->version == SOC7090)
			reg_1280 &= 0x001f;
		अन्यथा
			reg_1280 &= 0x01ff;
		अवरोध;

	हाल DIB7000P_POWER_ANALOG_ADC:
		/* dem, cfg, iqc, sad, agc */
		reg_774 &= ~((1 << 15) | (1 << 14) | (1 << 11) | (1 << 10) | (1 << 9));
		/* nud */
		reg_776 &= ~((1 << 0));
		/* Dout */
		अगर (state->version != SOC7090)
			reg_1280 &= ~((1 << 11));
		reg_1280 &= ~(1 << 6);
		fallthrough;
	हाल DIB7000P_POWER_INTERFACE_ONLY:
		/* just leave घातer on the control-पूर्णांकerfaces: GPIO and (I2C or SDIO) */
		/* TODO घातer up either SDIO or I2C */
		अगर (state->version == SOC7090)
			reg_1280 &= ~((1 << 7) | (1 << 5));
		अन्यथा
			reg_1280 &= ~((1 << 14) | (1 << 13) | (1 << 12) | (1 << 10));
		अवरोध;

/* TODO following stuff is just converted from the dib7000-driver - check when is used what */
	पूर्ण

	dib7000p_ग_लिखो_word(state, 774, reg_774);
	dib7000p_ग_लिखो_word(state, 775, reg_775);
	dib7000p_ग_लिखो_word(state, 776, reg_776);
	dib7000p_ग_लिखो_word(state, 1280, reg_1280);
	अगर (state->version != SOC7090)
		dib7000p_ग_लिखो_word(state, 899, reg_899);

	वापस 0;
पूर्ण

अटल व्योम dib7000p_set_adc_state(काष्ठा dib7000p_state *state, क्रमागत dibx000_adc_states no)
अणु
	u16 reg_908 = 0, reg_909 = 0;
	u16 reg;

	अगर (state->version != SOC7090) अणु
		reg_908 = dib7000p_पढ़ो_word(state, 908);
		reg_909 = dib7000p_पढ़ो_word(state, 909);
	पूर्ण

	चयन (no) अणु
	हाल DIBX000_SLOW_ADC_ON:
		अगर (state->version == SOC7090) अणु
			reg = dib7000p_पढ़ो_word(state, 1925);

			dib7000p_ग_लिखो_word(state, 1925, reg | (1 << 4) | (1 << 2));	/* en_slowAdc = 1 & reset_sladc = 1 */

			reg = dib7000p_पढ़ो_word(state, 1925);	/* पढ़ो access to make it works... strange ... */
			msleep(200);
			dib7000p_ग_लिखो_word(state, 1925, reg & ~(1 << 4));	/* en_slowAdc = 1 & reset_sladc = 0 */

			reg = dib7000p_पढ़ो_word(state, 72) & ~((0x3 << 14) | (0x3 << 12));
			dib7000p_ग_लिखो_word(state, 72, reg | (1 << 14) | (3 << 12) | 524);	/* ref = Vin1 => Vbg ; sel = Vin0 or Vin3 ; (Vin2 = Vcm) */
		पूर्ण अन्यथा अणु
			reg_909 |= (1 << 1) | (1 << 0);
			dib7000p_ग_लिखो_word(state, 909, reg_909);
			reg_909 &= ~(1 << 1);
		पूर्ण
		अवरोध;

	हाल DIBX000_SLOW_ADC_OFF:
		अगर (state->version == SOC7090) अणु
			reg = dib7000p_पढ़ो_word(state, 1925);
			dib7000p_ग_लिखो_word(state, 1925, (reg & ~(1 << 2)) | (1 << 4));	/* reset_sladc = 1 en_slowAdc = 0 */
		पूर्ण अन्यथा
			reg_909 |= (1 << 1) | (1 << 0);
		अवरोध;

	हाल DIBX000_ADC_ON:
		reg_908 &= 0x0fff;
		reg_909 &= 0x0003;
		अवरोध;

	हाल DIBX000_ADC_OFF:
		reg_908 |= (1 << 14) | (1 << 13) | (1 << 12);
		reg_909 |= (1 << 5) | (1 << 4) | (1 << 3) | (1 << 2);
		अवरोध;

	हाल DIBX000_VBG_ENABLE:
		reg_908 &= ~(1 << 15);
		अवरोध;

	हाल DIBX000_VBG_DISABLE:
		reg_908 |= (1 << 15);
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

//	dprपूर्णांकk( "908: %x, 909: %x\n", reg_908, reg_909);

	reg_909 |= (state->cfg.disable_sample_and_hold & 1) << 4;
	reg_908 |= (state->cfg.enable_current_mirror & 1) << 7;

	अगर (state->version != SOC7090) अणु
		dib7000p_ग_लिखो_word(state, 908, reg_908);
		dib7000p_ग_लिखो_word(state, 909, reg_909);
	पूर्ण
पूर्ण

अटल पूर्णांक dib7000p_set_bandwidth(काष्ठा dib7000p_state *state, u32 bw)
अणु
	u32 timf;

	// store the current bandwidth क्रम later use
	state->current_bandwidth = bw;

	अगर (state->timf == 0) अणु
		dprपूर्णांकk("using default timf\n");
		timf = state->cfg.bw->timf;
	पूर्ण अन्यथा अणु
		dprपूर्णांकk("using updated timf\n");
		timf = state->timf;
	पूर्ण

	timf = timf * (bw / 50) / 160;

	dib7000p_ग_लिखो_word(state, 23, (u16) ((timf >> 16) & 0xffff));
	dib7000p_ग_लिखो_word(state, 24, (u16) ((timf) & 0xffff));

	वापस 0;
पूर्ण

अटल पूर्णांक dib7000p_sad_calib(काष्ठा dib7000p_state *state)
अणु
/* पूर्णांकernal */
	dib7000p_ग_लिखो_word(state, 73, (0 << 1) | (0 << 0));

	अगर (state->version == SOC7090)
		dib7000p_ग_लिखो_word(state, 74, 2048);
	अन्यथा
		dib7000p_ग_लिखो_word(state, 74, 776);

	/* करो the calibration */
	dib7000p_ग_लिखो_word(state, 73, (1 << 0));
	dib7000p_ग_लिखो_word(state, 73, (0 << 0));

	msleep(1);

	वापस 0;
पूर्ण

अटल पूर्णांक dib7000p_set_wbd_ref(काष्ठा dvb_frontend *demod, u16 value)
अणु
	काष्ठा dib7000p_state *state = demod->demodulator_priv;
	अगर (value > 4095)
		value = 4095;
	state->wbd_ref = value;
	वापस dib7000p_ग_लिखो_word(state, 105, (dib7000p_पढ़ो_word(state, 105) & 0xf000) | value);
पूर्ण

अटल पूर्णांक dib7000p_get_agc_values(काष्ठा dvb_frontend *fe,
		u16 *agc_global, u16 *agc1, u16 *agc2, u16 *wbd)
अणु
	काष्ठा dib7000p_state *state = fe->demodulator_priv;

	अगर (agc_global != शून्य)
		*agc_global = dib7000p_पढ़ो_word(state, 394);
	अगर (agc1 != शून्य)
		*agc1 = dib7000p_पढ़ो_word(state, 392);
	अगर (agc2 != शून्य)
		*agc2 = dib7000p_पढ़ो_word(state, 393);
	अगर (wbd != शून्य)
		*wbd = dib7000p_पढ़ो_word(state, 397);

	वापस 0;
पूर्ण

अटल पूर्णांक dib7000p_set_agc1_min(काष्ठा dvb_frontend *fe, u16 v)
अणु
	काष्ठा dib7000p_state *state = fe->demodulator_priv;
	वापस dib7000p_ग_लिखो_word(state, 108,  v);
पूर्ण

अटल व्योम dib7000p_reset_pll(काष्ठा dib7000p_state *state)
अणु
	काष्ठा dibx000_bandwidth_config *bw = &state->cfg.bw[0];
	u16 clk_cfg0;

	अगर (state->version == SOC7090) अणु
		dib7000p_ग_लिखो_word(state, 1856, (!bw->pll_reset << 13) | (bw->pll_range << 12) | (bw->pll_ratio << 6) | (bw->pll_preभाग));

		जबतक (((dib7000p_पढ़ो_word(state, 1856) >> 15) & 0x1) != 1)
			;

		dib7000p_ग_लिखो_word(state, 1857, dib7000p_पढ़ो_word(state, 1857) | (!bw->pll_bypass << 15));
	पूर्ण अन्यथा अणु
		/* क्रमce PLL bypass */
		clk_cfg0 = (1 << 15) | ((bw->pll_ratio & 0x3f) << 9) |
			(bw->modulo << 7) | (bw->ADClkSrc << 6) | (bw->IO_CLK_en_core << 5) | (bw->bypclk_भाग << 2) | (bw->enable_refभाग << 1) | (0 << 0);

		dib7000p_ग_लिखो_word(state, 900, clk_cfg0);

		/* P_pll_cfg */
		dib7000p_ग_लिखो_word(state, 903, (bw->pll_preभाग << 5) | (((bw->pll_ratio >> 6) & 0x3) << 3) | (bw->pll_range << 1) | bw->pll_reset);
		clk_cfg0 = (bw->pll_bypass << 15) | (clk_cfg0 & 0x7fff);
		dib7000p_ग_लिखो_word(state, 900, clk_cfg0);
	पूर्ण

	dib7000p_ग_लिखो_word(state, 18, (u16) (((bw->पूर्णांकernal * 1000) >> 16) & 0xffff));
	dib7000p_ग_लिखो_word(state, 19, (u16) ((bw->पूर्णांकernal * 1000) & 0xffff));
	dib7000p_ग_लिखो_word(state, 21, (u16) ((bw->अगरreq >> 16) & 0xffff));
	dib7000p_ग_लिखो_word(state, 22, (u16) ((bw->अगरreq) & 0xffff));

	dib7000p_ग_लिखो_word(state, 72, bw->sad_cfg);
पूर्ण

अटल u32 dib7000p_get_पूर्णांकernal_freq(काष्ठा dib7000p_state *state)
अणु
	u32 पूर्णांकernal = (u32) dib7000p_पढ़ो_word(state, 18) << 16;
	पूर्णांकernal |= (u32) dib7000p_पढ़ो_word(state, 19);
	पूर्णांकernal /= 1000;

	वापस पूर्णांकernal;
पूर्ण

अटल पूर्णांक dib7000p_update_pll(काष्ठा dvb_frontend *fe, काष्ठा dibx000_bandwidth_config *bw)
अणु
	काष्ठा dib7000p_state *state = fe->demodulator_priv;
	u16 reg_1857, reg_1856 = dib7000p_पढ़ो_word(state, 1856);
	u8 loopभाग, preभाग;
	u32 पूर्णांकernal, xtal;

	/* get back old values */
	preभाग = reg_1856 & 0x3f;
	loopभाग = (reg_1856 >> 6) & 0x3f;

	अगर ((bw != शून्य) && (bw->pll_preभाग != preभाग || bw->pll_ratio != loopभाग)) अणु
		dprपूर्णांकk("Updating pll (prediv: old =  %d new = %d ; loopdiv : old = %d new = %d)\n", preभाग, bw->pll_preभाग, loopभाग, bw->pll_ratio);
		reg_1856 &= 0xf000;
		reg_1857 = dib7000p_पढ़ो_word(state, 1857);
		dib7000p_ग_लिखो_word(state, 1857, reg_1857 & ~(1 << 15));

		dib7000p_ग_लिखो_word(state, 1856, reg_1856 | ((bw->pll_ratio & 0x3f) << 6) | (bw->pll_preभाग & 0x3f));

		/* ग_लिखो new प्रणाली clk पूर्णांकo P_sec_len */
		पूर्णांकernal = dib7000p_get_पूर्णांकernal_freq(state);
		xtal = (पूर्णांकernal / loopभाग) * preभाग;
		पूर्णांकernal = 1000 * (xtal / bw->pll_preभाग) * bw->pll_ratio;	/* new पूर्णांकernal */
		dib7000p_ग_लिखो_word(state, 18, (u16) ((पूर्णांकernal >> 16) & 0xffff));
		dib7000p_ग_लिखो_word(state, 19, (u16) (पूर्णांकernal & 0xffff));

		dib7000p_ग_लिखो_word(state, 1857, reg_1857 | (1 << 15));

		जबतक (((dib7000p_पढ़ो_word(state, 1856) >> 15) & 0x1) != 1)
			dprपूर्णांकk("Waiting for PLL to lock\n");

		वापस 0;
	पूर्ण
	वापस -EIO;
पूर्ण

अटल पूर्णांक dib7000p_reset_gpio(काष्ठा dib7000p_state *st)
अणु
	/* reset the GPIOs */
	dprपूर्णांकk("gpio dir: %x: val: %x, pwm_pos: %x\n", st->gpio_dir, st->gpio_val, st->cfg.gpio_pwm_pos);

	dib7000p_ग_लिखो_word(st, 1029, st->gpio_dir);
	dib7000p_ग_लिखो_word(st, 1030, st->gpio_val);

	/* TODO 1031 is P_gpio_od */

	dib7000p_ग_लिखो_word(st, 1032, st->cfg.gpio_pwm_pos);

	dib7000p_ग_लिखो_word(st, 1037, st->cfg.pwm_freq_भाग);
	वापस 0;
पूर्ण

अटल पूर्णांक dib7000p_cfg_gpio(काष्ठा dib7000p_state *st, u8 num, u8 dir, u8 val)
अणु
	st->gpio_dir = dib7000p_पढ़ो_word(st, 1029);
	st->gpio_dir &= ~(1 << num);	/* reset the direction bit */
	st->gpio_dir |= (dir & 0x1) << num;	/* set the new direction */
	dib7000p_ग_लिखो_word(st, 1029, st->gpio_dir);

	st->gpio_val = dib7000p_पढ़ो_word(st, 1030);
	st->gpio_val &= ~(1 << num);	/* reset the direction bit */
	st->gpio_val |= (val & 0x01) << num;	/* set the new value */
	dib7000p_ग_लिखो_word(st, 1030, st->gpio_val);

	वापस 0;
पूर्ण

अटल पूर्णांक dib7000p_set_gpio(काष्ठा dvb_frontend *demod, u8 num, u8 dir, u8 val)
अणु
	काष्ठा dib7000p_state *state = demod->demodulator_priv;
	वापस dib7000p_cfg_gpio(state, num, dir, val);
पूर्ण

अटल u16 dib7000p_शेषs[] = अणु
	// स्वतः search configuration
	3, 2,
	0x0004,
	(1<<3)|(1<<11)|(1<<12)|(1<<13),
	0x0814,			/* Equal Lock */

	12, 6,
	0x001b,
	0x7740,
	0x005b,
	0x8d80,
	0x01c9,
	0xc380,
	0x0000,
	0x0080,
	0x0000,
	0x0090,
	0x0001,
	0xd4c0,

	1, 26,
	0x6680,

	/* set ADC level to -16 */
	11, 79,
	(1 << 13) - 825 - 117,
	(1 << 13) - 837 - 117,
	(1 << 13) - 811 - 117,
	(1 << 13) - 766 - 117,
	(1 << 13) - 737 - 117,
	(1 << 13) - 693 - 117,
	(1 << 13) - 648 - 117,
	(1 << 13) - 619 - 117,
	(1 << 13) - 575 - 117,
	(1 << 13) - 531 - 117,
	(1 << 13) - 501 - 117,

	1, 142,
	0x0410,

	/* disable घातer smoothing */
	8, 145,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,

	1, 154,
	1 << 13,

	1, 168,
	0x0ccd,

	1, 183,
	0x200f,

	1, 212,
		0x169,

	5, 187,
	0x023d,
	0x00a4,
	0x00a4,
	0x7ff0,
	0x3ccc,

	1, 198,
	0x800,

	1, 222,
	0x0010,

	1, 235,
	0x0062,

	0,
पूर्ण;

अटल व्योम dib7000p_reset_stats(काष्ठा dvb_frontend *fe);

अटल पूर्णांक dib7000p_demod_reset(काष्ठा dib7000p_state *state)
अणु
	dib7000p_set_घातer_mode(state, DIB7000P_POWER_ALL);

	अगर (state->version == SOC7090)
		dibx000_reset_i2c_master(&state->i2c_master);

	dib7000p_set_adc_state(state, DIBX000_VBG_ENABLE);

	/* restart all parts */
	dib7000p_ग_लिखो_word(state, 770, 0xffff);
	dib7000p_ग_लिखो_word(state, 771, 0xffff);
	dib7000p_ग_लिखो_word(state, 772, 0x001f);
	dib7000p_ग_लिखो_word(state, 1280, 0x001f - ((1 << 4) | (1 << 3)));

	dib7000p_ग_लिखो_word(state, 770, 0);
	dib7000p_ग_लिखो_word(state, 771, 0);
	dib7000p_ग_लिखो_word(state, 772, 0);
	dib7000p_ग_लिखो_word(state, 1280, 0);

	अगर (state->version != SOC7090) अणु
		dib7000p_ग_लिखो_word(state,  898, 0x0003);
		dib7000p_ग_लिखो_word(state,  898, 0);
	पूर्ण

	/* शेष */
	dib7000p_reset_pll(state);

	अगर (dib7000p_reset_gpio(state) != 0)
		dprपूर्णांकk("GPIO reset was not successful.\n");

	अगर (state->version == SOC7090) अणु
		dib7000p_ग_लिखो_word(state, 899, 0);

		/* impulse noise */
		dib7000p_ग_लिखो_word(state, 42, (1<<5) | 3); /* P_iqc_thsat_ipc = 1 ; P_iqc_win2 = 3 */
		dib7000p_ग_लिखो_word(state, 43, 0x2d4); /*-300 fag P_iqc_dect_min = -280 */
		dib7000p_ग_लिखो_word(state, 44, 300); /* 300 fag P_iqc_dect_min = +280 */
		dib7000p_ग_लिखो_word(state, 273, (0<<6) | 30);
	पूर्ण
	अगर (dib7000p_set_output_mode(state, OUTMODE_HIGH_Z) != 0)
		dprपूर्णांकk("OUTPUT_MODE could not be reset.\n");

	dib7000p_set_adc_state(state, DIBX000_SLOW_ADC_ON);
	dib7000p_sad_calib(state);
	dib7000p_set_adc_state(state, DIBX000_SLOW_ADC_OFF);

	/* unक्रमce भागstr regardless whether i2c क्रमागतeration was करोne or not */
	dib7000p_ग_लिखो_word(state, 1285, dib7000p_पढ़ो_word(state, 1285) & ~(1 << 1));

	dib7000p_set_bandwidth(state, 8000);

	अगर (state->version == SOC7090) अणु
		dib7000p_ग_लिखो_word(state, 36, 0x0755);/* P_iqc_impnc_on =1 & P_iqc_corr_inh = 1 क्रम impulsive noise */
	पूर्ण अन्यथा अणु
		अगर (state->cfg.tuner_is_baseband)
			dib7000p_ग_लिखो_word(state, 36, 0x0755);
		अन्यथा
			dib7000p_ग_लिखो_word(state, 36, 0x1f55);
	पूर्ण

	dib7000p_ग_लिखो_tab(state, dib7000p_शेषs);
	अगर (state->version != SOC7090) अणु
		dib7000p_ग_लिखो_word(state, 901, 0x0006);
		dib7000p_ग_लिखो_word(state, 902, (3 << 10) | (1 << 6));
		dib7000p_ग_लिखो_word(state, 905, 0x2c8e);
	पूर्ण

	dib7000p_set_घातer_mode(state, DIB7000P_POWER_INTERFACE_ONLY);

	वापस 0;
पूर्ण

अटल व्योम dib7000p_pll_clk_cfg(काष्ठा dib7000p_state *state)
अणु
	u16 पंचांगp = 0;
	पंचांगp = dib7000p_पढ़ो_word(state, 903);
	dib7000p_ग_लिखो_word(state, 903, (पंचांगp | 0x1));
	पंचांगp = dib7000p_पढ़ो_word(state, 900);
	dib7000p_ग_लिखो_word(state, 900, (पंचांगp & 0x7fff) | (1 << 6));
पूर्ण

अटल व्योम dib7000p_restart_agc(काष्ठा dib7000p_state *state)
अणु
	// P_restart_iqc & P_restart_agc
	dib7000p_ग_लिखो_word(state, 770, (1 << 11) | (1 << 9));
	dib7000p_ग_लिखो_word(state, 770, 0x0000);
पूर्ण

अटल पूर्णांक dib7000p_update_lna(काष्ठा dib7000p_state *state)
अणु
	u16 dyn_gain;

	अगर (state->cfg.update_lna) अणु
		dyn_gain = dib7000p_पढ़ो_word(state, 394);
		अगर (state->cfg.update_lna(&state->demod, dyn_gain)) अणु
			dib7000p_restart_agc(state);
			वापस 1;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक dib7000p_set_agc_config(काष्ठा dib7000p_state *state, u8 band)
अणु
	काष्ठा dibx000_agc_config *agc = शून्य;
	पूर्णांक i;
	अगर (state->current_band == band && state->current_agc != शून्य)
		वापस 0;
	state->current_band = band;

	क्रम (i = 0; i < state->cfg.agc_config_count; i++)
		अगर (state->cfg.agc[i].band_caps & band) अणु
			agc = &state->cfg.agc[i];
			अवरोध;
		पूर्ण

	अगर (agc == शून्य) अणु
		dprपूर्णांकk("no valid AGC configuration found for band 0x%02x\n", band);
		वापस -EINVAL;
	पूर्ण

	state->current_agc = agc;

	/* AGC */
	dib7000p_ग_लिखो_word(state, 75, agc->setup);
	dib7000p_ग_लिखो_word(state, 76, agc->inv_gain);
	dib7000p_ग_लिखो_word(state, 77, agc->समय_stabiliz);
	dib7000p_ग_लिखो_word(state, 100, (agc->alpha_level << 12) | agc->thlock);

	// Demod AGC loop configuration
	dib7000p_ग_लिखो_word(state, 101, (agc->alpha_mant << 5) | agc->alpha_exp);
	dib7000p_ग_लिखो_word(state, 102, (agc->beta_mant << 6) | agc->beta_exp);

	/* AGC जारीd */
	dprपूर्णांकk("WBD: ref: %d, sel: %d, active: %d, alpha: %d\n",
		state->wbd_ref != 0 ? state->wbd_ref : agc->wbd_ref, agc->wbd_sel, !agc->perक्रमm_agc_softsplit, agc->wbd_sel);

	अगर (state->wbd_ref != 0)
		dib7000p_ग_लिखो_word(state, 105, (agc->wbd_inv << 12) | state->wbd_ref);
	अन्यथा
		dib7000p_ग_लिखो_word(state, 105, (agc->wbd_inv << 12) | agc->wbd_ref);

	dib7000p_ग_लिखो_word(state, 106, (agc->wbd_sel << 13) | (agc->wbd_alpha << 9) | (agc->perक्रमm_agc_softsplit << 8));

	dib7000p_ग_लिखो_word(state, 107, agc->agc1_max);
	dib7000p_ग_लिखो_word(state, 108, agc->agc1_min);
	dib7000p_ग_लिखो_word(state, 109, agc->agc2_max);
	dib7000p_ग_लिखो_word(state, 110, agc->agc2_min);
	dib7000p_ग_लिखो_word(state, 111, (agc->agc1_pt1 << 8) | agc->agc1_pt2);
	dib7000p_ग_लिखो_word(state, 112, agc->agc1_pt3);
	dib7000p_ग_लिखो_word(state, 113, (agc->agc1_slope1 << 8) | agc->agc1_slope2);
	dib7000p_ग_लिखो_word(state, 114, (agc->agc2_pt1 << 8) | agc->agc2_pt2);
	dib7000p_ग_लिखो_word(state, 115, (agc->agc2_slope1 << 8) | agc->agc2_slope2);
	वापस 0;
पूर्ण

अटल पूर्णांक dib7000p_set_dds(काष्ठा dib7000p_state *state, s32 offset_khz)
अणु
	u32 पूर्णांकernal = dib7000p_get_पूर्णांकernal_freq(state);
	s32 unit_khz_dds_val;
	u32 असल_offset_khz = असल(offset_khz);
	u32 dds = state->cfg.bw->अगरreq & 0x1ffffff;
	u8 invert = !!(state->cfg.bw->अगरreq & (1 << 25));
	अगर (पूर्णांकernal == 0) अणु
		pr_warn("DIB7000P: dib7000p_get_internal_freq returned 0\n");
		वापस -1;
	पूर्ण
	/* 2**26 / Fsampling is the unit 1KHz offset */
	unit_khz_dds_val = 67108864 / (पूर्णांकernal);

	dprपूर्णांकk("setting a frequency offset of %dkHz internal freq = %d invert = %d\n", offset_khz, पूर्णांकernal, invert);

	अगर (offset_khz < 0)
		unit_khz_dds_val *= -1;

	/* IF tuner */
	अगर (invert)
		dds -= (असल_offset_khz * unit_khz_dds_val);	/* /100 because of /100 on the unit_khz_dds_val line calc क्रम better accuracy */
	अन्यथा
		dds += (असल_offset_khz * unit_khz_dds_val);

	अगर (असल_offset_khz <= (पूर्णांकernal / 2)) अणु	/* Max dds offset is the half of the demod freq */
		dib7000p_ग_लिखो_word(state, 21, (u16) (((dds >> 16) & 0x1ff) | (0 << 10) | (invert << 9)));
		dib7000p_ग_लिखो_word(state, 22, (u16) (dds & 0xffff));
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक dib7000p_agc_startup(काष्ठा dvb_frontend *demod)
अणु
	काष्ठा dtv_frontend_properties *ch = &demod->dtv_property_cache;
	काष्ठा dib7000p_state *state = demod->demodulator_priv;
	पूर्णांक ret = -1;
	u8 *agc_state = &state->agc_state;
	u8 agc_split;
	u16 reg;
	u32 upd_demod_gain_period = 0x1000;
	s32 frequency_offset = 0;

	चयन (state->agc_state) अणु
	हाल 0:
		dib7000p_set_घातer_mode(state, DIB7000P_POWER_ALL);
		अगर (state->version == SOC7090) अणु
			reg = dib7000p_पढ़ो_word(state, 0x79b) & 0xff00;
			dib7000p_ग_लिखो_word(state, 0x79a, upd_demod_gain_period & 0xFFFF);	/* lsb */
			dib7000p_ग_लिखो_word(state, 0x79b, reg | (1 << 14) | ((upd_demod_gain_period >> 16) & 0xFF));

			/* enable adc i & q */
			reg = dib7000p_पढ़ो_word(state, 0x780);
			dib7000p_ग_लिखो_word(state, 0x780, (reg | (0x3)) & (~(1 << 7)));
		पूर्ण अन्यथा अणु
			dib7000p_set_adc_state(state, DIBX000_ADC_ON);
			dib7000p_pll_clk_cfg(state);
		पूर्ण

		अगर (dib7000p_set_agc_config(state, BAND_OF_FREQUENCY(ch->frequency / 1000)) != 0)
			वापस -1;

		अगर (demod->ops.tuner_ops.get_frequency) अणु
			u32 frequency_tuner;

			demod->ops.tuner_ops.get_frequency(demod, &frequency_tuner);
			frequency_offset = (s32)frequency_tuner / 1000 - ch->frequency / 1000;
		पूर्ण

		अगर (dib7000p_set_dds(state, frequency_offset) < 0)
			वापस -1;

		ret = 7;
		(*agc_state)++;
		अवरोध;

	हाल 1:
		अगर (state->cfg.agc_control)
			state->cfg.agc_control(&state->demod, 1);

		dib7000p_ग_लिखो_word(state, 78, 32768);
		अगर (!state->current_agc->perक्रमm_agc_softsplit) अणु
			/* we are using the wbd - so slow AGC startup */
			/* क्रमce 0 split on WBD and restart AGC */
			dib7000p_ग_लिखो_word(state, 106, (state->current_agc->wbd_sel << 13) | (state->current_agc->wbd_alpha << 9) | (1 << 8));
			(*agc_state)++;
			ret = 5;
		पूर्ण अन्यथा अणु
			/* शेष AGC startup */
			(*agc_state) = 4;
			/* रुको AGC rough lock समय */
			ret = 7;
		पूर्ण

		dib7000p_restart_agc(state);
		अवरोध;

	हाल 2:		/* fast split search path after 5sec */
		dib7000p_ग_लिखो_word(state, 75, state->current_agc->setup | (1 << 4));	/* मुक्तze AGC loop */
		dib7000p_ग_लिखो_word(state, 106, (state->current_agc->wbd_sel << 13) | (2 << 9) | (0 << 8));	/* fast split search 0.25kHz */
		(*agc_state)++;
		ret = 14;
		अवरोध;

	हाल 3:		/* split search ended */
		agc_split = (u8) dib7000p_पढ़ो_word(state, 396);	/* store the split value क्रम the next समय */
		dib7000p_ग_लिखो_word(state, 78, dib7000p_पढ़ो_word(state, 394));	/* set AGC gain start value */

		dib7000p_ग_लिखो_word(state, 75, state->current_agc->setup);	/* std AGC loop */
		dib7000p_ग_लिखो_word(state, 106, (state->current_agc->wbd_sel << 13) | (state->current_agc->wbd_alpha << 9) | agc_split);	/* standard split search */

		dib7000p_restart_agc(state);

		dprपूर्णांकk("SPLIT %p: %u\n", demod, agc_split);

		(*agc_state)++;
		ret = 5;
		अवरोध;

	हाल 4:		/* LNA startup */
		ret = 7;

		अगर (dib7000p_update_lna(state))
			ret = 5;
		अन्यथा
			(*agc_state)++;
		अवरोध;

	हाल 5:
		अगर (state->cfg.agc_control)
			state->cfg.agc_control(&state->demod, 0);
		(*agc_state)++;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

अटल व्योम dib7000p_update_timf(काष्ठा dib7000p_state *state)
अणु
	u32 timf = (dib7000p_पढ़ो_word(state, 427) << 16) | dib7000p_पढ़ो_word(state, 428);
	state->timf = timf * 160 / (state->current_bandwidth / 50);
	dib7000p_ग_लिखो_word(state, 23, (u16) (timf >> 16));
	dib7000p_ग_लिखो_word(state, 24, (u16) (timf & 0xffff));
	dprपूर्णांकk("updated timf_frequency: %d (default: %d)\n", state->timf, state->cfg.bw->timf);

पूर्ण

अटल u32 dib7000p_ctrl_timf(काष्ठा dvb_frontend *fe, u8 op, u32 timf)
अणु
	काष्ठा dib7000p_state *state = fe->demodulator_priv;
	चयन (op) अणु
	हाल DEMOD_TIMF_SET:
		state->timf = timf;
		अवरोध;
	हाल DEMOD_TIMF_UPDATE:
		dib7000p_update_timf(state);
		अवरोध;
	हाल DEMOD_TIMF_GET:
		अवरोध;
	पूर्ण
	dib7000p_set_bandwidth(state, state->current_bandwidth);
	वापस state->timf;
पूर्ण

अटल व्योम dib7000p_set_channel(काष्ठा dib7000p_state *state,
				 काष्ठा dtv_frontend_properties *ch, u8 seq)
अणु
	u16 value, est[4];

	dib7000p_set_bandwidth(state, BANDWIDTH_TO_KHZ(ch->bandwidth_hz));

	/* nfft, guard, qam, alpha */
	value = 0;
	चयन (ch->transmission_mode) अणु
	हाल TRANSMISSION_MODE_2K:
		value |= (0 << 7);
		अवरोध;
	हाल TRANSMISSION_MODE_4K:
		value |= (2 << 7);
		अवरोध;
	शेष:
	हाल TRANSMISSION_MODE_8K:
		value |= (1 << 7);
		अवरोध;
	पूर्ण
	चयन (ch->guard_पूर्णांकerval) अणु
	हाल GUARD_INTERVAL_1_32:
		value |= (0 << 5);
		अवरोध;
	हाल GUARD_INTERVAL_1_16:
		value |= (1 << 5);
		अवरोध;
	हाल GUARD_INTERVAL_1_4:
		value |= (3 << 5);
		अवरोध;
	शेष:
	हाल GUARD_INTERVAL_1_8:
		value |= (2 << 5);
		अवरोध;
	पूर्ण
	चयन (ch->modulation) अणु
	हाल QPSK:
		value |= (0 << 3);
		अवरोध;
	हाल QAM_16:
		value |= (1 << 3);
		अवरोध;
	शेष:
	हाल QAM_64:
		value |= (2 << 3);
		अवरोध;
	पूर्ण
	चयन (HIERARCHY_1) अणु
	हाल HIERARCHY_2:
		value |= 2;
		अवरोध;
	हाल HIERARCHY_4:
		value |= 4;
		अवरोध;
	शेष:
	हाल HIERARCHY_1:
		value |= 1;
		अवरोध;
	पूर्ण
	dib7000p_ग_लिखो_word(state, 0, value);
	dib7000p_ग_लिखो_word(state, 5, (seq << 4) | 1);	/* करो not क्रमce tps, search list 0 */

	/* P_dपूर्णांकl_native, P_dपूर्णांकlv_inv, P_hrch, P_code_rate, P_select_hp */
	value = 0;
	अगर (1 != 0)
		value |= (1 << 6);
	अगर (ch->hierarchy == 1)
		value |= (1 << 4);
	अगर (1 == 1)
		value |= 1;
	चयन ((ch->hierarchy == 0 || 1 == 1) ? ch->code_rate_HP : ch->code_rate_LP) अणु
	हाल FEC_2_3:
		value |= (2 << 1);
		अवरोध;
	हाल FEC_3_4:
		value |= (3 << 1);
		अवरोध;
	हाल FEC_5_6:
		value |= (5 << 1);
		अवरोध;
	हाल FEC_7_8:
		value |= (7 << 1);
		अवरोध;
	शेष:
	हाल FEC_1_2:
		value |= (1 << 1);
		अवरोध;
	पूर्ण
	dib7000p_ग_लिखो_word(state, 208, value);

	/* offset loop parameters */
	dib7000p_ग_लिखो_word(state, 26, 0x6680);
	dib7000p_ग_लिखो_word(state, 32, 0x0003);
	dib7000p_ग_लिखो_word(state, 29, 0x1273);
	dib7000p_ग_लिखो_word(state, 33, 0x0005);

	/* P_dvsy_sync_रुको */
	चयन (ch->transmission_mode) अणु
	हाल TRANSMISSION_MODE_8K:
		value = 256;
		अवरोध;
	हाल TRANSMISSION_MODE_4K:
		value = 128;
		अवरोध;
	हाल TRANSMISSION_MODE_2K:
	शेष:
		value = 64;
		अवरोध;
	पूर्ण
	चयन (ch->guard_पूर्णांकerval) अणु
	हाल GUARD_INTERVAL_1_16:
		value *= 2;
		अवरोध;
	हाल GUARD_INTERVAL_1_8:
		value *= 4;
		अवरोध;
	हाल GUARD_INTERVAL_1_4:
		value *= 8;
		अवरोध;
	शेष:
	हाल GUARD_INTERVAL_1_32:
		value *= 1;
		अवरोध;
	पूर्ण
	अगर (state->cfg.भागersity_delay == 0)
		state->भाग_sync_रुको = (value * 3) / 2 + 48;
	अन्यथा
		state->भाग_sync_रुको = (value * 3) / 2 + state->cfg.भागersity_delay;

	/* deactivate the possibility of भागersity reception अगर extended पूर्णांकerleaver */
	state->भाग_क्रमce_off = !1 && ch->transmission_mode != TRANSMISSION_MODE_8K;
	dib7000p_set_भागersity_in(&state->demod, state->भाग_state);

	/* channel estimation fine configuration */
	चयन (ch->modulation) अणु
	हाल QAM_64:
		est[0] = 0x0148;	/* P_adp_regul_cnt 0.04 */
		est[1] = 0xfff0;	/* P_adp_noise_cnt -0.002 */
		est[2] = 0x00a4;	/* P_adp_regul_ext 0.02 */
		est[3] = 0xfff8;	/* P_adp_noise_ext -0.001 */
		अवरोध;
	हाल QAM_16:
		est[0] = 0x023d;	/* P_adp_regul_cnt 0.07 */
		est[1] = 0xffdf;	/* P_adp_noise_cnt -0.004 */
		est[2] = 0x00a4;	/* P_adp_regul_ext 0.02 */
		est[3] = 0xfff0;	/* P_adp_noise_ext -0.002 */
		अवरोध;
	शेष:
		est[0] = 0x099a;	/* P_adp_regul_cnt 0.3 */
		est[1] = 0xffae;	/* P_adp_noise_cnt -0.01 */
		est[2] = 0x0333;	/* P_adp_regul_ext 0.1 */
		est[3] = 0xfff8;	/* P_adp_noise_ext -0.002 */
		अवरोध;
	पूर्ण
	क्रम (value = 0; value < 4; value++)
		dib7000p_ग_लिखो_word(state, 187 + value, est[value]);
पूर्ण

अटल पूर्णांक dib7000p_स्वतःsearch_start(काष्ठा dvb_frontend *demod)
अणु
	काष्ठा dtv_frontend_properties *ch = &demod->dtv_property_cache;
	काष्ठा dib7000p_state *state = demod->demodulator_priv;
	काष्ठा dtv_frontend_properties schan;
	u32 value, factor;
	u32 पूर्णांकernal = dib7000p_get_पूर्णांकernal_freq(state);

	schan = *ch;
	schan.modulation = QAM_64;
	schan.guard_पूर्णांकerval = GUARD_INTERVAL_1_32;
	schan.transmission_mode = TRANSMISSION_MODE_8K;
	schan.code_rate_HP = FEC_2_3;
	schan.code_rate_LP = FEC_3_4;
	schan.hierarchy = 0;

	dib7000p_set_channel(state, &schan, 7);

	factor = BANDWIDTH_TO_KHZ(ch->bandwidth_hz);
	अगर (factor >= 5000) अणु
		अगर (state->version == SOC7090)
			factor = 2;
		अन्यथा
			factor = 1;
	पूर्ण अन्यथा
		factor = 6;

	value = 30 * पूर्णांकernal * factor;
	dib7000p_ग_लिखो_word(state, 6, (u16) ((value >> 16) & 0xffff));
	dib7000p_ग_लिखो_word(state, 7, (u16) (value & 0xffff));
	value = 100 * पूर्णांकernal * factor;
	dib7000p_ग_लिखो_word(state, 8, (u16) ((value >> 16) & 0xffff));
	dib7000p_ग_लिखो_word(state, 9, (u16) (value & 0xffff));
	value = 500 * पूर्णांकernal * factor;
	dib7000p_ग_लिखो_word(state, 10, (u16) ((value >> 16) & 0xffff));
	dib7000p_ग_लिखो_word(state, 11, (u16) (value & 0xffff));

	value = dib7000p_पढ़ो_word(state, 0);
	dib7000p_ग_लिखो_word(state, 0, (u16) ((1 << 9) | value));
	dib7000p_पढ़ो_word(state, 1284);
	dib7000p_ग_लिखो_word(state, 0, (u16) value);

	वापस 0;
पूर्ण

अटल पूर्णांक dib7000p_स्वतःsearch_is_irq(काष्ठा dvb_frontend *demod)
अणु
	काष्ठा dib7000p_state *state = demod->demodulator_priv;
	u16 irq_pending = dib7000p_पढ़ो_word(state, 1284);

	अगर (irq_pending & 0x1)
		वापस 1;

	अगर (irq_pending & 0x2)
		वापस 2;

	वापस 0;
पूर्ण

अटल व्योम dib7000p_spur_protect(काष्ठा dib7000p_state *state, u32 rf_khz, u32 bw)
अणु
	अटल s16 notch[] = अणु 16143, 14402, 12238, 9713, 6902, 3888, 759, -2392 पूर्ण;
	अटल u8 sine[] = अणु 0, 2, 3, 5, 6, 8, 9, 11, 13, 14, 16, 17, 19, 20, 22,
		24, 25, 27, 28, 30, 31, 33, 34, 36, 38, 39, 41, 42, 44, 45, 47, 48, 50, 51,
		53, 55, 56, 58, 59, 61, 62, 64, 65, 67, 68, 70, 71, 73, 74, 76, 77, 79, 80,
		82, 83, 85, 86, 88, 89, 91, 92, 94, 95, 97, 98, 99, 101, 102, 104, 105,
		107, 108, 109, 111, 112, 114, 115, 117, 118, 119, 121, 122, 123, 125, 126,
		128, 129, 130, 132, 133, 134, 136, 137, 138, 140, 141, 142, 144, 145, 146,
		147, 149, 150, 151, 152, 154, 155, 156, 157, 159, 160, 161, 162, 164, 165,
		166, 167, 168, 170, 171, 172, 173, 174, 175, 177, 178, 179, 180, 181, 182,
		183, 184, 185, 186, 188, 189, 190, 191, 192, 193, 194, 195, 196, 197, 198,
		199, 200, 201, 202, 203, 204, 205, 206, 207, 207, 208, 209, 210, 211, 212,
		213, 214, 215, 215, 216, 217, 218, 219, 220, 220, 221, 222, 223, 224, 224,
		225, 226, 227, 227, 228, 229, 229, 230, 231, 231, 232, 233, 233, 234, 235,
		235, 236, 237, 237, 238, 238, 239, 239, 240, 241, 241, 242, 242, 243, 243,
		244, 244, 245, 245, 245, 246, 246, 247, 247, 248, 248, 248, 249, 249, 249,
		250, 250, 250, 251, 251, 251, 252, 252, 252, 252, 253, 253, 253, 253, 254,
		254, 254, 254, 254, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
		255, 255, 255, 255, 255, 255
	पूर्ण;

	u32 xtal = state->cfg.bw->xtal_hz / 1000;
	पूर्णांक f_rel = DIV_ROUND_CLOSEST(rf_khz, xtal) * xtal - rf_khz;
	पूर्णांक k;
	पूर्णांक coef_re[8], coef_im[8];
	पूर्णांक bw_khz = bw;
	u32 pha;

	dprपूर्णांकk("relative position of the Spur: %dk (RF: %dk, XTAL: %dk)\n", f_rel, rf_khz, xtal);

	अगर (f_rel < -bw_khz / 2 || f_rel > bw_khz / 2)
		वापस;

	bw_khz /= 100;

	dib7000p_ग_लिखो_word(state, 142, 0x0610);

	क्रम (k = 0; k < 8; k++) अणु
		pha = ((f_rel * (k + 1) * 112 * 80 / bw_khz) / 1000) & 0x3ff;

		अगर (pha == 0) अणु
			coef_re[k] = 256;
			coef_im[k] = 0;
		पूर्ण अन्यथा अगर (pha < 256) अणु
			coef_re[k] = sine[256 - (pha & 0xff)];
			coef_im[k] = sine[pha & 0xff];
		पूर्ण अन्यथा अगर (pha == 256) अणु
			coef_re[k] = 0;
			coef_im[k] = 256;
		पूर्ण अन्यथा अगर (pha < 512) अणु
			coef_re[k] = -sine[pha & 0xff];
			coef_im[k] = sine[256 - (pha & 0xff)];
		पूर्ण अन्यथा अगर (pha == 512) अणु
			coef_re[k] = -256;
			coef_im[k] = 0;
		पूर्ण अन्यथा अगर (pha < 768) अणु
			coef_re[k] = -sine[256 - (pha & 0xff)];
			coef_im[k] = -sine[pha & 0xff];
		पूर्ण अन्यथा अगर (pha == 768) अणु
			coef_re[k] = 0;
			coef_im[k] = -256;
		पूर्ण अन्यथा अणु
			coef_re[k] = sine[pha & 0xff];
			coef_im[k] = -sine[256 - (pha & 0xff)];
		पूर्ण

		coef_re[k] *= notch[k];
		coef_re[k] += (1 << 14);
		अगर (coef_re[k] >= (1 << 24))
			coef_re[k] = (1 << 24) - 1;
		coef_re[k] /= (1 << 15);

		coef_im[k] *= notch[k];
		coef_im[k] += (1 << 14);
		अगर (coef_im[k] >= (1 << 24))
			coef_im[k] = (1 << 24) - 1;
		coef_im[k] /= (1 << 15);

		dprपूर्णांकk("PALF COEF: %d re: %d im: %d\n", k, coef_re[k], coef_im[k]);

		dib7000p_ग_लिखो_word(state, 143, (0 << 14) | (k << 10) | (coef_re[k] & 0x3ff));
		dib7000p_ग_लिखो_word(state, 144, coef_im[k] & 0x3ff);
		dib7000p_ग_लिखो_word(state, 143, (1 << 14) | (k << 10) | (coef_re[k] & 0x3ff));
	पूर्ण
	dib7000p_ग_लिखो_word(state, 143, 0);
पूर्ण

अटल पूर्णांक dib7000p_tune(काष्ठा dvb_frontend *demod)
अणु
	काष्ठा dtv_frontend_properties *ch = &demod->dtv_property_cache;
	काष्ठा dib7000p_state *state = demod->demodulator_priv;
	u16 पंचांगp = 0;

	अगर (ch != शून्य)
		dib7000p_set_channel(state, ch, 0);
	अन्यथा
		वापस -EINVAL;

	// restart demod
	dib7000p_ग_लिखो_word(state, 770, 0x4000);
	dib7000p_ग_लिखो_word(state, 770, 0x0000);
	msleep(45);

	/* P_ctrl_inh_cor=0, P_ctrl_alpha_cor=4, P_ctrl_inh_isi=0, P_ctrl_alpha_isi=3, P_ctrl_inh_cor4=1, P_ctrl_alpha_cor4=3 */
	पंचांगp = (0 << 14) | (4 << 10) | (0 << 9) | (3 << 5) | (1 << 4) | (0x3);
	अगर (state->sfn_workaround_active) अणु
		dprपूर्णांकk("SFN workaround is active\n");
		पंचांगp |= (1 << 9);
		dib7000p_ग_लिखो_word(state, 166, 0x4000);
	पूर्ण अन्यथा अणु
		dib7000p_ग_लिखो_word(state, 166, 0x0000);
	पूर्ण
	dib7000p_ग_लिखो_word(state, 29, पंचांगp);

	// never achieved a lock with that bandwidth so far - रुको क्रम osc-freq to update
	अगर (state->timf == 0)
		msleep(200);

	/* offset loop parameters */

	/* P_timf_alpha, P_corm_alpha=6, P_corm_thres=0x80 */
	पंचांगp = (6 << 8) | 0x80;
	चयन (ch->transmission_mode) अणु
	हाल TRANSMISSION_MODE_2K:
		पंचांगp |= (2 << 12);
		अवरोध;
	हाल TRANSMISSION_MODE_4K:
		पंचांगp |= (3 << 12);
		अवरोध;
	शेष:
	हाल TRANSMISSION_MODE_8K:
		पंचांगp |= (4 << 12);
		अवरोध;
	पूर्ण
	dib7000p_ग_लिखो_word(state, 26, पंचांगp);	/* timf_a(6xxx) */

	/* P_ctrl_मुक्तze_pha_shअगरt=0, P_ctrl_pha_off_max */
	पंचांगp = (0 << 4);
	चयन (ch->transmission_mode) अणु
	हाल TRANSMISSION_MODE_2K:
		पंचांगp |= 0x6;
		अवरोध;
	हाल TRANSMISSION_MODE_4K:
		पंचांगp |= 0x7;
		अवरोध;
	शेष:
	हाल TRANSMISSION_MODE_8K:
		पंचांगp |= 0x8;
		अवरोध;
	पूर्ण
	dib7000p_ग_लिखो_word(state, 32, पंचांगp);

	/* P_ctrl_sfreq_inh=0, P_ctrl_sfreq_step */
	पंचांगp = (0 << 4);
	चयन (ch->transmission_mode) अणु
	हाल TRANSMISSION_MODE_2K:
		पंचांगp |= 0x6;
		अवरोध;
	हाल TRANSMISSION_MODE_4K:
		पंचांगp |= 0x7;
		अवरोध;
	शेष:
	हाल TRANSMISSION_MODE_8K:
		पंचांगp |= 0x8;
		अवरोध;
	पूर्ण
	dib7000p_ग_लिखो_word(state, 33, पंचांगp);

	पंचांगp = dib7000p_पढ़ो_word(state, 509);
	अगर (!((पंचांगp >> 6) & 0x1)) अणु
		/* restart the fec */
		पंचांगp = dib7000p_पढ़ो_word(state, 771);
		dib7000p_ग_लिखो_word(state, 771, पंचांगp | (1 << 1));
		dib7000p_ग_लिखो_word(state, 771, पंचांगp);
		msleep(40);
		पंचांगp = dib7000p_पढ़ो_word(state, 509);
	पूर्ण
	// we achieved a lock - it's समय to update the osc freq
	अगर ((पंचांगp >> 6) & 0x1) अणु
		dib7000p_update_timf(state);
		/* P_timf_alpha += 2 */
		पंचांगp = dib7000p_पढ़ो_word(state, 26);
		dib7000p_ग_लिखो_word(state, 26, (पंचांगp & ~(0xf << 12)) | ((((पंचांगp >> 12) & 0xf) + 5) << 12));
	पूर्ण

	अगर (state->cfg.spur_protect)
		dib7000p_spur_protect(state, ch->frequency / 1000, BANDWIDTH_TO_KHZ(ch->bandwidth_hz));

	dib7000p_set_bandwidth(state, BANDWIDTH_TO_KHZ(ch->bandwidth_hz));

	dib7000p_reset_stats(demod);

	वापस 0;
पूर्ण

अटल पूर्णांक dib7000p_wakeup(काष्ठा dvb_frontend *demod)
अणु
	काष्ठा dib7000p_state *state = demod->demodulator_priv;
	dib7000p_set_घातer_mode(state, DIB7000P_POWER_ALL);
	dib7000p_set_adc_state(state, DIBX000_SLOW_ADC_ON);
	अगर (state->version == SOC7090)
		dib7000p_sad_calib(state);
	वापस 0;
पूर्ण

अटल पूर्णांक dib7000p_sleep(काष्ठा dvb_frontend *demod)
अणु
	काष्ठा dib7000p_state *state = demod->demodulator_priv;
	अगर (state->version == SOC7090)
		वापस dib7000p_set_घातer_mode(state, DIB7000P_POWER_INTERFACE_ONLY);
	वापस dib7000p_set_output_mode(state, OUTMODE_HIGH_Z) | dib7000p_set_घातer_mode(state, DIB7000P_POWER_INTERFACE_ONLY);
पूर्ण

अटल पूर्णांक dib7000p_identअगरy(काष्ठा dib7000p_state *st)
अणु
	u16 value;
	dprपूर्णांकk("checking demod on I2C address: %d (%x)\n", st->i2c_addr, st->i2c_addr);

	अगर ((value = dib7000p_पढ़ो_word(st, 768)) != 0x01b3) अणु
		dprपूर्णांकk("wrong Vendor ID (read=0x%x)\n", value);
		वापस -EREMOTEIO;
	पूर्ण

	अगर ((value = dib7000p_पढ़ो_word(st, 769)) != 0x4000) अणु
		dprपूर्णांकk("wrong Device ID (%x)\n", value);
		वापस -EREMOTEIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक dib7000p_get_frontend(काष्ठा dvb_frontend *fe,
				 काष्ठा dtv_frontend_properties *fep)
अणु
	काष्ठा dib7000p_state *state = fe->demodulator_priv;
	u16 tps = dib7000p_पढ़ो_word(state, 463);

	fep->inversion = INVERSION_AUTO;

	fep->bandwidth_hz = BANDWIDTH_TO_HZ(state->current_bandwidth);

	चयन ((tps >> 8) & 0x3) अणु
	हाल 0:
		fep->transmission_mode = TRANSMISSION_MODE_2K;
		अवरोध;
	हाल 1:
		fep->transmission_mode = TRANSMISSION_MODE_8K;
		अवरोध;
	/* हाल 2: fep->transmission_mode = TRANSMISSION_MODE_4K; अवरोध; */
	पूर्ण

	चयन (tps & 0x3) अणु
	हाल 0:
		fep->guard_पूर्णांकerval = GUARD_INTERVAL_1_32;
		अवरोध;
	हाल 1:
		fep->guard_पूर्णांकerval = GUARD_INTERVAL_1_16;
		अवरोध;
	हाल 2:
		fep->guard_पूर्णांकerval = GUARD_INTERVAL_1_8;
		अवरोध;
	हाल 3:
		fep->guard_पूर्णांकerval = GUARD_INTERVAL_1_4;
		अवरोध;
	पूर्ण

	चयन ((tps >> 14) & 0x3) अणु
	हाल 0:
		fep->modulation = QPSK;
		अवरोध;
	हाल 1:
		fep->modulation = QAM_16;
		अवरोध;
	हाल 2:
	शेष:
		fep->modulation = QAM_64;
		अवरोध;
	पूर्ण

	/* as दीर्घ as the frontend_param काष्ठाure is fixed क्रम hierarchical transmission I refuse to use it */
	/* (tps >> 13) & 0x1 == hrch is used, (tps >> 10) & 0x7 == alpha */

	fep->hierarchy = HIERARCHY_NONE;
	चयन ((tps >> 5) & 0x7) अणु
	हाल 1:
		fep->code_rate_HP = FEC_1_2;
		अवरोध;
	हाल 2:
		fep->code_rate_HP = FEC_2_3;
		अवरोध;
	हाल 3:
		fep->code_rate_HP = FEC_3_4;
		अवरोध;
	हाल 5:
		fep->code_rate_HP = FEC_5_6;
		अवरोध;
	हाल 7:
	शेष:
		fep->code_rate_HP = FEC_7_8;
		अवरोध;

	पूर्ण

	चयन ((tps >> 2) & 0x7) अणु
	हाल 1:
		fep->code_rate_LP = FEC_1_2;
		अवरोध;
	हाल 2:
		fep->code_rate_LP = FEC_2_3;
		अवरोध;
	हाल 3:
		fep->code_rate_LP = FEC_3_4;
		अवरोध;
	हाल 5:
		fep->code_rate_LP = FEC_5_6;
		अवरोध;
	हाल 7:
	शेष:
		fep->code_rate_LP = FEC_7_8;
		अवरोध;
	पूर्ण

	/* native पूर्णांकerleaver: (dib7000p_पढ़ो_word(state, 464) >>  5) & 0x1 */

	वापस 0;
पूर्ण

अटल पूर्णांक dib7000p_set_frontend(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dtv_frontend_properties *fep = &fe->dtv_property_cache;
	काष्ठा dib7000p_state *state = fe->demodulator_priv;
	पूर्णांक समय, ret;

	अगर (state->version == SOC7090)
		dib7090_set_भागersity_in(fe, 0);
	अन्यथा
		dib7000p_set_output_mode(state, OUTMODE_HIGH_Z);

	/* maybe the parameter has been changed */
	state->sfn_workaround_active = buggy_sfn_workaround;

	अगर (fe->ops.tuner_ops.set_params)
		fe->ops.tuner_ops.set_params(fe);

	/* start up the AGC */
	state->agc_state = 0;
	करो अणु
		समय = dib7000p_agc_startup(fe);
		अगर (समय != -1)
			msleep(समय);
	पूर्ण जबतक (समय != -1);

	अगर (fep->transmission_mode == TRANSMISSION_MODE_AUTO ||
		fep->guard_पूर्णांकerval == GUARD_INTERVAL_AUTO || fep->modulation == QAM_AUTO || fep->code_rate_HP == FEC_AUTO) अणु
		पूर्णांक i = 800, found;

		dib7000p_स्वतःsearch_start(fe);
		करो अणु
			msleep(1);
			found = dib7000p_स्वतःsearch_is_irq(fe);
		पूर्ण जबतक (found == 0 && i--);

		dprपूर्णांकk("autosearch returns: %d\n", found);
		अगर (found == 0 || found == 1)
			वापस 0;

		dib7000p_get_frontend(fe, fep);
	पूर्ण

	ret = dib7000p_tune(fe);

	/* make this a config parameter */
	अगर (state->version == SOC7090) अणु
		dib7090_set_output_mode(fe, state->cfg.output_mode);
		अगर (state->cfg.enMpegOutput == 0) अणु
			dib7090_setDibTxMux(state, MPEG_ON_DIBTX);
			dib7090_setHostBusMux(state, DIBTX_ON_HOSTBUS);
		पूर्ण
	पूर्ण अन्यथा
		dib7000p_set_output_mode(state, state->cfg.output_mode);

	वापस ret;
पूर्ण

अटल पूर्णांक dib7000p_get_stats(काष्ठा dvb_frontend *fe, क्रमागत fe_status stat);

अटल पूर्णांक dib7000p_पढ़ो_status(काष्ठा dvb_frontend *fe, क्रमागत fe_status *stat)
अणु
	काष्ठा dib7000p_state *state = fe->demodulator_priv;
	u16 lock = dib7000p_पढ़ो_word(state, 509);

	*stat = 0;

	अगर (lock & 0x8000)
		*stat |= FE_HAS_SIGNAL;
	अगर (lock & 0x3000)
		*stat |= FE_HAS_CARRIER;
	अगर (lock & 0x0100)
		*stat |= FE_HAS_VITERBI;
	अगर (lock & 0x0010)
		*stat |= FE_HAS_SYNC;
	अगर ((lock & 0x0038) == 0x38)
		*stat |= FE_HAS_LOCK;

	dib7000p_get_stats(fe, *stat);

	वापस 0;
पूर्ण

अटल पूर्णांक dib7000p_पढ़ो_ber(काष्ठा dvb_frontend *fe, u32 * ber)
अणु
	काष्ठा dib7000p_state *state = fe->demodulator_priv;
	*ber = (dib7000p_पढ़ो_word(state, 500) << 16) | dib7000p_पढ़ो_word(state, 501);
	वापस 0;
पूर्ण

अटल पूर्णांक dib7000p_पढ़ो_unc_blocks(काष्ठा dvb_frontend *fe, u32 * unc)
अणु
	काष्ठा dib7000p_state *state = fe->demodulator_priv;
	*unc = dib7000p_पढ़ो_word(state, 506);
	वापस 0;
पूर्ण

अटल पूर्णांक dib7000p_पढ़ो_संकेत_strength(काष्ठा dvb_frontend *fe, u16 * strength)
अणु
	काष्ठा dib7000p_state *state = fe->demodulator_priv;
	u16 val = dib7000p_पढ़ो_word(state, 394);
	*strength = 65535 - val;
	वापस 0;
पूर्ण

अटल u32 dib7000p_get_snr(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dib7000p_state *state = fe->demodulator_priv;
	u16 val;
	s32 संकेत_mant, संकेत_exp, noise_mant, noise_exp;
	u32 result = 0;

	val = dib7000p_पढ़ो_word(state, 479);
	noise_mant = (val >> 4) & 0xff;
	noise_exp = ((val & 0xf) << 2);
	val = dib7000p_पढ़ो_word(state, 480);
	noise_exp += ((val >> 14) & 0x3);
	अगर ((noise_exp & 0x20) != 0)
		noise_exp -= 0x40;

	संकेत_mant = (val >> 6) & 0xFF;
	संकेत_exp = (val & 0x3F);
	अगर ((संकेत_exp & 0x20) != 0)
		संकेत_exp -= 0x40;

	अगर (संकेत_mant != 0)
		result = पूर्णांकlog10(2) * 10 * संकेत_exp + 10 * पूर्णांकlog10(संकेत_mant);
	अन्यथा
		result = पूर्णांकlog10(2) * 10 * संकेत_exp - 100;

	अगर (noise_mant != 0)
		result -= पूर्णांकlog10(2) * 10 * noise_exp + 10 * पूर्णांकlog10(noise_mant);
	अन्यथा
		result -= पूर्णांकlog10(2) * 10 * noise_exp - 100;

	वापस result;
पूर्ण

अटल पूर्णांक dib7000p_पढ़ो_snr(काष्ठा dvb_frontend *fe, u16 *snr)
अणु
	u32 result;

	result = dib7000p_get_snr(fe);

	*snr = result / ((1 << 24) / 10);
	वापस 0;
पूर्ण

अटल व्योम dib7000p_reset_stats(काष्ठा dvb_frontend *demod)
अणु
	काष्ठा dib7000p_state *state = demod->demodulator_priv;
	काष्ठा dtv_frontend_properties *c = &demod->dtv_property_cache;
	u32 ucb;

	स_रखो(&c->strength, 0, माप(c->strength));
	स_रखो(&c->cnr, 0, माप(c->cnr));
	स_रखो(&c->post_bit_error, 0, माप(c->post_bit_error));
	स_रखो(&c->post_bit_count, 0, माप(c->post_bit_count));
	स_रखो(&c->block_error, 0, माप(c->block_error));

	c->strength.len = 1;
	c->cnr.len = 1;
	c->block_error.len = 1;
	c->block_count.len = 1;
	c->post_bit_error.len = 1;
	c->post_bit_count.len = 1;

	c->strength.stat[0].scale = FE_SCALE_DECIBEL;
	c->strength.stat[0].uvalue = 0;

	c->cnr.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	c->block_error.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	c->block_count.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	c->post_bit_error.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	c->post_bit_count.stat[0].scale = FE_SCALE_NOT_AVAILABLE;

	dib7000p_पढ़ो_unc_blocks(demod, &ucb);

	state->old_ucb = ucb;
	state->ber_jअगरfies_stats = 0;
	state->per_jअगरfies_stats = 0;
पूर्ण

काष्ठा linear_segments अणु
	अचिन्हित x;
	चिन्हित y;
पूर्ण;

/*
 * Table to estimate संकेत strength in dBm.
 * This table should be empirically determinated by measuring the संकेत
 * strength generated by a RF generator directly connected पूर्णांकo
 * a device.
 * This table was determinated by measuring the संकेत strength generated
 * by a DTA-2111 RF generator directly connected पूर्णांकo a dib7000p device
 * (a Hauppauge Nova-TD stick), using a good quality 3 meters length
 * RC6 cable and good RC6 connectors, connected directly to antenna 1.
 * As the minimum output घातer of DTA-2111 is -31dBm, a 16 dBm attenuator
 * were used, क्रम the lower घातer values.
 * The real value can actually be on other devices, or even at the
 * second antena input, depending on several factors, like अगर LNA
 * is enabled or not, अगर भागersity is enabled, type of connectors, etc.
 * Yet, it is better to use this measure in dB than a अक्रमom non-linear
 * percentage value, especially क्रम antenna adjusपंचांगents.
 * On my tests, the precision of the measure using this table is about
 * 0.5 dB, with sounds reasonable enough to adjust antennas.
 */
#घोषणा DB_OFFSET 131000

अटल काष्ठा linear_segments strength_to_db_table[] = अणु
	अणु 63630, DB_OFFSET - 20500पूर्ण,
	अणु 62273, DB_OFFSET - 21000पूर्ण,
	अणु 60162, DB_OFFSET - 22000पूर्ण,
	अणु 58730, DB_OFFSET - 23000पूर्ण,
	अणु 58294, DB_OFFSET - 24000पूर्ण,
	अणु 57778, DB_OFFSET - 25000पूर्ण,
	अणु 57320, DB_OFFSET - 26000पूर्ण,
	अणु 56779, DB_OFFSET - 27000पूर्ण,
	अणु 56293, DB_OFFSET - 28000पूर्ण,
	अणु 55724, DB_OFFSET - 29000पूर्ण,
	अणु 55145, DB_OFFSET - 30000पूर्ण,
	अणु 54680, DB_OFFSET - 31000पूर्ण,
	अणु 54293, DB_OFFSET - 32000पूर्ण,
	अणु 53813, DB_OFFSET - 33000पूर्ण,
	अणु 53427, DB_OFFSET - 34000पूर्ण,
	अणु 52981, DB_OFFSET - 35000पूर्ण,

	अणु 52636, DB_OFFSET - 36000पूर्ण,
	अणु 52014, DB_OFFSET - 37000पूर्ण,
	अणु 51674, DB_OFFSET - 38000पूर्ण,
	अणु 50692, DB_OFFSET - 39000पूर्ण,
	अणु 49824, DB_OFFSET - 40000पूर्ण,
	अणु 49052, DB_OFFSET - 41000पूर्ण,
	अणु 48436, DB_OFFSET - 42000पूर्ण,
	अणु 47836, DB_OFFSET - 43000पूर्ण,
	अणु 47368, DB_OFFSET - 44000पूर्ण,
	अणु 46468, DB_OFFSET - 45000पूर्ण,
	अणु 45597, DB_OFFSET - 46000पूर्ण,
	अणु 44586, DB_OFFSET - 47000पूर्ण,
	अणु 43667, DB_OFFSET - 48000पूर्ण,
	अणु 42673, DB_OFFSET - 49000पूर्ण,
	अणु 41816, DB_OFFSET - 50000पूर्ण,
	अणु 40876, DB_OFFSET - 51000पूर्ण,
	अणु     0,      0पूर्ण,
पूर्ण;

अटल u32 पूर्णांकerpolate_value(u32 value, काष्ठा linear_segments *segments,
			     अचिन्हित len)
अणु
	u64 पंचांगp64;
	u32 dx;
	s32 dy;
	पूर्णांक i, ret;

	अगर (value >= segments[0].x)
		वापस segments[0].y;
	अगर (value < segments[len-1].x)
		वापस segments[len-1].y;

	क्रम (i = 1; i < len - 1; i++) अणु
		/* If value is identical, no need to पूर्णांकerpolate */
		अगर (value == segments[i].x)
			वापस segments[i].y;
		अगर (value > segments[i].x)
			अवरोध;
	पूर्ण

	/* Linear पूर्णांकerpolation between the two (x,y) poपूर्णांकs */
	dy = segments[i - 1].y - segments[i].y;
	dx = segments[i - 1].x - segments[i].x;

	पंचांगp64 = value - segments[i].x;
	पंचांगp64 *= dy;
	करो_भाग(पंचांगp64, dx);
	ret = segments[i].y + पंचांगp64;

	वापस ret;
पूर्ण

/* FIXME: may require changes - this one was borrowed from dib8000 */
अटल u32 dib7000p_get_समय_us(काष्ठा dvb_frontend *demod)
अणु
	काष्ठा dtv_frontend_properties *c = &demod->dtv_property_cache;
	u64 समय_us, पंचांगp64;
	u32 पंचांगp, denom;
	पूर्णांक guard, rate_num, rate_dक्रमागत = 1, bits_per_symbol;
	पूर्णांक पूर्णांकerleaving = 0, fft_भाग;

	चयन (c->guard_पूर्णांकerval) अणु
	हाल GUARD_INTERVAL_1_4:
		guard = 4;
		अवरोध;
	हाल GUARD_INTERVAL_1_8:
		guard = 8;
		अवरोध;
	हाल GUARD_INTERVAL_1_16:
		guard = 16;
		अवरोध;
	शेष:
	हाल GUARD_INTERVAL_1_32:
		guard = 32;
		अवरोध;
	पूर्ण

	चयन (c->transmission_mode) अणु
	हाल TRANSMISSION_MODE_2K:
		fft_भाग = 4;
		अवरोध;
	हाल TRANSMISSION_MODE_4K:
		fft_भाग = 2;
		अवरोध;
	शेष:
	हाल TRANSMISSION_MODE_8K:
		fft_भाग = 1;
		अवरोध;
	पूर्ण

	चयन (c->modulation) अणु
	हाल DQPSK:
	हाल QPSK:
		bits_per_symbol = 2;
		अवरोध;
	हाल QAM_16:
		bits_per_symbol = 4;
		अवरोध;
	शेष:
	हाल QAM_64:
		bits_per_symbol = 6;
		अवरोध;
	पूर्ण

	चयन ((c->hierarchy == 0 || 1 == 1) ? c->code_rate_HP : c->code_rate_LP) अणु
	हाल FEC_1_2:
		rate_num = 1;
		rate_dक्रमागत = 2;
		अवरोध;
	हाल FEC_2_3:
		rate_num = 2;
		rate_dक्रमागत = 3;
		अवरोध;
	हाल FEC_3_4:
		rate_num = 3;
		rate_dक्रमागत = 4;
		अवरोध;
	हाल FEC_5_6:
		rate_num = 5;
		rate_dक्रमागत = 6;
		अवरोध;
	शेष:
	हाल FEC_7_8:
		rate_num = 7;
		rate_dक्रमागत = 8;
		अवरोध;
	पूर्ण

	denom = bits_per_symbol * rate_num * fft_भाग * 384;

	/*
	 * FIXME: check अगर the math makes sense. If so, fill the
	 * पूर्णांकerleaving var.
	 */

	/* If calculus माला_लो wrong, रुको क्रम 1s क्रम the next stats */
	अगर (!denom)
		वापस 0;

	/* Estimate the period क्रम the total bit rate */
	समय_us = rate_dक्रमागत * (1008 * 1562500L);
	पंचांगp64 = समय_us;
	करो_भाग(पंचांगp64, guard);
	समय_us = समय_us + पंचांगp64;
	समय_us += denom / 2;
	करो_भाग(समय_us, denom);

	पंचांगp = 1008 * 96 * पूर्णांकerleaving;
	समय_us += पंचांगp + पंचांगp / guard;

	वापस समय_us;
पूर्ण

अटल पूर्णांक dib7000p_get_stats(काष्ठा dvb_frontend *demod, क्रमागत fe_status stat)
अणु
	काष्ठा dib7000p_state *state = demod->demodulator_priv;
	काष्ठा dtv_frontend_properties *c = &demod->dtv_property_cache;
	पूर्णांक show_per_stats = 0;
	u32 समय_us = 0, val, snr;
	u64 blocks, ucb;
	s32 db;
	u16 strength;

	/* Get Signal strength */
	dib7000p_पढ़ो_संकेत_strength(demod, &strength);
	val = strength;
	db = पूर्णांकerpolate_value(val,
			       strength_to_db_table,
			       ARRAY_SIZE(strength_to_db_table)) - DB_OFFSET;
	c->strength.stat[0].svalue = db;

	/* UCB/BER/CNR measures require lock */
	अगर (!(stat & FE_HAS_LOCK)) अणु
		c->cnr.len = 1;
		c->block_count.len = 1;
		c->block_error.len = 1;
		c->post_bit_error.len = 1;
		c->post_bit_count.len = 1;
		c->cnr.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
		c->post_bit_error.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
		c->post_bit_count.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
		c->block_error.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
		c->block_count.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
		वापस 0;
	पूर्ण

	/* Check अगर समय क्रम stats was elapsed */
	अगर (समय_after(jअगरfies, state->per_jअगरfies_stats)) अणु
		state->per_jअगरfies_stats = jअगरfies + msecs_to_jअगरfies(1000);

		/* Get SNR */
		snr = dib7000p_get_snr(demod);
		अगर (snr)
			snr = (1000L * snr) >> 24;
		अन्यथा
			snr = 0;
		c->cnr.stat[0].svalue = snr;
		c->cnr.stat[0].scale = FE_SCALE_DECIBEL;

		/* Get UCB measures */
		dib7000p_पढ़ो_unc_blocks(demod, &val);
		ucb = val - state->old_ucb;
		अगर (val < state->old_ucb)
			ucb += 0x100000000LL;

		c->block_error.stat[0].scale = FE_SCALE_COUNTER;
		c->block_error.stat[0].uvalue = ucb;

		/* Estimate the number of packets based on bitrate */
		अगर (!समय_us)
			समय_us = dib7000p_get_समय_us(demod);

		अगर (समय_us) अणु
			blocks = 1250000ULL * 1000000ULL;
			करो_भाग(blocks, समय_us * 8 * 204);
			c->block_count.stat[0].scale = FE_SCALE_COUNTER;
			c->block_count.stat[0].uvalue += blocks;
		पूर्ण

		show_per_stats = 1;
	पूर्ण

	/* Get post-BER measures */
	अगर (समय_after(jअगरfies, state->ber_jअगरfies_stats)) अणु
		समय_us = dib7000p_get_समय_us(demod);
		state->ber_jअगरfies_stats = jअगरfies + msecs_to_jअगरfies((समय_us + 500) / 1000);

		dprपूर्णांकk("Next all layers stats available in %u us.\n", समय_us);

		dib7000p_पढ़ो_ber(demod, &val);
		c->post_bit_error.stat[0].scale = FE_SCALE_COUNTER;
		c->post_bit_error.stat[0].uvalue += val;

		c->post_bit_count.stat[0].scale = FE_SCALE_COUNTER;
		c->post_bit_count.stat[0].uvalue += 100000000;
	पूर्ण

	/* Get PER measures */
	अगर (show_per_stats) अणु
		dib7000p_पढ़ो_unc_blocks(demod, &val);

		c->block_error.stat[0].scale = FE_SCALE_COUNTER;
		c->block_error.stat[0].uvalue += val;

		समय_us = dib7000p_get_समय_us(demod);
		अगर (समय_us) अणु
			blocks = 1250000ULL * 1000000ULL;
			करो_भाग(blocks, समय_us * 8 * 204);
			c->block_count.stat[0].scale = FE_SCALE_COUNTER;
			c->block_count.stat[0].uvalue += blocks;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक dib7000p_fe_get_tune_settings(काष्ठा dvb_frontend *fe, काष्ठा dvb_frontend_tune_settings *tune)
अणु
	tune->min_delay_ms = 1000;
	वापस 0;
पूर्ण

अटल व्योम dib7000p_release(काष्ठा dvb_frontend *demod)
अणु
	काष्ठा dib7000p_state *st = demod->demodulator_priv;
	dibx000_निकास_i2c_master(&st->i2c_master);
	i2c_del_adapter(&st->dib7090_tuner_adap);
	kमुक्त(st);
पूर्ण

अटल पूर्णांक dib7000pc_detection(काष्ठा i2c_adapter *i2c_adap)
अणु
	u8 *tx, *rx;
	काष्ठा i2c_msg msg[2] = अणु
		अणु.addr = 18 >> 1, .flags = 0, .len = 2पूर्ण,
		अणु.addr = 18 >> 1, .flags = I2C_M_RD, .len = 2पूर्ण,
	पूर्ण;
	पूर्णांक ret = 0;

	tx = kzalloc(2, GFP_KERNEL);
	अगर (!tx)
		वापस -ENOMEM;
	rx = kzalloc(2, GFP_KERNEL);
	अगर (!rx) अणु
		ret = -ENOMEM;
		जाओ rx_memory_error;
	पूर्ण

	msg[0].buf = tx;
	msg[1].buf = rx;

	tx[0] = 0x03;
	tx[1] = 0x00;

	अगर (i2c_transfer(i2c_adap, msg, 2) == 2)
		अगर (rx[0] == 0x01 && rx[1] == 0xb3) अणु
			dprपूर्णांकk("-D-  DiB7000PC detected\n");
			ret = 1;
			जाओ out;
		पूर्ण

	msg[0].addr = msg[1].addr = 0x40;

	अगर (i2c_transfer(i2c_adap, msg, 2) == 2)
		अगर (rx[0] == 0x01 && rx[1] == 0xb3) अणु
			dprपूर्णांकk("-D-  DiB7000PC detected\n");
			ret = 1;
			जाओ out;
		पूर्ण

	dprपूर्णांकk("-D-  DiB7000PC not detected\n");

out:
	kमुक्त(rx);
rx_memory_error:
	kमुक्त(tx);
	वापस ret;
पूर्ण

अटल काष्ठा i2c_adapter *dib7000p_get_i2c_master(काष्ठा dvb_frontend *demod, क्रमागत dibx000_i2c_पूर्णांकerface पूर्णांकf, पूर्णांक gating)
अणु
	काष्ठा dib7000p_state *st = demod->demodulator_priv;
	वापस dibx000_get_i2c_adapter(&st->i2c_master, पूर्णांकf, gating);
पूर्ण

अटल पूर्णांक dib7000p_pid_filter_ctrl(काष्ठा dvb_frontend *fe, u8 onoff)
अणु
	काष्ठा dib7000p_state *state = fe->demodulator_priv;
	u16 val = dib7000p_पढ़ो_word(state, 235) & 0xffef;
	val |= (onoff & 0x1) << 4;
	dprपूर्णांकk("PID filter enabled %d\n", onoff);
	वापस dib7000p_ग_लिखो_word(state, 235, val);
पूर्ण

अटल पूर्णांक dib7000p_pid_filter(काष्ठा dvb_frontend *fe, u8 id, u16 pid, u8 onoff)
अणु
	काष्ठा dib7000p_state *state = fe->demodulator_priv;
	dprपूर्णांकk("PID filter: index %x, PID %d, OnOff %d\n", id, pid, onoff);
	वापस dib7000p_ग_लिखो_word(state, 241 + id, onoff ? (1 << 13) | pid : 0);
पूर्ण

अटल पूर्णांक dib7000p_i2c_क्रमागतeration(काष्ठा i2c_adapter *i2c, पूर्णांक no_of_demods, u8 शेष_addr, काष्ठा dib7000p_config cfg[])
अणु
	काष्ठा dib7000p_state *dpst;
	पूर्णांक k = 0;
	u8 new_addr = 0;

	dpst = kzalloc(माप(काष्ठा dib7000p_state), GFP_KERNEL);
	अगर (!dpst)
		वापस -ENOMEM;

	dpst->i2c_adap = i2c;
	mutex_init(&dpst->i2c_buffer_lock);

	क्रम (k = no_of_demods - 1; k >= 0; k--) अणु
		dpst->cfg = cfg[k];

		/* designated i2c address */
		अगर (cfg[k].शेष_i2c_addr != 0)
			new_addr = cfg[k].शेष_i2c_addr + (k << 1);
		अन्यथा
			new_addr = (0x40 + k) << 1;
		dpst->i2c_addr = new_addr;
		dib7000p_ग_लिखो_word(dpst, 1287, 0x0003);	/* sram lead in, rdy */
		अगर (dib7000p_identअगरy(dpst) != 0) अणु
			dpst->i2c_addr = शेष_addr;
			dib7000p_ग_लिखो_word(dpst, 1287, 0x0003);	/* sram lead in, rdy */
			अगर (dib7000p_identअगरy(dpst) != 0) अणु
				dprपूर्णांकk("DiB7000P #%d: not identified\n", k);
				kमुक्त(dpst);
				वापस -EIO;
			पूर्ण
		पूर्ण

		/* start भागersity to pull_करोwn भाग_str - just क्रम i2c-क्रमागतeration */
		dib7000p_set_output_mode(dpst, OUTMODE_DIVERSITY);

		/* set new i2c address and क्रमce भागstart */
		dib7000p_ग_लिखो_word(dpst, 1285, (new_addr << 2) | 0x2);

		dprपूर्णांकk("IC %d initialized (to i2c_address 0x%x)\n", k, new_addr);
	पूर्ण

	क्रम (k = 0; k < no_of_demods; k++) अणु
		dpst->cfg = cfg[k];
		अगर (cfg[k].शेष_i2c_addr != 0)
			dpst->i2c_addr = (cfg[k].शेष_i2c_addr + k) << 1;
		अन्यथा
			dpst->i2c_addr = (0x40 + k) << 1;

		// unक्रमce भागstr
		dib7000p_ग_लिखो_word(dpst, 1285, dpst->i2c_addr << 2);

		/* deactivate भाग - it was just क्रम i2c-क्रमागतeration */
		dib7000p_set_output_mode(dpst, OUTMODE_HIGH_Z);
	पूर्ण

	kमुक्त(dpst);
	वापस 0;
पूर्ण

अटल स्थिर s32 lut_1000ln_mant[] = अणु
	6908, 6956, 7003, 7047, 7090, 7131, 7170, 7208, 7244, 7279, 7313, 7346, 7377, 7408, 7438, 7467, 7495, 7523, 7549, 7575, 7600
पूर्ण;

अटल s32 dib7000p_get_adc_घातer(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dib7000p_state *state = fe->demodulator_priv;
	u32 पंचांगp_val = 0, exp = 0, mant = 0;
	s32 घात_i;
	u16 buf[2];
	u8 ix = 0;

	buf[0] = dib7000p_पढ़ो_word(state, 0x184);
	buf[1] = dib7000p_पढ़ो_word(state, 0x185);
	घात_i = (buf[0] << 16) | buf[1];
	dprपूर्णांकk("raw pow_i = %d\n", घात_i);

	पंचांगp_val = घात_i;
	जबतक (पंचांगp_val >>= 1)
		exp++;

	mant = (घात_i * 1000 / (1 << exp));
	dprपूर्णांकk(" mant = %d exp = %d\n", mant / 1000, exp);

	ix = (u8) ((mant - 1000) / 100);	/* index of the LUT */
	dprपूर्णांकk(" ix = %d\n", ix);

	घात_i = (lut_1000ln_mant[ix] + 693 * (exp - 20) - 6908);
	घात_i = (घात_i << 8) / 1000;
	dprपूर्णांकk(" pow_i = %d\n", घात_i);

	वापस घात_i;
पूर्ण

अटल पूर्णांक map_addr_to_serpar_number(काष्ठा i2c_msg *msg)
अणु
	अगर ((msg->buf[0] <= 15))
		msg->buf[0] -= 1;
	अन्यथा अगर (msg->buf[0] == 17)
		msg->buf[0] = 15;
	अन्यथा अगर (msg->buf[0] == 16)
		msg->buf[0] = 17;
	अन्यथा अगर (msg->buf[0] == 19)
		msg->buf[0] = 16;
	अन्यथा अगर (msg->buf[0] >= 21 && msg->buf[0] <= 25)
		msg->buf[0] -= 3;
	अन्यथा अगर (msg->buf[0] == 28)
		msg->buf[0] = 23;
	अन्यथा
		वापस -EINVAL;
	वापस 0;
पूर्ण

अटल पूर्णांक w7090p_tuner_ग_लिखो_serpar(काष्ठा i2c_adapter *i2c_adap, काष्ठा i2c_msg msg[], पूर्णांक num)
अणु
	काष्ठा dib7000p_state *state = i2c_get_adapdata(i2c_adap);
	u8 n_overflow = 1;
	u16 i = 1000;
	u16 serpar_num = msg[0].buf[0];

	जबतक (n_overflow == 1 && i) अणु
		n_overflow = (dib7000p_पढ़ो_word(state, 1984) >> 1) & 0x1;
		i--;
		अगर (i == 0)
			dprपूर्णांकk("Tuner ITF: write busy (overflow)\n");
	पूर्ण
	dib7000p_ग_लिखो_word(state, 1985, (1 << 6) | (serpar_num & 0x3f));
	dib7000p_ग_लिखो_word(state, 1986, (msg[0].buf[1] << 8) | msg[0].buf[2]);

	वापस num;
पूर्ण

अटल पूर्णांक w7090p_tuner_पढ़ो_serpar(काष्ठा i2c_adapter *i2c_adap, काष्ठा i2c_msg msg[], पूर्णांक num)
अणु
	काष्ठा dib7000p_state *state = i2c_get_adapdata(i2c_adap);
	u8 n_overflow = 1, n_empty = 1;
	u16 i = 1000;
	u16 serpar_num = msg[0].buf[0];
	u16 पढ़ो_word;

	जबतक (n_overflow == 1 && i) अणु
		n_overflow = (dib7000p_पढ़ो_word(state, 1984) >> 1) & 0x1;
		i--;
		अगर (i == 0)
			dprपूर्णांकk("TunerITF: read busy (overflow)\n");
	पूर्ण
	dib7000p_ग_लिखो_word(state, 1985, (0 << 6) | (serpar_num & 0x3f));

	i = 1000;
	जबतक (n_empty == 1 && i) अणु
		n_empty = dib7000p_पढ़ो_word(state, 1984) & 0x1;
		i--;
		अगर (i == 0)
			dprपूर्णांकk("TunerITF: read busy (empty)\n");
	पूर्ण
	पढ़ो_word = dib7000p_पढ़ो_word(state, 1987);
	msg[1].buf[0] = (पढ़ो_word >> 8) & 0xff;
	msg[1].buf[1] = (पढ़ो_word) & 0xff;

	वापस num;
पूर्ण

अटल पूर्णांक w7090p_tuner_rw_serpar(काष्ठा i2c_adapter *i2c_adap, काष्ठा i2c_msg msg[], पूर्णांक num)
अणु
	अगर (map_addr_to_serpar_number(&msg[0]) == 0) अणु	/* अन्यथा = Tuner regs to ignore : DIG_CFG, CTRL_RF_LT, PLL_CFG, PWM1_REG, ADCCLK, DIG_CFG_3; SLEEP_EN... */
		अगर (num == 1) अणु	/* ग_लिखो */
			वापस w7090p_tuner_ग_लिखो_serpar(i2c_adap, msg, 1);
		पूर्ण अन्यथा अणु	/* पढ़ो */
			वापस w7090p_tuner_पढ़ो_serpar(i2c_adap, msg, 2);
		पूर्ण
	पूर्ण
	वापस num;
पूर्ण

अटल पूर्णांक dib7090p_rw_on_apb(काष्ठा i2c_adapter *i2c_adap,
		काष्ठा i2c_msg msg[], पूर्णांक num, u16 apb_address)
अणु
	काष्ठा dib7000p_state *state = i2c_get_adapdata(i2c_adap);
	u16 word;

	अगर (num == 1) अणु		/* ग_लिखो */
		dib7000p_ग_लिखो_word(state, apb_address, ((msg[0].buf[1] << 8) | (msg[0].buf[2])));
	पूर्ण अन्यथा अणु
		word = dib7000p_पढ़ो_word(state, apb_address);
		msg[1].buf[0] = (word >> 8) & 0xff;
		msg[1].buf[1] = (word) & 0xff;
	पूर्ण

	वापस num;
पूर्ण

अटल पूर्णांक dib7090_tuner_xfer(काष्ठा i2c_adapter *i2c_adap, काष्ठा i2c_msg msg[], पूर्णांक num)
अणु
	काष्ठा dib7000p_state *state = i2c_get_adapdata(i2c_adap);

	u16 apb_address = 0, word;
	पूर्णांक i = 0;
	चयन (msg[0].buf[0]) अणु
	हाल 0x12:
		apb_address = 1920;
		अवरोध;
	हाल 0x14:
		apb_address = 1921;
		अवरोध;
	हाल 0x24:
		apb_address = 1922;
		अवरोध;
	हाल 0x1a:
		apb_address = 1923;
		अवरोध;
	हाल 0x22:
		apb_address = 1924;
		अवरोध;
	हाल 0x33:
		apb_address = 1926;
		अवरोध;
	हाल 0x34:
		apb_address = 1927;
		अवरोध;
	हाल 0x35:
		apb_address = 1928;
		अवरोध;
	हाल 0x36:
		apb_address = 1929;
		अवरोध;
	हाल 0x37:
		apb_address = 1930;
		अवरोध;
	हाल 0x38:
		apb_address = 1931;
		अवरोध;
	हाल 0x39:
		apb_address = 1932;
		अवरोध;
	हाल 0x2a:
		apb_address = 1935;
		अवरोध;
	हाल 0x2b:
		apb_address = 1936;
		अवरोध;
	हाल 0x2c:
		apb_address = 1937;
		अवरोध;
	हाल 0x2d:
		apb_address = 1938;
		अवरोध;
	हाल 0x2e:
		apb_address = 1939;
		अवरोध;
	हाल 0x2f:
		apb_address = 1940;
		अवरोध;
	हाल 0x30:
		apb_address = 1941;
		अवरोध;
	हाल 0x31:
		apb_address = 1942;
		अवरोध;
	हाल 0x32:
		apb_address = 1943;
		अवरोध;
	हाल 0x3e:
		apb_address = 1944;
		अवरोध;
	हाल 0x3f:
		apb_address = 1945;
		अवरोध;
	हाल 0x40:
		apb_address = 1948;
		अवरोध;
	हाल 0x25:
		apb_address = 914;
		अवरोध;
	हाल 0x26:
		apb_address = 915;
		अवरोध;
	हाल 0x27:
		apb_address = 917;
		अवरोध;
	हाल 0x28:
		apb_address = 916;
		अवरोध;
	हाल 0x1d:
		i = ((dib7000p_पढ़ो_word(state, 72) >> 12) & 0x3);
		word = dib7000p_पढ़ो_word(state, 384 + i);
		msg[1].buf[0] = (word >> 8) & 0xff;
		msg[1].buf[1] = (word) & 0xff;
		वापस num;
	हाल 0x1f:
		अगर (num == 1) अणु	/* ग_लिखो */
			word = (u16) ((msg[0].buf[1] << 8) | msg[0].buf[2]);
			word &= 0x3;
			word = (dib7000p_पढ़ो_word(state, 72) & ~(3 << 12)) | (word << 12);
			dib7000p_ग_लिखो_word(state, 72, word);	/* Set the proper input */
			वापस num;
		पूर्ण
	पूर्ण

	अगर (apb_address != 0)	/* R/W access via APB */
		वापस dib7090p_rw_on_apb(i2c_adap, msg, num, apb_address);
	अन्यथा			/* R/W access via SERPAR  */
		वापस w7090p_tuner_rw_serpar(i2c_adap, msg, num);

	वापस 0;
पूर्ण

अटल u32 dib7000p_i2c_func(काष्ठा i2c_adapter *adapter)
अणु
	वापस I2C_FUNC_I2C;
पूर्ण

अटल स्थिर काष्ठा i2c_algorithm dib7090_tuner_xfer_algo = अणु
	.master_xfer = dib7090_tuner_xfer,
	.functionality = dib7000p_i2c_func,
पूर्ण;

अटल काष्ठा i2c_adapter *dib7090_get_i2c_tuner(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dib7000p_state *st = fe->demodulator_priv;
	वापस &st->dib7090_tuner_adap;
पूर्ण

अटल पूर्णांक dib7090_host_bus_drive(काष्ठा dib7000p_state *state, u8 drive)
अणु
	u16 reg;

	/* drive host bus 2, 3, 4 */
	reg = dib7000p_पढ़ो_word(state, 1798) & ~((0x7) | (0x7 << 6) | (0x7 << 12));
	reg |= (drive << 12) | (drive << 6) | drive;
	dib7000p_ग_लिखो_word(state, 1798, reg);

	/* drive host bus 5,6 */
	reg = dib7000p_पढ़ो_word(state, 1799) & ~((0x7 << 2) | (0x7 << 8));
	reg |= (drive << 8) | (drive << 2);
	dib7000p_ग_लिखो_word(state, 1799, reg);

	/* drive host bus 7, 8, 9 */
	reg = dib7000p_पढ़ो_word(state, 1800) & ~((0x7) | (0x7 << 6) | (0x7 << 12));
	reg |= (drive << 12) | (drive << 6) | drive;
	dib7000p_ग_लिखो_word(state, 1800, reg);

	/* drive host bus 10, 11 */
	reg = dib7000p_पढ़ो_word(state, 1801) & ~((0x7 << 2) | (0x7 << 8));
	reg |= (drive << 8) | (drive << 2);
	dib7000p_ग_लिखो_word(state, 1801, reg);

	/* drive host bus 12, 13, 14 */
	reg = dib7000p_पढ़ो_word(state, 1802) & ~((0x7) | (0x7 << 6) | (0x7 << 12));
	reg |= (drive << 12) | (drive << 6) | drive;
	dib7000p_ग_लिखो_word(state, 1802, reg);

	वापस 0;
पूर्ण

अटल u32 dib7090_calcSyncFreq(u32 P_Kin, u32 P_Kout, u32 insertExtSynchro, u32 syncSize)
अणु
	u32 quantअगर = 3;
	u32 nom = (insertExtSynchro * P_Kin + syncSize);
	u32 denom = P_Kout;
	u32 syncFreq = ((nom << quantअगर) / denom);

	अगर ((syncFreq & ((1 << quantअगर) - 1)) != 0)
		syncFreq = (syncFreq >> quantअगर) + 1;
	अन्यथा
		syncFreq = (syncFreq >> quantअगर);

	अगर (syncFreq != 0)
		syncFreq = syncFreq - 1;

	वापस syncFreq;
पूर्ण

अटल पूर्णांक dib7090_cfg_DibTx(काष्ठा dib7000p_state *state, u32 P_Kin, u32 P_Kout, u32 insertExtSynchro, u32 synchroMode, u32 syncWord, u32 syncSize)
अणु
	dprपूर्णांकk("Configure DibStream Tx\n");

	dib7000p_ग_लिखो_word(state, 1615, 1);
	dib7000p_ग_लिखो_word(state, 1603, P_Kin);
	dib7000p_ग_लिखो_word(state, 1605, P_Kout);
	dib7000p_ग_लिखो_word(state, 1606, insertExtSynchro);
	dib7000p_ग_लिखो_word(state, 1608, synchroMode);
	dib7000p_ग_लिखो_word(state, 1609, (syncWord >> 16) & 0xffff);
	dib7000p_ग_लिखो_word(state, 1610, syncWord & 0xffff);
	dib7000p_ग_लिखो_word(state, 1612, syncSize);
	dib7000p_ग_लिखो_word(state, 1615, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक dib7090_cfg_DibRx(काष्ठा dib7000p_state *state, u32 P_Kin, u32 P_Kout, u32 synchroMode, u32 insertExtSynchro, u32 syncWord, u32 syncSize,
		u32 dataOutRate)
अणु
	u32 syncFreq;

	dprपूर्णांकk("Configure DibStream Rx\n");
	अगर ((P_Kin != 0) && (P_Kout != 0)) अणु
		syncFreq = dib7090_calcSyncFreq(P_Kin, P_Kout, insertExtSynchro, syncSize);
		dib7000p_ग_लिखो_word(state, 1542, syncFreq);
	पूर्ण
	dib7000p_ग_लिखो_word(state, 1554, 1);
	dib7000p_ग_लिखो_word(state, 1536, P_Kin);
	dib7000p_ग_लिखो_word(state, 1537, P_Kout);
	dib7000p_ग_लिखो_word(state, 1539, synchroMode);
	dib7000p_ग_लिखो_word(state, 1540, (syncWord >> 16) & 0xffff);
	dib7000p_ग_लिखो_word(state, 1541, syncWord & 0xffff);
	dib7000p_ग_लिखो_word(state, 1543, syncSize);
	dib7000p_ग_लिखो_word(state, 1544, dataOutRate);
	dib7000p_ग_लिखो_word(state, 1554, 0);

	वापस 0;
पूर्ण

अटल व्योम dib7090_enMpegMux(काष्ठा dib7000p_state *state, पूर्णांक onoff)
अणु
	u16 reg_1287 = dib7000p_पढ़ो_word(state, 1287);

	चयन (onoff) अणु
	हाल 1:
			reg_1287 &= ~(1<<7);
			अवरोध;
	हाल 0:
			reg_1287 |= (1<<7);
			अवरोध;
	पूर्ण

	dib7000p_ग_लिखो_word(state, 1287, reg_1287);
पूर्ण

अटल व्योम dib7090_configMpegMux(काष्ठा dib7000p_state *state,
		u16 pulseWidth, u16 enSerialMode, u16 enSerialClkDiv2)
अणु
	dprपूर्णांकk("Enable Mpeg mux\n");

	dib7090_enMpegMux(state, 0);

	/* If the input mode is MPEG करो not भागide the serial घड़ी */
	अगर ((enSerialMode == 1) && (state->input_mode_mpeg == 1))
		enSerialClkDiv2 = 0;

	dib7000p_ग_लिखो_word(state, 1287, ((pulseWidth & 0x1f) << 2)
			| ((enSerialMode & 0x1) << 1)
			| (enSerialClkDiv2 & 0x1));

	dib7090_enMpegMux(state, 1);
पूर्ण

अटल व्योम dib7090_setDibTxMux(काष्ठा dib7000p_state *state, पूर्णांक mode)
अणु
	u16 reg_1288 = dib7000p_पढ़ो_word(state, 1288) & ~(0x7 << 7);

	चयन (mode) अणु
	हाल MPEG_ON_DIBTX:
			dprपूर्णांकk("SET MPEG ON DIBSTREAM TX\n");
			dib7090_cfg_DibTx(state, 8, 5, 0, 0, 0, 0);
			reg_1288 |= (1<<9);
			अवरोध;
	हाल DIV_ON_DIBTX:
			dprपूर्णांकk("SET DIV_OUT ON DIBSTREAM TX\n");
			dib7090_cfg_DibTx(state, 5, 5, 0, 0, 0, 0);
			reg_1288 |= (1<<8);
			अवरोध;
	हाल ADC_ON_DIBTX:
			dprपूर्णांकk("SET ADC_OUT ON DIBSTREAM TX\n");
			dib7090_cfg_DibTx(state, 20, 5, 10, 0, 0, 0);
			reg_1288 |= (1<<7);
			अवरोध;
	शेष:
			अवरोध;
	पूर्ण
	dib7000p_ग_लिखो_word(state, 1288, reg_1288);
पूर्ण

अटल व्योम dib7090_setHostBusMux(काष्ठा dib7000p_state *state, पूर्णांक mode)
अणु
	u16 reg_1288 = dib7000p_पढ़ो_word(state, 1288) & ~(0x7 << 4);

	चयन (mode) अणु
	हाल DEMOUT_ON_HOSTBUS:
			dprपूर्णांकk("SET DEM OUT OLD INTERF ON HOST BUS\n");
			dib7090_enMpegMux(state, 0);
			reg_1288 |= (1<<6);
			अवरोध;
	हाल DIBTX_ON_HOSTBUS:
			dprपूर्णांकk("SET DIBSTREAM TX ON HOST BUS\n");
			dib7090_enMpegMux(state, 0);
			reg_1288 |= (1<<5);
			अवरोध;
	हाल MPEG_ON_HOSTBUS:
			dprपूर्णांकk("SET MPEG MUX ON HOST BUS\n");
			reg_1288 |= (1<<4);
			अवरोध;
	शेष:
			अवरोध;
	पूर्ण
	dib7000p_ग_लिखो_word(state, 1288, reg_1288);
पूर्ण

अटल पूर्णांक dib7090_set_भागersity_in(काष्ठा dvb_frontend *fe, पूर्णांक onoff)
अणु
	काष्ठा dib7000p_state *state = fe->demodulator_priv;
	u16 reg_1287;

	चयन (onoff) अणु
	हाल 0: /* only use the पूर्णांकernal way - not the भागersity input */
			dprपूर्णांकk("%s mode OFF : by default Enable Mpeg INPUT\n", __func__);
			dib7090_cfg_DibRx(state, 8, 5, 0, 0, 0, 8, 0);

			/* Do not भागide the serial घड़ी of MPEG MUX */
			/* in SERIAL MODE in हाल input mode MPEG is used */
			reg_1287 = dib7000p_पढ़ो_word(state, 1287);
			/* enSerialClkDiv2 == 1 ? */
			अगर ((reg_1287 & 0x1) == 1) अणु
				/* क्रमce enSerialClkDiv2 = 0 */
				reg_1287 &= ~0x1;
				dib7000p_ग_लिखो_word(state, 1287, reg_1287);
			पूर्ण
			state->input_mode_mpeg = 1;
			अवरोध;
	हाल 1: /* both ways */
	हाल 2: /* only the भागersity input */
			dprपूर्णांकk("%s ON : Enable diversity INPUT\n", __func__);
			dib7090_cfg_DibRx(state, 5, 5, 0, 0, 0, 0, 0);
			state->input_mode_mpeg = 0;
			अवरोध;
	पूर्ण

	dib7000p_set_भागersity_in(&state->demod, onoff);
	वापस 0;
पूर्ण

अटल पूर्णांक dib7090_set_output_mode(काष्ठा dvb_frontend *fe, पूर्णांक mode)
अणु
	काष्ठा dib7000p_state *state = fe->demodulator_priv;

	u16 outreg, smo_mode, fअगरo_threshold;
	u8 prefer_mpeg_mux_use = 1;
	पूर्णांक ret = 0;

	dib7090_host_bus_drive(state, 1);

	fअगरo_threshold = 1792;
	smo_mode = (dib7000p_पढ़ो_word(state, 235) & 0x0050) | (1 << 1);
	outreg = dib7000p_पढ़ो_word(state, 1286) & ~((1 << 10) | (0x7 << 6) | (1 << 1));

	चयन (mode) अणु
	हाल OUTMODE_HIGH_Z:
		outreg = 0;
		अवरोध;

	हाल OUTMODE_MPEG2_SERIAL:
		अगर (prefer_mpeg_mux_use) अणु
			dprपूर्णांकk("setting output mode TS_SERIAL using Mpeg Mux\n");
			dib7090_configMpegMux(state, 3, 1, 1);
			dib7090_setHostBusMux(state, MPEG_ON_HOSTBUS);
		पूर्ण अन्यथा अणु/* Use Smooth block */
			dprपूर्णांकk("setting output mode TS_SERIAL using Smooth bloc\n");
			dib7090_setHostBusMux(state, DEMOUT_ON_HOSTBUS);
			outreg |= (2<<6) | (0 << 1);
		पूर्ण
		अवरोध;

	हाल OUTMODE_MPEG2_PAR_GATED_CLK:
		अगर (prefer_mpeg_mux_use) अणु
			dprपूर्णांकk("setting output mode TS_PARALLEL_GATED using Mpeg Mux\n");
			dib7090_configMpegMux(state, 2, 0, 0);
			dib7090_setHostBusMux(state, MPEG_ON_HOSTBUS);
		पूर्ण अन्यथा अणु /* Use Smooth block */
			dprपूर्णांकk("setting output mode TS_PARALLEL_GATED using Smooth block\n");
			dib7090_setHostBusMux(state, DEMOUT_ON_HOSTBUS);
			outreg |= (0<<6);
		पूर्ण
		अवरोध;

	हाल OUTMODE_MPEG2_PAR_CONT_CLK:	/* Using Smooth block only */
		dprपूर्णांकk("setting output mode TS_PARALLEL_CONT using Smooth block\n");
		dib7090_setHostBusMux(state, DEMOUT_ON_HOSTBUS);
		outreg |= (1<<6);
		अवरोध;

	हाल OUTMODE_MPEG2_FIFO:	/* Using Smooth block because not supported by new Mpeg Mux bloc */
		dprपूर्णांकk("setting output mode TS_FIFO using Smooth block\n");
		dib7090_setHostBusMux(state, DEMOUT_ON_HOSTBUS);
		outreg |= (5<<6);
		smo_mode |= (3 << 1);
		fअगरo_threshold = 512;
		अवरोध;

	हाल OUTMODE_DIVERSITY:
		dprपूर्णांकk("setting output mode MODE_DIVERSITY\n");
		dib7090_setDibTxMux(state, DIV_ON_DIBTX);
		dib7090_setHostBusMux(state, DIBTX_ON_HOSTBUS);
		अवरोध;

	हाल OUTMODE_ANALOG_ADC:
		dprपूर्णांकk("setting output mode MODE_ANALOG_ADC\n");
		dib7090_setDibTxMux(state, ADC_ON_DIBTX);
		dib7090_setHostBusMux(state, DIBTX_ON_HOSTBUS);
		अवरोध;
	पूर्ण
	अगर (mode != OUTMODE_HIGH_Z)
		outreg |= (1 << 10);

	अगर (state->cfg.output_mpeg2_in_188_bytes)
		smo_mode |= (1 << 5);

	ret |= dib7000p_ग_लिखो_word(state, 235, smo_mode);
	ret |= dib7000p_ग_लिखो_word(state, 236, fअगरo_threshold);	/* synchronous ख_पढ़ो */
	ret |= dib7000p_ग_लिखो_word(state, 1286, outreg);

	वापस ret;
पूर्ण

अटल पूर्णांक dib7090_tuner_sleep(काष्ठा dvb_frontend *fe, पूर्णांक onoff)
अणु
	काष्ठा dib7000p_state *state = fe->demodulator_priv;
	u16 en_cur_state;

	dprपूर्णांकk("sleep dib7090: %d\n", onoff);

	en_cur_state = dib7000p_पढ़ो_word(state, 1922);

	अगर (en_cur_state > 0xff)
		state->tuner_enable = en_cur_state;

	अगर (onoff)
		en_cur_state &= 0x00ff;
	अन्यथा अणु
		अगर (state->tuner_enable != 0)
			en_cur_state = state->tuner_enable;
	पूर्ण

	dib7000p_ग_लिखो_word(state, 1922, en_cur_state);

	वापस 0;
पूर्ण

अटल पूर्णांक dib7090_get_adc_घातer(काष्ठा dvb_frontend *fe)
अणु
	वापस dib7000p_get_adc_घातer(fe);
पूर्ण

अटल पूर्णांक dib7090_slave_reset(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dib7000p_state *state = fe->demodulator_priv;
	u16 reg;

	reg = dib7000p_पढ़ो_word(state, 1794);
	dib7000p_ग_लिखो_word(state, 1794, reg | (4 << 12));

	dib7000p_ग_लिखो_word(state, 1032, 0xffff);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dvb_frontend_ops dib7000p_ops;
अटल काष्ठा dvb_frontend *dib7000p_init(काष्ठा i2c_adapter *i2c_adap, u8 i2c_addr, काष्ठा dib7000p_config *cfg)
अणु
	काष्ठा dvb_frontend *demod;
	काष्ठा dib7000p_state *st;
	st = kzalloc(माप(काष्ठा dib7000p_state), GFP_KERNEL);
	अगर (st == शून्य)
		वापस शून्य;

	स_नकल(&st->cfg, cfg, माप(काष्ठा dib7000p_config));
	st->i2c_adap = i2c_adap;
	st->i2c_addr = i2c_addr;
	st->gpio_val = cfg->gpio_val;
	st->gpio_dir = cfg->gpio_dir;

	/* Ensure the output mode reमुख्यs at the previous शेष अगर it's
	 * not specअगरically set by the caller.
	 */
	अगर ((st->cfg.output_mode != OUTMODE_MPEG2_SERIAL) && (st->cfg.output_mode != OUTMODE_MPEG2_PAR_GATED_CLK))
		st->cfg.output_mode = OUTMODE_MPEG2_FIFO;

	demod = &st->demod;
	demod->demodulator_priv = st;
	स_नकल(&st->demod.ops, &dib7000p_ops, माप(काष्ठा dvb_frontend_ops));
	mutex_init(&st->i2c_buffer_lock);

	dib7000p_ग_लिखो_word(st, 1287, 0x0003);	/* sram lead in, rdy */

	अगर (dib7000p_identअगरy(st) != 0)
		जाओ error;

	st->version = dib7000p_पढ़ो_word(st, 897);

	/* FIXME: make sure the dev.parent field is initialized, or अन्यथा
	   request_firmware() will hit an OOPS (this should be moved somewhere
	   more common) */
	st->i2c_master.gated_tuner_i2c_adap.dev.parent = i2c_adap->dev.parent;

	dibx000_init_i2c_master(&st->i2c_master, DIB7000P, st->i2c_adap, st->i2c_addr);

	/* init 7090 tuner adapter */
	strscpy(st->dib7090_tuner_adap.name, "DiB7090 tuner interface",
		माप(st->dib7090_tuner_adap.name));
	st->dib7090_tuner_adap.algo = &dib7090_tuner_xfer_algo;
	st->dib7090_tuner_adap.algo_data = शून्य;
	st->dib7090_tuner_adap.dev.parent = st->i2c_adap->dev.parent;
	i2c_set_adapdata(&st->dib7090_tuner_adap, st);
	i2c_add_adapter(&st->dib7090_tuner_adap);

	dib7000p_demod_reset(st);

	dib7000p_reset_stats(demod);

	अगर (st->version == SOC7090) अणु
		dib7090_set_output_mode(demod, st->cfg.output_mode);
		dib7090_set_भागersity_in(demod, 0);
	पूर्ण

	वापस demod;

error:
	kमुक्त(st);
	वापस शून्य;
पूर्ण

व्योम *dib7000p_attach(काष्ठा dib7000p_ops *ops)
अणु
	अगर (!ops)
		वापस शून्य;

	ops->slave_reset = dib7090_slave_reset;
	ops->get_adc_घातer = dib7090_get_adc_घातer;
	ops->dib7000pc_detection = dib7000pc_detection;
	ops->get_i2c_tuner = dib7090_get_i2c_tuner;
	ops->tuner_sleep = dib7090_tuner_sleep;
	ops->init = dib7000p_init;
	ops->set_agc1_min = dib7000p_set_agc1_min;
	ops->set_gpio = dib7000p_set_gpio;
	ops->i2c_क्रमागतeration = dib7000p_i2c_क्रमागतeration;
	ops->pid_filter = dib7000p_pid_filter;
	ops->pid_filter_ctrl = dib7000p_pid_filter_ctrl;
	ops->get_i2c_master = dib7000p_get_i2c_master;
	ops->update_pll = dib7000p_update_pll;
	ops->ctrl_timf = dib7000p_ctrl_timf;
	ops->get_agc_values = dib7000p_get_agc_values;
	ops->set_wbd_ref = dib7000p_set_wbd_ref;

	वापस ops;
पूर्ण
EXPORT_SYMBOL(dib7000p_attach);

अटल स्थिर काष्ठा dvb_frontend_ops dib7000p_ops = अणु
	.delsys = अणु SYS_DVBT पूर्ण,
	.info = अणु
		 .name = "DiBcom 7000PC",
		 .frequency_min_hz =  44250 * kHz,
		 .frequency_max_hz = 867250 * kHz,
		 .frequency_stepsize_hz = 62500,
		 .caps = FE_CAN_INVERSION_AUTO |
		 FE_CAN_FEC_1_2 | FE_CAN_FEC_2_3 | FE_CAN_FEC_3_4 |
		 FE_CAN_FEC_5_6 | FE_CAN_FEC_7_8 | FE_CAN_FEC_AUTO |
		 FE_CAN_QPSK | FE_CAN_QAM_16 | FE_CAN_QAM_64 | FE_CAN_QAM_AUTO |
		 FE_CAN_TRANSMISSION_MODE_AUTO | FE_CAN_GUARD_INTERVAL_AUTO | FE_CAN_RECOVER | FE_CAN_HIERARCHY_AUTO,
		 पूर्ण,

	.release = dib7000p_release,

	.init = dib7000p_wakeup,
	.sleep = dib7000p_sleep,

	.set_frontend = dib7000p_set_frontend,
	.get_tune_settings = dib7000p_fe_get_tune_settings,
	.get_frontend = dib7000p_get_frontend,

	.पढ़ो_status = dib7000p_पढ़ो_status,
	.पढ़ो_ber = dib7000p_पढ़ो_ber,
	.पढ़ो_संकेत_strength = dib7000p_पढ़ो_संकेत_strength,
	.पढ़ो_snr = dib7000p_पढ़ो_snr,
	.पढ़ो_ucblocks = dib7000p_पढ़ो_unc_blocks,
पूर्ण;

MODULE_AUTHOR("Olivier Grenie <olivie.grenie@parrot.com>");
MODULE_AUTHOR("Patrick Boettcher <patrick.boettcher@posteo.de>");
MODULE_DESCRIPTION("Driver for the DiBcom 7000PC COFDM demodulator");
MODULE_LICENSE("GPL");
