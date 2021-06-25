<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/* Copyright (C) 2020 MediaTek Inc. */

#समावेश "mt7921.h"
#समावेश "../dma.h"
#समावेश "mac.h"

पूर्णांक mt7921_init_tx_queues(काष्ठा mt7921_phy *phy, पूर्णांक idx, पूर्णांक n_desc)
अणु
	पूर्णांक i, err;

	err = mt76_init_tx_queue(phy->mt76, 0, idx, n_desc, MT_TX_RING_BASE);
	अगर (err < 0)
		वापस err;

	क्रम (i = 0; i <= MT_TXQ_PSD; i++)
		phy->mt76->q_tx[i] = phy->mt76->q_tx[0];

	वापस 0;
पूर्ण

व्योम mt7921_queue_rx_skb(काष्ठा mt76_dev *mdev, क्रमागत mt76_rxq_id q,
			 काष्ठा sk_buff *skb)
अणु
	काष्ठा mt7921_dev *dev = container_of(mdev, काष्ठा mt7921_dev, mt76);
	__le32 *rxd = (__le32 *)skb->data;
	क्रमागत rx_pkt_type type;
	u16 flag;

	type = FIELD_GET(MT_RXD0_PKT_TYPE, le32_to_cpu(rxd[0]));
	flag = FIELD_GET(MT_RXD0_PKT_FLAG, le32_to_cpu(rxd[0]));

	अगर (type == PKT_TYPE_RX_EVENT && flag == 0x1)
		type = PKT_TYPE_NORMAL_MCU;

	चयन (type) अणु
	हाल PKT_TYPE_TXRX_NOTIFY:
		mt7921_mac_tx_मुक्त(dev, skb);
		अवरोध;
	हाल PKT_TYPE_RX_EVENT:
		mt7921_mcu_rx_event(dev, skb);
		अवरोध;
	हाल PKT_TYPE_NORMAL_MCU:
	हाल PKT_TYPE_NORMAL:
		अगर (!mt7921_mac_fill_rx(dev, skb)) अणु
			mt76_rx(&dev->mt76, q, skb);
			वापस;
		पूर्ण
		fallthrough;
	शेष:
		dev_kमुक्त_skb(skb);
		अवरोध;
	पूर्ण
पूर्ण

व्योम mt7921_tx_cleanup(काष्ठा mt7921_dev *dev)
अणु
	mt76_queue_tx_cleanup(dev, dev->mt76.q_mcu[MT_MCUQ_WM], false);
	mt76_queue_tx_cleanup(dev, dev->mt76.q_mcu[MT_MCUQ_WA], false);
पूर्ण

