<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2013 Red Hat
 * Author: Rob Clark <robdclark@gmail.com>
 */

#अगर_अघोषित __HDMI_CONNECTOR_H__
#घोषणा __HDMI_CONNECTOR_H__

#समावेश <linux/i2c.h>
#समावेश <linux/clk.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/hdmi.h>

#समावेश <drm/drm_bridge.h>

#समावेश "msm_drv.h"
#समावेश "hdmi.xml.h"

#घोषणा HDMI_MAX_NUM_GPIO	6

काष्ठा hdmi_phy;
काष्ठा hdmi_platक्रमm_config;

काष्ठा hdmi_gpio_data अणु
	काष्ठा gpio_desc *gpiod;
	bool output;
	पूर्णांक value;
पूर्ण;

काष्ठा hdmi_audio अणु
	bool enabled;
	काष्ठा hdmi_audio_infoframe infoframe;
	पूर्णांक rate;
पूर्ण;

काष्ठा hdmi_hdcp_ctrl;

काष्ठा hdmi अणु
	काष्ठा drm_device *dev;
	काष्ठा platक्रमm_device *pdev;
	काष्ठा platक्रमm_device *audio_pdev;

	स्थिर काष्ठा hdmi_platक्रमm_config *config;

	/* audio state: */
	काष्ठा hdmi_audio audio;

	/* video state: */
	bool घातer_on;
	अचिन्हित दीर्घ पूर्णांक pixघड़ी;

	व्योम __iomem *mmio;
	व्योम __iomem *qfprom_mmio;
	phys_addr_t mmio_phy_addr;

	काष्ठा regulator **hpd_regs;
	काष्ठा regulator **pwr_regs;
	काष्ठा clk **hpd_clks;
	काष्ठा clk **pwr_clks;

	काष्ठा hdmi_phy *phy;
	काष्ठा device *phy_dev;

	काष्ठा i2c_adapter *i2c;
	काष्ठा drm_connector *connector;
	काष्ठा drm_bridge *bridge;

	/* the encoder we are hooked to (outside of hdmi block) */
	काष्ठा drm_encoder *encoder;

	bool hdmi_mode;               /* are we in hdmi mode? */

	पूर्णांक irq;
	काष्ठा workqueue_काष्ठा *workq;

	काष्ठा hdmi_hdcp_ctrl *hdcp_ctrl;

	/*
	* spinlock to protect रेजिस्टरs shared by dअगरferent execution
	* REG_HDMI_CTRL
	* REG_HDMI_DDC_ARBITRATION
	* REG_HDMI_HDCP_INT_CTRL
	* REG_HDMI_HPD_CTRL
	*/
	spinlock_t reg_lock;
पूर्ण;

/* platक्रमm config data (ie. from DT, or pdata) */
काष्ठा hdmi_platक्रमm_config अणु
	स्थिर अक्षर *mmio_name;
	स्थिर अक्षर *qfprom_mmio_name;

	/* regulators that need to be on क्रम hpd: */
	स्थिर अक्षर **hpd_reg_names;
	पूर्णांक hpd_reg_cnt;

	/* regulators that need to be on क्रम screen pwr: */
	स्थिर अक्षर **pwr_reg_names;
	पूर्णांक pwr_reg_cnt;

	/* clks that need to be on क्रम hpd: */
	स्थिर अक्षर **hpd_clk_names;
	स्थिर दीर्घ अचिन्हित *hpd_freq;
	पूर्णांक hpd_clk_cnt;

	/* clks that need to be on क्रम screen pwr (ie pixel clk): */
	स्थिर अक्षर **pwr_clk_names;
	पूर्णांक pwr_clk_cnt;

	/* gpio's: */
	काष्ठा hdmi_gpio_data gpios[HDMI_MAX_NUM_GPIO];
पूर्ण;

व्योम msm_hdmi_set_mode(काष्ठा hdmi *hdmi, bool घातer_on);

अटल अंतरभूत व्योम hdmi_ग_लिखो(काष्ठा hdmi *hdmi, u32 reg, u32 data)
अणु
	msm_ग_लिखोl(data, hdmi->mmio + reg);
