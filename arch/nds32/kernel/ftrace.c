<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#समावेश <linux/ftrace.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/cacheflush.h>

#अगर_अघोषित CONFIG_DYNAMIC_FTRACE
बाह्य व्योम (*ftrace_trace_function)(अचिन्हित दीर्घ, अचिन्हित दीर्घ,
				     काष्ठा ftrace_ops*, काष्ठा pt_regs*);
बाह्य व्योम ftrace_graph_caller(व्योम);

noअंतरभूत व्योम __naked ftrace_stub(अचिन्हित दीर्घ ip, अचिन्हित दीर्घ parent_ip,
				  काष्ठा ftrace_ops *op, काष्ठा ftrace_regs *fregs)
अणु
	__यंत्र__ ("");  /* aव्योम to optimize as pure function */
पूर्ण

noअंतरभूत व्योम _mcount(अचिन्हित दीर्घ parent_ip)
अणु
	/* save all state by the compiler prologue */

	अचिन्हित दीर्घ ip = (अचिन्हित दीर्घ)__builtin_वापस_address(0);

	अगर (ftrace_trace_function != ftrace_stub)
		ftrace_trace_function(ip - MCOUNT_INSN_SIZE, parent_ip,
				      शून्य, शून्य);

#अगर_घोषित CONFIG_FUNCTION_GRAPH_TRACER
	अगर (ftrace_graph_वापस != (trace_func_graph_ret_t)ftrace_stub
	    || ftrace_graph_entry != ftrace_graph_entry_stub)
		ftrace_graph_caller();
#पूर्ण_अगर

	/* restore all state by the compiler epilogue */
पूर्ण
EXPORT_SYMBOL(_mcount);

#अन्यथा /* CONFIG_DYNAMIC_FTRACE */

noअंतरभूत व्योम __naked ftrace_stub(अचिन्हित दीर्घ ip, अचिन्हित दीर्घ parent_ip,
				  काष्ठा ftrace_ops *op, काष्ठा ftrace_regs *fregs)
अणु
	__यंत्र__ ("");  /* aव्योम to optimize as pure function */
पूर्ण

noअंतरभूत व्योम __naked _mcount(अचिन्हित दीर्घ parent_ip)
अणु
	__यंत्र__ ("");  /* aव्योम to optimize as pure function */
पूर्ण
EXPORT_SYMBOL(_mcount);

#घोषणा XSTR(s) STR(s)
#घोषणा STR(s) #s
व्योम _ftrace_caller(अचिन्हित दीर्घ parent_ip)
अणु
	/* save all state needed by the compiler prologue */

	/*
	 * prepare arguments क्रम real tracing function
	 * first  arg : __builtin_वापस_address(0) - MCOUNT_INSN_SIZE
	 * second arg : parent_ip
	 */
	__यंत्र__ __अस्थिर__ (
		"move $r1, %0				   \n\t"
		"addi $r0, %1, #-" XSTR(MCOUNT_INSN_SIZE) "\n\t"
		:
		: "r" (parent_ip), "r" (__builtin_वापस_address(0)));

	/* a placeholder क्रम the call to a real tracing function */
	__यंत्र__ __अस्थिर__ (
		"ftrace_call:		\n\t"
		"nop			\n\t"
		"nop			\n\t"
		"nop			\n\t");

#अगर_घोषित CONFIG_FUNCTION_GRAPH_TRACER
	/* a placeholder क्रम the call to ftrace_graph_caller */
	__यंत्र__ __अस्थिर__ (
		"ftrace_graph_call:	\n\t"
		"nop			\n\t"
		"nop			\n\t"
		"nop			\n\t");
#पूर्ण_अगर
	/* restore all state needed by the compiler epilogue */
पूर्ण

पूर्णांक __init ftrace_dyn_arch_init(व्योम)
अणु
	वापस 0;
पूर्ण

अटल अचिन्हित दीर्घ gen_sethi_insn(अचिन्हित दीर्घ addr)
अणु
	अचिन्हित दीर्घ opcode = 0x46000000;
	अचिन्हित दीर्घ imm = addr >> 12;
	अचिन्हित दीर्घ rt_num = 0xf << 20;

	वापस ENDIAN_CONVERT(opcode | rt_num | imm);
पूर्ण

