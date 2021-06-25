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
 * Miscelanous functionality used in the other GenWQE driver parts.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/page-flags.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/hugetlb.h>
#समावेश <linux/iommu.h>
#समावेश <linux/pci.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/delay.h>
#समावेश <linux/pgtable.h>

#समावेश "genwqe_driver.h"
#समावेश "card_base.h"
#समावेश "card_ddcb.h"

/**
 * __genwqe_ग_लिखोq() - Write 64-bit रेजिस्टर
 * @cd:	        genwqe device descriptor
 * @byte_offs:  byte offset within BAR
 * @val:        64-bit value
 *
 * Return: 0 अगर success; < 0 अगर error
 */
पूर्णांक __genwqe_ग_लिखोq(काष्ठा genwqe_dev *cd, u64 byte_offs, u64 val)
अणु
	काष्ठा pci_dev *pci_dev = cd->pci_dev;

	अगर (cd->err_inject & GENWQE_INJECT_HARDWARE_FAILURE)
		वापस -EIO;

	अगर (cd->mmio == शून्य)
		वापस -EIO;

	अगर (pci_channel_offline(pci_dev))
		वापस -EIO;

	__raw_ग_लिखोq((__क्रमce u64)cpu_to_be64(val), cd->mmio + byte_offs);
	वापस 0;
पूर्ण

/**
 * __genwqe_पढ़ोq() - Read 64-bit रेजिस्टर
 * @cd:         genwqe device descriptor
 * @byte_offs:  offset within BAR
 *
 * Return: value from रेजिस्टर
 */
u64 __genwqe_पढ़ोq(काष्ठा genwqe_dev *cd, u64 byte_offs)
अणु
	अगर (cd->err_inject & GENWQE_INJECT_HARDWARE_FAILURE)
		वापस 0xffffffffffffffffull;

	अगर ((cd->err_inject & GENWQE_INJECT_GFIR_FATAL) &&
	    (byte_offs == IO_SLC_CFGREG_GFIR))
		वापस 0x000000000000ffffull;

	अगर ((cd->err_inject & GENWQE_INJECT_GFIR_INFO) &&
	    (byte_offs == IO_SLC_CFGREG_GFIR))
		वापस 0x00000000ffff0000ull;

	अगर (cd->mmio == शून्य)
		वापस 0xffffffffffffffffull;

	वापस be64_to_cpu((__क्रमce __be64)__raw_पढ़ोq(cd->mmio + byte_offs));
पूर्ण

/**
 * __genwqe_ग_लिखोl() - Write 32-bit रेजिस्टर
 * @cd:	        genwqe device descriptor
 * @byte_offs:  byte offset within BAR
 * @val:        32-bit value
 *
 * Return: 0 अगर success; < 0 अगर error
 */
पूर्णांक __genwqe_ग_लिखोl(काष्ठा genwqe_dev *cd, u64 byte_offs, u32 val)
अणु
	काष्ठा pci_dev *pci_dev = cd->pci_dev;

	अगर (cd->err_inject & GENWQE_INJECT_HARDWARE_FAILURE)
		वापस -EIO;

	अगर (cd->mmio == शून्य)
		वापस -EIO;

	अगर (pci_channel_offline(pci_dev))
		वापस -EIO;

	__raw_ग_लिखोl((__क्रमce u32)cpu_to_be32(val), cd->mmio + byte_offs);
	वापस 0;
पूर्ण

/**
 * __genwqe_पढ़ोl() - Read 32-bit रेजिस्टर
 * @cd:         genwqe device descriptor
 * @byte_offs:  offset within BAR
 *
 * Return: Value from रेजिस्टर
 */
u32 __genwqe_पढ़ोl(काष्ठा genwqe_dev *cd, u64 byte_offs)
अणु
	अगर (cd->err_inject & GENWQE_INJECT_HARDWARE_FAILURE)
		वापस 0xffffffff;

	अगर (cd->mmio == शून्य)
		वापस 0xffffffff;

	वापस be32_to_cpu((__क्रमce __be32)__raw_पढ़ोl(cd->mmio + byte_offs));
पूर्ण

/**
 * genwqe_पढ़ो_app_id() - Extract app_id
 * @cd:	        genwqe device descriptor
 * @app_name:   carrier used to pass-back name
 * @len:        length of data क्रम name
 *
 * app_unitcfg need to be filled with valid data first
 */
पूर्णांक genwqe_पढ़ो_app_id(काष्ठा genwqe_dev *cd, अक्षर *app_name, पूर्णांक len)
अणु
	पूर्णांक i, j;
	u32 app_id = (u32)cd->app_unitcfg;

	स_रखो(app_name, 0, len);
	क्रम (i = 0, j = 0; j < min(len, 4); j++) अणु
		अक्षर ch = (अक्षर)((app_id >> (24 - j*8)) & 0xff);

		अगर (ch == ' ')
			जारी;
		app_name[i++] = है_छाप(ch) ? ch : 'X';
	पूर्ण
	वापस i;
पूर्ण

/**
 * genwqe_init_crc32() - Prepare a lookup table क्रम fast crc32 calculations
 *
 * Existing kernel functions seem to use a dअगरferent polynom,
 * thereक्रमe we could not use them here.
 *
 * Genwqe's Polynomial = 0x20044009
 */
#घोषणा CRC32_POLYNOMIAL	0x20044009
अटल u32 crc32_tab[256];	/* crc32 lookup table */

