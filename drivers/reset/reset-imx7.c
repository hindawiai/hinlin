<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2017, Impinj, Inc.
 *
 * i.MX7 System Reset Controller (SRC) driver
 *
 * Author: Andrey Smirnov <andrew.smirnov@gmail.com>
 */

#समावेश <linux/mfd/syscon.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/reset-controller.h>
#समावेश <linux/regmap.h>
#समावेश <dt-bindings/reset/imx7-reset.h>
#समावेश <dt-bindings/reset/imx8mq-reset.h>
#समावेश <dt-bindings/reset/imx8mp-reset.h>

काष्ठा imx7_src_संकेत अणु
	अचिन्हित पूर्णांक offset, bit;
पूर्ण;

काष्ठा imx7_src_variant अणु
	स्थिर काष्ठा imx7_src_संकेत *संकेतs;
	अचिन्हित पूर्णांक संकेतs_num;
	काष्ठा reset_control_ops ops;
पूर्ण;

काष्ठा imx7_src अणु
	काष्ठा reset_controller_dev rcdev;
	काष्ठा regmap *regmap;
	स्थिर काष्ठा imx7_src_संकेत *संकेतs;
पूर्ण;

क्रमागत imx7_src_रेजिस्टरs अणु
	SRC_A7RCR0		= 0x0004,
	SRC_M4RCR		= 0x000c,
	SRC_ERCR		= 0x0014,
	SRC_HSICPHY_RCR		= 0x001c,
	SRC_USBOPHY1_RCR	= 0x0020,
	SRC_USBOPHY2_RCR	= 0x0024,
	SRC_MIPIPHY_RCR		= 0x0028,
	SRC_PCIEPHY_RCR		= 0x002c,
	SRC_DDRC_RCR		= 0x1000,
पूर्ण;

अटल पूर्णांक imx7_reset_update(काष्ठा imx7_src *imx7src,
			     अचिन्हित दीर्घ id, अचिन्हित पूर्णांक value)
अणु
	स्थिर काष्ठा imx7_src_संकेत *संकेत = &imx7src->संकेतs[id];

	वापस regmap_update_bits(imx7src->regmap,
				  संकेत->offset, संकेत->bit, value);
पूर्ण

अटल स्थिर काष्ठा imx7_src_संकेत imx7_src_संकेतs[IMX7_RESET_NUM] = अणु
	[IMX7_RESET_A7_CORE_POR_RESET0] = अणु SRC_A7RCR0, BIT(0) पूर्ण,
	[IMX7_RESET_A7_CORE_POR_RESET1] = अणु SRC_A7RCR0, BIT(1) पूर्ण,
	[IMX7_RESET_A7_CORE_RESET0]     = अणु SRC_A7RCR0, BIT(4) पूर्ण,
	[IMX7_RESET_A7_CORE_RESET1]	= अणु SRC_A7RCR0, BIT(5) पूर्ण,
	[IMX7_RESET_A7_DBG_RESET0]	= अणु SRC_A7RCR0, BIT(8) पूर्ण,
	[IMX7_RESET_A7_DBG_RESET1]	= अणु SRC_A7RCR0, BIT(9) पूर्ण,
	[IMX7_RESET_A7_ETM_RESET0]	= अणु SRC_A7RCR0, BIT(12) पूर्ण,
	[IMX7_RESET_A7_ETM_RESET1]	= अणु SRC_A7RCR0, BIT(13) पूर्ण,
	[IMX7_RESET_A7_SOC_DBG_RESET]	= अणु SRC_A7RCR0, BIT(20) पूर्ण,
	[IMX7_RESET_A7_L2RESET]		= अणु SRC_A7RCR0, BIT(21) पूर्ण,
	[IMX7_RESET_SW_M4C_RST]		= अणु SRC_M4RCR, BIT(1) पूर्ण,
	[IMX7_RESET_SW_M4P_RST]		= अणु SRC_M4RCR, BIT(2) पूर्ण,
	[IMX7_RESET_EIM_RST]		= अणु SRC_ERCR, BIT(0) पूर्ण,
	[IMX7_RESET_HSICPHY_PORT_RST]	= अणु SRC_HSICPHY_RCR, BIT(1) पूर्ण,
	[IMX7_RESET_USBPHY1_POR]	= अणु SRC_USBOPHY1_RCR, BIT(0) पूर्ण,
	[IMX7_RESET_USBPHY1_PORT_RST]	= अणु SRC_USBOPHY1_RCR, BIT(1) पूर्ण,
	[IMX7_RESET_USBPHY2_POR]	= अणु SRC_USBOPHY2_RCR, BIT(0) पूर्ण,
	[IMX7_RESET_USBPHY2_PORT_RST]	= अणु SRC_USBOPHY2_RCR, BIT(1) पूर्ण,
	[IMX7_RESET_MIPI_PHY_MRST]	= अणु SRC_MIPIPHY_RCR, BIT(1) पूर्ण,
	[IMX7_RESET_MIPI_PHY_SRST]	= अणु SRC_MIPIPHY_RCR, BIT(2) पूर्ण,
	[IMX7_RESET_PCIEPHY]		= अणु SRC_PCIEPHY_RCR, BIT(2) | BIT(1) पूर्ण,
	[IMX7_RESET_PCIEPHY_PERST]	= अणु SRC_PCIEPHY_RCR, BIT(3) पूर्ण,
	[IMX7_RESET_PCIE_CTRL_APPS_EN]	= अणु SRC_PCIEPHY_RCR, BIT(6) पूर्ण,
	[IMX7_RESET_PCIE_CTRL_APPS_TURNOFF] = अणु SRC_PCIEPHY_RCR, BIT(11) पूर्ण,
	[IMX7_RESET_DDRC_PRST]		= अणु SRC_DDRC_RCR, BIT(0) पूर्ण,
	[IMX7_RESET_DDRC_CORE_RST]	= अणु SRC_DDRC_RCR, BIT(1) पूर्ण,
