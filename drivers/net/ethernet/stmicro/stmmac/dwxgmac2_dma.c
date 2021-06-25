<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0 OR MIT)
/*
 * Copyright (c) 2018 Synopsys, Inc. and/or its affiliates.
 * sपंचांगmac XGMAC support.
 */

#समावेश <linux/iopoll.h>
#समावेश "stmmac.h"
#समावेश "dwxgmac2.h"

अटल पूर्णांक dwxgmac2_dma_reset(व्योम __iomem *ioaddr)
अणु
	u32 value = पढ़ोl(ioaddr + XGMAC_DMA_MODE);

	/* DMA SW reset */
	ग_लिखोl(value | XGMAC_SWR, ioaddr + XGMAC_DMA_MODE);

	वापस पढ़ोl_poll_समयout(ioaddr + XGMAC_DMA_MODE, value,
				  !(value & XGMAC_SWR), 0, 100000);
पूर्ण

अटल व्योम dwxgmac2_dma_init(व्योम __iomem *ioaddr,
			      काष्ठा sपंचांगmac_dma_cfg *dma_cfg, पूर्णांक atds)
अणु
	u32 value = पढ़ोl(ioaddr + XGMAC_DMA_SYSBUS_MODE);

	अगर (dma_cfg->aal)
		value |= XGMAC_AAL;

	अगर (dma_cfg->eame)
		value |= XGMAC_EAME;

	ग_लिखोl(value, ioaddr + XGMAC_DMA_SYSBUS_MODE);
पूर्ण

अटल व्योम dwxgmac2_dma_init_chan(व्योम __iomem *ioaddr,
				   काष्ठा sपंचांगmac_dma_cfg *dma_cfg, u32 chan)
अणु
	u32 value = पढ़ोl(ioaddr + XGMAC_DMA_CH_CONTROL(chan));

	अगर (dma_cfg->pblx8)
		value |= XGMAC_PBLx8;

	ग_लिखोl(value, ioaddr + XGMAC_DMA_CH_CONTROL(chan));
	ग_लिखोl(XGMAC_DMA_INT_DEFAULT_EN, ioaddr + XGMAC_DMA_CH_INT_EN(chan));
पूर्ण

अटल व्योम dwxgmac2_dma_init_rx_chan(व्योम __iomem *ioaddr,
				      काष्ठा sपंचांगmac_dma_cfg *dma_cfg,
				      dma_addr_t phy, u32 chan)
अणु
	u32 rxpbl = dma_cfg->rxpbl ?: dma_cfg->pbl;
	u32 value;

	value = पढ़ोl(ioaddr + XGMAC_DMA_CH_RX_CONTROL(chan));
	value &= ~XGMAC_RxPBL;
	value |= (rxpbl << XGMAC_RxPBL_SHIFT) & XGMAC_RxPBL;
	ग_लिखोl(value, ioaddr + XGMAC_DMA_CH_RX_CONTROL(chan));

	ग_लिखोl(upper_32_bits(phy), ioaddr + XGMAC_DMA_CH_RxDESC_HADDR(chan));
	ग_लिखोl(lower_32_bits(phy), ioaddr + XGMAC_DMA_CH_RxDESC_LADDR(chan));
पूर्ण

अटल व्योम dwxgmac2_dma_init_tx_chan(व्योम __iomem *ioaddr,
				      काष्ठा sपंचांगmac_dma_cfg *dma_cfg,
				      dma_addr_t phy, u32 chan)
अणु
	u32 txpbl = dma_cfg->txpbl ?: dma_cfg->pbl;
	u32 value;

	value = पढ़ोl(ioaddr + XGMAC_DMA_CH_TX_CONTROL(chan));
	value &= ~XGMAC_TxPBL;
	value |= (txpbl << XGMAC_TxPBL_SHIFT) & XGMAC_TxPBL;
	value |= XGMAC_OSP;
	ग_लिखोl(value, ioaddr + XGMAC_DMA_CH_TX_CONTROL(chan));

	ग_लिखोl(upper_32_bits(phy), ioaddr + XGMAC_DMA_CH_TxDESC_HADDR(chan));
	ग_लिखोl(lower_32_bits(phy), ioaddr + XGMAC_DMA_CH_TxDESC_LADDR(chan));
पूर्ण