व्योम genwqe_init_crc32(व्योम)
अणु
	पूर्णांक i, j;
	u32 crc;

	क्रम (i = 0;  i < 256;  i++) अणु
		crc = i << 24;
		क्रम (j = 0;  j < 8;  j++) अणु
			अगर (crc & 0x80000000)
				crc = (crc << 1) ^ CRC32_POLYNOMIAL;
			अन्यथा
				crc = (crc << 1);
		पूर्ण
		crc32_tab[i] = crc;
	पूर्ण
पूर्ण

/**
 * genwqe_crc32() - Generate 32-bit crc as required क्रम DDCBs
 * @buff:       poपूर्णांकer to data buffer
 * @len:        length of data क्रम calculation
 * @init:       initial crc (0xffffffff at start)
 *
 * polynomial = x^32 * + x^29 + x^18 + x^14 + x^3 + 1 (0x20044009)
 *
 * Example: 4 bytes 0x01 0x02 0x03 0x04 with init=0xffffffff should
 * result in a crc32 of 0xf33cb7d3.
 *
 * The existing kernel crc functions did not cover this polynom yet.
 *
 * Return: crc32 checksum.
 */
u32 genwqe_crc32(u8 *buff, माप_प्रकार len, u32 init)
अणु
	पूर्णांक i;
	u32 crc;

	crc = init;
	जबतक (len--) अणु
		i = ((crc >> 24) ^ *buff++) & 0xFF;
		crc = (crc << 8) ^ crc32_tab[i];
	पूर्ण
	वापस crc;
पूर्ण

व्योम *__genwqe_alloc_consistent(काष्ठा genwqe_dev *cd, माप_प्रकार size,
			       dma_addr_t *dma_handle)
अणु
	अगर (get_order(size) >= MAX_ORDER)
		वापस शून्य;

	वापस dma_alloc_coherent(&cd->pci_dev->dev, size, dma_handle,
				  GFP_KERNEL);
पूर्ण

व्योम __genwqe_मुक्त_consistent(काष्ठा genwqe_dev *cd, माप_प्रकार size,
			     व्योम *vaddr, dma_addr_t dma_handle)
अणु
	अगर (vaddr == शून्य)
		वापस;

	dma_मुक्त_coherent(&cd->pci_dev->dev, size, vaddr, dma_handle);
पूर्ण

अटल व्योम genwqe_unmap_pages(काष्ठा genwqe_dev *cd, dma_addr_t *dma_list,
			      पूर्णांक num_pages)
अणु
	पूर्णांक i;
	काष्ठा pci_dev *pci_dev = cd->pci_dev;

	क्रम (i = 0; (i < num_pages) && (dma_list[i] != 0x0); i++) अणु
		pci_unmap_page(pci_dev, dma_list[i],
			       PAGE_SIZE, PCI_DMA_BIसूचीECTIONAL);
		dma_list[i] = 0x0;
	पूर्ण
पूर्ण

अटल पूर्णांक genwqe_map_pages(काष्ठा genwqe_dev *cd,
			   काष्ठा page **page_list, पूर्णांक num_pages,
			   dma_addr_t *dma_list)
अणु
	पूर्णांक i;
	काष्ठा pci_dev *pci_dev = cd->pci_dev;

	/* establish DMA mapping क्रम requested pages */
	क्रम (i = 0; i < num_pages; i++) अणु
		dma_addr_t daddr;

		dma_list[i] = 0x0;
		daddr = pci_map_page(pci_dev, page_list[i],
				     0,	 /* map_offs */
				     PAGE_SIZE,
				     PCI_DMA_BIसूचीECTIONAL);  /* FIXME rd/rw */

		अगर (pci_dma_mapping_error(pci_dev, daddr)) अणु
			dev_err(&pci_dev->dev,
				"[%s] err: no dma addr daddr=%016llx!\n",
				__func__, (दीर्घ दीर्घ)daddr);
			जाओ err;
		पूर्ण

		dma_list[i] = daddr;
	पूर्ण
	वापस 0;

 err:
	genwqe_unmap_pages(cd, dma_list, num_pages);
	वापस -EIO;
पूर्ण

अटल पूर्णांक genwqe_sgl_size(पूर्णांक num_pages)
अणु
	पूर्णांक len, num_tlb = num_pages / 7;

	len = माप(काष्ठा sg_entry) * (num_pages+num_tlb + 1);
	वापस roundup(len, PAGE_SIZE);
पूर्ण

/*
 * genwqe_alloc_sync_sgl() - Allocate memory क्रम sgl and overlapping pages
 *
 * Allocates memory क्रम sgl and overlapping pages. Pages which might
 * overlap other user-space memory blocks are being cached क्रम DMAs,
 * such that we करो not run पूर्णांकo syncronization issues. Data is copied
 * from user-space पूर्णांकo the cached pages.
 */
पूर्णांक genwqe_alloc_sync_sgl(काष्ठा genwqe_dev *cd, काष्ठा genwqe_sgl *sgl,
			  व्योम __user *user_addr, माप_प्रकार user_size, पूर्णांक ग_लिखो)
