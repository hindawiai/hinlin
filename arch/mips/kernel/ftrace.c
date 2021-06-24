<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Code क्रम replacing ftrace calls with jumps.
 *
 * Copyright (C) 2007-2008 Steven Rostedt <srostedt@redhat.com>
 * Copyright (C) 2009, 2010 DSLab, Lanzhou University, China
 * Author: Wu Zhangjin <wuzhangjin@gmail.com>
 *
 * Thanks goes to Steven Rostedt क्रम writing the original x86 version.
 */

#समावेश <linux/uaccess.h>
#समावेश <linux/init.h>
#समावेश <linux/ftrace.h>
#समावेश <linux/syscalls.h>

#समावेश <यंत्र/यंत्र.h>
#समावेश <यंत्र/यंत्र-offsets.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/syscall.h>
#समावेश <यंत्र/uयंत्र.h>
#समावेश <यंत्र/unistd.h>

#समावेश <यंत्र-generic/sections.h>

#अगर defined(KBUILD_MCOUNT_RA_ADDRESS) && defined(CONFIG_32BIT)
#घोषणा MCOUNT_OFFSET_INSNS 5
#अन्यथा
#घोषणा MCOUNT_OFFSET_INSNS 4
#पूर्ण_अगर

#अगर_घोषित CONFIG_DYNAMIC_FTRACE

/* Arch override because MIPS करोesn't need to run this from stop_machine() */
व्योम arch_ftrace_update_code(पूर्णांक command)
अणु
	ftrace_modअगरy_all_code(command);
पूर्ण

#घोषणा JAL 0x0c000000		/* jump & link: ip --> ra, jump to target */
#घोषणा ADDR_MASK 0x03ffffff	/*  op_code|addr : 31...26|25 ....0 */
#घोषणा JUMP_RANGE_MASK ((1UL << 28) - 1)

#घोषणा INSN_NOP 0x00000000	/* nop */
#घोषणा INSN_JAL(addr)	\
	((अचिन्हित पूर्णांक)(JAL | (((addr) >> 2) & ADDR_MASK)))

अटल अचिन्हित पूर्णांक insn_jal_ftrace_caller __पढ़ो_mostly;
अटल अचिन्हित पूर्णांक insn_la_mcount[2] __पढ़ो_mostly;
अटल अचिन्हित पूर्णांक insn_j_ftrace_graph_caller __maybe_unused __पढ़ो_mostly;

अटल अंतरभूत व्योम ftrace_dyn_arch_init_insns(व्योम)
अणु
	u32 *buf;
	अचिन्हित पूर्णांक v1;

	/* la v1, _mcount */
	v1 = 3;
	buf = (u32 *)&insn_la_mcount[0];
	UASM_i_LA(&buf, v1, MCOUNT_ADDR);

	/* jal (ftrace_caller + 8), jump over the first two inकाष्ठाion */
	buf = (u32 *)&insn_jal_ftrace_caller;
	uयंत्र_i_jal(&buf, (FTRACE_ADDR + 8) & JUMP_RANGE_MASK);

#अगर_घोषित CONFIG_FUNCTION_GRAPH_TRACER
	/* j ftrace_graph_caller */
	buf = (u32 *)&insn_j_ftrace_graph_caller;
	uयंत्र_i_j(&buf, (अचिन्हित दीर्घ)ftrace_graph_caller & JUMP_RANGE_MASK);
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक ftrace_modअगरy_code(अचिन्हित दीर्घ ip, अचिन्हित पूर्णांक new_code)
अणु
	पूर्णांक faulted;

	/* *(अचिन्हित पूर्णांक *)ip = new_code; */
	safe_store_code(new_code, ip, faulted);

	अगर (unlikely(faulted))
		वापस -EFAULT;

	flush_icache_range(ip, ip + 8);

	वापस 0;
पूर्ण

#अगर_अघोषित CONFIG_64BIT
अटल पूर्णांक ftrace_modअगरy_code_2(अचिन्हित दीर्घ ip, अचिन्हित पूर्णांक new_code1,
				अचिन्हित पूर्णांक new_code2)
अणु
	पूर्णांक faulted;

	safe_store_code(new_code1, ip, faulted);
	अगर (unlikely(faulted))
		वापस -EFAULT;

	ip += 4;
	safe_store_code(new_code2, ip, faulted);
	अगर (unlikely(faulted))
		वापस -EFAULT;

	ip -= 4;
	flush_icache_range(ip, ip + 8);

	वापस 0;
