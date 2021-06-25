<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *	Adaptec AAC series RAID controller driver
 *	(c) Copyright 2001 Red Hat Inc.
 *
 * based on the old aacraid driver that is..
 * Adaptec aacraid device driver क्रम Linux.
 *
 * Copyright (c) 2000-2010 Adaptec, Inc.
 *               2010-2015 PMC-Sierra, Inc. (aacraid@pmc-sierra.com)
 *               2016-2017 Microsemi Corp. (aacraid@microsemi.com)
 *
 * Module Name:
 *  comminit.c
 *
 * Abstract: This supports the initialization of the host adapter commuication पूर्णांकerface.
 *    This is a platक्रमm dependent module क्रम the pci cyclone board.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/types.h>
#समावेश <linux/pci.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/slab.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/delay.h>
#समावेश <linux/completion.h>
#समावेश <linux/mm.h>
#समावेश <scsi/scsi_host.h>
#समावेश <scsi/scsi_device.h>
#समावेश <scsi/scsi_cmnd.h>

#समावेश "aacraid.h"

काष्ठा aac_common aac_config = अणु
	.irq_mod = 1
पूर्ण;

अटल अंतरभूत पूर्णांक aac_is_msix_mode(काष्ठा aac_dev *dev)
अणु
	u32 status = 0;

	अगर (aac_is_src(dev))
		status = src_पढ़ोl(dev, MUnit.OMR);
	वापस (status & AAC_INT_MODE_MSIX);
पूर्ण

अटल अंतरभूत व्योम aac_change_to_पूर्णांकx(काष्ठा aac_dev *dev)
अणु
	aac_src_access_devreg(dev, AAC_DISABLE_MSIX);
	aac_src_access_devreg(dev, AAC_ENABLE_INTX);
पूर्ण

