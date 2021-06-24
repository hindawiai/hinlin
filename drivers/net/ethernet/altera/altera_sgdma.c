<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Altera TSE SGDMA and MSGDMA Linux driver
 * Copyright (C) 2014 Altera Corporation. All rights reserved
 */

#समावेश <linux/list.h>
#समावेश "altera_utils.h"
#समावेश "altera_tse.h"
#समावेश "altera_sgdmahw.h"
#समावेश "altera_sgdma.h"

अटल व्योम sgdma_setup_descrip(काष्ठा sgdma_descrip __iomem *desc,
				काष्ठा sgdma_descrip __iomem *ndesc,
				dma_addr_t ndesc_phys,
				dma_addr_t raddr,
				dma_addr_t waddr,
				u16 length,
				पूर्णांक generate_eop,
				पूर्णांक rfixed,
				पूर्णांक wfixed);

अटल पूर्णांक sgdma_async_ग_लिखो(काष्ठा altera_tse_निजी *priv,
			      काष्ठा sgdma_descrip __iomem *desc);

अटल पूर्णांक sgdma_async_पढ़ो(काष्ठा altera_tse_निजी *priv);

अटल dma_addr_t
sgdma_txphysaddr(काष्ठा altera_tse_निजी *priv,
		 काष्ठा sgdma_descrip __iomem *desc);

अटल dma_addr_t
sgdma_rxphysaddr(काष्ठा altera_tse_निजी *priv,
		 काष्ठा sgdma_descrip __iomem *desc);

अटल पूर्णांक sgdma_txbusy(काष्ठा altera_tse_निजी *priv);

अटल पूर्णांक sgdma_rxbusy(काष्ठा altera_tse_निजी *priv);

अटल व्योम
queue_tx(काष्ठा altera_tse_निजी *priv, काष्ठा tse_buffer *buffer);

अटल व्योम
queue_rx(काष्ठा altera_tse_निजी *priv, काष्ठा tse_buffer *buffer);

अटल काष्ठा tse_buffer *
dequeue_tx(काष्ठा altera_tse_निजी *priv);

अटल काष्ठा tse_buffer *
dequeue_rx(काष्ठा altera_tse_निजी *priv);

अटल काष्ठा tse_buffer *
queue_rx_peekhead(काष्ठा altera_tse_निजी *priv);

पूर्णांक sgdma_initialize(काष्ठा altera_tse_निजी *priv)
अणु
	priv->txctrlreg = SGDMA_CTRLREG_ILASTD |
		      SGDMA_CTRLREG_INTEN;

	priv->rxctrlreg = SGDMA_CTRLREG_IDESCRIP |
		      SGDMA_CTRLREG_INTEN |
		      SGDMA_CTRLREG_ILASTD;

	INIT_LIST_HEAD(&priv->txlisthd);
	INIT_LIST_HEAD(&priv->rxlisthd);

	priv->rxdescphys = (dma_addr_t) 0;
	priv->txdescphys = (dma_addr_t) 0;

	priv->rxdescphys = dma_map_single(priv->device,
					  (व्योम __क्रमce *)priv->rx_dma_desc,
					  priv->rxdescmem, DMA_BIसूचीECTIONAL);

	अगर (dma_mapping_error(priv->device, priv->rxdescphys)) अणु
		sgdma_uninitialize(priv);
		netdev_err(priv->dev, "error mapping rx descriptor memory\n");
		वापस -EINVAL;
	पूर्ण

	priv->txdescphys = dma_map_single(priv->device,
					  (व्योम __क्रमce *)priv->tx_dma_desc,
					  priv->txdescmem, DMA_TO_DEVICE);

	अगर (dma_mapping_error(priv->device, priv->txdescphys)) अणु
		sgdma_uninitialize(priv);
		netdev_err(priv->dev, "error mapping tx descriptor memory\n");
		वापस -EINVAL;
	पूर्ण

	/* Initialize descriptor memory to all 0's, sync memory to cache */
	स_रखो_io(priv->tx_dma_desc, 0, priv->txdescmem);
	स_रखो_io(priv->rx_dma_desc, 0, priv->rxdescmem);

	dma_sync_single_क्रम_device(priv->device, priv->txdescphys,
				   priv->txdescmem, DMA_TO_DEVICE);

	dma_sync_single_क्रम_device(priv->device, priv->rxdescphys,
				   priv->rxdescmem, DMA_TO_DEVICE);

	वापस 0;
पूर्ण

