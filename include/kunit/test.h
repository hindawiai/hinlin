<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Base unit test (KUnit) API.
 *
 * Copyright (C) 2019, Google LLC.
 * Author: Brendan Higgins <brendanhiggins@google.com>
 */

#अगर_अघोषित _KUNIT_TEST_H
#घोषणा _KUNIT_TEST_H

#समावेश <kunit/निश्चित.स>
#समावेश <kunit/try-catch.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>
#समावेश <linux/kref.h>

काष्ठा kunit_resource;

प्रकार पूर्णांक (*kunit_resource_init_t)(काष्ठा kunit_resource *, व्योम *);
प्रकार व्योम (*kunit_resource_मुक्त_t)(काष्ठा kunit_resource *);

/**
 * काष्ठा kunit_resource - represents a *test managed resource*
 * @data: क्रम the user to store arbitrary data.
 * @name: optional name
 * @मुक्त: a user supplied function to मुक्त the resource. Populated by
 * kunit_resource_alloc().
 *
 * Represents a *test managed resource*, a resource which will स्वतःmatically be
 * cleaned up at the end of a test हाल.
 *
 * Resources are reference counted so अगर a resource is retrieved via
 * kunit_alloc_and_get_resource() or kunit_find_resource(), we need
 * to call kunit_put_resource() to reduce the resource reference count
 * when finished with it.  Note that kunit_alloc_resource() करोes not require a
 * kunit_resource_put() because it करोes not retrieve the resource itself.
 *
 * Example:
 *
 * .. code-block:: c
 *
 *	काष्ठा kunit_kदो_स्मृति_params अणु
 *		माप_प्रकार size;
 *		gfp_t gfp;
 *	पूर्ण;
 *
 *	अटल पूर्णांक kunit_kदो_स्मृति_init(काष्ठा kunit_resource *res, व्योम *context)
 *	अणु
 *		काष्ठा kunit_kदो_स्मृति_params *params = context;
 *		res->data = kदो_स्मृति(params->size, params->gfp);
 *
 *		अगर (!res->data)
 *			वापस -ENOMEM;
 *
 *		वापस 0;
 *	पूर्ण
 *
 *	अटल व्योम kunit_kदो_स्मृति_मुक्त(काष्ठा kunit_resource *res)
 *	अणु
 *		kमुक्त(res->data);
 *	पूर्ण
 *
 *	व्योम *kunit_kदो_स्मृति(काष्ठा kunit *test, माप_प्रकार size, gfp_t gfp)
 *	अणु
 *		काष्ठा kunit_kदो_स्मृति_params params;
 *
 *		params.size = size;
 *		params.gfp = gfp;
 *
 *		वापस kunit_alloc_resource(test, kunit_kदो_स्मृति_init,
 *			kunit_kदो_स्मृति_मुक्त, &params);
 *	पूर्ण
 *
 * Resources can also be named, with lookup/removal करोne on a name
 * basis also.  kunit_add_named_resource(), kunit_find_named_resource()
 * and kunit_destroy_named_resource().  Resource names must be
 * unique within the test instance.
 */
काष्ठा kunit_resource अणु
	व्योम *data;
	स्थिर अक्षर *name;
	kunit_resource_मुक्त_t मुक्त;

	/* निजी: पूर्णांकernal use only. */
	काष्ठा kref refcount;
	काष्ठा list_head node;
पूर्ण;

काष्ठा kunit;

/* Size of log associated with test. */
#घोषणा KUNIT_LOG_SIZE	512

/* Maximum size of parameter description string. */
#घोषणा KUNIT_PARAM_DESC_SIZE 128

/*
 * TAP specअगरies subtest stream indentation of 4 spaces, 8 spaces क्रम a
 * sub-subtest.  See the "Subtests" section in
 * https://node-tap.org/tap-protocol/
 */
#घोषणा KUNIT_SUBTEST_INDENT		"    "
#घोषणा KUNIT_SUBSUBTEST_INDENT		"        "

/**
 * काष्ठा kunit_हाल - represents an inभागidual test हाल.
 *
 * @run_हाल: the function representing the actual test हाल.
 * @name:     the name of the test हाल.
 * @generate_params: the generator function क्रम parameterized tests.
 *
 * A test हाल is a function with the signature,
 * ``व्योम (*)(काष्ठा kunit *)``
 * that makes expectations and निश्चितions (see KUNIT_EXPECT_TRUE() and
 * KUNIT_ASSERT_TRUE()) about code under test. Each test हाल is associated
 * with a &काष्ठा kunit_suite and will be run after the suite's init
 * function and followed by the suite's निकास function.
 *
 * A test हाल should be अटल and should only be created with the
 * KUNIT_CASE() macro; additionally, every array of test हालs should be
 * terminated with an empty test हाल.
 *
 * Example:
 *
 * .. code-block:: c
 *
 *	व्योम add_test_basic(काष्ठा kunit *test)
 *	अणु
 *		KUNIT_EXPECT_EQ(test, 1, add(1, 0));
 *		KUNIT_EXPECT_EQ(test, 2, add(1, 1));
 *		KUNIT_EXPECT_EQ(test, 0, add(-1, 1));
 *		KUNIT_EXPECT_EQ(test, पूर्णांक_उच्च, add(0, पूर्णांक_उच्च));
 *		KUNIT_EXPECT_EQ(test, -1, add(पूर्णांक_उच्च, पूर्णांक_न्यून));
 *	पूर्ण
 *
 *	अटल काष्ठा kunit_हाल example_test_हालs[] = अणु
 *		KUNIT_CASE(add_test_basic),
 *		अणुपूर्ण
 *	पूर्ण;
 *
 */
काष्ठा kunit_हाल अणु
	व्योम (*run_हाल)(काष्ठा kunit *test);
	स्थिर अक्षर *name;
	स्थिर व्योम* (*generate_params)(स्थिर व्योम *prev, अक्षर *desc);

	/* निजी: पूर्णांकernal use only. */
	bool success;
	अक्षर *log;
पूर्ण;

अटल अंतरभूत अक्षर *kunit_status_to_string(bool status)
अणु
	वापस status ? "ok" : "not ok";
पूर्ण

/**
 * KUNIT_CASE - A helper क्रम creating a &काष्ठा kunit_हाल
 *
 * @test_name: a reference to a test हाल function.
 *
 * Takes a symbol क्रम a function representing a test हाल and creates a
 * &काष्ठा kunit_हाल object from it. See the करोcumentation क्रम
 * &काष्ठा kunit_हाल क्रम an example on how to use it.
 */
#घोषणा KUNIT_CASE(test_name) अणु .run_हाल = test_name, .name = #test_name पूर्ण

/**
 * KUNIT_CASE_PARAM - A helper क्रम creation a parameterized &काष्ठा kunit_हाल
 *
 * @test_name: a reference to a test हाल function.
 * @gen_params: a reference to a parameter generator function.
 *
 * The generator function::
 *
 *	स्थिर व्योम* gen_params(स्थिर व्योम *prev, अक्षर *desc)
 *
 * is used to lazily generate a series of arbitrarily typed values that fit पूर्णांकo
 * a व्योम*. The argument @prev is the previously वापसed value, which should be
 * used to derive the next value; @prev is set to शून्य on the initial generator
 * call. When no more values are available, the generator must वापस शून्य.
 * Optionally ग_लिखो a string पूर्णांकo @desc (size of KUNIT_PARAM_DESC_SIZE)
 * describing the parameter.
 */
#घोषणा KUNIT_CASE_PARAM(test_name, gen_params)			\
		अणु .run_हाल = test_name, .name = #test_name,	\
		  .generate_params = gen_params पूर्ण

/**
 * काष्ठा kunit_suite - describes a related collection of &काष्ठा kunit_हाल
 *
 * @name:	the name of the test. Purely inक्रमmational.
 * @init:	called beक्रमe every test हाल.
 * @निकास:	called after every test हाल.
 * @test_हालs:	a null terminated array of test हालs.
 *
 * A kunit_suite is a collection of related &काष्ठा kunit_हाल s, such that
 * @init is called beक्रमe every test हाल and @निकास is called after every
 * test हाल, similar to the notion of a *test fixture* or a *test class*
 * in other unit testing frameworks like JUnit or Googletest.
 *
 * Every &काष्ठा kunit_हाल must be associated with a kunit_suite क्रम KUnit
 * to run it.
 */
काष्ठा kunit_suite अणु
	स्थिर अक्षर name[256];
	पूर्णांक (*init)(काष्ठा kunit *test);
	व्योम (*निकास)(काष्ठा kunit *test);
	काष्ठा kunit_हाल *test_हालs;

	/* निजी: पूर्णांकernal use only */
	काष्ठा dentry *debugfs;
	अक्षर *log;
पूर्ण;

/**
 * काष्ठा kunit - represents a running instance of a test.
 *
 * @priv: क्रम user to store arbitrary data. Commonly used to pass data
 *	  created in the init function (see &काष्ठा kunit_suite).
 *
 * Used to store inक्रमmation about the current context under which the test
 * is running. Most of this data is निजी and should only be accessed
 * indirectly via खुला functions; the one exception is @priv which can be
 * used by the test ग_लिखोr to store arbitrary data.
 */
काष्ठा kunit अणु
	व्योम *priv;

	/* निजी: पूर्णांकernal use only. */
	स्थिर अक्षर *name; /* Read only after initialization! */
	अक्षर *log; /* Poपूर्णांकs at हाल log after initialization */
	काष्ठा kunit_try_catch try_catch;
	/* param_value is the current parameter value क्रम a test हाल. */
	स्थिर व्योम *param_value;
	/* param_index stores the index of the parameter in parameterized tests. */
	पूर्णांक param_index;
	/*
	 * success starts as true, and may only be set to false during a
	 * test हाल; thus, it is safe to update this across multiple
	 * thपढ़ोs using WRITE_ONCE; however, as a consequence, it may only
	 * be पढ़ो after the test हाल finishes once all thपढ़ोs associated
	 * with the test हाल have terminated.
	 */
	bool success; /* Read only after test_हाल finishes! */
	spinlock_t lock; /* Guards all mutable test state. */
	/*
	 * Because resources is a list that may be updated multiple बार (with
	 * new resources) from any thपढ़ो associated with a test हाल, we must
	 * protect it with some type of lock.
	 */
	काष्ठा list_head resources; /* Protected by lock. */