अटल पूर्णांक aac_alloc_comm(काष्ठा aac_dev *dev, व्योम **commaddr, अचिन्हित दीर्घ commsize, अचिन्हित दीर्घ commalign)
अणु
	अचिन्हित अक्षर *base;
	अचिन्हित दीर्घ size, align;
	स्थिर अचिन्हित दीर्घ fibsize = dev->max_fib_size;
	स्थिर अचिन्हित दीर्घ म_लिखोbufsiz = 256;
	अचिन्हित दीर्घ host_rrq_size, aac_init_size;
	जोड़ aac_init *init;
	dma_addr_t phys;
	अचिन्हित दीर्घ aac_max_hostphysmempages;

	अगर ((dev->comm_पूर्णांकerface == AAC_COMM_MESSAGE_TYPE1) ||
		(dev->comm_पूर्णांकerface == AAC_COMM_MESSAGE_TYPE2) ||
		(dev->comm_पूर्णांकerface == AAC_COMM_MESSAGE_TYPE3 &&
		!dev->sa_firmware)) अणु
		host_rrq_size =
			(dev->scsi_host_ptr->can_queue + AAC_NUM_MGT_FIB)
				* माप(u32);
		aac_init_size = माप(जोड़ aac_init);
	पूर्ण अन्यथा अगर (dev->comm_पूर्णांकerface == AAC_COMM_MESSAGE_TYPE3 &&
		dev->sa_firmware) अणु
		host_rrq_size = (dev->scsi_host_ptr->can_queue
			+ AAC_NUM_MGT_FIB) * माप(u32)  * AAC_MAX_MSIX;
		aac_init_size = माप(जोड़ aac_init) +
			(AAC_MAX_HRRQ - 1) * माप(काष्ठा _rrq);
	पूर्ण अन्यथा अणु
		host_rrq_size = 0;
		aac_init_size = माप(जोड़ aac_init);
	पूर्ण
	size = fibsize + aac_init_size + commsize + commalign +
			म_लिखोbufsiz + host_rrq_size;

	base = dma_alloc_coherent(&dev->pdev->dev, size, &phys, GFP_KERNEL);
	अगर (base == शून्य) अणु
		prपूर्णांकk(KERN_ERR "aacraid: unable to create mapping.\n");
		वापस 0;
	पूर्ण

	dev->comm_addr = (व्योम *)base;
	dev->comm_phys = phys;
	dev->comm_size = size;

	अगर ((dev->comm_पूर्णांकerface == AAC_COMM_MESSAGE_TYPE1) ||
	    (dev->comm_पूर्णांकerface == AAC_COMM_MESSAGE_TYPE2) ||
	    (dev->comm_पूर्णांकerface == AAC_COMM_MESSAGE_TYPE3)) अणु
		dev->host_rrq = (u32 *)(base + fibsize);
		dev->host_rrq_pa = phys + fibsize;
		स_रखो(dev->host_rrq, 0, host_rrq_size);
	पूर्ण

	dev->init = (जोड़ aac_init *)(base + fibsize + host_rrq_size);
	dev->init_pa = phys + fibsize + host_rrq_size;

	init = dev->init;

	अगर (dev->comm_पूर्णांकerface == AAC_COMM_MESSAGE_TYPE3) अणु
		पूर्णांक i;
		u64 addr;

		init->r8.init_काष्ठा_revision =
			cpu_to_le32(ADAPTER_INIT_STRUCT_REVISION_8);
		init->r8.init_flags = cpu_to_le32(INITFLAGS_NEW_COMM_SUPPORTED |
					INITFLAGS_DRIVER_USES_UTC_TIME |
					INITFLAGS_DRIVER_SUPPORTS_PM);
		init->r8.init_flags |=
				cpu_to_le32(INITFLAGS_DRIVER_SUPPORTS_HBA_MODE);
		init->r8.rr_queue_count = cpu_to_le32(dev->max_msix);
		init->r8.max_io_size =
			cpu_to_le32(dev->scsi_host_ptr->max_sectors << 9);
		init->r8.max_num_aअगर = init->r8.reserved1 =
			init->r8.reserved2 = 0;

		क्रम (i = 0; i < dev->max_msix; i++) अणु
			addr = (u64)dev->host_rrq_pa + dev->vector_cap * i *
					माप(u32);
			init->r8.rrq[i].host_addr_high = cpu_to_le32(
						upper_32_bits(addr));
			init->r8.rrq[i].host_addr_low = cpu_to_le32(
						lower_32_bits(addr));
			init->r8.rrq[i].msix_id = i;
			init->r8.rrq[i].element_count = cpu_to_le16(
					(u16)dev->vector_cap);
			init->r8.rrq[i].comp_thresh =
					init->r8.rrq[i].unused = 0;
		पूर्ण

		pr_warn("aacraid: Comm Interface type3 enabled\n");
	पूर्ण अन्यथा अणु
		init->r7.init_काष्ठा_revision =
			cpu_to_le32(ADAPTER_INIT_STRUCT_REVISION);
		अगर (dev->max_fib_size != माप(काष्ठा hw_fib))
			init->r7.init_काष्ठा_revision =
				cpu_to_le32(ADAPTER_INIT_STRUCT_REVISION_4);
		init->r7.no_of_msix_vectors = cpu_to_le32(SA_MINIPORT_REVISION);
		init->r7.fsrev = cpu_to_le32(dev->fsrev);

		/*
		 *	Adapter Fibs are the first thing allocated so that they
		 *	start page aligned
		 */
		dev->aअगर_base_va = (काष्ठा hw_fib *)base;

		init->r7.adapter_fibs_भव_address = 0;
		init->r7.adapter_fibs_physical_address = cpu_to_le32((u32)phys);
		init->r7.adapter_fibs_size = cpu_to_le32(fibsize);
		init->r7.adapter_fib_align = cpu_to_le32(माप(काष्ठा hw_fib));

		/*
		 * number of 4k pages of host physical memory. The aacraid fw
		 * needs this number to be less than 4gb worth of pages. New
		 * firmware करोesn't have any issues with the mapping प्रणाली, but
		 * older Firmware did, and had *troubles* dealing with the math
		 * overloading past 32 bits, thus we must limit this field.
		 */
		aac_max_hostphysmempages =
				dma_get_required_mask(&dev->pdev->dev) >> 12;
		अगर (aac_max_hostphysmempages < AAC_MAX_HOSTPHYSMEMPAGES)
			init->r7.host_phys_mem_pages =
					cpu_to_le32(aac_max_hostphysmempages);
		अन्यथा
			init->r7.host_phys_mem_pages =
					cpu_to_le32(AAC_MAX_HOSTPHYSMEMPAGES);

		init->r7.init_flags =
			cpu_to_le32(INITFLAGS_DRIVER_USES_UTC_TIME |
			INITFLAGS_DRIVER_SUPPORTS_PM);
		init->r7.max_io_commands =
			cpu_to_le32(dev->scsi_host_ptr->can_queue +
					AAC_NUM_MGT_FIB);
		init->r7.max_io_size =
			cpu_to_le32(dev->scsi_host_ptr->max_sectors << 9);
		init->r7.max_fib_size = cpu_to_le32(dev->max_fib_size);
		init->r7.max_num_aअगर = cpu_to_le32(dev->max_num_aअगर);

		अगर (dev->comm_पूर्णांकerface == AAC_COMM_MESSAGE) अणु
			init->r7.init_flags |=
				cpu_to_le32(INITFLAGS_NEW_COMM_SUPPORTED);
			pr_warn("aacraid: Comm Interface enabled\n");
		पूर्ण अन्यथा अगर (dev->comm_पूर्णांकerface == AAC_COMM_MESSAGE_TYPE1) अणु
			init->r7.init_काष्ठा_revision =
				cpu_to_le32(ADAPTER_INIT_STRUCT_REVISION_6);
			init->r7.init_flags |=
				cpu_to_le32(INITFLAGS_NEW_COMM_SUPPORTED |
				INITFLAGS_NEW_COMM_TYPE1_SUPPORTED |
				INITFLAGS_FAST_JBOD_SUPPORTED);
			init->r7.host_rrq_addr_high =
				cpu_to_le32(upper_32_bits(dev->host_rrq_pa));
			init->r7.host_rrq_addr_low =
				cpu_to_le32(lower_32_bits(dev->host_rrq_pa));
			pr_warn("aacraid: Comm Interface type1 enabled\n");
		पूर्ण अन्यथा अगर (dev->comm_पूर्णांकerface == AAC_COMM_MESSAGE_TYPE2) अणु
			init->r7.init_काष्ठा_revision =
				cpu_to_le32(ADAPTER_INIT_STRUCT_REVISION_7);
			init->r7.init_flags |=
				cpu_to_le32(INITFLAGS_NEW_COMM_SUPPORTED |
				INITFLAGS_NEW_COMM_TYPE2_SUPPORTED |
				INITFLAGS_FAST_JBOD_SUPPORTED);
			init->r7.host_rrq_addr_high =
				cpu_to_le32(upper_32_bits(dev->host_rrq_pa));
			init->r7.host_rrq_addr_low =
				cpu_to_le32(lower_32_bits(dev->host_rrq_pa));
			init->r7.no_of_msix_vectors =
				cpu_to_le32(dev->max_msix);
			/* must be the COMM_PREFERRED_SETTINGS values */
			pr_warn("aacraid: Comm Interface type2 enabled\n");
		पूर्ण
	पूर्ण

	/*
	 * Increment the base address by the amount alपढ़ोy used
	 */
	base = base + fibsize + host_rrq_size + aac_init_size;
	phys = (dma_addr_t)((uदीर्घ)phys + fibsize + host_rrq_size +
			aac_init_size);

	/*
	 *	Align the beginning of Headers to commalign
	 */
	align = (commalign - ((uपूर्णांकptr_t)(base) & (commalign - 1)));
	base = base + align;
	phys = phys + align;
	/*
	 *	Fill in addresses of the Comm Area Headers and Queues
	 */
	*commaddr = base;
	अगर (dev->comm_पूर्णांकerface != AAC_COMM_MESSAGE_TYPE3)
		init->r7.comm_header_address = cpu_to_le32((u32)phys);
	/*
	 *	Increment the base address by the size of the CommArea
	 */
	base = base + commsize;
	phys = phys + commsize;
	/*
	 *	 Place the Prपूर्णांकf buffer area after the Fast I/O comm area.
	 */
	dev->म_लिखोbuf = (व्योम *)base;
	अगर (dev->comm_पूर्णांकerface != AAC_COMM_MESSAGE_TYPE3) अणु
		init->r7.म_लिखोbuf = cpu_to_le32(phys);
		init->r7.म_लिखोbufsiz = cpu_to_le32(म_लिखोbufsiz);
	पूर्ण
	स_रखो(base, 0, म_लिखोbufsiz);
	वापस 1;
