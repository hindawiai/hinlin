<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) Fuzhou Rockchip Electronics Co.Ltd
 *    Zheng Yang <zhengyang@rock-chips.com>
 */

#समावेश <drm/drm_of.h>
#समावेश <drm/drm_probe_helper.h>
#समावेश <drm/drm_simple_kms_helper.h>

#समावेश <linux/clk.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>

#समावेश "rk3066_hdmi.h"

#समावेश "rockchip_drm_drv.h"
#समावेश "rockchip_drm_vop.h"

#घोषणा DEFAULT_PLLA_RATE 30000000

काष्ठा hdmi_data_info अणु
	पूर्णांक vic; /* The CEA Video ID (VIC) of the current drm display mode. */
	bool sink_is_hdmi;
	अचिन्हित पूर्णांक enc_out_क्रमmat;
	अचिन्हित पूर्णांक colorimetry;
पूर्ण;

काष्ठा rk3066_hdmi_i2c अणु
	काष्ठा i2c_adapter adap;

	u8 ddc_addr;
	u8 segment_addr;
	u8 stat;

	काष्ठा mutex i2c_lock; /* For i2c operation. */
	काष्ठा completion cmpltn;
पूर्ण;

काष्ठा rk3066_hdmi अणु
	काष्ठा device *dev;
	काष्ठा drm_device *drm_dev;
	काष्ठा regmap *grf_regmap;
	पूर्णांक irq;
	काष्ठा clk *hclk;
	व्योम __iomem *regs;

	काष्ठा drm_connector connector;
	काष्ठा drm_encoder encoder;

	काष्ठा rk3066_hdmi_i2c *i2c;
	काष्ठा i2c_adapter *ddc;

	अचिन्हित पूर्णांक पंचांगdsclk;

	काष्ठा hdmi_data_info hdmi_data;
	काष्ठा drm_display_mode previous_mode;
पूर्ण;

#घोषणा to_rk3066_hdmi(x) container_of(x, काष्ठा rk3066_hdmi, x)

अटल अंतरभूत u8 hdmi_पढ़ोb(काष्ठा rk3066_hdmi *hdmi, u16 offset)
अणु
	वापस पढ़ोl_relaxed(hdmi->regs + offset);
पूर्ण

अटल अंतरभूत व्योम hdmi_ग_लिखोb(काष्ठा rk3066_hdmi *hdmi, u16 offset, u32 val)
अणु
	ग_लिखोl_relaxed(val, hdmi->regs + offset);
पूर्ण

अटल अंतरभूत व्योम hdmi_modb(काष्ठा rk3066_hdmi *hdmi, u16 offset,
			     u32 msk, u32 val)
अणु
	u8 temp = hdmi_पढ़ोb(hdmi, offset) & ~msk;

	temp |= val & msk;
	hdmi_ग_लिखोb(hdmi, offset, temp);
पूर्ण

अटल व्योम rk3066_hdmi_i2c_init(काष्ठा rk3066_hdmi *hdmi)
अणु
	पूर्णांक ddc_bus_freq;

	ddc_bus_freq = (hdmi->पंचांगdsclk >> 2) / HDMI_SCL_RATE;

	hdmi_ग_लिखोb(hdmi, HDMI_DDC_BUS_FREQ_L, ddc_bus_freq & 0xFF);
	hdmi_ग_लिखोb(hdmi, HDMI_DDC_BUS_FREQ_H, (ddc_bus_freq >> 8) & 0xFF);

	/* Clear the EDID पूर्णांकerrupt flag and mute the पूर्णांकerrupt. */
	hdmi_modb(hdmi, HDMI_INTR_MASK1, HDMI_INTR_EDID_MASK, 0);
	hdmi_ग_लिखोb(hdmi, HDMI_INTR_STATUS1, HDMI_INTR_EDID_MASK);
पूर्ण

अटल अंतरभूत u8 rk3066_hdmi_get_घातer_mode(काष्ठा rk3066_hdmi *hdmi)
अणु
	वापस hdmi_पढ़ोb(hdmi, HDMI_SYS_CTRL) & HDMI_SYS_POWER_MODE_MASK;
पूर्ण

