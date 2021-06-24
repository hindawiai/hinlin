<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *
 *			Linux MegaRAID device driver
 *
 * Copyright (c) 2003-2004  LSI Logic Corporation.
 *
 * खाता		: megaraid_mm.c
 * Version	: v2.20.2.7 (Jul 16 2006)
 *
 * Common management module
 */
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/mutex.h>
#समावेश "megaraid_mm.h"


// Entry poपूर्णांकs क्रम अक्षर node driver
अटल DEFINE_MUTEX(mraid_mm_mutex);
अटल पूर्णांक mraid_mm_खोलो(काष्ठा inode *, काष्ठा file *);
अटल दीर्घ mraid_mm_unlocked_ioctl(काष्ठा file *, uपूर्णांक, अचिन्हित दीर्घ);


// routines to convert to and from the old the क्रमmat
अटल पूर्णांक mimd_to_kioc(mimd_t __user *, mraid_mmadp_t *, uioc_t *);
अटल पूर्णांक kioc_to_mimd(uioc_t *, mimd_t __user *);


// Helper functions
अटल पूर्णांक handle_drvrcmd(व्योम __user *, uपूर्णांक8_t, पूर्णांक *);
अटल पूर्णांक lld_ioctl(mraid_mmadp_t *, uioc_t *);
अटल व्योम ioctl_करोne(uioc_t *);
अटल व्योम lld_समयकरोut(काष्ठा समयr_list *);
अटल व्योम hinfo_to_cinfo(mraid_hba_info_t *, mcontroller_t *);
अटल mraid_mmadp_t *mraid_mm_get_adapter(mimd_t __user *, पूर्णांक *);
अटल uioc_t *mraid_mm_alloc_kioc(mraid_mmadp_t *);
अटल व्योम mraid_mm_dealloc_kioc(mraid_mmadp_t *, uioc_t *);
अटल पूर्णांक mraid_mm_attach_buf(mraid_mmadp_t *, uioc_t *, पूर्णांक);
अटल पूर्णांक mraid_mm_setup_dma_pools(mraid_mmadp_t *);
अटल व्योम mraid_mm_मुक्त_adp_resources(mraid_mmadp_t *);
अटल व्योम mraid_mm_tearकरोwn_dma_pools(mraid_mmadp_t *);

MODULE_AUTHOR("LSI Logic Corporation");
MODULE_DESCRIPTION("LSI Logic Management Module");
MODULE_LICENSE("GPL");
MODULE_VERSION(LSI_COMMON_MOD_VERSION);

अटल पूर्णांक dbglevel = CL_ANN;
module_param_named(dlevel, dbglevel, पूर्णांक, 0);
MODULE_PARM_DESC(dlevel, "Debug level (default=0)");

EXPORT_SYMBOL(mraid_mm_रेजिस्टर_adp);
EXPORT_SYMBOL(mraid_mm_unरेजिस्टर_adp);
EXPORT_SYMBOL(mraid_mm_adapter_app_handle);

अटल uपूर्णांक32_t drvr_ver	= 0x02200207;

अटल पूर्णांक adapters_count_g;
अटल काष्ठा list_head adapters_list_g;

अटल रुको_queue_head_t रुको_q;

अटल स्थिर काष्ठा file_operations lsi_fops = अणु
	.खोलो	= mraid_mm_खोलो,
	.unlocked_ioctl = mraid_mm_unlocked_ioctl,
	.compat_ioctl = compat_ptr_ioctl,
	.owner	= THIS_MODULE,
	.llseek = noop_llseek,
पूर्ण;

अटल काष्ठा miscdevice megaraid_mm_dev = अणु
	.minor	= MISC_DYNAMIC_MINOR,
	.name   = "megadev0",
	.fops   = &lsi_fops,
पूर्ण;

/**
 * mraid_mm_खोलो - खोलो routine क्रम अक्षर node पूर्णांकerface
 * @inode	: unused
 * @filep	: unused
 *
 * Allow ioctl operations by apps only अगर they have superuser privilege.
 */
अटल पूर्णांक
mraid_mm_खोलो(काष्ठा inode *inode, काष्ठा file *filep)
अणु
	/*
	 * Only allow superuser to access निजी ioctl पूर्णांकerface
	 */
	अगर (!capable(CAP_SYS_ADMIN)) वापस (-EACCES);

	वापस 0;
पूर्ण

/**
 * mraid_mm_ioctl - module entry-poपूर्णांक क्रम ioctls
 * @filep	: file operations poपूर्णांकer (ignored)
 * @cmd		: ioctl command
 * @arg		: user ioctl packet
 */
