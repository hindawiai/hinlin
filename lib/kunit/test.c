<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Base unit test (KUnit) API.
 *
 * Copyright (C) 2019, Google LLC.
 * Author: Brendan Higgins <brendanhiggins@google.com>
 */

#समावेश <kunit/test.h>
#समावेश <kunit/test-bug.h>
#समावेश <linux/kernel.h>
#समावेश <linux/kref.h>
#समावेश <linux/sched/debug.h>
#समावेश <linux/sched.h>

#समावेश "debugfs.h"
#समावेश "string-stream.h"
#समावेश "try-catch-impl.h"

#अगर IS_BUILTIN(CONFIG_KUNIT)
/*
 * Fail the current test and prपूर्णांक an error message to the log.
 */
व्योम __kunit_fail_current_test(स्थिर अक्षर *file, पूर्णांक line, स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची args;
	पूर्णांक len;
	अक्षर *buffer;

	अगर (!current->kunit_test)
		वापस;

	kunit_set_failure(current->kunit_test);

	/* kunit_err() only accepts literals, so evaluate the args first. */
	बहु_शुरू(args, fmt);
	len = vsnम_लिखो(शून्य, 0, fmt, args) + 1;
	बहु_पूर्ण(args);

	buffer = kunit_kदो_स्मृति(current->kunit_test, len, GFP_KERNEL);
	अगर (!buffer)
		वापस;

	बहु_शुरू(args, fmt);
	vsnम_लिखो(buffer, len, fmt, args);
	बहु_पूर्ण(args);

	kunit_err(current->kunit_test, "%s:%d: %s", file, line, buffer);
	kunit_kमुक्त(current->kunit_test, buffer);
पूर्ण
EXPORT_SYMBOL_GPL(__kunit_fail_current_test);
#पूर्ण_अगर

/*
 * Append क्रमmatted message to log, size of which is limited to
 * KUNIT_LOG_SIZE bytes (including null terminating byte).
 */
व्योम kunit_log_append(अक्षर *log, स्थिर अक्षर *fmt, ...)
अणु
	अक्षर line[KUNIT_LOG_SIZE];
	बहु_सूची args;
	पूर्णांक len_left;

	अगर (!log)
		वापस;

	len_left = KUNIT_LOG_SIZE - म_माप(log) - 1;
	अगर (len_left <= 0)
		वापस;

	बहु_शुरू(args, fmt);
	vsnम_लिखो(line, माप(line), fmt, args);
	बहु_पूर्ण(args);

	म_जोड़न(log, line, len_left);
पूर्ण
EXPORT_SYMBOL_GPL(kunit_log_append);

माप_प्रकार kunit_suite_num_test_हालs(काष्ठा kunit_suite *suite)
अणु
	काष्ठा kunit_हाल *test_हाल;
	माप_प्रकार len = 0;

	kunit_suite_क्रम_each_test_हाल(suite, test_हाल)
		len++;

	वापस len;
पूर्ण
EXPORT_SYMBOL_GPL(kunit_suite_num_test_हालs);

अटल व्योम kunit_prपूर्णांक_subtest_start(काष्ठा kunit_suite *suite)
अणु
	kunit_log(KERN_INFO, suite, KUNIT_SUBTEST_INDENT "# Subtest: %s",
		  suite->name);
	kunit_log(KERN_INFO, suite, KUNIT_SUBTEST_INDENT "1..%zd",
		  kunit_suite_num_test_हालs(suite));
पूर्ण

अटल व्योम kunit_prपूर्णांक_ok_not_ok(व्योम *test_or_suite,
				  bool is_test,
				  bool is_ok,
				  माप_प्रकार test_number,
				  स्थिर अक्षर *description)
अणु
	काष्ठा kunit_suite *suite = is_test ? शून्य : test_or_suite;
	काष्ठा kunit *test = is_test ? test_or_suite : शून्य;

	/*
	 * We करो not log the test suite results as करोing so would
	 * mean debugfs display would consist of the test suite
	 * description and status prior to inभागidual test results.
	 * Hence directly prपूर्णांकk the suite status, and we will
	 * separately seq_म_लिखो() the suite status क्रम the debugfs
	 * representation.
	 */
	अगर (suite)
		pr_info("%s %zd - %s\n",
			kunit_status_to_string(is_ok),
			test_number, description);
	अन्यथा
		kunit_log(KERN_INFO, test, KUNIT_SUBTEST_INDENT "%s %zd - %s",
			  kunit_status_to_string(is_ok),
			  test_number, description);
पूर्ण

bool kunit_suite_has_succeeded(काष्ठा kunit_suite *suite)
अणु
	स्थिर काष्ठा kunit_हाल *test_हाल;

	kunit_suite_क्रम_each_test_हाल(suite, test_हाल) अणु
		अगर (!test_हाल->success)
			वापस false;
	पूर्ण

	वापस true;
पूर्ण
EXPORT_SYMBOL_GPL(kunit_suite_has_succeeded);

अटल व्योम kunit_prपूर्णांक_subtest_end(काष्ठा kunit_suite *suite)
अणु
	अटल माप_प्रकार kunit_suite_counter = 1;

	kunit_prपूर्णांक_ok_not_ok((व्योम *)suite, false,
			      kunit_suite_has_succeeded(suite),
			      kunit_suite_counter++,
			      suite->name);
पूर्ण

अचिन्हित पूर्णांक kunit_test_हाल_num(काष्ठा kunit_suite *suite,
				 काष्ठा kunit_हाल *test_हाल)
अणु
	काष्ठा kunit_हाल *tc;
	अचिन्हित पूर्णांक i = 1;

	kunit_suite_क्रम_each_test_हाल(suite, tc) अणु
		अगर (tc == test_हाल)
			वापस i;
		i++;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(kunit_test_हाल_num);

अटल व्योम kunit_prपूर्णांक_string_stream(काष्ठा kunit *test,
				      काष्ठा string_stream *stream)
अणु
	काष्ठा string_stream_fragment *fragment;
	अक्षर *buf;

	अगर (string_stream_is_empty(stream))
		वापस;

	buf = string_stream_get_string(stream);
	अगर (!buf) अणु
		kunit_err(test,
			  "Could not allocate buffer, dumping stream:\n");
		list_क्रम_each_entry(fragment, &stream->fragments, node) अणु
			kunit_err(test, "%s", fragment->fragment);
		पूर्ण
		kunit_err(test, "\n");
	पूर्ण अन्यथा अणु
		kunit_err(test, "%s", buf);
		kunit_kमुक्त(test, buf);
	पूर्ण
पूर्ण

अटल व्योम kunit_fail(काष्ठा kunit *test, काष्ठा kunit_निश्चित *निश्चित)
अणु
	काष्ठा string_stream *stream;

	kunit_set_failure(test);

	stream = alloc_string_stream(test, GFP_KERNEL);
	अगर (!stream) अणु
		WARN(true,
		     "Could not allocate stream to print failed assertion in %s:%d\n",
		     निश्चित->file,
		     निश्चित->line);
		वापस;
	पूर्ण

	निश्चित->क्रमmat(निश्चित, stream);

	kunit_prपूर्णांक_string_stream(test, stream);

	WARN_ON(string_stream_destroy(stream));
पूर्ण

अटल व्योम __noवापस kunit_पात(काष्ठा kunit *test)
अणु
	kunit_try_catch_throw(&test->try_catch); /* Does not वापस. */

	/*
	 * Throw could not पात from test.
	 *
	 * XXX: we should never reach this line! As kunit_try_catch_throw is
	 * marked __noवापस.
	 */
	WARN_ONCE(true, "Throw could not abort from test!\n");
पूर्ण

व्योम kunit_करो_निश्चितion(काष्ठा kunit *test,
			काष्ठा kunit_निश्चित *निश्चित,
			bool pass,
			स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची args;

	अगर (pass)
		वापस;

	बहु_शुरू(args, fmt);

	निश्चित->message.fmt = fmt;
	निश्चित->message.va = &args;

	kunit_fail(test, निश्चित);

	बहु_पूर्ण(args);

	अगर (निश्चित->type == KUNIT_ASSERTION)
		kunit_पात(test);
पूर्ण
EXPORT_SYMBOL_GPL(kunit_करो_निश्चितion);

व्योम kunit_init_test(काष्ठा kunit *test, स्थिर अक्षर *name, अक्षर *log)
अणु
	spin_lock_init(&test->lock);
	INIT_LIST_HEAD(&test->resources);
	test->name = name;
	test->log = log;
	अगर (test->log)
		test->log[0] = '\0';
	test->success = true;
पूर्ण
EXPORT_SYMBOL_GPL(kunit_init_test);

/*
 * Initializes and runs test हाल. Does not clean up or करो post validations.
 */
अटल व्योम kunit_run_हाल_पूर्णांकernal(काष्ठा kunit *test,
				    काष्ठा kunit_suite *suite,
				    काष्ठा kunit_हाल *test_हाल)
अणु
	अगर (suite->init) अणु
		पूर्णांक ret;

		ret = suite->init(test);
		अगर (ret) अणु
			kunit_err(test, "failed to initialize: %d\n", ret);
			kunit_set_failure(test);
			वापस;
		पूर्ण
	पूर्ण

	test_हाल->run_हाल(test);
पूर्ण

अटल व्योम kunit_हाल_पूर्णांकernal_cleanup(काष्ठा kunit *test)
अणु
	kunit_cleanup(test);
पूर्ण

/*
 * Perक्रमms post validations and cleanup after a test हाल was run.
 * XXX: Should ONLY BE CALLED AFTER kunit_run_हाल_पूर्णांकernal!
 */
अटल व्योम kunit_run_हाल_cleanup(काष्ठा kunit *test,
				   काष्ठा kunit_suite *suite)
अणु
	अगर (suite->निकास)
		suite->निकास(test);

	kunit_हाल_पूर्णांकernal_cleanup(test);
पूर्ण

काष्ठा kunit_try_catch_context अणु
	काष्ठा kunit *test;
	काष्ठा kunit_suite *suite;
	काष्ठा kunit_हाल *test_हाल;
पूर्ण;

अटल व्योम kunit_try_run_हाल(व्योम *data)
अणु
	काष्ठा kunit_try_catch_context *ctx = data;
	काष्ठा kunit *test = ctx->test;
	काष्ठा kunit_suite *suite = ctx->suite;
	काष्ठा kunit_हाल *test_हाल = ctx->test_हाल;

	current->kunit_test = test;

	/*
	 * kunit_run_हाल_पूर्णांकernal may encounter a fatal error; अगर it करोes,
	 * पात will be called, this thपढ़ो will निकास, and finally the parent
	 * thपढ़ो will resume control and handle any necessary clean up.
	 */
	kunit_run_हाल_पूर्णांकernal(test, suite, test_हाल);
	/* This line may never be reached. */
	kunit_run_हाल_cleanup(test, suite);
पूर्ण

अटल व्योम kunit_catch_run_हाल(व्योम *data)
अणु
	काष्ठा kunit_try_catch_context *ctx = data;
	काष्ठा kunit *test = ctx->test;
	काष्ठा kunit_suite *suite = ctx->suite;
	पूर्णांक try_निकास_code = kunit_try_catch_get_result(&test->try_catch);

	अगर (try_निकास_code) अणु
		kunit_set_failure(test);
		/*
		 * Test हाल could not finish, we have no idea what state it is
		 * in, so करोn't करो clean up.
		 */
		अगर (try_निकास_code == -ETIMEDOUT) अणु
			kunit_err(test, "test case timed out\n");
		/*
		 * Unknown पूर्णांकernal error occurred preventing test हाल from
		 * running, so there is nothing to clean up.
		 */
		पूर्ण अन्यथा अणु
			kunit_err(test, "internal error occurred preventing test case from running: %d\n",
				  try_निकास_code);
		पूर्ण
		वापस;
	पूर्ण

	/*
	 * Test हाल was run, but पातed. It is the test हाल's business as to
	 * whether it failed or not, we just need to clean up.
	 */
	kunit_run_हाल_cleanup(test, suite);
पूर्ण

/*
 * Perक्रमms all logic to run a test हाल. It also catches most errors that
 * occur in a test हाल and reports them as failures.
 */
अटल व्योम kunit_run_हाल_catch_errors(काष्ठा kunit_suite *suite,
					काष्ठा kunit_हाल *test_हाल,
					काष्ठा kunit *test)
अणु
	काष्ठा kunit_try_catch_context context;
	काष्ठा kunit_try_catch *try_catch;

	kunit_init_test(test, test_हाल->name, test_हाल->log);
	try_catch = &test->try_catch;

	kunit_try_catch_init(try_catch,
			     test,
			     kunit_try_run_हाल,
			     kunit_catch_run_हाल);
	context.test = test;
	context.suite = suite;
	context.test_हाल = test_हाल;
	kunit_try_catch_run(try_catch, &context);

	test_हाल->success = test->success;
पूर्ण

पूर्णांक kunit_run_tests(काष्ठा kunit_suite *suite)
अणु
	अक्षर param_desc[KUNIT_PARAM_DESC_SIZE];
	काष्ठा kunit_हाल *test_हाल;

	kunit_prपूर्णांक_subtest_start(suite);

	kunit_suite_क्रम_each_test_हाल(suite, test_हाल) अणु
		काष्ठा kunit test = अणु .param_value = शून्य, .param_index = 0 पूर्ण;
		bool test_success = true;

		अगर (test_हाल->generate_params) अणु
			/* Get initial param. */
			param_desc[0] = '\0';
			test.param_value = test_हाल->generate_params(शून्य, param_desc);
		पूर्ण

		करो अणु
			kunit_run_हाल_catch_errors(suite, test_हाल, &test);
			test_success &= test_हाल->success;

			अगर (test_हाल->generate_params) अणु
				अगर (param_desc[0] == '\0') अणु
					snम_लिखो(param_desc, माप(param_desc),
						 "param-%d", test.param_index);
				पूर्ण

				kunit_log(KERN_INFO, &test,
					  KUNIT_SUBTEST_INDENT
					  "# %s: %s %d - %s",
					  test_हाल->name,
					  kunit_status_to_string(test.success),
					  test.param_index + 1, param_desc);

				/* Get next param. */
				param_desc[0] = '\0';
				test.param_value = test_हाल->generate_params(test.param_value, param_desc);
				test.param_index++;
			पूर्ण
		पूर्ण जबतक (test.param_value);

		kunit_prपूर्णांक_ok_not_ok(&test, true, test_success,
				      kunit_test_हाल_num(suite, test_हाल),
				      test_हाल->name);
	पूर्ण

	kunit_prपूर्णांक_subtest_end(suite);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(kunit_run_tests);

अटल व्योम kunit_init_suite(काष्ठा kunit_suite *suite)
अणु
	kunit_debugfs_create_suite(suite);
पूर्ण

पूर्णांक __kunit_test_suites_init(काष्ठा kunit_suite * स्थिर * स्थिर suites)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; suites[i] != शून्य; i++) अणु
		kunit_init_suite(suites[i]);
		kunit_run_tests(suites[i]);
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(__kunit_test_suites_init);

अटल व्योम kunit_निकास_suite(काष्ठा kunit_suite *suite)
अणु
	kunit_debugfs_destroy_suite(suite);
पूर्ण

व्योम __kunit_test_suites_निकास(काष्ठा kunit_suite **suites)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; suites[i] != शून्य; i++)
		kunit_निकास_suite(suites[i]);
