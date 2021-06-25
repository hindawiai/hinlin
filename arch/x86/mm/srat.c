<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * ACPI 3.0 based NUMA setup
 * Copyright 2004 Andi Kleen, SuSE Lअसल.
 *
 * Reads the ACPI SRAT table to figure out what memory beदीर्घs to which CPUs.
 *
 * Called from acpi_numa_init जबतक पढ़ोing the SRAT and SLIT tables.
 * Assumes all memory regions beदीर्घing to a single proximity करोमुख्य
 * are in one chunk. Holes between them will be included in the node.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/acpi.h>
#समावेश <linux/mmzone.h>
#समावेश <linux/biपंचांगap.h>
#समावेश <linux/init.h>
#समावेश <linux/topology.h>
#समावेश <linux/mm.h>
#समावेश <यंत्र/proto.h>
#समावेश <यंत्र/numa.h>
#समावेश <यंत्र/e820/api.h>
#समावेश <यंत्र/apic.h>
#समावेश <यंत्र/uv/uv.h>

/* Callback क्रम Proximity Doमुख्य -> x2APIC mapping */
व्योम __init
acpi_numa_x2apic_affinity_init(काष्ठा acpi_srat_x2apic_cpu_affinity *pa)
अणु
	पूर्णांक pxm, node;
	पूर्णांक apic_id;

	अगर (srat_disabled())
		वापस;
	अगर (pa->header.length < माप(काष्ठा acpi_srat_x2apic_cpu_affinity)) अणु
		bad_srat();
		वापस;
	पूर्ण
	अगर ((pa->flags & ACPI_SRAT_CPU_ENABLED) == 0)
		वापस;
	pxm = pa->proximity_करोमुख्य;
	apic_id = pa->apic_id;
	अगर (!apic->apic_id_valid(apic_id)) अणु
		prपूर्णांकk(KERN_INFO "SRAT: PXM %u -> X2APIC 0x%04x ignored\n",
			 pxm, apic_id);
		वापस;
	पूर्ण
	node = acpi_map_pxm_to_node(pxm);
	अगर (node < 0) अणु
		prपूर्णांकk(KERN_ERR "SRAT: Too many proximity domains %x\n", pxm);
		bad_srat();
		वापस;
	पूर्ण

	अगर (apic_id >= MAX_LOCAL_APIC) अणु
		prपूर्णांकk(KERN_INFO "SRAT: PXM %u -> APIC 0x%04x -> Node %u skipped apicid that is too big\n", pxm, apic_id, node);
		वापस;
	पूर्ण
	set_apicid_to_node(apic_id, node);
	node_set(node, numa_nodes_parsed);
	prपूर्णांकk(KERN_INFO "SRAT: PXM %u -> APIC 0x%04x -> Node %u\n",
	       pxm, apic_id, node);
पूर्ण

/* Callback क्रम Proximity Doमुख्य -> LAPIC mapping */
व्योम __init
acpi_numa_processor_affinity_init(काष्ठा acpi_srat_cpu_affinity *pa)
अणु
	पूर्णांक pxm, node;
	पूर्णांक apic_id;

	अगर (srat_disabled())
		वापस;
	अगर (pa->header.length != माप(काष्ठा acpi_srat_cpu_affinity)) अणु
		bad_srat();
		वापस;
	पूर्ण
	अगर ((pa->flags & ACPI_SRAT_CPU_ENABLED) == 0)
		वापस;
	pxm = pa->proximity_करोमुख्य_lo;
	अगर (acpi_srat_revision >= 2)
		pxm |= *((अचिन्हित पूर्णांक*)pa->proximity_करोमुख्य_hi) << 8;
	node = acpi_map_pxm_to_node(pxm);
	अगर (node < 0) अणु
		prपूर्णांकk(KERN_ERR "SRAT: Too many proximity domains %x\n", pxm);
		bad_srat();
		वापस;
	पूर्ण

	अगर (get_uv_प्रणाली_type() >= UV_X2APIC)
		apic_id = (pa->apic_id << 8) | pa->local_sapic_eid;
	अन्यथा
		apic_id = pa->apic_id;

	अगर (apic_id >= MAX_LOCAL_APIC) अणु
		prपूर्णांकk(KERN_INFO "SRAT: PXM %u -> APIC 0x%02x -> Node %u skipped apicid that is too big\n", pxm, apic_id, node);
		वापस;
	पूर्ण

	set_apicid_to_node(apic_id, node);
	node_set(node, numa_nodes_parsed);
	prपूर्णांकk(KERN_INFO "SRAT: PXM %u -> APIC 0x%02x -> Node %u\n",
	       pxm, apic_id, node);
पूर्ण

पूर्णांक __init x86_acpi_numa_init(व्योम)
अणु
	पूर्णांक ret;

	ret = acpi_numa_init();
	अगर (ret < 0)
		वापस ret;
	वापस srat_disabled() ? -EINVAL : 0;
पूर्ण
