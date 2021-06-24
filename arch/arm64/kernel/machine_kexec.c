<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * kexec क्रम arm64
 *
 * Copyright (C) Linaro.
 * Copyright (C) Huawei Futurewei Technologies.
 */

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/kernel.h>
#समावेश <linux/kexec.h>
#समावेश <linux/page-flags.h>
#समावेश <linux/smp.h>

#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/cpu_ops.h>
#समावेश <यंत्र/daअगरflags.h>
#समावेश <यंत्र/memory.h>
#समावेश <यंत्र/mmu.h>
#समावेश <यंत्र/mmu_context.h>
#समावेश <यंत्र/page.h>

#समावेश "cpu-reset.h"

/* Global variables क्रम the arm64_relocate_new_kernel routine. */
बाह्य स्थिर अचिन्हित अक्षर arm64_relocate_new_kernel[];
बाह्य स्थिर अचिन्हित दीर्घ arm64_relocate_new_kernel_size;

/**
 * kexec_image_info - For debugging output.
 */
#घोषणा kexec_image_info(_i) _kexec_image_info(__func__, __LINE__, _i)
अटल व्योम _kexec_image_info(स्थिर अक्षर *func, पूर्णांक line,
	स्थिर काष्ठा kimage *kimage)
अणु
	अचिन्हित दीर्घ i;

	pr_debug("%s:%d:\n", func, line);
	pr_debug("  kexec kimage info:\n");
	pr_debug("    type:        %d\n", kimage->type);
	pr_debug("    start:       %lx\n", kimage->start);
	pr_debug("    head:        %lx\n", kimage->head);
	pr_debug("    nr_segments: %lu\n", kimage->nr_segments);
	pr_debug("    kern_reloc: %pa\n", &kimage->arch.kern_reloc);

	क्रम (i = 0; i < kimage->nr_segments; i++) अणु
		pr_debug("      segment[%lu]: %016lx - %016lx, 0x%lx bytes, %lu pages\n",
			i,
			kimage->segment[i].mem,
			kimage->segment[i].mem + kimage->segment[i].memsz,
			kimage->segment[i].memsz,
			kimage->segment[i].memsz /  PAGE_SIZE);
	पूर्ण
पूर्ण

व्योम machine_kexec_cleanup(काष्ठा kimage *kimage)
अणु
	/* Empty routine needed to aव्योम build errors. */
पूर्ण

पूर्णांक machine_kexec_post_load(काष्ठा kimage *kimage)
अणु
	व्योम *reloc_code = page_to_virt(kimage->control_code_page);

	स_नकल(reloc_code, arm64_relocate_new_kernel,
	       arm64_relocate_new_kernel_size);
	kimage->arch.kern_reloc = __pa(reloc_code);
	kexec_image_info(kimage);

	/* Flush the reloc_code in preparation क्रम its execution. */
	__flush_dcache_area(reloc_code, arm64_relocate_new_kernel_size);
	flush_icache_range((uपूर्णांकptr_t)reloc_code, (uपूर्णांकptr_t)reloc_code +
			   arm64_relocate_new_kernel_size);

	वापस 0;
पूर्ण

/**
 * machine_kexec_prepare - Prepare क्रम a kexec reboot.
 *
 * Called from the core kexec code when a kernel image is loaded.
 * Forbid loading a kexec kernel अगर we have no way of hotplugging cpus or cpus
 * are stuck in the kernel. This aव्योमs a panic once we hit machine_kexec().
 */
पूर्णांक machine_kexec_prepare(काष्ठा kimage *kimage)
अणु
	अगर (kimage->type != KEXEC_TYPE_CRASH && cpus_are_stuck_in_kernel()) अणु
		pr_err("Can't kexec: CPUs are stuck in the kernel.\n");
		वापस -EBUSY;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * kexec_list_flush - Helper to flush the kimage list and source pages to PoC.
 */
