<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  acpi.c - Architecture-Specअगरic Low-Level ACPI Support
 *
 *  Copyright (C) 1999 VA Linux Systems
 *  Copyright (C) 1999,2000 Walt Drummond <drummond@valinux.com>
 *  Copyright (C) 2000, 2002-2003 Hewlett-Packard Co.
 *	David Mosberger-Tang <davidm@hpl.hp.com>
 *  Copyright (C) 2000 Intel Corp.
 *  Copyright (C) 2000,2001 J.I. Lee <jung-ik.lee@पूर्णांकel.com>
 *  Copyright (C) 2001 Paul Diefenbaugh <paul.s.diefenbaugh@पूर्णांकel.com>
 *  Copyright (C) 2001 Jenna Hall <jenna.s.hall@पूर्णांकel.com>
 *  Copyright (C) 2001 Takayoshi Kochi <t-kochi@bq.jp.nec.com>
 *  Copyright (C) 2002 Erich Focht <efocht@ess.nec.de>
 *  Copyright (C) 2004 Ashok Raj <ashok.raj@पूर्णांकel.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/smp.h>
#समावेश <linux/माला.स>
#समावेश <linux/types.h>
#समावेश <linux/irq.h>
#समावेश <linux/acpi.h>
#समावेश <linux/efi.h>
#समावेश <linux/mmzone.h>
#समावेश <linux/nodemask.h>
#समावेश <linux/slab.h>
#समावेश <acpi/processor.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/iosapic.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/numa.h>
#समावेश <यंत्र/sal.h>
#समावेश <यंत्र/cyclone.h>

#घोषणा PREFIX			"ACPI: "

पूर्णांक acpi_lapic;
अचिन्हित पूर्णांक acpi_cpei_override;
अचिन्हित पूर्णांक acpi_cpei_phys_cpuid;

#घोषणा ACPI_MAX_PLATFORM_INTERRUPTS	256

/* Array to record platक्रमm पूर्णांकerrupt vectors क्रम generic पूर्णांकerrupt routing. */
पूर्णांक platक्रमm_पूर्णांकr_list[ACPI_MAX_PLATFORM_INTERRUPTS] = अणु
	[0 ... ACPI_MAX_PLATFORM_INTERRUPTS - 1] = -1
पूर्ण;

क्रमागत acpi_irq_model_id acpi_irq_model = ACPI_IRQ_MODEL_IOSAPIC;

/*
 * Interrupt routing API क्रम device drivers.  Provides पूर्णांकerrupt vector क्रम
 * a generic platक्रमm event.  Currently only CPEI is implemented.
 */
पूर्णांक acpi_request_vector(u32 पूर्णांक_type)
अणु
	पूर्णांक vector = -1;

	अगर (पूर्णांक_type < ACPI_MAX_PLATFORM_INTERRUPTS) अणु
		/* corrected platक्रमm error पूर्णांकerrupt */
		vector = platक्रमm_पूर्णांकr_list[पूर्णांक_type];
	पूर्ण अन्यथा
		prपूर्णांकk(KERN_ERR
		       "acpi_request_vector(): invalid interrupt type\n");
	वापस vector;
पूर्ण

व्योम __init __iomem *__acpi_map_table(अचिन्हित दीर्घ phys, अचिन्हित दीर्घ size)
अणु
	वापस __va(phys);
पूर्ण

व्योम __init __acpi_unmap_table(व्योम __iomem *map, अचिन्हित दीर्घ size)
अणु
पूर्ण

/* --------------------------------------------------------------------------
                            Boot-समय Table Parsing
   -------------------------------------------------------------------------- */

अटल पूर्णांक available_cpus __initdata;
काष्ठा acpi_table_madt *acpi_madt __initdata;
अटल u8 has_8259;

अटल पूर्णांक __init
acpi_parse_lapic_addr_ovr(जोड़ acpi_subtable_headers * header,
			  स्थिर अचिन्हित दीर्घ end)
अणु
	काष्ठा acpi_madt_local_apic_override *lapic;

	lapic = (काष्ठा acpi_madt_local_apic_override *)header;

	अगर (BAD_MADT_ENTRY(lapic, end))
		वापस -EINVAL;

	अगर (lapic->address) अणु
		iounmap(ipi_base_addr);
		ipi_base_addr = ioremap(lapic->address, 0);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक __init
acpi_parse_lsapic(जोड़ acpi_subtable_headers *header, स्थिर अचिन्हित दीर्घ end)
अणु
	काष्ठा acpi_madt_local_sapic *lsapic;

	lsapic = (काष्ठा acpi_madt_local_sapic *)header;

	/*Skip BAD_MADT_ENTRY check, as lsapic size could vary */

	अगर (lsapic->lapic_flags & ACPI_MADT_ENABLED) अणु
