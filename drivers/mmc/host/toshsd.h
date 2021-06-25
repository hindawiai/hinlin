<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *  Toshiba PCI Secure Digital Host Controller Interface driver
 *
 *  Copyright (C) 2014 Ondrej Zary
 *  Copyright (C) 2007 Riअक्षरd Betts, All Rights Reserved.
 *
 *      Based on asic3_mmc.c Copyright (c) 2005 SDG Systems, LLC
 */

#घोषणा HCLK	33000000	/* 33 MHz (PCI घड़ी) */

#घोषणा SD_PCICFG_CLKSTOP	0x40	/* 0x1f = घड़ी controller, 0 = stop */
#घोषणा SD_PCICFG_GATEDCLK	0x41	/* Gated घड़ी */
#घोषणा SD_PCICFG_CLKMODE	0x42	/* Control घड़ी of SD controller */
#घोषणा SD_PCICFG_PINSTATUS	0x44	/* R/O: पढ़ो status of SD pins */
#घोषणा SD_PCICFG_POWER1	0x48
#घोषणा SD_PCICFG_POWER2	0x49
#घोषणा SD_PCICFG_POWER3	0x4a
#घोषणा SD_PCICFG_CARDDETECT	0x4c
#घोषणा SD_PCICFG_SLOTS		0x50	/* R/O: define support slot number */
#घोषणा SD_PCICFG_EXTGATECLK1	0xf0	/* Could be used क्रम gated घड़ी */
#घोषणा SD_PCICFG_EXTGATECLK2	0xf1	/* Could be used क्रम gated घड़ी */
#घोषणा SD_PCICFG_EXTGATECLK3	0xf9	/* Bit 1: द्विगुन buffer/single buffer */
#घोषणा SD_PCICFG_SDLED_ENABLE1	0xfa
#घोषणा SD_PCICFG_SDLED_ENABLE2	0xfe

#घोषणा SD_PCICFG_CLKMODE_DIV_DISABLE	BIT(0)
#घोषणा SD_PCICFG_CLKSTOP_ENABLE_ALL	0x1f
#घोषणा SD_PCICFG_LED_ENABLE1_START	0x12
#घोषणा SD_PCICFG_LED_ENABLE2_START	0x80

#घोषणा SD_PCICFG_PWR1_33V	0x08	/* Set क्रम 3.3 volts */
#घोषणा SD_PCICFG_PWR1_OFF	0x00	/* Turn off घातer */
#घोषणा SD_PCICFG_PWR2_AUTO	0x02

#घोषणा SD_CMD			0x00	/* also क्रम SDIO */
#घोषणा SD_ARG0			0x04	/* also क्रम SDIO */
#घोषणा SD_ARG1			0x06	/* also क्रम SDIO */
#घोषणा SD_STOPINTERNAL		0x08
#घोषणा SD_BLOCKCOUNT		0x0a	/* also क्रम SDIO */
#घोषणा SD_RESPONSE0		0x0c	/* also क्रम SDIO */
#घोषणा SD_RESPONSE1		0x0e	/* also क्रम SDIO */
#घोषणा SD_RESPONSE2		0x10	/* also क्रम SDIO */
#घोषणा SD_RESPONSE3		0x12	/* also क्रम SDIO */
#घोषणा SD_RESPONSE4		0x14	/* also क्रम SDIO */
#घोषणा SD_RESPONSE5		0x16	/* also क्रम SDIO */
#घोषणा SD_RESPONSE6		0x18	/* also क्रम SDIO */
#घोषणा SD_RESPONSE7		0x1a	/* also क्रम SDIO */
#घोषणा SD_CARDSTATUS		0x1c	/* also क्रम SDIO */
#घोषणा SD_BUFFERCTRL		0x1e	/* also क्रम SDIO */
#घोषणा SD_INTMASKCARD		0x20	/* also क्रम SDIO */
#घोषणा SD_INTMASKBUFFER	0x22	/* also क्रम SDIO */
#घोषणा SD_CARDCLOCKCTRL	0x24
#घोषणा SD_CARDXFERDATALEN	0x26	/* also क्रम SDIO */
#घोषणा SD_CARDOPTIONSETUP	0x28	/* also क्रम SDIO */
#घोषणा SD_ERRORSTATUS0		0x2c	/* also क्रम SDIO */
#घोषणा SD_ERRORSTATUS1		0x2e	/* also क्रम SDIO */
#घोषणा SD_DATAPORT		0x30	/* also क्रम SDIO */
#घोषणा SD_TRANSACTIONCTRL	0x34	/* also क्रम SDIO */
#घोषणा SD_SOFTWARERESET	0xe0	/* also क्रम SDIO */

