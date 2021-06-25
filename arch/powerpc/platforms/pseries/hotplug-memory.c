<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * pseries Memory Hotplug infraकाष्ठाure.
 *
 * Copyright (C) 2008 Badari Pulavarty, IBM Corporation
 */

#घोषणा pr_fmt(fmt)	"pseries-hotplug-mem: " fmt

#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/memblock.h>
#समावेश <linux/memory.h>
#समावेश <linux/memory_hotplug.h>
#समावेश <linux/slab.h>

#समावेश <यंत्र/firmware.h>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/sparseस्मृति.स>
#समावेश <यंत्र/fadump.h>
#समावेश <यंत्र/drस्मृति.स>
#समावेश "pseries.h"

अचिन्हित दीर्घ pseries_memory_block_size(व्योम)
अणु
	काष्ठा device_node *np;
	u64 memblock_size = MIN_MEMORY_BLOCK_SIZE;
	काष्ठा resource r;

	np = of_find_node_by_path("/ibm,dynamic-reconfiguration-memory");
	अगर (np) अणु
		पूर्णांक len;
		पूर्णांक size_cells;
		स्थिर __be32 *prop;

		size_cells = of_n_size_cells(np);

		prop = of_get_property(np, "ibm,lmb-size", &len);
		अगर (prop && len >= size_cells * माप(__be32))
			memblock_size = of_पढ़ो_number(prop, size_cells);
		of_node_put(np);

	पूर्ण अन्यथा  अगर (machine_is(pseries)) अणु
		/* This fallback really only applies to pseries */
		अचिन्हित पूर्णांक memzero_size = 0;

		np = of_find_node_by_path("/memory@0");
		अगर (np) अणु
			अगर (!of_address_to_resource(np, 0, &r))
				memzero_size = resource_size(&r);
			of_node_put(np);
		पूर्ण

		अगर (memzero_size) अणु
			/* We now know the size of memory@0, use this to find
			 * the first memoryblock and get its size.
			 */
			अक्षर buf[64];

			प्र_लिखो(buf, "/memory@%x", memzero_size);
			np = of_find_node_by_path(buf);
			अगर (np) अणु
				अगर (!of_address_to_resource(np, 0, &r))
					memblock_size = resource_size(&r);
				of_node_put(np);
			पूर्ण
		पूर्ण
	पूर्ण
	वापस memblock_size;
पूर्ण

अटल व्योम dlpar_मुक्त_property(काष्ठा property *prop)
अणु
	kमुक्त(prop->name);
	kमुक्त(prop->value);
	kमुक्त(prop);
पूर्ण

अटल काष्ठा property *dlpar_clone_property(काष्ठा property *prop,
					     u32 prop_size)
अणु
	काष्ठा property *new_prop;

	new_prop = kzalloc(माप(*new_prop), GFP_KERNEL);
	अगर (!new_prop)
		वापस शून्य;

	new_prop->name = kstrdup(prop->name, GFP_KERNEL);
	new_prop->value = kzalloc(prop_size, GFP_KERNEL);
	अगर (!new_prop->name || !new_prop->value) अणु
		dlpar_मुक्त_property(new_prop);
		वापस शून्य;
	पूर्ण

	स_नकल(new_prop->value, prop->value, prop->length);
	new_prop->length = prop_size;

	of_property_set_flag(new_prop, OF_DYNAMIC);
	वापस new_prop;
पूर्ण

अटल bool find_aa_index(काष्ठा device_node *dr_node,
			 काष्ठा property *ala_prop,
			 स्थिर u32 *lmb_assoc, u32 *aa_index)
