<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2014 MediaTek Inc.
 * Author: Jie Qiu <jie.qiu@mediatek.com>
 */

#समावेश <linux/arm-smccc.h>
#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/hdmi.h>
#समावेश <linux/i2c.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/of.h>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/of_graph.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>

#समावेश <sound/hdmi-codec.h>

#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_bridge.h>
#समावेश <drm/drm_crtc.h>
#समावेश <drm/drm_edid.h>
#समावेश <drm/drm_prपूर्णांक.h>
#समावेश <drm/drm_probe_helper.h>

#समावेश "mtk_cec.h"
#समावेश "mtk_hdmi.h"
#समावेश "mtk_hdmi_regs.h"

#घोषणा NCTS_BYTES	7

क्रमागत mtk_hdmi_clk_id अणु
	MTK_HDMI_CLK_HDMI_PIXEL,
	MTK_HDMI_CLK_HDMI_PLL,
	MTK_HDMI_CLK_AUD_BCLK,
	MTK_HDMI_CLK_AUD_SPDIF,
	MTK_HDMI_CLK_COUNT
पूर्ण;

क्रमागत hdmi_aud_input_type अणु
	HDMI_AUD_INPUT_I2S = 0,
	HDMI_AUD_INPUT_SPDIF,
पूर्ण;

क्रमागत hdmi_aud_i2s_fmt अणु
	HDMI_I2S_MODE_RJT_24BIT = 0,
	HDMI_I2S_MODE_RJT_16BIT,
	HDMI_I2S_MODE_LJT_24BIT,
	HDMI_I2S_MODE_LJT_16BIT,
	HDMI_I2S_MODE_I2S_24BIT,
	HDMI_I2S_MODE_I2S_16BIT
पूर्ण;

क्रमागत hdmi_aud_mclk अणु
	HDMI_AUD_MCLK_128FS,
	HDMI_AUD_MCLK_192FS,
	HDMI_AUD_MCLK_256FS,
	HDMI_AUD_MCLK_384FS,
	HDMI_AUD_MCLK_512FS,
	HDMI_AUD_MCLK_768FS,
	HDMI_AUD_MCLK_1152FS,
पूर्ण;

क्रमागत hdmi_aud_channel_type अणु
	HDMI_AUD_CHAN_TYPE_1_0 = 0,
	HDMI_AUD_CHAN_TYPE_1_1,
	HDMI_AUD_CHAN_TYPE_2_0,
	HDMI_AUD_CHAN_TYPE_2_1,
	HDMI_AUD_CHAN_TYPE_3_0,
	HDMI_AUD_CHAN_TYPE_3_1,
	HDMI_AUD_CHAN_TYPE_4_0,
	HDMI_AUD_CHAN_TYPE_4_1,
	HDMI_AUD_CHAN_TYPE_5_0,
	HDMI_AUD_CHAN_TYPE_5_1,
	HDMI_AUD_CHAN_TYPE_6_0,
	HDMI_AUD_CHAN_TYPE_6_1,
	HDMI_AUD_CHAN_TYPE_7_0,
	HDMI_AUD_CHAN_TYPE_7_1,
	HDMI_AUD_CHAN_TYPE_3_0_LRS,
	HDMI_AUD_CHAN_TYPE_3_1_LRS,
	HDMI_AUD_CHAN_TYPE_4_0_CLRS,
	HDMI_AUD_CHAN_TYPE_4_1_CLRS,
	HDMI_AUD_CHAN_TYPE_6_1_CS,
	HDMI_AUD_CHAN_TYPE_6_1_CH,
	HDMI_AUD_CHAN_TYPE_6_1_OH,
	HDMI_AUD_CHAN_TYPE_6_1_CHR,
	HDMI_AUD_CHAN_TYPE_7_1_LH_RH,
	HDMI_AUD_CHAN_TYPE_7_1_LSR_RSR,
	HDMI_AUD_CHAN_TYPE_7_1_LC_RC,
	HDMI_AUD_CHAN_TYPE_7_1_LW_RW,
	HDMI_AUD_CHAN_TYPE_7_1_LSD_RSD,
	HDMI_AUD_CHAN_TYPE_7_1_LSS_RSS,
	HDMI_AUD_CHAN_TYPE_7_1_LHS_RHS,
	HDMI_AUD_CHAN_TYPE_7_1_CS_CH,
	HDMI_AUD_CHAN_TYPE_7_1_CS_OH,
	HDMI_AUD_CHAN_TYPE_7_1_CS_CHR,
	HDMI_AUD_CHAN_TYPE_7_1_CH_OH,
	HDMI_AUD_CHAN_TYPE_7_1_CH_CHR,
	HDMI_AUD_CHAN_TYPE_7_1_OH_CHR,
	HDMI_AUD_CHAN_TYPE_7_1_LSS_RSS_LSR_RSR,
	HDMI_AUD_CHAN_TYPE_6_0_CS,
	HDMI_AUD_CHAN_TYPE_6_0_CH,
	HDMI_AUD_CHAN_TYPE_6_0_OH,
	HDMI_AUD_CHAN_TYPE_6_0_CHR,
	HDMI_AUD_CHAN_TYPE_7_0_LH_RH,
	HDMI_AUD_CHAN_TYPE_7_0_LSR_RSR,
	HDMI_AUD_CHAN_TYPE_7_0_LC_RC,
	HDMI_AUD_CHAN_TYPE_7_0_LW_RW,
	HDMI_AUD_CHAN_TYPE_7_0_LSD_RSD,
	HDMI_AUD_CHAN_TYPE_7_0_LSS_RSS,
	HDMI_AUD_CHAN_TYPE_7_0_LHS_RHS,
	HDMI_AUD_CHAN_TYPE_7_0_CS_CH,
	HDMI_AUD_CHAN_TYPE_7_0_CS_OH,
	HDMI_AUD_CHAN_TYPE_7_0_CS_CHR,
	HDMI_AUD_CHAN_TYPE_7_0_CH_OH,
	HDMI_AUD_CHAN_TYPE_7_0_CH_CHR,
	HDMI_AUD_CHAN_TYPE_7_0_OH_CHR,
	HDMI_AUD_CHAN_TYPE_7_0_LSS_RSS_LSR_RSR,
	HDMI_AUD_CHAN_TYPE_8_0_LH_RH_CS,
	HDMI_AUD_CHAN_TYPE_UNKNOWN = 0xFF
पूर्ण;

क्रमागत hdmi_aud_channel_swap_type अणु
	HDMI_AUD_SWAP_LR,
	HDMI_AUD_SWAP_LFE_CC,
	HDMI_AUD_SWAP_LSRS,
	HDMI_AUD_SWAP_RLS_RRS,
	HDMI_AUD_SWAP_LR_STATUS,
पूर्ण;

काष्ठा hdmi_audio_param अणु
	क्रमागत hdmi_audio_coding_type aud_codec;
	क्रमागत hdmi_audio_sample_size aud_sampe_size;
	क्रमागत hdmi_aud_input_type aud_input_type;
	क्रमागत hdmi_aud_i2s_fmt aud_i2s_fmt;
	क्रमागत hdmi_aud_mclk aud_mclk;
	क्रमागत hdmi_aud_channel_type aud_input_chan_type;
	काष्ठा hdmi_codec_params codec_params;
पूर्ण;

काष्ठा mtk_hdmi_conf अणु
	bool tz_disabled;
पूर्ण;

काष्ठा mtk_hdmi अणु
	काष्ठा drm_bridge bridge;
	काष्ठा drm_bridge *next_bridge;
	काष्ठा drm_connector *curr_conn;/* current connector (only valid when 'enabled') */
	काष्ठा device *dev;
	स्थिर काष्ठा mtk_hdmi_conf *conf;
	काष्ठा phy *phy;
	काष्ठा device *cec_dev;
	काष्ठा i2c_adapter *ddc_adpt;
	काष्ठा clk *clk[MTK_HDMI_CLK_COUNT];
	काष्ठा drm_display_mode mode;
	bool dvi_mode;
	u32 min_घड़ी;
	u32 max_घड़ी;
	u32 max_hdisplay;
	u32 max_vdisplay;
	u32 ibias;
	u32 ibias_up;
	काष्ठा regmap *sys_regmap;
	अचिन्हित पूर्णांक sys_offset;
	व्योम __iomem *regs;
	क्रमागत hdmi_colorspace csp;
	काष्ठा hdmi_audio_param aud_param;
	bool audio_enable;
	bool घातered;
	bool enabled;
	hdmi_codec_plugged_cb plugged_cb;
	काष्ठा device *codec_dev;
	काष्ठा mutex update_plugged_status_lock;
पूर्ण;

अटल अंतरभूत काष्ठा mtk_hdmi *hdmi_ctx_from_bridge(काष्ठा drm_bridge *b)
अणु
	वापस container_of(b, काष्ठा mtk_hdmi, bridge);
पूर्ण

अटल u32 mtk_hdmi_पढ़ो(काष्ठा mtk_hdmi *hdmi, u32 offset)
अणु
	वापस पढ़ोl(hdmi->regs + offset);
पूर्ण

अटल व्योम mtk_hdmi_ग_लिखो(काष्ठा mtk_hdmi *hdmi, u32 offset, u32 val)
अणु
	ग_लिखोl(val, hdmi->regs + offset);
पूर्ण

अटल व्योम mtk_hdmi_clear_bits(काष्ठा mtk_hdmi *hdmi, u32 offset, u32 bits)
अणु
	व्योम __iomem *reg = hdmi->regs + offset;
	u32 पंचांगp;

	पंचांगp = पढ़ोl(reg);
	पंचांगp &= ~bits;
	ग_लिखोl(पंचांगp, reg);
पूर्ण

अटल व्योम mtk_hdmi_set_bits(काष्ठा mtk_hdmi *hdmi, u32 offset, u32 bits)
अणु
	व्योम __iomem *reg = hdmi->regs + offset;
	u32 पंचांगp;

	पंचांगp = पढ़ोl(reg);
	पंचांगp |= bits;
	ग_लिखोl(पंचांगp, reg);
पूर्ण

अटल व्योम mtk_hdmi_mask(काष्ठा mtk_hdmi *hdmi, u32 offset, u32 val, u32 mask)
अणु
	व्योम __iomem *reg = hdmi->regs + offset;
	u32 पंचांगp;

	पंचांगp = पढ़ोl(reg);
	पंचांगp = (पंचांगp & ~mask) | (val & mask);
	ग_लिखोl(पंचांगp, reg);
पूर्ण

अटल व्योम mtk_hdmi_hw_vid_black(काष्ठा mtk_hdmi *hdmi, bool black)
अणु
	mtk_hdmi_mask(hdmi, VIDEO_CFG_4, black ? GEN_RGB : NORMAL_PATH,
		      VIDEO_SOURCE_SEL);
