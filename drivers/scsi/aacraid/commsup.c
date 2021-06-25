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
 *		 2016-2017 Microsemi Corp. (aacraid@microsemi.com)
 *
 * Module Name:
 *  commsup.c
 *
 * Abstract: Contain all routines that are required क्रम FSA host/adapter
 *    communication.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/crash_dump.h>
#समावेश <linux/types.h>
#समावेश <linux/sched.h>
#समावेश <linux/pci.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/slab.h>
#समावेश <linux/completion.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/delay.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/bcd.h>
#समावेश <scsi/scsi.h>
#समावेश <scsi/scsi_host.h>
#समावेश <scsi/scsi_device.h>
#समावेश <scsi/scsi_cmnd.h>

#समावेश "aacraid.h"

/**
 *	fib_map_alloc		-	allocate the fib objects
 *	@dev: Adapter to allocate क्रम
 *
 *	Allocate and map the shared PCI space क्रम the FIB blocks used to
 *	talk to the Adaptec firmware.
 */

अटल पूर्णांक fib_map_alloc(काष्ठा aac_dev *dev)
अणु
	अगर (dev->max_fib_size > AAC_MAX_NATIVE_SIZE)
		dev->max_cmd_size = AAC_MAX_NATIVE_SIZE;
	अन्यथा
		dev->max_cmd_size = dev->max_fib_size;
	अगर (dev->max_fib_size < AAC_MAX_NATIVE_SIZE) अणु
		dev->max_cmd_size = AAC_MAX_NATIVE_SIZE;
	पूर्ण अन्यथा अणु
		dev->max_cmd_size = dev->max_fib_size;
	पूर्ण

	dprपूर्णांकk((KERN_INFO
	  "allocate hardware fibs dma_alloc_coherent(%p, %d * (%d + %d), %p)\n",
	  &dev->pdev->dev, dev->max_cmd_size, dev->scsi_host_ptr->can_queue,
	  AAC_NUM_MGT_FIB, &dev->hw_fib_pa));
	dev->hw_fib_va = dma_alloc_coherent(&dev->pdev->dev,
		(dev->max_cmd_size + माप(काष्ठा aac_fib_xporthdr))
		* (dev->scsi_host_ptr->can_queue + AAC_NUM_MGT_FIB) + (ALIGN32 - 1),
		&dev->hw_fib_pa, GFP_KERNEL);
	अगर (dev->hw_fib_va == शून्य)
		वापस -ENOMEM;
	वापस 0;
पूर्ण

/**
 *	aac_fib_map_मुक्त		-	मुक्त the fib objects
 *	@dev: Adapter to मुक्त
 *
 *	Free the PCI mappings and the memory allocated क्रम FIB blocks
 *	on this adapter.
 */

व्योम aac_fib_map_मुक्त(काष्ठा aac_dev *dev)
अणु
	माप_प्रकार alloc_size;
	माप_प्रकार fib_size;
	पूर्णांक num_fibs;

	अगर(!dev->hw_fib_va || !dev->max_cmd_size)
		वापस;

	num_fibs = dev->scsi_host_ptr->can_queue + AAC_NUM_MGT_FIB;
	fib_size = dev->max_fib_size + माप(काष्ठा aac_fib_xporthdr);
	alloc_size = fib_size * num_fibs + ALIGN32 - 1;

	dma_मुक्त_coherent(&dev->pdev->dev, alloc_size, dev->hw_fib_va,
			  dev->hw_fib_pa);

	dev->hw_fib_va = शून्य;
	dev->hw_fib_pa = 0;
पूर्ण

व्योम aac_fib_vector_assign(काष्ठा aac_dev *dev)
अणु
	u32 i = 0;
	u32 vector = 1;
	काष्ठा fib *fibptr = शून्य;

	क्रम (i = 0, fibptr = &dev->fibs[i];
		i < (dev->scsi_host_ptr->can_queue + AAC_NUM_MGT_FIB);
		i++, fibptr++) अणु
		अगर ((dev->max_msix == 1) ||
		  (i > ((dev->scsi_host_ptr->can_queue + AAC_NUM_MGT_FIB - 1)
			- dev->vector_cap))) अणु
			fibptr->vector_no = 0;
		पूर्ण अन्यथा अणु
			fibptr->vector_no = vector;
			vector++;
			अगर (vector == dev->max_msix)
				vector = 1;
		पूर्ण
	पूर्ण
पूर्ण

/**
 *	aac_fib_setup	-	setup the fibs
 *	@dev: Adapter to set up
 *
 *	Allocate the PCI space क्रम the fibs, map it and then initialise the
 *	fib area, the unmapped fib data and also the मुक्त list
 */

पूर्णांक aac_fib_setup(काष्ठा aac_dev * dev)
अणु
	काष्ठा fib *fibptr;
	काष्ठा hw_fib *hw_fib;
	dma_addr_t hw_fib_pa;
	पूर्णांक i;
	u32 max_cmds;

	जबतक (((i = fib_map_alloc(dev)) == -ENOMEM)
	 && (dev->scsi_host_ptr->can_queue > (64 - AAC_NUM_MGT_FIB))) अणु
		max_cmds = (dev->scsi_host_ptr->can_queue+AAC_NUM_MGT_FIB) >> 1;
		dev->scsi_host_ptr->can_queue = max_cmds - AAC_NUM_MGT_FIB;
		अगर (dev->comm_पूर्णांकerface != AAC_COMM_MESSAGE_TYPE3)
			dev->init->r7.max_io_commands = cpu_to_le32(max_cmds);
	पूर्ण
	अगर (i<0)
		वापस -ENOMEM;

	स_रखो(dev->hw_fib_va, 0,
		(dev->max_cmd_size + माप(काष्ठा aac_fib_xporthdr)) *
		(dev->scsi_host_ptr->can_queue + AAC_NUM_MGT_FIB));

	/* 32 byte alignment क्रम PMC */
	hw_fib_pa = (dev->hw_fib_pa + (ALIGN32 - 1)) & ~(ALIGN32 - 1);
	hw_fib    = (काष्ठा hw_fib *)((अचिन्हित अक्षर *)dev->hw_fib_va +
					(hw_fib_pa - dev->hw_fib_pa));

	/* add Xport header */
	hw_fib = (काष्ठा hw_fib *)((अचिन्हित अक्षर *)hw_fib +
		माप(काष्ठा aac_fib_xporthdr));
	hw_fib_pa += माप(काष्ठा aac_fib_xporthdr);

	/*
	 *	Initialise the fibs
	 */
	क्रम (i = 0, fibptr = &dev->fibs[i];
		i < (dev->scsi_host_ptr->can_queue + AAC_NUM_MGT_FIB);
		i++, fibptr++)
	अणु
		fibptr->flags = 0;
		fibptr->size = माप(काष्ठा fib);
		fibptr->dev = dev;
		fibptr->hw_fib_va = hw_fib;
		fibptr->data = (व्योम *) fibptr->hw_fib_va->data;
		fibptr->next = fibptr+1;	/* Forward chain the fibs */
		init_completion(&fibptr->event_रुको);
		spin_lock_init(&fibptr->event_lock);
		hw_fib->header.XferState = cpu_to_le32(0xffffffff);
		hw_fib->header.SenderSize =
			cpu_to_le16(dev->max_fib_size);	/* ?? max_cmd_size */
		fibptr->hw_fib_pa = hw_fib_pa;
		fibptr->hw_sgl_pa = hw_fib_pa +
			दुरत्व(काष्ठा aac_hba_cmd_req, sge[2]);
		/*
		 * one element is क्रम the ptr to the separate sg list,
		 * second element क्रम 32 byte alignment
		 */
		fibptr->hw_error_pa = hw_fib_pa +
			दुरत्व(काष्ठा aac_native_hba, resp.resp_bytes[0]);

		hw_fib = (काष्ठा hw_fib *)((अचिन्हित अक्षर *)hw_fib +
			dev->max_cmd_size + माप(काष्ठा aac_fib_xporthdr));
		hw_fib_pa = hw_fib_pa +
			dev->max_cmd_size + माप(काष्ठा aac_fib_xporthdr);
	पूर्ण

	/*
	 *Assign vector numbers to fibs
	 */
	aac_fib_vector_assign(dev);

	/*
	 *	Add the fib chain to the मुक्त list
	 */
	dev->fibs[dev->scsi_host_ptr->can_queue + AAC_NUM_MGT_FIB - 1].next = शून्य;
	/*
	*	Set 8 fibs aside क्रम management tools
	*/
	dev->मुक्त_fib = &dev->fibs[dev->scsi_host_ptr->can_queue];
	वापस 0;
पूर्ण

/**
 *	aac_fib_alloc_tag-allocate a fib using tags
 *	@dev: Adapter to allocate the fib क्रम
 *	@scmd: SCSI command
 *
 *	Allocate a fib from the adapter fib pool using tags
 *	from the blk layer.
 */

काष्ठा fib *aac_fib_alloc_tag(काष्ठा aac_dev *dev, काष्ठा scsi_cmnd *scmd)
अणु
	काष्ठा fib *fibptr;

	fibptr = &dev->fibs[scmd->request->tag];
	/*
	 *	Null out fields that depend on being zero at the start of
	 *	each I/O
	 */
	fibptr->hw_fib_va->header.XferState = 0;
	fibptr->type = FSAFS_NTC_FIB_CONTEXT;
	fibptr->callback_data = शून्य;
	fibptr->callback = शून्य;
	fibptr->flags = 0;

	वापस fibptr;
पूर्ण

/**
 *	aac_fib_alloc	-	allocate a fib
 *	@dev: Adapter to allocate the fib क्रम
 *
 *	Allocate a fib from the adapter fib pool. If the pool is empty we
 *	वापस शून्य.
 */

काष्ठा fib *aac_fib_alloc(काष्ठा aac_dev *dev)
अणु
	काष्ठा fib * fibptr;
	अचिन्हित दीर्घ flags;
	spin_lock_irqsave(&dev->fib_lock, flags);
	fibptr = dev->मुक्त_fib;
	अगर(!fibptr)अणु
		spin_unlock_irqrestore(&dev->fib_lock, flags);
		वापस fibptr;
	पूर्ण
	dev->मुक्त_fib = fibptr->next;
	spin_unlock_irqrestore(&dev->fib_lock, flags);
	/*
	 *	Set the proper node type code and node byte size
	 */
	fibptr->type = FSAFS_NTC_FIB_CONTEXT;
	fibptr->size = माप(काष्ठा fib);
	/*
	 *	Null out fields that depend on being zero at the start of
	 *	each I/O
	 */
	fibptr->hw_fib_va->header.XferState = 0;
	fibptr->flags = 0;
	fibptr->callback = शून्य;
	fibptr->callback_data = शून्य;

	वापस fibptr;
पूर्ण

/**
 *	aac_fib_मुक्त	-	मुक्त a fib
 *	@fibptr: fib to मुक्त up
 *
 *	Frees up a fib and places it on the appropriate queue
 */

व्योम aac_fib_मुक्त(काष्ठा fib *fibptr)
अणु
	अचिन्हित दीर्घ flags;

	अगर (fibptr->करोne == 2)
		वापस;

	spin_lock_irqsave(&fibptr->dev->fib_lock, flags);
	अगर (unlikely(fibptr->flags & FIB_CONTEXT_FLAG_TIMED_OUT))
		aac_config.fib_समयouts++;
	अगर (!(fibptr->flags & FIB_CONTEXT_FLAG_NATIVE_HBA) &&
		fibptr->hw_fib_va->header.XferState != 0) अणु
		prपूर्णांकk(KERN_WARNING "aac_fib_free, XferState != 0, fibptr = 0x%p, XferState = 0x%x\n",
			 (व्योम*)fibptr,
			 le32_to_cpu(fibptr->hw_fib_va->header.XferState));
	पूर्ण
	fibptr->next = fibptr->dev->मुक्त_fib;
	fibptr->dev->मुक्त_fib = fibptr;
	spin_unlock_irqrestore(&fibptr->dev->fib_lock, flags);
पूर्ण

/**
 *	aac_fib_init	-	initialise a fib
 *	@fibptr: The fib to initialize
 *
 *	Set up the generic fib fields पढ़ोy क्रम use
 */

व्योम aac_fib_init(काष्ठा fib *fibptr)
अणु
	काष्ठा hw_fib *hw_fib = fibptr->hw_fib_va;

	स_रखो(&hw_fib->header, 0, माप(काष्ठा aac_fibhdr));
	hw_fib->header.StructType = FIB_MAGIC;
	hw_fib->header.Size = cpu_to_le16(fibptr->dev->max_fib_size);
	hw_fib->header.XferState = cpu_to_le32(HostOwned | FibInitialized | FibEmpty | FastResponseCapable);
	hw_fib->header.u.ReceiverFibAddress = cpu_to_le32(fibptr->hw_fib_pa);
	hw_fib->header.SenderSize = cpu_to_le16(fibptr->dev->max_fib_size);
पूर्ण

