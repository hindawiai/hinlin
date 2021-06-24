<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2011-2012 Synopsys (www.synopsys.com)
 *
 * vineetg : May 2011
 *  -Adapted (from .26 to .35)
 *  -original contribution by Tim.yao@amlogic.com
 */

#समावेश <linux/types.h>
#समावेश <linux/perf_event.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/disयंत्र.h>

#अगर_घोषित CONFIG_CPU_BIG_ENDIAN
#घोषणा BE		1
#घोषणा FIRST_BYTE_16	"swap %1, %1\n swape %1, %1\n"
#घोषणा FIRST_BYTE_32	"swape %1, %1\n"
#अन्यथा
#घोषणा BE		0
#घोषणा FIRST_BYTE_16
#घोषणा FIRST_BYTE_32
#पूर्ण_अगर

#घोषणा __get8_unaligned_check(val, addr, err)		\
	__यंत्र__(					\
	"1:	ldb.ab	%1, [%2, 1]\n"			\
	"2:\n"						\
	"	.section .fixup,\"ax\"\n"		\
	"	.align	4\n"				\
	"3:	mov	%0, 1\n"			\
	"	j	2b\n"				\
	"	.previous\n"				\
	"	.section __ex_table,\"a\"\n"		\
	"	.align	4\n"				\
	"	.long	1b, 3b\n"			\
	"	.previous\n"				\
	: "=r" (err), "=&r" (val), "=r" (addr)		\
	: "0" (err), "2" (addr))

#घोषणा get16_unaligned_check(val, addr)		\
	करो अणु						\
		अचिन्हित पूर्णांक err = 0, v, a = addr;	\
		__get8_unaligned_check(v, a, err);	\
		val =  v << ((BE) ? 8 : 0);		\
		__get8_unaligned_check(v, a, err);	\
		val |= v << ((BE) ? 0 : 8);		\
		अगर (err)				\
			जाओ fault;			\
	पूर्ण जबतक (0)

#घोषणा get32_unaligned_check(val, addr)		\
	करो अणु						\
		अचिन्हित पूर्णांक err = 0, v, a = addr;	\
		__get8_unaligned_check(v, a, err);	\
		val =  v << ((BE) ? 24 : 0);		\
		__get8_unaligned_check(v, a, err);	\
		val |= v << ((BE) ? 16 : 8);		\
		__get8_unaligned_check(v, a, err);	\
		val |= v << ((BE) ? 8 : 16);		\
		__get8_unaligned_check(v, a, err);	\
		val |= v << ((BE) ? 0 : 24);		\
		अगर (err)				\
			जाओ fault;			\
	पूर्ण जबतक (0)

#घोषणा put16_unaligned_check(val, addr)		\
	करो अणु						\
		अचिन्हित पूर्णांक err = 0, v = val, a = addr;\
							\
		__यंत्र__(				\
		FIRST_BYTE_16				\
		"1:	stb.ab	%1, [%2, 1]\n"		\
		"	lsr %1, %1, 8\n"		\
		"2:	stb	%1, [%2]\n"		\
		"3:\n"					\
		"	.section .fixup,\"ax\"\n"	\
		"	.align	4\n"			\
		"4:	mov	%0, 1\n"		\
		"	j	3b\n"			\
		"	.previous\n"			\
		"	.section __ex_table,\"a\"\n"	\
		"	.align	4\n"			\
		"	.long	1b, 4b\n"		\
		"	.long	2b, 4b\n"		\
		"	.previous\n"			\
		: "=r" (err), "=&r" (v), "=&r" (a)	\
		: "0" (err), "1" (v), "2" (a));		\
							\
		अगर (err)				\
			जाओ fault;			\
	पूर्ण जबतक (0)

#घोषणा put32_unaligned_check(val, addr)		\
	करो अणु						\
		अचिन्हित पूर्णांक err = 0, v = val, a = addr;\
							\
		__यंत्र__(				\
		FIRST_BYTE_32				\
		"1:	stb.ab	%1, [%2, 1]\n"		\
		"	lsr %1, %1, 8\n"		\
		"2:	stb.ab	%1, [%2, 1]\n"		\
		"	lsr %1, %1, 8\n"		\
		"3:	stb.ab	%1, [%2, 1]\n"		\
		"	lsr %1, %1, 8\n"		\
		"4:	stb	%1, [%2]\n"		\
		"5:\n"					\
		"	.section .fixup,\"ax\"\n"	\
		"	.align	4\n"			\
		"6:	mov	%0, 1\n"		\
		"	j	5b\n"			\
		"	.previous\n"			\
		"	.section __ex_table,\"a\"\n"	\
		"	.align	4\n"			\
		"	.long	1b, 6b\n"		\
		"	.long	2b, 6b\n"		\
		"	.long	3b, 6b\n"		\
		"	.long	4b, 6b\n"		\
		"	.previous\n"			\
		: "=r" (err), "=&r" (v), "=&r" (a)	\
		: "0" (err), "1" (v), "2" (a));		\
							\
		अगर (err)				\
			जाओ fault;			\
	पूर्ण जबतक (0)