पूर्ण

अटल व्योम mtk_hdmi_hw_make_reg_writable(काष्ठा mtk_hdmi *hdmi, bool enable)
अणु
	काष्ठा arm_smccc_res res;

	/*
	 * MT8173 HDMI hardware has an output control bit to enable/disable HDMI
	 * output. This bit can only be controlled in ARM supervisor mode.
	 * The ARM trusted firmware provides an API क्रम the HDMI driver to set
	 * this control bit to enable HDMI output in supervisor mode.
	 */
	अगर (hdmi->conf && hdmi->conf->tz_disabled)
		regmap_update_bits(hdmi->sys_regmap,
				   hdmi->sys_offset + HDMI_SYS_CFG20,
				   0x80008005, enable ? 0x80000005 : 0x8000);
	अन्यथा
		arm_smccc_smc(MTK_SIP_SET_AUTHORIZED_SECURE_REG, 0x14000904,
			      0x80000000, 0, 0, 0, 0, 0, &res);

	regmap_update_bits(hdmi->sys_regmap, hdmi->sys_offset + HDMI_SYS_CFG20,
			   HDMI_PCLK_FREE_RUN, enable ? HDMI_PCLK_FREE_RUN : 0);
	regmap_update_bits(hdmi->sys_regmap, hdmi->sys_offset + HDMI_SYS_CFG1C,
			   HDMI_ON | ANLG_ON, enable ? (HDMI_ON | ANLG_ON) : 0);
पूर्ण

अटल व्योम mtk_hdmi_hw_1p4_version_enable(काष्ठा mtk_hdmi *hdmi, bool enable)
अणु
	regmap_update_bits(hdmi->sys_regmap, hdmi->sys_offset + HDMI_SYS_CFG20,
			   HDMI2P0_EN, enable ? 0 : HDMI2P0_EN);
पूर्ण

अटल व्योम mtk_hdmi_hw_aud_mute(काष्ठा mtk_hdmi *hdmi)
अणु
	mtk_hdmi_set_bits(hdmi, GRL_AUDIO_CFG, AUDIO_ZERO);
पूर्ण

अटल व्योम mtk_hdmi_hw_aud_unmute(काष्ठा mtk_hdmi *hdmi)
अणु
	mtk_hdmi_clear_bits(hdmi, GRL_AUDIO_CFG, AUDIO_ZERO);
पूर्ण

अटल व्योम mtk_hdmi_hw_reset(काष्ठा mtk_hdmi *hdmi)
अणु
	regmap_update_bits(hdmi->sys_regmap, hdmi->sys_offset + HDMI_SYS_CFG1C,
			   HDMI_RST, HDMI_RST);
	regmap_update_bits(hdmi->sys_regmap, hdmi->sys_offset + HDMI_SYS_CFG1C,
			   HDMI_RST, 0);
	mtk_hdmi_clear_bits(hdmi, GRL_CFG3, CFG3_CONTROL_PACKET_DELAY);
	regmap_update_bits(hdmi->sys_regmap, hdmi->sys_offset + HDMI_SYS_CFG1C,
			   ANLG_ON, ANLG_ON);
पूर्ण

अटल व्योम mtk_hdmi_hw_enable_notice(काष्ठा mtk_hdmi *hdmi, bool enable_notice)
अणु
	mtk_hdmi_mask(hdmi, GRL_CFG2, enable_notice ? CFG2_NOTICE_EN : 0,
		      CFG2_NOTICE_EN);
पूर्ण

अटल व्योम mtk_hdmi_hw_ग_लिखो_पूर्णांक_mask(काष्ठा mtk_hdmi *hdmi, u32 पूर्णांक_mask)
अणु
	mtk_hdmi_ग_लिखो(hdmi, GRL_INT_MASK, पूर्णांक_mask);
पूर्ण

अटल व्योम mtk_hdmi_hw_enable_dvi_mode(काष्ठा mtk_hdmi *hdmi, bool enable)
अणु
	mtk_hdmi_mask(hdmi, GRL_CFG1, enable ? CFG1_DVI : 0, CFG1_DVI);
पूर्ण

अटल व्योम mtk_hdmi_hw_send_info_frame(काष्ठा mtk_hdmi *hdmi, u8 *buffer,
					u8 len)
अणु
	u32 ctrl_reg = GRL_CTRL;
	पूर्णांक i;
	u8 *frame_data;
	क्रमागत hdmi_infoframe_type frame_type;
	u8 frame_ver;
	u8 frame_len;
	u8 checksum;
	पूर्णांक ctrl_frame_en = 0;

	frame_type = *buffer++;
	frame_ver = *buffer++;
	frame_len = *buffer++;
	checksum = *buffer++;
	frame_data = buffer;

	dev_dbg(hdmi->dev,
		"frame_type:0x%x,frame_ver:0x%x,frame_len:0x%x,checksum:0x%x\n",
		frame_type, frame_ver, frame_len, checksum);

	चयन (frame_type) अणु
	हाल HDMI_INFOFRAME_TYPE_AVI:
		ctrl_frame_en = CTRL_AVI_EN;
		ctrl_reg = GRL_CTRL;
		अवरोध;
	हाल HDMI_INFOFRAME_TYPE_SPD:
		ctrl_frame_en = CTRL_SPD_EN;
		ctrl_reg = GRL_CTRL;
		अवरोध;
	हाल HDMI_INFOFRAME_TYPE_AUDIO:
		ctrl_frame_en = CTRL_AUDIO_EN;
		ctrl_reg = GRL_CTRL;
		अवरोध;
	हाल HDMI_INFOFRAME_TYPE_VENDOR:
		ctrl_frame_en = VS_EN;
		ctrl_reg = GRL_ACP_ISRC_CTRL;
		अवरोध;
	शेष:
		dev_err(hdmi->dev, "Unknown infoframe type %d\n", frame_type);
		वापस;
	पूर्ण
	mtk_hdmi_clear_bits(hdmi, ctrl_reg, ctrl_frame_en);
	mtk_hdmi_ग_लिखो(hdmi, GRL_INFOFRM_TYPE, frame_type);
	mtk_hdmi_ग_लिखो(hdmi, GRL_INFOFRM_VER, frame_ver);
	mtk_hdmi_ग_लिखो(hdmi, GRL_INFOFRM_LNG, frame_len);

	mtk_hdmi_ग_लिखो(hdmi, GRL_IFM_PORT, checksum);
	क्रम (i = 0; i < frame_len; i++)
		mtk_hdmi_ग_लिखो(hdmi, GRL_IFM_PORT, frame_data[i]);

	mtk_hdmi_set_bits(hdmi, ctrl_reg, ctrl_frame_en);
पूर्ण

अटल व्योम mtk_hdmi_hw_send_aud_packet(काष्ठा mtk_hdmi *hdmi, bool enable)
अणु
	mtk_hdmi_mask(hdmi, GRL_SHIFT_R2, enable ? 0 : AUDIO_PACKET_OFF,
		      AUDIO_PACKET_OFF);
पूर्ण

अटल व्योम mtk_hdmi_hw_config_sys(काष्ठा mtk_hdmi *hdmi)
अणु
	regmap_update_bits(hdmi->sys_regmap, hdmi->sys_offset + HDMI_SYS_CFG20,
			   HDMI_OUT_FIFO_EN | MHL_MODE_ON, 0);
	usleep_range(2000, 4000);
	regmap_update_bits(hdmi->sys_regmap, hdmi->sys_offset + HDMI_SYS_CFG20,
			   HDMI_OUT_FIFO_EN | MHL_MODE_ON, HDMI_OUT_FIFO_EN);
पूर्ण

अटल व्योम mtk_hdmi_hw_set_deep_color_mode(काष्ठा mtk_hdmi *hdmi)
अणु
	regmap_update_bits(hdmi->sys_regmap, hdmi->sys_offset + HDMI_SYS_CFG20,
			   DEEP_COLOR_MODE_MASK | DEEP_COLOR_EN,
			   COLOR_8BIT_MODE);
पूर्ण

अटल व्योम mtk_hdmi_hw_send_av_mute(काष्ठा mtk_hdmi *hdmi)
अणु
	mtk_hdmi_clear_bits(hdmi, GRL_CFG4, CTRL_AVMUTE);
	usleep_range(2000, 4000);
	mtk_hdmi_set_bits(hdmi, GRL_CFG4, CTRL_AVMUTE);
पूर्ण

अटल व्योम mtk_hdmi_hw_send_av_unmute(काष्ठा mtk_hdmi *hdmi)
अणु
	mtk_hdmi_mask(hdmi, GRL_CFG4, CFG4_AV_UNMUTE_EN,
		      CFG4_AV_UNMUTE_EN | CFG4_AV_UNMUTE_SET);
	usleep_range(2000, 4000);
	mtk_hdmi_mask(hdmi, GRL_CFG4, CFG4_AV_UNMUTE_SET,
		      CFG4_AV_UNMUTE_EN | CFG4_AV_UNMUTE_SET);
पूर्ण

अटल व्योम mtk_hdmi_hw_ncts_enable(काष्ठा mtk_hdmi *hdmi, bool on)
अणु
	mtk_hdmi_mask(hdmi, GRL_CTS_CTRL, on ? 0 : CTS_CTRL_SOFT,
		      CTS_CTRL_SOFT);
पूर्ण

अटल व्योम mtk_hdmi_hw_ncts_स्वतः_ग_लिखो_enable(काष्ठा mtk_hdmi *hdmi,
					       bool enable)
अणु
	mtk_hdmi_mask(hdmi, GRL_CTS_CTRL, enable ? NCTS_WRI_ANYTIME : 0,
		      NCTS_WRI_ANYTIME);
पूर्ण

अटल व्योम mtk_hdmi_hw_msic_setting(काष्ठा mtk_hdmi *hdmi,
				     काष्ठा drm_display_mode *mode)
अणु
	mtk_hdmi_clear_bits(hdmi, GRL_CFG4, CFG4_MHL_MODE);

	अगर (mode->flags & DRM_MODE_FLAG_INTERLACE &&
	    mode->घड़ी == 74250 &&
	    mode->vdisplay == 1080)
		mtk_hdmi_clear_bits(hdmi, GRL_CFG2, CFG2_MHL_DE_SEL);
	अन्यथा
		mtk_hdmi_set_bits(hdmi, GRL_CFG2, CFG2_MHL_DE_SEL);
पूर्ण

अटल व्योम mtk_hdmi_hw_aud_set_channel_swap(काष्ठा mtk_hdmi *hdmi,
					क्रमागत hdmi_aud_channel_swap_type swap)
