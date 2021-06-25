<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Samsung SoC MIPI DSI Master driver.
 *
 * Copyright (c) 2014 Samsung Electronics Co., Ltd
 *
 * Contacts: Tomasz Figa <t.figa@samsung.com>
*/

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/component.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/irq.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/of_graph.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/regulator/consumer.h>

#समावेश <यंत्र/unaligned.h>

#समावेश <video/mipi_display.h>
#समावेश <video/videomode.h>

#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_bridge.h>
#समावेश <drm/drm_fb_helper.h>
#समावेश <drm/drm_mipi_dsi.h>
#समावेश <drm/drm_panel.h>
#समावेश <drm/drm_prपूर्णांक.h>
#समावेश <drm/drm_probe_helper.h>
#समावेश <drm/drm_simple_kms_helper.h>

#समावेश "exynos_drm_crtc.h"
#समावेश "exynos_drm_drv.h"

/* वापसs true अगरf both arguments logically dअगरfers */
#घोषणा NEQV(a, b) (!(a) ^ !(b))

/* DSIM_STATUS */
#घोषणा DSIM_STOP_STATE_DAT(x)		(((x) & 0xf) << 0)
#घोषणा DSIM_STOP_STATE_CLK		(1 << 8)
#घोषणा DSIM_TX_READY_HS_CLK		(1 << 10)
#घोषणा DSIM_PLL_STABLE			(1 << 31)

/* DSIM_SWRST */
#घोषणा DSIM_FUNCRST			(1 << 16)
#घोषणा DSIM_SWRST			(1 << 0)

/* DSIM_TIMEOUT */
#घोषणा DSIM_LPDR_TIMEOUT(x)		((x) << 0)
#घोषणा DSIM_BTA_TIMEOUT(x)		((x) << 16)

/* DSIM_CLKCTRL */
#घोषणा DSIM_ESC_PRESCALER(x)		(((x) & 0xffff) << 0)
#घोषणा DSIM_ESC_PRESCALER_MASK		(0xffff << 0)
#घोषणा DSIM_LANE_ESC_CLK_EN_CLK	(1 << 19)
#घोषणा DSIM_LANE_ESC_CLK_EN_DATA(x)	(((x) & 0xf) << 20)
#घोषणा DSIM_LANE_ESC_CLK_EN_DATA_MASK	(0xf << 20)
#घोषणा DSIM_BYTE_CLKEN			(1 << 24)
#घोषणा DSIM_BYTE_CLK_SRC(x)		(((x) & 0x3) << 25)
#घोषणा DSIM_BYTE_CLK_SRC_MASK		(0x3 << 25)
#घोषणा DSIM_PLL_BYPASS			(1 << 27)
#घोषणा DSIM_ESC_CLKEN			(1 << 28)
#घोषणा DSIM_TX_REQUEST_HSCLK		(1 << 31)

/* DSIM_CONFIG */
#घोषणा DSIM_LANE_EN_CLK		(1 << 0)
#घोषणा DSIM_LANE_EN(x)			(((x) & 0xf) << 1)
#घोषणा DSIM_NUM_OF_DATA_LANE(x)	(((x) & 0x3) << 5)
#घोषणा DSIM_SUB_PIX_FORMAT(x)		(((x) & 0x7) << 8)
#घोषणा DSIM_MAIN_PIX_FORMAT_MASK	(0x7 << 12)
#घोषणा DSIM_MAIN_PIX_FORMAT_RGB888	(0x7 << 12)
#घोषणा DSIM_MAIN_PIX_FORMAT_RGB666	(0x6 << 12)
#घोषणा DSIM_MAIN_PIX_FORMAT_RGB666_P	(0x5 << 12)
#घोषणा DSIM_MAIN_PIX_FORMAT_RGB565	(0x4 << 12)
#घोषणा DSIM_SUB_VC			(((x) & 0x3) << 16)
#घोषणा DSIM_MAIN_VC			(((x) & 0x3) << 18)
#घोषणा DSIM_HSA_MODE			(1 << 20)
#घोषणा DSIM_HBP_MODE			(1 << 21)
#घोषणा DSIM_HFP_MODE			(1 << 22)
#घोषणा DSIM_HSE_MODE			(1 << 23)
#घोषणा DSIM_AUTO_MODE			(1 << 24)
#घोषणा DSIM_VIDEO_MODE			(1 << 25)
#घोषणा DSIM_BURST_MODE			(1 << 26)
#घोषणा DSIM_SYNC_INFORM		(1 << 27)
#घोषणा DSIM_EOT_DISABLE		(1 << 28)
#घोषणा DSIM_MFLUSH_VS			(1 << 29)
/* This flag is valid only क्रम exynos3250/3472/5260/5430 */
#घोषणा DSIM_CLKLANE_STOP		(1 << 30)

/* DSIM_ESCMODE */
#घोषणा DSIM_TX_TRIGGER_RST		(1 << 4)
#घोषणा DSIM_TX_LPDT_LP			(1 << 6)
#घोषणा DSIM_CMD_LPDT_LP		(1 << 7)
#घोषणा DSIM_FORCE_BTA			(1 << 16)
#घोषणा DSIM_FORCE_STOP_STATE		(1 << 20)
#घोषणा DSIM_STOP_STATE_CNT(x)		(((x) & 0x7ff) << 21)
#घोषणा DSIM_STOP_STATE_CNT_MASK	(0x7ff << 21)

/* DSIM_MDRESOL */
#घोषणा DSIM_MAIN_STAND_BY		(1 << 31)
#घोषणा DSIM_MAIN_VRESOL(x, num_bits)	(((x) & ((1 << (num_bits)) - 1)) << 16)
#घोषणा DSIM_MAIN_HRESOL(x, num_bits)	(((x) & ((1 << (num_bits)) - 1)) << 0)

/* DSIM_MVPORCH */
#घोषणा DSIM_CMD_ALLOW(x)		((x) << 28)
#घोषणा DSIM_STABLE_VFP(x)		((x) << 16)
#घोषणा DSIM_MAIN_VBP(x)		((x) << 0)
#घोषणा DSIM_CMD_ALLOW_MASK		(0xf << 28)
#घोषणा DSIM_STABLE_VFP_MASK		(0x7ff << 16)
#घोषणा DSIM_MAIN_VBP_MASK		(0x7ff << 0)

/* DSIM_MHPORCH */
#घोषणा DSIM_MAIN_HFP(x)		((x) << 16)
#घोषणा DSIM_MAIN_HBP(x)		((x) << 0)
#घोषणा DSIM_MAIN_HFP_MASK		((0xffff) << 16)
#घोषणा DSIM_MAIN_HBP_MASK		((0xffff) << 0)

/* DSIM_MSYNC */
#घोषणा DSIM_MAIN_VSA(x)		((x) << 22)
#घोषणा DSIM_MAIN_HSA(x)		((x) << 0)
#घोषणा DSIM_MAIN_VSA_MASK		((0x3ff) << 22)
#घोषणा DSIM_MAIN_HSA_MASK		((0xffff) << 0)

/* DSIM_SDRESOL */
#घोषणा DSIM_SUB_STANDY(x)		((x) << 31)
#घोषणा DSIM_SUB_VRESOL(x)		((x) << 16)
#घोषणा DSIM_SUB_HRESOL(x)		((x) << 0)
#घोषणा DSIM_SUB_STANDY_MASK		((0x1) << 31)
#घोषणा DSIM_SUB_VRESOL_MASK		((0x7ff) << 16)
#घोषणा DSIM_SUB_HRESOL_MASK		((0x7ff) << 0)

/* DSIM_INTSRC */
#घोषणा DSIM_INT_PLL_STABLE		(1 << 31)
#घोषणा DSIM_INT_SW_RST_RELEASE		(1 << 30)
#घोषणा DSIM_INT_SFR_FIFO_EMPTY		(1 << 29)
#घोषणा DSIM_INT_SFR_HDR_FIFO_EMPTY	(1 << 28)
#घोषणा DSIM_INT_BTA			(1 << 25)
#घोषणा DSIM_INT_FRAME_DONE		(1 << 24)
#घोषणा DSIM_INT_RX_TIMEOUT		(1 << 21)
#घोषणा DSIM_INT_BTA_TIMEOUT		(1 << 20)
#घोषणा DSIM_INT_RX_DONE		(1 << 18)
#घोषणा DSIM_INT_RX_TE			(1 << 17)
#घोषणा DSIM_INT_RX_ACK			(1 << 16)
#घोषणा DSIM_INT_RX_ECC_ERR		(1 << 15)
#घोषणा DSIM_INT_RX_CRC_ERR		(1 << 14)

/* DSIM_FIFOCTRL */
#घोषणा DSIM_RX_DATA_FULL		(1 << 25)
#घोषणा DSIM_RX_DATA_EMPTY		(1 << 24)
#घोषणा DSIM_SFR_HEADER_FULL		(1 << 23)
#घोषणा DSIM_SFR_HEADER_EMPTY		(1 << 22)
#घोषणा DSIM_SFR_PAYLOAD_FULL		(1 << 21)
#घोषणा DSIM_SFR_PAYLOAD_EMPTY		(1 << 20)
#घोषणा DSIM_I80_HEADER_FULL		(1 << 19)
#घोषणा DSIM_I80_HEADER_EMPTY		(1 << 18)
#घोषणा DSIM_I80_PAYLOAD_FULL		(1 << 17)
#घोषणा DSIM_I80_PAYLOAD_EMPTY		(1 << 16)
#घोषणा DSIM_SD_HEADER_FULL		(1 << 15)
#घोषणा DSIM_SD_HEADER_EMPTY		(1 << 14)
#घोषणा DSIM_SD_PAYLOAD_FULL		(1 << 13)
#घोषणा DSIM_SD_PAYLOAD_EMPTY		(1 << 12)
#घोषणा DSIM_MD_HEADER_FULL		(1 << 11)
#घोषणा DSIM_MD_HEADER_EMPTY		(1 << 10)
#घोषणा DSIM_MD_PAYLOAD_FULL		(1 << 9)
#घोषणा DSIM_MD_PAYLOAD_EMPTY		(1 << 8)
#घोषणा DSIM_RX_FIFO			(1 << 4)
#घोषणा DSIM_SFR_FIFO			(1 << 3)
#घोषणा DSIM_I80_FIFO			(1 << 2)
#घोषणा DSIM_SD_FIFO			(1 << 1)
#घोषणा DSIM_MD_FIFO			(1 << 0)

/* DSIM_PHYACCHR */
#घोषणा DSIM_AFC_EN			(1 << 14)
#घोषणा DSIM_AFC_CTL(x)			(((x) & 0x7) << 5)

