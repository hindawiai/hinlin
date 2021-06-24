<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Freescale i.MX7 SoC series MIPI-CSI V3.3 receiver driver
 *
 * Copyright (C) 2019 Linaro Ltd
 * Copyright (C) 2015-2016 Freescale Semiconductor, Inc. All Rights Reserved.
 * Copyright (C) 2011 - 2013 Samsung Electronics Co., Ltd.
 *
 */

#समावेश <linux/clk.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/delay.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/reset.h>
#समावेश <linux/spinlock.h>

#समावेश <media/v4l2-common.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-fwnode.h>
#समावेश <media/v4l2-mc.h>
#समावेश <media/v4l2-subdev.h>

#घोषणा CSIS_DRIVER_NAME			"imx7-mipi-csis"
#घोषणा CSIS_SUBDEV_NAME			CSIS_DRIVER_NAME

#घोषणा CSIS_PAD_SINK				0
#घोषणा CSIS_PAD_SOURCE				1
#घोषणा CSIS_PADS_NUM				2

#घोषणा MIPI_CSIS_DEF_PIX_WIDTH			640
#घोषणा MIPI_CSIS_DEF_PIX_HEIGHT		480

/* Register map definition */

/* CSIS common control */
#घोषणा MIPI_CSIS_CMN_CTRL			0x04
#घोषणा MIPI_CSIS_CMN_CTRL_UPDATE_SHADOW	BIT(16)
#घोषणा MIPI_CSIS_CMN_CTRL_INTER_MODE		BIT(10)
#घोषणा MIPI_CSIS_CMN_CTRL_UPDATE_SHADOW_CTRL	BIT(2)
#घोषणा MIPI_CSIS_CMN_CTRL_RESET		BIT(1)
#घोषणा MIPI_CSIS_CMN_CTRL_ENABLE		BIT(0)

#घोषणा MIPI_CSIS_CMN_CTRL_LANE_NR_OFFSET	8
#घोषणा MIPI_CSIS_CMN_CTRL_LANE_NR_MASK		(3 << 8)

/* CSIS घड़ी control */
#घोषणा MIPI_CSIS_CLK_CTRL			0x08
#घोषणा MIPI_CSIS_CLK_CTRL_CLKGATE_TRAIL_CH3(x)	((x) << 28)
#घोषणा MIPI_CSIS_CLK_CTRL_CLKGATE_TRAIL_CH2(x)	((x) << 24)
#घोषणा MIPI_CSIS_CLK_CTRL_CLKGATE_TRAIL_CH1(x)	((x) << 20)
#घोषणा MIPI_CSIS_CLK_CTRL_CLKGATE_TRAIL_CH0(x)	((x) << 16)
#घोषणा MIPI_CSIS_CLK_CTRL_CLKGATE_EN_MSK	(0xf << 4)
#घोषणा MIPI_CSIS_CLK_CTRL_WCLK_SRC		BIT(0)

/* CSIS Interrupt mask */
#घोषणा MIPI_CSIS_INT_MSK			0x10
#घोषणा MIPI_CSIS_INT_MSK_EVEN_BEFORE		BIT(31)
#घोषणा MIPI_CSIS_INT_MSK_EVEN_AFTER		BIT(30)
#घोषणा MIPI_CSIS_INT_MSK_ODD_BEFORE		BIT(29)
#घोषणा MIPI_CSIS_INT_MSK_ODD_AFTER		BIT(28)
#घोषणा MIPI_CSIS_INT_MSK_FRAME_START		BIT(24)
#घोषणा MIPI_CSIS_INT_MSK_FRAME_END		BIT(20)
#घोषणा MIPI_CSIS_INT_MSK_ERR_SOT_HS		BIT(16)
#घोषणा MIPI_CSIS_INT_MSK_ERR_LOST_FS		BIT(12)
#घोषणा MIPI_CSIS_INT_MSK_ERR_LOST_FE		BIT(8)
#घोषणा MIPI_CSIS_INT_MSK_ERR_OVER		BIT(4)
#घोषणा MIPI_CSIS_INT_MSK_ERR_WRONG_CFG		BIT(3)
#घोषणा MIPI_CSIS_INT_MSK_ERR_ECC		BIT(2)
#घोषणा MIPI_CSIS_INT_MSK_ERR_CRC		BIT(1)
#घोषणा MIPI_CSIS_INT_MSK_ERR_UNKNOWN		BIT(0)

/* CSIS Interrupt source */
#घोषणा MIPI_CSIS_INT_SRC			0x14
#घोषणा MIPI_CSIS_INT_SRC_EVEN_BEFORE		BIT(31)
#घोषणा MIPI_CSIS_INT_SRC_EVEN_AFTER		BIT(30)
#घोषणा MIPI_CSIS_INT_SRC_EVEN			BIT(30)
#घोषणा MIPI_CSIS_INT_SRC_ODD_BEFORE		BIT(29)
#घोषणा MIPI_CSIS_INT_SRC_ODD_AFTER		BIT(28)
#घोषणा MIPI_CSIS_INT_SRC_ODD			(0x3 << 28)
#घोषणा MIPI_CSIS_INT_SRC_NON_IMAGE_DATA	(0xf << 28)
#घोषणा MIPI_CSIS_INT_SRC_FRAME_START		BIT(24)
#घोषणा MIPI_CSIS_INT_SRC_FRAME_END		BIT(20)
#घोषणा MIPI_CSIS_INT_SRC_ERR_SOT_HS		BIT(16)
#घोषणा MIPI_CSIS_INT_SRC_ERR_LOST_FS		BIT(12)
#घोषणा MIPI_CSIS_INT_SRC_ERR_LOST_FE		BIT(8)
#घोषणा MIPI_CSIS_INT_SRC_ERR_OVER		BIT(4)
#घोषणा MIPI_CSIS_INT_SRC_ERR_WRONG_CFG		BIT(3)
#घोषणा MIPI_CSIS_INT_SRC_ERR_ECC		BIT(2)
#घोषणा MIPI_CSIS_INT_SRC_ERR_CRC		BIT(1)
#घोषणा MIPI_CSIS_INT_SRC_ERR_UNKNOWN		BIT(0)
#घोषणा MIPI_CSIS_INT_SRC_ERRORS		0xfffff

/* D-PHY status control */
#घोषणा MIPI_CSIS_DPHY_STATUS			0x20
#घोषणा MIPI_CSIS_DPHY_STATUS_ULPS_DAT		BIT(8)
#घोषणा MIPI_CSIS_DPHY_STATUS_STOPSTATE_DAT	BIT(4)
#घोषणा MIPI_CSIS_DPHY_STATUS_ULPS_CLK		BIT(1)
#घोषणा MIPI_CSIS_DPHY_STATUS_STOPSTATE_CLK	BIT(0)

/* D-PHY common control */
#घोषणा MIPI_CSIS_DPHY_CMN_CTRL			0x24
#घोषणा MIPI_CSIS_DPHY_CMN_CTRL_HSSETTLE(n)	((n) << 24)
#घोषणा MIPI_CSIS_DPHY_CMN_CTRL_HSSETTLE_MASK	GENMASK(31, 24)
#घोषणा MIPI_CSIS_DPHY_CMN_CTRL_CLKSETTLE(n)	((n) << 22)
#घोषणा MIPI_CSIS_DPHY_CMN_CTRL_CLKSETTLE_MASK	GENMASK(23, 22)
#घोषणा MIPI_CSIS_DPHY_CMN_CTRL_DPDN_SWAP_CLK	BIT(6)
#घोषणा MIPI_CSIS_DPHY_CMN_CTRL_DPDN_SWAP_DAT	BIT(5)
#घोषणा MIPI_CSIS_DPHY_CMN_CTRL_ENABLE_DAT	BIT(1)
#घोषणा MIPI_CSIS_DPHY_CMN_CTRL_ENABLE_CLK	BIT(0)
#घोषणा MIPI_CSIS_DPHY_CMN_CTRL_ENABLE		(0x1f << 0)