अणु
	u8 swap_bit;

	चयन (swap) अणु
	हाल HDMI_AUD_SWAP_LR:
		swap_bit = LR_SWAP;
		अवरोध;
	हाल HDMI_AUD_SWAP_LFE_CC:
		swap_bit = LFE_CC_SWAP;
		अवरोध;
	हाल HDMI_AUD_SWAP_LSRS:
		swap_bit = LSRS_SWAP;
		अवरोध;
	हाल HDMI_AUD_SWAP_RLS_RRS:
		swap_bit = RLS_RRS_SWAP;
		अवरोध;
	हाल HDMI_AUD_SWAP_LR_STATUS:
		swap_bit = LR_STATUS_SWAP;
		अवरोध;
	शेष:
		swap_bit = LFE_CC_SWAP;
		अवरोध;
	पूर्ण
	mtk_hdmi_mask(hdmi, GRL_CH_SWAP, swap_bit, 0xff);
पूर्ण

अटल व्योम mtk_hdmi_hw_aud_set_bit_num(काष्ठा mtk_hdmi *hdmi,
					क्रमागत hdmi_audio_sample_size bit_num)
अणु
	u32 val;

	चयन (bit_num) अणु
	हाल HDMI_AUDIO_SAMPLE_SIZE_16:
		val = AOUT_16BIT;
		अवरोध;
	हाल HDMI_AUDIO_SAMPLE_SIZE_20:
		val = AOUT_20BIT;
		अवरोध;
	हाल HDMI_AUDIO_SAMPLE_SIZE_24:
	हाल HDMI_AUDIO_SAMPLE_SIZE_STREAM:
		val = AOUT_24BIT;
		अवरोध;
	पूर्ण

	mtk_hdmi_mask(hdmi, GRL_AOUT_CFG, val, AOUT_BNUM_SEL_MASK);
पूर्ण

अटल व्योम mtk_hdmi_hw_aud_set_i2s_fmt(काष्ठा mtk_hdmi *hdmi,
					क्रमागत hdmi_aud_i2s_fmt i2s_fmt)
अणु
	u32 val;

	val = mtk_hdmi_पढ़ो(hdmi, GRL_CFG0);
	val &= ~(CFG0_W_LENGTH_MASK | CFG0_I2S_MODE_MASK);

	चयन (i2s_fmt) अणु
	हाल HDMI_I2S_MODE_RJT_24BIT:
		val |= CFG0_I2S_MODE_RTJ | CFG0_W_LENGTH_24BIT;
		अवरोध;
	हाल HDMI_I2S_MODE_RJT_16BIT:
		val |= CFG0_I2S_MODE_RTJ | CFG0_W_LENGTH_16BIT;
		अवरोध;
	हाल HDMI_I2S_MODE_LJT_24BIT:
	शेष:
		val |= CFG0_I2S_MODE_LTJ | CFG0_W_LENGTH_24BIT;
		अवरोध;
	हाल HDMI_I2S_MODE_LJT_16BIT:
		val |= CFG0_I2S_MODE_LTJ | CFG0_W_LENGTH_16BIT;
		अवरोध;
	हाल HDMI_I2S_MODE_I2S_24BIT:
		val |= CFG0_I2S_MODE_I2S | CFG0_W_LENGTH_24BIT;
		अवरोध;
	हाल HDMI_I2S_MODE_I2S_16BIT:
		val |= CFG0_I2S_MODE_I2S | CFG0_W_LENGTH_16BIT;
		अवरोध;
	पूर्ण
	mtk_hdmi_ग_लिखो(hdmi, GRL_CFG0, val);
पूर्ण

अटल व्योम mtk_hdmi_hw_audio_config(काष्ठा mtk_hdmi *hdmi, bool dst)
अणु
	स्थिर u8 mask = HIGH_BIT_RATE | DST_NORMAL_DOUBLE | SACD_DST | DSD_SEL;
	u8 val;

	/* Disable high bitrate, set DST packet normal/द्विगुन */
	mtk_hdmi_clear_bits(hdmi, GRL_AOUT_CFG, HIGH_BIT_RATE_PACKET_ALIGN);

	अगर (dst)
		val = DST_NORMAL_DOUBLE | SACD_DST;
	अन्यथा
		val = 0;

	mtk_hdmi_mask(hdmi, GRL_AUDIO_CFG, val, mask);
पूर्ण

अटल व्योम mtk_hdmi_hw_aud_set_i2s_chan_num(काष्ठा mtk_hdmi *hdmi,
					क्रमागत hdmi_aud_channel_type channel_type,
					u8 channel_count)
अणु
	अचिन्हित पूर्णांक ch_चयन;
	u8 i2s_uv;

	ch_चयन = CH_SWITCH(7, 7) | CH_SWITCH(6, 6) |
		    CH_SWITCH(5, 5) | CH_SWITCH(4, 4) |
		    CH_SWITCH(3, 3) | CH_SWITCH(1, 2) |
		    CH_SWITCH(2, 1) | CH_SWITCH(0, 0);

	अगर (channel_count == 2) अणु
		i2s_uv = I2S_UV_CH_EN(0);
	पूर्ण अन्यथा अगर (channel_count == 3 || channel_count == 4) अणु
		अगर (channel_count == 4 &&
		    (channel_type == HDMI_AUD_CHAN_TYPE_3_0_LRS ||
		    channel_type == HDMI_AUD_CHAN_TYPE_4_0))
			i2s_uv = I2S_UV_CH_EN(2) | I2S_UV_CH_EN(0);
		अन्यथा
			i2s_uv = I2S_UV_CH_EN(3) | I2S_UV_CH_EN(2);
	पूर्ण अन्यथा अगर (channel_count == 6 || channel_count == 5) अणु
		अगर (channel_count == 6 &&
		    channel_type != HDMI_AUD_CHAN_TYPE_5_1 &&
		    channel_type != HDMI_AUD_CHAN_TYPE_4_1_CLRS) अणु
			i2s_uv = I2S_UV_CH_EN(3) | I2S_UV_CH_EN(2) |
				 I2S_UV_CH_EN(1) | I2S_UV_CH_EN(0);
		पूर्ण अन्यथा अणु
			i2s_uv = I2S_UV_CH_EN(2) | I2S_UV_CH_EN(1) |
				 I2S_UV_CH_EN(0);
		पूर्ण
	पूर्ण अन्यथा अगर (channel_count == 8 || channel_count == 7) अणु
		i2s_uv = I2S_UV_CH_EN(3) | I2S_UV_CH_EN(2) |
			 I2S_UV_CH_EN(1) | I2S_UV_CH_EN(0);
	पूर्ण अन्यथा अणु
		i2s_uv = I2S_UV_CH_EN(0);
	पूर्ण

	mtk_hdmi_ग_लिखो(hdmi, GRL_CH_SW0, ch_चयन & 0xff);
	mtk_hdmi_ग_लिखो(hdmi, GRL_CH_SW1, (ch_चयन >> 8) & 0xff);
	mtk_hdmi_ग_लिखो(hdmi, GRL_CH_SW2, (ch_चयन >> 16) & 0xff);
	mtk_hdmi_ग_लिखो(hdmi, GRL_I2S_UV, i2s_uv);
पूर्ण

अटल व्योम mtk_hdmi_hw_aud_set_input_type(काष्ठा mtk_hdmi *hdmi,
					   क्रमागत hdmi_aud_input_type input_type)
अणु
	u32 val;

	val = mtk_hdmi_पढ़ो(hdmi, GRL_CFG1);
	अगर (input_type == HDMI_AUD_INPUT_I2S &&
	    (val & CFG1_SPDIF) == CFG1_SPDIF) अणु
		val &= ~CFG1_SPDIF;
	पूर्ण अन्यथा अगर (input_type == HDMI_AUD_INPUT_SPDIF &&
		(val & CFG1_SPDIF) == 0) अणु
		val |= CFG1_SPDIF;
	पूर्ण
	mtk_hdmi_ग_लिखो(hdmi, GRL_CFG1, val);
पूर्ण

अटल व्योम mtk_hdmi_hw_aud_set_channel_status(काष्ठा mtk_hdmi *hdmi,
					       u8 *channel_status)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 5; i++) अणु
		mtk_hdmi_ग_लिखो(hdmi, GRL_I2S_C_STA0 + i * 4, channel_status[i]);
		mtk_hdmi_ग_लिखो(hdmi, GRL_L_STATUS_0 + i * 4, channel_status[i]);
		mtk_hdmi_ग_लिखो(hdmi, GRL_R_STATUS_0 + i * 4, channel_status[i]);
	पूर्ण
	क्रम (; i < 24; i++) अणु
		mtk_hdmi_ग_लिखो(hdmi, GRL_L_STATUS_0 + i * 4, 0);
		mtk_hdmi_ग_लिखो(hdmi, GRL_R_STATUS_0 + i * 4, 0);
	पूर्ण
पूर्ण

अटल व्योम mtk_hdmi_hw_aud_src_reenable(काष्ठा mtk_hdmi *hdmi)
अणु
	u32 val;

	val = mtk_hdmi_पढ़ो(hdmi, GRL_MIX_CTRL);
	अगर (val & MIX_CTRL_SRC_EN) अणु
		val &= ~MIX_CTRL_SRC_EN;
		mtk_hdmi_ग_लिखो(hdmi, GRL_MIX_CTRL, val);
		usleep_range(255, 512);
		val |= MIX_CTRL_SRC_EN;
		mtk_hdmi_ग_लिखो(hdmi, GRL_MIX_CTRL, val);
	पूर्ण
पूर्ण

अटल व्योम mtk_hdmi_hw_aud_src_disable(काष्ठा mtk_hdmi *hdmi)
अणु
	u32 val;

	val = mtk_hdmi_पढ़ो(hdmi, GRL_MIX_CTRL);
	val &= ~MIX_CTRL_SRC_EN;
	mtk_hdmi_ग_लिखो(hdmi, GRL_MIX_CTRL, val);
	mtk_hdmi_ग_लिखो(hdmi, GRL_SHIFT_L1, 0x00);
पूर्ण

अटल व्योम mtk_hdmi_hw_aud_set_mclk(काष्ठा mtk_hdmi *hdmi,
				     क्रमागत hdmi_aud_mclk mclk)
