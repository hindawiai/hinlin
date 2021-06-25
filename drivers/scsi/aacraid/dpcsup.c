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
 *  dpcsup.c
 *
 * Abstract: All DPC processing routines क्रम the cyclone board occur here.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/types.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/slab.h>
#समावेश <linux/completion.h>
#समावेश <linux/blkdev.h>

#समावेश "aacraid.h"

/**
 *	aac_response_normal	-	Handle command replies
 *	@q: Queue to पढ़ो from
 *
 *	This DPC routine will be run when the adapter पूर्णांकerrupts us to let us
 *	know there is a response on our normal priority queue. We will pull off
 *	all QE there are and wake up all the रुकोers beक्रमe निकासing. We will
 *	take a spinlock out on the queue beक्रमe operating on it.
 */

अचिन्हित पूर्णांक aac_response_normal(काष्ठा aac_queue * q)
अणु
	काष्ठा aac_dev * dev = q->dev;
	काष्ठा aac_entry *entry;
	काष्ठा hw_fib * hwfib;
	काष्ठा fib * fib;
	पूर्णांक consumed = 0;
	अचिन्हित दीर्घ flags, mflags;

	spin_lock_irqsave(q->lock, flags);
	/*
	 *	Keep pulling response QEs off the response queue and waking
	 *	up the रुकोers until there are no more QEs. We then वापस
	 *	back to the प्रणाली. If no response was requested we just
	 *	deallocate the Fib here and जारी.
	 */
	जबतक(aac_consumer_get(dev, q, &entry))
	अणु
		पूर्णांक fast;
		u32 index = le32_to_cpu(entry->addr);
		fast = index & 0x01;
		fib = &dev->fibs[index >> 2];
		hwfib = fib->hw_fib_va;
		
		aac_consumer_मुक्त(dev, q, HostNormRespQueue);
		/*
		 *	Remove this fib from the Outstanding I/O queue.
		 *	But only अगर it has not alपढ़ोy been समयd out.
		 *
		 *	If the fib has been समयd out alपढ़ोy, then just 
		 *	जारी. The caller has alपढ़ोy been notअगरied that
		 *	the fib समयd out.
		 */
		atomic_dec(&dev->queues->queue[AdapNormCmdQueue].numpending);

		अगर (unlikely(fib->flags & FIB_CONTEXT_FLAG_TIMED_OUT)) अणु
			spin_unlock_irqrestore(q->lock, flags);
			aac_fib_complete(fib);
			aac_fib_मुक्त(fib);
			spin_lock_irqsave(q->lock, flags);
			जारी;
		पूर्ण
		spin_unlock_irqrestore(q->lock, flags);

		अगर (fast) अणु
			/*
			 *	Doctor the fib
			 */
			*(__le32 *)hwfib->data = cpu_to_le32(ST_OK);
			hwfib->header.XferState |= cpu_to_le32(AdapterProcessed);
			fib->flags |= FIB_CONTEXT_FLAG_FASTRESP;
		पूर्ण

		FIB_COUNTER_INCREMENT(aac_config.FibRecved);

		अगर (hwfib->header.Command == cpu_to_le16(NuFileSystem))
		अणु
			__le32 *pstatus = (__le32 *)hwfib->data;
			अगर (*pstatus & cpu_to_le32(0xffff0000))
				*pstatus = cpu_to_le32(ST_OK);
		पूर्ण
		अगर (hwfib->header.XferState & cpu_to_le32(NoResponseExpected | Async)) 
		अणु
			अगर (hwfib->header.XferState & cpu_to_le32(NoResponseExpected)) अणु
				FIB_COUNTER_INCREMENT(aac_config.NoResponseRecved);
			पूर्ण अन्यथा अणु
				FIB_COUNTER_INCREMENT(aac_config.AsyncRecved);
			पूर्ण
			/*
			 *	NOTE:  we cannot touch the fib after this
			 *	    call, because it may have been deallocated.
			 */
			fib->callback(fib->callback_data, fib);
		पूर्ण अन्यथा अणु
			अचिन्हित दीर्घ flagv;
			spin_lock_irqsave(&fib->event_lock, flagv);
			अगर (!fib->करोne) अणु
				fib->करोne = 1;
				complete(&fib->event_रुको);
			पूर्ण
			spin_unlock_irqrestore(&fib->event_lock, flagv);

			spin_lock_irqsave(&dev->manage_lock, mflags);
			dev->management_fib_count--;
			spin_unlock_irqrestore(&dev->manage_lock, mflags);

			FIB_COUNTER_INCREMENT(aac_config.NormalRecved);
			अगर (fib->करोne == 2) अणु
				spin_lock_irqsave(&fib->event_lock, flagv);
				fib->करोne = 0;
				spin_unlock_irqrestore(&fib->event_lock, flagv);
				aac_fib_complete(fib);
				aac_fib_मुक्त(fib);
			पूर्ण
		पूर्ण
		consumed++;
		spin_lock_irqsave(q->lock, flags);
	पूर्ण

	अगर (consumed > aac_config.peak_fibs)
		aac_config.peak_fibs = consumed;
	अगर (consumed == 0) 
		aac_config.zero_fibs++;

	spin_unlock_irqrestore(q->lock, flags);
	वापस 0;
