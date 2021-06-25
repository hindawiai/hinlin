<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * UniNorth AGPGART routines.
 */
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/slab.h>
#समावेश <linux/init.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/agp_backend.h>
#समावेश <linux/delay.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <यंत्र/uninorth.h>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/pmac_feature.h>
#समावेश "agp.h"

/*
 * NOTES क्रम uninorth3 (G5 AGP) supports :
 *
 * There maybe also possibility to have bigger cache line size क्रम
 * agp (see pmac_pci.c and look क्रम cache line). Need to be investigated
 * by someone.
 *
 * PAGE size are hardcoded but this may change, see यंत्र/page.h.
 *
 * Jerome Glisse <j.glisse@gmail.com>
 */
अटल पूर्णांक uninorth_rev;
अटल पूर्णांक is_u3;
अटल u32 scratch_value;

#घोषणा DEFAULT_APERTURE_SIZE 256
#घोषणा DEFAULT_APERTURE_STRING "256"
अटल अक्षर *aperture = शून्य;

अटल पूर्णांक uninorth_fetch_size(व्योम)
अणु
	पूर्णांक i, size = 0;
	काष्ठा aper_size_info_32 *values =
	    A_SIZE_32(agp_bridge->driver->aperture_sizes);

	अगर (aperture) अणु
		अक्षर *save = aperture;

		size = memparse(aperture, &aperture) >> 20;
		aperture = save;

		क्रम (i = 0; i < agp_bridge->driver->num_aperture_sizes; i++)
			अगर (size == values[i].size)
				अवरोध;

		अगर (i == agp_bridge->driver->num_aperture_sizes) अणु
			dev_err(&agp_bridge->dev->dev, "invalid aperture size, "
				"using default\n");
			size = 0;
			aperture = शून्य;
		पूर्ण
	पूर्ण

	अगर (!size) अणु
		क्रम (i = 0; i < agp_bridge->driver->num_aperture_sizes; i++)
			अगर (values[i].size == DEFAULT_APERTURE_SIZE)
				अवरोध;
	पूर्ण

	agp_bridge->previous_size =
	    agp_bridge->current_size = (व्योम *)(values + i);
	agp_bridge->aperture_size_idx = i;
	वापस values[i].size;
पूर्ण

अटल व्योम uninorth_tlbflush(काष्ठा agp_memory *mem)
अणु
	u32 ctrl = UNI_N_CFG_GART_ENABLE;

	अगर (is_u3)
		ctrl |= U3_N_CFG_GART_PERFRD;
	pci_ग_लिखो_config_dword(agp_bridge->dev, UNI_N_CFG_GART_CTRL,
			       ctrl | UNI_N_CFG_GART_INVAL);
	pci_ग_लिखो_config_dword(agp_bridge->dev, UNI_N_CFG_GART_CTRL, ctrl);

	अगर (!mem && uninorth_rev <= 0x30) अणु
		pci_ग_लिखो_config_dword(agp_bridge->dev, UNI_N_CFG_GART_CTRL,
				       ctrl | UNI_N_CFG_GART_2xRESET);
		pci_ग_लिखो_config_dword(agp_bridge->dev, UNI_N_CFG_GART_CTRL,
				       ctrl);
	पूर्ण
पूर्ण

अटल व्योम uninorth_cleanup(व्योम)
अणु
	u32 पंचांगp;

	pci_पढ़ो_config_dword(agp_bridge->dev, UNI_N_CFG_GART_CTRL, &पंचांगp);
	अगर (!(पंचांगp & UNI_N_CFG_GART_ENABLE))
		वापस;
	पंचांगp |= UNI_N_CFG_GART_INVAL;
	pci_ग_लिखो_config_dword(agp_bridge->dev, UNI_N_CFG_GART_CTRL, पंचांगp);
	pci_ग_लिखो_config_dword(agp_bridge->dev, UNI_N_CFG_GART_CTRL, 0);

	अगर (uninorth_rev <= 0x30) अणु
		pci_ग_लिखो_config_dword(agp_bridge->dev, UNI_N_CFG_GART_CTRL,
				       UNI_N_CFG_GART_2xRESET);
		pci_ग_लिखो_config_dword(agp_bridge->dev, UNI_N_CFG_GART_CTRL,
				       0);
	पूर्ण
