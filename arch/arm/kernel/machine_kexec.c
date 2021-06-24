<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * machine_kexec.c - handle transition of Linux booting another kernel
 */

#समावेश <linux/mm.h>
#समावेश <linux/kexec.h>
#समावेश <linux/delay.h>
#समावेश <linux/reboot.h>
#समावेश <linux/पन.स>
#समावेश <linux/irq.h>
#समावेश <linux/memblock.h>
#समावेश <linux/of_fdt.h>
#समावेश <यंत्र/mmu_context.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/kexec-पूर्णांकernal.h>
#समावेश <यंत्र/fncpy.h>
#समावेश <यंत्र/mach-types.h>
#समावेश <यंत्र/smp_plat.h>
#समावेश <यंत्र/प्रणाली_misc.h>
#समावेश <यंत्र/set_memory.h>

बाह्य व्योम relocate_new_kernel(व्योम);
बाह्य स्थिर अचिन्हित पूर्णांक relocate_new_kernel_size;

अटल atomic_t रुकोing_क्रम_crash_ipi;

/*
 * Provide a dummy crash_notes definition जबतक crash dump arrives to arm.
 * This prevents अवरोधage of crash_notes attribute in kernel/ksysfs.c.
 */

पूर्णांक machine_kexec_prepare(काष्ठा kimage *image)
अणु
	काष्ठा kexec_segment *current_segment;
	__be32 header;
	पूर्णांक i, err;

	image->arch.kernel_r2 = image->start - KEXEC_ARM_ZIMAGE_OFFSET
				     + KEXEC_ARM_ATAGS_OFFSET;

	/*
	 * Validate that अगर the current HW supports SMP, then the SW supports
	 * and implements CPU hotplug क्रम the current HW. If not, we won't be
	 * able to kexec reliably, so fail the prepare operation.
	 */
	अगर (num_possible_cpus() > 1 && platक्रमm_can_secondary_boot() &&
	    !platक्रमm_can_cpu_hotplug())
		वापस -EINVAL;

	/*
	 * No segment at शेष ATAGs address. try to locate
	 * a dtb using magic.
	 */
	क्रम (i = 0; i < image->nr_segments; i++) अणु
		current_segment = &image->segment[i];

		अगर (!memblock_is_region_memory(idmap_to_phys(current_segment->mem),
					       current_segment->memsz))
			वापस -EINVAL;

		err = get_user(header, (__be32*)current_segment->buf);
		अगर (err)
			वापस err;

		अगर (header == cpu_to_be32(OF_DT_HEADER))
			image->arch.kernel_r2 = current_segment->mem;
	पूर्ण
	वापस 0;
पूर्ण

व्योम machine_kexec_cleanup(काष्ठा kimage *image)
अणु
पूर्ण

व्योम machine_crash_nonpanic_core(व्योम *unused)
अणु
	काष्ठा pt_regs regs;

	crash_setup_regs(&regs, get_irq_regs());
	prपूर्णांकk(KERN_DEBUG "CPU %u will stop doing anything useful since another CPU has crashed\n",
	       smp_processor_id());
	crash_save_cpu(&regs, smp_processor_id());
	flush_cache_all();

	set_cpu_online(smp_processor_id(), false);
	atomic_dec(&रुकोing_क्रम_crash_ipi);

	जबतक (1) अणु
		cpu_relax();
		wfe();
	पूर्ण
पूर्ण

व्योम crash_smp_send_stop(व्योम)
अणु
	अटल पूर्णांक cpus_stopped;
	अचिन्हित दीर्घ msecs;

	अगर (cpus_stopped)
		वापस;

	atomic_set(&रुकोing_क्रम_crash_ipi, num_online_cpus() - 1);
	smp_call_function(machine_crash_nonpanic_core, शून्य, false);
	msecs = 1000; /* Wait at most a second क्रम the other cpus to stop */
	जबतक ((atomic_पढ़ो(&रुकोing_क्रम_crash_ipi) > 0) && msecs) अणु
		mdelay(1);
		msecs--;
	पूर्ण
	अगर (atomic_पढ़ो(&रुकोing_क्रम_crash_ipi) > 0)
		pr_warn("Non-crashing CPUs did not react to IPI\n");

	cpus_stopped = 1;
पूर्ण

अटल व्योम machine_kexec_mask_पूर्णांकerrupts(व्योम)
अणु
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
	local_irq_disable();
	crash_smp_send_stop();

	crash_save_cpu(regs, smp_processor_id());
	machine_kexec_mask_पूर्णांकerrupts();

	pr_info("Loading crashdump kernel...\n");
पूर्ण

व्योम machine_kexec(काष्ठा kimage *image)
अणु
	अचिन्हित दीर्घ page_list, reboot_entry_phys;
	काष्ठा kexec_relocate_data *data;
	व्योम (*reboot_entry)(व्योम);
	व्योम *reboot_code_buffer;

	/*
	 * This can only happen अगर machine_shutकरोwn() failed to disable some
	 * CPU, and that can only happen अगर the checks in
	 * machine_kexec_prepare() were not correct. If this fails, we can't
	 * reliably kexec anyway, so BUG_ON is appropriate.
	 */
	BUG_ON(num_online_cpus() > 1);

	page_list = image->head & PAGE_MASK;

	reboot_code_buffer = page_address(image->control_code_page);

	/* copy our kernel relocation code to the control code page */
	reboot_entry = fncpy(reboot_code_buffer,
			     &relocate_new_kernel,
			     relocate_new_kernel_size);

	data = reboot_code_buffer + relocate_new_kernel_size;
	data->kexec_start_address = image->start;
	data->kexec_indirection_page = page_list;
	data->kexec_mach_type = machine_arch_type;
	data->kexec_r2 = image->arch.kernel_r2;

	/* get the identity mapping physical address क्रम the reboot code */
	reboot_entry_phys = virt_to_idmap(reboot_entry);

	pr_info("Bye!\n");

	soft_restart(reboot_entry_phys);
पूर्ण

व्योम arch_crash_save_vmcoreinfo(व्योम)
अणु
#अगर_घोषित CONFIG_ARM_LPAE
	VMCOREINFO_CONFIG(ARM_LPAE);
#पूर्ण_अगर
पूर्ण
