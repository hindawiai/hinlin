<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  Copyright (C) 2002 Intersil Americas Inc.
 *  Copyright 2004 Jens Maurer <Jens.Maurer@gmx.net>
 */

#समावेश <linux/netdevice.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>

#समावेश <यंत्र/पन.स>
#समावेश <linux/अगर_arp.h>

#समावेश "prismcompat.h"
#समावेश "isl_38xx.h"
#समावेश "islpci_mgt.h"
#समावेश "isl_oid.h"		/* additional types and defs क्रम isl38xx fw */
#समावेश "isl_ioctl.h"

#समावेश <net/iw_handler.h>

/******************************************************************************
        Global variable definition section
******************************************************************************/
पूर्णांक pc_debug = VERBOSE;
module_param(pc_debug, पूर्णांक, 0);

/******************************************************************************
    Driver general functions
******************************************************************************/
#अगर VERBOSE > SHOW_ERROR_MESSAGES
व्योम
display_buffer(अक्षर *buffer, पूर्णांक length)
अणु
	अगर ((pc_debug & SHOW_BUFFER_CONTENTS) == 0)
		वापस;

	जबतक (length > 0) अणु
		prपूर्णांकk("[%02x]", *buffer & 255);
		length--;
		buffer++;
	पूर्ण

	prपूर्णांकk("\n");
पूर्ण
#पूर्ण_अगर

/*****************************************************************************
    Queue handling क्रम management frames
******************************************************************************/

/*
 * Helper function to create a PIMFOR management frame header.
 */
अटल व्योम
pimक्रम_encode_header(पूर्णांक operation, u32 oid, u32 length, pimक्रम_header_t *h)
अणु
	h->version = PIMFOR_VERSION;
	h->operation = operation;
	h->device_id = PIMFOR_DEV_ID_MHLI_MIB;
	h->flags = 0;
	h->oid = cpu_to_be32(oid);
	h->length = cpu_to_be32(length);
पूर्ण

/*
 * Helper function to analyze a PIMFOR management frame header.
 */
अटल pimक्रम_header_t *
pimक्रम_decode_header(व्योम *data, पूर्णांक len)
अणु
	pimक्रम_header_t *h = data;

	जबतक ((व्योम *) h < data + len) अणु
		अगर (h->flags & PIMFOR_FLAG_LITTLE_ENDIAN) अणु
			le32_to_cpus(&h->oid);
			le32_to_cpus(&h->length);
		पूर्ण अन्यथा अणु
			be32_to_cpus(&h->oid);
			be32_to_cpus(&h->length);
		पूर्ण
		अगर (h->oid != OID_INL_TUNNEL)
			वापस h;
		h++;
	पूर्ण
	वापस शून्य;
पूर्ण

/*
 * Fill the receive queue क्रम management frames with fresh buffers.
 */
पूर्णांक
islpci_mgmt_rx_fill(काष्ठा net_device *ndev)
अणु
	islpci_निजी *priv = netdev_priv(ndev);
	isl38xx_control_block *cb =	/* अस्थिर not needed */
	    (isl38xx_control_block *) priv->control_block;
	u32 curr = le32_to_cpu(cb->driver_curr_frag[ISL38XX_CB_RX_MGMTQ]);

#अगर VERBOSE > SHOW_ERROR_MESSAGES
	DEBUG(SHOW_FUNCTION_CALLS, "islpci_mgmt_rx_fill\n");
