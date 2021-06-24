<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright तऊ 2009 - Maxim Levitsky
 * driver क्रम Ricoh xD पढ़ोers
 */

#समावेश <linux/pci.h>
#समावेश <linux/completion.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/mtd/rawnand.h>
#समावेश <linux/spinlock.h>


/* nand पूर्णांकerface + ecc
   byte ग_लिखो/पढ़ो करोes one cycle on nand data lines.
   dword ग_लिखो/पढ़ो करोes 4 cycles
   अगर R852_CTL_ECC_ACCESS is set in R852_CTL, then dword पढ़ो पढ़ोs
   results of ecc correction, अगर DMA पढ़ो was करोne beक्रमe.
   If ग_लिखो was करोne two dword पढ़ोs पढ़ो generated ecc checksums
*/
#घोषणा	R852_DATALINE		0x00

/* control रेजिस्टर */
#घोषणा R852_CTL		0x04
#घोषणा R852_CTL_COMMAND 	0x01	/* send command (#CLE)*/
#घोषणा R852_CTL_DATA		0x02	/* पढ़ो/ग_लिखो data (#ALE)*/
#घोषणा R852_CTL_ON		0x04	/* only seem to controls the hd led, */
					/* but has to be set on start...*/
#घोषणा R852_CTL_RESET		0x08	/* unknown, set only on start once*/
#घोषणा R852_CTL_CARDENABLE	0x10	/* probably (#CE) - always set*/
#घोषणा R852_CTL_ECC_ENABLE	0x20	/* enable ecc engine */
#घोषणा R852_CTL_ECC_ACCESS	0x40	/* पढ़ो/ग_लिखो ecc via reg #0*/
#घोषणा R852_CTL_WRITE		0x80	/* set when perक्रमming ग_लिखोs (#WP) */

/* card detection status */
#घोषणा R852_CARD_STA		0x05

#घोषणा R852_CARD_STA_CD	0x01	/* state of #CD line, same as 0x04 */
#घोषणा R852_CARD_STA_RO	0x02	/* card is पढ़ोonly */
#घोषणा R852_CARD_STA_PRESENT	0x04	/* card is present (#CD) */
#घोषणा R852_CARD_STA_ABSENT	0x08	/* card is असलent */
#घोषणा R852_CARD_STA_BUSY	0x80	/* card is busy - (#R/B) */

/* card detection irq status & enable*/
#घोषणा R852_CARD_IRQ_STA	0x06	/* IRQ status */
#घोषणा R852_CARD_IRQ_ENABLE	0x07	/* IRQ enable */

#घोषणा R852_CARD_IRQ_CD	0x01	/* fire when #CD lights, same as 0x04*/
#घोषणा R852_CARD_IRQ_REMOVE	0x04	/* detect card removal */
#घोषणा R852_CARD_IRQ_INSERT	0x08	/* detect card insert */
#घोषणा R852_CARD_IRQ_UNK1	0x10	/* unknown */
#घोषणा R852_CARD_IRQ_GENABLE	0x80	/* general enable */
#घोषणा R852_CARD_IRQ_MASK	0x1D



/* hardware enable */
#घोषणा R852_HW			0x08
#घोषणा R852_HW_ENABLED		0x01	/* hw enabled */
#घोषणा R852_HW_UNKNOWN		0x80


/* dma capabilities */
#घोषणा R852_DMA_CAP		0x09
#घोषणा R852_SMBIT		0x20	/* अगर set with bit #6 or bit #7, then */
					/* hw is smarपंचांगedia */
#घोषणा R852_DMA1		0x40	/* अगर set w/bit #7, dma is supported */
#घोषणा R852_DMA2		0x80	/* अगर set w/bit #6, dma is supported */


/* physical DMA address - 32 bit value*/
#घोषणा R852_DMA_ADDR		0x0C