पूर्ण
EXPORT_SYMBOL_GPL(__kunit_test_suites_निकास);

/*
 * Used क्रम अटल resources and when a kunit_resource * has been created by
 * kunit_alloc_resource().  When an init function is supplied, @data is passed
 * पूर्णांकo the init function; otherwise, we simply set the resource data field to
 * the data value passed in.
 */
पूर्णांक kunit_add_resource(काष्ठा kunit *test,
		       kunit_resource_init_t init,
		       kunit_resource_मुक्त_t मुक्त,
		       काष्ठा kunit_resource *res,
		       व्योम *data)
अणु
	पूर्णांक ret = 0;

	res->मुक्त = मुक्त;
	kref_init(&res->refcount);

	अगर (init) अणु
		ret = init(res, data);
		अगर (ret)
			वापस ret;
	पूर्ण अन्यथा अणु
		res->data = data;
	पूर्ण

	spin_lock(&test->lock);
	list_add_tail(&res->node, &test->resources);
	/* refcount क्रम list is established by kref_init() */
	spin_unlock(&test->lock);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(kunit_add_resource);

पूर्णांक kunit_add_named_resource(काष्ठा kunit *test,
			     kunit_resource_init_t init,
			     kunit_resource_मुक्त_t मुक्त,
			     काष्ठा kunit_resource *res,
			     स्थिर अक्षर *name,
			     व्योम *data)
