<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/*
 * Copyright (c) 2012-2017 Qualcomm Atheros, Inc.
 * Copyright (c) 2018-2019, The Linux Foundation. All rights reserved.
 */

#समावेश <linux/पूर्णांकerrupt.h>

#समावेश "wil6210.h"
#समावेश "trace.h"

/**
 * Theory of operation:
 *
 * There is ISR pseuकरो-cause रेजिस्टर,
 * dma_rgf->DMA_RGF.PSEUDO_CAUSE.PSEUDO_CAUSE
 * Its bits represents OR'ed bits from 3 real ISR रेजिस्टरs:
 * TX, RX, and MISC.
 *
 * Registers may be configured to either "write 1 to clear" or
 * "clear on read" mode
 *
 * When handling पूर्णांकerrupt, one have to mask/unmask पूर्णांकerrupts क्रम the
 * real ISR रेजिस्टरs, or hardware may malfunction.
 *
 */

#घोषणा WIL6210_IRQ_DISABLE		(0xFFFFFFFFUL)
#घोषणा WIL6210_IRQ_DISABLE_NO_HALP	(0xF7FFFFFFUL)
#घोषणा WIL6210_IMC_RX		(BIT_DMA_EP_RX_ICR_RX_DONE | \
				 BIT_DMA_EP_RX_ICR_RX_HTRSH)
#घोषणा WIL6210_IMC_RX_NO_RX_HTRSH (WIL6210_IMC_RX & \
				    (~(BIT_DMA_EP_RX_ICR_RX_HTRSH)))
#घोषणा WIL6210_IMC_TX		(BIT_DMA_EP_TX_ICR_TX_DONE | \
				BIT_DMA_EP_TX_ICR_TX_DONE_N(0))
#घोषणा WIL6210_IMC_TX_EDMA		BIT_TX_STATUS_IRQ
#घोषणा WIL6210_IMC_RX_EDMA		BIT_RX_STATUS_IRQ
#घोषणा WIL6210_IMC_MISC_NO_HALP	(ISR_MISC_FW_READY | \
					 ISR_MISC_MBOX_EVT | \
					 ISR_MISC_FW_ERROR)
#घोषणा WIL6210_IMC_MISC		(WIL6210_IMC_MISC_NO_HALP | \
					 BIT_DMA_EP_MISC_ICR_HALP)
#घोषणा WIL6210_IRQ_PSEUDO_MASK (u32)(~(BIT_DMA_PSEUDO_CAUSE_RX | \
					BIT_DMA_PSEUDO_CAUSE_TX | \
					BIT_DMA_PSEUDO_CAUSE_MISC))

#अगर defined(CONFIG_WIL6210_ISR_COR)
/* configure to Clear-On-Read mode */
#घोषणा WIL_ICR_ICC_VALUE	(0xFFFFFFFFUL)
#घोषणा WIL_ICR_ICC_MISC_VALUE	(0xF7FFFFFFUL)

अटल अंतरभूत व्योम wil_icr_clear(u32 x, व्योम __iomem *addr)
अणु
पूर्ण
#अन्यथा /* defined(CONFIG_WIL6210_ISR_COR) */
/* configure to Write-1-to-Clear mode */
#घोषणा WIL_ICR_ICC_VALUE	(0UL)
#घोषणा WIL_ICR_ICC_MISC_VALUE	(0UL)

अटल अंतरभूत व्योम wil_icr_clear(u32 x, व्योम __iomem *addr)
अणु
	ग_लिखोl(x, addr);
पूर्ण
#पूर्ण_अगर /* defined(CONFIG_WIL6210_ISR_COR) */

अटल अंतरभूत u32 wil_ioपढ़ो32_and_clear(व्योम __iomem *addr)
अणु
	u32 x = पढ़ोl(addr);

	wil_icr_clear(x, addr);

	वापस x;
पूर्ण

अटल व्योम wil6210_mask_irq_tx(काष्ठा wil6210_priv *wil)
अणु
	wil_w(wil, RGF_DMA_EP_TX_ICR + दुरत्व(काष्ठा RGF_ICR, IMS),
	      WIL6210_IRQ_DISABLE);
पूर्ण

अटल व्योम wil6210_mask_irq_tx_edma(काष्ठा wil6210_priv *wil)
अणु
	wil_w(wil, RGF_INT_GEN_TX_ICR + दुरत्व(काष्ठा RGF_ICR, IMS),
	      WIL6210_IRQ_DISABLE);
पूर्ण

अटल व्योम wil6210_mask_irq_rx(काष्ठा wil6210_priv *wil)
अणु
	wil_w(wil, RGF_DMA_EP_RX_ICR + दुरत्व(काष्ठा RGF_ICR, IMS),
	      WIL6210_IRQ_DISABLE);
पूर्ण

अटल व्योम wil6210_mask_irq_rx_edma(काष्ठा wil6210_priv *wil)
अणु
	wil_w(wil, RGF_INT_GEN_RX_ICR + दुरत्व(काष्ठा RGF_ICR, IMS),
	      WIL6210_IRQ_DISABLE);
पूर्ण

अटल व्योम wil6210_mask_irq_misc(काष्ठा wil6210_priv *wil, bool mask_halp)
अणु
	wil_dbg_irq(wil, "mask_irq_misc: mask_halp(%s)\n",
		    mask_halp ? "true" : "false");

	wil_w(wil, RGF_DMA_EP_MISC_ICR + दुरत्व(काष्ठा RGF_ICR, IMS),
	      mask_halp ? WIL6210_IRQ_DISABLE : WIL6210_IRQ_DISABLE_NO_HALP);
