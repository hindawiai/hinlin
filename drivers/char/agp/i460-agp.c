<शैली गुरु>
/*
 * For करोcumentation on the i460 AGP पूर्णांकerface, see Chapter 7 (AGP Subप्रणाली) of
 * the "Intel 460GTX Chipset Software Developer's Manual":
 * http://www.पूर्णांकel.com/design/archives/itanium/करोwnloads/248704.hपंचांग 
 */
/*
 * 460GX support by Chris Ahna <christopher.j.ahna@पूर्णांकel.com>
 * Clean up & simplअगरication by David Mosberger-Tang <davidm@hpl.hp.com>
 */
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/init.h>
#समावेश <linux/माला.स>
#समावेश <linux/slab.h>
#समावेश <linux/agp_backend.h>
#समावेश <linux/log2.h>

#समावेश "agp.h"

#घोषणा INTEL_I460_BAPBASE		0x98
#घोषणा INTEL_I460_GXBCTL		0xa0
#घोषणा INTEL_I460_AGPSIZ		0xa2
#घोषणा INTEL_I460_ATTBASE		0xfe200000
#घोषणा INTEL_I460_GATT_VALID		(1UL << 24)
#घोषणा INTEL_I460_GATT_COHERENT	(1UL << 25)

/*
 * The i460 can operate with large (4MB) pages, but there is no sane way to support this
 * within the current kernel/DRM environment, so we disable the relevant code क्रम now.
 * See also comments in ia64_alloc_page()...
 */
#घोषणा I460_LARGE_IO_PAGES		0

#अगर I460_LARGE_IO_PAGES
# define I460_IO_PAGE_SHIFT		i460.io_page_shअगरt
#अन्यथा
# define I460_IO_PAGE_SHIFT		12
#पूर्ण_अगर

#घोषणा I460_IOPAGES_PER_KPAGE		(PAGE_SIZE >> I460_IO_PAGE_SHIFT)
#घोषणा I460_KPAGES_PER_IOPAGE		(1 << (I460_IO_PAGE_SHIFT - PAGE_SHIFT))
#घोषणा I460_SRAM_IO_DISABLE		(1 << 4)
#घोषणा I460_BAPBASE_ENABLE		(1 << 3)
#घोषणा I460_AGPSIZ_MASK		0x7
#घोषणा I460_4M_PS			(1 << 1)

/* Control bits क्रम Out-Of-GART coherency and Burst Write Combining */
#घोषणा I460_GXBCTL_OOG		(1UL << 0)
#घोषणा I460_GXBCTL_BWC		(1UL << 2)

/*
 * gatt_table entries are 32-bits wide on the i460; the generic code ought to declare the
 * gatt_table and gatt_table_real poपूर्णांकers a "void *"...
 */
#घोषणा RD_GATT(index)		पढ़ोl((u32 *) i460.gatt + (index))
#घोषणा WR_GATT(index, val)	ग_लिखोl((val), (u32 *) i460.gatt + (index))
/*
 * The 460 spec says we have to पढ़ो the last location written to make sure that all
 * ग_लिखोs have taken effect
 */
#घोषणा WR_FLUSH_GATT(index)	RD_GATT(index)

अटल अचिन्हित दीर्घ i460_mask_memory (काष्ठा agp_bridge_data *bridge,
				       dma_addr_t addr, पूर्णांक type);

अटल काष्ठा अणु
	व्योम *gatt;				/* ioremap'd GATT area */

	/* i460 supports multiple GART page sizes, so GART pageshअगरt is dynamic: */
	u8 io_page_shअगरt;

	/* BIOS configures chipset to one of 2 possible apbase values: */
	u8 dynamic_apbase;

	/* काष्ठाure क्रम tracking partial use of 4MB GART pages: */
	काष्ठा lp_desc अणु
		अचिन्हित दीर्घ *alloced_map;	/* biपंचांगap of kernel-pages in use */
		पूर्णांक refcount;			/* number of kernel pages using the large page */
		u64 paddr;			/* physical address of large page */
		काष्ठा page *page; 		/* page poपूर्णांकer */
	पूर्ण *lp_desc;
पूर्ण i460;

