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
 *  commctrl.c
 *
 * Abstract: Contains all routines क्रम control of the AFA comm layer
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/types.h>
#समावेश <linux/pci.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/slab.h>
#समावेश <linux/completion.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/compat.h>
#समावेश <linux/delay.h> /* ssleep prototype */
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/uaccess.h>
#समावेश <scsi/scsi_host.h>

#समावेश "aacraid.h"

# define AAC_DEBUG_PREAMBLE	KERN_INFO
# define AAC_DEBUG_POSTAMBLE
/**
 *	ioctl_send_fib	-	send a FIB from userspace
 *	@dev:	adapter is being processed
 *	@arg:	arguments to the ioctl call
 *
 *	This routine sends a fib to the adapter on behalf of a user level
 *	program.
 */
अटल पूर्णांक ioctl_send_fib(काष्ठा aac_dev * dev, व्योम __user *arg)
अणु
	काष्ठा hw_fib * kfib;
	काष्ठा fib *fibptr;
	काष्ठा hw_fib * hw_fib = (काष्ठा hw_fib *)0;
	dma_addr_t hw_fib_pa = (dma_addr_t)0LL;
	अचिन्हित पूर्णांक size, osize;
	पूर्णांक retval;

	अगर (dev->in_reset) अणु
		वापस -EBUSY;
	पूर्ण
	fibptr = aac_fib_alloc(dev);
	अगर(fibptr == शून्य) अणु
		वापस -ENOMEM;
	पूर्ण

	kfib = fibptr->hw_fib_va;
	/*
	 *	First copy in the header so that we can check the size field.
	 */
	अगर (copy_from_user((व्योम *)kfib, arg, माप(काष्ठा aac_fibhdr))) अणु
		aac_fib_मुक्त(fibptr);
		वापस -EFAULT;
	पूर्ण
	/*
	 *	Since we copy based on the fib header size, make sure that we
	 *	will not overrun the buffer when we copy the memory. Return
	 *	an error अगर we would.
	 */
	osize = size = le16_to_cpu(kfib->header.Size) +
		माप(काष्ठा aac_fibhdr);
	अगर (size < le16_to_cpu(kfib->header.SenderSize))
		size = le16_to_cpu(kfib->header.SenderSize);
	अगर (size > dev->max_fib_size) अणु
		dma_addr_t daddr;

		अगर (size > 2048) अणु
			retval = -EINVAL;
			जाओ cleanup;
		पूर्ण

		kfib = dma_alloc_coherent(&dev->pdev->dev, size, &daddr,
					  GFP_KERNEL);
		अगर (!kfib) अणु
			retval = -ENOMEM;
			जाओ cleanup;
		पूर्ण

		/* Highjack the hw_fib */
		hw_fib = fibptr->hw_fib_va;
		hw_fib_pa = fibptr->hw_fib_pa;
		fibptr->hw_fib_va = kfib;
		fibptr->hw_fib_pa = daddr;
		स_रखो(((अक्षर *)kfib) + dev->max_fib_size, 0, size - dev->max_fib_size);
		स_नकल(kfib, hw_fib, dev->max_fib_size);
	पूर्ण

	अगर (copy_from_user(kfib, arg, size)) अणु
		retval = -EFAULT;
		जाओ cleanup;
	पूर्ण

	/* Sanity check the second copy */
	अगर ((osize != le16_to_cpu(kfib->header.Size) +
		माप(काष्ठा aac_fibhdr))
		|| (size < le16_to_cpu(kfib->header.SenderSize))) अणु
		retval = -EINVAL;
		जाओ cleanup;
	पूर्ण

	अगर (kfib->header.Command == cpu_to_le16(TakeABreakPt)) अणु
		aac_adapter_पूर्णांकerrupt(dev);
		/*
		 * Since we didn't really send a fib, zero out the state to allow
		 * cleanup code not to निश्चित.
		 */
		kfib->header.XferState = 0;
	पूर्ण अन्यथा अणु
		retval = aac_fib_send(le16_to_cpu(kfib->header.Command), fibptr,
				le16_to_cpu(kfib->header.Size) , FsaNormal,
				1, 1, शून्य, शून्य);
		अगर (retval) अणु
			जाओ cleanup;
		पूर्ण
		अगर (aac_fib_complete(fibptr) != 0) अणु
			retval = -EINVAL;
			जाओ cleanup;
		पूर्ण
	पूर्ण
	/*
	 *	Make sure that the size वापसed by the adapter (which includes
	 *	the header) is less than or equal to the size of a fib, so we
	 *	करोn't corrupt application data. Then copy that size to the user
	 *	buffer. (Don't try to add the header inक्रमmation again, since it
	 *	was alपढ़ोy included by the adapter.)
	 */

	retval = 0;
	अगर (copy_to_user(arg, (व्योम *)kfib, size))
		retval = -EFAULT;
cleanup:
	अगर (hw_fib) अणु
		dma_मुक्त_coherent(&dev->pdev->dev, size, kfib,
				  fibptr->hw_fib_pa);
		fibptr->hw_fib_pa = hw_fib_pa;
		fibptr->hw_fib_va = hw_fib;
	पूर्ण
	अगर (retval != -ERESTARTSYS)
		aac_fib_मुक्त(fibptr);
	वापस retval;
पूर्ण

/**
 *	खोलो_getadapter_fib	-	Get the next fib
 *	@dev:	adapter is being processed
 *	@arg:	arguments to the खोलो call
 *
 *	This routine will get the next Fib, अगर available, from the AdapterFibContext
 *	passed in from the user.
 */
