<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  mxl111sf-phy.c - driver क्रम the MaxLinear MXL111SF
 *
 *  Copyright (C) 2010-2014 Michael Krufky <mkrufky@linuxtv.org>
 */

#समावेश "mxl111sf-phy.h"
#समावेश "mxl111sf-reg.h"

पूर्णांक mxl111sf_init_tuner_demod(काष्ठा mxl111sf_state *state)
अणु
	काष्ठा mxl111sf_reg_ctrl_info mxl_111_overग_लिखो_शेष[] = अणु
		अणु0x07, 0xff, 0x0cपूर्ण,
		अणु0x58, 0xff, 0x9dपूर्ण,
		अणु0x09, 0xff, 0x00पूर्ण,
		अणु0x06, 0xff, 0x06पूर्ण,
		अणु0xc8, 0xff, 0x40पूर्ण, /* ED_LE_WIN_OLD = 0 */
		अणु0x8d, 0x01, 0x01पूर्ण, /* NEGATE_Q */
		अणु0x32, 0xff, 0xacपूर्ण, /* DIG_RFREFSELECT = 12 */
		अणु0x42, 0xff, 0x43पूर्ण, /* DIG_REG_AMP = 4 */
		अणु0x74, 0xff, 0xc4पूर्ण, /* SSPUR_FS_PRIO = 4 */
		अणु0x71, 0xff, 0xe6पूर्ण, /* SPUR_ROT_PRIO_VAL = 1 */
		अणु0x83, 0xff, 0x64पूर्ण, /* INF_FILT1_THD_SC = 100 */
		अणु0x85, 0xff, 0x64पूर्ण, /* INF_FILT2_THD_SC = 100 */
		अणु0x88, 0xff, 0xf0पूर्ण, /* INF_THD = 240 */
		अणु0x6f, 0xf0, 0xb0पूर्ण, /* DFE_DLY = 11 */
		अणु0x00, 0xff, 0x01पूर्ण, /* Change to page 1 */
		अणु0x81, 0xff, 0x11पूर्ण, /* DSM_FERR_BYPASS = 1 */
		अणु0xf4, 0xff, 0x07पूर्ण, /* DIG_FREQ_CORR = 1 */
		अणु0xd4, 0x1f, 0x0fपूर्ण, /* SPUR_TEST_NOISE_TH = 15 */
		अणु0xd6, 0xff, 0x0cपूर्ण, /* SPUR_TEST_NOISE_PAPR = 12 */
		अणु0x00, 0xff, 0x00पूर्ण, /* Change to page 0 */
		अणु0,    0,    0पूर्ण
	पूर्ण;

	mxl_debug("()");

	वापस mxl111sf_ctrl_program_regs(state, mxl_111_overग_लिखो_शेष);
पूर्ण

पूर्णांक mxl1x1sf_soft_reset(काष्ठा mxl111sf_state *state)
अणु
	पूर्णांक ret;
	mxl_debug("()");

	ret = mxl111sf_ग_लिखो_reg(state, 0xff, 0x00); /* AIC */
	अगर (mxl_fail(ret))
		जाओ fail;
	ret = mxl111sf_ग_लिखो_reg(state, 0x02, 0x01); /* get out of reset */
	mxl_fail(ret);
fail:
	वापस ret;
पूर्ण

पूर्णांक mxl1x1sf_set_device_mode(काष्ठा mxl111sf_state *state, पूर्णांक mode)
अणु
	पूर्णांक ret;

	mxl_debug("(%s)", MXL_SOC_MODE == mode ?
		"MXL_SOC_MODE" : "MXL_TUNER_MODE");

	/* set device mode */
	ret = mxl111sf_ग_लिखो_reg(state, 0x03,
				 MXL_SOC_MODE == mode ? 0x01 : 0x00);
	अगर (mxl_fail(ret))
		जाओ fail;

	ret = mxl111sf_ग_लिखो_reg_mask(state,
				      0x7d, 0x40, MXL_SOC_MODE == mode ?
				      0x00 : /* enable impulse noise filter,
						INF_BYP = 0 */
				      0x40); /* disable impulse noise filter,
						INF_BYP = 1 */
	अगर (mxl_fail(ret))
		जाओ fail;

	state->device_mode = mode;
fail:
	वापस ret;
पूर्ण

/* घातer up tuner */
पूर्णांक mxl1x1sf_top_master_ctrl(काष्ठा mxl111sf_state *state, पूर्णांक onoff)
अणु
	mxl_debug("(%d)", onoff);

	वापस mxl111sf_ग_लिखो_reg(state, 0x01, onoff ? 0x01 : 0x00);
पूर्ण

पूर्णांक mxl111sf_disable_656_port(काष्ठा mxl111sf_state *state)
अणु
	mxl_debug("()");

	वापस mxl111sf_ग_लिखो_reg_mask(state, 0x12, 0x04, 0x00);
पूर्ण