पूर्ण

अटल व्योम aac_queue_init(काष्ठा aac_dev * dev, काष्ठा aac_queue * q, u32 *mem, पूर्णांक qsize)
अणु
	atomic_set(&q->numpending, 0);
	q->dev = dev;
	init_रुकोqueue_head(&q->cmdपढ़ोy);
	INIT_LIST_HEAD(&q->cmdq);
	init_रुकोqueue_head(&q->qfull);
	spin_lock_init(&q->lockdata);
	q->lock = &q->lockdata;
	q->headers.producer = (__le32 *)mem;
	q->headers.consumer = (__le32 *)(mem+1);
	*(q->headers.producer) = cpu_to_le32(qsize);
	*(q->headers.consumer) = cpu_to_le32(qsize);
	q->entries = qsize;
पूर्ण

अटल bool रुको_क्रम_io_iter(काष्ठा scsi_cmnd *cmd, व्योम *data, bool rsvd)
अणु
	पूर्णांक *active = data;

	अगर (cmd->SCp.phase == AAC_OWNER_FIRMWARE)
		*active = *active + 1;
	वापस true;
पूर्ण
अटल व्योम aac_रुको_क्रम_io_completion(काष्ठा aac_dev *aac)
अणु
	पूर्णांक i = 0, active;

	क्रम (i = 60; i; --i) अणु

		active = 0;
		scsi_host_busy_iter(aac->scsi_host_ptr,
				    रुको_क्रम_io_iter, &active);
		/*
		 * We can निकास If all the commands are complete
		 */
		अगर (active == 0)
			अवरोध;
		dev_info(&aac->pdev->dev,
			 "Wait for %d commands to complete\n", active);
		ssleep(1);
	पूर्ण
	अगर (active)
		dev_err(&aac->pdev->dev,
			"%d outstanding commands during shutdown\n", active);
