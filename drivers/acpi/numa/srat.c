<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  acpi_numa.c - ACPI NUMA support
 *
 *  Copyright (C) 2002 Takayoshi Kochi <t-kochi@bq.jp.nec.com>
 */

#घोषणा pr_fmt(fmt) "ACPI: " fmt

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/acpi.h>
#समावेश <linux/memblock.h>
#समावेश <linux/numa.h>
#समावेश <linux/nodemask.h>
#समावेश <linux/topology.h>

अटल nodemask_t nodes_found_map = NODE_MASK_NONE;

/* maps to convert between proximity करोमुख्य and logical node ID */
अटल पूर्णांक pxm_to_node_map[MAX_PXM_DOMAINS]
			= अणु [0 ... MAX_PXM_DOMAINS - 1] = NUMA_NO_NODE पूर्ण;
अटल पूर्णांक node_to_pxm_map[MAX_NUMNODES]
			= अणु [0 ... MAX_NUMNODES - 1] = PXM_INVAL पूर्ण;

अचिन्हित अक्षर acpi_srat_revision __initdata;
अटल पूर्णांक acpi_numa __initdata;

व्योम __init disable_srat(व्योम)
अणु
	acpi_numa = -1;
पूर्ण

पूर्णांक pxm_to_node(पूर्णांक pxm)
अणु
	अगर (pxm < 0 || pxm >= MAX_PXM_DOMAINS || numa_off)
		वापस NUMA_NO_NODE;
	वापस pxm_to_node_map[pxm];
पूर्ण
EXPORT_SYMBOL(pxm_to_node);

पूर्णांक node_to_pxm(पूर्णांक node)
अणु
	अगर (node < 0)
		वापस PXM_INVAL;
	वापस node_to_pxm_map[node];
पूर्ण

अटल व्योम __acpi_map_pxm_to_node(पूर्णांक pxm, पूर्णांक node)
अणु
	अगर (pxm_to_node_map[pxm] == NUMA_NO_NODE || node < pxm_to_node_map[pxm])
		pxm_to_node_map[pxm] = node;
	अगर (node_to_pxm_map[node] == PXM_INVAL || pxm < node_to_pxm_map[node])
		node_to_pxm_map[node] = pxm;
पूर्ण

पूर्णांक acpi_map_pxm_to_node(पूर्णांक pxm)
अणु
	पूर्णांक node;

	अगर (pxm < 0 || pxm >= MAX_PXM_DOMAINS || numa_off)
		वापस NUMA_NO_NODE;

	node = pxm_to_node_map[pxm];

	अगर (node == NUMA_NO_NODE) अणु
		अगर (nodes_weight(nodes_found_map) >= MAX_NUMNODES)
			वापस NUMA_NO_NODE;
		node = first_unset_node(nodes_found_map);
		__acpi_map_pxm_to_node(pxm, node);
		node_set(node, nodes_found_map);
	पूर्ण

	वापस node;
पूर्ण
EXPORT_SYMBOL(acpi_map_pxm_to_node);

