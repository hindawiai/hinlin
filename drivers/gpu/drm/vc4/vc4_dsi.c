<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2016 Broadcom
 */

/**
 * DOC: VC4 DSI0/DSI1 module
 *
 * BCM2835 contains two DSI modules, DSI0 and DSI1.  DSI0 is a
 * single-lane DSI controller, जबतक DSI1 is a more modern 4-lane DSI
 * controller.
 *
 * Most Raspberry Pi boards expose DSI1 as their "DISPLAY" connector,
 * जबतक the compute module brings both DSI0 and DSI1 out.
 *
 * This driver has been tested क्रम DSI1 video-mode display only
 * currently, with most of the inक्रमmation necessary क्रम DSI0
 * hopefully present.
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/clk.h>
#समावेश <linux/completion.h>
#समावेश <linux/component.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/i2c.h>
#समावेश <linux/पन.स>
#समावेश <linux/of_address.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/pm_runसमय.स>

#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_bridge.h>
#समावेश <drm/drm_edid.h>
#समावेश <drm/drm_mipi_dsi.h>
#समावेश <drm/drm_of.h>
#समावेश <drm/drm_panel.h>
#समावेश <drm/drm_probe_helper.h>
#समावेश <drm/drm_simple_kms_helper.h>

#समावेश "vc4_drv.h"
#समावेश "vc4_regs.h"

#घोषणा DSI_CMD_FIFO_DEPTH  16
#घोषणा DSI_PIX_FIFO_DEPTH 256
#घोषणा DSI_PIX_FIFO_WIDTH   4

#घोषणा DSI0_CTRL		0x00

/* Command packet control. */
#घोषणा DSI0_TXPKT1C		0x04 /* AKA PKTC */
#घोषणा DSI1_TXPKT1C		0x04
# define DSI_TXPKT1C_TRIG_CMD_MASK	VC4_MASK(31, 24)
# define DSI_TXPKT1C_TRIG_CMD_SHIFT	24
# define DSI_TXPKT1C_CMD_REPEAT_MASK	VC4_MASK(23, 10)
# define DSI_TXPKT1C_CMD_REPEAT_SHIFT	10

# define DSI_TXPKT1C_DISPLAY_NO_MASK	VC4_MASK(9, 8)
# define DSI_TXPKT1C_DISPLAY_NO_SHIFT	8
/* Short, trigger, BTA, or a दीर्घ packet that fits all in CMDFIFO. */
# define DSI_TXPKT1C_DISPLAY_NO_SHORT		0
/* Primary display where cmdfअगरo provides part of the payload and
 * pixelvalve the rest.
 */
# define DSI_TXPKT1C_DISPLAY_NO_PRIMARY		1
/* Secondary display where cmdfअगरo provides part of the payload and
 * pixfअगरo the rest.
 */
# define DSI_TXPKT1C_DISPLAY_NO_SECONDARY	2

# define DSI_TXPKT1C_CMD_TX_TIME_MASK	VC4_MASK(7, 6)
# define DSI_TXPKT1C_CMD_TX_TIME_SHIFT	6

# define DSI_TXPKT1C_CMD_CTRL_MASK	VC4_MASK(5, 4)
# define DSI_TXPKT1C_CMD_CTRL_SHIFT	4
/* Command only.  Uses TXPKT1H and DISPLAY_NO */
# define DSI_TXPKT1C_CMD_CTRL_TX	0
/* Command with BTA क्रम either ack or पढ़ो data. */
# define DSI_TXPKT1C_CMD_CTRL_RX	1
/* Trigger according to TRIG_CMD */
# define DSI_TXPKT1C_CMD_CTRL_TRIG	2
/* BTA alone क्रम getting error status after a command, or a TE trigger
 * without a previous command.
 */
# define DSI_TXPKT1C_CMD_CTRL_BTA	3

# define DSI_TXPKT1C_CMD_MODE_LP	BIT(3)
# define DSI_TXPKT1C_CMD_TYPE_LONG	BIT(2)
# define DSI_TXPKT1C_CMD_TE_EN		BIT(1)
# define DSI_TXPKT1C_CMD_EN		BIT(0)

/* Command packet header. */
#घोषणा DSI0_TXPKT1H		0x08 /* AKA PKTH */
#घोषणा DSI1_TXPKT1H		0x08
# define DSI_TXPKT1H_BC_CMDFIFO_MASK	VC4_MASK(31, 24)
# define DSI_TXPKT1H_BC_CMDFIFO_SHIFT	24
# define DSI_TXPKT1H_BC_PARAM_MASK	VC4_MASK(23, 8)
# define DSI_TXPKT1H_BC_PARAM_SHIFT	8
# define DSI_TXPKT1H_BC_DT_MASK		VC4_MASK(7, 0)
# define DSI_TXPKT1H_BC_DT_SHIFT	0

#घोषणा DSI0_RXPKT1H		0x0c /* AKA RX1_PKTH */
#घोषणा DSI1_RXPKT1H		0x14
# define DSI_RXPKT1H_CRC_ERR		BIT(31)
# define DSI_RXPKT1H_DET_ERR		BIT(30)
# define DSI_RXPKT1H_ECC_ERR		BIT(29)
# define DSI_RXPKT1H_COR_ERR		BIT(28)
# define DSI_RXPKT1H_INCOMP_PKT		BIT(25)
# define DSI_RXPKT1H_PKT_TYPE_LONG	BIT(24)
/* Byte count अगर DSI_RXPKT1H_PKT_TYPE_LONG */
# define DSI_RXPKT1H_BC_PARAM_MASK	VC4_MASK(23, 8)
# define DSI_RXPKT1H_BC_PARAM_SHIFT	8
/* Short वापस bytes अगर !DSI_RXPKT1H_PKT_TYPE_LONG */
# define DSI_RXPKT1H_SHORT_1_MASK	VC4_MASK(23, 16)
# define DSI_RXPKT1H_SHORT_1_SHIFT	16
# define DSI_RXPKT1H_SHORT_0_MASK	VC4_MASK(15, 8)
# define DSI_RXPKT1H_SHORT_0_SHIFT	8
# define DSI_RXPKT1H_DT_LP_CMD_MASK	VC4_MASK(7, 0)
# define DSI_RXPKT1H_DT_LP_CMD_SHIFT	0

#घोषणा DSI0_RXPKT2H		0x10 /* AKA RX2_PKTH */
#घोषणा DSI1_RXPKT2H		0x18
# define DSI_RXPKT1H_DET_ERR		BIT(30)
# define DSI_RXPKT1H_ECC_ERR		BIT(29)
# define DSI_RXPKT1H_COR_ERR		BIT(28)
# define DSI_RXPKT1H_INCOMP_PKT		BIT(25)
# define DSI_RXPKT1H_BC_PARAM_MASK	VC4_MASK(23, 8)
# define DSI_RXPKT1H_BC_PARAM_SHIFT	8
# define DSI_RXPKT1H_DT_MASK		VC4_MASK(7, 0)
# define DSI_RXPKT1H_DT_SHIFT		0

#घोषणा DSI0_TXPKT_CMD_FIFO	0x14 /* AKA CMD_DATAF */
#घोषणा DSI1_TXPKT_CMD_FIFO	0x1c

#घोषणा DSI0_DISP0_CTRL		0x18
# define DSI_DISP0_PIX_CLK_DIV_MASK	VC4_MASK(21, 13)
# define DSI_DISP0_PIX_CLK_DIV_SHIFT	13
# define DSI_DISP0_LP_STOP_CTRL_MASK	VC4_MASK(12, 11)
# define DSI_DISP0_LP_STOP_CTRL_SHIFT	11
# define DSI_DISP0_LP_STOP_DISABLE	0
# define DSI_DISP0_LP_STOP_PERLINE	1
# define DSI_DISP0_LP_STOP_PERFRAME	2

/* Transmit RGB pixels and null packets only during HACTIVE, instead
 * of going to LP-STOP.
 */
# define DSI_DISP_HACTIVE_शून्य		BIT(10)
/* Transmit blanking packet only during vblank, instead of allowing LP-STOP. */
# define DSI_DISP_VBLP_CTRL		BIT(9)
/* Transmit blanking packet only during HFP, instead of allowing LP-STOP. */
# define DSI_DISP_HFP_CTRL		BIT(8)
/* Transmit blanking packet only during HBP, instead of allowing LP-STOP. */
# define DSI_DISP_HBP_CTRL		BIT(7)
# define DSI_DISP0_CHANNEL_MASK		VC4_MASK(6, 5)
# define DSI_DISP0_CHANNEL_SHIFT	5
/* Enables end events क्रम HSYNC/VSYNC, not just start events. */
# define DSI_DISP0_ST_END		BIT(4)
# define DSI_DISP0_PFORMAT_MASK		VC4_MASK(3, 2)
# define DSI_DISP0_PFORMAT_SHIFT	2
# define DSI_PFORMAT_RGB565		0
# define DSI_PFORMAT_RGB666_PACKED	1
# define DSI_PFORMAT_RGB666		2
# define DSI_PFORMAT_RGB888		3
/* Default is VIDEO mode. */
# define DSI_DISP0_COMMAND_MODE		BIT(1)
# define DSI_DISP0_ENABLE		BIT(0)

#घोषणा DSI0_DISP1_CTRL		0x1c
#घोषणा DSI1_DISP1_CTRL		0x2c
/* Format of the data written to TXPKT_PIX_FIFO. */
# define DSI_DISP1_PFORMAT_MASK		VC4_MASK(2, 1)
# define DSI_DISP1_PFORMAT_SHIFT	1
# define DSI_DISP1_PFORMAT_16BIT	0
# define DSI_DISP1_PFORMAT_24BIT	1
# define DSI_DISP1_PFORMAT_32BIT_LE	2
# define DSI_DISP1_PFORMAT_32BIT_BE	3

/* DISP1 is always command mode. */
# define DSI_DISP1_ENABLE		BIT(0)

#घोषणा DSI0_TXPKT_PIX_FIFO		0x20 /* AKA PIX_FIFO */

#घोषणा DSI0_INT_STAT		0x24
#घोषणा DSI0_INT_EN		0x28
# define DSI1_INT_PHY_D3_ULPS		BIT(30)
# define DSI1_INT_PHY_D3_STOP		BIT(29)
# define DSI1_INT_PHY_D2_ULPS		BIT(28)
# define DSI1_INT_PHY_D2_STOP		BIT(27)
# define DSI1_INT_PHY_D1_ULPS		BIT(26)
# define DSI1_INT_PHY_D1_STOP		BIT(25)
# define DSI1_INT_PHY_D0_ULPS		BIT(24)
# define DSI1_INT_PHY_D0_STOP		BIT(23)
# define DSI1_INT_FIFO_ERR		BIT(22)
# define DSI1_INT_PHY_सूची_RTF		BIT(21)
# define DSI1_INT_PHY_RXLPDT		BIT(20)
# define DSI1_INT_PHY_RXTRIG		BIT(19)
# define DSI1_INT_PHY_D0_LPDT		BIT(18)
# define DSI1_INT_PHY_सूची_FTR		BIT(17)

