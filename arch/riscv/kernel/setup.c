<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2009 Sunplus Core Technology Co., Ltd.
 *  Chen Liqin <liqin.chen@sunplusct.com>
 *  Lennox Wu <lennox.wu@sunplusct.com>
 * Copyright (C) 2012 Regents of the University of Calअगरornia
 * Copyright (C) 2020 FORTH-ICS/CARV
 *  Nick Kossअगरidis <mick@ics.क्रमth.gr>
 */

#समावेश <linux/init.h>
#समावेश <linux/mm.h>
#समावेश <linux/memblock.h>
#समावेश <linux/sched.h>
#समावेश <linux/console.h>
#समावेश <linux/screen_info.h>
#समावेश <linux/of_fdt.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/sched/task.h>
#समावेश <linux/swiotlb.h>
#समावेश <linux/smp.h>
#समावेश <linux/efi.h>
#समावेश <linux/crash_dump.h>

#समावेश <यंत्र/cpu_ops.h>
#समावेश <यंत्र/early_ioremap.h>
#समावेश <यंत्र/pgtable.h>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/set_memory.h>
#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/sbi.h>
#समावेश <यंत्र/tlbflush.h>
#समावेश <यंत्र/thपढ़ो_info.h>
#समावेश <यंत्र/kasan.h>
#समावेश <यंत्र/efi.h>

#समावेश "head.h"

#अगर defined(CONFIG_DUMMY_CONSOLE) || defined(CONFIG_EFI)
काष्ठा screen_info screen_info __section(".data") = अणु
	.orig_video_lines	= 30,
	.orig_video_cols	= 80,
	.orig_video_mode	= 0,
	.orig_video_ega_bx	= 0,
	.orig_video_isVGA	= 1,
	.orig_video_poपूर्णांकs	= 8
पूर्ण;
#पूर्ण_अगर

/*
 * The lucky hart to first increment this variable will boot the other cores.
 * This is used beक्रमe the kernel initializes the BSS so it can't be in the
 * BSS.
 */
atomic_t hart_lottery __section(".sdata")
#अगर_घोषित CONFIG_XIP_KERNEL
= ATOMIC_INIT(0xC001BEEF)
#पूर्ण_अगर
;
अचिन्हित दीर्घ boot_cpu_hartid;
अटल DEFINE_PER_CPU(काष्ठा cpu, cpu_devices);

/*
 * Place kernel memory regions on the resource tree so that
 * kexec-tools can retrieve them from /proc/iomem. While there
 * also add "System RAM" regions क्रम compatibility with other
 * archs, and the rest of the known regions क्रम completeness.
 */
अटल काष्ठा resource kimage_res = अणु .name = "Kernel image", पूर्ण;
अटल काष्ठा resource code_res = अणु .name = "Kernel code", पूर्ण;
अटल काष्ठा resource data_res = अणु .name = "Kernel data", पूर्ण;
अटल काष्ठा resource rodata_res = अणु .name = "Kernel rodata", पूर्ण;
अटल काष्ठा resource bss_res = अणु .name = "Kernel bss", पूर्ण;
#अगर_घोषित CONFIG_CRASH_DUMP
अटल काष्ठा resource elfcorehdr_res = अणु .name = "ELF Core hdr", पूर्ण;
#पूर्ण_अगर

अटल पूर्णांक __init add_resource(काष्ठा resource *parent,
				काष्ठा resource *res)
अणु
	पूर्णांक ret = 0;

	ret = insert_resource(parent, res);
	अगर (ret < 0) अणु
		pr_err("Failed to add a %s resource at %llx\n",
			res->name, (अचिन्हित दीर्घ दीर्घ) res->start);
		वापस ret;
	पूर्ण

	वापस 1;
पूर्ण

