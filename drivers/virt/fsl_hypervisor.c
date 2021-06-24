<शैली गुरु>
/*
 * Freescale Hypervisor Management Driver

 * Copyright (C) 2008-2011 Freescale Semiconductor, Inc.
 * Author: Timur Tabi <timur@मुक्तscale.com>
 *
 * This file is licensed under the terms of the GNU General Public License
 * version 2.  This program is licensed "as is" without any warranty of any
 * kind, whether express or implied.
 *
 * The Freescale hypervisor management driver provides several services to
 * drivers and applications related to the Freescale hypervisor:
 *
 * 1. An ioctl पूर्णांकerface क्रम querying and managing partitions.
 *
 * 2. A file पूर्णांकerface to पढ़ोing incoming करोorbells.
 *
 * 3. An पूर्णांकerrupt handler क्रम shutting करोwn the partition upon receiving the
 *    shutकरोwn करोorbell from a manager partition.
 *
 * 4. A kernel पूर्णांकerface क्रम receiving callbacks when a managed partition
 *    shuts करोwn.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/types.h>
#समावेश <linux/err.h>
#समावेश <linux/fs.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/mm.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/slab.h>
#समावेश <linux/poll.h>
#समावेश <linux/of.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/reboot.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/पूर्णांकerrupt.h>

#समावेश <linux/पन.स>
#समावेश <यंत्र/fsl_hcalls.h>

#समावेश <linux/fsl_hypervisor.h>

अटल BLOCKING_NOTIFIER_HEAD(failover_subscribers);

/*
 * Ioctl पूर्णांकerface क्रम FSL_HV_IOCTL_PARTITION_RESTART
 *
 * Restart a running partition
 */
अटल दीर्घ ioctl_restart(काष्ठा fsl_hv_ioctl_restart __user *p)
अणु
	काष्ठा fsl_hv_ioctl_restart param;

	/* Get the parameters from the user */
	अगर (copy_from_user(&param, p, माप(काष्ठा fsl_hv_ioctl_restart)))
		वापस -EFAULT;

	param.ret = fh_partition_restart(param.partition);

	अगर (copy_to_user(&p->ret, &param.ret, माप(__u32)))
		वापस -EFAULT;

	वापस 0;
पूर्ण

/*
 * Ioctl पूर्णांकerface क्रम FSL_HV_IOCTL_PARTITION_STATUS
 *
 * Query the status of a partition
 */
अटल दीर्घ ioctl_status(काष्ठा fsl_hv_ioctl_status __user *p)
अणु
	काष्ठा fsl_hv_ioctl_status param;
	u32 status;

	/* Get the parameters from the user */
	अगर (copy_from_user(&param, p, माप(काष्ठा fsl_hv_ioctl_status)))
		वापस -EFAULT;

	param.ret = fh_partition_get_status(param.partition, &status);
	अगर (!param.ret)
		param.status = status;

	अगर (copy_to_user(p, &param, माप(काष्ठा fsl_hv_ioctl_status)))
		वापस -EFAULT;

	वापस 0;
पूर्ण

/*
 * Ioctl पूर्णांकerface क्रम FSL_HV_IOCTL_PARTITION_START
 *
 * Start a stopped partition.
 */
अटल दीर्घ ioctl_start(काष्ठा fsl_hv_ioctl_start __user *p)
अणु
	काष्ठा fsl_hv_ioctl_start param;

	/* Get the parameters from the user */
	अगर (copy_from_user(&param, p, माप(काष्ठा fsl_hv_ioctl_start)))
		वापस -EFAULT;

	param.ret = fh_partition_start(param.partition, param.entry_poपूर्णांक,
				       param.load);

	अगर (copy_to_user(&p->ret, &param.ret, माप(__u32)))
		वापस -EFAULT;

	वापस 0;
पूर्ण

/*
 * Ioctl पूर्णांकerface क्रम FSL_HV_IOCTL_PARTITION_STOP
 *
 * Stop a running partition
 */
अटल दीर्घ ioctl_stop(काष्ठा fsl_hv_ioctl_stop __user *p)
अणु
	काष्ठा fsl_hv_ioctl_stop param;

	/* Get the parameters from the user */
	अगर (copy_from_user(&param, p, माप(काष्ठा fsl_hv_ioctl_stop)))
		वापस -EFAULT;

	param.ret = fh_partition_stop(param.partition);

	अगर (copy_to_user(&p->ret, &param.ret, माप(__u32)))
		वापस -EFAULT;

	वापस 0;