/* sysctl hooks */
पूर्णांक unaligned_enabled __पढ़ो_mostly = 1;	/* Enabled by शेष */
पूर्णांक no_unaligned_warning __पढ़ो_mostly = 1;	/* Only 1 warning by शेष */

अटल व्योम fixup_load(काष्ठा disयंत्र_state *state, काष्ठा pt_regs *regs,
			काष्ठा callee_regs *cregs)
अणु
	पूर्णांक val;

	/* रेजिस्टर ग_लिखो back */
	अगर ((state->aa == 1) || (state->aa == 2)) अणु
		set_reg(state->wb_reg, state->src1 + state->src2, regs, cregs);

		अगर (state->aa == 2)
			state->src2 = 0;
	पूर्ण

	अगर (state->zz == 0) अणु
		get32_unaligned_check(val, state->src1 + state->src2);
	पूर्ण अन्यथा अणु
		get16_unaligned_check(val, state->src1 + state->src2);

		अगर (state->x)
			val = (val << 16) >> 16;
	पूर्ण

	अगर (state->pref == 0)
		set_reg(state->dest, val, regs, cregs);

	वापस;

fault:	state->fault = 1;
पूर्ण

अटल व्योम fixup_store(काष्ठा disयंत्र_state *state, काष्ठा pt_regs *regs,
			काष्ठा callee_regs *cregs)
अणु
	/* रेजिस्टर ग_लिखो back */
	अगर ((state->aa == 1) || (state->aa == 2)) अणु
		set_reg(state->wb_reg, state->src2 + state->src3, regs, cregs);

		अगर (state->aa == 3)
			state->src3 = 0;
	पूर्ण अन्यथा अगर (state->aa == 3) अणु
		अगर (state->zz == 2) अणु
			set_reg(state->wb_reg, state->src2 + (state->src3 << 1),
				regs, cregs);
		पूर्ण अन्यथा अगर (!state->zz) अणु
			set_reg(state->wb_reg, state->src2 + (state->src3 << 2),
				regs, cregs);
		पूर्ण अन्यथा अणु
			जाओ fault;
		पूर्ण
	पूर्ण

	/* ग_लिखो fix-up */
	अगर (!state->zz)
		put32_unaligned_check(state->src1, state->src2 + state->src3);
	अन्यथा
		put16_unaligned_check(state->src1, state->src2 + state->src3);

	वापस;

fault:	state->fault = 1;
पूर्ण

/*
 * Handle an unaligned access
 * Returns 0 अगर successfully handled, 1 अगर some error happened
 */
पूर्णांक misaligned_fixup(अचिन्हित दीर्घ address, काष्ठा pt_regs *regs,
		     काष्ठा callee_regs *cregs)
अणु
	काष्ठा disयंत्र_state state;
	अक्षर buf[TASK_COMM_LEN];

	/* handle user mode only and only अगर enabled by sysadmin */
	अगर (!user_mode(regs) || !unaligned_enabled)
		वापस 1;

	अगर (no_unaligned_warning) अणु
		pr_warn_once("%s(%d) made unaligned access which was emulated"
			     " by kernel assist\n. This can degrade application"
			     " performance significantly\n. To enable further"
			     " logging of such instances, please \n"
			     " echo 0 > /proc/sys/kernel/ignore-unaligned-usertrap\n",
			     get_task_comm(buf, current), task_pid_nr(current));
	पूर्ण अन्यथा अणु
		/* Add rate limiting अगर it माला_लो करोwn to it */
		pr_warn("%s(%d): unaligned access to/from 0x%lx by PC: 0x%lx\n",
			get_task_comm(buf, current), task_pid_nr(current),
			address, regs->ret);

	पूर्ण

	disयंत्र_instr(regs->ret, &state, 1, regs, cregs);

	अगर (state.fault)
		जाओ fault;

	/* ldb/stb should not have unaligned exception */
	अगर ((state.zz == 1) || (state.di))
		जाओ fault;

	अगर (!state.ग_लिखो)
		fixup_load(&state, regs, cregs);
	अन्यथा
		fixup_store(&state, regs, cregs);

	अगर (state.fault)
		जाओ fault;

	/* clear any remanants of delay slot */
	अगर (delay_mode(regs)) अणु
		regs->ret = regs->bta & ~1U;
		regs->status32 &= ~STATUS_DE_MASK;
	पूर्ण अन्यथा अणु
		regs->ret += state.instr_len;

		/* handle zero-overhead-loop */
		अगर ((regs->ret == regs->lp_end) && (regs->lp_count)) अणु
			regs->ret = regs->lp_start;
			regs->lp_count--;
		पूर्ण
	पूर्ण

	perf_sw_event(PERF_COUNT_SW_ALIGNMENT_FAULTS, 1, regs, address);
	वापस 0;

fault:
	pr_err("Alignment trap: fault in fix-up %08lx at [<%08lx>]\n",
		state.words[0], address);

	वापस 1;
पूर्ण
