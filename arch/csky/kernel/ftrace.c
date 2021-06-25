<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (C) 2018 Hangzhou C-SKY Microप्रणालीs co.,ltd.

#समावेश <linux/ftrace.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/stop_machine.h>
#समावेश <यंत्र/cacheflush.h>

#अगर_घोषित CONFIG_DYNAMIC_FTRACE

#घोषणा NOP		0x4000
#घोषणा NOP32_HI	0xc400
#घोषणा NOP32_LO	0x4820
#घोषणा PUSH_LR		0x14d0
#घोषणा MOVIH_LINK	0xea3a
#घोषणा ORI_LINK	0xef5a
#घोषणा JSR_LINK	0xe8fa
#घोषणा BSR_LINK	0xe000

/*
 * Gcc-csky with -pg will insert stub in function prologue:
 *	push	lr
 *	jbsr	_mcount
 *	nop32
 *	nop32
 *
 * If the (callee - current_pc) is less then 64MB, we'll use bsr:
 *	push	lr
 *	bsr	_mcount
 *	nop32
 *	nop32
 * अन्यथा we'll use (movih + ori + jsr):
 *	push	lr
 *	movih	r26, ...
 *	ori	r26, ...
 *	jsr	r26
 *
 * (r26 is our reserved link-reg)
 *
 */
अटल अंतरभूत व्योम make_jbsr(अचिन्हित दीर्घ callee, अचिन्हित दीर्घ pc,
			     uपूर्णांक16_t *call, bool nolr)
अणु
	दीर्घ offset;

	call[0]	= nolr ? NOP : PUSH_LR;

	offset = (दीर्घ) callee - (दीर्घ) pc;

	अगर (unlikely(offset < -67108864 || offset > 67108864)) अणु
		call[1] = MOVIH_LINK;
		call[2] = callee >> 16;
		call[3] = ORI_LINK;
		call[4] = callee & 0xffff;
		call[5] = JSR_LINK;
		call[6] = 0;
	पूर्ण अन्यथा अणु
		offset = offset >> 1;

		call[1] = BSR_LINK |
			 ((uपूर्णांक16_t)((अचिन्हित दीर्घ) offset >> 16) & 0x3ff);
		call[2] = (uपूर्णांक16_t)((अचिन्हित दीर्घ) offset & 0xffff);
		call[3] = call[5] = NOP32_HI;
		call[4] = call[6] = NOP32_LO;
	पूर्ण
पूर्ण

अटल uपूर्णांक16_t nops[7] = अणुNOP, NOP32_HI, NOP32_LO, NOP32_HI, NOP32_LO,
				NOP32_HI, NOP32_LOपूर्ण;
अटल पूर्णांक ftrace_check_current_nop(अचिन्हित दीर्घ hook)
अणु
	uपूर्णांक16_t olds[7];
	अचिन्हित दीर्घ hook_pos = hook - 2;

	अगर (copy_from_kernel_nofault((व्योम *)olds, (व्योम *)hook_pos,
			माप(nops)))
		वापस -EFAULT;

	अगर (स_भेद((व्योम *)nops, (व्योम *)olds, माप(nops))) अणु
		pr_err("%p: nop but get (%04x %04x %04x %04x %04x %04x %04x)\n",
			(व्योम *)hook_pos,
			olds[0], olds[1], olds[2], olds[3], olds[4], olds[5],
			olds[6]);

		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ftrace_modअगरy_code(अचिन्हित दीर्घ hook, अचिन्हित दीर्घ target,
			      bool enable, bool nolr)
अणु
	uपूर्णांक16_t call[7];

	अचिन्हित दीर्घ hook_pos = hook - 2;
	पूर्णांक ret = 0;

	make_jbsr(target, hook, call, nolr);

	ret = copy_to_kernel_nofault((व्योम *)hook_pos, enable ? call : nops,
				 माप(nops));
	अगर (ret)
		वापस -EPERM;

	flush_icache_range(hook_pos, hook_pos + MCOUNT_INSN_SIZE);

	वापस 0;
पूर्ण

पूर्णांक ftrace_make_call(काष्ठा dyn_ftrace *rec, अचिन्हित दीर्घ addr)
अणु
	पूर्णांक ret = ftrace_check_current_nop(rec->ip);

	अगर (ret)
		वापस ret;

	वापस ftrace_modअगरy_code(rec->ip, addr, true, false);
पूर्ण

पूर्णांक ftrace_make_nop(काष्ठा module *mod, काष्ठा dyn_ftrace *rec,
		    अचिन्हित दीर्घ addr)
अणु
	वापस ftrace_modअगरy_code(rec->ip, addr, false, false);
पूर्ण

