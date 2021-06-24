<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Test module क्रम in-kernel kprobe event creation and generation.
 *
 * Copyright (C) 2019 Tom Zanussi <zanussi@kernel.org>
 */

#समावेश <linux/module.h>
#समावेश <linux/trace_events.h>

/*
 * This module is a simple test of basic functionality क्रम in-kernel
 * kprobe/kretprobe event creation.  The first test uses
 * kprobe_event_gen_cmd_start(), kprobe_event_add_fields() and
 * kprobe_event_gen_cmd_end() to create a kprobe event, which is then
 * enabled in order to generate trace output.  The second creates a
 * kretprobe event using kretprobe_event_gen_cmd_start() and
 * kretprobe_event_gen_cmd_end(), and is also then enabled.
 *
 * To test, select CONFIG_KPROBE_EVENT_GEN_TEST and build the module.
 * Then:
 *
 * # insmod kernel/trace/kprobe_event_gen_test.ko
 * # cat /sys/kernel/debug/tracing/trace
 *
 * You should see many instances of the "gen_kprobe_test" and
 * "gen_kretprobe_test" events in the trace buffer.
 *
 * To हटाओ the events, हटाओ the module:
 *
 * # rmmod kprobe_event_gen_test
 *
 */

अटल काष्ठा trace_event_file *gen_kprobe_test;
अटल काष्ठा trace_event_file *gen_kretprobe_test;

/*
 * Test to make sure we can create a kprobe event, then add more
 * fields.
 */
अटल पूर्णांक __init test_gen_kprobe_cmd(व्योम)
अणु
	काष्ठा dynevent_cmd cmd;
	अक्षर *buf;
	पूर्णांक ret;

	/* Create a buffer to hold the generated command */
	buf = kzalloc(MAX_DYNEVENT_CMD_LEN, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	/* Beक्रमe generating the command, initialize the cmd object */
	kprobe_event_cmd_init(&cmd, buf, MAX_DYNEVENT_CMD_LEN);

	/*
	 * Define the gen_kprobe_test event with the first 2 kprobe
	 * fields.
	 */
	ret = kprobe_event_gen_cmd_start(&cmd, "gen_kprobe_test",
					 "do_sys_open",
					 "dfd=%ax", "filename=%dx");
	अगर (ret)
		जाओ मुक्त;

	/* Use kprobe_event_add_fields to add the rest of the fields */

	ret = kprobe_event_add_fields(&cmd, "flags=%cx", "mode=+4($stack)");
	अगर (ret)
		जाओ मुक्त;

	/*
	 * This actually creates the event.
	 */
	ret = kprobe_event_gen_cmd_end(&cmd);
	अगर (ret)
		जाओ मुक्त;

	/*
	 * Now get the gen_kprobe_test event file.  We need to prevent
	 * the instance and event from disappearing from underneath
	 * us, which trace_get_event_file() करोes (though in this हाल
	 * we're using the top-level instance which never goes away).
	 */
	gen_kprobe_test = trace_get_event_file(शून्य, "kprobes",
					       "gen_kprobe_test");
	अगर (IS_ERR(gen_kprobe_test)) अणु
		ret = PTR_ERR(gen_kprobe_test);
		जाओ delete;
	पूर्ण

	/* Enable the event or you won't see anything */
	ret = trace_array_set_clr_event(gen_kprobe_test->tr,
					"kprobes", "gen_kprobe_test", true);
	अगर (ret) अणु
		trace_put_event_file(gen_kprobe_test);
		जाओ delete;
	पूर्ण
 out:
	वापस ret;
 delete:
	/* We got an error after creating the event, delete it */
	ret = kprobe_event_delete("gen_kprobe_test");
 मुक्त:
	kमुक्त(buf);

	जाओ out;
पूर्ण

/*
 * Test to make sure we can create a kretprobe event.
 */
अटल पूर्णांक __init test_gen_kretprobe_cmd(व्योम)
अणु
	काष्ठा dynevent_cmd cmd;
	अक्षर *buf;
	पूर्णांक ret;

	/* Create a buffer to hold the generated command */
	buf = kzalloc(MAX_DYNEVENT_CMD_LEN, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	/* Beक्रमe generating the command, initialize the cmd object */
	kprobe_event_cmd_init(&cmd, buf, MAX_DYNEVENT_CMD_LEN);

	/*
	 * Define the kretprobe event.
	 */
	ret = kretprobe_event_gen_cmd_start(&cmd, "gen_kretprobe_test",
					    "do_sys_open",
					    "$retval");
	अगर (ret)
		जाओ मुक्त;

	/*
	 * This actually creates the event.
	 */
	ret = kretprobe_event_gen_cmd_end(&cmd);
	अगर (ret)
		जाओ मुक्त;

	/*
	 * Now get the gen_kretprobe_test event file.  We need to
	 * prevent the instance and event from disappearing from
	 * underneath us, which trace_get_event_file() करोes (though in
	 * this हाल we're using the top-level instance which never
	 * goes away).
	 */
	gen_kretprobe_test = trace_get_event_file(शून्य, "kprobes",
						  "gen_kretprobe_test");
	अगर (IS_ERR(gen_kretprobe_test)) अणु
		ret = PTR_ERR(gen_kretprobe_test);
		जाओ delete;
	पूर्ण

	/* Enable the event or you won't see anything */
	ret = trace_array_set_clr_event(gen_kretprobe_test->tr,
					"kprobes", "gen_kretprobe_test", true);
	अगर (ret) अणु
		trace_put_event_file(gen_kretprobe_test);
		जाओ delete;
	पूर्ण
 out:
	वापस ret;
 delete:
	/* We got an error after creating the event, delete it */
	ret = kprobe_event_delete("gen_kretprobe_test");
 मुक्त:
	kमुक्त(buf);

	जाओ out;
पूर्ण

अटल पूर्णांक __init kprobe_event_gen_test_init(व्योम)
अणु
	पूर्णांक ret;

	ret = test_gen_kprobe_cmd();
	अगर (ret)
		वापस ret;

	ret = test_gen_kretprobe_cmd();
	अगर (ret) अणु
		WARN_ON(trace_array_set_clr_event(gen_kretprobe_test->tr,
						  "kprobes",
						  "gen_kretprobe_test", false));
		trace_put_event_file(gen_kretprobe_test);
		WARN_ON(kprobe_event_delete("gen_kretprobe_test"));
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम __निकास kprobe_event_gen_test_निकास(व्योम)
अणु
	/* Disable the event or you can't हटाओ it */
	WARN_ON(trace_array_set_clr_event(gen_kprobe_test->tr,
					  "kprobes",
					  "gen_kprobe_test", false));

	/* Now give the file and instance back */
	trace_put_event_file(gen_kprobe_test);

	/* Now unरेजिस्टर and मुक्त the event */
	WARN_ON(kprobe_event_delete("gen_kprobe_test"));

	/* Disable the event or you can't हटाओ it */
	WARN_ON(trace_array_set_clr_event(gen_kprobe_test->tr,
					  "kprobes",
					  "gen_kretprobe_test", false));

	/* Now give the file and instance back */
	trace_put_event_file(gen_kretprobe_test);

	/* Now unरेजिस्टर and मुक्त the event */
	WARN_ON(kprobe_event_delete("gen_kretprobe_test"));
पूर्ण

module_init(kprobe_event_gen_test_init)
module_निकास(kprobe_event_gen_test_निकास)

MODULE_AUTHOR("Tom Zanussi");
MODULE_DESCRIPTION("kprobe event generation test");
MODULE_LICENSE("GPL v2");
