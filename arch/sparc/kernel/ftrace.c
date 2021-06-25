<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/spinlock.h>
#समावेश <linux/hardirq.h>
#समावेश <linux/ftrace.h>
#समावेश <linux/percpu.h>
#समावेश <linux/init.h>
#समावेश <linux/list.h>
#समावेश <trace/syscall.h>

#समावेश <यंत्र/ftrace.h>

#अगर_घोषित CONFIG_DYNAMIC_FTRACE
अटल स्थिर u32 ftrace_nop = 0x01000000;

अटल u32 ftrace_call_replace(अचिन्हित दीर्घ ip, अचिन्हित दीर्घ addr)
अणु
	u32 call;
	s32 off;

	off = ((s32)addr - (s32)ip);
	call = 0x40000000 | ((u32)off >> 2);

	वापस call;
पूर्ण

अटल पूर्णांक ftrace_modअगरy_code(अचिन्हित दीर्घ ip, u32 old, u32 new)
अणु
	u32 replaced;
	पूर्णांक faulted;

	__यंत्र__ __अस्थिर__(
	"1:	cas	[%[ip]], %[old], %[new]\n"
	"	flush	%[ip]\n"
	"	mov	0, %[faulted]\n"
	"2:\n"
	"	.section .fixup,#alloc,#execinstr\n"
	"	.align	4\n"
	"3:	sethi	%%hi(2b), %[faulted]\n"
	"	jmpl	%[faulted] + %%lo(2b), %%g0\n"
	"	 mov	1, %[faulted]\n"
	"	.previous\n"
	"	.section __ex_table,\"a\"\n"
	"	.align	4\n"
	"	.word	1b, 3b\n"
	"	.previous\n"
	: "=r" (replaced), [faulted] "=r" (faulted)
	: [new] "0" (new), [old] "r" (old), [ip] "r" (ip)
	: "memory");

	अगर (replaced != old && replaced != new)
		faulted = 2;

	वापस faulted;
पूर्ण

पूर्णांक ftrace_make_nop(काष्ठा module *mod, काष्ठा dyn_ftrace *rec, अचिन्हित दीर्घ addr)
अणु
	अचिन्हित दीर्घ ip = rec->ip;
	u32 old, new;

	old = ftrace_call_replace(ip, addr);
	new = ftrace_nop;
	वापस ftrace_modअगरy_code(ip, old, new);
पूर्ण

पूर्णांक ftrace_make_call(काष्ठा dyn_ftrace *rec, अचिन्हित दीर्घ addr)
अणु
	अचिन्हित दीर्घ ip = rec->ip;
	u32 old, new;

	old = ftrace_nop;
	new = ftrace_call_replace(ip, addr);
	वापस ftrace_modअगरy_code(ip, old, new);
पूर्ण

पूर्णांक ftrace_update_ftrace_func(ftrace_func_t func)
अणु
	अचिन्हित दीर्घ ip = (अचिन्हित दीर्घ)(&ftrace_call);
	u32 old, new;

	old = *(u32 *) &ftrace_call;
	new = ftrace_call_replace(ip, (अचिन्हित दीर्घ)func);
	वापस ftrace_modअगरy_code(ip, old, new);
पूर्ण

पूर्णांक __init ftrace_dyn_arch_init(व्योम)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_FUNCTION_GRAPH_TRACER

#अगर_घोषित CONFIG_DYNAMIC_FTRACE
बाह्य व्योम ftrace_graph_call(व्योम);

पूर्णांक ftrace_enable_ftrace_graph_caller(व्योम)
अणु
	अचिन्हित दीर्घ ip = (अचिन्हित दीर्घ)(&ftrace_graph_call);
	u32 old, new;

	old = *(u32 *) &ftrace_graph_call;
	new = ftrace_call_replace(ip, (अचिन्हित दीर्घ) &ftrace_graph_caller);
	वापस ftrace_modअगरy_code(ip, old, new);
पूर्ण

पूर्णांक ftrace_disable_ftrace_graph_caller(व्योम)
अणु
	अचिन्हित दीर्घ ip = (अचिन्हित दीर्घ)(&ftrace_graph_call);
	u32 old, new;

	old = *(u32 *) &ftrace_graph_call;
	new = ftrace_call_replace(ip, (अचिन्हित दीर्घ) &ftrace_stub);

	वापस ftrace_modअगरy_code(ip, old, new);
पूर्ण

#पूर्ण_अगर /* !CONFIG_DYNAMIC_FTRACE */

/*
 * Hook the वापस address and push it in the stack of वापस addrs
 * in current thपढ़ो info.
 */
अचिन्हित दीर्घ prepare_ftrace_वापस(अचिन्हित दीर्घ parent,
				    अचिन्हित दीर्घ self_addr,
				    अचिन्हित दीर्घ frame_poपूर्णांकer)
अणु
	अचिन्हित दीर्घ वापस_hooker = (अचिन्हित दीर्घ) &वापस_to_handler;

	अगर (unlikely(atomic_पढ़ो(&current->tracing_graph_छोड़ो)))
		वापस parent + 8UL;

	अगर (function_graph_enter(parent, self_addr, frame_poपूर्णांकer, शून्य))
		वापस parent + 8UL;

	वापस वापस_hooker;
पूर्ण
#पूर्ण_अगर /* CONFIG_FUNCTION_GRAPH_TRACER */
