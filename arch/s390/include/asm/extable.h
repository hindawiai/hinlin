<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __S390_EXTABLE_H
#घोषणा __S390_EXTABLE_H

#समावेश <यंत्र/ptrace.h>
#समावेश <linux/compiler.h>

/*
 * The exception table consists of three addresses:
 *
 * - Address of an inकाष्ठाion that is allowed to fault.
 * - Address at which the program should जारी.
 * - Optional address of handler that takes pt_regs * argument and runs in
 *   पूर्णांकerrupt context.
 *
 * No रेजिस्टरs are modअगरied, so it is entirely up to the continuation code
 * to figure out what to करो.
 *
 * All the routines below use bits of fixup code that are out of line
 * with the मुख्य inकाष्ठाion path.  This means when everything is well,
 * we करोn't even have to jump over them.  Further, they करो not पूर्णांकrude
 * on our cache or tlb entries.
 */

काष्ठा exception_table_entry
अणु
	पूर्णांक insn, fixup;
	दीर्घ handler;
पूर्ण;

बाह्य काष्ठा exception_table_entry *__start_dma_ex_table;
बाह्य काष्ठा exception_table_entry *__stop_dma_ex_table;

स्थिर काष्ठा exception_table_entry *s390_search_extables(अचिन्हित दीर्घ addr);

अटल अंतरभूत अचिन्हित दीर्घ extable_fixup(स्थिर काष्ठा exception_table_entry *x)
अणु
	वापस (अचिन्हित दीर्घ)&x->fixup + x->fixup;
पूर्ण

प्रकार bool (*ex_handler_t)(स्थिर काष्ठा exception_table_entry *,
			     काष्ठा pt_regs *);

अटल अंतरभूत ex_handler_t
ex_fixup_handler(स्थिर काष्ठा exception_table_entry *x)
अणु
	अगर (likely(!x->handler))
		वापस शून्य;
	वापस (ex_handler_t)((अचिन्हित दीर्घ)&x->handler + x->handler);
पूर्ण

अटल अंतरभूत bool ex_handle(स्थिर काष्ठा exception_table_entry *x,
			     काष्ठा pt_regs *regs)
अणु
	ex_handler_t handler = ex_fixup_handler(x);

	अगर (unlikely(handler))
		वापस handler(x, regs);
	regs->psw.addr = extable_fixup(x);
	वापस true;
पूर्ण

#घोषणा ARCH_HAS_RELATIVE_EXTABLE

अटल अंतरभूत व्योम swap_ex_entry_fixup(काष्ठा exception_table_entry *a,
				       काष्ठा exception_table_entry *b,
				       काष्ठा exception_table_entry पंचांगp,
				       पूर्णांक delta)
अणु
	a->fixup = b->fixup + delta;
	b->fixup = पंचांगp.fixup - delta;
	a->handler = b->handler + delta;
	b->handler = पंचांगp.handler - delta;
पूर्ण

#पूर्ण_अगर
