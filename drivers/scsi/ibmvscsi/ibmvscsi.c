<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* ------------------------------------------------------------
 * ibmvscsi.c
 * (C) Copyright IBM Corporation 1994, 2004
 * Authors: Colin DeVilbiss (devilbis@us.ibm.com)
 *          Santiago Leon (santil@us.ibm.com)
 *          Dave Boutcher (sledकरोg@us.ibm.com)
 *
 * ------------------------------------------------------------
 * Emulation of a SCSI host adapter क्रम Virtual I/O devices
 *
 * This driver supports the SCSI adapter implemented by the IBM
 * Power5 firmware.  That SCSI adapter is not a physical adapter,
 * but allows Linux SCSI peripheral drivers to directly
 * access devices in another logical partition on the physical प्रणाली.
 *
 * The भव adapter(s) are present in the खोलो firmware device
 * tree just like real adapters.
 *
 * One of the capabilities provided on these प्रणालीs is the ability
 * to DMA between partitions.  The architecture states that क्रम VSCSI,
 * the server side is allowed to DMA to and from the client.  The client
 * is never trusted to DMA to or from the server directly.
 *
 * Messages are sent between partitions on a "Command/Response Queue" 
 * (CRQ), which is just a buffer of 16 byte entries in the receiver's 
 * Senders cannot access the buffer directly, but send messages by
 * making a hypervisor call and passing in the 16 bytes.  The hypervisor
 * माला_दो the message in the next 16 byte space in round-robin fashion,
 * turns on the high order bit of the message (the valid bit), and 
 * generates an पूर्णांकerrupt to the receiver (अगर पूर्णांकerrupts are turned on.) 
 * The receiver just turns off the valid bit when they have copied out
 * the message.
 *
 * The VSCSI client builds a SCSI Remote Protocol (SRP) Inक्रमmation Unit
 * (IU) (as defined in the T10 standard available at www.t10.org), माला_लो 
 * a DMA address क्रम the message, and sends it to the server as the
 * payload of a CRQ message.  The server DMAs the SRP IU and processes it,
 * including करोing any additional data transfers.  When it is करोne, it
 * DMAs the SRP response back to the same address as the request came from,
 * and sends a CRQ message back to inक्रमm the client that the request has
 * completed.
 *
 * TODO: This is currently pretty tied to the IBM pSeries hypervisor
 * पूर्णांकerfaces.  It would be really nice to असलtract this above an RDMA
 * layer.
 */

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <linux/of.h>
#समावेश <linux/pm.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <यंत्र/firmware.h>
#समावेश <यंत्र/vपन.स>
#समावेश <scsi/scsi.h>
#समावेश <scsi/scsi_cmnd.h>
#समावेश <scsi/scsi_host.h>
#समावेश <scsi/scsi_device.h>
#समावेश <scsi/scsi_transport_srp.h>
#समावेश "ibmvscsi.h"

/* The values below are somewhat arbitrary शेष values, but 
 * OS/400 will use 3 busses (disks, CDs, tapes, I think.)
 * Note that there are 3 bits of channel value, 6 bits of id, and
 * 5 bits of LUN.
 */
अटल पूर्णांक max_id = 64;
अटल पूर्णांक max_channel = 3;
अटल पूर्णांक init_समयout = 300;
अटल पूर्णांक login_समयout = 60;
अटल पूर्णांक info_समयout = 30;
अटल पूर्णांक पात_समयout = 60;
अटल पूर्णांक reset_समयout = 60;
अटल पूर्णांक max_requests = IBMVSCSI_MAX_REQUESTS_DEFAULT;
अटल पूर्णांक max_events = IBMVSCSI_MAX_REQUESTS_DEFAULT + 2;
अटल पूर्णांक fast_fail = 1;
अटल पूर्णांक client_reserve = 1;
अटल अक्षर partition_name[96] = "UNKNOWN";
अटल अचिन्हित पूर्णांक partition_number = -1;
अटल LIST_HEAD(ibmvscsi_head);
अटल DEFINE_SPINLOCK(ibmvscsi_driver_lock);

अटल काष्ठा scsi_transport_ढाँचा *ibmvscsi_transport_ढाँचा;

#घोषणा IBMVSCSI_VERSION "1.5.9"

MODULE_DESCRIPTION("IBM Virtual SCSI");
MODULE_AUTHOR("Dave Boutcher");
MODULE_LICENSE("GPL");
MODULE_VERSION(IBMVSCSI_VERSION);