पूर्णांक ftrace_update_ftrace_func(ftrace_func_t func)
अणु
	पूर्णांक ret = ftrace_modअगरy_code((अचिन्हित दीर्घ)&ftrace_call,
				(अचिन्हित दीर्घ)func, true, true);
	अगर (!ret)
		ret = ftrace_modअगरy_code((अचिन्हित दीर्घ)&ftrace_regs_call,
				(अचिन्हित दीर्घ)func, true, true);
	वापस ret;
पूर्ण

पूर्णांक __init ftrace_dyn_arch_init(व्योम)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_DYNAMIC_FTRACE */

#अगर_घोषित CONFIG_DYNAMIC_FTRACE_WITH_REGS
पूर्णांक ftrace_modअगरy_call(काष्ठा dyn_ftrace *rec, अचिन्हित दीर्घ old_addr,
		       अचिन्हित दीर्घ addr)
अणु
	वापस ftrace_modअगरy_code(rec->ip, addr, true, true);
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_FUNCTION_GRAPH_TRACER
व्योम prepare_ftrace_वापस(अचिन्हित दीर्घ *parent, अचिन्हित दीर्घ self_addr,
			   अचिन्हित दीर्घ frame_poपूर्णांकer)
अणु
	अचिन्हित दीर्घ वापस_hooker = (अचिन्हित दीर्घ)&वापस_to_handler;
	अचिन्हित दीर्घ old;

	अगर (unlikely(atomic_पढ़ो(&current->tracing_graph_छोड़ो)))
		वापस;

	old = *parent;

	अगर (!function_graph_enter(old, self_addr,
			*(अचिन्हित दीर्घ *)frame_poपूर्णांकer, parent)) अणु
		/*
		 * For csky-gcc function has sub-call:
		 * subi	sp,	sp, 8
		 * stw	r8,	(sp, 0)
		 * mov	r8,	sp
		 * st.w r15,	(sp, 0x4)
		 * push	r15
		 * jl	_mcount
		 * We only need set *parent क्रम resume
		 *
		 * For csky-gcc function has no sub-call:
		 * subi	sp,	sp, 4
		 * stw	r8,	(sp, 0)
		 * mov	r8,	sp
		 * push	r15
		 * jl	_mcount
		 * We need set *parent and *(frame_poपूर्णांकer + 4) क्रम resume,
		 * because lr is resumed twice.
		 */
		*parent = वापस_hooker;
		frame_poपूर्णांकer += 4;
		अगर (*(अचिन्हित दीर्घ *)frame_poपूर्णांकer == old)
			*(अचिन्हित दीर्घ *)frame_poपूर्णांकer = वापस_hooker;
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_DYNAMIC_FTRACE
पूर्णांक ftrace_enable_ftrace_graph_caller(व्योम)
अणु
	वापस ftrace_modअगरy_code((अचिन्हित दीर्घ)&ftrace_graph_call,
			(अचिन्हित दीर्घ)&ftrace_graph_caller, true, true);
पूर्ण

पूर्णांक ftrace_disable_ftrace_graph_caller(व्योम)
अणु
	वापस ftrace_modअगरy_code((अचिन्हित दीर्घ)&ftrace_graph_call,
			(अचिन्हित दीर्घ)&ftrace_graph_caller, false, true);
पूर्ण
#पूर्ण_अगर /* CONFIG_DYNAMIC_FTRACE */
#पूर्ण_अगर /* CONFIG_FUNCTION_GRAPH_TRACER */

#अगर_घोषित CONFIG_DYNAMIC_FTRACE
#अगर_अघोषित CONFIG_CPU_HAS_ICACHE_INS
काष्ठा ftrace_modअगरy_param अणु
	पूर्णांक command;
	atomic_t cpu_count;
पूर्ण;

अटल पूर्णांक __ftrace_modअगरy_code(व्योम *data)
अणु
	काष्ठा ftrace_modअगरy_param *param = data;

	अगर (atomic_inc_वापस(&param->cpu_count) == 1) अणु
		ftrace_modअगरy_all_code(param->command);
		atomic_inc(&param->cpu_count);
	पूर्ण अन्यथा अणु
		जबतक (atomic_पढ़ो(&param->cpu_count) <= num_online_cpus())
			cpu_relax();
		local_icache_inv_all(शून्य);
	पूर्ण

	वापस 0;
पूर्ण

व्योम arch_ftrace_update_code(पूर्णांक command)
अणु
	काष्ठा ftrace_modअगरy_param param = अणु command, ATOMIC_INIT(0) पूर्ण;

	stop_machine(__ftrace_modअगरy_code, &param, cpu_online_mask);
पूर्ण
#पूर्ण_अगर
#पूर्ण_अगर /* CONFIG_DYNAMIC_FTRACE */

/* _mcount is defined in abi's mcount.S */
EXPORT_SYMBOL(_mcount);
