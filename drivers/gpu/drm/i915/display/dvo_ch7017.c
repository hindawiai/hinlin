<शैली गुरु>
/*
 * Copyright तऊ 2006 Intel Corporation
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 * Authors:
 *    Eric Anholt <eric@anholt.net>
 *
 */

#समावेश "intel_display_types.h"
#समावेश "intel_dvo_dev.h"

#घोषणा CH7017_TV_DISPLAY_MODE		0x00
#घोषणा CH7017_FLICKER_FILTER		0x01
#घोषणा CH7017_VIDEO_BANDWIDTH		0x02
#घोषणा CH7017_TEXT_ENHANCEMENT		0x03
#घोषणा CH7017_START_ACTIVE_VIDEO	0x04
#घोषणा CH7017_HORIZONTAL_POSITION	0x05
#घोषणा CH7017_VERTICAL_POSITION	0x06
#घोषणा CH7017_BLACK_LEVEL		0x07
#घोषणा CH7017_CONTRAST_ENHANCEMENT	0x08
#घोषणा CH7017_TV_PLL			0x09
#घोषणा CH7017_TV_PLL_M			0x0a
#घोषणा CH7017_TV_PLL_N			0x0b
#घोषणा CH7017_SUB_CARRIER_0		0x0c
#घोषणा CH7017_CIV_CONTROL		0x10
#घोषणा CH7017_CIV_0			0x11
#घोषणा CH7017_CHROMA_BOOST		0x14
#घोषणा CH7017_CLOCK_MODE		0x1c
#घोषणा CH7017_INPUT_CLOCK		0x1d
#घोषणा CH7017_GPIO_CONTROL		0x1e
#घोषणा CH7017_INPUT_DATA_FORMAT	0x1f
#घोषणा CH7017_CONNECTION_DETECT	0x20
#घोषणा CH7017_DAC_CONTROL		0x21
#घोषणा CH7017_BUFFERED_CLOCK_OUTPUT	0x22
#घोषणा CH7017_DEFEAT_VSYNC		0x47
#घोषणा CH7017_TEST_PATTERN		0x48

#घोषणा CH7017_POWER_MANAGEMENT		0x49
/** Enables the TV output path. */
#घोषणा CH7017_TV_EN			(1 << 0)
#घोषणा CH7017_DAC0_POWER_DOWN		(1 << 1)
#घोषणा CH7017_DAC1_POWER_DOWN		(1 << 2)
#घोषणा CH7017_DAC2_POWER_DOWN		(1 << 3)
#घोषणा CH7017_DAC3_POWER_DOWN		(1 << 4)
/** Powers करोwn the TV out block, and DAC0-3 */
#घोषणा CH7017_TV_POWER_DOWN_EN		(1 << 5)

#घोषणा CH7017_VERSION_ID		0x4a

#घोषणा CH7017_DEVICE_ID		0x4b
#घोषणा CH7017_DEVICE_ID_VALUE		0x1b
#घोषणा CH7018_DEVICE_ID_VALUE		0x1a
#घोषणा CH7019_DEVICE_ID_VALUE		0x19

#घोषणा CH7017_XCLK_D2_ADJUST		0x53
#घोषणा CH7017_UP_SCALER_COEFF_0	0x55
#घोषणा CH7017_UP_SCALER_COEFF_1	0x56
#घोषणा CH7017_UP_SCALER_COEFF_2	0x57
#घोषणा CH7017_UP_SCALER_COEFF_3	0x58
#घोषणा CH7017_UP_SCALER_COEFF_4	0x59
#घोषणा CH7017_UP_SCALER_VERTICAL_INC_0	0x5a
#घोषणा CH7017_UP_SCALER_VERTICAL_INC_1	0x5b
#घोषणा CH7017_GPIO_INVERT		0x5c
#घोषणा CH7017_UP_SCALER_HORIZONTAL_INC_0	0x5d
#घोषणा CH7017_UP_SCALER_HORIZONTAL_INC_1	0x5e

#घोषणा CH7017_HORIZONTAL_ACTIVE_PIXEL_INPUT	0x5f
/**< Low bits of horizontal active pixel input */