अटल व्योम dwxgmac2_dma_axi(व्योम __iomem *ioaddr, काष्ठा sपंचांगmac_axi *axi)
अणु
	u32 value = पढ़ोl(ioaddr + XGMAC_DMA_SYSBUS_MODE);
	पूर्णांक i;

	अगर (axi->axi_lpi_en)
		value |= XGMAC_EN_LPI;
	अगर (axi->axi_xit_frm)
		value |= XGMAC_LPI_XIT_PKT;

	value &= ~XGMAC_WR_OSR_LMT;
	value |= (axi->axi_wr_osr_lmt << XGMAC_WR_OSR_LMT_SHIFT) &
		XGMAC_WR_OSR_LMT;

	value &= ~XGMAC_RD_OSR_LMT;
	value |= (axi->axi_rd_osr_lmt << XGMAC_RD_OSR_LMT_SHIFT) &
		XGMAC_RD_OSR_LMT;

	अगर (!axi->axi_fb)
		value |= XGMAC_UNDEF;

	value &= ~XGMAC_BLEN;
	क्रम (i = 0; i < AXI_BLEN; i++) अणु
		चयन (axi->axi_blen[i]) अणु
		हाल 256:
			value |= XGMAC_BLEN256;
			अवरोध;
		हाल 128:
			value |= XGMAC_BLEN128;
			अवरोध;
		हाल 64:
			value |= XGMAC_BLEN64;
			अवरोध;
		हाल 32:
			value |= XGMAC_BLEN32;
			अवरोध;
		हाल 16:
			value |= XGMAC_BLEN16;
			अवरोध;
		हाल 8:
			value |= XGMAC_BLEN8;
			अवरोध;
		हाल 4:
			value |= XGMAC_BLEN4;
			अवरोध;
		पूर्ण
	पूर्ण

	ग_लिखोl(value, ioaddr + XGMAC_DMA_SYSBUS_MODE);
	ग_लिखोl(XGMAC_TDPS, ioaddr + XGMAC_TX_EDMA_CTRL);
	ग_लिखोl(XGMAC_RDPS, ioaddr + XGMAC_RX_EDMA_CTRL);
पूर्ण

अटल व्योम dwxgmac2_dma_dump_regs(व्योम __iomem *ioaddr, u32 *reg_space)
अणु
	पूर्णांक i;

	क्रम (i = (XGMAC_DMA_MODE / 4); i < XGMAC_REGSIZE; i++)
		reg_space[i] = पढ़ोl(ioaddr + i * 4);
पूर्ण

अटल व्योम dwxgmac2_dma_rx_mode(व्योम __iomem *ioaddr, पूर्णांक mode,
				 u32 channel, पूर्णांक fअगरosz, u8 qmode)
अणु
	u32 value = पढ़ोl(ioaddr + XGMAC_MTL_RXQ_OPMODE(channel));
	अचिन्हित पूर्णांक rqs = fअगरosz / 256 - 1;

	अगर (mode == SF_DMA_MODE) अणु
		value |= XGMAC_RSF;
	पूर्ण अन्यथा अणु
		value &= ~XGMAC_RSF;
		value &= ~XGMAC_RTC;

		अगर (mode <= 64)
			value |= 0x0 << XGMAC_RTC_SHIFT;
		अन्यथा अगर (mode <= 96)
			value |= 0x2 << XGMAC_RTC_SHIFT;
		अन्यथा
			value |= 0x3 << XGMAC_RTC_SHIFT;
	पूर्ण

	value &= ~XGMAC_RQS;
	value |= (rqs << XGMAC_RQS_SHIFT) & XGMAC_RQS;

	अगर ((fअगरosz >= 4096) && (qmode != MTL_QUEUE_AVB)) अणु
		u32 flow = पढ़ोl(ioaddr + XGMAC_MTL_RXQ_FLOW_CONTROL(channel));
		अचिन्हित पूर्णांक rfd, rfa;

		value |= XGMAC_EHFC;

		/* Set Threshold क्रम Activating Flow Control to min 2 frames,
		 * i.e. 1500 * 2 = 3000 bytes.
		 *
		 * Set Threshold क्रम Deactivating Flow Control to min 1 frame,
		 * i.e. 1500 bytes.
		 */
		चयन (fअगरosz) अणु
		हाल 4096:
			/* This violates the above क्रमmula because of FIFO size
			 * limit thereक्रमe overflow may occur in spite of this.
			 */
			rfd = 0x03; /* Full-2.5K */
			rfa = 0x01; /* Full-1.5K */
			अवरोध;

		शेष:
			rfd = 0x07; /* Full-4.5K */
			rfa = 0x04; /* Full-3K */
			अवरोध;
		पूर्ण

		flow &= ~XGMAC_RFD;
		flow |= rfd << XGMAC_RFD_SHIFT;

		flow &= ~XGMAC_RFA;
		flow |= rfa << XGMAC_RFA_SHIFT;

		ग_लिखोl(flow, ioaddr + XGMAC_MTL_RXQ_FLOW_CONTROL(channel));
	पूर्ण

	ग_लिखोl(value, ioaddr + XGMAC_MTL_RXQ_OPMODE(channel));

	/* Enable MTL RX overflow */
	value = पढ़ोl(ioaddr + XGMAC_MTL_QINTEN(channel));
	ग_लिखोl(value | XGMAC_RXOIE, ioaddr + XGMAC_MTL_QINTEN(channel));