अणु
	काष्ठा kunit_resource *existing;

	अगर (!name)
		वापस -EINVAL;

	existing = kunit_find_named_resource(test, name);
	अगर (existing) अणु
		kunit_put_resource(existing);
		वापस -EEXIST;
	पूर्ण

	res->name = name;

	वापस kunit_add_resource(test, init, मुक्त, res, data);
पूर्ण
EXPORT_SYMBOL_GPL(kunit_add_named_resource);

काष्ठा kunit_resource *kunit_alloc_and_get_resource(काष्ठा kunit *test,
						    kunit_resource_init_t init,
						    kunit_resource_मुक्त_t मुक्त,
						    gfp_t पूर्णांकernal_gfp,
						    व्योम *data)
अणु
	काष्ठा kunit_resource *res;
	पूर्णांक ret;

	res = kzalloc(माप(*res), पूर्णांकernal_gfp);
	अगर (!res)
		वापस शून्य;

	ret = kunit_add_resource(test, init, मुक्त, res, data);
	अगर (!ret) अणु
		/*
		 * bump refcount क्रम get; kunit_resource_put() should be called
		 * when करोne.
		 */
		kunit_get_resource(res);
		वापस res;
	पूर्ण
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(kunit_alloc_and_get_resource);

व्योम kunit_हटाओ_resource(काष्ठा kunit *test, काष्ठा kunit_resource *res)
अणु
	spin_lock(&test->lock);
	list_del(&res->node);
	spin_unlock(&test->lock);
	kunit_put_resource(res);
