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

#समावेश <linux/slab.h>

#समावेश "dm_services.h"
#समावेश "include/vector.h"

bool dal_vector_स्थिरruct(
	काष्ठा vector *vector,
	काष्ठा dc_context *ctx,
	uपूर्णांक32_t capacity,
	uपूर्णांक32_t काष्ठा_size)
अणु
	vector->container = शून्य;

	अगर (!काष्ठा_size || !capacity) अणु
		/* Container must be non-zero size*/
		BREAK_TO_DEBUGGER();
		वापस false;
	पूर्ण

	vector->container = kसुस्मृति(capacity, काष्ठा_size, GFP_KERNEL);
	अगर (vector->container == शून्य)
		वापस false;
	vector->capacity = capacity;
	vector->काष्ठा_size = काष्ठा_size;
	vector->count = 0;
	vector->ctx = ctx;
	वापस true;
पूर्ण

अटल bool dal_vector_presized_coकाष्ठा(
	काष्ठा vector *vector,
	काष्ठा dc_context *ctx,
	uपूर्णांक32_t count,
	व्योम *initial_value,
	uपूर्णांक32_t काष्ठा_size)
अणु
	uपूर्णांक32_t i;

	vector->container = शून्य;

	अगर (!काष्ठा_size || !count) अणु
		/* Container must be non-zero size*/
		BREAK_TO_DEBUGGER();
		वापस false;
	पूर्ण

	vector->container = kसुस्मृति(count, काष्ठा_size, GFP_KERNEL);

	अगर (vector->container == शून्य)
		वापस false;

	/* If caller didn't supply initial value then the शेष
	 * of all zeros is expected, which is exactly what dal_alloc()
	 * initialises the memory to. */
	अगर (शून्य != initial_value) अणु
		क्रम (i = 0; i < count; ++i)
			स_हटाओ(
				vector->container + i * काष्ठा_size,
				initial_value,
				काष्ठा_size);
	पूर्ण

	vector->capacity = count;
	vector->काष्ठा_size = काष्ठा_size;
	vector->count = count;
	वापस true;
पूर्ण

काष्ठा vector *dal_vector_presized_create(
	काष्ठा dc_context *ctx,
	uपूर्णांक32_t size,
	व्योम *initial_value,
	uपूर्णांक32_t काष्ठा_size)
अणु
	काष्ठा vector *vector = kzalloc(माप(काष्ठा vector), GFP_KERNEL);

	अगर (vector == शून्य)
		वापस शून्य;

	अगर (dal_vector_presized_coकाष्ठा(
		vector, ctx, size, initial_value, काष्ठा_size))
		वापस vector;

	BREAK_TO_DEBUGGER();
	kमुक्त(vector);
	वापस शून्य;
पूर्ण

काष्ठा vector *dal_vector_create(
	काष्ठा dc_context *ctx,
	uपूर्णांक32_t capacity,
	uपूर्णांक32_t काष्ठा_size)
अणु
	काष्ठा vector *vector = kzalloc(माप(काष्ठा vector), GFP_KERNEL);

	अगर (vector == शून्य)
		वापस शून्य;

	अगर (dal_vector_स्थिरruct(vector, ctx, capacity, काष्ठा_size))
		वापस vector;

	BREAK_TO_DEBUGGER();
	kमुक्त(vector);
	वापस शून्य;
पूर्ण

व्योम dal_vector_deकाष्ठा(
	काष्ठा vector *vector)
अणु
	kमुक्त(vector->container);
	vector->count = 0;
	vector->capacity = 0;
पूर्ण

व्योम dal_vector_destroy(
	काष्ठा vector **vector)
अणु
	अगर (vector == शून्य || *vector == शून्य)
		वापस;
	dal_vector_deकाष्ठा(*vector);
	kमुक्त(*vector);
	*vector = शून्य;
पूर्ण

uपूर्णांक32_t dal_vector_get_count(
	स्थिर काष्ठा vector *vector)
अणु
	वापस vector->count;
पूर्ण

व्योम *dal_vector_at_index(
	स्थिर काष्ठा vector *vector,
	uपूर्णांक32_t index)
