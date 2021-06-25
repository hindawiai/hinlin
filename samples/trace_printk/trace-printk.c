<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#समावेश <linux/module.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/irq_work.h>

/* Must not be अटल to क्रमce gcc to consider these non स्थिरant */
अक्षर *trace_prपूर्णांकk_test_global_str =
	"This is a dynamic string that will use trace_puts\n";

अक्षर *trace_prपूर्णांकk_test_global_str_irq =
	"(irq) This is a dynamic string that will use trace_puts\n";

अक्षर *trace_prपूर्णांकk_test_global_str_fmt =
	"%sThis is a %s that will use trace_printk\n";

अटल काष्ठा irq_work irqwork;

अटल व्योम trace_prपूर्णांकk_irq_work(काष्ठा irq_work *work)
अणु
	trace_prपूर्णांकk("(irq) This is a static string that will use trace_bputs\n");
	trace_prपूर्णांकk(trace_prपूर्णांकk_test_global_str_irq);

	trace_prपूर्णांकk("(irq) This is a %s that will use trace_bprintk()\n",
		     "static string");

	trace_prपूर्णांकk(trace_prपूर्णांकk_test_global_str_fmt,
		     "(irq) ", "dynamic string");
पूर्ण

अटल पूर्णांक __init trace_prपूर्णांकk_init(व्योम)
अणु
	init_irq_work(&irqwork, trace_prपूर्णांकk_irq_work);

	trace_prपूर्णांकk("This is a static string that will use trace_bputs\n");
	trace_prपूर्णांकk(trace_prपूर्णांकk_test_global_str);

	/* Kick off prपूर्णांकing in irq context */
	irq_work_queue(&irqwork);
	irq_work_sync(&irqwork);

	trace_prपूर्णांकk("This is a %s that will use trace_bprintk()\n",
		     "static string");

	trace_prपूर्णांकk(trace_prपूर्णांकk_test_global_str_fmt, "", "dynamic string");

	वापस 0;
पूर्ण

अटल व्योम __निकास trace_prपूर्णांकk_निकास(व्योम)
अणु
पूर्ण

module_init(trace_prपूर्णांकk_init);
module_निकास(trace_prपूर्णांकk_निकास);

MODULE_AUTHOR("Steven Rostedt");
MODULE_DESCRIPTION("trace-printk");
MODULE_LICENSE("GPL");
