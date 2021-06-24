<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_TRAPS_H
#घोषणा __ASM_TRAPS_H

#घोषणा PARISC_ITLB_TRAP	6 /* defined by architecture. Do not change. */

#अगर !defined(__ASSEMBLY__)
काष्ठा pt_regs;

/* traps.c */
व्योम parisc_terminate(अक्षर *msg, काष्ठा pt_regs *regs,
		पूर्णांक code, अचिन्हित दीर्घ offset) __noवापस __cold;

व्योम die_अगर_kernel(अक्षर *str, काष्ठा pt_regs *regs, दीर्घ err);

/* mm/fault.c */
स्थिर अक्षर *trap_name(अचिन्हित दीर्घ code);
व्योम करो_page_fault(काष्ठा pt_regs *regs, अचिन्हित दीर्घ code,
		अचिन्हित दीर्घ address);
#पूर्ण_अगर

#पूर्ण_अगर
