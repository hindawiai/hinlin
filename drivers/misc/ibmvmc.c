<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * IBM Power Systems Virtual Management Channel Support.
 *
 * Copyright (c) 2004, 2018 IBM Corp.
 *   Dave Engebretsen engebret@us.ibm.com
 *   Steven Royer seroyer@linux.vnet.ibm.com
 *   Adam Reznechek adreznec@linux.vnet.ibm.com
 *   Bryant G. Ly <bryantly@linux.vnet.ibm.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/major.h>
#समावेश <linux/माला.स>
#समावेश <linux/fcntl.h>
#समावेश <linux/slab.h>
#समावेश <linux/poll.h>
#समावेश <linux/init.h>
#समावेश <linux/fs.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/percpu.h>
#समावेश <linux/delay.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/पन.स>
#समावेश <linux/miscdevice.h>
#समावेश <linux/sched/संकेत.स>

#समावेश <यंत्र/byteorder.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/vपन.स>

#समावेश "ibmvmc.h"

#घोषणा IBMVMC_DRIVER_VERSION "1.0"

/*
 * Static global variables
 */
अटल DECLARE_WAIT_QUEUE_HEAD(ibmvmc_पढ़ो_रुको);

अटल स्थिर अक्षर ibmvmc_driver_name[] = "ibmvmc";

अटल काष्ठा ibmvmc_काष्ठा ibmvmc;
अटल काष्ठा ibmvmc_hmc hmcs[MAX_HMCS];
अटल काष्ठा crq_server_adapter ibmvmc_adapter;

अटल पूर्णांक ibmvmc_max_buf_pool_size = DEFAULT_BUF_POOL_SIZE;
अटल पूर्णांक ibmvmc_max_hmcs = DEFAULT_HMCS;
अटल पूर्णांक ibmvmc_max_mtu = DEFAULT_MTU;

अटल अंतरभूत दीर्घ h_copy_rdma(s64 length, u64 sliobn, u64 slioba,
			       u64 dliobn, u64 dlioba)
अणु
	दीर्घ rc = 0;

	/* Ensure all ग_लिखोs to source memory are visible beक्रमe hcall */
	dma_wmb();
	pr_debug("ibmvmc: h_copy_rdma(0x%llx, 0x%llx, 0x%llx, 0x%llx, 0x%llx\n",
		 length, sliobn, slioba, dliobn, dlioba);
	rc = plpar_hcall_norets(H_COPY_RDMA, length, sliobn, slioba,
				dliobn, dlioba);
	pr_debug("ibmvmc: h_copy_rdma rc = 0x%lx\n", rc);

	वापस rc;
पूर्ण

अटल अंतरभूत व्योम h_मुक्त_crq(uपूर्णांक32_t unit_address)
अणु
	दीर्घ rc = 0;

	करो अणु
		अगर (H_IS_LONG_BUSY(rc))
			msleep(get_दीर्घbusy_msecs(rc));

		rc = plpar_hcall_norets(H_FREE_CRQ, unit_address);
	पूर्ण जबतक ((rc == H_BUSY) || (H_IS_LONG_BUSY(rc)));
पूर्ण

/**
 * h_request_vmc: - request a hypervisor भव management channel device
 * @vmc_index: drc index of the vmc device created
 *
 * Requests the hypervisor create a new भव management channel device,
 * allowing this partition to send hypervisor भवization control
 * commands.
 *
 * Return:
 *	0 - Success
 *	Non-zero - Failure
 */
अटल अंतरभूत दीर्घ h_request_vmc(u32 *vmc_index)
अणु
	दीर्घ rc = 0;
	अचिन्हित दीर्घ retbuf[PLPAR_HCALL_बफ_मानE];

	करो अणु
		अगर (H_IS_LONG_BUSY(rc))
			msleep(get_दीर्घbusy_msecs(rc));

		/* Call to request the VMC device from phyp */
		rc = plpar_hcall(H_REQUEST_VMC, retbuf);
		pr_debug("ibmvmc: %s rc = 0x%lx\n", __func__, rc);
		*vmc_index = retbuf[0];
	पूर्ण जबतक ((rc == H_BUSY) || (H_IS_LONG_BUSY(rc)));

	वापस rc;
पूर्ण

/* routines क्रम managing a command/response queue */
/**
 * ibmvmc_handle_event: - Interrupt handler क्रम crq events
 * @irq:        number of irq to handle, not used
 * @dev_instance: crq_server_adapter that received पूर्णांकerrupt
 *
 * Disables पूर्णांकerrupts and schedules ibmvmc_task
 *
 * Always वापसs IRQ_HANDLED
 */
अटल irqवापस_t ibmvmc_handle_event(पूर्णांक irq, व्योम *dev_instance)
अणु
	काष्ठा crq_server_adapter *adapter =
		(काष्ठा crq_server_adapter *)dev_instance;

	vio_disable_पूर्णांकerrupts(to_vio_dev(adapter->dev));
	tasklet_schedule(&adapter->work_task);

	वापस IRQ_HANDLED;
पूर्ण

/**
 * ibmvmc_release_crq_queue - Release CRQ Queue
 *
 * @adapter:	crq_server_adapter काष्ठा
 *
 * Return:
 *	0 - Success
 *	Non-Zero - Failure
 */
अटल व्योम ibmvmc_release_crq_queue(काष्ठा crq_server_adapter *adapter)
अणु
	काष्ठा vio_dev *vdev = to_vio_dev(adapter->dev);
	काष्ठा crq_queue *queue = &adapter->queue;

	मुक्त_irq(vdev->irq, (व्योम *)adapter);
	tasklet_समाप्त(&adapter->work_task);

	अगर (adapter->reset_task)
		kthपढ़ो_stop(adapter->reset_task);

	h_मुक्त_crq(vdev->unit_address);
	dma_unmap_single(adapter->dev,
			 queue->msg_token,
			 queue->size * माप(*queue->msgs), DMA_BIसूचीECTIONAL);
	मुक्त_page((अचिन्हित दीर्घ)queue->msgs);
पूर्ण

/**
 * ibmvmc_reset_crq_queue - Reset CRQ Queue
 *
 * @adapter:	crq_server_adapter काष्ठा
 *
 * This function calls h_मुक्त_crq and then calls H_REG_CRQ and करोes all the
 * bookkeeping to get us back to where we can communicate.
 *
 * Return:
 *	0 - Success
 *	Non-Zero - Failure
 */
अटल पूर्णांक ibmvmc_reset_crq_queue(काष्ठा crq_server_adapter *adapter)
अणु
	काष्ठा vio_dev *vdev = to_vio_dev(adapter->dev);
	काष्ठा crq_queue *queue = &adapter->queue;
	पूर्णांक rc = 0;

	/* Close the CRQ */
	h_मुक्त_crq(vdev->unit_address);

	/* Clean out the queue */
	स_रखो(queue->msgs, 0x00, PAGE_SIZE);
	queue->cur = 0;

	/* And re-खोलो it again */
	rc = plpar_hcall_norets(H_REG_CRQ,
				vdev->unit_address,
				queue->msg_token, PAGE_SIZE);
	अगर (rc == 2)
		/* Adapter is good, but other end is not पढ़ोy */
		dev_warn(adapter->dev, "Partner adapter not ready\n");
	अन्यथा अगर (rc != 0)
		dev_err(adapter->dev, "couldn't register crq--rc 0x%x\n", rc);

	वापस rc;
पूर्ण

/**
 * crq_queue_next_crq: - Returns the next entry in message queue
 * @queue:      crq_queue to use
 *
 * Returns poपूर्णांकer to next entry in queue, or शून्य अगर there are no new
 * entried in the CRQ.
 */
अटल काष्ठा ibmvmc_crq_msg *crq_queue_next_crq(काष्ठा crq_queue *queue)
अणु
	काष्ठा ibmvmc_crq_msg *crq;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&queue->lock, flags);
	crq = &queue->msgs[queue->cur];
	अगर (crq->valid & 0x80) अणु
		अगर (++queue->cur == queue->size)
			queue->cur = 0;

		/* Ensure the पढ़ो of the valid bit occurs beक्रमe पढ़ोing any
		 * other bits of the CRQ entry
		 */
		dma_rmb();
	पूर्ण अन्यथा अणु
		crq = शून्य;
	पूर्ण

	spin_unlock_irqrestore(&queue->lock, flags);

	वापस crq;
पूर्ण

/**
 * ibmvmc_send_crq - Send CRQ
 *
 * @adapter:	crq_server_adapter काष्ठा
 * @word1:	Word1 Data field
 * @word2:	Word2 Data field
 *
 * Return:
 *	0 - Success
 *	Non-Zero - Failure
 */
अटल दीर्घ ibmvmc_send_crq(काष्ठा crq_server_adapter *adapter,
			    u64 word1, u64 word2)
अणु
	काष्ठा vio_dev *vdev = to_vio_dev(adapter->dev);
	दीर्घ rc = 0;

	dev_dbg(adapter->dev, "(0x%x, 0x%016llx, 0x%016llx)\n",
		vdev->unit_address, word1, word2);

	/*
	 * Ensure the command buffer is flushed to memory beक्रमe handing it
	 * over to the other side to prevent it from fetching any stale data.
	 */
	dma_wmb();
	rc = plpar_hcall_norets(H_SEND_CRQ, vdev->unit_address, word1, word2);
	dev_dbg(adapter->dev, "rc = 0x%lx\n", rc);

	वापस rc;
पूर्ण

/**
 * alloc_dma_buffer - Create DMA Buffer
 *
 * @vdev:	vio_dev काष्ठा
 * @size:	Size field
 * @dma_handle:	DMA address field
 *
 * Allocates memory क्रम the command queue and maps remote memory पूर्णांकo an
 * ioba.
 *
 * Returns a poपूर्णांकer to the buffer
 */
अटल व्योम *alloc_dma_buffer(काष्ठा vio_dev *vdev, माप_प्रकार size,
			      dma_addr_t *dma_handle)
अणु
	/* allocate memory */
	व्योम *buffer = kzalloc(size, GFP_ATOMIC);

	अगर (!buffer) अणु
		*dma_handle = 0;
		वापस शून्य;
	पूर्ण

	/* DMA map */
	*dma_handle = dma_map_single(&vdev->dev, buffer, size,
				     DMA_BIसूचीECTIONAL);

	अगर (dma_mapping_error(&vdev->dev, *dma_handle)) अणु
		*dma_handle = 0;
		kमुक्त_sensitive(buffer);
		वापस शून्य;
	पूर्ण

	वापस buffer;
पूर्ण

/**
 * मुक्त_dma_buffer - Free DMA Buffer
 *
 * @vdev:	vio_dev काष्ठा
 * @size:	Size field
 * @vaddr:	Address field
 * @dma_handle:	DMA address field
 *
 * Releases memory क्रम a command queue and unmaps mapped remote memory.
 */
अटल व्योम मुक्त_dma_buffer(काष्ठा vio_dev *vdev, माप_प्रकार size, व्योम *vaddr,
			    dma_addr_t dma_handle)
अणु
	/* DMA unmap */
	dma_unmap_single(&vdev->dev, dma_handle, size, DMA_BIसूचीECTIONAL);

	/* deallocate memory */
	kमुक्त_sensitive(vaddr);
पूर्ण

/**
 * ibmvmc_get_valid_hmc_buffer - Retrieve Valid HMC Buffer
 *
 * @hmc_index:	HMC Index Field
 *
 * Return:
 *	Poपूर्णांकer to ibmvmc_buffer
 */
