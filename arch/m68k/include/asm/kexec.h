<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_M68K_KEXEC_H
#घोषणा _ASM_M68K_KEXEC_H

#अगर_घोषित CONFIG_KEXEC

/* Maximum physical address we can use pages from */
#घोषणा KEXEC_SOURCE_MEMORY_LIMIT (-1UL)
/* Maximum address we can reach in physical address mode */
#घोषणा KEXEC_DESTINATION_MEMORY_LIMIT (-1UL)
/* Maximum address we can use क्रम the control code buffer */
#घोषणा KEXEC_CONTROL_MEMORY_LIMIT (-1UL)

#घोषणा KEXEC_CONTROL_PAGE_SIZE	4096

#घोषणा KEXEC_ARCH KEXEC_ARCH_68K

#अगर_अघोषित __ASSEMBLY__

अटल अंतरभूत व्योम crash_setup_regs(काष्ठा pt_regs *newregs,
				    काष्ठा pt_regs *oldregs)
अणु
	/* Dummy implementation क्रम now */
पूर्ण

#पूर्ण_अगर /* __ASSEMBLY__ */

#पूर्ण_अगर /* CONFIG_KEXEC */

#पूर्ण_अगर /* _ASM_M68K_KEXEC_H */
