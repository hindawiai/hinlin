<शैली गुरु>
/*
 * Serverworks AGPGART routines.
 */

#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/init.h>
#समावेश <linux/माला.स>
#समावेश <linux/slab.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/agp_backend.h>
#समावेश <यंत्र/set_memory.h>
#समावेश "agp.h"

#घोषणा SVWRKS_COMMAND		0x04
#घोषणा SVWRKS_APSIZE		0x10
#घोषणा SVWRKS_MMBASE		0x14
#घोषणा SVWRKS_CACHING		0x4b
#घोषणा SVWRKS_AGP_ENABLE	0x60
#घोषणा SVWRKS_FEATURE		0x68

#घोषणा SVWRKS_SIZE_MASK	0xfe000000

/* Memory mapped रेजिस्टरs */
#घोषणा SVWRKS_GART_CACHE	0x02
#घोषणा SVWRKS_GATTBASE		0x04
#घोषणा SVWRKS_TLBFLUSH		0x10
#घोषणा SVWRKS_POSTFLUSH	0x14
#घोषणा SVWRKS_सूचीFLUSH		0x0c


काष्ठा serverworks_page_map अणु
	अचिन्हित दीर्घ *real;
	अचिन्हित दीर्घ __iomem *remapped;
पूर्ण;

अटल काष्ठा _serverworks_निजी अणु
	काष्ठा pci_dev *svrwrks_dev;	/* device one */
	अस्थिर u8 __iomem *रेजिस्टरs;
	काष्ठा serverworks_page_map **gatt_pages;
	पूर्णांक num_tables;
	काष्ठा serverworks_page_map scratch_dir;

	पूर्णांक gart_addr_ofs;
	पूर्णांक mm_addr_ofs;
पूर्ण serverworks_निजी;

अटल पूर्णांक serverworks_create_page_map(काष्ठा serverworks_page_map *page_map)
अणु
	पूर्णांक i;

	page_map->real = (अचिन्हित दीर्घ *) __get_मुक्त_page(GFP_KERNEL);
	अगर (page_map->real == शून्य) अणु
		वापस -ENOMEM;
	पूर्ण

	set_memory_uc((अचिन्हित दीर्घ)page_map->real, 1);
	page_map->remapped = page_map->real;

	क्रम (i = 0; i < PAGE_SIZE / माप(अचिन्हित दीर्घ); i++)
		ग_लिखोl(agp_bridge->scratch_page, page_map->remapped+i);
		/* Red Pen: Everyone अन्यथा करोes pci posting flush here */

	वापस 0;
पूर्ण

अटल व्योम serverworks_मुक्त_page_map(काष्ठा serverworks_page_map *page_map)
अणु
	set_memory_wb((अचिन्हित दीर्घ)page_map->real, 1);
	मुक्त_page((अचिन्हित दीर्घ) page_map->real);
पूर्ण

अटल व्योम serverworks_मुक्त_gatt_pages(व्योम)
अणु
	पूर्णांक i;
	काष्ठा serverworks_page_map **tables;
	काष्ठा serverworks_page_map *entry;

	tables = serverworks_निजी.gatt_pages;
	क्रम (i = 0; i < serverworks_निजी.num_tables; i++) अणु
		entry = tables[i];
		अगर (entry != शून्य) अणु
			अगर (entry->real != शून्य) अणु
				serverworks_मुक्त_page_map(entry);
			पूर्ण
			kमुक्त(entry);
		पूर्ण
	पूर्ण
	kमुक्त(tables);
पूर्ण

अटल पूर्णांक serverworks_create_gatt_pages(पूर्णांक nr_tables)
अणु
	काष्ठा serverworks_page_map **tables;
	काष्ठा serverworks_page_map *entry;
	पूर्णांक retval = 0;
	पूर्णांक i;

	tables = kसुस्मृति(nr_tables + 1, माप(काष्ठा serverworks_page_map *),
			 GFP_KERNEL);
	अगर (tables == शून्य)
		वापस -ENOMEM;

	क्रम (i = 0; i < nr_tables; i++) अणु
		entry = kzalloc(माप(काष्ठा serverworks_page_map), GFP_KERNEL);
		अगर (entry == शून्य) अणु
			retval = -ENOMEM;
			अवरोध;
		पूर्ण
		tables[i] = entry;
		retval = serverworks_create_page_map(entry);
		अगर (retval != 0) अवरोध;
	पूर्ण
	serverworks_निजी.num_tables = nr_tables;
	serverworks_निजी.gatt_pages = tables;

	अगर (retval != 0) serverworks_मुक्त_gatt_pages();

	वापस retval;
