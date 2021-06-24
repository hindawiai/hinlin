<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Extensible Firmware Interface
 *
 * Based on Extensible Firmware Interface Specअगरication version 2.4
 *
 * Copyright (C) 2013 - 2015 Linaro Ltd.
 */

#घोषणा pr_fmt(fmt)	"efi: " fmt

#समावेश <linux/efi.h>
#समावेश <linux/fwnode.h>
#समावेश <linux/init.h>
#समावेश <linux/memblock.h>
#समावेश <linux/mm_types.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_fdt.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/screen_info.h>

#समावेश <यंत्र/efi.h>

अटल पूर्णांक __init is_memory(efi_memory_desc_t *md)
अणु
	अगर (md->attribute & (EFI_MEMORY_WB|EFI_MEMORY_WT|EFI_MEMORY_WC))
		वापस 1;
	वापस 0;
पूर्ण

/*
 * Translate a EFI भव address पूर्णांकo a physical address: this is necessary,
 * as some data members of the EFI प्रणाली table are भवly remapped after
 * SetVirtualAddressMap() has been called.
 */
अटल phys_addr_t __init efi_to_phys(अचिन्हित दीर्घ addr)
अणु
	efi_memory_desc_t *md;

	क्रम_each_efi_memory_desc(md) अणु
		अगर (!(md->attribute & EFI_MEMORY_RUNTIME))
			जारी;
		अगर (md->virt_addr == 0)
			/* no भव mapping has been installed by the stub */
			अवरोध;
		अगर (md->virt_addr <= addr &&
		    (addr - md->virt_addr) < (md->num_pages << EFI_PAGE_SHIFT))
			वापस md->phys_addr + addr - md->virt_addr;
	पूर्ण
	वापस addr;
पूर्ण

अटल __initdata अचिन्हित दीर्घ screen_info_table = EFI_INVALID_TABLE_ADDR;
अटल __initdata अचिन्हित दीर्घ cpu_state_table = EFI_INVALID_TABLE_ADDR;

अटल स्थिर efi_config_table_type_t arch_tables[] __initस्थिर = अणु
	अणुLINUX_EFI_ARM_SCREEN_INFO_TABLE_GUID, &screen_info_tableपूर्ण,
	अणुLINUX_EFI_ARM_CPU_STATE_TABLE_GUID, &cpu_state_tableपूर्ण,
	अणुपूर्ण
पूर्ण;

अटल व्योम __init init_screen_info(व्योम)
अणु
	काष्ठा screen_info *si;

	अगर (IS_ENABLED(CONFIG_ARM) &&
	    screen_info_table != EFI_INVALID_TABLE_ADDR) अणु
		si = early_memremap_ro(screen_info_table, माप(*si));
		अगर (!si) अणु
			pr_err("Could not map screen_info config table\n");
			वापस;
		पूर्ण
		screen_info = *si;
		early_memunmap(si, माप(*si));

		/* dummycon on ARM needs non-zero values क्रम columns/lines */
		screen_info.orig_video_cols = 80;
		screen_info.orig_video_lines = 25;
	पूर्ण

	अगर (screen_info.orig_video_isVGA == VIDEO_TYPE_EFI &&
	    memblock_is_map_memory(screen_info.lfb_base))
		memblock_mark_nomap(screen_info.lfb_base, screen_info.lfb_size);
पूर्ण

अटल पूर्णांक __init uefi_init(u64 efi_प्रणाली_table)
अणु
	efi_config_table_t *config_tables;
	efi_प्रणाली_table_t *systab;
	माप_प्रकार table_size;
	पूर्णांक retval;

	systab = early_memremap_ro(efi_प्रणाली_table, माप(efi_प्रणाली_table_t));
	अगर (systab == शून्य) अणु
		pr_warn("Unable to map EFI system table.\n");
		वापस -ENOMEM;
	पूर्ण

	set_bit(EFI_BOOT, &efi.flags);
	अगर (IS_ENABLED(CONFIG_64BIT))
		set_bit(EFI_64BIT, &efi.flags);

	retval = efi_systab_check_header(&systab->hdr, 2);
	अगर (retval)
		जाओ out;

	efi.runसमय = systab->runसमय;
	efi.runसमय_version = systab->hdr.revision;

	efi_systab_report_header(&systab->hdr, efi_to_phys(systab->fw_venकरोr));

	table_size = माप(efi_config_table_t) * systab->nr_tables;
	config_tables = early_memremap_ro(efi_to_phys(systab->tables),
					  table_size);
	अगर (config_tables == शून्य) अणु
		pr_warn("Unable to map EFI config table array.\n");
		retval = -ENOMEM;
		जाओ out;
	पूर्ण
	retval = efi_config_parse_tables(config_tables, systab->nr_tables,
					 IS_ENABLED(CONFIG_ARM) ? arch_tables
								: शून्य);

	early_memunmap(config_tables, table_size);