पूर्ण

/*
 * Ioctl पूर्णांकerface क्रम FSL_HV_IOCTL_MEMCPY
 *
 * The FH_MEMCPY hypercall takes an array of address/address/size काष्ठाures
 * to represent the data being copied.  As a convenience to the user, this
 * ioctl takes a user-create buffer and a poपूर्णांकer to a guest physically
 * contiguous buffer in the remote partition, and creates the
 * address/address/size array क्रम the hypercall.
 */
अटल दीर्घ ioctl_स_नकल(काष्ठा fsl_hv_ioctl_स_नकल __user *p)
अणु
	काष्ठा fsl_hv_ioctl_स_नकल param;

	काष्ठा page **pages = शून्य;
	व्योम *sg_list_unaligned = शून्य;
	काष्ठा fh_sg_list *sg_list = शून्य;

	अचिन्हित पूर्णांक num_pages;
	अचिन्हित दीर्घ lb_offset; /* Offset within a page of the local buffer */

	अचिन्हित पूर्णांक i;
	दीर्घ ret = 0;
	पूर्णांक num_pinned = 0; /* वापस value from get_user_pages_fast() */
	phys_addr_t remote_paddr; /* The next address in the remote buffer */
	uपूर्णांक32_t count; /* The number of bytes left to copy */

	/* Get the parameters from the user */
	अगर (copy_from_user(&param, p, माप(काष्ठा fsl_hv_ioctl_स_नकल)))
		वापस -EFAULT;

	/*
	 * One partition must be local, the other must be remote.  In other
	 * words, अगर source and target are both -1, or are both not -1, then
	 * वापस an error.
	 */
	अगर ((param.source == -1) == (param.target == -1))
		वापस -EINVAL;

	/*
	 * The array of pages वापसed by get_user_pages_fast() covers only
	 * page-aligned memory.  Since the user buffer is probably not
	 * page-aligned, we need to handle the discrepancy.
	 *
	 * We calculate the offset within a page of the S/G list, and make
	 * adjusपंचांगents accordingly.  This will result in a page list that looks
	 * like this:
	 *
	 *      ----    <-- first page starts beक्रमe the buffer
	 *     |    |
	 *     |////|-> ----
	 *     |////|  |    |
	 *      ----   |    |
	 *             |    |
	 *      ----   |    |
	 *     |////|  |    |
	 *     |////|  |    |
	 *     |////|  |    |
	 *      ----   |    |
	 *             |    |
	 *      ----   |    |
	 *     |////|  |    |
	 *     |////|  |    |
	 *     |////|  |    |
	 *      ----   |    |
	 *             |    |
	 *      ----   |    |
	 *     |////|  |    |
	 *     |////|-> ----
	 *     |    |   <-- last page ends after the buffer
	 *      ----
	 *
	 * The distance between the start of the first page and the start of the
	 * buffer is lb_offset.  The hashed (///) areas are the parts of the
	 * page list that contain the actual buffer.
	 *
	 * The advantage of this approach is that the number of pages is
	 * equal to the number of entries in the S/G list that we give to the
	 * hypervisor.
	 */
	lb_offset = param.local_vaddr & (PAGE_SIZE - 1);
	अगर (param.count == 0 ||
	    param.count > U64_MAX - lb_offset - PAGE_SIZE + 1)
		वापस -EINVAL;
	num_pages = (param.count + lb_offset + PAGE_SIZE - 1) >> PAGE_SHIFT;

	/* Allocate the buffers we need */

	/*
	 * 'pages' is an array of struct page pointers that's initialized by
	 * get_user_pages_fast().
	 */
	pages = kसुस्मृति(num_pages, माप(काष्ठा page *), GFP_KERNEL);
	अगर (!pages) अणु
		pr_debug("fsl-hv: could not allocate page list\n");
		वापस -ENOMEM;
	पूर्ण

	/*
	 * sg_list is the list of fh_sg_list objects that we pass to the
	 * hypervisor.
	 */
	sg_list_unaligned = kदो_स्मृति(num_pages * माप(काष्ठा fh_sg_list) +
		माप(काष्ठा fh_sg_list) - 1, GFP_KERNEL);
	अगर (!sg_list_unaligned) अणु
		pr_debug("fsl-hv: could not allocate S/G list\n");
		ret = -ENOMEM;
		जाओ मुक्त_pages;
	पूर्ण
	sg_list = PTR_ALIGN(sg_list_unaligned, माप(काष्ठा fh_sg_list));

	/* Get the physical addresses of the source buffer */
	num_pinned = get_user_pages_fast(param.local_vaddr - lb_offset,
		num_pages, param.source != -1 ? FOLL_WRITE : 0, pages);

	अगर (num_pinned != num_pages) अणु
		pr_debug("fsl-hv: could not lock source buffer\n");
		ret = (num_pinned < 0) ? num_pinned : -EFAULT;
		जाओ निकास;
	पूर्ण

	/*
	 * Build the fh_sg_list[] array.  The first page is special
	 * because it's misaligned.
	 */
	अगर (param.source == -1) अणु
		sg_list[0].source = page_to_phys(pages[0]) + lb_offset;
		sg_list[0].target = param.remote_paddr;
	पूर्ण अन्यथा अणु
		sg_list[0].source = param.remote_paddr;
		sg_list[0].target = page_to_phys(pages[0]) + lb_offset;
	पूर्ण
	sg_list[0].size = min_t(uपूर्णांक64_t, param.count, PAGE_SIZE - lb_offset);

	remote_paddr = param.remote_paddr + sg_list[0].size;
	count = param.count - sg_list[0].size;

	क्रम (i = 1; i < num_pages; i++) अणु
		अगर (param.source == -1) अणु
			/* local to remote */
			sg_list[i].source = page_to_phys(pages[i]);
			sg_list[i].target = remote_paddr;
		पूर्ण अन्यथा अणु
			/* remote to local */
			sg_list[i].source = remote_paddr;
			sg_list[i].target = page_to_phys(pages[i]);
		पूर्ण
		sg_list[i].size = min_t(uपूर्णांक64_t, count, PAGE_SIZE);

		remote_paddr += sg_list[i].size;
		count -= sg_list[i].size;
	पूर्ण

	param.ret = fh_partition_स_नकल(param.source, param.target,
		virt_to_phys(sg_list), num_pages);