अटल व्योम kexec_list_flush(काष्ठा kimage *kimage)
अणु
	kimage_entry_t *entry;

	क्रम (entry = &kimage->head; ; entry++) अणु
		अचिन्हित पूर्णांक flag;
		व्योम *addr;

		/* flush the list entries. */
		__flush_dcache_area(entry, माप(kimage_entry_t));

		flag = *entry & IND_FLAGS;
		अगर (flag == IND_DONE)
			अवरोध;

		addr = phys_to_virt(*entry & PAGE_MASK);

		चयन (flag) अणु
		हाल IND_INसूचीECTION:
			/* Set entry poपूर्णांक just beक्रमe the new list page. */
			entry = (kimage_entry_t *)addr - 1;
			अवरोध;
		हाल IND_SOURCE:
			/* flush the source pages. */
			__flush_dcache_area(addr, PAGE_SIZE);
			अवरोध;
		हाल IND_DESTINATION:
			अवरोध;
		शेष:
			BUG();
		पूर्ण
	पूर्ण
पूर्ण

/**
 * kexec_segment_flush - Helper to flush the kimage segments to PoC.
 */
अटल व्योम kexec_segment_flush(स्थिर काष्ठा kimage *kimage)
अणु
	अचिन्हित दीर्घ i;

	pr_debug("%s:\n", __func__);

	क्रम (i = 0; i < kimage->nr_segments; i++) अणु
		pr_debug("  segment[%lu]: %016lx - %016lx, 0x%lx bytes, %lu pages\n",
			i,
			kimage->segment[i].mem,
			kimage->segment[i].mem + kimage->segment[i].memsz,
			kimage->segment[i].memsz,
			kimage->segment[i].memsz /  PAGE_SIZE);

		__flush_dcache_area(phys_to_virt(kimage->segment[i].mem),
			kimage->segment[i].memsz);
	पूर्ण
पूर्ण

/**
 * machine_kexec - Do the kexec reboot.
 *
 * Called from the core kexec code क्रम a sys_reboot with LINUX_REBOOT_CMD_KEXEC.
 */
व्योम machine_kexec(काष्ठा kimage *kimage)
अणु
	bool in_kexec_crash = (kimage == kexec_crash_image);
	bool stuck_cpus = cpus_are_stuck_in_kernel();

	/*
	 * New cpus may have become stuck_in_kernel after we loaded the image.
	 */
	BUG_ON(!in_kexec_crash && (stuck_cpus || (num_online_cpus() > 1)));
	WARN(in_kexec_crash && (stuck_cpus || smp_crash_stop_failed()),
		"Some CPUs may be stale, kdump will be unreliable.\n");

	/* Flush the kimage list and its buffers. */
	kexec_list_flush(kimage);

	/* Flush the new image अगर alपढ़ोy in place. */
	अगर ((kimage != kexec_crash_image) && (kimage->head & IND_DONE))
		kexec_segment_flush(kimage);

	pr_info("Bye!\n");

	local_daअगर_mask();

	/*
	 * cpu_soft_restart will shutकरोwn the MMU, disable data caches, then
	 * transfer control to the kern_reloc which contains a copy of
	 * the arm64_relocate_new_kernel routine.  arm64_relocate_new_kernel
	 * uses physical addressing to relocate the new image to its final
	 * position and transfers control to the image entry poपूर्णांक when the
	 * relocation is complete.
	 * In kexec हाल, kimage->start poपूर्णांकs to purgatory assuming that
	 * kernel entry and dtb address are embedded in purgatory by
	 * userspace (kexec-tools).
	 * In kexec_file हाल, the kernel starts directly without purgatory.
	 */
	cpu_soft_restart(kimage->arch.kern_reloc, kimage->head, kimage->start,
			 kimage->arch.dtb_mem);

	BUG(); /* Should never get here. */
पूर्ण

अटल व्योम machine_kexec_mask_पूर्णांकerrupts(व्योम)
अणु
	अचिन्हित पूर्णांक i;
	काष्ठा irq_desc *desc;

	क्रम_each_irq_desc(i, desc) अणु
		काष्ठा irq_chip *chip;
		पूर्णांक ret;

		chip = irq_desc_get_chip(desc);
		अगर (!chip)
			जारी;

		/*
		 * First try to हटाओ the active state. If this
		 * fails, try to EOI the पूर्णांकerrupt.
		 */
		ret = irq_set_irqchip_state(i, IRQCHIP_STATE_ACTIVE, false);

		अगर (ret && irqd_irq_inprogress(&desc->irq_data) &&
		    chip->irq_eoi)
			chip->irq_eoi(&desc->irq_data);

		अगर (chip->irq_mask)
			chip->irq_mask(&desc->irq_data);

		अगर (chip->irq_disable && !irqd_irq_disabled(&desc->irq_data))
			chip->irq_disable(&desc->irq_data);
	पूर्ण