#पूर्ण_अगर

	जबतक (curr - priv->index_mgmt_rx < ISL38XX_CB_MGMT_QSIZE) अणु
		u32 index = curr % ISL38XX_CB_MGMT_QSIZE;
		काष्ठा islpci_membuf *buf = &priv->mgmt_rx[index];
		isl38xx_fragment *frag = &cb->rx_data_mgmt[index];

		अगर (buf->mem == शून्य) अणु
			buf->mem = kदो_स्मृति(MGMT_FRAME_SIZE, GFP_ATOMIC);
			अगर (!buf->mem)
				वापस -ENOMEM;
			buf->size = MGMT_FRAME_SIZE;
		पूर्ण
		अगर (buf->pci_addr == 0) अणु
			buf->pci_addr = dma_map_single(&priv->pdev->dev,
						       buf->mem,
						       MGMT_FRAME_SIZE,
						       DMA_FROM_DEVICE);
			अगर (dma_mapping_error(&priv->pdev->dev, buf->pci_addr)) अणु
				prपूर्णांकk(KERN_WARNING
				       "Failed to make memory DMA'able.\n");
				वापस -ENOMEM;
			पूर्ण
		पूर्ण

		/* be safe: always reset control block inक्रमmation */
		frag->size = cpu_to_le16(MGMT_FRAME_SIZE);
		frag->flags = 0;
		frag->address = cpu_to_le32(buf->pci_addr);
		curr++;

		/* The fragment address in the control block must have
		 * been written beक्रमe announcing the frame buffer to
		 * device */
		wmb();
		cb->driver_curr_frag[ISL38XX_CB_RX_MGMTQ] = cpu_to_le32(curr);
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Create and transmit a management frame using "operation" and "oid",
 * with arguments data/length.
 * We either वापस an error and मुक्त the frame, or we वापस 0 and
 * islpci_mgt_cleanup_transmit() मुक्तs the frame in the tx-करोne
 * पूर्णांकerrupt.
 */
अटल पूर्णांक
islpci_mgt_transmit(काष्ठा net_device *ndev, पूर्णांक operation, अचिन्हित दीर्घ oid,
		    व्योम *data, पूर्णांक length)
अणु
	islpci_निजी *priv = netdev_priv(ndev);
	isl38xx_control_block *cb =
	    (isl38xx_control_block *) priv->control_block;
	व्योम *p;
	पूर्णांक err = -EINVAL;
	अचिन्हित दीर्घ flags;
	isl38xx_fragment *frag;
	काष्ठा islpci_membuf buf;
	u32 curr_frag;
	पूर्णांक index;
	पूर्णांक frag_len = length + PIMFOR_HEADER_SIZE;

#अगर VERBOSE > SHOW_ERROR_MESSAGES
	DEBUG(SHOW_FUNCTION_CALLS, "islpci_mgt_transmit\n");
#पूर्ण_अगर

	अगर (frag_len > MGMT_FRAME_SIZE) अणु
		prपूर्णांकk(KERN_DEBUG "%s: mgmt frame too large %d\n",
		       ndev->name, frag_len);
		जाओ error;
	पूर्ण

	err = -ENOMEM;
	p = buf.mem = kदो_स्मृति(frag_len, GFP_KERNEL);
	अगर (!buf.mem)
		जाओ error;

	buf.size = frag_len;

	/* create the header directly in the fragment data area */
	pimक्रम_encode_header(operation, oid, length, (pimक्रम_header_t *) p);
	p += PIMFOR_HEADER_SIZE;

	अगर (data)
		स_नकल(p, data, length);
	अन्यथा
		स_रखो(p, 0, length);

#अगर VERBOSE > SHOW_ERROR_MESSAGES
	अणु
		pimक्रम_header_t *h = buf.mem;
		DEBUG(SHOW_PIMFOR_FRAMES,
		      "PIMFOR: op %i, oid 0x%08lx, device %i, flags 0x%x length 0x%x\n",
		      h->operation, oid, h->device_id, h->flags, length);

		/* display the buffer contents क्रम debugging */
		display_buffer((अक्षर *) h, माप (pimक्रम_header_t));
		display_buffer(p, length);
	पूर्ण
