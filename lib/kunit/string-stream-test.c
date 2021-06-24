<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * KUnit test क्रम काष्ठा string_stream.
 *
 * Copyright (C) 2019, Google LLC.
 * Author: Brendan Higgins <brendanhiggins@google.com>
 */

#समावेश <kunit/test.h>
#समावेश <linux/slab.h>

#समावेश "string-stream.h"

अटल व्योम string_stream_test_empty_on_creation(काष्ठा kunit *test)
अणु
	काष्ठा string_stream *stream = alloc_string_stream(test, GFP_KERNEL);

	KUNIT_EXPECT_TRUE(test, string_stream_is_empty(stream));
पूर्ण

अटल व्योम string_stream_test_not_empty_after_add(काष्ठा kunit *test)
अणु
	काष्ठा string_stream *stream = alloc_string_stream(test, GFP_KERNEL);

	string_stream_add(stream, "Foo");

	KUNIT_EXPECT_FALSE(test, string_stream_is_empty(stream));
पूर्ण

अटल व्योम string_stream_test_get_string(काष्ठा kunit *test)
अणु
	काष्ठा string_stream *stream = alloc_string_stream(test, GFP_KERNEL);
	अक्षर *output;

	string_stream_add(stream, "Foo");
	string_stream_add(stream, " %s", "bar");

	output = string_stream_get_string(stream);
	KUNIT_ASSERT_STREQ(test, output, "Foo bar");
पूर्ण

अटल काष्ठा kunit_हाल string_stream_test_हालs[] = अणु
	KUNIT_CASE(string_stream_test_empty_on_creation),
	KUNIT_CASE(string_stream_test_not_empty_after_add),
	KUNIT_CASE(string_stream_test_get_string),
	अणुपूर्ण
पूर्ण;

अटल काष्ठा kunit_suite string_stream_test_suite = अणु
	.name = "string-stream-test",
	.test_हालs = string_stream_test_हालs
पूर्ण;
kunit_test_suites(&string_stream_test_suite);
