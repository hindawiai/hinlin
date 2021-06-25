<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/mm.h>
#समावेश <linux/kernel.h>   /* prपूर्णांकk() */
#समावेश <linux/slab.h>     /* kदो_स्मृति() */
#समावेश <linux/fs.h>       /* everything... */
#समावेश <linux/त्रुटिसं.स>    /* error codes */
#समावेश <linux/types.h>    /* माप_प्रकार */
#समावेश <linux/cdev.h>
#समावेश <linux/uaccess.h>  /* copy_*_user */
#समावेश <linux/highस्मृति.स>
#समावेश <linux/pagemap.h>
#समावेश "kpc_dma_driver.h"
#समावेश "uapi.h"

/**********  Helper Functions  **********/
अटल अंतरभूत
अचिन्हित पूर्णांक  count_pages(अचिन्हित दीर्घ iov_base, माप_प्रकार iov_len)
अणु
	अचिन्हित दीर्घ first = (iov_base                 & PAGE_MASK) >> PAGE_SHIFT;
	अचिन्हित दीर्घ last  = ((iov_base + iov_len - 1) & PAGE_MASK) >> PAGE_SHIFT;

	वापस last - first + 1;
पूर्ण

अटल अंतरभूत
अचिन्हित पूर्णांक  count_parts_क्रम_sge(काष्ठा scatterlist *sg)
अणु
	वापस DIV_ROUND_UP(sg_dma_len(sg), 0x80000);
पूर्ण

/**********  Transfer Helpers  **********/
अटल पूर्णांक kpc_dma_transfer(काष्ठा dev_निजी_data *priv,
			    अचिन्हित दीर्घ iov_base, माप_प्रकार iov_len)