out:
	early_memunmap(systab, माप(efi_प्रणाली_table_t));
	वापस retval;
पूर्ण

/*
 * Return true क्रम regions that can be used as System RAM.
 */
अटल __init पूर्णांक is_usable_memory(efi_memory_desc_t *md)
अणु
	चयन (md->type) अणु
	हाल EFI_LOADER_CODE:
	हाल EFI_LOADER_DATA:
	हाल EFI_ACPI_RECLAIM_MEMORY:
	हाल EFI_BOOT_SERVICES_CODE:
	हाल EFI_BOOT_SERVICES_DATA:
	हाल EFI_CONVENTIONAL_MEMORY:
	हाल EFI_PERSISTENT_MEMORY:
		/*
		 * Special purpose memory is 'soft reserved', which means it
		 * is set aside initially, but can be hotplugged back in or
		 * be asचिन्हित to the dax driver after boot.
		 */
		अगर (efi_soft_reserve_enabled() &&
		    (md->attribute & EFI_MEMORY_SP))
			वापस false;

		/*
		 * According to the spec, these regions are no दीर्घer reserved
		 * after calling ExitBootServices(). However, we can only use
		 * them as System RAM अगर they can be mapped ग_लिखोback cacheable.
		 */
		वापस (md->attribute & EFI_MEMORY_WB);
	शेष:
		अवरोध;
	पूर्ण
	वापस false;
पूर्ण

अटल __init व्योम reserve_regions(व्योम)
अणु
	efi_memory_desc_t *md;
	u64 paddr, npages, size;

	अगर (efi_enabled(EFI_DBG))
		pr_info("Processing EFI memory map:\n");

	/*
	 * Discard memblocks discovered so far: अगर there are any at this
	 * poपूर्णांक, they originate from memory nodes in the DT, and UEFI
	 * uses its own memory map instead.
	 */
	memblock_dump_all();
	memblock_हटाओ(0, PHYS_ADDR_MAX);

	क्रम_each_efi_memory_desc(md) अणु
		paddr = md->phys_addr;
		npages = md->num_pages;

		अगर (efi_enabled(EFI_DBG)) अणु
			अक्षर buf[64];

			pr_info("  0x%012llx-0x%012llx %s\n",
				paddr, paddr + (npages << EFI_PAGE_SHIFT) - 1,
				efi_md_typeattr_क्रमmat(buf, माप(buf), md));
		पूर्ण

		memrange_efi_to_native(&paddr, &npages);
		size = npages << PAGE_SHIFT;

		अगर (is_memory(md)) अणु
			early_init_dt_add_memory_arch(paddr, size);

			अगर (!is_usable_memory(md))
				memblock_mark_nomap(paddr, size);

			/* keep ACPI reclaim memory पूर्णांकact क्रम kexec etc. */
			अगर (md->type == EFI_ACPI_RECLAIM_MEMORY)
				memblock_reserve(paddr, size);
		पूर्ण
	पूर्ण
पूर्ण

व्योम __init efi_init(व्योम)
अणु
	काष्ठा efi_memory_map_data data;
	u64 efi_प्रणाली_table;

	/* Grab UEFI inक्रमmation placed in FDT by stub */
	efi_प्रणाली_table = efi_get_fdt_params(&data);
	अगर (!efi_प्रणाली_table)
		वापस;

	अगर (efi_memmap_init_early(&data) < 0) अणु
		/*
		* If we are booting via UEFI, the UEFI memory map is the only
		* description of memory we have, so there is little poपूर्णांक in
		* proceeding अगर we cannot access it.
		*/
		panic("Unable to map EFI memory map.\n");
	पूर्ण

	WARN(efi.memmap.desc_version != 1,
	     "Unexpected EFI_MEMORY_DESCRIPTOR version %ld",
	      efi.memmap.desc_version);

	अगर (uefi_init(efi_प्रणाली_table) < 0) अणु
		efi_memmap_unmap();
		वापस;
	पूर्ण

	reserve_regions();
	efi_esrt_init();
	efi_mokvar_table_init();

	memblock_reserve(data.phys_map & PAGE_MASK,
			 PAGE_ALIGN(data.size + (data.phys_map & ~PAGE_MASK)));

	init_screen_info();

