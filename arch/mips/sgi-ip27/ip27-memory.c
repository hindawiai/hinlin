<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2000, 05 by Ralf Baechle (ralf@linux-mips.org)
 * Copyright (C) 2000 by Silicon Graphics, Inc.
 * Copyright (C) 2004 by Christoph Hellwig
 *
 * On SGI IP27 the ARC memory configuration data is completely bogus but
 * alternate easier to use mechanisms are available.
 */
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/memblock.h>
#समावेश <linux/mm.h>
#समावेश <linux/mmzone.h>
#समावेश <linux/export.h>
#समावेश <linux/nodemask.h>
#समावेश <linux/swap.h>
#समावेश <linux/pfn.h>
#समावेश <linux/highस्मृति.स>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/pgभाग.स>
#समावेश <यंत्र/sections.h>

#समावेश <यंत्र/sn/arch.h>
#समावेश <यंत्र/sn/agent.h>
#समावेश <यंत्र/sn/klconfig.h>

#समावेश "ip27-common.h"

#घोषणा SLOT_PFNSHIFT		(SLOT_SHIFT - PAGE_SHIFT)
#घोषणा PFN_NASIDSHFT		(NASID_SHFT - PAGE_SHIFT)

काष्ठा node_data *__node_data[MAX_NUMNODES];

EXPORT_SYMBOL(__node_data);

अटल u64 gen_region_mask(व्योम)
अणु
	पूर्णांक region_shअगरt;
	u64 region_mask;
	nasid_t nasid;

	region_shअगरt = get_region_shअगरt();
	region_mask = 0;
	क्रम_each_online_node(nasid)
		region_mask |= BIT_ULL(nasid >> region_shअगरt);

	वापस region_mask;
पूर्ण

#घोषणा rou_rflag	rou_flags

अटल पूर्णांक router_distance;

अटल व्योम router_recurse(klrou_t *router_a, klrou_t *router_b, पूर्णांक depth)
अणु
	klrou_t *router;
	lboard_t *brd;
	पूर्णांक	port;

	अगर (router_a->rou_rflag == 1)
		वापस;

	अगर (depth >= router_distance)
		वापस;

	router_a->rou_rflag = 1;

	क्रम (port = 1; port <= MAX_ROUTER_PORTS; port++) अणु
		अगर (router_a->rou_port[port].port_nasid == INVALID_NASID)
			जारी;

		brd = (lboard_t *)NODE_OFFSET_TO_K0(
			router_a->rou_port[port].port_nasid,
			router_a->rou_port[port].port_offset);

		अगर (brd->brd_type == KLTYPE_ROUTER) अणु
			router = (klrou_t *)NODE_OFFSET_TO_K0(NASID_GET(brd), brd->brd_compts[0]);
			अगर (router == router_b) अणु
				अगर (depth < router_distance)
					router_distance = depth;
			पूर्ण
			अन्यथा
				router_recurse(router, router_b, depth + 1);
		पूर्ण
	पूर्ण

	router_a->rou_rflag = 0;
पूर्ण

अचिन्हित अक्षर __node_distances[MAX_NUMNODES][MAX_NUMNODES];
EXPORT_SYMBOL(__node_distances);

अटल पूर्णांक __init compute_node_distance(nasid_t nasid_a, nasid_t nasid_b)
अणु
	klrou_t *router, *router_a = शून्य, *router_b = शून्य;
	lboard_t *brd, *dest_brd;
	nasid_t nasid;
	पूर्णांक port;

	/* Figure out which routers nodes in question are connected to */
	क्रम_each_online_node(nasid) अणु
		brd = find_lboard_class((lboard_t *)KL_CONFIG_INFO(nasid),
					KLTYPE_ROUTER);

		अगर (!brd)
			जारी;

		करो अणु
			अगर (brd->brd_flags & DUPLICATE_BOARD)
				जारी;

			router = (klrou_t *)NODE_OFFSET_TO_K0(NASID_GET(brd), brd->brd_compts[0]);
			router->rou_rflag = 0;

			क्रम (port = 1; port <= MAX_ROUTER_PORTS; port++) अणु
				अगर (router->rou_port[port].port_nasid == INVALID_NASID)
					जारी;

				dest_brd = (lboard_t *)NODE_OFFSET_TO_K0(
					router->rou_port[port].port_nasid,
					router->rou_port[port].port_offset);

				अगर (dest_brd->brd_type == KLTYPE_IP27) अणु
					अगर (dest_brd->brd_nasid == nasid_a)
						router_a = router;
					अगर (dest_brd->brd_nasid == nasid_b)
						router_b = router;
				पूर्ण
			पूर्ण

		पूर्ण जबतक ((brd = find_lboard_class(KLCF_NEXT(brd), KLTYPE_ROUTER)));
	पूर्ण

	अगर (nasid_a == nasid_b)
		वापस LOCAL_DISTANCE;

	अगर (router_a == router_b)
		वापस LOCAL_DISTANCE + 1;

	अगर (router_a == शून्य) अणु
		pr_info("node_distance: router_a NULL\n");
		वापस 255;
	पूर्ण
	अगर (router_b == शून्य) अणु
		pr_info("node_distance: router_b NULL\n");
		वापस 255;
	पूर्ण

	router_distance = 100;
	router_recurse(router_a, router_b, 2);

	वापस LOCAL_DISTANCE + router_distance;