पूर्ण

व्योम wil6210_mask_halp(काष्ठा wil6210_priv *wil)
अणु
	wil_dbg_irq(wil, "mask_halp\n");

	wil_w(wil, RGF_DMA_EP_MISC_ICR + दुरत्व(काष्ठा RGF_ICR, IMS),
	      BIT_DMA_EP_MISC_ICR_HALP);
पूर्ण

अटल व्योम wil6210_mask_irq_pseuकरो(काष्ठा wil6210_priv *wil)
अणु
	wil_dbg_irq(wil, "mask_irq_pseudo\n");

	wil_w(wil, RGF_DMA_PSEUDO_CAUSE_MASK_SW, WIL6210_IRQ_DISABLE);

	clear_bit(wil_status_irqen, wil->status);
पूर्ण

व्योम wil6210_unmask_irq_tx(काष्ठा wil6210_priv *wil)
अणु
	wil_w(wil, RGF_DMA_EP_TX_ICR + दुरत्व(काष्ठा RGF_ICR, IMC),
	      WIL6210_IMC_TX);
पूर्ण

व्योम wil6210_unmask_irq_tx_edma(काष्ठा wil6210_priv *wil)
अणु
	wil_w(wil, RGF_INT_GEN_TX_ICR + दुरत्व(काष्ठा RGF_ICR, IMC),
	      WIL6210_IMC_TX_EDMA);
पूर्ण

व्योम wil6210_unmask_irq_rx(काष्ठा wil6210_priv *wil)
अणु
	bool unmask_rx_htrsh = atomic_पढ़ो(&wil->connected_vअगरs) > 0;

	wil_w(wil, RGF_DMA_EP_RX_ICR + दुरत्व(काष्ठा RGF_ICR, IMC),
	      unmask_rx_htrsh ? WIL6210_IMC_RX : WIL6210_IMC_RX_NO_RX_HTRSH);
पूर्ण

व्योम wil6210_unmask_irq_rx_edma(काष्ठा wil6210_priv *wil)
अणु
	wil_w(wil, RGF_INT_GEN_RX_ICR + दुरत्व(काष्ठा RGF_ICR, IMC),
	      WIL6210_IMC_RX_EDMA);
पूर्ण

अटल व्योम wil6210_unmask_irq_misc(काष्ठा wil6210_priv *wil, bool unmask_halp)
अणु
	wil_dbg_irq(wil, "unmask_irq_misc: unmask_halp(%s)\n",
		    unmask_halp ? "true" : "false");

	wil_w(wil, RGF_DMA_EP_MISC_ICR + दुरत्व(काष्ठा RGF_ICR, IMC),
	      unmask_halp ? WIL6210_IMC_MISC : WIL6210_IMC_MISC_NO_HALP);
पूर्ण

अटल व्योम wil6210_unmask_halp(काष्ठा wil6210_priv *wil)
अणु
	wil_dbg_irq(wil, "unmask_halp\n");

	wil_w(wil, RGF_DMA_EP_MISC_ICR + दुरत्व(काष्ठा RGF_ICR, IMC),
	      BIT_DMA_EP_MISC_ICR_HALP);
पूर्ण

अटल व्योम wil6210_unmask_irq_pseuकरो(काष्ठा wil6210_priv *wil)
अणु
	wil_dbg_irq(wil, "unmask_irq_pseudo\n");

	set_bit(wil_status_irqen, wil->status);

	wil_w(wil, RGF_DMA_PSEUDO_CAUSE_MASK_SW, WIL6210_IRQ_PSEUDO_MASK);
पूर्ण

व्योम wil_mask_irq(काष्ठा wil6210_priv *wil)
अणु
	wil_dbg_irq(wil, "mask_irq\n");

	wil6210_mask_irq_tx(wil);
	wil6210_mask_irq_tx_edma(wil);
	wil6210_mask_irq_rx(wil);
	wil6210_mask_irq_rx_edma(wil);
	wil6210_mask_irq_misc(wil, true);
	wil6210_mask_irq_pseuकरो(wil);
पूर्ण

व्योम wil_unmask_irq(काष्ठा wil6210_priv *wil)
अणु
	wil_dbg_irq(wil, "unmask_irq\n");

	wil_w(wil, RGF_DMA_EP_RX_ICR + दुरत्व(काष्ठा RGF_ICR, ICC),
	      WIL_ICR_ICC_VALUE);
	wil_w(wil, RGF_DMA_EP_TX_ICR + दुरत्व(काष्ठा RGF_ICR, ICC),
	      WIL_ICR_ICC_VALUE);
	wil_w(wil, RGF_DMA_EP_MISC_ICR + दुरत्व(काष्ठा RGF_ICR, ICC),
	      WIL_ICR_ICC_MISC_VALUE);
	wil_w(wil, RGF_INT_GEN_TX_ICR + दुरत्व(काष्ठा RGF_ICR, ICC),
	      WIL_ICR_ICC_VALUE);
	wil_w(wil, RGF_INT_GEN_RX_ICR + दुरत्व(काष्ठा RGF_ICR, ICC),
	      WIL_ICR_ICC_VALUE);

	wil6210_unmask_irq_pseuकरो(wil);
	अगर (wil->use_enhanced_dma_hw) अणु
		wil6210_unmask_irq_tx_edma(wil);
		wil6210_unmask_irq_rx_edma(wil);
	पूर्ण अन्यथा अणु
		wil6210_unmask_irq_tx(wil);
		wil6210_unmask_irq_rx(wil);
	पूर्ण
	wil6210_unmask_irq_misc(wil, true);
