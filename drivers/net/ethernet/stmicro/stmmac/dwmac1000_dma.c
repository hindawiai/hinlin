<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*******************************************************************************
  This is the driver क्रम the GMAC on-chip Ethernet controller क्रम ST SoCs.
  DWC Ether MAC 10/100/1000 Universal version 3.41a  has been used क्रम
  developing this code.

  This contains the functions to handle the dma.

  Copyright (C) 2007-2009  STMicroelectronics Ltd


  Author: Giuseppe Cavallaro <peppe.cavallaro@st.com>
*******************************************************************************/

#समावेश <यंत्र/पन.स>
#समावेश "dwmac1000.h"
#समावेश "dwmac_dma.h"

अटल व्योम dwmac1000_dma_axi(व्योम __iomem *ioaddr, काष्ठा sपंचांगmac_axi *axi)
अणु
	u32 value = पढ़ोl(ioaddr + DMA_AXI_BUS_MODE);
	पूर्णांक i;

	pr_info("dwmac1000: Master AXI performs %s burst length\n",
		!(value & DMA_AXI_UNDEF) ? "fixed" : "any");

	अगर (axi->axi_lpi_en)
		value |= DMA_AXI_EN_LPI;
	अगर (axi->axi_xit_frm)
		value |= DMA_AXI_LPI_XIT_FRM;

	value &= ~DMA_AXI_WR_OSR_LMT;
	value |= (axi->axi_wr_osr_lmt & DMA_AXI_WR_OSR_LMT_MASK) <<
		 DMA_AXI_WR_OSR_LMT_SHIFT;

	value &= ~DMA_AXI_RD_OSR_LMT;
	value |= (axi->axi_rd_osr_lmt & DMA_AXI_RD_OSR_LMT_MASK) <<
		 DMA_AXI_RD_OSR_LMT_SHIFT;

	/* Depending on the UNDEF bit the Master AXI will perक्रमm any burst
	 * length according to the BLEN programmed (by शेष all BLEN are
	 * set).
	 */
	क्रम (i = 0; i < AXI_BLEN; i++) अणु
		चयन (axi->axi_blen[i]) अणु
		हाल 256:
			value |= DMA_AXI_BLEN256;
			अवरोध;
		हाल 128:
			value |= DMA_AXI_BLEN128;
			अवरोध;
		हाल 64:
			value |= DMA_AXI_BLEN64;
			अवरोध;
		हाल 32:
			value |= DMA_AXI_BLEN32;
			अवरोध;
		हाल 16:
			value |= DMA_AXI_BLEN16;
			अवरोध;
		हाल 8:
			value |= DMA_AXI_BLEN8;
			अवरोध;
		हाल 4:
			value |= DMA_AXI_BLEN4;
			अवरोध;
		पूर्ण
	पूर्ण

	ग_लिखोl(value, ioaddr + DMA_AXI_BUS_MODE);
पूर्ण

अटल व्योम dwmac1000_dma_init(व्योम __iomem *ioaddr,
			       काष्ठा sपंचांगmac_dma_cfg *dma_cfg, पूर्णांक atds)
अणु
	u32 value = पढ़ोl(ioaddr + DMA_BUS_MODE);
	पूर्णांक txpbl = dma_cfg->txpbl ?: dma_cfg->pbl;
	पूर्णांक rxpbl = dma_cfg->rxpbl ?: dma_cfg->pbl;

	/*
	 * Set the DMA PBL (Programmable Burst Length) mode.
	 *
	 * Note: beक्रमe sपंचांगmac core 3.50 this mode bit was 4xPBL, and
	 * post 3.5 mode bit acts as 8*PBL.
	 */
	अगर (dma_cfg->pblx8)
		value |= DMA_BUS_MODE_MAXPBL;
	value |= DMA_BUS_MODE_USP;
	value &= ~(DMA_BUS_MODE_PBL_MASK | DMA_BUS_MODE_RPBL_MASK);
	value |= (txpbl << DMA_BUS_MODE_PBL_SHIFT);
	value |= (rxpbl << DMA_BUS_MODE_RPBL_SHIFT);

	/* Set the Fixed burst mode */
	अगर (dma_cfg->fixed_burst)
		value |= DMA_BUS_MODE_FB;

	/* Mixed Burst has no effect when fb is set */
	अगर (dma_cfg->mixed_burst)
		value |= DMA_BUS_MODE_MB;

	अगर (atds)
		value |= DMA_BUS_MODE_ATDS;

	अगर (dma_cfg->aal)
		value |= DMA_BUS_MODE_AAL;

	ग_लिखोl(value, ioaddr + DMA_BUS_MODE);

	/* Mask पूर्णांकerrupts by writing to CSR7 */
	ग_लिखोl(DMA_INTR_DEFAULT_MASK, ioaddr + DMA_INTR_ENA);
पूर्ण