पूर्ण
EXPORT_SYMBOL_GPL(kunit_हटाओ_resource);

पूर्णांक kunit_destroy_resource(काष्ठा kunit *test, kunit_resource_match_t match,
			   व्योम *match_data)
अणु
	काष्ठा kunit_resource *res = kunit_find_resource(test, match,
							 match_data);

	अगर (!res)
		वापस -ENOENT;

	kunit_हटाओ_resource(test, res);

	/* We have a reference also via _find(); drop it. */
	kunit_put_resource(res);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(kunit_destroy_resource);

काष्ठा kunit_kदो_स्मृति_params अणु
	माप_प्रकार size;
	gfp_t gfp;
पूर्ण;

अटल पूर्णांक kunit_kदो_स्मृति_init(काष्ठा kunit_resource *res, व्योम *context)
अणु
	काष्ठा kunit_kदो_स्मृति_params *params = context;

	res->data = kदो_स्मृति(params->size, params->gfp);
	अगर (!res->data)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

अटल व्योम kunit_kदो_स्मृति_मुक्त(काष्ठा kunit_resource *res)
अणु
	kमुक्त(res->data);
पूर्ण

व्योम *kunit_kदो_स्मृति(काष्ठा kunit *test, माप_प्रकार size, gfp_t gfp)
अणु
	काष्ठा kunit_kदो_स्मृति_params params = अणु
		.size = size,
		.gfp = gfp
	पूर्ण;

	वापस kunit_alloc_resource(test,
				    kunit_kदो_स्मृति_init,
				    kunit_kदो_स्मृति_मुक्त,
				    gfp,
				    &params);