#अगर_घोषित CONFIG_SMP
		smp_boot_data.cpu_phys_id[available_cpus] =
		    (lsapic->id << 8) | lsapic->eid;
#पूर्ण_अगर
		++available_cpus;
	पूर्ण

	total_cpus++;
	वापस 0;
पूर्ण

अटल पूर्णांक __init
acpi_parse_lapic_nmi(जोड़ acpi_subtable_headers * header, स्थिर अचिन्हित दीर्घ end)
अणु
	काष्ठा acpi_madt_local_apic_nmi *lacpi_nmi;

	lacpi_nmi = (काष्ठा acpi_madt_local_apic_nmi *)header;

	अगर (BAD_MADT_ENTRY(lacpi_nmi, end))
		वापस -EINVAL;

	/* TBD: Support lapic_nmi entries */
	वापस 0;
पूर्ण

अटल पूर्णांक __init
acpi_parse_iosapic(जोड़ acpi_subtable_headers * header, स्थिर अचिन्हित दीर्घ end)
अणु
	काष्ठा acpi_madt_io_sapic *iosapic;

	iosapic = (काष्ठा acpi_madt_io_sapic *)header;

	अगर (BAD_MADT_ENTRY(iosapic, end))
		वापस -EINVAL;

	वापस iosapic_init(iosapic->address, iosapic->global_irq_base);
पूर्ण

अटल अचिन्हित पूर्णांक __initdata acpi_madt_rev;

अटल पूर्णांक __init
acpi_parse_plat_पूर्णांक_src(जोड़ acpi_subtable_headers * header,
			स्थिर अचिन्हित दीर्घ end)
अणु
	काष्ठा acpi_madt_पूर्णांकerrupt_source *plपूर्णांकsrc;
	पूर्णांक vector;

	plपूर्णांकsrc = (काष्ठा acpi_madt_पूर्णांकerrupt_source *)header;

	अगर (BAD_MADT_ENTRY(plपूर्णांकsrc, end))
		वापस -EINVAL;

	/*
	 * Get vector assignment क्रम this पूर्णांकerrupt, set attributes,
	 * and program the IOSAPIC routing table.
	 */
	vector = iosapic_रेजिस्टर_platक्रमm_पूर्णांकr(plपूर्णांकsrc->type,
						plपूर्णांकsrc->global_irq,
						plपूर्णांकsrc->io_sapic_vector,
						plपूर्णांकsrc->eid,
						plपूर्णांकsrc->id,
						((plपूर्णांकsrc->पूर्णांकi_flags & ACPI_MADT_POLARITY_MASK) ==
						 ACPI_MADT_POLARITY_ACTIVE_HIGH) ?
						IOSAPIC_POL_HIGH : IOSAPIC_POL_LOW,
						((plपूर्णांकsrc->पूर्णांकi_flags & ACPI_MADT_TRIGGER_MASK) ==
						 ACPI_MADT_TRIGGER_EDGE) ?
						IOSAPIC_EDGE : IOSAPIC_LEVEL);

	platक्रमm_पूर्णांकr_list[plपूर्णांकsrc->type] = vector;
	अगर (acpi_madt_rev > 1) अणु
		acpi_cpei_override = plपूर्णांकsrc->flags & ACPI_MADT_CPEI_OVERRIDE;
	पूर्ण

	/*
	 * Save the physical id, so we can check when its being हटाओd
	 */
	acpi_cpei_phys_cpuid = ((plपूर्णांकsrc->id << 8) | (plपूर्णांकsrc->eid)) & 0xffff;

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_HOTPLUG_CPU
अचिन्हित पूर्णांक can_cpei_retarget(व्योम)
अणु
	बाह्य पूर्णांक cpe_vector;
	बाह्य अचिन्हित पूर्णांक क्रमce_cpei_retarget;

	/*
	 * Only अगर CPEI is supported and the override flag
	 * is present, otherwise वापस that its re-targettable
	 * अगर we are in polling mode.
	 */
	अगर (cpe_vector > 0) अणु
		अगर (acpi_cpei_override || क्रमce_cpei_retarget)
			वापस 1;
		अन्यथा
			वापस 0;
	पूर्ण
	वापस 1;
पूर्ण

अचिन्हित पूर्णांक is_cpu_cpei_target(अचिन्हित पूर्णांक cpu)
अणु
	अचिन्हित पूर्णांक logical_id;

	logical_id = cpu_logical_id(acpi_cpei_phys_cpuid);

	अगर (logical_id == cpu)
		वापस 1;
	अन्यथा
		वापस 0;