पूर्ण

#घोषणा SVRWRKS_GET_GATT(addr) (serverworks_निजी.gatt_pages[\
	GET_PAGE_सूची_IDX(addr)]->remapped)

#अगर_अघोषित GET_PAGE_सूची_OFF
#घोषणा GET_PAGE_सूची_OFF(addr) (addr >> 22)
#पूर्ण_अगर

#अगर_अघोषित GET_PAGE_सूची_IDX
#घोषणा GET_PAGE_सूची_IDX(addr) (GET_PAGE_सूची_OFF(addr) - \
	GET_PAGE_सूची_OFF(agp_bridge->gart_bus_addr))
#पूर्ण_अगर

#अगर_अघोषित GET_GATT_OFF
#घोषणा GET_GATT_OFF(addr) ((addr & 0x003ff000) >> 12)
#पूर्ण_अगर

अटल पूर्णांक serverworks_create_gatt_table(काष्ठा agp_bridge_data *bridge)
अणु
	काष्ठा aper_size_info_lvl2 *value;
	काष्ठा serverworks_page_map page_dir;
	पूर्णांक retval;
	u32 temp;
	पूर्णांक i;

	value = A_SIZE_LVL2(agp_bridge->current_size);
	retval = serverworks_create_page_map(&page_dir);
	अगर (retval != 0) अणु
		वापस retval;
	पूर्ण
	retval = serverworks_create_page_map(&serverworks_निजी.scratch_dir);
	अगर (retval != 0) अणु
		serverworks_मुक्त_page_map(&page_dir);
		वापस retval;
	पूर्ण
	/* Create a fake scratch directory */
	क्रम (i = 0; i < 1024; i++) अणु
		ग_लिखोl(agp_bridge->scratch_page, serverworks_निजी.scratch_dir.remapped+i);
		ग_लिखोl(virt_to_phys(serverworks_निजी.scratch_dir.real) | 1, page_dir.remapped+i);
	पूर्ण

	retval = serverworks_create_gatt_pages(value->num_entries / 1024);
	अगर (retval != 0) अणु
		serverworks_मुक्त_page_map(&page_dir);
		serverworks_मुक्त_page_map(&serverworks_निजी.scratch_dir);
		वापस retval;
	पूर्ण

	agp_bridge->gatt_table_real = (u32 *)page_dir.real;
	agp_bridge->gatt_table = (u32 __iomem *)page_dir.remapped;
	agp_bridge->gatt_bus_addr = virt_to_phys(page_dir.real);

	/* Get the address क्रम the gart region.
	 * This is a bus address even on the alpha, b/c its
	 * used to program the agp master not the cpu
	 */

	pci_पढ़ो_config_dword(agp_bridge->dev,serverworks_निजी.gart_addr_ofs,&temp);
	agp_bridge->gart_bus_addr = (temp & PCI_BASE_ADDRESS_MEM_MASK);

	/* Calculate the agp offset */
	क्रम (i = 0; i < value->num_entries / 1024; i++)
		ग_लिखोl(virt_to_phys(serverworks_निजी.gatt_pages[i]->real)|1, page_dir.remapped+i);

	वापस 0;
पूर्ण

अटल पूर्णांक serverworks_मुक्त_gatt_table(काष्ठा agp_bridge_data *bridge)
अणु
	काष्ठा serverworks_page_map page_dir;

	page_dir.real = (अचिन्हित दीर्घ *)agp_bridge->gatt_table_real;
	page_dir.remapped = (अचिन्हित दीर्घ __iomem *)agp_bridge->gatt_table;

	serverworks_मुक्त_gatt_pages();
	serverworks_मुक्त_page_map(&page_dir);
	serverworks_मुक्त_page_map(&serverworks_निजी.scratch_dir);
	वापस 0;