अणु
	पूर्णांक ret = -ENOMEM;
	काष्ठा pci_dev *pci_dev = cd->pci_dev;

	sgl->fpage_offs = offset_in_page((अचिन्हित दीर्घ)user_addr);
	sgl->fpage_size = min_t(माप_प्रकार, PAGE_SIZE-sgl->fpage_offs, user_size);
	sgl->nr_pages = DIV_ROUND_UP(sgl->fpage_offs + user_size, PAGE_SIZE);
	sgl->lpage_size = (user_size - sgl->fpage_size) % PAGE_SIZE;

	dev_dbg(&pci_dev->dev, "[%s] uaddr=%p usize=%8ld nr_pages=%ld fpage_offs=%lx fpage_size=%ld lpage_size=%ld\n",
		__func__, user_addr, user_size, sgl->nr_pages,
		sgl->fpage_offs, sgl->fpage_size, sgl->lpage_size);

	sgl->user_addr = user_addr;
	sgl->user_size = user_size;
	sgl->ग_लिखो = ग_लिखो;
	sgl->sgl_size = genwqe_sgl_size(sgl->nr_pages);

	अगर (get_order(sgl->sgl_size) > MAX_ORDER) अणु
		dev_err(&pci_dev->dev,
			"[%s] err: too much memory requested!\n", __func__);
		वापस ret;
	पूर्ण

	sgl->sgl = __genwqe_alloc_consistent(cd, sgl->sgl_size,
					     &sgl->sgl_dma_addr);
	अगर (sgl->sgl == शून्य) अणु
		dev_err(&pci_dev->dev,
			"[%s] err: no memory available!\n", __func__);
		वापस ret;
	पूर्ण

	/* Only use buffering on incomplete pages */
	अगर ((sgl->fpage_size != 0) && (sgl->fpage_size != PAGE_SIZE)) अणु
		sgl->fpage = __genwqe_alloc_consistent(cd, PAGE_SIZE,
						       &sgl->fpage_dma_addr);
		अगर (sgl->fpage == शून्य)
			जाओ err_out;

		/* Sync with user memory */
		अगर (copy_from_user(sgl->fpage + sgl->fpage_offs,
				   user_addr, sgl->fpage_size)) अणु
			ret = -EFAULT;
			जाओ err_out;
		पूर्ण
	पूर्ण
	अगर (sgl->lpage_size != 0) अणु
		sgl->lpage = __genwqe_alloc_consistent(cd, PAGE_SIZE,
						       &sgl->lpage_dma_addr);
		अगर (sgl->lpage == शून्य)
			जाओ err_out1;

		/* Sync with user memory */
		अगर (copy_from_user(sgl->lpage, user_addr + user_size -
				   sgl->lpage_size, sgl->lpage_size)) अणु
			ret = -EFAULT;
			जाओ err_out2;
		पूर्ण
	पूर्ण
	वापस 0;

 err_out2:
	__genwqe_मुक्त_consistent(cd, PAGE_SIZE, sgl->lpage,
				 sgl->lpage_dma_addr);
	sgl->lpage = शून्य;
	sgl->lpage_dma_addr = 0;
 err_out1:
	__genwqe_मुक्त_consistent(cd, PAGE_SIZE, sgl->fpage,
				 sgl->fpage_dma_addr);
	sgl->fpage = शून्य;
	sgl->fpage_dma_addr = 0;
 err_out:
	__genwqe_मुक्त_consistent(cd, sgl->sgl_size, sgl->sgl,
				 sgl->sgl_dma_addr);
	sgl->sgl = शून्य;
	sgl->sgl_dma_addr = 0;
	sgl->sgl_size = 0;

	वापस ret;
पूर्ण

पूर्णांक genwqe_setup_sgl(काष्ठा genwqe_dev *cd, काष्ठा genwqe_sgl *sgl,
		     dma_addr_t *dma_list)
अणु
	पूर्णांक i = 0, j = 0, p;
	अचिन्हित दीर्घ dma_offs, map_offs;
	dma_addr_t prev_daddr = 0;
	काष्ठा sg_entry *s, *last_s = शून्य;
	माप_प्रकार size = sgl->user_size;

	dma_offs = 128;		/* next block अगर needed/dma_offset */
	map_offs = sgl->fpage_offs; /* offset in first page */

	s = &sgl->sgl[0];	/* first set of 8 entries */
	p = 0;			/* page */
	जबतक (p < sgl->nr_pages) अणु
		dma_addr_t daddr;
		अचिन्हित पूर्णांक माप_प्रकारo_map;

		/* always ग_लिखो the chaining entry, cleanup is करोne later */
		j = 0;
		s[j].target_addr = cpu_to_be64(sgl->sgl_dma_addr + dma_offs);
		s[j].len	 = cpu_to_be32(128);
		s[j].flags	 = cpu_to_be32(SG_CHAINED);
		j++;

		जबतक (j < 8) अणु
			/* DMA mapping क्रम requested page, offs, size */
			माप_प्रकारo_map = min(size, PAGE_SIZE - map_offs);

			अगर ((p == 0) && (sgl->fpage != शून्य)) अणु
				daddr = sgl->fpage_dma_addr + map_offs;

			पूर्ण अन्यथा अगर ((p == sgl->nr_pages - 1) &&
				   (sgl->lpage != शून्य)) अणु
				daddr = sgl->lpage_dma_addr;
			पूर्ण अन्यथा अणु
				daddr = dma_list[p] + map_offs;
			पूर्ण

			size -= माप_प्रकारo_map;
			map_offs = 0;

			अगर (prev_daddr == daddr) अणु
				u32 prev_len = be32_to_cpu(last_s->len);

				/* pr_info("daddr combining: "
					"%016llx/%08x -> %016llx\n",
					prev_daddr, prev_len, daddr); */

				last_s->len = cpu_to_be32(prev_len +
							  माप_प्रकारo_map);

				p++; /* process next page */
				अगर (p == sgl->nr_pages)
					जाओ fixup;  /* nothing to करो */

				prev_daddr = daddr + माप_प्रकारo_map;
				जारी;
			पूर्ण

			/* start new entry */
			s[j].target_addr = cpu_to_be64(daddr);
			s[j].len	 = cpu_to_be32(माप_प्रकारo_map);
			s[j].flags	 = cpu_to_be32(SG_DATA);
			prev_daddr = daddr + माप_प्रकारo_map;
			last_s = &s[j];
			j++;

			p++;	/* process next page */
			अगर (p == sgl->nr_pages)
				जाओ fixup;  /* nothing to करो */
		पूर्ण
		dma_offs += 128;
		s += 8;		/* जारी 8 elements further */
	पूर्ण
 fixup:
	अगर (j == 1) अणु		/* combining happened on last entry! */
		s -= 8;		/* full shअगरt needed on previous sgl block */
		j =  7;		/* shअगरt all elements */
	पूर्ण

	क्रम (i = 0; i < j; i++)	/* move elements 1 up */
		s[i] = s[i + 1];

	s[i].target_addr = cpu_to_be64(0);
	s[i].len	 = cpu_to_be32(0);
	s[i].flags	 = cpu_to_be32(SG_END_LIST);
	वापस 0;