/* रेजिस्टरs above marked "also for SDIO" and all SDIO रेजिस्टरs below can be
 * accessed at SDIO_BASE + reg address */
#घोषणा SDIO_BASE	 0x100

#घोषणा SDIO_CARDPORTSEL	0x02
#घोषणा SDIO_CARDINTCTRL	0x36
#घोषणा SDIO_CLOCKNWAITCTRL	0x38
#घोषणा SDIO_HOSTINFORMATION	0x3a
#घोषणा SDIO_ERRORCTRL		0x3c
#घोषणा SDIO_LEDCTRL		0x3e

#घोषणा SD_TRANSCTL_SET		BIT(8)

#घोषणा SD_CARDCLK_DIV_DISABLE	BIT(15)
#घोषणा SD_CARDCLK_ENABLE_CLOCK	BIT(8)
#घोषणा SD_CARDCLK_CLK_DIV_512	BIT(7)
#घोषणा SD_CARDCLK_CLK_DIV_256	BIT(6)
#घोषणा SD_CARDCLK_CLK_DIV_128	BIT(5)
#घोषणा SD_CARDCLK_CLK_DIV_64	BIT(4)
#घोषणा SD_CARDCLK_CLK_DIV_32	BIT(3)
#घोषणा SD_CARDCLK_CLK_DIV_16	BIT(2)
#घोषणा SD_CARDCLK_CLK_DIV_8	BIT(1)
#घोषणा SD_CARDCLK_CLK_DIV_4	BIT(0)
#घोषणा SD_CARDCLK_CLK_DIV_2	0

#घोषणा SD_CARDOPT_REQUIRED		0x000e
#घोषणा SD_CARDOPT_DATA_RESP_TIMEOUT(x)	(((x) & 0x0f) << 4) /* 4 bits */
#घोषणा SD_CARDOPT_C2_MODULE_ABSENT	BIT(14)
#घोषणा SD_CARDOPT_DATA_XFR_WIDTH_1	(1 << 15)
#घोषणा SD_CARDOPT_DATA_XFR_WIDTH_4	(0 << 15)

#घोषणा SD_CMD_TYPE_CMD			(0 << 6)
#घोषणा SD_CMD_TYPE_ACMD		(1 << 6)
#घोषणा SD_CMD_TYPE_AUTHEN		(2 << 6)
#घोषणा SD_CMD_RESP_TYPE_NONE		(3 << 8)
#घोषणा SD_CMD_RESP_TYPE_EXT_R1		(4 << 8)
#घोषणा SD_CMD_RESP_TYPE_EXT_R1B	(5 << 8)
#घोषणा SD_CMD_RESP_TYPE_EXT_R2		(6 << 8)
#घोषणा SD_CMD_RESP_TYPE_EXT_R3		(7 << 8)
#घोषणा SD_CMD_RESP_TYPE_EXT_R6		(4 << 8)
#घोषणा SD_CMD_RESP_TYPE_EXT_R7		(4 << 8)
#घोषणा SD_CMD_DATA_PRESENT		BIT(11)
#घोषणा SD_CMD_TRANSFER_READ		BIT(12)
#घोषणा SD_CMD_MULTI_BLOCK		BIT(13)
#घोषणा SD_CMD_SECURITY_CMD		BIT(14)

