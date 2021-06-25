<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ARCH_POWERPC_EXTABLE_H
#घोषणा _ARCH_POWERPC_EXTABLE_H

/*
 * The exception table consists of pairs of relative addresses: the first is
 * the address of an inकाष्ठाion that is allowed to fault, and the second is
 * the address at which the program should जारी.  No रेजिस्टरs are
 * modअगरied, so it is entirely up to the continuation code to figure out what
 * to करो.
 *
 * All the routines below use bits of fixup code that are out of line with the
 * मुख्य inकाष्ठाion path.  This means when everything is well, we करोn't even
 * have to jump over them.  Further, they करो not पूर्णांकrude on our cache or tlb
 * entries.
 */

#घोषणा ARCH_HAS_RELATIVE_EXTABLE

काष्ठा exception_table_entry अणु
	पूर्णांक insn;
	पूर्णांक fixup;
पूर्ण;

अटल अंतरभूत अचिन्हित दीर्घ extable_fixup(स्थिर काष्ठा exception_table_entry *x)
अणु
	वापस (अचिन्हित दीर्घ)&x->fixup + x->fixup;
पूर्ण

#पूर्ण_अगर
