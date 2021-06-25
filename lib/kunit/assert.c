<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Assertion and expectation serialization API.
 *
 * Copyright (C) 2019, Google LLC.
 * Author: Brendan Higgins <brendanhiggins@google.com>
 */
#समावेश <kunit/निश्चित.स>
#समावेश <kunit/test.h>

#समावेश "string-stream.h"

व्योम kunit_base_निश्चित_क्रमmat(स्थिर काष्ठा kunit_निश्चित *निश्चित,
			      काष्ठा string_stream *stream)
अणु
	स्थिर अक्षर *expect_or_निश्चित = शून्य;

	चयन (निश्चित->type) अणु
	हाल KUNIT_EXPECTATION:
		expect_or_निश्चित = "EXPECTATION";
		अवरोध;
	हाल KUNIT_ASSERTION:
		expect_or_निश्चित = "ASSERTION";
		अवरोध;
	पूर्ण

	string_stream_add(stream, "%s FAILED at %s:%d\n",
			  expect_or_निश्चित, निश्चित->file, निश्चित->line);
पूर्ण
EXPORT_SYMBOL_GPL(kunit_base_निश्चित_क्रमmat);

व्योम kunit_निश्चित_prपूर्णांक_msg(स्थिर काष्ठा kunit_निश्चित *निश्चित,
			    काष्ठा string_stream *stream)
अणु
	अगर (निश्चित->message.fmt)
		string_stream_add(stream, "\n%pV", &निश्चित->message);
पूर्ण
EXPORT_SYMBOL_GPL(kunit_निश्चित_prपूर्णांक_msg);

व्योम kunit_fail_निश्चित_क्रमmat(स्थिर काष्ठा kunit_निश्चित *निश्चित,
			      काष्ठा string_stream *stream)
अणु
	kunit_base_निश्चित_क्रमmat(निश्चित, stream);
	string_stream_add(stream, "%pV", &निश्चित->message);
पूर्ण
EXPORT_SYMBOL_GPL(kunit_fail_निश्चित_क्रमmat);

व्योम kunit_unary_निश्चित_क्रमmat(स्थिर काष्ठा kunit_निश्चित *निश्चित,
			       काष्ठा string_stream *stream)
अणु
	काष्ठा kunit_unary_निश्चित *unary_निश्चित;

	unary_निश्चित = container_of(निश्चित, काष्ठा kunit_unary_निश्चित, निश्चित);

	kunit_base_निश्चित_क्रमmat(निश्चित, stream);
	अगर (unary_निश्चित->expected_true)
		string_stream_add(stream,
				  KUNIT_SUBTEST_INDENT "Expected %s to be true, but is false\n",
				  unary_निश्चित->condition);
	अन्यथा
		string_stream_add(stream,
				  KUNIT_SUBTEST_INDENT "Expected %s to be false, but is true\n",
				  unary_निश्चित->condition);
	kunit_निश्चित_prपूर्णांक_msg(निश्चित, stream);
पूर्ण
EXPORT_SYMBOL_GPL(kunit_unary_निश्चित_क्रमmat);

व्योम kunit_ptr_not_err_निश्चित_क्रमmat(स्थिर काष्ठा kunit_निश्चित *निश्चित,
				     काष्ठा string_stream *stream)
अणु
	काष्ठा kunit_ptr_not_err_निश्चित *ptr_निश्चित;

	ptr_निश्चित = container_of(निश्चित, काष्ठा kunit_ptr_not_err_निश्चित,
				  निश्चित);

	kunit_base_निश्चित_क्रमmat(निश्चित, stream);
	अगर (!ptr_निश्चित->value) अणु
		string_stream_add(stream,
				  KUNIT_SUBTEST_INDENT "Expected %s is not null, but is\n",
				  ptr_निश्चित->text);
	पूर्ण अन्यथा अगर (IS_ERR(ptr_निश्चित->value)) अणु
		string_stream_add(stream,
				  KUNIT_SUBTEST_INDENT "Expected %s is not error, but is: %ld\n",
				  ptr_निश्चित->text,
				  PTR_ERR(ptr_निश्चित->value));
	पूर्ण
	kunit_निश्चित_prपूर्णांक_msg(निश्चित, stream);
पूर्ण
EXPORT_SYMBOL_GPL(kunit_ptr_not_err_निश्चित_क्रमmat);

/* Checks अगर `text` is a literal representing `value`, e.g. "5" and 5 */
अटल bool is_literal(काष्ठा kunit *test, स्थिर अक्षर *text, दीर्घ दीर्घ value,
		       gfp_t gfp)
अणु
	अक्षर *buffer;
	पूर्णांक len;
	bool ret;

	len = snम_लिखो(शून्य, 0, "%lld", value);
	अगर (म_माप(text) != len)
		वापस false;

	buffer = kunit_kदो_स्मृति(test, len+1, gfp);
	अगर (!buffer)
		वापस false;

	snम_लिखो(buffer, len+1, "%lld", value);
	ret = म_भेदन(buffer, text, len) == 0;

	kunit_kमुक्त(test, buffer);
	वापस ret;
