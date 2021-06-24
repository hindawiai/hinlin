<शैली गुरु>
/*
 * Copyright (C) 2009 Francisco Jerez.
 * All Rights Reserved.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining
 * a copy of this software and associated करोcumentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modअगरy, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to करो so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice (including the
 * next paragraph) shall be included in all copies or substantial
 * portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE COPYRIGHT OWNER(S) AND/OR ITS SUPPLIERS BE
 * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */

#अगर_अघोषित __DRM_I2C_CH7006_PRIV_H__
#घोषणा __DRM_I2C_CH7006_PRIV_H__

#समावेश <drm/drm_crtc_helper.h>
#समावेश <drm/drm_encoder_slave.h>
#समावेश <drm/drm_probe_helper.h>
#समावेश <drm/i2c/ch7006.h>

प्रकार पूर्णांक64_t fixed;
#घोषणा fixed1 (1LL << 32)

क्रमागत ch7006_tv_norm अणु
	TV_NORM_PAL,
	TV_NORM_PAL_M,
	TV_NORM_PAL_N,
	TV_NORM_PAL_NC,
	TV_NORM_PAL_60,
	TV_NORM_NTSC_M,
	TV_NORM_NTSC_J,
	NUM_TV_NORMS
पूर्ण;

काष्ठा ch7006_tv_norm_info अणु
	fixed vrefresh;
	पूर्णांक vdisplay;
	पूर्णांक vtotal;
	पूर्णांक hभव;

	fixed subc_freq;
	fixed black_level;

	uपूर्णांक32_t dispmode;
	पूर्णांक voffset;
पूर्ण;

काष्ठा ch7006_mode अणु
	काष्ठा drm_display_mode mode;

	पूर्णांक enc_hdisp;
	पूर्णांक enc_vdisp;

	fixed subc_coeff;
	uपूर्णांक32_t dispmode;

	uपूर्णांक32_t valid_scales;
	uपूर्णांक32_t valid_norms;
पूर्ण;

काष्ठा ch7006_state अणु
	uपूर्णांक8_t regs[0x26];
पूर्ण;

काष्ठा ch7006_priv अणु
	काष्ठा ch7006_encoder_params params;
	स्थिर काष्ठा ch7006_mode *mode;

	काष्ठा ch7006_state state;
	काष्ठा ch7006_state saved_state;

	काष्ठा drm_property *scale_property;

	पूर्णांक select_subconnector;
	पूर्णांक subconnector;
	पूर्णांक hmargin;
	पूर्णांक vmargin;
	क्रमागत ch7006_tv_norm norm;
	पूर्णांक brightness;
	पूर्णांक contrast;
	पूर्णांक flicker;
	पूर्णांक scale;

	पूर्णांक chip_version;
	पूर्णांक last_dpms;
पूर्ण;

#घोषणा to_ch7006_priv(x) \
	((काष्ठा ch7006_priv *)to_encoder_slave(x)->slave_priv)

बाह्य पूर्णांक ch7006_debug;
बाह्य अक्षर *ch7006_tv_norm;
बाह्य पूर्णांक ch7006_scale;

बाह्य स्थिर अक्षर * स्थिर ch7006_tv_norm_names[];
बाह्य स्थिर काष्ठा ch7006_tv_norm_info ch7006_tv_norms[];
बाह्य स्थिर काष्ठा ch7006_mode ch7006_modes[];

स्थिर काष्ठा ch7006_mode *ch7006_lookup_mode(काष्ठा drm_encoder *encoder,
					     स्थिर काष्ठा drm_display_mode *drm_mode);

व्योम ch7006_setup_levels(काष्ठा drm_encoder *encoder);
व्योम ch7006_setup_subcarrier(काष्ठा drm_encoder *encoder);
व्योम ch7006_setup_pll(काष्ठा drm_encoder *encoder);
व्योम ch7006_setup_घातer_state(काष्ठा drm_encoder *encoder);
व्योम ch7006_setup_properties(काष्ठा drm_encoder *encoder);

व्योम ch7006_ग_लिखो(काष्ठा i2c_client *client, uपूर्णांक8_t addr, uपूर्णांक8_t val);
uपूर्णांक8_t ch7006_पढ़ो(काष्ठा i2c_client *client, uपूर्णांक8_t addr);

व्योम ch7006_state_load(काष्ठा i2c_client *client,
		       काष्ठा ch7006_state *state);