अटल व्योम __init
acpi_table_prपूर्णांक_srat_entry(काष्ठा acpi_subtable_header *header)
अणु
	चयन (header->type) अणु
	हाल ACPI_SRAT_TYPE_CPU_AFFINITY:
		अणु
			काष्ठा acpi_srat_cpu_affinity *p =
			    (काष्ठा acpi_srat_cpu_affinity *)header;
			pr_debug("SRAT Processor (id[0x%02x] eid[0x%02x]) in proximity domain %d %s\n",
				 p->apic_id, p->local_sapic_eid,
				 p->proximity_करोमुख्य_lo,
				 (p->flags & ACPI_SRAT_CPU_ENABLED) ?
				 "enabled" : "disabled");
		पूर्ण
		अवरोध;

	हाल ACPI_SRAT_TYPE_MEMORY_AFFINITY:
		अणु
			काष्ठा acpi_srat_mem_affinity *p =
			    (काष्ठा acpi_srat_mem_affinity *)header;
			pr_debug("SRAT Memory (0x%llx length 0x%llx) in proximity domain %d %s%s%s\n",
				 (अचिन्हित दीर्घ दीर्घ)p->base_address,
				 (अचिन्हित दीर्घ दीर्घ)p->length,
				 p->proximity_करोमुख्य,
				 (p->flags & ACPI_SRAT_MEM_ENABLED) ?
				 "enabled" : "disabled",
				 (p->flags & ACPI_SRAT_MEM_HOT_PLUGGABLE) ?
				 " hot-pluggable" : "",
				 (p->flags & ACPI_SRAT_MEM_NON_VOLATILE) ?
				 " non-volatile" : "");
		पूर्ण
		अवरोध;

	हाल ACPI_SRAT_TYPE_X2APIC_CPU_AFFINITY:
		अणु
			काष्ठा acpi_srat_x2apic_cpu_affinity *p =
			    (काष्ठा acpi_srat_x2apic_cpu_affinity *)header;
			pr_debug("SRAT Processor (x2apicid[0x%08x]) in proximity domain %d %s\n",
				 p->apic_id,
				 p->proximity_करोमुख्य,
				 (p->flags & ACPI_SRAT_CPU_ENABLED) ?
				 "enabled" : "disabled");
		पूर्ण
		अवरोध;

	हाल ACPI_SRAT_TYPE_GICC_AFFINITY:
		अणु
			काष्ठा acpi_srat_gicc_affinity *p =
			    (काष्ठा acpi_srat_gicc_affinity *)header;
			pr_debug("SRAT Processor (acpi id[0x%04x]) in proximity domain %d %s\n",
				 p->acpi_processor_uid,
				 p->proximity_करोमुख्य,
				 (p->flags & ACPI_SRAT_GICC_ENABLED) ?
				 "enabled" : "disabled");
		पूर्ण
		अवरोध;

	हाल ACPI_SRAT_TYPE_GENERIC_AFFINITY:
	अणु
		काष्ठा acpi_srat_generic_affinity *p =
			(काष्ठा acpi_srat_generic_affinity *)header;

		अगर (p->device_handle_type == 0) अणु
			/*
			 * For pci devices this may be the only place they
			 * are asचिन्हित a proximity करोमुख्य
			 */
			pr_debug("SRAT Generic Initiator(Seg:%u BDF:%u) in proximity domain %d %s\n",
				 *(u16 *)(&p->device_handle[0]),
				 *(u16 *)(&p->device_handle[2]),
				 p->proximity_करोमुख्य,
				 (p->flags & ACPI_SRAT_GENERIC_AFFINITY_ENABLED) ?
				"enabled" : "disabled");
		पूर्ण अन्यथा अणु
			/*
			 * In this हाल we can rely on the device having a
			 * proximity करोमुख्य reference
			 */
			pr_debug("SRAT Generic Initiator(HID=%.8s UID=%.4s) in proximity domain %d %s\n",
				(अक्षर *)(&p->device_handle[0]),
				(अक्षर *)(&p->device_handle[8]),
				p->proximity_करोमुख्य,
				(p->flags & ACPI_SRAT_GENERIC_AFFINITY_ENABLED) ?
				"enabled" : "disabled");
		पूर्ण
	पूर्ण
	अवरोध;
	शेष:
		pr_warn("Found unsupported SRAT entry (type = 0x%x)\n",
			header->type);
		अवरोध;
	पूर्ण
पूर्ण

/*
 * A lot of BIOS fill in 10 (= no distance) everywhere. This messes
 * up the NUMA heuristics which wants the local node to have a smaller
 * distance than the others.
 * Do some quick checks here and only use the SLIT अगर it passes.
 */
अटल पूर्णांक __init slit_valid(काष्ठा acpi_table_slit *slit)
अणु
	पूर्णांक i, j;
	पूर्णांक d = slit->locality_count;
	क्रम (i = 0; i < d; i++) अणु
		क्रम (j = 0; j < d; j++)  अणु
			u8 val = slit->entry[d*i + j];
			अगर (i == j) अणु
				अगर (val != LOCAL_DISTANCE)
					वापस 0;
			पूर्ण अन्यथा अगर (val <= LOCAL_DISTANCE)
				वापस 0;
		पूर्ण
	पूर्ण
	वापस 1;
पूर्ण

