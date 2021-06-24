<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Mips Jazz DMA controller support
 * Copyright (C) 1995, 1996 by Andreas Busse
 *
 * NOTE: Some of the argument checking could be हटाओd when
 * things have settled करोwn. Also, instead of वापसing 0xffffffff
 * on failure of vdma_alloc() one could leave page #0 unused
 * and वापस the more usual शून्य poपूर्णांकer as logical address.
 */
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/export.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/mm.h>
#समावेश <linux/memblock.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/gfp.h>
#समावेश <linux/dma-map-ops.h>
#समावेश <यंत्र/mipsregs.h>
#समावेश <यंत्र/jazz.h>
#समावेश <यंत्र/पन.स>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/dma.h>
#समावेश <यंत्र/jazzdma.h>

/*
 * Set this to one to enable additional vdma debug code.
 */
#घोषणा CONF_DEBUG_VDMA 0

अटल VDMA_PGTBL_ENTRY *pgtbl;

अटल DEFINE_SPINLOCK(vdma_lock);

/*
 * Debug stuff
 */
#घोषणा vdma_debug     ((CONF_DEBUG_VDMA) ? debuglvl : 0)

अटल पूर्णांक debuglvl = 3;

/*
 * Initialize the pagetable with a one-to-one mapping of
 * the first 16 Mbytes of मुख्य memory and declare all
 * entries to be unused. Using this method will at least
 * allow some early device driver operations to work.
 */
अटल अंतरभूत व्योम vdma_pgtbl_init(व्योम)
अणु
	अचिन्हित दीर्घ paddr = 0;
	पूर्णांक i;

	क्रम (i = 0; i < VDMA_PGTBL_ENTRIES; i++) अणु
		pgtbl[i].frame = paddr;
		pgtbl[i].owner = VDMA_PAGE_EMPTY;
		paddr += VDMA_PAGESIZE;
	पूर्ण
पूर्ण

/*
 * Initialize the Jazz R4030 dma controller
 */
अटल पूर्णांक __init vdma_init(व्योम)
अणु
	/*
	 * Allocate 32k of memory क्रम DMA page tables.	This needs to be page
	 * aligned and should be uncached to aव्योम cache flushing after every
	 * update.
	 */
	pgtbl = (VDMA_PGTBL_ENTRY *)__get_मुक्त_pages(GFP_KERNEL | GFP_DMA,
						    get_order(VDMA_PGTBL_SIZE));
	BUG_ON(!pgtbl);
	dma_cache_wback_inv((अचिन्हित दीर्घ)pgtbl, VDMA_PGTBL_SIZE);
	pgtbl = (VDMA_PGTBL_ENTRY *)CKSEG1ADDR((अचिन्हित दीर्घ)pgtbl);

	/*
	 * Clear the R4030 translation table
	 */
	vdma_pgtbl_init();

	r4030_ग_लिखो_reg32(JAZZ_R4030_TRSTBL_BASE,
			  CPHYSADDR((अचिन्हित दीर्घ)pgtbl));
	r4030_ग_लिखो_reg32(JAZZ_R4030_TRSTBL_LIM, VDMA_PGTBL_SIZE);
	r4030_ग_लिखो_reg32(JAZZ_R4030_TRSTBL_INV, 0);

	prपूर्णांकk(KERN_INFO "VDMA: R4030 DMA pagetables initialized.\n");
	वापस 0;
पूर्ण
arch_initcall(vdma_init);

/*
 * Allocate DMA pagetables using a simple first-fit algorithm
 */
