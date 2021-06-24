<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * AMD NUMA support.
 * Discover the memory map and associated nodes.
 *
 * This version पढ़ोs it directly from the AMD northbridge.
 *
 * Copyright 2002,2003 Andi Kleen, SuSE Lअसल.
 */
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/माला.स>
#समावेश <linux/nodemask.h>
#समावेश <linux/memblock.h>

#समावेश <यंत्र/पन.स>
#समावेश <linux/pci_ids.h>
#समावेश <linux/acpi.h>
#समावेश <यंत्र/types.h>
#समावेश <यंत्र/mmzone.h>
#समावेश <यंत्र/proto.h>
#समावेश <यंत्र/e820/api.h>
#समावेश <यंत्र/pci-direct.h>
#समावेश <यंत्र/numa.h>
#समावेश <यंत्र/mpspec.h>
#समावेश <यंत्र/apic.h>
#समावेश <यंत्र/amd_nb.h>

अटल अचिन्हित अक्षर __initdata nodeids[8];

अटल __init पूर्णांक find_northbridge(व्योम)
अणु
	पूर्णांक num;

	क्रम (num = 0; num < 32; num++) अणु
		u32 header;

		header = पढ़ो_pci_config(0, num, 0, 0x00);
		अगर (header != (PCI_VENDOR_ID_AMD | (0x1100<<16)) &&
			header != (PCI_VENDOR_ID_AMD | (0x1200<<16)) &&
			header != (PCI_VENDOR_ID_AMD | (0x1300<<16)))
			जारी;

		header = पढ़ो_pci_config(0, num, 1, 0x00);
		अगर (header != (PCI_VENDOR_ID_AMD | (0x1101<<16)) &&
			header != (PCI_VENDOR_ID_AMD | (0x1201<<16)) &&
			header != (PCI_VENDOR_ID_AMD | (0x1301<<16)))
			जारी;
		वापस num;
	पूर्ण

	वापस -ENOENT;
पूर्ण

पूर्णांक __init amd_numa_init(व्योम)
अणु
	u64 start = PFN_PHYS(0);
	u64 end = PFN_PHYS(max_pfn);
	अचिन्हित numnodes;
	u64 prevbase;
	पूर्णांक i, j, nb;
	u32 nodeid, reg;
	अचिन्हित पूर्णांक bits, cores, apicid_base;

	अगर (!early_pci_allowed())
		वापस -EINVAL;

	nb = find_northbridge();
	अगर (nb < 0)
		वापस nb;

	pr_info("Scanning NUMA topology in Northbridge %d\n", nb);

	reg = पढ़ो_pci_config(0, nb, 0, 0x60);
	numnodes = ((reg >> 4) & 0xF) + 1;
	अगर (numnodes <= 1)
		वापस -ENOENT;

	pr_info("Number of physical nodes %d\n", numnodes);

	prevbase = 0;
	क्रम (i = 0; i < 8; i++) अणु
		u64 base, limit;

		base = पढ़ो_pci_config(0, nb, 1, 0x40 + i*8);
		limit = पढ़ो_pci_config(0, nb, 1, 0x44 + i*8);

		nodeids[i] = nodeid = limit & 7;
		अगर ((base & 3) == 0) अणु
			अगर (i < numnodes)
				pr_info("Skipping disabled node %d\n", i);
			जारी;
		पूर्ण
		अगर (nodeid >= numnodes) अणु
			pr_info("Ignoring excess node %d (%Lx:%Lx)\n", nodeid,
				base, limit);
			जारी;
		पूर्ण

		अगर (!limit) अणु
			pr_info("Skipping node entry %d (base %Lx)\n",
				i, base);
			जारी;
		पूर्ण
		अगर ((base >> 8) & 3 || (limit >> 8) & 3) अणु
			pr_err("Node %d using interleaving mode %Lx/%Lx\n",
			       nodeid, (base >> 8) & 3, (limit >> 8) & 3);
			वापस -EINVAL;
		पूर्ण
		अगर (node_isset(nodeid, numa_nodes_parsed)) अणु
			pr_info("Node %d already present, skipping\n",
				nodeid);
			जारी;
		पूर्ण

		limit >>= 16;
		limit++;
		limit <<= 24;

		अगर (limit > end)
			limit = end;
		अगर (limit <= base)
			जारी;

		base >>= 16;
		base <<= 24;

		अगर (base < start)
			base = start;
		अगर (limit > end)
			limit = end;
		अगर (limit == base) अणु
			pr_err("Empty node %d\n", nodeid);
			जारी;
		पूर्ण
		अगर (limit < base) अणु
			pr_err("Node %d bogus settings %Lx-%Lx.\n",
			       nodeid, base, limit);
			जारी;
		पूर्ण

		/* Could sort here, but pun क्रम now. Should not happen anyroads. */
		अगर (prevbase > base) अणु
			pr_err("Node map not sorted %Lx,%Lx\n",
			       prevbase, base);
			वापस -EINVAL;
		पूर्ण

		pr_info("Node %d MemBase %016Lx Limit %016Lx\n",
			nodeid, base, limit);

		prevbase = base;
		numa_add_memblk(nodeid, base, limit);
		node_set(nodeid, numa_nodes_parsed);
	पूर्ण

	अगर (!nodes_weight(numa_nodes_parsed))
		वापस -ENOENT;

	/*
	 * We seem to have valid NUMA configuration.  Map apicids to nodes
	 * using the coreid bits from early_identअगरy_cpu.
	 */
	bits = boot_cpu_data.x86_coreid_bits;
	cores = 1 << bits;
	apicid_base = 0;

	/*
	 * get boot-समय SMP configuration:
	 */
	early_get_smp_config();

	अगर (boot_cpu_physical_apicid > 0) अणु
		pr_info("BSP APIC ID: %02x\n", boot_cpu_physical_apicid);
		apicid_base = boot_cpu_physical_apicid;
	पूर्ण

	क्रम_each_node_mask(i, numa_nodes_parsed)
		क्रम (j = apicid_base; j < cores + apicid_base; j++)
			set_apicid_to_node((i << bits) + j, i);

	वापस 0;
पूर्ण