module_param_named(max_id, max_id, पूर्णांक, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(max_id, "Largest ID value for each channel [Default=64]");
module_param_named(max_channel, max_channel, पूर्णांक, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(max_channel, "Largest channel value [Default=3]");
module_param_named(init_समयout, init_समयout, पूर्णांक, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(init_समयout, "Initialization timeout in seconds");
module_param_named(max_requests, max_requests, पूर्णांक, S_IRUGO);
MODULE_PARM_DESC(max_requests, "Maximum requests for this adapter");
module_param_named(fast_fail, fast_fail, पूर्णांक, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(fast_fail, "Enable fast fail. [Default=1]");
module_param_named(client_reserve, client_reserve, पूर्णांक, S_IRUGO );
MODULE_PARM_DESC(client_reserve, "Attempt client managed reserve/release");

अटल व्योम ibmvscsi_handle_crq(काष्ठा viosrp_crq *crq,
				काष्ठा ibmvscsi_host_data *hostdata);

/* ------------------------------------------------------------
 * Routines क्रम managing the command/response queue
 */
/**
 * ibmvscsi_handle_event: - Interrupt handler क्रम crq events
 * @irq:	number of irq to handle, not used
 * @dev_instance: ibmvscsi_host_data of host that received पूर्णांकerrupt
 *
 * Disables पूर्णांकerrupts and schedules srp_task
 * Always वापसs IRQ_HANDLED
 */
अटल irqवापस_t ibmvscsi_handle_event(पूर्णांक irq, व्योम *dev_instance)
अणु
	काष्ठा ibmvscsi_host_data *hostdata =
	    (काष्ठा ibmvscsi_host_data *)dev_instance;
	vio_disable_पूर्णांकerrupts(to_vio_dev(hostdata->dev));
	tasklet_schedule(&hostdata->srp_task);
	वापस IRQ_HANDLED;
पूर्ण

/**
 * ibmvscsi_release_crq_queue() - Deallocates data and unरेजिस्टरs CRQ
 * @queue:		crq_queue to initialize and रेजिस्टर
 * @hostdata:		ibmvscsi_host_data of host
 * @max_requests:	maximum requests (unused)
 *
 * Frees irq, deallocates a page क्रम messages, unmaps dma, and unरेजिस्टरs
 * the crq with the hypervisor.
 */
अटल व्योम ibmvscsi_release_crq_queue(काष्ठा crq_queue *queue,
				       काष्ठा ibmvscsi_host_data *hostdata,
				       पूर्णांक max_requests)
अणु
	दीर्घ rc = 0;
	काष्ठा vio_dev *vdev = to_vio_dev(hostdata->dev);
	मुक्त_irq(vdev->irq, (व्योम *)hostdata);
	tasklet_समाप्त(&hostdata->srp_task);
	करो अणु
		अगर (rc)
			msleep(100);
		rc = plpar_hcall_norets(H_FREE_CRQ, vdev->unit_address);
	पूर्ण जबतक ((rc == H_BUSY) || (H_IS_LONG_BUSY(rc)));
	dma_unmap_single(hostdata->dev,
			 queue->msg_token,
			 queue->size * माप(*queue->msgs), DMA_BIसूचीECTIONAL);
	मुक्त_page((अचिन्हित दीर्घ)queue->msgs);
पूर्ण

/**
 * crq_queue_next_crq: - Returns the next entry in message queue
 * @queue:	crq_queue to use
 *
 * Returns poपूर्णांकer to next entry in queue, or शून्य अगर there are no new
 * entried in the CRQ.
 */
अटल काष्ठा viosrp_crq *crq_queue_next_crq(काष्ठा crq_queue *queue)
अणु
	काष्ठा viosrp_crq *crq;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&queue->lock, flags);
	crq = &queue->msgs[queue->cur];
	अगर (crq->valid != VIOSRP_CRQ_FREE) अणु
		अगर (++queue->cur == queue->size)
			queue->cur = 0;

		/* Ensure the पढ़ो of the valid bit occurs beक्रमe पढ़ोing any
		 * other bits of the CRQ entry
		 */
		rmb();
	पूर्ण अन्यथा
		crq = शून्य;
	spin_unlock_irqrestore(&queue->lock, flags);

	वापस crq;
पूर्ण

/**
 * ibmvscsi_send_crq: - Send a CRQ
 * @hostdata:	the adapter
 * @word1:	the first 64 bits of the data
 * @word2:	the second 64 bits of the data
 */
अटल पूर्णांक ibmvscsi_send_crq(काष्ठा ibmvscsi_host_data *hostdata,
			     u64 word1, u64 word2)
अणु
	काष्ठा vio_dev *vdev = to_vio_dev(hostdata->dev);

	/*
	 * Ensure the command buffer is flushed to memory beक्रमe handing it
	 * over to the VIOS to prevent it from fetching any stale data.
	 */
	mb();
	वापस plpar_hcall_norets(H_SEND_CRQ, vdev->unit_address, word1, word2);
पूर्ण

/**
 * ibmvscsi_task: - Process srps asynchronously
 * @data:	ibmvscsi_host_data of host
 */
अटल व्योम ibmvscsi_task(व्योम *data)
अणु
	काष्ठा ibmvscsi_host_data *hostdata = (काष्ठा ibmvscsi_host_data *)data;
	काष्ठा vio_dev *vdev = to_vio_dev(hostdata->dev);
	काष्ठा viosrp_crq *crq;
	पूर्णांक करोne = 0;

	जबतक (!करोne) अणु
		/* Pull all the valid messages off the CRQ */
		जबतक ((crq = crq_queue_next_crq(&hostdata->queue)) != शून्य) अणु
			ibmvscsi_handle_crq(crq, hostdata);
			crq->valid = VIOSRP_CRQ_FREE;
			wmb();
		पूर्ण

		vio_enable_पूर्णांकerrupts(vdev);
		crq = crq_queue_next_crq(&hostdata->queue);
		अगर (crq != शून्य) अणु
			vio_disable_पूर्णांकerrupts(vdev);
			ibmvscsi_handle_crq(crq, hostdata);
			crq->valid = VIOSRP_CRQ_FREE;
			wmb();
		पूर्ण अन्यथा अणु
			करोne = 1;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम gather_partition_info(व्योम)
अणु
	स्थिर अक्षर *ppartition_name;
	स्थिर __be32 *p_number_ptr;

	/* Retrieve inक्रमmation about this partition */
	अगर (!of_root)
		वापस;

	of_node_get(of_root);

	ppartition_name = of_get_property(of_root, "ibm,partition-name", शून्य);
	अगर (ppartition_name)
		strlcpy(partition_name, ppartition_name,
				माप(partition_name));
	p_number_ptr = of_get_property(of_root, "ibm,partition-no", शून्य);
	अगर (p_number_ptr)
		partition_number = of_पढ़ो_number(p_number_ptr, 1);
	of_node_put(of_root);
पूर्ण

अटल व्योम set_adapter_info(काष्ठा ibmvscsi_host_data *hostdata)
अणु
	स_रखो(&hostdata->madapter_info, 0x00,
			माप(hostdata->madapter_info));

	dev_info(hostdata->dev, "SRP_VERSION: %s\n", SRP_VERSION);
	म_नकल(hostdata->madapter_info.srp_version, SRP_VERSION);

	म_नकलन(hostdata->madapter_info.partition_name, partition_name,
			माप(hostdata->madapter_info.partition_name));

	hostdata->madapter_info.partition_number =
					cpu_to_be32(partition_number);

	hostdata->madapter_info.mad_version = cpu_to_be32(SRP_MAD_VERSION_1);
	hostdata->madapter_info.os_type = cpu_to_be32(SRP_MAD_OS_LINUX);
पूर्ण

/**
 * ibmvscsi_reset_crq_queue() - resets a crq after a failure
 * @queue:	crq_queue to initialize and रेजिस्टर
 * @hostdata:	ibmvscsi_host_data of host
 */
अटल पूर्णांक ibmvscsi_reset_crq_queue(काष्ठा crq_queue *queue,
				    काष्ठा ibmvscsi_host_data *hostdata)
अणु
	पूर्णांक rc = 0;
	काष्ठा vio_dev *vdev = to_vio_dev(hostdata->dev);

	/* Close the CRQ */
	करो अणु
		अगर (rc)
			msleep(100);
		rc = plpar_hcall_norets(H_FREE_CRQ, vdev->unit_address);
	पूर्ण जबतक ((rc == H_BUSY) || (H_IS_LONG_BUSY(rc)));

	/* Clean out the queue */
	स_रखो(queue->msgs, 0x00, PAGE_SIZE);
	queue->cur = 0;

	set_adapter_info(hostdata);

	/* And re-खोलो it again */
	rc = plpar_hcall_norets(H_REG_CRQ,
				vdev->unit_address,
				queue->msg_token, PAGE_SIZE);
	अगर (rc == H_CLOSED) अणु
		/* Adapter is good, but other end is not पढ़ोy */
		dev_warn(hostdata->dev, "Partner adapter not ready\n");
	पूर्ण अन्यथा अगर (rc != 0) अणु
		dev_warn(hostdata->dev, "couldn't register crq--rc 0x%x\n", rc);
	पूर्ण
	वापस rc;
पूर्ण

/**
 * ibmvscsi_init_crq_queue() - Initializes and रेजिस्टरs CRQ with hypervisor
 * @queue:		crq_queue to initialize and रेजिस्टर
 * @hostdata:		ibmvscsi_host_data of host
 * @max_requests:	maximum requests (unused)
 *
 * Allocates a page क्रम messages, maps it क्रम dma, and रेजिस्टरs
 * the crq with the hypervisor.
 * Returns zero on success.
 */
अटल पूर्णांक ibmvscsi_init_crq_queue(काष्ठा crq_queue *queue,
				   काष्ठा ibmvscsi_host_data *hostdata,
				   पूर्णांक max_requests)
अणु
	पूर्णांक rc;
	पूर्णांक retrc;
	काष्ठा vio_dev *vdev = to_vio_dev(hostdata->dev);

	queue->msgs = (काष्ठा viosrp_crq *)get_zeroed_page(GFP_KERNEL);

	अगर (!queue->msgs)
		जाओ दो_स्मृति_failed;
	queue->size = PAGE_SIZE / माप(*queue->msgs);

	queue->msg_token = dma_map_single(hostdata->dev, queue->msgs,
					  queue->size * माप(*queue->msgs),
					  DMA_BIसूचीECTIONAL);

	अगर (dma_mapping_error(hostdata->dev, queue->msg_token))
		जाओ map_failed;

	gather_partition_info();
	set_adapter_info(hostdata);

	retrc = rc = plpar_hcall_norets(H_REG_CRQ,
				vdev->unit_address,
				queue->msg_token, PAGE_SIZE);
	अगर (rc == H_RESOURCE)
		/* maybe kexecing and resource is busy. try a reset */
		rc = ibmvscsi_reset_crq_queue(queue,
					      hostdata);

	अगर (rc == H_CLOSED) अणु
		/* Adapter is good, but other end is not पढ़ोy */
		dev_warn(hostdata->dev, "Partner adapter not ready\n");
		retrc = 0;
	पूर्ण अन्यथा अगर (rc != 0) अणु
		dev_warn(hostdata->dev, "Error %d opening adapter\n", rc);
		जाओ reg_crq_failed;
	पूर्ण

	queue->cur = 0;
	spin_lock_init(&queue->lock);

	tasklet_init(&hostdata->srp_task, (व्योम *)ibmvscsi_task,
		     (अचिन्हित दीर्घ)hostdata);

	अगर (request_irq(vdev->irq,
			ibmvscsi_handle_event,
			0, "ibmvscsi", (व्योम *)hostdata) != 0) अणु
		dev_err(hostdata->dev, "couldn't register irq 0x%x\n",
			vdev->irq);
		जाओ req_irq_failed;
	पूर्ण

	rc = vio_enable_पूर्णांकerrupts(vdev);
	अगर (rc != 0) अणु
		dev_err(hostdata->dev, "Error %d enabling interrupts!!!\n", rc);
		जाओ req_irq_failed;
	पूर्ण

	वापस retrc;

      req_irq_failed:
	tasklet_समाप्त(&hostdata->srp_task);
	rc = 0;
	करो अणु
		अगर (rc)
			msleep(100);
		rc = plpar_hcall_norets(H_FREE_CRQ, vdev->unit_address);
	पूर्ण जबतक ((rc == H_BUSY) || (H_IS_LONG_BUSY(rc)));
      reg_crq_failed:
	dma_unmap_single(hostdata->dev,
			 queue->msg_token,
			 queue->size * माप(*queue->msgs), DMA_BIसूचीECTIONAL);
      map_failed:
	मुक्त_page((अचिन्हित दीर्घ)queue->msgs);
      दो_स्मृति_failed:
	वापस -1;
पूर्ण

/**
 * ibmvscsi_reenable_crq_queue() - reenables a crq after
 * @queue:	crq_queue to initialize and रेजिस्टर
 * @hostdata:	ibmvscsi_host_data of host
 */
अटल पूर्णांक ibmvscsi_reenable_crq_queue(काष्ठा crq_queue *queue,
				       काष्ठा ibmvscsi_host_data *hostdata)
अणु
	पूर्णांक rc = 0;
	काष्ठा vio_dev *vdev = to_vio_dev(hostdata->dev);

	set_adapter_info(hostdata);

	/* Re-enable the CRQ */
	करो अणु
		अगर (rc)
			msleep(100);
		rc = plpar_hcall_norets(H_ENABLE_CRQ, vdev->unit_address);
	पूर्ण जबतक ((rc == H_IN_PROGRESS) || (rc == H_BUSY) || (H_IS_LONG_BUSY(rc)));

	अगर (rc)
		dev_err(hostdata->dev, "Error %d enabling adapter\n", rc);
	वापस rc;
पूर्ण

/* ------------------------------------------------------------
 * Routines क्रम the event pool and event काष्ठाs
 */
/**
 * initialize_event_pool: - Allocates and initializes the event pool क्रम a host
 * @pool:	event_pool to be initialized
 * @size:	Number of events in pool
 * @hostdata:	ibmvscsi_host_data who owns the event pool
 *
 * Returns zero on success.
 */
अटल पूर्णांक initialize_event_pool(काष्ठा event_pool *pool,
				 पूर्णांक size, काष्ठा ibmvscsi_host_data *hostdata)
अणु
	पूर्णांक i;

	pool->size = size;
	pool->next = 0;
	pool->events = kसुस्मृति(pool->size, माप(*pool->events), GFP_KERNEL);
	अगर (!pool->events)
		वापस -ENOMEM;

	pool->iu_storage =
	    dma_alloc_coherent(hostdata->dev,
			       pool->size * माप(*pool->iu_storage),
			       &pool->iu_token, 0);
	अगर (!pool->iu_storage) अणु
		kमुक्त(pool->events);
		वापस -ENOMEM;
	पूर्ण

	क्रम (i = 0; i < pool->size; ++i) अणु
		काष्ठा srp_event_काष्ठा *evt = &pool->events[i];
		स_रखो(&evt->crq, 0x00, माप(evt->crq));
		atomic_set(&evt->मुक्त, 1);
		evt->crq.valid = VIOSRP_CRQ_CMD_RSP;
		evt->crq.IU_length = cpu_to_be16(माप(*evt->xfer_iu));
		evt->crq.IU_data_ptr = cpu_to_be64(pool->iu_token +
			माप(*evt->xfer_iu) * i);
		evt->xfer_iu = pool->iu_storage + i;
		evt->hostdata = hostdata;
		evt->ext_list = शून्य;
		evt->ext_list_token = 0;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * release_event_pool() - Frees memory of an event pool of a host
 * @pool:	event_pool to be released
 * @hostdata:	ibmvscsi_host_data who owns the even pool
 *
 * Returns zero on success.
 */
अटल व्योम release_event_pool(काष्ठा event_pool *pool,
			       काष्ठा ibmvscsi_host_data *hostdata)
अणु
	पूर्णांक i, in_use = 0;
	क्रम (i = 0; i < pool->size; ++i) अणु
		अगर (atomic_पढ़ो(&pool->events[i].मुक्त) != 1)
			++in_use;
		अगर (pool->events[i].ext_list) अणु
			dma_मुक्त_coherent(hostdata->dev,
				  SG_ALL * माप(काष्ठा srp_direct_buf),
				  pool->events[i].ext_list,
				  pool->events[i].ext_list_token);
		पूर्ण
	पूर्ण
	अगर (in_use)
		dev_warn(hostdata->dev, "releasing event pool with %d "
			 "events still in use?\n", in_use);
	kमुक्त(pool->events);
	dma_मुक्त_coherent(hostdata->dev,
			  pool->size * माप(*pool->iu_storage),
			  pool->iu_storage, pool->iu_token);
पूर्ण

/**
 * valid_event_काष्ठा: - Determines अगर event is valid.
 * @pool:	event_pool that contains the event
 * @evt:	srp_event_काष्ठा to be checked क्रम validity
 *
 * Returns zero अगर event is invalid, one otherwise.
*/
अटल पूर्णांक valid_event_काष्ठा(काष्ठा event_pool *pool,
				काष्ठा srp_event_काष्ठा *evt)
अणु
	पूर्णांक index = evt - pool->events;
	अगर (index < 0 || index >= pool->size)	/* outside of bounds */
		वापस 0;
	अगर (evt != pool->events + index)	/* unaligned */
		वापस 0;
	वापस 1;
पूर्ण

/**
 * मुक्त_event_काष्ठा() - Changes status of event to "free"
 * @pool:	event_pool that contains the event
 * @evt:	srp_event_काष्ठा to be modअगरied
 */
अटल व्योम मुक्त_event_काष्ठा(काष्ठा event_pool *pool,
				       काष्ठा srp_event_काष्ठा *evt)
अणु
	अगर (!valid_event_काष्ठा(pool, evt)) अणु
		dev_err(evt->hostdata->dev, "Freeing invalid event_struct %p "
			"(not in pool %p)\n", evt, pool->events);
		वापस;
	पूर्ण
	अगर (atomic_inc_वापस(&evt->मुक्त) != 1) अणु
		dev_err(evt->hostdata->dev, "Freeing event_struct %p "
			"which is not in use!\n", evt);
		वापस;
	पूर्ण
पूर्ण

/**
 * get_event_काष्ठा() - Gets the next मुक्त event in pool
 * @pool:	event_pool that contains the events to be searched
 *
 * Returns the next event in "free" state, and शून्य अगर none are मुक्त.
 * Note that no synchronization is करोne here, we assume the host_lock
 * will syncrhonze things.
*/
अटल काष्ठा srp_event_काष्ठा *get_event_काष्ठा(काष्ठा event_pool *pool)
अणु
	पूर्णांक i;
	पूर्णांक poolsize = pool->size;
	पूर्णांक offset = pool->next;

	क्रम (i = 0; i < poolsize; i++) अणु
		offset = (offset + 1) % poolsize;
		अगर (!atomic_dec_अगर_positive(&pool->events[offset].मुक्त)) अणु
			pool->next = offset;
			वापस &pool->events[offset];
		पूर्ण
	पूर्ण

	prपूर्णांकk(KERN_ERR "ibmvscsi: found no event struct in pool!\n");
	वापस शून्य;
पूर्ण

/**
 * init_event_काष्ठा: Initialize fields in an event काष्ठा that are always 
 *                    required.
 * @evt_काष्ठा: The event
 * @करोne:       Routine to call when the event is responded to
 * @क्रमmat:     SRP or MAD क्रमmat
 * @समयout:    समयout value set in the CRQ
 */
अटल व्योम init_event_काष्ठा(काष्ठा srp_event_काष्ठा *evt_काष्ठा,
			      व्योम (*करोne) (काष्ठा srp_event_काष्ठा *),
			      u8 क्रमmat,
			      पूर्णांक समयout)
अणु
	evt_काष्ठा->cmnd = शून्य;
	evt_काष्ठा->cmnd_करोne = शून्य;
	evt_काष्ठा->sync_srp = शून्य;
	evt_काष्ठा->crq.क्रमmat = क्रमmat;
	evt_काष्ठा->crq.समयout = cpu_to_be16(समयout);
	evt_काष्ठा->करोne = करोne;
पूर्ण

/* ------------------------------------------------------------
 * Routines क्रम receiving SCSI responses from the hosting partition
 */

/*
 * set_srp_direction: Set the fields in the srp related to data
 *     direction and number of buffers based on the direction in
 *     the scsi_cmnd and the number of buffers
 */
अटल व्योम set_srp_direction(काष्ठा scsi_cmnd *cmd,
			      काष्ठा srp_cmd *srp_cmd, 
			      पूर्णांक numbuf)
अणु
	u8 fmt;

	अगर (numbuf == 0)
		वापस;
	
	अगर (numbuf == 1)
		fmt = SRP_DATA_DESC_सूचीECT;
	अन्यथा अणु
		fmt = SRP_DATA_DESC_INसूचीECT;
		numbuf = min(numbuf, MAX_INसूचीECT_BUFS);

		अगर (cmd->sc_data_direction == DMA_TO_DEVICE)
			srp_cmd->data_out_desc_cnt = numbuf;
		अन्यथा
			srp_cmd->data_in_desc_cnt = numbuf;
	पूर्ण

	अगर (cmd->sc_data_direction == DMA_TO_DEVICE)
		srp_cmd->buf_fmt = fmt << 4;
	अन्यथा
		srp_cmd->buf_fmt = fmt;
पूर्ण

/**
 * unmap_cmd_data: - Unmap data poपूर्णांकed in srp_cmd based on the क्रमmat
 * @cmd:	srp_cmd whose additional_data member will be unmapped
 * @evt_काष्ठा: the event
 * @dev:	device क्रम which the memory is mapped
 */
अटल व्योम unmap_cmd_data(काष्ठा srp_cmd *cmd,
			   काष्ठा srp_event_काष्ठा *evt_काष्ठा,
			   काष्ठा device *dev)
अणु
	u8 out_fmt, in_fmt;

	out_fmt = cmd->buf_fmt >> 4;
	in_fmt = cmd->buf_fmt & ((1U << 4) - 1);

	अगर (out_fmt == SRP_NO_DATA_DESC && in_fmt == SRP_NO_DATA_DESC)
		वापस;

	अगर (evt_काष्ठा->cmnd)
		scsi_dma_unmap(evt_काष्ठा->cmnd);
पूर्ण

अटल पूर्णांक map_sg_list(काष्ठा scsi_cmnd *cmd, पूर्णांक nseg,
		       काष्ठा srp_direct_buf *md)
अणु
	पूर्णांक i;
	काष्ठा scatterlist *sg;
	u64 total_length = 0;

	scsi_क्रम_each_sg(cmd, sg, nseg, i) अणु
		काष्ठा srp_direct_buf *descr = md + i;
		descr->va = cpu_to_be64(sg_dma_address(sg));
		descr->len = cpu_to_be32(sg_dma_len(sg));
		descr->key = 0;
		total_length += sg_dma_len(sg);
 	पूर्ण
	वापस total_length;
पूर्ण

/**
 * map_sg_data: - Maps dma क्रम a scatterlist and initializes descriptor fields
 * @cmd:	काष्ठा scsi_cmnd with the scatterlist
 * @evt_काष्ठा:	काष्ठा srp_event_काष्ठा to map
 * @srp_cmd:	srp_cmd that contains the memory descriptor
 * @dev:	device क्रम which to map dma memory
 *
 * Called by map_data_क्रम_srp_cmd() when building srp cmd from scsi cmd.
 * Returns 1 on success.
*/
अटल पूर्णांक map_sg_data(काष्ठा scsi_cmnd *cmd,
		       काष्ठा srp_event_काष्ठा *evt_काष्ठा,
		       काष्ठा srp_cmd *srp_cmd, काष्ठा device *dev)
अणु

	पूर्णांक sg_mapped;
	u64 total_length = 0;
	काष्ठा srp_direct_buf *data =
		(काष्ठा srp_direct_buf *) srp_cmd->add_data;
	काष्ठा srp_indirect_buf *indirect =
		(काष्ठा srp_indirect_buf *) data;

	sg_mapped = scsi_dma_map(cmd);
	अगर (!sg_mapped)
		वापस 1;
	अन्यथा अगर (sg_mapped < 0)
		वापस 0;

	set_srp_direction(cmd, srp_cmd, sg_mapped);

	/* special हाल; we can use a single direct descriptor */
	अगर (sg_mapped == 1) अणु
		map_sg_list(cmd, sg_mapped, data);
		वापस 1;
	पूर्ण

	indirect->table_desc.va = 0;
	indirect->table_desc.len = cpu_to_be32(sg_mapped *
					       माप(काष्ठा srp_direct_buf));
	indirect->table_desc.key = 0;

	अगर (sg_mapped <= MAX_INसूचीECT_BUFS) अणु
		total_length = map_sg_list(cmd, sg_mapped,
					   &indirect->desc_list[0]);
		indirect->len = cpu_to_be32(total_length);
		वापस 1;
	पूर्ण

	/* get indirect table */
	अगर (!evt_काष्ठा->ext_list) अणु
		evt_काष्ठा->ext_list = dma_alloc_coherent(dev,
					   SG_ALL * माप(काष्ठा srp_direct_buf),
					   &evt_काष्ठा->ext_list_token, 0);
		अगर (!evt_काष्ठा->ext_list) अणु
			अगर (!firmware_has_feature(FW_FEATURE_CMO))
				sdev_prपूर्णांकk(KERN_ERR, cmd->device,
				            "Can't allocate memory "
				            "for indirect table\n");
			scsi_dma_unmap(cmd);
			वापस 0;
		पूर्ण
	पूर्ण

	total_length = map_sg_list(cmd, sg_mapped, evt_काष्ठा->ext_list);

	indirect->len = cpu_to_be32(total_length);
	indirect->table_desc.va = cpu_to_be64(evt_काष्ठा->ext_list_token);
	indirect->table_desc.len = cpu_to_be32(sg_mapped *
					       माप(indirect->desc_list[0]));
	स_नकल(indirect->desc_list, evt_काष्ठा->ext_list,
	       MAX_INसूचीECT_BUFS * माप(काष्ठा srp_direct_buf));
 	वापस 1;
पूर्ण

/**
 * map_data_क्रम_srp_cmd: - Calls functions to map data क्रम srp cmds
 * @cmd:	काष्ठा scsi_cmnd with the memory to be mapped
 * @evt_काष्ठा:	काष्ठा srp_event_काष्ठा to map
 * @srp_cmd:	srp_cmd that contains the memory descriptor
 * @dev:	dma device क्रम which to map dma memory
 *
 * Called by scsi_cmd_to_srp_cmd() when converting scsi cmds to srp cmds 
 * Returns 1 on success.
*/
अटल पूर्णांक map_data_क्रम_srp_cmd(काष्ठा scsi_cmnd *cmd,
				काष्ठा srp_event_काष्ठा *evt_काष्ठा,
				काष्ठा srp_cmd *srp_cmd, काष्ठा device *dev)
अणु
	चयन (cmd->sc_data_direction) अणु
	हाल DMA_FROM_DEVICE:
	हाल DMA_TO_DEVICE:
		अवरोध;
	हाल DMA_NONE:
		वापस 1;
	हाल DMA_BIसूचीECTIONAL:
		sdev_prपूर्णांकk(KERN_ERR, cmd->device,
			    "Can't map DMA_BIDIRECTIONAL to read/write\n");
		वापस 0;
	शेष:
		sdev_prपूर्णांकk(KERN_ERR, cmd->device,
			    "Unknown data direction 0x%02x; can't map!\n",
			    cmd->sc_data_direction);
		वापस 0;
	पूर्ण

	वापस map_sg_data(cmd, evt_काष्ठा, srp_cmd, dev);
पूर्ण

/**
 * purge_requests: Our भव adapter just shut करोwn.  purge any sent requests
 * @hostdata:    the adapter
 * @error_code:  error code to वापस as the 'result'
 */
अटल व्योम purge_requests(काष्ठा ibmvscsi_host_data *hostdata, पूर्णांक error_code)
अणु
	काष्ठा srp_event_काष्ठा *evt;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(hostdata->host->host_lock, flags);
	जबतक (!list_empty(&hostdata->sent)) अणु
		evt = list_first_entry(&hostdata->sent, काष्ठा srp_event_काष्ठा, list);
		list_del(&evt->list);
		del_समयr(&evt->समयr);

		spin_unlock_irqrestore(hostdata->host->host_lock, flags);
		अगर (evt->cmnd) अणु
			evt->cmnd->result = (error_code << 16);
			unmap_cmd_data(&evt->iu.srp.cmd, evt,
				       evt->hostdata->dev);
			अगर (evt->cmnd_करोne)
				evt->cmnd_करोne(evt->cmnd);
		पूर्ण अन्यथा अगर (evt->करोne && evt->crq.क्रमmat != VIOSRP_MAD_FORMAT &&
			   evt->iu.srp.login_req.opcode != SRP_LOGIN_REQ)
			evt->करोne(evt);
		मुक्त_event_काष्ठा(&evt->hostdata->pool, evt);
		spin_lock_irqsave(hostdata->host->host_lock, flags);
	पूर्ण
	spin_unlock_irqrestore(hostdata->host->host_lock, flags);
पूर्ण

/**
 * ibmvscsi_set_request_limit - Set the adapter request_limit in response to
 * an adapter failure, reset, or SRP Login. Done under host lock to prevent
 * race with SCSI command submission.
 * @hostdata:	adapter to adjust
 * @limit:	new request limit
 */
अटल व्योम ibmvscsi_set_request_limit(काष्ठा ibmvscsi_host_data *hostdata, पूर्णांक limit)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(hostdata->host->host_lock, flags);
	atomic_set(&hostdata->request_limit, limit);
	spin_unlock_irqrestore(hostdata->host->host_lock, flags);
पूर्ण

/**
 * ibmvscsi_reset_host - Reset the connection to the server
 * @hostdata:	काष्ठा ibmvscsi_host_data to reset
*/
अटल व्योम ibmvscsi_reset_host(काष्ठा ibmvscsi_host_data *hostdata)
अणु
	scsi_block_requests(hostdata->host);
	ibmvscsi_set_request_limit(hostdata, 0);

	purge_requests(hostdata, DID_ERROR);
	hostdata->action = IBMVSCSI_HOST_ACTION_RESET;
	wake_up(&hostdata->work_रुको_q);
पूर्ण

/**
 * ibmvscsi_समयout - Internal command समयout handler
 * @t:	काष्ठा srp_event_काष्ठा that समयd out
 *
 * Called when an पूर्णांकernally generated command बार out
*/
अटल व्योम ibmvscsi_समयout(काष्ठा समयr_list *t)
अणु
	काष्ठा srp_event_काष्ठा *evt_काष्ठा = from_समयr(evt_काष्ठा, t, समयr);
	काष्ठा ibmvscsi_host_data *hostdata = evt_काष्ठा->hostdata;

	dev_err(hostdata->dev, "Command timed out (%x). Resetting connection\n",
		evt_काष्ठा->iu.srp.cmd.opcode);

	ibmvscsi_reset_host(hostdata);
पूर्ण


/* ------------------------------------------------------------
 * Routines क्रम sending and receiving SRPs
 */
/**
 * ibmvscsi_send_srp_event: - Transक्रमms event to u64 array and calls send_crq()
 * @evt_काष्ठा:	evt_काष्ठा to be sent
 * @hostdata:	ibmvscsi_host_data of host
 * @समयout:	समयout in seconds - 0 means करो not समय command
 *
 * Returns the value वापसed from ibmvscsi_send_crq(). (Zero क्रम success)
 * Note that this routine assumes that host_lock is held क्रम synchronization
*/
अटल पूर्णांक ibmvscsi_send_srp_event(काष्ठा srp_event_काष्ठा *evt_काष्ठा,
				   काष्ठा ibmvscsi_host_data *hostdata,
				   अचिन्हित दीर्घ समयout)
अणु
	__be64 *crq_as_u64 = (__be64 *)&evt_काष्ठा->crq;
	पूर्णांक request_status = 0;
	पूर्णांक rc;
	पूर्णांक srp_req = 0;

	/* If we have exhausted our request limit, just fail this request,
	 * unless it is क्रम a reset or पात.
	 * Note that there are rare हालs involving driver generated requests 
	 * (such as task management requests) that the mid layer may think we
	 * can handle more requests (can_queue) when we actually can't
	 */
	अगर (evt_काष्ठा->crq.क्रमmat == VIOSRP_SRP_FORMAT) अणु
		srp_req = 1;
		request_status =
			atomic_dec_अगर_positive(&hostdata->request_limit);
		/* If request limit was -1 when we started, it is now even
		 * less than that
		 */
		अगर (request_status < -1)
			जाओ send_error;
		/* Otherwise, we may have run out of requests. */
		/* If request limit was 0 when we started the adapter is in the
		 * process of perक्रमming a login with the server adapter, or
		 * we may have run out of requests.
		 */
		अन्यथा अगर (request_status == -1 &&
		         evt_काष्ठा->iu.srp.login_req.opcode != SRP_LOGIN_REQ)
			जाओ send_busy;
		/* Abort and reset calls should make it through.
		 * Nothing except पात and reset should use the last two
		 * slots unless we had two or less to begin with.
		 */
		अन्यथा अगर (request_status < 2 &&
		         evt_काष्ठा->iu.srp.cmd.opcode != SRP_TSK_MGMT) अणु
			/* In the हाल that we have less than two requests
			 * available, check the server limit as a combination
			 * of the request limit and the number of requests
			 * in-flight (the size of the send list).  If the
			 * server limit is greater than 2, वापस busy so
			 * that the last two are reserved क्रम reset and पात.
			 */
			पूर्णांक server_limit = request_status;
			काष्ठा srp_event_काष्ठा *पंचांगp_evt;

			list_क्रम_each_entry(पंचांगp_evt, &hostdata->sent, list) अणु
				server_limit++;
			पूर्ण

			अगर (server_limit > 2)
				जाओ send_busy;
		पूर्ण
	पूर्ण

	/* Copy the IU पूर्णांकo the transfer area */
	*evt_काष्ठा->xfer_iu = evt_काष्ठा->iu;
	evt_काष्ठा->xfer_iu->srp.rsp.tag = (u64)evt_काष्ठा;

	/* Add this to the sent list.  We need to करो this 
	 * beक्रमe we actually send 
	 * in हाल it comes back REALLY fast
	 */
	list_add_tail(&evt_काष्ठा->list, &hostdata->sent);

	समयr_setup(&evt_काष्ठा->समयr, ibmvscsi_समयout, 0);
	अगर (समयout) अणु
		evt_काष्ठा->समयr.expires = jअगरfies + (समयout * HZ);
		add_समयr(&evt_काष्ठा->समयr);
	पूर्ण

	rc = ibmvscsi_send_crq(hostdata, be64_to_cpu(crq_as_u64[0]),
			       be64_to_cpu(crq_as_u64[1]));
	अगर (rc != 0) अणु
		list_del(&evt_काष्ठा->list);
		del_समयr(&evt_काष्ठा->समयr);

		/* If send_crq वापसs H_CLOSED, वापस SCSI_MLQUEUE_HOST_BUSY.
		 * Firmware will send a CRQ with a transport event (0xFF) to
		 * tell this client what has happened to the transport.  This
		 * will be handled in ibmvscsi_handle_crq()
		 */
		अगर (rc == H_CLOSED) अणु
			dev_warn(hostdata->dev, "send warning. "
			         "Receive queue closed, will retry.\n");
			जाओ send_busy;
		पूर्ण
		dev_err(hostdata->dev, "send error %d\n", rc);
		अगर (srp_req)
			atomic_inc(&hostdata->request_limit);
		जाओ send_error;
	पूर्ण

	वापस 0;

 send_busy:
	unmap_cmd_data(&evt_काष्ठा->iu.srp.cmd, evt_काष्ठा, hostdata->dev);

	मुक्त_event_काष्ठा(&hostdata->pool, evt_काष्ठा);
	अगर (srp_req && request_status != -1)
		atomic_inc(&hostdata->request_limit);
	वापस SCSI_MLQUEUE_HOST_BUSY;

 send_error:
	unmap_cmd_data(&evt_काष्ठा->iu.srp.cmd, evt_काष्ठा, hostdata->dev);

	अगर (evt_काष्ठा->cmnd != शून्य) अणु
		evt_काष्ठा->cmnd->result = DID_ERROR << 16;
		evt_काष्ठा->cmnd_करोne(evt_काष्ठा->cmnd);
	पूर्ण अन्यथा अगर (evt_काष्ठा->करोne)
		evt_काष्ठा->करोne(evt_काष्ठा);

	मुक्त_event_काष्ठा(&hostdata->pool, evt_काष्ठा);
	वापस 0;
पूर्ण

/**
 * handle_cmd_rsp: -  Handle responses from commands
 * @evt_काष्ठा:	srp_event_काष्ठा to be handled
 *
 * Used as a callback by when sending scsi cmds.
 * Gets called by ibmvscsi_handle_crq()
*/
अटल व्योम handle_cmd_rsp(काष्ठा srp_event_काष्ठा *evt_काष्ठा)
अणु
	काष्ठा srp_rsp *rsp = &evt_काष्ठा->xfer_iu->srp.rsp;
	काष्ठा scsi_cmnd *cmnd = evt_काष्ठा->cmnd;

	अगर (unlikely(rsp->opcode != SRP_RSP)) अणु
		अगर (prपूर्णांकk_ratelimit())
			dev_warn(evt_काष्ठा->hostdata->dev,
				 "bad SRP RSP type %#02x\n", rsp->opcode);
	पूर्ण
	
	अगर (cmnd) अणु
		cmnd->result |= rsp->status;
		अगर (((cmnd->result >> 1) & 0x1f) == CHECK_CONDITION)
			स_नकल(cmnd->sense_buffer,
			       rsp->data,
			       be32_to_cpu(rsp->sense_data_len));
		unmap_cmd_data(&evt_काष्ठा->iu.srp.cmd, 
			       evt_काष्ठा, 
			       evt_काष्ठा->hostdata->dev);

		अगर (rsp->flags & SRP_RSP_FLAG_DOOVER)
			scsi_set_resid(cmnd,
				       be32_to_cpu(rsp->data_out_res_cnt));
		अन्यथा अगर (rsp->flags & SRP_RSP_FLAG_DIOVER)
			scsi_set_resid(cmnd, be32_to_cpu(rsp->data_in_res_cnt));
	पूर्ण

	अगर (evt_काष्ठा->cmnd_करोne)
		evt_काष्ठा->cmnd_करोne(cmnd);
पूर्ण

/**
 * lun_from_dev: - Returns the lun of the scsi device
 * @dev:	काष्ठा scsi_device
 *
*/
अटल अंतरभूत u16 lun_from_dev(काष्ठा scsi_device *dev)
अणु
	वापस (0x2 << 14) | (dev->id << 8) | (dev->channel << 5) | dev->lun;
पूर्ण

/**
 * ibmvscsi_queuecommand_lck() - The queuecommand function of the scsi ढाँचा
 * @cmnd:	काष्ठा scsi_cmnd to be executed
 * @करोne:	Callback function to be called when cmd is completed
*/
अटल पूर्णांक ibmvscsi_queuecommand_lck(काष्ठा scsi_cmnd *cmnd,
				 व्योम (*करोne) (काष्ठा scsi_cmnd *))
अणु
	काष्ठा srp_cmd *srp_cmd;
	काष्ठा srp_event_काष्ठा *evt_काष्ठा;
	काष्ठा srp_indirect_buf *indirect;
	काष्ठा ibmvscsi_host_data *hostdata = shost_priv(cmnd->device->host);
	u16 lun = lun_from_dev(cmnd->device);
	u8 out_fmt, in_fmt;

	cmnd->result = (DID_OK << 16);
	evt_काष्ठा = get_event_काष्ठा(&hostdata->pool);
	अगर (!evt_काष्ठा)
		वापस SCSI_MLQUEUE_HOST_BUSY;

	/* Set up the actual SRP IU */
	srp_cmd = &evt_काष्ठा->iu.srp.cmd;
	स_रखो(srp_cmd, 0x00, SRP_MAX_IU_LEN);
	srp_cmd->opcode = SRP_CMD;
	स_नकल(srp_cmd->cdb, cmnd->cmnd, माप(srp_cmd->cdb));
	पूर्णांक_to_scsilun(lun, &srp_cmd->lun);

	अगर (!map_data_क्रम_srp_cmd(cmnd, evt_काष्ठा, srp_cmd, hostdata->dev)) अणु
		अगर (!firmware_has_feature(FW_FEATURE_CMO))
			sdev_prपूर्णांकk(KERN_ERR, cmnd->device,
			            "couldn't convert cmd to srp_cmd\n");
		मुक्त_event_काष्ठा(&hostdata->pool, evt_काष्ठा);
		वापस SCSI_MLQUEUE_HOST_BUSY;
	पूर्ण

	init_event_काष्ठा(evt_काष्ठा,
			  handle_cmd_rsp,
			  VIOSRP_SRP_FORMAT,
			  cmnd->request->समयout/HZ);

	evt_काष्ठा->cmnd = cmnd;
	evt_काष्ठा->cmnd_करोne = करोne;

	/* Fix up dma address of the buffer itself */
	indirect = (काष्ठा srp_indirect_buf *) srp_cmd->add_data;
	out_fmt = srp_cmd->buf_fmt >> 4;
	in_fmt = srp_cmd->buf_fmt & ((1U << 4) - 1);
	अगर ((in_fmt == SRP_DATA_DESC_INसूचीECT ||
	     out_fmt == SRP_DATA_DESC_INसूचीECT) &&
	    indirect->table_desc.va == 0) अणु
		indirect->table_desc.va =
			cpu_to_be64(be64_to_cpu(evt_काष्ठा->crq.IU_data_ptr) +
			दुरत्व(काष्ठा srp_cmd, add_data) +
			दुरत्व(काष्ठा srp_indirect_buf, desc_list));
	पूर्ण

	वापस ibmvscsi_send_srp_event(evt_काष्ठा, hostdata, 0);
पूर्ण

अटल DEF_SCSI_QCMD(ibmvscsi_queuecommand)

/* ------------------------------------------------------------
 * Routines क्रम driver initialization
 */

/**
 * map_persist_bufs: - Pre-map persistent data क्रम adapter logins
 * @hostdata:   ibmvscsi_host_data of host
 *
 * Map the capabilities and adapter info DMA buffers to aव्योम runसमय failures.
 * Return 1 on error, 0 on success.
 */
अटल पूर्णांक map_persist_bufs(काष्ठा ibmvscsi_host_data *hostdata)
अणु

	hostdata->caps_addr = dma_map_single(hostdata->dev, &hostdata->caps,
					     माप(hostdata->caps), DMA_BIसूचीECTIONAL);

	अगर (dma_mapping_error(hostdata->dev, hostdata->caps_addr)) अणु
		dev_err(hostdata->dev, "Unable to map capabilities buffer!\n");
		वापस 1;
	पूर्ण

	hostdata->adapter_info_addr = dma_map_single(hostdata->dev,
						     &hostdata->madapter_info,
						     माप(hostdata->madapter_info),
						     DMA_BIसूचीECTIONAL);
	अगर (dma_mapping_error(hostdata->dev, hostdata->adapter_info_addr)) अणु
		dev_err(hostdata->dev, "Unable to map adapter info buffer!\n");
		dma_unmap_single(hostdata->dev, hostdata->caps_addr,
				 माप(hostdata->caps), DMA_BIसूचीECTIONAL);
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * unmap_persist_bufs: - Unmap persistent data needed क्रम adapter logins
 * @hostdata:   ibmvscsi_host_data of host
 *
 * Unmap the capabilities and adapter info DMA buffers
 */
अटल व्योम unmap_persist_bufs(काष्ठा ibmvscsi_host_data *hostdata)
अणु
	dma_unmap_single(hostdata->dev, hostdata->caps_addr,
			 माप(hostdata->caps), DMA_BIसूचीECTIONAL);

	dma_unmap_single(hostdata->dev, hostdata->adapter_info_addr,
			 माप(hostdata->madapter_info), DMA_BIसूचीECTIONAL);
पूर्ण

/**
 * login_rsp: - Handle response to SRP login request
 * @evt_काष्ठा:	srp_event_काष्ठा with the response
 *
 * Used as a "done" callback by when sending srp_login. Gets called
 * by ibmvscsi_handle_crq()
*/
अटल व्योम login_rsp(काष्ठा srp_event_काष्ठा *evt_काष्ठा)
अणु
	काष्ठा ibmvscsi_host_data *hostdata = evt_काष्ठा->hostdata;
	चयन (evt_काष्ठा->xfer_iu->srp.login_rsp.opcode) अणु
	हाल SRP_LOGIN_RSP:	/* it worked! */
		अवरोध;
	हाल SRP_LOGIN_REJ:	/* refused! */
		dev_info(hostdata->dev, "SRP_LOGIN_REJ reason %u\n",
			 evt_काष्ठा->xfer_iu->srp.login_rej.reason);
		/* Login failed.  */
		ibmvscsi_set_request_limit(hostdata, -1);
		वापस;
	शेष:
		dev_err(hostdata->dev, "Invalid login response typecode 0x%02x!\n",
			evt_काष्ठा->xfer_iu->srp.login_rsp.opcode);
		/* Login failed.  */
		ibmvscsi_set_request_limit(hostdata, -1);
		वापस;
	पूर्ण

	dev_info(hostdata->dev, "SRP_LOGIN succeeded\n");
	hostdata->client_migrated = 0;

	/* Now we know what the real request-limit is.
	 * This value is set rather than added to request_limit because
	 * request_limit could have been set to -1 by this client.
	 */
	ibmvscsi_set_request_limit(hostdata,
		   be32_to_cpu(evt_काष्ठा->xfer_iu->srp.login_rsp.req_lim_delta));

	/* If we had any pending I/Os, kick them */
	hostdata->action = IBMVSCSI_HOST_ACTION_UNBLOCK;
	wake_up(&hostdata->work_रुको_q);
पूर्ण

/**
 * send_srp_login: - Sends the srp login
 * @hostdata:	ibmvscsi_host_data of host
 *
 * Returns zero अगर successful.
*/
अटल पूर्णांक send_srp_login(काष्ठा ibmvscsi_host_data *hostdata)
अणु
	पूर्णांक rc;
	अचिन्हित दीर्घ flags;
	काष्ठा srp_login_req *login;
	काष्ठा srp_event_काष्ठा *evt_काष्ठा = get_event_काष्ठा(&hostdata->pool);

	BUG_ON(!evt_काष्ठा);
	init_event_काष्ठा(evt_काष्ठा, login_rsp,
			  VIOSRP_SRP_FORMAT, login_समयout);

	login = &evt_काष्ठा->iu.srp.login_req;
	स_रखो(login, 0, माप(*login));
	login->opcode = SRP_LOGIN_REQ;
	login->req_it_iu_len = cpu_to_be32(माप(जोड़ srp_iu));
	login->req_buf_fmt = cpu_to_be16(SRP_BUF_FORMAT_सूचीECT |
					 SRP_BUF_FORMAT_INसूचीECT);

	/* Start out with a request limit of 0, since this is negotiated in
	 * the login request we are just sending and login requests always
	 * get sent by the driver regardless of request_limit.
	 */
	ibmvscsi_set_request_limit(hostdata, 0);

	spin_lock_irqsave(hostdata->host->host_lock, flags);
	rc = ibmvscsi_send_srp_event(evt_काष्ठा, hostdata, login_समयout * 2);
	spin_unlock_irqrestore(hostdata->host->host_lock, flags);
	dev_info(hostdata->dev, "sent SRP login\n");
	वापस rc;
पूर्ण;

/**
 * capabilities_rsp: - Handle response to MAD adapter capabilities request
 * @evt_काष्ठा:	srp_event_काष्ठा with the response
 *
 * Used as a "done" callback by when sending adapter_info.
 */
अटल व्योम capabilities_rsp(काष्ठा srp_event_काष्ठा *evt_काष्ठा)
अणु
	काष्ठा ibmvscsi_host_data *hostdata = evt_काष्ठा->hostdata;

	अगर (evt_काष्ठा->xfer_iu->mad.capabilities.common.status) अणु
		dev_err(hostdata->dev, "error 0x%X getting capabilities info\n",
			evt_काष्ठा->xfer_iu->mad.capabilities.common.status);
	पूर्ण अन्यथा अणु
		अगर (hostdata->caps.migration.common.server_support !=
		    cpu_to_be16(SERVER_SUPPORTS_CAP))
			dev_info(hostdata->dev, "Partition migration not supported\n");

		अगर (client_reserve) अणु
			अगर (hostdata->caps.reserve.common.server_support ==
			    cpu_to_be16(SERVER_SUPPORTS_CAP))
				dev_info(hostdata->dev, "Client reserve enabled\n");
			अन्यथा
				dev_info(hostdata->dev, "Client reserve not supported\n");
		पूर्ण
	पूर्ण

	send_srp_login(hostdata);
पूर्ण

/**
 * send_mad_capabilities: - Sends the mad capabilities request
 *      and stores the result so it can be retrieved with
 * @hostdata:	ibmvscsi_host_data of host
 */
अटल व्योम send_mad_capabilities(काष्ठा ibmvscsi_host_data *hostdata)
अणु
	काष्ठा viosrp_capabilities *req;
	काष्ठा srp_event_काष्ठा *evt_काष्ठा;
	अचिन्हित दीर्घ flags;
	काष्ठा device_node *of_node = hostdata->dev->of_node;
	स्थिर अक्षर *location;

	evt_काष्ठा = get_event_काष्ठा(&hostdata->pool);
	BUG_ON(!evt_काष्ठा);

	init_event_काष्ठा(evt_काष्ठा, capabilities_rsp,
			  VIOSRP_MAD_FORMAT, info_समयout);

	req = &evt_काष्ठा->iu.mad.capabilities;
	स_रखो(req, 0, माप(*req));

	hostdata->caps.flags = cpu_to_be32(CAP_LIST_SUPPORTED);
	अगर (hostdata->client_migrated)
		hostdata->caps.flags |= cpu_to_be32(CLIENT_MIGRATED);

	strlcpy(hostdata->caps.name, dev_name(&hostdata->host->shost_gendev),
		माप(hostdata->caps.name));

	location = of_get_property(of_node, "ibm,loc-code", शून्य);
	location = location ? location : dev_name(hostdata->dev);
	strlcpy(hostdata->caps.loc, location, माप(hostdata->caps.loc));

	req->common.type = cpu_to_be32(VIOSRP_CAPABILITIES_TYPE);
	req->buffer = cpu_to_be64(hostdata->caps_addr);

	hostdata->caps.migration.common.cap_type =
				cpu_to_be32(MIGRATION_CAPABILITIES);
	hostdata->caps.migration.common.length =
				cpu_to_be16(माप(hostdata->caps.migration));
	hostdata->caps.migration.common.server_support =
				cpu_to_be16(SERVER_SUPPORTS_CAP);
	hostdata->caps.migration.ecl = cpu_to_be32(1);

	अगर (client_reserve) अणु
		hostdata->caps.reserve.common.cap_type =
					cpu_to_be32(RESERVATION_CAPABILITIES);
		hostdata->caps.reserve.common.length =
				cpu_to_be16(माप(hostdata->caps.reserve));
		hostdata->caps.reserve.common.server_support =
				cpu_to_be16(SERVER_SUPPORTS_CAP);
		hostdata->caps.reserve.type =
				cpu_to_be32(CLIENT_RESERVE_SCSI_2);
		req->common.length =
				cpu_to_be16(माप(hostdata->caps));
	पूर्ण अन्यथा
		req->common.length = cpu_to_be16(माप(hostdata->caps) -
						माप(hostdata->caps.reserve));

	spin_lock_irqsave(hostdata->host->host_lock, flags);
	अगर (ibmvscsi_send_srp_event(evt_काष्ठा, hostdata, info_समयout * 2))
		dev_err(hostdata->dev, "couldn't send CAPABILITIES_REQ!\n");
	spin_unlock_irqrestore(hostdata->host->host_lock, flags);
पूर्ण;

/**
 * fast_fail_rsp: - Handle response to MAD enable fast fail
 * @evt_काष्ठा:	srp_event_काष्ठा with the response
 *
 * Used as a "done" callback by when sending enable fast fail. Gets called
 * by ibmvscsi_handle_crq()
 */
अटल व्योम fast_fail_rsp(काष्ठा srp_event_काष्ठा *evt_काष्ठा)
अणु
	काष्ठा ibmvscsi_host_data *hostdata = evt_काष्ठा->hostdata;
	u16 status = be16_to_cpu(evt_काष्ठा->xfer_iu->mad.fast_fail.common.status);

	अगर (status == VIOSRP_MAD_NOT_SUPPORTED)
		dev_err(hostdata->dev, "fast_fail not supported in server\n");
	अन्यथा अगर (status == VIOSRP_MAD_FAILED)
		dev_err(hostdata->dev, "fast_fail request failed\n");
	अन्यथा अगर (status != VIOSRP_MAD_SUCCESS)
		dev_err(hostdata->dev, "error 0x%X enabling fast_fail\n", status);

	send_mad_capabilities(hostdata);
पूर्ण

/**
 * enable_fast_fail() - Start host initialization
 * @hostdata:	ibmvscsi_host_data of host
 *
 * Returns zero अगर successful.
 */
अटल पूर्णांक enable_fast_fail(काष्ठा ibmvscsi_host_data *hostdata)
अणु
	पूर्णांक rc;
	अचिन्हित दीर्घ flags;
	काष्ठा viosrp_fast_fail *fast_fail_mad;
	काष्ठा srp_event_काष्ठा *evt_काष्ठा;

	अगर (!fast_fail) अणु
		send_mad_capabilities(hostdata);
		वापस 0;
	पूर्ण

	evt_काष्ठा = get_event_काष्ठा(&hostdata->pool);
	BUG_ON(!evt_काष्ठा);

	init_event_काष्ठा(evt_काष्ठा, fast_fail_rsp, VIOSRP_MAD_FORMAT, info_समयout);

	fast_fail_mad = &evt_काष्ठा->iu.mad.fast_fail;
	स_रखो(fast_fail_mad, 0, माप(*fast_fail_mad));
	fast_fail_mad->common.type = cpu_to_be32(VIOSRP_ENABLE_FAST_FAIL);
	fast_fail_mad->common.length = cpu_to_be16(माप(*fast_fail_mad));

	spin_lock_irqsave(hostdata->host->host_lock, flags);
	rc = ibmvscsi_send_srp_event(evt_काष्ठा, hostdata, info_समयout * 2);
	spin_unlock_irqrestore(hostdata->host->host_lock, flags);
	वापस rc;
पूर्ण

/**
 * adapter_info_rsp: - Handle response to MAD adapter info request
 * @evt_काष्ठा:	srp_event_काष्ठा with the response
 *
 * Used as a "done" callback by when sending adapter_info. Gets called
 * by ibmvscsi_handle_crq()
*/
अटल व्योम adapter_info_rsp(काष्ठा srp_event_काष्ठा *evt_काष्ठा)
अणु
	काष्ठा ibmvscsi_host_data *hostdata = evt_काष्ठा->hostdata;

	अगर (evt_काष्ठा->xfer_iu->mad.adapter_info.common.status) अणु
		dev_err(hostdata->dev, "error %d getting adapter info\n",
			evt_काष्ठा->xfer_iu->mad.adapter_info.common.status);
	पूर्ण अन्यथा अणु
		dev_info(hostdata->dev, "host srp version: %s, "
			 "host partition %s (%d), OS %d, max io %u\n",
			 hostdata->madapter_info.srp_version,
			 hostdata->madapter_info.partition_name,
			 be32_to_cpu(hostdata->madapter_info.partition_number),
			 be32_to_cpu(hostdata->madapter_info.os_type),
			 be32_to_cpu(hostdata->madapter_info.port_max_txu[0]));
		
		अगर (hostdata->madapter_info.port_max_txu[0]) 
			hostdata->host->max_sectors = 
				be32_to_cpu(hostdata->madapter_info.port_max_txu[0]) >> 9;
		
		अगर (be32_to_cpu(hostdata->madapter_info.os_type) == SRP_MAD_OS_AIX &&
		    म_भेद(hostdata->madapter_info.srp_version, "1.6a") <= 0) अणु
			dev_err(hostdata->dev, "host (Ver. %s) doesn't support large transfers\n",
				hostdata->madapter_info.srp_version);
			dev_err(hostdata->dev, "limiting scatterlists to %d\n",
				MAX_INसूचीECT_BUFS);
			hostdata->host->sg_tablesize = MAX_INसूचीECT_BUFS;
		पूर्ण

		अगर (be32_to_cpu(hostdata->madapter_info.os_type) == SRP_MAD_OS_AIX) अणु
			enable_fast_fail(hostdata);
			वापस;
		पूर्ण
	पूर्ण

	send_srp_login(hostdata);
पूर्ण

/**
 * send_mad_adapter_info: - Sends the mad adapter info request
 *      and stores the result so it can be retrieved with
 *      sysfs.  We COULD consider causing a failure अगर the
 *      वापसed SRP version करोesn't match ours.
 * @hostdata:	ibmvscsi_host_data of host
 * 
 * Returns zero अगर successful.
*/
अटल व्योम send_mad_adapter_info(काष्ठा ibmvscsi_host_data *hostdata)
अणु
	काष्ठा viosrp_adapter_info *req;
	काष्ठा srp_event_काष्ठा *evt_काष्ठा;
	अचिन्हित दीर्घ flags;

	evt_काष्ठा = get_event_काष्ठा(&hostdata->pool);
	BUG_ON(!evt_काष्ठा);

	init_event_काष्ठा(evt_काष्ठा,
			  adapter_info_rsp,
			  VIOSRP_MAD_FORMAT,
			  info_समयout);
	
	req = &evt_काष्ठा->iu.mad.adapter_info;
	स_रखो(req, 0x00, माप(*req));
	
	req->common.type = cpu_to_be32(VIOSRP_ADAPTER_INFO_TYPE);
	req->common.length = cpu_to_be16(माप(hostdata->madapter_info));
	req->buffer = cpu_to_be64(hostdata->adapter_info_addr);

	spin_lock_irqsave(hostdata->host->host_lock, flags);
	अगर (ibmvscsi_send_srp_event(evt_काष्ठा, hostdata, info_समयout * 2))
		dev_err(hostdata->dev, "couldn't send ADAPTER_INFO_REQ!\n");
	spin_unlock_irqrestore(hostdata->host->host_lock, flags);
पूर्ण;

/*
 * init_adapter() - Start भव adapter initialization sequence
 */
अटल व्योम init_adapter(काष्ठा ibmvscsi_host_data *hostdata)
अणु
	send_mad_adapter_info(hostdata);
पूर्ण

/*
 * sync_completion: Signal that a synchronous command has completed
 * Note that after वापसing from this call, the evt_काष्ठा is मुक्तd.
 * the caller रुकोing on this completion shouldn't touch the evt_काष्ठा
 * again.
 */
अटल व्योम sync_completion(काष्ठा srp_event_काष्ठा *evt_काष्ठा)
अणु
	/* copy the response back */
	अगर (evt_काष्ठा->sync_srp)
		*evt_काष्ठा->sync_srp = *evt_काष्ठा->xfer_iu;
	
	complete(&evt_काष्ठा->comp);
पूर्ण

/*
 * ibmvscsi_eh_पात_handler: Abort a command...from scsi host ढाँचा
 * send this over to the server and रुको synchronously क्रम the response
 */
अटल पूर्णांक ibmvscsi_eh_पात_handler(काष्ठा scsi_cmnd *cmd)
अणु
	काष्ठा ibmvscsi_host_data *hostdata = shost_priv(cmd->device->host);
	काष्ठा srp_tsk_mgmt *tsk_mgmt;
	काष्ठा srp_event_काष्ठा *evt;
	काष्ठा srp_event_काष्ठा *पंचांगp_evt, *found_evt;
	जोड़ viosrp_iu srp_rsp;
	पूर्णांक rsp_rc;
	अचिन्हित दीर्घ flags;
	u16 lun = lun_from_dev(cmd->device);
	अचिन्हित दीर्घ रुको_चयन = 0;

	/* First, find this command in our sent list so we can figure
	 * out the correct tag
	 */
	spin_lock_irqsave(hostdata->host->host_lock, flags);
	रुको_चयन = jअगरfies + (init_समयout * HZ);
	करो अणु
		found_evt = शून्य;
		list_क्रम_each_entry(पंचांगp_evt, &hostdata->sent, list) अणु
			अगर (पंचांगp_evt->cmnd == cmd) अणु
				found_evt = पंचांगp_evt;
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (!found_evt) अणु
			spin_unlock_irqrestore(hostdata->host->host_lock, flags);
			वापस SUCCESS;
		पूर्ण

		evt = get_event_काष्ठा(&hostdata->pool);
		अगर (evt == शून्य) अणु
			spin_unlock_irqrestore(hostdata->host->host_lock, flags);
			sdev_prपूर्णांकk(KERN_ERR, cmd->device,
				"failed to allocate abort event\n");
			वापस FAILED;
		पूर्ण
	
		init_event_काष्ठा(evt,
				  sync_completion,
				  VIOSRP_SRP_FORMAT,
				  पात_समयout);

		tsk_mgmt = &evt->iu.srp.tsk_mgmt;
	
		/* Set up an पात SRP command */
		स_रखो(tsk_mgmt, 0x00, माप(*tsk_mgmt));
		tsk_mgmt->opcode = SRP_TSK_MGMT;
		पूर्णांक_to_scsilun(lun, &tsk_mgmt->lun);
		tsk_mgmt->tsk_mgmt_func = SRP_TSK_ABORT_TASK;
		tsk_mgmt->task_tag = (u64) found_evt;

		evt->sync_srp = &srp_rsp;

		init_completion(&evt->comp);
		rsp_rc = ibmvscsi_send_srp_event(evt, hostdata, पात_समयout * 2);

		अगर (rsp_rc != SCSI_MLQUEUE_HOST_BUSY)
			अवरोध;

		spin_unlock_irqrestore(hostdata->host->host_lock, flags);
		msleep(10);
		spin_lock_irqsave(hostdata->host->host_lock, flags);
	पूर्ण जबतक (समय_beक्रमe(jअगरfies, रुको_चयन));

	spin_unlock_irqrestore(hostdata->host->host_lock, flags);

	अगर (rsp_rc != 0) अणु
		sdev_prपूर्णांकk(KERN_ERR, cmd->device,
			    "failed to send abort() event. rc=%d\n", rsp_rc);
		वापस FAILED;
	पूर्ण

	sdev_prपूर्णांकk(KERN_INFO, cmd->device,
                    "aborting command. lun 0x%llx, tag 0x%llx\n",
		    (((u64) lun) << 48), (u64) found_evt);

	रुको_क्रम_completion(&evt->comp);

	/* make sure we got a good response */
	अगर (unlikely(srp_rsp.srp.rsp.opcode != SRP_RSP)) अणु
		अगर (prपूर्णांकk_ratelimit())
			sdev_prपूर्णांकk(KERN_WARNING, cmd->device, "abort bad SRP RSP type %d\n",
				    srp_rsp.srp.rsp.opcode);
		वापस FAILED;
	पूर्ण

	अगर (srp_rsp.srp.rsp.flags & SRP_RSP_FLAG_RSPVALID)
		rsp_rc = *((पूर्णांक *)srp_rsp.srp.rsp.data);
	अन्यथा
		rsp_rc = srp_rsp.srp.rsp.status;

	अगर (rsp_rc) अणु
		अगर (prपूर्णांकk_ratelimit())
			sdev_prपूर्णांकk(KERN_WARNING, cmd->device,
				    "abort code %d for task tag 0x%llx\n",
				    rsp_rc, tsk_mgmt->task_tag);
		वापस FAILED;
	पूर्ण

	/* Because we dropped the spinlock above, it's possible
	 * The event is no दीर्घer in our list.  Make sure it didn't
	 * complete जबतक we were पातing
	 */
	spin_lock_irqsave(hostdata->host->host_lock, flags);
	found_evt = शून्य;
	list_क्रम_each_entry(पंचांगp_evt, &hostdata->sent, list) अणु
		अगर (पंचांगp_evt->cmnd == cmd) अणु
			found_evt = पंचांगp_evt;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (found_evt == शून्य) अणु
		spin_unlock_irqrestore(hostdata->host->host_lock, flags);
		sdev_prपूर्णांकk(KERN_INFO, cmd->device, "aborted task tag 0x%llx completed\n",
			    tsk_mgmt->task_tag);
		वापस SUCCESS;
	पूर्ण

	sdev_prपूर्णांकk(KERN_INFO, cmd->device, "successfully aborted task tag 0x%llx\n",
		    tsk_mgmt->task_tag);

	cmd->result = (DID_ABORT << 16);
	list_del(&found_evt->list);
	unmap_cmd_data(&found_evt->iu.srp.cmd, found_evt,
		       found_evt->hostdata->dev);
	मुक्त_event_काष्ठा(&found_evt->hostdata->pool, found_evt);
	spin_unlock_irqrestore(hostdata->host->host_lock, flags);
	atomic_inc(&hostdata->request_limit);
	वापस SUCCESS;
पूर्ण

/*
 * ibmvscsi_eh_device_reset_handler: Reset a single LUN...from scsi host 
 * ढाँचा send this over to the server and रुको synchronously क्रम the 
 * response
 */
अटल पूर्णांक ibmvscsi_eh_device_reset_handler(काष्ठा scsi_cmnd *cmd)
अणु
	काष्ठा ibmvscsi_host_data *hostdata = shost_priv(cmd->device->host);
	काष्ठा srp_tsk_mgmt *tsk_mgmt;
	काष्ठा srp_event_काष्ठा *evt;
	काष्ठा srp_event_काष्ठा *पंचांगp_evt, *pos;
	जोड़ viosrp_iu srp_rsp;
	पूर्णांक rsp_rc;
	अचिन्हित दीर्घ flags;
	u16 lun = lun_from_dev(cmd->device);
	अचिन्हित दीर्घ रुको_चयन = 0;

	spin_lock_irqsave(hostdata->host->host_lock, flags);
	रुको_चयन = jअगरfies + (init_समयout * HZ);
	करो अणु
		evt = get_event_काष्ठा(&hostdata->pool);
		अगर (evt == शून्य) अणु
			spin_unlock_irqrestore(hostdata->host->host_lock, flags);
			sdev_prपूर्णांकk(KERN_ERR, cmd->device,
				"failed to allocate reset event\n");
			वापस FAILED;
		पूर्ण
	
		init_event_काष्ठा(evt,
				  sync_completion,
				  VIOSRP_SRP_FORMAT,
				  reset_समयout);

		tsk_mgmt = &evt->iu.srp.tsk_mgmt;

		/* Set up a lun reset SRP command */
		स_रखो(tsk_mgmt, 0x00, माप(*tsk_mgmt));
		tsk_mgmt->opcode = SRP_TSK_MGMT;
		पूर्णांक_to_scsilun(lun, &tsk_mgmt->lun);
		tsk_mgmt->tsk_mgmt_func = SRP_TSK_LUN_RESET;

		evt->sync_srp = &srp_rsp;

		init_completion(&evt->comp);
		rsp_rc = ibmvscsi_send_srp_event(evt, hostdata, reset_समयout * 2);

		अगर (rsp_rc != SCSI_MLQUEUE_HOST_BUSY)
			अवरोध;

		spin_unlock_irqrestore(hostdata->host->host_lock, flags);
		msleep(10);
		spin_lock_irqsave(hostdata->host->host_lock, flags);
	पूर्ण जबतक (समय_beक्रमe(jअगरfies, रुको_चयन));

	spin_unlock_irqrestore(hostdata->host->host_lock, flags);

	अगर (rsp_rc != 0) अणु
		sdev_prपूर्णांकk(KERN_ERR, cmd->device,
			    "failed to send reset event. rc=%d\n", rsp_rc);
		वापस FAILED;
	पूर्ण

	sdev_prपूर्णांकk(KERN_INFO, cmd->device, "resetting device. lun 0x%llx\n",
		    (((u64) lun) << 48));

	रुको_क्रम_completion(&evt->comp);

	/* make sure we got a good response */
	अगर (unlikely(srp_rsp.srp.rsp.opcode != SRP_RSP)) अणु
		अगर (prपूर्णांकk_ratelimit())
			sdev_prपूर्णांकk(KERN_WARNING, cmd->device, "reset bad SRP RSP type %d\n",
				    srp_rsp.srp.rsp.opcode);
		वापस FAILED;
	पूर्ण

	अगर (srp_rsp.srp.rsp.flags & SRP_RSP_FLAG_RSPVALID)
		rsp_rc = *((पूर्णांक *)srp_rsp.srp.rsp.data);
	अन्यथा
		rsp_rc = srp_rsp.srp.rsp.status;

	अगर (rsp_rc) अणु
		अगर (prपूर्णांकk_ratelimit())
			sdev_prपूर्णांकk(KERN_WARNING, cmd->device,
				    "reset code %d for task tag 0x%llx\n",
				    rsp_rc, tsk_mgmt->task_tag);
		वापस FAILED;
	पूर्ण

	/* We need to find all commands क्रम this LUN that have not yet been
	 * responded to, and fail them with DID_RESET
	 */
	spin_lock_irqsave(hostdata->host->host_lock, flags);
	list_क्रम_each_entry_safe(पंचांगp_evt, pos, &hostdata->sent, list) अणु
		अगर ((पंचांगp_evt->cmnd) && (पंचांगp_evt->cmnd->device == cmd->device)) अणु
			अगर (पंचांगp_evt->cmnd)
				पंचांगp_evt->cmnd->result = (DID_RESET << 16);
			list_del(&पंचांगp_evt->list);
			unmap_cmd_data(&पंचांगp_evt->iu.srp.cmd, पंचांगp_evt,
				       पंचांगp_evt->hostdata->dev);
			मुक्त_event_काष्ठा(&पंचांगp_evt->hostdata->pool,
						   पंचांगp_evt);
			atomic_inc(&hostdata->request_limit);
			अगर (पंचांगp_evt->cmnd_करोne)
				पंचांगp_evt->cmnd_करोne(पंचांगp_evt->cmnd);
			अन्यथा अगर (पंचांगp_evt->करोne)
				पंचांगp_evt->करोne(पंचांगp_evt);
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(hostdata->host->host_lock, flags);
	वापस SUCCESS;
पूर्ण

/**
 * ibmvscsi_eh_host_reset_handler - Reset the connection to the server
 * @cmd:	काष्ठा scsi_cmnd having problems
*/
अटल पूर्णांक ibmvscsi_eh_host_reset_handler(काष्ठा scsi_cmnd *cmd)
अणु
	अचिन्हित दीर्घ रुको_चयन = 0;
	काष्ठा ibmvscsi_host_data *hostdata = shost_priv(cmd->device->host);

	dev_err(hostdata->dev, "Resetting connection due to error recovery\n");

	ibmvscsi_reset_host(hostdata);

	क्रम (रुको_चयन = jअगरfies + (init_समयout * HZ);
	     समय_beक्रमe(jअगरfies, रुको_चयन) &&
		     atomic_पढ़ो(&hostdata->request_limit) < 2;) अणु

		msleep(10);
	पूर्ण

	अगर (atomic_पढ़ो(&hostdata->request_limit) <= 0)
		वापस FAILED;

	वापस SUCCESS;
पूर्ण

/**
 * ibmvscsi_handle_crq: - Handles and मुक्तs received events in the CRQ
 * @crq:	Command/Response queue
 * @hostdata:	ibmvscsi_host_data of host
 *
*/
अटल व्योम ibmvscsi_handle_crq(काष्ठा viosrp_crq *crq,
				काष्ठा ibmvscsi_host_data *hostdata)
अणु
	दीर्घ rc;
	अचिन्हित दीर्घ flags;
	/* The hypervisor copies our tag value here so no byteswapping */
	काष्ठा srp_event_काष्ठा *evt_काष्ठा =
			(__क्रमce काष्ठा srp_event_काष्ठा *)crq->IU_data_ptr;
	चयन (crq->valid) अणु
	हाल VIOSRP_CRQ_INIT_RSP:		/* initialization */
		चयन (crq->क्रमmat) अणु
		हाल VIOSRP_CRQ_INIT:	/* Initialization message */
			dev_info(hostdata->dev, "partner initialized\n");
			/* Send back a response */
			rc = ibmvscsi_send_crq(hostdata, 0xC002000000000000LL, 0);
			अगर (rc == 0) अणु
				/* Now login */
				init_adapter(hostdata);
			पूर्ण अन्यथा अणु
				dev_err(hostdata->dev, "Unable to send init rsp. rc=%ld\n", rc);
			पूर्ण

			अवरोध;
		हाल VIOSRP_CRQ_INIT_COMPLETE:	/* Initialization response */
			dev_info(hostdata->dev, "partner initialization complete\n");

			/* Now login */
			init_adapter(hostdata);
			अवरोध;
		शेष:
			dev_err(hostdata->dev, "unknown crq message type: %d\n", crq->क्रमmat);
		पूर्ण
		वापस;
	हाल VIOSRP_CRQ_XPORT_EVENT:	/* Hypervisor telling us the connection is बंदd */
		scsi_block_requests(hostdata->host);
		ibmvscsi_set_request_limit(hostdata, 0);
		अगर (crq->क्रमmat == 0x06) अणु
			/* We need to re-setup the पूर्णांकerpartition connection */
			dev_info(hostdata->dev, "Re-enabling adapter!\n");
			hostdata->client_migrated = 1;
			hostdata->action = IBMVSCSI_HOST_ACTION_REENABLE;
			purge_requests(hostdata, DID_REQUEUE);
			wake_up(&hostdata->work_रुको_q);
		पूर्ण अन्यथा अणु
			dev_err(hostdata->dev, "Virtual adapter failed rc %d!\n",
				crq->क्रमmat);
			ibmvscsi_reset_host(hostdata);
		पूर्ण
		वापस;
	हाल VIOSRP_CRQ_CMD_RSP:		/* real payload */
		अवरोध;
	शेष:
		dev_err(hostdata->dev, "got an invalid message type 0x%02x\n",
			crq->valid);
		वापस;
	पूर्ण

	/* The only kind of payload CRQs we should get are responses to
	 * things we send. Make sure this response is to something we
	 * actually sent
	 */
	अगर (!valid_event_काष्ठा(&hostdata->pool, evt_काष्ठा)) अणु
		dev_err(hostdata->dev, "returned correlation_token 0x%p is invalid!\n",
		       evt_काष्ठा);
		वापस;
	पूर्ण

	अगर (atomic_पढ़ो(&evt_काष्ठा->मुक्त)) अणु
		dev_err(hostdata->dev, "received duplicate correlation_token 0x%p!\n",
			evt_काष्ठा);
		वापस;
	पूर्ण

	अगर (crq->क्रमmat == VIOSRP_SRP_FORMAT)
		atomic_add(be32_to_cpu(evt_काष्ठा->xfer_iu->srp.rsp.req_lim_delta),
			   &hostdata->request_limit);

	del_समयr(&evt_काष्ठा->समयr);

	अगर ((crq->status != VIOSRP_OK && crq->status != VIOSRP_OK2) && evt_काष्ठा->cmnd)
		evt_काष्ठा->cmnd->result = DID_ERROR << 16;
	अगर (evt_काष्ठा->करोne)
		evt_काष्ठा->करोne(evt_काष्ठा);
	अन्यथा
		dev_err(hostdata->dev, "returned done() is NULL; not running it!\n");

	/*
	 * Lock the host_lock beक्रमe messing with these काष्ठाures, since we
	 * are running in a task context
	 */
	spin_lock_irqsave(evt_काष्ठा->hostdata->host->host_lock, flags);
	list_del(&evt_काष्ठा->list);
	मुक्त_event_काष्ठा(&evt_काष्ठा->hostdata->pool, evt_काष्ठा);
	spin_unlock_irqrestore(evt_काष्ठा->hostdata->host->host_lock, flags);
पूर्ण

/**
 * ibmvscsi_slave_configure: Set the "allow_restart" flag क्रम each disk.
 * @sdev:	काष्ठा scsi_device device to configure
 *
 * Enable allow_restart क्रम a device अगर it is a disk.  Adjust the
 * queue_depth here also as is required by the करोcumentation क्रम
 * काष्ठा scsi_host_ढाँचा.
 */
अटल पूर्णांक ibmvscsi_slave_configure(काष्ठा scsi_device *sdev)
अणु
	काष्ठा Scsi_Host *shost = sdev->host;
	अचिन्हित दीर्घ lock_flags = 0;

	spin_lock_irqsave(shost->host_lock, lock_flags);
	अगर (sdev->type == TYPE_DISK) अणु
		sdev->allow_restart = 1;
		blk_queue_rq_समयout(sdev->request_queue, 120 * HZ);
	पूर्ण
	spin_unlock_irqrestore(shost->host_lock, lock_flags);
	वापस 0;
पूर्ण

/**
 * ibmvscsi_change_queue_depth - Change the device's queue depth
 * @sdev:	scsi device काष्ठा
 * @qdepth:	depth to set
 *
 * Return value:
 * 	actual depth set
 **/
अटल पूर्णांक ibmvscsi_change_queue_depth(काष्ठा scsi_device *sdev, पूर्णांक qdepth)
अणु
	अगर (qdepth > IBMVSCSI_MAX_CMDS_PER_LUN)
		qdepth = IBMVSCSI_MAX_CMDS_PER_LUN;
	वापस scsi_change_queue_depth(sdev, qdepth);
पूर्ण

/* ------------------------------------------------------------
 * sysfs attributes
 */
अटल sमाप_प्रकार show_host_vhost_loc(काष्ठा device *dev,
				   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा Scsi_Host *shost = class_to_shost(dev);
	काष्ठा ibmvscsi_host_data *hostdata = shost_priv(shost);
	पूर्णांक len;

	len = snम_लिखो(buf, माप(hostdata->caps.loc), "%s\n",
		       hostdata->caps.loc);
	वापस len;
पूर्ण

अटल काष्ठा device_attribute ibmvscsi_host_vhost_loc = अणु
	.attr = अणु
		 .name = "vhost_loc",
		 .mode = S_IRUGO,
		 पूर्ण,
	.show = show_host_vhost_loc,
पूर्ण;

अटल sमाप_प्रकार show_host_vhost_name(काष्ठा device *dev,
				    काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा Scsi_Host *shost = class_to_shost(dev);
	काष्ठा ibmvscsi_host_data *hostdata = shost_priv(shost);
	पूर्णांक len;

	len = snम_लिखो(buf, माप(hostdata->caps.name), "%s\n",
		       hostdata->caps.name);
	वापस len;
पूर्ण

अटल काष्ठा device_attribute ibmvscsi_host_vhost_name = अणु
	.attr = अणु
		 .name = "vhost_name",
		 .mode = S_IRUGO,
		 पूर्ण,
	.show = show_host_vhost_name,
पूर्ण;

अटल sमाप_प्रकार show_host_srp_version(काष्ठा device *dev,
				     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा Scsi_Host *shost = class_to_shost(dev);
	काष्ठा ibmvscsi_host_data *hostdata = shost_priv(shost);
	पूर्णांक len;

	len = snम_लिखो(buf, PAGE_SIZE, "%s\n",
		       hostdata->madapter_info.srp_version);
	वापस len;
पूर्ण

अटल काष्ठा device_attribute ibmvscsi_host_srp_version = अणु
	.attr = अणु
		 .name = "srp_version",
		 .mode = S_IRUGO,
		 पूर्ण,
	.show = show_host_srp_version,
पूर्ण;

अटल sमाप_प्रकार show_host_partition_name(काष्ठा device *dev,
					काष्ठा device_attribute *attr,
					अक्षर *buf)
अणु
	काष्ठा Scsi_Host *shost = class_to_shost(dev);
	काष्ठा ibmvscsi_host_data *hostdata = shost_priv(shost);
	पूर्णांक len;

	len = snम_लिखो(buf, PAGE_SIZE, "%s\n",
		       hostdata->madapter_info.partition_name);
	वापस len;
पूर्ण

अटल काष्ठा device_attribute ibmvscsi_host_partition_name = अणु
	.attr = अणु
		 .name = "partition_name",
		 .mode = S_IRUGO,
		 पूर्ण,
	.show = show_host_partition_name,
पूर्ण;

अटल sमाप_प्रकार show_host_partition_number(काष्ठा device *dev,
					  काष्ठा device_attribute *attr,
					  अक्षर *buf)
अणु
	काष्ठा Scsi_Host *shost = class_to_shost(dev);
	काष्ठा ibmvscsi_host_data *hostdata = shost_priv(shost);
	पूर्णांक len;

	len = snम_लिखो(buf, PAGE_SIZE, "%d\n",
		       be32_to_cpu(hostdata->madapter_info.partition_number));
	वापस len;
पूर्ण

अटल काष्ठा device_attribute ibmvscsi_host_partition_number = अणु
	.attr = अणु
		 .name = "partition_number",
		 .mode = S_IRUGO,
		 पूर्ण,
	.show = show_host_partition_number,
पूर्ण;

अटल sमाप_प्रकार show_host_mad_version(काष्ठा device *dev,
				     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा Scsi_Host *shost = class_to_shost(dev);
	काष्ठा ibmvscsi_host_data *hostdata = shost_priv(shost);
	पूर्णांक len;

	len = snम_लिखो(buf, PAGE_SIZE, "%d\n",
		       be32_to_cpu(hostdata->madapter_info.mad_version));
	वापस len;
पूर्ण

अटल काष्ठा device_attribute ibmvscsi_host_mad_version = अणु
	.attr = अणु
		 .name = "mad_version",
		 .mode = S_IRUGO,
		 पूर्ण,
	.show = show_host_mad_version,
पूर्ण;

अटल sमाप_प्रकार show_host_os_type(काष्ठा device *dev,
				 काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा Scsi_Host *shost = class_to_shost(dev);
	काष्ठा ibmvscsi_host_data *hostdata = shost_priv(shost);
	पूर्णांक len;

	len = snम_लिखो(buf, PAGE_SIZE, "%d\n",
		       be32_to_cpu(hostdata->madapter_info.os_type));
	वापस len;
पूर्ण

अटल काष्ठा device_attribute ibmvscsi_host_os_type = अणु
	.attr = अणु
		 .name = "os_type",
		 .mode = S_IRUGO,
		 पूर्ण,
	.show = show_host_os_type,
पूर्ण;

अटल sमाप_प्रकार show_host_config(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस 0;
पूर्ण

अटल काष्ठा device_attribute ibmvscsi_host_config = अणु
	.attr = अणु
		.name = "config",
		.mode = S_IRUGO,
		पूर्ण,
	.show = show_host_config,
पूर्ण;

अटल पूर्णांक ibmvscsi_host_reset(काष्ठा Scsi_Host *shost, पूर्णांक reset_type)
अणु
	काष्ठा ibmvscsi_host_data *hostdata = shost_priv(shost);

	dev_info(hostdata->dev, "Initiating adapter reset!\n");
	ibmvscsi_reset_host(hostdata);

	वापस 0;
पूर्ण

अटल काष्ठा device_attribute *ibmvscsi_attrs[] = अणु
	&ibmvscsi_host_vhost_loc,
	&ibmvscsi_host_vhost_name,
	&ibmvscsi_host_srp_version,
	&ibmvscsi_host_partition_name,
	&ibmvscsi_host_partition_number,
	&ibmvscsi_host_mad_version,
	&ibmvscsi_host_os_type,
	&ibmvscsi_host_config,
	शून्य
पूर्ण;

/* ------------------------------------------------------------
 * SCSI driver registration
 */
अटल काष्ठा scsi_host_ढाँचा driver_ढाँचा = अणु
	.module = THIS_MODULE,
	.name = "IBM POWER Virtual SCSI Adapter " IBMVSCSI_VERSION,
	.proc_name = "ibmvscsi",
	.queuecommand = ibmvscsi_queuecommand,
	.eh_समयd_out = srp_समयd_out,
	.eh_पात_handler = ibmvscsi_eh_पात_handler,
	.eh_device_reset_handler = ibmvscsi_eh_device_reset_handler,
	.eh_host_reset_handler = ibmvscsi_eh_host_reset_handler,
	.slave_configure = ibmvscsi_slave_configure,
	.change_queue_depth = ibmvscsi_change_queue_depth,
	.host_reset = ibmvscsi_host_reset,
	.cmd_per_lun = IBMVSCSI_CMDS_PER_LUN_DEFAULT,
	.can_queue = IBMVSCSI_MAX_REQUESTS_DEFAULT,
	.this_id = -1,
	.sg_tablesize = SG_ALL,
	.shost_attrs = ibmvscsi_attrs,
पूर्ण;

/**
 * ibmvscsi_get_desired_dma - Calculate IO memory desired by the driver
 *
 * @vdev: काष्ठा vio_dev क्रम the device whose desired IO mem is to be वापसed
 *
 * Return value:
 *	Number of bytes of IO data the driver will need to perक्रमm well.
 */
अटल अचिन्हित दीर्घ ibmvscsi_get_desired_dma(काष्ठा vio_dev *vdev)
अणु
	/* iu_storage data allocated in initialize_event_pool */
	अचिन्हित दीर्घ desired_io = max_events * माप(जोड़ viosrp_iu);

	/* add io space क्रम sg data */
	desired_io += (IBMVSCSI_MAX_SECTORS_DEFAULT * 512 *
	                     IBMVSCSI_CMDS_PER_LUN_DEFAULT);

	वापस desired_io;
पूर्ण

अटल व्योम ibmvscsi_करो_work(काष्ठा ibmvscsi_host_data *hostdata)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक rc;
	अक्षर *action = "reset";

	spin_lock_irqsave(hostdata->host->host_lock, flags);
	चयन (hostdata->action) अणु
	हाल IBMVSCSI_HOST_ACTION_UNBLOCK:
		rc = 0;
		अवरोध;
	हाल IBMVSCSI_HOST_ACTION_RESET:
		spin_unlock_irqrestore(hostdata->host->host_lock, flags);
		rc = ibmvscsi_reset_crq_queue(&hostdata->queue, hostdata);
		spin_lock_irqsave(hostdata->host->host_lock, flags);
		अगर (!rc)
			rc = ibmvscsi_send_crq(hostdata, 0xC001000000000000LL, 0);
		vio_enable_पूर्णांकerrupts(to_vio_dev(hostdata->dev));
		अवरोध;
	हाल IBMVSCSI_HOST_ACTION_REENABLE:
		action = "enable";
		spin_unlock_irqrestore(hostdata->host->host_lock, flags);
		rc = ibmvscsi_reenable_crq_queue(&hostdata->queue, hostdata);
		spin_lock_irqsave(hostdata->host->host_lock, flags);
		अगर (!rc)
			rc = ibmvscsi_send_crq(hostdata, 0xC001000000000000LL, 0);
		अवरोध;
	हाल IBMVSCSI_HOST_ACTION_NONE:
	शेष:
		spin_unlock_irqrestore(hostdata->host->host_lock, flags);
		वापस;
	पूर्ण

	hostdata->action = IBMVSCSI_HOST_ACTION_NONE;
	spin_unlock_irqrestore(hostdata->host->host_lock, flags);

	अगर (rc) अणु
		ibmvscsi_set_request_limit(hostdata, -1);
		dev_err(hostdata->dev, "error after %s\n", action);
	पूर्ण

	scsi_unblock_requests(hostdata->host);
पूर्ण

अटल पूर्णांक __ibmvscsi_work_to_करो(काष्ठा ibmvscsi_host_data *hostdata)
अणु
	अगर (kthपढ़ो_should_stop())
		वापस 1;
	चयन (hostdata->action) अणु
	हाल IBMVSCSI_HOST_ACTION_NONE:
		वापस 0;
	हाल IBMVSCSI_HOST_ACTION_RESET:
	हाल IBMVSCSI_HOST_ACTION_REENABLE:
	हाल IBMVSCSI_HOST_ACTION_UNBLOCK:
	शेष:
		अवरोध;
	पूर्ण

	वापस 1;
पूर्ण

अटल पूर्णांक ibmvscsi_work_to_करो(काष्ठा ibmvscsi_host_data *hostdata)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक rc;

	spin_lock_irqsave(hostdata->host->host_lock, flags);
	rc = __ibmvscsi_work_to_करो(hostdata);
	spin_unlock_irqrestore(hostdata->host->host_lock, flags);

	वापस rc;
पूर्ण

अटल पूर्णांक ibmvscsi_work(व्योम *data)
अणु
	काष्ठा ibmvscsi_host_data *hostdata = data;
	पूर्णांक rc;

	set_user_nice(current, MIN_NICE);

	जबतक (1) अणु
		rc = रुको_event_पूर्णांकerruptible(hostdata->work_रुको_q,
					      ibmvscsi_work_to_करो(hostdata));

		BUG_ON(rc);

		अगर (kthपढ़ो_should_stop())
			अवरोध;

		ibmvscsi_करो_work(hostdata);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Called by bus code क्रम each adapter
 */
अटल पूर्णांक ibmvscsi_probe(काष्ठा vio_dev *vdev, स्थिर काष्ठा vio_device_id *id)
अणु
	काष्ठा ibmvscsi_host_data *hostdata;
	काष्ठा Scsi_Host *host;
	काष्ठा device *dev = &vdev->dev;
	काष्ठा srp_rport_identअगरiers ids;
	काष्ठा srp_rport *rport;
	अचिन्हित दीर्घ रुको_चयन = 0;
	पूर्णांक rc;

	dev_set_drvdata(&vdev->dev, शून्य);

	host = scsi_host_alloc(&driver_ढाँचा, माप(*hostdata));
	अगर (!host) अणु
		dev_err(&vdev->dev, "couldn't allocate host data\n");
		जाओ scsi_host_alloc_failed;
	पूर्ण

	host->transportt = ibmvscsi_transport_ढाँचा;
	hostdata = shost_priv(host);
	स_रखो(hostdata, 0x00, माप(*hostdata));
	INIT_LIST_HEAD(&hostdata->sent);
	init_रुकोqueue_head(&hostdata->work_रुको_q);
	hostdata->host = host;
	hostdata->dev = dev;
	ibmvscsi_set_request_limit(hostdata, -1);
	hostdata->host->max_sectors = IBMVSCSI_MAX_SECTORS_DEFAULT;

	अगर (map_persist_bufs(hostdata)) अणु
		dev_err(&vdev->dev, "couldn't map persistent buffers\n");
		जाओ persist_bufs_failed;
	पूर्ण

	hostdata->work_thपढ़ो = kthपढ़ो_run(ibmvscsi_work, hostdata, "%s_%d",
					    "ibmvscsi", host->host_no);

	अगर (IS_ERR(hostdata->work_thपढ़ो)) अणु
		dev_err(&vdev->dev, "couldn't initialize kthread. rc=%ld\n",
			PTR_ERR(hostdata->work_thपढ़ो));
		जाओ init_crq_failed;
	पूर्ण

	rc = ibmvscsi_init_crq_queue(&hostdata->queue, hostdata, max_events);
	अगर (rc != 0 && rc != H_RESOURCE) अणु
		dev_err(&vdev->dev, "couldn't initialize crq. rc=%d\n", rc);
		जाओ समाप्त_kthपढ़ो;
	पूर्ण
	अगर (initialize_event_pool(&hostdata->pool, max_events, hostdata) != 0) अणु
		dev_err(&vdev->dev, "couldn't initialize event pool\n");
		जाओ init_pool_failed;
	पूर्ण

	host->max_lun = IBMVSCSI_MAX_LUN;
	host->max_id = max_id;
	host->max_channel = max_channel;
	host->max_cmd_len = 16;

	dev_info(dev,
		 "Maximum ID: %d Maximum LUN: %llu Maximum Channel: %d\n",
		 host->max_id, host->max_lun, host->max_channel);

	अगर (scsi_add_host(hostdata->host, hostdata->dev))
		जाओ add_host_failed;

	/* we करोn't have a proper target_port_id so let's use the fake one */
	स_नकल(ids.port_id, hostdata->madapter_info.partition_name,
	       माप(ids.port_id));
	ids.roles = SRP_RPORT_ROLE_TARGET;
	rport = srp_rport_add(host, &ids);
	अगर (IS_ERR(rport))
		जाओ add_srp_port_failed;

	/* Try to send an initialization message.  Note that this is allowed
	 * to fail अगर the other end is not acive.  In that हाल we करोn't
	 * want to scan
	 */
	अगर (ibmvscsi_send_crq(hostdata, 0xC001000000000000LL, 0) == 0
	    || rc == H_RESOURCE) अणु
		/*
		 * Wait around max init_समयout secs क्रम the adapter to finish
		 * initializing. When we are करोne initializing, we will have a
		 * valid request_limit.  We करोn't want Linux scanning beक्रमe
		 * we are पढ़ोy.
		 */
		क्रम (रुको_चयन = jअगरfies + (init_समयout * HZ);
		     समय_beक्रमe(jअगरfies, रुको_चयन) &&
		     atomic_पढ़ो(&hostdata->request_limit) < 2;) अणु

			msleep(10);
		पूर्ण

		/* अगर we now have a valid request_limit, initiate a scan */
		अगर (atomic_पढ़ो(&hostdata->request_limit) > 0)
			scsi_scan_host(host);
	पूर्ण

	dev_set_drvdata(&vdev->dev, hostdata);
	spin_lock(&ibmvscsi_driver_lock);
	list_add_tail(&hostdata->host_list, &ibmvscsi_head);
	spin_unlock(&ibmvscsi_driver_lock);
	वापस 0;

      add_srp_port_failed:
	scsi_हटाओ_host(hostdata->host);
      add_host_failed:
	release_event_pool(&hostdata->pool, hostdata);
      init_pool_failed:
	ibmvscsi_release_crq_queue(&hostdata->queue, hostdata, max_events);
      समाप्त_kthपढ़ो:
      kthपढ़ो_stop(hostdata->work_thपढ़ो);
      init_crq_failed:
	unmap_persist_bufs(hostdata);
      persist_bufs_failed:
	scsi_host_put(host);
      scsi_host_alloc_failed:
	वापस -1;
पूर्ण

अटल व्योम ibmvscsi_हटाओ(काष्ठा vio_dev *vdev)
अणु
	काष्ठा ibmvscsi_host_data *hostdata = dev_get_drvdata(&vdev->dev);

	srp_हटाओ_host(hostdata->host);
	scsi_हटाओ_host(hostdata->host);

	purge_requests(hostdata, DID_ERROR);
	release_event_pool(&hostdata->pool, hostdata);

	ibmvscsi_release_crq_queue(&hostdata->queue, hostdata,
					max_events);

	kthपढ़ो_stop(hostdata->work_thपढ़ो);
	unmap_persist_bufs(hostdata);

	spin_lock(&ibmvscsi_driver_lock);
	list_del(&hostdata->host_list);
	spin_unlock(&ibmvscsi_driver_lock);

	scsi_host_put(hostdata->host);
पूर्ण

/**
 * ibmvscsi_resume: Resume from suspend
 * @dev:	device काष्ठा
 *
 * We may have lost an पूर्णांकerrupt across suspend/resume, so kick the
 * पूर्णांकerrupt handler
 */
अटल पूर्णांक ibmvscsi_resume(काष्ठा device *dev)
अणु
	काष्ठा ibmvscsi_host_data *hostdata = dev_get_drvdata(dev);
	vio_disable_पूर्णांकerrupts(to_vio_dev(hostdata->dev));
	tasklet_schedule(&hostdata->srp_task);

	वापस 0;
पूर्ण

/*
 * ibmvscsi_device_table: Used by vio.c to match devices in the device tree we 
 * support.
 */
अटल स्थिर काष्ठा vio_device_id ibmvscsi_device_table[] = अणु
	अणु"vscsi", "IBM,v-scsi"पूर्ण,
	अणु "", "" पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(vio, ibmvscsi_device_table);

अटल स्थिर काष्ठा dev_pm_ops ibmvscsi_pm_ops = अणु
	.resume = ibmvscsi_resume
पूर्ण;

अटल काष्ठा vio_driver ibmvscsi_driver = अणु
	.id_table = ibmvscsi_device_table,
	.probe = ibmvscsi_probe,
	.हटाओ = ibmvscsi_हटाओ,
	.get_desired_dma = ibmvscsi_get_desired_dma,
	.name = "ibmvscsi",
	.pm = &ibmvscsi_pm_ops,
पूर्ण;

अटल काष्ठा srp_function_ढाँचा ibmvscsi_transport_functions = अणु
पूर्ण;

अटल पूर्णांक __init ibmvscsi_module_init(व्योम)
अणु
	पूर्णांक ret;

	/* Ensure we have two requests to करो error recovery */
	driver_ढाँचा.can_queue = max_requests;
	max_events = max_requests + 2;

	अगर (!firmware_has_feature(FW_FEATURE_VIO))
		वापस -ENODEV;

	ibmvscsi_transport_ढाँचा =
		srp_attach_transport(&ibmvscsi_transport_functions);
	अगर (!ibmvscsi_transport_ढाँचा)
		वापस -ENOMEM;

	ret = vio_रेजिस्टर_driver(&ibmvscsi_driver);
	अगर (ret)
		srp_release_transport(ibmvscsi_transport_ढाँचा);
	वापस ret;
पूर्ण

अटल व्योम __निकास ibmvscsi_module_निकास(व्योम)
अणु
	vio_unरेजिस्टर_driver(&ibmvscsi_driver);
	srp_release_transport(ibmvscsi_transport_ढाँचा);
पूर्ण

module_init(ibmvscsi_module_init);
module_निकास(ibmvscsi_module_निकास);
