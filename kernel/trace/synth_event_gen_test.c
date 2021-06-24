<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Test module क्रम in-kernel synthetic event creation and generation.
 *
 * Copyright (C) 2019 Tom Zanussi <zanussi@kernel.org>
 */

#समावेश <linux/module.h>
#समावेश <linux/trace_events.h>

/*
 * This module is a simple test of basic functionality क्रम in-kernel
 * synthetic event creation and generation, the first and second tests
 * using synth_event_gen_cmd_start() and synth_event_add_field(), the
 * third uses synth_event_create() to करो it all at once with a अटल
 * field array.
 *
 * Following that are a few examples using the created events to test
 * various ways of tracing a synthetic event.
 *
 * To test, select CONFIG_SYNTH_EVENT_GEN_TEST and build the module.
 * Then:
 *
 * # insmod kernel/trace/synth_event_gen_test.ko
 * # cat /sys/kernel/debug/tracing/trace
 *
 * You should see several events in the trace buffer -
 * "create_synth_test", "empty_synth_test", and several instances of
 * "gen_synth_test".
 *
 * To हटाओ the events, हटाओ the module:
 *
 * # rmmod synth_event_gen_test
 *
 */

अटल काष्ठा trace_event_file *create_synth_test;
अटल काष्ठा trace_event_file *empty_synth_test;
अटल काष्ठा trace_event_file *gen_synth_test;

/*
 * Test to make sure we can create a synthetic event, then add more
 * fields.
 */