अटल पूर्णांक खोलो_getadapter_fib(काष्ठा aac_dev * dev, व्योम __user *arg)
अणु
	काष्ठा aac_fib_context * fibctx;
	पूर्णांक status;

	fibctx = kदो_स्मृति(माप(काष्ठा aac_fib_context), GFP_KERNEL);
	अगर (fibctx == शून्य) अणु
		status = -ENOMEM;
	पूर्ण अन्यथा अणु
		अचिन्हित दीर्घ flags;
		काष्ठा list_head * entry;
		काष्ठा aac_fib_context * context;

		fibctx->type = FSAFS_NTC_GET_ADAPTER_FIB_CONTEXT;
		fibctx->size = माप(काष्ठा aac_fib_context);
		/*
		 *	Yes yes, I know this could be an index, but we have a
		 * better guarantee of uniqueness क्रम the locked loop below.
		 * Without the aid of a persistent history, this also helps
		 * reduce the chance that the opaque context would be reused.
		 */
		fibctx->unique = (u32)((uदीर्घ)fibctx & 0xFFFFFFFF);
		/*
		 *	Initialize the mutex used to रुको क्रम the next AIF.
		 */
		init_completion(&fibctx->completion);
		fibctx->रुको = 0;
		/*
		 *	Initialize the fibs and set the count of fibs on
		 *	the list to 0.
		 */
		fibctx->count = 0;
		INIT_LIST_HEAD(&fibctx->fib_list);
		fibctx->jअगरfies = jअगरfies/HZ;
		/*
		 *	Now add this context onto the adapter's
		 *	AdapterFibContext list.
		 */
		spin_lock_irqsave(&dev->fib_lock, flags);
		/* Ensure that we have a unique identअगरier */
		entry = dev->fib_list.next;
		जबतक (entry != &dev->fib_list) अणु
			context = list_entry(entry, काष्ठा aac_fib_context, next);
			अगर (context->unique == fibctx->unique) अणु
				/* Not unique (32 bits) */
				fibctx->unique++;
				entry = dev->fib_list.next;
			पूर्ण अन्यथा अणु
				entry = entry->next;
			पूर्ण
		पूर्ण
		list_add_tail(&fibctx->next, &dev->fib_list);
		spin_unlock_irqrestore(&dev->fib_lock, flags);
		अगर (copy_to_user(arg, &fibctx->unique,
						माप(fibctx->unique))) अणु
			status = -EFAULT;
		पूर्ण अन्यथा अणु
			status = 0;
		पूर्ण
	पूर्ण
	वापस status;
पूर्ण

काष्ठा compat_fib_ioctl अणु
	u32	fibctx;
	s32	रुको;
	compat_uptr_t fib;
पूर्ण;

/**
 *	next_getadapter_fib	-	get the next fib
 *	@dev: adapter to use
 *	@arg: ioctl argument
 *
 *	This routine will get the next Fib, अगर available, from the AdapterFibContext
 *	passed in from the user.
 */
अटल पूर्णांक next_getadapter_fib(काष्ठा aac_dev * dev, व्योम __user *arg)
अणु
	काष्ठा fib_ioctl f;
	काष्ठा fib *fib;
	काष्ठा aac_fib_context *fibctx;
	पूर्णांक status;
	काष्ठा list_head * entry;
	अचिन्हित दीर्घ flags;

	अगर (in_compat_syscall()) अणु
		काष्ठा compat_fib_ioctl cf;

		अगर (copy_from_user(&cf, arg, माप(काष्ठा compat_fib_ioctl)))
			वापस -EFAULT;

		f.fibctx = cf.fibctx;
		f.रुको = cf.रुको;
		f.fib = compat_ptr(cf.fib);
	पूर्ण अन्यथा अणु
		अगर (copy_from_user(&f, arg, माप(काष्ठा fib_ioctl)))
			वापस -EFAULT;
	पूर्ण
	/*
	 *	Verअगरy that the HANDLE passed in was a valid AdapterFibContext
	 *
	 *	Search the list of AdapterFibContext addresses on the adapter
	 *	to be sure this is a valid address
	 */
	spin_lock_irqsave(&dev->fib_lock, flags);
	entry = dev->fib_list.next;
	fibctx = शून्य;

	जबतक (entry != &dev->fib_list) अणु
		fibctx = list_entry(entry, काष्ठा aac_fib_context, next);
		/*
		 *	Extract the AdapterFibContext from the Input parameters.
		 */
		अगर (fibctx->unique == f.fibctx) अणु /* We found a winner */
			अवरोध;
		पूर्ण
		entry = entry->next;
		fibctx = शून्य;
	पूर्ण
	अगर (!fibctx) अणु
		spin_unlock_irqrestore(&dev->fib_lock, flags);
		dprपूर्णांकk ((KERN_INFO "Fib Context not found\n"));
		वापस -EINVAL;
	पूर्ण

	अगर((fibctx->type != FSAFS_NTC_GET_ADAPTER_FIB_CONTEXT) ||
		 (fibctx->size != माप(काष्ठा aac_fib_context))) अणु
		spin_unlock_irqrestore(&dev->fib_lock, flags);
		dprपूर्णांकk ((KERN_INFO "Fib Context corrupt?\n"));
		वापस -EINVAL;
	पूर्ण
	status = 0;
	/*
	 *	If there are no fibs to send back, then either रुको or वापस
	 *	-EAGAIN
	 */
