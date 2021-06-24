<शैली गुरु>
/*
 * arch/xtensa/include/यंत्र/traps.h
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2012 Tensilica Inc.
 */
#अगर_अघोषित _XTENSA_TRAPS_H
#घोषणा _XTENSA_TRAPS_H

#समावेश <यंत्र/ptrace.h>

/*
 * Per-CPU exception handling data काष्ठाure.
 * EXCSAVE1 poपूर्णांकs to it.
 */
काष्ठा exc_table अणु
	/* Kernel Stack */
	व्योम *kstk;
	/* Double exception save area क्रम a0 */
	अचिन्हित दीर्घ द्विगुन_save;
	/* Fixup handler */
	व्योम *fixup;
	/* For passing a parameter to fixup */
	व्योम *fixup_param;
	/* Fast user exception handlers */
	व्योम *fast_user_handler[EXCCAUSE_N];
	/* Fast kernel exception handlers */
	व्योम *fast_kernel_handler[EXCCAUSE_N];
	/* Default C-Handlers */
	व्योम *शेष_handler[EXCCAUSE_N];
पूर्ण;

/*
 * handler must be either of the following:
 *  व्योम (*)(काष्ठा pt_regs *regs);
 *  व्योम (*)(काष्ठा pt_regs *regs, अचिन्हित दीर्घ exccause);
 */
बाह्य व्योम * __init trap_set_handler(पूर्णांक cause, व्योम *handler);
बाह्य व्योम करो_unhandled(काष्ठा pt_regs *regs, अचिन्हित दीर्घ exccause);
व्योम fast_second_level_miss(व्योम);

/* Initialize minimal exc_table काष्ठाure sufficient क्रम basic paging */
अटल अंतरभूत व्योम __init early_trap_init(व्योम)
अणु
	अटल काष्ठा exc_table exc_table __initdata = अणु
		.fast_kernel_handler[EXCCAUSE_DTLB_MISS] =
			fast_second_level_miss,
	पूर्ण;
	__यंत्र__ __अस्थिर__("wsr  %0, excsave1\n" : : "a" (&exc_table));
पूर्ण

व्योम secondary_trap_init(व्योम);

अटल अंतरभूत व्योम spill_रेजिस्टरs(व्योम)
अणु
#अगर XCHAL_NUM_AREGS > 16
	__यंत्र__ __अस्थिर__ (
		"	call8	1f\n"
		"	_j	2f\n"
		"	retw\n"
		"	.align	4\n"
		"1:\n"
#अगर XCHAL_NUM_AREGS == 32
		"	_entry	a1, 32\n"
		"	addi	a8, a0, 3\n"
		"	_entry	a1, 16\n"
		"	mov	a12, a12\n"
		"	retw\n"
#अन्यथा
		"	_entry	a1, 48\n"
		"	call12	1f\n"
		"	retw\n"
		"	.align	4\n"
		"1:\n"
		"	.rept	(" __stringअगरy(XCHAL_NUM_AREGS) " - 16) / 12\n"
		"	_entry	a1, 48\n"
		"	mov	a12, a0\n"
		"	.endr\n"
		"	_entry	a1, 16\n"
#अगर XCHAL_NUM_AREGS % 12 == 0
		"	mov	a12, a12\n"
#या_अगर XCHAL_NUM_AREGS % 12 == 4
		"	mov	a4, a4\n"
#या_अगर XCHAL_NUM_AREGS % 12 == 8
		"	mov	a8, a8\n"
#पूर्ण_अगर
		"	retw\n"
#पूर्ण_अगर
		"2:\n"
		: : : "a8", "a9", "memory");
#अन्यथा
	__यंत्र__ __अस्थिर__ (
		"	mov	a12, a12\n"
		: : : "memory");
#पूर्ण_अगर
पूर्ण

काष्ठा debug_table अणु
	/* Poपूर्णांकer to debug exception handler */
	व्योम (*debug_exception)(व्योम);
	/* Temporary रेजिस्टर save area */
	अचिन्हित दीर्घ debug_save[1];
#अगर_घोषित CONFIG_HAVE_HW_BREAKPOINT
	/* Save area क्रम DBREAKC रेजिस्टरs */
	अचिन्हित दीर्घ dअवरोधc_save[XCHAL_NUM_DBREAK];
	/* Saved ICOUNT रेजिस्टर */
	अचिन्हित दीर्घ icount_save;
	/* Saved ICOUNTLEVEL रेजिस्टर */
	अचिन्हित दीर्घ icount_level_save;
#पूर्ण_अगर
पूर्ण;

व्योम debug_exception(व्योम);

#पूर्ण_अगर /* _XTENSA_TRAPS_H */