पूर्ण

अटल पूर्णांक ftrace_modअगरy_code_2r(अचिन्हित दीर्घ ip, अचिन्हित पूर्णांक new_code1,
				 अचिन्हित पूर्णांक new_code2)
अणु
	पूर्णांक faulted;

	ip += 4;
	safe_store_code(new_code2, ip, faulted);
	अगर (unlikely(faulted))
		वापस -EFAULT;

	ip -= 4;
	safe_store_code(new_code1, ip, faulted);
	अगर (unlikely(faulted))
		वापस -EFAULT;

	flush_icache_range(ip, ip + 8);

	वापस 0;
पूर्ण
#पूर्ण_अगर

/*
 * The details about the calling site of mcount on MIPS
 *
 * 1. For kernel:
 *
 * move at, ra
 * jal _mcount		--> nop
 *  sub sp, sp, 8	--> nop  (CONFIG_32BIT)
 *
 * 2. For modules:
 *
 * 2.1 For KBUILD_MCOUNT_RA_ADDRESS and CONFIG_32BIT
 *
 * lui v1, hi_16bit_of_mcount	     --> b 1f (0x10000005)
 * addiu v1, v1, low_16bit_of_mcount --> nop  (CONFIG_32BIT)
 * move at, ra
 * move $12, ra_address
 * jalr v1
 *  sub sp, sp, 8
 *				    1: offset = 5 inकाष्ठाions
 * 2.2 For the Other situations
 *
 * lui v1, hi_16bit_of_mcount	     --> b 1f (0x10000004)
 * addiu v1, v1, low_16bit_of_mcount --> nop  (CONFIG_32BIT)
 * move at, ra
 * jalr v1
 *  nop | move $12, ra_address | sub sp, sp, 8
 *				    1: offset = 4 inकाष्ठाions
 */

#घोषणा INSN_B_1F (0x10000000 | MCOUNT_OFFSET_INSNS)

पूर्णांक ftrace_make_nop(काष्ठा module *mod,
		    काष्ठा dyn_ftrace *rec, अचिन्हित दीर्घ addr)
अणु
	अचिन्हित पूर्णांक new;
	अचिन्हित दीर्घ ip = rec->ip;

	/*
	 * If ip is in kernel space, no दीर्घ call, otherwise, दीर्घ call is
	 * needed.
	 */
	new = core_kernel_text(ip) ? INSN_NOP : INSN_B_1F;
#अगर_घोषित CONFIG_64BIT
	वापस ftrace_modअगरy_code(ip, new);
#अन्यथा
	/*
	 * On 32 bit MIPS platक्रमms, gcc adds a stack adjust
	 * inकाष्ठाion in the delay slot after the branch to
	 * mcount and expects mcount to restore the sp on वापस.
	 * This is based on a legacy API and करोes nothing but
	 * waste inकाष्ठाions so it's being हटाओd at runसमय.
	 */
	वापस ftrace_modअगरy_code_2(ip, new, INSN_NOP);
#पूर्ण_अगर
पूर्ण

पूर्णांक ftrace_make_call(काष्ठा dyn_ftrace *rec, अचिन्हित दीर्घ addr)
अणु
	अचिन्हित पूर्णांक new;
	अचिन्हित दीर्घ ip = rec->ip;

	new = core_kernel_text(ip) ? insn_jal_ftrace_caller : insn_la_mcount[0];

#अगर_घोषित CONFIG_64BIT
	वापस ftrace_modअगरy_code(ip, new);
#अन्यथा
	वापस ftrace_modअगरy_code_2r(ip, new, core_kernel_text(ip) ?
						INSN_NOP : insn_la_mcount[1]);
#पूर्ण_अगर
पूर्ण

#घोषणा FTRACE_CALL_IP ((अचिन्हित दीर्घ)(&ftrace_call))

पूर्णांक ftrace_update_ftrace_func(ftrace_func_t func)
अणु
	अचिन्हित पूर्णांक new;

	new = INSN_JAL((अचिन्हित दीर्घ)func);

	वापस ftrace_modअगरy_code(FTRACE_CALL_IP, new);
पूर्ण

