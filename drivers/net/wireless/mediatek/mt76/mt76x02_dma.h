<शैली गुरु>
/* SPDX-License-Identअगरier: ISC */
/*
 * Copyright (C) 2018 Lorenzo Bianconi <lorenzo.bianconi83@gmail.com>
 */

#अगर_अघोषित __MT76x02_DMA_H
#घोषणा __MT76x02_DMA_H

#समावेश "mt76x02.h"
#समावेश "dma.h"

#घोषणा MT_TXD_INFO_LEN			GENMASK(15, 0)
#घोषणा MT_TXD_INFO_NEXT_VLD		BIT(16)
#घोषणा MT_TXD_INFO_TX_BURST		BIT(17)
#घोषणा MT_TXD_INFO_80211		BIT(19)
#घोषणा MT_TXD_INFO_TSO			BIT(20)
#घोषणा MT_TXD_INFO_CSO			BIT(21)
#घोषणा MT_TXD_INFO_WIV			BIT(24)
#घोषणा MT_TXD_INFO_QSEL		GENMASK(26, 25)
#घोषणा MT_TXD_INFO_DPORT		GENMASK(29, 27)
#घोषणा MT_TXD_INFO_TYPE		GENMASK(31, 30)

#घोषणा MT_RX_FCE_INFO_LEN		GENMASK(13, 0)
#घोषणा MT_RX_FCE_INFO_SELF_GEN		BIT(15)
#घोषणा MT_RX_FCE_INFO_CMD_SEQ		GENMASK(19, 16)
#घोषणा MT_RX_FCE_INFO_EVT_TYPE		GENMASK(23, 20)
#घोषणा MT_RX_FCE_INFO_PCIE_INTR	BIT(24)
#घोषणा MT_RX_FCE_INFO_QSEL		GENMASK(26, 25)
#घोषणा MT_RX_FCE_INFO_D_PORT		GENMASK(29, 27)
#घोषणा MT_RX_FCE_INFO_TYPE		GENMASK(31, 30)

/* MCU request message header  */
#घोषणा MT_MCU_MSG_LEN			GENMASK(15, 0)
#घोषणा MT_MCU_MSG_CMD_SEQ		GENMASK(19, 16)
#घोषणा MT_MCU_MSG_CMD_TYPE		GENMASK(26, 20)
#घोषणा MT_MCU_MSG_PORT			GENMASK(29, 27)
#घोषणा MT_MCU_MSG_TYPE			GENMASK(31, 30)
#घोषणा MT_MCU_MSG_TYPE_CMD		BIT(30)

#घोषणा MT_RX_HEADROOM			32
#घोषणा MT76X02_RX_RING_SIZE		256

क्रमागत dma_msg_port अणु
	WLAN_PORT,
	CPU_RX_PORT,
	CPU_TX_PORT,
	HOST_PORT,
	VIRTUAL_CPU_RX_PORT,
	VIRTUAL_CPU_TX_PORT,
	DISCARD,
पूर्ण;

अटल अंतरभूत bool
mt76x02_रुको_क्रम_wpdma(काष्ठा mt76_dev *dev, पूर्णांक समयout)
अणु
	वापस __mt76_poll(dev, MT_WPDMA_GLO_CFG,
			   MT_WPDMA_GLO_CFG_TX_DMA_BUSY |
			   MT_WPDMA_GLO_CFG_RX_DMA_BUSY,
			   0, समयout);
पूर्ण

पूर्णांक mt76x02_dma_init(काष्ठा mt76x02_dev *dev);
व्योम mt76x02_dma_disable(काष्ठा mt76x02_dev *dev);

#पूर्ण_अगर /* __MT76x02_DMA_H */
