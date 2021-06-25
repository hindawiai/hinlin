<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*******************************************************************************
  Copyright (C) 2007-2009  STMicroelectronics Ltd


  Author: Giuseppe Cavallaro <peppe.cavallaro@st.com>
*******************************************************************************/

#समावेश <linux/पन.स>
#समावेश <linux/iopoll.h>
#समावेश "common.h"
#समावेश "dwmac_dma.h"

#घोषणा GMAC_HI_REG_AE		0x80000000

पूर्णांक dwmac_dma_reset(व्योम __iomem *ioaddr)
अणु
	u32 value = पढ़ोl(ioaddr + DMA_BUS_MODE);

	/* DMA SW reset */
	value |= DMA_BUS_MODE_SFT_RESET;
	ग_लिखोl(value, ioaddr + DMA_BUS_MODE);

	वापस पढ़ोl_poll_समयout(ioaddr + DMA_BUS_MODE, value,
				 !(value & DMA_BUS_MODE_SFT_RESET),
				 10000, 200000);
पूर्ण

/* CSR1 enables the transmit DMA to check क्रम new descriptor */
व्योम dwmac_enable_dma_transmission(व्योम __iomem *ioaddr)
अणु
	ग_लिखोl(1, ioaddr + DMA_XMT_POLL_DEMAND);
पूर्ण

व्योम dwmac_enable_dma_irq(व्योम __iomem *ioaddr, u32 chan, bool rx, bool tx)
अणु
	u32 value = पढ़ोl(ioaddr + DMA_INTR_ENA);

	अगर (rx)
		value |= DMA_INTR_DEFAULT_RX;
	अगर (tx)
		value |= DMA_INTR_DEFAULT_TX;

	ग_लिखोl(value, ioaddr + DMA_INTR_ENA);
पूर्ण

व्योम dwmac_disable_dma_irq(व्योम __iomem *ioaddr, u32 chan, bool rx, bool tx)
अणु
	u32 value = पढ़ोl(ioaddr + DMA_INTR_ENA);

	अगर (rx)
		value &= ~DMA_INTR_DEFAULT_RX;
	अगर (tx)
		value &= ~DMA_INTR_DEFAULT_TX;

	ग_लिखोl(value, ioaddr + DMA_INTR_ENA);
पूर्ण

व्योम dwmac_dma_start_tx(व्योम __iomem *ioaddr, u32 chan)
अणु
	u32 value = पढ़ोl(ioaddr + DMA_CONTROL);
	value |= DMA_CONTROL_ST;
	ग_लिखोl(value, ioaddr + DMA_CONTROL);
पूर्ण

व्योम dwmac_dma_stop_tx(व्योम __iomem *ioaddr, u32 chan)
अणु
	u32 value = पढ़ोl(ioaddr + DMA_CONTROL);
	value &= ~DMA_CONTROL_ST;
	ग_लिखोl(value, ioaddr + DMA_CONTROL);
पूर्ण

व्योम dwmac_dma_start_rx(व्योम __iomem *ioaddr, u32 chan)
अणु
	u32 value = पढ़ोl(ioaddr + DMA_CONTROL);
	value |= DMA_CONTROL_SR;
	ग_लिखोl(value, ioaddr + DMA_CONTROL);
पूर्ण

व्योम dwmac_dma_stop_rx(व्योम __iomem *ioaddr, u32 chan)
अणु
	u32 value = पढ़ोl(ioaddr + DMA_CONTROL);
	value &= ~DMA_CONTROL_SR;
	ग_लिखोl(value, ioaddr + DMA_CONTROL);
पूर्ण