अटल स्थिर काष्ठा aper_size_info_8 i460_sizes[3] =
अणु
	/*
	 * The 32GB aperture is only available with a 4M GART page size.  Due to the
	 * dynamic GART page size, we can't figure out page_order or num_entries until
	 * runसमय.
	 */
	अणु32768, 0, 0, 4पूर्ण,
	अणु1024, 0, 0, 2पूर्ण,
	अणु256, 0, 0, 1पूर्ण
पूर्ण;

अटल काष्ठा gatt_mask i460_masks[] =
अणु
	अणु
	  .mask = INTEL_I460_GATT_VALID | INTEL_I460_GATT_COHERENT,
	  .type = 0
	पूर्ण
पूर्ण;

अटल पूर्णांक i460_fetch_size (व्योम)
अणु
	पूर्णांक i;
	u8 temp;
	काष्ठा aper_size_info_8 *values;

	/* Determine the GART page size */
	pci_पढ़ो_config_byte(agp_bridge->dev, INTEL_I460_GXBCTL, &temp);
	i460.io_page_shअगरt = (temp & I460_4M_PS) ? 22 : 12;
	pr_debug("i460_fetch_size: io_page_shift=%d\n", i460.io_page_shअगरt);

	अगर (i460.io_page_shअगरt != I460_IO_PAGE_SHIFT) अणु
		prपूर्णांकk(KERN_ERR PFX
			"I/O (GART) page-size %luKB doesn't match expected "
				"size %luKB\n",
			1UL << (i460.io_page_shअगरt - 10),
			1UL << (I460_IO_PAGE_SHIFT));
		वापस 0;
	पूर्ण

	values = A_SIZE_8(agp_bridge->driver->aperture_sizes);

	pci_पढ़ो_config_byte(agp_bridge->dev, INTEL_I460_AGPSIZ, &temp);

	/* Exit now अगर the IO drivers क्रम the GART SRAMS are turned off */
	अगर (temp & I460_SRAM_IO_DISABLE) अणु
		prपूर्णांकk(KERN_ERR PFX "GART SRAMS disabled on 460GX chipset\n");
		prपूर्णांकk(KERN_ERR PFX "AGPGART operation not possible\n");
		वापस 0;
	पूर्ण

	/* Make sure we करोn't try to create an 2 ^ 23 entry GATT */
	अगर ((i460.io_page_shअगरt == 0) && ((temp & I460_AGPSIZ_MASK) == 4)) अणु
		prपूर्णांकk(KERN_ERR PFX "We can't have a 32GB aperture with 4KB GART pages\n");
		वापस 0;
	पूर्ण

	/* Determine the proper APBASE रेजिस्टर */
	अगर (temp & I460_BAPBASE_ENABLE)
		i460.dynamic_apbase = INTEL_I460_BAPBASE;
	अन्यथा
		i460.dynamic_apbase = AGP_APBASE;

	क्रम (i = 0; i < agp_bridge->driver->num_aperture_sizes; i++) अणु
		/*
		 * Dynamically calculate the proper num_entries and page_order values क्रम
		 * the define aperture sizes. Take care not to shअगरt off the end of
		 * values[i].size.
		 */
		values[i].num_entries = (values[i].size << 8) >> (I460_IO_PAGE_SHIFT - 12);
		values[i].page_order = ilog2((माप(u32)*values[i].num_entries) >> PAGE_SHIFT);
	पूर्ण

	क्रम (i = 0; i < agp_bridge->driver->num_aperture_sizes; i++) अणु
		/* Neglect control bits when matching up size_value */
		अगर ((temp & I460_AGPSIZ_MASK) == values[i].size_value) अणु
			agp_bridge->previous_size = agp_bridge->current_size = (व्योम *) (values + i);
			agp_bridge->aperture_size_idx = i;
			वापस values[i].size;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/* There isn't anything to करो here since 460 has no GART TLB. */
अटल व्योम i460_tlb_flush (काष्ठा agp_memory *mem)
अणु
	वापस;
पूर्ण

/*
 * This utility function is needed to prevent corruption of the control bits
 * which are stored aदीर्घ with the aperture size in 460's AGPSIZ रेजिस्टर
 */