पूर्ण

व्योम wil_configure_पूर्णांकerrupt_moderation_edma(काष्ठा wil6210_priv *wil)
अणु
	u32 moderation;

	wil_s(wil, RGF_INT_GEN_IDLE_TIME_LIMIT, WIL_EDMA_IDLE_TIME_LIMIT_USEC);

	wil_s(wil, RGF_INT_GEN_TIME_UNIT_LIMIT, WIL_EDMA_TIME_UNIT_CLK_CYCLES);

	/* Update RX and TX moderation */
	moderation = wil->rx_max_burst_duration |
		(WIL_EDMA_AGG_WATERMARK << WIL_EDMA_AGG_WATERMARK_POS);
	wil_w(wil, RGF_INT_CTRL_INT_GEN_CFG_0, moderation);
	wil_w(wil, RGF_INT_CTRL_INT_GEN_CFG_1, moderation);

	/* Treat special events as regular
	 * (set bit 0 to 0x1 and clear bits 1-8)
	 */
	wil_c(wil, RGF_INT_COUNT_ON_SPECIAL_EVT, 0x1FE);
	wil_s(wil, RGF_INT_COUNT_ON_SPECIAL_EVT, 0x1);
पूर्ण

व्योम wil_configure_पूर्णांकerrupt_moderation(काष्ठा wil6210_priv *wil)
अणु
	काष्ठा wireless_dev *wdev = wil->मुख्य_ndev->ieee80211_ptr;

	wil_dbg_irq(wil, "configure_interrupt_moderation\n");

	/* disable पूर्णांकerrupt moderation क्रम monitor
	 * to get better बारtamp precision
	 */
	अगर (wdev->अगरtype == NL80211_IFTYPE_MONITOR)
		वापस;

	/* Disable and clear tx counter beक्रमe (re)configuration */
	wil_w(wil, RGF_DMA_ITR_TX_CNT_CTL, BIT_DMA_ITR_TX_CNT_CTL_CLR);
	wil_w(wil, RGF_DMA_ITR_TX_CNT_TRSH, wil->tx_max_burst_duration);
	wil_info(wil, "set ITR_TX_CNT_TRSH = %d usec\n",
		 wil->tx_max_burst_duration);
	/* Configure TX max burst duration समयr to use usec units */
	wil_w(wil, RGF_DMA_ITR_TX_CNT_CTL,
	      BIT_DMA_ITR_TX_CNT_CTL_EN | BIT_DMA_ITR_TX_CNT_CTL_EXT_TIC_SEL);

	/* Disable and clear tx idle counter beक्रमe (re)configuration */
	wil_w(wil, RGF_DMA_ITR_TX_IDL_CNT_CTL, BIT_DMA_ITR_TX_IDL_CNT_CTL_CLR);
	wil_w(wil, RGF_DMA_ITR_TX_IDL_CNT_TRSH, wil->tx_पूर्णांकerframe_समयout);
	wil_info(wil, "set ITR_TX_IDL_CNT_TRSH = %d usec\n",
		 wil->tx_पूर्णांकerframe_समयout);
	/* Configure TX max burst duration समयr to use usec units */
	wil_w(wil, RGF_DMA_ITR_TX_IDL_CNT_CTL, BIT_DMA_ITR_TX_IDL_CNT_CTL_EN |
	      BIT_DMA_ITR_TX_IDL_CNT_CTL_EXT_TIC_SEL);

	/* Disable and clear rx counter beक्रमe (re)configuration */
	wil_w(wil, RGF_DMA_ITR_RX_CNT_CTL, BIT_DMA_ITR_RX_CNT_CTL_CLR);
	wil_w(wil, RGF_DMA_ITR_RX_CNT_TRSH, wil->rx_max_burst_duration);
	wil_info(wil, "set ITR_RX_CNT_TRSH = %d usec\n",
		 wil->rx_max_burst_duration);
	/* Configure TX max burst duration समयr to use usec units */
	wil_w(wil, RGF_DMA_ITR_RX_CNT_CTL,
	      BIT_DMA_ITR_RX_CNT_CTL_EN | BIT_DMA_ITR_RX_CNT_CTL_EXT_TIC_SEL);

	/* Disable and clear rx idle counter beक्रमe (re)configuration */
	wil_w(wil, RGF_DMA_ITR_RX_IDL_CNT_CTL, BIT_DMA_ITR_RX_IDL_CNT_CTL_CLR);
	wil_w(wil, RGF_DMA_ITR_RX_IDL_CNT_TRSH, wil->rx_पूर्णांकerframe_समयout);
	wil_info(wil, "set ITR_RX_IDL_CNT_TRSH = %d usec\n",
		 wil->rx_पूर्णांकerframe_समयout);
	/* Configure TX max burst duration समयr to use usec units */
	wil_w(wil, RGF_DMA_ITR_RX_IDL_CNT_CTL, BIT_DMA_ITR_RX_IDL_CNT_CTL_EN |
	      BIT_DMA_ITR_RX_IDL_CNT_CTL_EXT_TIC_SEL);
पूर्ण