पूर्णांक mxl111sf_enable_usb_output(काष्ठा mxl111sf_state *state)
अणु
	mxl_debug("()");

	वापस mxl111sf_ग_लिखो_reg_mask(state, 0x17, 0x40, 0x00);
पूर्ण

/* initialize TSIF as input port of MxL1X1SF क्रम MPEG2 data transfer */
पूर्णांक mxl111sf_config_mpeg_in(काष्ठा mxl111sf_state *state,
			    अचिन्हित पूर्णांक parallel_serial,
			    अचिन्हित पूर्णांक msb_lsb_1st,
			    अचिन्हित पूर्णांक घड़ी_phase,
			    अचिन्हित पूर्णांक mpeg_valid_pol,
			    अचिन्हित पूर्णांक mpeg_sync_pol)
अणु
	पूर्णांक ret;
	u8 mode, पंचांगp;

	mxl_debug("(%u,%u,%u,%u,%u)", parallel_serial, msb_lsb_1st,
		  घड़ी_phase, mpeg_valid_pol, mpeg_sync_pol);

	/* Enable PIN MUX */
	ret = mxl111sf_ग_लिखो_reg(state, V6_PIN_MUX_MODE_REG, V6_ENABLE_PIN_MUX);
	mxl_fail(ret);

	/* Configure MPEG Clock phase */
	mxl111sf_पढ़ो_reg(state, V6_MPEG_IN_CLK_INV_REG, &mode);

	अगर (घड़ी_phase == TSIF_NORMAL)
		mode &= ~V6_INVERTED_CLK_PHASE;
	अन्यथा
		mode |= V6_INVERTED_CLK_PHASE;

	ret = mxl111sf_ग_लिखो_reg(state, V6_MPEG_IN_CLK_INV_REG, mode);
	mxl_fail(ret);

	/* Configure data input mode, MPEG Valid polarity, MPEG Sync polarity
	 * Get current configuration */
	ret = mxl111sf_पढ़ो_reg(state, V6_MPEG_IN_CTRL_REG, &mode);
	mxl_fail(ret);

	/* Data Input mode */
	अगर (parallel_serial == TSIF_INPUT_PARALLEL) अणु
		/* Disable serial mode */
		mode &= ~V6_MPEG_IN_DATA_SERIAL;

		/* Enable Parallel mode */
		mode |= V6_MPEG_IN_DATA_PARALLEL;
	पूर्ण अन्यथा अणु
		/* Disable Parallel mode */
		mode &= ~V6_MPEG_IN_DATA_PARALLEL;

		/* Enable Serial Mode */
		mode |= V6_MPEG_IN_DATA_SERIAL;

		/* If serial पूर्णांकerface is chosen, configure
		   MSB or LSB order in transmission */
		ret = mxl111sf_पढ़ो_reg(state,
					V6_MPEG_INOUT_BIT_ORDER_CTRL_REG,
					&पंचांगp);
		mxl_fail(ret);

		अगर (msb_lsb_1st == MPEG_SER_MSB_FIRST_ENABLED)
			पंचांगp |= V6_MPEG_SER_MSB_FIRST;
		अन्यथा
			पंचांगp &= ~V6_MPEG_SER_MSB_FIRST;

		ret = mxl111sf_ग_लिखो_reg(state,
					 V6_MPEG_INOUT_BIT_ORDER_CTRL_REG,
					 पंचांगp);
		mxl_fail(ret);
	पूर्ण

	/* MPEG Sync polarity */
	अगर (mpeg_sync_pol == TSIF_NORMAL)
		mode &= ~V6_INVERTED_MPEG_SYNC;
	अन्यथा
		mode |= V6_INVERTED_MPEG_SYNC;

	/* MPEG Valid polarity */
	अगर (mpeg_valid_pol == 0)
		mode &= ~V6_INVERTED_MPEG_VALID;
	अन्यथा
		mode |= V6_INVERTED_MPEG_VALID;

	ret = mxl111sf_ग_लिखो_reg(state, V6_MPEG_IN_CTRL_REG, mode);
	mxl_fail(ret);

	वापस ret;
पूर्ण

पूर्णांक mxl111sf_init_i2s_port(काष्ठा mxl111sf_state *state, u8 sample_size)
अणु
	अटल काष्ठा mxl111sf_reg_ctrl_info init_i2s[] = अणु
		अणु0x1b, 0xff, 0x1eपूर्ण, /* pin mux mode, Choose 656/I2S input */
		अणु0x15, 0x60, 0x60पूर्ण, /* Enable I2S */
		अणु0x17, 0xe0, 0x20पूर्ण, /* Input, MPEG MODE USB,
				       Inverted 656 Clock, I2S_SOFT_RESET,
				       0 : Normal operation, 1 : Reset State */
#अगर 0
		अणु0x12, 0x01, 0x00पूर्ण, /* AUDIO_IRQ_CLR (Overflow Indicator) */