अटल व्योम i460_ग_लिखो_agpsiz (u8 size_value)
अणु
	u8 temp;

	pci_पढ़ो_config_byte(agp_bridge->dev, INTEL_I460_AGPSIZ, &temp);
	pci_ग_लिखो_config_byte(agp_bridge->dev, INTEL_I460_AGPSIZ,
			      ((temp & ~I460_AGPSIZ_MASK) | size_value));
पूर्ण

अटल व्योम i460_cleanup (व्योम)
अणु
	काष्ठा aper_size_info_8 *previous_size;

	previous_size = A_SIZE_8(agp_bridge->previous_size);
	i460_ग_लिखो_agpsiz(previous_size->size_value);

	अगर (I460_IO_PAGE_SHIFT > PAGE_SHIFT)
		kमुक्त(i460.lp_desc);
पूर्ण

अटल पूर्णांक i460_configure (व्योम)
अणु
	जोड़ अणु
		u32 small[2];
		u64 large;
	पूर्ण temp;
	माप_प्रकार size;
	u8 scratch;
	काष्ठा aper_size_info_8 *current_size;

	temp.large = 0;

	current_size = A_SIZE_8(agp_bridge->current_size);
	i460_ग_लिखो_agpsiz(current_size->size_value);

	/*
	 * Do the necessary rigmarole to पढ़ो all eight bytes of APBASE.
	 * This has to be करोne since the AGP aperture can be above 4GB on
	 * 460 based प्रणालीs.
	 */
	pci_पढ़ो_config_dword(agp_bridge->dev, i460.dynamic_apbase, &(temp.small[0]));
	pci_पढ़ो_config_dword(agp_bridge->dev, i460.dynamic_apbase + 4, &(temp.small[1]));

	/* Clear BAR control bits */
	agp_bridge->gart_bus_addr = temp.large & ~((1UL << 3) - 1);

	pci_पढ़ो_config_byte(agp_bridge->dev, INTEL_I460_GXBCTL, &scratch);
	pci_ग_लिखो_config_byte(agp_bridge->dev, INTEL_I460_GXBCTL,
			      (scratch & 0x02) | I460_GXBCTL_OOG | I460_GXBCTL_BWC);

	/*
	 * Initialize partial allocation trackers अगर a GART page is bigger than a kernel
	 * page.
	 */
	अगर (I460_IO_PAGE_SHIFT > PAGE_SHIFT) अणु
		size = current_size->num_entries * माप(i460.lp_desc[0]);
		i460.lp_desc = kzalloc(size, GFP_KERNEL);
		अगर (!i460.lp_desc)
			वापस -ENOMEM;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक i460_create_gatt_table (काष्ठा agp_bridge_data *bridge)
अणु
	पूर्णांक page_order, num_entries, i;
	व्योम *temp;

	/*
	 * Load up the fixed address of the GART SRAMS which hold our GATT table.
	 */
	temp = agp_bridge->current_size;
	page_order = A_SIZE_8(temp)->page_order;
	num_entries = A_SIZE_8(temp)->num_entries;

	i460.gatt = ioremap(INTEL_I460_ATTBASE, PAGE_SIZE << page_order);
	अगर (!i460.gatt) अणु
		prपूर्णांकk(KERN_ERR PFX "ioremap failed\n");
		वापस -ENOMEM;
	पूर्ण

	/* These are no good, the should be हटाओd from the agp_bridge strucure... */
	agp_bridge->gatt_table_real = शून्य;
	agp_bridge->gatt_table = शून्य;
	agp_bridge->gatt_bus_addr = 0;

	क्रम (i = 0; i < num_entries; ++i)
		WR_GATT(i, 0);
	WR_FLUSH_GATT(i - 1);
	वापस 0;
पूर्ण

अटल पूर्णांक i460_मुक्त_gatt_table (काष्ठा agp_bridge_data *bridge)
अणु
	पूर्णांक num_entries, i;
	व्योम *temp;

	temp = agp_bridge->current_size;

	num_entries = A_SIZE_8(temp)->num_entries;

	क्रम (i = 0; i < num_entries; ++i)
		WR_GATT(i, 0);
	WR_FLUSH_GATT(num_entries - 1);

	iounmap(i460.gatt);
	वापस 0;
