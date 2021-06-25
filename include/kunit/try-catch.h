<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * An API to allow a function, that may fail, to be executed, and recover in a
 * controlled manner.
 *
 * Copyright (C) 2019, Google LLC.
 * Author: Brendan Higgins <brendanhiggins@google.com>
 */

#अगर_अघोषित _KUNIT_TRY_CATCH_H
#घोषणा _KUNIT_TRY_CATCH_H

#समावेश <linux/types.h>

प्रकार व्योम (*kunit_try_catch_func_t)(व्योम *);

काष्ठा completion;
काष्ठा kunit;

/**
 * काष्ठा kunit_try_catch - provides a generic way to run code which might fail.
 * @test: The test हाल that is currently being executed.
 * @try_completion: Completion that the control thपढ़ो रुकोs on जबतक test runs.
 * @try_result: Contains any त्रुटि_सं obtained जबतक running test हाल.
 * @try: The function, the test हाल, to attempt to run.
 * @catch: The function called अगर @try bails out.
 * @context: used to pass user data to the try and catch functions.
 *
 * kunit_try_catch provides a generic, architecture independent way to execute
 * an arbitrary function of type kunit_try_catch_func_t which may bail out by
 * calling kunit_try_catch_throw(). If kunit_try_catch_throw() is called, @try
 * is stopped at the site of invocation and @catch is called.
 *
 * काष्ठा kunit_try_catch provides a generic पूर्णांकerface क्रम the functionality
 * needed to implement kunit->पात() which in turn is needed क्रम implementing
 * निश्चितions. Assertions allow stating a precondition क्रम a test simplअगरying
 * how test हालs are written and presented.
 *
 * Assertions are like expectations, except they पात (call
 * kunit_try_catch_throw()) when the specअगरied condition is not met. This is
 * useful when you look at a test हाल as a logical statement about some piece
 * of code, where निश्चितions are the premises क्रम the test हाल, and the
 * conclusion is a set of predicates, rather expectations, that must all be
 * true. If your premises are violated, it करोes not makes sense to जारी.
 */
काष्ठा kunit_try_catch अणु
	/* निजी: पूर्णांकernal use only. */
	काष्ठा kunit *test;
	काष्ठा completion *try_completion;
	पूर्णांक try_result;
	kunit_try_catch_func_t try;
	kunit_try_catch_func_t catch;
	व्योम *context;
पूर्ण;

व्योम kunit_try_catch_run(काष्ठा kunit_try_catch *try_catch, व्योम *context);

व्योम __noवापस kunit_try_catch_throw(काष्ठा kunit_try_catch *try_catch);

अटल अंतरभूत पूर्णांक kunit_try_catch_get_result(काष्ठा kunit_try_catch *try_catch)
अणु
	वापस try_catch->try_result;
पूर्ण

#पूर्ण_अगर /* _KUNIT_TRY_CATCH_H */
