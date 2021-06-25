<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * PPC32 code to handle Linux booting another kernel.
 *
 * Copyright (C) 2002-2003 Eric Biederman  <ebiederm@xmission.com>
 * GameCube/ppc32 port Copyright (C) 2004 Albert Herranz
 * Copyright (C) 2005 IBM Corporation.
 */

#समावेश <linux/kexec.h>
#समावेश <linux/mm.h>
#समावेश <linux/माला.स>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/hw_irq.h>
#समावेश <यंत्र/पन.स>

प्रकार व्योम (*relocate_new_kernel_t)(
				अचिन्हित दीर्घ indirection_page,
				अचिन्हित दीर्घ reboot_code_buffer,
				अचिन्हित दीर्घ start_address) __noवापस;

/*
 * This is a generic machine_kexec function suitable at least क्रम
 * non-OpenFirmware embedded platक्रमms.
 * It merely copies the image relocation code to the control page and
 * jumps to it.
 * A platक्रमm specअगरic function may just call this one.
 */
व्योम शेष_machine_kexec(काष्ठा kimage *image)
अणु
	बाह्य स्थिर अचिन्हित पूर्णांक relocate_new_kernel_size;
	अचिन्हित दीर्घ page_list;
	अचिन्हित दीर्घ reboot_code_buffer, reboot_code_buffer_phys;
	relocate_new_kernel_t rnk;

	/* Interrupts aren't acceptable जबतक we reboot */
	local_irq_disable();

	/* mask each पूर्णांकerrupt so we are in a more sane state क्रम the
	 * kexec kernel */
	machine_kexec_mask_पूर्णांकerrupts();

	page_list = image->head;

	/* we need both effective and real address here */
	reboot_code_buffer =
			(अचिन्हित दीर्घ)page_address(image->control_code_page);
	reboot_code_buffer_phys = virt_to_phys((व्योम *)reboot_code_buffer);

	/* copy our kernel relocation code to the control code page */
	स_नकल((व्योम *)reboot_code_buffer, relocate_new_kernel,
						relocate_new_kernel_size);

	flush_icache_range(reboot_code_buffer,
				reboot_code_buffer + KEXEC_CONTROL_PAGE_SIZE);
	prपूर्णांकk(KERN_INFO "Bye!\n");

	अगर (!IS_ENABLED(CONFIG_FSL_BOOKE) && !IS_ENABLED(CONFIG_44x))
		relocate_new_kernel(page_list, reboot_code_buffer_phys, image->start);

	/* now call it */
	rnk = (relocate_new_kernel_t) reboot_code_buffer;
	(*rnk)(page_list, reboot_code_buffer_phys, image->start);
पूर्ण

पूर्णांक शेष_machine_kexec_prepare(काष्ठा kimage *image)
अणु
	वापस 0;
पूर्ण
