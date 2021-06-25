<शैली गुरु>
/*
 * S32C1I selftest.
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2016 Cadence Design Systems Inc.
 */

#समावेश <linux/init.h>
#समावेश <linux/kernel.h>

#समावेश <यंत्र/traps.h>

#अगर XCHAL_HAVE_S32C1I

अटल पूर्णांक __initdata rcw_word, rcw_probe_pc, rcw_exc;

/*
 * Basic atomic compare-and-swap, that records PC of S32C1I क्रम probing.
 *
 * If *v == cmp, set *v = set.  Return previous *v.
 */
अटल अंतरभूत पूर्णांक probed_compare_swap(पूर्णांक *v, पूर्णांक cmp, पूर्णांक set)
अणु
	पूर्णांक पंचांगp;

	__यंत्र__ __अस्थिर__(
			"	movi	%1, 1f\n"
			"	s32i	%1, %4, 0\n"
			"	wsr	%2, scompare1\n"
			"1:	s32c1i	%0, %3, 0\n"
			: "=a" (set), "=&a" (पंचांगp)
			: "a" (cmp), "a" (v), "a" (&rcw_probe_pc), "0" (set)
			: "memory"
			);
	वापस set;
पूर्ण

/* Handle probed exception */

अटल व्योम __init करो_probed_exception(काष्ठा pt_regs *regs,
				       अचिन्हित दीर्घ exccause)
अणु
	अगर (regs->pc == rcw_probe_pc) अणु	/* exception on s32c1i ? */
		regs->pc += 3;		/* skip the s32c1i inकाष्ठाion */
		rcw_exc = exccause;
	पूर्ण अन्यथा अणु
		करो_unhandled(regs, exccause);
	पूर्ण
पूर्ण

/* Simple test of S32C1I (soc bringup assist) */

अटल पूर्णांक __init check_s32c1i(व्योम)
अणु
	पूर्णांक n, cause1, cause2;
	व्योम *handbus, *handdata, *handaddr; /* temporarily saved handlers */

	rcw_probe_pc = 0;
	handbus  = trap_set_handler(EXCCAUSE_LOAD_STORE_ERROR,
			करो_probed_exception);
	handdata = trap_set_handler(EXCCAUSE_LOAD_STORE_DATA_ERROR,
			करो_probed_exception);
	handaddr = trap_set_handler(EXCCAUSE_LOAD_STORE_ADDR_ERROR,
			करो_probed_exception);

	/* First try an S32C1I that करोes not store: */
	rcw_exc = 0;
	rcw_word = 1;
	n = probed_compare_swap(&rcw_word, 0, 2);
	cause1 = rcw_exc;

	/* took exception? */
	अगर (cause1 != 0) अणु
		/* unclean exception? */
		अगर (n != 2 || rcw_word != 1)
			panic("S32C1I exception error");
	पूर्ण अन्यथा अगर (rcw_word != 1 || n != 1) अणु
		panic("S32C1I compare error");
	पूर्ण

	/* Then an S32C1I that stores: */
	rcw_exc = 0;
	rcw_word = 0x1234567;
	n = probed_compare_swap(&rcw_word, 0x1234567, 0xabcde);
	cause2 = rcw_exc;

	अगर (cause2 != 0) अणु
		/* unclean exception? */
		अगर (n != 0xabcde || rcw_word != 0x1234567)
			panic("S32C1I exception error (b)");
	पूर्ण अन्यथा अगर (rcw_word != 0xabcde || n != 0x1234567) अणु
		panic("S32C1I store error");
	पूर्ण

	/* Verअगरy consistency of exceptions: */
	अगर (cause1 || cause2) अणु
		pr_warn("S32C1I took exception %d, %d\n", cause1, cause2);
		/* If emulation of S32C1I upon bus error माला_लो implemented,
		 * we can get rid of this panic क्रम single core (not SMP)
		 */
		panic("S32C1I exceptions not currently supported");
	पूर्ण
	अगर (cause1 != cause2)
		panic("inconsistent S32C1I exceptions");

	trap_set_handler(EXCCAUSE_LOAD_STORE_ERROR, handbus);
	trap_set_handler(EXCCAUSE_LOAD_STORE_DATA_ERROR, handdata);
	trap_set_handler(EXCCAUSE_LOAD_STORE_ADDR_ERROR, handaddr);
	वापस 0;
पूर्ण

#अन्यथा /* XCHAL_HAVE_S32C1I */

/* This condition should not occur with a commercially deployed processor.
 * Display reminder क्रम early engr test or demo chips / FPGA bitstreams
 */
अटल पूर्णांक __init check_s32c1i(व्योम)
अणु
	pr_warn("Processor configuration lacks atomic compare-and-swap support!\n");
	वापस 0;
पूर्ण

#पूर्ण_अगर /* XCHAL_HAVE_S32C1I */

early_initcall(check_s32c1i);