अटल व्योम rk3066_hdmi_set_घातer_mode(काष्ठा rk3066_hdmi *hdmi, पूर्णांक mode)
अणु
	u8 current_mode, next_mode;
	u8 i = 0;

	current_mode = rk3066_hdmi_get_घातer_mode(hdmi);

	DRM_DEV_DEBUG(hdmi->dev, "mode         :%d\n", mode);
	DRM_DEV_DEBUG(hdmi->dev, "current_mode :%d\n", current_mode);

	अगर (current_mode == mode)
		वापस;

	करो अणु
		अगर (current_mode > mode) अणु
			next_mode = current_mode / 2;
		पूर्ण अन्यथा अणु
			अगर (current_mode < HDMI_SYS_POWER_MODE_A)
				next_mode = HDMI_SYS_POWER_MODE_A;
			अन्यथा
				next_mode = current_mode * 2;
		पूर्ण

		DRM_DEV_DEBUG(hdmi->dev, "%d: next_mode :%d\n", i, next_mode);

		अगर (next_mode != HDMI_SYS_POWER_MODE_D) अणु
			hdmi_modb(hdmi, HDMI_SYS_CTRL,
				  HDMI_SYS_POWER_MODE_MASK, next_mode);
		पूर्ण अन्यथा अणु
			hdmi_ग_लिखोb(hdmi, HDMI_SYS_CTRL,
				    HDMI_SYS_POWER_MODE_D |
				    HDMI_SYS_PLL_RESET_MASK);
			usleep_range(90, 100);
			hdmi_ग_लिखोb(hdmi, HDMI_SYS_CTRL,
				    HDMI_SYS_POWER_MODE_D |
				    HDMI_SYS_PLLB_RESET);
			usleep_range(90, 100);
			hdmi_ग_लिखोb(hdmi, HDMI_SYS_CTRL,
				    HDMI_SYS_POWER_MODE_D);
		पूर्ण
		current_mode = next_mode;
		i = i + 1;
	पूर्ण जबतक ((next_mode != mode) && (i < 5));

	/*
	 * When the IP controller isn't configured with accurate video timing,
	 * DDC_CLK should be equal to the PLLA frequency, which is 30MHz,
	 * so we need to init the TMDS rate to the PCLK rate and reconfigure
	 * the DDC घड़ी.
	 */
	अगर (mode < HDMI_SYS_POWER_MODE_D)
		hdmi->पंचांगdsclk = DEFAULT_PLLA_RATE;
पूर्ण

अटल पूर्णांक
rk3066_hdmi_upload_frame(काष्ठा rk3066_hdmi *hdmi, पूर्णांक setup_rc,
			 जोड़ hdmi_infoframe *frame, u32 frame_index,
			 u32 mask, u32 disable, u32 enable)
अणु
	अगर (mask)
		hdmi_modb(hdmi, HDMI_CP_AUTO_SEND_CTRL, mask, disable);

	hdmi_ग_लिखोb(hdmi, HDMI_CP_BUF_INDEX, frame_index);

	अगर (setup_rc >= 0) अणु
		u8 packed_frame[HDMI_MAXIMUM_INFO_FRAME_SIZE];
		sमाप_प्रकार rc, i;

		rc = hdmi_infoframe_pack(frame, packed_frame,
					 माप(packed_frame));
		अगर (rc < 0)
			वापस rc;

		क्रम (i = 0; i < rc; i++)
			hdmi_ग_लिखोb(hdmi, HDMI_CP_BUF_ACC_HB0 + i * 4,
				    packed_frame[i]);

		अगर (mask)
			hdmi_modb(hdmi, HDMI_CP_AUTO_SEND_CTRL, mask, enable);
	पूर्ण

	वापस setup_rc;
पूर्ण

अटल पूर्णांक rk3066_hdmi_config_avi(काष्ठा rk3066_hdmi *hdmi,
				  काष्ठा drm_display_mode *mode)
अणु
	जोड़ hdmi_infoframe frame;
	पूर्णांक rc;

	rc = drm_hdmi_avi_infoframe_from_display_mode(&frame.avi,
						      &hdmi->connector, mode);

	अगर (hdmi->hdmi_data.enc_out_क्रमmat == HDMI_COLORSPACE_YUV444)
		frame.avi.colorspace = HDMI_COLORSPACE_YUV444;
	अन्यथा अगर (hdmi->hdmi_data.enc_out_क्रमmat == HDMI_COLORSPACE_YUV422)
		frame.avi.colorspace = HDMI_COLORSPACE_YUV422;
	अन्यथा
		frame.avi.colorspace = HDMI_COLORSPACE_RGB;

	frame.avi.colorimetry = hdmi->hdmi_data.colorimetry;
	frame.avi.scan_mode = HDMI_SCAN_MODE_NONE;

	वापस rk3066_hdmi_upload_frame(hdmi, rc, &frame,
					HDMI_INFOFRAME_AVI, 0, 0, 0);
पूर्ण

अटल पूर्णांक rk3066_hdmi_config_video_timing(काष्ठा rk3066_hdmi *hdmi,
					   काष्ठा drm_display_mode *mode)
