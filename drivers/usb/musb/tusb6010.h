<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Definitions क्रम TUSB6010 USB 2.0 OTG Dual Role controller
 *
 * Copyright (C) 2006 Nokia Corporation
 * Tony Lindgren <tony@atomide.com>
 */

#अगर_अघोषित __TUSB6010_H__
#घोषणा __TUSB6010_H__

/* VLYNQ control रेजिस्टर. 32-bit at offset 0x000 */
#घोषणा TUSB_VLYNQ_CTRL			0x004

/* Mentor Graphics OTG core रेजिस्टरs. 8,- 16- and 32-bit at offset 0x400 */
#घोषणा TUSB_BASE_OFFSET		0x400

/* FIFO रेजिस्टरs 32-bit at offset 0x600 */
#घोषणा TUSB_FIFO_BASE			0x600

/* Device System & Control रेजिस्टरs. 32-bit at offset 0x800 */
#घोषणा TUSB_SYS_REG_BASE		0x800

#घोषणा TUSB_DEV_CONF			(TUSB_SYS_REG_BASE + 0x000)
#घोषणा		TUSB_DEV_CONF_USB_HOST_MODE		(1 << 16)
#घोषणा		TUSB_DEV_CONF_PROD_TEST_MODE		(1 << 15)
#घोषणा		TUSB_DEV_CONF_SOFT_ID			(1 << 1)
#घोषणा		TUSB_DEV_CONF_ID_SEL			(1 << 0)

#घोषणा TUSB_PHY_OTG_CTRL_ENABLE	(TUSB_SYS_REG_BASE + 0x004)
#घोषणा TUSB_PHY_OTG_CTRL		(TUSB_SYS_REG_BASE + 0x008)
#घोषणा		TUSB_PHY_OTG_CTRL_WRPROTECT		(0xa5 << 24)
#घोषणा		TUSB_PHY_OTG_CTRL_OTG_ID_PULLUP		(1 << 23)
#घोषणा		TUSB_PHY_OTG_CTRL_OTG_VBUS_DET_EN	(1 << 19)
#घोषणा		TUSB_PHY_OTG_CTRL_OTG_SESS_END_EN	(1 << 18)
#घोषणा		TUSB_PHY_OTG_CTRL_TESTM2		(1 << 17)
#घोषणा		TUSB_PHY_OTG_CTRL_TESTM1		(1 << 16)
#घोषणा		TUSB_PHY_OTG_CTRL_TESTM0		(1 << 15)
#घोषणा		TUSB_PHY_OTG_CTRL_TX_DATA2		(1 << 14)
#घोषणा		TUSB_PHY_OTG_CTRL_TX_GZ2		(1 << 13)
#घोषणा		TUSB_PHY_OTG_CTRL_TX_ENABLE2		(1 << 12)
#घोषणा		TUSB_PHY_OTG_CTRL_DM_PULLDOWN		(1 << 11)
#घोषणा		TUSB_PHY_OTG_CTRL_DP_PULLDOWN		(1 << 10)
#घोषणा		TUSB_PHY_OTG_CTRL_OSC_EN		(1 << 9)
#घोषणा		TUSB_PHY_OTG_CTRL_PHYREF_CLKSEL(v)	(((v) & 3) << 7)
#घोषणा		TUSB_PHY_OTG_CTRL_PD			(1 << 6)
#घोषणा		TUSB_PHY_OTG_CTRL_PLL_ON		(1 << 5)
#घोषणा		TUSB_PHY_OTG_CTRL_EXT_RPU		(1 << 4)
#घोषणा		TUSB_PHY_OTG_CTRL_PWR_GOOD		(1 << 3)
#घोषणा		TUSB_PHY_OTG_CTRL_RESET			(1 << 2)
#घोषणा		TUSB_PHY_OTG_CTRL_SUSPENDM		(1 << 1)
#घोषणा		TUSB_PHY_OTG_CTRL_CLK_MODE		(1 << 0)

/*OTG status रेजिस्टर */
#घोषणा TUSB_DEV_OTG_STAT		(TUSB_SYS_REG_BASE + 0x00c)
#घोषणा		TUSB_DEV_OTG_STAT_PWR_CLK_GOOD		(1 << 8)
#घोषणा		TUSB_DEV_OTG_STAT_SESS_END		(1 << 7)
#घोषणा		TUSB_DEV_OTG_STAT_SESS_VALID		(1 << 6)
#घोषणा		TUSB_DEV_OTG_STAT_VBUS_VALID		(1 << 5)
#घोषणा		TUSB_DEV_OTG_STAT_VBUS_SENSE		(1 << 4)
#घोषणा		TUSB_DEV_OTG_STAT_ID_STATUS		(1 << 3)
#घोषणा		TUSB_DEV_OTG_STAT_HOST_DISCON		(1 << 2)
#घोषणा		TUSB_DEV_OTG_STAT_LINE_STATE		(3 << 0)
#घोषणा		TUSB_DEV_OTG_STAT_DP_ENABLE		(1 << 1)
#घोषणा		TUSB_DEV_OTG_STAT_DM_ENABLE		(1 << 0)