वापस_fib:
	अगर (!list_empty(&fibctx->fib_list)) अणु
		/*
		 *	Pull the next fib from the fibs
		 */
		entry = fibctx->fib_list.next;
		list_del(entry);

		fib = list_entry(entry, काष्ठा fib, fiblink);
		fibctx->count--;
		spin_unlock_irqrestore(&dev->fib_lock, flags);
		अगर (copy_to_user(f.fib, fib->hw_fib_va, माप(काष्ठा hw_fib))) अणु
			kमुक्त(fib->hw_fib_va);
			kमुक्त(fib);
			वापस -EFAULT;
		पूर्ण
		/*
		 *	Free the space occupied by this copy of the fib.
		 */
		kमुक्त(fib->hw_fib_va);
		kमुक्त(fib);
		status = 0;
	पूर्ण अन्यथा अणु
		spin_unlock_irqrestore(&dev->fib_lock, flags);
		/* If someone समाप्तed the AIF aacraid thपढ़ो, restart it */
		status = !dev->aअगर_thपढ़ो;
		अगर (status && !dev->in_reset && dev->queues && dev->fsa_dev) अणु
			/* Be paranoid, be very paranoid! */
			kthपढ़ो_stop(dev->thपढ़ो);
			ssleep(1);
			dev->aअगर_thपढ़ो = 0;
			dev->thपढ़ो = kthपढ़ो_run(aac_command_thपढ़ो, dev,
						  "%s", dev->name);
			ssleep(1);
		पूर्ण
		अगर (f.रुको) अणु
			अगर (रुको_क्रम_completion_पूर्णांकerruptible(&fibctx->completion) < 0) अणु
				status = -ERESTARTSYS;
			पूर्ण अन्यथा अणु
				/* Lock again and retry */
				spin_lock_irqsave(&dev->fib_lock, flags);
				जाओ वापस_fib;
			पूर्ण
		पूर्ण अन्यथा अणु
			status = -EAGAIN;
		पूर्ण
	पूर्ण
	fibctx->jअगरfies = jअगरfies/HZ;
	वापस status;
पूर्ण

पूर्णांक aac_बंद_fib_context(काष्ठा aac_dev * dev, काष्ठा aac_fib_context * fibctx)
अणु
	काष्ठा fib *fib;

	/*
	 *	First मुक्त any FIBs that have not been consumed.
	 */
	जबतक (!list_empty(&fibctx->fib_list)) अणु
		काष्ठा list_head * entry;
		/*
		 *	Pull the next fib from the fibs
		 */
		entry = fibctx->fib_list.next;
		list_del(entry);
		fib = list_entry(entry, काष्ठा fib, fiblink);
		fibctx->count--;
		/*
		 *	Free the space occupied by this copy of the fib.
		 */
		kमुक्त(fib->hw_fib_va);
		kमुक्त(fib);
	पूर्ण
	/*
	 *	Remove the Context from the AdapterFibContext List
	 */
	list_del(&fibctx->next);
	/*
	 *	Invalidate context
	 */
	fibctx->type = 0;
	/*
	 *	Free the space occupied by the Context
	 */
	kमुक्त(fibctx);
	वापस 0;
पूर्ण

/**
 *	बंद_getadapter_fib	-	बंद करोwn user fib context
 *	@dev: adapter
 *	@arg: ioctl arguments
 *
 *	This routine will बंद करोwn the fibctx passed in from the user.
 */

अटल पूर्णांक बंद_getadapter_fib(काष्ठा aac_dev * dev, व्योम __user *arg)
अणु
	काष्ठा aac_fib_context *fibctx;
	पूर्णांक status;
	अचिन्हित दीर्घ flags;
	काष्ठा list_head * entry;

	/*
	 *	Verअगरy that the HANDLE passed in was a valid AdapterFibContext
	 *
	 *	Search the list of AdapterFibContext addresses on the adapter
	 *	to be sure this is a valid address
	 */

	entry = dev->fib_list.next;
	fibctx = शून्य;

	जबतक(entry != &dev->fib_list) अणु
		fibctx = list_entry(entry, काष्ठा aac_fib_context, next);
		/*
		 *	Extract the fibctx from the input parameters
		 */
		अगर (fibctx->unique == (u32)(uपूर्णांकptr_t)arg) /* We found a winner */
			अवरोध;
		entry = entry->next;
		fibctx = शून्य;
	पूर्ण

	अगर (!fibctx)
		वापस 0; /* Alपढ़ोy gone */

	अगर((fibctx->type != FSAFS_NTC_GET_ADAPTER_FIB_CONTEXT) ||
		 (fibctx->size != माप(काष्ठा aac_fib_context)))
		वापस -EINVAL;
	spin_lock_irqsave(&dev->fib_lock, flags);
	status = aac_बंद_fib_context(dev, fibctx);
	spin_unlock_irqrestore(&dev->fib_lock, flags);
	वापस status;
पूर्ण

/**
 *	check_revision	-	बंद करोwn user fib context
 *	@dev: adapter
 *	@arg: ioctl arguments
 *
 *	This routine वापसs the driver version.
 *	Under Linux, there have been no version incompatibilities, so this is
 *	simple!
 */

अटल पूर्णांक check_revision(काष्ठा aac_dev *dev, व्योम __user *arg)
अणु
	काष्ठा revision response;
	अक्षर *driver_version = aac_driver_version;
	u32 version;

	response.compat = 1;
	version = (simple_म_से_दीर्घ(driver_version,
				&driver_version, 10) << 24) | 0x00000400;
	version += simple_म_से_दीर्घ(driver_version + 1, &driver_version, 10) << 16;
	version += simple_म_से_दीर्घ(driver_version + 1, शून्य, 10);
	response.version = cpu_to_le32(version);
#	अगरdef AAC_DRIVER_BUILD
		response.build = cpu_to_le32(AAC_DRIVER_BUILD);
#	अन्यथा
		response.build = cpu_to_le32(9999);