पूर्ण

/*
 * The following functions are called when the I/O (GART) page size is smaller than
 * PAGE_SIZE.
 */

अटल पूर्णांक i460_insert_memory_small_io_page (काष्ठा agp_memory *mem,
				off_t pg_start, पूर्णांक type)
अणु
	अचिन्हित दीर्घ paddr, io_pg_start, io_page_size;
	पूर्णांक i, j, k, num_entries;
	व्योम *temp;

	pr_debug("i460_insert_memory_small_io_page(mem=%p, pg_start=%ld, type=%d, paddr0=0x%lx)\n",
		 mem, pg_start, type, page_to_phys(mem->pages[0]));

	अगर (type >= AGP_USER_TYPES || mem->type >= AGP_USER_TYPES)
		वापस -EINVAL;

	io_pg_start = I460_IOPAGES_PER_KPAGE * pg_start;

	temp = agp_bridge->current_size;
	num_entries = A_SIZE_8(temp)->num_entries;

	अगर ((io_pg_start + I460_IOPAGES_PER_KPAGE * mem->page_count) > num_entries) अणु
		prपूर्णांकk(KERN_ERR PFX "Looks like we're out of AGP memory\n");
		वापस -EINVAL;
	पूर्ण

	j = io_pg_start;
	जबतक (j < (io_pg_start + I460_IOPAGES_PER_KPAGE * mem->page_count)) अणु
		अगर (!PGE_EMPTY(agp_bridge, RD_GATT(j))) अणु
			pr_debug("i460_insert_memory_small_io_page: GATT[%d]=0x%x is busy\n",
				 j, RD_GATT(j));
			वापस -EBUSY;
		पूर्ण
		j++;
	पूर्ण

	io_page_size = 1UL << I460_IO_PAGE_SHIFT;
	क्रम (i = 0, j = io_pg_start; i < mem->page_count; i++) अणु
		paddr = page_to_phys(mem->pages[i]);
		क्रम (k = 0; k < I460_IOPAGES_PER_KPAGE; k++, j++, paddr += io_page_size)
			WR_GATT(j, i460_mask_memory(agp_bridge, paddr, mem->type));
	पूर्ण
	WR_FLUSH_GATT(j - 1);
	वापस 0;
पूर्ण

अटल पूर्णांक i460_हटाओ_memory_small_io_page(काष्ठा agp_memory *mem,
				off_t pg_start, पूर्णांक type)
अणु
	पूर्णांक i;

	pr_debug("i460_remove_memory_small_io_page(mem=%p, pg_start=%ld, type=%d)\n",
		 mem, pg_start, type);

	pg_start = I460_IOPAGES_PER_KPAGE * pg_start;

	क्रम (i = pg_start; i < (pg_start + I460_IOPAGES_PER_KPAGE * mem->page_count); i++)
		WR_GATT(i, 0);
	WR_FLUSH_GATT(i - 1);
	वापस 0;
पूर्ण

#अगर I460_LARGE_IO_PAGES

/*
 * These functions are called when the I/O (GART) page size exceeds PAGE_SIZE.
 *
 * This situation is पूर्णांकeresting since AGP memory allocations that are smaller than a
 * single GART page are possible.  The i460.lp_desc array tracks partial allocation of the
 * large GART pages to work around this issue.
 *
 * i460.lp_desc[pg_num].refcount tracks the number of kernel pages in use within GART page
 * pg_num.  i460.lp_desc[pg_num].paddr is the physical address of the large page and
 * i460.lp_desc[pg_num].alloced_map is a biपंचांगap of kernel pages that are in use (allocated).
 */

