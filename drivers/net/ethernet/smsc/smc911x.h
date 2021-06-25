<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*------------------------------------------------------------------------
 . smc911x.h - macros क्रम SMSC's LAN911अणु5,6,7,8पूर्ण single-chip Ethernet device.
 .
 . Copyright (C) 2005 Sensoria Corp.
 . Derived from the unअगरied SMC91x driver by Nicolas Pitre
 .
 .
 . Inक्रमmation contained in this file was obtained from the LAN9118
 . manual from SMC.  To get a copy, अगर you really want one, you can find
 . inक्रमmation under www.smsc.com.
 .
 . Authors
 .	 Dustin McIntire		 <dustin@sensoria.com>
 .
 ---------------------------------------------------------------------------*/
#अगर_अघोषित _SMC911X_H_
#घोषणा _SMC911X_H_

#समावेश <linux/smc911x.h>
/*
 * Use the DMA feature on PXA chips
 */
#अगर_घोषित CONFIG_ARCH_PXA
  #घोषणा SMC_USE_PXA_DMA	1
  #घोषणा SMC_USE_16BIT		0
  #घोषणा SMC_USE_32BIT		1
  #घोषणा SMC_IRQ_SENSE		IRQF_TRIGGER_FALLING
#या_अगर defined(CONFIG_SH_MAGIC_PANEL_R2)
  #घोषणा SMC_USE_16BIT		0
  #घोषणा SMC_USE_32BIT		1
  #घोषणा SMC_IRQ_SENSE		IRQF_TRIGGER_LOW
#या_अगर defined(CONFIG_ARCH_OMAP3)
  #घोषणा SMC_USE_16BIT		0
  #घोषणा SMC_USE_32BIT		1
  #घोषणा SMC_IRQ_SENSE		IRQF_TRIGGER_LOW
  #घोषणा SMC_MEM_RESERVED	1
#या_अगर defined(CONFIG_ARCH_OMAP2)
  #घोषणा SMC_USE_16BIT		0
  #घोषणा SMC_USE_32BIT		1
  #घोषणा SMC_IRQ_SENSE		IRQF_TRIGGER_LOW
  #घोषणा SMC_MEM_RESERVED	1
#अन्यथा
/*
 * Default configuration
 */

#घोषणा SMC_DYNAMIC_BUS_CONFIG
#पूर्ण_अगर

#अगर_घोषित SMC_USE_PXA_DMA
#घोषणा SMC_USE_DMA
#पूर्ण_अगर

/* store this inक्रमmation क्रम the driver.. */
काष्ठा smc911x_local अणु
	/*
	 * If I have to रुको until the DMA is finished and पढ़ोy to reload a
	 * packet, I will store the skbuff here. Then, the DMA will send it
	 * out and मुक्त it.
	 */
	काष्ठा sk_buff *pending_tx_skb;

	/* version/revision of the SMC911x chip */
	u16 version;
	u16 revision;

	/* FIFO sizes */
	पूर्णांक tx_fअगरo_kb;
	पूर्णांक tx_fअगरo_size;
	पूर्णांक rx_fअगरo_size;
	पूर्णांक afc_cfg;

	/* Contains the current active receive/phy mode */
	पूर्णांक ctl_rfduplx;
	पूर्णांक ctl_rspeed;

	u32 msg_enable;
	u32 phy_type;
	काष्ठा mii_अगर_info mii;

	/* work queue */
	काष्ठा work_काष्ठा phy_configure;

	पूर्णांक tx_throttle;
	spinlock_t lock;

	काष्ठा net_device *netdev;

#अगर_घोषित SMC_USE_DMA
	/* DMA needs the physical address of the chip */
	u_दीर्घ physaddr;
	काष्ठा dma_chan *rxdma;
	काष्ठा dma_chan *txdma;
	पूर्णांक rxdma_active;
	पूर्णांक txdma_active;
	काष्ठा sk_buff *current_rx_skb;
	काष्ठा sk_buff *current_tx_skb;
	काष्ठा device *dev;
#पूर्ण_अगर
	व्योम __iomem *base;
#अगर_घोषित SMC_DYNAMIC_BUS_CONFIG
	काष्ठा smc911x_platdata cfg;
#पूर्ण_अगर
पूर्ण;

/*
 * Define the bus width specअगरic IO macros
 */

#अगर_घोषित SMC_DYNAMIC_BUS_CONFIG
अटल अंतरभूत अचिन्हित पूर्णांक SMC_inl(काष्ठा smc911x_local *lp, पूर्णांक reg)
अणु
	व्योम __iomem *ioaddr = lp->base + reg;

	अगर (lp->cfg.flags & SMC911X_USE_32BIT)
		वापस पढ़ोl(ioaddr);

	अगर (lp->cfg.flags & SMC911X_USE_16BIT)
		वापस पढ़ोw(ioaddr) | (पढ़ोw(ioaddr + 2) << 16);

	BUG();
पूर्ण

अटल अंतरभूत व्योम SMC_outl(अचिन्हित पूर्णांक value, काष्ठा smc911x_local *lp,
			    पूर्णांक reg)
अणु
	व्योम __iomem *ioaddr = lp->base + reg;

	अगर (lp->cfg.flags & SMC911X_USE_32BIT) अणु
		ग_लिखोl(value, ioaddr);
		वापस;
	पूर्ण

	अगर (lp->cfg.flags & SMC911X_USE_16BIT) अणु
		ग_लिखोw(value & 0xffff, ioaddr);
		ग_लिखोw(value >> 16, ioaddr + 2);
		वापस;
	पूर्ण

	BUG();
पूर्ण

अटल अंतरभूत व्योम SMC_insl(काष्ठा smc911x_local *lp, पूर्णांक reg,
			      व्योम *addr, अचिन्हित पूर्णांक count)
अणु
	व्योम __iomem *ioaddr = lp->base + reg;

	अगर (lp->cfg.flags & SMC911X_USE_32BIT) अणु
		ioपढ़ो32_rep(ioaddr, addr, count);
		वापस;
	पूर्ण

	अगर (lp->cfg.flags & SMC911X_USE_16BIT) अणु
		ioपढ़ो16_rep(ioaddr, addr, count * 2);
		वापस;
	पूर्ण

	BUG();
पूर्ण

अटल अंतरभूत व्योम SMC_outsl(काष्ठा smc911x_local *lp, पूर्णांक reg,
			     व्योम *addr, अचिन्हित पूर्णांक count)
अणु
	व्योम __iomem *ioaddr = lp->base + reg;

	अगर (lp->cfg.flags & SMC911X_USE_32BIT) अणु
		ioग_लिखो32_rep(ioaddr, addr, count);
		वापस;
	पूर्ण

	अगर (lp->cfg.flags & SMC911X_USE_16BIT) अणु
		ioग_लिखो16_rep(ioaddr, addr, count * 2);
		वापस;
	पूर्ण

	BUG();
पूर्ण
#अन्यथा
#अगर	SMC_USE_16BIT
#घोषणा SMC_inl(lp, r)		 ((पढ़ोw((lp)->base + (r)) & 0xFFFF) + (पढ़ोw((lp)->base + (r) + 2) << 16))
#घोषणा SMC_outl(v, lp, r) 			 \
	करोअणु					 \
		 ग_लिखोw(v & 0xFFFF, (lp)->base + (r));	 \
		 ग_लिखोw(v >> 16, (lp)->base + (r) + 2); \
	 पूर्ण जबतक (0)