अणु
	u32 *assoc_arrays, new_prop_size;
	काष्ठा property *new_prop;
	पूर्णांक aa_arrays, aa_array_entries, aa_array_sz;
	पूर्णांक i, index;

	/*
	 * The ibm,associativity-lookup-arrays property is defined to be
	 * a 32-bit value specअगरying the number of associativity arrays
	 * followed by a 32-bitvalue specअगरying the number of entries per
	 * array, followed by the associativity arrays.
	 */
	assoc_arrays = ala_prop->value;

	aa_arrays = be32_to_cpu(assoc_arrays[0]);
	aa_array_entries = be32_to_cpu(assoc_arrays[1]);
	aa_array_sz = aa_array_entries * माप(u32);

	क्रम (i = 0; i < aa_arrays; i++) अणु
		index = (i * aa_array_entries) + 2;

		अगर (स_भेद(&assoc_arrays[index], &lmb_assoc[1], aa_array_sz))
			जारी;

		*aa_index = i;
		वापस true;
	पूर्ण

	new_prop_size = ala_prop->length + aa_array_sz;
	new_prop = dlpar_clone_property(ala_prop, new_prop_size);
	अगर (!new_prop)
		वापस false;

	assoc_arrays = new_prop->value;

	/* increment the number of entries in the lookup array */
	assoc_arrays[0] = cpu_to_be32(aa_arrays + 1);

	/* copy the new associativity पूर्णांकo the lookup array */
	index = aa_arrays * aa_array_entries + 2;
	स_नकल(&assoc_arrays[index], &lmb_assoc[1], aa_array_sz);

	of_update_property(dr_node, new_prop);

	/*
	 * The associativity lookup array index क्रम this lmb is
	 * number of entries - 1 since we added its associativity
	 * to the end of the lookup array.
	 */
	*aa_index = be32_to_cpu(assoc_arrays[0]) - 1;
	वापस true;
पूर्ण

अटल पूर्णांक update_lmb_associativity_index(काष्ठा drmem_lmb *lmb)
अणु
	काष्ठा device_node *parent, *lmb_node, *dr_node;
	काष्ठा property *ala_prop;
	स्थिर u32 *lmb_assoc;
	u32 aa_index;
	bool found;

	parent = of_find_node_by_path("/");
	अगर (!parent)
		वापस -ENODEV;

	lmb_node = dlpar_configure_connector(cpu_to_be32(lmb->drc_index),
					     parent);
	of_node_put(parent);
	अगर (!lmb_node)
		वापस -EINVAL;

	lmb_assoc = of_get_property(lmb_node, "ibm,associativity", शून्य);
	अगर (!lmb_assoc) अणु
		dlpar_मुक्त_cc_nodes(lmb_node);
		वापस -ENODEV;
	पूर्ण

	dr_node = of_find_node_by_path("/ibm,dynamic-reconfiguration-memory");
	अगर (!dr_node) अणु
		dlpar_मुक्त_cc_nodes(lmb_node);
		वापस -ENODEV;
	पूर्ण

	ala_prop = of_find_property(dr_node, "ibm,associativity-lookup-arrays",
				    शून्य);
	अगर (!ala_prop) अणु
		of_node_put(dr_node);
		dlpar_मुक्त_cc_nodes(lmb_node);
		वापस -ENODEV;
	पूर्ण

	found = find_aa_index(dr_node, ala_prop, lmb_assoc, &aa_index);

	of_node_put(dr_node);
	dlpar_मुक्त_cc_nodes(lmb_node);

	अगर (!found) अणु
		pr_err("Could not find LMB associativity\n");
		वापस -1;
	पूर्ण

	lmb->aa_index = aa_index;
	वापस 0;
पूर्ण

अटल काष्ठा memory_block *lmb_to_memblock(काष्ठा drmem_lmb *lmb)
अणु
	अचिन्हित दीर्घ section_nr;
	काष्ठा mem_section *mem_sect;
	काष्ठा memory_block *mem_block;

	section_nr = pfn_to_section_nr(PFN_DOWN(lmb->base_addr));
	mem_sect = __nr_to_section(section_nr);

	mem_block = find_memory_block(mem_sect);
	वापस mem_block;
पूर्ण

अटल पूर्णांक get_lmb_range(u32 drc_index, पूर्णांक n_lmbs,
			 काष्ठा drmem_lmb **start_lmb,
			 काष्ठा drmem_lmb **end_lmb)
अणु
	काष्ठा drmem_lmb *lmb, *start, *end;
	काष्ठा drmem_lmb *limit;

	start = शून्य;
	क्रम_each_drmem_lmb(lmb) अणु
		अगर (lmb->drc_index == drc_index) अणु
			start = lmb;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!start)
		वापस -EINVAL;

	end = &start[n_lmbs];

	limit = &drmem_info->lmbs[drmem_info->n_lmbs];
	अगर (end > limit)
		वापस -EINVAL;

	*start_lmb = start;
	*end_lmb = end;
	वापस 0;
