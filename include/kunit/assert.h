<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Assertion and expectation serialization API.
 *
 * Copyright (C) 2019, Google LLC.
 * Author: Brendan Higgins <brendanhiggins@google.com>
 */

#अगर_अघोषित _KUNIT_ASSERT_H
#घोषणा _KUNIT_ASSERT_H

#समावेश <linux/err.h>
#समावेश <linux/kernel.h>

काष्ठा kunit;
काष्ठा string_stream;

/**
 * क्रमागत kunit_निश्चित_type - Type of expectation/निश्चितion.
 * @KUNIT_ASSERTION: Used to denote that a kunit_निश्चित represents an निश्चितion.
 * @KUNIT_EXPECTATION: Denotes that a kunit_निश्चित represents an expectation.
 *
 * Used in conjunction with a &काष्ठा kunit_निश्चित to denote whether it
 * represents an expectation or an निश्चितion.
 */
क्रमागत kunit_निश्चित_type अणु
	KUNIT_ASSERTION,
	KUNIT_EXPECTATION,
पूर्ण;

/**
 * काष्ठा kunit_निश्चित - Data क्रम prपूर्णांकing a failed निश्चितion or expectation.
 * @test: the test हाल this expectation/निश्चितion is associated with.
 * @type: the type (either an expectation or an निश्चितion) of this kunit_निश्चित.
 * @line: the source code line number that the expectation/निश्चितion is at.
 * @file: the file path of the source file that the expectation/निश्चितion is in.
 * @message: an optional message to provide additional context.
 * @क्रमmat: a function which क्रमmats the data in this kunit_निश्चित to a string.
 *
 * Represents a failed expectation/निश्चितion. Contains all the data necessary to
 * क्रमmat a string to a user reporting the failure.
 */
काष्ठा kunit_निश्चित अणु
	काष्ठा kunit *test;
	क्रमागत kunit_निश्चित_type type;
	पूर्णांक line;
	स्थिर अक्षर *file;
	काष्ठा va_क्रमmat message;
	व्योम (*क्रमmat)(स्थिर काष्ठा kunit_निश्चित *निश्चित,
		       काष्ठा string_stream *stream);
पूर्ण;

/**
 * KUNIT_INIT_VA_FMT_शून्य - Default initializer क्रम काष्ठा va_क्रमmat.
 *
 * Used inside a काष्ठा initialization block to initialize काष्ठा va_क्रमmat to
 * शेष values where fmt and va are null.
 */
#घोषणा KUNIT_INIT_VA_FMT_शून्य अणु .fmt = शून्य, .va = शून्य पूर्ण

/**
 * KUNIT_INIT_ASSERT_STRUCT() - Initializer क्रम a &काष्ठा kunit_निश्चित.
 * @kunit: The test हाल that this expectation/निश्चितion is associated with.
 * @निश्चित_type: The type (निश्चितion or expectation) of this kunit_निश्चित.
 * @fmt: The क्रमmatting function which builds a string out of this kunit_निश्चित.
 *
 * The base initializer क्रम a &काष्ठा kunit_निश्चित.
 */
#घोषणा KUNIT_INIT_ASSERT_STRUCT(kunit, निश्चित_type, fmt) अणु		       \
	.test = kunit,							       \
	.type = निश्चित_type,						       \
	.file = __खाता__,						       \
	.line = __LINE__,						       \
	.message = KUNIT_INIT_VA_FMT_शून्य,				       \
	.क्रमmat = fmt							       \
पूर्ण

व्योम kunit_base_निश्चित_क्रमmat(स्थिर काष्ठा kunit_निश्चित *निश्चित,
			      काष्ठा string_stream *stream);

व्योम kunit_निश्चित_prपूर्णांक_msg(स्थिर काष्ठा kunit_निश्चित *निश्चित,
			    काष्ठा string_stream *stream);

/**
 * काष्ठा kunit_fail_निश्चित - Represents a plain fail expectation/निश्चितion.
 * @निश्चित: The parent of this type.
 *
 * Represents a simple KUNIT_FAIL/KUNIT_ASSERT_FAILURE that always fails.
 */
काष्ठा kunit_fail_निश्चित अणु
	काष्ठा kunit_निश्चित निश्चित;
पूर्ण;

व्योम kunit_fail_निश्चित_क्रमmat(स्थिर काष्ठा kunit_निश्चित *निश्चित,
			      काष्ठा string_stream *stream);