अटल irqवापस_t wil6210_irq_rx(पूर्णांक irq, व्योम *cookie)
अणु
	काष्ठा wil6210_priv *wil = cookie;
	u32 isr;
	bool need_unmask = true;

	wil6210_mask_irq_rx(wil);

	isr = wil_ioपढ़ो32_and_clear(wil->csr +
				     HOSTADDR(RGF_DMA_EP_RX_ICR) +
				     दुरत्व(काष्ठा RGF_ICR, ICR));

	trace_wil6210_irq_rx(isr);
	wil_dbg_irq(wil, "ISR RX 0x%08x\n", isr);

	अगर (unlikely(!isr)) अणु
		wil_err_ratelimited(wil, "spurious IRQ: RX\n");
		wil6210_unmask_irq_rx(wil);
		वापस IRQ_NONE;
	पूर्ण

	/* RX_DONE and RX_HTRSH पूर्णांकerrupts are the same अगर पूर्णांकerrupt
	 * moderation is not used. Interrupt moderation may cause RX
	 * buffer overflow जबतक RX_DONE is delayed. The required
	 * action is always the same - should empty the accumulated
	 * packets from the RX ring.
	 */
	अगर (likely(isr & (BIT_DMA_EP_RX_ICR_RX_DONE |
			  BIT_DMA_EP_RX_ICR_RX_HTRSH))) अणु
		wil_dbg_irq(wil, "RX done / RX_HTRSH received, ISR (0x%x)\n",
			    isr);

		isr &= ~(BIT_DMA_EP_RX_ICR_RX_DONE |
			 BIT_DMA_EP_RX_ICR_RX_HTRSH);
		अगर (likely(test_bit(wil_status_fwपढ़ोy, wil->status))) अणु
			अगर (likely(test_bit(wil_status_napi_en, wil->status))) अणु
				wil_dbg_txrx(wil, "NAPI(Rx) schedule\n");
				need_unmask = false;
				napi_schedule(&wil->napi_rx);
			पूर्ण अन्यथा अणु
				wil_err_ratelimited(
					wil,
					"Got Rx interrupt while stopping interface\n");
			पूर्ण
		पूर्ण अन्यथा अणु
			wil_err_ratelimited(wil, "Got Rx interrupt while in reset\n");
		पूर्ण
	पूर्ण

	अगर (unlikely(isr))
		wil_err(wil, "un-handled RX ISR bits 0x%08x\n", isr);

	/* Rx IRQ will be enabled when NAPI processing finished */

	atomic_inc(&wil->isr_count_rx);

	अगर (unlikely(need_unmask))
		wil6210_unmask_irq_rx(wil);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t wil6210_irq_rx_edma(पूर्णांक irq, व्योम *cookie)
अणु
	काष्ठा wil6210_priv *wil = cookie;
	u32 isr;
	bool need_unmask = true;

	wil6210_mask_irq_rx_edma(wil);

	isr = wil_ioपढ़ो32_and_clear(wil->csr +
				     HOSTADDR(RGF_INT_GEN_RX_ICR) +
				     दुरत्व(काष्ठा RGF_ICR, ICR));

	trace_wil6210_irq_rx(isr);
	wil_dbg_irq(wil, "ISR RX 0x%08x\n", isr);

	अगर (unlikely(!isr)) अणु
		wil_err(wil, "spurious IRQ: RX\n");
		wil6210_unmask_irq_rx_edma(wil);
		वापस IRQ_NONE;
	पूर्ण

	अगर (likely(isr & BIT_RX_STATUS_IRQ)) अणु
		wil_dbg_irq(wil, "RX status ring\n");
		isr &= ~BIT_RX_STATUS_IRQ;
		अगर (likely(test_bit(wil_status_fwपढ़ोy, wil->status))) अणु
			अगर (likely(test_bit(wil_status_napi_en, wil->status))) अणु
				wil_dbg_txrx(wil, "NAPI(Rx) schedule\n");
				need_unmask = false;
				napi_schedule(&wil->napi_rx);
			पूर्ण अन्यथा अणु
				wil_err(wil,
					"Got Rx interrupt while stopping interface\n");
			पूर्ण
		पूर्ण अन्यथा अणु
			wil_err(wil, "Got Rx interrupt while in reset\n");
		पूर्ण
	पूर्ण

	अगर (unlikely(isr))
		wil_err(wil, "un-handled RX ISR bits 0x%08x\n", isr);

	/* Rx IRQ will be enabled when NAPI processing finished */

	atomic_inc(&wil->isr_count_rx);

	अगर (unlikely(need_unmask))
		wil6210_unmask_irq_rx_edma(wil);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t wil6210_irq_tx_edma(पूर्णांक irq, व्योम *cookie)
अणु
	काष्ठा wil6210_priv *wil = cookie;
	u32 isr;
	bool need_unmask = true;

	wil6210_mask_irq_tx_edma(wil);

	isr = wil_ioपढ़ो32_and_clear(wil->csr +
				     HOSTADDR(RGF_INT_GEN_TX_ICR) +
				     दुरत्व(काष्ठा RGF_ICR, ICR));

	trace_wil6210_irq_tx(isr);
	wil_dbg_irq(wil, "ISR TX 0x%08x\n", isr);

	अगर (unlikely(!isr)) अणु
		wil_err(wil, "spurious IRQ: TX\n");
		wil6210_unmask_irq_tx_edma(wil);
		वापस IRQ_NONE;
	पूर्ण

	अगर (likely(isr & BIT_TX_STATUS_IRQ)) अणु
		wil_dbg_irq(wil, "TX status ring\n");
		isr &= ~BIT_TX_STATUS_IRQ;
		अगर (likely(test_bit(wil_status_fwपढ़ोy, wil->status))) अणु
			wil_dbg_txrx(wil, "NAPI(Tx) schedule\n");
			need_unmask = false;
			napi_schedule(&wil->napi_tx);
		पूर्ण अन्यथा अणु
			wil_err(wil, "Got Tx status ring IRQ while in reset\n");
		पूर्ण
	पूर्ण

	अगर (unlikely(isr))
		wil_err(wil, "un-handled TX ISR bits 0x%08x\n", isr);

	/* Tx IRQ will be enabled when NAPI processing finished */

	atomic_inc(&wil->isr_count_tx);

	अगर (unlikely(need_unmask))
		wil6210_unmask_irq_tx_edma(wil);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t wil6210_irq_tx(पूर्णांक irq, व्योम *cookie)
