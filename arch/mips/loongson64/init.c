<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2009 Lemote Inc.
 * Author: Wu Zhangjin, wuzhangjin@gmail.com
 */

#समावेश <linux/irqchip.h>
#समावेश <linux/logic_pपन.स>
#समावेश <linux/memblock.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <यंत्र/bootinfo.h>
#समावेश <यंत्र/traps.h>
#समावेश <यंत्र/smp-ops.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/fw/fw.h>

#समावेश <loongson.h>
#समावेश <boot_param.h>

#घोषणा NODE_ID_OFFSET_ADDR	((व्योम __iomem *)TO_UNCAC(0x1001041c))

u32 node_id_offset;

अटल व्योम __init mips_nmi_setup(व्योम)
अणु
	व्योम *base;

	base = (व्योम *)(CAC_BASE + 0x380);
	स_नकल(base, except_vec_nmi, 0x80);
	flush_icache_range((अचिन्हित दीर्घ)base, (अचिन्हित दीर्घ)base + 0x80);
पूर्ण

व्योम ls7a_early_config(व्योम)
अणु
	node_id_offset = ((पढ़ोl(NODE_ID_OFFSET_ADDR) >> 8) & 0x1f) + 36;
पूर्ण

व्योम rs780e_early_config(व्योम)
अणु
	node_id_offset = 37;
पूर्ण

व्योम भव_early_config(व्योम)
अणु
	node_id_offset = 44;
पूर्ण

व्योम __init szmem(अचिन्हित पूर्णांक node)
अणु
	u32 i, mem_type;
	अटल अचिन्हित दीर्घ num_physpages;
	u64 node_id, node_psize, start_pfn, end_pfn, mem_start, mem_size;

	/* Otherwise come from DTB */
	अगर (loongson_sysconf.fw_पूर्णांकerface != LOONGSON_LEFI)
		वापस;

	/* Parse memory inक्रमmation and activate */
	क्रम (i = 0; i < loongson_memmap->nr_map; i++) अणु
		node_id = loongson_memmap->map[i].node_id;
		अगर (node_id != node)
			जारी;

		mem_type = loongson_memmap->map[i].mem_type;
		mem_size = loongson_memmap->map[i].mem_size;
		mem_start = loongson_memmap->map[i].mem_start;

		चयन (mem_type) अणु
		हाल SYSTEM_RAM_LOW:
		हाल SYSTEM_RAM_HIGH:
			start_pfn = ((node_id << 44) + mem_start) >> PAGE_SHIFT;
			node_psize = (mem_size << 20) >> PAGE_SHIFT;
			end_pfn  = start_pfn + node_psize;
			num_physpages += node_psize;
			pr_info("Node%d: mem_type:%d, mem_start:0x%llx, mem_size:0x%llx MB\n",
				(u32)node_id, mem_type, mem_start, mem_size);
			pr_info("       start_pfn:0x%llx, end_pfn:0x%llx, num_physpages:0x%lx\n",
				start_pfn, end_pfn, num_physpages);
			memblock_add_node(PFN_PHYS(start_pfn), PFN_PHYS(node_psize), node);
			अवरोध;
		हाल SYSTEM_RAM_RESERVED:
			pr_info("Node%d: mem_type:%d, mem_start:0x%llx, mem_size:0x%llx MB\n",
				(u32)node_id, mem_type, mem_start, mem_size);
			memblock_reserve(((node_id << 44) + mem_start), mem_size << 20);
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

#अगर_अघोषित CONFIG_NUMA
अटल व्योम __init prom_init_memory(व्योम)
अणु
	szmem(0);
पूर्ण
#पूर्ण_अगर

