<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * machine_kexec.c - handle transition of Linux booting another kernel
 * Copyright (C) 2002-2003 Eric Biederman  <ebiederm@xmission.com>
 *
 * GameCube/ppc32 port Copyright (C) 2004 Albert Herranz
 * LANDISK/sh4 supported by kogiidena
 */
#समावेश <linux/mm.h>
#समावेश <linux/kexec.h>
#समावेश <linux/delay.h>
#समावेश <linux/reboot.h>
#समावेश <linux/numa.h>
#समावेश <linux/ftrace.h>
#समावेश <linux/suspend.h>
#समावेश <linux/memblock.h>
#समावेश <यंत्र/mmu_context.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/sh_मूलप्रण.स>
#समावेश <यंत्र/reboot.h>

प्रकार व्योम (*relocate_new_kernel_t)(अचिन्हित दीर्घ indirection_page,
				      अचिन्हित दीर्घ reboot_code_buffer,
				      अचिन्हित दीर्घ start_address);

बाह्य स्थिर अचिन्हित अक्षर relocate_new_kernel[];
बाह्य स्थिर अचिन्हित पूर्णांक relocate_new_kernel_size;
बाह्य व्योम *vbr_base;

व्योम native_machine_crash_shutकरोwn(काष्ठा pt_regs *regs)
अणु
	/* Nothing to करो क्रम UP, but definitely broken क्रम SMP.. */
पूर्ण

/*
 * Do what every setup is needed on image and the
 * reboot code buffer to allow us to aव्योम allocations
 * later.
 */
पूर्णांक machine_kexec_prepare(काष्ठा kimage *image)
अणु
	वापस 0;
पूर्ण

व्योम machine_kexec_cleanup(काष्ठा kimage *image)
अणु
पूर्ण

अटल व्योम kexec_info(काष्ठा kimage *image)
अणु
        पूर्णांक i;
	prपूर्णांकk("kexec information\n");
	क्रम (i = 0; i < image->nr_segments; i++) अणु
	        prपूर्णांकk("  segment[%d]: 0x%08x - 0x%08x (0x%08x)\n",
		       i,
		       (अचिन्हित पूर्णांक)image->segment[i].mem,
		       (अचिन्हित पूर्णांक)image->segment[i].mem +
				     image->segment[i].memsz,
		       (अचिन्हित पूर्णांक)image->segment[i].memsz);
	पूर्ण
	prपूर्णांकk("  start     : 0x%08x\n\n", (अचिन्हित पूर्णांक)image->start);
पूर्ण

/*
 * Do not allocate memory (or fail in any way) in machine_kexec().
 * We are past the poपूर्णांक of no वापस, committed to rebooting now.
 */
व्योम machine_kexec(काष्ठा kimage *image)
अणु
	अचिन्हित दीर्घ page_list;
	अचिन्हित दीर्घ reboot_code_buffer;
	relocate_new_kernel_t rnk;
	अचिन्हित दीर्घ entry;
	अचिन्हित दीर्घ *ptr;
	पूर्णांक save_ftrace_enabled;

	/*
	 * Nicked from the mips version of machine_kexec():
	 * The generic kexec code builds a page list with physical
	 * addresses. Use phys_to_virt() to convert them to भव.
	 */
	क्रम (ptr = &image->head; (entry = *ptr) && !(entry & IND_DONE);
	     ptr = (entry & IND_INसूचीECTION) ?
	       phys_to_virt(entry & PAGE_MASK) : ptr + 1) अणु
		अगर (*ptr & IND_SOURCE || *ptr & IND_INसूचीECTION ||
		    *ptr & IND_DESTINATION)
			*ptr = (अचिन्हित दीर्घ) phys_to_virt(*ptr);
	पूर्ण

#अगर_घोषित CONFIG_KEXEC_JUMP
	अगर (image->preserve_context)
		save_processor_state();
