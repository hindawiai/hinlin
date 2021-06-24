<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * ACPI 5.1 based NUMA setup क्रम ARM64
 * Lots of code was borrowed from arch/x86/mm/srat.c
 *
 * Copyright 2004 Andi Kleen, SuSE Lअसल.
 * Copyright (C) 2013-2016, Linaro Ltd.
 *		Author: Hanjun Guo <hanjun.guo@linaro.org>
 *
 * Reads the ACPI SRAT table to figure out what memory beदीर्घs to which CPUs.
 *
 * Called from acpi_numa_init जबतक पढ़ोing the SRAT and SLIT tables.
 * Assumes all memory regions beदीर्घing to a single proximity करोमुख्य
 * are in one chunk. Holes between them will be included in the node.
 */

#घोषणा pr_fmt(fmt) "ACPI: NUMA: " fmt

#समावेश <linux/acpi.h>
#समावेश <linux/biपंचांगap.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/memblock.h>
#समावेश <linux/mmzone.h>
#समावेश <linux/module.h>
#समावेश <linux/topology.h>

#समावेश <यंत्र/numa.h>

अटल पूर्णांक acpi_early_node_map[NR_CPUS] __initdata = अणु NUMA_NO_NODE पूर्ण;

पूर्णांक __init acpi_numa_get_nid(अचिन्हित पूर्णांक cpu)
अणु
	वापस acpi_early_node_map[cpu];
पूर्ण

अटल अंतरभूत पूर्णांक get_cpu_क्रम_acpi_id(u32 uid)
अणु
	पूर्णांक cpu;

	क्रम (cpu = 0; cpu < nr_cpu_ids; cpu++)
		अगर (uid == get_acpi_id_क्रम_cpu(cpu))
			वापस cpu;

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक __init acpi_parse_gicc_pxm(जोड़ acpi_subtable_headers *header,
				      स्थिर अचिन्हित दीर्घ end)
अणु
	काष्ठा acpi_srat_gicc_affinity *pa;
	पूर्णांक cpu, pxm, node;

	अगर (srat_disabled())
		वापस -EINVAL;

	pa = (काष्ठा acpi_srat_gicc_affinity *)header;
	अगर (!pa)
		वापस -EINVAL;

	अगर (!(pa->flags & ACPI_SRAT_GICC_ENABLED))
		वापस 0;

	pxm = pa->proximity_करोमुख्य;
	node = pxm_to_node(pxm);

	/*
	 * If we can't map the UID to a logical cpu this
	 * means that the UID is not part of possible cpus
	 * so we करो not need a NUMA mapping क्रम it, skip
	 * the SRAT entry and keep parsing.
	 */
	cpu = get_cpu_क्रम_acpi_id(pa->acpi_processor_uid);
	अगर (cpu < 0)
		वापस 0;

	acpi_early_node_map[cpu] = node;
	pr_info("SRAT: PXM %d -> MPIDR 0x%llx -> Node %d\n", pxm,
		cpu_logical_map(cpu), node);

	वापस 0;
पूर्ण

व्योम __init acpi_map_cpus_to_nodes(व्योम)
अणु
	acpi_table_parse_entries(ACPI_SIG_SRAT, माप(काष्ठा acpi_table_srat),
					    ACPI_SRAT_TYPE_GICC_AFFINITY,
					    acpi_parse_gicc_pxm, 0);
पूर्ण

/* Callback क्रम Proximity Doमुख्य -> ACPI processor UID mapping */
व्योम __init acpi_numa_gicc_affinity_init(काष्ठा acpi_srat_gicc_affinity *pa)
अणु
	पूर्णांक pxm, node;

	अगर (srat_disabled())
		वापस;

	अगर (pa->header.length < माप(काष्ठा acpi_srat_gicc_affinity)) अणु
		pr_err("SRAT: Invalid SRAT header length: %d\n",
			pa->header.length);
		bad_srat();
		वापस;
	पूर्ण

	अगर (!(pa->flags & ACPI_SRAT_GICC_ENABLED))
		वापस;

	pxm = pa->proximity_करोमुख्य;
	node = acpi_map_pxm_to_node(pxm);

	अगर (node == NUMA_NO_NODE || node >= MAX_NUMNODES) अणु
		pr_err("SRAT: Too many proximity domains %d\n", pxm);
		bad_srat();
		वापस;
	पूर्ण

	node_set(node, numa_nodes_parsed);
पूर्ण

