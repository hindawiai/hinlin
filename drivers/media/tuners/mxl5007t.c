<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  mxl5007t.c - driver क्रम the MaxLinear MxL5007T silicon tuner
 *
 *  Copyright (C) 2008, 2009 Michael Krufky <mkrufky@linuxtv.org>
 */

#समावेश <linux/i2c.h>
#समावेश <linux/types.h>
#समावेश <linux/videodev2.h>
#समावेश "tuner-i2c.h"
#समावेश "mxl5007t.h"

अटल DEFINE_MUTEX(mxl5007t_list_mutex);
अटल LIST_HEAD(hybrid_tuner_instance_list);

अटल पूर्णांक mxl5007t_debug;
module_param_named(debug, mxl5007t_debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug, "set debug level");

/* ------------------------------------------------------------------------- */

#घोषणा mxl_prपूर्णांकk(kern, fmt, arg...) \
	prपूर्णांकk(kern "%s: " fmt "\n", __func__, ##arg)

#घोषणा mxl_err(fmt, arg...) \
	mxl_prपूर्णांकk(KERN_ERR, "%d: " fmt, __LINE__, ##arg)

#घोषणा mxl_warn(fmt, arg...) \
	mxl_prपूर्णांकk(KERN_WARNING, fmt, ##arg)

#घोषणा mxl_info(fmt, arg...) \
	mxl_prपूर्णांकk(KERN_INFO, fmt, ##arg)

#घोषणा mxl_debug(fmt, arg...)				\
(अणु							\
	अगर (mxl5007t_debug)				\
		mxl_prपूर्णांकk(KERN_DEBUG, fmt, ##arg);	\
पूर्ण)

#घोषणा mxl_fail(ret)							\
(अणु									\
	पूर्णांक __ret;							\
	__ret = (ret < 0);						\
	अगर (__ret)							\
		mxl_prपूर्णांकk(KERN_ERR, "error %d on line %d",		\
			   ret, __LINE__);				\
	__ret;								\
पूर्ण)

/* ------------------------------------------------------------------------- */

क्रमागत mxl5007t_mode अणु
	MxL_MODE_ISDBT     =    0,
	MxL_MODE_DVBT      =    1,
	MxL_MODE_ATSC      =    2,
	MxL_MODE_CABLE     = 0x10,
पूर्ण;

क्रमागत mxl5007t_chip_version अणु
	MxL_UNKNOWN_ID     = 0x00,
	MxL_5007_V1_F1     = 0x11,
	MxL_5007_V1_F2     = 0x12,
	MxL_5007_V4        = 0x14,
	MxL_5007_V2_100_F1 = 0x21,
	MxL_5007_V2_100_F2 = 0x22,
	MxL_5007_V2_200_F1 = 0x23,
	MxL_5007_V2_200_F2 = 0x24,
पूर्ण;

काष्ठा reg_pair_t अणु
	u8 reg;
	u8 val;
पूर्ण;

/* ------------------------------------------------------------------------- */

अटल काष्ठा reg_pair_t init_tab[] = अणु
	अणु 0x02, 0x06 पूर्ण,
	अणु 0x03, 0x48 पूर्ण,
	अणु 0x05, 0x04 पूर्ण,
	अणु 0x06, 0x10 पूर्ण,
	अणु 0x2e, 0x15 पूर्ण, /* OVERRIDE */
	अणु 0x30, 0x10 पूर्ण, /* OVERRIDE */
	अणु 0x45, 0x58 पूर्ण, /* OVERRIDE */
	अणु 0x48, 0x19 पूर्ण, /* OVERRIDE */
	अणु 0x52, 0x03 पूर्ण, /* OVERRIDE */
	अणु 0x53, 0x44 पूर्ण, /* OVERRIDE */
	अणु 0x6a, 0x4b पूर्ण, /* OVERRIDE */
	अणु 0x76, 0x00 पूर्ण, /* OVERRIDE */
	अणु 0x78, 0x18 पूर्ण, /* OVERRIDE */
	अणु 0x7a, 0x17 पूर्ण, /* OVERRIDE */
	अणु 0x85, 0x06 पूर्ण, /* OVERRIDE */
	अणु 0x01, 0x01 पूर्ण, /* TOP_MASTER_ENABLE */
	अणु 0, 0 पूर्ण
पूर्ण;

अटल काष्ठा reg_pair_t init_tab_cable[] = अणु
	अणु 0x02, 0x06 पूर्ण,
	अणु 0x03, 0x48 पूर्ण,
	अणु 0x05, 0x04 पूर्ण,
	अणु 0x06, 0x10 पूर्ण,
	अणु 0x09, 0x3f पूर्ण,
	अणु 0x0a, 0x3f पूर्ण,
	अणु 0x0b, 0x3f पूर्ण,
	अणु 0x2e, 0x15 पूर्ण, /* OVERRIDE */
	अणु 0x30, 0x10 पूर्ण, /* OVERRIDE */
	अणु 0x45, 0x58 पूर्ण, /* OVERRIDE */
	अणु 0x48, 0x19 पूर्ण, /* OVERRIDE */
	अणु 0x52, 0x03 पूर्ण, /* OVERRIDE */
	अणु 0x53, 0x44 पूर्ण, /* OVERRIDE */
	अणु 0x6a, 0x4b पूर्ण, /* OVERRIDE */
	अणु 0x76, 0x00 पूर्ण, /* OVERRIDE */
	अणु 0x78, 0x18 पूर्ण, /* OVERRIDE */
	अणु 0x7a, 0x17 पूर्ण, /* OVERRIDE */
	अणु 0x85, 0x06 पूर्ण, /* OVERRIDE */
	अणु 0x01, 0x01 पूर्ण, /* TOP_MASTER_ENABLE */
	अणु 0, 0 पूर्ण
पूर्ण;

/* ------------------------------------------------------------------------- */

अटल काष्ठा reg_pair_t reg_pair_rftune[] = अणु
	अणु 0x0f, 0x00 पूर्ण, /* पात tune */
	अणु 0x0c, 0x15 पूर्ण,
	अणु 0x0d, 0x40 पूर्ण,
	अणु 0x0e, 0x0e पूर्ण,
	अणु 0x1f, 0x87 पूर्ण, /* OVERRIDE */
	अणु 0x20, 0x1f पूर्ण, /* OVERRIDE */
	अणु 0x21, 0x87 पूर्ण, /* OVERRIDE */
	अणु 0x22, 0x1f पूर्ण, /* OVERRIDE */
	अणु 0x80, 0x01 पूर्ण, /* freq dependent */
	अणु 0x0f, 0x01 पूर्ण, /* start tune */
	अणु 0, 0 पूर्ण
पूर्ण;

/* ------------------------------------------------------------------------- */

काष्ठा mxl5007t_state अणु
	काष्ठा list_head hybrid_tuner_instance_list;
	काष्ठा tuner_i2c_props i2c_props;

	काष्ठा mutex lock;

	काष्ठा mxl5007t_config *config;

	क्रमागत mxl5007t_chip_version chip_id;

	काष्ठा reg_pair_t tab_init[ARRAY_SIZE(init_tab)];
	काष्ठा reg_pair_t tab_init_cable[ARRAY_SIZE(init_tab_cable)];
	काष्ठा reg_pair_t tab_rftune[ARRAY_SIZE(reg_pair_rftune)];

	क्रमागत mxl5007t_अगर_freq अगर_freq;

	u32 frequency;
	u32 bandwidth;
पूर्ण;

/* ------------------------------------------------------------------------- */

/* called by _init and _rftun to manipulate the रेजिस्टर arrays */

अटल व्योम set_reg_bits(काष्ठा reg_pair_t *reg_pair, u8 reg, u8 mask, u8 val)
अणु
	अचिन्हित पूर्णांक i = 0;

	जबतक (reg_pair[i].reg || reg_pair[i].val) अणु
		अगर (reg_pair[i].reg == reg) अणु
			reg_pair[i].val &= ~mask;
			reg_pair[i].val |= val;
		पूर्ण
		i++;

	पूर्ण
	वापस;
पूर्ण

अटल व्योम copy_reg_bits(काष्ठा reg_pair_t *reg_pair1,
			  काष्ठा reg_pair_t *reg_pair2)
अणु
	अचिन्हित पूर्णांक i, j;

	i = j = 0;

	जबतक (reg_pair1[i].reg || reg_pair1[i].val) अणु
		जबतक (reg_pair2[j].reg || reg_pair2[j].val) अणु
			अगर (reg_pair1[i].reg != reg_pair2[j].reg) अणु
				j++;
				जारी;
			पूर्ण
			reg_pair2[j].val = reg_pair1[i].val;
			अवरोध;
		पूर्ण
		i++;
	पूर्ण
	वापस;
पूर्ण

/* ------------------------------------------------------------------------- */

अटल व्योम mxl5007t_set_mode_bits(काष्ठा mxl5007t_state *state,
				   क्रमागत mxl5007t_mode mode,
				   s32 अगर_dअगरf_out_level)
अणु
	चयन (mode) अणु
	हाल MxL_MODE_ATSC:
		set_reg_bits(state->tab_init, 0x06, 0x1f, 0x12);
		अवरोध;
	हाल MxL_MODE_DVBT:
		set_reg_bits(state->tab_init, 0x06, 0x1f, 0x11);
		अवरोध;
	हाल MxL_MODE_ISDBT:
		set_reg_bits(state->tab_init, 0x06, 0x1f, 0x10);
		अवरोध;
	हाल MxL_MODE_CABLE:
		set_reg_bits(state->tab_init_cable, 0x09, 0xff, 0xc1);
		set_reg_bits(state->tab_init_cable, 0x0a, 0xff,
			     8 - अगर_dअगरf_out_level);
		set_reg_bits(state->tab_init_cable, 0x0b, 0xff, 0x17);
		अवरोध;
	शेष:
		mxl_fail(-EINVAL);
	पूर्ण
	वापस;
पूर्ण

अटल व्योम mxl5007t_set_अगर_freq_bits(काष्ठा mxl5007t_state *state,
				      क्रमागत mxl5007t_अगर_freq अगर_freq,
				      पूर्णांक invert_अगर)
अणु
	u8 val;

	चयन (अगर_freq) अणु
	हाल MxL_IF_4_MHZ:
		val = 0x00;
		अवरोध;
	हाल MxL_IF_4_5_MHZ:
		val = 0x02;
		अवरोध;
	हाल MxL_IF_4_57_MHZ:
		val = 0x03;
		अवरोध;
	हाल MxL_IF_5_MHZ:
		val = 0x04;
		अवरोध;
	हाल MxL_IF_5_38_MHZ:
		val = 0x05;
		अवरोध;
	हाल MxL_IF_6_MHZ:
		val = 0x06;
		अवरोध;
	हाल MxL_IF_6_28_MHZ:
		val = 0x07;
		अवरोध;
	हाल MxL_IF_9_1915_MHZ:
		val = 0x08;
		अवरोध;
	हाल MxL_IF_35_25_MHZ:
		val = 0x09;
		अवरोध;
	हाल MxL_IF_36_15_MHZ:
		val = 0x0a;
		अवरोध;
	हाल MxL_IF_44_MHZ:
		val = 0x0b;
		अवरोध;
	शेष:
		mxl_fail(-EINVAL);
		वापस;
	पूर्ण
	set_reg_bits(state->tab_init, 0x02, 0x0f, val);

	/* set inverted IF or normal IF */
	set_reg_bits(state->tab_init, 0x02, 0x10, invert_अगर ? 0x10 : 0x00);

	state->अगर_freq = अगर_freq;

	वापस;
पूर्ण

अटल व्योम mxl5007t_set_xtal_freq_bits(काष्ठा mxl5007t_state *state,
					क्रमागत mxl5007t_xtal_freq xtal_freq)
अणु
	चयन (xtal_freq) अणु
	हाल MxL_XTAL_16_MHZ:
		/* select xtal freq & ref freq */
		set_reg_bits(state->tab_init, 0x03, 0xf0, 0x00);
		set_reg_bits(state->tab_init, 0x05, 0x0f, 0x00);
		अवरोध;
	हाल MxL_XTAL_20_MHZ:
		set_reg_bits(state->tab_init, 0x03, 0xf0, 0x10);
		set_reg_bits(state->tab_init, 0x05, 0x0f, 0x01);
		अवरोध;
	हाल MxL_XTAL_20_25_MHZ:
		set_reg_bits(state->tab_init, 0x03, 0xf0, 0x20);
		set_reg_bits(state->tab_init, 0x05, 0x0f, 0x02);
		अवरोध;
	हाल MxL_XTAL_20_48_MHZ:
		set_reg_bits(state->tab_init, 0x03, 0xf0, 0x30);
		set_reg_bits(state->tab_init, 0x05, 0x0f, 0x03);
		अवरोध;
	हाल MxL_XTAL_24_MHZ:
		set_reg_bits(state->tab_init, 0x03, 0xf0, 0x40);
		set_reg_bits(state->tab_init, 0x05, 0x0f, 0x04);
		अवरोध;
	हाल MxL_XTAL_25_MHZ:
		set_reg_bits(state->tab_init, 0x03, 0xf0, 0x50);
		set_reg_bits(state->tab_init, 0x05, 0x0f, 0x05);
		अवरोध;
	हाल MxL_XTAL_25_14_MHZ:
		set_reg_bits(state->tab_init, 0x03, 0xf0, 0x60);
		set_reg_bits(state->tab_init, 0x05, 0x0f, 0x06);
		अवरोध;
	हाल MxL_XTAL_27_MHZ:
		set_reg_bits(state->tab_init, 0x03, 0xf0, 0x70);
		set_reg_bits(state->tab_init, 0x05, 0x0f, 0x07);
		अवरोध;
	हाल MxL_XTAL_28_8_MHZ:
		set_reg_bits(state->tab_init, 0x03, 0xf0, 0x80);
		set_reg_bits(state->tab_init, 0x05, 0x0f, 0x08);
		अवरोध;
	हाल MxL_XTAL_32_MHZ:
		set_reg_bits(state->tab_init, 0x03, 0xf0, 0x90);
		set_reg_bits(state->tab_init, 0x05, 0x0f, 0x09);
		अवरोध;
	हाल MxL_XTAL_40_MHZ:
		set_reg_bits(state->tab_init, 0x03, 0xf0, 0xa0);
		set_reg_bits(state->tab_init, 0x05, 0x0f, 0x0a);
		अवरोध;
	हाल MxL_XTAL_44_MHZ:
		set_reg_bits(state->tab_init, 0x03, 0xf0, 0xb0);
		set_reg_bits(state->tab_init, 0x05, 0x0f, 0x0b);
		अवरोध;
	हाल MxL_XTAL_48_MHZ:
		set_reg_bits(state->tab_init, 0x03, 0xf0, 0xc0);
		set_reg_bits(state->tab_init, 0x05, 0x0f, 0x0c);
		अवरोध;
	हाल MxL_XTAL_49_3811_MHZ:
		set_reg_bits(state->tab_init, 0x03, 0xf0, 0xd0);
		set_reg_bits(state->tab_init, 0x05, 0x0f, 0x0d);
		अवरोध;
	शेष:
		mxl_fail(-EINVAL);
		वापस;
	पूर्ण

	वापस;
पूर्ण

अटल काष्ठा reg_pair_t *mxl5007t_calc_init_regs(काष्ठा mxl5007t_state *state,
						  क्रमागत mxl5007t_mode mode)
अणु
	काष्ठा mxl5007t_config *cfg = state->config;

	स_नकल(&state->tab_init, &init_tab, माप(init_tab));
	स_नकल(&state->tab_init_cable, &init_tab_cable, माप(init_tab_cable));

	mxl5007t_set_mode_bits(state, mode, cfg->अगर_dअगरf_out_level);
	mxl5007t_set_अगर_freq_bits(state, cfg->अगर_freq_hz, cfg->invert_अगर);
	mxl5007t_set_xtal_freq_bits(state, cfg->xtal_freq_hz);

	set_reg_bits(state->tab_init, 0x03, 0x08, cfg->clk_out_enable << 3);
	set_reg_bits(state->tab_init, 0x03, 0x07, cfg->clk_out_amp);

	अगर (mode >= MxL_MODE_CABLE) अणु
		copy_reg_bits(state->tab_init, state->tab_init_cable);
		वापस state->tab_init_cable;
	पूर्ण अन्यथा
		वापस state->tab_init;
पूर्ण

/* ------------------------------------------------------------------------- */

क्रमागत mxl5007t_bw_mhz अणु
	MxL_BW_6MHz = 6,
	MxL_BW_7MHz = 7,
	MxL_BW_8MHz = 8,
पूर्ण;

अटल व्योम mxl5007t_set_bw_bits(काष्ठा mxl5007t_state *state,
				 क्रमागत mxl5007t_bw_mhz bw)
अणु
	u8 val;

	चयन (bw) अणु
	हाल MxL_BW_6MHz:
		val = 0x15; /* set DIG_MODEINDEX, DIG_MODEINDEX_A,
			     * and DIG_MODEINDEX_CSF */
		अवरोध;
	हाल MxL_BW_7MHz:
		val = 0x2a;
		अवरोध;
	हाल MxL_BW_8MHz:
		val = 0x3f;
		अवरोध;
	शेष:
		mxl_fail(-EINVAL);
		वापस;
	पूर्ण
	set_reg_bits(state->tab_rftune, 0x0c, 0x3f, val);

	वापस;
पूर्ण

अटल काष्ठा
reg_pair_t *mxl5007t_calc_rf_tune_regs(काष्ठा mxl5007t_state *state,
				       u32 rf_freq, क्रमागत mxl5007t_bw_mhz bw)
अणु
	u32 dig_rf_freq = 0;
	u32 temp;
	u32 frac_भागider = 1000000;
	अचिन्हित पूर्णांक i;

	स_नकल(&state->tab_rftune, &reg_pair_rftune, माप(reg_pair_rftune));

	mxl5007t_set_bw_bits(state, bw);

	/* Convert RF frequency पूर्णांकo 16 bits =>
	 * 10 bit पूर्णांकeger (MHz) + 6 bit fraction */
	dig_rf_freq = rf_freq / MHz;

	temp = rf_freq % MHz;

	क्रम (i = 0; i < 6; i++) अणु
		dig_rf_freq <<= 1;
		frac_भागider /= 2;
		अगर (temp > frac_भागider) अणु
			temp -= frac_भागider;
			dig_rf_freq++;
		पूर्ण
	पूर्ण

	/* add to have shअगरt center poपूर्णांक by 7.8124 kHz */
	अगर (temp > 7812)
		dig_rf_freq++;

	set_reg_bits(state->tab_rftune, 0x0d, 0xff, (u8) dig_rf_freq);
	set_reg_bits(state->tab_rftune, 0x0e, 0xff, (u8) (dig_rf_freq >> 8));

	अगर (rf_freq >= 333000000)
		set_reg_bits(state->tab_rftune, 0x80, 0x40, 0x40);

	वापस state->tab_rftune;
पूर्ण

/* ------------------------------------------------------------------------- */

अटल पूर्णांक mxl5007t_ग_लिखो_reg(काष्ठा mxl5007t_state *state, u8 reg, u8 val)
अणु
	u8 buf[] = अणु reg, val पूर्ण;
	काष्ठा i2c_msg msg = अणु .addr = state->i2c_props.addr, .flags = 0,
			       .buf = buf, .len = 2 पूर्ण;
	पूर्णांक ret;

	ret = i2c_transfer(state->i2c_props.adap, &msg, 1);
	अगर (ret != 1) अणु
		mxl_err("failed!");
		वापस -EREMOTEIO;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक mxl5007t_ग_लिखो_regs(काष्ठा mxl5007t_state *state,
			       काष्ठा reg_pair_t *reg_pair)
अणु
	अचिन्हित पूर्णांक i = 0;
	पूर्णांक ret = 0;

	जबतक ((ret == 0) && (reg_pair[i].reg || reg_pair[i].val)) अणु
		ret = mxl5007t_ग_लिखो_reg(state,
					 reg_pair[i].reg, reg_pair[i].val);
		i++;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक mxl5007t_पढ़ो_reg(काष्ठा mxl5007t_state *state, u8 reg, u8 *val)
अणु
	u8 buf[2] = अणु 0xfb, reg पूर्ण;
	काष्ठा i2c_msg msg[] = अणु
		अणु .addr = state->i2c_props.addr, .flags = 0,
		  .buf = buf, .len = 2 पूर्ण,
		अणु .addr = state->i2c_props.addr, .flags = I2C_M_RD,
		  .buf = val, .len = 1 पूर्ण,
	पूर्ण;
	पूर्णांक ret;

	ret = i2c_transfer(state->i2c_props.adap, msg, 2);
	अगर (ret != 2) अणु
		mxl_err("failed!");
		वापस -EREMOTEIO;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक mxl5007t_soft_reset(काष्ठा mxl5007t_state *state)
अणु
	u8 d = 0xff;
	काष्ठा i2c_msg msg = अणु
		.addr = state->i2c_props.addr, .flags = 0,
		.buf = &d, .len = 1
	पूर्ण;
	पूर्णांक ret = i2c_transfer(state->i2c_props.adap, &msg, 1);

	अगर (ret != 1) अणु
		mxl_err("failed!");
		वापस -EREMOTEIO;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक mxl5007t_tuner_init(काष्ठा mxl5007t_state *state,
			       क्रमागत mxl5007t_mode mode)
अणु
	काष्ठा reg_pair_t *init_regs;
	पूर्णांक ret;

	/* calculate initialization reg array */
	init_regs = mxl5007t_calc_init_regs(state, mode);

	ret = mxl5007t_ग_लिखो_regs(state, init_regs);
	अगर (mxl_fail(ret))
		जाओ fail;
	mdelay(1);
fail:
	वापस ret;
पूर्ण

अटल पूर्णांक mxl5007t_tuner_rf_tune(काष्ठा mxl5007t_state *state, u32 rf_freq_hz,
				  क्रमागत mxl5007t_bw_mhz bw)
अणु
	काष्ठा reg_pair_t *rf_tune_regs;
	पूर्णांक ret;

	/* calculate channel change reg array */
	rf_tune_regs = mxl5007t_calc_rf_tune_regs(state, rf_freq_hz, bw);

	ret = mxl5007t_ग_लिखो_regs(state, rf_tune_regs);
	अगर (mxl_fail(ret))
		जाओ fail;
	msleep(3);
fail:
	वापस ret;
पूर्ण

/* ------------------------------------------------------------------------- */

अटल पूर्णांक mxl5007t_synth_lock_status(काष्ठा mxl5007t_state *state,
				      पूर्णांक *rf_locked, पूर्णांक *ref_locked)
अणु
	u8 d;
	पूर्णांक ret;

	*rf_locked = 0;
	*ref_locked = 0;

	ret = mxl5007t_पढ़ो_reg(state, 0xd8, &d);
	अगर (mxl_fail(ret))
		जाओ fail;

	अगर ((d & 0x0c) == 0x0c)
		*rf_locked = 1;

	अगर ((d & 0x03) == 0x03)
		*ref_locked = 1;
fail:
	वापस ret;
पूर्ण

/* ------------------------------------------------------------------------- */

अटल पूर्णांक mxl5007t_get_status(काष्ठा dvb_frontend *fe, u32 *status)
अणु
	काष्ठा mxl5007t_state *state = fe->tuner_priv;
	पूर्णांक rf_locked, ref_locked, ret;

	*status = 0;

	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1);

	ret = mxl5007t_synth_lock_status(state, &rf_locked, &ref_locked);
	अगर (mxl_fail(ret))
		जाओ fail;
	mxl_debug("%s%s", rf_locked ? "rf locked " : "",
		  ref_locked ? "ref locked" : "");

	अगर ((rf_locked) || (ref_locked))
		*status |= TUNER_STATUS_LOCKED;
fail:
	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 0);

	वापस ret;
पूर्ण

/* ------------------------------------------------------------------------- */

अटल पूर्णांक mxl5007t_set_params(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;
	u32 delsys = c->delivery_प्रणाली;
	काष्ठा mxl5007t_state *state = fe->tuner_priv;
	क्रमागत mxl5007t_bw_mhz bw;
	क्रमागत mxl5007t_mode mode;
	पूर्णांक ret;
	u32 freq = c->frequency;

	चयन (delsys) अणु
	हाल SYS_ATSC:
		mode = MxL_MODE_ATSC;
		bw = MxL_BW_6MHz;
		अवरोध;
	हाल SYS_DVBC_ANNEX_B:
		mode = MxL_MODE_CABLE;
		bw = MxL_BW_6MHz;
		अवरोध;
	हाल SYS_DVBT:
	हाल SYS_DVBT2:
		mode = MxL_MODE_DVBT;
		चयन (c->bandwidth_hz) अणु
		हाल 6000000:
			bw = MxL_BW_6MHz;
			अवरोध;
		हाल 7000000:
			bw = MxL_BW_7MHz;
			अवरोध;
		हाल 8000000:
			bw = MxL_BW_8MHz;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	शेष:
		mxl_err("modulation type not supported!");
		वापस -EINVAL;
	पूर्ण

	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1);

	mutex_lock(&state->lock);

	ret = mxl5007t_tuner_init(state, mode);
	अगर (mxl_fail(ret))
		जाओ fail;

	ret = mxl5007t_tuner_rf_tune(state, freq, bw);
	अगर (mxl_fail(ret))
		जाओ fail;

	state->frequency = freq;
	state->bandwidth = c->bandwidth_hz;
fail:
	mutex_unlock(&state->lock);

	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 0);

	वापस ret;
पूर्ण

/* ------------------------------------------------------------------------- */

अटल पूर्णांक mxl5007t_init(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा mxl5007t_state *state = fe->tuner_priv;
	पूर्णांक ret;

	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1);

	/* wake from standby */
	ret = mxl5007t_ग_लिखो_reg(state, 0x01, 0x01);
	mxl_fail(ret);

	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 0);

	वापस ret;
पूर्ण

अटल पूर्णांक mxl5007t_sleep(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा mxl5007t_state *state = fe->tuner_priv;
	पूर्णांक ret;

	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1);

	/* enter standby mode */
	ret = mxl5007t_ग_लिखो_reg(state, 0x01, 0x00);
	mxl_fail(ret);
	ret = mxl5007t_ग_लिखो_reg(state, 0x0f, 0x00);
	mxl_fail(ret);

	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 0);

	वापस ret;
