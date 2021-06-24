<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * KUnit test क्रम core test infraकाष्ठाure.
 *
 * Copyright (C) 2019, Google LLC.
 * Author: Brendan Higgins <brendanhiggins@google.com>
 */
#समावेश <kunit/test.h>

#समावेश "try-catch-impl.h"

काष्ठा kunit_try_catch_test_context अणु
	काष्ठा kunit_try_catch *try_catch;
	bool function_called;
पूर्ण;

अटल व्योम kunit_test_successful_try(व्योम *data)
अणु
	काष्ठा kunit *test = data;
	काष्ठा kunit_try_catch_test_context *ctx = test->priv;

	ctx->function_called = true;
पूर्ण

अटल व्योम kunit_test_no_catch(व्योम *data)
अणु
	काष्ठा kunit *test = data;

	KUNIT_FAIL(test, "Catch should not be called\n");
पूर्ण

अटल व्योम kunit_test_try_catch_successful_try_no_catch(काष्ठा kunit *test)
अणु
	काष्ठा kunit_try_catch_test_context *ctx = test->priv;
	काष्ठा kunit_try_catch *try_catch = ctx->try_catch;

	kunit_try_catch_init(try_catch,
			     test,
			     kunit_test_successful_try,
			     kunit_test_no_catch);
	kunit_try_catch_run(try_catch, test);

	KUNIT_EXPECT_TRUE(test, ctx->function_called);
पूर्ण

अटल व्योम kunit_test_unsuccessful_try(व्योम *data)
अणु
	काष्ठा kunit *test = data;
	काष्ठा kunit_try_catch_test_context *ctx = test->priv;
	काष्ठा kunit_try_catch *try_catch = ctx->try_catch;

	kunit_try_catch_throw(try_catch);
	KUNIT_FAIL(test, "This line should never be reached\n");
पूर्ण

अटल व्योम kunit_test_catch(व्योम *data)
अणु
	काष्ठा kunit *test = data;
	काष्ठा kunit_try_catch_test_context *ctx = test->priv;

	ctx->function_called = true;
पूर्ण

अटल व्योम kunit_test_try_catch_unsuccessful_try_करोes_catch(काष्ठा kunit *test)
अणु
	काष्ठा kunit_try_catch_test_context *ctx = test->priv;
	काष्ठा kunit_try_catch *try_catch = ctx->try_catch;

	kunit_try_catch_init(try_catch,
			     test,
			     kunit_test_unsuccessful_try,
			     kunit_test_catch);
	kunit_try_catch_run(try_catch, test);

	KUNIT_EXPECT_TRUE(test, ctx->function_called);
पूर्ण

अटल पूर्णांक kunit_try_catch_test_init(काष्ठा kunit *test)
अणु
	काष्ठा kunit_try_catch_test_context *ctx;

	ctx = kunit_kzalloc(test, माप(*ctx), GFP_KERNEL);
	KUNIT_ASSERT_NOT_ERR_OR_शून्य(test, ctx);
	test->priv = ctx;

	ctx->try_catch = kunit_kदो_स्मृति(test,
				       माप(*ctx->try_catch),
				       GFP_KERNEL);
	KUNIT_ASSERT_NOT_ERR_OR_शून्य(test, ctx->try_catch);

	वापस 0;
पूर्ण

अटल काष्ठा kunit_हाल kunit_try_catch_test_हालs[] = अणु
	KUNIT_CASE(kunit_test_try_catch_successful_try_no_catch),
	KUNIT_CASE(kunit_test_try_catch_unsuccessful_try_करोes_catch),
	अणुपूर्ण
पूर्ण;

अटल काष्ठा kunit_suite kunit_try_catch_test_suite = अणु
	.name = "kunit-try-catch-test",
	.init = kunit_try_catch_test_init,
	.test_हालs = kunit_try_catch_test_हालs,
पूर्ण;

/*
 * Context क्रम testing test managed resources
 * is_resource_initialized is used to test arbitrary resources
 */
काष्ठा kunit_test_resource_context अणु
	काष्ठा kunit test;
	bool is_resource_initialized;
	पूर्णांक allocate_order[2];
	पूर्णांक मुक्त_order[2];
पूर्ण;