#घोषणा CH7017_ACTIVE_INPUT_LINE_OUTPUT	0x60
/** High bits of horizontal active pixel input */
#घोषणा CH7017_LVDS_HAP_INPUT_MASK	(0x7 << 0)
/** High bits of vertical active line output */
#घोषणा CH7017_LVDS_VAL_HIGH_MASK	(0x7 << 3)

#घोषणा CH7017_VERTICAL_ACTIVE_LINE_OUTPUT	0x61
/**< Low bits of vertical active line output */

#घोषणा CH7017_HORIZONTAL_ACTIVE_PIXEL_OUTPUT	0x62
/**< Low bits of horizontal active pixel output */

#घोषणा CH7017_LVDS_POWER_DOWN		0x63
/** High bits of horizontal active pixel output */
#घोषणा CH7017_LVDS_HAP_HIGH_MASK	(0x7 << 0)
/** Enables the LVDS घातer करोwn state transition */
#घोषणा CH7017_LVDS_POWER_DOWN_EN	(1 << 6)
/** Enables the LVDS upscaler */
#घोषणा CH7017_LVDS_UPSCALER_EN		(1 << 7)
#घोषणा CH7017_LVDS_POWER_DOWN_DEFAULT_RESERVED 0x08

#घोषणा CH7017_LVDS_ENCODING		0x64
#घोषणा CH7017_LVDS_DITHER_2D		(1 << 2)
#घोषणा CH7017_LVDS_DITHER_DIS		(1 << 3)
#घोषणा CH7017_LVDS_DUAL_CHANNEL_EN	(1 << 4)
#घोषणा CH7017_LVDS_24_BIT		(1 << 5)

#घोषणा CH7017_LVDS_ENCODING_2		0x65

#घोषणा CH7017_LVDS_PLL_CONTROL		0x66
/** Enables the LVDS panel output path */
#घोषणा CH7017_LVDS_PANEN		(1 << 0)
/** Enables the LVDS panel backlight */
#घोषणा CH7017_LVDS_BKLEN		(1 << 3)

#घोषणा CH7017_POWER_SEQUENCING_T1	0x67
#घोषणा CH7017_POWER_SEQUENCING_T2	0x68
#घोषणा CH7017_POWER_SEQUENCING_T3	0x69
#घोषणा CH7017_POWER_SEQUENCING_T4	0x6a
#घोषणा CH7017_POWER_SEQUENCING_T5	0x6b
#घोषणा CH7017_GPIO_DRIVER_TYPE		0x6c
#घोषणा CH7017_GPIO_DATA		0x6d
#घोषणा CH7017_GPIO_सूचीECTION_CONTROL	0x6e

#घोषणा CH7017_LVDS_PLL_FEEDBACK_DIV	0x71
# define CH7017_LVDS_PLL_FEED_BACK_DIVIDER_SHIFT 4
# define CH7017_LVDS_PLL_FEED_FORWARD_DIVIDER_SHIFT 0
# define CH7017_LVDS_PLL_FEEDBACK_DEFAULT_RESERVED 0x80

#घोषणा CH7017_LVDS_PLL_VCO_CONTROL	0x72
# define CH7017_LVDS_PLL_VCO_DEFAULT_RESERVED 0x80
# define CH7017_LVDS_PLL_VCO_SHIFT	4
# define CH7017_LVDS_PLL_POST_SCALE_DIV_SHIFT 0

#घोषणा CH7017_OUTPUTS_ENABLE		0x73
# define CH7017_CHARGE_PUMP_LOW		0x0
# define CH7017_CHARGE_PUMP_HIGH	0x3
# define CH7017_LVDS_CHANNEL_A		(1 << 3)
# define CH7017_LVDS_CHANNEL_B		(1 << 4)
# define CH7017_TV_DAC_A		(1 << 5)
# define CH7017_TV_DAC_B		(1 << 6)
# define CH7017_DDC_SELECT_DC2		(1 << 7)

#घोषणा CH7017_LVDS_OUTPUT_AMPLITUDE	0x74
#घोषणा CH7017_LVDS_PLL_EMI_REDUCTION	0x75
#घोषणा CH7017_LVDS_POWER_DOWN_FLICKER	0x76

