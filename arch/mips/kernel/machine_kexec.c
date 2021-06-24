<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * machine_kexec.c क्रम kexec
 * Created by <nschichan@corp.मुक्त.fr> on Thu Oct 12 15:15:06 2006
 */
#समावेश <linux/compiler.h>
#समावेश <linux/kexec.h>
#समावेश <linux/mm.h>
#समावेश <linux/delay.h>
#समावेश <linux/libfdt.h>

#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/page.h>

बाह्य स्थिर अचिन्हित अक्षर relocate_new_kernel[];
बाह्य स्थिर माप_प्रकार relocate_new_kernel_size;

बाह्य अचिन्हित दीर्घ kexec_start_address;
बाह्य अचिन्हित दीर्घ kexec_indirection_page;

अटल अचिन्हित दीर्घ reboot_code_buffer;

#अगर_घोषित CONFIG_SMP
अटल व्योम (*relocated_kexec_smp_रुको)(व्योम *);

atomic_t kexec_पढ़ोy_to_reboot = ATOMIC_INIT(0);
व्योम (*_crash_smp_send_stop)(व्योम) = शून्य;
#पूर्ण_अगर

व्योम (*_machine_kexec_shutकरोwn)(व्योम) = शून्य;
व्योम (*_machine_crash_shutकरोwn)(काष्ठा pt_regs *regs) = शून्य;

अटल व्योम kexec_image_info(स्थिर काष्ठा kimage *kimage)
अणु
	अचिन्हित दीर्घ i;

	pr_debug("kexec kimage info:\n");
	pr_debug("  type:        %d\n", kimage->type);
	pr_debug("  start:       %lx\n", kimage->start);
	pr_debug("  head:        %lx\n", kimage->head);
	pr_debug("  nr_segments: %lu\n", kimage->nr_segments);

	क्रम (i = 0; i < kimage->nr_segments; i++) अणु
		pr_debug("    segment[%lu]: %016lx - %016lx, 0x%lx bytes, %lu pages\n",
			i,
			kimage->segment[i].mem,
			kimage->segment[i].mem + kimage->segment[i].memsz,
			(अचिन्हित दीर्घ)kimage->segment[i].memsz,
			(अचिन्हित दीर्घ)kimage->segment[i].memsz /  PAGE_SIZE);
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_UHI_BOOT

अटल पूर्णांक uhi_machine_kexec_prepare(काष्ठा kimage *kimage)
अणु
	पूर्णांक i;

	/*
	 * In हाल DTB file is not passed to the new kernel, a flat device
	 * tree will be created by kexec tool. It holds modअगरied command
	 * line क्रम the new kernel.
	 */
	क्रम (i = 0; i < kimage->nr_segments; i++) अणु
		काष्ठा fdt_header fdt;

		अगर (kimage->segment[i].memsz <= माप(fdt))
			जारी;

		अगर (copy_from_user(&fdt, kimage->segment[i].buf, माप(fdt)))
			जारी;

		अगर (fdt_check_header(&fdt))
			जारी;

		kexec_args[0] = -2;
		kexec_args[1] = (अचिन्हित दीर्घ)
			phys_to_virt((अचिन्हित दीर्घ)kimage->segment[i].mem);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक (*_machine_kexec_prepare)(काष्ठा kimage *) = uhi_machine_kexec_prepare;

#अन्यथा

पूर्णांक (*_machine_kexec_prepare)(काष्ठा kimage *) = शून्य;

#पूर्ण_अगर /* CONFIG_UHI_BOOT */

पूर्णांक
machine_kexec_prepare(काष्ठा kimage *kimage)
अणु
#अगर_घोषित CONFIG_SMP
	अगर (!kexec_nonboot_cpu_func())
		वापस -EINVAL;
#पूर्ण_अगर

	kexec_image_info(kimage);

	अगर (_machine_kexec_prepare)
		वापस _machine_kexec_prepare(kimage);

	वापस 0;
पूर्ण

व्योम
machine_kexec_cleanup(काष्ठा kimage *kimage)
अणु
पूर्ण

#अगर_घोषित CONFIG_SMP
अटल व्योम kexec_shutकरोwn_secondary(व्योम *param)
अणु
	पूर्णांक cpu = smp_processor_id();

	अगर (!cpu_online(cpu))
		वापस;

	/* We won't be sent IPIs any more. */
	set_cpu_online(cpu, false);

	local_irq_disable();
	जबतक (!atomic_पढ़ो(&kexec_पढ़ोy_to_reboot))
		cpu_relax();

	kexec_reboot();

	/* NOTREACHED */
पूर्ण
#पूर्ण_अगर

व्योम
machine_shutकरोwn(व्योम)
अणु
	अगर (_machine_kexec_shutकरोwn)
		_machine_kexec_shutकरोwn();

