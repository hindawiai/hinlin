<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *  linux/drivers/mmc/host/wbsd.h - Winbond W83L51xD SD/MMC driver
 *
 *  Copyright (C) 2004-2007 Pierre Ossman, All Rights Reserved.
 */

#घोषणा LOCK_CODE		0xAA

#घोषणा WBSD_CONF_SWRST		0x02
#घोषणा WBSD_CONF_DEVICE	0x07
#घोषणा WBSD_CONF_ID_HI		0x20
#घोषणा WBSD_CONF_ID_LO		0x21
#घोषणा WBSD_CONF_POWER		0x22
#घोषणा WBSD_CONF_PME		0x23
#घोषणा WBSD_CONF_PMES		0x24

#घोषणा WBSD_CONF_ENABLE	0x30
#घोषणा WBSD_CONF_PORT_HI	0x60
#घोषणा WBSD_CONF_PORT_LO	0x61
#घोषणा WBSD_CONF_IRQ		0x70
#घोषणा WBSD_CONF_DRQ		0x74

#घोषणा WBSD_CONF_PINS		0xF0

#घोषणा DEVICE_SD		0x03

#घोषणा WBSD_PINS_DAT3_HI	0x20
#घोषणा WBSD_PINS_DAT3_OUT	0x10
#घोषणा WBSD_PINS_GP11_HI	0x04
#घोषणा WBSD_PINS_DETECT_GP11	0x02
#घोषणा WBSD_PINS_DETECT_DAT3	0x01

#घोषणा WBSD_CMDR		0x00
#घोषणा WBSD_DFR		0x01
#घोषणा WBSD_EIR		0x02
#घोषणा WBSD_ISR		0x03
#घोषणा WBSD_FSR		0x04
#घोषणा WBSD_IDXR		0x05
#घोषणा WBSD_DATAR		0x06
#घोषणा WBSD_CSR		0x07

#घोषणा WBSD_EINT_CARD		0x40
#घोषणा WBSD_EINT_FIFO_THRE	0x20
#घोषणा WBSD_EINT_CRC		0x10
#घोषणा WBSD_EINT_TIMEOUT	0x08
#घोषणा WBSD_EINT_PROGEND	0x04
#घोषणा WBSD_EINT_BUSYEND	0x02
#घोषणा WBSD_EINT_TC		0x01

#घोषणा WBSD_INT_PENDING	0x80
#घोषणा WBSD_INT_CARD		0x40
#घोषणा WBSD_INT_FIFO_THRE	0x20
#घोषणा WBSD_INT_CRC		0x10
#घोषणा WBSD_INT_TIMEOUT	0x08
#घोषणा WBSD_INT_PROGEND	0x04
#घोषणा WBSD_INT_BUSYEND	0x02
#घोषणा WBSD_INT_TC		0x01

#घोषणा WBSD_FIFO_EMPTY		0x80
#घोषणा WBSD_FIFO_FULL		0x40
#घोषणा WBSD_FIFO_EMTHRE	0x20
#घोषणा WBSD_FIFO_FUTHRE	0x10
#घोषणा WBSD_FIFO_SZMASK	0x0F

#घोषणा WBSD_MSLED		0x20
#घोषणा WBSD_POWER_N		0x10
#घोषणा WBSD_WRPT		0x04
#घोषणा WBSD_CARDPRESENT	0x01

#घोषणा WBSD_IDX_CLK		0x01
#घोषणा WBSD_IDX_PBSMSB		0x02
#घोषणा WBSD_IDX_TAAC		0x03
#घोषणा WBSD_IDX_NSAC		0x04
#घोषणा WBSD_IDX_PBSLSB		0x05
#घोषणा WBSD_IDX_SETUP		0x06
#घोषणा WBSD_IDX_DMA		0x07
#घोषणा WBSD_IDX_FIFOEN		0x08
#घोषणा WBSD_IDX_STATUS		0x10
#घोषणा WBSD_IDX_RSPLEN		0x1E
#घोषणा WBSD_IDX_RESP0		0x1F
#घोषणा WBSD_IDX_RESP1		0x20
#घोषणा WBSD_IDX_RESP2		0x21
#घोषणा WBSD_IDX_RESP3		0x22
#घोषणा WBSD_IDX_RESP4		0x23
#घोषणा WBSD_IDX_RESP5		0x24
#घोषणा WBSD_IDX_RESP6		0x25
#घोषणा WBSD_IDX_RESP7		0x26
#घोषणा WBSD_IDX_RESP8		0x27
#घोषणा WBSD_IDX_RESP9		0x28
#घोषणा WBSD_IDX_RESP10		0x29
#घोषणा WBSD_IDX_RESP11		0x2A
#घोषणा WBSD_IDX_RESP12		0x2B
#घोषणा WBSD_IDX_RESP13		0x2C
#घोषणा WBSD_IDX_RESP14		0x2D
#घोषणा WBSD_IDX_RESP15		0x2E
#घोषणा WBSD_IDX_RESP16		0x2F
#घोषणा WBSD_IDX_CRCSTATUS	0x30
#घोषणा WBSD_IDX_ISR		0x3F