/* D-PHY Master and Slave Control रेजिस्टर Low */
#घोषणा MIPI_CSIS_DPHY_BCTRL_L			0x30
#घोषणा MIPI_CSIS_DPHY_BCTRL_L_USER_DATA_PATTERN_LOW(n)		(((n) & 3U) << 30)
#घोषणा MIPI_CSIS_DPHY_BCTRL_L_BIAS_REF_VOLT_715MV		(0 << 28)
#घोषणा MIPI_CSIS_DPHY_BCTRL_L_BIAS_REF_VOLT_724MV		(1 << 28)
#घोषणा MIPI_CSIS_DPHY_BCTRL_L_BIAS_REF_VOLT_733MV		(2 << 28)
#घोषणा MIPI_CSIS_DPHY_BCTRL_L_BIAS_REF_VOLT_706MV		(3 << 28)
#घोषणा MIPI_CSIS_DPHY_BCTRL_L_BGR_CHOPPER_FREQ_3MHZ		(0 << 27)
#घोषणा MIPI_CSIS_DPHY_BCTRL_L_BGR_CHOPPER_FREQ_1_5MHZ		(1 << 27)
#घोषणा MIPI_CSIS_DPHY_BCTRL_L_VREG12_EXTPWR_EN_CTL		BIT(26)
#घोषणा MIPI_CSIS_DPHY_BCTRL_L_REG_12P_LVL_CTL_1_2V		(0 << 24)
#घोषणा MIPI_CSIS_DPHY_BCTRL_L_REG_12P_LVL_CTL_1_23V		(1 << 24)
#घोषणा MIPI_CSIS_DPHY_BCTRL_L_REG_12P_LVL_CTL_1_17V		(2 << 24)
#घोषणा MIPI_CSIS_DPHY_BCTRL_L_REG_12P_LVL_CTL_1_26V		(3 << 24)
#घोषणा MIPI_CSIS_DPHY_BCTRL_L_REG_1P2_LVL_SEL			BIT(23)
#घोषणा MIPI_CSIS_DPHY_BCTRL_L_LP_RX_HYS_LVL_80MV		(0 << 21)
#घोषणा MIPI_CSIS_DPHY_BCTRL_L_LP_RX_HYS_LVL_100MV		(1 << 21)
#घोषणा MIPI_CSIS_DPHY_BCTRL_L_LP_RX_HYS_LVL_120MV		(2 << 21)
#घोषणा MIPI_CSIS_DPHY_BCTRL_L_LP_RX_HYS_LVL_140MV		(3 << 21)
#घोषणा MIPI_CSIS_DPHY_BCTRL_L_VREF_SRC_SEL			BIT(20)
#घोषणा MIPI_CSIS_DPHY_BCTRL_L_LP_RX_VREF_LVL_715MV		(0 << 18)
#घोषणा MIPI_CSIS_DPHY_BCTRL_L_LP_RX_VREF_LVL_743MV		(1 << 18)
#घोषणा MIPI_CSIS_DPHY_BCTRL_L_LP_RX_VREF_LVL_650MV		(2 << 18)
#घोषणा MIPI_CSIS_DPHY_BCTRL_L_LP_RX_VREF_LVL_682MV		(3 << 18)
#घोषणा MIPI_CSIS_DPHY_BCTRL_L_LP_RX_PULSE_REJECT		BIT(17)
#घोषणा MIPI_CSIS_DPHY_BCTRL_L_MSTRCLK_LP_SLEW_RATE_DOWN_0	(0 << 15)
#घोषणा MIPI_CSIS_DPHY_BCTRL_L_MSTRCLK_LP_SLEW_RATE_DOWN_15P	(1 << 15)
#घोषणा MIPI_CSIS_DPHY_BCTRL_L_MSTRCLK_LP_SLEW_RATE_DOWN_30P	(3 << 15)
#घोषणा MIPI_CSIS_DPHY_BCTRL_L_MSTRCLK_LP_SLEW_RATE_UP		BIT(14)
#घोषणा MIPI_CSIS_DPHY_BCTRL_L_LP_CD_HYS_60MV			(0 << 13)
#घोषणा MIPI_CSIS_DPHY_BCTRL_L_LP_CD_HYS_70MV			(1 << 13)
#घोषणा MIPI_CSIS_DPHY_BCTRL_L_BGR_CHOPPER_EN			BIT(12)
#घोषणा MIPI_CSIS_DPHY_BCTRL_L_ERRCONTENTION_LP_EN		BIT(11)
#घोषणा MIPI_CSIS_DPHY_BCTRL_L_TXTRIGGER_CLK_EN			BIT(10)
#घोषणा MIPI_CSIS_DPHY_BCTRL_L_B_DPHYCTRL(n)			(((n) * 25 / 1000000) << 0)

/* D-PHY Master and Slave Control रेजिस्टर High */
#घोषणा MIPI_CSIS_DPHY_BCTRL_H			0x34
/* D-PHY Slave Control रेजिस्टर Low */
#घोषणा MIPI_CSIS_DPHY_SCTRL_L			0x38
/* D-PHY Slave Control रेजिस्टर High */
#घोषणा MIPI_CSIS_DPHY_SCTRL_H			0x3c

/* ISP Configuration रेजिस्टर */
#घोषणा MIPI_CSIS_ISP_CONFIG_CH(n)		(0x40 + (n) * 0x10)
#घोषणा MIPI_CSIS_ISPCFG_MEM_FULL_GAP_MSK	(0xff << 24)
#घोषणा MIPI_CSIS_ISPCFG_MEM_FULL_GAP(x)	((x) << 24)
#घोषणा MIPI_CSIS_ISPCFG_DOUBLE_CMPNT		BIT(12)
#घोषणा MIPI_CSIS_ISPCFG_ALIGN_32BIT		BIT(11)
#घोषणा MIPI_CSIS_ISPCFG_FMT_YCBCR422_8BIT	(0x1e << 2)
#घोषणा MIPI_CSIS_ISPCFG_FMT_RAW8		(0x2a << 2)
#घोषणा MIPI_CSIS_ISPCFG_FMT_RAW10		(0x2b << 2)
#घोषणा MIPI_CSIS_ISPCFG_FMT_RAW12		(0x2c << 2)
#घोषणा MIPI_CSIS_ISPCFG_FMT_RAW14		(0x2d << 2)
/* User defined क्रमmats, x = 1...4 */
#घोषणा MIPI_CSIS_ISPCFG_FMT_USER(x)		((0x30 + (x) - 1) << 2)
#घोषणा MIPI_CSIS_ISPCFG_FMT_MASK		(0x3f << 2)

/* ISP Image Resolution रेजिस्टर */
#घोषणा MIPI_CSIS_ISP_RESOL_CH(n)		(0x44 + (n) * 0x10)
#घोषणा CSIS_MAX_PIX_WIDTH			0xffff
#घोषणा CSIS_MAX_PIX_HEIGHT			0xffff

/* ISP SYNC रेजिस्टर */
#घोषणा MIPI_CSIS_ISP_SYNC_CH(n)		(0x48 + (n) * 0x10)
#घोषणा MIPI_CSIS_ISP_SYNC_HSYNC_LINTV_OFFSET	18
#घोषणा MIPI_CSIS_ISP_SYNC_VSYNC_SINTV_OFFSET	12
#घोषणा MIPI_CSIS_ISP_SYNC_VSYNC_EINTV_OFFSET	0

/* ISP shaकरोw रेजिस्टरs */
#घोषणा MIPI_CSIS_SDW_CONFIG_CH(n)		(0x80 + (n) * 0x10)
#घोषणा MIPI_CSIS_SDW_RESOL_CH(n)		(0x84 + (n) * 0x10)
#घोषणा MIPI_CSIS_SDW_SYNC_CH(n)		(0x88 + (n) * 0x10)

/* Debug control रेजिस्टर */
#घोषणा MIPI_CSIS_DBG_CTRL			0xc0

/* Non-image packet data buffers */
#घोषणा MIPI_CSIS_PKTDATA_ODD			0x2000
#घोषणा MIPI_CSIS_PKTDATA_EVEN			0x3000
#घोषणा MIPI_CSIS_PKTDATA_SIZE			SZ_4K

#घोषणा DEFAULT_SCLK_CSIS_FREQ			166000000UL