पूर्ण

/**
 *	aac_send_shutकरोwn		-	shutकरोwn an adapter
 *	@dev: Adapter to shutकरोwn
 *
 *	This routine will send a VM_CloseAll (shutकरोwn) request to the adapter.
 */

पूर्णांक aac_send_shutकरोwn(काष्ठा aac_dev * dev)
अणु
	काष्ठा fib * fibctx;
	काष्ठा aac_बंद *cmd;
	पूर्णांक status = 0;

	अगर (aac_adapter_check_health(dev))
		वापस status;

	अगर (!dev->adapter_shutकरोwn) अणु
		mutex_lock(&dev->ioctl_mutex);
		dev->adapter_shutकरोwn = 1;
		mutex_unlock(&dev->ioctl_mutex);
	पूर्ण

	aac_रुको_क्रम_io_completion(dev);

	fibctx = aac_fib_alloc(dev);
	अगर (!fibctx)
		वापस -ENOMEM;
	aac_fib_init(fibctx);

	cmd = (काष्ठा aac_बंद *) fib_data(fibctx);
	cmd->command = cpu_to_le32(VM_CloseAll);
	cmd->cid = cpu_to_le32(0xfffffffe);

	status = aac_fib_send(ContainerCommand,
			  fibctx,
			  माप(काष्ठा aac_बंद),
			  FsaNormal,
			  -2 /* Timeout silently */, 1,
			  शून्य, शून्य);

	अगर (status >= 0)
		aac_fib_complete(fibctx);
	/* FIB should be मुक्तd only after getting the response from the F/W */
	अगर (status != -ERESTARTSYS)
		aac_fib_मुक्त(fibctx);
	अगर (aac_is_src(dev) &&
	     dev->msi_enabled)
		aac_set_पूर्णांकx_mode(dev);
	वापस status;
पूर्ण

/**
 *	aac_comm_init	-	Initialise FSA data काष्ठाures
 *	@dev:	Adapter to initialise
 *
 *	Initializes the data काष्ठाures that are required क्रम the FSA commuication
 *	पूर्णांकerface to operate. 
 *	Returns
 *		1 - अगर we were able to init the commuication पूर्णांकerface.
 *		0 - If there were errors initing. This is a fatal error.
 */
 