निकास:
	अगर (pages && (num_pinned > 0)) अणु
		क्रम (i = 0; i < num_pinned; i++)
			put_page(pages[i]);
	पूर्ण

	kमुक्त(sg_list_unaligned);
मुक्त_pages:
	kमुक्त(pages);

	अगर (!ret)
		अगर (copy_to_user(&p->ret, &param.ret, माप(__u32)))
			वापस -EFAULT;

	वापस ret;
पूर्ण

/*
 * Ioctl पूर्णांकerface क्रम FSL_HV_IOCTL_DOORBELL
 *
 * Ring a करोorbell
 */
अटल दीर्घ ioctl_करोorbell(काष्ठा fsl_hv_ioctl_करोorbell __user *p)
अणु
	काष्ठा fsl_hv_ioctl_करोorbell param;

	/* Get the parameters from the user. */
	अगर (copy_from_user(&param, p, माप(काष्ठा fsl_hv_ioctl_करोorbell)))
		वापस -EFAULT;

	param.ret = ev_करोorbell_send(param.करोorbell);

	अगर (copy_to_user(&p->ret, &param.ret, माप(__u32)))
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल दीर्घ ioctl_dtprop(काष्ठा fsl_hv_ioctl_prop __user *p, पूर्णांक set)
अणु
	काष्ठा fsl_hv_ioctl_prop param;
	अक्षर __user *upath, *upropname;
	व्योम __user *upropval;
	अक्षर *path, *propname;
	व्योम *propval;
	पूर्णांक ret = 0;

	/* Get the parameters from the user. */
	अगर (copy_from_user(&param, p, माप(काष्ठा fsl_hv_ioctl_prop)))
		वापस -EFAULT;

	upath = (अक्षर __user *)(uपूर्णांकptr_t)param.path;
	upropname = (अक्षर __user *)(uपूर्णांकptr_t)param.propname;
	upropval = (व्योम __user *)(uपूर्णांकptr_t)param.propval;

	path = strndup_user(upath, FH_DTPROP_MAX_PATHLEN);
	अगर (IS_ERR(path))
		वापस PTR_ERR(path);

	propname = strndup_user(upropname, FH_DTPROP_MAX_PATHLEN);
	अगर (IS_ERR(propname)) अणु
		ret = PTR_ERR(propname);
		जाओ err_मुक्त_path;
	पूर्ण

	अगर (param.proplen > FH_DTPROP_MAX_PROPLEN) अणु
		ret = -EINVAL;
		जाओ err_मुक्त_propname;
	पूर्ण

	propval = kदो_स्मृति(param.proplen, GFP_KERNEL);
	अगर (!propval) अणु
		ret = -ENOMEM;
		जाओ err_मुक्त_propname;
	पूर्ण

	अगर (set) अणु
		अगर (copy_from_user(propval, upropval, param.proplen)) अणु
			ret = -EFAULT;
			जाओ err_मुक्त_propval;
		पूर्ण

		param.ret = fh_partition_set_dtprop(param.handle,
						    virt_to_phys(path),
						    virt_to_phys(propname),
						    virt_to_phys(propval),
						    param.proplen);
	पूर्ण अन्यथा अणु
		param.ret = fh_partition_get_dtprop(param.handle,
						    virt_to_phys(path),
						    virt_to_phys(propname),
						    virt_to_phys(propval),
						    &param.proplen);

		अगर (param.ret == 0) अणु
			अगर (copy_to_user(upropval, propval, param.proplen) ||
			    put_user(param.proplen, &p->proplen)) अणु
				ret = -EFAULT;
				जाओ err_मुक्त_propval;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (put_user(param.ret, &p->ret))
		ret = -EFAULT;

