<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#समावेश <linux/module.h>

#समावेश <linux/sched.h> /* क्रम wake_up_process() */
#समावेश <linux/ftrace.h>

व्योम my_direct_func(काष्ठा task_काष्ठा *p)
अणु
	trace_prपूर्णांकk("waking up %s-%d\n", p->comm, p->pid);
पूर्ण

बाह्य व्योम my_tramp(व्योम *);

यंत्र (
"	.pushsection    .text, \"ax\", @progbits\n"
"	.type		my_tramp, @function\n"
"	.globl		my_tramp\n"
"   my_tramp:"
"	pushq %rbp\n"
"	movq %rsp, %rbp\n"
"	pushq %rdi\n"
"	call my_direct_func\n"
"	popq %rdi\n"
"	leave\n"
"	ret\n"
"	.size		my_tramp, .-my_tramp\n"
"	.popsection\n"
);


अटल पूर्णांक __init ftrace_direct_init(व्योम)
अणु
	वापस रेजिस्टर_ftrace_direct((अचिन्हित दीर्घ)wake_up_process,
				     (अचिन्हित दीर्घ)my_tramp);
पूर्ण

अटल व्योम __निकास ftrace_direct_निकास(व्योम)
अणु
	unरेजिस्टर_ftrace_direct((अचिन्हित दीर्घ)wake_up_process,
				 (अचिन्हित दीर्घ)my_tramp);
पूर्ण

module_init(ftrace_direct_init);
module_निकास(ftrace_direct_निकास);

MODULE_AUTHOR("Steven Rostedt");
MODULE_DESCRIPTION("Example use case of using register_ftrace_direct()");
MODULE_LICENSE("GPL");
