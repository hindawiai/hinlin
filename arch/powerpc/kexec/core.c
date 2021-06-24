<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Code to handle transition of Linux booting another kernel.
 *
 * Copyright (C) 2002-2003 Eric Biederman  <ebiederm@xmission.com>
 * GameCube/ppc32 port Copyright (C) 2004 Albert Herranz
 * Copyright (C) 2005 IBM Corporation.
 */

#समावेश <linux/kexec.h>
#समावेश <linux/reboot.h>
#समावेश <linux/thपढ़ोs.h>
#समावेश <linux/memblock.h>
#समावेश <linux/of.h>
#समावेश <linux/irq.h>
#समावेश <linux/ftrace.h>

#समावेश <यंत्र/kdump.h>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/pgभाग.स>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/sections.h>

व्योम machine_kexec_mask_पूर्णांकerrupts(व्योम) अणु
	अचिन्हित पूर्णांक i;
	काष्ठा irq_desc *desc;

	क्रम_each_irq_desc(i, desc) अणु
		काष्ठा irq_chip *chip;

		chip = irq_desc_get_chip(desc);
		अगर (!chip)
			जारी;

		अगर (chip->irq_eoi && irqd_irq_inprogress(&desc->irq_data))
			chip->irq_eoi(&desc->irq_data);

		अगर (chip->irq_mask)
			chip->irq_mask(&desc->irq_data);

		अगर (chip->irq_disable && !irqd_irq_disabled(&desc->irq_data))
			chip->irq_disable(&desc->irq_data);
	पूर्ण
पूर्ण

व्योम machine_crash_shutकरोwn(काष्ठा pt_regs *regs)
अणु
	शेष_machine_crash_shutकरोwn(regs);
पूर्ण

/*
 * Do what every setup is needed on image and the
 * reboot code buffer to allow us to aव्योम allocations
 * later.
 */
पूर्णांक machine_kexec_prepare(काष्ठा kimage *image)
अणु
	अगर (ppc_md.machine_kexec_prepare)
		वापस ppc_md.machine_kexec_prepare(image);
	अन्यथा
		वापस शेष_machine_kexec_prepare(image);
पूर्ण

व्योम machine_kexec_cleanup(काष्ठा kimage *image)
अणु
पूर्ण

व्योम arch_crash_save_vmcoreinfo(व्योम)
अणु

#अगर_घोषित CONFIG_NEED_MULTIPLE_NODES
	VMCOREINFO_SYMBOL(node_data);
	VMCOREINFO_LENGTH(node_data, MAX_NUMNODES);
#पूर्ण_अगर
#अगर_अघोषित CONFIG_NEED_MULTIPLE_NODES
	VMCOREINFO_SYMBOL(contig_page_data);
#पूर्ण_अगर
#अगर defined(CONFIG_PPC64) && defined(CONFIG_SPARSEMEM_VMEMMAP)
	VMCOREINFO_SYMBOL(vmemmap_list);
	VMCOREINFO_SYMBOL(mmu_vmemmap_psize);
	VMCOREINFO_SYMBOL(mmu_psize_defs);
	VMCOREINFO_STRUCT_SIZE(vmemmap_backing);
	VMCOREINFO_OFFSET(vmemmap_backing, list);
	VMCOREINFO_OFFSET(vmemmap_backing, phys);
	VMCOREINFO_OFFSET(vmemmap_backing, virt_addr);
	VMCOREINFO_STRUCT_SIZE(mmu_psize_def);
	VMCOREINFO_OFFSET(mmu_psize_def, shअगरt);
#पूर्ण_अगर
	vmcoreinfo_append_str("KERNELOFFSET=%lx\n", kaslr_offset());
पूर्ण

/*
 * Do not allocate memory (or fail in any way) in machine_kexec().
 * We are past the poपूर्णांक of no वापस, committed to rebooting now.
 */
व्योम machine_kexec(काष्ठा kimage *image)
अणु
	पूर्णांक save_ftrace_enabled;

	save_ftrace_enabled = __ftrace_enabled_save();
	this_cpu_disable_ftrace();

	अगर (ppc_md.machine_kexec)
		ppc_md.machine_kexec(image);
	अन्यथा
		शेष_machine_kexec(image);

	this_cpu_enable_ftrace();
	__ftrace_enabled_restore(save_ftrace_enabled);

	/* Fall back to normal restart अगर we're still alive. */
	machine_restart(शून्य);
	क्रम(;;);
पूर्ण

व्योम __init reserve_crashkernel(व्योम)
अणु
	अचिन्हित दीर्घ दीर्घ crash_size, crash_base, total_mem_sz;
	पूर्णांक ret;

	total_mem_sz = memory_limit ? memory_limit : memblock_phys_mem_size();
	/* use common parsing */
	ret = parse_crashkernel(boot_command_line, total_mem_sz,
			&crash_size, &crash_base);
	अगर (ret == 0 && crash_size > 0) अणु
		crashk_res.start = crash_base;
		crashk_res.end = crash_base + crash_size - 1;
	पूर्ण

	अगर (crashk_res.end == crashk_res.start) अणु
		crashk_res.start = crashk_res.end = 0;
		वापस;
	पूर्ण

	/* We might have got these values via the command line or the
	 * device tree, either way sanitise them now. */

	crash_size = resource_size(&crashk_res);

#अगर_अघोषित CONFIG_NONSTATIC_KERNEL
	अगर (crashk_res.start != KDUMP_KERNELBASE)
		prपूर्णांकk("Crash kernel location must be 0x%x\n",
				KDUMP_KERNELBASE);

	crashk_res.start = KDUMP_KERNELBASE;
