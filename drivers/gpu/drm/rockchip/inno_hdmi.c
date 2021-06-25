<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) Fuzhou Rockchip Electronics Co.Ltd
 *    Zheng Yang <zhengyang@rock-chips.com>
 *    Yakir Yang <ykk@rock-chips.com>
 */

#समावेश <linux/irq.h>
#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/hdmi.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/of_device.h>

#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_edid.h>
#समावेश <drm/drm_of.h>
#समावेश <drm/drm_probe_helper.h>
#समावेश <drm/drm_simple_kms_helper.h>

#समावेश "rockchip_drm_drv.h"
#समावेश "rockchip_drm_vop.h"

#समावेश "inno_hdmi.h"

#घोषणा to_inno_hdmi(x)	container_of(x, काष्ठा inno_hdmi, x)

काष्ठा hdmi_data_info अणु
	पूर्णांक vic;
	bool sink_is_hdmi;
	bool sink_has_audio;
	अचिन्हित पूर्णांक enc_in_क्रमmat;
	अचिन्हित पूर्णांक enc_out_क्रमmat;
	अचिन्हित पूर्णांक colorimetry;
पूर्ण;

काष्ठा inno_hdmi_i2c अणु
	काष्ठा i2c_adapter adap;

	u8 ddc_addr;
	u8 segment_addr;

	काष्ठा mutex lock;
	काष्ठा completion cmp;
पूर्ण;

काष्ठा inno_hdmi अणु
	काष्ठा device *dev;
	काष्ठा drm_device *drm_dev;

	पूर्णांक irq;
	काष्ठा clk *pclk;
	व्योम __iomem *regs;

	काष्ठा drm_connector	connector;
	काष्ठा drm_encoder	encoder;

	काष्ठा inno_hdmi_i2c *i2c;
	काष्ठा i2c_adapter *ddc;

	अचिन्हित पूर्णांक पंचांगds_rate;

	काष्ठा hdmi_data_info	hdmi_data;
	काष्ठा drm_display_mode previous_mode;
पूर्ण;

क्रमागत अणु
	CSC_ITU601_16_235_TO_RGB_0_255_8BIT,
	CSC_ITU601_0_255_TO_RGB_0_255_8BIT,
	CSC_ITU709_16_235_TO_RGB_0_255_8BIT,
	CSC_RGB_0_255_TO_ITU601_16_235_8BIT,
	CSC_RGB_0_255_TO_ITU709_16_235_8BIT,
	CSC_RGB_0_255_TO_RGB_16_235_8BIT,
पूर्ण;

अटल स्थिर अक्षर coeff_csc[][24] = अणु
	/*
	 * YUV2RGB:601 SD mode(Y[16:235], UV[16:240], RGB[0:255]):
	 *   R = 1.164*Y + 1.596*V - 204
	 *   G = 1.164*Y - 0.391*U - 0.813*V + 154
	 *   B = 1.164*Y + 2.018*U - 258
	 */
	अणु
		0x04, 0xa7, 0x00, 0x00, 0x06, 0x62, 0x02, 0xcc,
		0x04, 0xa7, 0x11, 0x90, 0x13, 0x40, 0x00, 0x9a,
		0x04, 0xa7, 0x08, 0x12, 0x00, 0x00, 0x03, 0x02
	पूर्ण,
	/*
	 * YUV2RGB:601 SD mode(YUV[0:255],RGB[0:255]):
	 *   R = Y + 1.402*V - 248
	 *   G = Y - 0.344*U - 0.714*V + 135
	 *   B = Y + 1.772*U - 227
	 */
	अणु
		0x04, 0x00, 0x00, 0x00, 0x05, 0x9b, 0x02, 0xf8,
		0x04, 0x00, 0x11, 0x60, 0x12, 0xdb, 0x00, 0x87,
		0x04, 0x00, 0x07, 0x16, 0x00, 0x00, 0x02, 0xe3
	पूर्ण,
	/*
	 * YUV2RGB:709 HD mode(Y[16:235],UV[16:240],RGB[0:255]):
	 *   R = 1.164*Y + 1.793*V - 248
	 *   G = 1.164*Y - 0.213*U - 0.534*V + 77
	 *   B = 1.164*Y + 2.115*U - 289
	 */
	अणु
		0x04, 0xa7, 0x00, 0x00, 0x07, 0x2c, 0x02, 0xf8,
		0x04, 0xa7, 0x10, 0xda, 0x12, 0x22, 0x00, 0x4d,
		0x04, 0xa7, 0x08, 0x74, 0x00, 0x00, 0x03, 0x21
	पूर्ण,

	/*
	 * RGB2YUV:601 SD mode:
	 *   Cb = -0.291G - 0.148R + 0.439B + 128
	 *   Y  = 0.504G  + 0.257R + 0.098B + 16
	 *   Cr = -0.368G + 0.439R - 0.071B + 128
	 */
	अणु
		0x11, 0x5f, 0x01, 0x82, 0x10, 0x23, 0x00, 0x80,
		0x02, 0x1c, 0x00, 0xa1, 0x00, 0x36, 0x00, 0x1e,
		0x11, 0x29, 0x10, 0x59, 0x01, 0x82, 0x00, 0x80
	पूर्ण,
	/*
	 * RGB2YUV:709 HD mode:
	 *   Cb = - 0.338G - 0.101R + 0.439B + 128
	 *   Y  = 0.614G   + 0.183R + 0.062B + 16
	 *   Cr = - 0.399G + 0.439R - 0.040B + 128
	 */
	अणु
		0x11, 0x98, 0x01, 0xc1, 0x10, 0x28, 0x00, 0x80,
		0x02, 0x74, 0x00, 0xbb, 0x00, 0x3f, 0x00, 0x10,
		0x11, 0x5a, 0x10, 0x67, 0x01, 0xc1, 0x00, 0x80
	पूर्ण,
	/*
	 * RGB[0:255]2RGB[16:235]:
	 *   R' = R x (235-16)/255 + 16;
	 *   G' = G x (235-16)/255 + 16;
	 *   B' = B x (235-16)/255 + 16;
	 */
	अणु
		0x00, 0x00, 0x03, 0x6F, 0x00, 0x00, 0x00, 0x10,
		0x03, 0x6F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10,
		0x00, 0x00, 0x00, 0x00, 0x03, 0x6F, 0x00, 0x10
	पूर्ण,
