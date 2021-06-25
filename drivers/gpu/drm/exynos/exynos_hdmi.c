<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2011 Samsung Electronics Co.Ltd
 * Authors:
 * Seung-Woo Kim <sw0312.kim@samsung.com>
 *	Inki Dae <inki.dae@samsung.com>
 *	Joonyoung Shim <jy0922.shim@samsung.com>
 *
 * Based on drivers/media/video/s5p-tv/hdmi_drv.c
 */

#समावेश <drm/exynos_drm.h>
#समावेश <linux/clk.h>
#समावेश <linux/component.h>
#समावेश <linux/delay.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/hdmi.h>
#समावेश <linux/i2c.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/irq.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_graph.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/regmap.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/रुको.h>

#समावेश <sound/hdmi-codec.h>
#समावेश <media/cec-notअगरier.h>

#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_bridge.h>
#समावेश <drm/drm_edid.h>
#समावेश <drm/drm_prपूर्णांक.h>
#समावेश <drm/drm_probe_helper.h>
#समावेश <drm/drm_simple_kms_helper.h>

#समावेश "exynos_drm_crtc.h"
#समावेश "regs-hdmi.h"

#घोषणा HOTPLUG_DEBOUNCE_MS		1100

क्रमागत hdmi_type अणु
	HDMI_TYPE13,
	HDMI_TYPE14,
	HDMI_TYPE_COUNT
पूर्ण;

#घोषणा HDMI_MAPPED_BASE 0xffff0000

क्रमागत hdmi_mapped_regs अणु
	HDMI_PHY_STATUS = HDMI_MAPPED_BASE,
	HDMI_PHY_RSTOUT,
	HDMI_ACR_CON,
	HDMI_ACR_MCTS0,
	HDMI_ACR_CTS0,
	HDMI_ACR_N0
पूर्ण;

अटल स्थिर u32 hdmi_reg_map[][HDMI_TYPE_COUNT] = अणु
	अणु HDMI_V13_PHY_STATUS, HDMI_PHY_STATUS_0 पूर्ण,
	अणु HDMI_V13_PHY_RSTOUT, HDMI_V14_PHY_RSTOUT पूर्ण,
	अणु HDMI_V13_ACR_CON, HDMI_V14_ACR_CON पूर्ण,
	अणु HDMI_V13_ACR_MCTS0, HDMI_V14_ACR_MCTS0 पूर्ण,
	अणु HDMI_V13_ACR_CTS0, HDMI_V14_ACR_CTS0 पूर्ण,
	अणु HDMI_V13_ACR_N0, HDMI_V14_ACR_N0 पूर्ण,
पूर्ण;

अटल स्थिर अक्षर * स्थिर supply[] = अणु
	"vdd",
	"vdd_osc",
	"vdd_pll",
पूर्ण;

काष्ठा hdmiphy_config अणु
	पूर्णांक pixel_घड़ी;
	u8 conf[32];
पूर्ण;

काष्ठा hdmiphy_configs अणु
	पूर्णांक count;
	स्थिर काष्ठा hdmiphy_config *data;
पूर्ण;

काष्ठा string_array_spec अणु
	पूर्णांक count;
	स्थिर अक्षर * स्थिर *data;
पूर्ण;

#घोषणा INIT_ARRAY_SPEC(a) अणु .count = ARRAY_SIZE(a), .data = a पूर्ण

काष्ठा hdmi_driver_data अणु
	अचिन्हित पूर्णांक type;
	अचिन्हित पूर्णांक is_apb_phy:1;
	अचिन्हित पूर्णांक has_sysreg:1;
	काष्ठा hdmiphy_configs phy_confs;
	काष्ठा string_array_spec clk_gates;
	/*
	 * Array of triplets (p_off, p_on, घड़ी), where p_off and p_on are
	 * required parents of घड़ी when HDMI-PHY is respectively off or on.
	 */
	काष्ठा string_array_spec clk_muxes;
पूर्ण;

काष्ठा hdmi_audio अणु
	काष्ठा platक्रमm_device		*pdev;
	काष्ठा hdmi_audio_infoframe	infoframe;
	काष्ठा hdmi_codec_params	params;
	bool				mute;
पूर्ण;

काष्ठा hdmi_context अणु
	काष्ठा drm_encoder		encoder;
	काष्ठा device			*dev;
	काष्ठा drm_device		*drm_dev;
	काष्ठा drm_connector		connector;
	bool				dvi_mode;
	काष्ठा delayed_work		hotplug_work;
	काष्ठा cec_notअगरier		*notअगरier;
	स्थिर काष्ठा hdmi_driver_data	*drv_data;

	व्योम __iomem			*regs;
	व्योम __iomem			*regs_hdmiphy;
	काष्ठा i2c_client		*hdmiphy_port;
	काष्ठा i2c_adapter		*ddc_adpt;
	काष्ठा gpio_desc		*hpd_gpio;
	पूर्णांक				irq;
	काष्ठा regmap			*pmureg;
	काष्ठा regmap			*sysreg;
	काष्ठा clk			**clk_gates;
	काष्ठा clk			**clk_muxes;
	काष्ठा regulator_bulk_data	regul_bulk[ARRAY_SIZE(supply)];
	काष्ठा regulator		*reg_hdmi_en;
	काष्ठा exynos_drm_clk		phy_clk;
	काष्ठा drm_bridge		*bridge;

	/* mutex protecting subsequent fields below */
	काष्ठा mutex			mutex;
	काष्ठा hdmi_audio		audio;
	bool				घातered;
पूर्ण;

अटल अंतरभूत काष्ठा hdmi_context *encoder_to_hdmi(काष्ठा drm_encoder *e)
अणु
	वापस container_of(e, काष्ठा hdmi_context, encoder);
पूर्ण

अटल अंतरभूत काष्ठा hdmi_context *connector_to_hdmi(काष्ठा drm_connector *c)
अणु
	वापस container_of(c, काष्ठा hdmi_context, connector);
पूर्ण

