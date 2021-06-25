<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * machine_kexec.c - handle transition of Linux booting another kernel
 */
#समावेश <linux/compiler.h>
#समावेश <linux/kexec.h>
#समावेश <linux/mm.h>
#समावेश <linux/delay.h>

#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/setup.h>

बाह्य स्थिर अचिन्हित अक्षर relocate_new_kernel[];
बाह्य स्थिर माप_प्रकार relocate_new_kernel_size;

पूर्णांक machine_kexec_prepare(काष्ठा kimage *kimage)
अणु
	वापस 0;
पूर्ण

व्योम machine_kexec_cleanup(काष्ठा kimage *kimage)
अणु
पूर्ण

व्योम machine_shutकरोwn(व्योम)
अणु
पूर्ण

व्योम machine_crash_shutकरोwn(काष्ठा pt_regs *regs)
अणु
पूर्ण

प्रकार व्योम (*relocate_kernel_t)(अचिन्हित दीर्घ ptr,
				  अचिन्हित दीर्घ start,
				  अचिन्हित दीर्घ cpu_mmu_flags) __noवापस;

व्योम machine_kexec(काष्ठा kimage *image)
अणु
	व्योम *reboot_code_buffer;
	अचिन्हित दीर्घ cpu_mmu_flags;

	reboot_code_buffer = page_address(image->control_code_page);

	स_नकल(reboot_code_buffer, relocate_new_kernel,
	       relocate_new_kernel_size);

	/*
	 * we करो not want to be bothered.
	 */
	local_irq_disable();

	pr_info("Will call new kernel at 0x%08lx. Bye...\n", image->start);
	__flush_cache_all();
	cpu_mmu_flags = m68k_cputype | m68k_mmutype << 8;
	((relocate_kernel_t) reboot_code_buffer)(image->head & PAGE_MASK,
						 image->start,
						 cpu_mmu_flags);
पूर्ण
