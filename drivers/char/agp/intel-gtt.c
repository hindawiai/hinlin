<शैली गुरु>
/*
 * Intel GTT (Graphics Translation Table) routines
 *
 * Caveat: This driver implements the linux agp पूर्णांकerface, but this is far from
 * a agp driver! GTT support ended up here क्रम purely historical reasons: The
 * old userspace पूर्णांकel graphics drivers needed an पूर्णांकerface to map memory पूर्णांकo
 * the GTT. And the drm provides a शेष पूर्णांकerface क्रम graphic devices sitting
 * on an agp port. So it made sense to fake the GTT support as an agp port to
 * aव्योम having to create a new api.
 *
 * With gem this करोes not make much sense anymore, just needlessly complicates
 * the code. But as दीर्घ as the old graphics stack is still support, it's stuck
 * here.
 *
 * /fairy-tale-mode off
 */

#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/kernel.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/agp_backend.h>
#समावेश <linux/delay.h>
#समावेश <यंत्र/smp.h>
#समावेश "agp.h"
#समावेश "intel-agp.h"
#समावेश <drm/पूर्णांकel-gtt.h>
#समावेश <यंत्र/set_memory.h>

/*
 * If we have Intel graphics, we're not going to have anything other than
 * an Intel IOMMU. So make the correct use of the PCI DMA API contingent
 * on the Intel IOMMU support (CONFIG_INTEL_IOMMU).
 * Only newer chipsets need to bother with this, of course.
 */
#अगर_घोषित CONFIG_INTEL_IOMMU
#घोषणा USE_PCI_DMA_API 1
#अन्यथा
#घोषणा USE_PCI_DMA_API 0
#पूर्ण_अगर

काष्ठा पूर्णांकel_gtt_driver अणु
	अचिन्हित पूर्णांक gen : 8;
	अचिन्हित पूर्णांक is_g33 : 1;
	अचिन्हित पूर्णांक is_pineview : 1;
	अचिन्हित पूर्णांक is_ironlake : 1;
	अचिन्हित पूर्णांक has_pgtbl_enable : 1;
	अचिन्हित पूर्णांक dma_mask_size : 8;
	/* Chipset specअगरic GTT setup */
	पूर्णांक (*setup)(व्योम);
	/* This should unकरो anything करोne in ->setup() save the unmapping
	 * of the mmio रेजिस्टर file, that's करोne in the generic code. */
	व्योम (*cleanup)(व्योम);
	व्योम (*ग_लिखो_entry)(dma_addr_t addr, अचिन्हित पूर्णांक entry, अचिन्हित पूर्णांक flags);
	/* Flags is a more or less chipset specअगरic opaque value.
	 * For chipsets that need to support old ums (non-gem) code, this
	 * needs to be identical to the various supported agp memory types! */
	bool (*check_flags)(अचिन्हित पूर्णांक flags);
	व्योम (*chipset_flush)(व्योम);
पूर्ण;

अटल काष्ठा _पूर्णांकel_निजी अणु
	स्थिर काष्ठा पूर्णांकel_gtt_driver *driver;
	काष्ठा pci_dev *pcidev;	/* device one */
	काष्ठा pci_dev *bridge_dev;
	u8 __iomem *रेजिस्टरs;
	phys_addr_t gtt_phys_addr;
	u32 PGETBL_save;
	u32 __iomem *gtt;		/* I915G */
	bool clear_fake_agp; /* on first access via agp, fill with scratch */
	पूर्णांक num_dcache_entries;
	व्योम __iomem *i9xx_flush_page;
	अक्षर *i81x_gtt_table;
	काष्ठा resource अगरp_resource;
	पूर्णांक resource_valid;
	काष्ठा page *scratch_page;
	phys_addr_t scratch_page_dma;
	पूर्णांक refcount;
	/* Whether i915 needs to use the dmar apis or not. */
	अचिन्हित पूर्णांक needs_dmar : 1;
	phys_addr_t gma_bus_addr;
	/*  Size of memory reserved क्रम graphics by the BIOS */
	resource_माप_प्रकार stolen_size;
	/* Total number of gtt entries. */
	अचिन्हित पूर्णांक gtt_total_entries;
	/* Part of the gtt that is mappable by the cpu, क्रम those chips where
	 * this is not the full gtt. */
	अचिन्हित पूर्णांक gtt_mappable_entries;
पूर्ण पूर्णांकel_निजी;

#घोषणा INTEL_GTT_GEN	पूर्णांकel_निजी.driver->gen
#घोषणा IS_G33		पूर्णांकel_निजी.driver->is_g33
#घोषणा IS_PINEVIEW	पूर्णांकel_निजी.driver->is_pineview
#घोषणा IS_IRONLAKE	पूर्णांकel_निजी.driver->is_ironlake
#घोषणा HAS_PGTBL_EN	पूर्णांकel_निजी.driver->has_pgtbl_enable

#अगर IS_ENABLED(CONFIG_AGP_INTEL)
अटल पूर्णांक पूर्णांकel_gtt_map_memory(काष्ठा page **pages,
				अचिन्हित पूर्णांक num_entries,
				काष्ठा sg_table *st)
अणु
	काष्ठा scatterlist *sg;
	पूर्णांक i;

	DBG("try mapping %lu pages\n", (अचिन्हित दीर्घ)num_entries);

	अगर (sg_alloc_table(st, num_entries, GFP_KERNEL))
		जाओ err;

	क्रम_each_sg(st->sgl, sg, num_entries, i)
		sg_set_page(sg, pages[i], PAGE_SIZE, 0);

	अगर (!pci_map_sg(पूर्णांकel_निजी.pcidev,
			st->sgl, st->nents, PCI_DMA_BIसूचीECTIONAL))
		जाओ err;

	वापस 0;

err:
	sg_मुक्त_table(st);
	वापस -ENOMEM;
पूर्ण

अटल व्योम पूर्णांकel_gtt_unmap_memory(काष्ठा scatterlist *sg_list, पूर्णांक num_sg)
अणु
	काष्ठा sg_table st;
	DBG("try unmapping %lu pages\n", (अचिन्हित दीर्घ)mem->page_count);

	pci_unmap_sg(पूर्णांकel_निजी.pcidev, sg_list,
		     num_sg, PCI_DMA_BIसूचीECTIONAL);

	st.sgl = sg_list;
	st.orig_nents = st.nents = num_sg;

	sg_मुक्त_table(&st);
पूर्ण

अटल व्योम पूर्णांकel_fake_agp_enable(काष्ठा agp_bridge_data *bridge, u32 mode)
अणु
	वापस;
पूर्ण

/* Exists to support ARGB cursors */
अटल काष्ठा page *i8xx_alloc_pages(व्योम)
अणु
	काष्ठा page *page;

	page = alloc_pages(GFP_KERNEL | GFP_DMA32, 2);
	अगर (page == शून्य)
		वापस शून्य;

	अगर (set_pages_uc(page, 4) < 0) अणु
		set_pages_wb(page, 4);
		__मुक्त_pages(page, 2);
		वापस शून्य;
	पूर्ण
	atomic_inc(&agp_bridge->current_memory_agp);
	वापस page;
पूर्ण

अटल व्योम i8xx_destroy_pages(काष्ठा page *page)
अणु
	अगर (page == शून्य)
		वापस;

	set_pages_wb(page, 4);
	__मुक्त_pages(page, 2);
	atomic_dec(&agp_bridge->current_memory_agp);
पूर्ण
#पूर्ण_अगर