/**
 *	fib_dealloc		-	deallocate a fib
 *	@fibptr: fib to deallocate
 *
 *	Will deallocate and वापस to the मुक्त pool the FIB poपूर्णांकed to by the
 *	caller.
 */

अटल व्योम fib_dealloc(काष्ठा fib * fibptr)
अणु
	काष्ठा hw_fib *hw_fib = fibptr->hw_fib_va;
	hw_fib->header.XferState = 0;
पूर्ण

/*
 *	Commuication primitives define and support the queuing method we use to
 *	support host to adapter commuication. All queue accesses happen through
 *	these routines and are the only routines which have a knowledge of the
 *	 how these queues are implemented.
 */

/**
 *	aac_get_entry		-	get a queue entry
 *	@dev: Adapter
 *	@qid: Queue Number
 *	@entry: Entry वापस
 *	@index: Index वापस
 *	@nonotअगरy: notअगरication control
 *
 *	With a priority the routine वापसs a queue entry अगर the queue has मुक्त entries. If the queue
 *	is full(no मुक्त entries) than no entry is वापसed and the function वापसs 0 otherwise 1 is
 *	वापसed.
 */

अटल पूर्णांक aac_get_entry (काष्ठा aac_dev * dev, u32 qid, काष्ठा aac_entry **entry, u32 * index, अचिन्हित दीर्घ *nonotअगरy)
अणु
	काष्ठा aac_queue * q;
	अचिन्हित दीर्घ idx;

	/*
	 *	All of the queues wrap when they reach the end, so we check
	 *	to see अगर they have reached the end and अगर they have we just
	 *	set the index back to zero. This is a wrap. You could or off
	 *	the high bits in all updates but this is a bit faster I think.
	 */

	q = &dev->queues->queue[qid];

	idx = *index = le32_to_cpu(*(q->headers.producer));
	/* Interrupt Moderation, only पूर्णांकerrupt क्रम first two entries */
	अगर (idx != le32_to_cpu(*(q->headers.consumer))) अणु
		अगर (--idx == 0) अणु
			अगर (qid == AdapNormCmdQueue)
				idx = ADAP_NORM_CMD_ENTRIES;
			अन्यथा
				idx = ADAP_NORM_RESP_ENTRIES;
		पूर्ण
		अगर (idx != le32_to_cpu(*(q->headers.consumer)))
			*nonotअगरy = 1;
	पूर्ण

	अगर (qid == AdapNormCmdQueue) अणु
		अगर (*index >= ADAP_NORM_CMD_ENTRIES)
			*index = 0; /* Wrap to front of the Producer Queue. */
	पूर्ण अन्यथा अणु
		अगर (*index >= ADAP_NORM_RESP_ENTRIES)
			*index = 0; /* Wrap to front of the Producer Queue. */
	पूर्ण

	/* Queue is full */
	अगर ((*index + 1) == le32_to_cpu(*(q->headers.consumer))) अणु
		prपूर्णांकk(KERN_WARNING "Queue %d full, %u outstanding.\n",
				qid, atomic_पढ़ो(&q->numpending));
		वापस 0;
	पूर्ण अन्यथा अणु
		*entry = q->base + *index;
		वापस 1;
	पूर्ण
पूर्ण

/**
 *	aac_queue_get		-	get the next मुक्त QE
 *	@dev: Adapter
 *	@index: Returned index
 *	@qid: Queue number
 *	@hw_fib: Fib to associate with the queue entry
 *	@रुको: Wait अगर queue full
 *	@fibptr: Driver fib object to go with fib
 *	@nonotअगरy: Don't notअगरy the adapter
 *
 *	Gets the next मुक्त QE off the requested priorty adapter command
 *	queue and associates the Fib with the QE. The QE represented by
 *	index is पढ़ोy to insert on the queue when this routine वापसs
 *	success.
 */

पूर्णांक aac_queue_get(काष्ठा aac_dev * dev, u32 * index, u32 qid, काष्ठा hw_fib * hw_fib, पूर्णांक रुको, काष्ठा fib * fibptr, अचिन्हित दीर्घ *nonotअगरy)
अणु
	काष्ठा aac_entry * entry = शून्य;
	पूर्णांक map = 0;

	अगर (qid == AdapNormCmdQueue) अणु
		/*  अगर no entries रुको क्रम some अगर caller wants to */
		जबतक (!aac_get_entry(dev, qid, &entry, index, nonotअगरy)) अणु
			prपूर्णांकk(KERN_ERR "GetEntries failed\n");
		पूर्ण
		/*
		 *	Setup queue entry with a command, status and fib mapped
		 */
		entry->size = cpu_to_le32(le16_to_cpu(hw_fib->header.Size));
		map = 1;
	पूर्ण अन्यथा अणु
		जबतक (!aac_get_entry(dev, qid, &entry, index, nonotअगरy)) अणु
			/* अगर no entries रुको क्रम some अगर caller wants to */
		पूर्ण
		/*
		 *	Setup queue entry with command, status and fib mapped
		 */
		entry->size = cpu_to_le32(le16_to_cpu(hw_fib->header.Size));
		entry->addr = hw_fib->header.SenderFibAddress;
			/* Restore adapters poपूर्णांकer to the FIB */
		hw_fib->header.u.ReceiverFibAddress = hw_fib->header.SenderFibAddress;  /* Let the adapter now where to find its data */
		map = 0;
	पूर्ण
	/*
	 *	If MapFib is true than we need to map the Fib and put poपूर्णांकers
	 *	in the queue entry.
	 */
	अगर (map)
		entry->addr = cpu_to_le32(fibptr->hw_fib_pa);
	वापस 0;
पूर्ण

/*
 *	Define the highest level of host to adapter communication routines.
 *	These routines will support host to adapter FS commuication. These
 *	routines have no knowledge of the commuication method used. This level
 *	sends and receives FIBs. This level has no knowledge of how these FIBs
 *	get passed back and क्रमth.
 */

/**
 *	aac_fib_send	-	send a fib to the adapter
 *	@command: Command to send
 *	@fibptr: The fib
 *	@size: Size of fib data area
 *	@priority: Priority of Fib
 *	@रुको: Async/sync select
 *	@reply: True अगर a reply is wanted
 *	@callback: Called with reply
 *	@callback_data: Passed to callback
 *
 *	Sends the requested FIB to the adapter and optionally will रुको क्रम a
 *	response FIB. If the caller करोes not wish to रुको क्रम a response than
 *	an event to रुको on must be supplied. This event will be set when a
 *	response FIB is received from the adapter.
 */

पूर्णांक aac_fib_send(u16 command, काष्ठा fib *fibptr, अचिन्हित दीर्घ size,
		पूर्णांक priority, पूर्णांक रुको, पूर्णांक reply, fib_callback callback,
		व्योम *callback_data)
अणु
	काष्ठा aac_dev * dev = fibptr->dev;
	काष्ठा hw_fib * hw_fib = fibptr->hw_fib_va;
	अचिन्हित दीर्घ flags = 0;
	अचिन्हित दीर्घ mflags = 0;
	अचिन्हित दीर्घ sflags = 0;

	अगर (!(hw_fib->header.XferState & cpu_to_le32(HostOwned)))
		वापस -EBUSY;

	अगर (hw_fib->header.XferState & cpu_to_le32(AdapterProcessed))
		वापस -EINVAL;

	/*
	 *	There are 5 हालs with the रुको and response requested flags.
	 *	The only invalid हालs are अगर the caller requests to रुको and
	 *	करोes not request a response and अगर the caller करोes not want a
	 *	response and the Fib is not allocated from pool. If a response
	 *	is not requested the Fib will just be deallocaed by the DPC
	 *	routine when the response comes back from the adapter. No
	 *	further processing will be करोne besides deleting the Fib. We
	 *	will have a debug mode where the adapter can notअगरy the host
	 *	it had a problem and the host can log that fact.
	 */
	fibptr->flags = 0;
	अगर (रुको && !reply) अणु
		वापस -EINVAL;
	पूर्ण अन्यथा अगर (!रुको && reply) अणु
		hw_fib->header.XferState |= cpu_to_le32(Async | ResponseExpected);
		FIB_COUNTER_INCREMENT(aac_config.AsyncSent);
	पूर्ण अन्यथा अगर (!रुको && !reply) अणु
		hw_fib->header.XferState |= cpu_to_le32(NoResponseExpected);
		FIB_COUNTER_INCREMENT(aac_config.NoResponseSent);
	पूर्ण अन्यथा अगर (रुको && reply) अणु
		hw_fib->header.XferState |= cpu_to_le32(ResponseExpected);
		FIB_COUNTER_INCREMENT(aac_config.NormalSent);
	पूर्ण
	/*
	 *	Map the fib पूर्णांकo 32bits by using the fib number
	 */

	hw_fib->header.SenderFibAddress =
		cpu_to_le32(((u32)(fibptr - dev->fibs)) << 2);

	/* use the same shअगरted value क्रम handle to be compatible
	 * with the new native hba command handle
	 */
	hw_fib->header.Handle =
		cpu_to_le32((((u32)(fibptr - dev->fibs)) << 2) + 1);

	/*
	 *	Set FIB state to indicate where it came from and अगर we want a
	 *	response from the adapter. Also load the command from the
	 *	caller.
	 *
	 *	Map the hw fib poपूर्णांकer as a 32bit value
	 */
	hw_fib->header.Command = cpu_to_le16(command);
	hw_fib->header.XferState |= cpu_to_le32(SentFromHost);
	/*
	 *	Set the size of the Fib we want to send to the adapter
	 */
	hw_fib->header.Size = cpu_to_le16(माप(काष्ठा aac_fibhdr) + size);
	अगर (le16_to_cpu(hw_fib->header.Size) > le16_to_cpu(hw_fib->header.SenderSize)) अणु
		वापस -EMSGSIZE;
	पूर्ण
	/*
	 *	Get a queue entry connect the FIB to it and send an notअगरy
	 *	the adapter a command is पढ़ोy.
	 */
	hw_fib->header.XferState |= cpu_to_le32(NormalPriority);

	/*
	 *	Fill in the Callback and CallbackContext अगर we are not
	 *	going to रुको.
	 */
	अगर (!रुको) अणु
		fibptr->callback = callback;
		fibptr->callback_data = callback_data;
		fibptr->flags = FIB_CONTEXT_FLAG;
	पूर्ण

	fibptr->करोne = 0;

	FIB_COUNTER_INCREMENT(aac_config.FibsSent);

	dprपूर्णांकk((KERN_DEBUG "Fib contents:.\n"));
	dprपूर्णांकk((KERN_DEBUG "  Command =               %d.\n", le32_to_cpu(hw_fib->header.Command)));
	dprपूर्णांकk((KERN_DEBUG "  SubCommand =            %d.\n", le32_to_cpu(((काष्ठा aac_query_mount *)fib_data(fibptr))->command)));
	dprपूर्णांकk((KERN_DEBUG "  XferState  =            %x.\n", le32_to_cpu(hw_fib->header.XferState)));
	dprपूर्णांकk((KERN_DEBUG "  hw_fib va being sent=%p\n",fibptr->hw_fib_va));
	dprपूर्णांकk((KERN_DEBUG "  hw_fib pa being sent=%lx\n",(uदीर्घ)fibptr->hw_fib_pa));
	dprपूर्णांकk((KERN_DEBUG "  fib being sent=%p\n",fibptr));

	अगर (!dev->queues)
		वापस -EBUSY;

	अगर (रुको) अणु

		spin_lock_irqsave(&dev->manage_lock, mflags);
		अगर (dev->management_fib_count >= AAC_NUM_MGT_FIB) अणु
			prपूर्णांकk(KERN_INFO "No management Fibs Available:%d\n",
						dev->management_fib_count);
			spin_unlock_irqrestore(&dev->manage_lock, mflags);
			वापस -EBUSY;
		पूर्ण
		dev->management_fib_count++;
		spin_unlock_irqrestore(&dev->manage_lock, mflags);
		spin_lock_irqsave(&fibptr->event_lock, flags);
	पूर्ण

	अगर (dev->sync_mode) अणु
		अगर (रुको)
			spin_unlock_irqrestore(&fibptr->event_lock, flags);
		spin_lock_irqsave(&dev->sync_lock, sflags);
		अगर (dev->sync_fib) अणु
			list_add_tail(&fibptr->fiblink, &dev->sync_fib_list);
			spin_unlock_irqrestore(&dev->sync_lock, sflags);
		पूर्ण अन्यथा अणु
			dev->sync_fib = fibptr;
			spin_unlock_irqrestore(&dev->sync_lock, sflags);
			aac_adapter_sync_cmd(dev, SEND_SYNCHRONOUS_FIB,
				(u32)fibptr->hw_fib_pa, 0, 0, 0, 0, 0,
				शून्य, शून्य, शून्य, शून्य, शून्य);
		पूर्ण
		अगर (रुको) अणु
			fibptr->flags |= FIB_CONTEXT_FLAG_WAIT;
			अगर (रुको_क्रम_completion_पूर्णांकerruptible(&fibptr->event_रुको)) अणु
				fibptr->flags &= ~FIB_CONTEXT_FLAG_WAIT;
				वापस -EFAULT;
			पूर्ण
			वापस 0;
		पूर्ण
		वापस -EINPROGRESS;
	पूर्ण

	अगर (aac_adapter_deliver(fibptr) != 0) अणु
		prपूर्णांकk(KERN_ERR "aac_fib_send: returned -EBUSY\n");
		अगर (रुको) अणु
			spin_unlock_irqrestore(&fibptr->event_lock, flags);
			spin_lock_irqsave(&dev->manage_lock, mflags);
			dev->management_fib_count--;
			spin_unlock_irqrestore(&dev->manage_lock, mflags);
		पूर्ण
		वापस -EBUSY;
	पूर्ण


	/*
	 *	If the caller wanted us to रुको क्रम response रुको now.
	 */

	अगर (रुको) अणु
		spin_unlock_irqrestore(&fibptr->event_lock, flags);
		/* Only set क्रम first known पूर्णांकerruptable command */
		अगर (रुको < 0) अणु
			/*
			 * *VERY* Dangerous to समय out a command, the
			 * assumption is made that we have no hope of
			 * functioning because an पूर्णांकerrupt routing or other
			 * hardware failure has occurred.
			 */
			अचिन्हित दीर्घ समयout = jअगरfies + (180 * HZ); /* 3 minutes */
			जबतक (!try_रुको_क्रम_completion(&fibptr->event_रुको)) अणु
				पूर्णांक blink;
				अगर (समय_is_beक्रमe_eq_jअगरfies(समयout)) अणु
					काष्ठा aac_queue * q = &dev->queues->queue[AdapNormCmdQueue];
					atomic_dec(&q->numpending);
					अगर (रुको == -1) अणु
	        				prपूर्णांकk(KERN_ERR "aacraid: aac_fib_send: first asynchronous command timed out.\n"
						  "Usually a result of a PCI interrupt routing problem;\n"
						  "update mother board BIOS or consider utilizing one of\n"
						  "the SAFE mode kernel options (acpi, apic etc)\n");
					पूर्ण
					वापस -ETIMEDOUT;
				पूर्ण

				अगर (unlikely(aac_pci_offline(dev)))
					वापस -EFAULT;

				अगर ((blink = aac_adapter_check_health(dev)) > 0) अणु
					अगर (रुको == -1) अणु
	        				prपूर्णांकk(KERN_ERR "aacraid: aac_fib_send: adapter blinkLED 0x%x.\n"
						  "Usually a result of a serious unrecoverable hardware problem\n",
						  blink);
					पूर्ण
					वापस -EFAULT;
				पूर्ण
				/*
				 * Allow other processes / CPUS to use core
				 */
				schedule();
			पूर्ण
		पूर्ण अन्यथा अगर (रुको_क्रम_completion_पूर्णांकerruptible(&fibptr->event_रुको)) अणु
			/* Do nothing ... satisfy
			 * रुको_क्रम_completion_पूर्णांकerruptible must_check */
		पूर्ण

		spin_lock_irqsave(&fibptr->event_lock, flags);
		अगर (fibptr->करोne == 0) अणु
			fibptr->करोne = 2; /* Tell पूर्णांकerrupt we पातed */
			spin_unlock_irqrestore(&fibptr->event_lock, flags);
			वापस -ERESTARTSYS;
		पूर्ण
		spin_unlock_irqrestore(&fibptr->event_lock, flags);
		BUG_ON(fibptr->करोne == 0);

		अगर(unlikely(fibptr->flags & FIB_CONTEXT_FLAG_TIMED_OUT))
			वापस -ETIMEDOUT;
		वापस 0;
	पूर्ण
	/*
	 *	If the user करोes not want a response than वापस success otherwise
	 *	वापस pending
	 */
	अगर (reply)
		वापस -EINPROGRESS;
	अन्यथा
		वापस 0;