पूर्ण

अटल पूर्णांक serverworks_fetch_size(व्योम)
अणु
	पूर्णांक i;
	u32 temp;
	u32 temp2;
	काष्ठा aper_size_info_lvl2 *values;

	values = A_SIZE_LVL2(agp_bridge->driver->aperture_sizes);
	pci_पढ़ो_config_dword(agp_bridge->dev,serverworks_निजी.gart_addr_ofs,&temp);
	pci_ग_लिखो_config_dword(agp_bridge->dev,serverworks_निजी.gart_addr_ofs,
					SVWRKS_SIZE_MASK);
	pci_पढ़ो_config_dword(agp_bridge->dev,serverworks_निजी.gart_addr_ofs,&temp2);
	pci_ग_लिखो_config_dword(agp_bridge->dev,serverworks_निजी.gart_addr_ofs,temp);
	temp2 &= SVWRKS_SIZE_MASK;

	क्रम (i = 0; i < agp_bridge->driver->num_aperture_sizes; i++) अणु
		अगर (temp2 == values[i].size_value) अणु
			agp_bridge->previous_size =
			    agp_bridge->current_size = (व्योम *) (values + i);

			agp_bridge->aperture_size_idx = i;
			वापस values[i].size;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/*
 * This routine could be implemented by taking the addresses
 * written to the GATT, and flushing them inभागidually.  However
 * currently it just flushes the whole table.  Which is probably
 * more efficient, since agp_memory blocks can be a large number of
 * entries.
 */
अटल व्योम serverworks_tlbflush(काष्ठा agp_memory *temp)
अणु
	अचिन्हित दीर्घ समयout;

	ग_लिखोb(1, serverworks_निजी.रेजिस्टरs+SVWRKS_POSTFLUSH);
	समयout = jअगरfies + 3*HZ;
	जबतक (पढ़ोb(serverworks_निजी.रेजिस्टरs+SVWRKS_POSTFLUSH) == 1) अणु
		cpu_relax();
		अगर (समय_after(jअगरfies, समयout)) अणु
			dev_err(&serverworks_निजी.svrwrks_dev->dev,
				"TLB post flush took more than 3 seconds\n");
			अवरोध;
		पूर्ण
	पूर्ण

	ग_लिखोl(1, serverworks_निजी.रेजिस्टरs+SVWRKS_सूचीFLUSH);
	समयout = jअगरfies + 3*HZ;
	जबतक (पढ़ोl(serverworks_निजी.रेजिस्टरs+SVWRKS_सूचीFLUSH) == 1) अणु
		cpu_relax();
		अगर (समय_after(jअगरfies, समयout)) अणु
			dev_err(&serverworks_निजी.svrwrks_dev->dev,
				"TLB Dir flush took more than 3 seconds\n");
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक serverworks_configure(व्योम)
अणु
	काष्ठा aper_size_info_lvl2 *current_size;
	u32 temp;
	u8 enable_reg;
	u16 cap_reg;

	current_size = A_SIZE_LVL2(agp_bridge->current_size);

	/* Get the memory mapped रेजिस्टरs */
	pci_पढ़ो_config_dword(agp_bridge->dev, serverworks_निजी.mm_addr_ofs, &temp);
	temp = (temp & PCI_BASE_ADDRESS_MEM_MASK);
	serverworks_निजी.रेजिस्टरs = (अस्थिर u8 __iomem *) ioremap(temp, 4096);
	अगर (!serverworks_निजी.रेजिस्टरs) अणु
		dev_err(&agp_bridge->dev->dev, "can't ioremap(%#x)\n", temp);
		वापस -ENOMEM;
	पूर्ण

	ग_लिखोb(0xA, serverworks_निजी.रेजिस्टरs+SVWRKS_GART_CACHE);
	पढ़ोb(serverworks_निजी.रेजिस्टरs+SVWRKS_GART_CACHE);	/* PCI Posting. */

	ग_लिखोl(agp_bridge->gatt_bus_addr, serverworks_निजी.रेजिस्टरs+SVWRKS_GATTBASE);
	पढ़ोl(serverworks_निजी.रेजिस्टरs+SVWRKS_GATTBASE);	/* PCI Posting. */

	cap_reg = पढ़ोw(serverworks_निजी.रेजिस्टरs+SVWRKS_COMMAND);
	cap_reg &= ~0x0007;
	cap_reg |= 0x4;
	ग_लिखोw(cap_reg, serverworks_निजी.रेजिस्टरs+SVWRKS_COMMAND);
	पढ़ोw(serverworks_निजी.रेजिस्टरs+SVWRKS_COMMAND);

	pci_पढ़ो_config_byte(serverworks_निजी.svrwrks_dev,SVWRKS_AGP_ENABLE, &enable_reg);
	enable_reg |= 0x1; /* Agp Enable bit */
	pci_ग_लिखो_config_byte(serverworks_निजी.svrwrks_dev,SVWRKS_AGP_ENABLE, enable_reg);
	serverworks_tlbflush(शून्य);

	agp_bridge->capndx = pci_find_capability(serverworks_निजी.svrwrks_dev, PCI_CAP_ID_AGP);

	/* Fill in the mode रेजिस्टर */
	pci_पढ़ो_config_dword(serverworks_निजी.svrwrks_dev,
			      agp_bridge->capndx+PCI_AGP_STATUS, &agp_bridge->mode);

	pci_पढ़ो_config_byte(agp_bridge->dev, SVWRKS_CACHING, &enable_reg);
	enable_reg &= ~0x3;
	pci_ग_लिखो_config_byte(agp_bridge->dev, SVWRKS_CACHING, enable_reg);

	pci_पढ़ो_config_byte(agp_bridge->dev, SVWRKS_FEATURE, &enable_reg);
	enable_reg |= (1<<6);
	pci_ग_लिखो_config_byte(agp_bridge->dev,SVWRKS_FEATURE, enable_reg);

	वापस 0;