पूर्ण

/**
 * machine_crash_shutकरोwn - shutकरोwn non-crashing cpus and save रेजिस्टरs
 */
व्योम machine_crash_shutकरोwn(काष्ठा pt_regs *regs)
अणु
	local_irq_disable();

	/* shutकरोwn non-crashing cpus */
	crash_smp_send_stop();

	/* क्रम crashing cpu */
	crash_save_cpu(regs, smp_processor_id());
	machine_kexec_mask_पूर्णांकerrupts();

	pr_info("Starting crashdump kernel...\n");
पूर्ण

व्योम arch_kexec_protect_crashkres(व्योम)
अणु
	पूर्णांक i;

	kexec_segment_flush(kexec_crash_image);

	क्रम (i = 0; i < kexec_crash_image->nr_segments; i++)
		set_memory_valid(
			__phys_to_virt(kexec_crash_image->segment[i].mem),
			kexec_crash_image->segment[i].memsz >> PAGE_SHIFT, 0);
पूर्ण

व्योम arch_kexec_unprotect_crashkres(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < kexec_crash_image->nr_segments; i++)
		set_memory_valid(
			__phys_to_virt(kexec_crash_image->segment[i].mem),
			kexec_crash_image->segment[i].memsz >> PAGE_SHIFT, 1);
पूर्ण

#अगर_घोषित CONFIG_HIBERNATION
/*
 * To preserve the crash dump kernel image, the relevant memory segments
 * should be mapped again around the hibernation.
 */
व्योम crash_prepare_suspend(व्योम)
अणु
	अगर (kexec_crash_image)
		arch_kexec_unprotect_crashkres();
पूर्ण

व्योम crash_post_resume(व्योम)
अणु
	अगर (kexec_crash_image)
		arch_kexec_protect_crashkres();
पूर्ण

/*
 * crash_is_nosave
 *
 * Return true only अगर a page is part of reserved memory क्रम crash dump kernel,
 * but करोes not hold any data of loaded kernel image.
 *
 * Note that all the pages in crash dump kernel memory have been initially
 * marked as Reserved as memory was allocated via memblock_reserve().
 *
 * In hibernation, the pages which are Reserved and yet "nosave" are excluded
 * from the hibernation iamge. crash_is_nosave() करोes thich check क्रम crash
 * dump kernel and will reduce the total size of hibernation image.
 */

bool crash_is_nosave(अचिन्हित दीर्घ pfn)
अणु
	पूर्णांक i;
	phys_addr_t addr;

	अगर (!crashk_res.end)
		वापस false;

	/* in reserved memory? */
	addr = __pfn_to_phys(pfn);
	अगर ((addr < crashk_res.start) || (crashk_res.end < addr))
		वापस false;

	अगर (!kexec_crash_image)
		वापस true;

	/* not part of loaded kernel image? */
	क्रम (i = 0; i < kexec_crash_image->nr_segments; i++)
		अगर (addr >= kexec_crash_image->segment[i].mem &&
				addr < (kexec_crash_image->segment[i].mem +
					kexec_crash_image->segment[i].memsz))
			वापस false;

	वापस true;
पूर्ण

व्योम crash_मुक्त_reserved_phys_range(अचिन्हित दीर्घ begin, अचिन्हित दीर्घ end)
अणु
	अचिन्हित दीर्घ addr;
	काष्ठा page *page;

	क्रम (addr = begin; addr < end; addr += PAGE_SIZE) अणु
		page = phys_to_page(addr);
		मुक्त_reserved_page(page);
	पूर्ण
पूर्ण
#पूर्ण_अगर /* CONFIG_HIBERNATION */