पूर्ण

अटल पूर्णांक uninorth_configure(व्योम)
अणु
	काष्ठा aper_size_info_32 *current_size;

	current_size = A_SIZE_32(agp_bridge->current_size);

	dev_info(&agp_bridge->dev->dev, "configuring for size idx: %d\n",
		 current_size->size_value);

	/* aperture size and gatt addr */
	pci_ग_लिखो_config_dword(agp_bridge->dev,
		UNI_N_CFG_GART_BASE,
		(agp_bridge->gatt_bus_addr & 0xfffff000)
			| current_size->size_value);

	/* HACK ALERT
	 * UniNorth seem to be buggy enough not to handle properly when
	 * the AGP aperture isn't mapped at bus physical address 0
	 */
	agp_bridge->gart_bus_addr = 0;
#अगर_घोषित CONFIG_PPC64
	/* Assume U3 or later on PPC64 प्रणालीs */
	/* high 4 bits of GART physical address go in UNI_N_CFG_AGP_BASE */
	pci_ग_लिखो_config_dword(agp_bridge->dev, UNI_N_CFG_AGP_BASE,
			       (agp_bridge->gatt_bus_addr >> 32) & 0xf);
#अन्यथा
	pci_ग_लिखो_config_dword(agp_bridge->dev,
		UNI_N_CFG_AGP_BASE, agp_bridge->gart_bus_addr);
#पूर्ण_अगर

	अगर (is_u3) अणु
		pci_ग_लिखो_config_dword(agp_bridge->dev,
				       UNI_N_CFG_GART_DUMMY_PAGE,
				       page_to_phys(agp_bridge->scratch_page_page) >> 12);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक uninorth_insert_memory(काष्ठा agp_memory *mem, off_t pg_start, पूर्णांक type)
अणु
	पूर्णांक i, num_entries;
	व्योम *temp;
	u32 *gp;
	पूर्णांक mask_type;

	अगर (type != mem->type)
		वापस -EINVAL;

	mask_type = agp_bridge->driver->agp_type_to_mask_type(agp_bridge, type);
	अगर (mask_type != 0) अणु
		/* We know nothing of memory types */
		वापस -EINVAL;
	पूर्ण

	अगर (mem->page_count == 0)
		वापस 0;

	temp = agp_bridge->current_size;
	num_entries = A_SIZE_32(temp)->num_entries;

	अगर ((pg_start + mem->page_count) > num_entries)
		वापस -EINVAL;

	gp = (u32 *) &agp_bridge->gatt_table[pg_start];
	क्रम (i = 0; i < mem->page_count; ++i) अणु
		अगर (gp[i] != scratch_value) अणु
			dev_info(&agp_bridge->dev->dev,
				 "uninorth_insert_memory: entry 0x%x occupied (%x)\n",
				 i, gp[i]);
			वापस -EBUSY;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < mem->page_count; i++) अणु
		अगर (is_u3)
			gp[i] = (page_to_phys(mem->pages[i]) >> PAGE_SHIFT) | 0x80000000UL;
		अन्यथा
			gp[i] =	cpu_to_le32((page_to_phys(mem->pages[i]) & 0xFFFFF000UL) |
					    0x1UL);
		flush_dcache_range((अचिन्हित दीर्घ)__va(page_to_phys(mem->pages[i])),
				   (अचिन्हित दीर्घ)__va(page_to_phys(mem->pages[i]))+0x1000);
	पूर्ण
	mb();
	uninorth_tlbflush(mem);

	वापस 0;
पूर्ण

अटल पूर्णांक uninorth_हटाओ_memory(काष्ठा agp_memory *mem, off_t pg_start, पूर्णांक type)
अणु
	माप_प्रकार i;
	u32 *gp;
	पूर्णांक mask_type;

	अगर (type != mem->type)
		वापस -EINVAL;

	mask_type = agp_bridge->driver->agp_type_to_mask_type(agp_bridge, type);
	अगर (mask_type != 0) अणु
		/* We know nothing of memory types */
		वापस -EINVAL;
	पूर्ण

	अगर (mem->page_count == 0)
		वापस 0;

	gp = (u32 *) &agp_bridge->gatt_table[pg_start];
	क्रम (i = 0; i < mem->page_count; ++i) अणु
		gp[i] = scratch_value;
	पूर्ण
	mb();
	uninorth_tlbflush(mem);

	वापस 0;
