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
 *  sa.c
 *
 * Abstract: Drawbridge specअगरic support functions
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

अटल irqवापस_t aac_sa_पूर्णांकr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा aac_dev *dev = dev_id;
	अचिन्हित लघु पूर्णांकstat, mask;

	पूर्णांकstat = sa_पढ़ोw(dev, DoorbellReg_p);
	/*
	 *	Read mask and invert because drawbridge is reversed.
	 *	This allows us to only service पूर्णांकerrupts that have been enabled.
	 */
	mask = ~(sa_पढ़ोw(dev, SaDbCSR.PRISETIRQMASK));

	/* Check to see अगर this is our पूर्णांकerrupt.  If it isn't just वापस */

	अगर (पूर्णांकstat & mask) अणु
		अगर (पूर्णांकstat & Prपूर्णांकfReady) अणु
			aac_म_लिखो(dev, sa_पढ़ोl(dev, Mailbox5));
			sa_ग_लिखोw(dev, DoorbellClrReg_p, Prपूर्णांकfReady); /* clear Prपूर्णांकfReady */
			sa_ग_लिखोw(dev, DoorbellReg_s, Prपूर्णांकfDone);
		पूर्ण अन्यथा अगर (पूर्णांकstat & DOORBELL_1) अणु	// dev -> Host Normal Command Ready
			sa_ग_लिखोw(dev, DoorbellClrReg_p, DOORBELL_1);
			aac_command_normal(&dev->queues->queue[HostNormCmdQueue]);
		पूर्ण अन्यथा अगर (पूर्णांकstat & DOORBELL_2) अणु	// dev -> Host Normal Response Ready
			sa_ग_लिखोw(dev, DoorbellClrReg_p, DOORBELL_2);
			aac_response_normal(&dev->queues->queue[HostNormRespQueue]);
		पूर्ण अन्यथा अगर (पूर्णांकstat & DOORBELL_3) अणु	// dev -> Host Normal Command Not Full
			sa_ग_लिखोw(dev, DoorbellClrReg_p, DOORBELL_3);
		पूर्ण अन्यथा अगर (पूर्णांकstat & DOORBELL_4) अणु	// dev -> Host Normal Response Not Full
			sa_ग_लिखोw(dev, DoorbellClrReg_p, DOORBELL_4);
		पूर्ण
		वापस IRQ_HANDLED;
	पूर्ण
	वापस IRQ_NONE;
पूर्ण

/**
 *	aac_sa_disable_पूर्णांकerrupt	-	disable पूर्णांकerrupt
 *	@dev: Which adapter to enable.
 */

अटल व्योम aac_sa_disable_पूर्णांकerrupt (काष्ठा aac_dev *dev)
अणु
	sa_ग_लिखोw(dev, SaDbCSR.PRISETIRQMASK, 0xffff);
पूर्ण

/**
 *	aac_sa_enable_पूर्णांकerrupt	-	enable पूर्णांकerrupt
 *	@dev: Which adapter to enable.
 */

अटल व्योम aac_sa_enable_पूर्णांकerrupt (काष्ठा aac_dev *dev)
अणु
	sa_ग_लिखोw(dev, SaDbCSR.PRICLEARIRQMASK, (Prपूर्णांकfReady | DOORBELL_1 |
				DOORBELL_2 | DOORBELL_3 | DOORBELL_4));
पूर्ण

/**
 *	aac_sa_notअगरy_adapter		-	handle adapter notअगरication
 *	@dev:	Adapter that notअगरication is क्रम
 *	@event:	Event to notidy
 *
 *	Notअगरy the adapter of an event
 */
 