#घोषणा WBSD_CLK_375K		0x00
#घोषणा WBSD_CLK_12M		0x01
#घोषणा WBSD_CLK_16M		0x02
#घोषणा WBSD_CLK_24M		0x03

#घोषणा WBSD_DATA_WIDTH		0x01

#घोषणा WBSD_DAT3_H		0x08
#घोषणा WBSD_FIFO_RESET		0x04
#घोषणा WBSD_SOFT_RESET		0x02
#घोषणा WBSD_INC_INDEX		0x01

#घोषणा WBSD_DMA_SINGLE		0x02
#घोषणा WBSD_DMA_ENABLE		0x01

#घोषणा WBSD_FIFOEN_EMPTY	0x20
#घोषणा WBSD_FIFOEN_FULL	0x10
#घोषणा WBSD_FIFO_THREMASK	0x0F

#घोषणा WBSD_BLOCK_READ		0x80
#घोषणा WBSD_BLOCK_WRITE	0x40
#घोषणा WBSD_BUSY		0x20
#घोषणा WBSD_CARDTRAFFIC	0x04
#घोषणा WBSD_SENDCMD		0x02
#घोषणा WBSD_RECVRES		0x01

#घोषणा WBSD_RSP_SHORT		0x00
#घोषणा WBSD_RSP_LONG		0x01

#घोषणा WBSD_CRC_MASK		0x1F
#घोषणा WBSD_CRC_OK		0x05 /* S010E (00101) */
#घोषणा WBSD_CRC_FAIL		0x0B /* S101E (01011) */

#घोषणा WBSD_DMA_SIZE		65536

काष्ठा wbsd_host
अणु
	काष्ठा mmc_host*	mmc;		/* MMC काष्ठाure */

	spinlock_t		lock;		/* Mutex */

	पूर्णांक			flags;		/* Driver states */

#घोषणा WBSD_FCARD_PRESENT	(1<<0)		/* Card is present */
#घोषणा WBSD_FIGNORE_DETECT	(1<<1)		/* Ignore card detection */

	काष्ठा mmc_request*	mrq;		/* Current request */

	u8			isr;		/* Accumulated ISR */

	काष्ठा scatterlist*	cur_sg;		/* Current SG entry */
	अचिन्हित पूर्णांक		num_sg;		/* Number of entries left */

	अचिन्हित पूर्णांक		offset;		/* Offset पूर्णांकo current entry */
	अचिन्हित पूर्णांक		reमुख्य;		/* Data left in curren entry */

	अक्षर*			dma_buffer;	/* ISA DMA buffer */
	dma_addr_t		dma_addr;	/* Physical address क्रम same */

	पूर्णांक			firsterr;	/* See fअगरo functions */

	u8			clk;		/* Current घड़ी speed */
	अचिन्हित अक्षर		bus_width;	/* Current bus width */

	पूर्णांक			config;		/* Config port */
	u8			unlock_code;	/* Code to unlock config */

	पूर्णांक			chip_id;	/* ID of controller */

	पूर्णांक			base;		/* I/O port base */
	पूर्णांक			irq;		/* Interrupt */
	पूर्णांक			dma;		/* DMA channel */

	काष्ठा tasklet_काष्ठा	card_tasklet;	/* Tasklet काष्ठाures */
	काष्ठा tasklet_काष्ठा	fअगरo_tasklet;
	काष्ठा tasklet_काष्ठा	crc_tasklet;
	काष्ठा tasklet_काष्ठा	समयout_tasklet;
	काष्ठा tasklet_काष्ठा	finish_tasklet;

	काष्ठा समयr_list	ignore_समयr;	/* Ignore detection समयr */
पूर्ण;