#पूर्ण_अगर

	err = -ENOMEM;
	buf.pci_addr = dma_map_single(&priv->pdev->dev, buf.mem, frag_len,
				      DMA_TO_DEVICE);
	अगर (dma_mapping_error(&priv->pdev->dev, buf.pci_addr)) अणु
		prपूर्णांकk(KERN_WARNING "%s: cannot map PCI memory for mgmt\n",
		       ndev->name);
		जाओ error_मुक्त;
	पूर्ण

	/* Protect the control block modअगरications against पूर्णांकerrupts. */
	spin_lock_irqsave(&priv->slock, flags);
	curr_frag = le32_to_cpu(cb->driver_curr_frag[ISL38XX_CB_TX_MGMTQ]);
	अगर (curr_frag - priv->index_mgmt_tx >= ISL38XX_CB_MGMT_QSIZE) अणु
		prपूर्णांकk(KERN_WARNING "%s: mgmt tx queue is still full\n",
		       ndev->name);
		जाओ error_unlock;
	पूर्ण

	/* commit the frame to the tx device queue */
	index = curr_frag % ISL38XX_CB_MGMT_QSIZE;
	priv->mgmt_tx[index] = buf;
	frag = &cb->tx_data_mgmt[index];
	frag->size = cpu_to_le16(frag_len);
	frag->flags = 0;	/* क्रम any other than the last fragment, set to 1 */
	frag->address = cpu_to_le32(buf.pci_addr);

	/* The fragment address in the control block must have
	 * been written beक्रमe announcing the frame buffer to
	 * device */
	wmb();
	cb->driver_curr_frag[ISL38XX_CB_TX_MGMTQ] = cpu_to_le32(curr_frag + 1);
	spin_unlock_irqrestore(&priv->slock, flags);

	/* trigger the device */
	islpci_trigger(priv);
	वापस 0;

      error_unlock:
	spin_unlock_irqrestore(&priv->slock, flags);
      error_मुक्त:
	kमुक्त(buf.mem);
      error:
	वापस err;
पूर्ण

/*
 * Receive a management frame from the device.
 * This can be an arbitrary number of traps, and at most one response
 * frame क्रम a previous request sent via islpci_mgt_transmit().
 */
पूर्णांक
islpci_mgt_receive(काष्ठा net_device *ndev)
अणु
	islpci_निजी *priv = netdev_priv(ndev);
	isl38xx_control_block *cb =
	    (isl38xx_control_block *) priv->control_block;
	u32 curr_frag;

#अगर VERBOSE > SHOW_ERROR_MESSAGES
	DEBUG(SHOW_FUNCTION_CALLS, "islpci_mgt_receive\n");
#पूर्ण_अगर

	/* Only once per पूर्णांकerrupt, determine fragment range to
	 * process.  This aव्योमs an endless loop (i.e. lockup) अगर
	 * frames come in faster than we can process them. */
	curr_frag = le32_to_cpu(cb->device_curr_frag[ISL38XX_CB_RX_MGMTQ]);
	barrier();

	क्रम (; priv->index_mgmt_rx < curr_frag; priv->index_mgmt_rx++) अणु
		pimक्रम_header_t *header;
		u32 index = priv->index_mgmt_rx % ISL38XX_CB_MGMT_QSIZE;
		काष्ठा islpci_membuf *buf = &priv->mgmt_rx[index];
		u16 frag_len;
		पूर्णांक size;
		काष्ठा islpci_mgmtframe *frame;

		/* I have no idea (and no करोcumentation) अगर flags != 0
		 * is possible.  Drop the frame, reuse the buffer. */
		अगर (le16_to_cpu(cb->rx_data_mgmt[index].flags) != 0) अणु
			prपूर्णांकk(KERN_WARNING "%s: unknown flags 0x%04x\n",
			       ndev->name,
			       le16_to_cpu(cb->rx_data_mgmt[index].flags));
			जारी;
		पूर्ण

		/* The device only वापसs the size of the header(s) here. */
		frag_len = le16_to_cpu(cb->rx_data_mgmt[index].size);

		/*
		 * We appear to have no way to tell the device the
		 * size of a receive buffer.  Thus, अगर this check
		 * triggers, we likely have kernel heap corruption. */
		अगर (frag_len > MGMT_FRAME_SIZE) अणु
			prपूर्णांकk(KERN_WARNING
				"%s: Bogus packet size of %d (%#x).\n",
				ndev->name, frag_len, frag_len);
			frag_len = MGMT_FRAME_SIZE;
		पूर्ण

		/* Ensure the results of device DMA are visible to the CPU. */
		dma_sync_single_क्रम_cpu(&priv->pdev->dev, buf->pci_addr,
					buf->size, DMA_FROM_DEVICE);

		/* Perक्रमm endianess conversion क्रम PIMFOR header in-place. */
		header = pimक्रम_decode_header(buf->mem, frag_len);
		अगर (!header) अणु
			prपूर्णांकk(KERN_WARNING "%s: no PIMFOR header found\n",
			       ndev->name);
			जारी;
		पूर्ण

		/* The device ID from the PIMFOR packet received from
		 * the MVC is always 0.  We क्रमward a sensible device_id.
		 * Not that anyone upstream would care... */
		header->device_id = priv->ndev->अगरindex;