पूर्णांक __init ftrace_dyn_arch_init(व्योम)
अणु
	/* Encode the inकाष्ठाions when booting */
	ftrace_dyn_arch_init_insns();

	/* Remove "b ftrace_stub" to ensure ftrace_caller() is executed */
	ftrace_modअगरy_code(MCOUNT_ADDR, INSN_NOP);

	वापस 0;
पूर्ण
#पूर्ण_अगर	/* CONFIG_DYNAMIC_FTRACE */

#अगर_घोषित CONFIG_FUNCTION_GRAPH_TRACER

#अगर_घोषित CONFIG_DYNAMIC_FTRACE

बाह्य व्योम ftrace_graph_call(व्योम);
#घोषणा FTRACE_GRAPH_CALL_IP	((अचिन्हित दीर्घ)(&ftrace_graph_call))

पूर्णांक ftrace_enable_ftrace_graph_caller(व्योम)
अणु
	वापस ftrace_modअगरy_code(FTRACE_GRAPH_CALL_IP,
			insn_j_ftrace_graph_caller);
पूर्ण

पूर्णांक ftrace_disable_ftrace_graph_caller(व्योम)
अणु
	वापस ftrace_modअगरy_code(FTRACE_GRAPH_CALL_IP, INSN_NOP);
पूर्ण

#पूर्ण_अगर	/* CONFIG_DYNAMIC_FTRACE */

#अगर_अघोषित KBUILD_MCOUNT_RA_ADDRESS

#घोषणा S_RA_SP (0xafbf << 16)	/* sअणुd,wपूर्ण ra, offset(sp) */
#घोषणा S_R_SP	(0xafb0 << 16)	/* sअणुd,wपूर्ण R, offset(sp) */
#घोषणा OFFSET_MASK	0xffff	/* stack offset range: 0 ~ PT_SIZE */

अचिन्हित दीर्घ ftrace_get_parent_ra_addr(अचिन्हित दीर्घ self_ra, अचिन्हित दीर्घ
		old_parent_ra, अचिन्हित दीर्घ parent_ra_addr, अचिन्हित दीर्घ fp)
अणु
	अचिन्हित दीर्घ sp, ip, पंचांगp;
	अचिन्हित पूर्णांक code;
	पूर्णांक faulted;

	/*
	 * For module, move the ip from the वापस address after the
	 * inकाष्ठाion "lui v1, hi_16bit_of_mcount"(offset is 24), but क्रम
	 * kernel, move after the inकाष्ठाion "move ra, at"(offset is 16)
	 */
	ip = self_ra - (core_kernel_text(self_ra) ? 16 : 24);

	/*
	 * search the text until finding the non-store inकाष्ठाion or "sअणुd,wपूर्ण
	 * ra, offset(sp)" inकाष्ठाion
	 */
	करो अणु
		/* get the code at "ip": code = *(अचिन्हित पूर्णांक *)ip; */
		safe_load_code(code, ip, faulted);

		अगर (unlikely(faulted))
			वापस 0;
		/*
		 * If we hit the non-store inकाष्ठाion beक्रमe finding where the
		 * ra is stored, then this is a leaf function and it करोes not
		 * store the ra on the stack
		 */
		अगर ((code & S_R_SP) != S_R_SP)
			वापस parent_ra_addr;

		/* Move to the next inकाष्ठाion */
		ip -= 4;
	पूर्ण जबतक ((code & S_RA_SP) != S_RA_SP);

	sp = fp + (code & OFFSET_MASK);

	/* पंचांगp = *(अचिन्हित दीर्घ *)sp; */
	safe_load_stack(पंचांगp, sp, faulted);
	अगर (unlikely(faulted))
		वापस 0;

	अगर (पंचांगp == old_parent_ra)
		वापस sp;
	वापस 0;
पूर्ण

#पूर्ण_अगर	/* !KBUILD_MCOUNT_RA_ADDRESS */

/*
 * Hook the वापस address and push it in the stack of वापस addrs
 * in current thपढ़ो info.
 */
व्योम prepare_ftrace_वापस(अचिन्हित दीर्घ *parent_ra_addr, अचिन्हित दीर्घ self_ra,
			   अचिन्हित दीर्घ fp)