#अगर_घोषित CONFIG_SMP
	smp_call_function(kexec_shutकरोwn_secondary, शून्य, 0);

	जबतक (num_online_cpus() > 1) अणु
		cpu_relax();
		mdelay(1);
	पूर्ण
#पूर्ण_अगर
पूर्ण

व्योम
machine_crash_shutकरोwn(काष्ठा pt_regs *regs)
अणु
	अगर (_machine_crash_shutकरोwn)
		_machine_crash_shutकरोwn(regs);
	अन्यथा
		शेष_machine_crash_shutकरोwn(regs);
पूर्ण

#अगर_घोषित CONFIG_SMP
व्योम kexec_nonboot_cpu_jump(व्योम)
अणु
	local_flush_icache_range((अचिन्हित दीर्घ)relocated_kexec_smp_रुको,
				 reboot_code_buffer + relocate_new_kernel_size);

	relocated_kexec_smp_रुको(शून्य);
पूर्ण
#पूर्ण_अगर

व्योम kexec_reboot(व्योम)
अणु
	व्योम (*करो_kexec)(व्योम) __noवापस;

	/*
	 * We know we were online, and there will be no incoming IPIs at
	 * this poपूर्णांक. Mark online again beक्रमe rebooting so that the crash
	 * analysis tool will see us correctly.
	 */
	set_cpu_online(smp_processor_id(), true);

	/* Ensure remote CPUs observe that we're online beक्रमe rebooting. */
	smp_mb__after_atomic();

#अगर_घोषित CONFIG_SMP
	अगर (smp_processor_id() > 0) अणु
		/*
		 * Instead of cpu_relax() or रुको, this is needed क्रम kexec
		 * smp reboot. Kdump usually करोesn't require an smp new
		 * kernel, but kexec may करो.
		 */
		kexec_nonboot_cpu();

		/* NOTREACHED */
	पूर्ण
#पूर्ण_अगर

	/*
	 * Make sure we get correct inकाष्ठाions written by the
	 * machine_kexec() CPU.
	 */
	local_flush_icache_range(reboot_code_buffer,
				 reboot_code_buffer + relocate_new_kernel_size);

	करो_kexec = (व्योम *)reboot_code_buffer;
	करो_kexec();
पूर्ण

व्योम
machine_kexec(काष्ठा kimage *image)
अणु
	अचिन्हित दीर्घ entry;
	अचिन्हित दीर्घ *ptr;

	reboot_code_buffer =
	  (अचिन्हित दीर्घ)page_address(image->control_code_page);

	kexec_start_address =
		(अचिन्हित दीर्घ) phys_to_virt(image->start);

	अगर (image->type == KEXEC_TYPE_DEFAULT) अणु
		kexec_indirection_page =
			(अचिन्हित दीर्घ) phys_to_virt(image->head & PAGE_MASK);
	पूर्ण अन्यथा अणु
		kexec_indirection_page = (अचिन्हित दीर्घ)&image->head;
	पूर्ण

	स_नकल((व्योम*)reboot_code_buffer, relocate_new_kernel,
	       relocate_new_kernel_size);

	/*
	 * The generic kexec code builds a page list with physical
	 * addresses. they are directly accessible through KSEG0 (or
	 * CKSEG0 or XPHYS अगर on 64bit प्रणाली), hence the
	 * phys_to_virt() call.
	 */
	क्रम (ptr = &image->head; (entry = *ptr) && !(entry &IND_DONE);
	     ptr = (entry & IND_INसूचीECTION) ?
	       phys_to_virt(entry & PAGE_MASK) : ptr + 1) अणु
		अगर (*ptr & IND_SOURCE || *ptr & IND_INसूचीECTION ||
		    *ptr & IND_DESTINATION)
			*ptr = (अचिन्हित दीर्घ) phys_to_virt(*ptr);
	पूर्ण

	/* Mark offline BEFORE disabling local irq. */
	set_cpu_online(smp_processor_id(), false);

	/*
	 * we करो not want to be bothered.
	 */
	local_irq_disable();

	prपूर्णांकk("Will call new kernel at %08lx\n", image->start);
	prपूर्णांकk("Bye ...\n");
	/* Make reboot code buffer available to the boot CPU. */
	__flush_cache_all();
#अगर_घोषित CONFIG_SMP
	/* All secondary cpus now may jump to kexec_रुको cycle */
	relocated_kexec_smp_रुको = reboot_code_buffer +
		(व्योम *)(kexec_smp_रुको - relocate_new_kernel);
	smp_wmb();
	atomic_set(&kexec_पढ़ोy_to_reboot, 1);
#पूर्ण_अगर
	kexec_reboot();
पूर्ण