पूर्ण

अटल पूर्णांक dlpar_change_lmb_state(काष्ठा drmem_lmb *lmb, bool online)
अणु
	काष्ठा memory_block *mem_block;
	पूर्णांक rc;

	mem_block = lmb_to_memblock(lmb);
	अगर (!mem_block)
		वापस -EINVAL;

	अगर (online && mem_block->dev.offline)
		rc = device_online(&mem_block->dev);
	अन्यथा अगर (!online && !mem_block->dev.offline)
		rc = device_offline(&mem_block->dev);
	अन्यथा
		rc = 0;

	put_device(&mem_block->dev);

	वापस rc;
पूर्ण

अटल पूर्णांक dlpar_online_lmb(काष्ठा drmem_lmb *lmb)
अणु
	वापस dlpar_change_lmb_state(lmb, true);
पूर्ण

#अगर_घोषित CONFIG_MEMORY_HOTREMOVE
अटल पूर्णांक dlpar_offline_lmb(काष्ठा drmem_lmb *lmb)
अणु
	वापस dlpar_change_lmb_state(lmb, false);
पूर्ण

अटल पूर्णांक pseries_हटाओ_memblock(अचिन्हित दीर्घ base, अचिन्हित दीर्घ memblock_size)
अणु
	अचिन्हित दीर्घ block_sz, start_pfn;
	पूर्णांक sections_per_block;
	पूर्णांक i, nid;

	start_pfn = base >> PAGE_SHIFT;

	lock_device_hotplug();

	अगर (!pfn_valid(start_pfn))
		जाओ out;

	block_sz = pseries_memory_block_size();
	sections_per_block = block_sz / MIN_MEMORY_BLOCK_SIZE;
	nid = memory_add_physaddr_to_nid(base);

	क्रम (i = 0; i < sections_per_block; i++) अणु
		__हटाओ_memory(nid, base, MIN_MEMORY_BLOCK_SIZE);
		base += MIN_MEMORY_BLOCK_SIZE;
	पूर्ण

out:
	/* Update memory regions क्रम memory हटाओ */
	memblock_हटाओ(base, memblock_size);
	unlock_device_hotplug();
	वापस 0;
पूर्ण

अटल पूर्णांक pseries_हटाओ_mem_node(काष्ठा device_node *np)
अणु
	स्थिर __be32 *prop;
	अचिन्हित दीर्घ base;
	अचिन्हित दीर्घ lmb_size;
	पूर्णांक ret = -EINVAL;
	पूर्णांक addr_cells, size_cells;

	/*
	 * Check to see अगर we are actually removing memory
	 */
	अगर (!of_node_is_type(np, "memory"))
		वापस 0;

	/*
	 * Find the base address and size of the memblock
	 */
	prop = of_get_property(np, "reg", शून्य);
	अगर (!prop)
		वापस ret;

	addr_cells = of_n_addr_cells(np);
	size_cells = of_n_size_cells(np);

	/*
	 * "reg" property represents (addr,size) tuple.
	 */
	base = of_पढ़ो_number(prop, addr_cells);
	prop += addr_cells;
	lmb_size = of_पढ़ो_number(prop, size_cells);

	pseries_हटाओ_memblock(base, lmb_size);
	वापस 0;
पूर्ण

अटल bool lmb_is_removable(काष्ठा drmem_lmb *lmb)
अणु
	अगर (!(lmb->flags & DRCONF_MEM_ASSIGNED))
		वापस false;

#अगर_घोषित CONFIG_FA_DUMP
	/*
	 * Don't hot-हटाओ memory that falls in fadump boot memory area
	 * and memory that is reserved क्रम capturing old kernel memory.
	 */
	अगर (is_fadump_memory_area(lmb->base_addr, memory_block_size_bytes()))
		वापस false;
#पूर्ण_अगर
	/* device_offline() will determine अगर we can actually हटाओ this lmb */
	वापस true;
पूर्ण

अटल पूर्णांक dlpar_add_lmb(काष्ठा drmem_lmb *);

