<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_KDEBUG_H
#घोषणा _ASM_X86_KDEBUG_H

#समावेश <linux/notअगरier.h>

काष्ठा pt_regs;

/* Grossly misnamed. */
क्रमागत die_val अणु
	DIE_OOPS = 1,
	DIE_INT3,
	DIE_DEBUG,
	DIE_PANIC,
	DIE_NMI,
	DIE_DIE,
	DIE_KERNELDEBUG,
	DIE_TRAP,
	DIE_GPF,
	DIE_CALL,
	DIE_PAGE_FAULT,
	DIE_NMIUNKNOWN,
पूर्ण;

क्रमागत show_regs_mode अणु
	SHOW_REGS_SHORT,
	/*
	 * For when userspace crashed, but we करोn't think it's our fault, and
	 * thereक्रमe करोn't prपूर्णांक kernel रेजिस्टरs.
	 */
	SHOW_REGS_USER,
	SHOW_REGS_ALL
पूर्ण;

बाह्य व्योम die(स्थिर अक्षर *, काष्ठा pt_regs *,दीर्घ);
व्योम die_addr(स्थिर अक्षर *str, काष्ठा pt_regs *regs, दीर्घ err, दीर्घ gp_addr);
बाह्य पूर्णांक __must_check __die(स्थिर अक्षर *, काष्ठा pt_regs *, दीर्घ);
बाह्य व्योम show_stack_regs(काष्ठा pt_regs *regs);
बाह्य व्योम __show_regs(काष्ठा pt_regs *regs, क्रमागत show_regs_mode,
			स्थिर अक्षर *log_lvl);
बाह्य व्योम show_iret_regs(काष्ठा pt_regs *regs, स्थिर अक्षर *log_lvl);
बाह्य अचिन्हित दीर्घ oops_begin(व्योम);
बाह्य व्योम oops_end(अचिन्हित दीर्घ, काष्ठा pt_regs *, पूर्णांक signr);

#पूर्ण_अगर /* _ASM_X86_KDEBUG_H */