/* Signaled when the घड़ी lane enters the given state. */
# define DSI1_INT_PHY_CLOCK_ULPS	BIT(16)
# define DSI1_INT_PHY_CLOCK_HS		BIT(15)
# define DSI1_INT_PHY_CLOCK_STOP	BIT(14)

/* Signaled on समयouts */
# define DSI1_INT_PR_TO			BIT(13)
# define DSI1_INT_TA_TO			BIT(12)
# define DSI1_INT_LPRX_TO		BIT(11)
# define DSI1_INT_HSTX_TO		BIT(10)

/* Contention on a line when trying to drive the line low */
# define DSI1_INT_ERR_CONT_LP1		BIT(9)
# define DSI1_INT_ERR_CONT_LP0		BIT(8)

/* Control error: incorrect line state sequence on data lane 0. */
# define DSI1_INT_ERR_CONTROL		BIT(7)
/* LPDT synchronization error (bits received not a multiple of 8. */

# define DSI1_INT_ERR_SYNC_ESC		BIT(6)
/* Signaled after receiving an error packet from the display in
 * response to a पढ़ो.
 */
# define DSI1_INT_RXPKT2		BIT(5)
/* Signaled after receiving a packet.  The header and optional लघु
 * response will be in RXPKT1H, and a दीर्घ response will be in the
 * RXPKT_FIFO.
 */
# define DSI1_INT_RXPKT1		BIT(4)
# define DSI1_INT_TXPKT2_DONE		BIT(3)
# define DSI1_INT_TXPKT2_END		BIT(2)
/* Signaled after all repeats of TXPKT1 are transferred. */
# define DSI1_INT_TXPKT1_DONE		BIT(1)
/* Signaled after each TXPKT1 repeat is scheduled. */
# define DSI1_INT_TXPKT1_END		BIT(0)

#घोषणा DSI1_INTERRUPTS_ALWAYS_ENABLED	(DSI1_INT_ERR_SYNC_ESC | \
					 DSI1_INT_ERR_CONTROL |	 \
					 DSI1_INT_ERR_CONT_LP0 | \
					 DSI1_INT_ERR_CONT_LP1 | \
					 DSI1_INT_HSTX_TO |	 \
					 DSI1_INT_LPRX_TO |	 \
					 DSI1_INT_TA_TO |	 \
					 DSI1_INT_PR_TO)

#घोषणा DSI0_STAT		0x2c
#घोषणा DSI0_HSTX_TO_CNT	0x30
#घोषणा DSI0_LPRX_TO_CNT	0x34
#घोषणा DSI0_TA_TO_CNT		0x38
#घोषणा DSI0_PR_TO_CNT		0x3c
#घोषणा DSI0_PHYC		0x40
# define DSI1_PHYC_ESC_CLK_LPDT_MASK	VC4_MASK(25, 20)
# define DSI1_PHYC_ESC_CLK_LPDT_SHIFT	20
# define DSI1_PHYC_HS_CLK_CONTINUOUS	BIT(18)
# define DSI0_PHYC_ESC_CLK_LPDT_MASK	VC4_MASK(17, 12)
# define DSI0_PHYC_ESC_CLK_LPDT_SHIFT	12
# define DSI1_PHYC_CLANE_ULPS		BIT(17)
# define DSI1_PHYC_CLANE_ENABLE		BIT(16)
# define DSI_PHYC_DLANE3_ULPS		BIT(13)
# define DSI_PHYC_DLANE3_ENABLE		BIT(12)
# define DSI0_PHYC_HS_CLK_CONTINUOUS	BIT(10)
# define DSI0_PHYC_CLANE_ULPS		BIT(9)
# define DSI_PHYC_DLANE2_ULPS		BIT(9)
# define DSI0_PHYC_CLANE_ENABLE		BIT(8)
# define DSI_PHYC_DLANE2_ENABLE		BIT(8)
# define DSI_PHYC_DLANE1_ULPS		BIT(5)
# define DSI_PHYC_DLANE1_ENABLE		BIT(4)
# define DSI_PHYC_DLANE0_FORCE_STOP	BIT(2)
# define DSI_PHYC_DLANE0_ULPS		BIT(1)
# define DSI_PHYC_DLANE0_ENABLE		BIT(0)

#घोषणा DSI0_HS_CLT0		0x44
#घोषणा DSI0_HS_CLT1		0x48
#घोषणा DSI0_HS_CLT2		0x4c
#घोषणा DSI0_HS_DLT3		0x50
#घोषणा DSI0_HS_DLT4		0x54
#घोषणा DSI0_HS_DLT5		0x58
#घोषणा DSI0_HS_DLT6		0x5c
#घोषणा DSI0_HS_DLT7		0x60

#घोषणा DSI0_PHY_AFEC0		0x64
# define DSI0_PHY_AFEC0_DDR2CLK_EN		BIT(26)
# define DSI0_PHY_AFEC0_DDRCLK_EN		BIT(25)
# define DSI0_PHY_AFEC0_LATCH_ULPS		BIT(24)
# define DSI1_PHY_AFEC0_IDR_DLANE3_MASK		VC4_MASK(31, 29)
# define DSI1_PHY_AFEC0_IDR_DLANE3_SHIFT	29
# define DSI1_PHY_AFEC0_IDR_DLANE2_MASK		VC4_MASK(28, 26)
# define DSI1_PHY_AFEC0_IDR_DLANE2_SHIFT	26
# define DSI1_PHY_AFEC0_IDR_DLANE1_MASK		VC4_MASK(27, 23)
# define DSI1_PHY_AFEC0_IDR_DLANE1_SHIFT	23
# define DSI1_PHY_AFEC0_IDR_DLANE0_MASK		VC4_MASK(22, 20)
# define DSI1_PHY_AFEC0_IDR_DLANE0_SHIFT	20
# define DSI1_PHY_AFEC0_IDR_CLANE_MASK		VC4_MASK(19, 17)
# define DSI1_PHY_AFEC0_IDR_CLANE_SHIFT		17
# define DSI0_PHY_AFEC0_ACTRL_DLANE1_MASK	VC4_MASK(23, 20)
# define DSI0_PHY_AFEC0_ACTRL_DLANE1_SHIFT	20
# define DSI0_PHY_AFEC0_ACTRL_DLANE0_MASK	VC4_MASK(19, 16)
# define DSI0_PHY_AFEC0_ACTRL_DLANE0_SHIFT	16
# define DSI0_PHY_AFEC0_ACTRL_CLANE_MASK	VC4_MASK(15, 12)
# define DSI0_PHY_AFEC0_ACTRL_CLANE_SHIFT	12
# define DSI1_PHY_AFEC0_DDR2CLK_EN		BIT(16)
# define DSI1_PHY_AFEC0_DDRCLK_EN		BIT(15)
# define DSI1_PHY_AFEC0_LATCH_ULPS		BIT(14)
# define DSI1_PHY_AFEC0_RESET			BIT(13)
# define DSI1_PHY_AFEC0_PD			BIT(12)
# define DSI0_PHY_AFEC0_RESET			BIT(11)
# define DSI1_PHY_AFEC0_PD_BG			BIT(11)
# define DSI0_PHY_AFEC0_PD			BIT(10)
# define DSI1_PHY_AFEC0_PD_DLANE1		BIT(10)
# define DSI0_PHY_AFEC0_PD_BG			BIT(9)
# define DSI1_PHY_AFEC0_PD_DLANE2		BIT(9)
# define DSI0_PHY_AFEC0_PD_DLANE1		BIT(8)
# define DSI1_PHY_AFEC0_PD_DLANE3		BIT(8)
# define DSI_PHY_AFEC0_PTATADJ_MASK		VC4_MASK(7, 4)
# define DSI_PHY_AFEC0_PTATADJ_SHIFT		4
# define DSI_PHY_AFEC0_CTATADJ_MASK		VC4_MASK(3, 0)
# define DSI_PHY_AFEC0_CTATADJ_SHIFT		0

#घोषणा DSI0_PHY_AFEC1		0x68
# define DSI0_PHY_AFEC1_IDR_DLANE1_MASK		VC4_MASK(10, 8)
# define DSI0_PHY_AFEC1_IDR_DLANE1_SHIFT	8
# define DSI0_PHY_AFEC1_IDR_DLANE0_MASK		VC4_MASK(6, 4)
# define DSI0_PHY_AFEC1_IDR_DLANE0_SHIFT	4
# define DSI0_PHY_AFEC1_IDR_CLANE_MASK		VC4_MASK(2, 0)
# define DSI0_PHY_AFEC1_IDR_CLANE_SHIFT		0

#घोषणा DSI0_TST_SEL		0x6c
#घोषणा DSI0_TST_MON		0x70
#घोषणा DSI0_ID			0x74
# define DSI_ID_VALUE		0x00647369

#घोषणा DSI1_CTRL		0x00
# define DSI_CTRL_HS_CLKC_MASK		VC4_MASK(15, 14)
# define DSI_CTRL_HS_CLKC_SHIFT		14
# define DSI_CTRL_HS_CLKC_BYTE		0
# define DSI_CTRL_HS_CLKC_DDR2		1
# define DSI_CTRL_HS_CLKC_DDR		2

# define DSI_CTRL_RX_LPDT_EOT_DISABLE	BIT(13)
# define DSI_CTRL_LPDT_EOT_DISABLE	BIT(12)
# define DSI_CTRL_HSDT_EOT_DISABLE	BIT(11)
# define DSI_CTRL_SOFT_RESET_CFG	BIT(10)
# define DSI_CTRL_CAL_BYTE		BIT(9)
# define DSI_CTRL_INV_BYTE		BIT(8)
# define DSI_CTRL_CLR_LDF		BIT(7)
# define DSI0_CTRL_CLR_PBCF		BIT(6)
# define DSI1_CTRL_CLR_RXF		BIT(6)
# define DSI0_CTRL_CLR_CPBCF		BIT(5)
# define DSI1_CTRL_CLR_PDF		BIT(5)
# define DSI0_CTRL_CLR_PDF		BIT(4)
# define DSI1_CTRL_CLR_CDF		BIT(4)
# define DSI0_CTRL_CLR_CDF		BIT(3)
# define DSI0_CTRL_CTRL2		BIT(2)
# define DSI1_CTRL_DISABLE_DISP_CRCC	BIT(2)
# define DSI0_CTRL_CTRL1		BIT(1)
# define DSI1_CTRL_DISABLE_DISP_ECCC	BIT(1)
# define DSI0_CTRL_CTRL0		BIT(0)
# define DSI1_CTRL_EN			BIT(0)
# define DSI0_CTRL_RESET_FIFOS		(DSI_CTRL_CLR_LDF | \
					 DSI0_CTRL_CLR_PBCF | \
					 DSI0_CTRL_CLR_CPBCF |	\
					 DSI0_CTRL_CLR_PDF | \
					 DSI0_CTRL_CLR_CDF)
