<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright IBM Corp. 2005, 2011
 *
 * Author(s): Rolf Adelsberger,
 *	      Heiko Carstens <heiko.carstens@de.ibm.com>
 *	      Michael Holzheu <holzheu@linux.vnet.ibm.com>
 */

#समावेश <linux/device.h>
#समावेश <linux/mm.h>
#समावेश <linux/kexec.h>
#समावेश <linux/delay.h>
#समावेश <linux/reboot.h>
#समावेश <linux/ftrace.h>
#समावेश <linux/debug_locks.h>
#समावेश <यंत्र/cपन.स>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/smp.h>
#समावेश <यंत्र/ipl.h>
#समावेश <यंत्र/diag.h>
#समावेश <यंत्र/elf.h>
#समावेश <यंत्र/यंत्र-offsets.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/os_info.h>
#समावेश <यंत्र/set_memory.h>
#समावेश <यंत्र/stacktrace.h>
#समावेश <यंत्र/चयन_to.h>
#समावेश <यंत्र/nmi.h>

प्रकार व्योम (*relocate_kernel_t)(kimage_entry_t *, अचिन्हित दीर्घ);

बाह्य स्थिर अचिन्हित अक्षर relocate_kernel[];
बाह्य स्थिर अचिन्हित दीर्घ दीर्घ relocate_kernel_len;

#अगर_घोषित CONFIG_CRASH_DUMP

/*
 * Reset the प्रणाली, copy boot CPU रेजिस्टरs to असलolute zero,
 * and jump to the kdump image
 */
अटल व्योम __करो_machine_kdump(व्योम *image)
अणु
	पूर्णांक (*start_kdump)(पूर्णांक);
	अचिन्हित दीर्घ prefix;

	/* store_status() saved the prefix रेजिस्टर to lowcore */
	prefix = (अचिन्हित दीर्घ) S390_lowcore.prefixreg_save_area;

	/* Now करो the reset  */
	s390_reset_प्रणाली();

	/*
	 * Copy dump CPU store status info to असलolute zero.
	 * This need to be करोne *after* s390_reset_प्रणाली set the
	 * prefix रेजिस्टर of this CPU to zero
	 */
	स_नकल((व्योम *) __LC_FPREGS_SAVE_AREA,
	       (व्योम *)(prefix + __LC_FPREGS_SAVE_AREA), 512);

	__load_psw_mask(PSW_MASK_BASE | PSW_DEFAULT_KEY | PSW_MASK_EA | PSW_MASK_BA);
	start_kdump = (व्योम *)((काष्ठा kimage *) image)->start;
	start_kdump(1);

	/* Die अगर start_kdump वापसs */
	disabled_रुको();
पूर्ण

/*
 * Start kdump: create a LGR log entry, store status of all CPUs and
 * branch to __करो_machine_kdump.
 */
अटल noअंतरभूत व्योम __machine_kdump(व्योम *image)
अणु
	काष्ठा mcesa *mcesa;
	जोड़ ctlreg2 cr2_old, cr2_new;
	पूर्णांक this_cpu, cpu;

	lgr_info_log();
	/* Get status of the other CPUs */
	this_cpu = smp_find_processor_id(stap());
	क्रम_each_online_cpu(cpu) अणु
		अगर (cpu == this_cpu)
			जारी;
		अगर (smp_store_status(cpu))
			जारी;
	पूर्ण
	/* Store status of the boot CPU */
	mcesa = (काष्ठा mcesa *)(S390_lowcore.mcesad & MCESA_ORIGIN_MASK);
	अगर (MACHINE_HAS_VX)
		save_vx_regs((__vector128 *) mcesa->vector_save_area);
	अगर (MACHINE_HAS_GS) अणु
		__ctl_store(cr2_old.val, 2, 2);
		cr2_new = cr2_old;
		cr2_new.gse = 1;
		__ctl_load(cr2_new.val, 2, 2);
		save_gs_cb((काष्ठा gs_cb *) mcesa->guarded_storage_save_area);
		__ctl_load(cr2_old.val, 2, 2);
	पूर्ण
	/*
	 * To create a good backchain क्रम this CPU in the dump store_status
	 * is passed the address of a function. The address is saved पूर्णांकo
	 * the PSW save area of the boot CPU and the function is invoked as
	 * a tail call of store_status. The backchain in the dump will look
	 * like this:
	 *   restart_पूर्णांक_handler ->  __machine_kexec -> __करो_machine_kdump
	 * The call to store_status() will not वापस.
	 */
	store_status(__करो_machine_kdump, image);
पूर्ण

अटल अचिन्हित दीर्घ करो_start_kdump(अचिन्हित दीर्घ addr)
अणु
	काष्ठा kimage *image = (काष्ठा kimage *) addr;
	पूर्णांक (*start_kdump)(पूर्णांक) = (व्योम *)image->start;
	पूर्णांक rc;

	__arch_local_irq_stnsm(0xfb); /* disable DAT */
	rc = start_kdump(0);
	__arch_local_irq_stosm(0x04); /* enable DAT */
	वापस rc;
पूर्ण

#पूर्ण_अगर /* CONFIG_CRASH_DUMP */

/*
 * Check अगर kdump checksums are valid: We call purgatory with parameter "0"
 */
अटल bool kdump_csum_valid(काष्ठा kimage *image)
अणु
#अगर_घोषित CONFIG_CRASH_DUMP
	पूर्णांक rc;

	preempt_disable();
	rc = CALL_ON_STACK(करो_start_kdump, S390_lowcore.nodat_stack, 1, image);
	preempt_enable();
	वापस rc == 0;
