<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * ISHTP DMA I/F functions
 *
 * Copyright (c) 2003-2016, Intel Corporation.
 */

#समावेश <linux/slab.h>
#समावेश <linux/sched.h>
#समावेश <linux/रुको.h>
#समावेश <linux/delay.h>
#समावेश <linux/dma-mapping.h>
#समावेश "ishtp-dev.h"
#समावेश "client.h"

/**
 * ishtp_cl_alloc_dma_buf() - Allocate DMA RX and TX buffer
 * @dev: ishtp device
 *
 * Allocate RX and TX DMA buffer once during bus setup.
 * It allocates 1MB, RX and TX DMA buffer, which are भागided
 * पूर्णांकo slots.
 */
व्योम	ishtp_cl_alloc_dma_buf(काष्ठा ishtp_device *dev)
अणु
	dma_addr_t	h;

	अगर (dev->ishtp_host_dma_tx_buf)
		वापस;

	dev->ishtp_host_dma_tx_buf_size = 1024*1024;
	dev->ishtp_host_dma_rx_buf_size = 1024*1024;

	/* Allocate Tx buffer and init usage biपंचांगap */
	dev->ishtp_host_dma_tx_buf = dma_alloc_coherent(dev->devc,
					dev->ishtp_host_dma_tx_buf_size,
					&h, GFP_KERNEL);
	अगर (dev->ishtp_host_dma_tx_buf)
		dev->ishtp_host_dma_tx_buf_phys = h;

	dev->ishtp_dma_num_slots = dev->ishtp_host_dma_tx_buf_size /
						DMA_SLOT_SIZE;

	dev->ishtp_dma_tx_map = kसुस्मृति(dev->ishtp_dma_num_slots,
					माप(uपूर्णांक8_t),
					GFP_KERNEL);
	spin_lock_init(&dev->ishtp_dma_tx_lock);

	/* Allocate Rx buffer */
	dev->ishtp_host_dma_rx_buf = dma_alloc_coherent(dev->devc,
					dev->ishtp_host_dma_rx_buf_size,
					 &h, GFP_KERNEL);

	अगर (dev->ishtp_host_dma_rx_buf)
		dev->ishtp_host_dma_rx_buf_phys = h;
पूर्ण

/**
 * ishtp_cl_मुक्त_dma_buf() - Free DMA RX and TX buffer
 * @dev: ishtp device
 *
 * Free DMA buffer when all clients are released. This is
 * only happens during error path in ISH built in driver
 * model
 */
व्योम	ishtp_cl_मुक्त_dma_buf(काष्ठा ishtp_device *dev)
अणु
	dma_addr_t	h;

	अगर (dev->ishtp_host_dma_tx_buf) अणु
		h = dev->ishtp_host_dma_tx_buf_phys;
		dma_मुक्त_coherent(dev->devc, dev->ishtp_host_dma_tx_buf_size,
				  dev->ishtp_host_dma_tx_buf, h);
	पूर्ण

	अगर (dev->ishtp_host_dma_rx_buf) अणु
		h = dev->ishtp_host_dma_rx_buf_phys;
		dma_मुक्त_coherent(dev->devc, dev->ishtp_host_dma_rx_buf_size,
				  dev->ishtp_host_dma_rx_buf, h);
	पूर्ण

	kमुक्त(dev->ishtp_dma_tx_map);
	dev->ishtp_host_dma_tx_buf = शून्य;
	dev->ishtp_host_dma_rx_buf = शून्य;
	dev->ishtp_dma_tx_map = शून्य;
पूर्ण

/*
 * ishtp_cl_get_dma_send_buf() - Get a DMA memory slot
 * @dev:	ishtp device
 * @size:	Size of memory to get
 *
 * Find and वापस मुक्त address of "size" bytes in dma tx buffer.
 * the function will mark this address as "in-used" memory.
 *
 * Return: शून्य when no मुक्त buffer अन्यथा a buffer to copy
 */
व्योम *ishtp_cl_get_dma_send_buf(काष्ठा ishtp_device *dev,
				uपूर्णांक32_t size)
अणु
	अचिन्हित दीर्घ	flags;
	पूर्णांक i, j, मुक्त;
	/* additional slot is needed अगर there is rem */
	पूर्णांक required_slots = (size / DMA_SLOT_SIZE)
		+ 1 * (size % DMA_SLOT_SIZE != 0);

	spin_lock_irqsave(&dev->ishtp_dma_tx_lock, flags);
	क्रम (i = 0; i <= (dev->ishtp_dma_num_slots - required_slots); i++) अणु
		मुक्त = 1;
		क्रम (j = 0; j < required_slots; j++)
			अगर (dev->ishtp_dma_tx_map[i+j]) अणु
				मुक्त = 0;
				i += j;
				अवरोध;
			पूर्ण
		अगर (मुक्त) अणु
			/* mark memory as "caught" */
			क्रम (j = 0; j < required_slots; j++)
				dev->ishtp_dma_tx_map[i+j] = 1;
			spin_unlock_irqrestore(&dev->ishtp_dma_tx_lock, flags);
			वापस (i * DMA_SLOT_SIZE) +
				(अचिन्हित अक्षर *)dev->ishtp_host_dma_tx_buf;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&dev->ishtp_dma_tx_lock, flags);
	dev_err(dev->devc, "No free DMA buffer to send msg\n");
	वापस शून्य;
पूर्ण

/*
 * ishtp_cl_release_dma_acked_mem() - Release DMA memory slot
 * @dev:	ishtp device
 * @msg_addr:	message address of slot
 * @size:	Size of memory to get
 *
 * Release_dma_acked_mem - वापसes the acked memory to मुक्त list.
 * (from msg_addr, size bytes दीर्घ)
 */
व्योम ishtp_cl_release_dma_acked_mem(काष्ठा ishtp_device *dev,
				    व्योम *msg_addr,
				    uपूर्णांक8_t size)
अणु
	अचिन्हित दीर्घ	flags;
	पूर्णांक acked_slots = (size / DMA_SLOT_SIZE)
		+ 1 * (size % DMA_SLOT_SIZE != 0);
	पूर्णांक i, j;

	अगर ((msg_addr - dev->ishtp_host_dma_tx_buf) % DMA_SLOT_SIZE) अणु
		dev_err(dev->devc, "Bad DMA Tx ack address\n");
		वापस;
	पूर्ण

	i = (msg_addr - dev->ishtp_host_dma_tx_buf) / DMA_SLOT_SIZE;
	spin_lock_irqsave(&dev->ishtp_dma_tx_lock, flags);
	क्रम (j = 0; j < acked_slots; j++) अणु
		अगर ((i + j) >= dev->ishtp_dma_num_slots ||
					!dev->ishtp_dma_tx_map[i+j]) अणु
			/* no such slot, or memory is alपढ़ोy मुक्त */
			spin_unlock_irqrestore(&dev->ishtp_dma_tx_lock, flags);
			dev_err(dev->devc, "Bad DMA Tx ack address\n");
			वापस;
		पूर्ण
		dev->ishtp_dma_tx_map[i+j] = 0;
	पूर्ण
	spin_unlock_irqrestore(&dev->ishtp_dma_tx_lock, flags);
पूर्ण