#घोषणा I810_GTT_ORDER 4
अटल पूर्णांक i810_setup(व्योम)
अणु
	phys_addr_t reg_addr;
	अक्षर *gtt_table;

	/* i81x करोes not pपुनः_स्मृतिate the gtt. It's always 64kb in size. */
	gtt_table = alloc_gatt_pages(I810_GTT_ORDER);
	अगर (gtt_table == शून्य)
		वापस -ENOMEM;
	पूर्णांकel_निजी.i81x_gtt_table = gtt_table;

	reg_addr = pci_resource_start(पूर्णांकel_निजी.pcidev, I810_MMADR_BAR);

	पूर्णांकel_निजी.रेजिस्टरs = ioremap(reg_addr, KB(64));
	अगर (!पूर्णांकel_निजी.रेजिस्टरs)
		वापस -ENOMEM;

	ग_लिखोl(virt_to_phys(gtt_table) | I810_PGETBL_ENABLED,
	       पूर्णांकel_निजी.रेजिस्टरs+I810_PGETBL_CTL);

	पूर्णांकel_निजी.gtt_phys_addr = reg_addr + I810_PTE_BASE;

	अगर ((पढ़ोl(पूर्णांकel_निजी.रेजिस्टरs+I810_DRAM_CTL)
		& I810_DRAM_ROW_0) == I810_DRAM_ROW_0_SDRAM) अणु
		dev_info(&पूर्णांकel_निजी.pcidev->dev,
			 "detected 4MB dedicated video ram\n");
		पूर्णांकel_निजी.num_dcache_entries = 1024;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम i810_cleanup(व्योम)
अणु
	ग_लिखोl(0, पूर्णांकel_निजी.रेजिस्टरs+I810_PGETBL_CTL);
	मुक्त_gatt_pages(पूर्णांकel_निजी.i81x_gtt_table, I810_GTT_ORDER);
पूर्ण

#अगर IS_ENABLED(CONFIG_AGP_INTEL)
अटल पूर्णांक i810_insert_dcache_entries(काष्ठा agp_memory *mem, off_t pg_start,
				      पूर्णांक type)
अणु
	पूर्णांक i;

	अगर ((pg_start + mem->page_count)
			> पूर्णांकel_निजी.num_dcache_entries)
		वापस -EINVAL;

	अगर (!mem->is_flushed)
		global_cache_flush();

	क्रम (i = pg_start; i < (pg_start + mem->page_count); i++) अणु
		dma_addr_t addr = i << PAGE_SHIFT;
		पूर्णांकel_निजी.driver->ग_लिखो_entry(addr,
						  i, type);
	पूर्ण
	wmb();

	वापस 0;
पूर्ण

/*
 * The i810/i830 requires a physical address to program its mouse
 * poपूर्णांकer पूर्णांकo hardware.
 * However the Xserver still ग_लिखोs to it through the agp aperture.
 */
अटल काष्ठा agp_memory *alloc_agpphysmem_i8xx(माप_प्रकार pg_count, पूर्णांक type)
अणु
	काष्ठा agp_memory *new;
	काष्ठा page *page;

	चयन (pg_count) अणु
	हाल 1: page = agp_bridge->driver->agp_alloc_page(agp_bridge);
		अवरोध;
	हाल 4:
		/* kludge to get 4 physical pages क्रम ARGB cursor */
		page = i8xx_alloc_pages();
		अवरोध;
	शेष:
		वापस शून्य;
	पूर्ण

	अगर (page == शून्य)
		वापस शून्य;

	new = agp_create_memory(pg_count);
	अगर (new == शून्य)
		वापस शून्य;

	new->pages[0] = page;
	अगर (pg_count == 4) अणु
		/* kludge to get 4 physical pages क्रम ARGB cursor */
		new->pages[1] = new->pages[0] + 1;
		new->pages[2] = new->pages[1] + 1;
		new->pages[3] = new->pages[2] + 1;
	पूर्ण
	new->page_count = pg_count;
	new->num_scratch_pages = pg_count;
	new->type = AGP_PHYS_MEMORY;
	new->physical = page_to_phys(new->pages[0]);
	वापस new;
पूर्ण

अटल व्योम पूर्णांकel_i810_मुक्त_by_type(काष्ठा agp_memory *curr)
अणु
	agp_मुक्त_key(curr->key);
	अगर (curr->type == AGP_PHYS_MEMORY) अणु
		अगर (curr->page_count == 4)
			i8xx_destroy_pages(curr->pages[0]);
		अन्यथा अणु
			agp_bridge->driver->agp_destroy_page(curr->pages[0],
							     AGP_PAGE_DESTROY_UNMAP);
			agp_bridge->driver->agp_destroy_page(curr->pages[0],
							     AGP_PAGE_DESTROY_FREE);
		पूर्ण
		agp_मुक्त_page_array(curr);
	पूर्ण
	kमुक्त(curr);
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक पूर्णांकel_gtt_setup_scratch_page(व्योम)
अणु
	काष्ठा page *page;
	dma_addr_t dma_addr;

	page = alloc_page(GFP_KERNEL | GFP_DMA32 | __GFP_ZERO);
	अगर (page == शून्य)
		वापस -ENOMEM;
	set_pages_uc(page, 1);

	अगर (पूर्णांकel_निजी.needs_dmar) अणु
		dma_addr = pci_map_page(पूर्णांकel_निजी.pcidev, page, 0,
				    PAGE_SIZE, PCI_DMA_BIसूचीECTIONAL);
		अगर (pci_dma_mapping_error(पूर्णांकel_निजी.pcidev, dma_addr)) अणु
			__मुक्त_page(page);
			वापस -EINVAL;
		पूर्ण

		पूर्णांकel_निजी.scratch_page_dma = dma_addr;
	पूर्ण अन्यथा
		पूर्णांकel_निजी.scratch_page_dma = page_to_phys(page);

	पूर्णांकel_निजी.scratch_page = page;

	वापस 0;
पूर्ण

अटल व्योम i810_ग_लिखो_entry(dma_addr_t addr, अचिन्हित पूर्णांक entry,
			     अचिन्हित पूर्णांक flags)
अणु
	u32 pte_flags = I810_PTE_VALID;

	चयन (flags) अणु
	हाल AGP_DCACHE_MEMORY:
		pte_flags |= I810_PTE_LOCAL;
		अवरोध;
	हाल AGP_USER_CACHED_MEMORY:
		pte_flags |= I830_PTE_SYSTEM_CACHED;
		अवरोध;
	पूर्ण

	ग_लिखोl_relaxed(addr | pte_flags, पूर्णांकel_निजी.gtt + entry);
पूर्ण

अटल resource_माप_प्रकार पूर्णांकel_gtt_stolen_size(व्योम)
अणु
	u16 gmch_ctrl;
	u8 rdct;
	पूर्णांक local = 0;
	अटल स्थिर पूर्णांक ddt[4] = अणु 0, 16, 32, 64 पूर्ण;
	resource_माप_प्रकार stolen_size = 0;

	अगर (INTEL_GTT_GEN == 1)
		वापस 0; /* no stolen mem on i81x */

	pci_पढ़ो_config_word(पूर्णांकel_निजी.bridge_dev,
			     I830_GMCH_CTRL, &gmch_ctrl);

	अगर (पूर्णांकel_निजी.bridge_dev->device == PCI_DEVICE_ID_INTEL_82830_HB ||
	    पूर्णांकel_निजी.bridge_dev->device == PCI_DEVICE_ID_INTEL_82845G_HB) अणु
		चयन (gmch_ctrl & I830_GMCH_GMS_MASK) अणु
		हाल I830_GMCH_GMS_STOLEN_512:
			stolen_size = KB(512);
			अवरोध;
		हाल I830_GMCH_GMS_STOLEN_1024:
			stolen_size = MB(1);
			अवरोध;
		हाल I830_GMCH_GMS_STOLEN_8192:
			stolen_size = MB(8);
			अवरोध;
		हाल I830_GMCH_GMS_LOCAL:
			rdct = पढ़ोb(पूर्णांकel_निजी.रेजिस्टरs+I830_RDRAM_CHANNEL_TYPE);
			stolen_size = (I830_RDRAM_ND(rdct) + 1) *
					MB(ddt[I830_RDRAM_DDT(rdct)]);
			local = 1;
			अवरोध;
		शेष:
			stolen_size = 0;
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		चयन (gmch_ctrl & I855_GMCH_GMS_MASK) अणु
		हाल I855_GMCH_GMS_STOLEN_1M:
			stolen_size = MB(1);
			अवरोध;
		हाल I855_GMCH_GMS_STOLEN_4M:
			stolen_size = MB(4);
			अवरोध;
		हाल I855_GMCH_GMS_STOLEN_8M:
			stolen_size = MB(8);
			अवरोध;
		हाल I855_GMCH_GMS_STOLEN_16M:
			stolen_size = MB(16);
			अवरोध;
		हाल I855_GMCH_GMS_STOLEN_32M:
			stolen_size = MB(32);
			अवरोध;
		हाल I915_GMCH_GMS_STOLEN_48M:
			stolen_size = MB(48);
			अवरोध;
		हाल I915_GMCH_GMS_STOLEN_64M:
			stolen_size = MB(64);
			अवरोध;
		हाल G33_GMCH_GMS_STOLEN_128M:
			stolen_size = MB(128);
			अवरोध;
		हाल G33_GMCH_GMS_STOLEN_256M:
			stolen_size = MB(256);
			अवरोध;
		हाल INTEL_GMCH_GMS_STOLEN_96M:
			stolen_size = MB(96);
			अवरोध;
		हाल INTEL_GMCH_GMS_STOLEN_160M:
			stolen_size = MB(160);
			अवरोध;
		हाल INTEL_GMCH_GMS_STOLEN_224M:
			stolen_size = MB(224);
			अवरोध;
		हाल INTEL_GMCH_GMS_STOLEN_352M:
			stolen_size = MB(352);
			अवरोध;
		शेष:
			stolen_size = 0;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (stolen_size > 0) अणु
		dev_info(&पूर्णांकel_निजी.bridge_dev->dev, "detected %lluK %s memory\n",
		       (u64)stolen_size / KB(1), local ? "local" : "stolen");
	पूर्ण अन्यथा अणु
		dev_info(&पूर्णांकel_निजी.bridge_dev->dev,
		       "no pre-allocated video memory detected\n");
		stolen_size = 0;
	पूर्ण

	वापस stolen_size;
पूर्ण

अटल व्योम i965_adjust_pgetbl_size(अचिन्हित पूर्णांक size_flag)
अणु
	u32 pgetbl_ctl, pgetbl_ctl2;

	/* ensure that ppgtt is disabled */
	pgetbl_ctl2 = पढ़ोl(पूर्णांकel_निजी.रेजिस्टरs+I965_PGETBL_CTL2);
	pgetbl_ctl2 &= ~I810_PGETBL_ENABLED;
	ग_लिखोl(pgetbl_ctl2, पूर्णांकel_निजी.रेजिस्टरs+I965_PGETBL_CTL2);

	/* ग_लिखो the new ggtt size */
	pgetbl_ctl = पढ़ोl(पूर्णांकel_निजी.रेजिस्टरs+I810_PGETBL_CTL);
	pgetbl_ctl &= ~I965_PGETBL_SIZE_MASK;
	pgetbl_ctl |= size_flag;
	ग_लिखोl(pgetbl_ctl, पूर्णांकel_निजी.रेजिस्टरs+I810_PGETBL_CTL);
पूर्ण

अटल अचिन्हित पूर्णांक i965_gtt_total_entries(व्योम)
अणु
	पूर्णांक size;
	u32 pgetbl_ctl;
	u16 gmch_ctl;

	pci_पढ़ो_config_word(पूर्णांकel_निजी.bridge_dev,
			     I830_GMCH_CTRL, &gmch_ctl);

	अगर (INTEL_GTT_GEN == 5) अणु
		चयन (gmch_ctl & G4x_GMCH_SIZE_MASK) अणु
		हाल G4x_GMCH_SIZE_1M:
		हाल G4x_GMCH_SIZE_VT_1M:
			i965_adjust_pgetbl_size(I965_PGETBL_SIZE_1MB);
			अवरोध;
		हाल G4x_GMCH_SIZE_VT_1_5M:
			i965_adjust_pgetbl_size(I965_PGETBL_SIZE_1_5MB);
			अवरोध;
		हाल G4x_GMCH_SIZE_2M:
		हाल G4x_GMCH_SIZE_VT_2M:
			i965_adjust_pgetbl_size(I965_PGETBL_SIZE_2MB);
			अवरोध;
		पूर्ण
	पूर्ण

	pgetbl_ctl = पढ़ोl(पूर्णांकel_निजी.रेजिस्टरs+I810_PGETBL_CTL);

	चयन (pgetbl_ctl & I965_PGETBL_SIZE_MASK) अणु
	हाल I965_PGETBL_SIZE_128KB:
		size = KB(128);
		अवरोध;
	हाल I965_PGETBL_SIZE_256KB:
		size = KB(256);
		अवरोध;
	हाल I965_PGETBL_SIZE_512KB:
		size = KB(512);
		अवरोध;
	/* GTT pagetable sizes bigger than 512KB are not possible on G33! */
	हाल I965_PGETBL_SIZE_1MB:
		size = KB(1024);
		अवरोध;
	हाल I965_PGETBL_SIZE_2MB:
		size = KB(2048);
		अवरोध;
	हाल I965_PGETBL_SIZE_1_5MB:
		size = KB(1024 + 512);
		अवरोध;
	शेष:
		dev_info(&पूर्णांकel_निजी.pcidev->dev,
			 "unknown page table size, assuming 512KB\n");
		size = KB(512);
	पूर्ण

	वापस size/4;
पूर्ण

अटल अचिन्हित पूर्णांक पूर्णांकel_gtt_total_entries(व्योम)
अणु
	अगर (IS_G33 || INTEL_GTT_GEN == 4 || INTEL_GTT_GEN == 5)
		वापस i965_gtt_total_entries();
	अन्यथा अणु
		/* On previous hardware, the GTT size was just what was
		 * required to map the aperture.
		 */
		वापस पूर्णांकel_निजी.gtt_mappable_entries;
	पूर्ण
पूर्ण

अटल अचिन्हित पूर्णांक पूर्णांकel_gtt_mappable_entries(व्योम)
अणु
	अचिन्हित पूर्णांक aperture_size;

	अगर (INTEL_GTT_GEN == 1) अणु
		u32 smram_miscc;

		pci_पढ़ो_config_dword(पूर्णांकel_निजी.bridge_dev,
				      I810_SMRAM_MISCC, &smram_miscc);

		अगर ((smram_miscc & I810_GFX_MEM_WIN_SIZE)
				== I810_GFX_MEM_WIN_32M)
			aperture_size = MB(32);
		अन्यथा
			aperture_size = MB(64);
	पूर्ण अन्यथा अगर (INTEL_GTT_GEN == 2) अणु
		u16 gmch_ctrl;

		pci_पढ़ो_config_word(पूर्णांकel_निजी.bridge_dev,
				     I830_GMCH_CTRL, &gmch_ctrl);

		अगर ((gmch_ctrl & I830_GMCH_MEM_MASK) == I830_GMCH_MEM_64M)
			aperture_size = MB(64);
		अन्यथा
			aperture_size = MB(128);
	पूर्ण अन्यथा अणु
		/* 9xx supports large sizes, just look at the length */
		aperture_size = pci_resource_len(पूर्णांकel_निजी.pcidev, 2);
	पूर्ण

	वापस aperture_size >> PAGE_SHIFT;
पूर्ण

अटल व्योम पूर्णांकel_gtt_tearकरोwn_scratch_page(व्योम)
अणु
	set_pages_wb(पूर्णांकel_निजी.scratch_page, 1);
	अगर (पूर्णांकel_निजी.needs_dmar)
		pci_unmap_page(पूर्णांकel_निजी.pcidev,
			       पूर्णांकel_निजी.scratch_page_dma,
			       PAGE_SIZE, PCI_DMA_BIसूचीECTIONAL);
	__मुक्त_page(पूर्णांकel_निजी.scratch_page);
पूर्ण

अटल व्योम पूर्णांकel_gtt_cleanup(व्योम)
अणु
	पूर्णांकel_निजी.driver->cleanup();

	iounmap(पूर्णांकel_निजी.gtt);
	iounmap(पूर्णांकel_निजी.रेजिस्टरs);

	पूर्णांकel_gtt_tearकरोwn_scratch_page();
पूर्ण

/* Certain Gen5 chipsets require require idling the GPU beक्रमe
 * unmapping anything from the GTT when VT-d is enabled.
 */
अटल अंतरभूत पूर्णांक needs_ilk_vtd_wa(व्योम)
अणु
#अगर_घोषित CONFIG_INTEL_IOMMU
	स्थिर अचिन्हित लघु gpu_devid = पूर्णांकel_निजी.pcidev->device;

	/* Query पूर्णांकel_iommu to see अगर we need the workaround. Presumably that
	 * was loaded first.
	 */
	अगर ((gpu_devid == PCI_DEVICE_ID_INTEL_IRONLAKE_D_IG ||
	     gpu_devid == PCI_DEVICE_ID_INTEL_IRONLAKE_M_IG) &&
	     पूर्णांकel_iommu_gfx_mapped)
		वापस 1;
#पूर्ण_अगर
	वापस 0;
पूर्ण

अटल bool पूर्णांकel_gtt_can_wc(व्योम)
अणु
	अगर (INTEL_GTT_GEN <= 2)
		वापस false;

	अगर (INTEL_GTT_GEN >= 6)
		वापस false;

	/* Reports of major corruption with ILK vt'd enabled */
	अगर (needs_ilk_vtd_wa())
		वापस false;

	वापस true;
पूर्ण

अटल पूर्णांक पूर्णांकel_gtt_init(व्योम)
अणु
	u32 gtt_map_size;
	पूर्णांक ret, bar;

	ret = पूर्णांकel_निजी.driver->setup();
	अगर (ret != 0)
		वापस ret;

	पूर्णांकel_निजी.gtt_mappable_entries = पूर्णांकel_gtt_mappable_entries();
	पूर्णांकel_निजी.gtt_total_entries = पूर्णांकel_gtt_total_entries();

	/* save the PGETBL reg क्रम resume */
	पूर्णांकel_निजी.PGETBL_save =
		पढ़ोl(पूर्णांकel_निजी.रेजिस्टरs+I810_PGETBL_CTL)
			& ~I810_PGETBL_ENABLED;
	/* we only ever restore the रेजिस्टर when enabling the PGTBL... */
	अगर (HAS_PGTBL_EN)
		पूर्णांकel_निजी.PGETBL_save |= I810_PGETBL_ENABLED;

	dev_info(&पूर्णांकel_निजी.bridge_dev->dev,
			"detected gtt size: %dK total, %dK mappable\n",
			पूर्णांकel_निजी.gtt_total_entries * 4,
			पूर्णांकel_निजी.gtt_mappable_entries * 4);

	gtt_map_size = पूर्णांकel_निजी.gtt_total_entries * 4;

	पूर्णांकel_निजी.gtt = शून्य;
	अगर (पूर्णांकel_gtt_can_wc())
		पूर्णांकel_निजी.gtt = ioremap_wc(पूर्णांकel_निजी.gtt_phys_addr,
					       gtt_map_size);
	अगर (पूर्णांकel_निजी.gtt == शून्य)
		पूर्णांकel_निजी.gtt = ioremap(पूर्णांकel_निजी.gtt_phys_addr,
					    gtt_map_size);
	अगर (पूर्णांकel_निजी.gtt == शून्य) अणु
		पूर्णांकel_निजी.driver->cleanup();
		iounmap(पूर्णांकel_निजी.रेजिस्टरs);
		वापस -ENOMEM;
	पूर्ण

#अगर IS_ENABLED(CONFIG_AGP_INTEL)
	global_cache_flush();   /* FIXME: ? */
#पूर्ण_अगर

	पूर्णांकel_निजी.stolen_size = पूर्णांकel_gtt_stolen_size();

	पूर्णांकel_निजी.needs_dmar = USE_PCI_DMA_API && INTEL_GTT_GEN > 2;

	ret = पूर्णांकel_gtt_setup_scratch_page();
	अगर (ret != 0) अणु
		पूर्णांकel_gtt_cleanup();
		वापस ret;
	पूर्ण

	अगर (INTEL_GTT_GEN <= 2)
		bar = I810_GMADR_BAR;
	अन्यथा
		bar = I915_GMADR_BAR;

	पूर्णांकel_निजी.gma_bus_addr = pci_bus_address(पूर्णांकel_निजी.pcidev, bar);
	वापस 0;
पूर्ण

#अगर IS_ENABLED(CONFIG_AGP_INTEL)
अटल स्थिर काष्ठा aper_size_info_fixed पूर्णांकel_fake_agp_sizes[] = अणु
	अणु32, 8192, 3पूर्ण,
	अणु64, 16384, 4पूर्ण,
	अणु128, 32768, 5पूर्ण,
	अणु256, 65536, 6पूर्ण,
	अणु512, 131072, 7पूर्ण,
पूर्ण;

अटल पूर्णांक पूर्णांकel_fake_agp_fetch_size(व्योम)
अणु
	पूर्णांक num_sizes = ARRAY_SIZE(पूर्णांकel_fake_agp_sizes);
	अचिन्हित पूर्णांक aper_size;
	पूर्णांक i;

	aper_size = (पूर्णांकel_निजी.gtt_mappable_entries << PAGE_SHIFT) / MB(1);

	क्रम (i = 0; i < num_sizes; i++) अणु
		अगर (aper_size == पूर्णांकel_fake_agp_sizes[i].size) अणु
			agp_bridge->current_size =
				(व्योम *) (पूर्णांकel_fake_agp_sizes + i);
			वापस aper_size;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल व्योम i830_cleanup(व्योम)
अणु
पूर्ण

/* The chipset_flush पूर्णांकerface needs to get data that has alपढ़ोy been
 * flushed out of the CPU all the way out to मुख्य memory, because the GPU
 * करोesn't snoop those buffers.
 *
 * The 8xx series करोesn't have the same lovely पूर्णांकerface क्रम flushing the
 * chipset ग_लिखो buffers that the later chips करो. According to the 865
 * specs, it's 64 octwords, or 1KB.  So, to get those previous things in
 * that buffer out, we just fill 1KB and clflush it out, on the assumption
 * that it'll push whatever was in there out.  It appears to work.
 */
अटल व्योम i830_chipset_flush(व्योम)
अणु
	अचिन्हित दीर्घ समयout = jअगरfies + msecs_to_jअगरfies(1000);

	/* Forcibly evict everything from the CPU ग_लिखो buffers.
	 * clflush appears to be insufficient.
	 */
	wbinvd_on_all_cpus();

	/* Now we've only seen करोcuments क्रम this magic bit on 855GM,
	 * we hope it exists क्रम the other gen2 chipsets...
	 *
	 * Also works as advertised on my 845G.
	 */
	ग_लिखोl(पढ़ोl(पूर्णांकel_निजी.रेजिस्टरs+I830_HIC) | (1<<31),
	       पूर्णांकel_निजी.रेजिस्टरs+I830_HIC);

	जबतक (पढ़ोl(पूर्णांकel_निजी.रेजिस्टरs+I830_HIC) & (1<<31)) अणु
		अगर (समय_after(jअगरfies, समयout))
			अवरोध;

		udelay(50);
	पूर्ण
पूर्ण

अटल व्योम i830_ग_लिखो_entry(dma_addr_t addr, अचिन्हित पूर्णांक entry,
			     अचिन्हित पूर्णांक flags)
अणु
	u32 pte_flags = I810_PTE_VALID;

	अगर (flags ==  AGP_USER_CACHED_MEMORY)
		pte_flags |= I830_PTE_SYSTEM_CACHED;

	ग_लिखोl_relaxed(addr | pte_flags, पूर्णांकel_निजी.gtt + entry);
पूर्ण

bool पूर्णांकel_enable_gtt(व्योम)
अणु
	u8 __iomem *reg;

	अगर (INTEL_GTT_GEN == 2) अणु
		u16 gmch_ctrl;

		pci_पढ़ो_config_word(पूर्णांकel_निजी.bridge_dev,
				     I830_GMCH_CTRL, &gmch_ctrl);
		gmch_ctrl |= I830_GMCH_ENABLED;
		pci_ग_लिखो_config_word(पूर्णांकel_निजी.bridge_dev,
				      I830_GMCH_CTRL, gmch_ctrl);

		pci_पढ़ो_config_word(पूर्णांकel_निजी.bridge_dev,
				     I830_GMCH_CTRL, &gmch_ctrl);
		अगर ((gmch_ctrl & I830_GMCH_ENABLED) == 0) अणु
			dev_err(&पूर्णांकel_निजी.pcidev->dev,
				"failed to enable the GTT: GMCH_CTRL=%x\n",
				gmch_ctrl);
			वापस false;
		पूर्ण
	पूर्ण

	/* On the resume path we may be adjusting the PGTBL value, so
	 * be paranoid and flush all chipset ग_लिखो buffers...
	 */
	अगर (INTEL_GTT_GEN >= 3)
		ग_लिखोl(0, पूर्णांकel_निजी.रेजिस्टरs+GFX_FLSH_CNTL);

	reg = पूर्णांकel_निजी.रेजिस्टरs+I810_PGETBL_CTL;
	ग_लिखोl(पूर्णांकel_निजी.PGETBL_save, reg);
	अगर (HAS_PGTBL_EN && (पढ़ोl(reg) & I810_PGETBL_ENABLED) == 0) अणु
		dev_err(&पूर्णांकel_निजी.pcidev->dev,
			"failed to enable the GTT: PGETBL=%x [expected %x]\n",
			पढ़ोl(reg), पूर्णांकel_निजी.PGETBL_save);
		वापस false;
	पूर्ण

	अगर (INTEL_GTT_GEN >= 3)
		ग_लिखोl(0, पूर्णांकel_निजी.रेजिस्टरs+GFX_FLSH_CNTL);

	वापस true;
पूर्ण
EXPORT_SYMBOL(पूर्णांकel_enable_gtt);

अटल पूर्णांक i830_setup(व्योम)
अणु
	phys_addr_t reg_addr;

	reg_addr = pci_resource_start(पूर्णांकel_निजी.pcidev, I810_MMADR_BAR);

	पूर्णांकel_निजी.रेजिस्टरs = ioremap(reg_addr, KB(64));
	अगर (!पूर्णांकel_निजी.रेजिस्टरs)
		वापस -ENOMEM;

	पूर्णांकel_निजी.gtt_phys_addr = reg_addr + I810_PTE_BASE;

	वापस 0;
पूर्ण

#अगर IS_ENABLED(CONFIG_AGP_INTEL)
अटल पूर्णांक पूर्णांकel_fake_agp_create_gatt_table(काष्ठा agp_bridge_data *bridge)
अणु
	agp_bridge->gatt_table_real = शून्य;
	agp_bridge->gatt_table = शून्य;
	agp_bridge->gatt_bus_addr = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकel_fake_agp_मुक्त_gatt_table(काष्ठा agp_bridge_data *bridge)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकel_fake_agp_configure(व्योम)
अणु
	अगर (!पूर्णांकel_enable_gtt())
	    वापस -EIO;

	पूर्णांकel_निजी.clear_fake_agp = true;
	agp_bridge->gart_bus_addr = पूर्णांकel_निजी.gma_bus_addr;

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल bool i830_check_flags(अचिन्हित पूर्णांक flags)
अणु
	चयन (flags) अणु
	हाल 0:
	हाल AGP_PHYS_MEMORY:
	हाल AGP_USER_CACHED_MEMORY:
	हाल AGP_USER_MEMORY:
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

व्योम पूर्णांकel_gtt_insert_page(dma_addr_t addr,
			   अचिन्हित पूर्णांक pg,
			   अचिन्हित पूर्णांक flags)
अणु
	पूर्णांकel_निजी.driver->ग_लिखो_entry(addr, pg, flags);
	पढ़ोl(पूर्णांकel_निजी.gtt + pg);
	अगर (पूर्णांकel_निजी.driver->chipset_flush)
		पूर्णांकel_निजी.driver->chipset_flush();
पूर्ण
EXPORT_SYMBOL(पूर्णांकel_gtt_insert_page);

व्योम पूर्णांकel_gtt_insert_sg_entries(काष्ठा sg_table *st,
				 अचिन्हित पूर्णांक pg_start,
				 अचिन्हित पूर्णांक flags)
अणु
	काष्ठा scatterlist *sg;
	अचिन्हित पूर्णांक len, m;
	पूर्णांक i, j;

	j = pg_start;

	/* sg may merge pages, but we have to separate
	 * per-page addr क्रम GTT */
	क्रम_each_sg(st->sgl, sg, st->nents, i) अणु
		len = sg_dma_len(sg) >> PAGE_SHIFT;
		क्रम (m = 0; m < len; m++) अणु
			dma_addr_t addr = sg_dma_address(sg) + (m << PAGE_SHIFT);
			पूर्णांकel_निजी.driver->ग_लिखो_entry(addr, j, flags);
			j++;
		पूर्ण
	पूर्ण
	पढ़ोl(पूर्णांकel_निजी.gtt + j - 1);
	अगर (पूर्णांकel_निजी.driver->chipset_flush)
		पूर्णांकel_निजी.driver->chipset_flush();
पूर्ण
EXPORT_SYMBOL(पूर्णांकel_gtt_insert_sg_entries);

#अगर IS_ENABLED(CONFIG_AGP_INTEL)
अटल व्योम पूर्णांकel_gtt_insert_pages(अचिन्हित पूर्णांक first_entry,
				   अचिन्हित पूर्णांक num_entries,
				   काष्ठा page **pages,
				   अचिन्हित पूर्णांक flags)
अणु
	पूर्णांक i, j;

	क्रम (i = 0, j = first_entry; i < num_entries; i++, j++) अणु
		dma_addr_t addr = page_to_phys(pages[i]);
		पूर्णांकel_निजी.driver->ग_लिखो_entry(addr,
						  j, flags);
	पूर्ण
	wmb();
पूर्ण

अटल पूर्णांक पूर्णांकel_fake_agp_insert_entries(काष्ठा agp_memory *mem,
					 off_t pg_start, पूर्णांक type)
अणु
	पूर्णांक ret = -EINVAL;

	अगर (पूर्णांकel_निजी.clear_fake_agp) अणु
		पूर्णांक start = पूर्णांकel_निजी.stolen_size / PAGE_SIZE;
		पूर्णांक end = पूर्णांकel_निजी.gtt_mappable_entries;
		पूर्णांकel_gtt_clear_range(start, end - start);
		पूर्णांकel_निजी.clear_fake_agp = false;
	पूर्ण

	अगर (INTEL_GTT_GEN == 1 && type == AGP_DCACHE_MEMORY)
		वापस i810_insert_dcache_entries(mem, pg_start, type);

	अगर (mem->page_count == 0)
		जाओ out;

	अगर (pg_start + mem->page_count > पूर्णांकel_निजी.gtt_total_entries)
		जाओ out_err;

	अगर (type != mem->type)
		जाओ out_err;

	अगर (!पूर्णांकel_निजी.driver->check_flags(type))
		जाओ out_err;

	अगर (!mem->is_flushed)
		global_cache_flush();

	अगर (पूर्णांकel_निजी.needs_dmar) अणु
		काष्ठा sg_table st;

		ret = पूर्णांकel_gtt_map_memory(mem->pages, mem->page_count, &st);
		अगर (ret != 0)
			वापस ret;

		पूर्णांकel_gtt_insert_sg_entries(&st, pg_start, type);
		mem->sg_list = st.sgl;
		mem->num_sg = st.nents;
	पूर्ण अन्यथा
		पूर्णांकel_gtt_insert_pages(pg_start, mem->page_count, mem->pages,
				       type);

out:
	ret = 0;
out_err:
	mem->is_flushed = true;
	वापस ret;
पूर्ण
#पूर्ण_अगर

व्योम पूर्णांकel_gtt_clear_range(अचिन्हित पूर्णांक first_entry, अचिन्हित पूर्णांक num_entries)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = first_entry; i < (first_entry + num_entries); i++) अणु
		पूर्णांकel_निजी.driver->ग_लिखो_entry(पूर्णांकel_निजी.scratch_page_dma,
						  i, 0);
	पूर्ण
	wmb();
पूर्ण
EXPORT_SYMBOL(पूर्णांकel_gtt_clear_range);

#अगर IS_ENABLED(CONFIG_AGP_INTEL)
अटल पूर्णांक पूर्णांकel_fake_agp_हटाओ_entries(काष्ठा agp_memory *mem,
					 off_t pg_start, पूर्णांक type)
अणु
	अगर (mem->page_count == 0)
		वापस 0;

	पूर्णांकel_gtt_clear_range(pg_start, mem->page_count);

	अगर (पूर्णांकel_निजी.needs_dmar) अणु
		पूर्णांकel_gtt_unmap_memory(mem->sg_list, mem->num_sg);
		mem->sg_list = शून्य;
		mem->num_sg = 0;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा agp_memory *पूर्णांकel_fake_agp_alloc_by_type(माप_प्रकार pg_count,
						       पूर्णांक type)
अणु
	काष्ठा agp_memory *new;

	अगर (type == AGP_DCACHE_MEMORY && INTEL_GTT_GEN == 1) अणु
		अगर (pg_count != पूर्णांकel_निजी.num_dcache_entries)
			वापस शून्य;

		new = agp_create_memory(1);
		अगर (new == शून्य)
			वापस शून्य;

		new->type = AGP_DCACHE_MEMORY;
		new->page_count = pg_count;
		new->num_scratch_pages = 0;
		agp_मुक्त_page_array(new);
		वापस new;
	पूर्ण
	अगर (type == AGP_PHYS_MEMORY)
		वापस alloc_agpphysmem_i8xx(pg_count, type);
	/* always वापस शून्य क्रम other allocation types क्रम now */
	वापस शून्य;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक पूर्णांकel_alloc_chipset_flush_resource(व्योम)
अणु
	पूर्णांक ret;
	ret = pci_bus_alloc_resource(पूर्णांकel_निजी.bridge_dev->bus, &पूर्णांकel_निजी.अगरp_resource, PAGE_SIZE,
				     PAGE_SIZE, PCIBIOS_MIN_MEM, 0,
				     pcibios_align_resource, पूर्णांकel_निजी.bridge_dev);

	वापस ret;
पूर्ण

अटल व्योम पूर्णांकel_i915_setup_chipset_flush(व्योम)
अणु
	पूर्णांक ret;
	u32 temp;

	pci_पढ़ो_config_dword(पूर्णांकel_निजी.bridge_dev, I915_IFPADDR, &temp);
	अगर (!(temp & 0x1)) अणु
		पूर्णांकel_alloc_chipset_flush_resource();
		पूर्णांकel_निजी.resource_valid = 1;
		pci_ग_लिखो_config_dword(पूर्णांकel_निजी.bridge_dev, I915_IFPADDR, (पूर्णांकel_निजी.अगरp_resource.start & 0xffffffff) | 0x1);
	पूर्ण अन्यथा अणु
		temp &= ~1;

		पूर्णांकel_निजी.resource_valid = 1;
		पूर्णांकel_निजी.अगरp_resource.start = temp;
		पूर्णांकel_निजी.अगरp_resource.end = temp + PAGE_SIZE;
		ret = request_resource(&iomem_resource, &पूर्णांकel_निजी.अगरp_resource);
		/* some BIOSes reserve this area in a pnp some करोn't */
		अगर (ret)
			पूर्णांकel_निजी.resource_valid = 0;
	पूर्ण
पूर्ण

अटल व्योम पूर्णांकel_i965_g33_setup_chipset_flush(व्योम)
अणु
	u32 temp_hi, temp_lo;
	पूर्णांक ret;

	pci_पढ़ो_config_dword(पूर्णांकel_निजी.bridge_dev, I965_IFPADDR + 4, &temp_hi);
	pci_पढ़ो_config_dword(पूर्णांकel_निजी.bridge_dev, I965_IFPADDR, &temp_lo);

	अगर (!(temp_lo & 0x1)) अणु

		पूर्णांकel_alloc_chipset_flush_resource();

		पूर्णांकel_निजी.resource_valid = 1;
		pci_ग_लिखो_config_dword(पूर्णांकel_निजी.bridge_dev, I965_IFPADDR + 4,
			upper_32_bits(पूर्णांकel_निजी.अगरp_resource.start));
		pci_ग_लिखो_config_dword(पूर्णांकel_निजी.bridge_dev, I965_IFPADDR, (पूर्णांकel_निजी.अगरp_resource.start & 0xffffffff) | 0x1);
	पूर्ण अन्यथा अणु
		u64 l64;

		temp_lo &= ~0x1;
		l64 = ((u64)temp_hi << 32) | temp_lo;

		पूर्णांकel_निजी.resource_valid = 1;
		पूर्णांकel_निजी.अगरp_resource.start = l64;
		पूर्णांकel_निजी.अगरp_resource.end = l64 + PAGE_SIZE;
		ret = request_resource(&iomem_resource, &पूर्णांकel_निजी.अगरp_resource);
		/* some BIOSes reserve this area in a pnp some करोn't */
		अगर (ret)
			पूर्णांकel_निजी.resource_valid = 0;
	पूर्ण
पूर्ण

अटल व्योम पूर्णांकel_i9xx_setup_flush(व्योम)
अणु
	/* वापस अगर alपढ़ोy configured */
	अगर (पूर्णांकel_निजी.अगरp_resource.start)
		वापस;

	अगर (INTEL_GTT_GEN == 6)
		वापस;

	/* setup a resource क्रम this object */
	पूर्णांकel_निजी.अगरp_resource.name = "Intel Flush Page";
	पूर्णांकel_निजी.अगरp_resource.flags = IORESOURCE_MEM;

	/* Setup chipset flush क्रम 915 */
	अगर (IS_G33 || INTEL_GTT_GEN >= 4) अणु
		पूर्णांकel_i965_g33_setup_chipset_flush();
	पूर्ण अन्यथा अणु
		पूर्णांकel_i915_setup_chipset_flush();
	पूर्ण

	अगर (पूर्णांकel_निजी.अगरp_resource.start)
		पूर्णांकel_निजी.i9xx_flush_page = ioremap(पूर्णांकel_निजी.अगरp_resource.start, PAGE_SIZE);
	अगर (!पूर्णांकel_निजी.i9xx_flush_page)
		dev_err(&पूर्णांकel_निजी.pcidev->dev,
			"can't ioremap flush page - no chipset flushing\n");
पूर्ण

अटल व्योम i9xx_cleanup(व्योम)
अणु
	अगर (पूर्णांकel_निजी.i9xx_flush_page)
		iounmap(पूर्णांकel_निजी.i9xx_flush_page);
	अगर (पूर्णांकel_निजी.resource_valid)
		release_resource(&पूर्णांकel_निजी.अगरp_resource);
	पूर्णांकel_निजी.अगरp_resource.start = 0;
	पूर्णांकel_निजी.resource_valid = 0;
पूर्ण

अटल व्योम i9xx_chipset_flush(व्योम)
अणु
	wmb();
	अगर (पूर्णांकel_निजी.i9xx_flush_page)
		ग_लिखोl(1, पूर्णांकel_निजी.i9xx_flush_page);
पूर्ण

अटल व्योम i965_ग_लिखो_entry(dma_addr_t addr,
			     अचिन्हित पूर्णांक entry,
			     अचिन्हित पूर्णांक flags)
अणु
	u32 pte_flags;

	pte_flags = I810_PTE_VALID;
	अगर (flags == AGP_USER_CACHED_MEMORY)
		pte_flags |= I830_PTE_SYSTEM_CACHED;

	/* Shअगरt high bits करोwn */
	addr |= (addr >> 28) & 0xf0;
	ग_लिखोl_relaxed(addr | pte_flags, पूर्णांकel_निजी.gtt + entry);
पूर्ण

अटल पूर्णांक i9xx_setup(व्योम)
अणु
	phys_addr_t reg_addr;
	पूर्णांक size = KB(512);

	reg_addr = pci_resource_start(पूर्णांकel_निजी.pcidev, I915_MMADR_BAR);

	पूर्णांकel_निजी.रेजिस्टरs = ioremap(reg_addr, size);
	अगर (!पूर्णांकel_निजी.रेजिस्टरs)
		वापस -ENOMEM;

	चयन (INTEL_GTT_GEN) अणु
	हाल 3:
		पूर्णांकel_निजी.gtt_phys_addr =
			pci_resource_start(पूर्णांकel_निजी.pcidev, I915_PTE_BAR);
		अवरोध;
	हाल 5:
		पूर्णांकel_निजी.gtt_phys_addr = reg_addr + MB(2);
		अवरोध;
	शेष:
		पूर्णांकel_निजी.gtt_phys_addr = reg_addr + KB(512);
		अवरोध;
	पूर्ण

	पूर्णांकel_i9xx_setup_flush();

	वापस 0;
पूर्ण

#अगर IS_ENABLED(CONFIG_AGP_INTEL)
अटल स्थिर काष्ठा agp_bridge_driver पूर्णांकel_fake_agp_driver = अणु
	.owner			= THIS_MODULE,
	.माप_प्रकारype		= FIXED_APER_SIZE,
	.aperture_sizes		= पूर्णांकel_fake_agp_sizes,
	.num_aperture_sizes	= ARRAY_SIZE(पूर्णांकel_fake_agp_sizes),
	.configure		= पूर्णांकel_fake_agp_configure,
	.fetch_size		= पूर्णांकel_fake_agp_fetch_size,
	.cleanup		= पूर्णांकel_gtt_cleanup,
	.agp_enable		= पूर्णांकel_fake_agp_enable,
	.cache_flush		= global_cache_flush,
	.create_gatt_table	= पूर्णांकel_fake_agp_create_gatt_table,
	.मुक्त_gatt_table	= पूर्णांकel_fake_agp_मुक्त_gatt_table,
	.insert_memory		= पूर्णांकel_fake_agp_insert_entries,
	.हटाओ_memory		= पूर्णांकel_fake_agp_हटाओ_entries,
	.alloc_by_type		= पूर्णांकel_fake_agp_alloc_by_type,
	.मुक्त_by_type		= पूर्णांकel_i810_मुक्त_by_type,
	.agp_alloc_page		= agp_generic_alloc_page,
	.agp_alloc_pages        = agp_generic_alloc_pages,
	.agp_destroy_page	= agp_generic_destroy_page,
	.agp_destroy_pages      = agp_generic_destroy_pages,
पूर्ण;
#पूर्ण_अगर

अटल स्थिर काष्ठा पूर्णांकel_gtt_driver i81x_gtt_driver = अणु
	.gen = 1,
	.has_pgtbl_enable = 1,
	.dma_mask_size = 32,
	.setup = i810_setup,
	.cleanup = i810_cleanup,
	.check_flags = i830_check_flags,
	.ग_लिखो_entry = i810_ग_लिखो_entry,
पूर्ण;
अटल स्थिर काष्ठा पूर्णांकel_gtt_driver i8xx_gtt_driver = अणु
	.gen = 2,
	.has_pgtbl_enable = 1,
	.setup = i830_setup,
	.cleanup = i830_cleanup,
	.ग_लिखो_entry = i830_ग_लिखो_entry,
	.dma_mask_size = 32,
	.check_flags = i830_check_flags,
	.chipset_flush = i830_chipset_flush,
पूर्ण;
अटल स्थिर काष्ठा पूर्णांकel_gtt_driver i915_gtt_driver = अणु
	.gen = 3,
	.has_pgtbl_enable = 1,
	.setup = i9xx_setup,
	.cleanup = i9xx_cleanup,
	/* i945 is the last gpu to need phys mem (क्रम overlay and cursors). */
	.ग_लिखो_entry = i830_ग_लिखो_entry,
	.dma_mask_size = 32,
	.check_flags = i830_check_flags,
	.chipset_flush = i9xx_chipset_flush,
पूर्ण;
अटल स्थिर काष्ठा पूर्णांकel_gtt_driver g33_gtt_driver = अणु
	.gen = 3,
	.is_g33 = 1,
	.setup = i9xx_setup,
	.cleanup = i9xx_cleanup,
	.ग_लिखो_entry = i965_ग_लिखो_entry,
	.dma_mask_size = 36,
	.check_flags = i830_check_flags,
	.chipset_flush = i9xx_chipset_flush,
पूर्ण;
अटल स्थिर काष्ठा पूर्णांकel_gtt_driver pineview_gtt_driver = अणु
	.gen = 3,
	.is_pineview = 1, .is_g33 = 1,
	.setup = i9xx_setup,
	.cleanup = i9xx_cleanup,
	.ग_लिखो_entry = i965_ग_लिखो_entry,
	.dma_mask_size = 36,
	.check_flags = i830_check_flags,
	.chipset_flush = i9xx_chipset_flush,
पूर्ण;
अटल स्थिर काष्ठा पूर्णांकel_gtt_driver i965_gtt_driver = अणु
	.gen = 4,
	.has_pgtbl_enable = 1,
	.setup = i9xx_setup,
	.cleanup = i9xx_cleanup,
	.ग_लिखो_entry = i965_ग_लिखो_entry,
	.dma_mask_size = 36,
	.check_flags = i830_check_flags,
	.chipset_flush = i9xx_chipset_flush,
पूर्ण;
अटल स्थिर काष्ठा पूर्णांकel_gtt_driver g4x_gtt_driver = अणु
	.gen = 5,
	.setup = i9xx_setup,
	.cleanup = i9xx_cleanup,
	.ग_लिखो_entry = i965_ग_लिखो_entry,
	.dma_mask_size = 36,
	.check_flags = i830_check_flags,
	.chipset_flush = i9xx_chipset_flush,
पूर्ण;
अटल स्थिर काष्ठा पूर्णांकel_gtt_driver ironlake_gtt_driver = अणु
	.gen = 5,
	.is_ironlake = 1,
	.setup = i9xx_setup,
	.cleanup = i9xx_cleanup,
	.ग_लिखो_entry = i965_ग_लिखो_entry,
	.dma_mask_size = 36,
	.check_flags = i830_check_flags,
	.chipset_flush = i9xx_chipset_flush,
पूर्ण;

/* Table to describe Intel GMCH and AGP/PCIE GART drivers.  At least one of
 * driver and gmch_driver must be non-null, and find_gmch will determine
 * which one should be used अगर a gmch_chip_id is present.
 */
अटल स्थिर काष्ठा पूर्णांकel_gtt_driver_description अणु
	अचिन्हित पूर्णांक gmch_chip_id;
	अक्षर *name;
	स्थिर काष्ठा पूर्णांकel_gtt_driver *gtt_driver;
पूर्ण पूर्णांकel_gtt_chipsets[] = अणु
	अणु PCI_DEVICE_ID_INTEL_82810_IG1, "i810",
		&i81x_gtt_driverपूर्ण,
	अणु PCI_DEVICE_ID_INTEL_82810_IG3, "i810",
		&i81x_gtt_driverपूर्ण,
	अणु PCI_DEVICE_ID_INTEL_82810E_IG, "i810",
		&i81x_gtt_driverपूर्ण,
	अणु PCI_DEVICE_ID_INTEL_82815_CGC, "i815",
		&i81x_gtt_driverपूर्ण,
	अणु PCI_DEVICE_ID_INTEL_82830_CGC, "830M",
		&i8xx_gtt_driverपूर्ण,
	अणु PCI_DEVICE_ID_INTEL_82845G_IG, "845G",
		&i8xx_gtt_driverपूर्ण,
	अणु PCI_DEVICE_ID_INTEL_82854_IG, "854",
		&i8xx_gtt_driverपूर्ण,
	अणु PCI_DEVICE_ID_INTEL_82855GM_IG, "855GM",
		&i8xx_gtt_driverपूर्ण,
	अणु PCI_DEVICE_ID_INTEL_82865_IG, "865",
		&i8xx_gtt_driverपूर्ण,
	अणु PCI_DEVICE_ID_INTEL_E7221_IG, "E7221 (i915)",
		&i915_gtt_driver पूर्ण,
	अणु PCI_DEVICE_ID_INTEL_82915G_IG, "915G",
		&i915_gtt_driver पूर्ण,
	अणु PCI_DEVICE_ID_INTEL_82915GM_IG, "915GM",
		&i915_gtt_driver पूर्ण,
	अणु PCI_DEVICE_ID_INTEL_82945G_IG, "945G",
		&i915_gtt_driver पूर्ण,
	अणु PCI_DEVICE_ID_INTEL_82945GM_IG, "945GM",
		&i915_gtt_driver पूर्ण,
	अणु PCI_DEVICE_ID_INTEL_82945GME_IG, "945GME",
		&i915_gtt_driver पूर्ण,
	अणु PCI_DEVICE_ID_INTEL_82946GZ_IG, "946GZ",
		&i965_gtt_driver पूर्ण,
	अणु PCI_DEVICE_ID_INTEL_82G35_IG, "G35",
		&i965_gtt_driver पूर्ण,
	अणु PCI_DEVICE_ID_INTEL_82965Q_IG, "965Q",
		&i965_gtt_driver पूर्ण,
	अणु PCI_DEVICE_ID_INTEL_82965G_IG, "965G",
		&i965_gtt_driver पूर्ण,
	अणु PCI_DEVICE_ID_INTEL_82965GM_IG, "965GM",
		&i965_gtt_driver पूर्ण,
	अणु PCI_DEVICE_ID_INTEL_82965GME_IG, "965GME/GLE",
		&i965_gtt_driver पूर्ण,
	अणु PCI_DEVICE_ID_INTEL_G33_IG, "G33",
		&g33_gtt_driver पूर्ण,
	अणु PCI_DEVICE_ID_INTEL_Q35_IG, "Q35",
		&g33_gtt_driver पूर्ण,
	अणु PCI_DEVICE_ID_INTEL_Q33_IG, "Q33",
		&g33_gtt_driver पूर्ण,
	अणु PCI_DEVICE_ID_INTEL_PINEVIEW_M_IG, "GMA3150",
		&pineview_gtt_driver पूर्ण,
	अणु PCI_DEVICE_ID_INTEL_PINEVIEW_IG, "GMA3150",
		&pineview_gtt_driver पूर्ण,
	अणु PCI_DEVICE_ID_INTEL_GM45_IG, "GM45",
		&g4x_gtt_driver पूर्ण,
	अणु PCI_DEVICE_ID_INTEL_EAGLELAKE_IG, "Eaglelake",
		&g4x_gtt_driver पूर्ण,
	अणु PCI_DEVICE_ID_INTEL_Q45_IG, "Q45/Q43",
		&g4x_gtt_driver पूर्ण,
	अणु PCI_DEVICE_ID_INTEL_G45_IG, "G45/G43",
		&g4x_gtt_driver पूर्ण,
	अणु PCI_DEVICE_ID_INTEL_B43_IG, "B43",
		&g4x_gtt_driver पूर्ण,
	अणु PCI_DEVICE_ID_INTEL_B43_1_IG, "B43",
		&g4x_gtt_driver पूर्ण,
	अणु PCI_DEVICE_ID_INTEL_G41_IG, "G41",
		&g4x_gtt_driver पूर्ण,
	अणु PCI_DEVICE_ID_INTEL_IRONLAKE_D_IG,
	    "HD Graphics", &ironlake_gtt_driver पूर्ण,
	अणु PCI_DEVICE_ID_INTEL_IRONLAKE_M_IG,
	    "HD Graphics", &ironlake_gtt_driver पूर्ण,
	अणु 0, शून्य, शून्य पूर्ण
पूर्ण;

अटल पूर्णांक find_gmch(u16 device)
अणु
	काष्ठा pci_dev *gmch_device;

	gmch_device = pci_get_device(PCI_VENDOR_ID_INTEL, device, शून्य);
	अगर (gmch_device && PCI_FUNC(gmch_device->devfn) != 0) अणु
		gmch_device = pci_get_device(PCI_VENDOR_ID_INTEL,
					     device, gmch_device);
	पूर्ण

	अगर (!gmch_device)
		वापस 0;

	पूर्णांकel_निजी.pcidev = gmch_device;
	वापस 1;
पूर्ण

पूर्णांक पूर्णांकel_gmch_probe(काष्ठा pci_dev *bridge_pdev, काष्ठा pci_dev *gpu_pdev,
		     काष्ठा agp_bridge_data *bridge)
अणु
	पूर्णांक i, mask;

	क्रम (i = 0; पूर्णांकel_gtt_chipsets[i].name != शून्य; i++) अणु
		अगर (gpu_pdev) अणु
			अगर (gpu_pdev->device ==
			    पूर्णांकel_gtt_chipsets[i].gmch_chip_id) अणु
				पूर्णांकel_निजी.pcidev = pci_dev_get(gpu_pdev);
				पूर्णांकel_निजी.driver =
					पूर्णांकel_gtt_chipsets[i].gtt_driver;

				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अगर (find_gmch(पूर्णांकel_gtt_chipsets[i].gmch_chip_id)) अणु
			पूर्णांकel_निजी.driver =
				पूर्णांकel_gtt_chipsets[i].gtt_driver;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!पूर्णांकel_निजी.driver)
		वापस 0;

#अगर IS_ENABLED(CONFIG_AGP_INTEL)
	अगर (bridge) अणु
		अगर (INTEL_GTT_GEN > 1)
			वापस 0;

		bridge->driver = &पूर्णांकel_fake_agp_driver;
		bridge->dev_निजी_data = &पूर्णांकel_निजी;
		bridge->dev = bridge_pdev;
	पूर्ण
#पूर्ण_अगर


	/*
	 * Can be called from the fake agp driver but also directly from
	 * drm/i915.ko. Hence we need to check whether everything is set up
	 * alपढ़ोy.
	 */
	अगर (पूर्णांकel_निजी.refcount++)
		वापस 1;

	पूर्णांकel_निजी.bridge_dev = pci_dev_get(bridge_pdev);

	dev_info(&bridge_pdev->dev, "Intel %s Chipset\n", पूर्णांकel_gtt_chipsets[i].name);

	अगर (bridge) अणु
		mask = पूर्णांकel_निजी.driver->dma_mask_size;
		अगर (pci_set_dma_mask(पूर्णांकel_निजी.pcidev, DMA_BIT_MASK(mask)))
			dev_err(&पूर्णांकel_निजी.pcidev->dev,
				"set gfx device dma mask %d-bit failed!\n",
				mask);
		अन्यथा
			pci_set_consistent_dma_mask(पूर्णांकel_निजी.pcidev,
						    DMA_BIT_MASK(mask));
	पूर्ण

	अगर (पूर्णांकel_gtt_init() != 0) अणु
		पूर्णांकel_gmch_हटाओ();

		वापस 0;
	पूर्ण

	वापस 1;
पूर्ण
EXPORT_SYMBOL(पूर्णांकel_gmch_probe);

व्योम पूर्णांकel_gtt_get(u64 *gtt_total,
		   phys_addr_t *mappable_base,
		   resource_माप_प्रकार *mappable_end)
अणु
	*gtt_total = पूर्णांकel_निजी.gtt_total_entries << PAGE_SHIFT;
	*mappable_base = पूर्णांकel_निजी.gma_bus_addr;
	*mappable_end = पूर्णांकel_निजी.gtt_mappable_entries << PAGE_SHIFT;
पूर्ण
EXPORT_SYMBOL(पूर्णांकel_gtt_get);

व्योम पूर्णांकel_gtt_chipset_flush(व्योम)
अणु
	अगर (पूर्णांकel_निजी.driver->chipset_flush)
		पूर्णांकel_निजी.driver->chipset_flush();
पूर्ण
EXPORT_SYMBOL(पूर्णांकel_gtt_chipset_flush);

व्योम पूर्णांकel_gmch_हटाओ(व्योम)
अणु
	अगर (--पूर्णांकel_निजी.refcount)
		वापस;

	अगर (पूर्णांकel_निजी.scratch_page)
		पूर्णांकel_gtt_tearकरोwn_scratch_page();
	अगर (पूर्णांकel_निजी.pcidev)
		pci_dev_put(पूर्णांकel_निजी.pcidev);
	अगर (पूर्णांकel_निजी.bridge_dev)
		pci_dev_put(पूर्णांकel_निजी.bridge_dev);
	पूर्णांकel_निजी.driver = शून्य;
पूर्ण
EXPORT_SYMBOL(पूर्णांकel_gmch_हटाओ);

MODULE_AUTHOR("Dave Jones, Various @Intel");
MODULE_LICENSE("GPL and additional rights");