पूर्ण

पूर्णांक aac_hba_send(u8 command, काष्ठा fib *fibptr, fib_callback callback,
		व्योम *callback_data)
अणु
	काष्ठा aac_dev *dev = fibptr->dev;
	पूर्णांक रुको;
	अचिन्हित दीर्घ flags = 0;
	अचिन्हित दीर्घ mflags = 0;
	काष्ठा aac_hba_cmd_req *hbacmd = (काष्ठा aac_hba_cmd_req *)
			fibptr->hw_fib_va;

	fibptr->flags = (FIB_CONTEXT_FLAG | FIB_CONTEXT_FLAG_NATIVE_HBA);
	अगर (callback) अणु
		रुको = 0;
		fibptr->callback = callback;
		fibptr->callback_data = callback_data;
	पूर्ण अन्यथा
		रुको = 1;


	hbacmd->iu_type = command;

	अगर (command == HBA_IU_TYPE_SCSI_CMD_REQ) अणु
		/* bit1 of request_id must be 0 */
		hbacmd->request_id =
			cpu_to_le32((((u32)(fibptr - dev->fibs)) << 2) + 1);
		fibptr->flags |= FIB_CONTEXT_FLAG_SCSI_CMD;
	पूर्ण अन्यथा
		वापस -EINVAL;


	अगर (रुको) अणु
		spin_lock_irqsave(&dev->manage_lock, mflags);
		अगर (dev->management_fib_count >= AAC_NUM_MGT_FIB) अणु
			spin_unlock_irqrestore(&dev->manage_lock, mflags);
			वापस -EBUSY;
		पूर्ण
		dev->management_fib_count++;
		spin_unlock_irqrestore(&dev->manage_lock, mflags);
		spin_lock_irqsave(&fibptr->event_lock, flags);
	पूर्ण

	अगर (aac_adapter_deliver(fibptr) != 0) अणु
		अगर (रुको) अणु
			spin_unlock_irqrestore(&fibptr->event_lock, flags);
			spin_lock_irqsave(&dev->manage_lock, mflags);
			dev->management_fib_count--;
			spin_unlock_irqrestore(&dev->manage_lock, mflags);
		पूर्ण
		वापस -EBUSY;
	पूर्ण
	FIB_COUNTER_INCREMENT(aac_config.NativeSent);

	अगर (रुको) अणु

		spin_unlock_irqrestore(&fibptr->event_lock, flags);

		अगर (unlikely(aac_pci_offline(dev)))
			वापस -EFAULT;

		fibptr->flags |= FIB_CONTEXT_FLAG_WAIT;
		अगर (रुको_क्रम_completion_पूर्णांकerruptible(&fibptr->event_रुको))
			fibptr->करोne = 2;
		fibptr->flags &= ~(FIB_CONTEXT_FLAG_WAIT);

		spin_lock_irqsave(&fibptr->event_lock, flags);
		अगर ((fibptr->करोne == 0) || (fibptr->करोne == 2)) अणु
			fibptr->करोne = 2; /* Tell पूर्णांकerrupt we पातed */
			spin_unlock_irqrestore(&fibptr->event_lock, flags);
			वापस -ERESTARTSYS;
		पूर्ण
		spin_unlock_irqrestore(&fibptr->event_lock, flags);
		WARN_ON(fibptr->करोne == 0);

		अगर (unlikely(fibptr->flags & FIB_CONTEXT_FLAG_TIMED_OUT))
			वापस -ETIMEDOUT;

		वापस 0;
	पूर्ण

	वापस -EINPROGRESS;
पूर्ण

/**
 *	aac_consumer_get	-	get the top of the queue
 *	@dev: Adapter
 *	@q: Queue
 *	@entry: Return entry
 *
 *	Will वापस a poपूर्णांकer to the entry on the top of the queue requested that
 *	we are a consumer of, and वापस the address of the queue entry. It करोes
 *	not change the state of the queue.
 */

पूर्णांक aac_consumer_get(काष्ठा aac_dev * dev, काष्ठा aac_queue * q, काष्ठा aac_entry **entry)
अणु
	u32 index;
	पूर्णांक status;
	अगर (le32_to_cpu(*q->headers.producer) == le32_to_cpu(*q->headers.consumer)) अणु
		status = 0;
	पूर्ण अन्यथा अणु
		/*
		 *	The consumer index must be wrapped अगर we have reached
		 *	the end of the queue, अन्यथा we just use the entry
		 *	poपूर्णांकed to by the header index
		 */
		अगर (le32_to_cpu(*q->headers.consumer) >= q->entries)
			index = 0;
		अन्यथा
			index = le32_to_cpu(*q->headers.consumer);
		*entry = q->base + index;
		status = 1;
	पूर्ण
	वापस(status);
पूर्ण

/**
 *	aac_consumer_मुक्त	-	मुक्त consumer entry
 *	@dev: Adapter
 *	@q: Queue
 *	@qid: Queue ident
 *
 *	Frees up the current top of the queue we are a consumer of. If the
 *	queue was full notअगरy the producer that the queue is no दीर्घer full.
 */

व्योम aac_consumer_मुक्त(काष्ठा aac_dev * dev, काष्ठा aac_queue *q, u32 qid)
अणु
	पूर्णांक wasfull = 0;
	u32 notअगरy;

	अगर ((le32_to_cpu(*q->headers.producer)+1) == le32_to_cpu(*q->headers.consumer))
		wasfull = 1;

	अगर (le32_to_cpu(*q->headers.consumer) >= q->entries)
		*q->headers.consumer = cpu_to_le32(1);
	अन्यथा
		le32_add_cpu(q->headers.consumer, 1);

	अगर (wasfull) अणु
		चयन (qid) अणु

		हाल HostNormCmdQueue:
			notअगरy = HostNormCmdNotFull;
			अवरोध;
		हाल HostNormRespQueue:
			notअगरy = HostNormRespNotFull;
			अवरोध;
		शेष:
			BUG();
			वापस;
		पूर्ण
		aac_adapter_notअगरy(dev, notअगरy);
	पूर्ण
पूर्ण

/**
 *	aac_fib_adapter_complete	-	complete adapter issued fib
 *	@fibptr: fib to complete
 *	@size: size of fib
 *
 *	Will करो all necessary work to complete a FIB that was sent from
 *	the adapter.
 */

पूर्णांक aac_fib_adapter_complete(काष्ठा fib *fibptr, अचिन्हित लघु size)
अणु
	काष्ठा hw_fib * hw_fib = fibptr->hw_fib_va;
	काष्ठा aac_dev * dev = fibptr->dev;
	काष्ठा aac_queue * q;
	अचिन्हित दीर्घ noपूर्णांकr = 0;
	अचिन्हित दीर्घ qflags;

	अगर (dev->comm_पूर्णांकerface == AAC_COMM_MESSAGE_TYPE1 ||
		dev->comm_पूर्णांकerface == AAC_COMM_MESSAGE_TYPE2 ||
		dev->comm_पूर्णांकerface == AAC_COMM_MESSAGE_TYPE3) अणु
		kमुक्त(hw_fib);
		वापस 0;
	पूर्ण

	अगर (hw_fib->header.XferState == 0) अणु
		अगर (dev->comm_पूर्णांकerface == AAC_COMM_MESSAGE)
			kमुक्त(hw_fib);
		वापस 0;
	पूर्ण
	/*
	 *	If we plan to करो anything check the काष्ठाure type first.
	 */
	अगर (hw_fib->header.StructType != FIB_MAGIC &&
	    hw_fib->header.StructType != FIB_MAGIC2 &&
	    hw_fib->header.StructType != FIB_MAGIC2_64) अणु
		अगर (dev->comm_पूर्णांकerface == AAC_COMM_MESSAGE)
			kमुक्त(hw_fib);
		वापस -EINVAL;
	पूर्ण
	/*
	 *	This block handles the हाल where the adapter had sent us a
	 *	command and we have finished processing the command. We
	 *	call completeFib when we are करोne processing the command
	 *	and want to send a response back to the adapter. This will
	 *	send the completed cdb to the adapter.
	 */
	अगर (hw_fib->header.XferState & cpu_to_le32(SentFromAdapter)) अणु
		अगर (dev->comm_पूर्णांकerface == AAC_COMM_MESSAGE) अणु
			kमुक्त (hw_fib);
		पूर्ण अन्यथा अणु
			u32 index;
			hw_fib->header.XferState |= cpu_to_le32(HostProcessed);
			अगर (size) अणु
				size += माप(काष्ठा aac_fibhdr);
				अगर (size > le16_to_cpu(hw_fib->header.SenderSize))
					वापस -EMSGSIZE;
				hw_fib->header.Size = cpu_to_le16(size);
			पूर्ण
			q = &dev->queues->queue[AdapNormRespQueue];
			spin_lock_irqsave(q->lock, qflags);
			aac_queue_get(dev, &index, AdapNormRespQueue, hw_fib, 1, शून्य, &noपूर्णांकr);
			*(q->headers.producer) = cpu_to_le32(index + 1);
			spin_unlock_irqrestore(q->lock, qflags);
			अगर (!(noपूर्णांकr & (पूर्णांक)aac_config.irq_mod))
				aac_adapter_notअगरy(dev, AdapNormRespQueue);
		पूर्ण
	पूर्ण अन्यथा अणु
		prपूर्णांकk(KERN_WARNING "aac_fib_adapter_complete: "
			"Unknown xferstate detected.\n");
		BUG();
	पूर्ण
	वापस 0;
