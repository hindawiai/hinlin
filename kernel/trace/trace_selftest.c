<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Include in trace.c */

#समावेश <uapi/linux/sched/types.h>
#समावेश <linux/stringअगरy.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>

अटल अंतरभूत पूर्णांक trace_valid_entry(काष्ठा trace_entry *entry)
अणु
	चयन (entry->type) अणु
	हाल TRACE_FN:
	हाल TRACE_CTX:
	हाल TRACE_WAKE:
	हाल TRACE_STACK:
	हाल TRACE_PRINT:
	हाल TRACE_BRANCH:
	हाल TRACE_GRAPH_ENT:
	हाल TRACE_GRAPH_RET:
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक trace_test_buffer_cpu(काष्ठा array_buffer *buf, पूर्णांक cpu)
अणु
	काष्ठा ring_buffer_event *event;
	काष्ठा trace_entry *entry;
	अचिन्हित पूर्णांक loops = 0;

	जबतक ((event = ring_buffer_consume(buf->buffer, cpu, शून्य, शून्य))) अणु
		entry = ring_buffer_event_data(event);

		/*
		 * The ring buffer is a size of trace_buf_size, अगर
		 * we loop more than the size, there's something wrong
		 * with the ring buffer.
		 */
		अगर (loops++ > trace_buf_size) अणु
			prपूर्णांकk(KERN_CONT ".. bad ring buffer ");
			जाओ failed;
		पूर्ण
		अगर (!trace_valid_entry(entry)) अणु
			prपूर्णांकk(KERN_CONT ".. invalid entry %d ",
				entry->type);
			जाओ failed;
		पूर्ण
	पूर्ण
	वापस 0;

 failed:
	/* disable tracing */
	tracing_disabled = 1;
	prपूर्णांकk(KERN_CONT ".. corrupted trace buffer .. ");
	वापस -1;
पूर्ण

/*
 * Test the trace buffer to see अगर all the elements
 * are still sane.
 */
अटल पूर्णांक __maybe_unused trace_test_buffer(काष्ठा array_buffer *buf, अचिन्हित दीर्घ *count)
अणु
	अचिन्हित दीर्घ flags, cnt = 0;
	पूर्णांक cpu, ret = 0;

	/* Don't allow flipping of max traces now */
	local_irq_save(flags);
	arch_spin_lock(&buf->tr->max_lock);

	cnt = ring_buffer_entries(buf->buffer);

	/*
	 * The trace_test_buffer_cpu runs a जबतक loop to consume all data.
	 * If the calling tracer is broken, and is स्थिरantly filling
	 * the buffer, this will run क्रमever, and hard lock the box.
	 * We disable the ring buffer जबतक we करो this test to prevent
	 * a hard lock up.
	 */
	tracing_off();
	क्रम_each_possible_cpu(cpu) अणु
		ret = trace_test_buffer_cpu(buf, cpu);
		अगर (ret)
			अवरोध;
	पूर्ण
	tracing_on();
	arch_spin_unlock(&buf->tr->max_lock);
	local_irq_restore(flags);

	अगर (count)
		*count = cnt;

	वापस ret;
पूर्ण

अटल अंतरभूत व्योम warn_failed_init_tracer(काष्ठा tracer *trace, पूर्णांक init_ret)
अणु
	prपूर्णांकk(KERN_WARNING "Failed to init %s tracer, init returned %d\n",
		trace->name, init_ret);
पूर्ण
#अगर_घोषित CONFIG_FUNCTION_TRACER

#अगर_घोषित CONFIG_DYNAMIC_FTRACE

अटल पूर्णांक trace_selftest_test_probe1_cnt;
अटल व्योम trace_selftest_test_probe1_func(अचिन्हित दीर्घ ip,
					    अचिन्हित दीर्घ pip,
					    काष्ठा ftrace_ops *op,
					    काष्ठा ftrace_regs *fregs)
अणु
	trace_selftest_test_probe1_cnt++;
पूर्ण

अटल पूर्णांक trace_selftest_test_probe2_cnt;
अटल व्योम trace_selftest_test_probe2_func(अचिन्हित दीर्घ ip,
					    अचिन्हित दीर्घ pip,
					    काष्ठा ftrace_ops *op,
					    काष्ठा ftrace_regs *fregs)
अणु
	trace_selftest_test_probe2_cnt++;
पूर्ण

अटल पूर्णांक trace_selftest_test_probe3_cnt;
अटल व्योम trace_selftest_test_probe3_func(अचिन्हित दीर्घ ip,
					    अचिन्हित दीर्घ pip,
					    काष्ठा ftrace_ops *op,
					    काष्ठा ftrace_regs *fregs)
अणु
	trace_selftest_test_probe3_cnt++;
पूर्ण

अटल पूर्णांक trace_selftest_test_global_cnt;
अटल व्योम trace_selftest_test_global_func(अचिन्हित दीर्घ ip,
					    अचिन्हित दीर्घ pip,
					    काष्ठा ftrace_ops *op,
					    काष्ठा ftrace_regs *fregs)