पूर्ण;

अटल अंतरभूत u8 hdmi_पढ़ोb(काष्ठा inno_hdmi *hdmi, u16 offset)
अणु
	वापस पढ़ोl_relaxed(hdmi->regs + (offset) * 0x04);
पूर्ण

अटल अंतरभूत व्योम hdmi_ग_लिखोb(काष्ठा inno_hdmi *hdmi, u16 offset, u32 val)
अणु
	ग_लिखोl_relaxed(val, hdmi->regs + (offset) * 0x04);
पूर्ण

अटल अंतरभूत व्योम hdmi_modb(काष्ठा inno_hdmi *hdmi, u16 offset,
			     u32 msk, u32 val)
अणु
	u8 temp = hdmi_पढ़ोb(hdmi, offset) & ~msk;

	temp |= val & msk;
	hdmi_ग_लिखोb(hdmi, offset, temp);
पूर्ण

अटल व्योम inno_hdmi_i2c_init(काष्ठा inno_hdmi *hdmi)
अणु
	पूर्णांक ddc_bus_freq;

	ddc_bus_freq = (hdmi->पंचांगds_rate >> 2) / HDMI_SCL_RATE;

	hdmi_ग_लिखोb(hdmi, DDC_BUS_FREQ_L, ddc_bus_freq & 0xFF);
	hdmi_ग_लिखोb(hdmi, DDC_BUS_FREQ_H, (ddc_bus_freq >> 8) & 0xFF);

	/* Clear the EDID पूर्णांकerrupt flag and mute the पूर्णांकerrupt */
	hdmi_ग_लिखोb(hdmi, HDMI_INTERRUPT_MASK1, 0);
	hdmi_ग_लिखोb(hdmi, HDMI_INTERRUPT_STATUS1, m_INT_EDID_READY);
पूर्ण

अटल व्योम inno_hdmi_sys_घातer(काष्ठा inno_hdmi *hdmi, bool enable)
अणु
	अगर (enable)
		hdmi_modb(hdmi, HDMI_SYS_CTRL, m_POWER, v_PWR_ON);
	अन्यथा
		hdmi_modb(hdmi, HDMI_SYS_CTRL, m_POWER, v_PWR_OFF);
पूर्ण

अटल व्योम inno_hdmi_set_pwr_mode(काष्ठा inno_hdmi *hdmi, पूर्णांक mode)
अणु
	चयन (mode) अणु
	हाल NORMAL:
		inno_hdmi_sys_घातer(hdmi, false);

		hdmi_ग_लिखोb(hdmi, HDMI_PHY_PRE_EMPHASIS, 0x6f);
		hdmi_ग_लिखोb(hdmi, HDMI_PHY_DRIVER, 0xbb);

		hdmi_ग_लिखोb(hdmi, HDMI_PHY_SYS_CTL, 0x15);
		hdmi_ग_लिखोb(hdmi, HDMI_PHY_SYS_CTL, 0x14);
		hdmi_ग_लिखोb(hdmi, HDMI_PHY_SYS_CTL, 0x10);
		hdmi_ग_लिखोb(hdmi, HDMI_PHY_CHG_PWR, 0x0f);
		hdmi_ग_लिखोb(hdmi, HDMI_PHY_SYNC, 0x00);
		hdmi_ग_लिखोb(hdmi, HDMI_PHY_SYNC, 0x01);

		inno_hdmi_sys_घातer(hdmi, true);
		अवरोध;

	हाल LOWER_PWR:
		inno_hdmi_sys_घातer(hdmi, false);
		hdmi_ग_लिखोb(hdmi, HDMI_PHY_DRIVER, 0x00);
		hdmi_ग_लिखोb(hdmi, HDMI_PHY_PRE_EMPHASIS, 0x00);
		hdmi_ग_लिखोb(hdmi, HDMI_PHY_CHG_PWR, 0x00);
		hdmi_ग_लिखोb(hdmi, HDMI_PHY_SYS_CTL, 0x15);

		अवरोध;

	शेष:
		DRM_DEV_ERROR(hdmi->dev, "Unknown power mode %d\n", mode);
	पूर्ण
पूर्ण

अटल व्योम inno_hdmi_reset(काष्ठा inno_hdmi *hdmi)
अणु
	u32 val;
	u32 msk;

	hdmi_modb(hdmi, HDMI_SYS_CTRL, m_RST_DIGITAL, v_NOT_RST_DIGITAL);
	udelay(100);

	hdmi_modb(hdmi, HDMI_SYS_CTRL, m_RST_ANALOG, v_NOT_RST_ANALOG);
	udelay(100);

	msk = m_REG_CLK_INV | m_REG_CLK_SOURCE | m_POWER | m_INT_POL;
	val = v_REG_CLK_INV | v_REG_CLK_SOURCE_SYS | v_PWR_ON | v_INT_POL_HIGH;
	hdmi_modb(hdmi, HDMI_SYS_CTRL, msk, val);

	inno_hdmi_set_pwr_mode(hdmi, NORMAL);