#घोषणा SMC_insl(lp, r, p, l)	 ioपढ़ो16_rep((लघु*)((lp)->base + (r)), p, l*2)
#घोषणा SMC_outsl(lp, r, p, l)	 ioग_लिखो16_rep((लघु*)((lp)->base + (r)), p, l*2)

#या_अगर	SMC_USE_32BIT
#घोषणा SMC_inl(lp, r)		 पढ़ोl((lp)->base + (r))
#घोषणा SMC_outl(v, lp, r)	 ग_लिखोl(v, (lp)->base + (r))
#घोषणा SMC_insl(lp, r, p, l)	 ioपढ़ो32_rep((पूर्णांक*)((lp)->base + (r)), p, l)
#घोषणा SMC_outsl(lp, r, p, l)	 ioग_लिखो32_rep((पूर्णांक*)((lp)->base + (r)), p, l)

#पूर्ण_अगर /* SMC_USE_16BIT */
#पूर्ण_अगर /* SMC_DYNAMIC_BUS_CONFIG */


#अगर_घोषित SMC_USE_PXA_DMA

/*
 * Use a DMA क्रम RX and TX packets.
 */
#समावेश <linux/dma-mapping.h>

अटल dma_addr_t rx_dmabuf, tx_dmabuf;
अटल पूर्णांक rx_dmalen, tx_dmalen;
अटल व्योम smc911x_rx_dma_irq(व्योम *data);
अटल व्योम smc911x_tx_dma_irq(व्योम *data);

#अगर_घोषित SMC_insl
#अघोषित SMC_insl
#घोषणा SMC_insl(lp, r, p, l) \
	smc_pxa_dma_insl(lp, lp->physaddr, r, lp->rxdma, p, l)

अटल अंतरभूत व्योम
smc_pxa_dma_insl(काष्ठा smc911x_local *lp, u_दीर्घ physaddr,
		पूर्णांक reg, काष्ठा dma_chan *dma, u_अक्षर *buf, पूर्णांक len)
अणु
	काष्ठा dma_async_tx_descriptor *tx;

	/* 64 bit alignment is required क्रम memory to memory DMA */
	अगर ((दीर्घ)buf & 4) अणु
		*((u32 *)buf) = SMC_inl(lp, reg);
		buf += 4;
		len--;
	पूर्ण

	len *= 4;
	rx_dmabuf = dma_map_single(lp->dev, buf, len, DMA_FROM_DEVICE);
	rx_dmalen = len;
	tx = dmaengine_prep_slave_single(dma, rx_dmabuf, rx_dmalen,
					 DMA_DEV_TO_MEM, 0);
	अगर (tx) अणु
		tx->callback = smc911x_rx_dma_irq;
		tx->callback_param = lp;
		dmaengine_submit(tx);
		dma_async_issue_pending(dma);
	पूर्ण
पूर्ण
#पूर्ण_अगर

#अगर_घोषित SMC_outsl
#अघोषित SMC_outsl
#घोषणा SMC_outsl(lp, r, p, l) \
	 smc_pxa_dma_outsl(lp, lp->physaddr, r, lp->txdma, p, l)

अटल अंतरभूत व्योम
smc_pxa_dma_outsl(काष्ठा smc911x_local *lp, u_दीर्घ physaddr,
		पूर्णांक reg, काष्ठा dma_chan *dma, u_अक्षर *buf, पूर्णांक len)
अणु
	काष्ठा dma_async_tx_descriptor *tx;

	/* 64 bit alignment is required क्रम memory to memory DMA */
	अगर ((दीर्घ)buf & 4) अणु
		SMC_outl(*((u32 *)buf), lp, reg);
		buf += 4;
		len--;
	पूर्ण

	len *= 4;
	tx_dmabuf = dma_map_single(lp->dev, buf, len, DMA_TO_DEVICE);
	tx_dmalen = len;
	tx = dmaengine_prep_slave_single(dma, tx_dmabuf, tx_dmalen,
					 DMA_DEV_TO_MEM, 0);
	अगर (tx) अणु
		tx->callback = smc911x_tx_dma_irq;
		tx->callback_param = lp;
		dmaengine_submit(tx);
		dma_async_issue_pending(dma);
	पूर्ण
पूर्ण
#पूर्ण_अगर
#पूर्ण_अगर	 /* SMC_USE_PXA_DMA */


/* Chip Parameters and Register Definitions */

#घोषणा SMC911X_TX_FIFO_LOW_THRESHOLD	(1536*2)

#घोषणा SMC911X_IO_EXTENT	 0x100

#घोषणा SMC911X_EEPROM_LEN	 7

/* Below are the रेजिस्टर offsets and bit definitions
 * of the Lan911x memory space
 */
#घोषणा RX_DATA_FIFO		 (0x00)

#घोषणा TX_DATA_FIFO		 (0x20)
#घोषणा	TX_CMD_A_INT_ON_COMP_		(0x80000000)
#घोषणा	TX_CMD_A_INT_BUF_END_ALGN_	(0x03000000)
#घोषणा	TX_CMD_A_INT_4_BYTE_ALGN_	(0x00000000)
#घोषणा	TX_CMD_A_INT_16_BYTE_ALGN_	(0x01000000)
#घोषणा	TX_CMD_A_INT_32_BYTE_ALGN_	(0x02000000)
#घोषणा	TX_CMD_A_INT_DATA_OFFSET_	(0x001F0000)
#घोषणा	TX_CMD_A_INT_FIRST_SEG_		(0x00002000)
#घोषणा	TX_CMD_A_INT_LAST_SEG_		(0x00001000)
#घोषणा	TX_CMD_A_BUF_SIZE_		(0x000007FF)
#घोषणा	TX_CMD_B_PKT_TAG_		(0xFFFF0000)
#घोषणा	TX_CMD_B_ADD_CRC_DISABLE_	(0x00002000)
#घोषणा	TX_CMD_B_DISABLE_PADDING_	(0x00001000)
#घोषणा	TX_CMD_B_PKT_BYTE_LENGTH_	(0x000007FF)

#घोषणा RX_STATUS_FIFO		(0x40)
#घोषणा	RX_STS_PKT_LEN_			(0x3FFF0000)
#घोषणा	RX_STS_ES_			(0x00008000)
#घोषणा	RX_STS_BCST_			(0x00002000)
#घोषणा	RX_STS_LEN_ERR_			(0x00001000)
#घोषणा	RX_STS_RUNT_ERR_		(0x00000800)
#घोषणा	RX_STS_MCAST_			(0x00000400)
#घोषणा	RX_STS_TOO_LONG_		(0x00000080)
#घोषणा	RX_STS_COLL_			(0x00000040)
#घोषणा	RX_STS_ETH_TYPE_		(0x00000020)
#घोषणा	RX_STS_WDOG_TMT_		(0x00000010)
#घोषणा	RX_STS_MII_ERR_			(0x00000008)
#घोषणा	RX_STS_DRIBBLING_		(0x00000004)
#घोषणा	RX_STS_CRC_ERR_			(0x00000002)
#घोषणा RX_STATUS_FIFO_PEEK 	(0x44)
#घोषणा TX_STATUS_FIFO		(0x48)
#घोषणा	TX_STS_TAG_			(0xFFFF0000)
#घोषणा	TX_STS_ES_			(0x00008000)
#घोषणा	TX_STS_LOC_			(0x00000800)
#घोषणा	TX_STS_NO_CARR_			(0x00000400)
#घोषणा	TX_STS_LATE_COLL_		(0x00000200)
#घोषणा	TX_STS_MANY_COLL_		(0x00000100)
#घोषणा	TX_STS_COLL_CNT_		(0x00000078)
#घोषणा	TX_STS_MANY_DEFER_		(0x00000004)
#घोषणा	TX_STS_UNDERRUN_		(0x00000002)
#घोषणा	TX_STS_DEFERRED_		(0x00000001)
#घोषणा TX_STATUS_FIFO_PEEK	(0x4C)
#घोषणा ID_REV			(0x50)
#घोषणा	ID_REV_CHIP_ID_			(0xFFFF0000)  /* RO */
#घोषणा	ID_REV_REV_ID_			(0x0000FFFF)  /* RO */