#	endअगर

	अगर (copy_to_user(arg, &response, माप(response)))
		वापस -EFAULT;
	वापस 0;
पूर्ण


/**
 * aac_send_raw_srb()
 *	@dev:	adapter is being processed
 *	@arg:	arguments to the send call
 */
अटल पूर्णांक aac_send_raw_srb(काष्ठा aac_dev* dev, व्योम __user * arg)
अणु
	काष्ठा fib* srbfib;
	पूर्णांक status;
	काष्ठा aac_srb *srbcmd = शून्य;
	काष्ठा aac_hba_cmd_req *hbacmd = शून्य;
	काष्ठा user_aac_srb *user_srbcmd = शून्य;
	काष्ठा user_aac_srb __user *user_srb = arg;
	काष्ठा aac_srb_reply __user *user_reply;
	u32 chn;
	u32 fibsize = 0;
	u32 flags = 0;
	s32 rcode = 0;
	u32 data_dir;
	व्योम __user *sg_user[HBA_MAX_SG_EMBEDDED];
	व्योम *sg_list[HBA_MAX_SG_EMBEDDED];
	u32 sg_count[HBA_MAX_SG_EMBEDDED];
	u32 sg_indx = 0;
	u32 byte_count = 0;
	u32 actual_fibsize64, actual_fibsize = 0;
	पूर्णांक i;
	पूर्णांक is_native_device;
	u64 address;


	अगर (dev->in_reset) अणु
		dprपूर्णांकk((KERN_DEBUG"aacraid: send raw srb -EBUSY\n"));
		वापस -EBUSY;
	पूर्ण
	अगर (!capable(CAP_SYS_ADMIN))अणु
		dprपूर्णांकk((KERN_DEBUG"aacraid: No permission to send raw srb\n"));
		वापस -EPERM;
	पूर्ण
	/*
	 *	Allocate and initialize a Fib then setup a SRB command
	 */
	अगर (!(srbfib = aac_fib_alloc(dev))) अणु
		वापस -ENOMEM;
	पूर्ण

	स_रखो(sg_list, 0, माप(sg_list)); /* cleanup may take issue */
	अगर(copy_from_user(&fibsize, &user_srb->count,माप(u32)))अणु
		dprपूर्णांकk((KERN_DEBUG"aacraid: Could not copy data size from user\n"));
		rcode = -EFAULT;
		जाओ cleanup;
	पूर्ण

	अगर ((fibsize < (माप(काष्ठा user_aac_srb) - माप(काष्ठा user_sgentry))) ||
	    (fibsize > (dev->max_fib_size - माप(काष्ठा aac_fibhdr)))) अणु
		rcode = -EINVAL;
		जाओ cleanup;
	पूर्ण

	user_srbcmd = memdup_user(user_srb, fibsize);
	अगर (IS_ERR(user_srbcmd)) अणु
		rcode = PTR_ERR(user_srbcmd);
		user_srbcmd = शून्य;
		जाओ cleanup;
	पूर्ण

	flags = user_srbcmd->flags; /* from user in cpu order */
	चयन (flags & (SRB_DataIn | SRB_DataOut)) अणु
	हाल SRB_DataOut:
		data_dir = DMA_TO_DEVICE;
		अवरोध;
	हाल (SRB_DataIn | SRB_DataOut):
		data_dir = DMA_BIसूचीECTIONAL;
		अवरोध;
	हाल SRB_DataIn:
		data_dir = DMA_FROM_DEVICE;
		अवरोध;
	शेष:
		data_dir = DMA_NONE;
	पूर्ण
	अगर (user_srbcmd->sg.count > ARRAY_SIZE(sg_list)) अणु
		dprपूर्णांकk((KERN_DEBUG"aacraid: too many sg entries %d\n",
			user_srbcmd->sg.count));
		rcode = -EINVAL;
		जाओ cleanup;
	पूर्ण
	अगर ((data_dir == DMA_NONE) && user_srbcmd->sg.count) अणु
		dprपूर्णांकk((KERN_DEBUG"aacraid:SG with no direction specified\n"));
		rcode = -EINVAL;
		जाओ cleanup;
	पूर्ण
	actual_fibsize = माप(काष्ठा aac_srb) - माप(काष्ठा sgentry) +
		((user_srbcmd->sg.count & 0xff) * माप(काष्ठा sgentry));
	actual_fibsize64 = actual_fibsize + (user_srbcmd->sg.count & 0xff) *
	  (माप(काष्ठा sgentry64) - माप(काष्ठा sgentry));
	/* User made a mistake - should not जारी */
	अगर ((actual_fibsize != fibsize) && (actual_fibsize64 != fibsize)) अणु
		dprपूर्णांकk((KERN_DEBUG"aacraid: Bad Size specified in "
		  "Raw SRB command calculated fibsize=%lu;%lu "
		  "user_srbcmd->sg.count=%d aac_srb=%lu sgentry=%lu;%lu "
		  "issued fibsize=%d\n",
		  actual_fibsize, actual_fibsize64, user_srbcmd->sg.count,
		  माप(काष्ठा aac_srb), माप(काष्ठा sgentry),
		  माप(काष्ठा sgentry64), fibsize));
		rcode = -EINVAL;
		जाओ cleanup;
	पूर्ण

	chn = user_srbcmd->channel;
	अगर (chn < AAC_MAX_BUSES && user_srbcmd->id < AAC_MAX_TARGETS &&
		dev->hba_map[chn][user_srbcmd->id].devtype ==
		AAC_DEVTYPE_NATIVE_RAW) अणु
		is_native_device = 1;
		hbacmd = (काष्ठा aac_hba_cmd_req *)srbfib->hw_fib_va;
		स_रखो(hbacmd, 0, 96);	/* माप(*hbacmd) is not necessary */

		/* iu_type is a parameter of aac_hba_send */
		चयन (data_dir) अणु
		हाल DMA_TO_DEVICE:
			hbacmd->byte1 = 2;
			अवरोध;
		हाल DMA_FROM_DEVICE:
		हाल DMA_BIसूचीECTIONAL:
			hbacmd->byte1 = 1;
			अवरोध;
		हाल DMA_NONE:
		शेष:
			अवरोध;
		पूर्ण
		hbacmd->lun[1] = cpu_to_le32(user_srbcmd->lun);
		hbacmd->it_nexus = dev->hba_map[chn][user_srbcmd->id].rmw_nexus;

		/*
		 * we fill in reply_qid later in aac_src_deliver_message
		 * we fill in iu_type, request_id later in aac_hba_send
		 * we fill in emb_data_desc_count, data_length later
		 * in sg list build
		 */

		स_नकल(hbacmd->cdb, user_srbcmd->cdb, माप(hbacmd->cdb));

		address = (u64)srbfib->hw_error_pa;
		hbacmd->error_ptr_hi = cpu_to_le32((u32)(address >> 32));
		hbacmd->error_ptr_lo = cpu_to_le32((u32)(address & 0xffffffff));
		hbacmd->error_length = cpu_to_le32(FW_ERROR_BUFFER_SIZE);
		hbacmd->emb_data_desc_count =
					cpu_to_le32(user_srbcmd->sg.count);
		srbfib->hbacmd_size = 64 +
			user_srbcmd->sg.count * माप(काष्ठा aac_hba_sgl);

	पूर्ण अन्यथा अणु
		is_native_device = 0;
		aac_fib_init(srbfib);

		/* raw_srb FIB is not FastResponseCapable */
		srbfib->hw_fib_va->header.XferState &=
			~cpu_to_le32(FastResponseCapable);

		srbcmd = (काष्ठा aac_srb *) fib_data(srbfib);

		// Fix up srb क्रम endian and क्रमce some values

		srbcmd->function = cpu_to_le32(SRBF_ExecuteScsi); // Force this
		srbcmd->channel	 = cpu_to_le32(user_srbcmd->channel);
		srbcmd->id	 = cpu_to_le32(user_srbcmd->id);
		srbcmd->lun	 = cpu_to_le32(user_srbcmd->lun);
		srbcmd->समयout	 = cpu_to_le32(user_srbcmd->समयout);
		srbcmd->flags	 = cpu_to_le32(flags);
		srbcmd->retry_limit = 0; // Obsolete parameter
		srbcmd->cdb_size = cpu_to_le32(user_srbcmd->cdb_size);
		स_नकल(srbcmd->cdb, user_srbcmd->cdb, माप(srbcmd->cdb));
	पूर्ण

	byte_count = 0;
	अगर (is_native_device) अणु
		काष्ठा user_sgmap *usg32 = &user_srbcmd->sg;
		काष्ठा user_sgmap64 *usg64 =
			(काष्ठा user_sgmap64 *)&user_srbcmd->sg;

		क्रम (i = 0; i < usg32->count; i++) अणु
			व्योम *p;
			u64 addr;

			sg_count[i] = (actual_fibsize64 == fibsize) ?
				usg64->sg[i].count : usg32->sg[i].count;
			अगर (sg_count[i] >
				(dev->scsi_host_ptr->max_sectors << 9)) अणु
				pr_err("aacraid: upsg->sg[%d].count=%u>%u\n",
					i, sg_count[i],
					dev->scsi_host_ptr->max_sectors << 9);
				rcode = -EINVAL;
				जाओ cleanup;
			पूर्ण

			p = kदो_स्मृति(sg_count[i], GFP_KERNEL);
			अगर (!p) अणु
				rcode = -ENOMEM;
				जाओ cleanup;
			पूर्ण

			अगर (actual_fibsize64 == fibsize) अणु
				addr = (u64)usg64->sg[i].addr[0];
				addr += ((u64)usg64->sg[i].addr[1]) << 32;
			पूर्ण अन्यथा अणु
				addr = (u64)usg32->sg[i].addr;
			पूर्ण

			sg_user[i] = (व्योम __user *)(uपूर्णांकptr_t)addr;
			sg_list[i] = p; // save so we can clean up later
			sg_indx = i;

			अगर (flags & SRB_DataOut) अणु
				अगर (copy_from_user(p, sg_user[i],
					sg_count[i])) अणु
					rcode = -EFAULT;
					जाओ cleanup;
				पूर्ण
			पूर्ण
			addr = dma_map_single(&dev->pdev->dev, p, sg_count[i],
					      data_dir);
			hbacmd->sge[i].addr_hi = cpu_to_le32((u32)(addr>>32));
			hbacmd->sge[i].addr_lo = cpu_to_le32(
						(u32)(addr & 0xffffffff));
			hbacmd->sge[i].len = cpu_to_le32(sg_count[i]);
			hbacmd->sge[i].flags = 0;
			byte_count += sg_count[i];
		पूर्ण

		अगर (usg32->count > 0)	/* embedded sglist */
			hbacmd->sge[usg32->count-1].flags =
				cpu_to_le32(0x40000000);
		hbacmd->data_length = cpu_to_le32(byte_count);

		status = aac_hba_send(HBA_IU_TYPE_SCSI_CMD_REQ, srbfib,
					शून्य, शून्य);

	पूर्ण अन्यथा अगर (dev->adapter_info.options & AAC_OPT_SGMAP_HOST64) अणु
		काष्ठा user_sgmap64* upsg = (काष्ठा user_sgmap64*)&user_srbcmd->sg;
		काष्ठा sgmap64* psg = (काष्ठा sgmap64*)&srbcmd->sg;

		/*
		 * This should also catch अगर user used the 32 bit sgmap
		 */
		अगर (actual_fibsize64 == fibsize) अणु
			actual_fibsize = actual_fibsize64;
			क्रम (i = 0; i < upsg->count; i++) अणु
				u64 addr;
				व्योम* p;

				sg_count[i] = upsg->sg[i].count;
				अगर (sg_count[i] >
				    ((dev->adapter_info.options &
				     AAC_OPT_NEW_COMM) ?
				      (dev->scsi_host_ptr->max_sectors << 9) :
				      65536)) अणु
					rcode = -EINVAL;
					जाओ cleanup;
				पूर्ण

				p = kदो_स्मृति(sg_count[i], GFP_KERNEL);
				अगर(!p) अणु
					dprपूर्णांकk((KERN_DEBUG"aacraid: Could not allocate SG buffer - size = %d buffer number %d of %d\n",
					  sg_count[i], i, upsg->count));
					rcode = -ENOMEM;
					जाओ cleanup;
				पूर्ण
				addr = (u64)upsg->sg[i].addr[0];
				addr += ((u64)upsg->sg[i].addr[1]) << 32;
				sg_user[i] = (व्योम __user *)(uपूर्णांकptr_t)addr;
				sg_list[i] = p; // save so we can clean up later
				sg_indx = i;

				अगर (flags & SRB_DataOut) अणु
					अगर (copy_from_user(p, sg_user[i],
						sg_count[i]))अणु
						dprपूर्णांकk((KERN_DEBUG"aacraid: Could not copy sg data from user\n"));
						rcode = -EFAULT;
						जाओ cleanup;
					पूर्ण
				पूर्ण
				addr = dma_map_single(&dev->pdev->dev, p,
						      sg_count[i], data_dir);

				psg->sg[i].addr[0] = cpu_to_le32(addr & 0xffffffff);
				psg->sg[i].addr[1] = cpu_to_le32(addr>>32);
				byte_count += sg_count[i];
				psg->sg[i].count = cpu_to_le32(sg_count[i]);
			पूर्ण
		पूर्ण अन्यथा अणु
			काष्ठा user_sgmap* usg;
			usg = kmemdup(upsg,
				      actual_fibsize - माप(काष्ठा aac_srb)
				      + माप(काष्ठा sgmap), GFP_KERNEL);
			अगर (!usg) अणु
				dprपूर्णांकk((KERN_DEBUG"aacraid: Allocation error in Raw SRB command\n"));
				rcode = -ENOMEM;
				जाओ cleanup;
			पूर्ण
			actual_fibsize = actual_fibsize64;

			क्रम (i = 0; i < usg->count; i++) अणु
				u64 addr;
				व्योम* p;

				sg_count[i] = usg->sg[i].count;
				अगर (sg_count[i] >
				    ((dev->adapter_info.options &
				     AAC_OPT_NEW_COMM) ?
				      (dev->scsi_host_ptr->max_sectors << 9) :
				      65536)) अणु
					kमुक्त(usg);
					rcode = -EINVAL;
					जाओ cleanup;
				पूर्ण

				p = kदो_स्मृति(sg_count[i], GFP_KERNEL);
				अगर(!p) अणु
					dprपूर्णांकk((KERN_DEBUG "aacraid: Could not allocate SG buffer - size = %d buffer number %d of %d\n",
						sg_count[i], i, usg->count));
					kमुक्त(usg);
					rcode = -ENOMEM;
					जाओ cleanup;
				पूर्ण
				sg_user[i] = (व्योम __user *)(uपूर्णांकptr_t)usg->sg[i].addr;
				sg_list[i] = p; // save so we can clean up later
				sg_indx = i;

				अगर (flags & SRB_DataOut) अणु
					अगर (copy_from_user(p, sg_user[i],
						sg_count[i])) अणु
						kमुक्त (usg);
						dprपूर्णांकk((KERN_DEBUG"aacraid: Could not copy sg data from user\n"));
						rcode = -EFAULT;
						जाओ cleanup;
					पूर्ण
				पूर्ण
				addr = dma_map_single(&dev->pdev->dev, p,
						      sg_count[i], data_dir);

				psg->sg[i].addr[0] = cpu_to_le32(addr & 0xffffffff);
				psg->sg[i].addr[1] = cpu_to_le32(addr>>32);
				byte_count += sg_count[i];
				psg->sg[i].count = cpu_to_le32(sg_count[i]);
			पूर्ण
			kमुक्त (usg);
		पूर्ण
		srbcmd->count = cpu_to_le32(byte_count);
		अगर (user_srbcmd->sg.count)
			psg->count = cpu_to_le32(sg_indx+1);
		अन्यथा
			psg->count = 0;
		status = aac_fib_send(ScsiPortCommand64, srbfib, actual_fibsize, FsaNormal, 1, 1,शून्य,शून्य);
	पूर्ण अन्यथा अणु
		काष्ठा user_sgmap* upsg = &user_srbcmd->sg;
		काष्ठा sgmap* psg = &srbcmd->sg;

		अगर (actual_fibsize64 == fibsize) अणु
			काष्ठा user_sgmap64* usg = (काष्ठा user_sgmap64 *)upsg;
			क्रम (i = 0; i < upsg->count; i++) अणु
				uपूर्णांकptr_t addr;
				व्योम* p;

				sg_count[i] = usg->sg[i].count;
				अगर (sg_count[i] >
				    ((dev->adapter_info.options &
				     AAC_OPT_NEW_COMM) ?
				      (dev->scsi_host_ptr->max_sectors << 9) :
				      65536)) अणु
					rcode = -EINVAL;
					जाओ cleanup;
				पूर्ण
				p = kदो_स्मृति(sg_count[i], GFP_KERNEL);
				अगर (!p) अणु
					dprपूर्णांकk((KERN_DEBUG"aacraid: Could not allocate SG buffer - size = %d buffer number %d of %d\n",
						sg_count[i], i, usg->count));
					rcode = -ENOMEM;
					जाओ cleanup;
				पूर्ण
				addr = (u64)usg->sg[i].addr[0];
				addr += ((u64)usg->sg[i].addr[1]) << 32;
				sg_user[i] = (व्योम __user *)addr;
				sg_list[i] = p; // save so we can clean up later
				sg_indx = i;

				अगर (flags & SRB_DataOut) अणु
					अगर (copy_from_user(p, sg_user[i],
						sg_count[i]))अणु
						dprपूर्णांकk((KERN_DEBUG"aacraid: Could not copy sg data from user\n"));
						rcode = -EFAULT;
						जाओ cleanup;
					पूर्ण
				पूर्ण
				addr = dma_map_single(&dev->pdev->dev, p,
						      usg->sg[i].count,
						      data_dir);

				psg->sg[i].addr = cpu_to_le32(addr & 0xffffffff);
				byte_count += usg->sg[i].count;
				psg->sg[i].count = cpu_to_le32(sg_count[i]);
			पूर्ण
		पूर्ण अन्यथा अणु
			क्रम (i = 0; i < upsg->count; i++) अणु
				dma_addr_t addr;
				व्योम* p;

				sg_count[i] = upsg->sg[i].count;
				अगर (sg_count[i] >
				    ((dev->adapter_info.options &
				     AAC_OPT_NEW_COMM) ?
				      (dev->scsi_host_ptr->max_sectors << 9) :
				      65536)) अणु
					rcode = -EINVAL;
					जाओ cleanup;
				पूर्ण
				p = kदो_स्मृति(sg_count[i], GFP_KERNEL);
				अगर (!p) अणु
					dprपूर्णांकk((KERN_DEBUG"aacraid: Could not allocate SG buffer - size = %d buffer number %d of %d\n",
					  sg_count[i], i, upsg->count));
					rcode = -ENOMEM;
					जाओ cleanup;
				पूर्ण
				sg_user[i] = (व्योम __user *)(uपूर्णांकptr_t)upsg->sg[i].addr;
				sg_list[i] = p; // save so we can clean up later
				sg_indx = i;

				अगर (flags & SRB_DataOut) अणु
					अगर (copy_from_user(p, sg_user[i],
						sg_count[i])) अणु
						dprपूर्णांकk((KERN_DEBUG"aacraid: Could not copy sg data from user\n"));
						rcode = -EFAULT;
						जाओ cleanup;
					पूर्ण
				पूर्ण
				addr = dma_map_single(&dev->pdev->dev, p,
						      sg_count[i], data_dir);

				psg->sg[i].addr = cpu_to_le32(addr);
				byte_count += sg_count[i];
				psg->sg[i].count = cpu_to_le32(sg_count[i]);
			पूर्ण
		पूर्ण
		srbcmd->count = cpu_to_le32(byte_count);
		अगर (user_srbcmd->sg.count)
			psg->count = cpu_to_le32(sg_indx+1);
		अन्यथा
			psg->count = 0;
		status = aac_fib_send(ScsiPortCommand, srbfib, actual_fibsize, FsaNormal, 1, 1, शून्य, शून्य);
	पूर्ण

	अगर (status == -ERESTARTSYS) अणु
		rcode = -ERESTARTSYS;
		जाओ cleanup;
	पूर्ण

	अगर (status != 0) अणु
		dprपूर्णांकk((KERN_DEBUG"aacraid: Could not send raw srb fib to hba\n"));
		rcode = -ENXIO;
		जाओ cleanup;
	पूर्ण

	अगर (flags & SRB_DataIn) अणु
		क्रम(i = 0 ; i <= sg_indx; i++)अणु
			अगर (copy_to_user(sg_user[i], sg_list[i], sg_count[i])) अणु
				dprपूर्णांकk((KERN_DEBUG"aacraid: Could not copy sg data to user\n"));
				rcode = -EFAULT;
				जाओ cleanup;

			पूर्ण
		पूर्ण
	पूर्ण

	user_reply = arg + fibsize;
	अगर (is_native_device) अणु
		काष्ठा aac_hba_resp *err =
			&((काष्ठा aac_native_hba *)srbfib->hw_fib_va)->resp.err;
		काष्ठा aac_srb_reply reply;

		स_रखो(&reply, 0, माप(reply));
		reply.status = ST_OK;
		अगर (srbfib->flags & FIB_CONTEXT_FLAG_FASTRESP) अणु
			/* fast response */
			reply.srb_status = SRB_STATUS_SUCCESS;
			reply.scsi_status = 0;
			reply.data_xfer_length = byte_count;
			reply.sense_data_size = 0;
			स_रखो(reply.sense_data, 0, AAC_SENSE_BUFFERSIZE);
		पूर्ण अन्यथा अणु
			reply.srb_status = err->service_response;
			reply.scsi_status = err->status;
			reply.data_xfer_length = byte_count -
				le32_to_cpu(err->residual_count);
			reply.sense_data_size = err->sense_response_data_len;
			स_नकल(reply.sense_data, err->sense_response_buf,
				AAC_SENSE_BUFFERSIZE);
		पूर्ण
		अगर (copy_to_user(user_reply, &reply,
			माप(काष्ठा aac_srb_reply))) अणु
			dprपूर्णांकk((KERN_DEBUG"aacraid: Copy to user failed\n"));
			rcode = -EFAULT;
			जाओ cleanup;
		पूर्ण
	पूर्ण अन्यथा अणु
		काष्ठा aac_srb_reply *reply;

		reply = (काष्ठा aac_srb_reply *) fib_data(srbfib);
		अगर (copy_to_user(user_reply, reply,
			माप(काष्ठा aac_srb_reply))) अणु
			dprपूर्णांकk((KERN_DEBUG"aacraid: Copy to user failed\n"));
			rcode = -EFAULT;
			जाओ cleanup;
		पूर्ण
	पूर्ण

