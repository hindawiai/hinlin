<शैली गुरु>
/*
 * Ftrace support क्रम Microblaze.
 *
 * Copyright (C) 2009 Michal Simek <monstr@monstr.eu>
 * Copyright (C) 2009 PetaLogix
 *
 * Based on MIPS and PowerPC ftrace code
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License. See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 */

#समावेश <यंत्र/cacheflush.h>
#समावेश <linux/ftrace.h>

#अगर_घोषित CONFIG_FUNCTION_GRAPH_TRACER
/*
 * Hook the वापस address and push it in the stack of वापस addrs
 * in current thपढ़ो info.
 */
व्योम prepare_ftrace_वापस(अचिन्हित दीर्घ *parent, अचिन्हित दीर्घ self_addr)
अणु
	अचिन्हित दीर्घ old;
	पूर्णांक faulted;
	अचिन्हित दीर्घ वापस_hooker = (अचिन्हित दीर्घ)
				&वापस_to_handler;

	अगर (unlikely(ftrace_graph_is_dead()))
		वापस;

	अगर (unlikely(atomic_पढ़ो(&current->tracing_graph_छोड़ो)))
		वापस;

	/*
	 * Protect against fault, even अगर it shouldn't
	 * happen. This tool is too much पूर्णांकrusive to
	 * ignore such a protection.
	 */
	यंत्र अस्थिर("	1:	lwi	%0, %2, 0;"		\
			"2:	swi	%3, %2, 0;"		\
			"	addik	%1, r0, 0;"		\
			"3:"					\
			"	.section .fixup, \"ax\";"	\
			"4:	brid	3b;"			\
			"	addik	%1, r0, 1;"		\
			"	.previous;"			\
			"	.section __ex_table,\"a\";"	\
			"	.word	1b,4b;"			\
			"	.word	2b,4b;"			\
			"	.previous;"			\
			: "=&r" (old), "=r" (faulted)
			: "r" (parent), "r" (वापस_hooker)
	);

	flush_dcache_range((u32)parent, (u32)parent + 4);
	flush_icache_range((u32)parent, (u32)parent + 4);

	अगर (unlikely(faulted)) अणु
		ftrace_graph_stop();
		WARN_ON(1);
		वापस;
	पूर्ण

	अगर (function_graph_enter(old, self_addr, 0, शून्य))
		*parent = old;
पूर्ण
#पूर्ण_अगर /* CONFIG_FUNCTION_GRAPH_TRACER */

#अगर_घोषित CONFIG_DYNAMIC_FTRACE
/* save value to addr - it is save to करो it in यंत्र */
अटल पूर्णांक ftrace_modअगरy_code(अचिन्हित दीर्घ addr, अचिन्हित पूर्णांक value)
अणु
	पूर्णांक faulted = 0;

	__यंत्र__ __अस्थिर__("	1:	swi	%2, %1, 0;"		\
				"	addik	%0, r0, 0;"		\
				"2:"					\
				"	.section .fixup, \"ax\";"	\
				"3:	brid	2b;"			\
				"	addik	%0, r0, 1;"		\
				"	.previous;"			\
				"	.section __ex_table,\"a\";"	\
				"	.word	1b,3b;"			\
				"	.previous;"			\
				: "=r" (faulted)
				: "r" (addr), "r" (value)
	);

	अगर (unlikely(faulted))
		वापस -EFAULT;

	flush_dcache_range(addr, addr + 4);
	flush_icache_range(addr, addr + 4);

	वापस 0;
पूर्ण

#घोषणा MICROBLAZE_NOP 0x80000000
#घोषणा MICROBLAZE_BRI 0xb800000C

अटल अचिन्हित पूर्णांक recorded; /* अगर save was or not */
अटल अचिन्हित पूर्णांक imm; /* saving whole imm inकाष्ठाion */

/* There are two approaches howto solve ftrace_make nop function - look below */
#अघोषित USE_FTRACE_NOP

#अगर_घोषित USE_FTRACE_NOP
अटल अचिन्हित पूर्णांक bralid; /* saving whole bralid inकाष्ठाion */
#पूर्ण_अगर

पूर्णांक ftrace_make_nop(काष्ठा module *mod,
			काष्ठा dyn_ftrace *rec, अचिन्हित दीर्घ addr)
अणु
	/* we have this part of code which we are working with
	 * b000c000        imm     -16384
	 * b9fc8e30        bralid  r15, -29136     // c0008e30 <_mcount>
	 * 80000000        or      r0, r0, r0
	 *
	 * The first solution (!USE_FTRACE_NOP-could be called branch solution)
	 * b000c000        bri	12 (0xC - jump to any other inकाष्ठाion)
	 * b9fc8e30        bralid  r15, -29136     // c0008e30 <_mcount>
	 * 80000000        or      r0, r0, r0
	 * any other inकाष्ठाion
	 *
	 * The second solution (USE_FTRACE_NOP) - no jump just nops
	 * 80000000        or      r0, r0, r0
	 * 80000000        or      r0, r0, r0
	 * 80000000        or      r0, r0, r0
	 */
	पूर्णांक ret = 0;

	अगर (recorded == 0) अणु
		recorded = 1;
		imm = *(अचिन्हित पूर्णांक *)rec->ip;
		pr_debug("%s: imm:0x%x\n", __func__, imm);
