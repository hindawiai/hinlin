<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Intel & MS High Precision Event Timer Implementation.
 *
 * Copyright (C) 2003 Intel Corporation
 *	Venki Pallipadi
 * (c) Copyright 2004 Hewlett-Packard Development Company, L.P.
 *	Bob Picco <robert.picco@hp.com>
 */

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/major.h>
#समावेश <linux/ioport.h>
#समावेश <linux/fcntl.h>
#समावेश <linux/init.h>
#समावेश <linux/poll.h>
#समावेश <linux/mm.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/sysctl.h>
#समावेश <linux/रुको.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/bcd.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/bitops.h>
#समावेश <linux/compat.h>
#समावेश <linux/घड़ीsource.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/slab.h>
#समावेश <linux/पन.स>
#समावेश <linux/acpi.h>
#समावेश <linux/hpet.h>
#समावेश <यंत्र/current.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/भाग64.h>

/*
 * The High Precision Event Timer driver.
 * This driver is बंदly modelled after the rtc.c driver.
 * See HPET spec revision 1.
 */
#घोषणा	HPET_USER_FREQ	(64)
#घोषणा	HPET_DRIFT	(500)

#घोषणा HPET_RANGE_SIZE		1024	/* from HPET spec */


/* WARNING -- करोn't get confused.  These macros are never used
 * to ग_लिखो the (single) counter, and rarely to पढ़ो it.
 * They're badly named; to fix, someday.
 */
#अगर BITS_PER_LONG == 64
#घोषणा	ग_लिखो_counter(V, MC)	ग_लिखोq(V, MC)
#घोषणा	पढ़ो_counter(MC)	पढ़ोq(MC)
#अन्यथा
#घोषणा	ग_लिखो_counter(V, MC)	ग_लिखोl(V, MC)
#घोषणा	पढ़ो_counter(MC)	पढ़ोl(MC)
#पूर्ण_अगर

अटल DEFINE_MUTEX(hpet_mutex); /* replaces BKL */
अटल u32 hpet_nhpet, hpet_max_freq = HPET_USER_FREQ;

/* This घड़ीsource driver currently only works on ia64 */
#अगर_घोषित CONFIG_IA64
अटल व्योम __iomem *hpet_mctr;

अटल u64 पढ़ो_hpet(काष्ठा घड़ीsource *cs)
अणु
	वापस (u64)पढ़ो_counter((व्योम __iomem *)hpet_mctr);
पूर्ण

अटल काष्ठा घड़ीsource घड़ीsource_hpet = अणु
	.name		= "hpet",
	.rating		= 250,
	.पढ़ो		= पढ़ो_hpet,
	.mask		= CLOCKSOURCE_MASK(64),
	.flags		= CLOCK_SOURCE_IS_CONTINUOUS,
पूर्ण;
अटल काष्ठा घड़ीsource *hpet_घड़ीsource;
#पूर्ण_अगर

/* A lock क्रम concurrent access by app and isr hpet activity. */
अटल DEFINE_SPINLOCK(hpet_lock);

#घोषणा	HPET_DEV_NAME	(7)

काष्ठा hpet_dev अणु
	काष्ठा hpets *hd_hpets;
	काष्ठा hpet __iomem *hd_hpet;
	काष्ठा hpet_समयr __iomem *hd_समयr;
	अचिन्हित दीर्घ hd_ireqfreq;
	अचिन्हित दीर्घ hd_irqdata;
	रुको_queue_head_t hd_रुकोqueue;
	काष्ठा fasync_काष्ठा *hd_async_queue;
	अचिन्हित पूर्णांक hd_flags;
	अचिन्हित पूर्णांक hd_irq;
	अचिन्हित पूर्णांक hd_hdwirq;
	अक्षर hd_name[HPET_DEV_NAME];
पूर्ण;

काष्ठा hpets अणु
	काष्ठा hpets *hp_next;
	काष्ठा hpet __iomem *hp_hpet;
	अचिन्हित दीर्घ hp_hpet_phys;
	काष्ठा घड़ीsource *hp_घड़ीsource;
	अचिन्हित दीर्घ दीर्घ hp_tick_freq;
	अचिन्हित दीर्घ hp_delta;
	अचिन्हित पूर्णांक hp_nसमयr;
	अचिन्हित पूर्णांक hp_which;
	काष्ठा hpet_dev hp_dev[];
पूर्ण;

अटल काष्ठा hpets *hpets;

#घोषणा	HPET_OPEN		0x0001
#घोषणा	HPET_IE			0x0002	/* पूर्णांकerrupt enabled */
#घोषणा	HPET_PERIODIC		0x0004
#घोषणा	HPET_SHARED_IRQ		0x0008


#अगर_अघोषित पढ़ोq
अटल अंतरभूत अचिन्हित दीर्घ दीर्घ पढ़ोq(व्योम __iomem *addr)
अणु
	वापस पढ़ोl(addr) | (((अचिन्हित दीर्घ दीर्घ)पढ़ोl(addr + 4)) << 32LL);
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित ग_लिखोq
अटल अंतरभूत व्योम ग_लिखोq(अचिन्हित दीर्घ दीर्घ v, व्योम __iomem *addr)
अणु
	ग_लिखोl(v & 0xffffffff, addr);
	ग_लिखोl(v >> 32, addr + 4);
