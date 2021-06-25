<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2019, Intel Corporation.
 *
 * Heterogeneous Memory Attributes Table (HMAT) representation
 *
 * This program parses and reports the platक्रमm's HMAT tables, and रेजिस्टरs
 * the applicable attributes with the node's पूर्णांकerfaces.
 */

#घोषणा pr_fmt(fmt) "acpi/hmat: " fmt
#घोषणा dev_fmt(fmt) "acpi/hmat: " fmt

#समावेश <linux/acpi.h>
#समावेश <linux/bitops.h>
#समावेश <linux/device.h>
#समावेश <linux/init.h>
#समावेश <linux/list.h>
#समावेश <linux/mm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/list_sort.h>
#समावेश <linux/memregion.h>
#समावेश <linux/memory.h>
#समावेश <linux/mutex.h>
#समावेश <linux/node.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/dax.h>

अटल u8 hmat_revision;
अटल पूर्णांक hmat_disable __initdata;

व्योम __init disable_hmat(व्योम)
अणु
	hmat_disable = 1;
पूर्ण

अटल LIST_HEAD(tarमाला_लो);
अटल LIST_HEAD(initiators);
अटल LIST_HEAD(localities);

अटल DEFINE_MUTEX(target_lock);

/*
 * The defined क्रमागत order is used to prioritize attributes to अवरोध ties when
 * selecting the best perक्रमming node.
 */
क्रमागत locality_types अणु
	WRITE_LATENCY,
	READ_LATENCY,
	WRITE_BANDWIDTH,
	READ_BANDWIDTH,
पूर्ण;

अटल काष्ठा memory_locality *localities_types[4];

काष्ठा target_cache अणु
	काष्ठा list_head node;
	काष्ठा node_cache_attrs cache_attrs;
पूर्ण;

काष्ठा memory_target अणु
	काष्ठा list_head node;
	अचिन्हित पूर्णांक memory_pxm;
	अचिन्हित पूर्णांक processor_pxm;
	काष्ठा resource memregions;
	काष्ठा node_hmem_attrs hmem_attrs[2];
	काष्ठा list_head caches;
	काष्ठा node_cache_attrs cache_attrs;
	bool रेजिस्टरed;
पूर्ण;

काष्ठा memory_initiator अणु
	काष्ठा list_head node;
	अचिन्हित पूर्णांक processor_pxm;
	bool has_cpu;
पूर्ण;

काष्ठा memory_locality अणु
	काष्ठा list_head node;
	काष्ठा acpi_hmat_locality *hmat_loc;
पूर्ण;

अटल काष्ठा memory_initiator *find_mem_initiator(अचिन्हित पूर्णांक cpu_pxm)
अणु
	काष्ठा memory_initiator *initiator;

	list_क्रम_each_entry(initiator, &initiators, node)
		अगर (initiator->processor_pxm == cpu_pxm)
			वापस initiator;
	वापस शून्य;
पूर्ण

अटल काष्ठा memory_target *find_mem_target(अचिन्हित पूर्णांक mem_pxm)
अणु
	काष्ठा memory_target *target;

	list_क्रम_each_entry(target, &tarमाला_लो, node)
		अगर (target->memory_pxm == mem_pxm)
			वापस target;
	वापस शून्य;
पूर्ण

अटल __init व्योम alloc_memory_initiator(अचिन्हित पूर्णांक cpu_pxm)
अणु
	काष्ठा memory_initiator *initiator;

	अगर (pxm_to_node(cpu_pxm) == NUMA_NO_NODE)
		वापस;

	initiator = find_mem_initiator(cpu_pxm);
	अगर (initiator)
		वापस;

	initiator = kzalloc(माप(*initiator), GFP_KERNEL);
	अगर (!initiator)
		वापस;

	initiator->processor_pxm = cpu_pxm;
	initiator->has_cpu = node_state(pxm_to_node(cpu_pxm), N_CPU);
	list_add_tail(&initiator->node, &initiators);
पूर्ण

अटल __init व्योम alloc_memory_target(अचिन्हित पूर्णांक mem_pxm,
		resource_माप_प्रकार start, resource_माप_प्रकार len)