पूर्ण

व्योम set_cpei_target_cpu(अचिन्हित पूर्णांक cpu)
अणु
	acpi_cpei_phys_cpuid = cpu_physical_id(cpu);
पूर्ण
#पूर्ण_अगर

अचिन्हित पूर्णांक get_cpei_target_cpu(व्योम)
अणु
	वापस acpi_cpei_phys_cpuid;
पूर्ण

अटल पूर्णांक __init
acpi_parse_पूर्णांक_src_ovr(जोड़ acpi_subtable_headers * header,
		       स्थिर अचिन्हित दीर्घ end)
अणु
	काष्ठा acpi_madt_पूर्णांकerrupt_override *p;

	p = (काष्ठा acpi_madt_पूर्णांकerrupt_override *)header;

	अगर (BAD_MADT_ENTRY(p, end))
		वापस -EINVAL;

	iosapic_override_isa_irq(p->source_irq, p->global_irq,
				 ((p->पूर्णांकi_flags & ACPI_MADT_POLARITY_MASK) ==
				  ACPI_MADT_POLARITY_ACTIVE_LOW) ?
				 IOSAPIC_POL_LOW : IOSAPIC_POL_HIGH,
				 ((p->पूर्णांकi_flags & ACPI_MADT_TRIGGER_MASK) ==
				 ACPI_MADT_TRIGGER_LEVEL) ?
				 IOSAPIC_LEVEL : IOSAPIC_EDGE);
	वापस 0;
पूर्ण

अटल पूर्णांक __init
acpi_parse_nmi_src(जोड़ acpi_subtable_headers * header, स्थिर अचिन्हित दीर्घ end)
अणु
	काष्ठा acpi_madt_nmi_source *nmi_src;

	nmi_src = (काष्ठा acpi_madt_nmi_source *)header;

	अगर (BAD_MADT_ENTRY(nmi_src, end))
		वापस -EINVAL;

	/* TBD: Support nimsrc entries */
	वापस 0;
पूर्ण

अटल व्योम __init acpi_madt_oem_check(अक्षर *oem_id, अक्षर *oem_table_id)
अणु
	अगर (!म_भेदन(oem_id, "IBM", 3) && (!म_भेदन(oem_table_id, "SERMOW", 6))) अणु

		/*
		 * Unक्रमtunately ITC_DRIFT is not yet part of the
		 * official SAL spec, so the ITC_DRIFT bit is not
		 * set by the BIOS on this hardware.
		 */
		sal_platक्रमm_features |= IA64_SAL_PLATFORM_FEATURE_ITC_DRIFT;

		cyclone_setup();
	पूर्ण
पूर्ण

अटल पूर्णांक __init acpi_parse_madt(काष्ठा acpi_table_header *table)
अणु
	acpi_madt = (काष्ठा acpi_table_madt *)table;

	acpi_madt_rev = acpi_madt->header.revision;

	/* remember the value क्रम reference after मुक्त_iniपंचांगem() */
#अगर_घोषित CONFIG_ITANIUM
	has_8259 = 1;		/* Firmware on old Itanium प्रणालीs is broken */
#अन्यथा
	has_8259 = acpi_madt->flags & ACPI_MADT_PCAT_COMPAT;
#पूर्ण_अगर
	iosapic_प्रणाली_init(has_8259);

	/* Get base address of IPI Message Block */

	अगर (acpi_madt->address)
		ipi_base_addr = ioremap(acpi_madt->address, 0);

	prपूर्णांकk(KERN_INFO PREFIX "Local APIC address %p\n", ipi_base_addr);

	acpi_madt_oem_check(acpi_madt->header.oem_id,
			    acpi_madt->header.oem_table_id);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_ACPI_NUMA

#अघोषित SLIT_DEBUG

#घोषणा PXM_FLAG_LEN ((MAX_PXM_DOMAINS + 1)/32)

अटल पूर्णांक __initdata srat_num_cpus;	/* number of cpus */
अटल u32 pxm_flag[PXM_FLAG_LEN];
#घोषणा pxm_bit_set(bit)	(set_bit(bit,(व्योम *)pxm_flag))
#घोषणा pxm_bit_test(bit)	(test_bit(bit,(व्योम *)pxm_flag))
अटल काष्ठा acpi_table_slit __initdata *slit_table;
cpumask_t early_cpu_possible_map = CPU_MASK_NONE;

अटल पूर्णांक __init
get_processor_proximity_करोमुख्य(काष्ठा acpi_srat_cpu_affinity *pa)
अणु
	पूर्णांक pxm;

	pxm = pa->proximity_करोमुख्य_lo;
	अगर (acpi_srat_revision >= 2)
		pxm += pa->proximity_करोमुख्य_hi[0] << 8;
	वापस pxm;
