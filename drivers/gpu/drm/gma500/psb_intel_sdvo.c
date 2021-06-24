<शैली गुरु>
/*
 * Copyright 2006 Dave Airlie <airlied@linux.ie>
 * Copyright तऊ 2006-2007 Intel Corporation
 *   Jesse Barnes <jesse.barnes@पूर्णांकel.com>
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
 *	Eric Anholt <eric@anholt.net>
 */

#समावेश <linux/delay.h>
#समावेश <linux/i2c.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>

#समावेश <drm/drm_crtc.h>
#समावेश <drm/drm_edid.h>

#समावेश "psb_drv.h"
#समावेश "psb_intel_drv.h"
#समावेश "psb_intel_reg.h"
#समावेश "psb_intel_sdvo_regs.h"

#घोषणा SDVO_TMDS_MASK (SDVO_OUTPUT_TMDS0 | SDVO_OUTPUT_TMDS1)
#घोषणा SDVO_RGB_MASK  (SDVO_OUTPUT_RGB0 | SDVO_OUTPUT_RGB1)
#घोषणा SDVO_LVDS_MASK (SDVO_OUTPUT_LVDS0 | SDVO_OUTPUT_LVDS1)
#घोषणा SDVO_TV_MASK   (SDVO_OUTPUT_CVBS0 | SDVO_OUTPUT_SVID0)

#घोषणा SDVO_OUTPUT_MASK (SDVO_TMDS_MASK | SDVO_RGB_MASK | SDVO_LVDS_MASK |\
                         SDVO_TV_MASK)

#घोषणा IS_TV(c)	(c->output_flag & SDVO_TV_MASK)
#घोषणा IS_TMDS(c)	(c->output_flag & SDVO_TMDS_MASK)
#घोषणा IS_LVDS(c)	(c->output_flag & SDVO_LVDS_MASK)
#घोषणा IS_TV_OR_LVDS(c) (c->output_flag & (SDVO_TV_MASK | SDVO_LVDS_MASK))


अटल स्थिर अक्षर *tv_क्रमmat_names[] = अणु
	"NTSC_M"   , "NTSC_J"  , "NTSC_443",
	"PAL_B"    , "PAL_D"   , "PAL_G"   ,
	"PAL_H"    , "PAL_I"   , "PAL_M"   ,
	"PAL_N"    , "PAL_NC"  , "PAL_60"  ,
	"SECAM_B"  , "SECAM_D" , "SECAM_G" ,
	"SECAM_K"  , "SECAM_K1", "SECAM_L" ,
	"SECAM_60"
पूर्ण;

काष्ठा psb_पूर्णांकel_sdvo अणु
	काष्ठा gma_encoder base;

	काष्ठा i2c_adapter *i2c;
	u8 slave_addr;

	काष्ठा i2c_adapter ddc;

	/* Register क्रम the SDVO device: SDVOB or SDVOC */
	पूर्णांक sdvo_reg;

	/* Active outमाला_दो controlled by this SDVO output */
	uपूर्णांक16_t controlled_output;

	/*
	 * Capabilities of the SDVO device वापसed by
	 * i830_sdvo_get_capabilities()
	 */
	काष्ठा psb_पूर्णांकel_sdvo_caps caps;

	/* Pixel घड़ी limitations reported by the SDVO device, in kHz */
	पूर्णांक pixel_घड़ी_min, pixel_घड़ी_max;

	/*
	* For multiple function SDVO device,
	* this is क्रम current attached outमाला_दो.
	*/
	uपूर्णांक16_t attached_output;

	/**
	 * This is used to select the color range of RBG outमाला_दो in HDMI mode.
	 * It is only valid when using TMDS encoding and 8 bit per color mode.
	 */
	uपूर्णांक32_t color_range;

	/**
	 * This is set अगर we're going to treat the device as TV-out.
	 *
	 * While we have these nice मित्रly flags क्रम output types that ought
	 * to decide this क्रम us, the S-Video output on our HDMI+S-Video card
	 * shows up as RGB1 (VGA).
	 */
	bool is_tv;

	/* This is क्रम current tv क्रमmat name */
	पूर्णांक tv_क्रमmat_index;

	/**
	 * This is set अगर we treat the device as HDMI, instead of DVI.
	 */
	bool is_hdmi;
	bool has_hdmi_monitor;
	bool has_hdmi_audio;

	/**
	 * This is set अगर we detect output of sdvo device as LVDS and
	 * have a valid fixed mode to use with the panel.
	 */
	bool is_lvds;

	/**
	 * This is sdvo fixed panel mode poपूर्णांकer
	 */
	काष्ठा drm_display_mode *sdvo_lvds_fixed_mode;

	/* DDC bus used by this SDVO encoder */
	uपूर्णांक8_t ddc_bus;

	u8 pixel_multiplier;

	/* Input timings क्रम adjusted_mode */
	काष्ठा psb_पूर्णांकel_sdvo_dtd input_dtd;

	/* Saved SDVO output states */
	uपूर्णांक32_t saveSDVO; /* Can be SDVOB or SDVOC depending on sdvo_reg */
पूर्ण;

काष्ठा psb_पूर्णांकel_sdvo_connector अणु
	काष्ठा gma_connector base;

	/* Mark the type of connector */
	uपूर्णांक16_t output_flag;

	पूर्णांक क्रमce_audio;

	/* This contains all current supported TV क्रमmat */
	u8 tv_क्रमmat_supported[ARRAY_SIZE(tv_क्रमmat_names)];
	पूर्णांक   क्रमmat_supported_num;
	काष्ठा drm_property *tv_क्रमmat;

	/* add the property क्रम the SDVO-TV */
	काष्ठा drm_property *left;
	काष्ठा drm_property *right;
	काष्ठा drm_property *top;
	काष्ठा drm_property *bottom;
	काष्ठा drm_property *hpos;
	काष्ठा drm_property *vpos;
	काष्ठा drm_property *contrast;
	काष्ठा drm_property *saturation;
	काष्ठा drm_property *hue;
	काष्ठा drm_property *sharpness;
	काष्ठा drm_property *flicker_filter;
	काष्ठा drm_property *flicker_filter_adaptive;
	काष्ठा drm_property *flicker_filter_2d;
	काष्ठा drm_property *tv_chroma_filter;
	काष्ठा drm_property *tv_luma_filter;
	काष्ठा drm_property *करोt_crawl;

	/* add the property क्रम the SDVO-TV/LVDS */
	काष्ठा drm_property *brightness;

	/* Add variable to record current setting क्रम the above property */
	u32	left_margin, right_margin, top_margin, bottom_margin;

	/* this is to get the range of margin.*/
	u32	max_hscan,  max_vscan;
	u32	max_hpos, cur_hpos;
	u32	max_vpos, cur_vpos;
	u32	cur_brightness, max_brightness;
	u32	cur_contrast,	max_contrast;
	u32	cur_saturation, max_saturation;
	u32	cur_hue,	max_hue;
	u32	cur_sharpness,	max_sharpness;
	u32	cur_flicker_filter,		max_flicker_filter;
	u32	cur_flicker_filter_adaptive,	max_flicker_filter_adaptive;
	u32	cur_flicker_filter_2d,		max_flicker_filter_2d;
	u32	cur_tv_chroma_filter,	max_tv_chroma_filter;
	u32	cur_tv_luma_filter,	max_tv_luma_filter;
	u32	cur_करोt_crawl,	max_करोt_crawl;
पूर्ण;

अटल काष्ठा psb_पूर्णांकel_sdvo *to_psb_पूर्णांकel_sdvo(काष्ठा drm_encoder *encoder)
अणु
	वापस container_of(encoder, काष्ठा psb_पूर्णांकel_sdvo, base.base);
पूर्ण

अटल काष्ठा psb_पूर्णांकel_sdvo *पूर्णांकel_attached_sdvo(काष्ठा drm_connector *connector)
अणु
	वापस container_of(gma_attached_encoder(connector),
			    काष्ठा psb_पूर्णांकel_sdvo, base);
पूर्ण

अटल काष्ठा psb_पूर्णांकel_sdvo_connector *to_psb_पूर्णांकel_sdvo_connector(काष्ठा drm_connector *connector)
अणु
	वापस container_of(to_gma_connector(connector), काष्ठा psb_पूर्णांकel_sdvo_connector, base);
पूर्ण

अटल bool
psb_पूर्णांकel_sdvo_output_setup(काष्ठा psb_पूर्णांकel_sdvo *psb_पूर्णांकel_sdvo, uपूर्णांक16_t flags);
अटल bool
psb_पूर्णांकel_sdvo_tv_create_property(काष्ठा psb_पूर्णांकel_sdvo *psb_पूर्णांकel_sdvo,
			      काष्ठा psb_पूर्णांकel_sdvo_connector *psb_पूर्णांकel_sdvo_connector,
			      पूर्णांक type);
अटल bool
psb_पूर्णांकel_sdvo_create_enhance_property(काष्ठा psb_पूर्णांकel_sdvo *psb_पूर्णांकel_sdvo,
				   काष्ठा psb_पूर्णांकel_sdvo_connector *psb_पूर्णांकel_sdvo_connector);

/*
 * Writes the SDVOB or SDVOC with the given value, but always ग_लिखोs both
 * SDVOB and SDVOC to work around apparent hardware issues (according to
 * comments in the BIOS).
 */
अटल व्योम psb_पूर्णांकel_sdvo_ग_लिखो_sdvox(काष्ठा psb_पूर्णांकel_sdvo *psb_पूर्णांकel_sdvo, u32 val)
अणु
	काष्ठा drm_device *dev = psb_पूर्णांकel_sdvo->base.base.dev;
	u32 bval = val, cval = val;
	पूर्णांक i, j;
	पूर्णांक need_aux = IS_MRST(dev) ? 1 : 0;

	क्रम (j = 0; j <= need_aux; j++) अणु
		अगर (psb_पूर्णांकel_sdvo->sdvo_reg == SDVOB)
			cval = REG_READ_WITH_AUX(SDVOC, j);
		अन्यथा
			bval = REG_READ_WITH_AUX(SDVOB, j);

		/*
		* Write the रेजिस्टरs twice क्रम luck. Someबार,
		* writing them only once करोesn't appear to 'stick'.
		* The BIOS करोes this too. Yay, magic
		*/
		क्रम (i = 0; i < 2; i++) अणु
			REG_WRITE_WITH_AUX(SDVOB, bval, j);
			REG_READ_WITH_AUX(SDVOB, j);
			REG_WRITE_WITH_AUX(SDVOC, cval, j);
			REG_READ_WITH_AUX(SDVOC, j);
		पूर्ण
	पूर्ण
पूर्ण

अटल bool psb_पूर्णांकel_sdvo_पढ़ो_byte(काष्ठा psb_पूर्णांकel_sdvo *psb_पूर्णांकel_sdvo, u8 addr, u8 *ch)
अणु
	काष्ठा i2c_msg msgs[] = अणु
		अणु
			.addr = psb_पूर्णांकel_sdvo->slave_addr,
			.flags = 0,
			.len = 1,
			.buf = &addr,
		पूर्ण,
		अणु
			.addr = psb_पूर्णांकel_sdvo->slave_addr,
			.flags = I2C_M_RD,
			.len = 1,
			.buf = ch,
		पूर्ण
	पूर्ण;
	पूर्णांक ret;

	अगर ((ret = i2c_transfer(psb_पूर्णांकel_sdvo->i2c, msgs, 2)) == 2)
		वापस true;

	DRM_DEBUG_KMS("i2c transfer returned %d\n", ret);
	वापस false;
पूर्ण

#घोषणा SDVO_CMD_NAME_ENTRY(cmd) अणुcmd, #cmdपूर्ण
/** Mapping of command numbers to names, क्रम debug output */
अटल स्थिर काष्ठा _sdvo_cmd_name अणु
	u8 cmd;
	स्थिर अक्षर *name;
