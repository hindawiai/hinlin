<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2019 FORTH-ICS/CARV
 *  Nick Kossअगरidis <mick@ics.क्रमth.gr>
 */

#अगर_अघोषित _RISCV_KEXEC_H
#घोषणा _RISCV_KEXEC_H

#समावेश <यंत्र/page.h>    /* For PAGE_SIZE */

/* Maximum physical address we can use pages from */
#घोषणा KEXEC_SOURCE_MEMORY_LIMIT (-1UL)

/* Maximum address we can reach in physical address mode */
#घोषणा KEXEC_DESTINATION_MEMORY_LIMIT (-1UL)

/* Maximum address we can use क्रम the control code buffer */
#घोषणा KEXEC_CONTROL_MEMORY_LIMIT (-1UL)

/* Reserve a page क्रम the control code buffer */
#घोषणा KEXEC_CONTROL_PAGE_SIZE PAGE_SIZE

#घोषणा KEXEC_ARCH KEXEC_ARCH_RISCV

बाह्य व्योम riscv_crash_save_regs(काष्ठा pt_regs *newregs);

अटल अंतरभूत व्योम
crash_setup_regs(काष्ठा pt_regs *newregs,
		 काष्ठा pt_regs *oldregs)
अणु
	अगर (oldregs)
		स_नकल(newregs, oldregs, माप(काष्ठा pt_regs));
	अन्यथा
		riscv_crash_save_regs(newregs);
पूर्ण


#घोषणा ARCH_HAS_KIMAGE_ARCH

काष्ठा kimage_arch अणु
	अचिन्हित दीर्घ fdt_addr;
पूर्ण;

बाह्य स्थिर अचिन्हित अक्षर riscv_kexec_relocate[];
बाह्य स्थिर अचिन्हित पूर्णांक riscv_kexec_relocate_size;

प्रकार व्योम (*riscv_kexec_method)(अचिन्हित दीर्घ first_ind_entry,
				   अचिन्हित दीर्घ jump_addr,
				   अचिन्हित दीर्घ fdt_addr,
				   अचिन्हित दीर्घ hartid,
				   अचिन्हित दीर्घ va_pa_off);

बाह्य riscv_kexec_method riscv_kexec_norelocate;

#पूर्ण_अगर