अणु
	पूर्णांक value, vsync_offset;

	/* Set the details क्रम the बाह्यal polarity and पूर्णांकerlace mode. */
	value = HDMI_EXT_VIDEO_SET_EN;
	value |= mode->flags & DRM_MODE_FLAG_PHSYNC ?
		 HDMI_VIDEO_HSYNC_ACTIVE_HIGH : HDMI_VIDEO_HSYNC_ACTIVE_LOW;
	value |= mode->flags & DRM_MODE_FLAG_PVSYNC ?
		 HDMI_VIDEO_VSYNC_ACTIVE_HIGH : HDMI_VIDEO_VSYNC_ACTIVE_LOW;
	value |= mode->flags & DRM_MODE_FLAG_INTERLACE ?
		 HDMI_VIDEO_MODE_INTERLACE : HDMI_VIDEO_MODE_PROGRESSIVE;

	अगर (hdmi->hdmi_data.vic == 2 || hdmi->hdmi_data.vic == 3)
		vsync_offset = 6;
	अन्यथा
		vsync_offset = 0;

	value |= vsync_offset << HDMI_VIDEO_VSYNC_OFFSET_SHIFT;
	hdmi_ग_लिखोb(hdmi, HDMI_EXT_VIDEO_PARA, value);

	/* Set the details क्रम the बाह्यal video timing. */
	value = mode->htotal;
	hdmi_ग_लिखोb(hdmi, HDMI_EXT_HTOTAL_L, value & 0xFF);
	hdmi_ग_लिखोb(hdmi, HDMI_EXT_HTOTAL_H, (value >> 8) & 0xFF);

	value = mode->htotal - mode->hdisplay;
	hdmi_ग_लिखोb(hdmi, HDMI_EXT_HBLANK_L, value & 0xFF);
	hdmi_ग_लिखोb(hdmi, HDMI_EXT_HBLANK_H, (value >> 8) & 0xFF);

	value = mode->htotal - mode->hsync_start;
	hdmi_ग_लिखोb(hdmi, HDMI_EXT_HDELAY_L, value & 0xFF);
	hdmi_ग_लिखोb(hdmi, HDMI_EXT_HDELAY_H, (value >> 8) & 0xFF);

	value = mode->hsync_end - mode->hsync_start;
	hdmi_ग_लिखोb(hdmi, HDMI_EXT_HDURATION_L, value & 0xFF);
	hdmi_ग_लिखोb(hdmi, HDMI_EXT_HDURATION_H, (value >> 8) & 0xFF);

	value = mode->vtotal;
	hdmi_ग_लिखोb(hdmi, HDMI_EXT_VTOTAL_L, value & 0xFF);
	hdmi_ग_लिखोb(hdmi, HDMI_EXT_VTOTAL_H, (value >> 8) & 0xFF);

	value = mode->vtotal - mode->vdisplay;
	hdmi_ग_लिखोb(hdmi, HDMI_EXT_VBLANK_L, value & 0xFF);

	value = mode->vtotal - mode->vsync_start + vsync_offset;
	hdmi_ग_लिखोb(hdmi, HDMI_EXT_VDELAY, value & 0xFF);

	value = mode->vsync_end - mode->vsync_start;
	hdmi_ग_लिखोb(hdmi, HDMI_EXT_VDURATION, value & 0xFF);

	वापस 0;
पूर्ण

अटल व्योम
rk3066_hdmi_phy_ग_लिखो(काष्ठा rk3066_hdmi *hdmi, u16 offset, u8 value)
अणु
	hdmi_ग_लिखोb(hdmi, offset, value);
	hdmi_modb(hdmi, HDMI_SYS_CTRL,
		  HDMI_SYS_PLL_RESET_MASK, HDMI_SYS_PLL_RESET);
	usleep_range(90, 100);
	hdmi_modb(hdmi, HDMI_SYS_CTRL, HDMI_SYS_PLL_RESET_MASK, 0);
	usleep_range(900, 1000);
पूर्ण

अटल व्योम rk3066_hdmi_config_phy(काष्ठा rk3066_hdmi *hdmi)
अणु
	/* TMDS uses the same frequency as dclk. */
	hdmi_ग_लिखोb(hdmi, HDMI_DEEP_COLOR_MODE, 0x22);

	/*
	 * The semi-खुला करोcumentation करोes not describe the hdmi रेजिस्टरs
	 * used by the function rk3066_hdmi_phy_ग_लिखो(), so we keep using
	 * these magic values क्रम now.
	 */
	अगर (hdmi->पंचांगdsclk > 100000000) अणु
		rk3066_hdmi_phy_ग_लिखो(hdmi, 0x158, 0x0E);
		rk3066_hdmi_phy_ग_लिखो(hdmi, 0x15c, 0x00);
		rk3066_hdmi_phy_ग_लिखो(hdmi, 0x160, 0x60);
		rk3066_hdmi_phy_ग_लिखो(hdmi, 0x164, 0x00);
		rk3066_hdmi_phy_ग_लिखो(hdmi, 0x168, 0xDA);
		rk3066_hdmi_phy_ग_लिखो(hdmi, 0x16c, 0xA1);
		rk3066_hdmi_phy_ग_लिखो(hdmi, 0x170, 0x0e);
		rk3066_hdmi_phy_ग_लिखो(hdmi, 0x174, 0x22);
		rk3066_hdmi_phy_ग_लिखो(hdmi, 0x178, 0x00);
	पूर्ण अन्यथा अगर (hdmi->पंचांगdsclk > 50000000) अणु
		rk3066_hdmi_phy_ग_लिखो(hdmi, 0x158, 0x06);
		rk3066_hdmi_phy_ग_लिखो(hdmi, 0x15c, 0x00);
		rk3066_hdmi_phy_ग_लिखो(hdmi, 0x160, 0x60);
		rk3066_hdmi_phy_ग_लिखो(hdmi, 0x164, 0x00);
		rk3066_hdmi_phy_ग_लिखो(hdmi, 0x168, 0xCA);
		rk3066_hdmi_phy_ग_लिखो(hdmi, 0x16c, 0xA3);
		rk3066_hdmi_phy_ग_लिखो(hdmi, 0x170, 0x0e);
		rk3066_hdmi_phy_ग_लिखो(hdmi, 0x174, 0x20);
		rk3066_hdmi_phy_ग_लिखो(hdmi, 0x178, 0x00);
	पूर्ण अन्यथा अणु
		rk3066_hdmi_phy_ग_लिखो(hdmi, 0x158, 0x02);
		rk3066_hdmi_phy_ग_लिखो(hdmi, 0x15c, 0x00);
		rk3066_hdmi_phy_ग_लिखो(hdmi, 0x160, 0x60);
		rk3066_hdmi_phy_ग_लिखो(hdmi, 0x164, 0x00);
		rk3066_hdmi_phy_ग_लिखो(hdmi, 0x168, 0xC2);
		rk3066_hdmi_phy_ग_लिखो(hdmi, 0x16c, 0xA2);
		rk3066_hdmi_phy_ग_लिखो(hdmi, 0x170, 0x0e);
		rk3066_hdmi_phy_ग_लिखो(hdmi, 0x174, 0x20);
		rk3066_hdmi_phy_ग_लिखो(hdmi, 0x178, 0x00);
	पूर्ण
