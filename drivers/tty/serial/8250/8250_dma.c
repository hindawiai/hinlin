<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * 8250_dma.c - DMA Engine API support क्रम 8250.c
 *
 * Copyright (C) 2013 Intel Corporation
 */
#समावेश <linux/tty.h>
#समावेश <linux/tty_flip.h>
#समावेश <linux/serial_reg.h>
#समावेश <linux/dma-mapping.h>

#समावेश "8250.h"

अटल व्योम __dma_tx_complete(व्योम *param)
अणु
	काष्ठा uart_8250_port	*p = param;
	काष्ठा uart_8250_dma	*dma = p->dma;
	काष्ठा circ_buf		*xmit = &p->port.state->xmit;
	अचिन्हित दीर्घ	flags;
	पूर्णांक		ret;

	dma_sync_single_क्रम_cpu(dma->txchan->device->dev, dma->tx_addr,
				UART_XMIT_SIZE, DMA_TO_DEVICE);

	spin_lock_irqsave(&p->port.lock, flags);

	dma->tx_running = 0;

	xmit->tail += dma->tx_size;
	xmit->tail &= UART_XMIT_SIZE - 1;
	p->port.icount.tx += dma->tx_size;

	अगर (uart_circ_अक्षरs_pending(xmit) < WAKEUP_CHARS)
		uart_ग_लिखो_wakeup(&p->port);

	ret = serial8250_tx_dma(p);
	अगर (ret)
		serial8250_set_THRI(p);

	spin_unlock_irqrestore(&p->port.lock, flags);
पूर्ण

अटल व्योम __dma_rx_complete(व्योम *param)
अणु
	काष्ठा uart_8250_port	*p = param;
	काष्ठा uart_8250_dma	*dma = p->dma;
	काष्ठा tty_port		*tty_port = &p->port.state->port;
	काष्ठा dma_tx_state	state;
	पूर्णांक			count;

	dma->rx_running = 0;
	dmaengine_tx_status(dma->rxchan, dma->rx_cookie, &state);

	count = dma->rx_size - state.residue;

	tty_insert_flip_string(tty_port, dma->rx_buf, count);
	p->port.icount.rx += count;

	tty_flip_buffer_push(tty_port);
पूर्ण

पूर्णांक serial8250_tx_dma(काष्ठा uart_8250_port *p)
अणु
	काष्ठा uart_8250_dma		*dma = p->dma;
	काष्ठा circ_buf			*xmit = &p->port.state->xmit;
	काष्ठा dma_async_tx_descriptor	*desc;
	पूर्णांक ret;

	अगर (dma->tx_running)
		वापस 0;

	अगर (uart_tx_stopped(&p->port) || uart_circ_empty(xmit)) अणु
		/* We have been called from __dma_tx_complete() */
		serial8250_rpm_put_tx(p);
		वापस 0;
	पूर्ण

	dma->tx_size = CIRC_CNT_TO_END(xmit->head, xmit->tail, UART_XMIT_SIZE);

	desc = dmaengine_prep_slave_single(dma->txchan,
					   dma->tx_addr + xmit->tail,
					   dma->tx_size, DMA_MEM_TO_DEV,
					   DMA_PREP_INTERRUPT | DMA_CTRL_ACK);
	अगर (!desc) अणु
		ret = -EBUSY;
		जाओ err;
	पूर्ण

	dma->tx_running = 1;
	desc->callback = __dma_tx_complete;
	desc->callback_param = p;

	dma->tx_cookie = dmaengine_submit(desc);

	dma_sync_single_क्रम_device(dma->txchan->device->dev, dma->tx_addr,
				   UART_XMIT_SIZE, DMA_TO_DEVICE);

	dma_async_issue_pending(dma->txchan);
	अगर (dma->tx_err) अणु
		dma->tx_err = 0;
		serial8250_clear_THRI(p);
	पूर्ण
	वापस 0;
err:
	dma->tx_err = 1;
	वापस ret;
पूर्ण

पूर्णांक serial8250_rx_dma(काष्ठा uart_8250_port *p)
अणु
	काष्ठा uart_8250_dma		*dma = p->dma;
	काष्ठा dma_async_tx_descriptor	*desc;

	अगर (dma->rx_running)
		वापस 0;

	desc = dmaengine_prep_slave_single(dma->rxchan, dma->rx_addr,
					   dma->rx_size, DMA_DEV_TO_MEM,
					   DMA_PREP_INTERRUPT | DMA_CTRL_ACK);
	अगर (!desc)
		वापस -EBUSY;

	dma->rx_running = 1;
	desc->callback = __dma_rx_complete;
	desc->callback_param = p;

	dma->rx_cookie = dmaengine_submit(desc);

	dma_async_issue_pending(dma->rxchan);

	वापस 0;
पूर्ण

व्योम serial8250_rx_dma_flush(काष्ठा uart_8250_port *p)
अणु
	काष्ठा uart_8250_dma *dma = p->dma;

	अगर (dma->rx_running) अणु
		dmaengine_छोड़ो(dma->rxchan);
		__dma_rx_complete(p);
		dmaengine_terminate_async(dma->rxchan);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(serial8250_rx_dma_flush);