cleanup:
	kमुक्त(user_srbcmd);
	अगर (rcode != -ERESTARTSYS) अणु
		क्रम (i = 0; i <= sg_indx; i++)
			kमुक्त(sg_list[i]);
		aac_fib_complete(srbfib);
		aac_fib_मुक्त(srbfib);
	पूर्ण

	वापस rcode;
पूर्ण

काष्ठा aac_pci_info अणु
	u32 bus;
	u32 slot;
पूर्ण;


अटल पूर्णांक aac_get_pci_info(काष्ठा aac_dev* dev, व्योम __user *arg)
अणु
	काष्ठा aac_pci_info pci_info;

	pci_info.bus = dev->pdev->bus->number;
	pci_info.slot = PCI_SLOT(dev->pdev->devfn);

	अगर (copy_to_user(arg, &pci_info, माप(काष्ठा aac_pci_info))) अणु
		dprपूर्णांकk((KERN_DEBUG "aacraid: Could not copy pci info\n"));
		वापस -EFAULT;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक aac_get_hba_info(काष्ठा aac_dev *dev, व्योम __user *arg)
अणु
	काष्ठा aac_hba_info hbainfo;

	स_रखो(&hbainfo, 0, माप(hbainfo));
	hbainfo.adapter_number		= (u8) dev->id;
	hbainfo.प्रणाली_io_bus_number	= dev->pdev->bus->number;
	hbainfo.device_number		= (dev->pdev->devfn >> 3);
	hbainfo.function_number		= (dev->pdev->devfn & 0x0007);

	hbainfo.venकरोr_id		= dev->pdev->venकरोr;
	hbainfo.device_id		= dev->pdev->device;
	hbainfo.sub_venकरोr_id		= dev->pdev->subप्रणाली_venकरोr;
	hbainfo.sub_प्रणाली_id		= dev->pdev->subप्रणाली_device;

	अगर (copy_to_user(arg, &hbainfo, माप(काष्ठा aac_hba_info))) अणु
		dprपूर्णांकk((KERN_DEBUG "aacraid: Could not copy hba info\n"));
		वापस -EFAULT;
	पूर्ण

	वापस 0;