अटल स्थिर काष्ठा hdmiphy_config hdmiphy_v13_configs[] = अणु
	अणु
		.pixel_घड़ी = 27000000,
		.conf = अणु
			0x01, 0x05, 0x00, 0xD8, 0x10, 0x1C, 0x30, 0x40,
			0x6B, 0x10, 0x02, 0x51, 0xDF, 0xF2, 0x54, 0x87,
			0x84, 0x00, 0x30, 0x38, 0x00, 0x08, 0x10, 0xE0,
			0x22, 0x40, 0xE3, 0x26, 0x00, 0x00, 0x00, 0x80,
		पूर्ण,
	पूर्ण,
	अणु
		.pixel_घड़ी = 27027000,
		.conf = अणु
			0x01, 0x05, 0x00, 0xD4, 0x10, 0x9C, 0x09, 0x64,
			0x6B, 0x10, 0x02, 0x51, 0xDF, 0xF2, 0x54, 0x87,
			0x84, 0x00, 0x30, 0x38, 0x00, 0x08, 0x10, 0xE0,
			0x22, 0x40, 0xE3, 0x26, 0x00, 0x00, 0x00, 0x80,
		पूर्ण,
	पूर्ण,
	अणु
		.pixel_घड़ी = 74176000,
		.conf = अणु
			0x01, 0x05, 0x00, 0xD8, 0x10, 0x9C, 0xef, 0x5B,
			0x6D, 0x10, 0x01, 0x51, 0xef, 0xF3, 0x54, 0xb9,
			0x84, 0x00, 0x30, 0x38, 0x00, 0x08, 0x10, 0xE0,
			0x22, 0x40, 0xa5, 0x26, 0x01, 0x00, 0x00, 0x80,
		पूर्ण,
	पूर्ण,
	अणु
		.pixel_घड़ी = 74250000,
		.conf = अणु
			0x01, 0x05, 0x00, 0xd8, 0x10, 0x9c, 0xf8, 0x40,
			0x6a, 0x10, 0x01, 0x51, 0xff, 0xf1, 0x54, 0xba,
			0x84, 0x00, 0x10, 0x38, 0x00, 0x08, 0x10, 0xe0,
			0x22, 0x40, 0xa4, 0x26, 0x01, 0x00, 0x00, 0x80,
		पूर्ण,
	पूर्ण,
	अणु
		.pixel_घड़ी = 148500000,
		.conf = अणु
			0x01, 0x05, 0x00, 0xD8, 0x10, 0x9C, 0xf8, 0x40,
			0x6A, 0x18, 0x00, 0x51, 0xff, 0xF1, 0x54, 0xba,
			0x84, 0x00, 0x10, 0x38, 0x00, 0x08, 0x10, 0xE0,
			0x22, 0x40, 0xa4, 0x26, 0x02, 0x00, 0x00, 0x80,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा hdmiphy_config hdmiphy_v14_configs[] = अणु
	अणु
		.pixel_घड़ी = 25200000,
		.conf = अणु
			0x01, 0x51, 0x2A, 0x75, 0x40, 0x01, 0x00, 0x08,
			0x82, 0x80, 0xfc, 0xd8, 0x45, 0xa0, 0xac, 0x80,
			0x08, 0x80, 0x11, 0x04, 0x02, 0x22, 0x44, 0x86,
			0x54, 0xf4, 0x24, 0x00, 0x00, 0x00, 0x01, 0x80,
		पूर्ण,
	पूर्ण,
	अणु
		.pixel_घड़ी = 27000000,
		.conf = अणु
			0x01, 0xd1, 0x22, 0x51, 0x40, 0x08, 0xfc, 0x20,
			0x98, 0xa0, 0xcb, 0xd8, 0x45, 0xa0, 0xac, 0x80,
			0x06, 0x80, 0x11, 0x04, 0x02, 0x22, 0x44, 0x86,
			0x54, 0xe4, 0x24, 0x00, 0x00, 0x00, 0x01, 0x80,
		पूर्ण,
	पूर्ण,
	अणु
		.pixel_घड़ी = 27027000,
		.conf = अणु
			0x01, 0xd1, 0x2d, 0x72, 0x40, 0x64, 0x12, 0x08,
			0x43, 0xa0, 0x0e, 0xd9, 0x45, 0xa0, 0xac, 0x80,
			0x08, 0x80, 0x11, 0x04, 0x02, 0x22, 0x44, 0x86,
			0x54, 0xe3, 0x24, 0x00, 0x00, 0x00, 0x01, 0x80,
		पूर्ण,
	पूर्ण,
	अणु
		.pixel_घड़ी = 36000000,
		.conf = अणु
			0x01, 0x51, 0x2d, 0x55, 0x40, 0x01, 0x00, 0x08,
			0x82, 0x80, 0x0e, 0xd9, 0x45, 0xa0, 0xac, 0x80,
			0x08, 0x80, 0x11, 0x04, 0x02, 0x22, 0x44, 0x86,
			0x54, 0xab, 0x24, 0x00, 0x00, 0x00, 0x01, 0x80,
		पूर्ण,
	पूर्ण,
	अणु
		.pixel_घड़ी = 40000000,
		.conf = अणु
			0x01, 0x51, 0x32, 0x55, 0x40, 0x01, 0x00, 0x08,
			0x82, 0x80, 0x2c, 0xd9, 0x45, 0xa0, 0xac, 0x80,
			0x08, 0x80, 0x11, 0x04, 0x02, 0x22, 0x44, 0x86,
			0x54, 0x9a, 0x24, 0x00, 0x00, 0x00, 0x01, 0x80,
		पूर्ण,
	पूर्ण,
	अणु
		.pixel_घड़ी = 65000000,
		.conf = अणु
			0x01, 0xd1, 0x36, 0x34, 0x40, 0x1e, 0x0a, 0x08,
			0x82, 0xa0, 0x45, 0xd9, 0x45, 0xa0, 0xac, 0x80,
			0x08, 0x80, 0x11, 0x04, 0x02, 0x22, 0x44, 0x86,
			0x54, 0xbd, 0x24, 0x01, 0x00, 0x00, 0x01, 0x80,
		पूर्ण,
	पूर्ण,
	अणु
		.pixel_घड़ी = 71000000,
		.conf = अणु
			0x01, 0xd1, 0x3b, 0x35, 0x40, 0x0c, 0x04, 0x08,
			0x85, 0xa0, 0x63, 0xd9, 0x45, 0xa0, 0xac, 0x80,
			0x08, 0x80, 0x11, 0x04, 0x02, 0x22, 0x44, 0x86,
			0x54, 0xad, 0x24, 0x01, 0x00, 0x00, 0x01, 0x80,
		पूर्ण,
	पूर्ण,
	अणु
		.pixel_घड़ी = 73250000,
		.conf = अणु
			0x01, 0xd1, 0x3d, 0x35, 0x40, 0x18, 0x02, 0x08,
			0x83, 0xa0, 0x6e, 0xd9, 0x45, 0xa0, 0xac, 0x80,
			0x08, 0x80, 0x11, 0x04, 0x02, 0x22, 0x44, 0x86,
			0x54, 0xa8, 0x24, 0x01, 0x00, 0x00, 0x01, 0x80,
		पूर्ण,
	पूर्ण,
	अणु
		.pixel_घड़ी = 74176000,
		.conf = अणु
			0x01, 0xd1, 0x3e, 0x35, 0x40, 0x5b, 0xde, 0x08,
			0x82, 0xa0, 0x73, 0xd9, 0x45, 0xa0, 0xac, 0x80,
			0x56, 0x80, 0x11, 0x04, 0x02, 0x22, 0x44, 0x86,
			0x54, 0xa6, 0x24, 0x01, 0x00, 0x00, 0x01, 0x80,
		पूर्ण,
	पूर्ण,
	अणु
		.pixel_घड़ी = 74250000,
		.conf = अणु
			0x01, 0xd1, 0x1f, 0x10, 0x40, 0x40, 0xf8, 0x08,
			0x81, 0xa0, 0xba, 0xd8, 0x45, 0xa0, 0xac, 0x80,
			0x3c, 0x80, 0x11, 0x04, 0x02, 0x22, 0x44, 0x86,
			0x54, 0xa5, 0x24, 0x01, 0x00, 0x00, 0x01, 0x80,
		पूर्ण,
	पूर्ण,
	अणु
		.pixel_घड़ी = 83500000,
		.conf = अणु
			0x01, 0xd1, 0x23, 0x11, 0x40, 0x0c, 0xfb, 0x08,
			0x85, 0xa0, 0xd1, 0xd8, 0x45, 0xa0, 0xac, 0x80,
			0x08, 0x80, 0x11, 0x04, 0x02, 0x22, 0x44, 0x86,
			0x54, 0x93, 0x24, 0x01, 0x00, 0x00, 0x01, 0x80,
		पूर्ण,
	पूर्ण,
	अणु
		.pixel_घड़ी = 85500000,
		.conf = अणु
			0x01, 0xd1, 0x24, 0x11, 0x40, 0x40, 0xd0, 0x08,
			0x84, 0xa0, 0xd6, 0xd8, 0x45, 0xa0, 0xac, 0x80,
			0x08, 0x80, 0x11, 0x04, 0x02, 0x22, 0x44, 0x86,
			0x54, 0x90, 0x24, 0x01, 0x00, 0x00, 0x01, 0x80,
		पूर्ण,
	पूर्ण,
	अणु
		.pixel_घड़ी = 106500000,
		.conf = अणु
			0x01, 0xd1, 0x2c, 0x12, 0x40, 0x0c, 0x09, 0x08,
			0x84, 0xa0, 0x0a, 0xd9, 0x45, 0xa0, 0xac, 0x80,
			0x08, 0x80, 0x11, 0x04, 0x02, 0x22, 0x44, 0x86,
			0x54, 0x73, 0x24, 0x01, 0x00, 0x00, 0x01, 0x80,
		पूर्ण,
	पूर्ण,
	अणु
		.pixel_घड़ी = 108000000,
		.conf = अणु
			0x01, 0x51, 0x2d, 0x15, 0x40, 0x01, 0x00, 0x08,
			0x82, 0x80, 0x0e, 0xd9, 0x45, 0xa0, 0xac, 0x80,
			0x08, 0x80, 0x11, 0x04, 0x02, 0x22, 0x44, 0x86,
			0x54, 0xc7, 0x25, 0x03, 0x00, 0x00, 0x01, 0x80,
		पूर्ण,
	पूर्ण,
	अणु
		.pixel_घड़ी = 115500000,
		.conf = अणु
			0x01, 0xd1, 0x30, 0x12, 0x40, 0x40, 0x10, 0x08,
			0x80, 0x80, 0x21, 0xd9, 0x45, 0xa0, 0xac, 0x80,
			0x08, 0x80, 0x11, 0x04, 0x02, 0x22, 0x44, 0x86,
			0x54, 0xaa, 0x25, 0x03, 0x00, 0x00, 0x01, 0x80,
		पूर्ण,
	पूर्ण,
	अणु
		.pixel_घड़ी = 119000000,
		.conf = अणु
			0x01, 0xd1, 0x32, 0x1a, 0x40, 0x30, 0xd8, 0x08,
			0x04, 0xa0, 0x2a, 0xd9, 0x45, 0xa0, 0xac, 0x80,
			0x08, 0x80, 0x11, 0x04, 0x02, 0x22, 0x44, 0x86,
			0x54, 0x9d, 0x25, 0x03, 0x00, 0x00, 0x01, 0x80,
		पूर्ण,
	पूर्ण,
	अणु
		.pixel_घड़ी = 146250000,
		.conf = अणु
			0x01, 0xd1, 0x3d, 0x15, 0x40, 0x18, 0xfd, 0x08,
			0x83, 0xa0, 0x6e, 0xd9, 0x45, 0xa0, 0xac, 0x80,
			0x08, 0x80, 0x11, 0x04, 0x02, 0x22, 0x44, 0x86,
			0x54, 0x50, 0x25, 0x03, 0x00, 0x00, 0x01, 0x80,
		पूर्ण,
	पूर्ण,
	अणु
		.pixel_घड़ी = 148500000,
		.conf = अणु
			0x01, 0xd1, 0x1f, 0x00, 0x40, 0x40, 0xf8, 0x08,
			0x81, 0xa0, 0xba, 0xd8, 0x45, 0xa0, 0xac, 0x80,
			0x3c, 0x80, 0x11, 0x04, 0x02, 0x22, 0x44, 0x86,
			0x54, 0x4b, 0x25, 0x03, 0x00, 0x00, 0x01, 0x80,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा hdmiphy_config hdmiphy_5420_configs[] = अणु
	अणु
		.pixel_घड़ी = 25200000,
		.conf = अणु
			0x01, 0x52, 0x3F, 0x55, 0x40, 0x01, 0x00, 0xC8,
			0x82, 0xC8, 0xBD, 0xD8, 0x45, 0xA0, 0xAC, 0x80,
			0x06, 0x80, 0x01, 0x84, 0x05, 0x02, 0x24, 0x66,
			0x54, 0xF4, 0x24, 0x00, 0x00, 0x00, 0x01, 0x80,
		पूर्ण,
	पूर्ण,
	अणु
		.pixel_घड़ी = 27000000,
		.conf = अणु
			0x01, 0xD1, 0x22, 0x51, 0x40, 0x08, 0xFC, 0xE0,
			0x98, 0xE8, 0xCB, 0xD8, 0x45, 0xA0, 0xAC, 0x80,
			0x06, 0x80, 0x09, 0x84, 0x05, 0x02, 0x24, 0x66,
			0x54, 0xE4, 0x24, 0x00, 0x00, 0x00, 0x01, 0x80,
		पूर्ण,
	पूर्ण,
	अणु
		.pixel_घड़ी = 27027000,
		.conf = अणु
			0x01, 0xD1, 0x2D, 0x72, 0x40, 0x64, 0x12, 0xC8,
			0x43, 0xE8, 0x0E, 0xD9, 0x45, 0xA0, 0xAC, 0x80,
			0x26, 0x80, 0x09, 0x84, 0x05, 0x02, 0x24, 0x66,
			0x54, 0xE3, 0x24, 0x00, 0x00, 0x00, 0x01, 0x80,
		पूर्ण,
	पूर्ण,
	अणु
		.pixel_घड़ी = 36000000,
		.conf = अणु
			0x01, 0x51, 0x2D, 0x55, 0x40, 0x40, 0x00, 0xC8,
			0x02, 0xC8, 0x0E, 0xD9, 0x45, 0xA0, 0xAC, 0x80,
			0x08, 0x80, 0x09, 0x84, 0x05, 0x02, 0x24, 0x66,
			0x54, 0xAB, 0x24, 0x00, 0x00, 0x00, 0x01, 0x80,
		पूर्ण,
	पूर्ण,
	अणु
		.pixel_घड़ी = 40000000,
		.conf = अणु
			0x01, 0xD1, 0x21, 0x31, 0x40, 0x3C, 0x28, 0xC8,
			0x87, 0xE8, 0xC8, 0xD8, 0x45, 0xA0, 0xAC, 0x80,
			0x08, 0x80, 0x09, 0x84, 0x05, 0x02, 0x24, 0x66,
			0x54, 0x9A, 0x24, 0x00, 0x00, 0x00, 0x01, 0x80,
		पूर्ण,
	पूर्ण,
	अणु
		.pixel_घड़ी = 65000000,
		.conf = अणु
			0x01, 0xD1, 0x36, 0x34, 0x40, 0x0C, 0x04, 0xC8,
			0x82, 0xE8, 0x45, 0xD9, 0x45, 0xA0, 0xAC, 0x80,
			0x08, 0x80, 0x09, 0x84, 0x05, 0x02, 0x24, 0x66,
			0x54, 0xBD, 0x24, 0x01, 0x00, 0x00, 0x01, 0x80,
		पूर्ण,
	पूर्ण,
	अणु
		.pixel_घड़ी = 71000000,
		.conf = अणु
			0x01, 0xD1, 0x3B, 0x35, 0x40, 0x0C, 0x04, 0xC8,
			0x85, 0xE8, 0x63, 0xD9, 0x45, 0xA0, 0xAC, 0x80,
			0x08, 0x80, 0x09, 0x84, 0x05, 0x02, 0x24, 0x66,
			0x54, 0x57, 0x24, 0x00, 0x00, 0x00, 0x01, 0x80,
		पूर्ण,
	पूर्ण,
	अणु
		.pixel_घड़ी = 73250000,
		.conf = अणु
			0x01, 0xD1, 0x1F, 0x10, 0x40, 0x78, 0x8D, 0xC8,
			0x81, 0xE8, 0xB7, 0xD8, 0x45, 0xA0, 0xAC, 0x80,
			0x56, 0x80, 0x09, 0x84, 0x05, 0x02, 0x24, 0x66,
			0x54, 0xA8, 0x24, 0x01, 0x00, 0x00, 0x01, 0x80,
		पूर्ण,
	पूर्ण,
	अणु
		.pixel_घड़ी = 74176000,
		.conf = अणु
			0x01, 0xD1, 0x1F, 0x10, 0x40, 0x5B, 0xEF, 0xC8,
			0x81, 0xE8, 0xB9, 0xD8, 0x45, 0xA0, 0xAC, 0x80,
			0x56, 0x80, 0x09, 0x84, 0x05, 0x02, 0x24, 0x66,
			0x54, 0xA6, 0x24, 0x01, 0x00, 0x00, 0x01, 0x80,
		पूर्ण,
	पूर्ण,
	अणु
		.pixel_घड़ी = 74250000,
		.conf = अणु
			0x01, 0xD1, 0x1F, 0x10, 0x40, 0x40, 0xF8, 0x08,
			0x81, 0xE8, 0xBA, 0xD8, 0x45, 0xA0, 0xAC, 0x80,
			0x26, 0x80, 0x09, 0x84, 0x05, 0x22, 0x24, 0x66,
			0x54, 0xA5, 0x24, 0x01, 0x00, 0x00, 0x01, 0x80,
		पूर्ण,
	पूर्ण,
	अणु
		.pixel_घड़ी = 83500000,
		.conf = अणु
			0x01, 0xD1, 0x23, 0x11, 0x40, 0x0C, 0xFB, 0xC8,
			0x85, 0xE8, 0xD1, 0xD8, 0x45, 0xA0, 0xAC, 0x80,
			0x08, 0x80, 0x09, 0x84, 0x05, 0x02, 0x24, 0x66,
			0x54, 0x4A, 0x24, 0x00, 0x00, 0x00, 0x01, 0x80,
		पूर्ण,
	पूर्ण,
	अणु
		.pixel_घड़ी = 88750000,
		.conf = अणु
			0x01, 0xD1, 0x25, 0x11, 0x40, 0x18, 0xFF, 0xC8,
			0x83, 0xE8, 0xDE, 0xD8, 0x45, 0xA0, 0xAC, 0x80,
			0x08, 0x80, 0x09, 0x84, 0x05, 0x02, 0x24, 0x66,
			0x54, 0x45, 0x24, 0x00, 0x00, 0x00, 0x01, 0x80,
		पूर्ण,
	पूर्ण,
	अणु
		.pixel_घड़ी = 106500000,
		.conf = अणु
			0x01, 0xD1, 0x2C, 0x12, 0x40, 0x0C, 0x09, 0xC8,
			0x84, 0xE8, 0x0A, 0xD9, 0x45, 0xA0, 0xAC, 0x80,
			0x08, 0x80, 0x09, 0x84, 0x05, 0x02, 0x24, 0x66,
			0x54, 0x73, 0x24, 0x01, 0x00, 0x00, 0x01, 0x80,
		पूर्ण,
	पूर्ण,
	अणु
		.pixel_घड़ी = 108000000,
		.conf = अणु
			0x01, 0x51, 0x2D, 0x15, 0x40, 0x01, 0x00, 0xC8,
			0x82, 0xC8, 0x0E, 0xD9, 0x45, 0xA0, 0xAC, 0x80,
			0x08, 0x80, 0x09, 0x84, 0x05, 0x02, 0x24, 0x66,
			0x54, 0xC7, 0x25, 0x03, 0x00, 0x00, 0x01, 0x80,
		पूर्ण,
	पूर्ण,
	अणु
		.pixel_घड़ी = 115500000,
		.conf = अणु
			0x01, 0xD1, 0x30, 0x14, 0x40, 0x0C, 0x03, 0xC8,
			0x88, 0xE8, 0x21, 0xD9, 0x45, 0xA0, 0xAC, 0x80,
			0x08, 0x80, 0x09, 0x84, 0x05, 0x02, 0x24, 0x66,
			0x54, 0x6A, 0x24, 0x01, 0x00, 0x00, 0x01, 0x80,
		पूर्ण,
	पूर्ण,
	अणु
		.pixel_घड़ी = 146250000,
		.conf = अणु
			0x01, 0xD1, 0x3D, 0x15, 0x40, 0x18, 0xFD, 0xC8,
			0x83, 0xE8, 0x6E, 0xD9, 0x45, 0xA0, 0xAC, 0x80,
			0x08, 0x80, 0x09, 0x84, 0x05, 0x02, 0x24, 0x66,
			0x54, 0x54, 0x24, 0x01, 0x00, 0x00, 0x01, 0x80,
		पूर्ण,
	पूर्ण,
	अणु
		.pixel_घड़ी = 148500000,
		.conf = अणु
			0x01, 0xD1, 0x1F, 0x00, 0x40, 0x40, 0xF8, 0x08,
			0x81, 0xE8, 0xBA, 0xD8, 0x45, 0xA0, 0xAC, 0x80,
			0x26, 0x80, 0x09, 0x84, 0x05, 0x22, 0x24, 0x66,
			0x54, 0x4B, 0x25, 0x03, 0x00, 0x80, 0x01, 0x80,
		पूर्ण,
	पूर्ण,
	अणु
		.pixel_घड़ी = 154000000,
		.conf = अणु
			0x01, 0xD1, 0x20, 0x01, 0x40, 0x30, 0x08, 0xCC,
			0x8C, 0xE8, 0xC1, 0xD8, 0x45, 0xA0, 0xAC, 0x80,
			0x08, 0x80, 0x09, 0x84, 0x05, 0x02, 0x24, 0x86,
			0x54, 0x3F, 0x25, 0x03, 0x00, 0x00, 0x01, 0x80,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा hdmiphy_config hdmiphy_5433_configs[] = अणु
	अणु
		.pixel_घड़ी = 27000000,
		.conf = अणु
			0x01, 0x51, 0x2d, 0x75, 0x01, 0x00, 0x88, 0x02,
			0x72, 0x50, 0x44, 0x8c, 0x27, 0x00, 0x7c, 0xac,
			0xd6, 0x2b, 0x67, 0x00, 0x00, 0x04, 0x00, 0x30,
			0x08, 0x10, 0x01, 0x01, 0x48, 0x40, 0x00, 0x40,
		पूर्ण,
	पूर्ण,
	अणु
		.pixel_घड़ी = 27027000,
		.conf = अणु
			0x01, 0x51, 0x2d, 0x72, 0x64, 0x09, 0x88, 0xc3,
			0x71, 0x50, 0x44, 0x8c, 0x27, 0x00, 0x7c, 0xac,
			0xd6, 0x2b, 0x67, 0x00, 0x00, 0x04, 0x00, 0x30,
			0x08, 0x10, 0x01, 0x01, 0x48, 0x40, 0x00, 0x40,
		पूर्ण,
	पूर्ण,
	अणु
		.pixel_घड़ी = 40000000,
		.conf = अणु
			0x01, 0x51, 0x32, 0x55, 0x01, 0x00, 0x88, 0x02,
			0x4d, 0x50, 0x44, 0x8C, 0x27, 0x00, 0x7C, 0xAC,
			0xD6, 0x2B, 0x67, 0x00, 0x00, 0x04, 0x00, 0x30,
			0x08, 0x10, 0x01, 0x01, 0x48, 0x40, 0x00, 0x40,
		पूर्ण,
	पूर्ण,
	अणु
		.pixel_घड़ी = 50000000,
		.conf = अणु
			0x01, 0x51, 0x34, 0x40, 0x64, 0x09, 0x88, 0xc3,
			0x3d, 0x50, 0x44, 0x8C, 0x27, 0x00, 0x7C, 0xAC,
			0xD6, 0x2B, 0x67, 0x00, 0x00, 0x04, 0x00, 0x30,
			0x08, 0x10, 0x01, 0x01, 0x48, 0x40, 0x00, 0x40,
		पूर्ण,
	पूर्ण,
	अणु
		.pixel_घड़ी = 65000000,
		.conf = अणु
			0x01, 0x51, 0x36, 0x31, 0x40, 0x10, 0x04, 0xc6,
			0x2e, 0xe8, 0x44, 0x8C, 0x27, 0x00, 0x7C, 0xAC,
			0xD6, 0x2B, 0x67, 0x00, 0x00, 0x04, 0x00, 0x30,
			0x08, 0x10, 0x01, 0x01, 0x48, 0x40, 0x00, 0x40,
		पूर्ण,
	पूर्ण,
	अणु
		.pixel_घड़ी = 74176000,
		.conf = अणु
			0x01, 0x51, 0x3E, 0x35, 0x5B, 0xDE, 0x88, 0x42,
			0x53, 0x51, 0x44, 0x8C, 0x27, 0x00, 0x7C, 0xAC,
			0xD6, 0x2B, 0x67, 0x00, 0x00, 0x04, 0x00, 0x30,
			0x08, 0x10, 0x01, 0x01, 0x48, 0x40, 0x00, 0x40,
		पूर्ण,
	पूर्ण,
	अणु
		.pixel_घड़ी = 74250000,
		.conf = अणु
			0x01, 0x51, 0x3E, 0x35, 0x40, 0xF0, 0x88, 0xC2,
			0x52, 0x51, 0x44, 0x8C, 0x27, 0x00, 0x7C, 0xAC,
			0xD6, 0x2B, 0x67, 0x00, 0x00, 0x04, 0x00, 0x30,
			0x08, 0x10, 0x01, 0x01, 0x48, 0x40, 0x00, 0x40,
		पूर्ण,
	पूर्ण,
	अणु
		.pixel_घड़ी = 108000000,
		.conf = अणु
			0x01, 0x51, 0x2d, 0x15, 0x01, 0x00, 0x88, 0x02,
			0x72, 0x52, 0x44, 0x8C, 0x27, 0x00, 0x7C, 0xAC,
			0xD6, 0x2B, 0x67, 0x00, 0x00, 0x04, 0x00, 0x30,
			0x08, 0x10, 0x01, 0x01, 0x48, 0x40, 0x00, 0x40,
		पूर्ण,
	पूर्ण,
	अणु
		.pixel_घड़ी = 148500000,
		.conf = अणु
			0x01, 0x51, 0x1f, 0x00, 0x40, 0xf8, 0x88, 0xc1,
			0x52, 0x52, 0x24, 0x0c, 0x24, 0x0f, 0x7c, 0xa5,
			0xd4, 0x2b, 0x87, 0x00, 0x00, 0x04, 0x00, 0x30,
			0x08, 0x10, 0x01, 0x01, 0x48, 0x4a, 0x00, 0x40,
		पूर्ण,
	पूर्ण,
	अणु
		.pixel_घड़ी = 297000000,
		.conf = अणु
			0x01, 0x51, 0x3E, 0x05, 0x40, 0xF0, 0x88, 0xC2,
			0x52, 0x53, 0x44, 0x8C, 0x27, 0x00, 0x7C, 0xAC,
			0xD6, 0x2B, 0x67, 0x00, 0x00, 0x04, 0x00, 0x30,
			0x08, 0x10, 0x01, 0x01, 0x48, 0x40, 0x00, 0x40,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर अक्षर * स्थिर hdmi_clk_gates4[] = अणु
	"hdmi", "sclk_hdmi"