पूर्ण sdvo_cmd_names[] = अणु
    SDVO_CMD_NAME_ENTRY(SDVO_CMD_RESET),
    SDVO_CMD_NAME_ENTRY(SDVO_CMD_GET_DEVICE_CAPS),
    SDVO_CMD_NAME_ENTRY(SDVO_CMD_GET_FIRMWARE_REV),
    SDVO_CMD_NAME_ENTRY(SDVO_CMD_GET_TRAINED_INPUTS),
    SDVO_CMD_NAME_ENTRY(SDVO_CMD_GET_ACTIVE_OUTPUTS),
    SDVO_CMD_NAME_ENTRY(SDVO_CMD_SET_ACTIVE_OUTPUTS),
    SDVO_CMD_NAME_ENTRY(SDVO_CMD_GET_IN_OUT_MAP),
    SDVO_CMD_NAME_ENTRY(SDVO_CMD_SET_IN_OUT_MAP),
    SDVO_CMD_NAME_ENTRY(SDVO_CMD_GET_ATTACHED_DISPLAYS),
    SDVO_CMD_NAME_ENTRY(SDVO_CMD_GET_HOT_PLUG_SUPPORT),
    SDVO_CMD_NAME_ENTRY(SDVO_CMD_SET_ACTIVE_HOT_PLUG),
    SDVO_CMD_NAME_ENTRY(SDVO_CMD_GET_ACTIVE_HOT_PLUG),
    SDVO_CMD_NAME_ENTRY(SDVO_CMD_GET_INTERRUPT_EVENT_SOURCE),
    SDVO_CMD_NAME_ENTRY(SDVO_CMD_SET_TARGET_INPUT),
    SDVO_CMD_NAME_ENTRY(SDVO_CMD_SET_TARGET_OUTPUT),
    SDVO_CMD_NAME_ENTRY(SDVO_CMD_GET_INPUT_TIMINGS_PART1),
    SDVO_CMD_NAME_ENTRY(SDVO_CMD_GET_INPUT_TIMINGS_PART2),
    SDVO_CMD_NAME_ENTRY(SDVO_CMD_SET_INPUT_TIMINGS_PART1),
    SDVO_CMD_NAME_ENTRY(SDVO_CMD_SET_INPUT_TIMINGS_PART2),
    SDVO_CMD_NAME_ENTRY(SDVO_CMD_SET_INPUT_TIMINGS_PART1),
    SDVO_CMD_NAME_ENTRY(SDVO_CMD_SET_OUTPUT_TIMINGS_PART1),
    SDVO_CMD_NAME_ENTRY(SDVO_CMD_SET_OUTPUT_TIMINGS_PART2),
    SDVO_CMD_NAME_ENTRY(SDVO_CMD_GET_OUTPUT_TIMINGS_PART1),
    SDVO_CMD_NAME_ENTRY(SDVO_CMD_GET_OUTPUT_TIMINGS_PART2),
    SDVO_CMD_NAME_ENTRY(SDVO_CMD_CREATE_PREFERRED_INPUT_TIMING),
    SDVO_CMD_NAME_ENTRY(SDVO_CMD_GET_PREFERRED_INPUT_TIMING_PART1),
    SDVO_CMD_NAME_ENTRY(SDVO_CMD_GET_PREFERRED_INPUT_TIMING_PART2),
    SDVO_CMD_NAME_ENTRY(SDVO_CMD_GET_INPUT_PIXEL_CLOCK_RANGE),
    SDVO_CMD_NAME_ENTRY(SDVO_CMD_GET_OUTPUT_PIXEL_CLOCK_RANGE),
    SDVO_CMD_NAME_ENTRY(SDVO_CMD_GET_SUPPORTED_CLOCK_RATE_MULTS),
    SDVO_CMD_NAME_ENTRY(SDVO_CMD_GET_CLOCK_RATE_MULT),
    SDVO_CMD_NAME_ENTRY(SDVO_CMD_SET_CLOCK_RATE_MULT),
    SDVO_CMD_NAME_ENTRY(SDVO_CMD_GET_SUPPORTED_TV_FORMATS),
    SDVO_CMD_NAME_ENTRY(SDVO_CMD_GET_TV_FORMAT),
    SDVO_CMD_NAME_ENTRY(SDVO_CMD_SET_TV_FORMAT),
    SDVO_CMD_NAME_ENTRY(SDVO_CMD_GET_SUPPORTED_POWER_STATES),
    SDVO_CMD_NAME_ENTRY(SDVO_CMD_GET_POWER_STATE),
    SDVO_CMD_NAME_ENTRY(SDVO_CMD_SET_ENCODER_POWER_STATE),
    SDVO_CMD_NAME_ENTRY(SDVO_CMD_SET_DISPLAY_POWER_STATE),
    SDVO_CMD_NAME_ENTRY(SDVO_CMD_SET_CONTROL_BUS_SWITCH),
    SDVO_CMD_NAME_ENTRY(SDVO_CMD_GET_SDTV_RESOLUTION_SUPPORT),
    SDVO_CMD_NAME_ENTRY(SDVO_CMD_GET_SCALED_HDTV_RESOLUTION_SUPPORT),
    SDVO_CMD_NAME_ENTRY(SDVO_CMD_GET_SUPPORTED_ENHANCEMENTS),

    /* Add the op code क्रम SDVO enhancements */
    SDVO_CMD_NAME_ENTRY(SDVO_CMD_GET_MAX_HPOS),
    SDVO_CMD_NAME_ENTRY(SDVO_CMD_GET_HPOS),
    SDVO_CMD_NAME_ENTRY(SDVO_CMD_SET_HPOS),
    SDVO_CMD_NAME_ENTRY(SDVO_CMD_GET_MAX_VPOS),
    SDVO_CMD_NAME_ENTRY(SDVO_CMD_GET_VPOS),
    SDVO_CMD_NAME_ENTRY(SDVO_CMD_SET_VPOS),
    SDVO_CMD_NAME_ENTRY(SDVO_CMD_GET_MAX_SATURATION),
    SDVO_CMD_NAME_ENTRY(SDVO_CMD_GET_SATURATION),
    SDVO_CMD_NAME_ENTRY(SDVO_CMD_SET_SATURATION),
    SDVO_CMD_NAME_ENTRY(SDVO_CMD_GET_MAX_HUE),
    SDVO_CMD_NAME_ENTRY(SDVO_CMD_GET_HUE),
    SDVO_CMD_NAME_ENTRY(SDVO_CMD_SET_HUE),
    SDVO_CMD_NAME_ENTRY(SDVO_CMD_GET_MAX_CONTRAST),
    SDVO_CMD_NAME_ENTRY(SDVO_CMD_GET_CONTRAST),
    SDVO_CMD_NAME_ENTRY(SDVO_CMD_SET_CONTRAST),
    SDVO_CMD_NAME_ENTRY(SDVO_CMD_GET_MAX_BRIGHTNESS),
    SDVO_CMD_NAME_ENTRY(SDVO_CMD_GET_BRIGHTNESS),
    SDVO_CMD_NAME_ENTRY(SDVO_CMD_SET_BRIGHTNESS),
    SDVO_CMD_NAME_ENTRY(SDVO_CMD_GET_MAX_OVERSCAN_H),
    SDVO_CMD_NAME_ENTRY(SDVO_CMD_GET_OVERSCAN_H),
    SDVO_CMD_NAME_ENTRY(SDVO_CMD_SET_OVERSCAN_H),
    SDVO_CMD_NAME_ENTRY(SDVO_CMD_GET_MAX_OVERSCAN_V),
    SDVO_CMD_NAME_ENTRY(SDVO_CMD_GET_OVERSCAN_V),
    SDVO_CMD_NAME_ENTRY(SDVO_CMD_SET_OVERSCAN_V),
    SDVO_CMD_NAME_ENTRY(SDVO_CMD_GET_MAX_FLICKER_FILTER),
    SDVO_CMD_NAME_ENTRY(SDVO_CMD_GET_FLICKER_FILTER),
    SDVO_CMD_NAME_ENTRY(SDVO_CMD_SET_FLICKER_FILTER),
    SDVO_CMD_NAME_ENTRY(SDVO_CMD_GET_MAX_FLICKER_FILTER_ADAPTIVE),
    SDVO_CMD_NAME_ENTRY(SDVO_CMD_GET_FLICKER_FILTER_ADAPTIVE),
    SDVO_CMD_NAME_ENTRY(SDVO_CMD_SET_FLICKER_FILTER_ADAPTIVE),
    SDVO_CMD_NAME_ENTRY(SDVO_CMD_GET_MAX_FLICKER_FILTER_2D),
    SDVO_CMD_NAME_ENTRY(SDVO_CMD_GET_FLICKER_FILTER_2D),
    SDVO_CMD_NAME_ENTRY(SDVO_CMD_SET_FLICKER_FILTER_2D),
    SDVO_CMD_NAME_ENTRY(SDVO_CMD_GET_MAX_SHARPNESS),
    SDVO_CMD_NAME_ENTRY(SDVO_CMD_GET_SHARPNESS),
    SDVO_CMD_NAME_ENTRY(SDVO_CMD_SET_SHARPNESS),
    SDVO_CMD_NAME_ENTRY(SDVO_CMD_GET_DOT_CRAWL),
    SDVO_CMD_NAME_ENTRY(SDVO_CMD_SET_DOT_CRAWL),
    SDVO_CMD_NAME_ENTRY(SDVO_CMD_GET_MAX_TV_CHROMA_FILTER),
    SDVO_CMD_NAME_ENTRY(SDVO_CMD_GET_TV_CHROMA_FILTER),
    SDVO_CMD_NAME_ENTRY(SDVO_CMD_SET_TV_CHROMA_FILTER),
    SDVO_CMD_NAME_ENTRY(SDVO_CMD_GET_MAX_TV_LUMA_FILTER),
    SDVO_CMD_NAME_ENTRY(SDVO_CMD_GET_TV_LUMA_FILTER),
    SDVO_CMD_NAME_ENTRY(SDVO_CMD_SET_TV_LUMA_FILTER),

    /* HDMI op code */
    SDVO_CMD_NAME_ENTRY(SDVO_CMD_GET_SUPP_ENCODE),
    SDVO_CMD_NAME_ENTRY(SDVO_CMD_GET_ENCODE),
    SDVO_CMD_NAME_ENTRY(SDVO_CMD_SET_ENCODE),
    SDVO_CMD_NAME_ENTRY(SDVO_CMD_SET_PIXEL_REPLI),
    SDVO_CMD_NAME_ENTRY(SDVO_CMD_GET_PIXEL_REPLI),
    SDVO_CMD_NAME_ENTRY(SDVO_CMD_GET_COLORIMETRY_CAP),
    SDVO_CMD_NAME_ENTRY(SDVO_CMD_SET_COLORIMETRY),
    SDVO_CMD_NAME_ENTRY(SDVO_CMD_GET_COLORIMETRY),
    SDVO_CMD_NAME_ENTRY(SDVO_CMD_GET_AUDIO_ENCRYPT_PREFER),
    SDVO_CMD_NAME_ENTRY(SDVO_CMD_SET_AUDIO_STAT),
    SDVO_CMD_NAME_ENTRY(SDVO_CMD_GET_AUDIO_STAT),
    SDVO_CMD_NAME_ENTRY(SDVO_CMD_GET_HBUF_INDEX),
    SDVO_CMD_NAME_ENTRY(SDVO_CMD_SET_HBUF_INDEX),
    SDVO_CMD_NAME_ENTRY(SDVO_CMD_GET_HBUF_INFO),
    SDVO_CMD_NAME_ENTRY(SDVO_CMD_GET_HBUF_AV_SPLIT),
    SDVO_CMD_NAME_ENTRY(SDVO_CMD_SET_HBUF_AV_SPLIT),
    SDVO_CMD_NAME_ENTRY(SDVO_CMD_GET_HBUF_TXRATE),
    SDVO_CMD_NAME_ENTRY(SDVO_CMD_SET_HBUF_TXRATE),
    SDVO_CMD_NAME_ENTRY(SDVO_CMD_SET_HBUF_DATA),
    SDVO_CMD_NAME_ENTRY(SDVO_CMD_GET_HBUF_DATA),
पूर्ण;

#घोषणा IS_SDVOB(reg)	(reg == SDVOB)
#घोषणा SDVO_NAME(svकरो) (IS_SDVOB((svकरो)->sdvo_reg) ? "SDVOB" : "SDVOC")

अटल व्योम psb_पूर्णांकel_sdvo_debug_ग_लिखो(काष्ठा psb_पूर्णांकel_sdvo *psb_पूर्णांकel_sdvo, u8 cmd,
				   स्थिर व्योम *args, पूर्णांक args_len)
अणु
	पूर्णांक i;

	DRM_DEBUG_KMS("%s: W: %02X ",
				SDVO_NAME(psb_पूर्णांकel_sdvo), cmd);
	क्रम (i = 0; i < args_len; i++)
		DRM_DEBUG_KMS("%02X ", ((u8 *)args)[i]);
	क्रम (; i < 8; i++)
		DRM_DEBUG_KMS("   ");
	क्रम (i = 0; i < ARRAY_SIZE(sdvo_cmd_names); i++) अणु
		अगर (cmd == sdvo_cmd_names[i].cmd) अणु
			DRM_DEBUG_KMS("(%s)", sdvo_cmd_names[i].name);
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (i == ARRAY_SIZE(sdvo_cmd_names))
		DRM_DEBUG_KMS("(%02X)", cmd);
	DRM_DEBUG_KMS("\n");
पूर्ण

अटल स्थिर अक्षर *cmd_status_names[] = अणु
	"Power on",
	"Success",
	"Not supported",
	"Invalid arg",
	"Pending",
	"Target not specified",
	"Scaling not supported"
पूर्ण;

#घोषणा MAX_ARG_LEN 32

अटल bool psb_पूर्णांकel_sdvo_ग_लिखो_cmd(काष्ठा psb_पूर्णांकel_sdvo *psb_पूर्णांकel_sdvo, u8 cmd,
				 स्थिर व्योम *args, पूर्णांक args_len)
अणु
	u8 buf[MAX_ARG_LEN*2 + 2], status;
	काष्ठा i2c_msg msgs[MAX_ARG_LEN + 3];
	पूर्णांक i, ret;

	अगर (args_len > MAX_ARG_LEN) अणु
		DRM_ERROR("Need to increase arg length\n");
		वापस false;
	पूर्ण

	psb_पूर्णांकel_sdvo_debug_ग_लिखो(psb_पूर्णांकel_sdvo, cmd, args, args_len);

	क्रम (i = 0; i < args_len; i++) अणु
		msgs[i].addr = psb_पूर्णांकel_sdvo->slave_addr;
		msgs[i].flags = 0;
		msgs[i].len = 2;
		msgs[i].buf = buf + 2 *i;
		buf[2*i + 0] = SDVO_I2C_ARG_0 - i;
		buf[2*i + 1] = ((u8*)args)[i];
	पूर्ण
	msgs[i].addr = psb_पूर्णांकel_sdvo->slave_addr;
	msgs[i].flags = 0;
	msgs[i].len = 2;
	msgs[i].buf = buf + 2*i;
	buf[2*i + 0] = SDVO_I2C_OPCODE;
	buf[2*i + 1] = cmd;

	/* the following two are to पढ़ो the response */
	status = SDVO_I2C_CMD_STATUS;
	msgs[i+1].addr = psb_पूर्णांकel_sdvo->slave_addr;
	msgs[i+1].flags = 0;
	msgs[i+1].len = 1;
	msgs[i+1].buf = &status;

	msgs[i+2].addr = psb_पूर्णांकel_sdvo->slave_addr;
	msgs[i+2].flags = I2C_M_RD;
	msgs[i+2].len = 1;
	msgs[i+2].buf = &status;

	ret = i2c_transfer(psb_पूर्णांकel_sdvo->i2c, msgs, i+3);
	अगर (ret < 0) अणु
		DRM_DEBUG_KMS("I2c transfer returned %d\n", ret);
		वापस false;
	पूर्ण
	अगर (ret != i+3) अणु
		/* failure in I2C transfer */
		DRM_DEBUG_KMS("I2c transfer returned %d/%d\n", ret, i+3);
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल bool psb_पूर्णांकel_sdvo_पढ़ो_response(काष्ठा psb_पूर्णांकel_sdvo *psb_पूर्णांकel_sdvo,
				     व्योम *response, पूर्णांक response_len)
अणु
	u8 retry = 5;
	u8 status;
	पूर्णांक i;

	DRM_DEBUG_KMS("%s: R: ", SDVO_NAME(psb_पूर्णांकel_sdvo));

	/*
	 * The करोcumentation states that all commands will be
	 * processed within 15तगs, and that we need only poll
	 * the status byte a maximum of 3 बार in order क्रम the
	 * command to be complete.
	 *
	 * Check 5 बार in हाल the hardware failed to पढ़ो the करोcs.
	 */
	अगर (!psb_पूर्णांकel_sdvo_पढ़ो_byte(psb_पूर्णांकel_sdvo,
				  SDVO_I2C_CMD_STATUS,
				  &status))
		जाओ log_fail;

	जबतक ((status == SDVO_CMD_STATUS_PENDING ||
		status == SDVO_CMD_STATUS_TARGET_NOT_SPECIFIED) && retry--) अणु
		udelay(15);
		अगर (!psb_पूर्णांकel_sdvo_पढ़ो_byte(psb_पूर्णांकel_sdvo,
					  SDVO_I2C_CMD_STATUS,
					  &status))
			जाओ log_fail;
	पूर्ण

	अगर (status <= SDVO_CMD_STATUS_SCALING_NOT_SUPP)
		DRM_DEBUG_KMS("(%s)", cmd_status_names[status]);
	अन्यथा
		DRM_DEBUG_KMS("(??? %d)", status);

	अगर (status != SDVO_CMD_STATUS_SUCCESS)
		जाओ log_fail;

	/* Read the command response */
	क्रम (i = 0; i < response_len; i++) अणु
		अगर (!psb_पूर्णांकel_sdvo_पढ़ो_byte(psb_पूर्णांकel_sdvo,
					  SDVO_I2C_RETURN_0 + i,
					  &((u8 *)response)[i]))
			जाओ log_fail;
		DRM_DEBUG_KMS(" %02X", ((u8 *)response)[i]);
	पूर्ण
	DRM_DEBUG_KMS("\n");
	वापस true;

log_fail:
	DRM_DEBUG_KMS("... failed\n");
	वापस false;
पूर्ण

अटल पूर्णांक psb_पूर्णांकel_sdvo_get_pixel_multiplier(काष्ठा drm_display_mode *mode)
अणु
	अगर (mode->घड़ी >= 100000)
		वापस 1;
	अन्यथा अगर (mode->घड़ी >= 50000)
		वापस 2;
	अन्यथा
		वापस 4;
पूर्ण

अटल bool psb_पूर्णांकel_sdvo_set_control_bus_चयन(काष्ठा psb_पूर्णांकel_sdvo *psb_पूर्णांकel_sdvo,
					      u8 ddc_bus)
अणु
	/* This must be the immediately preceding ग_लिखो beक्रमe the i2c xfer */
	वापस psb_पूर्णांकel_sdvo_ग_लिखो_cmd(psb_पूर्णांकel_sdvo,
				    SDVO_CMD_SET_CONTROL_BUS_SWITCH,
				    &ddc_bus, 1);
पूर्ण

अटल bool psb_पूर्णांकel_sdvo_set_value(काष्ठा psb_पूर्णांकel_sdvo *psb_पूर्णांकel_sdvo, u8 cmd, स्थिर व्योम *data, पूर्णांक len)
अणु
	अगर (!psb_पूर्णांकel_sdvo_ग_लिखो_cmd(psb_पूर्णांकel_sdvo, cmd, data, len))
		वापस false;

	वापस psb_पूर्णांकel_sdvo_पढ़ो_response(psb_पूर्णांकel_sdvo, शून्य, 0);
पूर्ण

अटल bool
psb_पूर्णांकel_sdvo_get_value(काष्ठा psb_पूर्णांकel_sdvo *psb_पूर्णांकel_sdvo, u8 cmd, व्योम *value, पूर्णांक len)
अणु
	अगर (!psb_पूर्णांकel_sdvo_ग_लिखो_cmd(psb_पूर्णांकel_sdvo, cmd, शून्य, 0))
		वापस false;

	वापस psb_पूर्णांकel_sdvo_पढ़ो_response(psb_पूर्णांकel_sdvo, value, len);
पूर्ण

अटल bool psb_पूर्णांकel_sdvo_set_target_input(काष्ठा psb_पूर्णांकel_sdvo *psb_पूर्णांकel_sdvo)
अणु
	काष्ठा psb_पूर्णांकel_sdvo_set_target_input_args tarमाला_लो = अणु0पूर्ण;
	वापस psb_पूर्णांकel_sdvo_set_value(psb_पूर्णांकel_sdvo,
				    SDVO_CMD_SET_TARGET_INPUT,
				    &tarमाला_लो, माप(tarमाला_लो));
पूर्ण

/*
 * Return whether each input is trained.
 *
 * This function is making an assumption about the layout of the response,
 * which should be checked against the करोcs.
 */
अटल bool psb_पूर्णांकel_sdvo_get_trained_inमाला_दो(काष्ठा psb_पूर्णांकel_sdvo *psb_पूर्णांकel_sdvo, bool *input_1, bool *input_2)
अणु
	काष्ठा psb_पूर्णांकel_sdvo_get_trained_inमाला_दो_response response;

	BUILD_BUG_ON(माप(response) != 1);
	अगर (!psb_पूर्णांकel_sdvo_get_value(psb_पूर्णांकel_sdvo, SDVO_CMD_GET_TRAINED_INPUTS,
				  &response, माप(response)))
		वापस false;

	*input_1 = response.input0_trained;
	*input_2 = response.input1_trained;
	वापस true;
