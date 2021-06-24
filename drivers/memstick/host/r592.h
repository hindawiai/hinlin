<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2010 - Maxim Levitsky
 * driver क्रम Ricoh memstick पढ़ोers
 */

#अगर_अघोषित R592_H

#समावेश <linux/memstick.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/kfअगरo.h>
#समावेश <linux/प्रकार.स>

/* ग_लिखो to this reg (number,len) triggers TPC execution */
#घोषणा R592_TPC_EXEC			0x00
#घोषणा R592_TPC_EXEC_LEN_SHIFT		16		/* Bits 16..25 are TPC len */
#घोषणा R592_TPC_EXEC_BIG_FIFO		(1 << 26)	/* If bit 26 is set, large fअगरo is used (reg 48) */
#घोषणा R592_TPC_EXEC_TPC_SHIFT		28		/* Bits 28..31 are the TPC number */


/* Winकरोw क्रम small TPC fअगरo (big endian)*/
/* पढ़ोs and ग_लिखोs always are करोne in  8 byte chunks */
/* Not used in driver, because large fअगरo करोes better job */
#घोषणा R592_SFIFO			0x08


/* Status रेजिस्टर (ms पूर्णांक, small fअगरo, IO)*/
#घोषणा R592_STATUS			0x10
							/* Parallel INT bits */
#घोषणा R592_STATUS_P_CMDNACK		(1 << 16)	/* INT reg: NACK (parallel mode) */
#घोषणा R592_STATUS_P_BREQ		(1 << 17)	/* INT reg: card पढ़ोy (parallel mode)*/
#घोषणा R592_STATUS_P_INTERR		(1 << 18)	/* INT reg: पूर्णांक error (parallel mode)*/
#घोषणा R592_STATUS_P_CED		(1 << 19)	/* INT reg: command करोne (parallel mode) */

							/* Fअगरo status */
#घोषणा R592_STATUS_SFIFO_FULL		(1 << 20)	/* Small Fअगरo almost full (last chunk is written) */
#घोषणा R592_STATUS_SFIFO_EMPTY		(1 << 21)	/* Small Fअगरo empty */

							/* Error detection via CRC */
#घोषणा R592_STATUS_SEND_ERR		(1 << 24)	/* Send failed */
#घोषणा R592_STATUS_RECV_ERR		(1 << 25)	/* Receive failed */

							/* Card state */
#घोषणा R592_STATUS_RDY			(1 << 28)	/* RDY संकेत received */
#घोषणा R592_STATUS_CED			(1 << 29)	/* INT: Command करोne (serial mode)*/
#घोषणा R592_STATUS_SFIFO_INPUT		(1 << 30)	/* Small fअगरo received data*/

#घोषणा R592_SFIFO_SIZE			32		/* total size of small fअगरo is 32 bytes */
#घोषणा R592_SFIFO_PACKET		8		/* packet size of small fअगरo */

/* IO control */
#घोषणा R592_IO				0x18
#घोषणा	R592_IO_16			(1 << 16)	/* Set by शेष, can be cleared */
#घोषणा	R592_IO_18			(1 << 18)	/* Set by शेष, can be cleared */
#घोषणा	R592_IO_SERIAL1			(1 << 20)	/* Set by शेष, can be cleared, (cleared on parallel) */
#घोषणा	R592_IO_22			(1 << 22)	/* Set by शेष, can be cleared */
#घोषणा R592_IO_सूचीECTION		(1 << 24)	/* TPC direction (1 ग_लिखो 0 पढ़ो) */
#घोषणा	R592_IO_26			(1 << 26)	/* Set by शेष, can be cleared */
#घोषणा	R592_IO_SERIAL2			(1 << 30)	/* Set by शेष, can be cleared (cleared on parallel), serial करोesn't work अगर unset */
#घोषणा R592_IO_RESET			(1 << 31)	/* Reset, sets शेषs*/


/* Turns hardware on/off */
#घोषणा R592_POWER			0x20		/* bits 0-7 ग_लिखोable */
#घोषणा R592_POWER_0			(1 << 0)	/* set on start, cleared on stop - must be set*/
#घोषणा R592_POWER_1			(1 << 1)	/* set on start, cleared on stop - must be set*/
#घोषणा R592_POWER_3			(1 << 3)	/* must be clear */
#घोषणा R592_POWER_20			(1 << 5)	/* set beक्रमe चयन to parallel */

/* IO mode*/
#घोषणा R592_IO_MODE			0x24
#घोषणा R592_IO_MODE_SERIAL		1
#घोषणा R592_IO_MODE_PARALLEL		3


