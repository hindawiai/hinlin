<शैली गुरु>
/*
 * Transmeta's Efficeon AGPGART driver.
 *
 * Based upon a dअगरf by Linus around November '02.
 *
 * Ported to the 2.6 kernel by Carlos Puchol <cpglinux@puchol.com>
 * and H. Peter Anvin <hpa@transmeta.com>.
 */

/*
 * NOTE-cpg-040217:
 *
 *   - when compiled as a module, after loading the module,
 *     it will refuse to unload, indicating it is in use,
 *     when it is not.
 *   - no s3 (suspend to ram) testing.
 *   - tested on the efficeon पूर्णांकegrated nothbridge क्रम tens
 *     of iterations of starting x and glxgears.
 *   - tested with radeon 9000 and radeon mobility m9 cards
 *   - tested with c3/c4 enabled (with the mobility m9 card)
 */

#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/init.h>
#समावेश <linux/agp_backend.h>
#समावेश <linux/gfp.h>
#समावेश <linux/page-flags.h>
#समावेश <linux/mm.h>
#समावेश "agp.h"
#समावेश "intel-agp.h"

/*
 * The real dअगरferences to the generic AGP code is
 * in the GART mappings - a two-level setup with the
 * first level being an on-chip 64-entry table.
 *
 * The page array is filled through the ATTPAGE रेजिस्टर
 * (Aperture Translation Table Page Register) at 0xB8. Bits:
 *  31:20: physical page address
 *   11:9: Page Attribute Table Index (PATI)
 *	   must match the PAT index क्रम the
 *	   mapped pages (the 2nd level page table pages
 *	   themselves should be just regular WB-cacheable,
 *	   so this is normally zero.)
 *      8: Present
 *    7:6: reserved, ग_लिखो as zero
 *    5:0: GATT directory index: which 1st-level entry
 *
 * The Efficeon AGP spec requires pages to be WB-cacheable
 * but to be explicitly CLFLUSH'd after any changes.
 */
#घोषणा EFFICEON_ATTPAGE	0xb8
#घोषणा EFFICEON_L1_SIZE	64	/* Number of PDE pages */

#घोषणा EFFICEON_PATI		(0 << 9)
#घोषणा EFFICEON_PRESENT	(1 << 8)

अटल काष्ठा _efficeon_निजी अणु
	अचिन्हित दीर्घ l1_table[EFFICEON_L1_SIZE];
पूर्ण efficeon_निजी;

अटल स्थिर काष्ठा gatt_mask efficeon_generic_masks[] =
अणु
	अणु.mask = 0x00000001, .type = 0पूर्ण
पूर्ण;

/* This function करोes the same thing as mask_memory() क्रम this chipset... */
अटल अंतरभूत अचिन्हित दीर्घ efficeon_mask_memory(काष्ठा page *page)
अणु
	अचिन्हित दीर्घ addr = page_to_phys(page);
	वापस addr | 0x00000001;
पूर्ण

अटल स्थिर काष्ठा aper_size_info_lvl2 efficeon_generic_sizes[4] =
अणु
	अणु256, 65536, 0पूर्ण,
	अणु128, 32768, 32पूर्ण,
	अणु64, 16384, 48पूर्ण,
	अणु32, 8192, 56पूर्ण
पूर्ण;

/*
 * Control पूर्णांकerfaces are largely identical to
 * the legacy Intel 440BX..
 */

अटल पूर्णांक efficeon_fetch_size(व्योम)
अणु
	पूर्णांक i;
	u16 temp;
	काष्ठा aper_size_info_lvl2 *values;

	pci_पढ़ो_config_word(agp_bridge->dev, INTEL_APSIZE, &temp);
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

अटल व्योम efficeon_tlbflush(काष्ठा agp_memory * mem)
अणु
	prपूर्णांकk(KERN_DEBUG PFX "efficeon_tlbflush()\n");
	pci_ग_लिखो_config_dword(agp_bridge->dev, INTEL_AGPCTRL, 0x2200);
	pci_ग_लिखो_config_dword(agp_bridge->dev, INTEL_AGPCTRL, 0x2280);
पूर्ण

अटल व्योम efficeon_cleanup(व्योम)
अणु
	u16 temp;
	काष्ठा aper_size_info_lvl2 *previous_size;

	prपूर्णांकk(KERN_DEBUG PFX "efficeon_cleanup()\n");
	previous_size = A_SIZE_LVL2(agp_bridge->previous_size);
	pci_पढ़ो_config_word(agp_bridge->dev, INTEL_NBXCFG, &temp);
	pci_ग_लिखो_config_word(agp_bridge->dev, INTEL_NBXCFG, temp & ~(1 << 9));
	pci_ग_लिखो_config_word(agp_bridge->dev, INTEL_APSIZE,
			      previous_size->size_value);