पूर्ण


/**
 *	aac_command_normal	-	handle commands
 *	@q: queue to process
 *
 *	This DPC routine will be queued when the adapter पूर्णांकerrupts us to 
 *	let us know there is a command on our normal priority queue. We will 
 *	pull off all QE there are and wake up all the रुकोers beक्रमe निकासing.
 *	We will take a spinlock out on the queue beक्रमe operating on it.
 */
 
अचिन्हित पूर्णांक aac_command_normal(काष्ठा aac_queue *q)
अणु
	काष्ठा aac_dev * dev = q->dev;
	काष्ठा aac_entry *entry;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(q->lock, flags);

	/*
	 *	Keep pulling response QEs off the response queue and waking
	 *	up the रुकोers until there are no more QEs. We then वापस
	 *	back to the प्रणाली.
	 */
	जबतक(aac_consumer_get(dev, q, &entry))
	अणु
		काष्ठा fib fibctx;
		काष्ठा hw_fib * hw_fib;
		u32 index;
		काष्ठा fib *fib = &fibctx;
		
		index = le32_to_cpu(entry->addr) / माप(काष्ठा hw_fib);
		hw_fib = &dev->aअगर_base_va[index];
		
		/*
		 *	Allocate a FIB at all costs. For non queued stuff
		 *	we can just use the stack so we are happy. We need
		 *	a fib object in order to manage the linked lists
		 */
		अगर (dev->aअगर_thपढ़ो)
			अगर((fib = kदो_स्मृति(माप(काष्ठा fib), GFP_ATOMIC)) == शून्य)
				fib = &fibctx;
		
		स_रखो(fib, 0, माप(काष्ठा fib));
		INIT_LIST_HEAD(&fib->fiblink);
		fib->type = FSAFS_NTC_FIB_CONTEXT;
		fib->size = माप(काष्ठा fib);
		fib->hw_fib_va = hw_fib;
		fib->data = hw_fib->data;
		fib->dev = dev;
		
				
		अगर (dev->aअगर_thपढ़ो && fib != &fibctx) अणु
		        list_add_tail(&fib->fiblink, &q->cmdq);
	 	        aac_consumer_मुक्त(dev, q, HostNormCmdQueue);
		        wake_up_पूर्णांकerruptible(&q->cmdपढ़ोy);
		पूर्ण अन्यथा अणु
	 	        aac_consumer_मुक्त(dev, q, HostNormCmdQueue);
			spin_unlock_irqrestore(q->lock, flags);
			/*
			 *	Set the status of this FIB
			 */
			*(__le32 *)hw_fib->data = cpu_to_le32(ST_OK);
			aac_fib_adapter_complete(fib, माप(u32));
			spin_lock_irqsave(q->lock, flags);
		पूर्ण		
	पूर्ण
	spin_unlock_irqrestore(q->lock, flags);
	वापस 0;
पूर्ण

/*
 *
 * aac_aअगर_callback
 * @context: the context set in the fib - here it is scsi cmd
 * @fibptr: poपूर्णांकer to the fib
 *
 * Handles the AIFs - new method (SRC)
 *
 */

