<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * inventory.c
 *
 * Copyright (c) 1999 The Puffin Group (David Kennedy and Alex deVries)
 * Copyright (c) 2001 Matthew Wilcox क्रम Hewlett-Packard
 *
 * These are the routines to discover what hardware exists in this box.
 * This task is complicated by there being 3 dअगरferent ways of
 * perक्रमming an inventory, depending largely on the age of the box.
 * The recommended way to करो this is to check to see whether the machine
 * is a `Snake' first, then try System Map, then try PAT.  We try System
 * Map beक्रमe checking क्रम a Snake -- this probably करोesn't cause any
 * problems, but...
 */

#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/mm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <यंत्र/hardware.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/mmzone.h>
#समावेश <यंत्र/pdc.h>
#समावेश <यंत्र/pdcpat.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/parisc-device.h>
#समावेश <यंत्र/tlbflush.h>

/*
** Debug options
** DEBUG_PAT Dump details which PDC PAT provides about ranges/devices.
*/
#अघोषित DEBUG_PAT

पूर्णांक pdc_type __ro_after_init = PDC_TYPE_ILLEGAL;

/* cell number and location (PAT firmware only) */
अचिन्हित दीर्घ parisc_cell_num __ro_after_init;
अचिन्हित दीर्घ parisc_cell_loc __ro_after_init;
अचिन्हित दीर्घ parisc_pat_pdc_cap __ro_after_init;


व्योम __init setup_pdc(व्योम)
अणु
	दीर्घ status;
	अचिन्हित पूर्णांक bus_id;
	काष्ठा pdc_प्रणाली_map_mod_info module_result;
	काष्ठा pdc_module_path module_path;
	काष्ठा pdc_model model;
#अगर_घोषित CONFIG_64BIT
	काष्ठा pdc_pat_cell_num cell_info;
#पूर्ण_अगर

	/* Determine the pdc "type" used on this machine */

	prपूर्णांकk(KERN_INFO "Determining PDC firmware type: ");

	status = pdc_प्रणाली_map_find_mods(&module_result, &module_path, 0);
	अगर (status == PDC_OK) अणु
		pdc_type = PDC_TYPE_SYSTEM_MAP;
		pr_cont("System Map.\n");
		वापस;
	पूर्ण

	/*
	 * If the machine करोesn't support PDC_SYSTEM_MAP then either it
	 * is a pdc pat box, or it is an older box. All 64 bit capable
	 * machines are either pdc pat boxes or they support PDC_SYSTEM_MAP.
	 */

	/*
	 * TODO: We should test क्रम 64 bit capability and give a
	 * clearer message.
	 */

#अगर_घोषित CONFIG_64BIT
	status = pdc_pat_cell_get_number(&cell_info);
	अगर (status == PDC_OK) अणु
		अचिन्हित दीर्घ legacy_rev, pat_rev;
		pdc_type = PDC_TYPE_PAT;
		pr_cont("64 bit PAT.\n");
		parisc_cell_num = cell_info.cell_num;
		parisc_cell_loc = cell_info.cell_loc;
		pr_info("PAT: Running on cell %lu and location %lu.\n",
			parisc_cell_num, parisc_cell_loc);
		status = pdc_pat_pd_get_pdc_revisions(&legacy_rev,
			&pat_rev, &parisc_pat_pdc_cap);
		pr_info("PAT: legacy revision 0x%lx, pat_rev 0x%lx, pdc_cap 0x%lx, S-PTLB %d, HPMC_RENDEZ %d.\n",
			legacy_rev, pat_rev, parisc_pat_pdc_cap,
			parisc_pat_pdc_cap
			 & PDC_PAT_CAPABILITY_BIT_SIMULTANEOUS_PTLB ? 1:0,
			parisc_pat_pdc_cap
			 & PDC_PAT_CAPABILITY_BIT_PDC_HPMC_RENDEZ   ? 1:0);
		वापस;
	पूर्ण
#पूर्ण_अगर

	/* Check the CPU's bus ID.  There's probably a better test.  */

	status = pdc_model_info(&model);

	bus_id = (model.hversion >> (4 + 7)) & 0x1f;

	चयन (bus_id) अणु
	हाल 0x4:		/* 720, 730, 750, 735, 755 */
	हाल 0x6:		/* 705, 710 */
	हाल 0x7:		/* 715, 725 */
	हाल 0x8:		/* 745, 747, 742 */
	हाल 0xA:		/* 712 and similar */
	हाल 0xC:		/* 715/64, at least */

		pdc_type = PDC_TYPE_SNAKE;
		pr_cont("Snake.\n");
		वापस;

	शेष:		/* Everything अन्यथा */

		pr_cont("Unsupported.\n");
		panic("If this is a 64-bit machine, please try a 64-bit kernel.\n");
	पूर्ण
पूर्ण

#घोषणा PDC_PAGE_ADJ_SHIFT (PAGE_SHIFT - 12) /* pdc pages are always 4k */

अटल व्योम __init
set_pmem_entry(physmem_range_t *pmem_ptr, अचिन्हित दीर्घ start,
	       अचिन्हित दीर्घ pages4k)
अणु
	/* Rather than aligning and potentially throwing away
	 * memory, we'll assume that any ranges are alपढ़ोy
	 * nicely aligned with any reasonable page size, and
	 * panic अगर they are not (it's more likely that the
	 * pdc info is bad in this हाल).
	 */

	अगर (unlikely( ((start & (PAGE_SIZE - 1)) != 0)
	    || ((pages4k & ((1UL << PDC_PAGE_ADJ_SHIFT) - 1)) != 0) )) अणु

		panic("Memory range doesn't align with page size!\n");
	पूर्ण

	pmem_ptr->start_pfn = (start >> PAGE_SHIFT);
	pmem_ptr->pages = (pages4k >> PDC_PAGE_ADJ_SHIFT);
पूर्ण

अटल व्योम __init pagezero_memconfig(व्योम)
अणु
	अचिन्हित दीर्घ npages;

	/* Use the 32 bit inक्रमmation from page zero to create a single
	 * entry in the pmem_ranges[] table.
	 *
	 * We currently करोn't support machines with contiguous memory
	 * >= 4 Gb, who report that memory using 64 bit only fields
	 * on page zero. It's not worth करोing until it can be tested,
	 * and it is not clear we can support those machines क्रम other
	 * reasons.
	 *
	 * If that support is करोne in the future, this is where it
	 * should be करोne.
	 */

	npages = (PAGE_ALIGN(PAGE0->imm_max_mem) >> PAGE_SHIFT);
	set_pmem_entry(pmem_ranges,0UL,npages);
	npmem_ranges = 1;
पूर्ण

#अगर_घोषित CONFIG_64BIT

/* All of the PDC PAT specअगरic code is 64-bit only */

/*
**  The module object is filled via PDC_PAT_CELL[Return Cell Module].
**  If a module is found, रेजिस्टर module will get the IODC bytes via
**  pdc_iodc_पढ़ो() using the PA view of conf_base_addr क्रम the hpa parameter.
**
**  The IO view can be used by PDC_PAT_CELL[Return Cell Module]
**  only क्रम SBAs and LBAs.  This view will cause an invalid
**  argument error क्रम all other cell module types.
**
*/

अटल पूर्णांक __init 
pat_query_module(uदीर्घ pcell_loc, uदीर्घ mod_index)
अणु
	pdc_pat_cell_mod_maddr_block_t *pa_pdc_cell;
	अचिन्हित दीर्घ bytecnt;
	अचिन्हित दीर्घ temp;	/* 64-bit scratch value */
	दीर्घ status;		/* PDC वापस value status */
	काष्ठा parisc_device *dev;

	pa_pdc_cell = kदो_स्मृति(माप (*pa_pdc_cell), GFP_KERNEL);
	अगर (!pa_pdc_cell)
		panic("couldn't allocate memory for PDC_PAT_CELL!");

	/* वापस cell module (PA or Processor view) */
	status = pdc_pat_cell_module(&bytecnt, pcell_loc, mod_index,
				     PA_VIEW, pa_pdc_cell);

	अगर (status != PDC_OK) अणु
		/* no more cell modules or error */
		kमुक्त(pa_pdc_cell);
		वापस status;
	पूर्ण

	temp = pa_pdc_cell->cba;
	dev = alloc_pa_dev(PAT_GET_CBA(temp), &(pa_pdc_cell->mod_path));
	अगर (!dev) अणु
		kमुक्त(pa_pdc_cell);
		वापस PDC_OK;
	पूर्ण

	/* alloc_pa_dev sets dev->hpa */

	/*
	** save parameters in the parisc_device
	** (The idea being the device driver will call pdc_pat_cell_module()
	** and store the results in its own data काष्ठाure.)
	*/
	dev->pcell_loc = pcell_loc;
	dev->mod_index = mod_index;

	/* save generic info वापसed from the call */
	/* REVISIT: who is the consumer of this? not sure yet... */
	dev->mod_info = pa_pdc_cell->mod_info;	/* pass to PAT_GET_ENTITY() */
	dev->pmod_loc = pa_pdc_cell->mod_location;
	dev->mod0 = pa_pdc_cell->mod[0];

	रेजिस्टर_parisc_device(dev);	/* advertise device */

#अगर_घोषित DEBUG_PAT
	/* dump what we see so far... */
	चयन (PAT_GET_ENTITY(dev->mod_info)) अणु
		pdc_pat_cell_mod_maddr_block_t io_pdc_cell;
		अचिन्हित दीर्घ i;

	हाल PAT_ENTITY_PROC:
		prपूर्णांकk(KERN_DEBUG "PAT_ENTITY_PROC: id_eid 0x%lx\n",
			pa_pdc_cell->mod[0]);
		अवरोध;

	हाल PAT_ENTITY_MEM:
		prपूर्णांकk(KERN_DEBUG 
			"PAT_ENTITY_MEM: amount 0x%lx min_gni_base 0x%lx min_gni_len 0x%lx\n",
			pa_pdc_cell->mod[0], pa_pdc_cell->mod[1],
			pa_pdc_cell->mod[2]);
		अवरोध;
	हाल PAT_ENTITY_CA:
		prपूर्णांकk(KERN_DEBUG "PAT_ENTITY_CA: %ld\n", pcell_loc);
		अवरोध;

	हाल PAT_ENTITY_PBC:
		prपूर्णांकk(KERN_DEBUG "PAT_ENTITY_PBC: ");
		जाओ prपूर्णांक_ranges;

	हाल PAT_ENTITY_SBA:
		prपूर्णांकk(KERN_DEBUG "PAT_ENTITY_SBA: ");
		जाओ prपूर्णांक_ranges;

	हाल PAT_ENTITY_LBA:
		prपूर्णांकk(KERN_DEBUG "PAT_ENTITY_LBA: ");

 prपूर्णांक_ranges:
		pdc_pat_cell_module(&bytecnt, pcell_loc, mod_index,
				    IO_VIEW, &io_pdc_cell);
		prपूर्णांकk(KERN_DEBUG "ranges %ld\n", pa_pdc_cell->mod[1]);
		क्रम (i = 0; i < pa_pdc_cell->mod[1]; i++) अणु
			prपूर्णांकk(KERN_DEBUG 
				"  PA_VIEW %ld: 0x%016lx 0x%016lx 0x%016lx\n", 
				i, pa_pdc_cell->mod[2 + i * 3],	/* type */
				pa_pdc_cell->mod[3 + i * 3],	/* start */
				pa_pdc_cell->mod[4 + i * 3]);	/* finish (ie end) */
			prपूर्णांकk(KERN_DEBUG 
				"  IO_VIEW %ld: 0x%016lx 0x%016lx 0x%016lx\n", 
				i, io_pdc_cell.mod[2 + i * 3],	/* type */
				io_pdc_cell.mod[3 + i * 3],	/* start */
				io_pdc_cell.mod[4 + i * 3]);	/* finish (ie end) */
		पूर्ण
		prपूर्णांकk(KERN_DEBUG "\n");
		अवरोध;
	पूर्ण
#पूर्ण_अगर /* DEBUG_PAT */

	kमुक्त(pa_pdc_cell);

	वापस PDC_OK;
पूर्ण


/* pat pdc can वापस inक्रमmation about a variety of dअगरferent
 * types of memory (e.g. firmware,i/o, etc) but we only care about
 * the usable physical ram right now. Since the firmware specअगरic
 * inक्रमmation is allocated on the stack, we'll be generous, in
 * हाल there is a lot of other inक्रमmation we करोn't care about.
 */

#घोषणा PAT_MAX_RANGES (4 * MAX_PHYSMEM_RANGES)

अटल व्योम __init pat_memconfig(व्योम)
अणु
	अचिन्हित दीर्घ actual_len;
	काष्ठा pdc_pat_pd_addr_map_entry mem_table[PAT_MAX_RANGES+1];
	काष्ठा pdc_pat_pd_addr_map_entry *mtbl_ptr;
	physmem_range_t *pmem_ptr;
	दीर्घ status;
	पूर्णांक entries;
	अचिन्हित दीर्घ length;
	पूर्णांक i;

	length = (PAT_MAX_RANGES + 1) * माप(काष्ठा pdc_pat_pd_addr_map_entry);

	status = pdc_pat_pd_get_addr_map(&actual_len, mem_table, length, 0L);

	अगर ((status != PDC_OK)
	    || ((actual_len % माप(काष्ठा pdc_pat_pd_addr_map_entry)) != 0)) अणु

		/* The above pdc call shouldn't fail, but, just in
		 * हाल, just use the PAGE0 info.
		 */

		prपूर्णांकk("\n\n\n");
		prपूर्णांकk(KERN_WARNING "WARNING! Could not get full memory configuration. "
			"All memory may not be used!\n\n\n");
		pagezero_memconfig();
		वापस;
	पूर्ण

	entries = actual_len / माप(काष्ठा pdc_pat_pd_addr_map_entry);

	अगर (entries > PAT_MAX_RANGES) अणु
		prपूर्णांकk(KERN_WARNING "This Machine has more memory ranges than we support!\n");
		prपूर्णांकk(KERN_WARNING "Some memory may not be used!\n");
	पूर्ण

	/* Copy inक्रमmation पूर्णांकo the firmware independent pmem_ranges
	 * array, skipping types we करोn't care about. Notice we said
	 * "may" above. We'll use all the entries that were वापसed.
	 */

	npmem_ranges = 0;
	mtbl_ptr = mem_table;
	pmem_ptr = pmem_ranges; /* Global firmware independent table */
	क्रम (i = 0; i < entries; i++,mtbl_ptr++) अणु
		अगर (   (mtbl_ptr->entry_type != PAT_MEMORY_DESCRIPTOR)
		    || (mtbl_ptr->memory_type != PAT_MEMTYPE_MEMORY)
		    || (mtbl_ptr->pages == 0)
		    || (   (mtbl_ptr->memory_usage != PAT_MEMUSE_GENERAL)
			&& (mtbl_ptr->memory_usage != PAT_MEMUSE_GI)
			&& (mtbl_ptr->memory_usage != PAT_MEMUSE_GNI) ) ) अणु

			जारी;
		पूर्ण

		अगर (npmem_ranges == MAX_PHYSMEM_RANGES) अणु
			prपूर्णांकk(KERN_WARNING "This Machine has more memory ranges than we support!\n");
			prपूर्णांकk(KERN_WARNING "Some memory will not be used!\n");
			अवरोध;
		पूर्ण

		set_pmem_entry(pmem_ptr++,mtbl_ptr->paddr,mtbl_ptr->pages);
		npmem_ranges++;
	पूर्ण
पूर्ण

अटल पूर्णांक __init pat_inventory(व्योम)
अणु
	पूर्णांक status;
	uदीर्घ mod_index = 0;
	काष्ठा pdc_pat_cell_num cell_info;

	/*
	** Note:  Prelude (and it's successors: Lclass, A400/500) only
	**        implement PDC_PAT_CELL sub-options 0 and 2.
	*/
	status = pdc_pat_cell_get_number(&cell_info);
	अगर (status != PDC_OK) अणु
		वापस 0;
	पूर्ण

#अगर_घोषित DEBUG_PAT
	prपूर्णांकk(KERN_DEBUG "CELL_GET_NUMBER: 0x%lx 0x%lx\n", cell_info.cell_num, 
	       cell_info.cell_loc);
#पूर्ण_अगर

	जबतक (PDC_OK == pat_query_module(cell_info.cell_loc, mod_index)) अणु
		mod_index++;
	पूर्ण

	वापस mod_index;
पूर्ण

/* We only look क्रम extended memory ranges on a 64 bit capable box */
अटल व्योम __init sprockets_memconfig(व्योम)
अणु
	काष्ठा pdc_memory_table_raddr r_addr;
	काष्ठा pdc_memory_table mem_table[MAX_PHYSMEM_RANGES];
	काष्ठा pdc_memory_table *mtbl_ptr;
	physmem_range_t *pmem_ptr;
	दीर्घ status;
	पूर्णांक entries;
	पूर्णांक i;

	status = pdc_mem_mem_table(&r_addr,mem_table,
				(अचिन्हित दीर्घ)MAX_PHYSMEM_RANGES);

	अगर (status != PDC_OK) अणु

		/* The above pdc call only works on boxes with sprockets
		 * firmware (newer B,C,J class). Other non PAT PDC machines
		 * करो support more than 3.75 Gb of memory, but we करोn't
		 * support them yet.
		 */

		pagezero_memconfig();
		वापस;
	पूर्ण

	अगर (r_addr.entries_total > MAX_PHYSMEM_RANGES) अणु
		prपूर्णांकk(KERN_WARNING "This Machine has more memory ranges than we support!\n");
		prपूर्णांकk(KERN_WARNING "Some memory will not be used!\n");
	पूर्ण

	entries = (पूर्णांक)r_addr.entries_वापसed;

	npmem_ranges = 0;
	mtbl_ptr = mem_table;
	pmem_ptr = pmem_ranges; /* Global firmware independent table */
	क्रम (i = 0; i < entries; i++,mtbl_ptr++) अणु
		set_pmem_entry(pmem_ptr++,mtbl_ptr->paddr,mtbl_ptr->pages);
		npmem_ranges++;
	पूर्ण
पूर्ण

#अन्यथा   /* !CONFIG_64BIT */

#घोषणा pat_inventory() करो अणु पूर्ण जबतक (0)
#घोषणा pat_memconfig() करो अणु पूर्ण जबतक (0)
#घोषणा sprockets_memconfig() pagezero_memconfig()

#पूर्ण_अगर	/* !CONFIG_64BIT */


#अगर_अघोषित CONFIG_PA20

/* Code to support Snake machines (7[2350], 7[235]5, 715/Scorpio) */

अटल काष्ठा parisc_device * __init
legacy_create_device(काष्ठा pdc_memory_map *r_addr,
		काष्ठा pdc_module_path *module_path)
अणु
	काष्ठा parisc_device *dev;
	पूर्णांक status = pdc_mem_map_hpa(r_addr, module_path);
	अगर (status != PDC_OK)
		वापस शून्य;

	dev = alloc_pa_dev(r_addr->hpa, &module_path->path);
	अगर (dev == शून्य)
		वापस शून्य;

	रेजिस्टर_parisc_device(dev);
	वापस dev;
पूर्ण

/**
 * snake_inventory
 *
 * Beक्रमe PDC_SYSTEM_MAP was invented, the PDC_MEM_MAP call was used.
 * To use it, we initialise the mod_path.bc to 0xff and try all values of
 * mod to get the HPA क्रम the top-level devices.  Bus adapters may have
 * sub-devices which are discovered by setting bc[5] to 0 and bc[4] to the
 * module, then trying all possible functions.
 */
अटल व्योम __init snake_inventory(व्योम)
अणु
	पूर्णांक mod;
	क्रम (mod = 0; mod < 16; mod++) अणु
		काष्ठा parisc_device *dev;
		काष्ठा pdc_module_path module_path;
		काष्ठा pdc_memory_map r_addr;
		अचिन्हित पूर्णांक func;

		स_रखो(module_path.path.bc, 0xff, 6);
		module_path.path.mod = mod;
		dev = legacy_create_device(&r_addr, &module_path);
		अगर ((!dev) || (dev->id.hw_type != HPHW_BA))
			जारी;

		स_रखो(module_path.path.bc, 0xff, 4);
		module_path.path.bc[4] = mod;

		क्रम (func = 0; func < 16; func++) अणु
			module_path.path.bc[5] = 0;
			module_path.path.mod = func;
			legacy_create_device(&r_addr, &module_path);
		पूर्ण
	पूर्ण
पूर्ण

#अन्यथा /* CONFIG_PA20 */
#घोषणा snake_inventory() करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर  /* CONFIG_PA20 */

/* Common 32/64 bit based code goes here */

/**
 * add_प्रणाली_map_addresses - Add additional addresses to the parisc device.
 * @dev: The parisc device.
 * @num_addrs: Then number of addresses to add;
 * @module_instance: The प्रणाली_map module instance.
 *
 * This function adds any additional addresses reported by the प्रणाली_map
 * firmware to the parisc device.
 */
अटल व्योम __init
add_प्रणाली_map_addresses(काष्ठा parisc_device *dev, पूर्णांक num_addrs, 
			 पूर्णांक module_instance)
अणु
	पूर्णांक i;
	दीर्घ status;
	काष्ठा pdc_प्रणाली_map_addr_info addr_result;

	dev->addr = kदो_स्मृति_array(num_addrs, माप(*dev->addr), GFP_KERNEL);
	अगर(!dev->addr) अणु
		prपूर्णांकk(KERN_ERR "%s %s(): memory allocation failure\n",
		       __खाता__, __func__);
		वापस;
	पूर्ण

	क्रम(i = 1; i <= num_addrs; ++i) अणु
		status = pdc_प्रणाली_map_find_addrs(&addr_result, 
						   module_instance, i);
		अगर(PDC_OK == status) अणु
			dev->addr[dev->num_addrs] = (अचिन्हित दीर्घ)addr_result.mod_addr;
			dev->num_addrs++;
		पूर्ण अन्यथा अणु
			prपूर्णांकk(KERN_WARNING 
			       "Bad PDC_FIND_ADDRESS status return (%ld) for index %d\n",
			       status, i);
		पूर्ण
	पूर्ण
पूर्ण

/**
 * प्रणाली_map_inventory - Retrieve firmware devices via SYSTEM_MAP.
 *
 * This function attempts to retrieve and रेजिस्टर all the devices firmware
 * knows about via the SYSTEM_MAP PDC call.
 */
अटल व्योम __init प्रणाली_map_inventory(व्योम)
अणु
	पूर्णांक i;
	दीर्घ status = PDC_OK;
    
	क्रम (i = 0; i < 256; i++) अणु
		काष्ठा parisc_device *dev;
		काष्ठा pdc_प्रणाली_map_mod_info module_result;
		काष्ठा pdc_module_path module_path;

		status = pdc_प्रणाली_map_find_mods(&module_result,
				&module_path, i);
		अगर ((status == PDC_BAD_PROC) || (status == PDC_NE_MOD))
			अवरोध;
		अगर (status != PDC_OK)
			जारी;

		dev = alloc_pa_dev(module_result.mod_addr, &module_path.path);
		अगर (!dev)
			जारी;
		
		रेजिस्टर_parisc_device(dev);

		/* अगर available, get the additional addresses क्रम a module */
		अगर (!module_result.add_addrs)
			जारी;

		add_प्रणाली_map_addresses(dev, module_result.add_addrs, i);
	पूर्ण

	walk_central_bus();
	वापस;
पूर्ण

व्योम __init करो_memory_inventory(व्योम)
अणु
	चयन (pdc_type) अणु

	हाल PDC_TYPE_PAT:
		pat_memconfig();
		अवरोध;

	हाल PDC_TYPE_SYSTEM_MAP:
		sprockets_memconfig();
		अवरोध;

	हाल PDC_TYPE_SNAKE:
		pagezero_memconfig();
		वापस;

	शेष:
		panic("Unknown PDC type!\n");
	पूर्ण

	अगर (npmem_ranges == 0 || pmem_ranges[0].start_pfn != 0) अणु
		prपूर्णांकk(KERN_WARNING "Bad memory configuration returned!\n");
		prपूर्णांकk(KERN_WARNING "Some memory may not be used!\n");
		pagezero_memconfig();
	पूर्ण
पूर्ण

व्योम __init करो_device_inventory(व्योम)
अणु
	prपूर्णांकk(KERN_INFO "Searching for devices...\n");

	init_parisc_bus();

	चयन (pdc_type) अणु

	हाल PDC_TYPE_PAT:
		pat_inventory();
		अवरोध;

	हाल PDC_TYPE_SYSTEM_MAP:
		प्रणाली_map_inventory();
		अवरोध;

	हाल PDC_TYPE_SNAKE:
		snake_inventory();
		अवरोध;

	शेष:
		panic("Unknown PDC type!\n");
	पूर्ण
	prपूर्णांकk(KERN_INFO "Found devices:\n");
	prपूर्णांक_parisc_devices();

#अगर defined(CONFIG_64BIT) && defined(CONFIG_SMP)
	pa_serialize_tlb_flushes = machine_has_merced_bus();
	अगर (pa_serialize_tlb_flushes)
		pr_info("Merced bus found: Enable PxTLB serialization.\n");
#पूर्ण_अगर

#अगर defined(CONFIG_FW_CFG_SYSFS)
	अगर (running_on_qemu) अणु
		काष्ठा resource res[3] = अणु0,पूर्ण;
		अचिन्हित पूर्णांक base;

		base = ((अचिन्हित दीर्घ दीर्घ) PAGE0->pad0[2] << 32)
			| PAGE0->pad0[3]; /* SeaBIOS stored it here */

		res[0].name = "fw_cfg";
		res[0].start = base;
		res[0].end = base + 8 - 1;
		res[0].flags = IORESOURCE_MEM;

		res[1].name = "ctrl";
		res[1].start = 0;
		res[1].flags = IORESOURCE_REG;

		res[2].name = "data";
		res[2].start = 4;
		res[2].flags = IORESOURCE_REG;

		अगर (base) अणु
			pr_info("Found qemu fw_cfg interface at %#08x\n", base);
			platक्रमm_device_रेजिस्टर_simple("fw_cfg",
				PLATFORM_DEVID_NONE, res, 3);
		पूर्ण
	पूर्ण
#पूर्ण_अगर
पूर्ण