पूर्ण;

अटल काष्ठा imx7_src *to_imx7_src(काष्ठा reset_controller_dev *rcdev)
अणु
	वापस container_of(rcdev, काष्ठा imx7_src, rcdev);
पूर्ण

अटल पूर्णांक imx7_reset_set(काष्ठा reset_controller_dev *rcdev,
			  अचिन्हित दीर्घ id, bool निश्चित)
अणु
	काष्ठा imx7_src *imx7src = to_imx7_src(rcdev);
	स्थिर अचिन्हित पूर्णांक bit = imx7src->संकेतs[id].bit;
	अचिन्हित पूर्णांक value = निश्चित ? bit : 0;

	चयन (id) अणु
	हाल IMX7_RESET_PCIEPHY:
		/*
		 * रुको क्रम more than 10us to release phy g_rst and
		 * btnrst
		 */
		अगर (!निश्चित)
			udelay(10);
		अवरोध;

	हाल IMX7_RESET_PCIE_CTRL_APPS_EN:
		value = निश्चित ? 0 : bit;
		अवरोध;
	पूर्ण

	वापस imx7_reset_update(imx7src, id, value);
पूर्ण

अटल पूर्णांक imx7_reset_निश्चित(काष्ठा reset_controller_dev *rcdev,
			     अचिन्हित दीर्घ id)
अणु
	वापस imx7_reset_set(rcdev, id, true);
पूर्ण

अटल पूर्णांक imx7_reset_deनिश्चित(काष्ठा reset_controller_dev *rcdev,
			       अचिन्हित दीर्घ id)
अणु
	वापस imx7_reset_set(rcdev, id, false);
पूर्ण

अटल स्थिर काष्ठा imx7_src_variant variant_imx7 = अणु
	.संकेतs = imx7_src_संकेतs,
	.संकेतs_num = ARRAY_SIZE(imx7_src_संकेतs),
	.ops = अणु
		.निश्चित   = imx7_reset_निश्चित,
		.deनिश्चित = imx7_reset_deनिश्चित,
	पूर्ण,
पूर्ण;

क्रमागत imx8mq_src_रेजिस्टरs अणु
	SRC_A53RCR0		= 0x0004,
	SRC_HDMI_RCR		= 0x0030,
	SRC_DISP_RCR		= 0x0034,
	SRC_GPU_RCR		= 0x0040,
	SRC_VPU_RCR		= 0x0044,
	SRC_PCIE2_RCR		= 0x0048,
	SRC_MIPIPHY1_RCR	= 0x004c,
	SRC_MIPIPHY2_RCR	= 0x0050,
	SRC_DDRC2_RCR		= 0x1004,