#घोषणा CH7017_LVDS_CONTROL_2		0x78
# define CH7017_LOOP_FILTER_SHIFT	5
# define CH7017_PHASE_DETECTOR_SHIFT	0

#घोषणा CH7017_BANG_LIMIT_CONTROL	0x7f

काष्ठा ch7017_priv अणु
	u8 dummy;
पूर्ण;

अटल व्योम ch7017_dump_regs(काष्ठा पूर्णांकel_dvo_device *dvo);
अटल व्योम ch7017_dpms(काष्ठा पूर्णांकel_dvo_device *dvo, bool enable);

अटल bool ch7017_पढ़ो(काष्ठा पूर्णांकel_dvo_device *dvo, u8 addr, u8 *val)
अणु
	काष्ठा i2c_msg msgs[] = अणु
		अणु
			.addr = dvo->slave_addr,
			.flags = 0,
			.len = 1,
			.buf = &addr,
		पूर्ण,
		अणु
			.addr = dvo->slave_addr,
			.flags = I2C_M_RD,
			.len = 1,
			.buf = val,
		पूर्ण
	पूर्ण;
	वापस i2c_transfer(dvo->i2c_bus, msgs, 2) == 2;
पूर्ण

अटल bool ch7017_ग_लिखो(काष्ठा पूर्णांकel_dvo_device *dvo, u8 addr, u8 val)
अणु
	u8 buf[2] = अणु addr, val पूर्ण;
	काष्ठा i2c_msg msg = अणु
		.addr = dvo->slave_addr,
		.flags = 0,
		.len = 2,
		.buf = buf,
	पूर्ण;
	वापस i2c_transfer(dvo->i2c_bus, &msg, 1) == 1;
पूर्ण

/** Probes क्रम a CH7017 on the given bus and slave address. */
अटल bool ch7017_init(काष्ठा पूर्णांकel_dvo_device *dvo,
			काष्ठा i2c_adapter *adapter)
अणु
	काष्ठा ch7017_priv *priv;
	स्थिर अक्षर *str;
	u8 val;

	priv = kzalloc(माप(काष्ठा ch7017_priv), GFP_KERNEL);
	अगर (priv == शून्य)
		वापस false;

	dvo->i2c_bus = adapter;
	dvo->dev_priv = priv;

	अगर (!ch7017_पढ़ो(dvo, CH7017_DEVICE_ID, &val))
		जाओ fail;

	चयन (val) अणु
	हाल CH7017_DEVICE_ID_VALUE:
		str = "ch7017";
		अवरोध;
	हाल CH7018_DEVICE_ID_VALUE:
		str = "ch7018";
		अवरोध;
	हाल CH7019_DEVICE_ID_VALUE:
		str = "ch7019";
		अवरोध;
	शेष:
		DRM_DEBUG_KMS("ch701x not detected, got %d: from %s "
			      "slave %d.\n",
			      val, adapter->name, dvo->slave_addr);
		जाओ fail;
	पूर्ण

	DRM_DEBUG_KMS("%s detected on %s, addr %d\n",
		      str, adapter->name, dvo->slave_addr);
	वापस true;

fail:
	kमुक्त(priv);
	वापस false;
पूर्ण

अटल क्रमागत drm_connector_status ch7017_detect(काष्ठा पूर्णांकel_dvo_device *dvo)
अणु
	वापस connector_status_connected;
पूर्ण

अटल क्रमागत drm_mode_status ch7017_mode_valid(काष्ठा पूर्णांकel_dvo_device *dvo,
					      काष्ठा drm_display_mode *mode)
अणु
	अगर (mode->घड़ी > 160000)
		वापस MODE_CLOCK_HIGH;

	वापस MODE_OK;
पूर्ण

अटल व्योम ch7017_mode_set(काष्ठा पूर्णांकel_dvo_device *dvo,
			    स्थिर काष्ठा drm_display_mode *mode,
			    स्थिर काष्ठा drm_display_mode *adjusted_mode)
