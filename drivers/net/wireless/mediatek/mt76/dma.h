<शैली गुरु>
/* SPDX-License-Identअगरier: ISC */
/*
 * Copyright (C) 2016 Felix Fietkau <nbd@nbd.name>
 */
#अगर_अघोषित __MT76_DMA_H
#घोषणा __MT76_DMA_H

#घोषणा DMA_DUMMY_DATA			((व्योम *)~0)

#घोषणा MT_RING_SIZE			0x10

#घोषणा MT_DMA_CTL_SD_LEN1		GENMASK(13, 0)
#घोषणा MT_DMA_CTL_LAST_SEC1		BIT(14)
#घोषणा MT_DMA_CTL_BURST		BIT(15)
#घोषणा MT_DMA_CTL_SD_LEN0		GENMASK(29, 16)
#घोषणा MT_DMA_CTL_LAST_SEC0		BIT(30)
#घोषणा MT_DMA_CTL_DMA_DONE		BIT(31)

#घोषणा MT_DMA_HDR_LEN			4
#घोषणा MT_RX_INFO_LEN			4
#घोषणा MT_FCE_INFO_LEN			4
#घोषणा MT_RX_RXWI_LEN			32

काष्ठा mt76_desc अणु
	__le32 buf0;
	__le32 ctrl;
	__le32 buf1;
	__le32 info;
पूर्ण __packed __aligned(4);

क्रमागत mt76_qsel अणु
	MT_QSEL_MGMT,
	MT_QSEL_HCCA,
	MT_QSEL_EDCA,
	MT_QSEL_EDCA_2,
पूर्ण;

क्रमागत mt76_mcu_evt_type अणु
	EVT_CMD_DONE,
	EVT_CMD_ERROR,
	EVT_CMD_RETRY,
	EVT_EVENT_PWR_RSP,
	EVT_EVENT_WOW_RSP,
	EVT_EVENT_CARRIER_DETECT_RSP,
	EVT_EVENT_DFS_DETECT_RSP,
पूर्ण;

पूर्णांक mt76_dma_rx_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget);
व्योम mt76_dma_attach(काष्ठा mt76_dev *dev);
व्योम mt76_dma_cleanup(काष्ठा mt76_dev *dev);

#पूर्ण_अगर