अटल पूर्णांक __init add_kernel_resources(व्योम)
अणु
	पूर्णांक ret = 0;

	/*
	 * The memory region of the kernel image is continuous and
	 * was reserved on setup_booपंचांगem, रेजिस्टर it here as a
	 * resource, with the various segments of the image as
	 * child nodes.
	 */

	code_res.start = __pa_symbol(_text);
	code_res.end = __pa_symbol(_etext) - 1;
	code_res.flags = IORESOURCE_SYSTEM_RAM | IORESOURCE_BUSY;

	rodata_res.start = __pa_symbol(__start_rodata);
	rodata_res.end = __pa_symbol(__end_rodata) - 1;
	rodata_res.flags = IORESOURCE_SYSTEM_RAM | IORESOURCE_BUSY;

	data_res.start = __pa_symbol(_data);
	data_res.end = __pa_symbol(_edata) - 1;
	data_res.flags = IORESOURCE_SYSTEM_RAM | IORESOURCE_BUSY;

	bss_res.start = __pa_symbol(__bss_start);
	bss_res.end = __pa_symbol(__bss_stop) - 1;
	bss_res.flags = IORESOURCE_SYSTEM_RAM | IORESOURCE_BUSY;

	kimage_res.start = code_res.start;
	kimage_res.end = bss_res.end;
	kimage_res.flags = IORESOURCE_SYSTEM_RAM | IORESOURCE_BUSY;

	ret = add_resource(&iomem_resource, &kimage_res);
	अगर (ret < 0)
		वापस ret;

	ret = add_resource(&kimage_res, &code_res);
	अगर (ret < 0)
		वापस ret;

	ret = add_resource(&kimage_res, &rodata_res);
	अगर (ret < 0)
		वापस ret;

	ret = add_resource(&kimage_res, &data_res);
	अगर (ret < 0)
		वापस ret;

	ret = add_resource(&kimage_res, &bss_res);

	वापस ret;
पूर्ण

अटल व्योम __init init_resources(व्योम)
अणु
	काष्ठा memblock_region *region = शून्य;
	काष्ठा resource *res = शून्य;
	काष्ठा resource *mem_res = शून्य;
	माप_प्रकार mem_res_sz = 0;
	पूर्णांक num_resources = 0, res_idx = 0;
	पूर्णांक ret = 0;

	/* + 1 as memblock_alloc() might increase memblock.reserved.cnt */
	num_resources = memblock.memory.cnt + memblock.reserved.cnt + 1;
	res_idx = num_resources - 1;

	mem_res_sz = num_resources * माप(*mem_res);
	mem_res = memblock_alloc(mem_res_sz, SMP_CACHE_BYTES);
	अगर (!mem_res)
		panic("%s: Failed to allocate %zu bytes\n", __func__, mem_res_sz);

	/*
	 * Start by adding the reserved regions, अगर they overlap
	 * with /memory regions, insert_resource later on will take
	 * care of it.
	 */
	ret = add_kernel_resources();
	अगर (ret < 0)
		जाओ error;

#अगर_घोषित CONFIG_KEXEC_CORE
	अगर (crashk_res.start != crashk_res.end) अणु
		ret = add_resource(&iomem_resource, &crashk_res);
		अगर (ret < 0)
			जाओ error;
	पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_CRASH_DUMP
	अगर (elfcorehdr_size > 0) अणु
		elfcorehdr_res.start = elfcorehdr_addr;
		elfcorehdr_res.end = elfcorehdr_addr + elfcorehdr_size - 1;
		elfcorehdr_res.flags = IORESOURCE_SYSTEM_RAM | IORESOURCE_BUSY;
		add_resource(&iomem_resource, &elfcorehdr_res);
	पूर्ण
#पूर्ण_अगर

	क्रम_each_reserved_mem_region(region) अणु
		res = &mem_res[res_idx--];

		res->name = "Reserved";
		res->flags = IORESOURCE_MEM | IORESOURCE_BUSY;
		res->start = __pfn_to_phys(memblock_region_reserved_base_pfn(region));
		res->end = __pfn_to_phys(memblock_region_reserved_end_pfn(region)) - 1;

		/*
		 * Ignore any other reserved regions within
		 * प्रणाली memory.
		 */
		अगर (memblock_is_memory(res->start)) अणु
			/* Re-use this pre-allocated resource */
			res_idx++;
			जारी;
		पूर्ण

		ret = add_resource(&iomem_resource, res);
		अगर (ret < 0)
			जाओ error;
	पूर्ण

	/* Add /memory regions to the resource tree */
	क्रम_each_mem_region(region) अणु
		res = &mem_res[res_idx--];

		अगर (unlikely(memblock_is_nomap(region))) अणु
			res->name = "Reserved";
			res->flags = IORESOURCE_MEM | IORESOURCE_BUSY;
		पूर्ण अन्यथा अणु
			res->name = "System RAM";
			res->flags = IORESOURCE_SYSTEM_RAM | IORESOURCE_BUSY;
		पूर्ण

		res->start = __pfn_to_phys(memblock_region_memory_base_pfn(region));
		res->end = __pfn_to_phys(memblock_region_memory_end_pfn(region)) - 1;

		ret = add_resource(&iomem_resource, res);
		अगर (ret < 0)
			जाओ error;
	पूर्ण

	/* Clean-up any unused pre-allocated resources */
	mem_res_sz = (num_resources - res_idx + 1) * माप(*mem_res);
	memblock_मुक्त(__pa(mem_res), mem_res_sz);
	वापस;

 error:
	/* Better an empty resource tree than an inconsistent one */
	release_child_resources(&iomem_resource);
	memblock_मुक्त(__pa(mem_res), mem_res_sz);