पूर्ण

अटल bool psb_पूर्णांकel_sdvo_set_active_outमाला_दो(काष्ठा psb_पूर्णांकel_sdvo *psb_पूर्णांकel_sdvo,
					  u16 outमाला_दो)
अणु
	वापस psb_पूर्णांकel_sdvo_set_value(psb_पूर्णांकel_sdvo,
				    SDVO_CMD_SET_ACTIVE_OUTPUTS,
				    &outमाला_दो, माप(outमाला_दो));
पूर्ण

अटल bool psb_पूर्णांकel_sdvo_set_encoder_घातer_state(काष्ठा psb_पूर्णांकel_sdvo *psb_पूर्णांकel_sdvo,
					       पूर्णांक mode)
अणु
	u8 state = SDVO_ENCODER_STATE_ON;

	चयन (mode) अणु
	हाल DRM_MODE_DPMS_ON:
		state = SDVO_ENCODER_STATE_ON;
		अवरोध;
	हाल DRM_MODE_DPMS_STANDBY:
		state = SDVO_ENCODER_STATE_STANDBY;
		अवरोध;
	हाल DRM_MODE_DPMS_SUSPEND:
		state = SDVO_ENCODER_STATE_SUSPEND;
		अवरोध;
	हाल DRM_MODE_DPMS_OFF:
		state = SDVO_ENCODER_STATE_OFF;
		अवरोध;
	पूर्ण

	वापस psb_पूर्णांकel_sdvo_set_value(psb_पूर्णांकel_sdvo,
				    SDVO_CMD_SET_ENCODER_POWER_STATE, &state, माप(state));
पूर्ण

अटल bool psb_पूर्णांकel_sdvo_get_input_pixel_घड़ी_range(काष्ठा psb_पूर्णांकel_sdvo *psb_पूर्णांकel_sdvo,
						   पूर्णांक *घड़ी_min,
						   पूर्णांक *घड़ी_max)
अणु
	काष्ठा psb_पूर्णांकel_sdvo_pixel_घड़ी_range घड़ीs;

	BUILD_BUG_ON(माप(घड़ीs) != 4);
	अगर (!psb_पूर्णांकel_sdvo_get_value(psb_पूर्णांकel_sdvo,
				  SDVO_CMD_GET_INPUT_PIXEL_CLOCK_RANGE,
				  &घड़ीs, माप(घड़ीs)))
		वापस false;

	/* Convert the values from units of 10 kHz to kHz. */
	*घड़ी_min = घड़ीs.min * 10;
	*घड़ी_max = घड़ीs.max * 10;
	वापस true;
पूर्ण

अटल bool psb_पूर्णांकel_sdvo_set_target_output(काष्ठा psb_पूर्णांकel_sdvo *psb_पूर्णांकel_sdvo,
					 u16 outमाला_दो)
अणु
	वापस psb_पूर्णांकel_sdvo_set_value(psb_पूर्णांकel_sdvo,
				    SDVO_CMD_SET_TARGET_OUTPUT,
				    &outमाला_दो, माप(outमाला_दो));
पूर्ण

अटल bool psb_पूर्णांकel_sdvo_set_timing(काष्ठा psb_पूर्णांकel_sdvo *psb_पूर्णांकel_sdvo, u8 cmd,
				  काष्ठा psb_पूर्णांकel_sdvo_dtd *dtd)
अणु
	वापस psb_पूर्णांकel_sdvo_set_value(psb_पूर्णांकel_sdvo, cmd, &dtd->part1, माप(dtd->part1)) &&
		psb_पूर्णांकel_sdvo_set_value(psb_पूर्णांकel_sdvo, cmd + 1, &dtd->part2, माप(dtd->part2));
पूर्ण

अटल bool psb_पूर्णांकel_sdvo_set_input_timing(काष्ठा psb_पूर्णांकel_sdvo *psb_पूर्णांकel_sdvo,
					 काष्ठा psb_पूर्णांकel_sdvo_dtd *dtd)
अणु
	वापस psb_पूर्णांकel_sdvo_set_timing(psb_पूर्णांकel_sdvo,
				     SDVO_CMD_SET_INPUT_TIMINGS_PART1, dtd);
पूर्ण

अटल bool psb_पूर्णांकel_sdvo_set_output_timing(काष्ठा psb_पूर्णांकel_sdvo *psb_पूर्णांकel_sdvo,
					 काष्ठा psb_पूर्णांकel_sdvo_dtd *dtd)
अणु
	वापस psb_पूर्णांकel_sdvo_set_timing(psb_पूर्णांकel_sdvo,
				     SDVO_CMD_SET_OUTPUT_TIMINGS_PART1, dtd);
पूर्ण

अटल bool
psb_पूर्णांकel_sdvo_create_preferred_input_timing(काष्ठा psb_पूर्णांकel_sdvo *psb_पूर्णांकel_sdvo,
					 uपूर्णांक16_t घड़ी,
					 uपूर्णांक16_t width,
					 uपूर्णांक16_t height)
अणु
	काष्ठा psb_पूर्णांकel_sdvo_preferred_input_timing_args args;

	स_रखो(&args, 0, माप(args));
	args.घड़ी = घड़ी;
	args.width = width;
	args.height = height;
	args.पूर्णांकerlace = 0;

	अगर (psb_पूर्णांकel_sdvo->is_lvds &&
	   (psb_पूर्णांकel_sdvo->sdvo_lvds_fixed_mode->hdisplay != width ||
	    psb_पूर्णांकel_sdvo->sdvo_lvds_fixed_mode->vdisplay != height))
		args.scaled = 1;

	वापस psb_पूर्णांकel_sdvo_set_value(psb_पूर्णांकel_sdvo,
				    SDVO_CMD_CREATE_PREFERRED_INPUT_TIMING,
				    &args, माप(args));
पूर्ण

अटल bool psb_पूर्णांकel_sdvo_get_preferred_input_timing(काष्ठा psb_पूर्णांकel_sdvo *psb_पूर्णांकel_sdvo,
						  काष्ठा psb_पूर्णांकel_sdvo_dtd *dtd)
अणु
	BUILD_BUG_ON(माप(dtd->part1) != 8);
	BUILD_BUG_ON(माप(dtd->part2) != 8);
	वापस psb_पूर्णांकel_sdvo_get_value(psb_पूर्णांकel_sdvo, SDVO_CMD_GET_PREFERRED_INPUT_TIMING_PART1,
				    &dtd->part1, माप(dtd->part1)) &&
		psb_पूर्णांकel_sdvo_get_value(psb_पूर्णांकel_sdvo, SDVO_CMD_GET_PREFERRED_INPUT_TIMING_PART2,
				     &dtd->part2, माप(dtd->part2));
पूर्ण

अटल bool psb_पूर्णांकel_sdvo_set_घड़ी_rate_mult(काष्ठा psb_पूर्णांकel_sdvo *psb_पूर्णांकel_sdvo, u8 val)
अणु
	वापस psb_पूर्णांकel_sdvo_set_value(psb_पूर्णांकel_sdvo, SDVO_CMD_SET_CLOCK_RATE_MULT, &val, 1);
पूर्ण

अटल व्योम psb_पूर्णांकel_sdvo_get_dtd_from_mode(काष्ठा psb_पूर्णांकel_sdvo_dtd *dtd,
					 स्थिर काष्ठा drm_display_mode *mode)
अणु
	uपूर्णांक16_t width, height;
	uपूर्णांक16_t h_blank_len, h_sync_len, v_blank_len, v_sync_len;
	uपूर्णांक16_t h_sync_offset, v_sync_offset;

	width = mode->crtc_hdisplay;
	height = mode->crtc_vdisplay;

	/* करो some mode translations */
	h_blank_len = mode->crtc_hblank_end - mode->crtc_hblank_start;
	h_sync_len = mode->crtc_hsync_end - mode->crtc_hsync_start;

	v_blank_len = mode->crtc_vblank_end - mode->crtc_vblank_start;
	v_sync_len = mode->crtc_vsync_end - mode->crtc_vsync_start;

	h_sync_offset = mode->crtc_hsync_start - mode->crtc_hblank_start;
	v_sync_offset = mode->crtc_vsync_start - mode->crtc_vblank_start;

	dtd->part1.घड़ी = mode->घड़ी / 10;
	dtd->part1.h_active = width & 0xff;
	dtd->part1.h_blank = h_blank_len & 0xff;
	dtd->part1.h_high = (((width >> 8) & 0xf) << 4) |
		((h_blank_len >> 8) & 0xf);
	dtd->part1.v_active = height & 0xff;
	dtd->part1.v_blank = v_blank_len & 0xff;
	dtd->part1.v_high = (((height >> 8) & 0xf) << 4) |
		((v_blank_len >> 8) & 0xf);

	dtd->part2.h_sync_off = h_sync_offset & 0xff;
	dtd->part2.h_sync_width = h_sync_len & 0xff;
	dtd->part2.v_sync_off_width = (v_sync_offset & 0xf) << 4 |
		(v_sync_len & 0xf);
	dtd->part2.sync_off_width_high = ((h_sync_offset & 0x300) >> 2) |
		((h_sync_len & 0x300) >> 4) | ((v_sync_offset & 0x30) >> 2) |
		((v_sync_len & 0x30) >> 4);

	dtd->part2.dtd_flags = 0x18;
	अगर (mode->flags & DRM_MODE_FLAG_PHSYNC)
		dtd->part2.dtd_flags |= 0x2;
	अगर (mode->flags & DRM_MODE_FLAG_PVSYNC)
		dtd->part2.dtd_flags |= 0x4;

	dtd->part2.sdvo_flags = 0;
	dtd->part2.v_sync_off_high = v_sync_offset & 0xc0;
	dtd->part2.reserved = 0;
पूर्ण

अटल व्योम psb_पूर्णांकel_sdvo_get_mode_from_dtd(काष्ठा drm_display_mode * mode,
					 स्थिर काष्ठा psb_पूर्णांकel_sdvo_dtd *dtd)
अणु
	mode->hdisplay = dtd->part1.h_active;
	mode->hdisplay += ((dtd->part1.h_high >> 4) & 0x0f) << 8;
	mode->hsync_start = mode->hdisplay + dtd->part2.h_sync_off;
	mode->hsync_start += (dtd->part2.sync_off_width_high & 0xc0) << 2;
	mode->hsync_end = mode->hsync_start + dtd->part2.h_sync_width;
	mode->hsync_end += (dtd->part2.sync_off_width_high & 0x30) << 4;
	mode->htotal = mode->hdisplay + dtd->part1.h_blank;
	mode->htotal += (dtd->part1.h_high & 0xf) << 8;

	mode->vdisplay = dtd->part1.v_active;
	mode->vdisplay += ((dtd->part1.v_high >> 4) & 0x0f) << 8;
	mode->vsync_start = mode->vdisplay;
	mode->vsync_start += (dtd->part2.v_sync_off_width >> 4) & 0xf;
	mode->vsync_start += (dtd->part2.sync_off_width_high & 0x0c) << 2;
	mode->vsync_start += dtd->part2.v_sync_off_high & 0xc0;
	mode->vsync_end = mode->vsync_start +
		(dtd->part2.v_sync_off_width & 0xf);
	mode->vsync_end += (dtd->part2.sync_off_width_high & 0x3) << 4;
	mode->vtotal = mode->vdisplay + dtd->part1.v_blank;
	mode->vtotal += (dtd->part1.v_high & 0xf) << 8;

	mode->घड़ी = dtd->part1.घड़ी * 10;

	mode->flags &= ~(DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC);
	अगर (dtd->part2.dtd_flags & 0x2)
		mode->flags |= DRM_MODE_FLAG_PHSYNC;
	अगर (dtd->part2.dtd_flags & 0x4)
		mode->flags |= DRM_MODE_FLAG_PVSYNC;
पूर्ण

अटल bool psb_पूर्णांकel_sdvo_check_supp_encode(काष्ठा psb_पूर्णांकel_sdvo *psb_पूर्णांकel_sdvo)
अणु
	काष्ठा psb_पूर्णांकel_sdvo_encode encode;

	BUILD_BUG_ON(माप(encode) != 2);
	वापस psb_पूर्णांकel_sdvo_get_value(psb_पूर्णांकel_sdvo,
				  SDVO_CMD_GET_SUPP_ENCODE,
				  &encode, माप(encode));
पूर्ण

अटल bool psb_पूर्णांकel_sdvo_set_encode(काष्ठा psb_पूर्णांकel_sdvo *psb_पूर्णांकel_sdvo,
				  uपूर्णांक8_t mode)
अणु
	वापस psb_पूर्णांकel_sdvo_set_value(psb_पूर्णांकel_sdvo, SDVO_CMD_SET_ENCODE, &mode, 1);
पूर्ण

अटल bool psb_पूर्णांकel_sdvo_set_colorimetry(काष्ठा psb_पूर्णांकel_sdvo *psb_पूर्णांकel_sdvo,
				       uपूर्णांक8_t mode)
अणु
	वापस psb_पूर्णांकel_sdvo_set_value(psb_पूर्णांकel_sdvo, SDVO_CMD_SET_COLORIMETRY, &mode, 1);
पूर्ण

#अगर 0
अटल व्योम psb_पूर्णांकel_sdvo_dump_hdmi_buf(काष्ठा psb_पूर्णांकel_sdvo *psb_पूर्णांकel_sdvo)
अणु
	पूर्णांक i, j;
	uपूर्णांक8_t set_buf_index[2];
	uपूर्णांक8_t av_split;
	uपूर्णांक8_t buf_size;
	uपूर्णांक8_t buf[48];
	uपूर्णांक8_t *pos;

	psb_पूर्णांकel_sdvo_get_value(encoder, SDVO_CMD_GET_HBUF_AV_SPLIT, &av_split, 1);

	क्रम (i = 0; i <= av_split; i++) अणु
		set_buf_index[0] = i; set_buf_index[1] = 0;
		psb_पूर्णांकel_sdvo_ग_लिखो_cmd(encoder, SDVO_CMD_SET_HBUF_INDEX,
				     set_buf_index, 2);
		psb_पूर्णांकel_sdvo_ग_लिखो_cmd(encoder, SDVO_CMD_GET_HBUF_INFO, शून्य, 0);
		psb_पूर्णांकel_sdvo_पढ़ो_response(encoder, &buf_size, 1);

		pos = buf;
		क्रम (j = 0; j <= buf_size; j += 8) अणु
			psb_पूर्णांकel_sdvo_ग_लिखो_cmd(encoder, SDVO_CMD_GET_HBUF_DATA,
					     शून्य, 0);
			psb_पूर्णांकel_sdvo_पढ़ो_response(encoder, pos, 8);
			pos += 8;
		पूर्ण
	पूर्ण
पूर्ण
#पूर्ण_अगर

अटल bool psb_पूर्णांकel_sdvo_set_avi_infoframe(काष्ठा psb_पूर्णांकel_sdvo *psb_पूर्णांकel_sdvo)
अणु
	DRM_INFO("HDMI is not supported yet");

	वापस false;
पूर्ण

अटल bool psb_पूर्णांकel_sdvo_set_tv_क्रमmat(काष्ठा psb_पूर्णांकel_sdvo *psb_पूर्णांकel_sdvo)
अणु
	काष्ठा psb_पूर्णांकel_sdvo_tv_क्रमmat क्रमmat;
	uपूर्णांक32_t क्रमmat_map;

	क्रमmat_map = 1 << psb_पूर्णांकel_sdvo->tv_क्रमmat_index;
	स_रखो(&क्रमmat, 0, माप(क्रमmat));
	स_नकल(&क्रमmat, &क्रमmat_map, min(माप(क्रमmat), माप(क्रमmat_map)));

	BUILD_BUG_ON(माप(क्रमmat) != 6);
	वापस psb_पूर्णांकel_sdvo_set_value(psb_पूर्णांकel_sdvo,
				    SDVO_CMD_SET_TV_FORMAT,
				    &क्रमmat, माप(क्रमmat));
पूर्ण

अटल bool
psb_पूर्णांकel_sdvo_set_output_timings_from_mode(काष्ठा psb_पूर्णांकel_sdvo *psb_पूर्णांकel_sdvo,
					स्थिर काष्ठा drm_display_mode *mode)
अणु
	काष्ठा psb_पूर्णांकel_sdvo_dtd output_dtd;

	अगर (!psb_पूर्णांकel_sdvo_set_target_output(psb_पूर्णांकel_sdvo,
					  psb_पूर्णांकel_sdvo->attached_output))
		वापस false;

	psb_पूर्णांकel_sdvo_get_dtd_from_mode(&output_dtd, mode);
	अगर (!psb_पूर्णांकel_sdvo_set_output_timing(psb_पूर्णांकel_sdvo, &output_dtd))
		वापस false;

	वापस true;
पूर्ण