पूर्ण

अटल पूर्णांक inno_hdmi_upload_frame(काष्ठा inno_hdmi *hdmi, पूर्णांक setup_rc,
				  जोड़ hdmi_infoframe *frame, u32 frame_index,
				  u32 mask, u32 disable, u32 enable)
अणु
	अगर (mask)
		hdmi_modb(hdmi, HDMI_PACKET_SEND_AUTO, mask, disable);

	hdmi_ग_लिखोb(hdmi, HDMI_CONTROL_PACKET_BUF_INDEX, frame_index);

	अगर (setup_rc >= 0) अणु
		u8 packed_frame[HDMI_MAXIMUM_INFO_FRAME_SIZE];
		sमाप_प्रकार rc, i;

		rc = hdmi_infoframe_pack(frame, packed_frame,
					 माप(packed_frame));
		अगर (rc < 0)
			वापस rc;

		क्रम (i = 0; i < rc; i++)
			hdmi_ग_लिखोb(hdmi, HDMI_CONTROL_PACKET_ADDR + i,
				    packed_frame[i]);

		अगर (mask)
			hdmi_modb(hdmi, HDMI_PACKET_SEND_AUTO, mask, enable);
	पूर्ण

	वापस setup_rc;
पूर्ण

अटल पूर्णांक inno_hdmi_config_video_vsi(काष्ठा inno_hdmi *hdmi,
				      काष्ठा drm_display_mode *mode)
अणु
	जोड़ hdmi_infoframe frame;
	पूर्णांक rc;

	rc = drm_hdmi_venकरोr_infoframe_from_display_mode(&frame.venकरोr.hdmi,
							 &hdmi->connector,
							 mode);

	वापस inno_hdmi_upload_frame(hdmi, rc, &frame, INFOFRAME_VSI,
		m_PACKET_VSI_EN, v_PACKET_VSI_EN(0), v_PACKET_VSI_EN(1));
पूर्ण

अटल पूर्णांक inno_hdmi_config_video_avi(काष्ठा inno_hdmi *hdmi,
				      काष्ठा drm_display_mode *mode)
अणु
	जोड़ hdmi_infoframe frame;
	पूर्णांक rc;

	rc = drm_hdmi_avi_infoframe_from_display_mode(&frame.avi,
						      &hdmi->connector,
						      mode);

	अगर (hdmi->hdmi_data.enc_out_क्रमmat == HDMI_COLORSPACE_YUV444)
		frame.avi.colorspace = HDMI_COLORSPACE_YUV444;
	अन्यथा अगर (hdmi->hdmi_data.enc_out_क्रमmat == HDMI_COLORSPACE_YUV422)
		frame.avi.colorspace = HDMI_COLORSPACE_YUV422;
	अन्यथा
		frame.avi.colorspace = HDMI_COLORSPACE_RGB;

	वापस inno_hdmi_upload_frame(hdmi, rc, &frame, INFOFRAME_AVI, 0, 0, 0);
पूर्ण