/* DSIM_PLLCTRL */
#घोषणा DSIM_FREQ_BAND(x)		((x) << 24)
#घोषणा DSIM_PLL_EN			(1 << 23)
#घोषणा DSIM_PLL_P(x)			((x) << 13)
#घोषणा DSIM_PLL_M(x)			((x) << 4)
#घोषणा DSIM_PLL_S(x)			((x) << 1)

/* DSIM_PHYCTRL */
#घोषणा DSIM_PHYCTRL_ULPS_EXIT(x)	(((x) & 0x1ff) << 0)
#घोषणा DSIM_PHYCTRL_B_DPHYCTL_VREG_LP	(1 << 30)
#घोषणा DSIM_PHYCTRL_B_DPHYCTL_SLEW_UP	(1 << 14)

/* DSIM_PHYTIMING */
#घोषणा DSIM_PHYTIMING_LPX(x)		((x) << 8)
#घोषणा DSIM_PHYTIMING_HS_EXIT(x)	((x) << 0)

/* DSIM_PHYTIMING1 */
#घोषणा DSIM_PHYTIMING1_CLK_PREPARE(x)	((x) << 24)
#घोषणा DSIM_PHYTIMING1_CLK_ZERO(x)	((x) << 16)
#घोषणा DSIM_PHYTIMING1_CLK_POST(x)	((x) << 8)
#घोषणा DSIM_PHYTIMING1_CLK_TRAIL(x)	((x) << 0)

/* DSIM_PHYTIMING2 */
#घोषणा DSIM_PHYTIMING2_HS_PREPARE(x)	((x) << 16)
#घोषणा DSIM_PHYTIMING2_HS_ZERO(x)	((x) << 8)
#घोषणा DSIM_PHYTIMING2_HS_TRAIL(x)	((x) << 0)

#घोषणा DSI_MAX_BUS_WIDTH		4
#घोषणा DSI_NUM_VIRTUAL_CHANNELS	4
#घोषणा DSI_TX_FIFO_SIZE		2048
#घोषणा DSI_RX_FIFO_SIZE		256
#घोषणा DSI_XFER_TIMEOUT_MS		100
#घोषणा DSI_RX_FIFO_EMPTY		0x30800002

#घोषणा OLD_SCLK_MIPI_CLK_NAME "pll_clk"

अटल स्थिर अक्षर *स्थिर clk_names[5] = अणु "bus_clk", "sclk_mipi",
	"phyclk_mipidphy0_bitclkdiv8", "phyclk_mipidphy0_rxclkesc0",
	"sclk_rgb_vclk_to_dsim0" पूर्ण;

क्रमागत exynos_dsi_transfer_type अणु
	EXYNOS_DSI_TX,
	EXYNOS_DSI_RX,
पूर्ण;

काष्ठा exynos_dsi_transfer अणु
	काष्ठा list_head list;
	काष्ठा completion completed;
	पूर्णांक result;
	काष्ठा mipi_dsi_packet packet;
	u16 flags;
	u16 tx_करोne;

	u8 *rx_payload;
	u16 rx_len;
	u16 rx_करोne;
पूर्ण;

#घोषणा DSIM_STATE_ENABLED		BIT(0)
#घोषणा DSIM_STATE_INITIALIZED		BIT(1)
#घोषणा DSIM_STATE_CMD_LPM		BIT(2)
#घोषणा DSIM_STATE_VIDOUT_AVAILABLE	BIT(3)

काष्ठा exynos_dsi_driver_data अणु
	स्थिर अचिन्हित पूर्णांक *reg_ofs;
	अचिन्हित पूर्णांक pllपंचांगr_reg;
	अचिन्हित पूर्णांक has_freqband:1;
	अचिन्हित पूर्णांक has_clklane_stop:1;
	अचिन्हित पूर्णांक num_clks;
	अचिन्हित पूर्णांक max_freq;
	अचिन्हित पूर्णांक रुको_क्रम_reset;
	अचिन्हित पूर्णांक num_bits_resol;
	स्थिर अचिन्हित पूर्णांक *reg_values;
पूर्ण;

काष्ठा exynos_dsi अणु
	काष्ठा drm_encoder encoder;
	काष्ठा mipi_dsi_host dsi_host;
	काष्ठा drm_connector connector;
	काष्ठा drm_panel *panel;
	काष्ठा list_head bridge_chain;
	काष्ठा drm_bridge *out_bridge;
	काष्ठा device *dev;

	व्योम __iomem *reg_base;
	काष्ठा phy *phy;
	काष्ठा clk **clks;
	काष्ठा regulator_bulk_data supplies[2];
	पूर्णांक irq;
	पूर्णांक te_gpio;

	u32 pll_clk_rate;
	u32 burst_clk_rate;
	u32 esc_clk_rate;
	u32 lanes;
	u32 mode_flags;
	u32 क्रमmat;

	पूर्णांक state;
	काष्ठा drm_property *brightness;
	काष्ठा completion completed;

	spinlock_t transfer_lock; /* protects transfer_list */
	काष्ठा list_head transfer_list;

	स्थिर काष्ठा exynos_dsi_driver_data *driver_data;
पूर्ण;

#घोषणा host_to_dsi(host) container_of(host, काष्ठा exynos_dsi, dsi_host)
#घोषणा connector_to_dsi(c) container_of(c, काष्ठा exynos_dsi, connector)

अटल अंतरभूत काष्ठा exynos_dsi *encoder_to_dsi(काष्ठा drm_encoder *e)
अणु
	वापस container_of(e, काष्ठा exynos_dsi, encoder);
पूर्ण

क्रमागत reg_idx अणु
	DSIM_STATUS_REG,	/* Status रेजिस्टर */
	DSIM_SWRST_REG,		/* Software reset रेजिस्टर */
	DSIM_CLKCTRL_REG,	/* Clock control रेजिस्टर */
	DSIM_TIMEOUT_REG,	/* Time out रेजिस्टर */
	DSIM_CONFIG_REG,	/* Configuration रेजिस्टर */
	DSIM_ESCMODE_REG,	/* Escape mode रेजिस्टर */
	DSIM_MDRESOL_REG,
	DSIM_MVPORCH_REG,	/* Main display Vporch रेजिस्टर */
	DSIM_MHPORCH_REG,	/* Main display Hporch रेजिस्टर */
	DSIM_MSYNC_REG,		/* Main display sync area रेजिस्टर */
	DSIM_INTSRC_REG,	/* Interrupt source रेजिस्टर */
	DSIM_INTMSK_REG,	/* Interrupt mask रेजिस्टर */
	DSIM_PKTHDR_REG,	/* Packet Header FIFO रेजिस्टर */
	DSIM_PAYLOAD_REG,	/* Payload FIFO रेजिस्टर */
	DSIM_RXFIFO_REG,	/* Read FIFO रेजिस्टर */
	DSIM_FIFOCTRL_REG,	/* FIFO status and control रेजिस्टर */
	DSIM_PLLCTRL_REG,	/* PLL control रेजिस्टर */
	DSIM_PHYCTRL_REG,
	DSIM_PHYTIMING_REG,
	DSIM_PHYTIMING1_REG,
	DSIM_PHYTIMING2_REG,
	NUM_REGS
पूर्ण;

अटल अंतरभूत व्योम exynos_dsi_ग_लिखो(काष्ठा exynos_dsi *dsi, क्रमागत reg_idx idx,
				    u32 val)
अणु

	ग_लिखोl(val, dsi->reg_base + dsi->driver_data->reg_ofs[idx]);
पूर्ण

अटल अंतरभूत u32 exynos_dsi_पढ़ो(काष्ठा exynos_dsi *dsi, क्रमागत reg_idx idx)
अणु
	वापस पढ़ोl(dsi->reg_base + dsi->driver_data->reg_ofs[idx]);
पूर्ण

अटल स्थिर अचिन्हित पूर्णांक exynos_reg_ofs[] = अणु
	[DSIM_STATUS_REG] =  0x00,
	[DSIM_SWRST_REG] =  0x04,
	[DSIM_CLKCTRL_REG] =  0x08,
	[DSIM_TIMEOUT_REG] =  0x0c,
	[DSIM_CONFIG_REG] =  0x10,
	[DSIM_ESCMODE_REG] =  0x14,
	[DSIM_MDRESOL_REG] =  0x18,
	[DSIM_MVPORCH_REG] =  0x1c,
	[DSIM_MHPORCH_REG] =  0x20,
	[DSIM_MSYNC_REG] =  0x24,
	[DSIM_INTSRC_REG] =  0x2c,
	[DSIM_INTMSK_REG] =  0x30,
	[DSIM_PKTHDR_REG] =  0x34,
	[DSIM_PAYLOAD_REG] =  0x38,
	[DSIM_RXFIFO_REG] =  0x3c,
	[DSIM_FIFOCTRL_REG] =  0x44,
	[DSIM_PLLCTRL_REG] =  0x4c,
	[DSIM_PHYCTRL_REG] =  0x5c,
	[DSIM_PHYTIMING_REG] =  0x64,
	[DSIM_PHYTIMING1_REG] =  0x68,
	[DSIM_PHYTIMING2_REG] =  0x6c,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक exynos5433_reg_ofs[] = अणु
	[DSIM_STATUS_REG] = 0x04,
	[DSIM_SWRST_REG] = 0x0C,
	[DSIM_CLKCTRL_REG] = 0x10,
	[DSIM_TIMEOUT_REG] = 0x14,
	[DSIM_CONFIG_REG] = 0x18,
	[DSIM_ESCMODE_REG] = 0x1C,
	[DSIM_MDRESOL_REG] = 0x20,
	[DSIM_MVPORCH_REG] = 0x24,
	[DSIM_MHPORCH_REG] = 0x28,
	[DSIM_MSYNC_REG] = 0x2C,
	[DSIM_INTSRC_REG] = 0x34,
	[DSIM_INTMSK_REG] = 0x38,
	[DSIM_PKTHDR_REG] = 0x3C,
	[DSIM_PAYLOAD_REG] = 0x40,
	[DSIM_RXFIFO_REG] = 0x44,
	[DSIM_FIFOCTRL_REG] = 0x4C,
	[DSIM_PLLCTRL_REG] = 0x94,
	[DSIM_PHYCTRL_REG] = 0xA4,
	[DSIM_PHYTIMING_REG] = 0xB4,
	[DSIM_PHYTIMING1_REG] = 0xB8,
	[DSIM_PHYTIMING2_REG] = 0xBC,
पूर्ण;

