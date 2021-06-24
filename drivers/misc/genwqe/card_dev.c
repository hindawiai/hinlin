<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * IBM Accelerator Family 'GenWQE'
 *
 * (C) Copyright IBM Corp. 2013
 *
 * Author: Frank Haverkamp <haver@linux.vnet.ibm.com>
 * Author: Joerg-Stephan Vogt <jsvogt@de.ibm.com>
 * Author: Michael Jung <mijung@gmx.net>
 * Author: Michael Ruettger <michael@ibmra.de>
 */

/*
 * Character device representation of the GenWQE device. This allows
 * user-space applications to communicate with the card.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/माला.स>
#समावेश <linux/fs.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/रुको.h>
#समावेश <linux/delay.h>
#समावेश <linux/atomic.h>

#समावेश "card_base.h"
#समावेश "card_ddcb.h"

अटल पूर्णांक genwqe_खोलो_files(काष्ठा genwqe_dev *cd)
अणु
	पूर्णांक rc;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&cd->file_lock, flags);
	rc = list_empty(&cd->file_list);
	spin_unlock_irqrestore(&cd->file_lock, flags);
	वापस !rc;
पूर्ण

अटल व्योम genwqe_add_file(काष्ठा genwqe_dev *cd, काष्ठा genwqe_file *cfile)
अणु
	अचिन्हित दीर्घ flags;

	cfile->खोलोer = get_pid(task_tgid(current));
	spin_lock_irqsave(&cd->file_lock, flags);
	list_add(&cfile->list, &cd->file_list);
	spin_unlock_irqrestore(&cd->file_lock, flags);
पूर्ण

अटल पूर्णांक genwqe_del_file(काष्ठा genwqe_dev *cd, काष्ठा genwqe_file *cfile)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&cd->file_lock, flags);
	list_del(&cfile->list);
	spin_unlock_irqrestore(&cd->file_lock, flags);
	put_pid(cfile->खोलोer);

	वापस 0;
पूर्ण

अटल व्योम genwqe_add_pin(काष्ठा genwqe_file *cfile, काष्ठा dma_mapping *m)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&cfile->pin_lock, flags);
	list_add(&m->pin_list, &cfile->pin_list);
	spin_unlock_irqrestore(&cfile->pin_lock, flags);
पूर्ण

अटल पूर्णांक genwqe_del_pin(काष्ठा genwqe_file *cfile, काष्ठा dma_mapping *m)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&cfile->pin_lock, flags);
	list_del(&m->pin_list);
	spin_unlock_irqrestore(&cfile->pin_lock, flags);

	वापस 0;
पूर्ण

/**
 * genwqe_search_pin() - Search क्रम the mapping क्रम a userspace address
 * @cfile:	Descriptor of खोलोed file
 * @u_addr:	User भव address
 * @size:	Size of buffer
 * @virt_addr:	Virtual address to be updated
 *
 * Return: Poपूर्णांकer to the corresponding mapping	शून्य अगर not found
 */
अटल काष्ठा dma_mapping *genwqe_search_pin(काष्ठा genwqe_file *cfile,
					    अचिन्हित दीर्घ u_addr,
					    अचिन्हित पूर्णांक size,
					    व्योम **virt_addr)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा dma_mapping *m;

	spin_lock_irqsave(&cfile->pin_lock, flags);

	list_क्रम_each_entry(m, &cfile->pin_list, pin_list) अणु
		अगर ((((u64)m->u_vaddr) <= (u_addr)) &&
		    (((u64)m->u_vaddr + m->size) >= (u_addr + size))) अणु

			अगर (virt_addr)
				*virt_addr = m->k_vaddr +
					(u_addr - (u64)m->u_vaddr);

			spin_unlock_irqrestore(&cfile->pin_lock, flags);
			वापस m;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&cfile->pin_lock, flags);
	वापस शून्य;
पूर्ण

अटल व्योम __genwqe_add_mapping(काष्ठा genwqe_file *cfile,
			      काष्ठा dma_mapping *dma_map)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&cfile->map_lock, flags);
	list_add(&dma_map->card_list, &cfile->map_list);
	spin_unlock_irqrestore(&cfile->map_lock, flags);
पूर्ण

अटल व्योम __genwqe_del_mapping(काष्ठा genwqe_file *cfile,
			      काष्ठा dma_mapping *dma_map)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&cfile->map_lock, flags);
	list_del(&dma_map->card_list);
	spin_unlock_irqrestore(&cfile->map_lock, flags);
पूर्ण


/**
 * __genwqe_search_mapping() - Search क्रम the mapping क्रम a userspace address
 * @cfile:	descriptor of खोलोed file
 * @u_addr:	user भव address
 * @size:	size of buffer
 * @dma_addr:	DMA address to be updated
 * @virt_addr:	Virtual address to be updated
 * Return: Poपूर्णांकer to the corresponding mapping	शून्य अगर not found
 */
अटल काष्ठा dma_mapping *__genwqe_search_mapping(काष्ठा genwqe_file *cfile,
						   अचिन्हित दीर्घ u_addr,
						   अचिन्हित पूर्णांक size,
						   dma_addr_t *dma_addr,
						   व्योम **virt_addr)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा dma_mapping *m;
	काष्ठा pci_dev *pci_dev = cfile->cd->pci_dev;

	spin_lock_irqsave(&cfile->map_lock, flags);
	list_क्रम_each_entry(m, &cfile->map_list, card_list) अणु

		अगर ((((u64)m->u_vaddr) <= (u_addr)) &&
		    (((u64)m->u_vaddr + m->size) >= (u_addr + size))) अणु

			/* match found: current is as expected and
			   addr is in range */
			अगर (dma_addr)
				*dma_addr = m->dma_addr +
					(u_addr - (u64)m->u_vaddr);

			अगर (virt_addr)
				*virt_addr = m->k_vaddr +
					(u_addr - (u64)m->u_vaddr);

			spin_unlock_irqrestore(&cfile->map_lock, flags);
			वापस m;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&cfile->map_lock, flags);

	dev_err(&pci_dev->dev,
		"[%s] Entry not found: u_addr=%lx, size=%x\n",
		__func__, u_addr, size);

	वापस शून्य;
पूर्ण

