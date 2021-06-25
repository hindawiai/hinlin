<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2007-2015  STMicroelectronics Ltd
 *
 * Author: Alexandre Torgue <alexandre.torgue@st.com>
 */

#समावेश <linux/पन.स>
#समावेश <linux/iopoll.h>
#समावेश <linux/delay.h>
#समावेश "common.h"
#समावेश "dwmac4_dma.h"
#समावेश "dwmac4.h"

पूर्णांक dwmac4_dma_reset(व्योम __iomem *ioaddr)
अणु
	u32 value = पढ़ोl(ioaddr + DMA_BUS_MODE);

	/* DMA SW reset */
	value |= DMA_BUS_MODE_SFT_RESET;
	ग_लिखोl(value, ioaddr + DMA_BUS_MODE);

	वापस पढ़ोl_poll_समयout(ioaddr + DMA_BUS_MODE, value,
				 !(value & DMA_BUS_MODE_SFT_RESET),
				 10000, 1000000);
पूर्ण

व्योम dwmac4_set_rx_tail_ptr(व्योम __iomem *ioaddr, u32 tail_ptr, u32 chan)
अणु
	ग_लिखोl(tail_ptr, ioaddr + DMA_CHAN_RX_END_ADDR(chan));
पूर्ण

व्योम dwmac4_set_tx_tail_ptr(व्योम __iomem *ioaddr, u32 tail_ptr, u32 chan)
अणु
	ग_लिखोl(tail_ptr, ioaddr + DMA_CHAN_TX_END_ADDR(chan));
पूर्ण

व्योम dwmac4_dma_start_tx(व्योम __iomem *ioaddr, u32 chan)
अणु
	u32 value = पढ़ोl(ioaddr + DMA_CHAN_TX_CONTROL(chan));

	value |= DMA_CONTROL_ST;
	ग_लिखोl(value, ioaddr + DMA_CHAN_TX_CONTROL(chan));

	value = पढ़ोl(ioaddr + GMAC_CONFIG);
	value |= GMAC_CONFIG_TE;
	ग_लिखोl(value, ioaddr + GMAC_CONFIG);
पूर्ण

व्योम dwmac4_dma_stop_tx(व्योम __iomem *ioaddr, u32 chan)
अणु
	u32 value = पढ़ोl(ioaddr + DMA_CHAN_TX_CONTROL(chan));

	value &= ~DMA_CONTROL_ST;
	ग_लिखोl(value, ioaddr + DMA_CHAN_TX_CONTROL(chan));
पूर्ण

व्योम dwmac4_dma_start_rx(व्योम __iomem *ioaddr, u32 chan)
अणु
	u32 value = पढ़ोl(ioaddr + DMA_CHAN_RX_CONTROL(chan));

	value |= DMA_CONTROL_SR;

	ग_लिखोl(value, ioaddr + DMA_CHAN_RX_CONTROL(chan));

	value = पढ़ोl(ioaddr + GMAC_CONFIG);
	value |= GMAC_CONFIG_RE;
	ग_लिखोl(value, ioaddr + GMAC_CONFIG);
पूर्ण

व्योम dwmac4_dma_stop_rx(व्योम __iomem *ioaddr, u32 chan)
अणु
	u32 value = पढ़ोl(ioaddr + DMA_CHAN_RX_CONTROL(chan));

	value &= ~DMA_CONTROL_SR;
	ग_लिखोl(value, ioaddr + DMA_CHAN_RX_CONTROL(chan));
पूर्ण

व्योम dwmac4_set_tx_ring_len(व्योम __iomem *ioaddr, u32 len, u32 chan)
अणु
	ग_लिखोl(len, ioaddr + DMA_CHAN_TX_RING_LEN(chan));
पूर्ण

व्योम dwmac4_set_rx_ring_len(व्योम __iomem *ioaddr, u32 len, u32 chan)
अणु
	ग_लिखोl(len, ioaddr + DMA_CHAN_RX_RING_LEN(chan));
पूर्ण

व्योम dwmac4_enable_dma_irq(व्योम __iomem *ioaddr, u32 chan, bool rx, bool tx)
अणु
	u32 value = पढ़ोl(ioaddr + DMA_CHAN_INTR_ENA(chan));

	अगर (rx)
		value |= DMA_CHAN_INTR_DEFAULT_RX;
	अगर (tx)
		value |= DMA_CHAN_INTR_DEFAULT_TX;

	ग_लिखोl(value, ioaddr + DMA_CHAN_INTR_ENA(chan));
पूर्ण

व्योम dwmac410_enable_dma_irq(व्योम __iomem *ioaddr, u32 chan, bool rx, bool tx)
अणु
	u32 value = पढ़ोl(ioaddr + DMA_CHAN_INTR_ENA(chan));

	अगर (rx)
		value |= DMA_CHAN_INTR_DEFAULT_RX_4_10;
	अगर (tx)
		value |= DMA_CHAN_INTR_DEFAULT_TX_4_10;

	ग_लिखोl(value, ioaddr + DMA_CHAN_INTR_ENA(chan));
पूर्ण

