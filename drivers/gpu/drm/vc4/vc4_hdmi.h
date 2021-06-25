<शैली गुरु>
#अगर_अघोषित _VC4_HDMI_H_
#घोषणा _VC4_HDMI_H_

#समावेश <drm/drm_connector.h>
#समावेश <media/cec.h>
#समावेश <sound/dmaengine_pcm.h>
#समावेश <sound/soc.h>

#समावेश "vc4_drv.h"

/* VC4 HDMI encoder KMS काष्ठा */
काष्ठा vc4_hdmi_encoder अणु
	काष्ठा vc4_encoder base;
	bool hdmi_monitor;
	bool limited_rgb_range;
पूर्ण;

अटल अंतरभूत काष्ठा vc4_hdmi_encoder *
to_vc4_hdmi_encoder(काष्ठा drm_encoder *encoder)
अणु
	वापस container_of(encoder, काष्ठा vc4_hdmi_encoder, base.base);
पूर्ण

काष्ठा vc4_hdmi;
काष्ठा vc4_hdmi_रेजिस्टर;
काष्ठा vc4_hdmi_connector_state;

क्रमागत vc4_hdmi_phy_channel अणु
	PHY_LANE_0 = 0,
	PHY_LANE_1,
	PHY_LANE_2,
	PHY_LANE_CK,
पूर्ण;

काष्ठा vc4_hdmi_variant अणु
	/* Encoder Type क्रम that controller */
	क्रमागत vc4_encoder_type encoder_type;

	/* ALSA card name */
	स्थिर अक्षर *card_name;

	/* Filename to expose the रेजिस्टरs in debugfs */
	स्थिर अक्षर *debugfs_name;

	/* Maximum pixel घड़ी supported by the controller (in Hz) */
	अचिन्हित दीर्घ दीर्घ max_pixel_घड़ी;

	/* List of the रेजिस्टरs available on that variant */
	स्थिर काष्ठा vc4_hdmi_रेजिस्टर *रेजिस्टरs;

	/* Number of रेजिस्टरs on that variant */
	अचिन्हित पूर्णांक num_रेजिस्टरs;

	/* BCM2711 Only.
	 * The variants करोn't map the lane in the same order in the
	 * PHY, so this is an array mapping the HDMI channel (index)
	 * to the PHY lane (value).
	 */
	क्रमागत vc4_hdmi_phy_channel phy_lane_mapping[4];

	/* The BCM2711 cannot deal with odd horizontal pixel timings */
	bool unsupported_odd_h_timings;

	/*
	 * The BCM2711 CEC/hotplug IRQ controller is shared between the
	 * two HDMI controllers, and we have a proper irqchip driver क्रम
	 * it.
	 */
	bool बाह्यal_irq_controller;

	/* Callback to get the resources (memory region, पूर्णांकerrupts,
	 * घड़ीs, etc) क्रम that variant.
	 */
	पूर्णांक (*init_resources)(काष्ठा vc4_hdmi *vc4_hdmi);

	/* Callback to reset the HDMI block */
	व्योम (*reset)(काष्ठा vc4_hdmi *vc4_hdmi);

	/* Callback to enable / disable the CSC */
	व्योम (*csc_setup)(काष्ठा vc4_hdmi *vc4_hdmi, bool enable);

	/* Callback to configure the video timings in the HDMI block */
	व्योम (*set_timings)(काष्ठा vc4_hdmi *vc4_hdmi,
			    काष्ठा drm_connector_state *state,
			    काष्ठा drm_display_mode *mode);

	/* Callback to initialize the PHY according to the connector state */
	व्योम (*phy_init)(काष्ठा vc4_hdmi *vc4_hdmi,
			 काष्ठा vc4_hdmi_connector_state *vc4_conn_state);

	/* Callback to disable the PHY */
	व्योम (*phy_disable)(काष्ठा vc4_hdmi *vc4_hdmi);

	/* Callback to enable the RNG in the PHY */
	व्योम (*phy_rng_enable)(काष्ठा vc4_hdmi *vc4_hdmi);

	/* Callback to disable the RNG in the PHY */
	व्योम (*phy_rng_disable)(काष्ठा vc4_hdmi *vc4_hdmi);

	/* Callback to get channel map */
	u32 (*channel_map)(काष्ठा vc4_hdmi *vc4_hdmi, u32 channel_mask);
पूर्ण;