क्रमागत अणु
	ST_POWERED	= 1,
	ST_STREAMING	= 2,
	ST_SUSPENDED	= 4,
पूर्ण;

काष्ठा mipi_csis_event अणु
	u32 mask;
	स्थिर अक्षर * स्थिर name;
	अचिन्हित पूर्णांक counter;
पूर्ण;

अटल स्थिर काष्ठा mipi_csis_event mipi_csis_events[] = अणु
	/* Errors */
	अणु MIPI_CSIS_INT_SRC_ERR_SOT_HS,		"SOT Error" पूर्ण,
	अणु MIPI_CSIS_INT_SRC_ERR_LOST_FS,	"Lost Frame Start Error" पूर्ण,
	अणु MIPI_CSIS_INT_SRC_ERR_LOST_FE,	"Lost Frame End Error" पूर्ण,
	अणु MIPI_CSIS_INT_SRC_ERR_OVER,		"FIFO Overflow Error" पूर्ण,
	अणु MIPI_CSIS_INT_SRC_ERR_WRONG_CFG,	"Wrong Configuration Error" पूर्ण,
	अणु MIPI_CSIS_INT_SRC_ERR_ECC,		"ECC Error" पूर्ण,
	अणु MIPI_CSIS_INT_SRC_ERR_CRC,		"CRC Error" पूर्ण,
	अणु MIPI_CSIS_INT_SRC_ERR_UNKNOWN,	"Unknown Error" पूर्ण,
	/* Non-image data receive events */
	अणु MIPI_CSIS_INT_SRC_EVEN_BEFORE,	"Non-image data before even frame" पूर्ण,
	अणु MIPI_CSIS_INT_SRC_EVEN_AFTER,		"Non-image data after even frame" पूर्ण,
	अणु MIPI_CSIS_INT_SRC_ODD_BEFORE,		"Non-image data before odd frame" पूर्ण,
	अणु MIPI_CSIS_INT_SRC_ODD_AFTER,		"Non-image data after odd frame" पूर्ण,
	/* Frame start/end */
	अणु MIPI_CSIS_INT_SRC_FRAME_START,	"Frame Start" पूर्ण,
	अणु MIPI_CSIS_INT_SRC_FRAME_END,		"Frame End" पूर्ण,
पूर्ण;

#घोषणा MIPI_CSIS_NUM_EVENTS ARRAY_SIZE(mipi_csis_events)

क्रमागत mipi_csis_clk अणु
	MIPI_CSIS_CLK_PCLK,
	MIPI_CSIS_CLK_WRAP,
	MIPI_CSIS_CLK_PHY,
पूर्ण;

अटल स्थिर अक्षर * स्थिर mipi_csis_clk_id[] = अणु
	"pclk",
	"wrap",
	"phy",
पूर्ण;

काष्ठा csis_hw_reset अणु
	काष्ठा regmap *src;
	u8 req_src;
	u8 rst_bit;
पूर्ण;

काष्ठा csi_state अणु
	/* lock elements below */
	काष्ठा mutex lock;
	/* lock क्रम event handler */
	spinlock_t slock;
	काष्ठा device *dev;
	काष्ठा media_pad pads[CSIS_PADS_NUM];
	काष्ठा v4l2_subdev mipi_sd;
	काष्ठा v4l2_async_notअगरier notअगरier;
	काष्ठा v4l2_subdev *src_sd;

	u8 index;
	काष्ठा platक्रमm_device *pdev;
	काष्ठा phy *phy;
	व्योम __iomem *regs;
	पूर्णांक irq;
	u32 flags;

	काष्ठा dentry *debugfs_root;
	bool debug;

	पूर्णांक num_clks;
	काष्ठा clk_bulk_data *clks;

	u32 clk_frequency;
	u32 hs_settle;

	काष्ठा reset_control *mrst;

	स्थिर काष्ठा csis_pix_क्रमmat *csis_fmt;
	काष्ठा v4l2_mbus_framefmt क्रमmat_mbus;

	काष्ठा v4l2_fwnode_bus_mipi_csi2 bus;

	काष्ठा mipi_csis_event events[MIPI_CSIS_NUM_EVENTS];

	काष्ठा csis_hw_reset hw_reset;
	काष्ठा regulator *mipi_phy_regulator;
पूर्ण;

काष्ठा csis_pix_क्रमmat अणु
	u32 code;
	u32 fmt_reg;
	u8 width;
पूर्ण;

अटल स्थिर काष्ठा csis_pix_क्रमmat mipi_csis_क्रमmats[] = अणु
	/* YUV क्रमmats. */
	अणु
		.code = MEDIA_BUS_FMT_UYVY8_1X16,
		.fmt_reg = MIPI_CSIS_ISPCFG_FMT_YCBCR422_8BIT,
		.width = 16,
	पूर्ण,
	/* RAW (Bayer and greyscale) क्रमmats. */
	अणु
		.code = MEDIA_BUS_FMT_SBGGR8_1X8,
		.fmt_reg = MIPI_CSIS_ISPCFG_FMT_RAW8,
		.width = 8,
	पूर्ण, अणु
		.code = MEDIA_BUS_FMT_SGBRG8_1X8,
		.fmt_reg = MIPI_CSIS_ISPCFG_FMT_RAW8,
		.width = 8,
	पूर्ण, अणु
		.code = MEDIA_BUS_FMT_SGRBG8_1X8,
		.fmt_reg = MIPI_CSIS_ISPCFG_FMT_RAW8,
		.width = 8,
	पूर्ण, अणु
		.code = MEDIA_BUS_FMT_SRGGB8_1X8,
		.fmt_reg = MIPI_CSIS_ISPCFG_FMT_RAW8,
		.width = 8,
	पूर्ण, अणु
		.code = MEDIA_BUS_FMT_Y8_1X8,
		.fmt_reg = MIPI_CSIS_ISPCFG_FMT_RAW8,
		.width = 8,
	पूर्ण, अणु
		.code = MEDIA_BUS_FMT_SBGGR10_1X10,
		.fmt_reg = MIPI_CSIS_ISPCFG_FMT_RAW10,
		.width = 10,
	पूर्ण, अणु
		.code = MEDIA_BUS_FMT_SGBRG10_1X10,
		.fmt_reg = MIPI_CSIS_ISPCFG_FMT_RAW10,
		.width = 10,
	पूर्ण, अणु
		.code = MEDIA_BUS_FMT_SGRBG10_1X10,
		.fmt_reg = MIPI_CSIS_ISPCFG_FMT_RAW10,
		.width = 10,
	पूर्ण, अणु
		.code = MEDIA_BUS_FMT_SRGGB10_1X10,
		.fmt_reg = MIPI_CSIS_ISPCFG_FMT_RAW10,
		.width = 10,
	पूर्ण, अणु
		.code = MEDIA_BUS_FMT_Y10_1X10,
		.fmt_reg = MIPI_CSIS_ISPCFG_FMT_RAW10,
		.width = 10,
	पूर्ण, अणु
		.code = MEDIA_BUS_FMT_SBGGR12_1X12,
		.fmt_reg = MIPI_CSIS_ISPCFG_FMT_RAW12,
		.width = 12,
	पूर्ण, अणु
		.code = MEDIA_BUS_FMT_SGBRG12_1X12,
		.fmt_reg = MIPI_CSIS_ISPCFG_FMT_RAW12,
		.width = 12,
	पूर्ण, अणु
		.code = MEDIA_BUS_FMT_SGRBG12_1X12,
		.fmt_reg = MIPI_CSIS_ISPCFG_FMT_RAW12,
		.width = 12,
	पूर्ण, अणु
		.code = MEDIA_BUS_FMT_SRGGB12_1X12,
		.fmt_reg = MIPI_CSIS_ISPCFG_FMT_RAW12,
		.width = 12,
	पूर्ण, अणु
		.code = MEDIA_BUS_FMT_Y12_1X12,
		.fmt_reg = MIPI_CSIS_ISPCFG_FMT_RAW12,
		.width = 12,
	पूर्ण, अणु
		.code = MEDIA_BUS_FMT_SBGGR14_1X14,
		.fmt_reg = MIPI_CSIS_ISPCFG_FMT_RAW14,
		.width = 14,
	पूर्ण, अणु
		.code = MEDIA_BUS_FMT_SGBRG14_1X14,
		.fmt_reg = MIPI_CSIS_ISPCFG_FMT_RAW14,
		.width = 14,
	पूर्ण, अणु
		.code = MEDIA_BUS_FMT_SGRBG14_1X14,
		.fmt_reg = MIPI_CSIS_ISPCFG_FMT_RAW14,
		.width = 14,
	पूर्ण, अणु
		.code = MEDIA_BUS_FMT_SRGGB14_1X14,
		.fmt_reg = MIPI_CSIS_ISPCFG_FMT_RAW14,
		.width = 14,
	पूर्ण