अटल पूर्णांक dlpar_हटाओ_lmb(काष्ठा drmem_lmb *lmb)
अणु
	काष्ठा memory_block *mem_block;
	अचिन्हित दीर्घ block_sz;
	पूर्णांक rc;

	अगर (!lmb_is_removable(lmb))
		वापस -EINVAL;

	mem_block = lmb_to_memblock(lmb);
	अगर (mem_block == शून्य)
		वापस -EINVAL;

	rc = dlpar_offline_lmb(lmb);
	अगर (rc) अणु
		put_device(&mem_block->dev);
		वापस rc;
	पूर्ण

	block_sz = pseries_memory_block_size();

	__हटाओ_memory(mem_block->nid, lmb->base_addr, block_sz);
	put_device(&mem_block->dev);

	/* Update memory regions क्रम memory हटाओ */
	memblock_हटाओ(lmb->base_addr, block_sz);

	invalidate_lmb_associativity_index(lmb);
	lmb->flags &= ~DRCONF_MEM_ASSIGNED;

	वापस 0;
पूर्ण

अटल पूर्णांक dlpar_memory_हटाओ_by_count(u32 lmbs_to_हटाओ)
अणु
	काष्ठा drmem_lmb *lmb;
	पूर्णांक lmbs_हटाओd = 0;
	पूर्णांक lmbs_available = 0;
	पूर्णांक rc;

	pr_info("Attempting to hot-remove %d LMB(s)\n", lmbs_to_हटाओ);

	अगर (lmbs_to_हटाओ == 0)
		वापस -EINVAL;

	/* Validate that there are enough LMBs to satisfy the request */
	क्रम_each_drmem_lmb(lmb) अणु
		अगर (lmb_is_removable(lmb))
			lmbs_available++;

		अगर (lmbs_available == lmbs_to_हटाओ)
			अवरोध;
	पूर्ण

	अगर (lmbs_available < lmbs_to_हटाओ) अणु
		pr_info("Not enough LMBs available (%d of %d) to satisfy request\n",
			lmbs_available, lmbs_to_हटाओ);
		वापस -EINVAL;
	पूर्ण

	क्रम_each_drmem_lmb(lmb) अणु
		rc = dlpar_हटाओ_lmb(lmb);
		अगर (rc)
			जारी;

		/* Mark this lmb so we can add it later अगर all of the
		 * requested LMBs cannot be हटाओd.
		 */
		drmem_mark_lmb_reserved(lmb);

		lmbs_हटाओd++;
		अगर (lmbs_हटाओd == lmbs_to_हटाओ)
			अवरोध;
	पूर्ण

	अगर (lmbs_हटाओd != lmbs_to_हटाओ) अणु
		pr_err("Memory hot-remove failed, adding LMB's back\n");

		क्रम_each_drmem_lmb(lmb) अणु
			अगर (!drmem_lmb_reserved(lmb))
				जारी;

			rc = dlpar_add_lmb(lmb);
			अगर (rc)
				pr_err("Failed to add LMB back, drc index %x\n",
				       lmb->drc_index);

			drmem_हटाओ_lmb_reservation(lmb);
		पूर्ण

		rc = -EINVAL;
	पूर्ण अन्यथा अणु
		क्रम_each_drmem_lmb(lmb) अणु
			अगर (!drmem_lmb_reserved(lmb))
				जारी;

			dlpar_release_drc(lmb->drc_index);
			pr_info("Memory at %llx was hot-removed\n",
				lmb->base_addr);

			drmem_हटाओ_lmb_reservation(lmb);
		पूर्ण
		rc = 0;
	पूर्ण

	वापस rc;
पूर्ण

अटल पूर्णांक dlpar_memory_हटाओ_by_index(u32 drc_index)
अणु
	काष्ठा drmem_lmb *lmb;
	पूर्णांक lmb_found;
	पूर्णांक rc;

	pr_debug("Attempting to hot-remove LMB, drc index %x\n", drc_index);

	lmb_found = 0;
	क्रम_each_drmem_lmb(lmb) अणु
		अगर (lmb->drc_index == drc_index) अणु
			lmb_found = 1;
			rc = dlpar_हटाओ_lmb(lmb);
			अगर (!rc)
				dlpar_release_drc(lmb->drc_index);

			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!lmb_found)
		rc = -EINVAL;

	अगर (rc)
		pr_debug("Failed to hot-remove memory at %llx\n",
			 lmb->base_addr);
	अन्यथा
		pr_debug("Memory at %llx was hot-removed\n", lmb->base_addr);

	वापस rc;