err_मुक्त_propval:
	kमुक्त(propval);
err_मुक्त_propname:
	kमुक्त(propname);
err_मुक्त_path:
	kमुक्त(path);

	वापस ret;
पूर्ण

/*
 * Ioctl मुख्य entry poपूर्णांक
 */
अटल दीर्घ fsl_hv_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
			 अचिन्हित दीर्घ argaddr)
अणु
	व्योम __user *arg = (व्योम __user *)argaddr;
	दीर्घ ret;

	चयन (cmd) अणु
	हाल FSL_HV_IOCTL_PARTITION_RESTART:
		ret = ioctl_restart(arg);
		अवरोध;
	हाल FSL_HV_IOCTL_PARTITION_GET_STATUS:
		ret = ioctl_status(arg);
		अवरोध;
	हाल FSL_HV_IOCTL_PARTITION_START:
		ret = ioctl_start(arg);
		अवरोध;
	हाल FSL_HV_IOCTL_PARTITION_STOP:
		ret = ioctl_stop(arg);
		अवरोध;
	हाल FSL_HV_IOCTL_MEMCPY:
		ret = ioctl_स_नकल(arg);
		अवरोध;
	हाल FSL_HV_IOCTL_DOORBELL:
		ret = ioctl_करोorbell(arg);
		अवरोध;
	हाल FSL_HV_IOCTL_GETPROP:
		ret = ioctl_dtprop(arg, 0);
		अवरोध;
	हाल FSL_HV_IOCTL_SETPROP:
		ret = ioctl_dtprop(arg, 1);
		अवरोध;
	शेष:
		pr_debug("fsl-hv: bad ioctl dir=%u type=%u cmd=%u size=%u\n",
			 _IOC_सूची(cmd), _IOC_TYPE(cmd), _IOC_NR(cmd),
			 _IOC_SIZE(cmd));
		वापस -ENOTTY;
	पूर्ण

	वापस ret;
पूर्ण

/* Linked list of processes that have us खोलो */
अटल काष्ठा list_head db_list;

/* spinlock क्रम db_list */
अटल DEFINE_SPINLOCK(db_list_lock);

/* The size of the करोorbell event queue.  This must be a घातer of two. */
#घोषणा QSIZE	16

/* Returns the next head/tail poपूर्णांकer, wrapping around the queue अगर necessary */
#घोषणा nextp(x) (((x) + 1) & (QSIZE - 1))

