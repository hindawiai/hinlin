<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#समावेश <linux/module.h>
#समावेश <linux/kthपढ़ो.h>

/*
 * Any file that uses trace poपूर्णांकs, must include the header.
 * But only one file, must include the header by defining
 * CREATE_TRACE_POINTS first.  This will make the C code that
 * creates the handles क्रम the trace poपूर्णांकs.
 */
#घोषणा CREATE_TRACE_POINTS
#समावेश "trace-events-sample.h"

अटल स्थिर अक्षर *अक्रमom_strings[] = अणु
	"Mother Goose",
	"Snoopy",
	"Gandalf",
	"Frodo",
	"One ring to rule them all"
पूर्ण;

अटल व्योम simple_thपढ़ो_func(पूर्णांक cnt)
अणु
	पूर्णांक array[6];
	पूर्णांक len = cnt % 5;
	पूर्णांक i;

	set_current_state(TASK_INTERRUPTIBLE);
	schedule_समयout(HZ);

	क्रम (i = 0; i < len; i++)
		array[i] = i + 1;
	array[i] = 0;

	/* Silly tracepoपूर्णांकs */
	trace_foo_bar("hello", cnt, array, अक्रमom_strings[len],
		      current->cpus_ptr);

	trace_foo_with_ढाँचा_simple("HELLO", cnt);

	trace_foo_bar_with_cond("Some times print", cnt);

	trace_foo_with_ढाँचा_cond("prints other times", cnt);

	trace_foo_with_ढाँचा_prपूर्णांक("I have to be different", cnt);
पूर्ण

अटल पूर्णांक simple_thपढ़ो(व्योम *arg)
अणु
	पूर्णांक cnt = 0;

	जबतक (!kthपढ़ो_should_stop())
		simple_thपढ़ो_func(cnt++);

	वापस 0;
पूर्ण

अटल काष्ठा task_काष्ठा *simple_tsk;
अटल काष्ठा task_काष्ठा *simple_tsk_fn;

अटल व्योम simple_thपढ़ो_func_fn(पूर्णांक cnt)
अणु
	set_current_state(TASK_INTERRUPTIBLE);
	schedule_समयout(HZ);

	/* More silly tracepoपूर्णांकs */
	trace_foo_bar_with_fn("Look at me", cnt);
	trace_foo_with_ढाँचा_fn("Look at me too", cnt);
पूर्ण

अटल पूर्णांक simple_thपढ़ो_fn(व्योम *arg)
अणु
	पूर्णांक cnt = 0;

	जबतक (!kthपढ़ो_should_stop())
		simple_thपढ़ो_func_fn(cnt++);

	वापस 0;
पूर्ण

अटल DEFINE_MUTEX(thपढ़ो_mutex);
अटल पूर्णांक simple_thपढ़ो_cnt;

पूर्णांक foo_bar_reg(व्योम)
अणु
	mutex_lock(&thपढ़ो_mutex);
	अगर (simple_thपढ़ो_cnt++)
		जाओ out;

	pr_info("Starting thread for foo_bar_fn\n");
	/*
	 * We shouldn't be able to start a trace when the module is
	 * unloading (there's other locks to prevent that). But
	 * क्रम consistency sake, we still take the thपढ़ो_mutex.
	 */
	simple_tsk_fn = kthपढ़ो_run(simple_thपढ़ो_fn, शून्य, "event-sample-fn");
 out:
	mutex_unlock(&thपढ़ो_mutex);
	वापस 0;
पूर्ण

व्योम foo_bar_unreg(व्योम)
अणु
	mutex_lock(&thपढ़ो_mutex);
	अगर (--simple_thपढ़ो_cnt)
		जाओ out;

	pr_info("Killing thread for foo_bar_fn\n");
	अगर (simple_tsk_fn)
		kthपढ़ो_stop(simple_tsk_fn);
	simple_tsk_fn = शून्य;
 out:
	mutex_unlock(&thपढ़ो_mutex);
पूर्ण

अटल पूर्णांक __init trace_event_init(व्योम)
अणु
	simple_tsk = kthपढ़ो_run(simple_thपढ़ो, शून्य, "event-sample");
	अगर (IS_ERR(simple_tsk))
		वापस -1;

	वापस 0;
पूर्ण

अटल व्योम __निकास trace_event_निकास(व्योम)
अणु
	kthपढ़ो_stop(simple_tsk);
	mutex_lock(&thपढ़ो_mutex);
	अगर (simple_tsk_fn)
		kthपढ़ो_stop(simple_tsk_fn);
	simple_tsk_fn = शून्य;
	mutex_unlock(&thपढ़ो_mutex);
पूर्ण

module_init(trace_event_init);
module_निकास(trace_event_निकास);

MODULE_AUTHOR("Steven Rostedt");
MODULE_DESCRIPTION("trace-events-sample");
MODULE_LICENSE("GPL");