पूर्ण

अटल पूर्णांक rk3066_hdmi_setup(काष्ठा rk3066_hdmi *hdmi,
			     काष्ठा drm_display_mode *mode)
अणु
	hdmi->hdmi_data.vic = drm_match_cea_mode(mode);
	hdmi->hdmi_data.enc_out_क्रमmat = HDMI_COLORSPACE_RGB;

	अगर (hdmi->hdmi_data.vic == 6 || hdmi->hdmi_data.vic == 7 ||
	    hdmi->hdmi_data.vic == 21 || hdmi->hdmi_data.vic == 22 ||
	    hdmi->hdmi_data.vic == 2 || hdmi->hdmi_data.vic == 3 ||
	    hdmi->hdmi_data.vic == 17 || hdmi->hdmi_data.vic == 18)
		hdmi->hdmi_data.colorimetry = HDMI_COLORIMETRY_ITU_601;
	अन्यथा
		hdmi->hdmi_data.colorimetry = HDMI_COLORIMETRY_ITU_709;

	hdmi->पंचांगdsclk = mode->घड़ी * 1000;

	/* Mute video and audio output. */
	hdmi_modb(hdmi, HDMI_VIDEO_CTRL2, HDMI_VIDEO_AUDIO_DISABLE_MASK,
		  HDMI_AUDIO_DISABLE | HDMI_VIDEO_DISABLE);

	/* Set घातer state to mode B. */
	अगर (rk3066_hdmi_get_घातer_mode(hdmi) != HDMI_SYS_POWER_MODE_B)
		rk3066_hdmi_set_घातer_mode(hdmi, HDMI_SYS_POWER_MODE_B);

	/* Input video mode is RGB 24 bit. Use बाह्यal data enable संकेत. */
	hdmi_modb(hdmi, HDMI_AV_CTRL1,
		  HDMI_VIDEO_DE_MASK, HDMI_VIDEO_EXTERNAL_DE);
	hdmi_ग_लिखोb(hdmi, HDMI_VIDEO_CTRL1,
		    HDMI_VIDEO_OUTPUT_RGB444 |
		    HDMI_VIDEO_INPUT_DATA_DEPTH_8BIT |
		    HDMI_VIDEO_INPUT_COLOR_RGB);
	hdmi_ग_लिखोb(hdmi, HDMI_DEEP_COLOR_MODE, 0x20);

	rk3066_hdmi_config_video_timing(hdmi, mode);

	अगर (hdmi->hdmi_data.sink_is_hdmi) अणु
		hdmi_modb(hdmi, HDMI_HDCP_CTRL, HDMI_VIDEO_MODE_MASK,
			  HDMI_VIDEO_MODE_HDMI);
		rk3066_hdmi_config_avi(hdmi, mode);
	पूर्ण अन्यथा अणु
		hdmi_modb(hdmi, HDMI_HDCP_CTRL, HDMI_VIDEO_MODE_MASK, 0);
	पूर्ण

	rk3066_hdmi_config_phy(hdmi);

	rk3066_hdmi_set_घातer_mode(hdmi, HDMI_SYS_POWER_MODE_E);

	/*
	 * When the IP controller is configured with accurate video
	 * timing, the TMDS घड़ी source should be चयनed to
	 * DCLK_LCDC, so we need to init the TMDS rate to the pixel mode
	 * घड़ी rate and reconfigure the DDC घड़ी.
	 */
	rk3066_hdmi_i2c_init(hdmi);

	/* Unmute video output. */
	hdmi_modb(hdmi, HDMI_VIDEO_CTRL2,
		  HDMI_VIDEO_AUDIO_DISABLE_MASK, HDMI_AUDIO_DISABLE);
	वापस 0;
पूर्ण

अटल व्योम
rk3066_hdmi_encoder_mode_set(काष्ठा drm_encoder *encoder,
			     काष्ठा drm_display_mode *mode,
			     काष्ठा drm_display_mode *adj_mode)
अणु
	काष्ठा rk3066_hdmi *hdmi = to_rk3066_hdmi(encoder);

	/* Store the display mode क्रम plugin/DPMS घातeron events. */
	स_नकल(&hdmi->previous_mode, adj_mode, माप(hdmi->previous_mode));