पूर्ण;

क्रमागत imx8mp_src_रेजिस्टरs अणु
	SRC_SUPERMIX_RCR	= 0x0018,
	SRC_AUDIOMIX_RCR	= 0x001c,
	SRC_MLMIX_RCR		= 0x0028,
	SRC_GPU2D_RCR		= 0x0038,
	SRC_GPU3D_RCR		= 0x003c,
	SRC_VPU_G1_RCR		= 0x0048,
	SRC_VPU_G2_RCR		= 0x004c,
	SRC_VPUVC8KE_RCR	= 0x0050,
	SRC_NOC_RCR		= 0x0054,
पूर्ण;

अटल स्थिर काष्ठा imx7_src_संकेत imx8mq_src_संकेतs[IMX8MQ_RESET_NUM] = अणु
	[IMX8MQ_RESET_A53_CORE_POR_RESET0]	= अणु SRC_A53RCR0, BIT(0) पूर्ण,
	[IMX8MQ_RESET_A53_CORE_POR_RESET1]	= अणु SRC_A53RCR0, BIT(1) पूर्ण,
	[IMX8MQ_RESET_A53_CORE_POR_RESET2]	= अणु SRC_A53RCR0, BIT(2) पूर्ण,
	[IMX8MQ_RESET_A53_CORE_POR_RESET3]	= अणु SRC_A53RCR0, BIT(3) पूर्ण,
	[IMX8MQ_RESET_A53_CORE_RESET0]		= अणु SRC_A53RCR0, BIT(4) पूर्ण,
	[IMX8MQ_RESET_A53_CORE_RESET1]		= अणु SRC_A53RCR0, BIT(5) पूर्ण,
	[IMX8MQ_RESET_A53_CORE_RESET2]		= अणु SRC_A53RCR0, BIT(6) पूर्ण,
	[IMX8MQ_RESET_A53_CORE_RESET3]		= अणु SRC_A53RCR0, BIT(7) पूर्ण,
	[IMX8MQ_RESET_A53_DBG_RESET0]		= अणु SRC_A53RCR0, BIT(8) पूर्ण,
	[IMX8MQ_RESET_A53_DBG_RESET1]		= अणु SRC_A53RCR0, BIT(9) पूर्ण,
	[IMX8MQ_RESET_A53_DBG_RESET2]		= अणु SRC_A53RCR0, BIT(10) पूर्ण,
	[IMX8MQ_RESET_A53_DBG_RESET3]		= अणु SRC_A53RCR0, BIT(11) पूर्ण,
	[IMX8MQ_RESET_A53_ETM_RESET0]		= अणु SRC_A53RCR0, BIT(12) पूर्ण,
	[IMX8MQ_RESET_A53_ETM_RESET1]		= अणु SRC_A53RCR0, BIT(13) पूर्ण,
	[IMX8MQ_RESET_A53_ETM_RESET2]		= अणु SRC_A53RCR0, BIT(14) पूर्ण,
	[IMX8MQ_RESET_A53_ETM_RESET3]		= अणु SRC_A53RCR0, BIT(15) पूर्ण,
	[IMX8MQ_RESET_A53_SOC_DBG_RESET]	= अणु SRC_A53RCR0, BIT(20) पूर्ण,
	[IMX8MQ_RESET_A53_L2RESET]		= अणु SRC_A53RCR0, BIT(21) पूर्ण,
	[IMX8MQ_RESET_SW_NON_SCLR_M4C_RST]	= अणु SRC_M4RCR, BIT(0) पूर्ण,
	[IMX8MQ_RESET_SW_M4C_RST]		= अणु SRC_M4RCR, BIT(1) पूर्ण,
	[IMX8MQ_RESET_SW_M4P_RST]		= अणु SRC_M4RCR, BIT(2) पूर्ण,
	[IMX8MQ_RESET_M4_ENABLE]		= अणु SRC_M4RCR, BIT(3) पूर्ण,
	[IMX8MQ_RESET_OTG1_PHY_RESET]		= अणु SRC_USBOPHY1_RCR, BIT(0) पूर्ण,
	[IMX8MQ_RESET_OTG2_PHY_RESET]		= अणु SRC_USBOPHY2_RCR, BIT(0) पूर्ण,
	[IMX8MQ_RESET_MIPI_DSI_RESET_BYTE_N]	= अणु SRC_MIPIPHY_RCR, BIT(1) पूर्ण,
	[IMX8MQ_RESET_MIPI_DSI_RESET_N]		= अणु SRC_MIPIPHY_RCR, BIT(2) पूर्ण,
	[IMX8MQ_RESET_MIPI_DSI_DPI_RESET_N]	= अणु SRC_MIPIPHY_RCR, BIT(3) पूर्ण,
	[IMX8MQ_RESET_MIPI_DSI_ESC_RESET_N]	= अणु SRC_MIPIPHY_RCR, BIT(4) पूर्ण,
	[IMX8MQ_RESET_MIPI_DSI_PCLK_RESET_N]	= अणु SRC_MIPIPHY_RCR, BIT(5) पूर्ण,
	[IMX8MQ_RESET_PCIEPHY]			= अणु SRC_PCIEPHY_RCR,
						    BIT(2) | BIT(1) पूर्ण,
	[IMX8MQ_RESET_PCIEPHY_PERST]		= अणु SRC_PCIEPHY_RCR, BIT(3) पूर्ण,
	[IMX8MQ_RESET_PCIE_CTRL_APPS_EN]	= अणु SRC_PCIEPHY_RCR, BIT(6) पूर्ण,
	[IMX8MQ_RESET_PCIE_CTRL_APPS_TURNOFF]	= अणु SRC_PCIEPHY_RCR, BIT(11) पूर्ण,
	[IMX8MQ_RESET_HDMI_PHY_APB_RESET]	= अणु SRC_HDMI_RCR, BIT(0) पूर्ण,
	[IMX8MQ_RESET_DISP_RESET]		= अणु SRC_DISP_RCR, BIT(0) पूर्ण,
	[IMX8MQ_RESET_GPU_RESET]		= अणु SRC_GPU_RCR, BIT(0) पूर्ण,
	[IMX8MQ_RESET_VPU_RESET]		= अणु SRC_VPU_RCR, BIT(0) पूर्ण,
	[IMX8MQ_RESET_PCIEPHY2]			= अणु SRC_PCIE2_RCR,
						    BIT(2) | BIT(1) पूर्ण,
	[IMX8MQ_RESET_PCIEPHY2_PERST]		= अणु SRC_PCIE2_RCR, BIT(3) पूर्ण,
	[IMX8MQ_RESET_PCIE2_CTRL_APPS_EN]	= अणु SRC_PCIE2_RCR, BIT(6) पूर्ण,
	[IMX8MQ_RESET_PCIE2_CTRL_APPS_TURNOFF]	= अणु SRC_PCIE2_RCR, BIT(11) पूर्ण,
	[IMX8MQ_RESET_MIPI_CSI1_CORE_RESET]	= अणु SRC_MIPIPHY1_RCR, BIT(0) पूर्ण,
	[IMX8MQ_RESET_MIPI_CSI1_PHY_REF_RESET]	= अणु SRC_MIPIPHY1_RCR, BIT(1) पूर्ण,
	[IMX8MQ_RESET_MIPI_CSI1_ESC_RESET]	= अणु SRC_MIPIPHY1_RCR, BIT(2) पूर्ण,
	[IMX8MQ_RESET_MIPI_CSI2_CORE_RESET]	= अणु SRC_MIPIPHY2_RCR, BIT(0) पूर्ण,
	[IMX8MQ_RESET_MIPI_CSI2_PHY_REF_RESET]	= अणु SRC_MIPIPHY2_RCR, BIT(1) पूर्ण,
	[IMX8MQ_RESET_MIPI_CSI2_ESC_RESET]	= अणु SRC_MIPIPHY2_RCR, BIT(2) पूर्ण,
	[IMX8MQ_RESET_DDRC1_PRST]		= अणु SRC_DDRC_RCR, BIT(0) पूर्ण,
	[IMX8MQ_RESET_DDRC1_CORE_RESET]		= अणु SRC_DDRC_RCR, BIT(1) पूर्ण,
	[IMX8MQ_RESET_DDRC1_PHY_RESET]		= अणु SRC_DDRC_RCR, BIT(2) पूर्ण,
	[IMX8MQ_RESET_DDRC2_PHY_RESET]		= अणु SRC_DDRC2_RCR, BIT(0) पूर्ण,
	[IMX8MQ_RESET_DDRC2_CORE_RESET]		= अणु SRC_DDRC2_RCR, BIT(1) पूर्ण,
	[IMX8MQ_RESET_DDRC2_PRST]		= अणु SRC_DDRC2_RCR, BIT(2) पूर्ण,
