<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  linux/arch/alpha/mm/numa.c
 *
 *  DISCONTIGMEM NUMA alpha support.
 *
 *  Copyright (C) 2001 Andrea Arcangeli <andrea@suse.de> SuSE
 */

#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/memblock.h>
#समावेश <linux/swap.h>
#समावेश <linux/initrd.h>
#समावेश <linux/pfn.h>
#समावेश <linux/module.h>

#समावेश <यंत्र/hwrpb.h>
#समावेश <यंत्र/sections.h>

pg_data_t node_data[MAX_NUMNODES];
EXPORT_SYMBOL(node_data);

#अघोषित DEBUG_DISCONTIG
#अगर_घोषित DEBUG_DISCONTIG
#घोषणा DBGDCONT(args...) prपूर्णांकk(args)
#अन्यथा
#घोषणा DBGDCONT(args...)
#पूर्ण_अगर

#घोषणा क्रम_each_mem_cluster(memdesc, _cluster, i)		\
	क्रम ((_cluster) = (memdesc)->cluster, (i) = 0;		\
	     (i) < (memdesc)->numclusters; (i)++, (_cluster)++)

अटल व्योम __init show_mem_layout(व्योम)
अणु
	काष्ठा memclust_काष्ठा * cluster;
	काष्ठा memdesc_काष्ठा * memdesc;
	पूर्णांक i;

	/* Find मुक्त clusters, and init and मुक्त the booपंचांगem accordingly.  */
	memdesc = (काष्ठा memdesc_काष्ठा *)
	  (hwrpb->mddt_offset + (अचिन्हित दीर्घ) hwrpb);

	prपूर्णांकk("Raw memory layout:\n");
	क्रम_each_mem_cluster(memdesc, cluster, i) अणु
		prपूर्णांकk(" memcluster %2d, usage %1lx, start %8lu, end %8lu\n",
		       i, cluster->usage, cluster->start_pfn,
		       cluster->start_pfn + cluster->numpages);
	पूर्ण
पूर्ण

अटल व्योम __init
setup_memory_node(पूर्णांक nid, व्योम *kernel_end)
अणु
	बाह्य अचिन्हित दीर्घ mem_size_limit;
	काष्ठा memclust_काष्ठा * cluster;
	काष्ठा memdesc_काष्ठा * memdesc;
	अचिन्हित दीर्घ start_kernel_pfn, end_kernel_pfn;
	अचिन्हित दीर्घ start, end;
	अचिन्हित दीर्घ node_pfn_start, node_pfn_end;
	अचिन्हित दीर्घ node_min_pfn, node_max_pfn;
	पूर्णांक i;
	पूर्णांक show_init = 0;

	/* Find the bounds of current node */
	node_pfn_start = (node_mem_start(nid)) >> PAGE_SHIFT;
	node_pfn_end = node_pfn_start + (node_mem_size(nid) >> PAGE_SHIFT);
	
	/* Find मुक्त clusters, and init and मुक्त the booपंचांगem accordingly.  */
	memdesc = (काष्ठा memdesc_काष्ठा *)
	  (hwrpb->mddt_offset + (अचिन्हित दीर्घ) hwrpb);

	/* find the bounds of this node (node_min_pfn/node_max_pfn) */
	node_min_pfn = ~0UL;
	node_max_pfn = 0UL;
	क्रम_each_mem_cluster(memdesc, cluster, i) अणु
		/* Bit 0 is console/PALcode reserved.  Bit 1 is
		   non-अस्थिर memory -- we might want to mark
		   this क्रम later.  */
		अगर (cluster->usage & 3)
			जारी;

		start = cluster->start_pfn;
		end = start + cluster->numpages;

		अगर (start >= node_pfn_end || end <= node_pfn_start)
			जारी;

		अगर (!show_init) अणु
			show_init = 1;
			prपूर्णांकk("Initializing bootmem allocator on Node ID %d\n", nid);
		पूर्ण
		prपूर्णांकk(" memcluster %2d, usage %1lx, start %8lu, end %8lu\n",
		       i, cluster->usage, cluster->start_pfn,
		       cluster->start_pfn + cluster->numpages);

		अगर (start < node_pfn_start)
			start = node_pfn_start;
		अगर (end > node_pfn_end)
			end = node_pfn_end;

		अगर (start < node_min_pfn)
			node_min_pfn = start;
		अगर (end > node_max_pfn)
			node_max_pfn = end;
	पूर्ण

	अगर (mem_size_limit && node_max_pfn > mem_size_limit) अणु
		अटल पूर्णांक msg_shown = 0;
		अगर (!msg_shown) अणु
			msg_shown = 1;
			prपूर्णांकk("setup: forcing memory size to %ldK (from %ldK).\n",
			       mem_size_limit << (PAGE_SHIFT - 10),
			       node_max_pfn    << (PAGE_SHIFT - 10));
		पूर्ण
		node_max_pfn = mem_size_limit;
	पूर्ण

	अगर (node_min_pfn >= node_max_pfn)
		वापस;

	/* Update global अणुmin,maxपूर्ण_low_pfn from node inक्रमmation. */
	अगर (node_min_pfn < min_low_pfn)
		min_low_pfn = node_min_pfn;
	अगर (node_max_pfn > max_low_pfn)
		max_pfn = max_low_pfn = node_max_pfn;