अटल व्योम aac_aअगर_callback(व्योम *context, काष्ठा fib * fibptr)
अणु
	काष्ठा fib *fibctx;
	काष्ठा aac_dev *dev;
	काष्ठा aac_aअगरcmd *cmd;

	fibctx = (काष्ठा fib *)context;
	BUG_ON(fibptr == शून्य);
	dev = fibptr->dev;

	अगर ((fibptr->hw_fib_va->header.XferState &
	    cpu_to_le32(NoMoreAअगरDataAvailable)) ||
		dev->sa_firmware) अणु
		aac_fib_complete(fibptr);
		aac_fib_मुक्त(fibptr);
		वापस;
	पूर्ण

	aac_पूर्णांकr_normal(dev, 0, 1, 0, fibptr->hw_fib_va);

	aac_fib_init(fibctx);
	cmd = (काष्ठा aac_aअगरcmd *) fib_data(fibctx);
	cmd->command = cpu_to_le32(AअगरReqEvent);

	aac_fib_send(AअगरRequest,
		fibctx,
		माप(काष्ठा hw_fib)-माप(काष्ठा aac_fibhdr),
		FsaNormal,
		0, 1,
		(fib_callback)aac_aअगर_callback, fibctx);
पूर्ण


/*
 *	aac_पूर्णांकr_normal	-	Handle command replies
 *	@dev: Device
 *	@index: completion reference
 *
 *	This DPC routine will be run when the adapter पूर्णांकerrupts us to let us
 *	know there is a response on our normal priority queue. We will pull off
 *	all QE there are and wake up all the रुकोers beक्रमe निकासing.
 */
अचिन्हित पूर्णांक aac_पूर्णांकr_normal(काष्ठा aac_dev *dev, u32 index, पूर्णांक isAअगर,
	पूर्णांक isFastResponse, काष्ठा hw_fib *aअगर_fib)