पूर्ण

अटल व्योम dwxgmac2_dma_tx_mode(व्योम __iomem *ioaddr, पूर्णांक mode,
				 u32 channel, पूर्णांक fअगरosz, u8 qmode)
अणु
	u32 value = पढ़ोl(ioaddr + XGMAC_MTL_TXQ_OPMODE(channel));
	अचिन्हित पूर्णांक tqs = fअगरosz / 256 - 1;

	अगर (mode == SF_DMA_MODE) अणु
		value |= XGMAC_TSF;
	पूर्ण अन्यथा अणु
		value &= ~XGMAC_TSF;
		value &= ~XGMAC_TTC;

		अगर (mode <= 64)
			value |= 0x0 << XGMAC_TTC_SHIFT;
		अन्यथा अगर (mode <= 96)
			value |= 0x2 << XGMAC_TTC_SHIFT;
		अन्यथा अगर (mode <= 128)
			value |= 0x3 << XGMAC_TTC_SHIFT;
		अन्यथा अगर (mode <= 192)
			value |= 0x4 << XGMAC_TTC_SHIFT;
		अन्यथा अगर (mode <= 256)
			value |= 0x5 << XGMAC_TTC_SHIFT;
		अन्यथा अगर (mode <= 384)
			value |= 0x6 << XGMAC_TTC_SHIFT;
		अन्यथा
			value |= 0x7 << XGMAC_TTC_SHIFT;
	पूर्ण

	/* Use अटल TC to Queue mapping */
	value |= (channel << XGMAC_Q2TCMAP_SHIFT) & XGMAC_Q2TCMAP;

	value &= ~XGMAC_TXQEN;
	अगर (qmode != MTL_QUEUE_AVB)
		value |= 0x2 << XGMAC_TXQEN_SHIFT;
	अन्यथा
		value |= 0x1 << XGMAC_TXQEN_SHIFT;

	value &= ~XGMAC_TQS;
	value |= (tqs << XGMAC_TQS_SHIFT) & XGMAC_TQS;

	ग_लिखोl(value, ioaddr +  XGMAC_MTL_TXQ_OPMODE(channel));
पूर्ण

अटल व्योम dwxgmac2_enable_dma_irq(व्योम __iomem *ioaddr, u32 chan,
				    bool rx, bool tx)
अणु
	u32 value = पढ़ोl(ioaddr + XGMAC_DMA_CH_INT_EN(chan));

	अगर (rx)
		value |= XGMAC_DMA_INT_DEFAULT_RX;
	अगर (tx)
		value |= XGMAC_DMA_INT_DEFAULT_TX;

	ग_लिखोl(value, ioaddr + XGMAC_DMA_CH_INT_EN(chan));
पूर्ण

अटल व्योम dwxgmac2_disable_dma_irq(व्योम __iomem *ioaddr, u32 chan,
				     bool rx, bool tx)
अणु
	u32 value = पढ़ोl(ioaddr + XGMAC_DMA_CH_INT_EN(chan));

	अगर (rx)
		value &= ~XGMAC_DMA_INT_DEFAULT_RX;
	अगर (tx)
		value &= ~XGMAC_DMA_INT_DEFAULT_TX;

	ग_लिखोl(value, ioaddr + XGMAC_DMA_CH_INT_EN(chan));
पूर्ण