पूर्ण
#पूर्ण_अगर

अटल irqवापस_t hpet_पूर्णांकerrupt(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा hpet_dev *devp;
	अचिन्हित दीर्घ isr;

	devp = data;
	isr = 1 << (devp - devp->hd_hpets->hp_dev);

	अगर ((devp->hd_flags & HPET_SHARED_IRQ) &&
	    !(isr & पढ़ोl(&devp->hd_hpet->hpet_isr)))
		वापस IRQ_NONE;

	spin_lock(&hpet_lock);
	devp->hd_irqdata++;

	/*
	 * For non-periodic समयrs, increment the accumulator.
	 * This has the effect of treating non-periodic like periodic.
	 */
	अगर ((devp->hd_flags & (HPET_IE | HPET_PERIODIC)) == HPET_IE) अणु
		अचिन्हित दीर्घ m, t, mc, base, k;
		काष्ठा hpet __iomem *hpet = devp->hd_hpet;
		काष्ठा hpets *hpetp = devp->hd_hpets;

		t = devp->hd_ireqfreq;
		m = पढ़ो_counter(&devp->hd_समयr->hpet_compare);
		mc = पढ़ो_counter(&hpet->hpet_mc);
		/* The समय क्रम the next पूर्णांकerrupt would logically be t + m,
		 * however, अगर we are very unlucky and the पूर्णांकerrupt is delayed
		 * क्रम दीर्घer than t then we will completely miss the next
		 * पूर्णांकerrupt अगर we set t + m and an application will hang.
		 * Thereक्रमe we need to make a more complex computation assuming
		 * that there exists a k क्रम which the following is true:
		 * k * t + base < mc + delta
		 * (k + 1) * t + base > mc + delta
		 * where t is the पूर्णांकerval in hpet ticks क्रम the given freq,
		 * base is the theoretical start value 0 < base < t,
		 * mc is the मुख्य counter value at the समय of the पूर्णांकerrupt,
		 * delta is the समय it takes to ग_लिखो the a value to the
		 * comparator.
		 * k may then be computed as (mc - base + delta) / t .
		 */
		base = mc % t;
		k = (mc - base + hpetp->hp_delta) / t;
		ग_लिखो_counter(t * (k + 1) + base,
			      &devp->hd_समयr->hpet_compare);
	पूर्ण

	अगर (devp->hd_flags & HPET_SHARED_IRQ)
		ग_लिखोl(isr, &devp->hd_hpet->hpet_isr);
	spin_unlock(&hpet_lock);

	wake_up_पूर्णांकerruptible(&devp->hd_रुकोqueue);

	समाप्त_fasync(&devp->hd_async_queue, SIGIO, POLL_IN);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम hpet_समयr_set_irq(काष्ठा hpet_dev *devp)
अणु
	अचिन्हित दीर्घ v;
	पूर्णांक irq, gsi;
	काष्ठा hpet_समयr __iomem *समयr;

	spin_lock_irq(&hpet_lock);
	अगर (devp->hd_hdwirq) अणु
		spin_unlock_irq(&hpet_lock);
		वापस;
	पूर्ण

	समयr = devp->hd_समयr;

	/* we prefer level triggered mode */
	v = पढ़ोl(&समयr->hpet_config);
	अगर (!(v & Tn_INT_TYPE_CNF_MASK)) अणु
		v |= Tn_INT_TYPE_CNF_MASK;
		ग_लिखोl(v, &समयr->hpet_config);
	पूर्ण
	spin_unlock_irq(&hpet_lock);

	v = (पढ़ोq(&समयr->hpet_config) & Tn_INT_ROUTE_CAP_MASK) >>
				 Tn_INT_ROUTE_CAP_SHIFT;

	/*
	 * In PIC mode, skip IRQ0-4, IRQ6-9, IRQ12-15 which is always used by
	 * legacy device. In IO APIC mode, we skip all the legacy IRQS.
	 */
	अगर (acpi_irq_model == ACPI_IRQ_MODEL_PIC)
		v &= ~0xf3df;
	अन्यथा
		v &= ~0xffff;

	क्रम_each_set_bit(irq, &v, HPET_MAX_IRQ) अणु
		अगर (irq >= nr_irqs) अणु
			irq = HPET_MAX_IRQ;
			अवरोध;
		पूर्ण

		gsi = acpi_रेजिस्टर_gsi(शून्य, irq, ACPI_LEVEL_SENSITIVE,
					ACPI_ACTIVE_LOW);
		अगर (gsi > 0)
			अवरोध;

		/* FIXME: Setup पूर्णांकerrupt source table */
	पूर्ण

	अगर (irq < HPET_MAX_IRQ) अणु
		spin_lock_irq(&hpet_lock);
		v = पढ़ोl(&समयr->hpet_config);
		v |= irq << Tn_INT_ROUTE_CNF_SHIFT;
		ग_लिखोl(v, &समयr->hpet_config);
		devp->hd_hdwirq = gsi;
		spin_unlock_irq(&hpet_lock);
	पूर्ण
	वापस;
पूर्ण

अटल पूर्णांक hpet_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा hpet_dev *devp;
	काष्ठा hpets *hpetp;
	पूर्णांक i;

	अगर (file->f_mode & FMODE_WRITE)
		वापस -EINVAL;

	mutex_lock(&hpet_mutex);
	spin_lock_irq(&hpet_lock);

	क्रम (devp = शून्य, hpetp = hpets; hpetp && !devp; hpetp = hpetp->hp_next)
		क्रम (i = 0; i < hpetp->hp_nसमयr; i++)
			अगर (hpetp->hp_dev[i].hd_flags & HPET_OPEN)
				जारी;
			अन्यथा अणु
				devp = &hpetp->hp_dev[i];
				अवरोध;
			पूर्ण

	अगर (!devp) अणु
		spin_unlock_irq(&hpet_lock);
		mutex_unlock(&hpet_mutex);
		वापस -EBUSY;
	पूर्ण

	file->निजी_data = devp;
	devp->hd_irqdata = 0;
	devp->hd_flags |= HPET_OPEN;
	spin_unlock_irq(&hpet_lock);
	mutex_unlock(&hpet_mutex);

	hpet_समयr_set_irq(devp);

	वापस 0;
पूर्ण

अटल sमाप_प्रकार
hpet_पढ़ो(काष्ठा file *file, अक्षर __user *buf, माप_प्रकार count, loff_t * ppos)
अणु
	DECLARE_WAITQUEUE(रुको, current);
	अचिन्हित दीर्घ data;
	sमाप_प्रकार retval;
	काष्ठा hpet_dev *devp;

	devp = file->निजी_data;
	अगर (!devp->hd_ireqfreq)
		वापस -EIO;

	अगर (count < माप(अचिन्हित दीर्घ))
		वापस -EINVAL;

	add_रुको_queue(&devp->hd_रुकोqueue, &रुको);

	क्रम ( ; ; ) अणु
		set_current_state(TASK_INTERRUPTIBLE);

		spin_lock_irq(&hpet_lock);
		data = devp->hd_irqdata;
		devp->hd_irqdata = 0;
		spin_unlock_irq(&hpet_lock);

		अगर (data)
			अवरोध;
		अन्यथा अगर (file->f_flags & O_NONBLOCK) अणु
			retval = -EAGAIN;
			जाओ out;
		पूर्ण अन्यथा अगर (संकेत_pending(current)) अणु
			retval = -ERESTARTSYS;
			जाओ out;
		पूर्ण
		schedule();
	पूर्ण

	retval = put_user(data, (अचिन्हित दीर्घ __user *)buf);
	अगर (!retval)
		retval = माप(अचिन्हित दीर्घ);
out:
	__set_current_state(TASK_RUNNING);
	हटाओ_रुको_queue(&devp->hd_रुकोqueue, &रुको);

	वापस retval;
पूर्ण

अटल __poll_t hpet_poll(काष्ठा file *file, poll_table * रुको)
अणु
	अचिन्हित दीर्घ v;
	काष्ठा hpet_dev *devp;

	devp = file->निजी_data;

	अगर (!devp->hd_ireqfreq)
		वापस 0;

	poll_रुको(file, &devp->hd_रुकोqueue, रुको);

	spin_lock_irq(&hpet_lock);
	v = devp->hd_irqdata;
	spin_unlock_irq(&hpet_lock);

	अगर (v != 0)
		वापस EPOLLIN | EPOLLRDNORM;

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_HPET_MMAP
#अगर_घोषित CONFIG_HPET_MMAP_DEFAULT
अटल पूर्णांक hpet_mmap_enabled = 1;
#अन्यथा
अटल पूर्णांक hpet_mmap_enabled = 0;
#पूर्ण_अगर

अटल __init पूर्णांक hpet_mmap_enable(अक्षर *str)
अणु
	get_option(&str, &hpet_mmap_enabled);
	pr_info("HPET mmap %s\n", hpet_mmap_enabled ? "enabled" : "disabled");
	वापस 1;
पूर्ण
__setup("hpet_mmap=", hpet_mmap_enable);

अटल पूर्णांक hpet_mmap(काष्ठा file *file, काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा hpet_dev *devp;
	अचिन्हित दीर्घ addr;

	अगर (!hpet_mmap_enabled)
		वापस -EACCES;

	devp = file->निजी_data;
	addr = devp->hd_hpets->hp_hpet_phys;

	अगर (addr & (PAGE_SIZE - 1))
		वापस -ENOSYS;

	vma->vm_page_prot = pgprot_noncached(vma->vm_page_prot);
	वापस vm_iomap_memory(vma, addr, PAGE_SIZE);
पूर्ण
#अन्यथा
अटल पूर्णांक hpet_mmap(काष्ठा file *file, काष्ठा vm_area_काष्ठा *vma)
अणु
	वापस -ENOSYS;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक hpet_fasync(पूर्णांक fd, काष्ठा file *file, पूर्णांक on)
अणु
	काष्ठा hpet_dev *devp;

	devp = file->निजी_data;

	अगर (fasync_helper(fd, file, on, &devp->hd_async_queue) >= 0)
		वापस 0;
	अन्यथा
		वापस -EIO;
पूर्ण

अटल पूर्णांक hpet_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा hpet_dev *devp;
	काष्ठा hpet_समयr __iomem *समयr;
	पूर्णांक irq = 0;

	devp = file->निजी_data;
	समयr = devp->hd_समयr;

	spin_lock_irq(&hpet_lock);

	ग_लिखोq((पढ़ोq(&समयr->hpet_config) & ~Tn_INT_ENB_CNF_MASK),
	       &समयr->hpet_config);

	irq = devp->hd_irq;
	devp->hd_irq = 0;

	devp->hd_ireqfreq = 0;

	अगर (devp->hd_flags & HPET_PERIODIC
	    && पढ़ोq(&समयr->hpet_config) & Tn_TYPE_CNF_MASK) अणु
		अचिन्हित दीर्घ v;

		v = पढ़ोq(&समयr->hpet_config);
		v ^= Tn_TYPE_CNF_MASK;
		ग_लिखोq(v, &समयr->hpet_config);
	पूर्ण

	devp->hd_flags &= ~(HPET_OPEN | HPET_IE | HPET_PERIODIC);
	spin_unlock_irq(&hpet_lock);

	अगर (irq)
		मुक्त_irq(irq, devp);

	file->निजी_data = शून्य;
	वापस 0;
पूर्ण

अटल पूर्णांक hpet_ioctl_ieon(काष्ठा hpet_dev *devp)
अणु
	काष्ठा hpet_समयr __iomem *समयr;
	काष्ठा hpet __iomem *hpet;
	काष्ठा hpets *hpetp;
	पूर्णांक irq;
	अचिन्हित दीर्घ g, v, t, m;
	अचिन्हित दीर्घ flags, isr;

	समयr = devp->hd_समयr;
	hpet = devp->hd_hpet;
	hpetp = devp->hd_hpets;

	अगर (!devp->hd_ireqfreq)
		वापस -EIO;

	spin_lock_irq(&hpet_lock);

	अगर (devp->hd_flags & HPET_IE) अणु
		spin_unlock_irq(&hpet_lock);
		वापस -EBUSY;
	पूर्ण

	devp->hd_flags |= HPET_IE;

	अगर (पढ़ोl(&समयr->hpet_config) & Tn_INT_TYPE_CNF_MASK)
		devp->hd_flags |= HPET_SHARED_IRQ;
	spin_unlock_irq(&hpet_lock);

	irq = devp->hd_hdwirq;

	अगर (irq) अणु
		अचिन्हित दीर्घ irq_flags;

		अगर (devp->hd_flags & HPET_SHARED_IRQ) अणु
			/*
			 * To prevent the पूर्णांकerrupt handler from seeing an
			 * unwanted पूर्णांकerrupt status bit, program the समयr
			 * so that it will not fire in the near future ...
			 */
			ग_लिखोl(पढ़ोl(&समयr->hpet_config) & ~Tn_TYPE_CNF_MASK,
			       &समयr->hpet_config);
			ग_लिखो_counter(पढ़ो_counter(&hpet->hpet_mc),
				      &समयr->hpet_compare);
			/* ... and clear any left-over status. */
			isr = 1 << (devp - devp->hd_hpets->hp_dev);
			ग_लिखोl(isr, &hpet->hpet_isr);
		पूर्ण

		प्र_लिखो(devp->hd_name, "hpet%d", (पूर्णांक)(devp - hpetp->hp_dev));
		irq_flags = devp->hd_flags & HPET_SHARED_IRQ ? IRQF_SHARED : 0;
		अगर (request_irq(irq, hpet_पूर्णांकerrupt, irq_flags,
				devp->hd_name, (व्योम *)devp)) अणु
			prपूर्णांकk(KERN_ERR "hpet: IRQ %d is not free\n", irq);
			irq = 0;
		पूर्ण
	पूर्ण

	अगर (irq == 0) अणु
		spin_lock_irq(&hpet_lock);
		devp->hd_flags ^= HPET_IE;
		spin_unlock_irq(&hpet_lock);
		वापस -EIO;
	पूर्ण

	devp->hd_irq = irq;
	t = devp->hd_ireqfreq;
	v = पढ़ोq(&समयr->hpet_config);

	/* 64-bit comparators are not yet supported through the ioctls,
	 * so क्रमce this पूर्णांकo 32-bit mode अगर it supports both modes
	 */
	g = v | Tn_32MODE_CNF_MASK | Tn_INT_ENB_CNF_MASK;

	अगर (devp->hd_flags & HPET_PERIODIC) अणु
		g |= Tn_TYPE_CNF_MASK;
		v |= Tn_TYPE_CNF_MASK | Tn_VAL_SET_CNF_MASK;
		ग_लिखोq(v, &समयr->hpet_config);
		local_irq_save(flags);

		/*
		 * NOTE: First we modअगरy the hidden accumulator
		 * रेजिस्टर supported by periodic-capable comparators.
		 * We never want to modअगरy the (single) counter; that
		 * would affect all the comparators. The value written
		 * is the counter value when the first पूर्णांकerrupt is due.
		 */
		m = पढ़ो_counter(&hpet->hpet_mc);
		ग_लिखो_counter(t + m + hpetp->hp_delta, &समयr->hpet_compare);
		/*
		 * Then we modअगरy the comparator, indicating the period
		 * क्रम subsequent पूर्णांकerrupt.
		 */
		ग_लिखो_counter(t, &समयr->hpet_compare);
	पूर्ण अन्यथा अणु
		local_irq_save(flags);
		m = पढ़ो_counter(&hpet->hpet_mc);
		ग_लिखो_counter(t + m + hpetp->hp_delta, &समयr->hpet_compare);
	पूर्ण

	अगर (devp->hd_flags & HPET_SHARED_IRQ) अणु
		isr = 1 << (devp - devp->hd_hpets->hp_dev);
		ग_लिखोl(isr, &hpet->hpet_isr);
	पूर्ण
	ग_लिखोq(g, &समयr->hpet_config);
	local_irq_restore(flags);

	वापस 0;
पूर्ण

/* converts Hz to number of समयr ticks */
अटल अंतरभूत अचिन्हित दीर्घ hpet_समय_भाग(काष्ठा hpets *hpets,
					  अचिन्हित दीर्घ dis)
अणु
	अचिन्हित दीर्घ दीर्घ m;

	m = hpets->hp_tick_freq + (dis >> 1);
	वापस भाग64_ul(m, dis);
पूर्ण

अटल पूर्णांक
hpet_ioctl_common(काष्ठा hpet_dev *devp, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg,
		  काष्ठा hpet_info *info)
अणु
	काष्ठा hpet_समयr __iomem *समयr;
	काष्ठा hpets *hpetp;
	पूर्णांक err;
	अचिन्हित दीर्घ v;

	चयन (cmd) अणु
	हाल HPET_IE_OFF:
	हाल HPET_INFO:
	हाल HPET_EPI:
	हाल HPET_DPI:
	हाल HPET_IRQFREQ:
		समयr = devp->hd_समयr;
		hpetp = devp->hd_hpets;
		अवरोध;
	हाल HPET_IE_ON:
		वापस hpet_ioctl_ieon(devp);
	शेष:
		वापस -EINVAL;
	पूर्ण

	err = 0;

	चयन (cmd) अणु
	हाल HPET_IE_OFF:
		अगर ((devp->hd_flags & HPET_IE) == 0)
			अवरोध;
		v = पढ़ोq(&समयr->hpet_config);
		v &= ~Tn_INT_ENB_CNF_MASK;
		ग_लिखोq(v, &समयr->hpet_config);
		अगर (devp->hd_irq) अणु
			मुक्त_irq(devp->hd_irq, devp);
			devp->hd_irq = 0;
		पूर्ण
		devp->hd_flags ^= HPET_IE;
		अवरोध;
	हाल HPET_INFO:
		अणु
			स_रखो(info, 0, माप(*info));
			अगर (devp->hd_ireqfreq)
				info->hi_ireqfreq =
					hpet_समय_भाग(hpetp, devp->hd_ireqfreq);
			info->hi_flags =
			    पढ़ोq(&समयr->hpet_config) & Tn_PER_INT_CAP_MASK;
			info->hi_hpet = hpetp->hp_which;
			info->hi_समयr = devp - hpetp->hp_dev;
			अवरोध;
		पूर्ण
	हाल HPET_EPI:
		v = पढ़ोq(&समयr->hpet_config);
		अगर ((v & Tn_PER_INT_CAP_MASK) == 0) अणु
			err = -ENXIO;
			अवरोध;
		पूर्ण
		devp->hd_flags |= HPET_PERIODIC;
		अवरोध;
	हाल HPET_DPI:
		v = पढ़ोq(&समयr->hpet_config);
		अगर ((v & Tn_PER_INT_CAP_MASK) == 0) अणु
			err = -ENXIO;
			अवरोध;
		पूर्ण
		अगर (devp->hd_flags & HPET_PERIODIC &&
		    पढ़ोq(&समयr->hpet_config) & Tn_TYPE_CNF_MASK) अणु
			v = पढ़ोq(&समयr->hpet_config);
			v ^= Tn_TYPE_CNF_MASK;
			ग_लिखोq(v, &समयr->hpet_config);
		पूर्ण
		devp->hd_flags &= ~HPET_PERIODIC;
		अवरोध;
	हाल HPET_IRQFREQ:
		अगर ((arg > hpet_max_freq) &&
		    !capable(CAP_SYS_RESOURCE)) अणु
			err = -EACCES;
			अवरोध;
		पूर्ण

		अगर (!arg) अणु
			err = -EINVAL;
			अवरोध;
		पूर्ण

		devp->hd_ireqfreq = hpet_समय_भाग(hpetp, arg);
	पूर्ण

	वापस err;
पूर्ण

अटल दीर्घ
hpet_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा hpet_info info;
	पूर्णांक err;

	mutex_lock(&hpet_mutex);
	err = hpet_ioctl_common(file->निजी_data, cmd, arg, &info);
	mutex_unlock(&hpet_mutex);

	अगर ((cmd == HPET_INFO) && !err &&
	    (copy_to_user((व्योम __user *)arg, &info, माप(info))))
		err = -EFAULT;

	वापस err;
पूर्ण

#अगर_घोषित CONFIG_COMPAT
काष्ठा compat_hpet_info अणु
	compat_uदीर्घ_t hi_ireqfreq;	/* Hz */
	compat_uदीर्घ_t hi_flags;	/* inक्रमmation */
	अचिन्हित लघु hi_hpet;
	अचिन्हित लघु hi_समयr;
पूर्ण;

अटल दीर्घ
hpet_compat_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा hpet_info info;
	पूर्णांक err;

	mutex_lock(&hpet_mutex);
	err = hpet_ioctl_common(file->निजी_data, cmd, arg, &info);
	mutex_unlock(&hpet_mutex);

	अगर ((cmd == HPET_INFO) && !err) अणु
		काष्ठा compat_hpet_info __user *u = compat_ptr(arg);
		अगर (put_user(info.hi_ireqfreq, &u->hi_ireqfreq) ||
		    put_user(info.hi_flags, &u->hi_flags) ||
		    put_user(info.hi_hpet, &u->hi_hpet) ||
		    put_user(info.hi_समयr, &u->hi_समयr))
			err = -EFAULT;
	पूर्ण

	वापस err;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा file_operations hpet_fops = अणु
	.owner = THIS_MODULE,
	.llseek = no_llseek,
	.पढ़ो = hpet_पढ़ो,
	.poll = hpet_poll,
	.unlocked_ioctl = hpet_ioctl,
#अगर_घोषित CONFIG_COMPAT
	.compat_ioctl = hpet_compat_ioctl,
#पूर्ण_अगर
	.खोलो = hpet_खोलो,
	.release = hpet_release,
	.fasync = hpet_fasync,
	.mmap = hpet_mmap,
पूर्ण;

अटल पूर्णांक hpet_is_known(काष्ठा hpet_data *hdp)
अणु
	काष्ठा hpets *hpetp;

	क्रम (hpetp = hpets; hpetp; hpetp = hpetp->hp_next)
		अगर (hpetp->hp_hpet_phys == hdp->hd_phys_address)
			वापस 1;

	वापस 0;
पूर्ण

अटल काष्ठा ctl_table hpet_table[] = अणु
	अणु
	 .procname = "max-user-freq",
	 .data = &hpet_max_freq,
	 .maxlen = माप(पूर्णांक),
	 .mode = 0644,
	 .proc_handler = proc_करोपूर्णांकvec,
	 पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल काष्ठा ctl_table hpet_root[] = अणु
	अणु
	 .procname = "hpet",
	 .maxlen = 0,
	 .mode = 0555,
	 .child = hpet_table,
	 पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल काष्ठा ctl_table dev_root[] = अणु
	अणु
	 .procname = "dev",
	 .maxlen = 0,
	 .mode = 0555,
	 .child = hpet_root,
	 पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल काष्ठा ctl_table_header *sysctl_header;

/*
 * Adjusपंचांगent क्रम when arming the समयr with
 * initial conditions.  That is, मुख्य counter
 * ticks expired beक्रमe पूर्णांकerrupts are enabled.
 */
#घोषणा	TICK_CALIBRATE	(1000UL)

अटल अचिन्हित दीर्घ __hpet_calibrate(काष्ठा hpets *hpetp)
अणु
	काष्ठा hpet_समयr __iomem *समयr = शून्य;
	अचिन्हित दीर्घ t, m, count, i, flags, start;
	काष्ठा hpet_dev *devp;
	पूर्णांक j;
	काष्ठा hpet __iomem *hpet;

	क्रम (j = 0, devp = hpetp->hp_dev; j < hpetp->hp_nसमयr; j++, devp++)
		अगर ((devp->hd_flags & HPET_OPEN) == 0) अणु
			समयr = devp->hd_समयr;
			अवरोध;
		पूर्ण

	अगर (!समयr)
		वापस 0;

	hpet = hpetp->hp_hpet;
	t = पढ़ो_counter(&समयr->hpet_compare);

	i = 0;
	count = hpet_समय_भाग(hpetp, TICK_CALIBRATE);

	local_irq_save(flags);

	start = पढ़ो_counter(&hpet->hpet_mc);

	करो अणु
		m = पढ़ो_counter(&hpet->hpet_mc);
		ग_लिखो_counter(t + m + hpetp->hp_delta, &समयr->hpet_compare);
	पूर्ण जबतक (i++, (m - start) < count);

	local_irq_restore(flags);

	वापस (m - start) / i;
पूर्ण

अटल अचिन्हित दीर्घ hpet_calibrate(काष्ठा hpets *hpetp)
अणु
	अचिन्हित दीर्घ ret = ~0UL;
	अचिन्हित दीर्घ पंचांगp;

	/*
	 * Try to calibrate until वापस value becomes stable small value.
	 * If SMI पूर्णांकerruption occurs in calibration loop, the वापस value
	 * will be big. This aव्योमs its impact.
	 */
	क्रम ( ; ; ) अणु
		पंचांगp = __hpet_calibrate(hpetp);
		अगर (ret <= पंचांगp)
			अवरोध;
		ret = पंचांगp;
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक hpet_alloc(काष्ठा hpet_data *hdp)
अणु
	u64 cap, mcfg;
	काष्ठा hpet_dev *devp;
	u32 i, nसमयr;
	काष्ठा hpets *hpetp;
	काष्ठा hpet __iomem *hpet;
	अटल काष्ठा hpets *last;
	अचिन्हित दीर्घ period;
	अचिन्हित दीर्घ दीर्घ temp;
	u32 reमुख्यder;

	/*
	 * hpet_alloc can be called by platक्रमm dependent code.
	 * If platक्रमm dependent code has allocated the hpet that
	 * ACPI has also reported, then we catch it here.
	 */
	अगर (hpet_is_known(hdp)) अणु
		prपूर्णांकk(KERN_DEBUG "%s: duplicate HPET ignored\n",
			__func__);
		वापस 0;
	पूर्ण

	hpetp = kzalloc(काष्ठा_size(hpetp, hp_dev, hdp->hd_nirqs),
			GFP_KERNEL);

	अगर (!hpetp)
		वापस -ENOMEM;

	hpetp->hp_which = hpet_nhpet++;
	hpetp->hp_hpet = hdp->hd_address;
	hpetp->hp_hpet_phys = hdp->hd_phys_address;

	hpetp->hp_nसमयr = hdp->hd_nirqs;

	क्रम (i = 0; i < hdp->hd_nirqs; i++)
		hpetp->hp_dev[i].hd_hdwirq = hdp->hd_irq[i];

	hpet = hpetp->hp_hpet;

	cap = पढ़ोq(&hpet->hpet_cap);

	nसमयr = ((cap & HPET_NUM_TIM_CAP_MASK) >> HPET_NUM_TIM_CAP_SHIFT) + 1;

	अगर (hpetp->hp_nसमयr != nसमयr) अणु
		prपूर्णांकk(KERN_WARNING "hpet: number irqs doesn't agree"
		       " with number of timers\n");
		kमुक्त(hpetp);
		वापस -ENODEV;
	पूर्ण

	अगर (last)
		last->hp_next = hpetp;
	अन्यथा
		hpets = hpetp;

	last = hpetp;

	period = (cap & HPET_COUNTER_CLK_PERIOD_MASK) >>
		HPET_COUNTER_CLK_PERIOD_SHIFT; /* fs, 10^-15 */
	temp = 1000000000000000uLL; /* 10^15 femtoseconds per second */
	temp += period >> 1; /* round */
	करो_भाग(temp, period);
	hpetp->hp_tick_freq = temp; /* ticks per second */

	prपूर्णांकk(KERN_INFO "hpet%d: at MMIO 0x%lx, IRQ%s",
		hpetp->hp_which, hdp->hd_phys_address,
		hpetp->hp_nसमयr > 1 ? "s" : "");
	क्रम (i = 0; i < hpetp->hp_nसमयr; i++)
		prपूर्णांकk(KERN_CONT "%s %d", i > 0 ? "," : "", hdp->hd_irq[i]);
	prपूर्णांकk(KERN_CONT "\n");

	temp = hpetp->hp_tick_freq;
	reमुख्यder = करो_भाग(temp, 1000000);
	prपूर्णांकk(KERN_INFO
		"hpet%u: %u comparators, %d-bit %u.%06u MHz counter\n",
		hpetp->hp_which, hpetp->hp_nसमयr,
		cap & HPET_COUNTER_SIZE_MASK ? 64 : 32,
		(अचिन्हित) temp, reमुख्यder);

	mcfg = पढ़ोq(&hpet->hpet_config);
	अगर ((mcfg & HPET_ENABLE_CNF_MASK) == 0) अणु
		ग_लिखो_counter(0L, &hpet->hpet_mc);
		mcfg |= HPET_ENABLE_CNF_MASK;
		ग_लिखोq(mcfg, &hpet->hpet_config);
	पूर्ण

	क्रम (i = 0, devp = hpetp->hp_dev; i < hpetp->hp_nसमयr; i++, devp++) अणु
		काष्ठा hpet_समयr __iomem *समयr;

		समयr = &hpet->hpet_समयrs[devp - hpetp->hp_dev];

		devp->hd_hpets = hpetp;
		devp->hd_hpet = hpet;
		devp->hd_समयr = समयr;

		/*
		 * If the समयr was reserved by platक्रमm code,
		 * then make समयr unavailable क्रम खोलोs.
		 */
		अगर (hdp->hd_state & (1 << i)) अणु
			devp->hd_flags = HPET_OPEN;
			जारी;
		पूर्ण

		init_रुकोqueue_head(&devp->hd_रुकोqueue);
	पूर्ण

	hpetp->hp_delta = hpet_calibrate(hpetp);

/* This घड़ीsource driver currently only works on ia64 */
#अगर_घोषित CONFIG_IA64
	अगर (!hpet_घड़ीsource) अणु
		hpet_mctr = (व्योम __iomem *)&hpetp->hp_hpet->hpet_mc;
		घड़ीsource_hpet.archdata.fsys_mmio = hpet_mctr;
		घड़ीsource_रेजिस्टर_hz(&घड़ीsource_hpet, hpetp->hp_tick_freq);
		hpetp->hp_घड़ीsource = &घड़ीsource_hpet;
		hpet_घड़ीsource = &घड़ीsource_hpet;
	पूर्ण
#पूर्ण_अगर

	वापस 0;
पूर्ण

अटल acpi_status hpet_resources(काष्ठा acpi_resource *res, व्योम *data)
अणु
	काष्ठा hpet_data *hdp;
	acpi_status status;
	काष्ठा acpi_resource_address64 addr;

	hdp = data;

	status = acpi_resource_to_address64(res, &addr);

	अगर (ACPI_SUCCESS(status)) अणु
		hdp->hd_phys_address = addr.address.minimum;
		hdp->hd_address = ioremap(addr.address.minimum, addr.address.address_length);
		अगर (!hdp->hd_address)
			वापस AE_ERROR;

		अगर (hpet_is_known(hdp)) अणु
			iounmap(hdp->hd_address);
			वापस AE_ALREADY_EXISTS;
		पूर्ण
	पूर्ण अन्यथा अगर (res->type == ACPI_RESOURCE_TYPE_FIXED_MEMORY32) अणु
		काष्ठा acpi_resource_fixed_memory32 *fixmem32;

		fixmem32 = &res->data.fixed_memory32;

		hdp->hd_phys_address = fixmem32->address;
		hdp->hd_address = ioremap(fixmem32->address,
						HPET_RANGE_SIZE);
		अगर (!hdp->hd_address)
			वापस AE_ERROR;

		अगर (hpet_is_known(hdp)) अणु
			iounmap(hdp->hd_address);
			वापस AE_ALREADY_EXISTS;
		पूर्ण
	पूर्ण अन्यथा अगर (res->type == ACPI_RESOURCE_TYPE_EXTENDED_IRQ) अणु
		काष्ठा acpi_resource_extended_irq *irqp;
		पूर्णांक i, irq;

		irqp = &res->data.extended_irq;

		क्रम (i = 0; i < irqp->पूर्णांकerrupt_count; i++) अणु
			अगर (hdp->hd_nirqs >= HPET_MAX_TIMERS)
				अवरोध;

			irq = acpi_रेजिस्टर_gsi(शून्य, irqp->पूर्णांकerrupts[i],
				      irqp->triggering, irqp->polarity);
			अगर (irq < 0)
				वापस AE_ERROR;

			hdp->hd_irq[hdp->hd_nirqs] = irq;
			hdp->hd_nirqs++;
		पूर्ण
	पूर्ण

	वापस AE_OK;
पूर्ण

अटल पूर्णांक hpet_acpi_add(काष्ठा acpi_device *device)
अणु
	acpi_status result;
	काष्ठा hpet_data data;

	स_रखो(&data, 0, माप(data));

	result =
	    acpi_walk_resources(device->handle, METHOD_NAME__CRS,
				hpet_resources, &data);

	अगर (ACPI_FAILURE(result))
		वापस -ENODEV;

	अगर (!data.hd_address || !data.hd_nirqs) अणु
		अगर (data.hd_address)
			iounmap(data.hd_address);
		prपूर्णांकk("%s: no address or irqs in _CRS\n", __func__);
		वापस -ENODEV;
	पूर्ण

	वापस hpet_alloc(&data);
पूर्ण

अटल स्थिर काष्ठा acpi_device_id hpet_device_ids[] = अणु
	अणु"PNP0103", 0पूर्ण,
	अणु"", 0पूर्ण,
पूर्ण;

अटल काष्ठा acpi_driver hpet_acpi_driver = अणु
	.name = "hpet",
	.ids = hpet_device_ids,
	.ops = अणु
		.add = hpet_acpi_add,
		पूर्ण,
पूर्ण;

अटल काष्ठा miscdevice hpet_misc = अणु HPET_MINOR, "hpet", &hpet_fops पूर्ण;

अटल पूर्णांक __init hpet_init(व्योम)
अणु
	पूर्णांक result;

	result = misc_रेजिस्टर(&hpet_misc);
	अगर (result < 0)
		वापस -ENODEV;

	sysctl_header = रेजिस्टर_sysctl_table(dev_root);

	result = acpi_bus_रेजिस्टर_driver(&hpet_acpi_driver);
	अगर (result < 0) अणु
		अगर (sysctl_header)
			unरेजिस्टर_sysctl_table(sysctl_header);
		misc_deरेजिस्टर(&hpet_misc);
		वापस result;
	पूर्ण

	वापस 0;
पूर्ण
device_initcall(hpet_init);

/*
MODULE_AUTHOR("Bob Picco <Robert.Picco@hp.com>");
MODULE_LICENSE("GPL");
*/