#अगर 0 /* we'll try this one again in a little जबतक */
	/* Cute trick to make sure our local node data is on local memory */
	node_data[nid] = (pg_data_t *)(__va(node_min_pfn << PAGE_SHIFT));
#पूर्ण_अगर
	prपूर्णांकk(" Detected node memory:   start %8lu, end %8lu\n",
	       node_min_pfn, node_max_pfn);

	DBGDCONT(" DISCONTIG: node_data[%d]   is at 0x%p\n", nid, NODE_DATA(nid));

	/* Find the bounds of kernel memory.  */
	start_kernel_pfn = PFN_DOWN(KERNEL_START_PHYS);
	end_kernel_pfn = PFN_UP(virt_to_phys(kernel_end));

	अगर (!nid && (node_max_pfn < end_kernel_pfn || node_min_pfn > start_kernel_pfn))
		panic("kernel loaded out of ram");

	memblock_add_node(PFN_PHYS(node_min_pfn),
			  (node_max_pfn - node_min_pfn) << PAGE_SHIFT, nid);

	/* Zone start phys-addr must be 2^(MAX_ORDER-1) aligned.
	   Note that we round this करोwn, not up - node memory
	   has much larger alignment than 8Mb, so it's safe. */
	node_min_pfn &= ~((1UL << (MAX_ORDER-1))-1);

	NODE_DATA(nid)->node_start_pfn = node_min_pfn;
	NODE_DATA(nid)->node_present_pages = node_max_pfn - node_min_pfn;

	node_set_online(nid);
पूर्ण

व्योम __init
setup_memory(व्योम *kernel_end)
अणु
	अचिन्हित दीर्घ kernel_size;
	पूर्णांक nid;

	show_mem_layout();

	nodes_clear(node_online_map);

	min_low_pfn = ~0UL;
	max_low_pfn = 0UL;
	क्रम (nid = 0; nid < MAX_NUMNODES; nid++)
		setup_memory_node(nid, kernel_end);

	kernel_size = virt_to_phys(kernel_end) - KERNEL_START_PHYS;
	memblock_reserve(KERNEL_START_PHYS, kernel_size);

#अगर_घोषित CONFIG_BLK_DEV_INITRD
	initrd_start = INITRD_START;
	अगर (initrd_start) अणु
		बाह्य व्योम *move_initrd(अचिन्हित दीर्घ);

		initrd_end = initrd_start+INITRD_SIZE;
		prपूर्णांकk("Initial ramdisk at: 0x%p (%lu bytes)\n",
		       (व्योम *) initrd_start, INITRD_SIZE);

		अगर ((व्योम *)initrd_end > phys_to_virt(PFN_PHYS(max_low_pfn))) अणु
			अगर (!move_initrd(PFN_PHYS(max_low_pfn)))
				prपूर्णांकk("initrd extends beyond end of memory "
				       "(0x%08lx > 0x%p)\ndisabling initrd\n",
				       initrd_end,
				       phys_to_virt(PFN_PHYS(max_low_pfn)));
		पूर्ण अन्यथा अणु
			nid = kvaddr_to_nid(initrd_start);
			memblock_reserve(virt_to_phys((व्योम *)initrd_start),
					 INITRD_SIZE);
		पूर्ण
	पूर्ण
#पूर्ण_अगर /* CONFIG_BLK_DEV_INITRD */
पूर्ण

व्योम __init paging_init(व्योम)
अणु
	अचिन्हित दीर्घ   max_zone_pfn[MAX_NR_ZONES] = अणु0, पूर्ण;
	अचिन्हित दीर्घ	dma_local_pfn;

	/*
	 * The old global MAX_DMA_ADDRESS per-arch API करोesn't fit
	 * in the NUMA model, क्रम now we convert it to a pfn and
	 * we पूर्णांकerpret this pfn as a local per-node inक्रमmation.
	 * This issue isn't very important since none of these machines
	 * have legacy ISA slots anyways.
	 */
	dma_local_pfn = virt_to_phys((अक्षर *)MAX_DMA_ADDRESS) >> PAGE_SHIFT;

	max_zone_pfn[ZONE_DMA] = dma_local_pfn;
	max_zone_pfn[ZONE_NORMAL] = max_pfn;

	मुक्त_area_init(max_zone_pfn);

	/* Initialize the kernel's ZERO_PGE. */
	स_रखो((व्योम *)ZERO_PGE, 0, PAGE_SIZE);
पूर्ण