पूर्ण;

अटल अंतरभूत व्योम mipi_csis_ग_लिखो(काष्ठा csi_state *state, u32 reg, u32 val)
अणु
	ग_लिखोl(val, state->regs + reg);
पूर्ण

अटल अंतरभूत u32 mipi_csis_पढ़ो(काष्ठा csi_state *state, u32 reg)
अणु
	वापस पढ़ोl(state->regs + reg);
पूर्ण

अटल पूर्णांक mipi_csis_dump_regs(काष्ठा csi_state *state)
अणु
	काष्ठा device *dev = &state->pdev->dev;
	अचिन्हित पूर्णांक i;
	u32 cfg;
	अटल स्थिर काष्ठा अणु
		u32 offset;
		स्थिर अक्षर * स्थिर name;
	पूर्ण रेजिस्टरs[] = अणु
		अणु MIPI_CSIS_CMN_CTRL, "CMN_CTRL" पूर्ण,
		अणु MIPI_CSIS_CLK_CTRL, "CLK_CTRL" पूर्ण,
		अणु MIPI_CSIS_INT_MSK, "INT_MSK" पूर्ण,
		अणु MIPI_CSIS_DPHY_STATUS, "DPHY_STATUS" पूर्ण,
		अणु MIPI_CSIS_DPHY_CMN_CTRL, "DPHY_CMN_CTRL" पूर्ण,
		अणु MIPI_CSIS_DPHY_SCTRL_L, "DPHY_SCTRL_L" पूर्ण,
		अणु MIPI_CSIS_DPHY_SCTRL_H, "DPHY_SCTRL_H" पूर्ण,
		अणु MIPI_CSIS_ISP_CONFIG_CH(0), "ISP_CONFIG_CH0" पूर्ण,
		अणु MIPI_CSIS_ISP_RESOL_CH(0), "ISP_RESOL_CH0" पूर्ण,
		अणु MIPI_CSIS_SDW_CONFIG_CH(0), "SDW_CONFIG_CH0" पूर्ण,
		अणु MIPI_CSIS_SDW_RESOL_CH(0), "SDW_RESOL_CH0" पूर्ण,
		अणु MIPI_CSIS_DBG_CTRL, "DBG_CTRL" पूर्ण,
	पूर्ण;

	dev_info(dev, "--- REGISTERS ---\n");

	क्रम (i = 0; i < ARRAY_SIZE(रेजिस्टरs); i++) अणु
		cfg = mipi_csis_पढ़ो(state, रेजिस्टरs[i].offset);
		dev_info(dev, "%14s: 0x%08x\n", रेजिस्टरs[i].name, cfg);
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा csi_state *
mipi_notअगरier_to_csis_state(काष्ठा v4l2_async_notअगरier *n)
अणु
	वापस container_of(n, काष्ठा csi_state, notअगरier);
पूर्ण

अटल काष्ठा csi_state *mipi_sd_to_csis_state(काष्ठा v4l2_subdev *sdev)
अणु
	वापस container_of(sdev, काष्ठा csi_state, mipi_sd);
पूर्ण

अटल स्थिर काष्ठा csis_pix_क्रमmat *find_csis_क्रमmat(u32 code)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(mipi_csis_क्रमmats); i++)
		अगर (code == mipi_csis_क्रमmats[i].code)
			वापस &mipi_csis_क्रमmats[i];
	वापस शून्य;
पूर्ण

अटल व्योम mipi_csis_enable_पूर्णांकerrupts(काष्ठा csi_state *state, bool on)
अणु
	mipi_csis_ग_लिखो(state, MIPI_CSIS_INT_MSK, on ? 0xffffffff : 0);
पूर्ण

अटल व्योम mipi_csis_sw_reset(काष्ठा csi_state *state)
अणु
	u32 val = mipi_csis_पढ़ो(state, MIPI_CSIS_CMN_CTRL);

	mipi_csis_ग_लिखो(state, MIPI_CSIS_CMN_CTRL,
			val | MIPI_CSIS_CMN_CTRL_RESET);
	usleep_range(10, 20);
पूर्ण

अटल पूर्णांक mipi_csis_phy_init(काष्ठा csi_state *state)
अणु
	state->mipi_phy_regulator = devm_regulator_get(state->dev, "phy");
	अगर (IS_ERR(state->mipi_phy_regulator))
		वापस PTR_ERR(state->mipi_phy_regulator);

	वापस regulator_set_voltage(state->mipi_phy_regulator, 1000000,
				     1000000);
पूर्ण

अटल व्योम mipi_csis_phy_reset(काष्ठा csi_state *state)
अणु
	reset_control_निश्चित(state->mrst);

	msleep(20);

	reset_control_deनिश्चित(state->mrst);
पूर्ण

अटल व्योम mipi_csis_प्रणाली_enable(काष्ठा csi_state *state, पूर्णांक on)
अणु
	u32 val, mask;

	val = mipi_csis_पढ़ो(state, MIPI_CSIS_CMN_CTRL);
	अगर (on)
		val |= MIPI_CSIS_CMN_CTRL_ENABLE;
	अन्यथा
		val &= ~MIPI_CSIS_CMN_CTRL_ENABLE;
	mipi_csis_ग_लिखो(state, MIPI_CSIS_CMN_CTRL, val);

	val = mipi_csis_पढ़ो(state, MIPI_CSIS_DPHY_CMN_CTRL);
	val &= ~MIPI_CSIS_DPHY_CMN_CTRL_ENABLE;
	अगर (on) अणु
		mask = (1 << (state->bus.num_data_lanes + 1)) - 1;
		val |= (mask & MIPI_CSIS_DPHY_CMN_CTRL_ENABLE);
	पूर्ण
	mipi_csis_ग_लिखो(state, MIPI_CSIS_DPHY_CMN_CTRL, val);
पूर्ण

/* Called with the state.lock mutex held */
अटल व्योम __mipi_csis_set_क्रमmat(काष्ठा csi_state *state)
अणु
	काष्ठा v4l2_mbus_framefmt *mf = &state->क्रमmat_mbus;
	u32 val;

	/* Color क्रमmat */
	val = mipi_csis_पढ़ो(state, MIPI_CSIS_ISP_CONFIG_CH(0));
	val &= ~(MIPI_CSIS_ISPCFG_ALIGN_32BIT | MIPI_CSIS_ISPCFG_FMT_MASK);
	val |= state->csis_fmt->fmt_reg;
	mipi_csis_ग_लिखो(state, MIPI_CSIS_ISP_CONFIG_CH(0), val);

	/* Pixel resolution */
	val = mf->width | (mf->height << 16);
	mipi_csis_ग_लिखो(state, MIPI_CSIS_ISP_RESOL_CH(0), val);
पूर्ण

अटल पूर्णांक mipi_csis_calculate_params(काष्ठा csi_state *state)
अणु
	s64 link_freq;
	u32 lane_rate;

	/* Calculate the line rate from the pixel rate. */
	link_freq = v4l2_get_link_freq(state->src_sd->ctrl_handler,
				       state->csis_fmt->width,
				       state->bus.num_data_lanes * 2);
	अगर (link_freq < 0) अणु
		dev_err(state->dev, "Unable to obtain link frequency: %d\n",
			(पूर्णांक)link_freq);
		वापस link_freq;
	पूर्ण

	lane_rate = link_freq * 2;

	अगर (lane_rate < 80000000 || lane_rate > 1500000000) अणु
		dev_dbg(state->dev, "Out-of-bound lane rate %u\n", lane_rate);
		वापस -EINVAL;
	पूर्ण

	/*
	 * The HSSETTLE counter value is करोcument in a table, but can also
	 * easily be calculated.
	 */
	state->hs_settle = (lane_rate - 5000000) / 45000000;
	dev_dbg(state->dev, "lane rate %u, Ths_settle %u\n",
		lane_rate, state->hs_settle);

	वापस 0;
