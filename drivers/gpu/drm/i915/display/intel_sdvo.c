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
#समावेश <linux/export.h>
#समावेश <linux/i2c.h>
#समावेश <linux/slab.h>

#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_crtc.h>
#समावेश <drm/drm_edid.h>

#समावेश "i915_drv.h"
#समावेश "intel_atomic.h"
#समावेश "intel_connector.h"
#समावेश "intel_display_types.h"
#समावेश "intel_fifo_underrun.h"
#समावेश "intel_gmbus.h"
#समावेश "intel_hdmi.h"
#समावेश "intel_hotplug.h"
#समावेश "intel_panel.h"
#समावेश "intel_sdvo.h"
#समावेश "intel_sdvo_regs.h"

#घोषणा SDVO_TMDS_MASK (SDVO_OUTPUT_TMDS0 | SDVO_OUTPUT_TMDS1)
#घोषणा SDVO_RGB_MASK  (SDVO_OUTPUT_RGB0 | SDVO_OUTPUT_RGB1)
#घोषणा SDVO_LVDS_MASK (SDVO_OUTPUT_LVDS0 | SDVO_OUTPUT_LVDS1)
#घोषणा SDVO_TV_MASK   (SDVO_OUTPUT_CVBS0 | SDVO_OUTPUT_SVID0 | SDVO_OUTPUT_YPRPB0)

#घोषणा SDVO_OUTPUT_MASK (SDVO_TMDS_MASK | SDVO_RGB_MASK | SDVO_LVDS_MASK |\
			SDVO_TV_MASK)

#घोषणा IS_TV(c)	(c->output_flag & SDVO_TV_MASK)
#घोषणा IS_TMDS(c)	(c->output_flag & SDVO_TMDS_MASK)
#घोषणा IS_LVDS(c)	(c->output_flag & SDVO_LVDS_MASK)
#घोषणा IS_TV_OR_LVDS(c) (c->output_flag & (SDVO_TV_MASK | SDVO_LVDS_MASK))
#घोषणा IS_DIGITAL(c) (c->output_flag & (SDVO_TMDS_MASK | SDVO_LVDS_MASK))


अटल स्थिर अक्षर * स्थिर tv_क्रमmat_names[] = अणु
	"NTSC_M"   , "NTSC_J"  , "NTSC_443",
	"PAL_B"    , "PAL_D"   , "PAL_G"   ,
	"PAL_H"    , "PAL_I"   , "PAL_M"   ,
	"PAL_N"    , "PAL_NC"  , "PAL_60"  ,
	"SECAM_B"  , "SECAM_D" , "SECAM_G" ,
	"SECAM_K"  , "SECAM_K1", "SECAM_L" ,
	"SECAM_60"
पूर्ण;

#घोषणा TV_FORMAT_NUM  ARRAY_SIZE(tv_क्रमmat_names)

काष्ठा पूर्णांकel_sdvo अणु
	काष्ठा पूर्णांकel_encoder base;

	काष्ठा i2c_adapter *i2c;
	u8 slave_addr;

	काष्ठा i2c_adapter ddc;

	/* Register क्रम the SDVO device: SDVOB or SDVOC */
	i915_reg_t sdvo_reg;

	/* Active outमाला_दो controlled by this SDVO output */
	u16 controlled_output;

	/*
	 * Capabilities of the SDVO device वापसed by
	 * पूर्णांकel_sdvo_get_capabilities()
	 */
	काष्ठा पूर्णांकel_sdvo_caps caps;

	u8 colorimetry_cap;

	/* Pixel घड़ी limitations reported by the SDVO device, in kHz */
	पूर्णांक pixel_घड़ी_min, pixel_घड़ी_max;

	/*
	* For multiple function SDVO device,
	* this is क्रम current attached outमाला_दो.
	*/
	u16 attached_output;

	/*
	 * Hotplug activation bits क्रम this device
	 */
	u16 hotplug_active;

	क्रमागत port port;

	bool has_hdmi_monitor;
	bool has_hdmi_audio;

	/* DDC bus used by this SDVO encoder */
	u8 ddc_bus;

	/*
	 * the sdvo flag माला_लो lost in round trip: dtd->adjusted_mode->dtd
	 */
	u8 dtd_sdvo_flags;
पूर्ण;

काष्ठा पूर्णांकel_sdvo_connector अणु
	काष्ठा पूर्णांकel_connector base;

	/* Mark the type of connector */
	u16 output_flag;

	/* This contains all current supported TV क्रमmat */
	u8 tv_क्रमmat_supported[TV_FORMAT_NUM];
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

	/* this is to get the range of margin.*/
	u32 max_hscan, max_vscan;

	/**
	 * This is set अगर we treat the device as HDMI, instead of DVI.
	 */
	bool is_hdmi;
पूर्ण;

काष्ठा पूर्णांकel_sdvo_connector_state अणु
	/* base.base: tv.saturation/contrast/hue/brightness */
	काष्ठा पूर्णांकel_digital_connector_state base;

	काष्ठा अणु
		अचिन्हित overscan_h, overscan_v, hpos, vpos, sharpness;
		अचिन्हित flicker_filter, flicker_filter_2d, flicker_filter_adaptive;
		अचिन्हित chroma_filter, luma_filter, करोt_crawl;
	पूर्ण tv;
पूर्ण;

अटल काष्ठा पूर्णांकel_sdvo *to_sdvo(काष्ठा पूर्णांकel_encoder *encoder)
अणु
	वापस container_of(encoder, काष्ठा पूर्णांकel_sdvo, base);
पूर्ण

अटल काष्ठा पूर्णांकel_sdvo *पूर्णांकel_attached_sdvo(काष्ठा पूर्णांकel_connector *connector)
अणु
	वापस to_sdvo(पूर्णांकel_attached_encoder(connector));
पूर्ण

अटल काष्ठा पूर्णांकel_sdvo_connector *
to_पूर्णांकel_sdvo_connector(काष्ठा drm_connector *connector)
अणु
	वापस container_of(connector, काष्ठा पूर्णांकel_sdvo_connector, base.base);
पूर्ण

#घोषणा to_पूर्णांकel_sdvo_connector_state(conn_state) \
	container_of((conn_state), काष्ठा पूर्णांकel_sdvo_connector_state, base.base)

अटल bool
पूर्णांकel_sdvo_output_setup(काष्ठा पूर्णांकel_sdvo *पूर्णांकel_sdvo, u16 flags);
अटल bool
पूर्णांकel_sdvo_tv_create_property(काष्ठा पूर्णांकel_sdvo *पूर्णांकel_sdvo,
			      काष्ठा पूर्णांकel_sdvo_connector *पूर्णांकel_sdvo_connector,
			      पूर्णांक type);
अटल bool
पूर्णांकel_sdvo_create_enhance_property(काष्ठा पूर्णांकel_sdvo *पूर्णांकel_sdvo,
				   काष्ठा पूर्णांकel_sdvo_connector *पूर्णांकel_sdvo_connector);

/*
 * Writes the SDVOB or SDVOC with the given value, but always ग_लिखोs both
 * SDVOB and SDVOC to work around apparent hardware issues (according to
 * comments in the BIOS).
 */
अटल व्योम पूर्णांकel_sdvo_ग_लिखो_sdvox(काष्ठा पूर्णांकel_sdvo *पूर्णांकel_sdvo, u32 val)
अणु
	काष्ठा drm_device *dev = पूर्णांकel_sdvo->base.base.dev;
	काष्ठा drm_i915_निजी *dev_priv = to_i915(dev);
	u32 bval = val, cval = val;
	पूर्णांक i;

	अगर (HAS_PCH_SPLIT(dev_priv)) अणु
		पूर्णांकel_de_ग_लिखो(dev_priv, पूर्णांकel_sdvo->sdvo_reg, val);
		पूर्णांकel_de_posting_पढ़ो(dev_priv, पूर्णांकel_sdvo->sdvo_reg);
		/*
		 * HW workaround, need to ग_लिखो this twice क्रम issue
		 * that may result in first ग_लिखो getting masked.
		 */
		अगर (HAS_PCH_IBX(dev_priv)) अणु
			पूर्णांकel_de_ग_लिखो(dev_priv, पूर्णांकel_sdvo->sdvo_reg, val);
			पूर्णांकel_de_posting_पढ़ो(dev_priv, पूर्णांकel_sdvo->sdvo_reg);
		पूर्ण
		वापस;
	पूर्ण

	अगर (पूर्णांकel_sdvo->port == PORT_B)
		cval = पूर्णांकel_de_पढ़ो(dev_priv, GEN3_SDVOC);
	अन्यथा
		bval = पूर्णांकel_de_पढ़ो(dev_priv, GEN3_SDVOB);

	/*
	 * Write the रेजिस्टरs twice क्रम luck. Someबार,
	 * writing them only once करोesn't appear to 'stick'.
	 * The BIOS करोes this too. Yay, magic
	 */
	क्रम (i = 0; i < 2; i++) अणु
		पूर्णांकel_de_ग_लिखो(dev_priv, GEN3_SDVOB, bval);
		पूर्णांकel_de_posting_पढ़ो(dev_priv, GEN3_SDVOB);

		पूर्णांकel_de_ग_लिखो(dev_priv, GEN3_SDVOC, cval);
		पूर्णांकel_de_posting_पढ़ो(dev_priv, GEN3_SDVOC);
	पूर्ण
पूर्ण

अटल bool पूर्णांकel_sdvo_पढ़ो_byte(काष्ठा पूर्णांकel_sdvo *पूर्णांकel_sdvo, u8 addr, u8 *ch)
अणु
	काष्ठा i2c_msg msgs[] = अणु
		अणु
			.addr = पूर्णांकel_sdvo->slave_addr,
			.flags = 0,
			.len = 1,
			.buf = &addr,
		पूर्ण,
		अणु
			.addr = पूर्णांकel_sdvo->slave_addr,
			.flags = I2C_M_RD,
			.len = 1,
			.buf = ch,
		पूर्ण
	पूर्ण;
	पूर्णांक ret;

	अगर ((ret = i2c_transfer(पूर्णांकel_sdvo->i2c, msgs, 2)) == 2)
		वापस true;

	DRM_DEBUG_KMS("i2c transfer returned %d\n", ret);
	वापस false;
पूर्ण

#घोषणा SDVO_CMD_NAME_ENTRY(cmd_) अणु .cmd = SDVO_CMD_ ## cmd_, .name = #cmd_ पूर्ण

/** Mapping of command numbers to names, क्रम debug output */
अटल स्थिर काष्ठा अणु
	u8 cmd;
	स्थिर अक्षर *name;
पूर्ण __attribute__ ((packed)) sdvo_cmd_names[] = अणु
	SDVO_CMD_NAME_ENTRY(RESET),
	SDVO_CMD_NAME_ENTRY(GET_DEVICE_CAPS),
	SDVO_CMD_NAME_ENTRY(GET_FIRMWARE_REV),
	SDVO_CMD_NAME_ENTRY(GET_TRAINED_INPUTS),
	SDVO_CMD_NAME_ENTRY(GET_ACTIVE_OUTPUTS),
	SDVO_CMD_NAME_ENTRY(SET_ACTIVE_OUTPUTS),
	SDVO_CMD_NAME_ENTRY(GET_IN_OUT_MAP),
	SDVO_CMD_NAME_ENTRY(SET_IN_OUT_MAP),
	SDVO_CMD_NAME_ENTRY(GET_ATTACHED_DISPLAYS),
	SDVO_CMD_NAME_ENTRY(GET_HOT_PLUG_SUPPORT),
	SDVO_CMD_NAME_ENTRY(SET_ACTIVE_HOT_PLUG),
	SDVO_CMD_NAME_ENTRY(GET_ACTIVE_HOT_PLUG),
	SDVO_CMD_NAME_ENTRY(GET_INTERRUPT_EVENT_SOURCE),
	SDVO_CMD_NAME_ENTRY(SET_TARGET_INPUT),
	SDVO_CMD_NAME_ENTRY(SET_TARGET_OUTPUT),
	SDVO_CMD_NAME_ENTRY(GET_INPUT_TIMINGS_PART1),
	SDVO_CMD_NAME_ENTRY(GET_INPUT_TIMINGS_PART2),
	SDVO_CMD_NAME_ENTRY(SET_INPUT_TIMINGS_PART1),
	SDVO_CMD_NAME_ENTRY(SET_INPUT_TIMINGS_PART2),
	SDVO_CMD_NAME_ENTRY(SET_OUTPUT_TIMINGS_PART1),
	SDVO_CMD_NAME_ENTRY(SET_OUTPUT_TIMINGS_PART2),
	SDVO_CMD_NAME_ENTRY(GET_OUTPUT_TIMINGS_PART1),
	SDVO_CMD_NAME_ENTRY(GET_OUTPUT_TIMINGS_PART2),
	SDVO_CMD_NAME_ENTRY(CREATE_PREFERRED_INPUT_TIMING),
	SDVO_CMD_NAME_ENTRY(GET_PREFERRED_INPUT_TIMING_PART1),
	SDVO_CMD_NAME_ENTRY(GET_PREFERRED_INPUT_TIMING_PART2),
	SDVO_CMD_NAME_ENTRY(GET_INPUT_PIXEL_CLOCK_RANGE),
	SDVO_CMD_NAME_ENTRY(GET_OUTPUT_PIXEL_CLOCK_RANGE),
	SDVO_CMD_NAME_ENTRY(GET_SUPPORTED_CLOCK_RATE_MULTS),
	SDVO_CMD_NAME_ENTRY(GET_CLOCK_RATE_MULT),
	SDVO_CMD_NAME_ENTRY(SET_CLOCK_RATE_MULT),
	SDVO_CMD_NAME_ENTRY(GET_SUPPORTED_TV_FORMATS),
	SDVO_CMD_NAME_ENTRY(GET_TV_FORMAT),
	SDVO_CMD_NAME_ENTRY(SET_TV_FORMAT),
	SDVO_CMD_NAME_ENTRY(GET_SUPPORTED_POWER_STATES),
	SDVO_CMD_NAME_ENTRY(GET_POWER_STATE),
	SDVO_CMD_NAME_ENTRY(SET_ENCODER_POWER_STATE),
	SDVO_CMD_NAME_ENTRY(SET_DISPLAY_POWER_STATE),
	SDVO_CMD_NAME_ENTRY(SET_CONTROL_BUS_SWITCH),
	SDVO_CMD_NAME_ENTRY(GET_SDTV_RESOLUTION_SUPPORT),
	SDVO_CMD_NAME_ENTRY(GET_SCALED_HDTV_RESOLUTION_SUPPORT),
	SDVO_CMD_NAME_ENTRY(GET_SUPPORTED_ENHANCEMENTS),

	/* Add the op code क्रम SDVO enhancements */
	SDVO_CMD_NAME_ENTRY(GET_MAX_HPOS),
	SDVO_CMD_NAME_ENTRY(GET_HPOS),
	SDVO_CMD_NAME_ENTRY(SET_HPOS),
	SDVO_CMD_NAME_ENTRY(GET_MAX_VPOS),
	SDVO_CMD_NAME_ENTRY(GET_VPOS),
	SDVO_CMD_NAME_ENTRY(SET_VPOS),
	SDVO_CMD_NAME_ENTRY(GET_MAX_SATURATION),
	SDVO_CMD_NAME_ENTRY(GET_SATURATION),
	SDVO_CMD_NAME_ENTRY(SET_SATURATION),
	SDVO_CMD_NAME_ENTRY(GET_MAX_HUE),
	SDVO_CMD_NAME_ENTRY(GET_HUE),
	SDVO_CMD_NAME_ENTRY(SET_HUE),
	SDVO_CMD_NAME_ENTRY(GET_MAX_CONTRAST),
	SDVO_CMD_NAME_ENTRY(GET_CONTRAST),
	SDVO_CMD_NAME_ENTRY(SET_CONTRAST),
	SDVO_CMD_NAME_ENTRY(GET_MAX_BRIGHTNESS),
	SDVO_CMD_NAME_ENTRY(GET_BRIGHTNESS),
	SDVO_CMD_NAME_ENTRY(SET_BRIGHTNESS),
	SDVO_CMD_NAME_ENTRY(GET_MAX_OVERSCAN_H),
	SDVO_CMD_NAME_ENTRY(GET_OVERSCAN_H),
	SDVO_CMD_NAME_ENTRY(SET_OVERSCAN_H),
	SDVO_CMD_NAME_ENTRY(GET_MAX_OVERSCAN_V),
	SDVO_CMD_NAME_ENTRY(GET_OVERSCAN_V),
	SDVO_CMD_NAME_ENTRY(SET_OVERSCAN_V),
	SDVO_CMD_NAME_ENTRY(GET_MAX_FLICKER_FILTER),
	SDVO_CMD_NAME_ENTRY(GET_FLICKER_FILTER),
	SDVO_CMD_NAME_ENTRY(SET_FLICKER_FILTER),
	SDVO_CMD_NAME_ENTRY(GET_MAX_FLICKER_FILTER_ADAPTIVE),
	SDVO_CMD_NAME_ENTRY(GET_FLICKER_FILTER_ADAPTIVE),
	SDVO_CMD_NAME_ENTRY(SET_FLICKER_FILTER_ADAPTIVE),
	SDVO_CMD_NAME_ENTRY(GET_MAX_FLICKER_FILTER_2D),
	SDVO_CMD_NAME_ENTRY(GET_FLICKER_FILTER_2D),
	SDVO_CMD_NAME_ENTRY(SET_FLICKER_FILTER_2D),
	SDVO_CMD_NAME_ENTRY(GET_MAX_SHARPNESS),
	SDVO_CMD_NAME_ENTRY(GET_SHARPNESS),
	SDVO_CMD_NAME_ENTRY(SET_SHARPNESS),
	SDVO_CMD_NAME_ENTRY(GET_DOT_CRAWL),
	SDVO_CMD_NAME_ENTRY(SET_DOT_CRAWL),
	SDVO_CMD_NAME_ENTRY(GET_MAX_TV_CHROMA_FILTER),
	SDVO_CMD_NAME_ENTRY(GET_TV_CHROMA_FILTER),
	SDVO_CMD_NAME_ENTRY(SET_TV_CHROMA_FILTER),
	SDVO_CMD_NAME_ENTRY(GET_MAX_TV_LUMA_FILTER),
	SDVO_CMD_NAME_ENTRY(GET_TV_LUMA_FILTER),
	SDVO_CMD_NAME_ENTRY(SET_TV_LUMA_FILTER),

	/* HDMI op code */
	SDVO_CMD_NAME_ENTRY(GET_SUPP_ENCODE),
	SDVO_CMD_NAME_ENTRY(GET_ENCODE),
	SDVO_CMD_NAME_ENTRY(SET_ENCODE),
	SDVO_CMD_NAME_ENTRY(SET_PIXEL_REPLI),
	SDVO_CMD_NAME_ENTRY(GET_PIXEL_REPLI),
	SDVO_CMD_NAME_ENTRY(GET_COLORIMETRY_CAP),
	SDVO_CMD_NAME_ENTRY(SET_COLORIMETRY),
	SDVO_CMD_NAME_ENTRY(GET_COLORIMETRY),
	SDVO_CMD_NAME_ENTRY(GET_AUDIO_ENCRYPT_PREFER),
	SDVO_CMD_NAME_ENTRY(SET_AUDIO_STAT),
	SDVO_CMD_NAME_ENTRY(GET_AUDIO_STAT),
	SDVO_CMD_NAME_ENTRY(GET_HBUF_INDEX),
	SDVO_CMD_NAME_ENTRY(SET_HBUF_INDEX),
	SDVO_CMD_NAME_ENTRY(GET_HBUF_INFO),
	SDVO_CMD_NAME_ENTRY(GET_HBUF_AV_SPLIT),
	SDVO_CMD_NAME_ENTRY(SET_HBUF_AV_SPLIT),
	SDVO_CMD_NAME_ENTRY(GET_HBUF_TXRATE),
	SDVO_CMD_NAME_ENTRY(SET_HBUF_TXRATE),
	SDVO_CMD_NAME_ENTRY(SET_HBUF_DATA),
	SDVO_CMD_NAME_ENTRY(GET_HBUF_DATA),
पूर्ण;

#अघोषित SDVO_CMD_NAME_ENTRY

अटल स्थिर अक्षर *sdvo_cmd_name(u8 cmd)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(sdvo_cmd_names); i++) अणु
		अगर (cmd == sdvo_cmd_names[i].cmd)
			वापस sdvo_cmd_names[i].name;
	पूर्ण

	वापस शून्य;
