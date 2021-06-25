<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright 2016 Linaro Ltd.
 * Copyright 2016 ZTE Corporation.
 */

#समावेश <linux/clk.h>
#समावेश <linux/component.h>
#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/hdmi.h>
#समावेश <linux/irq.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/of_device.h>

#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_edid.h>
#समावेश <drm/drm_of.h>
#समावेश <drm/drm_probe_helper.h>
#समावेश <drm/drm_prपूर्णांक.h>
#समावेश <drm/drm_simple_kms_helper.h>

#समावेश <sound/hdmi-codec.h>

#समावेश "zx_hdmi_regs.h"
#समावेश "zx_vou.h"

#घोषणा ZX_HDMI_INFOFRAME_SIZE		31
#घोषणा DDC_SEGMENT_ADDR		0x30

काष्ठा zx_hdmi_i2c अणु
	काष्ठा i2c_adapter adap;
	काष्ठा mutex lock;
पूर्ण;

काष्ठा zx_hdmi अणु
	काष्ठा drm_connector connector;
	काष्ठा drm_encoder encoder;
	काष्ठा zx_hdmi_i2c *ddc;
	काष्ठा device *dev;
	काष्ठा drm_device *drm;
	व्योम __iomem *mmio;
	काष्ठा clk *cec_clk;
	काष्ठा clk *osc_clk;
	काष्ठा clk *xclk;
	bool sink_is_hdmi;
	bool sink_has_audio;
	काष्ठा platक्रमm_device *audio_pdev;
पूर्ण;

#घोषणा to_zx_hdmi(x) container_of(x, काष्ठा zx_hdmi, x)

अटल अंतरभूत u8 hdmi_पढ़ोb(काष्ठा zx_hdmi *hdmi, u16 offset)
अणु
	वापस पढ़ोl_relaxed(hdmi->mmio + offset * 4);
पूर्ण

अटल अंतरभूत व्योम hdmi_ग_लिखोb(काष्ठा zx_hdmi *hdmi, u16 offset, u8 val)
अणु
	ग_लिखोl_relaxed(val, hdmi->mmio + offset * 4);
पूर्ण

अटल अंतरभूत व्योम hdmi_ग_लिखोb_mask(काष्ठा zx_hdmi *hdmi, u16 offset,
				    u8 mask, u8 val)
अणु
	u8 पंचांगp;

	पंचांगp = hdmi_पढ़ोb(hdmi, offset);
	पंचांगp = (पंचांगp & ~mask) | (val & mask);
	hdmi_ग_लिखोb(hdmi, offset, पंचांगp);
पूर्ण

अटल पूर्णांक zx_hdmi_infoframe_trans(काष्ठा zx_hdmi *hdmi,
				   जोड़ hdmi_infoframe *frame, u8 fsel)
अणु
	u8 buffer[ZX_HDMI_INFOFRAME_SIZE];
	पूर्णांक num;
	पूर्णांक i;

	hdmi_ग_लिखोb(hdmi, TPI_INFO_FSEL, fsel);

	num = hdmi_infoframe_pack(frame, buffer, ZX_HDMI_INFOFRAME_SIZE);
	अगर (num < 0) अणु
		DRM_DEV_ERROR(hdmi->dev, "failed to pack infoframe: %d\n", num);
		वापस num;
	पूर्ण

	क्रम (i = 0; i < num; i++)
		hdmi_ग_लिखोb(hdmi, TPI_INFO_B0 + i, buffer[i]);

	hdmi_ग_लिखोb_mask(hdmi, TPI_INFO_EN, TPI_INFO_TRANS_RPT,
			 TPI_INFO_TRANS_RPT);
	hdmi_ग_लिखोb_mask(hdmi, TPI_INFO_EN, TPI_INFO_TRANS_EN,
			 TPI_INFO_TRANS_EN);

	वापस num;
पूर्ण

अटल पूर्णांक zx_hdmi_config_video_vsi(काष्ठा zx_hdmi *hdmi,
				    काष्ठा drm_display_mode *mode)