अटल पूर्णांक aac_comm_init(काष्ठा aac_dev * dev)
अणु
	अचिन्हित दीर्घ hdrsize = (माप(u32) * NUMBER_OF_COMM_QUEUES) * 2;
	अचिन्हित दीर्घ queuesize = माप(काष्ठा aac_entry) * TOTAL_QUEUE_ENTRIES;
	u32 *headers;
	काष्ठा aac_entry * queues;
	अचिन्हित दीर्घ size;
	काष्ठा aac_queue_block * comm = dev->queues;
	/*
	 *	Now allocate and initialize the zone काष्ठाures used as our 
	 *	pool of FIB context records.  The size of the zone is based
	 *	on the प्रणाली memory size.  We also initialize the mutex used
	 *	to protect the zone.
	 */
	spin_lock_init(&dev->fib_lock);

	/*
	 *	Allocate the physically contiguous space क्रम the commuication
	 *	queue headers. 
	 */

	size = hdrsize + queuesize;

	अगर (!aac_alloc_comm(dev, (व्योम * *)&headers, size, QUEUE_ALIGNMENT))
		वापस -ENOMEM;

	queues = (काष्ठा aac_entry *)(((uदीर्घ)headers) + hdrsize);

	/* Adapter to Host normal priority Command queue */ 
	comm->queue[HostNormCmdQueue].base = queues;
	aac_queue_init(dev, &comm->queue[HostNormCmdQueue], headers, HOST_NORM_CMD_ENTRIES);
	queues += HOST_NORM_CMD_ENTRIES;
	headers += 2;

	/* Adapter to Host high priority command queue */
	comm->queue[HostHighCmdQueue].base = queues;
	aac_queue_init(dev, &comm->queue[HostHighCmdQueue], headers, HOST_HIGH_CMD_ENTRIES);
    
	queues += HOST_HIGH_CMD_ENTRIES;
	headers +=2;

	/* Host to adapter normal priority command queue */
	comm->queue[AdapNormCmdQueue].base = queues;
	aac_queue_init(dev, &comm->queue[AdapNormCmdQueue], headers, ADAP_NORM_CMD_ENTRIES);
    
	queues += ADAP_NORM_CMD_ENTRIES;
	headers += 2;

	/* host to adapter high priority command queue */
	comm->queue[AdapHighCmdQueue].base = queues;
	aac_queue_init(dev, &comm->queue[AdapHighCmdQueue], headers, ADAP_HIGH_CMD_ENTRIES);
    
	queues += ADAP_HIGH_CMD_ENTRIES;
	headers += 2;

	/* adapter to host normal priority response queue */
	comm->queue[HostNormRespQueue].base = queues;
	aac_queue_init(dev, &comm->queue[HostNormRespQueue], headers, HOST_NORM_RESP_ENTRIES);
	queues += HOST_NORM_RESP_ENTRIES;
	headers += 2;

	/* adapter to host high priority response queue */
	comm->queue[HostHighRespQueue].base = queues;
	aac_queue_init(dev, &comm->queue[HostHighRespQueue], headers, HOST_HIGH_RESP_ENTRIES);
   
	queues += HOST_HIGH_RESP_ENTRIES;
	headers += 2;

	/* host to adapter normal priority response queue */
	comm->queue[AdapNormRespQueue].base = queues;
	aac_queue_init(dev, &comm->queue[AdapNormRespQueue], headers, ADAP_NORM_RESP_ENTRIES);

	queues += ADAP_NORM_RESP_ENTRIES;
	headers += 2;
	
	/* host to adapter high priority response queue */ 
	comm->queue[AdapHighRespQueue].base = queues;
	aac_queue_init(dev, &comm->queue[AdapHighRespQueue], headers, ADAP_HIGH_RESP_ENTRIES);

	comm->queue[AdapNormCmdQueue].lock = comm->queue[HostNormRespQueue].lock;
	comm->queue[AdapHighCmdQueue].lock = comm->queue[HostHighRespQueue].lock;
	comm->queue[AdapNormRespQueue].lock = comm->queue[HostNormCmdQueue].lock;
	comm->queue[AdapHighRespQueue].lock = comm->queue[HostHighCmdQueue].lock;

	वापस 0;
पूर्ण