पूर्ण

अटल पूर्णांक __init
get_memory_proximity_करोमुख्य(काष्ठा acpi_srat_mem_affinity *ma)
अणु
	पूर्णांक pxm;

	pxm = ma->proximity_करोमुख्य;
	अगर (acpi_srat_revision <= 1)
		pxm &= 0xff;

	वापस pxm;
पूर्ण

/*
 * ACPI 2.0 SLIT (System Locality Inक्रमmation Table)
 * http://devresource.hp.com/devresource/Docs/TechPapers/IA64/slit.pdf
 */
व्योम __init acpi_numa_slit_init(काष्ठा acpi_table_slit *slit)
अणु
	u32 len;

	len = माप(काष्ठा acpi_table_header) + 8
	    + slit->locality_count * slit->locality_count;
	अगर (slit->header.length != len) अणु
		prपूर्णांकk(KERN_ERR
		       "ACPI 2.0 SLIT: size mismatch: %d expected, %d actual\n",
		       len, slit->header.length);
		वापस;
	पूर्ण
	slit_table = slit;
पूर्ण

व्योम __init
acpi_numa_processor_affinity_init(काष्ठा acpi_srat_cpu_affinity *pa)
अणु
	पूर्णांक pxm;

	अगर (!(pa->flags & ACPI_SRAT_CPU_ENABLED))
		वापस;

	अगर (srat_num_cpus >= ARRAY_SIZE(node_cpuid)) अणु
		prपूर्णांकk_once(KERN_WARNING
			    "node_cpuid[%ld] is too small, may not be able to use all cpus\n",
			    ARRAY_SIZE(node_cpuid));
		वापस;
	पूर्ण
	pxm = get_processor_proximity_करोमुख्य(pa);

	/* record this node in proximity biपंचांगap */
	pxm_bit_set(pxm);

	node_cpuid[srat_num_cpus].phys_id =
	    (pa->apic_id << 8) | (pa->local_sapic_eid);
	/* nid should be overridden as logical node id later */
	node_cpuid[srat_num_cpus].nid = pxm;
	cpumask_set_cpu(srat_num_cpus, &early_cpu_possible_map);
	srat_num_cpus++;
पूर्ण

पूर्णांक __init
acpi_numa_memory_affinity_init(काष्ठा acpi_srat_mem_affinity *ma)
अणु
	अचिन्हित दीर्घ paddr, size;
	पूर्णांक pxm;
	काष्ठा node_memblk_s *p, *q, *pend;

	pxm = get_memory_proximity_करोमुख्य(ma);

	/* fill node memory chunk काष्ठाure */
	paddr = ma->base_address;
	size = ma->length;

	/* Ignore disabled entries */
	अगर (!(ma->flags & ACPI_SRAT_MEM_ENABLED))
		वापस -1;

	अगर (num_node_memblks >= NR_NODE_MEMBLKS) अणु
		pr_err("NUMA: too many memblk ranges\n");
		वापस -EINVAL;
	पूर्ण

	/* record this node in proximity biपंचांगap */
	pxm_bit_set(pxm);

	/* Insertion sort based on base address */
	pend = &node_memblk[num_node_memblks];
	क्रम (p = &node_memblk[0]; p < pend; p++) अणु
		अगर (paddr < p->start_paddr)
			अवरोध;
	पूर्ण
	अगर (p < pend) अणु
		क्रम (q = pend - 1; q >= p; q--)
			*(q + 1) = *q;
	पूर्ण
	p->start_paddr = paddr;
	p->size = size;
	p->nid = pxm;
	num_node_memblks++;
	वापस 0;
पूर्ण