अणु
	u32 val;

	val = mtk_hdmi_पढ़ो(hdmi, GRL_CFG5);
	val &= CFG5_CD_RATIO_MASK;

	चयन (mclk) अणु
	हाल HDMI_AUD_MCLK_128FS:
		val |= CFG5_FS128;
		अवरोध;
	हाल HDMI_AUD_MCLK_256FS:
		val |= CFG5_FS256;
		अवरोध;
	हाल HDMI_AUD_MCLK_384FS:
		val |= CFG5_FS384;
		अवरोध;
	हाल HDMI_AUD_MCLK_512FS:
		val |= CFG5_FS512;
		अवरोध;
	हाल HDMI_AUD_MCLK_768FS:
		val |= CFG5_FS768;
		अवरोध;
	शेष:
		val |= CFG5_FS256;
		अवरोध;
	पूर्ण
	mtk_hdmi_ग_लिखो(hdmi, GRL_CFG5, val);
पूर्ण

काष्ठा hdmi_acr_n अणु
	अचिन्हित पूर्णांक घड़ी;
	अचिन्हित पूर्णांक n[3];
पूर्ण;

/* Recommended N values from HDMI specअगरication, tables 7-1 to 7-3 */
अटल स्थिर काष्ठा hdmi_acr_n hdmi_rec_n_table[] = अणु
	/* Clock, N: 32kHz 44.1kHz 48kHz */
	अणु  25175, अणु  4576,  7007,  6864 पूर्ण पूर्ण,
	अणु  74176, अणु 11648, 17836, 11648 पूर्ण पूर्ण,
	अणु 148352, अणु 11648,  8918,  5824 पूर्ण पूर्ण,
	अणु 296703, अणु  5824,  4459,  5824 पूर्ण पूर्ण,
	अणु 297000, अणु  3072,  4704,  5120 पूर्ण पूर्ण,
	अणु      0, अणु  4096,  6272,  6144 पूर्ण पूर्ण, /* all other TMDS घड़ीs */
पूर्ण;

/**
 * hdmi_recommended_n() - Return N value recommended by HDMI specअगरication
 * @freq: audio sample rate in Hz
 * @घड़ी: rounded TMDS घड़ी in kHz
 */
अटल अचिन्हित पूर्णांक hdmi_recommended_n(अचिन्हित पूर्णांक freq, अचिन्हित पूर्णांक घड़ी)
अणु
	स्थिर काष्ठा hdmi_acr_n *recommended;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(hdmi_rec_n_table) - 1; i++) अणु
		अगर (घड़ी == hdmi_rec_n_table[i].घड़ी)
			अवरोध;
	पूर्ण
	recommended = hdmi_rec_n_table + i;

	चयन (freq) अणु
	हाल 32000:
		वापस recommended->n[0];
	हाल 44100:
		वापस recommended->n[1];
	हाल 48000:
		वापस recommended->n[2];
	हाल 88200:
		वापस recommended->n[1] * 2;
	हाल 96000:
		वापस recommended->n[2] * 2;
	हाल 176400:
		वापस recommended->n[1] * 4;
	हाल 192000:
		वापस recommended->n[2] * 4;
	शेष:
		वापस (128 * freq) / 1000;
	पूर्ण
पूर्ण

अटल अचिन्हित पूर्णांक hdmi_mode_घड़ी_प्रकारo_hz(अचिन्हित पूर्णांक घड़ी)
अणु
	चयन (घड़ी) अणु
	हाल 25175:
		वापस 25174825;	/* 25.2/1.001 MHz */
	हाल 74176:
		वापस 74175824;	/* 74.25/1.001 MHz */
	हाल 148352:
		वापस 148351648;	/* 148.5/1.001 MHz */
	हाल 296703:
		वापस 296703297;	/* 297/1.001 MHz */
	शेष:
		वापस घड़ी * 1000;
	पूर्ण
पूर्ण

अटल अचिन्हित पूर्णांक hdmi_expected_cts(अचिन्हित पूर्णांक audio_sample_rate,
				      अचिन्हित पूर्णांक पंचांगds_घड़ी, अचिन्हित पूर्णांक n)
अणु
	वापस DIV_ROUND_CLOSEST_ULL((u64)hdmi_mode_घड़ी_प्रकारo_hz(पंचांगds_घड़ी) * n,
				     128 * audio_sample_rate);
पूर्ण

अटल व्योम करो_hdmi_hw_aud_set_ncts(काष्ठा mtk_hdmi *hdmi, अचिन्हित पूर्णांक n,
				    अचिन्हित पूर्णांक cts)
अणु
	अचिन्हित अक्षर val[NCTS_BYTES];
	पूर्णांक i;

	mtk_hdmi_ग_लिखो(hdmi, GRL_NCTS, 0);
	mtk_hdmi_ग_लिखो(hdmi, GRL_NCTS, 0);
	mtk_hdmi_ग_लिखो(hdmi, GRL_NCTS, 0);
	स_रखो(val, 0, माप(val));

	val[0] = (cts >> 24) & 0xff;
	val[1] = (cts >> 16) & 0xff;
	val[2] = (cts >> 8) & 0xff;
	val[3] = cts & 0xff;

	val[4] = (n >> 16) & 0xff;
	val[5] = (n >> 8) & 0xff;
	val[6] = n & 0xff;

	क्रम (i = 0; i < NCTS_BYTES; i++)
		mtk_hdmi_ग_लिखो(hdmi, GRL_NCTS, val[i]);
पूर्ण

अटल व्योम mtk_hdmi_hw_aud_set_ncts(काष्ठा mtk_hdmi *hdmi,
				     अचिन्हित पूर्णांक sample_rate,
				     अचिन्हित पूर्णांक घड़ी)
अणु
	अचिन्हित पूर्णांक n, cts;

	n = hdmi_recommended_n(sample_rate, घड़ी);
	cts = hdmi_expected_cts(sample_rate, घड़ी, n);

	dev_dbg(hdmi->dev, "%s: sample_rate=%u, clock=%d, cts=%u, n=%u\n",
		__func__, sample_rate, घड़ी, n, cts);

	mtk_hdmi_mask(hdmi, DUMMY_304, AUDIO_I2S_NCTS_SEL_64,
		      AUDIO_I2S_NCTS_SEL);
	करो_hdmi_hw_aud_set_ncts(hdmi, n, cts);
पूर्ण

अटल u8 mtk_hdmi_aud_get_chnl_count(क्रमागत hdmi_aud_channel_type channel_type)
अणु
	चयन (channel_type) अणु
	हाल HDMI_AUD_CHAN_TYPE_1_0:
	हाल HDMI_AUD_CHAN_TYPE_1_1:
	हाल HDMI_AUD_CHAN_TYPE_2_0:
		वापस 2;
	हाल HDMI_AUD_CHAN_TYPE_2_1:
	हाल HDMI_AUD_CHAN_TYPE_3_0:
		वापस 3;
	हाल HDMI_AUD_CHAN_TYPE_3_1:
	हाल HDMI_AUD_CHAN_TYPE_4_0:
	हाल HDMI_AUD_CHAN_TYPE_3_0_LRS:
		वापस 4;
	हाल HDMI_AUD_CHAN_TYPE_4_1:
	हाल HDMI_AUD_CHAN_TYPE_5_0:
	हाल HDMI_AUD_CHAN_TYPE_3_1_LRS:
	हाल HDMI_AUD_CHAN_TYPE_4_0_CLRS:
		वापस 5;
	हाल HDMI_AUD_CHAN_TYPE_5_1:
	हाल HDMI_AUD_CHAN_TYPE_6_0:
	हाल HDMI_AUD_CHAN_TYPE_4_1_CLRS:
	हाल HDMI_AUD_CHAN_TYPE_6_0_CS:
	हाल HDMI_AUD_CHAN_TYPE_6_0_CH:
	हाल HDMI_AUD_CHAN_TYPE_6_0_OH:
	हाल HDMI_AUD_CHAN_TYPE_6_0_CHR:
		वापस 6;
	हाल HDMI_AUD_CHAN_TYPE_6_1:
	हाल HDMI_AUD_CHAN_TYPE_6_1_CS:
	हाल HDMI_AUD_CHAN_TYPE_6_1_CH:
	हाल HDMI_AUD_CHAN_TYPE_6_1_OH:
	हाल HDMI_AUD_CHAN_TYPE_6_1_CHR:
	हाल HDMI_AUD_CHAN_TYPE_7_0:
	हाल HDMI_AUD_CHAN_TYPE_7_0_LH_RH:
	हाल HDMI_AUD_CHAN_TYPE_7_0_LSR_RSR:
	हाल HDMI_AUD_CHAN_TYPE_7_0_LC_RC:
	हाल HDMI_AUD_CHAN_TYPE_7_0_LW_RW:
	हाल HDMI_AUD_CHAN_TYPE_7_0_LSD_RSD:
	हाल HDMI_AUD_CHAN_TYPE_7_0_LSS_RSS:
	हाल HDMI_AUD_CHAN_TYPE_7_0_LHS_RHS:
	हाल HDMI_AUD_CHAN_TYPE_7_0_CS_CH:
	हाल HDMI_AUD_CHAN_TYPE_7_0_CS_OH:
	हाल HDMI_AUD_CHAN_TYPE_7_0_CS_CHR:
	हाल HDMI_AUD_CHAN_TYPE_7_0_CH_OH:
	हाल HDMI_AUD_CHAN_TYPE_7_0_CH_CHR:
	हाल HDMI_AUD_CHAN_TYPE_7_0_OH_CHR:
	हाल HDMI_AUD_CHAN_TYPE_7_0_LSS_RSS_LSR_RSR:
	हाल HDMI_AUD_CHAN_TYPE_8_0_LH_RH_CS:
		वापस 7;
	हाल HDMI_AUD_CHAN_TYPE_7_1:
	हाल HDMI_AUD_CHAN_TYPE_7_1_LH_RH:
	हाल HDMI_AUD_CHAN_TYPE_7_1_LSR_RSR:
	हाल HDMI_AUD_CHAN_TYPE_7_1_LC_RC:
	हाल HDMI_AUD_CHAN_TYPE_7_1_LW_RW:
	हाल HDMI_AUD_CHAN_TYPE_7_1_LSD_RSD:
	हाल HDMI_AUD_CHAN_TYPE_7_1_LSS_RSS:
	हाल HDMI_AUD_CHAN_TYPE_7_1_LHS_RHS:
	हाल HDMI_AUD_CHAN_TYPE_7_1_CS_CH:
	हाल HDMI_AUD_CHAN_TYPE_7_1_CS_OH:
	हाल HDMI_AUD_CHAN_TYPE_7_1_CS_CHR:
	हाल HDMI_AUD_CHAN_TYPE_7_1_CH_OH:
	हाल HDMI_AUD_CHAN_TYPE_7_1_CH_CHR:
	हाल HDMI_AUD_CHAN_TYPE_7_1_OH_CHR:
	हाल HDMI_AUD_CHAN_TYPE_7_1_LSS_RSS_LSR_RSR:
		वापस 8;
	शेष:
		वापस 2;
	पूर्ण
