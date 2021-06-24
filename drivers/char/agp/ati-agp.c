<शैली गुरु>
/*
 * ATi AGPGART routines.
 */

#समावेश <linux/types.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/init.h>
#समावेश <linux/माला.स>
#समावेश <linux/slab.h>
#समावेश <linux/agp_backend.h>
#समावेश <यंत्र/agp.h>
#समावेश <यंत्र/set_memory.h>
#समावेश "agp.h"

#घोषणा ATI_GART_MMBASE_BAR	1
#घोषणा ATI_RS100_APSIZE	0xac
#घोषणा ATI_RS100_IG_AGPMODE	0xb0
#घोषणा ATI_RS300_APSIZE	0xf8
#घोषणा ATI_RS300_IG_AGPMODE	0xfc
#घोषणा ATI_GART_FEATURE_ID		0x00
#घोषणा ATI_GART_BASE			0x04
#घोषणा ATI_GART_CACHE_SZBASE		0x08
#घोषणा ATI_GART_CACHE_CNTRL		0x0c
#घोषणा ATI_GART_CACHE_ENTRY_CNTRL	0x10


अटल स्थिर काष्ठा aper_size_info_lvl2 ati_generic_sizes[7] =
अणु
	अणु2048, 524288, 0x0000000cपूर्ण,
	अणु1024, 262144, 0x0000000aपूर्ण,
	अणु512, 131072, 0x00000008पूर्ण,
	अणु256, 65536, 0x00000006पूर्ण,
	अणु128, 32768, 0x00000004पूर्ण,
	अणु64, 16384, 0x00000002पूर्ण,
	अणु32, 8192, 0x00000000पूर्ण
पूर्ण;

अटल काष्ठा gatt_mask ati_generic_masks[] =
अणु
	अणु .mask = 1, .type = 0पूर्ण
पूर्ण;


काष्ठा ati_page_map अणु
	अचिन्हित दीर्घ *real;
	अचिन्हित दीर्घ __iomem *remapped;
पूर्ण;

अटल काष्ठा _ati_generic_निजी अणु
	अस्थिर u8 __iomem *रेजिस्टरs;
	काष्ठा ati_page_map **gatt_pages;
	पूर्णांक num_tables;
पूर्ण ati_generic_निजी;

अटल पूर्णांक ati_create_page_map(काष्ठा ati_page_map *page_map)
अणु
	पूर्णांक i, err = 0;

	page_map->real = (अचिन्हित दीर्घ *) __get_मुक्त_page(GFP_KERNEL);
	अगर (page_map->real == शून्य)
		वापस -ENOMEM;

	set_memory_uc((अचिन्हित दीर्घ)page_map->real, 1);
	err = map_page_पूर्णांकo_agp(virt_to_page(page_map->real));
	page_map->remapped = page_map->real;

	क्रम (i = 0; i < PAGE_SIZE / माप(अचिन्हित दीर्घ); i++) अणु
		ग_लिखोl(agp_bridge->scratch_page, page_map->remapped+i);
		पढ़ोl(page_map->remapped+i);	/* PCI Posting. */
	पूर्ण

	वापस 0;
पूर्ण


अटल व्योम ati_मुक्त_page_map(काष्ठा ati_page_map *page_map)
अणु
	unmap_page_from_agp(virt_to_page(page_map->real));
	set_memory_wb((अचिन्हित दीर्घ)page_map->real, 1);
	मुक्त_page((अचिन्हित दीर्घ) page_map->real);
पूर्ण


अटल व्योम ati_मुक्त_gatt_pages(व्योम)
अणु
	पूर्णांक i;
	काष्ठा ati_page_map **tables;
	काष्ठा ati_page_map *entry;

	tables = ati_generic_निजी.gatt_pages;
	क्रम (i = 0; i < ati_generic_निजी.num_tables; i++) अणु
		entry = tables[i];
		अगर (entry != शून्य) अणु
			अगर (entry->real != शून्य)
				ati_मुक्त_page_map(entry);
			kमुक्त(entry);
		पूर्ण
	पूर्ण
	kमुक्त(tables);
