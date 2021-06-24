<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/export.h>
#समावेश <linux/init.h>
#समावेश <linux/memblock.h>
#समावेश <linux/percpu.h>
#समावेश <linux/kexec.h>
#समावेश <linux/crash_dump.h>
#समावेश <linux/smp.h>
#समावेश <linux/topology.h>
#समावेश <linux/pfn.h>
#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/desc.h>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/mpspec.h>
#समावेश <यंत्र/apicdef.h>
#समावेश <यंत्र/highस्मृति.स>
#समावेश <यंत्र/proto.h>
#समावेश <यंत्र/cpumask.h>
#समावेश <यंत्र/cpu.h>
#समावेश <यंत्र/stackprotector.h>

DEFINE_PER_CPU_READ_MOSTLY(पूर्णांक, cpu_number);
EXPORT_PER_CPU_SYMBOL(cpu_number);

#अगर_घोषित CONFIG_X86_64
#घोषणा BOOT_PERCPU_OFFSET ((अचिन्हित दीर्घ)__per_cpu_load)
#अन्यथा
#घोषणा BOOT_PERCPU_OFFSET 0
#पूर्ण_अगर

DEFINE_PER_CPU_READ_MOSTLY(अचिन्हित दीर्घ, this_cpu_off) = BOOT_PERCPU_OFFSET;
EXPORT_PER_CPU_SYMBOL(this_cpu_off);

अचिन्हित दीर्घ __per_cpu_offset[NR_CPUS] __ro_after_init = अणु
	[0 ... NR_CPUS-1] = BOOT_PERCPU_OFFSET,
पूर्ण;
EXPORT_SYMBOL(__per_cpu_offset);

/*
 * On x86_64 symbols referenced from code should be reachable using
 * 32bit relocations.  Reserve space क्रम अटल percpu variables in
 * modules so that they are always served from the first chunk which
 * is located at the percpu segment base.  On x86_32, anything can
 * address anywhere.  No need to reserve space in the first chunk.
 */
#अगर_घोषित CONFIG_X86_64
#घोषणा PERCPU_FIRST_CHUNK_RESERVE	PERCPU_MODULE_RESERVE
#अन्यथा
#घोषणा PERCPU_FIRST_CHUNK_RESERVE	0
#पूर्ण_अगर

#अगर_घोषित CONFIG_X86_32
/**
 * pcpu_need_numa - determine percpu allocation needs to consider NUMA
 *
 * If NUMA is not configured or there is only one NUMA node available,
 * there is no reason to consider NUMA.  This function determines
 * whether percpu allocation should consider NUMA or not.
 *
 * RETURNS:
 * true अगर NUMA should be considered; otherwise, false.
 */
अटल bool __init pcpu_need_numa(व्योम)
अणु
#अगर_घोषित CONFIG_NEED_MULTIPLE_NODES
	pg_data_t *last = शून्य;
	अचिन्हित पूर्णांक cpu;

	क्रम_each_possible_cpu(cpu) अणु
		पूर्णांक node = early_cpu_to_node(cpu);

		अगर (node_online(node) && NODE_DATA(node) &&
		    last && last != NODE_DATA(node))
			वापस true;

		last = NODE_DATA(node);
	पूर्ण
#पूर्ण_अगर
	वापस false;
पूर्ण
#पूर्ण_अगर

/**
 * pcpu_alloc_booपंचांगem - NUMA मित्रly alloc_booपंचांगem wrapper क्रम percpu
 * @cpu: cpu to allocate क्रम
 * @size: size allocation in bytes
 * @align: alignment
 *
 * Allocate @size bytes aligned at @align क्रम cpu @cpu.  This wrapper
 * करोes the right thing क्रम NUMA regardless of the current
 * configuration.
 *
 * RETURNS:
 * Poपूर्णांकer to the allocated area on success, शून्य on failure.
 */
अटल व्योम * __init pcpu_alloc_booपंचांगem(अचिन्हित पूर्णांक cpu, अचिन्हित दीर्घ size,
					अचिन्हित दीर्घ align)
अणु
	स्थिर अचिन्हित दीर्घ goal = __pa(MAX_DMA_ADDRESS);