/**
 * KUNIT_INIT_FAIL_ASSERT_STRUCT() - Initializer क्रम &काष्ठा kunit_fail_निश्चित.
 * @test: The test हाल that this expectation/निश्चितion is associated with.
 * @type: The type (निश्चितion or expectation) of this kunit_निश्चित.
 *
 * Initializes a &काष्ठा kunit_fail_निश्चित. Intended to be used in
 * KUNIT_EXPECT_* and KUNIT_ASSERT_* macros.
 */
#घोषणा KUNIT_INIT_FAIL_ASSERT_STRUCT(test, type) अणु			       \
	.निश्चित = KUNIT_INIT_ASSERT_STRUCT(test,			       \
					   type,			       \
					   kunit_fail_निश्चित_क्रमmat)	       \
पूर्ण

/**
 * काष्ठा kunit_unary_निश्चित - Represents a KUNIT_अणुEXPECT|ASSERTपूर्ण_अणुTRUE|FALSEपूर्ण
 * @निश्चित: The parent of this type.
 * @condition: A string representation of a conditional expression.
 * @expected_true: True अगर of type KUNIT_अणुEXPECT|ASSERTपूर्ण_TRUE, false otherwise.
 *
 * Represents a simple expectation or निश्चितion that simply निश्चितs something is
 * true or false. In other words, represents the expectations:
 * KUNIT_अणुEXPECT|ASSERTपूर्ण_अणुTRUE|FALSEपूर्ण
 */
काष्ठा kunit_unary_निश्चित अणु
	काष्ठा kunit_निश्चित निश्चित;
	स्थिर अक्षर *condition;
	bool expected_true;
पूर्ण;

व्योम kunit_unary_निश्चित_क्रमmat(स्थिर काष्ठा kunit_निश्चित *निश्चित,
			       काष्ठा string_stream *stream);

/**
 * KUNIT_INIT_UNARY_ASSERT_STRUCT() - Initializes &काष्ठा kunit_unary_निश्चित.
 * @test: The test हाल that this expectation/निश्चितion is associated with.
 * @type: The type (निश्चितion or expectation) of this kunit_निश्चित.
 * @cond: A string representation of the expression निश्चितed true or false.
 * @expect_true: True अगर of type KUNIT_अणुEXPECT|ASSERTपूर्ण_TRUE, false otherwise.
 *
 * Initializes a &काष्ठा kunit_unary_निश्चित. Intended to be used in
 * KUNIT_EXPECT_* and KUNIT_ASSERT_* macros.
 */
#घोषणा KUNIT_INIT_UNARY_ASSERT_STRUCT(test, type, cond, expect_true) अणु	       \
	.निश्चित = KUNIT_INIT_ASSERT_STRUCT(test,			       \
					   type,			       \
					   kunit_unary_निश्चित_क्रमmat),	       \
	.condition = cond,						       \
	.expected_true = expect_true					       \
पूर्ण

/**
 * काष्ठा kunit_ptr_not_err_निश्चित - An expectation/निश्चितion that a poपूर्णांकer is
 *	not शून्य and not a -त्रुटि_सं.
 * @निश्चित: The parent of this type.
 * @text: A string representation of the expression passed to the expectation.
 * @value: The actual evaluated poपूर्णांकer value of the expression.
 *
 * Represents an expectation/निश्चितion that a poपूर्णांकer is not null and is करोes
 * not contain a -त्रुटि_सं. (See IS_ERR_OR_शून्य().)
 */
काष्ठा kunit_ptr_not_err_निश्चित अणु
	काष्ठा kunit_निश्चित निश्चित;
	स्थिर अक्षर *text;
	स्थिर व्योम *value;
पूर्ण;

व्योम kunit_ptr_not_err_निश्चित_क्रमmat(स्थिर काष्ठा kunit_निश्चित *निश्चित,
				     काष्ठा string_stream *stream);

/**
 * KUNIT_INIT_PTR_NOT_ERR_ASSERT_STRUCT() - Initializes a
 *	&काष्ठा kunit_ptr_not_err_निश्चित.
 * @test: The test हाल that this expectation/निश्चितion is associated with.
 * @type: The type (निश्चितion or expectation) of this kunit_निश्चित.
 * @txt: A string representation of the expression passed to the expectation.
 * @val: The actual evaluated poपूर्णांकer value of the expression.
 *
 * Initializes a &काष्ठा kunit_ptr_not_err_निश्चित. Intended to be used in
 * KUNIT_EXPECT_* and KUNIT_ASSERT_* macros.
 */