अटल पूर्णांक fake_resource_init(काष्ठा kunit_resource *res, व्योम *context)
अणु
	काष्ठा kunit_test_resource_context *ctx = context;

	res->data = &ctx->is_resource_initialized;
	ctx->is_resource_initialized = true;
	वापस 0;
पूर्ण

अटल व्योम fake_resource_मुक्त(काष्ठा kunit_resource *res)
अणु
	bool *is_resource_initialized = res->data;

	*is_resource_initialized = false;
पूर्ण

अटल व्योम kunit_resource_test_init_resources(काष्ठा kunit *test)
अणु
	काष्ठा kunit_test_resource_context *ctx = test->priv;

	kunit_init_test(&ctx->test, "testing_test_init_test", शून्य);

	KUNIT_EXPECT_TRUE(test, list_empty(&ctx->test.resources));
पूर्ण

अटल व्योम kunit_resource_test_alloc_resource(काष्ठा kunit *test)
अणु
	काष्ठा kunit_test_resource_context *ctx = test->priv;
	काष्ठा kunit_resource *res;
	kunit_resource_मुक्त_t मुक्त = fake_resource_मुक्त;

	res = kunit_alloc_and_get_resource(&ctx->test,
					   fake_resource_init,
					   fake_resource_मुक्त,
					   GFP_KERNEL,
					   ctx);

	KUNIT_ASSERT_NOT_ERR_OR_शून्य(test, res);
	KUNIT_EXPECT_PTR_EQ(test,
			    &ctx->is_resource_initialized,
			    (bool *)res->data);
	KUNIT_EXPECT_TRUE(test, list_is_last(&res->node, &ctx->test.resources));
	KUNIT_EXPECT_PTR_EQ(test, मुक्त, res->मुक्त);

	kunit_put_resource(res);
पूर्ण

/*
 * Note: tests below use kunit_alloc_and_get_resource(), so as a consequence
 * they have a reference to the associated resource that they must release
 * via kunit_put_resource().  In normal operation, users will only
 * have to करो this क्रम हालs where they use kunit_find_resource(), and the
 * kunit_alloc_resource() function will be used (which करोes not take a
 * resource reference).
 */
अटल व्योम kunit_resource_test_destroy_resource(काष्ठा kunit *test)
अणु
	काष्ठा kunit_test_resource_context *ctx = test->priv;
	काष्ठा kunit_resource *res = kunit_alloc_and_get_resource(
			&ctx->test,
			fake_resource_init,
			fake_resource_मुक्त,
			GFP_KERNEL,
			ctx);

	kunit_put_resource(res);

	KUNIT_ASSERT_FALSE(test,
			   kunit_destroy_resource(&ctx->test,
						  kunit_resource_instance_match,
						  res->data));

	KUNIT_EXPECT_FALSE(test, ctx->is_resource_initialized);
	KUNIT_EXPECT_TRUE(test, list_empty(&ctx->test.resources));
पूर्ण

अटल व्योम kunit_resource_test_cleanup_resources(काष्ठा kunit *test)
अणु
	पूर्णांक i;
	काष्ठा kunit_test_resource_context *ctx = test->priv;
	काष्ठा kunit_resource *resources[5];

	क्रम (i = 0; i < ARRAY_SIZE(resources); i++) अणु
		resources[i] = kunit_alloc_and_get_resource(&ctx->test,
							    fake_resource_init,
							    fake_resource_मुक्त,
							    GFP_KERNEL,
							    ctx);
		kunit_put_resource(resources[i]);
	पूर्ण

	kunit_cleanup(&ctx->test);

	KUNIT_EXPECT_TRUE(test, list_empty(&ctx->test.resources));
पूर्ण

अटल व्योम kunit_resource_test_mark_order(पूर्णांक order_array[],
					   माप_प्रकार order_size,
					   पूर्णांक key)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < order_size && order_array[i]; i++)
		;

	order_array[i] = key;
पूर्ण

#घोषणा KUNIT_RESOURCE_TEST_MARK_ORDER(ctx, order_field, key)		       \
		kunit_resource_test_mark_order(ctx->order_field,	       \
					       ARRAY_SIZE(ctx->order_field),   \
					       key)

