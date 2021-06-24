<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/* Copyright (C) 2019 MediaTek Inc.
 *
 * Author: Ryder Lee <ryder.lee@mediatek.com>
 *         Roy Luo <royluo@google.com>
 *         Lorenzo Bianconi <lorenzo@kernel.org>
 *         Felix Fietkau <nbd@nbd.name>
 */

#समावेश "mt7615.h"
#समावेश "../dma.h"
#समावेश "mac.h"

अटल पूर्णांक
mt7622_init_tx_queues_multi(काष्ठा mt7615_dev *dev)
अणु
	अटल स्थिर u8 wmm_queue_map[] = अणु
		[IEEE80211_AC_BK] = MT7622_TXQ_AC0,
		[IEEE80211_AC_BE] = MT7622_TXQ_AC1,
		[IEEE80211_AC_VI] = MT7622_TXQ_AC2,
		[IEEE80211_AC_VO] = MT7622_TXQ_AC3,
	पूर्ण;
	पूर्णांक ret;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(wmm_queue_map); i++) अणु
		ret = mt76_init_tx_queue(&dev->mphy, i, wmm_queue_map[i],
					 MT7615_TX_RING_SIZE / 2,
					 MT_TX_RING_BASE);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = mt76_init_tx_queue(&dev->mphy, MT_TXQ_PSD, MT7622_TXQ_MGMT,
				 MT7615_TX_MGMT_RING_SIZE,
				 MT_TX_RING_BASE);
	अगर (ret)
		वापस ret;

	वापस mt76_init_mcu_queue(&dev->mt76, MT_MCUQ_WM, MT7622_TXQ_MCU,
				   MT7615_TX_MCU_RING_SIZE, MT_TX_RING_BASE);
पूर्ण

अटल पूर्णांक
mt7615_init_tx_queues(काष्ठा mt7615_dev *dev)
अणु
	पूर्णांक ret, i;

	ret = mt76_init_mcu_queue(&dev->mt76, MT_MCUQ_FWDL, MT7615_TXQ_FWDL,
				  MT7615_TX_FWDL_RING_SIZE, MT_TX_RING_BASE);
	अगर (ret)
		वापस ret;

	अगर (!is_mt7615(&dev->mt76))
		वापस mt7622_init_tx_queues_multi(dev);

	ret = mt76_init_tx_queue(&dev->mphy, 0, 0, MT7615_TX_RING_SIZE,
				 MT_TX_RING_BASE);
	अगर (ret)
		वापस ret;

	क्रम (i = 1; i <= MT_TXQ_PSD ; i++)
		dev->mphy.q_tx[i] = dev->mphy.q_tx[0];

	वापस mt76_init_mcu_queue(&dev->mt76, MT_MCUQ_WM, MT7615_TXQ_MCU,
				   MT7615_TX_MCU_RING_SIZE, MT_TX_RING_BASE);
पूर्ण