#अगर_घोषित CONFIG_ARM
	/* ARM करोes not permit early mappings to persist across paging_init() */
	efi_memmap_unmap();

	अगर (cpu_state_table != EFI_INVALID_TABLE_ADDR) अणु
		काष्ठा efi_arm_entry_state *state;
		bool dump_state = true;

		state = early_memremap_ro(cpu_state_table,
					  माप(काष्ठा efi_arm_entry_state));
		अगर (state == शून्य) अणु
			pr_warn("Unable to map CPU entry state table.\n");
			वापस;
		पूर्ण

		अगर ((state->sctlr_beक्रमe_ebs & 1) == 0)
			pr_warn(FW_BUG "EFI stub was entered with MMU and Dcache disabled, please fix your firmware!\n");
		अन्यथा अगर ((state->sctlr_after_ebs & 1) == 0)
			pr_warn(FW_BUG "ExitBootServices() returned with MMU and Dcache disabled, please fix your firmware!\n");
		अन्यथा
			dump_state = false;

		अगर (dump_state || efi_enabled(EFI_DBG)) अणु
			pr_info("CPSR at EFI stub entry        : 0x%08x\n", state->cpsr_beक्रमe_ebs);
			pr_info("SCTLR at EFI stub entry       : 0x%08x\n", state->sctlr_beक्रमe_ebs);
			pr_info("CPSR after ExitBootServices() : 0x%08x\n", state->cpsr_after_ebs);
			pr_info("SCTLR after ExitBootServices(): 0x%08x\n", state->sctlr_after_ebs);
		पूर्ण
		early_memunmap(state, माप(काष्ठा efi_arm_entry_state));
	पूर्ण
#पूर्ण_अगर
पूर्ण

अटल bool efअगरb_overlaps_pci_range(स्थिर काष्ठा of_pci_range *range)
अणु
	u64 fb_base = screen_info.lfb_base;

	अगर (screen_info.capabilities & VIDEO_CAPABILITY_64BIT_BASE)
		fb_base |= (u64)(अचिन्हित दीर्घ)screen_info.ext_lfb_base << 32;

	वापस fb_base >= range->cpu_addr &&
	       fb_base < (range->cpu_addr + range->size);
पूर्ण

अटल काष्ठा device_node *find_pci_overlap_node(व्योम)
अणु
	काष्ठा device_node *np;

	क्रम_each_node_by_type(np, "pci") अणु
		काष्ठा of_pci_range_parser parser;
		काष्ठा of_pci_range range;
		पूर्णांक err;

		err = of_pci_range_parser_init(&parser, np);
		अगर (err) अणु
			pr_warn("of_pci_range_parser_init() failed: %d\n", err);
			जारी;
		पूर्ण

		क्रम_each_of_pci_range(&parser, &range)
			अगर (efअगरb_overlaps_pci_range(&range))
				वापस np;
	पूर्ण
	वापस शून्य;
पूर्ण

/*
 * If the efअगरb framebuffer is backed by a PCI graphics controller, we have
 * to ensure that this relation is expressed using a device link when
 * running in DT mode, or the probe order may be reversed, resulting in a
 * resource reservation conflict on the memory winकरोw that the efअगरb
 * framebuffer steals from the PCIe host bridge.
 */
अटल पूर्णांक efअगरb_add_links(काष्ठा fwnode_handle *fwnode)
अणु
	काष्ठा device_node *sup_np;

	sup_np = find_pci_overlap_node();

	/*
	 * If there's no PCI graphics controller backing the efअगरb, we are
	 * करोne here.
	 */
	अगर (!sup_np)
		वापस 0;

	fwnode_link_add(fwnode, of_fwnode_handle(sup_np));
	of_node_put(sup_np);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा fwnode_operations efअगरb_fwnode_ops = अणु
	.add_links = efअगरb_add_links,
पूर्ण;

अटल काष्ठा fwnode_handle efअगरb_fwnode;

अटल पूर्णांक __init रेजिस्टर_gop_device(व्योम)
अणु
	काष्ठा platक्रमm_device *pd;
	पूर्णांक err;

	अगर (screen_info.orig_video_isVGA != VIDEO_TYPE_EFI)
		वापस 0;

	pd = platक्रमm_device_alloc("efi-framebuffer", 0);
	अगर (!pd)
		वापस -ENOMEM;

	अगर (IS_ENABLED(CONFIG_PCI)) अणु
		fwnode_init(&efअगरb_fwnode, &efअगरb_fwnode_ops);
		pd->dev.fwnode = &efअगरb_fwnode;
	पूर्ण

	err = platक्रमm_device_add_data(pd, &screen_info, माप(screen_info));
	अगर (err)
		वापस err;

	वापस platक्रमm_device_add(pd);
पूर्ण
subsys_initcall(रेजिस्टर_gop_device);