#अगर VERBOSE > SHOW_ERROR_MESSAGES
		DEBUG(SHOW_PIMFOR_FRAMES,
		      "PIMFOR: op %i, oid 0x%08x, device %i, flags 0x%x length 0x%x\n",
		      header->operation, header->oid, header->device_id,
		      header->flags, header->length);

		/* display the buffer contents क्रम debugging */
		display_buffer((अक्षर *) header, PIMFOR_HEADER_SIZE);
		display_buffer((अक्षर *) header + PIMFOR_HEADER_SIZE,
			       header->length);
#पूर्ण_अगर

		/* nobody sends these */
		अगर (header->flags & PIMFOR_FLAG_APPLIC_ORIGIN) अणु
			prपूर्णांकk(KERN_DEBUG
			       "%s: errant PIMFOR application frame\n",
			       ndev->name);
			जारी;
		पूर्ण

		/* Determine frame size, skipping OID_INL_TUNNEL headers. */
		size = PIMFOR_HEADER_SIZE + header->length;
		frame = kदो_स्मृति(माप(काष्ठा islpci_mgmtframe) + size,
				GFP_ATOMIC);
		अगर (!frame)
			जारी;

		frame->ndev = ndev;
		स_नकल(&frame->buf, header, size);
		frame->header = (pimक्रम_header_t *) frame->buf;
		frame->data = frame->buf + PIMFOR_HEADER_SIZE;

#अगर VERBOSE > SHOW_ERROR_MESSAGES
		DEBUG(SHOW_PIMFOR_FRAMES,
		      "frame: header: %p, data: %p, size: %d\n",
		      frame->header, frame->data, size);
#पूर्ण_अगर

		अगर (header->operation == PIMFOR_OP_TRAP) अणु
#अगर VERBOSE > SHOW_ERROR_MESSAGES
			prपूर्णांकk(KERN_DEBUG
			       "TRAP: oid 0x%x, device %i, flags 0x%x length %i\n",
			       header->oid, header->device_id, header->flags,
			       header->length);
#पूर्ण_अगर

			/* Create work to handle trap out of पूर्णांकerrupt
			 * context. */
			INIT_WORK(&frame->ws, prism54_process_trap);
			schedule_work(&frame->ws);

		पूर्ण अन्यथा अणु
			/* Signal the one रुकोing process that a response
			 * has been received. */
			अगर ((frame = xchg(&priv->mgmt_received, frame)) != शून्य) अणु
				prपूर्णांकk(KERN_WARNING
				       "%s: mgmt response not collected\n",
				       ndev->name);
				kमुक्त(frame);
			पूर्ण
#अगर VERBOSE > SHOW_ERROR_MESSAGES
			DEBUG(SHOW_TRACING, "Wake up Mgmt Queue\n");
#पूर्ण_अगर
			wake_up(&priv->mgmt_wqueue);
		पूर्ण

	पूर्ण

	वापस 0;
पूर्ण

/*
 * Cleanup the transmit queue by मुक्तing all frames handled by the device.
 */
व्योम
islpci_mgt_cleanup_transmit(काष्ठा net_device *ndev)
अणु
	islpci_निजी *priv = netdev_priv(ndev);
	isl38xx_control_block *cb =	/* अस्थिर not needed */
	    (isl38xx_control_block *) priv->control_block;
	u32 curr_frag;

