<शैली गुरु>
/*
 * Nvidia AGPGART routines.
 * Based upon a 2.4 agpgart dअगरf by the folks from NVIDIA, and hacked up
 * to work in 2.5 by Dave Jones.
 */

#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/init.h>
#समावेश <linux/agp_backend.h>
#समावेश <linux/page-flags.h>
#समावेश <linux/mm.h>
#समावेश <linux/jअगरfies.h>
#समावेश "agp.h"

/* NVIDIA रेजिस्टरs */
#घोषणा NVIDIA_0_APSIZE		0x80
#घोषणा NVIDIA_1_WBC		0xf0
#घोषणा NVIDIA_2_GARTCTRL	0xd0
#घोषणा NVIDIA_2_APBASE		0xd8
#घोषणा NVIDIA_2_APLIMIT	0xdc
#घोषणा NVIDIA_2_ATTBASE(i)	(0xe0 + (i) * 4)
#घोषणा NVIDIA_3_APBASE		0x50
#घोषणा NVIDIA_3_APLIMIT	0x54


अटल काष्ठा _nvidia_निजी अणु
	काष्ठा pci_dev *dev_1;
	काष्ठा pci_dev *dev_2;
	काष्ठा pci_dev *dev_3;
	अस्थिर u32 __iomem *aperture;
	पूर्णांक num_active_entries;
	off_t pg_offset;
	u32 wbc_mask;
पूर्ण nvidia_निजी;


अटल पूर्णांक nvidia_fetch_size(व्योम)
अणु
	पूर्णांक i;
	u8 size_value;
	काष्ठा aper_size_info_8 *values;

	pci_पढ़ो_config_byte(agp_bridge->dev, NVIDIA_0_APSIZE, &size_value);
	size_value &= 0x0f;
	values = A_SIZE_8(agp_bridge->driver->aperture_sizes);

	क्रम (i = 0; i < agp_bridge->driver->num_aperture_sizes; i++) अणु
		अगर (size_value == values[i].size_value) अणु
			agp_bridge->previous_size =
				agp_bridge->current_size = (व्योम *) (values + i);
			agp_bridge->aperture_size_idx = i;
			वापस values[i].size;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

#घोषणा SYSCFG          0xC0010010
#घोषणा IORR_BASE0      0xC0010016
#घोषणा IORR_MASK0      0xC0010017
#घोषणा AMD_K7_NUM_IORR 2

अटल पूर्णांक nvidia_init_iorr(u32 base, u32 size)
अणु
	u32 base_hi, base_lo;
	u32 mask_hi, mask_lo;
	u32 sys_hi, sys_lo;
	u32 iorr_addr, मुक्त_iorr_addr;

	/* Find the iorr that is alपढ़ोy used क्रम the base */
	/* If not found, determine the uppermost available iorr */
	मुक्त_iorr_addr = AMD_K7_NUM_IORR;
	क्रम (iorr_addr = 0; iorr_addr < AMD_K7_NUM_IORR; iorr_addr++) अणु
		rdmsr(IORR_BASE0 + 2 * iorr_addr, base_lo, base_hi);
		rdmsr(IORR_MASK0 + 2 * iorr_addr, mask_lo, mask_hi);

		अगर ((base_lo & 0xfffff000) == (base & 0xfffff000))
			अवरोध;

		अगर ((mask_lo & 0x00000800) == 0)
			मुक्त_iorr_addr = iorr_addr;
	पूर्ण

	अगर (iorr_addr >= AMD_K7_NUM_IORR) अणु
		iorr_addr = मुक्त_iorr_addr;
		अगर (iorr_addr >= AMD_K7_NUM_IORR)
			वापस -EINVAL;
	पूर्ण
    base_hi = 0x0;
    base_lo = (base & ~0xfff) | 0x18;
    mask_hi = 0xf;
    mask_lo = ((~(size - 1)) & 0xfffff000) | 0x800;
    wrmsr(IORR_BASE0 + 2 * iorr_addr, base_lo, base_hi);
    wrmsr(IORR_MASK0 + 2 * iorr_addr, mask_lo, mask_hi);

    rdmsr(SYSCFG, sys_lo, sys_hi);
    sys_lo |= 0x00100000;
    wrmsr(SYSCFG, sys_lo, sys_hi);

	वापस 0;