अणु
	u8 lvds_pll_feedback_भाग, lvds_pll_vco_control;
	u8 outमाला_दो_enable, lvds_control_2, lvds_घातer_करोwn;
	u8 horizontal_active_pixel_input;
	u8 horizontal_active_pixel_output, vertical_active_line_output;
	u8 active_input_line_output;

	DRM_DEBUG_KMS("Registers before mode setting\n");
	ch7017_dump_regs(dvo);

	/* LVDS PLL settings from page 75 of 7017-7017ds.pdf*/
	अगर (mode->घड़ी < 100000) अणु
		outमाला_दो_enable = CH7017_LVDS_CHANNEL_A | CH7017_CHARGE_PUMP_LOW;
		lvds_pll_feedback_भाग = CH7017_LVDS_PLL_FEEDBACK_DEFAULT_RESERVED |
			(2 << CH7017_LVDS_PLL_FEED_BACK_DIVIDER_SHIFT) |
			(13 << CH7017_LVDS_PLL_FEED_FORWARD_DIVIDER_SHIFT);
		lvds_pll_vco_control = CH7017_LVDS_PLL_VCO_DEFAULT_RESERVED |
			(2 << CH7017_LVDS_PLL_VCO_SHIFT) |
			(3 << CH7017_LVDS_PLL_POST_SCALE_DIV_SHIFT);
		lvds_control_2 = (1 << CH7017_LOOP_FILTER_SHIFT) |
			(0 << CH7017_PHASE_DETECTOR_SHIFT);
	पूर्ण अन्यथा अणु
		outमाला_दो_enable = CH7017_LVDS_CHANNEL_A | CH7017_CHARGE_PUMP_HIGH;
		lvds_pll_feedback_भाग =
			CH7017_LVDS_PLL_FEEDBACK_DEFAULT_RESERVED |
			(2 << CH7017_LVDS_PLL_FEED_BACK_DIVIDER_SHIFT) |
			(3 << CH7017_LVDS_PLL_FEED_FORWARD_DIVIDER_SHIFT);
		lvds_control_2 = (3 << CH7017_LOOP_FILTER_SHIFT) |
			(0 << CH7017_PHASE_DETECTOR_SHIFT);
		अगर (1) अणु /* XXX: dual channel panel detection.  Assume yes क्रम now. */
			outमाला_दो_enable |= CH7017_LVDS_CHANNEL_B;
			lvds_pll_vco_control = CH7017_LVDS_PLL_VCO_DEFAULT_RESERVED |
				(2 << CH7017_LVDS_PLL_VCO_SHIFT) |
				(13 << CH7017_LVDS_PLL_POST_SCALE_DIV_SHIFT);
		पूर्ण अन्यथा अणु
			lvds_pll_vco_control = CH7017_LVDS_PLL_VCO_DEFAULT_RESERVED |
				(1 << CH7017_LVDS_PLL_VCO_SHIFT) |
				(13 << CH7017_LVDS_PLL_POST_SCALE_DIV_SHIFT);
		पूर्ण
	पूर्ण

	horizontal_active_pixel_input = mode->hdisplay & 0x00ff;

	vertical_active_line_output = mode->vdisplay & 0x00ff;
	horizontal_active_pixel_output = mode->hdisplay & 0x00ff;

	active_input_line_output = ((mode->hdisplay & 0x0700) >> 8) |
				   (((mode->vdisplay & 0x0700) >> 8) << 3);

	lvds_घातer_करोwn = CH7017_LVDS_POWER_DOWN_DEFAULT_RESERVED |
			  (mode->hdisplay & 0x0700) >> 8;

	ch7017_dpms(dvo, false);
	ch7017_ग_लिखो(dvo, CH7017_HORIZONTAL_ACTIVE_PIXEL_INPUT,
			horizontal_active_pixel_input);
	ch7017_ग_लिखो(dvo, CH7017_HORIZONTAL_ACTIVE_PIXEL_OUTPUT,
			horizontal_active_pixel_output);
	ch7017_ग_लिखो(dvo, CH7017_VERTICAL_ACTIVE_LINE_OUTPUT,
			vertical_active_line_output);
	ch7017_ग_लिखो(dvo, CH7017_ACTIVE_INPUT_LINE_OUTPUT,
			active_input_line_output);
	ch7017_ग_लिखो(dvo, CH7017_LVDS_PLL_VCO_CONTROL, lvds_pll_vco_control);
	ch7017_ग_लिखो(dvo, CH7017_LVDS_PLL_FEEDBACK_DIV, lvds_pll_feedback_भाग);
	ch7017_ग_लिखो(dvo, CH7017_LVDS_CONTROL_2, lvds_control_2);
	ch7017_ग_लिखो(dvo, CH7017_OUTPUTS_ENABLE, outमाला_दो_enable);

	/* Turn the LVDS back on with new settings. */
	ch7017_ग_लिखो(dvo, CH7017_LVDS_POWER_DOWN, lvds_घातer_करोwn);

	DRM_DEBUG_KMS("Registers after mode setting\n");
	ch7017_dump_regs(dvo);