पूर्ण

/**
 *	aac_fib_complete	-	fib completion handler
 *	@fibptr: FIB to complete
 *
 *	Will करो all necessary work to complete a FIB.
 */

पूर्णांक aac_fib_complete(काष्ठा fib *fibptr)
अणु
	काष्ठा hw_fib * hw_fib = fibptr->hw_fib_va;

	अगर (fibptr->flags & FIB_CONTEXT_FLAG_NATIVE_HBA) अणु
		fib_dealloc(fibptr);
		वापस 0;
	पूर्ण

	/*
	 *	Check क्रम a fib which has alपढ़ोy been completed or with a
	 *	status रुको समयout
	 */

	अगर (hw_fib->header.XferState == 0 || fibptr->करोne == 2)
		वापस 0;
	/*
	 *	If we plan to करो anything check the काष्ठाure type first.
	 */

	अगर (hw_fib->header.StructType != FIB_MAGIC &&
	    hw_fib->header.StructType != FIB_MAGIC2 &&
	    hw_fib->header.StructType != FIB_MAGIC2_64)
		वापस -EINVAL;
	/*
	 *	This block completes a cdb which orginated on the host and we
	 *	just need to deallocate the cdb or reinit it. At this poपूर्णांक the
	 *	command is complete that we had sent to the adapter and this
	 *	cdb could be reused.
	 */

	अगर((hw_fib->header.XferState & cpu_to_le32(SentFromHost)) &&
		(hw_fib->header.XferState & cpu_to_le32(AdapterProcessed)))
	अणु
		fib_dealloc(fibptr);
	पूर्ण
	अन्यथा अगर(hw_fib->header.XferState & cpu_to_le32(SentFromHost))
	अणु
		/*
		 *	This handles the हाल when the host has पातed the I/O
		 *	to the adapter because the adapter is not responding
		 */
		fib_dealloc(fibptr);
	पूर्ण अन्यथा अगर(hw_fib->header.XferState & cpu_to_le32(HostOwned)) अणु
		fib_dealloc(fibptr);
	पूर्ण अन्यथा अणु
		BUG();
	पूर्ण
	वापस 0;
पूर्ण

/**
 *	aac_म_लिखो	-	handle म_लिखो from firmware
 *	@dev: Adapter
 *	@val: Message info
 *
 *	Prपूर्णांक a message passed to us by the controller firmware on the
 *	Adaptec board
 */

व्योम aac_म_लिखो(काष्ठा aac_dev *dev, u32 val)
अणु
	अक्षर *cp = dev->म_लिखोbuf;
	अगर (dev->म_लिखो_enabled)
	अणु
		पूर्णांक length = val & 0xffff;
		पूर्णांक level = (val >> 16) & 0xffff;

		/*
		 *	The size of the म_लिखोbuf is set in port.c
		 *	There is no variable or define क्रम it
		 */
		अगर (length > 255)
			length = 255;
		अगर (cp[length] != 0)
			cp[length] = 0;
		अगर (level == LOG_AAC_HIGH_ERROR)
			prपूर्णांकk(KERN_WARNING "%s:%s", dev->name, cp);
		अन्यथा
			prपूर्णांकk(KERN_INFO "%s:%s", dev->name, cp);
	पूर्ण
	स_रखो(cp, 0, 256);
पूर्ण

अटल अंतरभूत पूर्णांक aac_aअगर_data(काष्ठा aac_aअगरcmd *aअगरcmd, uपूर्णांक32_t index)
अणु
	वापस le32_to_cpu(((__le32 *)aअगरcmd->data)[index]);
पूर्ण


अटल व्योम aac_handle_aअगर_bu(काष्ठा aac_dev *dev, काष्ठा aac_aअगरcmd *aअगरcmd)
अणु
	चयन (aac_aअगर_data(aअगरcmd, 1)) अणु
	हाल AअगरBuCacheDataLoss:
		अगर (aac_aअगर_data(aअगरcmd, 2))
			dev_info(&dev->pdev->dev, "Backup unit had cache data loss - [%d]\n",
			aac_aअगर_data(aअगरcmd, 2));
		अन्यथा
			dev_info(&dev->pdev->dev, "Backup Unit had cache data loss\n");
		अवरोध;
	हाल AअगरBuCacheDataRecover:
		अगर (aac_aअगर_data(aअगरcmd, 2))
			dev_info(&dev->pdev->dev, "DDR cache data recovered successfully - [%d]\n",
			aac_aअगर_data(aअगरcmd, 2));
		अन्यथा
			dev_info(&dev->pdev->dev, "DDR cache data recovered successfully\n");
		अवरोध;
	पूर्ण
पूर्ण

#घोषणा AIF_SNIFF_TIMEOUT	(500*HZ)
/**
 *	aac_handle_aअगर		-	Handle a message from the firmware
 *	@dev: Which adapter this fib is from
 *	@fibptr: Poपूर्णांकer to fibptr from adapter
 *
 *	This routine handles a driver notअगरy fib from the adapter and
 *	dispatches it to the appropriate routine क्रम handling.
 */
अटल व्योम aac_handle_aअगर(काष्ठा aac_dev * dev, काष्ठा fib * fibptr)
अणु
	काष्ठा hw_fib * hw_fib = fibptr->hw_fib_va;
	काष्ठा aac_aअगरcmd * aअगरcmd = (काष्ठा aac_aअगरcmd *)hw_fib->data;
	u32 channel, id, lun, container;
	काष्ठा scsi_device *device;
	क्रमागत अणु
		NOTHING,
		DELETE,
		ADD,
		CHANGE
	पूर्ण device_config_needed = NOTHING;

	/* Snअगरf क्रम container changes */

	अगर (!dev || !dev->fsa_dev)
		वापस;
	container = channel = id = lun = (u32)-1;

	/*
	 *	We have set this up to try and minimize the number of
	 * re-configures that take place. As a result of this when
	 * certain AIF's come in we will set a flag रुकोing क्रम another
	 * type of AIF beक्रमe setting the re-config flag.
	 */
	चयन (le32_to_cpu(aअगरcmd->command)) अणु
	हाल AअगरCmdDriverNotअगरy:
		चयन (le32_to_cpu(((__le32 *)aअगरcmd->data)[0])) अणु
		हाल AअगरRawDeviceRemove:
			container = le32_to_cpu(((__le32 *)aअगरcmd->data)[1]);
			अगर ((container >> 28)) अणु
				container = (u32)-1;
				अवरोध;
			पूर्ण
			channel = (container >> 24) & 0xF;
			अगर (channel >= dev->maximum_num_channels) अणु
				container = (u32)-1;
				अवरोध;
			पूर्ण
			id = container & 0xFFFF;
			अगर (id >= dev->maximum_num_physicals) अणु
				container = (u32)-1;
				अवरोध;
			पूर्ण
			lun = (container >> 16) & 0xFF;
			container = (u32)-1;
			channel = aac_phys_to_logical(channel);
			device_config_needed = DELETE;
			अवरोध;

		/*
		 *	Morph or Expand complete
		 */
		हाल AअगरDenMorphComplete:
		हाल AअगरDenVolumeExtendComplete:
			container = le32_to_cpu(((__le32 *)aअगरcmd->data)[1]);
			अगर (container >= dev->maximum_num_containers)
				अवरोध;

			/*
			 *	Find the scsi_device associated with the SCSI
			 * address. Make sure we have the right array, and अगर
			 * so set the flag to initiate a new re-config once we
			 * see an AअगरEnConfigChange AIF come through.
			 */

			अगर ((dev != शून्य) && (dev->scsi_host_ptr != शून्य)) अणु
				device = scsi_device_lookup(dev->scsi_host_ptr,
					CONTAINER_TO_CHANNEL(container),
					CONTAINER_TO_ID(container),
					CONTAINER_TO_LUN(container));
				अगर (device) अणु
					dev->fsa_dev[container].config_needed = CHANGE;
					dev->fsa_dev[container].config_रुकोing_on = AअगरEnConfigChange;
					dev->fsa_dev[container].config_रुकोing_stamp = jअगरfies;
					scsi_device_put(device);
				पूर्ण
			पूर्ण
		पूर्ण

		/*
		 *	If we are रुकोing on something and this happens to be
		 * that thing then set the re-configure flag.
		 */
		अगर (container != (u32)-1) अणु
			अगर (container >= dev->maximum_num_containers)
				अवरोध;
			अगर ((dev->fsa_dev[container].config_रुकोing_on ==
			    le32_to_cpu(*(__le32 *)aअगरcmd->data)) &&
			 समय_beक्रमe(jअगरfies, dev->fsa_dev[container].config_रुकोing_stamp + AIF_SNIFF_TIMEOUT))
				dev->fsa_dev[container].config_रुकोing_on = 0;
		पूर्ण अन्यथा क्रम (container = 0;
		    container < dev->maximum_num_containers; ++container) अणु
			अगर ((dev->fsa_dev[container].config_रुकोing_on ==
			    le32_to_cpu(*(__le32 *)aअगरcmd->data)) &&
			 समय_beक्रमe(jअगरfies, dev->fsa_dev[container].config_रुकोing_stamp + AIF_SNIFF_TIMEOUT))
				dev->fsa_dev[container].config_रुकोing_on = 0;
		पूर्ण
		अवरोध;

	हाल AअगरCmdEventNotअगरy:
		चयन (le32_to_cpu(((__le32 *)aअगरcmd->data)[0])) अणु
		हाल AअगरEnBatteryEvent:
			dev->cache_रक्षित =
				(((__le32 *)aअगरcmd->data)[1] == cpu_to_le32(3));
			अवरोध;
		/*
		 *	Add an Array.
		 */
		हाल AअगरEnAddContainer:
			container = le32_to_cpu(((__le32 *)aअगरcmd->data)[1]);
			अगर (container >= dev->maximum_num_containers)
				अवरोध;
			dev->fsa_dev[container].config_needed = ADD;
			dev->fsa_dev[container].config_रुकोing_on =
				AअगरEnConfigChange;
			dev->fsa_dev[container].config_रुकोing_stamp = jअगरfies;
			अवरोध;

		/*
		 *	Delete an Array.
		 */
		हाल AअगरEnDeleteContainer:
			container = le32_to_cpu(((__le32 *)aअगरcmd->data)[1]);
			अगर (container >= dev->maximum_num_containers)
				अवरोध;
			dev->fsa_dev[container].config_needed = DELETE;
			dev->fsa_dev[container].config_रुकोing_on =
				AअगरEnConfigChange;
			dev->fsa_dev[container].config_रुकोing_stamp = jअगरfies;
			अवरोध;

		/*
		 *	Container change detected. If we currently are not
		 * रुकोing on something अन्यथा, setup to रुको on a Config Change.
		 */
		हाल AअगरEnContainerChange:
			container = le32_to_cpu(((__le32 *)aअगरcmd->data)[1]);
			अगर (container >= dev->maximum_num_containers)
				अवरोध;
			अगर (dev->fsa_dev[container].config_रुकोing_on &&
			 समय_beक्रमe(jअगरfies, dev->fsa_dev[container].config_रुकोing_stamp + AIF_SNIFF_TIMEOUT))
				अवरोध;
			dev->fsa_dev[container].config_needed = CHANGE;
			dev->fsa_dev[container].config_रुकोing_on =
				AअगरEnConfigChange;
			dev->fsa_dev[container].config_रुकोing_stamp = jअगरfies;
			अवरोध;

		हाल AअगरEnConfigChange:
			अवरोध;

		हाल AअगरEnAddJBOD:
		हाल AअगरEnDeleteJBOD:
			container = le32_to_cpu(((__le32 *)aअगरcmd->data)[1]);
			अगर ((container >> 28)) अणु
				container = (u32)-1;
				अवरोध;
			पूर्ण
			channel = (container >> 24) & 0xF;
			अगर (channel >= dev->maximum_num_channels) अणु
				container = (u32)-1;
				अवरोध;
			पूर्ण
			id = container & 0xFFFF;
			अगर (id >= dev->maximum_num_physicals) अणु
				container = (u32)-1;
				अवरोध;
			पूर्ण
			lun = (container >> 16) & 0xFF;
			container = (u32)-1;
			channel = aac_phys_to_logical(channel);
			device_config_needed =
			  (((__le32 *)aअगरcmd->data)[0] ==
			    cpu_to_le32(AअगरEnAddJBOD)) ? ADD : DELETE;
			अगर (device_config_needed == ADD) अणु
				device = scsi_device_lookup(dev->scsi_host_ptr,
					channel,
					id,
					lun);
				अगर (device) अणु
					scsi_हटाओ_device(device);
					scsi_device_put(device);
				पूर्ण
			पूर्ण
			अवरोध;

		हाल AअगरEnEnclosureManagement:
			/*
			 * If in JBOD mode, स्वतःmatic exposure of new
			 * physical target to be suppressed until configured.
			 */
			अगर (dev->jbod)
				अवरोध;
			चयन (le32_to_cpu(((__le32 *)aअगरcmd->data)[3])) अणु
			हाल EM_DRIVE_INSERTION:
			हाल EM_DRIVE_REMOVAL:
			हाल EM_SES_DRIVE_INSERTION:
			हाल EM_SES_DRIVE_REMOVAL:
				container = le32_to_cpu(
					((__le32 *)aअगरcmd->data)[2]);
				अगर ((container >> 28)) अणु
					container = (u32)-1;
					अवरोध;
				पूर्ण
				channel = (container >> 24) & 0xF;
				अगर (channel >= dev->maximum_num_channels) अणु
					container = (u32)-1;
					अवरोध;
				पूर्ण
				id = container & 0xFFFF;
				lun = (container >> 16) & 0xFF;
				container = (u32)-1;
				अगर (id >= dev->maximum_num_physicals) अणु
					/* legacy dev_t ? */
					अगर ((0x2000 <= id) || lun || channel ||
					  ((channel = (id >> 7) & 0x3F) >=
					  dev->maximum_num_channels))
						अवरोध;
					lun = (id >> 4) & 7;
					id &= 0xF;
				पूर्ण
				channel = aac_phys_to_logical(channel);
				device_config_needed =
				  ((((__le32 *)aअगरcmd->data)[3]
				    == cpu_to_le32(EM_DRIVE_INSERTION)) ||
				    (((__le32 *)aअगरcmd->data)[3]
				    == cpu_to_le32(EM_SES_DRIVE_INSERTION))) ?
				  ADD : DELETE;
				अवरोध;
			पूर्ण
			अवरोध;
		हाल AअगरBuManagerEvent:
			aac_handle_aअगर_bu(dev, aअगरcmd);
			अवरोध;
		पूर्ण

		/*
		 *	If we are रुकोing on something and this happens to be
		 * that thing then set the re-configure flag.
		 */
		अगर (container != (u32)-1) अणु
			अगर (container >= dev->maximum_num_containers)
				अवरोध;
			अगर ((dev->fsa_dev[container].config_रुकोing_on ==
			    le32_to_cpu(*(__le32 *)aअगरcmd->data)) &&
			 समय_beक्रमe(jअगरfies, dev->fsa_dev[container].config_रुकोing_stamp + AIF_SNIFF_TIMEOUT))
				dev->fsa_dev[container].config_रुकोing_on = 0;
		पूर्ण अन्यथा क्रम (container = 0;
		    container < dev->maximum_num_containers; ++container) अणु
			अगर ((dev->fsa_dev[container].config_रुकोing_on ==
			    le32_to_cpu(*(__le32 *)aअगरcmd->data)) &&
			 समय_beक्रमe(jअगरfies, dev->fsa_dev[container].config_रुकोing_stamp + AIF_SNIFF_TIMEOUT))
				dev->fsa_dev[container].config_रुकोing_on = 0;
		पूर्ण
		अवरोध;

	हाल AअगरCmdJobProgress:
		/*
		 *	These are job progress AIF's. When a Clear is being
		 * करोne on a container it is initially created then hidden from
		 * the OS. When the clear completes we करोn't get a config
		 * change so we monitor the job status complete on a clear then
		 * रुको क्रम a container change.
		 */

		अगर (((__le32 *)aअगरcmd->data)[1] == cpu_to_le32(AअगरJobCtrZero) &&
		    (((__le32 *)aअगरcmd->data)[6] == ((__le32 *)aअगरcmd->data)[5] ||
		     ((__le32 *)aअगरcmd->data)[4] == cpu_to_le32(AअगरJobStsSuccess))) अणु
			क्रम (container = 0;
			    container < dev->maximum_num_containers;
			    ++container) अणु
				/*
				 * Stomp on all config sequencing क्रम all
				 * containers?
				 */
				dev->fsa_dev[container].config_रुकोing_on =
					AअगरEnContainerChange;
				dev->fsa_dev[container].config_needed = ADD;
				dev->fsa_dev[container].config_रुकोing_stamp =
					jअगरfies;
			पूर्ण
		पूर्ण
		अगर (((__le32 *)aअगरcmd->data)[1] == cpu_to_le32(AअगरJobCtrZero) &&
		    ((__le32 *)aअगरcmd->data)[6] == 0 &&
		    ((__le32 *)aअगरcmd->data)[4] == cpu_to_le32(AअगरJobStsRunning)) अणु
			क्रम (container = 0;
			    container < dev->maximum_num_containers;
			    ++container) अणु
				/*
				 * Stomp on all config sequencing क्रम all
				 * containers?
				 */
				dev->fsa_dev[container].config_रुकोing_on =
					AअगरEnContainerChange;
				dev->fsa_dev[container].config_needed = DELETE;
				dev->fsa_dev[container].config_रुकोing_stamp =
					jअगरfies;
			पूर्ण
		पूर्ण
		अवरोध;
	पूर्ण

	container = 0;