पूर्ण

अटल व्योम __init init_topology_matrix(व्योम)
अणु
	nasid_t row, col;

	क्रम (row = 0; row < MAX_NUMNODES; row++)
		क्रम (col = 0; col < MAX_NUMNODES; col++)
			__node_distances[row][col] = -1;

	क्रम_each_online_node(row) अणु
		क्रम_each_online_node(col) अणु
			__node_distances[row][col] =
				compute_node_distance(row, col);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम __init dump_topology(व्योम)
अणु
	nasid_t nasid;
	lboard_t *brd, *dest_brd;
	पूर्णांक port;
	पूर्णांक router_num = 0;
	klrou_t *router;
	nasid_t row, col;

	pr_info("************** Topology ********************\n");

	pr_info("    ");
	क्रम_each_online_node(col)
		pr_cont("%02d ", col);
	pr_cont("\n");
	क्रम_each_online_node(row) अणु
		pr_info("%02d  ", row);
		क्रम_each_online_node(col)
			pr_cont("%2d ", node_distance(row, col));
		pr_cont("\n");
	पूर्ण

	क्रम_each_online_node(nasid) अणु
		brd = find_lboard_class((lboard_t *)KL_CONFIG_INFO(nasid),
					KLTYPE_ROUTER);

		अगर (!brd)
			जारी;

		करो अणु
			अगर (brd->brd_flags & DUPLICATE_BOARD)
				जारी;
			pr_cont("Router %d:", router_num);
			router_num++;

			router = (klrou_t *)NODE_OFFSET_TO_K0(NASID_GET(brd), brd->brd_compts[0]);

			क्रम (port = 1; port <= MAX_ROUTER_PORTS; port++) अणु
				अगर (router->rou_port[port].port_nasid == INVALID_NASID)
					जारी;

				dest_brd = (lboard_t *)NODE_OFFSET_TO_K0(
					router->rou_port[port].port_nasid,
					router->rou_port[port].port_offset);

				अगर (dest_brd->brd_type == KLTYPE_IP27)
					pr_cont(" %d", dest_brd->brd_nasid);
				अगर (dest_brd->brd_type == KLTYPE_ROUTER)
					pr_cont(" r");
			पूर्ण
			pr_cont("\n");

		पूर्ण जबतक ( (brd = find_lboard_class(KLCF_NEXT(brd), KLTYPE_ROUTER)) );
	पूर्ण
पूर्ण

अटल अचिन्हित दीर्घ __init slot_getbasepfn(nasid_t nasid, पूर्णांक slot)
अणु
	वापस ((अचिन्हित दीर्घ)nasid << PFN_NASIDSHFT) | (slot << SLOT_PFNSHIFT);
पूर्ण

अटल अचिन्हित दीर्घ __init slot_psize_compute(nasid_t nasid, पूर्णांक slot)
अणु
	lboard_t *brd;
	klmembnk_t *banks;
	अचिन्हित दीर्घ size;

	/* Find the node board */
	brd = find_lboard((lboard_t *)KL_CONFIG_INFO(nasid), KLTYPE_IP27);
	अगर (!brd)
		वापस 0;

	/* Get the memory bank काष्ठाure */
	banks = (klmembnk_t *) find_first_component(brd, KLSTRUCT_MEMBNK);
	अगर (!banks)
		वापस 0;

	/* Size in _Megabytes_ */
	size = (अचिन्हित दीर्घ)banks->membnk_bnksz[slot/4];

	/* hack क्रम 128 dimm banks */
	अगर (size <= 128) अणु
		अगर (slot % 4 == 0) अणु
			size <<= 20;		/* size in bytes */
			वापस size >> PAGE_SHIFT;
		पूर्ण अन्यथा
			वापस 0;
	पूर्ण अन्यथा अणु
		size /= 4;
		size <<= 20;
		वापस size >> PAGE_SHIFT;
	पूर्ण
पूर्ण

अटल व्योम __init mlreset(व्योम)
अणु
	u64 region_mask;
	nasid_t nasid;

	master_nasid = get_nasid();

	/*
	 * Probe क्रम all CPUs - this creates the cpumask and sets up the
	 * mapping tables.  We need to करो this as early as possible.
	 */
#अगर_घोषित CONFIG_SMP
	cpu_node_probe();