व्योम __init acpi_numa_fixup(व्योम)
अणु
	पूर्णांक i, j, node_from, node_to;

	/* If there's no SRAT, fix the phys_id and mark node 0 online */
	अगर (srat_num_cpus == 0) अणु
		node_set_online(0);
		node_cpuid[0].phys_id = hard_smp_processor_id();
		slit_distance(0, 0) = LOCAL_DISTANCE;
		जाओ out;
	पूर्ण

	/*
	 * MCD - This can probably be dropped now.  No need क्रम pxm ID to node ID
	 * mapping with sparse node numbering अगरf MAX_PXM_DOMAINS <= MAX_NUMNODES.
	 */
	nodes_clear(node_online_map);
	क्रम (i = 0; i < MAX_PXM_DOMAINS; i++) अणु
		अगर (pxm_bit_test(i)) अणु
			पूर्णांक nid = acpi_map_pxm_to_node(i);
			node_set_online(nid);
		पूर्ण
	पूर्ण

	/* set logical node id in memory chunk काष्ठाure */
	क्रम (i = 0; i < num_node_memblks; i++)
		node_memblk[i].nid = pxm_to_node(node_memblk[i].nid);

	/* assign memory bank numbers क्रम each chunk on each node */
	क्रम_each_online_node(i) अणु
		पूर्णांक bank;

		bank = 0;
		क्रम (j = 0; j < num_node_memblks; j++)
			अगर (node_memblk[j].nid == i)
				node_memblk[j].bank = bank++;
	पूर्ण

	/* set logical node id in cpu काष्ठाure */
	क्रम_each_possible_early_cpu(i)
		node_cpuid[i].nid = pxm_to_node(node_cpuid[i].nid);

	prपूर्णांकk(KERN_INFO "Number of logical nodes in system = %d\n",
	       num_online_nodes());
	prपूर्णांकk(KERN_INFO "Number of memory chunks in system = %d\n",
	       num_node_memblks);

	अगर (!slit_table) अणु
		क्रम (i = 0; i < MAX_NUMNODES; i++)
			क्रम (j = 0; j < MAX_NUMNODES; j++)
				slit_distance(i, j) = i == j ?
					LOCAL_DISTANCE : REMOTE_DISTANCE;
		जाओ out;
	पूर्ण

	स_रखो(numa_slit, -1, माप(numa_slit));
	क्रम (i = 0; i < slit_table->locality_count; i++) अणु
		अगर (!pxm_bit_test(i))
			जारी;
		node_from = pxm_to_node(i);
		क्रम (j = 0; j < slit_table->locality_count; j++) अणु
			अगर (!pxm_bit_test(j))
				जारी;
			node_to = pxm_to_node(j);
			slit_distance(node_from, node_to) =
			    slit_table->entry[i * slit_table->locality_count + j];
		पूर्ण
	पूर्ण

#अगर_घोषित SLIT_DEBUG
	prपूर्णांकk("ACPI 2.0 SLIT locality table:\n");
	क्रम_each_online_node(i) अणु
		क्रम_each_online_node(j)
		    prपूर्णांकk("%03d ", node_distance(i, j));
		prपूर्णांकk("\n");
	पूर्ण
#पूर्ण_अगर
out:
	node_possible_map = node_online_map;
पूर्ण
#पूर्ण_अगर				/* CONFIG_ACPI_NUMA */

/*
 * success: वापस IRQ number (>=0)
 * failure: वापस < 0
 */
पूर्णांक acpi_रेजिस्टर_gsi(काष्ठा device *dev, u32 gsi, पूर्णांक triggering, पूर्णांक polarity)
अणु
	अगर (acpi_irq_model == ACPI_IRQ_MODEL_PLATFORM)
		वापस gsi;

	अगर (has_8259 && gsi < 16)
		वापस isa_irq_to_vector(gsi);

	वापस iosapic_रेजिस्टर_पूर्णांकr(gsi,
				     (polarity ==
				      ACPI_ACTIVE_HIGH) ? IOSAPIC_POL_HIGH :
				     IOSAPIC_POL_LOW,
				     (triggering ==
				      ACPI_EDGE_SENSITIVE) ? IOSAPIC_EDGE :
				     IOSAPIC_LEVEL);
पूर्ण
EXPORT_SYMBOL_GPL(acpi_रेजिस्टर_gsi);

व्योम acpi_unरेजिस्टर_gsi(u32 gsi)
अणु
	अगर (acpi_irq_model == ACPI_IRQ_MODEL_PLATFORM)
		वापस;

	अगर (has_8259 && gsi < 16)
		वापस;

	iosapic_unरेजिस्टर_पूर्णांकr(gsi);
पूर्ण
EXPORT_SYMBOL_GPL(acpi_unरेजिस्टर_gsi);

अटल पूर्णांक __init acpi_parse_fadt(काष्ठा acpi_table_header *table)
अणु
	काष्ठा acpi_table_header *fadt_header;
	काष्ठा acpi_table_fadt *fadt;

	fadt_header = (काष्ठा acpi_table_header *)table;
	अगर (fadt_header->revision != 3)
		वापस -ENODEV;	/* Only deal with ACPI 2.0 FADT */

	fadt = (काष्ठा acpi_table_fadt *)fadt_header;

	acpi_रेजिस्टर_gsi(शून्य, fadt->sci_पूर्णांकerrupt, ACPI_LEVEL_SENSITIVE,
				 ACPI_ACTIVE_LOW);
	वापस 0;