पूर्ण

अटल पूर्णांक efficeon_configure(व्योम)
अणु
	u16 temp2;
	काष्ठा aper_size_info_lvl2 *current_size;

	prपूर्णांकk(KERN_DEBUG PFX "efficeon_configure()\n");

	current_size = A_SIZE_LVL2(agp_bridge->current_size);

	/* aperture size */
	pci_ग_लिखो_config_word(agp_bridge->dev, INTEL_APSIZE,
			      current_size->size_value);

	/* address to map to */
	agp_bridge->gart_bus_addr = pci_bus_address(agp_bridge->dev,
						    AGP_APERTURE_BAR);

	/* agpctrl */
	pci_ग_लिखो_config_dword(agp_bridge->dev, INTEL_AGPCTRL, 0x2280);

	/* paccfg/nbxcfg */
	pci_पढ़ो_config_word(agp_bridge->dev, INTEL_NBXCFG, &temp2);
	pci_ग_लिखो_config_word(agp_bridge->dev, INTEL_NBXCFG,
			      (temp2 & ~(1 << 10)) | (1 << 9) | (1 << 11));
	/* clear any possible error conditions */
	pci_ग_लिखो_config_byte(agp_bridge->dev, INTEL_ERRSTS + 1, 7);
	वापस 0;
पूर्ण

अटल पूर्णांक efficeon_मुक्त_gatt_table(काष्ठा agp_bridge_data *bridge)
अणु
	पूर्णांक index, मुक्तd = 0;

	क्रम (index = 0; index < EFFICEON_L1_SIZE; index++) अणु
		अचिन्हित दीर्घ page = efficeon_निजी.l1_table[index];
		अगर (page) अणु
			efficeon_निजी.l1_table[index] = 0;
			मुक्त_page(page);
			मुक्तd++;
		पूर्ण
		prपूर्णांकk(KERN_DEBUG PFX "efficeon_free_gatt_table(%p, %02x, %08x)\n",
			agp_bridge->dev, EFFICEON_ATTPAGE, index);
		pci_ग_लिखो_config_dword(agp_bridge->dev,
			EFFICEON_ATTPAGE, index);
	पूर्ण
	prपूर्णांकk(KERN_DEBUG PFX "efficeon_free_gatt_table() freed %d pages\n", मुक्तd);
	वापस 0;
पूर्ण


/*
 * Since we करोn't need contiguous memory we just try
 * to get the gatt table once
 */

#घोषणा GET_PAGE_सूची_OFF(addr) (addr >> 22)
#घोषणा GET_PAGE_सूची_IDX(addr) (GET_PAGE_सूची_OFF(addr) - \
	GET_PAGE_सूची_OFF(agp_bridge->gart_bus_addr))
#घोषणा GET_GATT_OFF(addr) ((addr & 0x003ff000) >> 12)
#अघोषित  GET_GATT
#घोषणा GET_GATT(addr) (efficeon_निजी.gatt_pages[\
	GET_PAGE_सूची_IDX(addr)]->remapped)

अटल पूर्णांक efficeon_create_gatt_table(काष्ठा agp_bridge_data *bridge)
अणु
	पूर्णांक index;
	स्थिर पूर्णांक pati    = EFFICEON_PATI;
	स्थिर पूर्णांक present = EFFICEON_PRESENT;
	स्थिर पूर्णांक clflush_chunk = ((cpuid_ebx(1) >> 8) & 0xff) << 3;
	पूर्णांक num_entries, l1_pages;

	num_entries = A_SIZE_LVL2(agp_bridge->current_size)->num_entries;

	prपूर्णांकk(KERN_DEBUG PFX "efficeon_create_gatt_table(%d)\n", num_entries);

	/* There are 2^10 PTE pages per PDE page */
	BUG_ON(num_entries & 0x3ff);
	l1_pages = num_entries >> 10;

	क्रम (index = 0 ; index < l1_pages ; index++) अणु
		पूर्णांक offset;
		अचिन्हित दीर्घ page;
		अचिन्हित दीर्घ value;

		page = efficeon_निजी.l1_table[index];
		BUG_ON(page);

		page = get_zeroed_page(GFP_KERNEL);
		अगर (!page) अणु
			efficeon_मुक्त_gatt_table(agp_bridge);
			वापस -ENOMEM;
		पूर्ण

		क्रम (offset = 0; offset < PAGE_SIZE; offset += clflush_chunk)
			clflush((अक्षर *)page+offset);

		efficeon_निजी.l1_table[index] = page;

		value = virt_to_phys((अचिन्हित दीर्घ *)page) | pati | present | index;

		pci_ग_लिखो_config_dword(agp_bridge->dev,
			EFFICEON_ATTPAGE, value);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक efficeon_insert_memory(काष्ठा agp_memory * mem, off_t pg_start, पूर्णांक type)