अणु
	जोड़ hdmi_infoframe frame;
	पूर्णांक ret;

	ret = drm_hdmi_venकरोr_infoframe_from_display_mode(&frame.venकरोr.hdmi,
							  &hdmi->connector,
							  mode);
	अगर (ret) अणु
		DRM_DEV_ERROR(hdmi->dev, "failed to get vendor infoframe: %d\n",
			      ret);
		वापस ret;
	पूर्ण

	वापस zx_hdmi_infoframe_trans(hdmi, &frame, FSEL_VSIF);
पूर्ण

अटल पूर्णांक zx_hdmi_config_video_avi(काष्ठा zx_hdmi *hdmi,
				    काष्ठा drm_display_mode *mode)
अणु
	जोड़ hdmi_infoframe frame;
	पूर्णांक ret;

	ret = drm_hdmi_avi_infoframe_from_display_mode(&frame.avi,
						       &hdmi->connector,
						       mode);
	अगर (ret) अणु
		DRM_DEV_ERROR(hdmi->dev, "failed to get avi infoframe: %d\n",
			      ret);
		वापस ret;
	पूर्ण

	/* We always use YUV444 क्रम HDMI output. */
	frame.avi.colorspace = HDMI_COLORSPACE_YUV444;

	वापस zx_hdmi_infoframe_trans(hdmi, &frame, FSEL_AVI);
पूर्ण

अटल व्योम zx_hdmi_encoder_mode_set(काष्ठा drm_encoder *encoder,
				     काष्ठा drm_display_mode *mode,
				     काष्ठा drm_display_mode *adj_mode)
अणु
	काष्ठा zx_hdmi *hdmi = to_zx_hdmi(encoder);

	अगर (hdmi->sink_is_hdmi) अणु
		zx_hdmi_config_video_avi(hdmi, mode);
		zx_hdmi_config_video_vsi(hdmi, mode);
	पूर्ण
पूर्ण

अटल व्योम zx_hdmi_phy_start(काष्ठा zx_hdmi *hdmi)
अणु
	/* Copy from ZTE BSP code */
	hdmi_ग_लिखोb(hdmi, 0x222, 0x0);
	hdmi_ग_लिखोb(hdmi, 0x224, 0x4);
	hdmi_ग_लिखोb(hdmi, 0x909, 0x0);
	hdmi_ग_लिखोb(hdmi, 0x7b0, 0x90);
	hdmi_ग_लिखोb(hdmi, 0x7b1, 0x00);
	hdmi_ग_लिखोb(hdmi, 0x7b2, 0xa7);
	hdmi_ग_लिखोb(hdmi, 0x7b8, 0xaa);
	hdmi_ग_लिखोb(hdmi, 0x7b2, 0xa7);
	hdmi_ग_लिखोb(hdmi, 0x7b3, 0x0f);
	hdmi_ग_लिखोb(hdmi, 0x7b4, 0x0f);
	hdmi_ग_लिखोb(hdmi, 0x7b5, 0x55);
	hdmi_ग_लिखोb(hdmi, 0x7b7, 0x03);
	hdmi_ग_लिखोb(hdmi, 0x7b9, 0x12);
	hdmi_ग_लिखोb(hdmi, 0x7ba, 0x32);
	hdmi_ग_लिखोb(hdmi, 0x7bc, 0x68);
	hdmi_ग_लिखोb(hdmi, 0x7be, 0x40);
	hdmi_ग_लिखोb(hdmi, 0x7bf, 0x84);
	hdmi_ग_लिखोb(hdmi, 0x7c1, 0x0f);
	hdmi_ग_लिखोb(hdmi, 0x7c8, 0x02);
	hdmi_ग_लिखोb(hdmi, 0x7c9, 0x03);
	hdmi_ग_लिखोb(hdmi, 0x7ca, 0x40);
	hdmi_ग_लिखोb(hdmi, 0x7dc, 0x31);
	hdmi_ग_लिखोb(hdmi, 0x7e2, 0x04);
	hdmi_ग_लिखोb(hdmi, 0x7e0, 0x06);
	hdmi_ग_लिखोb(hdmi, 0x7cb, 0x68);
	hdmi_ग_लिखोb(hdmi, 0x7f9, 0x02);
	hdmi_ग_लिखोb(hdmi, 0x7b6, 0x02);
	hdmi_ग_लिखोb(hdmi, 0x7f3, 0x0);