#अन्यथा
	वापस false;
#पूर्ण_अगर
पूर्ण

#अगर_घोषित CONFIG_CRASH_DUMP

व्योम crash_मुक्त_reserved_phys_range(अचिन्हित दीर्घ begin, अचिन्हित दीर्घ end)
अणु
	अचिन्हित दीर्घ addr, size;

	क्रम (addr = begin; addr < end; addr += PAGE_SIZE)
		मुक्त_reserved_page(pfn_to_page(addr >> PAGE_SHIFT));
	size = begin - crashk_res.start;
	अगर (size)
		os_info_crashkernel_add(crashk_res.start, size);
	अन्यथा
		os_info_crashkernel_add(0, 0);
पूर्ण

अटल व्योम crash_protect_pages(पूर्णांक protect)
अणु
	अचिन्हित दीर्घ size;

	अगर (!crashk_res.end)
		वापस;
	size = resource_size(&crashk_res);
	अगर (protect)
		set_memory_ro(crashk_res.start, size >> PAGE_SHIFT);
	अन्यथा
		set_memory_rw(crashk_res.start, size >> PAGE_SHIFT);
पूर्ण

व्योम arch_kexec_protect_crashkres(व्योम)
अणु
	crash_protect_pages(1);
पूर्ण

व्योम arch_kexec_unprotect_crashkres(व्योम)
अणु
	crash_protect_pages(0);
पूर्ण

#पूर्ण_अगर

/*
 * Give back memory to hypervisor beक्रमe new kdump is loaded
 */
अटल पूर्णांक machine_kexec_prepare_kdump(व्योम)
अणु
#अगर_घोषित CONFIG_CRASH_DUMP
	अगर (MACHINE_IS_VM)
		diag10_range(PFN_DOWN(crashk_res.start),
			     PFN_DOWN(crashk_res.end - crashk_res.start + 1));
	वापस 0;
#अन्यथा
	वापस -EINVAL;
#पूर्ण_अगर
पूर्ण

पूर्णांक machine_kexec_prepare(काष्ठा kimage *image)
अणु
	व्योम *reboot_code_buffer;

	अगर (image->type == KEXEC_TYPE_CRASH)
		वापस machine_kexec_prepare_kdump();

	/* We करोn't support anything but the शेष image type क्रम now. */
	अगर (image->type != KEXEC_TYPE_DEFAULT)
		वापस -EINVAL;

	/* Get the destination where the assembler code should be copied to.*/
	reboot_code_buffer = (व्योम *) page_to_phys(image->control_code_page);

	/* Then copy it */
	स_नकल(reboot_code_buffer, relocate_kernel, relocate_kernel_len);
	वापस 0;
पूर्ण

व्योम machine_kexec_cleanup(काष्ठा kimage *image)
अणु
पूर्ण

व्योम arch_crash_save_vmcoreinfo(व्योम)
अणु
	VMCOREINFO_SYMBOL(lowcore_ptr);
	VMCOREINFO_SYMBOL(high_memory);
	VMCOREINFO_LENGTH(lowcore_ptr, NR_CPUS);
	vmcoreinfo_append_str("SDMA=%lx\n", __sdma);
	vmcoreinfo_append_str("EDMA=%lx\n", __edma);
	vmcoreinfo_append_str("KERNELOFFSET=%lx\n", kaslr_offset());
	mem_assign_असलolute(S390_lowcore.vmcore_info, paddr_vmcoreinfo_note());
पूर्ण

व्योम machine_shutकरोwn(व्योम)
अणु
पूर्ण

व्योम machine_crash_shutकरोwn(काष्ठा pt_regs *regs)
अणु
	set_os_info_reipl_block();
पूर्ण

/*
 * Do normal kexec
 */
अटल व्योम __करो_machine_kexec(व्योम *data)
अणु
	relocate_kernel_t data_mover;
	काष्ठा kimage *image = data;

	s390_reset_प्रणाली();
	data_mover = (relocate_kernel_t) page_to_phys(image->control_code_page);

	__arch_local_irq_stnsm(0xfb); /* disable DAT - aव्योम no-execute */
	/* Call the moving routine */
	(*data_mover)(&image->head, image->start);

	/* Die अगर kexec वापसs */
	disabled_रुको();
पूर्ण

/*
 * Reset प्रणाली and call either kdump or normal kexec
 */
अटल व्योम __machine_kexec(व्योम *data)
अणु
	__arch_local_irq_stosm(0x04); /* enable DAT */
	pfault_fini();
	tracing_off();
	debug_locks_off();
#अगर_घोषित CONFIG_CRASH_DUMP
	अगर (((काष्ठा kimage *) data)->type == KEXEC_TYPE_CRASH)
		__machine_kdump(data);
#पूर्ण_अगर
	__करो_machine_kexec(data);
पूर्ण

/*
 * Do either kdump or normal kexec. In हाल of kdump we first ask
 * purgatory, अगर kdump checksums are valid.
 */
व्योम machine_kexec(काष्ठा kimage *image)
अणु
	अगर (image->type == KEXEC_TYPE_CRASH && !kdump_csum_valid(image))
		वापस;
	tracer_disable();
	smp_send_stop();
	smp_call_ipl_cpu(__machine_kexec, image);
पूर्ण