#अगर_घोषित CONFIG_NEED_MULTIPLE_NODES
	पूर्णांक node = early_cpu_to_node(cpu);
	व्योम *ptr;

	अगर (!node_online(node) || !NODE_DATA(node)) अणु
		ptr = memblock_alloc_from(size, align, goal);
		pr_info("cpu %d has no node %d or node-local memory\n",
			cpu, node);
		pr_debug("per cpu data for cpu%d %lu bytes at %016lx\n",
			 cpu, size, __pa(ptr));
	पूर्ण अन्यथा अणु
		ptr = memblock_alloc_try_nid(size, align, goal,
					     MEMBLOCK_ALLOC_ACCESSIBLE,
					     node);

		pr_debug("per cpu data for cpu%d %lu bytes on node%d at %016lx\n",
			 cpu, size, node, __pa(ptr));
	पूर्ण
	वापस ptr;
#अन्यथा
	वापस memblock_alloc_from(size, align, goal);
#पूर्ण_अगर
पूर्ण

/*
 * Helpers क्रम first chunk memory allocation
 */
अटल व्योम * __init pcpu_fc_alloc(अचिन्हित पूर्णांक cpu, माप_प्रकार size, माप_प्रकार align)
अणु
	वापस pcpu_alloc_booपंचांगem(cpu, size, align);
पूर्ण

अटल व्योम __init pcpu_fc_मुक्त(व्योम *ptr, माप_प्रकार size)
अणु
	memblock_मुक्त(__pa(ptr), size);
पूर्ण

अटल पूर्णांक __init pcpu_cpu_distance(अचिन्हित पूर्णांक from, अचिन्हित पूर्णांक to)
अणु
#अगर_घोषित CONFIG_NEED_MULTIPLE_NODES
	अगर (early_cpu_to_node(from) == early_cpu_to_node(to))
		वापस LOCAL_DISTANCE;
	अन्यथा
		वापस REMOTE_DISTANCE;
#अन्यथा
	वापस LOCAL_DISTANCE;
#पूर्ण_अगर
पूर्ण

अटल व्योम __init pcpup_populate_pte(अचिन्हित दीर्घ addr)
अणु
	populate_extra_pte(addr);
पूर्ण

अटल अंतरभूत व्योम setup_percpu_segment(पूर्णांक cpu)
अणु
#अगर_घोषित CONFIG_X86_32
	काष्ठा desc_काष्ठा d = GDT_ENTRY_INIT(0x8092, per_cpu_offset(cpu),
					      0xFFFFF);

	ग_लिखो_gdt_entry(get_cpu_gdt_rw(cpu), GDT_ENTRY_PERCPU, &d, DESCTYPE_S);
#पूर्ण_अगर
पूर्ण

व्योम __init setup_per_cpu_areas(व्योम)
अणु
	अचिन्हित पूर्णांक cpu;
	अचिन्हित दीर्घ delta;
	पूर्णांक rc;

	pr_info("NR_CPUS:%d nr_cpumask_bits:%d nr_cpu_ids:%u nr_node_ids:%u\n",
		NR_CPUS, nr_cpumask_bits, nr_cpu_ids, nr_node_ids);

	/*
	 * Allocate percpu area.  Embedding allocator is our favorite;
	 * however, on NUMA configurations, it can result in very
	 * sparse unit mapping and vदो_स्मृति area isn't spacious enough
	 * on 32bit.  Use page in that हाल.
	 */
#अगर_घोषित CONFIG_X86_32
	अगर (pcpu_chosen_fc == PCPU_FC_AUTO && pcpu_need_numa())
		pcpu_chosen_fc = PCPU_FC_PAGE;
#पूर्ण_अगर
	rc = -EINVAL;
	अगर (pcpu_chosen_fc != PCPU_FC_PAGE) अणु
		स्थिर माप_प्रकार dyn_size = PERCPU_MODULE_RESERVE +
			PERCPU_DYNAMIC_RESERVE - PERCPU_FIRST_CHUNK_RESERVE;
		माप_प्रकार atom_size;

		/*
		 * On 64bit, use PMD_SIZE क्रम atom_size so that embedded
		 * percpu areas are aligned to PMD.  This, in the future,
		 * can also allow using PMD mappings in vदो_स्मृति area.  Use
		 * PAGE_SIZE on 32bit as vदो_स्मृति space is highly contended
		 * and large vदो_स्मृति area allocs can easily fail.
		 */
#अगर_घोषित CONFIG_X86_64
		atom_size = PMD_SIZE;
#अन्यथा
		atom_size = PAGE_SIZE;