अचिन्हित दीर्घ vdma_alloc(अचिन्हित दीर्घ paddr, अचिन्हित दीर्घ size)
अणु
	पूर्णांक first, last, pages, frame, i;
	अचिन्हित दीर्घ laddr, flags;

	/* check arguments */

	अगर (paddr > 0x1fffffff) अणु
		अगर (vdma_debug)
			prपूर्णांकk("vdma_alloc: Invalid physical address: %08lx\n",
			       paddr);
		वापस DMA_MAPPING_ERROR;	/* invalid physical address */
	पूर्ण
	अगर (size > 0x400000 || size == 0) अणु
		अगर (vdma_debug)
			prपूर्णांकk("vdma_alloc: Invalid size: %08lx\n", size);
		वापस DMA_MAPPING_ERROR;	/* invalid physical address */
	पूर्ण

	spin_lock_irqsave(&vdma_lock, flags);
	/*
	 * Find मुक्त chunk
	 */
	pages = VDMA_PAGE(paddr + size) - VDMA_PAGE(paddr) + 1;
	first = 0;
	जबतक (1) अणु
		जबतक (pgtbl[first].owner != VDMA_PAGE_EMPTY &&
		       first < VDMA_PGTBL_ENTRIES) first++;
		अगर (first + pages > VDMA_PGTBL_ENTRIES) अणु	/* nothing मुक्त */
			spin_unlock_irqrestore(&vdma_lock, flags);
			वापस DMA_MAPPING_ERROR;
		पूर्ण

		last = first + 1;
		जबतक (pgtbl[last].owner == VDMA_PAGE_EMPTY
		       && last - first < pages)
			last++;

		अगर (last - first == pages)
			अवरोध;	/* found */
		first = last + 1;
	पूर्ण

	/*
	 * Mark pages as allocated
	 */
	laddr = (first << 12) + (paddr & (VDMA_PAGESIZE - 1));
	frame = paddr & ~(VDMA_PAGESIZE - 1);

	क्रम (i = first; i < last; i++) अणु
		pgtbl[i].frame = frame;
		pgtbl[i].owner = laddr;
		frame += VDMA_PAGESIZE;
	पूर्ण

	/*
	 * Update translation table and वापस logical start address
	 */
	r4030_ग_लिखो_reg32(JAZZ_R4030_TRSTBL_INV, 0);

	अगर (vdma_debug > 1)
		prपूर्णांकk("vdma_alloc: Allocated %d pages starting from %08lx\n",
		     pages, laddr);

	अगर (vdma_debug > 2) अणु
		prपूर्णांकk("LADDR: ");
		क्रम (i = first; i < last; i++)
			prपूर्णांकk("%08x ", i << 12);
		prपूर्णांकk("\nPADDR: ");
		क्रम (i = first; i < last; i++)
			prपूर्णांकk("%08x ", pgtbl[i].frame);
		prपूर्णांकk("\nOWNER: ");
		क्रम (i = first; i < last; i++)
			prपूर्णांकk("%08x ", pgtbl[i].owner);
		prपूर्णांकk("\n");
	पूर्ण

	spin_unlock_irqrestore(&vdma_lock, flags);

	वापस laddr;
पूर्ण

EXPORT_SYMBOL(vdma_alloc);

/*
 * Free previously allocated dma translation pages
 * Note that this करोes NOT change the translation table,
 * it just marks the मुक्त'd pages as unused!
 */
पूर्णांक vdma_मुक्त(अचिन्हित दीर्घ laddr)
अणु
	पूर्णांक i;

	i = laddr >> 12;

	अगर (pgtbl[i].owner != laddr) अणु
		prपूर्णांकk
		    ("vdma_free: trying to free other's dma pages, laddr=%8lx\n",
		     laddr);
		वापस -1;
	पूर्ण

	जबतक (i < VDMA_PGTBL_ENTRIES && pgtbl[i].owner == laddr) अणु
		pgtbl[i].owner = VDMA_PAGE_EMPTY;
		i++;
	पूर्ण

	अगर (vdma_debug > 1)
		prपूर्णांकk("vdma_free: freed %ld pages starting from %08lx\n",
		       i - (laddr >> 12), laddr);

	वापस 0;
पूर्ण

EXPORT_SYMBOL(vdma_मुक्त);

/*
 * Translate a physical address to a logical address.
 * This will वापस the logical address of the first
 * match.
 */
अचिन्हित दीर्घ vdma_phys2log(अचिन्हित दीर्घ paddr)
अणु
	पूर्णांक i;
	पूर्णांक frame;

	frame = paddr & ~(VDMA_PAGESIZE - 1);

	क्रम (i = 0; i < VDMA_PGTBL_ENTRIES; i++) अणु
		अगर (pgtbl[i].frame == frame)
			अवरोध;
	पूर्ण

	अगर (i == VDMA_PGTBL_ENTRIES)
		वापस ~0UL;

	वापस (i << 12) + (paddr & (VDMA_PAGESIZE - 1));
पूर्ण

EXPORT_SYMBOL(vdma_phys2log);