पूर्ण

/**
 * genwqe_मुक्त_sync_sgl() - Free memory क्रम sgl and overlapping pages
 * @cd:	        genwqe device descriptor
 * @sgl:        scatter gather list describing user-space memory
 *
 * After the DMA transfer has been completed we मुक्त the memory क्रम
 * the sgl and the cached pages. Data is being transferred from cached
 * pages पूर्णांकo user-space buffers.
 */
पूर्णांक genwqe_मुक्त_sync_sgl(काष्ठा genwqe_dev *cd, काष्ठा genwqe_sgl *sgl)
अणु
	पूर्णांक rc = 0;
	माप_प्रकार offset;
	अचिन्हित दीर्घ res;
	काष्ठा pci_dev *pci_dev = cd->pci_dev;

	अगर (sgl->fpage) अणु
		अगर (sgl->ग_लिखो) अणु
			res = copy_to_user(sgl->user_addr,
				sgl->fpage + sgl->fpage_offs, sgl->fpage_size);
			अगर (res) अणु
				dev_err(&pci_dev->dev,
					"[%s] err: copying fpage! (res=%lu)\n",
					__func__, res);
				rc = -EFAULT;
			पूर्ण
		पूर्ण
		__genwqe_मुक्त_consistent(cd, PAGE_SIZE, sgl->fpage,
					 sgl->fpage_dma_addr);
		sgl->fpage = शून्य;
		sgl->fpage_dma_addr = 0;
	पूर्ण
	अगर (sgl->lpage) अणु
		अगर (sgl->ग_लिखो) अणु
			offset = sgl->user_size - sgl->lpage_size;
			res = copy_to_user(sgl->user_addr + offset, sgl->lpage,
					   sgl->lpage_size);
			अगर (res) अणु
				dev_err(&pci_dev->dev,
					"[%s] err: copying lpage! (res=%lu)\n",
					__func__, res);
				rc = -EFAULT;
			पूर्ण
		पूर्ण
		__genwqe_मुक्त_consistent(cd, PAGE_SIZE, sgl->lpage,
					 sgl->lpage_dma_addr);
		sgl->lpage = शून्य;
		sgl->lpage_dma_addr = 0;
	पूर्ण
	__genwqe_मुक्त_consistent(cd, sgl->sgl_size, sgl->sgl,
				 sgl->sgl_dma_addr);

	sgl->sgl = शून्य;
	sgl->sgl_dma_addr = 0x0;
	sgl->sgl_size = 0;
	वापस rc;
पूर्ण

/**
 * genwqe_user_vmap() - Map user-space memory to भव kernel memory
 * @cd:         poपूर्णांकer to genwqe device
 * @m:          mapping params
 * @uaddr:      user भव address
 * @size:       size of memory to be mapped
 *
 * We need to think about how we could speed this up. Of course it is
 * not a good idea to करो this over and over again, like we are
 * currently करोing it. Nevertheless, I am curious where on the path
 * the perक्रमmance is spend. Most probably within the memory
 * allocation functions, but maybe also in the DMA mapping code.
 *
 * Restrictions: The maximum size of the possible mapping currently depends
 *               on the amount of memory we can get using kzalloc() क्रम the
 *               page_list and pci_alloc_consistent क्रम the sg_list.
 *               The sg_list is currently itself not scattered, which could
 *               be fixed with some efक्रमt. The page_list must be split पूर्णांकo
 *               PAGE_SIZE chunks too. All that will make the complicated
 *               code more complicated.
 *
 * Return: 0 अगर success
 */
पूर्णांक genwqe_user_vmap(काष्ठा genwqe_dev *cd, काष्ठा dma_mapping *m, व्योम *uaddr,
		     अचिन्हित दीर्घ size)