अटल व्योम aac_sa_notअगरy_adapter(काष्ठा aac_dev *dev, u32 event)
अणु
	चयन (event) अणु

	हाल AdapNormCmdQue:
		sa_ग_लिखोw(dev, DoorbellReg_s,DOORBELL_1);
		अवरोध;
	हाल HostNormRespNotFull:
		sa_ग_लिखोw(dev, DoorbellReg_s,DOORBELL_4);
		अवरोध;
	हाल AdapNormRespQue:
		sa_ग_लिखोw(dev, DoorbellReg_s,DOORBELL_2);
		अवरोध;
	हाल HostNormCmdNotFull:
		sa_ग_लिखोw(dev, DoorbellReg_s,DOORBELL_3);
		अवरोध;
	हाल HostShutकरोwn:
		/*
		sa_sync_cmd(dev, HOST_CRASHING, 0, 0, 0, 0, 0, 0,
		शून्य, शून्य, शून्य, शून्य, शून्य);
		*/
		अवरोध;
	हाल FastIo:
		sa_ग_लिखोw(dev, DoorbellReg_s,DOORBELL_6);
		अवरोध;
	हाल AdapPrपूर्णांकfDone:
		sa_ग_लिखोw(dev, DoorbellReg_s,DOORBELL_5);
		अवरोध;
	शेष:
		BUG();
		अवरोध;
	पूर्ण
पूर्ण


/**
 *	sa_sync_cmd	-	send a command and रुको
 *	@dev: Adapter
 *	@command: Command to execute
 *	@p1: first parameter
 *	@p2: second parameter
 *	@p3: third parameter
 *	@p4: क्रमth parameter
 *	@p5: fअगरth parameter
 *	@p6: sixth parameter
 *	@ret: adapter status
 *	@r1: first वापस value
 *	@r2: second वापस value
 *	@r3: third वापस value
 *	@r4: क्रमth वापस value
 *
 *	This routine will send a synchronous command to the adapter and रुको
 *	क्रम its	completion.
 */
अटल पूर्णांक sa_sync_cmd(काष्ठा aac_dev *dev, u32 command,
		u32 p1, u32 p2, u32 p3, u32 p4, u32 p5, u32 p6,
		u32 *ret, u32 *r1, u32 *r2, u32 *r3, u32 *r4)
अणु
	अचिन्हित दीर्घ start;
 	पूर्णांक ok;
	/*
	 *	Write the Command पूर्णांकo Mailbox 0
	 */
	sa_ग_लिखोl(dev, Mailbox0, command);
	/*
	 *	Write the parameters पूर्णांकo Mailboxes 1 - 4
	 */
	sa_ग_लिखोl(dev, Mailbox1, p1);
	sa_ग_लिखोl(dev, Mailbox2, p2);
	sa_ग_लिखोl(dev, Mailbox3, p3);
	sa_ग_लिखोl(dev, Mailbox4, p4);

	/*
	 *	Clear the synch command करोorbell to start on a clean slate.
	 */
	sa_ग_लिखोw(dev, DoorbellClrReg_p, DOORBELL_0);
	/*
	 *	Signal that there is a new synch command
	 */
	sa_ग_लिखोw(dev, DoorbellReg_s, DOORBELL_0);

	ok = 0;
	start = jअगरfies;

	जबतक(समय_beक्रमe(jअगरfies, start+30*HZ))
	अणु
		/*
		 *	Delay 5uS so that the monitor माला_लो access
		 */
		udelay(5);
		/*
		 *	Mon110 will set करोorbell0 bit when it has 
		 *	completed the command.
		 */
		अगर(sa_पढ़ोw(dev, DoorbellReg_p) & DOORBELL_0)  अणु
			ok = 1;
			अवरोध;
		पूर्ण
		msleep(1);
	पूर्ण

	अगर (ok != 1)
		वापस -ETIMEDOUT;
	/*
	 *	Clear the synch command करोorbell.
	 */
	sa_ग_लिखोw(dev, DoorbellClrReg_p, DOORBELL_0);
	/*
	 *	Pull the synch status from Mailbox 0.
	 */
	अगर (ret)
		*ret = sa_पढ़ोl(dev, Mailbox0);
	अगर (r1)
		*r1 = sa_पढ़ोl(dev, Mailbox1);
	अगर (r2)
		*r2 = sa_पढ़ोl(dev, Mailbox2);
	अगर (r3)
		*r3 = sa_पढ़ोl(dev, Mailbox3);
	अगर (r4)
		*r4 = sa_पढ़ोl(dev, Mailbox4);
	वापस 0;