अटल पूर्णांक fake_resource_2_init(काष्ठा kunit_resource *res, व्योम *context)
अणु
	काष्ठा kunit_test_resource_context *ctx = context;

	KUNIT_RESOURCE_TEST_MARK_ORDER(ctx, allocate_order, 2);

	res->data = ctx;

	वापस 0;
पूर्ण

अटल व्योम fake_resource_2_मुक्त(काष्ठा kunit_resource *res)
अणु
	काष्ठा kunit_test_resource_context *ctx = res->data;

	KUNIT_RESOURCE_TEST_MARK_ORDER(ctx, मुक्त_order, 2);
पूर्ण

अटल पूर्णांक fake_resource_1_init(काष्ठा kunit_resource *res, व्योम *context)
अणु
	काष्ठा kunit_test_resource_context *ctx = context;
	काष्ठा kunit_resource *res2;

	res2 = kunit_alloc_and_get_resource(&ctx->test,
					    fake_resource_2_init,
					    fake_resource_2_मुक्त,
					    GFP_KERNEL,
					    ctx);

	KUNIT_RESOURCE_TEST_MARK_ORDER(ctx, allocate_order, 1);

	res->data = ctx;

	kunit_put_resource(res2);

	वापस 0;
पूर्ण

अटल व्योम fake_resource_1_मुक्त(काष्ठा kunit_resource *res)
अणु
	काष्ठा kunit_test_resource_context *ctx = res->data;

	KUNIT_RESOURCE_TEST_MARK_ORDER(ctx, मुक्त_order, 1);
पूर्ण

/*
 * TODO(brendanhiggins@google.com): replace the arrays that keep track of the
 * order of allocation and मुक्तing with strict mocks using the IN_SEQUENCE macro
 * to निश्चित allocation and मुक्तing order when the feature becomes available.
 */
अटल व्योम kunit_resource_test_proper_मुक्त_ordering(काष्ठा kunit *test)
अणु
	काष्ठा kunit_test_resource_context *ctx = test->priv;
	काष्ठा kunit_resource *res;

	/* fake_resource_1 allocates a fake_resource_2 in its init. */
	res = kunit_alloc_and_get_resource(&ctx->test,
					   fake_resource_1_init,
					   fake_resource_1_मुक्त,
					   GFP_KERNEL,
					   ctx);

	/*
	 * Since fake_resource_2_init calls KUNIT_RESOURCE_TEST_MARK_ORDER
	 * beक्रमe वापसing to fake_resource_1_init, it should be the first to
	 * put its key in the allocate_order array.
	 */
	KUNIT_EXPECT_EQ(test, ctx->allocate_order[0], 2);
	KUNIT_EXPECT_EQ(test, ctx->allocate_order[1], 1);

	kunit_put_resource(res);

	kunit_cleanup(&ctx->test);

	/*
	 * Because fake_resource_2 finishes allocation beक्रमe fake_resource_1,
	 * fake_resource_1 should be मुक्तd first since it could depend on
	 * fake_resource_2.
	 */
	KUNIT_EXPECT_EQ(test, ctx->मुक्त_order[0], 1);
	KUNIT_EXPECT_EQ(test, ctx->मुक्त_order[1], 2);
पूर्ण

अटल व्योम kunit_resource_test_अटल(काष्ठा kunit *test)
अणु
	काष्ठा kunit_test_resource_context ctx;
	काष्ठा kunit_resource res;

	KUNIT_EXPECT_EQ(test, kunit_add_resource(test, शून्य, शून्य, &res, &ctx),
			0);

	KUNIT_EXPECT_PTR_EQ(test, res.data, (व्योम *)&ctx);

	kunit_cleanup(test);

	KUNIT_EXPECT_TRUE(test, list_empty(&test->resources));
पूर्ण