अटल व्योम dwmac1000_dma_init_rx(व्योम __iomem *ioaddr,
				  काष्ठा sपंचांगmac_dma_cfg *dma_cfg,
				  dma_addr_t dma_rx_phy, u32 chan)
अणु
	/* RX descriptor base address list must be written पूर्णांकo DMA CSR3 */
	ग_लिखोl(lower_32_bits(dma_rx_phy), ioaddr + DMA_RCV_BASE_ADDR);
पूर्ण

अटल व्योम dwmac1000_dma_init_tx(व्योम __iomem *ioaddr,
				  काष्ठा sपंचांगmac_dma_cfg *dma_cfg,
				  dma_addr_t dma_tx_phy, u32 chan)
अणु
	/* TX descriptor base address list must be written पूर्णांकo DMA CSR4 */
	ग_लिखोl(lower_32_bits(dma_tx_phy), ioaddr + DMA_TX_BASE_ADDR);
पूर्ण

अटल u32 dwmac1000_configure_fc(u32 csr6, पूर्णांक rxfअगरosz)
अणु
	csr6 &= ~DMA_CONTROL_RFA_MASK;
	csr6 &= ~DMA_CONTROL_RFD_MASK;

	/* Leave flow control disabled अगर receive fअगरo size is less than
	 * 4K or 0. Otherwise, send XOFF when fअगरo is 1K less than full,
	 * and send XON when 2K less than full.
	 */
	अगर (rxfअगरosz < 4096) अणु
		csr6 &= ~DMA_CONTROL_EFC;
		pr_debug("GMAC: disabling flow control, rxfifo too small(%d)\n",
			 rxfअगरosz);
	पूर्ण अन्यथा अणु
		csr6 |= DMA_CONTROL_EFC;
		csr6 |= RFA_FULL_MINUS_1K;
		csr6 |= RFD_FULL_MINUS_2K;
	पूर्ण
	वापस csr6;
पूर्ण

अटल व्योम dwmac1000_dma_operation_mode_rx(व्योम __iomem *ioaddr, पूर्णांक mode,
					    u32 channel, पूर्णांक fअगरosz, u8 qmode)
अणु
	u32 csr6 = पढ़ोl(ioaddr + DMA_CONTROL);

	अगर (mode == SF_DMA_MODE) अणु
		pr_debug("GMAC: enable RX store and forward mode\n");
		csr6 |= DMA_CONTROL_RSF;
	पूर्ण अन्यथा अणु
		pr_debug("GMAC: disable RX SF mode (threshold %d)\n", mode);
		csr6 &= ~DMA_CONTROL_RSF;
		csr6 &= DMA_CONTROL_TC_RX_MASK;
		अगर (mode <= 32)
			csr6 |= DMA_CONTROL_RTC_32;
		अन्यथा अगर (mode <= 64)
			csr6 |= DMA_CONTROL_RTC_64;
		अन्यथा अगर (mode <= 96)
			csr6 |= DMA_CONTROL_RTC_96;
		अन्यथा
			csr6 |= DMA_CONTROL_RTC_128;
	पूर्ण

	/* Configure flow control based on rx fअगरo size */
	csr6 = dwmac1000_configure_fc(csr6, fअगरosz);

	ग_लिखोl(csr6, ioaddr + DMA_CONTROL);
पूर्ण

अटल व्योम dwmac1000_dma_operation_mode_tx(व्योम __iomem *ioaddr, पूर्णांक mode,
					    u32 channel, पूर्णांक fअगरosz, u8 qmode)
अणु
	u32 csr6 = पढ़ोl(ioaddr + DMA_CONTROL);

	अगर (mode == SF_DMA_MODE) अणु
		pr_debug("GMAC: enable TX store and forward mode\n");
		/* Transmit COE type 2 cannot be करोne in cut-through mode. */
		csr6 |= DMA_CONTROL_TSF;
		/* Operating on second frame increase the perक्रमmance
		 * especially when transmit store-and-क्रमward is used.
		 */
		csr6 |= DMA_CONTROL_OSF;
	पूर्ण अन्यथा अणु
		pr_debug("GMAC: disabling TX SF (threshold %d)\n", mode);
		csr6 &= ~DMA_CONTROL_TSF;
		csr6 &= DMA_CONTROL_TC_TX_MASK;
		/* Set the transmit threshold */
		अगर (mode <= 32)
			csr6 |= DMA_CONTROL_TTC_32;
		अन्यथा अगर (mode <= 64)
			csr6 |= DMA_CONTROL_TTC_64;
		अन्यथा अगर (mode <= 128)
			csr6 |= DMA_CONTROL_TTC_128;
		अन्यथा अगर (mode <= 192)
			csr6 |= DMA_CONTROL_TTC_192;
		अन्यथा
			csr6 |= DMA_CONTROL_TTC_256;
	पूर्ण

	ग_लिखोl(csr6, ioaddr + DMA_CONTROL);
पूर्ण

