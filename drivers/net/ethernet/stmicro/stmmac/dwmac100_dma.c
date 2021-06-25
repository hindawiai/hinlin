<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*******************************************************************************
  This is the driver क्रम the MAC 10/100 on-chip Ethernet controller
  currently tested on all the ST boards based on STb7109 and stx7200 SoCs.

  DWC Ether MAC 10/100 Universal version 4.0 has been used क्रम developing
  this code.

  This contains the functions to handle the dma.

  Copyright (C) 2007-2009  STMicroelectronics Ltd


  Author: Giuseppe Cavallaro <peppe.cavallaro@st.com>
*******************************************************************************/

#समावेश <यंत्र/पन.स>
#समावेश "dwmac100.h"
#समावेश "dwmac_dma.h"

अटल व्योम dwmac100_dma_init(व्योम __iomem *ioaddr,
			      काष्ठा sपंचांगmac_dma_cfg *dma_cfg, पूर्णांक atds)
अणु
	/* Enable Application Access by writing to DMA CSR0 */
	ग_लिखोl(DMA_BUS_MODE_DEFAULT | (dma_cfg->pbl << DMA_BUS_MODE_PBL_SHIFT),
	       ioaddr + DMA_BUS_MODE);

	/* Mask पूर्णांकerrupts by writing to CSR7 */
	ग_लिखोl(DMA_INTR_DEFAULT_MASK, ioaddr + DMA_INTR_ENA);
पूर्ण

अटल व्योम dwmac100_dma_init_rx(व्योम __iomem *ioaddr,
				 काष्ठा sपंचांगmac_dma_cfg *dma_cfg,
				 dma_addr_t dma_rx_phy, u32 chan)
अणु
	/* RX descriptor base addr lists must be written पूर्णांकo DMA CSR3 */
	ग_लिखोl(lower_32_bits(dma_rx_phy), ioaddr + DMA_RCV_BASE_ADDR);
पूर्ण

अटल व्योम dwmac100_dma_init_tx(व्योम __iomem *ioaddr,
				 काष्ठा sपंचांगmac_dma_cfg *dma_cfg,
				 dma_addr_t dma_tx_phy, u32 chan)
अणु
	/* TX descriptor base addr lists must be written पूर्णांकo DMA CSR4 */
	ग_लिखोl(lower_32_bits(dma_tx_phy), ioaddr + DMA_TX_BASE_ADDR);
पूर्ण

/* Store and Forward capability is not used at all.
 *
 * The transmit threshold can be programmed by setting the TTC bits in the DMA
 * control रेजिस्टर.
 */
अटल व्योम dwmac100_dma_operation_mode_tx(व्योम __iomem *ioaddr, पूर्णांक mode,
					   u32 channel, पूर्णांक fअगरosz, u8 qmode)
अणु
	u32 csr6 = पढ़ोl(ioaddr + DMA_CONTROL);

	अगर (mode <= 32)
		csr6 |= DMA_CONTROL_TTC_32;
	अन्यथा अगर (mode <= 64)
		csr6 |= DMA_CONTROL_TTC_64;
	अन्यथा
		csr6 |= DMA_CONTROL_TTC_128;

	ग_लिखोl(csr6, ioaddr + DMA_CONTROL);
पूर्ण

अटल व्योम dwmac100_dump_dma_regs(व्योम __iomem *ioaddr, u32 *reg_space)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < NUM_DWMAC100_DMA_REGS; i++)
		reg_space[DMA_BUS_MODE / 4 + i] =
			पढ़ोl(ioaddr + DMA_BUS_MODE + i * 4);

	reg_space[DMA_CUR_TX_BUF_ADDR / 4] =
		पढ़ोl(ioaddr + DMA_CUR_TX_BUF_ADDR);
	reg_space[DMA_CUR_RX_BUF_ADDR / 4] =
		पढ़ोl(ioaddr + DMA_CUR_RX_BUF_ADDR);
पूर्ण

/* DMA controller has two counters to track the number of the missed frames. */
अटल व्योम dwmac100_dma_diagnostic_fr(व्योम *data, काष्ठा sपंचांगmac_extra_stats *x,
				       व्योम __iomem *ioaddr)
अणु
	काष्ठा net_device_stats *stats = (काष्ठा net_device_stats *)data;
	u32 csr8 = पढ़ोl(ioaddr + DMA_MISSED_FRAME_CTR);

	अगर (unlikely(csr8)) अणु
		अगर (csr8 & DMA_MISSED_FRAME_OVE) अणु
			stats->rx_over_errors += 0x800;
			x->rx_overflow_cntr += 0x800;
		पूर्ण अन्यथा अणु
			अचिन्हित पूर्णांक ove_cntr;
			ove_cntr = ((csr8 & DMA_MISSED_FRAME_OVE_CNTR) >> 17);
			stats->rx_over_errors += ove_cntr;
			x->rx_overflow_cntr += ove_cntr;
		पूर्ण

		अगर (csr8 & DMA_MISSED_FRAME_OVE_M) अणु
			stats->rx_missed_errors += 0xffff;
			x->rx_missed_cntr += 0xffff;
		पूर्ण अन्यथा अणु
			अचिन्हित पूर्णांक miss_f = (csr8 & DMA_MISSED_FRAME_M_CNTR);
			stats->rx_missed_errors += miss_f;
			x->rx_missed_cntr += miss_f;
		पूर्ण
	पूर्ण
पूर्ण

स्थिर काष्ठा sपंचांगmac_dma_ops dwmac100_dma_ops = अणु
	.reset = dwmac_dma_reset,
	.init = dwmac100_dma_init,
	.init_rx_chan = dwmac100_dma_init_rx,
	.init_tx_chan = dwmac100_dma_init_tx,
	.dump_regs = dwmac100_dump_dma_regs,
	.dma_tx_mode = dwmac100_dma_operation_mode_tx,
	.dma_diagnostic_fr = dwmac100_dma_diagnostic_fr,
	.enable_dma_transmission = dwmac_enable_dma_transmission,
	.enable_dma_irq = dwmac_enable_dma_irq,
	.disable_dma_irq = dwmac_disable_dma_irq,
	.start_tx = dwmac_dma_start_tx,
	.stop_tx = dwmac_dma_stop_tx,
	.start_rx = dwmac_dma_start_rx,
	.stop_rx = dwmac_dma_stop_rx,
	.dma_पूर्णांकerrupt = dwmac_dma_पूर्णांकerrupt,
पूर्ण;