अणु
	पूर्णांक i, count = mem->page_count, num_entries;
	अचिन्हित पूर्णांक *page, *last_page;
	स्थिर पूर्णांक clflush_chunk = ((cpuid_ebx(1) >> 8) & 0xff) << 3;
	स्थिर अचिन्हित दीर्घ clflush_mask = ~(clflush_chunk-1);

	prपूर्णांकk(KERN_DEBUG PFX "efficeon_insert_memory(%lx, %d)\n", pg_start, count);

	num_entries = A_SIZE_LVL2(agp_bridge->current_size)->num_entries;
	अगर ((pg_start + mem->page_count) > num_entries)
		वापस -EINVAL;
	अगर (type != 0 || mem->type != 0)
		वापस -EINVAL;

	अगर (!mem->is_flushed) अणु
		global_cache_flush();
		mem->is_flushed = true;
	पूर्ण

	last_page = शून्य;
	क्रम (i = 0; i < count; i++) अणु
		पूर्णांक index = pg_start + i;
		अचिन्हित दीर्घ insert = efficeon_mask_memory(mem->pages[i]);

		page = (अचिन्हित पूर्णांक *) efficeon_निजी.l1_table[index >> 10];

		अगर (!page)
			जारी;

		page += (index & 0x3ff);
		*page = insert;

		/* clflush is slow, so करोn't clflush until we have to */
		अगर (last_page &&
		    (((अचिन्हित दीर्घ)page^(अचिन्हित दीर्घ)last_page) &
		     clflush_mask))
			clflush(last_page);

		last_page = page;
	पूर्ण

	अगर ( last_page )
		clflush(last_page);

	agp_bridge->driver->tlb_flush(mem);
	वापस 0;
पूर्ण

अटल पूर्णांक efficeon_हटाओ_memory(काष्ठा agp_memory * mem, off_t pg_start, पूर्णांक type)
अणु
	पूर्णांक i, count = mem->page_count, num_entries;

	prपूर्णांकk(KERN_DEBUG PFX "efficeon_remove_memory(%lx, %d)\n", pg_start, count);

	num_entries = A_SIZE_LVL2(agp_bridge->current_size)->num_entries;

	अगर ((pg_start + mem->page_count) > num_entries)
		वापस -EINVAL;
	अगर (type != 0 || mem->type != 0)
		वापस -EINVAL;

	क्रम (i = 0; i < count; i++) अणु
		पूर्णांक index = pg_start + i;
		अचिन्हित पूर्णांक *page = (अचिन्हित पूर्णांक *) efficeon_निजी.l1_table[index >> 10];

		अगर (!page)
			जारी;
		page += (index & 0x3ff);
		*page = 0;
	पूर्ण
	agp_bridge->driver->tlb_flush(mem);
	वापस 0;
पूर्ण


अटल स्थिर काष्ठा agp_bridge_driver efficeon_driver = अणु
	.owner			= THIS_MODULE,
	.aperture_sizes		= efficeon_generic_sizes,
	.माप_प्रकारype		= LVL2_APER_SIZE,
	.num_aperture_sizes	= 4,
	.configure		= efficeon_configure,
	.fetch_size		= efficeon_fetch_size,
	.cleanup		= efficeon_cleanup,
	.tlb_flush		= efficeon_tlbflush,
	.mask_memory		= agp_generic_mask_memory,
	.masks			= efficeon_generic_masks,
	.agp_enable		= agp_generic_enable,
	.cache_flush		= global_cache_flush,

	// Efficeon-specअगरic GATT table setup / populate / tearकरोwn
	.create_gatt_table	= efficeon_create_gatt_table,
	.मुक्त_gatt_table	= efficeon_मुक्त_gatt_table,
	.insert_memory		= efficeon_insert_memory,
	.हटाओ_memory		= efficeon_हटाओ_memory,
	.cant_use_aperture	= false,	// true might be faster?

	// Generic
	.alloc_by_type		= agp_generic_alloc_by_type,
	.मुक्त_by_type		= agp_generic_मुक्त_by_type,
	.agp_alloc_page		= agp_generic_alloc_page,
	.agp_alloc_pages	= agp_generic_alloc_pages,
	.agp_destroy_page	= agp_generic_destroy_page,
	.agp_destroy_pages	= agp_generic_destroy_pages,
	.agp_type_to_mask_type  = agp_generic_type_to_mask_type,