/* Per-खोलो data काष्ठाure */
काष्ठा करोorbell_queue अणु
	काष्ठा list_head list;
	spinlock_t lock;
	रुको_queue_head_t रुको;
	अचिन्हित पूर्णांक head;
	अचिन्हित पूर्णांक tail;
	uपूर्णांक32_t q[QSIZE];
पूर्ण;

/* Linked list of ISRs that we रेजिस्टरed */
काष्ठा list_head isr_list;

/* Per-ISR data काष्ठाure */
काष्ठा करोorbell_isr अणु
	काष्ठा list_head list;
	अचिन्हित पूर्णांक irq;
	uपूर्णांक32_t करोorbell;	/* The करोorbell handle */
	uपूर्णांक32_t partition;	/* The partition handle, अगर used */
पूर्ण;

/*
 * Add a करोorbell to all of the करोorbell queues
 */
अटल व्योम fsl_hv_queue_करोorbell(uपूर्णांक32_t करोorbell)
अणु
	काष्ठा करोorbell_queue *dbq;
	अचिन्हित दीर्घ flags;

	/* Prevent another core from modअगरying db_list */
	spin_lock_irqsave(&db_list_lock, flags);

	list_क्रम_each_entry(dbq, &db_list, list) अणु
		अगर (dbq->head != nextp(dbq->tail)) अणु
			dbq->q[dbq->tail] = करोorbell;
			/*
			 * This memory barrier eliminates the need to grab
			 * the spinlock क्रम dbq.
			 */
			smp_wmb();
			dbq->tail = nextp(dbq->tail);
			wake_up_पूर्णांकerruptible(&dbq->रुको);
		पूर्ण
	पूर्ण

	spin_unlock_irqrestore(&db_list_lock, flags);
पूर्ण

/*
 * Interrupt handler क्रम all करोorbells
 *
 * We use the same पूर्णांकerrupt handler क्रम all करोorbells.  Whenever a करोorbell
 * is rung, and we receive an पूर्णांकerrupt, we just put the handle क्रम that
 * करोorbell (passed to us as *data) पूर्णांकo all of the queues.
 */
अटल irqवापस_t fsl_hv_isr(पूर्णांक irq, व्योम *data)
अणु
	fsl_hv_queue_करोorbell((uपूर्णांकptr_t) data);

	वापस IRQ_HANDLED;
पूर्ण

/*
 * State change thपढ़ो function
 *
 * The state change notअगरication arrives in an पूर्णांकerrupt, but we can't call
 * blocking_notअगरier_call_chain() in an पूर्णांकerrupt handler.  We could call
 * atomic_notअगरier_call_chain(), but that would require the clients' call-back
 * function to run in पूर्णांकerrupt context.  Since we करोn't want to impose that
 * restriction on the clients, we use a thपढ़ोed IRQ to process the
 * notअगरication in kernel context.
 */