अणु
	पूर्णांक rc = -EINVAL;
	अचिन्हित दीर्घ data, offs;
	काष्ठा pci_dev *pci_dev = cd->pci_dev;

	अगर ((uaddr == शून्य) || (size == 0)) अणु
		m->size = 0;	/* mark unused and not added */
		वापस -EINVAL;
	पूर्ण
	m->u_vaddr = uaddr;
	m->size    = size;

	/* determine space needed क्रम page_list. */
	data = (अचिन्हित दीर्घ)uaddr;
	offs = offset_in_page(data);
	अगर (size > अच_दीर्घ_उच्च - PAGE_SIZE - offs) अणु
		m->size = 0;	/* mark unused and not added */
		वापस -EINVAL;
	पूर्ण
	m->nr_pages = DIV_ROUND_UP(offs + size, PAGE_SIZE);

	m->page_list = kसुस्मृति(m->nr_pages,
			       माप(काष्ठा page *) + माप(dma_addr_t),
			       GFP_KERNEL);
	अगर (!m->page_list) अणु
		dev_err(&pci_dev->dev, "err: alloc page_list failed\n");
		m->nr_pages = 0;
		m->u_vaddr = शून्य;
		m->size = 0;	/* mark unused and not added */
		वापस -ENOMEM;
	पूर्ण
	m->dma_list = (dma_addr_t *)(m->page_list + m->nr_pages);

	/* pin user pages in memory */
	rc = pin_user_pages_fast(data & PAGE_MASK, /* page aligned addr */
				 m->nr_pages,
				 m->ग_लिखो ? FOLL_WRITE : 0,	/* पढ़ोable/writable */
				 m->page_list);	/* ptrs to pages */
	अगर (rc < 0)
		जाओ fail_pin_user_pages;

	/* assumption: pin_user_pages can be समाप्तed by संकेतs. */
	अगर (rc < m->nr_pages) अणु
		unpin_user_pages_dirty_lock(m->page_list, rc, m->ग_लिखो);
		rc = -EFAULT;
		जाओ fail_pin_user_pages;
	पूर्ण

	rc = genwqe_map_pages(cd, m->page_list, m->nr_pages, m->dma_list);
	अगर (rc != 0)
		जाओ fail_मुक्त_user_pages;

	वापस 0;

 fail_मुक्त_user_pages:
	unpin_user_pages_dirty_lock(m->page_list, m->nr_pages, m->ग_लिखो);

 fail_pin_user_pages:
	kमुक्त(m->page_list);
	m->page_list = शून्य;
	m->dma_list = शून्य;
	m->nr_pages = 0;
	m->u_vaddr = शून्य;
	m->size = 0;		/* mark unused and not added */
	वापस rc;
पूर्ण

/**
 * genwqe_user_vunmap() - Unकरो mapping of user-space mem to भव kernel
 *                        memory
 * @cd:         poपूर्णांकer to genwqe device
 * @m:          mapping params
 */
पूर्णांक genwqe_user_vunmap(काष्ठा genwqe_dev *cd, काष्ठा dma_mapping *m)
अणु
	काष्ठा pci_dev *pci_dev = cd->pci_dev;

	अगर (!dma_mapping_used(m)) अणु
		dev_err(&pci_dev->dev, "[%s] err: mapping %p not used!\n",
			__func__, m);
		वापस -EINVAL;
	पूर्ण

	अगर (m->dma_list)
		genwqe_unmap_pages(cd, m->dma_list, m->nr_pages);

	अगर (m->page_list) अणु
		unpin_user_pages_dirty_lock(m->page_list, m->nr_pages,
					    m->ग_लिखो);
		kमुक्त(m->page_list);
		m->page_list = शून्य;
		m->dma_list = शून्य;
		m->nr_pages = 0;
	पूर्ण

	m->u_vaddr = शून्य;
	m->size = 0;		/* mark as unused and not added */
	वापस 0;
पूर्ण

/**
 * genwqe_card_type() - Get chip type SLU Configuration Register
 * @cd:         poपूर्णांकer to the genwqe device descriptor
 * Return: 0: Altera Stratix-IV 230
 *         1: Altera Stratix-IV 530
 *         2: Altera Stratix-V A4
 *         3: Altera Stratix-V A7
 */
u8 genwqe_card_type(काष्ठा genwqe_dev *cd)
अणु
	u64 card_type = cd->slu_unitcfg;

	वापस (u8)((card_type & IO_SLU_UNITCFG_TYPE_MASK) >> 20);
पूर्ण

/**
 * genwqe_card_reset() - Reset the card
 * @cd:         poपूर्णांकer to the genwqe device descriptor
 */