अणु
	trace_selftest_test_global_cnt++;
पूर्ण

अटल पूर्णांक trace_selftest_test_dyn_cnt;
अटल व्योम trace_selftest_test_dyn_func(अचिन्हित दीर्घ ip,
					 अचिन्हित दीर्घ pip,
					 काष्ठा ftrace_ops *op,
					 काष्ठा ftrace_regs *fregs)
अणु
	trace_selftest_test_dyn_cnt++;
पूर्ण

अटल काष्ठा ftrace_ops test_probe1 = अणु
	.func			= trace_selftest_test_probe1_func,
पूर्ण;

अटल काष्ठा ftrace_ops test_probe2 = अणु
	.func			= trace_selftest_test_probe2_func,
पूर्ण;

अटल काष्ठा ftrace_ops test_probe3 = अणु
	.func			= trace_selftest_test_probe3_func,
पूर्ण;

अटल व्योम prपूर्णांक_counts(व्योम)
अणु
	prपूर्णांकk("(%d %d %d %d %d) ",
	       trace_selftest_test_probe1_cnt,
	       trace_selftest_test_probe2_cnt,
	       trace_selftest_test_probe3_cnt,
	       trace_selftest_test_global_cnt,
	       trace_selftest_test_dyn_cnt);
पूर्ण

अटल व्योम reset_counts(व्योम)
अणु
	trace_selftest_test_probe1_cnt = 0;
	trace_selftest_test_probe2_cnt = 0;
	trace_selftest_test_probe3_cnt = 0;
	trace_selftest_test_global_cnt = 0;
	trace_selftest_test_dyn_cnt = 0;
पूर्ण

अटल पूर्णांक trace_selftest_ops(काष्ठा trace_array *tr, पूर्णांक cnt)
अणु
	पूर्णांक save_ftrace_enabled = ftrace_enabled;
	काष्ठा ftrace_ops *dyn_ops;
	अक्षर *func1_name;
	अक्षर *func2_name;
	पूर्णांक len1;
	पूर्णांक len2;
	पूर्णांक ret = -1;

	prपूर्णांकk(KERN_CONT "PASSED\n");
	pr_info("Testing dynamic ftrace ops #%d: ", cnt);

	ftrace_enabled = 1;
	reset_counts();

	/* Handle PPC64 '.' name */
	func1_name = "*" __stringअगरy(DYN_FTRACE_TEST_NAME);
	func2_name = "*" __stringअगरy(DYN_FTRACE_TEST_NAME2);
	len1 = म_माप(func1_name);
	len2 = म_माप(func2_name);

	/*
	 * Probe 1 will trace function 1.
	 * Probe 2 will trace function 2.
	 * Probe 3 will trace functions 1 and 2.
	 */
	ftrace_set_filter(&test_probe1, func1_name, len1, 1);
	ftrace_set_filter(&test_probe2, func2_name, len2, 1);
	ftrace_set_filter(&test_probe3, func1_name, len1, 1);
	ftrace_set_filter(&test_probe3, func2_name, len2, 0);

	रेजिस्टर_ftrace_function(&test_probe1);
	रेजिस्टर_ftrace_function(&test_probe2);
	रेजिस्टर_ftrace_function(&test_probe3);
	/* First समय we are running with मुख्य function */
	अगर (cnt > 1) अणु
		ftrace_init_array_ops(tr, trace_selftest_test_global_func);
		रेजिस्टर_ftrace_function(tr->ops);
	पूर्ण

	DYN_FTRACE_TEST_NAME();

	prपूर्णांक_counts();

	अगर (trace_selftest_test_probe1_cnt != 1)
		जाओ out;
	अगर (trace_selftest_test_probe2_cnt != 0)
		जाओ out;
	अगर (trace_selftest_test_probe3_cnt != 1)
		जाओ out;
	अगर (cnt > 1) अणु
		अगर (trace_selftest_test_global_cnt == 0)
			जाओ out;
	पूर्ण

	DYN_FTRACE_TEST_NAME2();

	prपूर्णांक_counts();

	अगर (trace_selftest_test_probe1_cnt != 1)
		जाओ out;
	अगर (trace_selftest_test_probe2_cnt != 1)
		जाओ out;
	अगर (trace_selftest_test_probe3_cnt != 2)
		जाओ out;

	/* Add a dynamic probe */
	dyn_ops = kzalloc(माप(*dyn_ops), GFP_KERNEL);
	अगर (!dyn_ops) अणु
		prपूर्णांकk("MEMORY ERROR ");
		जाओ out;
	पूर्ण

	dyn_ops->func = trace_selftest_test_dyn_func;

	रेजिस्टर_ftrace_function(dyn_ops);

	trace_selftest_test_global_cnt = 0;

	DYN_FTRACE_TEST_NAME();

	prपूर्णांक_counts();

	अगर (trace_selftest_test_probe1_cnt != 2)
		जाओ out_मुक्त;
	अगर (trace_selftest_test_probe2_cnt != 1)
		जाओ out_मुक्त;
	अगर (trace_selftest_test_probe3_cnt != 3)
		जाओ out_मुक्त;
	अगर (cnt > 1) अणु
		अगर (trace_selftest_test_global_cnt == 0)
			जाओ out_मुक्त;
	पूर्ण
	अगर (trace_selftest_test_dyn_cnt == 0)
		जाओ out_मुक्त;

	DYN_FTRACE_TEST_NAME2();

	prपूर्णांक_counts();

	अगर (trace_selftest_test_probe1_cnt != 2)
		जाओ out_मुक्त;
	अगर (trace_selftest_test_probe2_cnt != 2)
		जाओ out_मुक्त;
	अगर (trace_selftest_test_probe3_cnt != 4)
		जाओ out_मुक्त;

	ret = 0;
 out_मुक्त:
	unरेजिस्टर_ftrace_function(dyn_ops);
	kमुक्त(dyn_ops);

 out:
	/* Purposely unरेजिस्टर in the same order */
	unरेजिस्टर_ftrace_function(&test_probe1);
	unरेजिस्टर_ftrace_function(&test_probe2);
	unरेजिस्टर_ftrace_function(&test_probe3);
	अगर (cnt > 1)
		unरेजिस्टर_ftrace_function(tr->ops);
	ftrace_reset_array_ops(tr);

	/* Make sure everything is off */
	reset_counts();
	DYN_FTRACE_TEST_NAME();
	DYN_FTRACE_TEST_NAME();

	अगर (trace_selftest_test_probe1_cnt ||
	    trace_selftest_test_probe2_cnt ||
	    trace_selftest_test_probe3_cnt ||
	    trace_selftest_test_global_cnt ||
	    trace_selftest_test_dyn_cnt)
		ret = -1;

	ftrace_enabled = save_ftrace_enabled;

	वापस ret;