अटल bool
psb_पूर्णांकel_sdvo_set_input_timings_क्रम_mode(काष्ठा psb_पूर्णांकel_sdvo *psb_पूर्णांकel_sdvo,
					स्थिर काष्ठा drm_display_mode *mode,
					काष्ठा drm_display_mode *adjusted_mode)
अणु
	/* Reset the input timing to the screen. Assume always input 0. */
	अगर (!psb_पूर्णांकel_sdvo_set_target_input(psb_पूर्णांकel_sdvo))
		वापस false;

	अगर (!psb_पूर्णांकel_sdvo_create_preferred_input_timing(psb_पूर्णांकel_sdvo,
						      mode->घड़ी / 10,
						      mode->hdisplay,
						      mode->vdisplay))
		वापस false;

	अगर (!psb_पूर्णांकel_sdvo_get_preferred_input_timing(psb_पूर्णांकel_sdvo,
						   &psb_पूर्णांकel_sdvo->input_dtd))
		वापस false;

	psb_पूर्णांकel_sdvo_get_mode_from_dtd(adjusted_mode, &psb_पूर्णांकel_sdvo->input_dtd);

	drm_mode_set_crtcinfo(adjusted_mode, 0);
	वापस true;
पूर्ण

अटल bool psb_पूर्णांकel_sdvo_mode_fixup(काष्ठा drm_encoder *encoder,
				  स्थिर काष्ठा drm_display_mode *mode,
				  काष्ठा drm_display_mode *adjusted_mode)
अणु
	काष्ठा psb_पूर्णांकel_sdvo *psb_पूर्णांकel_sdvo = to_psb_पूर्णांकel_sdvo(encoder);

	/* We need to स्थिरruct preferred input timings based on our
	 * output timings.  To करो that, we have to set the output
	 * timings, even though this isn't really the right place in
	 * the sequence to करो it. Oh well.
	 */
	अगर (psb_पूर्णांकel_sdvo->is_tv) अणु
		अगर (!psb_पूर्णांकel_sdvo_set_output_timings_from_mode(psb_पूर्णांकel_sdvo, mode))
			वापस false;

		(व्योम) psb_पूर्णांकel_sdvo_set_input_timings_क्रम_mode(psb_पूर्णांकel_sdvo,
							     mode,
							     adjusted_mode);
	पूर्ण अन्यथा अगर (psb_पूर्णांकel_sdvo->is_lvds) अणु
		अगर (!psb_पूर्णांकel_sdvo_set_output_timings_from_mode(psb_पूर्णांकel_sdvo,
							     psb_पूर्णांकel_sdvo->sdvo_lvds_fixed_mode))
			वापस false;

		(व्योम) psb_पूर्णांकel_sdvo_set_input_timings_क्रम_mode(psb_पूर्णांकel_sdvo,
							     mode,
							     adjusted_mode);
	पूर्ण

	/* Make the CRTC code factor in the SDVO pixel multiplier.  The
	 * SDVO device will factor out the multiplier during mode_set.
	 */
	psb_पूर्णांकel_sdvo->pixel_multiplier =
		psb_पूर्णांकel_sdvo_get_pixel_multiplier(adjusted_mode);
	adjusted_mode->घड़ी *= psb_पूर्णांकel_sdvo->pixel_multiplier;

	वापस true;
पूर्ण

अटल व्योम psb_पूर्णांकel_sdvo_mode_set(काष्ठा drm_encoder *encoder,
				काष्ठा drm_display_mode *mode,
				काष्ठा drm_display_mode *adjusted_mode)
अणु
	काष्ठा drm_device *dev = encoder->dev;
	काष्ठा drm_crtc *crtc = encoder->crtc;
	काष्ठा gma_crtc *gma_crtc = to_gma_crtc(crtc);
	काष्ठा psb_पूर्णांकel_sdvo *psb_पूर्णांकel_sdvo = to_psb_पूर्णांकel_sdvo(encoder);
	u32 sdvox;
	काष्ठा psb_पूर्णांकel_sdvo_in_out_map in_out;
	काष्ठा psb_पूर्णांकel_sdvo_dtd input_dtd;
	पूर्णांक rate;
	पूर्णांक need_aux = IS_MRST(dev) ? 1 : 0;

	अगर (!mode)
		वापस;

	/* First, set the input mapping क्रम the first input to our controlled
	 * output. This is only correct अगर we're a single-input device, in
	 * which हाल the first input is the output from the appropriate SDVO
	 * channel on the motherboard.  In a two-input device, the first input
	 * will be SDVOB and the second SDVOC.
	 */
	in_out.in0 = psb_पूर्णांकel_sdvo->attached_output;
	in_out.in1 = 0;

	psb_पूर्णांकel_sdvo_set_value(psb_पूर्णांकel_sdvo,
			     SDVO_CMD_SET_IN_OUT_MAP,
			     &in_out, माप(in_out));

	/* Set the output timings to the screen */
	अगर (!psb_पूर्णांकel_sdvo_set_target_output(psb_पूर्णांकel_sdvo,
					  psb_पूर्णांकel_sdvo->attached_output))
		वापस;

	/* We have tried to get input timing in mode_fixup, and filled पूर्णांकo
	 * adjusted_mode.
	 */
	अगर (psb_पूर्णांकel_sdvo->is_tv || psb_पूर्णांकel_sdvo->is_lvds) अणु
		input_dtd = psb_पूर्णांकel_sdvo->input_dtd;
	पूर्ण अन्यथा अणु
		/* Set the output timing to the screen */
		अगर (!psb_पूर्णांकel_sdvo_set_target_output(psb_पूर्णांकel_sdvo,
						  psb_पूर्णांकel_sdvo->attached_output))
			वापस;

		psb_पूर्णांकel_sdvo_get_dtd_from_mode(&input_dtd, adjusted_mode);
		(व्योम) psb_पूर्णांकel_sdvo_set_output_timing(psb_पूर्णांकel_sdvo, &input_dtd);
	पूर्ण

	/* Set the input timing to the screen. Assume always input 0. */
	अगर (!psb_पूर्णांकel_sdvo_set_target_input(psb_पूर्णांकel_sdvo))
		वापस;

	अगर (psb_पूर्णांकel_sdvo->has_hdmi_monitor) अणु
		psb_पूर्णांकel_sdvo_set_encode(psb_पूर्णांकel_sdvo, SDVO_ENCODE_HDMI);
		psb_पूर्णांकel_sdvo_set_colorimetry(psb_पूर्णांकel_sdvo,
					   SDVO_COLORIMETRY_RGB256);
		psb_पूर्णांकel_sdvo_set_avi_infoframe(psb_पूर्णांकel_sdvo);
	पूर्ण अन्यथा
		psb_पूर्णांकel_sdvo_set_encode(psb_पूर्णांकel_sdvo, SDVO_ENCODE_DVI);

	अगर (psb_पूर्णांकel_sdvo->is_tv &&
	    !psb_पूर्णांकel_sdvo_set_tv_क्रमmat(psb_पूर्णांकel_sdvo))
		वापस;

	(व्योम) psb_पूर्णांकel_sdvo_set_input_timing(psb_पूर्णांकel_sdvo, &input_dtd);

	चयन (psb_पूर्णांकel_sdvo->pixel_multiplier) अणु
	शेष:
	हाल 1: rate = SDVO_CLOCK_RATE_MULT_1X; अवरोध;
	हाल 2: rate = SDVO_CLOCK_RATE_MULT_2X; अवरोध;
	हाल 4: rate = SDVO_CLOCK_RATE_MULT_4X; अवरोध;
	पूर्ण
	अगर (!psb_पूर्णांकel_sdvo_set_घड़ी_rate_mult(psb_पूर्णांकel_sdvo, rate))
		वापस;

	/* Set the SDVO control regs. */
	अगर (need_aux)
		sdvox = REG_READ_AUX(psb_पूर्णांकel_sdvo->sdvo_reg);
	अन्यथा
		sdvox = REG_READ(psb_पूर्णांकel_sdvo->sdvo_reg);

	चयन (psb_पूर्णांकel_sdvo->sdvo_reg) अणु
	हाल SDVOB:
		sdvox &= SDVOB_PRESERVE_MASK;
		अवरोध;
	हाल SDVOC:
		sdvox &= SDVOC_PRESERVE_MASK;
		अवरोध;
	पूर्ण
	sdvox |= (9 << 19) | SDVO_BORDER_ENABLE;

	अगर (gma_crtc->pipe == 1)
		sdvox |= SDVO_PIPE_B_SELECT;
	अगर (psb_पूर्णांकel_sdvo->has_hdmi_audio)
		sdvox |= SDVO_AUDIO_ENABLE;

	/* FIXME: Check अगर this is needed क्रम PSB
	sdvox |= (pixel_multiplier - 1) << SDVO_PORT_MULTIPLY_SHIFT;
	*/

	अगर (input_dtd.part2.sdvo_flags & SDVO_NEED_TO_STALL)
		sdvox |= SDVO_STALL_SELECT;
	psb_पूर्णांकel_sdvo_ग_लिखो_sdvox(psb_पूर्णांकel_sdvo, sdvox);
पूर्ण

अटल व्योम psb_पूर्णांकel_sdvo_dpms(काष्ठा drm_encoder *encoder, पूर्णांक mode)
अणु
	काष्ठा drm_device *dev = encoder->dev;
	काष्ठा psb_पूर्णांकel_sdvo *psb_पूर्णांकel_sdvo = to_psb_पूर्णांकel_sdvo(encoder);
	u32 temp;
	पूर्णांक i;
	पूर्णांक need_aux = IS_MRST(dev) ? 1 : 0;

	चयन (mode) अणु
	हाल DRM_MODE_DPMS_ON:
		DRM_DEBUG("DPMS_ON");
		अवरोध;
	हाल DRM_MODE_DPMS_OFF:
		DRM_DEBUG("DPMS_OFF");
		अवरोध;
	शेष:
		DRM_DEBUG("DPMS: %d", mode);
	पूर्ण

	अगर (mode != DRM_MODE_DPMS_ON) अणु
		psb_पूर्णांकel_sdvo_set_active_outमाला_दो(psb_पूर्णांकel_sdvo, 0);
		अगर (0)
			psb_पूर्णांकel_sdvo_set_encoder_घातer_state(psb_पूर्णांकel_sdvo, mode);

		अगर (mode == DRM_MODE_DPMS_OFF) अणु
			अगर (need_aux)
				temp = REG_READ_AUX(psb_पूर्णांकel_sdvo->sdvo_reg);
			अन्यथा
				temp = REG_READ(psb_पूर्णांकel_sdvo->sdvo_reg);

			अगर ((temp & SDVO_ENABLE) != 0) अणु
				psb_पूर्णांकel_sdvo_ग_लिखो_sdvox(psb_पूर्णांकel_sdvo, temp & ~SDVO_ENABLE);
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		bool input1, input2;
		u8 status;

		अगर (need_aux)
			temp = REG_READ_AUX(psb_पूर्णांकel_sdvo->sdvo_reg);
		अन्यथा
			temp = REG_READ(psb_पूर्णांकel_sdvo->sdvo_reg);

		अगर ((temp & SDVO_ENABLE) == 0)
			psb_पूर्णांकel_sdvo_ग_लिखो_sdvox(psb_पूर्णांकel_sdvo, temp | SDVO_ENABLE);

		क्रम (i = 0; i < 2; i++)
			gma_रुको_क्रम_vblank(dev);

		status = psb_पूर्णांकel_sdvo_get_trained_inमाला_दो(psb_पूर्णांकel_sdvo, &input1, &input2);
		/* Warn अगर the device reported failure to sync.
		 * A lot of SDVO devices fail to notअगरy of sync, but it's
		 * a given it the status is a success, we succeeded.
		 */
		अगर (status == SDVO_CMD_STATUS_SUCCESS && !input1) अणु
			DRM_DEBUG_KMS("First %s output reported failure to "
					"sync\n", SDVO_NAME(psb_पूर्णांकel_sdvo));
		पूर्ण

		अगर (0)
			psb_पूर्णांकel_sdvo_set_encoder_घातer_state(psb_पूर्णांकel_sdvo, mode);
		psb_पूर्णांकel_sdvo_set_active_outमाला_दो(psb_पूर्णांकel_sdvo, psb_पूर्णांकel_sdvo->attached_output);
	पूर्ण
	वापस;
पूर्ण

अटल क्रमागत drm_mode_status psb_पूर्णांकel_sdvo_mode_valid(काष्ठा drm_connector *connector,
				 काष्ठा drm_display_mode *mode)
अणु
	काष्ठा psb_पूर्णांकel_sdvo *psb_पूर्णांकel_sdvo = पूर्णांकel_attached_sdvo(connector);

	अगर (mode->flags & DRM_MODE_FLAG_DBLSCAN)
		वापस MODE_NO_DBLESCAN;

	अगर (psb_पूर्णांकel_sdvo->pixel_घड़ी_min > mode->घड़ी)
		वापस MODE_CLOCK_LOW;

	अगर (psb_पूर्णांकel_sdvo->pixel_घड़ी_max < mode->घड़ी)
		वापस MODE_CLOCK_HIGH;

	अगर (psb_पूर्णांकel_sdvo->is_lvds) अणु
		अगर (mode->hdisplay > psb_पूर्णांकel_sdvo->sdvo_lvds_fixed_mode->hdisplay)
			वापस MODE_PANEL;

		अगर (mode->vdisplay > psb_पूर्णांकel_sdvo->sdvo_lvds_fixed_mode->vdisplay)
			वापस MODE_PANEL;
	पूर्ण

	वापस MODE_OK;
पूर्ण

अटल bool psb_पूर्णांकel_sdvo_get_capabilities(काष्ठा psb_पूर्णांकel_sdvo *psb_पूर्णांकel_sdvo, काष्ठा psb_पूर्णांकel_sdvo_caps *caps)
अणु
	BUILD_BUG_ON(माप(*caps) != 8);
	अगर (!psb_पूर्णांकel_sdvo_get_value(psb_पूर्णांकel_sdvo,
				  SDVO_CMD_GET_DEVICE_CAPS,
				  caps, माप(*caps)))
		वापस false;

	DRM_DEBUG_KMS("SDVO capabilities:\n"
		      "  vendor_id: %d\n"
		      "  device_id: %d\n"
		      "  device_rev_id: %d\n"
		      "  sdvo_version_major: %d\n"
		      "  sdvo_version_minor: %d\n"
		      "  sdvo_inputs_mask: %d\n"
		      "  smooth_scaling: %d\n"
		      "  sharp_scaling: %d\n"
		      "  up_scaling: %d\n"
		      "  down_scaling: %d\n"
		      "  stall_support: %d\n"
		      "  output_flags: %d\n",
		      caps->venकरोr_id,
		      caps->device_id,
		      caps->device_rev_id,
		      caps->sdvo_version_major,
		      caps->sdvo_version_minor,
		      caps->sdvo_inमाला_दो_mask,
		      caps->smooth_scaling,
		      caps->sharp_scaling,
		      caps->up_scaling,
		      caps->करोwn_scaling,
		      caps->stall_support,
		      caps->output_flags);

	वापस true;
पूर्ण

अटल bool
psb_पूर्णांकel_sdvo_multअगरunc_encoder(काष्ठा psb_पूर्णांकel_sdvo *psb_पूर्णांकel_sdvo)
अणु
	/* Is there more than one type of output? */
	पूर्णांक caps = psb_पूर्णांकel_sdvo->caps.output_flags & 0xf;
	वापस caps & -caps;
पूर्ण

अटल काष्ठा edid *
psb_पूर्णांकel_sdvo_get_edid(काष्ठा drm_connector *connector)
अणु
	काष्ठा psb_पूर्णांकel_sdvo *sdvo = पूर्णांकel_attached_sdvo(connector);
	वापस drm_get_edid(connector, &sdvo->ddc);
पूर्ण

/* Mac mini hack -- use the same DDC as the analog connector */
अटल काष्ठा edid *
psb_पूर्णांकel_sdvo_get_analog_edid(काष्ठा drm_connector *connector)
अणु
	काष्ठा drm_psb_निजी *dev_priv = connector->dev->dev_निजी;

	वापस drm_get_edid(connector,
			    &dev_priv->gmbus[dev_priv->crt_ddc_pin].adapter);
पूर्ण