पूर्ण;

अटल अंतरभूत व्योम kunit_set_failure(काष्ठा kunit *test)
अणु
	WRITE_ONCE(test->success, false);
पूर्ण

व्योम kunit_init_test(काष्ठा kunit *test, स्थिर अक्षर *name, अक्षर *log);

पूर्णांक kunit_run_tests(काष्ठा kunit_suite *suite);

माप_प्रकार kunit_suite_num_test_हालs(काष्ठा kunit_suite *suite);

अचिन्हित पूर्णांक kunit_test_हाल_num(काष्ठा kunit_suite *suite,
				 काष्ठा kunit_हाल *test_हाल);

पूर्णांक __kunit_test_suites_init(काष्ठा kunit_suite * स्थिर * स्थिर suites);

व्योम __kunit_test_suites_निकास(काष्ठा kunit_suite **suites);

#अगर IS_BUILTIN(CONFIG_KUNIT)
पूर्णांक kunit_run_all_tests(व्योम);
#अन्यथा
अटल अंतरभूत पूर्णांक kunit_run_all_tests(व्योम)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर /* IS_BUILTIN(CONFIG_KUNIT) */

#अगर_घोषित MODULE
/**
 * kunit_test_suites_क्रम_module() - used to रेजिस्टर one or more
 *			 &काष्ठा kunit_suite with KUnit.
 *
 * @__suites: a अटलally allocated list of &काष्ठा kunit_suite.
 *
 * Registers @__suites with the test framework. See &काष्ठा kunit_suite क्रम
 * more inक्रमmation.
 *
 * If a test suite is built-in, module_init() माला_लो translated पूर्णांकo
 * an initcall which we करोn't want as the idea is that क्रम builtins
 * the executor will manage execution.  So ensure we करो not define
 * module_अणुinit|निकासपूर्ण functions क्रम the builtin हाल when रेजिस्टरing
 * suites via kunit_test_suites() below.
 */
#घोषणा kunit_test_suites_क्रम_module(__suites)				\
	अटल पूर्णांक __init kunit_test_suites_init(व्योम)			\
	अणु								\
		वापस __kunit_test_suites_init(__suites);		\
	पूर्ण								\
	module_init(kunit_test_suites_init);				\
									\
	अटल व्योम __निकास kunit_test_suites_निकास(व्योम)			\
	अणु								\
		वापस __kunit_test_suites_निकास(__suites);		\
	पूर्ण								\
	module_निकास(kunit_test_suites_निकास)
#अन्यथा
#घोषणा kunit_test_suites_क्रम_module(__suites)
#पूर्ण_अगर /* MODULE */

#घोषणा __kunit_test_suites(unique_array, unique_suites, ...)		       \
	अटल काष्ठा kunit_suite *unique_array[] = अणु __VA_ARGS__, शून्य पूर्ण;     \
	kunit_test_suites_क्रम_module(unique_array);			       \
	अटल काष्ठा kunit_suite **unique_suites			       \
	__used __section(".kunit_test_suites") = unique_array

/**
 * kunit_test_suites() - used to रेजिस्टर one or more &काष्ठा kunit_suite
 *			 with KUnit.
 *
 * @__suites: a अटलally allocated list of &काष्ठा kunit_suite.
 *
 * Registers @suites with the test framework. See &काष्ठा kunit_suite क्रम
 * more inक्रमmation.
 *
 * When builtin,  KUnit tests are all run via executor; this is करोne
 * by placing the array of काष्ठा kunit_suite * in the .kunit_test_suites
 * ELF section.
 *
 * An alternative is to build the tests as a module.  Because modules करो not
 * support multiple initcall()s, we need to initialize an array of suites क्रम a
 * module.
 *
 */