अटल पूर्णांक mt7615_poll_tx(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा mt7615_dev *dev;

	dev = container_of(napi, काष्ठा mt7615_dev, mt76.tx_napi);
	अगर (!mt76_connac_pm_ref(&dev->mphy, &dev->pm)) अणु
		napi_complete(napi);
		queue_work(dev->mt76.wq, &dev->pm.wake_work);
		वापस 0;
	पूर्ण

	mt76_queue_tx_cleanup(dev, dev->mt76.q_mcu[MT_MCUQ_WM], false);
	अगर (napi_complete(napi))
		mt7615_irq_enable(dev, mt7615_tx_mcu_पूर्णांक_mask(dev));

	mt76_connac_pm_unref(&dev->pm);

	वापस 0;
पूर्ण

अटल पूर्णांक mt7615_poll_rx(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा mt7615_dev *dev;
	पूर्णांक करोne;

	dev = container_of(napi->dev, काष्ठा mt7615_dev, mt76.napi_dev);

	अगर (!mt76_connac_pm_ref(&dev->mphy, &dev->pm)) अणु
		napi_complete(napi);
		queue_work(dev->mt76.wq, &dev->pm.wake_work);
		वापस 0;
	पूर्ण
	करोne = mt76_dma_rx_poll(napi, budget);
	mt76_connac_pm_unref(&dev->pm);

	वापस करोne;
पूर्ण

पूर्णांक mt7615_रुको_pdma_busy(काष्ठा mt7615_dev *dev)
अणु
	काष्ठा mt76_dev *mdev = &dev->mt76;

	अगर (!is_mt7663(mdev)) अणु
		u32 mask = MT_PDMA_TX_BUSY | MT_PDMA_RX_BUSY;
		u32 reg = mt7615_reg_map(dev, MT_PDMA_BUSY);

		अगर (!mt76_poll_msec(dev, reg, mask, 0, 1000)) अणु
			dev_err(mdev->dev, "PDMA engine busy\n");
			वापस -EIO;
		पूर्ण

		वापस 0;
	पूर्ण

	अगर (!mt76_poll_msec(dev, MT_PDMA_BUSY_STATUS,
			    MT_PDMA_TX_IDX_BUSY, 0, 1000)) अणु
		dev_err(mdev->dev, "PDMA engine tx busy\n");
		वापस -EIO;
	पूर्ण

	अगर (!mt76_poll_msec(dev, MT_PSE_PG_INFO,
			    MT_PSE_SRC_CNT, 0, 1000)) अणु
		dev_err(mdev->dev, "PSE engine busy\n");
		वापस -EIO;
	पूर्ण

	अगर (!mt76_poll_msec(dev, MT_PDMA_BUSY_STATUS,
			    MT_PDMA_BUSY_IDX, 0, 1000)) अणु
		dev_err(mdev->dev, "PDMA engine busy\n");
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम mt7622_dma_sched_init(काष्ठा mt7615_dev *dev)
अणु
	u32 reg = mt7615_reg_map(dev, MT_DMASHDL_BASE);
	पूर्णांक i;

	mt76_rmw(dev, reg + MT_DMASHDL_PKT_MAX_SIZE,
		 MT_DMASHDL_PKT_MAX_SIZE_PLE | MT_DMASHDL_PKT_MAX_SIZE_PSE,
		 FIELD_PREP(MT_DMASHDL_PKT_MAX_SIZE_PLE, 1) |
		 FIELD_PREP(MT_DMASHDL_PKT_MAX_SIZE_PSE, 8));

	क्रम (i = 0; i <= 5; i++)
		mt76_wr(dev, reg + MT_DMASHDL_GROUP_QUOTA(i),
			FIELD_PREP(MT_DMASHDL_GROUP_QUOTA_MIN, 0x10) |
			FIELD_PREP(MT_DMASHDL_GROUP_QUOTA_MAX, 0x800));

	mt76_wr(dev, reg + MT_DMASHDL_Q_MAP(0), 0x42104210);
	mt76_wr(dev, reg + MT_DMASHDL_Q_MAP(1), 0x42104210);
	mt76_wr(dev, reg + MT_DMASHDL_Q_MAP(2), 0x5);
	mt76_wr(dev, reg + MT_DMASHDL_Q_MAP(3), 0);

	mt76_wr(dev, reg + MT_DMASHDL_SCHED_SET0, 0x6012345f);
	mt76_wr(dev, reg + MT_DMASHDL_SCHED_SET1, 0xedcba987);
पूर्ण

अटल व्योम mt7663_dma_sched_init(काष्ठा mt7615_dev *dev)
अणु
	पूर्णांक i;

	mt76_rmw(dev, MT_DMA_SHDL(MT_DMASHDL_PKT_MAX_SIZE),
		 MT_DMASHDL_PKT_MAX_SIZE_PLE | MT_DMASHDL_PKT_MAX_SIZE_PSE,
		 FIELD_PREP(MT_DMASHDL_PKT_MAX_SIZE_PLE, 1) |
		 FIELD_PREP(MT_DMASHDL_PKT_MAX_SIZE_PSE, 8));

	/* enable refill control group 0, 1, 2, 4, 5 */
	mt76_wr(dev, MT_DMA_SHDL(MT_DMASHDL_REFILL), 0xffc80000);
	/* enable group 0, 1, 2, 4, 5, 15 */
	mt76_wr(dev, MT_DMA_SHDL(MT_DMASHDL_OPTIONAL), 0x70068037);

	/* each group min quota must larger then PLE_PKT_MAX_SIZE_NUM */
	क्रम (i = 0; i < 5; i++)
		mt76_wr(dev, MT_DMA_SHDL(MT_DMASHDL_GROUP_QUOTA(i)),
			FIELD_PREP(MT_DMASHDL_GROUP_QUOTA_MIN, 0x40) |
			FIELD_PREP(MT_DMASHDL_GROUP_QUOTA_MAX, 0x800));
	mt76_wr(dev, MT_DMA_SHDL(MT_DMASHDL_GROUP_QUOTA(5)),
		FIELD_PREP(MT_DMASHDL_GROUP_QUOTA_MIN, 0x40) |
		FIELD_PREP(MT_DMASHDL_GROUP_QUOTA_MAX, 0x40));
	mt76_wr(dev, MT_DMA_SHDL(MT_DMASHDL_GROUP_QUOTA(15)),
		FIELD_PREP(MT_DMASHDL_GROUP_QUOTA_MIN, 0x20) |
		FIELD_PREP(MT_DMASHDL_GROUP_QUOTA_MAX, 0x20));

	mt76_wr(dev, MT_DMA_SHDL(MT_DMASHDL_Q_MAP(0)), 0x42104210);
	mt76_wr(dev, MT_DMA_SHDL(MT_DMASHDL_Q_MAP(1)), 0x42104210);
	mt76_wr(dev, MT_DMA_SHDL(MT_DMASHDL_Q_MAP(2)), 0x00050005);
	mt76_wr(dev, MT_DMA_SHDL(MT_DMASHDL_Q_MAP(3)), 0);
	/* ALTX0 and ALTX1 QID mapping to group 5 */
	mt76_wr(dev, MT_DMA_SHDL(MT_DMASHDL_SCHED_SET0), 0x6012345f);
	mt76_wr(dev, MT_DMA_SHDL(MT_DMASHDL_SCHED_SET1), 0xedcba987);
पूर्ण

व्योम mt7615_dma_start(काष्ठा mt7615_dev *dev)
अणु
	/* start dma engine */
	mt76_set(dev, MT_WPDMA_GLO_CFG,
		 MT_WPDMA_GLO_CFG_TX_DMA_EN |
		 MT_WPDMA_GLO_CFG_RX_DMA_EN |
		 MT_WPDMA_GLO_CFG_TX_WRITEBACK_DONE);

	अगर (is_mt7622(&dev->mt76))
		mt7622_dma_sched_init(dev);

	अगर (is_mt7663(&dev->mt76)) अणु
		mt7663_dma_sched_init(dev);

		mt76_wr(dev, MT_MCU2HOST_INT_ENABLE, MT7663_MCU_CMD_ERROR_MASK);
	पूर्ण

पूर्ण

पूर्णांक mt7615_dma_init(काष्ठा mt7615_dev *dev)
अणु
	पूर्णांक rx_ring_size = MT7615_RX_RING_SIZE;
	पूर्णांक rx_buf_size = MT_RX_BUF_SIZE;
	u32 mask;
	पूर्णांक ret;

	/* Increase buffer size to receive large VHT MPDUs */
	अगर (dev->mphy.cap.has_5ghz)
		rx_buf_size *= 2;

	mt76_dma_attach(&dev->mt76);

	mt76_wr(dev, MT_WPDMA_GLO_CFG,
		MT_WPDMA_GLO_CFG_TX_WRITEBACK_DONE |
		MT_WPDMA_GLO_CFG_FIFO_LITTLE_ENDIAN |
		MT_WPDMA_GLO_CFG_OMIT_TX_INFO);

	mt76_rmw_field(dev, MT_WPDMA_GLO_CFG,
		       MT_WPDMA_GLO_CFG_TX_BT_SIZE_BIT0, 0x1);

	mt76_rmw_field(dev, MT_WPDMA_GLO_CFG,
		       MT_WPDMA_GLO_CFG_TX_BT_SIZE_BIT21, 0x1);

	mt76_rmw_field(dev, MT_WPDMA_GLO_CFG,
		       MT_WPDMA_GLO_CFG_DMA_BURST_SIZE, 0x3);

	mt76_rmw_field(dev, MT_WPDMA_GLO_CFG,
		       MT_WPDMA_GLO_CFG_MULTI_DMA_EN, 0x3);

	अगर (is_mt7615(&dev->mt76)) अणु
		mt76_set(dev, MT_WPDMA_GLO_CFG,
			 MT_WPDMA_GLO_CFG_FIRST_TOKEN_ONLY);

		mt76_wr(dev, MT_WPDMA_GLO_CFG1, 0x1);
		mt76_wr(dev, MT_WPDMA_TX_PRE_CFG, 0xf0000);
		mt76_wr(dev, MT_WPDMA_RX_PRE_CFG, 0xf7f0000);
		mt76_wr(dev, MT_WPDMA_ABT_CFG, 0x4000026);
		mt76_wr(dev, MT_WPDMA_ABT_CFG1, 0x18811881);
		mt76_set(dev, 0x7158, BIT(16));
		mt76_clear(dev, 0x7000, BIT(23));
	पूर्ण

	mt76_wr(dev, MT_WPDMA_RST_IDX, ~0);

	ret = mt7615_init_tx_queues(dev);
	अगर (ret)
		वापस ret;

	/* init rx queues */
	ret = mt76_queue_alloc(dev, &dev->mt76.q_rx[MT_RXQ_MCU], 1,
			       MT7615_RX_MCU_RING_SIZE, rx_buf_size,
			       MT_RX_RING_BASE);
	अगर (ret)
		वापस ret;

	अगर (!is_mt7615(&dev->mt76))
	    rx_ring_size /= 2;

	ret = mt76_queue_alloc(dev, &dev->mt76.q_rx[MT_RXQ_MAIN], 0,
			       rx_ring_size, rx_buf_size, MT_RX_RING_BASE);
	अगर (ret)
		वापस ret;

	mt76_wr(dev, MT_DELAY_INT_CFG, 0);

	ret = mt76_init_queues(dev, mt7615_poll_rx);
	अगर (ret < 0)
		वापस ret;

	netअगर_tx_napi_add(&dev->mt76.tx_napi_dev, &dev->mt76.tx_napi,
			  mt7615_poll_tx, NAPI_POLL_WEIGHT);
	napi_enable(&dev->mt76.tx_napi);

	mt76_poll(dev, MT_WPDMA_GLO_CFG,
		  MT_WPDMA_GLO_CFG_TX_DMA_BUSY |
		  MT_WPDMA_GLO_CFG_RX_DMA_BUSY, 0, 1000);

	/* enable पूर्णांकerrupts क्रम TX/RX rings */

	mask = MT_INT_RX_DONE_ALL | mt7615_tx_mcu_पूर्णांक_mask(dev);
	अगर (is_mt7663(&dev->mt76))
	    mask |= MT7663_INT_MCU_CMD;
	अन्यथा
	    mask |= MT_INT_MCU_CMD;

	mt7615_irq_enable(dev, mask);

	mt7615_dma_start(dev);

	वापस 0;
पूर्ण

व्योम mt7615_dma_cleanup(काष्ठा mt7615_dev *dev)
अणु
	mt76_clear(dev, MT_WPDMA_GLO_CFG,
		   MT_WPDMA_GLO_CFG_TX_DMA_EN |
		   MT_WPDMA_GLO_CFG_RX_DMA_EN);
	mt76_set(dev, MT_WPDMA_GLO_CFG, MT_WPDMA_GLO_CFG_SW_RESET);

	mt76_dma_cleanup(&dev->mt76);
पूर्ण