पूर्ण

अटल पूर्णांक nvidia_configure(व्योम)
अणु
	पूर्णांक i, rc, num_dirs;
	u32 apbase, aplimit;
	phys_addr_t apbase_phys;
	काष्ठा aper_size_info_8 *current_size;
	u32 temp;

	current_size = A_SIZE_8(agp_bridge->current_size);

	/* aperture size */
	pci_ग_लिखो_config_byte(agp_bridge->dev, NVIDIA_0_APSIZE,
		current_size->size_value);

	/* address to map to */
	apbase = pci_bus_address(agp_bridge->dev, AGP_APERTURE_BAR);
	agp_bridge->gart_bus_addr = apbase;
	aplimit = apbase + (current_size->size * 1024 * 1024) - 1;
	pci_ग_लिखो_config_dword(nvidia_निजी.dev_2, NVIDIA_2_APBASE, apbase);
	pci_ग_लिखो_config_dword(nvidia_निजी.dev_2, NVIDIA_2_APLIMIT, aplimit);
	pci_ग_लिखो_config_dword(nvidia_निजी.dev_3, NVIDIA_3_APBASE, apbase);
	pci_ग_लिखो_config_dword(nvidia_निजी.dev_3, NVIDIA_3_APLIMIT, aplimit);
	अगर (0 != (rc = nvidia_init_iorr(apbase, current_size->size * 1024 * 1024)))
		वापस rc;

	/* directory size is 64k */
	num_dirs = current_size->size / 64;
	nvidia_निजी.num_active_entries = current_size->num_entries;
	nvidia_निजी.pg_offset = 0;
	अगर (num_dirs == 0) अणु
		num_dirs = 1;
		nvidia_निजी.num_active_entries /= (64 / current_size->size);
		nvidia_निजी.pg_offset = (apbase & (64 * 1024 * 1024 - 1) &
			~(current_size->size * 1024 * 1024 - 1)) / PAGE_SIZE;
	पूर्ण

	/* attbase */
	क्रम (i = 0; i < 8; i++) अणु
		pci_ग_लिखो_config_dword(nvidia_निजी.dev_2, NVIDIA_2_ATTBASE(i),
			(agp_bridge->gatt_bus_addr + (i % num_dirs) * 64 * 1024) | 1);
	पूर्ण

	/* gtlb control */
	pci_पढ़ो_config_dword(nvidia_निजी.dev_2, NVIDIA_2_GARTCTRL, &temp);
	pci_ग_लिखो_config_dword(nvidia_निजी.dev_2, NVIDIA_2_GARTCTRL, temp | 0x11);

	/* gart control */
	pci_पढ़ो_config_dword(agp_bridge->dev, NVIDIA_0_APSIZE, &temp);
	pci_ग_लिखो_config_dword(agp_bridge->dev, NVIDIA_0_APSIZE, temp | 0x100);

	/* map aperture */
	apbase_phys = pci_resource_start(agp_bridge->dev, AGP_APERTURE_BAR);
	nvidia_निजी.aperture =
		(अस्थिर u32 __iomem *) ioremap(apbase_phys, 33 * PAGE_SIZE);

	अगर (!nvidia_निजी.aperture)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

अटल व्योम nvidia_cleanup(व्योम)
अणु
	काष्ठा aper_size_info_8 *previous_size;
	u32 temp;

	/* gart control */
	pci_पढ़ो_config_dword(agp_bridge->dev, NVIDIA_0_APSIZE, &temp);
	pci_ग_लिखो_config_dword(agp_bridge->dev, NVIDIA_0_APSIZE, temp & ~(0x100));

	/* gtlb control */
	pci_पढ़ो_config_dword(nvidia_निजी.dev_2, NVIDIA_2_GARTCTRL, &temp);
	pci_ग_लिखो_config_dword(nvidia_निजी.dev_2, NVIDIA_2_GARTCTRL, temp & ~(0x11));

	/* unmap aperture */
	iounmap((व्योम __iomem *) nvidia_निजी.aperture);

	/* restore previous aperture size */
	previous_size = A_SIZE_8(agp_bridge->previous_size);
	pci_ग_लिखो_config_byte(agp_bridge->dev, NVIDIA_0_APSIZE,
		previous_size->size_value);

	/* restore iorr क्रम previous aperture size */
	nvidia_init_iorr(agp_bridge->gart_bus_addr,
		previous_size->size * 1024 * 1024);