पूर्ण


अटल पूर्णांक ati_create_gatt_pages(पूर्णांक nr_tables)
अणु
	काष्ठा ati_page_map **tables;
	काष्ठा ati_page_map *entry;
	पूर्णांक retval = 0;
	पूर्णांक i;

	tables = kसुस्मृति(nr_tables + 1, माप(काष्ठा ati_page_map *),
			 GFP_KERNEL);
	अगर (tables == शून्य)
		वापस -ENOMEM;

	क्रम (i = 0; i < nr_tables; i++) अणु
		entry = kzalloc(माप(काष्ठा ati_page_map), GFP_KERNEL);
		tables[i] = entry;
		अगर (entry == शून्य) अणु
			retval = -ENOMEM;
			अवरोध;
		पूर्ण
		retval = ati_create_page_map(entry);
		अगर (retval != 0)
			अवरोध;
	पूर्ण
	ati_generic_निजी.num_tables = i;
	ati_generic_निजी.gatt_pages = tables;

	अगर (retval != 0)
		ati_मुक्त_gatt_pages();

	वापस retval;
पूर्ण

अटल पूर्णांक is_r200(व्योम)
अणु
	अगर ((agp_bridge->dev->device == PCI_DEVICE_ID_ATI_RS100) ||
	    (agp_bridge->dev->device == PCI_DEVICE_ID_ATI_RS200) ||
	    (agp_bridge->dev->device == PCI_DEVICE_ID_ATI_RS200_B) ||
	    (agp_bridge->dev->device == PCI_DEVICE_ID_ATI_RS250))
		वापस 1;
	वापस 0;
पूर्ण

अटल पूर्णांक ati_fetch_size(व्योम)
अणु
	पूर्णांक i;
	u32 temp;
	काष्ठा aper_size_info_lvl2 *values;

	अगर (is_r200())
		pci_पढ़ो_config_dword(agp_bridge->dev, ATI_RS100_APSIZE, &temp);
	अन्यथा
		pci_पढ़ो_config_dword(agp_bridge->dev, ATI_RS300_APSIZE, &temp);

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

अटल व्योम ati_tlbflush(काष्ठा agp_memory * mem)
अणु
	ग_लिखोl(1, ati_generic_निजी.रेजिस्टरs+ATI_GART_CACHE_CNTRL);
	पढ़ोl(ati_generic_निजी.रेजिस्टरs+ATI_GART_CACHE_CNTRL);	/* PCI Posting. */
पूर्ण

अटल व्योम ati_cleanup(व्योम)
अणु
	काष्ठा aper_size_info_lvl2 *previous_size;
	u32 temp;

	previous_size = A_SIZE_LVL2(agp_bridge->previous_size);

	/* Write back the previous size and disable gart translation */
	अगर (is_r200()) अणु
		pci_पढ़ो_config_dword(agp_bridge->dev, ATI_RS100_APSIZE, &temp);
		temp = ((temp & ~(0x0000000f)) | previous_size->size_value);
		pci_ग_लिखो_config_dword(agp_bridge->dev, ATI_RS100_APSIZE, temp);
	पूर्ण अन्यथा अणु
		pci_पढ़ो_config_dword(agp_bridge->dev, ATI_RS300_APSIZE, &temp);
		temp = ((temp & ~(0x0000000f)) | previous_size->size_value);
		pci_ग_लिखो_config_dword(agp_bridge->dev, ATI_RS300_APSIZE, temp);
	पूर्ण
	iounmap((अस्थिर u8 __iomem *)ati_generic_निजी.रेजिस्टरs);
पूर्ण