# define DSI1_CTRL_RESET_FIFOS		(DSI_CTRL_CLR_LDF | \
					 DSI1_CTRL_CLR_RXF | \
					 DSI1_CTRL_CLR_PDF | \
					 DSI1_CTRL_CLR_CDF)

#घोषणा DSI1_TXPKT2C		0x0c
#घोषणा DSI1_TXPKT2H		0x10
#घोषणा DSI1_TXPKT_PIX_FIFO	0x20
#घोषणा DSI1_RXPKT_FIFO		0x24
#घोषणा DSI1_DISP0_CTRL		0x28
#घोषणा DSI1_INT_STAT		0x30
#घोषणा DSI1_INT_EN		0x34
/* State reporting bits.  These mostly behave like INT_STAT, where
 * writing a 1 clears the bit.
 */
#घोषणा DSI1_STAT		0x38
# define DSI1_STAT_PHY_D3_ULPS		BIT(31)
# define DSI1_STAT_PHY_D3_STOP		BIT(30)
# define DSI1_STAT_PHY_D2_ULPS		BIT(29)
# define DSI1_STAT_PHY_D2_STOP		BIT(28)
# define DSI1_STAT_PHY_D1_ULPS		BIT(27)
# define DSI1_STAT_PHY_D1_STOP		BIT(26)
# define DSI1_STAT_PHY_D0_ULPS		BIT(25)
# define DSI1_STAT_PHY_D0_STOP		BIT(24)
# define DSI1_STAT_FIFO_ERR		BIT(23)
# define DSI1_STAT_PHY_RXLPDT		BIT(22)
# define DSI1_STAT_PHY_RXTRIG		BIT(21)
# define DSI1_STAT_PHY_D0_LPDT		BIT(20)
/* Set when in क्रमward direction */
# define DSI1_STAT_PHY_सूची		BIT(19)
# define DSI1_STAT_PHY_CLOCK_ULPS	BIT(18)
# define DSI1_STAT_PHY_CLOCK_HS		BIT(17)
# define DSI1_STAT_PHY_CLOCK_STOP	BIT(16)
# define DSI1_STAT_PR_TO		BIT(15)
# define DSI1_STAT_TA_TO		BIT(14)
# define DSI1_STAT_LPRX_TO		BIT(13)
# define DSI1_STAT_HSTX_TO		BIT(12)
# define DSI1_STAT_ERR_CONT_LP1		BIT(11)
# define DSI1_STAT_ERR_CONT_LP0		BIT(10)
# define DSI1_STAT_ERR_CONTROL		BIT(9)
# define DSI1_STAT_ERR_SYNC_ESC		BIT(8)
# define DSI1_STAT_RXPKT2		BIT(7)
# define DSI1_STAT_RXPKT1		BIT(6)
# define DSI1_STAT_TXPKT2_BUSY		BIT(5)
# define DSI1_STAT_TXPKT2_DONE		BIT(4)
# define DSI1_STAT_TXPKT2_END		BIT(3)
# define DSI1_STAT_TXPKT1_BUSY		BIT(2)
# define DSI1_STAT_TXPKT1_DONE		BIT(1)
# define DSI1_STAT_TXPKT1_END		BIT(0)

#घोषणा DSI1_HSTX_TO_CNT	0x3c
#घोषणा DSI1_LPRX_TO_CNT	0x40
#घोषणा DSI1_TA_TO_CNT		0x44
#घोषणा DSI1_PR_TO_CNT		0x48
#घोषणा DSI1_PHYC		0x4c

#घोषणा DSI1_HS_CLT0		0x50
# define DSI_HS_CLT0_CZERO_MASK		VC4_MASK(26, 18)
# define DSI_HS_CLT0_CZERO_SHIFT	18
# define DSI_HS_CLT0_CPRE_MASK		VC4_MASK(17, 9)
# define DSI_HS_CLT0_CPRE_SHIFT		9
# define DSI_HS_CLT0_CPREP_MASK		VC4_MASK(8, 0)
# define DSI_HS_CLT0_CPREP_SHIFT	0

#घोषणा DSI1_HS_CLT1		0x54
# define DSI_HS_CLT1_CTRAIL_MASK	VC4_MASK(17, 9)
# define DSI_HS_CLT1_CTRAIL_SHIFT	9
# define DSI_HS_CLT1_CPOST_MASK		VC4_MASK(8, 0)
# define DSI_HS_CLT1_CPOST_SHIFT	0

#घोषणा DSI1_HS_CLT2		0x58
# define DSI_HS_CLT2_WUP_MASK		VC4_MASK(23, 0)
# define DSI_HS_CLT2_WUP_SHIFT		0

#घोषणा DSI1_HS_DLT3		0x5c
# define DSI_HS_DLT3_EXIT_MASK		VC4_MASK(26, 18)
# define DSI_HS_DLT3_EXIT_SHIFT		18
# define DSI_HS_DLT3_ZERO_MASK		VC4_MASK(17, 9)
# define DSI_HS_DLT3_ZERO_SHIFT		9
# define DSI_HS_DLT3_PRE_MASK		VC4_MASK(8, 0)
# define DSI_HS_DLT3_PRE_SHIFT		0

#घोषणा DSI1_HS_DLT4		0x60
# define DSI_HS_DLT4_ANLAT_MASK		VC4_MASK(22, 18)
# define DSI_HS_DLT4_ANLAT_SHIFT	18
# define DSI_HS_DLT4_TRAIL_MASK		VC4_MASK(17, 9)
# define DSI_HS_DLT4_TRAIL_SHIFT	9
# define DSI_HS_DLT4_LPX_MASK		VC4_MASK(8, 0)
# define DSI_HS_DLT4_LPX_SHIFT		0

#घोषणा DSI1_HS_DLT5		0x64
# define DSI_HS_DLT5_INIT_MASK		VC4_MASK(23, 0)
# define DSI_HS_DLT5_INIT_SHIFT		0

#घोषणा DSI1_HS_DLT6		0x68
# define DSI_HS_DLT6_TA_GET_MASK	VC4_MASK(31, 24)
# define DSI_HS_DLT6_TA_GET_SHIFT	24
# define DSI_HS_DLT6_TA_SURE_MASK	VC4_MASK(23, 16)
# define DSI_HS_DLT6_TA_SURE_SHIFT	16
# define DSI_HS_DLT6_TA_GO_MASK		VC4_MASK(15, 8)
# define DSI_HS_DLT6_TA_GO_SHIFT	8
# define DSI_HS_DLT6_LP_LPX_MASK	VC4_MASK(7, 0)
# define DSI_HS_DLT6_LP_LPX_SHIFT	0

#घोषणा DSI1_HS_DLT7		0x6c
# define DSI_HS_DLT7_LP_WUP_MASK	VC4_MASK(23, 0)
# define DSI_HS_DLT7_LP_WUP_SHIFT	0

#घोषणा DSI1_PHY_AFEC0		0x70

#घोषणा DSI1_PHY_AFEC1		0x74
# define DSI1_PHY_AFEC1_ACTRL_DLANE3_MASK	VC4_MASK(19, 16)
# define DSI1_PHY_AFEC1_ACTRL_DLANE3_SHIFT	16
# define DSI1_PHY_AFEC1_ACTRL_DLANE2_MASK	VC4_MASK(15, 12)
# define DSI1_PHY_AFEC1_ACTRL_DLANE2_SHIFT	12
# define DSI1_PHY_AFEC1_ACTRL_DLANE1_MASK	VC4_MASK(11, 8)
# define DSI1_PHY_AFEC1_ACTRL_DLANE1_SHIFT	8
# define DSI1_PHY_AFEC1_ACTRL_DLANE0_MASK	VC4_MASK(7, 4)
# define DSI1_PHY_AFEC1_ACTRL_DLANE0_SHIFT	4
# define DSI1_PHY_AFEC1_ACTRL_CLANE_MASK	VC4_MASK(3, 0)
# define DSI1_PHY_AFEC1_ACTRL_CLANE_SHIFT	0

#घोषणा DSI1_TST_SEL		0x78
#घोषणा DSI1_TST_MON		0x7c
#घोषणा DSI1_PHY_TST1		0x80
#घोषणा DSI1_PHY_TST2		0x84
#घोषणा DSI1_PHY_FIFO_STAT	0x88
/* Actually, all रेजिस्टरs in the range that aren't otherwise claimed
 * will वापस the ID.
 */
#घोषणा DSI1_ID			0x8c

काष्ठा vc4_dsi_variant अणु
	/* Whether we're on bcm2835's DSI0 or DSI1. */
	अचिन्हित पूर्णांक port;

	bool broken_axi_workaround;

	स्थिर अक्षर *debugfs_name;
	स्थिर काष्ठा debugfs_reg32 *regs;
	माप_प्रकार nregs;

पूर्ण;

/* General DSI hardware state. */
काष्ठा vc4_dsi अणु
	काष्ठा platक्रमm_device *pdev;

	काष्ठा mipi_dsi_host dsi_host;
	काष्ठा drm_encoder *encoder;
	काष्ठा drm_bridge *bridge;
	काष्ठा list_head bridge_chain;

	व्योम __iomem *regs;

	काष्ठा dma_chan *reg_dma_chan;
	dma_addr_t reg_dma_paddr;
	u32 *reg_dma_mem;
	dma_addr_t reg_paddr;

	स्थिर काष्ठा vc4_dsi_variant *variant;

	/* DSI channel क्रम the panel we're connected to. */
	u32 channel;
	u32 lanes;
	u32 क्रमmat;
	u32 भागider;
	u32 mode_flags;

	/* Input घड़ी from CPRMAN to the digital PHY, क्रम the DSI
	 * escape घड़ी.
	 */
	काष्ठा clk *escape_घड़ी;

	/* Input घड़ी to the analog PHY, used to generate the DSI bit
	 * घड़ी.
	 */
	काष्ठा clk *pll_phy_घड़ी;

	/* HS Clocks generated within the DSI analog PHY. */
	काष्ठा clk_fixed_factor phy_घड़ीs[3];

	काष्ठा clk_hw_onecell_data *clk_onecell;

	/* Pixel घड़ी output to the pixelvalve, generated from the HS
	 * घड़ी.
	 */
	काष्ठा clk *pixel_घड़ी;

	काष्ठा completion xfer_completion;
	पूर्णांक xfer_result;

	काष्ठा debugfs_regset32 regset;
पूर्ण;

#घोषणा host_to_dsi(host) container_of(host, काष्ठा vc4_dsi, dsi_host)