व्योम sgdma_uninitialize(काष्ठा altera_tse_निजी *priv)
अणु
	अगर (priv->rxdescphys)
		dma_unmap_single(priv->device, priv->rxdescphys,
				 priv->rxdescmem, DMA_BIसूचीECTIONAL);

	अगर (priv->txdescphys)
		dma_unmap_single(priv->device, priv->txdescphys,
				 priv->txdescmem, DMA_TO_DEVICE);
पूर्ण

/* This function resets the SGDMA controller and clears the
 * descriptor memory used क्रम transmits and receives.
 */
व्योम sgdma_reset(काष्ठा altera_tse_निजी *priv)
अणु
	/* Initialize descriptor memory to 0 */
	स_रखो_io(priv->tx_dma_desc, 0, priv->txdescmem);
	स_रखो_io(priv->rx_dma_desc, 0, priv->rxdescmem);

	csrwr32(SGDMA_CTRLREG_RESET, priv->tx_dma_csr, sgdma_csroffs(control));
	csrwr32(0, priv->tx_dma_csr, sgdma_csroffs(control));

	csrwr32(SGDMA_CTRLREG_RESET, priv->rx_dma_csr, sgdma_csroffs(control));
	csrwr32(0, priv->rx_dma_csr, sgdma_csroffs(control));
पूर्ण

/* For SGDMA, पूर्णांकerrupts reमुख्य enabled after initially enabling,
 * so no need to provide implementations क्रम असलtract enable
 * and disable
 */

व्योम sgdma_enable_rxirq(काष्ठा altera_tse_निजी *priv)
अणु
पूर्ण

व्योम sgdma_enable_txirq(काष्ठा altera_tse_निजी *priv)
अणु
पूर्ण

व्योम sgdma_disable_rxirq(काष्ठा altera_tse_निजी *priv)
अणु
पूर्ण

व्योम sgdma_disable_txirq(काष्ठा altera_tse_निजी *priv)
अणु
पूर्ण

व्योम sgdma_clear_rxirq(काष्ठा altera_tse_निजी *priv)
अणु
	tse_set_bit(priv->rx_dma_csr, sgdma_csroffs(control),
		    SGDMA_CTRLREG_CLRINT);
पूर्ण

व्योम sgdma_clear_txirq(काष्ठा altera_tse_निजी *priv)
अणु
	tse_set_bit(priv->tx_dma_csr, sgdma_csroffs(control),
		    SGDMA_CTRLREG_CLRINT);
पूर्ण

/* transmits buffer through SGDMA. Returns number of buffers
 * transmitted, 0 अगर not possible.
 *
 * tx_lock is held by the caller
 */
पूर्णांक sgdma_tx_buffer(काष्ठा altera_tse_निजी *priv, काष्ठा tse_buffer *buffer)
अणु
	काष्ठा sgdma_descrip __iomem *descbase =
		(काष्ठा sgdma_descrip __iomem *)priv->tx_dma_desc;

	काष्ठा sgdma_descrip __iomem *cdesc = &descbase[0];
	काष्ठा sgdma_descrip __iomem *ndesc = &descbase[1];

	/* रुको 'til the tx sgdma is पढ़ोy क्रम the next transmit request */
	अगर (sgdma_txbusy(priv))
		वापस 0;

	sgdma_setup_descrip(cdesc,			/* current descriptor */
			    ndesc,			/* next descriptor */
			    sgdma_txphysaddr(priv, ndesc),
			    buffer->dma_addr,		/* address of packet to xmit */
			    0,				/* ग_लिखो addr 0 क्रम tx dma */
			    buffer->len,		/* length of packet */
			    SGDMA_CONTROL_EOP,		/* Generate EOP */
			    0,				/* पढ़ो fixed */
			    SGDMA_CONTROL_WR_FIXED);	/* Generate SOP */

	sgdma_async_ग_लिखो(priv, cdesc);

	/* enqueue the request to the pending transmit queue */
	queue_tx(priv, buffer);

	वापस 1;
पूर्ण


/* tx_lock held to protect access to queued tx list
 */
u32 sgdma_tx_completions(काष्ठा altera_tse_निजी *priv)
अणु
	u32 पढ़ोy = 0;

	अगर (!sgdma_txbusy(priv) &&
	    ((csrrd8(priv->tx_dma_desc, sgdma_descroffs(control))
	     & SGDMA_CONTROL_HW_OWNED) == 0) &&
	    (dequeue_tx(priv))) अणु
		पढ़ोy = 1;
	पूर्ण

	वापस पढ़ोy;
पूर्ण