पूर्ण

अटल पूर्णांक mtk_hdmi_video_change_vpll(काष्ठा mtk_hdmi *hdmi, u32 घड़ी)
अणु
	अचिन्हित दीर्घ rate;
	पूर्णांक ret;

	/* The DPI driver alपढ़ोy should have set TVDPLL to the correct rate */
	ret = clk_set_rate(hdmi->clk[MTK_HDMI_CLK_HDMI_PLL], घड़ी);
	अगर (ret) अणु
		dev_err(hdmi->dev, "Failed to set PLL to %u Hz: %d\n", घड़ी,
			ret);
		वापस ret;
	पूर्ण

	rate = clk_get_rate(hdmi->clk[MTK_HDMI_CLK_HDMI_PLL]);

	अगर (DIV_ROUND_CLOSEST(rate, 1000) != DIV_ROUND_CLOSEST(घड़ी, 1000))
		dev_warn(hdmi->dev, "Want PLL %u Hz, got %lu Hz\n", घड़ी,
			 rate);
	अन्यथा
		dev_dbg(hdmi->dev, "Want PLL %u Hz, got %lu Hz\n", घड़ी, rate);

	mtk_hdmi_hw_config_sys(hdmi);
	mtk_hdmi_hw_set_deep_color_mode(hdmi);
	वापस 0;
पूर्ण

अटल व्योम mtk_hdmi_video_set_display_mode(काष्ठा mtk_hdmi *hdmi,
					    काष्ठा drm_display_mode *mode)
अणु
	mtk_hdmi_hw_reset(hdmi);
	mtk_hdmi_hw_enable_notice(hdmi, true);
	mtk_hdmi_hw_ग_लिखो_पूर्णांक_mask(hdmi, 0xff);
	mtk_hdmi_hw_enable_dvi_mode(hdmi, hdmi->dvi_mode);
	mtk_hdmi_hw_ncts_स्वतः_ग_लिखो_enable(hdmi, true);

	mtk_hdmi_hw_msic_setting(hdmi, mode);
पूर्ण


अटल व्योम mtk_hdmi_aud_set_input(काष्ठा mtk_hdmi *hdmi)
अणु
	क्रमागत hdmi_aud_channel_type chan_type;
	u8 chan_count;
	bool dst;

	mtk_hdmi_hw_aud_set_channel_swap(hdmi, HDMI_AUD_SWAP_LFE_CC);
	mtk_hdmi_set_bits(hdmi, GRL_MIX_CTRL, MIX_CTRL_FLAT);

	अगर (hdmi->aud_param.aud_input_type == HDMI_AUD_INPUT_SPDIF &&
	    hdmi->aud_param.aud_codec == HDMI_AUDIO_CODING_TYPE_DST) अणु
		mtk_hdmi_hw_aud_set_bit_num(hdmi, HDMI_AUDIO_SAMPLE_SIZE_24);
	पूर्ण अन्यथा अगर (hdmi->aud_param.aud_i2s_fmt == HDMI_I2S_MODE_LJT_24BIT) अणु
		hdmi->aud_param.aud_i2s_fmt = HDMI_I2S_MODE_LJT_16BIT;
	पूर्ण

	mtk_hdmi_hw_aud_set_i2s_fmt(hdmi, hdmi->aud_param.aud_i2s_fmt);
	mtk_hdmi_hw_aud_set_bit_num(hdmi, HDMI_AUDIO_SAMPLE_SIZE_24);

	dst = ((hdmi->aud_param.aud_input_type == HDMI_AUD_INPUT_SPDIF) &&
	       (hdmi->aud_param.aud_codec == HDMI_AUDIO_CODING_TYPE_DST));
	mtk_hdmi_hw_audio_config(hdmi, dst);

	अगर (hdmi->aud_param.aud_input_type == HDMI_AUD_INPUT_SPDIF)
		chan_type = HDMI_AUD_CHAN_TYPE_2_0;
	अन्यथा
		chan_type = hdmi->aud_param.aud_input_chan_type;
	chan_count = mtk_hdmi_aud_get_chnl_count(chan_type);
	mtk_hdmi_hw_aud_set_i2s_chan_num(hdmi, chan_type, chan_count);
	mtk_hdmi_hw_aud_set_input_type(hdmi, hdmi->aud_param.aud_input_type);
पूर्ण

अटल पूर्णांक mtk_hdmi_aud_set_src(काष्ठा mtk_hdmi *hdmi,
				काष्ठा drm_display_mode *display_mode)
अणु
	अचिन्हित पूर्णांक sample_rate = hdmi->aud_param.codec_params.sample_rate;

	mtk_hdmi_hw_ncts_enable(hdmi, false);
	mtk_hdmi_hw_aud_src_disable(hdmi);
	mtk_hdmi_clear_bits(hdmi, GRL_CFG2, CFG2_ACLK_INV);

	अगर (hdmi->aud_param.aud_input_type == HDMI_AUD_INPUT_I2S) अणु
		चयन (sample_rate) अणु
		हाल 32000:
		हाल 44100:
		हाल 48000:
		हाल 88200:
		हाल 96000:
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
		mtk_hdmi_hw_aud_set_mclk(hdmi, hdmi->aud_param.aud_mclk);
	पूर्ण अन्यथा अणु
		चयन (sample_rate) अणु
		हाल 32000:
		हाल 44100:
		हाल 48000:
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
		mtk_hdmi_hw_aud_set_mclk(hdmi, HDMI_AUD_MCLK_128FS);
	पूर्ण

	mtk_hdmi_hw_aud_set_ncts(hdmi, sample_rate, display_mode->घड़ी);

	mtk_hdmi_hw_aud_src_reenable(hdmi);
	वापस 0;
पूर्ण

अटल पूर्णांक mtk_hdmi_aud_output_config(काष्ठा mtk_hdmi *hdmi,
				      काष्ठा drm_display_mode *display_mode)
अणु
	mtk_hdmi_hw_aud_mute(hdmi);
	mtk_hdmi_hw_send_aud_packet(hdmi, false);

	mtk_hdmi_aud_set_input(hdmi);
	mtk_hdmi_aud_set_src(hdmi, display_mode);
	mtk_hdmi_hw_aud_set_channel_status(hdmi,
			hdmi->aud_param.codec_params.iec.status);

	usleep_range(50, 100);

	mtk_hdmi_hw_ncts_enable(hdmi, true);
	mtk_hdmi_hw_send_aud_packet(hdmi, true);
	mtk_hdmi_hw_aud_unmute(hdmi);
	वापस 0;
पूर्ण

अटल पूर्णांक mtk_hdmi_setup_avi_infoframe(काष्ठा mtk_hdmi *hdmi,
					काष्ठा drm_display_mode *mode)
अणु
	काष्ठा hdmi_avi_infoframe frame;
	u8 buffer[HDMI_INFOFRAME_HEADER_SIZE + HDMI_AVI_INFOFRAME_SIZE];
	sमाप_प्रकार err;

	err = drm_hdmi_avi_infoframe_from_display_mode(&frame,
						       hdmi->curr_conn, mode);
	अगर (err < 0) अणु
		dev_err(hdmi->dev,
			"Failed to get AVI infoframe from mode: %zd\n", err);
		वापस err;
	पूर्ण

	err = hdmi_avi_infoframe_pack(&frame, buffer, माप(buffer));
	अगर (err < 0) अणु
		dev_err(hdmi->dev, "Failed to pack AVI infoframe: %zd\n", err);
		वापस err;
	पूर्ण

	mtk_hdmi_hw_send_info_frame(hdmi, buffer, माप(buffer));
	वापस 0;
पूर्ण

अटल पूर्णांक mtk_hdmi_setup_spd_infoframe(काष्ठा mtk_hdmi *hdmi,
					स्थिर अक्षर *venकरोr,
					स्थिर अक्षर *product)
अणु
	काष्ठा hdmi_spd_infoframe frame;
	u8 buffer[HDMI_INFOFRAME_HEADER_SIZE + HDMI_SPD_INFOFRAME_SIZE];
	sमाप_प्रकार err;

	err = hdmi_spd_infoframe_init(&frame, venकरोr, product);
	अगर (err < 0) अणु
		dev_err(hdmi->dev, "Failed to initialize SPD infoframe: %zd\n",
			err);
		वापस err;
	पूर्ण

	err = hdmi_spd_infoframe_pack(&frame, buffer, माप(buffer));
	अगर (err < 0) अणु
		dev_err(hdmi->dev, "Failed to pack SDP infoframe: %zd\n", err);
		वापस err;
	पूर्ण

	mtk_hdmi_hw_send_info_frame(hdmi, buffer, माप(buffer));
	वापस 0;
पूर्ण

अटल पूर्णांक mtk_hdmi_setup_audio_infoframe(काष्ठा mtk_hdmi *hdmi)
अणु
	काष्ठा hdmi_audio_infoframe frame;
	u8 buffer[HDMI_INFOFRAME_HEADER_SIZE + HDMI_AUDIO_INFOFRAME_SIZE];
	sमाप_प्रकार err;

	err = hdmi_audio_infoframe_init(&frame);
	अगर (err < 0) अणु
		dev_err(hdmi->dev, "Failed to setup audio infoframe: %zd\n",
			err);
		वापस err;
	पूर्ण

	frame.coding_type = HDMI_AUDIO_CODING_TYPE_STREAM;
	frame.sample_frequency = HDMI_AUDIO_SAMPLE_FREQUENCY_STREAM;
	frame.sample_size = HDMI_AUDIO_SAMPLE_SIZE_STREAM;
	frame.channels = mtk_hdmi_aud_get_chnl_count(
					hdmi->aud_param.aud_input_chan_type);

	err = hdmi_audio_infoframe_pack(&frame, buffer, माप(buffer));
	अगर (err < 0) अणु
		dev_err(hdmi->dev, "Failed to pack audio infoframe: %zd\n",
			err);
		वापस err;
	पूर्ण

	mtk_hdmi_hw_send_info_frame(hdmi, buffer, माप(buffer));
	वापस 0;
पूर्ण

अटल पूर्णांक mtk_hdmi_setup_venकरोr_specअगरic_infoframe(काष्ठा mtk_hdmi *hdmi,
						काष्ठा drm_display_mode *mode)
अणु
	काष्ठा hdmi_venकरोr_infoframe frame;
	u8 buffer[10];
	sमाप_प्रकार err;

	err = drm_hdmi_venकरोr_infoframe_from_display_mode(&frame,
							  hdmi->curr_conn, mode);
	अगर (err) अणु
		dev_err(hdmi->dev,
			"Failed to get vendor infoframe from mode: %zd\n", err);
		वापस err;
	पूर्ण

	err = hdmi_venकरोr_infoframe_pack(&frame, buffer, माप(buffer));
	अगर (err < 0) अणु
		dev_err(hdmi->dev, "Failed to pack vendor infoframe: %zd\n",
			err);
		वापस err;
	पूर्ण

	mtk_hdmi_hw_send_info_frame(hdmi, buffer, माप(buffer));
	वापस 0;