पूर्ण

/* Test dynamic code modअगरication and ftrace filters */
अटल पूर्णांक trace_selftest_startup_dynamic_tracing(काष्ठा tracer *trace,
						  काष्ठा trace_array *tr,
						  पूर्णांक (*func)(व्योम))
अणु
	पूर्णांक save_ftrace_enabled = ftrace_enabled;
	अचिन्हित दीर्घ count;
	अक्षर *func_name;
	पूर्णांक ret;

	/* The ftrace test PASSED */
	prपूर्णांकk(KERN_CONT "PASSED\n");
	pr_info("Testing dynamic ftrace: ");

	/* enable tracing, and record the filter function */
	ftrace_enabled = 1;

	/* passed in by parameter to fool gcc from optimizing */
	func();

	/*
	 * Some archs *cough*PowerPC*cough* add अक्षरacters to the
	 * start of the function names. We simply put a '*' to
	 * accommodate them.
	 */
	func_name = "*" __stringअगरy(DYN_FTRACE_TEST_NAME);

	/* filter only on our function */
	ftrace_set_global_filter(func_name, म_माप(func_name), 1);

	/* enable tracing */
	ret = tracer_init(trace, tr);
	अगर (ret) अणु
		warn_failed_init_tracer(trace, ret);
		जाओ out;
	पूर्ण

	/* Sleep क्रम a 1/10 of a second */
	msleep(100);

	/* we should have nothing in the buffer */
	ret = trace_test_buffer(&tr->array_buffer, &count);
	अगर (ret)
		जाओ out;

	अगर (count) अणु
		ret = -1;
		prपूर्णांकk(KERN_CONT ".. filter did not filter .. ");
		जाओ out;
	पूर्ण

	/* call our function again */
	func();

	/* sleep again */
	msleep(100);

	/* stop the tracing. */
	tracing_stop();
	ftrace_enabled = 0;

	/* check the trace buffer */
	ret = trace_test_buffer(&tr->array_buffer, &count);

	ftrace_enabled = 1;
	tracing_start();

	/* we should only have one item */
	अगर (!ret && count != 1) अणु
		trace->reset(tr);
		prपूर्णांकk(KERN_CONT ".. filter failed count=%ld ..", count);
		ret = -1;
		जाओ out;
	पूर्ण

	/* Test the ops with global tracing running */
	ret = trace_selftest_ops(tr, 1);
	trace->reset(tr);

 out:
	ftrace_enabled = save_ftrace_enabled;

	/* Enable tracing on all functions again */
	ftrace_set_global_filter(शून्य, 0, 1);

	/* Test the ops with global tracing off */
	अगर (!ret)
		ret = trace_selftest_ops(tr, 2);

	वापस ret;
पूर्ण

अटल पूर्णांक trace_selftest_recursion_cnt;
अटल व्योम trace_selftest_test_recursion_func(अचिन्हित दीर्घ ip,
					       अचिन्हित दीर्घ pip,
					       काष्ठा ftrace_ops *op,
					       काष्ठा ftrace_regs *fregs)
अणु
	/*
	 * This function is रेजिस्टरed without the recursion safe flag.
	 * The ftrace infraकाष्ठाure should provide the recursion
	 * protection. If not, this will crash the kernel!
	 */
	अगर (trace_selftest_recursion_cnt++ > 10)
		वापस;
	DYN_FTRACE_TEST_NAME();