अटल काष्ठा ibmvmc_buffer *ibmvmc_get_valid_hmc_buffer(u8 hmc_index)
अणु
	काष्ठा ibmvmc_buffer *buffer;
	काष्ठा ibmvmc_buffer *ret_buf = शून्य;
	अचिन्हित दीर्घ i;

	अगर (hmc_index > ibmvmc.max_hmc_index)
		वापस शून्य;

	buffer = hmcs[hmc_index].buffer;

	क्रम (i = 0; i < ibmvmc_max_buf_pool_size; i++) अणु
		अगर (buffer[i].valid && buffer[i].मुक्त &&
		    buffer[i].owner == VMC_BUF_OWNER_ALPHA) अणु
			buffer[i].मुक्त = 0;
			ret_buf = &buffer[i];
			अवरोध;
		पूर्ण
	पूर्ण

	वापस ret_buf;
पूर्ण

/**
 * ibmvmc_get_मुक्त_hmc_buffer - Get Free HMC Buffer
 *
 * @adapter:	crq_server_adapter काष्ठा
 * @hmc_index:	Hmc Index field
 *
 * Return:
 *	Poपूर्णांकer to ibmvmc_buffer
 */
अटल काष्ठा ibmvmc_buffer *ibmvmc_get_मुक्त_hmc_buffer(काष्ठा crq_server_adapter *adapter,
							u8 hmc_index)
अणु
	काष्ठा ibmvmc_buffer *buffer;
	काष्ठा ibmvmc_buffer *ret_buf = शून्य;
	अचिन्हित दीर्घ i;

	अगर (hmc_index > ibmvmc.max_hmc_index) अणु
		dev_info(adapter->dev, "get_free_hmc_buffer: invalid hmc_index=0x%x\n",
			 hmc_index);
		वापस शून्य;
	पूर्ण

	buffer = hmcs[hmc_index].buffer;

	क्रम (i = 0; i < ibmvmc_max_buf_pool_size; i++) अणु
		अगर (buffer[i].मुक्त &&
		    buffer[i].owner == VMC_BUF_OWNER_ALPHA) अणु
			buffer[i].मुक्त = 0;
			ret_buf = &buffer[i];
			अवरोध;
		पूर्ण
	पूर्ण

	वापस ret_buf;
पूर्ण

/**
 * ibmvmc_मुक्त_hmc_buffer - Free an HMC Buffer
 *
 * @hmc:	ibmvmc_hmc काष्ठा
 * @buffer:	ibmvmc_buffer काष्ठा
 *
 */
अटल व्योम ibmvmc_मुक्त_hmc_buffer(काष्ठा ibmvmc_hmc *hmc,
				   काष्ठा ibmvmc_buffer *buffer)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&hmc->lock, flags);
	buffer->मुक्त = 1;
	spin_unlock_irqrestore(&hmc->lock, flags);
पूर्ण

/**
 * ibmvmc_count_hmc_buffers - Count HMC Buffers
 *
 * @hmc_index:	HMC Index field
 * @valid:	Valid number of buffers field
 * @मुक्त:	Free number of buffers field
 *
 */
अटल व्योम ibmvmc_count_hmc_buffers(u8 hmc_index, अचिन्हित पूर्णांक *valid,
				     अचिन्हित पूर्णांक *मुक्त)
अणु
	काष्ठा ibmvmc_buffer *buffer;
	अचिन्हित दीर्घ i;
	अचिन्हित दीर्घ flags;

	अगर (hmc_index > ibmvmc.max_hmc_index)
		वापस;

	अगर (!valid || !मुक्त)
		वापस;

	*valid = 0; *मुक्त = 0;

	buffer = hmcs[hmc_index].buffer;
	spin_lock_irqsave(&hmcs[hmc_index].lock, flags);

	क्रम (i = 0; i < ibmvmc_max_buf_pool_size; i++) अणु
		अगर (buffer[i].valid) अणु
			*valid = *valid + 1;
			अगर (buffer[i].मुक्त)
				*मुक्त = *मुक्त + 1;
		पूर्ण
	पूर्ण

	spin_unlock_irqrestore(&hmcs[hmc_index].lock, flags);
पूर्ण

/**
 * ibmvmc_get_मुक्त_hmc - Get Free HMC
 *
 * Return:
 *	Poपूर्णांकer to an available HMC Connection
 *	Null otherwise
 */
अटल काष्ठा ibmvmc_hmc *ibmvmc_get_मुक्त_hmc(व्योम)
अणु
	अचिन्हित दीर्घ i;
	अचिन्हित दीर्घ flags;

	/*
	 * Find an available HMC connection.
	 */
	क्रम (i = 0; i <= ibmvmc.max_hmc_index; i++) अणु
		spin_lock_irqsave(&hmcs[i].lock, flags);
		अगर (hmcs[i].state == ibmhmc_state_मुक्त) अणु
			hmcs[i].index = i;
			hmcs[i].state = ibmhmc_state_initial;
			spin_unlock_irqrestore(&hmcs[i].lock, flags);
			वापस &hmcs[i];
		पूर्ण
		spin_unlock_irqrestore(&hmcs[i].lock, flags);
	पूर्ण

	वापस शून्य;
पूर्ण

/**
 * ibmvmc_वापस_hmc - Return an HMC Connection
 *
 * @hmc:		ibmvmc_hmc काष्ठा
 * @release_पढ़ोers:	Number of पढ़ोers connected to session
 *
 * This function releases the HMC connections back पूर्णांकo the pool.
 *
 * Return:
 *	0 - Success
 *	Non-zero - Failure
 */
अटल पूर्णांक ibmvmc_वापस_hmc(काष्ठा ibmvmc_hmc *hmc, bool release_पढ़ोers)
अणु
	काष्ठा ibmvmc_buffer *buffer;
	काष्ठा crq_server_adapter *adapter;
	काष्ठा vio_dev *vdev;
	अचिन्हित दीर्घ i;
	अचिन्हित दीर्घ flags;

	अगर (!hmc || !hmc->adapter)
		वापस -EIO;

	अगर (release_पढ़ोers) अणु
		अगर (hmc->file_session) अणु
			काष्ठा ibmvmc_file_session *session = hmc->file_session;

			session->valid = 0;
			wake_up_पूर्णांकerruptible(&ibmvmc_पढ़ो_रुको);
		पूर्ण
	पूर्ण

	adapter = hmc->adapter;
	vdev = to_vio_dev(adapter->dev);

	spin_lock_irqsave(&hmc->lock, flags);
	hmc->index = 0;
	hmc->state = ibmhmc_state_मुक्त;
	hmc->queue_head = 0;
	hmc->queue_tail = 0;
	buffer = hmc->buffer;
	क्रम (i = 0; i < ibmvmc_max_buf_pool_size; i++) अणु
		अगर (buffer[i].valid) अणु
			मुक्त_dma_buffer(vdev,
					ibmvmc.max_mtu,
					buffer[i].real_addr_local,
					buffer[i].dma_addr_local);
			dev_dbg(adapter->dev, "Forgot buffer id 0x%lx\n", i);
		पूर्ण
		स_रखो(&buffer[i], 0, माप(काष्ठा ibmvmc_buffer));

		hmc->queue_outbound_msgs[i] = VMC_INVALID_BUFFER_ID;
	पूर्ण

	spin_unlock_irqrestore(&hmc->lock, flags);

	वापस 0;
पूर्ण

/**
 * ibmvmc_send_खोलो - Interface Open
 * @buffer: Poपूर्णांकer to ibmvmc_buffer काष्ठा
 * @hmc: Poपूर्णांकer to ibmvmc_hmc काष्ठा
 *
 * This command is sent by the management partition as the result of a
 * management partition device request. It causes the hypervisor to
 * prepare a set of data buffers क्रम the management application connection
 * indicated HMC idx. A unique HMC Idx would be used अगर multiple management
 * applications running concurrently were desired. Beक्रमe responding to this
 * command, the hypervisor must provide the management partition with at
 * least one of these new buffers via the Add Buffer. This indicates whether
 * the messages are inbound or outbound from the hypervisor.
 *
 * Return:
 *	0 - Success
 *	Non-zero - Failure
 */
अटल पूर्णांक ibmvmc_send_खोलो(काष्ठा ibmvmc_buffer *buffer,
			    काष्ठा ibmvmc_hmc *hmc)
अणु
	काष्ठा ibmvmc_crq_msg crq_msg;
	काष्ठा crq_server_adapter *adapter;
	__be64 *crq_as_u64 = (__be64 *)&crq_msg;
	पूर्णांक rc = 0;

	अगर (!hmc || !hmc->adapter)
		वापस -EIO;

	adapter = hmc->adapter;

	dev_dbg(adapter->dev, "send_open: 0x%lx 0x%lx 0x%lx 0x%lx 0x%lx\n",
		(अचिन्हित दीर्घ)buffer->size, (अचिन्हित दीर्घ)adapter->liobn,
		(अचिन्हित दीर्घ)buffer->dma_addr_local,
		(अचिन्हित दीर्घ)adapter->riobn,
		(अचिन्हित दीर्घ)buffer->dma_addr_remote);

	rc = h_copy_rdma(buffer->size,
			 adapter->liobn,
			 buffer->dma_addr_local,
			 adapter->riobn,
			 buffer->dma_addr_remote);
	अगर (rc) अणु
		dev_err(adapter->dev, "Error: In send_open, h_copy_rdma rc 0x%x\n",
			rc);
		वापस -EIO;
	पूर्ण

	hmc->state = ibmhmc_state_खोलोing;

	crq_msg.valid = 0x80;
	crq_msg.type = VMC_MSG_OPEN;
	crq_msg.status = 0;
	crq_msg.var1.rsvd = 0;
	crq_msg.hmc_session = hmc->session;
	crq_msg.hmc_index = hmc->index;
	crq_msg.var2.buffer_id = cpu_to_be16(buffer->id);
	crq_msg.rsvd = 0;
	crq_msg.var3.rsvd = 0;

	ibmvmc_send_crq(adapter, be64_to_cpu(crq_as_u64[0]),
			be64_to_cpu(crq_as_u64[1]));

	वापस rc;
पूर्ण

/**
 * ibmvmc_send_बंद - Interface Close
 * @hmc: Poपूर्णांकer to ibmvmc_hmc काष्ठा
 *
 * This command is sent by the management partition to terminate a
 * management application to hypervisor connection. When this command is
 * sent, the management partition has quiesced all I/O operations to all
 * buffers associated with this management application connection, and
 * has मुक्तd any storage क्रम these buffers.
 *
 * Return:
 *	0 - Success
 *	Non-zero - Failure
 */
अटल पूर्णांक ibmvmc_send_बंद(काष्ठा ibmvmc_hmc *hmc)
अणु
	काष्ठा ibmvmc_crq_msg crq_msg;
	काष्ठा crq_server_adapter *adapter;
	__be64 *crq_as_u64 = (__be64 *)&crq_msg;
	पूर्णांक rc = 0;

	अगर (!hmc || !hmc->adapter)
		वापस -EIO;

	adapter = hmc->adapter;

	dev_info(adapter->dev, "CRQ send: close\n");

	crq_msg.valid = 0x80;
	crq_msg.type = VMC_MSG_CLOSE;
	crq_msg.status = 0;
	crq_msg.var1.rsvd = 0;
	crq_msg.hmc_session = hmc->session;
	crq_msg.hmc_index = hmc->index;
	crq_msg.var2.rsvd = 0;
	crq_msg.rsvd = 0;
	crq_msg.var3.rsvd = 0;

	ibmvmc_send_crq(adapter, be64_to_cpu(crq_as_u64[0]),
			be64_to_cpu(crq_as_u64[1]));

	वापस rc;
पूर्ण

/**
 * ibmvmc_send_capabilities - Send VMC Capabilities
 *
 * @adapter:	crq_server_adapter काष्ठा
 *
 * The capabilities message is an administrative message sent after the CRQ
 * initialization sequence of messages and is used to exchange VMC capabilities
 * between the management partition and the hypervisor. The management
 * partition must send this message and the hypervisor must respond with VMC
 * capabilities Response message beक्रमe HMC पूर्णांकerface message can begin. Any
 * HMC पूर्णांकerface messages received beक्रमe the exchange of capabilities has
 * complete are dropped.
 *
 * Return:
 *	0 - Success
 */