व्योम __init prom_init(व्योम)
अणु
	fw_init_cmdline();

	अगर (fw_arg2 == 0 || (fdt_magic(fw_arg2) == FDT_MAGIC)) अणु
		loongson_sysconf.fw_पूर्णांकerface = LOONGSON_DTB;
		prom_dtb_init_env();
	पूर्ण अन्यथा अणु
		loongson_sysconf.fw_पूर्णांकerface = LOONGSON_LEFI;
		prom_lefi_init_env();
	पूर्ण

	/* init base address of io space */
	set_io_port_base(PCI_IOBASE);

	अगर (loongson_sysconf.early_config)
		loongson_sysconf.early_config();

#अगर_घोषित CONFIG_NUMA
	prom_init_numa_memory();
#अन्यथा
	prom_init_memory();
#पूर्ण_अगर

	/* Hardcode to CPU UART 0 */
	अगर ((पढ़ो_c0_prid() & PRID_IMP_MASK) == PRID_IMP_LOONGSON_64R)
		setup_8250_early_prपूर्णांकk_port(TO_UNCAC(LOONGSON_REG_BASE), 0, 1024);
	अन्यथा
		setup_8250_early_prपूर्णांकk_port(TO_UNCAC(LOONGSON_REG_BASE + 0x1e0), 0, 1024);

	रेजिस्टर_smp_ops(&loongson3_smp_ops);
	board_nmi_handler_setup = mips_nmi_setup;
पूर्ण

अटल पूर्णांक __init add_legacy_isa_io(काष्ठा fwnode_handle *fwnode, resource_माप_प्रकार hw_start,
				    resource_माप_प्रकार size)
अणु
	पूर्णांक ret = 0;
	काष्ठा logic_pio_hwaddr *range;
	अचिन्हित दीर्घ vaddr;

	range = kzalloc(माप(*range), GFP_ATOMIC);
	अगर (!range)
		वापस -ENOMEM;

	range->fwnode = fwnode;
	range->size = size = round_up(size, PAGE_SIZE);
	range->hw_start = hw_start;
	range->flags = LOGIC_PIO_CPU_MMIO;

	ret = logic_pio_रेजिस्टर_range(range);
	अगर (ret) अणु
		kमुक्त(range);
		वापस ret;
	पूर्ण

	/* Legacy ISA must placed at the start of PCI_IOBASE */
	अगर (range->io_start != 0) अणु
		logic_pio_unरेजिस्टर_range(range);
		kमुक्त(range);
		वापस -EINVAL;
	पूर्ण

	vaddr = PCI_IOBASE + range->io_start;

	ioremap_page_range(vaddr, vaddr + size, hw_start, pgprot_device(PAGE_KERNEL));

	वापस 0;
पूर्ण

अटल __init व्योम reserve_pio_range(व्योम)
अणु
	काष्ठा device_node *np;

	क्रम_each_node_by_name(np, "isa") अणु
		काष्ठा of_range range;
		काष्ठा of_range_parser parser;

		pr_info("ISA Bridge: %pOF\n", np);

		अगर (of_range_parser_init(&parser, np)) अणु
			pr_info("Failed to parse resources.\n");
			अवरोध;
		पूर्ण

		क्रम_each_of_range(&parser, &range) अणु
			चयन (range.flags & IORESOURCE_TYPE_BITS) अणु
			हाल IORESOURCE_IO:
				pr_info(" IO 0x%016llx..0x%016llx  ->  0x%016llx\n",
					range.cpu_addr,
					range.cpu_addr + range.size - 1,
					range.bus_addr);
				अगर (add_legacy_isa_io(&np->fwnode, range.cpu_addr, range.size))
					pr_warn("Failed to reserve legacy IO in Logic PIO\n");
				अवरोध;
			हाल IORESOURCE_MEM:
				pr_info(" MEM 0x%016llx..0x%016llx  ->  0x%016llx\n",
					range.cpu_addr,
					range.cpu_addr + range.size - 1,
					range.bus_addr);
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

व्योम __init arch_init_irq(व्योम)
अणु
	reserve_pio_range();
	irqchip_init();
पूर्ण