पूर्ण

अटल व्योम trace_selftest_test_recursion_safe_func(अचिन्हित दीर्घ ip,
						    अचिन्हित दीर्घ pip,
						    काष्ठा ftrace_ops *op,
						    काष्ठा ftrace_regs *fregs)
अणु
	/*
	 * We said we would provide our own recursion. By calling
	 * this function again, we should recurse back पूर्णांकo this function
	 * and count again. But this only happens अगर the arch supports
	 * all of ftrace features and nothing अन्यथा is using the function
	 * tracing utility.
	 */
	अगर (trace_selftest_recursion_cnt++)
		वापस;
	DYN_FTRACE_TEST_NAME();
पूर्ण

अटल काष्ठा ftrace_ops test_rec_probe = अणु
	.func			= trace_selftest_test_recursion_func,
	.flags			= FTRACE_OPS_FL_RECURSION,
पूर्ण;

अटल काष्ठा ftrace_ops test_recsafe_probe = अणु
	.func			= trace_selftest_test_recursion_safe_func,
पूर्ण;

अटल पूर्णांक
trace_selftest_function_recursion(व्योम)
अणु
	पूर्णांक save_ftrace_enabled = ftrace_enabled;
	अक्षर *func_name;
	पूर्णांक len;
	पूर्णांक ret;

	/* The previous test PASSED */
	pr_cont("PASSED\n");
	pr_info("Testing ftrace recursion: ");


	/* enable tracing, and record the filter function */
	ftrace_enabled = 1;

	/* Handle PPC64 '.' name */
	func_name = "*" __stringअगरy(DYN_FTRACE_TEST_NAME);
	len = म_माप(func_name);

	ret = ftrace_set_filter(&test_rec_probe, func_name, len, 1);
	अगर (ret) अणु
		pr_cont("*Could not set filter* ");
		जाओ out;
	पूर्ण

	ret = रेजिस्टर_ftrace_function(&test_rec_probe);
	अगर (ret) अणु
		pr_cont("*could not register callback* ");
		जाओ out;
	पूर्ण

	DYN_FTRACE_TEST_NAME();

	unरेजिस्टर_ftrace_function(&test_rec_probe);

	ret = -1;
	/*
	 * Recursion allows क्रम transitions between context,
	 * and may call the callback twice.
	 */
	अगर (trace_selftest_recursion_cnt != 1 &&
	    trace_selftest_recursion_cnt != 2) अणु
		pr_cont("*callback not called once (or twice) (%d)* ",
			trace_selftest_recursion_cnt);
		जाओ out;
	पूर्ण

	trace_selftest_recursion_cnt = 1;

	pr_cont("PASSED\n");
	pr_info("Testing ftrace recursion safe: ");

	ret = ftrace_set_filter(&test_recsafe_probe, func_name, len, 1);
	अगर (ret) अणु
		pr_cont("*Could not set filter* ");
		जाओ out;
	पूर्ण

	ret = रेजिस्टर_ftrace_function(&test_recsafe_probe);
	अगर (ret) अणु
		pr_cont("*could not register callback* ");
		जाओ out;
	पूर्ण

	DYN_FTRACE_TEST_NAME();

	unरेजिस्टर_ftrace_function(&test_recsafe_probe);

	ret = -1;
	अगर (trace_selftest_recursion_cnt != 2) अणु
		pr_cont("*callback not called expected 2 times (%d)* ",
			trace_selftest_recursion_cnt);
		जाओ out;
	पूर्ण

	ret = 0;
out:
	ftrace_enabled = save_ftrace_enabled;

	वापस ret;
पूर्ण
#अन्यथा
# define trace_selftest_startup_dynamic_tracing(trace, tr, func) (अणु 0; पूर्ण)
# define trace_selftest_function_recursion() (अणु 0; पूर्ण)
#पूर्ण_अगर /* CONFIG_DYNAMIC_FTRACE */

अटल क्रमागत अणु
	TRACE_SELFTEST_REGS_START,
	TRACE_SELFTEST_REGS_FOUND,
	TRACE_SELFTEST_REGS_NOT_FOUND,
पूर्ण trace_selftest_regs_stat;

अटल व्योम trace_selftest_test_regs_func(अचिन्हित दीर्घ ip,
					  अचिन्हित दीर्घ pip,
					  काष्ठा ftrace_ops *op,
					  काष्ठा ftrace_regs *fregs)
अणु
	काष्ठा pt_regs *regs = ftrace_get_regs(fregs);

	अगर (regs)
		trace_selftest_regs_stat = TRACE_SELFTEST_REGS_FOUND;
	अन्यथा
		trace_selftest_regs_stat = TRACE_SELFTEST_REGS_NOT_FOUND;
पूर्ण

अटल काष्ठा ftrace_ops test_regs_probe = अणु
	.func		= trace_selftest_test_regs_func,
	.flags		= FTRACE_OPS_FL_SAVE_REGS,
पूर्ण;