पूर्ण

अटल व्योम serverworks_cleanup(व्योम)
अणु
	iounmap((व्योम __iomem *) serverworks_निजी.रेजिस्टरs);
पूर्ण

अटल पूर्णांक serverworks_insert_memory(काष्ठा agp_memory *mem,
			     off_t pg_start, पूर्णांक type)
अणु
	पूर्णांक i, j, num_entries;
	अचिन्हित दीर्घ __iomem *cur_gatt;
	अचिन्हित दीर्घ addr;

	num_entries = A_SIZE_LVL2(agp_bridge->current_size)->num_entries;

	अगर (type != 0 || mem->type != 0) अणु
		वापस -EINVAL;
	पूर्ण
	अगर ((pg_start + mem->page_count) > num_entries) अणु
		वापस -EINVAL;
	पूर्ण

	j = pg_start;
	जबतक (j < (pg_start + mem->page_count)) अणु
		addr = (j * PAGE_SIZE) + agp_bridge->gart_bus_addr;
		cur_gatt = SVRWRKS_GET_GATT(addr);
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
		cur_gatt = SVRWRKS_GET_GATT(addr);
		ग_लिखोl(agp_bridge->driver->mask_memory(agp_bridge, 
				page_to_phys(mem->pages[i]), mem->type),
		       cur_gatt+GET_GATT_OFF(addr));
	पूर्ण
	serverworks_tlbflush(mem);
	वापस 0;
पूर्ण

अटल पूर्णांक serverworks_हटाओ_memory(काष्ठा agp_memory *mem, off_t pg_start,
			     पूर्णांक type)
अणु
	पूर्णांक i;
	अचिन्हित दीर्घ __iomem *cur_gatt;
	अचिन्हित दीर्घ addr;

	अगर (type != 0 || mem->type != 0) अणु
		वापस -EINVAL;
	पूर्ण

	global_cache_flush();
	serverworks_tlbflush(mem);

	क्रम (i = pg_start; i < (mem->page_count + pg_start); i++) अणु
		addr = (i * PAGE_SIZE) + agp_bridge->gart_bus_addr;
		cur_gatt = SVRWRKS_GET_GATT(addr);
		ग_लिखोl(agp_bridge->scratch_page, cur_gatt+GET_GATT_OFF(addr));
	पूर्ण

	serverworks_tlbflush(mem);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा gatt_mask serverworks_masks[] =