पूर्ण

पूर्णांक __init early_acpi_boot_init(व्योम)
अणु
	पूर्णांक ret;

	/*
	 * करो a partial walk of MADT to determine how many CPUs
	 * we have including offline CPUs
	 */
	अगर (acpi_table_parse(ACPI_SIG_MADT, acpi_parse_madt)) अणु
		prपूर्णांकk(KERN_ERR PREFIX "Can't find MADT\n");
		वापस 0;
	पूर्ण

	ret = acpi_table_parse_madt(ACPI_MADT_TYPE_LOCAL_SAPIC,
		acpi_parse_lsapic, NR_CPUS);
	अगर (ret < 1)
		prपूर्णांकk(KERN_ERR PREFIX
		       "Error parsing MADT - no LAPIC entries\n");
	अन्यथा
		acpi_lapic = 1;

#अगर_घोषित CONFIG_SMP
	अगर (available_cpus == 0) अणु
		prपूर्णांकk(KERN_INFO "ACPI: Found 0 CPUS; assuming 1\n");
		prपूर्णांकk(KERN_INFO "CPU 0 (0x%04x)", hard_smp_processor_id());
		smp_boot_data.cpu_phys_id[available_cpus] =
		    hard_smp_processor_id();
		available_cpus = 1;	/* We've got at least one of these, no? */
	पूर्ण
	smp_boot_data.cpu_count = available_cpus;
#पूर्ण_अगर
	/* Make boot-up look pretty */
	prपूर्णांकk(KERN_INFO "%d CPUs available, %d CPUs total\n", available_cpus,
	       total_cpus);

	वापस 0;
पूर्ण

पूर्णांक __init acpi_boot_init(व्योम)
अणु

	/*
	 * MADT
	 * ----
	 * Parse the Multiple APIC Description Table (MADT), अगर exists.
	 * Note that this table provides platक्रमm SMP configuration
	 * inक्रमmation -- the successor to MPS tables.
	 */

	अगर (acpi_table_parse(ACPI_SIG_MADT, acpi_parse_madt)) अणु
		prपूर्णांकk(KERN_ERR PREFIX "Can't find MADT\n");
		जाओ skip_madt;
	पूर्ण

	/* Local APIC */

	अगर (acpi_table_parse_madt
	    (ACPI_MADT_TYPE_LOCAL_APIC_OVERRIDE, acpi_parse_lapic_addr_ovr, 0) < 0)
		prपूर्णांकk(KERN_ERR PREFIX
		       "Error parsing LAPIC address override entry\n");

	अगर (acpi_table_parse_madt(ACPI_MADT_TYPE_LOCAL_APIC_NMI, acpi_parse_lapic_nmi, 0)
	    < 0)
		prपूर्णांकk(KERN_ERR PREFIX "Error parsing LAPIC NMI entry\n");

	/* I/O APIC */

	अगर (acpi_table_parse_madt
	    (ACPI_MADT_TYPE_IO_SAPIC, acpi_parse_iosapic, NR_IOSAPICS) < 1) अणु
		prपूर्णांकk(KERN_ERR PREFIX
		       "Error parsing MADT - no IOSAPIC entries\n");
	पूर्ण

	/* System-Level Interrupt Routing */

	अगर (acpi_table_parse_madt
	    (ACPI_MADT_TYPE_INTERRUPT_SOURCE, acpi_parse_plat_पूर्णांक_src,
	     ACPI_MAX_PLATFORM_INTERRUPTS) < 0)
		prपूर्णांकk(KERN_ERR PREFIX
		       "Error parsing platform interrupt source entry\n");

	अगर (acpi_table_parse_madt
	    (ACPI_MADT_TYPE_INTERRUPT_OVERRIDE, acpi_parse_पूर्णांक_src_ovr, 0) < 0)
		prपूर्णांकk(KERN_ERR PREFIX
		       "Error parsing interrupt source overrides entry\n");

	अगर (acpi_table_parse_madt(ACPI_MADT_TYPE_NMI_SOURCE, acpi_parse_nmi_src, 0) < 0)
		prपूर्णांकk(KERN_ERR PREFIX "Error parsing NMI SRC entry\n");
      skip_madt:

	/*
	 * FADT says whether a legacy keyboard controller is present.
	 * The FADT also contains an SCI_INT line, by which the प्रणाली
	 * माला_लो पूर्णांकerrupts such as घातer and sleep buttons.  If it's not
	 * on a Legacy पूर्णांकerrupt, it needs to be setup.
	 */
	अगर (acpi_table_parse(ACPI_SIG_FADT, acpi_parse_fadt))
		prपूर्णांकk(KERN_ERR PREFIX "Can't find FADT\n");