पूर्ण

अटल पूर्णांक dlpar_memory_हटाओ_by_ic(u32 lmbs_to_हटाओ, u32 drc_index)
अणु
	काष्ठा drmem_lmb *lmb, *start_lmb, *end_lmb;
	पूर्णांक lmbs_available = 0;
	पूर्णांक rc;

	pr_info("Attempting to hot-remove %u LMB(s) at %x\n",
		lmbs_to_हटाओ, drc_index);

	अगर (lmbs_to_हटाओ == 0)
		वापस -EINVAL;

	rc = get_lmb_range(drc_index, lmbs_to_हटाओ, &start_lmb, &end_lmb);
	अगर (rc)
		वापस -EINVAL;

	/* Validate that there are enough LMBs to satisfy the request */
	क्रम_each_drmem_lmb_in_range(lmb, start_lmb, end_lmb) अणु
		अगर (lmb->flags & DRCONF_MEM_RESERVED)
			अवरोध;

		lmbs_available++;
	पूर्ण

	अगर (lmbs_available < lmbs_to_हटाओ)
		वापस -EINVAL;

	क्रम_each_drmem_lmb_in_range(lmb, start_lmb, end_lmb) अणु
		अगर (!(lmb->flags & DRCONF_MEM_ASSIGNED))
			जारी;

		rc = dlpar_हटाओ_lmb(lmb);
		अगर (rc)
			अवरोध;

		drmem_mark_lmb_reserved(lmb);
	पूर्ण

	अगर (rc) अणु
		pr_err("Memory indexed-count-remove failed, adding any removed LMBs\n");


		क्रम_each_drmem_lmb_in_range(lmb, start_lmb, end_lmb) अणु
			अगर (!drmem_lmb_reserved(lmb))
				जारी;

			rc = dlpar_add_lmb(lmb);
			अगर (rc)
				pr_err("Failed to add LMB, drc index %x\n",
				       lmb->drc_index);

			drmem_हटाओ_lmb_reservation(lmb);
		पूर्ण
		rc = -EINVAL;
	पूर्ण अन्यथा अणु
		क्रम_each_drmem_lmb_in_range(lmb, start_lmb, end_lmb) अणु
			अगर (!drmem_lmb_reserved(lmb))
				जारी;

			dlpar_release_drc(lmb->drc_index);
			pr_info("Memory at %llx (drc index %x) was hot-removed\n",
				lmb->base_addr, lmb->drc_index);

			drmem_हटाओ_lmb_reservation(lmb);
		पूर्ण
	पूर्ण

	वापस rc;
पूर्ण

#अन्यथा
अटल अंतरभूत पूर्णांक pseries_हटाओ_memblock(अचिन्हित दीर्घ base,
					  अचिन्हित दीर्घ memblock_size)
अणु
	वापस -EOPNOTSUPP;
पूर्ण
अटल अंतरभूत पूर्णांक pseries_हटाओ_mem_node(काष्ठा device_node *np)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत पूर्णांक dlpar_memory_हटाओ(काष्ठा pseries_hp_errorlog *hp_elog)
अणु
	वापस -EOPNOTSUPP;
पूर्ण
अटल पूर्णांक dlpar_हटाओ_lmb(काष्ठा drmem_lmb *lmb)
अणु
	वापस -EOPNOTSUPP;
पूर्ण
अटल पूर्णांक dlpar_memory_हटाओ_by_count(u32 lmbs_to_हटाओ)
अणु
	वापस -EOPNOTSUPP;
पूर्ण
अटल पूर्णांक dlpar_memory_हटाओ_by_index(u32 drc_index)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल पूर्णांक dlpar_memory_हटाओ_by_ic(u32 lmbs_to_हटाओ, u32 drc_index)
अणु
	वापस -EOPNOTSUPP;