अटल पूर्णांक
trace_selftest_function_regs(व्योम)
अणु
	पूर्णांक save_ftrace_enabled = ftrace_enabled;
	अक्षर *func_name;
	पूर्णांक len;
	पूर्णांक ret;
	पूर्णांक supported = 0;

#अगर_घोषित CONFIG_DYNAMIC_FTRACE_WITH_REGS
	supported = 1;
#पूर्ण_अगर

	/* The previous test PASSED */
	pr_cont("PASSED\n");
	pr_info("Testing ftrace regs%s: ",
		!supported ? "(no arch support)" : "");

	/* enable tracing, and record the filter function */
	ftrace_enabled = 1;

	/* Handle PPC64 '.' name */
	func_name = "*" __stringअगरy(DYN_FTRACE_TEST_NAME);
	len = म_माप(func_name);

	ret = ftrace_set_filter(&test_regs_probe, func_name, len, 1);
	/*
	 * If DYNAMIC_FTRACE is not set, then we just trace all functions.
	 * This test really करोesn't care.
	 */
	अगर (ret && ret != -ENODEV) अणु
		pr_cont("*Could not set filter* ");
		जाओ out;
	पूर्ण

	ret = रेजिस्टर_ftrace_function(&test_regs_probe);
	/*
	 * Now अगर the arch करोes not support passing regs, then this should
	 * have failed.
	 */
	अगर (!supported) अणु
		अगर (!ret) अणु
			pr_cont("*registered save-regs without arch support* ");
			जाओ out;
		पूर्ण
		test_regs_probe.flags |= FTRACE_OPS_FL_SAVE_REGS_IF_SUPPORTED;
		ret = रेजिस्टर_ftrace_function(&test_regs_probe);
	पूर्ण
	अगर (ret) अणु
		pr_cont("*could not register callback* ");
		जाओ out;
	पूर्ण


	DYN_FTRACE_TEST_NAME();

	unरेजिस्टर_ftrace_function(&test_regs_probe);

	ret = -1;

	चयन (trace_selftest_regs_stat) अणु
	हाल TRACE_SELFTEST_REGS_START:
		pr_cont("*callback never called* ");
		जाओ out;

	हाल TRACE_SELFTEST_REGS_FOUND:
		अगर (supported)
			अवरोध;
		pr_cont("*callback received regs without arch support* ");
		जाओ out;

	हाल TRACE_SELFTEST_REGS_NOT_FOUND:
		अगर (!supported)
			अवरोध;
		pr_cont("*callback received NULL regs* ");
		जाओ out;
	पूर्ण

	ret = 0;
out:
	ftrace_enabled = save_ftrace_enabled;

	वापस ret;
पूर्ण

/*
 * Simple verअगरication test of ftrace function tracer.
 * Enable ftrace, sleep 1/10 second, and then पढ़ो the trace
 * buffer to see अगर all is in order.
 */
__init पूर्णांक
trace_selftest_startup_function(काष्ठा tracer *trace, काष्ठा trace_array *tr)
अणु
	पूर्णांक save_ftrace_enabled = ftrace_enabled;
	अचिन्हित दीर्घ count;
	पूर्णांक ret;

#अगर_घोषित CONFIG_DYNAMIC_FTRACE
	अगर (ftrace_filter_param) अणु
		prपूर्णांकk(KERN_CONT " ... kernel command line filter set: force PASS ... ");
		वापस 0;
	पूर्ण
#पूर्ण_अगर

	/* make sure msleep has been recorded */
	msleep(1);

	/* start the tracing */
	ftrace_enabled = 1;

	ret = tracer_init(trace, tr);
	अगर (ret) अणु
		warn_failed_init_tracer(trace, ret);
		जाओ out;
	पूर्ण

	/* Sleep क्रम a 1/10 of a second */
	msleep(100);
	/* stop the tracing. */
	tracing_stop();
	ftrace_enabled = 0;

	/* check the trace buffer */
	ret = trace_test_buffer(&tr->array_buffer, &count);

	ftrace_enabled = 1;
	trace->reset(tr);
	tracing_start();

	अगर (!ret && !count) अणु
		prपूर्णांकk(KERN_CONT ".. no entries found ..");
		ret = -1;
		जाओ out;
	पूर्ण

	ret = trace_selftest_startup_dynamic_tracing(trace, tr,
						     DYN_FTRACE_TEST_NAME);
	अगर (ret)
		जाओ out;

	ret = trace_selftest_function_recursion();
	अगर (ret)
		जाओ out;

	ret = trace_selftest_function_regs();
 out:
	ftrace_enabled = save_ftrace_enabled;

	/* समाप्त ftrace totally अगर we failed */
	अगर (ret)
		ftrace_समाप्त();

	वापस ret;
पूर्ण
#पूर्ण_अगर /* CONFIG_FUNCTION_TRACER */


#अगर_घोषित CONFIG_FUNCTION_GRAPH_TRACER

/* Maximum number of functions to trace beक्रमe diagnosing a hang */
#घोषणा GRAPH_MAX_FUNC_TEST	100000000

अटल अचिन्हित पूर्णांक graph_hang_thresh;