पूर्ण

अटल व्योम mipi_csis_set_params(काष्ठा csi_state *state)
अणु
	पूर्णांक lanes = state->bus.num_data_lanes;
	u32 val;

	val = mipi_csis_पढ़ो(state, MIPI_CSIS_CMN_CTRL);
	val &= ~MIPI_CSIS_CMN_CTRL_LANE_NR_MASK;
	val |= (lanes - 1) << MIPI_CSIS_CMN_CTRL_LANE_NR_OFFSET;
	val |= MIPI_CSIS_CMN_CTRL_INTER_MODE;
	mipi_csis_ग_लिखो(state, MIPI_CSIS_CMN_CTRL, val);

	__mipi_csis_set_क्रमmat(state);

	mipi_csis_ग_लिखो(state, MIPI_CSIS_DPHY_CMN_CTRL,
			MIPI_CSIS_DPHY_CMN_CTRL_HSSETTLE(state->hs_settle));

	val = (0 << MIPI_CSIS_ISP_SYNC_HSYNC_LINTV_OFFSET)
	    | (0 << MIPI_CSIS_ISP_SYNC_VSYNC_SINTV_OFFSET)
	    | (0 << MIPI_CSIS_ISP_SYNC_VSYNC_EINTV_OFFSET);
	mipi_csis_ग_लिखो(state, MIPI_CSIS_ISP_SYNC_CH(0), val);

	val = mipi_csis_पढ़ो(state, MIPI_CSIS_CLK_CTRL);
	val |= MIPI_CSIS_CLK_CTRL_WCLK_SRC;
	val |= MIPI_CSIS_CLK_CTRL_CLKGATE_TRAIL_CH0(15);
	val &= ~MIPI_CSIS_CLK_CTRL_CLKGATE_EN_MSK;
	mipi_csis_ग_लिखो(state, MIPI_CSIS_CLK_CTRL, val);

	mipi_csis_ग_लिखो(state, MIPI_CSIS_DPHY_BCTRL_L,
			MIPI_CSIS_DPHY_BCTRL_L_BIAS_REF_VOLT_715MV |
			MIPI_CSIS_DPHY_BCTRL_L_BGR_CHOPPER_FREQ_3MHZ |
			MIPI_CSIS_DPHY_BCTRL_L_REG_12P_LVL_CTL_1_2V |
			MIPI_CSIS_DPHY_BCTRL_L_LP_RX_HYS_LVL_80MV |
			MIPI_CSIS_DPHY_BCTRL_L_LP_RX_VREF_LVL_715MV |
			MIPI_CSIS_DPHY_BCTRL_L_LP_CD_HYS_60MV |
			MIPI_CSIS_DPHY_BCTRL_L_B_DPHYCTRL(20000000));
	mipi_csis_ग_लिखो(state, MIPI_CSIS_DPHY_BCTRL_H, 0);

	/* Update the shaकरोw रेजिस्टर. */
	val = mipi_csis_पढ़ो(state, MIPI_CSIS_CMN_CTRL);
	mipi_csis_ग_लिखो(state, MIPI_CSIS_CMN_CTRL,
			val | MIPI_CSIS_CMN_CTRL_UPDATE_SHADOW |
			MIPI_CSIS_CMN_CTRL_UPDATE_SHADOW_CTRL);
पूर्ण

अटल पूर्णांक mipi_csis_clk_enable(काष्ठा csi_state *state)
अणु
	वापस clk_bulk_prepare_enable(state->num_clks, state->clks);
पूर्ण

अटल व्योम mipi_csis_clk_disable(काष्ठा csi_state *state)
अणु
	clk_bulk_disable_unprepare(state->num_clks, state->clks);
पूर्ण

अटल पूर्णांक mipi_csis_clk_get(काष्ठा csi_state *state)
अणु
	काष्ठा device *dev = &state->pdev->dev;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	state->num_clks = ARRAY_SIZE(mipi_csis_clk_id);
	state->clks = devm_kसुस्मृति(dev, state->num_clks, माप(*state->clks),
				   GFP_KERNEL);

	अगर (!state->clks)
		वापस -ENOMEM;

	क्रम (i = 0; i < state->num_clks; i++)
		state->clks[i].id = mipi_csis_clk_id[i];

	ret = devm_clk_bulk_get(dev, state->num_clks, state->clks);
	अगर (ret < 0)
		वापस ret;

	/* Set घड़ी rate */
	ret = clk_set_rate(state->clks[MIPI_CSIS_CLK_WRAP].clk,
			   state->clk_frequency);
	अगर (ret < 0)
		dev_err(dev, "set rate=%d failed: %d\n", state->clk_frequency,
			ret);

	वापस ret;
पूर्ण

अटल व्योम mipi_csis_start_stream(काष्ठा csi_state *state)
अणु
	mipi_csis_sw_reset(state);
	mipi_csis_set_params(state);
	mipi_csis_प्रणाली_enable(state, true);
	mipi_csis_enable_पूर्णांकerrupts(state, true);
पूर्ण

अटल व्योम mipi_csis_stop_stream(काष्ठा csi_state *state)
अणु
	mipi_csis_enable_पूर्णांकerrupts(state, false);
	mipi_csis_प्रणाली_enable(state, false);
पूर्ण

अटल व्योम mipi_csis_clear_counters(काष्ठा csi_state *state)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक i;

	spin_lock_irqsave(&state->slock, flags);
	क्रम (i = 0; i < MIPI_CSIS_NUM_EVENTS; i++)
		state->events[i].counter = 0;
	spin_unlock_irqrestore(&state->slock, flags);
पूर्ण

अटल व्योम mipi_csis_log_counters(काष्ठा csi_state *state, bool non_errors)
अणु
	पूर्णांक i = non_errors ? MIPI_CSIS_NUM_EVENTS : MIPI_CSIS_NUM_EVENTS - 4;
	काष्ठा device *dev = &state->pdev->dev;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&state->slock, flags);

	क्रम (i--; i >= 0; i--) अणु
		अगर (state->events[i].counter > 0 || state->debug)
			dev_info(dev, "%s events: %d\n", state->events[i].name,
				 state->events[i].counter);
	पूर्ण
	spin_unlock_irqrestore(&state->slock, flags);
पूर्ण

/*
 * V4L2 subdev operations
 */
अटल पूर्णांक mipi_csis_s_stream(काष्ठा v4l2_subdev *mipi_sd, पूर्णांक enable)
अणु
	काष्ठा csi_state *state = mipi_sd_to_csis_state(mipi_sd);
	पूर्णांक ret;

	अगर (enable) अणु
		ret = mipi_csis_calculate_params(state);
		अगर (ret < 0)
			वापस ret;

		mipi_csis_clear_counters(state);

		ret = pm_runसमय_get_sync(&state->pdev->dev);
		अगर (ret < 0) अणु
			pm_runसमय_put_noidle(&state->pdev->dev);
			वापस ret;
		पूर्ण
		ret = v4l2_subdev_call(state->src_sd, core, s_घातer, 1);
		अगर (ret < 0 && ret != -ENOIOCTLCMD)
			जाओ करोne;
	पूर्ण

	mutex_lock(&state->lock);

	अगर (enable) अणु
		अगर (state->flags & ST_SUSPENDED) अणु
			ret = -EBUSY;
			जाओ unlock;
		पूर्ण

		mipi_csis_start_stream(state);
		ret = v4l2_subdev_call(state->src_sd, video, s_stream, 1);
		अगर (ret < 0)
			जाओ unlock;

		mipi_csis_log_counters(state, true);

		state->flags |= ST_STREAMING;
	पूर्ण अन्यथा अणु
		v4l2_subdev_call(state->src_sd, video, s_stream, 0);
		ret = v4l2_subdev_call(state->src_sd, core, s_घातer, 0);
		अगर (ret == -ENOIOCTLCMD)
			ret = 0;
		mipi_csis_stop_stream(state);
		state->flags &= ~ST_STREAMING;
		अगर (state->debug)
			mipi_csis_log_counters(state, true);
	पूर्ण