#अगर VERBOSE > SHOW_ERROR_MESSAGES
	DEBUG(SHOW_FUNCTION_CALLS, "islpci_mgt_cleanup_transmit\n");
#पूर्ण_अगर

	/* Only once per cleanup, determine fragment range to
	 * process.  This aव्योमs an endless loop (i.e. lockup) अगर
	 * the device became confused, incrementing device_curr_frag
	 * rapidly. */
	curr_frag = le32_to_cpu(cb->device_curr_frag[ISL38XX_CB_TX_MGMTQ]);
	barrier();

	क्रम (; priv->index_mgmt_tx < curr_frag; priv->index_mgmt_tx++) अणु
		पूर्णांक index = priv->index_mgmt_tx % ISL38XX_CB_MGMT_QSIZE;
		काष्ठा islpci_membuf *buf = &priv->mgmt_tx[index];
		dma_unmap_single(&priv->pdev->dev, buf->pci_addr, buf->size,
				 DMA_TO_DEVICE);
		buf->pci_addr = 0;
		kमुक्त(buf->mem);
		buf->mem = शून्य;
		buf->size = 0;
	पूर्ण
पूर्ण

/*
 * Perक्रमm one request-response transaction to the device.
 */
पूर्णांक
islpci_mgt_transaction(काष्ठा net_device *ndev,
		       पूर्णांक operation, अचिन्हित दीर्घ oid,
		       व्योम *senddata, पूर्णांक sendlen,
		       काष्ठा islpci_mgmtframe **recvframe)
अणु
	islpci_निजी *priv = netdev_priv(ndev);
	स्थिर दीर्घ रुको_cycle_jअगरfies = msecs_to_jअगरfies(ISL38XX_WAIT_CYCLE * 10);
	दीर्घ समयout_left = ISL38XX_MAX_WAIT_CYCLES * रुको_cycle_jअगरfies;
	पूर्णांक err;
	DEFINE_WAIT(रुको);

	*recvframe = शून्य;

	अगर (mutex_lock_पूर्णांकerruptible(&priv->mgmt_lock))
		वापस -ERESTARTSYS;

	prepare_to_रुको(&priv->mgmt_wqueue, &रुको, TASK_UNINTERRUPTIBLE);
	err = islpci_mgt_transmit(ndev, operation, oid, senddata, sendlen);
	अगर (err)
		जाओ out;

	err = -ETIMEDOUT;
	जबतक (समयout_left > 0) अणु
		पूर्णांक समयleft;
		काष्ठा islpci_mgmtframe *frame;

		समयleft = schedule_समयout_unपूर्णांकerruptible(रुको_cycle_jअगरfies);
		frame = xchg(&priv->mgmt_received, शून्य);
		अगर (frame) अणु
			अगर (frame->header->oid == oid) अणु
				*recvframe = frame;
				err = 0;
				जाओ out;
			पूर्ण अन्यथा अणु
				prपूर्णांकk(KERN_DEBUG
				       "%s: expecting oid 0x%x, received 0x%x.\n",
				       ndev->name, (अचिन्हित पूर्णांक) oid,
				       frame->header->oid);
				kमुक्त(frame);
				frame = शून्य;
			पूर्ण
		पूर्ण
		अगर (समयleft == 0) अणु
			prपूर्णांकk(KERN_DEBUG
				"%s: timeout waiting for mgmt response %lu, "
				"triggering device\n",
				ndev->name, समयout_left);
			islpci_trigger(priv);
		पूर्ण
		समयout_left += समयleft - रुको_cycle_jअगरfies;
	पूर्ण
	prपूर्णांकk(KERN_WARNING "%s: timeout waiting for mgmt response\n",
	       ndev->name);

	/* TODO: we should reset the device here */
 out:
	finish_रुको(&priv->mgmt_wqueue, &रुको);
	mutex_unlock(&priv->mgmt_lock);
	वापस err;
पूर्ण