अटल पूर्णांक i460_alloc_large_page (काष्ठा lp_desc *lp)
अणु
	अचिन्हित दीर्घ order = I460_IO_PAGE_SHIFT - PAGE_SHIFT;
	माप_प्रकार map_size;

	lp->page = alloc_pages(GFP_KERNEL, order);
	अगर (!lp->page) अणु
		prपूर्णांकk(KERN_ERR PFX "Couldn't alloc 4M GART page...\n");
		वापस -ENOMEM;
	पूर्ण

	map_size = ((I460_KPAGES_PER_IOPAGE + BITS_PER_LONG - 1) & -BITS_PER_LONG)/8;
	lp->alloced_map = kzalloc(map_size, GFP_KERNEL);
	अगर (!lp->alloced_map) अणु
		__मुक्त_pages(lp->page, order);
		prपूर्णांकk(KERN_ERR PFX "Out of memory, we're in trouble...\n");
		वापस -ENOMEM;
	पूर्ण

	lp->paddr = page_to_phys(lp->page);
	lp->refcount = 0;
	atomic_add(I460_KPAGES_PER_IOPAGE, &agp_bridge->current_memory_agp);
	वापस 0;
पूर्ण

अटल व्योम i460_मुक्त_large_page (काष्ठा lp_desc *lp)
अणु
	kमुक्त(lp->alloced_map);
	lp->alloced_map = शून्य;

	__मुक्त_pages(lp->page, I460_IO_PAGE_SHIFT - PAGE_SHIFT);
	atomic_sub(I460_KPAGES_PER_IOPAGE, &agp_bridge->current_memory_agp);
पूर्ण

अटल पूर्णांक i460_insert_memory_large_io_page (काष्ठा agp_memory *mem,
				off_t pg_start, पूर्णांक type)
अणु
	पूर्णांक i, start_offset, end_offset, idx, pg, num_entries;
	काष्ठा lp_desc *start, *end, *lp;
	व्योम *temp;

	अगर (type >= AGP_USER_TYPES || mem->type >= AGP_USER_TYPES)
		वापस -EINVAL;

	temp = agp_bridge->current_size;
	num_entries = A_SIZE_8(temp)->num_entries;

	/* Figure out what pg_start means in terms of our large GART pages */
	start = &i460.lp_desc[pg_start / I460_KPAGES_PER_IOPAGE];
	end = &i460.lp_desc[(pg_start + mem->page_count - 1) / I460_KPAGES_PER_IOPAGE];
	start_offset = pg_start % I460_KPAGES_PER_IOPAGE;
	end_offset = (pg_start + mem->page_count - 1) % I460_KPAGES_PER_IOPAGE;

	अगर (end > i460.lp_desc + num_entries) अणु
		prपूर्णांकk(KERN_ERR PFX "Looks like we're out of AGP memory\n");
		वापस -EINVAL;
	पूर्ण

	/* Check अगर the requested region of the aperture is मुक्त */
	क्रम (lp = start; lp <= end; ++lp) अणु
		अगर (!lp->alloced_map)
			जारी;	/* OK, the entire large page is available... */

		क्रम (idx = ((lp == start) ? start_offset : 0);
		     idx < ((lp == end) ? (end_offset + 1) : I460_KPAGES_PER_IOPAGE);
		     idx++)
		अणु
			अगर (test_bit(idx, lp->alloced_map))
				वापस -EBUSY;
		पूर्ण
	पूर्ण

	क्रम (lp = start, i = 0; lp <= end; ++lp) अणु
		अगर (!lp->alloced_map) अणु
			/* Allocate new GART pages... */
			अगर (i460_alloc_large_page(lp) < 0)
				वापस -ENOMEM;
			pg = lp - i460.lp_desc;
			WR_GATT(pg, i460_mask_memory(agp_bridge,
						     lp->paddr, 0));
			WR_FLUSH_GATT(pg);
		पूर्ण

		क्रम (idx = ((lp == start) ? start_offset : 0);
		     idx < ((lp == end) ? (end_offset + 1) : I460_KPAGES_PER_IOPAGE);
		     idx++, i++)
		अणु
			mem->pages[i] = lp->page;
			__set_bit(idx, lp->alloced_map);
			++lp->refcount;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक i460_हटाओ_memory_large_io_page (काष्ठा agp_memory *mem,
				off_t pg_start, पूर्णांक type)