unlock:
	mutex_unlock(&state->lock);

करोne:
	अगर (!enable || ret < 0)
		pm_runसमय_put(&state->pdev->dev);

	वापस ret;
पूर्ण

अटल पूर्णांक mipi_csis_link_setup(काष्ठा media_entity *entity,
				स्थिर काष्ठा media_pad *local_pad,
				स्थिर काष्ठा media_pad *remote_pad, u32 flags)
अणु
	काष्ठा v4l2_subdev *mipi_sd = media_entity_to_v4l2_subdev(entity);
	काष्ठा csi_state *state = mipi_sd_to_csis_state(mipi_sd);
	काष्ठा v4l2_subdev *remote_sd;

	dev_dbg(state->dev, "link setup %s -> %s", remote_pad->entity->name,
		local_pad->entity->name);

	/* We only care about the link to the source. */
	अगर (!(local_pad->flags & MEDIA_PAD_FL_SINK))
		वापस 0;

	remote_sd = media_entity_to_v4l2_subdev(remote_pad->entity);

	अगर (flags & MEDIA_LNK_FL_ENABLED) अणु
		अगर (state->src_sd)
			वापस -EBUSY;

		state->src_sd = remote_sd;
	पूर्ण अन्यथा अणु
		state->src_sd = शून्य;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा v4l2_mbus_framefmt *
mipi_csis_get_क्रमmat(काष्ठा csi_state *state,
		     काष्ठा v4l2_subdev_pad_config *cfg,
		     क्रमागत v4l2_subdev_क्रमmat_whence which,
		     अचिन्हित पूर्णांक pad)
अणु
	अगर (which == V4L2_SUBDEV_FORMAT_TRY)
		वापस v4l2_subdev_get_try_क्रमmat(&state->mipi_sd, cfg, pad);

	वापस &state->क्रमmat_mbus;
पूर्ण

अटल पूर्णांक mipi_csis_init_cfg(काष्ठा v4l2_subdev *mipi_sd,
			      काष्ठा v4l2_subdev_pad_config *cfg)
अणु
	काष्ठा csi_state *state = mipi_sd_to_csis_state(mipi_sd);
	काष्ठा v4l2_mbus_framefmt *fmt_sink;
	काष्ठा v4l2_mbus_framefmt *fmt_source;
	क्रमागत v4l2_subdev_क्रमmat_whence which;

	which = cfg ? V4L2_SUBDEV_FORMAT_TRY : V4L2_SUBDEV_FORMAT_ACTIVE;
	fmt_sink = mipi_csis_get_क्रमmat(state, cfg, which, CSIS_PAD_SINK);

	fmt_sink->code = MEDIA_BUS_FMT_UYVY8_1X16;
	fmt_sink->width = MIPI_CSIS_DEF_PIX_WIDTH;
	fmt_sink->height = MIPI_CSIS_DEF_PIX_HEIGHT;
	fmt_sink->field = V4L2_FIELD_NONE;

	fmt_sink->colorspace = V4L2_COLORSPACE_SMPTE170M;
	fmt_sink->xfer_func = V4L2_MAP_XFER_FUNC_DEFAULT(fmt_sink->colorspace);
	fmt_sink->ycbcr_enc = V4L2_MAP_YCBCR_ENC_DEFAULT(fmt_sink->colorspace);
	fmt_sink->quantization =
		V4L2_MAP_QUANTIZATION_DEFAULT(false, fmt_sink->colorspace,
					      fmt_sink->ycbcr_enc);

	/*
	 * When called from mipi_csis_subdev_init() to initialize the active
	 * configuration, cfg is शून्य, which indicates there's no source pad
	 * configuration to set.
	 */
	अगर (!cfg)
		वापस 0;

	fmt_source = mipi_csis_get_क्रमmat(state, cfg, which, CSIS_PAD_SOURCE);
	*fmt_source = *fmt_sink;

	वापस 0;
पूर्ण

अटल पूर्णांक mipi_csis_get_fmt(काष्ठा v4l2_subdev *mipi_sd,
			     काष्ठा v4l2_subdev_pad_config *cfg,
			     काष्ठा v4l2_subdev_क्रमmat *sdक्रमmat)