#घोषणा TUSB_DEV_OTG_TIMER		(TUSB_SYS_REG_BASE + 0x010)
#	define TUSB_DEV_OTG_TIMER_ENABLE		(1 << 31)
#	define TUSB_DEV_OTG_TIMER_VAL(v)		((v) & 0x07ffffff)
#घोषणा TUSB_PRCM_REV			(TUSB_SYS_REG_BASE + 0x014)

/* PRCM configuration रेजिस्टर */
#घोषणा TUSB_PRCM_CONF			(TUSB_SYS_REG_BASE + 0x018)
#घोषणा		TUSB_PRCM_CONF_SFW_CPEN		(1 << 24)
#घोषणा		TUSB_PRCM_CONF_SYS_CLKSEL(v)	(((v) & 3) << 16)

/* PRCM management रेजिस्टर */
#घोषणा TUSB_PRCM_MNGMT			(TUSB_SYS_REG_BASE + 0x01c)
#घोषणा		TUSB_PRCM_MNGMT_SRP_FIX_TIMER(v)	(((v) & 0xf) << 25)
#घोषणा		TUSB_PRCM_MNGMT_SRP_FIX_EN		(1 << 24)
#घोषणा		TUSB_PRCM_MNGMT_VBUS_VALID_TIMER(v)	(((v) & 0xf) << 20)
#घोषणा		TUSB_PRCM_MNGMT_VBUS_VALID_FLT_EN	(1 << 19)
#घोषणा		TUSB_PRCM_MNGMT_DFT_CLK_DIS		(1 << 18)
#घोषणा		TUSB_PRCM_MNGMT_VLYNQ_CLK_DIS		(1 << 17)
#घोषणा		TUSB_PRCM_MNGMT_OTG_SESS_END_EN		(1 << 10)
#घोषणा		TUSB_PRCM_MNGMT_OTG_VBUS_DET_EN		(1 << 9)
#घोषणा		TUSB_PRCM_MNGMT_OTG_ID_PULLUP		(1 << 8)
#घोषणा		TUSB_PRCM_MNGMT_15_SW_EN		(1 << 4)
#घोषणा		TUSB_PRCM_MNGMT_33_SW_EN		(1 << 3)
#घोषणा		TUSB_PRCM_MNGMT_5V_CPEN			(1 << 2)
#घोषणा		TUSB_PRCM_MNGMT_PM_IDLE			(1 << 1)
#घोषणा		TUSB_PRCM_MNGMT_DEV_IDLE		(1 << 0)

/* Wake-up source clear and mask रेजिस्टरs */
#घोषणा TUSB_PRCM_WAKEUP_SOURCE		(TUSB_SYS_REG_BASE + 0x020)
#घोषणा TUSB_PRCM_WAKEUP_CLEAR		(TUSB_SYS_REG_BASE + 0x028)
#घोषणा TUSB_PRCM_WAKEUP_MASK		(TUSB_SYS_REG_BASE + 0x02c)
#घोषणा		TUSB_PRCM_WAKEUP_RESERVED_BITS	(0xffffe << 13)
#घोषणा		TUSB_PRCM_WGPIO_7	(1 << 12)
#घोषणा		TUSB_PRCM_WGPIO_6	(1 << 11)
#घोषणा		TUSB_PRCM_WGPIO_5	(1 << 10)
#घोषणा		TUSB_PRCM_WGPIO_4	(1 << 9)
#घोषणा		TUSB_PRCM_WGPIO_3	(1 << 8)
#घोषणा		TUSB_PRCM_WGPIO_2	(1 << 7)
#घोषणा		TUSB_PRCM_WGPIO_1	(1 << 6)
#घोषणा		TUSB_PRCM_WGPIO_0	(1 << 5)
#घोषणा		TUSB_PRCM_WHOSTDISCON	(1 << 4)	/* Host disconnect */
#घोषणा		TUSB_PRCM_WBUS		(1 << 3)	/* USB bus resume */
#घोषणा		TUSB_PRCM_WNORCS	(1 << 2)	/* NOR chip select */
#घोषणा		TUSB_PRCM_WVBUS		(1 << 1)	/* OTG PHY VBUS */
#घोषणा		TUSB_PRCM_WID		(1 << 0)	/* OTG PHY ID detect */