अटल व्योम dwxgmac2_dma_start_tx(व्योम __iomem *ioaddr, u32 chan)
अणु
	u32 value;

	value = पढ़ोl(ioaddr + XGMAC_DMA_CH_TX_CONTROL(chan));
	value |= XGMAC_TXST;
	ग_लिखोl(value, ioaddr + XGMAC_DMA_CH_TX_CONTROL(chan));

	value = पढ़ोl(ioaddr + XGMAC_TX_CONFIG);
	value |= XGMAC_CONFIG_TE;
	ग_लिखोl(value, ioaddr + XGMAC_TX_CONFIG);
पूर्ण

अटल व्योम dwxgmac2_dma_stop_tx(व्योम __iomem *ioaddr, u32 chan)
अणु
	u32 value;

	value = पढ़ोl(ioaddr + XGMAC_DMA_CH_TX_CONTROL(chan));
	value &= ~XGMAC_TXST;
	ग_लिखोl(value, ioaddr + XGMAC_DMA_CH_TX_CONTROL(chan));

	value = पढ़ोl(ioaddr + XGMAC_TX_CONFIG);
	value &= ~XGMAC_CONFIG_TE;
	ग_लिखोl(value, ioaddr + XGMAC_TX_CONFIG);
पूर्ण

अटल व्योम dwxgmac2_dma_start_rx(व्योम __iomem *ioaddr, u32 chan)
अणु
	u32 value;

	value = पढ़ोl(ioaddr + XGMAC_DMA_CH_RX_CONTROL(chan));
	value |= XGMAC_RXST;
	ग_लिखोl(value, ioaddr + XGMAC_DMA_CH_RX_CONTROL(chan));

	value = पढ़ोl(ioaddr + XGMAC_RX_CONFIG);
	value |= XGMAC_CONFIG_RE;
	ग_लिखोl(value, ioaddr + XGMAC_RX_CONFIG);
पूर्ण

अटल व्योम dwxgmac2_dma_stop_rx(व्योम __iomem *ioaddr, u32 chan)
अणु
	u32 value;

	value = पढ़ोl(ioaddr + XGMAC_DMA_CH_RX_CONTROL(chan));
	value &= ~XGMAC_RXST;
	ग_लिखोl(value, ioaddr + XGMAC_DMA_CH_RX_CONTROL(chan));
पूर्ण

अटल पूर्णांक dwxgmac2_dma_पूर्णांकerrupt(व्योम __iomem *ioaddr,
				  काष्ठा sपंचांगmac_extra_stats *x, u32 chan,
				  u32 dir)
अणु
	u32 पूर्णांकr_status = पढ़ोl(ioaddr + XGMAC_DMA_CH_STATUS(chan));
	u32 पूर्णांकr_en = पढ़ोl(ioaddr + XGMAC_DMA_CH_INT_EN(chan));
	पूर्णांक ret = 0;

	अगर (dir == DMA_सूची_RX)
		पूर्णांकr_status &= XGMAC_DMA_STATUS_MSK_RX;
	अन्यथा अगर (dir == DMA_सूची_TX)
		पूर्णांकr_status &= XGMAC_DMA_STATUS_MSK_TX;

	/* ABNORMAL पूर्णांकerrupts */
	अगर (unlikely(पूर्णांकr_status & XGMAC_AIS)) अणु
		अगर (unlikely(पूर्णांकr_status & XGMAC_RBU)) अणु
			x->rx_buf_unav_irq++;
			ret |= handle_rx;
		पूर्ण
		अगर (unlikely(पूर्णांकr_status & XGMAC_TPS)) अणु
			x->tx_process_stopped_irq++;
			ret |= tx_hard_error;
		पूर्ण
		अगर (unlikely(पूर्णांकr_status & XGMAC_FBE)) अणु
			x->fatal_bus_error_irq++;
			ret |= tx_hard_error;
		पूर्ण
	पूर्ण

	/* TX/RX NORMAL पूर्णांकerrupts */
	अगर (likely(पूर्णांकr_status & XGMAC_NIS)) अणु
		x->normal_irq_n++;

		अगर (likely(पूर्णांकr_status & XGMAC_RI)) अणु
			x->rx_normal_irq_n++;
			ret |= handle_rx;
		पूर्ण
		अगर (likely(पूर्णांकr_status & (XGMAC_TI | XGMAC_TBU))) अणु
			x->tx_normal_irq_n++;
			ret |= handle_tx;
		पूर्ण
	पूर्ण

	/* Clear पूर्णांकerrupts */
	ग_लिखोl(पूर्णांकr_en & पूर्णांकr_status, ioaddr + XGMAC_DMA_CH_STATUS(chan));

	वापस ret;