व्योम dwmac4_disable_dma_irq(व्योम __iomem *ioaddr, u32 chan, bool rx, bool tx)
अणु
	u32 value = पढ़ोl(ioaddr + DMA_CHAN_INTR_ENA(chan));

	अगर (rx)
		value &= ~DMA_CHAN_INTR_DEFAULT_RX;
	अगर (tx)
		value &= ~DMA_CHAN_INTR_DEFAULT_TX;

	ग_लिखोl(value, ioaddr + DMA_CHAN_INTR_ENA(chan));
पूर्ण

व्योम dwmac410_disable_dma_irq(व्योम __iomem *ioaddr, u32 chan, bool rx, bool tx)
अणु
	u32 value = पढ़ोl(ioaddr + DMA_CHAN_INTR_ENA(chan));

	अगर (rx)
		value &= ~DMA_CHAN_INTR_DEFAULT_RX_4_10;
	अगर (tx)
		value &= ~DMA_CHAN_INTR_DEFAULT_TX_4_10;

	ग_लिखोl(value, ioaddr + DMA_CHAN_INTR_ENA(chan));
पूर्ण

पूर्णांक dwmac4_dma_पूर्णांकerrupt(व्योम __iomem *ioaddr,
			 काष्ठा sपंचांगmac_extra_stats *x, u32 chan, u32 dir)
अणु
	u32 पूर्णांकr_status = पढ़ोl(ioaddr + DMA_CHAN_STATUS(chan));
	u32 पूर्णांकr_en = पढ़ोl(ioaddr + DMA_CHAN_INTR_ENA(chan));
	पूर्णांक ret = 0;

	अगर (dir == DMA_सूची_RX)
		पूर्णांकr_status &= DMA_CHAN_STATUS_MSK_RX;
	अन्यथा अगर (dir == DMA_सूची_TX)
		पूर्णांकr_status &= DMA_CHAN_STATUS_MSK_TX;

	/* ABNORMAL पूर्णांकerrupts */
	अगर (unlikely(पूर्णांकr_status & DMA_CHAN_STATUS_AIS)) अणु
		अगर (unlikely(पूर्णांकr_status & DMA_CHAN_STATUS_RBU))
			x->rx_buf_unav_irq++;
		अगर (unlikely(पूर्णांकr_status & DMA_CHAN_STATUS_RPS))
			x->rx_process_stopped_irq++;
		अगर (unlikely(पूर्णांकr_status & DMA_CHAN_STATUS_RWT))
			x->rx_watchकरोg_irq++;
		अगर (unlikely(पूर्णांकr_status & DMA_CHAN_STATUS_ETI))
			x->tx_early_irq++;
		अगर (unlikely(पूर्णांकr_status & DMA_CHAN_STATUS_TPS)) अणु
			x->tx_process_stopped_irq++;
			ret = tx_hard_error;
		पूर्ण
		अगर (unlikely(पूर्णांकr_status & DMA_CHAN_STATUS_FBE)) अणु
			x->fatal_bus_error_irq++;
			ret = tx_hard_error;
		पूर्ण
	पूर्ण
	/* TX/RX NORMAL पूर्णांकerrupts */
	अगर (likely(पूर्णांकr_status & DMA_CHAN_STATUS_NIS))
		x->normal_irq_n++;
	अगर (likely(पूर्णांकr_status & DMA_CHAN_STATUS_RI)) अणु
		x->rx_normal_irq_n++;
		ret |= handle_rx;
	पूर्ण
	अगर (likely(पूर्णांकr_status & (DMA_CHAN_STATUS_TI |
		DMA_CHAN_STATUS_TBU))) अणु
		x->tx_normal_irq_n++;
		ret |= handle_tx;
	पूर्ण
	अगर (unlikely(पूर्णांकr_status & DMA_CHAN_STATUS_ERI))
		x->rx_early_irq++;

	ग_लिखोl(पूर्णांकr_status & पूर्णांकr_en, ioaddr + DMA_CHAN_STATUS(chan));
	वापस ret;
पूर्ण

व्योम sपंचांगmac_dwmac4_set_mac_addr(व्योम __iomem *ioaddr, u8 addr[6],
				अचिन्हित पूर्णांक high, अचिन्हित पूर्णांक low)
अणु
	अचिन्हित दीर्घ data;

	data = (addr[5] << 8) | addr[4];
	/* For MAC Addr रेजिस्टरs se have to set the Address Enable (AE)
	 * bit that has no effect on the High Reg 0 where the bit 31 (MO)
	 * is RO.
	 */
	data |= (STMMAC_CHAN0 << GMAC_HI_DCS_SHIFT);
	ग_लिखोl(data | GMAC_HI_REG_AE, ioaddr + high);
	data = (addr[3] << 24) | (addr[2] << 16) | (addr[1] << 8) | addr[0];
	ग_लिखोl(data, ioaddr + low);
पूर्ण

/* Enable disable MAC RX/TX */
व्योम sपंचांगmac_dwmac4_set_mac(व्योम __iomem *ioaddr, bool enable)
अणु
	u32 value = पढ़ोl(ioaddr + GMAC_CONFIG);

	अगर (enable)
		value |= GMAC_CONFIG_RE | GMAC_CONFIG_TE;
	अन्यथा
		value &= ~(GMAC_CONFIG_TE | GMAC_CONFIG_RE);

	ग_लिखोl(value, ioaddr + GMAC_CONFIG);
पूर्ण

व्योम sपंचांगmac_dwmac4_get_mac_addr(व्योम __iomem *ioaddr, अचिन्हित अक्षर *addr,
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