#घोषणा TUSB_PULLUP_1_CTRL		(TUSB_SYS_REG_BASE + 0x030)
#घोषणा TUSB_PULLUP_2_CTRL		(TUSB_SYS_REG_BASE + 0x034)
#घोषणा TUSB_INT_CTRL_REV		(TUSB_SYS_REG_BASE + 0x038)
#घोषणा TUSB_INT_CTRL_CONF		(TUSB_SYS_REG_BASE + 0x03c)
#घोषणा TUSB_USBIP_INT_SRC		(TUSB_SYS_REG_BASE + 0x040)
#घोषणा TUSB_USBIP_INT_SET		(TUSB_SYS_REG_BASE + 0x044)
#घोषणा TUSB_USBIP_INT_CLEAR		(TUSB_SYS_REG_BASE + 0x048)
#घोषणा TUSB_USBIP_INT_MASK		(TUSB_SYS_REG_BASE + 0x04c)
#घोषणा TUSB_DMA_INT_SRC		(TUSB_SYS_REG_BASE + 0x050)
#घोषणा TUSB_DMA_INT_SET		(TUSB_SYS_REG_BASE + 0x054)
#घोषणा TUSB_DMA_INT_CLEAR		(TUSB_SYS_REG_BASE + 0x058)
#घोषणा TUSB_DMA_INT_MASK		(TUSB_SYS_REG_BASE + 0x05c)
#घोषणा TUSB_GPIO_INT_SRC		(TUSB_SYS_REG_BASE + 0x060)
#घोषणा TUSB_GPIO_INT_SET		(TUSB_SYS_REG_BASE + 0x064)
#घोषणा TUSB_GPIO_INT_CLEAR		(TUSB_SYS_REG_BASE + 0x068)
#घोषणा TUSB_GPIO_INT_MASK		(TUSB_SYS_REG_BASE + 0x06c)

/* NOR flash पूर्णांकerrupt source रेजिस्टरs */
#घोषणा TUSB_INT_SRC			(TUSB_SYS_REG_BASE + 0x070)
#घोषणा TUSB_INT_SRC_SET		(TUSB_SYS_REG_BASE + 0x074)
#घोषणा TUSB_INT_SRC_CLEAR		(TUSB_SYS_REG_BASE + 0x078)
#घोषणा TUSB_INT_MASK			(TUSB_SYS_REG_BASE + 0x07c)
#घोषणा		TUSB_INT_SRC_TXRX_DMA_DONE		(1 << 24)
#घोषणा		TUSB_INT_SRC_USB_IP_CORE		(1 << 17)
#घोषणा		TUSB_INT_SRC_OTG_TIMEOUT		(1 << 16)
#घोषणा		TUSB_INT_SRC_VBUS_SENSE_CHNG		(1 << 15)
#घोषणा		TUSB_INT_SRC_ID_STATUS_CHNG		(1 << 14)
#घोषणा		TUSB_INT_SRC_DEV_WAKEUP			(1 << 13)
#घोषणा		TUSB_INT_SRC_DEV_READY			(1 << 12)
#घोषणा		TUSB_INT_SRC_USB_IP_TX			(1 << 9)
#घोषणा		TUSB_INT_SRC_USB_IP_RX			(1 << 8)
#घोषणा		TUSB_INT_SRC_USB_IP_VBUS_ERR		(1 << 7)
#घोषणा		TUSB_INT_SRC_USB_IP_VBUS_REQ		(1 << 6)
#घोषणा		TUSB_INT_SRC_USB_IP_DISCON		(1 << 5)
#घोषणा		TUSB_INT_SRC_USB_IP_CONN		(1 << 4)
#घोषणा		TUSB_INT_SRC_USB_IP_SOF			(1 << 3)
#घोषणा		TUSB_INT_SRC_USB_IP_RST_BABBLE		(1 << 2)
#घोषणा		TUSB_INT_SRC_USB_IP_RESUME		(1 << 1)
#घोषणा		TUSB_INT_SRC_USB_IP_SUSPEND		(1 << 0)

/* NOR flash पूर्णांकerrupt रेजिस्टरs reserved bits. Must be written as 0 */
#घोषणा		TUSB_INT_MASK_RESERVED_17		(0x3fff << 17)
#घोषणा		TUSB_INT_MASK_RESERVED_13		(1 << 13)
#घोषणा		TUSB_INT_MASK_RESERVED_8		(0xf << 8)
#घोषणा		TUSB_INT_SRC_RESERVED_26		(0x1f << 26)
#घोषणा		TUSB_INT_SRC_RESERVED_18		(0x3f << 18)
#घोषणा		TUSB_INT_SRC_RESERVED_10		(0x03 << 10)