क्रमागत reg_value_idx अणु
	RESET_TYPE,
	PLL_TIMER,
	STOP_STATE_CNT,
	PHYCTRL_ULPS_EXIT,
	PHYCTRL_VREG_LP,
	PHYCTRL_SLEW_UP,
	PHYTIMING_LPX,
	PHYTIMING_HS_EXIT,
	PHYTIMING_CLK_PREPARE,
	PHYTIMING_CLK_ZERO,
	PHYTIMING_CLK_POST,
	PHYTIMING_CLK_TRAIL,
	PHYTIMING_HS_PREPARE,
	PHYTIMING_HS_ZERO,
	PHYTIMING_HS_TRAIL
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक reg_values[] = अणु
	[RESET_TYPE] = DSIM_SWRST,
	[PLL_TIMER] = 500,
	[STOP_STATE_CNT] = 0xf,
	[PHYCTRL_ULPS_EXIT] = DSIM_PHYCTRL_ULPS_EXIT(0x0af),
	[PHYCTRL_VREG_LP] = 0,
	[PHYCTRL_SLEW_UP] = 0,
	[PHYTIMING_LPX] = DSIM_PHYTIMING_LPX(0x06),
	[PHYTIMING_HS_EXIT] = DSIM_PHYTIMING_HS_EXIT(0x0b),
	[PHYTIMING_CLK_PREPARE] = DSIM_PHYTIMING1_CLK_PREPARE(0x07),
	[PHYTIMING_CLK_ZERO] = DSIM_PHYTIMING1_CLK_ZERO(0x27),
	[PHYTIMING_CLK_POST] = DSIM_PHYTIMING1_CLK_POST(0x0d),
	[PHYTIMING_CLK_TRAIL] = DSIM_PHYTIMING1_CLK_TRAIL(0x08),
	[PHYTIMING_HS_PREPARE] = DSIM_PHYTIMING2_HS_PREPARE(0x09),
	[PHYTIMING_HS_ZERO] = DSIM_PHYTIMING2_HS_ZERO(0x0d),
	[PHYTIMING_HS_TRAIL] = DSIM_PHYTIMING2_HS_TRAIL(0x0b),
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक exynos5422_reg_values[] = अणु
	[RESET_TYPE] = DSIM_SWRST,
	[PLL_TIMER] = 500,
	[STOP_STATE_CNT] = 0xf,
	[PHYCTRL_ULPS_EXIT] = DSIM_PHYCTRL_ULPS_EXIT(0xaf),
	[PHYCTRL_VREG_LP] = 0,
	[PHYCTRL_SLEW_UP] = 0,
	[PHYTIMING_LPX] = DSIM_PHYTIMING_LPX(0x08),
	[PHYTIMING_HS_EXIT] = DSIM_PHYTIMING_HS_EXIT(0x0d),
	[PHYTIMING_CLK_PREPARE] = DSIM_PHYTIMING1_CLK_PREPARE(0x09),
	[PHYTIMING_CLK_ZERO] = DSIM_PHYTIMING1_CLK_ZERO(0x30),
	[PHYTIMING_CLK_POST] = DSIM_PHYTIMING1_CLK_POST(0x0e),
	[PHYTIMING_CLK_TRAIL] = DSIM_PHYTIMING1_CLK_TRAIL(0x0a),
	[PHYTIMING_HS_PREPARE] = DSIM_PHYTIMING2_HS_PREPARE(0x0c),
	[PHYTIMING_HS_ZERO] = DSIM_PHYTIMING2_HS_ZERO(0x11),
	[PHYTIMING_HS_TRAIL] = DSIM_PHYTIMING2_HS_TRAIL(0x0d),
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक exynos5433_reg_values[] = अणु
	[RESET_TYPE] = DSIM_FUNCRST,
	[PLL_TIMER] = 22200,
	[STOP_STATE_CNT] = 0xa,
	[PHYCTRL_ULPS_EXIT] = DSIM_PHYCTRL_ULPS_EXIT(0x190),
	[PHYCTRL_VREG_LP] = DSIM_PHYCTRL_B_DPHYCTL_VREG_LP,
	[PHYCTRL_SLEW_UP] = DSIM_PHYCTRL_B_DPHYCTL_SLEW_UP,
	[PHYTIMING_LPX] = DSIM_PHYTIMING_LPX(0x07),
	[PHYTIMING_HS_EXIT] = DSIM_PHYTIMING_HS_EXIT(0x0c),
	[PHYTIMING_CLK_PREPARE] = DSIM_PHYTIMING1_CLK_PREPARE(0x09),
	[PHYTIMING_CLK_ZERO] = DSIM_PHYTIMING1_CLK_ZERO(0x2d),
	[PHYTIMING_CLK_POST] = DSIM_PHYTIMING1_CLK_POST(0x0e),
	[PHYTIMING_CLK_TRAIL] = DSIM_PHYTIMING1_CLK_TRAIL(0x09),
	[PHYTIMING_HS_PREPARE] = DSIM_PHYTIMING2_HS_PREPARE(0x0b),
	[PHYTIMING_HS_ZERO] = DSIM_PHYTIMING2_HS_ZERO(0x10),
	[PHYTIMING_HS_TRAIL] = DSIM_PHYTIMING2_HS_TRAIL(0x0c),
पूर्ण;

अटल स्थिर काष्ठा exynos_dsi_driver_data exynos3_dsi_driver_data = अणु
	.reg_ofs = exynos_reg_ofs,
	.pllपंचांगr_reg = 0x50,
	.has_freqband = 1,
	.has_clklane_stop = 1,
	.num_clks = 2,
	.max_freq = 1000,
	.रुको_क्रम_reset = 1,
	.num_bits_resol = 11,
	.reg_values = reg_values,
पूर्ण;

अटल स्थिर काष्ठा exynos_dsi_driver_data exynos4_dsi_driver_data = अणु
	.reg_ofs = exynos_reg_ofs,
	.pllपंचांगr_reg = 0x50,
	.has_freqband = 1,
	.has_clklane_stop = 1,
	.num_clks = 2,
	.max_freq = 1000,
	.रुको_क्रम_reset = 1,
	.num_bits_resol = 11,
	.reg_values = reg_values,
पूर्ण;

अटल स्थिर काष्ठा exynos_dsi_driver_data exynos5_dsi_driver_data = अणु
	.reg_ofs = exynos_reg_ofs,
	.pllपंचांगr_reg = 0x58,
	.num_clks = 2,
	.max_freq = 1000,
	.रुको_क्रम_reset = 1,
	.num_bits_resol = 11,
	.reg_values = reg_values,
पूर्ण;

अटल स्थिर काष्ठा exynos_dsi_driver_data exynos5433_dsi_driver_data = अणु
	.reg_ofs = exynos5433_reg_ofs,
	.pllपंचांगr_reg = 0xa0,
	.has_clklane_stop = 1,
	.num_clks = 5,
	.max_freq = 1500,
	.रुको_क्रम_reset = 0,
	.num_bits_resol = 12,
	.reg_values = exynos5433_reg_values,
पूर्ण;

अटल स्थिर काष्ठा exynos_dsi_driver_data exynos5422_dsi_driver_data = अणु
	.reg_ofs = exynos5433_reg_ofs,
	.pllपंचांगr_reg = 0xa0,
	.has_clklane_stop = 1,
	.num_clks = 2,
	.max_freq = 1500,
	.रुको_क्रम_reset = 1,
	.num_bits_resol = 12,
	.reg_values = exynos5422_reg_values,
पूर्ण;

अटल स्थिर काष्ठा of_device_id exynos_dsi_of_match[] = अणु
	अणु .compatible = "samsung,exynos3250-mipi-dsi",
	  .data = &exynos3_dsi_driver_data पूर्ण,
	अणु .compatible = "samsung,exynos4210-mipi-dsi",
	  .data = &exynos4_dsi_driver_data पूर्ण,
	अणु .compatible = "samsung,exynos5410-mipi-dsi",
	  .data = &exynos5_dsi_driver_data पूर्ण,
	अणु .compatible = "samsung,exynos5422-mipi-dsi",
	  .data = &exynos5422_dsi_driver_data पूर्ण,
	अणु .compatible = "samsung,exynos5433-mipi-dsi",
	  .data = &exynos5433_dsi_driver_data पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल व्योम exynos_dsi_रुको_क्रम_reset(काष्ठा exynos_dsi *dsi)
अणु
	अगर (रुको_क्रम_completion_समयout(&dsi->completed, msecs_to_jअगरfies(300)))
		वापस;

	dev_err(dsi->dev, "timeout waiting for reset\n");
पूर्ण

अटल व्योम exynos_dsi_reset(काष्ठा exynos_dsi *dsi)
अणु
	u32 reset_val = dsi->driver_data->reg_values[RESET_TYPE];

	reinit_completion(&dsi->completed);
	exynos_dsi_ग_लिखो(dsi, DSIM_SWRST_REG, reset_val);
पूर्ण

#अगर_अघोषित MHZ
#घोषणा MHZ	(1000*1000)
#पूर्ण_अगर

अटल अचिन्हित दीर्घ exynos_dsi_pll_find_pms(काष्ठा exynos_dsi *dsi,
		अचिन्हित दीर्घ fin, अचिन्हित दीर्घ fout, u8 *p, u16 *m, u8 *s)
अणु
	स्थिर काष्ठा exynos_dsi_driver_data *driver_data = dsi->driver_data;
	अचिन्हित दीर्घ best_freq = 0;
	u32 min_delta = 0xffffffff;
	u8 p_min, p_max;
	u8 _p, best_p;
	u16 _m, best_m;
	u8 _s, best_s;

	p_min = DIV_ROUND_UP(fin, (12 * MHZ));
	p_max = fin / (6 * MHZ);

	क्रम (_p = p_min; _p <= p_max; ++_p) अणु
		क्रम (_s = 0; _s <= 5; ++_s) अणु
			u64 पंचांगp;
			u32 delta;

			पंचांगp = (u64)fout * (_p << _s);
			करो_भाग(पंचांगp, fin);
			_m = पंचांगp;
			अगर (_m < 41 || _m > 125)
				जारी;

			पंचांगp = (u64)_m * fin;
			करो_भाग(पंचांगp, _p);
			अगर (पंचांगp < 500 * MHZ ||
					पंचांगp > driver_data->max_freq * MHZ)
				जारी;

			पंचांगp = (u64)_m * fin;
			करो_भाग(पंचांगp, _p << _s);

			delta = असल(fout - पंचांगp);
			अगर (delta < min_delta) अणु
				best_p = _p;
				best_m = _m;
				best_s = _s;
				min_delta = delta;
				best_freq = पंचांगp;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (best_freq) अणु
		*p = best_p;
		*m = best_m;
		*s = best_s;
	पूर्ण

	वापस best_freq;
पूर्ण

अटल अचिन्हित दीर्घ exynos_dsi_set_pll(काष्ठा exynos_dsi *dsi,
					अचिन्हित दीर्घ freq)
