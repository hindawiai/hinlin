<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#समावेश <linux/module.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/ftrace.h>

व्योम my_direct_func1(व्योम)
अणु
	trace_prपूर्णांकk("my direct func1\n");
पूर्ण

व्योम my_direct_func2(व्योम)
अणु
	trace_prपूर्णांकk("my direct func2\n");
पूर्ण

बाह्य व्योम my_tramp1(व्योम *);
बाह्य व्योम my_tramp2(व्योम *);

अटल अचिन्हित दीर्घ my_ip = (अचिन्हित दीर्घ)schedule;

यंत्र (
"	.pushsection    .text, \"ax\", @progbits\n"
"	.type		my_tramp1, @function\n"
"	.globl		my_tramp1\n"
"   my_tramp1:"
"	pushq %rbp\n"
"	movq %rsp, %rbp\n"
"	call my_direct_func1\n"
"	leave\n"
"	.size		my_tramp1, .-my_tramp1\n"
"	ret\n"
"	.type		my_tramp2, @function\n"
"	.globl		my_tramp2\n"
"   my_tramp2:"
"	pushq %rbp\n"
"	movq %rsp, %rbp\n"
"	call my_direct_func2\n"
"	leave\n"
"	ret\n"
"	.size		my_tramp2, .-my_tramp2\n"
"	.popsection\n"
);

अटल अचिन्हित दीर्घ my_tramp = (अचिन्हित दीर्घ)my_tramp1;
अटल अचिन्हित दीर्घ tramps[2] = अणु
	(अचिन्हित दीर्घ)my_tramp1,
	(अचिन्हित दीर्घ)my_tramp2,
पूर्ण;

अटल पूर्णांक simple_thपढ़ो(व्योम *arg)
अणु
	अटल पूर्णांक t;
	पूर्णांक ret = 0;

	जबतक (!kthपढ़ो_should_stop()) अणु
		set_current_state(TASK_INTERRUPTIBLE);
		schedule_समयout(2 * HZ);

		अगर (ret)
			जारी;
		t ^= 1;
		ret = modअगरy_ftrace_direct(my_ip, my_tramp, tramps[t]);
		अगर (!ret)
			my_tramp = tramps[t];
		WARN_ON_ONCE(ret);
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा task_काष्ठा *simple_tsk;

अटल पूर्णांक __init ftrace_direct_init(व्योम)
अणु
	पूर्णांक ret;

	ret = रेजिस्टर_ftrace_direct(my_ip, my_tramp);
	अगर (!ret)
		simple_tsk = kthपढ़ो_run(simple_thपढ़ो, शून्य, "event-sample-fn");
	वापस ret;
पूर्ण

अटल व्योम __निकास ftrace_direct_निकास(व्योम)
अणु
	kthपढ़ो_stop(simple_tsk);
	unरेजिस्टर_ftrace_direct(my_ip, my_tramp);
पूर्ण

module_init(ftrace_direct_init);
module_निकास(ftrace_direct_निकास);

MODULE_AUTHOR("Steven Rostedt");
MODULE_DESCRIPTION("Example use case of using modify_ftrace_direct()");
MODULE_LICENSE("GPL");