अटल अचिन्हित दीर्घ gen_ori_insn(अचिन्हित दीर्घ addr)
अणु
	अचिन्हित दीर्घ opcode = 0x58000000;
	अचिन्हित दीर्घ imm = addr & 0x0000fff;
	अचिन्हित दीर्घ rt_num = 0xf << 20;
	अचिन्हित दीर्घ ra_num = 0xf << 15;

	वापस ENDIAN_CONVERT(opcode | rt_num | ra_num | imm);
पूर्ण

अटल अचिन्हित दीर्घ gen_jral_insn(अचिन्हित दीर्घ addr)
अणु
	अचिन्हित दीर्घ opcode = 0x4a000001;
	अचिन्हित दीर्घ rt_num = 0x1e << 20;
	अचिन्हित दीर्घ rb_num = 0xf << 10;

	वापस ENDIAN_CONVERT(opcode | rt_num | rb_num);
पूर्ण

अटल व्योम ftrace_gen_call_insn(अचिन्हित दीर्घ *call_insns,
				 अचिन्हित दीर्घ addr)
अणु
	call_insns[0] = gen_sethi_insn(addr); /* sethi $r15, imm20u       */
	call_insns[1] = gen_ori_insn(addr);   /* ori   $r15, $r15, imm15u */
	call_insns[2] = gen_jral_insn(addr);  /* jral  $lp,  $r15         */
पूर्ण

अटल पूर्णांक __ftrace_modअगरy_code(अचिन्हित दीर्घ pc, अचिन्हित दीर्घ *old_insn,
				अचिन्हित दीर्घ *new_insn, bool validate)
अणु
	अचिन्हित दीर्घ orig_insn[3];

	अगर (validate) अणु
		अगर (copy_from_kernel_nofault(orig_insn, (व्योम *)pc,
				MCOUNT_INSN_SIZE))
			वापस -EFAULT;
		अगर (स_भेद(orig_insn, old_insn, MCOUNT_INSN_SIZE))
			वापस -EINVAL;
	पूर्ण

	अगर (copy_to_kernel_nofault((व्योम *)pc, new_insn, MCOUNT_INSN_SIZE))
		वापस -EPERM;

	वापस 0;
पूर्ण

अटल पूर्णांक ftrace_modअगरy_code(अचिन्हित दीर्घ pc, अचिन्हित दीर्घ *old_insn,
			      अचिन्हित दीर्घ *new_insn, bool validate)
अणु
	पूर्णांक ret;

	ret = __ftrace_modअगरy_code(pc, old_insn, new_insn, validate);
	अगर (ret)
		वापस ret;

	flush_icache_range(pc, pc + MCOUNT_INSN_SIZE);

	वापस ret;
पूर्ण

पूर्णांक ftrace_update_ftrace_func(ftrace_func_t func)
अणु
	अचिन्हित दीर्घ pc = (अचिन्हित दीर्घ)&ftrace_call;
	अचिन्हित दीर्घ old_insn[3] = अणुINSN_NOP, INSN_NOP, INSN_NOPपूर्ण;
	अचिन्हित दीर्घ new_insn[3] = अणुINSN_NOP, INSN_NOP, INSN_NOPपूर्ण;

	अगर (func != ftrace_stub)
		ftrace_gen_call_insn(new_insn, (अचिन्हित दीर्घ)func);

	वापस ftrace_modअगरy_code(pc, old_insn, new_insn, false);
पूर्ण

पूर्णांक ftrace_make_call(काष्ठा dyn_ftrace *rec, अचिन्हित दीर्घ addr)
अणु
	अचिन्हित दीर्घ pc = rec->ip;
	अचिन्हित दीर्घ nop_insn[3] = अणुINSN_NOP, INSN_NOP, INSN_NOPपूर्ण;
	अचिन्हित दीर्घ call_insn[3] = अणुINSN_NOP, INSN_NOP, INSN_NOPपूर्ण;

	ftrace_gen_call_insn(call_insn, addr);

	वापस ftrace_modअगरy_code(pc, nop_insn, call_insn, true);
पूर्ण

पूर्णांक ftrace_make_nop(काष्ठा module *mod, काष्ठा dyn_ftrace *rec,
		    अचिन्हित दीर्घ addr)
अणु
	अचिन्हित दीर्घ pc = rec->ip;
	अचिन्हित दीर्घ nop_insn[3] = अणुINSN_NOP, INSN_NOP, INSN_NOPपूर्ण;
	अचिन्हित दीर्घ call_insn[3] = अणुINSN_NOP, INSN_NOP, INSN_NOPपूर्ण;

	ftrace_gen_call_insn(call_insn, addr);

	वापस ftrace_modअगरy_code(pc, call_insn, nop_insn, true);