व्योम sgdma_start_rxdma(काष्ठा altera_tse_निजी *priv)
अणु
	sgdma_async_पढ़ो(priv);
पूर्ण

व्योम sgdma_add_rx_desc(काष्ठा altera_tse_निजी *priv,
		       काष्ठा tse_buffer *rxbuffer)
अणु
	queue_rx(priv, rxbuffer);
पूर्ण

/* status is वापसed on upper 16 bits,
 * length is वापसed in lower 16 bits
 */
u32 sgdma_rx_status(काष्ठा altera_tse_निजी *priv)
अणु
	काष्ठा sgdma_descrip __iomem *base =
		(काष्ठा sgdma_descrip __iomem *)priv->rx_dma_desc;
	काष्ठा sgdma_descrip __iomem *desc = शून्य;
	काष्ठा tse_buffer *rxbuffer = शून्य;
	अचिन्हित पूर्णांक rxstatus = 0;

	u32 sts = csrrd32(priv->rx_dma_csr, sgdma_csroffs(status));

	desc = &base[0];
	अगर (sts & SGDMA_STSREG_EOP) अणु
		अचिन्हित पूर्णांक pktlength = 0;
		अचिन्हित पूर्णांक pktstatus = 0;
		dma_sync_single_क्रम_cpu(priv->device,
					priv->rxdescphys,
					SGDMA_DESC_LEN,
					DMA_FROM_DEVICE);

		pktlength = csrrd16(desc, sgdma_descroffs(bytes_xferred));
		pktstatus = csrrd8(desc, sgdma_descroffs(status));
		rxstatus = pktstatus & ~SGDMA_STATUS_EOP;
		rxstatus = rxstatus << 16;
		rxstatus |= (pktlength & 0xffff);

		अगर (rxstatus) अणु
			csrwr8(0, desc, sgdma_descroffs(status));

			rxbuffer = dequeue_rx(priv);
			अगर (rxbuffer == शून्य)
				netdev_info(priv->dev,
					    "sgdma rx and rx queue empty!\n");

			/* Clear control */
			csrwr32(0, priv->rx_dma_csr, sgdma_csroffs(control));
			/* clear status */
			csrwr32(0xf, priv->rx_dma_csr, sgdma_csroffs(status));

			/* kick the rx sgdma after reaping this descriptor */
			sgdma_async_पढ़ो(priv);

		पूर्ण अन्यथा अणु
			/* If the SGDMA indicated an end of packet on recv,
			 * then it's expected that the rxstatus from the
			 * descriptor is non-zero - meaning a valid packet
			 * with a nonzero length, or an error has been
			 * indicated. अगर not, then all we can करो is संकेत
			 * an error and वापस no packet received. Most likely
			 * there is a प्रणाली design error, or an error in the
			 * underlying kernel (cache or cache management problem)
			 */
			netdev_err(priv->dev,
				   "SGDMA RX Error Info: %x, %x, %x\n",
				   sts, csrrd8(desc, sgdma_descroffs(status)),
				   rxstatus);
		पूर्ण
	पूर्ण अन्यथा अगर (sts == 0) अणु
		sgdma_async_पढ़ो(priv);
	पूर्ण

	वापस rxstatus;
पूर्ण


/* Private functions */
अटल व्योम sgdma_setup_descrip(काष्ठा sgdma_descrip __iomem *desc,
				काष्ठा sgdma_descrip __iomem *ndesc,
				dma_addr_t ndesc_phys,
				dma_addr_t raddr,
				dma_addr_t waddr,
				u16 length,
				पूर्णांक generate_eop,
				पूर्णांक rfixed,
				पूर्णांक wfixed)
अणु
	/* Clear the next descriptor as not owned by hardware */

	u32 ctrl = csrrd8(ndesc, sgdma_descroffs(control));
	ctrl &= ~SGDMA_CONTROL_HW_OWNED;
	csrwr8(ctrl, ndesc, sgdma_descroffs(control));

	ctrl = SGDMA_CONTROL_HW_OWNED;
	ctrl |= generate_eop;
	ctrl |= rfixed;
	ctrl |= wfixed;

	/* Channel is implicitly zero, initialized to 0 by शेष */
	csrwr32(lower_32_bits(raddr), desc, sgdma_descroffs(raddr));
	csrwr32(lower_32_bits(waddr), desc, sgdma_descroffs(waddr));

	csrwr32(0, desc, sgdma_descroffs(pad1));
	csrwr32(0, desc, sgdma_descroffs(pad2));
	csrwr32(lower_32_bits(ndesc_phys), desc, sgdma_descroffs(next));

	csrwr8(ctrl, desc, sgdma_descroffs(control));
	csrwr8(0, desc, sgdma_descroffs(status));
	csrwr8(0, desc, sgdma_descroffs(wburst));
	csrwr8(0, desc, sgdma_descroffs(rburst));
	csrwr16(length, desc, sgdma_descroffs(bytes));
	csrwr16(0, desc, sgdma_descroffs(bytes_xferred));