अटल पूर्णांक ati_configure(व्योम)
अणु
	phys_addr_t reg;
	u32 temp;

	/* Get the memory mapped रेजिस्टरs */
	reg = pci_resource_start(agp_bridge->dev, ATI_GART_MMBASE_BAR);
	ati_generic_निजी.रेजिस्टरs = (अस्थिर u8 __iomem *) ioremap(reg, 4096);

	अगर (!ati_generic_निजी.रेजिस्टरs)
		वापस -ENOMEM;

	अगर (is_r200())
		pci_ग_लिखो_config_dword(agp_bridge->dev, ATI_RS100_IG_AGPMODE, 0x20000);
	अन्यथा
		pci_ग_लिखो_config_dword(agp_bridge->dev, ATI_RS300_IG_AGPMODE, 0x20000);

	/* address to map to */
	/*
	agp_bridge.gart_bus_addr = pci_bus_address(agp_bridge.dev,
						   AGP_APERTURE_BAR);
	prपूर्णांकk(KERN_INFO PFX "IGP320 gart_bus_addr: %x\n", agp_bridge.gart_bus_addr);
	*/
	ग_लिखोl(0x60000, ati_generic_निजी.रेजिस्टरs+ATI_GART_FEATURE_ID);
	पढ़ोl(ati_generic_निजी.रेजिस्टरs+ATI_GART_FEATURE_ID);	/* PCI Posting.*/

	/* SIGNALED_SYSTEM_ERROR @ NB_STATUS */
	pci_पढ़ो_config_dword(agp_bridge->dev, PCI_COMMAND, &temp);
	pci_ग_लिखो_config_dword(agp_bridge->dev, PCI_COMMAND, temp | (1<<14));

	/* Write out the address of the gatt table */
	ग_लिखोl(agp_bridge->gatt_bus_addr, ati_generic_निजी.रेजिस्टरs+ATI_GART_BASE);
	पढ़ोl(ati_generic_निजी.रेजिस्टरs+ATI_GART_BASE);	/* PCI Posting. */

	वापस 0;
पूर्ण


#अगर_घोषित CONFIG_PM
अटल पूर्णांक agp_ati_suspend(काष्ठा pci_dev *dev, pm_message_t state)
अणु
	pci_save_state(dev);
	pci_set_घातer_state(dev, PCI_D3hot);

	वापस 0;
पूर्ण

अटल पूर्णांक agp_ati_resume(काष्ठा pci_dev *dev)
अणु
	pci_set_घातer_state(dev, PCI_D0);
	pci_restore_state(dev);

	वापस ati_configure();
पूर्ण
#पूर्ण_अगर

/*
 *Since we करोn't need contiguous memory we just try
 * to get the gatt table once
 */

#घोषणा GET_PAGE_सूची_OFF(addr) (addr >> 22)
#घोषणा GET_PAGE_सूची_IDX(addr) (GET_PAGE_सूची_OFF(addr) - \
	GET_PAGE_सूची_OFF(agp_bridge->gart_bus_addr))
#घोषणा GET_GATT_OFF(addr) ((addr & 0x003ff000) >> 12)
#अघोषित  GET_GATT
#घोषणा GET_GATT(addr) (ati_generic_निजी.gatt_pages[\
	GET_PAGE_सूची_IDX(addr)]->remapped)

अटल पूर्णांक ati_insert_memory(काष्ठा agp_memory * mem,
			     off_t pg_start, पूर्णांक type)
अणु
	पूर्णांक i, j, num_entries;
	अचिन्हित दीर्घ __iomem *cur_gatt;
	अचिन्हित दीर्घ addr;
	पूर्णांक mask_type;

	num_entries = A_SIZE_LVL2(agp_bridge->current_size)->num_entries;

	mask_type = agp_generic_type_to_mask_type(mem->bridge, type);
	अगर (mask_type != 0 || type != mem->type)
		वापस -EINVAL;

	अगर (mem->page_count == 0)
		वापस 0;

	अगर ((pg_start + mem->page_count) > num_entries)
		वापस -EINVAL;

	j = pg_start;
	जबतक (j < (pg_start + mem->page_count)) अणु
		addr = (j * PAGE_SIZE) + agp_bridge->gart_bus_addr;
		cur_gatt = GET_GATT(addr);
		अगर (!PGE_EMPTY(agp_bridge,पढ़ोl(cur_gatt+GET_GATT_OFF(addr))))
			वापस -EBUSY;
		j++;
	पूर्ण

	अगर (!mem->is_flushed) अणु
		/*CACHE_FLUSH(); */
		global_cache_flush();
		mem->is_flushed = true;
	पूर्ण

	क्रम (i = 0, j = pg_start; i < mem->page_count; i++, j++) अणु
		addr = (j * PAGE_SIZE) + agp_bridge->gart_bus_addr;
		cur_gatt = GET_GATT(addr);
		ग_लिखोl(agp_bridge->driver->mask_memory(agp_bridge,	
						       page_to_phys(mem->pages[i]),
						       mem->type),
		       cur_gatt+GET_GATT_OFF(addr));
	पूर्ण
	पढ़ोl(GET_GATT(agp_bridge->gart_bus_addr)); /* PCI posting */
	agp_bridge->driver->tlb_flush(mem);
	वापस 0;