पूर्णांक genwqe_card_reset(काष्ठा genwqe_dev *cd)
अणु
	u64 softrst;
	काष्ठा pci_dev *pci_dev = cd->pci_dev;

	अगर (!genwqe_is_privileged(cd))
		वापस -ENODEV;

	/* new SL */
	__genwqe_ग_लिखोq(cd, IO_SLC_CFGREG_SOFTRESET, 0x1ull);
	msleep(1000);
	__genwqe_पढ़ोq(cd, IO_HSU_FIR_CLR);
	__genwqe_पढ़ोq(cd, IO_APP_FIR_CLR);
	__genwqe_पढ़ोq(cd, IO_SLU_FIR_CLR);

	/*
	 * Read-modअगरy-ग_लिखो to preserve the stealth bits
	 *
	 * For SL >= 039, Stealth WE bit allows removing
	 * the पढ़ो-modअगरy-wrote.
	 * r-m-w may require a mask 0x3C to aव्योम hitting hard
	 * reset again क्रम error reset (should be 0, chicken).
	 */
	softrst = __genwqe_पढ़ोq(cd, IO_SLC_CFGREG_SOFTRESET) & 0x3cull;
	__genwqe_ग_लिखोq(cd, IO_SLC_CFGREG_SOFTRESET, softrst | 0x2ull);

	/* give ERRORRESET some समय to finish */
	msleep(50);

	अगर (genwqe_need_err_masking(cd)) अणु
		dev_info(&pci_dev->dev,
			 "[%s] masking errors for old bitstreams\n", __func__);
		__genwqe_ग_लिखोq(cd, IO_SLC_MISC_DEBUG, 0x0aull);
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक genwqe_पढ़ो_softreset(काष्ठा genwqe_dev *cd)
अणु
	u64 bitstream;

	अगर (!genwqe_is_privileged(cd))
		वापस -ENODEV;

	bitstream = __genwqe_पढ़ोq(cd, IO_SLU_BITSTREAM) & 0x1;
	cd->softreset = (bitstream == 0) ? 0x8ull : 0xcull;
	वापस 0;
पूर्ण

/**
 * genwqe_set_पूर्णांकerrupt_capability() - Configure MSI capability काष्ठाure
 * @cd:         poपूर्णांकer to the device
 * @count:      number of vectors to allocate
 * Return: 0 अगर no error
 */
पूर्णांक genwqe_set_पूर्णांकerrupt_capability(काष्ठा genwqe_dev *cd, पूर्णांक count)
अणु
	पूर्णांक rc;

	rc = pci_alloc_irq_vectors(cd->pci_dev, 1, count, PCI_IRQ_MSI);
	अगर (rc < 0)
		वापस rc;
	वापस 0;
पूर्ण

/**
 * genwqe_reset_पूर्णांकerrupt_capability() - Unकरो genwqe_set_पूर्णांकerrupt_capability()
 * @cd:         poपूर्णांकer to the device
 */
व्योम genwqe_reset_पूर्णांकerrupt_capability(काष्ठा genwqe_dev *cd)
अणु
	pci_मुक्त_irq_vectors(cd->pci_dev);
पूर्ण

/**
 * set_reg_idx() - Fill array with data. Ignore illegal offsets.
 * @cd:         card device
 * @r:          debug रेजिस्टर array
 * @i:          index to desired entry
 * @m:          maximum possible entries
 * @addr:       addr which is पढ़ो
 * @idx:        index in debug array
 * @val:        पढ़ो value
 */
अटल पूर्णांक set_reg_idx(काष्ठा genwqe_dev *cd, काष्ठा genwqe_reg *r,
		       अचिन्हित पूर्णांक *i, अचिन्हित पूर्णांक m, u32 addr, u32 idx,
		       u64 val)
अणु
	अगर (WARN_ON_ONCE(*i >= m))
		वापस -EFAULT;

	r[*i].addr = addr;
	r[*i].idx = idx;
	r[*i].val = val;
	++*i;
	वापस 0;
पूर्ण

अटल पूर्णांक set_reg(काष्ठा genwqe_dev *cd, काष्ठा genwqe_reg *r,
		   अचिन्हित पूर्णांक *i, अचिन्हित पूर्णांक m, u32 addr, u64 val)
अणु
	वापस set_reg_idx(cd, r, i, m, addr, 0, val);
पूर्ण

पूर्णांक genwqe_पढ़ो_ffdc_regs(काष्ठा genwqe_dev *cd, काष्ठा genwqe_reg *regs,
			 अचिन्हित पूर्णांक max_regs, पूर्णांक all)
अणु
	अचिन्हित पूर्णांक i, j, idx = 0;
	u32 ufir_addr, ufec_addr, sfir_addr, sfec_addr;
	u64 gfir, sluid, appid, ufir, ufec, sfir, sfec;

	/* Global FIR */
	gfir = __genwqe_पढ़ोq(cd, IO_SLC_CFGREG_GFIR);
	set_reg(cd, regs, &idx, max_regs, IO_SLC_CFGREG_GFIR, gfir);

	/* UnitCfg क्रम SLU */
	sluid = __genwqe_पढ़ोq(cd, IO_SLU_UNITCFG); /* 0x00000000 */
	set_reg(cd, regs, &idx, max_regs, IO_SLU_UNITCFG, sluid);

	/* UnitCfg क्रम APP */
	appid = __genwqe_पढ़ोq(cd, IO_APP_UNITCFG); /* 0x02000000 */
	set_reg(cd, regs, &idx, max_regs, IO_APP_UNITCFG, appid);

	/* Check all chip Units */
	क्रम (i = 0; i < GENWQE_MAX_UNITS; i++) अणु

		/* Unit FIR */
		ufir_addr = (i << 24) | 0x008;
		ufir = __genwqe_पढ़ोq(cd, ufir_addr);
		set_reg(cd, regs, &idx, max_regs, ufir_addr, ufir);

		/* Unit FEC */
		ufec_addr = (i << 24) | 0x018;
		ufec = __genwqe_पढ़ोq(cd, ufec_addr);
		set_reg(cd, regs, &idx, max_regs, ufec_addr, ufec);

		क्रम (j = 0; j < 64; j++) अणु
			/* wherever there is a primary 1, पढ़ो the 2ndary */
			अगर (!all && (!(ufir & (1ull << j))))
				जारी;

			sfir_addr = (i << 24) | (0x100 + 8 * j);
			sfir = __genwqe_पढ़ोq(cd, sfir_addr);
			set_reg(cd, regs, &idx, max_regs, sfir_addr, sfir);

			sfec_addr = (i << 24) | (0x300 + 8 * j);
			sfec = __genwqe_पढ़ोq(cd, sfec_addr);
			set_reg(cd, regs, &idx, max_regs, sfec_addr, sfec);
		पूर्ण
	पूर्ण

	/* fill with invalid data until end */
	क्रम (i = idx; i < max_regs; i++) अणु
		regs[i].addr = 0xffffffff;
		regs[i].val = 0xffffffffffffffffull;
	पूर्ण
	वापस idx;