अणु
	अगर (vector->container == शून्य || index >= vector->count)
		वापस शून्य;
	वापस vector->container + (index * vector->काष्ठा_size);
पूर्ण

bool dal_vector_हटाओ_at_index(
	काष्ठा vector *vector,
	uपूर्णांक32_t index)
अणु
	अगर (index >= vector->count)
		वापस false;

	अगर (index != vector->count - 1)
		स_हटाओ(
			vector->container + (index * vector->काष्ठा_size),
			vector->container + ((index + 1) * vector->काष्ठा_size),
			(vector->count - index - 1) * vector->काष्ठा_size);
	vector->count -= 1;

	वापस true;
पूर्ण

व्योम dal_vector_set_at_index(
	स्थिर काष्ठा vector *vector,
	स्थिर व्योम *what,
	uपूर्णांक32_t index)
अणु
	व्योम *where = dal_vector_at_index(vector, index);

	अगर (!where) अणु
		BREAK_TO_DEBUGGER();
		वापस;
	पूर्ण
	स_हटाओ(
		where,
		what,
		vector->काष्ठा_size);
पूर्ण

अटल अंतरभूत uपूर्णांक32_t calc_increased_capacity(
	uपूर्णांक32_t old_capacity)
अणु
	वापस old_capacity * 2;
पूर्ण

bool dal_vector_insert_at(
	काष्ठा vector *vector,
	स्थिर व्योम *what,
	uपूर्णांक32_t position)
अणु
	uपूर्णांक8_t *insert_address;

	अगर (vector->count == vector->capacity) अणु
		अगर (!dal_vector_reserve(
			vector,
			calc_increased_capacity(vector->capacity)))
			वापस false;
	पूर्ण

	insert_address = vector->container + (vector->काष्ठा_size * position);

	अगर (vector->count && position < vector->count)
		स_हटाओ(
			insert_address + vector->काष्ठा_size,
			insert_address,
			vector->काष्ठा_size * (vector->count - position));

	स_हटाओ(
		insert_address,
		what,
		vector->काष्ठा_size);

	vector->count++;

	वापस true;
पूर्ण

bool dal_vector_append(
	काष्ठा vector *vector,
	स्थिर व्योम *item)
अणु
	वापस dal_vector_insert_at(vector, item, vector->count);
पूर्ण

काष्ठा vector *dal_vector_clone(
	स्थिर काष्ठा vector *vector)
अणु
	काष्ठा vector *vec_cloned;
	uपूर्णांक32_t count;

	/* create new vector */
	count = dal_vector_get_count(vector);

	अगर (count == 0)
		/* when count is 0 we still want to create clone of the vector
		 */
		vec_cloned = dal_vector_create(
			vector->ctx,
			vector->capacity,
			vector->काष्ठा_size);
	अन्यथा
		/* Call "presized create" version, independently of how the
		 * original vector was created.
		 * The owner of original vector must know how to treat the new
		 * vector - as "presized" or as "regular".
		 * But from vector poपूर्णांक of view it करोesn't matter. */
		vec_cloned = dal_vector_presized_create(vector->ctx, count,
			शून्य,/* no initial value */
			vector->काष्ठा_size);

	अगर (शून्य == vec_cloned) अणु
		BREAK_TO_DEBUGGER();
		वापस शून्य;
	पूर्ण

	/* copy vector's data */
	स_हटाओ(vec_cloned->container, vector->container,
			vec_cloned->काष्ठा_size * vec_cloned->capacity);

	वापस vec_cloned;
पूर्ण

uपूर्णांक32_t dal_vector_capacity(स्थिर काष्ठा vector *vector)
अणु
	वापस vector->capacity;
पूर्ण

bool dal_vector_reserve(काष्ठा vector *vector, uपूर्णांक32_t capacity)
अणु
	व्योम *new_container;

	अगर (capacity <= vector->capacity)
		वापस true;

	new_container = kपुनः_स्मृति(vector->container,
				 capacity * vector->काष्ठा_size, GFP_KERNEL);

	अगर (new_container) अणु
		vector->container = new_container;
		vector->capacity = capacity;
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

व्योम dal_vector_clear(काष्ठा vector *vector)
अणु
	vector->count = 0;
पूर्ण