अटल क्रमागत drm_connector_status
psb_पूर्णांकel_sdvo_hdmi_sink_detect(काष्ठा drm_connector *connector)
अणु
	काष्ठा psb_पूर्णांकel_sdvo *psb_पूर्णांकel_sdvo = पूर्णांकel_attached_sdvo(connector);
	क्रमागत drm_connector_status status;
	काष्ठा edid *edid;

	edid = psb_पूर्णांकel_sdvo_get_edid(connector);

	अगर (edid == शून्य && psb_पूर्णांकel_sdvo_multअगरunc_encoder(psb_पूर्णांकel_sdvo)) अणु
		u8 ddc, saved_ddc = psb_पूर्णांकel_sdvo->ddc_bus;

		/*
		 * Don't use the 1 as the argument of DDC bus चयन to get
		 * the EDID. It is used क्रम SDVO SPD ROM.
		 */
		क्रम (ddc = psb_पूर्णांकel_sdvo->ddc_bus >> 1; ddc > 1; ddc >>= 1) अणु
			psb_पूर्णांकel_sdvo->ddc_bus = ddc;
			edid = psb_पूर्णांकel_sdvo_get_edid(connector);
			अगर (edid)
				अवरोध;
		पूर्ण
		/*
		 * If we found the EDID on the other bus,
		 * assume that is the correct DDC bus.
		 */
		अगर (edid == शून्य)
			psb_पूर्णांकel_sdvo->ddc_bus = saved_ddc;
	पूर्ण

	/*
	 * When there is no edid and no monitor is connected with VGA
	 * port, try to use the CRT ddc to पढ़ो the EDID क्रम DVI-connector.
	 */
	अगर (edid == शून्य)
		edid = psb_पूर्णांकel_sdvo_get_analog_edid(connector);

	status = connector_status_unknown;
	अगर (edid != शून्य) अणु
		/* DDC bus is shared, match EDID to connector type */
		अगर (edid->input & DRM_EDID_INPUT_DIGITAL) अणु
			status = connector_status_connected;
			अगर (psb_पूर्णांकel_sdvo->is_hdmi) अणु
				psb_पूर्णांकel_sdvo->has_hdmi_monitor = drm_detect_hdmi_monitor(edid);
				psb_पूर्णांकel_sdvo->has_hdmi_audio = drm_detect_monitor_audio(edid);
			पूर्ण
		पूर्ण अन्यथा
			status = connector_status_disconnected;
		kमुक्त(edid);
	पूर्ण

	अगर (status == connector_status_connected) अणु
		काष्ठा psb_पूर्णांकel_sdvo_connector *psb_पूर्णांकel_sdvo_connector = to_psb_पूर्णांकel_sdvo_connector(connector);
		अगर (psb_पूर्णांकel_sdvo_connector->क्रमce_audio)
			psb_पूर्णांकel_sdvo->has_hdmi_audio = psb_पूर्णांकel_sdvo_connector->क्रमce_audio > 0;
	पूर्ण

	वापस status;
पूर्ण

अटल क्रमागत drm_connector_status
psb_पूर्णांकel_sdvo_detect(काष्ठा drm_connector *connector, bool क्रमce)
अणु
	uपूर्णांक16_t response;
	काष्ठा psb_पूर्णांकel_sdvo *psb_पूर्णांकel_sdvo = पूर्णांकel_attached_sdvo(connector);
	काष्ठा psb_पूर्णांकel_sdvo_connector *psb_पूर्णांकel_sdvo_connector = to_psb_पूर्णांकel_sdvo_connector(connector);
	क्रमागत drm_connector_status ret;

	अगर (!psb_पूर्णांकel_sdvo_ग_लिखो_cmd(psb_पूर्णांकel_sdvo,
				  SDVO_CMD_GET_ATTACHED_DISPLAYS, शून्य, 0))
		वापस connector_status_unknown;

	/* add 30ms delay when the output type might be TV */
	अगर (psb_पूर्णांकel_sdvo->caps.output_flags &
	    (SDVO_OUTPUT_SVID0 | SDVO_OUTPUT_CVBS0))
		mdelay(30);

	अगर (!psb_पूर्णांकel_sdvo_पढ़ो_response(psb_पूर्णांकel_sdvo, &response, 2))
		वापस connector_status_unknown;

	DRM_DEBUG_KMS("SDVO response %d %d [%x]\n",
		      response & 0xff, response >> 8,
		      psb_पूर्णांकel_sdvo_connector->output_flag);

	अगर (response == 0)
		वापस connector_status_disconnected;

	psb_पूर्णांकel_sdvo->attached_output = response;

	psb_पूर्णांकel_sdvo->has_hdmi_monitor = false;
	psb_पूर्णांकel_sdvo->has_hdmi_audio = false;

	अगर ((psb_पूर्णांकel_sdvo_connector->output_flag & response) == 0)
		ret = connector_status_disconnected;
	अन्यथा अगर (IS_TMDS(psb_पूर्णांकel_sdvo_connector))
		ret = psb_पूर्णांकel_sdvo_hdmi_sink_detect(connector);
	अन्यथा अणु
		काष्ठा edid *edid;

		/* अगर we have an edid check it matches the connection */
		edid = psb_पूर्णांकel_sdvo_get_edid(connector);
		अगर (edid == शून्य)
			edid = psb_पूर्णांकel_sdvo_get_analog_edid(connector);
		अगर (edid != शून्य) अणु
			अगर (edid->input & DRM_EDID_INPUT_DIGITAL)
				ret = connector_status_disconnected;
			अन्यथा
				ret = connector_status_connected;
			kमुक्त(edid);
		पूर्ण अन्यथा
			ret = connector_status_connected;
	पूर्ण

	/* May update encoder flag क्रम like घड़ी क्रम SDVO TV, etc.*/
	अगर (ret == connector_status_connected) अणु
		psb_पूर्णांकel_sdvo->is_tv = false;
		psb_पूर्णांकel_sdvo->is_lvds = false;
		psb_पूर्णांकel_sdvo->base.needs_tv_घड़ी = false;

		अगर (response & SDVO_TV_MASK) अणु
			psb_पूर्णांकel_sdvo->is_tv = true;
			psb_पूर्णांकel_sdvo->base.needs_tv_घड़ी = true;
		पूर्ण
		अगर (response & SDVO_LVDS_MASK)
			psb_पूर्णांकel_sdvo->is_lvds = psb_पूर्णांकel_sdvo->sdvo_lvds_fixed_mode != शून्य;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम psb_पूर्णांकel_sdvo_get_ddc_modes(काष्ठा drm_connector *connector)
अणु
	काष्ठा edid *edid;

	/* set the bus चयन and get the modes */
	edid = psb_पूर्णांकel_sdvo_get_edid(connector);

	/*
	 * Mac mini hack.  On this device, the DVI-I connector shares one DDC
	 * link between analog and digital outमाला_दो. So, अगर the regular SDVO
	 * DDC fails, check to see अगर the analog output is disconnected, in
	 * which हाल we'll look there क्रम the digital DDC data.
	 */
	अगर (edid == शून्य)
		edid = psb_पूर्णांकel_sdvo_get_analog_edid(connector);

	अगर (edid != शून्य) अणु
		काष्ठा psb_पूर्णांकel_sdvo_connector *psb_पूर्णांकel_sdvo_connector = to_psb_पूर्णांकel_sdvo_connector(connector);
		bool monitor_is_digital = !!(edid->input & DRM_EDID_INPUT_DIGITAL);
		bool connector_is_digital = !!IS_TMDS(psb_पूर्णांकel_sdvo_connector);

		अगर (connector_is_digital == monitor_is_digital) अणु
			drm_connector_update_edid_property(connector, edid);
			drm_add_edid_modes(connector, edid);
		पूर्ण

		kमुक्त(edid);
	पूर्ण
पूर्ण

/*
 * Set of SDVO TV modes.
 * Note!  This is in reply order (see loop in get_tv_modes).
 * XXX: all 60Hz refresh?
 */
अटल स्थिर काष्ठा drm_display_mode sdvo_tv_modes[] = अणु
	अणु DRM_MODE("320x200", DRM_MODE_TYPE_DRIVER, 5815, 320, 321, 384,
		   416, 0, 200, 201, 232, 233, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC) पूर्ण,
	अणु DRM_MODE("320x240", DRM_MODE_TYPE_DRIVER, 6814, 320, 321, 384,
		   416, 0, 240, 241, 272, 273, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC) पूर्ण,
	अणु DRM_MODE("400x300", DRM_MODE_TYPE_DRIVER, 9910, 400, 401, 464,
		   496, 0, 300, 301, 332, 333, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC) पूर्ण,
	अणु DRM_MODE("640x350", DRM_MODE_TYPE_DRIVER, 16913, 640, 641, 704,
		   736, 0, 350, 351, 382, 383, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC) पूर्ण,
	अणु DRM_MODE("640x400", DRM_MODE_TYPE_DRIVER, 19121, 640, 641, 704,
		   736, 0, 400, 401, 432, 433, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC) पूर्ण,
	अणु DRM_MODE("640x480", DRM_MODE_TYPE_DRIVER, 22654, 640, 641, 704,
		   736, 0, 480, 481, 512, 513, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC) पूर्ण,
	अणु DRM_MODE("704x480", DRM_MODE_TYPE_DRIVER, 24624, 704, 705, 768,
		   800, 0, 480, 481, 512, 513, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC) पूर्ण,
	अणु DRM_MODE("704x576", DRM_MODE_TYPE_DRIVER, 29232, 704, 705, 768,
		   800, 0, 576, 577, 608, 609, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC) पूर्ण,
	अणु DRM_MODE("720x350", DRM_MODE_TYPE_DRIVER, 18751, 720, 721, 784,
		   816, 0, 350, 351, 382, 383, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC) पूर्ण,
	अणु DRM_MODE("720x400", DRM_MODE_TYPE_DRIVER, 21199, 720, 721, 784,
		   816, 0, 400, 401, 432, 433, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC) पूर्ण,
	अणु DRM_MODE("720x480", DRM_MODE_TYPE_DRIVER, 25116, 720, 721, 784,
		   816, 0, 480, 481, 512, 513, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC) पूर्ण,
	अणु DRM_MODE("720x540", DRM_MODE_TYPE_DRIVER, 28054, 720, 721, 784,
		   816, 0, 540, 541, 572, 573, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC) पूर्ण,
	अणु DRM_MODE("720x576", DRM_MODE_TYPE_DRIVER, 29816, 720, 721, 784,
		   816, 0, 576, 577, 608, 609, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC) पूर्ण,
	अणु DRM_MODE("768x576", DRM_MODE_TYPE_DRIVER, 31570, 768, 769, 832,
		   864, 0, 576, 577, 608, 609, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC) पूर्ण,
	अणु DRM_MODE("800x600", DRM_MODE_TYPE_DRIVER, 34030, 800, 801, 864,
		   896, 0, 600, 601, 632, 633, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC) पूर्ण,
	अणु DRM_MODE("832x624", DRM_MODE_TYPE_DRIVER, 36581, 832, 833, 896,
		   928, 0, 624, 625, 656, 657, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC) पूर्ण,
	अणु DRM_MODE("920x766", DRM_MODE_TYPE_DRIVER, 48707, 920, 921, 984,
		   1016, 0, 766, 767, 798, 799, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC) पूर्ण,
	अणु DRM_MODE("1024x768", DRM_MODE_TYPE_DRIVER, 53827, 1024, 1025, 1088,
		   1120, 0, 768, 769, 800, 801, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC) पूर्ण,
	अणु DRM_MODE("1280x1024", DRM_MODE_TYPE_DRIVER, 87265, 1280, 1281, 1344,
		   1376, 0, 1024, 1025, 1056, 1057, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC) पूर्ण,
पूर्ण;

अटल व्योम psb_पूर्णांकel_sdvo_get_tv_modes(काष्ठा drm_connector *connector)
अणु
	काष्ठा psb_पूर्णांकel_sdvo *psb_पूर्णांकel_sdvo = पूर्णांकel_attached_sdvo(connector);
	काष्ठा psb_पूर्णांकel_sdvo_sdtv_resolution_request tv_res;
	uपूर्णांक32_t reply = 0, क्रमmat_map = 0;
	पूर्णांक i;

	/* Read the list of supported input resolutions क्रम the selected TV
	 * क्रमmat.
	 */
	क्रमmat_map = 1 << psb_पूर्णांकel_sdvo->tv_क्रमmat_index;
	स_नकल(&tv_res, &क्रमmat_map,
	       min(माप(क्रमmat_map), माप(काष्ठा psb_पूर्णांकel_sdvo_sdtv_resolution_request)));

	अगर (!psb_पूर्णांकel_sdvo_set_target_output(psb_पूर्णांकel_sdvo, psb_पूर्णांकel_sdvo->attached_output))
		वापस;

	BUILD_BUG_ON(माप(tv_res) != 3);
	अगर (!psb_पूर्णांकel_sdvo_ग_लिखो_cmd(psb_पूर्णांकel_sdvo,
				  SDVO_CMD_GET_SDTV_RESOLUTION_SUPPORT,
				  &tv_res, माप(tv_res)))
		वापस;
	अगर (!psb_पूर्णांकel_sdvo_पढ़ो_response(psb_पूर्णांकel_sdvo, &reply, 3))
		वापस;

	क्रम (i = 0; i < ARRAY_SIZE(sdvo_tv_modes); i++)
		अगर (reply & (1 << i)) अणु
			काष्ठा drm_display_mode *nmode;
			nmode = drm_mode_duplicate(connector->dev,
						   &sdvo_tv_modes[i]);
			अगर (nmode)
				drm_mode_probed_add(connector, nmode);
		पूर्ण
पूर्ण

अटल व्योम psb_पूर्णांकel_sdvo_get_lvds_modes(काष्ठा drm_connector *connector)
अणु
	काष्ठा psb_पूर्णांकel_sdvo *psb_पूर्णांकel_sdvo = पूर्णांकel_attached_sdvo(connector);
	काष्ठा drm_psb_निजी *dev_priv = connector->dev->dev_निजी;
	काष्ठा drm_display_mode *newmode;

	/*
	 * Attempt to get the mode list from DDC.
	 * Assume that the preferred modes are
	 * arranged in priority order.
	 */
	psb_पूर्णांकel_ddc_get_modes(connector, psb_पूर्णांकel_sdvo->i2c);
	अगर (list_empty(&connector->probed_modes) == false)
		जाओ end;

	/* Fetch modes from VBT */
	अगर (dev_priv->sdvo_lvds_vbt_mode != शून्य) अणु
		newmode = drm_mode_duplicate(connector->dev,
					     dev_priv->sdvo_lvds_vbt_mode);
		अगर (newmode != शून्य) अणु
			/* Guarantee the mode is preferred */
			newmode->type = (DRM_MODE_TYPE_PREFERRED |
					 DRM_MODE_TYPE_DRIVER);
			drm_mode_probed_add(connector, newmode);
		पूर्ण
	पूर्ण

end:
	list_क्रम_each_entry(newmode, &connector->probed_modes, head) अणु
		अगर (newmode->type & DRM_MODE_TYPE_PREFERRED) अणु
			psb_पूर्णांकel_sdvo->sdvo_lvds_fixed_mode =
				drm_mode_duplicate(connector->dev, newmode);

			drm_mode_set_crtcinfo(psb_पूर्णांकel_sdvo->sdvo_lvds_fixed_mode,
					      0);

			psb_पूर्णांकel_sdvo->is_lvds = true;
			अवरोध;
		पूर्ण
	पूर्ण

पूर्ण

अटल पूर्णांक psb_पूर्णांकel_sdvo_get_modes(काष्ठा drm_connector *connector)
अणु
	काष्ठा psb_पूर्णांकel_sdvo_connector *psb_पूर्णांकel_sdvo_connector = to_psb_पूर्णांकel_sdvo_connector(connector);

	अगर (IS_TV(psb_पूर्णांकel_sdvo_connector))
		psb_पूर्णांकel_sdvo_get_tv_modes(connector);
	अन्यथा अगर (IS_LVDS(psb_पूर्णांकel_sdvo_connector))
		psb_पूर्णांकel_sdvo_get_lvds_modes(connector);
	अन्यथा
		psb_पूर्णांकel_sdvo_get_ddc_modes(connector);

	वापस !list_empty(&connector->probed_modes);
पूर्ण

अटल व्योम psb_पूर्णांकel_sdvo_destroy(काष्ठा drm_connector *connector)
अणु
	drm_connector_unरेजिस्टर(connector);
	drm_connector_cleanup(connector);
	kमुक्त(connector);
पूर्ण

अटल bool psb_पूर्णांकel_sdvo_detect_hdmi_audio(काष्ठा drm_connector *connector)
अणु
	काष्ठा psb_पूर्णांकel_sdvo *psb_पूर्णांकel_sdvo = पूर्णांकel_attached_sdvo(connector);
	काष्ठा edid *edid;
	bool has_audio = false;

	अगर (!psb_पूर्णांकel_sdvo->is_hdmi)
		वापस false;

	edid = psb_पूर्णांकel_sdvo_get_edid(connector);
	अगर (edid != शून्य && edid->input & DRM_EDID_INPUT_DIGITAL)
		has_audio = drm_detect_monitor_audio(edid);

	वापस has_audio;
पूर्ण

अटल पूर्णांक
psb_पूर्णांकel_sdvo_set_property(काष्ठा drm_connector *connector,
			काष्ठा drm_property *property,
			uपूर्णांक64_t val)