#घोषणा INT_CFG			(0x54)
#घोषणा	INT_CFG_INT_DEAS_		(0xFF000000)  /* R/W */
#घोषणा	INT_CFG_INT_DEAS_CLR_		(0x00004000)
#घोषणा	INT_CFG_INT_DEAS_STS_		(0x00002000)
#घोषणा	INT_CFG_IRQ_INT_		(0x00001000)  /* RO */
#घोषणा	INT_CFG_IRQ_EN_			(0x00000100)  /* R/W */
#घोषणा	INT_CFG_IRQ_POL_		(0x00000010)  /* R/W Not Affected by SW Reset */
#घोषणा	INT_CFG_IRQ_TYPE_		(0x00000001)  /* R/W Not Affected by SW Reset */

#घोषणा INT_STS			(0x58)
#घोषणा	INT_STS_SW_INT_			(0x80000000)  /* R/WC */
#घोषणा	INT_STS_TXSTOP_INT_		(0x02000000)  /* R/WC */
#घोषणा	INT_STS_RXSTOP_INT_		(0x01000000)  /* R/WC */
#घोषणा	INT_STS_RXDFH_INT_		(0x00800000)  /* R/WC */
#घोषणा	INT_STS_RXDF_INT_		(0x00400000)  /* R/WC */
#घोषणा	INT_STS_TX_IOC_			(0x00200000)  /* R/WC */
#घोषणा	INT_STS_RXD_INT_		(0x00100000)  /* R/WC */
#घोषणा	INT_STS_GPT_INT_		(0x00080000)  /* R/WC */
#घोषणा	INT_STS_PHY_INT_		(0x00040000)  /* RO */
#घोषणा	INT_STS_PME_INT_		(0x00020000)  /* R/WC */
#घोषणा	INT_STS_TXSO_			(0x00010000)  /* R/WC */
#घोषणा	INT_STS_RWT_			(0x00008000)  /* R/WC */
#घोषणा	INT_STS_RXE_			(0x00004000)  /* R/WC */
#घोषणा	INT_STS_TXE_			(0x00002000)  /* R/WC */
//#घोषणा	INT_STS_ERX_		(0x00001000)  /* R/WC */
#घोषणा	INT_STS_TDFU_			(0x00000800)  /* R/WC */
#घोषणा	INT_STS_TDFO_			(0x00000400)  /* R/WC */
#घोषणा	INT_STS_TDFA_			(0x00000200)  /* R/WC */
#घोषणा	INT_STS_TSFF_			(0x00000100)  /* R/WC */
#घोषणा	INT_STS_TSFL_			(0x00000080)  /* R/WC */
//#घोषणा	INT_STS_RXDF_		(0x00000040)  /* R/WC */
#घोषणा	INT_STS_RDFO_			(0x00000040)  /* R/WC */
#घोषणा	INT_STS_RDFL_			(0x00000020)  /* R/WC */
#घोषणा	INT_STS_RSFF_			(0x00000010)  /* R/WC */
#घोषणा	INT_STS_RSFL_			(0x00000008)  /* R/WC */
#घोषणा	INT_STS_GPIO2_INT_		(0x00000004)  /* R/WC */
#घोषणा	INT_STS_GPIO1_INT_		(0x00000002)  /* R/WC */
#घोषणा	INT_STS_GPIO0_INT_		(0x00000001)  /* R/WC */

#घोषणा INT_EN			(0x5C)
#घोषणा	INT_EN_SW_INT_EN_		(0x80000000)  /* R/W */
#घोषणा	INT_EN_TXSTOP_INT_EN_		(0x02000000)  /* R/W */
#घोषणा	INT_EN_RXSTOP_INT_EN_		(0x01000000)  /* R/W */
#घोषणा	INT_EN_RXDFH_INT_EN_		(0x00800000)  /* R/W */
//#घोषणा	INT_EN_RXDF_INT_EN_		(0x00400000)  /* R/W */
#घोषणा	INT_EN_TIOC_INT_EN_		(0x00200000)  /* R/W */
#घोषणा	INT_EN_RXD_INT_EN_		(0x00100000)  /* R/W */
#घोषणा	INT_EN_GPT_INT_EN_		(0x00080000)  /* R/W */
#घोषणा	INT_EN_PHY_INT_EN_		(0x00040000)  /* R/W */
#घोषणा	INT_EN_PME_INT_EN_		(0x00020000)  /* R/W */
#घोषणा	INT_EN_TXSO_EN_			(0x00010000)  /* R/W */
#घोषणा	INT_EN_RWT_EN_			(0x00008000)  /* R/W */
#घोषणा	INT_EN_RXE_EN_			(0x00004000)  /* R/W */
#घोषणा	INT_EN_TXE_EN_			(0x00002000)  /* R/W */
//#घोषणा	INT_EN_ERX_EN_			(0x00001000)  /* R/W */
#घोषणा	INT_EN_TDFU_EN_			(0x00000800)  /* R/W */
#घोषणा	INT_EN_TDFO_EN_			(0x00000400)  /* R/W */
#घोषणा	INT_EN_TDFA_EN_			(0x00000200)  /* R/W */
#घोषणा	INT_EN_TSFF_EN_			(0x00000100)  /* R/W */
#घोषणा	INT_EN_TSFL_EN_			(0x00000080)  /* R/W */
//#घोषणा	INT_EN_RXDF_EN_			(0x00000040)  /* R/W */
#घोषणा	INT_EN_RDFO_EN_			(0x00000040)  /* R/W */
#घोषणा	INT_EN_RDFL_EN_			(0x00000020)  /* R/W */
#घोषणा	INT_EN_RSFF_EN_			(0x00000010)  /* R/W */
#घोषणा	INT_EN_RSFL_EN_			(0x00000008)  /* R/W */
#घोषणा	INT_EN_GPIO2_INT_		(0x00000004)  /* R/W */
#घोषणा	INT_EN_GPIO1_INT_		(0x00000002)  /* R/W */
#घोषणा	INT_EN_GPIO0_INT_		(0x00000001)  /* R/W */

#घोषणा BYTE_TEST		(0x64)
#घोषणा FIFO_INT		(0x68)
#घोषणा	FIFO_INT_TX_AVAIL_LEVEL_	(0xFF000000)  /* R/W */
#घोषणा	FIFO_INT_TX_STS_LEVEL_		(0x00FF0000)  /* R/W */
#घोषणा	FIFO_INT_RX_AVAIL_LEVEL_	(0x0000FF00)  /* R/W */
#घोषणा	FIFO_INT_RX_STS_LEVEL_		(0x000000FF)  /* R/W */