#पूर्ण_अगर

	save_ftrace_enabled = __ftrace_enabled_save();

	/* Interrupts aren't acceptable जबतक we reboot */
	local_irq_disable();

	page_list = image->head;

	/* we need both effective and real address here */
	reboot_code_buffer =
			(अचिन्हित दीर्घ)page_address(image->control_code_page);

	/* copy our kernel relocation code to the control code page */
	स_नकल((व्योम *)reboot_code_buffer, relocate_new_kernel,
						relocate_new_kernel_size);

	kexec_info(image);
	flush_cache_all();

	sh_bios_vbr_reload();

	/* now call it */
	rnk = (relocate_new_kernel_t) reboot_code_buffer;
	(*rnk)(page_list, reboot_code_buffer,
	       (अचिन्हित दीर्घ)phys_to_virt(image->start));

#अगर_घोषित CONFIG_KEXEC_JUMP
	यंत्र अस्थिर("ldc %0, vbr" : : "r" (&vbr_base) : "memory");

	अगर (image->preserve_context)
		restore_processor_state();

	/* Convert page list back to physical addresses, what a mess. */
	क्रम (ptr = &image->head; (entry = *ptr) && !(entry & IND_DONE);
	     ptr = (*ptr & IND_INसूचीECTION) ?
	       phys_to_virt(*ptr & PAGE_MASK) : ptr + 1) अणु
		अगर (*ptr & IND_SOURCE || *ptr & IND_INसूचीECTION ||
		    *ptr & IND_DESTINATION)
			*ptr = virt_to_phys(*ptr);
	पूर्ण
#पूर्ण_अगर

	__ftrace_enabled_restore(save_ftrace_enabled);
पूर्ण

व्योम arch_crash_save_vmcoreinfo(व्योम)
अणु
#अगर_घोषित CONFIG_NUMA
	VMCOREINFO_SYMBOL(node_data);
	VMCOREINFO_LENGTH(node_data, MAX_NUMNODES);
#पूर्ण_अगर
#अगर_घोषित CONFIG_X2TLB
	VMCOREINFO_CONFIG(X2TLB);
#पूर्ण_अगर
पूर्ण

व्योम __init reserve_crashkernel(व्योम)
अणु
	अचिन्हित दीर्घ दीर्घ crash_size, crash_base;
	पूर्णांक ret;

	ret = parse_crashkernel(boot_command_line, memblock_phys_mem_size(),
			&crash_size, &crash_base);
	अगर (ret == 0 && crash_size > 0) अणु
		crashk_res.start = crash_base;
		crashk_res.end = crash_base + crash_size - 1;
	पूर्ण

	अगर (crashk_res.end == crashk_res.start)
		जाओ disable;

	crash_size = PAGE_ALIGN(resource_size(&crashk_res));
	अगर (!crashk_res.start) अणु
		अचिन्हित दीर्घ max = memblock_end_of_DRAM() - memory_limit;
		crashk_res.start = memblock_phys_alloc_range(crash_size,
							     PAGE_SIZE, 0, max);
		अगर (!crashk_res.start) अणु
			pr_err("crashkernel allocation failed\n");
			जाओ disable;
		पूर्ण
	पूर्ण अन्यथा अणु
		ret = memblock_reserve(crashk_res.start, crash_size);
		अगर (unlikely(ret < 0)) अणु
			pr_err("crashkernel reservation failed - "
			       "memory is in use\n");
			जाओ disable;
		पूर्ण
	पूर्ण

	crashk_res.end = crashk_res.start + crash_size - 1;

	/*
	 * Crash kernel trumps memory limit
	 */
	अगर ((memblock_end_of_DRAM() - memory_limit) <= crashk_res.end) अणु
		memory_limit = 0;
		pr_info("Disabled memory limit for crashkernel\n");
	पूर्ण

	pr_info("Reserving %ldMB of memory at 0x%08lx "
		"for crashkernel (System RAM: %ldMB)\n",
		(अचिन्हित दीर्घ)(crash_size >> 20),
		(अचिन्हित दीर्घ)(crashk_res.start),
		(अचिन्हित दीर्घ)(memblock_phys_mem_size() >> 20));

	वापस;

disable:
	crashk_res.start = crashk_res.end = 0;
पूर्ण