पूर्ण

अटल व्योम uninorth_agp_enable(काष्ठा agp_bridge_data *bridge, u32 mode)
अणु
	u32 command, scratch, status;
	पूर्णांक समयout;

	pci_पढ़ो_config_dword(bridge->dev,
			      bridge->capndx + PCI_AGP_STATUS,
			      &status);

	command = agp_collect_device_status(bridge, mode, status);
	command |= PCI_AGP_COMMAND_AGP;

	अगर (uninorth_rev == 0x21) अणु
		/*
		 * Darwin disable AGP 4x on this revision, thus we
		 * may assume it's broken. This is an AGP2 controller.
		 */
		command &= ~AGPSTAT2_4X;
	पूर्ण

	अगर ((uninorth_rev >= 0x30) && (uninorth_rev <= 0x33)) अणु
		/*
		 * We need to set REQ_DEPTH to 7 क्रम U3 versions 1.0, 2.1,
		 * 2.2 and 2.3, Darwin करो so.
		 */
		अगर ((command >> AGPSTAT_RQ_DEPTH_SHIFT) > 7)
			command = (command & ~AGPSTAT_RQ_DEPTH)
				| (7 << AGPSTAT_RQ_DEPTH_SHIFT);
	पूर्ण

	uninorth_tlbflush(शून्य);

	समयout = 0;
	करो अणु
		pci_ग_लिखो_config_dword(bridge->dev,
				       bridge->capndx + PCI_AGP_COMMAND,
				       command);
		pci_पढ़ो_config_dword(bridge->dev,
				      bridge->capndx + PCI_AGP_COMMAND,
				       &scratch);
	पूर्ण जबतक ((scratch & PCI_AGP_COMMAND_AGP) == 0 && ++समयout < 1000);
	अगर ((scratch & PCI_AGP_COMMAND_AGP) == 0)
		dev_err(&bridge->dev->dev, "can't write UniNorth AGP "
			"command register\n");

	अगर (uninorth_rev >= 0x30) अणु
		/* This is an AGP V3 */
		agp_device_command(command, (status & AGPSTAT_MODE_3_0) != 0);
	पूर्ण अन्यथा अणु
		/* AGP V2 */
		agp_device_command(command, false);
	पूर्ण

	uninorth_tlbflush(शून्य);
पूर्ण

#अगर_घोषित CONFIG_PM
/*
 * These Power Management routines are _not_ called by the normal PCI PM layer,
 * but directly by the video driver through function poपूर्णांकers in the device
 * tree.
 */
अटल पूर्णांक agp_uninorth_suspend(काष्ठा pci_dev *pdev)
अणु
	काष्ठा agp_bridge_data *bridge;
	u32 cmd;
	u8 agp;
	काष्ठा pci_dev *device = शून्य;

	bridge = agp_find_bridge(pdev);
	अगर (bridge == शून्य)
		वापस -ENODEV;

	/* Only one suspend supported */
	अगर (bridge->dev_निजी_data)
		वापस 0;

	/* turn off AGP on the video chip, अगर it was enabled */
	क्रम_each_pci_dev(device) अणु
		/* Don't touch the bridge yet, device first */
		अगर (device == pdev)
			जारी;
		/* Only deal with devices on the same bus here, no Mac has a P2P
		 * bridge on the AGP port, and mucking around the entire PCI
		 * tree is source of problems on some machines because of a bug
		 * in some versions of pci_find_capability() when hitting a dead
		 * device
		 */
		अगर (device->bus != pdev->bus)
			जारी;
		agp = pci_find_capability(device, PCI_CAP_ID_AGP);
		अगर (!agp)
			जारी;
		pci_पढ़ो_config_dword(device, agp + PCI_AGP_COMMAND, &cmd);
		अगर (!(cmd & PCI_AGP_COMMAND_AGP))
			जारी;
		dev_info(&pdev->dev, "disabling AGP on device %s\n",
			 pci_name(device));
		cmd &= ~PCI_AGP_COMMAND_AGP;
		pci_ग_लिखो_config_dword(device, agp + PCI_AGP_COMMAND, cmd);
	पूर्ण

	/* turn off AGP on the bridge */
	agp = pci_find_capability(pdev, PCI_CAP_ID_AGP);
	pci_पढ़ो_config_dword(pdev, agp + PCI_AGP_COMMAND, &cmd);
	bridge->dev_निजी_data = (व्योम *)(दीर्घ)cmd;
	अगर (cmd & PCI_AGP_COMMAND_AGP) अणु
		dev_info(&pdev->dev, "disabling AGP on bridge\n");
		cmd &= ~PCI_AGP_COMMAND_AGP;
		pci_ग_लिखो_config_dword(pdev, agp + PCI_AGP_COMMAND, cmd);
	पूर्ण
	/* turn off the GART */
	uninorth_cleanup();

	वापस 0;
