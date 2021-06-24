<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Altera TSE SGDMA and MSGDMA Linux driver
 * Copyright (C) 2014 Altera Corporation. All rights reserved
 */

#समावेश <linux/netdevice.h>
#समावेश "altera_utils.h"
#समावेश "altera_tse.h"
#समावेश "altera_msgdmahw.h"
#समावेश "altera_msgdma.h"

/* No initialization work to करो क्रम MSGDMA */
पूर्णांक msgdma_initialize(काष्ठा altera_tse_निजी *priv)
अणु
	वापस 0;
पूर्ण

व्योम msgdma_uninitialize(काष्ठा altera_tse_निजी *priv)
अणु
पूर्ण

व्योम msgdma_start_rxdma(काष्ठा altera_tse_निजी *priv)
अणु
पूर्ण

व्योम msgdma_reset(काष्ठा altera_tse_निजी *priv)
अणु
	पूर्णांक counter;

	/* Reset Rx mSGDMA */
	csrwr32(MSGDMA_CSR_STAT_MASK, priv->rx_dma_csr,
		msgdma_csroffs(status));
	csrwr32(MSGDMA_CSR_CTL_RESET, priv->rx_dma_csr,
		msgdma_csroffs(control));

	counter = 0;
	जबतक (counter++ < ALTERA_TSE_SW_RESET_WATCHDOG_CNTR) अणु
		अगर (tse_bit_is_clear(priv->rx_dma_csr, msgdma_csroffs(status),
				     MSGDMA_CSR_STAT_RESETTING))
			अवरोध;
		udelay(1);
	पूर्ण

	अगर (counter >= ALTERA_TSE_SW_RESET_WATCHDOG_CNTR)
		netअगर_warn(priv, drv, priv->dev,
			   "TSE Rx mSGDMA resetting bit never cleared!\n");

	/* clear all status bits */
	csrwr32(MSGDMA_CSR_STAT_MASK, priv->rx_dma_csr, msgdma_csroffs(status));

	/* Reset Tx mSGDMA */
	csrwr32(MSGDMA_CSR_STAT_MASK, priv->tx_dma_csr,
		msgdma_csroffs(status));

	csrwr32(MSGDMA_CSR_CTL_RESET, priv->tx_dma_csr,
		msgdma_csroffs(control));

	counter = 0;
	जबतक (counter++ < ALTERA_TSE_SW_RESET_WATCHDOG_CNTR) अणु
		अगर (tse_bit_is_clear(priv->tx_dma_csr, msgdma_csroffs(status),
				     MSGDMA_CSR_STAT_RESETTING))
			अवरोध;
		udelay(1);
	पूर्ण

	अगर (counter >= ALTERA_TSE_SW_RESET_WATCHDOG_CNTR)
		netअगर_warn(priv, drv, priv->dev,
			   "TSE Tx mSGDMA resetting bit never cleared!\n");

	/* clear all status bits */
	csrwr32(MSGDMA_CSR_STAT_MASK, priv->tx_dma_csr, msgdma_csroffs(status));
पूर्ण

व्योम msgdma_disable_rxirq(काष्ठा altera_tse_निजी *priv)
अणु
	tse_clear_bit(priv->rx_dma_csr, msgdma_csroffs(control),
		      MSGDMA_CSR_CTL_GLOBAL_INTR);
पूर्ण

व्योम msgdma_enable_rxirq(काष्ठा altera_tse_निजी *priv)
अणु
	tse_set_bit(priv->rx_dma_csr, msgdma_csroffs(control),
		    MSGDMA_CSR_CTL_GLOBAL_INTR);
पूर्ण

व्योम msgdma_disable_txirq(काष्ठा altera_tse_निजी *priv)
अणु
	tse_clear_bit(priv->tx_dma_csr, msgdma_csroffs(control),
		      MSGDMA_CSR_CTL_GLOBAL_INTR);
पूर्ण

व्योम msgdma_enable_txirq(काष्ठा altera_tse_निजी *priv)
अणु
	tse_set_bit(priv->tx_dma_csr, msgdma_csroffs(control),
		    MSGDMA_CSR_CTL_GLOBAL_INTR);
पूर्ण

व्योम msgdma_clear_rxirq(काष्ठा altera_tse_निजी *priv)
अणु
	csrwr32(MSGDMA_CSR_STAT_IRQ, priv->rx_dma_csr, msgdma_csroffs(status));
पूर्ण

व्योम msgdma_clear_txirq(काष्ठा altera_tse_निजी *priv)
अणु
	csrwr32(MSGDMA_CSR_STAT_IRQ, priv->tx_dma_csr, msgdma_csroffs(status));
पूर्ण