पूर्ण

/**
 * genwqe_ffdc_buff_size() - Calculates the number of dump रेजिस्टरs
 * @cd:	        genwqe device descriptor
 * @uid:	unit ID
 */
पूर्णांक genwqe_ffdc_buff_size(काष्ठा genwqe_dev *cd, पूर्णांक uid)
अणु
	पूर्णांक entries = 0, ring, traps, traces, trace_entries;
	u32 eevptr_addr, l_addr, d_len, d_type;
	u64 eevptr, val, addr;

	eevptr_addr = GENWQE_UID_OFFS(uid) | IO_EXTENDED_ERROR_POINTER;
	eevptr = __genwqe_पढ़ोq(cd, eevptr_addr);

	अगर ((eevptr != 0x0) && (eevptr != -1ull)) अणु
		l_addr = GENWQE_UID_OFFS(uid) | eevptr;

		जबतक (1) अणु
			val = __genwqe_पढ़ोq(cd, l_addr);

			अगर ((val == 0x0) || (val == -1ull))
				अवरोध;

			/* 38:24 */
			d_len  = (val & 0x0000007fff000000ull) >> 24;

			/* 39 */
			d_type = (val & 0x0000008000000000ull) >> 36;

			अगर (d_type) अणु	/* repeat */
				entries += d_len;
			पूर्ण अन्यथा अणु	/* size in bytes! */
				entries += d_len >> 3;
			पूर्ण

			l_addr += 8;
		पूर्ण
	पूर्ण

	क्रम (ring = 0; ring < 8; ring++) अणु
		addr = GENWQE_UID_OFFS(uid) | IO_EXTENDED_DIAG_MAP(ring);
		val = __genwqe_पढ़ोq(cd, addr);

		अगर ((val == 0x0ull) || (val == -1ull))
			जारी;

		traps = (val >> 24) & 0xff;
		traces = (val >> 16) & 0xff;
		trace_entries = val & 0xffff;

		entries += traps + (traces * trace_entries);
	पूर्ण
	वापस entries;
पूर्ण

/**
 * genwqe_ffdc_buff_पढ़ो() - Implements LogoutExtendedErrorRegisters procedure
 * @cd:	        genwqe device descriptor
 * @uid:	unit ID
 * @regs:       रेजिस्टर inक्रमmation
 * @max_regs:   number of रेजिस्टर entries
 */
पूर्णांक genwqe_ffdc_buff_पढ़ो(काष्ठा genwqe_dev *cd, पूर्णांक uid,
			  काष्ठा genwqe_reg *regs, अचिन्हित पूर्णांक max_regs)
