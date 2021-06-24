<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_EXTABLE_H
#घोषणा __ASM_EXTABLE_H
/*
 * The exception table consists of pairs of addresses: the first is the
 * address of an inकाष्ठाion that is allowed to fault, and the second is
 * the address at which the program should जारी.  No रेजिस्टरs are
 * modअगरied, so it is entirely up to the continuation code to figure out
 * what to करो.
 *
 * All the routines below use bits of fixup code that are out of line
 * with the मुख्य inकाष्ठाion path.  This means when everything is well,
 * we करोn't even have to jump over them.  Further, they करो not पूर्णांकrude
 * on our cache or tlb entries.
 */

काष्ठा exception_table_entry अणु
        अचिन्हित पूर्णांक insn, fixup;
पूर्ण;

#पूर्ण_अगर
