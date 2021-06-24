<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) STMicroelectronics SA 2014
 * Author: Vincent Abriou <vincent.abriou@st.com> क्रम STMicroelectronics.
 */

#अगर_अघोषित _STI_HDMI_H_
#घोषणा _STI_HDMI_H_

#समावेश <linux/hdmi.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <media/cec-notअगरier.h>

#समावेश <drm/drm_modes.h>
#समावेश <drm/drm_property.h>

#घोषणा HDMI_STA           0x0010
#घोषणा HDMI_STA_DLL_LCK   BIT(5)
#घोषणा HDMI_STA_HOT_PLUG  BIT(4)

काष्ठा sti_hdmi;

काष्ठा hdmi_phy_ops अणु
	bool (*start)(काष्ठा sti_hdmi *hdmi);
	व्योम (*stop)(काष्ठा sti_hdmi *hdmi);
पूर्ण;

काष्ठा hdmi_audio_params अणु
	bool enabled;
	अचिन्हित पूर्णांक sample_width;
	अचिन्हित पूर्णांक sample_rate;
	काष्ठा hdmi_audio_infoframe cea;
पूर्ण;

#घोषणा DEFAULT_COLORSPACE_MODE HDMI_COLORSPACE_RGB

/**
 * STI hdmi काष्ठाure
 *
 * @dev: driver device
 * @drm_dev: poपूर्णांकer to drm device
 * @mode: current display mode selected
 * @regs: hdmi रेजिस्टर
 * @syscfg: syscfg रेजिस्टर क्रम pll rejection configuration
 * @clk_pix: hdmi pixel घड़ी
 * @clk_पंचांगds: hdmi पंचांगds घड़ी
 * @clk_phy: hdmi phy घड़ी
 * @clk_audio: hdmi audio घड़ी
 * @irq: hdmi पूर्णांकerrupt number
 * @irq_status: पूर्णांकerrupt status रेजिस्टर
 * @phy_ops: phy start/stop operations
 * @enabled: true अगर hdmi is enabled अन्यथा false
 * @hpd: hot plug detect status
 * @रुको_event: रुको event
 * @event_received: रुको event status
 * @reset: reset control of the hdmi phy
 * @ddc_adapt: i2c ddc adapter
 * @colorspace: current colorspace selected
 * @hdmi_monitor: true अगर HDMI monitor detected अन्यथा DVI monitor assumed
 * @audio_pdev: ASoC hdmi-codec platक्रमm device
 * @audio: hdmi audio parameters.
 * @drm_connector: hdmi connector
 * @notअगरier: hotplug detect notअगरier
 */
काष्ठा sti_hdmi अणु
	काष्ठा device dev;
	काष्ठा drm_device *drm_dev;
	काष्ठा drm_display_mode mode;
	व्योम __iomem *regs;
	व्योम __iomem *syscfg;
	काष्ठा clk *clk_pix;
	काष्ठा clk *clk_पंचांगds;
	काष्ठा clk *clk_phy;
	काष्ठा clk *clk_audio;
	पूर्णांक irq;
	u32 irq_status;
	काष्ठा hdmi_phy_ops *phy_ops;
	bool enabled;
	bool hpd;
	रुको_queue_head_t रुको_event;
	bool event_received;
	काष्ठा reset_control *reset;
	काष्ठा i2c_adapter *ddc_adapt;
	क्रमागत hdmi_colorspace colorspace;
	bool hdmi_monitor;
	काष्ठा platक्रमm_device *audio_pdev;
	काष्ठा hdmi_audio_params audio;
	काष्ठा drm_connector *drm_connector;
	काष्ठा cec_notअगरier *notअगरier;
पूर्ण;

u32 hdmi_पढ़ो(काष्ठा sti_hdmi *hdmi, पूर्णांक offset);
व्योम hdmi_ग_लिखो(काष्ठा sti_hdmi *hdmi, u32 val, पूर्णांक offset);

/**
 * hdmi phy config काष्ठाure
 *
 * A poपूर्णांकer to an array of these काष्ठाures is passed to a TMDS (HDMI) output
 * via the control पूर्णांकerface to provide board and SoC specअगरic
 * configurations of the HDMI PHY. Each entry in the array specअगरies a hardware
 * specअगरic configuration क्रम a given TMDS घड़ी frequency range.
 *
 * @min_पंचांगds_freq: Lower bound of TMDS घड़ी frequency this entry applies to
 * @max_पंचांगds_freq: Upper bound of TMDS घड़ी frequency this entry applies to
 * @config: SoC specअगरic रेजिस्टर configuration
 */
काष्ठा hdmi_phy_config अणु
	u32 min_पंचांगds_freq;
	u32 max_पंचांगds_freq;
	u32 config[4];
पूर्ण;

#पूर्ण_अगर