अणु
	अचिन्हित पूर्णांक i = 0;
	पूर्णांक rv = 0, nr_pages = 0;
	काष्ठा kpc_dma_device *ldev;
	काष्ठा aio_cb_data *acd;
	DECLARE_COMPLETION_ONSTACK(करोne);
	u32 desc_needed = 0;
	काष्ठा scatterlist *sg;
	u32 num_descrs_avail;
	काष्ठा kpc_dma_descriptor *desc;
	अचिन्हित पूर्णांक pcnt;
	अचिन्हित पूर्णांक p;
	u64 card_addr;
	u64 dma_addr;
	u64 user_ctl;

	ldev = priv->ldev;

	acd = kzalloc(माप(*acd), GFP_KERNEL);
	अगर (!acd) अणु
		dev_err(&priv->ldev->pldev->dev, "Couldn't kmalloc space for the aio data\n");
		वापस -ENOMEM;
	पूर्ण
	स_रखो(acd, 0x66, माप(काष्ठा aio_cb_data));

	acd->priv = priv;
	acd->ldev = priv->ldev;
	acd->cpl = &करोne;
	acd->flags = 0;
	acd->len = iov_len;
	acd->page_count = count_pages(iov_base, iov_len);

	// Allocate an array of page poपूर्णांकers
	acd->user_pages = kसुस्मृति(acd->page_count, माप(काष्ठा page *),
				  GFP_KERNEL);
	अगर (!acd->user_pages) अणु
		dev_err(&priv->ldev->pldev->dev, "Couldn't kmalloc space for the page pointers\n");
		rv = -ENOMEM;
		जाओ err_alloc_userpages;
	पूर्ण

	// Lock the user buffer pages in memory, and hold on to the page poपूर्णांकers (क्रम the sglist)
	mmap_पढ़ो_lock(current->mm);      /*  get memory map semaphore */
	rv = pin_user_pages(iov_base, acd->page_count, FOLL_TOUCH | FOLL_WRITE,
			    acd->user_pages, शून्य);
	mmap_पढ़ो_unlock(current->mm);        /*  release the semaphore */
	अगर (rv != acd->page_count) अणु
		nr_pages = rv;
		अगर (rv > 0)
			rv = -EFAULT;

		dev_err(&priv->ldev->pldev->dev, "Couldn't pin_user_pages (%d)\n", rv);
		जाओ unpin_pages;
	पूर्ण
	nr_pages = acd->page_count;

	// Allocate and setup the sg_table (scatterlist entries)
	rv = sg_alloc_table_from_pages(&acd->sgt, acd->user_pages, acd->page_count,
				       iov_base & (PAGE_SIZE - 1), iov_len, GFP_KERNEL);
	अगर (rv) अणु
		dev_err(&priv->ldev->pldev->dev, "Couldn't alloc sg_table (%d)\n", rv);
		जाओ unpin_pages;
	पूर्ण

	// Setup the DMA mapping क्रम all the sg entries
	acd->mapped_entry_count = dma_map_sg(&ldev->pldev->dev, acd->sgt.sgl, acd->sgt.nents,
					     ldev->dir);
	अगर (acd->mapped_entry_count <= 0) अणु
		dev_err(&priv->ldev->pldev->dev, "Couldn't dma_map_sg (%d)\n",
			acd->mapped_entry_count);
		जाओ मुक्त_table;
	पूर्ण

	// Calculate how many descriptors are actually needed क्रम this transfer.
	क्रम_each_sg(acd->sgt.sgl, sg, acd->mapped_entry_count, i) अणु
		desc_needed += count_parts_क्रम_sge(sg);
	पूर्ण

	lock_engine(ldev);

	// Figoure out how many descriptors are available and वापस an error अगर there aren't enough
	num_descrs_avail = count_descriptors_available(ldev);
	dev_dbg(&priv->ldev->pldev->dev,
		"    mapped_entry_count = %d    num_descrs_needed = %d    num_descrs_avail = %d\n",
		acd->mapped_entry_count, desc_needed, num_descrs_avail);

	अगर (desc_needed >= ldev->desc_pool_cnt) अणु
		dev_warn(&priv->ldev->pldev->dev,
			 "    mapped_entry_count = %d    num_descrs_needed = %d    num_descrs_avail = %d    TOO MANY to ever complete!\n",
			 acd->mapped_entry_count, desc_needed, num_descrs_avail);
		rv = -EAGAIN;
		जाओ err_descr_too_many;
	पूर्ण
	अगर (desc_needed > num_descrs_avail) अणु
		dev_warn(&priv->ldev->pldev->dev,
			 "    mapped_entry_count = %d    num_descrs_needed = %d    num_descrs_avail = %d    Too many to complete right now.\n",
			 acd->mapped_entry_count, desc_needed, num_descrs_avail);
		rv = -EMSGSIZE;
		जाओ err_descr_too_many;
	पूर्ण

	// Loop through all the sg table entries and fill out a descriptor क्रम each one.
	desc = ldev->desc_next;
	card_addr = acd->priv->card_addr;
	क्रम_each_sg(acd->sgt.sgl, sg, acd->mapped_entry_count, i) अणु
		pcnt = count_parts_क्रम_sge(sg);
		क्रम (p = 0 ; p < pcnt ; p++) अणु
			// Fill out the descriptor
			BUG_ON(!desc);
			clear_desc(desc);
			अगर (p != pcnt - 1)
				desc->DescByteCount = 0x80000;
			अन्यथा
				desc->DescByteCount = sg_dma_len(sg) - (p * 0x80000);

			desc->DescBufferByteCount = desc->DescByteCount;

			desc->DescControlFlags |= DMA_DESC_CTL_IRQONERR;
			अगर (i == 0 && p == 0)
				desc->DescControlFlags |= DMA_DESC_CTL_SOP;
			अगर (i == acd->mapped_entry_count - 1 && p == pcnt - 1)
				desc->DescControlFlags |= DMA_DESC_CTL_EOP | DMA_DESC_CTL_IRQONDONE;

			desc->DescCardAddrLS = (card_addr & 0xFFFFFFFF);
			desc->DescCardAddrMS = (card_addr >> 32) & 0xF;
			card_addr += desc->DescByteCount;

			dma_addr  = sg_dma_address(sg) + (p * 0x80000);
			desc->DescSystemAddrLS = (dma_addr & 0x00000000FFFFFFFFUL) >>  0;
			desc->DescSystemAddrMS = (dma_addr & 0xFFFFFFFF00000000UL) >> 32;

			user_ctl = acd->priv->user_ctl;
			अगर (i == acd->mapped_entry_count - 1 && p == pcnt - 1)
				user_ctl = acd->priv->user_ctl_last;

			desc->DescUserControlLS = (user_ctl & 0x00000000FFFFFFFFUL) >>  0;
			desc->DescUserControlMS = (user_ctl & 0xFFFFFFFF00000000UL) >> 32;

			अगर (i == acd->mapped_entry_count - 1 && p == pcnt - 1)
				desc->acd = acd;

			dev_dbg(&priv->ldev->pldev->dev, "  Filled descriptor %p (acd = %p)\n",
				desc, desc->acd);

			ldev->desc_next = desc->Next;
			desc = desc->Next;
		पूर्ण
	पूर्ण

	// Send the filled descriptors off to the hardware to process!
	SetEngineSWPtr(ldev, ldev->desc_next);

	unlock_engine(ldev);

	rv = रुको_क्रम_completion_पूर्णांकerruptible(&करोne);
	/*
	 * If the user पातed (rv == -ERESTARTSYS), we're no दीर्घer responsible
	 * क्रम cleaning up the acd
	 */
	अगर (rv == -ERESTARTSYS)
		acd->cpl = शून्य;
	अगर (rv == 0) अणु
		rv = acd->len;
		kमुक्त(acd);
	पूर्ण
	वापस rv;

 err_descr_too_many:
	unlock_engine(ldev);
	dma_unmap_sg(&ldev->pldev->dev, acd->sgt.sgl, acd->sgt.nents, ldev->dir);
 मुक्त_table:
	sg_मुक्त_table(&acd->sgt);

 unpin_pages:
	अगर (nr_pages > 0)
		unpin_user_pages(acd->user_pages, nr_pages);
	kमुक्त(acd->user_pages);
 err_alloc_userpages:
	kमुक्त(acd);
	dev_dbg(&priv->ldev->pldev->dev, "%s returning with error %d\n", __func__, rv);
	वापस rv;