पूर्ण

अटल व्योम dwxgmac2_get_hw_feature(व्योम __iomem *ioaddr,
				    काष्ठा dma_features *dma_cap)
अणु
	u32 hw_cap;

	/*  MAC HW feature 0 */
	hw_cap = पढ़ोl(ioaddr + XGMAC_HW_FEATURE0);
	dma_cap->vlins = (hw_cap & XGMAC_HWFEAT_SAVLANINS) >> 27;
	dma_cap->rx_coe = (hw_cap & XGMAC_HWFEAT_RXCOESEL) >> 16;
	dma_cap->tx_coe = (hw_cap & XGMAC_HWFEAT_TXCOESEL) >> 14;
	dma_cap->eee = (hw_cap & XGMAC_HWFEAT_EEESEL) >> 13;
	dma_cap->aसमय_stamp = (hw_cap & XGMAC_HWFEAT_TSSEL) >> 12;
	dma_cap->av = (hw_cap & XGMAC_HWFEAT_AVSEL) >> 11;
	dma_cap->av &= !((hw_cap & XGMAC_HWFEAT_RAVSEL) >> 10);
	dma_cap->arpoffsel = (hw_cap & XGMAC_HWFEAT_ARPOFFSEL) >> 9;
	dma_cap->rmon = (hw_cap & XGMAC_HWFEAT_MMCSEL) >> 8;
	dma_cap->pmt_magic_frame = (hw_cap & XGMAC_HWFEAT_MGKSEL) >> 7;
	dma_cap->pmt_remote_wake_up = (hw_cap & XGMAC_HWFEAT_RWKSEL) >> 6;
	dma_cap->vlhash = (hw_cap & XGMAC_HWFEAT_VLHASH) >> 4;
	dma_cap->mbps_1000 = (hw_cap & XGMAC_HWFEAT_GMIISEL) >> 1;

	/* MAC HW feature 1 */
	hw_cap = पढ़ोl(ioaddr + XGMAC_HW_FEATURE1);
	dma_cap->l3l4fnum = (hw_cap & XGMAC_HWFEAT_L3L4FNUM) >> 27;
	dma_cap->hash_tb_sz = (hw_cap & XGMAC_HWFEAT_HASHTBLSZ) >> 24;
	dma_cap->rssen = (hw_cap & XGMAC_HWFEAT_RSSEN) >> 20;
	dma_cap->tsoen = (hw_cap & XGMAC_HWFEAT_TSOEN) >> 18;
	dma_cap->sphen = (hw_cap & XGMAC_HWFEAT_SPHEN) >> 17;

	dma_cap->addr64 = (hw_cap & XGMAC_HWFEAT_ADDR64) >> 14;
	चयन (dma_cap->addr64) अणु
	हाल 0:
		dma_cap->addr64 = 32;
		अवरोध;
	हाल 1:
		dma_cap->addr64 = 40;
		अवरोध;
	हाल 2:
		dma_cap->addr64 = 48;
		अवरोध;
	शेष:
		dma_cap->addr64 = 32;
		अवरोध;
	पूर्ण

	dma_cap->tx_fअगरo_size =
		128 << ((hw_cap & XGMAC_HWFEAT_TXFIFOSIZE) >> 6);
	dma_cap->rx_fअगरo_size =
		128 << ((hw_cap & XGMAC_HWFEAT_RXFIFOSIZE) >> 0);

	/* MAC HW feature 2 */
	hw_cap = पढ़ोl(ioaddr + XGMAC_HW_FEATURE2);
	dma_cap->pps_out_num = (hw_cap & XGMAC_HWFEAT_PPSOUTNUM) >> 24;
	dma_cap->number_tx_channel =
		((hw_cap & XGMAC_HWFEAT_TXCHCNT) >> 18) + 1;
	dma_cap->number_rx_channel =
		((hw_cap & XGMAC_HWFEAT_RXCHCNT) >> 12) + 1;
	dma_cap->number_tx_queues =
		((hw_cap & XGMAC_HWFEAT_TXQCNT) >> 6) + 1;
	dma_cap->number_rx_queues =
		((hw_cap & XGMAC_HWFEAT_RXQCNT) >> 0) + 1;

	/* MAC HW feature 3 */
	hw_cap = पढ़ोl(ioaddr + XGMAC_HW_FEATURE3);
	dma_cap->tbssel = (hw_cap & XGMAC_HWFEAT_TBSSEL) >> 27;
	dma_cap->fpesel = (hw_cap & XGMAC_HWFEAT_FPESEL) >> 26;
	dma_cap->estwid = (hw_cap & XGMAC_HWFEAT_ESTWID) >> 23;
	dma_cap->estdep = (hw_cap & XGMAC_HWFEAT_ESTDEP) >> 20;
	dma_cap->estsel = (hw_cap & XGMAC_HWFEAT_ESTSEL) >> 19;
	dma_cap->asp = (hw_cap & XGMAC_HWFEAT_ASP) >> 14;
	dma_cap->dvlan = (hw_cap & XGMAC_HWFEAT_DVLAN) >> 13;
	dma_cap->frpes = (hw_cap & XGMAC_HWFEAT_FRPES) >> 11;
	dma_cap->frpbs = (hw_cap & XGMAC_HWFEAT_FRPPB) >> 9;
	dma_cap->frpsel = (hw_cap & XGMAC_HWFEAT_FRPSEL) >> 3;