पूर्ण;

अटल पूर्णांक imx8mq_reset_set(काष्ठा reset_controller_dev *rcdev,
			    अचिन्हित दीर्घ id, bool निश्चित)
अणु
	काष्ठा imx7_src *imx7src = to_imx7_src(rcdev);
	स्थिर अचिन्हित पूर्णांक bit = imx7src->संकेतs[id].bit;
	अचिन्हित पूर्णांक value = निश्चित ? bit : 0;

	चयन (id) अणु
	हाल IMX8MQ_RESET_PCIEPHY:
	हाल IMX8MQ_RESET_PCIEPHY2:
		/*
		 * रुको क्रम more than 10us to release phy g_rst and
		 * btnrst
		 */
		अगर (!निश्चित)
			udelay(10);
		अवरोध;

	हाल IMX8MQ_RESET_PCIE_CTRL_APPS_EN:
	हाल IMX8MQ_RESET_PCIE2_CTRL_APPS_EN:
	हाल IMX8MQ_RESET_MIPI_DSI_PCLK_RESET_N:
	हाल IMX8MQ_RESET_MIPI_DSI_ESC_RESET_N:
	हाल IMX8MQ_RESET_MIPI_DSI_DPI_RESET_N:
	हाल IMX8MQ_RESET_MIPI_DSI_RESET_N:
	हाल IMX8MQ_RESET_MIPI_DSI_RESET_BYTE_N:
	हाल IMX8MQ_RESET_M4_ENABLE:
		value = निश्चित ? 0 : bit;
		अवरोध;
	पूर्ण

	वापस imx7_reset_update(imx7src, id, value);