व्योम __init bad_srat(व्योम)
अणु
	pr_err("SRAT: SRAT not used.\n");
	disable_srat();
पूर्ण

पूर्णांक __init srat_disabled(व्योम)
अणु
	वापस acpi_numa < 0;
पूर्ण

#अगर defined(CONFIG_X86) || defined(CONFIG_ARM64)
/*
 * Callback क्रम SLIT parsing.  pxm_to_node() वापसs NUMA_NO_NODE क्रम
 * I/O localities since SRAT करोes not list them.  I/O localities are
 * not supported at this poपूर्णांक.
 */
व्योम __init acpi_numa_slit_init(काष्ठा acpi_table_slit *slit)
अणु
	पूर्णांक i, j;

	क्रम (i = 0; i < slit->locality_count; i++) अणु
		स्थिर पूर्णांक from_node = pxm_to_node(i);

		अगर (from_node == NUMA_NO_NODE)
			जारी;

		क्रम (j = 0; j < slit->locality_count; j++) अणु
			स्थिर पूर्णांक to_node = pxm_to_node(j);

			अगर (to_node == NUMA_NO_NODE)
				जारी;

			numa_set_distance(from_node, to_node,
				slit->entry[slit->locality_count * i + j]);
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Default callback क्रम parsing of the Proximity Doमुख्य <-> Memory
 * Area mappings
 */
पूर्णांक __init
acpi_numa_memory_affinity_init(काष्ठा acpi_srat_mem_affinity *ma)
अणु
	u64 start, end;
	u32 hotpluggable;
	पूर्णांक node, pxm;

	अगर (srat_disabled())
		जाओ out_err;
	अगर (ma->header.length < माप(काष्ठा acpi_srat_mem_affinity)) अणु
		pr_err("SRAT: Unexpected header length: %d\n",
		       ma->header.length);
		जाओ out_err_bad_srat;
	पूर्ण
	अगर ((ma->flags & ACPI_SRAT_MEM_ENABLED) == 0)
		जाओ out_err;
	hotpluggable = ma->flags & ACPI_SRAT_MEM_HOT_PLUGGABLE;
	अगर (hotpluggable && !IS_ENABLED(CONFIG_MEMORY_HOTPLUG))
		जाओ out_err;

	start = ma->base_address;
	end = start + ma->length;
	pxm = ma->proximity_करोमुख्य;
	अगर (acpi_srat_revision <= 1)
		pxm &= 0xff;

	node = acpi_map_pxm_to_node(pxm);
	अगर (node == NUMA_NO_NODE) अणु
		pr_err("SRAT: Too many proximity domains.\n");
		जाओ out_err_bad_srat;
	पूर्ण

	अगर (numa_add_memblk(node, start, end) < 0) अणु
		pr_err("SRAT: Failed to add memblk to node %u [mem %#010Lx-%#010Lx]\n",
		       node, (अचिन्हित दीर्घ दीर्घ) start,
		       (अचिन्हित दीर्घ दीर्घ) end - 1);
		जाओ out_err_bad_srat;
	पूर्ण

	node_set(node, numa_nodes_parsed);

	pr_info("SRAT: Node %u PXM %u [mem %#010Lx-%#010Lx]%s%s\n",
		node, pxm,
		(अचिन्हित दीर्घ दीर्घ) start, (अचिन्हित दीर्घ दीर्घ) end - 1,
		hotpluggable ? " hotplug" : "",
		ma->flags & ACPI_SRAT_MEM_NON_VOLATILE ? " non-volatile" : "");

	/* Mark hotplug range in memblock. */
	अगर (hotpluggable && memblock_mark_hotplug(start, ma->length))
		pr_warn("SRAT: Failed to mark hotplug range [mem %#010Lx-%#010Lx] in memblock\n",
			(अचिन्हित दीर्घ दीर्घ)start, (अचिन्हित दीर्घ दीर्घ)end - 1);

	max_possible_pfn = max(max_possible_pfn, PFN_UP(end - 1));

	वापस 0;
out_err_bad_srat:
	bad_srat();
out_err:
	वापस -EINVAL;
पूर्ण
#पूर्ण_अगर /* defined(CONFIG_X86) || defined (CONFIG_ARM64) */