अटल पूर्णांक
mraid_mm_ioctl(काष्ठा file *filep, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	uioc_t		*kioc;
	अक्षर		signature[EXT_IOCTL_SIGN_SZ]	= अणु0पूर्ण;
	पूर्णांक		rval;
	mraid_mmadp_t	*adp;
	uपूर्णांक8_t		old_ioctl;
	पूर्णांक		drvrcmd_rval;
	व्योम __user *argp = (व्योम __user *)arg;

	/*
	 * Make sure only USCSICMD are issued through this पूर्णांकerface.
	 * MIMD application would still fire dअगरferent command.
	 */

	अगर ((_IOC_TYPE(cmd) != MEGAIOC_MAGIC) && (cmd != USCSICMD)) अणु
		वापस (-EINVAL);
	पूर्ण

	/*
	 * Look क्रम signature to see अगर this is the new or old ioctl क्रमmat.
	 */
	अगर (copy_from_user(signature, argp, EXT_IOCTL_SIGN_SZ)) अणु
		con_log(CL_ANN, (KERN_WARNING
			"megaraid cmm: copy from usr addr failed\n"));
		वापस (-EFAULT);
	पूर्ण

	अगर (स_भेद(signature, EXT_IOCTL_SIGN, EXT_IOCTL_SIGN_SZ) == 0)
		old_ioctl = 0;
	अन्यथा
		old_ioctl = 1;

	/*
	 * At present, we करोn't support the new ioctl packet
	 */
	अगर (!old_ioctl )
		वापस (-EINVAL);

	/*
	 * If it is a driver ioctl (as opposed to fw ioctls), then we can
	 * handle the command locally. rval > 0 means it is not a drvr cmd
	 */
	rval = handle_drvrcmd(argp, old_ioctl, &drvrcmd_rval);

	अगर (rval < 0)
		वापस rval;
	अन्यथा अगर (rval == 0)
		वापस drvrcmd_rval;

	rval = 0;
	अगर ((adp = mraid_mm_get_adapter(argp, &rval)) == शून्य) अणु
		वापस rval;
	पूर्ण

	/*
	 * Check अगर adapter can accept ioctl. We may have marked it offline
	 * अगर any previous kioc had समयकरोut on this controller.
	 */
	अगर (!adp->quiescent) अणु
		con_log(CL_ANN, (KERN_WARNING
			"megaraid cmm: controller cannot accept cmds due to "
			"earlier errors\n" ));
		वापस -EFAULT;
	पूर्ण

	/*
	 * The following call will block till a kioc is available
	 * or वापस शून्य अगर the list head is empty क्रम the poपूर्णांकer
	 * of type mraid_mmapt passed to mraid_mm_alloc_kioc
	 */
	kioc = mraid_mm_alloc_kioc(adp);
	अगर (!kioc)
		वापस -ENXIO;

	/*
	 * User sent the old mimd_t ioctl packet. Convert it to uioc_t.
	 */
	अगर ((rval = mimd_to_kioc(argp, adp, kioc))) अणु
		mraid_mm_dealloc_kioc(adp, kioc);
		वापस rval;
	पूर्ण

	kioc->करोne = ioctl_करोne;

	/*
	 * Issue the IOCTL to the low level driver. After the IOCTL completes
	 * release the kioc अगर and only अगर it was _not_ समयकरोut. If it was
	 * समयकरोut, that means that resources are still with low level driver.
	 */
	अगर ((rval = lld_ioctl(adp, kioc))) अणु

		अगर (!kioc->समयकरोut)
			mraid_mm_dealloc_kioc(adp, kioc);

		वापस rval;
	पूर्ण

	/*
	 * Convert the kioc back to user space
	 */
	rval = kioc_to_mimd(kioc, argp);

	/*
	 * Return the kioc to मुक्त pool
	 */
	mraid_mm_dealloc_kioc(adp, kioc);

	वापस rval;
पूर्ण

अटल दीर्घ
mraid_mm_unlocked_ioctl(काष्ठा file *filep, अचिन्हित पूर्णांक cmd,
		        अचिन्हित दीर्घ arg)
अणु
	पूर्णांक err;

	mutex_lock(&mraid_mm_mutex);
	err = mraid_mm_ioctl(filep, cmd, arg);
	mutex_unlock(&mraid_mm_mutex);

	वापस err;
पूर्ण

/**
 * mraid_mm_get_adapter - Returns corresponding adapters क्रम the mimd packet
 * @umimd	: User space mimd_t ioctl packet
 * @rval	: वापसed success/error status
 *
 * The function वापस value is a poपूर्णांकer to the located @adapter.
 */
अटल mraid_mmadp_t *
mraid_mm_get_adapter(mimd_t __user *umimd, पूर्णांक *rval)
अणु
	mraid_mmadp_t	*adapter;
	mimd_t		mimd;
	uपूर्णांक32_t	adapno;
	पूर्णांक		iterator;


	अगर (copy_from_user(&mimd, umimd, माप(mimd_t))) अणु
		*rval = -EFAULT;
		वापस शून्य;
	पूर्ण

	adapno = GETADAP(mimd.ui.fcs.adapno);

	अगर (adapno >= adapters_count_g) अणु
		*rval = -ENODEV;
		वापस शून्य;
	पूर्ण

	adapter = शून्य;
	iterator = 0;

	list_क्रम_each_entry(adapter, &adapters_list_g, list) अणु
		अगर (iterator++ == adapno) अवरोध;
	पूर्ण

	अगर (!adapter) अणु
		*rval = -ENODEV;
		वापस शून्य;
	पूर्ण

	वापस adapter;
पूर्ण

/**
 * handle_drvrcmd - Checks अगर the opcode is a driver cmd and अगर it is, handles it.
 * @arg		: packet sent by the user app
 * @old_ioctl	: mimd अगर 1; uioc otherwise
 * @rval	: poपूर्णांकer क्रम command's वापसed value (not function status)
 */
अटल पूर्णांक
handle_drvrcmd(व्योम __user *arg, uपूर्णांक8_t old_ioctl, पूर्णांक *rval)
अणु
	mimd_t		__user *umimd;
	mimd_t		kmimd;
	uपूर्णांक8_t		opcode;
	uपूर्णांक8_t		subopcode;

	अगर (old_ioctl)
		जाओ old_packet;
	अन्यथा
		जाओ new_packet;

new_packet:
	वापस (-ENOTSUPP);

old_packet:
	*rval = 0;
	umimd = arg;

	अगर (copy_from_user(&kmimd, umimd, माप(mimd_t)))
		वापस (-EFAULT);

	opcode		= kmimd.ui.fcs.opcode;
	subopcode	= kmimd.ui.fcs.subopcode;

	/*
	 * If the opcode is 0x82 and the subopcode is either GET_DRVRVER or
	 * GET_NUMADP, then we can handle. Otherwise we should वापस 1 to
	 * indicate that we cannot handle this.
	 */
	अगर (opcode != 0x82)
		वापस 1;

	चयन (subopcode) अणु

	हाल MEGAIOC_QDRVRVER:

		अगर (copy_to_user(kmimd.data, &drvr_ver, माप(uपूर्णांक32_t)))
			वापस (-EFAULT);

		वापस 0;

	हाल MEGAIOC_QNADAP:

		*rval = adapters_count_g;

		अगर (copy_to_user(kmimd.data, &adapters_count_g,
				माप(uपूर्णांक32_t)))
			वापस (-EFAULT);

		वापस 0;

	शेष:
		/* cannot handle */
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण


/**
 * mimd_to_kioc	- Converter from old to new ioctl क्रमmat
 * @umimd	: user space old MIMD IOCTL
 * @adp		: adapter softstate
 * @kioc	: kernel space new क्रमmat IOCTL
 *
 * Routine to convert MIMD पूर्णांकerface IOCTL to new पूर्णांकerface IOCTL packet. The
 * new packet is in kernel space so that driver can perक्रमm operations on it
 * मुक्तly.
 */

अटल पूर्णांक
mimd_to_kioc(mimd_t __user *umimd, mraid_mmadp_t *adp, uioc_t *kioc)
अणु
	mbox64_t		*mbox64;
	mbox_t			*mbox;
	mraid_passthru_t	*pthru32;
	uपूर्णांक32_t		adapno;
	uपूर्णांक8_t			opcode;
	uपूर्णांक8_t			subopcode;
	mimd_t			mimd;

	अगर (copy_from_user(&mimd, umimd, माप(mimd_t)))
		वापस (-EFAULT);

	/*
	 * Applications are not allowed to send extd pthru
	 */
	अगर ((mimd.mbox[0] == MBOXCMD_PASSTHRU64) ||
			(mimd.mbox[0] == MBOXCMD_EXTPTHRU))
		वापस (-EINVAL);

	opcode		= mimd.ui.fcs.opcode;
	subopcode	= mimd.ui.fcs.subopcode;
	adapno		= GETADAP(mimd.ui.fcs.adapno);

	अगर (adapno >= adapters_count_g)
		वापस (-ENODEV);

	kioc->adapno	= adapno;
	kioc->mb_type	= MBOX_LEGACY;
	kioc->app_type	= APPTYPE_MIMD;

	चयन (opcode) अणु

	हाल 0x82:

		अगर (subopcode == MEGAIOC_QADAPINFO) अणु

			kioc->opcode	= GET_ADAP_INFO;
			kioc->data_dir	= UIOC_RD;
			kioc->xferlen	= माप(mraid_hba_info_t);

			अगर (mraid_mm_attach_buf(adp, kioc, kioc->xferlen))
				वापस (-ENOMEM);
		पूर्ण
		अन्यथा अणु
			con_log(CL_ANN, (KERN_WARNING
					"megaraid cmm: Invalid subop\n"));
			वापस (-EINVAL);
		पूर्ण

		अवरोध;

	हाल 0x81:

		kioc->opcode		= MBOX_CMD;
		kioc->xferlen		= mimd.ui.fcs.length;
		kioc->user_data_len	= kioc->xferlen;
		kioc->user_data		= mimd.ui.fcs.buffer;

		अगर (mraid_mm_attach_buf(adp, kioc, kioc->xferlen))
			वापस (-ENOMEM);

		अगर (mimd.outlen) kioc->data_dir  = UIOC_RD;
		अगर (mimd.inlen) kioc->data_dir |= UIOC_WR;

		अवरोध;

	हाल 0x80:

		kioc->opcode		= MBOX_CMD;
		kioc->xferlen		= (mimd.outlen > mimd.inlen) ?
						mimd.outlen : mimd.inlen;
		kioc->user_data_len	= kioc->xferlen;
		kioc->user_data		= mimd.data;

		अगर (mraid_mm_attach_buf(adp, kioc, kioc->xferlen))
			वापस (-ENOMEM);

		अगर (mimd.outlen) kioc->data_dir  = UIOC_RD;
		अगर (mimd.inlen) kioc->data_dir |= UIOC_WR;

		अवरोध;

	शेष:
		वापस (-EINVAL);
	पूर्ण

	/*
	 * If driver command, nothing अन्यथा to करो
	 */
	अगर (opcode == 0x82)
		वापस 0;

	/*
	 * This is a mailbox cmd; copy the mailbox from mimd
	 */
	mbox64	= (mbox64_t *)((अचिन्हित दीर्घ)kioc->cmdbuf);
	mbox	= &mbox64->mbox32;
	स_नकल(mbox, mimd.mbox, 14);

	अगर (mbox->cmd != MBOXCMD_PASSTHRU) अणु	// regular DCMD

		mbox->xferaddr	= (uपूर्णांक32_t)kioc->buf_paddr;

		अगर (kioc->data_dir & UIOC_WR) अणु
			अगर (copy_from_user(kioc->buf_vaddr, kioc->user_data,
							kioc->xferlen)) अणु
				वापस (-EFAULT);
			पूर्ण
		पूर्ण

		वापस 0;
	पूर्ण

	/*
	 * This is a regular 32-bit pthru cmd; mbox poपूर्णांकs to pthru काष्ठा.
	 * Just like in above हाल, the beginning क्रम memblk is treated as
	 * a mailbox. The passthru will begin at next 1K boundary. And the
	 * data will start 1K after that.
	 */
	pthru32			= kioc->pthru32;
	kioc->user_pthru	= &umimd->pthru;
	mbox->xferaddr		= (uपूर्णांक32_t)kioc->pthru32_h;

	अगर (copy_from_user(pthru32, kioc->user_pthru,
			माप(mraid_passthru_t))) अणु
		वापस (-EFAULT);
	पूर्ण

	pthru32->dataxferaddr	= kioc->buf_paddr;
	अगर (kioc->data_dir & UIOC_WR) अणु
		अगर (pthru32->dataxferlen > kioc->xferlen)
			वापस -EINVAL;
		अगर (copy_from_user(kioc->buf_vaddr, kioc->user_data,
						pthru32->dataxferlen)) अणु
			वापस (-EFAULT);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/**
 * mraid_mm_attach_buf - Attach a मुक्त dma buffer क्रम required size
 * @adp		: Adapter softstate
 * @kioc	: kioc that the buffer needs to be attached to
 * @xferlen	: required length क्रम buffer
 *
 * First we search क्रम a pool with smallest buffer that is >= @xferlen. If
 * that pool has no मुक्त buffer, we will try क्रम the next bigger size. If none
 * is available, we will try to allocate the smallest buffer that is >=
 * @xferlen and attach it the pool.
 */
अटल पूर्णांक
mraid_mm_attach_buf(mraid_mmadp_t *adp, uioc_t *kioc, पूर्णांक xferlen)
अणु
	mm_dmapool_t	*pool;
	पूर्णांक		right_pool = -1;
	अचिन्हित दीर्घ	flags;
	पूर्णांक		i;

	kioc->pool_index	= -1;
	kioc->buf_vaddr		= शून्य;
	kioc->buf_paddr		= 0;
	kioc->मुक्त_buf		= 0;

	/*
	 * We need xferlen amount of memory. See अगर we can get it from our
	 * dma pools. If we करोn't get exact size, we will try bigger buffer
	 */

	क्रम (i = 0; i < MAX_DMA_POOLS; i++) अणु

		pool = &adp->dma_pool_list[i];

		अगर (xferlen > pool->buf_size)
			जारी;

		अगर (right_pool == -1)
			right_pool = i;

		spin_lock_irqsave(&pool->lock, flags);

		अगर (!pool->in_use) अणु

			pool->in_use		= 1;
			kioc->pool_index	= i;
			kioc->buf_vaddr		= pool->vaddr;
			kioc->buf_paddr		= pool->paddr;

			spin_unlock_irqrestore(&pool->lock, flags);
			वापस 0;
		पूर्ण
		अन्यथा अणु
			spin_unlock_irqrestore(&pool->lock, flags);
			जारी;
		पूर्ण
	पूर्ण

	/*
	 * If xferlen करोesn't match any of our pools, वापस error
	 */
	अगर (right_pool == -1)
		वापस -EINVAL;

	/*
	 * We did not get any buffer from the pपुनः_स्मृतिated pool. Let us try
	 * to allocate one new buffer. NOTE: This is a blocking call.
	 */
	pool = &adp->dma_pool_list[right_pool];

	spin_lock_irqsave(&pool->lock, flags);

	kioc->pool_index	= right_pool;
	kioc->मुक्त_buf		= 1;
	kioc->buf_vaddr		= dma_pool_alloc(pool->handle, GFP_ATOMIC,
							&kioc->buf_paddr);
	spin_unlock_irqrestore(&pool->lock, flags);

	अगर (!kioc->buf_vaddr)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

/**
 * mraid_mm_alloc_kioc - Returns a uioc_t from मुक्त list
 * @adp	: Adapter softstate क्रम this module
 *
 * The kioc_semaphore is initialized with number of kioc nodes in the
 * मुक्त kioc pool. If the kioc pool is empty, this function blocks till
 * a kioc becomes मुक्त.
 */
अटल uioc_t *
mraid_mm_alloc_kioc(mraid_mmadp_t *adp)
अणु
	uioc_t			*kioc;
	काष्ठा list_head*	head;
	अचिन्हित दीर्घ		flags;

	करोwn(&adp->kioc_semaphore);

	spin_lock_irqsave(&adp->kioc_pool_lock, flags);

	head = &adp->kioc_pool;

	अगर (list_empty(head)) अणु
		up(&adp->kioc_semaphore);
		spin_unlock_irqrestore(&adp->kioc_pool_lock, flags);

		con_log(CL_ANN, ("megaraid cmm: kioc list empty!\n"));
		वापस शून्य;
	पूर्ण

	kioc = list_entry(head->next, uioc_t, list);
	list_del_init(&kioc->list);

	spin_unlock_irqrestore(&adp->kioc_pool_lock, flags);

	स_रखो((caddr_t)(अचिन्हित दीर्घ)kioc->cmdbuf, 0, माप(mbox64_t));
	स_रखो((caddr_t) kioc->pthru32, 0, माप(mraid_passthru_t));

	kioc->buf_vaddr		= शून्य;
	kioc->buf_paddr		= 0;
	kioc->pool_index	=-1;
	kioc->मुक्त_buf		= 0;
	kioc->user_data		= शून्य;
	kioc->user_data_len	= 0;
	kioc->user_pthru	= शून्य;
	kioc->समयकरोut		= 0;

	वापस kioc;
पूर्ण

/**
 * mraid_mm_dealloc_kioc - Return kioc to मुक्त pool
 * @adp		: Adapter softstate
 * @kioc	: uioc_t node to be वापसed to मुक्त pool
 */
अटल व्योम
mraid_mm_dealloc_kioc(mraid_mmadp_t *adp, uioc_t *kioc)
अणु
	mm_dmapool_t	*pool;
	अचिन्हित दीर्घ	flags;

	अगर (kioc->pool_index != -1) अणु
		pool = &adp->dma_pool_list[kioc->pool_index];

		/* This routine may be called in non-isr context also */
		spin_lock_irqsave(&pool->lock, flags);

		/*
		 * While attaching the dma buffer, अगर we didn't get the 
		 * required buffer from the pool, we would have allocated 
		 * it at the run समय and set the मुक्त_buf flag. We must 
		 * मुक्त that buffer. Otherwise, just mark that the buffer is 
		 * not in use
		 */
		अगर (kioc->मुक्त_buf == 1)
			dma_pool_मुक्त(pool->handle, kioc->buf_vaddr, 
							kioc->buf_paddr);
		अन्यथा
			pool->in_use = 0;

		spin_unlock_irqrestore(&pool->lock, flags);
	पूर्ण

	/* Return the kioc to the मुक्त pool */
	spin_lock_irqsave(&adp->kioc_pool_lock, flags);
	list_add(&kioc->list, &adp->kioc_pool);
	spin_unlock_irqrestore(&adp->kioc_pool_lock, flags);

	/* increment the मुक्त kioc count */
	up(&adp->kioc_semaphore);

	वापस;
पूर्ण

/**
 * lld_ioctl - Routine to issue ioctl to low level drvr
 * @adp		: The adapter handle
 * @kioc	: The ioctl packet with kernel addresses
 */
अटल पूर्णांक
lld_ioctl(mraid_mmadp_t *adp, uioc_t *kioc)
अणु
	पूर्णांक			rval;
	काष्ठा uioc_समयout	समयout = अणु पूर्ण;

	kioc->status	= -ENODATA;
	rval		= adp->issue_uioc(adp->drvr_data, kioc, IOCTL_ISSUE);

	अगर (rval) वापस rval;

	/*
	 * Start the समयr
	 */
	अगर (adp->समयout > 0) अणु
		समयout.uioc = kioc;
		समयr_setup_on_stack(&समयout.समयr, lld_समयकरोut, 0);

		समयout.समयr.expires	= jअगरfies + adp->समयout * HZ;

		add_समयr(&समयout.समयr);
	पूर्ण

	/*
	 * Wait till the low level driver completes the ioctl. After this
	 * call, the ioctl either completed successfully or समयकरोut.
	 */
	रुको_event(रुको_q, (kioc->status != -ENODATA));
	अगर (समयout.समयr.function) अणु
		del_समयr_sync(&समयout.समयr);
		destroy_समयr_on_stack(&समयout.समयr);
	पूर्ण

	/*
	 * If the command had समयकरोut, we mark the controller offline
	 * beक्रमe वापसing
	 */
	अगर (kioc->समयकरोut) अणु
		adp->quiescent = 0;
	पूर्ण

	वापस kioc->status;
पूर्ण


/**
 * ioctl_करोne - callback from the low level driver
 * @kioc	: completed ioctl packet
 */
अटल व्योम
ioctl_करोne(uioc_t *kioc)
अणु
	uपूर्णांक32_t	adapno;
	पूर्णांक		iterator;
	mraid_mmadp_t*	adapter;

	/*
	 * When the kioc वापसs from driver, make sure it still करोesn't
	 * have ENODATA in status. Otherwise, driver will hang on रुको_event
	 * क्रमever
	 */
	अगर (kioc->status == -ENODATA) अणु
		con_log(CL_ANN, (KERN_WARNING
			"megaraid cmm: lld didn't change status!\n"));

		kioc->status = -EINVAL;
	पूर्ण

	/*
	 * Check अगर this kioc was समयकरोut beक्रमe. If so, nobody is रुकोing
	 * on this kioc. We करोn't have to wake up anybody. Instead, we just
	 * have to मुक्त the kioc
	 */
	अगर (kioc->समयकरोut) अणु
		iterator	= 0;
		adapter		= शून्य;
		adapno		= kioc->adapno;

		con_log(CL_ANN, ( KERN_WARNING "megaraid cmm: completed "
					"ioctl that was timedout before\n"));

		list_क्रम_each_entry(adapter, &adapters_list_g, list) अणु
			अगर (iterator++ == adapno) अवरोध;
		पूर्ण

		kioc->समयकरोut = 0;

		अगर (adapter) अणु
			mraid_mm_dealloc_kioc( adapter, kioc );
		पूर्ण
	पूर्ण
	अन्यथा अणु
		wake_up(&रुको_q);
	पूर्ण
पूर्ण


/**
 * lld_समयकरोut	- callback from the expired समयr
 * @t		: समयr that समयd out
 */
अटल व्योम
lld_समयकरोut(काष्ठा समयr_list *t)
अणु
	काष्ठा uioc_समयout *समयout = from_समयr(समयout, t, समयr);
	uioc_t *kioc	= समयout->uioc;

	kioc->status 	= -ETIME;
	kioc->समयकरोut	= 1;

	con_log(CL_ANN, (KERN_WARNING "megaraid cmm: ioctl timed out\n"));

	wake_up(&रुको_q);
पूर्ण


/**
 * kioc_to_mimd	- Converter from new back to old क्रमmat
 * @kioc	: Kernel space IOCTL packet (successfully issued)
 * @mimd	: User space MIMD packet
 */
अटल पूर्णांक
kioc_to_mimd(uioc_t *kioc, mimd_t __user *mimd)
अणु
	mimd_t			kmimd;
	uपूर्णांक8_t			opcode;
	uपूर्णांक8_t			subopcode;

	mbox64_t		*mbox64;
	mraid_passthru_t	__user *upthru32;
	mraid_passthru_t	*kpthru32;
	mcontroller_t		cinfo;
	mraid_hba_info_t	*hinfo;


	अगर (copy_from_user(&kmimd, mimd, माप(mimd_t)))
		वापस (-EFAULT);

	opcode		= kmimd.ui.fcs.opcode;
	subopcode	= kmimd.ui.fcs.subopcode;

	अगर (opcode == 0x82) अणु
		चयन (subopcode) अणु

		हाल MEGAIOC_QADAPINFO:

			hinfo = (mraid_hba_info_t *)(अचिन्हित दीर्घ)
					kioc->buf_vaddr;

			hinfo_to_cinfo(hinfo, &cinfo);

			अगर (copy_to_user(kmimd.data, &cinfo, माप(cinfo)))
				वापस (-EFAULT);

			वापस 0;

		शेष:
			वापस (-EINVAL);
		पूर्ण

		वापस 0;
	पूर्ण

	mbox64 = (mbox64_t *)(अचिन्हित दीर्घ)kioc->cmdbuf;

	अगर (kioc->user_pthru) अणु

		upthru32 = kioc->user_pthru;
		kpthru32 = kioc->pthru32;

		अगर (copy_to_user(&upthru32->scsistatus,
					&kpthru32->scsistatus,
					माप(uपूर्णांक8_t))) अणु
			वापस (-EFAULT);
		पूर्ण
	पूर्ण

	अगर (kioc->user_data) अणु
		अगर (copy_to_user(kioc->user_data, kioc->buf_vaddr,
					kioc->user_data_len)) अणु
			वापस (-EFAULT);
		पूर्ण
	पूर्ण

	अगर (copy_to_user(&mimd->mbox[17],
			&mbox64->mbox32.status, माप(uपूर्णांक8_t))) अणु
		वापस (-EFAULT);
	पूर्ण

	वापस 0;
पूर्ण


/**
 * hinfo_to_cinfo - Convert new क्रमmat hba info पूर्णांकo old क्रमmat
 * @hinfo	: New क्रमmat, more comprehensive adapter info
 * @cinfo	: Old क्रमmat adapter info to support mimd_t apps
 */
अटल व्योम
hinfo_to_cinfo(mraid_hba_info_t *hinfo, mcontroller_t *cinfo)
अणु
	अगर (!hinfo || !cinfo)
		वापस;

	cinfo->base		= hinfo->baseport;
	cinfo->irq		= hinfo->irq;
	cinfo->numldrv		= hinfo->num_ldrv;
	cinfo->pcibus		= hinfo->pci_bus;
	cinfo->pcidev		= hinfo->pci_slot;
	cinfo->pcअगरun		= PCI_FUNC(hinfo->pci_dev_fn);
	cinfo->pciid		= hinfo->pci_device_id;
	cinfo->pcivenकरोr	= hinfo->pci_venकरोr_id;
	cinfo->pcislot		= hinfo->pci_slot;
	cinfo->uid		= hinfo->unique_id;
पूर्ण


/**
 * mraid_mm_रेजिस्टर_adp - Registration routine क्रम low level drivers
 * @lld_adp	: Adapter object
 */
पूर्णांक
mraid_mm_रेजिस्टर_adp(mraid_mmadp_t *lld_adp)
अणु
	mraid_mmadp_t	*adapter;
	mbox64_t	*mbox_list;
	uioc_t		*kioc;
	uपूर्णांक32_t	rval;
	पूर्णांक		i;


	अगर (lld_adp->drvr_type != DRVRTYPE_MBOX)
		वापस (-EINVAL);

	adapter = kzalloc(माप(mraid_mmadp_t), GFP_KERNEL);

	अगर (!adapter)
		वापस -ENOMEM;


	adapter->unique_id	= lld_adp->unique_id;
	adapter->drvr_type	= lld_adp->drvr_type;
	adapter->drvr_data	= lld_adp->drvr_data;
	adapter->pdev		= lld_adp->pdev;
	adapter->issue_uioc	= lld_adp->issue_uioc;
	adapter->समयout	= lld_adp->समयout;
	adapter->max_kioc	= lld_adp->max_kioc;
	adapter->quiescent	= 1;

	/*
	 * Allocate single blocks of memory क्रम all required kiocs,
	 * mailboxes and passthru काष्ठाures.
	 */
	adapter->kioc_list	= kदो_स्मृति_array(lld_adp->max_kioc,
						  माप(uioc_t),
						  GFP_KERNEL);
	adapter->mbox_list	= kदो_स्मृति_array(lld_adp->max_kioc,
						  माप(mbox64_t),
						  GFP_KERNEL);
	adapter->pthru_dma_pool = dma_pool_create("megaraid mm pthru pool",
						&adapter->pdev->dev,
						माप(mraid_passthru_t),
						16, 0);

	अगर (!adapter->kioc_list || !adapter->mbox_list ||
			!adapter->pthru_dma_pool) अणु

		con_log(CL_ANN, (KERN_WARNING
			"megaraid cmm: out of memory, %s %d\n", __func__,
			__LINE__));

		rval = (-ENOMEM);

		जाओ meदो_स्मृति_error;
	पूर्ण

	/*
	 * Slice kioc_list and make a kioc_pool with the inभागidiual kiocs
	 */
	INIT_LIST_HEAD(&adapter->kioc_pool);
	spin_lock_init(&adapter->kioc_pool_lock);
	sema_init(&adapter->kioc_semaphore, lld_adp->max_kioc);

	mbox_list	= (mbox64_t *)adapter->mbox_list;

	क्रम (i = 0; i < lld_adp->max_kioc; i++) अणु

		kioc		= adapter->kioc_list + i;
		kioc->cmdbuf	= (uपूर्णांक64_t)(अचिन्हित दीर्घ)(mbox_list + i);
		kioc->pthru32	= dma_pool_alloc(adapter->pthru_dma_pool,
						GFP_KERNEL, &kioc->pthru32_h);

		अगर (!kioc->pthru32) अणु

			con_log(CL_ANN, (KERN_WARNING
				"megaraid cmm: out of memory, %s %d\n",
					__func__, __LINE__));

			rval = (-ENOMEM);

			जाओ pthru_dma_pool_error;
		पूर्ण

		list_add_tail(&kioc->list, &adapter->kioc_pool);
	पूर्ण

	// Setup the dma pools क्रम data buffers
	अगर ((rval = mraid_mm_setup_dma_pools(adapter)) != 0) अणु
		जाओ dma_pool_error;
	पूर्ण

	list_add_tail(&adapter->list, &adapters_list_g);

	adapters_count_g++;

	वापस 0;

dma_pool_error:
	/* Do nothing */

pthru_dma_pool_error:

	क्रम (i = 0; i < lld_adp->max_kioc; i++) अणु
		kioc = adapter->kioc_list + i;
		अगर (kioc->pthru32) अणु
			dma_pool_मुक्त(adapter->pthru_dma_pool, kioc->pthru32,
				kioc->pthru32_h);
		पूर्ण
	पूर्ण

meदो_स्मृति_error:

	kमुक्त(adapter->kioc_list);
	kमुक्त(adapter->mbox_list);

	dma_pool_destroy(adapter->pthru_dma_pool);

	kमुक्त(adapter);

	वापस rval;
पूर्ण


/**
 * mraid_mm_adapter_app_handle - वापस the application handle क्रम this adapter
 * @unique_id	: adapter unique identअगरier
 *
 * For the given driver data, locate the adapter in our global list and
 * वापस the corresponding handle, which is also used by applications to
 * uniquely identअगरy an adapter.
 *
 * Return adapter handle अगर found in the list.
 * Return 0 अगर adapter could not be located, should never happen though.
 */
uपूर्णांक32_t
mraid_mm_adapter_app_handle(uपूर्णांक32_t unique_id)
अणु
	mraid_mmadp_t	*adapter;
	mraid_mmadp_t	*पंचांगp;
	पूर्णांक		index = 0;

	list_क्रम_each_entry_safe(adapter, पंचांगp, &adapters_list_g, list) अणु

		अगर (adapter->unique_id == unique_id) अणु

			वापस MKADAP(index);
		पूर्ण

		index++;
	पूर्ण

	वापस 0;
पूर्ण


/**
 * mraid_mm_setup_dma_pools - Set up dma buffer pools per adapter
 * @adp	: Adapter softstate
 *
 * We मुख्यtain a pool of dma buffers per each adapter. Each pool has one
 * buffer. E.g, we may have 5 dma pools - one each क्रम 4k, 8k ... 64k buffers.
 * We have just one 4k buffer in 4k pool, one 8k buffer in 8k pool etc. We
 * करोnt' want to waste too much memory by allocating more buffers per each
 * pool.
 */
अटल पूर्णांक
mraid_mm_setup_dma_pools(mraid_mmadp_t *adp)
अणु
	mm_dmapool_t	*pool;
	पूर्णांक		bufsize;
	पूर्णांक		i;

	/*
	 * Create MAX_DMA_POOLS number of pools
	 */
	bufsize = MRAID_MM_INIT_BUFF_SIZE;

	क्रम (i = 0; i < MAX_DMA_POOLS; i++)अणु

		pool = &adp->dma_pool_list[i];

		pool->buf_size = bufsize;
		spin_lock_init(&pool->lock);

		pool->handle = dma_pool_create("megaraid mm data buffer",
						&adp->pdev->dev, bufsize,
						16, 0);

		अगर (!pool->handle) अणु
			जाओ dma_pool_setup_error;
		पूर्ण

		pool->vaddr = dma_pool_alloc(pool->handle, GFP_KERNEL,
							&pool->paddr);

		अगर (!pool->vaddr)
			जाओ dma_pool_setup_error;

		bufsize = bufsize * 2;
	पूर्ण

	वापस 0;

dma_pool_setup_error:

	mraid_mm_tearकरोwn_dma_pools(adp);
	वापस (-ENOMEM);
पूर्ण


/**
 * mraid_mm_unरेजिस्टर_adp - Unरेजिस्टर routine क्रम low level drivers
 * @unique_id	: UID of the adpater
 *
 * Assumes no outstanding ioctls to llds.
 */
पूर्णांक
mraid_mm_unरेजिस्टर_adp(uपूर्णांक32_t unique_id)
अणु
	mraid_mmadp_t	*adapter;
	mraid_mmadp_t	*पंचांगp;

	list_क्रम_each_entry_safe(adapter, पंचांगp, &adapters_list_g, list) अणु


		अगर (adapter->unique_id == unique_id) अणु

			adapters_count_g--;

			list_del_init(&adapter->list);

			mraid_mm_मुक्त_adp_resources(adapter);

			kमुक्त(adapter);

			con_log(CL_ANN, (
				"megaraid cmm: Unregistered one adapter:%#x\n",
				unique_id));

			वापस 0;
		पूर्ण
	पूर्ण

	वापस (-ENODEV);
पूर्ण

/**
 * mraid_mm_मुक्त_adp_resources - Free adapter softstate
 * @adp	: Adapter softstate
 */
अटल व्योम
mraid_mm_मुक्त_adp_resources(mraid_mmadp_t *adp)
अणु
	uioc_t	*kioc;
	पूर्णांक	i;

	mraid_mm_tearकरोwn_dma_pools(adp);

	क्रम (i = 0; i < adp->max_kioc; i++) अणु

		kioc = adp->kioc_list + i;

		dma_pool_मुक्त(adp->pthru_dma_pool, kioc->pthru32,
				kioc->pthru32_h);
	पूर्ण

	kमुक्त(adp->kioc_list);
	kमुक्त(adp->mbox_list);

	dma_pool_destroy(adp->pthru_dma_pool);


	वापस;
पूर्ण


/**
 * mraid_mm_tearकरोwn_dma_pools - Free all per adapter dma buffers
 * @adp	: Adapter softstate
 */
अटल व्योम
mraid_mm_tearकरोwn_dma_pools(mraid_mmadp_t *adp)
अणु
	पूर्णांक		i;
	mm_dmapool_t	*pool;

	क्रम (i = 0; i < MAX_DMA_POOLS; i++) अणु

		pool = &adp->dma_pool_list[i];

		अगर (pool->handle) अणु

			अगर (pool->vaddr)
				dma_pool_मुक्त(pool->handle, pool->vaddr,
							pool->paddr);

			dma_pool_destroy(pool->handle);
			pool->handle = शून्य;
		पूर्ण
	पूर्ण

	वापस;
पूर्ण

/**
 * mraid_mm_init	- Module entry poपूर्णांक
 */
अटल पूर्णांक __init
mraid_mm_init(व्योम)
अणु
	पूर्णांक err;

	// Announce the driver version
	con_log(CL_ANN, (KERN_INFO "megaraid cmm: %s %s\n",
		LSI_COMMON_MOD_VERSION, LSI_COMMON_MOD_EXT_VERSION));

	err = misc_रेजिस्टर(&megaraid_mm_dev);
	अगर (err < 0) अणु
		con_log(CL_ANN, ("megaraid cmm: cannot register misc device\n"));
		वापस err;
	पूर्ण

	init_रुकोqueue_head(&रुको_q);

	INIT_LIST_HEAD(&adapters_list_g);

	वापस 0;
पूर्ण


/**
 * mraid_mm_निकास	- Module निकास poपूर्णांक
 */
अटल व्योम __निकास
mraid_mm_निकास(व्योम)
अणु
	con_log(CL_DLEVEL1 , ("exiting common mod\n"));

	misc_deरेजिस्टर(&megaraid_mm_dev);
पूर्ण

module_init(mraid_mm_init);
module_निकास(mraid_mm_निकास);

/* vi: set ts=8 sw=8 tw=78: */