#घोषणा RX_CFG			(0x6C)
#घोषणा	RX_CFG_RX_END_ALGN_		(0xC0000000)  /* R/W */
#घोषणा		RX_CFG_RX_END_ALGN4_		(0x00000000)  /* R/W */
#घोषणा		RX_CFG_RX_END_ALGN16_		(0x40000000)  /* R/W */
#घोषणा		RX_CFG_RX_END_ALGN32_		(0x80000000)  /* R/W */
#घोषणा	RX_CFG_RX_DMA_CNT_		(0x0FFF0000)  /* R/W */
#घोषणा	RX_CFG_RX_DUMP_			(0x00008000)  /* R/W */
#घोषणा	RX_CFG_RXDOFF_			(0x00001F00)  /* R/W */
//#घोषणा	RX_CFG_RXBAD_			(0x00000001)  /* R/W */

#घोषणा TX_CFG			(0x70)
//#घोषणा	TX_CFG_TX_DMA_LVL_		(0xE0000000)	 /* R/W */
//#घोषणा	TX_CFG_TX_DMA_CNT_		(0x0FFF0000)	 /* R/W Self Clearing */
#घोषणा	TX_CFG_TXS_DUMP_		(0x00008000)  /* Self Clearing */
#घोषणा	TX_CFG_TXD_DUMP_		(0x00004000)  /* Self Clearing */
#घोषणा	TX_CFG_TXSAO_			(0x00000004)  /* R/W */
#घोषणा	TX_CFG_TX_ON_			(0x00000002)  /* R/W */
#घोषणा	TX_CFG_STOP_TX_			(0x00000001)  /* Self Clearing */

#घोषणा HW_CFG			(0x74)
#घोषणा	HW_CFG_TTM_			(0x00200000)  /* R/W */
#घोषणा	HW_CFG_SF_			(0x00100000)  /* R/W */
#घोषणा	HW_CFG_TX_FIF_SZ_		(0x000F0000)  /* R/W */
#घोषणा	HW_CFG_TR_			(0x00003000)  /* R/W */
#घोषणा	HW_CFG_PHY_CLK_SEL_		(0x00000060)  /* R/W */
#घोषणा		 HW_CFG_PHY_CLK_SEL_INT_PHY_ 	(0x00000000) /* R/W */
#घोषणा		 HW_CFG_PHY_CLK_SEL_EXT_PHY_ 	(0x00000020) /* R/W */
#घोषणा		 HW_CFG_PHY_CLK_SEL_CLK_DIS_ 	(0x00000040) /* R/W */
#घोषणा	HW_CFG_SMI_SEL_			(0x00000010)  /* R/W */
#घोषणा	HW_CFG_EXT_PHY_DET_		(0x00000008)  /* RO */
#घोषणा	HW_CFG_EXT_PHY_EN_		(0x00000004)  /* R/W */
#घोषणा	HW_CFG_32_16_BIT_MODE_		(0x00000004)  /* RO */
#घोषणा	HW_CFG_SRST_TO_			(0x00000002)  /* RO */
#घोषणा	HW_CFG_SRST_			(0x00000001)  /* Self Clearing */

#घोषणा RX_DP_CTRL		(0x78)
#घोषणा	RX_DP_CTRL_RX_FFWD_		(0x80000000)  /* R/W */
#घोषणा	RX_DP_CTRL_FFWD_BUSY_		(0x80000000)  /* RO */

#घोषणा RX_FIFO_INF		(0x7C)
#घोषणा	 RX_FIFO_INF_RXSUSED_		(0x00FF0000)  /* RO */
#घोषणा	 RX_FIFO_INF_RXDUSED_		(0x0000FFFF)  /* RO */

#घोषणा TX_FIFO_INF		(0x80)
#घोषणा	TX_FIFO_INF_TSUSED_		(0x00FF0000)  /* RO */
#घोषणा	TX_FIFO_INF_TDFREE_		(0x0000FFFF)  /* RO */

#घोषणा PMT_CTRL		(0x84)
#घोषणा	PMT_CTRL_PM_MODE_		(0x00003000)  /* Self Clearing */
#घोषणा	PMT_CTRL_PHY_RST_		(0x00000400)  /* Self Clearing */
#घोषणा	PMT_CTRL_WOL_EN_		(0x00000200)  /* R/W */
#घोषणा	PMT_CTRL_ED_EN_			(0x00000100)  /* R/W */
#घोषणा	PMT_CTRL_PME_TYPE_		(0x00000040)  /* R/W Not Affected by SW Reset */
#घोषणा	PMT_CTRL_WUPS_			(0x00000030)  /* R/WC */
#घोषणा		PMT_CTRL_WUPS_NOWAKE_		(0x00000000)  /* R/WC */
#घोषणा		PMT_CTRL_WUPS_ED_		(0x00000010)  /* R/WC */
#घोषणा		PMT_CTRL_WUPS_WOL_		(0x00000020)  /* R/WC */
#घोषणा		PMT_CTRL_WUPS_MULTI_		(0x00000030)  /* R/WC */
#घोषणा	PMT_CTRL_PME_IND_		(0x00000008)  /* R/W */
#घोषणा	PMT_CTRL_PME_POL_		(0x00000004)  /* R/W */
#घोषणा	PMT_CTRL_PME_EN_		(0x00000002)  /* R/W Not Affected by SW Reset */
#घोषणा	PMT_CTRL_READY_			(0x00000001)  /* RO */

#घोषणा GPIO_CFG		(0x88)
#घोषणा	GPIO_CFG_LED3_EN_		(0x40000000)  /* R/W */
#घोषणा	GPIO_CFG_LED2_EN_		(0x20000000)  /* R/W */
#घोषणा	GPIO_CFG_LED1_EN_		(0x10000000)  /* R/W */
#घोषणा	GPIO_CFG_GPIO2_INT_POL_		(0x04000000)  /* R/W */
#घोषणा	GPIO_CFG_GPIO1_INT_POL_		(0x02000000)  /* R/W */
#घोषणा	GPIO_CFG_GPIO0_INT_POL_		(0x01000000)  /* R/W */
#घोषणा	GPIO_CFG_EEPR_EN_		(0x00700000)  /* R/W */
#घोषणा	GPIO_CFG_GPIOBUF2_		(0x00040000)  /* R/W */
#घोषणा	GPIO_CFG_GPIOBUF1_		(0x00020000)  /* R/W */
#घोषणा	GPIO_CFG_GPIOBUF0_		(0x00010000)  /* R/W */
#घोषणा	GPIO_CFG_GPIOसूची2_		(0x00000400)  /* R/W */
#घोषणा	GPIO_CFG_GPIOसूची1_		(0x00000200)  /* R/W */
#घोषणा	GPIO_CFG_GPIOसूची0_		(0x00000100)  /* R/W */
#घोषणा	GPIO_CFG_GPIOD4_		(0x00000010)  /* R/W */
#घोषणा	GPIO_CFG_GPIOD3_		(0x00000008)  /* R/W */
#घोषणा	GPIO_CFG_GPIOD2_		(0x00000004)  /* R/W */
#घोषणा	GPIO_CFG_GPIOD1_		(0x00000002)  /* R/W */
#घोषणा	GPIO_CFG_GPIOD0_		(0x00000001)  /* R/W */

#घोषणा GPT_CFG			(0x8C)
#घोषणा	GPT_CFG_TIMER_EN_		(0x20000000)  /* R/W */
#घोषणा	GPT_CFG_GPT_LOAD_		(0x0000FFFF)  /* R/W */