अटल पूर्णांक __init acpi_parse_slit(काष्ठा acpi_table_header *table)
अणु
	काष्ठा acpi_table_slit *slit = (काष्ठा acpi_table_slit *)table;

	अगर (!slit_valid(slit)) अणु
		pr_info("SLIT table looks invalid. Not used.\n");
		वापस -EINVAL;
	पूर्ण
	acpi_numa_slit_init(slit);

	वापस 0;
पूर्ण

व्योम __init __weak
acpi_numa_x2apic_affinity_init(काष्ठा acpi_srat_x2apic_cpu_affinity *pa)
अणु
	pr_warn("Found unsupported x2apic [0x%08x] SRAT entry\n", pa->apic_id);
पूर्ण

अटल पूर्णांक __init
acpi_parse_x2apic_affinity(जोड़ acpi_subtable_headers *header,
			   स्थिर अचिन्हित दीर्घ end)
अणु
	काष्ठा acpi_srat_x2apic_cpu_affinity *processor_affinity;

	processor_affinity = (काष्ठा acpi_srat_x2apic_cpu_affinity *)header;

	acpi_table_prपूर्णांक_srat_entry(&header->common);

	/* let architecture-dependent part to करो it */
	acpi_numa_x2apic_affinity_init(processor_affinity);

	वापस 0;
पूर्ण

अटल पूर्णांक __init
acpi_parse_processor_affinity(जोड़ acpi_subtable_headers *header,
			      स्थिर अचिन्हित दीर्घ end)
अणु
	काष्ठा acpi_srat_cpu_affinity *processor_affinity;

	processor_affinity = (काष्ठा acpi_srat_cpu_affinity *)header;

	acpi_table_prपूर्णांक_srat_entry(&header->common);

	/* let architecture-dependent part to करो it */
	acpi_numa_processor_affinity_init(processor_affinity);

	वापस 0;
पूर्ण

अटल पूर्णांक __init
acpi_parse_gicc_affinity(जोड़ acpi_subtable_headers *header,
			 स्थिर अचिन्हित दीर्घ end)
अणु
	काष्ठा acpi_srat_gicc_affinity *processor_affinity;

	processor_affinity = (काष्ठा acpi_srat_gicc_affinity *)header;

	acpi_table_prपूर्णांक_srat_entry(&header->common);

	/* let architecture-dependent part to करो it */
	acpi_numa_gicc_affinity_init(processor_affinity);

	वापस 0;
पूर्ण

#अगर defined(CONFIG_X86) || defined(CONFIG_ARM64)
अटल पूर्णांक __init
acpi_parse_gi_affinity(जोड़ acpi_subtable_headers *header,
		       स्थिर अचिन्हित दीर्घ end)
अणु
	काष्ठा acpi_srat_generic_affinity *gi_affinity;
	पूर्णांक node;

	gi_affinity = (काष्ठा acpi_srat_generic_affinity *)header;
	अगर (!gi_affinity)
		वापस -EINVAL;
	acpi_table_prपूर्णांक_srat_entry(&header->common);

	अगर (!(gi_affinity->flags & ACPI_SRAT_GENERIC_AFFINITY_ENABLED))
		वापस -EINVAL;

	node = acpi_map_pxm_to_node(gi_affinity->proximity_करोमुख्य);
	अगर (node == NUMA_NO_NODE || node >= MAX_NUMNODES) अणु
		pr_err("SRAT: Too many proximity domains.\n");
		वापस -EINVAL;
	पूर्ण
	node_set(node, numa_nodes_parsed);
	node_set_state(node, N_GENERIC_INITIATOR);

	वापस 0;
पूर्ण
#अन्यथा
अटल पूर्णांक __init
acpi_parse_gi_affinity(जोड़ acpi_subtable_headers *header,
		       स्थिर अचिन्हित दीर्घ end)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर /* defined(CONFIG_X86) || defined (CONFIG_ARM64) */

अटल पूर्णांक __initdata parsed_numa_memblks;

अटल पूर्णांक __init
acpi_parse_memory_affinity(जोड़ acpi_subtable_headers * header,
			   स्थिर अचिन्हित दीर्घ end)