/* IRQ,card detection,large fअगरo (first word irq status, second enable) */
/* IRQs are ACKed by clearing the bits */
#घोषणा R592_REG_MSC			0x28
#घोषणा R592_REG_MSC_PRSNT		(1 << 1)	/* card present (only status)*/
#घोषणा R592_REG_MSC_IRQ_INSERT		(1 << 8)	/* detect insert / card insered */
#घोषणा R592_REG_MSC_IRQ_REMOVE		(1 << 9)	/* detect removal / card हटाओd */
#घोषणा R592_REG_MSC_FIFO_EMPTY		(1 << 10)	/* fअगरo is empty */
#घोषणा R592_REG_MSC_FIFO_DMA_DONE	(1 << 11)	/* dma enable / dma करोne */

#घोषणा R592_REG_MSC_FIFO_USER_ORN	(1 << 12)	/* set अगर software पढ़ोs empty fअगरo (अगर R592_REG_MSC_FIFO_EMPTY is set) */
#घोषणा R592_REG_MSC_FIFO_MISMATH	(1 << 13)	/* set अगर amount of data in fअगरo करोesn't match amount in TPC */
#घोषणा R592_REG_MSC_FIFO_DMA_ERR	(1 << 14)	/* IO failure */
#घोषणा R592_REG_MSC_LED		(1 << 15)	/* clear to turn led off (only status)*/

#घोषणा DMA_IRQ_ACK_MASK \
	(R592_REG_MSC_FIFO_DMA_DONE | R592_REG_MSC_FIFO_DMA_ERR)

#घोषणा DMA_IRQ_EN_MASK (DMA_IRQ_ACK_MASK << 16)

#घोषणा IRQ_ALL_ACK_MASK 0x00007F00
#घोषणा IRQ_ALL_EN_MASK (IRQ_ALL_ACK_MASK << 16)

/* DMA address क्रम large FIFO पढ़ो/ग_लिखोs*/
#घोषणा R592_FIFO_DMA			0x2C

/* PIO access to large FIFO (512 bytes) (big endian)*/
#घोषणा R592_FIFO_PIO			0x30
#घोषणा R592_LFIFO_SIZE			512		/* large fअगरo size */


/* large FIFO DMA settings */
#घोषणा R592_FIFO_DMA_SETTINGS		0x34
#घोषणा R592_FIFO_DMA_SETTINGS_EN	(1 << 0)	/* DMA enabled */
#घोषणा R592_FIFO_DMA_SETTINGS_सूची	(1 << 1)	/* Dma direction (1 पढ़ो, 0 ग_लिखो) */
#घोषणा R592_FIFO_DMA_SETTINGS_CAP	(1 << 24)	/* Dma is aviable */

/* Maybe just an delay */
/* Bits 17..19 are just number */
/* bit 16 is set, then bit 20 is रुकोed */
/* समय to रुको is about 50 spins * 2 ^ (bits 17..19) */
/* seems to be possible just to ignore */
/* Probably debug रेजिस्टर */
#घोषणा R592_REG38			0x38
#घोषणा R592_REG38_CHANGE		(1 << 16)	/* Start bit */
#घोषणा R592_REG38_DONE			(1 << 20)	/* HW set this after the delay */
#घोषणा R592_REG38_SHIFT		17

/* Debug रेजिस्टर, written (0xABCDEF00) when error happens - not used*/
#घोषणा R592_REG_3C			0x3C

काष्ठा r592_device अणु
	काष्ठा pci_dev *pci_dev;
	काष्ठा memstick_host	*host;		/* host backpoपूर्णांकer */
	काष्ठा memstick_request *req;		/* current request */

	/* Registers, IRQ */
	व्योम __iomem *mmio;
	पूर्णांक irq;
	spinlock_t irq_lock;
	spinlock_t io_thपढ़ो_lock;
	काष्ठा समयr_list detect_समयr;

	काष्ठा task_काष्ठा *io_thपढ़ो;
	bool parallel_mode;

	DECLARE_KFIFO(pio_fअगरo, u8, माप(u32));

	/* DMA area */
	पूर्णांक dma_capable;
	पूर्णांक dma_error;
	काष्ठा completion dma_करोne;
	व्योम *dummy_dma_page;
	dma_addr_t dummy_dma_page_physical_address;

पूर्ण;

#घोषणा DRV_NAME "r592"


#घोषणा message(क्रमmat, ...) \
	prपूर्णांकk(KERN_INFO DRV_NAME ": " क्रमmat "\n", ## __VA_ARGS__)

#घोषणा __dbg(level, क्रमmat, ...) \
	करो अणु \
		अगर (debug >= level) \
			prपूर्णांकk(KERN_DEBUG DRV_NAME \
				": " क्रमmat "\n", ## __VA_ARGS__); \
	पूर्ण जबतक (0)


#घोषणा dbg(क्रमmat, ...)		__dbg(1, क्रमmat, ## __VA_ARGS__)
#घोषणा dbg_verbose(क्रमmat, ...)	__dbg(2, क्रमmat, ## __VA_ARGS__)
#घोषणा dbg_reg(क्रमmat, ...)		__dbg(3, क्रमmat, ## __VA_ARGS__)

#पूर्ण_अगर