व्योम aac_define_पूर्णांक_mode(काष्ठा aac_dev *dev)
अणु
	पूर्णांक i, msi_count, min_msix;

	msi_count = i = 0;
	/* max. vectors from GET_COMM_PREFERRED_SETTINGS */
	अगर (dev->max_msix == 0 ||
	    dev->pdev->device == PMC_DEVICE_S6 ||
	    dev->sync_mode) अणु
		dev->max_msix = 1;
		dev->vector_cap =
			dev->scsi_host_ptr->can_queue +
			AAC_NUM_MGT_FIB;
		वापस;
	पूर्ण

	/* Don't bother allocating more MSI-X vectors than cpus */
	msi_count = min(dev->max_msix,
		(अचिन्हित पूर्णांक)num_online_cpus());

	dev->max_msix = msi_count;

	अगर (msi_count > AAC_MAX_MSIX)
		msi_count = AAC_MAX_MSIX;

	अगर (msi_count > 1 &&
	    pci_find_capability(dev->pdev, PCI_CAP_ID_MSIX)) अणु
		min_msix = 2;
		i = pci_alloc_irq_vectors(dev->pdev,
					  min_msix, msi_count,
					  PCI_IRQ_MSIX | PCI_IRQ_AFFINITY);
		अगर (i > 0) अणु
			dev->msi_enabled = 1;
			msi_count = i;
		पूर्ण अन्यथा अणु
			dev->msi_enabled = 0;
			dev_err(&dev->pdev->dev,
			"MSIX not supported!! Will try INTX 0x%x.\n", i);
		पूर्ण
	पूर्ण

	अगर (!dev->msi_enabled)
		dev->max_msix = msi_count = 1;
	अन्यथा अणु
		अगर (dev->max_msix > msi_count)
			dev->max_msix = msi_count;
	पूर्ण
	अगर (dev->comm_पूर्णांकerface == AAC_COMM_MESSAGE_TYPE3 && dev->sa_firmware)
		dev->vector_cap = dev->scsi_host_ptr->can_queue +
				AAC_NUM_MGT_FIB;
	अन्यथा
		dev->vector_cap = (dev->scsi_host_ptr->can_queue +
				AAC_NUM_MGT_FIB) / msi_count;

