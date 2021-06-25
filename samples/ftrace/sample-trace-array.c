<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#समावेश <linux/module.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/trace.h>
#समावेश <linux/trace_events.h>
#समावेश <linux/समयr.h>
#समावेश <linux/err.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/workqueue.h>

/*
 * Any file that uses trace poपूर्णांकs, must include the header.
 * But only one file, must include the header by defining
 * CREATE_TRACE_POINTS first.  This will make the C code that
 * creates the handles क्रम the trace poपूर्णांकs.
 */
#घोषणा CREATE_TRACE_POINTS
#समावेश "sample-trace-array.h"

काष्ठा trace_array *tr;
अटल व्योम myसमयr_handler(काष्ठा समयr_list *unused);
अटल काष्ठा task_काष्ठा *simple_tsk;

अटल व्योम trace_work_fn(काष्ठा work_काष्ठा *work)
अणु
	/*
	 * Disable tracing क्रम event "sample_event".
	 */
	trace_array_set_clr_event(tr, "sample-subsystem", "sample_event",
			false);
पूर्ण
अटल DECLARE_WORK(trace_work, trace_work_fn);

/*
 * myसमयr: Timer setup to disable tracing क्रम event "sample_event". This
 * समयr is only क्रम the purposes of the sample module to demonstrate access of
 * Ftrace instances from within kernel.
 */
अटल DEFINE_TIMER(myसमयr, myसमयr_handler);

अटल व्योम myसमयr_handler(काष्ठा समयr_list *unused)
अणु
	schedule_work(&trace_work);
पूर्ण

अटल व्योम simple_thपढ़ो_func(पूर्णांक count)
अणु
	set_current_state(TASK_INTERRUPTIBLE);
	schedule_समयout(HZ);

	/*
	 * Prपूर्णांकing count value using trace_array_prपूर्णांकk() - trace_prपूर्णांकk()
	 * equivalent क्रम the instance buffers.
	 */
	trace_array_prपूर्णांकk(tr, _THIS_IP_, "trace_array_printk: count=%d\n",
			count);
	/*
	 * Tracepoपूर्णांक क्रम event "sample_event". This will prपूर्णांक the
	 * current value of count and current jअगरfies.
	 */
	trace_sample_event(count, jअगरfies);
पूर्ण

अटल पूर्णांक simple_thपढ़ो(व्योम *arg)
अणु
	पूर्णांक count = 0;
	अचिन्हित दीर्घ delay = msecs_to_jअगरfies(5000);

	/*
	 * Enable tracing क्रम "sample_event".
	 */
	trace_array_set_clr_event(tr, "sample-subsystem", "sample_event", true);

	/*
	 * Adding समयr - myसमयr. This समयr will disable tracing after
	 * delay seconds.
	 *
	 */
	add_समयr(&myसमयr);
	mod_समयr(&myसमयr, jअगरfies+delay);

	जबतक (!kthपढ़ो_should_stop())
		simple_thपढ़ो_func(count++);

	del_समयr(&myसमयr);
	cancel_work_sync(&trace_work);

	/*
	 * trace_array_put() decrements the reference counter associated with
	 * the trace array - "tr". We are करोne using the trace array, hence
	 * decrement the reference counter so that it can be destroyed using
	 * trace_array_destroy().
	 */
	trace_array_put(tr);

	वापस 0;
पूर्ण

अटल पूर्णांक __init sample_trace_array_init(व्योम)
अणु
	/*
	 * Return a poपूर्णांकer to the trace array with name "sample-instance" अगर it
	 * exists, अन्यथा create a new trace array.
	 *
	 * NOTE: This function increments the reference counter
	 * associated with the trace array - "tr".
	 */
	tr = trace_array_get_by_name("sample-instance");

	अगर (!tr)
		वापस -1;
	/*
	 * If context specअगरic per-cpu buffers havent alपढ़ोy been allocated.
	 */
	trace_prपूर्णांकk_init_buffers();

	simple_tsk = kthपढ़ो_run(simple_thपढ़ो, शून्य, "sample-instance");
	अगर (IS_ERR(simple_tsk)) अणु
		trace_array_put(tr);
		trace_array_destroy(tr);
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम __निकास sample_trace_array_निकास(व्योम)
अणु
	kthपढ़ो_stop(simple_tsk);

	/*
	 * We are unloading our module and no दीर्घer require the trace array.
	 * Remove/destroy "tr" using trace_array_destroy()
	 */
	trace_array_destroy(tr);
पूर्ण

module_init(sample_trace_array_init);
module_निकास(sample_trace_array_निकास);

MODULE_AUTHOR("Divya Indi");
MODULE_DESCRIPTION("Sample module for kernel access to Ftrace instances");
MODULE_LICENSE("GPL");