अणु
	स्थिर काष्ठा exynos_dsi_driver_data *driver_data = dsi->driver_data;
	अचिन्हित दीर्घ fin, fout;
	पूर्णांक समयout;
	u8 p, s;
	u16 m;
	u32 reg;

	fin = dsi->pll_clk_rate;
	fout = exynos_dsi_pll_find_pms(dsi, fin, freq, &p, &m, &s);
	अगर (!fout) अणु
		dev_err(dsi->dev,
			"failed to find PLL PMS for requested frequency\n");
		वापस 0;
	पूर्ण
	dev_dbg(dsi->dev, "PLL freq %lu, (p %d, m %d, s %d)\n", fout, p, m, s);

	ग_लिखोl(driver_data->reg_values[PLL_TIMER],
			dsi->reg_base + driver_data->pllपंचांगr_reg);

	reg = DSIM_PLL_EN | DSIM_PLL_P(p) | DSIM_PLL_M(m) | DSIM_PLL_S(s);

	अगर (driver_data->has_freqband) अणु
		अटल स्थिर अचिन्हित दीर्घ freq_bands[] = अणु
			100 * MHZ, 120 * MHZ, 160 * MHZ, 200 * MHZ,
			270 * MHZ, 320 * MHZ, 390 * MHZ, 450 * MHZ,
			510 * MHZ, 560 * MHZ, 640 * MHZ, 690 * MHZ,
			770 * MHZ, 870 * MHZ, 950 * MHZ,
		पूर्ण;
		पूर्णांक band;

		क्रम (band = 0; band < ARRAY_SIZE(freq_bands); ++band)
			अगर (fout < freq_bands[band])
				अवरोध;

		dev_dbg(dsi->dev, "band %d\n", band);

		reg |= DSIM_FREQ_BAND(band);
	पूर्ण

	exynos_dsi_ग_लिखो(dsi, DSIM_PLLCTRL_REG, reg);

	समयout = 1000;
	करो अणु
		अगर (समयout-- == 0) अणु
			dev_err(dsi->dev, "PLL failed to stabilize\n");
			वापस 0;
		पूर्ण
		reg = exynos_dsi_पढ़ो(dsi, DSIM_STATUS_REG);
	पूर्ण जबतक ((reg & DSIM_PLL_STABLE) == 0);

	वापस fout;
पूर्ण

अटल पूर्णांक exynos_dsi_enable_घड़ी(काष्ठा exynos_dsi *dsi)
अणु
	अचिन्हित दीर्घ hs_clk, byte_clk, esc_clk;
	अचिन्हित दीर्घ esc_भाग;
	u32 reg;

	hs_clk = exynos_dsi_set_pll(dsi, dsi->burst_clk_rate);
	अगर (!hs_clk) अणु
		dev_err(dsi->dev, "failed to configure DSI PLL\n");
		वापस -EFAULT;
	पूर्ण

	byte_clk = hs_clk / 8;
	esc_भाग = DIV_ROUND_UP(byte_clk, dsi->esc_clk_rate);
	esc_clk = byte_clk / esc_भाग;

	अगर (esc_clk > 20 * MHZ) अणु
		++esc_भाग;
		esc_clk = byte_clk / esc_भाग;
	पूर्ण

	dev_dbg(dsi->dev, "hs_clk = %lu, byte_clk = %lu, esc_clk = %lu\n",
		hs_clk, byte_clk, esc_clk);

	reg = exynos_dsi_पढ़ो(dsi, DSIM_CLKCTRL_REG);
	reg &= ~(DSIM_ESC_PRESCALER_MASK | DSIM_LANE_ESC_CLK_EN_CLK
			| DSIM_LANE_ESC_CLK_EN_DATA_MASK | DSIM_PLL_BYPASS
			| DSIM_BYTE_CLK_SRC_MASK);
	reg |= DSIM_ESC_CLKEN | DSIM_BYTE_CLKEN
			| DSIM_ESC_PRESCALER(esc_भाग)
			| DSIM_LANE_ESC_CLK_EN_CLK
			| DSIM_LANE_ESC_CLK_EN_DATA(BIT(dsi->lanes) - 1)
			| DSIM_BYTE_CLK_SRC(0)
			| DSIM_TX_REQUEST_HSCLK;
	exynos_dsi_ग_लिखो(dsi, DSIM_CLKCTRL_REG, reg);

	वापस 0;
पूर्ण

अटल व्योम exynos_dsi_set_phy_ctrl(काष्ठा exynos_dsi *dsi)
अणु
	स्थिर काष्ठा exynos_dsi_driver_data *driver_data = dsi->driver_data;
	स्थिर अचिन्हित पूर्णांक *reg_values = driver_data->reg_values;
	u32 reg;

	अगर (driver_data->has_freqband)
		वापस;

	/* B D-PHY: D-PHY Master & Slave Analog Block control */
	reg = reg_values[PHYCTRL_ULPS_EXIT] | reg_values[PHYCTRL_VREG_LP] |
		reg_values[PHYCTRL_SLEW_UP];
	exynos_dsi_ग_लिखो(dsi, DSIM_PHYCTRL_REG, reg);

	/*
	 * T LPX: Transmitted length of any Low-Power state period
	 * T HS-EXIT: Time that the transmitter drives LP-11 following a HS
	 *	burst
	 */
	reg = reg_values[PHYTIMING_LPX] | reg_values[PHYTIMING_HS_EXIT];
	exynos_dsi_ग_लिखो(dsi, DSIM_PHYTIMING_REG, reg);

	/*
	 * T CLK-PREPARE: Time that the transmitter drives the Clock Lane LP-00
	 *	Line state immediately beक्रमe the HS-0 Line state starting the
	 *	HS transmission
	 * T CLK-ZERO: Time that the transmitter drives the HS-0 state prior to
	 *	transmitting the Clock.
	 * T CLK_POST: Time that the transmitter जारीs to send HS घड़ी
	 *	after the last associated Data Lane has transitioned to LP Mode
	 *	Interval is defined as the period from the end of T HS-TRAIL to
	 *	the beginning of T CLK-TRAIL
	 * T CLK-TRAIL: Time that the transmitter drives the HS-0 state after
	 *	the last payload घड़ी bit of a HS transmission burst
	 */
	reg = reg_values[PHYTIMING_CLK_PREPARE] |
		reg_values[PHYTIMING_CLK_ZERO] |
		reg_values[PHYTIMING_CLK_POST] |
		reg_values[PHYTIMING_CLK_TRAIL];

	exynos_dsi_ग_लिखो(dsi, DSIM_PHYTIMING1_REG, reg);

	/*
	 * T HS-PREPARE: Time that the transmitter drives the Data Lane LP-00
	 *	Line state immediately beक्रमe the HS-0 Line state starting the
	 *	HS transmission
	 * T HS-ZERO: Time that the transmitter drives the HS-0 state prior to
	 *	transmitting the Sync sequence.
	 * T HS-TRAIL: Time that the transmitter drives the flipped dअगरferential
	 *	state after last payload data bit of a HS transmission burst
	 */
	reg = reg_values[PHYTIMING_HS_PREPARE] | reg_values[PHYTIMING_HS_ZERO] |
		reg_values[PHYTIMING_HS_TRAIL];
	exynos_dsi_ग_लिखो(dsi, DSIM_PHYTIMING2_REG, reg);
पूर्ण

अटल व्योम exynos_dsi_disable_घड़ी(काष्ठा exynos_dsi *dsi)
अणु
	u32 reg;

	reg = exynos_dsi_पढ़ो(dsi, DSIM_CLKCTRL_REG);
	reg &= ~(DSIM_LANE_ESC_CLK_EN_CLK | DSIM_LANE_ESC_CLK_EN_DATA_MASK
			| DSIM_ESC_CLKEN | DSIM_BYTE_CLKEN);
	exynos_dsi_ग_लिखो(dsi, DSIM_CLKCTRL_REG, reg);

	reg = exynos_dsi_पढ़ो(dsi, DSIM_PLLCTRL_REG);
	reg &= ~DSIM_PLL_EN;
	exynos_dsi_ग_लिखो(dsi, DSIM_PLLCTRL_REG, reg);
पूर्ण

अटल व्योम exynos_dsi_enable_lane(काष्ठा exynos_dsi *dsi, u32 lane)
अणु
	u32 reg = exynos_dsi_पढ़ो(dsi, DSIM_CONFIG_REG);
	reg |= (DSIM_NUM_OF_DATA_LANE(dsi->lanes - 1) | DSIM_LANE_EN_CLK |
			DSIM_LANE_EN(lane));
	exynos_dsi_ग_लिखो(dsi, DSIM_CONFIG_REG, reg);
पूर्ण