#पूर्ण_अगर
		अणु0x00, 0xff, 0x02पूर्ण, /* Change to Control Page */
		अणु0x26, 0x0d, 0x0dपूर्ण, /* I2S_MODE & BT656_SRC_SEL क्रम FPGA only */
		अणु0x00, 0xff, 0x00पूर्ण,
		अणु0,    0,    0पूर्ण
	पूर्ण;
	पूर्णांक ret;

	mxl_debug("(0x%02x)", sample_size);

	ret = mxl111sf_ctrl_program_regs(state, init_i2s);
	अगर (mxl_fail(ret))
		जाओ fail;

	ret = mxl111sf_ग_लिखो_reg(state, V6_I2S_NUM_SAMPLES_REG, sample_size);
	mxl_fail(ret);
fail:
	वापस ret;
पूर्ण

पूर्णांक mxl111sf_disable_i2s_port(काष्ठा mxl111sf_state *state)
अणु
	अटल काष्ठा mxl111sf_reg_ctrl_info disable_i2s[] = अणु
		अणु0x15, 0x40, 0x00पूर्ण,
		अणु0,    0,    0पूर्ण
	पूर्ण;

	mxl_debug("()");

	वापस mxl111sf_ctrl_program_regs(state, disable_i2s);
पूर्ण

पूर्णांक mxl111sf_config_i2s(काष्ठा mxl111sf_state *state,
			u8 msb_start_pos, u8 data_width)
अणु
	पूर्णांक ret;
	u8 पंचांगp;

	mxl_debug("(0x%02x, 0x%02x)", msb_start_pos, data_width);

	ret = mxl111sf_पढ़ो_reg(state, V6_I2S_STREAM_START_BIT_REG, &पंचांगp);
	अगर (mxl_fail(ret))
		जाओ fail;

	पंचांगp &= 0xe0;
	पंचांगp |= msb_start_pos;
	ret = mxl111sf_ग_लिखो_reg(state, V6_I2S_STREAM_START_BIT_REG, पंचांगp);
	अगर (mxl_fail(ret))
		जाओ fail;

	ret = mxl111sf_पढ़ो_reg(state, V6_I2S_STREAM_END_BIT_REG, &पंचांगp);
	अगर (mxl_fail(ret))
		जाओ fail;

	पंचांगp &= 0xe0;
	पंचांगp |= data_width;
	ret = mxl111sf_ग_लिखो_reg(state, V6_I2S_STREAM_END_BIT_REG, पंचांगp);
	mxl_fail(ret);
fail:
	वापस ret;
पूर्ण

पूर्णांक mxl111sf_config_spi(काष्ठा mxl111sf_state *state, पूर्णांक onoff)
अणु
	u8 val;
	पूर्णांक ret;

	mxl_debug("(%d)", onoff);

	ret = mxl111sf_ग_लिखो_reg(state, 0x00, 0x02);
	अगर (mxl_fail(ret))
		जाओ fail;

	ret = mxl111sf_पढ़ो_reg(state, V8_SPI_MODE_REG, &val);
	अगर (mxl_fail(ret))
		जाओ fail;

	अगर (onoff)
		val |= 0x04;
	अन्यथा
		val &= ~0x04;

	ret = mxl111sf_ग_लिखो_reg(state, V8_SPI_MODE_REG, val);
	अगर (mxl_fail(ret))
		जाओ fail;

	ret = mxl111sf_ग_लिखो_reg(state, 0x00, 0x00);
	mxl_fail(ret);
fail:
	वापस ret;
पूर्ण

पूर्णांक mxl111sf_idac_config(काष्ठा mxl111sf_state *state,
			 u8 control_mode, u8 current_setting,
			 u8 current_value, u8 hysteresis_value)
अणु
	पूर्णांक ret;
	u8 val;
	/* current value will be set क्रम both स्वतःmatic & manual IDAC control */
	val = current_value;

	अगर (control_mode == IDAC_MANUAL_CONTROL) अणु
		/* enable manual control of IDAC */
		val |= IDAC_MANUAL_CONTROL_BIT_MASK;

		अगर (current_setting == IDAC_CURRENT_SINKING_ENABLE)
			/* enable current sinking in manual mode */
			val |= IDAC_CURRENT_SINKING_BIT_MASK;
		अन्यथा
			/* disable current sinking in manual mode */
			val &= ~IDAC_CURRENT_SINKING_BIT_MASK;
	पूर्ण अन्यथा अणु
		/* disable manual control of IDAC */
		val &= ~IDAC_MANUAL_CONTROL_BIT_MASK;

		/* set hysteresis value  reg: 0x0B<5:0> */
		ret = mxl111sf_ग_लिखो_reg(state, V6_IDAC_HYSTERESIS_REG,
					 (hysteresis_value & 0x3F));
		mxl_fail(ret);
	पूर्ण

	ret = mxl111sf_ग_लिखो_reg(state, V6_IDAC_SETTINGS_REG, val);
	mxl_fail(ret);

	वापस ret;
पूर्ण