retry_next:
	अगर (device_config_needed == NOTHING) अणु
		क्रम (; container < dev->maximum_num_containers; ++container) अणु
			अगर ((dev->fsa_dev[container].config_रुकोing_on == 0) &&
			    (dev->fsa_dev[container].config_needed != NOTHING) &&
			    समय_beक्रमe(jअगरfies, dev->fsa_dev[container].config_रुकोing_stamp + AIF_SNIFF_TIMEOUT)) अणु
				device_config_needed =
					dev->fsa_dev[container].config_needed;
				dev->fsa_dev[container].config_needed = NOTHING;
				channel = CONTAINER_TO_CHANNEL(container);
				id = CONTAINER_TO_ID(container);
				lun = CONTAINER_TO_LUN(container);
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (device_config_needed == NOTHING)
		वापस;

	/*
	 *	If we decided that a re-configuration needs to be करोne,
	 * schedule it here on the way out the करोor, please बंद the करोor
	 * behind you.
	 */

	/*
	 *	Find the scsi_device associated with the SCSI address,
	 * and mark it as changed, invalidating the cache. This deals
	 * with changes to existing device IDs.
	 */

	अगर (!dev || !dev->scsi_host_ptr)
		वापस;
	/*
	 * क्रमce reload of disk info via aac_probe_container
	 */
	अगर ((channel == CONTAINER_CHANNEL) &&
	  (device_config_needed != NOTHING)) अणु
		अगर (dev->fsa_dev[container].valid == 1)
			dev->fsa_dev[container].valid = 2;
		aac_probe_container(dev, container);
	पूर्ण
	device = scsi_device_lookup(dev->scsi_host_ptr, channel, id, lun);
	अगर (device) अणु
		चयन (device_config_needed) अणु
		हाल DELETE:
#अगर (defined(AAC_DEBUG_INSTRUMENT_AIF_DELETE))
			scsi_हटाओ_device(device);
#अन्यथा
			अगर (scsi_device_online(device)) अणु
				scsi_device_set_state(device, SDEV_OFFLINE);
				sdev_prपूर्णांकk(KERN_INFO, device,
					"Device offlined - %s\n",
					(channel == CONTAINER_CHANNEL) ?
						"array deleted" :
						"enclosure services event");
			पूर्ण
#पूर्ण_अगर
			अवरोध;
		हाल ADD:
			अगर (!scsi_device_online(device)) अणु
				sdev_prपूर्णांकk(KERN_INFO, device,
					"Device online - %s\n",
					(channel == CONTAINER_CHANNEL) ?
						"array created" :
						"enclosure services event");
				scsi_device_set_state(device, SDEV_RUNNING);
			पूर्ण
			fallthrough;
		हाल CHANGE:
			अगर ((channel == CONTAINER_CHANNEL)
			 && (!dev->fsa_dev[container].valid)) अणु
#अगर (defined(AAC_DEBUG_INSTRUMENT_AIF_DELETE))
				scsi_हटाओ_device(device);
#अन्यथा
				अगर (!scsi_device_online(device))
					अवरोध;
				scsi_device_set_state(device, SDEV_OFFLINE);
				sdev_prपूर्णांकk(KERN_INFO, device,
					"Device offlined - %s\n",
					"array failed");
#पूर्ण_अगर
				अवरोध;
			पूर्ण
			scsi_rescan_device(&device->sdev_gendev);
			अवरोध;

		शेष:
			अवरोध;
		पूर्ण
		scsi_device_put(device);
		device_config_needed = NOTHING;
	पूर्ण
	अगर (device_config_needed == ADD)
		scsi_add_device(dev->scsi_host_ptr, channel, id, lun);
	अगर (channel == CONTAINER_CHANNEL) अणु
		container++;
		device_config_needed = NOTHING;
		जाओ retry_next;
	पूर्ण
पूर्ण

अटल व्योम aac_schedule_bus_scan(काष्ठा aac_dev *aac)
अणु
	अगर (aac->sa_firmware)
		aac_schedule_safw_scan_worker(aac);
	अन्यथा
		aac_schedule_src_reinit_aअगर_worker(aac);
पूर्ण

अटल पूर्णांक _aac_reset_adapter(काष्ठा aac_dev *aac, पूर्णांक क्रमced, u8 reset_type)
अणु
	पूर्णांक index, quirks;
	पूर्णांक retval;
	काष्ठा Scsi_Host *host = aac->scsi_host_ptr;
	पूर्णांक jafo = 0;
	पूर्णांक bled;
	u64 dmamask;
	पूर्णांक num_of_fibs = 0;

	/*
	 * Assumptions:
	 *	- host is locked, unless called by the aacraid thपढ़ो.
	 *	  (a matter of convenience, due to legacy issues surrounding
	 *	  eh_host_adapter_reset).
	 *	- in_reset is निश्चितed, so no new i/o is getting to the
	 *	  card.
	 *	- The card is dead, or will be very लघुly ;-/ so no new
	 *	  commands are completing in the पूर्णांकerrupt service.
	 */
	aac_adapter_disable_पूर्णांक(aac);
	अगर (aac->thपढ़ो && aac->thपढ़ो->pid != current->pid) अणु
		spin_unlock_irq(host->host_lock);
		kthपढ़ो_stop(aac->thपढ़ो);
		aac->thपढ़ो = शून्य;
		jafo = 1;
	पूर्ण

	/*
	 *	If a positive health, means in a known DEAD PANIC
	 * state and the adapter could be reset to `try again'.
	 */
	bled = क्रमced ? 0 : aac_adapter_check_health(aac);
	retval = aac_adapter_restart(aac, bled, reset_type);

	अगर (retval)
		जाओ out;

	/*
	 *	Loop through the fibs, बंद the synchronous FIBS
	 */
	retval = 1;
	num_of_fibs = aac->scsi_host_ptr->can_queue + AAC_NUM_MGT_FIB;
	क्रम (index = 0; index <  num_of_fibs; index++) अणु

		काष्ठा fib *fib = &aac->fibs[index];
		__le32 XferState = fib->hw_fib_va->header.XferState;
		bool is_response_expected = false;

		अगर (!(XferState & cpu_to_le32(NoResponseExpected | Async)) &&
		   (XferState & cpu_to_le32(ResponseExpected)))
			is_response_expected = true;

		अगर (is_response_expected
		  || fib->flags & FIB_CONTEXT_FLAG_WAIT) अणु
			अचिन्हित दीर्घ flagv;
			spin_lock_irqsave(&fib->event_lock, flagv);
			complete(&fib->event_रुको);
			spin_unlock_irqrestore(&fib->event_lock, flagv);
			schedule();
			retval = 0;
		पूर्ण
	पूर्ण
	/* Give some extra समय क्रम ioctls to complete. */
	अगर (retval == 0)
		ssleep(2);
	index = aac->cardtype;

	/*
	 * Re-initialize the adapter, first मुक्त resources, then carefully
	 * apply the initialization sequence to come back again. Only risk
	 * is a change in Firmware dropping cache, it is assumed the caller
	 * will ensure that i/o is queisced and the card is flushed in that
	 * हाल.
	 */
	aac_मुक्त_irq(aac);
	aac_fib_map_मुक्त(aac);
	dma_मुक्त_coherent(&aac->pdev->dev, aac->comm_size, aac->comm_addr,
			  aac->comm_phys);
	aac_adapter_ioremap(aac, 0);
	aac->comm_addr = शून्य;
	aac->comm_phys = 0;
	kमुक्त(aac->queues);
	aac->queues = शून्य;
	kमुक्त(aac->fsa_dev);
	aac->fsa_dev = शून्य;

	dmamask = DMA_BIT_MASK(32);
	quirks = aac_get_driver_ident(index)->quirks;
	अगर (quirks & AAC_QUIRK_31BIT)
		retval = dma_set_mask(&aac->pdev->dev, dmamask);
	अन्यथा अगर (!(quirks & AAC_QUIRK_SRC))
		retval = dma_set_mask(&aac->pdev->dev, dmamask);
	अन्यथा
		retval = dma_set_coherent_mask(&aac->pdev->dev, dmamask);

	अगर (quirks & AAC_QUIRK_31BIT && !retval) अणु
		dmamask = DMA_BIT_MASK(31);
		retval = dma_set_coherent_mask(&aac->pdev->dev, dmamask);
	पूर्ण

	अगर (retval)
		जाओ out;

	अगर ((retval = (*(aac_get_driver_ident(index)->init))(aac)))
		जाओ out;

	अगर (jafo) अणु
		aac->thपढ़ो = kthपढ़ो_run(aac_command_thपढ़ो, aac, "%s",
					  aac->name);
		अगर (IS_ERR(aac->thपढ़ो)) अणु
			retval = PTR_ERR(aac->thपढ़ो);
			aac->thपढ़ो = शून्य;
			जाओ out;
		पूर्ण
	पूर्ण
	(व्योम)aac_get_adapter_info(aac);
	अगर ((quirks & AAC_QUIRK_34SG) && (host->sg_tablesize > 34)) अणु
		host->sg_tablesize = 34;
		host->max_sectors = (host->sg_tablesize * 8) + 112;
	पूर्ण
	अगर ((quirks & AAC_QUIRK_17SG) && (host->sg_tablesize > 17)) अणु
		host->sg_tablesize = 17;
		host->max_sectors = (host->sg_tablesize * 8) + 112;
	पूर्ण
	aac_get_config_status(aac, 1);
	aac_get_containers(aac);
	/*
	 * This is where the assumption that the Adapter is quiesced
	 * is important.
	 */
	scsi_host_complete_all_commands(host, DID_RESET);

	retval = 0;
