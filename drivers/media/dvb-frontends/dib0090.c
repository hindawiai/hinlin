<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Linux-DVB Driver क्रम DiBcom's DiB0090 base-band RF Tuner.
 *
 * Copyright (C) 2005-9 DiBcom (http://www.dibcom.fr/)
 *
 * This code is more or less generated from another driver, please
 * excuse some codingstyle oddities.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/i2c.h>
#समावेश <linux/mutex.h>

#समावेश <media/dvb_frontend.h>

#समावेश "dib0090.h"
#समावेश "dibx000_common.h"

अटल पूर्णांक debug;
module_param(debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug, "turn on debugging (default: 0)");

#घोषणा dprपूर्णांकk(fmt, arg...) करो अणु					\
	अगर (debug)							\
		prपूर्णांकk(KERN_DEBUG pr_fmt("%s: " fmt),			\
		       __func__, ##arg);				\
पूर्ण जबतक (0)

#घोषणा CONFIG_SYS_DVBT
#घोषणा CONFIG_SYS_ISDBT
#घोषणा CONFIG_BAND_CBAND
#घोषणा CONFIG_BAND_VHF
#घोषणा CONFIG_BAND_UHF
#घोषणा CONFIG_DIB0090_USE_PWM_AGC

#घोषणा EN_LNA0      0x8000
#घोषणा EN_LNA1      0x4000
#घोषणा EN_LNA2      0x2000
#घोषणा EN_LNA3      0x1000
#घोषणा EN_MIX0      0x0800
#घोषणा EN_MIX1      0x0400
#घोषणा EN_MIX2      0x0200
#घोषणा EN_MIX3      0x0100
#घोषणा EN_IQADC     0x0040
#घोषणा EN_PLL       0x0020
#घोषणा EN_TX        0x0010
#घोषणा EN_BB        0x0008
#घोषणा EN_LO        0x0004
#घोषणा EN_BIAS      0x0001

#घोषणा EN_IQANA     0x0002
#घोषणा EN_DIGCLK    0x0080	/* not in the 0x24 reg, only in 0x1b */
#घोषणा EN_CRYSTAL   0x0002

#घोषणा EN_UHF		 0x22E9
#घोषणा EN_VHF		 0x44E9
#घोषणा EN_LBD		 0x11E9
#घोषणा EN_SBD		 0x44E9
#घोषणा EN_CAB		 0x88E9

/* Calibration defines */
#घोषणा      DC_CAL 0x1
#घोषणा     WBD_CAL 0x2
#घोषणा    TEMP_CAL 0x4
#घोषणा CAPTRIM_CAL 0x8

#घोषणा KROSUS_PLL_LOCKED   0x800
#घोषणा KROSUS              0x2

/* Use those defines to identअगरy SOC version */
#घोषणा SOC               0x02
#घोषणा SOC_7090_P1G_11R1 0x82
#घोषणा SOC_7090_P1G_21R1 0x8a
#घोषणा SOC_8090_P1G_11R1 0x86
#घोषणा SOC_8090_P1G_21R1 0x8e

/* अन्यथा use thos ones to check */
#घोषणा P1A_B      0x0
#घोषणा P1C	   0x1
#घोषणा P1D_E_F    0x3
#घोषणा P1G	   0x7
#घोषणा P1G_21R2   0xf

#घोषणा MP001 0x1		/* Single 9090/8096 */
#घोषणा MP005 0x4		/* Single Sband */
#घोषणा MP008 0x6		/* Dual भागersity VHF-UHF-LBAND */
#घोषणा MP009 0x7		/* Dual भागersity 29098 CBAND-UHF-LBAND-SBAND */

#घोषणा pgm_पढ़ो_word(w) (*w)

काष्ठा dc_calibration;

काष्ठा dib0090_tuning अणु
	u32 max_freq;		/* क्रम every frequency less than or equal to that field: this inक्रमmation is correct */
	u8 चयन_trim;
	u8 lna_tune;
	u16 lna_bias;
	u16 v2i;
	u16 mix;
	u16 load;
	u16 tuner_enable;
पूर्ण;

काष्ठा dib0090_pll अणु
	u32 max_freq;		/* क्रम every frequency less than or equal to that field: this inक्रमmation is correct */
	u8 vco_band;
	u8 hfभाग_code;
	u8 hfभाग;
	u8 topresc;
पूर्ण;

काष्ठा dib0090_identity अणु
	u8 version;
	u8 product;
	u8 p1g;
	u8 in_soc;
पूर्ण;

काष्ठा dib0090_state अणु
	काष्ठा i2c_adapter *i2c;
	काष्ठा dvb_frontend *fe;
	स्थिर काष्ठा dib0090_config *config;

	u8 current_band;
	क्रमागत frontend_tune_state tune_state;
	u32 current_rf;

	u16 wbd_offset;
	s16 wbd_target;		/* in dB */

	s16 rf_gain_limit;	/* take-over-poपूर्णांक: where to split between bb and rf gain */
	s16 current_gain;	/* keeps the currently programmed gain */
	u8 agc_step;		/* new binary search */

	u16 gain[2];		/* क्रम channel monitoring */

	स्थिर u16 *rf_ramp;
	स्थिर u16 *bb_ramp;

	/* क्रम the software AGC ramps */
	u16 bb_1_def;
	u16 rf_lt_def;
	u16 gain_reg[4];

	/* क्रम the captrim/dc-offset search */
	s8 step;
	s16 adc_dअगरf;
	s16 min_adc_dअगरf;

	s8 captrim;
	s8 fcaptrim;

	स्थिर काष्ठा dc_calibration *dc;
	u16 bb6, bb7;

	स्थिर काष्ठा dib0090_tuning *current_tune_table_index;
	स्थिर काष्ठा dib0090_pll *current_pll_table_index;

	u8 tuner_is_tuned;
	u8 agc_मुक्तze;

	काष्ठा dib0090_identity identity;

	u32 rf_request;
	u8 current_standard;

	u8 calibrate;
	u32 rest;
	u16 bias;
	s16 temperature;

	u8 wbd_calibration_gain;
	स्थिर काष्ठा dib0090_wbd_slope *current_wbd_table;
	u16 wbdmux;

	/* क्रम the I2C transfer */
	काष्ठा i2c_msg msg[2];
	u8 i2c_ग_लिखो_buffer[3];
	u8 i2c_पढ़ो_buffer[2];
	काष्ठा mutex i2c_buffer_lock;
पूर्ण;

काष्ठा dib0090_fw_state अणु
	काष्ठा i2c_adapter *i2c;
	काष्ठा dvb_frontend *fe;
	काष्ठा dib0090_identity identity;
	स्थिर काष्ठा dib0090_config *config;

	/* क्रम the I2C transfer */
	काष्ठा i2c_msg msg;
	u8 i2c_ग_लिखो_buffer[2];
	u8 i2c_पढ़ो_buffer[2];
	काष्ठा mutex i2c_buffer_lock;
पूर्ण;

अटल u16 dib0090_पढ़ो_reg(काष्ठा dib0090_state *state, u8 reg)
अणु
	u16 ret;

	अगर (mutex_lock_पूर्णांकerruptible(&state->i2c_buffer_lock) < 0) अणु
		dprपूर्णांकk("could not acquire lock\n");
		वापस 0;
	पूर्ण

	state->i2c_ग_लिखो_buffer[0] = reg;

	स_रखो(state->msg, 0, 2 * माप(काष्ठा i2c_msg));
	state->msg[0].addr = state->config->i2c_address;
	state->msg[0].flags = 0;
	state->msg[0].buf = state->i2c_ग_लिखो_buffer;
	state->msg[0].len = 1;
	state->msg[1].addr = state->config->i2c_address;
	state->msg[1].flags = I2C_M_RD;
	state->msg[1].buf = state->i2c_पढ़ो_buffer;
	state->msg[1].len = 2;

	अगर (i2c_transfer(state->i2c, state->msg, 2) != 2) अणु
		pr_warn("DiB0090 I2C read failed\n");
		ret = 0;
	पूर्ण अन्यथा
		ret = (state->i2c_पढ़ो_buffer[0] << 8)
			| state->i2c_पढ़ो_buffer[1];

	mutex_unlock(&state->i2c_buffer_lock);
	वापस ret;
पूर्ण

अटल पूर्णांक dib0090_ग_लिखो_reg(काष्ठा dib0090_state *state, u32 reg, u16 val)
अणु
	पूर्णांक ret;

	अगर (mutex_lock_पूर्णांकerruptible(&state->i2c_buffer_lock) < 0) अणु
		dprपूर्णांकk("could not acquire lock\n");
		वापस -EINVAL;
	पूर्ण

	state->i2c_ग_लिखो_buffer[0] = reg & 0xff;
	state->i2c_ग_लिखो_buffer[1] = val >> 8;
	state->i2c_ग_लिखो_buffer[2] = val & 0xff;

	स_रखो(state->msg, 0, माप(काष्ठा i2c_msg));
	state->msg[0].addr = state->config->i2c_address;
	state->msg[0].flags = 0;
	state->msg[0].buf = state->i2c_ग_लिखो_buffer;
	state->msg[0].len = 3;

	अगर (i2c_transfer(state->i2c, state->msg, 1) != 1) अणु
		pr_warn("DiB0090 I2C write failed\n");
		ret = -EREMOTEIO;
	पूर्ण अन्यथा
		ret = 0;

	mutex_unlock(&state->i2c_buffer_lock);
	वापस ret;
पूर्ण

अटल u16 dib0090_fw_पढ़ो_reg(काष्ठा dib0090_fw_state *state, u8 reg)
अणु
	u16 ret;

	अगर (mutex_lock_पूर्णांकerruptible(&state->i2c_buffer_lock) < 0) अणु
		dprपूर्णांकk("could not acquire lock\n");
		वापस 0;
	पूर्ण

	state->i2c_ग_लिखो_buffer[0] = reg;

	स_रखो(&state->msg, 0, माप(काष्ठा i2c_msg));
	state->msg.addr = reg;
	state->msg.flags = I2C_M_RD;
	state->msg.buf = state->i2c_पढ़ो_buffer;
	state->msg.len = 2;
	अगर (i2c_transfer(state->i2c, &state->msg, 1) != 1) अणु
		pr_warn("DiB0090 I2C read failed\n");
		ret = 0;
	पूर्ण अन्यथा
		ret = (state->i2c_पढ़ो_buffer[0] << 8)
			| state->i2c_पढ़ो_buffer[1];

	mutex_unlock(&state->i2c_buffer_lock);
	वापस ret;
पूर्ण

अटल पूर्णांक dib0090_fw_ग_लिखो_reg(काष्ठा dib0090_fw_state *state, u8 reg, u16 val)
अणु
	पूर्णांक ret;

	अगर (mutex_lock_पूर्णांकerruptible(&state->i2c_buffer_lock) < 0) अणु
		dprपूर्णांकk("could not acquire lock\n");
		वापस -EINVAL;
	पूर्ण

	state->i2c_ग_लिखो_buffer[0] = val >> 8;
	state->i2c_ग_लिखो_buffer[1] = val & 0xff;

	स_रखो(&state->msg, 0, माप(काष्ठा i2c_msg));
	state->msg.addr = reg;
	state->msg.flags = 0;
	state->msg.buf = state->i2c_ग_लिखो_buffer;
	state->msg.len = 2;
	अगर (i2c_transfer(state->i2c, &state->msg, 1) != 1) अणु
		pr_warn("DiB0090 I2C write failed\n");
		ret = -EREMOTEIO;
	पूर्ण अन्यथा
		ret = 0;

	mutex_unlock(&state->i2c_buffer_lock);
	वापस ret;
पूर्ण

#घोषणा HARD_RESET(state) करो अणु  अगर (cfg->reset) अणु  अगर (cfg->sleep) cfg->sleep(fe, 0); msleep(10);  cfg->reset(fe, 1); msleep(10);  cfg->reset(fe, 0); msleep(10);  पूर्ण  पूर्ण जबतक (0)
#घोषणा ADC_TARGET -220
#घोषणा GAIN_ALPHA 5
#घोषणा WBD_ALPHA 6
#घोषणा LPF	100
अटल व्योम dib0090_ग_लिखो_regs(काष्ठा dib0090_state *state, u8 r, स्थिर u16 * b, u8 c)
अणु
	करो अणु
		dib0090_ग_लिखो_reg(state, r++, *b++);
	पूर्ण जबतक (--c);
पूर्ण

अटल पूर्णांक dib0090_identअगरy(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dib0090_state *state = fe->tuner_priv;
	u16 v;
	काष्ठा dib0090_identity *identity = &state->identity;

	v = dib0090_पढ़ो_reg(state, 0x1a);

	identity->p1g = 0;
	identity->in_soc = 0;

	dprपूर्णांकk("Tuner identification (Version = 0x%04x)\n", v);

	/* without PLL lock info */
	v &= ~KROSUS_PLL_LOCKED;

	identity->version = v & 0xff;
	identity->product = (v >> 8) & 0xf;

	अगर (identity->product != KROSUS)
		जाओ identअगरication_error;

	अगर ((identity->version & 0x3) == SOC) अणु
		identity->in_soc = 1;
		चयन (identity->version) अणु
		हाल SOC_8090_P1G_11R1:
			dprपूर्णांकk("SOC 8090 P1-G11R1 Has been detected\n");
			identity->p1g = 1;
			अवरोध;
		हाल SOC_8090_P1G_21R1:
			dprपूर्णांकk("SOC 8090 P1-G21R1 Has been detected\n");
			identity->p1g = 1;
			अवरोध;
		हाल SOC_7090_P1G_11R1:
			dprपूर्णांकk("SOC 7090 P1-G11R1 Has been detected\n");
			identity->p1g = 1;
			अवरोध;
		हाल SOC_7090_P1G_21R1:
			dprपूर्णांकk("SOC 7090 P1-G21R1 Has been detected\n");
			identity->p1g = 1;
			अवरोध;
		शेष:
			जाओ identअगरication_error;
		पूर्ण
	पूर्ण अन्यथा अणु
		चयन ((identity->version >> 5) & 0x7) अणु
		हाल MP001:
			dprपूर्णांकk("MP001 : 9090/8096\n");
			अवरोध;
		हाल MP005:
			dprपूर्णांकk("MP005 : Single Sband\n");
			अवरोध;
		हाल MP008:
			dprपूर्णांकk("MP008 : diversity VHF-UHF-LBAND\n");
			अवरोध;
		हाल MP009:
			dprपूर्णांकk("MP009 : diversity 29098 CBAND-UHF-LBAND-SBAND\n");
			अवरोध;
		शेष:
			जाओ identअगरication_error;
		पूर्ण

		चयन (identity->version & 0x1f) अणु
		हाल P1G_21R2:
			dprपूर्णांकk("P1G_21R2 detected\n");
			identity->p1g = 1;
			अवरोध;
		हाल P1G:
			dprपूर्णांकk("P1G detected\n");
			identity->p1g = 1;
			अवरोध;
		हाल P1D_E_F:
			dprपूर्णांकk("P1D/E/F detected\n");
			अवरोध;
		हाल P1C:
			dprपूर्णांकk("P1C detected\n");
			अवरोध;
		हाल P1A_B:
			dprपूर्णांकk("P1-A/B detected: driver is deactivated - not available\n");
			जाओ identअगरication_error;
			अवरोध;
		शेष:
			जाओ identअगरication_error;
		पूर्ण
	पूर्ण

	वापस 0;

identअगरication_error:
	वापस -EIO;
पूर्ण

अटल पूर्णांक dib0090_fw_identअगरy(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dib0090_fw_state *state = fe->tuner_priv;
	काष्ठा dib0090_identity *identity = &state->identity;

	u16 v = dib0090_fw_पढ़ो_reg(state, 0x1a);
	identity->p1g = 0;
	identity->in_soc = 0;

	dprपूर्णांकk("FE: Tuner identification (Version = 0x%04x)\n", v);

	/* without PLL lock info */
	v &= ~KROSUS_PLL_LOCKED;

	identity->version = v & 0xff;
	identity->product = (v >> 8) & 0xf;

	अगर (identity->product != KROSUS)
		जाओ identअगरication_error;

	अगर ((identity->version & 0x3) == SOC) अणु
		identity->in_soc = 1;
		चयन (identity->version) अणु
		हाल SOC_8090_P1G_11R1:
			dprपूर्णांकk("SOC 8090 P1-G11R1 Has been detected\n");
			identity->p1g = 1;
			अवरोध;
		हाल SOC_8090_P1G_21R1:
			dprपूर्णांकk("SOC 8090 P1-G21R1 Has been detected\n");
			identity->p1g = 1;
			अवरोध;
		हाल SOC_7090_P1G_11R1:
			dprपूर्णांकk("SOC 7090 P1-G11R1 Has been detected\n");
			identity->p1g = 1;
			अवरोध;
		हाल SOC_7090_P1G_21R1:
			dprपूर्णांकk("SOC 7090 P1-G21R1 Has been detected\n");
			identity->p1g = 1;
			अवरोध;
		शेष:
			जाओ identअगरication_error;
		पूर्ण
	पूर्ण अन्यथा अणु
		चयन ((identity->version >> 5) & 0x7) अणु
		हाल MP001:
			dprपूर्णांकk("MP001 : 9090/8096\n");
			अवरोध;
		हाल MP005:
			dprपूर्णांकk("MP005 : Single Sband\n");
			अवरोध;
		हाल MP008:
			dprपूर्णांकk("MP008 : diversity VHF-UHF-LBAND\n");
			अवरोध;
		हाल MP009:
			dprपूर्णांकk("MP009 : diversity 29098 CBAND-UHF-LBAND-SBAND\n");
			अवरोध;
		शेष:
			जाओ identअगरication_error;
		पूर्ण

		चयन (identity->version & 0x1f) अणु
		हाल P1G_21R2:
			dprपूर्णांकk("P1G_21R2 detected\n");
			identity->p1g = 1;
			अवरोध;
		हाल P1G:
			dprपूर्णांकk("P1G detected\n");
			identity->p1g = 1;
			अवरोध;
		हाल P1D_E_F:
			dprपूर्णांकk("P1D/E/F detected\n");
			अवरोध;
		हाल P1C:
			dprपूर्णांकk("P1C detected\n");
			अवरोध;
		हाल P1A_B:
			dprपूर्णांकk("P1-A/B detected: driver is deactivated - not available\n");
			जाओ identअगरication_error;
			अवरोध;
		शेष:
			जाओ identअगरication_error;
		पूर्ण
	पूर्ण

	वापस 0;

identअगरication_error:
	वापस -EIO;
पूर्ण

अटल व्योम dib0090_reset_digital(काष्ठा dvb_frontend *fe, स्थिर काष्ठा dib0090_config *cfg)
अणु
	काष्ठा dib0090_state *state = fe->tuner_priv;
	u16 PllCfg, i, v;

	HARD_RESET(state);
	dib0090_ग_लिखो_reg(state, 0x24, EN_PLL | EN_CRYSTAL);
	अगर (cfg->in_soc)
		वापस;

	dib0090_ग_लिखो_reg(state, 0x1b, EN_DIGCLK | EN_PLL | EN_CRYSTAL);	/* PLL, DIG_CLK and CRYSTAL reमुख्य */
	/* adcClkOutRatio=8->7, release reset */
	dib0090_ग_लिखो_reg(state, 0x20, ((cfg->io.adc_घड़ी_ratio - 1) << 11) | (0 << 10) | (1 << 9) | (1 << 8) | (0 << 4) | 0);
	अगर (cfg->clkoutdrive != 0)
		dib0090_ग_लिखो_reg(state, 0x23, (0 << 15) | ((!cfg->analog_output) << 14) | (2 << 10) | (1 << 9) | (0 << 8)
				| (cfg->clkoutdrive << 5) | (cfg->clkouttobamse << 4) | (0 << 2) | (0));
	अन्यथा
		dib0090_ग_लिखो_reg(state, 0x23, (0 << 15) | ((!cfg->analog_output) << 14) | (2 << 10) | (1 << 9) | (0 << 8)
				| (7 << 5) | (cfg->clkouttobamse << 4) | (0 << 2) | (0));

	/* Read Pll current config * */
	PllCfg = dib0090_पढ़ो_reg(state, 0x21);

	/** Reconfigure PLL अगर current setting is dअगरferent from शेष setting **/
	अगर ((PllCfg & 0x1FFF) != ((cfg->io.pll_range << 12) | (cfg->io.pll_loopभाग << 6) | (cfg->io.pll_preभाग)) && (!cfg->in_soc)
			&& !cfg->io.pll_bypass) अणु

		/* Set Bypass mode */
		PllCfg |= (1 << 15);
		dib0090_ग_लिखो_reg(state, 0x21, PllCfg);

		/* Set Reset Pll */
		PllCfg &= ~(1 << 13);
		dib0090_ग_लिखो_reg(state, 0x21, PllCfg);

	/*** Set new Pll configuration in bypass and reset state ***/
		PllCfg = (1 << 15) | (0 << 13) | (cfg->io.pll_range << 12) | (cfg->io.pll_loopभाग << 6) | (cfg->io.pll_preभाग);
		dib0090_ग_लिखो_reg(state, 0x21, PllCfg);

		/* Remove Reset Pll */
		PllCfg |= (1 << 13);
		dib0090_ग_लिखो_reg(state, 0x21, PllCfg);

	/*** Wait क्रम PLL lock ***/
		i = 100;
		करो अणु
			v = !!(dib0090_पढ़ो_reg(state, 0x1a) & 0x800);
			अगर (v)
				अवरोध;
		पूर्ण जबतक (--i);

		अगर (i == 0) अणु
			dprपूर्णांकk("Pll: Unable to lock Pll\n");
			वापस;
		पूर्ण

		/* Finally Remove Bypass mode */
		PllCfg &= ~(1 << 15);
		dib0090_ग_लिखो_reg(state, 0x21, PllCfg);
	पूर्ण

	अगर (cfg->io.pll_bypass) अणु
		PllCfg |= (cfg->io.pll_bypass << 15);
		dib0090_ग_लिखो_reg(state, 0x21, PllCfg);
	पूर्ण
पूर्ण

अटल पूर्णांक dib0090_fw_reset_digital(काष्ठा dvb_frontend *fe, स्थिर काष्ठा dib0090_config *cfg)
अणु
	काष्ठा dib0090_fw_state *state = fe->tuner_priv;
	u16 PllCfg;
	u16 v;
	पूर्णांक i;

	dprपूर्णांकk("fw reset digital\n");
	HARD_RESET(state);

	dib0090_fw_ग_लिखो_reg(state, 0x24, EN_PLL | EN_CRYSTAL);
	dib0090_fw_ग_लिखो_reg(state, 0x1b, EN_DIGCLK | EN_PLL | EN_CRYSTAL);	/* PLL, DIG_CLK and CRYSTAL reमुख्य */

	dib0090_fw_ग_लिखो_reg(state, 0x20,
			((cfg->io.adc_घड़ी_ratio - 1) << 11) | (0 << 10) | (1 << 9) | (1 << 8) | (cfg->data_tx_drv << 4) | cfg->ls_cfg_pad_drv);

	v = (0 << 15) | ((!cfg->analog_output) << 14) | (1 << 9) | (0 << 8) | (cfg->clkouttobamse << 4) | (0 << 2) | (0);
	अगर (cfg->clkoutdrive != 0)
		v |= cfg->clkoutdrive << 5;
	अन्यथा
		v |= 7 << 5;

	v |= 2 << 10;
	dib0090_fw_ग_लिखो_reg(state, 0x23, v);

	/* Read Pll current config * */
	PllCfg = dib0090_fw_पढ़ो_reg(state, 0x21);

	/** Reconfigure PLL अगर current setting is dअगरferent from शेष setting **/
	अगर ((PllCfg & 0x1FFF) != ((cfg->io.pll_range << 12) | (cfg->io.pll_loopभाग << 6) | (cfg->io.pll_preभाग)) && !cfg->io.pll_bypass) अणु

		/* Set Bypass mode */
		PllCfg |= (1 << 15);
		dib0090_fw_ग_लिखो_reg(state, 0x21, PllCfg);

		/* Set Reset Pll */
		PllCfg &= ~(1 << 13);
		dib0090_fw_ग_लिखो_reg(state, 0x21, PllCfg);

	/*** Set new Pll configuration in bypass and reset state ***/
		PllCfg = (1 << 15) | (0 << 13) | (cfg->io.pll_range << 12) | (cfg->io.pll_loopभाग << 6) | (cfg->io.pll_preभाग);
		dib0090_fw_ग_लिखो_reg(state, 0x21, PllCfg);

		/* Remove Reset Pll */
		PllCfg |= (1 << 13);
		dib0090_fw_ग_लिखो_reg(state, 0x21, PllCfg);

	/*** Wait क्रम PLL lock ***/
		i = 100;
		करो अणु
			v = !!(dib0090_fw_पढ़ो_reg(state, 0x1a) & 0x800);
			अगर (v)
				अवरोध;
		पूर्ण जबतक (--i);

		अगर (i == 0) अणु
			dprपूर्णांकk("Pll: Unable to lock Pll\n");
			वापस -EIO;
		पूर्ण

		/* Finally Remove Bypass mode */
		PllCfg &= ~(1 << 15);
		dib0090_fw_ग_लिखो_reg(state, 0x21, PllCfg);
	पूर्ण

	अगर (cfg->io.pll_bypass) अणु
		PllCfg |= (cfg->io.pll_bypass << 15);
		dib0090_fw_ग_लिखो_reg(state, 0x21, PllCfg);
	पूर्ण

	वापस dib0090_fw_identअगरy(fe);
पूर्ण

अटल पूर्णांक dib0090_wakeup(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dib0090_state *state = fe->tuner_priv;
	अगर (state->config->sleep)
		state->config->sleep(fe, 0);

	/* enable dataTX in हाल we have been restarted in the wrong moment */
	dib0090_ग_लिखो_reg(state, 0x23, dib0090_पढ़ो_reg(state, 0x23) | (1 << 14));
	वापस 0;
पूर्ण

अटल पूर्णांक dib0090_sleep(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dib0090_state *state = fe->tuner_priv;
	अगर (state->config->sleep)
		state->config->sleep(fe, 1);
	वापस 0;
पूर्ण

व्योम dib0090_dcc_freq(काष्ठा dvb_frontend *fe, u8 fast)
अणु
	काष्ठा dib0090_state *state = fe->tuner_priv;
	अगर (fast)
		dib0090_ग_लिखो_reg(state, 0x04, 0);
	अन्यथा
		dib0090_ग_लिखो_reg(state, 0x04, 1);
पूर्ण

EXPORT_SYMBOL(dib0090_dcc_freq);

अटल स्थिर u16 bb_ramp_pwm_normal_socs[] = अणु
	550, /* max BB gain in 10th of dB */
	(1<<9) | 8, /* ramp_slope = 1dB of gain -> घड़ी_प्रकारicks_per_db = clk_khz / ramp_slope -> BB_RAMP2 */
	440,
	(4  << 9) | 0, /* BB_RAMP3 = 26dB */
	(0  << 9) | 208, /* BB_RAMP4 */
	(4  << 9) | 208, /* BB_RAMP5 = 29dB */
	(0  << 9) | 440, /* BB_RAMP6 */
पूर्ण;

अटल स्थिर u16 rf_ramp_pwm_cband_7090p[] = अणु
	280, /* max RF gain in 10th of dB */
	18, /* ramp_slope = 1dB of gain -> घड़ी_प्रकारicks_per_db = clk_khz / ramp_slope -> RF_RAMP2 */
	504, /* ramp_max = maximum X used on the ramp */
	(29 << 10) | 364, /* RF_RAMP5, LNA 1 = 8dB */
	(0  << 10) | 504, /* RF_RAMP6, LNA 1 */
	(60 << 10) | 228, /* RF_RAMP7, LNA 2 = 7.7dB */
	(0  << 10) | 364, /* RF_RAMP8, LNA 2 */
	(34 << 10) | 109, /* GAIN_4_1, LNA 3 = 6.8dB */
	(0  << 10) | 228, /* GAIN_4_2, LNA 3 */
	(37 << 10) | 0, /* RF_RAMP3, LNA 4 = 6.2dB */
	(0  << 10) | 109, /* RF_RAMP4, LNA 4 */
पूर्ण;

अटल स्थिर u16 rf_ramp_pwm_cband_7090e_sensitivity[] = अणु
	186, /* max RF gain in 10th of dB */
	40, /* ramp_slope = 1dB of gain -> घड़ी_प्रकारicks_per_db = clk_khz / ramp_slope -> RF_RAMP2 */
	746, /* ramp_max = maximum X used on the ramp */
	(10 << 10) | 345, /* RF_RAMP5, LNA 1 = 10dB */
	(0  << 10) | 746, /* RF_RAMP6, LNA 1 */
	(0 << 10) | 0, /* RF_RAMP7, LNA 2 = 0 dB */
	(0  << 10) | 0, /* RF_RAMP8, LNA 2 */
	(28 << 10) | 200, /* GAIN_4_1, LNA 3 = 6.8dB */ /* 3.61 dB */
	(0  << 10) | 345, /* GAIN_4_2, LNA 3 */
	(20 << 10) | 0, /* RF_RAMP3, LNA 4 = 6.2dB */ /* 4.96 dB */
	(0  << 10) | 200, /* RF_RAMP4, LNA 4 */
पूर्ण;

अटल स्थिर u16 rf_ramp_pwm_cband_7090e_aci[] = अणु
	86, /* max RF gain in 10th of dB */
	40, /* ramp_slope = 1dB of gain -> घड़ी_प्रकारicks_per_db = clk_khz / ramp_slope -> RF_RAMP2 */
	345, /* ramp_max = maximum X used on the ramp */
	(0 << 10) | 0, /* RF_RAMP5, LNA 1 = 8dB */ /* 7.47 dB */
	(0 << 10) | 0, /* RF_RAMP6, LNA 1 */
	(0 << 10) | 0, /* RF_RAMP7, LNA 2 = 0 dB */
	(0 << 10) | 0, /* RF_RAMP8, LNA 2 */
	(28 << 10) | 200, /* GAIN_4_1, LNA 3 = 6.8dB */ /* 3.61 dB */
	(0  << 10) | 345, /* GAIN_4_2, LNA 3 */
	(20 << 10) | 0, /* RF_RAMP3, LNA 4 = 6.2dB */ /* 4.96 dB */
	(0  << 10) | 200, /* RF_RAMP4, LNA 4 */
पूर्ण;

अटल स्थिर u16 rf_ramp_pwm_cband_8090[] = अणु
	345, /* max RF gain in 10th of dB */
	29, /* ramp_slope = 1dB of gain -> घड़ी_प्रकारicks_per_db = clk_khz / ramp_slope -> RF_RAMP2 */
	1000, /* ramp_max = maximum X used on the ramp */
	(35 << 10) | 772, /* RF_RAMP3, LNA 1 = 8dB */
	(0  << 10) | 1000, /* RF_RAMP4, LNA 1 */
	(58 << 10) | 496, /* RF_RAMP5, LNA 2 = 9.5dB */
	(0  << 10) | 772, /* RF_RAMP6, LNA 2 */
	(27 << 10) | 200, /* RF_RAMP7, LNA 3 = 10.5dB */
	(0  << 10) | 496, /* RF_RAMP8, LNA 3 */
	(40 << 10) | 0, /* GAIN_4_1, LNA 4 = 7dB */
	(0  << 10) | 200, /* GAIN_4_2, LNA 4 */
पूर्ण;

अटल स्थिर u16 rf_ramp_pwm_uhf_7090[] = अणु
	407, /* max RF gain in 10th of dB */
	13, /* ramp_slope = 1dB of gain -> घड़ी_प्रकारicks_per_db = clk_khz / ramp_slope -> RF_RAMP2 */
	529, /* ramp_max = maximum X used on the ramp */
	(23 << 10) | 0, /* RF_RAMP3, LNA 1 = 14.7dB */
	(0  << 10) | 176, /* RF_RAMP4, LNA 1 */
	(63 << 10) | 400, /* RF_RAMP5, LNA 2 = 8dB */
	(0  << 10) | 529, /* RF_RAMP6, LNA 2 */
	(48 << 10) | 316, /* RF_RAMP7, LNA 3 = 6.8dB */
	(0  << 10) | 400, /* RF_RAMP8, LNA 3 */
	(29 << 10) | 176, /* GAIN_4_1, LNA 4 = 11.5dB */
	(0  << 10) | 316, /* GAIN_4_2, LNA 4 */
पूर्ण;

अटल स्थिर u16 rf_ramp_pwm_uhf_8090[] = अणु
	388, /* max RF gain in 10th of dB */
	26, /* ramp_slope = 1dB of gain -> घड़ी_प्रकारicks_per_db = clk_khz / ramp_slope -> RF_RAMP2 */
	1008, /* ramp_max = maximum X used on the ramp */
	(11 << 10) | 0, /* RF_RAMP3, LNA 1 = 14.7dB */
	(0  << 10) | 369, /* RF_RAMP4, LNA 1 */
	(41 << 10) | 809, /* RF_RAMP5, LNA 2 = 8dB */
	(0  << 10) | 1008, /* RF_RAMP6, LNA 2 */
	(27 << 10) | 659, /* RF_RAMP7, LNA 3 = 6dB */
	(0  << 10) | 809, /* RF_RAMP8, LNA 3 */
	(14 << 10) | 369, /* GAIN_4_1, LNA 4 = 11.5dB */
	(0  << 10) | 659, /* GAIN_4_2, LNA 4 */
पूर्ण;

/* GENERAL PWM ramp definition क्रम all other Krosus */
अटल स्थिर u16 bb_ramp_pwm_normal[] = अणु
	500, /* max BB gain in 10th of dB */
	8, /* ramp_slope = 1dB of gain -> घड़ी_प्रकारicks_per_db = clk_khz / ramp_slope -> BB_RAMP2 */
	400,
	(2  << 9) | 0, /* BB_RAMP3 = 21dB */
	(0  << 9) | 168, /* BB_RAMP4 */
	(2  << 9) | 168, /* BB_RAMP5 = 29dB */
	(0  << 9) | 400, /* BB_RAMP6 */
पूर्ण;

#अगर 0
/* Currently unused */
अटल स्थिर u16 bb_ramp_pwm_boost[] = अणु
	550, /* max BB gain in 10th of dB */
	8, /* ramp_slope = 1dB of gain -> घड़ी_प्रकारicks_per_db = clk_khz / ramp_slope -> BB_RAMP2 */
	440,
	(2  << 9) | 0, /* BB_RAMP3 = 26dB */
	(0  << 9) | 208, /* BB_RAMP4 */
	(2  << 9) | 208, /* BB_RAMP5 = 29dB */
	(0  << 9) | 440, /* BB_RAMP6 */
पूर्ण;
#पूर्ण_अगर

अटल स्थिर u16 rf_ramp_pwm_cband[] = अणु
	314, /* max RF gain in 10th of dB */
	33, /* ramp_slope = 1dB of gain -> घड़ी_प्रकारicks_per_db = clk_khz / ramp_slope -> RF_RAMP2 */
	1023, /* ramp_max = maximum X used on the ramp */
	(8  << 10) | 743, /* RF_RAMP3, LNA 1 = 0dB */
	(0  << 10) | 1023, /* RF_RAMP4, LNA 1 */
	(15 << 10) | 469, /* RF_RAMP5, LNA 2 = 0dB */
	(0  << 10) | 742, /* RF_RAMP6, LNA 2 */
	(9  << 10) | 234, /* RF_RAMP7, LNA 3 = 0dB */
	(0  << 10) | 468, /* RF_RAMP8, LNA 3 */
	(9  << 10) | 0, /* GAIN_4_1, LNA 4 = 0dB */
	(0  << 10) | 233, /* GAIN_4_2, LNA 4 */
पूर्ण;

अटल स्थिर u16 rf_ramp_pwm_vhf[] = अणु
	398, /* max RF gain in 10th of dB */
	24, /* ramp_slope = 1dB of gain -> घड़ी_प्रकारicks_per_db = clk_khz / ramp_slope -> RF_RAMP2 */
	954, /* ramp_max = maximum X used on the ramp */
	(7  << 10) | 0, /* RF_RAMP3, LNA 1 = 13.2dB */
	(0  << 10) | 290, /* RF_RAMP4, LNA 1 */
	(16 << 10) | 699, /* RF_RAMP5, LNA 2 = 10.5dB */
	(0  << 10) | 954, /* RF_RAMP6, LNA 2 */
	(17 << 10) | 580, /* RF_RAMP7, LNA 3 = 5dB */
	(0  << 10) | 699, /* RF_RAMP8, LNA 3 */
	(7  << 10) | 290, /* GAIN_4_1, LNA 4 = 12.5dB */
	(0  << 10) | 580, /* GAIN_4_2, LNA 4 */
पूर्ण;

अटल स्थिर u16 rf_ramp_pwm_uhf[] = अणु
	398, /* max RF gain in 10th of dB */
	24, /* ramp_slope = 1dB of gain -> घड़ी_प्रकारicks_per_db = clk_khz / ramp_slope -> RF_RAMP2 */
	954, /* ramp_max = maximum X used on the ramp */
	(7  << 10) | 0, /* RF_RAMP3, LNA 1 = 13.2dB */
	(0  << 10) | 290, /* RF_RAMP4, LNA 1 */
	(16 << 10) | 699, /* RF_RAMP5, LNA 2 = 10.5dB */
	(0  << 10) | 954, /* RF_RAMP6, LNA 2 */
	(17 << 10) | 580, /* RF_RAMP7, LNA 3 = 5dB */
	(0  << 10) | 699, /* RF_RAMP8, LNA 3 */
	(7  << 10) | 290, /* GAIN_4_1, LNA 4 = 12.5dB */
	(0  << 10) | 580, /* GAIN_4_2, LNA 4 */
पूर्ण;

#अगर 0
/* Currently unused */
अटल स्थिर u16 rf_ramp_pwm_sband[] = अणु
	253, /* max RF gain in 10th of dB */
	38, /* ramp_slope = 1dB of gain -> घड़ी_प्रकारicks_per_db = clk_khz / ramp_slope -> RF_RAMP2 */
	961,
	(4  << 10) | 0, /* RF_RAMP3, LNA 1 = 14.1dB */
	(0  << 10) | 508, /* RF_RAMP4, LNA 1 */
	(9  << 10) | 508, /* RF_RAMP5, LNA 2 = 11.2dB */
	(0  << 10) | 961, /* RF_RAMP6, LNA 2 */
	(0  << 10) | 0, /* RF_RAMP7, LNA 3 = 0dB */
	(0  << 10) | 0, /* RF_RAMP8, LNA 3 */
	(0  << 10) | 0, /* GAIN_4_1, LNA 4 = 0dB */
	(0  << 10) | 0, /* GAIN_4_2, LNA 4 */
पूर्ण;
#पूर्ण_अगर

काष्ठा slope अणु
	s16 range;
	s16 slope;
पूर्ण;
अटल u16 slopes_to_scale(स्थिर काष्ठा slope *slopes, u8 num, s16 val)
अणु
	u8 i;
	u16 rest;
	u16 ret = 0;
	क्रम (i = 0; i < num; i++) अणु
		अगर (val > slopes[i].range)
			rest = slopes[i].range;
		अन्यथा
			rest = val;
		ret += (rest * slopes[i].slope) / slopes[i].range;
		val -= rest;
	पूर्ण
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा slope dib0090_wbd_slopes[3] = अणु
	अणु66, 120पूर्ण,		/* -64,-52: offset -   65 */
	अणु600, 170पूर्ण,		/* -52,-35: 65     -  665 */
	अणु170, 250पूर्ण,		/* -45,-10: 665    - 835 */
पूर्ण;

अटल s16 dib0090_wbd_to_db(काष्ठा dib0090_state *state, u16 wbd)
अणु
	wbd &= 0x3ff;
	अगर (wbd < state->wbd_offset)
		wbd = 0;
	अन्यथा
		wbd -= state->wbd_offset;
	/* -64dB is the न्यूनमान */
	वापस -640 + (s16) slopes_to_scale(dib0090_wbd_slopes, ARRAY_SIZE(dib0090_wbd_slopes), wbd);
पूर्ण

अटल व्योम dib0090_wbd_target(काष्ठा dib0090_state *state, u32 rf)
अणु
	u16 offset = 250;

	/* TODO : DAB digital N+/-1 पूर्णांकerferer perfs : offset = 10 */

	अगर (state->current_band == BAND_VHF)
		offset = 650;
#अगर_अघोषित FIRMWARE_FIREFLY
	अगर (state->current_band == BAND_VHF)
		offset = state->config->wbd_vhf_offset;
	अगर (state->current_band == BAND_CBAND)
		offset = state->config->wbd_cband_offset;
#पूर्ण_अगर

	state->wbd_target = dib0090_wbd_to_db(state, state->wbd_offset + offset);
	dprपूर्णांकk("wbd-target: %d dB\n", (u32) state->wbd_target);
पूर्ण

अटल स्थिर पूर्णांक gain_reg_addr[4] = अणु
	0x08, 0x0a, 0x0f, 0x01
पूर्ण;

अटल व्योम dib0090_gain_apply(काष्ठा dib0090_state *state, s16 gain_delta, s16 top_delta, u8 क्रमce)
अणु
	u16 rf, bb, ref;
	u16 i, v, gain_reg[4] = अणु 0 पूर्ण, gain;
	स्थिर u16 *g;

	अगर (top_delta < -511)
		top_delta = -511;
	अगर (top_delta > 511)
		top_delta = 511;

	अगर (क्रमce) अणु
		top_delta *= (1 << WBD_ALPHA);
		gain_delta *= (1 << GAIN_ALPHA);
	पूर्ण

	अगर (top_delta >= ((s16) (state->rf_ramp[0] << WBD_ALPHA) - state->rf_gain_limit))	/* overflow */
		state->rf_gain_limit = state->rf_ramp[0] << WBD_ALPHA;
	अन्यथा
		state->rf_gain_limit += top_delta;

	अगर (state->rf_gain_limit < 0)	/*underflow */
		state->rf_gain_limit = 0;

	/* use gain as a temporary variable and correct current_gain */
	gain = ((state->rf_gain_limit >> WBD_ALPHA) + state->bb_ramp[0]) << GAIN_ALPHA;
	अगर (gain_delta >= ((s16) gain - state->current_gain))	/* overflow */
		state->current_gain = gain;
	अन्यथा
		state->current_gain += gain_delta;
	/* cannot be less than 0 (only अगर gain_delta is less than 0 we can have current_gain < 0) */
	अगर (state->current_gain < 0)
		state->current_gain = 0;

	/* now split total gain to rf and bb gain */
	gain = state->current_gain >> GAIN_ALPHA;

	/* requested gain is bigger than rf gain limit - ACI/WBD adjusपंचांगent */
	अगर (gain > (state->rf_gain_limit >> WBD_ALPHA)) अणु
		rf = state->rf_gain_limit >> WBD_ALPHA;
		bb = gain - rf;
		अगर (bb > state->bb_ramp[0])
			bb = state->bb_ramp[0];
	पूर्ण अन्यथा अणु		/* high संकेत level -> all gains put on RF */
		rf = gain;
		bb = 0;
	पूर्ण

	state->gain[0] = rf;
	state->gain[1] = bb;

	/* software ramp */
	/* Start with RF gains */
	g = state->rf_ramp + 1;	/* poपूर्णांक on RF LNA1 max gain */
	ref = rf;
	क्रम (i = 0; i < 7; i++) अणु	/* Go over all amplअगरiers => 5RF amps + 2 BB amps = 7 amps */
		अगर (g[0] == 0 || ref < (g[1] - g[0]))	/* अगर total gain of the current amp is null or this amp is not concerned because it starts to work from an higher gain value */
			v = 0;	/* क्रमce the gain to ग_लिखो क्रम the current amp to be null */
		अन्यथा अगर (ref >= g[1])	/* Gain to set is higher than the high working poपूर्णांक of this amp */
			v = g[2];	/* क्रमce this amp to be full gain */
		अन्यथा		/* compute the value to set to this amp because we are somewhere in his range */
			v = ((ref - (g[1] - g[0])) * g[2]) / g[0];

		अगर (i == 0)	/* LNA 1 reg mapping */
			gain_reg[0] = v;
		अन्यथा अगर (i == 1)	/* LNA 2 reg mapping */
			gain_reg[0] |= v << 7;
		अन्यथा अगर (i == 2)	/* LNA 3 reg mapping */
			gain_reg[1] = v;
		अन्यथा अगर (i == 3)	/* LNA 4 reg mapping */
			gain_reg[1] |= v << 7;
		अन्यथा अगर (i == 4)	/* CBAND LNA reg mapping */
			gain_reg[2] = v | state->rf_lt_def;
		अन्यथा अगर (i == 5)	/* BB gain 1 reg mapping */
			gain_reg[3] = v << 3;
		अन्यथा अगर (i == 6)	/* BB gain 2 reg mapping */
			gain_reg[3] |= v << 8;

		g += 3;		/* go to next gain bloc */

		/* When RF is finished, start with BB */
		अगर (i == 4) अणु
			g = state->bb_ramp + 1;	/* poपूर्णांक on BB gain 1 max gain */
			ref = bb;
		पूर्ण
	पूर्ण
	gain_reg[3] |= state->bb_1_def;
	gain_reg[3] |= ((bb % 10) * 100) / 125;

#अगर_घोषित DEBUG_AGC
	dprपूर्णांकk("GA CALC: DB: %3d(rf) + %3d(bb) = %3d gain_reg[0]=%04x gain_reg[1]=%04x gain_reg[2]=%04x gain_reg[0]=%04x\n", rf, bb, rf + bb,
		gain_reg[0], gain_reg[1], gain_reg[2], gain_reg[3]);
#पूर्ण_अगर

	/* Write the amplअगरier regs */
	क्रम (i = 0; i < 4; i++) अणु
		v = gain_reg[i];
		अगर (क्रमce || state->gain_reg[i] != v) अणु
			state->gain_reg[i] = v;
			dib0090_ग_लिखो_reg(state, gain_reg_addr[i], v);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम dib0090_set_boost(काष्ठा dib0090_state *state, पूर्णांक onoff)
अणु
	state->bb_1_def &= 0xdfff;
	state->bb_1_def |= onoff << 13;
पूर्ण

अटल व्योम dib0090_set_rframp(काष्ठा dib0090_state *state, स्थिर u16 * cfg)
अणु
	state->rf_ramp = cfg;
पूर्ण

अटल व्योम dib0090_set_rframp_pwm(काष्ठा dib0090_state *state, स्थिर u16 * cfg)
अणु
	state->rf_ramp = cfg;

	dib0090_ग_लिखो_reg(state, 0x2a, 0xffff);

	dprपूर्णांकk("total RF gain: %ddB, step: %d\n", (u32) cfg[0], dib0090_पढ़ो_reg(state, 0x2a));

	dib0090_ग_लिखो_regs(state, 0x2c, cfg + 3, 6);
	dib0090_ग_लिखो_regs(state, 0x3e, cfg + 9, 2);
पूर्ण

अटल व्योम dib0090_set_bbramp(काष्ठा dib0090_state *state, स्थिर u16 * cfg)
अणु
	state->bb_ramp = cfg;
	dib0090_set_boost(state, cfg[0] > 500);	/* we want the boost अगर the gain is higher that 50dB */
पूर्ण

अटल व्योम dib0090_set_bbramp_pwm(काष्ठा dib0090_state *state, स्थिर u16 * cfg)
अणु
	state->bb_ramp = cfg;

	dib0090_set_boost(state, cfg[0] > 500);	/* we want the boost अगर the gain is higher that 50dB */

	dib0090_ग_लिखो_reg(state, 0x33, 0xffff);
	dprपूर्णांकk("total BB gain: %ddB, step: %d\n", (u32) cfg[0], dib0090_पढ़ो_reg(state, 0x33));
	dib0090_ग_लिखो_regs(state, 0x35, cfg + 3, 4);
पूर्ण

व्योम dib0090_pwm_gain_reset(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dib0090_state *state = fe->tuner_priv;
	स्थिर u16 *bb_ramp = bb_ramp_pwm_normal; /* शेष baseband config */
	स्थिर u16 *rf_ramp = शून्य;
	u8 en_pwm_rf_mux = 1;

	/* reset the AGC */
	अगर (state->config->use_pwm_agc) अणु
		अगर (state->current_band == BAND_CBAND) अणु
			अगर (state->identity.in_soc) अणु
				bb_ramp = bb_ramp_pwm_normal_socs;
				अगर (state->identity.version == SOC_8090_P1G_11R1 || state->identity.version == SOC_8090_P1G_21R1)
					rf_ramp = rf_ramp_pwm_cband_8090;
				अन्यथा अगर (state->identity.version == SOC_7090_P1G_11R1 || state->identity.version == SOC_7090_P1G_21R1) अणु
					अगर (state->config->is_dib7090e) अणु
						अगर (state->rf_ramp == शून्य)
							rf_ramp = rf_ramp_pwm_cband_7090e_sensitivity;
						अन्यथा
							rf_ramp = state->rf_ramp;
					पूर्ण अन्यथा
						rf_ramp = rf_ramp_pwm_cband_7090p;
				पूर्ण
			पूर्ण अन्यथा
				rf_ramp = rf_ramp_pwm_cband;
		पूर्ण अन्यथा

			अगर (state->current_band == BAND_VHF) अणु
				अगर (state->identity.in_soc) अणु
					bb_ramp = bb_ramp_pwm_normal_socs;
					/* rf_ramp = &rf_ramp_pwm_vhf_socs; */ /* TODO */
				पूर्ण अन्यथा
					rf_ramp = rf_ramp_pwm_vhf;
			पूर्ण अन्यथा अगर (state->current_band == BAND_UHF) अणु
				अगर (state->identity.in_soc) अणु
					bb_ramp = bb_ramp_pwm_normal_socs;
					अगर (state->identity.version == SOC_8090_P1G_11R1 || state->identity.version == SOC_8090_P1G_21R1)
						rf_ramp = rf_ramp_pwm_uhf_8090;
					अन्यथा अगर (state->identity.version == SOC_7090_P1G_11R1 || state->identity.version == SOC_7090_P1G_21R1)
						rf_ramp = rf_ramp_pwm_uhf_7090;
				पूर्ण अन्यथा
					rf_ramp = rf_ramp_pwm_uhf;
			पूर्ण
		अगर (rf_ramp)
			dib0090_set_rframp_pwm(state, rf_ramp);
		dib0090_set_bbramp_pwm(state, bb_ramp);

		/* activate the ramp generator using PWM control */
		अगर (state->rf_ramp)
			dprपूर्णांकk("ramp RF gain = %d BAND = %s version = %d\n",
				state->rf_ramp[0],
				(state->current_band == BAND_CBAND) ? "CBAND" : "NOT CBAND",
				state->identity.version & 0x1f);

		अगर (rf_ramp && ((state->rf_ramp && state->rf_ramp[0] == 0) ||
		    (state->current_band == BAND_CBAND &&
		    (state->identity.version & 0x1f) <= P1D_E_F))) अणु
			dprपूर्णांकk("DE-Engage mux for direct gain reg control\n");
			en_pwm_rf_mux = 0;
		पूर्ण अन्यथा
			dprपूर्णांकk("Engage mux for PWM control\n");

		dib0090_ग_लिखो_reg(state, 0x32, (en_pwm_rf_mux << 12) | (en_pwm_rf_mux << 11));

		/* Set fast servo cutoff to start AGC; 0 = 1KHz ; 1 = 50Hz ; 2 = 150Hz ; 3 = 50KHz ; 4 = servo fast*/
		अगर (state->identity.version == SOC_7090_P1G_11R1 || state->identity.version == SOC_7090_P1G_21R1)
			dib0090_ग_लिखो_reg(state, 0x04, 3);
		अन्यथा
			dib0090_ग_लिखो_reg(state, 0x04, 1);
		dib0090_ग_लिखो_reg(state, 0x39, (1 << 10)); /* 0 gain by शेष */
	पूर्ण
पूर्ण
EXPORT_SYMBOL(dib0090_pwm_gain_reset);

व्योम dib0090_set_dc_servo(काष्ठा dvb_frontend *fe, u8 DC_servo_cutoff)
अणु
	काष्ठा dib0090_state *state = fe->tuner_priv;
	अगर (DC_servo_cutoff < 4)
		dib0090_ग_लिखो_reg(state, 0x04, DC_servo_cutoff);
पूर्ण
EXPORT_SYMBOL(dib0090_set_dc_servo);

अटल u32 dib0090_get_slow_adc_val(काष्ठा dib0090_state *state)
अणु
	u16 adc_val = dib0090_पढ़ो_reg(state, 0x1d);
	अगर (state->identity.in_soc)
		adc_val >>= 2;
	वापस adc_val;
पूर्ण

पूर्णांक dib0090_gain_control(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dib0090_state *state = fe->tuner_priv;
	क्रमागत frontend_tune_state *tune_state = &state->tune_state;
	पूर्णांक ret = 10;

	u16 wbd_val = 0;
	u8 apply_gain_immediatly = 1;
	s16 wbd_error = 0, adc_error = 0;

	अगर (*tune_state == CT_AGC_START) अणु
		state->agc_मुक्तze = 0;
		dib0090_ग_लिखो_reg(state, 0x04, 0x0);

#अगर_घोषित CONFIG_BAND_SBAND
		अगर (state->current_band == BAND_SBAND) अणु
			dib0090_set_rframp(state, rf_ramp_sband);
			dib0090_set_bbramp(state, bb_ramp_boost);
		पूर्ण अन्यथा
#पूर्ण_अगर
#अगर_घोषित CONFIG_BAND_VHF
		अगर (state->current_band == BAND_VHF && !state->identity.p1g) अणु
			dib0090_set_rframp(state, rf_ramp_pwm_vhf);
			dib0090_set_bbramp(state, bb_ramp_pwm_normal);
		पूर्ण अन्यथा
#पूर्ण_अगर
#अगर_घोषित CONFIG_BAND_CBAND
		अगर (state->current_band == BAND_CBAND && !state->identity.p1g) अणु
			dib0090_set_rframp(state, rf_ramp_pwm_cband);
			dib0090_set_bbramp(state, bb_ramp_pwm_normal);
		पूर्ण अन्यथा
#पूर्ण_अगर
		अगर ((state->current_band == BAND_CBAND || state->current_band == BAND_VHF) && state->identity.p1g) अणु
			dib0090_set_rframp(state, rf_ramp_pwm_cband_7090p);
			dib0090_set_bbramp(state, bb_ramp_pwm_normal_socs);
		पूर्ण अन्यथा अणु
			dib0090_set_rframp(state, rf_ramp_pwm_uhf);
			dib0090_set_bbramp(state, bb_ramp_pwm_normal);
		पूर्ण

		dib0090_ग_लिखो_reg(state, 0x32, 0);
		dib0090_ग_लिखो_reg(state, 0x39, 0);

		dib0090_wbd_target(state, state->current_rf);

		state->rf_gain_limit = state->rf_ramp[0] << WBD_ALPHA;
		state->current_gain = ((state->rf_ramp[0] + state->bb_ramp[0]) / 2) << GAIN_ALPHA;

		*tune_state = CT_AGC_STEP_0;
	पूर्ण अन्यथा अगर (!state->agc_मुक्तze) अणु
		s16 wbd = 0, i, cnt;

		पूर्णांक adc;
		wbd_val = dib0090_get_slow_adc_val(state);

		अगर (*tune_state == CT_AGC_STEP_0)
			cnt = 5;
		अन्यथा
			cnt = 1;

		क्रम (i = 0; i < cnt; i++) अणु
			wbd_val = dib0090_get_slow_adc_val(state);
			wbd += dib0090_wbd_to_db(state, wbd_val);
		पूर्ण
		wbd /= cnt;
		wbd_error = state->wbd_target - wbd;

		अगर (*tune_state == CT_AGC_STEP_0) अणु
			अगर (wbd_error < 0 && state->rf_gain_limit > 0 && !state->identity.p1g) अणु
#अगर_घोषित CONFIG_BAND_CBAND
				/* in हाल of CBAND tune reduce first the lt_gain2 beक्रमe adjusting the RF gain */
				u8 ltg2 = (state->rf_lt_def >> 10) & 0x7;
				अगर (state->current_band == BAND_CBAND && ltg2) अणु
					ltg2 >>= 1;
					state->rf_lt_def &= ltg2 << 10;	/* reduce in 3 steps from 7 to 0 */
				पूर्ण
#पूर्ण_अगर
			पूर्ण अन्यथा अणु
				state->agc_step = 0;
				*tune_state = CT_AGC_STEP_1;
			पूर्ण
		पूर्ण अन्यथा अणु
			/* calc the adc घातer */
			adc = state->config->get_adc_घातer(fe);
			adc = (adc * ((s32) 355774) + (((s32) 1) << 20)) >> 21;	/* included in [0:-700] */

			adc_error = (s16) (((s32) ADC_TARGET) - adc);
#अगर_घोषित CONFIG_STANDARD_DAB
			अगर (state->fe->dtv_property_cache.delivery_प्रणाली == STANDARD_DAB)
				adc_error -= 10;
#पूर्ण_अगर
#अगर_घोषित CONFIG_STANDARD_DVBT
			अगर (state->fe->dtv_property_cache.delivery_प्रणाली == STANDARD_DVBT &&
					(state->fe->dtv_property_cache.modulation == QAM_64 || state->fe->dtv_property_cache.modulation == QAM_16))
				adc_error += 60;
#पूर्ण_अगर
#अगर_घोषित CONFIG_SYS_ISDBT
			अगर ((state->fe->dtv_property_cache.delivery_प्रणाली == SYS_ISDBT) && (((state->fe->dtv_property_cache.layer[0].segment_count >
								0)
							&&
							((state->fe->dtv_property_cache.layer[0].modulation ==
							  QAM_64)
							 || (state->fe->dtv_property_cache.
								 layer[0].modulation == QAM_16)))
						||
						((state->fe->dtv_property_cache.layer[1].segment_count >
						  0)
						 &&
						 ((state->fe->dtv_property_cache.layer[1].modulation ==
						   QAM_64)
						  || (state->fe->dtv_property_cache.
							  layer[1].modulation == QAM_16)))
						||
						((state->fe->dtv_property_cache.layer[2].segment_count >
						  0)
						 &&
						 ((state->fe->dtv_property_cache.layer[2].modulation ==
						   QAM_64)
						  || (state->fe->dtv_property_cache.
							  layer[2].modulation == QAM_16)))
						)
				)
				adc_error += 60;
#पूर्ण_अगर

			अगर (*tune_state == CT_AGC_STEP_1) अणु	/* quickly go to the correct range of the ADC घातer */
				अगर (असल(adc_error) < 50 || state->agc_step++ > 5) अणु

#अगर_घोषित CONFIG_STANDARD_DAB
					अगर (state->fe->dtv_property_cache.delivery_प्रणाली == STANDARD_DAB) अणु
						dib0090_ग_लिखो_reg(state, 0x02, (1 << 15) | (15 << 11) | (31 << 6) | (63));	/* cap value = 63 : narrow BB filter : Fc = 1.8MHz */
						dib0090_ग_लिखो_reg(state, 0x04, 0x0);
					पूर्ण अन्यथा
#पूर्ण_अगर
					अणु
						dib0090_ग_लिखो_reg(state, 0x02, (1 << 15) | (3 << 11) | (6 << 6) | (32));
						dib0090_ग_लिखो_reg(state, 0x04, 0x01);	/*0 = 1KHz ; 1 = 150Hz ; 2 = 50Hz ; 3 = 50KHz ; 4 = servo fast */
					पूर्ण

					*tune_state = CT_AGC_STOP;
				पूर्ण
			पूर्ण अन्यथा अणु
				/* everything higher than or equal to CT_AGC_STOP means tracking */
				ret = 100;	/* 10ms पूर्णांकerval */
				apply_gain_immediatly = 0;
			पूर्ण
		पूर्ण
#अगर_घोषित DEBUG_AGC
		dprपूर्णांकk
			("tune state %d, ADC = %3ddB (ADC err %3d) WBD %3ddB (WBD err %3d, WBD val SADC: %4d), RFGainLimit (TOP): %3d, signal: %3ddBm",
			 (u32) *tune_state, (u32) adc, (u32) adc_error, (u32) wbd, (u32) wbd_error, (u32) wbd_val,
			 (u32) state->rf_gain_limit >> WBD_ALPHA, (s32) 200 + adc - (state->current_gain >> GAIN_ALPHA));
#पूर्ण_अगर
	पूर्ण

	/* apply gain */
	अगर (!state->agc_मुक्तze)
		dib0090_gain_apply(state, adc_error, wbd_error, apply_gain_immediatly);
	वापस ret;
पूर्ण

EXPORT_SYMBOL(dib0090_gain_control);

व्योम dib0090_get_current_gain(काष्ठा dvb_frontend *fe, u16 * rf, u16 * bb, u16 * rf_gain_limit, u16 * rflt)
अणु
	काष्ठा dib0090_state *state = fe->tuner_priv;
	अगर (rf)
		*rf = state->gain[0];
	अगर (bb)
		*bb = state->gain[1];
	अगर (rf_gain_limit)
		*rf_gain_limit = state->rf_gain_limit;
	अगर (rflt)
		*rflt = (state->rf_lt_def >> 10) & 0x7;
पूर्ण

EXPORT_SYMBOL(dib0090_get_current_gain);

u16 dib0090_get_wbd_target(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dib0090_state *state = fe->tuner_priv;
	u32 f_MHz = state->fe->dtv_property_cache.frequency / 1000000;
	s32 current_temp = state->temperature;
	s32 wbd_thot, wbd_tcold;
	स्थिर काष्ठा dib0090_wbd_slope *wbd = state->current_wbd_table;

	जबतक (f_MHz > wbd->max_freq)
		wbd++;

	dprपूर्णांकk("using wbd-table-entry with max freq %d\n", wbd->max_freq);

	अगर (current_temp < 0)
		current_temp = 0;
	अगर (current_temp > 128)
		current_temp = 128;

	state->wbdmux &= ~(7 << 13);
	अगर (wbd->wbd_gain != 0)
		state->wbdmux |= (wbd->wbd_gain << 13);
	अन्यथा
		state->wbdmux |= (4 << 13);

	dib0090_ग_लिखो_reg(state, 0x10, state->wbdmux);

	wbd_thot = wbd->offset_hot - (((u32) wbd->slope_hot * f_MHz) >> 6);
	wbd_tcold = wbd->offset_cold - (((u32) wbd->slope_cold * f_MHz) >> 6);

	wbd_tcold += ((wbd_thot - wbd_tcold) * current_temp) >> 7;

	state->wbd_target = dib0090_wbd_to_db(state, state->wbd_offset + wbd_tcold);
	dprपूर्णांकk("wbd-target: %d dB\n", (u32) state->wbd_target);
	dprपूर्णांकk("wbd offset applied is %d\n", wbd_tcold);

	वापस state->wbd_offset + wbd_tcold;
पूर्ण
EXPORT_SYMBOL(dib0090_get_wbd_target);

u16 dib0090_get_wbd_offset(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dib0090_state *state = fe->tuner_priv;
	वापस state->wbd_offset;
पूर्ण
EXPORT_SYMBOL(dib0090_get_wbd_offset);

पूर्णांक dib0090_set_चयन(काष्ठा dvb_frontend *fe, u8 sw1, u8 sw2, u8 sw3)
अणु
	काष्ठा dib0090_state *state = fe->tuner_priv;

	dib0090_ग_लिखो_reg(state, 0x0b, (dib0090_पढ़ो_reg(state, 0x0b) & 0xfff8)
			| ((sw3 & 1) << 2) | ((sw2 & 1) << 1) | (sw1 & 1));

	वापस 0;
पूर्ण
EXPORT_SYMBOL(dib0090_set_चयन);

पूर्णांक dib0090_set_vga(काष्ठा dvb_frontend *fe, u8 onoff)
अणु
	काष्ठा dib0090_state *state = fe->tuner_priv;

	dib0090_ग_लिखो_reg(state, 0x09, (dib0090_पढ़ो_reg(state, 0x09) & 0x7fff)
			| ((onoff & 1) << 15));
	वापस 0;
पूर्ण
EXPORT_SYMBOL(dib0090_set_vga);

पूर्णांक dib0090_update_rframp_7090(काष्ठा dvb_frontend *fe, u8 cfg_sensitivity)
अणु
	काष्ठा dib0090_state *state = fe->tuner_priv;

	अगर ((!state->identity.p1g) || (!state->identity.in_soc)
			|| ((state->identity.version != SOC_7090_P1G_21R1)
				&& (state->identity.version != SOC_7090_P1G_11R1))) अणु
		dprपूर्णांकk("%s() function can only be used for dib7090P\n", __func__);
		वापस -ENODEV;
	पूर्ण

	अगर (cfg_sensitivity)
		state->rf_ramp = rf_ramp_pwm_cband_7090e_sensitivity;
	अन्यथा
		state->rf_ramp = rf_ramp_pwm_cband_7090e_aci;
	dib0090_pwm_gain_reset(fe);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(dib0090_update_rframp_7090);

अटल स्थिर u16 dib0090_शेषs[] = अणु

	25, 0x01,
	0x0000,
	0x99a0,
	0x6008,
	0x0000,
	0x8bcb,
	0x0000,
	0x0405,
	0x0000,
	0x0000,
	0x0000,
	0xb802,
	0x0300,
	0x2d12,
	0xbac0,
	0x7c00,
	0xdbb9,
	0x0954,
	0x0743,
	0x8000,
	0x0001,
	0x0040,
	0x0100,
	0x0000,
	0xe910,
	0x149e,

	1, 0x1c,
	0xff2d,

	1, 0x39,
	0x0000,

	2, 0x1e,
	0x07FF,
	0x0007,

	1, 0x24,
	EN_UHF | EN_CRYSTAL,

	2, 0x3c,
	0x3ff,
	0x111,
	0
पूर्ण;

अटल स्थिर u16 dib0090_p1g_additionnal_शेषs[] = अणु
	1, 0x05,
	0xabcd,

	1, 0x11,
	0x00b4,

	1, 0x1c,
	0xfffd,

	1, 0x40,
	0x108,
	0
पूर्ण;

अटल व्योम dib0090_set_शेष_config(काष्ठा dib0090_state *state, स्थिर u16 * n)
अणु
	u16 l, r;

	l = pgm_पढ़ो_word(n++);
	जबतक (l) अणु
		r = pgm_पढ़ो_word(n++);
		करो अणु
			dib0090_ग_लिखो_reg(state, r, pgm_पढ़ो_word(n++));
			r++;
		पूर्ण जबतक (--l);
		l = pgm_पढ़ो_word(n++);
	पूर्ण
पूर्ण

#घोषणा CAP_VALUE_MIN (u8)  9
#घोषणा CAP_VALUE_MAX (u8) 40
#घोषणा HR_MIN	      (u8) 25
#घोषणा HR_MAX	      (u8) 40
#घोषणा POLY_MIN      (u8)  0
#घोषणा POLY_MAX      (u8)  8

अटल व्योम dib0090_set_EFUSE(काष्ठा dib0090_state *state)
अणु
	u8 c, h, n;
	u16 e2, e4;
	u16 cal;

	e2 = dib0090_पढ़ो_reg(state, 0x26);
	e4 = dib0090_पढ़ो_reg(state, 0x28);

	अगर ((state->identity.version == P1D_E_F) ||
			(state->identity.version == P1G) || (e2 == 0xffff)) अणु

		dib0090_ग_लिखो_reg(state, 0x22, 0x10);
		cal = (dib0090_पढ़ो_reg(state, 0x22) >> 6) & 0x3ff;

		अगर ((cal < 670) || (cal == 1023))
			cal = 850;
		n = 165 - ((cal * 10)>>6) ;
		e2 = e4 = (3<<12) | (34<<6) | (n);
	पूर्ण

	अगर (e2 != e4)
		e2 &= e4; /* Remove the redundancy  */

	अगर (e2 != 0xffff) अणु
		c = e2 & 0x3f;
		n = (e2 >> 12) & 0xf;
		h = (e2 >> 6) & 0x3f;

		अगर ((c >= CAP_VALUE_MAX) || (c <= CAP_VALUE_MIN))
			c = 32;
		अन्यथा
			c += 14;
		अगर ((h >= HR_MAX) || (h <= HR_MIN))
			h = 34;
		अगर ((n >= POLY_MAX) || (n <= POLY_MIN))
			n = 3;

		dib0090_ग_लिखो_reg(state, 0x13, (h << 10));
		e2 = (n << 11) | ((h >> 2)<<6) | c;
		dib0090_ग_लिखो_reg(state, 0x2, e2); /* Load the BB_2 */
	पूर्ण
पूर्ण

अटल पूर्णांक dib0090_reset(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dib0090_state *state = fe->tuner_priv;

	dib0090_reset_digital(fe, state->config);
	अगर (dib0090_identअगरy(fe) < 0)
		वापस -EIO;

#अगर_घोषित CONFIG_TUNER_DIB0090_P1B_SUPPORT
	अगर (!(state->identity.version & 0x1))	/* it is P1B - reset is alपढ़ोy करोne */
		वापस 0;
#पूर्ण_अगर

	अगर (!state->identity.in_soc) अणु
		अगर ((dib0090_पढ़ो_reg(state, 0x1a) >> 5) & 0x2)
			dib0090_ग_लिखो_reg(state, 0x1b, (EN_IQADC | EN_BB | EN_BIAS | EN_DIGCLK | EN_PLL | EN_CRYSTAL));
		अन्यथा
			dib0090_ग_लिखो_reg(state, 0x1b, (EN_DIGCLK | EN_PLL | EN_CRYSTAL));
	पूर्ण

	dib0090_set_शेष_config(state, dib0090_शेषs);

	अगर (state->identity.in_soc)
		dib0090_ग_लिखो_reg(state, 0x18, 0x2910);  /* अक्षरge pump current = 0 */

	अगर (state->identity.p1g)
		dib0090_set_शेष_config(state, dib0090_p1g_additionnal_शेषs);

	/* Update the efuse : Only available क्रम KROSUS > P1C  and SOC as well*/
	अगर (((state->identity.version & 0x1f) >= P1D_E_F) || (state->identity.in_soc))
		dib0090_set_EFUSE(state);

	/* Congigure in function of the crystal */
	अगर (state->config->क्रमce_crystal_mode != 0)
		dib0090_ग_लिखो_reg(state, 0x14,
				state->config->क्रमce_crystal_mode & 3);
	अन्यथा अगर (state->config->io.घड़ी_khz >= 24000)
		dib0090_ग_लिखो_reg(state, 0x14, 1);
	अन्यथा
		dib0090_ग_लिखो_reg(state, 0x14, 2);
	dprपूर्णांकk("Pll lock : %d\n", (dib0090_पढ़ो_reg(state, 0x1a) >> 11) & 0x1);

	state->calibrate = DC_CAL | WBD_CAL | TEMP_CAL;	/* enable iq-offset-calibration and wbd-calibration when tuning next समय */

	वापस 0;
पूर्ण

#घोषणा steps(u) (((u) > 15) ? ((u)-16) : (u))
#घोषणा INTERN_WAIT 10
अटल पूर्णांक dib0090_get_offset(काष्ठा dib0090_state *state, क्रमागत frontend_tune_state *tune_state)
अणु
	पूर्णांक ret = INTERN_WAIT * 10;

	चयन (*tune_state) अणु
	हाल CT_TUNER_STEP_2:
		/* Turns to positive */
		dib0090_ग_लिखो_reg(state, 0x1f, 0x7);
		*tune_state = CT_TUNER_STEP_3;
		अवरोध;

	हाल CT_TUNER_STEP_3:
		state->adc_dअगरf = dib0090_पढ़ो_reg(state, 0x1d);

		/* Turns to negative */
		dib0090_ग_लिखो_reg(state, 0x1f, 0x4);
		*tune_state = CT_TUNER_STEP_4;
		अवरोध;

	हाल CT_TUNER_STEP_4:
		state->adc_dअगरf -= dib0090_पढ़ो_reg(state, 0x1d);
		*tune_state = CT_TUNER_STEP_5;
		ret = 0;
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

काष्ठा dc_calibration अणु
	u8 addr;
	u8 offset;
	u8 pga:1;
	u16 bb1;
	u8 i:1;
पूर्ण;

अटल स्थिर काष्ठा dc_calibration dc_table[] = अणु
	/* Step1 BB gain1= 26 with boost 1, gain 2 = 0 */
	अणु0x06, 5, 1, (1 << 13) | (0 << 8) | (26 << 3), 1पूर्ण,
	अणु0x07, 11, 1, (1 << 13) | (0 << 8) | (26 << 3), 0पूर्ण,
	/* Step 2 BB gain 1 = 26 with boost = 1 & gain 2 = 29 */
	अणु0x06, 0, 0, (1 << 13) | (29 << 8) | (26 << 3), 1पूर्ण,
	अणु0x06, 10, 0, (1 << 13) | (29 << 8) | (26 << 3), 0पूर्ण,
	अणु0पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा dc_calibration dc_p1g_table[] = अणु
	/* Step1 BB gain1= 26 with boost 1, gain 2 = 0 */
	/* addr ; trim reg offset ; pga ; CTRL_BB1 value ; i or q */
	अणु0x06, 5, 1, (1 << 13) | (0 << 8) | (15 << 3), 1पूर्ण,
	अणु0x07, 11, 1, (1 << 13) | (0 << 8) | (15 << 3), 0पूर्ण,
	/* Step 2 BB gain 1 = 26 with boost = 1 & gain 2 = 29 */
	अणु0x06, 0, 0, (1 << 13) | (29 << 8) | (15 << 3), 1पूर्ण,
	अणु0x06, 10, 0, (1 << 13) | (29 << 8) | (15 << 3), 0पूर्ण,
	अणु0पूर्ण,
पूर्ण;

अटल व्योम dib0090_set_trim(काष्ठा dib0090_state *state)
अणु
	u16 *val;

	अगर (state->dc->addr == 0x07)
		val = &state->bb7;
	अन्यथा
		val = &state->bb6;

	*val &= ~(0x1f << state->dc->offset);
	*val |= state->step << state->dc->offset;

	dib0090_ग_लिखो_reg(state, state->dc->addr, *val);
पूर्ण

अटल पूर्णांक dib0090_dc_offset_calibration(काष्ठा dib0090_state *state, क्रमागत frontend_tune_state *tune_state)
अणु
	पूर्णांक ret = 0;
	u16 reg;

	चयन (*tune_state) अणु
	हाल CT_TUNER_START:
		dprपूर्णांकk("Start DC offset calibration");

		/* क्रमce vcm2 = 0.8V */
		state->bb6 = 0;
		state->bb7 = 0x040d;

		/* the LNA AND LO are off */
		reg = dib0090_पढ़ो_reg(state, 0x24) & 0x0ffb;	/* shutकरोwn lna and lo */
		dib0090_ग_लिखो_reg(state, 0x24, reg);

		state->wbdmux = dib0090_पढ़ो_reg(state, 0x10);
		dib0090_ग_लिखो_reg(state, 0x10, (state->wbdmux & ~(0xff << 3)) | (0x7 << 3) | 0x3);
		dib0090_ग_लिखो_reg(state, 0x23, dib0090_पढ़ो_reg(state, 0x23) & ~(1 << 14));

		state->dc = dc_table;

		अगर (state->identity.p1g)
			state->dc = dc_p1g_table;

		fallthrough;
	हाल CT_TUNER_STEP_0:
		dprपूर्णांकk("Start/continue DC calibration for %s path\n",
			(state->dc->i == 1) ? "I" : "Q");
		dib0090_ग_लिखो_reg(state, 0x01, state->dc->bb1);
		dib0090_ग_लिखो_reg(state, 0x07, state->bb7 | (state->dc->i << 7));

		state->step = 0;
		state->min_adc_dअगरf = 1023;
		*tune_state = CT_TUNER_STEP_1;
		ret = 50;
		अवरोध;

	हाल CT_TUNER_STEP_1:
		dib0090_set_trim(state);
		*tune_state = CT_TUNER_STEP_2;
		अवरोध;

	हाल CT_TUNER_STEP_2:
	हाल CT_TUNER_STEP_3:
	हाल CT_TUNER_STEP_4:
		ret = dib0090_get_offset(state, tune_state);
		अवरोध;

	हाल CT_TUNER_STEP_5:	/* found an offset */
		dprपूर्णांकk("adc_diff = %d, current step= %d\n", (u32) state->adc_dअगरf, state->step);
		अगर (state->step == 0 && state->adc_dअगरf < 0) अणु
			state->min_adc_dअगरf = -1023;
			dprपूर्णांकk("Change of sign of the minimum adc diff\n");
		पूर्ण

		dprपूर्णांकk("adc_diff = %d, min_adc_diff = %d current_step = %d\n", state->adc_dअगरf, state->min_adc_dअगरf, state->step);

		/* first turn क्रम this frequency */
		अगर (state->step == 0) अणु
			अगर (state->dc->pga && state->adc_dअगरf < 0)
				state->step = 0x10;
			अगर (state->dc->pga == 0 && state->adc_dअगरf > 0)
				state->step = 0x10;
		पूर्ण

		/* Look क्रम a change of Sign in the Adc_dअगरf.min_adc_dअगरf is used to STORE the setp N-1 */
		अगर ((state->adc_dअगरf & 0x8000) == (state->min_adc_dअगरf & 0x8000) && steps(state->step) < 15) अणु
			/* stop search when the delta the sign is changing and Steps =15 and Step=0 is क्रमce क्रम continuance */
			state->step++;
			state->min_adc_dअगरf = state->adc_dअगरf;
			*tune_state = CT_TUNER_STEP_1;
		पूर्ण अन्यथा अणु
			/* the minimum was what we have seen in the step beक्रमe */
			अगर (असल(state->adc_dअगरf) > असल(state->min_adc_dअगरf)) अणु
				dprपूर्णांकk("Since adc_diff N = %d  > adc_diff step N-1 = %d, Come back one step\n", state->adc_dअगरf, state->min_adc_dअगरf);
				state->step--;
			पूर्ण

			dib0090_set_trim(state);
			dprपूर्णांकk("BB Offset Cal, BBreg=%u,Offset=%d,Value Set=%d\n",
				state->dc->addr, state->adc_dअगरf, state->step);

			state->dc++;
			अगर (state->dc->addr == 0)	/* करोne */
				*tune_state = CT_TUNER_STEP_6;
			अन्यथा
				*tune_state = CT_TUNER_STEP_0;

		पूर्ण
		अवरोध;

	हाल CT_TUNER_STEP_6:
		dib0090_ग_लिखो_reg(state, 0x07, state->bb7 & ~0x0008);
		dib0090_ग_लिखो_reg(state, 0x1f, 0x7);
		*tune_state = CT_TUNER_START;	/* reset करोne -> real tuning can now begin */
		state->calibrate &= ~DC_CAL;
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक dib0090_wbd_calibration(काष्ठा dib0090_state *state, क्रमागत frontend_tune_state *tune_state)
अणु
	u8 wbd_gain;
	स्थिर काष्ठा dib0090_wbd_slope *wbd = state->current_wbd_table;

	चयन (*tune_state) अणु
	हाल CT_TUNER_START:
		जबतक (state->current_rf / 1000 > wbd->max_freq)
			wbd++;
		अगर (wbd->wbd_gain != 0)
			wbd_gain = wbd->wbd_gain;
		अन्यथा अणु
			wbd_gain = 4;
#अगर defined(CONFIG_BAND_LBAND) || defined(CONFIG_BAND_SBAND)
			अगर ((state->current_band == BAND_LBAND) || (state->current_band == BAND_SBAND))
				wbd_gain = 2;
#पूर्ण_अगर
		पूर्ण

		अगर (wbd_gain == state->wbd_calibration_gain) अणु	/* the WBD calibration has alपढ़ोy been करोne */
			*tune_state = CT_TUNER_START;
			state->calibrate &= ~WBD_CAL;
			वापस 0;
		पूर्ण

		dib0090_ग_लिखो_reg(state, 0x10, 0x1b81 | (1 << 10) | (wbd_gain << 13) | (1 << 3));

		dib0090_ग_लिखो_reg(state, 0x24, ((EN_UHF & 0x0fff) | (1 << 1)));
		*tune_state = CT_TUNER_STEP_0;
		state->wbd_calibration_gain = wbd_gain;
		वापस 90;	/* रुको क्रम the WBDMUX to चयन and क्रम the ADC to sample */

	हाल CT_TUNER_STEP_0:
		state->wbd_offset = dib0090_get_slow_adc_val(state);
		dprपूर्णांकk("WBD calibration offset = %d\n", state->wbd_offset);
		*tune_state = CT_TUNER_START;	/* reset करोne -> real tuning can now begin */
		state->calibrate &= ~WBD_CAL;
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम dib0090_set_bandwidth(काष्ठा dib0090_state *state)
अणु
	u16 पंचांगp;

	अगर (state->fe->dtv_property_cache.bandwidth_hz / 1000 <= 5000)
		पंचांगp = (3 << 14);
	अन्यथा अगर (state->fe->dtv_property_cache.bandwidth_hz / 1000 <= 6000)
		पंचांगp = (2 << 14);
	अन्यथा अगर (state->fe->dtv_property_cache.bandwidth_hz / 1000 <= 7000)
		पंचांगp = (1 << 14);
	अन्यथा
		पंचांगp = (0 << 14);

	state->bb_1_def &= 0x3fff;
	state->bb_1_def |= पंचांगp;

	dib0090_ग_लिखो_reg(state, 0x01, state->bb_1_def);	/* be sure that we have the right bb-filter */

	dib0090_ग_लिखो_reg(state, 0x03, 0x6008);	/* = 0x6008 : vcm3_trim = 1 ; filter2_gm1_trim = 8 ; filter2_cutoff_freq = 0 */
	dib0090_ग_लिखो_reg(state, 0x04, 0x1);	/* 0 = 1KHz ; 1 = 50Hz ; 2 = 150Hz ; 3 = 50KHz ; 4 = servo fast */
	अगर (state->identity.in_soc) अणु
		dib0090_ग_लिखो_reg(state, 0x05, 0x9bcf); /* attenuator_ibias_tri = 2 ; input_stage_ibias_tr = 1 ; nc = 11 ; ext_gm_trim = 1 ; obuf_ibias_trim = 4 ; filter13_gm2_ibias_t = 15 */
	पूर्ण अन्यथा अणु
		dib0090_ग_लिखो_reg(state, 0x02, (5 << 11) | (8 << 6) | (22 & 0x3f));	/* 22 = cap_value */
		dib0090_ग_लिखो_reg(state, 0x05, 0xabcd);	/* = 0xabcd : attenuator_ibias_tri = 2 ; input_stage_ibias_tr = 2 ; nc = 11 ; ext_gm_trim = 1 ; obuf_ibias_trim = 4 ; filter13_gm2_ibias_t = 13 */
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा dib0090_pll dib0090_pll_table[] = अणु
#अगर_घोषित CONFIG_BAND_CBAND
	अणु56000, 0, 9, 48, 6पूर्ण,
	अणु70000, 1, 9, 48, 6पूर्ण,
	अणु87000, 0, 8, 32, 4पूर्ण,
	अणु105000, 1, 8, 32, 4पूर्ण,
	अणु115000, 0, 7, 24, 6पूर्ण,
	अणु140000, 1, 7, 24, 6पूर्ण,
	अणु170000, 0, 6, 16, 4पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_BAND_VHF
	अणु200000, 1, 6, 16, 4पूर्ण,
	अणु230000, 0, 5, 12, 6पूर्ण,
	अणु280000, 1, 5, 12, 6पूर्ण,
	अणु340000, 0, 4, 8, 4पूर्ण,
	अणु380000, 1, 4, 8, 4पूर्ण,
	अणु450000, 0, 3, 6, 6पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_BAND_UHF
	अणु580000, 1, 3, 6, 6पूर्ण,
	अणु700000, 0, 2, 4, 4पूर्ण,
	अणु860000, 1, 2, 4, 4पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_BAND_LBAND
	अणु1800000, 1, 0, 2, 4पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_BAND_SBAND
	अणु2900000, 0, 14, 1, 4पूर्ण,
#पूर्ण_अगर
पूर्ण;

अटल स्थिर काष्ठा dib0090_tuning dib0090_tuning_table_fm_vhf_on_cband[] = अणु

#अगर_घोषित CONFIG_BAND_CBAND
	अणु184000, 4, 1, 15, 0x280, 0x2912, 0xb94e, EN_CABपूर्ण,
	अणु227000, 4, 3, 15, 0x280, 0x2912, 0xb94e, EN_CABपूर्ण,
	अणु380000, 4, 7, 15, 0x280, 0x2912, 0xb94e, EN_CABपूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_BAND_UHF
	अणु520000, 2, 0, 15, 0x300, 0x1d12, 0xb9ce, EN_UHFपूर्ण,
	अणु550000, 2, 2, 15, 0x300, 0x1d12, 0xb9ce, EN_UHFपूर्ण,
	अणु650000, 2, 3, 15, 0x300, 0x1d12, 0xb9ce, EN_UHFपूर्ण,
	अणु750000, 2, 5, 15, 0x300, 0x1d12, 0xb9ce, EN_UHFपूर्ण,
	अणु850000, 2, 6, 15, 0x300, 0x1d12, 0xb9ce, EN_UHFपूर्ण,
	अणु900000, 2, 7, 15, 0x300, 0x1d12, 0xb9ce, EN_UHFपूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_BAND_LBAND
	अणु1500000, 4, 0, 20, 0x300, 0x1912, 0x82c9, EN_LBDपूर्ण,
	अणु1600000, 4, 1, 20, 0x300, 0x1912, 0x82c9, EN_LBDपूर्ण,
	अणु1800000, 4, 3, 20, 0x300, 0x1912, 0x82c9, EN_LBDपूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_BAND_SBAND
	अणु2300000, 1, 4, 20, 0x300, 0x2d2A, 0x82c7, EN_SBDपूर्ण,
	अणु2900000, 1, 7, 20, 0x280, 0x2deb, 0x8347, EN_SBDपूर्ण,
#पूर्ण_अगर
पूर्ण;

अटल स्थिर काष्ठा dib0090_tuning dib0090_tuning_table[] = अणु

#अगर_घोषित CONFIG_BAND_CBAND
	अणु170000, 4, 1, 15, 0x280, 0x2912, 0xb94e, EN_CABपूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_BAND_VHF
	अणु184000, 1, 1, 15, 0x300, 0x4d12, 0xb94e, EN_VHFपूर्ण,
	अणु227000, 1, 3, 15, 0x300, 0x4d12, 0xb94e, EN_VHFपूर्ण,
	अणु380000, 1, 7, 15, 0x300, 0x4d12, 0xb94e, EN_VHFपूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_BAND_UHF
	अणु520000, 2, 0, 15, 0x300, 0x1d12, 0xb9ce, EN_UHFपूर्ण,
	अणु550000, 2, 2, 15, 0x300, 0x1d12, 0xb9ce, EN_UHFपूर्ण,
	अणु650000, 2, 3, 15, 0x300, 0x1d12, 0xb9ce, EN_UHFपूर्ण,
	अणु750000, 2, 5, 15, 0x300, 0x1d12, 0xb9ce, EN_UHFपूर्ण,
	अणु850000, 2, 6, 15, 0x300, 0x1d12, 0xb9ce, EN_UHFपूर्ण,
	अणु900000, 2, 7, 15, 0x300, 0x1d12, 0xb9ce, EN_UHFपूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_BAND_LBAND
	अणु1500000, 4, 0, 20, 0x300, 0x1912, 0x82c9, EN_LBDपूर्ण,
	अणु1600000, 4, 1, 20, 0x300, 0x1912, 0x82c9, EN_LBDपूर्ण,
	अणु1800000, 4, 3, 20, 0x300, 0x1912, 0x82c9, EN_LBDपूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_BAND_SBAND
	अणु2300000, 1, 4, 20, 0x300, 0x2d2A, 0x82c7, EN_SBDपूर्ण,
	अणु2900000, 1, 7, 20, 0x280, 0x2deb, 0x8347, EN_SBDपूर्ण,
#पूर्ण_अगर
पूर्ण;

अटल स्थिर काष्ठा dib0090_tuning dib0090_p1g_tuning_table[] = अणु
#अगर_घोषित CONFIG_BAND_CBAND
	अणु170000, 4, 1, 0x820f, 0x300, 0x2d22, 0x82cb, EN_CABपूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_BAND_VHF
	अणु184000, 1, 1, 15, 0x300, 0x4d12, 0xb94e, EN_VHFपूर्ण,
	अणु227000, 1, 3, 15, 0x300, 0x4d12, 0xb94e, EN_VHFपूर्ण,
	अणु380000, 1, 7, 15, 0x300, 0x4d12, 0xb94e, EN_VHFपूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_BAND_UHF
	अणु510000, 2, 0, 15, 0x300, 0x1d12, 0xb9ce, EN_UHFपूर्ण,
	अणु540000, 2, 1, 15, 0x300, 0x1d12, 0xb9ce, EN_UHFपूर्ण,
	अणु600000, 2, 3, 15, 0x300, 0x1d12, 0xb9ce, EN_UHFपूर्ण,
	अणु630000, 2, 4, 15, 0x300, 0x1d12, 0xb9ce, EN_UHFपूर्ण,
	अणु680000, 2, 5, 15, 0x300, 0x1d12, 0xb9ce, EN_UHFपूर्ण,
	अणु720000, 2, 6, 15, 0x300, 0x1d12, 0xb9ce, EN_UHFपूर्ण,
	अणु900000, 2, 7, 15, 0x300, 0x1d12, 0xb9ce, EN_UHFपूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_BAND_LBAND
	अणु1500000, 4, 0, 20, 0x300, 0x1912, 0x82c9, EN_LBDपूर्ण,
	अणु1600000, 4, 1, 20, 0x300, 0x1912, 0x82c9, EN_LBDपूर्ण,
	अणु1800000, 4, 3, 20, 0x300, 0x1912, 0x82c9, EN_LBDपूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_BAND_SBAND
	अणु2300000, 1, 4, 20, 0x300, 0x2d2A, 0x82c7, EN_SBDपूर्ण,
	अणु2900000, 1, 7, 20, 0x280, 0x2deb, 0x8347, EN_SBDपूर्ण,
#पूर्ण_अगर
पूर्ण;

अटल स्थिर काष्ठा dib0090_pll dib0090_p1g_pll_table[] = अणु
#अगर_घोषित CONFIG_BAND_CBAND
	अणु57000, 0, 11, 48, 6पूर्ण,
	अणु70000, 1, 11, 48, 6पूर्ण,
	अणु86000, 0, 10, 32, 4पूर्ण,
	अणु105000, 1, 10, 32, 4पूर्ण,
	अणु115000, 0, 9, 24, 6पूर्ण,
	अणु140000, 1, 9, 24, 6पूर्ण,
	अणु170000, 0, 8, 16, 4पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_BAND_VHF
	अणु200000, 1, 8, 16, 4पूर्ण,
	अणु230000, 0, 7, 12, 6पूर्ण,
	अणु280000, 1, 7, 12, 6पूर्ण,
	अणु340000, 0, 6, 8, 4पूर्ण,
	अणु380000, 1, 6, 8, 4पूर्ण,
	अणु455000, 0, 5, 6, 6पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_BAND_UHF
	अणु580000, 1, 5, 6, 6पूर्ण,
	अणु680000, 0, 4, 4, 4पूर्ण,
	अणु860000, 1, 4, 4, 4पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_BAND_LBAND
	अणु1800000, 1, 2, 2, 4पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_BAND_SBAND
	अणु2900000, 0, 1, 1, 6पूर्ण,
#पूर्ण_अगर
पूर्ण;

अटल स्थिर काष्ठा dib0090_tuning dib0090_p1g_tuning_table_fm_vhf_on_cband[] = अणु
#अगर_घोषित CONFIG_BAND_CBAND
	अणु184000, 4, 3, 0x4187, 0x2c0, 0x2d22, 0x81cb, EN_CABपूर्ण,
	अणु227000, 4, 3, 0x4187, 0x2c0, 0x2d22, 0x81cb, EN_CABपूर्ण,
	अणु380000, 4, 3, 0x4187, 0x2c0, 0x2d22, 0x81cb, EN_CABपूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_BAND_UHF
	अणु520000, 2, 0, 15, 0x300, 0x1d12, 0xb9ce, EN_UHFपूर्ण,
	अणु550000, 2, 2, 15, 0x300, 0x1d12, 0xb9ce, EN_UHFपूर्ण,
	अणु650000, 2, 3, 15, 0x300, 0x1d12, 0xb9ce, EN_UHFपूर्ण,
	अणु750000, 2, 5, 15, 0x300, 0x1d12, 0xb9ce, EN_UHFपूर्ण,
	अणु850000, 2, 6, 15, 0x300, 0x1d12, 0xb9ce, EN_UHFपूर्ण,
	अणु900000, 2, 7, 15, 0x300, 0x1d12, 0xb9ce, EN_UHFपूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_BAND_LBAND
	अणु1500000, 4, 0, 20, 0x300, 0x1912, 0x82c9, EN_LBDपूर्ण,
	अणु1600000, 4, 1, 20, 0x300, 0x1912, 0x82c9, EN_LBDपूर्ण,
	अणु1800000, 4, 3, 20, 0x300, 0x1912, 0x82c9, EN_LBDपूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_BAND_SBAND
	अणु2300000, 1, 4, 20, 0x300, 0x2d2A, 0x82c7, EN_SBDपूर्ण,
	अणु2900000, 1, 7, 20, 0x280, 0x2deb, 0x8347, EN_SBDपूर्ण,
#पूर्ण_अगर
पूर्ण;

अटल स्थिर काष्ठा dib0090_tuning dib0090_tuning_table_cband_7090[] = अणु
#अगर_घोषित CONFIG_BAND_CBAND
	अणु300000, 4, 3, 0x018F, 0x2c0, 0x2d22, 0xb9ce, EN_CABपूर्ण,
	अणु380000, 4, 10, 0x018F, 0x2c0, 0x2d22, 0xb9ce, EN_CABपूर्ण,
	अणु570000, 4, 10, 0x8190, 0x2c0, 0x2d22, 0xb9ce, EN_CABपूर्ण,
	अणु858000, 4, 5, 0x8190, 0x2c0, 0x2d22, 0xb9ce, EN_CABपूर्ण,
#पूर्ण_अगर
पूर्ण;

अटल स्थिर काष्ठा dib0090_tuning dib0090_tuning_table_cband_7090e_sensitivity[] = अणु
#अगर_घोषित CONFIG_BAND_CBAND
	अणु 300000,  0 ,  3,  0x8105, 0x2c0, 0x2d12, 0xb84e, EN_CAB पूर्ण,
	अणु 380000,  0 ,  10, 0x810F, 0x2c0, 0x2d12, 0xb84e, EN_CAB पूर्ण,
	अणु 600000,  0 ,  10, 0x815E, 0x280, 0x2d12, 0xb84e, EN_CAB पूर्ण,
	अणु 660000,  0 ,  5,  0x85E3, 0x280, 0x2d12, 0xb84e, EN_CAB पूर्ण,
	अणु 720000,  0 ,  5,  0x852E, 0x280, 0x2d12, 0xb84e, EN_CAB पूर्ण,
	अणु 860000,  0 ,  4,  0x85E5, 0x280, 0x2d12, 0xb84e, EN_CAB पूर्ण,
#पूर्ण_अगर
पूर्ण;

पूर्णांक dib0090_update_tuning_table_7090(काष्ठा dvb_frontend *fe,
		u8 cfg_sensitivity)
अणु
	काष्ठा dib0090_state *state = fe->tuner_priv;
	स्थिर काष्ठा dib0090_tuning *tune =
		dib0090_tuning_table_cband_7090e_sensitivity;
	अटल स्थिर काष्ठा dib0090_tuning dib0090_tuning_table_cband_7090e_aci[] = अणु
		अणु 300000,  0 ,  3,  0x8165, 0x2c0, 0x2d12, 0xb84e, EN_CAB पूर्ण,
		अणु 650000,  0 ,  4,  0x815B, 0x280, 0x2d12, 0xb84e, EN_CAB पूर्ण,
		अणु 860000,  0 ,  5,  0x84EF, 0x280, 0x2d12, 0xb84e, EN_CAB पूर्ण,
	पूर्ण;

	अगर ((!state->identity.p1g) || (!state->identity.in_soc)
			|| ((state->identity.version != SOC_7090_P1G_21R1)
				&& (state->identity.version != SOC_7090_P1G_11R1))) अणु
		dprपूर्णांकk("%s() function can only be used for dib7090\n", __func__);
		वापस -ENODEV;
	पूर्ण

	अगर (cfg_sensitivity)
		tune = dib0090_tuning_table_cband_7090e_sensitivity;
	अन्यथा
		tune = dib0090_tuning_table_cband_7090e_aci;

	जबतक (state->rf_request > tune->max_freq)
		tune++;

	dib0090_ग_लिखो_reg(state, 0x09, (dib0090_पढ़ो_reg(state, 0x09) & 0x8000)
			| (tune->lna_bias & 0x7fff));
	dib0090_ग_लिखो_reg(state, 0x0b, (dib0090_पढ़ो_reg(state, 0x0b) & 0xf83f)
			| ((tune->lna_tune << 6) & 0x07c0));
	वापस 0;
पूर्ण
EXPORT_SYMBOL(dib0090_update_tuning_table_7090);

अटल पूर्णांक dib0090_captrim_search(काष्ठा dib0090_state *state, क्रमागत frontend_tune_state *tune_state)
अणु
	पूर्णांक ret = 0;
	u16 lo4 = 0xe900;

	s16 adc_target;
	u16 adc;
	s8 step_sign;
	u8 क्रमce_soft_search = 0;

	अगर (state->identity.version == SOC_8090_P1G_11R1 || state->identity.version == SOC_8090_P1G_21R1)
		क्रमce_soft_search = 1;

	अगर (*tune_state == CT_TUNER_START) अणु
		dprपूर्णांकk("Start Captrim search : %s\n",
			(क्रमce_soft_search == 1) ? "FORCE SOFT SEARCH" : "AUTO");
		dib0090_ग_लिखो_reg(state, 0x10, 0x2B1);
		dib0090_ग_लिखो_reg(state, 0x1e, 0x0032);

		अगर (!state->tuner_is_tuned) अणु
			/* prepare a complete captrim */
			अगर (!state->identity.p1g || क्रमce_soft_search)
				state->step = state->captrim = state->fcaptrim = 64;

			state->current_rf = state->rf_request;
		पूर्ण अन्यथा अणु	/* we are alपढ़ोy tuned to this frequency - the configuration is correct  */
			अगर (!state->identity.p1g || क्रमce_soft_search) अणु
				/* करो a minimal captrim even अगर the frequency has not changed */
				state->step = 4;
				state->captrim = state->fcaptrim = dib0090_पढ़ो_reg(state, 0x18) & 0x7f;
			पूर्ण
		पूर्ण
		state->adc_dअगरf = 3000;
		*tune_state = CT_TUNER_STEP_0;

	पूर्ण अन्यथा अगर (*tune_state == CT_TUNER_STEP_0) अणु
		अगर (state->identity.p1g && !क्रमce_soft_search) अणु
			u8 ratio = 31;

			dib0090_ग_लिखो_reg(state, 0x40, (3 << 7) | (ratio << 2) | (1 << 1) | 1);
			dib0090_पढ़ो_reg(state, 0x40);
			ret = 50;
		पूर्ण अन्यथा अणु
			state->step /= 2;
			dib0090_ग_लिखो_reg(state, 0x18, lo4 | state->captrim);

			अगर (state->identity.in_soc)
				ret = 25;
		पूर्ण
		*tune_state = CT_TUNER_STEP_1;

	पूर्ण अन्यथा अगर (*tune_state == CT_TUNER_STEP_1) अणु
		अगर (state->identity.p1g && !क्रमce_soft_search) अणु
			dib0090_ग_लिखो_reg(state, 0x40, 0x18c | (0 << 1) | 0);
			dib0090_पढ़ो_reg(state, 0x40);

			state->fcaptrim = dib0090_पढ़ो_reg(state, 0x18) & 0x7F;
			dprपूर्णांकk("***Final Captrim= 0x%x\n", state->fcaptrim);
			*tune_state = CT_TUNER_STEP_3;

		पूर्ण अन्यथा अणु
			/* MERGE क्रम all krosus beक्रमe P1G */
			adc = dib0090_get_slow_adc_val(state);
			dprपूर्णांकk("CAPTRIM=%d; ADC = %d (ADC) & %dmV\n", (u32) state->captrim, (u32) adc, (u32) (adc) * (u32) 1800 / (u32) 1024);

			अगर (state->rest == 0 || state->identity.in_soc) अणु	/* Just क्रम 8090P SOCS where स्वतः captrim HW bug : TO CHECK IN ACI क्रम SOCS !!! अगर 400 क्रम 8090p SOC => tune issue !!! */
				adc_target = 200;
			पूर्ण अन्यथा
				adc_target = 400;

			अगर (adc >= adc_target) अणु
				adc -= adc_target;
				step_sign = -1;
			पूर्ण अन्यथा अणु
				adc = adc_target - adc;
				step_sign = 1;
			पूर्ण

			अगर (adc < state->adc_dअगरf) अणु
				dprपूर्णांकk("CAPTRIM=%d is closer to target (%d/%d)\n", (u32) state->captrim, (u32) adc, (u32) state->adc_dअगरf);
				state->adc_dअगरf = adc;
				state->fcaptrim = state->captrim;
			पूर्ण

			state->captrim += step_sign * state->step;
			अगर (state->step >= 1)
				*tune_state = CT_TUNER_STEP_0;
			अन्यथा
				*tune_state = CT_TUNER_STEP_2;

			ret = 25;
		पूर्ण
	पूर्ण अन्यथा अगर (*tune_state == CT_TUNER_STEP_2) अणु	/* this step is only used by krosus < P1G */
		/*ग_लिखो the final cptrim config */
		dib0090_ग_लिखो_reg(state, 0x18, lo4 | state->fcaptrim);

		*tune_state = CT_TUNER_STEP_3;

	पूर्ण अन्यथा अगर (*tune_state == CT_TUNER_STEP_3) अणु
		state->calibrate &= ~CAPTRIM_CAL;
		*tune_state = CT_TUNER_STEP_0;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक dib0090_get_temperature(काष्ठा dib0090_state *state, क्रमागत frontend_tune_state *tune_state)
अणु
	पूर्णांक ret = 15;
	s16 val;

	चयन (*tune_state) अणु
	हाल CT_TUNER_START:
		state->wbdmux = dib0090_पढ़ो_reg(state, 0x10);
		dib0090_ग_लिखो_reg(state, 0x10, (state->wbdmux & ~(0xff << 3)) | (0x8 << 3));

		state->bias = dib0090_पढ़ो_reg(state, 0x13);
		dib0090_ग_लिखो_reg(state, 0x13, state->bias | (0x3 << 8));

		*tune_state = CT_TUNER_STEP_0;
		/* रुको क्रम the WBDMUX to चयन and क्रम the ADC to sample */
		अवरोध;

	हाल CT_TUNER_STEP_0:
		state->adc_dअगरf = dib0090_get_slow_adc_val(state);
		dib0090_ग_लिखो_reg(state, 0x13, (state->bias & ~(0x3 << 8)) | (0x2 << 8));
		*tune_state = CT_TUNER_STEP_1;
		अवरोध;

	हाल CT_TUNER_STEP_1:
		val = dib0090_get_slow_adc_val(state);
		state->temperature = ((s16) ((val - state->adc_dअगरf) * 180) >> 8) + 55;

		dprपूर्णांकk("temperature: %d C\n", state->temperature - 30);

		*tune_state = CT_TUNER_STEP_2;
		अवरोध;

	हाल CT_TUNER_STEP_2:
		dib0090_ग_लिखो_reg(state, 0x13, state->bias);
		dib0090_ग_लिखो_reg(state, 0x10, state->wbdmux);	/* ग_लिखो back original WBDMUX */

		*tune_state = CT_TUNER_START;
		state->calibrate &= ~TEMP_CAL;
		अगर (state->config->analog_output == 0)
			dib0090_ग_लिखो_reg(state, 0x23, dib0090_पढ़ो_reg(state, 0x23) | (1 << 14));

		अवरोध;

	शेष:
		ret = 0;
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

#घोषणा WBD     0x781		/* 1 1 1 1 0000 0 0 1 */
अटल पूर्णांक dib0090_tune(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dib0090_state *state = fe->tuner_priv;
	स्थिर काष्ठा dib0090_tuning *tune = state->current_tune_table_index;
	स्थिर काष्ठा dib0090_pll *pll = state->current_pll_table_index;
	क्रमागत frontend_tune_state *tune_state = &state->tune_state;

	u16 lo5, lo6, Den, पंचांगp;
	u32 FBDiv, Rest, FREF, VCOF_kHz = 0;
	पूर्णांक ret = 10;		/* 1ms is the शेष delay most of the समय */
	u8 c, i;

	/************************* VCO ***************************/
	/* Default values क्रम FG                                 */
	/* from these are needed :                               */
	/* Cp,HFभाग,VCOband,SD,Num,Den,FB and REFDiv             */

	/* in any हाल we first need to करो a calibration अगर needed */
	अगर (*tune_state == CT_TUNER_START) अणु
		/* deactivate DataTX beक्रमe some calibrations */
		अगर (state->calibrate & (DC_CAL | TEMP_CAL | WBD_CAL))
			dib0090_ग_लिखो_reg(state, 0x23, dib0090_पढ़ो_reg(state, 0x23) & ~(1 << 14));
		अन्यथा
			/* Activate DataTX in हाल a calibration has been करोne beक्रमe */
			अगर (state->config->analog_output == 0)
				dib0090_ग_लिखो_reg(state, 0x23, dib0090_पढ़ो_reg(state, 0x23) | (1 << 14));
	पूर्ण

	अगर (state->calibrate & DC_CAL)
		वापस dib0090_dc_offset_calibration(state, tune_state);
	अन्यथा अगर (state->calibrate & WBD_CAL) अणु
		अगर (state->current_rf == 0)
			state->current_rf = state->fe->dtv_property_cache.frequency / 1000;
		वापस dib0090_wbd_calibration(state, tune_state);
	पूर्ण अन्यथा अगर (state->calibrate & TEMP_CAL)
		वापस dib0090_get_temperature(state, tune_state);
	अन्यथा अगर (state->calibrate & CAPTRIM_CAL)
		वापस dib0090_captrim_search(state, tune_state);

	अगर (*tune_state == CT_TUNER_START) अणु
		/* अगर soc and AGC pwm control, disengage mux to be able to R/W access to 0x01 रेजिस्टर to set the right filter (cutoff_freq_select) during the tune sequence, otherwise, SOC SERPAR error when accessing to 0x01 */
		अगर (state->config->use_pwm_agc && state->identity.in_soc) अणु
			पंचांगp = dib0090_पढ़ो_reg(state, 0x39);
			अगर ((पंचांगp >> 10) & 0x1)
				dib0090_ग_लिखो_reg(state, 0x39, पंचांगp & ~(1 << 10));
		पूर्ण

		state->current_band = (u8) BAND_OF_FREQUENCY(state->fe->dtv_property_cache.frequency / 1000);
		state->rf_request =
			state->fe->dtv_property_cache.frequency / 1000 + (state->current_band ==
					BAND_UHF ? state->config->freq_offset_khz_uhf : state->config->
					freq_offset_khz_vhf);

		/* in ISDB-T 1seg we shअगरt tuning frequency */
		अगर ((state->fe->dtv_property_cache.delivery_प्रणाली == SYS_ISDBT && state->fe->dtv_property_cache.isdbt_sb_mode == 1
					&& state->fe->dtv_property_cache.isdbt_partial_reception == 0)) अणु
			स्थिर काष्ठा dib0090_low_अगर_offset_table *LUT_offset = state->config->low_अगर;
			u8 found_offset = 0;
			u32 margin_khz = 100;

			अगर (LUT_offset != शून्य) अणु
				जबतक (LUT_offset->RF_freq != 0xffff) अणु
					अगर (((state->rf_request > (LUT_offset->RF_freq - margin_khz))
								&& (state->rf_request < (LUT_offset->RF_freq + margin_khz)))
							&& LUT_offset->std == state->fe->dtv_property_cache.delivery_प्रणाली) अणु
						state->rf_request += LUT_offset->offset_khz;
						found_offset = 1;
						अवरोध;
					पूर्ण
					LUT_offset++;
				पूर्ण
			पूर्ण

			अगर (found_offset == 0)
				state->rf_request += 400;
		पूर्ण
		अगर (state->current_rf != state->rf_request || (state->current_standard != state->fe->dtv_property_cache.delivery_प्रणाली)) अणु
			state->tuner_is_tuned = 0;
			state->current_rf = 0;
			state->current_standard = 0;

			tune = dib0090_tuning_table;
			अगर (state->identity.p1g)
				tune = dib0090_p1g_tuning_table;

			पंचांगp = (state->identity.version >> 5) & 0x7;

			अगर (state->identity.in_soc) अणु
				अगर (state->config->क्रमce_cband_input) अणु	/* Use the CBAND input क्रम all band */
					अगर (state->current_band & BAND_CBAND || state->current_band & BAND_FM || state->current_band & BAND_VHF
							|| state->current_band & BAND_UHF) अणु
						state->current_band = BAND_CBAND;
						अगर (state->config->is_dib7090e)
							tune = dib0090_tuning_table_cband_7090e_sensitivity;
						अन्यथा
							tune = dib0090_tuning_table_cband_7090;
					पूर्ण
				पूर्ण अन्यथा अणु	/* Use the CBAND input क्रम all band under UHF */
					अगर (state->current_band & BAND_CBAND || state->current_band & BAND_FM || state->current_band & BAND_VHF) अणु
						state->current_band = BAND_CBAND;
						अगर (state->config->is_dib7090e)
							tune = dib0090_tuning_table_cband_7090e_sensitivity;
						अन्यथा
							tune = dib0090_tuning_table_cband_7090;
					पूर्ण
				पूर्ण
			पूर्ण अन्यथा
			 अगर (पंचांगp == 0x4 || पंचांगp == 0x7) अणु
				/* CBAND tuner version क्रम VHF */
				अगर (state->current_band == BAND_FM || state->current_band == BAND_CBAND || state->current_band == BAND_VHF) अणु
					state->current_band = BAND_CBAND;	/* Force CBAND */

					tune = dib0090_tuning_table_fm_vhf_on_cband;
					अगर (state->identity.p1g)
						tune = dib0090_p1g_tuning_table_fm_vhf_on_cband;
				पूर्ण
			पूर्ण

			pll = dib0090_pll_table;
			अगर (state->identity.p1g)
				pll = dib0090_p1g_pll_table;

			/* Look क्रम the पूर्णांकerval */
			जबतक (state->rf_request > tune->max_freq)
				tune++;
			जबतक (state->rf_request > pll->max_freq)
				pll++;

			state->current_tune_table_index = tune;
			state->current_pll_table_index = pll;

			dib0090_ग_लिखो_reg(state, 0x0b, 0xb800 | (tune->चयन_trim));

			VCOF_kHz = (pll->hfभाग * state->rf_request) * 2;

			FREF = state->config->io.घड़ी_khz;
			अगर (state->config->fref_घड़ी_ratio != 0)
				FREF /= state->config->fref_घड़ी_ratio;

			FBDiv = (VCOF_kHz / pll->topresc / FREF);
			Rest = (VCOF_kHz / pll->topresc) - FBDiv * FREF;

			अगर (Rest < LPF)
				Rest = 0;
			अन्यथा अगर (Rest < 2 * LPF)
				Rest = 2 * LPF;
			अन्यथा अगर (Rest > (FREF - LPF)) अणु
				Rest = 0;
				FBDiv += 1;
			पूर्ण अन्यथा अगर (Rest > (FREF - 2 * LPF))
				Rest = FREF - 2 * LPF;
			Rest = (Rest * 6528) / (FREF / 10);
			state->rest = Rest;

			/* बाह्यal loop filter, otherwise:
			 * lo5 = (0 << 15) | (0 << 12) | (0 << 11) | (3 << 9) | (4 << 6) | (3 << 4) | 4;
			 * lo6 = 0x0e34 */

			अगर (Rest == 0) अणु
				अगर (pll->vco_band)
					lo5 = 0x049f;
				अन्यथा
					lo5 = 0x041f;
			पूर्ण अन्यथा अणु
				अगर (pll->vco_band)
					lo5 = 0x049e;
				अन्यथा अगर (state->config->analog_output)
					lo5 = 0x041d;
				अन्यथा
					lo5 = 0x041c;
			पूर्ण

			अगर (state->identity.p1g) अणु	/* Bias is करोne स्वतःmatically in P1G */
				अगर (state->identity.in_soc) अणु
					अगर (state->identity.version == SOC_8090_P1G_11R1)
						lo5 = 0x46f;
					अन्यथा
						lo5 = 0x42f;
				पूर्ण अन्यथा
					lo5 = 0x42c;
			पूर्ण

			lo5 |= (pll->hfभाग_code << 11) | (pll->vco_band << 7);	/* bit 15 is the split to the slave, we करो not करो it here */

			अगर (!state->config->io.pll_पूर्णांक_loop_filt) अणु
				अगर (state->identity.in_soc)
					lo6 = 0xff98;
				अन्यथा अगर (state->identity.p1g || (Rest == 0))
					lo6 = 0xfff8;
				अन्यथा
					lo6 = 0xff28;
			पूर्ण अन्यथा
				lo6 = (state->config->io.pll_पूर्णांक_loop_filt << 3);

			Den = 1;

			अगर (Rest > 0) अणु
				lo6 |= (1 << 2) | 2;
				Den = 255;
			पूर्ण
			dib0090_ग_लिखो_reg(state, 0x15, (u16) FBDiv);
			अगर (state->config->fref_घड़ी_ratio != 0)
				dib0090_ग_लिखो_reg(state, 0x16, (Den << 8) | state->config->fref_घड़ी_ratio);
			अन्यथा
				dib0090_ग_लिखो_reg(state, 0x16, (Den << 8) | 1);
			dib0090_ग_लिखो_reg(state, 0x17, (u16) Rest);
			dib0090_ग_लिखो_reg(state, 0x19, lo5);
			dib0090_ग_लिखो_reg(state, 0x1c, lo6);

			lo6 = tune->tuner_enable;
			अगर (state->config->analog_output)
				lo6 = (lo6 & 0xff9f) | 0x2;

			dib0090_ग_लिखो_reg(state, 0x24, lo6 | EN_LO | state->config->use_pwm_agc * EN_CRYSTAL);

		पूर्ण

		state->current_rf = state->rf_request;
		state->current_standard = state->fe->dtv_property_cache.delivery_प्रणाली;

		ret = 20;
		state->calibrate = CAPTRIM_CAL;	/* captrim search now */
	पूर्ण

	अन्यथा अगर (*tune_state == CT_TUNER_STEP_0) अणु	/* Warning : because of captrim cal, अगर you change this step, change it also in _cal.c file because it is the step following captrim cal state machine */
		स्थिर काष्ठा dib0090_wbd_slope *wbd = state->current_wbd_table;

		जबतक (state->current_rf / 1000 > wbd->max_freq)
			wbd++;

		dib0090_ग_लिखो_reg(state, 0x1e, 0x07ff);
		dprपूर्णांकk("Final Captrim: %d\n", (u32) state->fcaptrim);
		dprपूर्णांकk("HFDIV code: %d\n", (u32) pll->hfभाग_code);
		dprपूर्णांकk("VCO = %d\n", (u32) pll->vco_band);
		dprपूर्णांकk("VCOF in kHz: %d ((%d*%d) << 1))\n", (u32) ((pll->hfभाग * state->rf_request) * 2), (u32) pll->hfभाग, (u32) state->rf_request);
		dprपूर्णांकk("REFDIV: %d, FREF: %d\n", (u32) 1, (u32) state->config->io.घड़ी_khz);
		dprपूर्णांकk("FBDIV: %d, Rest: %d\n", (u32) dib0090_पढ़ो_reg(state, 0x15), (u32) dib0090_पढ़ो_reg(state, 0x17));
		dprपूर्णांकk("Num: %d, Den: %d, SD: %d\n", (u32) dib0090_पढ़ो_reg(state, 0x17), (u32) (dib0090_पढ़ो_reg(state, 0x16) >> 8),
			(u32) dib0090_पढ़ो_reg(state, 0x1c) & 0x3);

#घोषणा WBD     0x781		/* 1 1 1 1 0000 0 0 1 */
		c = 4;
		i = 3;

		अगर (wbd->wbd_gain != 0)
			c = wbd->wbd_gain;

		state->wbdmux = (c << 13) | (i << 11) | (WBD | (state->config->use_pwm_agc << 1));
		dib0090_ग_लिखो_reg(state, 0x10, state->wbdmux);

		अगर ((tune->tuner_enable == EN_CAB) && state->identity.p1g) अणु
			dprपूर्णांकk("P1G : The cable band is selected and lna_tune = %d\n", tune->lna_tune);
			dib0090_ग_लिखो_reg(state, 0x09, tune->lna_bias);
			dib0090_ग_लिखो_reg(state, 0x0b, 0xb800 | (tune->lna_tune << 6) | (tune->चयन_trim));
		पूर्ण अन्यथा
			dib0090_ग_लिखो_reg(state, 0x09, (tune->lna_tune << 5) | tune->lna_bias);

		dib0090_ग_लिखो_reg(state, 0x0c, tune->v2i);
		dib0090_ग_लिखो_reg(state, 0x0d, tune->mix);
		dib0090_ग_लिखो_reg(state, 0x0e, tune->load);
		*tune_state = CT_TUNER_STEP_1;

	पूर्ण अन्यथा अगर (*tune_state == CT_TUNER_STEP_1) अणु
		/* initialize the lt gain रेजिस्टर */
		state->rf_lt_def = 0x7c00;

		dib0090_set_bandwidth(state);
		state->tuner_is_tuned = 1;

		state->calibrate |= WBD_CAL;
		state->calibrate |= TEMP_CAL;
		*tune_state = CT_TUNER_STOP;
	पूर्ण अन्यथा
		ret = FE_CALLBACK_TIME_NEVER;
	वापस ret;
पूर्ण

अटल व्योम dib0090_release(काष्ठा dvb_frontend *fe)
अणु
	kमुक्त(fe->tuner_priv);
	fe->tuner_priv = शून्य;
पूर्ण

क्रमागत frontend_tune_state dib0090_get_tune_state(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dib0090_state *state = fe->tuner_priv;

	वापस state->tune_state;
पूर्ण

EXPORT_SYMBOL(dib0090_get_tune_state);

पूर्णांक dib0090_set_tune_state(काष्ठा dvb_frontend *fe, क्रमागत frontend_tune_state tune_state)
अणु
	काष्ठा dib0090_state *state = fe->tuner_priv;

	state->tune_state = tune_state;
	वापस 0;
पूर्ण

EXPORT_SYMBOL(dib0090_set_tune_state);

अटल पूर्णांक dib0090_get_frequency(काष्ठा dvb_frontend *fe, u32 * frequency)
अणु
	काष्ठा dib0090_state *state = fe->tuner_priv;

	*frequency = 1000 * state->current_rf;
	वापस 0;
पूर्ण

अटल पूर्णांक dib0090_set_params(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dib0090_state *state = fe->tuner_priv;
	u32 ret;

	state->tune_state = CT_TUNER_START;

	करो अणु
		ret = dib0090_tune(fe);
		अगर (ret == FE_CALLBACK_TIME_NEVER)
			अवरोध;

		/*
		 * Despite dib0090_tune वापसs समय at a 0.1 ms range,
		 * the actual sleep समय depends on CONFIG_HZ. The worse हाल
		 * is when CONFIG_HZ=100. In such हाल, the minimum granularity
		 * is 10ms. On some real field tests, the tuner someबार करोn't
		 * lock when this समयr is lower than 10ms. So, enक्रमce a 10ms
		 * granularity and use usleep_range() instead of msleep().
		 */
		ret = 10 * (ret + 99)/100;
		usleep_range(ret * 1000, (ret + 1) * 1000);
	पूर्ण जबतक (state->tune_state != CT_TUNER_STOP);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dvb_tuner_ops dib0090_ops = अणु
	.info = अणु
		 .name = "DiBcom DiB0090",
		 .frequency_min_hz  =  45 * MHz,
		 .frequency_max_hz  = 860 * MHz,
		 .frequency_step_hz =   1 * kHz,
		 पूर्ण,
	.release = dib0090_release,

	.init = dib0090_wakeup,
	.sleep = dib0090_sleep,
	.set_params = dib0090_set_params,
	.get_frequency = dib0090_get_frequency,
पूर्ण;

अटल स्थिर काष्ठा dvb_tuner_ops dib0090_fw_ops = अणु
	.info = अणु
		 .name = "DiBcom DiB0090",
		 .frequency_min_hz  =  45 * MHz,
		 .frequency_max_hz  = 860 * MHz,
		 .frequency_step_hz =   1 * kHz,
		 पूर्ण,
	.release = dib0090_release,

	.init = शून्य,
	.sleep = शून्य,
	.set_params = शून्य,
	.get_frequency = शून्य,
पूर्ण;

अटल स्थिर काष्ठा dib0090_wbd_slope dib0090_wbd_table_शेष[] = अणु
	अणु470, 0, 250, 0, 100, 4पूर्ण,
	अणु860, 51, 866, 21, 375, 4पूर्ण,
	अणु1700, 0, 800, 0, 850, 4पूर्ण,
	अणु2900, 0, 250, 0, 100, 6पूर्ण,
	अणु0xFFFF, 0, 0, 0, 0, 0पूर्ण,
पूर्ण;

काष्ठा dvb_frontend *dib0090_रेजिस्टर(काष्ठा dvb_frontend *fe, काष्ठा i2c_adapter *i2c, स्थिर काष्ठा dib0090_config *config)
अणु
	काष्ठा dib0090_state *st = kzalloc(माप(काष्ठा dib0090_state), GFP_KERNEL);
	अगर (st == शून्य)
		वापस शून्य;

	st->config = config;
	st->i2c = i2c;
	st->fe = fe;
	mutex_init(&st->i2c_buffer_lock);
	fe->tuner_priv = st;

	अगर (config->wbd == शून्य)
		st->current_wbd_table = dib0090_wbd_table_शेष;
	अन्यथा
		st->current_wbd_table = config->wbd;

	अगर (dib0090_reset(fe) != 0)
		जाओ मुक्त_mem;

	pr_info("DiB0090: successfully identified\n");
	स_नकल(&fe->ops.tuner_ops, &dib0090_ops, माप(काष्ठा dvb_tuner_ops));

	वापस fe;
 मुक्त_mem:
	kमुक्त(st);
	fe->tuner_priv = शून्य;
	वापस शून्य;
पूर्ण

EXPORT_SYMBOL(dib0090_रेजिस्टर);

काष्ठा dvb_frontend *dib0090_fw_रेजिस्टर(काष्ठा dvb_frontend *fe, काष्ठा i2c_adapter *i2c, स्थिर काष्ठा dib0090_config *config)
अणु
	काष्ठा dib0090_fw_state *st = kzalloc(माप(काष्ठा dib0090_fw_state), GFP_KERNEL);
	अगर (st == शून्य)
		वापस शून्य;

	st->config = config;
	st->i2c = i2c;
	st->fe = fe;
	mutex_init(&st->i2c_buffer_lock);
	fe->tuner_priv = st;

	अगर (dib0090_fw_reset_digital(fe, st->config) != 0)
		जाओ मुक्त_mem;

	dprपूर्णांकk("DiB0090 FW: successfully identified\n");
	स_नकल(&fe->ops.tuner_ops, &dib0090_fw_ops, माप(काष्ठा dvb_tuner_ops));

	वापस fe;
मुक्त_mem:
	kमुक्त(st);
	fe->tuner_priv = शून्य;
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(dib0090_fw_रेजिस्टर);

MODULE_AUTHOR("Patrick Boettcher <patrick.boettcher@posteo.de>");
MODULE_AUTHOR("Olivier Grenie <olivier.grenie@parrot.com>");
MODULE_DESCRIPTION("Driver for the DiBcom 0090 base-band RF Tuner");
MODULE_LICENSE("GPL");