अणु
	काष्ठा csi_state *state = mipi_sd_to_csis_state(mipi_sd);
	काष्ठा v4l2_mbus_framefmt *fmt;

	mutex_lock(&state->lock);
	fmt = mipi_csis_get_क्रमmat(state, cfg, sdक्रमmat->which, sdक्रमmat->pad);
	sdक्रमmat->क्रमmat = *fmt;
	mutex_unlock(&state->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक mipi_csis_क्रमागत_mbus_code(काष्ठा v4l2_subdev *mipi_sd,
				    काष्ठा v4l2_subdev_pad_config *cfg,
				    काष्ठा v4l2_subdev_mbus_code_क्रमागत *code)
अणु
	काष्ठा csi_state *state = mipi_sd_to_csis_state(mipi_sd);

	/*
	 * The CSIS can't transcode in any way, the source क्रमmat is identical
	 * to the sink क्रमmat.
	 */
	अगर (code->pad == CSIS_PAD_SOURCE) अणु
		काष्ठा v4l2_mbus_framefmt *fmt;

		अगर (code->index > 0)
			वापस -EINVAL;

		fmt = mipi_csis_get_क्रमmat(state, cfg, code->which, code->pad);
		code->code = fmt->code;
		वापस 0;
	पूर्ण

	अगर (code->pad != CSIS_PAD_SINK)
		वापस -EINVAL;

	अगर (code->index >= ARRAY_SIZE(mipi_csis_क्रमmats))
		वापस -EINVAL;

	code->code = mipi_csis_क्रमmats[code->index].code;

	वापस 0;
पूर्ण

अटल पूर्णांक mipi_csis_set_fmt(काष्ठा v4l2_subdev *mipi_sd,
			     काष्ठा v4l2_subdev_pad_config *cfg,
			     काष्ठा v4l2_subdev_क्रमmat *sdक्रमmat)
अणु
	काष्ठा csi_state *state = mipi_sd_to_csis_state(mipi_sd);
	काष्ठा csis_pix_क्रमmat स्थिर *csis_fmt;
	काष्ठा v4l2_mbus_framefmt *fmt;
	अचिन्हित पूर्णांक align;

	/*
	 * The CSIS can't transcode in any way, the source format can't be
	 * modअगरied.
	 */
	अगर (sdक्रमmat->pad == CSIS_PAD_SOURCE)
		वापस mipi_csis_get_fmt(mipi_sd, cfg, sdक्रमmat);

	अगर (sdक्रमmat->pad != CSIS_PAD_SINK)
		वापस -EINVAL;

	fmt = mipi_csis_get_क्रमmat(state, cfg, sdक्रमmat->which, sdक्रमmat->pad);

	mutex_lock(&state->lock);

	/* Validate the media bus code and clamp the size. */
	csis_fmt = find_csis_क्रमmat(sdक्रमmat->क्रमmat.code);
	अगर (!csis_fmt)
		csis_fmt = &mipi_csis_क्रमmats[0];

	fmt->code = csis_fmt->code;
	fmt->width = sdक्रमmat->क्रमmat.width;
	fmt->height = sdक्रमmat->क्रमmat.height;

	/*
	 * The total number of bits per line must be a multiple of 8. We thus
	 * need to align the width क्रम क्रमmats that are not multiples of 8
	 * bits.
	 */
	चयन (csis_fmt->width % 8) अणु
	हाल 0:
		align = 0;
		अवरोध;
	हाल 4:
		align = 1;
		अवरोध;
	हाल 2:
	हाल 6:
		align = 2;
		अवरोध;
	हाल 1:
	हाल 3:
	हाल 5:
	हाल 7:
		align = 3;
		अवरोध;
	पूर्ण

	v4l_bound_align_image(&fmt->width, 1, CSIS_MAX_PIX_WIDTH, align,
			      &fmt->height, 1, CSIS_MAX_PIX_HEIGHT, 0, 0);

	sdक्रमmat->क्रमmat = *fmt;

	/* Propagate the क्रमmat from sink to source. */
	fmt = mipi_csis_get_क्रमmat(state, cfg, sdक्रमmat->which,
				   CSIS_PAD_SOURCE);
	*fmt = sdक्रमmat->क्रमmat;

	/* Store the CSIS क्रमmat descriptor क्रम active क्रमmats. */
	अगर (sdक्रमmat->which == V4L2_SUBDEV_FORMAT_ACTIVE)
		state->csis_fmt = csis_fmt;

	mutex_unlock(&state->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक mipi_csis_log_status(काष्ठा v4l2_subdev *mipi_sd)
अणु
	काष्ठा csi_state *state = mipi_sd_to_csis_state(mipi_sd);

	mutex_lock(&state->lock);
	mipi_csis_log_counters(state, true);
	अगर (state->debug && (state->flags & ST_POWERED))
		mipi_csis_dump_regs(state);
	mutex_unlock(&state->lock);

	वापस 0;
पूर्ण

अटल irqवापस_t mipi_csis_irq_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा csi_state *state = dev_id;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक i;
	u32 status;

	status = mipi_csis_पढ़ो(state, MIPI_CSIS_INT_SRC);

	spin_lock_irqsave(&state->slock, flags);

	/* Update the event/error counters */
	अगर ((status & MIPI_CSIS_INT_SRC_ERRORS) || state->debug) अणु
		क्रम (i = 0; i < MIPI_CSIS_NUM_EVENTS; i++) अणु
			अगर (!(status & state->events[i].mask))
				जारी;
			state->events[i].counter++;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&state->slock, flags);

	mipi_csis_ग_लिखो(state, MIPI_CSIS_INT_SRC, status);

	वापस IRQ_HANDLED;
पूर्ण

अटल स्थिर काष्ठा v4l2_subdev_core_ops mipi_csis_core_ops = अणु
	.log_status	= mipi_csis_log_status,
पूर्ण;

अटल स्थिर काष्ठा media_entity_operations mipi_csis_entity_ops = अणु
	.link_setup	= mipi_csis_link_setup,
	.link_validate	= v4l2_subdev_link_validate,
	.get_fwnode_pad = v4l2_subdev_get_fwnode_pad_1_to_1,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_video_ops mipi_csis_video_ops = अणु
	.s_stream	= mipi_csis_s_stream,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_pad_ops mipi_csis_pad_ops = अणु
	.init_cfg		= mipi_csis_init_cfg,
	.क्रमागत_mbus_code		= mipi_csis_क्रमागत_mbus_code,
	.get_fmt		= mipi_csis_get_fmt,
	.set_fmt		= mipi_csis_set_fmt,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ops mipi_csis_subdev_ops = अणु
	.core	= &mipi_csis_core_ops,
	.video	= &mipi_csis_video_ops,
	.pad	= &mipi_csis_pad_ops,
पूर्ण;

अटल पूर्णांक mipi_csis_parse_dt(काष्ठा platक्रमm_device *pdev,
			      काष्ठा csi_state *state)
अणु
	काष्ठा device_node *node = pdev->dev.of_node;

	अगर (of_property_पढ़ो_u32(node, "clock-frequency",
				 &state->clk_frequency))
		state->clk_frequency = DEFAULT_SCLK_CSIS_FREQ;

	/* Get MIPI PHY resets */
	state->mrst = devm_reset_control_get_exclusive(&pdev->dev, शून्य);
	अगर (IS_ERR(state->mrst))
		वापस PTR_ERR(state->mrst);

	वापस 0;
पूर्ण

अटल पूर्णांक mipi_csis_pm_resume(काष्ठा device *dev, bool runसमय);

अटल पूर्णांक mipi_csis_notअगरy_bound(काष्ठा v4l2_async_notअगरier *notअगरier,
				  काष्ठा v4l2_subdev *sd,
				  काष्ठा v4l2_async_subdev *asd)
अणु
	काष्ठा csi_state *state = mipi_notअगरier_to_csis_state(notअगरier);
	काष्ठा media_pad *sink = &state->mipi_sd.entity.pads[CSIS_PAD_SINK];

	वापस v4l2_create_fwnode_links_to_pad(sd, sink, 0);
पूर्ण

अटल स्थिर काष्ठा v4l2_async_notअगरier_operations mipi_csis_notअगरy_ops = अणु
	.bound = mipi_csis_notअगरy_bound,
पूर्ण;

अटल पूर्णांक mipi_csis_subdev_init(काष्ठा v4l2_subdev *mipi_sd,
				 काष्ठा platक्रमm_device *pdev,
				 स्थिर काष्ठा v4l2_subdev_ops *ops)
अणु
	काष्ठा csi_state *state = mipi_sd_to_csis_state(mipi_sd);

	v4l2_subdev_init(mipi_sd, ops);
	mipi_sd->owner = THIS_MODULE;
	snम_लिखो(mipi_sd->name, माप(mipi_sd->name), "%s.%d",
		 CSIS_SUBDEV_NAME, state->index);

	mipi_sd->flags |= V4L2_SUBDEV_FL_HAS_DEVNODE;
	mipi_sd->ctrl_handler = शून्य;

	mipi_sd->entity.function = MEDIA_ENT_F_VID_IF_BRIDGE;
	mipi_sd->entity.ops = &mipi_csis_entity_ops;

	mipi_sd->dev = &pdev->dev;

	state->csis_fmt = &mipi_csis_क्रमmats[0];
	mipi_csis_init_cfg(mipi_sd, शून्य);

	v4l2_set_subdevdata(mipi_sd, &pdev->dev);

	state->pads[CSIS_PAD_SINK].flags = MEDIA_PAD_FL_SINK
					 | MEDIA_PAD_FL_MUST_CONNECT;
	state->pads[CSIS_PAD_SOURCE].flags = MEDIA_PAD_FL_SOURCE
					   | MEDIA_PAD_FL_MUST_CONNECT;
	वापस media_entity_pads_init(&mipi_sd->entity, CSIS_PADS_NUM,
				      state->pads);
पूर्ण

अटल पूर्णांक mipi_csis_async_रेजिस्टर(काष्ठा csi_state *state)
अणु
	काष्ठा v4l2_fwnode_endpoपूर्णांक vep = अणु
		.bus_type = V4L2_MBUS_CSI2_DPHY,
	पूर्ण;
	काष्ठा v4l2_async_subdev *asd;
	काष्ठा fwnode_handle *ep;
	पूर्णांक ret;

	v4l2_async_notअगरier_init(&state->notअगरier);

	ep = fwnode_graph_get_endpoपूर्णांक_by_id(dev_fwnode(state->dev), 0, 0,
					     FWNODE_GRAPH_ENDPOINT_NEXT);
	अगर (!ep)
		वापस -ENOTCONN;

	ret = v4l2_fwnode_endpoपूर्णांक_parse(ep, &vep);
	अगर (ret)
		जाओ err_parse;

	state->bus = vep.bus.mipi_csi2;

	dev_dbg(state->dev, "data lanes: %d\n", state->bus.num_data_lanes);
	dev_dbg(state->dev, "flags: 0x%08x\n", state->bus.flags);

	asd = v4l2_async_notअगरier_add_fwnode_remote_subdev(
		&state->notअगरier, ep, काष्ठा v4l2_async_subdev);
	अगर (IS_ERR(asd)) अणु
		ret = PTR_ERR(asd);
		जाओ err_parse;
	पूर्ण

	fwnode_handle_put(ep);

	state->notअगरier.ops = &mipi_csis_notअगरy_ops;

	ret = v4l2_async_subdev_notअगरier_रेजिस्टर(&state->mipi_sd,
						  &state->notअगरier);
	अगर (ret)
		वापस ret;

	वापस v4l2_async_रेजिस्टर_subdev(&state->mipi_sd);

err_parse:
	fwnode_handle_put(ep);

	वापस ret;
पूर्ण

अटल पूर्णांक mipi_csis_dump_regs_show(काष्ठा seq_file *m, व्योम *निजी)
अणु
	काष्ठा csi_state *state = m->निजी;

	वापस mipi_csis_dump_regs(state);
पूर्ण
DEFINE_SHOW_ATTRIBUTE(mipi_csis_dump_regs);

अटल व्योम mipi_csis_debugfs_init(काष्ठा csi_state *state)
अणु
	state->debugfs_root = debugfs_create_dir(dev_name(state->dev), शून्य);

	debugfs_create_bool("debug_enable", 0600, state->debugfs_root,
			    &state->debug);
	debugfs_create_file("dump_regs", 0600, state->debugfs_root, state,
			    &mipi_csis_dump_regs_fops);
पूर्ण

अटल व्योम mipi_csis_debugfs_निकास(काष्ठा csi_state *state)
अणु
	debugfs_हटाओ_recursive(state->debugfs_root);
पूर्ण

अटल पूर्णांक mipi_csis_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा csi_state *state;
	पूर्णांक ret;

	state = devm_kzalloc(dev, माप(*state), GFP_KERNEL);
	अगर (!state)
		वापस -ENOMEM;

	spin_lock_init(&state->slock);

	state->pdev = pdev;
	state->dev = dev;

	ret = mipi_csis_parse_dt(pdev, state);
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to parse device tree: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = mipi_csis_phy_init(state);
	अगर (ret < 0)
		वापस ret;

	mipi_csis_phy_reset(state);

	state->regs = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(state->regs))
		वापस PTR_ERR(state->regs);

	state->irq = platक्रमm_get_irq(pdev, 0);
	अगर (state->irq < 0)
		वापस state->irq;

	ret = mipi_csis_clk_get(state);
	अगर (ret < 0)
		वापस ret;

	ret = mipi_csis_clk_enable(state);
	अगर (ret < 0) अणु
		dev_err(state->dev, "failed to enable clocks: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = devm_request_irq(dev, state->irq, mipi_csis_irq_handler,
			       0, dev_name(dev), state);
	अगर (ret) अणु
		dev_err(dev, "Interrupt request failed\n");
		जाओ disable_घड़ी;
	पूर्ण

	platक्रमm_set_drvdata(pdev, &state->mipi_sd);

	mutex_init(&state->lock);
	ret = mipi_csis_subdev_init(&state->mipi_sd, pdev,
				    &mipi_csis_subdev_ops);
	अगर (ret < 0)
		जाओ disable_घड़ी;

	ret = mipi_csis_async_रेजिस्टर(state);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "async register failed: %d\n", ret);
		जाओ cleanup;
	पूर्ण

	स_नकल(state->events, mipi_csis_events, माप(state->events));

	mipi_csis_debugfs_init(state);
	pm_runसमय_enable(dev);
	अगर (!pm_runसमय_enabled(dev)) अणु
		ret = mipi_csis_pm_resume(dev, true);
		अगर (ret < 0)
			जाओ unरेजिस्टर_all;
	पूर्ण

	dev_info(&pdev->dev, "lanes: %d, freq: %u\n",
		 state->bus.num_data_lanes, state->clk_frequency);

	वापस 0;