/*
 * Translate a logical DMA address to a physical address
 */
अचिन्हित दीर्घ vdma_log2phys(अचिन्हित दीर्घ laddr)
अणु
	वापस pgtbl[laddr >> 12].frame + (laddr & (VDMA_PAGESIZE - 1));
पूर्ण

EXPORT_SYMBOL(vdma_log2phys);

/*
 * Prपूर्णांक DMA statistics
 */
व्योम vdma_stats(व्योम)
अणु
	पूर्णांक i;

	prपूर्णांकk("vdma_stats: CONFIG: %08x\n",
	       r4030_पढ़ो_reg32(JAZZ_R4030_CONFIG));
	prपूर्णांकk("R4030 translation table base: %08x\n",
	       r4030_पढ़ो_reg32(JAZZ_R4030_TRSTBL_BASE));
	prपूर्णांकk("R4030 translation table limit: %08x\n",
	       r4030_पढ़ो_reg32(JAZZ_R4030_TRSTBL_LIM));
	prपूर्णांकk("vdma_stats: INV_ADDR: %08x\n",
	       r4030_पढ़ो_reg32(JAZZ_R4030_INV_ADDR));
	prपूर्णांकk("vdma_stats: R_FAIL_ADDR: %08x\n",
	       r4030_पढ़ो_reg32(JAZZ_R4030_R_FAIL_ADDR));
	prपूर्णांकk("vdma_stats: M_FAIL_ADDR: %08x\n",
	       r4030_पढ़ो_reg32(JAZZ_R4030_M_FAIL_ADDR));
	prपूर्णांकk("vdma_stats: IRQ_SOURCE: %08x\n",
	       r4030_पढ़ो_reg32(JAZZ_R4030_IRQ_SOURCE));
	prपूर्णांकk("vdma_stats: I386_ERROR: %08x\n",
	       r4030_पढ़ो_reg32(JAZZ_R4030_I386_ERROR));
	prपूर्णांकk("vdma_chnl_modes:   ");
	क्रम (i = 0; i < 8; i++)
		prपूर्णांकk("%04x ",
		       (अचिन्हित) r4030_पढ़ो_reg32(JAZZ_R4030_CHNL_MODE +
						   (i << 5)));
	prपूर्णांकk("\n");
	prपूर्णांकk("vdma_chnl_enables: ");
	क्रम (i = 0; i < 8; i++)
		prपूर्णांकk("%04x ",
		       (अचिन्हित) r4030_पढ़ो_reg32(JAZZ_R4030_CHNL_ENABLE +
						   (i << 5)));
	prपूर्णांकk("\n");
पूर्ण

/*
 * DMA transfer functions
 */

/*
 * Enable a DMA channel. Also clear any error conditions.
 */
व्योम vdma_enable(पूर्णांक channel)
अणु
	पूर्णांक status;

	अगर (vdma_debug)
		prपूर्णांकk("vdma_enable: channel %d\n", channel);

	/*
	 * Check error conditions first
	 */
	status = r4030_पढ़ो_reg32(JAZZ_R4030_CHNL_ENABLE + (channel << 5));
	अगर (status & 0x400)
		prपूर्णांकk("VDMA: Channel %d: Address error!\n", channel);
	अगर (status & 0x200)
		prपूर्णांकk("VDMA: Channel %d: Memory error!\n", channel);

	/*
	 * Clear all पूर्णांकerrupt flags
	 */
	r4030_ग_लिखो_reg32(JAZZ_R4030_CHNL_ENABLE + (channel << 5),
			  r4030_पढ़ो_reg32(JAZZ_R4030_CHNL_ENABLE +
					   (channel << 5)) | R4030_TC_INTR
			  | R4030_MEM_INTR | R4030_ADDR_INTR);

	/*
	 * Enable the desired channel
	 */
	r4030_ग_लिखो_reg32(JAZZ_R4030_CHNL_ENABLE + (channel << 5),
			  r4030_पढ़ो_reg32(JAZZ_R4030_CHNL_ENABLE +
					   (channel << 5)) |
			  R4030_CHNL_ENABLE);
पूर्ण

EXPORT_SYMBOL(vdma_enable);

/*
 * Disable a DMA channel
 */