व्योम ch7006_state_save(काष्ठा i2c_client *client,
		       काष्ठा ch7006_state *state);

/* Some helper macros */

#घोषणा ch7006_dbg(client, क्रमmat, ...) करो अणु				\
		अगर (ch7006_debug)					\
			dev_prपूर्णांकk(KERN_DEBUG, &client->dev,		\
				   "%s: " क्रमmat, __func__, ## __VA_ARGS__); \
	पूर्ण जबतक (0)
#घोषणा ch7006_info(client, क्रमmat, ...) \
				dev_info(&client->dev, क्रमmat, __VA_ARGS__)
#घोषणा ch7006_err(client, क्रमmat, ...) \
				dev_err(&client->dev, क्रमmat, __VA_ARGS__)

#घोषणा __mask(src, bitfield) \
		(((2 << (1 ? bitfield)) - 1) & ~((1 << (0 ? bitfield)) - 1))
#घोषणा mask(bitfield) __mask(bitfield)

#घोषणा __bitf(src, bitfield, x) \
		(((x) >> (src) << (0 ? bitfield)) &  __mask(src, bitfield))
#घोषणा bitf(bitfield, x) __bitf(bitfield, x)
#घोषणा bitfs(bitfield, s) __bitf(bitfield, bitfield##_##s)
#घोषणा setbitf(state, reg, bitfield, x)				\
	state->regs[reg] = (state->regs[reg] & ~mask(reg##_##bitfield))	\
		| bitf(reg##_##bitfield, x)

#घोषणा __unbitf(src, bitfield, x) \
		((x & __mask(src, bitfield)) >> (0 ? bitfield) << (src))
#घोषणा unbitf(bitfield, x) __unbitf(bitfield, x)

अटल अंतरभूत पूर्णांक पूर्णांकerpolate(पूर्णांक y0, पूर्णांक y1, पूर्णांक y2, पूर्णांक x)
अणु
	वापस y1 + (x < 50 ? y1 - y0 : y2 - y1) * (x - 50) / 50;
पूर्ण

अटल अंतरभूत पूर्णांक32_t round_fixed(fixed x)
अणु
	वापस (x + fixed1/2) >> 32;
पूर्ण

#घोषणा ch7006_load_reg(client, state, reg) ch7006_ग_लिखो(client, reg, state->regs[reg])
#घोषणा ch7006_save_reg(client, state, reg) state->regs[reg] = ch7006_पढ़ो(client, reg)

/* Fixed hardware specs */

#घोषणा CH7006_FREQ0				14318
#घोषणा CH7006_MAXN				650
#घोषणा CH7006_MAXM				315

/* Register definitions */

#घोषणा CH7006_DISPMODE				0x00
#घोषणा CH7006_DISPMODE_INPUT_RES		0, 7:5
#घोषणा CH7006_DISPMODE_INPUT_RES_512x384	0x0
#घोषणा CH7006_DISPMODE_INPUT_RES_720x400	0x1
#घोषणा CH7006_DISPMODE_INPUT_RES_640x400	0x2
#घोषणा CH7006_DISPMODE_INPUT_RES_640x480	0x3
#घोषणा CH7006_DISPMODE_INPUT_RES_800x600	0x4
#घोषणा CH7006_DISPMODE_INPUT_RES_NATIVE	0x5
#घोषणा CH7006_DISPMODE_OUTPUT_STD		0, 4:3
#घोषणा CH7006_DISPMODE_OUTPUT_STD_PAL		0x0
#घोषणा CH7006_DISPMODE_OUTPUT_STD_NTSC		0x1
#घोषणा CH7006_DISPMODE_OUTPUT_STD_PAL_M	0x2
#घोषणा CH7006_DISPMODE_OUTPUT_STD_NTSC_J	0x3
#घोषणा CH7006_DISPMODE_SCALING_RATIO		0, 2:0
#घोषणा CH7006_DISPMODE_SCALING_RATIO_5_4	0x0
#घोषणा CH7006_DISPMODE_SCALING_RATIO_1_1	0x1
#घोषणा CH7006_DISPMODE_SCALING_RATIO_7_8	0x2
#घोषणा CH7006_DISPMODE_SCALING_RATIO_5_6	0x3
#घोषणा CH7006_DISPMODE_SCALING_RATIO_3_4	0x4
#घोषणा CH7006_DISPMODE_SCALING_RATIO_7_10	0x5

#घोषणा CH7006_FFILTER				0x01
#घोषणा CH7006_FFILTER_TEXT			0, 5:4
#घोषणा CH7006_FFILTER_LUMA			0, 3:2
#घोषणा CH7006_FFILTER_CHROMA			0, 1:0
#घोषणा CH7006_FFILTER_CHROMA_NO_DCRAWL		0x3

#घोषणा CH7006_BWIDTH				0x03
#घोषणा CH7006_BWIDTH_5L_FखाताR			(1 << 7)
#घोषणा CH7006_BWIDTH_CVBS_NO_CHROMA		(1 << 6)
#घोषणा CH7006_BWIDTH_CHROMA			0, 5:4
#घोषणा CH7006_BWIDTH_SVIDEO_YPEAK		(1 << 3)
#घोषणा CH7006_BWIDTH_SVIDEO_LUMA		0, 2:1
#घोषणा CH7006_BWIDTH_CVBS_LUMA			0, 0:0

#घोषणा CH7006_INPUT_FORMAT			0x04
#घोषणा CH7006_INPUT_FORMAT_DAC_GAIN		(1 << 6)
#घोषणा CH7006_INPUT_FORMAT_RGB_PASS_THROUGH	(1 << 5)
#घोषणा CH7006_INPUT_FORMAT_FORMAT		0, 3:0
#घोषणा CH7006_INPUT_FORMAT_FORMAT_RGB16	0x0
#घोषणा CH7006_INPUT_FORMAT_FORMAT_YCrCb24m16	0x1
#घोषणा CH7006_INPUT_FORMAT_FORMAT_RGB24m16	0x2
#घोषणा CH7006_INPUT_FORMAT_FORMAT_RGB15	0x3
#घोषणा CH7006_INPUT_FORMAT_FORMAT_RGB24m12C	0x4
#घोषणा CH7006_INPUT_FORMAT_FORMAT_RGB24m12I	0x5
#घोषणा CH7006_INPUT_FORMAT_FORMAT_RGB24m8	0x6
#घोषणा CH7006_INPUT_FORMAT_FORMAT_RGB16m8	0x7
#घोषणा CH7006_INPUT_FORMAT_FORMAT_RGB15m8	0x8
#घोषणा CH7006_INPUT_FORMAT_FORMAT_YCrCb24m8	0x9

#घोषणा CH7006_CLKMODE				0x06
#घोषणा CH7006_CLKMODE_SUBC_LOCK		(1 << 7)
#घोषणा CH7006_CLKMODE_MASTER			(1 << 6)
#घोषणा CH7006_CLKMODE_POS_EDGE			(1 << 4)
#घोषणा CH7006_CLKMODE_XCM			0, 3:2
#घोषणा CH7006_CLKMODE_PCM			0, 1:0

#घोषणा CH7006_START_ACTIVE			0x07
#घोषणा CH7006_START_ACTIVE_0			0, 7:0

#घोषणा CH7006_POV				0x08
#घोषणा CH7006_POV_START_ACTIVE_8		8, 2:2
#घोषणा CH7006_POV_HPOS_8			8, 1:1
#घोषणा CH7006_POV_VPOS_8			8, 0:0

#घोषणा CH7006_BLACK_LEVEL			0x09
#घोषणा CH7006_BLACK_LEVEL_0			0, 7:0

#घोषणा CH7006_HPOS				0x0a
#घोषणा CH7006_HPOS_0				0, 7:0

#घोषणा CH7006_VPOS				0x0b
#घोषणा CH7006_VPOS_0				0, 7:0

#घोषणा CH7006_INPUT_SYNC			0x0d
#घोषणा CH7006_INPUT_SYNC_EMBEDDED		(1 << 3)
#घोषणा CH7006_INPUT_SYNC_OUTPUT		(1 << 2)
#घोषणा CH7006_INPUT_SYNC_PVSYNC		(1 << 1)
#घोषणा CH7006_INPUT_SYNC_PHSYNC		(1 << 0)

#घोषणा CH7006_POWER				0x0e
#घोषणा CH7006_POWER_SCART			(1 << 4)
#घोषणा CH7006_POWER_RESET			(1 << 3)
#घोषणा CH7006_POWER_LEVEL			0, 2:0
#घोषणा CH7006_POWER_LEVEL_CVBS_OFF		0x0
#घोषणा CH7006_POWER_LEVEL_POWER_OFF		0x1
#घोषणा CH7006_POWER_LEVEL_SVIDEO_OFF		0x2
#घोषणा CH7006_POWER_LEVEL_NORMAL		0x3
#घोषणा CH7006_POWER_LEVEL_FULL_POWER_OFF	0x4

#घोषणा CH7006_DETECT				0x10
#घोषणा CH7006_DETECT_SVIDEO_Y_TEST		(1 << 3)
#घोषणा CH7006_DETECT_SVIDEO_C_TEST		(1 << 2)
#घोषणा CH7006_DETECT_CVBS_TEST			(1 << 1)
#घोषणा CH7006_DETECT_SENSE			(1 << 0)

#घोषणा CH7006_CONTRAST				0x11
#घोषणा CH7006_CONTRAST_0			0, 2:0

#घोषणा CH7006_PLLOV	 			0x13
#घोषणा CH7006_PLLOV_N_8	 		8, 2:1
#घोषणा CH7006_PLLOV_M_8	 		8, 0:0

#घोषणा CH7006_PLLM	 			0x14
#घोषणा CH7006_PLLM_0	 			0, 7:0

#घोषणा CH7006_PLLN	 			0x15
#घोषणा CH7006_PLLN_0	 			0, 7:0

#घोषणा CH7006_BCLKOUT	 			0x17

#घोषणा CH7006_SUBC_INC0			0x18
#घोषणा CH7006_SUBC_INC0_28			28, 3:0

#घोषणा CH7006_SUBC_INC1			0x19
#घोषणा CH7006_SUBC_INC1_24			24, 3:0

#घोषणा CH7006_SUBC_INC2			0x1a
#घोषणा CH7006_SUBC_INC2_20			20, 3:0

#घोषणा CH7006_SUBC_INC3			0x1b
#घोषणा CH7006_SUBC_INC3_GPIO1_VAL		(1 << 7)
#घोषणा CH7006_SUBC_INC3_GPIO0_VAL		(1 << 6)
#घोषणा CH7006_SUBC_INC3_POUT_3_3V		(1 << 5)
#घोषणा CH7006_SUBC_INC3_POUT_INV		(1 << 4)
#घोषणा CH7006_SUBC_INC3_16			16, 3:0

#घोषणा CH7006_SUBC_INC4			0x1c
#घोषणा CH7006_SUBC_INC4_GPIO1_IN		(1 << 7)
#घोषणा CH7006_SUBC_INC4_GPIO0_IN		(1 << 6)
#घोषणा CH7006_SUBC_INC4_DS_INPUT		(1 << 4)
#घोषणा CH7006_SUBC_INC4_12			12, 3:0

#घोषणा CH7006_SUBC_INC5			0x1d
#घोषणा CH7006_SUBC_INC5_8			8, 3:0

#घोषणा CH7006_SUBC_INC6			0x1e
#घोषणा CH7006_SUBC_INC6_4			4, 3:0

#घोषणा CH7006_SUBC_INC7			0x1f
#घोषणा CH7006_SUBC_INC7_0			0, 3:0

#घोषणा CH7006_PLL_CONTROL			0x20
#घोषणा CH7006_PLL_CONTROL_CPI			(1 << 5)
#घोषणा CH7006_PLL_CONTROL_CAPACITOR		(1 << 4)
#घोषणा CH7006_PLL_CONTROL_7STAGES		(1 << 3)
#घोषणा CH7006_PLL_CONTROL_DIGITAL_5V		(1 << 2)
#घोषणा CH7006_PLL_CONTROL_ANALOG_5V		(1 << 1)
#घोषणा CH7006_PLL_CONTROL_MEMORY_5V		(1 << 0)

#घोषणा CH7006_CALC_SUBC_INC0			0x21
#घोषणा CH7006_CALC_SUBC_INC0_24		24, 4:3
#घोषणा CH7006_CALC_SUBC_INC0_HYST		0, 2:1
#घोषणा CH7006_CALC_SUBC_INC0_AUTO		(1 << 0)

#घोषणा CH7006_CALC_SUBC_INC1			0x22
#घोषणा CH7006_CALC_SUBC_INC1_16		16, 7:0

#घोषणा CH7006_CALC_SUBC_INC2			0x23
#घोषणा CH7006_CALC_SUBC_INC2_8			8, 7:0

#घोषणा CH7006_CALC_SUBC_INC3			0x24
#घोषणा CH7006_CALC_SUBC_INC3_0			0, 7:0

#घोषणा CH7006_VERSION_ID			0x25

#पूर्ण_अगर
