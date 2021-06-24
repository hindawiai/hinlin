<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#समावेश <linux/module.h>

#समावेश <linux/mm.h> /* क्रम handle_mm_fault() */
#समावेश <linux/ftrace.h>

व्योम my_direct_func(काष्ठा vm_area_काष्ठा *vma,
			अचिन्हित दीर्घ address, अचिन्हित पूर्णांक flags)
अणु
	trace_prपूर्णांकk("handle mm fault vma=%p address=%lx flags=%x\n",
		     vma, address, flags);
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
"	pushq %rsi\n"
"	pushq %rdx\n"
"	call my_direct_func\n"
"	popq %rdx\n"
"	popq %rsi\n"
"	popq %rdi\n"
"	leave\n"
"	ret\n"
"	.size		my_tramp, .-my_tramp\n"
"	.popsection\n"
);


अटल पूर्णांक __init ftrace_direct_init(व्योम)
अणु
	वापस रेजिस्टर_ftrace_direct((अचिन्हित दीर्घ)handle_mm_fault,
				     (अचिन्हित दीर्घ)my_tramp);
पूर्ण

अटल व्योम __निकास ftrace_direct_निकास(व्योम)
अणु
	unरेजिस्टर_ftrace_direct((अचिन्हित दीर्घ)handle_mm_fault,
				 (अचिन्हित दीर्घ)my_tramp);
पूर्ण

module_init(ftrace_direct_init);
module_निकास(ftrace_direct_निकास);

MODULE_AUTHOR("Steven Rostedt");
MODULE_DESCRIPTION("Another example use case of using register_ftrace_direct()");
MODULE_LICENSE("GPL");
