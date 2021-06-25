<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Internal kunit try catch implementation to be shared with tests.
 *
 * Copyright (C) 2019, Google LLC.
 * Author: Brendan Higgins <brendanhiggins@google.com>
 */

#अगर_अघोषित _KUNIT_TRY_CATCH_IMPL_H
#घोषणा _KUNIT_TRY_CATCH_IMPL_H

#समावेश <kunit/try-catch.h>
#समावेश <linux/types.h>

काष्ठा kunit;

अटल अंतरभूत व्योम kunit_try_catch_init(काष्ठा kunit_try_catch *try_catch,
					काष्ठा kunit *test,
					kunit_try_catch_func_t try,
					kunit_try_catch_func_t catch)
अणु
	try_catch->test = test;
	try_catch->try = try;
	try_catch->catch = catch;
पूर्ण

#पूर्ण_अगर /* _KUNIT_TRY_CATCH_IMPL_H */