#घोषणा GPT_CNT			(0x90)
#घोषणा	GPT_CNT_GPT_CNT_		(0x0000FFFF)  /* RO */

#घोषणा ENDIAN			(0x98)
#घोषणा FREE_RUN		(0x9C)
#घोषणा RX_DROP			(0xA0)
#घोषणा MAC_CSR_CMD		(0xA4)
#घोषणा	 MAC_CSR_CMD_CSR_BUSY_		(0x80000000)  /* Self Clearing */
#घोषणा	 MAC_CSR_CMD_R_NOT_W_		(0x40000000)  /* R/W */
#घोषणा	 MAC_CSR_CMD_CSR_ADDR_		(0x000000FF)  /* R/W */

#घोषणा MAC_CSR_DATA		(0xA8)
#घोषणा AFC_CFG			(0xAC)
#घोषणा		AFC_CFG_AFC_HI_			(0x00FF0000)  /* R/W */
#घोषणा		AFC_CFG_AFC_LO_			(0x0000FF00)  /* R/W */
#घोषणा		AFC_CFG_BACK_DUR_		(0x000000F0)  /* R/W */
#घोषणा		AFC_CFG_FCMULT_			(0x00000008)  /* R/W */
#घोषणा		AFC_CFG_FCBRD_			(0x00000004)  /* R/W */
#घोषणा		AFC_CFG_FCADD_			(0x00000002)  /* R/W */
#घोषणा		AFC_CFG_FCANY_			(0x00000001)  /* R/W */

#घोषणा E2P_CMD			(0xB0)
#घोषणा	E2P_CMD_EPC_BUSY_		(0x80000000)  /* Self Clearing */
#घोषणा	E2P_CMD_EPC_CMD_			(0x70000000)  /* R/W */
#घोषणा		E2P_CMD_EPC_CMD_READ_		(0x00000000)  /* R/W */
#घोषणा		E2P_CMD_EPC_CMD_EWDS_		(0x10000000)  /* R/W */
#घोषणा		E2P_CMD_EPC_CMD_EWEN_		(0x20000000)  /* R/W */
#घोषणा		E2P_CMD_EPC_CMD_WRITE_		(0x30000000)  /* R/W */
#घोषणा		E2P_CMD_EPC_CMD_WRAL_		(0x40000000)  /* R/W */
#घोषणा		E2P_CMD_EPC_CMD_ERASE_		(0x50000000)  /* R/W */
#घोषणा		E2P_CMD_EPC_CMD_ERAL_		(0x60000000)  /* R/W */
#घोषणा		E2P_CMD_EPC_CMD_RELOAD_		(0x70000000)  /* R/W */
#घोषणा	E2P_CMD_EPC_TIMEOUT_		(0x00000200)  /* RO */
#घोषणा	E2P_CMD_MAC_ADDR_LOADED_	(0x00000100)  /* RO */
#घोषणा	E2P_CMD_EPC_ADDR_		(0x000000FF)  /* R/W */

#घोषणा E2P_DATA		(0xB4)
#घोषणा	E2P_DATA_EEPROM_DATA_		(0x000000FF)  /* R/W */
/* end of LAN रेजिस्टर offsets and bit definitions */

/*
 ****************************************************************************
 ****************************************************************************
 * MAC Control and Status Register (Indirect Address)
 * Offset (through the MAC_CSR CMD and DATA port)
 ****************************************************************************
 ****************************************************************************
 *
 */
#घोषणा MAC_CR			(0x01)  /* R/W */

/* MAC_CR - MAC Control Register */
#घोषणा MAC_CR_RXALL_			(0x80000000)
// TODO: delete this bit? It is not described in the data sheet.
#घोषणा MAC_CR_HBDIS_			(0x10000000)
#घोषणा MAC_CR_RCVOWN_			(0x00800000)
#घोषणा MAC_CR_LOOPBK_			(0x00200000)
#घोषणा MAC_CR_FDPX_			(0x00100000)
#घोषणा MAC_CR_MCPAS_			(0x00080000)
#घोषणा MAC_CR_PRMS_			(0x00040000)
#घोषणा MAC_CR_INVFILT_			(0x00020000)
#घोषणा MAC_CR_PASSBAD_			(0x00010000)
#घोषणा MAC_CR_HFILT_			(0x00008000)
#घोषणा MAC_CR_HPFILT_			(0x00002000)
#घोषणा MAC_CR_LCOLL_			(0x00001000)
#घोषणा MAC_CR_BCAST_			(0x00000800)
#घोषणा MAC_CR_DISRTY_			(0x00000400)
#घोषणा MAC_CR_PADSTR_			(0x00000100)
#घोषणा MAC_CR_BOLMT_MASK_		(0x000000C0)
#घोषणा MAC_CR_DFCHK_			(0x00000020)
#घोषणा MAC_CR_TXEN_			(0x00000008)
#घोषणा MAC_CR_RXEN_			(0x00000004)

#घोषणा ADDRH			(0x02)	  /* R/W mask 0x0000FFFFUL */
#घोषणा ADDRL			(0x03)	  /* R/W mask 0xFFFFFFFFUL */
#घोषणा HASHH			(0x04)	  /* R/W */
#घोषणा HASHL			(0x05)	  /* R/W */

#घोषणा MII_ACC			(0x06)	  /* R/W */
#घोषणा MII_ACC_PHY_ADDR_		(0x0000F800)
#घोषणा MII_ACC_MIIRINDA_		(0x000007C0)
#घोषणा MII_ACC_MII_WRITE_		(0x00000002)
#घोषणा MII_ACC_MII_BUSY_		(0x00000001)

#घोषणा MII_DATA		(0x07)	  /* R/W mask 0x0000FFFFUL */

#घोषणा FLOW			(0x08)	  /* R/W */
#घोषणा FLOW_FCPT_			(0xFFFF0000)
#घोषणा FLOW_FCPASS_			(0x00000004)
#घोषणा FLOW_FCEN_			(0x00000002)
#घोषणा FLOW_FCBSY_			(0x00000001)

#घोषणा VLAN1			(0x09)	  /* R/W mask 0x0000FFFFUL */
#घोषणा VLAN1_VTI1_			(0x0000ffff)

#घोषणा VLAN2			(0x0A)	  /* R/W mask 0x0000FFFFUL */
#घोषणा VLAN2_VTI2_			(0x0000ffff)

#घोषणा WUFF			(0x0B)	  /* WO */

#घोषणा WUCSR			(0x0C)	  /* R/W */
#घोषणा WUCSR_GUE_			(0x00000200)
#घोषणा WUCSR_WUFR_			(0x00000040)
#घोषणा WUCSR_MPR_			(0x00000020)
#घोषणा WUCSR_WAKE_EN_			(0x00000004)
#घोषणा WUCSR_MPEN_			(0x00000002)

/*
 ****************************************************************************
 * Chip Specअगरic MII Defines
 ****************************************************************************
 *
 * Phy रेजिस्टर offsets and bit definitions
 *
 */