अणु
	काष्ठा memory_target *target;

	target = find_mem_target(mem_pxm);
	अगर (!target) अणु
		target = kzalloc(माप(*target), GFP_KERNEL);
		अगर (!target)
			वापस;
		target->memory_pxm = mem_pxm;
		target->processor_pxm = PXM_INVAL;
		target->memregions = (काष्ठा resource) अणु
			.name	= "ACPI mem",
			.start	= 0,
			.end	= -1,
			.flags	= IORESOURCE_MEM,
		पूर्ण;
		list_add_tail(&target->node, &tarमाला_लो);
		INIT_LIST_HEAD(&target->caches);
	पूर्ण

	/*
	 * There are potentially multiple ranges per PXM, so record each
	 * in the per-target memregions resource tree.
	 */
	अगर (!__request_region(&target->memregions, start, len, "memory target",
				IORESOURCE_MEM))
		pr_warn("failed to reserve %#llx - %#llx in pxm: %d\n",
				start, start + len, mem_pxm);
पूर्ण

अटल __init स्थिर अक्षर *hmat_data_type(u8 type)
अणु
	चयन (type) अणु
	हाल ACPI_HMAT_ACCESS_LATENCY:
		वापस "Access Latency";
	हाल ACPI_HMAT_READ_LATENCY:
		वापस "Read Latency";
	हाल ACPI_HMAT_WRITE_LATENCY:
		वापस "Write Latency";
	हाल ACPI_HMAT_ACCESS_BANDWIDTH:
		वापस "Access Bandwidth";
	हाल ACPI_HMAT_READ_BANDWIDTH:
		वापस "Read Bandwidth";
	हाल ACPI_HMAT_WRITE_BANDWIDTH:
		वापस "Write Bandwidth";
	शेष:
		वापस "Reserved";
	पूर्ण
पूर्ण

अटल __init स्थिर अक्षर *hmat_data_type_suffix(u8 type)
अणु
	चयन (type) अणु
	हाल ACPI_HMAT_ACCESS_LATENCY:
	हाल ACPI_HMAT_READ_LATENCY:
	हाल ACPI_HMAT_WRITE_LATENCY:
		वापस " nsec";
	हाल ACPI_HMAT_ACCESS_BANDWIDTH:
	हाल ACPI_HMAT_READ_BANDWIDTH:
	हाल ACPI_HMAT_WRITE_BANDWIDTH:
		वापस " MB/s";
	शेष:
		वापस "";
	पूर्ण
पूर्ण

अटल u32 hmat_normalize(u16 entry, u64 base, u8 type)
अणु
	u32 value;

	/*
	 * Check क्रम invalid and overflow values
	 */
	अगर (entry == 0xffff || !entry)
		वापस 0;
	अन्यथा अगर (base > (अच_पूर्णांक_उच्च / (entry)))
		वापस 0;

	/*
	 * Divide by the base unit क्रम version 1, convert latency from
	 * picosenonds to nanoseconds अगर revision 2.
	 */
	value = entry * base;
	अगर (hmat_revision == 1) अणु
		अगर (value < 10)
			वापस 0;
		value = DIV_ROUND_UP(value, 10);
	पूर्ण अन्यथा अगर (hmat_revision == 2) अणु
		चयन (type) अणु
		हाल ACPI_HMAT_ACCESS_LATENCY:
		हाल ACPI_HMAT_READ_LATENCY:
		हाल ACPI_HMAT_WRITE_LATENCY:
			value = DIV_ROUND_UP(value, 1000);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण
	वापस value;
पूर्ण

अटल व्योम hmat_update_target_access(काष्ठा memory_target *target,
				      u8 type, u32 value, पूर्णांक access)