पूर्ण
#पूर्ण_अगर /* CONFIG_MEMORY_HOTREMOVE */

अटल पूर्णांक dlpar_add_lmb(काष्ठा drmem_lmb *lmb)
अणु
	अचिन्हित दीर्घ block_sz;
	पूर्णांक nid, rc;

	अगर (lmb->flags & DRCONF_MEM_ASSIGNED)
		वापस -EINVAL;

	rc = update_lmb_associativity_index(lmb);
	अगर (rc) अणु
		dlpar_release_drc(lmb->drc_index);
		वापस rc;
	पूर्ण

	block_sz = memory_block_size_bytes();

	/* Find the node id क्रम this LMB.  Fake one अगर necessary. */
	nid = of_drconf_to_nid_single(lmb);
	अगर (nid < 0 || !node_possible(nid))
		nid = first_online_node;

	/* Add the memory */
	rc = __add_memory(nid, lmb->base_addr, block_sz, MHP_NONE);
	अगर (rc) अणु
		invalidate_lmb_associativity_index(lmb);
		वापस rc;
	पूर्ण

	rc = dlpar_online_lmb(lmb);
	अगर (rc) अणु
		__हटाओ_memory(nid, lmb->base_addr, block_sz);
		invalidate_lmb_associativity_index(lmb);
	पूर्ण अन्यथा अणु
		lmb->flags |= DRCONF_MEM_ASSIGNED;
	पूर्ण

	वापस rc;
पूर्ण

अटल पूर्णांक dlpar_memory_add_by_count(u32 lmbs_to_add)
अणु
	काष्ठा drmem_lmb *lmb;
	पूर्णांक lmbs_available = 0;
	पूर्णांक lmbs_added = 0;
	पूर्णांक rc;

	pr_info("Attempting to hot-add %d LMB(s)\n", lmbs_to_add);

	अगर (lmbs_to_add == 0)
		वापस -EINVAL;

	/* Validate that there are enough LMBs to satisfy the request */
	क्रम_each_drmem_lmb(lmb) अणु
		अगर (!(lmb->flags & DRCONF_MEM_ASSIGNED))
			lmbs_available++;

		अगर (lmbs_available == lmbs_to_add)
			अवरोध;
	पूर्ण

	अगर (lmbs_available < lmbs_to_add)
		वापस -EINVAL;

	क्रम_each_drmem_lmb(lmb) अणु
		अगर (lmb->flags & DRCONF_MEM_ASSIGNED)
			जारी;

		rc = dlpar_acquire_drc(lmb->drc_index);
		अगर (rc)
			जारी;

		rc = dlpar_add_lmb(lmb);
		अगर (rc) अणु
			dlpar_release_drc(lmb->drc_index);
			जारी;
		पूर्ण

		/* Mark this lmb so we can हटाओ it later अगर all of the
		 * requested LMBs cannot be added.
		 */
		drmem_mark_lmb_reserved(lmb);

		lmbs_added++;
		अगर (lmbs_added == lmbs_to_add)
			अवरोध;
	पूर्ण

	अगर (lmbs_added != lmbs_to_add) अणु
		pr_err("Memory hot-add failed, removing any added LMBs\n");

		क्रम_each_drmem_lmb(lmb) अणु
			अगर (!drmem_lmb_reserved(lmb))
				जारी;

			rc = dlpar_हटाओ_lmb(lmb);
			अगर (rc)
				pr_err("Failed to remove LMB, drc index %x\n",
				       lmb->drc_index);
			अन्यथा
				dlpar_release_drc(lmb->drc_index);

			drmem_हटाओ_lmb_reservation(lmb);
		पूर्ण
		rc = -EINVAL;
	पूर्ण अन्यथा अणु
		क्रम_each_drmem_lmb(lmb) अणु
			अगर (!drmem_lmb_reserved(lmb))
				जारी;

			pr_debug("Memory at %llx (drc index %x) was hot-added\n",
				 lmb->base_addr, lmb->drc_index);
			drmem_हटाओ_lmb_reservation(lmb);
		पूर्ण
		rc = 0;
	पूर्ण

	वापस rc;
पूर्ण