पूर्ण

#घोषणा SDVO_NAME(svकरो) ((svकरो)->port == PORT_B ? "SDVOB" : "SDVOC")

अटल व्योम पूर्णांकel_sdvo_debug_ग_लिखो(काष्ठा पूर्णांकel_sdvo *पूर्णांकel_sdvo, u8 cmd,
				   स्थिर व्योम *args, पूर्णांक args_len)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(पूर्णांकel_sdvo->base.base.dev);
	स्थिर अक्षर *cmd_name;
	पूर्णांक i, pos = 0;
	अक्षर buffer[64];

#घोषणा BUF_PRINT(args...) \
	pos += snम_लिखो(buffer + pos, max_t(पूर्णांक, माप(buffer) - pos, 0), args)

	क्रम (i = 0; i < args_len; i++) अणु
		BUF_PRINT("%02X ", ((u8 *)args)[i]);
	पूर्ण
	क्रम (; i < 8; i++) अणु
		BUF_PRINT("   ");
	पूर्ण

	cmd_name = sdvo_cmd_name(cmd);
	अगर (cmd_name)
		BUF_PRINT("(%s)", cmd_name);
	अन्यथा
		BUF_PRINT("(%02X)", cmd);

	drm_WARN_ON(&dev_priv->drm, pos >= माप(buffer) - 1);
#अघोषित BUF_PRINT

	DRM_DEBUG_KMS("%s: W: %02X %s\n", SDVO_NAME(पूर्णांकel_sdvo), cmd, buffer);
पूर्ण

अटल स्थिर अक्षर * स्थिर cmd_status_names[] = अणु
	[SDVO_CMD_STATUS_POWER_ON] = "Power on",
	[SDVO_CMD_STATUS_SUCCESS] = "Success",
	[SDVO_CMD_STATUS_NOTSUPP] = "Not supported",
	[SDVO_CMD_STATUS_INVALID_ARG] = "Invalid arg",
	[SDVO_CMD_STATUS_PENDING] = "Pending",
	[SDVO_CMD_STATUS_TARGET_NOT_SPECIFIED] = "Target not specified",
	[SDVO_CMD_STATUS_SCALING_NOT_SUPP] = "Scaling not supported",
पूर्ण;

अटल स्थिर अक्षर *sdvo_cmd_status(u8 status)
अणु
	अगर (status < ARRAY_SIZE(cmd_status_names))
		वापस cmd_status_names[status];
	अन्यथा
		वापस शून्य;
पूर्ण

अटल bool __पूर्णांकel_sdvo_ग_लिखो_cmd(काष्ठा पूर्णांकel_sdvo *पूर्णांकel_sdvo, u8 cmd,
				   स्थिर व्योम *args, पूर्णांक args_len,
				   bool unlocked)
अणु
	u8 *buf, status;
	काष्ठा i2c_msg *msgs;
	पूर्णांक i, ret = true;

	/* Would be simpler to allocate both in one go ? */
	buf = kzalloc(args_len * 2 + 2, GFP_KERNEL);
	अगर (!buf)
		वापस false;

	msgs = kसुस्मृति(args_len + 3, माप(*msgs), GFP_KERNEL);
	अगर (!msgs) अणु
		kमुक्त(buf);
		वापस false;
	पूर्ण

	पूर्णांकel_sdvo_debug_ग_लिखो(पूर्णांकel_sdvo, cmd, args, args_len);

	क्रम (i = 0; i < args_len; i++) अणु
		msgs[i].addr = पूर्णांकel_sdvo->slave_addr;
		msgs[i].flags = 0;
		msgs[i].len = 2;
		msgs[i].buf = buf + 2 *i;
		buf[2*i + 0] = SDVO_I2C_ARG_0 - i;
		buf[2*i + 1] = ((u8*)args)[i];
	पूर्ण
	msgs[i].addr = पूर्णांकel_sdvo->slave_addr;
	msgs[i].flags = 0;
	msgs[i].len = 2;
	msgs[i].buf = buf + 2*i;
	buf[2*i + 0] = SDVO_I2C_OPCODE;
	buf[2*i + 1] = cmd;

	/* the following two are to पढ़ो the response */
	status = SDVO_I2C_CMD_STATUS;
	msgs[i+1].addr = पूर्णांकel_sdvo->slave_addr;
	msgs[i+1].flags = 0;
	msgs[i+1].len = 1;
	msgs[i+1].buf = &status;

	msgs[i+2].addr = पूर्णांकel_sdvo->slave_addr;
	msgs[i+2].flags = I2C_M_RD;
	msgs[i+2].len = 1;
	msgs[i+2].buf = &status;

	अगर (unlocked)
		ret = i2c_transfer(पूर्णांकel_sdvo->i2c, msgs, i+3);
	अन्यथा
		ret = __i2c_transfer(पूर्णांकel_sdvo->i2c, msgs, i+3);
	अगर (ret < 0) अणु
		DRM_DEBUG_KMS("I2c transfer returned %d\n", ret);
		ret = false;
		जाओ out;
	पूर्ण
	अगर (ret != i+3) अणु
		/* failure in I2C transfer */
		DRM_DEBUG_KMS("I2c transfer returned %d/%d\n", ret, i+3);
		ret = false;
	पूर्ण

out:
	kमुक्त(msgs);
	kमुक्त(buf);
	वापस ret;
पूर्ण

अटल bool पूर्णांकel_sdvo_ग_लिखो_cmd(काष्ठा पूर्णांकel_sdvo *पूर्णांकel_sdvo, u8 cmd,
				 स्थिर व्योम *args, पूर्णांक args_len)
अणु
	वापस __पूर्णांकel_sdvo_ग_लिखो_cmd(पूर्णांकel_sdvo, cmd, args, args_len, true);
पूर्ण

अटल bool पूर्णांकel_sdvo_पढ़ो_response(काष्ठा पूर्णांकel_sdvo *पूर्णांकel_sdvo,
				     व्योम *response, पूर्णांक response_len)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(पूर्णांकel_sdvo->base.base.dev);
	स्थिर अक्षर *cmd_status;
	u8 retry = 15; /* 5 quick checks, followed by 10 दीर्घ checks */
	u8 status;
	पूर्णांक i, pos = 0;
	अक्षर buffer[64];

	buffer[0] = '\0';

	/*
	 * The करोcumentation states that all commands will be
	 * processed within 15तगs, and that we need only poll
	 * the status byte a maximum of 3 बार in order क्रम the
	 * command to be complete.
	 *
	 * Check 5 बार in हाल the hardware failed to पढ़ो the करोcs.
	 *
	 * Also beware that the first response by many devices is to
	 * reply PENDING and stall क्रम समय. TVs are notorious क्रम
	 * requiring दीर्घer than specअगरied to complete their replies.
	 * Originally (in the DDX दीर्घ ago), the delay was only ever 15ms
	 * with an additional delay of 30ms applied क्रम TVs added later after
	 * many experiments. To accommodate both sets of delays, we करो a
	 * sequence of slow checks अगर the device is falling behind and fails
	 * to reply within 5*15तगs.
	 */
	अगर (!पूर्णांकel_sdvo_पढ़ो_byte(पूर्णांकel_sdvo,
				  SDVO_I2C_CMD_STATUS,
				  &status))
		जाओ log_fail;

	जबतक ((status == SDVO_CMD_STATUS_PENDING ||
		status == SDVO_CMD_STATUS_TARGET_NOT_SPECIFIED) && --retry) अणु
		अगर (retry < 10)
			msleep(15);
		अन्यथा
			udelay(15);

		अगर (!पूर्णांकel_sdvo_पढ़ो_byte(पूर्णांकel_sdvo,
					  SDVO_I2C_CMD_STATUS,
					  &status))
			जाओ log_fail;
	पूर्ण

#घोषणा BUF_PRINT(args...) \
	pos += snम_लिखो(buffer + pos, max_t(पूर्णांक, माप(buffer) - pos, 0), args)

	cmd_status = sdvo_cmd_status(status);
	अगर (cmd_status)
		BUF_PRINT("(%s)", cmd_status);
	अन्यथा
		BUF_PRINT("(??? %d)", status);

	अगर (status != SDVO_CMD_STATUS_SUCCESS)
		जाओ log_fail;

	/* Read the command response */
	क्रम (i = 0; i < response_len; i++) अणु
		अगर (!पूर्णांकel_sdvo_पढ़ो_byte(पूर्णांकel_sdvo,
					  SDVO_I2C_RETURN_0 + i,
					  &((u8 *)response)[i]))
			जाओ log_fail;
		BUF_PRINT(" %02X", ((u8 *)response)[i]);
	पूर्ण

	drm_WARN_ON(&dev_priv->drm, pos >= माप(buffer) - 1);
#अघोषित BUF_PRINT

	DRM_DEBUG_KMS("%s: R: %s\n", SDVO_NAME(पूर्णांकel_sdvo), buffer);
	वापस true;

log_fail:
	DRM_DEBUG_KMS("%s: R: ... failed %s\n",
		      SDVO_NAME(पूर्णांकel_sdvo), buffer);
	वापस false;
पूर्ण

अटल पूर्णांक पूर्णांकel_sdvo_get_pixel_multiplier(स्थिर काष्ठा drm_display_mode *adjusted_mode)
अणु
	अगर (adjusted_mode->crtc_घड़ी >= 100000)
		वापस 1;
	अन्यथा अगर (adjusted_mode->crtc_घड़ी >= 50000)
		वापस 2;
	अन्यथा
		वापस 4;
पूर्ण

अटल bool __पूर्णांकel_sdvo_set_control_bus_चयन(काष्ठा पूर्णांकel_sdvo *पूर्णांकel_sdvo,
						u8 ddc_bus)
अणु
	/* This must be the immediately preceding ग_लिखो beक्रमe the i2c xfer */
	वापस __पूर्णांकel_sdvo_ग_लिखो_cmd(पूर्णांकel_sdvo,
				      SDVO_CMD_SET_CONTROL_BUS_SWITCH,
				      &ddc_bus, 1, false);
पूर्ण

अटल bool पूर्णांकel_sdvo_set_value(काष्ठा पूर्णांकel_sdvo *पूर्णांकel_sdvo, u8 cmd, स्थिर व्योम *data, पूर्णांक len)
अणु
	अगर (!पूर्णांकel_sdvo_ग_लिखो_cmd(पूर्णांकel_sdvo, cmd, data, len))
		वापस false;

	वापस पूर्णांकel_sdvo_पढ़ो_response(पूर्णांकel_sdvo, शून्य, 0);
पूर्ण

अटल bool
पूर्णांकel_sdvo_get_value(काष्ठा पूर्णांकel_sdvo *पूर्णांकel_sdvo, u8 cmd, व्योम *value, पूर्णांक len)
अणु
	अगर (!पूर्णांकel_sdvo_ग_लिखो_cmd(पूर्णांकel_sdvo, cmd, शून्य, 0))
		वापस false;

	वापस पूर्णांकel_sdvo_पढ़ो_response(पूर्णांकel_sdvo, value, len);
पूर्ण

अटल bool पूर्णांकel_sdvo_set_target_input(काष्ठा पूर्णांकel_sdvo *पूर्णांकel_sdvo)
अणु
	काष्ठा पूर्णांकel_sdvo_set_target_input_args tarमाला_लो = अणु0पूर्ण;
	वापस पूर्णांकel_sdvo_set_value(पूर्णांकel_sdvo,
				    SDVO_CMD_SET_TARGET_INPUT,
				    &tarमाला_लो, माप(tarमाला_लो));
पूर्ण

/*
 * Return whether each input is trained.
 *
 * This function is making an assumption about the layout of the response,
 * which should be checked against the करोcs.
 */
अटल bool पूर्णांकel_sdvo_get_trained_inमाला_दो(काष्ठा पूर्णांकel_sdvo *पूर्णांकel_sdvo, bool *input_1, bool *input_2)
अणु
	काष्ठा पूर्णांकel_sdvo_get_trained_inमाला_दो_response response;

	BUILD_BUG_ON(माप(response) != 1);
	अगर (!पूर्णांकel_sdvo_get_value(पूर्णांकel_sdvo, SDVO_CMD_GET_TRAINED_INPUTS,
				  &response, माप(response)))
		वापस false;

	*input_1 = response.input0_trained;
	*input_2 = response.input1_trained;
	वापस true;
पूर्ण

अटल bool पूर्णांकel_sdvo_set_active_outमाला_दो(काष्ठा पूर्णांकel_sdvo *पूर्णांकel_sdvo,
					  u16 outमाला_दो)
अणु
	वापस पूर्णांकel_sdvo_set_value(पूर्णांकel_sdvo,
				    SDVO_CMD_SET_ACTIVE_OUTPUTS,
				    &outमाला_दो, माप(outमाला_दो));
पूर्ण

अटल bool पूर्णांकel_sdvo_get_active_outमाला_दो(काष्ठा पूर्णांकel_sdvo *पूर्णांकel_sdvo,
					  u16 *outमाला_दो)
अणु
	वापस पूर्णांकel_sdvo_get_value(पूर्णांकel_sdvo,
				    SDVO_CMD_GET_ACTIVE_OUTPUTS,
				    outमाला_दो, माप(*outमाला_दो));
पूर्ण