अटल irqवापस_t fsl_hv_state_change_thपढ़ो(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा करोorbell_isr *dbisr = data;

	blocking_notअगरier_call_chain(&failover_subscribers, dbisr->partition,
				     शून्य);

	वापस IRQ_HANDLED;
पूर्ण

/*
 * Interrupt handler क्रम state-change करोorbells
 */
अटल irqवापस_t fsl_hv_state_change_isr(पूर्णांक irq, व्योम *data)
अणु
	अचिन्हित पूर्णांक status;
	काष्ठा करोorbell_isr *dbisr = data;
	पूर्णांक ret;

	/* It's still a करोorbell, so add it to all the queues. */
	fsl_hv_queue_करोorbell(dbisr->करोorbell);

	/* Determine the new state, and अगर it's stopped, notअगरy the clients. */
	ret = fh_partition_get_status(dbisr->partition, &status);
	अगर (!ret && (status == FH_PARTITION_STOPPED))
		वापस IRQ_WAKE_THREAD;

	वापस IRQ_HANDLED;
पूर्ण

/*
 * Returns a biपंचांगask indicating whether a पढ़ो will block
 */
अटल __poll_t fsl_hv_poll(काष्ठा file *filp, काष्ठा poll_table_काष्ठा *p)
अणु
	काष्ठा करोorbell_queue *dbq = filp->निजी_data;
	अचिन्हित दीर्घ flags;
	__poll_t mask;

	spin_lock_irqsave(&dbq->lock, flags);

	poll_रुको(filp, &dbq->रुको, p);
	mask = (dbq->head == dbq->tail) ? 0 : (EPOLLIN | EPOLLRDNORM);

	spin_unlock_irqrestore(&dbq->lock, flags);

	वापस mask;
पूर्ण

/*
 * Return the handles क्रम any incoming करोorbells
 *
 * If there are करोorbell handles in the queue क्रम this खोलो instance, then
 * वापस them to the caller as an array of 32-bit पूर्णांकegers.  Otherwise,
 * block until there is at least one handle to वापस.
 */
अटल sमाप_प्रकार fsl_hv_पढ़ो(काष्ठा file *filp, अक्षर __user *buf, माप_प्रकार len,
			   loff_t *off)
अणु
	काष्ठा करोorbell_queue *dbq = filp->निजी_data;
	uपूर्णांक32_t __user *p = (uपूर्णांक32_t __user *) buf; /* क्रम put_user() */
	अचिन्हित दीर्घ flags;
	sमाप_प्रकार count = 0;

	/* Make sure we stop when the user buffer is full. */
	जबतक (len >= माप(uपूर्णांक32_t)) अणु
		uपूर्णांक32_t dbell;	/* Local copy of करोorbell queue data */

		spin_lock_irqsave(&dbq->lock, flags);

		/*
		 * If the queue is empty, then either we're करोne or we need
		 * to block.  If the application specअगरied O_NONBLOCK, then
		 * we वापस the appropriate error code.
		 */
		अगर (dbq->head == dbq->tail) अणु
			spin_unlock_irqrestore(&dbq->lock, flags);
			अगर (count)
				अवरोध;
			अगर (filp->f_flags & O_NONBLOCK)
				वापस -EAGAIN;
			अगर (रुको_event_पूर्णांकerruptible(dbq->रुको,
						     dbq->head != dbq->tail))
				वापस -ERESTARTSYS;
			जारी;
		पूर्ण

		/*
		 * Even though we have an smp_wmb() in the ISR, the core
		 * might speculatively execute the "dbell = ..." below जबतक
		 * it's evaluating the अगर-statement above.  In that हाल, the
		 * value put पूर्णांकo dbell could be stale अगर the core accepts the
		 * speculation. To prevent that, we need a पढ़ो memory barrier
		 * here as well.
		 */
		smp_rmb();

		/* Copy the data to a temporary local buffer, because
		 * we can't call copy_to_user() from inside a spinlock
		 */
		dbell = dbq->q[dbq->head];
		dbq->head = nextp(dbq->head);

		spin_unlock_irqrestore(&dbq->lock, flags);

		अगर (put_user(dbell, p))
			वापस -EFAULT;
		p++;
		count += माप(uपूर्णांक32_t);
		len -= माप(uपूर्णांक32_t);
	पूर्ण

	वापस count;
पूर्ण

/*
 * Open the driver and prepare क्रम पढ़ोing करोorbells.
 *
 * Every समय an application खोलोs the driver, we create a करोorbell queue
 * क्रम that file handle.  This queue is used क्रम any incoming करोorbells.
 */
अटल पूर्णांक fsl_hv_खोलो(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा करोorbell_queue *dbq;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;

	dbq = kzalloc(माप(काष्ठा करोorbell_queue), GFP_KERNEL);
	अगर (!dbq) अणु
		pr_err("fsl-hv: out of memory\n");
		वापस -ENOMEM;
	पूर्ण

	spin_lock_init(&dbq->lock);
	init_रुकोqueue_head(&dbq->रुको);

	spin_lock_irqsave(&db_list_lock, flags);
	list_add(&dbq->list, &db_list);
	spin_unlock_irqrestore(&db_list_lock, flags);

	filp->निजी_data = dbq;

	वापस ret;
पूर्ण

/*
 * Close the driver
 */
अटल पूर्णांक fsl_hv_बंद(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा करोorbell_queue *dbq = filp->निजी_data;
	अचिन्हित दीर्घ flags;

	पूर्णांक ret = 0;

	spin_lock_irqsave(&db_list_lock, flags);
	list_del(&dbq->list);
	spin_unlock_irqrestore(&db_list_lock, flags);

	kमुक्त(dbq);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा file_operations fsl_hv_fops = अणु
	.owner = THIS_MODULE,
	.खोलो = fsl_hv_खोलो,
	.release = fsl_hv_बंद,
	.poll = fsl_hv_poll,
	.पढ़ो = fsl_hv_पढ़ो,
	.unlocked_ioctl = fsl_hv_ioctl,
	.compat_ioctl = compat_ptr_ioctl,
पूर्ण;

अटल काष्ठा miscdevice fsl_hv_misc_dev = अणु
	MISC_DYNAMIC_MINOR,
	"fsl-hv",
	&fsl_hv_fops
पूर्ण;

अटल irqवापस_t fsl_hv_shutकरोwn_isr(पूर्णांक irq, व्योम *data)
अणु
	orderly_घातeroff(false);

	वापस IRQ_HANDLED;
पूर्ण

/*
 * Returns the handle of the parent of the given node
 *
 * The handle is the value of the 'hv-handle' property
 */
अटल पूर्णांक get_parent_handle(काष्ठा device_node *np)
अणु
	काष्ठा device_node *parent;
	स्थिर uपूर्णांक32_t *prop;
	uपूर्णांक32_t handle;
	पूर्णांक len;

	parent = of_get_parent(np);
	अगर (!parent)
		/* It's not really possible क्रम this to fail */
		वापस -ENODEV;

	/*
	 * The proper name क्रम the handle property is "hv-handle", but some
	 * older versions of the hypervisor used "reg".
	 */
	prop = of_get_property(parent, "hv-handle", &len);
	अगर (!prop)
		prop = of_get_property(parent, "reg", &len);

	अगर (!prop || (len != माप(uपूर्णांक32_t))) अणु
		/* This can happen only अगर the node is malक्रमmed */
		of_node_put(parent);
		वापस -ENODEV;
	पूर्ण

	handle = be32_to_cpup(prop);
	of_node_put(parent);

	वापस handle;
पूर्ण

/*
 * Register a callback क्रम failover events
 *
 * This function is called by device drivers to रेजिस्टर their callback
 * functions क्रम fail-over events.
 */
पूर्णांक fsl_hv_failover_रेजिस्टर(काष्ठा notअगरier_block *nb)
अणु
	वापस blocking_notअगरier_chain_रेजिस्टर(&failover_subscribers, nb);
पूर्ण
EXPORT_SYMBOL(fsl_hv_failover_रेजिस्टर);

/*
 * Unरेजिस्टर a callback क्रम failover events
 */
पूर्णांक fsl_hv_failover_unरेजिस्टर(काष्ठा notअगरier_block *nb)
अणु
	वापस blocking_notअगरier_chain_unरेजिस्टर(&failover_subscribers, nb);
पूर्ण
EXPORT_SYMBOL(fsl_hv_failover_unरेजिस्टर);

/*
 * Return TRUE अगर we're running under FSL hypervisor
 *
 * This function checks to see अगर we're running under the Freescale
 * hypervisor, and वापसs zero अगर we're not, or non-zero अगर we are.
 *
 * First, it checks अगर MSR[GS]==1, which means we're running under some
 * hypervisor.  Then it checks अगर there is a hypervisor node in the device
 * tree.  Currently, that means there needs to be a node in the root called
 * "hypervisor" and which has a property named "fsl,hv-version".
 */
अटल पूर्णांक has_fsl_hypervisor(व्योम)
अणु
	काष्ठा device_node *node;
	पूर्णांक ret;

	node = of_find_node_by_path("/hypervisor");
	अगर (!node)
		वापस 0;

	ret = of_find_property(node, "fsl,hv-version", शून्य) != शून्य;

	of_node_put(node);

	वापस ret;
पूर्ण

/*
 * Freescale hypervisor management driver init
 *
 * This function is called when this module is loaded.
 *
 * Register ourselves as a miscellaneous driver.  This will रेजिस्टर the
 * fops काष्ठाure and create the right sysfs entries क्रम udev.
 */
अटल पूर्णांक __init fsl_hypervisor_init(व्योम)
अणु
	काष्ठा device_node *np;
	काष्ठा करोorbell_isr *dbisr, *n;
	पूर्णांक ret;

	pr_info("Freescale hypervisor management driver\n");

	अगर (!has_fsl_hypervisor()) अणु
		pr_info("fsl-hv: no hypervisor found\n");
		वापस -ENODEV;
	पूर्ण

	ret = misc_रेजिस्टर(&fsl_hv_misc_dev);
	अगर (ret) अणु
		pr_err("fsl-hv: cannot register device\n");
		वापस ret;
	पूर्ण

	INIT_LIST_HEAD(&db_list);
	INIT_LIST_HEAD(&isr_list);

	क्रम_each_compatible_node(np, शून्य, "epapr,hv-receive-doorbell") अणु
		अचिन्हित पूर्णांक irq;
		स्थिर uपूर्णांक32_t *handle;

		handle = of_get_property(np, "interrupts", शून्य);
		irq = irq_of_parse_and_map(np, 0);
		अगर (!handle || (irq == NO_IRQ)) अणु
			pr_err("fsl-hv: no 'interrupts' property in %pOF node\n",
				np);
			जारी;
		पूर्ण

		dbisr = kzalloc(माप(*dbisr), GFP_KERNEL);
		अगर (!dbisr)
			जाओ out_of_memory;

		dbisr->irq = irq;
		dbisr->करोorbell = be32_to_cpup(handle);

		अगर (of_device_is_compatible(np, "fsl,hv-shutdown-doorbell")) अणु
			/* The shutकरोwn करोorbell माला_लो its own ISR */
			ret = request_irq(irq, fsl_hv_shutकरोwn_isr, 0,
					  np->name, शून्य);
		पूर्ण अन्यथा अगर (of_device_is_compatible(np,
			"fsl,hv-state-change-doorbell")) अणु
			/*
			 * The state change करोorbell triggers a notअगरication अगर
			 * the state of the managed partition changes to
			 * "stopped". We need a separate पूर्णांकerrupt handler क्रम
			 * that, and we also need to know the handle of the
			 * target partition, not just the handle of the
			 * करोorbell.
			 */
			dbisr->partition = ret = get_parent_handle(np);
			अगर (ret < 0) अणु
				pr_err("fsl-hv: node %pOF has missing or "
				       "malformed parent\n", np);
				kमुक्त(dbisr);
				जारी;
			पूर्ण
			ret = request_thपढ़ोed_irq(irq, fsl_hv_state_change_isr,
						   fsl_hv_state_change_thपढ़ो,
						   0, np->name, dbisr);
		पूर्ण अन्यथा
			ret = request_irq(irq, fsl_hv_isr, 0, np->name, dbisr);

		अगर (ret < 0) अणु
			pr_err("fsl-hv: could not request irq %u for node %pOF\n",
			       irq, np);
			kमुक्त(dbisr);
			जारी;
		पूर्ण

		list_add(&dbisr->list, &isr_list);

		pr_info("fsl-hv: registered handler for doorbell %u\n",
			dbisr->करोorbell);
	पूर्ण

	वापस 0;

out_of_memory:
	list_क्रम_each_entry_safe(dbisr, n, &isr_list, list) अणु
		मुक्त_irq(dbisr->irq, dbisr);
		list_del(&dbisr->list);
		kमुक्त(dbisr);
	पूर्ण

	misc_deरेजिस्टर(&fsl_hv_misc_dev);

	वापस -ENOMEM;
पूर्ण

/*
 * Freescale hypervisor management driver termination
 *
 * This function is called when this driver is unloaded.
 */
अटल व्योम __निकास fsl_hypervisor_निकास(व्योम)
अणु
	काष्ठा करोorbell_isr *dbisr, *n;

	list_क्रम_each_entry_safe(dbisr, n, &isr_list, list) अणु
		मुक्त_irq(dbisr->irq, dbisr);
		list_del(&dbisr->list);
		kमुक्त(dbisr);
	पूर्ण

	misc_deरेजिस्टर(&fsl_hv_misc_dev);
पूर्ण

module_init(fsl_hypervisor_init);
module_निकास(fsl_hypervisor_निकास);

MODULE_AUTHOR("Timur Tabi <timur@freescale.com>");
MODULE_DESCRIPTION("Freescale hypervisor management driver");
MODULE_LICENSE("GPL v2");