अणु
	चयन (type) अणु
	हाल ACPI_HMAT_ACCESS_LATENCY:
		target->hmem_attrs[access].पढ़ो_latency = value;
		target->hmem_attrs[access].ग_लिखो_latency = value;
		अवरोध;
	हाल ACPI_HMAT_READ_LATENCY:
		target->hmem_attrs[access].पढ़ो_latency = value;
		अवरोध;
	हाल ACPI_HMAT_WRITE_LATENCY:
		target->hmem_attrs[access].ग_लिखो_latency = value;
		अवरोध;
	हाल ACPI_HMAT_ACCESS_BANDWIDTH:
		target->hmem_attrs[access].पढ़ो_bandwidth = value;
		target->hmem_attrs[access].ग_लिखो_bandwidth = value;
		अवरोध;
	हाल ACPI_HMAT_READ_BANDWIDTH:
		target->hmem_attrs[access].पढ़ो_bandwidth = value;
		अवरोध;
	हाल ACPI_HMAT_WRITE_BANDWIDTH:
		target->hmem_attrs[access].ग_लिखो_bandwidth = value;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल __init व्योम hmat_add_locality(काष्ठा acpi_hmat_locality *hmat_loc)
अणु
	काष्ठा memory_locality *loc;

	loc = kzalloc(माप(*loc), GFP_KERNEL);
	अगर (!loc) अणु
		pr_notice_once("Failed to allocate HMAT locality\n");
		वापस;
	पूर्ण

	loc->hmat_loc = hmat_loc;
	list_add_tail(&loc->node, &localities);

	चयन (hmat_loc->data_type) अणु
	हाल ACPI_HMAT_ACCESS_LATENCY:
		localities_types[READ_LATENCY] = loc;
		localities_types[WRITE_LATENCY] = loc;
		अवरोध;
	हाल ACPI_HMAT_READ_LATENCY:
		localities_types[READ_LATENCY] = loc;
		अवरोध;
	हाल ACPI_HMAT_WRITE_LATENCY:
		localities_types[WRITE_LATENCY] = loc;
		अवरोध;
	हाल ACPI_HMAT_ACCESS_BANDWIDTH:
		localities_types[READ_BANDWIDTH] = loc;
		localities_types[WRITE_BANDWIDTH] = loc;
		अवरोध;
	हाल ACPI_HMAT_READ_BANDWIDTH:
		localities_types[READ_BANDWIDTH] = loc;
		अवरोध;
	हाल ACPI_HMAT_WRITE_BANDWIDTH:
		localities_types[WRITE_BANDWIDTH] = loc;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल __init पूर्णांक hmat_parse_locality(जोड़ acpi_subtable_headers *header,
				      स्थिर अचिन्हित दीर्घ end)
अणु
	काष्ठा acpi_hmat_locality *hmat_loc = (व्योम *)header;
	काष्ठा memory_target *target;
	अचिन्हित पूर्णांक init, targ, total_size, ipds, tpds;
	u32 *inits, *targs, value;
	u16 *entries;
	u8 type, mem_hier;

	अगर (hmat_loc->header.length < माप(*hmat_loc)) अणु
		pr_notice("HMAT: Unexpected locality header length: %u\n",
			 hmat_loc->header.length);
		वापस -EINVAL;
	पूर्ण

	type = hmat_loc->data_type;
	mem_hier = hmat_loc->flags & ACPI_HMAT_MEMORY_HIERARCHY;
	ipds = hmat_loc->number_of_initiator_Pds;
	tpds = hmat_loc->number_of_target_Pds;
	total_size = माप(*hmat_loc) + माप(*entries) * ipds * tpds +
		     माप(*inits) * ipds + माप(*targs) * tpds;
	अगर (hmat_loc->header.length < total_size) अणु
		pr_notice("HMAT: Unexpected locality header length:%u, minimum required:%u\n",
			 hmat_loc->header.length, total_size);
		वापस -EINVAL;
	पूर्ण

	pr_info("HMAT: Locality: Flags:%02x Type:%s Initiator Domains:%u Target Domains:%u Base:%lld\n",
		hmat_loc->flags, hmat_data_type(type), ipds, tpds,
		hmat_loc->entry_base_unit);

	inits = (u32 *)(hmat_loc + 1);
	targs = inits + ipds;
	entries = (u16 *)(targs + tpds);
	क्रम (init = 0; init < ipds; init++) अणु
		alloc_memory_initiator(inits[init]);
		क्रम (targ = 0; targ < tpds; targ++) अणु
			value = hmat_normalize(entries[init * tpds + targ],
					       hmat_loc->entry_base_unit,
					       type);
			pr_info("  Initiator-Target[%u-%u]:%u%s\n",
				inits[init], targs[targ], value,
				hmat_data_type_suffix(type));

			अगर (mem_hier == ACPI_HMAT_MEMORY) अणु
				target = find_mem_target(targs[targ]);
				अगर (target && target->processor_pxm == inits[init]) अणु
					hmat_update_target_access(target, type, value, 0);
					/* If the node has a CPU, update access 1 */
					अगर (node_state(pxm_to_node(inits[init]), N_CPU))
						hmat_update_target_access(target, type, value, 1);
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (mem_hier == ACPI_HMAT_MEMORY)
		hmat_add_locality(hmat_loc);

	वापस 0;
