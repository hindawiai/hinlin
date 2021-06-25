<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2015 Broadcom
 * Copyright (c) 2014 The Linux Foundation. All rights reserved.
 * Copyright (C) 2013 Red Hat
 * Author: Rob Clark <robdclark@gmail.com>
 */

/**
 * DOC: VC4 Falcon HDMI module
 *
 * The HDMI core has a state machine and a PHY.  On BCM2835, most of
 * the unit operates off of the HSM घड़ी from CPRMAN.  It also
 * पूर्णांकernally uses the PLLH_PIX घड़ी क्रम the PHY.
 *
 * HDMI infoframes are kept within a small packet ram, where each
 * packet can be inभागidually enabled क्रम including in a frame.
 *
 * HDMI audio is implemented entirely within the HDMI IP block.  A
 * रेजिस्टर in the HDMI encoder takes SPDIF frames from the DMA engine
 * and transfers them over an पूर्णांकernal MAI (multi-channel audio
 * पूर्णांकerconnect) bus to the encoder side क्रम insertion पूर्णांकo the video
 * blank regions.
 *
 * The driver's HDMI encoder करोes not yet support घातer management.
 * The HDMI encoder's घातer करोमुख्य and the HSM/pixel घड़ीs are kept
 * continuously running, and only the HDMI logic and packet ram are
 * घातered off/on at disable/enable समय.
 *
 * The driver करोes not yet support CEC control, though the HDMI
 * encoder block has CEC support.
 */

#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_edid.h>
#समावेश <drm/drm_probe_helper.h>
#समावेश <drm/drm_simple_kms_helper.h>
#समावेश <linux/clk.h>
#समावेश <linux/component.h>
#समावेश <linux/i2c.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/rational.h>
#समावेश <linux/reset.h>
#समावेश <sound/dmaengine_pcm.h>
#समावेश <sound/pcm_drm_eld.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश "media/cec.h"
#समावेश "vc4_drv.h"
#समावेश "vc4_hdmi.h"
#समावेश "vc4_hdmi_regs.h"
#समावेश "vc4_regs.h"

#घोषणा VC5_HDMI_HORZA_HFP_SHIFT		16
#घोषणा VC5_HDMI_HORZA_HFP_MASK			VC4_MASK(28, 16)
#घोषणा VC5_HDMI_HORZA_VPOS			BIT(15)
#घोषणा VC5_HDMI_HORZA_HPOS			BIT(14)
#घोषणा VC5_HDMI_HORZA_HAP_SHIFT		0
#घोषणा VC5_HDMI_HORZA_HAP_MASK			VC4_MASK(13, 0)

#घोषणा VC5_HDMI_HORZB_HBP_SHIFT		16
#घोषणा VC5_HDMI_HORZB_HBP_MASK			VC4_MASK(26, 16)
#घोषणा VC5_HDMI_HORZB_HSP_SHIFT		0
#घोषणा VC5_HDMI_HORZB_HSP_MASK			VC4_MASK(10, 0)

#घोषणा VC5_HDMI_VERTA_VSP_SHIFT		24
#घोषणा VC5_HDMI_VERTA_VSP_MASK			VC4_MASK(28, 24)
#घोषणा VC5_HDMI_VERTA_VFP_SHIFT		16
#घोषणा VC5_HDMI_VERTA_VFP_MASK			VC4_MASK(22, 16)
#घोषणा VC5_HDMI_VERTA_VAL_SHIFT		0
#घोषणा VC5_HDMI_VERTA_VAL_MASK			VC4_MASK(12, 0)

#घोषणा VC5_HDMI_VERTB_VSPO_SHIFT		16
#घोषणा VC5_HDMI_VERTB_VSPO_MASK		VC4_MASK(29, 16)

#घोषणा VC5_HDMI_DEEP_COLOR_CONFIG_1_INIT_PACK_PHASE_SHIFT	8
#घोषणा VC5_HDMI_DEEP_COLOR_CONFIG_1_INIT_PACK_PHASE_MASK	VC4_MASK(10, 8)

#घोषणा VC5_HDMI_DEEP_COLOR_CONFIG_1_COLOR_DEPTH_SHIFT		0
#घोषणा VC5_HDMI_DEEP_COLOR_CONFIG_1_COLOR_DEPTH_MASK		VC4_MASK(3, 0)

#घोषणा VC5_HDMI_GCP_CONFIG_GCP_ENABLE		BIT(31)

#घोषणा VC5_HDMI_GCP_WORD_1_GCP_SUBPACKET_BYTE_1_SHIFT	8
#घोषणा VC5_HDMI_GCP_WORD_1_GCP_SUBPACKET_BYTE_1_MASK	VC4_MASK(15, 8)

# define VC4_HD_M_SW_RST			BIT(2)
# define VC4_HD_M_ENABLE			BIT(0)

#घोषणा CEC_CLOCK_FREQ 40000
#घोषणा VC4_HSM_MID_CLOCK 149985000

#घोषणा HDMI_14_MAX_TMDS_CLK   (340 * 1000 * 1000)

अटल पूर्णांक vc4_hdmi_debugfs_regs(काष्ठा seq_file *m, व्योम *unused)
अणु
	काष्ठा drm_info_node *node = (काष्ठा drm_info_node *)m->निजी;
	काष्ठा vc4_hdmi *vc4_hdmi = node->info_ent->data;
	काष्ठा drm_prपूर्णांकer p = drm_seq_file_prपूर्णांकer(m);

	drm_prपूर्णांक_regset32(&p, &vc4_hdmi->hdmi_regset);
	drm_prपूर्णांक_regset32(&p, &vc4_hdmi->hd_regset);

	वापस 0;
पूर्ण

अटल व्योम vc4_hdmi_reset(काष्ठा vc4_hdmi *vc4_hdmi)
अणु
	HDMI_WRITE(HDMI_M_CTL, VC4_HD_M_SW_RST);
	udelay(1);
	HDMI_WRITE(HDMI_M_CTL, 0);

	HDMI_WRITE(HDMI_M_CTL, VC4_HD_M_ENABLE);

	HDMI_WRITE(HDMI_SW_RESET_CONTROL,
		   VC4_HDMI_SW_RESET_HDMI |
		   VC4_HDMI_SW_RESET_FORMAT_DETECT);

	HDMI_WRITE(HDMI_SW_RESET_CONTROL, 0);
पूर्ण

अटल व्योम vc5_hdmi_reset(काष्ठा vc4_hdmi *vc4_hdmi)
अणु
	reset_control_reset(vc4_hdmi->reset);

	HDMI_WRITE(HDMI_DVP_CTL, 0);

	HDMI_WRITE(HDMI_CLOCK_STOP,
		   HDMI_READ(HDMI_CLOCK_STOP) | VC4_DVP_HT_CLOCK_STOP_PIXEL);
पूर्ण

#अगर_घोषित CONFIG_DRM_VC4_HDMI_CEC
अटल व्योम vc4_hdmi_cec_update_clk_भाग(काष्ठा vc4_hdmi *vc4_hdmi)
अणु
	u16 clk_cnt;
	u32 value;

	value = HDMI_READ(HDMI_CEC_CNTRL_1);
	value &= ~VC4_HDMI_CEC_DIV_CLK_CNT_MASK;

	/*
	 * Set the घड़ी भागider: the hsm_घड़ी rate and this भागider
	 * setting will give a 40 kHz CEC घड़ी.
	 */
	clk_cnt = clk_get_rate(vc4_hdmi->cec_घड़ी) / CEC_CLOCK_FREQ;
	value |= clk_cnt << VC4_HDMI_CEC_DIV_CLK_CNT_SHIFT;
	HDMI_WRITE(HDMI_CEC_CNTRL_1, value);
पूर्ण
#अन्यथा
अटल व्योम vc4_hdmi_cec_update_clk_भाग(काष्ठा vc4_hdmi *vc4_hdmi) अणुपूर्ण
#पूर्ण_अगर

अटल क्रमागत drm_connector_status
vc4_hdmi_connector_detect(काष्ठा drm_connector *connector, bool क्रमce)
अणु
	काष्ठा vc4_hdmi *vc4_hdmi = connector_to_vc4_hdmi(connector);
	bool connected = false;

	अगर (vc4_hdmi->hpd_gpio) अणु
		अगर (gpio_get_value_cansleep(vc4_hdmi->hpd_gpio) ^
		    vc4_hdmi->hpd_active_low)
			connected = true;
	पूर्ण अन्यथा अगर (drm_probe_ddc(vc4_hdmi->ddc)) अणु
		connected = true;
	पूर्ण अन्यथा अगर (HDMI_READ(HDMI_HOTPLUG) & VC4_HDMI_HOTPLUG_CONNECTED) अणु
		connected = true;
	पूर्ण

	अगर (connected) अणु
		अगर (connector->status != connector_status_connected) अणु
			काष्ठा edid *edid = drm_get_edid(connector, vc4_hdmi->ddc);

			अगर (edid) अणु
				cec_s_phys_addr_from_edid(vc4_hdmi->cec_adap, edid);
				vc4_hdmi->encoder.hdmi_monitor = drm_detect_hdmi_monitor(edid);
				kमुक्त(edid);
			पूर्ण
		पूर्ण

		वापस connector_status_connected;
	पूर्ण

	cec_phys_addr_invalidate(vc4_hdmi->cec_adap);
	वापस connector_status_disconnected;
पूर्ण

अटल व्योम vc4_hdmi_connector_destroy(काष्ठा drm_connector *connector)
अणु
	drm_connector_unरेजिस्टर(connector);
	drm_connector_cleanup(connector);
पूर्ण

अटल पूर्णांक vc4_hdmi_connector_get_modes(काष्ठा drm_connector *connector)
अणु
	काष्ठा vc4_hdmi *vc4_hdmi = connector_to_vc4_hdmi(connector);
	काष्ठा vc4_hdmi_encoder *vc4_encoder = &vc4_hdmi->encoder;
	पूर्णांक ret = 0;
	काष्ठा edid *edid;

	edid = drm_get_edid(connector, vc4_hdmi->ddc);
	cec_s_phys_addr_from_edid(vc4_hdmi->cec_adap, edid);
	अगर (!edid)
		वापस -ENODEV;

	vc4_encoder->hdmi_monitor = drm_detect_hdmi_monitor(edid);

	drm_connector_update_edid_property(connector, edid);
	ret = drm_add_edid_modes(connector, edid);
	kमुक्त(edid);

	वापस ret;
पूर्ण

अटल व्योम vc4_hdmi_connector_reset(काष्ठा drm_connector *connector)
अणु
	काष्ठा vc4_hdmi_connector_state *old_state =
		conn_state_to_vc4_hdmi_conn_state(connector->state);
	काष्ठा vc4_hdmi_connector_state *new_state =
		kzalloc(माप(*new_state), GFP_KERNEL);

	अगर (connector->state)
		__drm_atomic_helper_connector_destroy_state(connector->state);

	kमुक्त(old_state);
	__drm_atomic_helper_connector_reset(connector, &new_state->base);

	अगर (!new_state)
		वापस;

	new_state->base.max_bpc = 8;
	new_state->base.max_requested_bpc = 8;
	drm_atomic_helper_connector_tv_reset(connector);
पूर्ण

अटल काष्ठा drm_connector_state *
vc4_hdmi_connector_duplicate_state(काष्ठा drm_connector *connector)
अणु
	काष्ठा drm_connector_state *conn_state = connector->state;
	काष्ठा vc4_hdmi_connector_state *vc4_state = conn_state_to_vc4_hdmi_conn_state(conn_state);
	काष्ठा vc4_hdmi_connector_state *new_state;

	new_state = kzalloc(माप(*new_state), GFP_KERNEL);
	अगर (!new_state)
		वापस शून्य;

	new_state->pixel_rate = vc4_state->pixel_rate;
	__drm_atomic_helper_connector_duplicate_state(connector, &new_state->base);

	वापस &new_state->base;
पूर्ण

अटल स्थिर काष्ठा drm_connector_funcs vc4_hdmi_connector_funcs = अणु
	.detect = vc4_hdmi_connector_detect,
	.fill_modes = drm_helper_probe_single_connector_modes,
	.destroy = vc4_hdmi_connector_destroy,
	.reset = vc4_hdmi_connector_reset,
	.atomic_duplicate_state = vc4_hdmi_connector_duplicate_state,
	.atomic_destroy_state = drm_atomic_helper_connector_destroy_state,
पूर्ण;

अटल स्थिर काष्ठा drm_connector_helper_funcs vc4_hdmi_connector_helper_funcs = अणु
	.get_modes = vc4_hdmi_connector_get_modes,
पूर्ण;

अटल पूर्णांक vc4_hdmi_connector_init(काष्ठा drm_device *dev,
				   काष्ठा vc4_hdmi *vc4_hdmi)