/* Wrap the real function entry probe to aव्योम possible hanging */
अटल पूर्णांक trace_graph_entry_watchकरोg(काष्ठा ftrace_graph_ent *trace)
अणु
	/* This is harmlessly racy, we want to approximately detect a hang */
	अगर (unlikely(++graph_hang_thresh > GRAPH_MAX_FUNC_TEST)) अणु
		ftrace_graph_stop();
		prपूर्णांकk(KERN_WARNING "BUG: Function graph tracer hang!\n");
		अगर (ftrace_dump_on_oops) अणु
			ftrace_dump(DUMP_ALL);
			/* ftrace_dump() disables tracing */
			tracing_on();
		पूर्ण
		वापस 0;
	पूर्ण

	वापस trace_graph_entry(trace);
पूर्ण

अटल काष्ठा fgraph_ops fgraph_ops __initdata  = अणु
	.entryfunc		= &trace_graph_entry_watchकरोg,
	.retfunc		= &trace_graph_वापस,
पूर्ण;

/*
 * Pretty much the same than क्रम the function tracer from which the selftest
 * has been borrowed.
 */
__init पूर्णांक
trace_selftest_startup_function_graph(काष्ठा tracer *trace,
					काष्ठा trace_array *tr)
अणु
	पूर्णांक ret;
	अचिन्हित दीर्घ count;

#अगर_घोषित CONFIG_DYNAMIC_FTRACE
	अगर (ftrace_filter_param) अणु
		prपूर्णांकk(KERN_CONT " ... kernel command line filter set: force PASS ... ");
		वापस 0;
	पूर्ण
#पूर्ण_अगर

	/*
	 * Simulate the init() callback but we attach a watchकरोg callback
	 * to detect and recover from possible hangs
	 */
	tracing_reset_online_cpus(&tr->array_buffer);
	set_graph_array(tr);
	ret = रेजिस्टर_ftrace_graph(&fgraph_ops);
	अगर (ret) अणु
		warn_failed_init_tracer(trace, ret);
		जाओ out;
	पूर्ण
	tracing_start_cmdline_record();

	/* Sleep क्रम a 1/10 of a second */
	msleep(100);

	/* Have we just recovered from a hang? */
	अगर (graph_hang_thresh > GRAPH_MAX_FUNC_TEST) अणु
		disable_tracing_selftest("recovering from a hang");
		ret = -1;
		जाओ out;
	पूर्ण

	tracing_stop();

	/* check the trace buffer */
	ret = trace_test_buffer(&tr->array_buffer, &count);

	/* Need to also simulate the tr->reset to हटाओ this fgraph_ops */
	tracing_stop_cmdline_record();
	unरेजिस्टर_ftrace_graph(&fgraph_ops);

	tracing_start();

	अगर (!ret && !count) अणु
		prपूर्णांकk(KERN_CONT ".. no entries found ..");
		ret = -1;
		जाओ out;
	पूर्ण

	/* Don't test dynamic tracing, the function tracer alपढ़ोy did */

out:
	/* Stop it अगर we failed */
	अगर (ret)
		ftrace_graph_stop();

	वापस ret;
पूर्ण
#पूर्ण_अगर /* CONFIG_FUNCTION_GRAPH_TRACER */


#अगर_घोषित CONFIG_IRQSOFF_TRACER
पूर्णांक
trace_selftest_startup_irqsoff(काष्ठा tracer *trace, काष्ठा trace_array *tr)
अणु
	अचिन्हित दीर्घ save_max = tr->max_latency;
	अचिन्हित दीर्घ count;
	पूर्णांक ret;

	/* start the tracing */
	ret = tracer_init(trace, tr);
	अगर (ret) अणु
		warn_failed_init_tracer(trace, ret);
		वापस ret;
	पूर्ण

	/* reset the max latency */
	tr->max_latency = 0;
	/* disable पूर्णांकerrupts क्रम a bit */
	local_irq_disable();
	udelay(100);
	local_irq_enable();

	/*
	 * Stop the tracer to aव्योम a warning subsequent
	 * to buffer flipping failure because tracing_stop()
	 * disables the tr and max buffers, making flipping impossible
	 * in हाल of parallels max irqs off latencies.
	 */
	trace->stop(tr);
	/* stop the tracing. */
	tracing_stop();
	/* check both trace buffers */
	ret = trace_test_buffer(&tr->array_buffer, शून्य);
	अगर (!ret)
		ret = trace_test_buffer(&tr->max_buffer, &count);
	trace->reset(tr);
	tracing_start();

	अगर (!ret && !count) अणु
		prपूर्णांकk(KERN_CONT ".. no entries found ..");
		ret = -1;
	पूर्ण

	tr->max_latency = save_max;

	वापस ret;
पूर्ण
#पूर्ण_अगर /* CONFIG_IRQSOFF_TRACER */