अटल व्योम dwmac1000_dump_dma_regs(व्योम __iomem *ioaddr, u32 *reg_space)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < NUM_DWMAC1000_DMA_REGS; i++)
		अगर ((i < 12) || (i > 17))
			reg_space[DMA_BUS_MODE / 4 + i] =
				पढ़ोl(ioaddr + DMA_BUS_MODE + i * 4);
पूर्ण

अटल व्योम dwmac1000_get_hw_feature(व्योम __iomem *ioaddr,
				     काष्ठा dma_features *dma_cap)
अणु
	u32 hw_cap = पढ़ोl(ioaddr + DMA_HW_FEATURE);

	dma_cap->mbps_10_100 = (hw_cap & DMA_HW_FEAT_MIISEL);
	dma_cap->mbps_1000 = (hw_cap & DMA_HW_FEAT_GMIISEL) >> 1;
	dma_cap->half_duplex = (hw_cap & DMA_HW_FEAT_HDSEL) >> 2;
	dma_cap->hash_filter = (hw_cap & DMA_HW_FEAT_HASHSEL) >> 4;
	dma_cap->multi_addr = (hw_cap & DMA_HW_FEAT_ADDMAC) >> 5;
	dma_cap->pcs = (hw_cap & DMA_HW_FEAT_PCSSEL) >> 6;
	dma_cap->sma_mdio = (hw_cap & DMA_HW_FEAT_SMASEL) >> 8;
	dma_cap->pmt_remote_wake_up = (hw_cap & DMA_HW_FEAT_RWKSEL) >> 9;
	dma_cap->pmt_magic_frame = (hw_cap & DMA_HW_FEAT_MGKSEL) >> 10;
	/* MMC */
	dma_cap->rmon = (hw_cap & DMA_HW_FEAT_MMCSEL) >> 11;
	/* IEEE 1588-2002 */
	dma_cap->समय_stamp =
	    (hw_cap & DMA_HW_FEAT_TSVER1SEL) >> 12;
	/* IEEE 1588-2008 */
	dma_cap->aसमय_stamp = (hw_cap & DMA_HW_FEAT_TSVER2SEL) >> 13;
	/* 802.3az - Energy-Efficient Ethernet (EEE) */
	dma_cap->eee = (hw_cap & DMA_HW_FEAT_EEESEL) >> 14;
	dma_cap->av = (hw_cap & DMA_HW_FEAT_AVSEL) >> 15;
	/* TX and RX csum */
	dma_cap->tx_coe = (hw_cap & DMA_HW_FEAT_TXCOESEL) >> 16;
	dma_cap->rx_coe_type1 = (hw_cap & DMA_HW_FEAT_RXTYP1COE) >> 17;
	dma_cap->rx_coe_type2 = (hw_cap & DMA_HW_FEAT_RXTYP2COE) >> 18;
	dma_cap->rxfअगरo_over_2048 = (hw_cap & DMA_HW_FEAT_RXFIFOSIZE) >> 19;
	/* TX and RX number of channels */
	dma_cap->number_rx_channel = (hw_cap & DMA_HW_FEAT_RXCHCNT) >> 20;
	dma_cap->number_tx_channel = (hw_cap & DMA_HW_FEAT_TXCHCNT) >> 22;
	/* Alternate (enhanced) DESC mode */
	dma_cap->enh_desc = (hw_cap & DMA_HW_FEAT_ENHDESSEL) >> 24;
पूर्ण

अटल व्योम dwmac1000_rx_watchकरोg(व्योम __iomem *ioaddr, u32 riwt,
				  u32 queue)
अणु
	ग_लिखोl(riwt, ioaddr + DMA_RX_WATCHDOG);
पूर्ण

स्थिर काष्ठा sपंचांगmac_dma_ops dwmac1000_dma_ops = अणु
	.reset = dwmac_dma_reset,
	.init = dwmac1000_dma_init,
	.init_rx_chan = dwmac1000_dma_init_rx,
	.init_tx_chan = dwmac1000_dma_init_tx,
	.axi = dwmac1000_dma_axi,
	.dump_regs = dwmac1000_dump_dma_regs,
	.dma_rx_mode = dwmac1000_dma_operation_mode_rx,
	.dma_tx_mode = dwmac1000_dma_operation_mode_tx,
	.enable_dma_transmission = dwmac_enable_dma_transmission,
	.enable_dma_irq = dwmac_enable_dma_irq,
	.disable_dma_irq = dwmac_disable_dma_irq,
	.start_tx = dwmac_dma_start_tx,
	.stop_tx = dwmac_dma_stop_tx,
	.start_rx = dwmac_dma_start_rx,
	.stop_rx = dwmac_dma_stop_rx,
	.dma_पूर्णांकerrupt = dwmac_dma_पूर्णांकerrupt,
	.get_hw_feature = dwmac1000_get_hw_feature,
	.rx_watchकरोg = dwmac1000_rx_watchकरोg,
पूर्ण;