अणु
	काष्ठा wil6210_priv *wil = cookie;
	u32 isr;
	bool need_unmask = true;

	wil6210_mask_irq_tx(wil);

	isr = wil_ioपढ़ो32_and_clear(wil->csr +
				     HOSTADDR(RGF_DMA_EP_TX_ICR) +
				     दुरत्व(काष्ठा RGF_ICR, ICR));

	trace_wil6210_irq_tx(isr);
	wil_dbg_irq(wil, "ISR TX 0x%08x\n", isr);

	अगर (unlikely(!isr)) अणु
		wil_err_ratelimited(wil, "spurious IRQ: TX\n");
		wil6210_unmask_irq_tx(wil);
		वापस IRQ_NONE;
	पूर्ण

	अगर (likely(isr & BIT_DMA_EP_TX_ICR_TX_DONE)) अणु
		wil_dbg_irq(wil, "TX done\n");
		isr &= ~BIT_DMA_EP_TX_ICR_TX_DONE;
		/* clear also all VRING पूर्णांकerrupts */
		isr &= ~(BIT(25) - 1UL);
		अगर (likely(test_bit(wil_status_fwपढ़ोy, wil->status))) अणु
			wil_dbg_txrx(wil, "NAPI(Tx) schedule\n");
			need_unmask = false;
			napi_schedule(&wil->napi_tx);
		पूर्ण अन्यथा अणु
			wil_err_ratelimited(wil, "Got Tx interrupt while in reset\n");
		पूर्ण
	पूर्ण

	अगर (unlikely(isr))
		wil_err_ratelimited(wil, "un-handled TX ISR bits 0x%08x\n",
				    isr);

	/* Tx IRQ will be enabled when NAPI processing finished */

	atomic_inc(&wil->isr_count_tx);

	अगर (unlikely(need_unmask))
		wil6210_unmask_irq_tx(wil);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम wil_notअगरy_fw_error(काष्ठा wil6210_priv *wil)
अणु
	काष्ठा device *dev = &wil->मुख्य_ndev->dev;
	अक्षर *envp[3] = अणु
		[0] = "SOURCE=wil6210",
		[1] = "EVENT=FW_ERROR",
		[2] = शून्य,
	पूर्ण;
	wil_err(wil, "Notify about firmware error\n");
	kobject_uevent_env(&dev->kobj, KOBJ_CHANGE, envp);
पूर्ण

अटल व्योम wil_cache_mbox_regs(काष्ठा wil6210_priv *wil)
अणु
	/* make shaकरोw copy of रेजिस्टरs that should not change on run समय */
	wil_स_नकल_fromio_32(&wil->mbox_ctl, wil->csr + HOST_MBOX,
			     माप(काष्ठा wil6210_mbox_ctl));
	wil_mbox_ring_le2cpus(&wil->mbox_ctl.rx);
	wil_mbox_ring_le2cpus(&wil->mbox_ctl.tx);
पूर्ण