पूर्ण
काष्ठा aac_dev *aac_init_adapter(काष्ठा aac_dev *dev)
अणु
	u32 status[5];
	काष्ठा Scsi_Host * host = dev->scsi_host_ptr;
	बाह्य पूर्णांक aac_sync_mode;

	/*
	 *	Check the preferred comm settings, शेषs from ढाँचा.
	 */
	dev->management_fib_count = 0;
	spin_lock_init(&dev->manage_lock);
	spin_lock_init(&dev->sync_lock);
	spin_lock_init(&dev->iq_lock);
	dev->max_fib_size = माप(काष्ठा hw_fib);
	dev->sg_tablesize = host->sg_tablesize = (dev->max_fib_size
		- माप(काष्ठा aac_fibhdr)
		- माप(काष्ठा aac_ग_लिखो) + माप(काष्ठा sgentry))
			/ माप(काष्ठा sgentry);
	dev->comm_पूर्णांकerface = AAC_COMM_PRODUCER;
	dev->raw_io_पूर्णांकerface = dev->raw_io_64 = 0;


	/*
	 * Enable INTX mode, अगर not करोne alपढ़ोy Enabled
	 */
	अगर (aac_is_msix_mode(dev)) अणु
		aac_change_to_पूर्णांकx(dev);
		dev_info(&dev->pdev->dev, "Changed firmware to INTX mode");
	पूर्ण

	अगर ((!aac_adapter_sync_cmd(dev, GET_ADAPTER_PROPERTIES,
		0, 0, 0, 0, 0, 0,
		status+0, status+1, status+2, status+3, status+4)) &&
		(status[0] == 0x00000001)) अणु
		dev->करोorbell_mask = status[3];
		अगर (status[1] & AAC_OPT_NEW_COMM_64)
			dev->raw_io_64 = 1;
		dev->sync_mode = aac_sync_mode;
		अगर (dev->a_ops.adapter_comm &&
		    (status[1] & AAC_OPT_NEW_COMM)) अणु
			dev->comm_पूर्णांकerface = AAC_COMM_MESSAGE;
			dev->raw_io_पूर्णांकerface = 1;
			अगर ((status[1] & AAC_OPT_NEW_COMM_TYPE1)) अणु
				/* driver supports TYPE1 (Tupelo) */
				dev->comm_पूर्णांकerface = AAC_COMM_MESSAGE_TYPE1;
			पूर्ण अन्यथा अगर (status[1] & AAC_OPT_NEW_COMM_TYPE2) अणु
				/* driver supports TYPE2 (Denali, Yosemite) */
				dev->comm_पूर्णांकerface = AAC_COMM_MESSAGE_TYPE2;
			पूर्ण अन्यथा अगर (status[1] & AAC_OPT_NEW_COMM_TYPE3) अणु
				/* driver supports TYPE3 (Yosemite, Thor) */
				dev->comm_पूर्णांकerface = AAC_COMM_MESSAGE_TYPE3;
			पूर्ण अन्यथा अगर (status[1] & AAC_OPT_NEW_COMM_TYPE4) अणु
				/* not supported TYPE - चयन to sync. mode */
				dev->comm_पूर्णांकerface = AAC_COMM_MESSAGE_TYPE2;
				dev->sync_mode = 1;
			पूर्ण
		पूर्ण
		अगर ((status[1] & le32_to_cpu(AAC_OPT_EXTENDED)) &&
			(status[4] & le32_to_cpu(AAC_EXTOPT_SA_FIRMWARE)))
			dev->sa_firmware = 1;
		अन्यथा
			dev->sa_firmware = 0;

		अगर (status[4] & le32_to_cpu(AAC_EXTOPT_SOFT_RESET))
			dev->soft_reset_support = 1;
		अन्यथा
			dev->soft_reset_support = 0;

		अगर ((dev->comm_पूर्णांकerface == AAC_COMM_MESSAGE) &&
		    (status[2] > dev->base_size)) अणु
			aac_adapter_ioremap(dev, 0);
			dev->base_size = status[2];
			अगर (aac_adapter_ioremap(dev, status[2])) अणु
				/* remap failed, go back ... */
				dev->comm_पूर्णांकerface = AAC_COMM_PRODUCER;
				अगर (aac_adapter_ioremap(dev, AAC_MIN_FOOTPRINT_SIZE)) अणु
					prपूर्णांकk(KERN_WARNING
					  "aacraid: unable to map adapter.\n");
					वापस शून्य;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
	dev->max_msix = 0;
	dev->msi_enabled = 0;
	dev->adapter_shutकरोwn = 0;
	अगर ((!aac_adapter_sync_cmd(dev, GET_COMM_PREFERRED_SETTINGS,
	  0, 0, 0, 0, 0, 0,
	  status+0, status+1, status+2, status+3, status+4))
	 && (status[0] == 0x00000001)) अणु
		/*
		 *	status[1] >> 16		maximum command size in KB
		 *	status[1] & 0xFFFF	maximum FIB size
		 *	status[2] >> 16		maximum SG elements to driver
		 *	status[2] & 0xFFFF	maximum SG elements from driver
		 *	status[3] & 0xFFFF	maximum number FIBs outstanding
		 */
		host->max_sectors = (status[1] >> 16) << 1;
		/* Multiple of 32 क्रम PMC */
		dev->max_fib_size = status[1] & 0xFFE0;
		host->sg_tablesize = status[2] >> 16;
		dev->sg_tablesize = status[2] & 0xFFFF;
		अगर (aac_is_src(dev)) अणु
			अगर (host->can_queue > (status[3] >> 16) -
					AAC_NUM_MGT_FIB)
				host->can_queue = (status[3] >> 16) -
					AAC_NUM_MGT_FIB;
		पूर्ण अन्यथा अगर (host->can_queue > (status[3] & 0xFFFF) -
				AAC_NUM_MGT_FIB)
			host->can_queue = (status[3] & 0xFFFF) -
				AAC_NUM_MGT_FIB;

		dev->max_num_aअगर = status[4] & 0xFFFF;
	पूर्ण
	अगर (numacb > 0) अणु
		अगर (numacb < host->can_queue)
			host->can_queue = numacb;
		अन्यथा
			pr_warn("numacb=%d ignored\n", numacb);
	पूर्ण

	अगर (aac_is_src(dev))
		aac_define_पूर्णांक_mode(dev);
	/*
	 *	Ok now init the communication subप्रणाली
	 */

	dev->queues = kzalloc(माप(काष्ठा aac_queue_block), GFP_KERNEL);
	अगर (dev->queues == शून्य) अणु
		prपूर्णांकk(KERN_ERR "Error could not allocate comm region.\n");
		वापस शून्य;
	पूर्ण

	अगर (aac_comm_init(dev)<0)अणु
		kमुक्त(dev->queues);
		वापस शून्य;
	पूर्ण
	/*
	 *	Initialize the list of fibs
	 */
	अगर (aac_fib_setup(dev) < 0) अणु
		kमुक्त(dev->queues);
		वापस शून्य;
	पूर्ण
		
	INIT_LIST_HEAD(&dev->fib_list);
	INIT_LIST_HEAD(&dev->sync_fib_list);

	वापस dev;
पूर्ण