अटल पूर्णांक ibmvmc_send_capabilities(काष्ठा crq_server_adapter *adapter)
अणु
	काष्ठा ibmvmc_admin_crq_msg crq_msg;
	__be64 *crq_as_u64 = (__be64 *)&crq_msg;

	dev_dbg(adapter->dev, "ibmvmc: CRQ send: capabilities\n");
	crq_msg.valid = 0x80;
	crq_msg.type = VMC_MSG_CAP;
	crq_msg.status = 0;
	crq_msg.rsvd[0] = 0;
	crq_msg.rsvd[1] = 0;
	crq_msg.max_hmc = ibmvmc_max_hmcs;
	crq_msg.max_mtu = cpu_to_be32(ibmvmc_max_mtu);
	crq_msg.pool_size = cpu_to_be16(ibmvmc_max_buf_pool_size);
	crq_msg.crq_size = cpu_to_be16(adapter->queue.size);
	crq_msg.version = cpu_to_be16(IBMVMC_PROTOCOL_VERSION);

	ibmvmc_send_crq(adapter, be64_to_cpu(crq_as_u64[0]),
			be64_to_cpu(crq_as_u64[1]));

	ibmvmc.state = ibmvmc_state_capabilities;

	वापस 0;
पूर्ण

/**
 * ibmvmc_send_add_buffer_resp - Add Buffer Response
 *
 * @adapter:	crq_server_adapter काष्ठा
 * @status:	Status field
 * @hmc_session: HMC Session field
 * @hmc_index:	HMC Index field
 * @buffer_id:	Buffer Id field
 *
 * This command is sent by the management partition to the hypervisor in
 * response to the Add Buffer message. The Status field indicates the result of
 * the command.
 *
 * Return:
 *	0 - Success
 */
अटल पूर्णांक ibmvmc_send_add_buffer_resp(काष्ठा crq_server_adapter *adapter,
				       u8 status, u8 hmc_session,
				       u8 hmc_index, u16 buffer_id)
अणु
	काष्ठा ibmvmc_crq_msg crq_msg;
	__be64 *crq_as_u64 = (__be64 *)&crq_msg;

	dev_dbg(adapter->dev, "CRQ send: add_buffer_resp\n");
	crq_msg.valid = 0x80;
	crq_msg.type = VMC_MSG_ADD_BUF_RESP;
	crq_msg.status = status;
	crq_msg.var1.rsvd = 0;
	crq_msg.hmc_session = hmc_session;
	crq_msg.hmc_index = hmc_index;
	crq_msg.var2.buffer_id = cpu_to_be16(buffer_id);
	crq_msg.rsvd = 0;
	crq_msg.var3.rsvd = 0;

	ibmvmc_send_crq(adapter, be64_to_cpu(crq_as_u64[0]),
			be64_to_cpu(crq_as_u64[1]));

	वापस 0;
पूर्ण

/**
 * ibmvmc_send_rem_buffer_resp - Remove Buffer Response
 *
 * @adapter:	crq_server_adapter काष्ठा
 * @status:	Status field
 * @hmc_session: HMC Session field
 * @hmc_index:	HMC Index field
 * @buffer_id:	Buffer Id field
 *
 * This command is sent by the management partition to the hypervisor in
 * response to the Remove Buffer message. The Buffer ID field indicates
 * which buffer the management partition selected to हटाओ. The Status
 * field indicates the result of the command.
 *
 * Return:
 *	0 - Success
 */
अटल पूर्णांक ibmvmc_send_rem_buffer_resp(काष्ठा crq_server_adapter *adapter,
				       u8 status, u8 hmc_session,
				       u8 hmc_index, u16 buffer_id)
अणु
	काष्ठा ibmvmc_crq_msg crq_msg;
	__be64 *crq_as_u64 = (__be64 *)&crq_msg;

	dev_dbg(adapter->dev, "CRQ send: rem_buffer_resp\n");
	crq_msg.valid = 0x80;
	crq_msg.type = VMC_MSG_REM_BUF_RESP;
	crq_msg.status = status;
	crq_msg.var1.rsvd = 0;
	crq_msg.hmc_session = hmc_session;
	crq_msg.hmc_index = hmc_index;
	crq_msg.var2.buffer_id = cpu_to_be16(buffer_id);
	crq_msg.rsvd = 0;
	crq_msg.var3.rsvd = 0;

	ibmvmc_send_crq(adapter, be64_to_cpu(crq_as_u64[0]),
			be64_to_cpu(crq_as_u64[1]));

	वापस 0;
पूर्ण

/**
 * ibmvmc_send_msg - Signal Message
 *
 * @adapter:	crq_server_adapter काष्ठा
 * @buffer:	ibmvmc_buffer काष्ठा
 * @hmc:	ibmvmc_hmc काष्ठा
 * @msg_len:	message length field
 *
 * This command is sent between the management partition and the hypervisor
 * in order to संकेत the arrival of an HMC protocol message. The command
 * can be sent by both the management partition and the hypervisor. It is
 * used क्रम all traffic between the management application and the hypervisor,
 * regardless of who initiated the communication.
 *
 * There is no response to this message.
 *
 * Return:
 *	0 - Success
 *	Non-zero - Failure
 */
अटल पूर्णांक ibmvmc_send_msg(काष्ठा crq_server_adapter *adapter,
			   काष्ठा ibmvmc_buffer *buffer,
			   काष्ठा ibmvmc_hmc *hmc, पूर्णांक msg_len)
अणु
	काष्ठा ibmvmc_crq_msg crq_msg;
	__be64 *crq_as_u64 = (__be64 *)&crq_msg;
	पूर्णांक rc = 0;

	dev_dbg(adapter->dev, "CRQ send: rdma to HV\n");
	rc = h_copy_rdma(msg_len,
			 adapter->liobn,
			 buffer->dma_addr_local,
			 adapter->riobn,
			 buffer->dma_addr_remote);
	अगर (rc) अणु
		dev_err(adapter->dev, "Error in send_msg, h_copy_rdma rc 0x%x\n",
			rc);
		वापस rc;
	पूर्ण

	crq_msg.valid = 0x80;
	crq_msg.type = VMC_MSG_SIGNAL;
	crq_msg.status = 0;
	crq_msg.var1.rsvd = 0;
	crq_msg.hmc_session = hmc->session;
	crq_msg.hmc_index = hmc->index;
	crq_msg.var2.buffer_id = cpu_to_be16(buffer->id);
	crq_msg.var3.msg_len = cpu_to_be32(msg_len);
	dev_dbg(adapter->dev, "CRQ send: msg to HV 0x%llx 0x%llx\n",
		be64_to_cpu(crq_as_u64[0]), be64_to_cpu(crq_as_u64[1]));

	buffer->owner = VMC_BUF_OWNER_HV;
	ibmvmc_send_crq(adapter, be64_to_cpu(crq_as_u64[0]),
			be64_to_cpu(crq_as_u64[1]));

	वापस rc;
पूर्ण

/**
 * ibmvmc_खोलो - Open Session
 *
 * @inode:	inode काष्ठा
 * @file:	file काष्ठा
 *
 * Return:
 *	0 - Success
 *	Non-zero - Failure
 */
अटल पूर्णांक ibmvmc_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा ibmvmc_file_session *session;

	pr_debug("%s: inode = 0x%lx, file = 0x%lx, state = 0x%x\n", __func__,
		 (अचिन्हित दीर्घ)inode, (अचिन्हित दीर्घ)file,
		 ibmvmc.state);

	session = kzalloc(माप(*session), GFP_KERNEL);
	अगर (!session)
		वापस -ENOMEM;

	session->file = file;
	file->निजी_data = session;

	वापस 0;
पूर्ण

/**
 * ibmvmc_बंद - Close Session
 *
 * @inode:	inode काष्ठा
 * @file:	file काष्ठा
 *
 * Return:
 *	0 - Success
 *	Non-zero - Failure
 */
