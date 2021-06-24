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
 *  rx.c
 *
 * Abstract: Hardware miniport क्रम Drawbridge specअगरic hardware functions.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/types.h>
#समावेश <linux/pci.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/delay.h>
#समावेश <linux/completion.h>
#समावेश <linux/समय.स>
#समावेश <linux/पूर्णांकerrupt.h>

#समावेश <scsi/scsi_host.h>

#समावेश "aacraid.h"

अटल irqवापस_t aac_rx_पूर्णांकr_producer(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा aac_dev *dev = dev_id;
	अचिन्हित दीर्घ bellbits;
	u8 पूर्णांकstat = rx_पढ़ोb(dev, MUnit.OISR);

	/*
	 *	Read mask and invert because drawbridge is reversed.
	 *	This allows us to only service पूर्णांकerrupts that have
	 *	been enabled.
	 *	Check to see अगर this is our पूर्णांकerrupt.  If it isn't just वापस
	 */
	अगर (likely(पूर्णांकstat & ~(dev->OIMR))) अणु
		bellbits = rx_पढ़ोl(dev, OutboundDoorbellReg);
		अगर (unlikely(bellbits & DoorBellPrपूर्णांकfReady)) अणु
			aac_म_लिखो(dev, पढ़ोl (&dev->IndexRegs->Mailbox[5]));
			rx_ग_लिखोl(dev, MUnit.ODR,DoorBellPrपूर्णांकfReady);
			rx_ग_लिखोl(dev, InboundDoorbellReg,DoorBellPrपूर्णांकfDone);
		पूर्ण
		अन्यथा अगर (unlikely(bellbits & DoorBellAdapterNormCmdReady)) अणु
			rx_ग_लिखोl(dev, MUnit.ODR, DoorBellAdapterNormCmdReady);
			aac_command_normal(&dev->queues->queue[HostNormCmdQueue]);
		पूर्ण
		अन्यथा अगर (likely(bellbits & DoorBellAdapterNormRespReady)) अणु
			rx_ग_लिखोl(dev, MUnit.ODR,DoorBellAdapterNormRespReady);
			aac_response_normal(&dev->queues->queue[HostNormRespQueue]);
		पूर्ण
		अन्यथा अगर (unlikely(bellbits & DoorBellAdapterNormCmdNotFull)) अणु
			rx_ग_लिखोl(dev, MUnit.ODR, DoorBellAdapterNormCmdNotFull);
		पूर्ण
		अन्यथा अगर (unlikely(bellbits & DoorBellAdapterNormRespNotFull)) अणु
			rx_ग_लिखोl(dev, MUnit.ODR, DoorBellAdapterNormCmdNotFull);
			rx_ग_लिखोl(dev, MUnit.ODR, DoorBellAdapterNormRespNotFull);
		पूर्ण
		वापस IRQ_HANDLED;
	पूर्ण
	वापस IRQ_NONE;
पूर्ण

अटल irqवापस_t aac_rx_पूर्णांकr_message(पूर्णांक irq, व्योम *dev_id)
अणु
	पूर्णांक isAअगर, isFastResponse, isSpecial;
	काष्ठा aac_dev *dev = dev_id;
	u32 Index = rx_पढ़ोl(dev, MUnit.OutboundQueue);
	अगर (unlikely(Index == 0xFFFFFFFFL))
		Index = rx_पढ़ोl(dev, MUnit.OutboundQueue);
	अगर (likely(Index != 0xFFFFFFFFL)) अणु
		करो अणु
			isAअगर = isFastResponse = isSpecial = 0;
			अगर (Index & 0x00000002L) अणु
				isAअगर = 1;
				अगर (Index == 0xFFFFFFFEL)
					isSpecial = 1;
				Index &= ~0x00000002L;
			पूर्ण अन्यथा अणु
				अगर (Index & 0x00000001L)
					isFastResponse = 1;
				Index >>= 2;
			पूर्ण
			अगर (!isSpecial) अणु
				अगर (unlikely(aac_पूर्णांकr_normal(dev,
						Index, isAअगर,
						isFastResponse, शून्य))) अणु
					rx_ग_लिखोl(dev,
						MUnit.OutboundQueue,
						Index);
					rx_ग_लिखोl(dev,
						MUnit.ODR,
						DoorBellAdapterNormRespReady);
				पूर्ण
			पूर्ण
			Index = rx_पढ़ोl(dev, MUnit.OutboundQueue);
		पूर्ण जबतक (Index != 0xFFFFFFFFL);
		वापस IRQ_HANDLED;
	पूर्ण
	वापस IRQ_NONE;
पूर्ण

/**
 *	aac_rx_disable_पूर्णांकerrupt	-	Disable पूर्णांकerrupts
 *	@dev: Adapter
 */

अटल व्योम aac_rx_disable_पूर्णांकerrupt(काष्ठा aac_dev *dev)
अणु
	rx_ग_लिखोb(dev, MUnit.OIMR, dev->OIMR = 0xff);
पूर्ण

/**
 *	aac_rx_enable_पूर्णांकerrupt_producer	-	Enable पूर्णांकerrupts
 *	@dev: Adapter
 */

अटल व्योम aac_rx_enable_पूर्णांकerrupt_producer(काष्ठा aac_dev *dev)
अणु
	rx_ग_लिखोb(dev, MUnit.OIMR, dev->OIMR = 0xfb);
पूर्ण

/**
 *	aac_rx_enable_पूर्णांकerrupt_message	-	Enable पूर्णांकerrupts
 *	@dev: Adapter
 */

अटल व्योम aac_rx_enable_पूर्णांकerrupt_message(काष्ठा aac_dev *dev)
अणु
	rx_ग_लिखोb(dev, MUnit.OIMR, dev->OIMR = 0xf7);
पूर्ण

/**
 *	rx_sync_cmd	-	send a command and रुको
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
 *	@r2: second वापस value
 *	@r3: third वापस value
 *	@r4: क्रमth वापस value
 *
 *	This routine will send a synchronous command to the adapter and रुको 
 *	क्रम its	completion.
 */

अटल पूर्णांक rx_sync_cmd(काष्ठा aac_dev *dev, u32 command,
	u32 p1, u32 p2, u32 p3, u32 p4, u32 p5, u32 p6,
	u32 *status, u32 * r1, u32 * r2, u32 * r3, u32 * r4)
अणु
	अचिन्हित दीर्घ start;
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
	rx_ग_लिखोl(dev, OutboundDoorbellReg, OUTBOUNDDOORBELL_0);
	/*
	 *	Disable करोorbell पूर्णांकerrupts
	 */
	rx_ग_लिखोb(dev, MUnit.OIMR, dev->OIMR = 0xff);
	/*
	 *	Force the completion of the mask रेजिस्टर ग_लिखो beक्रमe issuing
	 *	the पूर्णांकerrupt.
	 */
	rx_पढ़ोb (dev, MUnit.OIMR);
	/*
	 *	Signal that there is a new synch command
	 */
	rx_ग_लिखोl(dev, InboundDoorbellReg, INBOUNDDOORBELL_0);

	ok = 0;
	start = jअगरfies;

	/*
	 *	Wait up to 30 seconds
	 */
	जबतक (समय_beक्रमe(jअगरfies, start+30*HZ)) 
	अणु
		udelay(5);	/* Delay 5 microseconds to let Mon960 get info. */
		/*
		 *	Mon960 will set करोorbell0 bit when it has completed the command.
		 */
		अगर (rx_पढ़ोl(dev, OutboundDoorbellReg) & OUTBOUNDDOORBELL_0) अणु
			/*
			 *	Clear the करोorbell.
			 */
			rx_ग_लिखोl(dev, OutboundDoorbellReg, OUTBOUNDDOORBELL_0);
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
	/*
	 *	Clear the synch command करोorbell.
	 */
	rx_ग_लिखोl(dev, OutboundDoorbellReg, OUTBOUNDDOORBELL_0);
	/*
	 *	Restore पूर्णांकerrupt mask
	 */
	aac_adapter_enable_पूर्णांक(dev);
	वापस 0;

पूर्ण

/**
 *	aac_rx_पूर्णांकerrupt_adapter	-	पूर्णांकerrupt adapter
 *	@dev: Adapter
 *
 *	Send an पूर्णांकerrupt to the i960 and अवरोधpoपूर्णांक it.
 */

अटल व्योम aac_rx_पूर्णांकerrupt_adapter(काष्ठा aac_dev *dev)
अणु
	rx_sync_cmd(dev, BREAKPOINT_REQUEST, 0, 0, 0, 0, 0, 0, शून्य, शून्य, शून्य, शून्य, शून्य);
पूर्ण

/**
 *	aac_rx_notअगरy_adapter		-	send an event to the adapter
 *	@dev: Adapter
 *	@event: Event to send
 *
 *	Notअगरy the i960 that something it probably cares about has
 *	happened.
 */

अटल व्योम aac_rx_notअगरy_adapter(काष्ठा aac_dev *dev, u32 event)
अणु
	चयन (event) अणु

	हाल AdapNormCmdQue:
		rx_ग_लिखोl(dev, MUnit.IDR,INBOUNDDOORBELL_1);
		अवरोध;
	हाल HostNormRespNotFull:
		rx_ग_लिखोl(dev, MUnit.IDR,INBOUNDDOORBELL_4);
		अवरोध;
	हाल AdapNormRespQue:
		rx_ग_लिखोl(dev, MUnit.IDR,INBOUNDDOORBELL_2);
		अवरोध;
	हाल HostNormCmdNotFull:
		rx_ग_लिखोl(dev, MUnit.IDR,INBOUNDDOORBELL_3);
		अवरोध;
	हाल HostShutकरोwn:
		अवरोध;
	हाल FastIo:
		rx_ग_लिखोl(dev, MUnit.IDR,INBOUNDDOORBELL_6);
		अवरोध;
	हाल AdapPrपूर्णांकfDone:
		rx_ग_लिखोl(dev, MUnit.IDR,INBOUNDDOORBELL_5);
		अवरोध;
	शेष:
		BUG();
		अवरोध;
	पूर्ण
पूर्ण

/**
 *	aac_rx_start_adapter		-	activate adapter
 *	@dev:	Adapter
 *
 *	Start up processing on an i960 based AAC adapter
 */

अटल व्योम aac_rx_start_adapter(काष्ठा aac_dev *dev)
अणु
	जोड़ aac_init *init;

	init = dev->init;
	init->r7.host_elapsed_seconds = cpu_to_le32(kसमय_get_real_seconds());
	// We can only use a 32 bit address here
	rx_sync_cmd(dev, INIT_STRUCT_BASE_ADDRESS, (u32)(uदीर्घ)dev->init_pa,
	  0, 0, 0, 0, 0, शून्य, शून्य, शून्य, शून्य, शून्य);
पूर्ण

/**
 *	aac_rx_check_health
 *	@dev: device to check अगर healthy
 *
 *	Will attempt to determine अगर the specअगरied adapter is alive and
 *	capable of handling requests, वापसing 0 अगर alive.
 */
अटल पूर्णांक aac_rx_check_health(काष्ठा aac_dev *dev)
अणु
	u32 status = rx_पढ़ोl(dev, MUnit.OMRx[0]);

	/*
	 *	Check to see अगर the board failed any self tests.
	 */
	अगर (unlikely(status & SELF_TEST_FAILED))
		वापस -1;
	/*
	 *	Check to see अगर the board panic'd.
	 */
	अगर (unlikely(status & KERNEL_PANIC)) अणु
		अक्षर * buffer;
		काष्ठा POSTSTATUS अणु
			__le32 Post_Command;
			__le32 Post_Address;
		पूर्ण * post;
		dma_addr_t paddr, baddr;
		पूर्णांक ret;

		अगर (likely((status & 0xFF000000L) == 0xBC000000L))
			वापस (status >> 16) & 0xFF;
		buffer = dma_alloc_coherent(&dev->pdev->dev, 512, &baddr,
					    GFP_KERNEL);
		ret = -2;
		अगर (unlikely(buffer == शून्य))
			वापस ret;
		post = dma_alloc_coherent(&dev->pdev->dev,
					  माप(काष्ठा POSTSTATUS), &paddr,
					  GFP_KERNEL);
		अगर (unlikely(post == शून्य)) अणु
			dma_मुक्त_coherent(&dev->pdev->dev, 512, buffer, baddr);
			वापस ret;
		पूर्ण
		स_रखो(buffer, 0, 512);
		post->Post_Command = cpu_to_le32(COMMAND_POST_RESULTS);
		post->Post_Address = cpu_to_le32(baddr);
		rx_ग_लिखोl(dev, MUnit.IMRx[0], paddr);
		rx_sync_cmd(dev, COMMAND_POST_RESULTS, baddr, 0, 0, 0, 0, 0,
		  शून्य, शून्य, शून्य, शून्य, शून्य);
		dma_मुक्त_coherent(&dev->pdev->dev, माप(काष्ठा POSTSTATUS),
				  post, paddr);
		अगर (likely((buffer[0] == '0') && ((buffer[1] == 'x') || (buffer[1] == 'X')))) अणु
			ret = (hex_to_bin(buffer[2]) << 4) +
				hex_to_bin(buffer[3]);
		पूर्ण
		dma_मुक्त_coherent(&dev->pdev->dev, 512, buffer, baddr);
		वापस ret;
	पूर्ण
	/*
	 *	Wait क्रम the adapter to be up and running.
	 */
	अगर (unlikely(!(status & KERNEL_UP_AND_RUNNING)))
		वापस -3;
	/*
	 *	Everything is OK
	 */
	वापस 0;
पूर्ण

/**
 *	aac_rx_deliver_producer
 *	@fib: fib to issue
 *
 *	Will send a fib, वापसing 0 अगर successful.
 */
पूर्णांक aac_rx_deliver_producer(काष्ठा fib * fib)
अणु
	काष्ठा aac_dev *dev = fib->dev;
	काष्ठा aac_queue *q = &dev->queues->queue[AdapNormCmdQueue];
	u32 Index;
	अचिन्हित दीर्घ noपूर्णांकr = 0;

	aac_queue_get( dev, &Index, AdapNormCmdQueue, fib->hw_fib_va, 1, fib, &noपूर्णांकr);

	atomic_inc(&q->numpending);
	*(q->headers.producer) = cpu_to_le32(Index + 1);
	अगर (!(noपूर्णांकr & aac_config.irq_mod))
		aac_adapter_notअगरy(dev, AdapNormCmdQueue);

	वापस 0;
पूर्ण

/**
 *	aac_rx_deliver_message
 *	@fib: fib to issue
 *
 *	Will send a fib, वापसing 0 अगर successful.
 */
अटल पूर्णांक aac_rx_deliver_message(काष्ठा fib * fib)
अणु
	काष्ठा aac_dev *dev = fib->dev;
	काष्ठा aac_queue *q = &dev->queues->queue[AdapNormCmdQueue];
	u32 Index;
	u64 addr;
	अस्थिर व्योम __iomem *device;

	अचिन्हित दीर्घ count = 10000000L; /* 50 seconds */
	atomic_inc(&q->numpending);
	क्रम(;;) अणु
		Index = rx_पढ़ोl(dev, MUnit.InboundQueue);
		अगर (unlikely(Index == 0xFFFFFFFFL))
			Index = rx_पढ़ोl(dev, MUnit.InboundQueue);
		अगर (likely(Index != 0xFFFFFFFFL))
			अवरोध;
		अगर (--count == 0) अणु
			atomic_dec(&q->numpending);
			वापस -ETIMEDOUT;
		पूर्ण
		udelay(5);
	पूर्ण
	device = dev->base + Index;
	addr = fib->hw_fib_pa;
	ग_लिखोl((u32)(addr & 0xffffffff), device);
	device += माप(u32);
	ग_लिखोl((u32)(addr >> 32), device);
	device += माप(u32);
	ग_लिखोl(le16_to_cpu(fib->hw_fib_va->header.Size), device);
	rx_ग_लिखोl(dev, MUnit.InboundQueue, Index);
	वापस 0;
पूर्ण

/**
 *	aac_rx_ioremap
 *	@dev: adapter
 *	@size: mapping resize request
 *
 */
अटल पूर्णांक aac_rx_ioremap(काष्ठा aac_dev * dev, u32 size)
अणु
	अगर (!size) अणु
		iounmap(dev->regs.rx);
		वापस 0;
	पूर्ण
	dev->base = dev->regs.rx = ioremap(dev->base_start, size);
	अगर (dev->base == शून्य)
		वापस -1;
	dev->IndexRegs = &dev->regs.rx->IndexRegs;
	वापस 0;
पूर्ण

अटल पूर्णांक aac_rx_restart_adapter(काष्ठा aac_dev *dev, पूर्णांक bled, u8 reset_type)
अणु
	u32 var = 0;

	अगर (!(dev->supplement_adapter_info.supported_options2 &
	  AAC_OPTION_MU_RESET) || (bled >= 0) || (bled == -2)) अणु
		अगर (bled)
			prपूर्णांकk(KERN_ERR "%s%d: adapter kernel panic'd %x.\n",
				dev->name, dev->id, bled);
		अन्यथा अणु
			bled = aac_adapter_sync_cmd(dev, IOP_RESET_ALWAYS,
			  0, 0, 0, 0, 0, 0, &var, शून्य, शून्य, शून्य, शून्य);
			अगर (!bled && (var != 0x00000001) && (var != 0x3803000F))
				bled = -EINVAL;
		पूर्ण
		अगर (bled && (bled != -ETIMEDOUT))
			bled = aac_adapter_sync_cmd(dev, IOP_RESET,
			  0, 0, 0, 0, 0, 0, &var, शून्य, शून्य, शून्य, शून्य);

		अगर (bled && (bled != -ETIMEDOUT))
			वापस -EINVAL;
	पूर्ण
	अगर (bled && (var == 0x3803000F)) अणु /* USE_OTHER_METHOD */
		rx_ग_लिखोl(dev, MUnit.reserved2, 3);
		msleep(5000); /* Delay 5 seconds */
		var = 0x00000001;
	पूर्ण
	अगर (bled && (var != 0x00000001))
		वापस -EINVAL;
	ssleep(5);
	अगर (rx_पढ़ोl(dev, MUnit.OMRx[0]) & KERNEL_PANIC)
		वापस -ENODEV;
	अगर (startup_समयout < 300)
		startup_समयout = 300;
	वापस 0;
पूर्ण

/**
 *	aac_rx_select_comm	-	Select communications method
 *	@dev: Adapter
 *	@comm: communications method
 */

पूर्णांक aac_rx_select_comm(काष्ठा aac_dev *dev, पूर्णांक comm)
अणु
	चयन (comm) अणु
	हाल AAC_COMM_PRODUCER:
		dev->a_ops.adapter_enable_पूर्णांक = aac_rx_enable_पूर्णांकerrupt_producer;
		dev->a_ops.adapter_पूर्णांकr = aac_rx_पूर्णांकr_producer;
		dev->a_ops.adapter_deliver = aac_rx_deliver_producer;
		अवरोध;
	हाल AAC_COMM_MESSAGE:
		dev->a_ops.adapter_enable_पूर्णांक = aac_rx_enable_पूर्णांकerrupt_message;
		dev->a_ops.adapter_पूर्णांकr = aac_rx_पूर्णांकr_message;
		dev->a_ops.adapter_deliver = aac_rx_deliver_message;
		अवरोध;
	शेष:
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

/**
 *	_aac_rx_init	-	initialize an i960 based AAC card
 *	@dev: device to configure
 *
 *	Allocate and set up resources क्रम the i960 based AAC variants. The 
 *	device_पूर्णांकerface in the commregion will be allocated and linked 
 *	to the comm region.
 */

पूर्णांक _aac_rx_init(काष्ठा aac_dev *dev)
अणु
	अचिन्हित दीर्घ start;
	अचिन्हित दीर्घ status;
	पूर्णांक restart = 0;
	पूर्णांक instance = dev->id;
	स्थिर अक्षर * name = dev->name;

	अगर (aac_adapter_ioremap(dev, dev->base_size)) अणु
		prपूर्णांकk(KERN_WARNING "%s: unable to map adapter.\n", name);
		जाओ error_iounmap;
	पूर्ण

	/* Failure to reset here is an option ... */
	dev->a_ops.adapter_sync_cmd = rx_sync_cmd;
	dev->a_ops.adapter_enable_पूर्णांक = aac_rx_disable_पूर्णांकerrupt;
	dev->OIMR = status = rx_पढ़ोb (dev, MUnit.OIMR);

	अगर (((status & 0x0c) != 0x0c) || dev->init_reset) अणु
		dev->init_reset = false;
		अगर (!aac_rx_restart_adapter(dev, 0, IOP_HWSOFT_RESET)) अणु
			/* Make sure the Hardware FIFO is empty */
			जबतक ((++restart < 512) &&
			       (rx_पढ़ोl(dev, MUnit.OutboundQueue) != 0xFFFFFFFFL));
		पूर्ण
	पूर्ण

	/*
	 *	Check to see अगर the board panic'd जबतक booting.
	 */
	status = rx_पढ़ोl(dev, MUnit.OMRx[0]);
	अगर (status & KERNEL_PANIC) अणु
		अगर (aac_rx_restart_adapter(dev,
			aac_rx_check_health(dev), IOP_HWSOFT_RESET))
			जाओ error_iounmap;
		++restart;
	पूर्ण
	/*
	 *	Check to see अगर the board failed any self tests.
	 */
	status = rx_पढ़ोl(dev, MUnit.OMRx[0]);
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
	जबतक (!((status = rx_पढ़ोl(dev, MUnit.OMRx[0])) & KERNEL_UP_AND_RUNNING))
	अणु
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
			अगर (likely(!aac_rx_restart_adapter(dev,
				aac_rx_check_health(dev), IOP_HWSOFT_RESET)))
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
	dev->a_ops.adapter_पूर्णांकerrupt = aac_rx_पूर्णांकerrupt_adapter;
	dev->a_ops.adapter_disable_पूर्णांक = aac_rx_disable_पूर्णांकerrupt;
	dev->a_ops.adapter_notअगरy = aac_rx_notअगरy_adapter;
	dev->a_ops.adapter_sync_cmd = rx_sync_cmd;
	dev->a_ops.adapter_check_health = aac_rx_check_health;
	dev->a_ops.adapter_restart = aac_rx_restart_adapter;
	dev->a_ops.adapter_start = aac_rx_start_adapter;

	/*
	 *	First clear out all पूर्णांकerrupts.  Then enable the one's that we
	 *	can handle.
	 */
	aac_adapter_comm(dev, AAC_COMM_PRODUCER);
	aac_adapter_disable_पूर्णांक(dev);
	rx_ग_लिखोl(dev, MUnit.ODR, 0xffffffff);
	aac_adapter_enable_पूर्णांक(dev);

	अगर (aac_init_adapter(dev) == शून्य)
		जाओ error_iounmap;
	aac_adapter_comm(dev, dev->comm_पूर्णांकerface);
	dev->sync_mode = 0;	/* sync. mode not supported */
	dev->msi = aac_msi && !pci_enable_msi(dev->pdev);
	अगर (request_irq(dev->pdev->irq, dev->a_ops.adapter_पूर्णांकr,
			IRQF_SHARED, "aacraid", dev) < 0) अणु
		अगर (dev->msi)
			pci_disable_msi(dev->pdev);
		prपूर्णांकk(KERN_ERR "%s%d: Interrupt unavailable.\n",
			name, instance);
		जाओ error_iounmap;
	पूर्ण
	dev->dbg_base = dev->base_start;
	dev->dbg_base_mapped = dev->base;
	dev->dbg_size = dev->base_size;

	aac_adapter_enable_पूर्णांक(dev);
	/*
	 *	Tell the adapter that all is configured, and it can
	 * start accepting requests
	 */
	aac_rx_start_adapter(dev);

	वापस 0;

error_iounmap:

	वापस -1;
पूर्ण

पूर्णांक aac_rx_init(काष्ठा aac_dev *dev)
अणु
	/*
	 *	Fill in the function dispatch table.
	 */
	dev->a_ops.adapter_ioremap = aac_rx_ioremap;
	dev->a_ops.adapter_comm = aac_rx_select_comm;

	वापस _aac_rx_init(dev);
पूर्ण