पूर्ण

अटल पूर्णांक agp_uninorth_resume(काष्ठा pci_dev *pdev)
अणु
	काष्ठा agp_bridge_data *bridge;
	u32 command;

	bridge = agp_find_bridge(pdev);
	अगर (bridge == शून्य)
		वापस -ENODEV;

	command = (दीर्घ)bridge->dev_निजी_data;
	bridge->dev_निजी_data = शून्य;
	अगर (!(command & PCI_AGP_COMMAND_AGP))
		वापस 0;

	uninorth_agp_enable(bridge, command);

	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_PM */

अटल काष्ठा अणु
	काष्ठा page **pages_arr;
पूर्ण uninorth_priv;

अटल पूर्णांक uninorth_create_gatt_table(काष्ठा agp_bridge_data *bridge)
अणु
	अक्षर *table;
	अक्षर *table_end;
	पूर्णांक size;
	पूर्णांक page_order;
	पूर्णांक num_entries;
	पूर्णांक i;
	व्योम *temp;
	काष्ठा page *page;

	/* We can't handle 2 level gatt's */
	अगर (bridge->driver->माप_प्रकारype == LVL2_APER_SIZE)
		वापस -EINVAL;

	table = शून्य;
	i = bridge->aperture_size_idx;
	temp = bridge->current_size;
	size = page_order = num_entries = 0;

	करो अणु
		size = A_SIZE_32(temp)->size;
		page_order = A_SIZE_32(temp)->page_order;
		num_entries = A_SIZE_32(temp)->num_entries;

		table = (अक्षर *) __get_मुक्त_pages(GFP_KERNEL, page_order);

		अगर (table == शून्य) अणु
			i++;
			bridge->current_size = A_IDX32(bridge);
		पूर्ण अन्यथा अणु
			bridge->aperture_size_idx = i;
		पूर्ण
	पूर्ण जबतक (!table && (i < bridge->driver->num_aperture_sizes));

	अगर (table == शून्य)
		वापस -ENOMEM;

	uninorth_priv.pages_arr = kदो_स्मृति_array(1 << page_order,
						माप(काष्ठा page *),
						GFP_KERNEL);
	अगर (uninorth_priv.pages_arr == शून्य)
		जाओ enomem;

	table_end = table + ((PAGE_SIZE * (1 << page_order)) - 1);

	क्रम (page = virt_to_page(table), i = 0; page <= virt_to_page(table_end);
	     page++, i++) अणु
		SetPageReserved(page);
		uninorth_priv.pages_arr[i] = page;
	पूर्ण

	bridge->gatt_table_real = (u32 *) table;
	/* Need to clear out any dirty data still sitting in caches */
	flush_dcache_range((अचिन्हित दीर्घ)table,
			   (अचिन्हित दीर्घ)table_end + 1);
	bridge->gatt_table = vmap(uninorth_priv.pages_arr, (1 << page_order), 0, PAGE_KERNEL_NCG);

	अगर (bridge->gatt_table == शून्य)
		जाओ enomem;

	bridge->gatt_bus_addr = virt_to_phys(table);

	अगर (is_u3)
		scratch_value = (page_to_phys(agp_bridge->scratch_page_page) >> PAGE_SHIFT) | 0x80000000UL;
	अन्यथा
		scratch_value =	cpu_to_le32((page_to_phys(agp_bridge->scratch_page_page) & 0xFFFFF000UL) |
				0x1UL);
	क्रम (i = 0; i < num_entries; i++)
		bridge->gatt_table[i] = scratch_value;

	वापस 0;