अणु
	अचिन्हित दीर्घ mflags;
	dprपूर्णांकk((KERN_INFO "aac_intr_normal(%p,%x)\n", dev, index));
	अगर (isAअगर == 1) अणु	/* AIF - common */
		काष्ठा hw_fib * hw_fib;
		काष्ठा fib * fib;
		काष्ठा aac_queue *q = &dev->queues->queue[HostNormCmdQueue];
		अचिन्हित दीर्घ flags;

		/*
		 *	Allocate a FIB. For non queued stuff we can just use
		 * the stack so we are happy. We need a fib object in order to
		 * manage the linked lists.
		 */
		अगर ((!dev->aअगर_thपढ़ो)
		 || (!(fib = kzalloc(माप(काष्ठा fib),GFP_ATOMIC))))
			वापस 1;
		अगर (!(hw_fib = kzalloc(माप(काष्ठा hw_fib),GFP_ATOMIC))) अणु
			kमुक्त (fib);
			वापस 1;
		पूर्ण
		अगर (dev->sa_firmware) अणु
			fib->hbacmd_size = index;	/* store event type */
		पूर्ण अन्यथा अगर (aअगर_fib != शून्य) अणु
			स_नकल(hw_fib, aअगर_fib, माप(काष्ठा hw_fib));
		पूर्ण अन्यथा अणु
			स_नकल(hw_fib, (काष्ठा hw_fib *)
				(((uपूर्णांकptr_t)(dev->regs.sa)) + index),
				माप(काष्ठा hw_fib));
		पूर्ण
		INIT_LIST_HEAD(&fib->fiblink);
		fib->type = FSAFS_NTC_FIB_CONTEXT;
		fib->size = माप(काष्ठा fib);
		fib->hw_fib_va = hw_fib;
		fib->data = hw_fib->data;
		fib->dev = dev;
	
		spin_lock_irqsave(q->lock, flags);
		list_add_tail(&fib->fiblink, &q->cmdq);
	        wake_up_पूर्णांकerruptible(&q->cmdपढ़ोy);
		spin_unlock_irqrestore(q->lock, flags);
		वापस 1;
	पूर्ण अन्यथा अगर (isAअगर == 2) अणु	/* AIF - new (SRC) */
		काष्ठा fib *fibctx;
		काष्ठा aac_aअगरcmd *cmd;

		fibctx = aac_fib_alloc(dev);
		अगर (!fibctx)
			वापस 1;
		aac_fib_init(fibctx);

		cmd = (काष्ठा aac_aअगरcmd *) fib_data(fibctx);
		cmd->command = cpu_to_le32(AअगरReqEvent);

		वापस aac_fib_send(AअगरRequest,
			fibctx,
			माप(काष्ठा hw_fib)-माप(काष्ठा aac_fibhdr),
			FsaNormal,
			0, 1,
			(fib_callback)aac_aअगर_callback, fibctx);
	पूर्ण अन्यथा अणु
		काष्ठा fib *fib = &dev->fibs[index];
		पूर्णांक start_callback = 0;

		/*
		 *	Remove this fib from the Outstanding I/O queue.
		 *	But only अगर it has not alपढ़ोy been समयd out.
		 *
		 *	If the fib has been समयd out alपढ़ोy, then just 
		 *	जारी. The caller has alपढ़ोy been notअगरied that
		 *	the fib समयd out.
		 */
		atomic_dec(&dev->queues->queue[AdapNormCmdQueue].numpending);

		अगर (unlikely(fib->flags & FIB_CONTEXT_FLAG_TIMED_OUT)) अणु
			aac_fib_complete(fib);
			aac_fib_मुक्त(fib);
			वापस 0;
		पूर्ण

		FIB_COUNTER_INCREMENT(aac_config.FibRecved);

		अगर (fib->flags & FIB_CONTEXT_FLAG_NATIVE_HBA) अणु

			अगर (isFastResponse)
				fib->flags |= FIB_CONTEXT_FLAG_FASTRESP;

			अगर (fib->callback) अणु
				start_callback = 1;
			पूर्ण अन्यथा अणु
				अचिन्हित दीर्घ flagv;
				पूर्णांक completed = 0;

				dprपूर्णांकk((KERN_INFO "event_wait up\n"));
				spin_lock_irqsave(&fib->event_lock, flagv);
				अगर (fib->करोne == 2) अणु
					fib->करोne = 1;
					completed = 1;
				पूर्ण अन्यथा अणु
					fib->करोne = 1;
					complete(&fib->event_रुको);
				पूर्ण
				spin_unlock_irqrestore(&fib->event_lock, flagv);

				spin_lock_irqsave(&dev->manage_lock, mflags);
				dev->management_fib_count--;
				spin_unlock_irqrestore(&dev->manage_lock,
					mflags);

				FIB_COUNTER_INCREMENT(aac_config.NativeRecved);
				अगर (completed)
					aac_fib_complete(fib);
			पूर्ण
		पूर्ण अन्यथा अणु
			काष्ठा hw_fib *hwfib = fib->hw_fib_va;

			अगर (isFastResponse) अणु
				/* Doctor the fib */
				*(__le32 *)hwfib->data = cpu_to_le32(ST_OK);
				hwfib->header.XferState |=
					cpu_to_le32(AdapterProcessed);
				fib->flags |= FIB_CONTEXT_FLAG_FASTRESP;
			पूर्ण

			अगर (hwfib->header.Command ==
				cpu_to_le16(NuFileSystem)) अणु
				__le32 *pstatus = (__le32 *)hwfib->data;

				अगर (*pstatus & cpu_to_le32(0xffff0000))
					*pstatus = cpu_to_le32(ST_OK);
			पूर्ण
			अगर (hwfib->header.XferState &
				cpu_to_le32(NoResponseExpected | Async)) अणु
				अगर (hwfib->header.XferState & cpu_to_le32(
					NoResponseExpected)) अणु
					FIB_COUNTER_INCREMENT(
						aac_config.NoResponseRecved);
				पूर्ण अन्यथा अणु
					FIB_COUNTER_INCREMENT(
						aac_config.AsyncRecved);
				पूर्ण
				start_callback = 1;
			पूर्ण अन्यथा अणु
				अचिन्हित दीर्घ flagv;
				पूर्णांक completed = 0;

				dprपूर्णांकk((KERN_INFO "event_wait up\n"));
				spin_lock_irqsave(&fib->event_lock, flagv);
				अगर (fib->करोne == 2) अणु
					fib->करोne = 1;
					completed = 1;
				पूर्ण अन्यथा अणु
					fib->करोne = 1;
					complete(&fib->event_रुको);
				पूर्ण
				spin_unlock_irqrestore(&fib->event_lock, flagv);

				spin_lock_irqsave(&dev->manage_lock, mflags);
				dev->management_fib_count--;
				spin_unlock_irqrestore(&dev->manage_lock,
					mflags);

				FIB_COUNTER_INCREMENT(aac_config.NormalRecved);
				अगर (completed)
					aac_fib_complete(fib);
			पूर्ण
		पूर्ण


		अगर (start_callback) अणु
			/*
			 * NOTE:  we cannot touch the fib after this
			 *  call, because it may have been deallocated.
			 */
			अगर (likely(fib->callback && fib->callback_data)) अणु
				fib->callback(fib->callback_data, fib);
			पूर्ण अन्यथा अणु
				aac_fib_complete(fib);
				aac_fib_मुक्त(fib);
			पूर्ण

		पूर्ण
		वापस 0;
	पूर्ण
पूर्ण