#अगर_घोषित CONFIG_ACPI_NUMA
#अगर_घोषित CONFIG_SMP
	अगर (srat_num_cpus == 0) अणु
		पूर्णांक cpu, i = 1;
		क्रम (cpu = 0; cpu < smp_boot_data.cpu_count; cpu++)
			अगर (smp_boot_data.cpu_phys_id[cpu] !=
			    hard_smp_processor_id())
				node_cpuid[i++].phys_id =
				    smp_boot_data.cpu_phys_id[cpu];
	पूर्ण
#पूर्ण_अगर
	build_cpu_to_node_map();
#पूर्ण_अगर
	वापस 0;
पूर्ण

पूर्णांक acpi_gsi_to_irq(u32 gsi, अचिन्हित पूर्णांक *irq)
अणु
	पूर्णांक पंचांगp;

	अगर (has_8259 && gsi < 16)
		*irq = isa_irq_to_vector(gsi);
	अन्यथा अणु
		पंचांगp = gsi_to_irq(gsi);
		अगर (पंचांगp == -1)
			वापस -1;
		*irq = पंचांगp;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक acpi_isa_irq_to_gsi(अचिन्हित isa_irq, u32 *gsi)
अणु
	अगर (isa_irq >= 16)
		वापस -1;
	*gsi = isa_irq;
	वापस 0;
पूर्ण

/*
 *  ACPI based hotplug CPU support
 */
#अगर_घोषित CONFIG_ACPI_HOTPLUG_CPU
पूर्णांक acpi_map_cpu2node(acpi_handle handle, पूर्णांक cpu, पूर्णांक physid)
अणु
#अगर_घोषित CONFIG_ACPI_NUMA
	/*
	 * We करोn't have cpu-only-node hotadd. But अगर the प्रणाली equips
	 * SRAT table, pxm is alपढ़ोy found and node is पढ़ोy.
  	 * So, just pxm_to_nid(pxm) is OK.
	 * This code here is क्रम the प्रणाली which करोesn't have full SRAT
  	 * table क्रम possible cpus.
	 */
	node_cpuid[cpu].phys_id = physid;
	node_cpuid[cpu].nid = acpi_get_node(handle);
#पूर्ण_अगर
	वापस 0;
पूर्ण

पूर्णांक additional_cpus __initdata = -1;

अटल __init पूर्णांक setup_additional_cpus(अक्षर *s)
अणु
	अगर (s)
		additional_cpus = simple_म_से_दीर्घ(s, शून्य, 0);

	वापस 0;
पूर्ण

early_param("additional_cpus", setup_additional_cpus);

/*
 * cpu_possible_mask should be अटल, it cannot change as CPUs
 * are onlined, or offlined. The reason is per-cpu data-काष्ठाures
 * are allocated by some modules at init समय, and करोnt expect to
 * करो this dynamically on cpu arrival/departure.
 * cpu_present_mask on the other hand can change dynamically.
 * In हाल when cpu_hotplug is not compiled, then we resort to current
 * behaviour, which is cpu_possible == cpu_present.
 * - Ashok Raj
 *
 * Three ways to find out the number of additional hotplug CPUs:
 * - If the BIOS specअगरied disabled CPUs in ACPI/mptables use that.
 * - The user can overग_लिखो it with additional_cpus=NUM
 * - Otherwise करोn't reserve additional CPUs.
 */
__init व्योम prefill_possible_map(व्योम)
अणु
	पूर्णांक i;
	पूर्णांक possible, disabled_cpus;

	disabled_cpus = total_cpus - available_cpus;

 	अगर (additional_cpus == -1) अणु
 		अगर (disabled_cpus > 0)
			additional_cpus = disabled_cpus;
 		अन्यथा
			additional_cpus = 0;
 	पूर्ण

	possible = available_cpus + additional_cpus;

	अगर (possible > nr_cpu_ids)
		possible = nr_cpu_ids;

	prपूर्णांकk(KERN_INFO "SMP: Allowing %d CPUs, %d hotplug CPUs\n",
		possible, max((possible - available_cpus), 0));

	क्रम (i = 0; i < possible; i++)
		set_cpu_possible(i, true);
पूर्ण

अटल पूर्णांक _acpi_map_lsapic(acpi_handle handle, पूर्णांक physid, पूर्णांक *pcpu)
अणु
	cpumask_t पंचांगp_map;
	पूर्णांक cpu;

	cpumask_complement(&पंचांगp_map, cpu_present_mask);
	cpu = cpumask_first(&पंचांगp_map);
	अगर (cpu >= nr_cpu_ids)
		वापस -EINVAL;

	acpi_map_cpu2node(handle, cpu, physid);

	set_cpu_present(cpu, true);
	ia64_cpu_to_sapicid[cpu] = physid;

	acpi_processor_set_pdc(handle);

	*pcpu = cpu;
	वापस (0);