अटल bool wil_validate_mbox_regs(काष्ठा wil6210_priv *wil)
अणु
	माप_प्रकार min_size = माप(काष्ठा wil6210_mbox_hdr) +
		माप(काष्ठा wmi_cmd_hdr);

	अगर (wil->mbox_ctl.rx.entry_size < min_size) अणु
		wil_err(wil, "rx mbox entry too small (%d)\n",
			wil->mbox_ctl.rx.entry_size);
		वापस false;
	पूर्ण
	अगर (wil->mbox_ctl.tx.entry_size < min_size) अणु
		wil_err(wil, "tx mbox entry too small (%d)\n",
			wil->mbox_ctl.tx.entry_size);
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल irqवापस_t wil6210_irq_misc(पूर्णांक irq, व्योम *cookie)
अणु
	काष्ठा wil6210_priv *wil = cookie;
	u32 isr;

	wil6210_mask_irq_misc(wil, false);

	isr = wil_ioपढ़ो32_and_clear(wil->csr +
				     HOSTADDR(RGF_DMA_EP_MISC_ICR) +
				     दुरत्व(काष्ठा RGF_ICR, ICR));

	trace_wil6210_irq_misc(isr);
	wil_dbg_irq(wil, "ISR MISC 0x%08x\n", isr);

	अगर (!isr) अणु
		wil_err(wil, "spurious IRQ: MISC\n");
		wil6210_unmask_irq_misc(wil, false);
		वापस IRQ_NONE;
	पूर्ण

	अगर (isr & ISR_MISC_FW_ERROR) अणु
		u32 fw_निश्चित_code = wil_r(wil, wil->rgf_fw_निश्चित_code_addr);
		u32 ucode_निश्चित_code =
			wil_r(wil, wil->rgf_ucode_निश्चित_code_addr);

		wil_err(wil,
			"Firmware error detected, assert codes FW 0x%08x, UCODE 0x%08x\n",
			fw_निश्चित_code, ucode_निश्चित_code);
		clear_bit(wil_status_fwपढ़ोy, wil->status);
		/*
		 * करो not clear @isr here - we करो 2-nd part in thपढ़ो
		 * there, user space get notअगरied, and it should be करोne
		 * in non-atomic context
		 */
	पूर्ण

	अगर (isr & ISR_MISC_FW_READY) अणु
		wil_dbg_irq(wil, "IRQ: FW ready\n");
		wil_cache_mbox_regs(wil);
		अगर (wil_validate_mbox_regs(wil))
			set_bit(wil_status_mbox_पढ़ोy, wil->status);
		/**
		 * Actual FW पढ़ोy indicated by the
		 * WMI_FW_READY_EVENTID
		 */
		isr &= ~ISR_MISC_FW_READY;
	पूर्ण

	अगर (isr & BIT_DMA_EP_MISC_ICR_HALP) अणु
		isr &= ~BIT_DMA_EP_MISC_ICR_HALP;
		अगर (wil->halp.handle_icr) अणु
			/* no need to handle HALP ICRs until next vote */
			wil->halp.handle_icr = false;
			wil_dbg_irq(wil, "irq_misc: HALP IRQ invoked\n");
			wil6210_mask_irq_misc(wil, true);
			complete(&wil->halp.comp);
		पूर्ण
	पूर्ण

	wil->isr_misc = isr;

	अगर (isr) अणु
		वापस IRQ_WAKE_THREAD;
	पूर्ण अन्यथा अणु
		wil6210_unmask_irq_misc(wil, false);
		वापस IRQ_HANDLED;
	पूर्ण
पूर्ण

अटल irqवापस_t wil6210_irq_misc_thपढ़ो(पूर्णांक irq, व्योम *cookie)
अणु
	काष्ठा wil6210_priv *wil = cookie;
	u32 isr = wil->isr_misc;

	trace_wil6210_irq_misc_thपढ़ो(isr);
	wil_dbg_irq(wil, "Thread ISR MISC 0x%08x\n", isr);

	अगर (isr & ISR_MISC_FW_ERROR) अणु
		wil->recovery_state = fw_recovery_pending;
		wil_fw_core_dump(wil);
		wil_notअगरy_fw_error(wil);
		isr &= ~ISR_MISC_FW_ERROR;
		अगर (wil->platक्रमm_ops.notअगरy) अणु
			wil_err(wil, "notify platform driver about FW crash");
			wil->platक्रमm_ops.notअगरy(wil->platक्रमm_handle,
						 WIL_PLATFORM_EVT_FW_CRASH);
		पूर्ण अन्यथा अणु
			wil_fw_error_recovery(wil);
		पूर्ण
	पूर्ण
	अगर (isr & ISR_MISC_MBOX_EVT) अणु
		wil_dbg_irq(wil, "MBOX event\n");
		wmi_recv_cmd(wil);
		isr &= ~ISR_MISC_MBOX_EVT;
	पूर्ण

	अगर (isr)
		wil_dbg_irq(wil, "un-handled MISC ISR bits 0x%08x\n", isr);

	wil->isr_misc = 0;

	wil6210_unmask_irq_misc(wil, false);

	/* in non-triple MSI हाल, this is करोne inside wil6210_thपढ़ो_irq
	 * because it has to be करोne after unmasking the pseuकरो.
	 */
	अगर (wil->n_msi == 3 && wil->suspend_resp_rcvd) अणु
		wil_dbg_irq(wil, "set suspend_resp_comp to true\n");
		wil->suspend_resp_comp = true;
		wake_up_पूर्णांकerruptible(&wil->wq);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

/* thपढ़ो IRQ handler */
अटल irqवापस_t wil6210_thपढ़ो_irq(पूर्णांक irq, व्योम *cookie)
अणु
	काष्ठा wil6210_priv *wil = cookie;

	wil_dbg_irq(wil, "Thread IRQ\n");
	/* Discover real IRQ cause */
	अगर (wil->isr_misc)
		wil6210_irq_misc_thपढ़ो(irq, cookie);

	wil6210_unmask_irq_pseuकरो(wil);

	अगर (wil->suspend_resp_rcvd) अणु
		wil_dbg_irq(wil, "set suspend_resp_comp to true\n");
		wil->suspend_resp_comp = true;
		wake_up_पूर्णांकerruptible(&wil->wq);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

/* DEBUG
 * There is subtle bug in hardware that causes IRQ to उठाओ when it should be
 * masked. It is quite rare and hard to debug.
 *
 * Catch irq issue अगर it happens and prपूर्णांक all I can.
 */
