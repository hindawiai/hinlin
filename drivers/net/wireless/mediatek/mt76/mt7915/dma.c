<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/* Copyright (C) 2020 MediaTek Inc. */

#समावेश "mt7915.h"
#समावेश "../dma.h"
#समावेश "mac.h"

पूर्णांक mt7915_init_tx_queues(काष्ठा mt7915_phy *phy, पूर्णांक idx, पूर्णांक n_desc)
अणु
	पूर्णांक i, err;

	err = mt76_init_tx_queue(phy->mt76, 0, idx, n_desc, MT_TX_RING_BASE);
	अगर (err < 0)
		वापस err;

	क्रम (i = 0; i <= MT_TXQ_PSD; i++)
		phy->mt76->q_tx[i] = phy->mt76->q_tx[0];

	वापस 0;
पूर्ण

व्योम mt7915_queue_rx_skb(काष्ठा mt76_dev *mdev, क्रमागत mt76_rxq_id q,
			 काष्ठा sk_buff *skb)
अणु
	काष्ठा mt7915_dev *dev = container_of(mdev, काष्ठा mt7915_dev, mt76);
	__le32 *rxd = (__le32 *)skb->data;
	क्रमागत rx_pkt_type type;

	type = FIELD_GET(MT_RXD0_PKT_TYPE, le32_to_cpu(rxd[0]));

	चयन (type) अणु
	हाल PKT_TYPE_TXRX_NOTIFY:
		mt7915_mac_tx_मुक्त(dev, skb);
		अवरोध;
	हाल PKT_TYPE_RX_EVENT:
		mt7915_mcu_rx_event(dev, skb);
		अवरोध;
#अगर_घोषित CONFIG_NL80211_TESTMODE
	हाल PKT_TYPE_TXRXV:
		mt7915_mac_fill_rx_vector(dev, skb);
		अवरोध;
#पूर्ण_अगर
	हाल PKT_TYPE_NORMAL:
		अगर (!mt7915_mac_fill_rx(dev, skb)) अणु
			mt76_rx(&dev->mt76, q, skb);
			वापस;
		पूर्ण
		fallthrough;
	शेष:
		dev_kमुक्त_skb(skb);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम
mt7915_tx_cleanup(काष्ठा mt7915_dev *dev)
अणु
	mt76_queue_tx_cleanup(dev, dev->mt76.q_mcu[MT_MCUQ_WM], false);
	mt76_queue_tx_cleanup(dev, dev->mt76.q_mcu[MT_MCUQ_WA], false);
पूर्ण

