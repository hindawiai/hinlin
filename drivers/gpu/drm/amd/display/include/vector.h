<शैली गुरु>
/*
 * Copyright 2012-15 Advanced Micro Devices, Inc.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Authors: AMD
 *
 */

#अगर_अघोषित __DAL_VECTOR_H__
#घोषणा __DAL_VECTOR_H__

काष्ठा vector अणु
	uपूर्णांक8_t *container;
	uपूर्णांक32_t काष्ठा_size;
	uपूर्णांक32_t count;
	uपूर्णांक32_t capacity;
	काष्ठा dc_context *ctx;
पूर्ण;

bool dal_vector_स्थिरruct(
	काष्ठा vector *vector,
	काष्ठा dc_context *ctx,
	uपूर्णांक32_t capacity,
	uपूर्णांक32_t काष्ठा_size);

काष्ठा vector *dal_vector_create(
	काष्ठा dc_context *ctx,
	uपूर्णांक32_t capacity,
	uपूर्णांक32_t काष्ठा_size);

/* 'initial_value' is optional. If initial_value not supplied,
 * each "structure" in the vector will contain zeros by शेष. */
काष्ठा vector *dal_vector_presized_create(
	काष्ठा dc_context *ctx,
	uपूर्णांक32_t size,
	व्योम *initial_value,
	uपूर्णांक32_t काष्ठा_size);

व्योम dal_vector_deकाष्ठा(
	काष्ठा vector *vector);

व्योम dal_vector_destroy(
	काष्ठा vector **vector);

uपूर्णांक32_t dal_vector_get_count(
	स्थिर काष्ठा vector *vector);

/* dal_vector_insert_at
 * पुनः_स्मृतिate container अगर necessary
 * then shell items at right and insert
 * वापस अगर the container modअगरied
 * करो not check that index beदीर्घs to container
 * since the function is निजी and index is going to be calculated
 * either with by function or as get_count+1 */
bool dal_vector_insert_at(
	काष्ठा vector *vector,
	स्थिर व्योम *what,
	uपूर्णांक32_t position);

bool dal_vector_append(
	काष्ठा vector *vector,
	स्थिर व्योम *item);

/* चालक[] */
व्योम *dal_vector_at_index(
	स्थिर काष्ठा vector *vector,
	uपूर्णांक32_t index);

व्योम dal_vector_set_at_index(
	स्थिर काष्ठा vector *vector,
	स्थिर व्योम *what,
	uपूर्णांक32_t index);

/* create a clone (copy) of a vector */
काष्ठा vector *dal_vector_clone(
	स्थिर काष्ठा vector *vector_other);

/* dal_vector_हटाओ_at_index
 * Shअगरts elements on the right from हटाओ position to the left,
 * removing an element at position by overग_लिखो means*/
bool dal_vector_हटाओ_at_index(
	काष्ठा vector *vector,
	uपूर्णांक32_t index);

uपूर्णांक32_t dal_vector_capacity(स्थिर काष्ठा vector *vector);

bool dal_vector_reserve(काष्ठा vector *vector, uपूर्णांक32_t capacity);

व्योम dal_vector_clear(काष्ठा vector *vector);

/***************************************************************************
 * Macro definitions of TYPE-SAFE versions of vector set/get functions.
 ***************************************************************************/

#घोषणा DAL_VECTOR_INSERT_AT(vector_type, type_t) \
	अटल bool vector_type##_vector_insert_at( \
		काष्ठा vector *vector, \
		type_t what, \
		uपूर्णांक32_t position) \
अणु \
	वापस dal_vector_insert_at(vector, what, position); \
पूर्ण

#घोषणा DAL_VECTOR_APPEND(vector_type, type_t) \
	अटल bool vector_type##_vector_append( \
		काष्ठा vector *vector, \
		type_t item) \
अणु \
	वापस dal_vector_append(vector, item); \
पूर्ण

/* Note: "type_t" is the ONLY token accepted by "checkpatch.pl" and by
 * "checkcommit" as *वापस type*.
 * For unअगरormity reasons "type_t" is used क्रम all type-safe macro
 * definitions here. */
#घोषणा DAL_VECTOR_AT_INDEX(vector_type, type_t) \
	अटल type_t vector_type##_vector_at_index( \
		स्थिर काष्ठा vector *vector, \
		uपूर्णांक32_t index) \
अणु \
	वापस dal_vector_at_index(vector, index); \
पूर्ण

#घोषणा DAL_VECTOR_SET_AT_INDEX(vector_type, type_t) \
	अटल व्योम vector_type##_vector_set_at_index( \
		स्थिर काष्ठा vector *vector, \
		type_t what, \
		uपूर्णांक32_t index) \
अणु \
	dal_vector_set_at_index(vector, what, index); \
पूर्ण

#पूर्ण_अगर /* __DAL_VECTOR_H__ */