अणु
	पूर्णांक i, traps, traces, trace, trace_entries, trace_entry, ring;
	अचिन्हित पूर्णांक idx = 0;
	u32 eevptr_addr, l_addr, d_addr, d_len, d_type;
	u64 eevptr, e, val, addr;

	eevptr_addr = GENWQE_UID_OFFS(uid) | IO_EXTENDED_ERROR_POINTER;
	eevptr = __genwqe_पढ़ोq(cd, eevptr_addr);

	अगर ((eevptr != 0x0) && (eevptr != 0xffffffffffffffffull)) अणु
		l_addr = GENWQE_UID_OFFS(uid) | eevptr;
		जबतक (1) अणु
			e = __genwqe_पढ़ोq(cd, l_addr);
			अगर ((e == 0x0) || (e == 0xffffffffffffffffull))
				अवरोध;

			d_addr = (e & 0x0000000000ffffffull);	    /* 23:0 */
			d_len  = (e & 0x0000007fff000000ull) >> 24; /* 38:24 */
			d_type = (e & 0x0000008000000000ull) >> 36; /* 39 */
			d_addr |= GENWQE_UID_OFFS(uid);

			अगर (d_type) अणु
				क्रम (i = 0; i < (पूर्णांक)d_len; i++) अणु
					val = __genwqe_पढ़ोq(cd, d_addr);
					set_reg_idx(cd, regs, &idx, max_regs,
						    d_addr, i, val);
				पूर्ण
			पूर्ण अन्यथा अणु
				d_len >>= 3; /* Size in bytes! */
				क्रम (i = 0; i < (पूर्णांक)d_len; i++, d_addr += 8) अणु
					val = __genwqe_पढ़ोq(cd, d_addr);
					set_reg_idx(cd, regs, &idx, max_regs,
						    d_addr, 0, val);
				पूर्ण
			पूर्ण
			l_addr += 8;
		पूर्ण
	पूर्ण

	/*
	 * To save समय, there are only 6 traces poplulated on Uid=2,
	 * Ring=1. each with iters=512.
	 */
	क्रम (ring = 0; ring < 8; ring++) अणु /* 0 is fls, 1 is fds,
					      2...7 are ASI rings */
		addr = GENWQE_UID_OFFS(uid) | IO_EXTENDED_DIAG_MAP(ring);
		val = __genwqe_पढ़ोq(cd, addr);

		अगर ((val == 0x0ull) || (val == -1ull))
			जारी;

		traps = (val >> 24) & 0xff;	/* Number of Traps	*/
		traces = (val >> 16) & 0xff;	/* Number of Traces	*/
		trace_entries = val & 0xffff;	/* Entries per trace	*/

		/* Note: This is a combined loop that dumps both the traps */
		/* (क्रम the trace == 0 हाल) as well as the traces 1 to    */
		/* 'traces'.						   */
		क्रम (trace = 0; trace <= traces; trace++) अणु
			u32 diag_sel =
				GENWQE_EXTENDED_DIAG_SELECTOR(ring, trace);

			addr = (GENWQE_UID_OFFS(uid) |
				IO_EXTENDED_DIAG_SELECTOR);
			__genwqe_ग_लिखोq(cd, addr, diag_sel);

			क्रम (trace_entry = 0;
			     trace_entry < (trace ? trace_entries : traps);
			     trace_entry++) अणु
				addr = (GENWQE_UID_OFFS(uid) |
					IO_EXTENDED_DIAG_READ_MBX);
				val = __genwqe_पढ़ोq(cd, addr);
				set_reg_idx(cd, regs, &idx, max_regs, addr,
					    (diag_sel<<16) | trace_entry, val);
			पूर्ण
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/**
 * genwqe_ग_लिखो_vreg() - Write रेजिस्टर in भव winकरोw
 * @cd:	        genwqe device descriptor
 * @reg:	रेजिस्टर (byte) offset within BAR
 * @val:	value to ग_लिखो
 * @func:	PCI भव function
 *
 * Note, these रेजिस्टरs are only accessible to the PF through the
 * VF-winकरोw. It is not पूर्णांकended क्रम the VF to access.
 */
पूर्णांक genwqe_ग_लिखो_vreg(काष्ठा genwqe_dev *cd, u32 reg, u64 val, पूर्णांक func)
अणु
	__genwqe_ग_लिखोq(cd, IO_PF_SLC_VIRTUAL_WINDOW, func & 0xf);
	__genwqe_ग_लिखोq(cd, reg, val);
	वापस 0;
पूर्ण

/**
 * genwqe_पढ़ो_vreg() - Read रेजिस्टर in भव winकरोw
 * @cd:	        genwqe device descriptor
 * @reg:	रेजिस्टर (byte) offset within BAR
 * @func:	PCI भव function
 *
 * Note, these रेजिस्टरs are only accessible to the PF through the
 * VF-winकरोw. It is not पूर्णांकended क्रम the VF to access.
 */
u64 genwqe_पढ़ो_vreg(काष्ठा genwqe_dev *cd, u32 reg, पूर्णांक func)
अणु
	__genwqe_ग_लिखोq(cd, IO_PF_SLC_VIRTUAL_WINDOW, func & 0xf);
	वापस __genwqe_पढ़ोq(cd, reg);
पूर्ण

/**
 * genwqe_base_घड़ी_frequency() - Deteremine base घड़ी frequency of the card
 * @cd:	        genwqe device descriptor
 *
 * Note: From a design perspective it turned out to be a bad idea to
 * use codes here to specअगरiy the frequency/speed values. An old
 * driver cannot understand new codes and is thereक्रमe always a
 * problem. Better is to measure out the value or put the
 * speed/frequency directly पूर्णांकo a रेजिस्टर which is always a valid
 * value क्रम old as well as क्रम new software.
 *
 * Return: Card घड़ी in MHz
 */
पूर्णांक genwqe_base_घड़ी_frequency(काष्ठा genwqe_dev *cd)
अणु
	u16 speed;		/*         MHz  MHz  MHz  MHz */
	अटल स्थिर पूर्णांक speed_grade[] = अणु 250, 200, 166, 175 पूर्ण;

	speed = (u16)((cd->slu_unitcfg >> 28) & 0x0full);
	अगर (speed >= ARRAY_SIZE(speed_grade))
		वापस 0;	/* illegal value */

	वापस speed_grade[speed];
पूर्ण

/**
 * genwqe_stop_traps() - Stop traps
 * @cd:	        genwqe device descriptor
 *
 * Beक्रमe पढ़ोing out the analysis data, we need to stop the traps.
 */
व्योम genwqe_stop_traps(काष्ठा genwqe_dev *cd)
अणु
	__genwqe_ग_लिखोq(cd, IO_SLC_MISC_DEBUG_SET, 0xcull);
पूर्ण

/**
 * genwqe_start_traps() - Start traps
 * @cd:	        genwqe device descriptor
 *
 * After having पढ़ो the data, we can/must enable the traps again.
 */
व्योम genwqe_start_traps(काष्ठा genwqe_dev *cd)
अणु
	__genwqe_ग_लिखोq(cd, IO_SLC_MISC_DEBUG_CLR, 0xcull);

	अगर (genwqe_need_err_masking(cd))
		__genwqe_ग_लिखोq(cd, IO_SLC_MISC_DEBUG, 0x0aull);
पूर्ण