#अन्यथा
	अगर (!crashk_res.start) अणु
#अगर_घोषित CONFIG_PPC64
		/*
		 * On 64bit we split the RMO in half but cap it at half of
		 * a small SLB (128MB) since the crash kernel needs to place
		 * itself and some stacks to be in the first segment.
		 */
		crashk_res.start = min(0x8000000ULL, (ppc64_rma_size / 2));
#अन्यथा
		crashk_res.start = KDUMP_KERNELBASE;
#पूर्ण_अगर
	पूर्ण

	crash_base = PAGE_ALIGN(crashk_res.start);
	अगर (crash_base != crashk_res.start) अणु
		prपूर्णांकk("Crash kernel base must be aligned to 0x%lx\n",
				PAGE_SIZE);
		crashk_res.start = crash_base;
	पूर्ण

#पूर्ण_अगर
	crash_size = PAGE_ALIGN(crash_size);
	crashk_res.end = crashk_res.start + crash_size - 1;

	/* The crash region must not overlap the current kernel */
	अगर (overlaps_crashkernel(__pa(_stext), _end - _stext)) अणु
		prपूर्णांकk(KERN_WARNING
			"Crash kernel can not overlap current kernel\n");
		crashk_res.start = crashk_res.end = 0;
		वापस;
	पूर्ण

	/* Crash kernel trumps memory limit */
	अगर (memory_limit && memory_limit <= crashk_res.end) अणु
		memory_limit = crashk_res.end + 1;
		total_mem_sz = memory_limit;
		prपूर्णांकk("Adjusted memory limit for crashkernel, now 0x%llx\n",
		       memory_limit);
	पूर्ण

	prपूर्णांकk(KERN_INFO "Reserving %ldMB of memory at %ldMB "
			"for crashkernel (System RAM: %ldMB)\n",
			(अचिन्हित दीर्घ)(crash_size >> 20),
			(अचिन्हित दीर्घ)(crashk_res.start >> 20),
			(अचिन्हित दीर्घ)(total_mem_sz >> 20));

	अगर (!memblock_is_region_memory(crashk_res.start, crash_size) ||
	    memblock_reserve(crashk_res.start, crash_size)) अणु
		pr_err("Failed to reserve memory for crashkernel!\n");
		crashk_res.start = crashk_res.end = 0;
		वापस;
	पूर्ण
पूर्ण

पूर्णांक overlaps_crashkernel(अचिन्हित दीर्घ start, अचिन्हित दीर्घ size)
अणु
	वापस (start + size) > crashk_res.start && start <= crashk_res.end;
पूर्ण

/* Values we need to export to the second kernel via the device tree. */
अटल phys_addr_t kernel_end;
अटल phys_addr_t crashk_base;
अटल phys_addr_t crashk_size;
अटल अचिन्हित दीर्घ दीर्घ mem_limit;

अटल काष्ठा property kernel_end_prop = अणु
	.name = "linux,kernel-end",
	.length = माप(phys_addr_t),
	.value = &kernel_end,
पूर्ण;

अटल काष्ठा property crashk_base_prop = अणु
	.name = "linux,crashkernel-base",
	.length = माप(phys_addr_t),
	.value = &crashk_base
पूर्ण;

अटल काष्ठा property crashk_size_prop = अणु
	.name = "linux,crashkernel-size",
	.length = माप(phys_addr_t),
	.value = &crashk_size,
पूर्ण;

अटल काष्ठा property memory_limit_prop = अणु
	.name = "linux,memory-limit",
	.length = माप(अचिन्हित दीर्घ दीर्घ),
	.value = &mem_limit,
पूर्ण;

#घोषणा cpu_to_be_uदीर्घ	__PASTE(cpu_to_be, BITS_PER_LONG)

अटल व्योम __init export_crashk_values(काष्ठा device_node *node)
अणु
	/* There might be existing crash kernel properties, but we can't
	 * be sure what's in them, so हटाओ them. */
	of_हटाओ_property(node, of_find_property(node,
				"linux,crashkernel-base", शून्य));
	of_हटाओ_property(node, of_find_property(node,
				"linux,crashkernel-size", शून्य));

	अगर (crashk_res.start != 0) अणु
		crashk_base = cpu_to_be_uदीर्घ(crashk_res.start),
		of_add_property(node, &crashk_base_prop);
		crashk_size = cpu_to_be_uदीर्घ(resource_size(&crashk_res));
		of_add_property(node, &crashk_size_prop);
	पूर्ण

	/*
	 * memory_limit is required by the kexec-tools to limit the
	 * crash regions to the actual memory used.
	 */
	mem_limit = cpu_to_be_uदीर्घ(memory_limit);
	of_update_property(node, &memory_limit_prop);
पूर्ण

अटल पूर्णांक __init kexec_setup(व्योम)
अणु
	काष्ठा device_node *node;

	node = of_find_node_by_path("/chosen");
	अगर (!node)
		वापस -ENOENT;

	/* हटाओ any stale properties so ours can be found */
	of_हटाओ_property(node, of_find_property(node, kernel_end_prop.name, शून्य));

	/* inक्रमmation needed by userspace when using शेष_machine_kexec */
	kernel_end = cpu_to_be_uदीर्घ(__pa(_end));
	of_add_property(node, &kernel_end_prop);

	export_crashk_values(node);

	of_node_put(node);
	वापस 0;
पूर्ण
late_initcall(kexec_setup);