#अगर_घोषित CONFIG_PREEMPT_TRACER
पूर्णांक
trace_selftest_startup_preemptoff(काष्ठा tracer *trace, काष्ठा trace_array *tr)
अणु
	अचिन्हित दीर्घ save_max = tr->max_latency;
	अचिन्हित दीर्घ count;
	पूर्णांक ret;

	/*
	 * Now that the big kernel lock is no दीर्घer preemptible,
	 * and this is called with the BKL held, it will always
	 * fail. If preemption is alपढ़ोy disabled, simply
	 * pass the test. When the BKL is हटाओd, or becomes
	 * preemptible again, we will once again test this,
	 * so keep it in.
	 */
	अगर (preempt_count()) अणु
		prपूर्णांकk(KERN_CONT "can not test ... force ");
		वापस 0;
	पूर्ण

	/* start the tracing */
	ret = tracer_init(trace, tr);
	अगर (ret) अणु
		warn_failed_init_tracer(trace, ret);
		वापस ret;
	पूर्ण

	/* reset the max latency */
	tr->max_latency = 0;
	/* disable preemption क्रम a bit */
	preempt_disable();
	udelay(100);
	preempt_enable();

	/*
	 * Stop the tracer to aव्योम a warning subsequent
	 * to buffer flipping failure because tracing_stop()
	 * disables the tr and max buffers, making flipping impossible
	 * in हाल of parallels max preempt off latencies.
	 */
	trace->stop(tr);
	/* stop the tracing. */
	tracing_stop();
	/* check both trace buffers */
	ret = trace_test_buffer(&tr->array_buffer, शून्य);
	अगर (!ret)
		ret = trace_test_buffer(&tr->max_buffer, &count);
	trace->reset(tr);
	tracing_start();

	अगर (!ret && !count) अणु
		prपूर्णांकk(KERN_CONT ".. no entries found ..");
		ret = -1;
	पूर्ण

	tr->max_latency = save_max;

	वापस ret;
पूर्ण
#पूर्ण_अगर /* CONFIG_PREEMPT_TRACER */

#अगर defined(CONFIG_IRQSOFF_TRACER) && defined(CONFIG_PREEMPT_TRACER)
पूर्णांक
trace_selftest_startup_preemptirqsoff(काष्ठा tracer *trace, काष्ठा trace_array *tr)
अणु
	अचिन्हित दीर्घ save_max = tr->max_latency;
	अचिन्हित दीर्घ count;
	पूर्णांक ret;

	/*
	 * Now that the big kernel lock is no दीर्घer preemptible,
	 * and this is called with the BKL held, it will always
	 * fail. If preemption is alपढ़ोy disabled, simply
	 * pass the test. When the BKL is हटाओd, or becomes
	 * preemptible again, we will once again test this,
	 * so keep it in.
	 */
	अगर (preempt_count()) अणु
		prपूर्णांकk(KERN_CONT "can not test ... force ");
		वापस 0;
	पूर्ण

	/* start the tracing */
	ret = tracer_init(trace, tr);
	अगर (ret) अणु
		warn_failed_init_tracer(trace, ret);
		जाओ out_no_start;
	पूर्ण

	/* reset the max latency */
	tr->max_latency = 0;

	/* disable preemption and पूर्णांकerrupts क्रम a bit */
	preempt_disable();
	local_irq_disable();
	udelay(100);
	preempt_enable();
	/* reverse the order of preempt vs irqs */
	local_irq_enable();

	/*
	 * Stop the tracer to aव्योम a warning subsequent
	 * to buffer flipping failure because tracing_stop()
	 * disables the tr and max buffers, making flipping impossible
	 * in हाल of parallels max irqs/preempt off latencies.
	 */
	trace->stop(tr);
	/* stop the tracing. */
	tracing_stop();
	/* check both trace buffers */
	ret = trace_test_buffer(&tr->array_buffer, शून्य);
	अगर (ret)
		जाओ out;

	ret = trace_test_buffer(&tr->max_buffer, &count);
	अगर (ret)
		जाओ out;

	अगर (!ret && !count) अणु
		prपूर्णांकk(KERN_CONT ".. no entries found ..");
		ret = -1;
		जाओ out;
	पूर्ण

	/* करो the test by disabling पूर्णांकerrupts first this समय */
	tr->max_latency = 0;
	tracing_start();
	trace->start(tr);

	preempt_disable();
	local_irq_disable();
	udelay(100);
	preempt_enable();
	/* reverse the order of preempt vs irqs */
	local_irq_enable();

	trace->stop(tr);
	/* stop the tracing. */
	tracing_stop();
	/* check both trace buffers */
	ret = trace_test_buffer(&tr->array_buffer, शून्य);
	अगर (ret)
		जाओ out;

	ret = trace_test_buffer(&tr->max_buffer, &count);

	अगर (!ret && !count) अणु
		prपूर्णांकk(KERN_CONT ".. no entries found ..");
		ret = -1;
		जाओ out;
	पूर्ण

out:
	tracing_start();
out_no_start:
	trace->reset(tr);
	tr->max_latency = save_max;

	वापस ret;
पूर्ण
#पूर्ण_अगर /* CONFIG_IRQSOFF_TRACER && CONFIG_PREEMPT_TRACER */