अटल पूर्णांक wil6210_debug_irq_mask(काष्ठा wil6210_priv *wil, u32 pseuकरो_cause)
अणु
	u32 icm_rx, icr_rx, imv_rx;
	u32 icm_tx, icr_tx, imv_tx;
	u32 icm_misc, icr_misc, imv_misc;

	अगर (!test_bit(wil_status_irqen, wil->status)) अणु
		अगर (wil->use_enhanced_dma_hw) अणु
			icm_rx = wil_ioपढ़ो32_and_clear(wil->csr +
					HOSTADDR(RGF_INT_GEN_RX_ICR) +
					दुरत्व(काष्ठा RGF_ICR, ICM));
			icr_rx = wil_ioपढ़ो32_and_clear(wil->csr +
					HOSTADDR(RGF_INT_GEN_RX_ICR) +
					दुरत्व(काष्ठा RGF_ICR, ICR));
			imv_rx = wil_r(wil, RGF_INT_GEN_RX_ICR +
				   दुरत्व(काष्ठा RGF_ICR, IMV));
			icm_tx = wil_ioपढ़ो32_and_clear(wil->csr +
					HOSTADDR(RGF_INT_GEN_TX_ICR) +
					दुरत्व(काष्ठा RGF_ICR, ICM));
			icr_tx = wil_ioपढ़ो32_and_clear(wil->csr +
					HOSTADDR(RGF_INT_GEN_TX_ICR) +
					दुरत्व(काष्ठा RGF_ICR, ICR));
			imv_tx = wil_r(wil, RGF_INT_GEN_TX_ICR +
					   दुरत्व(काष्ठा RGF_ICR, IMV));
		पूर्ण अन्यथा अणु
			icm_rx = wil_ioपढ़ो32_and_clear(wil->csr +
					HOSTADDR(RGF_DMA_EP_RX_ICR) +
					दुरत्व(काष्ठा RGF_ICR, ICM));
			icr_rx = wil_ioपढ़ो32_and_clear(wil->csr +
					HOSTADDR(RGF_DMA_EP_RX_ICR) +
					दुरत्व(काष्ठा RGF_ICR, ICR));
			imv_rx = wil_r(wil, RGF_DMA_EP_RX_ICR +
				   दुरत्व(काष्ठा RGF_ICR, IMV));
			icm_tx = wil_ioपढ़ो32_and_clear(wil->csr +
					HOSTADDR(RGF_DMA_EP_TX_ICR) +
					दुरत्व(काष्ठा RGF_ICR, ICM));
			icr_tx = wil_ioपढ़ो32_and_clear(wil->csr +
					HOSTADDR(RGF_DMA_EP_TX_ICR) +
					दुरत्व(काष्ठा RGF_ICR, ICR));
			imv_tx = wil_r(wil, RGF_DMA_EP_TX_ICR +
					   दुरत्व(काष्ठा RGF_ICR, IMV));
		पूर्ण
		icm_misc = wil_ioपढ़ो32_and_clear(wil->csr +
				HOSTADDR(RGF_DMA_EP_MISC_ICR) +
				दुरत्व(काष्ठा RGF_ICR, ICM));
		icr_misc = wil_ioपढ़ो32_and_clear(wil->csr +
				HOSTADDR(RGF_DMA_EP_MISC_ICR) +
				दुरत्व(काष्ठा RGF_ICR, ICR));
		imv_misc = wil_r(wil, RGF_DMA_EP_MISC_ICR +
				     दुरत्व(काष्ठा RGF_ICR, IMV));

		/* HALP पूर्णांकerrupt can be unmasked when misc पूर्णांकerrupts are
		 * masked
		 */
		अगर (icr_misc & BIT_DMA_EP_MISC_ICR_HALP)
			वापस 0;

		wil_err(wil, "IRQ when it should be masked: pseudo 0x%08x\n"
				"Rx   icm:icr:imv 0x%08x 0x%08x 0x%08x\n"
				"Tx   icm:icr:imv 0x%08x 0x%08x 0x%08x\n"
				"Misc icm:icr:imv 0x%08x 0x%08x 0x%08x\n",
				pseuकरो_cause,
				icm_rx, icr_rx, imv_rx,
				icm_tx, icr_tx, imv_tx,
				icm_misc, icr_misc, imv_misc);

		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल irqवापस_t wil6210_hardirq(पूर्णांक irq, व्योम *cookie)
अणु
	irqवापस_t rc = IRQ_HANDLED;
	काष्ठा wil6210_priv *wil = cookie;
	u32 pseuकरो_cause = wil_r(wil, RGF_DMA_PSEUDO_CAUSE);

	/**
	 * pseuकरो_cause is Clear-On-Read, no need to ACK
	 */
	अगर (unlikely((pseuकरो_cause == 0) || ((pseuकरो_cause & 0xff) == 0xff)))
		वापस IRQ_NONE;

	/* IRQ mask debug */
	अगर (unlikely(wil6210_debug_irq_mask(wil, pseuकरो_cause)))
		वापस IRQ_NONE;

	trace_wil6210_irq_pseuकरो(pseuकरो_cause);
	wil_dbg_irq(wil, "Pseudo IRQ 0x%08x\n", pseuकरो_cause);

	wil6210_mask_irq_pseuकरो(wil);

	/* Discover real IRQ cause
	 * There are 2 possible phases क्रम every IRQ:
	 * - hard IRQ handler called right here
	 * - thपढ़ोed handler called later
	 *
	 * Hard IRQ handler पढ़ोs and clears ISR.
	 *
	 * If thपढ़ोed handler requested, hard IRQ handler
	 * वापसs IRQ_WAKE_THREAD and saves ISR रेजिस्टर value
	 * क्रम the thपढ़ोed handler use.
	 *
	 * voting क्रम wake thपढ़ो - need at least 1 vote
	 */
	अगर ((pseuकरो_cause & BIT_DMA_PSEUDO_CAUSE_RX) &&
	    (wil->txrx_ops.irq_rx(irq, cookie) == IRQ_WAKE_THREAD))
		rc = IRQ_WAKE_THREAD;

	अगर ((pseuकरो_cause & BIT_DMA_PSEUDO_CAUSE_TX) &&
	    (wil->txrx_ops.irq_tx(irq, cookie) == IRQ_WAKE_THREAD))
		rc = IRQ_WAKE_THREAD;

	अगर ((pseuकरो_cause & BIT_DMA_PSEUDO_CAUSE_MISC) &&
	    (wil6210_irq_misc(irq, cookie) == IRQ_WAKE_THREAD))
		rc = IRQ_WAKE_THREAD;

	/* अगर thपढ़ो is requested, it will unmask IRQ */
	अगर (rc != IRQ_WAKE_THREAD)
		wil6210_unmask_irq_pseuकरो(wil);

	वापस rc;