अटल पूर्णांक exynos_dsi_init_link(काष्ठा exynos_dsi *dsi)
अणु
	स्थिर काष्ठा exynos_dsi_driver_data *driver_data = dsi->driver_data;
	पूर्णांक समयout;
	u32 reg;
	u32 lanes_mask;

	/* Initialize FIFO poपूर्णांकers */
	reg = exynos_dsi_पढ़ो(dsi, DSIM_FIFOCTRL_REG);
	reg &= ~0x1f;
	exynos_dsi_ग_लिखो(dsi, DSIM_FIFOCTRL_REG, reg);

	usleep_range(9000, 11000);

	reg |= 0x1f;
	exynos_dsi_ग_लिखो(dsi, DSIM_FIFOCTRL_REG, reg);
	usleep_range(9000, 11000);

	/* DSI configuration */
	reg = 0;

	/*
	 * The first bit of mode_flags specअगरies display configuration.
	 * If this bit is set[= MIPI_DSI_MODE_VIDEO], dsi will support video
	 * mode, otherwise it will support command mode.
	 */
	अगर (dsi->mode_flags & MIPI_DSI_MODE_VIDEO) अणु
		reg |= DSIM_VIDEO_MODE;

		/*
		 * The user manual describes that following bits are ignored in
		 * command mode.
		 */
		अगर (!(dsi->mode_flags & MIPI_DSI_MODE_VSYNC_FLUSH))
			reg |= DSIM_MFLUSH_VS;
		अगर (dsi->mode_flags & MIPI_DSI_MODE_VIDEO_SYNC_PULSE)
			reg |= DSIM_SYNC_INFORM;
		अगर (dsi->mode_flags & MIPI_DSI_MODE_VIDEO_BURST)
			reg |= DSIM_BURST_MODE;
		अगर (dsi->mode_flags & MIPI_DSI_MODE_VIDEO_AUTO_VERT)
			reg |= DSIM_AUTO_MODE;
		अगर (dsi->mode_flags & MIPI_DSI_MODE_VIDEO_HSE)
			reg |= DSIM_HSE_MODE;
		अगर (!(dsi->mode_flags & MIPI_DSI_MODE_VIDEO_HFP))
			reg |= DSIM_HFP_MODE;
		अगर (!(dsi->mode_flags & MIPI_DSI_MODE_VIDEO_HBP))
			reg |= DSIM_HBP_MODE;
		अगर (!(dsi->mode_flags & MIPI_DSI_MODE_VIDEO_HSA))
			reg |= DSIM_HSA_MODE;
	पूर्ण

	अगर (!(dsi->mode_flags & MIPI_DSI_MODE_EOT_PACKET))
		reg |= DSIM_EOT_DISABLE;

	चयन (dsi->क्रमmat) अणु
	हाल MIPI_DSI_FMT_RGB888:
		reg |= DSIM_MAIN_PIX_FORMAT_RGB888;
		अवरोध;
	हाल MIPI_DSI_FMT_RGB666:
		reg |= DSIM_MAIN_PIX_FORMAT_RGB666;
		अवरोध;
	हाल MIPI_DSI_FMT_RGB666_PACKED:
		reg |= DSIM_MAIN_PIX_FORMAT_RGB666_P;
		अवरोध;
	हाल MIPI_DSI_FMT_RGB565:
		reg |= DSIM_MAIN_PIX_FORMAT_RGB565;
		अवरोध;
	शेष:
		dev_err(dsi->dev, "invalid pixel format\n");
		वापस -EINVAL;
	पूर्ण

	/*
	 * Use non-continuous घड़ी mode अगर the periparal wants and
	 * host controller supports
	 *
	 * In non-continous घड़ी mode, host controller will turn off
	 * the HS घड़ी between high-speed transmissions to reduce
	 * घातer consumption.
	 */
	अगर (driver_data->has_clklane_stop &&
			dsi->mode_flags & MIPI_DSI_CLOCK_NON_CONTINUOUS) अणु
		reg |= DSIM_CLKLANE_STOP;
	पूर्ण
	exynos_dsi_ग_लिखो(dsi, DSIM_CONFIG_REG, reg);

	lanes_mask = BIT(dsi->lanes) - 1;
	exynos_dsi_enable_lane(dsi, lanes_mask);

	/* Check घड़ी and data lane state are stop state */
	समयout = 100;
	करो अणु
		अगर (समयout-- == 0) अणु
			dev_err(dsi->dev, "waiting for bus lanes timed out\n");
			वापस -EFAULT;
		पूर्ण

		reg = exynos_dsi_पढ़ो(dsi, DSIM_STATUS_REG);
		अगर ((reg & DSIM_STOP_STATE_DAT(lanes_mask))
		    != DSIM_STOP_STATE_DAT(lanes_mask))
			जारी;
	पूर्ण जबतक (!(reg & (DSIM_STOP_STATE_CLK | DSIM_TX_READY_HS_CLK)));

	reg = exynos_dsi_पढ़ो(dsi, DSIM_ESCMODE_REG);
	reg &= ~DSIM_STOP_STATE_CNT_MASK;
	reg |= DSIM_STOP_STATE_CNT(driver_data->reg_values[STOP_STATE_CNT]);
	exynos_dsi_ग_लिखो(dsi, DSIM_ESCMODE_REG, reg);

	reg = DSIM_BTA_TIMEOUT(0xff) | DSIM_LPDR_TIMEOUT(0xffff);
	exynos_dsi_ग_लिखो(dsi, DSIM_TIMEOUT_REG, reg);

	वापस 0;
पूर्ण

अटल व्योम exynos_dsi_set_display_mode(काष्ठा exynos_dsi *dsi)
अणु
	काष्ठा drm_display_mode *m = &dsi->encoder.crtc->state->adjusted_mode;
	अचिन्हित पूर्णांक num_bits_resol = dsi->driver_data->num_bits_resol;
	u32 reg;

	अगर (dsi->mode_flags & MIPI_DSI_MODE_VIDEO) अणु
		reg = DSIM_CMD_ALLOW(0xf)
			| DSIM_STABLE_VFP(m->vsync_start - m->vdisplay)
			| DSIM_MAIN_VBP(m->vtotal - m->vsync_end);
		exynos_dsi_ग_लिखो(dsi, DSIM_MVPORCH_REG, reg);

		reg = DSIM_MAIN_HFP(m->hsync_start - m->hdisplay)
			| DSIM_MAIN_HBP(m->htotal - m->hsync_end);
		exynos_dsi_ग_लिखो(dsi, DSIM_MHPORCH_REG, reg);

		reg = DSIM_MAIN_VSA(m->vsync_end - m->vsync_start)
			| DSIM_MAIN_HSA(m->hsync_end - m->hsync_start);
		exynos_dsi_ग_लिखो(dsi, DSIM_MSYNC_REG, reg);
	पूर्ण
	reg =  DSIM_MAIN_HRESOL(m->hdisplay, num_bits_resol) |
		DSIM_MAIN_VRESOL(m->vdisplay, num_bits_resol);

	exynos_dsi_ग_लिखो(dsi, DSIM_MDRESOL_REG, reg);

	dev_dbg(dsi->dev, "LCD size = %dx%d\n", m->hdisplay, m->vdisplay);
पूर्ण

अटल व्योम exynos_dsi_set_display_enable(काष्ठा exynos_dsi *dsi, bool enable)
अणु
	u32 reg;

	reg = exynos_dsi_पढ़ो(dsi, DSIM_MDRESOL_REG);
	अगर (enable)
		reg |= DSIM_MAIN_STAND_BY;
	अन्यथा
		reg &= ~DSIM_MAIN_STAND_BY;
	exynos_dsi_ग_लिखो(dsi, DSIM_MDRESOL_REG, reg);
पूर्ण

अटल पूर्णांक exynos_dsi_रुको_क्रम_hdr_fअगरo(काष्ठा exynos_dsi *dsi)
अणु
	पूर्णांक समयout = 2000;

	करो अणु
		u32 reg = exynos_dsi_पढ़ो(dsi, DSIM_FIFOCTRL_REG);

		अगर (!(reg & DSIM_SFR_HEADER_FULL))
			वापस 0;

		अगर (!cond_resched())
			usleep_range(950, 1050);
	पूर्ण जबतक (--समयout);

	वापस -ETIMEDOUT;
पूर्ण

अटल व्योम exynos_dsi_set_cmd_lpm(काष्ठा exynos_dsi *dsi, bool lpm)
अणु
	u32 v = exynos_dsi_पढ़ो(dsi, DSIM_ESCMODE_REG);

	अगर (lpm)
		v |= DSIM_CMD_LPDT_LP;
	अन्यथा
		v &= ~DSIM_CMD_LPDT_LP;

	exynos_dsi_ग_लिखो(dsi, DSIM_ESCMODE_REG, v);
पूर्ण

अटल व्योम exynos_dsi_क्रमce_bta(काष्ठा exynos_dsi *dsi)
अणु
	u32 v = exynos_dsi_पढ़ो(dsi, DSIM_ESCMODE_REG);
	v |= DSIM_FORCE_BTA;
	exynos_dsi_ग_लिखो(dsi, DSIM_ESCMODE_REG, v);
पूर्ण

अटल व्योम exynos_dsi_send_to_fअगरo(काष्ठा exynos_dsi *dsi,
					काष्ठा exynos_dsi_transfer *xfer)
अणु
	काष्ठा device *dev = dsi->dev;
	काष्ठा mipi_dsi_packet *pkt = &xfer->packet;
	स्थिर u8 *payload = pkt->payload + xfer->tx_करोne;
	u16 length = pkt->payload_length - xfer->tx_करोne;
	bool first = !xfer->tx_करोne;
	u32 reg;

	dev_dbg(dev, "< xfer %pK: tx len %u, done %u, rx len %u, done %u\n",
		xfer, length, xfer->tx_करोne, xfer->rx_len, xfer->rx_करोne);

	अगर (length > DSI_TX_FIFO_SIZE)
		length = DSI_TX_FIFO_SIZE;

	xfer->tx_करोne += length;

	/* Send payload */
	जबतक (length >= 4) अणु
		reg = get_unaligned_le32(payload);
		exynos_dsi_ग_लिखो(dsi, DSIM_PAYLOAD_REG, reg);
		payload += 4;
		length -= 4;
	पूर्ण

	reg = 0;
	चयन (length) अणु
	हाल 3:
		reg |= payload[2] << 16;
		fallthrough;
	हाल 2:
		reg |= payload[1] << 8;
		fallthrough;
	हाल 1:
		reg |= payload[0];
		exynos_dsi_ग_लिखो(dsi, DSIM_PAYLOAD_REG, reg);
		अवरोध;
	पूर्ण

	/* Send packet header */
	अगर (!first)
		वापस;

	reg = get_unaligned_le32(pkt->header);
	अगर (exynos_dsi_रुको_क्रम_hdr_fअगरo(dsi)) अणु
		dev_err(dev, "waiting for header FIFO timed out\n");
		वापस;
	पूर्ण

	अगर (NEQV(xfer->flags & MIPI_DSI_MSG_USE_LPM,
		 dsi->state & DSIM_STATE_CMD_LPM)) अणु
		exynos_dsi_set_cmd_lpm(dsi, xfer->flags & MIPI_DSI_MSG_USE_LPM);
		dsi->state ^= DSIM_STATE_CMD_LPM;
	पूर्ण

	exynos_dsi_ग_लिखो(dsi, DSIM_PKTHDR_REG, reg);

	अगर (xfer->flags & MIPI_DSI_MSG_REQ_ACK)
		exynos_dsi_क्रमce_bta(dsi);
पूर्ण

अटल व्योम exynos_dsi_पढ़ो_from_fअगरo(काष्ठा exynos_dsi *dsi,
					काष्ठा exynos_dsi_transfer *xfer)