out:
	aac->in_reset = 0;

	/*
	 * Issue bus rescan to catch any configuration that might have
	 * occurred
	 */
	अगर (!retval && !is_kdump_kernel()) अणु
		dev_info(&aac->pdev->dev, "Scheduling bus rescan\n");
		aac_schedule_bus_scan(aac);
	पूर्ण

	अगर (jafo) अणु
		spin_lock_irq(host->host_lock);
	पूर्ण
	वापस retval;
पूर्ण

पूर्णांक aac_reset_adapter(काष्ठा aac_dev *aac, पूर्णांक क्रमced, u8 reset_type)
अणु
	अचिन्हित दीर्घ flagv = 0;
	पूर्णांक retval, unblock_retval;
	काष्ठा Scsi_Host *host = aac->scsi_host_ptr;
	पूर्णांक bled;

	अगर (spin_trylock_irqsave(&aac->fib_lock, flagv) == 0)
		वापस -EBUSY;

	अगर (aac->in_reset) अणु
		spin_unlock_irqrestore(&aac->fib_lock, flagv);
		वापस -EBUSY;
	पूर्ण
	aac->in_reset = 1;
	spin_unlock_irqrestore(&aac->fib_lock, flagv);

	/*
	 * Wait क्रम all commands to complete to this specअगरic
	 * target (block maximum 60 seconds). Although not necessary,
	 * it करोes make us a good storage citizen.
	 */
	scsi_host_block(host);

	/* Quiesce build, flush cache, ग_लिखो through mode */
	अगर (क्रमced < 2)
		aac_send_shutकरोwn(aac);
	spin_lock_irqsave(host->host_lock, flagv);
	bled = क्रमced ? क्रमced :
			(aac_check_reset != 0 && aac_check_reset != 1);
	retval = _aac_reset_adapter(aac, bled, reset_type);
	spin_unlock_irqrestore(host->host_lock, flagv);

	unblock_retval = scsi_host_unblock(host, SDEV_RUNNING);
	अगर (!retval)
		retval = unblock_retval;
	अगर ((क्रमced < 2) && (retval == -ENODEV)) अणु
		/* Unwind aac_send_shutकरोwn() IOP_RESET unsupported/disabled */
		काष्ठा fib * fibctx = aac_fib_alloc(aac);
		अगर (fibctx) अणु
			काष्ठा aac_छोड़ो *cmd;
			पूर्णांक status;

			aac_fib_init(fibctx);

			cmd = (काष्ठा aac_छोड़ो *) fib_data(fibctx);

			cmd->command = cpu_to_le32(VM_ContainerConfig);
			cmd->type = cpu_to_le32(CT_PAUSE_IO);
			cmd->समयout = cpu_to_le32(1);
			cmd->min = cpu_to_le32(1);
			cmd->noRescan = cpu_to_le32(1);
			cmd->count = cpu_to_le32(0);

			status = aac_fib_send(ContainerCommand,
			  fibctx,
			  माप(काष्ठा aac_छोड़ो),
			  FsaNormal,
			  -2 /* Timeout silently */, 1,
			  शून्य, शून्य);

			अगर (status >= 0)
				aac_fib_complete(fibctx);
			/* FIB should be मुक्तd only after getting
			 * the response from the F/W */
			अगर (status != -ERESTARTSYS)
				aac_fib_मुक्त(fibctx);
		पूर्ण
	पूर्ण

	वापस retval;
पूर्ण

पूर्णांक aac_check_health(काष्ठा aac_dev * aac)
अणु
	पूर्णांक BlinkLED;
	अचिन्हित दीर्घ समय_now, flagv = 0;
	काष्ठा list_head * entry;

	/* Extending the scope of fib_lock slightly to protect aac->in_reset */
	अगर (spin_trylock_irqsave(&aac->fib_lock, flagv) == 0)
		वापस 0;

	अगर (aac->in_reset || !(BlinkLED = aac_adapter_check_health(aac))) अणु
		spin_unlock_irqrestore(&aac->fib_lock, flagv);
		वापस 0; /* OK */
	पूर्ण

	aac->in_reset = 1;

	/* Fake up an AIF:
	 *	aac_aअगरcmd.command = AअगरCmdEventNotअगरy = 1
	 *	aac_aअगरcmd.seqnum = 0xFFFFFFFF
	 *	aac_aअगरcmd.data[0] = AअगरEnExpEvent = 23
	 *	aac_aअगरcmd.data[1] = AअगरExeFirmwarePanic = 3
	 *	aac.aअगरcmd.data[2] = AअगरHighPriority = 3
	 *	aac.aअगरcmd.data[3] = BlinkLED
	 */

	समय_now = jअगरfies/HZ;
	entry = aac->fib_list.next;

	/*
	 * For each Context that is on the
	 * fibctxList, make a copy of the
	 * fib, and then set the event to wake up the
	 * thपढ़ो that is रुकोing क्रम it.
	 */
	जबतक (entry != &aac->fib_list) अणु
		/*
		 * Extract the fibctx
		 */
		काष्ठा aac_fib_context *fibctx = list_entry(entry, काष्ठा aac_fib_context, next);
		काष्ठा hw_fib * hw_fib;
		काष्ठा fib * fib;
		/*
		 * Check अगर the queue is getting
		 * backlogged
		 */
		अगर (fibctx->count > 20) अणु
			/*
			 * It's *not* jअगरfies folks,
			 * but jअगरfies / HZ, so करो not
			 * panic ...
			 */
			u32 समय_last = fibctx->jअगरfies;
			/*
			 * Has it been > 2 minutes
			 * since the last पढ़ो off
			 * the queue?
			 */
			अगर ((समय_now - समय_last) > aअगर_समयout) अणु
				entry = entry->next;
				aac_बंद_fib_context(aac, fibctx);
				जारी;
			पूर्ण
		पूर्ण
		/*
		 * Warning: no sleep allowed जबतक
		 * holding spinlock
		 */
		hw_fib = kzalloc(माप(काष्ठा hw_fib), GFP_ATOMIC);
		fib = kzalloc(माप(काष्ठा fib), GFP_ATOMIC);
		अगर (fib && hw_fib) अणु
			काष्ठा aac_aअगरcmd * aअगर;

			fib->hw_fib_va = hw_fib;
			fib->dev = aac;
			aac_fib_init(fib);
			fib->type = FSAFS_NTC_FIB_CONTEXT;
			fib->size = माप (काष्ठा fib);
			fib->data = hw_fib->data;
			aअगर = (काष्ठा aac_aअगरcmd *)hw_fib->data;
			aअगर->command = cpu_to_le32(AअगरCmdEventNotअगरy);
			aअगर->seqnum = cpu_to_le32(0xFFFFFFFF);
			((__le32 *)aअगर->data)[0] = cpu_to_le32(AअगरEnExpEvent);
			((__le32 *)aअगर->data)[1] = cpu_to_le32(AअगरExeFirmwarePanic);
			((__le32 *)aअगर->data)[2] = cpu_to_le32(AअगरHighPriority);
			((__le32 *)aअगर->data)[3] = cpu_to_le32(BlinkLED);

			/*
			 * Put the FIB onto the
			 * fibctx's fibs
			 */
			list_add_tail(&fib->fiblink, &fibctx->fib_list);
			fibctx->count++;
			/*
			 * Set the event to wake up the
			 * thपढ़ो that will रुकोing.
			 */
			complete(&fibctx->completion);
		पूर्ण अन्यथा अणु
			prपूर्णांकk(KERN_WARNING "aifd: didn't allocate NewFib.\n");
			kमुक्त(fib);
			kमुक्त(hw_fib);
		पूर्ण
		entry = entry->next;
	पूर्ण

	spin_unlock_irqrestore(&aac->fib_lock, flagv);

	अगर (BlinkLED < 0) अणु
		prपूर्णांकk(KERN_ERR "%s: Host adapter is dead (or got a PCI error) %d\n",
				aac->name, BlinkLED);
		जाओ out;
	पूर्ण

	prपूर्णांकk(KERN_ERR "%s: Host adapter BLINK LED 0x%x\n", aac->name, BlinkLED);

out:
	aac->in_reset = 0;
	वापस BlinkLED;
पूर्ण

अटल अंतरभूत पूर्णांक is_safw_raid_volume(काष्ठा aac_dev *aac, पूर्णांक bus, पूर्णांक target)
अणु
	वापस bus == CONTAINER_CHANNEL && target < aac->maximum_num_containers;
पूर्ण

अटल काष्ठा scsi_device *aac_lookup_safw_scsi_device(काष्ठा aac_dev *dev,
								पूर्णांक bus,
								पूर्णांक target)
अणु
	अगर (bus != CONTAINER_CHANNEL)
		bus = aac_phys_to_logical(bus);

	वापस scsi_device_lookup(dev->scsi_host_ptr, bus, target, 0);
पूर्ण

अटल पूर्णांक aac_add_safw_device(काष्ठा aac_dev *dev, पूर्णांक bus, पूर्णांक target)
अणु
	अगर (bus != CONTAINER_CHANNEL)
		bus = aac_phys_to_logical(bus);

	वापस scsi_add_device(dev->scsi_host_ptr, bus, target, 0);
पूर्ण

अटल व्योम aac_put_safw_scsi_device(काष्ठा scsi_device *sdev)
अणु
	अगर (sdev)
		scsi_device_put(sdev);
पूर्ण

अटल व्योम aac_हटाओ_safw_device(काष्ठा aac_dev *dev, पूर्णांक bus, पूर्णांक target)
अणु
	काष्ठा scsi_device *sdev;

	sdev = aac_lookup_safw_scsi_device(dev, bus, target);
	scsi_हटाओ_device(sdev);
	aac_put_safw_scsi_device(sdev);
पूर्ण

अटल अंतरभूत पूर्णांक aac_is_safw_scan_count_equal(काष्ठा aac_dev *dev,
	पूर्णांक bus, पूर्णांक target)
अणु
	वापस dev->hba_map[bus][target].scan_counter == dev->scan_counter;
पूर्ण

अटल पूर्णांक aac_is_safw_target_valid(काष्ठा aac_dev *dev, पूर्णांक bus, पूर्णांक target)
अणु
	अगर (is_safw_raid_volume(dev, bus, target))
		वापस dev->fsa_dev[target].valid;
	अन्यथा
		वापस aac_is_safw_scan_count_equal(dev, bus, target);
पूर्ण

अटल पूर्णांक aac_is_safw_device_exposed(काष्ठा aac_dev *dev, पूर्णांक bus, पूर्णांक target)
अणु
	पूर्णांक is_exposed = 0;
	काष्ठा scsi_device *sdev;

	sdev = aac_lookup_safw_scsi_device(dev, bus, target);
	अगर (sdev)
		is_exposed = 1;
	aac_put_safw_scsi_device(sdev);

	वापस is_exposed;
पूर्ण

अटल पूर्णांक aac_update_safw_host_devices(काष्ठा aac_dev *dev)
अणु
	पूर्णांक i;
	पूर्णांक bus;
	पूर्णांक target;
	पूर्णांक is_exposed = 0;
	पूर्णांक rcode = 0;

	rcode = aac_setup_safw_adapter(dev);
	अगर (unlikely(rcode < 0)) अणु
		जाओ out;
	पूर्ण

	क्रम (i = 0; i < AAC_BUS_TARGET_LOOP; i++) अणु

		bus = get_bus_number(i);
		target = get_target_number(i);

		is_exposed = aac_is_safw_device_exposed(dev, bus, target);

		अगर (aac_is_safw_target_valid(dev, bus, target) && !is_exposed)
			aac_add_safw_device(dev, bus, target);
		अन्यथा अगर (!aac_is_safw_target_valid(dev, bus, target) &&
								is_exposed)
			aac_हटाओ_safw_device(dev, bus, target);
	पूर्ण