अणु
	काष्ठा acpi_srat_mem_affinity *memory_affinity;

	memory_affinity = (काष्ठा acpi_srat_mem_affinity *)header;

	acpi_table_prपूर्णांक_srat_entry(&header->common);

	/* let architecture-dependent part to करो it */
	अगर (!acpi_numa_memory_affinity_init(memory_affinity))
		parsed_numa_memblks++;
	वापस 0;
पूर्ण

अटल पूर्णांक __init acpi_parse_srat(काष्ठा acpi_table_header *table)
अणु
	काष्ठा acpi_table_srat *srat = (काष्ठा acpi_table_srat *)table;

	acpi_srat_revision = srat->header.revision;

	/* Real work करोne in acpi_table_parse_srat below. */

	वापस 0;
पूर्ण

अटल पूर्णांक __init
acpi_table_parse_srat(क्रमागत acpi_srat_type id,
		      acpi_tbl_entry_handler handler, अचिन्हित पूर्णांक max_entries)
अणु
	वापस acpi_table_parse_entries(ACPI_SIG_SRAT,
					    माप(काष्ठा acpi_table_srat), id,
					    handler, max_entries);
पूर्ण

पूर्णांक __init acpi_numa_init(व्योम)
अणु
	पूर्णांक cnt = 0;

	अगर (acpi_disabled)
		वापस -EINVAL;

	/*
	 * Should not limit number with cpu num that is from NR_CPUS or nr_cpus=
	 * SRAT cpu entries could have dअगरferent order with that in MADT.
	 * So go over all cpu entries in SRAT to get apicid to node mapping.
	 */

	/* SRAT: System Resource Affinity Table */
	अगर (!acpi_table_parse(ACPI_SIG_SRAT, acpi_parse_srat)) अणु
		काष्ठा acpi_subtable_proc srat_proc[4];

		स_रखो(srat_proc, 0, माप(srat_proc));
		srat_proc[0].id = ACPI_SRAT_TYPE_CPU_AFFINITY;
		srat_proc[0].handler = acpi_parse_processor_affinity;
		srat_proc[1].id = ACPI_SRAT_TYPE_X2APIC_CPU_AFFINITY;
		srat_proc[1].handler = acpi_parse_x2apic_affinity;
		srat_proc[2].id = ACPI_SRAT_TYPE_GICC_AFFINITY;
		srat_proc[2].handler = acpi_parse_gicc_affinity;
		srat_proc[3].id = ACPI_SRAT_TYPE_GENERIC_AFFINITY;
		srat_proc[3].handler = acpi_parse_gi_affinity;

		acpi_table_parse_entries_array(ACPI_SIG_SRAT,
					माप(काष्ठा acpi_table_srat),
					srat_proc, ARRAY_SIZE(srat_proc), 0);

		cnt = acpi_table_parse_srat(ACPI_SRAT_TYPE_MEMORY_AFFINITY,
					    acpi_parse_memory_affinity, 0);
	पूर्ण

	/* SLIT: System Locality Inक्रमmation Table */
	acpi_table_parse(ACPI_SIG_SLIT, acpi_parse_slit);

	अगर (cnt < 0)
		वापस cnt;
	अन्यथा अगर (!parsed_numa_memblks)
		वापस -ENOENT;
	वापस 0;
पूर्ण

अटल पूर्णांक acpi_get_pxm(acpi_handle h)
अणु
	अचिन्हित दीर्घ दीर्घ pxm;
	acpi_status status;
	acpi_handle handle;
	acpi_handle phandle = h;

	करो अणु
		handle = phandle;
		status = acpi_evaluate_पूर्णांकeger(handle, "_PXM", शून्य, &pxm);
		अगर (ACPI_SUCCESS(status))
			वापस pxm;
		status = acpi_get_parent(handle, &phandle);
	पूर्ण जबतक (ACPI_SUCCESS(status));
	वापस -1;
पूर्ण

पूर्णांक acpi_get_node(acpi_handle handle)
अणु
	पूर्णांक pxm;

	pxm = acpi_get_pxm(handle);

	वापस pxm_to_node(pxm);
पूर्ण
EXPORT_SYMBOL(acpi_get_node);