#पूर्ण_अगर
		rc = pcpu_embed_first_chunk(PERCPU_FIRST_CHUNK_RESERVE,
					    dyn_size, atom_size,
					    pcpu_cpu_distance,
					    pcpu_fc_alloc, pcpu_fc_मुक्त);
		अगर (rc < 0)
			pr_warn("%s allocator failed (%d), falling back to page size\n",
				pcpu_fc_names[pcpu_chosen_fc], rc);
	पूर्ण
	अगर (rc < 0)
		rc = pcpu_page_first_chunk(PERCPU_FIRST_CHUNK_RESERVE,
					   pcpu_fc_alloc, pcpu_fc_मुक्त,
					   pcpup_populate_pte);
	अगर (rc < 0)
		panic("cannot initialize percpu area (err=%d)", rc);

	/* alrighty, percpu areas up and running */
	delta = (अचिन्हित दीर्घ)pcpu_base_addr - (अचिन्हित दीर्घ)__per_cpu_start;
	क्रम_each_possible_cpu(cpu) अणु
		per_cpu_offset(cpu) = delta + pcpu_unit_offsets[cpu];
		per_cpu(this_cpu_off, cpu) = per_cpu_offset(cpu);
		per_cpu(cpu_number, cpu) = cpu;
		setup_percpu_segment(cpu);
		/*
		 * Copy data used in early init routines from the
		 * initial arrays to the per cpu data areas.  These
		 * arrays then become expendable and the *_early_ptr's
		 * are zeroed indicating that the अटल arrays are
		 * gone.
		 */
#अगर_घोषित CONFIG_X86_LOCAL_APIC
		per_cpu(x86_cpu_to_apicid, cpu) =
			early_per_cpu_map(x86_cpu_to_apicid, cpu);
		per_cpu(x86_bios_cpu_apicid, cpu) =
			early_per_cpu_map(x86_bios_cpu_apicid, cpu);
		per_cpu(x86_cpu_to_acpiid, cpu) =
			early_per_cpu_map(x86_cpu_to_acpiid, cpu);
#पूर्ण_अगर
#अगर_घोषित CONFIG_X86_32
		per_cpu(x86_cpu_to_logical_apicid, cpu) =
			early_per_cpu_map(x86_cpu_to_logical_apicid, cpu);
#पूर्ण_अगर
#अगर_घोषित CONFIG_NUMA
		per_cpu(x86_cpu_to_node_map, cpu) =
			early_per_cpu_map(x86_cpu_to_node_map, cpu);
		/*
		 * Ensure that the boot cpu numa_node is correct when the boot
		 * cpu is on a node that करोesn't have memory installed.
		 * Also cpu_up() will call cpu_to_node() क्रम APs when
		 * MEMORY_HOTPLUG is defined, beक्रमe per_cpu(numa_node) is set
		 * up later with c_init aka पूर्णांकel_init/amd_init.
		 * So set them all (boot cpu and all APs).
		 */
		set_cpu_numa_node(cpu, early_cpu_to_node(cpu));
#पूर्ण_अगर
		/*
		 * Up to this poपूर्णांक, the boot CPU has been using .init.data
		 * area.  Reload any changed state क्रम the boot CPU.
		 */
		अगर (!cpu)
			चयन_to_new_gdt(cpu);
	पूर्ण

	/* indicate the early अटल arrays will soon be gone */
#अगर_घोषित CONFIG_X86_LOCAL_APIC
	early_per_cpu_ptr(x86_cpu_to_apicid) = शून्य;
	early_per_cpu_ptr(x86_bios_cpu_apicid) = शून्य;
	early_per_cpu_ptr(x86_cpu_to_acpiid) = शून्य;
#पूर्ण_अगर
#अगर_घोषित CONFIG_X86_32
	early_per_cpu_ptr(x86_cpu_to_logical_apicid) = शून्य;
#पूर्ण_अगर
#अगर_घोषित CONFIG_NUMA
	early_per_cpu_ptr(x86_cpu_to_node_map) = शून्य;
#पूर्ण_अगर

	/* Setup node to cpumask map */
	setup_node_to_cpumask_map();

	/* Setup cpu initialized, callin, callout masks */
	setup_cpu_local_masks();

	/*
	 * Sync back kernel address range again.  We alपढ़ोy did this in
	 * setup_arch(), but percpu data also needs to be available in
	 * the smpboot यंत्र and arch_sync_kernel_mappings() करोesn't sync to
	 * swapper_pg_dir on 32-bit. The per-cpu mappings need to be available
	 * there too.
	 *
	 * FIXME: Can the later sync in setup_cpu_entry_areas() replace
	 * this call?
	 */
	sync_initial_page_table();
पूर्ण