अणु
	u8 *payload = xfer->rx_payload + xfer->rx_करोne;
	bool first = !xfer->rx_करोne;
	काष्ठा device *dev = dsi->dev;
	u16 length;
	u32 reg;

	अगर (first) अणु
		reg = exynos_dsi_पढ़ो(dsi, DSIM_RXFIFO_REG);

		चयन (reg & 0x3f) अणु
		हाल MIPI_DSI_RX_GENERIC_SHORT_READ_RESPONSE_2BYTE:
		हाल MIPI_DSI_RX_DCS_SHORT_READ_RESPONSE_2BYTE:
			अगर (xfer->rx_len >= 2) अणु
				payload[1] = reg >> 16;
				++xfer->rx_करोne;
			पूर्ण
			fallthrough;
		हाल MIPI_DSI_RX_GENERIC_SHORT_READ_RESPONSE_1BYTE:
		हाल MIPI_DSI_RX_DCS_SHORT_READ_RESPONSE_1BYTE:
			payload[0] = reg >> 8;
			++xfer->rx_करोne;
			xfer->rx_len = xfer->rx_करोne;
			xfer->result = 0;
			जाओ clear_fअगरo;
		हाल MIPI_DSI_RX_ACKNOWLEDGE_AND_ERROR_REPORT:
			dev_err(dev, "DSI Error Report: 0x%04x\n",
				(reg >> 8) & 0xffff);
			xfer->result = 0;
			जाओ clear_fअगरo;
		पूर्ण

		length = (reg >> 8) & 0xffff;
		अगर (length > xfer->rx_len) अणु
			dev_err(dev,
				"response too long (%u > %u bytes), stripping\n",
				xfer->rx_len, length);
			length = xfer->rx_len;
		पूर्ण अन्यथा अगर (length < xfer->rx_len)
			xfer->rx_len = length;
	पूर्ण

	length = xfer->rx_len - xfer->rx_करोne;
	xfer->rx_करोne += length;

	/* Receive payload */
	जबतक (length >= 4) अणु
		reg = exynos_dsi_पढ़ो(dsi, DSIM_RXFIFO_REG);
		payload[0] = (reg >>  0) & 0xff;
		payload[1] = (reg >>  8) & 0xff;
		payload[2] = (reg >> 16) & 0xff;
		payload[3] = (reg >> 24) & 0xff;
		payload += 4;
		length -= 4;
	पूर्ण

	अगर (length) अणु
		reg = exynos_dsi_पढ़ो(dsi, DSIM_RXFIFO_REG);
		चयन (length) अणु
		हाल 3:
			payload[2] = (reg >> 16) & 0xff;
			fallthrough;
		हाल 2:
			payload[1] = (reg >> 8) & 0xff;
			fallthrough;
		हाल 1:
			payload[0] = reg & 0xff;
		पूर्ण
	पूर्ण

	अगर (xfer->rx_करोne == xfer->rx_len)
		xfer->result = 0;

clear_fअगरo:
	length = DSI_RX_FIFO_SIZE / 4;
	करो अणु
		reg = exynos_dsi_पढ़ो(dsi, DSIM_RXFIFO_REG);
		अगर (reg == DSI_RX_FIFO_EMPTY)
			अवरोध;
	पूर्ण जबतक (--length);
पूर्ण

अटल व्योम exynos_dsi_transfer_start(काष्ठा exynos_dsi *dsi)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा exynos_dsi_transfer *xfer;
	bool start = false;

again:
	spin_lock_irqsave(&dsi->transfer_lock, flags);

	अगर (list_empty(&dsi->transfer_list)) अणु
		spin_unlock_irqrestore(&dsi->transfer_lock, flags);
		वापस;
	पूर्ण

	xfer = list_first_entry(&dsi->transfer_list,
					काष्ठा exynos_dsi_transfer, list);

	spin_unlock_irqrestore(&dsi->transfer_lock, flags);

	अगर (xfer->packet.payload_length &&
	    xfer->tx_करोne == xfer->packet.payload_length)
		/* रुकोing क्रम RX */
		वापस;

	exynos_dsi_send_to_fअगरo(dsi, xfer);

	अगर (xfer->packet.payload_length || xfer->rx_len)
		वापस;

	xfer->result = 0;
	complete(&xfer->completed);

	spin_lock_irqsave(&dsi->transfer_lock, flags);

	list_del_init(&xfer->list);
	start = !list_empty(&dsi->transfer_list);

	spin_unlock_irqrestore(&dsi->transfer_lock, flags);

	अगर (start)
		जाओ again;
पूर्ण

अटल bool exynos_dsi_transfer_finish(काष्ठा exynos_dsi *dsi)
अणु
	काष्ठा exynos_dsi_transfer *xfer;
	अचिन्हित दीर्घ flags;
	bool start = true;

	spin_lock_irqsave(&dsi->transfer_lock, flags);

	अगर (list_empty(&dsi->transfer_list)) अणु
		spin_unlock_irqrestore(&dsi->transfer_lock, flags);
		वापस false;
	पूर्ण

	xfer = list_first_entry(&dsi->transfer_list,
					काष्ठा exynos_dsi_transfer, list);

	spin_unlock_irqrestore(&dsi->transfer_lock, flags);

	dev_dbg(dsi->dev,
		"> xfer %pK, tx_len %zu, tx_done %u, rx_len %u, rx_done %u\n",
		xfer, xfer->packet.payload_length, xfer->tx_करोne, xfer->rx_len,
		xfer->rx_करोne);

	अगर (xfer->tx_करोne != xfer->packet.payload_length)
		वापस true;

	अगर (xfer->rx_करोne != xfer->rx_len)
		exynos_dsi_पढ़ो_from_fअगरo(dsi, xfer);

	अगर (xfer->rx_करोne != xfer->rx_len)
		वापस true;

	spin_lock_irqsave(&dsi->transfer_lock, flags);

	list_del_init(&xfer->list);
	start = !list_empty(&dsi->transfer_list);

	spin_unlock_irqrestore(&dsi->transfer_lock, flags);

	अगर (!xfer->rx_len)
		xfer->result = 0;
	complete(&xfer->completed);

	वापस start;
पूर्ण

अटल व्योम exynos_dsi_हटाओ_transfer(काष्ठा exynos_dsi *dsi,
					काष्ठा exynos_dsi_transfer *xfer)
अणु
	अचिन्हित दीर्घ flags;
	bool start;

	spin_lock_irqsave(&dsi->transfer_lock, flags);

	अगर (!list_empty(&dsi->transfer_list) &&
	    xfer == list_first_entry(&dsi->transfer_list,
				     काष्ठा exynos_dsi_transfer, list)) अणु
		list_del_init(&xfer->list);
		start = !list_empty(&dsi->transfer_list);
		spin_unlock_irqrestore(&dsi->transfer_lock, flags);
		अगर (start)
			exynos_dsi_transfer_start(dsi);
		वापस;
	पूर्ण

	list_del_init(&xfer->list);

	spin_unlock_irqrestore(&dsi->transfer_lock, flags);
पूर्ण

अटल पूर्णांक exynos_dsi_transfer(काष्ठा exynos_dsi *dsi,
					काष्ठा exynos_dsi_transfer *xfer)
अणु
	अचिन्हित दीर्घ flags;
	bool stopped;

	xfer->tx_करोne = 0;
	xfer->rx_करोne = 0;
	xfer->result = -ETIMEDOUT;
	init_completion(&xfer->completed);

	spin_lock_irqsave(&dsi->transfer_lock, flags);

	stopped = list_empty(&dsi->transfer_list);
	list_add_tail(&xfer->list, &dsi->transfer_list);

	spin_unlock_irqrestore(&dsi->transfer_lock, flags);

	अगर (stopped)
		exynos_dsi_transfer_start(dsi);

	रुको_क्रम_completion_समयout(&xfer->completed,
				    msecs_to_jअगरfies(DSI_XFER_TIMEOUT_MS));
	अगर (xfer->result == -ETIMEDOUT) अणु
		काष्ठा mipi_dsi_packet *pkt = &xfer->packet;
		exynos_dsi_हटाओ_transfer(dsi, xfer);
		dev_err(dsi->dev, "xfer timed out: %*ph %*ph\n", 4, pkt->header,
			(पूर्णांक)pkt->payload_length, pkt->payload);
		वापस -ETIMEDOUT;
	पूर्ण

	/* Also covers hardware समयout condition */
	वापस xfer->result;
पूर्ण

अटल irqवापस_t exynos_dsi_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा exynos_dsi *dsi = dev_id;
	u32 status;

	status = exynos_dsi_पढ़ो(dsi, DSIM_INTSRC_REG);
	अगर (!status) अणु
		अटल अचिन्हित दीर्घ पूर्णांक j;
		अगर (prपूर्णांकk_समयd_ratelimit(&j, 500))
			dev_warn(dsi->dev, "spurious interrupt\n");
		वापस IRQ_HANDLED;
	पूर्ण
	exynos_dsi_ग_लिखो(dsi, DSIM_INTSRC_REG, status);

	अगर (status & DSIM_INT_SW_RST_RELEASE) अणु
		u32 mask = ~(DSIM_INT_RX_DONE | DSIM_INT_SFR_FIFO_EMPTY |
			DSIM_INT_SFR_HDR_FIFO_EMPTY | DSIM_INT_RX_ECC_ERR |
			DSIM_INT_SW_RST_RELEASE);
		exynos_dsi_ग_लिखो(dsi, DSIM_INTMSK_REG, mask);
		complete(&dsi->completed);
		वापस IRQ_HANDLED;
	पूर्ण

	अगर (!(status & (DSIM_INT_RX_DONE | DSIM_INT_SFR_FIFO_EMPTY |
			DSIM_INT_PLL_STABLE)))
		वापस IRQ_HANDLED;

	अगर (exynos_dsi_transfer_finish(dsi))
		exynos_dsi_transfer_start(dsi);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t exynos_dsi_te_irq_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा exynos_dsi *dsi = (काष्ठा exynos_dsi *)dev_id;
	काष्ठा drm_encoder *encoder = &dsi->encoder;

	अगर (dsi->state & DSIM_STATE_VIDOUT_AVAILABLE)
		exynos_drm_crtc_te_handler(encoder->crtc);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम exynos_dsi_enable_irq(काष्ठा exynos_dsi *dsi)
अणु
	enable_irq(dsi->irq);

	अगर (gpio_is_valid(dsi->te_gpio))
		enable_irq(gpio_to_irq(dsi->te_gpio));
पूर्ण

अटल व्योम exynos_dsi_disable_irq(काष्ठा exynos_dsi *dsi)
अणु
	अगर (gpio_is_valid(dsi->te_gpio))
		disable_irq(gpio_to_irq(dsi->te_gpio));

	disable_irq(dsi->irq);
पूर्ण

अटल पूर्णांक exynos_dsi_init(काष्ठा exynos_dsi *dsi)
अणु
	स्थिर काष्ठा exynos_dsi_driver_data *driver_data = dsi->driver_data;

	exynos_dsi_reset(dsi);
	exynos_dsi_enable_irq(dsi);

	अगर (driver_data->reg_values[RESET_TYPE] == DSIM_FUNCRST)
		exynos_dsi_enable_lane(dsi, BIT(dsi->lanes) - 1);

	exynos_dsi_enable_घड़ी(dsi);
	अगर (driver_data->रुको_क्रम_reset)
		exynos_dsi_रुको_क्रम_reset(dsi);
	exynos_dsi_set_phy_ctrl(dsi);
	exynos_dsi_init_link(dsi);

	वापस 0;
पूर्ण

अटल पूर्णांक exynos_dsi_रेजिस्टर_te_irq(काष्ठा exynos_dsi *dsi,
				      काष्ठा device *panel)