अटल अंतरभूत व्योम
dsi_dma_workaround_ग_लिखो(काष्ठा vc4_dsi *dsi, u32 offset, u32 val)
अणु
	काष्ठा dma_chan *chan = dsi->reg_dma_chan;
	काष्ठा dma_async_tx_descriptor *tx;
	dma_cookie_t cookie;
	पूर्णांक ret;

	/* DSI0 should be able to ग_लिखो normally. */
	अगर (!chan) अणु
		ग_लिखोl(val, dsi->regs + offset);
		वापस;
	पूर्ण

	*dsi->reg_dma_mem = val;

	tx = chan->device->device_prep_dma_स_नकल(chan,
						  dsi->reg_paddr + offset,
						  dsi->reg_dma_paddr,
						  4, 0);
	अगर (!tx) अणु
		DRM_ERROR("Failed to set up DMA register write\n");
		वापस;
	पूर्ण

	cookie = tx->tx_submit(tx);
	ret = dma_submit_error(cookie);
	अगर (ret) अणु
		DRM_ERROR("Failed to submit DMA: %d\n", ret);
		वापस;
	पूर्ण
	ret = dma_sync_रुको(chan, cookie);
	अगर (ret)
		DRM_ERROR("Failed to wait for DMA: %d\n", ret);
पूर्ण