व्योम vdma_disable(पूर्णांक channel)
अणु
	अगर (vdma_debug) अणु
		पूर्णांक status =
		    r4030_पढ़ो_reg32(JAZZ_R4030_CHNL_ENABLE +
				     (channel << 5));

		prपूर्णांकk("vdma_disable: channel %d\n", channel);
		prपूर्णांकk("VDMA: channel %d status: %04x (%s) mode: "
		       "%02x addr: %06x count: %06x\n",
		       channel, status,
		       ((status & 0x600) ? "ERROR" : "OK"),
		       (अचिन्हित) r4030_पढ़ो_reg32(JAZZ_R4030_CHNL_MODE +
						   (channel << 5)),
		       (अचिन्हित) r4030_पढ़ो_reg32(JAZZ_R4030_CHNL_ADDR +
						   (channel << 5)),
		       (अचिन्हित) r4030_पढ़ो_reg32(JAZZ_R4030_CHNL_COUNT +
						   (channel << 5)));
	पूर्ण

	r4030_ग_लिखो_reg32(JAZZ_R4030_CHNL_ENABLE + (channel << 5),
			  r4030_पढ़ो_reg32(JAZZ_R4030_CHNL_ENABLE +
					   (channel << 5)) &
			  ~R4030_CHNL_ENABLE);

	/*
	 * After disabling a DMA channel a remote bus रेजिस्टर should be
	 * पढ़ो to ensure that the current DMA acknowledge cycle is completed.
	 */
	*((अस्थिर अचिन्हित पूर्णांक *) JAZZ_DUMMY_DEVICE);
पूर्ण

EXPORT_SYMBOL(vdma_disable);

/*
 * Set DMA mode. This function accepts the mode values used
 * to set a PC-style DMA controller. For the SCSI and FDC
 * channels, we also set the शेष modes each समय we're
 * called.
 * NOTE: The FAST and BURST dma modes are supported by the
 * R4030 Rev. 2 and PICA chipsets only. I leave them disabled
 * क्रम now.
 */
व्योम vdma_set_mode(पूर्णांक channel, पूर्णांक mode)
अणु
	अगर (vdma_debug)
		prपूर्णांकk("vdma_set_mode: channel %d, mode 0x%x\n", channel,
		       mode);

	चयन (channel) अणु
	हाल JAZZ_SCSI_DMA:	/* scsi */
		r4030_ग_लिखो_reg32(JAZZ_R4030_CHNL_MODE + (channel << 5),
/*			  R4030_MODE_FAST | */
/*			  R4030_MODE_BURST | */
				  R4030_MODE_INTR_EN |
				  R4030_MODE_WIDTH_16 |
				  R4030_MODE_ATIME_80);
		अवरोध;

	हाल JAZZ_FLOPPY_DMA:	/* floppy */
		r4030_ग_लिखो_reg32(JAZZ_R4030_CHNL_MODE + (channel << 5),
/*			  R4030_MODE_FAST | */
/*			  R4030_MODE_BURST | */
				  R4030_MODE_INTR_EN |
				  R4030_MODE_WIDTH_8 |
				  R4030_MODE_ATIME_120);
		अवरोध;

	हाल JAZZ_AUDIOL_DMA:
	हाल JAZZ_AUDIOR_DMA:
		prपूर्णांकk("VDMA: Audio DMA not supported yet.\n");
		अवरोध;

	शेष:
		prपूर्णांकk
		    ("VDMA: vdma_set_mode() called with unsupported channel %d!\n",
		     channel);
	पूर्ण

	चयन (mode) अणु
	हाल DMA_MODE_READ:
		r4030_ग_लिखो_reg32(JAZZ_R4030_CHNL_ENABLE + (channel << 5),
				  r4030_पढ़ो_reg32(JAZZ_R4030_CHNL_ENABLE +
						   (channel << 5)) &
				  ~R4030_CHNL_WRITE);
		अवरोध;

	हाल DMA_MODE_WRITE:
		r4030_ग_लिखो_reg32(JAZZ_R4030_CHNL_ENABLE + (channel << 5),
				  r4030_पढ़ो_reg32(JAZZ_R4030_CHNL_ENABLE +
						   (channel << 5)) |
				  R4030_CHNL_WRITE);
		अवरोध;

	शेष:
		prपूर्णांकk
		    ("VDMA: vdma_set_mode() called with unknown dma mode 0x%x\n",
		     mode);
	पूर्ण
