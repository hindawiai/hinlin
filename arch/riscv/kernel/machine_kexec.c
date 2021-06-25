<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2019 FORTH-ICS/CARV
 *  Nick Kossअगरidis <mick@ics.क्रमth.gr>
 */

#समावेश <linux/kexec.h>
#समावेश <यंत्र/kexec.h>		/* For riscv_kexec_* symbol defines */
#समावेश <linux/smp.h>		/* For smp_send_stop () */
#समावेश <यंत्र/cacheflush.h>	/* For local_flush_icache_all() */
#समावेश <यंत्र/barrier.h>	/* For smp_wmb() */
#समावेश <यंत्र/page.h>		/* For PAGE_MASK */
#समावेश <linux/libfdt.h>	/* For fdt_check_header() */
#समावेश <यंत्र/set_memory.h>	/* For set_memory_x() */
#समावेश <linux/compiler.h>	/* For unreachable() */
#समावेश <linux/cpu.h>		/* For cpu_करोwn() */
#समावेश <linux/reboot.h>

/*
 * kexec_image_info - Prपूर्णांक received image details
 */
अटल व्योम
kexec_image_info(स्थिर काष्ठा kimage *image)
अणु
	अचिन्हित दीर्घ i;

	pr_debug("Kexec image info:\n");
	pr_debug("\ttype:        %d\n", image->type);
	pr_debug("\tstart:       %lx\n", image->start);
	pr_debug("\thead:        %lx\n", image->head);
	pr_debug("\tnr_segments: %lu\n", image->nr_segments);

	क्रम (i = 0; i < image->nr_segments; i++) अणु
		pr_debug("\t    segment[%lu]: %016lx - %016lx", i,
			image->segment[i].mem,
			image->segment[i].mem + image->segment[i].memsz);
		pr_debug("\t\t0x%lx bytes, %lu pages\n",
			(अचिन्हित दीर्घ) image->segment[i].memsz,
			(अचिन्हित दीर्घ) image->segment[i].memsz /  PAGE_SIZE);
	पूर्ण
पूर्ण

/*
 * machine_kexec_prepare - Initialize kexec
 *
 * This function is called from करो_kexec_load, when the user has
 * provided us with an image to be loaded. Its goal is to validate
 * the image and prepare the control code buffer as needed.
 * Note that kimage_alloc_init has alपढ़ोy been called and the
 * control buffer has alपढ़ोy been allocated.
 */
पूर्णांक
machine_kexec_prepare(काष्ठा kimage *image)
अणु
	काष्ठा kimage_arch *पूर्णांकernal = &image->arch;
	काष्ठा fdt_header fdt = अणु0पूर्ण;
	व्योम *control_code_buffer = शून्य;
	अचिन्हित पूर्णांक control_code_buffer_sz = 0;
	पूर्णांक i = 0;

	kexec_image_info(image);

	/* Find the Flattened Device Tree and save its physical address */
	क्रम (i = 0; i < image->nr_segments; i++) अणु
		अगर (image->segment[i].memsz <= माप(fdt))
			जारी;

		अगर (copy_from_user(&fdt, image->segment[i].buf, माप(fdt)))
			जारी;

		अगर (fdt_check_header(&fdt))
			जारी;

		पूर्णांकernal->fdt_addr = (अचिन्हित दीर्घ) image->segment[i].mem;
		अवरोध;
	पूर्ण

	अगर (!पूर्णांकernal->fdt_addr) अणु
		pr_err("Device tree not included in the provided image\n");
		वापस -EINVAL;
	पूर्ण

	/* Copy the assembler code क्रम relocation to the control page */
	अगर (image->type != KEXEC_TYPE_CRASH) अणु
		control_code_buffer = page_address(image->control_code_page);
		control_code_buffer_sz = page_size(image->control_code_page);

		अगर (unlikely(riscv_kexec_relocate_size > control_code_buffer_sz)) अणु
			pr_err("Relocation code doesn't fit within a control page\n");
			वापस -EINVAL;
		पूर्ण

		स_नकल(control_code_buffer, riscv_kexec_relocate,
			riscv_kexec_relocate_size);

		/* Mark the control page executable */
		set_memory_x((अचिन्हित दीर्घ) control_code_buffer, 1);
	पूर्ण

	वापस 0;