अटल पूर्णांक inno_hdmi_config_video_csc(काष्ठा inno_hdmi *hdmi)
अणु
	काष्ठा hdmi_data_info *data = &hdmi->hdmi_data;
	पूर्णांक c0_c2_change = 0;
	पूर्णांक csc_enable = 0;
	पूर्णांक csc_mode = 0;
	पूर्णांक स्वतः_csc = 0;
	पूर्णांक value;
	पूर्णांक i;

	/* Input video mode is SDR RGB24bit, data enable संकेत from बाह्यal */
	hdmi_ग_लिखोb(hdmi, HDMI_VIDEO_CONTRL1, v_DE_EXTERNAL |
		    v_VIDEO_INPUT_FORMAT(VIDEO_INPUT_SDR_RGB444));

	/* Input color hardcode to RGB, and output color hardcode to RGB888 */
	value = v_VIDEO_INPUT_BITS(VIDEO_INPUT_8BITS) |
		v_VIDEO_OUTPUT_COLOR(0) |
		v_VIDEO_INPUT_CSP(0);
	hdmi_ग_लिखोb(hdmi, HDMI_VIDEO_CONTRL2, value);

	अगर (data->enc_in_क्रमmat == data->enc_out_क्रमmat) अणु
		अगर ((data->enc_in_क्रमmat == HDMI_COLORSPACE_RGB) ||
		    (data->enc_in_क्रमmat >= HDMI_COLORSPACE_YUV444)) अणु
			value = v_SOF_DISABLE | v_COLOR_DEPTH_NOT_INDICATED(1);
			hdmi_ग_लिखोb(hdmi, HDMI_VIDEO_CONTRL3, value);

			hdmi_modb(hdmi, HDMI_VIDEO_CONTRL,
				  m_VIDEO_AUTO_CSC | m_VIDEO_C0_C2_SWAP,
				  v_VIDEO_AUTO_CSC(AUTO_CSC_DISABLE) |
				  v_VIDEO_C0_C2_SWAP(C0_C2_CHANGE_DISABLE));
			वापस 0;
		पूर्ण
	पूर्ण

	अगर (data->colorimetry == HDMI_COLORIMETRY_ITU_601) अणु
		अगर ((data->enc_in_क्रमmat == HDMI_COLORSPACE_RGB) &&
		    (data->enc_out_क्रमmat == HDMI_COLORSPACE_YUV444)) अणु
			csc_mode = CSC_RGB_0_255_TO_ITU601_16_235_8BIT;
			स्वतः_csc = AUTO_CSC_DISABLE;
			c0_c2_change = C0_C2_CHANGE_DISABLE;
			csc_enable = v_CSC_ENABLE;
		पूर्ण अन्यथा अगर ((data->enc_in_क्रमmat == HDMI_COLORSPACE_YUV444) &&
			   (data->enc_out_क्रमmat == HDMI_COLORSPACE_RGB)) अणु
			csc_mode = CSC_ITU601_16_235_TO_RGB_0_255_8BIT;
			स्वतः_csc = AUTO_CSC_ENABLE;
			c0_c2_change = C0_C2_CHANGE_DISABLE;
			csc_enable = v_CSC_DISABLE;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर ((data->enc_in_क्रमmat == HDMI_COLORSPACE_RGB) &&
		    (data->enc_out_क्रमmat == HDMI_COLORSPACE_YUV444)) अणु
			csc_mode = CSC_RGB_0_255_TO_ITU709_16_235_8BIT;
			स्वतः_csc = AUTO_CSC_DISABLE;
			c0_c2_change = C0_C2_CHANGE_DISABLE;
			csc_enable = v_CSC_ENABLE;
		पूर्ण अन्यथा अगर ((data->enc_in_क्रमmat == HDMI_COLORSPACE_YUV444) &&
			   (data->enc_out_क्रमmat == HDMI_COLORSPACE_RGB)) अणु
			csc_mode = CSC_ITU709_16_235_TO_RGB_0_255_8BIT;
			स्वतः_csc = AUTO_CSC_ENABLE;
			c0_c2_change = C0_C2_CHANGE_DISABLE;
			csc_enable = v_CSC_DISABLE;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < 24; i++)
		hdmi_ग_लिखोb(hdmi, HDMI_VIDEO_CSC_COEF + i,
			    coeff_csc[csc_mode][i]);

	value = v_SOF_DISABLE | csc_enable | v_COLOR_DEPTH_NOT_INDICATED(1);
	hdmi_ग_लिखोb(hdmi, HDMI_VIDEO_CONTRL3, value);
	hdmi_modb(hdmi, HDMI_VIDEO_CONTRL, m_VIDEO_AUTO_CSC |
		  m_VIDEO_C0_C2_SWAP, v_VIDEO_AUTO_CSC(स्वतः_csc) |
		  v_VIDEO_C0_C2_SWAP(c0_c2_change));

	वापस 0;
पूर्ण

अटल पूर्णांक inno_hdmi_config_video_timing(काष्ठा inno_hdmi *hdmi,
					 काष्ठा drm_display_mode *mode)
अणु
	पूर्णांक value;

	/* Set detail बाह्यal video timing polarity and पूर्णांकerlace mode */
	value = v_EXTERANL_VIDEO(1);
	value |= mode->flags & DRM_MODE_FLAG_PHSYNC ?
		 v_HSYNC_POLARITY(1) : v_HSYNC_POLARITY(0);
	value |= mode->flags & DRM_MODE_FLAG_PVSYNC ?
		 v_VSYNC_POLARITY(1) : v_VSYNC_POLARITY(0);
	value |= mode->flags & DRM_MODE_FLAG_INTERLACE ?
		 v_INETLACE(1) : v_INETLACE(0);
	hdmi_ग_लिखोb(hdmi, HDMI_VIDEO_TIMING_CTL, value);

	/* Set detail बाह्यal video timing */
	value = mode->htotal;
	hdmi_ग_लिखोb(hdmi, HDMI_VIDEO_EXT_HTOTAL_L, value & 0xFF);
	hdmi_ग_लिखोb(hdmi, HDMI_VIDEO_EXT_HTOTAL_H, (value >> 8) & 0xFF);

	value = mode->htotal - mode->hdisplay;
	hdmi_ग_लिखोb(hdmi, HDMI_VIDEO_EXT_HBLANK_L, value & 0xFF);
	hdmi_ग_लिखोb(hdmi, HDMI_VIDEO_EXT_HBLANK_H, (value >> 8) & 0xFF);

	value = mode->hsync_start - mode->hdisplay;
	hdmi_ग_लिखोb(hdmi, HDMI_VIDEO_EXT_HDELAY_L, value & 0xFF);
	hdmi_ग_लिखोb(hdmi, HDMI_VIDEO_EXT_HDELAY_H, (value >> 8) & 0xFF);

	value = mode->hsync_end - mode->hsync_start;
	hdmi_ग_लिखोb(hdmi, HDMI_VIDEO_EXT_HDURATION_L, value & 0xFF);
	hdmi_ग_लिखोb(hdmi, HDMI_VIDEO_EXT_HDURATION_H, (value >> 8) & 0xFF);

	value = mode->vtotal;
	hdmi_ग_लिखोb(hdmi, HDMI_VIDEO_EXT_VTOTAL_L, value & 0xFF);
	hdmi_ग_लिखोb(hdmi, HDMI_VIDEO_EXT_VTOTAL_H, (value >> 8) & 0xFF);

	value = mode->vtotal - mode->vdisplay;
	hdmi_ग_लिखोb(hdmi, HDMI_VIDEO_EXT_VBLANK, value & 0xFF);

	value = mode->vsync_start - mode->vdisplay;
	hdmi_ग_लिखोb(hdmi, HDMI_VIDEO_EXT_VDELAY, value & 0xFF);

	value = mode->vsync_end - mode->vsync_start;
	hdmi_ग_लिखोb(hdmi, HDMI_VIDEO_EXT_VDURATION, value & 0xFF);

	hdmi_ग_लिखोb(hdmi, HDMI_PHY_PRE_DIV_RATIO, 0x1e);
	hdmi_ग_लिखोb(hdmi, HDMI_PHY_FEEDBACK_DIV_RATIO_LOW, 0x2c);
	hdmi_ग_लिखोb(hdmi, HDMI_PHY_FEEDBACK_DIV_RATIO_HIGH, 0x01);

	वापस 0;