enomem:
	kमुक्त(uninorth_priv.pages_arr);
	अगर (table)
		मुक्त_pages((अचिन्हित दीर्घ)table, page_order);
	वापस -ENOMEM;
पूर्ण

अटल पूर्णांक uninorth_मुक्त_gatt_table(काष्ठा agp_bridge_data *bridge)
अणु
	पूर्णांक page_order;
	अक्षर *table, *table_end;
	व्योम *temp;
	काष्ठा page *page;

	temp = bridge->current_size;
	page_order = A_SIZE_32(temp)->page_order;

	/* Do not worry about मुक्तing memory, because अगर this is
	 * called, then all agp memory is deallocated and हटाओd
	 * from the table.
	 */

	vunmap(bridge->gatt_table);
	kमुक्त(uninorth_priv.pages_arr);
	table = (अक्षर *) bridge->gatt_table_real;
	table_end = table + ((PAGE_SIZE * (1 << page_order)) - 1);

	क्रम (page = virt_to_page(table); page <= virt_to_page(table_end); page++)
		ClearPageReserved(page);

	मुक्त_pages((अचिन्हित दीर्घ) bridge->gatt_table_real, page_order);

	वापस 0;
पूर्ण

अटल व्योम null_cache_flush(व्योम)
अणु
	mb();
पूर्ण

/* Setup function */

अटल स्थिर काष्ठा aper_size_info_32 uninorth_sizes[] =
अणु
	अणु256, 65536, 6, 64पूर्ण,
	अणु128, 32768, 5, 32पूर्ण,
	अणु64, 16384, 4, 16पूर्ण,
	अणु32, 8192, 3, 8पूर्ण,
	अणु16, 4096, 2, 4पूर्ण,
	अणु8, 2048, 1, 2पूर्ण,
	अणु4, 1024, 0, 1पूर्ण
पूर्ण;

/*
 * Not sure that u3 supports that high aperture sizes but it
 * would strange अगर it did not :)
 */
अटल स्थिर काष्ठा aper_size_info_32 u3_sizes[] =
अणु
	अणु512, 131072, 7, 128पूर्ण,
	अणु256, 65536, 6, 64पूर्ण,
	अणु128, 32768, 5, 32पूर्ण,
	अणु64, 16384, 4, 16पूर्ण,
	अणु32, 8192, 3, 8पूर्ण,
	अणु16, 4096, 2, 4पूर्ण,
	अणु8, 2048, 1, 2पूर्ण,
	अणु4, 1024, 0, 1पूर्ण
पूर्ण;

स्थिर काष्ठा agp_bridge_driver uninorth_agp_driver = अणु
	.owner			= THIS_MODULE,
	.aperture_sizes		= (व्योम *)uninorth_sizes,
	.माप_प्रकारype		= U32_APER_SIZE,
	.num_aperture_sizes	= ARRAY_SIZE(uninorth_sizes),
	.configure		= uninorth_configure,
	.fetch_size		= uninorth_fetch_size,
	.cleanup		= uninorth_cleanup,
	.tlb_flush		= uninorth_tlbflush,
	.mask_memory		= agp_generic_mask_memory,
	.masks			= शून्य,
	.cache_flush		= null_cache_flush,
	.agp_enable		= uninorth_agp_enable,
	.create_gatt_table	= uninorth_create_gatt_table,
	.मुक्त_gatt_table	= uninorth_मुक्त_gatt_table,
	.insert_memory		= uninorth_insert_memory,
	.हटाओ_memory		= uninorth_हटाओ_memory,
	.alloc_by_type		= agp_generic_alloc_by_type,
	.मुक्त_by_type		= agp_generic_मुक्त_by_type,
	.agp_alloc_page		= agp_generic_alloc_page,
	.agp_alloc_pages	= agp_generic_alloc_pages,
	.agp_destroy_page	= agp_generic_destroy_page,
	.agp_destroy_pages	= agp_generic_destroy_pages,
	.agp_type_to_mask_type  = agp_generic_type_to_mask_type,
	.cant_use_aperture	= true,
	.needs_scratch_page	= true,