अणु
	अचिन्हित दीर्घ old_parent_ra;
	अचिन्हित दीर्घ वापस_hooker = (अचिन्हित दीर्घ)
	    &वापस_to_handler;
	पूर्णांक faulted, insns;

	अगर (unlikely(ftrace_graph_is_dead()))
		वापस;

	अगर (unlikely(atomic_पढ़ो(&current->tracing_graph_छोड़ो)))
		वापस;

	/*
	 * "parent_ra_addr" is the stack address where the वापस address of
	 * the caller of _mcount is saved.
	 *
	 * If gcc < 4.5, a leaf function करोes not save the वापस address
	 * in the stack address, so we "emulate" one in _mcount's stack space,
	 * and hijack it directly.
	 * For a non-leaf function, it करोes save the वापस address to its own
	 * stack space, so we can not hijack it directly, but need to find the
	 * real stack address, which is करोne by ftrace_get_parent_addr().
	 *
	 * If gcc >= 4.5, with the new -mmcount-ra-address option, क्रम a
	 * non-leaf function, the location of the वापस address will be saved
	 * to $12 क्रम us.
	 * For a leaf function, it just माला_दो a zero पूर्णांकo $12, so we handle
	 * it in ftrace_graph_caller() of mcount.S.
	 */

	/* old_parent_ra = *parent_ra_addr; */
	safe_load_stack(old_parent_ra, parent_ra_addr, faulted);
	अगर (unlikely(faulted))
		जाओ out;
#अगर_अघोषित KBUILD_MCOUNT_RA_ADDRESS
	parent_ra_addr = (अचिन्हित दीर्घ *)ftrace_get_parent_ra_addr(self_ra,
			old_parent_ra, (अचिन्हित दीर्घ)parent_ra_addr, fp);
	/*
	 * If fails when getting the stack address of the non-leaf function's
	 * ra, stop function graph tracer and वापस
	 */
	अगर (parent_ra_addr == शून्य)
		जाओ out;
#पूर्ण_अगर
	/* *parent_ra_addr = वापस_hooker; */
	safe_store_stack(वापस_hooker, parent_ra_addr, faulted);
	अगर (unlikely(faulted))
		जाओ out;

	/*
	 * Get the recorded ip of the current mcount calling site in the
	 * __mcount_loc section, which will be used to filter the function
	 * entries configured through the tracing/set_graph_function पूर्णांकerface.
	 */

	insns = core_kernel_text(self_ra) ? 2 : MCOUNT_OFFSET_INSNS + 1;
	self_ra -= (MCOUNT_INSN_SIZE * insns);

	अगर (function_graph_enter(old_parent_ra, self_ra, fp, शून्य))
		*parent_ra_addr = old_parent_ra;
	वापस;
out:
	ftrace_graph_stop();
	WARN_ON(1);
पूर्ण
#पूर्ण_अगर	/* CONFIG_FUNCTION_GRAPH_TRACER */

#अगर_घोषित CONFIG_FTRACE_SYSCALLS

#अगर_घोषित CONFIG_32BIT
अचिन्हित दीर्घ __init arch_syscall_addr(पूर्णांक nr)
अणु
	वापस (अचिन्हित दीर्घ)sys_call_table[nr - __NR_O32_Linux];
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_64BIT

अचिन्हित दीर्घ __init arch_syscall_addr(पूर्णांक nr)
अणु
#अगर_घोषित CONFIG_MIPS32_N32
	अगर (nr >= __NR_N32_Linux && nr < __NR_N32_Linux + __NR_N32_Linux_syscalls)
		वापस (अचिन्हित दीर्घ)sysn32_call_table[nr - __NR_N32_Linux];
#पूर्ण_अगर
	अगर (nr >= __NR_64_Linux  && nr < __NR_64_Linux + __NR_64_Linux_syscalls)
		वापस (अचिन्हित दीर्घ)sys_call_table[nr - __NR_64_Linux];
#अगर_घोषित CONFIG_MIPS32_O32
	अगर (nr >= __NR_O32_Linux && nr < __NR_O32_Linux + __NR_O32_Linux_syscalls)
		वापस (अचिन्हित दीर्घ)sys32_call_table[nr - __NR_O32_Linux];
#पूर्ण_अगर

	वापस (अचिन्हित दीर्घ) &sys_ni_syscall;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* CONFIG_FTRACE_SYSCALLS */