पूर्ण

/* If hardware is busy, करोn't restart async पढ़ो.
 * अगर status रेजिस्टर is 0 - meaning initial state, restart async पढ़ो,
 * probably क्रम the first समय when populating a receive buffer.
 * If पढ़ो status indicate not busy and a status, restart the async
 * DMA पढ़ो.
 */
अटल पूर्णांक sgdma_async_पढ़ो(काष्ठा altera_tse_निजी *priv)
अणु
	काष्ठा sgdma_descrip __iomem *descbase =
		(काष्ठा sgdma_descrip __iomem *)priv->rx_dma_desc;

	काष्ठा sgdma_descrip __iomem *cdesc = &descbase[0];
	काष्ठा sgdma_descrip __iomem *ndesc = &descbase[1];
	काष्ठा tse_buffer *rxbuffer = शून्य;

	अगर (!sgdma_rxbusy(priv)) अणु
		rxbuffer = queue_rx_peekhead(priv);
		अगर (rxbuffer == शून्य) अणु
			netdev_err(priv->dev, "no rx buffers available\n");
			वापस 0;
		पूर्ण

		sgdma_setup_descrip(cdesc,		/* current descriptor */
				    ndesc,		/* next descriptor */
				    sgdma_rxphysaddr(priv, ndesc),
				    0,			/* पढ़ो addr 0 क्रम rx dma */
				    rxbuffer->dma_addr, /* ग_लिखो addr क्रम rx dma */
				    0,			/* पढ़ो 'til EOP */
				    0,			/* EOP: NA क्रम rx dma */
				    0,			/* पढ़ो fixed: NA क्रम rx dma */
				    0);			/* SOP: NA क्रम rx DMA */

		dma_sync_single_क्रम_device(priv->device,
					   priv->rxdescphys,
					   SGDMA_DESC_LEN,
					   DMA_TO_DEVICE);

		csrwr32(lower_32_bits(sgdma_rxphysaddr(priv, cdesc)),
			priv->rx_dma_csr,
			sgdma_csroffs(next_descrip));

		csrwr32((priv->rxctrlreg | SGDMA_CTRLREG_START),
			priv->rx_dma_csr,
			sgdma_csroffs(control));

		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sgdma_async_ग_लिखो(काष्ठा altera_tse_निजी *priv,
			     काष्ठा sgdma_descrip __iomem *desc)
अणु
	अगर (sgdma_txbusy(priv))
		वापस 0;

	/* clear control and status */
	csrwr32(0, priv->tx_dma_csr, sgdma_csroffs(control));
	csrwr32(0x1f, priv->tx_dma_csr, sgdma_csroffs(status));

	dma_sync_single_क्रम_device(priv->device, priv->txdescphys,
				   SGDMA_DESC_LEN, DMA_TO_DEVICE);

	csrwr32(lower_32_bits(sgdma_txphysaddr(priv, desc)),
		priv->tx_dma_csr,
		sgdma_csroffs(next_descrip));

	csrwr32((priv->txctrlreg | SGDMA_CTRLREG_START),
		priv->tx_dma_csr,
		sgdma_csroffs(control));

	वापस 1;
पूर्ण

अटल dma_addr_t
sgdma_txphysaddr(काष्ठा altera_tse_निजी *priv,
		 काष्ठा sgdma_descrip __iomem *desc)
अणु
	dma_addr_t paddr = priv->txdescmem_busaddr;
	uपूर्णांकptr_t offs = (uपूर्णांकptr_t)desc - (uपूर्णांकptr_t)priv->tx_dma_desc;
	वापस (dma_addr_t)((uपूर्णांकptr_t)paddr + offs);
पूर्ण

अटल dma_addr_t
sgdma_rxphysaddr(काष्ठा altera_tse_निजी *priv,
		 काष्ठा sgdma_descrip __iomem *desc)
अणु
	dma_addr_t paddr = priv->rxdescmem_busaddr;
	uपूर्णांकptr_t offs = (uपूर्णांकptr_t)desc - (uपूर्णांकptr_t)priv->rx_dma_desc;
	वापस (dma_addr_t)((uपूर्णांकptr_t)paddr + offs);