पूर्ण

अटल __init पूर्णांक hmat_parse_cache(जोड़ acpi_subtable_headers *header,
				   स्थिर अचिन्हित दीर्घ end)
अणु
	काष्ठा acpi_hmat_cache *cache = (व्योम *)header;
	काष्ठा memory_target *target;
	काष्ठा target_cache *tcache;
	u32 attrs;

	अगर (cache->header.length < माप(*cache)) अणु
		pr_notice("HMAT: Unexpected cache header length: %u\n",
			 cache->header.length);
		वापस -EINVAL;
	पूर्ण

	attrs = cache->cache_attributes;
	pr_info("HMAT: Cache: Domain:%u Size:%llu Attrs:%08x SMBIOS Handles:%d\n",
		cache->memory_PD, cache->cache_size, attrs,
		cache->number_of_SMBIOShandles);

	target = find_mem_target(cache->memory_PD);
	अगर (!target)
		वापस 0;

	tcache = kzalloc(माप(*tcache), GFP_KERNEL);
	अगर (!tcache) अणु
		pr_notice_once("Failed to allocate HMAT cache info\n");
		वापस 0;
	पूर्ण

	tcache->cache_attrs.size = cache->cache_size;
	tcache->cache_attrs.level = (attrs & ACPI_HMAT_CACHE_LEVEL) >> 4;
	tcache->cache_attrs.line_size = (attrs & ACPI_HMAT_CACHE_LINE_SIZE) >> 16;

	चयन ((attrs & ACPI_HMAT_CACHE_ASSOCIATIVITY) >> 8) अणु
	हाल ACPI_HMAT_CA_सूचीECT_MAPPED:
		tcache->cache_attrs.indexing = NODE_CACHE_सूचीECT_MAP;
		अवरोध;
	हाल ACPI_HMAT_CA_COMPLEX_CACHE_INDEXING:
		tcache->cache_attrs.indexing = NODE_CACHE_INDEXED;
		अवरोध;
	हाल ACPI_HMAT_CA_NONE:
	शेष:
		tcache->cache_attrs.indexing = NODE_CACHE_OTHER;
		अवरोध;
	पूर्ण

	चयन ((attrs & ACPI_HMAT_WRITE_POLICY) >> 12) अणु
	हाल ACPI_HMAT_CP_WB:
		tcache->cache_attrs.ग_लिखो_policy = NODE_CACHE_WRITE_BACK;
		अवरोध;
	हाल ACPI_HMAT_CP_WT:
		tcache->cache_attrs.ग_लिखो_policy = NODE_CACHE_WRITE_THROUGH;
		अवरोध;
	हाल ACPI_HMAT_CP_NONE:
	शेष:
		tcache->cache_attrs.ग_लिखो_policy = NODE_CACHE_WRITE_OTHER;
		अवरोध;
	पूर्ण
	list_add_tail(&tcache->node, &target->caches);

	वापस 0;
पूर्ण

अटल पूर्णांक __init hmat_parse_proximity_करोमुख्य(जोड़ acpi_subtable_headers *header,
					      स्थिर अचिन्हित दीर्घ end)