#अगर_घोषित USE_FTRACE_NOP
		bralid = *(अचिन्हित पूर्णांक *)(rec->ip + 4);
		pr_debug("%s: bralid 0x%x\n", __func__, bralid);
#पूर्ण_अगर /* USE_FTRACE_NOP */
	पूर्ण

#अगर_घोषित USE_FTRACE_NOP
	ret = ftrace_modअगरy_code(rec->ip, MICROBLAZE_NOP);
	ret += ftrace_modअगरy_code(rec->ip + 4, MICROBLAZE_NOP);
#अन्यथा /* USE_FTRACE_NOP */
	ret = ftrace_modअगरy_code(rec->ip, MICROBLAZE_BRI);
#पूर्ण_अगर /* USE_FTRACE_NOP */
	वापस ret;
पूर्ण

/* I believe that first is called ftrace_make_nop beक्रमe this function */
पूर्णांक ftrace_make_call(काष्ठा dyn_ftrace *rec, अचिन्हित दीर्घ addr)
अणु
	पूर्णांक ret;
	pr_debug("%s: addr:0x%x, rec->ip: 0x%x, imm:0x%x\n",
		__func__, (अचिन्हित पूर्णांक)addr, (अचिन्हित पूर्णांक)rec->ip, imm);
	ret = ftrace_modअगरy_code(rec->ip, imm);
#अगर_घोषित USE_FTRACE_NOP
	pr_debug("%s: bralid:0x%x\n", __func__, bralid);
	ret += ftrace_modअगरy_code(rec->ip + 4, bralid);
#पूर्ण_अगर /* USE_FTRACE_NOP */
	वापस ret;
पूर्ण

पूर्णांक __init ftrace_dyn_arch_init(व्योम)
अणु
	वापस 0;
पूर्ण

पूर्णांक ftrace_update_ftrace_func(ftrace_func_t func)
अणु
	अचिन्हित दीर्घ ip = (अचिन्हित दीर्घ)(&ftrace_call);
	अचिन्हित पूर्णांक upper = (अचिन्हित पूर्णांक)func;
	अचिन्हित पूर्णांक lower = (अचिन्हित पूर्णांक)func;
	पूर्णांक ret = 0;

	/* create proper saving to ftrace_call poll */
	upper = 0xb0000000 + (upper >> 16); /* imm func_upper */
	lower = 0x32800000 + (lower & 0xFFFF); /* addik r20, r0, func_lower */

	pr_debug("%s: func=0x%x, ip=0x%x, upper=0x%x, lower=0x%x\n",
		__func__, (अचिन्हित पूर्णांक)func, (अचिन्हित पूर्णांक)ip, upper, lower);

	/* save upper and lower code */
	ret = ftrace_modअगरy_code(ip, upper);
	ret += ftrace_modअगरy_code(ip + 4, lower);

	/* We just need to replace the rtsd r15, 8 with NOP */
	ret += ftrace_modअगरy_code((अचिन्हित दीर्घ)&ftrace_caller,
				  MICROBLAZE_NOP);

	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_FUNCTION_GRAPH_TRACER
अचिन्हित पूर्णांक old_jump; /* saving place क्रम jump inकाष्ठाion */

पूर्णांक ftrace_enable_ftrace_graph_caller(व्योम)
अणु
	अचिन्हित पूर्णांक ret;
	अचिन्हित दीर्घ ip = (अचिन्हित दीर्घ)(&ftrace_call_graph);

	old_jump = *(अचिन्हित पूर्णांक *)ip; /* save jump over inकाष्ठाion */
	ret = ftrace_modअगरy_code(ip, MICROBLAZE_NOP);

	pr_debug("%s: Replace instruction: 0x%x\n", __func__, old_jump);
	वापस ret;
पूर्ण

पूर्णांक ftrace_disable_ftrace_graph_caller(व्योम)
अणु
	अचिन्हित पूर्णांक ret;
	अचिन्हित दीर्घ ip = (अचिन्हित दीर्घ)(&ftrace_call_graph);

	ret = ftrace_modअगरy_code(ip, old_jump);

	pr_debug("%s\n", __func__);
	वापस ret;
पूर्ण
#पूर्ण_अगर /* CONFIG_FUNCTION_GRAPH_TRACER */
#पूर्ण_अगर /* CONFIG_DYNAMIC_FTRACE */