अणु
	अणु.mask = 1, .type = 0पूर्ण
पूर्ण;

अटल स्थिर काष्ठा aper_size_info_lvl2 serverworks_sizes[7] =
अणु
	अणु2048, 524288, 0x80000000पूर्ण,
	अणु1024, 262144, 0xc0000000पूर्ण,
	अणु512, 131072, 0xe0000000पूर्ण,
	अणु256, 65536, 0xf0000000पूर्ण,
	अणु128, 32768, 0xf8000000पूर्ण,
	अणु64, 16384, 0xfc000000पूर्ण,
	अणु32, 8192, 0xfe000000पूर्ण
पूर्ण;

अटल व्योम serverworks_agp_enable(काष्ठा agp_bridge_data *bridge, u32 mode)
अणु
	u32 command;

	pci_पढ़ो_config_dword(serverworks_निजी.svrwrks_dev,
			      bridge->capndx + PCI_AGP_STATUS,
			      &command);

	command = agp_collect_device_status(bridge, mode, command);

	command &= ~0x10;	/* disable FW */
	command &= ~0x08;

	command |= 0x100;

	pci_ग_लिखो_config_dword(serverworks_निजी.svrwrks_dev,
			       bridge->capndx + PCI_AGP_COMMAND,
			       command);

	agp_device_command(command, false);
पूर्ण

अटल स्थिर काष्ठा agp_bridge_driver sworks_driver = अणु
	.owner			= THIS_MODULE,
	.aperture_sizes		= serverworks_sizes,
	.माप_प्रकारype		= LVL2_APER_SIZE,
	.num_aperture_sizes	= 7,
	.configure		= serverworks_configure,
	.fetch_size		= serverworks_fetch_size,
	.cleanup		= serverworks_cleanup,
	.tlb_flush		= serverworks_tlbflush,
	.mask_memory		= agp_generic_mask_memory,
	.masks			= serverworks_masks,
	.agp_enable		= serverworks_agp_enable,
	.cache_flush		= global_cache_flush,
	.create_gatt_table	= serverworks_create_gatt_table,
	.मुक्त_gatt_table	= serverworks_मुक्त_gatt_table,
	.insert_memory		= serverworks_insert_memory,
	.हटाओ_memory		= serverworks_हटाओ_memory,
	.alloc_by_type		= agp_generic_alloc_by_type,
	.मुक्त_by_type		= agp_generic_मुक्त_by_type,
	.agp_alloc_page		= agp_generic_alloc_page,
	.agp_alloc_pages	= agp_generic_alloc_pages,
	.agp_destroy_page	= agp_generic_destroy_page,
	.agp_destroy_pages	= agp_generic_destroy_pages,
	.agp_type_to_mask_type  = agp_generic_type_to_mask_type,
पूर्ण;

अटल पूर्णांक agp_serverworks_probe(काष्ठा pci_dev *pdev,
				 स्थिर काष्ठा pci_device_id *ent)