पूर्ण;

स्थिर काष्ठा agp_bridge_driver u3_agp_driver = अणु
	.owner			= THIS_MODULE,
	.aperture_sizes		= (व्योम *)u3_sizes,
	.माप_प्रकारype		= U32_APER_SIZE,
	.num_aperture_sizes	= ARRAY_SIZE(u3_sizes),
	.configure		= uninorth_configure,
	.fetch_size		= uninorth_fetch_size,
	.cleanup		= uninorth_cleanup,
	.tlb_flush		= uninorth_tlbflush,
	.mask_memory		= agp_generic_mask_memory,
	.masks			= शून्य,
	.cache_flush		= null_cache_flush,
	.agp_enable		= uninorth_agp_enable,
	.create_gatt_table	= uninorth_create_gatt_table,
	.मुक्त_gatt_table	= uninorth_मुक्त_gatt_table,
	.insert_memory		= uninorth_insert_memory,
	.हटाओ_memory		= uninorth_हटाओ_memory,
	.alloc_by_type		= agp_generic_alloc_by_type,
	.मुक्त_by_type		= agp_generic_मुक्त_by_type,
	.agp_alloc_page		= agp_generic_alloc_page,
	.agp_alloc_pages	= agp_generic_alloc_pages,
	.agp_destroy_page	= agp_generic_destroy_page,
	.agp_destroy_pages	= agp_generic_destroy_pages,
	.agp_type_to_mask_type  = agp_generic_type_to_mask_type,
	.cant_use_aperture	= true,
	.needs_scratch_page	= true,
पूर्ण;

अटल काष्ठा agp_device_ids uninorth_agp_device_ids[] = अणु
	अणु
		.device_id	= PCI_DEVICE_ID_APPLE_UNI_N_AGP,
		.chipset_name	= "UniNorth",
	पूर्ण,
	अणु
		.device_id	= PCI_DEVICE_ID_APPLE_UNI_N_AGP_P,
		.chipset_name	= "UniNorth/Pangea",
	पूर्ण,
	अणु
		.device_id	= PCI_DEVICE_ID_APPLE_UNI_N_AGP15,
		.chipset_name	= "UniNorth 1.5",
	पूर्ण,
	अणु
		.device_id	= PCI_DEVICE_ID_APPLE_UNI_N_AGP2,
		.chipset_name	= "UniNorth 2",
	पूर्ण,
	अणु
		.device_id	= PCI_DEVICE_ID_APPLE_U3_AGP,
		.chipset_name	= "U3",
	पूर्ण,
	अणु
		.device_id	= PCI_DEVICE_ID_APPLE_U3L_AGP,
		.chipset_name	= "U3L",
	पूर्ण,
	अणु
		.device_id	= PCI_DEVICE_ID_APPLE_U3H_AGP,
		.chipset_name	= "U3H",
	पूर्ण,
	अणु
		.device_id	= PCI_DEVICE_ID_APPLE_IPID2_AGP,
		.chipset_name	= "UniNorth/Intrepid2",
	पूर्ण,
पूर्ण;

अटल पूर्णांक agp_uninorth_probe(काष्ठा pci_dev *pdev,
			      स्थिर काष्ठा pci_device_id *ent)