/* Reserved bits क्रम NOR flash पूर्णांकerrupt mask and clear रेजिस्टर */
#घोषणा		TUSB_INT_MASK_RESERVED_BITS	(TUSB_INT_MASK_RESERVED_17 | \
						TUSB_INT_MASK_RESERVED_13 | \
						TUSB_INT_MASK_RESERVED_8)

/* Reserved bits क्रम NOR flash पूर्णांकerrupt status रेजिस्टर */
#घोषणा		TUSB_INT_SRC_RESERVED_BITS	(TUSB_INT_SRC_RESERVED_26 | \
						TUSB_INT_SRC_RESERVED_18 | \
						TUSB_INT_SRC_RESERVED_10)

#घोषणा TUSB_GPIO_REV			(TUSB_SYS_REG_BASE + 0x080)
#घोषणा TUSB_GPIO_CONF			(TUSB_SYS_REG_BASE + 0x084)
#घोषणा TUSB_DMA_CTRL_REV		(TUSB_SYS_REG_BASE + 0x100)
#घोषणा TUSB_DMA_REQ_CONF		(TUSB_SYS_REG_BASE + 0x104)
#घोषणा TUSB_EP0_CONF			(TUSB_SYS_REG_BASE + 0x108)
#घोषणा TUSB_DMA_EP_MAP			(TUSB_SYS_REG_BASE + 0x148)

/* Offsets from each ep base रेजिस्टर */
#घोषणा TUSB_EP_TX_OFFSET		0x10c	/* EP_IN in करोcs */
#घोषणा TUSB_EP_RX_OFFSET		0x14c	/* EP_OUT in करोcs */
#घोषणा TUSB_EP_MAX_PACKET_SIZE_OFFSET	0x188

#घोषणा TUSB_WAIT_COUNT			(TUSB_SYS_REG_BASE + 0x1c8)
#घोषणा TUSB_SCRATCH_PAD		(TUSB_SYS_REG_BASE + 0x1c4)
#घोषणा TUSB_PROD_TEST_RESET		(TUSB_SYS_REG_BASE + 0x1d8)

/* Device System & Control रेजिस्टर bitfields */
#घोषणा TUSB_INT_CTRL_CONF_INT_RELCYC(v)	(((v) & 0x7) << 18)
#घोषणा TUSB_INT_CTRL_CONF_INT_POLARITY		(1 << 17)
#घोषणा TUSB_INT_CTRL_CONF_INT_MODE		(1 << 16)
#घोषणा TUSB_GPIO_CONF_DMAREQ(v)		(((v) & 0x3f) << 24)
#घोषणा TUSB_DMA_REQ_CONF_BURST_SIZE(v)		(((v) & 3) << 26)
#घोषणा TUSB_DMA_REQ_CONF_DMA_REQ_EN(v)		(((v) & 0x3f) << 20)
#घोषणा TUSB_DMA_REQ_CONF_DMA_REQ_ASSER(v)	(((v) & 0xf) << 16)
#घोषणा TUSB_EP0_CONFIG_SW_EN			(1 << 8)
#घोषणा TUSB_EP0_CONFIG_सूची_TX			(1 << 7)
#घोषणा TUSB_EP0_CONFIG_XFR_SIZE(v)		((v) & 0x7f)
#घोषणा TUSB_EP_CONFIG_SW_EN			(1 << 31)
#घोषणा TUSB_EP_CONFIG_XFR_SIZE(v)		((v) & 0x7fffffff)
#घोषणा TUSB_PROD_TEST_RESET_VAL		0xa596
#घोषणा TUSB_EP_FIFO(ep)			(TUSB_FIFO_BASE + (ep) * 0x20)

#घोषणा TUSB_DIDR1_LO				(TUSB_SYS_REG_BASE + 0x1f8)
#घोषणा TUSB_DIDR1_HI				(TUSB_SYS_REG_BASE + 0x1fc)
#घोषणा		TUSB_DIDR1_HI_CHIP_REV(v)		(((v) >> 17) & 0xf)
#घोषणा			TUSB_DIDR1_HI_REV_20		0
#घोषणा			TUSB_DIDR1_HI_REV_30		1
#घोषणा			TUSB_DIDR1_HI_REV_31		2

#घोषणा TUSB_REV_10	0x10
#घोषणा TUSB_REV_20	0x20
#घोषणा TUSB_REV_30	0x30
#घोषणा TUSB_REV_31	0x31

#पूर्ण_अगर /* __TUSB6010_H__ */
