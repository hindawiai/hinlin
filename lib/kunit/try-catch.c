<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * An API to allow a function, that may fail, to be executed, and recover in a
 * controlled manner.
 *
 * Copyright (C) 2019, Google LLC.
 * Author: Brendan Higgins <brendanhiggins@google.com>
 */

#समावेश <kunit/test.h>
#समावेश <linux/completion.h>
#समावेश <linux/kernel.h>
#समावेश <linux/kthपढ़ो.h>

#समावेश "try-catch-impl.h"

व्योम __noवापस kunit_try_catch_throw(काष्ठा kunit_try_catch *try_catch)
अणु
	try_catch->try_result = -EFAULT;
	complete_and_निकास(try_catch->try_completion, -EFAULT);
पूर्ण
EXPORT_SYMBOL_GPL(kunit_try_catch_throw);

अटल पूर्णांक kunit_generic_run_thपढ़ोfn_adapter(व्योम *data)
अणु
	काष्ठा kunit_try_catch *try_catch = data;

	try_catch->try(try_catch->context);

	complete_and_निकास(try_catch->try_completion, 0);
पूर्ण

अटल अचिन्हित दीर्घ kunit_test_समयout(व्योम)
अणु
	/*
	 * TODO(brendanhiggins@google.com): We should probably have some type of
	 * variable समयout here. The only question is what that समयout value
	 * should be.
	 *
	 * The पूर्णांकention has always been, at some poपूर्णांक, to be able to label
	 * tests with some type of size bucket (unit/small, पूर्णांकegration/medium,
	 * large/प्रणाली/end-to-end, etc), where each size bucket would get a
	 * शेष समयout value kind of like what Bazel करोes:
	 * https://करोcs.bazel.build/versions/master/be/common-definitions.hपंचांगl#test.size
	 * There is still some debate to be had on exactly how we करो this. (For
	 * one, we probably want to have some sort of test runner level
	 * समयout.)
	 *
	 * For more background on this topic, see:
	 * https://mike-bland.com/2011/11/01/small-medium-large.hपंचांगl
	 *
	 * If tests समयout due to exceeding sysctl_hung_task_समयout_secs,
	 * the task will be समाप्तed and an oops generated.
	 */
	वापस 300 * MSEC_PER_SEC; /* 5 min */
पूर्ण

व्योम kunit_try_catch_run(काष्ठा kunit_try_catch *try_catch, व्योम *context)
अणु
	DECLARE_COMPLETION_ONSTACK(try_completion);
	काष्ठा kunit *test = try_catch->test;
	काष्ठा task_काष्ठा *task_काष्ठा;
	पूर्णांक निकास_code, समय_reमुख्यing;

	try_catch->context = context;
	try_catch->try_completion = &try_completion;
	try_catch->try_result = 0;
	task_काष्ठा = kthपढ़ो_run(kunit_generic_run_thपढ़ोfn_adapter,
				  try_catch,
				  "kunit_try_catch_thread");
	अगर (IS_ERR(task_काष्ठा)) अणु
		try_catch->catch(try_catch->context);
		वापस;
	पूर्ण

	समय_reमुख्यing = रुको_क्रम_completion_समयout(&try_completion,
						     kunit_test_समयout());
	अगर (समय_reमुख्यing == 0) अणु
		kunit_err(test, "try timed out\n");
		try_catch->try_result = -ETIMEDOUT;
	पूर्ण

	निकास_code = try_catch->try_result;

	अगर (!निकास_code)
		वापस;

	अगर (निकास_code == -EFAULT)
		try_catch->try_result = 0;
	अन्यथा अगर (निकास_code == -EINTR)
		kunit_err(test, "wake_up_process() was never called\n");
	अन्यथा अगर (निकास_code)
		kunit_err(test, "Unknown error: %d\n", निकास_code);

	try_catch->catch(try_catch->context);
पूर्ण
EXPORT_SYMBOL_GPL(kunit_try_catch_run);