पूर्ण


अटल व्योम __init parse_dtb(व्योम)
अणु
	/* Early scan of device tree from init memory */
	अगर (early_init_dt_scan(dtb_early_va)) अणु
		स्थिर अक्षर *name = of_flat_dt_get_machine_name();

		अगर (name) अणु
			pr_info("Machine model: %s\n", name);
			dump_stack_set_arch_desc("%s (DT)", name);
		पूर्ण
		वापस;
	पूर्ण

	pr_err("No DTB passed to the kernel\n");
#अगर_घोषित CONFIG_CMDLINE_FORCE
	strlcpy(boot_command_line, CONFIG_CMDLINE, COMMAND_LINE_SIZE);
	pr_info("Forcing kernel command line to: %s\n", boot_command_line);
#पूर्ण_अगर
पूर्ण

व्योम __init setup_arch(अक्षर **cmdline_p)
अणु
	parse_dtb();
	init_mm.start_code = (अचिन्हित दीर्घ) _stext;
	init_mm.end_code   = (अचिन्हित दीर्घ) _etext;
	init_mm.end_data   = (अचिन्हित दीर्घ) _edata;
	init_mm.brk        = (अचिन्हित दीर्घ) _end;

	*cmdline_p = boot_command_line;

	early_ioremap_setup();
	jump_label_init();
	parse_early_param();

	efi_init();
	setup_booपंचांगem();
	paging_init();
#अगर IS_ENABLED(CONFIG_BUILTIN_DTB)
	unflatten_and_copy_device_tree();
#अन्यथा
	अगर (early_init_dt_verअगरy(__va(XIP_FIXUP(dtb_early_pa))))
		unflatten_device_tree();
	अन्यथा
		pr_err("No DTB found in kernel mappings\n");
#पूर्ण_अगर
	misc_mem_init();

	init_resources();
	sbi_init();

	अगर (IS_ENABLED(CONFIG_STRICT_KERNEL_RWX)) अणु
		protect_kernel_text_data();
		protect_kernel_linear_mapping_text_rodata();
	पूर्ण

#अगर_घोषित CONFIG_SWIOTLB
	swiotlb_init(1);
#पूर्ण_अगर

#अगर_घोषित CONFIG_KASAN
	kasan_init();
#पूर्ण_अगर

#अगर_घोषित CONFIG_SMP
	setup_smp();
#पूर्ण_अगर

	riscv_fill_hwcap();
पूर्ण

अटल पूर्णांक __init topology_init(व्योम)
अणु
	पूर्णांक i, ret;

	क्रम_each_online_node(i)
		रेजिस्टर_one_node(i);

	क्रम_each_possible_cpu(i) अणु
		काष्ठा cpu *cpu = &per_cpu(cpu_devices, i);

		cpu->hotpluggable = cpu_has_hotplug(i);
		ret = रेजिस्टर_cpu(cpu, i);
		अगर (unlikely(ret))
			pr_warn("Warning: %s: register_cpu %d failed (%d)\n",
			       __func__, i, ret);
	पूर्ण

	वापस 0;
पूर्ण
subsys_initcall(topology_init);

व्योम मुक्त_iniपंचांगem(व्योम)
अणु
	अचिन्हित दीर्घ init_begin = (अचिन्हित दीर्घ)__init_begin;
	अचिन्हित दीर्घ init_end = (अचिन्हित दीर्घ)__init_end;

	अगर (IS_ENABLED(CONFIG_STRICT_KERNEL_RWX))
		set_memory_rw_nx(init_begin, (init_end - init_begin) >> PAGE_SHIFT);

	मुक्त_iniपंचांगem_शेष(POISON_FREE_INITMEM);
पूर्ण