पूर्ण

/* set the CH7017 घातer state */
अटल व्योम ch7017_dpms(काष्ठा पूर्णांकel_dvo_device *dvo, bool enable)
अणु
	u8 val;

	ch7017_पढ़ो(dvo, CH7017_LVDS_POWER_DOWN, &val);

	/* Turn off TV/VGA, and never turn it on since we करोn't support it. */
	ch7017_ग_लिखो(dvo, CH7017_POWER_MANAGEMENT,
			CH7017_DAC0_POWER_DOWN |
			CH7017_DAC1_POWER_DOWN |
			CH7017_DAC2_POWER_DOWN |
			CH7017_DAC3_POWER_DOWN |
			CH7017_TV_POWER_DOWN_EN);

	अगर (enable) अणु
		/* Turn on the LVDS */
		ch7017_ग_लिखो(dvo, CH7017_LVDS_POWER_DOWN,
			     val & ~CH7017_LVDS_POWER_DOWN_EN);
	पूर्ण अन्यथा अणु
		/* Turn off the LVDS */
		ch7017_ग_लिखो(dvo, CH7017_LVDS_POWER_DOWN,
			     val | CH7017_LVDS_POWER_DOWN_EN);
	पूर्ण

	/* XXX: Should actually रुको क्रम update घातer status somehow */
	msleep(20);
पूर्ण

अटल bool ch7017_get_hw_state(काष्ठा पूर्णांकel_dvo_device *dvo)
अणु
	u8 val;

	ch7017_पढ़ो(dvo, CH7017_LVDS_POWER_DOWN, &val);

	अगर (val & CH7017_LVDS_POWER_DOWN_EN)
		वापस false;
	अन्यथा
		वापस true;
पूर्ण

अटल व्योम ch7017_dump_regs(काष्ठा पूर्णांकel_dvo_device *dvo)
अणु
	u8 val;

#घोषणा DUMP(reg)					\
करो अणु							\
	ch7017_पढ़ो(dvo, reg, &val);			\
	DRM_DEBUG_KMS(#reg ": %02x\n", val);		\
पूर्ण जबतक (0)

	DUMP(CH7017_HORIZONTAL_ACTIVE_PIXEL_INPUT);
	DUMP(CH7017_HORIZONTAL_ACTIVE_PIXEL_OUTPUT);
	DUMP(CH7017_VERTICAL_ACTIVE_LINE_OUTPUT);
	DUMP(CH7017_ACTIVE_INPUT_LINE_OUTPUT);
	DUMP(CH7017_LVDS_PLL_VCO_CONTROL);
	DUMP(CH7017_LVDS_PLL_FEEDBACK_DIV);
	DUMP(CH7017_LVDS_CONTROL_2);
	DUMP(CH7017_OUTPUTS_ENABLE);
	DUMP(CH7017_LVDS_POWER_DOWN);
पूर्ण

अटल व्योम ch7017_destroy(काष्ठा पूर्णांकel_dvo_device *dvo)
अणु
	काष्ठा ch7017_priv *priv = dvo->dev_priv;

	अगर (priv) अणु
		kमुक्त(priv);
		dvo->dev_priv = शून्य;
	पूर्ण
पूर्ण

स्थिर काष्ठा पूर्णांकel_dvo_dev_ops ch7017_ops = अणु
	.init = ch7017_init,
	.detect = ch7017_detect,
	.mode_valid = ch7017_mode_valid,
	.mode_set = ch7017_mode_set,
	.dpms = ch7017_dpms,
	.get_hw_state = ch7017_get_hw_state,
	.dump_regs = ch7017_dump_regs,
	.destroy = ch7017_destroy,
पूर्ण;