#घोषणा kunit_test_suites(__suites...)						\
	__kunit_test_suites(__UNIQUE_ID(array),				\
			    __UNIQUE_ID(suites),			\
			    ##__suites)

#घोषणा kunit_test_suite(suite)	kunit_test_suites(&suite)

#घोषणा kunit_suite_क्रम_each_test_हाल(suite, test_हाल)		\
	क्रम (test_हाल = suite->test_हालs; test_हाल->run_हाल; test_हाल++)

bool kunit_suite_has_succeeded(काष्ठा kunit_suite *suite);

/*
 * Like kunit_alloc_resource() below, but वापसs the काष्ठा kunit_resource
 * object that contains the allocation. This is mostly क्रम testing purposes.
 */
काष्ठा kunit_resource *kunit_alloc_and_get_resource(काष्ठा kunit *test,
						    kunit_resource_init_t init,
						    kunit_resource_मुक्त_t मुक्त,
						    gfp_t पूर्णांकernal_gfp,
						    व्योम *context);

/**
 * kunit_get_resource() - Hold resource क्रम use.  Should not need to be used
 *			  by most users as we स्वतःmatically get resources
 *			  retrieved by kunit_find_resource*().
 * @res: resource
 */
अटल अंतरभूत व्योम kunit_get_resource(काष्ठा kunit_resource *res)
अणु
	kref_get(&res->refcount);
पूर्ण

/*
 * Called when refcount reaches zero via kunit_put_resources();
 * should not be called directly.
 */
अटल अंतरभूत व्योम kunit_release_resource(काष्ठा kref *kref)
अणु
	काष्ठा kunit_resource *res = container_of(kref, काष्ठा kunit_resource,
						  refcount);

	/* If मुक्त function is defined, resource was dynamically allocated. */
	अगर (res->मुक्त) अणु
		res->मुक्त(res);
		kमुक्त(res);
	पूर्ण
पूर्ण

/**
 * kunit_put_resource() - When caller is करोne with retrieved resource,
 *			  kunit_put_resource() should be called to drop
 *			  reference count.  The resource list मुख्यtains
 *			  a reference count on resources, so अगर no users
 *			  are utilizing a resource and it is हटाओd from
 *			  the resource list, it will be मुक्तd via the
 *			  associated मुक्त function (अगर any).  Only
 *			  needs to be used अगर we alloc_and_get() or
 *			  find() resource.
 * @res: resource
 */
अटल अंतरभूत व्योम kunit_put_resource(काष्ठा kunit_resource *res)
अणु
	kref_put(&res->refcount, kunit_release_resource);
पूर्ण

/**
 * kunit_add_resource() - Add a *test managed resource*.
 * @test: The test context object.
 * @init: a user-supplied function to initialize the result (अगर needed).  If
 *        none is supplied, the resource data value is simply set to @data.
 *	  If an init function is supplied, @data is passed to it instead.
 * @मुक्त: a user-supplied function to मुक्त the resource (अगर needed).
 * @res: The resource.
 * @data: value to pass to init function or set in resource data field.
 */
पूर्णांक kunit_add_resource(काष्ठा kunit *test,
		       kunit_resource_init_t init,
		       kunit_resource_मुक्त_t मुक्त,
		       काष्ठा kunit_resource *res,
		       व्योम *data);

/**
 * kunit_add_named_resource() - Add a named *test managed resource*.
 * @test: The test context object.
 * @init: a user-supplied function to initialize the resource data, अगर needed.
 * @मुक्त: a user-supplied function to मुक्त the resource data, अगर needed.
 * @res: The resource.
 * @name: name to be set क्रम resource.
 * @data: value to pass to init function or set in resource data field.
 */
पूर्णांक kunit_add_named_resource(काष्ठा kunit *test,
			     kunit_resource_init_t init,
			     kunit_resource_मुक्त_t मुक्त,
			     काष्ठा kunit_resource *res,
			     स्थिर अक्षर *name,
			     व्योम *data);

/**
 * kunit_alloc_resource() - Allocates a *test managed resource*.
 * @test: The test context object.
 * @init: a user supplied function to initialize the resource.
 * @मुक्त: a user supplied function to मुक्त the resource.
 * @पूर्णांकernal_gfp: gfp to use क्रम पूर्णांकernal allocations, अगर unsure, use GFP_KERNEL
 * @context: क्रम the user to pass in arbitrary data to the init function.
 *
 * Allocates a *test managed resource*, a resource which will स्वतःmatically be
 * cleaned up at the end of a test हाल. See &काष्ठा kunit_resource क्रम an
 * example.
 *
 * Note: KUnit needs to allocate memory क्रम a kunit_resource object. You must
 * specअगरy an @पूर्णांकernal_gfp that is compatible with the use context of your
 * resource.
 */
अटल अंतरभूत व्योम *kunit_alloc_resource(काष्ठा kunit *test,
					 kunit_resource_init_t init,
					 kunit_resource_मुक्त_t मुक्त,
					 gfp_t पूर्णांकernal_gfp,
					 व्योम *context)
अणु
	काष्ठा kunit_resource *res;

	res = kzalloc(माप(*res), पूर्णांकernal_gfp);
	अगर (!res)
		वापस शून्य;

	अगर (!kunit_add_resource(test, init, मुक्त, res, context))
		वापस res->data;

	वापस शून्य;
पूर्ण

प्रकार bool (*kunit_resource_match_t)(काष्ठा kunit *test,
				       काष्ठा kunit_resource *res,
				       व्योम *match_data);

/**
 * kunit_resource_instance_match() - Match a resource with the same instance.
 * @test: Test हाल to which the resource beदीर्घs.
 * @res: The resource.
 * @match_data: The resource poपूर्णांकer to match against.
 *
 * An instance of kunit_resource_match_t that matches a resource whose
 * allocation matches @match_data.
 */
अटल अंतरभूत bool kunit_resource_instance_match(काष्ठा kunit *test,
						 काष्ठा kunit_resource *res,
						 व्योम *match_data)
अणु
	वापस res->data == match_data;
पूर्ण

/**
 * kunit_resource_name_match() - Match a resource with the same name.
 * @test: Test हाल to which the resource beदीर्घs.
 * @res: The resource.
 * @match_name: The name to match against.
 */
अटल अंतरभूत bool kunit_resource_name_match(काष्ठा kunit *test,
					     काष्ठा kunit_resource *res,
					     व्योम *match_name)
अणु
	वापस res->name && म_भेद(res->name, match_name) == 0;
पूर्ण

/**
 * kunit_find_resource() - Find a resource using match function/data.
 * @test: Test हाल to which the resource beदीर्घs.
 * @match: match function to be applied to resources/match data.
 * @match_data: data to be used in matching.
 */
अटल अंतरभूत काष्ठा kunit_resource *
kunit_find_resource(काष्ठा kunit *test,
		    kunit_resource_match_t match,
		    व्योम *match_data)
अणु
	काष्ठा kunit_resource *res, *found = शून्य;

	spin_lock(&test->lock);

	list_क्रम_each_entry_reverse(res, &test->resources, node) अणु
		अगर (match(test, res, (व्योम *)match_data)) अणु
			found = res;
			kunit_get_resource(found);
			अवरोध;
		पूर्ण
	पूर्ण

	spin_unlock(&test->lock);

	वापस found;
पूर्ण

/**
 * kunit_find_named_resource() - Find a resource using match name.
 * @test: Test हाल to which the resource beदीर्घs.
 * @name: match name.
 */
अटल अंतरभूत काष्ठा kunit_resource *
kunit_find_named_resource(काष्ठा kunit *test,
			  स्थिर अक्षर *name)
अणु
	वापस kunit_find_resource(test, kunit_resource_name_match,
				   (व्योम *)name);
पूर्ण

/**
 * kunit_destroy_resource() - Find a kunit_resource and destroy it.
 * @test: Test हाल to which the resource beदीर्घs.
 * @match: Match function. Returns whether a given resource matches @match_data.
 * @match_data: Data passed पूर्णांकo @match.
 *
 * RETURNS:
 * 0 अगर kunit_resource is found and मुक्तd, -ENOENT अगर not found.
 */
पूर्णांक kunit_destroy_resource(काष्ठा kunit *test,
			   kunit_resource_match_t match,
			   व्योम *match_data);

अटल अंतरभूत पूर्णांक kunit_destroy_named_resource(काष्ठा kunit *test,
					       स्थिर अक्षर *name)
अणु
	वापस kunit_destroy_resource(test, kunit_resource_name_match,
				      (व्योम *)name);
पूर्ण

/**
 * kunit_हटाओ_resource() - हटाओ resource from resource list associated with
 *			     test.
 * @test: The test context object.
 * @res: The resource to be हटाओd.
 *
 * Note that the resource will not be immediately मुक्तd since it is likely
 * the caller has a reference to it via alloc_and_get() or find();
 * in this हाल a final call to kunit_put_resource() is required.
 */
व्योम kunit_हटाओ_resource(काष्ठा kunit *test, काष्ठा kunit_resource *res);

/**
 * kunit_kदो_स्मृति() - Like kदो_स्मृति() except the allocation is *test managed*.
 * @test: The test context object.
 * @size: The size in bytes of the desired memory.
 * @gfp: flags passed to underlying kदो_स्मृति().
 *
 * Just like `kदो_स्मृति(...)`, except the allocation is managed by the test हाल
 * and is स्वतःmatically cleaned up after the test हाल concludes. See &काष्ठा
 * kunit_resource क्रम more inक्रमmation.
 */
व्योम *kunit_kदो_स्मृति(काष्ठा kunit *test, माप_प्रकार size, gfp_t gfp);

/**
 * kunit_kमुक्त() - Like kमुक्त except क्रम allocations managed by KUnit.
 * @test: The test हाल to which the resource beदीर्घs.
 * @ptr: The memory allocation to मुक्त.
 */
व्योम kunit_kमुक्त(काष्ठा kunit *test, स्थिर व्योम *ptr);

/**
 * kunit_kzalloc() - Just like kunit_kदो_स्मृति(), but zeroes the allocation.
 * @test: The test context object.
 * @size: The size in bytes of the desired memory.
 * @gfp: flags passed to underlying kदो_स्मृति().
 *
 * See kzalloc() and kunit_kदो_स्मृति() क्रम more inक्रमmation.
 */
अटल अंतरभूत व्योम *kunit_kzalloc(काष्ठा kunit *test, माप_प्रकार size, gfp_t gfp)
अणु
	वापस kunit_kदो_स्मृति(test, size, gfp | __GFP_ZERO);
पूर्ण

व्योम kunit_cleanup(काष्ठा kunit *test);

व्योम kunit_log_append(अक्षर *log, स्थिर अक्षर *fmt, ...);

/*
 * prपूर्णांकk and log to per-test or per-suite log buffer.  Logging only करोne
 * अगर CONFIG_KUNIT_DEBUGFS is 'y'; if it is 'n', no log is allocated/used.
 */
#घोषणा kunit_log(lvl, test_or_suite, fmt, ...)				\
	करो अणु								\
		prपूर्णांकk(lvl fmt, ##__VA_ARGS__);				\
		kunit_log_append((test_or_suite)->log,	fmt "\n",	\
				 ##__VA_ARGS__);			\
	पूर्ण जबतक (0)

#घोषणा kunit_prपूर्णांकk(lvl, test, fmt, ...)				\
	kunit_log(lvl, test, KUNIT_SUBTEST_INDENT "# %s: " fmt,		\
		  (test)->name,	##__VA_ARGS__)

/**
 * kunit_info() - Prपूर्णांकs an INFO level message associated with @test.
 *
 * @test: The test context object.
 * @fmt:  A prपूर्णांकk() style क्रमmat string.
 *
 * Prपूर्णांकs an info level message associated with the test suite being run.
 * Takes a variable number of क्रमmat parameters just like prपूर्णांकk().
 */
#घोषणा kunit_info(test, fmt, ...) \
	kunit_prपूर्णांकk(KERN_INFO, test, fmt, ##__VA_ARGS__)

/**
 * kunit_warn() - Prपूर्णांकs a WARN level message associated with @test.
 *
 * @test: The test context object.
 * @fmt:  A prपूर्णांकk() style क्रमmat string.
 *
 * Prपूर्णांकs a warning level message.
 */
#घोषणा kunit_warn(test, fmt, ...) \
	kunit_prपूर्णांकk(KERN_WARNING, test, fmt, ##__VA_ARGS__)

/**
 * kunit_err() - Prपूर्णांकs an ERROR level message associated with @test.
 *
 * @test: The test context object.
 * @fmt:  A prपूर्णांकk() style क्रमmat string.
 *
 * Prपूर्णांकs an error level message.
 */
#घोषणा kunit_err(test, fmt, ...) \
	kunit_prपूर्णांकk(KERN_ERR, test, fmt, ##__VA_ARGS__)

/**
 * KUNIT_SUCCEED() - A no-op expectation. Only exists क्रम code clarity.
 * @test: The test context object.
 *
 * The opposite of KUNIT_FAIL(), it is an expectation that cannot fail. In other
 * words, it करोes nothing and only exists क्रम code clarity. See
 * KUNIT_EXPECT_TRUE() क्रम more inक्रमmation.
 */
#घोषणा KUNIT_SUCCEED(test) करो अणुपूर्ण जबतक (0)

व्योम kunit_करो_निश्चितion(काष्ठा kunit *test,
			काष्ठा kunit_निश्चित *निश्चित,
			bool pass,
			स्थिर अक्षर *fmt, ...);

#घोषणा KUNIT_ASSERTION(test, pass, निश्चित_class, INITIALIZER, fmt, ...) करो अणु  \
	काष्ठा निश्चित_class __निश्चितion = INITIALIZER;			       \
	kunit_करो_निश्चितion(test,					       \
			   &__निश्चितion.निश्चित,				       \
			   pass,					       \
			   fmt,						       \
			   ##__VA_ARGS__);				       \
पूर्ण जबतक (0)


#घोषणा KUNIT_FAIL_ASSERTION(test, निश्चित_type, fmt, ...)		       \
	KUNIT_ASSERTION(test,						       \
			false,						       \
			kunit_fail_निश्चित,				       \
			KUNIT_INIT_FAIL_ASSERT_STRUCT(test, निश्चित_type),      \
			fmt,						       \
			##__VA_ARGS__)

/**
 * KUNIT_FAIL() - Always causes a test to fail when evaluated.
 * @test: The test context object.
 * @fmt: an inक्रमmational message to be prपूर्णांकed when the निश्चितion is made.
 * @...: string क्रमmat arguments.
 *
 * The opposite of KUNIT_SUCCEED(), it is an expectation that always fails. In
 * other words, it always results in a failed expectation, and consequently
 * always causes the test हाल to fail when evaluated. See KUNIT_EXPECT_TRUE()
 * क्रम more inक्रमmation.
 */
#घोषणा KUNIT_FAIL(test, fmt, ...)					       \
	KUNIT_FAIL_ASSERTION(test,					       \
			     KUNIT_EXPECTATION,				       \
			     fmt,					       \
			     ##__VA_ARGS__)

#घोषणा KUNIT_UNARY_ASSERTION(test,					       \
			      निश्चित_type,				       \
			      condition,				       \
			      expected_true,				       \
			      fmt,					       \
			      ...)					       \
	KUNIT_ASSERTION(test,						       \
			!!(condition) == !!expected_true,		       \
			kunit_unary_निश्चित,				       \
			KUNIT_INIT_UNARY_ASSERT_STRUCT(test,		       \
						       निश्चित_type,	       \
						       #condition,	       \
						       expected_true),	       \
			fmt,						       \
			##__VA_ARGS__)

#घोषणा KUNIT_TRUE_MSG_ASSERTION(test, निश्चित_type, condition, fmt, ...)       \
	KUNIT_UNARY_ASSERTION(test,					       \
			      निश्चित_type,				       \
			      condition,				       \
			      true,					       \
			      fmt,					       \
			      ##__VA_ARGS__)

#घोषणा KUNIT_TRUE_ASSERTION(test, निश्चित_type, condition) \
	KUNIT_TRUE_MSG_ASSERTION(test, निश्चित_type, condition, शून्य)

#घोषणा KUNIT_FALSE_MSG_ASSERTION(test, निश्चित_type, condition, fmt, ...)      \
	KUNIT_UNARY_ASSERTION(test,					       \
			      निश्चित_type,				       \
			      condition,				       \
			      false,					       \
			      fmt,					       \
			      ##__VA_ARGS__)

#घोषणा KUNIT_FALSE_ASSERTION(test, निश्चित_type, condition) \
	KUNIT_FALSE_MSG_ASSERTION(test, निश्चित_type, condition, शून्य)

/*
 * A factory macro क्रम defining the निश्चितions and expectations क्रम the basic
 * comparisons defined क्रम the built in types.
 *
 * Unक्रमtunately, there is no common type that all types can be promoted to क्रम
 * which all the binary चालकs behave the same way as क्रम the actual types
 * (क्रम example, there is no type that दीर्घ दीर्घ and अचिन्हित दीर्घ दीर्घ can
 * both be cast to where the comparison result is preserved क्रम all values). So
 * the best we can करो is करो the comparison in the original types and then coerce
 * everything to दीर्घ दीर्घ क्रम prपूर्णांकing; this way, the comparison behaves
 * correctly and the prपूर्णांकed out value usually makes sense without
 * पूर्णांकerpretation, but can always be पूर्णांकerpreted to figure out the actual
 * value.
 */
#घोषणा KUNIT_BASE_BINARY_ASSERTION(test,				       \
				    निश्चित_class,			       \
				    ASSERT_CLASS_INIT,			       \
				    निश्चित_type,			       \
				    left,				       \
				    op,					       \
				    right,				       \
				    fmt,				       \
				    ...)				       \
करो अणु									       \
	typeof(left) __left = (left);					       \
	typeof(right) __right = (right);				       \
	((व्योम)__typecheck(__left, __right));				       \
									       \
	KUNIT_ASSERTION(test,						       \
			__left op __right,				       \
			निश्चित_class,					       \
			ASSERT_CLASS_INIT(test,				       \
					  निश्चित_type,			       \
					  #op,				       \
					  #left,			       \
					  __left,			       \
					  #right,			       \
					  __right),			       \
			fmt,						       \
			##__VA_ARGS__);					       \
पूर्ण जबतक (0)

#घोषणा KUNIT_BASE_EQ_MSG_ASSERTION(test,				       \
				    निश्चित_class,			       \
				    ASSERT_CLASS_INIT,			       \
				    निश्चित_type,			       \
				    left,				       \
				    right,				       \
				    fmt,				       \
				    ...)				       \
	KUNIT_BASE_BINARY_ASSERTION(test,				       \
				    निश्चित_class,			       \
				    ASSERT_CLASS_INIT,			       \
				    निश्चित_type,			       \
				    left, ==, right,			       \
				    fmt,				       \
				    ##__VA_ARGS__)

#घोषणा KUNIT_BASE_NE_MSG_ASSERTION(test,				       \
				    निश्चित_class,			       \
				    ASSERT_CLASS_INIT,			       \
				    निश्चित_type,			       \
				    left,				       \
				    right,				       \
				    fmt,				       \
				    ...)				       \
	KUNIT_BASE_BINARY_ASSERTION(test,				       \
				    निश्चित_class,			       \
				    ASSERT_CLASS_INIT,			       \
				    निश्चित_type,			       \
				    left, !=, right,			       \
				    fmt,				       \
				    ##__VA_ARGS__)

#घोषणा KUNIT_BASE_LT_MSG_ASSERTION(test,				       \
				    निश्चित_class,			       \
				    ASSERT_CLASS_INIT,			       \
				    निश्चित_type,			       \
				    left,				       \
				    right,				       \
				    fmt,				       \
				    ...)				       \
	KUNIT_BASE_BINARY_ASSERTION(test,				       \
				    निश्चित_class,			       \
				    ASSERT_CLASS_INIT,			       \
				    निश्चित_type,			       \
				    left, <, right,			       \
				    fmt,				       \
				    ##__VA_ARGS__)

#घोषणा KUNIT_BASE_LE_MSG_ASSERTION(test,				       \
				    निश्चित_class,			       \
				    ASSERT_CLASS_INIT,			       \
				    निश्चित_type,			       \
				    left,				       \
				    right,				       \
				    fmt,				       \
				    ...)				       \
	KUNIT_BASE_BINARY_ASSERTION(test,				       \
				    निश्चित_class,			       \
				    ASSERT_CLASS_INIT,			       \
				    निश्चित_type,			       \
				    left, <=, right,			       \
				    fmt,				       \
				    ##__VA_ARGS__)

#घोषणा KUNIT_BASE_GT_MSG_ASSERTION(test,				       \
				    निश्चित_class,			       \
				    ASSERT_CLASS_INIT,			       \
				    निश्चित_type,			       \
				    left,				       \
				    right,				       \
				    fmt,				       \
				    ...)				       \
	KUNIT_BASE_BINARY_ASSERTION(test,				       \
				    निश्चित_class,			       \
				    ASSERT_CLASS_INIT,			       \
				    निश्चित_type,			       \
				    left, >, right,			       \
				    fmt,				       \
				    ##__VA_ARGS__)

#घोषणा KUNIT_BASE_GE_MSG_ASSERTION(test,				       \
				    निश्चित_class,			       \
				    ASSERT_CLASS_INIT,			       \
				    निश्चित_type,			       \
				    left,				       \
				    right,				       \
				    fmt,				       \
				    ...)				       \
	KUNIT_BASE_BINARY_ASSERTION(test,				       \
				    निश्चित_class,			       \
				    ASSERT_CLASS_INIT,			       \
				    निश्चित_type,			       \
				    left, >=, right,			       \
				    fmt,				       \
				    ##__VA_ARGS__)

#घोषणा KUNIT_BINARY_EQ_MSG_ASSERTION(test, निश्चित_type, left, right, fmt, ...)\
	KUNIT_BASE_EQ_MSG_ASSERTION(test,				       \
				    kunit_binary_निश्चित,		       \
				    KUNIT_INIT_BINARY_ASSERT_STRUCT,	       \
				    निश्चित_type,			       \
				    left,				       \
				    right,				       \
				    fmt,				       \
				    ##__VA_ARGS__)

#घोषणा KUNIT_BINARY_EQ_ASSERTION(test, निश्चित_type, left, right)	       \
	KUNIT_BINARY_EQ_MSG_ASSERTION(test,				       \
				      निश्चित_type,			       \
				      left,				       \
				      right,				       \
				      शून्य)

#घोषणा KUNIT_BINARY_PTR_EQ_MSG_ASSERTION(test,				       \
					  निश्चित_type,			       \
					  left,				       \
					  right,			       \
					  fmt,				       \
					  ...)				       \
	KUNIT_BASE_EQ_MSG_ASSERTION(test,				       \
				    kunit_binary_ptr_निश्चित,		       \
				    KUNIT_INIT_BINARY_PTR_ASSERT_STRUCT,       \
				    निश्चित_type,			       \
				    left,				       \
				    right,				       \
				    fmt,				       \
				    ##__VA_ARGS__)

#घोषणा KUNIT_BINARY_PTR_EQ_ASSERTION(test, निश्चित_type, left, right)	       \
	KUNIT_BINARY_PTR_EQ_MSG_ASSERTION(test,				       \
					  निश्चित_type,			       \
					  left,				       \
					  right,			       \
					  शून्य)

#घोषणा KUNIT_BINARY_NE_MSG_ASSERTION(test, निश्चित_type, left, right, fmt, ...)\
	KUNIT_BASE_NE_MSG_ASSERTION(test,				       \
				    kunit_binary_निश्चित,		       \
				    KUNIT_INIT_BINARY_ASSERT_STRUCT,	       \
				    निश्चित_type,			       \
				    left,				       \
				    right,				       \
				    fmt,				       \
				    ##__VA_ARGS__)

#घोषणा KUNIT_BINARY_NE_ASSERTION(test, निश्चित_type, left, right)	       \
	KUNIT_BINARY_NE_MSG_ASSERTION(test,				       \
				      निश्चित_type,			       \
				      left,				       \
				      right,				       \
				      शून्य)

#घोषणा KUNIT_BINARY_PTR_NE_MSG_ASSERTION(test,				       \
					  निश्चित_type,			       \
					  left,				       \
					  right,			       \
					  fmt,				       \
					  ...)				       \
	KUNIT_BASE_NE_MSG_ASSERTION(test,				       \
				    kunit_binary_ptr_निश्चित,		       \
				    KUNIT_INIT_BINARY_PTR_ASSERT_STRUCT,       \
				    निश्चित_type,			       \
				    left,				       \
				    right,				       \
				    fmt,				       \
				    ##__VA_ARGS__)

#घोषणा KUNIT_BINARY_PTR_NE_ASSERTION(test, निश्चित_type, left, right)	       \
	KUNIT_BINARY_PTR_NE_MSG_ASSERTION(test,				       \
					  निश्चित_type,			       \
					  left,				       \
					  right,			       \
					  शून्य)

#घोषणा KUNIT_BINARY_LT_MSG_ASSERTION(test, निश्चित_type, left, right, fmt, ...)\
	KUNIT_BASE_LT_MSG_ASSERTION(test,				       \
				    kunit_binary_निश्चित,		       \
				    KUNIT_INIT_BINARY_ASSERT_STRUCT,	       \
				    निश्चित_type,			       \
				    left,				       \
				    right,				       \
				    fmt,				       \
				    ##__VA_ARGS__)

#घोषणा KUNIT_BINARY_LT_ASSERTION(test, निश्चित_type, left, right)	       \
	KUNIT_BINARY_LT_MSG_ASSERTION(test,				       \
				      निश्चित_type,			       \
				      left,				       \
				      right,				       \
				      शून्य)

#घोषणा KUNIT_BINARY_PTR_LT_MSG_ASSERTION(test,				       \
					  निश्चित_type,			       \
					  left,				       \
					  right,			       \
					  fmt,				       \
					  ...)				       \
	KUNIT_BASE_LT_MSG_ASSERTION(test,				       \
				    kunit_binary_ptr_निश्चित,		       \
				    KUNIT_INIT_BINARY_PTR_ASSERT_STRUCT,       \
				    निश्चित_type,			       \
				    left,				       \
				    right,				       \
				    fmt,				       \
				    ##__VA_ARGS__)

#घोषणा KUNIT_BINARY_PTR_LT_ASSERTION(test, निश्चित_type, left, right)	       \
	KUNIT_BINARY_PTR_LT_MSG_ASSERTION(test,				       \
					  निश्चित_type,			       \
					  left,				       \
					  right,			       \
					  शून्य)

#घोषणा KUNIT_BINARY_LE_MSG_ASSERTION(test, निश्चित_type, left, right, fmt, ...)\
	KUNIT_BASE_LE_MSG_ASSERTION(test,				       \
				    kunit_binary_निश्चित,		       \
				    KUNIT_INIT_BINARY_ASSERT_STRUCT,	       \
				    निश्चित_type,			       \
				    left,				       \
				    right,				       \
				    fmt,				       \
				    ##__VA_ARGS__)

#घोषणा KUNIT_BINARY_LE_ASSERTION(test, निश्चित_type, left, right)	       \
	KUNIT_BINARY_LE_MSG_ASSERTION(test,				       \
				      निश्चित_type,			       \
				      left,				       \
				      right,				       \
				      शून्य)

#घोषणा KUNIT_BINARY_PTR_LE_MSG_ASSERTION(test,				       \
					  निश्चित_type,			       \
					  left,				       \
					  right,			       \
					  fmt,				       \
					  ...)				       \
	KUNIT_BASE_LE_MSG_ASSERTION(test,				       \
				    kunit_binary_ptr_निश्चित,		       \
				    KUNIT_INIT_BINARY_PTR_ASSERT_STRUCT,       \
				    निश्चित_type,			       \
				    left,				       \
				    right,				       \
				    fmt,				       \
				    ##__VA_ARGS__)

#घोषणा KUNIT_BINARY_PTR_LE_ASSERTION(test, निश्चित_type, left, right)	       \
	KUNIT_BINARY_PTR_LE_MSG_ASSERTION(test,				       \
					  निश्चित_type,			       \
					  left,				       \
					  right,			       \
					  शून्य)

#घोषणा KUNIT_BINARY_GT_MSG_ASSERTION(test, निश्चित_type, left, right, fmt, ...)\
	KUNIT_BASE_GT_MSG_ASSERTION(test,				       \
				    kunit_binary_निश्चित,		       \
				    KUNIT_INIT_BINARY_ASSERT_STRUCT,	       \
				    निश्चित_type,			       \
				    left,				       \
				    right,				       \
				    fmt,				       \
				    ##__VA_ARGS__)

#घोषणा KUNIT_BINARY_GT_ASSERTION(test, निश्चित_type, left, right)	       \
	KUNIT_BINARY_GT_MSG_ASSERTION(test,				       \
				      निश्चित_type,			       \
				      left,				       \
				      right,				       \
				      शून्य)

#घोषणा KUNIT_BINARY_PTR_GT_MSG_ASSERTION(test,				       \
					  निश्चित_type,			       \
					  left,				       \
					  right,			       \
					  fmt,				       \
					  ...)				       \
	KUNIT_BASE_GT_MSG_ASSERTION(test,				       \
				    kunit_binary_ptr_निश्चित,		       \
				    KUNIT_INIT_BINARY_PTR_ASSERT_STRUCT,       \
				    निश्चित_type,			       \
				    left,				       \
				    right,				       \
				    fmt,				       \
				    ##__VA_ARGS__)

#घोषणा KUNIT_BINARY_PTR_GT_ASSERTION(test, निश्चित_type, left, right)	       \
	KUNIT_BINARY_PTR_GT_MSG_ASSERTION(test,				       \
					  निश्चित_type,			       \
					  left,				       \
					  right,			       \
					  शून्य)

#घोषणा KUNIT_BINARY_GE_MSG_ASSERTION(test, निश्चित_type, left, right, fmt, ...)\
	KUNIT_BASE_GE_MSG_ASSERTION(test,				       \
				    kunit_binary_निश्चित,		       \
				    KUNIT_INIT_BINARY_ASSERT_STRUCT,	       \
				    निश्चित_type,			       \
				    left,				       \
				    right,				       \
				    fmt,				       \
				    ##__VA_ARGS__)

#घोषणा KUNIT_BINARY_GE_ASSERTION(test, निश्चित_type, left, right)	       \
	KUNIT_BINARY_GE_MSG_ASSERTION(test,				       \
				      निश्चित_type,			       \
				      left,				       \
				      right,				       \
				      शून्य)

#घोषणा KUNIT_BINARY_PTR_GE_MSG_ASSERTION(test,				       \
					  निश्चित_type,			       \
					  left,				       \
					  right,			       \
					  fmt,				       \
					  ...)				       \
	KUNIT_BASE_GE_MSG_ASSERTION(test,				       \
				    kunit_binary_ptr_निश्चित,		       \
				    KUNIT_INIT_BINARY_PTR_ASSERT_STRUCT,       \
				    निश्चित_type,			       \
				    left,				       \
				    right,				       \
				    fmt,				       \
				    ##__VA_ARGS__)

#घोषणा KUNIT_BINARY_PTR_GE_ASSERTION(test, निश्चित_type, left, right)	       \
	KUNIT_BINARY_PTR_GE_MSG_ASSERTION(test,				       \
					  निश्चित_type,			       \
					  left,				       \
					  right,			       \
					  शून्य)

#घोषणा KUNIT_BINARY_STR_ASSERTION(test,				       \
				   निश्चित_type,				       \
				   left,				       \
				   op,					       \
				   right,				       \
				   fmt,					       \
				   ...)					       \
करो अणु									       \
	typeof(left) __left = (left);					       \
	typeof(right) __right = (right);				       \
									       \
	KUNIT_ASSERTION(test,						       \
			म_भेद(__left, __right) op 0,			       \
			kunit_binary_str_निश्चित,			       \
			KUNIT_INIT_BINARY_STR_ASSERT_STRUCT(test,	       \
							निश्चित_type,	       \
							#op,		       \
							#left,		       \
							__left,		       \
							#right,		       \
							__right),	       \
			fmt,						       \
			##__VA_ARGS__);					       \
पूर्ण जबतक (0)

#घोषणा KUNIT_BINARY_STR_EQ_MSG_ASSERTION(test,				       \
					  निश्चित_type,			       \
					  left,				       \
					  right,			       \
					  fmt,				       \
					  ...)				       \
	KUNIT_BINARY_STR_ASSERTION(test,				       \
				   निश्चित_type,				       \
				   left, ==, right,			       \
				   fmt,					       \
				   ##__VA_ARGS__)

#घोषणा KUNIT_BINARY_STR_EQ_ASSERTION(test, निश्चित_type, left, right)	       \
	KUNIT_BINARY_STR_EQ_MSG_ASSERTION(test,				       \
					  निश्चित_type,			       \
					  left,				       \
					  right,			       \
					  शून्य)

#घोषणा KUNIT_BINARY_STR_NE_MSG_ASSERTION(test,				       \
					  निश्चित_type,			       \
					  left,				       \
					  right,			       \
					  fmt,				       \
					  ...)				       \
	KUNIT_BINARY_STR_ASSERTION(test,				       \
				   निश्चित_type,				       \
				   left, !=, right,			       \
				   fmt,					       \
				   ##__VA_ARGS__)

#घोषणा KUNIT_BINARY_STR_NE_ASSERTION(test, निश्चित_type, left, right)	       \
	KUNIT_BINARY_STR_NE_MSG_ASSERTION(test,				       \
					  निश्चित_type,			       \
					  left,				       \
					  right,			       \
					  शून्य)

#घोषणा KUNIT_PTR_NOT_ERR_OR_शून्य_MSG_ASSERTION(test,			       \
						निश्चित_type,		       \
						ptr,			       \
						fmt,			       \
						...)			       \
करो अणु									       \
	typeof(ptr) __ptr = (ptr);					       \
									       \
	KUNIT_ASSERTION(test,						       \
			!IS_ERR_OR_शून्य(__ptr),				       \
			kunit_ptr_not_err_निश्चित,			       \
			KUNIT_INIT_PTR_NOT_ERR_STRUCT(test,		       \
						      निश्चित_type,	       \
						      #ptr,		       \
						      __ptr),		       \
			fmt,						       \
			##__VA_ARGS__);					       \
पूर्ण जबतक (0)

#घोषणा KUNIT_PTR_NOT_ERR_OR_शून्य_ASSERTION(test, निश्चित_type, ptr)	       \
	KUNIT_PTR_NOT_ERR_OR_शून्य_MSG_ASSERTION(test,			       \
						निश्चित_type,		       \
						ptr,			       \
						शून्य)

/**
 * KUNIT_EXPECT_TRUE() - Causes a test failure when the expression is not true.
 * @test: The test context object.
 * @condition: an arbitrary boolean expression. The test fails when this करोes
 * not evaluate to true.
 *
 * This and expectations of the क्रमm `KUNIT_EXPECT_*` will cause the test हाल
 * to fail when the specअगरied condition is not met; however, it will not prevent
 * the test हाल from continuing to run; this is otherwise known as an
 * *expectation failure*.
 */
#घोषणा KUNIT_EXPECT_TRUE(test, condition) \
	KUNIT_TRUE_ASSERTION(test, KUNIT_EXPECTATION, condition)

#घोषणा KUNIT_EXPECT_TRUE_MSG(test, condition, fmt, ...)		       \
	KUNIT_TRUE_MSG_ASSERTION(test,					       \
				 KUNIT_EXPECTATION,			       \
				 condition,				       \
				 fmt,					       \
				 ##__VA_ARGS__)

/**
 * KUNIT_EXPECT_FALSE() - Makes a test failure when the expression is not false.
 * @test: The test context object.
 * @condition: an arbitrary boolean expression. The test fails when this करोes
 * not evaluate to false.
 *
 * Sets an expectation that @condition evaluates to false. See
 * KUNIT_EXPECT_TRUE() क्रम more inक्रमmation.
 */
#घोषणा KUNIT_EXPECT_FALSE(test, condition) \
	KUNIT_FALSE_ASSERTION(test, KUNIT_EXPECTATION, condition)

#घोषणा KUNIT_EXPECT_FALSE_MSG(test, condition, fmt, ...)		       \
	KUNIT_FALSE_MSG_ASSERTION(test,					       \
				  KUNIT_EXPECTATION,			       \
				  condition,				       \
				  fmt,					       \
				  ##__VA_ARGS__)

/**
 * KUNIT_EXPECT_EQ() - Sets an expectation that @left and @right are equal.
 * @test: The test context object.
 * @left: an arbitrary expression that evaluates to a primitive C type.
 * @right: an arbitrary expression that evaluates to a primitive C type.
 *
 * Sets an expectation that the values that @left and @right evaluate to are
 * equal. This is semantically equivalent to
 * KUNIT_EXPECT_TRUE(@test, (@left) == (@right)). See KUNIT_EXPECT_TRUE() क्रम
 * more inक्रमmation.
 */
#घोषणा KUNIT_EXPECT_EQ(test, left, right) \
	KUNIT_BINARY_EQ_ASSERTION(test, KUNIT_EXPECTATION, left, right)

#घोषणा KUNIT_EXPECT_EQ_MSG(test, left, right, fmt, ...)		       \
	KUNIT_BINARY_EQ_MSG_ASSERTION(test,				       \
				      KUNIT_EXPECTATION,		       \
				      left,				       \
				      right,				       \
				      fmt,				       \
				      ##__VA_ARGS__)

/**
 * KUNIT_EXPECT_PTR_EQ() - Expects that poपूर्णांकers @left and @right are equal.
 * @test: The test context object.
 * @left: an arbitrary expression that evaluates to a poपूर्णांकer.
 * @right: an arbitrary expression that evaluates to a poपूर्णांकer.
 *
 * Sets an expectation that the values that @left and @right evaluate to are
 * equal. This is semantically equivalent to
 * KUNIT_EXPECT_TRUE(@test, (@left) == (@right)). See KUNIT_EXPECT_TRUE() क्रम
 * more inक्रमmation.
 */
#घोषणा KUNIT_EXPECT_PTR_EQ(test, left, right)				       \
	KUNIT_BINARY_PTR_EQ_ASSERTION(test,				       \
				      KUNIT_EXPECTATION,		       \
				      left,				       \
				      right)

#घोषणा KUNIT_EXPECT_PTR_EQ_MSG(test, left, right, fmt, ...)		       \
	KUNIT_BINARY_PTR_EQ_MSG_ASSERTION(test,				       \
					  KUNIT_EXPECTATION,		       \
					  left,				       \
					  right,			       \
					  fmt,				       \
					  ##__VA_ARGS__)

/**
 * KUNIT_EXPECT_NE() - An expectation that @left and @right are not equal.
 * @test: The test context object.
 * @left: an arbitrary expression that evaluates to a primitive C type.
 * @right: an arbitrary expression that evaluates to a primitive C type.
 *
 * Sets an expectation that the values that @left and @right evaluate to are not
 * equal. This is semantically equivalent to
 * KUNIT_EXPECT_TRUE(@test, (@left) != (@right)). See KUNIT_EXPECT_TRUE() क्रम
 * more inक्रमmation.
 */
#घोषणा KUNIT_EXPECT_NE(test, left, right) \
	KUNIT_BINARY_NE_ASSERTION(test, KUNIT_EXPECTATION, left, right)

#घोषणा KUNIT_EXPECT_NE_MSG(test, left, right, fmt, ...)		       \
	KUNIT_BINARY_NE_MSG_ASSERTION(test,				       \
				      KUNIT_EXPECTATION,		       \
				      left,				       \
				      right,				       \
				      fmt,				       \
				      ##__VA_ARGS__)

/**
 * KUNIT_EXPECT_PTR_NE() - Expects that poपूर्णांकers @left and @right are not equal.
 * @test: The test context object.
 * @left: an arbitrary expression that evaluates to a poपूर्णांकer.
 * @right: an arbitrary expression that evaluates to a poपूर्णांकer.
 *
 * Sets an expectation that the values that @left and @right evaluate to are not
 * equal. This is semantically equivalent to
 * KUNIT_EXPECT_TRUE(@test, (@left) != (@right)). See KUNIT_EXPECT_TRUE() क्रम
 * more inक्रमmation.
 */
#घोषणा KUNIT_EXPECT_PTR_NE(test, left, right)				       \
	KUNIT_BINARY_PTR_NE_ASSERTION(test,				       \
				      KUNIT_EXPECTATION,		       \
				      left,				       \
				      right)

#घोषणा KUNIT_EXPECT_PTR_NE_MSG(test, left, right, fmt, ...)		       \
	KUNIT_BINARY_PTR_NE_MSG_ASSERTION(test,				       \
					  KUNIT_EXPECTATION,		       \
					  left,				       \
					  right,			       \
					  fmt,				       \
					  ##__VA_ARGS__)

/**
 * KUNIT_EXPECT_LT() - An expectation that @left is less than @right.
 * @test: The test context object.
 * @left: an arbitrary expression that evaluates to a primitive C type.
 * @right: an arbitrary expression that evaluates to a primitive C type.
 *
 * Sets an expectation that the value that @left evaluates to is less than the
 * value that @right evaluates to. This is semantically equivalent to
 * KUNIT_EXPECT_TRUE(@test, (@left) < (@right)). See KUNIT_EXPECT_TRUE() क्रम
 * more inक्रमmation.
 */
#घोषणा KUNIT_EXPECT_LT(test, left, right) \
	KUNIT_BINARY_LT_ASSERTION(test, KUNIT_EXPECTATION, left, right)

#घोषणा KUNIT_EXPECT_LT_MSG(test, left, right, fmt, ...)		       \
	KUNIT_BINARY_LT_MSG_ASSERTION(test,				       \
				      KUNIT_EXPECTATION,		       \
				      left,				       \
				      right,				       \
				      fmt,				       \
				      ##__VA_ARGS__)

/**
 * KUNIT_EXPECT_LE() - Expects that @left is less than or equal to @right.
 * @test: The test context object.
 * @left: an arbitrary expression that evaluates to a primitive C type.
 * @right: an arbitrary expression that evaluates to a primitive C type.
 *
 * Sets an expectation that the value that @left evaluates to is less than or
 * equal to the value that @right evaluates to. Semantically this is equivalent
 * to KUNIT_EXPECT_TRUE(@test, (@left) <= (@right)). See KUNIT_EXPECT_TRUE() क्रम
 * more inक्रमmation.
 */
#घोषणा KUNIT_EXPECT_LE(test, left, right) \
	KUNIT_BINARY_LE_ASSERTION(test, KUNIT_EXPECTATION, left, right)

#घोषणा KUNIT_EXPECT_LE_MSG(test, left, right, fmt, ...)		       \
	KUNIT_BINARY_LE_MSG_ASSERTION(test,				       \
				      KUNIT_EXPECTATION,		       \
				      left,				       \
				      right,				       \
				      fmt,				       \
				      ##__VA_ARGS__)

/**
 * KUNIT_EXPECT_GT() - An expectation that @left is greater than @right.
 * @test: The test context object.
 * @left: an arbitrary expression that evaluates to a primitive C type.
 * @right: an arbitrary expression that evaluates to a primitive C type.
 *
 * Sets an expectation that the value that @left evaluates to is greater than
 * the value that @right evaluates to. This is semantically equivalent to
 * KUNIT_EXPECT_TRUE(@test, (@left) > (@right)). See KUNIT_EXPECT_TRUE() क्रम
 * more inक्रमmation.
 */
#घोषणा KUNIT_EXPECT_GT(test, left, right) \
	KUNIT_BINARY_GT_ASSERTION(test, KUNIT_EXPECTATION, left, right)

#घोषणा KUNIT_EXPECT_GT_MSG(test, left, right, fmt, ...)		       \
	KUNIT_BINARY_GT_MSG_ASSERTION(test,				       \
				      KUNIT_EXPECTATION,		       \
				      left,				       \
				      right,				       \
				      fmt,				       \
				      ##__VA_ARGS__)

/**
 * KUNIT_EXPECT_GE() - Expects that @left is greater than or equal to @right.
 * @test: The test context object.
 * @left: an arbitrary expression that evaluates to a primitive C type.
 * @right: an arbitrary expression that evaluates to a primitive C type.
 *
 * Sets an expectation that the value that @left evaluates to is greater than
 * the value that @right evaluates to. This is semantically equivalent to
 * KUNIT_EXPECT_TRUE(@test, (@left) >= (@right)). See KUNIT_EXPECT_TRUE() क्रम
 * more inक्रमmation.
 */
#घोषणा KUNIT_EXPECT_GE(test, left, right) \
	KUNIT_BINARY_GE_ASSERTION(test, KUNIT_EXPECTATION, left, right)

#घोषणा KUNIT_EXPECT_GE_MSG(test, left, right, fmt, ...)		       \
	KUNIT_BINARY_GE_MSG_ASSERTION(test,				       \
				      KUNIT_EXPECTATION,		       \
				      left,				       \
				      right,				       \
				      fmt,				       \
				      ##__VA_ARGS__)

/**
 * KUNIT_EXPECT_STREQ() - Expects that strings @left and @right are equal.
 * @test: The test context object.
 * @left: an arbitrary expression that evaluates to a null terminated string.
 * @right: an arbitrary expression that evaluates to a null terminated string.
 *
 * Sets an expectation that the values that @left and @right evaluate to are
 * equal. This is semantically equivalent to
 * KUNIT_EXPECT_TRUE(@test, !म_भेद((@left), (@right))). See KUNIT_EXPECT_TRUE()
 * क्रम more inक्रमmation.
 */
#घोषणा KUNIT_EXPECT_STREQ(test, left, right) \
	KUNIT_BINARY_STR_EQ_ASSERTION(test, KUNIT_EXPECTATION, left, right)

#घोषणा KUNIT_EXPECT_STREQ_MSG(test, left, right, fmt, ...)		       \
	KUNIT_BINARY_STR_EQ_MSG_ASSERTION(test,				       \
					  KUNIT_EXPECTATION,		       \
					  left,				       \
					  right,			       \
					  fmt,				       \
					  ##__VA_ARGS__)

/**
 * KUNIT_EXPECT_STRNEQ() - Expects that strings @left and @right are not equal.
 * @test: The test context object.
 * @left: an arbitrary expression that evaluates to a null terminated string.
 * @right: an arbitrary expression that evaluates to a null terminated string.
 *
 * Sets an expectation that the values that @left and @right evaluate to are
 * not equal. This is semantically equivalent to
 * KUNIT_EXPECT_TRUE(@test, म_भेद((@left), (@right))). See KUNIT_EXPECT_TRUE()
 * क्रम more inक्रमmation.
 */
#घोषणा KUNIT_EXPECT_STRNEQ(test, left, right) \
	KUNIT_BINARY_STR_NE_ASSERTION(test, KUNIT_EXPECTATION, left, right)

#घोषणा KUNIT_EXPECT_STRNEQ_MSG(test, left, right, fmt, ...)		       \
	KUNIT_BINARY_STR_NE_MSG_ASSERTION(test,				       \
					  KUNIT_EXPECTATION,		       \
					  left,				       \
					  right,			       \
					  fmt,				       \
					  ##__VA_ARGS__)

/**
 * KUNIT_EXPECT_NOT_ERR_OR_शून्य() - Expects that @ptr is not null and not err.
 * @test: The test context object.
 * @ptr: an arbitrary poपूर्णांकer.
 *
 * Sets an expectation that the value that @ptr evaluates to is not null and not
 * an त्रुटि_सं stored in a poपूर्णांकer. This is semantically equivalent to
 * KUNIT_EXPECT_TRUE(@test, !IS_ERR_OR_शून्य(@ptr)). See KUNIT_EXPECT_TRUE() क्रम
 * more inक्रमmation.
 */
#घोषणा KUNIT_EXPECT_NOT_ERR_OR_शून्य(test, ptr) \
	KUNIT_PTR_NOT_ERR_OR_शून्य_ASSERTION(test, KUNIT_EXPECTATION, ptr)

#घोषणा KUNIT_EXPECT_NOT_ERR_OR_शून्य_MSG(test, ptr, fmt, ...)		       \
	KUNIT_PTR_NOT_ERR_OR_शून्य_MSG_ASSERTION(test,			       \
						KUNIT_EXPECTATION,	       \
						ptr,			       \
						fmt,			       \
						##__VA_ARGS__)

#घोषणा KUNIT_ASSERT_FAILURE(test, fmt, ...) \
	KUNIT_FAIL_ASSERTION(test, KUNIT_ASSERTION, fmt, ##__VA_ARGS__)

/**
 * KUNIT_ASSERT_TRUE() - Sets an निश्चितion that @condition is true.
 * @test: The test context object.
 * @condition: an arbitrary boolean expression. The test fails and पातs when
 * this करोes not evaluate to true.
 *
 * This and निश्चितions of the क्रमm `KUNIT_ASSERT_*` will cause the test हाल to
 * fail *and immediately पात* when the specअगरied condition is not met. Unlike
 * an expectation failure, it will prevent the test हाल from continuing to run;
 * this is otherwise known as an *निश्चितion failure*.
 */
#घोषणा KUNIT_ASSERT_TRUE(test, condition) \
	KUNIT_TRUE_ASSERTION(test, KUNIT_ASSERTION, condition)

#घोषणा KUNIT_ASSERT_TRUE_MSG(test, condition, fmt, ...)		       \
	KUNIT_TRUE_MSG_ASSERTION(test,					       \
				 KUNIT_ASSERTION,			       \
				 condition,				       \
				 fmt,					       \
				 ##__VA_ARGS__)

/**
 * KUNIT_ASSERT_FALSE() - Sets an निश्चितion that @condition is false.
 * @test: The test context object.
 * @condition: an arbitrary boolean expression.
 *
 * Sets an निश्चितion that the value that @condition evaluates to is false. This
 * is the same as KUNIT_EXPECT_FALSE(), except it causes an निश्चितion failure
 * (see KUNIT_ASSERT_TRUE()) when the निश्चितion is not met.
 */
#घोषणा KUNIT_ASSERT_FALSE(test, condition) \
	KUNIT_FALSE_ASSERTION(test, KUNIT_ASSERTION, condition)

#घोषणा KUNIT_ASSERT_FALSE_MSG(test, condition, fmt, ...)		       \
	KUNIT_FALSE_MSG_ASSERTION(test,					       \
				  KUNIT_ASSERTION,			       \
				  condition,				       \
				  fmt,					       \
				  ##__VA_ARGS__)

/**
 * KUNIT_ASSERT_EQ() - Sets an निश्चितion that @left and @right are equal.
 * @test: The test context object.
 * @left: an arbitrary expression that evaluates to a primitive C type.
 * @right: an arbitrary expression that evaluates to a primitive C type.
 *
 * Sets an निश्चितion that the values that @left and @right evaluate to are
 * equal. This is the same as KUNIT_EXPECT_EQ(), except it causes an निश्चितion
 * failure (see KUNIT_ASSERT_TRUE()) when the निश्चितion is not met.
 */
#घोषणा KUNIT_ASSERT_EQ(test, left, right) \
	KUNIT_BINARY_EQ_ASSERTION(test, KUNIT_ASSERTION, left, right)

#घोषणा KUNIT_ASSERT_EQ_MSG(test, left, right, fmt, ...)		       \
	KUNIT_BINARY_EQ_MSG_ASSERTION(test,				       \
				      KUNIT_ASSERTION,			       \
				      left,				       \
				      right,				       \
				      fmt,				       \
				      ##__VA_ARGS__)

/**
 * KUNIT_ASSERT_PTR_EQ() - Asserts that poपूर्णांकers @left and @right are equal.
 * @test: The test context object.
 * @left: an arbitrary expression that evaluates to a poपूर्णांकer.
 * @right: an arbitrary expression that evaluates to a poपूर्णांकer.
 *
 * Sets an निश्चितion that the values that @left and @right evaluate to are
 * equal. This is the same as KUNIT_EXPECT_EQ(), except it causes an निश्चितion
 * failure (see KUNIT_ASSERT_TRUE()) when the निश्चितion is not met.
 */
#घोषणा KUNIT_ASSERT_PTR_EQ(test, left, right) \
	KUNIT_BINARY_PTR_EQ_ASSERTION(test, KUNIT_ASSERTION, left, right)

#घोषणा KUNIT_ASSERT_PTR_EQ_MSG(test, left, right, fmt, ...)		       \
	KUNIT_BINARY_PTR_EQ_MSG_ASSERTION(test,				       \
					  KUNIT_ASSERTION,		       \
					  left,				       \
					  right,			       \
					  fmt,				       \
					  ##__VA_ARGS__)

/**
 * KUNIT_ASSERT_NE() - An निश्चितion that @left and @right are not equal.
 * @test: The test context object.
 * @left: an arbitrary expression that evaluates to a primitive C type.
 * @right: an arbitrary expression that evaluates to a primitive C type.
 *
 * Sets an निश्चितion that the values that @left and @right evaluate to are not
 * equal. This is the same as KUNIT_EXPECT_NE(), except it causes an निश्चितion
 * failure (see KUNIT_ASSERT_TRUE()) when the निश्चितion is not met.
 */
#घोषणा KUNIT_ASSERT_NE(test, left, right) \
	KUNIT_BINARY_NE_ASSERTION(test, KUNIT_ASSERTION, left, right)

#घोषणा KUNIT_ASSERT_NE_MSG(test, left, right, fmt, ...)		       \
	KUNIT_BINARY_NE_MSG_ASSERTION(test,				       \
				      KUNIT_ASSERTION,			       \
				      left,				       \
				      right,				       \
				      fmt,				       \
				      ##__VA_ARGS__)

/**
 * KUNIT_ASSERT_PTR_NE() - Asserts that poपूर्णांकers @left and @right are not equal.
 * KUNIT_ASSERT_PTR_EQ() - Asserts that poपूर्णांकers @left and @right are equal.
 * @test: The test context object.
 * @left: an arbitrary expression that evaluates to a poपूर्णांकer.
 * @right: an arbitrary expression that evaluates to a poपूर्णांकer.
 *
 * Sets an निश्चितion that the values that @left and @right evaluate to are not
 * equal. This is the same as KUNIT_EXPECT_NE(), except it causes an निश्चितion
 * failure (see KUNIT_ASSERT_TRUE()) when the निश्चितion is not met.
 */
#घोषणा KUNIT_ASSERT_PTR_NE(test, left, right) \
	KUNIT_BINARY_PTR_NE_ASSERTION(test, KUNIT_ASSERTION, left, right)

#घोषणा KUNIT_ASSERT_PTR_NE_MSG(test, left, right, fmt, ...)		       \
	KUNIT_BINARY_PTR_NE_MSG_ASSERTION(test,				       \
					  KUNIT_ASSERTION,		       \
					  left,				       \
					  right,			       \
					  fmt,				       \
					  ##__VA_ARGS__)
/**
 * KUNIT_ASSERT_LT() - An निश्चितion that @left is less than @right.
 * @test: The test context object.
 * @left: an arbitrary expression that evaluates to a primitive C type.
 * @right: an arbitrary expression that evaluates to a primitive C type.
 *
 * Sets an निश्चितion that the value that @left evaluates to is less than the
 * value that @right evaluates to. This is the same as KUNIT_EXPECT_LT(), except
 * it causes an निश्चितion failure (see KUNIT_ASSERT_TRUE()) when the निश्चितion
 * is not met.
 */
#घोषणा KUNIT_ASSERT_LT(test, left, right) \
	KUNIT_BINARY_LT_ASSERTION(test, KUNIT_ASSERTION, left, right)

#घोषणा KUNIT_ASSERT_LT_MSG(test, left, right, fmt, ...)		       \
	KUNIT_BINARY_LT_MSG_ASSERTION(test,				       \
				      KUNIT_ASSERTION,			       \
				      left,				       \
				      right,				       \
				      fmt,				       \
				      ##__VA_ARGS__)
/**
 * KUNIT_ASSERT_LE() - An निश्चितion that @left is less than or equal to @right.
 * @test: The test context object.
 * @left: an arbitrary expression that evaluates to a primitive C type.
 * @right: an arbitrary expression that evaluates to a primitive C type.
 *
 * Sets an निश्चितion that the value that @left evaluates to is less than or
 * equal to the value that @right evaluates to. This is the same as
 * KUNIT_EXPECT_LE(), except it causes an निश्चितion failure (see
 * KUNIT_ASSERT_TRUE()) when the निश्चितion is not met.
 */
#घोषणा KUNIT_ASSERT_LE(test, left, right) \
	KUNIT_BINARY_LE_ASSERTION(test, KUNIT_ASSERTION, left, right)

#घोषणा KUNIT_ASSERT_LE_MSG(test, left, right, fmt, ...)		       \
	KUNIT_BINARY_LE_MSG_ASSERTION(test,				       \
				      KUNIT_ASSERTION,			       \
				      left,				       \
				      right,				       \
				      fmt,				       \
				      ##__VA_ARGS__)

/**
 * KUNIT_ASSERT_GT() - An निश्चितion that @left is greater than @right.
 * @test: The test context object.
 * @left: an arbitrary expression that evaluates to a primitive C type.
 * @right: an arbitrary expression that evaluates to a primitive C type.
 *
 * Sets an निश्चितion that the value that @left evaluates to is greater than the
 * value that @right evaluates to. This is the same as KUNIT_EXPECT_GT(), except
 * it causes an निश्चितion failure (see KUNIT_ASSERT_TRUE()) when the निश्चितion
 * is not met.
 */
#घोषणा KUNIT_ASSERT_GT(test, left, right) \
	KUNIT_BINARY_GT_ASSERTION(test, KUNIT_ASSERTION, left, right)

#घोषणा KUNIT_ASSERT_GT_MSG(test, left, right, fmt, ...)		       \
	KUNIT_BINARY_GT_MSG_ASSERTION(test,				       \
				      KUNIT_ASSERTION,			       \
				      left,				       \
				      right,				       \
				      fmt,				       \
				      ##__VA_ARGS__)

/**
 * KUNIT_ASSERT_GE() - Assertion that @left is greater than or equal to @right.
 * @test: The test context object.
 * @left: an arbitrary expression that evaluates to a primitive C type.
 * @right: an arbitrary expression that evaluates to a primitive C type.
 *
 * Sets an निश्चितion that the value that @left evaluates to is greater than the
 * value that @right evaluates to. This is the same as KUNIT_EXPECT_GE(), except
 * it causes an निश्चितion failure (see KUNIT_ASSERT_TRUE()) when the निश्चितion
 * is not met.
 */
#घोषणा KUNIT_ASSERT_GE(test, left, right) \
	KUNIT_BINARY_GE_ASSERTION(test, KUNIT_ASSERTION, left, right)

#घोषणा KUNIT_ASSERT_GE_MSG(test, left, right, fmt, ...)		       \
	KUNIT_BINARY_GE_MSG_ASSERTION(test,				       \
				      KUNIT_ASSERTION,			       \
				      left,				       \
				      right,				       \
				      fmt,				       \
				      ##__VA_ARGS__)

/**
 * KUNIT_ASSERT_STREQ() - An निश्चितion that strings @left and @right are equal.
 * @test: The test context object.
 * @left: an arbitrary expression that evaluates to a null terminated string.
 * @right: an arbitrary expression that evaluates to a null terminated string.
 *
 * Sets an निश्चितion that the values that @left and @right evaluate to are
 * equal. This is the same as KUNIT_EXPECT_STREQ(), except it causes an
 * निश्चितion failure (see KUNIT_ASSERT_TRUE()) when the निश्चितion is not met.
 */
#घोषणा KUNIT_ASSERT_STREQ(test, left, right) \
	KUNIT_BINARY_STR_EQ_ASSERTION(test, KUNIT_ASSERTION, left, right)

#घोषणा KUNIT_ASSERT_STREQ_MSG(test, left, right, fmt, ...)		       \
	KUNIT_BINARY_STR_EQ_MSG_ASSERTION(test,				       \
					  KUNIT_ASSERTION,		       \
					  left,				       \
					  right,			       \
					  fmt,				       \
					  ##__VA_ARGS__)

/**
 * KUNIT_ASSERT_STRNEQ() - Expects that strings @left and @right are not equal.
 * @test: The test context object.
 * @left: an arbitrary expression that evaluates to a null terminated string.
 * @right: an arbitrary expression that evaluates to a null terminated string.
 *
 * Sets an expectation that the values that @left and @right evaluate to are
 * not equal. This is semantically equivalent to
 * KUNIT_ASSERT_TRUE(@test, म_भेद((@left), (@right))). See KUNIT_ASSERT_TRUE()
 * क्रम more inक्रमmation.
 */
#घोषणा KUNIT_ASSERT_STRNEQ(test, left, right) \
	KUNIT_BINARY_STR_NE_ASSERTION(test, KUNIT_ASSERTION, left, right)

#घोषणा KUNIT_ASSERT_STRNEQ_MSG(test, left, right, fmt, ...)		       \
	KUNIT_BINARY_STR_NE_MSG_ASSERTION(test,				       \
					  KUNIT_ASSERTION,		       \
					  left,				       \
					  right,			       \
					  fmt,				       \
					  ##__VA_ARGS__)

/**
 * KUNIT_ASSERT_NOT_ERR_OR_शून्य() - Assertion that @ptr is not null and not err.
 * @test: The test context object.
 * @ptr: an arbitrary poपूर्णांकer.
 *
 * Sets an निश्चितion that the value that @ptr evaluates to is not null and not
 * an त्रुटि_सं stored in a poपूर्णांकer. This is the same as
 * KUNIT_EXPECT_NOT_ERR_OR_शून्य(), except it causes an निश्चितion failure (see
 * KUNIT_ASSERT_TRUE()) when the निश्चितion is not met.
 */
#घोषणा KUNIT_ASSERT_NOT_ERR_OR_शून्य(test, ptr) \
	KUNIT_PTR_NOT_ERR_OR_शून्य_ASSERTION(test, KUNIT_ASSERTION, ptr)

#घोषणा KUNIT_ASSERT_NOT_ERR_OR_शून्य_MSG(test, ptr, fmt, ...)		       \
	KUNIT_PTR_NOT_ERR_OR_शून्य_MSG_ASSERTION(test,			       \
						KUNIT_ASSERTION,	       \
						ptr,			       \
						fmt,			       \
						##__VA_ARGS__)

/**
 * KUNIT_ARRAY_PARAM() - Define test parameter generator from an array.
 * @name:  prefix क्रम the test parameter generator function.
 * @array: array of test parameters.
 * @get_desc: function to convert param to description; शून्य to use शेष
 *
 * Define function @name_gen_params which uses @array to generate parameters.
 */
#घोषणा KUNIT_ARRAY_PARAM(name, array, get_desc)						\
	अटल स्थिर व्योम *name##_gen_params(स्थिर व्योम *prev, अक्षर *desc)			\
	अणु											\
		typeof((array)[0]) *__next = prev ? ((typeof(__next)) prev) + 1 : (array);	\
		अगर (__next - (array) < ARRAY_SIZE((array))) अणु					\
			व्योम (*__get_desc)(typeof(__next), अक्षर *) = get_desc;			\
			अगर (__get_desc)								\
				__get_desc(__next, desc);					\
			वापस __next;								\
		पूर्ण										\
		वापस शून्य;									\
	पूर्ण

#पूर्ण_अगर /* _KUNIT_TEST_H */