अणु
	पूर्णांक i, pg, start_offset, end_offset, idx, num_entries;
	काष्ठा lp_desc *start, *end, *lp;
	व्योम *temp;

	temp = agp_bridge->current_size;
	num_entries = A_SIZE_8(temp)->num_entries;

	/* Figure out what pg_start means in terms of our large GART pages */
	start = &i460.lp_desc[pg_start / I460_KPAGES_PER_IOPAGE];
	end = &i460.lp_desc[(pg_start + mem->page_count - 1) / I460_KPAGES_PER_IOPAGE];
	start_offset = pg_start % I460_KPAGES_PER_IOPAGE;
	end_offset = (pg_start + mem->page_count - 1) % I460_KPAGES_PER_IOPAGE;

	क्रम (i = 0, lp = start; lp <= end; ++lp) अणु
		क्रम (idx = ((lp == start) ? start_offset : 0);
		     idx < ((lp == end) ? (end_offset + 1) : I460_KPAGES_PER_IOPAGE);
		     idx++, i++)
		अणु
			mem->pages[i] = शून्य;
			__clear_bit(idx, lp->alloced_map);
			--lp->refcount;
		पूर्ण

		/* Free GART pages अगर they are unused */
		अगर (lp->refcount == 0) अणु
			pg = lp - i460.lp_desc;
			WR_GATT(pg, 0);
			WR_FLUSH_GATT(pg);
			i460_मुक्त_large_page(lp);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/* Wrapper routines to call the approriate अणुsmall_io_page,large_io_pageपूर्ण function */

अटल पूर्णांक i460_insert_memory (काष्ठा agp_memory *mem,
				off_t pg_start, पूर्णांक type)
अणु
	अगर (I460_IO_PAGE_SHIFT <= PAGE_SHIFT)
		वापस i460_insert_memory_small_io_page(mem, pg_start, type);
	अन्यथा
		वापस i460_insert_memory_large_io_page(mem, pg_start, type);
पूर्ण

अटल पूर्णांक i460_हटाओ_memory (काष्ठा agp_memory *mem,
				off_t pg_start, पूर्णांक type)
अणु
	अगर (I460_IO_PAGE_SHIFT <= PAGE_SHIFT)
		वापस i460_हटाओ_memory_small_io_page(mem, pg_start, type);
	अन्यथा
		वापस i460_हटाओ_memory_large_io_page(mem, pg_start, type);
पूर्ण

/*
 * If the I/O (GART) page size is bigger than the kernel page size, we करोn't want to
 * allocate memory until we know where it is to be bound in the aperture (a
 * multi-kernel-page alloc might fit inside of an alपढ़ोy allocated GART page).
 *
 * Let's just hope nobody counts on the allocated AGP memory being there beक्रमe bind समय
 * (I करोn't think current drivers करो)...
 */
अटल काष्ठा page *i460_alloc_page (काष्ठा agp_bridge_data *bridge)
अणु
	व्योम *page;

	अगर (I460_IO_PAGE_SHIFT <= PAGE_SHIFT) अणु
		page = agp_generic_alloc_page(agp_bridge);
	पूर्ण अन्यथा
		/* Returning शून्य would cause problems */
		/* AK: really dubious code. */
		page = (व्योम *)~0UL;
	वापस page;
पूर्ण

अटल व्योम i460_destroy_page (काष्ठा page *page, पूर्णांक flags)
अणु
	अगर (I460_IO_PAGE_SHIFT <= PAGE_SHIFT) अणु
		agp_generic_destroy_page(page, flags);
	पूर्ण
पूर्ण

#पूर्ण_अगर /* I460_LARGE_IO_PAGES */

अटल अचिन्हित दीर्घ i460_mask_memory (काष्ठा agp_bridge_data *bridge,
				       dma_addr_t addr, पूर्णांक type)
अणु
	/* Make sure the वापसed address is a valid GATT entry */
	वापस bridge->driver->masks[0].mask
		| (((addr & ~((1 << I460_IO_PAGE_SHIFT) - 1)) & 0xfffff000) >> 12);
पूर्ण

स्थिर काष्ठा agp_bridge_driver पूर्णांकel_i460_driver = अणु
	.owner			= THIS_MODULE,
	.aperture_sizes		= i460_sizes,
	.माप_प्रकारype		= U8_APER_SIZE,
	.num_aperture_sizes	= 3,
	.configure		= i460_configure,
	.fetch_size		= i460_fetch_size,
	.cleanup		= i460_cleanup,
	.tlb_flush		= i460_tlb_flush,
	.mask_memory		= i460_mask_memory,
	.masks			= i460_masks,
	.agp_enable		= agp_generic_enable,
	.cache_flush		= global_cache_flush,
	.create_gatt_table	= i460_create_gatt_table,
	.मुक्त_gatt_table	= i460_मुक्त_gatt_table,
