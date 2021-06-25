<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_EXTABLE_H
#घोषणा _ASM_X86_EXTABLE_H
/*
 * The exception table consists of triples of addresses relative to the
 * exception table entry itself. The first address is of an inकाष्ठाion
 * that is allowed to fault, the second is the target at which the program
 * should जारी. The third is a handler function to deal with the fault
 * caused by the inकाष्ठाion in the first field.
 *
 * All the routines below use bits of fixup code that are out of line
 * with the मुख्य inकाष्ठाion path.  This means when everything is well,
 * we करोn't even have to jump over them.  Further, they करो not पूर्णांकrude
 * on our cache or tlb entries.
 */

काष्ठा exception_table_entry अणु
	पूर्णांक insn, fixup, handler;
पूर्ण;
काष्ठा pt_regs;

#घोषणा ARCH_HAS_RELATIVE_EXTABLE

#घोषणा swap_ex_entry_fixup(a, b, पंचांगp, delta)			\
	करो अणु							\
		(a)->fixup = (b)->fixup + (delta);		\
		(b)->fixup = (पंचांगp).fixup - (delta);		\
		(a)->handler = (b)->handler + (delta);		\
		(b)->handler = (पंचांगp).handler - (delta);		\
	पूर्ण जबतक (0)

क्रमागत handler_type अणु
	EX_HANDLER_NONE,
	EX_HANDLER_FAULT,
	EX_HANDLER_UACCESS,
	EX_HANDLER_OTHER
पूर्ण;

बाह्य पूर्णांक fixup_exception(काष्ठा pt_regs *regs, पूर्णांक trapnr,
			   अचिन्हित दीर्घ error_code, अचिन्हित दीर्घ fault_addr);
बाह्य पूर्णांक fixup_bug(काष्ठा pt_regs *regs, पूर्णांक trapnr);
बाह्य क्रमागत handler_type ex_get_fault_handler_type(अचिन्हित दीर्घ ip);
बाह्य व्योम early_fixup_exception(काष्ठा pt_regs *regs, पूर्णांक trapnr);

#पूर्ण_अगर