अणु
	काष्ठा psb_पूर्णांकel_sdvo *psb_पूर्णांकel_sdvo = पूर्णांकel_attached_sdvo(connector);
	काष्ठा psb_पूर्णांकel_sdvo_connector *psb_पूर्णांकel_sdvo_connector = to_psb_पूर्णांकel_sdvo_connector(connector);
	काष्ठा drm_psb_निजी *dev_priv = connector->dev->dev_निजी;
	uपूर्णांक16_t temp_value;
	uपूर्णांक8_t cmd;
	पूर्णांक ret;

	ret = drm_object_property_set_value(&connector->base, property, val);
	अगर (ret)
		वापस ret;

	अगर (property == dev_priv->क्रमce_audio_property) अणु
		पूर्णांक i = val;
		bool has_audio;

		अगर (i == psb_पूर्णांकel_sdvo_connector->क्रमce_audio)
			वापस 0;

		psb_पूर्णांकel_sdvo_connector->क्रमce_audio = i;

		अगर (i == 0)
			has_audio = psb_पूर्णांकel_sdvo_detect_hdmi_audio(connector);
		अन्यथा
			has_audio = i > 0;

		अगर (has_audio == psb_पूर्णांकel_sdvo->has_hdmi_audio)
			वापस 0;

		psb_पूर्णांकel_sdvo->has_hdmi_audio = has_audio;
		जाओ करोne;
	पूर्ण

	अगर (property == dev_priv->broadcast_rgb_property) अणु
		अगर (val == !!psb_पूर्णांकel_sdvo->color_range)
			वापस 0;

		psb_पूर्णांकel_sdvo->color_range = val ? SDVO_COLOR_RANGE_16_235 : 0;
		जाओ करोne;
	पूर्ण