अटल पूर्णांक ibmvmc_बंद(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा ibmvmc_file_session *session;
	काष्ठा ibmvmc_hmc *hmc;
	पूर्णांक rc = 0;
	अचिन्हित दीर्घ flags;

	pr_debug("%s: file = 0x%lx, state = 0x%x\n", __func__,
		 (अचिन्हित दीर्घ)file, ibmvmc.state);

	session = file->निजी_data;
	अगर (!session)
		वापस -EIO;

	hmc = session->hmc;
	अगर (hmc) अणु
		अगर (!hmc->adapter)
			वापस -EIO;

		अगर (ibmvmc.state == ibmvmc_state_failed) अणु
			dev_warn(hmc->adapter->dev, "close: state_failed\n");
			वापस -EIO;
		पूर्ण

		spin_lock_irqsave(&hmc->lock, flags);
		अगर (hmc->state >= ibmhmc_state_खोलोing) अणु
			rc = ibmvmc_send_बंद(hmc);
			अगर (rc)
				dev_warn(hmc->adapter->dev, "close: send_close failed.\n");
		पूर्ण
		spin_unlock_irqrestore(&hmc->lock, flags);
	पूर्ण

	kमुक्त_sensitive(session);

	वापस rc;
पूर्ण

/**
 * ibmvmc_पढ़ो - Read
 *
 * @file:	file काष्ठा
 * @buf:	Character buffer
 * @nbytes:	Size in bytes
 * @ppos:	Offset
 *
 * Return:
 *	0 - Success
 *	Non-zero - Failure
 */
अटल sमाप_प्रकार ibmvmc_पढ़ो(काष्ठा file *file, अक्षर *buf, माप_प्रकार nbytes,
			   loff_t *ppos)
अणु
	काष्ठा ibmvmc_file_session *session;
	काष्ठा ibmvmc_hmc *hmc;
	काष्ठा crq_server_adapter *adapter;
	काष्ठा ibmvmc_buffer *buffer;
	sमाप_प्रकार n;
	sमाप_प्रकार retval = 0;
	अचिन्हित दीर्घ flags;
	DEFINE_WAIT(रुको);

	pr_debug("ibmvmc: read: file = 0x%lx, buf = 0x%lx, nbytes = 0x%lx\n",
		 (अचिन्हित दीर्घ)file, (अचिन्हित दीर्घ)buf,
		 (अचिन्हित दीर्घ)nbytes);

	अगर (nbytes == 0)
		वापस 0;

	अगर (nbytes > ibmvmc.max_mtu) अणु
		pr_warn("ibmvmc: read: nbytes invalid 0x%x\n",
			(अचिन्हित पूर्णांक)nbytes);
		वापस -EINVAL;
	पूर्ण

	session = file->निजी_data;
	अगर (!session) अणु
		pr_warn("ibmvmc: read: no session\n");
		वापस -EIO;
	पूर्ण

	hmc = session->hmc;
	अगर (!hmc) अणु
		pr_warn("ibmvmc: read: no hmc\n");
		वापस -EIO;
	पूर्ण

	adapter = hmc->adapter;
	अगर (!adapter) अणु
		pr_warn("ibmvmc: read: no adapter\n");
		वापस -EIO;
	पूर्ण

	करो अणु
		prepare_to_रुको(&ibmvmc_पढ़ो_रुको, &रुको, TASK_INTERRUPTIBLE);

		spin_lock_irqsave(&hmc->lock, flags);
		अगर (hmc->queue_tail != hmc->queue_head)
			/* Data is available */
			अवरोध;

		spin_unlock_irqrestore(&hmc->lock, flags);

		अगर (!session->valid) अणु
			retval = -EBADFD;
			जाओ out;
		पूर्ण
		अगर (file->f_flags & O_NONBLOCK) अणु
			retval = -EAGAIN;
			जाओ out;
		पूर्ण

		schedule();

		अगर (संकेत_pending(current)) अणु
			retval = -ERESTARTSYS;
			जाओ out;
		पूर्ण
	पूर्ण जबतक (1);

	buffer = &(hmc->buffer[hmc->queue_outbound_msgs[hmc->queue_tail]]);
	hmc->queue_tail++;
	अगर (hmc->queue_tail == ibmvmc_max_buf_pool_size)
		hmc->queue_tail = 0;
	spin_unlock_irqrestore(&hmc->lock, flags);

	nbytes = min_t(माप_प्रकार, nbytes, buffer->msg_len);
	n = copy_to_user((व्योम *)buf, buffer->real_addr_local, nbytes);
	dev_dbg(adapter->dev, "read: copy to user nbytes = 0x%lx.\n", nbytes);
	ibmvmc_मुक्त_hmc_buffer(hmc, buffer);
	retval = nbytes;

	अगर (n) अणु
		dev_warn(adapter->dev, "read: copy to user failed.\n");
		retval = -EFAULT;
	पूर्ण

 out:
	finish_रुको(&ibmvmc_पढ़ो_रुको, &रुको);
	dev_dbg(adapter->dev, "read: out %ld\n", retval);
	वापस retval;
पूर्ण

/**
 * ibmvmc_poll - Poll
 *
 * @file:	file काष्ठा
 * @रुको:	Poll Table
 *
 * Return:
 *	poll.h वापस values
 */
अटल अचिन्हित पूर्णांक ibmvmc_poll(काष्ठा file *file, poll_table *रुको)
अणु
	काष्ठा ibmvmc_file_session *session;
	काष्ठा ibmvmc_hmc *hmc;
	अचिन्हित पूर्णांक mask = 0;

	session = file->निजी_data;
	अगर (!session)
		वापस 0;

	hmc = session->hmc;
	अगर (!hmc)
		वापस 0;

	poll_रुको(file, &ibmvmc_पढ़ो_रुको, रुको);

	अगर (hmc->queue_head != hmc->queue_tail)
		mask |= POLLIN | POLLRDNORM;

	वापस mask;
पूर्ण

/**
 * ibmvmc_ग_लिखो - Write
 *
 * @file:	file काष्ठा
 * @buffer:	Character buffer
 * @count:	Count field
 * @ppos:	Offset
 *
 * Return:
 *	0 - Success
 *	Non-zero - Failure
 */
अटल sमाप_प्रकार ibmvmc_ग_लिखो(काष्ठा file *file, स्थिर अक्षर *buffer,
			    माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ibmvmc_buffer *vmc_buffer;
	काष्ठा ibmvmc_file_session *session;
	काष्ठा crq_server_adapter *adapter;
	काष्ठा ibmvmc_hmc *hmc;
	अचिन्हित अक्षर *buf;
	अचिन्हित दीर्घ flags;
	माप_प्रकार bytes;
	स्थिर अक्षर *p = buffer;
	माप_प्रकार c = count;
	पूर्णांक ret = 0;

	session = file->निजी_data;
	अगर (!session)
		वापस -EIO;

	hmc = session->hmc;
	अगर (!hmc)
		वापस -EIO;

	spin_lock_irqsave(&hmc->lock, flags);
	अगर (hmc->state == ibmhmc_state_मुक्त) अणु
		/* HMC connection is not valid (possibly was reset under us). */
		ret = -EIO;
		जाओ out;
	पूर्ण

	adapter = hmc->adapter;
	अगर (!adapter) अणु
		ret = -EIO;
		जाओ out;
	पूर्ण

	अगर (count > ibmvmc.max_mtu) अणु
		dev_warn(adapter->dev, "invalid buffer size 0x%lx\n",
			 (अचिन्हित दीर्घ)count);
		ret = -EIO;
		जाओ out;
	पूर्ण

	/* Waiting क्रम the खोलो resp message to the ioctl(1) - retry */
	अगर (hmc->state == ibmhmc_state_खोलोing) अणु
		ret = -EBUSY;
		जाओ out;
	पूर्ण

	/* Make sure the ioctl() was called & the खोलो msg sent, and that
	 * the HMC connection has not failed.
	 */
	अगर (hmc->state != ibmhmc_state_पढ़ोy) अणु
		ret = -EIO;
		जाओ out;
	पूर्ण

	vmc_buffer = ibmvmc_get_valid_hmc_buffer(hmc->index);
	अगर (!vmc_buffer) अणु
		/* No buffer available क्रम the msg send, or we have not yet
		 * completed the खोलो/खोलो_resp sequence.  Retry until this is
		 * complete.
		 */
		ret = -EBUSY;
		जाओ out;
	पूर्ण
	अगर (!vmc_buffer->real_addr_local) अणु
		dev_err(adapter->dev, "no buffer storage assigned\n");
		ret = -EIO;
		जाओ out;
	पूर्ण
	buf = vmc_buffer->real_addr_local;

	जबतक (c > 0) अणु
		bytes = min_t(माप_प्रकार, c, vmc_buffer->size);

		bytes -= copy_from_user(buf, p, bytes);
		अगर (!bytes) अणु
			ret = -EFAULT;
			जाओ out;
		पूर्ण
		c -= bytes;
		p += bytes;
	पूर्ण
	अगर (p == buffer)
		जाओ out;

	file->f_path.dentry->d_inode->i_mसमय = current_समय(file_inode(file));
	mark_inode_dirty(file->f_path.dentry->d_inode);

	dev_dbg(adapter->dev, "write: file = 0x%lx, count = 0x%lx\n",
		(अचिन्हित दीर्घ)file, (अचिन्हित दीर्घ)count);

	ibmvmc_send_msg(adapter, vmc_buffer, hmc, count);
	ret = p - buffer;
 out:
	spin_unlock_irqrestore(&hmc->lock, flags);
	वापस (sमाप_प्रकार)(ret);
पूर्ण

/**
 * ibmvmc_setup_hmc - Setup the HMC
 *
 * @session:	ibmvmc_file_session काष्ठा
 *
 * Return:
 *	0 - Success
 *	Non-zero - Failure
 */
अटल दीर्घ ibmvmc_setup_hmc(काष्ठा ibmvmc_file_session *session)
अणु
	काष्ठा ibmvmc_hmc *hmc;
	अचिन्हित पूर्णांक valid, मुक्त, index;

	अगर (ibmvmc.state == ibmvmc_state_failed) अणु
		pr_warn("ibmvmc: Reserve HMC: state_failed\n");
		वापस -EIO;
	पूर्ण

	अगर (ibmvmc.state < ibmvmc_state_पढ़ोy) अणु
		pr_warn("ibmvmc: Reserve HMC: not state_ready\n");
		वापस -EAGAIN;
	पूर्ण

	/* Device is busy until capabilities have been exchanged and we
	 * have a generic buffer क्रम each possible HMC connection.
	 */
	क्रम (index = 0; index <= ibmvmc.max_hmc_index; index++) अणु
		valid = 0;
		ibmvmc_count_hmc_buffers(index, &valid, &मुक्त);
		अगर (valid == 0) अणु
			pr_warn("ibmvmc: buffers not ready for index %d\n",
				index);
			वापस -ENOBUFS;
		पूर्ण
	पूर्ण

	/* Get an hmc object, and transition to ibmhmc_state_initial */
	hmc = ibmvmc_get_मुक्त_hmc();
	अगर (!hmc) अणु
		pr_warn("%s: free hmc not found\n", __func__);
		वापस -EBUSY;
	पूर्ण

	hmc->session = hmc->session + 1;
	अगर (hmc->session == 0xff)
		hmc->session = 1;

	session->hmc = hmc;
	hmc->adapter = &ibmvmc_adapter;
	hmc->file_session = session;
	session->valid = 1;

	वापस 0;
पूर्ण

/**
 * ibmvmc_ioctl_sethmcid - IOCTL Set HMC ID
 *
 * @session:	ibmvmc_file_session काष्ठा
 * @new_hmc_id:	HMC id field
 *
 * IOCTL command to setup the hmc id
 *
 * Return:
 *	0 - Success
 *	Non-zero - Failure
 */
अटल दीर्घ ibmvmc_ioctl_sethmcid(काष्ठा ibmvmc_file_session *session,
				  अचिन्हित अक्षर __user *new_hmc_id)
अणु
	काष्ठा ibmvmc_hmc *hmc;
	काष्ठा ibmvmc_buffer *buffer;
	माप_प्रकार bytes;
	अक्षर prपूर्णांक_buffer[HMC_ID_LEN + 1];
	अचिन्हित दीर्घ flags;
	दीर्घ rc = 0;

	/* Reserve HMC session */
	hmc = session->hmc;
	अगर (!hmc) अणु
		rc = ibmvmc_setup_hmc(session);
		अगर (rc)
			वापस rc;

		hmc = session->hmc;
		अगर (!hmc) अणु
			pr_err("ibmvmc: setup_hmc success but no hmc\n");
			वापस -EIO;
		पूर्ण
	पूर्ण

	अगर (hmc->state != ibmhmc_state_initial) अणु
		pr_warn("ibmvmc: sethmcid: invalid state to send open 0x%x\n",
			hmc->state);
		वापस -EIO;
	पूर्ण

	bytes = copy_from_user(hmc->hmc_id, new_hmc_id, HMC_ID_LEN);
	अगर (bytes)
		वापस -EFAULT;

	/* Send Open Session command */
	spin_lock_irqsave(&hmc->lock, flags);
	buffer = ibmvmc_get_valid_hmc_buffer(hmc->index);
	spin_unlock_irqrestore(&hmc->lock, flags);

	अगर (!buffer || !buffer->real_addr_local) अणु
		pr_warn("ibmvmc: sethmcid: no buffer available\n");
		वापस -EIO;
	पूर्ण

	/* Make sure buffer is शून्य terminated beक्रमe trying to prपूर्णांक it */
	स_रखो(prपूर्णांक_buffer, 0, HMC_ID_LEN + 1);
	म_नकलन(prपूर्णांक_buffer, hmc->hmc_id, HMC_ID_LEN);
	pr_info("ibmvmc: sethmcid: Set HMC ID: \"%s\"\n", prपूर्णांक_buffer);

	स_नकल(buffer->real_addr_local, hmc->hmc_id, HMC_ID_LEN);
	/* RDMA over ID, send खोलो msg, change state to ibmhmc_state_खोलोing */
	rc = ibmvmc_send_खोलो(buffer, hmc);

	वापस rc;
पूर्ण

/**
 * ibmvmc_ioctl_query - IOCTL Query
 *
 * @session:	ibmvmc_file_session काष्ठा
 * @ret_काष्ठा:	ibmvmc_query_काष्ठा
 *
 * Return:
 *	0 - Success
 *	Non-zero - Failure
 */
अटल दीर्घ ibmvmc_ioctl_query(काष्ठा ibmvmc_file_session *session,
			       काष्ठा ibmvmc_query_काष्ठा __user *ret_काष्ठा)
अणु
	काष्ठा ibmvmc_query_काष्ठा query_काष्ठा;
	माप_प्रकार bytes;

	स_रखो(&query_काष्ठा, 0, माप(query_काष्ठा));
	query_काष्ठा.have_vmc = (ibmvmc.state > ibmvmc_state_initial);
	query_काष्ठा.state = ibmvmc.state;
	query_काष्ठा.vmc_drc_index = ibmvmc.vmc_drc_index;

	bytes = copy_to_user(ret_काष्ठा, &query_काष्ठा,
			     माप(query_काष्ठा));
	अगर (bytes)
		वापस -EFAULT;

	वापस 0;
पूर्ण

/**
 * ibmvmc_ioctl_requestvmc - IOCTL Request VMC
 *
 * @session:	ibmvmc_file_session काष्ठा
 * @ret_vmc_index:	VMC Index
 *
 * Return:
 *	0 - Success
 *	Non-zero - Failure
 */
अटल दीर्घ ibmvmc_ioctl_requestvmc(काष्ठा ibmvmc_file_session *session,
				    u32 __user *ret_vmc_index)
अणु
	/* TODO: (adreznec) Add locking to control multiple process access */
	माप_प्रकार bytes;
	दीर्घ rc;
	u32 vmc_drc_index;

	/* Call to request the VMC device from phyp*/
	rc = h_request_vmc(&vmc_drc_index);
	pr_debug("ibmvmc: requestvmc: H_REQUEST_VMC rc = 0x%lx\n", rc);

	अगर (rc == H_SUCCESS) अणु
		rc = 0;
	पूर्ण अन्यथा अगर (rc == H_FUNCTION) अणु
		pr_err("ibmvmc: requestvmc: h_request_vmc not supported\n");
		वापस -EPERM;
	पूर्ण अन्यथा अगर (rc == H_AUTHORITY) अणु
		pr_err("ibmvmc: requestvmc: hypervisor denied vmc request\n");
		वापस -EPERM;
	पूर्ण अन्यथा अगर (rc == H_HARDWARE) अणु
		pr_err("ibmvmc: requestvmc: hypervisor hardware fault\n");
		वापस -EIO;
	पूर्ण अन्यथा अगर (rc == H_RESOURCE) अणु
		pr_err("ibmvmc: requestvmc: vmc resource unavailable\n");
		वापस -ENODEV;
	पूर्ण अन्यथा अगर (rc == H_NOT_AVAILABLE) अणु
		pr_err("ibmvmc: requestvmc: system cannot be vmc managed\n");
		वापस -EPERM;
	पूर्ण अन्यथा अगर (rc == H_PARAMETER) अणु
		pr_err("ibmvmc: requestvmc: invalid parameter\n");
		वापस -EINVAL;
	पूर्ण

	/* Success, set the vmc index in global काष्ठा */
	ibmvmc.vmc_drc_index = vmc_drc_index;

	bytes = copy_to_user(ret_vmc_index, &vmc_drc_index,
			     माप(*ret_vmc_index));
	अगर (bytes) अणु
		pr_warn("ibmvmc: requestvmc: copy to user failed.\n");
		वापस -EFAULT;
	पूर्ण
	वापस rc;
पूर्ण

/**
 * ibmvmc_ioctl - IOCTL
 *
 * @file:	file inक्रमmation
 * @cmd:	cmd field
 * @arg:	Argument field
 *
 * Return:
 *	0 - Success
 *	Non-zero - Failure
 */
अटल दीर्घ ibmvmc_ioctl(काष्ठा file *file,
			 अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा ibmvmc_file_session *session = file->निजी_data;

	pr_debug("ibmvmc: ioctl file=0x%lx, cmd=0x%x, arg=0x%lx, ses=0x%lx\n",
		 (अचिन्हित दीर्घ)file, cmd, arg,
		 (अचिन्हित दीर्घ)session);

	अगर (!session) अणु
		pr_warn("ibmvmc: ioctl: no session\n");
		वापस -EIO;
	पूर्ण

	चयन (cmd) अणु
	हाल VMC_IOCTL_SETHMCID:
		वापस ibmvmc_ioctl_sethmcid(session,
			(अचिन्हित अक्षर __user *)arg);
	हाल VMC_IOCTL_QUERY:
		वापस ibmvmc_ioctl_query(session,
			(काष्ठा ibmvmc_query_काष्ठा __user *)arg);
	हाल VMC_IOCTL_REQUESTVMC:
		वापस ibmvmc_ioctl_requestvmc(session,
			(अचिन्हित पूर्णांक __user *)arg);
	शेष:
		pr_warn("ibmvmc: unknown ioctl 0x%x\n", cmd);
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा file_operations ibmvmc_fops = अणु
	.owner		= THIS_MODULE,
	.पढ़ो		= ibmvmc_पढ़ो,
	.ग_लिखो		= ibmvmc_ग_लिखो,
	.poll		= ibmvmc_poll,
	.unlocked_ioctl	= ibmvmc_ioctl,
	.खोलो           = ibmvmc_खोलो,
	.release        = ibmvmc_बंद,
पूर्ण;

/**
 * ibmvmc_add_buffer - Add Buffer
 *
 * @adapter: crq_server_adapter काष्ठा
 * @crq:	ibmvmc_crq_msg काष्ठा
 *
 * This message transfers a buffer from hypervisor ownership to management
 * partition ownership. The LIOBA is obtained from the भव TCE table
 * associated with the hypervisor side of the VMC device, and poपूर्णांकs to a
 * buffer of size MTU (as established in the capabilities exchange).
 *
 * Typical flow क्रम ading buffers:
 * 1. A new management application connection is खोलोed by the management
 *	partition.
 * 2. The hypervisor assigns new buffers क्रम the traffic associated with
 *	that connection.
 * 3. The hypervisor sends VMC Add Buffer messages to the management
 *	partition, inक्रमming it of the new buffers.
 * 4. The hypervisor sends an HMC protocol message (to the management
 *	application) notअगरying it of the new buffers. This inक्रमms the
 *	application that it has buffers available क्रम sending HMC
 *	commands.
 *
 * Return:
 *	0 - Success
 *	Non-zero - Failure
 */
अटल पूर्णांक ibmvmc_add_buffer(काष्ठा crq_server_adapter *adapter,
			     काष्ठा ibmvmc_crq_msg *crq)
अणु
	काष्ठा ibmvmc_buffer *buffer;
	u8 hmc_index;
	u8 hmc_session;
	u16 buffer_id;
	अचिन्हित दीर्घ flags;
	पूर्णांक rc = 0;

	अगर (!crq)
		वापस -1;

	hmc_session = crq->hmc_session;
	hmc_index = crq->hmc_index;
	buffer_id = be16_to_cpu(crq->var2.buffer_id);

	अगर (hmc_index > ibmvmc.max_hmc_index) अणु
		dev_err(adapter->dev, "add_buffer: invalid hmc_index = 0x%x\n",
			hmc_index);
		ibmvmc_send_add_buffer_resp(adapter, VMC_MSG_INVALID_HMC_INDEX,
					    hmc_session, hmc_index, buffer_id);
		वापस -1;
	पूर्ण

	अगर (buffer_id >= ibmvmc.max_buffer_pool_size) अणु
		dev_err(adapter->dev, "add_buffer: invalid buffer_id = 0x%x\n",
			buffer_id);
		ibmvmc_send_add_buffer_resp(adapter, VMC_MSG_INVALID_BUFFER_ID,
					    hmc_session, hmc_index, buffer_id);
		वापस -1;
	पूर्ण

	spin_lock_irqsave(&hmcs[hmc_index].lock, flags);
	buffer = &hmcs[hmc_index].buffer[buffer_id];

	अगर (buffer->real_addr_local || buffer->dma_addr_local) अणु
		dev_warn(adapter->dev, "add_buffer: already allocated id = 0x%lx\n",
			 (अचिन्हित दीर्घ)buffer_id);
		spin_unlock_irqrestore(&hmcs[hmc_index].lock, flags);
		ibmvmc_send_add_buffer_resp(adapter, VMC_MSG_INVALID_BUFFER_ID,
					    hmc_session, hmc_index, buffer_id);
		वापस -1;
	पूर्ण

	buffer->real_addr_local = alloc_dma_buffer(to_vio_dev(adapter->dev),
						   ibmvmc.max_mtu,
						   &buffer->dma_addr_local);

	अगर (!buffer->real_addr_local) अणु
		dev_err(adapter->dev, "add_buffer: alloc_dma_buffer failed.\n");
		spin_unlock_irqrestore(&hmcs[hmc_index].lock, flags);
		ibmvmc_send_add_buffer_resp(adapter, VMC_MSG_INTERFACE_FAILURE,
					    hmc_session, hmc_index, buffer_id);
		वापस -1;
	पूर्ण

	buffer->dma_addr_remote = be32_to_cpu(crq->var3.lioba);
	buffer->size = ibmvmc.max_mtu;
	buffer->owner = crq->var1.owner;
	buffer->मुक्त = 1;
	/* Must ensure valid==1 is observable only after all other fields are */
	dma_wmb();
	buffer->valid = 1;
	buffer->id = buffer_id;

	dev_dbg(adapter->dev, "add_buffer: successfully added a buffer:\n");
	dev_dbg(adapter->dev, "   index: %d, session: %d, buffer: 0x%x, owner: %d\n",
		hmc_index, hmc_session, buffer_id, buffer->owner);
	dev_dbg(adapter->dev, "   local: 0x%x, remote: 0x%x\n",
		(u32)buffer->dma_addr_local,
		(u32)buffer->dma_addr_remote);
	spin_unlock_irqrestore(&hmcs[hmc_index].lock, flags);

	ibmvmc_send_add_buffer_resp(adapter, VMC_MSG_SUCCESS, hmc_session,
				    hmc_index, buffer_id);

	वापस rc;
पूर्ण

/**
 * ibmvmc_rem_buffer - Remove Buffer
 *
 * @adapter: crq_server_adapter काष्ठा
 * @crq:	ibmvmc_crq_msg काष्ठा
 *
 * This message requests an HMC buffer to be transferred from management
 * partition ownership to hypervisor ownership. The management partition may
 * not be able to satisfy the request at a particular poपूर्णांक in समय अगर all its
 * buffers are in use. The management partition requires a depth of at least
 * one inbound buffer to allow management application commands to flow to the
 * hypervisor. It is, thereक्रमe, an पूर्णांकerface error क्रम the hypervisor to
 * attempt to हटाओ the management partition's last buffer.
 *
 * The hypervisor is expected to manage buffer usage with the management
 * application directly and inक्रमm the management partition when buffers may be
 * हटाओd. The typical flow क्रम removing buffers:
 *
 * 1. The management application no दीर्घer needs a communication path to a
 *	particular hypervisor function. That function is बंदd.
 * 2. The hypervisor and the management application quiesce all traffic to that
 *	function. The hypervisor requests a reduction in buffer pool size.
 * 3. The management application acknowledges the reduction in buffer pool size.
 * 4. The hypervisor sends a Remove Buffer message to the management partition,
 *	inक्रमming it of the reduction in buffers.
 * 5. The management partition verअगरies it can हटाओ the buffer. This is
 *	possible अगर buffers have been quiesced.
 *
 * Return:
 *	0 - Success
 *	Non-zero - Failure
 */
/*
 * The hypervisor requested that we pick an unused buffer, and वापस it.
 * Beक्रमe sending the buffer back, we मुक्त any storage associated with the
 * buffer.
 */
अटल पूर्णांक ibmvmc_rem_buffer(काष्ठा crq_server_adapter *adapter,
			     काष्ठा ibmvmc_crq_msg *crq)
अणु
	काष्ठा ibmvmc_buffer *buffer;
	u8 hmc_index;
	u8 hmc_session;
	u16 buffer_id = 0;
	अचिन्हित दीर्घ flags;
	पूर्णांक rc = 0;

	अगर (!crq)
		वापस -1;

	hmc_session = crq->hmc_session;
	hmc_index = crq->hmc_index;

	अगर (hmc_index > ibmvmc.max_hmc_index) अणु
		dev_warn(adapter->dev, "rem_buffer: invalid hmc_index = 0x%x\n",
			 hmc_index);
		ibmvmc_send_rem_buffer_resp(adapter, VMC_MSG_INVALID_HMC_INDEX,
					    hmc_session, hmc_index, buffer_id);
		वापस -1;
	पूर्ण

	spin_lock_irqsave(&hmcs[hmc_index].lock, flags);
	buffer = ibmvmc_get_मुक्त_hmc_buffer(adapter, hmc_index);
	अगर (!buffer) अणु
		dev_info(adapter->dev, "rem_buffer: no buffer to remove\n");
		spin_unlock_irqrestore(&hmcs[hmc_index].lock, flags);
		ibmvmc_send_rem_buffer_resp(adapter, VMC_MSG_NO_BUFFER,
					    hmc_session, hmc_index,
					    VMC_INVALID_BUFFER_ID);
		वापस -1;
	पूर्ण

	buffer_id = buffer->id;

	अगर (buffer->valid)
		मुक्त_dma_buffer(to_vio_dev(adapter->dev),
				ibmvmc.max_mtu,
				buffer->real_addr_local,
				buffer->dma_addr_local);

	स_रखो(buffer, 0, माप(काष्ठा ibmvmc_buffer));
	spin_unlock_irqrestore(&hmcs[hmc_index].lock, flags);

	dev_dbg(adapter->dev, "rem_buffer: removed buffer 0x%x.\n", buffer_id);
	ibmvmc_send_rem_buffer_resp(adapter, VMC_MSG_SUCCESS, hmc_session,
				    hmc_index, buffer_id);

	वापस rc;
पूर्ण

अटल पूर्णांक ibmvmc_recv_msg(काष्ठा crq_server_adapter *adapter,
			   काष्ठा ibmvmc_crq_msg *crq)
अणु
	काष्ठा ibmvmc_buffer *buffer;
	काष्ठा ibmvmc_hmc *hmc;
	अचिन्हित दीर्घ msg_len;
	u8 hmc_index;
	u8 hmc_session;
	u16 buffer_id;
	अचिन्हित दीर्घ flags;
	पूर्णांक rc = 0;

	अगर (!crq)
		वापस -1;

	/* Hypervisor ग_लिखोs CRQs directly पूर्णांकo our memory in big endian */
	dev_dbg(adapter->dev, "Recv_msg: msg from HV 0x%016llx 0x%016llx\n",
		be64_to_cpu(*((अचिन्हित दीर्घ *)crq)),
		be64_to_cpu(*(((अचिन्हित दीर्घ *)crq) + 1)));

	hmc_session = crq->hmc_session;
	hmc_index = crq->hmc_index;
	buffer_id = be16_to_cpu(crq->var2.buffer_id);
	msg_len = be32_to_cpu(crq->var3.msg_len);

	अगर (hmc_index > ibmvmc.max_hmc_index) अणु
		dev_err(adapter->dev, "Recv_msg: invalid hmc_index = 0x%x\n",
			hmc_index);
		ibmvmc_send_add_buffer_resp(adapter, VMC_MSG_INVALID_HMC_INDEX,
					    hmc_session, hmc_index, buffer_id);
		वापस -1;
	पूर्ण

	अगर (buffer_id >= ibmvmc.max_buffer_pool_size) अणु
		dev_err(adapter->dev, "Recv_msg: invalid buffer_id = 0x%x\n",
			buffer_id);
		ibmvmc_send_add_buffer_resp(adapter, VMC_MSG_INVALID_BUFFER_ID,
					    hmc_session, hmc_index, buffer_id);
		वापस -1;
	पूर्ण

	hmc = &hmcs[hmc_index];
	spin_lock_irqsave(&hmc->lock, flags);

	अगर (hmc->state == ibmhmc_state_मुक्त) अणु
		dev_err(adapter->dev, "Recv_msg: invalid hmc state = 0x%x\n",
			hmc->state);
		/* HMC connection is not valid (possibly was reset under us). */
		spin_unlock_irqrestore(&hmc->lock, flags);
		वापस -1;
	पूर्ण

	buffer = &hmc->buffer[buffer_id];

	अगर (buffer->valid == 0 || buffer->owner == VMC_BUF_OWNER_ALPHA) अणु
		dev_err(adapter->dev, "Recv_msg: not valid, or not HV.  0x%x 0x%x\n",
			buffer->valid, buffer->owner);
		spin_unlock_irqrestore(&hmc->lock, flags);
		वापस -1;
	पूर्ण

	/* RDMA the data पूर्णांकo the partition. */
	rc = h_copy_rdma(msg_len,
			 adapter->riobn,
			 buffer->dma_addr_remote,
			 adapter->liobn,
			 buffer->dma_addr_local);

	dev_dbg(adapter->dev, "Recv_msg: msg_len = 0x%x, buffer_id = 0x%x, queue_head = 0x%x, hmc_idx = 0x%x\n",
		(अचिन्हित पूर्णांक)msg_len, (अचिन्हित पूर्णांक)buffer_id,
		(अचिन्हित पूर्णांक)hmc->queue_head, (अचिन्हित पूर्णांक)hmc_index);
	buffer->msg_len = msg_len;
	buffer->मुक्त = 0;
	buffer->owner = VMC_BUF_OWNER_ALPHA;

	अगर (rc) अणु
		dev_err(adapter->dev, "Failure in recv_msg: h_copy_rdma = 0x%x\n",
			rc);
		spin_unlock_irqrestore(&hmc->lock, flags);
		वापस -1;
	पूर्ण

	/* Must be locked because पढ़ो operates on the same data */
	hmc->queue_outbound_msgs[hmc->queue_head] = buffer_id;
	hmc->queue_head++;
	अगर (hmc->queue_head == ibmvmc_max_buf_pool_size)
		hmc->queue_head = 0;

	अगर (hmc->queue_head == hmc->queue_tail)
		dev_err(adapter->dev, "outbound buffer queue wrapped.\n");

	spin_unlock_irqrestore(&hmc->lock, flags);

	wake_up_पूर्णांकerruptible(&ibmvmc_पढ़ो_रुको);

	वापस 0;
पूर्ण

/**
 * ibmvmc_process_capabilities - Process Capabilities
 *
 * @adapter:	crq_server_adapter काष्ठा
 * @crqp:	ibmvmc_crq_msg काष्ठा
 *
 */
अटल व्योम ibmvmc_process_capabilities(काष्ठा crq_server_adapter *adapter,
					काष्ठा ibmvmc_crq_msg *crqp)
अणु
	काष्ठा ibmvmc_admin_crq_msg *crq = (काष्ठा ibmvmc_admin_crq_msg *)crqp;

	अगर ((be16_to_cpu(crq->version) >> 8) !=
			(IBMVMC_PROTOCOL_VERSION >> 8)) अणु
		dev_err(adapter->dev, "init failed, incompatible versions 0x%x 0x%x\n",
			be16_to_cpu(crq->version),
			IBMVMC_PROTOCOL_VERSION);
		ibmvmc.state = ibmvmc_state_failed;
		वापस;
	पूर्ण

	ibmvmc.max_mtu = min_t(u32, ibmvmc_max_mtu, be32_to_cpu(crq->max_mtu));
	ibmvmc.max_buffer_pool_size = min_t(u16, ibmvmc_max_buf_pool_size,
					    be16_to_cpu(crq->pool_size));
	ibmvmc.max_hmc_index = min_t(u8, ibmvmc_max_hmcs, crq->max_hmc) - 1;
	ibmvmc.state = ibmvmc_state_पढ़ोy;

	dev_info(adapter->dev, "Capabilities: mtu=0x%x, pool_size=0x%x, max_hmc=0x%x\n",
		 ibmvmc.max_mtu, ibmvmc.max_buffer_pool_size,
		 ibmvmc.max_hmc_index);
पूर्ण

/**
 * ibmvmc_validate_hmc_session - Validate HMC Session
 *
 * @adapter:	crq_server_adapter काष्ठा
 * @crq:	ibmvmc_crq_msg काष्ठा
 *
 * Return:
 *	0 - Success
 *	Non-zero - Failure
 */
अटल पूर्णांक ibmvmc_validate_hmc_session(काष्ठा crq_server_adapter *adapter,
				       काष्ठा ibmvmc_crq_msg *crq)
अणु
	अचिन्हित अक्षर hmc_index;

	hmc_index = crq->hmc_index;

	अगर (crq->hmc_session == 0)
		वापस 0;

	अगर (hmc_index > ibmvmc.max_hmc_index)
		वापस -1;

	अगर (hmcs[hmc_index].session != crq->hmc_session) अणु
		dev_warn(adapter->dev, "Drop, bad session: expected 0x%x, recv 0x%x\n",
			 hmcs[hmc_index].session, crq->hmc_session);
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * ibmvmc_reset - Reset
 *
 * @adapter:	crq_server_adapter काष्ठा
 * @xport_event:	export_event field
 *
 * Closes all HMC sessions and conditionally schedules a CRQ reset.
 * @xport_event: If true, the partner बंदd their CRQ; we करोn't need to reset.
 *               If false, we need to schedule a CRQ reset.
 */
अटल व्योम ibmvmc_reset(काष्ठा crq_server_adapter *adapter, bool xport_event)
अणु
	पूर्णांक i;

	अगर (ibmvmc.state != ibmvmc_state_sched_reset) अणु
		dev_info(adapter->dev, "*** Reset to initial state.\n");
		क्रम (i = 0; i < ibmvmc_max_hmcs; i++)
			ibmvmc_वापस_hmc(&hmcs[i], xport_event);

		अगर (xport_event) अणु
			/* CRQ was बंदd by the partner.  We करोn't need to करो
			 * anything except set ourself to the correct state to
			 * handle init msgs.
			 */
			ibmvmc.state = ibmvmc_state_crqinit;
		पूर्ण अन्यथा अणु
			/* The partner did not बंद their CRQ - instead, we're
			 * closing the CRQ on our end. Need to schedule this
			 * क्रम process context, because CRQ reset may require a
			 * sleep.
			 *
			 * Setting ibmvmc.state here immediately prevents
			 * ibmvmc_खोलो from completing until the reset
			 * completes in process context.
			 */
			ibmvmc.state = ibmvmc_state_sched_reset;
			dev_dbg(adapter->dev, "Device reset scheduled");
			wake_up_पूर्णांकerruptible(&adapter->reset_रुको_queue);
		पूर्ण
	पूर्ण
पूर्ण

/**
 * ibmvmc_reset_task - Reset Task
 *
 * @data:	Data field
 *
 * Perक्रमms a CRQ reset of the VMC device in process context.
 * NOTE: This function should not be called directly, use ibmvmc_reset.
 */
अटल पूर्णांक ibmvmc_reset_task(व्योम *data)
अणु
	काष्ठा crq_server_adapter *adapter = data;
	पूर्णांक rc;

	set_user_nice(current, -20);

	जबतक (!kthपढ़ो_should_stop()) अणु
		रुको_event_पूर्णांकerruptible(adapter->reset_रुको_queue,
			(ibmvmc.state == ibmvmc_state_sched_reset) ||
			kthपढ़ो_should_stop());

		अगर (kthपढ़ो_should_stop())
			अवरोध;

		dev_dbg(adapter->dev, "CRQ resetting in process context");
		tasklet_disable(&adapter->work_task);

		rc = ibmvmc_reset_crq_queue(adapter);

		अगर (rc != H_SUCCESS && rc != H_RESOURCE) अणु
			dev_err(adapter->dev, "Error initializing CRQ.  rc = 0x%x\n",
				rc);
			ibmvmc.state = ibmvmc_state_failed;
		पूर्ण अन्यथा अणु
			ibmvmc.state = ibmvmc_state_crqinit;

			अगर (ibmvmc_send_crq(adapter, 0xC001000000000000LL, 0)
			    != 0 && rc != H_RESOURCE)
				dev_warn(adapter->dev, "Failed to send initialize CRQ message\n");
		पूर्ण

		vio_enable_पूर्णांकerrupts(to_vio_dev(adapter->dev));
		tasklet_enable(&adapter->work_task);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * ibmvmc_process_खोलो_resp - Process Open Response
 *
 * @crq: ibmvmc_crq_msg काष्ठा
 * @adapter:    crq_server_adapter काष्ठा
 *
 * This command is sent by the hypervisor in response to the Interface
 * Open message. When this message is received, the indicated buffer is
 * again available क्रम management partition use.
 */
अटल व्योम ibmvmc_process_खोलो_resp(काष्ठा ibmvmc_crq_msg *crq,
				     काष्ठा crq_server_adapter *adapter)
अणु
	अचिन्हित अक्षर hmc_index;
	अचिन्हित लघु buffer_id;

	hmc_index = crq->hmc_index;
	अगर (hmc_index > ibmvmc.max_hmc_index) अणु
		/* Why would PHYP give an index > max negotiated? */
		ibmvmc_reset(adapter, false);
		वापस;
	पूर्ण

	अगर (crq->status) अणु
		dev_warn(adapter->dev, "open_resp: failed - status 0x%x\n",
			 crq->status);
		ibmvmc_वापस_hmc(&hmcs[hmc_index], false);
		वापस;
	पूर्ण

	अगर (hmcs[hmc_index].state == ibmhmc_state_खोलोing) अणु
		buffer_id = be16_to_cpu(crq->var2.buffer_id);
		अगर (buffer_id >= ibmvmc.max_buffer_pool_size) अणु
			dev_err(adapter->dev, "open_resp: invalid buffer_id = 0x%x\n",
				buffer_id);
			hmcs[hmc_index].state = ibmhmc_state_failed;
		पूर्ण अन्यथा अणु
			ibmvmc_मुक्त_hmc_buffer(&hmcs[hmc_index],
					       &hmcs[hmc_index].buffer[buffer_id]);
			hmcs[hmc_index].state = ibmhmc_state_पढ़ोy;
			dev_dbg(adapter->dev, "open_resp: set hmc state = ready\n");
		पूर्ण
	पूर्ण अन्यथा अणु
		dev_warn(adapter->dev, "open_resp: invalid hmc state (0x%x)\n",
			 hmcs[hmc_index].state);
	पूर्ण
पूर्ण

/**
 * ibmvmc_process_बंद_resp - Process Close Response
 *
 * @crq: ibmvmc_crq_msg काष्ठा
 * @adapter:    crq_server_adapter काष्ठा
 *
 * This command is sent by the hypervisor in response to the managemant
 * application Interface Close message.
 *
 * If the बंद fails, simply reset the entire driver as the state of the VMC
 * must be in tough shape.
 */
अटल व्योम ibmvmc_process_बंद_resp(काष्ठा ibmvmc_crq_msg *crq,
				      काष्ठा crq_server_adapter *adapter)
अणु
	अचिन्हित अक्षर hmc_index;

	hmc_index = crq->hmc_index;
	अगर (hmc_index > ibmvmc.max_hmc_index) अणु
		ibmvmc_reset(adapter, false);
		वापस;
	पूर्ण

	अगर (crq->status) अणु
		dev_warn(adapter->dev, "close_resp: failed - status 0x%x\n",
			 crq->status);
		ibmvmc_reset(adapter, false);
		वापस;
	पूर्ण

	ibmvmc_वापस_hmc(&hmcs[hmc_index], false);
पूर्ण

/**
 * ibmvmc_crq_process - Process CRQ
 *
 * @adapter:    crq_server_adapter काष्ठा
 * @crq:	ibmvmc_crq_msg काष्ठा
 *
 * Process the CRQ message based upon the type of message received.
 *
 */
अटल व्योम ibmvmc_crq_process(काष्ठा crq_server_adapter *adapter,
			       काष्ठा ibmvmc_crq_msg *crq)
अणु
	चयन (crq->type) अणु
	हाल VMC_MSG_CAP_RESP:
		dev_dbg(adapter->dev, "CRQ recv: capabilities resp (0x%x)\n",
			crq->type);
		अगर (ibmvmc.state == ibmvmc_state_capabilities)
			ibmvmc_process_capabilities(adapter, crq);
		अन्यथा
			dev_warn(adapter->dev, "caps msg invalid in state 0x%x\n",
				 ibmvmc.state);
		अवरोध;
	हाल VMC_MSG_OPEN_RESP:
		dev_dbg(adapter->dev, "CRQ recv: open resp (0x%x)\n",
			crq->type);
		अगर (ibmvmc_validate_hmc_session(adapter, crq) == 0)
			ibmvmc_process_खोलो_resp(crq, adapter);
		अवरोध;
	हाल VMC_MSG_ADD_BUF:
		dev_dbg(adapter->dev, "CRQ recv: add buf (0x%x)\n",
			crq->type);
		अगर (ibmvmc_validate_hmc_session(adapter, crq) == 0)
			ibmvmc_add_buffer(adapter, crq);
		अवरोध;
	हाल VMC_MSG_REM_BUF:
		dev_dbg(adapter->dev, "CRQ recv: rem buf (0x%x)\n",
			crq->type);
		अगर (ibmvmc_validate_hmc_session(adapter, crq) == 0)
			ibmvmc_rem_buffer(adapter, crq);
		अवरोध;
	हाल VMC_MSG_SIGNAL:
		dev_dbg(adapter->dev, "CRQ recv: signal msg (0x%x)\n",
			crq->type);
		अगर (ibmvmc_validate_hmc_session(adapter, crq) == 0)
			ibmvmc_recv_msg(adapter, crq);
		अवरोध;
	हाल VMC_MSG_CLOSE_RESP:
		dev_dbg(adapter->dev, "CRQ recv: close resp (0x%x)\n",
			crq->type);
		अगर (ibmvmc_validate_hmc_session(adapter, crq) == 0)
			ibmvmc_process_बंद_resp(crq, adapter);
		अवरोध;
	हाल VMC_MSG_CAP:
	हाल VMC_MSG_OPEN:
	हाल VMC_MSG_CLOSE:
	हाल VMC_MSG_ADD_BUF_RESP:
	हाल VMC_MSG_REM_BUF_RESP:
		dev_warn(adapter->dev, "CRQ recv: unexpected msg (0x%x)\n",
			 crq->type);
		अवरोध;
	शेष:
		dev_warn(adapter->dev, "CRQ recv: unknown msg (0x%x)\n",
			 crq->type);
		अवरोध;
	पूर्ण
पूर्ण

/**
 * ibmvmc_handle_crq_init - Handle CRQ Init
 *
 * @crq:	ibmvmc_crq_msg काष्ठा
 * @adapter:	crq_server_adapter काष्ठा
 *
 * Handle the type of crq initialization based on whether
 * it is a message or a response.
 *
 */
अटल व्योम ibmvmc_handle_crq_init(काष्ठा ibmvmc_crq_msg *crq,
				   काष्ठा crq_server_adapter *adapter)
अणु
	चयन (crq->type) अणु
	हाल 0x01:	/* Initialization message */
		dev_dbg(adapter->dev, "CRQ recv: CRQ init msg - state 0x%x\n",
			ibmvmc.state);
		अगर (ibmvmc.state == ibmvmc_state_crqinit) अणु
			/* Send back a response */
			अगर (ibmvmc_send_crq(adapter, 0xC002000000000000,
					    0) == 0)
				ibmvmc_send_capabilities(adapter);
			अन्यथा
				dev_err(adapter->dev, " Unable to send init rsp\n");
		पूर्ण अन्यथा अणु
			dev_err(adapter->dev, "Invalid state 0x%x mtu = 0x%x\n",
				ibmvmc.state, ibmvmc.max_mtu);
		पूर्ण

		अवरोध;
	हाल 0x02:	/* Initialization response */
		dev_dbg(adapter->dev, "CRQ recv: initialization resp msg - state 0x%x\n",
			ibmvmc.state);
		अगर (ibmvmc.state == ibmvmc_state_crqinit)
			ibmvmc_send_capabilities(adapter);
		अवरोध;
	शेष:
		dev_warn(adapter->dev, "Unknown crq message type 0x%lx\n",
			 (अचिन्हित दीर्घ)crq->type);
	पूर्ण
पूर्ण

/**
 * ibmvmc_handle_crq - Handle CRQ
 *
 * @crq:	ibmvmc_crq_msg काष्ठा
 * @adapter:	crq_server_adapter काष्ठा
 *
 * Read the command elements from the command queue and execute the
 * requests based upon the type of crq message.
 *
 */
अटल व्योम ibmvmc_handle_crq(काष्ठा ibmvmc_crq_msg *crq,
			      काष्ठा crq_server_adapter *adapter)
अणु
	चयन (crq->valid) अणु
	हाल 0xC0:		/* initialization */
		ibmvmc_handle_crq_init(crq, adapter);
		अवरोध;
	हाल 0xFF:	/* Hypervisor telling us the connection is बंदd */
		dev_warn(adapter->dev, "CRQ recv: virtual adapter failed - resetting.\n");
		ibmvmc_reset(adapter, true);
		अवरोध;
	हाल 0x80:	/* real payload */
		ibmvmc_crq_process(adapter, crq);
		अवरोध;
	शेष:
		dev_warn(adapter->dev, "CRQ recv: unknown msg 0x%02x.\n",
			 crq->valid);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम ibmvmc_task(अचिन्हित दीर्घ data)
अणु
	काष्ठा crq_server_adapter *adapter =
		(काष्ठा crq_server_adapter *)data;
	काष्ठा vio_dev *vdev = to_vio_dev(adapter->dev);
	काष्ठा ibmvmc_crq_msg *crq;
	पूर्णांक करोne = 0;

	जबतक (!करोne) अणु
		/* Pull all the valid messages off the CRQ */
		जबतक ((crq = crq_queue_next_crq(&adapter->queue)) != शून्य) अणु
			ibmvmc_handle_crq(crq, adapter);
			crq->valid = 0x00;
			/* CRQ reset was requested, stop processing CRQs.
			 * Interrupts will be re-enabled by the reset task.
			 */
			अगर (ibmvmc.state == ibmvmc_state_sched_reset)
				वापस;
		पूर्ण

		vio_enable_पूर्णांकerrupts(vdev);
		crq = crq_queue_next_crq(&adapter->queue);
		अगर (crq) अणु
			vio_disable_पूर्णांकerrupts(vdev);
			ibmvmc_handle_crq(crq, adapter);
			crq->valid = 0x00;
			/* CRQ reset was requested, stop processing CRQs.
			 * Interrupts will be re-enabled by the reset task.
			 */
			अगर (ibmvmc.state == ibmvmc_state_sched_reset)
				वापस;
		पूर्ण अन्यथा अणु
			करोne = 1;
		पूर्ण
	पूर्ण
पूर्ण

/**
 * ibmvmc_init_crq_queue - Init CRQ Queue
 *
 * @adapter:	crq_server_adapter काष्ठा
 *
 * Return:
 *	0 - Success
 *	Non-zero - Failure
 */
अटल पूर्णांक ibmvmc_init_crq_queue(काष्ठा crq_server_adapter *adapter)
अणु
	काष्ठा vio_dev *vdev = to_vio_dev(adapter->dev);
	काष्ठा crq_queue *queue = &adapter->queue;
	पूर्णांक rc = 0;
	पूर्णांक retrc = 0;

	queue->msgs = (काष्ठा ibmvmc_crq_msg *)get_zeroed_page(GFP_KERNEL);

	अगर (!queue->msgs)
		जाओ दो_स्मृति_failed;

	queue->size = PAGE_SIZE / माप(*queue->msgs);

	queue->msg_token = dma_map_single(adapter->dev, queue->msgs,
					  queue->size * माप(*queue->msgs),
					  DMA_BIसूचीECTIONAL);

	अगर (dma_mapping_error(adapter->dev, queue->msg_token))
		जाओ map_failed;

	retrc = plpar_hcall_norets(H_REG_CRQ,
				   vdev->unit_address,
				   queue->msg_token, PAGE_SIZE);
	rc = retrc;

	अगर (rc == H_RESOURCE)
		rc = ibmvmc_reset_crq_queue(adapter);

	अगर (rc == 2) अणु
		dev_warn(adapter->dev, "Partner adapter not ready\n");
		retrc = 0;
	पूर्ण अन्यथा अगर (rc != 0) अणु
		dev_err(adapter->dev, "Error %d opening adapter\n", rc);
		जाओ reg_crq_failed;
	पूर्ण

	queue->cur = 0;
	spin_lock_init(&queue->lock);

	tasklet_init(&adapter->work_task, ibmvmc_task, (अचिन्हित दीर्घ)adapter);

	अगर (request_irq(vdev->irq,
			ibmvmc_handle_event,
			0, "ibmvmc", (व्योम *)adapter) != 0) अणु
		dev_err(adapter->dev, "couldn't register irq 0x%x\n",
			vdev->irq);
		जाओ req_irq_failed;
	पूर्ण

	rc = vio_enable_पूर्णांकerrupts(vdev);
	अगर (rc != 0) अणु
		dev_err(adapter->dev, "Error %d enabling interrupts!!!\n", rc);
		जाओ req_irq_failed;
	पूर्ण

	वापस retrc;

req_irq_failed:
	/* Cannot have any work since we either never got our IRQ रेजिस्टरed,
	 * or never got पूर्णांकerrupts enabled
	 */
	tasklet_समाप्त(&adapter->work_task);
	h_मुक्त_crq(vdev->unit_address);
reg_crq_failed:
	dma_unmap_single(adapter->dev,
			 queue->msg_token,
			 queue->size * माप(*queue->msgs), DMA_BIसूचीECTIONAL);
map_failed:
	मुक्त_page((अचिन्हित दीर्घ)queue->msgs);
दो_स्मृति_failed:
	वापस -ENOMEM;
पूर्ण

/* Fill in the liobn and riobn fields on the adapter */
अटल पूर्णांक पढ़ो_dma_winकरोw(काष्ठा vio_dev *vdev,
			   काष्ठा crq_server_adapter *adapter)
अणु
	स्थिर __be32 *dma_winकरोw;
	स्थिर __be32 *prop;

	/* TODO Using of_parse_dma_winकरोw would be better, but it करोesn't give
	 * a way to पढ़ो multiple winकरोws without alपढ़ोy knowing the size of
	 * a winकरोw or the number of winकरोws
	 */
	dma_winकरोw =
		(स्थिर __be32 *)vio_get_attribute(vdev, "ibm,my-dma-window",
						शून्य);
	अगर (!dma_winकरोw) अणु
		dev_warn(adapter->dev, "Couldn't find ibm,my-dma-window property\n");
		वापस -1;
	पूर्ण

	adapter->liobn = be32_to_cpu(*dma_winकरोw);
	dma_winकरोw++;

	prop = (स्थिर __be32 *)vio_get_attribute(vdev, "ibm,#dma-address-cells",
						शून्य);
	अगर (!prop) अणु
		dev_warn(adapter->dev, "Couldn't find ibm,#dma-address-cells property\n");
		dma_winकरोw++;
	पूर्ण अन्यथा अणु
		dma_winकरोw += be32_to_cpu(*prop);
	पूर्ण

	prop = (स्थिर __be32 *)vio_get_attribute(vdev, "ibm,#dma-size-cells",
						शून्य);
	अगर (!prop) अणु
		dev_warn(adapter->dev, "Couldn't find ibm,#dma-size-cells property\n");
		dma_winकरोw++;
	पूर्ण अन्यथा अणु
		dma_winकरोw += be32_to_cpu(*prop);
	पूर्ण

	/* dma_winकरोw should poपूर्णांक to the second winकरोw now */
	adapter->riobn = be32_to_cpu(*dma_winकरोw);

	वापस 0;
पूर्ण

अटल पूर्णांक ibmvmc_probe(काष्ठा vio_dev *vdev, स्थिर काष्ठा vio_device_id *id)
अणु
	काष्ठा crq_server_adapter *adapter = &ibmvmc_adapter;
	पूर्णांक rc;

	dev_set_drvdata(&vdev->dev, शून्य);
	स_रखो(adapter, 0, माप(*adapter));
	adapter->dev = &vdev->dev;

	dev_info(adapter->dev, "Probe for UA 0x%x\n", vdev->unit_address);

	rc = पढ़ो_dma_winकरोw(vdev, adapter);
	अगर (rc != 0) अणु
		ibmvmc.state = ibmvmc_state_failed;
		वापस -1;
	पूर्ण

	dev_dbg(adapter->dev, "Probe: liobn 0x%x, riobn 0x%x\n",
		adapter->liobn, adapter->riobn);

	init_रुकोqueue_head(&adapter->reset_रुको_queue);
	adapter->reset_task = kthपढ़ो_run(ibmvmc_reset_task, adapter, "ibmvmc");
	अगर (IS_ERR(adapter->reset_task)) अणु
		dev_err(adapter->dev, "Failed to start reset thread\n");
		ibmvmc.state = ibmvmc_state_failed;
		rc = PTR_ERR(adapter->reset_task);
		adapter->reset_task = शून्य;
		वापस rc;
	पूर्ण

	rc = ibmvmc_init_crq_queue(adapter);
	अगर (rc != 0 && rc != H_RESOURCE) अणु
		dev_err(adapter->dev, "Error initializing CRQ.  rc = 0x%x\n",
			rc);
		ibmvmc.state = ibmvmc_state_failed;
		जाओ crq_failed;
	पूर्ण

	ibmvmc.state = ibmvmc_state_crqinit;

	/* Try to send an initialization message.  Note that this is allowed
	 * to fail अगर the other end is not acive.  In that हाल we just रुको
	 * क्रम the other side to initialize.
	 */
	अगर (ibmvmc_send_crq(adapter, 0xC001000000000000LL, 0) != 0 &&
	    rc != H_RESOURCE)
		dev_warn(adapter->dev, "Failed to send initialize CRQ message\n");

	dev_set_drvdata(&vdev->dev, adapter);

	वापस 0;

crq_failed:
	kthपढ़ो_stop(adapter->reset_task);
	adapter->reset_task = शून्य;
	वापस -EPERM;
पूर्ण

अटल व्योम ibmvmc_हटाओ(काष्ठा vio_dev *vdev)
अणु
	काष्ठा crq_server_adapter *adapter = dev_get_drvdata(&vdev->dev);

	dev_info(adapter->dev, "Entering remove for UA 0x%x\n",
		 vdev->unit_address);
	ibmvmc_release_crq_queue(adapter);
पूर्ण

अटल काष्ठा vio_device_id ibmvmc_device_table[] = अणु
	अणु "ibm,vmc", "IBM,vmc" पूर्ण,
	अणु "", "" पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(vio, ibmvmc_device_table);

अटल काष्ठा vio_driver ibmvmc_driver = अणु
	.name        = ibmvmc_driver_name,
	.id_table    = ibmvmc_device_table,
	.probe       = ibmvmc_probe,
	.हटाओ      = ibmvmc_हटाओ,
पूर्ण;

अटल व्योम __init ibmvmc_scrub_module_parms(व्योम)
अणु
	अगर (ibmvmc_max_mtu > MAX_MTU) अणु
		pr_warn("ibmvmc: Max MTU reduced to %d\n", MAX_MTU);
		ibmvmc_max_mtu = MAX_MTU;
	पूर्ण अन्यथा अगर (ibmvmc_max_mtu < MIN_MTU) अणु
		pr_warn("ibmvmc: Max MTU increased to %d\n", MIN_MTU);
		ibmvmc_max_mtu = MIN_MTU;
	पूर्ण

	अगर (ibmvmc_max_buf_pool_size > MAX_BUF_POOL_SIZE) अणु
		pr_warn("ibmvmc: Max buffer pool size reduced to %d\n",
			MAX_BUF_POOL_SIZE);
		ibmvmc_max_buf_pool_size = MAX_BUF_POOL_SIZE;
	पूर्ण अन्यथा अगर (ibmvmc_max_buf_pool_size < MIN_BUF_POOL_SIZE) अणु
		pr_warn("ibmvmc: Max buffer pool size increased to %d\n",
			MIN_BUF_POOL_SIZE);
		ibmvmc_max_buf_pool_size = MIN_BUF_POOL_SIZE;
	पूर्ण

	अगर (ibmvmc_max_hmcs > MAX_HMCS) अणु
		pr_warn("ibmvmc: Max HMCs reduced to %d\n", MAX_HMCS);
		ibmvmc_max_hmcs = MAX_HMCS;
	पूर्ण अन्यथा अगर (ibmvmc_max_hmcs < MIN_HMCS) अणु
		pr_warn("ibmvmc: Max HMCs increased to %d\n", MIN_HMCS);
		ibmvmc_max_hmcs = MIN_HMCS;
	पूर्ण
पूर्ण

अटल काष्ठा miscdevice ibmvmc_miscdev = अणु
	.name = ibmvmc_driver_name,
	.minor = MISC_DYNAMIC_MINOR,
	.fops = &ibmvmc_fops,
पूर्ण;

अटल पूर्णांक __init ibmvmc_module_init(व्योम)
अणु
	पूर्णांक rc, i, j;

	ibmvmc.state = ibmvmc_state_initial;
	pr_info("ibmvmc: version %s\n", IBMVMC_DRIVER_VERSION);

	rc = misc_रेजिस्टर(&ibmvmc_miscdev);
	अगर (rc) अणु
		pr_err("ibmvmc: misc registration failed\n");
		जाओ misc_रेजिस्टर_failed;
	पूर्ण
	pr_info("ibmvmc: node %d:%d\n", MISC_MAJOR,
		ibmvmc_miscdev.minor);

	/* Initialize data काष्ठाures */
	स_रखो(hmcs, 0, माप(काष्ठा ibmvmc_hmc) * MAX_HMCS);
	क्रम (i = 0; i < MAX_HMCS; i++) अणु
		spin_lock_init(&hmcs[i].lock);
		hmcs[i].state = ibmhmc_state_मुक्त;
		क्रम (j = 0; j < MAX_BUF_POOL_SIZE; j++)
			hmcs[i].queue_outbound_msgs[j] = VMC_INVALID_BUFFER_ID;
	पूर्ण

	/* Sanity check module parms */
	ibmvmc_scrub_module_parms();

	/*
	 * Initialize some reasonable values.  Might be negotiated smaller
	 * values during the capabilities exchange.
	 */
	ibmvmc.max_mtu = ibmvmc_max_mtu;
	ibmvmc.max_buffer_pool_size = ibmvmc_max_buf_pool_size;
	ibmvmc.max_hmc_index = ibmvmc_max_hmcs - 1;

	rc = vio_रेजिस्टर_driver(&ibmvmc_driver);

	अगर (rc) अणु
		pr_err("ibmvmc: rc %d from vio_register_driver\n", rc);
		जाओ vio_reg_failed;
	पूर्ण

	वापस 0;

vio_reg_failed:
	misc_deरेजिस्टर(&ibmvmc_miscdev);
misc_रेजिस्टर_failed:
	वापस rc;
पूर्ण

अटल व्योम __निकास ibmvmc_module_निकास(व्योम)
अणु
	pr_info("ibmvmc: module exit\n");
	vio_unरेजिस्टर_driver(&ibmvmc_driver);
	misc_deरेजिस्टर(&ibmvmc_miscdev);
पूर्ण

module_init(ibmvmc_module_init);
module_निकास(ibmvmc_module_निकास);

module_param_named(buf_pool_size, ibmvmc_max_buf_pool_size,
		   पूर्णांक, 0644);
MODULE_PARM_DESC(buf_pool_size, "Buffer pool size");
module_param_named(max_hmcs, ibmvmc_max_hmcs, पूर्णांक, 0644);
MODULE_PARM_DESC(max_hmcs, "Max HMCs");
module_param_named(max_mtu, ibmvmc_max_mtu, पूर्णांक, 0644);
MODULE_PARM_DESC(max_mtu, "Max MTU");

MODULE_AUTHOR("Steven Royer <seroyer@linux.vnet.ibm.com>");
MODULE_DESCRIPTION("IBM VMC");
MODULE_VERSION(IBMVMC_DRIVER_VERSION);
MODULE_LICENSE("GPL v2");