अणु
	काष्ठा drm_connector *connector = &vc4_hdmi->connector;
	काष्ठा drm_encoder *encoder = &vc4_hdmi->encoder.base.base;
	पूर्णांक ret;

	drm_connector_init_with_ddc(dev, connector,
				    &vc4_hdmi_connector_funcs,
				    DRM_MODE_CONNECTOR_HDMIA,
				    vc4_hdmi->ddc);
	drm_connector_helper_add(connector, &vc4_hdmi_connector_helper_funcs);

	/*
	 * Some of the properties below require access to state, like bpc.
	 * Allocate some शेष initial connector state with our reset helper.
	 */
	अगर (connector->funcs->reset)
		connector->funcs->reset(connector);

	/* Create and attach TV margin props to this connector. */
	ret = drm_mode_create_tv_margin_properties(dev);
	अगर (ret)
		वापस ret;

	drm_connector_attach_tv_margin_properties(connector);
	drm_connector_attach_max_bpc_property(connector, 8, 12);

	connector->polled = (DRM_CONNECTOR_POLL_CONNECT |
			     DRM_CONNECTOR_POLL_DISCONNECT);

	connector->पूर्णांकerlace_allowed = 1;
	connector->द्विगुनscan_allowed = 0;

	drm_connector_attach_encoder(connector, encoder);

	वापस 0;
पूर्ण

अटल पूर्णांक vc4_hdmi_stop_packet(काष्ठा drm_encoder *encoder,
				क्रमागत hdmi_infoframe_type type,
				bool poll)
अणु
	काष्ठा vc4_hdmi *vc4_hdmi = encoder_to_vc4_hdmi(encoder);
	u32 packet_id = type - 0x80;

	HDMI_WRITE(HDMI_RAM_PACKET_CONFIG,
		   HDMI_READ(HDMI_RAM_PACKET_CONFIG) & ~BIT(packet_id));

	अगर (!poll)
		वापस 0;

	वापस रुको_क्रम(!(HDMI_READ(HDMI_RAM_PACKET_STATUS) &
			  BIT(packet_id)), 100);
पूर्ण

अटल व्योम vc4_hdmi_ग_लिखो_infoframe(काष्ठा drm_encoder *encoder,
				     जोड़ hdmi_infoframe *frame)
अणु
	काष्ठा vc4_hdmi *vc4_hdmi = encoder_to_vc4_hdmi(encoder);
	u32 packet_id = frame->any.type - 0x80;
	स्थिर काष्ठा vc4_hdmi_रेजिस्टर *ram_packet_start =
		&vc4_hdmi->variant->रेजिस्टरs[HDMI_RAM_PACKET_START];
	u32 packet_reg = ram_packet_start->offset + VC4_HDMI_PACKET_STRIDE * packet_id;
	व्योम __iomem *base = __vc4_hdmi_get_field_base(vc4_hdmi,
						       ram_packet_start->reg);
	uपूर्णांक8_t buffer[VC4_HDMI_PACKET_STRIDE];
	sमाप_प्रकार len, i;
	पूर्णांक ret;

	WARN_ONCE(!(HDMI_READ(HDMI_RAM_PACKET_CONFIG) &
		    VC4_HDMI_RAM_PACKET_ENABLE),
		  "Packet RAM has to be on to store the packet.");

	len = hdmi_infoframe_pack(frame, buffer, माप(buffer));
	अगर (len < 0)
		वापस;

	ret = vc4_hdmi_stop_packet(encoder, frame->any.type, true);
	अगर (ret) अणु
		DRM_ERROR("Failed to wait for infoframe to go idle: %d\n", ret);
		वापस;
	पूर्ण

	क्रम (i = 0; i < len; i += 7) अणु
		ग_लिखोl(buffer[i + 0] << 0 |
		       buffer[i + 1] << 8 |
		       buffer[i + 2] << 16,
		       base + packet_reg);
		packet_reg += 4;

		ग_लिखोl(buffer[i + 3] << 0 |
		       buffer[i + 4] << 8 |
		       buffer[i + 5] << 16 |
		       buffer[i + 6] << 24,
		       base + packet_reg);
		packet_reg += 4;
	पूर्ण

	HDMI_WRITE(HDMI_RAM_PACKET_CONFIG,
		   HDMI_READ(HDMI_RAM_PACKET_CONFIG) | BIT(packet_id));
	ret = रुको_क्रम((HDMI_READ(HDMI_RAM_PACKET_STATUS) &
			BIT(packet_id)), 100);
	अगर (ret)
		DRM_ERROR("Failed to wait for infoframe to start: %d\n", ret);
पूर्ण