पूर्ण

अटल पूर्णांक imx8mq_reset_निश्चित(काष्ठा reset_controller_dev *rcdev,
			       अचिन्हित दीर्घ id)
अणु
	वापस imx8mq_reset_set(rcdev, id, true);
पूर्ण

अटल पूर्णांक imx8mq_reset_deनिश्चित(काष्ठा reset_controller_dev *rcdev,
				 अचिन्हित दीर्घ id)
अणु
	वापस imx8mq_reset_set(rcdev, id, false);
पूर्ण

अटल स्थिर काष्ठा imx7_src_variant variant_imx8mq = अणु
	.संकेतs = imx8mq_src_संकेतs,
	.संकेतs_num = ARRAY_SIZE(imx8mq_src_संकेतs),
	.ops = अणु
		.निश्चित   = imx8mq_reset_निश्चित,
		.deनिश्चित = imx8mq_reset_deनिश्चित,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा imx7_src_संकेत imx8mp_src_संकेतs[IMX8MP_RESET_NUM] = अणु
	[IMX8MP_RESET_A53_CORE_POR_RESET0]	= अणु SRC_A53RCR0, BIT(0) पूर्ण,
	[IMX8MP_RESET_A53_CORE_POR_RESET1]	= अणु SRC_A53RCR0, BIT(1) पूर्ण,
	[IMX8MP_RESET_A53_CORE_POR_RESET2]	= अणु SRC_A53RCR0, BIT(2) पूर्ण,
	[IMX8MP_RESET_A53_CORE_POR_RESET3]	= अणु SRC_A53RCR0, BIT(3) पूर्ण,
	[IMX8MP_RESET_A53_CORE_RESET0]		= अणु SRC_A53RCR0, BIT(4) पूर्ण,
	[IMX8MP_RESET_A53_CORE_RESET1]		= अणु SRC_A53RCR0, BIT(5) पूर्ण,
	[IMX8MP_RESET_A53_CORE_RESET2]		= अणु SRC_A53RCR0, BIT(6) पूर्ण,
	[IMX8MP_RESET_A53_CORE_RESET3]		= अणु SRC_A53RCR0, BIT(7) पूर्ण,
	[IMX8MP_RESET_A53_DBG_RESET0]		= अणु SRC_A53RCR0, BIT(8) पूर्ण,
	[IMX8MP_RESET_A53_DBG_RESET1]		= अणु SRC_A53RCR0, BIT(9) पूर्ण,
	[IMX8MP_RESET_A53_DBG_RESET2]		= अणु SRC_A53RCR0, BIT(10) पूर्ण,
	[IMX8MP_RESET_A53_DBG_RESET3]		= अणु SRC_A53RCR0, BIT(11) पूर्ण,
	[IMX8MP_RESET_A53_ETM_RESET0]		= अणु SRC_A53RCR0, BIT(12) पूर्ण,
	[IMX8MP_RESET_A53_ETM_RESET1]		= अणु SRC_A53RCR0, BIT(13) पूर्ण,
	[IMX8MP_RESET_A53_ETM_RESET2]		= अणु SRC_A53RCR0, BIT(14) पूर्ण,
	[IMX8MP_RESET_A53_ETM_RESET3]		= अणु SRC_A53RCR0, BIT(15) पूर्ण,
	[IMX8MP_RESET_A53_SOC_DBG_RESET]	= अणु SRC_A53RCR0, BIT(20) पूर्ण,
	[IMX8MP_RESET_A53_L2RESET]		= अणु SRC_A53RCR0, BIT(21) पूर्ण,
	[IMX8MP_RESET_SW_NON_SCLR_M7C_RST]	= अणु SRC_M4RCR, BIT(0) पूर्ण,
	[IMX8MP_RESET_OTG1_PHY_RESET]		= अणु SRC_USBOPHY1_RCR, BIT(0) पूर्ण,
	[IMX8MP_RESET_OTG2_PHY_RESET]		= अणु SRC_USBOPHY2_RCR, BIT(0) पूर्ण,
	[IMX8MP_RESET_SUPERMIX_RESET]		= अणु SRC_SUPERMIX_RCR, BIT(0) पूर्ण,
	[IMX8MP_RESET_AUDIOMIX_RESET]		= अणु SRC_AUDIOMIX_RCR, BIT(0) पूर्ण,
	[IMX8MP_RESET_MLMIX_RESET]		= अणु SRC_MLMIX_RCR, BIT(0) पूर्ण,
	[IMX8MP_RESET_PCIEPHY]			= अणु SRC_PCIEPHY_RCR, BIT(2) पूर्ण,
	[IMX8MP_RESET_PCIEPHY_PERST]		= अणु SRC_PCIEPHY_RCR, BIT(3) पूर्ण,
	[IMX8MP_RESET_PCIE_CTRL_APPS_EN]	= अणु SRC_PCIEPHY_RCR, BIT(6) पूर्ण,
	[IMX8MP_RESET_PCIE_CTRL_APPS_TURNOFF]	= अणु SRC_PCIEPHY_RCR, BIT(11) पूर्ण,
	[IMX8MP_RESET_HDMI_PHY_APB_RESET]	= अणु SRC_HDMI_RCR, BIT(0) पूर्ण,
	[IMX8MP_RESET_MEDIA_RESET]		= अणु SRC_DISP_RCR, BIT(0) पूर्ण,
	[IMX8MP_RESET_GPU2D_RESET]		= अणु SRC_GPU2D_RCR, BIT(0) पूर्ण,
	[IMX8MP_RESET_GPU3D_RESET]		= अणु SRC_GPU3D_RCR, BIT(0) पूर्ण,
	[IMX8MP_RESET_GPU_RESET]		= अणु SRC_GPU_RCR, BIT(0) पूर्ण,
	[IMX8MP_RESET_VPU_RESET]		= अणु SRC_VPU_RCR, BIT(0) पूर्ण,
	[IMX8MP_RESET_VPU_G1_RESET]		= अणु SRC_VPU_G1_RCR, BIT(0) पूर्ण,
	[IMX8MP_RESET_VPU_G2_RESET]		= अणु SRC_VPU_G2_RCR, BIT(0) पूर्ण,
	[IMX8MP_RESET_VPUVC8KE_RESET]		= अणु SRC_VPUVC8KE_RCR, BIT(0) पूर्ण,
	[IMX8MP_RESET_NOC_RESET]		= अणु SRC_NOC_RCR, BIT(0) पूर्ण,