पूर्ण

#घोषणा list_हटाओ_head(list, entry, type, member)			\
	करो अणु								\
		entry = शून्य;						\
		अगर (!list_empty(list)) अणु				\
			entry = list_entry((list)->next, type, member);	\
			list_del_init(&entry->member);			\
		पूर्ण							\
	पूर्ण जबतक (0)

#घोषणा list_peek_head(list, entry, type, member)			\
	करो अणु								\
		entry = शून्य;						\
		अगर (!list_empty(list)) अणु				\
			entry = list_entry((list)->next, type, member);	\
		पूर्ण							\
	पूर्ण जबतक (0)

/* adds a tse_buffer to the tail of a tx buffer list.
 * assumes the caller is managing and holding a mutual exclusion
 * primitive to aव्योम simultaneous pushes/pops to the list.
 */
अटल व्योम
queue_tx(काष्ठा altera_tse_निजी *priv, काष्ठा tse_buffer *buffer)
अणु
	list_add_tail(&buffer->lh, &priv->txlisthd);
पूर्ण


/* adds a tse_buffer to the tail of a rx buffer list
 * assumes the caller is managing and holding a mutual exclusion
 * primitive to aव्योम simultaneous pushes/pops to the list.
 */
अटल व्योम
queue_rx(काष्ठा altera_tse_निजी *priv, काष्ठा tse_buffer *buffer)
अणु
	list_add_tail(&buffer->lh, &priv->rxlisthd);
पूर्ण

/* dequeues a tse_buffer from the transmit buffer list, otherwise
 * वापसs शून्य अगर empty.
 * assumes the caller is managing and holding a mutual exclusion
 * primitive to aव्योम simultaneous pushes/pops to the list.
 */
अटल काष्ठा tse_buffer *
dequeue_tx(काष्ठा altera_tse_निजी *priv)
अणु
	काष्ठा tse_buffer *buffer = शून्य;
	list_हटाओ_head(&priv->txlisthd, buffer, काष्ठा tse_buffer, lh);
	वापस buffer;
पूर्ण

/* dequeues a tse_buffer from the receive buffer list, otherwise
 * वापसs शून्य अगर empty
 * assumes the caller is managing and holding a mutual exclusion
 * primitive to aव्योम simultaneous pushes/pops to the list.
 */
अटल काष्ठा tse_buffer *
dequeue_rx(काष्ठा altera_tse_निजी *priv)
अणु
	काष्ठा tse_buffer *buffer = शून्य;
	list_हटाओ_head(&priv->rxlisthd, buffer, काष्ठा tse_buffer, lh);
	वापस buffer;
पूर्ण

/* dequeues a tse_buffer from the receive buffer list, otherwise
 * वापसs शून्य अगर empty
 * assumes the caller is managing and holding a mutual exclusion
 * primitive to aव्योम simultaneous pushes/pops to the list जबतक the
 * head is being examined.
 */
अटल काष्ठा tse_buffer *
queue_rx_peekhead(काष्ठा altera_tse_निजी *priv)
अणु
	काष्ठा tse_buffer *buffer = शून्य;
	list_peek_head(&priv->rxlisthd, buffer, काष्ठा tse_buffer, lh);
	वापस buffer;
पूर्ण

/* check and वापस rx sgdma status without polling
 */
अटल पूर्णांक sgdma_rxbusy(काष्ठा altera_tse_निजी *priv)
अणु
	वापस csrrd32(priv->rx_dma_csr, sgdma_csroffs(status))
		       & SGDMA_STSREG_BUSY;
पूर्ण

/* रुकोs क्रम the tx sgdma to finish it's current operation, वापसs 0
 * when it transitions to nonbusy, वापसs 1 अगर the operation बार out
 */
अटल पूर्णांक sgdma_txbusy(काष्ठा altera_tse_निजी *priv)
अणु
	पूर्णांक delay = 0;

	/* अगर DMA is busy, रुको क्रम current transactino to finish */
	जबतक ((csrrd32(priv->tx_dma_csr, sgdma_csroffs(status))
		& SGDMA_STSREG_BUSY) && (delay++ < 100))
		udelay(1);

	अगर (csrrd32(priv->tx_dma_csr, sgdma_csroffs(status))
	    & SGDMA_STSREG_BUSY) अणु
		netdev_err(priv->dev, "timeout waiting for tx dma\n");
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण
