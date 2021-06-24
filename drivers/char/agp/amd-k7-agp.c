<शैली गुरु>
/*
 * AMD K7 AGPGART routines.
 */

#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/init.h>
#समावेश <linux/agp_backend.h>
#समावेश <linux/page-flags.h>
#समावेश <linux/mm.h>
#समावेश <linux/slab.h>
#समावेश <यंत्र/set_memory.h>
#समावेश "agp.h"

#घोषणा AMD_MMBASE_BAR	1
#घोषणा AMD_APSIZE	0xac
#घोषणा AMD_MODECNTL	0xb0
#घोषणा AMD_MODECNTL2	0xb2
#घोषणा AMD_GARTENABLE	0x02	/* In mmio region (16-bit रेजिस्टर) */
#घोषणा AMD_ATTBASE	0x04	/* In mmio region (32-bit रेजिस्टर) */
#घोषणा AMD_TLBFLUSH	0x0c	/* In mmio region (32-bit रेजिस्टर) */
#घोषणा AMD_CACHEENTRY	0x10	/* In mmio region (32-bit रेजिस्टर) */

अटल स्थिर काष्ठा pci_device_id agp_amdk7_pci_table[];

काष्ठा amd_page_map अणु
	अचिन्हित दीर्घ *real;
	अचिन्हित दीर्घ __iomem *remapped;
पूर्ण;

अटल काष्ठा _amd_irongate_निजी अणु
	अस्थिर u8 __iomem *रेजिस्टरs;
	काष्ठा amd_page_map **gatt_pages;
	पूर्णांक num_tables;
पूर्ण amd_irongate_निजी;

अटल पूर्णांक amd_create_page_map(काष्ठा amd_page_map *page_map)
अणु
	पूर्णांक i;

	page_map->real = (अचिन्हित दीर्घ *) __get_मुक्त_page(GFP_KERNEL);
	अगर (page_map->real == शून्य)
		वापस -ENOMEM;

	set_memory_uc((अचिन्हित दीर्घ)page_map->real, 1);
	page_map->remapped = page_map->real;

	क्रम (i = 0; i < PAGE_SIZE / माप(अचिन्हित दीर्घ); i++) अणु
		ग_लिखोl(agp_bridge->scratch_page, page_map->remapped+i);
		पढ़ोl(page_map->remapped+i);	/* PCI Posting. */
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम amd_मुक्त_page_map(काष्ठा amd_page_map *page_map)
अणु
	set_memory_wb((अचिन्हित दीर्घ)page_map->real, 1);
	मुक्त_page((अचिन्हित दीर्घ) page_map->real);
पूर्ण

अटल व्योम amd_मुक्त_gatt_pages(व्योम)
अणु
	पूर्णांक i;
	काष्ठा amd_page_map **tables;
	काष्ठा amd_page_map *entry;

	tables = amd_irongate_निजी.gatt_pages;
	क्रम (i = 0; i < amd_irongate_निजी.num_tables; i++) अणु
		entry = tables[i];
		अगर (entry != शून्य) अणु
			अगर (entry->real != शून्य)
				amd_मुक्त_page_map(entry);
			kमुक्त(entry);
		पूर्ण
	पूर्ण
	kमुक्त(tables);
	amd_irongate_निजी.gatt_pages = शून्य;
पूर्ण

अटल पूर्णांक amd_create_gatt_pages(पूर्णांक nr_tables)
अणु
	काष्ठा amd_page_map **tables;
	काष्ठा amd_page_map *entry;
	पूर्णांक retval = 0;
	पूर्णांक i;

	tables = kसुस्मृति(nr_tables + 1, माप(काष्ठा amd_page_map *),
			 GFP_KERNEL);
	अगर (tables == शून्य)
		वापस -ENOMEM;

	क्रम (i = 0; i < nr_tables; i++) अणु
		entry = kzalloc(माप(काष्ठा amd_page_map), GFP_KERNEL);
		tables[i] = entry;
		अगर (entry == शून्य) अणु
			retval = -ENOMEM;
			अवरोध;
		पूर्ण
		retval = amd_create_page_map(entry);
		अगर (retval != 0)
			अवरोध;
	पूर्ण
	amd_irongate_निजी.num_tables = i;
	amd_irongate_निजी.gatt_pages = tables;

	अगर (retval != 0)
		amd_मुक्त_gatt_pages();

	वापस retval;
पूर्ण

/* Since we करोn't need contiguous memory we just try
 * to get the gatt table once
 */

#घोषणा GET_PAGE_सूची_OFF(addr) (addr >> 22)
#घोषणा GET_PAGE_सूची_IDX(addr) (GET_PAGE_सूची_OFF(addr) - \
	GET_PAGE_सूची_OFF(agp_bridge->gart_bus_addr))
#घोषणा GET_GATT_OFF(addr) ((addr & 0x003ff000) >> 12)
#घोषणा GET_GATT(addr) (amd_irongate_निजी.gatt_pages[\
	GET_PAGE_सूची_IDX(addr)]->remapped)

अटल पूर्णांक amd_create_gatt_table(काष्ठा agp_bridge_data *bridge)
अणु
	काष्ठा aper_size_info_lvl2 *value;
	काष्ठा amd_page_map page_dir;
	अचिन्हित दीर्घ __iomem *cur_gatt;
	अचिन्हित दीर्घ addr;
	पूर्णांक retval;
	पूर्णांक i;

	value = A_SIZE_LVL2(agp_bridge->current_size);
	retval = amd_create_page_map(&page_dir);
	अगर (retval != 0)
		वापस retval;

	retval = amd_create_gatt_pages(value->num_entries / 1024);
	अगर (retval != 0) अणु
		amd_मुक्त_page_map(&page_dir);
		वापस retval;
	पूर्ण

	agp_bridge->gatt_table_real = (u32 *)page_dir.real;
	agp_bridge->gatt_table = (u32 __iomem *)page_dir.remapped;
	agp_bridge->gatt_bus_addr = virt_to_phys(page_dir.real);

	/* Get the address क्रम the gart region.
	 * This is a bus address even on the alpha, b/c its
	 * used to program the agp master not the cpu
	 */

	addr = pci_bus_address(agp_bridge->dev, AGP_APERTURE_BAR);
	agp_bridge->gart_bus_addr = addr;

	/* Calculate the agp offset */
	क्रम (i = 0; i < value->num_entries / 1024; i++, addr += 0x00400000) अणु
		ग_लिखोl(virt_to_phys(amd_irongate_निजी.gatt_pages[i]->real) | 1,
			page_dir.remapped+GET_PAGE_सूची_OFF(addr));
		पढ़ोl(page_dir.remapped+GET_PAGE_सूची_OFF(addr));	/* PCI Posting. */
	पूर्ण

	क्रम (i = 0; i < value->num_entries; i++) अणु
		addr = (i * PAGE_SIZE) + agp_bridge->gart_bus_addr;
		cur_gatt = GET_GATT(addr);
		ग_लिखोl(agp_bridge->scratch_page, cur_gatt+GET_GATT_OFF(addr));
		पढ़ोl(cur_gatt+GET_GATT_OFF(addr));	/* PCI Posting. */
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक amd_मुक्त_gatt_table(काष्ठा agp_bridge_data *bridge)
अणु
	काष्ठा amd_page_map page_dir;

	page_dir.real = (अचिन्हित दीर्घ *)agp_bridge->gatt_table_real;
	page_dir.remapped = (अचिन्हित दीर्घ __iomem *)agp_bridge->gatt_table;

	amd_मुक्त_gatt_pages();
	amd_मुक्त_page_map(&page_dir);
	वापस 0;
पूर्ण

अटल पूर्णांक amd_irongate_fetch_size(व्योम)
अणु
	पूर्णांक i;
	u32 temp;
	काष्ठा aper_size_info_lvl2 *values;

	pci_पढ़ो_config_dword(agp_bridge->dev, AMD_APSIZE, &temp);
	temp = (temp & 0x0000000e);
	values = A_SIZE_LVL2(agp_bridge->driver->aperture_sizes);
	क्रम (i = 0; i < agp_bridge->driver->num_aperture_sizes; i++) अणु
		अगर (temp == values[i].size_value) अणु
			agp_bridge->previous_size =
			    agp_bridge->current_size = (व्योम *) (values + i);

			agp_bridge->aperture_size_idx = i;
			वापस values[i].size;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक amd_irongate_configure(व्योम)
अणु
	काष्ठा aper_size_info_lvl2 *current_size;
	phys_addr_t reg;
	u32 temp;
	u16 enable_reg;

	current_size = A_SIZE_LVL2(agp_bridge->current_size);

	अगर (!amd_irongate_निजी.रेजिस्टरs) अणु
		/* Get the memory mapped रेजिस्टरs */
		reg = pci_resource_start(agp_bridge->dev, AMD_MMBASE_BAR);
		amd_irongate_निजी.रेजिस्टरs = (अस्थिर u8 __iomem *) ioremap(reg, 4096);
		अगर (!amd_irongate_निजी.रेजिस्टरs)
			वापस -ENOMEM;
	पूर्ण

	/* Write out the address of the gatt table */
	ग_लिखोl(agp_bridge->gatt_bus_addr, amd_irongate_निजी.रेजिस्टरs+AMD_ATTBASE);
	पढ़ोl(amd_irongate_निजी.रेजिस्टरs+AMD_ATTBASE);	/* PCI Posting. */

	/* Write the Sync रेजिस्टर */
	pci_ग_लिखो_config_byte(agp_bridge->dev, AMD_MODECNTL, 0x80);

	/* Set indexing mode */
	pci_ग_लिखो_config_byte(agp_bridge->dev, AMD_MODECNTL2, 0x00);

	/* Write the enable रेजिस्टर */
	enable_reg = पढ़ोw(amd_irongate_निजी.रेजिस्टरs+AMD_GARTENABLE);
	enable_reg = (enable_reg | 0x0004);
	ग_लिखोw(enable_reg, amd_irongate_निजी.रेजिस्टरs+AMD_GARTENABLE);
	पढ़ोw(amd_irongate_निजी.रेजिस्टरs+AMD_GARTENABLE);	/* PCI Posting. */

	/* Write out the size रेजिस्टर */
	pci_पढ़ो_config_dword(agp_bridge->dev, AMD_APSIZE, &temp);
	temp = (((temp & ~(0x0000000e)) | current_size->size_value) | 1);
	pci_ग_लिखो_config_dword(agp_bridge->dev, AMD_APSIZE, temp);

	/* Flush the tlb */
	ग_लिखोl(1, amd_irongate_निजी.रेजिस्टरs+AMD_TLBFLUSH);
	पढ़ोl(amd_irongate_निजी.रेजिस्टरs+AMD_TLBFLUSH);	/* PCI Posting.*/
	वापस 0;
पूर्ण

अटल व्योम amd_irongate_cleanup(व्योम)
अणु
	काष्ठा aper_size_info_lvl2 *previous_size;
	u32 temp;
	u16 enable_reg;

	previous_size = A_SIZE_LVL2(agp_bridge->previous_size);

	enable_reg = पढ़ोw(amd_irongate_निजी.रेजिस्टरs+AMD_GARTENABLE);
	enable_reg = (enable_reg & ~(0x0004));
	ग_लिखोw(enable_reg, amd_irongate_निजी.रेजिस्टरs+AMD_GARTENABLE);
	पढ़ोw(amd_irongate_निजी.रेजिस्टरs+AMD_GARTENABLE);	/* PCI Posting. */

	/* Write back the previous size and disable gart translation */
	pci_पढ़ो_config_dword(agp_bridge->dev, AMD_APSIZE, &temp);
	temp = ((temp & ~(0x0000000f)) | previous_size->size_value);
	pci_ग_लिखो_config_dword(agp_bridge->dev, AMD_APSIZE, temp);
	iounmap((व्योम __iomem *) amd_irongate_निजी.रेजिस्टरs);
पूर्ण

/*
 * This routine could be implemented by taking the addresses
 * written to the GATT, and flushing them inभागidually.  However
 * currently it just flushes the whole table.  Which is probably
 * more efficient, since agp_memory blocks can be a large number of
 * entries.
 */

अटल व्योम amd_irongate_tlbflush(काष्ठा agp_memory *temp)
अणु
	ग_लिखोl(1, amd_irongate_निजी.रेजिस्टरs+AMD_TLBFLUSH);
	पढ़ोl(amd_irongate_निजी.रेजिस्टरs+AMD_TLBFLUSH);	/* PCI Posting. */
पूर्ण

अटल पूर्णांक amd_insert_memory(काष्ठा agp_memory *mem, off_t pg_start, पूर्णांक type)
अणु
	पूर्णांक i, j, num_entries;
	अचिन्हित दीर्घ __iomem *cur_gatt;
	अचिन्हित दीर्घ addr;

	num_entries = A_SIZE_LVL2(agp_bridge->current_size)->num_entries;

	अगर (type != mem->type ||
	    agp_bridge->driver->agp_type_to_mask_type(agp_bridge, type))
		वापस -EINVAL;

	अगर ((pg_start + mem->page_count) > num_entries)
		वापस -EINVAL;

	j = pg_start;
	जबतक (j < (pg_start + mem->page_count)) अणु
		addr = (j * PAGE_SIZE) + agp_bridge->gart_bus_addr;
		cur_gatt = GET_GATT(addr);
		अगर (!PGE_EMPTY(agp_bridge, पढ़ोl(cur_gatt+GET_GATT_OFF(addr))))
			वापस -EBUSY;
		j++;
	पूर्ण

	अगर (!mem->is_flushed) अणु
		global_cache_flush();
		mem->is_flushed = true;
	पूर्ण

	क्रम (i = 0, j = pg_start; i < mem->page_count; i++, j++) अणु
		addr = (j * PAGE_SIZE) + agp_bridge->gart_bus_addr;
		cur_gatt = GET_GATT(addr);
		ग_लिखोl(agp_generic_mask_memory(agp_bridge,
					       page_to_phys(mem->pages[i]),
					       mem->type),
		       cur_gatt+GET_GATT_OFF(addr));
		पढ़ोl(cur_gatt+GET_GATT_OFF(addr));	/* PCI Posting. */
	पूर्ण
	amd_irongate_tlbflush(mem);
	वापस 0;
पूर्ण

अटल पूर्णांक amd_हटाओ_memory(काष्ठा agp_memory *mem, off_t pg_start, पूर्णांक type)
अणु
	पूर्णांक i;
	अचिन्हित दीर्घ __iomem *cur_gatt;
	अचिन्हित दीर्घ addr;

	अगर (type != mem->type ||
	    agp_bridge->driver->agp_type_to_mask_type(agp_bridge, type))
		वापस -EINVAL;

	क्रम (i = pg_start; i < (mem->page_count + pg_start); i++) अणु
		addr = (i * PAGE_SIZE) + agp_bridge->gart_bus_addr;
		cur_gatt = GET_GATT(addr);
		ग_लिखोl(agp_bridge->scratch_page, cur_gatt+GET_GATT_OFF(addr));
		पढ़ोl(cur_gatt+GET_GATT_OFF(addr));	/* PCI Posting. */
	पूर्ण

	amd_irongate_tlbflush(mem);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा aper_size_info_lvl2 amd_irongate_sizes[7] =
अणु
	अणु2048, 524288, 0x0000000cपूर्ण,
	अणु1024, 262144, 0x0000000aपूर्ण,
	अणु512, 131072, 0x00000008पूर्ण,
	अणु256, 65536, 0x00000006पूर्ण,
	अणु128, 32768, 0x00000004पूर्ण,
	अणु64, 16384, 0x00000002पूर्ण,
	अणु32, 8192, 0x00000000पूर्ण
पूर्ण;

अटल स्थिर काष्ठा gatt_mask amd_irongate_masks[] =
अणु
	अणु.mask = 1, .type = 0पूर्ण
पूर्ण;

अटल स्थिर काष्ठा agp_bridge_driver amd_irongate_driver = अणु
	.owner			= THIS_MODULE,
	.aperture_sizes		= amd_irongate_sizes,
	.माप_प्रकारype		= LVL2_APER_SIZE,
	.num_aperture_sizes	= 7,
	.needs_scratch_page	= true,
	.configure		= amd_irongate_configure,
	.fetch_size		= amd_irongate_fetch_size,
	.cleanup		= amd_irongate_cleanup,
	.tlb_flush		= amd_irongate_tlbflush,
	.mask_memory		= agp_generic_mask_memory,
	.masks			= amd_irongate_masks,
	.agp_enable		= agp_generic_enable,
	.cache_flush		= global_cache_flush,
	.create_gatt_table	= amd_create_gatt_table,
	.मुक्त_gatt_table	= amd_मुक्त_gatt_table,
	.insert_memory		= amd_insert_memory,
	.हटाओ_memory		= amd_हटाओ_memory,
	.alloc_by_type		= agp_generic_alloc_by_type,
	.मुक्त_by_type		= agp_generic_मुक्त_by_type,
	.agp_alloc_page		= agp_generic_alloc_page,
	.agp_alloc_pages	= agp_generic_alloc_pages,
	.agp_destroy_page	= agp_generic_destroy_page,
	.agp_destroy_pages	= agp_generic_destroy_pages,
	.agp_type_to_mask_type  = agp_generic_type_to_mask_type,
पूर्ण;

अटल काष्ठा agp_device_ids amd_agp_device_ids[] =
अणु
	अणु
		.device_id	= PCI_DEVICE_ID_AMD_FE_GATE_7006,
		.chipset_name	= "Irongate",
	पूर्ण,
	अणु
		.device_id	= PCI_DEVICE_ID_AMD_FE_GATE_700E,
		.chipset_name	= "761",
	पूर्ण,
	अणु
		.device_id	= PCI_DEVICE_ID_AMD_FE_GATE_700C,
		.chipset_name	= "760MP",
	पूर्ण,
	अणु पूर्ण, /* dummy final entry, always present */
पूर्ण;

अटल पूर्णांक agp_amdk7_probe(काष्ठा pci_dev *pdev,
			   स्थिर काष्ठा pci_device_id *ent)
अणु
	काष्ठा agp_bridge_data *bridge;
	u8 cap_ptr;
	पूर्णांक j;

	cap_ptr = pci_find_capability(pdev, PCI_CAP_ID_AGP);
	अगर (!cap_ptr)
		वापस -ENODEV;

	j = ent - agp_amdk7_pci_table;
	dev_info(&pdev->dev, "AMD %s chipset\n",
		 amd_agp_device_ids[j].chipset_name);

	bridge = agp_alloc_bridge();
	अगर (!bridge)
		वापस -ENOMEM;

	bridge->driver = &amd_irongate_driver;
	bridge->dev_निजी_data = &amd_irongate_निजी;
	bridge->dev = pdev;
	bridge->capndx = cap_ptr;

	/* 751 Errata (22564_B-1.PDF)
	   erratum 20: strobe glitch with Nvidia NV10 GeForce cards.
	   प्रणाली controller may experience noise due to strong drive strengths
	 */
	अगर (agp_bridge->dev->device == PCI_DEVICE_ID_AMD_FE_GATE_7006) अणु
		काष्ठा pci_dev *gfxcard=शून्य;

		cap_ptr = 0;
		जबतक (!cap_ptr) अणु
			gfxcard = pci_get_class(PCI_CLASS_DISPLAY_VGA<<8, gfxcard);
			अगर (!gfxcard) अणु
				dev_info(&pdev->dev, "no AGP VGA controller\n");
				वापस -ENODEV;
			पूर्ण
			cap_ptr = pci_find_capability(gfxcard, PCI_CAP_ID_AGP);
		पूर्ण

		/* With so many variants of NVidia cards, it's simpler just
		   to blacklist them all, and then whitelist them as needed
		   (अगर necessary at all). */
		अगर (gfxcard->venकरोr == PCI_VENDOR_ID_NVIDIA) अणु
			agp_bridge->flags |= AGP_ERRATA_1X;
			dev_info(&pdev->dev, "AMD 751 chipset with NVidia GeForce; forcing 1X due to errata\n");
		पूर्ण
		pci_dev_put(gfxcard);
	पूर्ण

	/* 761 Errata (23613_F.pdf)
	 * Revisions B0/B1 were a disaster.
	 * erratum 44: SYSCLK/AGPCLK skew causes 2X failures -- Force mode to 1X
	 * erratum 45: Timing problem prevents fast ग_लिखोs -- Disable fast ग_लिखो.
	 * erratum 46: Setup violation on AGP SBA pins - Disable side band addressing.
	 * With this lot disabled, we should prevent lockups. */
	अगर (agp_bridge->dev->device == PCI_DEVICE_ID_AMD_FE_GATE_700E) अणु
		अगर (pdev->revision == 0x10 || pdev->revision == 0x11) अणु
			agp_bridge->flags = AGP_ERRATA_FASTWRITES;
			agp_bridge->flags |= AGP_ERRATA_SBA;
			agp_bridge->flags |= AGP_ERRATA_1X;
			dev_info(&pdev->dev, "AMD 761 chipset with errata; disabling AGP fast writes & SBA and forcing to 1X\n");
		पूर्ण
	पूर्ण

	/* Fill in the mode रेजिस्टर */
	pci_पढ़ो_config_dword(pdev,
			bridge->capndx+PCI_AGP_STATUS,
			&bridge->mode);

	pci_set_drvdata(pdev, bridge);
	वापस agp_add_bridge(bridge);