#घोषणा PHY_MODE_CTRL_STS	((u32)17)	/* Mode Control/Status Register */
//#घोषणा MODE_CTRL_STS_FASTRIP_	  ((u16)0x4000)
#घोषणा MODE_CTRL_STS_EDPWRDOWN_	 ((u16)0x2000)
//#घोषणा MODE_CTRL_STS_LOWSQEN_	   ((u16)0x0800)
//#घोषणा MODE_CTRL_STS_MDPREBP_	   ((u16)0x0400)
//#घोषणा MODE_CTRL_STS_FARLOOPBACK_  ((u16)0x0200)
//#घोषणा MODE_CTRL_STS_FASTEST_	   ((u16)0x0100)
//#घोषणा MODE_CTRL_STS_REFCLKEN_	   ((u16)0x0010)
//#घोषणा MODE_CTRL_STS_PHYADBP_	   ((u16)0x0008)
//#घोषणा MODE_CTRL_STS_FORCE_G_LINK_ ((u16)0x0004)
#घोषणा MODE_CTRL_STS_ENERGYON_	 	((u16)0x0002)

#घोषणा PHY_INT_SRC			((u32)29)
#घोषणा PHY_INT_SRC_ENERGY_ON_			((u16)0x0080)
#घोषणा PHY_INT_SRC_ANEG_COMP_			((u16)0x0040)
#घोषणा PHY_INT_SRC_REMOTE_FAULT_		((u16)0x0020)
#घोषणा PHY_INT_SRC_LINK_DOWN_			((u16)0x0010)
#घोषणा PHY_INT_SRC_ANEG_LP_ACK_		((u16)0x0008)
#घोषणा PHY_INT_SRC_PAR_DET_FAULT_		((u16)0x0004)
#घोषणा PHY_INT_SRC_ANEG_PGRX_			((u16)0x0002)

#घोषणा PHY_INT_MASK			((u32)30)
#घोषणा PHY_INT_MASK_ENERGY_ON_			((u16)0x0080)
#घोषणा PHY_INT_MASK_ANEG_COMP_			((u16)0x0040)
#घोषणा PHY_INT_MASK_REMOTE_FAULT_		((u16)0x0020)
#घोषणा PHY_INT_MASK_LINK_DOWN_			((u16)0x0010)
#घोषणा PHY_INT_MASK_ANEG_LP_ACK_		((u16)0x0008)
#घोषणा PHY_INT_MASK_PAR_DET_FAULT_		((u16)0x0004)
#घोषणा PHY_INT_MASK_ANEG_PGRX_			((u16)0x0002)

#घोषणा PHY_SPECIAL			((u32)31)
#घोषणा PHY_SPECIAL_ANEG_DONE_			((u16)0x1000)
#घोषणा PHY_SPECIAL_RES_			((u16)0x0040)
#घोषणा PHY_SPECIAL_RES_MASK_			((u16)0x0FE1)
#घोषणा PHY_SPECIAL_SPD_			((u16)0x001C)
#घोषणा PHY_SPECIAL_SPD_10HALF_			((u16)0x0004)
#घोषणा PHY_SPECIAL_SPD_10FULL_			((u16)0x0014)
#घोषणा PHY_SPECIAL_SPD_100HALF_		((u16)0x0008)
#घोषणा PHY_SPECIAL_SPD_100FULL_		((u16)0x0018)

#घोषणा LAN911X_INTERNAL_PHY_ID		(0x0007C000)

/* Chip ID values */
#घोषणा CHIP_9115	0x0115
#घोषणा CHIP_9116	0x0116
#घोषणा CHIP_9117	0x0117
#घोषणा CHIP_9118	0x0118
#घोषणा CHIP_9211	0x9211
#घोषणा CHIP_9215	0x115A
#घोषणा CHIP_9217	0x117A
#घोषणा CHIP_9218	0x118A

काष्ठा chip_id अणु
	u16 id;
	अक्षर *name;
पूर्ण;

अटल स्थिर काष्ठा chip_id chip_ids[] =  अणु
	अणु CHIP_9115, "LAN9115" पूर्ण,
	अणु CHIP_9116, "LAN9116" पूर्ण,
	अणु CHIP_9117, "LAN9117" पूर्ण,
	अणु CHIP_9118, "LAN9118" पूर्ण,
	अणु CHIP_9211, "LAN9211" पूर्ण,
	अणु CHIP_9215, "LAN9215" पूर्ण,
	अणु CHIP_9217, "LAN9217" पूर्ण,
	अणु CHIP_9218, "LAN9218" पूर्ण,
	अणु 0, शून्य पूर्ण,
पूर्ण;

#घोषणा IS_REV_A(x)	((x & 0xFFFF)==0)

/*
 * Macros to असलtract रेजिस्टर access according to the data bus
 * capabilities.  Please use those and not the in/out primitives.
 */
/* FIFO पढ़ो/ग_लिखो macros */
#घोषणा SMC_PUSH_DATA(lp, p, l)	SMC_outsl( lp, TX_DATA_FIFO, p, (l) >> 2 )
#घोषणा SMC_PULL_DATA(lp, p, l)	SMC_insl ( lp, RX_DATA_FIFO, p, (l) >> 2 )
#घोषणा SMC_SET_TX_FIFO(lp, x) 	SMC_outl( x, lp, TX_DATA_FIFO )
#घोषणा SMC_GET_RX_FIFO(lp)	SMC_inl( lp, RX_DATA_FIFO )


/* I/O mapped रेजिस्टर पढ़ो/ग_लिखो macros */
#घोषणा SMC_GET_TX_STS_FIFO(lp)		SMC_inl( lp, TX_STATUS_FIFO )
#घोषणा SMC_GET_RX_STS_FIFO(lp)		SMC_inl( lp, RX_STATUS_FIFO )
#घोषणा SMC_GET_RX_STS_FIFO_PEEK(lp)	SMC_inl( lp, RX_STATUS_FIFO_PEEK )
#घोषणा SMC_GET_PN(lp)			(SMC_inl( lp, ID_REV ) >> 16)
#घोषणा SMC_GET_REV(lp)			(SMC_inl( lp, ID_REV ) & 0xFFFF)
#घोषणा SMC_GET_IRQ_CFG(lp)		SMC_inl( lp, INT_CFG )
#घोषणा SMC_SET_IRQ_CFG(lp, x)		SMC_outl( x, lp, INT_CFG )
#घोषणा SMC_GET_INT(lp)			SMC_inl( lp, INT_STS )
#घोषणा SMC_ACK_INT(lp, x)			SMC_outl( x, lp, INT_STS )
#घोषणा SMC_GET_INT_EN(lp)		SMC_inl( lp, INT_EN )
#घोषणा SMC_SET_INT_EN(lp, x)		SMC_outl( x, lp, INT_EN )
#घोषणा SMC_GET_BYTE_TEST(lp)		SMC_inl( lp, BYTE_TEST )
#घोषणा SMC_SET_BYTE_TEST(lp, x)		SMC_outl( x, lp, BYTE_TEST )
#घोषणा SMC_GET_FIFO_INT(lp)		SMC_inl( lp, FIFO_INT )
#घोषणा SMC_SET_FIFO_INT(lp, x)		SMC_outl( x, lp, FIFO_INT )
#घोषणा SMC_SET_FIFO_TDA(lp, x)					\
	करो अणु							\
		अचिन्हित दीर्घ __flags;				\
		पूर्णांक __mask;					\
		local_irq_save(__flags);			\
		__mask = SMC_GET_FIFO_INT((lp)) & ~(0xFF<<24);	\
		SMC_SET_FIFO_INT( (lp), __mask | (x)<<24 );	\
		local_irq_restore(__flags);			\
	पूर्ण जबतक (0)
#घोषणा SMC_SET_FIFO_TSL(lp, x)					\
	करो अणु							\
		अचिन्हित दीर्घ __flags;				\
		पूर्णांक __mask;					\
		local_irq_save(__flags);			\
		__mask = SMC_GET_FIFO_INT((lp)) & ~(0xFF<<16);	\
		SMC_SET_FIFO_INT( (lp), __mask | (((x) & 0xFF)<<16));	\
		local_irq_restore(__flags);			\
	पूर्ण जबतक (0)