#घोषणा DSI_READ(offset) पढ़ोl(dsi->regs + (offset))
#घोषणा DSI_WRITE(offset, val) dsi_dma_workaround_ग_लिखो(dsi, offset, val)
#घोषणा DSI_PORT_READ(offset) \
	DSI_READ(dsi->variant->port ? DSI1_##offset : DSI0_##offset)
#घोषणा DSI_PORT_WRITE(offset, val) \
	DSI_WRITE(dsi->variant->port ? DSI1_##offset : DSI0_##offset, val)
#घोषणा DSI_PORT_BIT(bit) (dsi->variant->port ? DSI1_##bit : DSI0_##bit)

/* VC4 DSI encoder KMS काष्ठा */
काष्ठा vc4_dsi_encoder अणु
	काष्ठा vc4_encoder base;
	काष्ठा vc4_dsi *dsi;
पूर्ण;

अटल अंतरभूत काष्ठा vc4_dsi_encoder *
to_vc4_dsi_encoder(काष्ठा drm_encoder *encoder)
अणु
	वापस container_of(encoder, काष्ठा vc4_dsi_encoder, base.base);
पूर्ण

अटल स्थिर काष्ठा debugfs_reg32 dsi0_regs[] = अणु
	VC4_REG32(DSI0_CTRL),
	VC4_REG32(DSI0_STAT),
	VC4_REG32(DSI0_HSTX_TO_CNT),
	VC4_REG32(DSI0_LPRX_TO_CNT),
	VC4_REG32(DSI0_TA_TO_CNT),
	VC4_REG32(DSI0_PR_TO_CNT),
	VC4_REG32(DSI0_DISP0_CTRL),
	VC4_REG32(DSI0_DISP1_CTRL),
	VC4_REG32(DSI0_INT_STAT),
	VC4_REG32(DSI0_INT_EN),
	VC4_REG32(DSI0_PHYC),
	VC4_REG32(DSI0_HS_CLT0),
	VC4_REG32(DSI0_HS_CLT1),
	VC4_REG32(DSI0_HS_CLT2),
	VC4_REG32(DSI0_HS_DLT3),
	VC4_REG32(DSI0_HS_DLT4),
	VC4_REG32(DSI0_HS_DLT5),
	VC4_REG32(DSI0_HS_DLT6),
	VC4_REG32(DSI0_HS_DLT7),
	VC4_REG32(DSI0_PHY_AFEC0),
	VC4_REG32(DSI0_PHY_AFEC1),
	VC4_REG32(DSI0_ID),
पूर्ण;

अटल स्थिर काष्ठा debugfs_reg32 dsi1_regs[] = अणु
	VC4_REG32(DSI1_CTRL),
	VC4_REG32(DSI1_STAT),
	VC4_REG32(DSI1_HSTX_TO_CNT),
	VC4_REG32(DSI1_LPRX_TO_CNT),
	VC4_REG32(DSI1_TA_TO_CNT),
	VC4_REG32(DSI1_PR_TO_CNT),
	VC4_REG32(DSI1_DISP0_CTRL),
	VC4_REG32(DSI1_DISP1_CTRL),
	VC4_REG32(DSI1_INT_STAT),
	VC4_REG32(DSI1_INT_EN),
	VC4_REG32(DSI1_PHYC),
	VC4_REG32(DSI1_HS_CLT0),
	VC4_REG32(DSI1_HS_CLT1),
	VC4_REG32(DSI1_HS_CLT2),
	VC4_REG32(DSI1_HS_DLT3),
	VC4_REG32(DSI1_HS_DLT4),
	VC4_REG32(DSI1_HS_DLT5),
	VC4_REG32(DSI1_HS_DLT6),
	VC4_REG32(DSI1_HS_DLT7),
	VC4_REG32(DSI1_PHY_AFEC0),
	VC4_REG32(DSI1_PHY_AFEC1),
	VC4_REG32(DSI1_ID),
पूर्ण;

अटल व्योम vc4_dsi_latch_ulps(काष्ठा vc4_dsi *dsi, bool latch)
अणु
	u32 afec0 = DSI_PORT_READ(PHY_AFEC0);

	अगर (latch)
		afec0 |= DSI_PORT_BIT(PHY_AFEC0_LATCH_ULPS);
	अन्यथा
		afec0 &= ~DSI_PORT_BIT(PHY_AFEC0_LATCH_ULPS);

	DSI_PORT_WRITE(PHY_AFEC0, afec0);
पूर्ण

/* Enters or निकासs Ultra Low Power State. */
अटल व्योम vc4_dsi_ulps(काष्ठा vc4_dsi *dsi, bool ulps)
अणु
	bool non_continuous = dsi->mode_flags & MIPI_DSI_CLOCK_NON_CONTINUOUS;
	u32 phyc_ulps = ((non_continuous ? DSI_PORT_BIT(PHYC_CLANE_ULPS) : 0) |
			 DSI_PHYC_DLANE0_ULPS |
			 (dsi->lanes > 1 ? DSI_PHYC_DLANE1_ULPS : 0) |
			 (dsi->lanes > 2 ? DSI_PHYC_DLANE2_ULPS : 0) |
			 (dsi->lanes > 3 ? DSI_PHYC_DLANE3_ULPS : 0));
	u32 stat_ulps = ((non_continuous ? DSI1_STAT_PHY_CLOCK_ULPS : 0) |
			 DSI1_STAT_PHY_D0_ULPS |
			 (dsi->lanes > 1 ? DSI1_STAT_PHY_D1_ULPS : 0) |
			 (dsi->lanes > 2 ? DSI1_STAT_PHY_D2_ULPS : 0) |
			 (dsi->lanes > 3 ? DSI1_STAT_PHY_D3_ULPS : 0));
	u32 stat_stop = ((non_continuous ? DSI1_STAT_PHY_CLOCK_STOP : 0) |
			 DSI1_STAT_PHY_D0_STOP |
			 (dsi->lanes > 1 ? DSI1_STAT_PHY_D1_STOP : 0) |
			 (dsi->lanes > 2 ? DSI1_STAT_PHY_D2_STOP : 0) |
			 (dsi->lanes > 3 ? DSI1_STAT_PHY_D3_STOP : 0));
	पूर्णांक ret;
	bool ulps_currently_enabled = (DSI_PORT_READ(PHY_AFEC0) &
				       DSI_PORT_BIT(PHY_AFEC0_LATCH_ULPS));

	अगर (ulps == ulps_currently_enabled)
		वापस;

	DSI_PORT_WRITE(STAT, stat_ulps);
	DSI_PORT_WRITE(PHYC, DSI_PORT_READ(PHYC) | phyc_ulps);
	ret = रुको_क्रम((DSI_PORT_READ(STAT) & stat_ulps) == stat_ulps, 200);
	अगर (ret) अणु
		dev_warn(&dsi->pdev->dev,
			 "Timeout waiting for DSI ULPS entry: STAT 0x%08x",
			 DSI_PORT_READ(STAT));
		DSI_PORT_WRITE(PHYC, DSI_PORT_READ(PHYC) & ~phyc_ulps);
		vc4_dsi_latch_ulps(dsi, false);
		वापस;
	पूर्ण

	/* The DSI module can't be disabled जबतक the module is
	 * generating ULPS state.  So, to be able to disable the
	 * module, we have the AFE latch the ULPS state and जारी
	 * on to having the module enter STOP.
	 */
	vc4_dsi_latch_ulps(dsi, ulps);

	DSI_PORT_WRITE(STAT, stat_stop);
	DSI_PORT_WRITE(PHYC, DSI_PORT_READ(PHYC) & ~phyc_ulps);
	ret = रुको_क्रम((DSI_PORT_READ(STAT) & stat_stop) == stat_stop, 200);
	अगर (ret) अणु
		dev_warn(&dsi->pdev->dev,
			 "Timeout waiting for DSI STOP entry: STAT 0x%08x",
			 DSI_PORT_READ(STAT));
		DSI_PORT_WRITE(PHYC, DSI_PORT_READ(PHYC) & ~phyc_ulps);
		वापस;
	पूर्ण
पूर्ण

अटल u32
dsi_hs_timing(u32 ui_ns, u32 ns, u32 ui)
अणु
	/* The HS timings have to be rounded up to a multiple of 8
	 * because we're using the byte घड़ी.
	 */
	वापस roundup(ui + DIV_ROUND_UP(ns, ui_ns), 8);
पूर्ण

/* ESC always runs at 100Mhz. */
#घोषणा ESC_TIME_NS 10

अटल u32
dsi_esc_timing(u32 ns)
अणु
	वापस DIV_ROUND_UP(ns, ESC_TIME_NS);
पूर्ण

अटल व्योम vc4_dsi_encoder_disable(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा vc4_dsi_encoder *vc4_encoder = to_vc4_dsi_encoder(encoder);
	काष्ठा vc4_dsi *dsi = vc4_encoder->dsi;
	काष्ठा device *dev = &dsi->pdev->dev;
	काष्ठा drm_bridge *iter;

	list_क्रम_each_entry_reverse(iter, &dsi->bridge_chain, chain_node) अणु
		अगर (iter->funcs->disable)
			iter->funcs->disable(iter);
	पूर्ण

	vc4_dsi_ulps(dsi, true);

	list_क्रम_each_entry_from(iter, &dsi->bridge_chain, chain_node) अणु
		अगर (iter->funcs->post_disable)
			iter->funcs->post_disable(iter);
	पूर्ण

	clk_disable_unprepare(dsi->pll_phy_घड़ी);
	clk_disable_unprepare(dsi->escape_घड़ी);
	clk_disable_unprepare(dsi->pixel_घड़ी);

	pm_runसमय_put(dev);
पूर्ण

/* Extends the mode's blank intervals to handle BCM2835's पूर्णांकeger-only
 * DSI PLL भागider.
 *
 * On 2835, PLLD is set to 2Ghz, and may not be changed by the display
 * driver since most peripherals are hanging off of the PLLD_PER
 * भागider.  PLLD_DSI1, which drives our DSI bit घड़ी (and thereक्रमe
 * the pixel घड़ी), only has an पूर्णांकeger भागider off of DSI.
 *
 * To get our panel mode to refresh at the expected 60Hz, we need to
 * extend the horizontal blank समय.  This means we drive a
 * higher-than-expected घड़ी rate to the panel, but that's what the
 * firmware करोes too.
 */
अटल bool vc4_dsi_encoder_mode_fixup(काष्ठा drm_encoder *encoder,
				       स्थिर काष्ठा drm_display_mode *mode,
				       काष्ठा drm_display_mode *adjusted_mode)
अणु
	काष्ठा vc4_dsi_encoder *vc4_encoder = to_vc4_dsi_encoder(encoder);
	काष्ठा vc4_dsi *dsi = vc4_encoder->dsi;
	काष्ठा clk *phy_parent = clk_get_parent(dsi->pll_phy_घड़ी);
	अचिन्हित दीर्घ parent_rate = clk_get_rate(phy_parent);
	अचिन्हित दीर्घ pixel_घड़ी_hz = mode->घड़ी * 1000;
	अचिन्हित दीर्घ pll_घड़ी = pixel_घड़ी_hz * dsi->भागider;
	पूर्णांक भागider;

	/* Find what भागider माला_लो us a faster घड़ी than the requested
	 * pixel घड़ी.
	 */
	क्रम (भागider = 1; भागider < 8; भागider++) अणु
		अगर (parent_rate / भागider < pll_घड़ी) अणु
			भागider--;
			अवरोध;
		पूर्ण
	पूर्ण

	/* Now that we've picked a PLL भागider, calculate back to its
	 * pixel घड़ी.
	 */
	pll_घड़ी = parent_rate / भागider;
	pixel_घड़ी_hz = pll_घड़ी / dsi->भागider;

	adjusted_mode->घड़ी = pixel_घड़ी_hz / 1000;

	/* Given the new pixel घड़ी, adjust HFP to keep vrefresh the same. */
	adjusted_mode->htotal = adjusted_mode->घड़ी * mode->htotal /
				mode->घड़ी;
	adjusted_mode->hsync_end += adjusted_mode->htotal - mode->htotal;
	adjusted_mode->hsync_start += adjusted_mode->htotal - mode->htotal;

	वापस true;
पूर्ण

अटल व्योम vc4_dsi_encoder_enable(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा drm_display_mode *mode = &encoder->crtc->state->adjusted_mode;
	काष्ठा vc4_dsi_encoder *vc4_encoder = to_vc4_dsi_encoder(encoder);
	काष्ठा vc4_dsi *dsi = vc4_encoder->dsi;
	काष्ठा device *dev = &dsi->pdev->dev;
	bool debug_dump_regs = false;
	काष्ठा drm_bridge *iter;
	अचिन्हित दीर्घ hs_घड़ी;
	u32 ui_ns;
	/* Minimum LP state duration in escape घड़ी cycles. */
	u32 lpx = dsi_esc_timing(60);
	अचिन्हित दीर्घ pixel_घड़ी_hz = mode->घड़ी * 1000;
	अचिन्हित दीर्घ dsip_घड़ी;
	अचिन्हित दीर्घ phy_घड़ी;
	पूर्णांक ret;

	ret = pm_runसमय_get_sync(dev);
	अगर (ret) अणु
		DRM_ERROR("Failed to runtime PM enable on DSI%d\n", dsi->variant->port);
		वापस;
	पूर्ण

	अगर (debug_dump_regs) अणु
		काष्ठा drm_prपूर्णांकer p = drm_info_prपूर्णांकer(&dsi->pdev->dev);
		dev_info(&dsi->pdev->dev, "DSI regs before:\n");
		drm_prपूर्णांक_regset32(&p, &dsi->regset);
	पूर्ण

	/* Round up the clk_set_rate() request slightly, since
	 * PLLD_DSI1 is an पूर्णांकeger भागider and its rate selection will
	 * never round up.
	 */
	phy_घड़ी = (pixel_घड़ी_hz + 1000) * dsi->भागider;
	ret = clk_set_rate(dsi->pll_phy_घड़ी, phy_घड़ी);
	अगर (ret) अणु
		dev_err(&dsi->pdev->dev,
			"Failed to set phy clock to %ld: %d\n", phy_घड़ी, ret);
	पूर्ण

	/* Reset the DSI and all its fअगरos. */
	DSI_PORT_WRITE(CTRL,
		       DSI_CTRL_SOFT_RESET_CFG |
		       DSI_PORT_BIT(CTRL_RESET_FIFOS));

	DSI_PORT_WRITE(CTRL,
		       DSI_CTRL_HSDT_EOT_DISABLE |
		       DSI_CTRL_RX_LPDT_EOT_DISABLE);

	/* Clear all stat bits so we see what has happened during enable. */
	DSI_PORT_WRITE(STAT, DSI_PORT_READ(STAT));

	/* Set AFE CTR00/CTR1 to release घातerकरोwn of analog. */
	अगर (dsi->variant->port == 0) अणु
		u32 afec0 = (VC4_SET_FIELD(7, DSI_PHY_AFEC0_PTATADJ) |
			     VC4_SET_FIELD(7, DSI_PHY_AFEC0_CTATADJ));

		अगर (dsi->lanes < 2)
			afec0 |= DSI0_PHY_AFEC0_PD_DLANE1;

		अगर (!(dsi->mode_flags & MIPI_DSI_MODE_VIDEO))
			afec0 |= DSI0_PHY_AFEC0_RESET;

		DSI_PORT_WRITE(PHY_AFEC0, afec0);

		DSI_PORT_WRITE(PHY_AFEC1,
			       VC4_SET_FIELD(6,  DSI0_PHY_AFEC1_IDR_DLANE1) |
			       VC4_SET_FIELD(6,  DSI0_PHY_AFEC1_IDR_DLANE0) |
			       VC4_SET_FIELD(6,  DSI0_PHY_AFEC1_IDR_CLANE));
	पूर्ण अन्यथा अणु
		u32 afec0 = (VC4_SET_FIELD(7, DSI_PHY_AFEC0_PTATADJ) |
			     VC4_SET_FIELD(7, DSI_PHY_AFEC0_CTATADJ) |
			     VC4_SET_FIELD(6, DSI1_PHY_AFEC0_IDR_CLANE) |
			     VC4_SET_FIELD(6, DSI1_PHY_AFEC0_IDR_DLANE0) |
			     VC4_SET_FIELD(6, DSI1_PHY_AFEC0_IDR_DLANE1) |
			     VC4_SET_FIELD(6, DSI1_PHY_AFEC0_IDR_DLANE2) |
			     VC4_SET_FIELD(6, DSI1_PHY_AFEC0_IDR_DLANE3));

		अगर (dsi->lanes < 4)
			afec0 |= DSI1_PHY_AFEC0_PD_DLANE3;
		अगर (dsi->lanes < 3)
			afec0 |= DSI1_PHY_AFEC0_PD_DLANE2;
		अगर (dsi->lanes < 2)
			afec0 |= DSI1_PHY_AFEC0_PD_DLANE1;

		afec0 |= DSI1_PHY_AFEC0_RESET;

		DSI_PORT_WRITE(PHY_AFEC0, afec0);

		DSI_PORT_WRITE(PHY_AFEC1, 0);

		/* AFEC reset hold समय */
		mdelay(1);
	पूर्ण

	ret = clk_prepare_enable(dsi->escape_घड़ी);
	अगर (ret) अणु
		DRM_ERROR("Failed to turn on DSI escape clock: %d\n", ret);
		वापस;
	पूर्ण

	ret = clk_prepare_enable(dsi->pll_phy_घड़ी);
	अगर (ret) अणु
		DRM_ERROR("Failed to turn on DSI PLL: %d\n", ret);
		वापस;
	पूर्ण

	hs_घड़ी = clk_get_rate(dsi->pll_phy_घड़ी);

	/* Yes, we set the DSI0P/DSI1P pixel घड़ी to the byte rate,
	 * not the pixel घड़ी rate.  DSIxP take from the APHY's byte,
	 * DDR2, or DDR4 घड़ी (we use byte) and feed पूर्णांकo the PV at
	 * that rate.  Separately, a value derived from PIX_CLK_DIV
	 * and HS_CLKC is fed पूर्णांकo the PV to भागide करोwn to the actual
	 * pixel घड़ी क्रम pushing pixels पूर्णांकo DSI.
	 */
	dsip_घड़ी = phy_घड़ी / 8;
	ret = clk_set_rate(dsi->pixel_घड़ी, dsip_घड़ी);
	अगर (ret) अणु
		dev_err(dev, "Failed to set pixel clock to %ldHz: %d\n",
			dsip_घड़ी, ret);
	पूर्ण

	ret = clk_prepare_enable(dsi->pixel_घड़ी);
	अगर (ret) अणु
		DRM_ERROR("Failed to turn on DSI pixel clock: %d\n", ret);
		वापस;
	पूर्ण

	/* How many ns one DSI unit पूर्णांकerval is.  Note that the घड़ी
	 * is DDR, so there's an extra भागide by 2.
	 */
	ui_ns = DIV_ROUND_UP(500000000, hs_घड़ी);

	DSI_PORT_WRITE(HS_CLT0,
		       VC4_SET_FIELD(dsi_hs_timing(ui_ns, 262, 0),
				     DSI_HS_CLT0_CZERO) |
		       VC4_SET_FIELD(dsi_hs_timing(ui_ns, 0, 8),
				     DSI_HS_CLT0_CPRE) |
		       VC4_SET_FIELD(dsi_hs_timing(ui_ns, 38, 0),
				     DSI_HS_CLT0_CPREP));

	DSI_PORT_WRITE(HS_CLT1,
		       VC4_SET_FIELD(dsi_hs_timing(ui_ns, 60, 0),
				     DSI_HS_CLT1_CTRAIL) |
		       VC4_SET_FIELD(dsi_hs_timing(ui_ns, 60, 52),
				     DSI_HS_CLT1_CPOST));

	DSI_PORT_WRITE(HS_CLT2,
		       VC4_SET_FIELD(dsi_hs_timing(ui_ns, 1000000, 0),
				     DSI_HS_CLT2_WUP));

	DSI_PORT_WRITE(HS_DLT3,
		       VC4_SET_FIELD(dsi_hs_timing(ui_ns, 100, 0),
				     DSI_HS_DLT3_EXIT) |
		       VC4_SET_FIELD(dsi_hs_timing(ui_ns, 105, 6),
				     DSI_HS_DLT3_ZERO) |
		       VC4_SET_FIELD(dsi_hs_timing(ui_ns, 40, 4),
				     DSI_HS_DLT3_PRE));

	DSI_PORT_WRITE(HS_DLT4,
		       VC4_SET_FIELD(dsi_hs_timing(ui_ns, lpx * ESC_TIME_NS, 0),
				     DSI_HS_DLT4_LPX) |
		       VC4_SET_FIELD(max(dsi_hs_timing(ui_ns, 0, 8),
					 dsi_hs_timing(ui_ns, 60, 4)),
				     DSI_HS_DLT4_TRAIL) |
		       VC4_SET_FIELD(0, DSI_HS_DLT4_ANLAT));

	/* T_INIT is how दीर्घ STOP is driven after घातer-up to
	 * indicate to the slave (also coming out of घातer-up) that
	 * master init is complete, and should be greater than the
	 * maximum of two value: T_INIT,MASTER and T_INIT,SLAVE.  The
	 * D-PHY spec gives a minimum 100us क्रम T_INIT,MASTER and
	 * T_INIT,SLAVE, जबतक allowing protocols on top of it to give
	 * greater minimums.  The vc4 firmware uses an extremely
	 * conservative 5ms, and we मुख्यtain that here.
	 */
	DSI_PORT_WRITE(HS_DLT5, VC4_SET_FIELD(dsi_hs_timing(ui_ns,
							    5 * 1000 * 1000, 0),
					      DSI_HS_DLT5_INIT));

	DSI_PORT_WRITE(HS_DLT6,
		       VC4_SET_FIELD(lpx * 5, DSI_HS_DLT6_TA_GET) |
		       VC4_SET_FIELD(lpx, DSI_HS_DLT6_TA_SURE) |
		       VC4_SET_FIELD(lpx * 4, DSI_HS_DLT6_TA_GO) |
		       VC4_SET_FIELD(lpx, DSI_HS_DLT6_LP_LPX));

	DSI_PORT_WRITE(HS_DLT7,
		       VC4_SET_FIELD(dsi_esc_timing(1000000),
				     DSI_HS_DLT7_LP_WUP));

	DSI_PORT_WRITE(PHYC,
		       DSI_PHYC_DLANE0_ENABLE |
		       (dsi->lanes >= 2 ? DSI_PHYC_DLANE1_ENABLE : 0) |
		       (dsi->lanes >= 3 ? DSI_PHYC_DLANE2_ENABLE : 0) |
		       (dsi->lanes >= 4 ? DSI_PHYC_DLANE3_ENABLE : 0) |
		       DSI_PORT_BIT(PHYC_CLANE_ENABLE) |
		       ((dsi->mode_flags & MIPI_DSI_CLOCK_NON_CONTINUOUS) ?
			0 : DSI_PORT_BIT(PHYC_HS_CLK_CONTINUOUS)) |
		       (dsi->variant->port == 0 ?
			VC4_SET_FIELD(lpx - 1, DSI0_PHYC_ESC_CLK_LPDT) :
			VC4_SET_FIELD(lpx - 1, DSI1_PHYC_ESC_CLK_LPDT)));

	DSI_PORT_WRITE(CTRL,
		       DSI_PORT_READ(CTRL) |
		       DSI_CTRL_CAL_BYTE);

	/* HS समयout in HS घड़ी cycles: disabled. */
	DSI_PORT_WRITE(HSTX_TO_CNT, 0);
	/* LP receive समयout in HS घड़ीs. */
	DSI_PORT_WRITE(LPRX_TO_CNT, 0xffffff);
	/* Bus turnaround समयout */
	DSI_PORT_WRITE(TA_TO_CNT, 100000);
	/* Display reset sequence समयout */
	DSI_PORT_WRITE(PR_TO_CNT, 100000);

	/* Set up DISP1 क्रम transferring दीर्घ command payloads through
	 * the pixfअगरo.
	 */
	DSI_PORT_WRITE(DISP1_CTRL,
		       VC4_SET_FIELD(DSI_DISP1_PFORMAT_32BIT_LE,
				     DSI_DISP1_PFORMAT) |
		       DSI_DISP1_ENABLE);

	/* Ungate the block. */
	अगर (dsi->variant->port == 0)
		DSI_PORT_WRITE(CTRL, DSI_PORT_READ(CTRL) | DSI0_CTRL_CTRL0);
	अन्यथा
		DSI_PORT_WRITE(CTRL, DSI_PORT_READ(CTRL) | DSI1_CTRL_EN);

	/* Bring AFE out of reset. */
	अगर (dsi->variant->port == 0) अणु
	पूर्ण अन्यथा अणु
		DSI_PORT_WRITE(PHY_AFEC0,
			       DSI_PORT_READ(PHY_AFEC0) &
			       ~DSI1_PHY_AFEC0_RESET);
	पूर्ण

	vc4_dsi_ulps(dsi, false);

	list_क्रम_each_entry_reverse(iter, &dsi->bridge_chain, chain_node) अणु
		अगर (iter->funcs->pre_enable)
			iter->funcs->pre_enable(iter);
	पूर्ण

	अगर (dsi->mode_flags & MIPI_DSI_MODE_VIDEO) अणु
		DSI_PORT_WRITE(DISP0_CTRL,
			       VC4_SET_FIELD(dsi->भागider,
					     DSI_DISP0_PIX_CLK_DIV) |
			       VC4_SET_FIELD(dsi->क्रमmat, DSI_DISP0_PFORMAT) |
			       VC4_SET_FIELD(DSI_DISP0_LP_STOP_PERFRAME,
					     DSI_DISP0_LP_STOP_CTRL) |
			       DSI_DISP0_ST_END |
			       DSI_DISP0_ENABLE);
	पूर्ण अन्यथा अणु
		DSI_PORT_WRITE(DISP0_CTRL,
			       DSI_DISP0_COMMAND_MODE |
			       DSI_DISP0_ENABLE);
	पूर्ण

	list_क्रम_each_entry(iter, &dsi->bridge_chain, chain_node) अणु
		अगर (iter->funcs->enable)
			iter->funcs->enable(iter);
	पूर्ण

	अगर (debug_dump_regs) अणु
		काष्ठा drm_prपूर्णांकer p = drm_info_prपूर्णांकer(&dsi->pdev->dev);
		dev_info(&dsi->pdev->dev, "DSI regs after:\n");
		drm_prपूर्णांक_regset32(&p, &dsi->regset);
	पूर्ण
पूर्ण

अटल sमाप_प्रकार vc4_dsi_host_transfer(काष्ठा mipi_dsi_host *host,
				     स्थिर काष्ठा mipi_dsi_msg *msg)
अणु
	काष्ठा vc4_dsi *dsi = host_to_dsi(host);
	काष्ठा mipi_dsi_packet packet;
	u32 pkth = 0, pktc = 0;
	पूर्णांक i, ret;
	bool is_दीर्घ = mipi_dsi_packet_क्रमmat_is_दीर्घ(msg->type);
	u32 cmd_fअगरo_len = 0, pix_fअगरo_len = 0;

	mipi_dsi_create_packet(&packet, msg);

	pkth |= VC4_SET_FIELD(packet.header[0], DSI_TXPKT1H_BC_DT);
	pkth |= VC4_SET_FIELD(packet.header[1] |
			      (packet.header[2] << 8),
			      DSI_TXPKT1H_BC_PARAM);
	अगर (is_दीर्घ) अणु
		/* Divide data across the various FIFOs we have available.
		 * The command FIFO takes byte-oriented data, but is of
		 * limited size. The pixel FIFO (never actually used क्रम
		 * pixel data in reality) is word oriented, and substantially
		 * larger. So, we use the pixel FIFO क्रम most of the data,
		 * sending the residual bytes in the command FIFO at the start.
		 *
		 * With this arrangement, the command FIFO will never get full.
		 */
		अगर (packet.payload_length <= 16) अणु
			cmd_fअगरo_len = packet.payload_length;
			pix_fअगरo_len = 0;
		पूर्ण अन्यथा अणु
			cmd_fअगरo_len = (packet.payload_length %
					DSI_PIX_FIFO_WIDTH);
			pix_fअगरo_len = ((packet.payload_length - cmd_fअगरo_len) /
					DSI_PIX_FIFO_WIDTH);
		पूर्ण

		WARN_ON_ONCE(pix_fअगरo_len >= DSI_PIX_FIFO_DEPTH);

		pkth |= VC4_SET_FIELD(cmd_fअगरo_len, DSI_TXPKT1H_BC_CMDFIFO);
	पूर्ण

	अगर (msg->rx_len) अणु
		pktc |= VC4_SET_FIELD(DSI_TXPKT1C_CMD_CTRL_RX,
				      DSI_TXPKT1C_CMD_CTRL);
	पूर्ण अन्यथा अणु
		pktc |= VC4_SET_FIELD(DSI_TXPKT1C_CMD_CTRL_TX,
				      DSI_TXPKT1C_CMD_CTRL);
	पूर्ण

	क्रम (i = 0; i < cmd_fअगरo_len; i++)
		DSI_PORT_WRITE(TXPKT_CMD_FIFO, packet.payload[i]);
	क्रम (i = 0; i < pix_fअगरo_len; i++) अणु
		स्थिर u8 *pix = packet.payload + cmd_fअगरo_len + i * 4;

		DSI_PORT_WRITE(TXPKT_PIX_FIFO,
			       pix[0] |
			       pix[1] << 8 |
			       pix[2] << 16 |
			       pix[3] << 24);
	पूर्ण

	अगर (msg->flags & MIPI_DSI_MSG_USE_LPM)
		pktc |= DSI_TXPKT1C_CMD_MODE_LP;
	अगर (is_दीर्घ)
		pktc |= DSI_TXPKT1C_CMD_TYPE_LONG;

	/* Send one copy of the packet.  Larger repeats are used क्रम pixel
	 * data in command mode.
	 */
	pktc |= VC4_SET_FIELD(1, DSI_TXPKT1C_CMD_REPEAT);

	pktc |= DSI_TXPKT1C_CMD_EN;
	अगर (pix_fअगरo_len) अणु
		pktc |= VC4_SET_FIELD(DSI_TXPKT1C_DISPLAY_NO_SECONDARY,
				      DSI_TXPKT1C_DISPLAY_NO);
	पूर्ण अन्यथा अणु
		pktc |= VC4_SET_FIELD(DSI_TXPKT1C_DISPLAY_NO_SHORT,
				      DSI_TXPKT1C_DISPLAY_NO);
	पूर्ण

	/* Enable the appropriate पूर्णांकerrupt क्रम the transfer completion. */
	dsi->xfer_result = 0;
	reinit_completion(&dsi->xfer_completion);
	DSI_PORT_WRITE(INT_STAT, DSI1_INT_TXPKT1_DONE | DSI1_INT_PHY_सूची_RTF);
	अगर (msg->rx_len) अणु
		DSI_PORT_WRITE(INT_EN, (DSI1_INTERRUPTS_ALWAYS_ENABLED |
					DSI1_INT_PHY_सूची_RTF));
	पूर्ण अन्यथा अणु
		DSI_PORT_WRITE(INT_EN, (DSI1_INTERRUPTS_ALWAYS_ENABLED |
					DSI1_INT_TXPKT1_DONE));
	पूर्ण

	/* Send the packet. */
	DSI_PORT_WRITE(TXPKT1H, pkth);
	DSI_PORT_WRITE(TXPKT1C, pktc);

	अगर (!रुको_क्रम_completion_समयout(&dsi->xfer_completion,
					 msecs_to_jअगरfies(1000))) अणु
		dev_err(&dsi->pdev->dev, "transfer interrupt wait timeout");
		dev_err(&dsi->pdev->dev, "instat: 0x%08x\n",
			DSI_PORT_READ(INT_STAT));
		ret = -ETIMEDOUT;
	पूर्ण अन्यथा अणु
		ret = dsi->xfer_result;
	पूर्ण

	DSI_PORT_WRITE(INT_EN, DSI1_INTERRUPTS_ALWAYS_ENABLED);

	अगर (ret)
		जाओ reset_fअगरo_and_वापस;

	अगर (ret == 0 && msg->rx_len) अणु
		u32 rxpkt1h = DSI_PORT_READ(RXPKT1H);
		u8 *msg_rx = msg->rx_buf;

		अगर (rxpkt1h & DSI_RXPKT1H_PKT_TYPE_LONG) अणु
			u32 rxlen = VC4_GET_FIELD(rxpkt1h,
						  DSI_RXPKT1H_BC_PARAM);

			अगर (rxlen != msg->rx_len) अणु
				DRM_ERROR("DSI returned %db, expecting %db\n",
					  rxlen, (पूर्णांक)msg->rx_len);
				ret = -ENXIO;
				जाओ reset_fअगरo_and_वापस;
			पूर्ण

			क्रम (i = 0; i < msg->rx_len; i++)
				msg_rx[i] = DSI_READ(DSI1_RXPKT_FIFO);
		पूर्ण अन्यथा अणु
			/* FINISHME: Handle AWER */

			msg_rx[0] = VC4_GET_FIELD(rxpkt1h,
						  DSI_RXPKT1H_SHORT_0);
			अगर (msg->rx_len > 1) अणु
				msg_rx[1] = VC4_GET_FIELD(rxpkt1h,
							  DSI_RXPKT1H_SHORT_1);
			पूर्ण
		पूर्ण
	पूर्ण

	वापस ret;

reset_fअगरo_and_वापस:
	DRM_ERROR("DSI transfer failed, resetting: %d\n", ret);

	DSI_PORT_WRITE(TXPKT1C, DSI_PORT_READ(TXPKT1C) & ~DSI_TXPKT1C_CMD_EN);
	udelay(1);
	DSI_PORT_WRITE(CTRL,
		       DSI_PORT_READ(CTRL) |
		       DSI_PORT_BIT(CTRL_RESET_FIFOS));

	DSI_PORT_WRITE(TXPKT1C, 0);
	DSI_PORT_WRITE(INT_EN, DSI1_INTERRUPTS_ALWAYS_ENABLED);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा component_ops vc4_dsi_ops;
अटल पूर्णांक vc4_dsi_host_attach(काष्ठा mipi_dsi_host *host,
			       काष्ठा mipi_dsi_device *device)
अणु
	काष्ठा vc4_dsi *dsi = host_to_dsi(host);
	पूर्णांक ret;

	dsi->lanes = device->lanes;
	dsi->channel = device->channel;
	dsi->mode_flags = device->mode_flags;

	चयन (device->क्रमmat) अणु
	हाल MIPI_DSI_FMT_RGB888:
		dsi->क्रमmat = DSI_PFORMAT_RGB888;
		dsi->भागider = 24 / dsi->lanes;
		अवरोध;
	हाल MIPI_DSI_FMT_RGB666:
		dsi->क्रमmat = DSI_PFORMAT_RGB666;
		dsi->भागider = 24 / dsi->lanes;
		अवरोध;
	हाल MIPI_DSI_FMT_RGB666_PACKED:
		dsi->क्रमmat = DSI_PFORMAT_RGB666_PACKED;
		dsi->भागider = 18 / dsi->lanes;
		अवरोध;
	हाल MIPI_DSI_FMT_RGB565:
		dsi->क्रमmat = DSI_PFORMAT_RGB565;
		dsi->भागider = 16 / dsi->lanes;
		अवरोध;
	शेष:
		dev_err(&dsi->pdev->dev, "Unknown DSI format: %d.\n",
			dsi->क्रमmat);
		वापस 0;
	पूर्ण

	अगर (!(dsi->mode_flags & MIPI_DSI_MODE_VIDEO)) अणु
		dev_err(&dsi->pdev->dev,
			"Only VIDEO mode panels supported currently.\n");
		वापस 0;
	पूर्ण

	ret = component_add(&dsi->pdev->dev, &vc4_dsi_ops);
	अगर (ret) अणु
		mipi_dsi_host_unरेजिस्टर(&dsi->dsi_host);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vc4_dsi_host_detach(काष्ठा mipi_dsi_host *host,
			       काष्ठा mipi_dsi_device *device)
अणु
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा mipi_dsi_host_ops vc4_dsi_host_ops = अणु
	.attach = vc4_dsi_host_attach,
	.detach = vc4_dsi_host_detach,
	.transfer = vc4_dsi_host_transfer,
पूर्ण;

अटल स्थिर काष्ठा drm_encoder_helper_funcs vc4_dsi_encoder_helper_funcs = अणु
	.disable = vc4_dsi_encoder_disable,
	.enable = vc4_dsi_encoder_enable,
	.mode_fixup = vc4_dsi_encoder_mode_fixup,
पूर्ण;

अटल स्थिर काष्ठा vc4_dsi_variant bcm2711_dsi1_variant = अणु
	.port			= 1,
	.debugfs_name		= "dsi1_regs",
	.regs			= dsi1_regs,
	.nregs			= ARRAY_SIZE(dsi1_regs),
पूर्ण;

अटल स्थिर काष्ठा vc4_dsi_variant bcm2835_dsi0_variant = अणु
	.port			= 0,
	.debugfs_name		= "dsi0_regs",
	.regs			= dsi0_regs,
	.nregs			= ARRAY_SIZE(dsi0_regs),
पूर्ण;

अटल स्थिर काष्ठा vc4_dsi_variant bcm2835_dsi1_variant = अणु
	.port			= 1,
	.broken_axi_workaround	= true,
	.debugfs_name		= "dsi1_regs",
	.regs			= dsi1_regs,
	.nregs			= ARRAY_SIZE(dsi1_regs),
पूर्ण;

अटल स्थिर काष्ठा of_device_id vc4_dsi_dt_match[] = अणु
	अणु .compatible = "brcm,bcm2711-dsi1", &bcm2711_dsi1_variant पूर्ण,
	अणु .compatible = "brcm,bcm2835-dsi0", &bcm2835_dsi0_variant पूर्ण,
	अणु .compatible = "brcm,bcm2835-dsi1", &bcm2835_dsi1_variant पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल व्योम dsi_handle_error(काष्ठा vc4_dsi *dsi,
			     irqवापस_t *ret, u32 stat, u32 bit,
			     स्थिर अक्षर *type)
अणु
	अगर (!(stat & bit))
		वापस;

	DRM_ERROR("DSI%d: %s error\n", dsi->variant->port, type);
	*ret = IRQ_HANDLED;
पूर्ण

/*
 * Initial handler क्रम port 1 where we need the reg_dma workaround.
 * The रेजिस्टर DMA ग_लिखोs sleep, so we can't करो it in the top half.
 * Instead we use IRQF_ONESHOT so that the IRQ माला_लो disabled in the
 * parent पूर्णांकerrupt contrller until our पूर्णांकerrupt thपढ़ो is करोne.
 */
अटल irqवापस_t vc4_dsi_irq_defer_to_thपढ़ो_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा vc4_dsi *dsi = data;
	u32 stat = DSI_PORT_READ(INT_STAT);

	अगर (!stat)
		वापस IRQ_NONE;

	वापस IRQ_WAKE_THREAD;
पूर्ण

/*
 * Normal IRQ handler क्रम port 0, or the thपढ़ोed IRQ handler क्रम port
 * 1 where we need the reg_dma workaround.
 */
अटल irqवापस_t vc4_dsi_irq_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा vc4_dsi *dsi = data;
	u32 stat = DSI_PORT_READ(INT_STAT);
	irqवापस_t ret = IRQ_NONE;

	DSI_PORT_WRITE(INT_STAT, stat);

	dsi_handle_error(dsi, &ret, stat,
			 DSI1_INT_ERR_SYNC_ESC, "LPDT sync");
	dsi_handle_error(dsi, &ret, stat,
			 DSI1_INT_ERR_CONTROL, "data lane 0 sequence");
	dsi_handle_error(dsi, &ret, stat,
			 DSI1_INT_ERR_CONT_LP0, "LP0 contention");
	dsi_handle_error(dsi, &ret, stat,
			 DSI1_INT_ERR_CONT_LP1, "LP1 contention");
	dsi_handle_error(dsi, &ret, stat,
			 DSI1_INT_HSTX_TO, "HSTX timeout");
	dsi_handle_error(dsi, &ret, stat,
			 DSI1_INT_LPRX_TO, "LPRX timeout");
	dsi_handle_error(dsi, &ret, stat,
			 DSI1_INT_TA_TO, "turnaround timeout");
	dsi_handle_error(dsi, &ret, stat,
			 DSI1_INT_PR_TO, "peripheral reset timeout");

	अगर (stat & (DSI1_INT_TXPKT1_DONE | DSI1_INT_PHY_सूची_RTF)) अणु
		complete(&dsi->xfer_completion);
		ret = IRQ_HANDLED;
	पूर्ण अन्यथा अगर (stat & DSI1_INT_HSTX_TO) अणु
		complete(&dsi->xfer_completion);
		dsi->xfer_result = -ETIMEDOUT;
		ret = IRQ_HANDLED;
	पूर्ण

	वापस ret;
पूर्ण

/**
 * vc4_dsi_init_phy_घड़ीs - Exposes घड़ीs generated by the analog
 * PHY that are consumed by CPRMAN (clk-bcm2835.c).
 * @dsi: DSI encoder
 */
अटल पूर्णांक
vc4_dsi_init_phy_घड़ीs(काष्ठा vc4_dsi *dsi)
अणु
	काष्ठा device *dev = &dsi->pdev->dev;
	स्थिर अक्षर *parent_name = __clk_get_name(dsi->pll_phy_घड़ी);
	अटल स्थिर काष्ठा अणु
		स्थिर अक्षर *name;
		पूर्णांक भाग;
	पूर्ण phy_घड़ीs[] = अणु
		अणु "byte", 8 पूर्ण,
		अणु "ddr2", 4 पूर्ण,
		अणु "ddr", 2 पूर्ण,
	पूर्ण;
	पूर्णांक i;

	dsi->clk_onecell = devm_kzalloc(dev,
					माप(*dsi->clk_onecell) +
					ARRAY_SIZE(phy_घड़ीs) *
					माप(काष्ठा clk_hw *),
					GFP_KERNEL);
	अगर (!dsi->clk_onecell)
		वापस -ENOMEM;
	dsi->clk_onecell->num = ARRAY_SIZE(phy_घड़ीs);

	क्रम (i = 0; i < ARRAY_SIZE(phy_घड़ीs); i++) अणु
		काष्ठा clk_fixed_factor *fix = &dsi->phy_घड़ीs[i];
		काष्ठा clk_init_data init;
		अक्षर clk_name[16];
		पूर्णांक ret;

		snम_लिखो(clk_name, माप(clk_name),
			 "dsi%u_%s", dsi->variant->port, phy_घड़ीs[i].name);

		/* We just use core fixed factor घड़ी ops क्रम the PHY
		 * घड़ीs.  The घड़ीs are actually gated by the
		 * PHY_AFEC0_DDRCLK_EN bits, which we should be
		 * setting अगर we use the DDR/DDR2 घड़ीs.  However,
		 * vc4_dsi_encoder_enable() is setting up both AFEC0,
		 * setting both our parent DSI PLL's rate and this
		 * घड़ी's rate, so it knows अगर DDR/DDR2 are going to
		 * be used and could enable the gates itself.
		 */
		fix->mult = 1;
		fix->भाग = phy_घड़ीs[i].भाग;
		fix->hw.init = &init;

		स_रखो(&init, 0, माप(init));
		init.parent_names = &parent_name;
		init.num_parents = 1;
		init.name = clk_name;
		init.ops = &clk_fixed_factor_ops;

		ret = devm_clk_hw_रेजिस्टर(dev, &fix->hw);
		अगर (ret)
			वापस ret;

		dsi->clk_onecell->hws[i] = &fix->hw;
	पूर्ण

	वापस of_clk_add_hw_provider(dev->of_node,
				      of_clk_hw_onecell_get,
				      dsi->clk_onecell);
पूर्ण

अटल पूर्णांक vc4_dsi_bind(काष्ठा device *dev, काष्ठा device *master, व्योम *data)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा drm_device *drm = dev_get_drvdata(master);
	काष्ठा vc4_dsi *dsi = dev_get_drvdata(dev);
	काष्ठा vc4_dsi_encoder *vc4_dsi_encoder;
	काष्ठा drm_panel *panel;
	स्थिर काष्ठा of_device_id *match;
	dma_cap_mask_t dma_mask;
	पूर्णांक ret;

	match = of_match_device(vc4_dsi_dt_match, dev);
	अगर (!match)
		वापस -ENODEV;

	dsi->variant = match->data;

	vc4_dsi_encoder = devm_kzalloc(dev, माप(*vc4_dsi_encoder),
				       GFP_KERNEL);
	अगर (!vc4_dsi_encoder)
		वापस -ENOMEM;

	INIT_LIST_HEAD(&dsi->bridge_chain);
	vc4_dsi_encoder->base.type = VC4_ENCODER_TYPE_DSI1;
	vc4_dsi_encoder->dsi = dsi;
	dsi->encoder = &vc4_dsi_encoder->base.base;

	dsi->regs = vc4_ioremap_regs(pdev, 0);
	अगर (IS_ERR(dsi->regs))
		वापस PTR_ERR(dsi->regs);

	dsi->regset.base = dsi->regs;
	dsi->regset.regs = dsi->variant->regs;
	dsi->regset.nregs = dsi->variant->nregs;

	अगर (DSI_PORT_READ(ID) != DSI_ID_VALUE) अणु
		dev_err(dev, "Port returned 0x%08x for ID instead of 0x%08x\n",
			DSI_PORT_READ(ID), DSI_ID_VALUE);
		वापस -ENODEV;
	पूर्ण

	/* DSI1 on BCM2835/6/7 has a broken AXI slave that करोesn't respond to
	 * ग_लिखोs from the ARM.  It करोes handle ग_लिखोs from the DMA engine,
	 * so set up a channel क्रम talking to it.
	 */
	अगर (dsi->variant->broken_axi_workaround) अणु
		dsi->reg_dma_mem = dma_alloc_coherent(dev, 4,
						      &dsi->reg_dma_paddr,
						      GFP_KERNEL);
		अगर (!dsi->reg_dma_mem) अणु
			DRM_ERROR("Failed to get DMA memory\n");
			वापस -ENOMEM;
		पूर्ण

		dma_cap_zero(dma_mask);
		dma_cap_set(DMA_MEMCPY, dma_mask);
		dsi->reg_dma_chan = dma_request_chan_by_mask(&dma_mask);
		अगर (IS_ERR(dsi->reg_dma_chan)) अणु
			ret = PTR_ERR(dsi->reg_dma_chan);
			अगर (ret != -EPROBE_DEFER)
				DRM_ERROR("Failed to get DMA channel: %d\n",
					  ret);
			वापस ret;
		पूर्ण

		/* Get the physical address of the device's रेजिस्टरs.  The
		 * काष्ठा resource क्रम the regs gives us the bus address
		 * instead.
		 */
		dsi->reg_paddr = be32_to_cpup(of_get_address(dev->of_node,
							     0, शून्य, शून्य));
	पूर्ण

	init_completion(&dsi->xfer_completion);
	/* At startup enable error-reporting पूर्णांकerrupts and nothing अन्यथा. */
	DSI_PORT_WRITE(INT_EN, DSI1_INTERRUPTS_ALWAYS_ENABLED);
	/* Clear any existing पूर्णांकerrupt state. */
	DSI_PORT_WRITE(INT_STAT, DSI_PORT_READ(INT_STAT));

	अगर (dsi->reg_dma_mem)
		ret = devm_request_thपढ़ोed_irq(dev, platक्रमm_get_irq(pdev, 0),
						vc4_dsi_irq_defer_to_thपढ़ो_handler,
						vc4_dsi_irq_handler,
						IRQF_ONESHOT,
						"vc4 dsi", dsi);
	अन्यथा
		ret = devm_request_irq(dev, platक्रमm_get_irq(pdev, 0),
				       vc4_dsi_irq_handler, 0, "vc4 dsi", dsi);
	अगर (ret) अणु
		अगर (ret != -EPROBE_DEFER)
			dev_err(dev, "Failed to get interrupt: %d\n", ret);
		वापस ret;
	पूर्ण

	dsi->escape_घड़ी = devm_clk_get(dev, "escape");
	अगर (IS_ERR(dsi->escape_घड़ी)) अणु
		ret = PTR_ERR(dsi->escape_घड़ी);
		अगर (ret != -EPROBE_DEFER)
			dev_err(dev, "Failed to get escape clock: %d\n", ret);
		वापस ret;
	पूर्ण

	dsi->pll_phy_घड़ी = devm_clk_get(dev, "phy");
	अगर (IS_ERR(dsi->pll_phy_घड़ी)) अणु
		ret = PTR_ERR(dsi->pll_phy_घड़ी);
		अगर (ret != -EPROBE_DEFER)
			dev_err(dev, "Failed to get phy clock: %d\n", ret);
		वापस ret;
	पूर्ण

	dsi->pixel_घड़ी = devm_clk_get(dev, "pixel");
	अगर (IS_ERR(dsi->pixel_घड़ी)) अणु
		ret = PTR_ERR(dsi->pixel_घड़ी);
		अगर (ret != -EPROBE_DEFER)
			dev_err(dev, "Failed to get pixel clock: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = drm_of_find_panel_or_bridge(dev->of_node, 0, 0,
					  &panel, &dsi->bridge);
	अगर (ret) अणु
		/* If the bridge or panel poपूर्णांकed by dev->of_node is not
		 * enabled, just वापस 0 here so that we करोn't prevent the DRM
		 * dev from being रेजिस्टरed. Of course that means the DSI
		 * encoder won't be exposed, but that's not a problem since
		 * nothing is connected to it.
		 */
		अगर (ret == -ENODEV)
			वापस 0;

		वापस ret;
	पूर्ण

	अगर (panel) अणु
		dsi->bridge = devm_drm_panel_bridge_add_typed(dev, panel,
							      DRM_MODE_CONNECTOR_DSI);
		अगर (IS_ERR(dsi->bridge))
			वापस PTR_ERR(dsi->bridge);
	पूर्ण

	/* The esc घड़ी rate is supposed to always be 100Mhz. */
	ret = clk_set_rate(dsi->escape_घड़ी, 100 * 1000000);
	अगर (ret) अणु
		dev_err(dev, "Failed to set esc clock: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = vc4_dsi_init_phy_घड़ीs(dsi);
	अगर (ret)
		वापस ret;

	drm_simple_encoder_init(drm, dsi->encoder, DRM_MODE_ENCODER_DSI);
	drm_encoder_helper_add(dsi->encoder, &vc4_dsi_encoder_helper_funcs);

	ret = drm_bridge_attach(dsi->encoder, dsi->bridge, शून्य, 0);
	अगर (ret) अणु
		dev_err(dev, "bridge attach failed: %d\n", ret);
		वापस ret;
	पूर्ण
	/* Disable the atomic helper calls पूर्णांकo the bridge.  We
	 * manually call the bridge pre_enable / enable / etc. calls
	 * from our driver, since we need to sequence them within the
	 * encoder's enable/disable paths.
	 */
	list_splice_init(&dsi->encoder->bridge_chain, &dsi->bridge_chain);

	vc4_debugfs_add_regset32(drm, dsi->variant->debugfs_name, &dsi->regset);

	pm_runसमय_enable(dev);

	वापस 0;
पूर्ण

अटल व्योम vc4_dsi_unbind(काष्ठा device *dev, काष्ठा device *master,
			   व्योम *data)
अणु
	काष्ठा vc4_dsi *dsi = dev_get_drvdata(dev);

	अगर (dsi->bridge)
		pm_runसमय_disable(dev);

	/*
	 * Restore the bridge_chain so the bridge detach procedure can happen
	 * normally.
	 */
	list_splice_init(&dsi->bridge_chain, &dsi->encoder->bridge_chain);
	drm_encoder_cleanup(dsi->encoder);
पूर्ण

अटल स्थिर काष्ठा component_ops vc4_dsi_ops = अणु
	.bind   = vc4_dsi_bind,
	.unbind = vc4_dsi_unbind,
पूर्ण;

अटल पूर्णांक vc4_dsi_dev_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा vc4_dsi *dsi;

	dsi = devm_kzalloc(dev, माप(*dsi), GFP_KERNEL);
	अगर (!dsi)
		वापस -ENOMEM;
	dev_set_drvdata(dev, dsi);

	dsi->pdev = pdev;
	dsi->dsi_host.ops = &vc4_dsi_host_ops;
	dsi->dsi_host.dev = dev;
	mipi_dsi_host_रेजिस्टर(&dsi->dsi_host);

	वापस 0;
पूर्ण

अटल पूर्णांक vc4_dsi_dev_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा vc4_dsi *dsi = dev_get_drvdata(dev);

	component_del(&pdev->dev, &vc4_dsi_ops);
	mipi_dsi_host_unरेजिस्टर(&dsi->dsi_host);

	वापस 0;
पूर्ण

काष्ठा platक्रमm_driver vc4_dsi_driver = अणु
	.probe = vc4_dsi_dev_probe,
	.हटाओ = vc4_dsi_dev_हटाओ,
	.driver = अणु
		.name = "vc4_dsi",
		.of_match_table = vc4_dsi_dt_match,
	पूर्ण,
पूर्ण;