पूर्ण

अटल व्योम agp_amdk7_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा agp_bridge_data *bridge = pci_get_drvdata(pdev);

	agp_हटाओ_bridge(bridge);
	agp_put_bridge(bridge);
पूर्ण

#अगर_घोषित CONFIG_PM

अटल पूर्णांक agp_amdk7_suspend(काष्ठा pci_dev *pdev, pm_message_t state)
अणु
	pci_save_state(pdev);
	pci_set_घातer_state(pdev, pci_choose_state(pdev, state));

	वापस 0;
पूर्ण

अटल पूर्णांक agp_amdk7_resume(काष्ठा pci_dev *pdev)
अणु
	pci_set_घातer_state(pdev, PCI_D0);
	pci_restore_state(pdev);

	वापस amd_irongate_driver.configure();
पूर्ण

#पूर्ण_अगर /* CONFIG_PM */

/* must be the same order as name table above */
अटल स्थिर काष्ठा pci_device_id agp_amdk7_pci_table[] = अणु
	अणु
	.class		= (PCI_CLASS_BRIDGE_HOST << 8),
	.class_mask	= ~0,
	.venकरोr		= PCI_VENDOR_ID_AMD,
	.device		= PCI_DEVICE_ID_AMD_FE_GATE_7006,
	.subvenकरोr	= PCI_ANY_ID,
	.subdevice	= PCI_ANY_ID,
	पूर्ण,
	अणु
	.class		= (PCI_CLASS_BRIDGE_HOST << 8),
	.class_mask	= ~0,
	.venकरोr		= PCI_VENDOR_ID_AMD,
	.device		= PCI_DEVICE_ID_AMD_FE_GATE_700E,
	.subvenकरोr	= PCI_ANY_ID,
	.subdevice	= PCI_ANY_ID,
	पूर्ण,
	अणु
	.class		= (PCI_CLASS_BRIDGE_HOST << 8),
	.class_mask	= ~0,
	.venकरोr		= PCI_VENDOR_ID_AMD,
	.device		= PCI_DEVICE_ID_AMD_FE_GATE_700C,
	.subvenकरोr	= PCI_ANY_ID,
	.subdevice	= PCI_ANY_ID,
	पूर्ण,
	अणु पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, agp_amdk7_pci_table);

अटल काष्ठा pci_driver agp_amdk7_pci_driver = अणु
	.name		= "agpgart-amdk7",
	.id_table	= agp_amdk7_pci_table,
	.probe		= agp_amdk7_probe,
	.हटाओ		= agp_amdk7_हटाओ,
#अगर_घोषित CONFIG_PM
	.suspend	= agp_amdk7_suspend,
	.resume		= agp_amdk7_resume,
#पूर्ण_अगर
पूर्ण;

अटल पूर्णांक __init agp_amdk7_init(व्योम)
अणु
	अगर (agp_off)
		वापस -EINVAL;
	वापस pci_रेजिस्टर_driver(&agp_amdk7_pci_driver);
पूर्ण

अटल व्योम __निकास agp_amdk7_cleanup(व्योम)
अणु
	pci_unरेजिस्टर_driver(&agp_amdk7_pci_driver);
पूर्ण

module_init(agp_amdk7_init);
module_निकास(agp_amdk7_cleanup);

MODULE_LICENSE("GPL and additional rights");