अणु
	काष्ठा agp_bridge_data *bridge;
	काष्ठा pci_dev *bridge_dev;
	u32 temp, temp2;
	u8 cap_ptr = 0;

	cap_ptr = pci_find_capability(pdev, PCI_CAP_ID_AGP);

	चयन (pdev->device) अणु
	हाल 0x0006:
		dev_err(&pdev->dev, "ServerWorks CNB20HE is unsupported due to lack of documentation\n");
		वापस -ENODEV;

	हाल PCI_DEVICE_ID_SERVERWORKS_HE:
	हाल PCI_DEVICE_ID_SERVERWORKS_LE:
	हाल 0x0007:
		अवरोध;

	शेष:
		अगर (cap_ptr)
			dev_err(&pdev->dev, "unsupported Serverworks chipset "
				"[%04x/%04x]\n", pdev->venकरोr, pdev->device);
		वापस -ENODEV;
	पूर्ण

	/* Everything is on func 1 here so we are hardcoding function one */
	bridge_dev = pci_get_करोमुख्य_bus_and_slot(pci_करोमुख्य_nr(pdev->bus),
			(अचिन्हित पूर्णांक)pdev->bus->number,
			PCI_DEVFN(0, 1));
	अगर (!bridge_dev) अणु
		dev_info(&pdev->dev, "can't find secondary device\n");
		वापस -ENODEV;
	पूर्ण

	serverworks_निजी.svrwrks_dev = bridge_dev;
	serverworks_निजी.gart_addr_ofs = 0x10;

	pci_पढ़ो_config_dword(pdev, SVWRKS_APSIZE, &temp);
	अगर (temp & PCI_BASE_ADDRESS_MEM_TYPE_64) अणु
		pci_पढ़ो_config_dword(pdev, SVWRKS_APSIZE + 4, &temp2);
		अगर (temp2 != 0) अणु
			dev_info(&pdev->dev, "64 bit aperture address, "
				 "but top bits are not zero; disabling AGP\n");
			वापस -ENODEV;
		पूर्ण
		serverworks_निजी.mm_addr_ofs = 0x18;
	पूर्ण अन्यथा
		serverworks_निजी.mm_addr_ofs = 0x14;

	pci_पढ़ो_config_dword(pdev, serverworks_निजी.mm_addr_ofs, &temp);
	अगर (temp & PCI_BASE_ADDRESS_MEM_TYPE_64) अणु
		pci_पढ़ो_config_dword(pdev,
				serverworks_निजी.mm_addr_ofs + 4, &temp2);
		अगर (temp2 != 0) अणु
			dev_info(&pdev->dev, "64 bit MMIO address, but top "
				 "bits are not zero; disabling AGP\n");
			वापस -ENODEV;
		पूर्ण
	पूर्ण

	bridge = agp_alloc_bridge();
	अगर (!bridge)
		वापस -ENOMEM;

	bridge->driver = &sworks_driver;
	bridge->dev_निजी_data = &serverworks_निजी;
	bridge->dev = pci_dev_get(pdev);

	pci_set_drvdata(pdev, bridge);
	वापस agp_add_bridge(bridge);
पूर्ण

अटल व्योम agp_serverworks_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा agp_bridge_data *bridge = pci_get_drvdata(pdev);

	pci_dev_put(bridge->dev);
	agp_हटाओ_bridge(bridge);
	agp_put_bridge(bridge);
	pci_dev_put(serverworks_निजी.svrwrks_dev);
	serverworks_निजी.svrwrks_dev = शून्य;
पूर्ण

अटल काष्ठा pci_device_id agp_serverworks_pci_table[] = अणु
	अणु
	.class		= (PCI_CLASS_BRIDGE_HOST << 8),
	.class_mask	= ~0,
	.venकरोr		= PCI_VENDOR_ID_SERVERWORKS,
	.device		= PCI_ANY_ID,
	.subvenकरोr	= PCI_ANY_ID,
	.subdevice	= PCI_ANY_ID,
	पूर्ण,
	अणु पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, agp_serverworks_pci_table);

अटल काष्ठा pci_driver agp_serverworks_pci_driver = अणु
	.name		= "agpgart-serverworks",
	.id_table	= agp_serverworks_pci_table,
	.probe		= agp_serverworks_probe,
	.हटाओ		= agp_serverworks_हटाओ,
पूर्ण;

अटल पूर्णांक __init agp_serverworks_init(व्योम)
अणु
	अगर (agp_off)
		वापस -EINVAL;
	वापस pci_रेजिस्टर_driver(&agp_serverworks_pci_driver);
पूर्ण

अटल व्योम __निकास agp_serverworks_cleanup(व्योम)
अणु
	pci_unरेजिस्टर_driver(&agp_serverworks_pci_driver);
पूर्ण

module_init(agp_serverworks_init);
module_निकास(agp_serverworks_cleanup);

MODULE_LICENSE("GPL and additional rights");

