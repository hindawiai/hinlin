<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Linux-DVB Driver क्रम DiBcom's DiB7000M and
 *              first generation DiB7000P-demodulator-family.
 *
 * Copyright (C) 2005-7 DiBcom (http://www.dibcom.fr/)
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/i2c.h>
#समावेश <linux/mutex.h>

#समावेश <media/dvb_frontend.h>

#समावेश "dib7000m.h"

अटल पूर्णांक debug;
module_param(debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug, "turn on debugging (default: 0)");

#घोषणा dprपूर्णांकk(fmt, arg...) करो अणु					\
	अगर (debug)							\
		prपूर्णांकk(KERN_DEBUG pr_fmt("%s: " fmt),			\
		       __func__, ##arg);				\
पूर्ण जबतक (0)

काष्ठा dib7000m_state अणु
	काष्ठा dvb_frontend demod;
    काष्ठा dib7000m_config cfg;

	u8 i2c_addr;
	काष्ठा i2c_adapter   *i2c_adap;

	काष्ठा dibx000_i2c_master i2c_master;

/* offset is 1 in हाल of the 7000MC */
	u8 reg_offs;

	u16 wbd_ref;

	u8 current_band;
	u32 current_bandwidth;
	काष्ठा dibx000_agc_config *current_agc;
	u32 timf;
	u32 timf_शेष;
	u32 पूर्णांकernal_clk;

	u8 भाग_क्रमce_off : 1;
	u8 भाग_state : 1;
	u16 भाग_sync_रुको;

	u16 revision;

	u8 agc_state;

	/* क्रम the I2C transfer */
	काष्ठा i2c_msg msg[2];
	u8 i2c_ग_लिखो_buffer[4];
	u8 i2c_पढ़ो_buffer[2];
	काष्ठा mutex i2c_buffer_lock;
पूर्ण;

क्रमागत dib7000m_घातer_mode अणु
	DIB7000M_POWER_ALL = 0,

	DIB7000M_POWER_NO,
	DIB7000M_POWER_INTERF_ANALOG_AGC,
	DIB7000M_POWER_COR4_DINTLV_ICIRM_EQUAL_CFROD,
	DIB7000M_POWER_COR4_CRY_ESRAM_MOUT_NUD,
	DIB7000M_POWER_INTERFACE_ONLY,
पूर्ण;

अटल u16 dib7000m_पढ़ो_word(काष्ठा dib7000m_state *state, u16 reg)
अणु
	u16 ret;

	अगर (mutex_lock_पूर्णांकerruptible(&state->i2c_buffer_lock) < 0) अणु
		dprपूर्णांकk("could not acquire lock\n");
		वापस 0;
	पूर्ण

	state->i2c_ग_लिखो_buffer[0] = (reg >> 8) | 0x80;
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

अटल पूर्णांक dib7000m_ग_लिखो_word(काष्ठा dib7000m_state *state, u16 reg, u16 val)
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
अटल व्योम dib7000m_ग_लिखो_tab(काष्ठा dib7000m_state *state, u16 *buf)
अणु
	u16 l = 0, r, *n;
	n = buf;
	l = *n++;
	जबतक (l) अणु
		r = *n++;

		अगर (state->reg_offs && (r >= 112 && r <= 331)) // compensate क्रम 7000MC
			r++;

		करो अणु
			dib7000m_ग_लिखो_word(state, r, *n++);
			r++;
		पूर्ण जबतक (--l);
		l = *n++;
	पूर्ण
पूर्ण

अटल पूर्णांक dib7000m_set_output_mode(काष्ठा dib7000m_state *state, पूर्णांक mode)
अणु
	पूर्णांक    ret = 0;
	u16 outreg, fअगरo_threshold, smo_mode,
		sram = 0x0005; /* by शेष SRAM output is disabled */

	outreg = 0;
	fअगरo_threshold = 1792;
	smo_mode = (dib7000m_पढ़ो_word(state, 294 + state->reg_offs) & 0x0010) | (1 << 1);

	dprपूर्णांकk("setting output mode for demod %p to %d\n", &state->demod, mode);

	चयन (mode) अणु
		हाल OUTMODE_MPEG2_PAR_GATED_CLK:   // STBs with parallel gated घड़ी
			outreg = (1 << 10);  /* 0x0400 */
			अवरोध;
		हाल OUTMODE_MPEG2_PAR_CONT_CLK:    // STBs with parallel जारीs घड़ी
			outreg = (1 << 10) | (1 << 6); /* 0x0440 */
			अवरोध;
		हाल OUTMODE_MPEG2_SERIAL:          // STBs with serial input
			outreg = (1 << 10) | (2 << 6) | (0 << 1); /* 0x0482 */
			अवरोध;
		हाल OUTMODE_DIVERSITY:
			अगर (state->cfg.hostbus_भागersity)
				outreg = (1 << 10) | (4 << 6); /* 0x0500 */
			अन्यथा
				sram   |= 0x0c00;
			अवरोध;
		हाल OUTMODE_MPEG2_FIFO:            // e.g. USB feeding
			smo_mode |= (3 << 1);
			fअगरo_threshold = 512;
			outreg = (1 << 10) | (5 << 6);
			अवरोध;
		हाल OUTMODE_HIGH_Z:  // disable
			outreg = 0;
			अवरोध;
		शेष:
			dprपूर्णांकk("Unhandled output_mode passed to be set for demod %p\n", &state->demod);
			अवरोध;
	पूर्ण

	अगर (state->cfg.output_mpeg2_in_188_bytes)
		smo_mode |= (1 << 5) ;

	ret |= dib7000m_ग_लिखो_word(state,  294 + state->reg_offs, smo_mode);
	ret |= dib7000m_ग_लिखो_word(state,  295 + state->reg_offs, fअगरo_threshold); /* synchronous ख_पढ़ो */
	ret |= dib7000m_ग_लिखो_word(state, 1795, outreg);
	ret |= dib7000m_ग_लिखो_word(state, 1805, sram);

	अगर (state->revision == 0x4003) अणु
		u16 clk_cfg1 = dib7000m_पढ़ो_word(state, 909) & 0xfffd;
		अगर (mode == OUTMODE_DIVERSITY)
			clk_cfg1 |= (1 << 1); // P_O_CLK_en
		dib7000m_ग_लिखो_word(state, 909, clk_cfg1);
	पूर्ण
	वापस ret;
पूर्ण

अटल व्योम dib7000m_set_घातer_mode(काष्ठा dib7000m_state *state, क्रमागत dib7000m_घातer_mode mode)
अणु
	/* by शेष everything is going to be घातered off */
	u16 reg_903 = 0xffff, reg_904 = 0xffff, reg_905 = 0xffff, reg_906  = 0x3fff;
	u8  offset = 0;

	/* now, depending on the requested mode, we घातer on */
	चयन (mode) अणु
		/* घातer up everything in the demod */
		हाल DIB7000M_POWER_ALL:
			reg_903 = 0x0000; reg_904 = 0x0000; reg_905 = 0x0000; reg_906 = 0x0000;
			अवरोध;

		/* just leave घातer on the control-पूर्णांकerfaces: GPIO and (I2C or SDIO or SRAM) */
		हाल DIB7000M_POWER_INTERFACE_ONLY: /* TODO घातer up either SDIO or I2C or SRAM */
			reg_905 &= ~((1 << 7) | (1 << 6) | (1 << 5) | (1 << 2));
			अवरोध;

		हाल DIB7000M_POWER_INTERF_ANALOG_AGC:
			reg_903 &= ~((1 << 15) | (1 << 14) | (1 << 11) | (1 << 10));
			reg_905 &= ~((1 << 7) | (1 << 6) | (1 << 5) | (1 << 4) | (1 << 2));
			reg_906 &= ~((1 << 0));
			अवरोध;

		हाल DIB7000M_POWER_COR4_DINTLV_ICIRM_EQUAL_CFROD:
			reg_903 = 0x0000; reg_904 = 0x801f; reg_905 = 0x0000; reg_906 = 0x0000;
			अवरोध;

		हाल DIB7000M_POWER_COR4_CRY_ESRAM_MOUT_NUD:
			reg_903 = 0x0000; reg_904 = 0x8000; reg_905 = 0x010b; reg_906 = 0x0000;
			अवरोध;
		हाल DIB7000M_POWER_NO:
			अवरोध;
	पूर्ण

	/* always घातer करोwn unused parts */
	अगर (!state->cfg.mobile_mode)
		reg_904 |= (1 << 7) | (1 << 6) | (1 << 4) | (1 << 2) | (1 << 1);

	/* P_sdio_select_clk = 0 on MC and after*/
	अगर (state->revision != 0x4000)
		reg_906 <<= 1;

	अगर (state->revision == 0x4003)
		offset = 1;

	dib7000m_ग_लिखो_word(state, 903 + offset, reg_903);
	dib7000m_ग_लिखो_word(state, 904 + offset, reg_904);
	dib7000m_ग_लिखो_word(state, 905 + offset, reg_905);
	dib7000m_ग_लिखो_word(state, 906 + offset, reg_906);
पूर्ण

अटल पूर्णांक dib7000m_set_adc_state(काष्ठा dib7000m_state *state, क्रमागत dibx000_adc_states no)
अणु
	पूर्णांक ret = 0;
	u16 reg_913 = dib7000m_पढ़ो_word(state, 913),
	       reg_914 = dib7000m_पढ़ो_word(state, 914);

	चयन (no) अणु
		हाल DIBX000_SLOW_ADC_ON:
			reg_914 |= (1 << 1) | (1 << 0);
			ret |= dib7000m_ग_लिखो_word(state, 914, reg_914);
			reg_914 &= ~(1 << 1);
			अवरोध;

		हाल DIBX000_SLOW_ADC_OFF:
			reg_914 |=  (1 << 1) | (1 << 0);
			अवरोध;

		हाल DIBX000_ADC_ON:
			अगर (state->revision == 0x4000) अणु // workaround क्रम PA/MA
				// घातer-up ADC
				dib7000m_ग_लिखो_word(state, 913, 0);
				dib7000m_ग_लिखो_word(state, 914, reg_914 & 0x3);
				// घातer-करोwn bandgag
				dib7000m_ग_लिखो_word(state, 913, (1 << 15));
				dib7000m_ग_लिखो_word(state, 914, reg_914 & 0x3);
			पूर्ण

			reg_913 &= 0x0fff;
			reg_914 &= 0x0003;
			अवरोध;

		हाल DIBX000_ADC_OFF: // leave the VBG voltage on
			reg_913 |= (1 << 14) | (1 << 13) | (1 << 12);
			reg_914 |= (1 << 5) | (1 << 4) | (1 << 3) | (1 << 2);
			अवरोध;

		हाल DIBX000_VBG_ENABLE:
			reg_913 &= ~(1 << 15);
			अवरोध;

		हाल DIBX000_VBG_DISABLE:
			reg_913 |= (1 << 15);
			अवरोध;

		शेष:
			अवरोध;
	पूर्ण

//	dprपूर्णांकk("913: %x, 914: %x\n", reg_913, reg_914);
	ret |= dib7000m_ग_लिखो_word(state, 913, reg_913);
	ret |= dib7000m_ग_लिखो_word(state, 914, reg_914);

	वापस ret;
पूर्ण

अटल पूर्णांक dib7000m_set_bandwidth(काष्ठा dib7000m_state *state, u32 bw)
अणु
	u32 timf;

	अगर (!bw)
		bw = 8000;

	// store the current bandwidth क्रम later use
	state->current_bandwidth = bw;

	अगर (state->timf == 0) अणु
		dprपूर्णांकk("using default timf\n");
		timf = state->timf_शेष;
	पूर्ण अन्यथा अणु
		dprपूर्णांकk("using updated timf\n");
		timf = state->timf;
	पूर्ण

	timf = timf * (bw / 50) / 160;

	dib7000m_ग_लिखो_word(state, 23, (u16) ((timf >> 16) & 0xffff));
	dib7000m_ग_लिखो_word(state, 24, (u16) ((timf      ) & 0xffff));

	वापस 0;
पूर्ण

अटल पूर्णांक dib7000m_set_भागersity_in(काष्ठा dvb_frontend *demod, पूर्णांक onoff)
अणु
	काष्ठा dib7000m_state *state = demod->demodulator_priv;

	अगर (state->भाग_क्रमce_off) अणु
		dprपूर्णांकk("diversity combination deactivated - forced by COFDM parameters\n");
		onoff = 0;
	पूर्ण
	state->भाग_state = (u8)onoff;

	अगर (onoff) अणु
		dib7000m_ग_लिखो_word(state, 263 + state->reg_offs, 6);
		dib7000m_ग_लिखो_word(state, 264 + state->reg_offs, 6);
		dib7000m_ग_लिखो_word(state, 266 + state->reg_offs, (state->भाग_sync_रुको << 4) | (1 << 2) | (2 << 0));
	पूर्ण अन्यथा अणु
		dib7000m_ग_लिखो_word(state, 263 + state->reg_offs, 1);
		dib7000m_ग_लिखो_word(state, 264 + state->reg_offs, 0);
		dib7000m_ग_लिखो_word(state, 266 + state->reg_offs, 0);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक dib7000m_sad_calib(काष्ठा dib7000m_state *state)
अणु

/* पूर्णांकernal */
//	dib7000m_ग_लिखो_word(state, 928, (3 << 14) | (1 << 12) | (524 << 0)); // sampling घड़ी of the SAD is writing in set_bandwidth
	dib7000m_ग_लिखो_word(state, 929, (0 << 1) | (0 << 0));
	dib7000m_ग_लिखो_word(state, 930, 776); // 0.625*3.3 / 4096

	/* करो the calibration */
	dib7000m_ग_लिखो_word(state, 929, (1 << 0));
	dib7000m_ग_लिखो_word(state, 929, (0 << 0));

	msleep(1);

	वापस 0;
पूर्ण

अटल व्योम dib7000m_reset_pll_common(काष्ठा dib7000m_state *state, स्थिर काष्ठा dibx000_bandwidth_config *bw)
अणु
	dib7000m_ग_लिखो_word(state, 18, (u16) (((bw->पूर्णांकernal*1000) >> 16) & 0xffff));
	dib7000m_ग_लिखो_word(state, 19, (u16) ( (bw->पूर्णांकernal*1000)        & 0xffff));
	dib7000m_ग_लिखो_word(state, 21, (u16) ( (bw->अगरreq          >> 16) & 0xffff));
	dib7000m_ग_लिखो_word(state, 22, (u16) (  bw->अगरreq                 & 0xffff));

	dib7000m_ग_लिखो_word(state, 928, bw->sad_cfg);
पूर्ण

अटल व्योम dib7000m_reset_pll(काष्ठा dib7000m_state *state)
अणु
	स्थिर काष्ठा dibx000_bandwidth_config *bw = state->cfg.bw;
	u16 reg_907,reg_910;

	/* शेष */
	reg_907 = (bw->pll_bypass << 15) | (bw->modulo << 7) |
		(bw->ADClkSrc << 6) | (bw->IO_CLK_en_core << 5) | (bw->bypclk_भाग << 2) |
		(bw->enable_refभाग << 1) | (0 << 0);
	reg_910 = (((bw->pll_ratio >> 6) & 0x3) << 3) | (bw->pll_range << 1) | bw->pll_reset;

	// क्रम this oscillator frequency should be 30 MHz क्रम the Master (शेष values in the board_parameters give that value)
	// this is only working only क्रम 30 MHz crystals
	अगर (!state->cfg.quartz_direct) अणु
		reg_910 |= (1 << 5);  // क्रमcing the preभागider to 1

		// अगर the previous front-end is baseband, its output frequency is 15 MHz (prev freq भागided by 2)
		अगर(state->cfg.input_clk_is_भाग_2)
			reg_907 |= (16 << 9);
		अन्यथा // otherwise the previous front-end माला_दो out its input (शेष 30MHz) - no extra भागision necessary
			reg_907 |= (8 << 9);
	पूर्ण अन्यथा अणु
		reg_907 |= (bw->pll_ratio & 0x3f) << 9;
		reg_910 |= (bw->pll_preभाग << 5);
	पूर्ण

	dib7000m_ग_लिखो_word(state, 910, reg_910); // pll cfg
	dib7000m_ग_लिखो_word(state, 907, reg_907); // clk cfg0
	dib7000m_ग_लिखो_word(state, 908, 0x0006);  // clk_cfg1

	dib7000m_reset_pll_common(state, bw);
पूर्ण

अटल व्योम dib7000mc_reset_pll(काष्ठा dib7000m_state *state)
अणु
	स्थिर काष्ठा dibx000_bandwidth_config *bw = state->cfg.bw;
	u16 clk_cfg1;

	// clk_cfg0
	dib7000m_ग_लिखो_word(state, 907, (bw->pll_preभाग << 8) | (bw->pll_ratio << 0));

	// clk_cfg1
	//dib7000m_ग_लिखो_word(state, 908, (1 << 14) | (3 << 12) |(0 << 11) |
	clk_cfg1 = (0 << 14) | (3 << 12) |(0 << 11) |
			(bw->IO_CLK_en_core << 10) | (bw->bypclk_भाग << 5) | (bw->enable_refभाग << 4) |
			(1 << 3) | (bw->pll_range << 1) | (bw->pll_reset << 0);
	dib7000m_ग_लिखो_word(state, 908, clk_cfg1);
	clk_cfg1 = (clk_cfg1 & 0xfff7) | (bw->pll_bypass << 3);
	dib7000m_ग_लिखो_word(state, 908, clk_cfg1);

	// smpl_cfg
	dib7000m_ग_लिखो_word(state, 910, (1 << 12) | (2 << 10) | (bw->modulo << 8) | (bw->ADClkSrc << 7));

	dib7000m_reset_pll_common(state, bw);
पूर्ण

अटल पूर्णांक dib7000m_reset_gpio(काष्ठा dib7000m_state *st)
अणु
	/* reset the GPIOs */
	dib7000m_ग_लिखो_word(st, 773, st->cfg.gpio_dir);
	dib7000m_ग_लिखो_word(st, 774, st->cfg.gpio_val);

	/* TODO 782 is P_gpio_od */

	dib7000m_ग_लिखो_word(st, 775, st->cfg.gpio_pwm_pos);

	dib7000m_ग_लिखो_word(st, 780, st->cfg.pwm_freq_भाग);
	वापस 0;
पूर्ण

अटल u16 dib7000m_शेषs_common[] =

अणु
	// स्वतः search configuration
	3, 2,
		0x0004,
		0x1000,
		0x0814,

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
		0x6680, // P_corm_thres Lock algorithms configuration

	1, 170,
		0x0410, // P_palf_alpha_regul, P_palf_filter_मुक्तze, P_palf_filter_on

	8, 173,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,

	1, 182,
		8192, // P_fft_nb_to_cut

	2, 195,
		0x0ccd, // P_pha3_thres
		0,      // P_cti_use_cpe, P_cti_use_prog

	1, 205,
		0x200f, // P_cspu_regul, P_cspu_win_cut

	5, 214,
		0x023d, // P_adp_regul_cnt
		0x00a4, // P_adp_noise_cnt
		0x00a4, // P_adp_regul_ext
		0x7ff0, // P_adp_noise_ext
		0x3ccc, // P_adp_fil

	1, 226,
		0, // P_2d_byp_ti_num

	1, 255,
		0x800, // P_equal_thres_wgn

	1, 263,
		0x0001,

	1, 281,
		0x0010, // P_fec_*

	1, 294,
		0x0062, // P_smo_mode, P_smo_rs_discard, P_smo_fअगरo_flush, P_smo_pid_parse, P_smo_error_discard

	0
पूर्ण;

अटल u16 dib7000m_शेषs[] =

अणु
	/* set ADC level to -16 */
	11, 76,
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

	// Tuner IO bank: max drive (14mA)
	1, 912,
		0x2c8a,

	1, 1817,
		1,

	0,
पूर्ण;

अटल पूर्णांक dib7000m_demod_reset(काष्ठा dib7000m_state *state)
अणु
	dib7000m_set_घातer_mode(state, DIB7000M_POWER_ALL);

	/* always leave the VBG voltage on - it consumes almost nothing but takes a दीर्घ समय to start */
	dib7000m_set_adc_state(state, DIBX000_VBG_ENABLE);

	/* restart all parts */
	dib7000m_ग_लिखो_word(state,  898, 0xffff);
	dib7000m_ग_लिखो_word(state,  899, 0xffff);
	dib7000m_ग_लिखो_word(state,  900, 0xff0f);
	dib7000m_ग_लिखो_word(state,  901, 0xfffc);

	dib7000m_ग_लिखो_word(state,  898, 0);
	dib7000m_ग_लिखो_word(state,  899, 0);
	dib7000m_ग_लिखो_word(state,  900, 0);
	dib7000m_ग_लिखो_word(state,  901, 0);

	अगर (state->revision == 0x4000)
		dib7000m_reset_pll(state);
	अन्यथा
		dib7000mc_reset_pll(state);

	अगर (dib7000m_reset_gpio(state) != 0)
		dprपूर्णांकk("GPIO reset was not successful.\n");

	अगर (dib7000m_set_output_mode(state, OUTMODE_HIGH_Z) != 0)
		dprपूर्णांकk("OUTPUT_MODE could not be reset.\n");

	/* unक्रमce भागstr regardless whether i2c क्रमागतeration was करोne or not */
	dib7000m_ग_लिखो_word(state, 1794, dib7000m_पढ़ो_word(state, 1794) & ~(1 << 1) );

	dib7000m_set_bandwidth(state, 8000);

	dib7000m_set_adc_state(state, DIBX000_SLOW_ADC_ON);
	dib7000m_sad_calib(state);
	dib7000m_set_adc_state(state, DIBX000_SLOW_ADC_OFF);

	अगर (state->cfg.dvbt_mode)
		dib7000m_ग_लिखो_word(state, 1796, 0x0); // select DVB-T output

	अगर (state->cfg.mobile_mode)
		dib7000m_ग_लिखो_word(state, 261 + state->reg_offs, 2);
	अन्यथा
		dib7000m_ग_लिखो_word(state, 224 + state->reg_offs, 1);

	// P_iqc_alpha_pha, P_iqc_alpha_amp, P_iqc_dcc_alpha, ...
	अगर(state->cfg.tuner_is_baseband)
		dib7000m_ग_लिखो_word(state, 36, 0x0755);
	अन्यथा
		dib7000m_ग_लिखो_word(state, 36, 0x1f55);

	// P_भागclksel=3 P_भागbitsel=1
	अगर (state->revision == 0x4000)
		dib7000m_ग_लिखो_word(state, 909, (3 << 10) | (1 << 6));
	अन्यथा
		dib7000m_ग_लिखो_word(state, 909, (3 << 4) | 1);

	dib7000m_ग_लिखो_tab(state, dib7000m_शेषs_common);
	dib7000m_ग_लिखो_tab(state, dib7000m_शेषs);

	dib7000m_set_घातer_mode(state, DIB7000M_POWER_INTERFACE_ONLY);

	state->पूर्णांकernal_clk = state->cfg.bw->पूर्णांकernal;

	वापस 0;
पूर्ण

अटल व्योम dib7000m_restart_agc(काष्ठा dib7000m_state *state)
अणु
	// P_restart_iqc & P_restart_agc
	dib7000m_ग_लिखो_word(state, 898, 0x0c00);
	dib7000m_ग_लिखो_word(state, 898, 0x0000);
पूर्ण

अटल पूर्णांक dib7000m_agc_soft_split(काष्ठा dib7000m_state *state)
अणु
	u16 agc,split_offset;

	अगर(!state->current_agc || !state->current_agc->perक्रमm_agc_softsplit || state->current_agc->split.max == 0)
		वापस 0;

	// n_agc_global
	agc = dib7000m_पढ़ो_word(state, 390);

	अगर (agc > state->current_agc->split.min_thres)
		split_offset = state->current_agc->split.min;
	अन्यथा अगर (agc < state->current_agc->split.max_thres)
		split_offset = state->current_agc->split.max;
	अन्यथा
		split_offset = state->current_agc->split.max *
			(agc - state->current_agc->split.min_thres) /
			(state->current_agc->split.max_thres - state->current_agc->split.min_thres);

	dprपूर्णांकk("AGC split_offset: %d\n", split_offset);

	// P_agc_क्रमce_split and P_agc_split_offset
	वापस dib7000m_ग_लिखो_word(state, 103, (dib7000m_पढ़ो_word(state, 103) & 0xff00) | split_offset);
पूर्ण

अटल पूर्णांक dib7000m_update_lna(काष्ठा dib7000m_state *state)
अणु
	u16 dyn_gain;

	अगर (state->cfg.update_lna) अणु
		// पढ़ो dyn_gain here (because it is demod-dependent and not fe)
		dyn_gain = dib7000m_पढ़ो_word(state, 390);

		अगर (state->cfg.update_lna(&state->demod,dyn_gain)) अणु // LNA has changed
			dib7000m_restart_agc(state);
			वापस 1;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक dib7000m_set_agc_config(काष्ठा dib7000m_state *state, u8 band)
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
	dib7000m_ग_लिखो_word(state, 72 ,  agc->setup);
	dib7000m_ग_लिखो_word(state, 73 ,  agc->inv_gain);
	dib7000m_ग_लिखो_word(state, 74 ,  agc->समय_stabiliz);
	dib7000m_ग_लिखो_word(state, 97 , (agc->alpha_level << 12) | agc->thlock);

	// Demod AGC loop configuration
	dib7000m_ग_लिखो_word(state, 98, (agc->alpha_mant << 5) | agc->alpha_exp);
	dib7000m_ग_लिखो_word(state, 99, (agc->beta_mant  << 6) | agc->beta_exp);

	dprपूर्णांकk("WBD: ref: %d, sel: %d, active: %d, alpha: %d\n",
		state->wbd_ref != 0 ? state->wbd_ref : agc->wbd_ref, agc->wbd_sel, !agc->perक्रमm_agc_softsplit, agc->wbd_sel);

	/* AGC जारीd */
	अगर (state->wbd_ref != 0)
		dib7000m_ग_लिखो_word(state, 102, state->wbd_ref);
	अन्यथा // use शेष
		dib7000m_ग_लिखो_word(state, 102, agc->wbd_ref);

	dib7000m_ग_लिखो_word(state, 103, (agc->wbd_alpha << 9) | (agc->perक्रमm_agc_softsplit << 8) );
	dib7000m_ग_लिखो_word(state, 104,  agc->agc1_max);
	dib7000m_ग_लिखो_word(state, 105,  agc->agc1_min);
	dib7000m_ग_लिखो_word(state, 106,  agc->agc2_max);
	dib7000m_ग_लिखो_word(state, 107,  agc->agc2_min);
	dib7000m_ग_लिखो_word(state, 108, (agc->agc1_pt1 << 8) | agc->agc1_pt2 );
	dib7000m_ग_लिखो_word(state, 109, (agc->agc1_slope1 << 8) | agc->agc1_slope2);
	dib7000m_ग_लिखो_word(state, 110, (agc->agc2_pt1 << 8) | agc->agc2_pt2);
	dib7000m_ग_लिखो_word(state, 111, (agc->agc2_slope1 << 8) | agc->agc2_slope2);

	अगर (state->revision > 0x4000) अणु // settings क्रम the MC
		dib7000m_ग_लिखो_word(state, 71,   agc->agc1_pt3);
//		dprपूर्णांकk("929: %x %d %d\n",
//			(dib7000m_पढ़ो_word(state, 929) & 0xffe3) | (agc->wbd_inv << 4) | (agc->wbd_sel << 2), agc->wbd_inv, agc->wbd_sel);
		dib7000m_ग_लिखो_word(state, 929, (dib7000m_पढ़ो_word(state, 929) & 0xffe3) | (agc->wbd_inv << 4) | (agc->wbd_sel << 2));
	पूर्ण अन्यथा अणु
		// wrong शेष values
		u16 b[9] = अणु 676, 696, 717, 737, 758, 778, 799, 819, 840 पूर्ण;
		क्रम (i = 0; i < 9; i++)
			dib7000m_ग_लिखो_word(state, 88 + i, b[i]);
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम dib7000m_update_timf(काष्ठा dib7000m_state *state)
अणु
	u32 timf = (dib7000m_पढ़ो_word(state, 436) << 16) | dib7000m_पढ़ो_word(state, 437);
	state->timf = timf * 160 / (state->current_bandwidth / 50);
	dib7000m_ग_लिखो_word(state, 23, (u16) (timf >> 16));
	dib7000m_ग_लिखो_word(state, 24, (u16) (timf & 0xffff));
	dprपूर्णांकk("updated timf_frequency: %d (default: %d)\n", state->timf, state->timf_शेष);
पूर्ण

अटल पूर्णांक dib7000m_agc_startup(काष्ठा dvb_frontend *demod)
अणु
	काष्ठा dtv_frontend_properties *ch = &demod->dtv_property_cache;
	काष्ठा dib7000m_state *state = demod->demodulator_priv;
	u16 cfg_72 = dib7000m_पढ़ो_word(state, 72);
	पूर्णांक ret = -1;
	u8 *agc_state = &state->agc_state;
	u8 agc_split;

	चयन (state->agc_state) अणु
		हाल 0:
			// set घातer-up level: पूर्णांकerf+analog+AGC
			dib7000m_set_घातer_mode(state, DIB7000M_POWER_INTERF_ANALOG_AGC);
			dib7000m_set_adc_state(state, DIBX000_ADC_ON);

			अगर (dib7000m_set_agc_config(state, BAND_OF_FREQUENCY(ch->frequency/1000)) != 0)
				वापस -1;

			ret = 7; /* ADC घातer up */
			(*agc_state)++;
			अवरोध;

		हाल 1:
			/* AGC initialization */
			अगर (state->cfg.agc_control)
				state->cfg.agc_control(&state->demod, 1);

			dib7000m_ग_लिखो_word(state, 75, 32768);
			अगर (!state->current_agc->perक्रमm_agc_softsplit) अणु
				/* we are using the wbd - so slow AGC startup */
				dib7000m_ग_लिखो_word(state, 103, 1 << 8); /* क्रमce 0 split on WBD and restart AGC */
				(*agc_state)++;
				ret = 5;
			पूर्ण अन्यथा अणु
				/* शेष AGC startup */
				(*agc_state) = 4;
				/* रुको AGC rough lock समय */
				ret = 7;
			पूर्ण

			dib7000m_restart_agc(state);
			अवरोध;

		हाल 2: /* fast split search path after 5sec */
			dib7000m_ग_लिखो_word(state,  72, cfg_72 | (1 << 4)); /* मुक्तze AGC loop */
			dib7000m_ग_लिखो_word(state, 103, 2 << 9);            /* fast split search 0.25kHz */
			(*agc_state)++;
			ret = 14;
			अवरोध;

	हाल 3: /* split search ended */
			agc_split = (u8)dib7000m_पढ़ो_word(state, 392); /* store the split value क्रम the next समय */
			dib7000m_ग_लिखो_word(state, 75, dib7000m_पढ़ो_word(state, 390)); /* set AGC gain start value */

			dib7000m_ग_लिखो_word(state, 72,  cfg_72 & ~(1 << 4));   /* std AGC loop */
			dib7000m_ग_लिखो_word(state, 103, (state->current_agc->wbd_alpha << 9) | agc_split); /* standard split search */

			dib7000m_restart_agc(state);

			dprपूर्णांकk("SPLIT %p: %u\n", demod, agc_split);

			(*agc_state)++;
			ret = 5;
			अवरोध;

		हाल 4: /* LNA startup */
			/* रुको AGC accurate lock समय */
			ret = 7;

			अगर (dib7000m_update_lna(state))
				// रुको only AGC rough lock समय
				ret = 5;
			अन्यथा
				(*agc_state)++;
			अवरोध;

		हाल 5:
			dib7000m_agc_soft_split(state);

			अगर (state->cfg.agc_control)
				state->cfg.agc_control(&state->demod, 0);

			(*agc_state)++;
			अवरोध;

		शेष:
			अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

अटल व्योम dib7000m_set_channel(काष्ठा dib7000m_state *state, काष्ठा dtv_frontend_properties *ch,
				 u8 seq)
अणु
	u16 value, est[4];

	dib7000m_set_bandwidth(state, BANDWIDTH_TO_KHZ(ch->bandwidth_hz));

	/* nfft, guard, qam, alpha */
	value = 0;
	चयन (ch->transmission_mode) अणु
		हाल TRANSMISSION_MODE_2K: value |= (0 << 7); अवरोध;
		हाल TRANSMISSION_MODE_4K: value |= (2 << 7); अवरोध;
		शेष:
		हाल TRANSMISSION_MODE_8K: value |= (1 << 7); अवरोध;
	पूर्ण
	चयन (ch->guard_पूर्णांकerval) अणु
		हाल GUARD_INTERVAL_1_32: value |= (0 << 5); अवरोध;
		हाल GUARD_INTERVAL_1_16: value |= (1 << 5); अवरोध;
		हाल GUARD_INTERVAL_1_4:  value |= (3 << 5); अवरोध;
		शेष:
		हाल GUARD_INTERVAL_1_8:  value |= (2 << 5); अवरोध;
	पूर्ण
	चयन (ch->modulation) अणु
		हाल QPSK:  value |= (0 << 3); अवरोध;
		हाल QAM_16: value |= (1 << 3); अवरोध;
		शेष:
		हाल QAM_64: value |= (2 << 3); अवरोध;
	पूर्ण
	चयन (HIERARCHY_1) अणु
		हाल HIERARCHY_2: value |= 2; अवरोध;
		हाल HIERARCHY_4: value |= 4; अवरोध;
		शेष:
		हाल HIERARCHY_1: value |= 1; अवरोध;
	पूर्ण
	dib7000m_ग_लिखो_word(state, 0, value);
	dib7000m_ग_लिखो_word(state, 5, (seq << 4));

	/* P_dपूर्णांकl_native, P_dपूर्णांकlv_inv, P_hrch, P_code_rate, P_select_hp */
	value = 0;
	अगर (1 != 0)
		value |= (1 << 6);
	अगर (ch->hierarchy == 1)
		value |= (1 << 4);
	अगर (1 == 1)
		value |= 1;
	चयन ((ch->hierarchy == 0 || 1 == 1) ? ch->code_rate_HP : ch->code_rate_LP) अणु
		हाल FEC_2_3: value |= (2 << 1); अवरोध;
		हाल FEC_3_4: value |= (3 << 1); अवरोध;
		हाल FEC_5_6: value |= (5 << 1); अवरोध;
		हाल FEC_7_8: value |= (7 << 1); अवरोध;
		शेष:
		हाल FEC_1_2: value |= (1 << 1); अवरोध;
	पूर्ण
	dib7000m_ग_लिखो_word(state, 267 + state->reg_offs, value);

	/* offset loop parameters */

	/* P_timf_alpha = 6, P_corm_alpha=6, P_corm_thres=0x80 */
	dib7000m_ग_लिखो_word(state, 26, (6 << 12) | (6 << 8) | 0x80);

	/* P_ctrl_inh_cor=0, P_ctrl_alpha_cor=4, P_ctrl_inh_isi=1, P_ctrl_alpha_isi=3, P_ctrl_inh_cor4=1, P_ctrl_alpha_cor4=3 */
	dib7000m_ग_लिखो_word(state, 29, (0 << 14) | (4 << 10) | (1 << 9) | (3 << 5) | (1 << 4) | (0x3));

	/* P_ctrl_मुक्तze_pha_shअगरt=0, P_ctrl_pha_off_max=3 */
	dib7000m_ग_लिखो_word(state, 32, (0 << 4) | 0x3);

	/* P_ctrl_sfreq_inh=0, P_ctrl_sfreq_step=5 */
	dib7000m_ग_लिखो_word(state, 33, (0 << 4) | 0x5);

	/* P_dvsy_sync_रुको */
	चयन (ch->transmission_mode) अणु
		हाल TRANSMISSION_MODE_8K: value = 256; अवरोध;
		हाल TRANSMISSION_MODE_4K: value = 128; अवरोध;
		हाल TRANSMISSION_MODE_2K:
		शेष: value = 64; अवरोध;
	पूर्ण
	चयन (ch->guard_पूर्णांकerval) अणु
		हाल GUARD_INTERVAL_1_16: value *= 2; अवरोध;
		हाल GUARD_INTERVAL_1_8:  value *= 4; अवरोध;
		हाल GUARD_INTERVAL_1_4:  value *= 8; अवरोध;
		शेष:
		हाल GUARD_INTERVAL_1_32: value *= 1; अवरोध;
	पूर्ण
	state->भाग_sync_रुको = (value * 3) / 2 + 32; // add 50% SFN margin + compensate क्रम one DVSY-fअगरo TODO

	/* deactivate the possibility of भागersity reception अगर extended पूर्णांकerleave - not क्रम 7000MC */
	/* P_dvsy_sync_mode = 0, P_dvsy_sync_enable=1, P_dvcb_comb_mode=2 */
	अगर (1 == 1 || state->revision > 0x4000)
		state->भाग_क्रमce_off = 0;
	अन्यथा
		state->भाग_क्रमce_off = 1;
	dib7000m_set_भागersity_in(&state->demod, state->भाग_state);

	/* channel estimation fine configuration */
	चयन (ch->modulation) अणु
		हाल QAM_64:
			est[0] = 0x0148;       /* P_adp_regul_cnt 0.04 */
			est[1] = 0xfff0;       /* P_adp_noise_cnt -0.002 */
			est[2] = 0x00a4;       /* P_adp_regul_ext 0.02 */
			est[3] = 0xfff8;       /* P_adp_noise_ext -0.001 */
			अवरोध;
		हाल QAM_16:
			est[0] = 0x023d;       /* P_adp_regul_cnt 0.07 */
			est[1] = 0xffdf;       /* P_adp_noise_cnt -0.004 */
			est[2] = 0x00a4;       /* P_adp_regul_ext 0.02 */
			est[3] = 0xfff0;       /* P_adp_noise_ext -0.002 */
			अवरोध;
		शेष:
			est[0] = 0x099a;       /* P_adp_regul_cnt 0.3 */
			est[1] = 0xffae;       /* P_adp_noise_cnt -0.01 */
			est[2] = 0x0333;       /* P_adp_regul_ext 0.1 */
			est[3] = 0xfff8;       /* P_adp_noise_ext -0.002 */
			अवरोध;
	पूर्ण
	क्रम (value = 0; value < 4; value++)
		dib7000m_ग_लिखो_word(state, 214 + value + state->reg_offs, est[value]);

	// set घातer-up level: स्वतःsearch
	dib7000m_set_घातer_mode(state, DIB7000M_POWER_COR4_DINTLV_ICIRM_EQUAL_CFROD);
पूर्ण

अटल पूर्णांक dib7000m_स्वतःsearch_start(काष्ठा dvb_frontend *demod)
अणु
	काष्ठा dtv_frontend_properties *ch = &demod->dtv_property_cache;
	काष्ठा dib7000m_state *state = demod->demodulator_priv;
	काष्ठा dtv_frontend_properties schan;
	पूर्णांक ret = 0;
	u32 value, factor;

	schan = *ch;

	schan.modulation = QAM_64;
	schan.guard_पूर्णांकerval        = GUARD_INTERVAL_1_32;
	schan.transmission_mode         = TRANSMISSION_MODE_8K;
	schan.code_rate_HP = FEC_2_3;
	schan.code_rate_LP = FEC_3_4;
	schan.hierarchy    = 0;

	dib7000m_set_channel(state, &schan, 7);

	factor = BANDWIDTH_TO_KHZ(schan.bandwidth_hz);
	अगर (factor >= 5000)
		factor = 1;
	अन्यथा
		factor = 6;

	// always use the setting क्रम 8MHz here lock_समय क्रम 7,6 MHz are दीर्घer
	value = 30 * state->पूर्णांकernal_clk * factor;
	ret |= dib7000m_ग_लिखो_word(state, 6,  (u16) ((value >> 16) & 0xffff)); // lock0 रुको समय
	ret |= dib7000m_ग_लिखो_word(state, 7,  (u16)  (value        & 0xffff)); // lock0 रुको समय
	value = 100 * state->पूर्णांकernal_clk * factor;
	ret |= dib7000m_ग_लिखो_word(state, 8,  (u16) ((value >> 16) & 0xffff)); // lock1 रुको समय
	ret |= dib7000m_ग_लिखो_word(state, 9,  (u16)  (value        & 0xffff)); // lock1 रुको समय
	value = 500 * state->पूर्णांकernal_clk * factor;
	ret |= dib7000m_ग_लिखो_word(state, 10, (u16) ((value >> 16) & 0xffff)); // lock2 रुको समय
	ret |= dib7000m_ग_लिखो_word(state, 11, (u16)  (value        & 0xffff)); // lock2 रुको समय

	// start search
	value = dib7000m_पढ़ो_word(state, 0);
	ret |= dib7000m_ग_लिखो_word(state, 0, (u16) (value | (1 << 9)));

	/* clear n_irq_pending */
	अगर (state->revision == 0x4000)
		dib7000m_ग_लिखो_word(state, 1793, 0);
	अन्यथा
		dib7000m_पढ़ो_word(state, 537);

	ret |= dib7000m_ग_लिखो_word(state, 0, (u16) value);

	वापस ret;
पूर्ण

अटल पूर्णांक dib7000m_स्वतःsearch_irq(काष्ठा dib7000m_state *state, u16 reg)
अणु
	u16 irq_pending = dib7000m_पढ़ो_word(state, reg);

	अगर (irq_pending & 0x1) अणु // failed
		dprपूर्णांकk("autosearch failed\n");
		वापस 1;
	पूर्ण

	अगर (irq_pending & 0x2) अणु // succeeded
		dprपूर्णांकk("autosearch succeeded\n");
		वापस 2;
	पूर्ण
	वापस 0; // still pending
पूर्ण

अटल पूर्णांक dib7000m_स्वतःsearch_is_irq(काष्ठा dvb_frontend *demod)
अणु
	काष्ठा dib7000m_state *state = demod->demodulator_priv;
	अगर (state->revision == 0x4000)
		वापस dib7000m_स्वतःsearch_irq(state, 1793);
	अन्यथा
		वापस dib7000m_स्वतःsearch_irq(state, 537);
पूर्ण

अटल पूर्णांक dib7000m_tune(काष्ठा dvb_frontend *demod)
अणु
	काष्ठा dtv_frontend_properties *ch = &demod->dtv_property_cache;
	काष्ठा dib7000m_state *state = demod->demodulator_priv;
	पूर्णांक ret = 0;
	u16 value;

	// we are alपढ़ोy tuned - just resuming from suspend
	dib7000m_set_channel(state, ch, 0);

	// restart demod
	ret |= dib7000m_ग_लिखो_word(state, 898, 0x4000);
	ret |= dib7000m_ग_लिखो_word(state, 898, 0x0000);
	msleep(45);

	dib7000m_set_घातer_mode(state, DIB7000M_POWER_COR4_CRY_ESRAM_MOUT_NUD);
	/* P_ctrl_inh_cor=0, P_ctrl_alpha_cor=4, P_ctrl_inh_isi=0, P_ctrl_alpha_isi=3, P_ctrl_inh_cor4=1, P_ctrl_alpha_cor4=3 */
	ret |= dib7000m_ग_लिखो_word(state, 29, (0 << 14) | (4 << 10) | (0 << 9) | (3 << 5) | (1 << 4) | (0x3));

	// never achieved a lock beक्रमe - रुको क्रम timfreq to update
	अगर (state->timf == 0)
		msleep(200);

	//dump_reg(state);
	/* P_timf_alpha, P_corm_alpha=6, P_corm_thres=0x80 */
	value = (6 << 8) | 0x80;
	चयन (ch->transmission_mode) अणु
		हाल TRANSMISSION_MODE_2K: value |= (7 << 12); अवरोध;
		हाल TRANSMISSION_MODE_4K: value |= (8 << 12); अवरोध;
		शेष:
		हाल TRANSMISSION_MODE_8K: value |= (9 << 12); अवरोध;
	पूर्ण
	ret |= dib7000m_ग_लिखो_word(state, 26, value);

	/* P_ctrl_मुक्तze_pha_shअगरt=0, P_ctrl_pha_off_max */
	value = (0 << 4);
	चयन (ch->transmission_mode) अणु
		हाल TRANSMISSION_MODE_2K: value |= 0x6; अवरोध;
		हाल TRANSMISSION_MODE_4K: value |= 0x7; अवरोध;
		शेष:
		हाल TRANSMISSION_MODE_8K: value |= 0x8; अवरोध;
	पूर्ण
	ret |= dib7000m_ग_लिखो_word(state, 32, value);

	/* P_ctrl_sfreq_inh=0, P_ctrl_sfreq_step */
	value = (0 << 4);
	चयन (ch->transmission_mode) अणु
		हाल TRANSMISSION_MODE_2K: value |= 0x6; अवरोध;
		हाल TRANSMISSION_MODE_4K: value |= 0x7; अवरोध;
		शेष:
		हाल TRANSMISSION_MODE_8K: value |= 0x8; अवरोध;
	पूर्ण
	ret |= dib7000m_ग_लिखो_word(state, 33,  value);

	// we achieved a lock - it's समय to update the timf freq
	अगर ((dib7000m_पढ़ो_word(state, 535) >> 6)  & 0x1)
		dib7000m_update_timf(state);

	dib7000m_set_bandwidth(state, BANDWIDTH_TO_KHZ(ch->bandwidth_hz));
	वापस ret;
पूर्ण

अटल पूर्णांक dib7000m_wakeup(काष्ठा dvb_frontend *demod)
अणु
	काष्ठा dib7000m_state *state = demod->demodulator_priv;

	dib7000m_set_घातer_mode(state, DIB7000M_POWER_ALL);

	अगर (dib7000m_set_adc_state(state, DIBX000_SLOW_ADC_ON) != 0)
		dprपूर्णांकk("could not start Slow ADC\n");

	वापस 0;
पूर्ण

अटल पूर्णांक dib7000m_sleep(काष्ठा dvb_frontend *demod)
अणु
	काष्ठा dib7000m_state *st = demod->demodulator_priv;
	dib7000m_set_output_mode(st, OUTMODE_HIGH_Z);
	dib7000m_set_घातer_mode(st, DIB7000M_POWER_INTERFACE_ONLY);
	वापस dib7000m_set_adc_state(st, DIBX000_SLOW_ADC_OFF) |
		dib7000m_set_adc_state(st, DIBX000_ADC_OFF);
पूर्ण

अटल पूर्णांक dib7000m_identअगरy(काष्ठा dib7000m_state *state)
अणु
	u16 value;

	अगर ((value = dib7000m_पढ़ो_word(state, 896)) != 0x01b3) अणु
		dprपूर्णांकk("wrong Vendor ID (0x%x)\n", value);
		वापस -EREMOTEIO;
	पूर्ण

	state->revision = dib7000m_पढ़ो_word(state, 897);
	अगर (state->revision != 0x4000 &&
		state->revision != 0x4001 &&
		state->revision != 0x4002 &&
		state->revision != 0x4003) अणु
		dprपूर्णांकk("wrong Device ID (0x%x)\n", value);
		वापस -EREMOTEIO;
	पूर्ण

	/* protect this driver to be used with 7000PC */
	अगर (state->revision == 0x4000 && dib7000m_पढ़ो_word(state, 769) == 0x4000) अणु
		dprपूर्णांकk("this driver does not work with DiB7000PC\n");
		वापस -EREMOTEIO;
	पूर्ण

	चयन (state->revision) अणु
	हाल 0x4000: dprपूर्णांकk("found DiB7000MA/PA/MB/PB\n"); अवरोध;
	हाल 0x4001: state->reg_offs = 1; dprपूर्णांकk("found DiB7000HC\n"); अवरोध;
	हाल 0x4002: state->reg_offs = 1; dprपूर्णांकk("found DiB7000MC\n"); अवरोध;
	हाल 0x4003: state->reg_offs = 1; dprपूर्णांकk("found DiB9000\n"); अवरोध;
	पूर्ण

	वापस 0;
पूर्ण


अटल पूर्णांक dib7000m_get_frontend(काष्ठा dvb_frontend* fe,
				 काष्ठा dtv_frontend_properties *fep)
अणु
	काष्ठा dib7000m_state *state = fe->demodulator_priv;
	u16 tps = dib7000m_पढ़ो_word(state,480);

	fep->inversion = INVERSION_AUTO;

	fep->bandwidth_hz = BANDWIDTH_TO_HZ(state->current_bandwidth);

	चयन ((tps >> 8) & 0x3) अणु
		हाल 0: fep->transmission_mode = TRANSMISSION_MODE_2K; अवरोध;
		हाल 1: fep->transmission_mode = TRANSMISSION_MODE_8K; अवरोध;
		/* हाल 2: fep->transmission_mode = TRANSMISSION_MODE_4K; अवरोध; */
	पूर्ण

	चयन (tps & 0x3) अणु
		हाल 0: fep->guard_पूर्णांकerval = GUARD_INTERVAL_1_32; अवरोध;
		हाल 1: fep->guard_पूर्णांकerval = GUARD_INTERVAL_1_16; अवरोध;
		हाल 2: fep->guard_पूर्णांकerval = GUARD_INTERVAL_1_8; अवरोध;
		हाल 3: fep->guard_पूर्णांकerval = GUARD_INTERVAL_1_4; अवरोध;
	पूर्ण

	चयन ((tps >> 14) & 0x3) अणु
		हाल 0: fep->modulation = QPSK; अवरोध;
		हाल 1: fep->modulation = QAM_16; अवरोध;
		हाल 2:
		शेष: fep->modulation = QAM_64; अवरोध;
	पूर्ण

	/* as दीर्घ as the frontend_param काष्ठाure is fixed क्रम hierarchical transmission I refuse to use it */
	/* (tps >> 13) & 0x1 == hrch is used, (tps >> 10) & 0x7 == alpha */

	fep->hierarchy = HIERARCHY_NONE;
	चयन ((tps >> 5) & 0x7) अणु
		हाल 1: fep->code_rate_HP = FEC_1_2; अवरोध;
		हाल 2: fep->code_rate_HP = FEC_2_3; अवरोध;
		हाल 3: fep->code_rate_HP = FEC_3_4; अवरोध;
		हाल 5: fep->code_rate_HP = FEC_5_6; अवरोध;
		हाल 7:
		शेष: fep->code_rate_HP = FEC_7_8; अवरोध;

	पूर्ण

	चयन ((tps >> 2) & 0x7) अणु
		हाल 1: fep->code_rate_LP = FEC_1_2; अवरोध;
		हाल 2: fep->code_rate_LP = FEC_2_3; अवरोध;
		हाल 3: fep->code_rate_LP = FEC_3_4; अवरोध;
		हाल 5: fep->code_rate_LP = FEC_5_6; अवरोध;
		हाल 7:
		शेष: fep->code_rate_LP = FEC_7_8; अवरोध;
	पूर्ण

	/* native पूर्णांकerleaver: (dib7000m_पढ़ो_word(state, 481) >>  5) & 0x1 */

	वापस 0;
पूर्ण

अटल पूर्णांक dib7000m_set_frontend(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dtv_frontend_properties *fep = &fe->dtv_property_cache;
	काष्ठा dib7000m_state *state = fe->demodulator_priv;
	पूर्णांक समय, ret;

	dib7000m_set_output_mode(state, OUTMODE_HIGH_Z);

	dib7000m_set_bandwidth(state, BANDWIDTH_TO_KHZ(fep->bandwidth_hz));

	अगर (fe->ops.tuner_ops.set_params)
		fe->ops.tuner_ops.set_params(fe);

	/* start up the AGC */
	state->agc_state = 0;
	करो अणु
		समय = dib7000m_agc_startup(fe);
		अगर (समय != -1)
			msleep(समय);
	पूर्ण जबतक (समय != -1);

	अगर (fep->transmission_mode == TRANSMISSION_MODE_AUTO ||
		fep->guard_पूर्णांकerval    == GUARD_INTERVAL_AUTO ||
		fep->modulation        == QAM_AUTO ||
		fep->code_rate_HP      == FEC_AUTO) अणु
		पूर्णांक i = 800, found;

		dib7000m_स्वतःsearch_start(fe);
		करो अणु
			msleep(1);
			found = dib7000m_स्वतःsearch_is_irq(fe);
		पूर्ण जबतक (found == 0 && i--);

		dprपूर्णांकk("autosearch returns: %d\n", found);
		अगर (found == 0 || found == 1)
			वापस 0; // no channel found

		dib7000m_get_frontend(fe, fep);
	पूर्ण

	ret = dib7000m_tune(fe);

	/* make this a config parameter */
	dib7000m_set_output_mode(state, OUTMODE_MPEG2_FIFO);
	वापस ret;
पूर्ण

अटल पूर्णांक dib7000m_पढ़ो_status(काष्ठा dvb_frontend *fe, क्रमागत fe_status *stat)
अणु
	काष्ठा dib7000m_state *state = fe->demodulator_priv;
	u16 lock = dib7000m_पढ़ो_word(state, 535);

	*stat = 0;

	अगर (lock & 0x8000)
		*stat |= FE_HAS_SIGNAL;
	अगर (lock & 0x3000)
		*stat |= FE_HAS_CARRIER;
	अगर (lock & 0x0100)
		*stat |= FE_HAS_VITERBI;
	अगर (lock & 0x0010)
		*stat |= FE_HAS_SYNC;
	अगर (lock & 0x0008)
		*stat |= FE_HAS_LOCK;

	वापस 0;
पूर्ण

अटल पूर्णांक dib7000m_पढ़ो_ber(काष्ठा dvb_frontend *fe, u32 *ber)
अणु
	काष्ठा dib7000m_state *state = fe->demodulator_priv;
	*ber = (dib7000m_पढ़ो_word(state, 526) << 16) | dib7000m_पढ़ो_word(state, 527);
	वापस 0;
पूर्ण

अटल पूर्णांक dib7000m_पढ़ो_unc_blocks(काष्ठा dvb_frontend *fe, u32 *unc)
अणु
	काष्ठा dib7000m_state *state = fe->demodulator_priv;
	*unc = dib7000m_पढ़ो_word(state, 534);
	वापस 0;
पूर्ण

अटल पूर्णांक dib7000m_पढ़ो_संकेत_strength(काष्ठा dvb_frontend *fe, u16 *strength)
अणु
	काष्ठा dib7000m_state *state = fe->demodulator_priv;
	u16 val = dib7000m_पढ़ो_word(state, 390);
	*strength = 65535 - val;
	वापस 0;
पूर्ण

अटल पूर्णांक dib7000m_पढ़ो_snr(काष्ठा dvb_frontend* fe, u16 *snr)
अणु
	*snr = 0x0000;
	वापस 0;
पूर्ण

अटल पूर्णांक dib7000m_fe_get_tune_settings(काष्ठा dvb_frontend* fe, काष्ठा dvb_frontend_tune_settings *tune)
अणु
	tune->min_delay_ms = 1000;
	वापस 0;
पूर्ण

अटल व्योम dib7000m_release(काष्ठा dvb_frontend *demod)
अणु
	काष्ठा dib7000m_state *st = demod->demodulator_priv;
	dibx000_निकास_i2c_master(&st->i2c_master);
	kमुक्त(st);
पूर्ण

काष्ठा i2c_adapter * dib7000m_get_i2c_master(काष्ठा dvb_frontend *demod, क्रमागत dibx000_i2c_पूर्णांकerface पूर्णांकf, पूर्णांक gating)
अणु
	काष्ठा dib7000m_state *st = demod->demodulator_priv;
	वापस dibx000_get_i2c_adapter(&st->i2c_master, पूर्णांकf, gating);
पूर्ण
EXPORT_SYMBOL(dib7000m_get_i2c_master);

पूर्णांक dib7000m_pid_filter_ctrl(काष्ठा dvb_frontend *fe, u8 onoff)
अणु
	काष्ठा dib7000m_state *state = fe->demodulator_priv;
	u16 val = dib7000m_पढ़ो_word(state, 294 + state->reg_offs) & 0xffef;
	val |= (onoff & 0x1) << 4;
	dprपूर्णांकk("PID filter enabled %d\n", onoff);
	वापस dib7000m_ग_लिखो_word(state, 294 + state->reg_offs, val);
पूर्ण
EXPORT_SYMBOL(dib7000m_pid_filter_ctrl);

पूर्णांक dib7000m_pid_filter(काष्ठा dvb_frontend *fe, u8 id, u16 pid, u8 onoff)
अणु
	काष्ठा dib7000m_state *state = fe->demodulator_priv;
	dprपूर्णांकk("PID filter: index %x, PID %d, OnOff %d\n", id, pid, onoff);
	वापस dib7000m_ग_लिखो_word(state, 300 + state->reg_offs + id,
			onoff ? (1 << 13) | pid : 0);
पूर्ण
EXPORT_SYMBOL(dib7000m_pid_filter);

#अगर 0
/* used with some prototype boards */
पूर्णांक dib7000m_i2c_क्रमागतeration(काष्ठा i2c_adapter *i2c, पूर्णांक no_of_demods,
		u8 शेष_addr, काष्ठा dib7000m_config cfg[])
अणु
	काष्ठा dib7000m_state st = अणु .i2c_adap = i2c पूर्ण;
	पूर्णांक k = 0;
	u8 new_addr = 0;

	क्रम (k = no_of_demods-1; k >= 0; k--) अणु
		st.cfg = cfg[k];

		/* designated i2c address */
		new_addr          = (0x40 + k) << 1;
		st.i2c_addr = new_addr;
		अगर (dib7000m_identअगरy(&st) != 0) अणु
			st.i2c_addr = शेष_addr;
			अगर (dib7000m_identअगरy(&st) != 0) अणु
				dprपूर्णांकk("DiB7000M #%d: not identified\n", k);
				वापस -EIO;
			पूर्ण
		पूर्ण

		/* start भागersity to pull_करोwn भाग_str - just क्रम i2c-क्रमागतeration */
		dib7000m_set_output_mode(&st, OUTMODE_DIVERSITY);

		dib7000m_ग_लिखो_word(&st, 1796, 0x0); // select DVB-T output

		/* set new i2c address and क्रमce भागstart */
		dib7000m_ग_लिखो_word(&st, 1794, (new_addr << 2) | 0x2);

		dprपूर्णांकk("IC %d initialized (to i2c_address 0x%x)\n", k, new_addr);
	पूर्ण

	क्रम (k = 0; k < no_of_demods; k++) अणु
		st.cfg = cfg[k];
		st.i2c_addr = (0x40 + k) << 1;

		// unक्रमce भागstr
		dib7000m_ग_लिखो_word(&st,1794, st.i2c_addr << 2);

		/* deactivate भाग - it was just क्रम i2c-क्रमागतeration */
		dib7000m_set_output_mode(&st, OUTMODE_HIGH_Z);
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(dib7000m_i2c_क्रमागतeration);
#पूर्ण_अगर

अटल स्थिर काष्ठा dvb_frontend_ops dib7000m_ops;
काष्ठा dvb_frontend * dib7000m_attach(काष्ठा i2c_adapter *i2c_adap, u8 i2c_addr, काष्ठा dib7000m_config *cfg)
अणु
	काष्ठा dvb_frontend *demod;
	काष्ठा dib7000m_state *st;
	st = kzalloc(माप(काष्ठा dib7000m_state), GFP_KERNEL);
	अगर (st == शून्य)
		वापस शून्य;

	स_नकल(&st->cfg, cfg, माप(काष्ठा dib7000m_config));
	st->i2c_adap = i2c_adap;
	st->i2c_addr = i2c_addr;

	demod                   = &st->demod;
	demod->demodulator_priv = st;
	स_नकल(&st->demod.ops, &dib7000m_ops, माप(काष्ठा dvb_frontend_ops));
	mutex_init(&st->i2c_buffer_lock);

	st->timf_शेष = cfg->bw->timf;

	अगर (dib7000m_identअगरy(st) != 0)
		जाओ error;

	अगर (st->revision == 0x4000)
		dibx000_init_i2c_master(&st->i2c_master, DIB7000, st->i2c_adap, st->i2c_addr);
	अन्यथा
		dibx000_init_i2c_master(&st->i2c_master, DIB7000MC, st->i2c_adap, st->i2c_addr);

	dib7000m_demod_reset(st);

	वापस demod;

error:
	kमुक्त(st);
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(dib7000m_attach);

अटल स्थिर काष्ठा dvb_frontend_ops dib7000m_ops = अणु
	.delsys = अणु SYS_DVBT पूर्ण,
	.info = अणु
		.name = "DiBcom 7000MA/MB/PA/PB/MC",
		.frequency_min_hz      =  44250 * kHz,
		.frequency_max_hz      = 867250 * kHz,
		.frequency_stepsize_hz = 62500,
		.caps = FE_CAN_INVERSION_AUTO |
			FE_CAN_FEC_1_2 | FE_CAN_FEC_2_3 | FE_CAN_FEC_3_4 |
			FE_CAN_FEC_5_6 | FE_CAN_FEC_7_8 | FE_CAN_FEC_AUTO |
			FE_CAN_QPSK | FE_CAN_QAM_16 | FE_CAN_QAM_64 | FE_CAN_QAM_AUTO |
			FE_CAN_TRANSMISSION_MODE_AUTO |
			FE_CAN_GUARD_INTERVAL_AUTO |
			FE_CAN_RECOVER |
			FE_CAN_HIERARCHY_AUTO,
	पूर्ण,

	.release              = dib7000m_release,

	.init                 = dib7000m_wakeup,
	.sleep                = dib7000m_sleep,

	.set_frontend         = dib7000m_set_frontend,
	.get_tune_settings    = dib7000m_fe_get_tune_settings,
	.get_frontend         = dib7000m_get_frontend,

	.पढ़ो_status          = dib7000m_पढ़ो_status,
	.पढ़ो_ber             = dib7000m_पढ़ो_ber,
	.पढ़ो_संकेत_strength = dib7000m_पढ़ो_संकेत_strength,
	.पढ़ो_snr             = dib7000m_पढ़ो_snr,
	.पढ़ो_ucblocks        = dib7000m_पढ़ो_unc_blocks,
पूर्ण;

MODULE_AUTHOR("Patrick Boettcher <patrick.boettcher@posteo.de>");
MODULE_DESCRIPTION("Driver for the DiBcom 7000MA/MB/PA/PB/MC COFDM demodulator");
MODULE_LICENSE("GPL");
