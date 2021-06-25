<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * arch/ia64/kernel/machine_kexec.c
 *
 * Handle transition of Linux booting another kernel
 * Copyright (C) 2005 Hewlett-Packard Development Comapny, L.P.
 * Copyright (C) 2005 Khalid Aziz <khalid.aziz@hp.com>
 * Copyright (C) 2006 Intel Corp, Zou Nan hai <nanhai.zou@पूर्णांकel.com>
 */

#समावेश <linux/mm.h>
#समावेश <linux/kexec.h>
#समावेश <linux/cpu.h>
#समावेश <linux/irq.h>
#समावेश <linux/efi.h>
#समावेश <linux/numa.h>
#समावेश <linux/mmzone.h>

#समावेश <यंत्र/efi.h>
#समावेश <यंत्र/numa.h>
#समावेश <यंत्र/mmu_context.h>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/delay.h>
#समावेश <यंत्र/meminit.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/sal.h>
#समावेश <यंत्र/mca.h>

प्रकार व्योम (*relocate_new_kernel_t)(
					अचिन्हित दीर्घ indirection_page,
					अचिन्हित दीर्घ start_address,
					काष्ठा ia64_boot_param *boot_param,
					अचिन्हित दीर्घ pal_addr) __noवापस;

काष्ठा kimage *ia64_kimage;

काष्ठा resource efi_memmap_res = अणु
        .name  = "EFI Memory Map",
        .start = 0,
        .end   = 0,
        .flags = IORESOURCE_BUSY | IORESOURCE_MEM
पूर्ण;

काष्ठा resource boot_param_res = अणु
        .name  = "Boot parameter",
        .start = 0,
        .end   = 0,
        .flags = IORESOURCE_BUSY | IORESOURCE_MEM
पूर्ण;


/*
 * Do what every setup is needed on image and the
 * reboot code buffer to allow us to aव्योम allocations
 * later.
 */
पूर्णांक machine_kexec_prepare(काष्ठा kimage *image)
अणु
	व्योम *control_code_buffer;
	स्थिर अचिन्हित दीर्घ *func;

	func = (अचिन्हित दीर्घ *)&relocate_new_kernel;
	/* Pre-load control code buffer to minimize work in kexec path */
	control_code_buffer = page_address(image->control_code_page);
	स_नकल((व्योम *)control_code_buffer, (स्थिर व्योम *)func[0],
			relocate_new_kernel_size);
	flush_icache_range((अचिन्हित दीर्घ)control_code_buffer,
			(अचिन्हित दीर्घ)control_code_buffer + relocate_new_kernel_size);
	ia64_kimage = image;

	वापस 0;
पूर्ण

व्योम machine_kexec_cleanup(काष्ठा kimage *image)
अणु
पूर्ण

/*
 * Do not allocate memory (or fail in any way) in machine_kexec().
 * We are past the poपूर्णांक of no वापस, committed to rebooting now.
 */
अटल व्योम ia64_machine_kexec(काष्ठा unw_frame_info *info, व्योम *arg)
अणु
	काष्ठा kimage *image = arg;
	relocate_new_kernel_t rnk;
	व्योम *pal_addr = efi_get_pal_addr();
	अचिन्हित दीर्घ code_addr;
	पूर्णांक ii;
	u64 fp, gp;
	ia64_fptr_t *init_handler = (ia64_fptr_t *)ia64_os_init_on_kdump;

	BUG_ON(!image);
	code_addr = (अचिन्हित दीर्घ)page_address(image->control_code_page);
	अगर (image->type == KEXEC_TYPE_CRASH) अणु
		crash_save_this_cpu();
		current->thपढ़ो.ksp = (__u64)info->sw - 16;

		/* Register noop init handler */
		fp = ia64_tpa(init_handler->fp);
		gp = ia64_tpa(ia64_getreg(_IA64_REG_GP));
		ia64_sal_set_vectors(SAL_VECTOR_OS_INIT, fp, gp, 0, fp, gp, 0);
	पूर्ण अन्यथा अणु
		/* Unरेजिस्टर init handlers of current kernel */
		ia64_sal_set_vectors(SAL_VECTOR_OS_INIT, 0, 0, 0, 0, 0, 0);
	पूर्ण

	/* Unरेजिस्टर mca handler - No more recovery on current kernel */
	ia64_sal_set_vectors(SAL_VECTOR_OS_MCA, 0, 0, 0, 0, 0, 0);

	/* Interrupts aren't acceptable जबतक we reboot */
	local_irq_disable();

	/* Mask CMC and Perक्रमmance Monitor पूर्णांकerrupts */
	ia64_setreg(_IA64_REG_CR_PMV, 1 << 16);
	ia64_setreg(_IA64_REG_CR_CMCV, 1 << 16);

	/* Mask ITV and Local Redirect Registers */
	ia64_set_itv(1 << 16);
	ia64_set_lrr0(1 << 16);
	ia64_set_lrr1(1 << 16);

	/* terminate possible nested in-service पूर्णांकerrupts */
	क्रम (ii = 0; ii < 16; ii++)
		ia64_eoi();

	/* unmask TPR and clear any pending पूर्णांकerrupts */
	ia64_setreg(_IA64_REG_CR_TPR, 0);
	ia64_srlz_d();
	जबतक (ia64_get_ivr() != IA64_SPURIOUS_INT_VECTOR)
		ia64_eoi();
	rnk = (relocate_new_kernel_t)&code_addr;
	(*rnk)(image->head, image->start, ia64_boot_param,
		     GRANULEROUNDDOWN((अचिन्हित दीर्घ) pal_addr));
	BUG();
पूर्ण

व्योम machine_kexec(काष्ठा kimage *image)
अणु
	BUG_ON(!image);
	unw_init_running(ia64_machine_kexec, image);
	क्रम(;;);
पूर्ण

व्योम arch_crash_save_vmcoreinfo(व्योम)
अणु
#अगर defined(CONFIG_SPARSEMEM)
	VMCOREINFO_SYMBOL(pgdat_list);
	VMCOREINFO_LENGTH(pgdat_list, MAX_NUMNODES);
#पूर्ण_अगर
#अगर_घोषित CONFIG_NUMA
	VMCOREINFO_SYMBOL(node_memblk);
	VMCOREINFO_LENGTH(node_memblk, NR_NODE_MEMBLKS);
	VMCOREINFO_STRUCT_SIZE(node_memblk_s);
	VMCOREINFO_OFFSET(node_memblk_s, start_paddr);
	VMCOREINFO_OFFSET(node_memblk_s, size);
#पूर्ण_अगर
#अगर CONFIG_PGTABLE_LEVELS == 3
	VMCOREINFO_CONFIG(PGTABLE_3);
#या_अगर CONFIG_PGTABLE_LEVELS == 4
	VMCOREINFO_CONFIG(PGTABLE_4);
#पूर्ण_अगर
पूर्ण