पूर्ण

/**
 *	aac_sa_पूर्णांकerrupt_adapter	-	पूर्णांकerrupt an adapter
 *	@dev: Which adapter to enable.
 *
 *	Breakpoपूर्णांक an adapter.
 */
 
अटल व्योम aac_sa_पूर्णांकerrupt_adapter (काष्ठा aac_dev *dev)
अणु
	sa_sync_cmd(dev, BREAKPOINT_REQUEST, 0, 0, 0, 0, 0, 0,
			शून्य, शून्य, शून्य, शून्य, शून्य);
पूर्ण

/**
 *	aac_sa_start_adapter		-	activate adapter
 *	@dev:	Adapter
 *
 *	Start up processing on an ARM based AAC adapter
 */

अटल व्योम aac_sa_start_adapter(काष्ठा aac_dev *dev)
अणु
	जोड़ aac_init *init;
	/*
	 * Fill in the reमुख्यing pieces of the init.
	 */
	init = dev->init;
	init->r7.host_elapsed_seconds = cpu_to_le32(kसमय_get_real_seconds());
	/* We can only use a 32 bit address here */
	sa_sync_cmd(dev, INIT_STRUCT_BASE_ADDRESS, 
			(u32)(uदीर्घ)dev->init_pa, 0, 0, 0, 0, 0,
			शून्य, शून्य, शून्य, शून्य, शून्य);
पूर्ण

अटल पूर्णांक aac_sa_restart_adapter(काष्ठा aac_dev *dev, पूर्णांक bled, u8 reset_type)
अणु
	वापस -EINVAL;
पूर्ण

/**
 *	aac_sa_check_health
 *	@dev: device to check अगर healthy
 *
 *	Will attempt to determine अगर the specअगरied adapter is alive and
 *	capable of handling requests, वापसing 0 अगर alive.
 */
अटल पूर्णांक aac_sa_check_health(काष्ठा aac_dev *dev)
अणु
	दीर्घ status = sa_पढ़ोl(dev, Mailbox7);

	/*
	 *	Check to see अगर the board failed any self tests.
	 */
	अगर (status & SELF_TEST_FAILED)
		वापस -1;
	/*
	 *	Check to see अगर the board panic'd जबतक booting.
	 */
	अगर (status & KERNEL_PANIC)
		वापस -2;
	/*
	 *	Wait क्रम the adapter to be up and running. Wait up to 3 minutes
	 */
	अगर (!(status & KERNEL_UP_AND_RUNNING))
		वापस -3;
	/*
	 *	Everything is OK
	 */
	वापस 0;
पूर्ण

/**
 *	aac_sa_ioremap
 *	@dev: device to ioremap
 *	@size: mapping resize request
 *
 */
अटल पूर्णांक aac_sa_ioremap(काष्ठा aac_dev * dev, u32 size)
अणु
	अगर (!size) अणु
		iounmap(dev->regs.sa);
		वापस 0;
	पूर्ण
	dev->base = dev->regs.sa = ioremap(dev->base_start, size);
	वापस (dev->base == शून्य) ? -1 : 0;
पूर्ण

/**
 *	aac_sa_init	-	initialize an ARM based AAC card
 *	@dev: device to configure
 *
 *	Allocate and set up resources क्रम the ARM based AAC variants. The
 *	device_पूर्णांकerface in the commregion will be allocated and linked
 *	to the comm region.
 */