out:
	वापस rcode;
पूर्ण

अटल पूर्णांक aac_scan_safw_host(काष्ठा aac_dev *dev)
अणु
	पूर्णांक rcode = 0;

	rcode = aac_update_safw_host_devices(dev);
	अगर (rcode)
		aac_schedule_safw_scan_worker(dev);

	वापस rcode;
पूर्ण

पूर्णांक aac_scan_host(काष्ठा aac_dev *dev)
अणु
	पूर्णांक rcode = 0;

	mutex_lock(&dev->scan_mutex);
	अगर (dev->sa_firmware)
		rcode = aac_scan_safw_host(dev);
	अन्यथा
		scsi_scan_host(dev->scsi_host_ptr);
	mutex_unlock(&dev->scan_mutex);

	वापस rcode;
पूर्ण

व्योम aac_src_reinit_aअगर_worker(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा aac_dev *dev = container_of(to_delayed_work(work),
				काष्ठा aac_dev, src_reinit_aअगर_worker);

	रुको_event(dev->scsi_host_ptr->host_रुको,
			!scsi_host_in_recovery(dev->scsi_host_ptr));
	aac_reinit_aअगर(dev, dev->cardtype);
पूर्ण

/**
 *	aac_handle_sa_aअगर -	Handle a message from the firmware
 *	@dev: Which adapter this fib is from
 *	@fibptr: Poपूर्णांकer to fibptr from adapter
 *
 *	This routine handles a driver notअगरy fib from the adapter and
 *	dispatches it to the appropriate routine क्रम handling.
 */
अटल व्योम aac_handle_sa_aअगर(काष्ठा aac_dev *dev, काष्ठा fib *fibptr)
अणु
	पूर्णांक i;
	u32 events = 0;

	अगर (fibptr->hbacmd_size & SA_AIF_HOTPLUG)
		events = SA_AIF_HOTPLUG;
	अन्यथा अगर (fibptr->hbacmd_size & SA_AIF_HARDWARE)
		events = SA_AIF_HARDWARE;
	अन्यथा अगर (fibptr->hbacmd_size & SA_AIF_PDEV_CHANGE)
		events = SA_AIF_PDEV_CHANGE;
	अन्यथा अगर (fibptr->hbacmd_size & SA_AIF_LDEV_CHANGE)
		events = SA_AIF_LDEV_CHANGE;
	अन्यथा अगर (fibptr->hbacmd_size & SA_AIF_BPSTAT_CHANGE)
		events = SA_AIF_BPSTAT_CHANGE;
	अन्यथा अगर (fibptr->hbacmd_size & SA_AIF_BPCFG_CHANGE)
		events = SA_AIF_BPCFG_CHANGE;

	चयन (events) अणु
	हाल SA_AIF_HOTPLUG:
	हाल SA_AIF_HARDWARE:
	हाल SA_AIF_PDEV_CHANGE:
	हाल SA_AIF_LDEV_CHANGE:
	हाल SA_AIF_BPCFG_CHANGE:

		aac_scan_host(dev);

		अवरोध;

	हाल SA_AIF_BPSTAT_CHANGE:
		/* currently करो nothing */
		अवरोध;
	पूर्ण

	क्रम (i = 1; i <= 10; ++i) अणु
		events = src_पढ़ोl(dev, MUnit.IDR);
		अगर (events & (1<<23)) अणु
			pr_warn(" AIF not cleared by firmware - %d/%d)\n",
				i, 10);
			ssleep(1);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक get_fib_count(काष्ठा aac_dev *dev)
अणु
	अचिन्हित पूर्णांक num = 0;
	काष्ठा list_head *entry;
	अचिन्हित दीर्घ flagv;

	/*
	 * Warning: no sleep allowed जबतक
	 * holding spinlock. We take the estimate
	 * and pre-allocate a set of fibs outside the
	 * lock.
	 */
	num = le32_to_cpu(dev->init->r7.adapter_fibs_size)
			/ माप(काष्ठा hw_fib); /* some extra */
	spin_lock_irqsave(&dev->fib_lock, flagv);
	entry = dev->fib_list.next;
	जबतक (entry != &dev->fib_list) अणु
		entry = entry->next;
		++num;
	पूर्ण
	spin_unlock_irqrestore(&dev->fib_lock, flagv);

	वापस num;
पूर्ण

अटल पूर्णांक fillup_pools(काष्ठा aac_dev *dev, काष्ठा hw_fib **hw_fib_pool,
						काष्ठा fib **fib_pool,
						अचिन्हित पूर्णांक num)
अणु
	काष्ठा hw_fib **hw_fib_p;
	काष्ठा fib **fib_p;

	hw_fib_p = hw_fib_pool;
	fib_p = fib_pool;
	जबतक (hw_fib_p < &hw_fib_pool[num]) अणु
		*(hw_fib_p) = kदो_स्मृति(माप(काष्ठा hw_fib), GFP_KERNEL);
		अगर (!(*(hw_fib_p++))) अणु
			--hw_fib_p;
			अवरोध;
		पूर्ण

		*(fib_p) = kदो_स्मृति(माप(काष्ठा fib), GFP_KERNEL);
		अगर (!(*(fib_p++))) अणु
			kमुक्त(*(--hw_fib_p));
			अवरोध;
		पूर्ण
	पूर्ण

	/*
	 * Get the actual number of allocated fibs
	 */
	num = hw_fib_p - hw_fib_pool;
	वापस num;
पूर्ण

अटल व्योम wakeup_fibctx_thपढ़ोs(काष्ठा aac_dev *dev,
						काष्ठा hw_fib **hw_fib_pool,
						काष्ठा fib **fib_pool,
						काष्ठा fib *fib,
						काष्ठा hw_fib *hw_fib,
						अचिन्हित पूर्णांक num)
अणु
	अचिन्हित दीर्घ flagv;
	काष्ठा list_head *entry;
	काष्ठा hw_fib **hw_fib_p;
	काष्ठा fib **fib_p;
	u32 समय_now, समय_last;
	काष्ठा hw_fib *hw_newfib;
	काष्ठा fib *newfib;
	काष्ठा aac_fib_context *fibctx;

	समय_now = jअगरfies/HZ;
	spin_lock_irqsave(&dev->fib_lock, flagv);
	entry = dev->fib_list.next;
	/*
	 * For each Context that is on the
	 * fibctxList, make a copy of the
	 * fib, and then set the event to wake up the
	 * thपढ़ो that is रुकोing क्रम it.
	 */

	hw_fib_p = hw_fib_pool;
	fib_p = fib_pool;
	जबतक (entry != &dev->fib_list) अणु
		/*
		 * Extract the fibctx
		 */
		fibctx = list_entry(entry, काष्ठा aac_fib_context,
				next);
		/*
		 * Check अगर the queue is getting
		 * backlogged
		 */
		अगर (fibctx->count > 20) अणु
			/*
			 * It's *not* jअगरfies folks,
			 * but jअगरfies / HZ so करो not
			 * panic ...
			 */
			समय_last = fibctx->jअगरfies;
			/*
			 * Has it been > 2 minutes
			 * since the last पढ़ो off
			 * the queue?
			 */
			अगर ((समय_now - समय_last) > aअगर_समयout) अणु
				entry = entry->next;
				aac_बंद_fib_context(dev, fibctx);
				जारी;
			पूर्ण
		पूर्ण
		/*
		 * Warning: no sleep allowed जबतक
		 * holding spinlock
		 */
		अगर (hw_fib_p >= &hw_fib_pool[num]) अणु
			pr_warn("aifd: didn't allocate NewFib\n");
			entry = entry->next;
			जारी;
		पूर्ण

		hw_newfib = *hw_fib_p;
		*(hw_fib_p++) = शून्य;
		newfib = *fib_p;
		*(fib_p++) = शून्य;
		/*
		 * Make the copy of the FIB
		 */
		स_नकल(hw_newfib, hw_fib, माप(काष्ठा hw_fib));
		स_नकल(newfib, fib, माप(काष्ठा fib));
		newfib->hw_fib_va = hw_newfib;
		/*
		 * Put the FIB onto the
		 * fibctx's fibs
		 */
		list_add_tail(&newfib->fiblink, &fibctx->fib_list);
		fibctx->count++;
		/*
		 * Set the event to wake up the
		 * thपढ़ो that is रुकोing.
		 */
		complete(&fibctx->completion);

		entry = entry->next;
	पूर्ण
	/*
	 *	Set the status of this FIB
	 */
	*(__le32 *)hw_fib->data = cpu_to_le32(ST_OK);
	aac_fib_adapter_complete(fib, माप(u32));
	spin_unlock_irqrestore(&dev->fib_lock, flagv);

पूर्ण

अटल व्योम aac_process_events(काष्ठा aac_dev *dev)
अणु
	काष्ठा hw_fib *hw_fib;
	काष्ठा fib *fib;
	अचिन्हित दीर्घ flags;
	spinlock_t *t_lock;

	t_lock = dev->queues->queue[HostNormCmdQueue].lock;
	spin_lock_irqsave(t_lock, flags);

	जबतक (!list_empty(&(dev->queues->queue[HostNormCmdQueue].cmdq))) अणु
		काष्ठा list_head *entry;
		काष्ठा aac_aअगरcmd *aअगरcmd;
		अचिन्हित पूर्णांक  num;
		काष्ठा hw_fib **hw_fib_pool, **hw_fib_p;
		काष्ठा fib **fib_pool, **fib_p;

		set_current_state(TASK_RUNNING);

		entry = dev->queues->queue[HostNormCmdQueue].cmdq.next;
		list_del(entry);

		t_lock = dev->queues->queue[HostNormCmdQueue].lock;
		spin_unlock_irqrestore(t_lock, flags);

		fib = list_entry(entry, काष्ठा fib, fiblink);
		hw_fib = fib->hw_fib_va;
		अगर (dev->sa_firmware) अणु
			/* Thor AIF */
			aac_handle_sa_aअगर(dev, fib);
			aac_fib_adapter_complete(fib, (u16)माप(u32));
			जाओ मुक्त_fib;
		पूर्ण
		/*
		 *	We will process the FIB here or pass it to a
		 *	worker thपढ़ो that is TBD. We Really can't
		 *	करो anything at this poपूर्णांक since we करोn't have
		 *	anything defined क्रम this thपढ़ो to करो.
		 */
		स_रखो(fib, 0, माप(काष्ठा fib));
		fib->type = FSAFS_NTC_FIB_CONTEXT;
		fib->size = माप(काष्ठा fib);
		fib->hw_fib_va = hw_fib;
		fib->data = hw_fib->data;
		fib->dev = dev;
		/*
		 *	We only handle AअगरRequest fibs from the adapter.
		 */

		aअगरcmd = (काष्ठा aac_aअगरcmd *) hw_fib->data;
		अगर (aअगरcmd->command == cpu_to_le32(AअगरCmdDriverNotअगरy)) अणु
			/* Handle Driver Notअगरy Events */
			aac_handle_aअगर(dev, fib);
			*(__le32 *)hw_fib->data = cpu_to_le32(ST_OK);
			aac_fib_adapter_complete(fib, (u16)माप(u32));
			जाओ मुक्त_fib;
		पूर्ण
		/*
		 * The u32 here is important and पूर्णांकended. We are using
		 * 32bit wrapping समय to fit the adapter field
		 */

		/* Snअगरf events */
		अगर (aअगरcmd->command == cpu_to_le32(AअगरCmdEventNotअगरy)
		 || aअगरcmd->command == cpu_to_le32(AअगरCmdJobProgress)) अणु
			aac_handle_aअगर(dev, fib);
		पूर्ण

		/*
		 * get number of fibs to process
		 */
		num = get_fib_count(dev);
		अगर (!num)
			जाओ मुक्त_fib;

		hw_fib_pool = kदो_स्मृति_array(num, माप(काष्ठा hw_fib *),
						GFP_KERNEL);
		अगर (!hw_fib_pool)
			जाओ मुक्त_fib;

		fib_pool = kदो_स्मृति_array(num, माप(काष्ठा fib *), GFP_KERNEL);
		अगर (!fib_pool)
			जाओ मुक्त_hw_fib_pool;

		/*
		 * Fill up fib poपूर्णांकer pools with actual fibs
		 * and hw_fibs
		 */
		num = fillup_pools(dev, hw_fib_pool, fib_pool, num);
		अगर (!num)
			जाओ मुक्त_mem;

		/*
		 * wakeup the thपढ़ो that is रुकोing क्रम
		 * the response from fw (ioctl)
		 */
		wakeup_fibctx_thपढ़ोs(dev, hw_fib_pool, fib_pool,
							    fib, hw_fib, num);

मुक्त_mem:
		/* Free up the reमुख्यing resources */
		hw_fib_p = hw_fib_pool;
		fib_p = fib_pool;
		जबतक (hw_fib_p < &hw_fib_pool[num]) अणु
			kमुक्त(*hw_fib_p);
			kमुक्त(*fib_p);
			++fib_p;
			++hw_fib_p;
		पूर्ण
		kमुक्त(fib_pool);
मुक्त_hw_fib_pool:
		kमुक्त(hw_fib_pool);
मुक्त_fib:
		kमुक्त(fib);
		t_lock = dev->queues->queue[HostNormCmdQueue].lock;
		spin_lock_irqsave(t_lock, flags);
	पूर्ण
	/*
	 *	There are no more AIF's
	 */
	t_lock = dev->queues->queue[HostNormCmdQueue].lock;
	spin_unlock_irqrestore(t_lock, flags);
पूर्ण

अटल पूर्णांक aac_send_wellness_command(काष्ठा aac_dev *dev, अक्षर *wellness_str,
							u32 datasize)
अणु
	काष्ठा aac_srb *srbcmd;
	काष्ठा sgmap64 *sg64;
	dma_addr_t addr;
	अक्षर *dma_buf;
	काष्ठा fib *fibptr;
	पूर्णांक ret = -ENOMEM;
	u32 vbus, vid;

	fibptr = aac_fib_alloc(dev);
	अगर (!fibptr)
		जाओ out;

	dma_buf = dma_alloc_coherent(&dev->pdev->dev, datasize, &addr,
				     GFP_KERNEL);
	अगर (!dma_buf)
		जाओ fib_मुक्त_out;

	aac_fib_init(fibptr);

	vbus = (u32)le16_to_cpu(dev->supplement_adapter_info.virt_device_bus);
	vid = (u32)le16_to_cpu(dev->supplement_adapter_info.virt_device_target);

	srbcmd = (काष्ठा aac_srb *)fib_data(fibptr);

	srbcmd->function = cpu_to_le32(SRBF_ExecuteScsi);
	srbcmd->channel = cpu_to_le32(vbus);
	srbcmd->id = cpu_to_le32(vid);
	srbcmd->lun = 0;
	srbcmd->flags = cpu_to_le32(SRB_DataOut);
	srbcmd->समयout = cpu_to_le32(10);
	srbcmd->retry_limit = 0;
	srbcmd->cdb_size = cpu_to_le32(12);
	srbcmd->count = cpu_to_le32(datasize);

	स_रखो(srbcmd->cdb, 0, माप(srbcmd->cdb));
	srbcmd->cdb[0] = BMIC_OUT;
	srbcmd->cdb[6] = WRITE_HOST_WELLNESS;
	स_नकल(dma_buf, (अक्षर *)wellness_str, datasize);

	sg64 = (काष्ठा sgmap64 *)&srbcmd->sg;
	sg64->count = cpu_to_le32(1);
	sg64->sg[0].addr[1] = cpu_to_le32((u32)(((addr) >> 16) >> 16));
	sg64->sg[0].addr[0] = cpu_to_le32((u32)(addr & 0xffffffff));
	sg64->sg[0].count = cpu_to_le32(datasize);

	ret = aac_fib_send(ScsiPortCommand64, fibptr, माप(काष्ठा aac_srb),
				FsaNormal, 1, 1, शून्य, शून्य);

	dma_मुक्त_coherent(&dev->pdev->dev, datasize, dma_buf, addr);

	/*
	 * Do not set XferState to zero unless
	 * receives a response from F/W
	 */
	अगर (ret >= 0)
		aac_fib_complete(fibptr);

	/*
	 * FIB should be मुक्तd only after
	 * getting the response from the F/W
	 */
	अगर (ret != -ERESTARTSYS)
		जाओ fib_मुक्त_out;

out:
	वापस ret;
fib_मुक्त_out:
	aac_fib_मुक्त(fibptr);
	जाओ out;
पूर्ण

अटल पूर्णांक aac_send_safw_hosttसमय(काष्ठा aac_dev *dev, काष्ठा बारpec64 *now)
अणु
	काष्ठा पंचांग cur_पंचांग;
	अक्षर wellness_str[] = "<HW>TD\010\0\0\0\0\0\0\0\0\0DW\0\0ZZ";
	u32 datasize = माप(wellness_str);
	समय64_t local_समय;
	पूर्णांक ret = -ENODEV;

	अगर (!dev->sa_firmware)
		जाओ out;

	local_समय = (now->tv_sec - (sys_tz.tz_minuteswest * 60));
	समय64_to_पंचांग(local_समय, 0, &cur_पंचांग);
	cur_पंचांग.पंचांग_mon += 1;
	cur_पंचांग.पंचांग_year += 1900;
	wellness_str[8] = bin2bcd(cur_पंचांग.पंचांग_hour);
	wellness_str[9] = bin2bcd(cur_पंचांग.पंचांग_min);
	wellness_str[10] = bin2bcd(cur_पंचांग.पंचांग_sec);
	wellness_str[12] = bin2bcd(cur_पंचांग.पंचांग_mon);
	wellness_str[13] = bin2bcd(cur_पंचांग.पंचांग_mday);
	wellness_str[14] = bin2bcd(cur_पंचांग.पंचांग_year / 100);
	wellness_str[15] = bin2bcd(cur_पंचांग.पंचांग_year % 100);

	ret = aac_send_wellness_command(dev, wellness_str, datasize);

out:
	वापस ret;
पूर्ण

अटल पूर्णांक aac_send_hostसमय(काष्ठा aac_dev *dev, काष्ठा बारpec64 *now)
अणु
	पूर्णांक ret = -ENOMEM;
	काष्ठा fib *fibptr;
	__le32 *info;

	fibptr = aac_fib_alloc(dev);
	अगर (!fibptr)
		जाओ out;

	aac_fib_init(fibptr);
	info = (__le32 *)fib_data(fibptr);
	*info = cpu_to_le32(now->tv_sec); /* overflow in y2106 */
	ret = aac_fib_send(SendHostTime, fibptr, माप(*info), FsaNormal,
					1, 1, शून्य, शून्य);

	/*
	 * Do not set XferState to zero unless
	 * receives a response from F/W
	 */
	अगर (ret >= 0)
		aac_fib_complete(fibptr);

	/*
	 * FIB should be मुक्तd only after
	 * getting the response from the F/W
	 */
	अगर (ret != -ERESTARTSYS)
		aac_fib_मुक्त(fibptr);

out:
	वापस ret;
पूर्ण

/**
 *	aac_command_thपढ़ो	-	command processing thपढ़ो
 *	@data: Adapter to monitor
 *
 *	Waits on the commandपढ़ोy event in it's queue. When the event माला_लो set
 *	it will pull FIBs off it's queue. It will जारी to pull FIBs off
 *	until the queue is empty. When the queue is empty it will रुको क्रम
 *	more FIBs.
 */

पूर्णांक aac_command_thपढ़ो(व्योम *data)
अणु
	काष्ठा aac_dev *dev = data;
	DECLARE_WAITQUEUE(रुको, current);
	अचिन्हित दीर्घ next_jअगरfies = jअगरfies + HZ;
	अचिन्हित दीर्घ next_check_jअगरfies = next_jअगरfies;
	दीर्घ dअगरference = HZ;

	/*
	 *	We can only have one thपढ़ो per adapter क्रम AIF's.
	 */
	अगर (dev->aअगर_thपढ़ो)
		वापस -EINVAL;

	/*
	 *	Let the DPC know it has a place to send the AIF's to.
	 */
	dev->aअगर_thपढ़ो = 1;
	add_रुको_queue(&dev->queues->queue[HostNormCmdQueue].cmdपढ़ोy, &रुको);
	set_current_state(TASK_INTERRUPTIBLE);
	dprपूर्णांकk ((KERN_INFO "aac_command_thread start\n"));
	जबतक (1) अणु

		aac_process_events(dev);

		/*
		 *	Background activity
		 */
		अगर ((समय_beक्रमe(next_check_jअगरfies,next_jअगरfies))
		 && ((dअगरference = next_check_jअगरfies - jअगरfies) <= 0)) अणु
			next_check_jअगरfies = next_jअगरfies;
			अगर (aac_adapter_check_health(dev) == 0) अणु
				dअगरference = ((दीर्घ)(अचिन्हित)check_पूर्णांकerval)
					   * HZ;
				next_check_jअगरfies = jअगरfies + dअगरference;
			पूर्ण अन्यथा अगर (!dev->queues)
				अवरोध;
		पूर्ण
		अगर (!समय_beक्रमe(next_check_jअगरfies,next_jअगरfies)
		 && ((dअगरference = next_jअगरfies - jअगरfies) <= 0)) अणु
			काष्ठा बारpec64 now;
			पूर्णांक ret;

			/* Don't even try to talk to adapter अगर its sick */
			ret = aac_adapter_check_health(dev);
			अगर (ret || !dev->queues)
				अवरोध;
			next_check_jअगरfies = jअगरfies
					   + ((दीर्घ)(अचिन्हित)check_पूर्णांकerval)
					   * HZ;
			kसमय_get_real_ts64(&now);

			/* Synchronize our watches */
			अगर (((NSEC_PER_SEC - (NSEC_PER_SEC / HZ)) > now.tv_nsec)
			 && (now.tv_nsec > (NSEC_PER_SEC / HZ)))
				dअगरference = HZ + HZ / 2 -
					     now.tv_nsec / (NSEC_PER_SEC / HZ);
			अन्यथा अणु
				अगर (now.tv_nsec > NSEC_PER_SEC / 2)
					++now.tv_sec;

				अगर (dev->sa_firmware)
					ret =
					aac_send_safw_hosttसमय(dev, &now);
				अन्यथा
					ret = aac_send_hostसमय(dev, &now);

				dअगरference = (दीर्घ)(अचिन्हित)update_पूर्णांकerval*HZ;
			पूर्ण
			next_jअगरfies = jअगरfies + dअगरference;
			अगर (समय_beक्रमe(next_check_jअगरfies,next_jअगरfies))
				dअगरference = next_check_jअगरfies - jअगरfies;
		पूर्ण
		अगर (dअगरference <= 0)
			dअगरference = 1;
		set_current_state(TASK_INTERRUPTIBLE);

		अगर (kthपढ़ो_should_stop())
			अवरोध;

		/*
		 * we probably want usleep_range() here instead of the
		 * jअगरfies computation
		 */
		schedule_समयout(dअगरference);

		अगर (kthपढ़ो_should_stop())
			अवरोध;
	पूर्ण
	अगर (dev->queues)
		हटाओ_रुको_queue(&dev->queues->queue[HostNormCmdQueue].cmdपढ़ोy, &रुको);
	dev->aअगर_thपढ़ो = 0;
	वापस 0;
पूर्ण

पूर्णांक aac_acquire_irq(काष्ठा aac_dev *dev)
अणु
	पूर्णांक i;
	पूर्णांक j;
	पूर्णांक ret = 0;

	अगर (!dev->sync_mode && dev->msi_enabled && dev->max_msix > 1) अणु
		क्रम (i = 0; i < dev->max_msix; i++) अणु
			dev->aac_msix[i].vector_no = i;
			dev->aac_msix[i].dev = dev;
			अगर (request_irq(pci_irq_vector(dev->pdev, i),
					dev->a_ops.adapter_पूर्णांकr,
					0, "aacraid", &(dev->aac_msix[i]))) अणु
				prपूर्णांकk(KERN_ERR "%s%d: Failed to register IRQ for vector %d.\n",
						dev->name, dev->id, i);
				क्रम (j = 0 ; j < i ; j++)
					मुक्त_irq(pci_irq_vector(dev->pdev, j),
						 &(dev->aac_msix[j]));
				pci_disable_msix(dev->pdev);
				ret = -1;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		dev->aac_msix[0].vector_no = 0;
		dev->aac_msix[0].dev = dev;

		अगर (request_irq(dev->pdev->irq, dev->a_ops.adapter_पूर्णांकr,
			IRQF_SHARED, "aacraid",
			&(dev->aac_msix[0])) < 0) अणु
			अगर (dev->msi)
				pci_disable_msi(dev->pdev);
			prपूर्णांकk(KERN_ERR "%s%d: Interrupt unavailable.\n",
					dev->name, dev->id);
			ret = -1;
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

व्योम aac_मुक्त_irq(काष्ठा aac_dev *dev)
अणु
	पूर्णांक i;

	अगर (aac_is_src(dev)) अणु
		अगर (dev->max_msix > 1) अणु
			क्रम (i = 0; i < dev->max_msix; i++)
				मुक्त_irq(pci_irq_vector(dev->pdev, i),
					 &(dev->aac_msix[i]));
		पूर्ण अन्यथा अणु
			मुक्त_irq(dev->pdev->irq, &(dev->aac_msix[0]));
		पूर्ण
	पूर्ण अन्यथा अणु
		मुक्त_irq(dev->pdev->irq, dev);
	पूर्ण
	अगर (dev->msi)
		pci_disable_msi(dev->pdev);
	अन्यथा अगर (dev->max_msix > 1)
		pci_disable_msix(dev->pdev);
पूर्ण