अटल पूर्णांक mt7921_poll_tx(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा mt7921_dev *dev;

	dev = container_of(napi, काष्ठा mt7921_dev, mt76.tx_napi);

	अगर (!mt76_connac_pm_ref(&dev->mphy, &dev->pm)) अणु
		napi_complete(napi);
		queue_work(dev->mt76.wq, &dev->pm.wake_work);
		वापस 0;
	पूर्ण

	mt7921_tx_cleanup(dev);
	अगर (napi_complete(napi))
		mt7921_irq_enable(dev, MT_INT_TX_DONE_ALL);
	mt76_connac_pm_unref(&dev->pm);

	वापस 0;
पूर्ण

अटल पूर्णांक mt7921_poll_rx(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा mt7921_dev *dev;
	पूर्णांक करोne;

	dev = container_of(napi->dev, काष्ठा mt7921_dev, mt76.napi_dev);

	अगर (!mt76_connac_pm_ref(&dev->mphy, &dev->pm)) अणु
		napi_complete(napi);
		queue_work(dev->mt76.wq, &dev->pm.wake_work);
		वापस 0;
	पूर्ण
	करोne = mt76_dma_rx_poll(napi, budget);
	mt76_connac_pm_unref(&dev->pm);

	वापस करोne;
पूर्ण

अटल व्योम mt7921_dma_prefetch(काष्ठा mt7921_dev *dev)
अणु
#घोषणा PREFETCH(base, depth)	((base) << 16 | (depth))

	mt76_wr(dev, MT_WFDMA0_RX_RING0_EXT_CTRL, PREFETCH(0x0, 0x4));
	mt76_wr(dev, MT_WFDMA0_RX_RING2_EXT_CTRL, PREFETCH(0x40, 0x4));
	mt76_wr(dev, MT_WFDMA0_RX_RING3_EXT_CTRL, PREFETCH(0x80, 0x4));
	mt76_wr(dev, MT_WFDMA0_RX_RING4_EXT_CTRL, PREFETCH(0xc0, 0x4));
	mt76_wr(dev, MT_WFDMA0_RX_RING5_EXT_CTRL, PREFETCH(0x100, 0x4));

	mt76_wr(dev, MT_WFDMA0_TX_RING0_EXT_CTRL, PREFETCH(0x140, 0x4));
	mt76_wr(dev, MT_WFDMA0_TX_RING1_EXT_CTRL, PREFETCH(0x180, 0x4));
	mt76_wr(dev, MT_WFDMA0_TX_RING2_EXT_CTRL, PREFETCH(0x1c0, 0x4));
	mt76_wr(dev, MT_WFDMA0_TX_RING3_EXT_CTRL, PREFETCH(0x200, 0x4));
	mt76_wr(dev, MT_WFDMA0_TX_RING4_EXT_CTRL, PREFETCH(0x240, 0x4));
	mt76_wr(dev, MT_WFDMA0_TX_RING5_EXT_CTRL, PREFETCH(0x280, 0x4));
	mt76_wr(dev, MT_WFDMA0_TX_RING6_EXT_CTRL, PREFETCH(0x2c0, 0x4));
	mt76_wr(dev, MT_WFDMA0_TX_RING16_EXT_CTRL, PREFETCH(0x340, 0x4));
	mt76_wr(dev, MT_WFDMA0_TX_RING17_EXT_CTRL, PREFETCH(0x380, 0x4));
पूर्ण

अटल u32 __mt7921_reg_addr(काष्ठा mt7921_dev *dev, u32 addr)
अणु
	अटल स्थिर काष्ठा अणु
		u32 phys;
		u32 mapped;
		u32 size;
	पूर्ण fixed_map[] = अणु
		अणु 0x00400000, 0x80000, 0x10000पूर्ण, /* WF_MCU_SYSRAM */
		अणु 0x00410000, 0x90000, 0x10000पूर्ण, /* WF_MCU_SYSRAM (configure रेजिस्टर) */
		अणु 0x40000000, 0x70000, 0x10000पूर्ण, /* WF_UMAC_SYSRAM */
		अणु 0x54000000, 0x02000, 0x1000 पूर्ण, /* WFDMA PCIE0 MCU DMA0 */
		अणु 0x55000000, 0x03000, 0x1000 पूर्ण, /* WFDMA PCIE0 MCU DMA1 */
		अणु 0x58000000, 0x06000, 0x1000 पूर्ण, /* WFDMA PCIE1 MCU DMA0 (MEM_DMA) */
		अणु 0x59000000, 0x07000, 0x1000 पूर्ण, /* WFDMA PCIE1 MCU DMA1 */
		अणु 0x7c000000, 0xf0000, 0x10000 पूर्ण, /* CONN_INFRA */
		अणु 0x7c020000, 0xd0000, 0x10000 पूर्ण, /* CONN_INFRA, WFDMA */
		अणु 0x7c060000, 0xe0000, 0x10000पूर्ण, /* CONN_INFRA, conn_host_csr_top */
		अणु 0x80020000, 0xb0000, 0x10000 पूर्ण, /* WF_TOP_MISC_OFF */
		अणु 0x81020000, 0xc0000, 0x10000 पूर्ण, /* WF_TOP_MISC_ON */
		अणु 0x820c0000, 0x08000, 0x4000 पूर्ण, /* WF_UMAC_TOP (PLE) */
		अणु 0x820c8000, 0x0c000, 0x2000 पूर्ण, /* WF_UMAC_TOP (PSE) */
		अणु 0x820cc000, 0x0e000, 0x2000 पूर्ण, /* WF_UMAC_TOP (PP) */
		अणु 0x820ce000, 0x21c00, 0x0200 पूर्ण, /* WF_LMAC_TOP (WF_SEC) */
		अणु 0x820cf000, 0x22000, 0x1000 पूर्ण, /* WF_LMAC_TOP (WF_PF) */
		अणु 0x820d0000, 0x30000, 0x10000 पूर्ण, /* WF_LMAC_TOP (WF_WTBLON) */
		अणु 0x820e0000, 0x20000, 0x0400 पूर्ण, /* WF_LMAC_TOP BN0 (WF_CFG) */
		अणु 0x820e1000, 0x20400, 0x0200 पूर्ण, /* WF_LMAC_TOP BN0 (WF_TRB) */
		अणु 0x820e2000, 0x20800, 0x0400 पूर्ण, /* WF_LMAC_TOP BN0 (WF_AGG) */
		अणु 0x820e3000, 0x20c00, 0x0400 पूर्ण, /* WF_LMAC_TOP BN0 (WF_ARB) */
		अणु 0x820e4000, 0x21000, 0x0400 पूर्ण, /* WF_LMAC_TOP BN0 (WF_TMAC) */
		अणु 0x820e5000, 0x21400, 0x0800 पूर्ण, /* WF_LMAC_TOP BN0 (WF_RMAC) */
		अणु 0x820e7000, 0x21e00, 0x0200 पूर्ण, /* WF_LMAC_TOP BN0 (WF_DMA) */
		अणु 0x820e9000, 0x23400, 0x0200 पूर्ण, /* WF_LMAC_TOP BN0 (WF_WTBLOFF) */
		अणु 0x820ea000, 0x24000, 0x0200 पूर्ण, /* WF_LMAC_TOP BN0 (WF_ETBF) */
		अणु 0x820eb000, 0x24200, 0x0400 पूर्ण, /* WF_LMAC_TOP BN0 (WF_LPON) */
		अणु 0x820ec000, 0x24600, 0x0200 पूर्ण, /* WF_LMAC_TOP BN0 (WF_INT) */
		अणु 0x820ed000, 0x24800, 0x0800 पूर्ण, /* WF_LMAC_TOP BN0 (WF_MIB) */
		अणु 0x820f0000, 0xa0000, 0x0400 पूर्ण, /* WF_LMAC_TOP BN1 (WF_CFG) */
		अणु 0x820f1000, 0xa0600, 0x0200 पूर्ण, /* WF_LMAC_TOP BN1 (WF_TRB) */
		अणु 0x820f2000, 0xa0800, 0x0400 पूर्ण, /* WF_LMAC_TOP BN1 (WF_AGG) */
		अणु 0x820f3000, 0xa0c00, 0x0400 पूर्ण, /* WF_LMAC_TOP BN1 (WF_ARB) */
		अणु 0x820f4000, 0xa1000, 0x0400 पूर्ण, /* WF_LMAC_TOP BN1 (WF_TMAC) */
		अणु 0x820f5000, 0xa1400, 0x0800 पूर्ण, /* WF_LMAC_TOP BN1 (WF_RMAC) */
		अणु 0x820f7000, 0xa1e00, 0x0200 पूर्ण, /* WF_LMAC_TOP BN1 (WF_DMA) */
		अणु 0x820f9000, 0xa3400, 0x0200 पूर्ण, /* WF_LMAC_TOP BN1 (WF_WTBLOFF) */
		अणु 0x820fa000, 0xa4000, 0x0200 पूर्ण, /* WF_LMAC_TOP BN1 (WF_ETBF) */
		अणु 0x820fb000, 0xa4200, 0x0400 पूर्ण, /* WF_LMAC_TOP BN1 (WF_LPON) */
		अणु 0x820fc000, 0xa4600, 0x0200 पूर्ण, /* WF_LMAC_TOP BN1 (WF_INT) */
		अणु 0x820fd000, 0xa4800, 0x0800 पूर्ण, /* WF_LMAC_TOP BN1 (WF_MIB) */
	पूर्ण;
	पूर्णांक i;

	अगर (addr < 0x100000)
		वापस addr;

	क्रम (i = 0; i < ARRAY_SIZE(fixed_map); i++) अणु
		u32 ofs;

		अगर (addr < fixed_map[i].phys)
			जारी;

		ofs = addr - fixed_map[i].phys;
		अगर (ofs > fixed_map[i].size)
			जारी;

		वापस fixed_map[i].mapped + ofs;
	पूर्ण

	अगर ((addr >= 0x18000000 && addr < 0x18c00000) ||
	    (addr >= 0x70000000 && addr < 0x78000000) ||
	    (addr >= 0x7c000000 && addr < 0x7c400000))
		वापस mt7921_reg_map_l1(dev, addr);

	dev_err(dev->mt76.dev, "Access currently unsupported address %08x\n",
		addr);

	वापस 0;
पूर्ण

अटल u32 mt7921_rr(काष्ठा mt76_dev *mdev, u32 offset)
अणु
	काष्ठा mt7921_dev *dev = container_of(mdev, काष्ठा mt7921_dev, mt76);
	u32 addr = __mt7921_reg_addr(dev, offset);

	वापस dev->bus_ops->rr(mdev, addr);
पूर्ण

अटल व्योम mt7921_wr(काष्ठा mt76_dev *mdev, u32 offset, u32 val)
अणु
	काष्ठा mt7921_dev *dev = container_of(mdev, काष्ठा mt7921_dev, mt76);
	u32 addr = __mt7921_reg_addr(dev, offset);

	dev->bus_ops->wr(mdev, addr, val);
पूर्ण

अटल u32 mt7921_rmw(काष्ठा mt76_dev *mdev, u32 offset, u32 mask, u32 val)
अणु
	काष्ठा mt7921_dev *dev = container_of(mdev, काष्ठा mt7921_dev, mt76);
	u32 addr = __mt7921_reg_addr(dev, offset);

	वापस dev->bus_ops->rmw(mdev, addr, mask, val);
पूर्ण

अटल पूर्णांक mt7921_dma_disable(काष्ठा mt7921_dev *dev, bool क्रमce)
अणु
	अगर (क्रमce) अणु
		/* reset */
		mt76_clear(dev, MT_WFDMA0_RST,
			   MT_WFDMA0_RST_DMASHDL_ALL_RST |
			   MT_WFDMA0_RST_LOGIC_RST);

		mt76_set(dev, MT_WFDMA0_RST,
			 MT_WFDMA0_RST_DMASHDL_ALL_RST |
			 MT_WFDMA0_RST_LOGIC_RST);
	पूर्ण

	/* disable dmashdl */
	mt76_clear(dev, MT_WFDMA0_GLO_CFG_EXT0,
		   MT_WFDMA0_CSR_TX_DMASHDL_ENABLE);
	mt76_set(dev, MT_DMASHDL_SW_CONTROL, MT_DMASHDL_DMASHDL_BYPASS);

	/* disable WFDMA0 */
	mt76_clear(dev, MT_WFDMA0_GLO_CFG,
		   MT_WFDMA0_GLO_CFG_TX_DMA_EN | MT_WFDMA0_GLO_CFG_RX_DMA_EN |
		   MT_WFDMA0_GLO_CFG_CSR_DISP_BASE_PTR_CHAIN_EN |
		   MT_WFDMA0_GLO_CFG_OMIT_TX_INFO |
		   MT_WFDMA0_GLO_CFG_OMIT_RX_INFO |
		   MT_WFDMA0_GLO_CFG_OMIT_RX_INFO_PFET2);

	अगर (!mt76_poll(dev, MT_WFDMA0_GLO_CFG,
		       MT_WFDMA0_GLO_CFG_TX_DMA_BUSY |
		       MT_WFDMA0_GLO_CFG_RX_DMA_BUSY, 0, 1000))
		वापस -ETIMEDOUT;

	वापस 0;
पूर्ण

अटल पूर्णांक mt7921_dma_enable(काष्ठा mt7921_dev *dev)
अणु
	/* configure perfetch settings */
	mt7921_dma_prefetch(dev);

	/* reset dma idx */
	mt76_wr(dev, MT_WFDMA0_RST_DTX_PTR, ~0);

	/* configure delay पूर्णांकerrupt */
	mt76_wr(dev, MT_WFDMA0_PRI_DLY_INT_CFG0, 0);

	mt76_set(dev, MT_WFDMA0_GLO_CFG,
		 MT_WFDMA0_GLO_CFG_TX_WB_DDONE |
		 MT_WFDMA0_GLO_CFG_FIFO_LITTLE_ENDIAN |
		 MT_WFDMA0_GLO_CFG_CLK_GAT_DIS |
		 MT_WFDMA0_GLO_CFG_OMIT_TX_INFO |
		 MT_WFDMA0_GLO_CFG_CSR_DISP_BASE_PTR_CHAIN_EN |
		 MT_WFDMA0_GLO_CFG_OMIT_RX_INFO_PFET2);

	mt76_set(dev, MT_WFDMA0_GLO_CFG,
		 MT_WFDMA0_GLO_CFG_TX_DMA_EN | MT_WFDMA0_GLO_CFG_RX_DMA_EN);

	mt76_set(dev, MT_WFDMA_DUMMY_CR, MT_WFDMA_NEED_REINIT);

	/* enable पूर्णांकerrupts क्रम TX/RX rings */
	mt7921_irq_enable(dev,
			  MT_INT_RX_DONE_ALL | MT_INT_TX_DONE_ALL |
			  MT_INT_MCU_CMD);
	mt76_set(dev, MT_MCU2HOST_SW_INT_ENA, MT_MCU_CMD_WAKE_RX_PCIE);

	वापस 0;
पूर्ण

अटल पूर्णांक mt7921_dma_reset(काष्ठा mt7921_dev *dev, bool क्रमce)
अणु
	पूर्णांक i, err;

	err = mt7921_dma_disable(dev, क्रमce);
	अगर (err)
		वापस err;

	/* reset hw queues */
	क्रम (i = 0; i < __MT_TXQ_MAX; i++)
		mt76_queue_reset(dev, dev->mphy.q_tx[i]);

	क्रम (i = 0; i < __MT_MCUQ_MAX; i++)
		mt76_queue_reset(dev, dev->mt76.q_mcu[i]);

	mt76_क्रम_each_q_rx(&dev->mt76, i)
		mt76_queue_reset(dev, &dev->mt76.q_rx[i]);

	mt76_tx_status_check(&dev->mt76, शून्य, true);

	वापस mt7921_dma_enable(dev);
पूर्ण

पूर्णांक mt7921_wfsys_reset(काष्ठा mt7921_dev *dev)
अणु
	mt76_set(dev, 0x70002600, BIT(0));
	msleep(200);
	mt76_clear(dev, 0x70002600, BIT(0));

	अगर (!__mt76_poll_msec(&dev->mt76, MT_WFSYS_SW_RST_B,
			      WFSYS_SW_INIT_DONE, WFSYS_SW_INIT_DONE, 500))
		वापस -ETIMEDOUT;

	वापस 0;
पूर्ण

पूर्णांक mt7921_wpdma_reset(काष्ठा mt7921_dev *dev, bool क्रमce)
अणु
	पूर्णांक i, err;

	/* clean up hw queues */
	क्रम (i = 0; i < ARRAY_SIZE(dev->mt76.phy.q_tx); i++)
		mt76_queue_tx_cleanup(dev, dev->mphy.q_tx[i], true);

	क्रम (i = 0; i < ARRAY_SIZE(dev->mt76.q_mcu); i++)
		mt76_queue_tx_cleanup(dev, dev->mt76.q_mcu[i], true);

	mt76_क्रम_each_q_rx(&dev->mt76, i)
		mt76_queue_rx_cleanup(dev, &dev->mt76.q_rx[i]);

	अगर (क्रमce) अणु
		err = mt7921_wfsys_reset(dev);
		अगर (err)
			वापस err;
	पूर्ण
	err = mt7921_dma_reset(dev, क्रमce);
	अगर (err)
		वापस err;

	mt76_क्रम_each_q_rx(&dev->mt76, i)
		mt76_queue_rx_reset(dev, i);

	वापस 0;
पूर्ण

पूर्णांक mt7921_wpdma_reinit_cond(काष्ठा mt7921_dev *dev)
अणु
	काष्ठा mt76_connac_pm *pm = &dev->pm;
	पूर्णांक err;

	/* check अगर the wpdma must be reinitialized */
	अगर (mt7921_dma_need_reinit(dev)) अणु
		/* disable पूर्णांकerrutpts */
		mt76_wr(dev, MT_WFDMA0_HOST_INT_ENA, 0);
		mt76_wr(dev, MT_PCIE_MAC_INT_ENABLE, 0x0);

		err = mt7921_wpdma_reset(dev, false);
		अगर (err) अणु
			dev_err(dev->mt76.dev, "wpdma reset failed\n");
			वापस err;
		पूर्ण

		/* enable पूर्णांकerrutpts */
		mt76_wr(dev, MT_PCIE_MAC_INT_ENABLE, 0xff);
		pm->stats.lp_wake++;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक mt7921_dma_init(काष्ठा mt7921_dev *dev)
अणु
	/* Increase buffer size to receive large VHT/HE MPDUs */
	काष्ठा mt76_bus_ops *bus_ops;
	पूर्णांक rx_buf_size = MT_RX_BUF_SIZE * 2;
	पूर्णांक ret;

	dev->bus_ops = dev->mt76.bus;
	bus_ops = devm_kmemdup(dev->mt76.dev, dev->bus_ops, माप(*bus_ops),
			       GFP_KERNEL);
	अगर (!bus_ops)
		वापस -ENOMEM;

	bus_ops->rr = mt7921_rr;
	bus_ops->wr = mt7921_wr;
	bus_ops->rmw = mt7921_rmw;
	dev->mt76.bus = bus_ops;

	mt76_dma_attach(&dev->mt76);

	ret = mt7921_dma_disable(dev, true);
	अगर (ret)
		वापस ret;

	/* init tx queue */
	ret = mt7921_init_tx_queues(&dev->phy, MT7921_TXQ_BAND0,
				    MT7921_TX_RING_SIZE);
	अगर (ret)
		वापस ret;

	mt76_wr(dev, MT_WFDMA0_TX_RING0_EXT_CTRL, 0x4);

	/* command to WM */
	ret = mt76_init_mcu_queue(&dev->mt76, MT_MCUQ_WM, MT7921_TXQ_MCU_WM,
				  MT7921_TX_MCU_RING_SIZE, MT_TX_RING_BASE);
	अगर (ret)
		वापस ret;

	/* firmware करोwnload */
	ret = mt76_init_mcu_queue(&dev->mt76, MT_MCUQ_FWDL, MT7921_TXQ_FWDL,
				  MT7921_TX_FWDL_RING_SIZE, MT_TX_RING_BASE);
	अगर (ret)
		वापस ret;

	/* event from WM beक्रमe firmware करोwnload */
	ret = mt76_queue_alloc(dev, &dev->mt76.q_rx[MT_RXQ_MCU],
			       MT7921_RXQ_MCU_WM,
			       MT7921_RX_MCU_RING_SIZE,
			       rx_buf_size, MT_RX_EVENT_RING_BASE);
	अगर (ret)
		वापस ret;

	/* Change mcu queue after firmware करोwnload */
	ret = mt76_queue_alloc(dev, &dev->mt76.q_rx[MT_RXQ_MCU_WA],
			       MT7921_RXQ_MCU_WM,
			       MT7921_RX_MCU_RING_SIZE,
			       rx_buf_size, MT_WFDMA0(0x540));
	अगर (ret)
		वापस ret;

	/* rx data */
	ret = mt76_queue_alloc(dev, &dev->mt76.q_rx[MT_RXQ_MAIN],
			       MT7921_RXQ_BAND0, MT7921_RX_RING_SIZE,
			       rx_buf_size, MT_RX_DATA_RING_BASE);
	अगर (ret)
		वापस ret;

	ret = mt76_init_queues(dev, mt7921_poll_rx);
	अगर (ret < 0)
		वापस ret;

	netअगर_tx_napi_add(&dev->mt76.tx_napi_dev, &dev->mt76.tx_napi,
			  mt7921_poll_tx, NAPI_POLL_WEIGHT);
	napi_enable(&dev->mt76.tx_napi);

	वापस mt7921_dma_enable(dev);
पूर्ण

व्योम mt7921_dma_cleanup(काष्ठा mt7921_dev *dev)
अणु
	/* disable */
	mt76_clear(dev, MT_WFDMA0_GLO_CFG,
		   MT_WFDMA0_GLO_CFG_TX_DMA_EN |
		   MT_WFDMA0_GLO_CFG_RX_DMA_EN |
		   MT_WFDMA0_GLO_CFG_CSR_DISP_BASE_PTR_CHAIN_EN |
		   MT_WFDMA0_GLO_CFG_OMIT_TX_INFO |
		   MT_WFDMA0_GLO_CFG_OMIT_RX_INFO |
		   MT_WFDMA0_GLO_CFG_OMIT_RX_INFO_PFET2);

	/* reset */
	mt76_clear(dev, MT_WFDMA0_RST,
		   MT_WFDMA0_RST_DMASHDL_ALL_RST |
		   MT_WFDMA0_RST_LOGIC_RST);

	mt76_set(dev, MT_WFDMA0_RST,
		 MT_WFDMA0_RST_DMASHDL_ALL_RST |
		 MT_WFDMA0_RST_LOGIC_RST);

	mt76_dma_cleanup(&dev->mt76);
पूर्ण