पूर्ण
EXPORT_SYMBOL_GPL(kunit_kदो_स्मृति);

व्योम kunit_kमुक्त(काष्ठा kunit *test, स्थिर व्योम *ptr)
अणु
	काष्ठा kunit_resource *res;

	res = kunit_find_resource(test, kunit_resource_instance_match,
				  (व्योम *)ptr);

	/*
	 * Removing the resource from the list of resources drops the
	 * reference count to 1; the final put will trigger the मुक्त.
	 */
	kunit_हटाओ_resource(test, res);

	kunit_put_resource(res);

पूर्ण
EXPORT_SYMBOL_GPL(kunit_kमुक्त);

व्योम kunit_cleanup(काष्ठा kunit *test)
अणु
	काष्ठा kunit_resource *res;

	/*
	 * test->resources is a stack - each allocation must be मुक्तd in the
	 * reverse order from which it was added since one resource may depend
	 * on another क्रम its entire lअगरeसमय.
	 * Also, we cannot use the normal list_क्रम_each स्थिरructs, even the
	 * safe ones because *arbitrary* nodes may be deleted when
	 * kunit_resource_मुक्त is called; the list_क्रम_each_safe variants only
	 * protect against the current node being deleted, not the next.
	 */
	जबतक (true) अणु
		spin_lock(&test->lock);
		अगर (list_empty(&test->resources)) अणु
			spin_unlock(&test->lock);
			अवरोध;
		पूर्ण
		res = list_last_entry(&test->resources,
				      काष्ठा kunit_resource,
				      node);
		/*
		 * Need to unlock here as a resource may हटाओ another
		 * resource, and this can't happen अगर the test->lock
		 * is held.
		 */
		spin_unlock(&test->lock);
		kunit_हटाओ_resource(test, res);
	पूर्ण
	current->kunit_test = शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(kunit_cleanup);

अटल पूर्णांक __init kunit_init(व्योम)
अणु
	kunit_debugfs_init();

	वापस 0;
पूर्ण
late_initcall(kunit_init);

अटल व्योम __निकास kunit_निकास(व्योम)
अणु
	kunit_debugfs_cleanup();
पूर्ण
module_निकास(kunit_निकास);

MODULE_LICENSE("GPL v2");
