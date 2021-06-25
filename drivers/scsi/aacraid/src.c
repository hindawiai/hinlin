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
 *  src.c
 *
 * Abstract: Hardware Device Interface क्रम PMC SRC based controllers
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
#समावेश <linux/समय.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <scsi/scsi_host.h>

#समावेश "aacraid.h"

अटल पूर्णांक aac_src_get_sync_status(काष्ठा aac_dev *dev);

अटल irqवापस_t aac_src_पूर्णांकr_message(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा aac_msix_ctx *ctx;
	काष्ठा aac_dev *dev;
	अचिन्हित दीर्घ bellbits, bellbits_shअगरted;
	पूर्णांक vector_no;
	पूर्णांक isFastResponse, mode;
	u32 index, handle;

	ctx = (काष्ठा aac_msix_ctx *)dev_id;
	dev = ctx->dev;
	vector_no = ctx->vector_no;

	अगर (dev->msi_enabled) अणु
		mode = AAC_INT_MODE_MSI;
		अगर (vector_no == 0) अणु
			bellbits = src_पढ़ोl(dev, MUnit.ODR_MSI);
			अगर (bellbits & 0x40000)
				mode |= AAC_INT_MODE_AIF;
			अगर (bellbits & 0x1000)
				mode |= AAC_INT_MODE_SYNC;
		पूर्ण
	पूर्ण अन्यथा अणु
		mode = AAC_INT_MODE_INTX;
		bellbits = src_पढ़ोl(dev, MUnit.ODR_R);
		अगर (bellbits & PmDoorBellResponseSent) अणु
			bellbits = PmDoorBellResponseSent;
			src_ग_लिखोl(dev, MUnit.ODR_C, bellbits);
			src_पढ़ोl(dev, MUnit.ODR_C);
		पूर्ण अन्यथा अणु
			bellbits_shअगरted = (bellbits >> SRC_ODR_SHIFT);
			src_ग_लिखोl(dev, MUnit.ODR_C, bellbits);
			src_पढ़ोl(dev, MUnit.ODR_C);

			अगर (bellbits_shअगरted & DoorBellAअगरPending)
				mode |= AAC_INT_MODE_AIF;
			अन्यथा अगर (bellbits_shअगरted & OUTBOUNDDOORBELL_0)
				mode |= AAC_INT_MODE_SYNC;
		पूर्ण
	पूर्ण

	अगर (mode & AAC_INT_MODE_SYNC) अणु
		अचिन्हित दीर्घ sflags;
		काष्ठा list_head *entry;
		पूर्णांक send_it = 0;
		बाह्य पूर्णांक aac_sync_mode;

		अगर (!aac_sync_mode && !dev->msi_enabled) अणु
			src_ग_लिखोl(dev, MUnit.ODR_C, bellbits);
			src_पढ़ोl(dev, MUnit.ODR_C);
		पूर्ण

		अगर (dev->sync_fib) अणु
			अगर (dev->sync_fib->callback)
				dev->sync_fib->callback(dev->sync_fib->callback_data,
					dev->sync_fib);
			spin_lock_irqsave(&dev->sync_fib->event_lock, sflags);
			अगर (dev->sync_fib->flags & FIB_CONTEXT_FLAG_WAIT) अणु
				dev->management_fib_count--;
				complete(&dev->sync_fib->event_रुको);
			पूर्ण
			spin_unlock_irqrestore(&dev->sync_fib->event_lock,
						sflags);
			spin_lock_irqsave(&dev->sync_lock, sflags);
			अगर (!list_empty(&dev->sync_fib_list)) अणु
				entry = dev->sync_fib_list.next;
				dev->sync_fib = list_entry(entry,
							   काष्ठा fib,
							   fiblink);
				list_del(entry);
				send_it = 1;
			पूर्ण अन्यथा अणु
				dev->sync_fib = शून्य;
			पूर्ण
			spin_unlock_irqrestore(&dev->sync_lock, sflags);
			अगर (send_it) अणु
				aac_adapter_sync_cmd(dev, SEND_SYNCHRONOUS_FIB,
					(u32)dev->sync_fib->hw_fib_pa,
					0, 0, 0, 0, 0,
					शून्य, शून्य, शून्य, शून्य, शून्य);
			पूर्ण
		पूर्ण
		अगर (!dev->msi_enabled)
			mode = 0;

	पूर्ण

	अगर (mode & AAC_INT_MODE_AIF) अणु
		/* handle AIF */
		अगर (dev->sa_firmware) अणु
			u32 events = src_पढ़ोl(dev, MUnit.SCR0);

			aac_पूर्णांकr_normal(dev, events, 1, 0, शून्य);
			ग_लिखोl(events, &dev->IndexRegs->Mailbox[0]);
			src_ग_लिखोl(dev, MUnit.IDR, 1 << 23);
		पूर्ण अन्यथा अणु
			अगर (dev->aअगर_thपढ़ो && dev->fsa_dev)
				aac_पूर्णांकr_normal(dev, 0, 2, 0, शून्य);
		पूर्ण
		अगर (dev->msi_enabled)
			aac_src_access_devreg(dev, AAC_CLEAR_AIF_BIT);
		mode = 0;
	पूर्ण

	अगर (mode) अणु
		index = dev->host_rrq_idx[vector_no];

		क्रम (;;) अणु
			isFastResponse = 0;
			/* हटाओ toggle bit (31) */
			handle = le32_to_cpu((dev->host_rrq[index])
				& 0x7fffffff);
			/* check fast response bits (30, 1) */
			अगर (handle & 0x40000000)
				isFastResponse = 1;
			handle &= 0x0000ffff;
			अगर (handle == 0)
				अवरोध;
			handle >>= 2;
			अगर (dev->msi_enabled && dev->max_msix > 1)
				atomic_dec(&dev->rrq_outstanding[vector_no]);
			aac_पूर्णांकr_normal(dev, handle, 0, isFastResponse, शून्य);
			dev->host_rrq[index++] = 0;
			अगर (index == (vector_no + 1) * dev->vector_cap)
				index = vector_no * dev->vector_cap;
			dev->host_rrq_idx[vector_no] = index;
		पूर्ण
		mode = 0;
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

/**
 *	aac_src_disable_पूर्णांकerrupt	-	Disable पूर्णांकerrupts
 *	@dev: Adapter
 */

अटल व्योम aac_src_disable_पूर्णांकerrupt(काष्ठा aac_dev *dev)
अणु
	src_ग_लिखोl(dev, MUnit.OIMR, dev->OIMR = 0xffffffff);
पूर्ण

/**
 *	aac_src_enable_पूर्णांकerrupt_message	-	Enable पूर्णांकerrupts
 *	@dev: Adapter
 */

अटल व्योम aac_src_enable_पूर्णांकerrupt_message(काष्ठा aac_dev *dev)
अणु
	aac_src_access_devreg(dev, AAC_ENABLE_INTERRUPT);
पूर्ण

/**
 *	src_sync_cmd	-	send a command and रुको
 *	@dev: Adapter
 *	@command: Command to execute
 *	@p1: first parameter
 *	@p2: second parameter
 *	@p3: third parameter
 *	@p4: क्रमth parameter
 *	@p5: fअगरth parameter
 *	@p6: sixth parameter
 *	@status: adapter status
 *	@r1: first वापस value
 *	@r2: second वापस valu
 *	@r3: third वापस value
 *	@r4: क्रमth वापस value
 *
 *	This routine will send a synchronous command to the adapter and रुको
 *	क्रम its	completion.
 */

अटल पूर्णांक src_sync_cmd(काष्ठा aac_dev *dev, u32 command,
	u32 p1, u32 p2, u32 p3, u32 p4, u32 p5, u32 p6,
	u32 *status, u32 * r1, u32 * r2, u32 * r3, u32 * r4)
अणु
	अचिन्हित दीर्घ start;
	अचिन्हित दीर्घ delay;
	पूर्णांक ok;

	/*
	 *	Write the command पूर्णांकo Mailbox 0
	 */
	ग_लिखोl(command, &dev->IndexRegs->Mailbox[0]);
	/*
	 *	Write the parameters पूर्णांकo Mailboxes 1 - 6
	 */
	ग_लिखोl(p1, &dev->IndexRegs->Mailbox[1]);
	ग_लिखोl(p2, &dev->IndexRegs->Mailbox[2]);
	ग_लिखोl(p3, &dev->IndexRegs->Mailbox[3]);
	ग_लिखोl(p4, &dev->IndexRegs->Mailbox[4]);

	/*
	 *	Clear the synch command करोorbell to start on a clean slate.
	 */
	अगर (!dev->msi_enabled)
		src_ग_लिखोl(dev,
			   MUnit.ODR_C,
			   OUTBOUNDDOORBELL_0 << SRC_ODR_SHIFT);

	/*
	 *	Disable करोorbell पूर्णांकerrupts
	 */
	src_ग_लिखोl(dev, MUnit.OIMR, dev->OIMR = 0xffffffff);

	/*
	 *	Force the completion of the mask रेजिस्टर ग_लिखो beक्रमe issuing
	 *	the पूर्णांकerrupt.
	 */
	src_पढ़ोl(dev, MUnit.OIMR);

	/*
	 *	Signal that there is a new synch command
	 */
	src_ग_लिखोl(dev, MUnit.IDR, INBOUNDDOORBELL_0 << SRC_IDR_SHIFT);

	अगर ((!dev->sync_mode || command != SEND_SYNCHRONOUS_FIB) &&
		!dev->in_soft_reset) अणु
		ok = 0;
		start = jअगरfies;

		अगर (command == IOP_RESET_ALWAYS) अणु
			/* Wait up to 10 sec */
			delay = 10*HZ;
		पूर्ण अन्यथा अणु
			/* Wait up to 5 minutes */
			delay = 300*HZ;
		पूर्ण
		जबतक (समय_beक्रमe(jअगरfies, start+delay)) अणु
			udelay(5);	/* Delay 5 microseconds to let Mon960 get info. */
			/*
			 *	Mon960 will set करोorbell0 bit when it has completed the command.
			 */
			अगर (aac_src_get_sync_status(dev) & OUTBOUNDDOORBELL_0) अणु
				/*
				 *	Clear the करोorbell.
				 */
				अगर (dev->msi_enabled)
					aac_src_access_devreg(dev,
						AAC_CLEAR_SYNC_BIT);
				अन्यथा
					src_ग_लिखोl(dev,
						MUnit.ODR_C,
						OUTBOUNDDOORBELL_0 << SRC_ODR_SHIFT);
				ok = 1;
				अवरोध;
			पूर्ण
			/*
			 *	Yield the processor in हाल we are slow
			 */
			msleep(1);
		पूर्ण
		अगर (unlikely(ok != 1)) अणु
			/*
			 *	Restore पूर्णांकerrupt mask even though we समयd out
			 */
			aac_adapter_enable_पूर्णांक(dev);
			वापस -ETIMEDOUT;
		पूर्ण
		/*
		 *	Pull the synch status from Mailbox 0.
		 */
		अगर (status)
			*status = पढ़ोl(&dev->IndexRegs->Mailbox[0]);
		अगर (r1)
			*r1 = पढ़ोl(&dev->IndexRegs->Mailbox[1]);
		अगर (r2)
			*r2 = पढ़ोl(&dev->IndexRegs->Mailbox[2]);
		अगर (r3)
			*r3 = पढ़ोl(&dev->IndexRegs->Mailbox[3]);
		अगर (r4)
			*r4 = पढ़ोl(&dev->IndexRegs->Mailbox[4]);
		अगर (command == GET_COMM_PREFERRED_SETTINGS)
			dev->max_msix =
				पढ़ोl(&dev->IndexRegs->Mailbox[5]) & 0xFFFF;
		/*
		 *	Clear the synch command करोorbell.
		 */
		अगर (!dev->msi_enabled)
			src_ग_लिखोl(dev,
				MUnit.ODR_C,
				OUTBOUNDDOORBELL_0 << SRC_ODR_SHIFT);
	पूर्ण

	/*
	 *	Restore पूर्णांकerrupt mask
	 */
	aac_adapter_enable_पूर्णांक(dev);
	वापस 0;
पूर्ण

/**
 *	aac_src_पूर्णांकerrupt_adapter	-	पूर्णांकerrupt adapter
 *	@dev: Adapter
 *
 *	Send an पूर्णांकerrupt to the i960 and अवरोधpoपूर्णांक it.
 */

अटल व्योम aac_src_पूर्णांकerrupt_adapter(काष्ठा aac_dev *dev)
अणु
	src_sync_cmd(dev, BREAKPOINT_REQUEST,
		0, 0, 0, 0, 0, 0,
		शून्य, शून्य, शून्य, शून्य, शून्य);
पूर्ण

/**
 *	aac_src_notअगरy_adapter		-	send an event to the adapter
 *	@dev: Adapter
 *	@event: Event to send
 *
 *	Notअगरy the i960 that something it probably cares about has
 *	happened.
 */

अटल व्योम aac_src_notअगरy_adapter(काष्ठा aac_dev *dev, u32 event)
अणु
	चयन (event) अणु

	हाल AdapNormCmdQue:
		src_ग_लिखोl(dev, MUnit.ODR_C,
			INBOUNDDOORBELL_1 << SRC_ODR_SHIFT);
		अवरोध;
	हाल HostNormRespNotFull:
		src_ग_लिखोl(dev, MUnit.ODR_C,
			INBOUNDDOORBELL_4 << SRC_ODR_SHIFT);
		अवरोध;
	हाल AdapNormRespQue:
		src_ग_लिखोl(dev, MUnit.ODR_C,
			INBOUNDDOORBELL_2 << SRC_ODR_SHIFT);
		अवरोध;
	हाल HostNormCmdNotFull:
		src_ग_लिखोl(dev, MUnit.ODR_C,
			INBOUNDDOORBELL_3 << SRC_ODR_SHIFT);
		अवरोध;
	हाल FastIo:
		src_ग_लिखोl(dev, MUnit.ODR_C,
			INBOUNDDOORBELL_6 << SRC_ODR_SHIFT);
		अवरोध;
	हाल AdapPrपूर्णांकfDone:
		src_ग_लिखोl(dev, MUnit.ODR_C,
			INBOUNDDOORBELL_5 << SRC_ODR_SHIFT);
		अवरोध;
	शेष:
		BUG();
		अवरोध;
	पूर्ण
पूर्ण

/**
 *	aac_src_start_adapter		-	activate adapter
 *	@dev:	Adapter
 *
 *	Start up processing on an i960 based AAC adapter
 */

अटल व्योम aac_src_start_adapter(काष्ठा aac_dev *dev)
अणु
	जोड़ aac_init *init;
	पूर्णांक i;

	 /* reset host_rrq_idx first */
	क्रम (i = 0; i < dev->max_msix; i++) अणु
		dev->host_rrq_idx[i] = i * dev->vector_cap;
		atomic_set(&dev->rrq_outstanding[i], 0);
	पूर्ण
	atomic_set(&dev->msix_counter, 0);
	dev->fibs_pushed_no = 0;

	init = dev->init;
	अगर (dev->comm_पूर्णांकerface == AAC_COMM_MESSAGE_TYPE3) अणु
		init->r8.host_elapsed_seconds =
			cpu_to_le32(kसमय_get_real_seconds());
		src_sync_cmd(dev, INIT_STRUCT_BASE_ADDRESS,
			lower_32_bits(dev->init_pa),
			upper_32_bits(dev->init_pa),
			माप(काष्ठा _r8) +
			(AAC_MAX_HRRQ - 1) * माप(काष्ठा _rrq),
			0, 0, 0, शून्य, शून्य, शून्य, शून्य, शून्य);
	पूर्ण अन्यथा अणु
		init->r7.host_elapsed_seconds =
			cpu_to_le32(kसमय_get_real_seconds());
		// We can only use a 32 bit address here
		src_sync_cmd(dev, INIT_STRUCT_BASE_ADDRESS,
			(u32)(uदीर्घ)dev->init_pa, 0, 0, 0, 0, 0,
			शून्य, शून्य, शून्य, शून्य, शून्य);
	पूर्ण

पूर्ण

/**
 *	aac_src_check_health
 *	@dev: device to check अगर healthy
 *
 *	Will attempt to determine अगर the specअगरied adapter is alive and
 *	capable of handling requests, वापसing 0 अगर alive.
 */
अटल पूर्णांक aac_src_check_health(काष्ठा aac_dev *dev)
अणु
	u32 status = src_पढ़ोl(dev, MUnit.OMR);

	/*
	 *	Check to see अगर the board panic'd.
	 */
	अगर (unlikely(status & KERNEL_PANIC))
		जाओ err_blink;

	/*
	 *	Check to see अगर the board failed any self tests.
	 */
	अगर (unlikely(status & SELF_TEST_FAILED))
		जाओ err_out;

	/*
	 *	Check to see अगर the board failed any self tests.
	 */
	अगर (unlikely(status & MONITOR_PANIC))
		जाओ err_out;

	/*
	 *	Wait क्रम the adapter to be up and running.
	 */
	अगर (unlikely(!(status & KERNEL_UP_AND_RUNNING)))
		वापस -3;
	/*
	 *	Everything is OK
	 */
	वापस 0;

err_out:
	वापस -1;

err_blink:
	वापस (status >> 16) & 0xFF;
पूर्ण

अटल अंतरभूत u32 aac_get_vector(काष्ठा aac_dev *dev)
अणु
	वापस atomic_inc_वापस(&dev->msix_counter)%dev->max_msix;
पूर्ण

/**
 *	aac_src_deliver_message
 *	@fib: fib to issue
 *
 *	Will send a fib, वापसing 0 अगर successful.
 */
अटल पूर्णांक aac_src_deliver_message(काष्ठा fib *fib)
अणु
	काष्ठा aac_dev *dev = fib->dev;
	काष्ठा aac_queue *q = &dev->queues->queue[AdapNormCmdQueue];
	u32 fibsize;
	dma_addr_t address;
	काष्ठा aac_fib_xporthdr *pFibX;
	पूर्णांक native_hba;
#अगर !defined(ग_लिखोq)
	अचिन्हित दीर्घ flags;
#पूर्ण_अगर

	u16 vector_no;

	atomic_inc(&q->numpending);

	native_hba = (fib->flags & FIB_CONTEXT_FLAG_NATIVE_HBA) ? 1 : 0;


	अगर (dev->msi_enabled && dev->max_msix > 1 &&
		(native_hba || fib->hw_fib_va->header.Command != AअगरRequest)) अणु

		अगर ((dev->comm_पूर्णांकerface == AAC_COMM_MESSAGE_TYPE3)
			&& dev->sa_firmware)
			vector_no = aac_get_vector(dev);
		अन्यथा
			vector_no = fib->vector_no;

		अगर (native_hba) अणु
			अगर (fib->flags & FIB_CONTEXT_FLAG_NATIVE_HBA_TMF) अणु
				काष्ठा aac_hba_पंचांग_req *पंचांग_req;

				पंचांग_req = (काष्ठा aac_hba_पंचांग_req *)
						fib->hw_fib_va;
				अगर (पंचांग_req->iu_type ==
					HBA_IU_TYPE_SCSI_TM_REQ) अणु
					((काष्ठा aac_hba_पंचांग_req *)
						fib->hw_fib_va)->reply_qid
							= vector_no;
					((काष्ठा aac_hba_पंचांग_req *)
						fib->hw_fib_va)->request_id
							+= (vector_no << 16);
				पूर्ण अन्यथा अणु
					((काष्ठा aac_hba_reset_req *)
						fib->hw_fib_va)->reply_qid
							= vector_no;
					((काष्ठा aac_hba_reset_req *)
						fib->hw_fib_va)->request_id
							+= (vector_no << 16);
				पूर्ण
			पूर्ण अन्यथा अणु
				((काष्ठा aac_hba_cmd_req *)
					fib->hw_fib_va)->reply_qid
						= vector_no;
				((काष्ठा aac_hba_cmd_req *)
					fib->hw_fib_va)->request_id
						+= (vector_no << 16);
			पूर्ण
		पूर्ण अन्यथा अणु
			fib->hw_fib_va->header.Handle += (vector_no << 16);
		पूर्ण
	पूर्ण अन्यथा अणु
		vector_no = 0;
	पूर्ण

	atomic_inc(&dev->rrq_outstanding[vector_no]);

	अगर (native_hba) अणु
		address = fib->hw_fib_pa;
		fibsize = (fib->hbacmd_size + 127) / 128 - 1;
		अगर (fibsize > 31)
			fibsize = 31;
		address |= fibsize;
#अगर defined(ग_लिखोq)
		src_ग_लिखोq(dev, MUnit.IQN_L, (u64)address);
#अन्यथा
		spin_lock_irqsave(&fib->dev->iq_lock, flags);
		src_ग_लिखोl(dev, MUnit.IQN_H,
			upper_32_bits(address) & 0xffffffff);
		src_ग_लिखोl(dev, MUnit.IQN_L, address & 0xffffffff);
		spin_unlock_irqrestore(&fib->dev->iq_lock, flags);
#पूर्ण_अगर
	पूर्ण अन्यथा अणु
		अगर (dev->comm_पूर्णांकerface == AAC_COMM_MESSAGE_TYPE2 ||
			dev->comm_पूर्णांकerface == AAC_COMM_MESSAGE_TYPE3) अणु
			/* Calculate the amount to the fibsize bits */
			fibsize = (le16_to_cpu(fib->hw_fib_va->header.Size)
				+ 127) / 128 - 1;
			/* New FIB header, 32-bit */
			address = fib->hw_fib_pa;
			fib->hw_fib_va->header.StructType = FIB_MAGIC2;
			fib->hw_fib_va->header.SenderFibAddress =
				cpu_to_le32((u32)address);
			fib->hw_fib_va->header.u.TimeStamp = 0;
			WARN_ON(upper_32_bits(address) != 0L);
		पूर्ण अन्यथा अणु
			/* Calculate the amount to the fibsize bits */
			fibsize = (माप(काष्ठा aac_fib_xporthdr) +
				le16_to_cpu(fib->hw_fib_va->header.Size)
				+ 127) / 128 - 1;
			/* Fill XPORT header */
			pFibX = (काष्ठा aac_fib_xporthdr *)
				((अचिन्हित अक्षर *)fib->hw_fib_va -
				माप(काष्ठा aac_fib_xporthdr));
			pFibX->Handle = fib->hw_fib_va->header.Handle;
			pFibX->HostAddress =
				cpu_to_le64((u64)fib->hw_fib_pa);
			pFibX->Size = cpu_to_le32(
				le16_to_cpu(fib->hw_fib_va->header.Size));
			address = fib->hw_fib_pa -
				(u64)माप(काष्ठा aac_fib_xporthdr);
		पूर्ण
		अगर (fibsize > 31)
			fibsize = 31;
		address |= fibsize;

#अगर defined(ग_लिखोq)
		src_ग_लिखोq(dev, MUnit.IQ_L, (u64)address);
#अन्यथा
		spin_lock_irqsave(&fib->dev->iq_lock, flags);
		src_ग_लिखोl(dev, MUnit.IQ_H,
			upper_32_bits(address) & 0xffffffff);
		src_ग_लिखोl(dev, MUnit.IQ_L, address & 0xffffffff);
		spin_unlock_irqrestore(&fib->dev->iq_lock, flags);
#पूर्ण_अगर
	पूर्ण
	वापस 0;
पूर्ण

/**
 *	aac_src_ioremap
 *	@dev: device ioremap
 *	@size: mapping resize request
 *
 */
अटल पूर्णांक aac_src_ioremap(काष्ठा aac_dev *dev, u32 size)
अणु
	अगर (!size) अणु
		iounmap(dev->regs.src.bar1);
		dev->regs.src.bar1 = शून्य;
		iounmap(dev->regs.src.bar0);
		dev->base = dev->regs.src.bar0 = शून्य;
		वापस 0;
	पूर्ण
	dev->regs.src.bar1 = ioremap(pci_resource_start(dev->pdev, 2),
		AAC_MIN_SRC_BAR1_SIZE);
	dev->base = शून्य;
	अगर (dev->regs.src.bar1 == शून्य)
		वापस -1;
	dev->base = dev->regs.src.bar0 = ioremap(dev->base_start, size);
	अगर (dev->base == शून्य) अणु
		iounmap(dev->regs.src.bar1);
		dev->regs.src.bar1 = शून्य;
		वापस -1;
	पूर्ण
	dev->IndexRegs = &((काष्ठा src_रेजिस्टरs __iomem *)
		dev->base)->u.tupelo.IndexRegs;
	वापस 0;
पूर्ण

/**
 *  aac_srcv_ioremap
 *	@dev: device ioremap
 *	@size: mapping resize request
 *
 */
अटल पूर्णांक aac_srcv_ioremap(काष्ठा aac_dev *dev, u32 size)
अणु
	अगर (!size) अणु
		iounmap(dev->regs.src.bar0);
		dev->base = dev->regs.src.bar0 = शून्य;
		वापस 0;
	पूर्ण

	dev->regs.src.bar1 =
	ioremap(pci_resource_start(dev->pdev, 2), AAC_MIN_SRCV_BAR1_SIZE);
	dev->base = शून्य;
	अगर (dev->regs.src.bar1 == शून्य)
		वापस -1;
	dev->base = dev->regs.src.bar0 = ioremap(dev->base_start, size);
	अगर (dev->base == शून्य) अणु
		iounmap(dev->regs.src.bar1);
		dev->regs.src.bar1 = शून्य;
		वापस -1;
	पूर्ण
	dev->IndexRegs = &((काष्ठा src_रेजिस्टरs __iomem *)
		dev->base)->u.denali.IndexRegs;
	वापस 0;
पूर्ण

व्योम aac_set_पूर्णांकx_mode(काष्ठा aac_dev *dev)
अणु
	अगर (dev->msi_enabled) अणु
		aac_src_access_devreg(dev, AAC_ENABLE_INTX);
		dev->msi_enabled = 0;
		msleep(5000); /* Delay 5 seconds */
	पूर्ण
पूर्ण

अटल व्योम aac_clear_omr(काष्ठा aac_dev *dev)
अणु
	u32 omr_value = 0;

	omr_value = src_पढ़ोl(dev, MUnit.OMR);

	/*
	 * Check क्रम PCI Errors or Kernel Panic
	 */
	अगर ((omr_value == INVALID_OMR) || (omr_value & KERNEL_PANIC))
		omr_value = 0;

	/*
	 * Preserve MSIX Value अगर any
	 */
	src_ग_लिखोl(dev, MUnit.OMR, omr_value & AAC_INT_MODE_MSIX);
	src_पढ़ोl(dev, MUnit.OMR);
पूर्ण

अटल व्योम aac_dump_fw_fib_iop_reset(काष्ठा aac_dev *dev)
अणु
	__le32 supported_options3;

	अगर (!aac_fib_dump)
		वापस;

	supported_options3  = dev->supplement_adapter_info.supported_options3;
	अगर (!(supported_options3 & AAC_OPTION_SUPPORTED3_IOP_RESET_FIB_DUMP))
		वापस;

	aac_adapter_sync_cmd(dev, IOP_RESET_FW_FIB_DUMP,
			0, 0, 0,  0, 0, 0, शून्य, शून्य, शून्य, शून्य, शून्य);
पूर्ण

अटल bool aac_is_ctrl_up_and_running(काष्ठा aac_dev *dev)
अणु
	bool ctrl_up = true;
	अचिन्हित दीर्घ status, start;
	bool is_up = false;

	start = jअगरfies;
	करो अणु
		schedule();
		status = src_पढ़ोl(dev, MUnit.OMR);

		अगर (status == 0xffffffff)
			status = 0;

		अगर (status & KERNEL_BOOTING) अणु
			start = jअगरfies;
			जारी;
		पूर्ण

		अगर (समय_after(jअगरfies, start+HZ*SOFT_RESET_TIME)) अणु
			ctrl_up = false;
			अवरोध;
		पूर्ण

		is_up = status & KERNEL_UP_AND_RUNNING;

	पूर्ण जबतक (!is_up);

	वापस ctrl_up;
पूर्ण

अटल व्योम aac_src_drop_io(काष्ठा aac_dev *dev)
अणु
	अगर (!dev->soft_reset_support)
		वापस;

	aac_adapter_sync_cmd(dev, DROP_IO,
			0, 0, 0, 0, 0, 0, शून्य, शून्य, शून्य, शून्य, शून्य);
पूर्ण

अटल व्योम aac_notअगरy_fw_of_iop_reset(काष्ठा aac_dev *dev)
अणु
	aac_adapter_sync_cmd(dev, IOP_RESET_ALWAYS, 0, 0, 0, 0, 0, 0, शून्य,
						शून्य, शून्य, शून्य, शून्य);
	aac_src_drop_io(dev);
पूर्ण

अटल व्योम aac_send_iop_reset(काष्ठा aac_dev *dev)
अणु
	aac_dump_fw_fib_iop_reset(dev);

	aac_notअगरy_fw_of_iop_reset(dev);

	aac_set_पूर्णांकx_mode(dev);

	aac_clear_omr(dev);

	src_ग_लिखोl(dev, MUnit.IDR, IOP_SRC_RESET_MASK);

	msleep(5000);
पूर्ण

अटल व्योम aac_send_hardware_soft_reset(काष्ठा aac_dev *dev)
अणु
	u_पूर्णांक32_t val;

	aac_clear_omr(dev);
	val = पढ़ोl(((अक्षर *)(dev->base) + IBW_SWR_OFFSET));
	val |= 0x01;
	ग_लिखोl(val, ((अक्षर *)(dev->base) + IBW_SWR_OFFSET));
	msleep_पूर्णांकerruptible(20000);
पूर्ण

अटल पूर्णांक aac_src_restart_adapter(काष्ठा aac_dev *dev, पूर्णांक bled, u8 reset_type)
अणु
	bool is_ctrl_up;
	पूर्णांक ret = 0;

	अगर (bled < 0)
		जाओ invalid_out;

	अगर (bled)
		dev_err(&dev->pdev->dev, "adapter kernel panic'd %x.\n", bled);

	/*
	 * When there is a BlinkLED, IOP_RESET has not effect
	 */
	अगर (bled >= 2 && dev->sa_firmware && reset_type & HW_IOP_RESET)
		reset_type &= ~HW_IOP_RESET;

	dev->a_ops.adapter_enable_पूर्णांक = aac_src_disable_पूर्णांकerrupt;

	dev_err(&dev->pdev->dev, "Controller reset type is %d\n", reset_type);

	अगर (reset_type & HW_IOP_RESET) अणु
		dev_info(&dev->pdev->dev, "Issuing IOP reset\n");
		aac_send_iop_reset(dev);

		/*
		 * Creates a delay or रुको till up and running comes thru
		 */
		is_ctrl_up = aac_is_ctrl_up_and_running(dev);
		अगर (!is_ctrl_up)
			dev_err(&dev->pdev->dev, "IOP reset failed\n");
		अन्यथा अणु
			dev_info(&dev->pdev->dev, "IOP reset succeeded\n");
			जाओ set_startup;
		पूर्ण
	पूर्ण

	अगर (!dev->sa_firmware) अणु
		dev_err(&dev->pdev->dev, "ARC Reset attempt failed\n");
		ret = -ENODEV;
		जाओ out;
	पूर्ण

	अगर (reset_type & HW_SOFT_RESET) अणु
		dev_info(&dev->pdev->dev, "Issuing SOFT reset\n");
		aac_send_hardware_soft_reset(dev);
		dev->msi_enabled = 0;

		is_ctrl_up = aac_is_ctrl_up_and_running(dev);
		अगर (!is_ctrl_up) अणु
			dev_err(&dev->pdev->dev, "SOFT reset failed\n");
			ret = -ENODEV;
			जाओ out;
		पूर्ण अन्यथा
			dev_info(&dev->pdev->dev, "SOFT reset succeeded\n");
	पूर्ण

set_startup:
	अगर (startup_समयout < 300)
		startup_समयout = 300;

out:
	वापस ret;

invalid_out:
	अगर (src_पढ़ोl(dev, MUnit.OMR) & KERNEL_PANIC)
		ret = -ENODEV;
जाओ out;
पूर्ण

/**
 *	aac_src_select_comm	-	Select communications method
 *	@dev: Adapter
 *	@comm: communications method
 */
अटल पूर्णांक aac_src_select_comm(काष्ठा aac_dev *dev, पूर्णांक comm)
अणु
	चयन (comm) अणु
	हाल AAC_COMM_MESSAGE:
		dev->a_ops.adapter_पूर्णांकr = aac_src_पूर्णांकr_message;
		dev->a_ops.adapter_deliver = aac_src_deliver_message;
		अवरोध;
	शेष:
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

/**
 *  aac_src_init	-	initialize an Cardinal Frey Bar card
 *  @dev: device to configure
 *
 */

पूर्णांक aac_src_init(काष्ठा aac_dev *dev)
अणु
	अचिन्हित दीर्घ start;
	अचिन्हित दीर्घ status;
	पूर्णांक restart = 0;
	पूर्णांक instance = dev->id;
	स्थिर अक्षर *name = dev->name;

	dev->a_ops.adapter_ioremap = aac_src_ioremap;
	dev->a_ops.adapter_comm = aac_src_select_comm;

	dev->base_size = AAC_MIN_SRC_BAR0_SIZE;
	अगर (aac_adapter_ioremap(dev, dev->base_size)) अणु
		prपूर्णांकk(KERN_WARNING "%s: unable to map adapter.\n", name);
		जाओ error_iounmap;
	पूर्ण

	/* Failure to reset here is an option ... */
	dev->a_ops.adapter_sync_cmd = src_sync_cmd;
	dev->a_ops.adapter_enable_पूर्णांक = aac_src_disable_पूर्णांकerrupt;

	अगर (dev->init_reset) अणु
		dev->init_reset = false;
		अगर (!aac_src_restart_adapter(dev, 0, IOP_HWSOFT_RESET))
			++restart;
	पूर्ण

	/*
	 *	Check to see अगर the board panic'd जबतक booting.
	 */
	status = src_पढ़ोl(dev, MUnit.OMR);
	अगर (status & KERNEL_PANIC) अणु
		अगर (aac_src_restart_adapter(dev,
			aac_src_check_health(dev), IOP_HWSOFT_RESET))
			जाओ error_iounmap;
		++restart;
	पूर्ण
	/*
	 *	Check to see अगर the board failed any self tests.
	 */
	status = src_पढ़ोl(dev, MUnit.OMR);
	अगर (status & SELF_TEST_FAILED) अणु
		prपूर्णांकk(KERN_ERR "%s%d: adapter self-test failed.\n",
			dev->name, instance);
		जाओ error_iounmap;
	पूर्ण
	/*
	 *	Check to see अगर the monitor panic'd जबतक booting.
	 */
	अगर (status & MONITOR_PANIC) अणु
		prपूर्णांकk(KERN_ERR "%s%d: adapter monitor panic.\n",
			dev->name, instance);
		जाओ error_iounmap;
	पूर्ण
	start = jअगरfies;
	/*
	 *	Wait क्रम the adapter to be up and running. Wait up to 3 minutes
	 */
	जबतक (!((status = src_पढ़ोl(dev, MUnit.OMR)) &
		KERNEL_UP_AND_RUNNING)) अणु
		अगर ((restart &&
		  (status & (KERNEL_PANIC|SELF_TEST_FAILED|MONITOR_PANIC))) ||
		  समय_after(jअगरfies, start+HZ*startup_समयout)) अणु
			prपूर्णांकk(KERN_ERR "%s%d: adapter kernel failed to start, init status = %lx.\n",
					dev->name, instance, status);
			जाओ error_iounmap;
		पूर्ण
		अगर (!restart &&
		  ((status & (KERNEL_PANIC|SELF_TEST_FAILED|MONITOR_PANIC)) ||
		  समय_after(jअगरfies, start + HZ *
		  ((startup_समयout > 60)
		    ? (startup_समयout - 60)
		    : (startup_समयout / 2))))) अणु
			अगर (likely(!aac_src_restart_adapter(dev,
				aac_src_check_health(dev), IOP_HWSOFT_RESET)))
				start = jअगरfies;
			++restart;
		पूर्ण
		msleep(1);
	पूर्ण
	अगर (restart && aac_commit)
		aac_commit = 1;
	/*
	 *	Fill in the common function dispatch table.
	 */
	dev->a_ops.adapter_पूर्णांकerrupt = aac_src_पूर्णांकerrupt_adapter;
	dev->a_ops.adapter_disable_पूर्णांक = aac_src_disable_पूर्णांकerrupt;
	dev->a_ops.adapter_enable_पूर्णांक = aac_src_disable_पूर्णांकerrupt;
	dev->a_ops.adapter_notअगरy = aac_src_notअगरy_adapter;
	dev->a_ops.adapter_sync_cmd = src_sync_cmd;
	dev->a_ops.adapter_check_health = aac_src_check_health;
	dev->a_ops.adapter_restart = aac_src_restart_adapter;
	dev->a_ops.adapter_start = aac_src_start_adapter;

	/*
	 *	First clear out all पूर्णांकerrupts.  Then enable the one's that we
	 *	can handle.
	 */
	aac_adapter_comm(dev, AAC_COMM_MESSAGE);
	aac_adapter_disable_पूर्णांक(dev);
	src_ग_लिखोl(dev, MUnit.ODR_C, 0xffffffff);
	aac_adapter_enable_पूर्णांक(dev);

	अगर (aac_init_adapter(dev) == शून्य)
		जाओ error_iounmap;
	अगर (dev->comm_पूर्णांकerface != AAC_COMM_MESSAGE_TYPE1)
		जाओ error_iounmap;

	dev->msi = !pci_enable_msi(dev->pdev);

	dev->aac_msix[0].vector_no = 0;
	dev->aac_msix[0].dev = dev;

	अगर (request_irq(dev->pdev->irq, dev->a_ops.adapter_पूर्णांकr,
			IRQF_SHARED, "aacraid", &(dev->aac_msix[0]))  < 0) अणु

		अगर (dev->msi)
			pci_disable_msi(dev->pdev);

		prपूर्णांकk(KERN_ERR "%s%d: Interrupt unavailable.\n",
			name, instance);
		जाओ error_iounmap;
	पूर्ण
	dev->dbg_base = pci_resource_start(dev->pdev, 2);
	dev->dbg_base_mapped = dev->regs.src.bar1;
	dev->dbg_size = AAC_MIN_SRC_BAR1_SIZE;
	dev->a_ops.adapter_enable_पूर्णांक = aac_src_enable_पूर्णांकerrupt_message;

	aac_adapter_enable_पूर्णांक(dev);

	अगर (!dev->sync_mode) अणु
		/*
		 * Tell the adapter that all is configured, and it can
		 * start accepting requests
		 */
		aac_src_start_adapter(dev);
	पूर्ण
	वापस 0;

error_iounmap:

	वापस -1;
पूर्ण

अटल पूर्णांक aac_src_रुको_sync(काष्ठा aac_dev *dev, पूर्णांक *status)
अणु
	अचिन्हित दीर्घ start = jअगरfies;
	अचिन्हित दीर्घ usecs = 0;
	पूर्णांक delay = 5 * HZ;
	पूर्णांक rc = 1;

	जबतक (समय_beक्रमe(jअगरfies, start+delay)) अणु
		/*
		 * Delay 5 microseconds to let Mon960 get info.
		 */
		udelay(5);

		/*
		 * Mon960 will set करोorbell0 bit when it has completed the
		 * command.
		 */
		अगर (aac_src_get_sync_status(dev) & OUTBOUNDDOORBELL_0) अणु
			/*
			 * Clear: the करोorbell.
			 */
			अगर (dev->msi_enabled)
				aac_src_access_devreg(dev, AAC_CLEAR_SYNC_BIT);
			अन्यथा
				src_ग_लिखोl(dev, MUnit.ODR_C,
					OUTBOUNDDOORBELL_0 << SRC_ODR_SHIFT);
			rc = 0;

			अवरोध;
		पूर्ण

		/*
		 * Yield the processor in हाल we are slow
		 */
		usecs = 1 * USEC_PER_MSEC;
		usleep_range(usecs, usecs + 50);
	पूर्ण
	/*
	 * Pull the synch status from Mailbox 0.
	 */
	अगर (status && !rc) अणु
		status[0] = पढ़ोl(&dev->IndexRegs->Mailbox[0]);
		status[1] = पढ़ोl(&dev->IndexRegs->Mailbox[1]);
		status[2] = पढ़ोl(&dev->IndexRegs->Mailbox[2]);
		status[3] = पढ़ोl(&dev->IndexRegs->Mailbox[3]);
		status[4] = पढ़ोl(&dev->IndexRegs->Mailbox[4]);
	पूर्ण

	वापस rc;
पूर्ण

/**
 *  aac_src_soft_reset	-	perक्रमm soft reset to speed up
 *  access
 *
 *  Assumptions: That the controller is in a state where we can
 *  bring it back to lअगरe with an init काष्ठा. We can only use
 *  fast sync commands, as the समयout is 5 seconds.
 *
 *  @dev: device to configure
 *
 */

अटल पूर्णांक aac_src_soft_reset(काष्ठा aac_dev *dev)
अणु
	u32 status_omr = src_पढ़ोl(dev, MUnit.OMR);
	u32 status[5];
	पूर्णांक rc = 1;
	पूर्णांक state = 0;
	अक्षर *state_str[7] = अणु
		"GET_ADAPTER_PROPERTIES Failed",
		"GET_ADAPTER_PROPERTIES timeout",
		"SOFT_RESET not supported",
		"DROP_IO Failed",
		"DROP_IO timeout",
		"Check Health failed"
	पूर्ण;

	अगर (status_omr == INVALID_OMR)
		वापस 1;       // pcie hosed

	अगर (!(status_omr & KERNEL_UP_AND_RUNNING))
		वापस 1;       // not up and running

	/*
	 * We go पूर्णांकo soft reset mode to allow us to handle response
	 */
	dev->in_soft_reset = 1;
	dev->msi_enabled = status_omr & AAC_INT_MODE_MSIX;

	/* Get adapter properties */
	rc = aac_adapter_sync_cmd(dev, GET_ADAPTER_PROPERTIES, 0, 0, 0,
		0, 0, 0, status+0, status+1, status+2, status+3, status+4);
	अगर (rc)
		जाओ out;

	state++;
	अगर (aac_src_रुको_sync(dev, status)) अणु
		rc = 1;
		जाओ out;
	पूर्ण

	state++;
	अगर (!(status[1] & le32_to_cpu(AAC_OPT_EXTENDED) &&
		(status[4] & le32_to_cpu(AAC_EXTOPT_SOFT_RESET)))) अणु
		rc = 2;
		जाओ out;
	पूर्ण

	अगर ((status[1] & le32_to_cpu(AAC_OPT_EXTENDED)) &&
		(status[4] & le32_to_cpu(AAC_EXTOPT_SA_FIRMWARE)))
		dev->sa_firmware = 1;

	state++;
	rc = aac_adapter_sync_cmd(dev, DROP_IO, 0, 0, 0, 0, 0, 0,
		 status+0, status+1, status+2, status+3, status+4);

	अगर (rc)
		जाओ out;

	state++;
	अगर (aac_src_रुको_sync(dev, status)) अणु
		rc = 3;
		जाओ out;
	पूर्ण

	अगर (status[1])
		dev_err(&dev->pdev->dev, "%s: %d outstanding I/O pending\n",
			__func__, status[1]);

	state++;
	rc = aac_src_check_health(dev);

out:
	dev->in_soft_reset = 0;
	dev->msi_enabled = 0;
	अगर (rc)
		dev_err(&dev->pdev->dev, "%s: %s status = %d", __func__,
			state_str[state], rc);

	वापस rc;
पूर्ण
/**
 *  aac_srcv_init	-	initialize an SRCv card
 *  @dev: device to configure
 *
 */

पूर्णांक aac_srcv_init(काष्ठा aac_dev *dev)
अणु
	अचिन्हित दीर्घ start;
	अचिन्हित दीर्घ status;
	पूर्णांक restart = 0;
	पूर्णांक instance = dev->id;
	स्थिर अक्षर *name = dev->name;

	dev->a_ops.adapter_ioremap = aac_srcv_ioremap;
	dev->a_ops.adapter_comm = aac_src_select_comm;

	dev->base_size = AAC_MIN_SRCV_BAR0_SIZE;
	अगर (aac_adapter_ioremap(dev, dev->base_size)) अणु
		prपूर्णांकk(KERN_WARNING "%s: unable to map adapter.\n", name);
		जाओ error_iounmap;
	पूर्ण

	/* Failure to reset here is an option ... */
	dev->a_ops.adapter_sync_cmd = src_sync_cmd;
	dev->a_ops.adapter_enable_पूर्णांक = aac_src_disable_पूर्णांकerrupt;

	अगर (dev->init_reset) अणु
		dev->init_reset = false;
		अगर (aac_src_soft_reset(dev)) अणु
			aac_src_restart_adapter(dev, 0, IOP_HWSOFT_RESET);
			++restart;
		पूर्ण
	पूर्ण

	/*
	 *	Check to see अगर flash update is running.
	 *	Wait क्रम the adapter to be up and running. Wait up to 5 minutes
	 */
	status = src_पढ़ोl(dev, MUnit.OMR);
	अगर (status & FLASH_UPD_PENDING) अणु
		start = jअगरfies;
		करो अणु
			status = src_पढ़ोl(dev, MUnit.OMR);
			अगर (समय_after(jअगरfies, start+HZ*FWUPD_TIMEOUT)) अणु
				prपूर्णांकk(KERN_ERR "%s%d: adapter flash update failed.\n",
					dev->name, instance);
				जाओ error_iounmap;
			पूर्ण
		पूर्ण जबतक (!(status & FLASH_UPD_SUCCESS) &&
			 !(status & FLASH_UPD_FAILED));
		/* Delay 10 seconds.
		 * Because right now FW is करोing a soft reset,
		 * करो not पढ़ो scratch pad रेजिस्टर at this समय
		 */
		ssleep(10);
	पूर्ण
	/*
	 *	Check to see अगर the board panic'd जबतक booting.
	 */
	status = src_पढ़ोl(dev, MUnit.OMR);
	अगर (status & KERNEL_PANIC) अणु
		अगर (aac_src_restart_adapter(dev,
			aac_src_check_health(dev), IOP_HWSOFT_RESET))
			जाओ error_iounmap;
		++restart;
	पूर्ण
	/*
	 *	Check to see अगर the board failed any self tests.
	 */
	status = src_पढ़ोl(dev, MUnit.OMR);
	अगर (status & SELF_TEST_FAILED) अणु
		prपूर्णांकk(KERN_ERR "%s%d: adapter self-test failed.\n", dev->name, instance);
		जाओ error_iounmap;
	पूर्ण
	/*
	 *	Check to see अगर the monitor panic'd जबतक booting.
	 */
	अगर (status & MONITOR_PANIC) अणु
		prपूर्णांकk(KERN_ERR "%s%d: adapter monitor panic.\n", dev->name, instance);
		जाओ error_iounmap;
	पूर्ण

	start = jअगरfies;
	/*
	 *	Wait क्रम the adapter to be up and running. Wait up to 3 minutes
	 */
	करो अणु
		status = src_पढ़ोl(dev, MUnit.OMR);
		अगर (status == INVALID_OMR)
			status = 0;

		अगर ((restart &&
		  (status & (KERNEL_PANIC|SELF_TEST_FAILED|MONITOR_PANIC))) ||
		  समय_after(jअगरfies, start+HZ*startup_समयout)) अणु
			prपूर्णांकk(KERN_ERR "%s%d: adapter kernel failed to start, init status = %lx.\n",
					dev->name, instance, status);
			जाओ error_iounmap;
		पूर्ण
		अगर (!restart &&
		  ((status & (KERNEL_PANIC|SELF_TEST_FAILED|MONITOR_PANIC)) ||
		  समय_after(jअगरfies, start + HZ *
		  ((startup_समयout > 60)
		    ? (startup_समयout - 60)
		    : (startup_समयout / 2))))) अणु
			अगर (likely(!aac_src_restart_adapter(dev,
				aac_src_check_health(dev), IOP_HWSOFT_RESET)))
				start = jअगरfies;
			++restart;
		पूर्ण
		msleep(1);
	पूर्ण जबतक (!(status & KERNEL_UP_AND_RUNNING));

	अगर (restart && aac_commit)
		aac_commit = 1;
	/*
	 *	Fill in the common function dispatch table.
	 */
	dev->a_ops.adapter_पूर्णांकerrupt = aac_src_पूर्णांकerrupt_adapter;
	dev->a_ops.adapter_disable_पूर्णांक = aac_src_disable_पूर्णांकerrupt;
	dev->a_ops.adapter_enable_पूर्णांक = aac_src_disable_पूर्णांकerrupt;
	dev->a_ops.adapter_notअगरy = aac_src_notअगरy_adapter;
	dev->a_ops.adapter_sync_cmd = src_sync_cmd;
	dev->a_ops.adapter_check_health = aac_src_check_health;
	dev->a_ops.adapter_restart = aac_src_restart_adapter;
	dev->a_ops.adapter_start = aac_src_start_adapter;

	/*
	 *	First clear out all पूर्णांकerrupts.  Then enable the one's that we
	 *	can handle.
	 */
	aac_adapter_comm(dev, AAC_COMM_MESSAGE);
	aac_adapter_disable_पूर्णांक(dev);
	src_ग_लिखोl(dev, MUnit.ODR_C, 0xffffffff);
	aac_adapter_enable_पूर्णांक(dev);

	अगर (aac_init_adapter(dev) == शून्य)
		जाओ error_iounmap;
	अगर ((dev->comm_पूर्णांकerface != AAC_COMM_MESSAGE_TYPE2) &&
		(dev->comm_पूर्णांकerface != AAC_COMM_MESSAGE_TYPE3))
		जाओ error_iounmap;
	अगर (dev->msi_enabled)
		aac_src_access_devreg(dev, AAC_ENABLE_MSIX);

	अगर (aac_acquire_irq(dev))
		जाओ error_iounmap;

	dev->dbg_base = pci_resource_start(dev->pdev, 2);
	dev->dbg_base_mapped = dev->regs.src.bar1;
	dev->dbg_size = AAC_MIN_SRCV_BAR1_SIZE;
	dev->a_ops.adapter_enable_पूर्णांक = aac_src_enable_पूर्णांकerrupt_message;

	aac_adapter_enable_पूर्णांक(dev);

	अगर (!dev->sync_mode) अणु
		/*
		 * Tell the adapter that all is configured, and it can
		 * start accepting requests
		 */
		aac_src_start_adapter(dev);
	पूर्ण
	वापस 0;

error_iounmap:

	वापस -1;
पूर्ण

व्योम aac_src_access_devreg(काष्ठा aac_dev *dev, पूर्णांक mode)
अणु
	u_पूर्णांक32_t val;

	चयन (mode) अणु
	हाल AAC_ENABLE_INTERRUPT:
		src_ग_लिखोl(dev,
			   MUnit.OIMR,
			   dev->OIMR = (dev->msi_enabled ?
					AAC_INT_ENABLE_TYPE1_MSIX :
					AAC_INT_ENABLE_TYPE1_INTX));
		अवरोध;

	हाल AAC_DISABLE_INTERRUPT:
		src_ग_लिखोl(dev,
			   MUnit.OIMR,
			   dev->OIMR = AAC_INT_DISABLE_ALL);
		अवरोध;

	हाल AAC_ENABLE_MSIX:
		/* set bit 6 */
		val = src_पढ़ोl(dev, MUnit.IDR);
		val |= 0x40;
		src_ग_लिखोl(dev,  MUnit.IDR, val);
		src_पढ़ोl(dev, MUnit.IDR);
		/* unmask पूर्णांक. */
		val = PMC_ALL_INTERRUPT_BITS;
		src_ग_लिखोl(dev, MUnit.IOAR, val);
		val = src_पढ़ोl(dev, MUnit.OIMR);
		src_ग_लिखोl(dev,
			   MUnit.OIMR,
			   val & (~(PMC_GLOBAL_INT_BIT2 | PMC_GLOBAL_INT_BIT0)));
		अवरोध;

	हाल AAC_DISABLE_MSIX:
		/* reset bit 6 */
		val = src_पढ़ोl(dev, MUnit.IDR);
		val &= ~0x40;
		src_ग_लिखोl(dev, MUnit.IDR, val);
		src_पढ़ोl(dev, MUnit.IDR);
		अवरोध;

	हाल AAC_CLEAR_AIF_BIT:
		/* set bit 5 */
		val = src_पढ़ोl(dev, MUnit.IDR);
		val |= 0x20;
		src_ग_लिखोl(dev, MUnit.IDR, val);
		src_पढ़ोl(dev, MUnit.IDR);
		अवरोध;

	हाल AAC_CLEAR_SYNC_BIT:
		/* set bit 4 */
		val = src_पढ़ोl(dev, MUnit.IDR);
		val |= 0x10;
		src_ग_लिखोl(dev, MUnit.IDR, val);
		src_पढ़ोl(dev, MUnit.IDR);
		अवरोध;

	हाल AAC_ENABLE_INTX:
		/* set bit 7 */
		val = src_पढ़ोl(dev, MUnit.IDR);
		val |= 0x80;
		src_ग_लिखोl(dev, MUnit.IDR, val);
		src_पढ़ोl(dev, MUnit.IDR);
		/* unmask पूर्णांक. */
		val = PMC_ALL_INTERRUPT_BITS;
		src_ग_लिखोl(dev, MUnit.IOAR, val);
		src_पढ़ोl(dev, MUnit.IOAR);
		val = src_पढ़ोl(dev, MUnit.OIMR);
		src_ग_लिखोl(dev, MUnit.OIMR,
				val & (~(PMC_GLOBAL_INT_BIT2)));
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक aac_src_get_sync_status(काष्ठा aac_dev *dev)
अणु
	पूर्णांक msix_val = 0;
	पूर्णांक legacy_val = 0;

	msix_val = src_पढ़ोl(dev, MUnit.ODR_MSI) & SRC_MSI_READ_MASK ? 1 : 0;

	अगर (!dev->msi_enabled) अणु
		/*
		 * अगर Legacy पूर्णांक status indicates cmd is not complete
		 * sample MSIx रेजिस्टर to see अगर it indiactes cmd complete,
		 * अगर yes set the controller in MSIx mode and consider cmd
		 * completed
		 */
		legacy_val = src_पढ़ोl(dev, MUnit.ODR_R) >> SRC_ODR_SHIFT;
		अगर (!(legacy_val & 1) && msix_val)
			dev->msi_enabled = 1;
		वापस legacy_val;
	पूर्ण

	वापस msix_val;
पूर्ण