#घोषणा KUNIT_INIT_PTR_NOT_ERR_STRUCT(test, type, txt, val) अणु		       \
	.निश्चित = KUNIT_INIT_ASSERT_STRUCT(test,			       \
					   type,			       \
					   kunit_ptr_not_err_निश्चित_क्रमmat),   \
	.text = txt,							       \
	.value = val							       \
पूर्ण

/**
 * काष्ठा kunit_binary_निश्चित - An expectation/निश्चितion that compares two
 *	non-poपूर्णांकer values (क्रम example, KUNIT_EXPECT_EQ(test, 1 + 1, 2)).
 * @निश्चित: The parent of this type.
 * @operation: A string representation of the comparison चालक (e.g. "==").
 * @left_text: A string representation of the expression in the left slot.
 * @left_value: The actual evaluated value of the expression in the left slot.
 * @right_text: A string representation of the expression in the right slot.
 * @right_value: The actual evaluated value of the expression in the right slot.
 *
 * Represents an expectation/निश्चितion that compares two non-poपूर्णांकer values. For
 * example, to expect that 1 + 1 == 2, you can use the expectation
 * KUNIT_EXPECT_EQ(test, 1 + 1, 2);
 */
काष्ठा kunit_binary_निश्चित अणु
	काष्ठा kunit_निश्चित निश्चित;
	स्थिर अक्षर *operation;
	स्थिर अक्षर *left_text;
	दीर्घ दीर्घ left_value;
	स्थिर अक्षर *right_text;
	दीर्घ दीर्घ right_value;
पूर्ण;

व्योम kunit_binary_निश्चित_क्रमmat(स्थिर काष्ठा kunit_निश्चित *निश्चित,
				काष्ठा string_stream *stream);

/**
 * KUNIT_INIT_BINARY_ASSERT_STRUCT() - Initializes a
 *	&काष्ठा kunit_binary_निश्चित.
 * @test: The test हाल that this expectation/निश्चितion is associated with.
 * @type: The type (निश्चितion or expectation) of this kunit_निश्चित.
 * @op_str: A string representation of the comparison चालक (e.g. "==").
 * @left_str: A string representation of the expression in the left slot.
 * @left_val: The actual evaluated value of the expression in the left slot.
 * @right_str: A string representation of the expression in the right slot.
 * @right_val: The actual evaluated value of the expression in the right slot.
 *
 * Initializes a &काष्ठा kunit_binary_निश्चित. Intended to be used in
 * KUNIT_EXPECT_* and KUNIT_ASSERT_* macros.
 */
#घोषणा KUNIT_INIT_BINARY_ASSERT_STRUCT(test,				       \
					type,				       \
					op_str,				       \
					left_str,			       \
					left_val,			       \
					right_str,			       \
					right_val) अणु			       \
	.निश्चित = KUNIT_INIT_ASSERT_STRUCT(test,			       \
					   type,			       \
					   kunit_binary_निश्चित_क्रमmat),	       \
	.operation = op_str,						       \
	.left_text = left_str,						       \
	.left_value = left_val,						       \
	.right_text = right_str,					       \
	.right_value = right_val					       \
पूर्ण

/**
 * काष्ठा kunit_binary_ptr_निश्चित - An expectation/निश्चितion that compares two
 *	poपूर्णांकer values (क्रम example, KUNIT_EXPECT_PTR_EQ(test, foo, bar)).
 * @निश्चित: The parent of this type.
 * @operation: A string representation of the comparison चालक (e.g. "==").
 * @left_text: A string representation of the expression in the left slot.
 * @left_value: The actual evaluated value of the expression in the left slot.
 * @right_text: A string representation of the expression in the right slot.
 * @right_value: The actual evaluated value of the expression in the right slot.
 *
 * Represents an expectation/निश्चितion that compares two poपूर्णांकer values. For
 * example, to expect that foo and bar poपूर्णांक to the same thing, you can use the
 * expectation KUNIT_EXPECT_PTR_EQ(test, foo, bar);
 */
काष्ठा kunit_binary_ptr_निश्चित अणु
	काष्ठा kunit_निश्चित निश्चित;
	स्थिर अक्षर *operation;
	स्थिर अक्षर *left_text;
	स्थिर व्योम *left_value;
	स्थिर अक्षर *right_text;
	स्थिर व्योम *right_value;
पूर्ण;