#अगर_घोषित DWMAC_DMA_DEBUG
अटल व्योम show_tx_process_state(अचिन्हित पूर्णांक status)
अणु
	अचिन्हित पूर्णांक state;
	state = (status & DMA_STATUS_TS_MASK) >> DMA_STATUS_TS_SHIFT;

	चयन (state) अणु
	हाल 0:
		pr_debug("- TX (Stopped): Reset or Stop command\n");
		अवरोध;
	हाल 1:
		pr_debug("- TX (Running): Fetching the Tx desc\n");
		अवरोध;
	हाल 2:
		pr_debug("- TX (Running): Waiting for end of tx\n");
		अवरोध;
	हाल 3:
		pr_debug("- TX (Running): Reading the data "
		       "and queuing the data into the Tx buf\n");
		अवरोध;
	हाल 6:
		pr_debug("- TX (Suspended): Tx Buff Underflow "
		       "or an unavailable Transmit descriptor\n");
		अवरोध;
	हाल 7:
		pr_debug("- TX (Running): Closing Tx descriptor\n");
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम show_rx_process_state(अचिन्हित पूर्णांक status)
अणु
	अचिन्हित पूर्णांक state;
	state = (status & DMA_STATUS_RS_MASK) >> DMA_STATUS_RS_SHIFT;

	चयन (state) अणु
	हाल 0:
		pr_debug("- RX (Stopped): Reset or Stop command\n");
		अवरोध;
	हाल 1:
		pr_debug("- RX (Running): Fetching the Rx desc\n");
		अवरोध;
	हाल 2:
		pr_debug("- RX (Running): Checking for end of pkt\n");
		अवरोध;
	हाल 3:
		pr_debug("- RX (Running): Waiting for Rx pkt\n");
		अवरोध;
	हाल 4:
		pr_debug("- RX (Suspended): Unavailable Rx buf\n");
		अवरोध;
	हाल 5:
		pr_debug("- RX (Running): Closing Rx descriptor\n");
		अवरोध;
	हाल 6:
		pr_debug("- RX(Running): Flushing the current frame"
		       " from the Rx buf\n");
		अवरोध;
	हाल 7:
		pr_debug("- RX (Running): Queuing the Rx frame"
		       " from the Rx buf into memory\n");
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण
#पूर्ण_अगर

पूर्णांक dwmac_dma_पूर्णांकerrupt(व्योम __iomem *ioaddr,
			काष्ठा sपंचांगmac_extra_stats *x, u32 chan, u32 dir)
अणु
	पूर्णांक ret = 0;
	/* पढ़ो the status रेजिस्टर (CSR5) */
	u32 पूर्णांकr_status = पढ़ोl(ioaddr + DMA_STATUS);

#अगर_घोषित DWMAC_DMA_DEBUG
	/* Enable it to monitor DMA rx/tx status in हाल of critical problems */
	pr_debug("%s: [CSR5: 0x%08x]\n", __func__, पूर्णांकr_status);
	show_tx_process_state(पूर्णांकr_status);
	show_rx_process_state(पूर्णांकr_status);
#पूर्ण_अगर

	अगर (dir == DMA_सूची_RX)
		पूर्णांकr_status &= DMA_STATUS_MSK_RX;
	अन्यथा अगर (dir == DMA_सूची_TX)
		पूर्णांकr_status &= DMA_STATUS_MSK_TX;

	/* ABNORMAL पूर्णांकerrupts */
	अगर (unlikely(पूर्णांकr_status & DMA_STATUS_AIS)) अणु
		अगर (unlikely(पूर्णांकr_status & DMA_STATUS_UNF)) अणु
			ret = tx_hard_error_bump_tc;
			x->tx_undeflow_irq++;
		पूर्ण
		अगर (unlikely(पूर्णांकr_status & DMA_STATUS_TJT))
			x->tx_jabber_irq++;

		अगर (unlikely(पूर्णांकr_status & DMA_STATUS_OVF))
			x->rx_overflow_irq++;

		अगर (unlikely(पूर्णांकr_status & DMA_STATUS_RU))
			x->rx_buf_unav_irq++;
		अगर (unlikely(पूर्णांकr_status & DMA_STATUS_RPS))
			x->rx_process_stopped_irq++;
		अगर (unlikely(पूर्णांकr_status & DMA_STATUS_RWT))
			x->rx_watchकरोg_irq++;
		अगर (unlikely(पूर्णांकr_status & DMA_STATUS_ETI))
			x->tx_early_irq++;
		अगर (unlikely(पूर्णांकr_status & DMA_STATUS_TPS)) अणु
			x->tx_process_stopped_irq++;
			ret = tx_hard_error;
		पूर्ण
		अगर (unlikely(पूर्णांकr_status & DMA_STATUS_FBI)) अणु
			x->fatal_bus_error_irq++;
			ret = tx_hard_error;
		पूर्ण
	पूर्ण
	/* TX/RX NORMAL पूर्णांकerrupts */
	अगर (likely(पूर्णांकr_status & DMA_STATUS_NIS)) अणु
		x->normal_irq_n++;
		अगर (likely(पूर्णांकr_status & DMA_STATUS_RI)) अणु
			u32 value = पढ़ोl(ioaddr + DMA_INTR_ENA);
			/* to schedule NAPI on real RIE event. */
			अगर (likely(value & DMA_INTR_ENA_RIE)) अणु
				x->rx_normal_irq_n++;
				ret |= handle_rx;
			पूर्ण
		पूर्ण
		अगर (likely(पूर्णांकr_status & DMA_STATUS_TI)) अणु
			x->tx_normal_irq_n++;
			ret |= handle_tx;
		पूर्ण
		अगर (unlikely(पूर्णांकr_status & DMA_STATUS_ERI))
			x->rx_early_irq++;
	पूर्ण
	/* Optional hardware blocks, पूर्णांकerrupts should be disabled */
	अगर (unlikely(पूर्णांकr_status &
		     (DMA_STATUS_GPI | DMA_STATUS_GMI | DMA_STATUS_GLI)))
		pr_warn("%s: unexpected status %08x\n", __func__, पूर्णांकr_status);

	/* Clear the पूर्णांकerrupt by writing a logic 1 to the CSR5[15-0] */
	ग_लिखोl((पूर्णांकr_status & 0x1ffff), ioaddr + DMA_STATUS);

	वापस ret;