अटल व्योम genwqe_हटाओ_mappings(काष्ठा genwqe_file *cfile)
अणु
	पूर्णांक i = 0;
	काष्ठा list_head *node, *next;
	काष्ठा dma_mapping *dma_map;
	काष्ठा genwqe_dev *cd = cfile->cd;
	काष्ठा pci_dev *pci_dev = cfile->cd->pci_dev;

	list_क्रम_each_safe(node, next, &cfile->map_list) अणु
		dma_map = list_entry(node, काष्ठा dma_mapping, card_list);

		list_del_init(&dma_map->card_list);

		/*
		 * This is really a bug, because those things should
		 * have been alपढ़ोy tidied up.
		 *
		 * GENWQE_MAPPING_RAW should have been हटाओd via mmunmap().
		 * GENWQE_MAPPING_SGL_TEMP should be हटाओd by tidy up code.
		 */
		dev_err(&pci_dev->dev,
			"[%s] %d. cleanup mapping: u_vaddr=%p u_kaddr=%016lx dma_addr=%lx\n",
			__func__, i++, dma_map->u_vaddr,
			(अचिन्हित दीर्घ)dma_map->k_vaddr,
			(अचिन्हित दीर्घ)dma_map->dma_addr);

		अगर (dma_map->type == GENWQE_MAPPING_RAW) अणु
			/* we allocated this dynamically */
			__genwqe_मुक्त_consistent(cd, dma_map->size,
						dma_map->k_vaddr,
						dma_map->dma_addr);
			kमुक्त(dma_map);
		पूर्ण अन्यथा अगर (dma_map->type == GENWQE_MAPPING_SGL_TEMP) अणु
			/* we use dma_map अटलally from the request */
			genwqe_user_vunmap(cd, dma_map);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम genwqe_हटाओ_pinnings(काष्ठा genwqe_file *cfile)
अणु
	काष्ठा list_head *node, *next;
	काष्ठा dma_mapping *dma_map;
	काष्ठा genwqe_dev *cd = cfile->cd;

	list_क्रम_each_safe(node, next, &cfile->pin_list) अणु
		dma_map = list_entry(node, काष्ठा dma_mapping, pin_list);

		/*
		 * This is not a bug, because a समाप्तed processed might
		 * not call the unpin ioctl, which is supposed to मुक्त
		 * the resources.
		 *
		 * Pinnings are dymically allocated and need to be
		 * deleted.
		 */
		list_del_init(&dma_map->pin_list);
		genwqe_user_vunmap(cd, dma_map);
		kमुक्त(dma_map);
	पूर्ण
पूर्ण

/**
 * genwqe_समाप्त_fasync() - Send संकेत to all processes with खोलो GenWQE files
 * @cd: GenWQE device inक्रमmation
 * @sig: Signal to send out
 *
 * E.g. genwqe_send_संकेत(cd, SIGIO);
 */
अटल पूर्णांक genwqe_समाप्त_fasync(काष्ठा genwqe_dev *cd, पूर्णांक sig)
अणु
	अचिन्हित पूर्णांक files = 0;
	अचिन्हित दीर्घ flags;
	काष्ठा genwqe_file *cfile;

	spin_lock_irqsave(&cd->file_lock, flags);
	list_क्रम_each_entry(cfile, &cd->file_list, list) अणु
		अगर (cfile->async_queue)
			समाप्त_fasync(&cfile->async_queue, sig, POLL_HUP);
		files++;
	पूर्ण
	spin_unlock_irqrestore(&cd->file_lock, flags);
	वापस files;
पूर्ण

अटल पूर्णांक genwqe_terminate(काष्ठा genwqe_dev *cd)
अणु
	अचिन्हित पूर्णांक files = 0;
	अचिन्हित दीर्घ flags;
	काष्ठा genwqe_file *cfile;

	spin_lock_irqsave(&cd->file_lock, flags);
	list_क्रम_each_entry(cfile, &cd->file_list, list) अणु
		समाप्त_pid(cfile->खोलोer, SIGKILL, 1);
		files++;
	पूर्ण
	spin_unlock_irqrestore(&cd->file_lock, flags);
	वापस files;
पूर्ण

/**
 * genwqe_खोलो() - file खोलो
 * @inode:      file प्रणाली inक्रमmation
 * @filp:	file handle
 *
 * This function is executed whenever an application calls
 * खोलो("/dev/genwqe",..).
 *
 * Return: 0 अगर successful or <0 अगर errors
 */