अणु
	काष्ठा acpi_hmat_proximity_करोमुख्य *p = (व्योम *)header;
	काष्ठा memory_target *target = शून्य;

	अगर (p->header.length != माप(*p)) अणु
		pr_notice("HMAT: Unexpected address range header length: %u\n",
			 p->header.length);
		वापस -EINVAL;
	पूर्ण

	अगर (hmat_revision == 1)
		pr_info("HMAT: Memory (%#llx length %#llx) Flags:%04x Processor Domain:%u Memory Domain:%u\n",
			p->reserved3, p->reserved4, p->flags, p->processor_PD,
			p->memory_PD);
	अन्यथा
		pr_info("HMAT: Memory Flags:%04x Processor Domain:%u Memory Domain:%u\n",
			p->flags, p->processor_PD, p->memory_PD);

	अगर ((hmat_revision == 1 && p->flags & ACPI_HMAT_MEMORY_PD_VALID) ||
	    hmat_revision > 1) अणु
		target = find_mem_target(p->memory_PD);
		अगर (!target) अणु
			pr_debug("HMAT: Memory Domain missing from SRAT\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण
	अगर (target && p->flags & ACPI_HMAT_PROCESSOR_PD_VALID) अणु
		पूर्णांक p_node = pxm_to_node(p->processor_PD);

		अगर (p_node == NUMA_NO_NODE) अणु
			pr_debug("HMAT: Invalid Processor Domain\n");
			वापस -EINVAL;
		पूर्ण
		target->processor_pxm = p->processor_PD;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __init hmat_parse_subtable(जोड़ acpi_subtable_headers *header,
				      स्थिर अचिन्हित दीर्घ end)
अणु
	काष्ठा acpi_hmat_काष्ठाure *hdr = (व्योम *)header;

	अगर (!hdr)
		वापस -EINVAL;

	चयन (hdr->type) अणु
	हाल ACPI_HMAT_TYPE_PROXIMITY:
		वापस hmat_parse_proximity_करोमुख्य(header, end);
	हाल ACPI_HMAT_TYPE_LOCALITY:
		वापस hmat_parse_locality(header, end);
	हाल ACPI_HMAT_TYPE_CACHE:
		वापस hmat_parse_cache(header, end);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल __init पूर्णांक srat_parse_mem_affinity(जोड़ acpi_subtable_headers *header,
					  स्थिर अचिन्हित दीर्घ end)
अणु
	काष्ठा acpi_srat_mem_affinity *ma = (व्योम *)header;

	अगर (!ma)
		वापस -EINVAL;
	अगर (!(ma->flags & ACPI_SRAT_MEM_ENABLED))
		वापस 0;
	alloc_memory_target(ma->proximity_करोमुख्य, ma->base_address, ma->length);
	वापस 0;
पूर्ण

अटल u32 hmat_initiator_perf(काष्ठा memory_target *target,
			       काष्ठा memory_initiator *initiator,
			       काष्ठा acpi_hmat_locality *hmat_loc)
अणु
	अचिन्हित पूर्णांक ipds, tpds, i, idx = 0, tdx = 0;
	u32 *inits, *targs;
	u16 *entries;

	ipds = hmat_loc->number_of_initiator_Pds;
	tpds = hmat_loc->number_of_target_Pds;
	inits = (u32 *)(hmat_loc + 1);
	targs = inits + ipds;
	entries = (u16 *)(targs + tpds);

	क्रम (i = 0; i < ipds; i++) अणु
		अगर (inits[i] == initiator->processor_pxm) अणु
			idx = i;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (i == ipds)
		वापस 0;

	क्रम (i = 0; i < tpds; i++) अणु
		अगर (targs[i] == target->memory_pxm) अणु
			tdx = i;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (i == tpds)
		वापस 0;

	वापस hmat_normalize(entries[idx * tpds + tdx],
			      hmat_loc->entry_base_unit,
			      hmat_loc->data_type);
पूर्ण

अटल bool hmat_update_best(u8 type, u32 value, u32 *best)
अणु
	bool updated = false;

	अगर (!value)
		वापस false;

	चयन (type) अणु
	हाल ACPI_HMAT_ACCESS_LATENCY:
	हाल ACPI_HMAT_READ_LATENCY:
	हाल ACPI_HMAT_WRITE_LATENCY:
		अगर (!*best || *best > value) अणु
			*best = value;
			updated = true;
		पूर्ण
		अवरोध;
	हाल ACPI_HMAT_ACCESS_BANDWIDTH:
	हाल ACPI_HMAT_READ_BANDWIDTH:
	हाल ACPI_HMAT_WRITE_BANDWIDTH:
		अगर (!*best || *best < value) अणु
			*best = value;
			updated = true;
		पूर्ण
		अवरोध;
	पूर्ण

	वापस updated;
पूर्ण

अटल पूर्णांक initiator_cmp(व्योम *priv, स्थिर काष्ठा list_head *a,
			 स्थिर काष्ठा list_head *b)
अणु
	काष्ठा memory_initiator *ia;
	काष्ठा memory_initiator *ib;
	अचिन्हित दीर्घ *p_nodes = priv;

	ia = list_entry(a, काष्ठा memory_initiator, node);
	ib = list_entry(b, काष्ठा memory_initiator, node);

	set_bit(ia->processor_pxm, p_nodes);
	set_bit(ib->processor_pxm, p_nodes);

	वापस ia->processor_pxm - ib->processor_pxm;
पूर्ण

अटल व्योम hmat_रेजिस्टर_target_initiators(काष्ठा memory_target *target)
अणु
	अटल DECLARE_BITMAP(p_nodes, MAX_NUMNODES);
	काष्ठा memory_initiator *initiator;
	अचिन्हित पूर्णांक mem_nid, cpu_nid;
	काष्ठा memory_locality *loc = शून्य;
	u32 best = 0;
	bool access0करोne = false;
	पूर्णांक i;

	mem_nid = pxm_to_node(target->memory_pxm);
	/*
	 * If the Address Range Structure provides a local processor pxm, link
	 * only that one. Otherwise, find the best perक्रमmance attributes and
	 * रेजिस्टर all initiators that match.
	 */
	अगर (target->processor_pxm != PXM_INVAL) अणु
		cpu_nid = pxm_to_node(target->processor_pxm);
		रेजिस्टर_memory_node_under_compute_node(mem_nid, cpu_nid, 0);
		access0करोne = true;
		अगर (node_state(cpu_nid, N_CPU)) अणु
			रेजिस्टर_memory_node_under_compute_node(mem_nid, cpu_nid, 1);
			वापस;
		पूर्ण
	पूर्ण

	अगर (list_empty(&localities))
		वापस;

	/*
	 * We need the initiator list sorted so we can use biपंचांगap_clear क्रम
	 * previously set initiators when we find a better memory accessor.
	 * We'll also use the sorting to prime the candidate nodes with known
	 * initiators.
	 */
	biपंचांगap_zero(p_nodes, MAX_NUMNODES);
	list_sort(p_nodes, &initiators, initiator_cmp);
	अगर (!access0करोne) अणु
		क्रम (i = WRITE_LATENCY; i <= READ_BANDWIDTH; i++) अणु
			loc = localities_types[i];
			अगर (!loc)
				जारी;

			best = 0;
			list_क्रम_each_entry(initiator, &initiators, node) अणु
				u32 value;

				अगर (!test_bit(initiator->processor_pxm, p_nodes))
					जारी;

				value = hmat_initiator_perf(target, initiator,
							    loc->hmat_loc);
				अगर (hmat_update_best(loc->hmat_loc->data_type, value, &best))
					biपंचांगap_clear(p_nodes, 0, initiator->processor_pxm);
				अगर (value != best)
					clear_bit(initiator->processor_pxm, p_nodes);
			पूर्ण
			अगर (best)
				hmat_update_target_access(target, loc->hmat_loc->data_type,
							  best, 0);
		पूर्ण

		क्रम_each_set_bit(i, p_nodes, MAX_NUMNODES) अणु
			cpu_nid = pxm_to_node(i);
			रेजिस्टर_memory_node_under_compute_node(mem_nid, cpu_nid, 0);
		पूर्ण
	पूर्ण

	/* Access 1 ignores Generic Initiators */
	biपंचांगap_zero(p_nodes, MAX_NUMNODES);
	list_sort(p_nodes, &initiators, initiator_cmp);
	best = 0;
	क्रम (i = WRITE_LATENCY; i <= READ_BANDWIDTH; i++) अणु
		loc = localities_types[i];
		अगर (!loc)
			जारी;

		best = 0;
		list_क्रम_each_entry(initiator, &initiators, node) अणु
			u32 value;

			अगर (!initiator->has_cpu) अणु
				clear_bit(initiator->processor_pxm, p_nodes);
				जारी;
			पूर्ण
			अगर (!test_bit(initiator->processor_pxm, p_nodes))
				जारी;

			value = hmat_initiator_perf(target, initiator, loc->hmat_loc);
			अगर (hmat_update_best(loc->hmat_loc->data_type, value, &best))
				biपंचांगap_clear(p_nodes, 0, initiator->processor_pxm);
			अगर (value != best)
				clear_bit(initiator->processor_pxm, p_nodes);
		पूर्ण
		अगर (best)
			hmat_update_target_access(target, loc->hmat_loc->data_type, best, 1);
	पूर्ण
	क्रम_each_set_bit(i, p_nodes, MAX_NUMNODES) अणु
		cpu_nid = pxm_to_node(i);
		रेजिस्टर_memory_node_under_compute_node(mem_nid, cpu_nid, 1);
	पूर्ण
पूर्ण

अटल व्योम hmat_रेजिस्टर_target_cache(काष्ठा memory_target *target)
अणु
	अचिन्हित mem_nid = pxm_to_node(target->memory_pxm);
	काष्ठा target_cache *tcache;

	list_क्रम_each_entry(tcache, &target->caches, node)
		node_add_cache(mem_nid, &tcache->cache_attrs);
पूर्ण

अटल व्योम hmat_रेजिस्टर_target_perf(काष्ठा memory_target *target, पूर्णांक access)
अणु
	अचिन्हित mem_nid = pxm_to_node(target->memory_pxm);
	node_set_perf_attrs(mem_nid, &target->hmem_attrs[access], access);
पूर्ण

अटल व्योम hmat_रेजिस्टर_target_devices(काष्ठा memory_target *target)
अणु
	काष्ठा resource *res;

	/*
	 * Do not bother creating devices अगर no driver is available to
	 * consume them.
	 */
	अगर (!IS_ENABLED(CONFIG_DEV_DAX_HMEM))
		वापस;

	क्रम (res = target->memregions.child; res; res = res->sibling) अणु
		पूर्णांक target_nid = pxm_to_node(target->memory_pxm);

		hmem_रेजिस्टर_device(target_nid, res);
	पूर्ण
पूर्ण

अटल व्योम hmat_रेजिस्टर_target(काष्ठा memory_target *target)
अणु
	पूर्णांक nid = pxm_to_node(target->memory_pxm);

	/*
	 * Devices may beदीर्घ to either an offline or online
	 * node, so unconditionally add them.
	 */
	hmat_रेजिस्टर_target_devices(target);

	/*
	 * Skip offline nodes. This can happen when memory
	 * marked EFI_MEMORY_SP, "specific purpose", is applied
	 * to all the memory in a proximity करोमुख्य leading to
	 * the node being marked offline / unplugged, or अगर
	 * memory-only "hotplug" node is offline.
	 */
	अगर (nid == NUMA_NO_NODE || !node_online(nid))
		वापस;

	mutex_lock(&target_lock);
	अगर (!target->रेजिस्टरed) अणु
		hmat_रेजिस्टर_target_initiators(target);
		hmat_रेजिस्टर_target_cache(target);
		hmat_रेजिस्टर_target_perf(target, 0);
		hmat_रेजिस्टर_target_perf(target, 1);
		target->रेजिस्टरed = true;
	पूर्ण
	mutex_unlock(&target_lock);
पूर्ण

अटल व्योम hmat_रेजिस्टर_tarमाला_लो(व्योम)
अणु
	काष्ठा memory_target *target;

	list_क्रम_each_entry(target, &tarमाला_लो, node)
		hmat_रेजिस्टर_target(target);
पूर्ण

अटल पूर्णांक hmat_callback(काष्ठा notअगरier_block *self,
			 अचिन्हित दीर्घ action, व्योम *arg)
अणु
	काष्ठा memory_target *target;
	काष्ठा memory_notअगरy *mnb = arg;
	पूर्णांक pxm, nid = mnb->status_change_nid;

	अगर (nid == NUMA_NO_NODE || action != MEM_ONLINE)
		वापस NOTIFY_OK;

	pxm = node_to_pxm(nid);
	target = find_mem_target(pxm);
	अगर (!target)
		वापस NOTIFY_OK;

	hmat_रेजिस्टर_target(target);
	वापस NOTIFY_OK;
पूर्ण

अटल काष्ठा notअगरier_block hmat_callback_nb = अणु
	.notअगरier_call = hmat_callback,
	.priority = 2,
पूर्ण;

अटल __init व्योम hmat_मुक्त_काष्ठाures(व्योम)
अणु
	काष्ठा memory_target *target, *tnext;
	काष्ठा memory_locality *loc, *lnext;
	काष्ठा memory_initiator *initiator, *inext;
	काष्ठा target_cache *tcache, *cnext;

	list_क्रम_each_entry_safe(target, tnext, &tarमाला_लो, node) अणु
		काष्ठा resource *res, *res_next;

		list_क्रम_each_entry_safe(tcache, cnext, &target->caches, node) अणु
			list_del(&tcache->node);
			kमुक्त(tcache);
		पूर्ण

		list_del(&target->node);
		res = target->memregions.child;
		जबतक (res) अणु
			res_next = res->sibling;
			__release_region(&target->memregions, res->start,
					resource_size(res));
			res = res_next;
		पूर्ण
		kमुक्त(target);
	पूर्ण

	list_क्रम_each_entry_safe(initiator, inext, &initiators, node) अणु
		list_del(&initiator->node);
		kमुक्त(initiator);
	पूर्ण

	list_क्रम_each_entry_safe(loc, lnext, &localities, node) अणु
		list_del(&loc->node);
		kमुक्त(loc);
	पूर्ण
पूर्ण

अटल __init पूर्णांक hmat_init(व्योम)
अणु
	काष्ठा acpi_table_header *tbl;
	क्रमागत acpi_hmat_type i;
	acpi_status status;

	अगर (srat_disabled() || hmat_disable)
		वापस 0;

	status = acpi_get_table(ACPI_SIG_SRAT, 0, &tbl);
	अगर (ACPI_FAILURE(status))
		वापस 0;

	अगर (acpi_table_parse_entries(ACPI_SIG_SRAT,
				माप(काष्ठा acpi_table_srat),
				ACPI_SRAT_TYPE_MEMORY_AFFINITY,
				srat_parse_mem_affinity, 0) < 0)
		जाओ out_put;
	acpi_put_table(tbl);

	status = acpi_get_table(ACPI_SIG_HMAT, 0, &tbl);
	अगर (ACPI_FAILURE(status))
		जाओ out_put;

	hmat_revision = tbl->revision;
	चयन (hmat_revision) अणु
	हाल 1:
	हाल 2:
		अवरोध;
	शेष:
		pr_notice("Ignoring HMAT: Unknown revision:%d\n", hmat_revision);
		जाओ out_put;
	पूर्ण

	क्रम (i = ACPI_HMAT_TYPE_PROXIMITY; i < ACPI_HMAT_TYPE_RESERVED; i++) अणु
		अगर (acpi_table_parse_entries(ACPI_SIG_HMAT,
					     माप(काष्ठा acpi_table_hmat), i,
					     hmat_parse_subtable, 0) < 0) अणु
			pr_notice("Ignoring HMAT: Invalid table");
			जाओ out_put;
		पूर्ण
	पूर्ण
	hmat_रेजिस्टर_tarमाला_लो();

	/* Keep the table and काष्ठाures अगर the notअगरier may use them */
	अगर (!रेजिस्टर_hoपंचांगemory_notअगरier(&hmat_callback_nb))
		वापस 0;
out_put:
	hmat_मुक्त_काष्ठाures();
	acpi_put_table(tbl);
	वापस 0;
पूर्ण
device_initcall(hmat_init);