पूर्ण;

अटल स्थिर अक्षर * स्थिर hdmi_clk_muxes4[] = अणु
	"sclk_pixel", "sclk_hdmiphy", "mout_hdmi"
पूर्ण;

अटल स्थिर अक्षर * स्थिर hdmi_clk_gates5433[] = अणु
	"hdmi_pclk", "hdmi_i_pclk", "i_tmds_clk", "i_pixel_clk", "i_spdif_clk"
पूर्ण;

अटल स्थिर अक्षर * स्थिर hdmi_clk_muxes5433[] = अणु
	"oscclk", "tmds_clko", "tmds_clko_user",
	"oscclk", "pixel_clko", "pixel_clko_user"
पूर्ण;

अटल स्थिर काष्ठा hdmi_driver_data exynos4210_hdmi_driver_data = अणु
	.type		= HDMI_TYPE13,
	.phy_confs	= INIT_ARRAY_SPEC(hdmiphy_v13_configs),
	.clk_gates	= INIT_ARRAY_SPEC(hdmi_clk_gates4),
	.clk_muxes	= INIT_ARRAY_SPEC(hdmi_clk_muxes4),
पूर्ण;

अटल स्थिर काष्ठा hdmi_driver_data exynos4212_hdmi_driver_data = अणु
	.type		= HDMI_TYPE14,
	.phy_confs	= INIT_ARRAY_SPEC(hdmiphy_v14_configs),
	.clk_gates	= INIT_ARRAY_SPEC(hdmi_clk_gates4),
	.clk_muxes	= INIT_ARRAY_SPEC(hdmi_clk_muxes4),
पूर्ण;

अटल स्थिर काष्ठा hdmi_driver_data exynos5420_hdmi_driver_data = अणु
	.type		= HDMI_TYPE14,
	.is_apb_phy	= 1,
	.phy_confs	= INIT_ARRAY_SPEC(hdmiphy_5420_configs),
	.clk_gates	= INIT_ARRAY_SPEC(hdmi_clk_gates4),
	.clk_muxes	= INIT_ARRAY_SPEC(hdmi_clk_muxes4),
पूर्ण;

अटल स्थिर काष्ठा hdmi_driver_data exynos5433_hdmi_driver_data = अणु
	.type		= HDMI_TYPE14,
	.is_apb_phy	= 1,
	.has_sysreg     = 1,
	.phy_confs	= INIT_ARRAY_SPEC(hdmiphy_5433_configs),
	.clk_gates	= INIT_ARRAY_SPEC(hdmi_clk_gates5433),
	.clk_muxes	= INIT_ARRAY_SPEC(hdmi_clk_muxes5433),
पूर्ण;

अटल अंतरभूत u32 hdmi_map_reg(काष्ठा hdmi_context *hdata, u32 reg_id)
अणु
	अगर ((reg_id & 0xffff0000) == HDMI_MAPPED_BASE)
		वापस hdmi_reg_map[reg_id & 0xffff][hdata->drv_data->type];
	वापस reg_id;
पूर्ण

अटल अंतरभूत u32 hdmi_reg_पढ़ो(काष्ठा hdmi_context *hdata, u32 reg_id)
अणु
	वापस पढ़ोl(hdata->regs + hdmi_map_reg(hdata, reg_id));
पूर्ण

अटल अंतरभूत व्योम hdmi_reg_ग_लिखोb(काष्ठा hdmi_context *hdata,
				 u32 reg_id, u8 value)
अणु
	ग_लिखोl(value, hdata->regs + hdmi_map_reg(hdata, reg_id));
पूर्ण

अटल अंतरभूत व्योम hdmi_reg_ग_लिखोv(काष्ठा hdmi_context *hdata, u32 reg_id,
				   पूर्णांक bytes, u32 val)
अणु
	reg_id = hdmi_map_reg(hdata, reg_id);

	जबतक (--bytes >= 0) अणु
		ग_लिखोl(val & 0xff, hdata->regs + reg_id);
		val >>= 8;
		reg_id += 4;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम hdmi_reg_ग_लिखो_buf(काष्ठा hdmi_context *hdata, u32 reg_id,
				      u8 *buf, पूर्णांक size)
अणु
	क्रम (reg_id = hdmi_map_reg(hdata, reg_id); size; --size, reg_id += 4)
		ग_लिखोl(*buf++, hdata->regs + reg_id);
पूर्ण