पूर्ण

अटल पूर्णांक ati_हटाओ_memory(काष्ठा agp_memory * mem, off_t pg_start,
			     पूर्णांक type)
अणु
	पूर्णांक i;
	अचिन्हित दीर्घ __iomem *cur_gatt;
	अचिन्हित दीर्घ addr;
	पूर्णांक mask_type;

	mask_type = agp_generic_type_to_mask_type(mem->bridge, type);
	अगर (mask_type != 0 || type != mem->type)
		वापस -EINVAL;

	अगर (mem->page_count == 0)
		वापस 0;

	क्रम (i = pg_start; i < (mem->page_count + pg_start); i++) अणु
		addr = (i * PAGE_SIZE) + agp_bridge->gart_bus_addr;
		cur_gatt = GET_GATT(addr);
		ग_लिखोl(agp_bridge->scratch_page, cur_gatt+GET_GATT_OFF(addr));
	पूर्ण

	पढ़ोl(GET_GATT(agp_bridge->gart_bus_addr)); /* PCI posting */
	agp_bridge->driver->tlb_flush(mem);
	वापस 0;
पूर्ण

अटल पूर्णांक ati_create_gatt_table(काष्ठा agp_bridge_data *bridge)
अणु
	काष्ठा aper_size_info_lvl2 *value;
	काष्ठा ati_page_map page_dir;
	अचिन्हित दीर्घ __iomem *cur_gatt;
	अचिन्हित दीर्घ addr;
	पूर्णांक retval;
	u32 temp;
	पूर्णांक i;
	काष्ठा aper_size_info_lvl2 *current_size;

	value = A_SIZE_LVL2(agp_bridge->current_size);
	retval = ati_create_page_map(&page_dir);
	अगर (retval != 0)
		वापस retval;

	retval = ati_create_gatt_pages(value->num_entries / 1024);
	अगर (retval != 0) अणु
		ati_मुक्त_page_map(&page_dir);
		वापस retval;
	पूर्ण

	agp_bridge->gatt_table_real = (u32 *)page_dir.real;
	agp_bridge->gatt_table = (u32 __iomem *) page_dir.remapped;
	agp_bridge->gatt_bus_addr = virt_to_phys(page_dir.real);

	/* Write out the size रेजिस्टर */
	current_size = A_SIZE_LVL2(agp_bridge->current_size);

	अगर (is_r200()) अणु
		pci_पढ़ो_config_dword(agp_bridge->dev, ATI_RS100_APSIZE, &temp);
		temp = (((temp & ~(0x0000000e)) | current_size->size_value)
			| 0x00000001);
		pci_ग_लिखो_config_dword(agp_bridge->dev, ATI_RS100_APSIZE, temp);
		pci_पढ़ो_config_dword(agp_bridge->dev, ATI_RS100_APSIZE, &temp);
	पूर्ण अन्यथा अणु
		pci_पढ़ो_config_dword(agp_bridge->dev, ATI_RS300_APSIZE, &temp);
		temp = (((temp & ~(0x0000000e)) | current_size->size_value)
			| 0x00000001);
		pci_ग_लिखो_config_dword(agp_bridge->dev, ATI_RS300_APSIZE, temp);
		pci_पढ़ो_config_dword(agp_bridge->dev, ATI_RS300_APSIZE, &temp);
	पूर्ण

	/*
	 * Get the address क्रम the gart region.
	 * This is a bus address even on the alpha, b/c its
	 * used to program the agp master not the cpu
	 */
	addr = pci_bus_address(agp_bridge->dev, AGP_APERTURE_BAR);
	agp_bridge->gart_bus_addr = addr;

	/* Calculate the agp offset */
	क्रम (i = 0; i < value->num_entries / 1024; i++, addr += 0x00400000) अणु
		ग_लिखोl(virt_to_phys(ati_generic_निजी.gatt_pages[i]->real) | 1,
			page_dir.remapped+GET_PAGE_सूची_OFF(addr));
		पढ़ोl(page_dir.remapped+GET_PAGE_सूची_OFF(addr));	/* PCI Posting. */
	पूर्ण

	क्रम (i = 0; i < value->num_entries; i++) अणु
		addr = (i * PAGE_SIZE) + agp_bridge->gart_bus_addr;
		cur_gatt = GET_GATT(addr);
		ग_लिखोl(agp_bridge->scratch_page, cur_gatt+GET_GATT_OFF(addr));
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ati_मुक्त_gatt_table(काष्ठा agp_bridge_data *bridge)
अणु
	काष्ठा ati_page_map page_dir;

	page_dir.real = (अचिन्हित दीर्घ *)agp_bridge->gatt_table_real;
	page_dir.remapped = (अचिन्हित दीर्घ __iomem *)agp_bridge->gatt_table;

	ati_मुक्त_gatt_pages();
	ati_मुक्त_page_map(&page_dir);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा agp_bridge_driver ati_generic_bridge = अणु
	.owner			= THIS_MODULE,
	.aperture_sizes		= ati_generic_sizes,
	.माप_प्रकारype		= LVL2_APER_SIZE,
	.num_aperture_sizes	= 7,
	.needs_scratch_page	= true,
	.configure		= ati_configure,
	.fetch_size		= ati_fetch_size,
	.cleanup		= ati_cleanup,
	.tlb_flush		= ati_tlbflush,
	.mask_memory		= agp_generic_mask_memory,
	.masks			= ati_generic_masks,
	.agp_enable		= agp_generic_enable,
	.cache_flush		= global_cache_flush,
	.create_gatt_table	= ati_create_gatt_table,
	.मुक्त_gatt_table	= ati_मुक्त_gatt_table,
	.insert_memory		= ati_insert_memory,
	.हटाओ_memory		= ati_हटाओ_memory,
	.alloc_by_type		= agp_generic_alloc_by_type,
	.मुक्त_by_type		= agp_generic_मुक्त_by_type,
	.agp_alloc_page		= agp_generic_alloc_page,
	.agp_alloc_pages	= agp_generic_alloc_pages,
	.agp_destroy_page	= agp_generic_destroy_page,
	.agp_destroy_pages	= agp_generic_destroy_pages,
	.agp_type_to_mask_type  = agp_generic_type_to_mask_type,
