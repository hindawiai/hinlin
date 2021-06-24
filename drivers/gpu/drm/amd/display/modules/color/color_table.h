<शैली गुरु>
/*
 * Copyright 2016 Advanced Micro Devices, Inc.
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


#अगर_अघोषित COLOR_MOD_COLOR_TABLE_H_
#घोषणा COLOR_MOD_COLOR_TABLE_H_

#समावेश "dc_types.h"

#घोषणा NUM_PTS_IN_REGION 16
#घोषणा NUM_REGIONS 32
#घोषणा MAX_HW_POINTS (NUM_PTS_IN_REGION*NUM_REGIONS)

क्रमागत table_type अणु
	type_pq_table,
	type_de_pq_table
पूर्ण;

bool mod_color_is_table_init(क्रमागत table_type type);

काष्ठा fixed31_32 *mod_color_get_table(क्रमागत table_type type);

व्योम mod_color_set_table_init_state(क्रमागत table_type type, bool state);

#पूर्ण_अगर /* COLOR_MOD_COLOR_TABLE_H_ */