अटल पूर्णांक dlpar_memory_add_by_index(u32 drc_index)
अणु
	काष्ठा drmem_lmb *lmb;
	पूर्णांक rc, lmb_found;

	pr_info("Attempting to hot-add LMB, drc index %x\n", drc_index);

	lmb_found = 0;
	क्रम_each_drmem_lmb(lmb) अणु
		अगर (lmb->drc_index == drc_index) अणु
			lmb_found = 1;
			rc = dlpar_acquire_drc(lmb->drc_index);
			अगर (!rc) अणु
				rc = dlpar_add_lmb(lmb);
				अगर (rc)
					dlpar_release_drc(lmb->drc_index);
			पूर्ण

			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!lmb_found)
		rc = -EINVAL;

	अगर (rc)
		pr_info("Failed to hot-add memory, drc index %x\n", drc_index);
	अन्यथा
		pr_info("Memory at %llx (drc index %x) was hot-added\n",
			lmb->base_addr, drc_index);

	वापस rc;
पूर्ण

अटल पूर्णांक dlpar_memory_add_by_ic(u32 lmbs_to_add, u32 drc_index)
अणु
	काष्ठा drmem_lmb *lmb, *start_lmb, *end_lmb;
	पूर्णांक lmbs_available = 0;
	पूर्णांक rc;

	pr_info("Attempting to hot-add %u LMB(s) at index %x\n",
		lmbs_to_add, drc_index);

	अगर (lmbs_to_add == 0)
		वापस -EINVAL;

	rc = get_lmb_range(drc_index, lmbs_to_add, &start_lmb, &end_lmb);
	अगर (rc)
		वापस -EINVAL;

	/* Validate that the LMBs in this range are not reserved */
	क्रम_each_drmem_lmb_in_range(lmb, start_lmb, end_lmb) अणु
		अगर (lmb->flags & DRCONF_MEM_RESERVED)
			अवरोध;

		lmbs_available++;
	पूर्ण

	अगर (lmbs_available < lmbs_to_add)
		वापस -EINVAL;

	क्रम_each_drmem_lmb_in_range(lmb, start_lmb, end_lmb) अणु
		अगर (lmb->flags & DRCONF_MEM_ASSIGNED)
			जारी;

		rc = dlpar_acquire_drc(lmb->drc_index);
		अगर (rc)
			अवरोध;

		rc = dlpar_add_lmb(lmb);
		अगर (rc) अणु
			dlpar_release_drc(lmb->drc_index);
			अवरोध;
		पूर्ण

		drmem_mark_lmb_reserved(lmb);
	पूर्ण

	अगर (rc) अणु
		pr_err("Memory indexed-count-add failed, removing any added LMBs\n");

		क्रम_each_drmem_lmb_in_range(lmb, start_lmb, end_lmb) अणु
			अगर (!drmem_lmb_reserved(lmb))
				जारी;

			rc = dlpar_हटाओ_lmb(lmb);
			अगर (rc)
				pr_err("Failed to remove LMB, drc index %x\n",
				       lmb->drc_index);
			अन्यथा
				dlpar_release_drc(lmb->drc_index);

			drmem_हटाओ_lmb_reservation(lmb);
		पूर्ण
		rc = -EINVAL;
	पूर्ण अन्यथा अणु
		क्रम_each_drmem_lmb_in_range(lmb, start_lmb, end_lmb) अणु
			अगर (!drmem_lmb_reserved(lmb))
				जारी;

			pr_info("Memory at %llx (drc index %x) was hot-added\n",
				lmb->base_addr, lmb->drc_index);
			drmem_हटाओ_lmb_reservation(lmb);
		पूर्ण
	पूर्ण

	वापस rc;
पूर्ण