अटल पूर्णांक genwqe_खोलो(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा genwqe_dev *cd;
	काष्ठा genwqe_file *cfile;

	cfile = kzalloc(माप(*cfile), GFP_KERNEL);
	अगर (cfile == शून्य)
		वापस -ENOMEM;

	cd = container_of(inode->i_cdev, काष्ठा genwqe_dev, cdev_genwqe);
	cfile->cd = cd;
	cfile->filp = filp;
	cfile->client = शून्य;

	spin_lock_init(&cfile->map_lock);  /* list of raw memory allocations */
	INIT_LIST_HEAD(&cfile->map_list);

	spin_lock_init(&cfile->pin_lock);  /* list of user pinned memory */
	INIT_LIST_HEAD(&cfile->pin_list);

	filp->निजी_data = cfile;

	genwqe_add_file(cd, cfile);
	वापस 0;
पूर्ण

/**
 * genwqe_fasync() - Setup process to receive SIGIO.
 * @fd:        file descriptor
 * @filp:      file handle
 * @mode:      file mode
 *
 * Sending a संकेत is working as following:
 *
 * अगर (cdev->async_queue)
 *         समाप्त_fasync(&cdev->async_queue, SIGIO, POLL_IN);
 *
 * Some devices also implement asynchronous notअगरication to indicate
 * when the device can be written; in this हाल, of course,
 * समाप्त_fasync must be called with a mode of POLL_OUT.
 */
अटल पूर्णांक genwqe_fasync(पूर्णांक fd, काष्ठा file *filp, पूर्णांक mode)
अणु
	काष्ठा genwqe_file *cdev = (काष्ठा genwqe_file *)filp->निजी_data;

	वापस fasync_helper(fd, filp, mode, &cdev->async_queue);
पूर्ण


/**
 * genwqe_release() - file बंद
 * @inode:      file प्रणाली inक्रमmation
 * @filp:       file handle
 *
 * This function is executed whenever an application calls 'close(fd_genwqe)'
 *
 * Return: always 0
 */
अटल पूर्णांक genwqe_release(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा genwqe_file *cfile = (काष्ठा genwqe_file *)filp->निजी_data;
	काष्ठा genwqe_dev *cd = cfile->cd;

	/* there must be no entries in these lists! */
	genwqe_हटाओ_mappings(cfile);
	genwqe_हटाओ_pinnings(cfile);

	/* हटाओ this filp from the asynchronously notअगरied filp's */
	genwqe_fasync(-1, filp, 0);

	/*
	 * For this to work we must not release cd when this cfile is
	 * not yet released, otherwise the list entry is invalid,
	 * because the list itself माला_लो reinstantiated!
	 */
	genwqe_del_file(cd, cfile);
	kमुक्त(cfile);
	वापस 0;
पूर्ण

अटल व्योम genwqe_vma_खोलो(काष्ठा vm_area_काष्ठा *vma)
अणु
	/* nothing ... */
पूर्ण

/**
 * genwqe_vma_बंद() - Called each समय when vma is unmapped
 * @vma: VMA area to बंद
 *
 * Free memory which got allocated by GenWQE mmap().
 */
अटल व्योम genwqe_vma_बंद(काष्ठा vm_area_काष्ठा *vma)
अणु
	अचिन्हित दीर्घ vsize = vma->vm_end - vma->vm_start;
	काष्ठा inode *inode = file_inode(vma->vm_file);
	काष्ठा dma_mapping *dma_map;
	काष्ठा genwqe_dev *cd = container_of(inode->i_cdev, काष्ठा genwqe_dev,
					    cdev_genwqe);
	काष्ठा pci_dev *pci_dev = cd->pci_dev;
	dma_addr_t d_addr = 0;
	काष्ठा genwqe_file *cfile = vma->vm_निजी_data;

	dma_map = __genwqe_search_mapping(cfile, vma->vm_start, vsize,
					 &d_addr, शून्य);
	अगर (dma_map == शून्य) अणु
		dev_err(&pci_dev->dev,
			"  [%s] err: mapping not found: v=%lx, p=%lx s=%lx\n",
			__func__, vma->vm_start, vma->vm_pgoff << PAGE_SHIFT,
			vsize);
		वापस;
	पूर्ण
	__genwqe_del_mapping(cfile, dma_map);
	__genwqe_मुक्त_consistent(cd, dma_map->size, dma_map->k_vaddr,
				 dma_map->dma_addr);
	kमुक्त(dma_map);
पूर्ण

अटल स्थिर काष्ठा vm_operations_काष्ठा genwqe_vma_ops = अणु
	.खोलो   = genwqe_vma_खोलो,
	.बंद  = genwqe_vma_बंद,
पूर्ण;

/**
 * genwqe_mmap() - Provide contignous buffers to userspace
 * @filp:	File poपूर्णांकer (unused)
 * @vma:	VMA area to map
 *
 * We use mmap() to allocate contignous buffers used क्रम DMA
 * transfers. After the buffer is allocated we remap it to user-space
 * and remember a reference to our dma_mapping data काष्ठाure, where
 * we store the associated DMA address and allocated size.
 *
 * When we receive a DDCB execution request with the ATS bits set to
 * plain buffer, we lookup our dma_mapping list to find the
 * corresponding DMA address क्रम the associated user-space address.
 */
अटल पूर्णांक genwqe_mmap(काष्ठा file *filp, काष्ठा vm_area_काष्ठा *vma)
अणु
	पूर्णांक rc;
	अचिन्हित दीर्घ pfn, vsize = vma->vm_end - vma->vm_start;
	काष्ठा genwqe_file *cfile = (काष्ठा genwqe_file *)filp->निजी_data;
	काष्ठा genwqe_dev *cd = cfile->cd;
	काष्ठा dma_mapping *dma_map;

	अगर (vsize == 0)
		वापस -EINVAL;

	अगर (get_order(vsize) > MAX_ORDER)
		वापस -ENOMEM;

	dma_map = kzalloc(माप(काष्ठा dma_mapping), GFP_KERNEL);
	अगर (dma_map == शून्य)
		वापस -ENOMEM;

	genwqe_mapping_init(dma_map, GENWQE_MAPPING_RAW);
	dma_map->u_vaddr = (व्योम *)vma->vm_start;
	dma_map->size = vsize;
	dma_map->nr_pages = DIV_ROUND_UP(vsize, PAGE_SIZE);
	dma_map->k_vaddr = __genwqe_alloc_consistent(cd, vsize,
						     &dma_map->dma_addr);
	अगर (dma_map->k_vaddr == शून्य) अणु
		rc = -ENOMEM;
		जाओ मुक्त_dma_map;
	पूर्ण

	अगर (capable(CAP_SYS_ADMIN) && (vsize > माप(dma_addr_t)))
		*(dma_addr_t *)dma_map->k_vaddr = dma_map->dma_addr;

	pfn = virt_to_phys(dma_map->k_vaddr) >> PAGE_SHIFT;
	rc = remap_pfn_range(vma,
			     vma->vm_start,
			     pfn,
			     vsize,
			     vma->vm_page_prot);
	अगर (rc != 0) अणु
		rc = -EFAULT;
		जाओ मुक्त_dma_mem;
	पूर्ण

	vma->vm_निजी_data = cfile;
	vma->vm_ops = &genwqe_vma_ops;
	__genwqe_add_mapping(cfile, dma_map);

	वापस 0;

 मुक्त_dma_mem:
	__genwqe_मुक्त_consistent(cd, dma_map->size,
				dma_map->k_vaddr,
				dma_map->dma_addr);
 मुक्त_dma_map:
	kमुक्त(dma_map);
	वापस rc;
पूर्ण

#घोषणा	FLASH_BLOCK	0x40000	/* we use 256k blocks */

/**
 * करो_flash_update() - Excute flash update (ग_लिखो image or CVPD)
 * @cfile:	Descriptor of खोलोed file
 * @load:      details about image load
 *
 * Return: 0 अगर successful
 */
अटल पूर्णांक करो_flash_update(काष्ठा genwqe_file *cfile,
			   काष्ठा genwqe_bitstream *load)
अणु
	पूर्णांक rc = 0;
	पूर्णांक blocks_to_flash;
	dma_addr_t dma_addr;
	u64 flash = 0;
	माप_प्रकार tocopy = 0;
	u8 __user *buf;
	u8 *xbuf;
	u32 crc;
	u8 cmकरोpts;
	काष्ठा genwqe_dev *cd = cfile->cd;
	काष्ठा file *filp = cfile->filp;
	काष्ठा pci_dev *pci_dev = cd->pci_dev;

	अगर ((load->size & 0x3) != 0)
		वापस -EINVAL;

	अगर (((अचिन्हित दीर्घ)(load->data_addr) & ~PAGE_MASK) != 0)
		वापस -EINVAL;

	/* FIXME Bits have changed क्रम new service layer! */
	चयन ((अक्षर)load->partition) अणु
	हाल '0':
		cmकरोpts = 0x14;
		अवरोध;		/* करोwnload/erase_first/part_0 */
	हाल '1':
		cmकरोpts = 0x1C;
		अवरोध;		/* करोwnload/erase_first/part_1 */
	हाल 'v':
		cmकरोpts = 0x0C;
		अवरोध;		/* करोwnload/erase_first/vpd */
	शेष:
		वापस -EINVAL;
	पूर्ण

	buf = (u8 __user *)load->data_addr;
	xbuf = __genwqe_alloc_consistent(cd, FLASH_BLOCK, &dma_addr);
	अगर (xbuf == शून्य)
		वापस -ENOMEM;

	blocks_to_flash = load->size / FLASH_BLOCK;
	जबतक (load->size) अणु
		काष्ठा genwqe_ddcb_cmd *req;

		/*
		 * We must be 4 byte aligned. Buffer must be 0 appened
		 * to have defined values when calculating CRC.
		 */
		tocopy = min_t(माप_प्रकार, load->size, FLASH_BLOCK);

		rc = copy_from_user(xbuf, buf, tocopy);
		अगर (rc) अणु
			rc = -EFAULT;
			जाओ मुक्त_buffer;
		पूर्ण
		crc = genwqe_crc32(xbuf, tocopy, 0xffffffff);

		dev_dbg(&pci_dev->dev,
			"[%s] DMA: %lx CRC: %08x SZ: %ld %d\n",
			__func__, (अचिन्हित दीर्घ)dma_addr, crc, tocopy,
			blocks_to_flash);

		/* prepare DDCB क्रम SLU process */
		req = ddcb_requ_alloc();
		अगर (req == शून्य) अणु
			rc = -ENOMEM;
			जाओ मुक्त_buffer;
		पूर्ण

		req->cmd = SLCMD_MOVE_FLASH;
		req->cmकरोpts = cmकरोpts;

		/* prepare invariant values */
		अगर (genwqe_get_slu_id(cd) <= 0x2) अणु
			*(__be64 *)&req->__asiv[0]  = cpu_to_be64(dma_addr);
			*(__be64 *)&req->__asiv[8]  = cpu_to_be64(tocopy);
			*(__be64 *)&req->__asiv[16] = cpu_to_be64(flash);
			*(__be32 *)&req->__asiv[24] = cpu_to_be32(0);
			req->__asiv[24]	       = load->uid;
			*(__be32 *)&req->__asiv[28] = cpu_to_be32(crc);

			/* क्रम simulation only */
			*(__be64 *)&req->__asiv[88] = cpu_to_be64(load->slu_id);
			*(__be64 *)&req->__asiv[96] = cpu_to_be64(load->app_id);
			req->asiv_length = 32; /* bytes included in crc calc */
		पूर्ण अन्यथा अणु	/* setup DDCB क्रम ATS architecture */
			*(__be64 *)&req->asiv[0]  = cpu_to_be64(dma_addr);
			*(__be32 *)&req->asiv[8]  = cpu_to_be32(tocopy);
			*(__be32 *)&req->asiv[12] = cpu_to_be32(0); /* resvd */
			*(__be64 *)&req->asiv[16] = cpu_to_be64(flash);
			*(__be32 *)&req->asiv[24] = cpu_to_be32(load->uid<<24);
			*(__be32 *)&req->asiv[28] = cpu_to_be32(crc);

			/* क्रम simulation only */
			*(__be64 *)&req->asiv[80] = cpu_to_be64(load->slu_id);
			*(__be64 *)&req->asiv[88] = cpu_to_be64(load->app_id);

			/* Rd only */
			req->ats = 0x4ULL << 44;
			req->asiv_length = 40; /* bytes included in crc calc */
		पूर्ण
		req->asv_length  = 8;

		/* For Genwqe5 we get back the calculated CRC */
		*(u64 *)&req->asv[0] = 0ULL;			/* 0x80 */

		rc = __genwqe_execute_raw_ddcb(cd, req, filp->f_flags);

		load->retc = req->retc;
		load->attn = req->attn;
		load->progress = req->progress;

		अगर (rc < 0) अणु
			ddcb_requ_मुक्त(req);
			जाओ मुक्त_buffer;
		पूर्ण

		अगर (req->retc != DDCB_RETC_COMPLETE) अणु
			rc = -EIO;
			ddcb_requ_मुक्त(req);
			जाओ मुक्त_buffer;
		पूर्ण

		load->size  -= tocopy;
		flash += tocopy;
		buf += tocopy;
		blocks_to_flash--;
		ddcb_requ_मुक्त(req);
	पूर्ण

 मुक्त_buffer:
	__genwqe_मुक्त_consistent(cd, FLASH_BLOCK, xbuf, dma_addr);
	वापस rc;
पूर्ण

अटल पूर्णांक करो_flash_पढ़ो(काष्ठा genwqe_file *cfile,
			 काष्ठा genwqe_bitstream *load)
अणु
	पूर्णांक rc, blocks_to_flash;
	dma_addr_t dma_addr;
	u64 flash = 0;
	माप_प्रकार tocopy = 0;
	u8 __user *buf;
	u8 *xbuf;
	u8 cmकरोpts;
	काष्ठा genwqe_dev *cd = cfile->cd;
	काष्ठा file *filp = cfile->filp;
	काष्ठा pci_dev *pci_dev = cd->pci_dev;
	काष्ठा genwqe_ddcb_cmd *cmd;

	अगर ((load->size & 0x3) != 0)
		वापस -EINVAL;

	अगर (((अचिन्हित दीर्घ)(load->data_addr) & ~PAGE_MASK) != 0)
		वापस -EINVAL;

	/* FIXME Bits have changed क्रम new service layer! */
	चयन ((अक्षर)load->partition) अणु
	हाल '0':
		cmकरोpts = 0x12;
		अवरोध;		/* upload/part_0 */
	हाल '1':
		cmकरोpts = 0x1A;
		अवरोध;		/* upload/part_1 */
	हाल 'v':
		cmकरोpts = 0x0A;
		अवरोध;		/* upload/vpd */
	शेष:
		वापस -EINVAL;
	पूर्ण

	buf = (u8 __user *)load->data_addr;
	xbuf = __genwqe_alloc_consistent(cd, FLASH_BLOCK, &dma_addr);
	अगर (xbuf == शून्य)
		वापस -ENOMEM;

	blocks_to_flash = load->size / FLASH_BLOCK;
	जबतक (load->size) अणु
		/*
		 * We must be 4 byte aligned. Buffer must be 0 appened
		 * to have defined values when calculating CRC.
		 */
		tocopy = min_t(माप_प्रकार, load->size, FLASH_BLOCK);

		dev_dbg(&pci_dev->dev,
			"[%s] DMA: %lx SZ: %ld %d\n",
			__func__, (अचिन्हित दीर्घ)dma_addr, tocopy,
			blocks_to_flash);

		/* prepare DDCB क्रम SLU process */
		cmd = ddcb_requ_alloc();
		अगर (cmd == शून्य) अणु
			rc = -ENOMEM;
			जाओ मुक्त_buffer;
		पूर्ण
		cmd->cmd = SLCMD_MOVE_FLASH;
		cmd->cmकरोpts = cmकरोpts;

		/* prepare invariant values */
		अगर (genwqe_get_slu_id(cd) <= 0x2) अणु
			*(__be64 *)&cmd->__asiv[0]  = cpu_to_be64(dma_addr);
			*(__be64 *)&cmd->__asiv[8]  = cpu_to_be64(tocopy);
			*(__be64 *)&cmd->__asiv[16] = cpu_to_be64(flash);
			*(__be32 *)&cmd->__asiv[24] = cpu_to_be32(0);
			cmd->__asiv[24] = load->uid;
			*(__be32 *)&cmd->__asiv[28] = cpu_to_be32(0) /* CRC */;
			cmd->asiv_length = 32; /* bytes included in crc calc */
		पूर्ण अन्यथा अणु	/* setup DDCB क्रम ATS architecture */
			*(__be64 *)&cmd->asiv[0]  = cpu_to_be64(dma_addr);
			*(__be32 *)&cmd->asiv[8]  = cpu_to_be32(tocopy);
			*(__be32 *)&cmd->asiv[12] = cpu_to_be32(0); /* resvd */
			*(__be64 *)&cmd->asiv[16] = cpu_to_be64(flash);
			*(__be32 *)&cmd->asiv[24] = cpu_to_be32(load->uid<<24);
			*(__be32 *)&cmd->asiv[28] = cpu_to_be32(0); /* CRC */

			/* rd/wr */
			cmd->ats = 0x5ULL << 44;
			cmd->asiv_length = 40; /* bytes included in crc calc */
		पूर्ण
		cmd->asv_length  = 8;

		/* we only get back the calculated CRC */
		*(u64 *)&cmd->asv[0] = 0ULL;	/* 0x80 */

		rc = __genwqe_execute_raw_ddcb(cd, cmd, filp->f_flags);

		load->retc = cmd->retc;
		load->attn = cmd->attn;
		load->progress = cmd->progress;

		अगर ((rc < 0) && (rc != -EBADMSG)) अणु
			ddcb_requ_मुक्त(cmd);
			जाओ मुक्त_buffer;
		पूर्ण

		rc = copy_to_user(buf, xbuf, tocopy);
		अगर (rc) अणु
			rc = -EFAULT;
			ddcb_requ_मुक्त(cmd);
			जाओ मुक्त_buffer;
		पूर्ण

		/* We know that we can get retc 0x104 with CRC err */
		अगर (((cmd->retc == DDCB_RETC_FAULT) &&
		     (cmd->attn != 0x02)) ||  /* Normally ignore CRC error */
		    ((cmd->retc == DDCB_RETC_COMPLETE) &&
		     (cmd->attn != 0x00))) अणु  /* Everything was fine */
			rc = -EIO;
			ddcb_requ_मुक्त(cmd);
			जाओ मुक्त_buffer;
		पूर्ण

		load->size  -= tocopy;
		flash += tocopy;
		buf += tocopy;
		blocks_to_flash--;
		ddcb_requ_मुक्त(cmd);
	पूर्ण
	rc = 0;

 मुक्त_buffer:
	__genwqe_मुक्त_consistent(cd, FLASH_BLOCK, xbuf, dma_addr);
	वापस rc;
पूर्ण

अटल पूर्णांक genwqe_pin_mem(काष्ठा genwqe_file *cfile, काष्ठा genwqe_mem *m)
अणु
	पूर्णांक rc;
	काष्ठा genwqe_dev *cd = cfile->cd;
	काष्ठा pci_dev *pci_dev = cfile->cd->pci_dev;
	काष्ठा dma_mapping *dma_map;
	अचिन्हित दीर्घ map_addr;
	अचिन्हित दीर्घ map_size;

	अगर ((m->addr == 0x0) || (m->size == 0))
		वापस -EINVAL;
	अगर (m->size > अच_दीर्घ_उच्च - PAGE_SIZE - (m->addr & ~PAGE_MASK))
		वापस -EINVAL;

	map_addr = (m->addr & PAGE_MASK);
	map_size = round_up(m->size + (m->addr & ~PAGE_MASK), PAGE_SIZE);

	dma_map = kzalloc(माप(काष्ठा dma_mapping), GFP_KERNEL);
	अगर (dma_map == शून्य)
		वापस -ENOMEM;

	genwqe_mapping_init(dma_map, GENWQE_MAPPING_SGL_PINNED);
	rc = genwqe_user_vmap(cd, dma_map, (व्योम *)map_addr, map_size);
	अगर (rc != 0) अणु
		dev_err(&pci_dev->dev,
			"[%s] genwqe_user_vmap rc=%d\n", __func__, rc);
		kमुक्त(dma_map);
		वापस rc;
	पूर्ण

	genwqe_add_pin(cfile, dma_map);
	वापस 0;
पूर्ण

अटल पूर्णांक genwqe_unpin_mem(काष्ठा genwqe_file *cfile, काष्ठा genwqe_mem *m)
अणु
	काष्ठा genwqe_dev *cd = cfile->cd;
	काष्ठा dma_mapping *dma_map;
	अचिन्हित दीर्घ map_addr;
	अचिन्हित दीर्घ map_size;

	अगर (m->addr == 0x0)
		वापस -EINVAL;

	map_addr = (m->addr & PAGE_MASK);
	map_size = round_up(m->size + (m->addr & ~PAGE_MASK), PAGE_SIZE);

	dma_map = genwqe_search_pin(cfile, map_addr, map_size, शून्य);
	अगर (dma_map == शून्य)
		वापस -ENOENT;

	genwqe_del_pin(cfile, dma_map);
	genwqe_user_vunmap(cd, dma_map);
	kमुक्त(dma_map);
	वापस 0;
पूर्ण

/**
 * ddcb_cmd_cleanup() - Remove dynamically created fixup entries
 * @cfile:	Descriptor of खोलोed file
 * @req:	DDCB work request
 *
 * Only अगर there are any. Pinnings are not हटाओd.
 */
अटल पूर्णांक ddcb_cmd_cleanup(काष्ठा genwqe_file *cfile, काष्ठा ddcb_requ *req)
अणु
	अचिन्हित पूर्णांक i;
	काष्ठा dma_mapping *dma_map;
	काष्ठा genwqe_dev *cd = cfile->cd;

	क्रम (i = 0; i < DDCB_FIXUPS; i++) अणु
		dma_map = &req->dma_mappings[i];

		अगर (dma_mapping_used(dma_map)) अणु
			__genwqe_del_mapping(cfile, dma_map);
			genwqe_user_vunmap(cd, dma_map);
		पूर्ण
		अगर (req->sgls[i].sgl != शून्य)
			genwqe_मुक्त_sync_sgl(cd, &req->sgls[i]);
	पूर्ण
	वापस 0;
पूर्ण

/**
 * ddcb_cmd_fixups() - Establish DMA fixups/sglists क्रम user memory references
 * @cfile:	Descriptor of खोलोed file
 * @req:	DDCB work request
 *
 * Beक्रमe the DDCB माला_लो executed we need to handle the fixups. We
 * replace the user-space addresses with DMA addresses or करो
 * additional setup work e.g. generating a scatter-gather list which
 * is used to describe the memory referred to in the fixup.
 */
अटल पूर्णांक ddcb_cmd_fixups(काष्ठा genwqe_file *cfile, काष्ठा ddcb_requ *req)
अणु
	पूर्णांक rc;
	अचिन्हित पूर्णांक asiv_offs, i;
	काष्ठा genwqe_dev *cd = cfile->cd;
	काष्ठा genwqe_ddcb_cmd *cmd = &req->cmd;
	काष्ठा dma_mapping *m;

	क्रम (i = 0, asiv_offs = 0x00; asiv_offs <= 0x58;
	     i++, asiv_offs += 0x08) अणु

		u64 u_addr;
		dma_addr_t d_addr;
		u32 u_size = 0;
		u64 ats_flags;

		ats_flags = ATS_GET_FLAGS(cmd->ats, asiv_offs);

		चयन (ats_flags) अणु

		हाल ATS_TYPE_DATA:
			अवरोध;	/* nothing to करो here */

		हाल ATS_TYPE_FLAT_RDWR:
		हाल ATS_TYPE_FLAT_RD: अणु
			u_addr = be64_to_cpu(*((__be64 *)&cmd->
					       asiv[asiv_offs]));
			u_size = be32_to_cpu(*((__be32 *)&cmd->
					       asiv[asiv_offs + 0x08]));

			/*
			 * No data available. Ignore u_addr in this
			 * हाल and set addr to 0. Hardware must not
			 * fetch the buffer.
			 */
			अगर (u_size == 0x0) अणु
				*((__be64 *)&cmd->asiv[asiv_offs]) =
					cpu_to_be64(0x0);
				अवरोध;
			पूर्ण

			m = __genwqe_search_mapping(cfile, u_addr, u_size,
						   &d_addr, शून्य);
			अगर (m == शून्य) अणु
				rc = -EFAULT;
				जाओ err_out;
			पूर्ण

			*((__be64 *)&cmd->asiv[asiv_offs]) =
				cpu_to_be64(d_addr);
			अवरोध;
		पूर्ण

		हाल ATS_TYPE_SGL_RDWR:
		हाल ATS_TYPE_SGL_RD: अणु
			पूर्णांक page_offs;

			u_addr = be64_to_cpu(*((__be64 *)
					       &cmd->asiv[asiv_offs]));
			u_size = be32_to_cpu(*((__be32 *)
					       &cmd->asiv[asiv_offs + 0x08]));

			/*
			 * No data available. Ignore u_addr in this
			 * हाल and set addr to 0. Hardware must not
			 * fetch the empty sgl.
			 */
			अगर (u_size == 0x0) अणु
				*((__be64 *)&cmd->asiv[asiv_offs]) =
					cpu_to_be64(0x0);
				अवरोध;
			पूर्ण

			m = genwqe_search_pin(cfile, u_addr, u_size, शून्य);
			अगर (m != शून्य) अणु
				page_offs = (u_addr -
					     (u64)m->u_vaddr)/PAGE_SIZE;
			पूर्ण अन्यथा अणु
				m = &req->dma_mappings[i];

				genwqe_mapping_init(m,
						    GENWQE_MAPPING_SGL_TEMP);

				अगर (ats_flags == ATS_TYPE_SGL_RD)
					m->ग_लिखो = 0;

				rc = genwqe_user_vmap(cd, m, (व्योम *)u_addr,
						      u_size);
				अगर (rc != 0)
					जाओ err_out;

				__genwqe_add_mapping(cfile, m);
				page_offs = 0;
			पूर्ण

			/* create genwqe style scatter gather list */
			rc = genwqe_alloc_sync_sgl(cd, &req->sgls[i],
						   (व्योम __user *)u_addr,
						   u_size, m->ग_लिखो);
			अगर (rc != 0)
				जाओ err_out;

			genwqe_setup_sgl(cd, &req->sgls[i],
					 &m->dma_list[page_offs]);

			*((__be64 *)&cmd->asiv[asiv_offs]) =
				cpu_to_be64(req->sgls[i].sgl_dma_addr);

			अवरोध;
		पूर्ण
		शेष:
			rc = -EINVAL;
			जाओ err_out;
		पूर्ण
	पूर्ण
	वापस 0;

 err_out:
	ddcb_cmd_cleanup(cfile, req);
	वापस rc;
पूर्ण

/**
 * genwqe_execute_ddcb() - Execute DDCB using userspace address fixups
 * @cfile:	Descriptor of खोलोed file
 * @cmd:        Command identअगरier (passed from user)
 *
 * The code will build up the translation tables or lookup the
 * contignous memory allocation table to find the right translations
 * and DMA addresses.
 */
अटल पूर्णांक genwqe_execute_ddcb(काष्ठा genwqe_file *cfile,
			       काष्ठा genwqe_ddcb_cmd *cmd)
अणु
	पूर्णांक rc;
	काष्ठा genwqe_dev *cd = cfile->cd;
	काष्ठा file *filp = cfile->filp;
	काष्ठा ddcb_requ *req = container_of(cmd, काष्ठा ddcb_requ, cmd);

	rc = ddcb_cmd_fixups(cfile, req);
	अगर (rc != 0)
		वापस rc;

	rc = __genwqe_execute_raw_ddcb(cd, cmd, filp->f_flags);
	ddcb_cmd_cleanup(cfile, req);
	वापस rc;
पूर्ण

अटल पूर्णांक करो_execute_ddcb(काष्ठा genwqe_file *cfile,
			   अचिन्हित दीर्घ arg, पूर्णांक raw)
अणु
	पूर्णांक rc;
	काष्ठा genwqe_ddcb_cmd *cmd;
	काष्ठा genwqe_dev *cd = cfile->cd;
	काष्ठा file *filp = cfile->filp;

	cmd = ddcb_requ_alloc();
	अगर (cmd == शून्य)
		वापस -ENOMEM;

	अगर (copy_from_user(cmd, (व्योम __user *)arg, माप(*cmd))) अणु
		ddcb_requ_मुक्त(cmd);
		वापस -EFAULT;
	पूर्ण

	अगर (!raw)
		rc = genwqe_execute_ddcb(cfile, cmd);
	अन्यथा
		rc = __genwqe_execute_raw_ddcb(cd, cmd, filp->f_flags);

	/* Copy back only the modअगरed fields. Do not copy ASIV
	   back since the copy got modअगरied by the driver. */
	अगर (copy_to_user((व्योम __user *)arg, cmd,
			 माप(*cmd) - DDCB_ASIV_LENGTH)) अणु
		ddcb_requ_मुक्त(cmd);
		वापस -EFAULT;
	पूर्ण

	ddcb_requ_मुक्त(cmd);
	वापस rc;
पूर्ण

/**
 * genwqe_ioctl() - IO control
 * @filp:       file handle
 * @cmd:        command identअगरier (passed from user)
 * @arg:        argument (passed from user)
 *
 * Return: 0 success
 */
अटल दीर्घ genwqe_ioctl(काष्ठा file *filp, अचिन्हित पूर्णांक cmd,
			 अचिन्हित दीर्घ arg)
अणु
	पूर्णांक rc = 0;
	काष्ठा genwqe_file *cfile = (काष्ठा genwqe_file *)filp->निजी_data;
	काष्ठा genwqe_dev *cd = cfile->cd;
	काष्ठा pci_dev *pci_dev = cd->pci_dev;
	काष्ठा genwqe_reg_io __user *io;
	u64 val;
	u32 reg_offs;

	/* Return -EIO अगर card hit EEH */
	अगर (pci_channel_offline(pci_dev))
		वापस -EIO;

	अगर (_IOC_TYPE(cmd) != GENWQE_IOC_CODE)
		वापस -EINVAL;

	चयन (cmd) अणु

	हाल GENWQE_GET_CARD_STATE:
		put_user(cd->card_state, (क्रमागत genwqe_card_state __user *)arg);
		वापस 0;

		/* Register access */
	हाल GENWQE_READ_REG64: अणु
		io = (काष्ठा genwqe_reg_io __user *)arg;

		अगर (get_user(reg_offs, &io->num))
			वापस -EFAULT;

		अगर ((reg_offs >= cd->mmio_len) || (reg_offs & 0x7))
			वापस -EINVAL;

		val = __genwqe_पढ़ोq(cd, reg_offs);
		put_user(val, &io->val64);
		वापस 0;
	पूर्ण

	हाल GENWQE_WRITE_REG64: अणु
		io = (काष्ठा genwqe_reg_io __user *)arg;

		अगर (!capable(CAP_SYS_ADMIN))
			वापस -EPERM;

		अगर ((filp->f_flags & O_ACCMODE) == O_RDONLY)
			वापस -EPERM;

		अगर (get_user(reg_offs, &io->num))
			वापस -EFAULT;

		अगर ((reg_offs >= cd->mmio_len) || (reg_offs & 0x7))
			वापस -EINVAL;

		अगर (get_user(val, &io->val64))
			वापस -EFAULT;

		__genwqe_ग_लिखोq(cd, reg_offs, val);
		वापस 0;
	पूर्ण

	हाल GENWQE_READ_REG32: अणु
		io = (काष्ठा genwqe_reg_io __user *)arg;

		अगर (get_user(reg_offs, &io->num))
			वापस -EFAULT;

		अगर ((reg_offs >= cd->mmio_len) || (reg_offs & 0x3))
			वापस -EINVAL;

		val = __genwqe_पढ़ोl(cd, reg_offs);
		put_user(val, &io->val64);
		वापस 0;
	पूर्ण

	हाल GENWQE_WRITE_REG32: अणु
		io = (काष्ठा genwqe_reg_io __user *)arg;

		अगर (!capable(CAP_SYS_ADMIN))
			वापस -EPERM;

		अगर ((filp->f_flags & O_ACCMODE) == O_RDONLY)
			वापस -EPERM;

		अगर (get_user(reg_offs, &io->num))
			वापस -EFAULT;

		अगर ((reg_offs >= cd->mmio_len) || (reg_offs & 0x3))
			वापस -EINVAL;

		अगर (get_user(val, &io->val64))
			वापस -EFAULT;

		__genwqe_ग_लिखोl(cd, reg_offs, val);
		वापस 0;
	पूर्ण

		/* Flash update/पढ़ोing */
	हाल GENWQE_SLU_UPDATE: अणु
		काष्ठा genwqe_bitstream load;

		अगर (!genwqe_is_privileged(cd))
			वापस -EPERM;

		अगर ((filp->f_flags & O_ACCMODE) == O_RDONLY)
			वापस -EPERM;

		अगर (copy_from_user(&load, (व्योम __user *)arg,
				   माप(load)))
			वापस -EFAULT;

		rc = करो_flash_update(cfile, &load);

		अगर (copy_to_user((व्योम __user *)arg, &load, माप(load)))
			वापस -EFAULT;

		वापस rc;
	पूर्ण

	हाल GENWQE_SLU_READ: अणु
		काष्ठा genwqe_bitstream load;

		अगर (!genwqe_is_privileged(cd))
			वापस -EPERM;

		अगर (genwqe_flash_पढ़ोback_fails(cd))
			वापस -ENOSPC;	 /* known to fail क्रम old versions */

		अगर (copy_from_user(&load, (व्योम __user *)arg, माप(load)))
			वापस -EFAULT;

		rc = करो_flash_पढ़ो(cfile, &load);

		अगर (copy_to_user((व्योम __user *)arg, &load, माप(load)))
			वापस -EFAULT;

		वापस rc;
	पूर्ण

		/* memory pinning and unpinning */
	हाल GENWQE_PIN_MEM: अणु
		काष्ठा genwqe_mem m;

		अगर (copy_from_user(&m, (व्योम __user *)arg, माप(m)))
			वापस -EFAULT;

		वापस genwqe_pin_mem(cfile, &m);
	पूर्ण

	हाल GENWQE_UNPIN_MEM: अणु
		काष्ठा genwqe_mem m;

		अगर (copy_from_user(&m, (व्योम __user *)arg, माप(m)))
			वापस -EFAULT;

		वापस genwqe_unpin_mem(cfile, &m);
	पूर्ण

		/* launch an DDCB and रुको क्रम completion */
	हाल GENWQE_EXECUTE_DDCB:
		वापस करो_execute_ddcb(cfile, arg, 0);

	हाल GENWQE_EXECUTE_RAW_DDCB: अणु

		अगर (!capable(CAP_SYS_ADMIN))
			वापस -EPERM;

		वापस करो_execute_ddcb(cfile, arg, 1);
	पूर्ण

	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस rc;
पूर्ण

अटल स्थिर काष्ठा file_operations genwqe_fops = अणु
	.owner		= THIS_MODULE,
	.खोलो		= genwqe_खोलो,
	.fasync		= genwqe_fasync,
	.mmap		= genwqe_mmap,
	.unlocked_ioctl	= genwqe_ioctl,
	.compat_ioctl   = compat_ptr_ioctl,
	.release	= genwqe_release,
पूर्ण;

अटल पूर्णांक genwqe_device_initialized(काष्ठा genwqe_dev *cd)
अणु
	वापस cd->dev != शून्य;
पूर्ण

/**
 * genwqe_device_create() - Create and configure genwqe अक्षर device
 * @cd:      genwqe device descriptor
 *
 * This function must be called beक्रमe we create any more genwqe
 * अक्षरacter devices, because it is allocating the major and minor
 * number which are supposed to be used by the client drivers.
 */
पूर्णांक genwqe_device_create(काष्ठा genwqe_dev *cd)
अणु
	पूर्णांक rc;
	काष्ठा pci_dev *pci_dev = cd->pci_dev;

	/*
	 * Here starts the inभागidual setup per client. It must
	 * initialize its own cdev data काष्ठाure with its own fops.
	 * The appropriate devnum needs to be created. The ranges must
	 * not overlap.
	 */
	rc = alloc_chrdev_region(&cd->devnum_genwqe, 0,
				 GENWQE_MAX_MINOR, GENWQE_DEVNAME);
	अगर (rc < 0) अणु
		dev_err(&pci_dev->dev, "err: alloc_chrdev_region failed\n");
		जाओ err_dev;
	पूर्ण

	cdev_init(&cd->cdev_genwqe, &genwqe_fops);
	cd->cdev_genwqe.owner = THIS_MODULE;

	rc = cdev_add(&cd->cdev_genwqe, cd->devnum_genwqe, 1);
	अगर (rc < 0) अणु
		dev_err(&pci_dev->dev, "err: cdev_add failed\n");
		जाओ err_add;
	पूर्ण

	/*
	 * Finally the device in /dev/... must be created. The rule is
	 * to use card%d_clientname क्रम each created device.
	 */
	cd->dev = device_create_with_groups(cd->class_genwqe,
					    &cd->pci_dev->dev,
					    cd->devnum_genwqe, cd,
					    genwqe_attribute_groups,
					    GENWQE_DEVNAME "%u_card",
					    cd->card_idx);
	अगर (IS_ERR(cd->dev)) अणु
		rc = PTR_ERR(cd->dev);
		जाओ err_cdev;
	पूर्ण

	genwqe_init_debugfs(cd);

	वापस 0;

 err_cdev:
	cdev_del(&cd->cdev_genwqe);
 err_add:
	unरेजिस्टर_chrdev_region(cd->devnum_genwqe, GENWQE_MAX_MINOR);
 err_dev:
	cd->dev = शून्य;
	वापस rc;
पूर्ण

अटल पूर्णांक genwqe_inक्रमm_and_stop_processes(काष्ठा genwqe_dev *cd)
अणु
	पूर्णांक rc;
	अचिन्हित पूर्णांक i;
	काष्ठा pci_dev *pci_dev = cd->pci_dev;

	अगर (!genwqe_खोलो_files(cd))
		वापस 0;

	dev_warn(&pci_dev->dev, "[%s] send SIGIO and wait ...\n", __func__);

	rc = genwqe_समाप्त_fasync(cd, SIGIO);
	अगर (rc > 0) अणु
		/* give समाप्त_समयout seconds to बंद file descriptors ... */
		क्रम (i = 0; (i < GENWQE_KILL_TIMEOUT) &&
			     genwqe_खोलो_files(cd); i++) अणु
			dev_info(&pci_dev->dev, "  %d sec ...", i);

			cond_resched();
			msleep(1000);
		पूर्ण

		/* अगर no खोलो files we can safely जारी, अन्यथा ... */
		अगर (!genwqe_खोलो_files(cd))
			वापस 0;

		dev_warn(&pci_dev->dev,
			 "[%s] send SIGKILL and wait ...\n", __func__);

		rc = genwqe_terminate(cd);
		अगर (rc) अणु
			/* Give समाप्त_timout more seconds to end processes */
			क्रम (i = 0; (i < GENWQE_KILL_TIMEOUT) &&
				     genwqe_खोलो_files(cd); i++) अणु
				dev_warn(&pci_dev->dev, "  %d sec ...", i);

				cond_resched();
				msleep(1000);
			पूर्ण
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/**
 * genwqe_device_हटाओ() - Remove genwqe's अक्षर device
 * @cd: GenWQE device inक्रमmation
 *
 * This function must be called after the client devices are हटाओd
 * because it will मुक्त the major/minor number range क्रम the genwqe
 * drivers.
 *
 * This function must be robust enough to be called twice.
 */
पूर्णांक genwqe_device_हटाओ(काष्ठा genwqe_dev *cd)
अणु
	पूर्णांक rc;
	काष्ठा pci_dev *pci_dev = cd->pci_dev;

	अगर (!genwqe_device_initialized(cd))
		वापस 1;

	genwqe_inक्रमm_and_stop_processes(cd);

	/*
	 * We currently करो रुको until all filedescriptors are
	 * बंदd. This leads to a problem when we पात the
	 * application which will decrease this reference from
	 * 1/unused to 0/illegal and not from 2/used 1/empty.
	 */
	rc = kref_पढ़ो(&cd->cdev_genwqe.kobj.kref);
	अगर (rc != 1) अणु
		dev_err(&pci_dev->dev,
			"[%s] err: cdev_genwqe...refcount=%d\n", __func__, rc);
		panic("Fatal err: cannot free resources with pending references!");
	पूर्ण

	genqwe_निकास_debugfs(cd);
	device_destroy(cd->class_genwqe, cd->devnum_genwqe);
	cdev_del(&cd->cdev_genwqe);
	unरेजिस्टर_chrdev_region(cd->devnum_genwqe, GENWQE_MAX_MINOR);
	cd->dev = शून्य;

	वापस 0;
पूर्ण
