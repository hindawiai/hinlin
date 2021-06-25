<शैली गुरु>
/*
 * Copyright 2019 Advanced Micro Devices, Inc.
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

#समावेश "color_table.h"

अटल काष्ठा fixed31_32 pq_table[MAX_HW_POINTS + 2];
अटल काष्ठा fixed31_32 de_pq_table[MAX_HW_POINTS + 2];
अटल bool pq_initialized;
अटल bool de_pg_initialized;

bool mod_color_is_table_init(क्रमागत table_type type)
अणु
	bool ret = false;

	अगर (type == type_pq_table)
		ret = pq_initialized;
	अगर (type == type_de_pq_table)
		ret = de_pg_initialized;

	वापस ret;
पूर्ण

काष्ठा fixed31_32 *mod_color_get_table(क्रमागत table_type type)
अणु
	काष्ठा fixed31_32 *table = शून्य;

	अगर (type == type_pq_table)
		table = pq_table;
	अगर (type == type_de_pq_table)
		table = de_pq_table;

	वापस table;
पूर्ण

व्योम mod_color_set_table_init_state(क्रमागत table_type type, bool state)
अणु
	अगर (type == type_pq_table)
		pq_initialized = state;
	अगर (type == type_de_pq_table)
		de_pg_initialized = state;
पूर्ण