पूर्ण

अटल पूर्णांक mtk_hdmi_output_init(काष्ठा mtk_hdmi *hdmi)
अणु
	काष्ठा hdmi_audio_param *aud_param = &hdmi->aud_param;

	hdmi->csp = HDMI_COLORSPACE_RGB;
	aud_param->aud_codec = HDMI_AUDIO_CODING_TYPE_PCM;
	aud_param->aud_sampe_size = HDMI_AUDIO_SAMPLE_SIZE_16;
	aud_param->aud_input_type = HDMI_AUD_INPUT_I2S;
	aud_param->aud_i2s_fmt = HDMI_I2S_MODE_I2S_24BIT;
	aud_param->aud_mclk = HDMI_AUD_MCLK_128FS;
	aud_param->aud_input_chan_type = HDMI_AUD_CHAN_TYPE_2_0;

	वापस 0;
पूर्ण

अटल व्योम mtk_hdmi_audio_enable(काष्ठा mtk_hdmi *hdmi)
अणु
	mtk_hdmi_hw_send_aud_packet(hdmi, true);
	hdmi->audio_enable = true;
पूर्ण

अटल व्योम mtk_hdmi_audio_disable(काष्ठा mtk_hdmi *hdmi)
अणु
	mtk_hdmi_hw_send_aud_packet(hdmi, false);
	hdmi->audio_enable = false;
पूर्ण

अटल पूर्णांक mtk_hdmi_audio_set_param(काष्ठा mtk_hdmi *hdmi,
				    काष्ठा hdmi_audio_param *param)
अणु
	अगर (!hdmi->audio_enable) अणु
		dev_err(hdmi->dev, "hdmi audio is in disable state!\n");
		वापस -EINVAL;
	पूर्ण
	dev_dbg(hdmi->dev, "codec:%d, input:%d, channel:%d, fs:%d\n",
		param->aud_codec, param->aud_input_type,
		param->aud_input_chan_type, param->codec_params.sample_rate);
	स_नकल(&hdmi->aud_param, param, माप(*param));
	वापस mtk_hdmi_aud_output_config(hdmi, &hdmi->mode);
पूर्ण

अटल पूर्णांक mtk_hdmi_output_set_display_mode(काष्ठा mtk_hdmi *hdmi,
					    काष्ठा drm_display_mode *mode)
अणु
	पूर्णांक ret;

	mtk_hdmi_hw_vid_black(hdmi, true);
	mtk_hdmi_hw_aud_mute(hdmi);
	mtk_hdmi_hw_send_av_mute(hdmi);
	phy_घातer_off(hdmi->phy);

	ret = mtk_hdmi_video_change_vpll(hdmi,
					 mode->घड़ी * 1000);
	अगर (ret) अणु
		dev_err(hdmi->dev, "Failed to set vpll: %d\n", ret);
		वापस ret;
	पूर्ण
	mtk_hdmi_video_set_display_mode(hdmi, mode);

	phy_घातer_on(hdmi->phy);
	mtk_hdmi_aud_output_config(hdmi, mode);

	mtk_hdmi_hw_vid_black(hdmi, false);
	mtk_hdmi_hw_aud_unmute(hdmi);
	mtk_hdmi_hw_send_av_unmute(hdmi);

	वापस 0;
पूर्ण

अटल स्थिर अक्षर * स्थिर mtk_hdmi_clk_names[MTK_HDMI_CLK_COUNT] = अणु
	[MTK_HDMI_CLK_HDMI_PIXEL] = "pixel",
	[MTK_HDMI_CLK_HDMI_PLL] = "pll",
	[MTK_HDMI_CLK_AUD_BCLK] = "bclk",
	[MTK_HDMI_CLK_AUD_SPDIF] = "spdif",
पूर्ण;

अटल पूर्णांक mtk_hdmi_get_all_clk(काष्ठा mtk_hdmi *hdmi,
				काष्ठा device_node *np)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(mtk_hdmi_clk_names); i++) अणु
		hdmi->clk[i] = of_clk_get_by_name(np,
						  mtk_hdmi_clk_names[i]);
		अगर (IS_ERR(hdmi->clk[i]))
			वापस PTR_ERR(hdmi->clk[i]);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक mtk_hdmi_clk_enable_audio(काष्ठा mtk_hdmi *hdmi)
अणु
	पूर्णांक ret;

	ret = clk_prepare_enable(hdmi->clk[MTK_HDMI_CLK_AUD_BCLK]);
	अगर (ret)
		वापस ret;

	ret = clk_prepare_enable(hdmi->clk[MTK_HDMI_CLK_AUD_SPDIF]);
	अगर (ret)
		जाओ err;

	वापस 0;
err:
	clk_disable_unprepare(hdmi->clk[MTK_HDMI_CLK_AUD_BCLK]);
	वापस ret;
पूर्ण

अटल व्योम mtk_hdmi_clk_disable_audio(काष्ठा mtk_hdmi *hdmi)
अणु
	clk_disable_unprepare(hdmi->clk[MTK_HDMI_CLK_AUD_BCLK]);
	clk_disable_unprepare(hdmi->clk[MTK_HDMI_CLK_AUD_SPDIF]);
पूर्ण

अटल क्रमागत drm_connector_status
mtk_hdmi_update_plugged_status(काष्ठा mtk_hdmi *hdmi)
अणु
	bool connected;

	mutex_lock(&hdmi->update_plugged_status_lock);
	connected = mtk_cec_hpd_high(hdmi->cec_dev);
	अगर (hdmi->plugged_cb && hdmi->codec_dev)
		hdmi->plugged_cb(hdmi->codec_dev, connected);
	mutex_unlock(&hdmi->update_plugged_status_lock);

	वापस connected ?
	       connector_status_connected : connector_status_disconnected;
पूर्ण

अटल क्रमागत drm_connector_status mtk_hdmi_detect(काष्ठा mtk_hdmi *hdmi)
अणु
	वापस mtk_hdmi_update_plugged_status(hdmi);
पूर्ण

अटल पूर्णांक mtk_hdmi_bridge_mode_valid(काष्ठा drm_bridge *bridge,
				      स्थिर काष्ठा drm_display_info *info,
				      स्थिर काष्ठा drm_display_mode *mode)
अणु
	काष्ठा mtk_hdmi *hdmi = hdmi_ctx_from_bridge(bridge);
	काष्ठा drm_bridge *next_bridge;

	dev_dbg(hdmi->dev, "xres=%d, yres=%d, refresh=%d, intl=%d clock=%d\n",
		mode->hdisplay, mode->vdisplay, drm_mode_vrefresh(mode),
		!!(mode->flags & DRM_MODE_FLAG_INTERLACE), mode->घड़ी * 1000);

	next_bridge = drm_bridge_get_next_bridge(&hdmi->bridge);
	अगर (next_bridge) अणु
		काष्ठा drm_display_mode adjusted_mode;

		drm_mode_copy(&adjusted_mode, mode);
		अगर (!drm_bridge_chain_mode_fixup(next_bridge, mode,
						 &adjusted_mode))
			वापस MODE_BAD;
	पूर्ण

	अगर (mode->घड़ी < 27000)
		वापस MODE_CLOCK_LOW;
	अगर (mode->घड़ी > 297000)
		वापस MODE_CLOCK_HIGH;

	वापस drm_mode_validate_size(mode, 0x1fff, 0x1fff);
पूर्ण

अटल व्योम mtk_hdmi_hpd_event(bool hpd, काष्ठा device *dev)
अणु
	काष्ठा mtk_hdmi *hdmi = dev_get_drvdata(dev);

	अगर (hdmi && hdmi->bridge.encoder && hdmi->bridge.encoder->dev) अणु
		अटल क्रमागत drm_connector_status status;

		status = mtk_hdmi_detect(hdmi);
		drm_helper_hpd_irq_event(hdmi->bridge.encoder->dev);
		drm_bridge_hpd_notअगरy(&hdmi->bridge, status);
	पूर्ण
पूर्ण

/*
 * Bridge callbacks
 */

अटल क्रमागत drm_connector_status mtk_hdmi_bridge_detect(काष्ठा drm_bridge *bridge)
अणु
	काष्ठा mtk_hdmi *hdmi = hdmi_ctx_from_bridge(bridge);

	वापस mtk_hdmi_detect(hdmi);
पूर्ण

अटल काष्ठा edid *mtk_hdmi_bridge_get_edid(काष्ठा drm_bridge *bridge,
					     काष्ठा drm_connector *connector)
अणु
	काष्ठा mtk_hdmi *hdmi = hdmi_ctx_from_bridge(bridge);
	काष्ठा edid *edid;

	अगर (!hdmi->ddc_adpt)
		वापस शून्य;
	edid = drm_get_edid(connector, hdmi->ddc_adpt);
	अगर (!edid)
		वापस शून्य;
	hdmi->dvi_mode = !drm_detect_monitor_audio(edid);
	वापस edid;
पूर्ण

अटल पूर्णांक mtk_hdmi_bridge_attach(काष्ठा drm_bridge *bridge,
				  क्रमागत drm_bridge_attach_flags flags)