पूर्ण;

अटल पूर्णांक agp_efficeon_probe(काष्ठा pci_dev *pdev,
			      स्थिर काष्ठा pci_device_id *ent)
अणु
	काष्ठा agp_bridge_data *bridge;
	u8 cap_ptr;
	काष्ठा resource *r;

	cap_ptr = pci_find_capability(pdev, PCI_CAP_ID_AGP);
	अगर (!cap_ptr)
		वापस -ENODEV;

	/* Probe क्रम Efficeon controller */
	अगर (pdev->device != PCI_DEVICE_ID_EFFICEON) अणु
		prपूर्णांकk(KERN_ERR PFX "Unsupported Efficeon chipset (device id: %04x)\n",
		    pdev->device);
		वापस -ENODEV;
	पूर्ण

	prपूर्णांकk(KERN_INFO PFX "Detected Transmeta Efficeon TM8000 series chipset\n");

	bridge = agp_alloc_bridge();
	अगर (!bridge)
		वापस -ENOMEM;

	bridge->driver = &efficeon_driver;
	bridge->dev = pdev;
	bridge->capndx = cap_ptr;

	/*
	* If the device has not been properly setup, the following will catch
	* the problem and should stop the प्रणाली from crashing.
	* 20030610 - hamish@zot.org
	*/
	अगर (pci_enable_device(pdev)) अणु
		prपूर्णांकk(KERN_ERR PFX "Unable to Enable PCI device\n");
		agp_put_bridge(bridge);
		वापस -ENODEV;
	पूर्ण

	/*
	* The following fixes the हाल where the BIOS has "forgotten" to
	* provide an address range क्रम the GART.
	* 20030610 - hamish@zot.org
	*/
	r = &pdev->resource[0];
	अगर (!r->start && r->end) अणु
		अगर (pci_assign_resource(pdev, 0)) अणु
			prपूर्णांकk(KERN_ERR PFX "could not assign resource 0\n");
			agp_put_bridge(bridge);
			वापस -ENODEV;
		पूर्ण
	पूर्ण

	/* Fill in the mode रेजिस्टर */
	अगर (cap_ptr) अणु
		pci_पढ़ो_config_dword(pdev,
				bridge->capndx+PCI_AGP_STATUS,
				&bridge->mode);
	पूर्ण

	pci_set_drvdata(pdev, bridge);
	वापस agp_add_bridge(bridge);
पूर्ण

अटल व्योम agp_efficeon_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा agp_bridge_data *bridge = pci_get_drvdata(pdev);

	agp_हटाओ_bridge(bridge);
	agp_put_bridge(bridge);
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक agp_efficeon_suspend(काष्ठा pci_dev *dev, pm_message_t state)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक agp_efficeon_resume(काष्ठा pci_dev *pdev)
अणु
	prपूर्णांकk(KERN_DEBUG PFX "agp_efficeon_resume()\n");
	वापस efficeon_configure();
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा pci_device_id agp_efficeon_pci_table[] = अणु
	अणु
	.class		= (PCI_CLASS_BRIDGE_HOST << 8),
	.class_mask	= ~0,
	.venकरोr		= PCI_VENDOR_ID_TRANSMETA,
	.device		= PCI_ANY_ID,
	.subvenकरोr	= PCI_ANY_ID,
	.subdevice	= PCI_ANY_ID,
	पूर्ण,
	अणु पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, agp_efficeon_pci_table);

अटल काष्ठा pci_driver agp_efficeon_pci_driver = अणु
	.name		= "agpgart-efficeon",
	.id_table	= agp_efficeon_pci_table,
	.probe		= agp_efficeon_probe,
	.हटाओ		= agp_efficeon_हटाओ,
#अगर_घोषित CONFIG_PM
	.suspend	= agp_efficeon_suspend,
	.resume		= agp_efficeon_resume,
#पूर्ण_अगर
पूर्ण;

अटल पूर्णांक __init agp_efficeon_init(व्योम)
अणु
	अटल पूर्णांक agp_initialised=0;

	अगर (agp_off)
		वापस -EINVAL;

	अगर (agp_initialised == 1)
		वापस 0;
	agp_initialised=1;

	वापस pci_रेजिस्टर_driver(&agp_efficeon_pci_driver);
पूर्ण

अटल व्योम __निकास agp_efficeon_cleanup(व्योम)
अणु
	pci_unरेजिस्टर_driver(&agp_efficeon_pci_driver);
पूर्ण

module_init(agp_efficeon_init);
module_निकास(agp_efficeon_cleanup);

MODULE_AUTHOR("Carlos Puchol <cpglinux@puchol.com>");
MODULE_LICENSE("GPL and additional rights");