अटल अंतरभूत व्योम hdmi_reg_ग_लिखोmask(काष्ठा hdmi_context *hdata,
				 u32 reg_id, u32 value, u32 mask)
अणु
	u32 old;

	reg_id = hdmi_map_reg(hdata, reg_id);
	old = पढ़ोl(hdata->regs + reg_id);
	value = (value & mask) | (old & ~mask);
	ग_लिखोl(value, hdata->regs + reg_id);
पूर्ण

अटल पूर्णांक hdmiphy_reg_ग_लिखो_buf(काष्ठा hdmi_context *hdata,
			u32 reg_offset, स्थिर u8 *buf, u32 len)
अणु
	अगर ((reg_offset + len) > 32)
		वापस -EINVAL;

	अगर (hdata->hdmiphy_port) अणु
		पूर्णांक ret;

		ret = i2c_master_send(hdata->hdmiphy_port, buf, len);
		अगर (ret == len)
			वापस 0;
		वापस ret;
	पूर्ण अन्यथा अणु
		पूर्णांक i;
		क्रम (i = 0; i < len; i++)
			ग_लिखोl(buf[i], hdata->regs_hdmiphy +
				((reg_offset + i)<<2));
		वापस 0;
	पूर्ण
पूर्ण

अटल पूर्णांक hdmi_clk_enable_gates(काष्ठा hdmi_context *hdata)
अणु
	पूर्णांक i, ret;

	क्रम (i = 0; i < hdata->drv_data->clk_gates.count; ++i) अणु
		ret = clk_prepare_enable(hdata->clk_gates[i]);
		अगर (!ret)
			जारी;

		dev_err(hdata->dev, "Cannot enable clock '%s', %d\n",
			hdata->drv_data->clk_gates.data[i], ret);
		जबतक (i--)
			clk_disable_unprepare(hdata->clk_gates[i]);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम hdmi_clk_disable_gates(काष्ठा hdmi_context *hdata)
अणु
	पूर्णांक i = hdata->drv_data->clk_gates.count;

	जबतक (i--)
		clk_disable_unprepare(hdata->clk_gates[i]);
पूर्ण

अटल पूर्णांक hdmi_clk_set_parents(काष्ठा hdmi_context *hdata, bool to_phy)
अणु
	काष्ठा device *dev = hdata->dev;
	पूर्णांक ret = 0;
	पूर्णांक i;

	क्रम (i = 0; i < hdata->drv_data->clk_muxes.count; i += 3) अणु
		काष्ठा clk **c = &hdata->clk_muxes[i];

		ret = clk_set_parent(c[2], c[to_phy]);
		अगर (!ret)
			जारी;

		dev_err(dev, "Cannot set clock parent of '%s' to '%s', %d\n",
			hdata->drv_data->clk_muxes.data[i + 2],
			hdata->drv_data->clk_muxes.data[i + to_phy], ret);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक hdmi_audio_infoframe_apply(काष्ठा hdmi_context *hdata)
अणु
	काष्ठा hdmi_audio_infoframe *infoframe = &hdata->audio.infoframe;
	u8 buf[HDMI_INFOFRAME_SIZE(AUDIO)];
	पूर्णांक len;

	len = hdmi_audio_infoframe_pack(infoframe, buf, माप(buf));
	अगर (len < 0)
		वापस len;

	hdmi_reg_ग_लिखोb(hdata, HDMI_AUI_CON, HDMI_AUI_CON_EVERY_VSYNC);
	hdmi_reg_ग_लिखो_buf(hdata, HDMI_AUI_HEADER0, buf, len);

	वापस 0;
पूर्ण

अटल व्योम hdmi_reg_infoframes(काष्ठा hdmi_context *hdata)
अणु
	काष्ठा drm_display_mode *m = &hdata->encoder.crtc->state->mode;
	जोड़ hdmi_infoframe frm;
	u8 buf[25];
	पूर्णांक ret;

	अगर (hdata->dvi_mode) अणु
		hdmi_reg_ग_लिखोb(hdata, HDMI_AVI_CON,
				HDMI_AVI_CON_DO_NOT_TRANSMIT);
		hdmi_reg_ग_लिखोb(hdata, HDMI_VSI_CON,
				HDMI_VSI_CON_DO_NOT_TRANSMIT);
		hdmi_reg_ग_लिखोb(hdata, HDMI_AUI_CON, HDMI_AUI_CON_NO_TRAN);
		वापस;
	पूर्ण

	ret = drm_hdmi_avi_infoframe_from_display_mode(&frm.avi,
						       &hdata->connector, m);
	अगर (!ret)
		ret = hdmi_avi_infoframe_pack(&frm.avi, buf, माप(buf));
	अगर (ret > 0) अणु
		hdmi_reg_ग_लिखोb(hdata, HDMI_AVI_CON, HDMI_AVI_CON_EVERY_VSYNC);
		hdmi_reg_ग_लिखो_buf(hdata, HDMI_AVI_HEADER0, buf, ret);
	पूर्ण अन्यथा अणु
		DRM_INFO("%s: invalid AVI infoframe (%d)\n", __func__, ret);
	पूर्ण

	ret = drm_hdmi_venकरोr_infoframe_from_display_mode(&frm.venकरोr.hdmi,
							  &hdata->connector, m);
	अगर (!ret)
		ret = hdmi_venकरोr_infoframe_pack(&frm.venकरोr.hdmi, buf,
				माप(buf));
	अगर (ret > 0) अणु
		hdmi_reg_ग_लिखोb(hdata, HDMI_VSI_CON, HDMI_VSI_CON_EVERY_VSYNC);
		hdmi_reg_ग_लिखो_buf(hdata, HDMI_VSI_HEADER0, buf, 3);
		hdmi_reg_ग_लिखो_buf(hdata, HDMI_VSI_DATA(0), buf + 3, ret - 3);
	पूर्ण

	hdmi_audio_infoframe_apply(hdata);
पूर्ण

अटल क्रमागत drm_connector_status hdmi_detect(काष्ठा drm_connector *connector,
				bool क्रमce)
अणु
	काष्ठा hdmi_context *hdata = connector_to_hdmi(connector);

	अगर (gpiod_get_value(hdata->hpd_gpio))
		वापस connector_status_connected;

	cec_notअगरier_set_phys_addr(hdata->notअगरier, CEC_PHYS_ADDR_INVALID);
	वापस connector_status_disconnected;
पूर्ण

अटल व्योम hdmi_connector_destroy(काष्ठा drm_connector *connector)
अणु
	काष्ठा hdmi_context *hdata = connector_to_hdmi(connector);

	cec_notअगरier_conn_unरेजिस्टर(hdata->notअगरier);

	drm_connector_unरेजिस्टर(connector);
	drm_connector_cleanup(connector);
पूर्ण

अटल स्थिर काष्ठा drm_connector_funcs hdmi_connector_funcs = अणु
	.fill_modes = drm_helper_probe_single_connector_modes,
	.detect = hdmi_detect,
	.destroy = hdmi_connector_destroy,
	.reset = drm_atomic_helper_connector_reset,
	.atomic_duplicate_state = drm_atomic_helper_connector_duplicate_state,
	.atomic_destroy_state = drm_atomic_helper_connector_destroy_state,
पूर्ण;

अटल पूर्णांक hdmi_get_modes(काष्ठा drm_connector *connector)
अणु
	काष्ठा hdmi_context *hdata = connector_to_hdmi(connector);
	काष्ठा edid *edid;
	पूर्णांक ret;

	अगर (!hdata->ddc_adpt)
		वापस -ENODEV;

	edid = drm_get_edid(connector, hdata->ddc_adpt);
	अगर (!edid)
		वापस -ENODEV;

	hdata->dvi_mode = !drm_detect_hdmi_monitor(edid);
	DRM_DEV_DEBUG_KMS(hdata->dev, "%s : width[%d] x height[%d]\n",
			  (hdata->dvi_mode ? "dvi monitor" : "hdmi monitor"),
			  edid->width_cm, edid->height_cm);

	drm_connector_update_edid_property(connector, edid);
	cec_notअगरier_set_phys_addr_from_edid(hdata->notअगरier, edid);

	ret = drm_add_edid_modes(connector, edid);

	kमुक्त(edid);

	वापस ret;
पूर्ण

अटल पूर्णांक hdmi_find_phy_conf(काष्ठा hdmi_context *hdata, u32 pixel_घड़ी)
अणु
	स्थिर काष्ठा hdmiphy_configs *confs = &hdata->drv_data->phy_confs;
	पूर्णांक i;

	क्रम (i = 0; i < confs->count; i++)
		अगर (confs->data[i].pixel_घड़ी == pixel_घड़ी)
			वापस i;

	DRM_DEV_DEBUG_KMS(hdata->dev, "Could not find phy config for %d\n",
			  pixel_घड़ी);
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक hdmi_mode_valid(काष्ठा drm_connector *connector,
			काष्ठा drm_display_mode *mode)
अणु
	काष्ठा hdmi_context *hdata = connector_to_hdmi(connector);
	पूर्णांक ret;

	DRM_DEV_DEBUG_KMS(hdata->dev,
			  "xres=%d, yres=%d, refresh=%d, intl=%d clock=%d\n",
			  mode->hdisplay, mode->vdisplay,
			  drm_mode_vrefresh(mode),
			  (mode->flags & DRM_MODE_FLAG_INTERLACE) ? true :
			  false, mode->घड़ी * 1000);

	ret = hdmi_find_phy_conf(hdata, mode->घड़ी * 1000);
	अगर (ret < 0)
		वापस MODE_BAD;

	वापस MODE_OK;
पूर्ण

अटल स्थिर काष्ठा drm_connector_helper_funcs hdmi_connector_helper_funcs = अणु
	.get_modes = hdmi_get_modes,
	.mode_valid = hdmi_mode_valid,
पूर्ण;

