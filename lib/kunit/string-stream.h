<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * C++ stream style string builder used in KUnit क्रम building messages.
 *
 * Copyright (C) 2019, Google LLC.
 * Author: Brendan Higgins <brendanhiggins@google.com>
 */

#अगर_अघोषित _KUNIT_STRING_STREAM_H
#घोषणा _KUNIT_STRING_STREAM_H

#समावेश <linux/spinlock.h>
#समावेश <linux/types.h>
#समावेश <मानकतर्क.स>

काष्ठा string_stream_fragment अणु
	काष्ठा kunit *test;
	काष्ठा list_head node;
	अक्षर *fragment;
पूर्ण;

काष्ठा string_stream अणु
	माप_प्रकार length;
	काष्ठा list_head fragments;
	/* length and fragments are रक्षित by this lock */
	spinlock_t lock;
	काष्ठा kunit *test;
	gfp_t gfp;
पूर्ण;

काष्ठा kunit;

काष्ठा string_stream *alloc_string_stream(काष्ठा kunit *test, gfp_t gfp);

पूर्णांक __म_लिखो(2, 3) string_stream_add(काष्ठा string_stream *stream,
				     स्थिर अक्षर *fmt, ...);

पूर्णांक string_stream_vadd(काष्ठा string_stream *stream,
		       स्थिर अक्षर *fmt,
		       बहु_सूची args);

अक्षर *string_stream_get_string(काष्ठा string_stream *stream);

पूर्णांक string_stream_append(काष्ठा string_stream *stream,
			 काष्ठा string_stream *other);

bool string_stream_is_empty(काष्ठा string_stream *stream);

पूर्णांक string_stream_destroy(काष्ठा string_stream *stream);

#पूर्ण_अगर /* _KUNIT_STRING_STREAM_H */