#घोषणा CHECK_PROPERTY(name, NAME) \
	अगर (psb_पूर्णांकel_sdvo_connector->name == property) अणु \
		अगर (psb_पूर्णांकel_sdvo_connector->cur_##name == temp_value) वापस 0; \
		अगर (psb_पूर्णांकel_sdvo_connector->max_##name < temp_value) वापस -EINVAL; \
		cmd = SDVO_CMD_SET_##NAME; \
		psb_पूर्णांकel_sdvo_connector->cur_##name = temp_value; \
		जाओ set_value; \
	पूर्ण

	अगर (property == psb_पूर्णांकel_sdvo_connector->tv_क्रमmat) अणु
		अगर (val >= ARRAY_SIZE(tv_क्रमmat_names))
			वापस -EINVAL;

		अगर (psb_पूर्णांकel_sdvo->tv_क्रमmat_index ==
		    psb_पूर्णांकel_sdvo_connector->tv_क्रमmat_supported[val])
			वापस 0;

		psb_पूर्णांकel_sdvo->tv_क्रमmat_index = psb_पूर्णांकel_sdvo_connector->tv_क्रमmat_supported[val];
		जाओ करोne;
	पूर्ण अन्यथा अगर (IS_TV_OR_LVDS(psb_पूर्णांकel_sdvo_connector)) अणु
		temp_value = val;
		अगर (psb_पूर्णांकel_sdvo_connector->left == property) अणु
			drm_object_property_set_value(&connector->base,
							 psb_पूर्णांकel_sdvo_connector->right, val);
			अगर (psb_पूर्णांकel_sdvo_connector->left_margin == temp_value)
				वापस 0;

			psb_पूर्णांकel_sdvo_connector->left_margin = temp_value;
			psb_पूर्णांकel_sdvo_connector->right_margin = temp_value;
			temp_value = psb_पूर्णांकel_sdvo_connector->max_hscan -
				psb_पूर्णांकel_sdvo_connector->left_margin;
			cmd = SDVO_CMD_SET_OVERSCAN_H;
			जाओ set_value;
		पूर्ण अन्यथा अगर (psb_पूर्णांकel_sdvo_connector->right == property) अणु
			drm_object_property_set_value(&connector->base,
							 psb_पूर्णांकel_sdvo_connector->left, val);
			अगर (psb_पूर्णांकel_sdvo_connector->right_margin == temp_value)
				वापस 0;

			psb_पूर्णांकel_sdvo_connector->left_margin = temp_value;
			psb_पूर्णांकel_sdvo_connector->right_margin = temp_value;
			temp_value = psb_पूर्णांकel_sdvo_connector->max_hscan -
				psb_पूर्णांकel_sdvo_connector->left_margin;
			cmd = SDVO_CMD_SET_OVERSCAN_H;
			जाओ set_value;
		पूर्ण अन्यथा अगर (psb_पूर्णांकel_sdvo_connector->top == property) अणु
			drm_object_property_set_value(&connector->base,
							 psb_पूर्णांकel_sdvo_connector->bottom, val);
			अगर (psb_पूर्णांकel_sdvo_connector->top_margin == temp_value)
				वापस 0;

			psb_पूर्णांकel_sdvo_connector->top_margin = temp_value;
			psb_पूर्णांकel_sdvo_connector->bottom_margin = temp_value;
			temp_value = psb_पूर्णांकel_sdvo_connector->max_vscan -
				psb_पूर्णांकel_sdvo_connector->top_margin;
			cmd = SDVO_CMD_SET_OVERSCAN_V;
			जाओ set_value;
		पूर्ण अन्यथा अगर (psb_पूर्णांकel_sdvo_connector->bottom == property) अणु
			drm_object_property_set_value(&connector->base,
							 psb_पूर्णांकel_sdvo_connector->top, val);
			अगर (psb_पूर्णांकel_sdvo_connector->bottom_margin == temp_value)
				वापस 0;

			psb_पूर्णांकel_sdvo_connector->top_margin = temp_value;
			psb_पूर्णांकel_sdvo_connector->bottom_margin = temp_value;
			temp_value = psb_पूर्णांकel_sdvo_connector->max_vscan -
				psb_पूर्णांकel_sdvo_connector->top_margin;
			cmd = SDVO_CMD_SET_OVERSCAN_V;
			जाओ set_value;
		पूर्ण
		CHECK_PROPERTY(hpos, HPOS)
		CHECK_PROPERTY(vpos, VPOS)
		CHECK_PROPERTY(saturation, SATURATION)
		CHECK_PROPERTY(contrast, CONTRAST)
		CHECK_PROPERTY(hue, HUE)
		CHECK_PROPERTY(brightness, BRIGHTNESS)
		CHECK_PROPERTY(sharpness, SHARPNESS)
		CHECK_PROPERTY(flicker_filter, FLICKER_FILTER)
		CHECK_PROPERTY(flicker_filter_2d, FLICKER_FILTER_2D)
		CHECK_PROPERTY(flicker_filter_adaptive, FLICKER_FILTER_ADAPTIVE)
		CHECK_PROPERTY(tv_chroma_filter, TV_CHROMA_FILTER)
		CHECK_PROPERTY(tv_luma_filter, TV_LUMA_FILTER)
		CHECK_PROPERTY(करोt_crawl, DOT_CRAWL)
	पूर्ण

	वापस -EINVAL; /* unknown property */

set_value:
	अगर (!psb_पूर्णांकel_sdvo_set_value(psb_पूर्णांकel_sdvo, cmd, &temp_value, 2))
		वापस -EIO;


करोne:
	अगर (psb_पूर्णांकel_sdvo->base.base.crtc) अणु
		काष्ठा drm_crtc *crtc = psb_पूर्णांकel_sdvo->base.base.crtc;
		drm_crtc_helper_set_mode(crtc, &crtc->mode, crtc->x,
					 crtc->y, crtc->primary->fb);
	पूर्ण

	वापस 0;
#अघोषित CHECK_PROPERTY
पूर्ण

अटल व्योम psb_पूर्णांकel_sdvo_save(काष्ठा drm_connector *connector)
अणु
	काष्ठा drm_device *dev = connector->dev;
	काष्ठा gma_encoder *gma_encoder = gma_attached_encoder(connector);
	काष्ठा psb_पूर्णांकel_sdvo *sdvo = to_psb_पूर्णांकel_sdvo(&gma_encoder->base);

	sdvo->saveSDVO = REG_READ(sdvo->sdvo_reg);
पूर्ण

अटल व्योम psb_पूर्णांकel_sdvo_restore(काष्ठा drm_connector *connector)
अणु
	काष्ठा drm_device *dev = connector->dev;
	काष्ठा drm_encoder *encoder = &gma_attached_encoder(connector)->base;
	काष्ठा psb_पूर्णांकel_sdvo *sdvo = to_psb_पूर्णांकel_sdvo(encoder);
	काष्ठा drm_crtc *crtc = encoder->crtc;

	REG_WRITE(sdvo->sdvo_reg, sdvo->saveSDVO);

	/* Force a full mode set on the crtc. We're supposed to have the
	   mode_config lock alपढ़ोy. */
	अगर (connector->status == connector_status_connected)
		drm_crtc_helper_set_mode(crtc, &crtc->mode, crtc->x, crtc->y,
					 शून्य);
पूर्ण

अटल स्थिर काष्ठा drm_encoder_helper_funcs psb_पूर्णांकel_sdvo_helper_funcs = अणु
	.dpms = psb_पूर्णांकel_sdvo_dpms,
	.mode_fixup = psb_पूर्णांकel_sdvo_mode_fixup,
	.prepare = gma_encoder_prepare,
	.mode_set = psb_पूर्णांकel_sdvo_mode_set,
	.commit = gma_encoder_commit,
पूर्ण;

अटल स्थिर काष्ठा drm_connector_funcs psb_पूर्णांकel_sdvo_connector_funcs = अणु
	.dpms = drm_helper_connector_dpms,
	.detect = psb_पूर्णांकel_sdvo_detect,
	.fill_modes = drm_helper_probe_single_connector_modes,
	.set_property = psb_पूर्णांकel_sdvo_set_property,
	.destroy = psb_पूर्णांकel_sdvo_destroy,
पूर्ण;

अटल स्थिर काष्ठा drm_connector_helper_funcs psb_पूर्णांकel_sdvo_connector_helper_funcs = अणु
	.get_modes = psb_पूर्णांकel_sdvo_get_modes,
	.mode_valid = psb_पूर्णांकel_sdvo_mode_valid,
	.best_encoder = gma_best_encoder,
पूर्ण;

अटल व्योम psb_पूर्णांकel_sdvo_enc_destroy(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा psb_पूर्णांकel_sdvo *psb_पूर्णांकel_sdvo = to_psb_पूर्णांकel_sdvo(encoder);

	अगर (psb_पूर्णांकel_sdvo->sdvo_lvds_fixed_mode != शून्य)
		drm_mode_destroy(encoder->dev,
				 psb_पूर्णांकel_sdvo->sdvo_lvds_fixed_mode);

	i2c_del_adapter(&psb_पूर्णांकel_sdvo->ddc);
	gma_encoder_destroy(encoder);
पूर्ण

अटल स्थिर काष्ठा drm_encoder_funcs psb_पूर्णांकel_sdvo_enc_funcs = अणु
	.destroy = psb_पूर्णांकel_sdvo_enc_destroy,
पूर्ण;

अटल व्योम
psb_पूर्णांकel_sdvo_guess_ddc_bus(काष्ठा psb_पूर्णांकel_sdvo *sdvo)
अणु
	/* FIXME: At the moment, ddc_bus = 2 is the only thing that works.
	 * We need to figure out अगर this is true क्रम all available poulsbo
	 * hardware, or अगर we need to fiddle with the guessing code above.
	 * The problem might go away अगर we can parse sdvo mappings from bios */
	sdvo->ddc_bus = 2;

#अगर 0
	uपूर्णांक16_t mask = 0;
	अचिन्हित पूर्णांक num_bits;

	/* Make a mask of outमाला_दो less than or equal to our own priority in the
	 * list.
	 */
	चयन (sdvo->controlled_output) अणु
	हाल SDVO_OUTPUT_LVDS1:
		mask |= SDVO_OUTPUT_LVDS1;
	हाल SDVO_OUTPUT_LVDS0:
		mask |= SDVO_OUTPUT_LVDS0;
	हाल SDVO_OUTPUT_TMDS1:
		mask |= SDVO_OUTPUT_TMDS1;
	हाल SDVO_OUTPUT_TMDS0:
		mask |= SDVO_OUTPUT_TMDS0;
	हाल SDVO_OUTPUT_RGB1:
		mask |= SDVO_OUTPUT_RGB1;
	हाल SDVO_OUTPUT_RGB0:
		mask |= SDVO_OUTPUT_RGB0;
		अवरोध;
	पूर्ण

	/* Count bits to find what number we are in the priority list. */
	mask &= sdvo->caps.output_flags;
	num_bits = hweight16(mask);
	/* If more than 3 outमाला_दो, शेष to DDC bus 3 क्रम now. */
	अगर (num_bits > 3)
		num_bits = 3;

	/* Corresponds to SDVO_CONTROL_BUS_DDCx */
	sdvo->ddc_bus = 1 << num_bits;
#पूर्ण_अगर
पूर्ण

/*
 * Choose the appropriate DDC bus क्रम control bus चयन command क्रम this
 * SDVO output based on the controlled output.
 *
 * DDC bus number assignment is in a priority order of RGB outमाला_दो, then TMDS
 * outमाला_दो, then LVDS outमाला_दो.
 */
अटल व्योम
psb_पूर्णांकel_sdvo_select_ddc_bus(काष्ठा drm_psb_निजी *dev_priv,
			  काष्ठा psb_पूर्णांकel_sdvo *sdvo, u32 reg)
अणु
	काष्ठा sdvo_device_mapping *mapping;

	अगर (IS_SDVOB(reg))
		mapping = &(dev_priv->sdvo_mappings[0]);
	अन्यथा
		mapping = &(dev_priv->sdvo_mappings[1]);

	अगर (mapping->initialized)
		sdvo->ddc_bus = 1 << ((mapping->ddc_pin & 0xf0) >> 4);
	अन्यथा
		psb_पूर्णांकel_sdvo_guess_ddc_bus(sdvo);
पूर्ण

अटल व्योम
psb_पूर्णांकel_sdvo_select_i2c_bus(काष्ठा drm_psb_निजी *dev_priv,
			  काष्ठा psb_पूर्णांकel_sdvo *sdvo, u32 reg)
अणु
	काष्ठा sdvo_device_mapping *mapping;
	u8 pin, speed;

	अगर (IS_SDVOB(reg))
		mapping = &dev_priv->sdvo_mappings[0];
	अन्यथा
		mapping = &dev_priv->sdvo_mappings[1];

	pin = GMBUS_PORT_DPB;
	speed = GMBUS_RATE_1MHZ >> 8;
	अगर (mapping->initialized) अणु
		pin = mapping->i2c_pin;
		speed = mapping->i2c_speed;
	पूर्ण

	अगर (pin < GMBUS_NUM_PORTS) अणु
		sdvo->i2c = &dev_priv->gmbus[pin].adapter;
		gma_पूर्णांकel_gmbus_set_speed(sdvo->i2c, speed);
		gma_पूर्णांकel_gmbus_क्रमce_bit(sdvo->i2c, true);
	पूर्ण अन्यथा
		sdvo->i2c = &dev_priv->gmbus[GMBUS_PORT_DPB].adapter;
पूर्ण

अटल bool
psb_पूर्णांकel_sdvo_is_hdmi_connector(काष्ठा psb_पूर्णांकel_sdvo *psb_पूर्णांकel_sdvo, पूर्णांक device)
अणु
	वापस psb_पूर्णांकel_sdvo_check_supp_encode(psb_पूर्णांकel_sdvo);
पूर्ण

अटल u8
psb_पूर्णांकel_sdvo_get_slave_addr(काष्ठा drm_device *dev, पूर्णांक sdvo_reg)
अणु
	काष्ठा drm_psb_निजी *dev_priv = dev->dev_निजी;
	काष्ठा sdvo_device_mapping *my_mapping, *other_mapping;

	अगर (IS_SDVOB(sdvo_reg)) अणु
		my_mapping = &dev_priv->sdvo_mappings[0];
		other_mapping = &dev_priv->sdvo_mappings[1];
	पूर्ण अन्यथा अणु
		my_mapping = &dev_priv->sdvo_mappings[1];
		other_mapping = &dev_priv->sdvo_mappings[0];
	पूर्ण

	/* If the BIOS described our SDVO device, take advantage of it. */
	अगर (my_mapping->slave_addr)
		वापस my_mapping->slave_addr;

	/* If the BIOS only described a dअगरferent SDVO device, use the
	 * address that it isn't using.
	 */
	अगर (other_mapping->slave_addr) अणु
		अगर (other_mapping->slave_addr == 0x70)
			वापस 0x72;
		अन्यथा
			वापस 0x70;
	पूर्ण

	/* No SDVO device info is found क्रम another DVO port,
	 * so use mapping assumption we had beक्रमe BIOS parsing.
	 */
	अगर (IS_SDVOB(sdvo_reg))
		वापस 0x70;
	अन्यथा
		वापस 0x72;
पूर्ण

अटल व्योम
psb_पूर्णांकel_sdvo_connector_init(काष्ठा psb_पूर्णांकel_sdvo_connector *connector,
			  काष्ठा psb_पूर्णांकel_sdvo *encoder)
अणु
	drm_connector_init(encoder->base.base.dev,
			   &connector->base.base,
			   &psb_पूर्णांकel_sdvo_connector_funcs,
			   connector->base.base.connector_type);

	drm_connector_helper_add(&connector->base.base,
				 &psb_पूर्णांकel_sdvo_connector_helper_funcs);

	connector->base.base.पूर्णांकerlace_allowed = 0;
	connector->base.base.द्विगुनscan_allowed = 0;
	connector->base.base.display_info.subpixel_order = SubPixelHorizontalRGB;

	connector->base.save = psb_पूर्णांकel_sdvo_save;
	connector->base.restore = psb_पूर्णांकel_sdvo_restore;

	gma_connector_attach_encoder(&connector->base, &encoder->base);
	drm_connector_रेजिस्टर(&connector->base.base);
पूर्ण

अटल व्योम
psb_पूर्णांकel_sdvo_add_hdmi_properties(काष्ठा psb_पूर्णांकel_sdvo_connector *connector)
अणु
	/* FIXME: We करोn't support HDMI at the moment
	काष्ठा drm_device *dev = connector->base.base.dev;

	पूर्णांकel_attach_क्रमce_audio_property(&connector->base.base);
	पूर्णांकel_attach_broadcast_rgb_property(&connector->base.base);
	*/
पूर्ण

अटल bool
psb_पूर्णांकel_sdvo_dvi_init(काष्ठा psb_पूर्णांकel_sdvo *psb_पूर्णांकel_sdvo, पूर्णांक device)
अणु
	काष्ठा drm_encoder *encoder = &psb_पूर्णांकel_sdvo->base.base;
	काष्ठा drm_connector *connector;
	काष्ठा gma_connector *पूर्णांकel_connector;
	काष्ठा psb_पूर्णांकel_sdvo_connector *psb_पूर्णांकel_sdvo_connector;

	psb_पूर्णांकel_sdvo_connector = kzalloc(माप(काष्ठा psb_पूर्णांकel_sdvo_connector), GFP_KERNEL);
	अगर (!psb_पूर्णांकel_sdvo_connector)
		वापस false;

	अगर (device == 0) अणु
		psb_पूर्णांकel_sdvo->controlled_output |= SDVO_OUTPUT_TMDS0;
		psb_पूर्णांकel_sdvo_connector->output_flag = SDVO_OUTPUT_TMDS0;
	पूर्ण अन्यथा अगर (device == 1) अणु
		psb_पूर्णांकel_sdvo->controlled_output |= SDVO_OUTPUT_TMDS1;
		psb_पूर्णांकel_sdvo_connector->output_flag = SDVO_OUTPUT_TMDS1;
	पूर्ण

	पूर्णांकel_connector = &psb_पूर्णांकel_sdvo_connector->base;
	connector = &पूर्णांकel_connector->base;
	// connector->polled = DRM_CONNECTOR_POLL_CONNECT | DRM_CONNECTOR_POLL_DISCONNECT;
	encoder->encoder_type = DRM_MODE_ENCODER_TMDS;
	connector->connector_type = DRM_MODE_CONNECTOR_DVID;

	अगर (psb_पूर्णांकel_sdvo_is_hdmi_connector(psb_पूर्णांकel_sdvo, device)) अणु
		connector->connector_type = DRM_MODE_CONNECTOR_HDMIA;
		psb_पूर्णांकel_sdvo->is_hdmi = true;
	पूर्ण
	psb_पूर्णांकel_sdvo->base.clone_mask = ((1 << INTEL_SDVO_NON_TV_CLONE_BIT) |
				       (1 << INTEL_ANALOG_CLONE_BIT));

	psb_पूर्णांकel_sdvo_connector_init(psb_पूर्णांकel_sdvo_connector, psb_पूर्णांकel_sdvo);
	अगर (psb_पूर्णांकel_sdvo->is_hdmi)
		psb_पूर्णांकel_sdvo_add_hdmi_properties(psb_पूर्णांकel_sdvo_connector);

	वापस true;
पूर्ण

अटल bool
psb_पूर्णांकel_sdvo_tv_init(काष्ठा psb_पूर्णांकel_sdvo *psb_पूर्णांकel_sdvo, पूर्णांक type)
अणु
	काष्ठा drm_encoder *encoder = &psb_पूर्णांकel_sdvo->base.base;
	काष्ठा drm_connector *connector;
	काष्ठा gma_connector *पूर्णांकel_connector;
	काष्ठा psb_पूर्णांकel_sdvo_connector *psb_पूर्णांकel_sdvo_connector;

	psb_पूर्णांकel_sdvo_connector = kzalloc(माप(काष्ठा psb_पूर्णांकel_sdvo_connector), GFP_KERNEL);
	अगर (!psb_पूर्णांकel_sdvo_connector)
		वापस false;

	पूर्णांकel_connector = &psb_पूर्णांकel_sdvo_connector->base;
	connector = &पूर्णांकel_connector->base;
	encoder->encoder_type = DRM_MODE_ENCODER_TVDAC;
	connector->connector_type = DRM_MODE_CONNECTOR_SVIDEO;

	psb_पूर्णांकel_sdvo->controlled_output |= type;
	psb_पूर्णांकel_sdvo_connector->output_flag = type;

	psb_पूर्णांकel_sdvo->is_tv = true;
	psb_पूर्णांकel_sdvo->base.needs_tv_घड़ी = true;
	psb_पूर्णांकel_sdvo->base.clone_mask = 1 << INTEL_SDVO_TV_CLONE_BIT;

	psb_पूर्णांकel_sdvo_connector_init(psb_पूर्णांकel_sdvo_connector, psb_पूर्णांकel_sdvo);

	अगर (!psb_पूर्णांकel_sdvo_tv_create_property(psb_पूर्णांकel_sdvo, psb_पूर्णांकel_sdvo_connector, type))
		जाओ err;

	अगर (!psb_पूर्णांकel_sdvo_create_enhance_property(psb_पूर्णांकel_sdvo, psb_पूर्णांकel_sdvo_connector))
		जाओ err;

	वापस true;

err:
	psb_पूर्णांकel_sdvo_destroy(connector);
	वापस false;
पूर्ण

अटल bool
psb_पूर्णांकel_sdvo_analog_init(काष्ठा psb_पूर्णांकel_sdvo *psb_पूर्णांकel_sdvo, पूर्णांक device)
अणु
	काष्ठा drm_encoder *encoder = &psb_पूर्णांकel_sdvo->base.base;
	काष्ठा drm_connector *connector;
	काष्ठा gma_connector *पूर्णांकel_connector;
	काष्ठा psb_पूर्णांकel_sdvo_connector *psb_पूर्णांकel_sdvo_connector;

	psb_पूर्णांकel_sdvo_connector = kzalloc(माप(काष्ठा psb_पूर्णांकel_sdvo_connector), GFP_KERNEL);
	अगर (!psb_पूर्णांकel_sdvo_connector)
		वापस false;

	पूर्णांकel_connector = &psb_पूर्णांकel_sdvo_connector->base;
	connector = &पूर्णांकel_connector->base;
	connector->polled = DRM_CONNECTOR_POLL_CONNECT;
	encoder->encoder_type = DRM_MODE_ENCODER_DAC;
	connector->connector_type = DRM_MODE_CONNECTOR_VGA;

	अगर (device == 0) अणु
		psb_पूर्णांकel_sdvo->controlled_output |= SDVO_OUTPUT_RGB0;
		psb_पूर्णांकel_sdvo_connector->output_flag = SDVO_OUTPUT_RGB0;
	पूर्ण अन्यथा अगर (device == 1) अणु
		psb_पूर्णांकel_sdvo->controlled_output |= SDVO_OUTPUT_RGB1;
		psb_पूर्णांकel_sdvo_connector->output_flag = SDVO_OUTPUT_RGB1;
	पूर्ण

	psb_पूर्णांकel_sdvo->base.clone_mask = ((1 << INTEL_SDVO_NON_TV_CLONE_BIT) |
				       (1 << INTEL_ANALOG_CLONE_BIT));

	psb_पूर्णांकel_sdvo_connector_init(psb_पूर्णांकel_sdvo_connector,
				  psb_पूर्णांकel_sdvo);
	वापस true;
पूर्ण

अटल bool
psb_पूर्णांकel_sdvo_lvds_init(काष्ठा psb_पूर्णांकel_sdvo *psb_पूर्णांकel_sdvo, पूर्णांक device)
अणु
	काष्ठा drm_encoder *encoder = &psb_पूर्णांकel_sdvo->base.base;
	काष्ठा drm_connector *connector;
	काष्ठा gma_connector *पूर्णांकel_connector;
	काष्ठा psb_पूर्णांकel_sdvo_connector *psb_पूर्णांकel_sdvo_connector;

	psb_पूर्णांकel_sdvo_connector = kzalloc(माप(काष्ठा psb_पूर्णांकel_sdvo_connector), GFP_KERNEL);
	अगर (!psb_पूर्णांकel_sdvo_connector)
		वापस false;

	पूर्णांकel_connector = &psb_पूर्णांकel_sdvo_connector->base;
	connector = &पूर्णांकel_connector->base;
	encoder->encoder_type = DRM_MODE_ENCODER_LVDS;
	connector->connector_type = DRM_MODE_CONNECTOR_LVDS;

	अगर (device == 0) अणु
		psb_पूर्णांकel_sdvo->controlled_output |= SDVO_OUTPUT_LVDS0;
		psb_पूर्णांकel_sdvo_connector->output_flag = SDVO_OUTPUT_LVDS0;
	पूर्ण अन्यथा अगर (device == 1) अणु
		psb_पूर्णांकel_sdvo->controlled_output |= SDVO_OUTPUT_LVDS1;
		psb_पूर्णांकel_sdvo_connector->output_flag = SDVO_OUTPUT_LVDS1;
	पूर्ण

	psb_पूर्णांकel_sdvo->base.clone_mask = ((1 << INTEL_ANALOG_CLONE_BIT) |
				       (1 << INTEL_SDVO_LVDS_CLONE_BIT));

	psb_पूर्णांकel_sdvo_connector_init(psb_पूर्णांकel_sdvo_connector, psb_पूर्णांकel_sdvo);
	अगर (!psb_पूर्णांकel_sdvo_create_enhance_property(psb_पूर्णांकel_sdvo, psb_पूर्णांकel_sdvo_connector))
		जाओ err;

	वापस true;

err:
	psb_पूर्णांकel_sdvo_destroy(connector);
	वापस false;
पूर्ण

अटल bool
psb_पूर्णांकel_sdvo_output_setup(काष्ठा psb_पूर्णांकel_sdvo *psb_पूर्णांकel_sdvo, uपूर्णांक16_t flags)
अणु
	psb_पूर्णांकel_sdvo->is_tv = false;
	psb_पूर्णांकel_sdvo->base.needs_tv_घड़ी = false;
	psb_पूर्णांकel_sdvo->is_lvds = false;

	/* SDVO requires XXX1 function may not exist unless it has XXX0 function.*/

	अगर (flags & SDVO_OUTPUT_TMDS0)
		अगर (!psb_पूर्णांकel_sdvo_dvi_init(psb_पूर्णांकel_sdvo, 0))
			वापस false;

	अगर ((flags & SDVO_TMDS_MASK) == SDVO_TMDS_MASK)
		अगर (!psb_पूर्णांकel_sdvo_dvi_init(psb_पूर्णांकel_sdvo, 1))
			वापस false;

	/* TV has no XXX1 function block */
	अगर (flags & SDVO_OUTPUT_SVID0)
		अगर (!psb_पूर्णांकel_sdvo_tv_init(psb_पूर्णांकel_sdvo, SDVO_OUTPUT_SVID0))
			वापस false;

	अगर (flags & SDVO_OUTPUT_CVBS0)
		अगर (!psb_पूर्णांकel_sdvo_tv_init(psb_पूर्णांकel_sdvo, SDVO_OUTPUT_CVBS0))
			वापस false;

	अगर (flags & SDVO_OUTPUT_RGB0)
		अगर (!psb_पूर्णांकel_sdvo_analog_init(psb_पूर्णांकel_sdvo, 0))
			वापस false;

	अगर ((flags & SDVO_RGB_MASK) == SDVO_RGB_MASK)
		अगर (!psb_पूर्णांकel_sdvo_analog_init(psb_पूर्णांकel_sdvo, 1))
			वापस false;

	अगर (flags & SDVO_OUTPUT_LVDS0)
		अगर (!psb_पूर्णांकel_sdvo_lvds_init(psb_पूर्णांकel_sdvo, 0))
			वापस false;

	अगर ((flags & SDVO_LVDS_MASK) == SDVO_LVDS_MASK)
		अगर (!psb_पूर्णांकel_sdvo_lvds_init(psb_पूर्णांकel_sdvo, 1))
			वापस false;

	अगर ((flags & SDVO_OUTPUT_MASK) == 0) अणु
		अचिन्हित अक्षर bytes[2];

		psb_पूर्णांकel_sdvo->controlled_output = 0;
		स_नकल(bytes, &psb_पूर्णांकel_sdvo->caps.output_flags, 2);
		DRM_DEBUG_KMS("%s: Unknown SDVO output type (0x%02x%02x)\n",
			      SDVO_NAME(psb_पूर्णांकel_sdvo),
			      bytes[0], bytes[1]);
		वापस false;
	पूर्ण
	psb_पूर्णांकel_sdvo->base.crtc_mask = (1 << 0) | (1 << 1);

	वापस true;
पूर्ण

अटल bool psb_पूर्णांकel_sdvo_tv_create_property(काष्ठा psb_पूर्णांकel_sdvo *psb_पूर्णांकel_sdvo,
					  काष्ठा psb_पूर्णांकel_sdvo_connector *psb_पूर्णांकel_sdvo_connector,
					  पूर्णांक type)
अणु
	काष्ठा drm_device *dev = psb_पूर्णांकel_sdvo->base.base.dev;
	काष्ठा psb_पूर्णांकel_sdvo_tv_क्रमmat क्रमmat;
	uपूर्णांक32_t क्रमmat_map, i;

	अगर (!psb_पूर्णांकel_sdvo_set_target_output(psb_पूर्णांकel_sdvo, type))
		वापस false;

	BUILD_BUG_ON(माप(क्रमmat) != 6);
	अगर (!psb_पूर्णांकel_sdvo_get_value(psb_पूर्णांकel_sdvo,
				  SDVO_CMD_GET_SUPPORTED_TV_FORMATS,
				  &क्रमmat, माप(क्रमmat)))
		वापस false;

	स_नकल(&क्रमmat_map, &क्रमmat, min(माप(क्रमmat_map), माप(क्रमmat)));

	अगर (क्रमmat_map == 0)
		वापस false;

	psb_पूर्णांकel_sdvo_connector->क्रमmat_supported_num = 0;
	क्रम (i = 0 ; i < ARRAY_SIZE(tv_क्रमmat_names); i++)
		अगर (क्रमmat_map & (1 << i))
			psb_पूर्णांकel_sdvo_connector->tv_क्रमmat_supported[psb_पूर्णांकel_sdvo_connector->क्रमmat_supported_num++] = i;


	psb_पूर्णांकel_sdvo_connector->tv_क्रमmat =
			drm_property_create(dev, DRM_MODE_PROP_ENUM,
					    "mode", psb_पूर्णांकel_sdvo_connector->क्रमmat_supported_num);
	अगर (!psb_पूर्णांकel_sdvo_connector->tv_क्रमmat)
		वापस false;

	क्रम (i = 0; i < psb_पूर्णांकel_sdvo_connector->क्रमmat_supported_num; i++)
		drm_property_add_क्रमागत(
				psb_पूर्णांकel_sdvo_connector->tv_क्रमmat,
				i, tv_क्रमmat_names[psb_पूर्णांकel_sdvo_connector->tv_क्रमmat_supported[i]]);

	psb_पूर्णांकel_sdvo->tv_क्रमmat_index = psb_पूर्णांकel_sdvo_connector->tv_क्रमmat_supported[0];
	drm_object_attach_property(&psb_पूर्णांकel_sdvo_connector->base.base.base,
				      psb_पूर्णांकel_sdvo_connector->tv_क्रमmat, 0);
	वापस true;

पूर्ण

#घोषणा ENHANCEMENT(name, NAME) करो अणु \
	अगर (enhancements.name) अणु \
		अगर (!psb_पूर्णांकel_sdvo_get_value(psb_पूर्णांकel_sdvo, SDVO_CMD_GET_MAX_##NAME, &data_value, 4) || \
		    !psb_पूर्णांकel_sdvo_get_value(psb_पूर्णांकel_sdvo, SDVO_CMD_GET_##NAME, &response, 2)) \
			वापस false; \
		psb_पूर्णांकel_sdvo_connector->max_##name = data_value[0]; \
		psb_पूर्णांकel_sdvo_connector->cur_##name = response; \
		psb_पूर्णांकel_sdvo_connector->name = \
			drm_property_create_range(dev, 0, #name, 0, data_value[0]); \
		अगर (!psb_पूर्णांकel_sdvo_connector->name) वापस false; \
		drm_object_attach_property(&connector->base, \
					      psb_पूर्णांकel_sdvo_connector->name, \
					      psb_पूर्णांकel_sdvo_connector->cur_##name); \
		DRM_DEBUG_KMS(#name ": max %d, default %d, current %d\n", \
			      data_value[0], data_value[1], response); \
	पूर्ण \
पूर्ण जबतक(0)

अटल bool
psb_पूर्णांकel_sdvo_create_enhance_property_tv(काष्ठा psb_पूर्णांकel_sdvo *psb_पूर्णांकel_sdvo,
				      काष्ठा psb_पूर्णांकel_sdvo_connector *psb_पूर्णांकel_sdvo_connector,
				      काष्ठा psb_पूर्णांकel_sdvo_enhancements_reply enhancements)
अणु
	काष्ठा drm_device *dev = psb_पूर्णांकel_sdvo->base.base.dev;
	काष्ठा drm_connector *connector = &psb_पूर्णांकel_sdvo_connector->base.base;
	uपूर्णांक16_t response, data_value[2];

	/* when horizontal overscan is supported, Add the left/right  property */
	अगर (enhancements.overscan_h) अणु
		अगर (!psb_पूर्णांकel_sdvo_get_value(psb_पूर्णांकel_sdvo,
					  SDVO_CMD_GET_MAX_OVERSCAN_H,
					  &data_value, 4))
			वापस false;

		अगर (!psb_पूर्णांकel_sdvo_get_value(psb_पूर्णांकel_sdvo,
					  SDVO_CMD_GET_OVERSCAN_H,
					  &response, 2))
			वापस false;

		psb_पूर्णांकel_sdvo_connector->max_hscan = data_value[0];
		psb_पूर्णांकel_sdvo_connector->left_margin = data_value[0] - response;
		psb_पूर्णांकel_sdvo_connector->right_margin = psb_पूर्णांकel_sdvo_connector->left_margin;
		psb_पूर्णांकel_sdvo_connector->left =
			drm_property_create_range(dev, 0, "left_margin", 0, data_value[0]);
		अगर (!psb_पूर्णांकel_sdvo_connector->left)
			वापस false;

		drm_object_attach_property(&connector->base,
					      psb_पूर्णांकel_sdvo_connector->left,
					      psb_पूर्णांकel_sdvo_connector->left_margin);

		psb_पूर्णांकel_sdvo_connector->right =
			drm_property_create_range(dev, 0, "right_margin", 0, data_value[0]);
		अगर (!psb_पूर्णांकel_sdvo_connector->right)
			वापस false;

		drm_object_attach_property(&connector->base,
					      psb_पूर्णांकel_sdvo_connector->right,
					      psb_पूर्णांकel_sdvo_connector->right_margin);
		DRM_DEBUG_KMS("h_overscan: max %d, "
			      "default %d, current %d\n",
			      data_value[0], data_value[1], response);
	पूर्ण

	अगर (enhancements.overscan_v) अणु
		अगर (!psb_पूर्णांकel_sdvo_get_value(psb_पूर्णांकel_sdvo,
					  SDVO_CMD_GET_MAX_OVERSCAN_V,
					  &data_value, 4))
			वापस false;

		अगर (!psb_पूर्णांकel_sdvo_get_value(psb_पूर्णांकel_sdvo,
					  SDVO_CMD_GET_OVERSCAN_V,
					  &response, 2))
			वापस false;

		psb_पूर्णांकel_sdvo_connector->max_vscan = data_value[0];
		psb_पूर्णांकel_sdvo_connector->top_margin = data_value[0] - response;
		psb_पूर्णांकel_sdvo_connector->bottom_margin = psb_पूर्णांकel_sdvo_connector->top_margin;
		psb_पूर्णांकel_sdvo_connector->top =
			drm_property_create_range(dev, 0, "top_margin", 0, data_value[0]);
		अगर (!psb_पूर्णांकel_sdvo_connector->top)
			वापस false;

		drm_object_attach_property(&connector->base,
					      psb_पूर्णांकel_sdvo_connector->top,
					      psb_पूर्णांकel_sdvo_connector->top_margin);

		psb_पूर्णांकel_sdvo_connector->bottom =
			drm_property_create_range(dev, 0, "bottom_margin", 0, data_value[0]);
		अगर (!psb_पूर्णांकel_sdvo_connector->bottom)
			वापस false;

		drm_object_attach_property(&connector->base,
					      psb_पूर्णांकel_sdvo_connector->bottom,
					      psb_पूर्णांकel_sdvo_connector->bottom_margin);
		DRM_DEBUG_KMS("v_overscan: max %d, "
			      "default %d, current %d\n",
			      data_value[0], data_value[1], response);
	पूर्ण

	ENHANCEMENT(hpos, HPOS);
	ENHANCEMENT(vpos, VPOS);
	ENHANCEMENT(saturation, SATURATION);
	ENHANCEMENT(contrast, CONTRAST);
	ENHANCEMENT(hue, HUE);
	ENHANCEMENT(sharpness, SHARPNESS);
	ENHANCEMENT(brightness, BRIGHTNESS);
	ENHANCEMENT(flicker_filter, FLICKER_FILTER);
	ENHANCEMENT(flicker_filter_adaptive, FLICKER_FILTER_ADAPTIVE);
	ENHANCEMENT(flicker_filter_2d, FLICKER_FILTER_2D);
	ENHANCEMENT(tv_chroma_filter, TV_CHROMA_FILTER);
	ENHANCEMENT(tv_luma_filter, TV_LUMA_FILTER);

	अगर (enhancements.करोt_crawl) अणु
		अगर (!psb_पूर्णांकel_sdvo_get_value(psb_पूर्णांकel_sdvo, SDVO_CMD_GET_DOT_CRAWL, &response, 2))
			वापस false;

		psb_पूर्णांकel_sdvo_connector->max_करोt_crawl = 1;
		psb_पूर्णांकel_sdvo_connector->cur_करोt_crawl = response & 0x1;
		psb_पूर्णांकel_sdvo_connector->करोt_crawl =
			drm_property_create_range(dev, 0, "dot_crawl", 0, 1);
		अगर (!psb_पूर्णांकel_sdvo_connector->करोt_crawl)
			वापस false;

		drm_object_attach_property(&connector->base,
					      psb_पूर्णांकel_sdvo_connector->करोt_crawl,
					      psb_पूर्णांकel_sdvo_connector->cur_करोt_crawl);
		DRM_DEBUG_KMS("dot crawl: current %d\n", response);
	पूर्ण

	वापस true;
पूर्ण

अटल bool
psb_पूर्णांकel_sdvo_create_enhance_property_lvds(काष्ठा psb_पूर्णांकel_sdvo *psb_पूर्णांकel_sdvo,
					काष्ठा psb_पूर्णांकel_sdvo_connector *psb_पूर्णांकel_sdvo_connector,
					काष्ठा psb_पूर्णांकel_sdvo_enhancements_reply enhancements)
अणु
	काष्ठा drm_device *dev = psb_पूर्णांकel_sdvo->base.base.dev;
	काष्ठा drm_connector *connector = &psb_पूर्णांकel_sdvo_connector->base.base;
	uपूर्णांक16_t response, data_value[2];

	ENHANCEMENT(brightness, BRIGHTNESS);

	वापस true;
पूर्ण
#अघोषित ENHANCEMENT

अटल bool psb_पूर्णांकel_sdvo_create_enhance_property(काष्ठा psb_पूर्णांकel_sdvo *psb_पूर्णांकel_sdvo,
					       काष्ठा psb_पूर्णांकel_sdvo_connector *psb_पूर्णांकel_sdvo_connector)
अणु
	जोड़ अणु
		काष्ठा psb_पूर्णांकel_sdvo_enhancements_reply reply;
		uपूर्णांक16_t response;
	पूर्ण enhancements;

	BUILD_BUG_ON(माप(enhancements) != 2);

	enhancements.response = 0;
	psb_पूर्णांकel_sdvo_get_value(psb_पूर्णांकel_sdvo,
			     SDVO_CMD_GET_SUPPORTED_ENHANCEMENTS,
			     &enhancements, माप(enhancements));
	अगर (enhancements.response == 0) अणु
		DRM_DEBUG_KMS("No enhancement is supported\n");
		वापस true;
	पूर्ण

	अगर (IS_TV(psb_पूर्णांकel_sdvo_connector))
		वापस psb_पूर्णांकel_sdvo_create_enhance_property_tv(psb_पूर्णांकel_sdvo, psb_पूर्णांकel_sdvo_connector, enhancements.reply);
	अन्यथा अगर(IS_LVDS(psb_पूर्णांकel_sdvo_connector))
		वापस psb_पूर्णांकel_sdvo_create_enhance_property_lvds(psb_पूर्णांकel_sdvo, psb_पूर्णांकel_sdvo_connector, enhancements.reply);
	अन्यथा
		वापस true;
पूर्ण

अटल पूर्णांक psb_पूर्णांकel_sdvo_ddc_proxy_xfer(काष्ठा i2c_adapter *adapter,
				     काष्ठा i2c_msg *msgs,
				     पूर्णांक num)
अणु
	काष्ठा psb_पूर्णांकel_sdvo *sdvo = adapter->algo_data;

	अगर (!psb_पूर्णांकel_sdvo_set_control_bus_चयन(sdvo, sdvo->ddc_bus))
		वापस -EIO;

	वापस sdvo->i2c->algo->master_xfer(sdvo->i2c, msgs, num);
पूर्ण

अटल u32 psb_पूर्णांकel_sdvo_ddc_proxy_func(काष्ठा i2c_adapter *adapter)
अणु
	काष्ठा psb_पूर्णांकel_sdvo *sdvo = adapter->algo_data;
	वापस sdvo->i2c->algo->functionality(sdvo->i2c);
पूर्ण

अटल स्थिर काष्ठा i2c_algorithm psb_पूर्णांकel_sdvo_ddc_proxy = अणु
	.master_xfer	= psb_पूर्णांकel_sdvo_ddc_proxy_xfer,
	.functionality	= psb_पूर्णांकel_sdvo_ddc_proxy_func
पूर्ण;

अटल bool
psb_पूर्णांकel_sdvo_init_ddc_proxy(काष्ठा psb_पूर्णांकel_sdvo *sdvo,
			  काष्ठा drm_device *dev)
अणु
	sdvo->ddc.owner = THIS_MODULE;
	sdvo->ddc.class = I2C_CLASS_DDC;
	snम_लिखो(sdvo->ddc.name, I2C_NAME_SIZE, "SDVO DDC proxy");
	sdvo->ddc.dev.parent = dev->dev;
	sdvo->ddc.algo_data = sdvo;
	sdvo->ddc.algo = &psb_पूर्णांकel_sdvo_ddc_proxy;

	वापस i2c_add_adapter(&sdvo->ddc) == 0;
पूर्ण

bool psb_पूर्णांकel_sdvo_init(काष्ठा drm_device *dev, पूर्णांक sdvo_reg)
अणु
	काष्ठा drm_psb_निजी *dev_priv = dev->dev_निजी;
	काष्ठा gma_encoder *gma_encoder;
	काष्ठा psb_पूर्णांकel_sdvo *psb_पूर्णांकel_sdvo;
	पूर्णांक i;

	psb_पूर्णांकel_sdvo = kzalloc(माप(काष्ठा psb_पूर्णांकel_sdvo), GFP_KERNEL);
	अगर (!psb_पूर्णांकel_sdvo)
		वापस false;

	psb_पूर्णांकel_sdvo->sdvo_reg = sdvo_reg;
	psb_पूर्णांकel_sdvo->slave_addr = psb_पूर्णांकel_sdvo_get_slave_addr(dev, sdvo_reg) >> 1;
	psb_पूर्णांकel_sdvo_select_i2c_bus(dev_priv, psb_पूर्णांकel_sdvo, sdvo_reg);
	अगर (!psb_पूर्णांकel_sdvo_init_ddc_proxy(psb_पूर्णांकel_sdvo, dev)) अणु
		kमुक्त(psb_पूर्णांकel_sdvo);
		वापस false;
	पूर्ण

	/* encoder type will be decided later */
	gma_encoder = &psb_पूर्णांकel_sdvo->base;
	gma_encoder->type = INTEL_OUTPUT_SDVO;
	drm_encoder_init(dev, &gma_encoder->base, &psb_पूर्णांकel_sdvo_enc_funcs,
			 0, शून्य);

	/* Read the regs to test अगर we can talk to the device */
	क्रम (i = 0; i < 0x40; i++) अणु
		u8 byte;

		अगर (!psb_पूर्णांकel_sdvo_पढ़ो_byte(psb_पूर्णांकel_sdvo, i, &byte)) अणु
			DRM_DEBUG_KMS("No SDVO device found on SDVO%c\n",
				      IS_SDVOB(sdvo_reg) ? 'B' : 'C');
			जाओ err;
		पूर्ण
	पूर्ण

	अगर (IS_SDVOB(sdvo_reg))
		dev_priv->hotplug_supported_mask |= SDVOB_HOTPLUG_INT_STATUS;
	अन्यथा
		dev_priv->hotplug_supported_mask |= SDVOC_HOTPLUG_INT_STATUS;

	drm_encoder_helper_add(&gma_encoder->base, &psb_पूर्णांकel_sdvo_helper_funcs);

	/* In शेष हाल sdvo lvds is false */
	अगर (!psb_पूर्णांकel_sdvo_get_capabilities(psb_पूर्णांकel_sdvo, &psb_पूर्णांकel_sdvo->caps))
		जाओ err;

	अगर (psb_पूर्णांकel_sdvo_output_setup(psb_पूर्णांकel_sdvo,
				    psb_पूर्णांकel_sdvo->caps.output_flags) != true) अणु
		DRM_DEBUG_KMS("SDVO output failed to setup on SDVO%c\n",
			      IS_SDVOB(sdvo_reg) ? 'B' : 'C');
		जाओ err;
	पूर्ण

	psb_पूर्णांकel_sdvo_select_ddc_bus(dev_priv, psb_पूर्णांकel_sdvo, sdvo_reg);

	/* Set the input timing to the screen. Assume always input 0. */
	अगर (!psb_पूर्णांकel_sdvo_set_target_input(psb_पूर्णांकel_sdvo))
		जाओ err;

	अगर (!psb_पूर्णांकel_sdvo_get_input_pixel_घड़ी_range(psb_पूर्णांकel_sdvo,
						    &psb_पूर्णांकel_sdvo->pixel_घड़ी_min,
						    &psb_पूर्णांकel_sdvo->pixel_घड़ी_max))
		जाओ err;

	DRM_DEBUG_KMS("%s device VID/DID: %02X:%02X.%02X, "
			"clock range %dMHz - %dMHz, "
			"input 1: %c, input 2: %c, "
			"output 1: %c, output 2: %c\n",
			SDVO_NAME(psb_पूर्णांकel_sdvo),
			psb_पूर्णांकel_sdvo->caps.venकरोr_id, psb_पूर्णांकel_sdvo->caps.device_id,
			psb_पूर्णांकel_sdvo->caps.device_rev_id,
			psb_पूर्णांकel_sdvo->pixel_घड़ी_min / 1000,
			psb_पूर्णांकel_sdvo->pixel_घड़ी_max / 1000,
			(psb_पूर्णांकel_sdvo->caps.sdvo_inमाला_दो_mask & 0x1) ? 'Y' : 'N',
			(psb_पूर्णांकel_sdvo->caps.sdvo_inमाला_दो_mask & 0x2) ? 'Y' : 'N',
			/* check currently supported outमाला_दो */
			psb_पूर्णांकel_sdvo->caps.output_flags &
			(SDVO_OUTPUT_TMDS0 | SDVO_OUTPUT_RGB0) ? 'Y' : 'N',
			psb_पूर्णांकel_sdvo->caps.output_flags &
			(SDVO_OUTPUT_TMDS1 | SDVO_OUTPUT_RGB1) ? 'Y' : 'N');
	वापस true;

err:
	drm_encoder_cleanup(&gma_encoder->base);
	i2c_del_adapter(&psb_पूर्णांकel_sdvo->ddc);
	kमुक्त(psb_पूर्णांकel_sdvo);

	वापस false;
पूर्ण