अटल व्योम kunit_resource_test_named(काष्ठा kunit *test)
अणु
	काष्ठा kunit_resource res1, res2, *found = शून्य;
	काष्ठा kunit_test_resource_context ctx;

	KUNIT_EXPECT_EQ(test,
			kunit_add_named_resource(test, शून्य, शून्य, &res1,
						 "resource_1", &ctx),
			0);
	KUNIT_EXPECT_PTR_EQ(test, res1.data, (व्योम *)&ctx);

	KUNIT_EXPECT_EQ(test,
			kunit_add_named_resource(test, शून्य, शून्य, &res1,
						 "resource_1", &ctx),
			-EEXIST);

	KUNIT_EXPECT_EQ(test,
			kunit_add_named_resource(test, शून्य, शून्य, &res2,
						 "resource_2", &ctx),
			0);

	found = kunit_find_named_resource(test, "resource_1");

	KUNIT_EXPECT_PTR_EQ(test, found, &res1);

	अगर (found)
		kunit_put_resource(&res1);

	KUNIT_EXPECT_EQ(test, kunit_destroy_named_resource(test, "resource_2"),
			0);

	kunit_cleanup(test);

	KUNIT_EXPECT_TRUE(test, list_empty(&test->resources));
पूर्ण

अटल पूर्णांक kunit_resource_test_init(काष्ठा kunit *test)
अणु
	काष्ठा kunit_test_resource_context *ctx =
			kzalloc(माप(*ctx), GFP_KERNEL);

	KUNIT_ASSERT_NOT_ERR_OR_शून्य(test, ctx);

	test->priv = ctx;

	kunit_init_test(&ctx->test, "test_test_context", शून्य);

	वापस 0;
पूर्ण

अटल व्योम kunit_resource_test_निकास(काष्ठा kunit *test)
अणु
	काष्ठा kunit_test_resource_context *ctx = test->priv;

	kunit_cleanup(&ctx->test);
	kमुक्त(ctx);
पूर्ण

अटल काष्ठा kunit_हाल kunit_resource_test_हालs[] = अणु
	KUNIT_CASE(kunit_resource_test_init_resources),
	KUNIT_CASE(kunit_resource_test_alloc_resource),
	KUNIT_CASE(kunit_resource_test_destroy_resource),
	KUNIT_CASE(kunit_resource_test_cleanup_resources),
	KUNIT_CASE(kunit_resource_test_proper_मुक्त_ordering),
	KUNIT_CASE(kunit_resource_test_अटल),
	KUNIT_CASE(kunit_resource_test_named),
	अणुपूर्ण
पूर्ण;

अटल काष्ठा kunit_suite kunit_resource_test_suite = अणु
	.name = "kunit-resource-test",
	.init = kunit_resource_test_init,
	.निकास = kunit_resource_test_निकास,
	.test_हालs = kunit_resource_test_हालs,
पूर्ण;

अटल व्योम kunit_log_test(काष्ठा kunit *test);

अटल काष्ठा kunit_हाल kunit_log_test_हालs[] = अणु
	KUNIT_CASE(kunit_log_test),
	अणुपूर्ण
पूर्ण;

अटल काष्ठा kunit_suite kunit_log_test_suite = अणु
	.name = "kunit-log-test",
	.test_हालs = kunit_log_test_हालs,
पूर्ण;

अटल व्योम kunit_log_test(काष्ठा kunit *test)
अणु
	काष्ठा kunit_suite *suite = &kunit_log_test_suite;

	kunit_log(KERN_INFO, test, "put this in log.");
	kunit_log(KERN_INFO, test, "this too.");
	kunit_log(KERN_INFO, suite, "add to suite log.");
	kunit_log(KERN_INFO, suite, "along with this.");

#अगर_घोषित CONFIG_KUNIT_DEBUGFS
	KUNIT_EXPECT_NOT_ERR_OR_शून्य(test,
				     म_माला(test->log, "put this in log."));
	KUNIT_EXPECT_NOT_ERR_OR_शून्य(test,
				     म_माला(test->log, "this too."));
	KUNIT_EXPECT_NOT_ERR_OR_शून्य(test,
				     म_माला(suite->log, "add to suite log."));
	KUNIT_EXPECT_NOT_ERR_OR_शून्य(test,
				     म_माला(suite->log, "along with this."));
#अन्यथा
	KUNIT_EXPECT_PTR_EQ(test, test->log, (अक्षर *)शून्य);
	KUNIT_EXPECT_PTR_EQ(test, suite->log, (अक्षर *)शून्य);
#पूर्ण_अगर
पूर्ण

kunit_test_suites(&kunit_try_catch_test_suite, &kunit_resource_test_suite,
		  &kunit_log_test_suite);

MODULE_LICENSE("GPL v2");