अणु
	काष्ठा mtk_hdmi *hdmi = hdmi_ctx_from_bridge(bridge);
	पूर्णांक ret;

	अगर (!(flags & DRM_BRIDGE_ATTACH_NO_CONNECTOR)) अणु
		DRM_ERROR("%s: The flag DRM_BRIDGE_ATTACH_NO_CONNECTOR must be supplied\n",
			  __func__);
		वापस -EINVAL;
	पूर्ण

	अगर (hdmi->next_bridge) अणु
		ret = drm_bridge_attach(bridge->encoder, hdmi->next_bridge,
					bridge, flags);
		अगर (ret) अणु
			dev_err(hdmi->dev,
				"Failed to attach external bridge: %d\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण

	mtk_cec_set_hpd_event(hdmi->cec_dev, mtk_hdmi_hpd_event, hdmi->dev);

	वापस 0;
पूर्ण

अटल bool mtk_hdmi_bridge_mode_fixup(काष्ठा drm_bridge *bridge,
				       स्थिर काष्ठा drm_display_mode *mode,
				       काष्ठा drm_display_mode *adjusted_mode)
अणु
	वापस true;
पूर्ण

अटल व्योम mtk_hdmi_bridge_atomic_disable(काष्ठा drm_bridge *bridge,
					   काष्ठा drm_bridge_state *old_bridge_state)
अणु
	काष्ठा mtk_hdmi *hdmi = hdmi_ctx_from_bridge(bridge);

	अगर (!hdmi->enabled)
		वापस;

	phy_घातer_off(hdmi->phy);
	clk_disable_unprepare(hdmi->clk[MTK_HDMI_CLK_HDMI_PIXEL]);
	clk_disable_unprepare(hdmi->clk[MTK_HDMI_CLK_HDMI_PLL]);

	hdmi->curr_conn = शून्य;

	hdmi->enabled = false;
पूर्ण

अटल व्योम mtk_hdmi_bridge_atomic_post_disable(काष्ठा drm_bridge *bridge,
						काष्ठा drm_bridge_state *old_state)
अणु
	काष्ठा mtk_hdmi *hdmi = hdmi_ctx_from_bridge(bridge);

	अगर (!hdmi->घातered)
		वापस;

	mtk_hdmi_hw_1p4_version_enable(hdmi, true);
	mtk_hdmi_hw_make_reg_writable(hdmi, false);

	hdmi->घातered = false;
पूर्ण

अटल व्योम mtk_hdmi_bridge_mode_set(काष्ठा drm_bridge *bridge,
				स्थिर काष्ठा drm_display_mode *mode,
				स्थिर काष्ठा drm_display_mode *adjusted_mode)
अणु
	काष्ठा mtk_hdmi *hdmi = hdmi_ctx_from_bridge(bridge);

	dev_dbg(hdmi->dev, "cur info: name:%s, hdisplay:%d\n",
		adjusted_mode->name, adjusted_mode->hdisplay);
	dev_dbg(hdmi->dev, "hsync_start:%d,hsync_end:%d, htotal:%d",
		adjusted_mode->hsync_start, adjusted_mode->hsync_end,
		adjusted_mode->htotal);
	dev_dbg(hdmi->dev, "hskew:%d, vdisplay:%d\n",
		adjusted_mode->hskew, adjusted_mode->vdisplay);
	dev_dbg(hdmi->dev, "vsync_start:%d, vsync_end:%d, vtotal:%d",
		adjusted_mode->vsync_start, adjusted_mode->vsync_end,
		adjusted_mode->vtotal);
	dev_dbg(hdmi->dev, "vscan:%d, flag:%d\n",
		adjusted_mode->vscan, adjusted_mode->flags);

	drm_mode_copy(&hdmi->mode, adjusted_mode);
पूर्ण

अटल व्योम mtk_hdmi_bridge_atomic_pre_enable(काष्ठा drm_bridge *bridge,
					      काष्ठा drm_bridge_state *old_state)
अणु
	काष्ठा mtk_hdmi *hdmi = hdmi_ctx_from_bridge(bridge);

	mtk_hdmi_hw_make_reg_writable(hdmi, true);
	mtk_hdmi_hw_1p4_version_enable(hdmi, true);

	hdmi->घातered = true;
पूर्ण

अटल व्योम mtk_hdmi_send_infoframe(काष्ठा mtk_hdmi *hdmi,
				    काष्ठा drm_display_mode *mode)
अणु
	mtk_hdmi_setup_audio_infoframe(hdmi);
	mtk_hdmi_setup_avi_infoframe(hdmi, mode);
	mtk_hdmi_setup_spd_infoframe(hdmi, "mediatek", "On-chip HDMI");
	अगर (mode->flags & DRM_MODE_FLAG_3D_MASK)
		mtk_hdmi_setup_venकरोr_specअगरic_infoframe(hdmi, mode);
पूर्ण

अटल व्योम mtk_hdmi_bridge_atomic_enable(काष्ठा drm_bridge *bridge,
					  काष्ठा drm_bridge_state *old_state)
अणु
	काष्ठा drm_atomic_state *state = old_state->base.state;
	काष्ठा mtk_hdmi *hdmi = hdmi_ctx_from_bridge(bridge);

	/* Retrieve the connector through the atomic state. */
	hdmi->curr_conn = drm_atomic_get_new_connector_क्रम_encoder(state,
								   bridge->encoder);

	mtk_hdmi_output_set_display_mode(hdmi, &hdmi->mode);
	clk_prepare_enable(hdmi->clk[MTK_HDMI_CLK_HDMI_PLL]);
	clk_prepare_enable(hdmi->clk[MTK_HDMI_CLK_HDMI_PIXEL]);
	phy_घातer_on(hdmi->phy);
	mtk_hdmi_send_infoframe(hdmi, &hdmi->mode);

	hdmi->enabled = true;
पूर्ण

अटल स्थिर काष्ठा drm_bridge_funcs mtk_hdmi_bridge_funcs = अणु
	.mode_valid = mtk_hdmi_bridge_mode_valid,
	.atomic_duplicate_state = drm_atomic_helper_bridge_duplicate_state,
	.atomic_destroy_state = drm_atomic_helper_bridge_destroy_state,
	.atomic_reset = drm_atomic_helper_bridge_reset,
	.attach = mtk_hdmi_bridge_attach,
	.mode_fixup = mtk_hdmi_bridge_mode_fixup,
	.atomic_disable = mtk_hdmi_bridge_atomic_disable,
	.atomic_post_disable = mtk_hdmi_bridge_atomic_post_disable,
	.mode_set = mtk_hdmi_bridge_mode_set,
	.atomic_pre_enable = mtk_hdmi_bridge_atomic_pre_enable,
	.atomic_enable = mtk_hdmi_bridge_atomic_enable,
	.detect = mtk_hdmi_bridge_detect,
	.get_edid = mtk_hdmi_bridge_get_edid,
पूर्ण;

अटल पूर्णांक mtk_hdmi_dt_parse_pdata(काष्ठा mtk_hdmi *hdmi,
				   काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *np = dev->of_node;
	काष्ठा device_node *cec_np, *remote, *i2c_np;
	काष्ठा platक्रमm_device *cec_pdev;
	काष्ठा regmap *regmap;
	काष्ठा resource *mem;
	पूर्णांक ret;

	ret = mtk_hdmi_get_all_clk(hdmi, np);
	अगर (ret) अणु
		अगर (ret != -EPROBE_DEFER)
			dev_err(dev, "Failed to get clocks: %d\n", ret);

		वापस ret;
	पूर्ण

	/* The CEC module handles HDMI hotplug detection */
	cec_np = of_get_compatible_child(np->parent, "mediatek,mt8173-cec");
	अगर (!cec_np) अणु
		dev_err(dev, "Failed to find CEC node\n");
		वापस -EINVAL;
	पूर्ण

	cec_pdev = of_find_device_by_node(cec_np);
	अगर (!cec_pdev) अणु
		dev_err(hdmi->dev, "Waiting for CEC device %pOF\n",
			cec_np);
		of_node_put(cec_np);
		वापस -EPROBE_DEFER;
	पूर्ण
	of_node_put(cec_np);
	hdmi->cec_dev = &cec_pdev->dev;

	/*
	 * The mediatek,syscon-hdmi property contains a phandle link to the
	 * MMSYS_CONFIG device and the रेजिस्टर offset of the HDMI_SYS_CFG
	 * रेजिस्टरs it contains.
	 */
	regmap = syscon_regmap_lookup_by_phandle(np, "mediatek,syscon-hdmi");
	ret = of_property_पढ़ो_u32_index(np, "mediatek,syscon-hdmi", 1,
					 &hdmi->sys_offset);
	अगर (IS_ERR(regmap))
		ret = PTR_ERR(regmap);
	अगर (ret) अणु
		dev_err(dev,
			"Failed to get system configuration registers: %d\n",
			ret);
		जाओ put_device;
	पूर्ण
	hdmi->sys_regmap = regmap;

	mem = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	hdmi->regs = devm_ioremap_resource(dev, mem);
	अगर (IS_ERR(hdmi->regs)) अणु
		ret = PTR_ERR(hdmi->regs);
		जाओ put_device;
	पूर्ण

	remote = of_graph_get_remote_node(np, 1, 0);
	अगर (!remote) अणु
		ret = -EINVAL;
		जाओ put_device;
	पूर्ण

	अगर (!of_device_is_compatible(remote, "hdmi-connector")) अणु
		hdmi->next_bridge = of_drm_find_bridge(remote);
		अगर (!hdmi->next_bridge) अणु
			dev_err(dev, "Waiting for external bridge\n");
			of_node_put(remote);
			ret = -EPROBE_DEFER;
			जाओ put_device;
		पूर्ण
	पूर्ण

	i2c_np = of_parse_phandle(remote, "ddc-i2c-bus", 0);
	अगर (!i2c_np) अणु
		dev_err(dev, "Failed to find ddc-i2c-bus node in %pOF\n",
			remote);
		of_node_put(remote);
		ret = -EINVAL;
		जाओ put_device;
	पूर्ण
	of_node_put(remote);

	hdmi->ddc_adpt = of_find_i2c_adapter_by_node(i2c_np);
	of_node_put(i2c_np);
	अगर (!hdmi->ddc_adpt) अणु
		dev_err(dev, "Failed to get ddc i2c adapter by node\n");
		ret = -EINVAL;
		जाओ put_device;
	पूर्ण

	वापस 0;
put_device:
	put_device(hdmi->cec_dev);
	वापस ret;
पूर्ण

/*
 * HDMI audio codec callbacks
 */

अटल पूर्णांक mtk_hdmi_audio_hw_params(काष्ठा device *dev, व्योम *data,
				    काष्ठा hdmi_codec_daअगरmt *daअगरmt,
				    काष्ठा hdmi_codec_params *params)
अणु
	काष्ठा mtk_hdmi *hdmi = dev_get_drvdata(dev);
	काष्ठा hdmi_audio_param hdmi_params;
	अचिन्हित पूर्णांक chan = params->cea.channels;

	dev_dbg(hdmi->dev, "%s: %u Hz, %d bit, %d channels\n", __func__,
		params->sample_rate, params->sample_width, chan);

	अगर (!hdmi->bridge.encoder)
		वापस -ENODEV;

	चयन (chan) अणु
	हाल 2:
		hdmi_params.aud_input_chan_type = HDMI_AUD_CHAN_TYPE_2_0;
		अवरोध;
	हाल 4:
		hdmi_params.aud_input_chan_type = HDMI_AUD_CHAN_TYPE_4_0;
		अवरोध;
	हाल 6:
		hdmi_params.aud_input_chan_type = HDMI_AUD_CHAN_TYPE_5_1;
		अवरोध;
	हाल 8:
		hdmi_params.aud_input_chan_type = HDMI_AUD_CHAN_TYPE_7_1;
		अवरोध;
	शेष:
		dev_err(hdmi->dev, "channel[%d] not supported!\n", chan);
		वापस -EINVAL;
	पूर्ण

	चयन (params->sample_rate) अणु
	हाल 32000:
	हाल 44100:
	हाल 48000:
	हाल 88200:
	हाल 96000:
	हाल 176400:
	हाल 192000:
		अवरोध;
	शेष:
		dev_err(hdmi->dev, "rate[%d] not supported!\n",
			params->sample_rate);
		वापस -EINVAL;
	पूर्ण

	चयन (daअगरmt->fmt) अणु
	हाल HDMI_I2S:
		hdmi_params.aud_codec = HDMI_AUDIO_CODING_TYPE_PCM;
		hdmi_params.aud_sampe_size = HDMI_AUDIO_SAMPLE_SIZE_16;
		hdmi_params.aud_input_type = HDMI_AUD_INPUT_I2S;
		hdmi_params.aud_i2s_fmt = HDMI_I2S_MODE_I2S_24BIT;
		hdmi_params.aud_mclk = HDMI_AUD_MCLK_128FS;
		अवरोध;
	हाल HDMI_SPDIF:
		hdmi_params.aud_codec = HDMI_AUDIO_CODING_TYPE_PCM;
		hdmi_params.aud_sampe_size = HDMI_AUDIO_SAMPLE_SIZE_16;
		hdmi_params.aud_input_type = HDMI_AUD_INPUT_SPDIF;
		अवरोध;
	शेष:
		dev_err(hdmi->dev, "%s: Invalid DAI format %d\n", __func__,
			daअगरmt->fmt);
		वापस -EINVAL;
	पूर्ण

	स_नकल(&hdmi_params.codec_params, params,
	       माप(hdmi_params.codec_params));

	mtk_hdmi_audio_set_param(hdmi, &hdmi_params);

	वापस 0;
पूर्ण

अटल पूर्णांक mtk_hdmi_audio_startup(काष्ठा device *dev, व्योम *data)
अणु
	काष्ठा mtk_hdmi *hdmi = dev_get_drvdata(dev);

	mtk_hdmi_audio_enable(hdmi);

	वापस 0;
पूर्ण

अटल व्योम mtk_hdmi_audio_shutकरोwn(काष्ठा device *dev, व्योम *data)
अणु
	काष्ठा mtk_hdmi *hdmi = dev_get_drvdata(dev);

	mtk_hdmi_audio_disable(hdmi);
पूर्ण

अटल पूर्णांक
mtk_hdmi_audio_mute(काष्ठा device *dev, व्योम *data,
		    bool enable, पूर्णांक direction)
अणु
	काष्ठा mtk_hdmi *hdmi = dev_get_drvdata(dev);

	अगर (enable)
		mtk_hdmi_hw_aud_mute(hdmi);
	अन्यथा
		mtk_hdmi_hw_aud_unmute(hdmi);

	वापस 0;
पूर्ण

अटल पूर्णांक mtk_hdmi_audio_get_eld(काष्ठा device *dev, व्योम *data, uपूर्णांक8_t *buf, माप_प्रकार len)
अणु
	काष्ठा mtk_hdmi *hdmi = dev_get_drvdata(dev);

	अगर (hdmi->enabled)
		स_नकल(buf, hdmi->curr_conn->eld, min(माप(hdmi->curr_conn->eld), len));
	अन्यथा
		स_रखो(buf, 0, len);
	वापस 0;
पूर्ण

अटल पूर्णांक mtk_hdmi_audio_hook_plugged_cb(काष्ठा device *dev, व्योम *data,
					  hdmi_codec_plugged_cb fn,
					  काष्ठा device *codec_dev)
अणु
	काष्ठा mtk_hdmi *hdmi = data;

	mutex_lock(&hdmi->update_plugged_status_lock);
	hdmi->plugged_cb = fn;
	hdmi->codec_dev = codec_dev;
	mutex_unlock(&hdmi->update_plugged_status_lock);

	mtk_hdmi_update_plugged_status(hdmi);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा hdmi_codec_ops mtk_hdmi_audio_codec_ops = अणु
	.hw_params = mtk_hdmi_audio_hw_params,
	.audio_startup = mtk_hdmi_audio_startup,
	.audio_shutकरोwn = mtk_hdmi_audio_shutकरोwn,
	.mute_stream = mtk_hdmi_audio_mute,
	.get_eld = mtk_hdmi_audio_get_eld,
	.hook_plugged_cb = mtk_hdmi_audio_hook_plugged_cb,
	.no_capture_mute = 1,
पूर्ण;

अटल पूर्णांक mtk_hdmi_रेजिस्टर_audio_driver(काष्ठा device *dev)
अणु
	काष्ठा mtk_hdmi *hdmi = dev_get_drvdata(dev);
	काष्ठा hdmi_codec_pdata codec_data = अणु
		.ops = &mtk_hdmi_audio_codec_ops,
		.max_i2s_channels = 2,
		.i2s = 1,
		.data = hdmi,
	पूर्ण;
	काष्ठा platक्रमm_device *pdev;

	pdev = platक्रमm_device_रेजिस्टर_data(dev, HDMI_CODEC_DRV_NAME,
					     PLATFORM_DEVID_AUTO, &codec_data,
					     माप(codec_data));
	अगर (IS_ERR(pdev))
		वापस PTR_ERR(pdev);

	DRM_INFO("%s driver bound to HDMI\n", HDMI_CODEC_DRV_NAME);
	वापस 0;
पूर्ण

अटल पूर्णांक mtk_drm_hdmi_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mtk_hdmi *hdmi;
	काष्ठा device *dev = &pdev->dev;
	पूर्णांक ret;

	hdmi = devm_kzalloc(dev, माप(*hdmi), GFP_KERNEL);
	अगर (!hdmi)
		वापस -ENOMEM;

	hdmi->dev = dev;
	hdmi->conf = of_device_get_match_data(dev);

	ret = mtk_hdmi_dt_parse_pdata(hdmi, pdev);
	अगर (ret)
		वापस ret;

	hdmi->phy = devm_phy_get(dev, "hdmi");
	अगर (IS_ERR(hdmi->phy)) अणु
		ret = PTR_ERR(hdmi->phy);
		dev_err(dev, "Failed to get HDMI PHY: %d\n", ret);
		वापस ret;
	पूर्ण

	mutex_init(&hdmi->update_plugged_status_lock);
	platक्रमm_set_drvdata(pdev, hdmi);

	ret = mtk_hdmi_output_init(hdmi);
	अगर (ret) अणु
		dev_err(dev, "Failed to initialize hdmi output\n");
		वापस ret;
	पूर्ण

	ret = mtk_hdmi_रेजिस्टर_audio_driver(dev);
	अगर (ret) अणु
		dev_err(dev, "Failed to register audio driver: %d\n", ret);
		वापस ret;
	पूर्ण

	hdmi->bridge.funcs = &mtk_hdmi_bridge_funcs;
	hdmi->bridge.of_node = pdev->dev.of_node;
	hdmi->bridge.ops = DRM_BRIDGE_OP_DETECT | DRM_BRIDGE_OP_EDID
			 | DRM_BRIDGE_OP_HPD;
	hdmi->bridge.type = DRM_MODE_CONNECTOR_HDMIA;
	drm_bridge_add(&hdmi->bridge);

	ret = mtk_hdmi_clk_enable_audio(hdmi);
	अगर (ret) अणु
		dev_err(dev, "Failed to enable audio clocks: %d\n", ret);
		जाओ err_bridge_हटाओ;
	पूर्ण

	वापस 0;

err_bridge_हटाओ:
	drm_bridge_हटाओ(&hdmi->bridge);
	वापस ret;
पूर्ण

अटल पूर्णांक mtk_drm_hdmi_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mtk_hdmi *hdmi = platक्रमm_get_drvdata(pdev);

	drm_bridge_हटाओ(&hdmi->bridge);
	mtk_hdmi_clk_disable_audio(hdmi);
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक mtk_hdmi_suspend(काष्ठा device *dev)
अणु
	काष्ठा mtk_hdmi *hdmi = dev_get_drvdata(dev);

	mtk_hdmi_clk_disable_audio(hdmi);

	वापस 0;
पूर्ण

अटल पूर्णांक mtk_hdmi_resume(काष्ठा device *dev)
अणु
	काष्ठा mtk_hdmi *hdmi = dev_get_drvdata(dev);
	पूर्णांक ret = 0;

	ret = mtk_hdmi_clk_enable_audio(hdmi);
	अगर (ret) अणु
		dev_err(dev, "hdmi resume failed!\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण
#पूर्ण_अगर
अटल SIMPLE_DEV_PM_OPS(mtk_hdmi_pm_ops,
			 mtk_hdmi_suspend, mtk_hdmi_resume);

अटल स्थिर काष्ठा mtk_hdmi_conf mtk_hdmi_conf_mt2701 = अणु
	.tz_disabled = true,
पूर्ण;

अटल स्थिर काष्ठा of_device_id mtk_drm_hdmi_of_ids[] = अणु
	अणु .compatible = "mediatek,mt2701-hdmi",
	  .data = &mtk_hdmi_conf_mt2701,
	पूर्ण,
	अणु .compatible = "mediatek,mt8173-hdmi",
	पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, mtk_drm_hdmi_of_ids);

अटल काष्ठा platक्रमm_driver mtk_hdmi_driver = अणु
	.probe = mtk_drm_hdmi_probe,
	.हटाओ = mtk_drm_hdmi_हटाओ,
	.driver = अणु
		.name = "mediatek-drm-hdmi",
		.of_match_table = mtk_drm_hdmi_of_ids,
		.pm = &mtk_hdmi_pm_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver * स्थिर mtk_hdmi_drivers[] = अणु
	&mtk_hdmi_ddc_driver,
	&mtk_cec_driver,
	&mtk_hdmi_driver,
पूर्ण;

अटल पूर्णांक __init mtk_hdmitx_init(व्योम)
अणु
	वापस platक्रमm_रेजिस्टर_drivers(mtk_hdmi_drivers,
					 ARRAY_SIZE(mtk_hdmi_drivers));
पूर्ण

अटल व्योम __निकास mtk_hdmitx_निकास(व्योम)
अणु
	platक्रमm_unरेजिस्टर_drivers(mtk_hdmi_drivers,
				    ARRAY_SIZE(mtk_hdmi_drivers));
पूर्ण

module_init(mtk_hdmitx_init);
module_निकास(mtk_hdmitx_निकास);

MODULE_AUTHOR("Jie Qiu <jie.qiu@mediatek.com>");
MODULE_DESCRIPTION("MediaTek HDMI Driver");
MODULE_LICENSE("GPL v2");