पूर्णांक serial8250_request_dma(काष्ठा uart_8250_port *p)
अणु
	काष्ठा uart_8250_dma	*dma = p->dma;
	phys_addr_t rx_dma_addr = dma->rx_dma_addr ?
				  dma->rx_dma_addr : p->port.mapbase;
	phys_addr_t tx_dma_addr = dma->tx_dma_addr ?
				  dma->tx_dma_addr : p->port.mapbase;
	dma_cap_mask_t		mask;
	काष्ठा dma_slave_caps	caps;
	पूर्णांक			ret;

	/* Default slave configuration parameters */
	dma->rxconf.direction		= DMA_DEV_TO_MEM;
	dma->rxconf.src_addr_width	= DMA_SLAVE_BUSWIDTH_1_BYTE;
	dma->rxconf.src_addr		= rx_dma_addr + UART_RX;

	dma->txconf.direction		= DMA_MEM_TO_DEV;
	dma->txconf.dst_addr_width	= DMA_SLAVE_BUSWIDTH_1_BYTE;
	dma->txconf.dst_addr		= tx_dma_addr + UART_TX;

	dma_cap_zero(mask);
	dma_cap_set(DMA_SLAVE, mask);

	/* Get a channel क्रम RX */
	dma->rxchan = dma_request_slave_channel_compat(mask,
						       dma->fn, dma->rx_param,
						       p->port.dev, "rx");
	अगर (!dma->rxchan)
		वापस -ENODEV;

	/* 8250 rx dma requires dmaengine driver to support छोड़ो/terminate */
	ret = dma_get_slave_caps(dma->rxchan, &caps);
	अगर (ret)
		जाओ release_rx;
	अगर (!caps.cmd_छोड़ो || !caps.cmd_terminate ||
	    caps.residue_granularity == DMA_RESIDUE_GRANULARITY_DESCRIPTOR) अणु
		ret = -EINVAL;
		जाओ release_rx;
	पूर्ण

	dmaengine_slave_config(dma->rxchan, &dma->rxconf);

	/* Get a channel क्रम TX */
	dma->txchan = dma_request_slave_channel_compat(mask,
						       dma->fn, dma->tx_param,
						       p->port.dev, "tx");
	अगर (!dma->txchan) अणु
		ret = -ENODEV;
		जाओ release_rx;
	पूर्ण

	/* 8250 tx dma requires dmaengine driver to support terminate */
	ret = dma_get_slave_caps(dma->txchan, &caps);
	अगर (ret)
		जाओ err;
	अगर (!caps.cmd_terminate) अणु
		ret = -EINVAL;
		जाओ err;
	पूर्ण

	dmaengine_slave_config(dma->txchan, &dma->txconf);

	/* RX buffer */
	अगर (!dma->rx_size)
		dma->rx_size = PAGE_SIZE;

	dma->rx_buf = dma_alloc_coherent(dma->rxchan->device->dev, dma->rx_size,
					&dma->rx_addr, GFP_KERNEL);
	अगर (!dma->rx_buf) अणु
		ret = -ENOMEM;
		जाओ err;
	पूर्ण

	/* TX buffer */
	dma->tx_addr = dma_map_single(dma->txchan->device->dev,
					p->port.state->xmit.buf,
					UART_XMIT_SIZE,
					DMA_TO_DEVICE);
	अगर (dma_mapping_error(dma->txchan->device->dev, dma->tx_addr)) अणु
		dma_मुक्त_coherent(dma->rxchan->device->dev, dma->rx_size,
				  dma->rx_buf, dma->rx_addr);
		ret = -ENOMEM;
		जाओ err;
	पूर्ण

	dev_dbg_ratelimited(p->port.dev, "got both dma channels\n");

	वापस 0;
err:
	dma_release_channel(dma->txchan);
release_rx:
	dma_release_channel(dma->rxchan);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(serial8250_request_dma);

व्योम serial8250_release_dma(काष्ठा uart_8250_port *p)
अणु
	काष्ठा uart_8250_dma *dma = p->dma;

	अगर (!dma)
		वापस;

	/* Release RX resources */
	dmaengine_terminate_sync(dma->rxchan);
	dma_मुक्त_coherent(dma->rxchan->device->dev, dma->rx_size, dma->rx_buf,
			  dma->rx_addr);
	dma_release_channel(dma->rxchan);
	dma->rxchan = शून्य;

	/* Release TX resources */
	dmaengine_terminate_sync(dma->txchan);
	dma_unmap_single(dma->txchan->device->dev, dma->tx_addr,
			 UART_XMIT_SIZE, DMA_TO_DEVICE);
	dma_release_channel(dma->txchan);
	dma->txchan = शून्य;
	dma->tx_running = 0;

	dev_dbg_ratelimited(p->port.dev, "dma channels released\n");
पूर्ण
EXPORT_SYMBOL_GPL(serial8250_release_dma);