unरेजिस्टर_all:
	mipi_csis_debugfs_निकास(state);
cleanup:
	media_entity_cleanup(&state->mipi_sd.entity);
	v4l2_async_notअगरier_unरेजिस्टर(&state->notअगरier);
	v4l2_async_notअगरier_cleanup(&state->notअगरier);
	v4l2_async_unरेजिस्टर_subdev(&state->mipi_sd);
disable_घड़ी:
	mipi_csis_clk_disable(state);
	mutex_destroy(&state->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक mipi_csis_pm_suspend(काष्ठा device *dev, bool runसमय)
अणु
	काष्ठा v4l2_subdev *mipi_sd = dev_get_drvdata(dev);
	काष्ठा csi_state *state = mipi_sd_to_csis_state(mipi_sd);
	पूर्णांक ret = 0;

	mutex_lock(&state->lock);
	अगर (state->flags & ST_POWERED) अणु
		mipi_csis_stop_stream(state);
		ret = regulator_disable(state->mipi_phy_regulator);
		अगर (ret)
			जाओ unlock;
		mipi_csis_clk_disable(state);
		state->flags &= ~ST_POWERED;
		अगर (!runसमय)
			state->flags |= ST_SUSPENDED;
	पूर्ण

unlock:
	mutex_unlock(&state->lock);

	वापस ret ? -EAGAIN : 0;
पूर्ण

अटल पूर्णांक mipi_csis_pm_resume(काष्ठा device *dev, bool runसमय)
अणु
	काष्ठा v4l2_subdev *mipi_sd = dev_get_drvdata(dev);
	काष्ठा csi_state *state = mipi_sd_to_csis_state(mipi_sd);
	पूर्णांक ret = 0;

	mutex_lock(&state->lock);
	अगर (!runसमय && !(state->flags & ST_SUSPENDED))
		जाओ unlock;

	अगर (!(state->flags & ST_POWERED)) अणु
		ret = regulator_enable(state->mipi_phy_regulator);
		अगर (ret)
			जाओ unlock;

		state->flags |= ST_POWERED;
		mipi_csis_clk_enable(state);
	पूर्ण
	अगर (state->flags & ST_STREAMING)
		mipi_csis_start_stream(state);

	state->flags &= ~ST_SUSPENDED;

unlock:
	mutex_unlock(&state->lock);

	वापस ret ? -EAGAIN : 0;
पूर्ण

अटल पूर्णांक __maybe_unused mipi_csis_suspend(काष्ठा device *dev)
अणु
	वापस mipi_csis_pm_suspend(dev, false);
पूर्ण

अटल पूर्णांक __maybe_unused mipi_csis_resume(काष्ठा device *dev)
अणु
	वापस mipi_csis_pm_resume(dev, false);
पूर्ण

अटल पूर्णांक __maybe_unused mipi_csis_runसमय_suspend(काष्ठा device *dev)
अणु
	वापस mipi_csis_pm_suspend(dev, true);
पूर्ण

अटल पूर्णांक __maybe_unused mipi_csis_runसमय_resume(काष्ठा device *dev)
अणु
	वापस mipi_csis_pm_resume(dev, true);
पूर्ण

अटल पूर्णांक mipi_csis_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा v4l2_subdev *mipi_sd = platक्रमm_get_drvdata(pdev);
	काष्ठा csi_state *state = mipi_sd_to_csis_state(mipi_sd);

	mipi_csis_debugfs_निकास(state);
	v4l2_async_notअगरier_unरेजिस्टर(&state->notअगरier);
	v4l2_async_notअगरier_cleanup(&state->notअगरier);
	v4l2_async_unरेजिस्टर_subdev(&state->mipi_sd);

	pm_runसमय_disable(&pdev->dev);
	mipi_csis_pm_suspend(&pdev->dev, true);
	mipi_csis_clk_disable(state);
	media_entity_cleanup(&state->mipi_sd.entity);
	mutex_destroy(&state->lock);
	pm_runसमय_set_suspended(&pdev->dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops mipi_csis_pm_ops = अणु
	SET_RUNTIME_PM_OPS(mipi_csis_runसमय_suspend, mipi_csis_runसमय_resume,
			   शून्य)
	SET_SYSTEM_SLEEP_PM_OPS(mipi_csis_suspend, mipi_csis_resume)
पूर्ण;

अटल स्थिर काष्ठा of_device_id mipi_csis_of_match[] = अणु
	अणु .compatible = "fsl,imx7-mipi-csi2", पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, mipi_csis_of_match);

अटल काष्ठा platक्रमm_driver mipi_csis_driver = अणु
	.probe		= mipi_csis_probe,
	.हटाओ		= mipi_csis_हटाओ,
	.driver		= अणु
		.of_match_table = mipi_csis_of_match,
		.name		= CSIS_DRIVER_NAME,
		.pm		= &mipi_csis_pm_ops,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(mipi_csis_driver);

MODULE_DESCRIPTION("i.MX7 MIPI CSI-2 Receiver driver");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:imx7-mipi-csi2");