अटल पूर्णांक mt7915_poll_tx(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा mt7915_dev *dev;

	dev = container_of(napi, काष्ठा mt7915_dev, mt76.tx_napi);

	mt7915_tx_cleanup(dev);

	अगर (napi_complete_करोne(napi, 0))
		mt7915_irq_enable(dev, MT_INT_TX_DONE_MCU);

	वापस 0;
पूर्ण

अटल व्योम __mt7915_dma_prefetch(काष्ठा mt7915_dev *dev, u32 ofs)
अणु
#घोषणा PREFETCH(base, depth)	((base) << 16 | (depth))

	mt76_wr(dev, MT_WFDMA0_RX_RING0_EXT_CTRL + ofs, PREFETCH(0x0, 0x4));
	mt76_wr(dev, MT_WFDMA0_RX_RING1_EXT_CTRL + ofs, PREFETCH(0x40, 0x4));
	mt76_wr(dev, MT_WFDMA0_RX_RING2_EXT_CTRL + ofs, PREFETCH(0x80, 0x0));

	mt76_wr(dev, MT_WFDMA1_TX_RING0_EXT_CTRL + ofs, PREFETCH(0x80, 0x4));
	mt76_wr(dev, MT_WFDMA1_TX_RING1_EXT_CTRL + ofs, PREFETCH(0xc0, 0x4));
	mt76_wr(dev, MT_WFDMA1_TX_RING2_EXT_CTRL + ofs, PREFETCH(0x100, 0x4));
	mt76_wr(dev, MT_WFDMA1_TX_RING3_EXT_CTRL + ofs, PREFETCH(0x140, 0x4));
	mt76_wr(dev, MT_WFDMA1_TX_RING4_EXT_CTRL + ofs, PREFETCH(0x180, 0x4));
	mt76_wr(dev, MT_WFDMA1_TX_RING5_EXT_CTRL + ofs, PREFETCH(0x1c0, 0x4));
	mt76_wr(dev, MT_WFDMA1_TX_RING6_EXT_CTRL + ofs, PREFETCH(0x200, 0x4));
	mt76_wr(dev, MT_WFDMA1_TX_RING7_EXT_CTRL + ofs, PREFETCH(0x240, 0x4));

	mt76_wr(dev, MT_WFDMA1_TX_RING16_EXT_CTRL + ofs, PREFETCH(0x280, 0x4));
	mt76_wr(dev, MT_WFDMA1_TX_RING17_EXT_CTRL + ofs, PREFETCH(0x2c0, 0x4));
	mt76_wr(dev, MT_WFDMA1_TX_RING18_EXT_CTRL + ofs, PREFETCH(0x300, 0x4));
	mt76_wr(dev, MT_WFDMA1_TX_RING19_EXT_CTRL + ofs, PREFETCH(0x340, 0x4));
	mt76_wr(dev, MT_WFDMA1_TX_RING20_EXT_CTRL + ofs, PREFETCH(0x380, 0x4));
	mt76_wr(dev, MT_WFDMA1_TX_RING21_EXT_CTRL + ofs, PREFETCH(0x3c0, 0x0));

	mt76_wr(dev, MT_WFDMA1_RX_RING0_EXT_CTRL + ofs, PREFETCH(0x3c0, 0x4));
	mt76_wr(dev, MT_WFDMA1_RX_RING1_EXT_CTRL + ofs, PREFETCH(0x400, 0x4));
	mt76_wr(dev, MT_WFDMA1_RX_RING2_EXT_CTRL + ofs, PREFETCH(0x440, 0x4));
	mt76_wr(dev, MT_WFDMA1_RX_RING3_EXT_CTRL + ofs, PREFETCH(0x480, 0x0));
पूर्ण

व्योम mt7915_dma_prefetch(काष्ठा mt7915_dev *dev)
अणु
	__mt7915_dma_prefetch(dev, 0);
	अगर (dev->hअगर2)
		__mt7915_dma_prefetch(dev, MT_WFDMA1_PCIE1_BASE - MT_WFDMA1_BASE);
पूर्ण

पूर्णांक mt7915_dma_init(काष्ठा mt7915_dev *dev)
अणु
	/* Increase buffer size to receive large VHT/HE MPDUs */
	पूर्णांक rx_buf_size = MT_RX_BUF_SIZE * 2;
	u32 hअगर1_ofs = 0;
	पूर्णांक ret;

	mt76_dma_attach(&dev->mt76);

	अगर (dev->hअगर2)
		hअगर1_ofs = MT_WFDMA1_PCIE1_BASE - MT_WFDMA1_BASE;

	/* configure global setting */
	mt76_set(dev, MT_WFDMA1_GLO_CFG,
		 MT_WFDMA1_GLO_CFG_OMIT_TX_INFO |
		 MT_WFDMA1_GLO_CFG_OMIT_RX_INFO);

	/* reset dma idx */
	mt76_wr(dev, MT_WFDMA0_RST_DTX_PTR, ~0);
	mt76_wr(dev, MT_WFDMA1_RST_DTX_PTR, ~0);

	/* configure delay पूर्णांकerrupt */
	mt76_wr(dev, MT_WFDMA0_PRI_DLY_INT_CFG0, 0);
	mt76_wr(dev, MT_WFDMA1_PRI_DLY_INT_CFG0, 0);

	अगर (dev->hअगर2) अणु
		mt76_set(dev, MT_WFDMA1_GLO_CFG + hअगर1_ofs,
			 MT_WFDMA1_GLO_CFG_OMIT_TX_INFO |
			 MT_WFDMA1_GLO_CFG_OMIT_RX_INFO);

		mt76_wr(dev, MT_WFDMA0_RST_DTX_PTR + hअगर1_ofs, ~0);
		mt76_wr(dev, MT_WFDMA1_RST_DTX_PTR + hअगर1_ofs, ~0);

		mt76_wr(dev, MT_WFDMA0_PRI_DLY_INT_CFG0 + hअगर1_ofs, 0);
		mt76_wr(dev, MT_WFDMA1_PRI_DLY_INT_CFG0 + hअगर1_ofs, 0);
	पूर्ण

	/* configure perfetch settings */
	mt7915_dma_prefetch(dev);

	/* init tx queue */
	ret = mt7915_init_tx_queues(&dev->phy, MT7915_TXQ_BAND0,
				    MT7915_TX_RING_SIZE);
	अगर (ret)
		वापस ret;

	/* command to WM */
	ret = mt76_init_mcu_queue(&dev->mt76, MT_MCUQ_WM, MT7915_TXQ_MCU_WM,
				  MT7915_TX_MCU_RING_SIZE, MT_TX_RING_BASE);
	अगर (ret)
		वापस ret;

	/* command to WA */
	ret = mt76_init_mcu_queue(&dev->mt76, MT_MCUQ_WA, MT7915_TXQ_MCU_WA,
				  MT7915_TX_MCU_RING_SIZE, MT_TX_RING_BASE);
	अगर (ret)
		वापस ret;

	/* firmware करोwnload */
	ret = mt76_init_mcu_queue(&dev->mt76, MT_MCUQ_FWDL, MT7915_TXQ_FWDL,
				  MT7915_TX_FWDL_RING_SIZE, MT_TX_RING_BASE);
	अगर (ret)
		वापस ret;

	/* event from WM */
	ret = mt76_queue_alloc(dev, &dev->mt76.q_rx[MT_RXQ_MCU],
			       MT7915_RXQ_MCU_WM, MT7915_RX_MCU_RING_SIZE,
			       rx_buf_size, MT_RX_EVENT_RING_BASE);
	अगर (ret)
		वापस ret;

	/* event from WA */
	ret = mt76_queue_alloc(dev, &dev->mt76.q_rx[MT_RXQ_MCU_WA],
			       MT7915_RXQ_MCU_WA, MT7915_RX_MCU_RING_SIZE,
			       rx_buf_size, MT_RX_EVENT_RING_BASE);
	अगर (ret)
		वापस ret;

	/* rx data queue */
	ret = mt76_queue_alloc(dev, &dev->mt76.q_rx[MT_RXQ_MAIN],
			       MT7915_RXQ_BAND0, MT7915_RX_RING_SIZE,
			       rx_buf_size, MT_RX_DATA_RING_BASE);
	अगर (ret)
		वापस ret;

	अगर (dev->dbdc_support) अणु
		ret = mt76_queue_alloc(dev, &dev->mt76.q_rx[MT_RXQ_EXT],
				       MT7915_RXQ_BAND1, MT7915_RX_RING_SIZE,
				       rx_buf_size,
				       MT_RX_DATA_RING_BASE + hअगर1_ofs);
		अगर (ret)
			वापस ret;

		/* event from WA */
		ret = mt76_queue_alloc(dev, &dev->mt76.q_rx[MT_RXQ_EXT_WA],
				       MT7915_RXQ_MCU_WA_EXT,
				       MT7915_RX_MCU_RING_SIZE,
				       rx_buf_size,
				       MT_RX_EVENT_RING_BASE + hअगर1_ofs);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = mt76_init_queues(dev, mt76_dma_rx_poll);
	अगर (ret < 0)
		वापस ret;

	netअगर_tx_napi_add(&dev->mt76.tx_napi_dev, &dev->mt76.tx_napi,
			  mt7915_poll_tx, NAPI_POLL_WEIGHT);
	napi_enable(&dev->mt76.tx_napi);

	/* hअगर रुको WFDMA idle */
	mt76_set(dev, MT_WFDMA0_BUSY_ENA,
		 MT_WFDMA0_BUSY_ENA_TX_FIFO0 |
		 MT_WFDMA0_BUSY_ENA_TX_FIFO1 |
		 MT_WFDMA0_BUSY_ENA_RX_FIFO);

	mt76_set(dev, MT_WFDMA1_BUSY_ENA,
		 MT_WFDMA1_BUSY_ENA_TX_FIFO0 |
		 MT_WFDMA1_BUSY_ENA_TX_FIFO1 |
		 MT_WFDMA1_BUSY_ENA_RX_FIFO);

	mt76_set(dev, MT_WFDMA0_PCIE1_BUSY_ENA,
		 MT_WFDMA0_PCIE1_BUSY_ENA_TX_FIFO0 |
		 MT_WFDMA0_PCIE1_BUSY_ENA_TX_FIFO1 |
		 MT_WFDMA0_PCIE1_BUSY_ENA_RX_FIFO);

	mt76_set(dev, MT_WFDMA1_PCIE1_BUSY_ENA,
		 MT_WFDMA1_PCIE1_BUSY_ENA_TX_FIFO0 |
		 MT_WFDMA1_PCIE1_BUSY_ENA_TX_FIFO1 |
		 MT_WFDMA1_PCIE1_BUSY_ENA_RX_FIFO);

	mt76_poll(dev, MT_WFDMA_EXT_CSR_HIF_MISC,
		  MT_WFDMA_EXT_CSR_HIF_MISC_BUSY, 0, 1000);

	/* set WFDMA Tx/Rx */
	mt76_set(dev, MT_WFDMA0_GLO_CFG,
		 MT_WFDMA0_GLO_CFG_TX_DMA_EN | MT_WFDMA0_GLO_CFG_RX_DMA_EN);
	mt76_set(dev, MT_WFDMA1_GLO_CFG,
		 MT_WFDMA1_GLO_CFG_TX_DMA_EN | MT_WFDMA1_GLO_CFG_RX_DMA_EN);

	अगर (dev->hअगर2) अणु
		mt76_set(dev, MT_WFDMA0_GLO_CFG + hअगर1_ofs,
			 (MT_WFDMA0_GLO_CFG_TX_DMA_EN |
			  MT_WFDMA0_GLO_CFG_RX_DMA_EN));
		mt76_set(dev, MT_WFDMA1_GLO_CFG + hअगर1_ofs,
			 (MT_WFDMA1_GLO_CFG_TX_DMA_EN |
			  MT_WFDMA1_GLO_CFG_RX_DMA_EN));
		mt76_set(dev, MT_WFDMA_HOST_CONFIG,
			 MT_WFDMA_HOST_CONFIG_PDMA_BAND);
	पूर्ण

	/* enable पूर्णांकerrupts क्रम TX/RX rings */
	mt7915_irq_enable(dev, MT_INT_RX_DONE_ALL | MT_INT_TX_DONE_MCU |
			  MT_INT_MCU_CMD);

	वापस 0;
पूर्ण

व्योम mt7915_dma_cleanup(काष्ठा mt7915_dev *dev)
अणु
	/* disable */
	mt76_clear(dev, MT_WFDMA0_GLO_CFG,
		   MT_WFDMA0_GLO_CFG_TX_DMA_EN |
		   MT_WFDMA0_GLO_CFG_RX_DMA_EN);
	mt76_clear(dev, MT_WFDMA1_GLO_CFG,
		   MT_WFDMA1_GLO_CFG_TX_DMA_EN |
		   MT_WFDMA1_GLO_CFG_RX_DMA_EN);

	/* reset */
	mt76_clear(dev, MT_WFDMA1_RST,
		   MT_WFDMA1_RST_DMASHDL_ALL_RST |
		   MT_WFDMA1_RST_LOGIC_RST);

	mt76_set(dev, MT_WFDMA1_RST,
		 MT_WFDMA1_RST_DMASHDL_ALL_RST |
		 MT_WFDMA1_RST_LOGIC_RST);

	mt76_clear(dev, MT_WFDMA0_RST,
		   MT_WFDMA0_RST_DMASHDL_ALL_RST |
		   MT_WFDMA0_RST_LOGIC_RST);

	mt76_set(dev, MT_WFDMA0_RST,
		 MT_WFDMA0_RST_DMASHDL_ALL_RST |
		 MT_WFDMA0_RST_LOGIC_RST);

	mt76_dma_cleanup(&dev->mt76);
पूर्ण