पूर्ण

अटल पूर्णांक wil6210_request_3msi(काष्ठा wil6210_priv *wil, पूर्णांक irq)
अणु
	पूर्णांक rc;

	/* IRQ's are in the following order:
	 * - Tx
	 * - Rx
	 * - Misc
	 */
	rc = request_irq(irq, wil->txrx_ops.irq_tx, IRQF_SHARED,
			 WIL_NAME "_tx", wil);
	अगर (rc)
		वापस rc;

	rc = request_irq(irq + 1, wil->txrx_ops.irq_rx, IRQF_SHARED,
			 WIL_NAME "_rx", wil);
	अगर (rc)
		जाओ मुक्त0;

	rc = request_thपढ़ोed_irq(irq + 2, wil6210_irq_misc,
				  wil6210_irq_misc_thपढ़ो,
				  IRQF_SHARED, WIL_NAME "_misc", wil);
	अगर (rc)
		जाओ मुक्त1;

	वापस 0;
मुक्त1:
	मुक्त_irq(irq + 1, wil);
मुक्त0:
	मुक्त_irq(irq, wil);

	वापस rc;
पूर्ण

/* can't use wil_ioपढ़ो32_and_clear because ICC value is not set yet */
अटल अंतरभूत व्योम wil_clear32(व्योम __iomem *addr)
अणु
	u32 x = पढ़ोl(addr);

	ग_लिखोl(x, addr);
पूर्ण

व्योम wil6210_clear_irq(काष्ठा wil6210_priv *wil)
अणु
	wil_clear32(wil->csr + HOSTADDR(RGF_DMA_EP_RX_ICR) +
		    दुरत्व(काष्ठा RGF_ICR, ICR));
	wil_clear32(wil->csr + HOSTADDR(RGF_DMA_EP_TX_ICR) +
		    दुरत्व(काष्ठा RGF_ICR, ICR));
	wil_clear32(wil->csr + HOSTADDR(RGF_INT_GEN_RX_ICR) +
		    दुरत्व(काष्ठा RGF_ICR, ICR));
	wil_clear32(wil->csr + HOSTADDR(RGF_INT_GEN_TX_ICR) +
		    दुरत्व(काष्ठा RGF_ICR, ICR));
	wil_clear32(wil->csr + HOSTADDR(RGF_DMA_EP_MISC_ICR) +
		    दुरत्व(काष्ठा RGF_ICR, ICR));
	wmb(); /* make sure ग_लिखो completed */
पूर्ण

व्योम wil6210_set_halp(काष्ठा wil6210_priv *wil)
अणु
	wil_dbg_irq(wil, "set_halp\n");

	wil_w(wil, RGF_DMA_EP_MISC_ICR + दुरत्व(काष्ठा RGF_ICR, ICS),
	      BIT_DMA_EP_MISC_ICR_HALP);
पूर्ण

व्योम wil6210_clear_halp(काष्ठा wil6210_priv *wil)
अणु
	wil_dbg_irq(wil, "clear_halp\n");

	wil_w(wil, RGF_DMA_EP_MISC_ICR + दुरत्व(काष्ठा RGF_ICR, ICR),
	      BIT_DMA_EP_MISC_ICR_HALP);
	wil6210_unmask_halp(wil);
पूर्ण

पूर्णांक wil6210_init_irq(काष्ठा wil6210_priv *wil, पूर्णांक irq)
अणु
	पूर्णांक rc;

	wil_dbg_misc(wil, "init_irq: %s, n_msi=%d\n",
		     wil->n_msi ? "MSI" : "INTx", wil->n_msi);

	अगर (wil->use_enhanced_dma_hw) अणु
		wil->txrx_ops.irq_tx = wil6210_irq_tx_edma;
		wil->txrx_ops.irq_rx = wil6210_irq_rx_edma;
	पूर्ण अन्यथा अणु
		wil->txrx_ops.irq_tx = wil6210_irq_tx;
		wil->txrx_ops.irq_rx = wil6210_irq_rx;
	पूर्ण

	अगर (wil->n_msi == 3)
		rc = wil6210_request_3msi(wil, irq);
	अन्यथा
		rc = request_thपढ़ोed_irq(irq, wil6210_hardirq,
					  wil6210_thपढ़ो_irq,
					  wil->n_msi ? 0 : IRQF_SHARED,
					  WIL_NAME, wil);
	वापस rc;
पूर्ण

व्योम wil6210_fini_irq(काष्ठा wil6210_priv *wil, पूर्णांक irq)
अणु
	wil_dbg_misc(wil, "fini_irq:\n");

	wil_mask_irq(wil);
	मुक्त_irq(irq, wil);
	अगर (wil->n_msi == 3) अणु
		मुक्त_irq(irq + 1, wil);
		मुक्त_irq(irq + 2, wil);
	पूर्ण
पूर्ण