#पूर्ण_अगर

	init_topology_matrix();
	dump_topology();

	region_mask = gen_region_mask();

	setup_replication_mask();

	/*
	 * Set all nodes' calias sizes to 8k
	 */
	क्रम_each_online_node(nasid) अणु
		/*
		 * Always have node 0 in the region mask, otherwise
		 * CALIAS accesses get exceptions since the hub
		 * thinks it is a node 0 address.
		 */
		REMOTE_HUB_S(nasid, PI_REGION_PRESENT, (region_mask | 1));
		REMOTE_HUB_S(nasid, PI_CALIAS_SIZE, PI_CALIAS_SIZE_0);

#अगर_घोषित LATER
		/*
		 * Set up all hubs to have a big winकरोw poपूर्णांकing at
		 * widget 0. Memory mode, widget 0, offset 0
		 */
		REMOTE_HUB_S(nasid, IIO_ITTE(SWIN0_BIGWIN),
			((HUB_PIO_MAP_TO_MEM << IIO_ITTE_IOSP_SHIFT) |
			(0 << IIO_ITTE_WIDGET_SHIFT)));
#पूर्ण_अगर
	पूर्ण
पूर्ण

अटल व्योम __init szmem(व्योम)
अणु
	अचिन्हित दीर्घ slot_psize, slot0sz = 0, nodebytes;	/* Hack to detect problem configs */
	पूर्णांक slot;
	nasid_t node;

	क्रम_each_online_node(node) अणु
		nodebytes = 0;
		क्रम (slot = 0; slot < MAX_MEM_SLOTS; slot++) अणु
			slot_psize = slot_psize_compute(node, slot);
			अगर (slot == 0)
				slot0sz = slot_psize;
			/*
			 * We need to refine the hack when we have replicated
			 * kernel text.
			 */
			nodebytes += (1LL << SLOT_SHIFT);

			अगर (!slot_psize)
				जारी;

			अगर ((nodebytes >> PAGE_SHIFT) * (माप(काष्ठा page)) >
						(slot0sz << PAGE_SHIFT)) अणु
				pr_info("Ignoring slot %d onwards on node %d\n",
								slot, node);
				slot = MAX_MEM_SLOTS;
				जारी;
			पूर्ण
			memblock_add_node(PFN_PHYS(slot_getbasepfn(node, slot)),
					  PFN_PHYS(slot_psize), node);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम __init node_mem_init(nasid_t node)
अणु
	अचिन्हित दीर्घ slot_firstpfn = slot_getbasepfn(node, 0);
	अचिन्हित दीर्घ slot_मुक्तpfn = node_getfirstमुक्त(node);
	अचिन्हित दीर्घ start_pfn, end_pfn;

	get_pfn_range_क्रम_nid(node, &start_pfn, &end_pfn);

	/*
	 * Allocate the node data काष्ठाures on the node first.
	 */
	__node_data[node] = __va(slot_मुक्तpfn << PAGE_SHIFT);
	स_रखो(__node_data[node], 0, PAGE_SIZE);

	NODE_DATA(node)->node_start_pfn = start_pfn;
	NODE_DATA(node)->node_spanned_pages = end_pfn - start_pfn;

	cpumask_clear(&hub_data(node)->h_cpus);

	slot_मुक्तpfn += PFN_UP(माप(काष्ठा pglist_data) +
			       माप(काष्ठा hub_data));

	memblock_reserve(slot_firstpfn << PAGE_SHIFT,
			 ((slot_मुक्तpfn - slot_firstpfn) << PAGE_SHIFT));
पूर्ण

/*
 * A node with nothing.	 We use it to aव्योम any special casing in
 * cpumask_of_node
 */
अटल काष्ठा node_data null_node = अणु
	.hub = अणु
		.h_cpus = CPU_MASK_NONE
	पूर्ण
पूर्ण;

/*
 * Currently, the पूर्णांकranode memory hole support assumes that each slot
 * contains at least 32 MBytes of memory. We assume all booपंचांगem data
 * fits on the first slot.
 */
व्योम __init prom_meminit(व्योम)
अणु
	nasid_t node;

	mlreset();
	szmem();
	max_low_pfn = PHYS_PFN(memblock_end_of_DRAM());

	क्रम (node = 0; node < MAX_NUMNODES; node++) अणु
		अगर (node_online(node)) अणु
			node_mem_init(node);
			जारी;
		पूर्ण
		__node_data[node] = &null_node;
	पूर्ण
पूर्ण

बाह्य व्योम setup_zero_pages(व्योम);

व्योम __init paging_init(व्योम)
अणु
	अचिन्हित दीर्घ zones_size[MAX_NR_ZONES] = अणु0, पूर्ण;

	pagetable_init();
	zones_size[ZONE_NORMAL] = max_low_pfn;
	मुक्त_area_init(zones_size);
पूर्ण

व्योम __init mem_init(व्योम)
अणु
	high_memory = (व्योम *) __va(get_num_physpages() << PAGE_SHIFT);
	memblock_मुक्त_all();
	setup_zero_pages();	/* This comes from node 0 */
पूर्ण