अणु
	पूर्णांक ret;
	पूर्णांक te_gpio_irq;

	dsi->te_gpio = of_get_named_gpio(panel->of_node, "te-gpios", 0);
	अगर (dsi->te_gpio == -ENOENT)
		वापस 0;

	अगर (!gpio_is_valid(dsi->te_gpio)) अणु
		ret = dsi->te_gpio;
		dev_err(dsi->dev, "cannot get te-gpios, %d\n", ret);
		जाओ out;
	पूर्ण

	ret = gpio_request(dsi->te_gpio, "te_gpio");
	अगर (ret) अणु
		dev_err(dsi->dev, "gpio request failed with %d\n", ret);
		जाओ out;
	पूर्ण

	te_gpio_irq = gpio_to_irq(dsi->te_gpio);

	ret = request_thपढ़ोed_irq(te_gpio_irq, exynos_dsi_te_irq_handler, शून्य,
				   IRQF_TRIGGER_RISING | IRQF_NO_AUTOEN, "TE", dsi);
	अगर (ret) अणु
		dev_err(dsi->dev, "request interrupt failed with %d\n", ret);
		gpio_मुक्त(dsi->te_gpio);
		जाओ out;
	पूर्ण

out:
	वापस ret;
पूर्ण

अटल व्योम exynos_dsi_unरेजिस्टर_te_irq(काष्ठा exynos_dsi *dsi)
अणु
	अगर (gpio_is_valid(dsi->te_gpio)) अणु
		मुक्त_irq(gpio_to_irq(dsi->te_gpio), dsi);
		gpio_मुक्त(dsi->te_gpio);
		dsi->te_gpio = -ENOENT;
	पूर्ण
पूर्ण