पूर्ण

व्योम  transfer_complete_cb(काष्ठा aio_cb_data *acd, माप_प्रकार xfr_count, u32 flags)
अणु
	अचिन्हित पूर्णांक i;

	BUG_ON(!acd);
	BUG_ON(!acd->user_pages);
	BUG_ON(!acd->sgt.sgl);
	BUG_ON(!acd->ldev);
	BUG_ON(!acd->ldev->pldev);

	dma_unmap_sg(&acd->ldev->pldev->dev, acd->sgt.sgl, acd->sgt.nents, acd->ldev->dir);

	क्रम (i = 0 ; i < acd->page_count ; i++) अणु
		अगर (!PageReserved(acd->user_pages[i]))
			set_page_dirty_lock(acd->user_pages[i]);
	पूर्ण

	unpin_user_pages(acd->user_pages, acd->page_count);

	sg_मुक्त_table(&acd->sgt);

	kमुक्त(acd->user_pages);

	acd->flags = flags;

	अगर (acd->cpl) अणु
		complete(acd->cpl);
	पूर्ण अन्यथा अणु
		/*
		 * There's no completion, so we're responsible क्रम cleaning up
		 * the acd
		 */
		kमुक्त(acd);
	पूर्ण
पूर्ण

/**********  Fileops  **********/
अटल
पूर्णांक  kpc_dma_खोलो(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा dev_निजी_data *priv;
	काष्ठा kpc_dma_device *ldev = kpc_dma_lookup_device(iminor(inode));

	अगर (!ldev)
		वापस -ENODEV;

	अगर (!atomic_dec_and_test(&ldev->खोलो_count)) अणु
		atomic_inc(&ldev->खोलो_count);
		वापस -EBUSY; /* alपढ़ोy खोलो */
	पूर्ण

	priv = kzalloc(माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->ldev = ldev;
	filp->निजी_data = priv;

	वापस 0;
पूर्ण

अटल
पूर्णांक  kpc_dma_बंद(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा kpc_dma_descriptor *cur;
	काष्ठा dev_निजी_data *priv = (काष्ठा dev_निजी_data *)filp->निजी_data;
	काष्ठा kpc_dma_device *eng = priv->ldev;

	lock_engine(eng);

	stop_dma_engine(eng);

	cur = eng->desc_completed->Next;
	जबतक (cur != eng->desc_next) अणु
		dev_dbg(&eng->pldev->dev, "Aborting descriptor %p (acd = %p)\n", cur, cur->acd);
		अगर (cur->DescControlFlags & DMA_DESC_CTL_EOP) अणु
			अगर (cur->acd)
				transfer_complete_cb(cur->acd, 0, ACD_FLAG_ABORT);
		पूर्ण

		clear_desc(cur);
		eng->desc_completed = cur;

		cur = cur->Next;
	पूर्ण

	start_dma_engine(eng);

	unlock_engine(eng);

	atomic_inc(&priv->ldev->खोलो_count); /* release the device */
	kमुक्त(priv);
	वापस 0;
पूर्ण

अटल
sमाप_प्रकार  kpc_dma_पढ़ो(काष्ठा file *filp,       अक्षर __user *user_buf, माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा dev_निजी_data *priv = (काष्ठा dev_निजी_data *)filp->निजी_data;

	अगर (priv->ldev->dir != DMA_FROM_DEVICE)
		वापस -EMEDIUMTYPE;

	वापस kpc_dma_transfer(priv, (अचिन्हित दीर्घ)user_buf, count);
पूर्ण

अटल
sमाप_प्रकार  kpc_dma_ग_लिखो(काष्ठा file *filp, स्थिर अक्षर __user *user_buf, माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा dev_निजी_data *priv = (काष्ठा dev_निजी_data *)filp->निजी_data;

	अगर (priv->ldev->dir != DMA_TO_DEVICE)
		वापस -EMEDIUMTYPE;

	वापस kpc_dma_transfer(priv, (अचिन्हित दीर्घ)user_buf, count);
पूर्ण

अटल
दीर्घ  kpc_dma_ioctl(काष्ठा file *filp, अचिन्हित पूर्णांक ioctl_num, अचिन्हित दीर्घ ioctl_param)
अणु
	काष्ठा dev_निजी_data *priv = (काष्ठा dev_निजी_data *)filp->निजी_data;

	चयन (ioctl_num) अणु
	हाल KND_IOCTL_SET_CARD_ADDR:
		priv->card_addr  = ioctl_param; वापस priv->card_addr;
	हाल KND_IOCTL_SET_USER_CTL:
		priv->user_ctl   = ioctl_param; वापस priv->user_ctl;
	हाल KND_IOCTL_SET_USER_CTL_LAST:
		priv->user_ctl_last = ioctl_param; वापस priv->user_ctl_last;
	हाल KND_IOCTL_GET_USER_STS:
		वापस priv->user_sts;
	पूर्ण

	वापस -ENOTTY;
पूर्ण

स्थिर काष्ठा file_operations  kpc_dma_fops = अणु
	.owner      = THIS_MODULE,
	.खोलो           = kpc_dma_खोलो,
	.release        = kpc_dma_बंद,
	.पढ़ो           = kpc_dma_पढ़ो,
	.ग_लिखो          = kpc_dma_ग_लिखो,
	.unlocked_ioctl = kpc_dma_ioctl,
पूर्ण;