पूर्णांक aac_sa_init(काष्ठा aac_dev *dev)
अणु
	अचिन्हित दीर्घ start;
	अचिन्हित दीर्घ status;
	पूर्णांक instance;
	स्थिर अक्षर *name;

	instance = dev->id;
	name     = dev->name;

	/*
	 *	Fill in the function dispatch table.
	 */

	dev->a_ops.adapter_पूर्णांकerrupt = aac_sa_पूर्णांकerrupt_adapter;
	dev->a_ops.adapter_disable_पूर्णांक = aac_sa_disable_पूर्णांकerrupt;
	dev->a_ops.adapter_enable_पूर्णांक = aac_sa_enable_पूर्णांकerrupt;
	dev->a_ops.adapter_notअगरy = aac_sa_notअगरy_adapter;
	dev->a_ops.adapter_sync_cmd = sa_sync_cmd;
	dev->a_ops.adapter_check_health = aac_sa_check_health;
	dev->a_ops.adapter_restart = aac_sa_restart_adapter;
	dev->a_ops.adapter_start = aac_sa_start_adapter;
	dev->a_ops.adapter_पूर्णांकr = aac_sa_पूर्णांकr;
	dev->a_ops.adapter_deliver = aac_rx_deliver_producer;
	dev->a_ops.adapter_ioremap = aac_sa_ioremap;

	अगर (aac_sa_ioremap(dev, dev->base_size)) अणु
		prपूर्णांकk(KERN_WARNING "%s: unable to map adapter.\n", name);
		जाओ error_iounmap;
	पूर्ण

	/*
	 *	Check to see अगर the board failed any self tests.
	 */
	अगर (sa_पढ़ोl(dev, Mailbox7) & SELF_TEST_FAILED) अणु
		prपूर्णांकk(KERN_WARNING "%s%d: adapter self-test failed.\n", name, instance);
		जाओ error_iounmap;
	पूर्ण
	/*
	 *	Check to see अगर the board panic'd जबतक booting.
	 */
	अगर (sa_पढ़ोl(dev, Mailbox7) & KERNEL_PANIC) अणु
		prपूर्णांकk(KERN_WARNING "%s%d: adapter kernel panic'd.\n", name, instance);
		जाओ error_iounmap;
	पूर्ण
	start = jअगरfies;
	/*
	 *	Wait क्रम the adapter to be up and running. Wait up to 3 minutes.
	 */
	जबतक (!(sa_पढ़ोl(dev, Mailbox7) & KERNEL_UP_AND_RUNNING)) अणु
		अगर (समय_after(jअगरfies, start+startup_समयout*HZ)) अणु
			status = sa_पढ़ोl(dev, Mailbox7);
			prपूर्णांकk(KERN_WARNING "%s%d: adapter kernel failed to start, init status = %lx.\n", 
					name, instance, status);
			जाओ error_iounmap;
		पूर्ण
		msleep(1);
	पूर्ण

	/*
	 *	First clear out all पूर्णांकerrupts.  Then enable the one's that 
	 *	we can handle.
	 */
	aac_adapter_disable_पूर्णांक(dev);
	aac_adapter_enable_पूर्णांक(dev);

	अगर(aac_init_adapter(dev) == शून्य)
		जाओ error_irq;
	dev->sync_mode = 0;	/* sync. mode not supported */
	अगर (request_irq(dev->pdev->irq, dev->a_ops.adapter_पूर्णांकr,
			IRQF_SHARED, "aacraid", (व्योम *)dev) < 0) अणु
		prपूर्णांकk(KERN_WARNING "%s%d: Interrupt unavailable.\n",
			name, instance);
		जाओ error_iounmap;
	पूर्ण
	dev->dbg_base = dev->base_start;
	dev->dbg_base_mapped = dev->base;
	dev->dbg_size = dev->base_size;

	aac_adapter_enable_पूर्णांक(dev);

	/*
	 *	Tell the adapter that all is configure, and it can start 
	 *	accepting requests
	 */
	aac_sa_start_adapter(dev);
	वापस 0;

error_irq:
	aac_sa_disable_पूर्णांकerrupt(dev);
	मुक्त_irq(dev->pdev->irq, (व्योम *)dev);

error_iounmap:

	वापस -1;
पूर्ण