अटल व्योम exynos_dsi_enable(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा exynos_dsi *dsi = encoder_to_dsi(encoder);
	काष्ठा drm_bridge *iter;
	पूर्णांक ret;

	अगर (dsi->state & DSIM_STATE_ENABLED)
		वापस;

	pm_runसमय_get_sync(dsi->dev);
	dsi->state |= DSIM_STATE_ENABLED;

	अगर (dsi->panel) अणु
		ret = drm_panel_prepare(dsi->panel);
		अगर (ret < 0)
			जाओ err_put_sync;
	पूर्ण अन्यथा अणु
		list_क्रम_each_entry_reverse(iter, &dsi->bridge_chain,
					    chain_node) अणु
			अगर (iter->funcs->pre_enable)
				iter->funcs->pre_enable(iter);
		पूर्ण
	पूर्ण

	exynos_dsi_set_display_mode(dsi);
	exynos_dsi_set_display_enable(dsi, true);

	अगर (dsi->panel) अणु
		ret = drm_panel_enable(dsi->panel);
		अगर (ret < 0)
			जाओ err_display_disable;
	पूर्ण अन्यथा अणु
		list_क्रम_each_entry(iter, &dsi->bridge_chain, chain_node) अणु
			अगर (iter->funcs->enable)
				iter->funcs->enable(iter);
		पूर्ण
	पूर्ण

	dsi->state |= DSIM_STATE_VIDOUT_AVAILABLE;
	वापस;

err_display_disable:
	exynos_dsi_set_display_enable(dsi, false);
	drm_panel_unprepare(dsi->panel);

err_put_sync:
	dsi->state &= ~DSIM_STATE_ENABLED;
	pm_runसमय_put(dsi->dev);
पूर्ण

अटल व्योम exynos_dsi_disable(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा exynos_dsi *dsi = encoder_to_dsi(encoder);
	काष्ठा drm_bridge *iter;

	अगर (!(dsi->state & DSIM_STATE_ENABLED))
		वापस;

	dsi->state &= ~DSIM_STATE_VIDOUT_AVAILABLE;

	drm_panel_disable(dsi->panel);

	list_क्रम_each_entry_reverse(iter, &dsi->bridge_chain, chain_node) अणु
		अगर (iter->funcs->disable)
			iter->funcs->disable(iter);
	पूर्ण

	exynos_dsi_set_display_enable(dsi, false);
	drm_panel_unprepare(dsi->panel);

	list_क्रम_each_entry(iter, &dsi->bridge_chain, chain_node) अणु
		अगर (iter->funcs->post_disable)
			iter->funcs->post_disable(iter);
	पूर्ण

	dsi->state &= ~DSIM_STATE_ENABLED;
	pm_runसमय_put_sync(dsi->dev);
पूर्ण

अटल क्रमागत drm_connector_status
exynos_dsi_detect(काष्ठा drm_connector *connector, bool क्रमce)
अणु
	वापस connector->status;
पूर्ण

अटल व्योम exynos_dsi_connector_destroy(काष्ठा drm_connector *connector)
अणु
	drm_connector_unरेजिस्टर(connector);
	drm_connector_cleanup(connector);
	connector->dev = शून्य;
पूर्ण

अटल स्थिर काष्ठा drm_connector_funcs exynos_dsi_connector_funcs = अणु
	.detect = exynos_dsi_detect,
	.fill_modes = drm_helper_probe_single_connector_modes,
	.destroy = exynos_dsi_connector_destroy,
	.reset = drm_atomic_helper_connector_reset,
	.atomic_duplicate_state = drm_atomic_helper_connector_duplicate_state,
	.atomic_destroy_state = drm_atomic_helper_connector_destroy_state,
पूर्ण;

अटल पूर्णांक exynos_dsi_get_modes(काष्ठा drm_connector *connector)
अणु
	काष्ठा exynos_dsi *dsi = connector_to_dsi(connector);

	अगर (dsi->panel)
		वापस drm_panel_get_modes(dsi->panel, connector);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा drm_connector_helper_funcs exynos_dsi_connector_helper_funcs = अणु
	.get_modes = exynos_dsi_get_modes,
पूर्ण;

अटल पूर्णांक exynos_dsi_create_connector(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा exynos_dsi *dsi = encoder_to_dsi(encoder);
	काष्ठा drm_connector *connector = &dsi->connector;
	काष्ठा drm_device *drm = encoder->dev;
	पूर्णांक ret;

	connector->polled = DRM_CONNECTOR_POLL_HPD;

	ret = drm_connector_init(drm, connector, &exynos_dsi_connector_funcs,
				 DRM_MODE_CONNECTOR_DSI);
	अगर (ret) अणु
		DRM_DEV_ERROR(dsi->dev,
			      "Failed to initialize connector with drm\n");
		वापस ret;
	पूर्ण

	connector->status = connector_status_disconnected;
	drm_connector_helper_add(connector, &exynos_dsi_connector_helper_funcs);
	drm_connector_attach_encoder(connector, encoder);
	अगर (!drm->रेजिस्टरed)
		वापस 0;

	connector->funcs->reset(connector);
	drm_connector_रेजिस्टर(connector);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा drm_encoder_helper_funcs exynos_dsi_encoder_helper_funcs = अणु
	.enable = exynos_dsi_enable,
	.disable = exynos_dsi_disable,
पूर्ण;

MODULE_DEVICE_TABLE(of, exynos_dsi_of_match);

अटल पूर्णांक exynos_dsi_host_attach(काष्ठा mipi_dsi_host *host,
				  काष्ठा mipi_dsi_device *device)
अणु
	काष्ठा exynos_dsi *dsi = host_to_dsi(host);
	काष्ठा drm_encoder *encoder = &dsi->encoder;
	काष्ठा drm_device *drm = encoder->dev;
	काष्ठा drm_bridge *out_bridge;

	out_bridge  = of_drm_find_bridge(device->dev.of_node);
	अगर (out_bridge) अणु
		drm_bridge_attach(encoder, out_bridge, शून्य, 0);
		dsi->out_bridge = out_bridge;
		list_splice_init(&encoder->bridge_chain, &dsi->bridge_chain);
	पूर्ण अन्यथा अणु
		पूर्णांक ret = exynos_dsi_create_connector(encoder);

		अगर (ret) अणु
			DRM_DEV_ERROR(dsi->dev,
				      "failed to create connector ret = %d\n",
				      ret);
			drm_encoder_cleanup(encoder);
			वापस ret;
		पूर्ण

		dsi->panel = of_drm_find_panel(device->dev.of_node);
		अगर (IS_ERR(dsi->panel))
			dsi->panel = शून्य;
		अन्यथा
			dsi->connector.status = connector_status_connected;
	पूर्ण

	/*
	 * This is a temporary solution and should be made by more generic way.
	 *
	 * If attached panel device is क्रम command mode one, dsi should रेजिस्टर
	 * TE पूर्णांकerrupt handler.
	 */
	अगर (!(device->mode_flags & MIPI_DSI_MODE_VIDEO)) अणु
		पूर्णांक ret = exynos_dsi_रेजिस्टर_te_irq(dsi, &device->dev);
		अगर (ret)
			वापस ret;
	पूर्ण

	mutex_lock(&drm->mode_config.mutex);

	dsi->lanes = device->lanes;
	dsi->क्रमmat = device->क्रमmat;
	dsi->mode_flags = device->mode_flags;
	exynos_drm_crtc_get_by_type(drm, EXYNOS_DISPLAY_TYPE_LCD)->i80_mode =
			!(dsi->mode_flags & MIPI_DSI_MODE_VIDEO);

	mutex_unlock(&drm->mode_config.mutex);

	अगर (drm->mode_config.poll_enabled)
		drm_kms_helper_hotplug_event(drm);

	वापस 0;
पूर्ण

अटल पूर्णांक exynos_dsi_host_detach(काष्ठा mipi_dsi_host *host,
				  काष्ठा mipi_dsi_device *device)
अणु
	काष्ठा exynos_dsi *dsi = host_to_dsi(host);
	काष्ठा drm_device *drm = dsi->encoder.dev;

	अगर (dsi->panel) अणु
		mutex_lock(&drm->mode_config.mutex);
		exynos_dsi_disable(&dsi->encoder);
		dsi->panel = शून्य;
		dsi->connector.status = connector_status_disconnected;
		mutex_unlock(&drm->mode_config.mutex);
	पूर्ण अन्यथा अणु
		अगर (dsi->out_bridge->funcs->detach)
			dsi->out_bridge->funcs->detach(dsi->out_bridge);
		dsi->out_bridge = शून्य;
		INIT_LIST_HEAD(&dsi->bridge_chain);
	पूर्ण

	अगर (drm->mode_config.poll_enabled)
		drm_kms_helper_hotplug_event(drm);

	exynos_dsi_unरेजिस्टर_te_irq(dsi);

	वापस 0;
पूर्ण

अटल sमाप_प्रकार exynos_dsi_host_transfer(काष्ठा mipi_dsi_host *host,
					 स्थिर काष्ठा mipi_dsi_msg *msg)
अणु
	काष्ठा exynos_dsi *dsi = host_to_dsi(host);
	काष्ठा exynos_dsi_transfer xfer;
	पूर्णांक ret;

	अगर (!(dsi->state & DSIM_STATE_ENABLED))
		वापस -EINVAL;

	अगर (!(dsi->state & DSIM_STATE_INITIALIZED)) अणु
		ret = exynos_dsi_init(dsi);
		अगर (ret)
			वापस ret;
		dsi->state |= DSIM_STATE_INITIALIZED;
	पूर्ण

	ret = mipi_dsi_create_packet(&xfer.packet, msg);
	अगर (ret < 0)
		वापस ret;

	xfer.rx_len = msg->rx_len;
	xfer.rx_payload = msg->rx_buf;
	xfer.flags = msg->flags;

	ret = exynos_dsi_transfer(dsi, &xfer);
	वापस (ret < 0) ? ret : xfer.rx_करोne;
पूर्ण

अटल स्थिर काष्ठा mipi_dsi_host_ops exynos_dsi_ops = अणु
	.attach = exynos_dsi_host_attach,
	.detach = exynos_dsi_host_detach,
	.transfer = exynos_dsi_host_transfer,
पूर्ण;

अटल पूर्णांक exynos_dsi_of_पढ़ो_u32(स्थिर काष्ठा device_node *np,
				  स्थिर अक्षर *propname, u32 *out_value)
अणु
	पूर्णांक ret = of_property_पढ़ो_u32(np, propname, out_value);

	अगर (ret < 0)
		pr_err("%pOF: failed to get '%s' property\n", np, propname);

	वापस ret;
पूर्ण

क्रमागत अणु
	DSI_PORT_IN,
	DSI_PORT_OUT
पूर्ण;

अटल पूर्णांक exynos_dsi_parse_dt(काष्ठा exynos_dsi *dsi)
अणु
	काष्ठा device *dev = dsi->dev;
	काष्ठा device_node *node = dev->of_node;
	पूर्णांक ret;

	ret = exynos_dsi_of_पढ़ो_u32(node, "samsung,pll-clock-frequency",
				     &dsi->pll_clk_rate);
	अगर (ret < 0)
		वापस ret;

	ret = exynos_dsi_of_पढ़ो_u32(node, "samsung,burst-clock-frequency",
				     &dsi->burst_clk_rate);
	अगर (ret < 0)
		वापस ret;

	ret = exynos_dsi_of_पढ़ो_u32(node, "samsung,esc-clock-frequency",
				     &dsi->esc_clk_rate);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक exynos_dsi_bind(काष्ठा device *dev, काष्ठा device *master,
				व्योम *data)
अणु
	काष्ठा exynos_dsi *dsi = dev_get_drvdata(dev);
	काष्ठा drm_encoder *encoder = &dsi->encoder;
	काष्ठा drm_device *drm_dev = data;
	काष्ठा device_node *in_bridge_node;
	काष्ठा drm_bridge *in_bridge;
	पूर्णांक ret;

	drm_simple_encoder_init(drm_dev, encoder, DRM_MODE_ENCODER_TMDS);

	drm_encoder_helper_add(encoder, &exynos_dsi_encoder_helper_funcs);

	ret = exynos_drm_set_possible_crtcs(encoder, EXYNOS_DISPLAY_TYPE_LCD);
	अगर (ret < 0)
		वापस ret;

	in_bridge_node = of_graph_get_remote_node(dev->of_node, DSI_PORT_IN, 0);
	अगर (in_bridge_node) अणु
		in_bridge = of_drm_find_bridge(in_bridge_node);
		अगर (in_bridge)
			drm_bridge_attach(encoder, in_bridge, शून्य, 0);
		of_node_put(in_bridge_node);
	पूर्ण

	वापस mipi_dsi_host_रेजिस्टर(&dsi->dsi_host);
पूर्ण

अटल व्योम exynos_dsi_unbind(काष्ठा device *dev, काष्ठा device *master,
				व्योम *data)
अणु
	काष्ठा exynos_dsi *dsi = dev_get_drvdata(dev);
	काष्ठा drm_encoder *encoder = &dsi->encoder;

	exynos_dsi_disable(encoder);

	mipi_dsi_host_unरेजिस्टर(&dsi->dsi_host);
पूर्ण

अटल स्थिर काष्ठा component_ops exynos_dsi_component_ops = अणु
	.bind	= exynos_dsi_bind,
	.unbind	= exynos_dsi_unbind,
पूर्ण;

अटल पूर्णांक exynos_dsi_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा resource *res;
	काष्ठा exynos_dsi *dsi;
	पूर्णांक ret, i;

	dsi = devm_kzalloc(dev, माप(*dsi), GFP_KERNEL);
	अगर (!dsi)
		वापस -ENOMEM;

	/* To be checked as invalid one */
	dsi->te_gpio = -ENOENT;

	init_completion(&dsi->completed);
	spin_lock_init(&dsi->transfer_lock);
	INIT_LIST_HEAD(&dsi->transfer_list);
	INIT_LIST_HEAD(&dsi->bridge_chain);

	dsi->dsi_host.ops = &exynos_dsi_ops;
	dsi->dsi_host.dev = dev;

	dsi->dev = dev;
	dsi->driver_data = of_device_get_match_data(dev);

	dsi->supplies[0].supply = "vddcore";
	dsi->supplies[1].supply = "vddio";
	ret = devm_regulator_bulk_get(dev, ARRAY_SIZE(dsi->supplies),
				      dsi->supplies);
	अगर (ret)
		वापस dev_err_probe(dev, ret, "failed to get regulators\n");

	dsi->clks = devm_kसुस्मृति(dev,
			dsi->driver_data->num_clks, माप(*dsi->clks),
			GFP_KERNEL);
	अगर (!dsi->clks)
		वापस -ENOMEM;

	क्रम (i = 0; i < dsi->driver_data->num_clks; i++) अणु
		dsi->clks[i] = devm_clk_get(dev, clk_names[i]);
		अगर (IS_ERR(dsi->clks[i])) अणु
			अगर (म_भेद(clk_names[i], "sclk_mipi") == 0) अणु
				dsi->clks[i] = devm_clk_get(dev,
							OLD_SCLK_MIPI_CLK_NAME);
				अगर (!IS_ERR(dsi->clks[i]))
					जारी;
			पूर्ण

			dev_info(dev, "failed to get the clock: %s\n",
					clk_names[i]);
			वापस PTR_ERR(dsi->clks[i]);
		पूर्ण
	पूर्ण

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	dsi->reg_base = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(dsi->reg_base))
		वापस PTR_ERR(dsi->reg_base);

	dsi->phy = devm_phy_get(dev, "dsim");
	अगर (IS_ERR(dsi->phy)) अणु
		dev_info(dev, "failed to get dsim phy\n");
		वापस PTR_ERR(dsi->phy);
	पूर्ण

	dsi->irq = platक्रमm_get_irq(pdev, 0);
	अगर (dsi->irq < 0)
		वापस dsi->irq;

	ret = devm_request_thपढ़ोed_irq(dev, dsi->irq, शून्य,
					exynos_dsi_irq,
					IRQF_ONESHOT | IRQF_NO_AUTOEN,
					dev_name(dev), dsi);
	अगर (ret) अणु
		dev_err(dev, "failed to request dsi irq\n");
		वापस ret;
	पूर्ण

	ret = exynos_dsi_parse_dt(dsi);
	अगर (ret)
		वापस ret;

	platक्रमm_set_drvdata(pdev, dsi);

	pm_runसमय_enable(dev);

	ret = component_add(dev, &exynos_dsi_component_ops);
	अगर (ret)
		जाओ err_disable_runसमय;

	वापस 0;

err_disable_runसमय:
	pm_runसमय_disable(dev);

	वापस ret;
पूर्ण

अटल पूर्णांक exynos_dsi_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	pm_runसमय_disable(&pdev->dev);

	component_del(&pdev->dev, &exynos_dsi_component_ops);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused exynos_dsi_suspend(काष्ठा device *dev)
अणु
	काष्ठा exynos_dsi *dsi = dev_get_drvdata(dev);
	स्थिर काष्ठा exynos_dsi_driver_data *driver_data = dsi->driver_data;
	पूर्णांक ret, i;

	usleep_range(10000, 20000);

	अगर (dsi->state & DSIM_STATE_INITIALIZED) अणु
		dsi->state &= ~DSIM_STATE_INITIALIZED;

		exynos_dsi_disable_घड़ी(dsi);

		exynos_dsi_disable_irq(dsi);
	पूर्ण

	dsi->state &= ~DSIM_STATE_CMD_LPM;

	phy_घातer_off(dsi->phy);

	क्रम (i = driver_data->num_clks - 1; i > -1; i--)
		clk_disable_unprepare(dsi->clks[i]);

	ret = regulator_bulk_disable(ARRAY_SIZE(dsi->supplies), dsi->supplies);
	अगर (ret < 0)
		dev_err(dsi->dev, "cannot disable regulators %d\n", ret);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused exynos_dsi_resume(काष्ठा device *dev)
अणु
	काष्ठा exynos_dsi *dsi = dev_get_drvdata(dev);
	स्थिर काष्ठा exynos_dsi_driver_data *driver_data = dsi->driver_data;
	पूर्णांक ret, i;

	ret = regulator_bulk_enable(ARRAY_SIZE(dsi->supplies), dsi->supplies);
	अगर (ret < 0) अणु
		dev_err(dsi->dev, "cannot enable regulators %d\n", ret);
		वापस ret;
	पूर्ण

	क्रम (i = 0; i < driver_data->num_clks; i++) अणु
		ret = clk_prepare_enable(dsi->clks[i]);
		अगर (ret < 0)
			जाओ err_clk;
	पूर्ण

	ret = phy_घातer_on(dsi->phy);
	अगर (ret < 0) अणु
		dev_err(dsi->dev, "cannot enable phy %d\n", ret);
		जाओ err_clk;
	पूर्ण

	वापस 0;

err_clk:
	जबतक (--i > -1)
		clk_disable_unprepare(dsi->clks[i]);
	regulator_bulk_disable(ARRAY_SIZE(dsi->supplies), dsi->supplies);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops exynos_dsi_pm_ops = अणु
	SET_RUNTIME_PM_OPS(exynos_dsi_suspend, exynos_dsi_resume, शून्य)
	SET_SYSTEM_SLEEP_PM_OPS(pm_runसमय_क्रमce_suspend,
				pm_runसमय_क्रमce_resume)
पूर्ण;

काष्ठा platक्रमm_driver dsi_driver = अणु
	.probe = exynos_dsi_probe,
	.हटाओ = exynos_dsi_हटाओ,
	.driver = अणु
		   .name = "exynos-dsi",
		   .owner = THIS_MODULE,
		   .pm = &exynos_dsi_pm_ops,
		   .of_match_table = exynos_dsi_of_match,
	पूर्ण,
पूर्ण;

MODULE_AUTHOR("Tomasz Figa <t.figa@samsung.com>");
MODULE_AUTHOR("Andrzej Hajda <a.hajda@samsung.com>");
MODULE_DESCRIPTION("Samsung SoC MIPI DSI Master");
MODULE_LICENSE("GPL v2");