पूर्ण

काष्ठा aac_reset_iop अणु
	u8	reset_type;
पूर्ण;

अटल पूर्णांक aac_send_reset_adapter(काष्ठा aac_dev *dev, व्योम __user *arg)
अणु
	काष्ठा aac_reset_iop reset;
	पूर्णांक retval;

	अगर (copy_from_user((व्योम *)&reset, arg, माप(काष्ठा aac_reset_iop)))
		वापस -EFAULT;

	dev->adapter_shutकरोwn = 1;

	mutex_unlock(&dev->ioctl_mutex);
	retval = aac_reset_adapter(dev, 0, reset.reset_type);
	mutex_lock(&dev->ioctl_mutex);

	वापस retval;
पूर्ण

पूर्णांक aac_करो_ioctl(काष्ठा aac_dev *dev, अचिन्हित पूर्णांक cmd, व्योम __user *arg)
अणु
	पूर्णांक status;

	mutex_lock(&dev->ioctl_mutex);

	अगर (dev->adapter_shutकरोwn) अणु
		status = -EACCES;
		जाओ cleanup;
	पूर्ण

	/*
	 *	HBA माला_लो first crack
	 */

	status = aac_dev_ioctl(dev, cmd, arg);
	अगर (status != -ENOTTY)
		जाओ cleanup;

	चयन (cmd) अणु
	हाल FSACTL_MINIPORT_REV_CHECK:
		status = check_revision(dev, arg);
		अवरोध;
	हाल FSACTL_SEND_LARGE_FIB:
	हाल FSACTL_SENDFIB:
		status = ioctl_send_fib(dev, arg);
		अवरोध;
	हाल FSACTL_OPEN_GET_ADAPTER_FIB:
		status = खोलो_getadapter_fib(dev, arg);
		अवरोध;
	हाल FSACTL_GET_NEXT_ADAPTER_FIB:
		status = next_getadapter_fib(dev, arg);
		अवरोध;
	हाल FSACTL_CLOSE_GET_ADAPTER_FIB:
		status = बंद_getadapter_fib(dev, arg);
		अवरोध;
	हाल FSACTL_SEND_RAW_SRB:
		status = aac_send_raw_srb(dev,arg);
		अवरोध;
	हाल FSACTL_GET_PCI_INFO:
		status = aac_get_pci_info(dev,arg);
		अवरोध;
	हाल FSACTL_GET_HBA_INFO:
		status = aac_get_hba_info(dev, arg);
		अवरोध;
	हाल FSACTL_RESET_IOP:
		status = aac_send_reset_adapter(dev, arg);
		अवरोध;

	शेष:
		status = -ENOTTY;
		अवरोध;
	पूर्ण

cleanup:
	mutex_unlock(&dev->ioctl_mutex);

	वापस status;
पूर्ण