व्योम kunit_binary_ptr_निश्चित_क्रमmat(स्थिर काष्ठा kunit_निश्चित *निश्चित,
				    काष्ठा string_stream *stream);

/**
 * KUNIT_INIT_BINARY_PTR_ASSERT_STRUCT() - Initializes a
 *	&काष्ठा kunit_binary_ptr_निश्चित.
 * @test: The test हाल that this expectation/निश्चितion is associated with.
 * @type: The type (निश्चितion or expectation) of this kunit_निश्चित.
 * @op_str: A string representation of the comparison चालक (e.g. "==").
 * @left_str: A string representation of the expression in the left slot.
 * @left_val: The actual evaluated value of the expression in the left slot.
 * @right_str: A string representation of the expression in the right slot.
 * @right_val: The actual evaluated value of the expression in the right slot.
 *
 * Initializes a &काष्ठा kunit_binary_ptr_निश्चित. Intended to be used in
 * KUNIT_EXPECT_* and KUNIT_ASSERT_* macros.
 */
#घोषणा KUNIT_INIT_BINARY_PTR_ASSERT_STRUCT(test,			       \
					    type,			       \
					    op_str,			       \
					    left_str,			       \
					    left_val,			       \
					    right_str,			       \
					    right_val) अणु		       \
	.निश्चित = KUNIT_INIT_ASSERT_STRUCT(test,			       \
					   type,			       \
					   kunit_binary_ptr_निश्चित_क्रमmat),    \
	.operation = op_str,						       \
	.left_text = left_str,						       \
	.left_value = left_val,						       \
	.right_text = right_str,					       \
	.right_value = right_val					       \
पूर्ण

/**
 * काष्ठा kunit_binary_str_निश्चित - An expectation/निश्चितion that compares two
 *	string values (क्रम example, KUNIT_EXPECT_STREQ(test, foo, "bar")).
 * @निश्चित: The parent of this type.
 * @operation: A string representation of the comparison चालक (e.g. "==").
 * @left_text: A string representation of the expression in the left slot.
 * @left_value: The actual evaluated value of the expression in the left slot.
 * @right_text: A string representation of the expression in the right slot.
 * @right_value: The actual evaluated value of the expression in the right slot.
 *
 * Represents an expectation/निश्चितion that compares two string values. For
 * example, to expect that the string in foo is equal to "bar", you can use the
 * expectation KUNIT_EXPECT_STREQ(test, foo, "bar");
 */
काष्ठा kunit_binary_str_निश्चित अणु
	काष्ठा kunit_निश्चित निश्चित;
	स्थिर अक्षर *operation;
	स्थिर अक्षर *left_text;
	स्थिर अक्षर *left_value;
	स्थिर अक्षर *right_text;
	स्थिर अक्षर *right_value;
पूर्ण;

व्योम kunit_binary_str_निश्चित_क्रमmat(स्थिर काष्ठा kunit_निश्चित *निश्चित,
				    काष्ठा string_stream *stream);

/**
 * KUNIT_INIT_BINARY_STR_ASSERT_STRUCT() - Initializes a
 *	&काष्ठा kunit_binary_str_निश्चित.
 * @test: The test हाल that this expectation/निश्चितion is associated with.
 * @type: The type (निश्चितion or expectation) of this kunit_निश्चित.
 * @op_str: A string representation of the comparison चालक (e.g. "==").
 * @left_str: A string representation of the expression in the left slot.
 * @left_val: The actual evaluated value of the expression in the left slot.
 * @right_str: A string representation of the expression in the right slot.
 * @right_val: The actual evaluated value of the expression in the right slot.
 *
 * Initializes a &काष्ठा kunit_binary_str_निश्चित. Intended to be used in
 * KUNIT_EXPECT_* and KUNIT_ASSERT_* macros.
 */
#घोषणा KUNIT_INIT_BINARY_STR_ASSERT_STRUCT(test,			       \
					    type,			       \
					    op_str,			       \
					    left_str,			       \
					    left_val,			       \
					    right_str,			       \
					    right_val) अणु		       \
	.निश्चित = KUNIT_INIT_ASSERT_STRUCT(test,			       \
					   type,			       \
					   kunit_binary_str_निश्चित_क्रमmat),    \
	.operation = op_str,						       \
	.left_text = left_str,						       \
	.left_value = left_val,						       \
	.right_text = right_str,					       \
	.right_value = right_val					       \
पूर्ण

#पूर्ण_अगर /*  _KUNIT_ASSERT_H */