पूर्ण
#पूर्ण_अगर /* CONFIG_DYNAMIC_FTRACE */

#अगर_घोषित CONFIG_FUNCTION_GRAPH_TRACER
व्योम prepare_ftrace_वापस(अचिन्हित दीर्घ *parent, अचिन्हित दीर्घ self_addr,
			   अचिन्हित दीर्घ frame_poपूर्णांकer)
अणु
	अचिन्हित दीर्घ वापस_hooker = (अचिन्हित दीर्घ)&वापस_to_handler;
	अचिन्हित दीर्घ old;

	अगर (unlikely(atomic_पढ़ो(&current->tracing_graph_छोड़ो)))
		वापस;

	old = *parent;

	अगर (!function_graph_enter(old, self_addr, frame_poपूर्णांकer, शून्य))
		*parent = वापस_hooker;
पूर्ण

noअंतरभूत व्योम ftrace_graph_caller(व्योम)
अणु
	अचिन्हित दीर्घ *parent_ip =
		(अचिन्हित दीर्घ *)(__builtin_frame_address(2) - 4);

	अचिन्हित दीर्घ selfpc =
		(अचिन्हित दीर्घ)(__builtin_वापस_address(1) - MCOUNT_INSN_SIZE);

	अचिन्हित दीर्घ frame_poपूर्णांकer =
		(अचिन्हित दीर्घ)__builtin_frame_address(3);

	prepare_ftrace_वापस(parent_ip, selfpc, frame_poपूर्णांकer);
पूर्ण

बाह्य अचिन्हित दीर्घ ftrace_वापस_to_handler(अचिन्हित दीर्घ frame_poपूर्णांकer);
व्योम __naked वापस_to_handler(व्योम)
अणु
	__यंत्र__ __अस्थिर__ (
		/* save state needed by the ABI     */
		"smw.adm $r0,[$sp],$r1,#0x0  \n\t"

		/* get original वापस address      */
		"move $r0, $fp               \n\t"
		"bal ftrace_return_to_handler\n\t"
		"move $lp, $r0               \n\t"

		/* restore state needed by the ABI  */
		"lmw.bim $r0,[$sp],$r1,#0x0  \n\t");
पूर्ण

#अगर_घोषित CONFIG_DYNAMIC_FTRACE
बाह्य अचिन्हित दीर्घ ftrace_graph_call;

अटल पूर्णांक ftrace_modअगरy_graph_caller(bool enable)
अणु
	अचिन्हित दीर्घ pc = (अचिन्हित दीर्घ)&ftrace_graph_call;
	अचिन्हित दीर्घ nop_insn[3] = अणुINSN_NOP, INSN_NOP, INSN_NOPपूर्ण;
	अचिन्हित दीर्घ call_insn[3] = अणुINSN_NOP, INSN_NOP, INSN_NOPपूर्ण;

	ftrace_gen_call_insn(call_insn, (अचिन्हित दीर्घ)ftrace_graph_caller);

	अगर (enable)
		वापस ftrace_modअगरy_code(pc, nop_insn, call_insn, true);
	अन्यथा
		वापस ftrace_modअगरy_code(pc, call_insn, nop_insn, true);
पूर्ण

पूर्णांक ftrace_enable_ftrace_graph_caller(व्योम)
अणु
	वापस ftrace_modअगरy_graph_caller(true);
पूर्ण

पूर्णांक ftrace_disable_ftrace_graph_caller(व्योम)
अणु
	वापस ftrace_modअगरy_graph_caller(false);
पूर्ण
#पूर्ण_अगर /* CONFIG_DYNAMIC_FTRACE */

#पूर्ण_अगर /* CONFIG_FUNCTION_GRAPH_TRACER */


#अगर_घोषित CONFIG_TRACE_IRQFLAGS
noअंतरभूत व्योम __trace_hardirqs_off(व्योम)
अणु
	trace_hardirqs_off();
पूर्ण
noअंतरभूत व्योम __trace_hardirqs_on(व्योम)
अणु
	trace_hardirqs_on();
पूर्ण
#पूर्ण_अगर /* CONFIG_TRACE_IRQFLAGS */