पूर्ण;

अटल पूर्णांक imx8mp_reset_set(काष्ठा reset_controller_dev *rcdev,
			    अचिन्हित दीर्घ id, bool निश्चित)
अणु
	काष्ठा imx7_src *imx7src = to_imx7_src(rcdev);
	स्थिर अचिन्हित पूर्णांक bit = imx7src->संकेतs[id].bit;
	अचिन्हित पूर्णांक value = निश्चित ? bit : 0;

	चयन (id) अणु
	हाल IMX8MP_RESET_PCIEPHY:
		/*
		 * रुको क्रम more than 10us to release phy g_rst and
		 * btnrst
		 */
		अगर (!निश्चित)
			udelay(10);
		अवरोध;

	हाल IMX8MP_RESET_PCIE_CTRL_APPS_EN:
		value = निश्चित ? 0 : bit;
		अवरोध;
	पूर्ण

	वापस imx7_reset_update(imx7src, id, value);
पूर्ण

अटल पूर्णांक imx8mp_reset_निश्चित(काष्ठा reset_controller_dev *rcdev,
			       अचिन्हित दीर्घ id)
अणु
	वापस imx8mp_reset_set(rcdev, id, true);
पूर्ण

अटल पूर्णांक imx8mp_reset_deनिश्चित(काष्ठा reset_controller_dev *rcdev,
				 अचिन्हित दीर्घ id)