#घोषणा SMC_SET_FIFO_RSA(lp, x)					\
	करो अणु							\
		अचिन्हित दीर्घ __flags;				\
		पूर्णांक __mask;					\
		local_irq_save(__flags);			\
		__mask = SMC_GET_FIFO_INT((lp)) & ~(0xFF<<8);	\
		SMC_SET_FIFO_INT( (lp), __mask | (((x) & 0xFF)<<8));	\
		local_irq_restore(__flags);			\
	पूर्ण जबतक (0)
#घोषणा SMC_SET_FIFO_RSL(lp, x)					\
	करो अणु							\
		अचिन्हित दीर्घ __flags;				\
		पूर्णांक __mask;					\
		local_irq_save(__flags);			\
		__mask = SMC_GET_FIFO_INT((lp)) & ~0xFF;	\
		SMC_SET_FIFO_INT( (lp),__mask | ((x) & 0xFF));	\
		local_irq_restore(__flags);			\
	पूर्ण जबतक (0)
#घोषणा SMC_GET_RX_CFG(lp)		SMC_inl( lp, RX_CFG )
#घोषणा SMC_SET_RX_CFG(lp, x)		SMC_outl( x, lp, RX_CFG )
#घोषणा SMC_GET_TX_CFG(lp)		SMC_inl( lp, TX_CFG )
#घोषणा SMC_SET_TX_CFG(lp, x)		SMC_outl( x, lp, TX_CFG )
#घोषणा SMC_GET_HW_CFG(lp)		SMC_inl( lp, HW_CFG )
#घोषणा SMC_SET_HW_CFG(lp, x)		SMC_outl( x, lp, HW_CFG )
#घोषणा SMC_GET_RX_DP_CTRL(lp)		SMC_inl( lp, RX_DP_CTRL )
#घोषणा SMC_SET_RX_DP_CTRL(lp, x)		SMC_outl( x, lp, RX_DP_CTRL )
#घोषणा SMC_GET_PMT_CTRL(lp)		SMC_inl( lp, PMT_CTRL )
#घोषणा SMC_SET_PMT_CTRL(lp, x)		SMC_outl( x, lp, PMT_CTRL )
#घोषणा SMC_GET_GPIO_CFG(lp)		SMC_inl( lp, GPIO_CFG )
#घोषणा SMC_SET_GPIO_CFG(lp, x)		SMC_outl( x, lp, GPIO_CFG )
#घोषणा SMC_GET_RX_FIFO_INF(lp)		SMC_inl( lp, RX_FIFO_INF )
#घोषणा SMC_SET_RX_FIFO_INF(lp, x)		SMC_outl( x, lp, RX_FIFO_INF )
#घोषणा SMC_GET_TX_FIFO_INF(lp)		SMC_inl( lp, TX_FIFO_INF )
#घोषणा SMC_SET_TX_FIFO_INF(lp, x)		SMC_outl( x, lp, TX_FIFO_INF )
#घोषणा SMC_GET_GPT_CFG(lp)		SMC_inl( lp, GPT_CFG )
#घोषणा SMC_SET_GPT_CFG(lp, x)		SMC_outl( x, lp, GPT_CFG )
#घोषणा SMC_GET_RX_DROP(lp)		SMC_inl( lp, RX_DROP )
#घोषणा SMC_SET_RX_DROP(lp, x)		SMC_outl( x, lp, RX_DROP )
#घोषणा SMC_GET_MAC_CMD(lp)		SMC_inl( lp, MAC_CSR_CMD )
#घोषणा SMC_SET_MAC_CMD(lp, x)		SMC_outl( x, lp, MAC_CSR_CMD )
#घोषणा SMC_GET_MAC_DATA(lp)		SMC_inl( lp, MAC_CSR_DATA )
#घोषणा SMC_SET_MAC_DATA(lp, x)		SMC_outl( x, lp, MAC_CSR_DATA )
#घोषणा SMC_GET_AFC_CFG(lp)		SMC_inl( lp, AFC_CFG )
#घोषणा SMC_SET_AFC_CFG(lp, x)		SMC_outl( x, lp, AFC_CFG )
#घोषणा SMC_GET_E2P_CMD(lp)		SMC_inl( lp, E2P_CMD )
#घोषणा SMC_SET_E2P_CMD(lp, x)		SMC_outl( x, lp, E2P_CMD )
#घोषणा SMC_GET_E2P_DATA(lp)		SMC_inl( lp, E2P_DATA )
#घोषणा SMC_SET_E2P_DATA(lp, x)		SMC_outl( x, lp, E2P_DATA )

/* MAC रेजिस्टर पढ़ो/ग_लिखो macros */
#घोषणा SMC_GET_MAC_CSR(lp,a,v)						\
	करो अणु								\
		जबतक (SMC_GET_MAC_CMD((lp)) & MAC_CSR_CMD_CSR_BUSY_);	\
		SMC_SET_MAC_CMD((lp),MAC_CSR_CMD_CSR_BUSY_ |		\
			MAC_CSR_CMD_R_NOT_W_ | (a) );			\
		जबतक (SMC_GET_MAC_CMD((lp)) & MAC_CSR_CMD_CSR_BUSY_);	\
		v = SMC_GET_MAC_DATA((lp));			       	\
	पूर्ण जबतक (0)
#घोषणा SMC_SET_MAC_CSR(lp,a,v)						\
	करो अणु								\
		जबतक (SMC_GET_MAC_CMD((lp)) & MAC_CSR_CMD_CSR_BUSY_);	\
		SMC_SET_MAC_DATA((lp), v);				\
		SMC_SET_MAC_CMD((lp), MAC_CSR_CMD_CSR_BUSY_ | (a) );	\
		जबतक (SMC_GET_MAC_CMD((lp)) & MAC_CSR_CMD_CSR_BUSY_);	\
	पूर्ण जबतक (0)