अणु
	काष्ठा agp_device_ids *devs = uninorth_agp_device_ids;
	काष्ठा agp_bridge_data *bridge;
	काष्ठा device_node *uninorth_node;
	u8 cap_ptr;
	पूर्णांक j;

	cap_ptr = pci_find_capability(pdev, PCI_CAP_ID_AGP);
	अगर (cap_ptr == 0)
		वापस -ENODEV;

	/* probe क्रम known chipsets */
	क्रम (j = 0; devs[j].chipset_name != शून्य; ++j) अणु
		अगर (pdev->device == devs[j].device_id) अणु
			dev_info(&pdev->dev, "Apple %s chipset\n",
				 devs[j].chipset_name);
			जाओ found;
		पूर्ण
	पूर्ण

	dev_err(&pdev->dev, "unsupported Apple chipset [%04x/%04x]\n",
		pdev->venकरोr, pdev->device);
	वापस -ENODEV;

 found:
	/* Set revision to 0 अगर we could not पढ़ो it. */
	uninorth_rev = 0;
	is_u3 = 0;
	/* Locate core99 Uni-N */
	uninorth_node = of_find_node_by_name(शून्य, "uni-n");
	/* Locate G5 u3 */
	अगर (uninorth_node == शून्य) अणु
		is_u3 = 1;
		uninorth_node = of_find_node_by_name(शून्य, "u3");
	पूर्ण
	अगर (uninorth_node) अणु
		स्थिर पूर्णांक *revprop = of_get_property(uninorth_node,
				"device-rev", शून्य);
		अगर (revprop != शून्य)
			uninorth_rev = *revprop & 0x3f;
		of_node_put(uninorth_node);
	पूर्ण

#अगर_घोषित CONFIG_PM
	/* Inक्रमm platक्रमm of our suspend/resume caps */
	pmac_रेजिस्टर_agp_pm(pdev, agp_uninorth_suspend, agp_uninorth_resume);
#पूर्ण_अगर

	/* Allocate & setup our driver */
	bridge = agp_alloc_bridge();
	अगर (!bridge)
		वापस -ENOMEM;

	अगर (is_u3)
		bridge->driver = &u3_agp_driver;
	अन्यथा
		bridge->driver = &uninorth_agp_driver;

	bridge->dev = pdev;
	bridge->capndx = cap_ptr;
	bridge->flags = AGP_ERRATA_FASTWRITES;

	/* Fill in the mode रेजिस्टर */
	pci_पढ़ो_config_dword(pdev, cap_ptr+PCI_AGP_STATUS, &bridge->mode);

	pci_set_drvdata(pdev, bridge);
	वापस agp_add_bridge(bridge);
पूर्ण

अटल व्योम agp_uninorth_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा agp_bridge_data *bridge = pci_get_drvdata(pdev);

#अगर_घोषित CONFIG_PM
	/* Inक्रमm platक्रमm of our suspend/resume caps */
	pmac_रेजिस्टर_agp_pm(pdev, शून्य, शून्य);
#पूर्ण_अगर

	agp_हटाओ_bridge(bridge);
	agp_put_bridge(bridge);
पूर्ण

अटल स्थिर काष्ठा pci_device_id agp_uninorth_pci_table[] = अणु
	अणु
	.class		= (PCI_CLASS_BRIDGE_HOST << 8),
	.class_mask	= ~0,
	.venकरोr		= PCI_VENDOR_ID_APPLE,
	.device		= PCI_ANY_ID,
	.subvenकरोr	= PCI_ANY_ID,
	.subdevice	= PCI_ANY_ID,
	पूर्ण,
	अणु पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, agp_uninorth_pci_table);

अटल काष्ठा pci_driver agp_uninorth_pci_driver = अणु
	.name		= "agpgart-uninorth",
	.id_table	= agp_uninorth_pci_table,
	.probe		= agp_uninorth_probe,
	.हटाओ		= agp_uninorth_हटाओ,
पूर्ण;

अटल पूर्णांक __init agp_uninorth_init(व्योम)
अणु
	अगर (agp_off)
		वापस -EINVAL;
	वापस pci_रेजिस्टर_driver(&agp_uninorth_pci_driver);
पूर्ण

अटल व्योम __निकास agp_uninorth_cleanup(व्योम)
अणु
	pci_unरेजिस्टर_driver(&agp_uninorth_pci_driver);
पूर्ण

module_init(agp_uninorth_init);
module_निकास(agp_uninorth_cleanup);

module_param(aperture, अक्षरp, 0);
MODULE_PARM_DESC(aperture,
		 "Aperture size, must be power of two between 4MB and an\n"
		 "\t\tupper limit specific to the UniNorth revision.\n"
		 "\t\tDefault: " DEFAULT_APERTURE_STRING "M");

MODULE_AUTHOR("Ben Herrenschmidt & Paul Mackerras");
MODULE_LICENSE("GPL");