पूर्ण


/*
 * Note we can't use the generic routines, even though they are 99% the same.
 * Aperture sizes <64M still requires a full 64k GART directory, but
 * only use the portion of the TLB entries that correspond to the apertures
 * alignment inside the surrounding 64M block.
 */
बाह्य पूर्णांक agp_memory_reserved;

अटल पूर्णांक nvidia_insert_memory(काष्ठा agp_memory *mem, off_t pg_start, पूर्णांक type)
अणु
	पूर्णांक i, j;
	पूर्णांक mask_type;

	mask_type = agp_generic_type_to_mask_type(mem->bridge, type);
	अगर (mask_type != 0 || type != mem->type)
		वापस -EINVAL;

	अगर (mem->page_count == 0)
		वापस 0;

	अगर ((pg_start + mem->page_count) >
		(nvidia_निजी.num_active_entries - agp_memory_reserved/PAGE_SIZE))
		वापस -EINVAL;

	क्रम (j = pg_start; j < (pg_start + mem->page_count); j++) अणु
		अगर (!PGE_EMPTY(agp_bridge, पढ़ोl(agp_bridge->gatt_table+nvidia_निजी.pg_offset+j)))
			वापस -EBUSY;
	पूर्ण

	अगर (!mem->is_flushed) अणु
		global_cache_flush();
		mem->is_flushed = true;
	पूर्ण
	क्रम (i = 0, j = pg_start; i < mem->page_count; i++, j++) अणु
		ग_लिखोl(agp_bridge->driver->mask_memory(agp_bridge,
			       page_to_phys(mem->pages[i]), mask_type),
			agp_bridge->gatt_table+nvidia_निजी.pg_offset+j);
	पूर्ण

	/* PCI Posting. */
	पढ़ोl(agp_bridge->gatt_table+nvidia_निजी.pg_offset+j - 1);

	agp_bridge->driver->tlb_flush(mem);
	वापस 0;
पूर्ण


अटल पूर्णांक nvidia_हटाओ_memory(काष्ठा agp_memory *mem, off_t pg_start, पूर्णांक type)
अणु
	पूर्णांक i;

	पूर्णांक mask_type;

	mask_type = agp_generic_type_to_mask_type(mem->bridge, type);
	अगर (mask_type != 0 || type != mem->type)
		वापस -EINVAL;

	अगर (mem->page_count == 0)
		वापस 0;

	क्रम (i = pg_start; i < (mem->page_count + pg_start); i++)
		ग_लिखोl(agp_bridge->scratch_page, agp_bridge->gatt_table+nvidia_निजी.pg_offset+i);

	agp_bridge->driver->tlb_flush(mem);
	वापस 0;
पूर्ण


अटल व्योम nvidia_tlbflush(काष्ठा agp_memory *mem)
अणु
	अचिन्हित दीर्घ end;
	u32 wbc_reg, temp;
	पूर्णांक i;

	/* flush chipset */
	अगर (nvidia_निजी.wbc_mask) अणु
		pci_पढ़ो_config_dword(nvidia_निजी.dev_1, NVIDIA_1_WBC, &wbc_reg);
		wbc_reg |= nvidia_निजी.wbc_mask;
		pci_ग_लिखो_config_dword(nvidia_निजी.dev_1, NVIDIA_1_WBC, wbc_reg);

		end = jअगरfies + 3*HZ;
		करो अणु
			pci_पढ़ो_config_dword(nvidia_निजी.dev_1,
					NVIDIA_1_WBC, &wbc_reg);
			अगर (समय_beक्रमe_eq(end, jअगरfies)) अणु
				prपूर्णांकk(KERN_ERR PFX
				    "TLB flush took more than 3 seconds.\n");
			पूर्ण
		पूर्ण जबतक (wbc_reg & nvidia_निजी.wbc_mask);
	पूर्ण

	/* flush TLB entries */
	क्रम (i = 0; i < 32 + 1; i++)
		temp = पढ़ोl(nvidia_निजी.aperture+(i * PAGE_SIZE / माप(u32)));
	क्रम (i = 0; i < 32 + 1; i++)
		temp = पढ़ोl(nvidia_निजी.aperture+(i * PAGE_SIZE / माप(u32)));