पूर्ण

अटल अंतरभूत u32 hdmi_पढ़ो(काष्ठा hdmi *hdmi, u32 reg)
अणु
	वापस msm_पढ़ोl(hdmi->mmio + reg);
पूर्ण

अटल अंतरभूत u32 hdmi_qfprom_पढ़ो(काष्ठा hdmi *hdmi, u32 reg)
अणु
	वापस msm_पढ़ोl(hdmi->qfprom_mmio + reg);
पूर्ण

/*
 * hdmi phy:
 */

क्रमागत hdmi_phy_type अणु
	MSM_HDMI_PHY_8x60,
	MSM_HDMI_PHY_8960,
	MSM_HDMI_PHY_8x74,
	MSM_HDMI_PHY_8996,
	MSM_HDMI_PHY_MAX,
पूर्ण;

काष्ठा hdmi_phy_cfg अणु
	क्रमागत hdmi_phy_type type;
	व्योम (*घातerup)(काष्ठा hdmi_phy *phy, अचिन्हित दीर्घ पूर्णांक pixघड़ी);
	व्योम (*घातerकरोwn)(काष्ठा hdmi_phy *phy);
	स्थिर अक्षर * स्थिर *reg_names;
	पूर्णांक num_regs;
	स्थिर अक्षर * स्थिर *clk_names;
	पूर्णांक num_clks;
पूर्ण;

बाह्य स्थिर काष्ठा hdmi_phy_cfg msm_hdmi_phy_8x60_cfg;
बाह्य स्थिर काष्ठा hdmi_phy_cfg msm_hdmi_phy_8960_cfg;
बाह्य स्थिर काष्ठा hdmi_phy_cfg msm_hdmi_phy_8x74_cfg;
बाह्य स्थिर काष्ठा hdmi_phy_cfg msm_hdmi_phy_8996_cfg;

काष्ठा hdmi_phy अणु
	काष्ठा platक्रमm_device *pdev;
	व्योम __iomem *mmio;
	काष्ठा hdmi_phy_cfg *cfg;
	स्थिर काष्ठा hdmi_phy_funcs *funcs;
	काष्ठा regulator **regs;
	काष्ठा clk **clks;
पूर्ण;

अटल अंतरभूत व्योम hdmi_phy_ग_लिखो(काष्ठा hdmi_phy *phy, u32 reg, u32 data)
अणु
	msm_ग_लिखोl(data, phy->mmio + reg);
पूर्ण

अटल अंतरभूत u32 hdmi_phy_पढ़ो(काष्ठा hdmi_phy *phy, u32 reg)
अणु
	वापस msm_पढ़ोl(phy->mmio + reg);
पूर्ण

पूर्णांक msm_hdmi_phy_resource_enable(काष्ठा hdmi_phy *phy);
व्योम msm_hdmi_phy_resource_disable(काष्ठा hdmi_phy *phy);
व्योम msm_hdmi_phy_घातerup(काष्ठा hdmi_phy *phy, अचिन्हित दीर्घ पूर्णांक pixघड़ी);
व्योम msm_hdmi_phy_घातerकरोwn(काष्ठा hdmi_phy *phy);
व्योम __init msm_hdmi_phy_driver_रेजिस्टर(व्योम);
व्योम __निकास msm_hdmi_phy_driver_unरेजिस्टर(व्योम);

#अगर_घोषित CONFIG_COMMON_CLK
पूर्णांक msm_hdmi_pll_8960_init(काष्ठा platक्रमm_device *pdev);
पूर्णांक msm_hdmi_pll_8996_init(काष्ठा platक्रमm_device *pdev);
#अन्यथा
अटल अंतरभूत पूर्णांक msm_hdmi_pll_8960_init(काष्ठा platक्रमm_device *pdev)
अणु
	वापस -ENODEV;
पूर्ण

अटल अंतरभूत पूर्णांक msm_hdmi_pll_8996_init(काष्ठा platक्रमm_device *pdev)
अणु
	वापस -ENODEV;
पूर्ण
#पूर्ण_अगर

/*
 * audio:
 */