पूर्ण

अटल व्योम dwxgmac2_rx_watchकरोg(व्योम __iomem *ioaddr, u32 riwt, u32 queue)
अणु
	ग_लिखोl(riwt & XGMAC_RWT, ioaddr + XGMAC_DMA_CH_Rx_WATCHDOG(queue));
पूर्ण

अटल व्योम dwxgmac2_set_rx_ring_len(व्योम __iomem *ioaddr, u32 len, u32 chan)
अणु
	ग_लिखोl(len, ioaddr + XGMAC_DMA_CH_RxDESC_RING_LEN(chan));
पूर्ण

अटल व्योम dwxgmac2_set_tx_ring_len(व्योम __iomem *ioaddr, u32 len, u32 chan)
अणु
	ग_लिखोl(len, ioaddr + XGMAC_DMA_CH_TxDESC_RING_LEN(chan));
पूर्ण

अटल व्योम dwxgmac2_set_rx_tail_ptr(व्योम __iomem *ioaddr, u32 ptr, u32 chan)
अणु
	ग_लिखोl(ptr, ioaddr + XGMAC_DMA_CH_RxDESC_TAIL_LPTR(chan));
पूर्ण

अटल व्योम dwxgmac2_set_tx_tail_ptr(व्योम __iomem *ioaddr, u32 ptr, u32 chan)
अणु
	ग_लिखोl(ptr, ioaddr + XGMAC_DMA_CH_TxDESC_TAIL_LPTR(chan));
पूर्ण

अटल व्योम dwxgmac2_enable_tso(व्योम __iomem *ioaddr, bool en, u32 chan)
अणु
	u32 value = पढ़ोl(ioaddr + XGMAC_DMA_CH_TX_CONTROL(chan));

	अगर (en)
		value |= XGMAC_TSE;
	अन्यथा
		value &= ~XGMAC_TSE;

	ग_लिखोl(value, ioaddr + XGMAC_DMA_CH_TX_CONTROL(chan));
पूर्ण

अटल व्योम dwxgmac2_qmode(व्योम __iomem *ioaddr, u32 channel, u8 qmode)
अणु
	u32 value = पढ़ोl(ioaddr + XGMAC_MTL_TXQ_OPMODE(channel));
	u32 flow = पढ़ोl(ioaddr + XGMAC_RX_FLOW_CTRL);

	value &= ~XGMAC_TXQEN;
	अगर (qmode != MTL_QUEUE_AVB) अणु
		value |= 0x2 << XGMAC_TXQEN_SHIFT;
		ग_लिखोl(0, ioaddr + XGMAC_MTL_TCx_ETS_CONTROL(channel));
	पूर्ण अन्यथा अणु
		value |= 0x1 << XGMAC_TXQEN_SHIFT;
		ग_लिखोl(flow & (~XGMAC_RFE), ioaddr + XGMAC_RX_FLOW_CTRL);
	पूर्ण

	ग_लिखोl(value, ioaddr +  XGMAC_MTL_TXQ_OPMODE(channel));
पूर्ण