#घोषणा SMC_GET_MAC_CR(lp, x)	SMC_GET_MAC_CSR( (lp), MAC_CR, x )
#घोषणा SMC_SET_MAC_CR(lp, x)	SMC_SET_MAC_CSR( (lp), MAC_CR, x )
#घोषणा SMC_GET_ADDRH(lp, x)	SMC_GET_MAC_CSR( (lp), ADDRH, x )
#घोषणा SMC_SET_ADDRH(lp, x)	SMC_SET_MAC_CSR( (lp), ADDRH, x )
#घोषणा SMC_GET_ADDRL(lp, x)	SMC_GET_MAC_CSR( (lp), ADDRL, x )
#घोषणा SMC_SET_ADDRL(lp, x)	SMC_SET_MAC_CSR( (lp), ADDRL, x )
#घोषणा SMC_GET_HASHH(lp, x)	SMC_GET_MAC_CSR( (lp), HASHH, x )
#घोषणा SMC_SET_HASHH(lp, x)	SMC_SET_MAC_CSR( (lp), HASHH, x )
#घोषणा SMC_GET_HASHL(lp, x)	SMC_GET_MAC_CSR( (lp), HASHL, x )
#घोषणा SMC_SET_HASHL(lp, x)	SMC_SET_MAC_CSR( (lp), HASHL, x )
#घोषणा SMC_GET_MII_ACC(lp, x)	SMC_GET_MAC_CSR( (lp), MII_ACC, x )
#घोषणा SMC_SET_MII_ACC(lp, x)	SMC_SET_MAC_CSR( (lp), MII_ACC, x )
#घोषणा SMC_GET_MII_DATA(lp, x)	SMC_GET_MAC_CSR( (lp), MII_DATA, x )
#घोषणा SMC_SET_MII_DATA(lp, x)	SMC_SET_MAC_CSR( (lp), MII_DATA, x )
#घोषणा SMC_GET_FLOW(lp, x)		SMC_GET_MAC_CSR( (lp), FLOW, x )
#घोषणा SMC_SET_FLOW(lp, x)		SMC_SET_MAC_CSR( (lp), FLOW, x )
#घोषणा SMC_GET_VLAN1(lp, x)	SMC_GET_MAC_CSR( (lp), VLAN1, x )
#घोषणा SMC_SET_VLAN1(lp, x)	SMC_SET_MAC_CSR( (lp), VLAN1, x )
#घोषणा SMC_GET_VLAN2(lp, x)	SMC_GET_MAC_CSR( (lp), VLAN2, x )
#घोषणा SMC_SET_VLAN2(lp, x)	SMC_SET_MAC_CSR( (lp), VLAN2, x )
#घोषणा SMC_SET_WUFF(lp, x)		SMC_SET_MAC_CSR( (lp), WUFF, x )
#घोषणा SMC_GET_WUCSR(lp, x)	SMC_GET_MAC_CSR( (lp), WUCSR, x )
#घोषणा SMC_SET_WUCSR(lp, x)	SMC_SET_MAC_CSR( (lp), WUCSR, x )

/* PHY रेजिस्टर पढ़ो/ग_लिखो macros */
#घोषणा SMC_GET_MII(lp,a,phy,v)					\
	करो अणु							\
		u32 __v;					\
		करो अणु						\
			SMC_GET_MII_ACC((lp), __v);			\
		पूर्ण जबतक ( __v & MII_ACC_MII_BUSY_ );		\
		SMC_SET_MII_ACC( (lp), ((phy)<<11) | ((a)<<6) |	\
			MII_ACC_MII_BUSY_);			\
		करो अणु						\
			SMC_GET_MII_ACC( (lp), __v);			\
		पूर्ण जबतक ( __v & MII_ACC_MII_BUSY_ );		\
		SMC_GET_MII_DATA((lp), v);				\
	पूर्ण जबतक (0)
#घोषणा SMC_SET_MII(lp,a,phy,v)					\
	करो अणु							\
		u32 __v;					\
		करो अणु						\
			SMC_GET_MII_ACC((lp), __v);			\
		पूर्ण जबतक ( __v & MII_ACC_MII_BUSY_ );		\
		SMC_SET_MII_DATA((lp), v);				\
		SMC_SET_MII_ACC( (lp), ((phy)<<11) | ((a)<<6) |	\
			MII_ACC_MII_BUSY_	 |		\
			MII_ACC_MII_WRITE_  );			\
		करो अणु						\
			SMC_GET_MII_ACC((lp), __v);			\
		पूर्ण जबतक ( __v & MII_ACC_MII_BUSY_ );		\
	पूर्ण जबतक (0)
#घोषणा SMC_GET_PHY_BMCR(lp,phy,x)		SMC_GET_MII( (lp), MII_BMCR, phy, x )
#घोषणा SMC_SET_PHY_BMCR(lp,phy,x)		SMC_SET_MII( (lp), MII_BMCR, phy, x )
#घोषणा SMC_GET_PHY_BMSR(lp,phy,x)		SMC_GET_MII( (lp), MII_BMSR, phy, x )
#घोषणा SMC_GET_PHY_ID1(lp,phy,x)		SMC_GET_MII( (lp), MII_PHYSID1, phy, x )
#घोषणा SMC_GET_PHY_ID2(lp,phy,x)		SMC_GET_MII( (lp), MII_PHYSID2, phy, x )
#घोषणा SMC_GET_PHY_MII_ADV(lp,phy,x)	SMC_GET_MII( (lp), MII_ADVERTISE, phy, x )
#घोषणा SMC_SET_PHY_MII_ADV(lp,phy,x)	SMC_SET_MII( (lp), MII_ADVERTISE, phy, x )
#घोषणा SMC_GET_PHY_MII_LPA(lp,phy,x)	SMC_GET_MII( (lp), MII_LPA, phy, x )
#घोषणा SMC_SET_PHY_MII_LPA(lp,phy,x)	SMC_SET_MII( (lp), MII_LPA, phy, x )
#घोषणा SMC_GET_PHY_CTRL_STS(lp,phy,x)	SMC_GET_MII( (lp), PHY_MODE_CTRL_STS, phy, x )
#घोषणा SMC_SET_PHY_CTRL_STS(lp,phy,x)	SMC_SET_MII( (lp), PHY_MODE_CTRL_STS, phy, x )
#घोषणा SMC_GET_PHY_INT_SRC(lp,phy,x)	SMC_GET_MII( (lp), PHY_INT_SRC, phy, x )
#घोषणा SMC_SET_PHY_INT_SRC(lp,phy,x)	SMC_SET_MII( (lp), PHY_INT_SRC, phy, x )
#घोषणा SMC_GET_PHY_INT_MASK(lp,phy,x)	SMC_GET_MII( (lp), PHY_INT_MASK, phy, x )
#घोषणा SMC_SET_PHY_INT_MASK(lp,phy,x)	SMC_SET_MII( (lp), PHY_INT_MASK, phy, x )
#घोषणा SMC_GET_PHY_SPECIAL(lp,phy,x)	SMC_GET_MII( (lp), PHY_SPECIAL, phy, x )



/* Misc पढ़ो/ग_लिखो macros */

#अगर_अघोषित SMC_GET_MAC_ADDR
#घोषणा SMC_GET_MAC_ADDR(lp, addr)				\
	करो अणु							\
		अचिन्हित पूर्णांक __v;				\
								\
		SMC_GET_MAC_CSR((lp), ADDRL, __v);			\
		addr[0] = __v; addr[1] = __v >> 8;		\
		addr[2] = __v >> 16; addr[3] = __v >> 24;	\
		SMC_GET_MAC_CSR((lp), ADDRH, __v);			\
		addr[4] = __v; addr[5] = __v >> 8;		\
	पूर्ण जबतक (0)
#पूर्ण_अगर

#घोषणा SMC_SET_MAC_ADDR(lp, addr)				\
	करो अणु							\
		 SMC_SET_MAC_CSR((lp), ADDRL,				\
				 addr[0] |			\
				(addr[1] << 8) |		\
				(addr[2] << 16) |		\
				(addr[3] << 24));		\
		 SMC_SET_MAC_CSR((lp), ADDRH, addr[4]|(addr[5] << 8));\
	पूर्ण जबतक (0)


#घोषणा SMC_WRITE_EEPROM_CMD(lp, cmd, addr)				\
	करो अणु								\
		जबतक (SMC_GET_E2P_CMD((lp)) & MAC_CSR_CMD_CSR_BUSY_);	\
		SMC_SET_MAC_CMD((lp), MAC_CSR_CMD_R_NOT_W_ | a );		\
		जबतक (SMC_GET_MAC_CMD((lp)) & MAC_CSR_CMD_CSR_BUSY_);	\
	पूर्ण जबतक (0)

#पूर्ण_अगर	 /* _SMC911X_H_ */