/* वापस 0 to indicate transmit is pending */
पूर्णांक msgdma_tx_buffer(काष्ठा altera_tse_निजी *priv, काष्ठा tse_buffer *buffer)
अणु
	csrwr32(lower_32_bits(buffer->dma_addr), priv->tx_dma_desc,
		msgdma_descroffs(पढ़ो_addr_lo));
	csrwr32(upper_32_bits(buffer->dma_addr), priv->tx_dma_desc,
		msgdma_descroffs(पढ़ो_addr_hi));
	csrwr32(0, priv->tx_dma_desc, msgdma_descroffs(ग_लिखो_addr_lo));
	csrwr32(0, priv->tx_dma_desc, msgdma_descroffs(ग_लिखो_addr_hi));
	csrwr32(buffer->len, priv->tx_dma_desc, msgdma_descroffs(len));
	csrwr32(0, priv->tx_dma_desc, msgdma_descroffs(burst_seq_num));
	csrwr32(MSGDMA_DESC_TX_STRIDE, priv->tx_dma_desc,
		msgdma_descroffs(stride));
	csrwr32(MSGDMA_DESC_CTL_TX_SINGLE, priv->tx_dma_desc,
		msgdma_descroffs(control));
	वापस 0;
पूर्ण

u32 msgdma_tx_completions(काष्ठा altera_tse_निजी *priv)
अणु
	u32 पढ़ोy = 0;
	u32 inuse;
	u32 status;

	/* Get number of sent descriptors */
	inuse = csrrd32(priv->tx_dma_csr, msgdma_csroffs(rw_fill_level))
			& 0xffff;

	अगर (inuse) अणु /* Tx FIFO is not empty */
		पढ़ोy = max_t(पूर्णांक,
			      priv->tx_prod - priv->tx_cons - inuse - 1, 0);
	पूर्ण अन्यथा अणु
		/* Check क्रम buffered last packet */
		status = csrrd32(priv->tx_dma_csr, msgdma_csroffs(status));
		अगर (status & MSGDMA_CSR_STAT_BUSY)
			पढ़ोy = priv->tx_prod - priv->tx_cons - 1;
		अन्यथा
			पढ़ोy = priv->tx_prod - priv->tx_cons;
	पूर्ण
	वापस पढ़ोy;
पूर्ण

/* Put buffer to the mSGDMA RX FIFO
 */
व्योम msgdma_add_rx_desc(काष्ठा altera_tse_निजी *priv,
			काष्ठा tse_buffer *rxbuffer)
अणु
	u32 len = priv->rx_dma_buf_sz;
	dma_addr_t dma_addr = rxbuffer->dma_addr;
	u32 control = (MSGDMA_DESC_CTL_END_ON_EOP
			| MSGDMA_DESC_CTL_END_ON_LEN
			| MSGDMA_DESC_CTL_TR_COMP_IRQ
			| MSGDMA_DESC_CTL_EARLY_IRQ
			| MSGDMA_DESC_CTL_TR_ERR_IRQ
			| MSGDMA_DESC_CTL_GO);

	csrwr32(0, priv->rx_dma_desc, msgdma_descroffs(पढ़ो_addr_lo));
	csrwr32(0, priv->rx_dma_desc, msgdma_descroffs(पढ़ो_addr_hi));
	csrwr32(lower_32_bits(dma_addr), priv->rx_dma_desc,
		msgdma_descroffs(ग_लिखो_addr_lo));
	csrwr32(upper_32_bits(dma_addr), priv->rx_dma_desc,
		msgdma_descroffs(ग_लिखो_addr_hi));
	csrwr32(len, priv->rx_dma_desc, msgdma_descroffs(len));
	csrwr32(0, priv->rx_dma_desc, msgdma_descroffs(burst_seq_num));
	csrwr32(0x00010001, priv->rx_dma_desc, msgdma_descroffs(stride));
	csrwr32(control, priv->rx_dma_desc, msgdma_descroffs(control));
पूर्ण

/* status is वापसed on upper 16 bits,
 * length is वापसed in lower 16 bits
 */
u32 msgdma_rx_status(काष्ठा altera_tse_निजी *priv)
अणु
	u32 rxstatus = 0;
	u32 pktlength;
	u32 pktstatus;

	अगर (csrrd32(priv->rx_dma_csr, msgdma_csroffs(resp_fill_level))
	    & 0xffff) अणु
		pktlength = csrrd32(priv->rx_dma_resp,
				    msgdma_respoffs(bytes_transferred));
		pktstatus = csrrd32(priv->rx_dma_resp,
				    msgdma_respoffs(status));
		rxstatus = pktstatus;
		rxstatus = rxstatus << 16;
		rxstatus |= (pktlength & 0xffff);
	पूर्ण
	वापस rxstatus;
पूर्ण
