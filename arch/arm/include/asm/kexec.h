<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ARM_KEXEC_H
#घोषणा _ARM_KEXEC_H

#अगर_घोषित CONFIG_KEXEC

/* Maximum physical address we can use pages from */
#घोषणा KEXEC_SOURCE_MEMORY_LIMIT (-1UL)
/* Maximum address we can reach in physical address mode */
#घोषणा KEXEC_DESTINATION_MEMORY_LIMIT (-1UL)
/* Maximum address we can use क्रम the control code buffer */
#घोषणा KEXEC_CONTROL_MEMORY_LIMIT (-1UL)

#घोषणा KEXEC_CONTROL_PAGE_SIZE	4096

#घोषणा KEXEC_ARCH KEXEC_ARCH_ARM

#घोषणा KEXEC_ARM_ATAGS_OFFSET  0x1000
#घोषणा KEXEC_ARM_ZIMAGE_OFFSET 0x8000

#अगर_अघोषित __ASSEMBLY__

#घोषणा ARCH_HAS_KIMAGE_ARCH
काष्ठा kimage_arch अणु
	u32 kernel_r2;
पूर्ण;

/**
 * crash_setup_regs() - save रेजिस्टरs क्रम the panic kernel
 * @newregs: रेजिस्टरs are saved here
 * @oldregs: रेजिस्टरs to be saved (may be %शून्य)
 *
 * Function copies machine रेजिस्टरs from @oldregs to @newregs. If @oldregs is
 * %शून्य then current रेजिस्टरs are stored there.
 */
अटल अंतरभूत व्योम crash_setup_regs(काष्ठा pt_regs *newregs,
				    काष्ठा pt_regs *oldregs)
अणु
	अगर (oldregs) अणु
		स_नकल(newregs, oldregs, माप(*newregs));
	पूर्ण अन्यथा अणु
		__यंत्र__ __अस्थिर__ (
			"stmia	%[regs_base], {r0-r12}\n\t"
			"mov	%[_ARM_sp], sp\n\t"
			"str	lr, %[_ARM_lr]\n\t"
			"adr	%[_ARM_pc], 1f\n\t"
			"mrs	%[_ARM_cpsr], cpsr\n\t"
		"1:"
			: [_ARM_pc] "=r" (newregs->ARM_pc),
			  [_ARM_cpsr] "=r" (newregs->ARM_cpsr),
			  [_ARM_sp] "=r" (newregs->ARM_sp),
			  [_ARM_lr] "=o" (newregs->ARM_lr)
			: [regs_base] "r" (&newregs->ARM_r0)
			: "memory"
		);
	पूर्ण
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ phys_to_boot_phys(phys_addr_t phys)
अणु
	वापस phys_to_idmap(phys);
पूर्ण
#घोषणा phys_to_boot_phys phys_to_boot_phys

अटल अंतरभूत phys_addr_t boot_phys_to_phys(अचिन्हित दीर्घ entry)
अणु
	वापस idmap_to_phys(entry);
पूर्ण
#घोषणा boot_phys_to_phys boot_phys_to_phys

अटल अंतरभूत अचिन्हित दीर्घ page_to_boot_pfn(काष्ठा page *page)
अणु
	वापस page_to_pfn(page) + (arch_phys_to_idmap_offset >> PAGE_SHIFT);
पूर्ण
#घोषणा page_to_boot_pfn page_to_boot_pfn

अटल अंतरभूत काष्ठा page *boot_pfn_to_page(अचिन्हित दीर्घ boot_pfn)
अणु
	वापस pfn_to_page(boot_pfn - (arch_phys_to_idmap_offset >> PAGE_SHIFT));
पूर्ण
#घोषणा boot_pfn_to_page boot_pfn_to_page

#पूर्ण_अगर /* __ASSEMBLY__ */

#पूर्ण_अगर /* CONFIG_KEXEC */

#पूर्ण_अगर /* _ARM_KEXEC_H */