पूर्ण

व्योम kunit_binary_निश्चित_क्रमmat(स्थिर काष्ठा kunit_निश्चित *निश्चित,
				काष्ठा string_stream *stream)
अणु
	काष्ठा kunit_binary_निश्चित *binary_निश्चित;

	binary_निश्चित = container_of(निश्चित, काष्ठा kunit_binary_निश्चित,
				     निश्चित);

	kunit_base_निश्चित_क्रमmat(निश्चित, stream);
	string_stream_add(stream,
			  KUNIT_SUBTEST_INDENT "Expected %s %s %s, but\n",
			  binary_निश्चित->left_text,
			  binary_निश्चित->operation,
			  binary_निश्चित->right_text);
	अगर (!is_literal(stream->test, binary_निश्चित->left_text,
			binary_निश्चित->left_value, stream->gfp))
		string_stream_add(stream, KUNIT_SUBSUBTEST_INDENT "%s == %lld\n",
				  binary_निश्चित->left_text,
				  binary_निश्चित->left_value);
	अगर (!is_literal(stream->test, binary_निश्चित->right_text,
			binary_निश्चित->right_value, stream->gfp))
		string_stream_add(stream, KUNIT_SUBSUBTEST_INDENT "%s == %lld",
				  binary_निश्चित->right_text,
				  binary_निश्चित->right_value);
	kunit_निश्चित_prपूर्णांक_msg(निश्चित, stream);
पूर्ण
EXPORT_SYMBOL_GPL(kunit_binary_निश्चित_क्रमmat);

व्योम kunit_binary_ptr_निश्चित_क्रमmat(स्थिर काष्ठा kunit_निश्चित *निश्चित,
				    काष्ठा string_stream *stream)
अणु
	काष्ठा kunit_binary_ptr_निश्चित *binary_निश्चित;

	binary_निश्चित = container_of(निश्चित, काष्ठा kunit_binary_ptr_निश्चित,
				     निश्चित);

	kunit_base_निश्चित_क्रमmat(निश्चित, stream);
	string_stream_add(stream,
			  KUNIT_SUBTEST_INDENT "Expected %s %s %s, but\n",
			  binary_निश्चित->left_text,
			  binary_निश्चित->operation,
			  binary_निश्चित->right_text);
	string_stream_add(stream, KUNIT_SUBSUBTEST_INDENT "%s == %px\n",
			  binary_निश्चित->left_text,
			  binary_निश्चित->left_value);
	string_stream_add(stream, KUNIT_SUBSUBTEST_INDENT "%s == %px",
			  binary_निश्चित->right_text,
			  binary_निश्चित->right_value);
	kunit_निश्चित_prपूर्णांक_msg(निश्चित, stream);
पूर्ण
EXPORT_SYMBOL_GPL(kunit_binary_ptr_निश्चित_क्रमmat);

/* Checks अगर KUNIT_EXPECT_STREQ() args were string literals.
 * Note: `text` will have ""s where as `value` will not.
 */
अटल bool is_str_literal(स्थिर अक्षर *text, स्थिर अक्षर *value)
अणु
	पूर्णांक len;

	len = म_माप(text);
	अगर (len < 2)
		वापस false;
	अगर (text[0] != '\"' || text[len - 1] != '\"')
		वापस false;

	वापस म_भेदन(text + 1, value, len - 2) == 0;
पूर्ण

व्योम kunit_binary_str_निश्चित_क्रमmat(स्थिर काष्ठा kunit_निश्चित *निश्चित,
				    काष्ठा string_stream *stream)
अणु
	काष्ठा kunit_binary_str_निश्चित *binary_निश्चित;

	binary_निश्चित = container_of(निश्चित, काष्ठा kunit_binary_str_निश्चित,
				     निश्चित);

	kunit_base_निश्चित_क्रमmat(निश्चित, stream);
	string_stream_add(stream,
			  KUNIT_SUBTEST_INDENT "Expected %s %s %s, but\n",
			  binary_निश्चित->left_text,
			  binary_निश्चित->operation,
			  binary_निश्चित->right_text);
	अगर (!is_str_literal(binary_निश्चित->left_text, binary_निश्चित->left_value))
		string_stream_add(stream, KUNIT_SUBSUBTEST_INDENT "%s == \"%s\"\n",
				  binary_निश्चित->left_text,
				  binary_निश्चित->left_value);
	अगर (!is_str_literal(binary_निश्चित->right_text, binary_निश्चित->right_value))
		string_stream_add(stream, KUNIT_SUBSUBTEST_INDENT "%s == \"%s\"",
				  binary_निश्चित->right_text,
				  binary_निश्चित->right_value);
	kunit_निश्चित_prपूर्णांक_msg(निश्चित, stream);
पूर्ण
EXPORT_SYMBOL_GPL(kunit_binary_str_निश्चित_क्रमmat);