अटल पूर्णांक hdmi_create_connector(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा hdmi_context *hdata = encoder_to_hdmi(encoder);
	काष्ठा drm_connector *connector = &hdata->connector;
	काष्ठा cec_connector_info conn_info;
	पूर्णांक ret;

	connector->पूर्णांकerlace_allowed = true;
	connector->polled = DRM_CONNECTOR_POLL_HPD;

	ret = drm_connector_init_with_ddc(hdata->drm_dev, connector,
					  &hdmi_connector_funcs,
					  DRM_MODE_CONNECTOR_HDMIA,
					  hdata->ddc_adpt);
	अगर (ret) अणु
		DRM_DEV_ERROR(hdata->dev,
			      "Failed to initialize connector with drm\n");
		वापस ret;
	पूर्ण

	drm_connector_helper_add(connector, &hdmi_connector_helper_funcs);
	drm_connector_attach_encoder(connector, encoder);

	अगर (hdata->bridge) अणु
		ret = drm_bridge_attach(encoder, hdata->bridge, शून्य, 0);
		अगर (ret)
			DRM_DEV_ERROR(hdata->dev, "Failed to attach bridge\n");
	पूर्ण

	cec_fill_conn_info_from_drm(&conn_info, connector);

	hdata->notअगरier = cec_notअगरier_conn_रेजिस्टर(hdata->dev, शून्य,
						     &conn_info);
	अगर (!hdata->notअगरier) अणु
		ret = -ENOMEM;
		DRM_DEV_ERROR(hdata->dev, "Failed to allocate CEC notifier\n");
	पूर्ण

	वापस ret;
पूर्ण

अटल bool hdmi_mode_fixup(काष्ठा drm_encoder *encoder,
			    स्थिर काष्ठा drm_display_mode *mode,
			    काष्ठा drm_display_mode *adjusted_mode)
अणु
	काष्ठा drm_device *dev = encoder->dev;
	काष्ठा drm_connector *connector;
	काष्ठा drm_display_mode *m;
	काष्ठा drm_connector_list_iter conn_iter;
	पूर्णांक mode_ok;

	drm_mode_set_crtcinfo(adjusted_mode, 0);

	drm_connector_list_iter_begin(dev, &conn_iter);
	drm_क्रम_each_connector_iter(connector, &conn_iter) अणु
		अगर (connector->encoder == encoder)
			अवरोध;
	पूर्ण
	अगर (connector)
		drm_connector_get(connector);
	drm_connector_list_iter_end(&conn_iter);

	अगर (!connector)
		वापस true;

	mode_ok = hdmi_mode_valid(connector, adjusted_mode);

	अगर (mode_ok == MODE_OK)
		जाओ cleanup;

	/*
	 * Find the most suitable mode and copy it to adjusted_mode.
	 */
	list_क्रम_each_entry(m, &connector->modes, head) अणु
		mode_ok = hdmi_mode_valid(connector, m);

		अगर (mode_ok == MODE_OK) अणु
			DRM_INFO("desired mode doesn't exist so\n");
			DRM_INFO("use the most suitable mode among modes.\n");

			DRM_DEV_DEBUG_KMS(dev->dev,
					  "Adjusted Mode: [%d]x[%d] [%d]Hz\n",
					  m->hdisplay, m->vdisplay,
					  drm_mode_vrefresh(m));

			drm_mode_copy(adjusted_mode, m);
			अवरोध;
		पूर्ण
	पूर्ण

cleanup:
	drm_connector_put(connector);

	वापस true;
पूर्ण

अटल व्योम hdmi_reg_acr(काष्ठा hdmi_context *hdata, u32 freq)
अणु
	u32 n, cts;

	cts = (freq % 9) ? 27000 : 30000;
	n = 128 * freq / (27000000 / cts);

	hdmi_reg_ग_लिखोv(hdata, HDMI_ACR_N0, 3, n);
	hdmi_reg_ग_लिखोv(hdata, HDMI_ACR_MCTS0, 3, cts);
	hdmi_reg_ग_लिखोv(hdata, HDMI_ACR_CTS0, 3, cts);
	hdmi_reg_ग_लिखोb(hdata, HDMI_ACR_CON, 4);
पूर्ण

अटल व्योम hdmi_audio_config(काष्ठा hdmi_context *hdata)
अणु
	u32 bit_ch = 1;
	u32 data_num, val;
	पूर्णांक i;

	चयन (hdata->audio.params.sample_width) अणु
	हाल 20:
		data_num = 2;
		अवरोध;
	हाल 24:
		data_num = 3;
		अवरोध;
	शेष:
		data_num = 1;
		bit_ch = 0;
		अवरोध;
	पूर्ण

	hdmi_reg_acr(hdata, hdata->audio.params.sample_rate);

	hdmi_reg_ग_लिखोb(hdata, HDMI_I2S_MUX_CON, HDMI_I2S_IN_DISABLE
				| HDMI_I2S_AUD_I2S | HDMI_I2S_CUV_I2S_ENABLE
				| HDMI_I2S_MUX_ENABLE);

	hdmi_reg_ग_लिखोb(hdata, HDMI_I2S_MUX_CH, HDMI_I2S_CH0_EN
			| HDMI_I2S_CH1_EN | HDMI_I2S_CH2_EN);

	hdmi_reg_ग_लिखोb(hdata, HDMI_I2S_MUX_CUV, HDMI_I2S_CUV_RL_EN);
	hdmi_reg_ग_लिखोb(hdata, HDMI_I2S_CLK_CON, HDMI_I2S_CLK_DIS);
	hdmi_reg_ग_लिखोb(hdata, HDMI_I2S_CLK_CON, HDMI_I2S_CLK_EN);

	val = hdmi_reg_पढ़ो(hdata, HDMI_I2S_DSD_CON) | 0x01;
	hdmi_reg_ग_लिखोb(hdata, HDMI_I2S_DSD_CON, val);

	/* Configuration I2S input ports. Configure I2S_PIN_SEL_0~4 */
	hdmi_reg_ग_लिखोb(hdata, HDMI_I2S_PIN_SEL_0, HDMI_I2S_SEL_SCLK(5)
			| HDMI_I2S_SEL_LRCK(6));

	hdmi_reg_ग_लिखोb(hdata, HDMI_I2S_PIN_SEL_1, HDMI_I2S_SEL_SDATA1(3)
			| HDMI_I2S_SEL_SDATA0(4));

	hdmi_reg_ग_लिखोb(hdata, HDMI_I2S_PIN_SEL_2, HDMI_I2S_SEL_SDATA3(1)
			| HDMI_I2S_SEL_SDATA2(2));

	hdmi_reg_ग_लिखोb(hdata, HDMI_I2S_PIN_SEL_3, HDMI_I2S_SEL_DSD(0));

	/* I2S_CON_1 & 2 */
	hdmi_reg_ग_लिखोb(hdata, HDMI_I2S_CON_1, HDMI_I2S_SCLK_FALLING_EDGE
			| HDMI_I2S_L_CH_LOW_POL);
	hdmi_reg_ग_लिखोb(hdata, HDMI_I2S_CON_2, HDMI_I2S_MSB_FIRST_MODE
			| HDMI_I2S_SET_BIT_CH(bit_ch)
			| HDMI_I2S_SET_SDATA_BIT(data_num)
			| HDMI_I2S_BASIC_FORMAT);

	/* Configuration of the audio channel status रेजिस्टरs */
	क्रम (i = 0; i < HDMI_I2S_CH_ST_MAXNUM; i++)
		hdmi_reg_ग_लिखोb(hdata, HDMI_I2S_CH_ST(i),
				hdata->audio.params.iec.status[i]);

	hdmi_reg_ग_लिखोb(hdata, HDMI_I2S_CH_ST_CON, HDMI_I2S_CH_STATUS_RELOAD);
पूर्ण

अटल व्योम hdmi_audio_control(काष्ठा hdmi_context *hdata)
अणु
	bool enable = !hdata->audio.mute;

	अगर (hdata->dvi_mode)
		वापस;

	hdmi_reg_ग_लिखोb(hdata, HDMI_AUI_CON, enable ?
			HDMI_AVI_CON_EVERY_VSYNC : HDMI_AUI_CON_NO_TRAN);
	hdmi_reg_ग_लिखोmask(hdata, HDMI_CON_0, enable ?
			HDMI_ASP_EN : HDMI_ASP_DIS, HDMI_ASP_MASK);
पूर्ण

अटल व्योम hdmi_start(काष्ठा hdmi_context *hdata, bool start)
अणु
	काष्ठा drm_display_mode *m = &hdata->encoder.crtc->state->mode;
	u32 val = start ? HDMI_TG_EN : 0;

	अगर (m->flags & DRM_MODE_FLAG_INTERLACE)
		val |= HDMI_FIELD_EN;

	hdmi_reg_ग_लिखोmask(hdata, HDMI_CON_0, val, HDMI_EN);
	hdmi_reg_ग_लिखोmask(hdata, HDMI_TG_CMD, val, HDMI_TG_EN | HDMI_FIELD_EN);
पूर्ण

अटल व्योम hdmi_conf_init(काष्ठा hdmi_context *hdata)
अणु
	/* disable HPD पूर्णांकerrupts from HDMI IP block, use GPIO instead */
	hdmi_reg_ग_लिखोmask(hdata, HDMI_INTC_CON, 0, HDMI_INTC_EN_GLOBAL |
		HDMI_INTC_EN_HPD_PLUG | HDMI_INTC_EN_HPD_UNPLUG);

	/* choose HDMI mode */
	hdmi_reg_ग_लिखोmask(hdata, HDMI_MODE_SEL,
		HDMI_MODE_HDMI_EN, HDMI_MODE_MASK);
	/* apply video pre-amble and guard band in HDMI mode only */
	hdmi_reg_ग_लिखोb(hdata, HDMI_CON_2, 0);
	/* disable bluescreen */
	hdmi_reg_ग_लिखोmask(hdata, HDMI_CON_0, 0, HDMI_BLUE_SCR_EN);

	अगर (hdata->dvi_mode) अणु
		hdmi_reg_ग_लिखोmask(hdata, HDMI_MODE_SEL,
				HDMI_MODE_DVI_EN, HDMI_MODE_MASK);
		hdmi_reg_ग_लिखोb(hdata, HDMI_CON_2,
				HDMI_VID_PREAMBLE_DIS | HDMI_GUARD_BAND_DIS);
	पूर्ण

	अगर (hdata->drv_data->type == HDMI_TYPE13) अणु
		/* choose bluescreen (fecal) color */
		hdmi_reg_ग_लिखोb(hdata, HDMI_V13_BLUE_SCREEN_0, 0x12);
		hdmi_reg_ग_लिखोb(hdata, HDMI_V13_BLUE_SCREEN_1, 0x34);
		hdmi_reg_ग_लिखोb(hdata, HDMI_V13_BLUE_SCREEN_2, 0x56);

		/* enable AVI packet every vsync, fixes purple line problem */
		hdmi_reg_ग_लिखोb(hdata, HDMI_V13_AVI_CON, 0x02);
		/* क्रमce RGB, look to CEA-861-D, table 7 क्रम more detail */
		hdmi_reg_ग_लिखोb(hdata, HDMI_V13_AVI_BYTE(0), 0 << 5);
		hdmi_reg_ग_लिखोmask(hdata, HDMI_CON_1, 0x10 << 5, 0x11 << 5);

		hdmi_reg_ग_लिखोb(hdata, HDMI_V13_SPD_CON, 0x02);
		hdmi_reg_ग_लिखोb(hdata, HDMI_V13_AUI_CON, 0x02);
		hdmi_reg_ग_लिखोb(hdata, HDMI_V13_ACR_CON, 0x04);
	पूर्ण अन्यथा अणु
		hdmi_reg_infoframes(hdata);

		/* enable AVI packet every vsync, fixes purple line problem */
		hdmi_reg_ग_लिखोmask(hdata, HDMI_CON_1, 2, 3 << 5);
	पूर्ण
पूर्ण

अटल व्योम hdmiphy_रुको_क्रम_pll(काष्ठा hdmi_context *hdata)
अणु
	पूर्णांक tries;

	क्रम (tries = 0; tries < 10; ++tries) अणु
		u32 val = hdmi_reg_पढ़ो(hdata, HDMI_PHY_STATUS);

		अगर (val & HDMI_PHY_STATUS_READY) अणु
			DRM_DEV_DEBUG_KMS(hdata->dev,
					  "PLL stabilized after %d tries\n",
					  tries);
			वापस;
		पूर्ण
		usleep_range(10, 20);
	पूर्ण

	DRM_DEV_ERROR(hdata->dev, "PLL could not reach steady state\n");
पूर्ण

अटल व्योम hdmi_v13_mode_apply(काष्ठा hdmi_context *hdata)
अणु
	काष्ठा drm_display_mode *m = &hdata->encoder.crtc->state->mode;
	अचिन्हित पूर्णांक val;

	hdmi_reg_ग_लिखोv(hdata, HDMI_H_BLANK_0, 2, m->htotal - m->hdisplay);
	hdmi_reg_ग_लिखोv(hdata, HDMI_V13_H_V_LINE_0, 3,
			(m->htotal << 12) | m->vtotal);

	val = (m->flags & DRM_MODE_FLAG_NVSYNC) ? 1 : 0;
	hdmi_reg_ग_लिखोv(hdata, HDMI_VSYNC_POL, 1, val);

	val = (m->flags & DRM_MODE_FLAG_INTERLACE) ? 1 : 0;
	hdmi_reg_ग_लिखोv(hdata, HDMI_INT_PRO_MODE, 1, val);

	val = (m->hsync_start - m->hdisplay - 2);
	val |= ((m->hsync_end - m->hdisplay - 2) << 10);
	val |= ((m->flags & DRM_MODE_FLAG_NHSYNC) ? 1 : 0)<<20;
	hdmi_reg_ग_लिखोv(hdata, HDMI_V13_H_SYNC_GEN_0, 3, val);

	/*
	 * Quirk requirement क्रम exynos HDMI IP design,
	 * 2 pixels less than the actual calculation क्रम hsync_start
	 * and end.
	 */

	/* Following values & calculations dअगरfer क्रम dअगरferent type of modes */
	अगर (m->flags & DRM_MODE_FLAG_INTERLACE) अणु
		val = ((m->vsync_end - m->vdisplay) / 2);
		val |= ((m->vsync_start - m->vdisplay) / 2) << 12;
		hdmi_reg_ग_लिखोv(hdata, HDMI_V13_V_SYNC_GEN_1_0, 3, val);

		val = m->vtotal / 2;
		val |= ((m->vtotal - m->vdisplay) / 2) << 11;
		hdmi_reg_ग_लिखोv(hdata, HDMI_V13_V_BLANK_0, 3, val);

		val = (m->vtotal +
			((m->vsync_end - m->vsync_start) * 4) + 5) / 2;
		val |= m->vtotal << 11;
		hdmi_reg_ग_लिखोv(hdata, HDMI_V13_V_BLANK_F_0, 3, val);

		val = ((m->vtotal / 2) + 7);
		val |= ((m->vtotal / 2) + 2) << 12;
		hdmi_reg_ग_लिखोv(hdata, HDMI_V13_V_SYNC_GEN_2_0, 3, val);

		val = ((m->htotal / 2) + (m->hsync_start - m->hdisplay));
		val |= ((m->htotal / 2) +
			(m->hsync_start - m->hdisplay)) << 12;
		hdmi_reg_ग_लिखोv(hdata, HDMI_V13_V_SYNC_GEN_3_0, 3, val);

		hdmi_reg_ग_लिखोv(hdata, HDMI_TG_VACT_ST_L, 2,
				(m->vtotal - m->vdisplay) / 2);
		hdmi_reg_ग_लिखोv(hdata, HDMI_TG_VACT_SZ_L, 2, m->vdisplay / 2);

		hdmi_reg_ग_लिखोv(hdata, HDMI_TG_VACT_ST2_L, 2, 0x249);
	पूर्ण अन्यथा अणु
		val = m->vtotal;
		val |= (m->vtotal - m->vdisplay) << 11;
		hdmi_reg_ग_लिखोv(hdata, HDMI_V13_V_BLANK_0, 3, val);

		hdmi_reg_ग_लिखोv(hdata, HDMI_V13_V_BLANK_F_0, 3, 0);

		val = (m->vsync_end - m->vdisplay);
		val |= ((m->vsync_start - m->vdisplay) << 12);
		hdmi_reg_ग_लिखोv(hdata, HDMI_V13_V_SYNC_GEN_1_0, 3, val);

		hdmi_reg_ग_लिखोv(hdata, HDMI_V13_V_SYNC_GEN_2_0, 3, 0x1001);
		hdmi_reg_ग_लिखोv(hdata, HDMI_V13_V_SYNC_GEN_3_0, 3, 0x1001);
		hdmi_reg_ग_लिखोv(hdata, HDMI_TG_VACT_ST_L, 2,
				m->vtotal - m->vdisplay);
		hdmi_reg_ग_लिखोv(hdata, HDMI_TG_VACT_SZ_L, 2, m->vdisplay);
	पूर्ण

	hdmi_reg_ग_लिखोv(hdata, HDMI_TG_H_FSZ_L, 2, m->htotal);
	hdmi_reg_ग_लिखोv(hdata, HDMI_TG_HACT_ST_L, 2, m->htotal - m->hdisplay);
	hdmi_reg_ग_लिखोv(hdata, HDMI_TG_HACT_SZ_L, 2, m->hdisplay);
	hdmi_reg_ग_लिखोv(hdata, HDMI_TG_V_FSZ_L, 2, m->vtotal);
पूर्ण

अटल व्योम hdmi_v14_mode_apply(काष्ठा hdmi_context *hdata)
अणु
	काष्ठा drm_display_mode *m = &hdata->encoder.crtc->state->mode;
	काष्ठा drm_display_mode *am =
				&hdata->encoder.crtc->state->adjusted_mode;
	पूर्णांक hquirk = 0;

	/*
	 * In हाल video mode coming from CRTC dअगरfers from requested one HDMI
	 * someबार is able to almost properly perक्रमm conversion - only
	 * first line is distorted.
	 */
	अगर ((m->vdisplay != am->vdisplay) &&
	    (m->hdisplay == 1280 || m->hdisplay == 1024 || m->hdisplay == 1366))
		hquirk = 258;

	hdmi_reg_ग_लिखोv(hdata, HDMI_H_BLANK_0, 2, m->htotal - m->hdisplay);
	hdmi_reg_ग_लिखोv(hdata, HDMI_V_LINE_0, 2, m->vtotal);
	hdmi_reg_ग_लिखोv(hdata, HDMI_H_LINE_0, 2, m->htotal);
	hdmi_reg_ग_लिखोv(hdata, HDMI_HSYNC_POL, 1,
			(m->flags & DRM_MODE_FLAG_NHSYNC) ? 1 : 0);
	hdmi_reg_ग_लिखोv(hdata, HDMI_VSYNC_POL, 1,
			(m->flags & DRM_MODE_FLAG_NVSYNC) ? 1 : 0);
	hdmi_reg_ग_लिखोv(hdata, HDMI_INT_PRO_MODE, 1,
			(m->flags & DRM_MODE_FLAG_INTERLACE) ? 1 : 0);

	/*
	 * Quirk requirement क्रम exynos 5 HDMI IP design,
	 * 2 pixels less than the actual calculation क्रम hsync_start
	 * and end.
	 */

	/* Following values & calculations dअगरfer क्रम dअगरferent type of modes */
	अगर (m->flags & DRM_MODE_FLAG_INTERLACE) अणु
		hdmi_reg_ग_लिखोv(hdata, HDMI_V_SYNC_LINE_BEF_2_0, 2,
			(m->vsync_end - m->vdisplay) / 2);
		hdmi_reg_ग_लिखोv(hdata, HDMI_V_SYNC_LINE_BEF_1_0, 2,
			(m->vsync_start - m->vdisplay) / 2);
		hdmi_reg_ग_लिखोv(hdata, HDMI_V2_BLANK_0, 2, m->vtotal / 2);
		hdmi_reg_ग_लिखोv(hdata, HDMI_V1_BLANK_0, 2,
				(m->vtotal - m->vdisplay) / 2);
		hdmi_reg_ग_लिखोv(hdata, HDMI_V_BLANK_F0_0, 2,
				m->vtotal - m->vdisplay / 2);
		hdmi_reg_ग_लिखोv(hdata, HDMI_V_BLANK_F1_0, 2, m->vtotal);
		hdmi_reg_ग_लिखोv(hdata, HDMI_V_SYNC_LINE_AFT_2_0, 2,
				(m->vtotal / 2) + 7);
		hdmi_reg_ग_लिखोv(hdata, HDMI_V_SYNC_LINE_AFT_1_0, 2,
				(m->vtotal / 2) + 2);
		hdmi_reg_ग_लिखोv(hdata, HDMI_V_SYNC_LINE_AFT_PXL_2_0, 2,
			(m->htotal / 2) + (m->hsync_start - m->hdisplay));
		hdmi_reg_ग_लिखोv(hdata, HDMI_V_SYNC_LINE_AFT_PXL_1_0, 2,
			(m->htotal / 2) + (m->hsync_start - m->hdisplay));
		hdmi_reg_ग_लिखोv(hdata, HDMI_TG_VACT_ST_L, 2,
				(m->vtotal - m->vdisplay) / 2);
		hdmi_reg_ग_लिखोv(hdata, HDMI_TG_VACT_SZ_L, 2, m->vdisplay / 2);
		hdmi_reg_ग_लिखोv(hdata, HDMI_TG_VACT_ST2_L, 2,
				m->vtotal - m->vdisplay / 2);
		hdmi_reg_ग_लिखोv(hdata, HDMI_TG_VSYNC2_L, 2,
				(m->vtotal / 2) + 1);
		hdmi_reg_ग_लिखोv(hdata, HDMI_TG_VSYNC_BOT_HDMI_L, 2,
				(m->vtotal / 2) + 1);
		hdmi_reg_ग_लिखोv(hdata, HDMI_TG_FIELD_BOT_HDMI_L, 2,
				(m->vtotal / 2) + 1);
		hdmi_reg_ग_लिखोv(hdata, HDMI_TG_VACT_ST3_L, 2, 0x0);
		hdmi_reg_ग_लिखोv(hdata, HDMI_TG_VACT_ST4_L, 2, 0x0);
	पूर्ण अन्यथा अणु
		hdmi_reg_ग_लिखोv(hdata, HDMI_V_SYNC_LINE_BEF_2_0, 2,
			m->vsync_end - m->vdisplay);
		hdmi_reg_ग_लिखोv(hdata, HDMI_V_SYNC_LINE_BEF_1_0, 2,
			m->vsync_start - m->vdisplay);
		hdmi_reg_ग_लिखोv(hdata, HDMI_V2_BLANK_0, 2, m->vtotal);
		hdmi_reg_ग_लिखोv(hdata, HDMI_V1_BLANK_0, 2,
				m->vtotal - m->vdisplay);
		hdmi_reg_ग_लिखोv(hdata, HDMI_V_BLANK_F0_0, 2, 0xffff);
		hdmi_reg_ग_लिखोv(hdata, HDMI_V_BLANK_F1_0, 2, 0xffff);
		hdmi_reg_ग_लिखोv(hdata, HDMI_V_SYNC_LINE_AFT_2_0, 2, 0xffff);
		hdmi_reg_ग_लिखोv(hdata, HDMI_V_SYNC_LINE_AFT_1_0, 2, 0xffff);
		hdmi_reg_ग_लिखोv(hdata, HDMI_V_SYNC_LINE_AFT_PXL_2_0, 2, 0xffff);
		hdmi_reg_ग_लिखोv(hdata, HDMI_V_SYNC_LINE_AFT_PXL_1_0, 2, 0xffff);
		hdmi_reg_ग_लिखोv(hdata, HDMI_TG_VACT_ST_L, 2,
				m->vtotal - m->vdisplay);
		hdmi_reg_ग_लिखोv(hdata, HDMI_TG_VACT_SZ_L, 2, m->vdisplay);
	पूर्ण

	hdmi_reg_ग_लिखोv(hdata, HDMI_H_SYNC_START_0, 2,
			m->hsync_start - m->hdisplay - 2);
	hdmi_reg_ग_लिखोv(hdata, HDMI_H_SYNC_END_0, 2,
			m->hsync_end - m->hdisplay - 2);
	hdmi_reg_ग_लिखोv(hdata, HDMI_VACT_SPACE_1_0, 2, 0xffff);
	hdmi_reg_ग_लिखोv(hdata, HDMI_VACT_SPACE_2_0, 2, 0xffff);
	hdmi_reg_ग_लिखोv(hdata, HDMI_VACT_SPACE_3_0, 2, 0xffff);
	hdmi_reg_ग_लिखोv(hdata, HDMI_VACT_SPACE_4_0, 2, 0xffff);
	hdmi_reg_ग_लिखोv(hdata, HDMI_VACT_SPACE_5_0, 2, 0xffff);
	hdmi_reg_ग_लिखोv(hdata, HDMI_VACT_SPACE_6_0, 2, 0xffff);
	hdmi_reg_ग_लिखोv(hdata, HDMI_V_BLANK_F2_0, 2, 0xffff);
	hdmi_reg_ग_लिखोv(hdata, HDMI_V_BLANK_F3_0, 2, 0xffff);
	hdmi_reg_ग_लिखोv(hdata, HDMI_V_BLANK_F4_0, 2, 0xffff);
	hdmi_reg_ग_लिखोv(hdata, HDMI_V_BLANK_F5_0, 2, 0xffff);
	hdmi_reg_ग_लिखोv(hdata, HDMI_V_SYNC_LINE_AFT_3_0, 2, 0xffff);
	hdmi_reg_ग_लिखोv(hdata, HDMI_V_SYNC_LINE_AFT_4_0, 2, 0xffff);
	hdmi_reg_ग_लिखोv(hdata, HDMI_V_SYNC_LINE_AFT_5_0, 2, 0xffff);
	hdmi_reg_ग_लिखोv(hdata, HDMI_V_SYNC_LINE_AFT_6_0, 2, 0xffff);
	hdmi_reg_ग_लिखोv(hdata, HDMI_V_SYNC_LINE_AFT_PXL_3_0, 2, 0xffff);
	hdmi_reg_ग_लिखोv(hdata, HDMI_V_SYNC_LINE_AFT_PXL_4_0, 2, 0xffff);
	hdmi_reg_ग_लिखोv(hdata, HDMI_V_SYNC_LINE_AFT_PXL_5_0, 2, 0xffff);
	hdmi_reg_ग_लिखोv(hdata, HDMI_V_SYNC_LINE_AFT_PXL_6_0, 2, 0xffff);

	hdmi_reg_ग_लिखोv(hdata, HDMI_TG_H_FSZ_L, 2, m->htotal);
	hdmi_reg_ग_लिखोv(hdata, HDMI_TG_HACT_ST_L, 2,
					m->htotal - m->hdisplay - hquirk);
	hdmi_reg_ग_लिखोv(hdata, HDMI_TG_HACT_SZ_L, 2, m->hdisplay + hquirk);
	hdmi_reg_ग_लिखोv(hdata, HDMI_TG_V_FSZ_L, 2, m->vtotal);
	अगर (hdata->drv_data == &exynos5433_hdmi_driver_data)
		hdmi_reg_ग_लिखोb(hdata, HDMI_TG_DECON_EN, 1);
पूर्ण

अटल व्योम hdmi_mode_apply(काष्ठा hdmi_context *hdata)
अणु
	अगर (hdata->drv_data->type == HDMI_TYPE13)
		hdmi_v13_mode_apply(hdata);
	अन्यथा
		hdmi_v14_mode_apply(hdata);

	hdmi_start(hdata, true);
पूर्ण

अटल व्योम hdmiphy_conf_reset(काष्ठा hdmi_context *hdata)
अणु
	hdmi_reg_ग_लिखोmask(hdata, HDMI_CORE_RSTOUT, 0, 1);
	usleep_range(10000, 12000);
	hdmi_reg_ग_लिखोmask(hdata, HDMI_CORE_RSTOUT, ~0, 1);
	usleep_range(10000, 12000);
	hdmi_reg_ग_लिखोmask(hdata, HDMI_PHY_RSTOUT, ~0, HDMI_PHY_SW_RSTOUT);
	usleep_range(10000, 12000);
	hdmi_reg_ग_लिखोmask(hdata, HDMI_PHY_RSTOUT, 0, HDMI_PHY_SW_RSTOUT);
	usleep_range(10000, 12000);
पूर्ण

अटल व्योम hdmiphy_enable_mode_set(काष्ठा hdmi_context *hdata, bool enable)
अणु
	u8 v = enable ? HDMI_PHY_ENABLE_MODE_SET : HDMI_PHY_DISABLE_MODE_SET;

	अगर (hdata->drv_data == &exynos5433_hdmi_driver_data)
		ग_लिखोl(v, hdata->regs_hdmiphy + HDMIPHY5433_MODE_SET_DONE);
पूर्ण

अटल व्योम hdmiphy_conf_apply(काष्ठा hdmi_context *hdata)
अणु
	काष्ठा drm_display_mode *m = &hdata->encoder.crtc->state->mode;
	पूर्णांक ret;
	स्थिर u8 *phy_conf;

	ret = hdmi_find_phy_conf(hdata, m->घड़ी * 1000);
	अगर (ret < 0) अणु
		DRM_DEV_ERROR(hdata->dev, "failed to find hdmiphy conf\n");
		वापस;
	पूर्ण
	phy_conf = hdata->drv_data->phy_confs.data[ret].conf;

	hdmi_clk_set_parents(hdata, false);

	hdmiphy_conf_reset(hdata);

	hdmiphy_enable_mode_set(hdata, true);
	ret = hdmiphy_reg_ग_लिखो_buf(hdata, 0, phy_conf, 32);
	अगर (ret) अणु
		DRM_DEV_ERROR(hdata->dev, "failed to configure hdmiphy\n");
		वापस;
	पूर्ण
	hdmiphy_enable_mode_set(hdata, false);
	hdmi_clk_set_parents(hdata, true);
	usleep_range(10000, 12000);
	hdmiphy_रुको_क्रम_pll(hdata);
पूर्ण

/* Should be called with hdata->mutex mutex held */
अटल व्योम hdmi_conf_apply(काष्ठा hdmi_context *hdata)
अणु
	hdmi_start(hdata, false);
	hdmi_conf_init(hdata);
	hdmi_audio_config(hdata);
	hdmi_mode_apply(hdata);
	hdmi_audio_control(hdata);
पूर्ण

अटल व्योम hdmi_set_refclk(काष्ठा hdmi_context *hdata, bool on)
अणु
	अगर (!hdata->sysreg)
		वापस;

	regmap_update_bits(hdata->sysreg, EXYNOS5433_SYSREG_DISP_HDMI_PHY,
			   SYSREG_HDMI_REFCLK_INT_CLK, on ? ~0 : 0);
पूर्ण

/* Should be called with hdata->mutex mutex held. */
अटल व्योम hdmiphy_enable(काष्ठा hdmi_context *hdata)
अणु
	अगर (hdata->घातered)
		वापस;

	pm_runसमय_get_sync(hdata->dev);

	अगर (regulator_bulk_enable(ARRAY_SIZE(supply), hdata->regul_bulk))
		DRM_DEV_DEBUG_KMS(hdata->dev,
				  "failed to enable regulator bulk\n");

	regmap_update_bits(hdata->pmureg, PMU_HDMI_PHY_CONTROL,
			PMU_HDMI_PHY_ENABLE_BIT, 1);

	hdmi_set_refclk(hdata, true);

	hdmi_reg_ग_लिखोmask(hdata, HDMI_PHY_CON_0, 0, HDMI_PHY_POWER_OFF_EN);

	hdmiphy_conf_apply(hdata);

	hdata->घातered = true;
पूर्ण

/* Should be called with hdata->mutex mutex held. */
अटल व्योम hdmiphy_disable(काष्ठा hdmi_context *hdata)
अणु
	अगर (!hdata->घातered)
		वापस;

	hdmi_reg_ग_लिखोmask(hdata, HDMI_CON_0, 0, HDMI_EN);

	hdmi_reg_ग_लिखोmask(hdata, HDMI_PHY_CON_0, ~0, HDMI_PHY_POWER_OFF_EN);

	hdmi_set_refclk(hdata, false);

	regmap_update_bits(hdata->pmureg, PMU_HDMI_PHY_CONTROL,
			PMU_HDMI_PHY_ENABLE_BIT, 0);

	regulator_bulk_disable(ARRAY_SIZE(supply), hdata->regul_bulk);

	pm_runसमय_put_sync(hdata->dev);

	hdata->घातered = false;
पूर्ण

अटल व्योम hdmi_enable(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा hdmi_context *hdata = encoder_to_hdmi(encoder);

	mutex_lock(&hdata->mutex);

	hdmiphy_enable(hdata);
	hdmi_conf_apply(hdata);

	mutex_unlock(&hdata->mutex);
पूर्ण

अटल व्योम hdmi_disable(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा hdmi_context *hdata = encoder_to_hdmi(encoder);

	mutex_lock(&hdata->mutex);

	अगर (hdata->घातered) अणु
		/*
		 * The SFRs of VP and Mixer are updated by Vertical Sync of
		 * Timing generator which is a part of HDMI so the sequence
		 * to disable TV Subप्रणाली should be as following,
		 *	VP -> Mixer -> HDMI
		 *
		 * To achieve such sequence HDMI is disabled together with
		 * HDMI PHY, via pipe घड़ी callback.
		 */
		mutex_unlock(&hdata->mutex);
		cancel_delayed_work(&hdata->hotplug_work);
		अगर (hdata->notअगरier)
			cec_notअगरier_phys_addr_invalidate(hdata->notअगरier);
		वापस;
	पूर्ण

	mutex_unlock(&hdata->mutex);
पूर्ण

अटल स्थिर काष्ठा drm_encoder_helper_funcs exynos_hdmi_encoder_helper_funcs = अणु
	.mode_fixup	= hdmi_mode_fixup,
	.enable		= hdmi_enable,
	.disable	= hdmi_disable,
पूर्ण;

अटल व्योम hdmi_audio_shutकरोwn(काष्ठा device *dev, व्योम *data)
अणु
	काष्ठा hdmi_context *hdata = dev_get_drvdata(dev);

	mutex_lock(&hdata->mutex);

	hdata->audio.mute = true;

	अगर (hdata->घातered)
		hdmi_audio_control(hdata);

	mutex_unlock(&hdata->mutex);
पूर्ण

अटल पूर्णांक hdmi_audio_hw_params(काष्ठा device *dev, व्योम *data,
				काष्ठा hdmi_codec_daअगरmt *daअगरmt,
				काष्ठा hdmi_codec_params *params)
अणु
	काष्ठा hdmi_context *hdata = dev_get_drvdata(dev);

	अगर (daअगरmt->fmt != HDMI_I2S || daअगरmt->bit_clk_inv ||
	    daअगरmt->frame_clk_inv || daअगरmt->bit_clk_master ||
	    daअगरmt->frame_clk_master) अणु
		dev_err(dev, "%s: Bad flags %d %d %d %d\n", __func__,
			daअगरmt->bit_clk_inv, daअगरmt->frame_clk_inv,
			daअगरmt->bit_clk_master,
			daअगरmt->frame_clk_master);
		वापस -EINVAL;
	पूर्ण

	mutex_lock(&hdata->mutex);

	hdata->audio.params = *params;

	अगर (hdata->घातered) अणु
		hdmi_audio_config(hdata);
		hdmi_audio_infoframe_apply(hdata);
	पूर्ण

	mutex_unlock(&hdata->mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक hdmi_audio_mute(काष्ठा device *dev, व्योम *data,
			   bool mute, पूर्णांक direction)
अणु
	काष्ठा hdmi_context *hdata = dev_get_drvdata(dev);

	mutex_lock(&hdata->mutex);

	hdata->audio.mute = mute;

	अगर (hdata->घातered)
		hdmi_audio_control(hdata);

	mutex_unlock(&hdata->mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक hdmi_audio_get_eld(काष्ठा device *dev, व्योम *data, uपूर्णांक8_t *buf,
			      माप_प्रकार len)
अणु
	काष्ठा hdmi_context *hdata = dev_get_drvdata(dev);
	काष्ठा drm_connector *connector = &hdata->connector;

	स_नकल(buf, connector->eld, min(माप(connector->eld), len));

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा hdmi_codec_ops audio_codec_ops = अणु
	.hw_params = hdmi_audio_hw_params,
	.audio_shutकरोwn = hdmi_audio_shutकरोwn,
	.mute_stream = hdmi_audio_mute,
	.get_eld = hdmi_audio_get_eld,
	.no_capture_mute = 1,
पूर्ण;

अटल पूर्णांक hdmi_रेजिस्टर_audio_device(काष्ठा hdmi_context *hdata)
अणु
	काष्ठा hdmi_codec_pdata codec_data = अणु
		.ops = &audio_codec_ops,
		.max_i2s_channels = 6,
		.i2s = 1,
	पूर्ण;

	hdata->audio.pdev = platक्रमm_device_रेजिस्टर_data(
		hdata->dev, HDMI_CODEC_DRV_NAME, PLATFORM_DEVID_AUTO,
		&codec_data, माप(codec_data));

	वापस PTR_ERR_OR_ZERO(hdata->audio.pdev);
पूर्ण

अटल व्योम hdmi_hotplug_work_func(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा hdmi_context *hdata;

	hdata = container_of(work, काष्ठा hdmi_context, hotplug_work.work);

	अगर (hdata->drm_dev)
		drm_helper_hpd_irq_event(hdata->drm_dev);
पूर्ण

अटल irqवापस_t hdmi_irq_thपढ़ो(पूर्णांक irq, व्योम *arg)
अणु
	काष्ठा hdmi_context *hdata = arg;

	mod_delayed_work(प्रणाली_wq, &hdata->hotplug_work,
			msecs_to_jअगरfies(HOTPLUG_DEBOUNCE_MS));

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक hdmi_clks_get(काष्ठा hdmi_context *hdata,
			 स्थिर काष्ठा string_array_spec *names,
			 काष्ठा clk **clks)
अणु
	काष्ठा device *dev = hdata->dev;
	पूर्णांक i;

	क्रम (i = 0; i < names->count; ++i) अणु
		काष्ठा clk *clk = devm_clk_get(dev, names->data[i]);

		अगर (IS_ERR(clk)) अणु
			पूर्णांक ret = PTR_ERR(clk);

			dev_err(dev, "Cannot get clock %s, %d\n",
				names->data[i], ret);

			वापस ret;
		पूर्ण

		clks[i] = clk;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक hdmi_clk_init(काष्ठा hdmi_context *hdata)
अणु
	स्थिर काष्ठा hdmi_driver_data *drv_data = hdata->drv_data;
	पूर्णांक count = drv_data->clk_gates.count + drv_data->clk_muxes.count;
	काष्ठा device *dev = hdata->dev;
	काष्ठा clk **clks;
	पूर्णांक ret;

	अगर (!count)
		वापस 0;

	clks = devm_kसुस्मृति(dev, count, माप(*clks), GFP_KERNEL);
	अगर (!clks)
		वापस -ENOMEM;

	hdata->clk_gates = clks;
	hdata->clk_muxes = clks + drv_data->clk_gates.count;

	ret = hdmi_clks_get(hdata, &drv_data->clk_gates, hdata->clk_gates);
	अगर (ret)
		वापस ret;

	वापस hdmi_clks_get(hdata, &drv_data->clk_muxes, hdata->clk_muxes);
पूर्ण


अटल व्योम hdmiphy_clk_enable(काष्ठा exynos_drm_clk *clk, bool enable)
अणु
	काष्ठा hdmi_context *hdata = container_of(clk, काष्ठा hdmi_context,
						  phy_clk);
	mutex_lock(&hdata->mutex);

	अगर (enable)
		hdmiphy_enable(hdata);
	अन्यथा
		hdmiphy_disable(hdata);

	mutex_unlock(&hdata->mutex);
पूर्ण

अटल पूर्णांक hdmi_bridge_init(काष्ठा hdmi_context *hdata)
अणु
	काष्ठा device *dev = hdata->dev;
	काष्ठा device_node *ep, *np;

	ep = of_graph_get_endpoपूर्णांक_by_regs(dev->of_node, 1, -1);
	अगर (!ep)
		वापस 0;

	np = of_graph_get_remote_port_parent(ep);
	of_node_put(ep);
	अगर (!np) अणु
		DRM_DEV_ERROR(dev, "failed to get remote port parent");
		वापस -EINVAL;
	पूर्ण

	hdata->bridge = of_drm_find_bridge(np);
	of_node_put(np);

	अगर (!hdata->bridge)
		वापस -EPROBE_DEFER;

	वापस 0;
पूर्ण

अटल पूर्णांक hdmi_resources_init(काष्ठा hdmi_context *hdata)
अणु
	काष्ठा device *dev = hdata->dev;
	पूर्णांक i, ret;

	DRM_DEV_DEBUG_KMS(dev, "HDMI resource init\n");

	hdata->hpd_gpio = devm_gpiod_get(dev, "hpd", GPIOD_IN);
	अगर (IS_ERR(hdata->hpd_gpio)) अणु
		DRM_DEV_ERROR(dev, "cannot get hpd gpio property\n");
		वापस PTR_ERR(hdata->hpd_gpio);
	पूर्ण

	hdata->irq = gpiod_to_irq(hdata->hpd_gpio);
	अगर (hdata->irq < 0) अणु
		DRM_DEV_ERROR(dev, "failed to get GPIO irq\n");
		वापस  hdata->irq;
	पूर्ण

	ret = hdmi_clk_init(hdata);
	अगर (ret)
		वापस ret;

	ret = hdmi_clk_set_parents(hdata, false);
	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < ARRAY_SIZE(supply); ++i)
		hdata->regul_bulk[i].supply = supply[i];

	ret = devm_regulator_bulk_get(dev, ARRAY_SIZE(supply), hdata->regul_bulk);
	अगर (ret)
		वापस dev_err_probe(dev, ret, "failed to get regulators\n");

	hdata->reg_hdmi_en = devm_regulator_get_optional(dev, "hdmi-en");

	अगर (PTR_ERR(hdata->reg_hdmi_en) != -ENODEV)
		अगर (IS_ERR(hdata->reg_hdmi_en))
			वापस PTR_ERR(hdata->reg_hdmi_en);

	वापस hdmi_bridge_init(hdata);
पूर्ण

अटल स्थिर काष्ठा of_device_id hdmi_match_types[] = अणु
	अणु
		.compatible = "samsung,exynos4210-hdmi",
		.data = &exynos4210_hdmi_driver_data,
	पूर्ण, अणु
		.compatible = "samsung,exynos4212-hdmi",
		.data = &exynos4212_hdmi_driver_data,
	पूर्ण, अणु
		.compatible = "samsung,exynos5420-hdmi",
		.data = &exynos5420_hdmi_driver_data,
	पूर्ण, अणु
		.compatible = "samsung,exynos5433-hdmi",
		.data = &exynos5433_hdmi_driver_data,
	पूर्ण, अणु
		/* end node */
	पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE (of, hdmi_match_types);

अटल पूर्णांक hdmi_bind(काष्ठा device *dev, काष्ठा device *master, व्योम *data)
अणु
	काष्ठा drm_device *drm_dev = data;
	काष्ठा hdmi_context *hdata = dev_get_drvdata(dev);
	काष्ठा drm_encoder *encoder = &hdata->encoder;
	काष्ठा exynos_drm_crtc *crtc;
	पूर्णांक ret;

	hdata->drm_dev = drm_dev;

	hdata->phy_clk.enable = hdmiphy_clk_enable;

	drm_simple_encoder_init(drm_dev, encoder, DRM_MODE_ENCODER_TMDS);

	drm_encoder_helper_add(encoder, &exynos_hdmi_encoder_helper_funcs);

	ret = exynos_drm_set_possible_crtcs(encoder, EXYNOS_DISPLAY_TYPE_HDMI);
	अगर (ret < 0)
		वापस ret;

	crtc = exynos_drm_crtc_get_by_type(drm_dev, EXYNOS_DISPLAY_TYPE_HDMI);
	crtc->pipe_clk = &hdata->phy_clk;

	ret = hdmi_create_connector(encoder);
	अगर (ret) अणु
		DRM_DEV_ERROR(dev, "failed to create connector ret = %d\n",
			      ret);
		drm_encoder_cleanup(encoder);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम hdmi_unbind(काष्ठा device *dev, काष्ठा device *master, व्योम *data)
अणु
पूर्ण

अटल स्थिर काष्ठा component_ops hdmi_component_ops = अणु
	.bind	= hdmi_bind,
	.unbind = hdmi_unbind,
पूर्ण;

अटल पूर्णांक hdmi_get_ddc_adapter(काष्ठा hdmi_context *hdata)
अणु
	स्थिर अक्षर *compatible_str = "samsung,exynos4210-hdmiddc";
	काष्ठा device_node *np;
	काष्ठा i2c_adapter *adpt;

	np = of_find_compatible_node(शून्य, शून्य, compatible_str);
	अगर (np)
		np = of_get_next_parent(np);
	अन्यथा
		np = of_parse_phandle(hdata->dev->of_node, "ddc", 0);

	अगर (!np) अणु
		DRM_DEV_ERROR(hdata->dev,
			      "Failed to find ddc node in device tree\n");
		वापस -ENODEV;
	पूर्ण

	adpt = of_find_i2c_adapter_by_node(np);
	of_node_put(np);

	अगर (!adpt) अणु
		DRM_INFO("Failed to get ddc i2c adapter by node\n");
		वापस -EPROBE_DEFER;
	पूर्ण

	hdata->ddc_adpt = adpt;

	वापस 0;
पूर्ण

अटल पूर्णांक hdmi_get_phy_io(काष्ठा hdmi_context *hdata)
अणु
	स्थिर अक्षर *compatible_str = "samsung,exynos4212-hdmiphy";
	काष्ठा device_node *np;
	पूर्णांक ret = 0;

	np = of_find_compatible_node(शून्य, शून्य, compatible_str);
	अगर (!np) अणु
		np = of_parse_phandle(hdata->dev->of_node, "phy", 0);
		अगर (!np) अणु
			DRM_DEV_ERROR(hdata->dev,
				      "Failed to find hdmiphy node in device tree\n");
			वापस -ENODEV;
		पूर्ण
	पूर्ण

	अगर (hdata->drv_data->is_apb_phy) अणु
		hdata->regs_hdmiphy = of_iomap(np, 0);
		अगर (!hdata->regs_hdmiphy) अणु
			DRM_DEV_ERROR(hdata->dev,
				      "failed to ioremap hdmi phy\n");
			ret = -ENOMEM;
			जाओ out;
		पूर्ण
	पूर्ण अन्यथा अणु
		hdata->hdmiphy_port = of_find_i2c_device_by_node(np);
		अगर (!hdata->hdmiphy_port) अणु
			DRM_INFO("Failed to get hdmi phy i2c client\n");
			ret = -EPROBE_DEFER;
			जाओ out;
		पूर्ण
	पूर्ण

out:
	of_node_put(np);
	वापस ret;
पूर्ण

अटल पूर्णांक hdmi_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा hdmi_audio_infoframe *audio_infoframe;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा hdmi_context *hdata;
	काष्ठा resource *res;
	पूर्णांक ret;

	hdata = devm_kzalloc(dev, माप(काष्ठा hdmi_context), GFP_KERNEL);
	अगर (!hdata)
		वापस -ENOMEM;

	hdata->drv_data = of_device_get_match_data(dev);

	platक्रमm_set_drvdata(pdev, hdata);

	hdata->dev = dev;

	mutex_init(&hdata->mutex);

	ret = hdmi_resources_init(hdata);
	अगर (ret) अणु
		अगर (ret != -EPROBE_DEFER)
			DRM_DEV_ERROR(dev, "hdmi_resources_init failed\n");
		वापस ret;
	पूर्ण

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	hdata->regs = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(hdata->regs)) अणु
		ret = PTR_ERR(hdata->regs);
		वापस ret;
	पूर्ण

	ret = hdmi_get_ddc_adapter(hdata);
	अगर (ret)
		वापस ret;

	ret = hdmi_get_phy_io(hdata);
	अगर (ret)
		जाओ err_ddc;

	INIT_DELAYED_WORK(&hdata->hotplug_work, hdmi_hotplug_work_func);

	ret = devm_request_thपढ़ोed_irq(dev, hdata->irq, शून्य,
			hdmi_irq_thपढ़ो, IRQF_TRIGGER_RISING |
			IRQF_TRIGGER_FALLING | IRQF_ONESHOT,
			"hdmi", hdata);
	अगर (ret) अणु
		DRM_DEV_ERROR(dev, "failed to register hdmi interrupt\n");
		जाओ err_hdmiphy;
	पूर्ण

	hdata->pmureg = syscon_regmap_lookup_by_phandle(dev->of_node,
			"samsung,syscon-phandle");
	अगर (IS_ERR(hdata->pmureg)) अणु
		DRM_DEV_ERROR(dev, "syscon regmap lookup failed.\n");
		ret = -EPROBE_DEFER;
		जाओ err_hdmiphy;
	पूर्ण

	अगर (hdata->drv_data->has_sysreg) अणु
		hdata->sysreg = syscon_regmap_lookup_by_phandle(dev->of_node,
				"samsung,sysreg-phandle");
		अगर (IS_ERR(hdata->sysreg)) अणु
			DRM_DEV_ERROR(dev, "sysreg regmap lookup failed.\n");
			ret = -EPROBE_DEFER;
			जाओ err_hdmiphy;
		पूर्ण
	पूर्ण

	अगर (!IS_ERR(hdata->reg_hdmi_en)) अणु
		ret = regulator_enable(hdata->reg_hdmi_en);
		अगर (ret) अणु
			DRM_DEV_ERROR(dev,
			      "failed to enable hdmi-en regulator\n");
			जाओ err_hdmiphy;
		पूर्ण
	पूर्ण

	pm_runसमय_enable(dev);

	audio_infoframe = &hdata->audio.infoframe;
	hdmi_audio_infoframe_init(audio_infoframe);
	audio_infoframe->coding_type = HDMI_AUDIO_CODING_TYPE_STREAM;
	audio_infoframe->sample_size = HDMI_AUDIO_SAMPLE_SIZE_STREAM;
	audio_infoframe->sample_frequency = HDMI_AUDIO_SAMPLE_FREQUENCY_STREAM;
	audio_infoframe->channels = 2;

	ret = hdmi_रेजिस्टर_audio_device(hdata);
	अगर (ret)
		जाओ err_rpm_disable;

	ret = component_add(&pdev->dev, &hdmi_component_ops);
	अगर (ret)
		जाओ err_unरेजिस्टर_audio;

	वापस ret;

err_unरेजिस्टर_audio:
	platक्रमm_device_unरेजिस्टर(hdata->audio.pdev);

err_rpm_disable:
	pm_runसमय_disable(dev);
	अगर (!IS_ERR(hdata->reg_hdmi_en))
		regulator_disable(hdata->reg_hdmi_en);
err_hdmiphy:
	अगर (hdata->hdmiphy_port)
		put_device(&hdata->hdmiphy_port->dev);
	अगर (hdata->regs_hdmiphy)
		iounmap(hdata->regs_hdmiphy);
err_ddc:
	put_device(&hdata->ddc_adpt->dev);

	वापस ret;
पूर्ण

अटल पूर्णांक hdmi_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा hdmi_context *hdata = platक्रमm_get_drvdata(pdev);

	cancel_delayed_work_sync(&hdata->hotplug_work);

	component_del(&pdev->dev, &hdmi_component_ops);
	platक्रमm_device_unरेजिस्टर(hdata->audio.pdev);

	pm_runसमय_disable(&pdev->dev);

	अगर (!IS_ERR(hdata->reg_hdmi_en))
		regulator_disable(hdata->reg_hdmi_en);

	अगर (hdata->hdmiphy_port)
		put_device(&hdata->hdmiphy_port->dev);

	अगर (hdata->regs_hdmiphy)
		iounmap(hdata->regs_hdmiphy);

	put_device(&hdata->ddc_adpt->dev);

	mutex_destroy(&hdata->mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused exynos_hdmi_suspend(काष्ठा device *dev)
अणु
	काष्ठा hdmi_context *hdata = dev_get_drvdata(dev);

	hdmi_clk_disable_gates(hdata);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused exynos_hdmi_resume(काष्ठा device *dev)
अणु
	काष्ठा hdmi_context *hdata = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = hdmi_clk_enable_gates(hdata);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops exynos_hdmi_pm_ops = अणु
	SET_RUNTIME_PM_OPS(exynos_hdmi_suspend, exynos_hdmi_resume, शून्य)
	SET_SYSTEM_SLEEP_PM_OPS(pm_runसमय_क्रमce_suspend,
				pm_runसमय_क्रमce_resume)
पूर्ण;

काष्ठा platक्रमm_driver hdmi_driver = अणु
	.probe		= hdmi_probe,
	.हटाओ		= hdmi_हटाओ,
	.driver		= अणु
		.name	= "exynos-hdmi",
		.owner	= THIS_MODULE,
		.pm	= &exynos_hdmi_pm_ops,
		.of_match_table = hdmi_match_types,
	पूर्ण,
पूर्ण;