#घोषणा SD_STOPINT_ISSUE_CMD12		BIT(0)
#घोषणा SD_STOPINT_AUTO_ISSUE_CMD12	BIT(8)

#घोषणा SD_CARD_RESP_END	BIT(0)
#घोषणा SD_CARD_RW_END		BIT(2)
#घोषणा SD_CARD_CARD_REMOVED_0	BIT(3)
#घोषणा SD_CARD_CARD_INSERTED_0	BIT(4)
#घोषणा SD_CARD_PRESENT_0	BIT(5)
#घोषणा SD_CARD_UNK6		BIT(6)
#घोषणा SD_CARD_WRITE_PROTECT	BIT(7)
#घोषणा SD_CARD_CARD_REMOVED_3	BIT(8)
#घोषणा SD_CARD_CARD_INSERTED_3	BIT(9)
#घोषणा SD_CARD_PRESENT_3	BIT(10)

#घोषणा SD_BUF_CMD_INDEX_ERR	BIT(16)
#घोषणा SD_BUF_CRC_ERR		BIT(17)
#घोषणा SD_BUF_STOP_BIT_END_ERR	BIT(18)
#घोषणा SD_BUF_DATA_TIMEOUT	BIT(19)
#घोषणा SD_BUF_OVERFLOW		BIT(20)
#घोषणा SD_BUF_UNDERFLOW	BIT(21)
#घोषणा SD_BUF_CMD_TIMEOUT	BIT(22)
#घोषणा SD_BUF_UNK7		BIT(23)
#घोषणा SD_BUF_READ_ENABLE	BIT(24)
#घोषणा SD_BUF_WRITE_ENABLE	BIT(25)
#घोषणा SD_BUF_ILLEGAL_FUNCTION	BIT(29)
#घोषणा SD_BUF_CMD_BUSY		BIT(30)
#घोषणा SD_BUF_ILLEGAL_ACCESS	BIT(31)

#घोषणा SD_ERR0_RESP_CMD_ERR			BIT(0)
#घोषणा SD_ERR0_RESP_NON_CMD12_END_BIT_ERR	BIT(2)
#घोषणा SD_ERR0_RESP_CMD12_END_BIT_ERR		BIT(3)
#घोषणा SD_ERR0_READ_DATA_END_BIT_ERR		BIT(4)
#घोषणा SD_ERR0_WRITE_CRC_STATUS_END_BIT_ERR	BIT(5)
#घोषणा SD_ERR0_RESP_NON_CMD12_CRC_ERR		BIT(8)
#घोषणा SD_ERR0_RESP_CMD12_CRC_ERR		BIT(9)
#घोषणा SD_ERR0_READ_DATA_CRC_ERR		BIT(10)
#घोषणा SD_ERR0_WRITE_CMD_CRC_ERR		BIT(11)

#घोषणा SD_ERR1_NO_CMD_RESP		BIT(16)
#घोषणा SD_ERR1_TIMEOUT_READ_DATA	BIT(20)
#घोषणा SD_ERR1_TIMEOUT_CRS_STATUS	BIT(21)
#घोषणा SD_ERR1_TIMEOUT_CRC_BUSY	BIT(22)

#घोषणा IRQ_DONT_CARE_BITS (SD_CARD_PRESENT_3 \
	| SD_CARD_WRITE_PROTECT \
	| SD_CARD_UNK6 \
	| SD_CARD_PRESENT_0 \
	| SD_BUF_UNK7 \
	| SD_BUF_CMD_BUSY)

काष्ठा toshsd_host अणु
	काष्ठा pci_dev *pdev;
	काष्ठा mmc_host *mmc;

	spinlock_t lock;

	काष्ठा mmc_request *mrq;/* Current request */
	काष्ठा mmc_command *cmd;/* Current command */
	काष्ठा mmc_data *data;	/* Current data request */

	काष्ठा sg_mapping_iter sg_miter; /* क्रम PIO */

	व्योम __iomem *ioaddr; /* mapped address */
पूर्ण;