पूर्णांक dlpar_memory(काष्ठा pseries_hp_errorlog *hp_elog)
अणु
	u32 count, drc_index;
	पूर्णांक rc;

	lock_device_hotplug();

	चयन (hp_elog->action) अणु
	हाल PSERIES_HP_ELOG_ACTION_ADD:
		चयन (hp_elog->id_type) अणु
		हाल PSERIES_HP_ELOG_ID_DRC_COUNT:
			count = hp_elog->_drc_u.drc_count;
			rc = dlpar_memory_add_by_count(count);
			अवरोध;
		हाल PSERIES_HP_ELOG_ID_DRC_INDEX:
			drc_index = hp_elog->_drc_u.drc_index;
			rc = dlpar_memory_add_by_index(drc_index);
			अवरोध;
		हाल PSERIES_HP_ELOG_ID_DRC_IC:
			count = hp_elog->_drc_u.ic.count;
			drc_index = hp_elog->_drc_u.ic.index;
			rc = dlpar_memory_add_by_ic(count, drc_index);
			अवरोध;
		शेष:
			rc = -EINVAL;
			अवरोध;
		पूर्ण

		अवरोध;
	हाल PSERIES_HP_ELOG_ACTION_REMOVE:
		चयन (hp_elog->id_type) अणु
		हाल PSERIES_HP_ELOG_ID_DRC_COUNT:
			count = hp_elog->_drc_u.drc_count;
			rc = dlpar_memory_हटाओ_by_count(count);
			अवरोध;
		हाल PSERIES_HP_ELOG_ID_DRC_INDEX:
			drc_index = hp_elog->_drc_u.drc_index;
			rc = dlpar_memory_हटाओ_by_index(drc_index);
			अवरोध;
		हाल PSERIES_HP_ELOG_ID_DRC_IC:
			count = hp_elog->_drc_u.ic.count;
			drc_index = hp_elog->_drc_u.ic.index;
			rc = dlpar_memory_हटाओ_by_ic(count, drc_index);
			अवरोध;
		शेष:
			rc = -EINVAL;
			अवरोध;
		पूर्ण

		अवरोध;
	शेष:
		pr_err("Invalid action (%d) specified\n", hp_elog->action);
		rc = -EINVAL;
		अवरोध;
	पूर्ण

	अगर (!rc)
		rc = drmem_update_dt();

	unlock_device_hotplug();
	वापस rc;
पूर्ण

अटल पूर्णांक pseries_add_mem_node(काष्ठा device_node *np)
अणु
	स्थिर __be32 *prop;
	अचिन्हित दीर्घ base;
	अचिन्हित दीर्घ lmb_size;
	पूर्णांक ret = -EINVAL;
	पूर्णांक addr_cells, size_cells;

	/*
	 * Check to see अगर we are actually adding memory
	 */
	अगर (!of_node_is_type(np, "memory"))
		वापस 0;

	/*
	 * Find the base and size of the memblock
	 */
	prop = of_get_property(np, "reg", शून्य);
	अगर (!prop)
		वापस ret;

	addr_cells = of_n_addr_cells(np);
	size_cells = of_n_size_cells(np);
	/*
	 * "reg" property represents (addr,size) tuple.
	 */
	base = of_पढ़ो_number(prop, addr_cells);
	prop += addr_cells;
	lmb_size = of_पढ़ो_number(prop, size_cells);

	/*
	 * Update memory region to represent the memory add
	 */
	ret = memblock_add(base, lmb_size);
	वापस (ret < 0) ? -EINVAL : 0;
पूर्ण

अटल पूर्णांक pseries_memory_notअगरier(काष्ठा notअगरier_block *nb,
				   अचिन्हित दीर्घ action, व्योम *data)
अणु
	काष्ठा of_reconfig_data *rd = data;
	पूर्णांक err = 0;

	चयन (action) अणु
	हाल OF_RECONFIG_ATTACH_NODE:
		err = pseries_add_mem_node(rd->dn);
		अवरोध;
	हाल OF_RECONFIG_DETACH_NODE:
		err = pseries_हटाओ_mem_node(rd->dn);
		अवरोध;
	पूर्ण
	वापस notअगरier_from_त्रुटि_सं(err);
पूर्ण

अटल काष्ठा notअगरier_block pseries_mem_nb = अणु
	.notअगरier_call = pseries_memory_notअगरier,
पूर्ण;

अटल पूर्णांक __init pseries_memory_hotplug_init(व्योम)
अणु
	अगर (firmware_has_feature(FW_FEATURE_LPAR))
		of_reconfig_notअगरier_रेजिस्टर(&pseries_mem_nb);

	वापस 0;
पूर्ण
machine_device_initcall(pseries, pseries_memory_hotplug_init);