अटल पूर्णांक __init test_gen_synth_cmd(व्योम)
अणु
	काष्ठा dynevent_cmd cmd;
	u64 vals[7];
	अक्षर *buf;
	पूर्णांक ret;

	/* Create a buffer to hold the generated command */
	buf = kzalloc(MAX_DYNEVENT_CMD_LEN, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	/* Beक्रमe generating the command, initialize the cmd object */
	synth_event_cmd_init(&cmd, buf, MAX_DYNEVENT_CMD_LEN);

	/*
	 * Create the empty gen_synth_test synthetic event with the
	 * first 4 fields.
	 */
	ret = synth_event_gen_cmd_start(&cmd, "gen_synth_test", THIS_MODULE,
					"pid_t", "next_pid_field",
					"char[16]", "next_comm_field",
					"u64", "ts_ns",
					"u64", "ts_ms");
	अगर (ret)
		जाओ मुक्त;

	/* Use synth_event_add_field to add the rest of the fields */

	ret = synth_event_add_field(&cmd, "unsigned int", "cpu");
	अगर (ret)
		जाओ मुक्त;

	ret = synth_event_add_field(&cmd, "char[64]", "my_string_field");
	अगर (ret)
		जाओ मुक्त;

	ret = synth_event_add_field(&cmd, "int", "my_int_field");
	अगर (ret)
		जाओ मुक्त;

	ret = synth_event_gen_cmd_end(&cmd);
	अगर (ret)
		जाओ मुक्त;

	/*
	 * Now get the gen_synth_test event file.  We need to prevent
	 * the instance and event from disappearing from underneath
	 * us, which trace_get_event_file() करोes (though in this हाल
	 * we're using the top-level instance which never goes away).
	 */
	gen_synth_test = trace_get_event_file(शून्य, "synthetic",
					      "gen_synth_test");
	अगर (IS_ERR(gen_synth_test)) अणु
		ret = PTR_ERR(gen_synth_test);
		जाओ delete;
	पूर्ण

	/* Enable the event or you won't see anything */
	ret = trace_array_set_clr_event(gen_synth_test->tr,
					"synthetic", "gen_synth_test", true);
	अगर (ret) अणु
		trace_put_event_file(gen_synth_test);
		जाओ delete;
	पूर्ण

	/* Create some bogus values just क्रम testing */

	vals[0] = 777;			/* next_pid_field */
	vals[1] = (u64)(दीर्घ)"hula hoops";	/* next_comm_field */
	vals[2] = 1000000;		/* ts_ns */
	vals[3] = 1000;			/* ts_ms */
	vals[4] = raw_smp_processor_id(); /* cpu */
	vals[5] = (u64)(दीर्घ)"thneed";	/* my_string_field */
	vals[6] = 598;			/* my_पूर्णांक_field */

	/* Now generate a gen_synth_test event */
	ret = synth_event_trace_array(gen_synth_test, vals, ARRAY_SIZE(vals));
 out:
	वापस ret;
 delete:
	/* We got an error after creating the event, delete it */
	synth_event_delete("gen_synth_test");
 मुक्त:
	kमुक्त(buf);

	जाओ out;
पूर्ण

/*
 * Test to make sure we can create an initially empty synthetic event,
 * then add all the fields.
 */
अटल पूर्णांक __init test_empty_synth_event(व्योम)
अणु
	काष्ठा dynevent_cmd cmd;
	u64 vals[7];
	अक्षर *buf;
	पूर्णांक ret;

	/* Create a buffer to hold the generated command */
	buf = kzalloc(MAX_DYNEVENT_CMD_LEN, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	/* Beक्रमe generating the command, initialize the cmd object */
	synth_event_cmd_init(&cmd, buf, MAX_DYNEVENT_CMD_LEN);

	/*
	 * Create the empty_synth_test synthetic event with no fields.
	 */
	ret = synth_event_gen_cmd_start(&cmd, "empty_synth_test", THIS_MODULE);
	अगर (ret)
		जाओ मुक्त;

	/* Use synth_event_add_field to add all of the fields */

	ret = synth_event_add_field(&cmd, "pid_t", "next_pid_field");
	अगर (ret)
		जाओ मुक्त;

	ret = synth_event_add_field(&cmd, "char[16]", "next_comm_field");
	अगर (ret)
		जाओ मुक्त;

	ret = synth_event_add_field(&cmd, "u64", "ts_ns");
	अगर (ret)
		जाओ मुक्त;

	ret = synth_event_add_field(&cmd, "u64", "ts_ms");
	अगर (ret)
		जाओ मुक्त;

	ret = synth_event_add_field(&cmd, "unsigned int", "cpu");
	अगर (ret)
		जाओ मुक्त;

	ret = synth_event_add_field(&cmd, "char[64]", "my_string_field");
	अगर (ret)
		जाओ मुक्त;

	ret = synth_event_add_field(&cmd, "int", "my_int_field");
	अगर (ret)
		जाओ मुक्त;

	/* All fields have been added, बंद and रेजिस्टर the synth event */

	ret = synth_event_gen_cmd_end(&cmd);
	अगर (ret)
		जाओ मुक्त;

	/*
	 * Now get the empty_synth_test event file.  We need to
	 * prevent the instance and event from disappearing from
	 * underneath us, which trace_get_event_file() करोes (though in
	 * this हाल we're using the top-level instance which never
	 * goes away).
	 */
	empty_synth_test = trace_get_event_file(शून्य, "synthetic",
						"empty_synth_test");
	अगर (IS_ERR(empty_synth_test)) अणु
		ret = PTR_ERR(empty_synth_test);
		जाओ delete;
	पूर्ण

	/* Enable the event or you won't see anything */
	ret = trace_array_set_clr_event(empty_synth_test->tr,
					"synthetic", "empty_synth_test", true);
	अगर (ret) अणु
		trace_put_event_file(empty_synth_test);
		जाओ delete;
	पूर्ण

	/* Create some bogus values just क्रम testing */

	vals[0] = 777;			/* next_pid_field */
	vals[1] = (u64)(दीर्घ)"tiddlywinks";	/* next_comm_field */
	vals[2] = 1000000;		/* ts_ns */
	vals[3] = 1000;			/* ts_ms */
	vals[4] = raw_smp_processor_id(); /* cpu */
	vals[5] = (u64)(दीर्घ)"thneed_2.0";	/* my_string_field */
	vals[6] = 399;			/* my_पूर्णांक_field */

	/* Now trace an empty_synth_test event */
	ret = synth_event_trace_array(empty_synth_test, vals, ARRAY_SIZE(vals));
 out:
	वापस ret;
 delete:
	/* We got an error after creating the event, delete it */
	synth_event_delete("empty_synth_test");
 मुक्त:
	kमुक्त(buf);

	जाओ out;
पूर्ण

अटल काष्ठा synth_field_desc create_synth_test_fields[] = अणु
	अणु .type = "pid_t",		.name = "next_pid_field" पूर्ण,
	अणु .type = "char[16]",		.name = "next_comm_field" पूर्ण,
	अणु .type = "u64",		.name = "ts_ns" पूर्ण,
	अणु .type = "char[]",		.name = "dynstring_field_1" पूर्ण,
	अणु .type = "u64",		.name = "ts_ms" पूर्ण,
	अणु .type = "unsigned int",	.name = "cpu" पूर्ण,
	अणु .type = "char[64]",		.name = "my_string_field" पूर्ण,
	अणु .type = "char[]",		.name = "dynstring_field_2" पूर्ण,
	अणु .type = "int",		.name = "my_int_field" पूर्ण,
पूर्ण;

/*
 * Test synthetic event creation all at once from array of field
 * descriptors.
 */
अटल पूर्णांक __init test_create_synth_event(व्योम)
अणु
	u64 vals[9];
	पूर्णांक ret;

	/* Create the create_synth_test event with the fields above */
	ret = synth_event_create("create_synth_test",
				 create_synth_test_fields,
				 ARRAY_SIZE(create_synth_test_fields),
				 THIS_MODULE);
	अगर (ret)
		जाओ out;

	/*
	 * Now get the create_synth_test event file.  We need to
	 * prevent the instance and event from disappearing from
	 * underneath us, which trace_get_event_file() करोes (though in
	 * this हाल we're using the top-level instance which never
	 * goes away).
	 */
	create_synth_test = trace_get_event_file(शून्य, "synthetic",
						 "create_synth_test");
	अगर (IS_ERR(create_synth_test)) अणु
		ret = PTR_ERR(create_synth_test);
		जाओ delete;
	पूर्ण

	/* Enable the event or you won't see anything */
	ret = trace_array_set_clr_event(create_synth_test->tr,
					"synthetic", "create_synth_test", true);
	अगर (ret) अणु
		trace_put_event_file(create_synth_test);
		जाओ delete;
	पूर्ण

	/* Create some bogus values just क्रम testing */

	vals[0] = 777;			/* next_pid_field */
	vals[1] = (u64)(दीर्घ)"tiddlywinks";	/* next_comm_field */
	vals[2] = 1000000;		/* ts_ns */
	vals[3] = (u64)(दीर्घ)"xrayspecs";	/* dynstring_field_1 */
	vals[4] = 1000;			/* ts_ms */
	vals[5] = raw_smp_processor_id(); /* cpu */
	vals[6] = (u64)(दीर्घ)"thneed";	/* my_string_field */
	vals[7] = (u64)(दीर्घ)"kerplunk";	/* dynstring_field_2 */
	vals[8] = 398;			/* my_पूर्णांक_field */

	/* Now generate a create_synth_test event */
	ret = synth_event_trace_array(create_synth_test, vals, ARRAY_SIZE(vals));
 out:
	वापस ret;
 delete:
	/* We got an error after creating the event, delete it */
	synth_event_delete("create_synth_test");

	जाओ out;
पूर्ण

/*
 * Test tracing a synthetic event by reserving trace buffer space,
 * then filling in fields one after another.
 */
अटल पूर्णांक __init test_add_next_synth_val(व्योम)
अणु
	काष्ठा synth_event_trace_state trace_state;
	पूर्णांक ret;

	/* Start by reserving space in the trace buffer */
	ret = synth_event_trace_start(gen_synth_test, &trace_state);
	अगर (ret)
		वापस ret;

	/* Write some bogus values पूर्णांकo the trace buffer, one after another */

	/* next_pid_field */
	ret = synth_event_add_next_val(777, &trace_state);
	अगर (ret)
		जाओ out;

	/* next_comm_field */
	ret = synth_event_add_next_val((u64)(दीर्घ)"slinky", &trace_state);
	अगर (ret)
		जाओ out;

	/* ts_ns */
	ret = synth_event_add_next_val(1000000, &trace_state);
	अगर (ret)
		जाओ out;

	/* ts_ms */
	ret = synth_event_add_next_val(1000, &trace_state);
	अगर (ret)
		जाओ out;

	/* cpu */
	ret = synth_event_add_next_val(raw_smp_processor_id(), &trace_state);
	अगर (ret)
		जाओ out;

	/* my_string_field */
	ret = synth_event_add_next_val((u64)(दीर्घ)"thneed_2.01", &trace_state);
	अगर (ret)
		जाओ out;

	/* my_पूर्णांक_field */
	ret = synth_event_add_next_val(395, &trace_state);
 out:
	/* Finally, commit the event */
	ret = synth_event_trace_end(&trace_state);

	वापस ret;
पूर्ण

/*
 * Test tracing a synthetic event by reserving trace buffer space,
 * then filling in fields using field names, which can be करोne in any
 * order.
 */
अटल पूर्णांक __init test_add_synth_val(व्योम)
अणु
	काष्ठा synth_event_trace_state trace_state;
	पूर्णांक ret;

	/* Start by reserving space in the trace buffer */
	ret = synth_event_trace_start(gen_synth_test, &trace_state);
	अगर (ret)
		वापस ret;

	/* Write some bogus values पूर्णांकo the trace buffer, using field names */

	ret = synth_event_add_val("ts_ns", 1000000, &trace_state);
	अगर (ret)
		जाओ out;

	ret = synth_event_add_val("ts_ms", 1000, &trace_state);
	अगर (ret)
		जाओ out;

	ret = synth_event_add_val("cpu", raw_smp_processor_id(), &trace_state);
	अगर (ret)
		जाओ out;

	ret = synth_event_add_val("next_pid_field", 777, &trace_state);
	अगर (ret)
		जाओ out;

	ret = synth_event_add_val("next_comm_field", (u64)(दीर्घ)"silly putty",
				  &trace_state);
	अगर (ret)
		जाओ out;

	ret = synth_event_add_val("my_string_field", (u64)(दीर्घ)"thneed_9",
				  &trace_state);
	अगर (ret)
		जाओ out;

	ret = synth_event_add_val("my_int_field", 3999, &trace_state);
 out:
	/* Finally, commit the event */
	ret = synth_event_trace_end(&trace_state);

	वापस ret;
पूर्ण

/*
 * Test tracing a synthetic event all at once from array of values.
 */
अटल पूर्णांक __init test_trace_synth_event(व्योम)
अणु
	पूर्णांक ret;

	/* Trace some bogus values just क्रम testing */
	ret = synth_event_trace(create_synth_test, 9,	/* number of values */
				(u64)444,		/* next_pid_field */
				(u64)(दीर्घ)"clackers",	/* next_comm_field */
				(u64)1000000,		/* ts_ns */
				(u64)(दीर्घ)"viewmaster",/* dynstring_field_1 */
				(u64)1000,		/* ts_ms */
				(u64)raw_smp_processor_id(), /* cpu */
				(u64)(दीर्घ)"Thneed",	/* my_string_field */
				(u64)(दीर्घ)"yoyos",	/* dynstring_field_2 */
				(u64)999);		/* my_पूर्णांक_field */
	वापस ret;
पूर्ण

अटल पूर्णांक __init synth_event_gen_test_init(व्योम)
अणु
	पूर्णांक ret;

	ret = test_gen_synth_cmd();
	अगर (ret)
		वापस ret;

	ret = test_empty_synth_event();
	अगर (ret) अणु
		WARN_ON(trace_array_set_clr_event(gen_synth_test->tr,
						  "synthetic",
						  "gen_synth_test", false));
		trace_put_event_file(gen_synth_test);
		WARN_ON(synth_event_delete("gen_synth_test"));
		जाओ out;
	पूर्ण

	ret = test_create_synth_event();
	अगर (ret) अणु
		WARN_ON(trace_array_set_clr_event(gen_synth_test->tr,
						  "synthetic",
						  "gen_synth_test", false));
		trace_put_event_file(gen_synth_test);
		WARN_ON(synth_event_delete("gen_synth_test"));

		WARN_ON(trace_array_set_clr_event(empty_synth_test->tr,
						  "synthetic",
						  "empty_synth_test", false));
		trace_put_event_file(empty_synth_test);
		WARN_ON(synth_event_delete("empty_synth_test"));
		जाओ out;
	पूर्ण

	ret = test_add_next_synth_val();
	WARN_ON(ret);

	ret = test_add_synth_val();
	WARN_ON(ret);

	ret = test_trace_synth_event();
	WARN_ON(ret);
 out:
	वापस ret;
पूर्ण

अटल व्योम __निकास synth_event_gen_test_निकास(व्योम)
अणु
	/* Disable the event or you can't हटाओ it */
	WARN_ON(trace_array_set_clr_event(gen_synth_test->tr,
					  "synthetic",
					  "gen_synth_test", false));

	/* Now give the file and instance back */
	trace_put_event_file(gen_synth_test);

	/* Now unरेजिस्टर and मुक्त the synthetic event */
	WARN_ON(synth_event_delete("gen_synth_test"));

	/* Disable the event or you can't हटाओ it */
	WARN_ON(trace_array_set_clr_event(empty_synth_test->tr,
					  "synthetic",
					  "empty_synth_test", false));

	/* Now give the file and instance back */
	trace_put_event_file(empty_synth_test);

	/* Now unरेजिस्टर and मुक्त the synthetic event */
	WARN_ON(synth_event_delete("empty_synth_test"));

	/* Disable the event or you can't हटाओ it */
	WARN_ON(trace_array_set_clr_event(create_synth_test->tr,
					  "synthetic",
					  "create_synth_test", false));

	/* Now give the file and instance back */
	trace_put_event_file(create_synth_test);

	/* Now unरेजिस्टर and मुक्त the synthetic event */
	WARN_ON(synth_event_delete("create_synth_test"));
पूर्ण

module_init(synth_event_gen_test_init)
module_निकास(synth_event_gen_test_निकास)

MODULE_AUTHOR("Tom Zanussi");
MODULE_DESCRIPTION("synthetic event generation test");
MODULE_LICENSE("GPL v2");