/* HDMI audio inक्रमmation */
काष्ठा vc4_hdmi_audio अणु
	काष्ठा snd_soc_card card;
	काष्ठा snd_soc_dai_link link;
	काष्ठा snd_soc_dai_link_component cpu;
	काष्ठा snd_soc_dai_link_component codec;
	काष्ठा snd_soc_dai_link_component platक्रमm;
	पूर्णांक samplerate;
	पूर्णांक channels;
	काष्ठा snd_dmaengine_dai_dma_data dma_data;
	काष्ठा snd_pcm_substream *substream;

	bool streaming;
पूर्ण;

/* General HDMI hardware state. */
काष्ठा vc4_hdmi अणु
	काष्ठा vc4_hdmi_audio audio;

	काष्ठा platक्रमm_device *pdev;
	स्थिर काष्ठा vc4_hdmi_variant *variant;

	काष्ठा vc4_hdmi_encoder encoder;
	काष्ठा drm_connector connector;

	काष्ठा i2c_adapter *ddc;
	व्योम __iomem *hdmicore_regs;
	व्योम __iomem *hd_regs;

	/* VC5 Only */
	व्योम __iomem *cec_regs;
	/* VC5 Only */
	व्योम __iomem *csc_regs;
	/* VC5 Only */
	व्योम __iomem *dvp_regs;
	/* VC5 Only */
	व्योम __iomem *phy_regs;
	/* VC5 Only */
	व्योम __iomem *ram_regs;
	/* VC5 Only */
	व्योम __iomem *rm_regs;

	पूर्णांक hpd_gpio;
	bool hpd_active_low;

	/*
	 * On some प्रणालीs (like the RPi4), some modes are in the same
	 * frequency range than the WiFi channels (1440p@60Hz क्रम
	 * example). Should we take evasive actions because that प्रणाली
	 * has a wअगरi adapter?
	 */
	bool disable_wअगरi_frequencies;

	काष्ठा cec_adapter *cec_adap;
	काष्ठा cec_msg cec_rx_msg;
	bool cec_tx_ok;
	bool cec_irq_was_rx;

	काष्ठा clk *cec_घड़ी;
	काष्ठा clk *pixel_घड़ी;
	काष्ठा clk *hsm_घड़ी;
	काष्ठा clk *audio_घड़ी;
	काष्ठा clk *pixel_bvb_घड़ी;

	काष्ठा reset_control *reset;

	काष्ठा debugfs_regset32 hdmi_regset;
	काष्ठा debugfs_regset32 hd_regset;
पूर्ण;

अटल अंतरभूत काष्ठा vc4_hdmi *
connector_to_vc4_hdmi(काष्ठा drm_connector *connector)
अणु
	वापस container_of(connector, काष्ठा vc4_hdmi, connector);
पूर्ण

अटल अंतरभूत काष्ठा vc4_hdmi *
encoder_to_vc4_hdmi(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा vc4_hdmi_encoder *_encoder = to_vc4_hdmi_encoder(encoder);

	वापस container_of(_encoder, काष्ठा vc4_hdmi, encoder);
पूर्ण

काष्ठा vc4_hdmi_connector_state अणु
	काष्ठा drm_connector_state	base;
	अचिन्हित दीर्घ दीर्घ		pixel_rate;
पूर्ण;

अटल अंतरभूत काष्ठा vc4_hdmi_connector_state *
conn_state_to_vc4_hdmi_conn_state(काष्ठा drm_connector_state *conn_state)
अणु
	वापस container_of(conn_state, काष्ठा vc4_hdmi_connector_state, base);
पूर्ण

व्योम vc4_hdmi_phy_init(काष्ठा vc4_hdmi *vc4_hdmi,
		       काष्ठा vc4_hdmi_connector_state *vc4_conn_state);
व्योम vc4_hdmi_phy_disable(काष्ठा vc4_hdmi *vc4_hdmi);
व्योम vc4_hdmi_phy_rng_enable(काष्ठा vc4_hdmi *vc4_hdmi);
व्योम vc4_hdmi_phy_rng_disable(काष्ठा vc4_hdmi *vc4_hdmi);

व्योम vc5_hdmi_phy_init(काष्ठा vc4_hdmi *vc4_hdmi,
		       काष्ठा vc4_hdmi_connector_state *vc4_conn_state);
व्योम vc5_hdmi_phy_disable(काष्ठा vc4_hdmi *vc4_hdmi);
व्योम vc5_hdmi_phy_rng_enable(काष्ठा vc4_hdmi *vc4_hdmi);
व्योम vc5_hdmi_phy_rng_disable(काष्ठा vc4_hdmi *vc4_hdmi);

#पूर्ण_अगर /* _VC4_HDMI_H_ */