अटल व्योम vc4_hdmi_set_avi_infoframe(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा vc4_hdmi *vc4_hdmi = encoder_to_vc4_hdmi(encoder);
	काष्ठा vc4_hdmi_encoder *vc4_encoder = to_vc4_hdmi_encoder(encoder);
	काष्ठा drm_connector *connector = &vc4_hdmi->connector;
	काष्ठा drm_connector_state *cstate = connector->state;
	काष्ठा drm_crtc *crtc = encoder->crtc;
	स्थिर काष्ठा drm_display_mode *mode = &crtc->state->adjusted_mode;
	जोड़ hdmi_infoframe frame;
	पूर्णांक ret;

	ret = drm_hdmi_avi_infoframe_from_display_mode(&frame.avi,
						       connector, mode);
	अगर (ret < 0) अणु
		DRM_ERROR("couldn't fill AVI infoframe\n");
		वापस;
	पूर्ण

	drm_hdmi_avi_infoframe_quant_range(&frame.avi,
					   connector, mode,
					   vc4_encoder->limited_rgb_range ?
					   HDMI_QUANTIZATION_RANGE_LIMITED :
					   HDMI_QUANTIZATION_RANGE_FULL);

	drm_hdmi_avi_infoframe_bars(&frame.avi, cstate);

	vc4_hdmi_ग_लिखो_infoframe(encoder, &frame);
पूर्ण

अटल व्योम vc4_hdmi_set_spd_infoframe(काष्ठा drm_encoder *encoder)
अणु
	जोड़ hdmi_infoframe frame;
	पूर्णांक ret;

	ret = hdmi_spd_infoframe_init(&frame.spd, "Broadcom", "Videocore");
	अगर (ret < 0) अणु
		DRM_ERROR("couldn't fill SPD infoframe\n");
		वापस;
	पूर्ण

	frame.spd.sdi = HDMI_SPD_SDI_PC;

	vc4_hdmi_ग_लिखो_infoframe(encoder, &frame);
पूर्ण

अटल व्योम vc4_hdmi_set_audio_infoframe(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा vc4_hdmi *vc4_hdmi = encoder_to_vc4_hdmi(encoder);
	जोड़ hdmi_infoframe frame;

	hdmi_audio_infoframe_init(&frame.audio);

	frame.audio.coding_type = HDMI_AUDIO_CODING_TYPE_STREAM;
	frame.audio.sample_frequency = HDMI_AUDIO_SAMPLE_FREQUENCY_STREAM;
	frame.audio.sample_size = HDMI_AUDIO_SAMPLE_SIZE_STREAM;
	frame.audio.channels = vc4_hdmi->audio.channels;

	vc4_hdmi_ग_लिखो_infoframe(encoder, &frame);
पूर्ण

अटल व्योम vc4_hdmi_set_infoframes(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा vc4_hdmi *vc4_hdmi = encoder_to_vc4_hdmi(encoder);

	vc4_hdmi_set_avi_infoframe(encoder);
	vc4_hdmi_set_spd_infoframe(encoder);
	/*
	 * If audio was streaming, then we need to reenabled the audio
	 * infoframe here during encoder_enable.
	 */
	अगर (vc4_hdmi->audio.streaming)
		vc4_hdmi_set_audio_infoframe(encoder);
पूर्ण

अटल व्योम vc4_hdmi_encoder_post_crtc_disable(काष्ठा drm_encoder *encoder,
					       काष्ठा drm_atomic_state *state)
अणु
	काष्ठा vc4_hdmi *vc4_hdmi = encoder_to_vc4_hdmi(encoder);

	HDMI_WRITE(HDMI_RAM_PACKET_CONFIG, 0);

	HDMI_WRITE(HDMI_VID_CTL, HDMI_READ(HDMI_VID_CTL) |
		   VC4_HD_VID_CTL_CLRRGB | VC4_HD_VID_CTL_CLRSYNC);

	HDMI_WRITE(HDMI_VID_CTL,
		   HDMI_READ(HDMI_VID_CTL) | VC4_HD_VID_CTL_BLANKPIX);
पूर्ण

अटल व्योम vc4_hdmi_encoder_post_crtc_घातerकरोwn(काष्ठा drm_encoder *encoder,
						 काष्ठा drm_atomic_state *state)
अणु
	काष्ठा vc4_hdmi *vc4_hdmi = encoder_to_vc4_hdmi(encoder);
	पूर्णांक ret;

	अगर (vc4_hdmi->variant->phy_disable)
		vc4_hdmi->variant->phy_disable(vc4_hdmi);

	HDMI_WRITE(HDMI_VID_CTL,
		   HDMI_READ(HDMI_VID_CTL) & ~VC4_HD_VID_CTL_ENABLE);

	clk_disable_unprepare(vc4_hdmi->pixel_bvb_घड़ी);
	clk_disable_unprepare(vc4_hdmi->hsm_घड़ी);
	clk_disable_unprepare(vc4_hdmi->pixel_घड़ी);

	ret = pm_runसमय_put(&vc4_hdmi->pdev->dev);
	अगर (ret < 0)
		DRM_ERROR("Failed to release power domain: %d\n", ret);
पूर्ण

अटल व्योम vc4_hdmi_encoder_disable(काष्ठा drm_encoder *encoder)
अणु
पूर्ण

अटल व्योम vc4_hdmi_csc_setup(काष्ठा vc4_hdmi *vc4_hdmi, bool enable)
अणु
	u32 csc_ctl;

	csc_ctl = VC4_SET_FIELD(VC4_HD_CSC_CTL_ORDER_BGR,
				VC4_HD_CSC_CTL_ORDER);

	अगर (enable) अणु
		/* CEA VICs other than #1 requre limited range RGB
		 * output unless overridden by an AVI infoframe.
		 * Apply a colorspace conversion to squash 0-255 करोwn
		 * to 16-235.  The matrix here is:
		 *
		 * [ 0      0      0.8594 16]
		 * [ 0      0.8594 0      16]
		 * [ 0.8594 0      0      16]
		 * [ 0      0      0       1]
		 */
		csc_ctl |= VC4_HD_CSC_CTL_ENABLE;
		csc_ctl |= VC4_HD_CSC_CTL_RGB2YCC;
		csc_ctl |= VC4_SET_FIELD(VC4_HD_CSC_CTL_MODE_CUSTOM,
					 VC4_HD_CSC_CTL_MODE);

		HDMI_WRITE(HDMI_CSC_12_11, (0x000 << 16) | 0x000);
		HDMI_WRITE(HDMI_CSC_14_13, (0x100 << 16) | 0x6e0);
		HDMI_WRITE(HDMI_CSC_22_21, (0x6e0 << 16) | 0x000);
		HDMI_WRITE(HDMI_CSC_24_23, (0x100 << 16) | 0x000);
		HDMI_WRITE(HDMI_CSC_32_31, (0x000 << 16) | 0x6e0);
		HDMI_WRITE(HDMI_CSC_34_33, (0x100 << 16) | 0x000);
	पूर्ण

	/* The RGB order applies even when CSC is disabled. */
	HDMI_WRITE(HDMI_CSC_CTL, csc_ctl);
पूर्ण

अटल व्योम vc5_hdmi_csc_setup(काष्ठा vc4_hdmi *vc4_hdmi, bool enable)
अणु
	u32 csc_ctl;

	csc_ctl = 0x07;	/* RGB_CONVERT_MODE = custom matrix, || USE_RGB_TO_YCBCR */

	अगर (enable) अणु
		/* CEA VICs other than #1 requre limited range RGB
		 * output unless overridden by an AVI infoframe.
		 * Apply a colorspace conversion to squash 0-255 करोwn
		 * to 16-235.  The matrix here is:
		 *
		 * [ 0.8594 0      0      16]
		 * [ 0      0.8594 0      16]
		 * [ 0      0      0.8594 16]
		 * [ 0      0      0       1]
		 * Matrix is चिन्हित 2p13 fixed poपूर्णांक, with चिन्हित 9p6 offsets
		 */
		HDMI_WRITE(HDMI_CSC_12_11, (0x0000 << 16) | 0x1b80);
		HDMI_WRITE(HDMI_CSC_14_13, (0x0400 << 16) | 0x0000);
		HDMI_WRITE(HDMI_CSC_22_21, (0x1b80 << 16) | 0x0000);
		HDMI_WRITE(HDMI_CSC_24_23, (0x0400 << 16) | 0x0000);
		HDMI_WRITE(HDMI_CSC_32_31, (0x0000 << 16) | 0x0000);
		HDMI_WRITE(HDMI_CSC_34_33, (0x0400 << 16) | 0x1b80);
	पूर्ण अन्यथा अणु
		/* Still use the matrix क्रम full range, but make it unity.
		 * Matrix is चिन्हित 2p13 fixed poपूर्णांक, with चिन्हित 9p6 offsets
		 */
		HDMI_WRITE(HDMI_CSC_12_11, (0x0000 << 16) | 0x2000);
		HDMI_WRITE(HDMI_CSC_14_13, (0x0000 << 16) | 0x0000);
		HDMI_WRITE(HDMI_CSC_22_21, (0x2000 << 16) | 0x0000);
		HDMI_WRITE(HDMI_CSC_24_23, (0x0000 << 16) | 0x0000);
		HDMI_WRITE(HDMI_CSC_32_31, (0x0000 << 16) | 0x0000);
		HDMI_WRITE(HDMI_CSC_34_33, (0x0000 << 16) | 0x2000);
	पूर्ण

	HDMI_WRITE(HDMI_CSC_CTL, csc_ctl);
पूर्ण

अटल व्योम vc4_hdmi_set_timings(काष्ठा vc4_hdmi *vc4_hdmi,
				 काष्ठा drm_connector_state *state,
				 काष्ठा drm_display_mode *mode)
अणु
	bool hsync_pos = mode->flags & DRM_MODE_FLAG_PHSYNC;
	bool vsync_pos = mode->flags & DRM_MODE_FLAG_PVSYNC;
	bool पूर्णांकerlaced = mode->flags & DRM_MODE_FLAG_INTERLACE;
	u32 pixel_rep = (mode->flags & DRM_MODE_FLAG_DBLCLK) ? 2 : 1;
	u32 verta = (VC4_SET_FIELD(mode->crtc_vsync_end - mode->crtc_vsync_start,
				   VC4_HDMI_VERTA_VSP) |
		     VC4_SET_FIELD(mode->crtc_vsync_start - mode->crtc_vdisplay,
				   VC4_HDMI_VERTA_VFP) |
		     VC4_SET_FIELD(mode->crtc_vdisplay, VC4_HDMI_VERTA_VAL));
	u32 vertb = (VC4_SET_FIELD(0, VC4_HDMI_VERTB_VSPO) |
		     VC4_SET_FIELD(mode->crtc_vtotal - mode->crtc_vsync_end,
				   VC4_HDMI_VERTB_VBP));
	u32 vertb_even = (VC4_SET_FIELD(0, VC4_HDMI_VERTB_VSPO) |
			  VC4_SET_FIELD(mode->crtc_vtotal -
					mode->crtc_vsync_end -
					पूर्णांकerlaced,
					VC4_HDMI_VERTB_VBP));

	HDMI_WRITE(HDMI_HORZA,
		   (vsync_pos ? VC4_HDMI_HORZA_VPOS : 0) |
		   (hsync_pos ? VC4_HDMI_HORZA_HPOS : 0) |
		   VC4_SET_FIELD(mode->hdisplay * pixel_rep,
				 VC4_HDMI_HORZA_HAP));

	HDMI_WRITE(HDMI_HORZB,
		   VC4_SET_FIELD((mode->htotal -
				  mode->hsync_end) * pixel_rep,
				 VC4_HDMI_HORZB_HBP) |
		   VC4_SET_FIELD((mode->hsync_end -
				  mode->hsync_start) * pixel_rep,
				 VC4_HDMI_HORZB_HSP) |
		   VC4_SET_FIELD((mode->hsync_start -
				  mode->hdisplay) * pixel_rep,
				 VC4_HDMI_HORZB_HFP));

	HDMI_WRITE(HDMI_VERTA0, verta);
	HDMI_WRITE(HDMI_VERTA1, verta);

	HDMI_WRITE(HDMI_VERTB0, vertb_even);
	HDMI_WRITE(HDMI_VERTB1, vertb);
पूर्ण

अटल व्योम vc5_hdmi_set_timings(काष्ठा vc4_hdmi *vc4_hdmi,
				 काष्ठा drm_connector_state *state,
				 काष्ठा drm_display_mode *mode)
अणु
	bool hsync_pos = mode->flags & DRM_MODE_FLAG_PHSYNC;
	bool vsync_pos = mode->flags & DRM_MODE_FLAG_PVSYNC;
	bool पूर्णांकerlaced = mode->flags & DRM_MODE_FLAG_INTERLACE;
	u32 pixel_rep = (mode->flags & DRM_MODE_FLAG_DBLCLK) ? 2 : 1;
	u32 verta = (VC4_SET_FIELD(mode->crtc_vsync_end - mode->crtc_vsync_start,
				   VC5_HDMI_VERTA_VSP) |
		     VC4_SET_FIELD(mode->crtc_vsync_start - mode->crtc_vdisplay,
				   VC5_HDMI_VERTA_VFP) |
		     VC4_SET_FIELD(mode->crtc_vdisplay, VC5_HDMI_VERTA_VAL));
	u32 vertb = (VC4_SET_FIELD(0, VC5_HDMI_VERTB_VSPO) |
		     VC4_SET_FIELD(mode->crtc_vtotal - mode->crtc_vsync_end,
				   VC4_HDMI_VERTB_VBP));
	u32 vertb_even = (VC4_SET_FIELD(0, VC5_HDMI_VERTB_VSPO) |
			  VC4_SET_FIELD(mode->crtc_vtotal -
					mode->crtc_vsync_end -
					पूर्णांकerlaced,
					VC4_HDMI_VERTB_VBP));
	अचिन्हित अक्षर gcp;
	bool gcp_en;
	u32 reg;

	HDMI_WRITE(HDMI_VEC_INTERFACE_XBAR, 0x354021);
	HDMI_WRITE(HDMI_HORZA,
		   (vsync_pos ? VC5_HDMI_HORZA_VPOS : 0) |
		   (hsync_pos ? VC5_HDMI_HORZA_HPOS : 0) |
		   VC4_SET_FIELD(mode->hdisplay * pixel_rep,
				 VC5_HDMI_HORZA_HAP) |
		   VC4_SET_FIELD((mode->hsync_start -
				  mode->hdisplay) * pixel_rep,
				 VC5_HDMI_HORZA_HFP));

	HDMI_WRITE(HDMI_HORZB,
		   VC4_SET_FIELD((mode->htotal -
				  mode->hsync_end) * pixel_rep,
				 VC5_HDMI_HORZB_HBP) |
		   VC4_SET_FIELD((mode->hsync_end -
				  mode->hsync_start) * pixel_rep,
				 VC5_HDMI_HORZB_HSP));

	HDMI_WRITE(HDMI_VERTA0, verta);
	HDMI_WRITE(HDMI_VERTA1, verta);

	HDMI_WRITE(HDMI_VERTB0, vertb_even);
	HDMI_WRITE(HDMI_VERTB1, vertb);

	चयन (state->max_bpc) अणु
	हाल 12:
		gcp = 6;
		gcp_en = true;
		अवरोध;
	हाल 10:
		gcp = 5;
		gcp_en = true;
		अवरोध;
	हाल 8:
	शेष:
		gcp = 4;
		gcp_en = false;
		अवरोध;
	पूर्ण

	reg = HDMI_READ(HDMI_DEEP_COLOR_CONFIG_1);
	reg &= ~(VC5_HDMI_DEEP_COLOR_CONFIG_1_INIT_PACK_PHASE_MASK |
		 VC5_HDMI_DEEP_COLOR_CONFIG_1_COLOR_DEPTH_MASK);
	reg |= VC4_SET_FIELD(2, VC5_HDMI_DEEP_COLOR_CONFIG_1_INIT_PACK_PHASE) |
	       VC4_SET_FIELD(gcp, VC5_HDMI_DEEP_COLOR_CONFIG_1_COLOR_DEPTH);
	HDMI_WRITE(HDMI_DEEP_COLOR_CONFIG_1, reg);

	reg = HDMI_READ(HDMI_GCP_WORD_1);
	reg &= ~VC5_HDMI_GCP_WORD_1_GCP_SUBPACKET_BYTE_1_MASK;
	reg |= VC4_SET_FIELD(gcp, VC5_HDMI_GCP_WORD_1_GCP_SUBPACKET_BYTE_1);
	HDMI_WRITE(HDMI_GCP_WORD_1, reg);

	reg = HDMI_READ(HDMI_GCP_CONFIG);
	reg &= ~VC5_HDMI_GCP_CONFIG_GCP_ENABLE;
	reg |= gcp_en ? VC5_HDMI_GCP_CONFIG_GCP_ENABLE : 0;
	HDMI_WRITE(HDMI_GCP_CONFIG, reg);

	HDMI_WRITE(HDMI_CLOCK_STOP, 0);
पूर्ण

अटल व्योम vc4_hdmi_recenter_fअगरo(काष्ठा vc4_hdmi *vc4_hdmi)
अणु
	u32 drअगरt;
	पूर्णांक ret;

	drअगरt = HDMI_READ(HDMI_FIFO_CTL);
	drअगरt &= VC4_HDMI_FIFO_VALID_WRITE_MASK;

	HDMI_WRITE(HDMI_FIFO_CTL,
		   drअगरt & ~VC4_HDMI_FIFO_CTL_RECENTER);
	HDMI_WRITE(HDMI_FIFO_CTL,
		   drअगरt | VC4_HDMI_FIFO_CTL_RECENTER);
	usleep_range(1000, 1100);
	HDMI_WRITE(HDMI_FIFO_CTL,
		   drअगरt & ~VC4_HDMI_FIFO_CTL_RECENTER);
	HDMI_WRITE(HDMI_FIFO_CTL,
		   drअगरt | VC4_HDMI_FIFO_CTL_RECENTER);

	ret = रुको_क्रम(HDMI_READ(HDMI_FIFO_CTL) &
		       VC4_HDMI_FIFO_CTL_RECENTER_DONE, 1);
	WARN_ONCE(ret, "Timeout waiting for "
		  "VC4_HDMI_FIFO_CTL_RECENTER_DONE");
पूर्ण

अटल काष्ठा drm_connector_state *
vc4_hdmi_encoder_get_connector_state(काष्ठा drm_encoder *encoder,
				     काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_connector_state *conn_state;
	काष्ठा drm_connector *connector;
	अचिन्हित पूर्णांक i;

	क्रम_each_new_connector_in_state(state, connector, conn_state, i) अणु
		अगर (conn_state->best_encoder == encoder)
			वापस conn_state;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम vc4_hdmi_encoder_pre_crtc_configure(काष्ठा drm_encoder *encoder,
						काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_connector_state *conn_state =
		vc4_hdmi_encoder_get_connector_state(encoder, state);
	काष्ठा vc4_hdmi_connector_state *vc4_conn_state =
		conn_state_to_vc4_hdmi_conn_state(conn_state);
	काष्ठा drm_display_mode *mode = &encoder->crtc->state->adjusted_mode;
	काष्ठा vc4_hdmi *vc4_hdmi = encoder_to_vc4_hdmi(encoder);
	अचिन्हित दीर्घ pixel_rate, hsm_rate;
	पूर्णांक ret;

	ret = pm_runसमय_get_sync(&vc4_hdmi->pdev->dev);
	अगर (ret < 0) अणु
		DRM_ERROR("Failed to retain power domain: %d\n", ret);
		वापस;
	पूर्ण

	pixel_rate = vc4_conn_state->pixel_rate;
	ret = clk_set_rate(vc4_hdmi->pixel_घड़ी, pixel_rate);
	अगर (ret) अणु
		DRM_ERROR("Failed to set pixel clock rate: %d\n", ret);
		वापस;
	पूर्ण

	ret = clk_prepare_enable(vc4_hdmi->pixel_घड़ी);
	अगर (ret) अणु
		DRM_ERROR("Failed to turn on pixel clock: %d\n", ret);
		वापस;
	पूर्ण

	/*
	 * As stated in RPi's vc4 firmware "HDMI state machine (HSM) घड़ी must
	 * be faster than pixel घड़ी, infinitesimally faster, tested in
	 * simulation. Otherwise, exact value is unimportant क्रम HDMI
	 * operation." This conflicts with bcm2835's vc4 करोcumentation, which
	 * states HSM's घड़ी has to be at least 108% of the pixel घड़ी.
	 *
	 * Real lअगरe tests reveal that vc4's firmware statement holds up, and
	 * users are able to use pixel घड़ीs बंदr to HSM's, namely क्रम
	 * 1920x1200@60Hz. So it was decided to have leave a 1% margin between
	 * both घड़ीs. Which, क्रम RPi0-3 implies a maximum pixel घड़ी of
	 * 162MHz.
	 *
	 * Additionally, the AXI घड़ी needs to be at least 25% of
	 * pixel घड़ी, but HSM ends up being the limiting factor.
	 */
	hsm_rate = max_t(अचिन्हित दीर्घ, 120000000, (pixel_rate / 100) * 101);
	ret = clk_set_min_rate(vc4_hdmi->hsm_घड़ी, hsm_rate);
	अगर (ret) अणु
		DRM_ERROR("Failed to set HSM clock rate: %d\n", ret);
		वापस;
	पूर्ण

	ret = clk_prepare_enable(vc4_hdmi->hsm_घड़ी);
	अगर (ret) अणु
		DRM_ERROR("Failed to turn on HSM clock: %d\n", ret);
		clk_disable_unprepare(vc4_hdmi->pixel_घड़ी);
		वापस;
	पूर्ण

	vc4_hdmi_cec_update_clk_भाग(vc4_hdmi);

	/*
	 * FIXME: When the pixel freq is 594MHz (4k60), this needs to be setup
	 * at 300MHz.
	 */
	ret = clk_set_min_rate(vc4_hdmi->pixel_bvb_घड़ी,
			       (hsm_rate > VC4_HSM_MID_CLOCK ? 150000000 : 75000000));
	अगर (ret) अणु
		DRM_ERROR("Failed to set pixel bvb clock rate: %d\n", ret);
		clk_disable_unprepare(vc4_hdmi->hsm_घड़ी);
		clk_disable_unprepare(vc4_hdmi->pixel_घड़ी);
		वापस;
	पूर्ण

	ret = clk_prepare_enable(vc4_hdmi->pixel_bvb_घड़ी);
	अगर (ret) अणु
		DRM_ERROR("Failed to turn on pixel bvb clock: %d\n", ret);
		clk_disable_unprepare(vc4_hdmi->hsm_घड़ी);
		clk_disable_unprepare(vc4_hdmi->pixel_घड़ी);
		वापस;
	पूर्ण

	अगर (vc4_hdmi->variant->phy_init)
		vc4_hdmi->variant->phy_init(vc4_hdmi, vc4_conn_state);

	HDMI_WRITE(HDMI_SCHEDULER_CONTROL,
		   HDMI_READ(HDMI_SCHEDULER_CONTROL) |
		   VC4_HDMI_SCHEDULER_CONTROL_MANUAL_FORMAT |
		   VC4_HDMI_SCHEDULER_CONTROL_IGNORE_VSYNC_PREDICTS);

	अगर (vc4_hdmi->variant->set_timings)
		vc4_hdmi->variant->set_timings(vc4_hdmi, conn_state, mode);
पूर्ण

अटल व्योम vc4_hdmi_encoder_pre_crtc_enable(काष्ठा drm_encoder *encoder,
					     काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_display_mode *mode = &encoder->crtc->state->adjusted_mode;
	काष्ठा vc4_hdmi_encoder *vc4_encoder = to_vc4_hdmi_encoder(encoder);
	काष्ठा vc4_hdmi *vc4_hdmi = encoder_to_vc4_hdmi(encoder);

	अगर (vc4_encoder->hdmi_monitor &&
	    drm_शेष_rgb_quant_range(mode) == HDMI_QUANTIZATION_RANGE_LIMITED) अणु
		अगर (vc4_hdmi->variant->csc_setup)
			vc4_hdmi->variant->csc_setup(vc4_hdmi, true);

		vc4_encoder->limited_rgb_range = true;
	पूर्ण अन्यथा अणु
		अगर (vc4_hdmi->variant->csc_setup)
			vc4_hdmi->variant->csc_setup(vc4_hdmi, false);

		vc4_encoder->limited_rgb_range = false;
	पूर्ण

	HDMI_WRITE(HDMI_FIFO_CTL, VC4_HDMI_FIFO_CTL_MASTER_SLAVE_N);
पूर्ण

अटल व्योम vc4_hdmi_encoder_post_crtc_enable(काष्ठा drm_encoder *encoder,
					      काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_display_mode *mode = &encoder->crtc->state->adjusted_mode;
	काष्ठा vc4_hdmi *vc4_hdmi = encoder_to_vc4_hdmi(encoder);
	काष्ठा vc4_hdmi_encoder *vc4_encoder = to_vc4_hdmi_encoder(encoder);
	bool hsync_pos = mode->flags & DRM_MODE_FLAG_PHSYNC;
	bool vsync_pos = mode->flags & DRM_MODE_FLAG_PVSYNC;
	पूर्णांक ret;

	HDMI_WRITE(HDMI_VID_CTL,
		   VC4_HD_VID_CTL_ENABLE |
		   VC4_HD_VID_CTL_UNDERFLOW_ENABLE |
		   VC4_HD_VID_CTL_FRAME_COUNTER_RESET |
		   (vsync_pos ? 0 : VC4_HD_VID_CTL_VSYNC_LOW) |
		   (hsync_pos ? 0 : VC4_HD_VID_CTL_HSYNC_LOW));

	HDMI_WRITE(HDMI_VID_CTL,
		   HDMI_READ(HDMI_VID_CTL) & ~VC4_HD_VID_CTL_BLANKPIX);

	अगर (vc4_encoder->hdmi_monitor) अणु
		HDMI_WRITE(HDMI_SCHEDULER_CONTROL,
			   HDMI_READ(HDMI_SCHEDULER_CONTROL) |
			   VC4_HDMI_SCHEDULER_CONTROL_MODE_HDMI);

		ret = रुको_क्रम(HDMI_READ(HDMI_SCHEDULER_CONTROL) &
			       VC4_HDMI_SCHEDULER_CONTROL_HDMI_ACTIVE, 1000);
		WARN_ONCE(ret, "Timeout waiting for "
			  "VC4_HDMI_SCHEDULER_CONTROL_HDMI_ACTIVE\n");
	पूर्ण अन्यथा अणु
		HDMI_WRITE(HDMI_RAM_PACKET_CONFIG,
			   HDMI_READ(HDMI_RAM_PACKET_CONFIG) &
			   ~(VC4_HDMI_RAM_PACKET_ENABLE));
		HDMI_WRITE(HDMI_SCHEDULER_CONTROL,
			   HDMI_READ(HDMI_SCHEDULER_CONTROL) &
			   ~VC4_HDMI_SCHEDULER_CONTROL_MODE_HDMI);

		ret = रुको_क्रम(!(HDMI_READ(HDMI_SCHEDULER_CONTROL) &
				 VC4_HDMI_SCHEDULER_CONTROL_HDMI_ACTIVE), 1000);
		WARN_ONCE(ret, "Timeout waiting for "
			  "!VC4_HDMI_SCHEDULER_CONTROL_HDMI_ACTIVE\n");
	पूर्ण

	अगर (vc4_encoder->hdmi_monitor) अणु
		WARN_ON(!(HDMI_READ(HDMI_SCHEDULER_CONTROL) &
			  VC4_HDMI_SCHEDULER_CONTROL_HDMI_ACTIVE));
		HDMI_WRITE(HDMI_SCHEDULER_CONTROL,
			   HDMI_READ(HDMI_SCHEDULER_CONTROL) |
			   VC4_HDMI_SCHEDULER_CONTROL_VERT_ALWAYS_KEEPOUT);

		HDMI_WRITE(HDMI_RAM_PACKET_CONFIG,
			   VC4_HDMI_RAM_PACKET_ENABLE);

		vc4_hdmi_set_infoframes(encoder);
	पूर्ण

	vc4_hdmi_recenter_fअगरo(vc4_hdmi);
पूर्ण

अटल व्योम vc4_hdmi_encoder_enable(काष्ठा drm_encoder *encoder)
अणु
पूर्ण

#घोषणा WIFI_2_4GHz_CH1_MIN_FREQ	2400000000ULL
#घोषणा WIFI_2_4GHz_CH1_MAX_FREQ	2422000000ULL

अटल पूर्णांक vc4_hdmi_encoder_atomic_check(काष्ठा drm_encoder *encoder,
					 काष्ठा drm_crtc_state *crtc_state,
					 काष्ठा drm_connector_state *conn_state)
अणु
	काष्ठा vc4_hdmi_connector_state *vc4_state = conn_state_to_vc4_hdmi_conn_state(conn_state);
	काष्ठा drm_display_mode *mode = &crtc_state->adjusted_mode;
	काष्ठा vc4_hdmi *vc4_hdmi = encoder_to_vc4_hdmi(encoder);
	अचिन्हित दीर्घ दीर्घ pixel_rate = mode->घड़ी * 1000;
	अचिन्हित दीर्घ दीर्घ पंचांगds_rate;

	अगर (vc4_hdmi->variant->unsupported_odd_h_timings &&
	    ((mode->hdisplay % 2) || (mode->hsync_start % 2) ||
	     (mode->hsync_end % 2) || (mode->htotal % 2)))
		वापस -EINVAL;

	/*
	 * The 1440p@60 pixel rate is in the same range than the first
	 * WiFi channel (between 2.4GHz and 2.422GHz with 22MHz
	 * bandwidth). Slightly lower the frequency to bring it out of
	 * the WiFi range.
	 */
	पंचांगds_rate = pixel_rate * 10;
	अगर (vc4_hdmi->disable_wअगरi_frequencies &&
	    (पंचांगds_rate >= WIFI_2_4GHz_CH1_MIN_FREQ &&
	     पंचांगds_rate <= WIFI_2_4GHz_CH1_MAX_FREQ)) अणु
		mode->घड़ी = 238560;
		pixel_rate = mode->घड़ी * 1000;
	पूर्ण

	अगर (conn_state->max_bpc == 12) अणु
		pixel_rate = pixel_rate * 150;
		करो_भाग(pixel_rate, 100);
	पूर्ण अन्यथा अगर (conn_state->max_bpc == 10) अणु
		pixel_rate = pixel_rate * 125;
		करो_भाग(pixel_rate, 100);
	पूर्ण

	अगर (mode->flags & DRM_MODE_FLAG_DBLCLK)
		pixel_rate = pixel_rate * 2;

	अगर (pixel_rate > vc4_hdmi->variant->max_pixel_घड़ी)
		वापस -EINVAL;

	vc4_state->pixel_rate = pixel_rate;

	वापस 0;
पूर्ण

अटल क्रमागत drm_mode_status
vc4_hdmi_encoder_mode_valid(काष्ठा drm_encoder *encoder,
			    स्थिर काष्ठा drm_display_mode *mode)
अणु
	काष्ठा vc4_hdmi *vc4_hdmi = encoder_to_vc4_hdmi(encoder);

	अगर (vc4_hdmi->variant->unsupported_odd_h_timings &&
	    ((mode->hdisplay % 2) || (mode->hsync_start % 2) ||
	     (mode->hsync_end % 2) || (mode->htotal % 2)))
		वापस MODE_H_ILLEGAL;

	अगर ((mode->घड़ी * 1000) > vc4_hdmi->variant->max_pixel_घड़ी)
		वापस MODE_CLOCK_HIGH;

	वापस MODE_OK;
पूर्ण

अटल स्थिर काष्ठा drm_encoder_helper_funcs vc4_hdmi_encoder_helper_funcs = अणु
	.atomic_check = vc4_hdmi_encoder_atomic_check,
	.mode_valid = vc4_hdmi_encoder_mode_valid,
	.disable = vc4_hdmi_encoder_disable,
	.enable = vc4_hdmi_encoder_enable,
पूर्ण;

अटल u32 vc4_hdmi_channel_map(काष्ठा vc4_hdmi *vc4_hdmi, u32 channel_mask)
अणु
	पूर्णांक i;
	u32 channel_map = 0;

	क्रम (i = 0; i < 8; i++) अणु
		अगर (channel_mask & BIT(i))
			channel_map |= i << (3 * i);
	पूर्ण
	वापस channel_map;
पूर्ण

अटल u32 vc5_hdmi_channel_map(काष्ठा vc4_hdmi *vc4_hdmi, u32 channel_mask)
अणु
	पूर्णांक i;
	u32 channel_map = 0;

	क्रम (i = 0; i < 8; i++) अणु
		अगर (channel_mask & BIT(i))
			channel_map |= i << (4 * i);
	पूर्ण
	वापस channel_map;
पूर्ण

/* HDMI audio codec callbacks */
अटल व्योम vc4_hdmi_audio_set_mai_घड़ी(काष्ठा vc4_hdmi *vc4_hdmi)
अणु
	u32 hsm_घड़ी = clk_get_rate(vc4_hdmi->audio_घड़ी);
	अचिन्हित दीर्घ n, m;

	rational_best_approximation(hsm_घड़ी, vc4_hdmi->audio.samplerate,
				    VC4_HD_MAI_SMP_N_MASK >>
				    VC4_HD_MAI_SMP_N_SHIFT,
				    (VC4_HD_MAI_SMP_M_MASK >>
				     VC4_HD_MAI_SMP_M_SHIFT) + 1,
				    &n, &m);

	HDMI_WRITE(HDMI_MAI_SMP,
		   VC4_SET_FIELD(n, VC4_HD_MAI_SMP_N) |
		   VC4_SET_FIELD(m - 1, VC4_HD_MAI_SMP_M));
पूर्ण

अटल व्योम vc4_hdmi_set_n_cts(काष्ठा vc4_hdmi *vc4_hdmi)
अणु
	काष्ठा drm_encoder *encoder = &vc4_hdmi->encoder.base.base;
	काष्ठा drm_crtc *crtc = encoder->crtc;
	स्थिर काष्ठा drm_display_mode *mode = &crtc->state->adjusted_mode;
	u32 samplerate = vc4_hdmi->audio.samplerate;
	u32 n, cts;
	u64 पंचांगp;

	n = 128 * samplerate / 1000;
	पंचांगp = (u64)(mode->घड़ी * 1000) * n;
	करो_भाग(पंचांगp, 128 * samplerate);
	cts = पंचांगp;

	HDMI_WRITE(HDMI_CRP_CFG,
		   VC4_HDMI_CRP_CFG_EXTERNAL_CTS_EN |
		   VC4_SET_FIELD(n, VC4_HDMI_CRP_CFG_N));

	/*
	 * We could get slightly more accurate घड़ीs in some हालs by
	 * providing a CTS_1 value.  The two CTS values are alternated
	 * between based on the period fields
	 */
	HDMI_WRITE(HDMI_CTS_0, cts);
	HDMI_WRITE(HDMI_CTS_1, cts);
पूर्ण

अटल अंतरभूत काष्ठा vc4_hdmi *dai_to_hdmi(काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_card *card = snd_soc_dai_get_drvdata(dai);

	वापस snd_soc_card_get_drvdata(card);
पूर्ण

अटल पूर्णांक vc4_hdmi_audio_startup(काष्ठा snd_pcm_substream *substream,
				  काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा vc4_hdmi *vc4_hdmi = dai_to_hdmi(dai);
	काष्ठा drm_encoder *encoder = &vc4_hdmi->encoder.base.base;
	काष्ठा drm_connector *connector = &vc4_hdmi->connector;
	पूर्णांक ret;

	अगर (vc4_hdmi->audio.substream && vc4_hdmi->audio.substream != substream)
		वापस -EINVAL;

	vc4_hdmi->audio.substream = substream;

	/*
	 * If the HDMI encoder hasn't probed, or the encoder is
	 * currently in DVI mode, treat the codec dai as missing.
	 */
	अगर (!encoder->crtc || !(HDMI_READ(HDMI_RAM_PACKET_CONFIG) &
				VC4_HDMI_RAM_PACKET_ENABLE))
		वापस -ENODEV;

	ret = snd_pcm_hw_स्थिरraपूर्णांक_eld(substream->runसमय, connector->eld);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक vc4_hdmi_audio_set_fmt(काष्ठा snd_soc_dai *dai, अचिन्हित पूर्णांक fmt)
अणु
	वापस 0;
पूर्ण

अटल व्योम vc4_hdmi_audio_reset(काष्ठा vc4_hdmi *vc4_hdmi)
अणु
	काष्ठा drm_encoder *encoder = &vc4_hdmi->encoder.base.base;
	काष्ठा device *dev = &vc4_hdmi->pdev->dev;
	पूर्णांक ret;

	vc4_hdmi->audio.streaming = false;
	ret = vc4_hdmi_stop_packet(encoder, HDMI_INFOFRAME_TYPE_AUDIO, false);
	अगर (ret)
		dev_err(dev, "Failed to stop audio infoframe: %d\n", ret);

	HDMI_WRITE(HDMI_MAI_CTL, VC4_HD_MAI_CTL_RESET);
	HDMI_WRITE(HDMI_MAI_CTL, VC4_HD_MAI_CTL_ERRORF);
	HDMI_WRITE(HDMI_MAI_CTL, VC4_HD_MAI_CTL_FLUSH);
पूर्ण

अटल व्योम vc4_hdmi_audio_shutकरोwn(काष्ठा snd_pcm_substream *substream,
				    काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा vc4_hdmi *vc4_hdmi = dai_to_hdmi(dai);

	अगर (substream != vc4_hdmi->audio.substream)
		वापस;

	vc4_hdmi_audio_reset(vc4_hdmi);

	vc4_hdmi->audio.substream = शून्य;
पूर्ण

/* HDMI audio codec callbacks */
अटल पूर्णांक vc4_hdmi_audio_hw_params(काष्ठा snd_pcm_substream *substream,
				    काष्ठा snd_pcm_hw_params *params,
				    काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा vc4_hdmi *vc4_hdmi = dai_to_hdmi(dai);
	काष्ठा drm_encoder *encoder = &vc4_hdmi->encoder.base.base;
	काष्ठा device *dev = &vc4_hdmi->pdev->dev;
	u32 audio_packet_config, channel_mask;
	u32 channel_map;

	अगर (substream != vc4_hdmi->audio.substream)
		वापस -EINVAL;

	dev_dbg(dev, "%s: %u Hz, %d bit, %d channels\n", __func__,
		params_rate(params), params_width(params),
		params_channels(params));

	vc4_hdmi->audio.channels = params_channels(params);
	vc4_hdmi->audio.samplerate = params_rate(params);

	HDMI_WRITE(HDMI_MAI_CTL,
		   VC4_HD_MAI_CTL_RESET |
		   VC4_HD_MAI_CTL_FLUSH |
		   VC4_HD_MAI_CTL_DLATE |
		   VC4_HD_MAI_CTL_ERRORE |
		   VC4_HD_MAI_CTL_ERRORF);

	vc4_hdmi_audio_set_mai_घड़ी(vc4_hdmi);

	/* The B frame identअगरier should match the value used by alsa-lib (8) */
	audio_packet_config =
		VC4_HDMI_AUDIO_PACKET_ZERO_DATA_ON_SAMPLE_FLAT |
		VC4_HDMI_AUDIO_PACKET_ZERO_DATA_ON_INACTIVE_CHANNELS |
		VC4_SET_FIELD(0x8, VC4_HDMI_AUDIO_PACKET_B_FRAME_IDENTIFIER);

	channel_mask = GENMASK(vc4_hdmi->audio.channels - 1, 0);
	audio_packet_config |= VC4_SET_FIELD(channel_mask,
					     VC4_HDMI_AUDIO_PACKET_CEA_MASK);

	/* Set the MAI threshold.  This logic mimics the firmware's. */
	अगर (vc4_hdmi->audio.samplerate > 96000) अणु
		HDMI_WRITE(HDMI_MAI_THR,
			   VC4_SET_FIELD(0x12, VC4_HD_MAI_THR_DREQHIGH) |
			   VC4_SET_FIELD(0x12, VC4_HD_MAI_THR_DREQLOW));
	पूर्ण अन्यथा अगर (vc4_hdmi->audio.samplerate > 48000) अणु
		HDMI_WRITE(HDMI_MAI_THR,
			   VC4_SET_FIELD(0x14, VC4_HD_MAI_THR_DREQHIGH) |
			   VC4_SET_FIELD(0x12, VC4_HD_MAI_THR_DREQLOW));
	पूर्ण अन्यथा अणु
		HDMI_WRITE(HDMI_MAI_THR,
			   VC4_SET_FIELD(0x10, VC4_HD_MAI_THR_PANICHIGH) |
			   VC4_SET_FIELD(0x10, VC4_HD_MAI_THR_PANICLOW) |
			   VC4_SET_FIELD(0x10, VC4_HD_MAI_THR_DREQHIGH) |
			   VC4_SET_FIELD(0x10, VC4_HD_MAI_THR_DREQLOW));
	पूर्ण

	HDMI_WRITE(HDMI_MAI_CONFIG,
		   VC4_HDMI_MAI_CONFIG_BIT_REVERSE |
		   VC4_SET_FIELD(channel_mask, VC4_HDMI_MAI_CHANNEL_MASK));

	channel_map = vc4_hdmi->variant->channel_map(vc4_hdmi, channel_mask);
	HDMI_WRITE(HDMI_MAI_CHANNEL_MAP, channel_map);
	HDMI_WRITE(HDMI_AUDIO_PACKET_CONFIG, audio_packet_config);
	vc4_hdmi_set_n_cts(vc4_hdmi);

	vc4_hdmi_set_audio_infoframe(encoder);

	वापस 0;
पूर्ण

अटल पूर्णांक vc4_hdmi_audio_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd,
				  काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा vc4_hdmi *vc4_hdmi = dai_to_hdmi(dai);

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
		vc4_hdmi->audio.streaming = true;

		अगर (vc4_hdmi->variant->phy_rng_enable)
			vc4_hdmi->variant->phy_rng_enable(vc4_hdmi);

		HDMI_WRITE(HDMI_MAI_CTL,
			   VC4_SET_FIELD(vc4_hdmi->audio.channels,
					 VC4_HD_MAI_CTL_CHNUM) |
			   VC4_HD_MAI_CTL_ENABLE);
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
		HDMI_WRITE(HDMI_MAI_CTL,
			   VC4_HD_MAI_CTL_DLATE |
			   VC4_HD_MAI_CTL_ERRORE |
			   VC4_HD_MAI_CTL_ERRORF);

		अगर (vc4_hdmi->variant->phy_rng_disable)
			vc4_hdmi->variant->phy_rng_disable(vc4_hdmi);

		vc4_hdmi->audio.streaming = false;

		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत काष्ठा vc4_hdmi *
snd_component_to_hdmi(काष्ठा snd_soc_component *component)
अणु
	काष्ठा snd_soc_card *card = snd_soc_component_get_drvdata(component);

	वापस snd_soc_card_get_drvdata(card);
पूर्ण

अटल पूर्णांक vc4_hdmi_audio_eld_ctl_info(काष्ठा snd_kcontrol *kcontrol,
				       काष्ठा snd_ctl_elem_info *uinfo)
अणु
	काष्ठा snd_soc_component *component = snd_kcontrol_chip(kcontrol);
	काष्ठा vc4_hdmi *vc4_hdmi = snd_component_to_hdmi(component);
	काष्ठा drm_connector *connector = &vc4_hdmi->connector;

	uinfo->type = SNDRV_CTL_ELEM_TYPE_BYTES;
	uinfo->count = माप(connector->eld);

	वापस 0;
पूर्ण

अटल पूर्णांक vc4_hdmi_audio_eld_ctl_get(काष्ठा snd_kcontrol *kcontrol,
				      काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_kcontrol_chip(kcontrol);
	काष्ठा vc4_hdmi *vc4_hdmi = snd_component_to_hdmi(component);
	काष्ठा drm_connector *connector = &vc4_hdmi->connector;

	स_नकल(ucontrol->value.bytes.data, connector->eld,
	       माप(connector->eld));

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new vc4_hdmi_audio_controls[] = अणु
	अणु
		.access = SNDRV_CTL_ELEM_ACCESS_READ |
			  SNDRV_CTL_ELEM_ACCESS_VOLATILE,
		.अगरace = SNDRV_CTL_ELEM_IFACE_PCM,
		.name = "ELD",
		.info = vc4_hdmi_audio_eld_ctl_info,
		.get = vc4_hdmi_audio_eld_ctl_get,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget vc4_hdmi_audio_widमाला_लो[] = अणु
	SND_SOC_DAPM_OUTPUT("TX"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route vc4_hdmi_audio_routes[] = अणु
	अणु "TX", शून्य, "Playback" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver vc4_hdmi_audio_component_drv = अणु
	.name			= "vc4-hdmi-codec-dai-component",
	.controls		= vc4_hdmi_audio_controls,
	.num_controls		= ARRAY_SIZE(vc4_hdmi_audio_controls),
	.dapm_widमाला_लो		= vc4_hdmi_audio_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(vc4_hdmi_audio_widमाला_लो),
	.dapm_routes		= vc4_hdmi_audio_routes,
	.num_dapm_routes	= ARRAY_SIZE(vc4_hdmi_audio_routes),
	.idle_bias_on		= 1,
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dai_ops vc4_hdmi_audio_dai_ops = अणु
	.startup = vc4_hdmi_audio_startup,
	.shutकरोwn = vc4_hdmi_audio_shutकरोwn,
	.hw_params = vc4_hdmi_audio_hw_params,
	.set_fmt = vc4_hdmi_audio_set_fmt,
	.trigger = vc4_hdmi_audio_trigger,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver vc4_hdmi_audio_codec_dai_drv = अणु
	.name = "vc4-hdmi-hifi",
	.playback = अणु
		.stream_name = "Playback",
		.channels_min = 2,
		.channels_max = 8,
		.rates = SNDRV_PCM_RATE_32000 | SNDRV_PCM_RATE_44100 |
			 SNDRV_PCM_RATE_48000 | SNDRV_PCM_RATE_88200 |
			 SNDRV_PCM_RATE_96000 | SNDRV_PCM_RATE_176400 |
			 SNDRV_PCM_RATE_192000,
		.क्रमmats = SNDRV_PCM_FMTBIT_IEC958_SUBFRAME_LE,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver vc4_hdmi_audio_cpu_dai_comp = अणु
	.name = "vc4-hdmi-cpu-dai-component",
पूर्ण;

अटल पूर्णांक vc4_hdmi_audio_cpu_dai_probe(काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा vc4_hdmi *vc4_hdmi = dai_to_hdmi(dai);

	snd_soc_dai_init_dma_data(dai, &vc4_hdmi->audio.dma_data, शून्य);

	वापस 0;
पूर्ण

अटल काष्ठा snd_soc_dai_driver vc4_hdmi_audio_cpu_dai_drv = अणु
	.name = "vc4-hdmi-cpu-dai",
	.probe  = vc4_hdmi_audio_cpu_dai_probe,
	.playback = अणु
		.stream_name = "Playback",
		.channels_min = 1,
		.channels_max = 8,
		.rates = SNDRV_PCM_RATE_32000 | SNDRV_PCM_RATE_44100 |
			 SNDRV_PCM_RATE_48000 | SNDRV_PCM_RATE_88200 |
			 SNDRV_PCM_RATE_96000 | SNDRV_PCM_RATE_176400 |
			 SNDRV_PCM_RATE_192000,
		.क्रमmats = SNDRV_PCM_FMTBIT_IEC958_SUBFRAME_LE,
	पूर्ण,
	.ops = &vc4_hdmi_audio_dai_ops,
पूर्ण;

अटल स्थिर काष्ठा snd_dmaengine_pcm_config pcm_conf = अणु
	.chan_names[SNDRV_PCM_STREAM_PLAYBACK] = "audio-rx",
	.prepare_slave_config = snd_dmaengine_pcm_prepare_slave_config,
पूर्ण;

अटल पूर्णांक vc4_hdmi_audio_init(काष्ठा vc4_hdmi *vc4_hdmi)
अणु
	स्थिर काष्ठा vc4_hdmi_रेजिस्टर *mai_data =
		&vc4_hdmi->variant->रेजिस्टरs[HDMI_MAI_DATA];
	काष्ठा snd_soc_dai_link *dai_link = &vc4_hdmi->audio.link;
	काष्ठा snd_soc_card *card = &vc4_hdmi->audio.card;
	काष्ठा device *dev = &vc4_hdmi->pdev->dev;
	स्थिर __be32 *addr;
	पूर्णांक index;
	पूर्णांक ret;

	अगर (!of_find_property(dev->of_node, "dmas", शून्य)) अणु
		dev_warn(dev,
			 "'dmas' DT property is missing, no HDMI audio\n");
		वापस 0;
	पूर्ण

	अगर (mai_data->reg != VC4_HD) अणु
		WARN_ONCE(true, "MAI isn't in the HD block\n");
		वापस -EINVAL;
	पूर्ण

	/*
	 * Get the physical address of VC4_HD_MAI_DATA. We need to retrieve
	 * the bus address specअगरied in the DT, because the physical address
	 * (the one वापसed by platक्रमm_get_resource()) is not appropriate
	 * क्रम DMA transfers.
	 * This VC/MMU should probably be exposed to aव्योम this kind of hacks.
	 */
	index = of_property_match_string(dev->of_node, "reg-names", "hd");
	/* Beक्रमe BCM2711, we करोn't have a named रेजिस्टर range */
	अगर (index < 0)
		index = 1;

	addr = of_get_address(dev->of_node, index, शून्य, शून्य);

	vc4_hdmi->audio.dma_data.addr = be32_to_cpup(addr) + mai_data->offset;
	vc4_hdmi->audio.dma_data.addr_width = DMA_SLAVE_BUSWIDTH_4_BYTES;
	vc4_hdmi->audio.dma_data.maxburst = 2;

	ret = devm_snd_dmaengine_pcm_रेजिस्टर(dev, &pcm_conf, 0);
	अगर (ret) अणु
		dev_err(dev, "Could not register PCM component: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = devm_snd_soc_रेजिस्टर_component(dev, &vc4_hdmi_audio_cpu_dai_comp,
					      &vc4_hdmi_audio_cpu_dai_drv, 1);
	अगर (ret) अणु
		dev_err(dev, "Could not register CPU DAI: %d\n", ret);
		वापस ret;
	पूर्ण

	/* रेजिस्टर component and codec dai */
	ret = devm_snd_soc_रेजिस्टर_component(dev, &vc4_hdmi_audio_component_drv,
				     &vc4_hdmi_audio_codec_dai_drv, 1);
	अगर (ret) अणु
		dev_err(dev, "Could not register component: %d\n", ret);
		वापस ret;
	पूर्ण

	dai_link->cpus		= &vc4_hdmi->audio.cpu;
	dai_link->codecs	= &vc4_hdmi->audio.codec;
	dai_link->platक्रमms	= &vc4_hdmi->audio.platक्रमm;

	dai_link->num_cpus	= 1;
	dai_link->num_codecs	= 1;
	dai_link->num_platक्रमms	= 1;

	dai_link->name = "MAI";
	dai_link->stream_name = "MAI PCM";
	dai_link->codecs->dai_name = vc4_hdmi_audio_codec_dai_drv.name;
	dai_link->cpus->dai_name = dev_name(dev);
	dai_link->codecs->name = dev_name(dev);
	dai_link->platक्रमms->name = dev_name(dev);

	card->dai_link = dai_link;
	card->num_links = 1;
	card->name = vc4_hdmi->variant->card_name;
	card->driver_name = "vc4-hdmi";
	card->dev = dev;
	card->owner = THIS_MODULE;

	/*
	 * Be careful, snd_soc_रेजिस्टर_card() calls dev_set_drvdata() and
	 * stores a poपूर्णांकer to the snd card object in dev->driver_data. This
	 * means we cannot use it क्रम something अन्यथा. The hdmi back-poपूर्णांकer is
	 * now stored in card->drvdata and should be retrieved with
	 * snd_soc_card_get_drvdata() अगर needed.
	 */
	snd_soc_card_set_drvdata(card, vc4_hdmi);
	ret = devm_snd_soc_रेजिस्टर_card(dev, card);
	अगर (ret)
		dev_err(dev, "Could not register sound card: %d\n", ret);

	वापस ret;

पूर्ण

#अगर_घोषित CONFIG_DRM_VC4_HDMI_CEC
अटल irqवापस_t vc4_cec_irq_handler_rx_thपढ़ो(पूर्णांक irq, व्योम *priv)
अणु
	काष्ठा vc4_hdmi *vc4_hdmi = priv;

	अगर (vc4_hdmi->cec_rx_msg.len)
		cec_received_msg(vc4_hdmi->cec_adap,
				 &vc4_hdmi->cec_rx_msg);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t vc4_cec_irq_handler_tx_thपढ़ो(पूर्णांक irq, व्योम *priv)
अणु
	काष्ठा vc4_hdmi *vc4_hdmi = priv;

	अगर (vc4_hdmi->cec_tx_ok) अणु
		cec_transmit_करोne(vc4_hdmi->cec_adap, CEC_TX_STATUS_OK,
				  0, 0, 0, 0);
	पूर्ण अन्यथा अणु
		/*
		 * This CEC implementation makes 1 retry, so अगर we
		 * get a NACK, then that means it made 2 attempts.
		 */
		cec_transmit_करोne(vc4_hdmi->cec_adap, CEC_TX_STATUS_NACK,
				  0, 2, 0, 0);
	पूर्ण
	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t vc4_cec_irq_handler_thपढ़ो(पूर्णांक irq, व्योम *priv)
अणु
	काष्ठा vc4_hdmi *vc4_hdmi = priv;
	irqवापस_t ret;

	अगर (vc4_hdmi->cec_irq_was_rx)
		ret = vc4_cec_irq_handler_rx_thपढ़ो(irq, priv);
	अन्यथा
		ret = vc4_cec_irq_handler_tx_thपढ़ो(irq, priv);

	वापस ret;
पूर्ण

अटल व्योम vc4_cec_पढ़ो_msg(काष्ठा vc4_hdmi *vc4_hdmi, u32 cntrl1)
अणु
	काष्ठा drm_device *dev = vc4_hdmi->connector.dev;
	काष्ठा cec_msg *msg = &vc4_hdmi->cec_rx_msg;
	अचिन्हित पूर्णांक i;

	msg->len = 1 + ((cntrl1 & VC4_HDMI_CEC_REC_WRD_CNT_MASK) >>
					VC4_HDMI_CEC_REC_WRD_CNT_SHIFT);

	अगर (msg->len > 16) अणु
		drm_err(dev, "Attempting to read too much data (%d)\n", msg->len);
		वापस;
	पूर्ण

	क्रम (i = 0; i < msg->len; i += 4) अणु
		u32 val = HDMI_READ(HDMI_CEC_RX_DATA_1 + (i >> 2));

		msg->msg[i] = val & 0xff;
		msg->msg[i + 1] = (val >> 8) & 0xff;
		msg->msg[i + 2] = (val >> 16) & 0xff;
		msg->msg[i + 3] = (val >> 24) & 0xff;
	पूर्ण
पूर्ण

अटल irqवापस_t vc4_cec_irq_handler_tx_bare(पूर्णांक irq, व्योम *priv)
अणु
	काष्ठा vc4_hdmi *vc4_hdmi = priv;
	u32 cntrl1;

	cntrl1 = HDMI_READ(HDMI_CEC_CNTRL_1);
	vc4_hdmi->cec_tx_ok = cntrl1 & VC4_HDMI_CEC_TX_STATUS_GOOD;
	cntrl1 &= ~VC4_HDMI_CEC_START_XMIT_BEGIN;
	HDMI_WRITE(HDMI_CEC_CNTRL_1, cntrl1);

	वापस IRQ_WAKE_THREAD;
पूर्ण

अटल irqवापस_t vc4_cec_irq_handler_rx_bare(पूर्णांक irq, व्योम *priv)
अणु
	काष्ठा vc4_hdmi *vc4_hdmi = priv;
	u32 cntrl1;

	vc4_hdmi->cec_rx_msg.len = 0;
	cntrl1 = HDMI_READ(HDMI_CEC_CNTRL_1);
	vc4_cec_पढ़ो_msg(vc4_hdmi, cntrl1);
	cntrl1 |= VC4_HDMI_CEC_CLEAR_RECEIVE_OFF;
	HDMI_WRITE(HDMI_CEC_CNTRL_1, cntrl1);
	cntrl1 &= ~VC4_HDMI_CEC_CLEAR_RECEIVE_OFF;

	HDMI_WRITE(HDMI_CEC_CNTRL_1, cntrl1);

	वापस IRQ_WAKE_THREAD;
पूर्ण

अटल irqवापस_t vc4_cec_irq_handler(पूर्णांक irq, व्योम *priv)
अणु
	काष्ठा vc4_hdmi *vc4_hdmi = priv;
	u32 stat = HDMI_READ(HDMI_CEC_CPU_STATUS);
	irqवापस_t ret;
	u32 cntrl5;

	अगर (!(stat & VC4_HDMI_CPU_CEC))
		वापस IRQ_NONE;

	cntrl5 = HDMI_READ(HDMI_CEC_CNTRL_5);
	vc4_hdmi->cec_irq_was_rx = cntrl5 & VC4_HDMI_CEC_RX_CEC_INT;
	अगर (vc4_hdmi->cec_irq_was_rx)
		ret = vc4_cec_irq_handler_rx_bare(irq, priv);
	अन्यथा
		ret = vc4_cec_irq_handler_tx_bare(irq, priv);

	HDMI_WRITE(HDMI_CEC_CPU_CLEAR, VC4_HDMI_CPU_CEC);
	वापस ret;
पूर्ण

अटल पूर्णांक vc4_hdmi_cec_adap_enable(काष्ठा cec_adapter *adap, bool enable)
अणु
	काष्ठा vc4_hdmi *vc4_hdmi = cec_get_drvdata(adap);
	/* घड़ी period in microseconds */
	स्थिर u32 usecs = 1000000 / CEC_CLOCK_FREQ;
	u32 val = HDMI_READ(HDMI_CEC_CNTRL_5);

	val &= ~(VC4_HDMI_CEC_TX_SW_RESET | VC4_HDMI_CEC_RX_SW_RESET |
		 VC4_HDMI_CEC_CNT_TO_4700_US_MASK |
		 VC4_HDMI_CEC_CNT_TO_4500_US_MASK);
	val |= ((4700 / usecs) << VC4_HDMI_CEC_CNT_TO_4700_US_SHIFT) |
	       ((4500 / usecs) << VC4_HDMI_CEC_CNT_TO_4500_US_SHIFT);

	अगर (enable) अणु
		HDMI_WRITE(HDMI_CEC_CNTRL_5, val |
			   VC4_HDMI_CEC_TX_SW_RESET | VC4_HDMI_CEC_RX_SW_RESET);
		HDMI_WRITE(HDMI_CEC_CNTRL_5, val);
		HDMI_WRITE(HDMI_CEC_CNTRL_2,
			   ((1500 / usecs) << VC4_HDMI_CEC_CNT_TO_1500_US_SHIFT) |
			   ((1300 / usecs) << VC4_HDMI_CEC_CNT_TO_1300_US_SHIFT) |
			   ((800 / usecs) << VC4_HDMI_CEC_CNT_TO_800_US_SHIFT) |
			   ((600 / usecs) << VC4_HDMI_CEC_CNT_TO_600_US_SHIFT) |
			   ((400 / usecs) << VC4_HDMI_CEC_CNT_TO_400_US_SHIFT));
		HDMI_WRITE(HDMI_CEC_CNTRL_3,
			   ((2750 / usecs) << VC4_HDMI_CEC_CNT_TO_2750_US_SHIFT) |
			   ((2400 / usecs) << VC4_HDMI_CEC_CNT_TO_2400_US_SHIFT) |
			   ((2050 / usecs) << VC4_HDMI_CEC_CNT_TO_2050_US_SHIFT) |
			   ((1700 / usecs) << VC4_HDMI_CEC_CNT_TO_1700_US_SHIFT));
		HDMI_WRITE(HDMI_CEC_CNTRL_4,
			   ((4300 / usecs) << VC4_HDMI_CEC_CNT_TO_4300_US_SHIFT) |
			   ((3900 / usecs) << VC4_HDMI_CEC_CNT_TO_3900_US_SHIFT) |
			   ((3600 / usecs) << VC4_HDMI_CEC_CNT_TO_3600_US_SHIFT) |
			   ((3500 / usecs) << VC4_HDMI_CEC_CNT_TO_3500_US_SHIFT));

		अगर (!vc4_hdmi->variant->बाह्यal_irq_controller)
			HDMI_WRITE(HDMI_CEC_CPU_MASK_CLEAR, VC4_HDMI_CPU_CEC);
	पूर्ण अन्यथा अणु
		अगर (!vc4_hdmi->variant->बाह्यal_irq_controller)
			HDMI_WRITE(HDMI_CEC_CPU_MASK_SET, VC4_HDMI_CPU_CEC);
		HDMI_WRITE(HDMI_CEC_CNTRL_5, val |
			   VC4_HDMI_CEC_TX_SW_RESET | VC4_HDMI_CEC_RX_SW_RESET);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक vc4_hdmi_cec_adap_log_addr(काष्ठा cec_adapter *adap, u8 log_addr)
अणु
	काष्ठा vc4_hdmi *vc4_hdmi = cec_get_drvdata(adap);

	HDMI_WRITE(HDMI_CEC_CNTRL_1,
		   (HDMI_READ(HDMI_CEC_CNTRL_1) & ~VC4_HDMI_CEC_ADDR_MASK) |
		   (log_addr & 0xf) << VC4_HDMI_CEC_ADDR_SHIFT);
	वापस 0;
पूर्ण

अटल पूर्णांक vc4_hdmi_cec_adap_transmit(काष्ठा cec_adapter *adap, u8 attempts,
				      u32 संकेत_मुक्त_समय, काष्ठा cec_msg *msg)
अणु
	काष्ठा vc4_hdmi *vc4_hdmi = cec_get_drvdata(adap);
	काष्ठा drm_device *dev = vc4_hdmi->connector.dev;
	u32 val;
	अचिन्हित पूर्णांक i;

	अगर (msg->len > 16) अणु
		drm_err(dev, "Attempting to transmit too much data (%d)\n", msg->len);
		वापस -ENOMEM;
	पूर्ण

	क्रम (i = 0; i < msg->len; i += 4)
		HDMI_WRITE(HDMI_CEC_TX_DATA_1 + (i >> 2),
			   (msg->msg[i]) |
			   (msg->msg[i + 1] << 8) |
			   (msg->msg[i + 2] << 16) |
			   (msg->msg[i + 3] << 24));

	val = HDMI_READ(HDMI_CEC_CNTRL_1);
	val &= ~VC4_HDMI_CEC_START_XMIT_BEGIN;
	HDMI_WRITE(HDMI_CEC_CNTRL_1, val);
	val &= ~VC4_HDMI_CEC_MESSAGE_LENGTH_MASK;
	val |= (msg->len - 1) << VC4_HDMI_CEC_MESSAGE_LENGTH_SHIFT;
	val |= VC4_HDMI_CEC_START_XMIT_BEGIN;

	HDMI_WRITE(HDMI_CEC_CNTRL_1, val);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा cec_adap_ops vc4_hdmi_cec_adap_ops = अणु
	.adap_enable = vc4_hdmi_cec_adap_enable,
	.adap_log_addr = vc4_hdmi_cec_adap_log_addr,
	.adap_transmit = vc4_hdmi_cec_adap_transmit,
पूर्ण;

अटल पूर्णांक vc4_hdmi_cec_init(काष्ठा vc4_hdmi *vc4_hdmi)
अणु
	काष्ठा cec_connector_info conn_info;
	काष्ठा platक्रमm_device *pdev = vc4_hdmi->pdev;
	काष्ठा device *dev = &pdev->dev;
	u32 value;
	पूर्णांक ret;

	अगर (!of_find_property(dev->of_node, "interrupts", शून्य)) अणु
		dev_warn(dev, "'interrupts' DT property is missing, no CEC\n");
		वापस 0;
	पूर्ण

	vc4_hdmi->cec_adap = cec_allocate_adapter(&vc4_hdmi_cec_adap_ops,
						  vc4_hdmi, "vc4",
						  CEC_CAP_DEFAULTS |
						  CEC_CAP_CONNECTOR_INFO, 1);
	ret = PTR_ERR_OR_ZERO(vc4_hdmi->cec_adap);
	अगर (ret < 0)
		वापस ret;

	cec_fill_conn_info_from_drm(&conn_info, &vc4_hdmi->connector);
	cec_s_conn_info(vc4_hdmi->cec_adap, &conn_info);

	value = HDMI_READ(HDMI_CEC_CNTRL_1);
	/* Set the logical address to Unरेजिस्टरed */
	value |= VC4_HDMI_CEC_ADDR_MASK;
	HDMI_WRITE(HDMI_CEC_CNTRL_1, value);

	vc4_hdmi_cec_update_clk_भाग(vc4_hdmi);

	अगर (vc4_hdmi->variant->बाह्यal_irq_controller) अणु
		ret = devm_request_thपढ़ोed_irq(&pdev->dev,
						platक्रमm_get_irq_byname(pdev, "cec-rx"),
						vc4_cec_irq_handler_rx_bare,
						vc4_cec_irq_handler_rx_thपढ़ो, 0,
						"vc4 hdmi cec rx", vc4_hdmi);
		अगर (ret)
			जाओ err_delete_cec_adap;

		ret = devm_request_thपढ़ोed_irq(&pdev->dev,
						platक्रमm_get_irq_byname(pdev, "cec-tx"),
						vc4_cec_irq_handler_tx_bare,
						vc4_cec_irq_handler_tx_thपढ़ो, 0,
						"vc4 hdmi cec tx", vc4_hdmi);
		अगर (ret)
			जाओ err_delete_cec_adap;
	पूर्ण अन्यथा अणु
		HDMI_WRITE(HDMI_CEC_CPU_MASK_SET, 0xffffffff);

		ret = devm_request_thपढ़ोed_irq(&pdev->dev, platक्रमm_get_irq(pdev, 0),
						vc4_cec_irq_handler,
						vc4_cec_irq_handler_thपढ़ो, 0,
						"vc4 hdmi cec", vc4_hdmi);
		अगर (ret)
			जाओ err_delete_cec_adap;
	पूर्ण

	ret = cec_रेजिस्टर_adapter(vc4_hdmi->cec_adap, &pdev->dev);
	अगर (ret < 0)
		जाओ err_delete_cec_adap;

	वापस 0;

err_delete_cec_adap:
	cec_delete_adapter(vc4_hdmi->cec_adap);

	वापस ret;
पूर्ण

अटल व्योम vc4_hdmi_cec_निकास(काष्ठा vc4_hdmi *vc4_hdmi)
अणु
	cec_unरेजिस्टर_adapter(vc4_hdmi->cec_adap);
पूर्ण
#अन्यथा
अटल पूर्णांक vc4_hdmi_cec_init(काष्ठा vc4_hdmi *vc4_hdmi)
अणु
	वापस 0;
पूर्ण

अटल व्योम vc4_hdmi_cec_निकास(काष्ठा vc4_hdmi *vc4_hdmi) अणुपूर्ण;

#पूर्ण_अगर

अटल पूर्णांक vc4_hdmi_build_regset(काष्ठा vc4_hdmi *vc4_hdmi,
				 काष्ठा debugfs_regset32 *regset,
				 क्रमागत vc4_hdmi_regs reg)
अणु
	स्थिर काष्ठा vc4_hdmi_variant *variant = vc4_hdmi->variant;
	काष्ठा debugfs_reg32 *regs, *new_regs;
	अचिन्हित पूर्णांक count = 0;
	अचिन्हित पूर्णांक i;

	regs = kसुस्मृति(variant->num_रेजिस्टरs, माप(*regs),
		       GFP_KERNEL);
	अगर (!regs)
		वापस -ENOMEM;

	क्रम (i = 0; i < variant->num_रेजिस्टरs; i++) अणु
		स्थिर काष्ठा vc4_hdmi_रेजिस्टर *field =	&variant->रेजिस्टरs[i];

		अगर (field->reg != reg)
			जारी;

		regs[count].name = field->name;
		regs[count].offset = field->offset;
		count++;
	पूर्ण

	new_regs = kपुनः_स्मृति(regs, count * माप(*regs), GFP_KERNEL);
	अगर (!new_regs)
		वापस -ENOMEM;

	regset->base = __vc4_hdmi_get_field_base(vc4_hdmi, reg);
	regset->regs = new_regs;
	regset->nregs = count;

	वापस 0;
पूर्ण

अटल पूर्णांक vc4_hdmi_init_resources(काष्ठा vc4_hdmi *vc4_hdmi)
अणु
	काष्ठा platक्रमm_device *pdev = vc4_hdmi->pdev;
	काष्ठा device *dev = &pdev->dev;
	पूर्णांक ret;

	vc4_hdmi->hdmicore_regs = vc4_ioremap_regs(pdev, 0);
	अगर (IS_ERR(vc4_hdmi->hdmicore_regs))
		वापस PTR_ERR(vc4_hdmi->hdmicore_regs);

	vc4_hdmi->hd_regs = vc4_ioremap_regs(pdev, 1);
	अगर (IS_ERR(vc4_hdmi->hd_regs))
		वापस PTR_ERR(vc4_hdmi->hd_regs);

	ret = vc4_hdmi_build_regset(vc4_hdmi, &vc4_hdmi->hd_regset, VC4_HD);
	अगर (ret)
		वापस ret;

	ret = vc4_hdmi_build_regset(vc4_hdmi, &vc4_hdmi->hdmi_regset, VC4_HDMI);
	अगर (ret)
		वापस ret;

	vc4_hdmi->pixel_घड़ी = devm_clk_get(dev, "pixel");
	अगर (IS_ERR(vc4_hdmi->pixel_घड़ी)) अणु
		ret = PTR_ERR(vc4_hdmi->pixel_घड़ी);
		अगर (ret != -EPROBE_DEFER)
			DRM_ERROR("Failed to get pixel clock\n");
		वापस ret;
	पूर्ण

	vc4_hdmi->hsm_घड़ी = devm_clk_get(dev, "hdmi");
	अगर (IS_ERR(vc4_hdmi->hsm_घड़ी)) अणु
		DRM_ERROR("Failed to get HDMI state machine clock\n");
		वापस PTR_ERR(vc4_hdmi->hsm_घड़ी);
	पूर्ण
	vc4_hdmi->audio_घड़ी = vc4_hdmi->hsm_घड़ी;
	vc4_hdmi->cec_घड़ी = vc4_hdmi->hsm_घड़ी;

	वापस 0;
पूर्ण

अटल पूर्णांक vc5_hdmi_init_resources(काष्ठा vc4_hdmi *vc4_hdmi)
अणु
	काष्ठा platक्रमm_device *pdev = vc4_hdmi->pdev;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा resource *res;

	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "hdmi");
	अगर (!res)
		वापस -ENODEV;

	vc4_hdmi->hdmicore_regs = devm_ioremap(dev, res->start,
					       resource_size(res));
	अगर (!vc4_hdmi->hdmicore_regs)
		वापस -ENOMEM;

	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "hd");
	अगर (!res)
		वापस -ENODEV;

	vc4_hdmi->hd_regs = devm_ioremap(dev, res->start, resource_size(res));
	अगर (!vc4_hdmi->hd_regs)
		वापस -ENOMEM;

	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "cec");
	अगर (!res)
		वापस -ENODEV;

	vc4_hdmi->cec_regs = devm_ioremap(dev, res->start, resource_size(res));
	अगर (!vc4_hdmi->cec_regs)
		वापस -ENOMEM;

	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "csc");
	अगर (!res)
		वापस -ENODEV;

	vc4_hdmi->csc_regs = devm_ioremap(dev, res->start, resource_size(res));
	अगर (!vc4_hdmi->csc_regs)
		वापस -ENOMEM;

	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "dvp");
	अगर (!res)
		वापस -ENODEV;

	vc4_hdmi->dvp_regs = devm_ioremap(dev, res->start, resource_size(res));
	अगर (!vc4_hdmi->dvp_regs)
		वापस -ENOMEM;

	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "phy");
	अगर (!res)
		वापस -ENODEV;

	vc4_hdmi->phy_regs = devm_ioremap(dev, res->start, resource_size(res));
	अगर (!vc4_hdmi->phy_regs)
		वापस -ENOMEM;

	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "packet");
	अगर (!res)
		वापस -ENODEV;

	vc4_hdmi->ram_regs = devm_ioremap(dev, res->start, resource_size(res));
	अगर (!vc4_hdmi->ram_regs)
		वापस -ENOMEM;

	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "rm");
	अगर (!res)
		वापस -ENODEV;

	vc4_hdmi->rm_regs = devm_ioremap(dev, res->start, resource_size(res));
	अगर (!vc4_hdmi->rm_regs)
		वापस -ENOMEM;

	vc4_hdmi->hsm_घड़ी = devm_clk_get(dev, "hdmi");
	अगर (IS_ERR(vc4_hdmi->hsm_घड़ी)) अणु
		DRM_ERROR("Failed to get HDMI state machine clock\n");
		वापस PTR_ERR(vc4_hdmi->hsm_घड़ी);
	पूर्ण

	vc4_hdmi->pixel_bvb_घड़ी = devm_clk_get(dev, "bvb");
	अगर (IS_ERR(vc4_hdmi->pixel_bvb_घड़ी)) अणु
		DRM_ERROR("Failed to get pixel bvb clock\n");
		वापस PTR_ERR(vc4_hdmi->pixel_bvb_घड़ी);
	पूर्ण

	vc4_hdmi->audio_घड़ी = devm_clk_get(dev, "audio");
	अगर (IS_ERR(vc4_hdmi->audio_घड़ी)) अणु
		DRM_ERROR("Failed to get audio clock\n");
		वापस PTR_ERR(vc4_hdmi->audio_घड़ी);
	पूर्ण

	vc4_hdmi->cec_घड़ी = devm_clk_get(dev, "cec");
	अगर (IS_ERR(vc4_hdmi->cec_घड़ी)) अणु
		DRM_ERROR("Failed to get CEC clock\n");
		वापस PTR_ERR(vc4_hdmi->cec_घड़ी);
	पूर्ण

	vc4_hdmi->reset = devm_reset_control_get(dev, शून्य);
	अगर (IS_ERR(vc4_hdmi->reset)) अणु
		DRM_ERROR("Failed to get HDMI reset line\n");
		वापस PTR_ERR(vc4_hdmi->reset);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vc4_hdmi_bind(काष्ठा device *dev, काष्ठा device *master, व्योम *data)
अणु
	स्थिर काष्ठा vc4_hdmi_variant *variant = of_device_get_match_data(dev);
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा drm_device *drm = dev_get_drvdata(master);
	काष्ठा vc4_hdmi *vc4_hdmi;
	काष्ठा drm_encoder *encoder;
	काष्ठा device_node *ddc_node;
	u32 value;
	पूर्णांक ret;

	vc4_hdmi = devm_kzalloc(dev, माप(*vc4_hdmi), GFP_KERNEL);
	अगर (!vc4_hdmi)
		वापस -ENOMEM;

	dev_set_drvdata(dev, vc4_hdmi);
	encoder = &vc4_hdmi->encoder.base.base;
	vc4_hdmi->encoder.base.type = variant->encoder_type;
	vc4_hdmi->encoder.base.pre_crtc_configure = vc4_hdmi_encoder_pre_crtc_configure;
	vc4_hdmi->encoder.base.pre_crtc_enable = vc4_hdmi_encoder_pre_crtc_enable;
	vc4_hdmi->encoder.base.post_crtc_enable = vc4_hdmi_encoder_post_crtc_enable;
	vc4_hdmi->encoder.base.post_crtc_disable = vc4_hdmi_encoder_post_crtc_disable;
	vc4_hdmi->encoder.base.post_crtc_घातerकरोwn = vc4_hdmi_encoder_post_crtc_घातerकरोwn;
	vc4_hdmi->pdev = pdev;
	vc4_hdmi->variant = variant;

	ret = variant->init_resources(vc4_hdmi);
	अगर (ret)
		वापस ret;

	ddc_node = of_parse_phandle(dev->of_node, "ddc", 0);
	अगर (!ddc_node) अणु
		DRM_ERROR("Failed to find ddc node in device tree\n");
		वापस -ENODEV;
	पूर्ण

	vc4_hdmi->ddc = of_find_i2c_adapter_by_node(ddc_node);
	of_node_put(ddc_node);
	अगर (!vc4_hdmi->ddc) अणु
		DRM_DEBUG("Failed to get ddc i2c adapter by node\n");
		वापस -EPROBE_DEFER;
	पूर्ण

	/* Only use the GPIO HPD pin अगर present in the DT, otherwise
	 * we'll use the HDMI core's रेजिस्टर.
	 */
	अगर (of_find_property(dev->of_node, "hpd-gpios", &value)) अणु
		क्रमागत of_gpio_flags hpd_gpio_flags;

		vc4_hdmi->hpd_gpio = of_get_named_gpio_flags(dev->of_node,
							     "hpd-gpios", 0,
							     &hpd_gpio_flags);
		अगर (vc4_hdmi->hpd_gpio < 0) अणु
			ret = vc4_hdmi->hpd_gpio;
			जाओ err_unprepare_hsm;
		पूर्ण

		vc4_hdmi->hpd_active_low = hpd_gpio_flags & OF_GPIO_ACTIVE_LOW;
	पूर्ण

	vc4_hdmi->disable_wअगरi_frequencies =
		of_property_पढ़ो_bool(dev->of_node, "wifi-2.4ghz-coexistence");

	अगर (vc4_hdmi->variant->reset)
		vc4_hdmi->variant->reset(vc4_hdmi);

	pm_runसमय_enable(dev);

	drm_simple_encoder_init(drm, encoder, DRM_MODE_ENCODER_TMDS);
	drm_encoder_helper_add(encoder, &vc4_hdmi_encoder_helper_funcs);

	ret = vc4_hdmi_connector_init(drm, vc4_hdmi);
	अगर (ret)
		जाओ err_destroy_encoder;

	ret = vc4_hdmi_cec_init(vc4_hdmi);
	अगर (ret)
		जाओ err_destroy_conn;

	ret = vc4_hdmi_audio_init(vc4_hdmi);
	अगर (ret)
		जाओ err_मुक्त_cec;

	vc4_debugfs_add_file(drm, variant->debugfs_name,
			     vc4_hdmi_debugfs_regs,
			     vc4_hdmi);

	वापस 0;

err_मुक्त_cec:
	vc4_hdmi_cec_निकास(vc4_hdmi);
err_destroy_conn:
	vc4_hdmi_connector_destroy(&vc4_hdmi->connector);
err_destroy_encoder:
	drm_encoder_cleanup(encoder);
err_unprepare_hsm:
	pm_runसमय_disable(dev);
	put_device(&vc4_hdmi->ddc->dev);

	वापस ret;
पूर्ण

अटल व्योम vc4_hdmi_unbind(काष्ठा device *dev, काष्ठा device *master,
			    व्योम *data)
अणु
	काष्ठा vc4_hdmi *vc4_hdmi;

	/*
	 * ASoC makes it a bit hard to retrieve a poपूर्णांकer to the
	 * vc4_hdmi काष्ठाure. Registering the card will overग_लिखो our
	 * device drvdata with a poपूर्णांकer to the snd_soc_card काष्ठाure,
	 * which can then be used to retrieve whatever drvdata we want
	 * to associate.
	 *
	 * However, that करोesn't fly in the case where we wouldn't
	 * रेजिस्टर an ASoC card (because of an old DT that is missing
	 * the dmas properties क्रम example), then the card isn't
	 * रेजिस्टरed and the device drvdata wouldn't be set.
	 *
	 * We can deal with both हालs by making sure a snd_soc_card
	 * poपूर्णांकer and a vc4_hdmi काष्ठाure are poपूर्णांकing to the same
	 * memory address, so we can treat them indistinctly without any
	 * issue.
	 */
	BUILD_BUG_ON(दुरत्व(काष्ठा vc4_hdmi_audio, card) != 0);
	BUILD_BUG_ON(दुरत्व(काष्ठा vc4_hdmi, audio) != 0);
	vc4_hdmi = dev_get_drvdata(dev);

	kमुक्त(vc4_hdmi->hdmi_regset.regs);
	kमुक्त(vc4_hdmi->hd_regset.regs);

	vc4_hdmi_cec_निकास(vc4_hdmi);
	vc4_hdmi_connector_destroy(&vc4_hdmi->connector);
	drm_encoder_cleanup(&vc4_hdmi->encoder.base.base);

	pm_runसमय_disable(dev);

	put_device(&vc4_hdmi->ddc->dev);
पूर्ण

अटल स्थिर काष्ठा component_ops vc4_hdmi_ops = अणु
	.bind   = vc4_hdmi_bind,
	.unbind = vc4_hdmi_unbind,
पूर्ण;

अटल पूर्णांक vc4_hdmi_dev_probe(काष्ठा platक्रमm_device *pdev)
अणु
	वापस component_add(&pdev->dev, &vc4_hdmi_ops);
पूर्ण

अटल पूर्णांक vc4_hdmi_dev_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	component_del(&pdev->dev, &vc4_hdmi_ops);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा vc4_hdmi_variant bcm2835_variant = अणु
	.encoder_type		= VC4_ENCODER_TYPE_HDMI0,
	.debugfs_name		= "hdmi_regs",
	.card_name		= "vc4-hdmi",
	.max_pixel_घड़ी	= 162000000,
	.रेजिस्टरs		= vc4_hdmi_fields,
	.num_रेजिस्टरs		= ARRAY_SIZE(vc4_hdmi_fields),

	.init_resources		= vc4_hdmi_init_resources,
	.csc_setup		= vc4_hdmi_csc_setup,
	.reset			= vc4_hdmi_reset,
	.set_timings		= vc4_hdmi_set_timings,
	.phy_init		= vc4_hdmi_phy_init,
	.phy_disable		= vc4_hdmi_phy_disable,
	.phy_rng_enable		= vc4_hdmi_phy_rng_enable,
	.phy_rng_disable	= vc4_hdmi_phy_rng_disable,
	.channel_map		= vc4_hdmi_channel_map,
पूर्ण;

अटल स्थिर काष्ठा vc4_hdmi_variant bcm2711_hdmi0_variant = अणु
	.encoder_type		= VC4_ENCODER_TYPE_HDMI0,
	.debugfs_name		= "hdmi0_regs",
	.card_name		= "vc4-hdmi-0",
	.max_pixel_घड़ी	= HDMI_14_MAX_TMDS_CLK,
	.रेजिस्टरs		= vc5_hdmi_hdmi0_fields,
	.num_रेजिस्टरs		= ARRAY_SIZE(vc5_hdmi_hdmi0_fields),
	.phy_lane_mapping	= अणु
		PHY_LANE_0,
		PHY_LANE_1,
		PHY_LANE_2,
		PHY_LANE_CK,
	पूर्ण,
	.unsupported_odd_h_timings	= true,
	.बाह्यal_irq_controller	= true,

	.init_resources		= vc5_hdmi_init_resources,
	.csc_setup		= vc5_hdmi_csc_setup,
	.reset			= vc5_hdmi_reset,
	.set_timings		= vc5_hdmi_set_timings,
	.phy_init		= vc5_hdmi_phy_init,
	.phy_disable		= vc5_hdmi_phy_disable,
	.phy_rng_enable		= vc5_hdmi_phy_rng_enable,
	.phy_rng_disable	= vc5_hdmi_phy_rng_disable,
	.channel_map		= vc5_hdmi_channel_map,
पूर्ण;

अटल स्थिर काष्ठा vc4_hdmi_variant bcm2711_hdmi1_variant = अणु
	.encoder_type		= VC4_ENCODER_TYPE_HDMI1,
	.debugfs_name		= "hdmi1_regs",
	.card_name		= "vc4-hdmi-1",
	.max_pixel_घड़ी	= HDMI_14_MAX_TMDS_CLK,
	.रेजिस्टरs		= vc5_hdmi_hdmi1_fields,
	.num_रेजिस्टरs		= ARRAY_SIZE(vc5_hdmi_hdmi1_fields),
	.phy_lane_mapping	= अणु
		PHY_LANE_1,
		PHY_LANE_0,
		PHY_LANE_CK,
		PHY_LANE_2,
	पूर्ण,
	.unsupported_odd_h_timings	= true,
	.बाह्यal_irq_controller	= true,

	.init_resources		= vc5_hdmi_init_resources,
	.csc_setup		= vc5_hdmi_csc_setup,
	.reset			= vc5_hdmi_reset,
	.set_timings		= vc5_hdmi_set_timings,
	.phy_init		= vc5_hdmi_phy_init,
	.phy_disable		= vc5_hdmi_phy_disable,
	.phy_rng_enable		= vc5_hdmi_phy_rng_enable,
	.phy_rng_disable	= vc5_hdmi_phy_rng_disable,
	.channel_map		= vc5_hdmi_channel_map,
पूर्ण;

अटल स्थिर काष्ठा of_device_id vc4_hdmi_dt_match[] = अणु
	अणु .compatible = "brcm,bcm2835-hdmi", .data = &bcm2835_variant पूर्ण,
	अणु .compatible = "brcm,bcm2711-hdmi0", .data = &bcm2711_hdmi0_variant पूर्ण,
	अणु .compatible = "brcm,bcm2711-hdmi1", .data = &bcm2711_hdmi1_variant पूर्ण,
	अणुपूर्ण
पूर्ण;

काष्ठा platक्रमm_driver vc4_hdmi_driver = अणु
	.probe = vc4_hdmi_dev_probe,
	.हटाओ = vc4_hdmi_dev_हटाओ,
	.driver = अणु
		.name = "vc4_hdmi",
		.of_match_table = vc4_hdmi_dt_match,
	पूर्ण,
पूर्ण;