पूर्ण

/* ------------------------------------------------------------------------- */

अटल पूर्णांक mxl5007t_get_frequency(काष्ठा dvb_frontend *fe, u32 *frequency)
अणु
	काष्ठा mxl5007t_state *state = fe->tuner_priv;
	*frequency = state->frequency;
	वापस 0;
पूर्ण

अटल पूर्णांक mxl5007t_get_bandwidth(काष्ठा dvb_frontend *fe, u32 *bandwidth)
अणु
	काष्ठा mxl5007t_state *state = fe->tuner_priv;
	*bandwidth = state->bandwidth;
	वापस 0;
पूर्ण

अटल पूर्णांक mxl5007t_get_अगर_frequency(काष्ठा dvb_frontend *fe, u32 *frequency)
अणु
	काष्ठा mxl5007t_state *state = fe->tuner_priv;

	*frequency = 0;

	चयन (state->अगर_freq) अणु
	हाल MxL_IF_4_MHZ:
		*frequency = 4000000;
		अवरोध;
	हाल MxL_IF_4_5_MHZ:
		*frequency = 4500000;
		अवरोध;
	हाल MxL_IF_4_57_MHZ:
		*frequency = 4570000;
		अवरोध;
	हाल MxL_IF_5_MHZ:
		*frequency = 5000000;
		अवरोध;
	हाल MxL_IF_5_38_MHZ:
		*frequency = 5380000;
		अवरोध;
	हाल MxL_IF_6_MHZ:
		*frequency = 6000000;
		अवरोध;
	हाल MxL_IF_6_28_MHZ:
		*frequency = 6280000;
		अवरोध;
	हाल MxL_IF_9_1915_MHZ:
		*frequency = 9191500;
		अवरोध;
	हाल MxL_IF_35_25_MHZ:
		*frequency = 35250000;
		अवरोध;
	हाल MxL_IF_36_15_MHZ:
		*frequency = 36150000;
		अवरोध;
	हाल MxL_IF_44_MHZ:
		*frequency = 44000000;
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम mxl5007t_release(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा mxl5007t_state *state = fe->tuner_priv;

	mutex_lock(&mxl5007t_list_mutex);

	अगर (state)
		hybrid_tuner_release_state(state);

	mutex_unlock(&mxl5007t_list_mutex);

	fe->tuner_priv = शून्य;
पूर्ण

/* ------------------------------------------------------------------------- */

अटल स्थिर काष्ठा dvb_tuner_ops mxl5007t_tuner_ops = अणु
	.info = अणु
		.name = "MaxLinear MxL5007T",
	पूर्ण,
	.init              = mxl5007t_init,
	.sleep             = mxl5007t_sleep,
	.set_params        = mxl5007t_set_params,
	.get_status        = mxl5007t_get_status,
	.get_frequency     = mxl5007t_get_frequency,
	.get_bandwidth     = mxl5007t_get_bandwidth,
	.release           = mxl5007t_release,
	.get_अगर_frequency  = mxl5007t_get_अगर_frequency,
पूर्ण;

अटल पूर्णांक mxl5007t_get_chip_id(काष्ठा mxl5007t_state *state)
अणु
	अक्षर *name;
	पूर्णांक ret;
	u8 id;

	ret = mxl5007t_पढ़ो_reg(state, 0xd9, &id);
	अगर (mxl_fail(ret))
		जाओ fail;

	चयन (id) अणु
	हाल MxL_5007_V1_F1:
		name = "MxL5007.v1.f1";
		अवरोध;
	हाल MxL_5007_V1_F2:
		name = "MxL5007.v1.f2";
		अवरोध;
	हाल MxL_5007_V2_100_F1:
		name = "MxL5007.v2.100.f1";
		अवरोध;
	हाल MxL_5007_V2_100_F2:
		name = "MxL5007.v2.100.f2";
		अवरोध;
	हाल MxL_5007_V2_200_F1:
		name = "MxL5007.v2.200.f1";
		अवरोध;
	हाल MxL_5007_V2_200_F2:
		name = "MxL5007.v2.200.f2";
		अवरोध;
	हाल MxL_5007_V4:
		name = "MxL5007T.v4";
		अवरोध;
	शेष:
		name = "MxL5007T";
		prपूर्णांकk(KERN_WARNING "%s: unknown rev (%02x)\n", __func__, id);
		id = MxL_UNKNOWN_ID;
	पूर्ण
	state->chip_id = id;
	mxl_info("%s detected @ %d-%04x", name,
		 i2c_adapter_id(state->i2c_props.adap),
		 state->i2c_props.addr);
	वापस 0;
fail:
	mxl_warn("unable to identify device @ %d-%04x",
		 i2c_adapter_id(state->i2c_props.adap),
		 state->i2c_props.addr);

	state->chip_id = MxL_UNKNOWN_ID;
	वापस ret;
पूर्ण

काष्ठा dvb_frontend *mxl5007t_attach(काष्ठा dvb_frontend *fe,
				     काष्ठा i2c_adapter *i2c, u8 addr,
				     काष्ठा mxl5007t_config *cfg)
अणु
	काष्ठा mxl5007t_state *state = शून्य;
	पूर्णांक instance, ret;

	mutex_lock(&mxl5007t_list_mutex);
	instance = hybrid_tuner_request_state(काष्ठा mxl5007t_state, state,
					      hybrid_tuner_instance_list,
					      i2c, addr, "mxl5007t");
	चयन (instance) अणु
	हाल 0:
		जाओ fail;
	हाल 1:
		/* new tuner instance */
		state->config = cfg;

		mutex_init(&state->lock);

		अगर (fe->ops.i2c_gate_ctrl)
			fe->ops.i2c_gate_ctrl(fe, 1);

		ret = mxl5007t_get_chip_id(state);

		अगर (fe->ops.i2c_gate_ctrl)
			fe->ops.i2c_gate_ctrl(fe, 0);

		/* check वापस value of mxl5007t_get_chip_id */
		अगर (mxl_fail(ret))
			जाओ fail;
		अवरोध;
	शेष:
		/* existing tuner instance */
		अवरोध;
	पूर्ण

	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1);

	ret = mxl5007t_soft_reset(state);

	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 0);

	अगर (mxl_fail(ret))
		जाओ fail;

	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1);

	ret = mxl5007t_ग_लिखो_reg(state, 0x04,
		state->config->loop_thru_enable);

	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 0);

	अगर (mxl_fail(ret))
		जाओ fail;

	fe->tuner_priv = state;

	mutex_unlock(&mxl5007t_list_mutex);

	स_नकल(&fe->ops.tuner_ops, &mxl5007t_tuner_ops,
	       माप(काष्ठा dvb_tuner_ops));

	वापस fe;
fail:
	mutex_unlock(&mxl5007t_list_mutex);

	mxl5007t_release(fe);
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(mxl5007t_attach);
MODULE_DESCRIPTION("MaxLinear MxL5007T Silicon IC tuner driver");
MODULE_AUTHOR("Michael Krufky <mkrufky@linuxtv.org>");
MODULE_LICENSE("GPL");
MODULE_VERSION("0.2");