पूर्ण


अटल स्थिर काष्ठा aper_size_info_8 nvidia_generic_sizes[5] =
अणु
	अणु512, 131072, 7, 0पूर्ण,
	अणु256, 65536, 6, 8पूर्ण,
	अणु128, 32768, 5, 12पूर्ण,
	अणु64, 16384, 4, 14पूर्ण,
	/* The 32M mode still requires a 64k gatt */
	अणु32, 16384, 4, 15पूर्ण
पूर्ण;


अटल स्थिर काष्ठा gatt_mask nvidia_generic_masks[] =
अणु
	अणु .mask = 1, .type = 0पूर्ण
पूर्ण;


अटल स्थिर काष्ठा agp_bridge_driver nvidia_driver = अणु
	.owner			= THIS_MODULE,
	.aperture_sizes		= nvidia_generic_sizes,
	.माप_प्रकारype		= U8_APER_SIZE,
	.num_aperture_sizes	= 5,
	.needs_scratch_page	= true,
	.configure		= nvidia_configure,
	.fetch_size		= nvidia_fetch_size,
	.cleanup		= nvidia_cleanup,
	.tlb_flush		= nvidia_tlbflush,
	.mask_memory		= agp_generic_mask_memory,
	.masks			= nvidia_generic_masks,
	.agp_enable		= agp_generic_enable,
	.cache_flush		= global_cache_flush,
	.create_gatt_table	= agp_generic_create_gatt_table,
	.मुक्त_gatt_table	= agp_generic_मुक्त_gatt_table,
	.insert_memory		= nvidia_insert_memory,
	.हटाओ_memory		= nvidia_हटाओ_memory,
	.alloc_by_type		= agp_generic_alloc_by_type,
	.मुक्त_by_type		= agp_generic_मुक्त_by_type,
	.agp_alloc_page		= agp_generic_alloc_page,
	.agp_alloc_pages	= agp_generic_alloc_pages,
	.agp_destroy_page	= agp_generic_destroy_page,
	.agp_destroy_pages	= agp_generic_destroy_pages,
	.agp_type_to_mask_type  = agp_generic_type_to_mask_type,
पूर्ण;

अटल पूर्णांक agp_nvidia_probe(काष्ठा pci_dev *pdev,
			    स्थिर काष्ठा pci_device_id *ent)
अणु
	काष्ठा agp_bridge_data *bridge;
	u8 cap_ptr;

	nvidia_निजी.dev_1 =
		pci_get_करोमुख्य_bus_and_slot(pci_करोमुख्य_nr(pdev->bus),
					    (अचिन्हित पूर्णांक)pdev->bus->number,
					    PCI_DEVFN(0, 1));
	nvidia_निजी.dev_2 =
		pci_get_करोमुख्य_bus_and_slot(pci_करोमुख्य_nr(pdev->bus),
					    (अचिन्हित पूर्णांक)pdev->bus->number,
					    PCI_DEVFN(0, 2));
	nvidia_निजी.dev_3 =
		pci_get_करोमुख्य_bus_and_slot(pci_करोमुख्य_nr(pdev->bus),
					    (अचिन्हित पूर्णांक)pdev->bus->number,
					    PCI_DEVFN(30, 0));

	अगर (!nvidia_निजी.dev_1 || !nvidia_निजी.dev_2 || !nvidia_निजी.dev_3) अणु
		prपूर्णांकk(KERN_INFO PFX "Detected an NVIDIA nForce/nForce2 "
			"chipset, but could not find the secondary devices.\n");
		वापस -ENODEV;
	पूर्ण

	cap_ptr = pci_find_capability(pdev, PCI_CAP_ID_AGP);
	अगर (!cap_ptr)
		वापस -ENODEV;

	चयन (pdev->device) अणु
	हाल PCI_DEVICE_ID_NVIDIA_NFORCE:
		prपूर्णांकk(KERN_INFO PFX "Detected NVIDIA nForce chipset\n");
		nvidia_निजी.wbc_mask = 0x00010000;
		अवरोध;
	हाल PCI_DEVICE_ID_NVIDIA_NFORCE2:
		prपूर्णांकk(KERN_INFO PFX "Detected NVIDIA nForce2 chipset\n");
		nvidia_निजी.wbc_mask = 0x80000000;
		अवरोध;
	शेष:
		prपूर्णांकk(KERN_ERR PFX "Unsupported NVIDIA chipset (device id: %04x)\n",
			    pdev->device);
		वापस -ENODEV;
	पूर्ण

	bridge = agp_alloc_bridge();
	अगर (!bridge)
		वापस -ENOMEM;

	bridge->driver = &nvidia_driver;
	bridge->dev_निजी_data = &nvidia_निजी;
	bridge->dev = pdev;
	bridge->capndx = cap_ptr;

	/* Fill in the mode रेजिस्टर */
	pci_पढ़ो_config_dword(pdev,
			bridge->capndx+PCI_AGP_STATUS,
			&bridge->mode);

	pci_set_drvdata(pdev, bridge);
	वापस agp_add_bridge(bridge);