पूर्ण

अटल पूर्णांक inno_hdmi_setup(काष्ठा inno_hdmi *hdmi,
			   काष्ठा drm_display_mode *mode)
अणु
	hdmi->hdmi_data.vic = drm_match_cea_mode(mode);

	hdmi->hdmi_data.enc_in_क्रमmat = HDMI_COLORSPACE_RGB;
	hdmi->hdmi_data.enc_out_क्रमmat = HDMI_COLORSPACE_RGB;

	अगर ((hdmi->hdmi_data.vic == 6) || (hdmi->hdmi_data.vic == 7) ||
	    (hdmi->hdmi_data.vic == 21) || (hdmi->hdmi_data.vic == 22) ||
	    (hdmi->hdmi_data.vic == 2) || (hdmi->hdmi_data.vic == 3) ||
	    (hdmi->hdmi_data.vic == 17) || (hdmi->hdmi_data.vic == 18))
		hdmi->hdmi_data.colorimetry = HDMI_COLORIMETRY_ITU_601;
	अन्यथा
		hdmi->hdmi_data.colorimetry = HDMI_COLORIMETRY_ITU_709;

	/* Mute video and audio output */
	hdmi_modb(hdmi, HDMI_AV_MUTE, m_AUDIO_MUTE | m_VIDEO_BLACK,
		  v_AUDIO_MUTE(1) | v_VIDEO_MUTE(1));

	/* Set HDMI Mode */
	hdmi_ग_लिखोb(hdmi, HDMI_HDCP_CTRL,
		    v_HDMI_DVI(hdmi->hdmi_data.sink_is_hdmi));

	inno_hdmi_config_video_timing(hdmi, mode);

	inno_hdmi_config_video_csc(hdmi);

	अगर (hdmi->hdmi_data.sink_is_hdmi) अणु
		inno_hdmi_config_video_avi(hdmi, mode);
		inno_hdmi_config_video_vsi(hdmi, mode);
	पूर्ण

	/*
	 * When IP controller have configured to an accurate video
	 * timing, then the TMDS घड़ी source would be चयनed to
	 * DCLK_LCDC, so we need to init the TMDS rate to mode pixel
	 * घड़ी rate, and reconfigure the DDC घड़ी.
	 */
	hdmi->पंचांगds_rate = mode->घड़ी * 1000;
	inno_hdmi_i2c_init(hdmi);

	/* Unmute video and audio output */
	hdmi_modb(hdmi, HDMI_AV_MUTE, m_AUDIO_MUTE | m_VIDEO_BLACK,
		  v_AUDIO_MUTE(0) | v_VIDEO_MUTE(0));

	वापस 0;
पूर्ण

अटल व्योम inno_hdmi_encoder_mode_set(काष्ठा drm_encoder *encoder,
				       काष्ठा drm_display_mode *mode,
				       काष्ठा drm_display_mode *adj_mode)
अणु
	काष्ठा inno_hdmi *hdmi = to_inno_hdmi(encoder);

	inno_hdmi_setup(hdmi, adj_mode);

	/* Store the display mode क्रम plugin/DPMS घातeron events */
	स_नकल(&hdmi->previous_mode, adj_mode, माप(hdmi->previous_mode));
पूर्ण

