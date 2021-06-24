<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  cb710/cb710-mmc.h
 *
 *  Copyright by Michaध Mirosधaw, 2008-2009
 */
#अगर_अघोषित LINUX_CB710_MMC_H
#घोषणा LINUX_CB710_MMC_H

#समावेश <linux/cb710.h>

/* per-MMC-पढ़ोer काष्ठाure */
काष्ठा cb710_mmc_पढ़ोer अणु
	काष्ठा tasklet_काष्ठा finish_req_tasklet;
	काष्ठा mmc_request *mrq;
	spinlock_t irq_lock;
	अचिन्हित अक्षर last_घातer_mode;
पूर्ण;

/* some device काष्ठा walking */

अटल अंतरभूत काष्ठा mmc_host *cb710_slot_to_mmc(काष्ठा cb710_slot *slot)
अणु
	वापस platक्रमm_get_drvdata(&slot->pdev);
पूर्ण

अटल अंतरभूत काष्ठा cb710_slot *cb710_mmc_to_slot(काष्ठा mmc_host *mmc)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(mmc_dev(mmc));
	वापस cb710_pdev_to_slot(pdev);
पूर्ण

/* रेजिस्टरs (this might be all wrong ;) */

#घोषणा CB710_MMC_DATA_PORT		0x00

#घोषणा CB710_MMC_CONFIG_PORT		0x04
#घोषणा CB710_MMC_CONFIG0_PORT		0x04
#घोषणा CB710_MMC_CONFIG1_PORT		0x05
#घोषणा   CB710_MMC_C1_4BIT_DATA_BUS		0x40
#घोषणा CB710_MMC_CONFIG2_PORT		0x06
#घोषणा   CB710_MMC_C2_READ_PIO_SIZE_MASK	0x0F	/* N-1 */
#घोषणा CB710_MMC_CONFIG3_PORT		0x07

#घोषणा CB710_MMC_CONFIGB_PORT		0x08

#घोषणा CB710_MMC_IRQ_ENABLE_PORT	0x0C
#घोषणा   CB710_MMC_IE_TEST_MASK		0x00BF
#घोषणा   CB710_MMC_IE_CARD_INSERTION_STATUS	0x1000
#घोषणा   CB710_MMC_IE_IRQ_ENABLE		0x8000
#घोषणा   CB710_MMC_IE_CISTATUS_MASK		\
		(CB710_MMC_IE_CARD_INSERTION_STATUS|CB710_MMC_IE_IRQ_ENABLE)

#घोषणा CB710_MMC_STATUS_PORT		0x10
#घोषणा   CB710_MMC_STATUS_ERROR_EVENTS		0x60FF
#घोषणा CB710_MMC_STATUS0_PORT		0x10
#घोषणा   CB710_MMC_S0_FIFO_UNDERFLOW		0x40
#घोषणा CB710_MMC_STATUS1_PORT		0x11
#घोषणा   CB710_MMC_S1_COMMAND_SENT		0x01
#घोषणा   CB710_MMC_S1_DATA_TRANSFER_DONE	0x02
#घोषणा   CB710_MMC_S1_PIO_TRANSFER_DONE	0x04
#घोषणा   CB710_MMC_S1_CARD_CHANGED		0x10
#घोषणा   CB710_MMC_S1_RESET			0x20
#घोषणा CB710_MMC_STATUS2_PORT		0x12
#घोषणा   CB710_MMC_S2_FIFO_READY		0x01
#घोषणा   CB710_MMC_S2_FIFO_EMPTY		0x02
#घोषणा   CB710_MMC_S2_BUSY_10			0x10
#घोषणा   CB710_MMC_S2_BUSY_20			0x20
#घोषणा CB710_MMC_STATUS3_PORT		0x13
#घोषणा   CB710_MMC_S3_CARD_DETECTED		0x02
#घोषणा   CB710_MMC_S3_WRITE_PROTECTED		0x04

#घोषणा CB710_MMC_CMD_TYPE_PORT		0x14
#घोषणा   CB710_MMC_RSP_TYPE_MASK		0x0007
#घोषणा     CB710_MMC_RSP_R1			(0)
#घोषणा     CB710_MMC_RSP_136			(5)
#घोषणा     CB710_MMC_RSP_NO_CRC		(2)
#घोषणा   CB710_MMC_RSP_PRESENT_MASK		0x0018
#घोषणा     CB710_MMC_RSP_NONE			(0 << 3)
#घोषणा     CB710_MMC_RSP_PRESENT		(1 << 3)
#घोषणा     CB710_MMC_RSP_PRESENT_X		(2 << 3)
#घोषणा   CB710_MMC_CMD_TYPE_MASK		0x0060
#घोषणा     CB710_MMC_CMD_BC			(0 << 5)
#घोषणा     CB710_MMC_CMD_BCR			(1 << 5)
#घोषणा     CB710_MMC_CMD_AC			(2 << 5)
#घोषणा     CB710_MMC_CMD_ADTC			(3 << 5)
#घोषणा   CB710_MMC_DATA_READ			0x0080
#घोषणा   CB710_MMC_CMD_CODE_MASK		0x3F00
#घोषणा   CB710_MMC_CMD_CODE_SHIFT		8
#घोषणा   CB710_MMC_IS_APP_CMD			0x4000
#घोषणा   CB710_MMC_RSP_BUSY			0x8000

#घोषणा CB710_MMC_CMD_PARAM_PORT	0x18
#घोषणा CB710_MMC_TRANSFER_SIZE_PORT	0x1C
#घोषणा CB710_MMC_RESPONSE0_PORT	0x20
#घोषणा CB710_MMC_RESPONSE1_PORT	0x24
#घोषणा CB710_MMC_RESPONSE2_PORT	0x28
#घोषणा CB710_MMC_RESPONSE3_PORT	0x2C

#पूर्ण_अगर /* LINUX_CB710_MMC_H */