पूर्ण

अटल व्योम agp_nvidia_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा agp_bridge_data *bridge = pci_get_drvdata(pdev);

	agp_हटाओ_bridge(bridge);
	agp_put_bridge(bridge);
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक agp_nvidia_suspend(काष्ठा pci_dev *pdev, pm_message_t state)
अणु
	pci_save_state(pdev);
	pci_set_घातer_state(pdev, PCI_D3hot);

	वापस 0;
पूर्ण

अटल पूर्णांक agp_nvidia_resume(काष्ठा pci_dev *pdev)
अणु
	/* set घातer state 0 and restore PCI space */
	pci_set_घातer_state(pdev, PCI_D0);
	pci_restore_state(pdev);

	/* reconfigure AGP hardware again */
	nvidia_configure();

	वापस 0;
पूर्ण
#पूर्ण_अगर


अटल स्थिर काष्ठा pci_device_id agp_nvidia_pci_table[] = अणु
	अणु
	.class		= (PCI_CLASS_BRIDGE_HOST << 8),
	.class_mask	= ~0,
	.venकरोr		= PCI_VENDOR_ID_NVIDIA,
	.device		= PCI_DEVICE_ID_NVIDIA_NFORCE,
	.subvenकरोr	= PCI_ANY_ID,
	.subdevice	= PCI_ANY_ID,
	पूर्ण,
	अणु
	.class		= (PCI_CLASS_BRIDGE_HOST << 8),
	.class_mask	= ~0,
	.venकरोr		= PCI_VENDOR_ID_NVIDIA,
	.device		= PCI_DEVICE_ID_NVIDIA_NFORCE2,
	.subvenकरोr	= PCI_ANY_ID,
	.subdevice	= PCI_ANY_ID,
	पूर्ण,
	अणु पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, agp_nvidia_pci_table);

अटल काष्ठा pci_driver agp_nvidia_pci_driver = अणु
	.name		= "agpgart-nvidia",
	.id_table	= agp_nvidia_pci_table,
	.probe		= agp_nvidia_probe,
	.हटाओ		= agp_nvidia_हटाओ,
#अगर_घोषित CONFIG_PM
	.suspend	= agp_nvidia_suspend,
	.resume		= agp_nvidia_resume,
#पूर्ण_अगर
पूर्ण;

अटल पूर्णांक __init agp_nvidia_init(व्योम)
अणु
	अगर (agp_off)
		वापस -EINVAL;
	वापस pci_रेजिस्टर_driver(&agp_nvidia_pci_driver);
पूर्ण

अटल व्योम __निकास agp_nvidia_cleanup(व्योम)
अणु
	pci_unरेजिस्टर_driver(&agp_nvidia_pci_driver);
	pci_dev_put(nvidia_निजी.dev_1);
	pci_dev_put(nvidia_निजी.dev_2);
	pci_dev_put(nvidia_निजी.dev_3);
पूर्ण

module_init(agp_nvidia_init);
module_निकास(agp_nvidia_cleanup);

MODULE_LICENSE("GPL and additional rights");
MODULE_AUTHOR("NVIDIA Corporation");