अटल bool पूर्णांकel_sdvo_set_encoder_घातer_state(काष्ठा पूर्णांकel_sdvo *पूर्णांकel_sdvo,
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

	वापस पूर्णांकel_sdvo_set_value(पूर्णांकel_sdvo,
				    SDVO_CMD_SET_ENCODER_POWER_STATE, &state, माप(state));
पूर्ण

अटल bool पूर्णांकel_sdvo_get_input_pixel_घड़ी_range(काष्ठा पूर्णांकel_sdvo *पूर्णांकel_sdvo,
						   पूर्णांक *घड़ी_min,
						   पूर्णांक *घड़ी_max)
अणु
	काष्ठा पूर्णांकel_sdvo_pixel_घड़ी_range घड़ीs;

	BUILD_BUG_ON(माप(घड़ीs) != 4);
	अगर (!पूर्णांकel_sdvo_get_value(पूर्णांकel_sdvo,
				  SDVO_CMD_GET_INPUT_PIXEL_CLOCK_RANGE,
				  &घड़ीs, माप(घड़ीs)))
		वापस false;

	/* Convert the values from units of 10 kHz to kHz. */
	*घड़ी_min = घड़ीs.min * 10;
	*घड़ी_max = घड़ीs.max * 10;
	वापस true;
पूर्ण

अटल bool पूर्णांकel_sdvo_set_target_output(काष्ठा पूर्णांकel_sdvo *पूर्णांकel_sdvo,
					 u16 outमाला_दो)
अणु
	वापस पूर्णांकel_sdvo_set_value(पूर्णांकel_sdvo,
				    SDVO_CMD_SET_TARGET_OUTPUT,
				    &outमाला_दो, माप(outमाला_दो));
पूर्ण

अटल bool पूर्णांकel_sdvo_set_timing(काष्ठा पूर्णांकel_sdvo *पूर्णांकel_sdvo, u8 cmd,
				  काष्ठा पूर्णांकel_sdvo_dtd *dtd)
अणु
	वापस पूर्णांकel_sdvo_set_value(पूर्णांकel_sdvo, cmd, &dtd->part1, माप(dtd->part1)) &&
		पूर्णांकel_sdvo_set_value(पूर्णांकel_sdvo, cmd + 1, &dtd->part2, माप(dtd->part2));
पूर्ण

अटल bool पूर्णांकel_sdvo_get_timing(काष्ठा पूर्णांकel_sdvo *पूर्णांकel_sdvo, u8 cmd,
				  काष्ठा पूर्णांकel_sdvo_dtd *dtd)
अणु
	वापस पूर्णांकel_sdvo_get_value(पूर्णांकel_sdvo, cmd, &dtd->part1, माप(dtd->part1)) &&
		पूर्णांकel_sdvo_get_value(पूर्णांकel_sdvo, cmd + 1, &dtd->part2, माप(dtd->part2));
पूर्ण

अटल bool पूर्णांकel_sdvo_set_input_timing(काष्ठा पूर्णांकel_sdvo *पूर्णांकel_sdvo,
					 काष्ठा पूर्णांकel_sdvo_dtd *dtd)
अणु
	वापस पूर्णांकel_sdvo_set_timing(पूर्णांकel_sdvo,
				     SDVO_CMD_SET_INPUT_TIMINGS_PART1, dtd);
पूर्ण

अटल bool पूर्णांकel_sdvo_set_output_timing(काष्ठा पूर्णांकel_sdvo *पूर्णांकel_sdvo,
					 काष्ठा पूर्णांकel_sdvo_dtd *dtd)
अणु
	वापस पूर्णांकel_sdvo_set_timing(पूर्णांकel_sdvo,
				     SDVO_CMD_SET_OUTPUT_TIMINGS_PART1, dtd);
पूर्ण

अटल bool पूर्णांकel_sdvo_get_input_timing(काष्ठा पूर्णांकel_sdvo *पूर्णांकel_sdvo,
					काष्ठा पूर्णांकel_sdvo_dtd *dtd)
अणु
	वापस पूर्णांकel_sdvo_get_timing(पूर्णांकel_sdvo,
				     SDVO_CMD_GET_INPUT_TIMINGS_PART1, dtd);
पूर्ण

अटल bool
पूर्णांकel_sdvo_create_preferred_input_timing(काष्ठा पूर्णांकel_sdvo *पूर्णांकel_sdvo,
					 काष्ठा पूर्णांकel_sdvo_connector *पूर्णांकel_sdvo_connector,
					 u16 घड़ी,
					 u16 width,
					 u16 height)
अणु
	काष्ठा पूर्णांकel_sdvo_preferred_input_timing_args args;

	स_रखो(&args, 0, माप(args));
	args.घड़ी = घड़ी;
	args.width = width;
	args.height = height;
	args.पूर्णांकerlace = 0;

	अगर (IS_LVDS(पूर्णांकel_sdvo_connector)) अणु
		स्थिर काष्ठा drm_display_mode *fixed_mode =
			पूर्णांकel_sdvo_connector->base.panel.fixed_mode;

		अगर (fixed_mode->hdisplay != width ||
		    fixed_mode->vdisplay != height)
			args.scaled = 1;
	पूर्ण

	वापस पूर्णांकel_sdvo_set_value(पूर्णांकel_sdvo,
				    SDVO_CMD_CREATE_PREFERRED_INPUT_TIMING,
				    &args, माप(args));
पूर्ण

अटल bool पूर्णांकel_sdvo_get_preferred_input_timing(काष्ठा पूर्णांकel_sdvo *पूर्णांकel_sdvo,
						  काष्ठा पूर्णांकel_sdvo_dtd *dtd)
अणु
	BUILD_BUG_ON(माप(dtd->part1) != 8);
	BUILD_BUG_ON(माप(dtd->part2) != 8);
	वापस पूर्णांकel_sdvo_get_value(पूर्णांकel_sdvo, SDVO_CMD_GET_PREFERRED_INPUT_TIMING_PART1,
				    &dtd->part1, माप(dtd->part1)) &&
		पूर्णांकel_sdvo_get_value(पूर्णांकel_sdvo, SDVO_CMD_GET_PREFERRED_INPUT_TIMING_PART2,
				     &dtd->part2, माप(dtd->part2));
पूर्ण

अटल bool पूर्णांकel_sdvo_set_घड़ी_rate_mult(काष्ठा पूर्णांकel_sdvo *पूर्णांकel_sdvo, u8 val)
अणु
	वापस पूर्णांकel_sdvo_set_value(पूर्णांकel_sdvo, SDVO_CMD_SET_CLOCK_RATE_MULT, &val, 1);
पूर्ण

अटल व्योम पूर्णांकel_sdvo_get_dtd_from_mode(काष्ठा पूर्णांकel_sdvo_dtd *dtd,
					 स्थिर काष्ठा drm_display_mode *mode)
अणु
	u16 width, height;
	u16 h_blank_len, h_sync_len, v_blank_len, v_sync_len;
	u16 h_sync_offset, v_sync_offset;
	पूर्णांक mode_घड़ी;

	स_रखो(dtd, 0, माप(*dtd));

	width = mode->hdisplay;
	height = mode->vdisplay;

	/* करो some mode translations */
	h_blank_len = mode->htotal - mode->hdisplay;
	h_sync_len = mode->hsync_end - mode->hsync_start;

	v_blank_len = mode->vtotal - mode->vdisplay;
	v_sync_len = mode->vsync_end - mode->vsync_start;

	h_sync_offset = mode->hsync_start - mode->hdisplay;
	v_sync_offset = mode->vsync_start - mode->vdisplay;

	mode_घड़ी = mode->घड़ी;
	mode_घड़ी /= 10;
	dtd->part1.घड़ी = mode_घड़ी;

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
	अगर (mode->flags & DRM_MODE_FLAG_INTERLACE)
		dtd->part2.dtd_flags |= DTD_FLAG_INTERLACE;
	अगर (mode->flags & DRM_MODE_FLAG_PHSYNC)
		dtd->part2.dtd_flags |= DTD_FLAG_HSYNC_POSITIVE;
	अगर (mode->flags & DRM_MODE_FLAG_PVSYNC)
		dtd->part2.dtd_flags |= DTD_FLAG_VSYNC_POSITIVE;

	dtd->part2.v_sync_off_high = v_sync_offset & 0xc0;
पूर्ण

अटल व्योम पूर्णांकel_sdvo_get_mode_from_dtd(काष्ठा drm_display_mode *pmode,
					 स्थिर काष्ठा पूर्णांकel_sdvo_dtd *dtd)
अणु
	काष्ठा drm_display_mode mode = अणुपूर्ण;

	mode.hdisplay = dtd->part1.h_active;
	mode.hdisplay += ((dtd->part1.h_high >> 4) & 0x0f) << 8;
	mode.hsync_start = mode.hdisplay + dtd->part2.h_sync_off;
	mode.hsync_start += (dtd->part2.sync_off_width_high & 0xc0) << 2;
	mode.hsync_end = mode.hsync_start + dtd->part2.h_sync_width;
	mode.hsync_end += (dtd->part2.sync_off_width_high & 0x30) << 4;
	mode.htotal = mode.hdisplay + dtd->part1.h_blank;
	mode.htotal += (dtd->part1.h_high & 0xf) << 8;

	mode.vdisplay = dtd->part1.v_active;
	mode.vdisplay += ((dtd->part1.v_high >> 4) & 0x0f) << 8;
	mode.vsync_start = mode.vdisplay;
	mode.vsync_start += (dtd->part2.v_sync_off_width >> 4) & 0xf;
	mode.vsync_start += (dtd->part2.sync_off_width_high & 0x0c) << 2;
	mode.vsync_start += dtd->part2.v_sync_off_high & 0xc0;
	mode.vsync_end = mode.vsync_start +
		(dtd->part2.v_sync_off_width & 0xf);
	mode.vsync_end += (dtd->part2.sync_off_width_high & 0x3) << 4;
	mode.vtotal = mode.vdisplay + dtd->part1.v_blank;
	mode.vtotal += (dtd->part1.v_high & 0xf) << 8;

	mode.घड़ी = dtd->part1.घड़ी * 10;

	अगर (dtd->part2.dtd_flags & DTD_FLAG_INTERLACE)
		mode.flags |= DRM_MODE_FLAG_INTERLACE;
	अगर (dtd->part2.dtd_flags & DTD_FLAG_HSYNC_POSITIVE)
		mode.flags |= DRM_MODE_FLAG_PHSYNC;
	अन्यथा
		mode.flags |= DRM_MODE_FLAG_NHSYNC;
	अगर (dtd->part2.dtd_flags & DTD_FLAG_VSYNC_POSITIVE)
		mode.flags |= DRM_MODE_FLAG_PVSYNC;
	अन्यथा
		mode.flags |= DRM_MODE_FLAG_NVSYNC;

	drm_mode_set_crtcinfo(&mode, 0);

	drm_mode_copy(pmode, &mode);
पूर्ण

अटल bool पूर्णांकel_sdvo_check_supp_encode(काष्ठा पूर्णांकel_sdvo *पूर्णांकel_sdvo)
अणु
	काष्ठा पूर्णांकel_sdvo_encode encode;

	BUILD_BUG_ON(माप(encode) != 2);
	वापस पूर्णांकel_sdvo_get_value(पूर्णांकel_sdvo,
				  SDVO_CMD_GET_SUPP_ENCODE,
				  &encode, माप(encode));
पूर्ण

अटल bool पूर्णांकel_sdvo_set_encode(काष्ठा पूर्णांकel_sdvo *पूर्णांकel_sdvo,
				  u8 mode)
अणु
	वापस पूर्णांकel_sdvo_set_value(पूर्णांकel_sdvo, SDVO_CMD_SET_ENCODE, &mode, 1);
पूर्ण

अटल bool पूर्णांकel_sdvo_set_colorimetry(काष्ठा पूर्णांकel_sdvo *पूर्णांकel_sdvo,
				       u8 mode)
अणु
	वापस पूर्णांकel_sdvo_set_value(पूर्णांकel_sdvo, SDVO_CMD_SET_COLORIMETRY, &mode, 1);
पूर्ण

अटल bool पूर्णांकel_sdvo_set_pixel_replication(काष्ठा पूर्णांकel_sdvo *पूर्णांकel_sdvo,
					     u8 pixel_repeat)
अणु
	वापस पूर्णांकel_sdvo_set_value(पूर्णांकel_sdvo, SDVO_CMD_SET_PIXEL_REPLI,
				    &pixel_repeat, 1);
पूर्ण

अटल bool पूर्णांकel_sdvo_set_audio_state(काष्ठा पूर्णांकel_sdvo *पूर्णांकel_sdvo,
				       u8 audio_state)
अणु
	वापस पूर्णांकel_sdvo_set_value(पूर्णांकel_sdvo, SDVO_CMD_SET_AUDIO_STAT,
				    &audio_state, 1);
पूर्ण

अटल bool पूर्णांकel_sdvo_get_hbuf_size(काष्ठा पूर्णांकel_sdvo *पूर्णांकel_sdvo,
				     u8 *hbuf_size)
अणु
	अगर (!पूर्णांकel_sdvo_get_value(पूर्णांकel_sdvo, SDVO_CMD_GET_HBUF_INFO,
				  hbuf_size, 1))
		वापस false;

	/* Buffer size is 0 based, hooray! However zero means zero. */
	अगर (*hbuf_size)
		(*hbuf_size)++;

	वापस true;
पूर्ण

#अगर 0
अटल व्योम पूर्णांकel_sdvo_dump_hdmi_buf(काष्ठा पूर्णांकel_sdvo *पूर्णांकel_sdvo)
अणु
	पूर्णांक i, j;
	u8 set_buf_index[2];
	u8 av_split;
	u8 buf_size;
	u8 buf[48];
	u8 *pos;

	पूर्णांकel_sdvo_get_value(encoder, SDVO_CMD_GET_HBUF_AV_SPLIT, &av_split, 1);

	क्रम (i = 0; i <= av_split; i++) अणु
		set_buf_index[0] = i; set_buf_index[1] = 0;
		पूर्णांकel_sdvo_ग_लिखो_cmd(encoder, SDVO_CMD_SET_HBUF_INDEX,
				     set_buf_index, 2);
		पूर्णांकel_sdvo_ग_लिखो_cmd(encoder, SDVO_CMD_GET_HBUF_INFO, शून्य, 0);
		पूर्णांकel_sdvo_पढ़ो_response(encoder, &buf_size, 1);

		pos = buf;
		क्रम (j = 0; j <= buf_size; j += 8) अणु
			पूर्णांकel_sdvo_ग_लिखो_cmd(encoder, SDVO_CMD_GET_HBUF_DATA,
					     शून्य, 0);
			पूर्णांकel_sdvo_पढ़ो_response(encoder, pos, 8);
			pos += 8;
		पूर्ण
	पूर्ण
पूर्ण
#पूर्ण_अगर

अटल bool पूर्णांकel_sdvo_ग_लिखो_infoframe(काष्ठा पूर्णांकel_sdvo *पूर्णांकel_sdvo,
				       अचिन्हित पूर्णांक अगर_index, u8 tx_rate,
				       स्थिर u8 *data, अचिन्हित पूर्णांक length)
अणु
	u8 set_buf_index[2] = अणु अगर_index, 0 पूर्ण;
	u8 hbuf_size, पंचांगp[8];
	पूर्णांक i;

	अगर (!पूर्णांकel_sdvo_set_value(पूर्णांकel_sdvo,
				  SDVO_CMD_SET_HBUF_INDEX,
				  set_buf_index, 2))
		वापस false;

	अगर (!पूर्णांकel_sdvo_get_hbuf_size(पूर्णांकel_sdvo, &hbuf_size))
		वापस false;

	DRM_DEBUG_KMS("writing sdvo hbuf: %i, length %u, hbuf_size: %i\n",
		      अगर_index, length, hbuf_size);

	अगर (hbuf_size < length)
		वापस false;

	क्रम (i = 0; i < hbuf_size; i += 8) अणु
		स_रखो(पंचांगp, 0, 8);
		अगर (i < length)
			स_नकल(पंचांगp, data + i, min_t(अचिन्हित, 8, length - i));

		अगर (!पूर्णांकel_sdvo_set_value(पूर्णांकel_sdvo,
					  SDVO_CMD_SET_HBUF_DATA,
					  पंचांगp, 8))
			वापस false;
	पूर्ण

	वापस पूर्णांकel_sdvo_set_value(पूर्णांकel_sdvo,
				    SDVO_CMD_SET_HBUF_TXRATE,
				    &tx_rate, 1);
पूर्ण

अटल sमाप_प्रकार पूर्णांकel_sdvo_पढ़ो_infoframe(काष्ठा पूर्णांकel_sdvo *पूर्णांकel_sdvo,
					 अचिन्हित पूर्णांक अगर_index,
					 u8 *data, अचिन्हित पूर्णांक length)
अणु
	u8 set_buf_index[2] = अणु अगर_index, 0 पूर्ण;
	u8 hbuf_size, tx_rate, av_split;
	पूर्णांक i;

	अगर (!पूर्णांकel_sdvo_get_value(पूर्णांकel_sdvo,
				  SDVO_CMD_GET_HBUF_AV_SPLIT,
				  &av_split, 1))
		वापस -ENXIO;

	अगर (av_split < अगर_index)
		वापस 0;

	अगर (!पूर्णांकel_sdvo_set_value(पूर्णांकel_sdvo,
				  SDVO_CMD_SET_HBUF_INDEX,
				  set_buf_index, 2))
		वापस -ENXIO;

	अगर (!पूर्णांकel_sdvo_get_value(पूर्णांकel_sdvo,
				  SDVO_CMD_GET_HBUF_TXRATE,
				  &tx_rate, 1))
		वापस -ENXIO;

	अगर (tx_rate == SDVO_HBUF_TX_DISABLED)
		वापस 0;

	अगर (!पूर्णांकel_sdvo_get_hbuf_size(पूर्णांकel_sdvo, &hbuf_size))
		वापस false;

	DRM_DEBUG_KMS("reading sdvo hbuf: %i, length %u, hbuf_size: %i\n",
		      अगर_index, length, hbuf_size);

	hbuf_size = min_t(अचिन्हित पूर्णांक, length, hbuf_size);

	क्रम (i = 0; i < hbuf_size; i += 8) अणु
		अगर (!पूर्णांकel_sdvo_ग_लिखो_cmd(पूर्णांकel_sdvo, SDVO_CMD_GET_HBUF_DATA, शून्य, 0))
			वापस -ENXIO;
		अगर (!पूर्णांकel_sdvo_पढ़ो_response(पूर्णांकel_sdvo, &data[i],
					      min_t(अचिन्हित पूर्णांक, 8, hbuf_size - i)))
			वापस -ENXIO;
	पूर्ण

	वापस hbuf_size;
पूर्ण

अटल bool पूर्णांकel_sdvo_compute_avi_infoframe(काष्ठा पूर्णांकel_sdvo *पूर्णांकel_sdvo,
					     काष्ठा पूर्णांकel_crtc_state *crtc_state,
					     काष्ठा drm_connector_state *conn_state)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(पूर्णांकel_sdvo->base.base.dev);
	काष्ठा hdmi_avi_infoframe *frame = &crtc_state->infoframes.avi.avi;
	स्थिर काष्ठा drm_display_mode *adjusted_mode =
		&crtc_state->hw.adjusted_mode;
	पूर्णांक ret;

	अगर (!crtc_state->has_hdmi_sink)
		वापस true;

	crtc_state->infoframes.enable |=
		पूर्णांकel_hdmi_infoframe_enable(HDMI_INFOFRAME_TYPE_AVI);

	ret = drm_hdmi_avi_infoframe_from_display_mode(frame,
						       conn_state->connector,
						       adjusted_mode);
	अगर (ret)
		वापस false;

	drm_hdmi_avi_infoframe_quant_range(frame,
					   conn_state->connector,
					   adjusted_mode,
					   crtc_state->limited_color_range ?
					   HDMI_QUANTIZATION_RANGE_LIMITED :
					   HDMI_QUANTIZATION_RANGE_FULL);

	ret = hdmi_avi_infoframe_check(frame);
	अगर (drm_WARN_ON(&dev_priv->drm, ret))
		वापस false;

	वापस true;
पूर्ण

अटल bool पूर्णांकel_sdvo_set_avi_infoframe(काष्ठा पूर्णांकel_sdvo *पूर्णांकel_sdvo,
					 स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(पूर्णांकel_sdvo->base.base.dev);
	u8 sdvo_data[HDMI_INFOFRAME_SIZE(AVI)];
	स्थिर जोड़ hdmi_infoframe *frame = &crtc_state->infoframes.avi;
	sमाप_प्रकार len;

	अगर ((crtc_state->infoframes.enable &
	     पूर्णांकel_hdmi_infoframe_enable(HDMI_INFOFRAME_TYPE_AVI)) == 0)
		वापस true;

	अगर (drm_WARN_ON(&dev_priv->drm,
			frame->any.type != HDMI_INFOFRAME_TYPE_AVI))
		वापस false;

	len = hdmi_infoframe_pack_only(frame, sdvo_data, माप(sdvo_data));
	अगर (drm_WARN_ON(&dev_priv->drm, len < 0))
		वापस false;

	वापस पूर्णांकel_sdvo_ग_लिखो_infoframe(पूर्णांकel_sdvo, SDVO_HBUF_INDEX_AVI_IF,
					  SDVO_HBUF_TX_VSYNC,
					  sdvo_data, len);
पूर्ण

अटल व्योम पूर्णांकel_sdvo_get_avi_infoframe(काष्ठा पूर्णांकel_sdvo *पूर्णांकel_sdvo,
					 काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	u8 sdvo_data[HDMI_INFOFRAME_SIZE(AVI)];
	जोड़ hdmi_infoframe *frame = &crtc_state->infoframes.avi;
	sमाप_प्रकार len;
	पूर्णांक ret;

	अगर (!crtc_state->has_hdmi_sink)
		वापस;

	len = पूर्णांकel_sdvo_पढ़ो_infoframe(पूर्णांकel_sdvo, SDVO_HBUF_INDEX_AVI_IF,
					sdvo_data, माप(sdvo_data));
	अगर (len < 0) अणु
		DRM_DEBUG_KMS("failed to read AVI infoframe\n");
		वापस;
	पूर्ण अन्यथा अगर (len == 0) अणु
		वापस;
	पूर्ण

	crtc_state->infoframes.enable |=
		पूर्णांकel_hdmi_infoframe_enable(HDMI_INFOFRAME_TYPE_AVI);

	ret = hdmi_infoframe_unpack(frame, sdvo_data, len);
	अगर (ret) अणु
		DRM_DEBUG_KMS("Failed to unpack AVI infoframe\n");
		वापस;
	पूर्ण

	अगर (frame->any.type != HDMI_INFOFRAME_TYPE_AVI)
		DRM_DEBUG_KMS("Found the wrong infoframe type 0x%x (expected 0x%02x)\n",
			      frame->any.type, HDMI_INFOFRAME_TYPE_AVI);
पूर्ण

अटल bool पूर्णांकel_sdvo_set_tv_क्रमmat(काष्ठा पूर्णांकel_sdvo *पूर्णांकel_sdvo,
				     स्थिर काष्ठा drm_connector_state *conn_state)
अणु
	काष्ठा पूर्णांकel_sdvo_tv_क्रमmat क्रमmat;
	u32 क्रमmat_map;

	क्रमmat_map = 1 << conn_state->tv.mode;
	स_रखो(&क्रमmat, 0, माप(क्रमmat));
	स_नकल(&क्रमmat, &क्रमmat_map, min(माप(क्रमmat), माप(क्रमmat_map)));

	BUILD_BUG_ON(माप(क्रमmat) != 6);
	वापस पूर्णांकel_sdvo_set_value(पूर्णांकel_sdvo,
				    SDVO_CMD_SET_TV_FORMAT,
				    &क्रमmat, माप(क्रमmat));
पूर्ण

अटल bool
पूर्णांकel_sdvo_set_output_timings_from_mode(काष्ठा पूर्णांकel_sdvo *पूर्णांकel_sdvo,
					स्थिर काष्ठा drm_display_mode *mode)
अणु
	काष्ठा पूर्णांकel_sdvo_dtd output_dtd;

	अगर (!पूर्णांकel_sdvo_set_target_output(पूर्णांकel_sdvo,
					  पूर्णांकel_sdvo->attached_output))
		वापस false;

	पूर्णांकel_sdvo_get_dtd_from_mode(&output_dtd, mode);
	अगर (!पूर्णांकel_sdvo_set_output_timing(पूर्णांकel_sdvo, &output_dtd))
		वापस false;

	वापस true;
पूर्ण

/*
 * Asks the sdvo controller क्रम the preferred input mode given the output mode.
 * Unक्रमtunately we have to set up the full output mode to करो that.
 */
अटल bool
पूर्णांकel_sdvo_get_preferred_input_mode(काष्ठा पूर्णांकel_sdvo *पूर्णांकel_sdvo,
				    काष्ठा पूर्णांकel_sdvo_connector *पूर्णांकel_sdvo_connector,
				    स्थिर काष्ठा drm_display_mode *mode,
				    काष्ठा drm_display_mode *adjusted_mode)
अणु
	काष्ठा पूर्णांकel_sdvo_dtd input_dtd;

	/* Reset the input timing to the screen. Assume always input 0. */
	अगर (!पूर्णांकel_sdvo_set_target_input(पूर्णांकel_sdvo))
		वापस false;

	अगर (!पूर्णांकel_sdvo_create_preferred_input_timing(पूर्णांकel_sdvo,
						      पूर्णांकel_sdvo_connector,
						      mode->घड़ी / 10,
						      mode->hdisplay,
						      mode->vdisplay))
		वापस false;

	अगर (!पूर्णांकel_sdvo_get_preferred_input_timing(पूर्णांकel_sdvo,
						   &input_dtd))
		वापस false;

	पूर्णांकel_sdvo_get_mode_from_dtd(adjusted_mode, &input_dtd);
	पूर्णांकel_sdvo->dtd_sdvo_flags = input_dtd.part2.sdvo_flags;

	वापस true;
पूर्ण

अटल व्योम i9xx_adjust_sdvo_tv_घड़ी(काष्ठा पूर्णांकel_crtc_state *pipe_config)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(pipe_config->uapi.crtc->dev);
	अचिन्हित करोtघड़ी = pipe_config->port_घड़ी;
	काष्ठा dpll *घड़ी = &pipe_config->dpll;

	/*
	 * SDVO TV has fixed PLL values depend on its घड़ी range,
	 * this mirrors vbios setting.
	 */
	अगर (करोtघड़ी >= 100000 && करोtघड़ी < 140500) अणु
		घड़ी->p1 = 2;
		घड़ी->p2 = 10;
		घड़ी->n = 3;
		घड़ी->m1 = 16;
		घड़ी->m2 = 8;
	पूर्ण अन्यथा अगर (करोtघड़ी >= 140500 && करोtघड़ी <= 200000) अणु
		घड़ी->p1 = 1;
		घड़ी->p2 = 10;
		घड़ी->n = 6;
		घड़ी->m1 = 12;
		घड़ी->m2 = 8;
	पूर्ण अन्यथा अणु
		drm_WARN(&dev_priv->drm, 1,
			 "SDVO TV clock out of range: %i\n", करोtघड़ी);
	पूर्ण

	pipe_config->घड़ी_set = true;
पूर्ण

अटल bool पूर्णांकel_has_hdmi_sink(काष्ठा पूर्णांकel_sdvo *sdvo,
				स्थिर काष्ठा drm_connector_state *conn_state)
अणु
	वापस sdvo->has_hdmi_monitor &&
		READ_ONCE(to_पूर्णांकel_digital_connector_state(conn_state)->क्रमce_audio) != HDMI_AUDIO_OFF_DVI;
पूर्ण

अटल bool पूर्णांकel_sdvo_limited_color_range(काष्ठा पूर्णांकel_encoder *encoder,
					   स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
					   स्थिर काष्ठा drm_connector_state *conn_state)
अणु
	काष्ठा पूर्णांकel_sdvo *पूर्णांकel_sdvo = to_sdvo(encoder);

	अगर ((पूर्णांकel_sdvo->colorimetry_cap & SDVO_COLORIMETRY_RGB220) == 0)
		वापस false;

	वापस पूर्णांकel_hdmi_limited_color_range(crtc_state, conn_state);
पूर्ण

अटल पूर्णांक पूर्णांकel_sdvo_compute_config(काष्ठा पूर्णांकel_encoder *encoder,
				     काष्ठा पूर्णांकel_crtc_state *pipe_config,
				     काष्ठा drm_connector_state *conn_state)
अणु
	काष्ठा पूर्णांकel_sdvo *पूर्णांकel_sdvo = to_sdvo(encoder);
	काष्ठा पूर्णांकel_sdvo_connector_state *पूर्णांकel_sdvo_state =
		to_पूर्णांकel_sdvo_connector_state(conn_state);
	काष्ठा पूर्णांकel_sdvo_connector *पूर्णांकel_sdvo_connector =
		to_पूर्णांकel_sdvo_connector(conn_state->connector);
	काष्ठा drm_display_mode *adjusted_mode = &pipe_config->hw.adjusted_mode;
	काष्ठा drm_display_mode *mode = &pipe_config->hw.mode;

	DRM_DEBUG_KMS("forcing bpc to 8 for SDVO\n");
	pipe_config->pipe_bpp = 8*3;
	pipe_config->output_क्रमmat = INTEL_OUTPUT_FORMAT_RGB;

	अगर (HAS_PCH_SPLIT(to_i915(encoder->base.dev)))
		pipe_config->has_pch_encoder = true;

	/*
	 * We need to स्थिरruct preferred input timings based on our
	 * output timings.  To करो that, we have to set the output
	 * timings, even though this isn't really the right place in
	 * the sequence to करो it. Oh well.
	 */
	अगर (IS_TV(पूर्णांकel_sdvo_connector)) अणु
		अगर (!पूर्णांकel_sdvo_set_output_timings_from_mode(पूर्णांकel_sdvo, mode))
			वापस -EINVAL;

		(व्योम) पूर्णांकel_sdvo_get_preferred_input_mode(पूर्णांकel_sdvo,
							   पूर्णांकel_sdvo_connector,
							   mode,
							   adjusted_mode);
		pipe_config->sdvo_tv_घड़ी = true;
	पूर्ण अन्यथा अगर (IS_LVDS(पूर्णांकel_sdvo_connector)) अणु
		अगर (!पूर्णांकel_sdvo_set_output_timings_from_mode(पूर्णांकel_sdvo,
							     पूर्णांकel_sdvo_connector->base.panel.fixed_mode))
			वापस -EINVAL;

		(व्योम) पूर्णांकel_sdvo_get_preferred_input_mode(पूर्णांकel_sdvo,
							   पूर्णांकel_sdvo_connector,
							   mode,
							   adjusted_mode);
	पूर्ण

	अगर (adjusted_mode->flags & DRM_MODE_FLAG_DBLSCAN)
		वापस -EINVAL;

	/*
	 * Make the CRTC code factor in the SDVO pixel multiplier.  The
	 * SDVO device will factor out the multiplier during mode_set.
	 */
	pipe_config->pixel_multiplier =
		पूर्णांकel_sdvo_get_pixel_multiplier(adjusted_mode);

	pipe_config->has_hdmi_sink = पूर्णांकel_has_hdmi_sink(पूर्णांकel_sdvo, conn_state);

	अगर (pipe_config->has_hdmi_sink) अणु
		अगर (पूर्णांकel_sdvo_state->base.क्रमce_audio == HDMI_AUDIO_AUTO)
			pipe_config->has_audio = पूर्णांकel_sdvo->has_hdmi_audio;
		अन्यथा
			pipe_config->has_audio =
				पूर्णांकel_sdvo_state->base.क्रमce_audio == HDMI_AUDIO_ON;
	पूर्ण

	pipe_config->limited_color_range =
		पूर्णांकel_sdvo_limited_color_range(encoder, pipe_config,
					       conn_state);

	/* Clock computation needs to happen after pixel multiplier. */
	अगर (IS_TV(पूर्णांकel_sdvo_connector))
		i9xx_adjust_sdvo_tv_घड़ी(pipe_config);

	अगर (conn_state->picture_aspect_ratio)
		adjusted_mode->picture_aspect_ratio =
			conn_state->picture_aspect_ratio;

	अगर (!पूर्णांकel_sdvo_compute_avi_infoframe(पूर्णांकel_sdvo,
					      pipe_config, conn_state)) अणु
		DRM_DEBUG_KMS("bad AVI infoframe\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

#घोषणा UPDATE_PROPERTY(input, NAME) \
	करो अणु \
		val = input; \
		पूर्णांकel_sdvo_set_value(पूर्णांकel_sdvo, SDVO_CMD_SET_##NAME, &val, माप(val)); \
	पूर्ण जबतक (0)

अटल व्योम पूर्णांकel_sdvo_update_props(काष्ठा पूर्णांकel_sdvo *पूर्णांकel_sdvo,
				    स्थिर काष्ठा पूर्णांकel_sdvo_connector_state *sdvo_state)
अणु
	स्थिर काष्ठा drm_connector_state *conn_state = &sdvo_state->base.base;
	काष्ठा पूर्णांकel_sdvo_connector *पूर्णांकel_sdvo_conn =
		to_पूर्णांकel_sdvo_connector(conn_state->connector);
	u16 val;

	अगर (पूर्णांकel_sdvo_conn->left)
		UPDATE_PROPERTY(sdvo_state->tv.overscan_h, OVERSCAN_H);

	अगर (पूर्णांकel_sdvo_conn->top)
		UPDATE_PROPERTY(sdvo_state->tv.overscan_v, OVERSCAN_V);

	अगर (पूर्णांकel_sdvo_conn->hpos)
		UPDATE_PROPERTY(sdvo_state->tv.hpos, HPOS);

	अगर (पूर्णांकel_sdvo_conn->vpos)
		UPDATE_PROPERTY(sdvo_state->tv.vpos, VPOS);

	अगर (पूर्णांकel_sdvo_conn->saturation)
		UPDATE_PROPERTY(conn_state->tv.saturation, SATURATION);

	अगर (पूर्णांकel_sdvo_conn->contrast)
		UPDATE_PROPERTY(conn_state->tv.contrast, CONTRAST);

	अगर (पूर्णांकel_sdvo_conn->hue)
		UPDATE_PROPERTY(conn_state->tv.hue, HUE);

	अगर (पूर्णांकel_sdvo_conn->brightness)
		UPDATE_PROPERTY(conn_state->tv.brightness, BRIGHTNESS);

	अगर (पूर्णांकel_sdvo_conn->sharpness)
		UPDATE_PROPERTY(sdvo_state->tv.sharpness, SHARPNESS);

	अगर (पूर्णांकel_sdvo_conn->flicker_filter)
		UPDATE_PROPERTY(sdvo_state->tv.flicker_filter, FLICKER_FILTER);

	अगर (पूर्णांकel_sdvo_conn->flicker_filter_2d)
		UPDATE_PROPERTY(sdvo_state->tv.flicker_filter_2d, FLICKER_FILTER_2D);

	अगर (पूर्णांकel_sdvo_conn->flicker_filter_adaptive)
		UPDATE_PROPERTY(sdvo_state->tv.flicker_filter_adaptive, FLICKER_FILTER_ADAPTIVE);

	अगर (पूर्णांकel_sdvo_conn->tv_chroma_filter)
		UPDATE_PROPERTY(sdvo_state->tv.chroma_filter, TV_CHROMA_FILTER);

	अगर (पूर्णांकel_sdvo_conn->tv_luma_filter)
		UPDATE_PROPERTY(sdvo_state->tv.luma_filter, TV_LUMA_FILTER);

	अगर (पूर्णांकel_sdvo_conn->करोt_crawl)
		UPDATE_PROPERTY(sdvo_state->tv.करोt_crawl, DOT_CRAWL);

#अघोषित UPDATE_PROPERTY
पूर्ण

अटल व्योम पूर्णांकel_sdvo_pre_enable(काष्ठा पूर्णांकel_atomic_state *state,
				  काष्ठा पूर्णांकel_encoder *पूर्णांकel_encoder,
				  स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
				  स्थिर काष्ठा drm_connector_state *conn_state)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(पूर्णांकel_encoder->base.dev);
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(crtc_state->uapi.crtc);
	स्थिर काष्ठा drm_display_mode *adjusted_mode = &crtc_state->hw.adjusted_mode;
	स्थिर काष्ठा पूर्णांकel_sdvo_connector_state *sdvo_state =
		to_पूर्णांकel_sdvo_connector_state(conn_state);
	स्थिर काष्ठा पूर्णांकel_sdvo_connector *पूर्णांकel_sdvo_connector =
		to_पूर्णांकel_sdvo_connector(conn_state->connector);
	स्थिर काष्ठा drm_display_mode *mode = &crtc_state->hw.mode;
	काष्ठा पूर्णांकel_sdvo *पूर्णांकel_sdvo = to_sdvo(पूर्णांकel_encoder);
	u32 sdvox;
	काष्ठा पूर्णांकel_sdvo_in_out_map in_out;
	काष्ठा पूर्णांकel_sdvo_dtd input_dtd, output_dtd;
	पूर्णांक rate;

	पूर्णांकel_sdvo_update_props(पूर्णांकel_sdvo, sdvo_state);

	/*
	 * First, set the input mapping क्रम the first input to our controlled
	 * output. This is only correct अगर we're a single-input device, in
	 * which हाल the first input is the output from the appropriate SDVO
	 * channel on the motherboard.  In a two-input device, the first input
	 * will be SDVOB and the second SDVOC.
	 */
	in_out.in0 = पूर्णांकel_sdvo->attached_output;
	in_out.in1 = 0;

	पूर्णांकel_sdvo_set_value(पूर्णांकel_sdvo,
			     SDVO_CMD_SET_IN_OUT_MAP,
			     &in_out, माप(in_out));

	/* Set the output timings to the screen */
	अगर (!पूर्णांकel_sdvo_set_target_output(पूर्णांकel_sdvo,
					  पूर्णांकel_sdvo->attached_output))
		वापस;

	/* lvds has a special fixed output timing. */
	अगर (IS_LVDS(पूर्णांकel_sdvo_connector))
		पूर्णांकel_sdvo_get_dtd_from_mode(&output_dtd,
					     पूर्णांकel_sdvo_connector->base.panel.fixed_mode);
	अन्यथा
		पूर्णांकel_sdvo_get_dtd_from_mode(&output_dtd, mode);
	अगर (!पूर्णांकel_sdvo_set_output_timing(पूर्णांकel_sdvo, &output_dtd))
		drm_info(&dev_priv->drm,
			 "Setting output timings on %s failed\n",
			 SDVO_NAME(पूर्णांकel_sdvo));

	/* Set the input timing to the screen. Assume always input 0. */
	अगर (!पूर्णांकel_sdvo_set_target_input(पूर्णांकel_sdvo))
		वापस;

	अगर (crtc_state->has_hdmi_sink) अणु
		पूर्णांकel_sdvo_set_encode(पूर्णांकel_sdvo, SDVO_ENCODE_HDMI);
		पूर्णांकel_sdvo_set_colorimetry(पूर्णांकel_sdvo,
					   crtc_state->limited_color_range ?
					   SDVO_COLORIMETRY_RGB220 :
					   SDVO_COLORIMETRY_RGB256);
		पूर्णांकel_sdvo_set_avi_infoframe(पूर्णांकel_sdvo, crtc_state);
		पूर्णांकel_sdvo_set_pixel_replication(पूर्णांकel_sdvo,
						 !!(adjusted_mode->flags &
						    DRM_MODE_FLAG_DBLCLK));
	पूर्ण अन्यथा
		पूर्णांकel_sdvo_set_encode(पूर्णांकel_sdvo, SDVO_ENCODE_DVI);

	अगर (IS_TV(पूर्णांकel_sdvo_connector) &&
	    !पूर्णांकel_sdvo_set_tv_क्रमmat(पूर्णांकel_sdvo, conn_state))
		वापस;

	पूर्णांकel_sdvo_get_dtd_from_mode(&input_dtd, adjusted_mode);

	अगर (IS_TV(पूर्णांकel_sdvo_connector) || IS_LVDS(पूर्णांकel_sdvo_connector))
		input_dtd.part2.sdvo_flags = पूर्णांकel_sdvo->dtd_sdvo_flags;
	अगर (!पूर्णांकel_sdvo_set_input_timing(पूर्णांकel_sdvo, &input_dtd))
		drm_info(&dev_priv->drm,
			 "Setting input timings on %s failed\n",
			 SDVO_NAME(पूर्णांकel_sdvo));

	चयन (crtc_state->pixel_multiplier) अणु
	शेष:
		drm_WARN(&dev_priv->drm, 1,
			 "unknown pixel multiplier specified\n");
		fallthrough;
	हाल 1: rate = SDVO_CLOCK_RATE_MULT_1X; अवरोध;
	हाल 2: rate = SDVO_CLOCK_RATE_MULT_2X; अवरोध;
	हाल 4: rate = SDVO_CLOCK_RATE_MULT_4X; अवरोध;
	पूर्ण
	अगर (!पूर्णांकel_sdvo_set_घड़ी_rate_mult(पूर्णांकel_sdvo, rate))
		वापस;

	/* Set the SDVO control regs. */
	अगर (DISPLAY_VER(dev_priv) >= 4) अणु
		/* The real mode polarity is set by the SDVO commands, using
		 * काष्ठा पूर्णांकel_sdvo_dtd. */
		sdvox = SDVO_VSYNC_ACTIVE_HIGH | SDVO_HSYNC_ACTIVE_HIGH;
		अगर (DISPLAY_VER(dev_priv) < 5)
			sdvox |= SDVO_BORDER_ENABLE;
	पूर्ण अन्यथा अणु
		sdvox = पूर्णांकel_de_पढ़ो(dev_priv, पूर्णांकel_sdvo->sdvo_reg);
		अगर (पूर्णांकel_sdvo->port == PORT_B)
			sdvox &= SDVOB_PRESERVE_MASK;
		अन्यथा
			sdvox &= SDVOC_PRESERVE_MASK;
		sdvox |= (9 << 19) | SDVO_BORDER_ENABLE;
	पूर्ण

	अगर (HAS_PCH_CPT(dev_priv))
		sdvox |= SDVO_PIPE_SEL_CPT(crtc->pipe);
	अन्यथा
		sdvox |= SDVO_PIPE_SEL(crtc->pipe);

	अगर (DISPLAY_VER(dev_priv) >= 4) अणु
		/* करोne in crtc_mode_set as the dpll_md reg must be written early */
	पूर्ण अन्यथा अगर (IS_I945G(dev_priv) || IS_I945GM(dev_priv) ||
		   IS_G33(dev_priv) || IS_PINEVIEW(dev_priv)) अणु
		/* करोne in crtc_mode_set as it lives inside the dpll रेजिस्टर */
	पूर्ण अन्यथा अणु
		sdvox |= (crtc_state->pixel_multiplier - 1)
			<< SDVO_PORT_MULTIPLY_SHIFT;
	पूर्ण

	अगर (input_dtd.part2.sdvo_flags & SDVO_NEED_TO_STALL &&
	    DISPLAY_VER(dev_priv) < 5)
		sdvox |= SDVO_STALL_SELECT;
	पूर्णांकel_sdvo_ग_लिखो_sdvox(पूर्णांकel_sdvo, sdvox);
पूर्ण

अटल bool पूर्णांकel_sdvo_connector_get_hw_state(काष्ठा पूर्णांकel_connector *connector)
अणु
	काष्ठा पूर्णांकel_sdvo_connector *पूर्णांकel_sdvo_connector =
		to_पूर्णांकel_sdvo_connector(&connector->base);
	काष्ठा पूर्णांकel_sdvo *पूर्णांकel_sdvo = पूर्णांकel_attached_sdvo(connector);
	u16 active_outमाला_दो = 0;

	पूर्णांकel_sdvo_get_active_outमाला_दो(पूर्णांकel_sdvo, &active_outमाला_दो);

	वापस active_outमाला_दो & पूर्णांकel_sdvo_connector->output_flag;
पूर्ण

bool पूर्णांकel_sdvo_port_enabled(काष्ठा drm_i915_निजी *dev_priv,
			     i915_reg_t sdvo_reg, क्रमागत pipe *pipe)
अणु
	u32 val;

	val = पूर्णांकel_de_पढ़ो(dev_priv, sdvo_reg);

	/* निश्चितs want to know the pipe even अगर the port is disabled */
	अगर (HAS_PCH_CPT(dev_priv))
		*pipe = (val & SDVO_PIPE_SEL_MASK_CPT) >> SDVO_PIPE_SEL_SHIFT_CPT;
	अन्यथा अगर (IS_CHERRYVIEW(dev_priv))
		*pipe = (val & SDVO_PIPE_SEL_MASK_CHV) >> SDVO_PIPE_SEL_SHIFT_CHV;
	अन्यथा
		*pipe = (val & SDVO_PIPE_SEL_MASK) >> SDVO_PIPE_SEL_SHIFT;

	वापस val & SDVO_ENABLE;
पूर्ण

अटल bool पूर्णांकel_sdvo_get_hw_state(काष्ठा पूर्णांकel_encoder *encoder,
				    क्रमागत pipe *pipe)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	काष्ठा पूर्णांकel_sdvo *पूर्णांकel_sdvo = to_sdvo(encoder);
	u16 active_outमाला_दो = 0;
	bool ret;

	पूर्णांकel_sdvo_get_active_outमाला_दो(पूर्णांकel_sdvo, &active_outमाला_दो);

	ret = पूर्णांकel_sdvo_port_enabled(dev_priv, पूर्णांकel_sdvo->sdvo_reg, pipe);

	वापस ret || active_outमाला_दो;
पूर्ण

अटल व्योम पूर्णांकel_sdvo_get_config(काष्ठा पूर्णांकel_encoder *encoder,
				  काष्ठा पूर्णांकel_crtc_state *pipe_config)
अणु
	काष्ठा drm_device *dev = encoder->base.dev;
	काष्ठा drm_i915_निजी *dev_priv = to_i915(dev);
	काष्ठा पूर्णांकel_sdvo *पूर्णांकel_sdvo = to_sdvo(encoder);
	काष्ठा पूर्णांकel_sdvo_dtd dtd;
	पूर्णांक encoder_pixel_multiplier = 0;
	पूर्णांक करोtघड़ी;
	u32 flags = 0, sdvox;
	u8 val;
	bool ret;

	pipe_config->output_types |= BIT(INTEL_OUTPUT_SDVO);

	sdvox = पूर्णांकel_de_पढ़ो(dev_priv, पूर्णांकel_sdvo->sdvo_reg);

	ret = पूर्णांकel_sdvo_get_input_timing(पूर्णांकel_sdvo, &dtd);
	अगर (!ret) अणु
		/*
		 * Some sdvo encoders are not spec compliant and करोn't
		 * implement the mandatory get_timings function.
		 */
		drm_dbg(&dev_priv->drm, "failed to retrieve SDVO DTD\n");
		pipe_config->quirks |= PIPE_CONFIG_QUIRK_MODE_SYNC_FLAGS;
	पूर्ण अन्यथा अणु
		अगर (dtd.part2.dtd_flags & DTD_FLAG_HSYNC_POSITIVE)
			flags |= DRM_MODE_FLAG_PHSYNC;
		अन्यथा
			flags |= DRM_MODE_FLAG_NHSYNC;

		अगर (dtd.part2.dtd_flags & DTD_FLAG_VSYNC_POSITIVE)
			flags |= DRM_MODE_FLAG_PVSYNC;
		अन्यथा
			flags |= DRM_MODE_FLAG_NVSYNC;
	पूर्ण

	pipe_config->hw.adjusted_mode.flags |= flags;

	/*
	 * pixel multiplier पढ़ोout is tricky: Only on i915g/gm it is stored in
	 * the sdvo port रेजिस्टर, on all other platक्रमms it is part of the dpll
	 * state. Since the general pipe state पढ़ोout happens beक्रमe the
	 * encoder->get_config we so alपढ़ोy have a valid pixel multplier on all
	 * other platfroms.
	 */
	अगर (IS_I915G(dev_priv) || IS_I915GM(dev_priv)) अणु
		pipe_config->pixel_multiplier =
			((sdvox & SDVO_PORT_MULTIPLY_MASK)
			 >> SDVO_PORT_MULTIPLY_SHIFT) + 1;
	पूर्ण

	करोtघड़ी = pipe_config->port_घड़ी;

	अगर (pipe_config->pixel_multiplier)
		करोtघड़ी /= pipe_config->pixel_multiplier;

	pipe_config->hw.adjusted_mode.crtc_घड़ी = करोtघड़ी;

	/* Cross check the port pixel multiplier with the sdvo encoder state. */
	अगर (पूर्णांकel_sdvo_get_value(पूर्णांकel_sdvo, SDVO_CMD_GET_CLOCK_RATE_MULT,
				 &val, 1)) अणु
		चयन (val) अणु
		हाल SDVO_CLOCK_RATE_MULT_1X:
			encoder_pixel_multiplier = 1;
			अवरोध;
		हाल SDVO_CLOCK_RATE_MULT_2X:
			encoder_pixel_multiplier = 2;
			अवरोध;
		हाल SDVO_CLOCK_RATE_MULT_4X:
			encoder_pixel_multiplier = 4;
			अवरोध;
		पूर्ण
	पूर्ण

	drm_WARN(dev,
		 encoder_pixel_multiplier != pipe_config->pixel_multiplier,
		 "SDVO pixel multiplier mismatch, port: %i, encoder: %i\n",
		 pipe_config->pixel_multiplier, encoder_pixel_multiplier);

	अगर (पूर्णांकel_sdvo_get_value(पूर्णांकel_sdvo, SDVO_CMD_GET_COLORIMETRY,
				 &val, 1)) अणु
		अगर (val == SDVO_COLORIMETRY_RGB220)
			pipe_config->limited_color_range = true;
	पूर्ण

	अगर (पूर्णांकel_sdvo_get_value(पूर्णांकel_sdvo, SDVO_CMD_GET_AUDIO_STAT,
				 &val, 1)) अणु
		u8 mask = SDVO_AUDIO_ELD_VALID | SDVO_AUDIO_PRESENCE_DETECT;

		अगर ((val & mask) == mask)
			pipe_config->has_audio = true;
	पूर्ण

	अगर (पूर्णांकel_sdvo_get_value(पूर्णांकel_sdvo, SDVO_CMD_GET_ENCODE,
				 &val, 1)) अणु
		अगर (val == SDVO_ENCODE_HDMI)
			pipe_config->has_hdmi_sink = true;
	पूर्ण

	पूर्णांकel_sdvo_get_avi_infoframe(पूर्णांकel_sdvo, pipe_config);
पूर्ण

अटल व्योम पूर्णांकel_sdvo_disable_audio(काष्ठा पूर्णांकel_sdvo *पूर्णांकel_sdvo)
अणु
	पूर्णांकel_sdvo_set_audio_state(पूर्णांकel_sdvo, 0);
पूर्ण

अटल व्योम पूर्णांकel_sdvo_enable_audio(काष्ठा पूर्णांकel_sdvo *पूर्णांकel_sdvo,
				    स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
				    स्थिर काष्ठा drm_connector_state *conn_state)
अणु
	स्थिर काष्ठा drm_display_mode *adjusted_mode =
		&crtc_state->hw.adjusted_mode;
	काष्ठा drm_connector *connector = conn_state->connector;
	u8 *eld = connector->eld;

	eld[6] = drm_av_sync_delay(connector, adjusted_mode) / 2;

	पूर्णांकel_sdvo_set_audio_state(पूर्णांकel_sdvo, 0);

	पूर्णांकel_sdvo_ग_लिखो_infoframe(पूर्णांकel_sdvo, SDVO_HBUF_INDEX_ELD,
				   SDVO_HBUF_TX_DISABLED,
				   eld, drm_eld_size(eld));

	पूर्णांकel_sdvo_set_audio_state(पूर्णांकel_sdvo, SDVO_AUDIO_ELD_VALID |
				   SDVO_AUDIO_PRESENCE_DETECT);
पूर्ण

अटल व्योम पूर्णांकel_disable_sdvo(काष्ठा पूर्णांकel_atomic_state *state,
			       काष्ठा पूर्णांकel_encoder *encoder,
			       स्थिर काष्ठा पूर्णांकel_crtc_state *old_crtc_state,
			       स्थिर काष्ठा drm_connector_state *conn_state)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	काष्ठा पूर्णांकel_sdvo *पूर्णांकel_sdvo = to_sdvo(encoder);
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(old_crtc_state->uapi.crtc);
	u32 temp;

	अगर (old_crtc_state->has_audio)
		पूर्णांकel_sdvo_disable_audio(पूर्णांकel_sdvo);

	पूर्णांकel_sdvo_set_active_outमाला_दो(पूर्णांकel_sdvo, 0);
	अगर (0)
		पूर्णांकel_sdvo_set_encoder_घातer_state(पूर्णांकel_sdvo,
						   DRM_MODE_DPMS_OFF);

	temp = पूर्णांकel_de_पढ़ो(dev_priv, पूर्णांकel_sdvo->sdvo_reg);

	temp &= ~SDVO_ENABLE;
	पूर्णांकel_sdvo_ग_लिखो_sdvox(पूर्णांकel_sdvo, temp);

	/*
	 * HW workaround क्रम IBX, we need to move the port
	 * to transcoder A after disabling it to allow the
	 * matching DP port to be enabled on transcoder A.
	 */
	अगर (HAS_PCH_IBX(dev_priv) && crtc->pipe == PIPE_B) अणु
		/*
		 * We get CPU/PCH FIFO underruns on the other pipe when
		 * करोing the workaround. Sweep them under the rug.
		 */
		पूर्णांकel_set_cpu_fअगरo_underrun_reporting(dev_priv, PIPE_A, false);
		पूर्णांकel_set_pch_fअगरo_underrun_reporting(dev_priv, PIPE_A, false);

		temp &= ~SDVO_PIPE_SEL_MASK;
		temp |= SDVO_ENABLE | SDVO_PIPE_SEL(PIPE_A);
		पूर्णांकel_sdvo_ग_लिखो_sdvox(पूर्णांकel_sdvo, temp);

		temp &= ~SDVO_ENABLE;
		पूर्णांकel_sdvo_ग_लिखो_sdvox(पूर्णांकel_sdvo, temp);

		पूर्णांकel_रुको_क्रम_vblank_अगर_active(dev_priv, PIPE_A);
		पूर्णांकel_set_cpu_fअगरo_underrun_reporting(dev_priv, PIPE_A, true);
		पूर्णांकel_set_pch_fअगरo_underrun_reporting(dev_priv, PIPE_A, true);
	पूर्ण
पूर्ण

अटल व्योम pch_disable_sdvo(काष्ठा पूर्णांकel_atomic_state *state,
			     काष्ठा पूर्णांकel_encoder *encoder,
			     स्थिर काष्ठा पूर्णांकel_crtc_state *old_crtc_state,
			     स्थिर काष्ठा drm_connector_state *old_conn_state)
अणु
पूर्ण

अटल व्योम pch_post_disable_sdvo(काष्ठा पूर्णांकel_atomic_state *state,
				  काष्ठा पूर्णांकel_encoder *encoder,
				  स्थिर काष्ठा पूर्णांकel_crtc_state *old_crtc_state,
				  स्थिर काष्ठा drm_connector_state *old_conn_state)
अणु
	पूर्णांकel_disable_sdvo(state, encoder, old_crtc_state, old_conn_state);
पूर्ण

अटल व्योम पूर्णांकel_enable_sdvo(काष्ठा पूर्णांकel_atomic_state *state,
			      काष्ठा पूर्णांकel_encoder *encoder,
			      स्थिर काष्ठा पूर्णांकel_crtc_state *pipe_config,
			      स्थिर काष्ठा drm_connector_state *conn_state)
अणु
	काष्ठा drm_device *dev = encoder->base.dev;
	काष्ठा drm_i915_निजी *dev_priv = to_i915(dev);
	काष्ठा पूर्णांकel_sdvo *पूर्णांकel_sdvo = to_sdvo(encoder);
	काष्ठा पूर्णांकel_crtc *पूर्णांकel_crtc = to_पूर्णांकel_crtc(pipe_config->uapi.crtc);
	u32 temp;
	bool input1, input2;
	पूर्णांक i;
	bool success;

	temp = पूर्णांकel_de_पढ़ो(dev_priv, पूर्णांकel_sdvo->sdvo_reg);
	temp |= SDVO_ENABLE;
	पूर्णांकel_sdvo_ग_लिखो_sdvox(पूर्णांकel_sdvo, temp);

	क्रम (i = 0; i < 2; i++)
		पूर्णांकel_रुको_क्रम_vblank(dev_priv, पूर्णांकel_crtc->pipe);

	success = पूर्णांकel_sdvo_get_trained_inमाला_दो(पूर्णांकel_sdvo, &input1, &input2);
	/*
	 * Warn अगर the device reported failure to sync.
	 *
	 * A lot of SDVO devices fail to notअगरy of sync, but it's
	 * a given it the status is a success, we succeeded.
	 */
	अगर (success && !input1) अणु
		drm_dbg_kms(&dev_priv->drm,
			    "First %s output reported failure to "
			    "sync\n", SDVO_NAME(पूर्णांकel_sdvo));
	पूर्ण

	अगर (0)
		पूर्णांकel_sdvo_set_encoder_घातer_state(पूर्णांकel_sdvo,
						   DRM_MODE_DPMS_ON);
	पूर्णांकel_sdvo_set_active_outमाला_दो(पूर्णांकel_sdvo, पूर्णांकel_sdvo->attached_output);

	अगर (pipe_config->has_audio)
		पूर्णांकel_sdvo_enable_audio(पूर्णांकel_sdvo, pipe_config, conn_state);
पूर्ण

अटल क्रमागत drm_mode_status
पूर्णांकel_sdvo_mode_valid(काष्ठा drm_connector *connector,
		      काष्ठा drm_display_mode *mode)
अणु
	काष्ठा पूर्णांकel_sdvo *पूर्णांकel_sdvo = पूर्णांकel_attached_sdvo(to_पूर्णांकel_connector(connector));
	काष्ठा पूर्णांकel_sdvo_connector *पूर्णांकel_sdvo_connector =
		to_पूर्णांकel_sdvo_connector(connector);
	पूर्णांक max_करोtclk = to_i915(connector->dev)->max_करोtclk_freq;
	bool has_hdmi_sink = पूर्णांकel_has_hdmi_sink(पूर्णांकel_sdvo, connector->state);
	पूर्णांक घड़ी = mode->घड़ी;

	अगर (mode->flags & DRM_MODE_FLAG_DBLSCAN)
		वापस MODE_NO_DBLESCAN;


	अगर (घड़ी > max_करोtclk)
		वापस MODE_CLOCK_HIGH;

	अगर (mode->flags & DRM_MODE_FLAG_DBLCLK) अणु
		अगर (!has_hdmi_sink)
			वापस MODE_CLOCK_LOW;
		घड़ी *= 2;
	पूर्ण

	अगर (पूर्णांकel_sdvo->pixel_घड़ी_min > घड़ी)
		वापस MODE_CLOCK_LOW;

	अगर (पूर्णांकel_sdvo->pixel_घड़ी_max < घड़ी)
		वापस MODE_CLOCK_HIGH;

	अगर (IS_LVDS(पूर्णांकel_sdvo_connector)) अणु
		स्थिर काष्ठा drm_display_mode *fixed_mode =
			पूर्णांकel_sdvo_connector->base.panel.fixed_mode;

		अगर (mode->hdisplay > fixed_mode->hdisplay)
			वापस MODE_PANEL;

		अगर (mode->vdisplay > fixed_mode->vdisplay)
			वापस MODE_PANEL;
	पूर्ण

	वापस MODE_OK;
पूर्ण

अटल bool पूर्णांकel_sdvo_get_capabilities(काष्ठा पूर्णांकel_sdvo *पूर्णांकel_sdvo, काष्ठा पूर्णांकel_sdvo_caps *caps)
अणु
	BUILD_BUG_ON(माप(*caps) != 8);
	अगर (!पूर्णांकel_sdvo_get_value(पूर्णांकel_sdvo,
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

अटल u8 पूर्णांकel_sdvo_get_colorimetry_cap(काष्ठा पूर्णांकel_sdvo *पूर्णांकel_sdvo)
अणु
	u8 cap;

	अगर (!पूर्णांकel_sdvo_get_value(पूर्णांकel_sdvo, SDVO_CMD_GET_COLORIMETRY_CAP,
				  &cap, माप(cap)))
		वापस SDVO_COLORIMETRY_RGB256;

	वापस cap;
पूर्ण

अटल u16 पूर्णांकel_sdvo_get_hotplug_support(काष्ठा पूर्णांकel_sdvo *पूर्णांकel_sdvo)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(पूर्णांकel_sdvo->base.base.dev);
	u16 hotplug;

	अगर (!I915_HAS_HOTPLUG(dev_priv))
		वापस 0;

	/*
	 * HW Erratum: SDVO Hotplug is broken on all i945G chips, there's noise
	 * on the line.
	 */
	अगर (IS_I945G(dev_priv) || IS_I945GM(dev_priv))
		वापस 0;

	अगर (!पूर्णांकel_sdvo_get_value(पूर्णांकel_sdvo, SDVO_CMD_GET_HOT_PLUG_SUPPORT,
					&hotplug, माप(hotplug)))
		वापस 0;

	वापस hotplug;
पूर्ण

अटल व्योम पूर्णांकel_sdvo_enable_hotplug(काष्ठा पूर्णांकel_encoder *encoder)
अणु
	काष्ठा पूर्णांकel_sdvo *पूर्णांकel_sdvo = to_sdvo(encoder);

	पूर्णांकel_sdvo_ग_लिखो_cmd(पूर्णांकel_sdvo, SDVO_CMD_SET_ACTIVE_HOT_PLUG,
			     &पूर्णांकel_sdvo->hotplug_active, 2);
पूर्ण

अटल क्रमागत पूर्णांकel_hotplug_state
पूर्णांकel_sdvo_hotplug(काष्ठा पूर्णांकel_encoder *encoder,
		   काष्ठा पूर्णांकel_connector *connector)
अणु
	पूर्णांकel_sdvo_enable_hotplug(encoder);

	वापस पूर्णांकel_encoder_hotplug(encoder, connector);
पूर्ण

अटल bool
पूर्णांकel_sdvo_multअगरunc_encoder(काष्ठा पूर्णांकel_sdvo *पूर्णांकel_sdvo)
अणु
	/* Is there more than one type of output? */
	वापस hweight16(पूर्णांकel_sdvo->caps.output_flags) > 1;
पूर्ण

अटल काष्ठा edid *
पूर्णांकel_sdvo_get_edid(काष्ठा drm_connector *connector)
अणु
	काष्ठा पूर्णांकel_sdvo *sdvo = पूर्णांकel_attached_sdvo(to_पूर्णांकel_connector(connector));
	वापस drm_get_edid(connector, &sdvo->ddc);
पूर्ण

/* Mac mini hack -- use the same DDC as the analog connector */
अटल काष्ठा edid *
पूर्णांकel_sdvo_get_analog_edid(काष्ठा drm_connector *connector)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(connector->dev);

	वापस drm_get_edid(connector,
			    पूर्णांकel_gmbus_get_adapter(dev_priv,
						    dev_priv->vbt.crt_ddc_pin));
पूर्ण

अटल क्रमागत drm_connector_status
पूर्णांकel_sdvo_पंचांगds_sink_detect(काष्ठा drm_connector *connector)
अणु
	काष्ठा पूर्णांकel_sdvo *पूर्णांकel_sdvo = पूर्णांकel_attached_sdvo(to_पूर्णांकel_connector(connector));
	काष्ठा पूर्णांकel_sdvo_connector *पूर्णांकel_sdvo_connector =
		to_पूर्णांकel_sdvo_connector(connector);
	क्रमागत drm_connector_status status;
	काष्ठा edid *edid;

	edid = पूर्णांकel_sdvo_get_edid(connector);

	अगर (edid == शून्य && पूर्णांकel_sdvo_multअगरunc_encoder(पूर्णांकel_sdvo)) अणु
		u8 ddc, saved_ddc = पूर्णांकel_sdvo->ddc_bus;

		/*
		 * Don't use the 1 as the argument of DDC bus चयन to get
		 * the EDID. It is used क्रम SDVO SPD ROM.
		 */
		क्रम (ddc = पूर्णांकel_sdvo->ddc_bus >> 1; ddc > 1; ddc >>= 1) अणु
			पूर्णांकel_sdvo->ddc_bus = ddc;
			edid = पूर्णांकel_sdvo_get_edid(connector);
			अगर (edid)
				अवरोध;
		पूर्ण
		/*
		 * If we found the EDID on the other bus,
		 * assume that is the correct DDC bus.
		 */
		अगर (edid == शून्य)
			पूर्णांकel_sdvo->ddc_bus = saved_ddc;
	पूर्ण

	/*
	 * When there is no edid and no monitor is connected with VGA
	 * port, try to use the CRT ddc to पढ़ो the EDID क्रम DVI-connector.
	 */
	अगर (edid == शून्य)
		edid = पूर्णांकel_sdvo_get_analog_edid(connector);

	status = connector_status_unknown;
	अगर (edid != शून्य) अणु
		/* DDC bus is shared, match EDID to connector type */
		अगर (edid->input & DRM_EDID_INPUT_DIGITAL) अणु
			status = connector_status_connected;
			अगर (पूर्णांकel_sdvo_connector->is_hdmi) अणु
				पूर्णांकel_sdvo->has_hdmi_monitor = drm_detect_hdmi_monitor(edid);
				पूर्णांकel_sdvo->has_hdmi_audio = drm_detect_monitor_audio(edid);
			पूर्ण
		पूर्ण अन्यथा
			status = connector_status_disconnected;
		kमुक्त(edid);
	पूर्ण

	वापस status;
पूर्ण

अटल bool
पूर्णांकel_sdvo_connector_matches_edid(काष्ठा पूर्णांकel_sdvo_connector *sdvo,
				  काष्ठा edid *edid)
अणु
	bool monitor_is_digital = !!(edid->input & DRM_EDID_INPUT_DIGITAL);
	bool connector_is_digital = !!IS_DIGITAL(sdvo);

	DRM_DEBUG_KMS("connector_is_digital? %d, monitor_is_digital? %d\n",
		      connector_is_digital, monitor_is_digital);
	वापस connector_is_digital == monitor_is_digital;
पूर्ण

अटल क्रमागत drm_connector_status
पूर्णांकel_sdvo_detect(काष्ठा drm_connector *connector, bool क्रमce)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(connector->dev);
	काष्ठा पूर्णांकel_sdvo *पूर्णांकel_sdvo = पूर्णांकel_attached_sdvo(to_पूर्णांकel_connector(connector));
	काष्ठा पूर्णांकel_sdvo_connector *पूर्णांकel_sdvo_connector = to_पूर्णांकel_sdvo_connector(connector);
	क्रमागत drm_connector_status ret;
	u16 response;

	DRM_DEBUG_KMS("[CONNECTOR:%d:%s]\n",
		      connector->base.id, connector->name);

	अगर (!INTEL_DISPLAY_ENABLED(i915))
		वापस connector_status_disconnected;

	अगर (!पूर्णांकel_sdvo_get_value(पूर्णांकel_sdvo,
				  SDVO_CMD_GET_ATTACHED_DISPLAYS,
				  &response, 2))
		वापस connector_status_unknown;

	DRM_DEBUG_KMS("SDVO response %d %d [%x]\n",
		      response & 0xff, response >> 8,
		      पूर्णांकel_sdvo_connector->output_flag);

	अगर (response == 0)
		वापस connector_status_disconnected;

	पूर्णांकel_sdvo->attached_output = response;

	पूर्णांकel_sdvo->has_hdmi_monitor = false;
	पूर्णांकel_sdvo->has_hdmi_audio = false;

	अगर ((पूर्णांकel_sdvo_connector->output_flag & response) == 0)
		ret = connector_status_disconnected;
	अन्यथा अगर (IS_TMDS(पूर्णांकel_sdvo_connector))
		ret = पूर्णांकel_sdvo_पंचांगds_sink_detect(connector);
	अन्यथा अणु
		काष्ठा edid *edid;

		/* अगर we have an edid check it matches the connection */
		edid = पूर्णांकel_sdvo_get_edid(connector);
		अगर (edid == शून्य)
			edid = पूर्णांकel_sdvo_get_analog_edid(connector);
		अगर (edid != शून्य) अणु
			अगर (पूर्णांकel_sdvo_connector_matches_edid(पूर्णांकel_sdvo_connector,
							      edid))
				ret = connector_status_connected;
			अन्यथा
				ret = connector_status_disconnected;

			kमुक्त(edid);
		पूर्ण अन्यथा
			ret = connector_status_connected;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक पूर्णांकel_sdvo_get_ddc_modes(काष्ठा drm_connector *connector)
अणु
	पूर्णांक num_modes = 0;
	काष्ठा edid *edid;

	DRM_DEBUG_KMS("[CONNECTOR:%d:%s]\n",
		      connector->base.id, connector->name);

	/* set the bus चयन and get the modes */
	edid = पूर्णांकel_sdvo_get_edid(connector);

	/*
	 * Mac mini hack.  On this device, the DVI-I connector shares one DDC
	 * link between analog and digital outमाला_दो. So, अगर the regular SDVO
	 * DDC fails, check to see अगर the analog output is disconnected, in
	 * which हाल we'll look there क्रम the digital DDC data.
	 */
	अगर (!edid)
		edid = पूर्णांकel_sdvo_get_analog_edid(connector);

	अगर (!edid)
		वापस 0;

	अगर (पूर्णांकel_sdvo_connector_matches_edid(to_पूर्णांकel_sdvo_connector(connector),
					      edid))
		num_modes += पूर्णांकel_connector_update_modes(connector, edid);

	kमुक्त(edid);

	वापस num_modes;
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

अटल पूर्णांक पूर्णांकel_sdvo_get_tv_modes(काष्ठा drm_connector *connector)
अणु
	काष्ठा पूर्णांकel_sdvo *पूर्णांकel_sdvo = पूर्णांकel_attached_sdvo(to_पूर्णांकel_connector(connector));
	स्थिर काष्ठा drm_connector_state *conn_state = connector->state;
	काष्ठा पूर्णांकel_sdvo_sdtv_resolution_request tv_res;
	u32 reply = 0, क्रमmat_map = 0;
	पूर्णांक num_modes = 0;
	पूर्णांक i;

	DRM_DEBUG_KMS("[CONNECTOR:%d:%s]\n",
		      connector->base.id, connector->name);

	/*
	 * Read the list of supported input resolutions क्रम the selected TV
	 * क्रमmat.
	 */
	क्रमmat_map = 1 << conn_state->tv.mode;
	स_नकल(&tv_res, &क्रमmat_map,
	       min(माप(क्रमmat_map), माप(काष्ठा पूर्णांकel_sdvo_sdtv_resolution_request)));

	अगर (!पूर्णांकel_sdvo_set_target_output(पूर्णांकel_sdvo, पूर्णांकel_sdvo->attached_output))
		वापस 0;

	BUILD_BUG_ON(माप(tv_res) != 3);
	अगर (!पूर्णांकel_sdvo_ग_लिखो_cmd(पूर्णांकel_sdvo,
				  SDVO_CMD_GET_SDTV_RESOLUTION_SUPPORT,
				  &tv_res, माप(tv_res)))
		वापस 0;
	अगर (!पूर्णांकel_sdvo_पढ़ो_response(पूर्णांकel_sdvo, &reply, 3))
		वापस 0;

	क्रम (i = 0; i < ARRAY_SIZE(sdvo_tv_modes); i++) अणु
		अगर (reply & (1 << i)) अणु
			काष्ठा drm_display_mode *nmode;
			nmode = drm_mode_duplicate(connector->dev,
						   &sdvo_tv_modes[i]);
			अगर (nmode) अणु
				drm_mode_probed_add(connector, nmode);
				num_modes++;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस num_modes;
पूर्ण

अटल पूर्णांक पूर्णांकel_sdvo_get_lvds_modes(काष्ठा drm_connector *connector)
अणु
	काष्ठा पूर्णांकel_sdvo *पूर्णांकel_sdvo = पूर्णांकel_attached_sdvo(to_पूर्णांकel_connector(connector));
	काष्ठा drm_i915_निजी *dev_priv = to_i915(connector->dev);
	काष्ठा drm_display_mode *newmode;
	पूर्णांक num_modes = 0;

	drm_dbg_kms(&dev_priv->drm, "[CONNECTOR:%d:%s]\n",
		    connector->base.id, connector->name);

	/*
	 * Fetch modes from VBT. For SDVO prefer the VBT mode since some
	 * SDVO->LVDS transcoders can't cope with the EDID mode.
	 */
	अगर (dev_priv->vbt.sdvo_lvds_vbt_mode != शून्य) अणु
		newmode = drm_mode_duplicate(connector->dev,
					     dev_priv->vbt.sdvo_lvds_vbt_mode);
		अगर (newmode != शून्य) अणु
			/* Guarantee the mode is preferred */
			newmode->type = (DRM_MODE_TYPE_PREFERRED |
					 DRM_MODE_TYPE_DRIVER);
			drm_mode_probed_add(connector, newmode);
			num_modes++;
		पूर्ण
	पूर्ण

	/*
	 * Attempt to get the mode list from DDC.
	 * Assume that the preferred modes are
	 * arranged in priority order.
	 */
	num_modes += पूर्णांकel_ddc_get_modes(connector, &पूर्णांकel_sdvo->ddc);

	वापस num_modes;
पूर्ण

अटल पूर्णांक पूर्णांकel_sdvo_get_modes(काष्ठा drm_connector *connector)
अणु
	काष्ठा पूर्णांकel_sdvo_connector *पूर्णांकel_sdvo_connector = to_पूर्णांकel_sdvo_connector(connector);

	अगर (IS_TV(पूर्णांकel_sdvo_connector))
		वापस पूर्णांकel_sdvo_get_tv_modes(connector);
	अन्यथा अगर (IS_LVDS(पूर्णांकel_sdvo_connector))
		वापस पूर्णांकel_sdvo_get_lvds_modes(connector);
	अन्यथा
		वापस पूर्णांकel_sdvo_get_ddc_modes(connector);
पूर्ण

अटल पूर्णांक
पूर्णांकel_sdvo_connector_atomic_get_property(काष्ठा drm_connector *connector,
					 स्थिर काष्ठा drm_connector_state *state,
					 काष्ठा drm_property *property,
					 u64 *val)
अणु
	काष्ठा पूर्णांकel_sdvo_connector *पूर्णांकel_sdvo_connector = to_पूर्णांकel_sdvo_connector(connector);
	स्थिर काष्ठा पूर्णांकel_sdvo_connector_state *sdvo_state = to_पूर्णांकel_sdvo_connector_state((व्योम *)state);

	अगर (property == पूर्णांकel_sdvo_connector->tv_क्रमmat) अणु
		पूर्णांक i;

		क्रम (i = 0; i < पूर्णांकel_sdvo_connector->क्रमmat_supported_num; i++)
			अगर (state->tv.mode == पूर्णांकel_sdvo_connector->tv_क्रमmat_supported[i]) अणु
				*val = i;

				वापस 0;
			पूर्ण

		drm_WARN_ON(connector->dev, 1);
		*val = 0;
	पूर्ण अन्यथा अगर (property == पूर्णांकel_sdvo_connector->top ||
		   property == पूर्णांकel_sdvo_connector->bottom)
		*val = पूर्णांकel_sdvo_connector->max_vscan - sdvo_state->tv.overscan_v;
	अन्यथा अगर (property == पूर्णांकel_sdvo_connector->left ||
		 property == पूर्णांकel_sdvo_connector->right)
		*val = पूर्णांकel_sdvo_connector->max_hscan - sdvo_state->tv.overscan_h;
	अन्यथा अगर (property == पूर्णांकel_sdvo_connector->hpos)
		*val = sdvo_state->tv.hpos;
	अन्यथा अगर (property == पूर्णांकel_sdvo_connector->vpos)
		*val = sdvo_state->tv.vpos;
	अन्यथा अगर (property == पूर्णांकel_sdvo_connector->saturation)
		*val = state->tv.saturation;
	अन्यथा अगर (property == पूर्णांकel_sdvo_connector->contrast)
		*val = state->tv.contrast;
	अन्यथा अगर (property == पूर्णांकel_sdvo_connector->hue)
		*val = state->tv.hue;
	अन्यथा अगर (property == पूर्णांकel_sdvo_connector->brightness)
		*val = state->tv.brightness;
	अन्यथा अगर (property == पूर्णांकel_sdvo_connector->sharpness)
		*val = sdvo_state->tv.sharpness;
	अन्यथा अगर (property == पूर्णांकel_sdvo_connector->flicker_filter)
		*val = sdvo_state->tv.flicker_filter;
	अन्यथा अगर (property == पूर्णांकel_sdvo_connector->flicker_filter_2d)
		*val = sdvo_state->tv.flicker_filter_2d;
	अन्यथा अगर (property == पूर्णांकel_sdvo_connector->flicker_filter_adaptive)
		*val = sdvo_state->tv.flicker_filter_adaptive;
	अन्यथा अगर (property == पूर्णांकel_sdvo_connector->tv_chroma_filter)
		*val = sdvo_state->tv.chroma_filter;
	अन्यथा अगर (property == पूर्णांकel_sdvo_connector->tv_luma_filter)
		*val = sdvo_state->tv.luma_filter;
	अन्यथा अगर (property == पूर्णांकel_sdvo_connector->करोt_crawl)
		*val = sdvo_state->tv.करोt_crawl;
	अन्यथा
		वापस पूर्णांकel_digital_connector_atomic_get_property(connector, state, property, val);

	वापस 0;
पूर्ण

अटल पूर्णांक
पूर्णांकel_sdvo_connector_atomic_set_property(काष्ठा drm_connector *connector,
					 काष्ठा drm_connector_state *state,
					 काष्ठा drm_property *property,
					 u64 val)
अणु
	काष्ठा पूर्णांकel_sdvo_connector *पूर्णांकel_sdvo_connector = to_पूर्णांकel_sdvo_connector(connector);
	काष्ठा पूर्णांकel_sdvo_connector_state *sdvo_state = to_पूर्णांकel_sdvo_connector_state(state);

	अगर (property == पूर्णांकel_sdvo_connector->tv_क्रमmat) अणु
		state->tv.mode = पूर्णांकel_sdvo_connector->tv_क्रमmat_supported[val];

		अगर (state->crtc) अणु
			काष्ठा drm_crtc_state *crtc_state =
				drm_atomic_get_new_crtc_state(state->state, state->crtc);

			crtc_state->connectors_changed = true;
		पूर्ण
	पूर्ण अन्यथा अगर (property == पूर्णांकel_sdvo_connector->top ||
		   property == पूर्णांकel_sdvo_connector->bottom)
		/* Cannot set these independent from each other */
		sdvo_state->tv.overscan_v = पूर्णांकel_sdvo_connector->max_vscan - val;
	अन्यथा अगर (property == पूर्णांकel_sdvo_connector->left ||
		 property == पूर्णांकel_sdvo_connector->right)
		/* Cannot set these independent from each other */
		sdvo_state->tv.overscan_h = पूर्णांकel_sdvo_connector->max_hscan - val;
	अन्यथा अगर (property == पूर्णांकel_sdvo_connector->hpos)
		sdvo_state->tv.hpos = val;
	अन्यथा अगर (property == पूर्णांकel_sdvo_connector->vpos)
		sdvo_state->tv.vpos = val;
	अन्यथा अगर (property == पूर्णांकel_sdvo_connector->saturation)
		state->tv.saturation = val;
	अन्यथा अगर (property == पूर्णांकel_sdvo_connector->contrast)
		state->tv.contrast = val;
	अन्यथा अगर (property == पूर्णांकel_sdvo_connector->hue)
		state->tv.hue = val;
	अन्यथा अगर (property == पूर्णांकel_sdvo_connector->brightness)
		state->tv.brightness = val;
	अन्यथा अगर (property == पूर्णांकel_sdvo_connector->sharpness)
		sdvo_state->tv.sharpness = val;
	अन्यथा अगर (property == पूर्णांकel_sdvo_connector->flicker_filter)
		sdvo_state->tv.flicker_filter = val;
	अन्यथा अगर (property == पूर्णांकel_sdvo_connector->flicker_filter_2d)
		sdvo_state->tv.flicker_filter_2d = val;
	अन्यथा अगर (property == पूर्णांकel_sdvo_connector->flicker_filter_adaptive)
		sdvo_state->tv.flicker_filter_adaptive = val;
	अन्यथा अगर (property == पूर्णांकel_sdvo_connector->tv_chroma_filter)
		sdvo_state->tv.chroma_filter = val;
	अन्यथा अगर (property == पूर्णांकel_sdvo_connector->tv_luma_filter)
		sdvo_state->tv.luma_filter = val;
	अन्यथा अगर (property == पूर्णांकel_sdvo_connector->करोt_crawl)
		sdvo_state->tv.करोt_crawl = val;
	अन्यथा
		वापस पूर्णांकel_digital_connector_atomic_set_property(connector, state, property, val);

	वापस 0;
पूर्ण

अटल पूर्णांक
पूर्णांकel_sdvo_connector_रेजिस्टर(काष्ठा drm_connector *connector)
अणु
	काष्ठा पूर्णांकel_sdvo *sdvo = पूर्णांकel_attached_sdvo(to_पूर्णांकel_connector(connector));
	पूर्णांक ret;

	ret = पूर्णांकel_connector_रेजिस्टर(connector);
	अगर (ret)
		वापस ret;

	वापस sysfs_create_link(&connector->kdev->kobj,
				 &sdvo->ddc.dev.kobj,
				 sdvo->ddc.dev.kobj.name);
पूर्ण

अटल व्योम
पूर्णांकel_sdvo_connector_unरेजिस्टर(काष्ठा drm_connector *connector)
अणु
	काष्ठा पूर्णांकel_sdvo *sdvo = पूर्णांकel_attached_sdvo(to_पूर्णांकel_connector(connector));

	sysfs_हटाओ_link(&connector->kdev->kobj,
			  sdvo->ddc.dev.kobj.name);
	पूर्णांकel_connector_unरेजिस्टर(connector);
पूर्ण

अटल काष्ठा drm_connector_state *
पूर्णांकel_sdvo_connector_duplicate_state(काष्ठा drm_connector *connector)
अणु
	काष्ठा पूर्णांकel_sdvo_connector_state *state;

	state = kmemdup(connector->state, माप(*state), GFP_KERNEL);
	अगर (!state)
		वापस शून्य;

	__drm_atomic_helper_connector_duplicate_state(connector, &state->base.base);
	वापस &state->base.base;
पूर्ण

अटल स्थिर काष्ठा drm_connector_funcs पूर्णांकel_sdvo_connector_funcs = अणु
	.detect = पूर्णांकel_sdvo_detect,
	.fill_modes = drm_helper_probe_single_connector_modes,
	.atomic_get_property = पूर्णांकel_sdvo_connector_atomic_get_property,
	.atomic_set_property = पूर्णांकel_sdvo_connector_atomic_set_property,
	.late_रेजिस्टर = पूर्णांकel_sdvo_connector_रेजिस्टर,
	.early_unरेजिस्टर = पूर्णांकel_sdvo_connector_unरेजिस्टर,
	.destroy = पूर्णांकel_connector_destroy,
	.atomic_destroy_state = drm_atomic_helper_connector_destroy_state,
	.atomic_duplicate_state = पूर्णांकel_sdvo_connector_duplicate_state,
पूर्ण;

अटल पूर्णांक पूर्णांकel_sdvo_atomic_check(काष्ठा drm_connector *conn,
				   काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_connector_state *new_conn_state =
		drm_atomic_get_new_connector_state(state, conn);
	काष्ठा drm_connector_state *old_conn_state =
		drm_atomic_get_old_connector_state(state, conn);
	काष्ठा पूर्णांकel_sdvo_connector_state *old_state =
		to_पूर्णांकel_sdvo_connector_state(old_conn_state);
	काष्ठा पूर्णांकel_sdvo_connector_state *new_state =
		to_पूर्णांकel_sdvo_connector_state(new_conn_state);

	अगर (new_conn_state->crtc &&
	    (स_भेद(&old_state->tv, &new_state->tv, माप(old_state->tv)) ||
	     स_भेद(&old_conn_state->tv, &new_conn_state->tv, माप(old_conn_state->tv)))) अणु
		काष्ठा drm_crtc_state *crtc_state =
			drm_atomic_get_new_crtc_state(state,
						      new_conn_state->crtc);

		crtc_state->connectors_changed = true;
	पूर्ण

	वापस पूर्णांकel_digital_connector_atomic_check(conn, state);
पूर्ण

अटल स्थिर काष्ठा drm_connector_helper_funcs पूर्णांकel_sdvo_connector_helper_funcs = अणु
	.get_modes = पूर्णांकel_sdvo_get_modes,
	.mode_valid = पूर्णांकel_sdvo_mode_valid,
	.atomic_check = पूर्णांकel_sdvo_atomic_check,
पूर्ण;

अटल व्योम पूर्णांकel_sdvo_enc_destroy(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा पूर्णांकel_sdvo *पूर्णांकel_sdvo = to_sdvo(to_पूर्णांकel_encoder(encoder));

	i2c_del_adapter(&पूर्णांकel_sdvo->ddc);
	पूर्णांकel_encoder_destroy(encoder);
पूर्ण

अटल स्थिर काष्ठा drm_encoder_funcs पूर्णांकel_sdvo_enc_funcs = अणु
	.destroy = पूर्णांकel_sdvo_enc_destroy,
पूर्ण;

अटल व्योम
पूर्णांकel_sdvo_guess_ddc_bus(काष्ठा पूर्णांकel_sdvo *sdvo)
अणु
	u16 mask = 0;
	अचिन्हित पूर्णांक num_bits;

	/*
	 * Make a mask of outमाला_दो less than or equal to our own priority in the
	 * list.
	 */
	चयन (sdvo->controlled_output) अणु
	हाल SDVO_OUTPUT_LVDS1:
		mask |= SDVO_OUTPUT_LVDS1;
		fallthrough;
	हाल SDVO_OUTPUT_LVDS0:
		mask |= SDVO_OUTPUT_LVDS0;
		fallthrough;
	हाल SDVO_OUTPUT_TMDS1:
		mask |= SDVO_OUTPUT_TMDS1;
		fallthrough;
	हाल SDVO_OUTPUT_TMDS0:
		mask |= SDVO_OUTPUT_TMDS0;
		fallthrough;
	हाल SDVO_OUTPUT_RGB1:
		mask |= SDVO_OUTPUT_RGB1;
		fallthrough;
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
पूर्ण

/*
 * Choose the appropriate DDC bus क्रम control bus चयन command क्रम this
 * SDVO output based on the controlled output.
 *
 * DDC bus number assignment is in a priority order of RGB outमाला_दो, then TMDS
 * outमाला_दो, then LVDS outमाला_दो.
 */
अटल व्योम
पूर्णांकel_sdvo_select_ddc_bus(काष्ठा drm_i915_निजी *dev_priv,
			  काष्ठा पूर्णांकel_sdvo *sdvo)
अणु
	काष्ठा sdvo_device_mapping *mapping;

	अगर (sdvo->port == PORT_B)
		mapping = &dev_priv->vbt.sdvo_mappings[0];
	अन्यथा
		mapping = &dev_priv->vbt.sdvo_mappings[1];

	अगर (mapping->initialized)
		sdvo->ddc_bus = 1 << ((mapping->ddc_pin & 0xf0) >> 4);
	अन्यथा
		पूर्णांकel_sdvo_guess_ddc_bus(sdvo);
पूर्ण

अटल व्योम
पूर्णांकel_sdvo_select_i2c_bus(काष्ठा drm_i915_निजी *dev_priv,
			  काष्ठा पूर्णांकel_sdvo *sdvo)
अणु
	काष्ठा sdvo_device_mapping *mapping;
	u8 pin;

	अगर (sdvo->port == PORT_B)
		mapping = &dev_priv->vbt.sdvo_mappings[0];
	अन्यथा
		mapping = &dev_priv->vbt.sdvo_mappings[1];

	अगर (mapping->initialized &&
	    पूर्णांकel_gmbus_is_valid_pin(dev_priv, mapping->i2c_pin))
		pin = mapping->i2c_pin;
	अन्यथा
		pin = GMBUS_PIN_DPB;

	sdvo->i2c = पूर्णांकel_gmbus_get_adapter(dev_priv, pin);

	/*
	 * With gmbus we should be able to drive sdvo i2c at 2MHz, but somehow
	 * our code totally fails once we start using gmbus. Hence fall back to
	 * bit banging क्रम now.
	 */
	पूर्णांकel_gmbus_क्रमce_bit(sdvo->i2c, true);
पूर्ण

/* unकरो any changes पूर्णांकel_sdvo_select_i2c_bus() did to sdvo->i2c */
अटल व्योम
पूर्णांकel_sdvo_unselect_i2c_bus(काष्ठा पूर्णांकel_sdvo *sdvo)
अणु
	पूर्णांकel_gmbus_क्रमce_bit(sdvo->i2c, false);
पूर्ण

अटल bool
पूर्णांकel_sdvo_is_hdmi_connector(काष्ठा पूर्णांकel_sdvo *पूर्णांकel_sdvo, पूर्णांक device)
अणु
	वापस पूर्णांकel_sdvo_check_supp_encode(पूर्णांकel_sdvo);
पूर्ण

अटल u8
पूर्णांकel_sdvo_get_slave_addr(काष्ठा drm_i915_निजी *dev_priv,
			  काष्ठा पूर्णांकel_sdvo *sdvo)
अणु
	काष्ठा sdvo_device_mapping *my_mapping, *other_mapping;

	अगर (sdvo->port == PORT_B) अणु
		my_mapping = &dev_priv->vbt.sdvo_mappings[0];
		other_mapping = &dev_priv->vbt.sdvo_mappings[1];
	पूर्ण अन्यथा अणु
		my_mapping = &dev_priv->vbt.sdvo_mappings[1];
		other_mapping = &dev_priv->vbt.sdvo_mappings[0];
	पूर्ण

	/* If the BIOS described our SDVO device, take advantage of it. */
	अगर (my_mapping->slave_addr)
		वापस my_mapping->slave_addr;

	/*
	 * If the BIOS only described a dअगरferent SDVO device, use the
	 * address that it isn't using.
	 */
	अगर (other_mapping->slave_addr) अणु
		अगर (other_mapping->slave_addr == 0x70)
			वापस 0x72;
		अन्यथा
			वापस 0x70;
	पूर्ण

	/*
	 * No SDVO device info is found क्रम another DVO port,
	 * so use mapping assumption we had beक्रमe BIOS parsing.
	 */
	अगर (sdvo->port == PORT_B)
		वापस 0x70;
	अन्यथा
		वापस 0x72;
पूर्ण

अटल पूर्णांक
पूर्णांकel_sdvo_connector_init(काष्ठा पूर्णांकel_sdvo_connector *connector,
			  काष्ठा पूर्णांकel_sdvo *encoder)
अणु
	काष्ठा drm_connector *drm_connector;
	पूर्णांक ret;

	drm_connector = &connector->base.base;
	ret = drm_connector_init(encoder->base.base.dev,
			   drm_connector,
			   &पूर्णांकel_sdvo_connector_funcs,
			   connector->base.base.connector_type);
	अगर (ret < 0)
		वापस ret;

	drm_connector_helper_add(drm_connector,
				 &पूर्णांकel_sdvo_connector_helper_funcs);

	connector->base.base.पूर्णांकerlace_allowed = 1;
	connector->base.base.द्विगुनscan_allowed = 0;
	connector->base.base.display_info.subpixel_order = SubPixelHorizontalRGB;
	connector->base.get_hw_state = पूर्णांकel_sdvo_connector_get_hw_state;

	पूर्णांकel_connector_attach_encoder(&connector->base, &encoder->base);

	वापस 0;
पूर्ण

अटल व्योम
पूर्णांकel_sdvo_add_hdmi_properties(काष्ठा पूर्णांकel_sdvo *पूर्णांकel_sdvo,
			       काष्ठा पूर्णांकel_sdvo_connector *connector)
अणु
	पूर्णांकel_attach_क्रमce_audio_property(&connector->base.base);
	अगर (पूर्णांकel_sdvo->colorimetry_cap & SDVO_COLORIMETRY_RGB220)
		पूर्णांकel_attach_broadcast_rgb_property(&connector->base.base);
	पूर्णांकel_attach_aspect_ratio_property(&connector->base.base);
पूर्ण

अटल काष्ठा पूर्णांकel_sdvo_connector *पूर्णांकel_sdvo_connector_alloc(व्योम)
अणु
	काष्ठा पूर्णांकel_sdvo_connector *sdvo_connector;
	काष्ठा पूर्णांकel_sdvo_connector_state *conn_state;

	sdvo_connector = kzalloc(माप(*sdvo_connector), GFP_KERNEL);
	अगर (!sdvo_connector)
		वापस शून्य;

	conn_state = kzalloc(माप(*conn_state), GFP_KERNEL);
	अगर (!conn_state) अणु
		kमुक्त(sdvo_connector);
		वापस शून्य;
	पूर्ण

	__drm_atomic_helper_connector_reset(&sdvo_connector->base.base,
					    &conn_state->base.base);

	वापस sdvo_connector;
पूर्ण

अटल bool
पूर्णांकel_sdvo_dvi_init(काष्ठा पूर्णांकel_sdvo *पूर्णांकel_sdvo, पूर्णांक device)
अणु
	काष्ठा drm_encoder *encoder = &पूर्णांकel_sdvo->base.base;
	काष्ठा drm_connector *connector;
	काष्ठा पूर्णांकel_encoder *पूर्णांकel_encoder = to_पूर्णांकel_encoder(encoder);
	काष्ठा पूर्णांकel_connector *पूर्णांकel_connector;
	काष्ठा पूर्णांकel_sdvo_connector *पूर्णांकel_sdvo_connector;

	DRM_DEBUG_KMS("initialising DVI device %d\n", device);

	पूर्णांकel_sdvo_connector = पूर्णांकel_sdvo_connector_alloc();
	अगर (!पूर्णांकel_sdvo_connector)
		वापस false;

	अगर (device == 0) अणु
		पूर्णांकel_sdvo->controlled_output |= SDVO_OUTPUT_TMDS0;
		पूर्णांकel_sdvo_connector->output_flag = SDVO_OUTPUT_TMDS0;
	पूर्ण अन्यथा अगर (device == 1) अणु
		पूर्णांकel_sdvo->controlled_output |= SDVO_OUTPUT_TMDS1;
		पूर्णांकel_sdvo_connector->output_flag = SDVO_OUTPUT_TMDS1;
	पूर्ण

	पूर्णांकel_connector = &पूर्णांकel_sdvo_connector->base;
	connector = &पूर्णांकel_connector->base;
	अगर (पूर्णांकel_sdvo_get_hotplug_support(पूर्णांकel_sdvo) &
		पूर्णांकel_sdvo_connector->output_flag) अणु
		पूर्णांकel_sdvo->hotplug_active |= पूर्णांकel_sdvo_connector->output_flag;
		/*
		 * Some SDVO devices have one-shot hotplug पूर्णांकerrupts.
		 * Ensure that they get re-enabled when an पूर्णांकerrupt happens.
		 */
		पूर्णांकel_connector->polled = DRM_CONNECTOR_POLL_HPD;
		पूर्णांकel_encoder->hotplug = पूर्णांकel_sdvo_hotplug;
		पूर्णांकel_sdvo_enable_hotplug(पूर्णांकel_encoder);
	पूर्ण अन्यथा अणु
		पूर्णांकel_connector->polled = DRM_CONNECTOR_POLL_CONNECT | DRM_CONNECTOR_POLL_DISCONNECT;
	पूर्ण
	encoder->encoder_type = DRM_MODE_ENCODER_TMDS;
	connector->connector_type = DRM_MODE_CONNECTOR_DVID;

	अगर (पूर्णांकel_sdvo_is_hdmi_connector(पूर्णांकel_sdvo, device)) अणु
		connector->connector_type = DRM_MODE_CONNECTOR_HDMIA;
		पूर्णांकel_sdvo_connector->is_hdmi = true;
	पूर्ण

	अगर (पूर्णांकel_sdvo_connector_init(पूर्णांकel_sdvo_connector, पूर्णांकel_sdvo) < 0) अणु
		kमुक्त(पूर्णांकel_sdvo_connector);
		वापस false;
	पूर्ण

	अगर (पूर्णांकel_sdvo_connector->is_hdmi)
		पूर्णांकel_sdvo_add_hdmi_properties(पूर्णांकel_sdvo, पूर्णांकel_sdvo_connector);

	वापस true;
पूर्ण

अटल bool
पूर्णांकel_sdvo_tv_init(काष्ठा पूर्णांकel_sdvo *पूर्णांकel_sdvo, पूर्णांक type)
अणु
	काष्ठा drm_encoder *encoder = &पूर्णांकel_sdvo->base.base;
	काष्ठा drm_connector *connector;
	काष्ठा पूर्णांकel_connector *पूर्णांकel_connector;
	काष्ठा पूर्णांकel_sdvo_connector *पूर्णांकel_sdvo_connector;

	DRM_DEBUG_KMS("initialising TV type %d\n", type);

	पूर्णांकel_sdvo_connector = पूर्णांकel_sdvo_connector_alloc();
	अगर (!पूर्णांकel_sdvo_connector)
		वापस false;

	पूर्णांकel_connector = &पूर्णांकel_sdvo_connector->base;
	connector = &पूर्णांकel_connector->base;
	encoder->encoder_type = DRM_MODE_ENCODER_TVDAC;
	connector->connector_type = DRM_MODE_CONNECTOR_SVIDEO;

	पूर्णांकel_sdvo->controlled_output |= type;
	पूर्णांकel_sdvo_connector->output_flag = type;

	अगर (पूर्णांकel_sdvo_connector_init(पूर्णांकel_sdvo_connector, पूर्णांकel_sdvo) < 0) अणु
		kमुक्त(पूर्णांकel_sdvo_connector);
		वापस false;
	पूर्ण

	अगर (!पूर्णांकel_sdvo_tv_create_property(पूर्णांकel_sdvo, पूर्णांकel_sdvo_connector, type))
		जाओ err;

	अगर (!पूर्णांकel_sdvo_create_enhance_property(पूर्णांकel_sdvo, पूर्णांकel_sdvo_connector))
		जाओ err;

	वापस true;

err:
	पूर्णांकel_connector_destroy(connector);
	वापस false;
पूर्ण

अटल bool
पूर्णांकel_sdvo_analog_init(काष्ठा पूर्णांकel_sdvo *पूर्णांकel_sdvo, पूर्णांक device)
अणु
	काष्ठा drm_encoder *encoder = &पूर्णांकel_sdvo->base.base;
	काष्ठा drm_connector *connector;
	काष्ठा पूर्णांकel_connector *पूर्णांकel_connector;
	काष्ठा पूर्णांकel_sdvo_connector *पूर्णांकel_sdvo_connector;

	DRM_DEBUG_KMS("initialising analog device %d\n", device);

	पूर्णांकel_sdvo_connector = पूर्णांकel_sdvo_connector_alloc();
	अगर (!पूर्णांकel_sdvo_connector)
		वापस false;

	पूर्णांकel_connector = &पूर्णांकel_sdvo_connector->base;
	connector = &पूर्णांकel_connector->base;
	पूर्णांकel_connector->polled = DRM_CONNECTOR_POLL_CONNECT;
	encoder->encoder_type = DRM_MODE_ENCODER_DAC;
	connector->connector_type = DRM_MODE_CONNECTOR_VGA;

	अगर (device == 0) अणु
		पूर्णांकel_sdvo->controlled_output |= SDVO_OUTPUT_RGB0;
		पूर्णांकel_sdvo_connector->output_flag = SDVO_OUTPUT_RGB0;
	पूर्ण अन्यथा अगर (device == 1) अणु
		पूर्णांकel_sdvo->controlled_output |= SDVO_OUTPUT_RGB1;
		पूर्णांकel_sdvo_connector->output_flag = SDVO_OUTPUT_RGB1;
	पूर्ण

	अगर (पूर्णांकel_sdvo_connector_init(पूर्णांकel_sdvo_connector, पूर्णांकel_sdvo) < 0) अणु
		kमुक्त(पूर्णांकel_sdvo_connector);
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल bool
पूर्णांकel_sdvo_lvds_init(काष्ठा पूर्णांकel_sdvo *पूर्णांकel_sdvo, पूर्णांक device)
अणु
	काष्ठा drm_encoder *encoder = &पूर्णांकel_sdvo->base.base;
	काष्ठा drm_connector *connector;
	काष्ठा पूर्णांकel_connector *पूर्णांकel_connector;
	काष्ठा पूर्णांकel_sdvo_connector *पूर्णांकel_sdvo_connector;
	काष्ठा drm_display_mode *mode;

	DRM_DEBUG_KMS("initialising LVDS device %d\n", device);

	पूर्णांकel_sdvo_connector = पूर्णांकel_sdvo_connector_alloc();
	अगर (!पूर्णांकel_sdvo_connector)
		वापस false;

	पूर्णांकel_connector = &पूर्णांकel_sdvo_connector->base;
	connector = &पूर्णांकel_connector->base;
	encoder->encoder_type = DRM_MODE_ENCODER_LVDS;
	connector->connector_type = DRM_MODE_CONNECTOR_LVDS;

	अगर (device == 0) अणु
		पूर्णांकel_sdvo->controlled_output |= SDVO_OUTPUT_LVDS0;
		पूर्णांकel_sdvo_connector->output_flag = SDVO_OUTPUT_LVDS0;
	पूर्ण अन्यथा अगर (device == 1) अणु
		पूर्णांकel_sdvo->controlled_output |= SDVO_OUTPUT_LVDS1;
		पूर्णांकel_sdvo_connector->output_flag = SDVO_OUTPUT_LVDS1;
	पूर्ण

	अगर (पूर्णांकel_sdvo_connector_init(पूर्णांकel_sdvo_connector, पूर्णांकel_sdvo) < 0) अणु
		kमुक्त(पूर्णांकel_sdvo_connector);
		वापस false;
	पूर्ण

	अगर (!पूर्णांकel_sdvo_create_enhance_property(पूर्णांकel_sdvo, पूर्णांकel_sdvo_connector))
		जाओ err;

	पूर्णांकel_sdvo_get_lvds_modes(connector);

	list_क्रम_each_entry(mode, &connector->probed_modes, head) अणु
		अगर (mode->type & DRM_MODE_TYPE_PREFERRED) अणु
			काष्ठा drm_display_mode *fixed_mode =
				drm_mode_duplicate(connector->dev, mode);

			पूर्णांकel_panel_init(&पूर्णांकel_connector->panel,
					 fixed_mode, शून्य);
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!पूर्णांकel_connector->panel.fixed_mode)
		जाओ err;

	वापस true;

err:
	पूर्णांकel_connector_destroy(connector);
	वापस false;
पूर्ण

अटल bool
पूर्णांकel_sdvo_output_setup(काष्ठा पूर्णांकel_sdvo *पूर्णांकel_sdvo, u16 flags)
अणु
	/* SDVO requires XXX1 function may not exist unless it has XXX0 function.*/

	अगर (flags & SDVO_OUTPUT_TMDS0)
		अगर (!पूर्णांकel_sdvo_dvi_init(पूर्णांकel_sdvo, 0))
			वापस false;

	अगर ((flags & SDVO_TMDS_MASK) == SDVO_TMDS_MASK)
		अगर (!पूर्णांकel_sdvo_dvi_init(पूर्णांकel_sdvo, 1))
			वापस false;

	/* TV has no XXX1 function block */
	अगर (flags & SDVO_OUTPUT_SVID0)
		अगर (!पूर्णांकel_sdvo_tv_init(पूर्णांकel_sdvo, SDVO_OUTPUT_SVID0))
			वापस false;

	अगर (flags & SDVO_OUTPUT_CVBS0)
		अगर (!पूर्णांकel_sdvo_tv_init(पूर्णांकel_sdvo, SDVO_OUTPUT_CVBS0))
			वापस false;

	अगर (flags & SDVO_OUTPUT_YPRPB0)
		अगर (!पूर्णांकel_sdvo_tv_init(पूर्णांकel_sdvo, SDVO_OUTPUT_YPRPB0))
			वापस false;

	अगर (flags & SDVO_OUTPUT_RGB0)
		अगर (!पूर्णांकel_sdvo_analog_init(पूर्णांकel_sdvo, 0))
			वापस false;

	अगर ((flags & SDVO_RGB_MASK) == SDVO_RGB_MASK)
		अगर (!पूर्णांकel_sdvo_analog_init(पूर्णांकel_sdvo, 1))
			वापस false;

	अगर (flags & SDVO_OUTPUT_LVDS0)
		अगर (!पूर्णांकel_sdvo_lvds_init(पूर्णांकel_sdvo, 0))
			वापस false;

	अगर ((flags & SDVO_LVDS_MASK) == SDVO_LVDS_MASK)
		अगर (!पूर्णांकel_sdvo_lvds_init(पूर्णांकel_sdvo, 1))
			वापस false;

	अगर ((flags & SDVO_OUTPUT_MASK) == 0) अणु
		अचिन्हित अक्षर bytes[2];

		पूर्णांकel_sdvo->controlled_output = 0;
		स_नकल(bytes, &पूर्णांकel_sdvo->caps.output_flags, 2);
		DRM_DEBUG_KMS("%s: Unknown SDVO output type (0x%02x%02x)\n",
			      SDVO_NAME(पूर्णांकel_sdvo),
			      bytes[0], bytes[1]);
		वापस false;
	पूर्ण
	पूर्णांकel_sdvo->base.pipe_mask = ~0;

	वापस true;
पूर्ण

अटल व्योम पूर्णांकel_sdvo_output_cleanup(काष्ठा पूर्णांकel_sdvo *पूर्णांकel_sdvo)
अणु
	काष्ठा drm_device *dev = पूर्णांकel_sdvo->base.base.dev;
	काष्ठा drm_connector *connector, *पंचांगp;

	list_क्रम_each_entry_safe(connector, पंचांगp,
				 &dev->mode_config.connector_list, head) अणु
		अगर (पूर्णांकel_attached_encoder(to_पूर्णांकel_connector(connector)) == &पूर्णांकel_sdvo->base) अणु
			drm_connector_unरेजिस्टर(connector);
			पूर्णांकel_connector_destroy(connector);
		पूर्ण
	पूर्ण
पूर्ण

अटल bool पूर्णांकel_sdvo_tv_create_property(काष्ठा पूर्णांकel_sdvo *पूर्णांकel_sdvo,
					  काष्ठा पूर्णांकel_sdvo_connector *पूर्णांकel_sdvo_connector,
					  पूर्णांक type)
अणु
	काष्ठा drm_device *dev = पूर्णांकel_sdvo->base.base.dev;
	काष्ठा पूर्णांकel_sdvo_tv_क्रमmat क्रमmat;
	u32 क्रमmat_map, i;

	अगर (!पूर्णांकel_sdvo_set_target_output(पूर्णांकel_sdvo, type))
		वापस false;

	BUILD_BUG_ON(माप(क्रमmat) != 6);
	अगर (!पूर्णांकel_sdvo_get_value(पूर्णांकel_sdvo,
				  SDVO_CMD_GET_SUPPORTED_TV_FORMATS,
				  &क्रमmat, माप(क्रमmat)))
		वापस false;

	स_नकल(&क्रमmat_map, &क्रमmat, min(माप(क्रमmat_map), माप(क्रमmat)));

	अगर (क्रमmat_map == 0)
		वापस false;

	पूर्णांकel_sdvo_connector->क्रमmat_supported_num = 0;
	क्रम (i = 0 ; i < TV_FORMAT_NUM; i++)
		अगर (क्रमmat_map & (1 << i))
			पूर्णांकel_sdvo_connector->tv_क्रमmat_supported[पूर्णांकel_sdvo_connector->क्रमmat_supported_num++] = i;


	पूर्णांकel_sdvo_connector->tv_क्रमmat =
			drm_property_create(dev, DRM_MODE_PROP_ENUM,
					    "mode", पूर्णांकel_sdvo_connector->क्रमmat_supported_num);
	अगर (!पूर्णांकel_sdvo_connector->tv_क्रमmat)
		वापस false;

	क्रम (i = 0; i < पूर्णांकel_sdvo_connector->क्रमmat_supported_num; i++)
		drm_property_add_क्रमागत(पूर्णांकel_sdvo_connector->tv_क्रमmat, i,
				      tv_क्रमmat_names[पूर्णांकel_sdvo_connector->tv_क्रमmat_supported[i]]);

	पूर्णांकel_sdvo_connector->base.base.state->tv.mode = पूर्णांकel_sdvo_connector->tv_क्रमmat_supported[0];
	drm_object_attach_property(&पूर्णांकel_sdvo_connector->base.base.base,
				   पूर्णांकel_sdvo_connector->tv_क्रमmat, 0);
	वापस true;

पूर्ण

#घोषणा _ENHANCEMENT(state_assignment, name, NAME) करो अणु \
	अगर (enhancements.name) अणु \
		अगर (!पूर्णांकel_sdvo_get_value(पूर्णांकel_sdvo, SDVO_CMD_GET_MAX_##NAME, &data_value, 4) || \
		    !पूर्णांकel_sdvo_get_value(पूर्णांकel_sdvo, SDVO_CMD_GET_##NAME, &response, 2)) \
			वापस false; \
		पूर्णांकel_sdvo_connector->name = \
			drm_property_create_range(dev, 0, #name, 0, data_value[0]); \
		अगर (!पूर्णांकel_sdvo_connector->name) वापस false; \
		state_assignment = response; \
		drm_object_attach_property(&connector->base, \
					   पूर्णांकel_sdvo_connector->name, 0); \
		DRM_DEBUG_KMS(#name ": max %d, default %d, current %d\n", \
			      data_value[0], data_value[1], response); \
	पूर्ण \
पूर्ण जबतक (0)

#घोषणा ENHANCEMENT(state, name, NAME) _ENHANCEMENT((state)->name, name, NAME)

अटल bool
पूर्णांकel_sdvo_create_enhance_property_tv(काष्ठा पूर्णांकel_sdvo *पूर्णांकel_sdvo,
				      काष्ठा पूर्णांकel_sdvo_connector *पूर्णांकel_sdvo_connector,
				      काष्ठा पूर्णांकel_sdvo_enhancements_reply enhancements)
अणु
	काष्ठा drm_device *dev = पूर्णांकel_sdvo->base.base.dev;
	काष्ठा drm_connector *connector = &पूर्णांकel_sdvo_connector->base.base;
	काष्ठा drm_connector_state *conn_state = connector->state;
	काष्ठा पूर्णांकel_sdvo_connector_state *sdvo_state =
		to_पूर्णांकel_sdvo_connector_state(conn_state);
	u16 response, data_value[2];

	/* when horizontal overscan is supported, Add the left/right property */
	अगर (enhancements.overscan_h) अणु
		अगर (!पूर्णांकel_sdvo_get_value(पूर्णांकel_sdvo,
					  SDVO_CMD_GET_MAX_OVERSCAN_H,
					  &data_value, 4))
			वापस false;

		अगर (!पूर्णांकel_sdvo_get_value(पूर्णांकel_sdvo,
					  SDVO_CMD_GET_OVERSCAN_H,
					  &response, 2))
			वापस false;

		sdvo_state->tv.overscan_h = response;

		पूर्णांकel_sdvo_connector->max_hscan = data_value[0];
		पूर्णांकel_sdvo_connector->left =
			drm_property_create_range(dev, 0, "left_margin", 0, data_value[0]);
		अगर (!पूर्णांकel_sdvo_connector->left)
			वापस false;

		drm_object_attach_property(&connector->base,
					   पूर्णांकel_sdvo_connector->left, 0);

		पूर्णांकel_sdvo_connector->right =
			drm_property_create_range(dev, 0, "right_margin", 0, data_value[0]);
		अगर (!पूर्णांकel_sdvo_connector->right)
			वापस false;

		drm_object_attach_property(&connector->base,
					      पूर्णांकel_sdvo_connector->right, 0);
		DRM_DEBUG_KMS("h_overscan: max %d, "
			      "default %d, current %d\n",
			      data_value[0], data_value[1], response);
	पूर्ण

	अगर (enhancements.overscan_v) अणु
		अगर (!पूर्णांकel_sdvo_get_value(पूर्णांकel_sdvo,
					  SDVO_CMD_GET_MAX_OVERSCAN_V,
					  &data_value, 4))
			वापस false;

		अगर (!पूर्णांकel_sdvo_get_value(पूर्णांकel_sdvo,
					  SDVO_CMD_GET_OVERSCAN_V,
					  &response, 2))
			वापस false;

		sdvo_state->tv.overscan_v = response;

		पूर्णांकel_sdvo_connector->max_vscan = data_value[0];
		पूर्णांकel_sdvo_connector->top =
			drm_property_create_range(dev, 0,
					    "top_margin", 0, data_value[0]);
		अगर (!पूर्णांकel_sdvo_connector->top)
			वापस false;

		drm_object_attach_property(&connector->base,
					   पूर्णांकel_sdvo_connector->top, 0);

		पूर्णांकel_sdvo_connector->bottom =
			drm_property_create_range(dev, 0,
					    "bottom_margin", 0, data_value[0]);
		अगर (!पूर्णांकel_sdvo_connector->bottom)
			वापस false;

		drm_object_attach_property(&connector->base,
					      पूर्णांकel_sdvo_connector->bottom, 0);
		DRM_DEBUG_KMS("v_overscan: max %d, "
			      "default %d, current %d\n",
			      data_value[0], data_value[1], response);
	पूर्ण

	ENHANCEMENT(&sdvo_state->tv, hpos, HPOS);
	ENHANCEMENT(&sdvo_state->tv, vpos, VPOS);
	ENHANCEMENT(&conn_state->tv, saturation, SATURATION);
	ENHANCEMENT(&conn_state->tv, contrast, CONTRAST);
	ENHANCEMENT(&conn_state->tv, hue, HUE);
	ENHANCEMENT(&conn_state->tv, brightness, BRIGHTNESS);
	ENHANCEMENT(&sdvo_state->tv, sharpness, SHARPNESS);
	ENHANCEMENT(&sdvo_state->tv, flicker_filter, FLICKER_FILTER);
	ENHANCEMENT(&sdvo_state->tv, flicker_filter_adaptive, FLICKER_FILTER_ADAPTIVE);
	ENHANCEMENT(&sdvo_state->tv, flicker_filter_2d, FLICKER_FILTER_2D);
	_ENHANCEMENT(sdvo_state->tv.chroma_filter, tv_chroma_filter, TV_CHROMA_FILTER);
	_ENHANCEMENT(sdvo_state->tv.luma_filter, tv_luma_filter, TV_LUMA_FILTER);

	अगर (enhancements.करोt_crawl) अणु
		अगर (!पूर्णांकel_sdvo_get_value(पूर्णांकel_sdvo, SDVO_CMD_GET_DOT_CRAWL, &response, 2))
			वापस false;

		sdvo_state->tv.करोt_crawl = response & 0x1;
		पूर्णांकel_sdvo_connector->करोt_crawl =
			drm_property_create_range(dev, 0, "dot_crawl", 0, 1);
		अगर (!पूर्णांकel_sdvo_connector->करोt_crawl)
			वापस false;

		drm_object_attach_property(&connector->base,
					   पूर्णांकel_sdvo_connector->करोt_crawl, 0);
		DRM_DEBUG_KMS("dot crawl: current %d\n", response);
	पूर्ण

	वापस true;
पूर्ण

अटल bool
पूर्णांकel_sdvo_create_enhance_property_lvds(काष्ठा पूर्णांकel_sdvo *पूर्णांकel_sdvo,
					काष्ठा पूर्णांकel_sdvo_connector *पूर्णांकel_sdvo_connector,
					काष्ठा पूर्णांकel_sdvo_enhancements_reply enhancements)
अणु
	काष्ठा drm_device *dev = पूर्णांकel_sdvo->base.base.dev;
	काष्ठा drm_connector *connector = &पूर्णांकel_sdvo_connector->base.base;
	u16 response, data_value[2];

	ENHANCEMENT(&connector->state->tv, brightness, BRIGHTNESS);

	वापस true;
पूर्ण
#अघोषित ENHANCEMENT
#अघोषित _ENHANCEMENT

अटल bool पूर्णांकel_sdvo_create_enhance_property(काष्ठा पूर्णांकel_sdvo *पूर्णांकel_sdvo,
					       काष्ठा पूर्णांकel_sdvo_connector *पूर्णांकel_sdvo_connector)
अणु
	जोड़ अणु
		काष्ठा पूर्णांकel_sdvo_enhancements_reply reply;
		u16 response;
	पूर्ण enhancements;

	BUILD_BUG_ON(माप(enhancements) != 2);

	अगर (!पूर्णांकel_sdvo_get_value(पूर्णांकel_sdvo,
				  SDVO_CMD_GET_SUPPORTED_ENHANCEMENTS,
				  &enhancements, माप(enhancements)) ||
	    enhancements.response == 0) अणु
		DRM_DEBUG_KMS("No enhancement is supported\n");
		वापस true;
	पूर्ण

	अगर (IS_TV(पूर्णांकel_sdvo_connector))
		वापस पूर्णांकel_sdvo_create_enhance_property_tv(पूर्णांकel_sdvo, पूर्णांकel_sdvo_connector, enhancements.reply);
	अन्यथा अगर (IS_LVDS(पूर्णांकel_sdvo_connector))
		वापस पूर्णांकel_sdvo_create_enhance_property_lvds(पूर्णांकel_sdvo, पूर्णांकel_sdvo_connector, enhancements.reply);
	अन्यथा
		वापस true;
पूर्ण

अटल पूर्णांक पूर्णांकel_sdvo_ddc_proxy_xfer(काष्ठा i2c_adapter *adapter,
				     काष्ठा i2c_msg *msgs,
				     पूर्णांक num)
अणु
	काष्ठा पूर्णांकel_sdvo *sdvo = adapter->algo_data;

	अगर (!__पूर्णांकel_sdvo_set_control_bus_चयन(sdvo, sdvo->ddc_bus))
		वापस -EIO;

	वापस sdvo->i2c->algo->master_xfer(sdvo->i2c, msgs, num);
पूर्ण

अटल u32 पूर्णांकel_sdvo_ddc_proxy_func(काष्ठा i2c_adapter *adapter)
अणु
	काष्ठा पूर्णांकel_sdvo *sdvo = adapter->algo_data;
	वापस sdvo->i2c->algo->functionality(sdvo->i2c);
पूर्ण

अटल स्थिर काष्ठा i2c_algorithm पूर्णांकel_sdvo_ddc_proxy = अणु
	.master_xfer	= पूर्णांकel_sdvo_ddc_proxy_xfer,
	.functionality	= पूर्णांकel_sdvo_ddc_proxy_func
पूर्ण;

अटल व्योम proxy_lock_bus(काष्ठा i2c_adapter *adapter,
			   अचिन्हित पूर्णांक flags)
अणु
	काष्ठा पूर्णांकel_sdvo *sdvo = adapter->algo_data;
	sdvo->i2c->lock_ops->lock_bus(sdvo->i2c, flags);
पूर्ण

अटल पूर्णांक proxy_trylock_bus(काष्ठा i2c_adapter *adapter,
			     अचिन्हित पूर्णांक flags)
अणु
	काष्ठा पूर्णांकel_sdvo *sdvo = adapter->algo_data;
	वापस sdvo->i2c->lock_ops->trylock_bus(sdvo->i2c, flags);
पूर्ण

अटल व्योम proxy_unlock_bus(काष्ठा i2c_adapter *adapter,
			     अचिन्हित पूर्णांक flags)
अणु
	काष्ठा पूर्णांकel_sdvo *sdvo = adapter->algo_data;
	sdvo->i2c->lock_ops->unlock_bus(sdvo->i2c, flags);
पूर्ण

अटल स्थिर काष्ठा i2c_lock_operations proxy_lock_ops = अणु
	.lock_bus =    proxy_lock_bus,
	.trylock_bus = proxy_trylock_bus,
	.unlock_bus =  proxy_unlock_bus,
पूर्ण;

अटल bool
पूर्णांकel_sdvo_init_ddc_proxy(काष्ठा पूर्णांकel_sdvo *sdvo,
			  काष्ठा drm_i915_निजी *dev_priv)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev_priv->drm.dev);

	sdvo->ddc.owner = THIS_MODULE;
	sdvo->ddc.class = I2C_CLASS_DDC;
	snम_लिखो(sdvo->ddc.name, I2C_NAME_SIZE, "SDVO DDC proxy");
	sdvo->ddc.dev.parent = &pdev->dev;
	sdvo->ddc.algo_data = sdvo;
	sdvo->ddc.algo = &पूर्णांकel_sdvo_ddc_proxy;
	sdvo->ddc.lock_ops = &proxy_lock_ops;

	वापस i2c_add_adapter(&sdvo->ddc) == 0;
पूर्ण

अटल व्योम निश्चित_sdvo_port_valid(स्थिर काष्ठा drm_i915_निजी *dev_priv,
				   क्रमागत port port)
अणु
	अगर (HAS_PCH_SPLIT(dev_priv))
		drm_WARN_ON(&dev_priv->drm, port != PORT_B);
	अन्यथा
		drm_WARN_ON(&dev_priv->drm, port != PORT_B && port != PORT_C);
पूर्ण

bool पूर्णांकel_sdvo_init(काष्ठा drm_i915_निजी *dev_priv,
		     i915_reg_t sdvo_reg, क्रमागत port port)
अणु
	काष्ठा पूर्णांकel_encoder *पूर्णांकel_encoder;
	काष्ठा पूर्णांकel_sdvo *पूर्णांकel_sdvo;
	पूर्णांक i;

	निश्चित_sdvo_port_valid(dev_priv, port);

	पूर्णांकel_sdvo = kzalloc(माप(*पूर्णांकel_sdvo), GFP_KERNEL);
	अगर (!पूर्णांकel_sdvo)
		वापस false;

	पूर्णांकel_sdvo->sdvo_reg = sdvo_reg;
	पूर्णांकel_sdvo->port = port;
	पूर्णांकel_sdvo->slave_addr =
		पूर्णांकel_sdvo_get_slave_addr(dev_priv, पूर्णांकel_sdvo) >> 1;
	पूर्णांकel_sdvo_select_i2c_bus(dev_priv, पूर्णांकel_sdvo);
	अगर (!पूर्णांकel_sdvo_init_ddc_proxy(पूर्णांकel_sdvo, dev_priv))
		जाओ err_i2c_bus;

	/* encoder type will be decided later */
	पूर्णांकel_encoder = &पूर्णांकel_sdvo->base;
	पूर्णांकel_encoder->type = INTEL_OUTPUT_SDVO;
	पूर्णांकel_encoder->घातer_करोमुख्य = POWER_DOMAIN_PORT_OTHER;
	पूर्णांकel_encoder->port = port;
	drm_encoder_init(&dev_priv->drm, &पूर्णांकel_encoder->base,
			 &पूर्णांकel_sdvo_enc_funcs, 0,
			 "SDVO %c", port_name(port));

	/* Read the regs to test अगर we can talk to the device */
	क्रम (i = 0; i < 0x40; i++) अणु
		u8 byte;

		अगर (!पूर्णांकel_sdvo_पढ़ो_byte(पूर्णांकel_sdvo, i, &byte)) अणु
			drm_dbg_kms(&dev_priv->drm,
				    "No SDVO device found on %s\n",
				    SDVO_NAME(पूर्णांकel_sdvo));
			जाओ err;
		पूर्ण
	पूर्ण

	पूर्णांकel_encoder->compute_config = पूर्णांकel_sdvo_compute_config;
	अगर (HAS_PCH_SPLIT(dev_priv)) अणु
		पूर्णांकel_encoder->disable = pch_disable_sdvo;
		पूर्णांकel_encoder->post_disable = pch_post_disable_sdvo;
	पूर्ण अन्यथा अणु
		पूर्णांकel_encoder->disable = पूर्णांकel_disable_sdvo;
	पूर्ण
	पूर्णांकel_encoder->pre_enable = पूर्णांकel_sdvo_pre_enable;
	पूर्णांकel_encoder->enable = पूर्णांकel_enable_sdvo;
	पूर्णांकel_encoder->get_hw_state = पूर्णांकel_sdvo_get_hw_state;
	पूर्णांकel_encoder->get_config = पूर्णांकel_sdvo_get_config;

	/* In शेष हाल sdvo lvds is false */
	अगर (!पूर्णांकel_sdvo_get_capabilities(पूर्णांकel_sdvo, &पूर्णांकel_sdvo->caps))
		जाओ err;

	पूर्णांकel_sdvo->colorimetry_cap =
		पूर्णांकel_sdvo_get_colorimetry_cap(पूर्णांकel_sdvo);

	अगर (पूर्णांकel_sdvo_output_setup(पूर्णांकel_sdvo,
				    पूर्णांकel_sdvo->caps.output_flags) != true) अणु
		drm_dbg_kms(&dev_priv->drm,
			    "SDVO output failed to setup on %s\n",
			    SDVO_NAME(पूर्णांकel_sdvo));
		/* Output_setup can leave behind connectors! */
		जाओ err_output;
	पूर्ण

	/*
	 * Only enable the hotplug irq अगर we need it, to work around noisy
	 * hotplug lines.
	 */
	अगर (पूर्णांकel_sdvo->hotplug_active) अणु
		अगर (पूर्णांकel_sdvo->port == PORT_B)
			पूर्णांकel_encoder->hpd_pin = HPD_SDVO_B;
		अन्यथा
			पूर्णांकel_encoder->hpd_pin = HPD_SDVO_C;
	पूर्ण

	/*
	 * Cloning SDVO with anything is often impossible, since the SDVO
	 * encoder can request a special input timing mode. And even अगर that's
	 * not the हाल we have evidence that cloning a plain unscaled mode with
	 * VGA करोesn't really work. Furthermore the cloning flags are way too
	 * simplistic anyway to express such स्थिरraपूर्णांकs, so just give up on
	 * cloning क्रम SDVO encoders.
	 */
	पूर्णांकel_sdvo->base.cloneable = 0;

	पूर्णांकel_sdvo_select_ddc_bus(dev_priv, पूर्णांकel_sdvo);

	/* Set the input timing to the screen. Assume always input 0. */
	अगर (!पूर्णांकel_sdvo_set_target_input(पूर्णांकel_sdvo))
		जाओ err_output;

	अगर (!पूर्णांकel_sdvo_get_input_pixel_घड़ी_range(पूर्णांकel_sdvo,
						    &पूर्णांकel_sdvo->pixel_घड़ी_min,
						    &पूर्णांकel_sdvo->pixel_घड़ी_max))
		जाओ err_output;

	drm_dbg_kms(&dev_priv->drm, "%s device VID/DID: %02X:%02X.%02X, "
			"clock range %dMHz - %dMHz, "
			"input 1: %c, input 2: %c, "
			"output 1: %c, output 2: %c\n",
			SDVO_NAME(पूर्णांकel_sdvo),
			पूर्णांकel_sdvo->caps.venकरोr_id, पूर्णांकel_sdvo->caps.device_id,
			पूर्णांकel_sdvo->caps.device_rev_id,
			पूर्णांकel_sdvo->pixel_घड़ी_min / 1000,
			पूर्णांकel_sdvo->pixel_घड़ी_max / 1000,
			(पूर्णांकel_sdvo->caps.sdvo_inमाला_दो_mask & 0x1) ? 'Y' : 'N',
			(पूर्णांकel_sdvo->caps.sdvo_inमाला_दो_mask & 0x2) ? 'Y' : 'N',
			/* check currently supported outमाला_दो */
			पूर्णांकel_sdvo->caps.output_flags &
			(SDVO_OUTPUT_TMDS0 | SDVO_OUTPUT_RGB0) ? 'Y' : 'N',
			पूर्णांकel_sdvo->caps.output_flags &
			(SDVO_OUTPUT_TMDS1 | SDVO_OUTPUT_RGB1) ? 'Y' : 'N');
	वापस true;

err_output:
	पूर्णांकel_sdvo_output_cleanup(पूर्णांकel_sdvo);

err:
	drm_encoder_cleanup(&पूर्णांकel_encoder->base);
	i2c_del_adapter(&पूर्णांकel_sdvo->ddc);
err_i2c_bus:
	पूर्णांकel_sdvo_unselect_i2c_bus(पूर्णांकel_sdvo);
	kमुक्त(पूर्णांकel_sdvo);

	वापस false;
पूर्ण