पूर्ण

अटल व्योम rk3066_hdmi_encoder_enable(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा rk3066_hdmi *hdmi = to_rk3066_hdmi(encoder);
	पूर्णांक mux, val;

	mux = drm_of_encoder_active_endpoपूर्णांक_id(hdmi->dev->of_node, encoder);
	अगर (mux)
		val = (HDMI_VIDEO_SEL << 16) | HDMI_VIDEO_SEL;
	अन्यथा
		val = HDMI_VIDEO_SEL << 16;

	regmap_ग_लिखो(hdmi->grf_regmap, GRF_SOC_CON0, val);

	DRM_DEV_DEBUG(hdmi->dev, "hdmi encoder enable select: vop%s\n",
		      (mux) ? "1" : "0");

	rk3066_hdmi_setup(hdmi, &hdmi->previous_mode);
पूर्ण

अटल व्योम rk3066_hdmi_encoder_disable(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा rk3066_hdmi *hdmi = to_rk3066_hdmi(encoder);

	DRM_DEV_DEBUG(hdmi->dev, "hdmi encoder disable\n");

	अगर (rk3066_hdmi_get_घातer_mode(hdmi) == HDMI_SYS_POWER_MODE_E) अणु
		hdmi_ग_लिखोb(hdmi, HDMI_VIDEO_CTRL2,
			    HDMI_VIDEO_AUDIO_DISABLE_MASK);
		hdmi_modb(hdmi, HDMI_VIDEO_CTRL2,
			  HDMI_AUDIO_CP_LOGIC_RESET_MASK,
			  HDMI_AUDIO_CP_LOGIC_RESET);
		usleep_range(500, 510);
	पूर्ण
	rk3066_hdmi_set_घातer_mode(hdmi, HDMI_SYS_POWER_MODE_A);
पूर्ण

अटल bool
rk3066_hdmi_encoder_mode_fixup(काष्ठा drm_encoder *encoder,
			       स्थिर काष्ठा drm_display_mode *mode,
			       काष्ठा drm_display_mode *adj_mode)
अणु
	वापस true;
पूर्ण

अटल पूर्णांक
rk3066_hdmi_encoder_atomic_check(काष्ठा drm_encoder *encoder,
				 काष्ठा drm_crtc_state *crtc_state,
				 काष्ठा drm_connector_state *conn_state)
अणु
	काष्ठा rockchip_crtc_state *s = to_rockchip_crtc_state(crtc_state);

	s->output_mode = ROCKCHIP_OUT_MODE_P888;
	s->output_type = DRM_MODE_CONNECTOR_HDMIA;

	वापस 0;
पूर्ण

अटल स्थिर
काष्ठा drm_encoder_helper_funcs rk3066_hdmi_encoder_helper_funcs = अणु
	.enable       = rk3066_hdmi_encoder_enable,
	.disable      = rk3066_hdmi_encoder_disable,
	.mode_fixup   = rk3066_hdmi_encoder_mode_fixup,
	.mode_set     = rk3066_hdmi_encoder_mode_set,
	.atomic_check = rk3066_hdmi_encoder_atomic_check,
पूर्ण;

अटल क्रमागत drm_connector_status
rk3066_hdmi_connector_detect(काष्ठा drm_connector *connector, bool क्रमce)
अणु
	काष्ठा rk3066_hdmi *hdmi = to_rk3066_hdmi(connector);

	वापस (hdmi_पढ़ोb(hdmi, HDMI_HPG_MENS_STA) & HDMI_HPG_IN_STATUS_HIGH) ?
		connector_status_connected : connector_status_disconnected;
पूर्ण

अटल पूर्णांक rk3066_hdmi_connector_get_modes(काष्ठा drm_connector *connector)
अणु
	काष्ठा rk3066_hdmi *hdmi = to_rk3066_hdmi(connector);
	काष्ठा edid *edid;
	पूर्णांक ret = 0;

	अगर (!hdmi->ddc)
		वापस 0;

	edid = drm_get_edid(connector, hdmi->ddc);
	अगर (edid) अणु
		hdmi->hdmi_data.sink_is_hdmi = drm_detect_hdmi_monitor(edid);
		drm_connector_update_edid_property(connector, edid);
		ret = drm_add_edid_modes(connector, edid);
		kमुक्त(edid);
	पूर्ण

	वापस ret;
पूर्ण

अटल क्रमागत drm_mode_status
rk3066_hdmi_connector_mode_valid(काष्ठा drm_connector *connector,
				 काष्ठा drm_display_mode *mode)
अणु
	u32 vic = drm_match_cea_mode(mode);

	अगर (vic > 1)
		वापस MODE_OK;
	अन्यथा
		वापस MODE_BAD;
पूर्ण

अटल काष्ठा drm_encoder *
rk3066_hdmi_connector_best_encoder(काष्ठा drm_connector *connector)
अणु
	काष्ठा rk3066_hdmi *hdmi = to_rk3066_hdmi(connector);

	वापस &hdmi->encoder;
पूर्ण

अटल पूर्णांक
rk3066_hdmi_probe_single_connector_modes(काष्ठा drm_connector *connector,
					 uपूर्णांक32_t maxX, uपूर्णांक32_t maxY)
अणु
	अगर (maxX > 1920)
		maxX = 1920;
	अगर (maxY > 1080)
		maxY = 1080;

	वापस drm_helper_probe_single_connector_modes(connector, maxX, maxY);
पूर्ण

अटल व्योम rk3066_hdmi_connector_destroy(काष्ठा drm_connector *connector)
अणु
	drm_connector_unरेजिस्टर(connector);
	drm_connector_cleanup(connector);
पूर्ण

अटल स्थिर काष्ठा drm_connector_funcs rk3066_hdmi_connector_funcs = अणु
	.fill_modes = rk3066_hdmi_probe_single_connector_modes,
	.detect = rk3066_hdmi_connector_detect,
	.destroy = rk3066_hdmi_connector_destroy,
	.reset = drm_atomic_helper_connector_reset,
	.atomic_duplicate_state = drm_atomic_helper_connector_duplicate_state,
	.atomic_destroy_state = drm_atomic_helper_connector_destroy_state,
पूर्ण;

अटल स्थिर
काष्ठा drm_connector_helper_funcs rk3066_hdmi_connector_helper_funcs = अणु
	.get_modes = rk3066_hdmi_connector_get_modes,
	.mode_valid = rk3066_hdmi_connector_mode_valid,
	.best_encoder = rk3066_hdmi_connector_best_encoder,
पूर्ण;

अटल पूर्णांक
rk3066_hdmi_रेजिस्टर(काष्ठा drm_device *drm, काष्ठा rk3066_hdmi *hdmi)
अणु
	काष्ठा drm_encoder *encoder = &hdmi->encoder;
	काष्ठा device *dev = hdmi->dev;

	encoder->possible_crtcs =
		drm_of_find_possible_crtcs(drm, dev->of_node);

	/*
	 * If we failed to find the CRTC(s) which this encoder is
	 * supposed to be connected to, it's because the CRTC has
	 * not been रेजिस्टरed yet.  Defer probing, and hope that
	 * the required CRTC is added later.
	 */
	अगर (encoder->possible_crtcs == 0)
		वापस -EPROBE_DEFER;

	drm_encoder_helper_add(encoder, &rk3066_hdmi_encoder_helper_funcs);
	drm_simple_encoder_init(drm, encoder, DRM_MODE_ENCODER_TMDS);

	hdmi->connector.polled = DRM_CONNECTOR_POLL_HPD;

	drm_connector_helper_add(&hdmi->connector,
				 &rk3066_hdmi_connector_helper_funcs);
	drm_connector_init_with_ddc(drm, &hdmi->connector,
				    &rk3066_hdmi_connector_funcs,
				    DRM_MODE_CONNECTOR_HDMIA,
				    hdmi->ddc);

	drm_connector_attach_encoder(&hdmi->connector, encoder);

	वापस 0;
पूर्ण

अटल irqवापस_t rk3066_hdmi_hardirq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा rk3066_hdmi *hdmi = dev_id;
	irqवापस_t ret = IRQ_NONE;
	u8 पूर्णांकerrupt;

	अगर (rk3066_hdmi_get_घातer_mode(hdmi) == HDMI_SYS_POWER_MODE_A)
		hdmi_ग_लिखोb(hdmi, HDMI_SYS_CTRL, HDMI_SYS_POWER_MODE_B);

	पूर्णांकerrupt = hdmi_पढ़ोb(hdmi, HDMI_INTR_STATUS1);
	अगर (पूर्णांकerrupt)
		hdmi_ग_लिखोb(hdmi, HDMI_INTR_STATUS1, पूर्णांकerrupt);

	अगर (पूर्णांकerrupt & HDMI_INTR_EDID_MASK) अणु
		hdmi->i2c->stat = पूर्णांकerrupt;
		complete(&hdmi->i2c->cmpltn);
	पूर्ण

	अगर (पूर्णांकerrupt & (HDMI_INTR_HOTPLUG | HDMI_INTR_MSENS))
		ret = IRQ_WAKE_THREAD;

	वापस ret;
पूर्ण

अटल irqवापस_t rk3066_hdmi_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा rk3066_hdmi *hdmi = dev_id;

	drm_helper_hpd_irq_event(hdmi->connector.dev);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक rk3066_hdmi_i2c_पढ़ो(काष्ठा rk3066_hdmi *hdmi, काष्ठा i2c_msg *msgs)
अणु
	पूर्णांक length = msgs->len;
	u8 *buf = msgs->buf;
	पूर्णांक ret;

	ret = रुको_क्रम_completion_समयout(&hdmi->i2c->cmpltn, HZ / 10);
	अगर (!ret || hdmi->i2c->stat & HDMI_INTR_EDID_ERR)
		वापस -EAGAIN;

	जबतक (length--)
		*buf++ = hdmi_पढ़ोb(hdmi, HDMI_DDC_READ_FIFO_ADDR);

	वापस 0;
पूर्ण

अटल पूर्णांक rk3066_hdmi_i2c_ग_लिखो(काष्ठा rk3066_hdmi *hdmi, काष्ठा i2c_msg *msgs)
अणु
	/*
	 * The DDC module only supports पढ़ो EDID message, so
	 * we assume that each word ग_लिखो to this i2c adapter
	 * should be the offset of the EDID word address.
	 */
	अगर (msgs->len != 1 ||
	    (msgs->addr != DDC_ADDR && msgs->addr != DDC_SEGMENT_ADDR))
		वापस -EINVAL;

	reinit_completion(&hdmi->i2c->cmpltn);

	अगर (msgs->addr == DDC_SEGMENT_ADDR)
		hdmi->i2c->segment_addr = msgs->buf[0];
	अगर (msgs->addr == DDC_ADDR)
		hdmi->i2c->ddc_addr = msgs->buf[0];

	/* Set edid fअगरo first address. */
	hdmi_ग_लिखोb(hdmi, HDMI_EDID_FIFO_ADDR, 0x00);

	/* Set edid word address 0x00/0x80. */
	hdmi_ग_लिखोb(hdmi, HDMI_EDID_WORD_ADDR, hdmi->i2c->ddc_addr);

	/* Set edid segment poपूर्णांकer. */
	hdmi_ग_लिखोb(hdmi, HDMI_EDID_SEGMENT_POINTER, hdmi->i2c->segment_addr);

	वापस 0;
पूर्ण

अटल पूर्णांक rk3066_hdmi_i2c_xfer(काष्ठा i2c_adapter *adap,
				काष्ठा i2c_msg *msgs, पूर्णांक num)
अणु
	काष्ठा rk3066_hdmi *hdmi = i2c_get_adapdata(adap);
	काष्ठा rk3066_hdmi_i2c *i2c = hdmi->i2c;
	पूर्णांक i, ret = 0;

	mutex_lock(&i2c->i2c_lock);

	rk3066_hdmi_i2c_init(hdmi);

	/* Unmute HDMI EDID पूर्णांकerrupt. */
	hdmi_modb(hdmi, HDMI_INTR_MASK1,
		  HDMI_INTR_EDID_MASK, HDMI_INTR_EDID_MASK);
	i2c->stat = 0;

	क्रम (i = 0; i < num; i++) अणु
		DRM_DEV_DEBUG(hdmi->dev,
			      "xfer: num: %d/%d, len: %d, flags: %#x\n",
			      i + 1, num, msgs[i].len, msgs[i].flags);

		अगर (msgs[i].flags & I2C_M_RD)
			ret = rk3066_hdmi_i2c_पढ़ो(hdmi, &msgs[i]);
		अन्यथा
			ret = rk3066_hdmi_i2c_ग_लिखो(hdmi, &msgs[i]);

		अगर (ret < 0)
			अवरोध;
	पूर्ण

	अगर (!ret)
		ret = num;

	/* Mute HDMI EDID पूर्णांकerrupt. */
	hdmi_modb(hdmi, HDMI_INTR_MASK1, HDMI_INTR_EDID_MASK, 0);

	mutex_unlock(&i2c->i2c_lock);

	वापस ret;
पूर्ण

अटल u32 rk3066_hdmi_i2c_func(काष्ठा i2c_adapter *adapter)
अणु
	वापस I2C_FUNC_I2C | I2C_FUNC_SMBUS_EMUL;
पूर्ण

अटल स्थिर काष्ठा i2c_algorithm rk3066_hdmi_algorithm = अणु
	.master_xfer   = rk3066_hdmi_i2c_xfer,
	.functionality = rk3066_hdmi_i2c_func,
पूर्ण;

अटल काष्ठा i2c_adapter *rk3066_hdmi_i2c_adapter(काष्ठा rk3066_hdmi *hdmi)
अणु
	काष्ठा i2c_adapter *adap;
	काष्ठा rk3066_hdmi_i2c *i2c;
	पूर्णांक ret;

	i2c = devm_kzalloc(hdmi->dev, माप(*i2c), GFP_KERNEL);
	अगर (!i2c)
		वापस ERR_PTR(-ENOMEM);

	mutex_init(&i2c->i2c_lock);
	init_completion(&i2c->cmpltn);

	adap = &i2c->adap;
	adap->class = I2C_CLASS_DDC;
	adap->owner = THIS_MODULE;
	adap->dev.parent = hdmi->dev;
	adap->dev.of_node = hdmi->dev->of_node;
	adap->algo = &rk3066_hdmi_algorithm;
	strlcpy(adap->name, "RK3066 HDMI", माप(adap->name));
	i2c_set_adapdata(adap, hdmi);

	ret = i2c_add_adapter(adap);
	अगर (ret) अणु
		DRM_DEV_ERROR(hdmi->dev, "cannot add %s I2C adapter\n",
			      adap->name);
		devm_kमुक्त(hdmi->dev, i2c);
		वापस ERR_PTR(ret);
	पूर्ण

	hdmi->i2c = i2c;

	DRM_DEV_DEBUG(hdmi->dev, "registered %s I2C bus driver\n", adap->name);

	वापस adap;
पूर्ण

अटल पूर्णांक rk3066_hdmi_bind(काष्ठा device *dev, काष्ठा device *master,
			    व्योम *data)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा drm_device *drm = data;
	काष्ठा rk3066_hdmi *hdmi;
	पूर्णांक irq;
	पूर्णांक ret;

	hdmi = devm_kzalloc(dev, माप(*hdmi), GFP_KERNEL);
	अगर (!hdmi)
		वापस -ENOMEM;

	hdmi->dev = dev;
	hdmi->drm_dev = drm;
	hdmi->regs = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(hdmi->regs))
		वापस PTR_ERR(hdmi->regs);

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;

	hdmi->hclk = devm_clk_get(dev, "hclk");
	अगर (IS_ERR(hdmi->hclk)) अणु
		DRM_DEV_ERROR(dev, "unable to get HDMI hclk clock\n");
		वापस PTR_ERR(hdmi->hclk);
	पूर्ण

	ret = clk_prepare_enable(hdmi->hclk);
	अगर (ret) अणु
		DRM_DEV_ERROR(dev, "cannot enable HDMI hclk clock: %d\n", ret);
		वापस ret;
	पूर्ण

	hdmi->grf_regmap = syscon_regmap_lookup_by_phandle(dev->of_node,
							   "rockchip,grf");
	अगर (IS_ERR(hdmi->grf_regmap)) अणु
		DRM_DEV_ERROR(dev, "unable to get rockchip,grf\n");
		ret = PTR_ERR(hdmi->grf_regmap);
		जाओ err_disable_hclk;
	पूर्ण

	/* पूर्णांकernal hclk = hdmi_hclk / 25 */
	hdmi_ग_लिखोb(hdmi, HDMI_INTERNAL_CLK_DIVIDER, 25);

	hdmi->ddc = rk3066_hdmi_i2c_adapter(hdmi);
	अगर (IS_ERR(hdmi->ddc)) अणु
		ret = PTR_ERR(hdmi->ddc);
		hdmi->ddc = शून्य;
		जाओ err_disable_hclk;
	पूर्ण

	rk3066_hdmi_set_घातer_mode(hdmi, HDMI_SYS_POWER_MODE_B);
	usleep_range(999, 1000);
	hdmi_ग_लिखोb(hdmi, HDMI_INTR_MASK1, HDMI_INTR_HOTPLUG);
	hdmi_ग_लिखोb(hdmi, HDMI_INTR_MASK2, 0);
	hdmi_ग_लिखोb(hdmi, HDMI_INTR_MASK3, 0);
	hdmi_ग_लिखोb(hdmi, HDMI_INTR_MASK4, 0);
	rk3066_hdmi_set_घातer_mode(hdmi, HDMI_SYS_POWER_MODE_A);

	ret = rk3066_hdmi_रेजिस्टर(drm, hdmi);
	अगर (ret)
		जाओ err_disable_i2c;

	dev_set_drvdata(dev, hdmi);

	ret = devm_request_thपढ़ोed_irq(dev, irq, rk3066_hdmi_hardirq,
					rk3066_hdmi_irq, IRQF_SHARED,
					dev_name(dev), hdmi);
	अगर (ret) अणु
		DRM_DEV_ERROR(dev, "failed to request hdmi irq: %d\n", ret);
		जाओ err_cleanup_hdmi;
	पूर्ण

	वापस 0;

err_cleanup_hdmi:
	hdmi->connector.funcs->destroy(&hdmi->connector);
	hdmi->encoder.funcs->destroy(&hdmi->encoder);
err_disable_i2c:
	i2c_put_adapter(hdmi->ddc);
err_disable_hclk:
	clk_disable_unprepare(hdmi->hclk);

	वापस ret;
पूर्ण

अटल व्योम rk3066_hdmi_unbind(काष्ठा device *dev, काष्ठा device *master,
			       व्योम *data)
अणु
	काष्ठा rk3066_hdmi *hdmi = dev_get_drvdata(dev);

	hdmi->connector.funcs->destroy(&hdmi->connector);
	hdmi->encoder.funcs->destroy(&hdmi->encoder);

	i2c_put_adapter(hdmi->ddc);
	clk_disable_unprepare(hdmi->hclk);
पूर्ण

अटल स्थिर काष्ठा component_ops rk3066_hdmi_ops = अणु
	.bind   = rk3066_hdmi_bind,
	.unbind = rk3066_hdmi_unbind,
पूर्ण;

अटल पूर्णांक rk3066_hdmi_probe(काष्ठा platक्रमm_device *pdev)
अणु
	वापस component_add(&pdev->dev, &rk3066_hdmi_ops);
पूर्ण

अटल पूर्णांक rk3066_hdmi_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	component_del(&pdev->dev, &rk3066_hdmi_ops);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id rk3066_hdmi_dt_ids[] = अणु
	अणु .compatible = "rockchip,rk3066-hdmi" पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, rk3066_hdmi_dt_ids);

काष्ठा platक्रमm_driver rk3066_hdmi_driver = अणु
	.probe  = rk3066_hdmi_probe,
	.हटाओ = rk3066_hdmi_हटाओ,
	.driver = अणु
		.name = "rockchip-rk3066-hdmi",
		.of_match_table = rk3066_hdmi_dt_ids,
	पूर्ण,
पूर्ण;