पूर्ण

व्योम dwmac_dma_flush_tx_fअगरo(व्योम __iomem *ioaddr)
अणु
	u32 csr6 = पढ़ोl(ioaddr + DMA_CONTROL);
	ग_लिखोl((csr6 | DMA_CONTROL_FTF), ioaddr + DMA_CONTROL);

	करो अणुपूर्ण जबतक ((पढ़ोl(ioaddr + DMA_CONTROL) & DMA_CONTROL_FTF));
पूर्ण

व्योम sपंचांगmac_set_mac_addr(व्योम __iomem *ioaddr, u8 addr[6],
			 अचिन्हित पूर्णांक high, अचिन्हित पूर्णांक low)
अणु
	अचिन्हित दीर्घ data;

	data = (addr[5] << 8) | addr[4];
	/* For MAC Addr रेजिस्टरs we have to set the Address Enable (AE)
	 * bit that has no effect on the High Reg 0 where the bit 31 (MO)
	 * is RO.
	 */
	ग_लिखोl(data | GMAC_HI_REG_AE, ioaddr + high);
	data = (addr[3] << 24) | (addr[2] << 16) | (addr[1] << 8) | addr[0];
	ग_लिखोl(data, ioaddr + low);
पूर्ण
EXPORT_SYMBOL_GPL(sपंचांगmac_set_mac_addr);

/* Enable disable MAC RX/TX */
व्योम sपंचांगmac_set_mac(व्योम __iomem *ioaddr, bool enable)
अणु
	u32 value = पढ़ोl(ioaddr + MAC_CTRL_REG);

	अगर (enable)
		value |= MAC_ENABLE_RX | MAC_ENABLE_TX;
	अन्यथा
		value &= ~(MAC_ENABLE_TX | MAC_ENABLE_RX);

	ग_लिखोl(value, ioaddr + MAC_CTRL_REG);
पूर्ण

व्योम sपंचांगmac_get_mac_addr(व्योम __iomem *ioaddr, अचिन्हित अक्षर *addr,
			 अचिन्हित पूर्णांक high, अचिन्हित पूर्णांक low)
अणु
	अचिन्हित पूर्णांक hi_addr, lo_addr;

	/* Read the MAC address from the hardware */
	hi_addr = पढ़ोl(ioaddr + high);
	lo_addr = पढ़ोl(ioaddr + low);

	/* Extract the MAC address from the high and low words */
	addr[0] = lo_addr & 0xff;
	addr[1] = (lo_addr >> 8) & 0xff;
	addr[2] = (lo_addr >> 16) & 0xff;
	addr[3] = (lo_addr >> 24) & 0xff;
	addr[4] = hi_addr & 0xff;
	addr[5] = (hi_addr >> 8) & 0xff;
पूर्ण
EXPORT_SYMBOL_GPL(sपंचांगmac_get_mac_addr);