#अगर_घोषित CONFIG_NOP_TRACER
पूर्णांक
trace_selftest_startup_nop(काष्ठा tracer *trace, काष्ठा trace_array *tr)
अणु
	/* What could possibly go wrong? */
	वापस 0;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_SCHED_TRACER

काष्ठा wakeup_test_data अणु
	काष्ठा completion	is_पढ़ोy;
	पूर्णांक			go;
पूर्ण;

अटल पूर्णांक trace_wakeup_test_thपढ़ो(व्योम *data)
अणु
	/* Make this a -deadline thपढ़ो */
	अटल स्थिर काष्ठा sched_attr attr = अणु
		.sched_policy = SCHED_DEADLINE,
		.sched_runसमय = 100000ULL,
		.sched_deadline = 10000000ULL,
		.sched_period = 10000000ULL
	पूर्ण;
	काष्ठा wakeup_test_data *x = data;

	sched_setattr(current, &attr);

	/* Make it know we have a new prio */
	complete(&x->is_पढ़ोy);

	/* now go to sleep and let the test wake us up */
	set_current_state(TASK_INTERRUPTIBLE);
	जबतक (!x->go) अणु
		schedule();
		set_current_state(TASK_INTERRUPTIBLE);
	पूर्ण

	complete(&x->is_पढ़ोy);

	set_current_state(TASK_INTERRUPTIBLE);

	/* we are awake, now रुको to disappear */
	जबतक (!kthपढ़ो_should_stop()) अणु
		schedule();
		set_current_state(TASK_INTERRUPTIBLE);
	पूर्ण

	__set_current_state(TASK_RUNNING);

	वापस 0;
पूर्ण
पूर्णांक
trace_selftest_startup_wakeup(काष्ठा tracer *trace, काष्ठा trace_array *tr)
अणु
	अचिन्हित दीर्घ save_max = tr->max_latency;
	काष्ठा task_काष्ठा *p;
	काष्ठा wakeup_test_data data;
	अचिन्हित दीर्घ count;
	पूर्णांक ret;

	स_रखो(&data, 0, माप(data));

	init_completion(&data.is_पढ़ोy);

	/* create a -deadline thपढ़ो */
	p = kthपढ़ो_run(trace_wakeup_test_thपढ़ो, &data, "ftrace-test");
	अगर (IS_ERR(p)) अणु
		prपूर्णांकk(KERN_CONT "Failed to create ftrace wakeup test thread ");
		वापस -1;
	पूर्ण

	/* make sure the thपढ़ो is running at -deadline policy */
	रुको_क्रम_completion(&data.is_पढ़ोy);

	/* start the tracing */
	ret = tracer_init(trace, tr);
	अगर (ret) अणु
		warn_failed_init_tracer(trace, ret);
		वापस ret;
	पूर्ण

	/* reset the max latency */
	tr->max_latency = 0;

	जबतक (p->on_rq) अणु
		/*
		 * Sleep to make sure the -deadline thपढ़ो is asleep too.
		 * On भव machines we can't rely on timings,
		 * but we want to make sure this test still works.
		 */
		msleep(100);
	पूर्ण

	init_completion(&data.is_पढ़ोy);

	data.go = 1;
	/* memory barrier is in the wake_up_process() */

	wake_up_process(p);

	/* Wait क्रम the task to wake up */
	रुको_क्रम_completion(&data.is_पढ़ोy);

	/* stop the tracing. */
	tracing_stop();
	/* check both trace buffers */
	ret = trace_test_buffer(&tr->array_buffer, शून्य);
	अगर (!ret)
		ret = trace_test_buffer(&tr->max_buffer, &count);


	trace->reset(tr);
	tracing_start();

	tr->max_latency = save_max;

	/* समाप्त the thपढ़ो */
	kthपढ़ो_stop(p);

	अगर (!ret && !count) अणु
		prपूर्णांकk(KERN_CONT ".. no entries found ..");
		ret = -1;
	पूर्ण

	वापस ret;
पूर्ण
#पूर्ण_अगर /* CONFIG_SCHED_TRACER */

#अगर_घोषित CONFIG_BRANCH_TRACER
पूर्णांक
trace_selftest_startup_branch(काष्ठा tracer *trace, काष्ठा trace_array *tr)
अणु
	अचिन्हित दीर्घ count;
	पूर्णांक ret;

	/* start the tracing */
	ret = tracer_init(trace, tr);
	अगर (ret) अणु
		warn_failed_init_tracer(trace, ret);
		वापस ret;
	पूर्ण

	/* Sleep क्रम a 1/10 of a second */
	msleep(100);
	/* stop the tracing. */
	tracing_stop();
	/* check the trace buffer */
	ret = trace_test_buffer(&tr->array_buffer, &count);
	trace->reset(tr);
	tracing_start();

	अगर (!ret && !count) अणु
		prपूर्णांकk(KERN_CONT ".. no entries found ..");
		ret = -1;
	पूर्ण

	वापस ret;
पूर्ण
#पूर्ण_अगर /* CONFIG_BRANCH_TRACER */

