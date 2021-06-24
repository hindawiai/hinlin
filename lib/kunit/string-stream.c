<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * C++ stream style string builder used in KUnit क्रम building messages.
 *
 * Copyright (C) 2019, Google LLC.
 * Author: Brendan Higgins <brendanhiggins@google.com>
 */

#समावेश <kunit/test.h>
#समावेश <linux/list.h>
#समावेश <linux/slab.h>

#समावेश "string-stream.h"

काष्ठा string_stream_fragment_alloc_context अणु
	काष्ठा kunit *test;
	पूर्णांक len;
	gfp_t gfp;
पूर्ण;

अटल पूर्णांक string_stream_fragment_init(काष्ठा kunit_resource *res,
				       व्योम *context)
अणु
	काष्ठा string_stream_fragment_alloc_context *ctx = context;
	काष्ठा string_stream_fragment *frag;

	frag = kunit_kzalloc(ctx->test, माप(*frag), ctx->gfp);
	अगर (!frag)
		वापस -ENOMEM;

	frag->test = ctx->test;
	frag->fragment = kunit_kदो_स्मृति(ctx->test, ctx->len, ctx->gfp);
	अगर (!frag->fragment)
		वापस -ENOMEM;

	res->data = frag;

	वापस 0;
पूर्ण

अटल व्योम string_stream_fragment_मुक्त(काष्ठा kunit_resource *res)
अणु
	काष्ठा string_stream_fragment *frag = res->data;

	list_del(&frag->node);
	kunit_kमुक्त(frag->test, frag->fragment);
	kunit_kमुक्त(frag->test, frag);
पूर्ण

अटल काष्ठा string_stream_fragment *alloc_string_stream_fragment(
		काष्ठा kunit *test, पूर्णांक len, gfp_t gfp)
अणु
	काष्ठा string_stream_fragment_alloc_context context = अणु
		.test = test,
		.len = len,
		.gfp = gfp
	पूर्ण;

	वापस kunit_alloc_resource(test,
				    string_stream_fragment_init,
				    string_stream_fragment_मुक्त,
				    gfp,
				    &context);
पूर्ण

अटल पूर्णांक string_stream_fragment_destroy(काष्ठा string_stream_fragment *frag)
अणु
	वापस kunit_destroy_resource(frag->test,
				      kunit_resource_instance_match,
				      frag);
पूर्ण

पूर्णांक string_stream_vadd(काष्ठा string_stream *stream,
		       स्थिर अक्षर *fmt,
		       बहु_सूची args)
अणु
	काष्ठा string_stream_fragment *frag_container;
	पूर्णांक len;
	बहु_सूची args_क्रम_counting;

	/* Make a copy because `vsnम_लिखो` could change it */
	va_copy(args_क्रम_counting, args);

	/* Need space क्रम null byte. */
	len = vsnम_लिखो(शून्य, 0, fmt, args_क्रम_counting) + 1;

	बहु_पूर्ण(args_क्रम_counting);

	frag_container = alloc_string_stream_fragment(stream->test,
						      len,
						      stream->gfp);
	अगर (!frag_container)
		वापस -ENOMEM;

	len = vsnम_लिखो(frag_container->fragment, len, fmt, args);
	spin_lock(&stream->lock);
	stream->length += len;
	list_add_tail(&frag_container->node, &stream->fragments);
	spin_unlock(&stream->lock);

	वापस 0;
पूर्ण

पूर्णांक string_stream_add(काष्ठा string_stream *stream, स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची args;
	पूर्णांक result;

	बहु_शुरू(args, fmt);
	result = string_stream_vadd(stream, fmt, args);
	बहु_पूर्ण(args);

	वापस result;
पूर्ण

अटल व्योम string_stream_clear(काष्ठा string_stream *stream)
अणु
	काष्ठा string_stream_fragment *frag_container, *frag_container_safe;

	spin_lock(&stream->lock);
	list_क्रम_each_entry_safe(frag_container,
				 frag_container_safe,
				 &stream->fragments,
				 node) अणु
		string_stream_fragment_destroy(frag_container);
	पूर्ण
	stream->length = 0;
	spin_unlock(&stream->lock);
पूर्ण

अक्षर *string_stream_get_string(काष्ठा string_stream *stream)
अणु
	काष्ठा string_stream_fragment *frag_container;
	माप_प्रकार buf_len = stream->length + 1; /* +1 क्रम null byte. */
	अक्षर *buf;

	buf = kunit_kzalloc(stream->test, buf_len, stream->gfp);
	अगर (!buf)
		वापस शून्य;

	spin_lock(&stream->lock);
	list_क्रम_each_entry(frag_container, &stream->fragments, node)
		strlcat(buf, frag_container->fragment, buf_len);
	spin_unlock(&stream->lock);

	वापस buf;
पूर्ण

पूर्णांक string_stream_append(काष्ठा string_stream *stream,
			 काष्ठा string_stream *other)
अणु
	स्थिर अक्षर *other_content;

	other_content = string_stream_get_string(other);

	अगर (!other_content)
		वापस -ENOMEM;

	वापस string_stream_add(stream, other_content);
पूर्ण

bool string_stream_is_empty(काष्ठा string_stream *stream)
अणु
	वापस list_empty(&stream->fragments);
पूर्ण

काष्ठा string_stream_alloc_context अणु
	काष्ठा kunit *test;
	gfp_t gfp;
पूर्ण;

अटल पूर्णांक string_stream_init(काष्ठा kunit_resource *res, व्योम *context)
अणु
	काष्ठा string_stream *stream;
	काष्ठा string_stream_alloc_context *ctx = context;

	stream = kunit_kzalloc(ctx->test, माप(*stream), ctx->gfp);
	अगर (!stream)
		वापस -ENOMEM;

	res->data = stream;
	stream->gfp = ctx->gfp;
	stream->test = ctx->test;
	INIT_LIST_HEAD(&stream->fragments);
	spin_lock_init(&stream->lock);

	वापस 0;
पूर्ण

अटल व्योम string_stream_मुक्त(काष्ठा kunit_resource *res)
अणु
	काष्ठा string_stream *stream = res->data;

	string_stream_clear(stream);
पूर्ण

काष्ठा string_stream *alloc_string_stream(काष्ठा kunit *test, gfp_t gfp)
अणु
	काष्ठा string_stream_alloc_context context = अणु
		.test = test,
		.gfp = gfp
	पूर्ण;

	वापस kunit_alloc_resource(test,
				    string_stream_init,
				    string_stream_मुक्त,
				    gfp,
				    &context);
पूर्ण

पूर्णांक string_stream_destroy(काष्ठा string_stream *stream)
अणु
	वापस kunit_destroy_resource(stream->test,
				      kunit_resource_instance_match,
				      stream);
पूर्ण