/* Supported HDMI Audio channels and rates */
#घोषणा	MSM_HDMI_AUDIO_CHANNEL_2	0
#घोषणा	MSM_HDMI_AUDIO_CHANNEL_4	1
#घोषणा	MSM_HDMI_AUDIO_CHANNEL_6	2
#घोषणा	MSM_HDMI_AUDIO_CHANNEL_8	3

#घोषणा	HDMI_SAMPLE_RATE_32KHZ		0
#घोषणा	HDMI_SAMPLE_RATE_44_1KHZ	1
#घोषणा	HDMI_SAMPLE_RATE_48KHZ		2
#घोषणा	HDMI_SAMPLE_RATE_88_2KHZ	3
#घोषणा	HDMI_SAMPLE_RATE_96KHZ		4
#घोषणा	HDMI_SAMPLE_RATE_176_4KHZ	5
#घोषणा	HDMI_SAMPLE_RATE_192KHZ		6

पूर्णांक msm_hdmi_audio_update(काष्ठा hdmi *hdmi);
पूर्णांक msm_hdmi_audio_info_setup(काष्ठा hdmi *hdmi, bool enabled,
	uपूर्णांक32_t num_of_channels, uपूर्णांक32_t channel_allocation,
	uपूर्णांक32_t level_shअगरt, bool करोwn_mix);
व्योम msm_hdmi_audio_set_sample_rate(काष्ठा hdmi *hdmi, पूर्णांक rate);


/*
 * hdmi bridge:
 */

काष्ठा drm_bridge *msm_hdmi_bridge_init(काष्ठा hdmi *hdmi);
व्योम msm_hdmi_bridge_destroy(काष्ठा drm_bridge *bridge);

/*
 * hdmi connector:
 */

व्योम msm_hdmi_connector_irq(काष्ठा drm_connector *connector);
काष्ठा drm_connector *msm_hdmi_connector_init(काष्ठा hdmi *hdmi);
पूर्णांक msm_hdmi_hpd_enable(काष्ठा drm_connector *connector);

/*
 * i2c adapter क्रम ddc:
 */

व्योम msm_hdmi_i2c_irq(काष्ठा i2c_adapter *i2c);
व्योम msm_hdmi_i2c_destroy(काष्ठा i2c_adapter *i2c);
काष्ठा i2c_adapter *msm_hdmi_i2c_init(काष्ठा hdmi *hdmi);

/*
 * hdcp
 */
#अगर_घोषित CONFIG_DRM_MSM_HDMI_HDCP
काष्ठा hdmi_hdcp_ctrl *msm_hdmi_hdcp_init(काष्ठा hdmi *hdmi);
व्योम msm_hdmi_hdcp_destroy(काष्ठा hdmi *hdmi);
व्योम msm_hdmi_hdcp_on(काष्ठा hdmi_hdcp_ctrl *hdcp_ctrl);
व्योम msm_hdmi_hdcp_off(काष्ठा hdmi_hdcp_ctrl *hdcp_ctrl);
व्योम msm_hdmi_hdcp_irq(काष्ठा hdmi_hdcp_ctrl *hdcp_ctrl);
#अन्यथा
अटल अंतरभूत काष्ठा hdmi_hdcp_ctrl *msm_hdmi_hdcp_init(काष्ठा hdmi *hdmi)
अणु
	वापस ERR_PTR(-ENXIO);
पूर्ण
अटल अंतरभूत व्योम msm_hdmi_hdcp_destroy(काष्ठा hdmi *hdmi) अणुपूर्ण
अटल अंतरभूत व्योम msm_hdmi_hdcp_on(काष्ठा hdmi_hdcp_ctrl *hdcp_ctrl) अणुपूर्ण
अटल अंतरभूत व्योम msm_hdmi_hdcp_off(काष्ठा hdmi_hdcp_ctrl *hdcp_ctrl) अणुपूर्ण
अटल अंतरभूत व्योम msm_hdmi_hdcp_irq(काष्ठा hdmi_hdcp_ctrl *hdcp_ctrl) अणुपूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* __HDMI_CONNECTOR_H__ */