पूर्ण


/*
 * machine_kexec_cleanup - Cleanup any leftovers from
 *			   machine_kexec_prepare
 *
 * This function is called by kimage_मुक्त to handle any arch-specअगरic
 * allocations करोne on machine_kexec_prepare. Since we didn't करो any
 * allocations there, this is just an empty function. Note that the
 * control buffer is मुक्तd by kimage_मुक्त.
 */
व्योम
machine_kexec_cleanup(काष्ठा kimage *image)
अणु
पूर्ण


/*
 * machine_shutकरोwn - Prepare क्रम a kexec reboot
 *
 * This function is called by kernel_kexec just beक्रमe machine_kexec
 * below. Its goal is to prepare the rest of the प्रणाली (the other
 * harts and possibly devices etc) क्रम a kexec reboot.
 */
व्योम machine_shutकरोwn(व्योम)
अणु
	/*
	 * No more पूर्णांकerrupts on this hart
	 * until we are back up.
	 */
	local_irq_disable();

#अगर defined(CONFIG_HOTPLUG_CPU)
	smp_shutकरोwn_nonboot_cpus(smp_processor_id());
#पूर्ण_अगर
पूर्ण

/*
 * machine_crash_shutकरोwn - Prepare to kexec after a kernel crash
 *
 * This function is called by crash_kexec just beक्रमe machine_kexec
 * below and its goal is similar to machine_shutकरोwn, but in हाल of
 * a kernel crash. Since we करोn't handle such हालs yet, this function
 * is empty.
 */
व्योम
machine_crash_shutकरोwn(काष्ठा pt_regs *regs)
अणु
	crash_save_cpu(regs, smp_processor_id());
	machine_shutकरोwn();
	pr_info("Starting crashdump kernel...\n");
पूर्ण

/*
 * machine_kexec - Jump to the loaded kimage
 *
 * This function is called by kernel_kexec which is called by the
 * reboot प्रणाली call when the reboot cmd is LINUX_REBOOT_CMD_KEXEC,
 * or by crash_kernel which is called by the kernel's arch-specअगरic
 * trap handler in हाल of a kernel panic. It's the final stage of
 * the kexec process where the pre-loaded kimage is पढ़ोy to be
 * executed. We assume at this poपूर्णांक that all other harts are
 * suspended and this hart will be the new boot hart.
 */
व्योम __noवापस
machine_kexec(काष्ठा kimage *image)
अणु
	काष्ठा kimage_arch *पूर्णांकernal = &image->arch;
	अचिन्हित दीर्घ jump_addr = (अचिन्हित दीर्घ) image->start;
	अचिन्हित दीर्घ first_ind_entry = (अचिन्हित दीर्घ) &image->head;
	अचिन्हित दीर्घ this_hart_id = raw_smp_processor_id();
	अचिन्हित दीर्घ fdt_addr = पूर्णांकernal->fdt_addr;
	व्योम *control_code_buffer = page_address(image->control_code_page);
	riscv_kexec_method kexec_method = शून्य;

	अगर (image->type != KEXEC_TYPE_CRASH)
		kexec_method = control_code_buffer;
	अन्यथा
		kexec_method = (riscv_kexec_method) &riscv_kexec_norelocate;

	pr_notice("Will call new kernel at %08lx from hart id %lx\n",
		  jump_addr, this_hart_id);
	pr_notice("FDT image at %08lx\n", fdt_addr);

	/* Make sure the relocation code is visible to the hart */
	local_flush_icache_all();

	/* Jump to the relocation code */
	pr_notice("Bye...\n");
	kexec_method(first_ind_entry, jump_addr, fdt_addr,
		     this_hart_id, va_pa_offset);
	unreachable();
पूर्ण