पूर्ण

/* wrapper to silence section mismatch warning */
पूर्णांक __ref acpi_map_cpu(acpi_handle handle, phys_cpuid_t physid, u32 acpi_id,
		       पूर्णांक *pcpu)
अणु
	वापस _acpi_map_lsapic(handle, physid, pcpu);
पूर्ण
EXPORT_SYMBOL(acpi_map_cpu);

पूर्णांक acpi_unmap_cpu(पूर्णांक cpu)
अणु
	ia64_cpu_to_sapicid[cpu] = -1;
	set_cpu_present(cpu, false);

#अगर_घोषित CONFIG_ACPI_NUMA
	/* NUMA specअगरic cleanup's */
#पूर्ण_अगर

	वापस (0);
पूर्ण
EXPORT_SYMBOL(acpi_unmap_cpu);
#पूर्ण_अगर				/* CONFIG_ACPI_HOTPLUG_CPU */

#अगर_घोषित CONFIG_ACPI_NUMA
अटल acpi_status acpi_map_iosapic(acpi_handle handle, u32 depth,
				    व्योम *context, व्योम **ret)
अणु
	काष्ठा acpi_buffer buffer = अणु ACPI_ALLOCATE_BUFFER, शून्य पूर्ण;
	जोड़ acpi_object *obj;
	काष्ठा acpi_madt_io_sapic *iosapic;
	अचिन्हित पूर्णांक gsi_base;
	पूर्णांक node;

	/* Only care about objects w/ a method that वापसs the MADT */
	अगर (ACPI_FAILURE(acpi_evaluate_object(handle, "_MAT", शून्य, &buffer)))
		वापस AE_OK;

	अगर (!buffer.length || !buffer.poपूर्णांकer)
		वापस AE_OK;

	obj = buffer.poपूर्णांकer;
	अगर (obj->type != ACPI_TYPE_BUFFER ||
	    obj->buffer.length < माप(*iosapic)) अणु
		kमुक्त(buffer.poपूर्णांकer);
		वापस AE_OK;
	पूर्ण

	iosapic = (काष्ठा acpi_madt_io_sapic *)obj->buffer.poपूर्णांकer;

	अगर (iosapic->header.type != ACPI_MADT_TYPE_IO_SAPIC) अणु
		kमुक्त(buffer.poपूर्णांकer);
		वापस AE_OK;
	पूर्ण

	gsi_base = iosapic->global_irq_base;

	kमुक्त(buffer.poपूर्णांकer);

	/* OK, it's an IOSAPIC MADT entry; associate it with a node */
	node = acpi_get_node(handle);
	अगर (node == NUMA_NO_NODE || !node_online(node) ||
	    cpumask_empty(cpumask_of_node(node)))
		वापस AE_OK;

	/* We know a gsi to node mapping! */
	map_iosapic_to_node(gsi_base, node);
	वापस AE_OK;
पूर्ण

अटल पूर्णांक __init
acpi_map_iosapics (व्योम)
अणु
	acpi_get_devices(शून्य, acpi_map_iosapic, शून्य, शून्य);
	वापस 0;
पूर्ण

fs_initcall(acpi_map_iosapics);
#पूर्ण_अगर				/* CONFIG_ACPI_NUMA */

पूर्णांक __ref acpi_रेजिस्टर_ioapic(acpi_handle handle, u64 phys_addr, u32 gsi_base)
अणु
	पूर्णांक err;

	अगर ((err = iosapic_init(phys_addr, gsi_base)))
		वापस err;

#अगर_घोषित CONFIG_ACPI_NUMA
	acpi_map_iosapic(handle, 0, शून्य, शून्य);
#पूर्ण_अगर				/* CONFIG_ACPI_NUMA */

	वापस 0;
पूर्ण

EXPORT_SYMBOL(acpi_रेजिस्टर_ioapic);

पूर्णांक acpi_unरेजिस्टर_ioapic(acpi_handle handle, u32 gsi_base)
अणु
	वापस iosapic_हटाओ(gsi_base);
पूर्ण

EXPORT_SYMBOL(acpi_unरेजिस्टर_ioapic);

/*
 * acpi_suspend_lowlevel() - save kernel state and suspend.
 *
 * TBD when when IA64 starts to support suspend...
 */
पूर्णांक acpi_suspend_lowlevel(व्योम) अणु वापस 0; पूर्ण