पूर्ण;


अटल काष्ठा agp_device_ids ati_agp_device_ids[] =
अणु
	अणु
		.device_id	= PCI_DEVICE_ID_ATI_RS100,
		.chipset_name	= "IGP320/M",
	पूर्ण,
	अणु
		.device_id	= PCI_DEVICE_ID_ATI_RS200,
		.chipset_name	= "IGP330/340/345/350/M",
	पूर्ण,
	अणु
		.device_id	= PCI_DEVICE_ID_ATI_RS200_B,
		.chipset_name	= "IGP345M",
	पूर्ण,
	अणु
		.device_id	= PCI_DEVICE_ID_ATI_RS250,
		.chipset_name	= "IGP7000/M",
	पूर्ण,
	अणु
		.device_id	= PCI_DEVICE_ID_ATI_RS300_100,
		.chipset_name	= "IGP9100/M",
	पूर्ण,
	अणु
		.device_id	= PCI_DEVICE_ID_ATI_RS300_133,
		.chipset_name	= "IGP9100/M",
	पूर्ण,
	अणु
		.device_id	= PCI_DEVICE_ID_ATI_RS300_166,
		.chipset_name	= "IGP9100/M",
	पूर्ण,
	अणु
		.device_id	= PCI_DEVICE_ID_ATI_RS300_200,
		.chipset_name	= "IGP9100/M",
	पूर्ण,
	अणु
		.device_id	= PCI_DEVICE_ID_ATI_RS350_133,
		.chipset_name	= "IGP9000/M",
	पूर्ण,
	अणु
		.device_id	= PCI_DEVICE_ID_ATI_RS350_200,
		.chipset_name	= "IGP9100/M",
	पूर्ण,
	अणु पूर्ण, /* dummy final entry, always present */