अटल व्योम dwxgmac2_set_bfsize(व्योम __iomem *ioaddr, पूर्णांक bfsize, u32 chan)
अणु
	u32 value;

	value = पढ़ोl(ioaddr + XGMAC_DMA_CH_RX_CONTROL(chan));
	value &= ~XGMAC_RBSZ;
	value |= bfsize << XGMAC_RBSZ_SHIFT;
	ग_लिखोl(value, ioaddr + XGMAC_DMA_CH_RX_CONTROL(chan));
पूर्ण

अटल व्योम dwxgmac2_enable_sph(व्योम __iomem *ioaddr, bool en, u32 chan)
अणु
	u32 value = पढ़ोl(ioaddr + XGMAC_RX_CONFIG);

	value &= ~XGMAC_CONFIG_HDSMS;
	value |= XGMAC_CONFIG_HDSMS_256; /* Segment max 256 bytes */
	ग_लिखोl(value, ioaddr + XGMAC_RX_CONFIG);

	value = पढ़ोl(ioaddr + XGMAC_DMA_CH_CONTROL(chan));
	अगर (en)
		value |= XGMAC_SPH;
	अन्यथा
		value &= ~XGMAC_SPH;
	ग_लिखोl(value, ioaddr + XGMAC_DMA_CH_CONTROL(chan));
पूर्ण

अटल पूर्णांक dwxgmac2_enable_tbs(व्योम __iomem *ioaddr, bool en, u32 chan)
अणु
	u32 value = पढ़ोl(ioaddr + XGMAC_DMA_CH_TX_CONTROL(chan));

	अगर (en)
		value |= XGMAC_EDSE;
	अन्यथा
		value &= ~XGMAC_EDSE;

	ग_लिखोl(value, ioaddr + XGMAC_DMA_CH_TX_CONTROL(chan));

	value = पढ़ोl(ioaddr + XGMAC_DMA_CH_TX_CONTROL(chan)) & XGMAC_EDSE;
	अगर (en && !value)
		वापस -EIO;

	ग_लिखोl(XGMAC_DEF_FTOS, ioaddr + XGMAC_DMA_TBS_CTRL0);
	ग_लिखोl(XGMAC_DEF_FTOS, ioaddr + XGMAC_DMA_TBS_CTRL1);
	ग_लिखोl(XGMAC_DEF_FTOS, ioaddr + XGMAC_DMA_TBS_CTRL2);
	ग_लिखोl(XGMAC_DEF_FTOS, ioaddr + XGMAC_DMA_TBS_CTRL3);
	वापस 0;
पूर्ण

स्थिर काष्ठा sपंचांगmac_dma_ops dwxgmac210_dma_ops = अणु
	.reset = dwxgmac2_dma_reset,
	.init = dwxgmac2_dma_init,
	.init_chan = dwxgmac2_dma_init_chan,
	.init_rx_chan = dwxgmac2_dma_init_rx_chan,
	.init_tx_chan = dwxgmac2_dma_init_tx_chan,
	.axi = dwxgmac2_dma_axi,
	.dump_regs = dwxgmac2_dma_dump_regs,
	.dma_rx_mode = dwxgmac2_dma_rx_mode,
	.dma_tx_mode = dwxgmac2_dma_tx_mode,
	.enable_dma_irq = dwxgmac2_enable_dma_irq,
	.disable_dma_irq = dwxgmac2_disable_dma_irq,
	.start_tx = dwxgmac2_dma_start_tx,
	.stop_tx = dwxgmac2_dma_stop_tx,
	.start_rx = dwxgmac2_dma_start_rx,
	.stop_rx = dwxgmac2_dma_stop_rx,
	.dma_पूर्णांकerrupt = dwxgmac2_dma_पूर्णांकerrupt,
	.get_hw_feature = dwxgmac2_get_hw_feature,
	.rx_watchकरोg = dwxgmac2_rx_watchकरोg,
	.set_rx_ring_len = dwxgmac2_set_rx_ring_len,
	.set_tx_ring_len = dwxgmac2_set_tx_ring_len,
	.set_rx_tail_ptr = dwxgmac2_set_rx_tail_ptr,
	.set_tx_tail_ptr = dwxgmac2_set_tx_tail_ptr,
	.enable_tso = dwxgmac2_enable_tso,
	.qmode = dwxgmac2_qmode,
	.set_bfsize = dwxgmac2_set_bfsize,
	.enable_sph = dwxgmac2_enable_sph,
	.enable_tbs = dwxgmac2_enable_tbs,
पूर्ण;