/* dma settings */
#घोषणा R852_DMA_SETTINGS	0x10
#घोषणा R852_DMA_MEMORY		0x01	/* (memory <-> पूर्णांकernal hw buffer) */
#घोषणा R852_DMA_READ		0x02	/* 0 = ग_लिखो, 1 = पढ़ो */
#घोषणा R852_DMA_INTERNAL	0x04	/* (पूर्णांकernal hw buffer <-> card) */

/* dma IRQ status */
#घोषणा R852_DMA_IRQ_STA		0x14

/* dma IRQ enable */
#घोषणा R852_DMA_IRQ_ENABLE	0x18

#घोषणा R852_DMA_IRQ_MEMORY	0x01	/* (memory <-> पूर्णांकernal hw buffer) */
#घोषणा R852_DMA_IRQ_ERROR	0x02	/* error did happen */
#घोषणा R852_DMA_IRQ_INTERNAL	0x04	/* (पूर्णांकernal hw buffer <-> card) */
#घोषणा R852_DMA_IRQ_MASK	0x07	/* mask of all IRQ bits */


/* ECC syndrome क्रमmat - पढ़ो from reg #0 will वापस two copies of these क्रम
   each half of the page.
   first byte is error byte location, and second, bit location + flags */
#घोषणा R852_ECC_ERR_BIT_MSK	0x07	/* error bit location */
#घोषणा R852_ECC_CORRECT		0x10	/* no errors - (guessed) */
#घोषणा R852_ECC_CORRECTABLE	0x20	/* correctable error exist */
#घोषणा R852_ECC_FAIL		0x40	/* non correctable error detected */

#घोषणा R852_DMA_LEN		512

#घोषणा DMA_INTERNAL	0
#घोषणा DMA_MEMORY	1

काष्ठा r852_device अणु
	काष्ठा nand_controller		controller;
	व्योम __iomem *mmio;		/* mmio */
	काष्ठा nand_chip *chip;		/* nand chip backpoपूर्णांकer */
	काष्ठा pci_dev *pci_dev;	/* pci backpoपूर्णांकer */

	/* dma area */
	dma_addr_t phys_dma_addr;	/* bus address of buffer*/
	काष्ठा completion dma_करोne;	/* data transfer करोne */

	dma_addr_t phys_bounce_buffer;	/* bus address of bounce buffer */
	uपूर्णांक8_t *bounce_buffer;		/* भव address of bounce buffer */

	पूर्णांक dma_dir;			/* 1 = पढ़ो, 0 = ग_लिखो */
	पूर्णांक dma_stage;			/* 0 - idle, 1 - first step,
					   2 - second step */

	पूर्णांक dma_state;			/* 0 = पूर्णांकernal, 1 = memory */
	पूर्णांक dma_error;			/* dma errors */
	पूर्णांक dma_usable;			/* is it possible to use dma */

	/* card status area */
	काष्ठा delayed_work card_detect_work;
	काष्ठा workqueue_काष्ठा *card_workqueue;
	पूर्णांक card_रेजिस्टरed;		/* card रेजिस्टरed with mtd */
	पूर्णांक card_detected;		/* card detected in slot */
	पूर्णांक card_unstable;		/* whenever the card is inserted,
					   is not known yet */
	पूर्णांक पढ़ोonly;			/* card is पढ़ोonly */
	पूर्णांक sm;				/* Is card smarपंचांगedia */

	/* पूर्णांकerrupt handling */
	spinlock_t irqlock;		/* IRQ protecting lock */
	पूर्णांक irq;			/* irq num */
	/* misc */
	व्योम *पंचांगp_buffer;		/* temporary buffer */
	uपूर्णांक8_t ctlreg;			/* cached contents of control reg */
पूर्ण;

#घोषणा dbg(क्रमmat, ...) \
	अगर (debug) \
		pr_debug(क्रमmat "\n", ## __VA_ARGS__)

#घोषणा dbg_verbose(क्रमmat, ...) \
	अगर (debug > 1) \
		pr_debug(क्रमmat "\n", ## __VA_ARGS__)


#घोषणा message(क्रमmat, ...) \
	pr_info(क्रमmat "\n", ## __VA_ARGS__)