पूर्ण

EXPORT_SYMBOL(vdma_set_mode);

/*
 * Set Transfer Address
 */
व्योम vdma_set_addr(पूर्णांक channel, दीर्घ addr)
अणु
	अगर (vdma_debug)
		prपूर्णांकk("vdma_set_addr: channel %d, addr %lx\n", channel,
		       addr);

	r4030_ग_लिखो_reg32(JAZZ_R4030_CHNL_ADDR + (channel << 5), addr);
पूर्ण

EXPORT_SYMBOL(vdma_set_addr);

/*
 * Set Transfer Count
 */
व्योम vdma_set_count(पूर्णांक channel, पूर्णांक count)
अणु
	अगर (vdma_debug)
		prपूर्णांकk("vdma_set_count: channel %d, count %08x\n", channel,
		       (अचिन्हित) count);

	r4030_ग_लिखो_reg32(JAZZ_R4030_CHNL_COUNT + (channel << 5), count);
पूर्ण

EXPORT_SYMBOL(vdma_set_count);

/*
 * Get Residual
 */
पूर्णांक vdma_get_residue(पूर्णांक channel)
अणु
	पूर्णांक residual;

	residual = r4030_पढ़ो_reg32(JAZZ_R4030_CHNL_COUNT + (channel << 5));

	अगर (vdma_debug)
		prपूर्णांकk("vdma_get_residual: channel %d: residual=%d\n",
		       channel, residual);

	वापस residual;
पूर्ण

/*
 * Get DMA channel enable रेजिस्टर
 */
पूर्णांक vdma_get_enable(पूर्णांक channel)
अणु
	पूर्णांक enable;

	enable = r4030_पढ़ो_reg32(JAZZ_R4030_CHNL_ENABLE + (channel << 5));

	अगर (vdma_debug)
		prपूर्णांकk("vdma_get_enable: channel %d: enable=%d\n", channel,
		       enable);

	वापस enable;
पूर्ण

अटल व्योम *jazz_dma_alloc(काष्ठा device *dev, माप_प्रकार size,
		dma_addr_t *dma_handle, gfp_t gfp, अचिन्हित दीर्घ attrs)
अणु
	काष्ठा page *page;
	व्योम *ret;

	अगर (attrs & DMA_ATTR_NO_WARN)
		gfp |= __GFP_NOWARN;

	size = PAGE_ALIGN(size);
	page = alloc_pages(gfp, get_order(size));
	अगर (!page)
		वापस शून्य;
	ret = page_address(page);
	स_रखो(ret, 0, size);
	*dma_handle = vdma_alloc(virt_to_phys(ret), size);
	अगर (*dma_handle == DMA_MAPPING_ERROR)
		जाओ out_मुक्त_pages;
	arch_dma_prep_coherent(page, size);
	वापस (व्योम *)(UNCAC_BASE + __pa(ret));

out_मुक्त_pages:
	__मुक्त_pages(page, get_order(size));
	वापस शून्य;
पूर्ण

अटल व्योम jazz_dma_मुक्त(काष्ठा device *dev, माप_प्रकार size, व्योम *vaddr,
		dma_addr_t dma_handle, अचिन्हित दीर्घ attrs)
अणु
	vdma_मुक्त(dma_handle);
	__मुक्त_pages(virt_to_page(vaddr), get_order(size));
पूर्ण

अटल dma_addr_t jazz_dma_map_page(काष्ठा device *dev, काष्ठा page *page,
		अचिन्हित दीर्घ offset, माप_प्रकार size, क्रमागत dma_data_direction dir,
		अचिन्हित दीर्घ attrs)
अणु
	phys_addr_t phys = page_to_phys(page) + offset;

	अगर (!(attrs & DMA_ATTR_SKIP_CPU_SYNC))
		arch_sync_dma_क्रम_device(phys, size, dir);
	वापस vdma_alloc(phys, size);
पूर्ण

अटल व्योम jazz_dma_unmap_page(काष्ठा device *dev, dma_addr_t dma_addr,
		माप_प्रकार size, क्रमागत dma_data_direction dir, अचिन्हित दीर्घ attrs)