अटल व्योम inno_hdmi_encoder_enable(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा inno_hdmi *hdmi = to_inno_hdmi(encoder);

	inno_hdmi_set_pwr_mode(hdmi, NORMAL);
पूर्ण

अटल व्योम inno_hdmi_encoder_disable(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा inno_hdmi *hdmi = to_inno_hdmi(encoder);

	inno_hdmi_set_pwr_mode(hdmi, LOWER_PWR);
पूर्ण

अटल bool inno_hdmi_encoder_mode_fixup(काष्ठा drm_encoder *encoder,
					 स्थिर काष्ठा drm_display_mode *mode,
					 काष्ठा drm_display_mode *adj_mode)
अणु
	वापस true;
पूर्ण

अटल पूर्णांक
inno_hdmi_encoder_atomic_check(काष्ठा drm_encoder *encoder,
			       काष्ठा drm_crtc_state *crtc_state,
			       काष्ठा drm_connector_state *conn_state)
अणु
	काष्ठा rockchip_crtc_state *s = to_rockchip_crtc_state(crtc_state);

	s->output_mode = ROCKCHIP_OUT_MODE_P888;
	s->output_type = DRM_MODE_CONNECTOR_HDMIA;

	वापस 0;
पूर्ण

अटल काष्ठा drm_encoder_helper_funcs inno_hdmi_encoder_helper_funcs = अणु
	.enable     = inno_hdmi_encoder_enable,
	.disable    = inno_hdmi_encoder_disable,
	.mode_fixup = inno_hdmi_encoder_mode_fixup,
	.mode_set   = inno_hdmi_encoder_mode_set,
	.atomic_check = inno_hdmi_encoder_atomic_check,
पूर्ण;

अटल क्रमागत drm_connector_status
inno_hdmi_connector_detect(काष्ठा drm_connector *connector, bool क्रमce)
अणु
	काष्ठा inno_hdmi *hdmi = to_inno_hdmi(connector);

	वापस (hdmi_पढ़ोb(hdmi, HDMI_STATUS) & m_HOTPLUG) ?
		connector_status_connected : connector_status_disconnected;
पूर्ण

अटल पूर्णांक inno_hdmi_connector_get_modes(काष्ठा drm_connector *connector)
अणु
	काष्ठा inno_hdmi *hdmi = to_inno_hdmi(connector);
	काष्ठा edid *edid;
	पूर्णांक ret = 0;

	अगर (!hdmi->ddc)
		वापस 0;

	edid = drm_get_edid(connector, hdmi->ddc);
	अगर (edid) अणु
		hdmi->hdmi_data.sink_is_hdmi = drm_detect_hdmi_monitor(edid);
		hdmi->hdmi_data.sink_has_audio = drm_detect_monitor_audio(edid);
		drm_connector_update_edid_property(connector, edid);
		ret = drm_add_edid_modes(connector, edid);
		kमुक्त(edid);
	पूर्ण

	वापस ret;
पूर्ण

अटल क्रमागत drm_mode_status
inno_hdmi_connector_mode_valid(काष्ठा drm_connector *connector,
			       काष्ठा drm_display_mode *mode)
अणु
	वापस MODE_OK;
पूर्ण

अटल पूर्णांक
inno_hdmi_probe_single_connector_modes(काष्ठा drm_connector *connector,
				       uपूर्णांक32_t maxX, uपूर्णांक32_t maxY)
अणु
	वापस drm_helper_probe_single_connector_modes(connector, 1920, 1080);
पूर्ण

अटल व्योम inno_hdmi_connector_destroy(काष्ठा drm_connector *connector)
अणु
	drm_connector_unरेजिस्टर(connector);
	drm_connector_cleanup(connector);
पूर्ण

अटल स्थिर काष्ठा drm_connector_funcs inno_hdmi_connector_funcs = अणु
	.fill_modes = inno_hdmi_probe_single_connector_modes,
	.detect = inno_hdmi_connector_detect,
	.destroy = inno_hdmi_connector_destroy,
	.reset = drm_atomic_helper_connector_reset,
	.atomic_duplicate_state = drm_atomic_helper_connector_duplicate_state,
	.atomic_destroy_state = drm_atomic_helper_connector_destroy_state,
पूर्ण;

अटल काष्ठा drm_connector_helper_funcs inno_hdmi_connector_helper_funcs = अणु
	.get_modes = inno_hdmi_connector_get_modes,
	.mode_valid = inno_hdmi_connector_mode_valid,
पूर्ण;

अटल पूर्णांक inno_hdmi_रेजिस्टर(काष्ठा drm_device *drm, काष्ठा inno_hdmi *hdmi)
अणु
	काष्ठा drm_encoder *encoder = &hdmi->encoder;
	काष्ठा device *dev = hdmi->dev;

	encoder->possible_crtcs = drm_of_find_possible_crtcs(drm, dev->of_node);

	/*
	 * If we failed to find the CRTC(s) which this encoder is
	 * supposed to be connected to, it's because the CRTC has
	 * not been रेजिस्टरed yet.  Defer probing, and hope that
	 * the required CRTC is added later.
	 */
	अगर (encoder->possible_crtcs == 0)
		वापस -EPROBE_DEFER;

	drm_encoder_helper_add(encoder, &inno_hdmi_encoder_helper_funcs);
	drm_simple_encoder_init(drm, encoder, DRM_MODE_ENCODER_TMDS);

	hdmi->connector.polled = DRM_CONNECTOR_POLL_HPD;

	drm_connector_helper_add(&hdmi->connector,
				 &inno_hdmi_connector_helper_funcs);
	drm_connector_init_with_ddc(drm, &hdmi->connector,
				    &inno_hdmi_connector_funcs,
				    DRM_MODE_CONNECTOR_HDMIA,
				    hdmi->ddc);

	drm_connector_attach_encoder(&hdmi->connector, encoder);

	वापस 0;
पूर्ण

अटल irqवापस_t inno_hdmi_i2c_irq(काष्ठा inno_hdmi *hdmi)
अणु
	काष्ठा inno_hdmi_i2c *i2c = hdmi->i2c;
	u8 stat;

	stat = hdmi_पढ़ोb(hdmi, HDMI_INTERRUPT_STATUS1);
	अगर (!(stat & m_INT_EDID_READY))
		वापस IRQ_NONE;

	/* Clear HDMI EDID पूर्णांकerrupt flag */
	hdmi_ग_लिखोb(hdmi, HDMI_INTERRUPT_STATUS1, m_INT_EDID_READY);

	complete(&i2c->cmp);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t inno_hdmi_hardirq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा inno_hdmi *hdmi = dev_id;
	irqवापस_t ret = IRQ_NONE;
	u8 पूर्णांकerrupt;

	अगर (hdmi->i2c)
		ret = inno_hdmi_i2c_irq(hdmi);

	पूर्णांकerrupt = hdmi_पढ़ोb(hdmi, HDMI_STATUS);
	अगर (पूर्णांकerrupt & m_INT_HOTPLUG) अणु
		hdmi_modb(hdmi, HDMI_STATUS, m_INT_HOTPLUG, m_INT_HOTPLUG);
		ret = IRQ_WAKE_THREAD;
	पूर्ण

	वापस ret;
पूर्ण

अटल irqवापस_t inno_hdmi_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा inno_hdmi *hdmi = dev_id;

	drm_helper_hpd_irq_event(hdmi->connector.dev);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक inno_hdmi_i2c_पढ़ो(काष्ठा inno_hdmi *hdmi, काष्ठा i2c_msg *msgs)
अणु
	पूर्णांक length = msgs->len;
	u8 *buf = msgs->buf;
	पूर्णांक ret;

	ret = रुको_क्रम_completion_समयout(&hdmi->i2c->cmp, HZ / 10);
	अगर (!ret)
		वापस -EAGAIN;

	जबतक (length--)
		*buf++ = hdmi_पढ़ोb(hdmi, HDMI_EDID_FIFO_ADDR);

	वापस 0;
पूर्ण

अटल पूर्णांक inno_hdmi_i2c_ग_लिखो(काष्ठा inno_hdmi *hdmi, काष्ठा i2c_msg *msgs)
अणु
	/*
	 * The DDC module only support पढ़ो EDID message, so
	 * we assume that each word ग_लिखो to this i2c adapter
	 * should be the offset of EDID word address.
	 */
	अगर ((msgs->len != 1) ||
	    ((msgs->addr != DDC_ADDR) && (msgs->addr != DDC_SEGMENT_ADDR)))
		वापस -EINVAL;

	reinit_completion(&hdmi->i2c->cmp);

	अगर (msgs->addr == DDC_SEGMENT_ADDR)
		hdmi->i2c->segment_addr = msgs->buf[0];
	अगर (msgs->addr == DDC_ADDR)
		hdmi->i2c->ddc_addr = msgs->buf[0];

	/* Set edid fअगरo first addr */
	hdmi_ग_लिखोb(hdmi, HDMI_EDID_FIFO_OFFSET, 0x00);

	/* Set edid word address 0x00/0x80 */
	hdmi_ग_लिखोb(hdmi, HDMI_EDID_WORD_ADDR, hdmi->i2c->ddc_addr);

	/* Set edid segment poपूर्णांकer */
	hdmi_ग_लिखोb(hdmi, HDMI_EDID_SEGMENT_POINTER, hdmi->i2c->segment_addr);

	वापस 0;
पूर्ण

अटल पूर्णांक inno_hdmi_i2c_xfer(काष्ठा i2c_adapter *adap,
			      काष्ठा i2c_msg *msgs, पूर्णांक num)
अणु
	काष्ठा inno_hdmi *hdmi = i2c_get_adapdata(adap);
	काष्ठा inno_hdmi_i2c *i2c = hdmi->i2c;
	पूर्णांक i, ret = 0;

	mutex_lock(&i2c->lock);

	/* Clear the EDID पूर्णांकerrupt flag and unmute the पूर्णांकerrupt */
	hdmi_ग_लिखोb(hdmi, HDMI_INTERRUPT_MASK1, m_INT_EDID_READY);
	hdmi_ग_लिखोb(hdmi, HDMI_INTERRUPT_STATUS1, m_INT_EDID_READY);

	क्रम (i = 0; i < num; i++) अणु
		DRM_DEV_DEBUG(hdmi->dev,
			      "xfer: num: %d/%d, len: %d, flags: %#x\n",
			      i + 1, num, msgs[i].len, msgs[i].flags);

		अगर (msgs[i].flags & I2C_M_RD)
			ret = inno_hdmi_i2c_पढ़ो(hdmi, &msgs[i]);
		अन्यथा
			ret = inno_hdmi_i2c_ग_लिखो(hdmi, &msgs[i]);

		अगर (ret < 0)
			अवरोध;
	पूर्ण

	अगर (!ret)
		ret = num;

	/* Mute HDMI EDID पूर्णांकerrupt */
	hdmi_ग_लिखोb(hdmi, HDMI_INTERRUPT_MASK1, 0);

	mutex_unlock(&i2c->lock);

	वापस ret;
पूर्ण

अटल u32 inno_hdmi_i2c_func(काष्ठा i2c_adapter *adapter)
अणु
	वापस I2C_FUNC_I2C | I2C_FUNC_SMBUS_EMUL;
पूर्ण

अटल स्थिर काष्ठा i2c_algorithm inno_hdmi_algorithm = अणु
	.master_xfer	= inno_hdmi_i2c_xfer,
	.functionality	= inno_hdmi_i2c_func,
पूर्ण;

अटल काष्ठा i2c_adapter *inno_hdmi_i2c_adapter(काष्ठा inno_hdmi *hdmi)
अणु
	काष्ठा i2c_adapter *adap;
	काष्ठा inno_hdmi_i2c *i2c;
	पूर्णांक ret;

	i2c = devm_kzalloc(hdmi->dev, माप(*i2c), GFP_KERNEL);
	अगर (!i2c)
		वापस ERR_PTR(-ENOMEM);

	mutex_init(&i2c->lock);
	init_completion(&i2c->cmp);

	adap = &i2c->adap;
	adap->class = I2C_CLASS_DDC;
	adap->owner = THIS_MODULE;
	adap->dev.parent = hdmi->dev;
	adap->dev.of_node = hdmi->dev->of_node;
	adap->algo = &inno_hdmi_algorithm;
	strlcpy(adap->name, "Inno HDMI", माप(adap->name));
	i2c_set_adapdata(adap, hdmi);

	ret = i2c_add_adapter(adap);
	अगर (ret) अणु
		dev_warn(hdmi->dev, "cannot add %s I2C adapter\n", adap->name);
		devm_kमुक्त(hdmi->dev, i2c);
		वापस ERR_PTR(ret);
	पूर्ण

	hdmi->i2c = i2c;

	DRM_DEV_INFO(hdmi->dev, "registered %s I2C bus driver\n", adap->name);

	वापस adap;
पूर्ण

अटल पूर्णांक inno_hdmi_bind(काष्ठा device *dev, काष्ठा device *master,
				 व्योम *data)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा drm_device *drm = data;
	काष्ठा inno_hdmi *hdmi;
	काष्ठा resource *iores;
	पूर्णांक irq;
	पूर्णांक ret;

	hdmi = devm_kzalloc(dev, माप(*hdmi), GFP_KERNEL);
	अगर (!hdmi)
		वापस -ENOMEM;

	hdmi->dev = dev;
	hdmi->drm_dev = drm;

	iores = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	hdmi->regs = devm_ioremap_resource(dev, iores);
	अगर (IS_ERR(hdmi->regs))
		वापस PTR_ERR(hdmi->regs);

	hdmi->pclk = devm_clk_get(hdmi->dev, "pclk");
	अगर (IS_ERR(hdmi->pclk)) अणु
		DRM_DEV_ERROR(hdmi->dev, "Unable to get HDMI pclk clk\n");
		वापस PTR_ERR(hdmi->pclk);
	पूर्ण

	ret = clk_prepare_enable(hdmi->pclk);
	अगर (ret) अणु
		DRM_DEV_ERROR(hdmi->dev,
			      "Cannot enable HDMI pclk clock: %d\n", ret);
		वापस ret;
	पूर्ण

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0) अणु
		ret = irq;
		जाओ err_disable_clk;
	पूर्ण

	inno_hdmi_reset(hdmi);

	hdmi->ddc = inno_hdmi_i2c_adapter(hdmi);
	अगर (IS_ERR(hdmi->ddc)) अणु
		ret = PTR_ERR(hdmi->ddc);
		hdmi->ddc = शून्य;
		जाओ err_disable_clk;
	पूर्ण

	/*
	 * When IP controller haven't configured to an accurate video
	 * timing, then the TMDS घड़ी source would be चयनed to
	 * PCLK_HDMI, so we need to init the TMDS rate to PCLK rate,
	 * and reconfigure the DDC घड़ी.
	 */
	hdmi->पंचांगds_rate = clk_get_rate(hdmi->pclk);
	inno_hdmi_i2c_init(hdmi);

	ret = inno_hdmi_रेजिस्टर(drm, hdmi);
	अगर (ret)
		जाओ err_put_adapter;

	dev_set_drvdata(dev, hdmi);

	/* Unmute hotplug पूर्णांकerrupt */
	hdmi_modb(hdmi, HDMI_STATUS, m_MASK_INT_HOTPLUG, v_MASK_INT_HOTPLUG(1));

	ret = devm_request_thपढ़ोed_irq(dev, irq, inno_hdmi_hardirq,
					inno_hdmi_irq, IRQF_SHARED,
					dev_name(dev), hdmi);
	अगर (ret < 0)
		जाओ err_cleanup_hdmi;

	वापस 0;
err_cleanup_hdmi:
	hdmi->connector.funcs->destroy(&hdmi->connector);
	hdmi->encoder.funcs->destroy(&hdmi->encoder);
err_put_adapter:
	i2c_put_adapter(hdmi->ddc);
err_disable_clk:
	clk_disable_unprepare(hdmi->pclk);
	वापस ret;
पूर्ण

अटल व्योम inno_hdmi_unbind(काष्ठा device *dev, काष्ठा device *master,
			     व्योम *data)
अणु
	काष्ठा inno_hdmi *hdmi = dev_get_drvdata(dev);

	hdmi->connector.funcs->destroy(&hdmi->connector);
	hdmi->encoder.funcs->destroy(&hdmi->encoder);

	i2c_put_adapter(hdmi->ddc);
	clk_disable_unprepare(hdmi->pclk);
पूर्ण

अटल स्थिर काष्ठा component_ops inno_hdmi_ops = अणु
	.bind	= inno_hdmi_bind,
	.unbind	= inno_hdmi_unbind,
पूर्ण;

अटल पूर्णांक inno_hdmi_probe(काष्ठा platक्रमm_device *pdev)
अणु
	वापस component_add(&pdev->dev, &inno_hdmi_ops);
पूर्ण

अटल पूर्णांक inno_hdmi_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	component_del(&pdev->dev, &inno_hdmi_ops);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id inno_hdmi_dt_ids[] = अणु
	अणु .compatible = "rockchip,rk3036-inno-hdmi",
	पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, inno_hdmi_dt_ids);

काष्ठा platक्रमm_driver inno_hdmi_driver = अणु
	.probe  = inno_hdmi_probe,
	.हटाओ = inno_hdmi_हटाओ,
	.driver = अणु
		.name = "innohdmi-rockchip",
		.of_match_table = inno_hdmi_dt_ids,
	पूर्ण,
पूर्ण;