#अगर I460_LARGE_IO_PAGES
	.insert_memory		= i460_insert_memory,
	.हटाओ_memory		= i460_हटाओ_memory,
	.agp_alloc_page		= i460_alloc_page,
	.agp_destroy_page	= i460_destroy_page,
#अन्यथा
	.insert_memory		= i460_insert_memory_small_io_page,
	.हटाओ_memory		= i460_हटाओ_memory_small_io_page,
	.agp_alloc_page		= agp_generic_alloc_page,
	.agp_alloc_pages	= agp_generic_alloc_pages,
	.agp_destroy_page	= agp_generic_destroy_page,
	.agp_destroy_pages	= agp_generic_destroy_pages,
#पूर्ण_अगर
	.alloc_by_type		= agp_generic_alloc_by_type,
	.मुक्त_by_type		= agp_generic_मुक्त_by_type,
	.agp_type_to_mask_type  = agp_generic_type_to_mask_type,
	.cant_use_aperture	= true,
पूर्ण;

अटल पूर्णांक agp_पूर्णांकel_i460_probe(काष्ठा pci_dev *pdev,
				स्थिर काष्ठा pci_device_id *ent)
अणु
	काष्ठा agp_bridge_data *bridge;
	u8 cap_ptr;

	cap_ptr = pci_find_capability(pdev, PCI_CAP_ID_AGP);
	अगर (!cap_ptr)
		वापस -ENODEV;

	bridge = agp_alloc_bridge();
	अगर (!bridge)
		वापस -ENOMEM;

	bridge->driver = &पूर्णांकel_i460_driver;
	bridge->dev = pdev;
	bridge->capndx = cap_ptr;

	prपूर्णांकk(KERN_INFO PFX "Detected Intel 460GX chipset\n");

	pci_set_drvdata(pdev, bridge);
	वापस agp_add_bridge(bridge);
पूर्ण

अटल व्योम agp_पूर्णांकel_i460_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा agp_bridge_data *bridge = pci_get_drvdata(pdev);

	agp_हटाओ_bridge(bridge);
	agp_put_bridge(bridge);
पूर्ण

अटल काष्ठा pci_device_id agp_पूर्णांकel_i460_pci_table[] = अणु
	अणु
	.class		= (PCI_CLASS_BRIDGE_HOST << 8),
	.class_mask	= ~0,
	.venकरोr		= PCI_VENDOR_ID_INTEL,
	.device		= PCI_DEVICE_ID_INTEL_84460GX,
	.subvenकरोr	= PCI_ANY_ID,
	.subdevice	= PCI_ANY_ID,
	पूर्ण,
	अणु पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, agp_पूर्णांकel_i460_pci_table);

अटल काष्ठा pci_driver agp_पूर्णांकel_i460_pci_driver = अणु
	.name		= "agpgart-intel-i460",
	.id_table	= agp_पूर्णांकel_i460_pci_table,
	.probe		= agp_पूर्णांकel_i460_probe,
	.हटाओ		= agp_पूर्णांकel_i460_हटाओ,
पूर्ण;

अटल पूर्णांक __init agp_पूर्णांकel_i460_init(व्योम)
अणु
	अगर (agp_off)
		वापस -EINVAL;
	वापस pci_रेजिस्टर_driver(&agp_पूर्णांकel_i460_pci_driver);
पूर्ण

अटल व्योम __निकास agp_पूर्णांकel_i460_cleanup(व्योम)
अणु
	pci_unरेजिस्टर_driver(&agp_पूर्णांकel_i460_pci_driver);
पूर्ण

module_init(agp_पूर्णांकel_i460_init);
module_निकास(agp_पूर्णांकel_i460_cleanup);

MODULE_AUTHOR("Chris Ahna <Christopher.J.Ahna@intel.com>");
MODULE_LICENSE("GPL and additional rights");