पूर्ण

अटल व्योम zx_hdmi_hw_enable(काष्ठा zx_hdmi *hdmi)
अणु
	/* Enable pclk */
	hdmi_ग_लिखोb_mask(hdmi, CLKPWD, CLKPWD_PDIDCK, CLKPWD_PDIDCK);

	/* Enable HDMI क्रम TX */
	hdmi_ग_लिखोb_mask(hdmi, FUNC_SEL, FUNC_HDMI_EN, FUNC_HDMI_EN);

	/* Enable deep color packet */
	hdmi_ग_लिखोb_mask(hdmi, P2T_CTRL, P2T_DC_PKT_EN, P2T_DC_PKT_EN);

	/* Enable HDMI/MHL mode क्रम output */
	hdmi_ग_लिखोb_mask(hdmi, TEST_TXCTRL, TEST_TXCTRL_HDMI_MODE,
			 TEST_TXCTRL_HDMI_MODE);

	/* Configure reg_qc_sel */
	hdmi_ग_लिखोb(hdmi, HDMICTL4, 0x3);

	/* Enable पूर्णांकerrupt */
	hdmi_ग_लिखोb_mask(hdmi, INTR1_MASK, INTR1_MONITOR_DETECT,
			 INTR1_MONITOR_DETECT);

	/* Start up phy */
	zx_hdmi_phy_start(hdmi);
पूर्ण

अटल व्योम zx_hdmi_hw_disable(काष्ठा zx_hdmi *hdmi)
अणु
	/* Disable पूर्णांकerrupt */
	hdmi_ग_लिखोb_mask(hdmi, INTR1_MASK, INTR1_MONITOR_DETECT, 0);

	/* Disable deep color packet */
	hdmi_ग_लिखोb_mask(hdmi, P2T_CTRL, P2T_DC_PKT_EN, P2T_DC_PKT_EN);

	/* Disable HDMI क्रम TX */
	hdmi_ग_लिखोb_mask(hdmi, FUNC_SEL, FUNC_HDMI_EN, 0);

	/* Disable pclk */
	hdmi_ग_लिखोb_mask(hdmi, CLKPWD, CLKPWD_PDIDCK, 0);
पूर्ण