अणु
	अगर (!(attrs & DMA_ATTR_SKIP_CPU_SYNC))
		arch_sync_dma_क्रम_cpu(vdma_log2phys(dma_addr), size, dir);
	vdma_मुक्त(dma_addr);
पूर्ण

अटल पूर्णांक jazz_dma_map_sg(काष्ठा device *dev, काष्ठा scatterlist *sglist,
		पूर्णांक nents, क्रमागत dma_data_direction dir, अचिन्हित दीर्घ attrs)
अणु
	पूर्णांक i;
	काष्ठा scatterlist *sg;

	क्रम_each_sg(sglist, sg, nents, i) अणु
		अगर (!(attrs & DMA_ATTR_SKIP_CPU_SYNC))
			arch_sync_dma_क्रम_device(sg_phys(sg), sg->length,
				dir);
		sg->dma_address = vdma_alloc(sg_phys(sg), sg->length);
		अगर (sg->dma_address == DMA_MAPPING_ERROR)
			वापस 0;
		sg_dma_len(sg) = sg->length;
	पूर्ण

	वापस nents;
पूर्ण

अटल व्योम jazz_dma_unmap_sg(काष्ठा device *dev, काष्ठा scatterlist *sglist,
		पूर्णांक nents, क्रमागत dma_data_direction dir, अचिन्हित दीर्घ attrs)
अणु
	पूर्णांक i;
	काष्ठा scatterlist *sg;

	क्रम_each_sg(sglist, sg, nents, i) अणु
		अगर (!(attrs & DMA_ATTR_SKIP_CPU_SYNC))
			arch_sync_dma_क्रम_cpu(sg_phys(sg), sg->length, dir);
		vdma_मुक्त(sg->dma_address);
	पूर्ण
पूर्ण

अटल व्योम jazz_dma_sync_single_क्रम_device(काष्ठा device *dev,
		dma_addr_t addr, माप_प्रकार size, क्रमागत dma_data_direction dir)
अणु
	arch_sync_dma_क्रम_device(vdma_log2phys(addr), size, dir);
पूर्ण

अटल व्योम jazz_dma_sync_single_क्रम_cpu(काष्ठा device *dev,
		dma_addr_t addr, माप_प्रकार size, क्रमागत dma_data_direction dir)
अणु
	arch_sync_dma_क्रम_cpu(vdma_log2phys(addr), size, dir);
पूर्ण

अटल व्योम jazz_dma_sync_sg_क्रम_device(काष्ठा device *dev,
		काष्ठा scatterlist *sgl, पूर्णांक nents, क्रमागत dma_data_direction dir)
अणु
	काष्ठा scatterlist *sg;
	पूर्णांक i;

	क्रम_each_sg(sgl, sg, nents, i)
		arch_sync_dma_क्रम_device(sg_phys(sg), sg->length, dir);
पूर्ण

अटल व्योम jazz_dma_sync_sg_क्रम_cpu(काष्ठा device *dev,
		काष्ठा scatterlist *sgl, पूर्णांक nents, क्रमागत dma_data_direction dir)
अणु
	काष्ठा scatterlist *sg;
	पूर्णांक i;

	क्रम_each_sg(sgl, sg, nents, i)
		arch_sync_dma_क्रम_cpu(sg_phys(sg), sg->length, dir);
पूर्ण

स्थिर काष्ठा dma_map_ops jazz_dma_ops = अणु
	.alloc			= jazz_dma_alloc,
	.मुक्त			= jazz_dma_मुक्त,
	.map_page		= jazz_dma_map_page,
	.unmap_page		= jazz_dma_unmap_page,
	.map_sg			= jazz_dma_map_sg,
	.unmap_sg		= jazz_dma_unmap_sg,
	.sync_single_क्रम_cpu	= jazz_dma_sync_single_क्रम_cpu,
	.sync_single_क्रम_device	= jazz_dma_sync_single_क्रम_device,
	.sync_sg_क्रम_cpu	= jazz_dma_sync_sg_क्रम_cpu,
	.sync_sg_क्रम_device	= jazz_dma_sync_sg_क्रम_device,
	.mmap			= dma_common_mmap,
	.get_sgtable		= dma_common_get_sgtable,
	.alloc_pages		= dma_common_alloc_pages,
	.मुक्त_pages		= dma_common_मुक्त_pages,
पूर्ण;
EXPORT_SYMBOL(jazz_dma_ops);