अणु
	वापस imx8mp_reset_set(rcdev, id, false);
पूर्ण

अटल स्थिर काष्ठा imx7_src_variant variant_imx8mp = अणु
	.संकेतs = imx8mp_src_संकेतs,
	.संकेतs_num = ARRAY_SIZE(imx8mp_src_संकेतs),
	.ops = अणु
		.निश्चित   = imx8mp_reset_निश्चित,
		.deनिश्चित = imx8mp_reset_deनिश्चित,
	पूर्ण,
पूर्ण;

अटल पूर्णांक imx7_reset_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा imx7_src *imx7src;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा regmap_config config = अणु .name = "src" पूर्ण;
	स्थिर काष्ठा imx7_src_variant *variant = of_device_get_match_data(dev);

	imx7src = devm_kzalloc(dev, माप(*imx7src), GFP_KERNEL);
	अगर (!imx7src)
		वापस -ENOMEM;

	imx7src->संकेतs = variant->संकेतs;
	imx7src->regmap = syscon_node_to_regmap(dev->of_node);
	अगर (IS_ERR(imx7src->regmap)) अणु
		dev_err(dev, "Unable to get imx7-src regmap");
		वापस PTR_ERR(imx7src->regmap);
	पूर्ण
	regmap_attach_dev(dev, imx7src->regmap, &config);

	imx7src->rcdev.owner     = THIS_MODULE;
	imx7src->rcdev.nr_resets = variant->संकेतs_num;
	imx7src->rcdev.ops       = &variant->ops;
	imx7src->rcdev.of_node   = dev->of_node;

	वापस devm_reset_controller_रेजिस्टर(dev, &imx7src->rcdev);
पूर्ण

अटल स्थिर काष्ठा of_device_id imx7_reset_dt_ids[] = अणु
	अणु .compatible = "fsl,imx7d-src", .data = &variant_imx7 पूर्ण,
	अणु .compatible = "fsl,imx8mq-src", .data = &variant_imx8mq पूर्ण,
	अणु .compatible = "fsl,imx8mp-src", .data = &variant_imx8mp पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, imx7_reset_dt_ids);

अटल काष्ठा platक्रमm_driver imx7_reset_driver = अणु
	.probe	= imx7_reset_probe,
	.driver = अणु
		.name		= KBUILD_MODNAME,
		.of_match_table	= imx7_reset_dt_ids,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(imx7_reset_driver);

MODULE_AUTHOR("Andrey Smirnov <andrew.smirnov@gmail.com>");
MODULE_DESCRIPTION("NXP i.MX7 reset driver");
MODULE_LICENSE("GPL v2");