अटल व्योम zx_hdmi_encoder_enable(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा zx_hdmi *hdmi = to_zx_hdmi(encoder);

	clk_prepare_enable(hdmi->cec_clk);
	clk_prepare_enable(hdmi->osc_clk);
	clk_prepare_enable(hdmi->xclk);

	zx_hdmi_hw_enable(hdmi);

	vou_inf_enable(VOU_HDMI, encoder->crtc);
पूर्ण

अटल व्योम zx_hdmi_encoder_disable(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा zx_hdmi *hdmi = to_zx_hdmi(encoder);

	vou_inf_disable(VOU_HDMI, encoder->crtc);

	zx_hdmi_hw_disable(hdmi);

	clk_disable_unprepare(hdmi->xclk);
	clk_disable_unprepare(hdmi->osc_clk);
	clk_disable_unprepare(hdmi->cec_clk);
पूर्ण

अटल स्थिर काष्ठा drm_encoder_helper_funcs zx_hdmi_encoder_helper_funcs = अणु
	.enable	= zx_hdmi_encoder_enable,
	.disable = zx_hdmi_encoder_disable,
	.mode_set = zx_hdmi_encoder_mode_set,
पूर्ण;

अटल पूर्णांक zx_hdmi_connector_get_modes(काष्ठा drm_connector *connector)
अणु
	काष्ठा zx_hdmi *hdmi = to_zx_hdmi(connector);
	काष्ठा edid *edid;
	पूर्णांक ret;

	edid = drm_get_edid(connector, &hdmi->ddc->adap);
	अगर (!edid)
		वापस 0;

	hdmi->sink_is_hdmi = drm_detect_hdmi_monitor(edid);
	hdmi->sink_has_audio = drm_detect_monitor_audio(edid);
	drm_connector_update_edid_property(connector, edid);
	ret = drm_add_edid_modes(connector, edid);
	kमुक्त(edid);

	वापस ret;
पूर्ण

अटल क्रमागत drm_mode_status
zx_hdmi_connector_mode_valid(काष्ठा drm_connector *connector,
			     काष्ठा drm_display_mode *mode)
अणु
	वापस MODE_OK;
पूर्ण

अटल काष्ठा drm_connector_helper_funcs zx_hdmi_connector_helper_funcs = अणु
	.get_modes = zx_hdmi_connector_get_modes,
	.mode_valid = zx_hdmi_connector_mode_valid,
पूर्ण;

अटल क्रमागत drm_connector_status
zx_hdmi_connector_detect(काष्ठा drm_connector *connector, bool क्रमce)
अणु
	काष्ठा zx_hdmi *hdmi = to_zx_hdmi(connector);

	वापस (hdmi_पढ़ोb(hdmi, TPI_HPD_RSEN) & TPI_HPD_CONNECTION) ?
		connector_status_connected : connector_status_disconnected;
पूर्ण

अटल स्थिर काष्ठा drm_connector_funcs zx_hdmi_connector_funcs = अणु
	.fill_modes = drm_helper_probe_single_connector_modes,
	.detect = zx_hdmi_connector_detect,
	.destroy = drm_connector_cleanup,
	.reset = drm_atomic_helper_connector_reset,
	.atomic_duplicate_state = drm_atomic_helper_connector_duplicate_state,
	.atomic_destroy_state = drm_atomic_helper_connector_destroy_state,
पूर्ण;

अटल पूर्णांक zx_hdmi_रेजिस्टर(काष्ठा drm_device *drm, काष्ठा zx_hdmi *hdmi)
अणु
	काष्ठा drm_encoder *encoder = &hdmi->encoder;

	encoder->possible_crtcs = VOU_CRTC_MASK;

	drm_simple_encoder_init(drm, encoder, DRM_MODE_ENCODER_TMDS);
	drm_encoder_helper_add(encoder, &zx_hdmi_encoder_helper_funcs);

	hdmi->connector.polled = DRM_CONNECTOR_POLL_HPD;

	drm_connector_init_with_ddc(drm, &hdmi->connector,
				    &zx_hdmi_connector_funcs,
				    DRM_MODE_CONNECTOR_HDMIA,
				    &hdmi->ddc->adap);
	drm_connector_helper_add(&hdmi->connector,
				 &zx_hdmi_connector_helper_funcs);

	drm_connector_attach_encoder(&hdmi->connector, encoder);

	वापस 0;
पूर्ण

अटल irqवापस_t zx_hdmi_irq_thपढ़ो(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा zx_hdmi *hdmi = dev_id;

	drm_helper_hpd_irq_event(hdmi->connector.dev);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t zx_hdmi_irq_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा zx_hdmi *hdmi = dev_id;
	u8 lstat;

	lstat = hdmi_पढ़ोb(hdmi, L1_INTR_STAT);

	/* Monitor detect/HPD पूर्णांकerrupt */
	अगर (lstat & L1_INTR_STAT_INTR1) अणु
		u8 stat;

		stat = hdmi_पढ़ोb(hdmi, INTR1_STAT);
		hdmi_ग_लिखोb(hdmi, INTR1_STAT, stat);

		अगर (stat & INTR1_MONITOR_DETECT)
			वापस IRQ_WAKE_THREAD;
	पूर्ण

	वापस IRQ_NONE;
पूर्ण

अटल पूर्णांक zx_hdmi_audio_startup(काष्ठा device *dev, व्योम *data)
अणु
	काष्ठा zx_hdmi *hdmi = dev_get_drvdata(dev);
	काष्ठा drm_encoder *encoder = &hdmi->encoder;

	vou_inf_hdmi_audio_sel(encoder->crtc, VOU_HDMI_AUD_SPDIF);

	वापस 0;
पूर्ण

अटल व्योम zx_hdmi_audio_shutकरोwn(काष्ठा device *dev, व्योम *data)
अणु
	काष्ठा zx_hdmi *hdmi = dev_get_drvdata(dev);

	/* Disable audio input */
	hdmi_ग_लिखोb_mask(hdmi, AUD_EN, AUD_IN_EN, 0);
पूर्ण

अटल अंतरभूत पूर्णांक zx_hdmi_audio_get_n(अचिन्हित पूर्णांक fs)
अणु
	अचिन्हित पूर्णांक n;

	अगर (fs && (fs % 44100) == 0)
		n = 6272 * (fs / 44100);
	अन्यथा
		n = fs * 128 / 1000;

	वापस n;
पूर्ण

अटल पूर्णांक zx_hdmi_audio_hw_params(काष्ठा device *dev,
				   व्योम *data,
				   काष्ठा hdmi_codec_daअगरmt *daअगरmt,
				   काष्ठा hdmi_codec_params *params)
अणु
	काष्ठा zx_hdmi *hdmi = dev_get_drvdata(dev);
	काष्ठा hdmi_audio_infoframe *cea = &params->cea;
	जोड़ hdmi_infoframe frame;
	पूर्णांक n;

	/* We only support spdअगर क्रम now */
	अगर (daअगरmt->fmt != HDMI_SPDIF) अणु
		DRM_DEV_ERROR(hdmi->dev, "invalid daifmt %d\n", daअगरmt->fmt);
		वापस -EINVAL;
	पूर्ण

	चयन (params->sample_width) अणु
	हाल 16:
		hdmi_ग_लिखोb_mask(hdmi, TPI_AUD_CONFIG, SPDIF_SAMPLE_SIZE_MASK,
				 SPDIF_SAMPLE_SIZE_16BIT);
		अवरोध;
	हाल 20:
		hdmi_ग_लिखोb_mask(hdmi, TPI_AUD_CONFIG, SPDIF_SAMPLE_SIZE_MASK,
				 SPDIF_SAMPLE_SIZE_20BIT);
		अवरोध;
	हाल 24:
		hdmi_ग_लिखोb_mask(hdmi, TPI_AUD_CONFIG, SPDIF_SAMPLE_SIZE_MASK,
				 SPDIF_SAMPLE_SIZE_24BIT);
		अवरोध;
	शेष:
		DRM_DEV_ERROR(hdmi->dev, "invalid sample width %d\n",
			      params->sample_width);
		वापस -EINVAL;
	पूर्ण

	/* CTS is calculated by hardware, and we only need to take care of N */
	n = zx_hdmi_audio_get_n(params->sample_rate);
	hdmi_ग_लिखोb(hdmi, N_SVAL1, n & 0xff);
	hdmi_ग_लिखोb(hdmi, N_SVAL2, (n >> 8) & 0xff);
	hdmi_ग_लिखोb(hdmi, N_SVAL3, (n >> 16) & 0xf);

	/* Enable spdअगर mode */
	hdmi_ग_लिखोb_mask(hdmi, AUD_MODE, SPDIF_EN, SPDIF_EN);

	/* Enable audio input */
	hdmi_ग_लिखोb_mask(hdmi, AUD_EN, AUD_IN_EN, AUD_IN_EN);

	स_नकल(&frame.audio, cea, माप(*cea));

	वापस zx_hdmi_infoframe_trans(hdmi, &frame, FSEL_AUDIO);
पूर्ण

अटल पूर्णांक zx_hdmi_audio_mute(काष्ठा device *dev, व्योम *data,
			      bool enable, पूर्णांक direction)
अणु
	काष्ठा zx_hdmi *hdmi = dev_get_drvdata(dev);

	अगर (enable)
		hdmi_ग_लिखोb_mask(hdmi, TPI_AUD_CONFIG, TPI_AUD_MUTE,
				 TPI_AUD_MUTE);
	अन्यथा
		hdmi_ग_लिखोb_mask(hdmi, TPI_AUD_CONFIG, TPI_AUD_MUTE, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक zx_hdmi_audio_get_eld(काष्ठा device *dev, व्योम *data,
				 uपूर्णांक8_t *buf, माप_प्रकार len)
अणु
	काष्ठा zx_hdmi *hdmi = dev_get_drvdata(dev);
	काष्ठा drm_connector *connector = &hdmi->connector;

	स_नकल(buf, connector->eld, min(माप(connector->eld), len));

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा hdmi_codec_ops zx_hdmi_codec_ops = अणु
	.audio_startup = zx_hdmi_audio_startup,
	.hw_params = zx_hdmi_audio_hw_params,
	.audio_shutकरोwn = zx_hdmi_audio_shutकरोwn,
	.mute_stream = zx_hdmi_audio_mute,
	.get_eld = zx_hdmi_audio_get_eld,
	.no_capture_mute = 1,
पूर्ण;

अटल काष्ठा hdmi_codec_pdata zx_hdmi_codec_pdata = अणु
	.ops = &zx_hdmi_codec_ops,
	.spdअगर = 1,
पूर्ण;

अटल पूर्णांक zx_hdmi_audio_रेजिस्टर(काष्ठा zx_hdmi *hdmi)
अणु
	काष्ठा platक्रमm_device *pdev;

	pdev = platक्रमm_device_रेजिस्टर_data(hdmi->dev, HDMI_CODEC_DRV_NAME,
					     PLATFORM_DEVID_AUTO,
					     &zx_hdmi_codec_pdata,
					     माप(zx_hdmi_codec_pdata));
	अगर (IS_ERR(pdev))
		वापस PTR_ERR(pdev);

	hdmi->audio_pdev = pdev;

	वापस 0;
पूर्ण

अटल पूर्णांक zx_hdmi_i2c_पढ़ो(काष्ठा zx_hdmi *hdmi, काष्ठा i2c_msg *msg)
अणु
	पूर्णांक len = msg->len;
	u8 *buf = msg->buf;
	पूर्णांक retry = 0;
	पूर्णांक ret = 0;

	/* Bits [9:8] of bytes */
	hdmi_ग_लिखोb(hdmi, ZX_DDC_DIN_CNT2, (len >> 8) & 0xff);
	/* Bits [7:0] of bytes */
	hdmi_ग_लिखोb(hdmi, ZX_DDC_DIN_CNT1, len & 0xff);

	/* Clear FIFO */
	hdmi_ग_लिखोb_mask(hdmi, ZX_DDC_CMD, DDC_CMD_MASK, DDC_CMD_CLEAR_FIFO);

	/* Kick off the पढ़ो */
	hdmi_ग_लिखोb_mask(hdmi, ZX_DDC_CMD, DDC_CMD_MASK,
			 DDC_CMD_SEQUENTIAL_READ);

	जबतक (len > 0) अणु
		पूर्णांक cnt, i;

		/* FIFO needs some समय to get पढ़ोy */
		usleep_range(500, 1000);

		cnt = hdmi_पढ़ोb(hdmi, ZX_DDC_DOUT_CNT) & DDC_DOUT_CNT_MASK;
		अगर (cnt == 0) अणु
			अगर (++retry > 5) अणु
				DRM_DEV_ERROR(hdmi->dev,
					      "DDC FIFO read timed out!");
				वापस -ETIMEDOUT;
			पूर्ण
			जारी;
		पूर्ण

		क्रम (i = 0; i < cnt; i++)
			*buf++ = hdmi_पढ़ोb(hdmi, ZX_DDC_DATA);
		len -= cnt;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक zx_hdmi_i2c_ग_लिखो(काष्ठा zx_hdmi *hdmi, काष्ठा i2c_msg *msg)
अणु
	/*
	 * The DDC I2C adapter is only क्रम पढ़ोing EDID data, so we assume
	 * that the ग_लिखो to this adapter must be the EDID data offset.
	 */
	अगर ((msg->len != 1) ||
	    ((msg->addr != DDC_ADDR) && (msg->addr != DDC_SEGMENT_ADDR)))
		वापस -EINVAL;

	अगर (msg->addr == DDC_SEGMENT_ADDR)
		hdmi_ग_लिखोb(hdmi, ZX_DDC_SEGM, msg->addr << 1);
	अन्यथा अगर (msg->addr == DDC_ADDR)
		hdmi_ग_लिखोb(hdmi, ZX_DDC_ADDR, msg->addr << 1);

	hdmi_ग_लिखोb(hdmi, ZX_DDC_OFFSET, msg->buf[0]);

	वापस 0;
पूर्ण

अटल पूर्णांक zx_hdmi_i2c_xfer(काष्ठा i2c_adapter *adap, काष्ठा i2c_msg *msgs,
			    पूर्णांक num)
अणु
	काष्ठा zx_hdmi *hdmi = i2c_get_adapdata(adap);
	काष्ठा zx_hdmi_i2c *ddc = hdmi->ddc;
	पूर्णांक i, ret = 0;

	mutex_lock(&ddc->lock);

	/* Enable DDC master access */
	hdmi_ग_लिखोb_mask(hdmi, TPI_DDC_MASTER_EN, HW_DDC_MASTER, HW_DDC_MASTER);

	क्रम (i = 0; i < num; i++) अणु
		DRM_DEV_DEBUG(hdmi->dev,
			      "xfer: num: %d/%d, len: %d, flags: %#x\n",
			      i + 1, num, msgs[i].len, msgs[i].flags);

		अगर (msgs[i].flags & I2C_M_RD)
			ret = zx_hdmi_i2c_पढ़ो(hdmi, &msgs[i]);
		अन्यथा
			ret = zx_hdmi_i2c_ग_लिखो(hdmi, &msgs[i]);

		अगर (ret < 0)
			अवरोध;
	पूर्ण

	अगर (!ret)
		ret = num;

	/* Disable DDC master access */
	hdmi_ग_लिखोb_mask(hdmi, TPI_DDC_MASTER_EN, HW_DDC_MASTER, 0);

	mutex_unlock(&ddc->lock);

	वापस ret;
पूर्ण

अटल u32 zx_hdmi_i2c_func(काष्ठा i2c_adapter *adapter)
अणु
	वापस I2C_FUNC_I2C | I2C_FUNC_SMBUS_EMUL;
पूर्ण

अटल स्थिर काष्ठा i2c_algorithm zx_hdmi_algorithm = अणु
	.master_xfer	= zx_hdmi_i2c_xfer,
	.functionality	= zx_hdmi_i2c_func,
पूर्ण;

अटल पूर्णांक zx_hdmi_ddc_रेजिस्टर(काष्ठा zx_hdmi *hdmi)
अणु
	काष्ठा i2c_adapter *adap;
	काष्ठा zx_hdmi_i2c *ddc;
	पूर्णांक ret;

	ddc = devm_kzalloc(hdmi->dev, माप(*ddc), GFP_KERNEL);
	अगर (!ddc)
		वापस -ENOMEM;

	hdmi->ddc = ddc;
	mutex_init(&ddc->lock);

	adap = &ddc->adap;
	adap->owner = THIS_MODULE;
	adap->class = I2C_CLASS_DDC;
	adap->dev.parent = hdmi->dev;
	adap->algo = &zx_hdmi_algorithm;
	snम_लिखो(adap->name, माप(adap->name), "zx hdmi i2c");

	ret = i2c_add_adapter(adap);
	अगर (ret) अणु
		DRM_DEV_ERROR(hdmi->dev, "failed to add I2C adapter: %d\n",
			      ret);
		वापस ret;
	पूर्ण

	i2c_set_adapdata(adap, hdmi);

	वापस 0;
पूर्ण

अटल पूर्णांक zx_hdmi_bind(काष्ठा device *dev, काष्ठा device *master, व्योम *data)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा drm_device *drm = data;
	काष्ठा resource *res;
	काष्ठा zx_hdmi *hdmi;
	पूर्णांक irq;
	पूर्णांक ret;

	hdmi = devm_kzalloc(dev, माप(*hdmi), GFP_KERNEL);
	अगर (!hdmi)
		वापस -ENOMEM;

	hdmi->dev = dev;
	hdmi->drm = drm;

	dev_set_drvdata(dev, hdmi);

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	hdmi->mmio = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(hdmi->mmio)) अणु
		ret = PTR_ERR(hdmi->mmio);
		DRM_DEV_ERROR(dev, "failed to remap hdmi region: %d\n", ret);
		वापस ret;
	पूर्ण

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;

	hdmi->cec_clk = devm_clk_get(hdmi->dev, "osc_cec");
	अगर (IS_ERR(hdmi->cec_clk)) अणु
		ret = PTR_ERR(hdmi->cec_clk);
		DRM_DEV_ERROR(dev, "failed to get cec_clk: %d\n", ret);
		वापस ret;
	पूर्ण

	hdmi->osc_clk = devm_clk_get(hdmi->dev, "osc_clk");
	अगर (IS_ERR(hdmi->osc_clk)) अणु
		ret = PTR_ERR(hdmi->osc_clk);
		DRM_DEV_ERROR(dev, "failed to get osc_clk: %d\n", ret);
		वापस ret;
	पूर्ण

	hdmi->xclk = devm_clk_get(hdmi->dev, "xclk");
	अगर (IS_ERR(hdmi->xclk)) अणु
		ret = PTR_ERR(hdmi->xclk);
		DRM_DEV_ERROR(dev, "failed to get xclk: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = zx_hdmi_ddc_रेजिस्टर(hdmi);
	अगर (ret) अणु
		DRM_DEV_ERROR(dev, "failed to register ddc: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = zx_hdmi_audio_रेजिस्टर(hdmi);
	अगर (ret) अणु
		DRM_DEV_ERROR(dev, "failed to register audio: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = zx_hdmi_रेजिस्टर(drm, hdmi);
	अगर (ret) अणु
		DRM_DEV_ERROR(dev, "failed to register hdmi: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = devm_request_thपढ़ोed_irq(dev, irq, zx_hdmi_irq_handler,
					zx_hdmi_irq_thपढ़ो, IRQF_SHARED,
					dev_name(dev), hdmi);
	अगर (ret) अणु
		DRM_DEV_ERROR(dev, "failed to request threaded irq: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम zx_hdmi_unbind(काष्ठा device *dev, काष्ठा device *master,
			   व्योम *data)
अणु
	काष्ठा zx_hdmi *hdmi = dev_get_drvdata(dev);

	hdmi->connector.funcs->destroy(&hdmi->connector);
	hdmi->encoder.funcs->destroy(&hdmi->encoder);

	अगर (hdmi->audio_pdev)
		platक्रमm_device_unरेजिस्टर(hdmi->audio_pdev);
पूर्ण

अटल स्थिर काष्ठा component_ops zx_hdmi_component_ops = अणु
	.bind = zx_hdmi_bind,
	.unbind = zx_hdmi_unbind,
पूर्ण;

अटल पूर्णांक zx_hdmi_probe(काष्ठा platक्रमm_device *pdev)
अणु
	वापस component_add(&pdev->dev, &zx_hdmi_component_ops);
पूर्ण

अटल पूर्णांक zx_hdmi_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	component_del(&pdev->dev, &zx_hdmi_component_ops);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id zx_hdmi_of_match[] = अणु
	अणु .compatible = "zte,zx296718-hdmi", पूर्ण,
	अणु /* end */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, zx_hdmi_of_match);

काष्ठा platक्रमm_driver zx_hdmi_driver = अणु
	.probe = zx_hdmi_probe,
	.हटाओ = zx_hdmi_हटाओ,
	.driver	= अणु
		.name = "zx-hdmi",
		.of_match_table	= zx_hdmi_of_match,
	पूर्ण,
पूर्ण;