पूर्ण;

अटल पूर्णांक agp_ati_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent)
अणु
	काष्ठा agp_device_ids *devs = ati_agp_device_ids;
	काष्ठा agp_bridge_data *bridge;
	u8 cap_ptr;
	पूर्णांक j;

	cap_ptr = pci_find_capability(pdev, PCI_CAP_ID_AGP);
	अगर (!cap_ptr)
		वापस -ENODEV;

	/* probe क्रम known chipsets */
	क्रम (j = 0; devs[j].chipset_name; j++) अणु
		अगर (pdev->device == devs[j].device_id)
			जाओ found;
	पूर्ण

	dev_err(&pdev->dev, "unsupported Ati chipset [%04x/%04x])\n",
		pdev->venकरोr, pdev->device);
	वापस -ENODEV;

found:
	bridge = agp_alloc_bridge();
	अगर (!bridge)
		वापस -ENOMEM;

	bridge->dev = pdev;
	bridge->capndx = cap_ptr;

	bridge->driver = &ati_generic_bridge;

	dev_info(&pdev->dev, "Ati %s chipset\n", devs[j].chipset_name);

	/* Fill in the mode रेजिस्टर */
	pci_पढ़ो_config_dword(pdev,
			bridge->capndx+PCI_AGP_STATUS,
			&bridge->mode);

	pci_set_drvdata(pdev, bridge);
	वापस agp_add_bridge(bridge);
पूर्ण

अटल व्योम agp_ati_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा agp_bridge_data *bridge = pci_get_drvdata(pdev);

	agp_हटाओ_bridge(bridge);
	agp_put_bridge(bridge);
पूर्ण

अटल स्थिर काष्ठा pci_device_id agp_ati_pci_table[] = अणु
	अणु
	.class		= (PCI_CLASS_BRIDGE_HOST << 8),
	.class_mask	= ~0,
	.venकरोr		= PCI_VENDOR_ID_ATI,
	.device		= PCI_ANY_ID,
	.subvenकरोr	= PCI_ANY_ID,
	.subdevice	= PCI_ANY_ID,
	पूर्ण,
	अणु पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, agp_ati_pci_table);

अटल काष्ठा pci_driver agp_ati_pci_driver = अणु
	.name		= "agpgart-ati",
	.id_table	= agp_ati_pci_table,
	.probe		= agp_ati_probe,
	.हटाओ		= agp_ati_हटाओ,
#अगर_घोषित CONFIG_PM
	.suspend	= agp_ati_suspend,
	.resume		= agp_ati_resume,
#पूर्ण_अगर
पूर्ण;

अटल पूर्णांक __init agp_ati_init(व्योम)
अणु
	अगर (agp_off)
		वापस -EINVAL;
	वापस pci_रेजिस्टर_driver(&agp_ati_pci_driver);
पूर्ण

अटल व्योम __निकास agp_ati_cleanup(व्योम)
अणु
	pci_unरेजिस्टर_driver(&agp_ati_pci_driver);
पूर्ण

module_init(agp_ati_init);
module_निकास(agp_ati_cleanup);

MODULE_AUTHOR("Dave Jones");
MODULE_LICENSE("GPL and additional rights");

