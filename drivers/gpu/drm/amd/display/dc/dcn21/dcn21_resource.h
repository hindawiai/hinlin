<शैली गुरु>
/*
 * Copyright 2018 Advanced Micro Devices, Inc.
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

#अगर_अघोषित _DCN21_RESOURCE_H_
#घोषणा _DCN21_RESOURCE_H_

#समावेश "core_types.h"

#घोषणा TO_DCN21_RES_POOL(pool)\
	container_of(pool, काष्ठा dcn21_resource_pool, base)

काष्ठा dc;
काष्ठा resource_pool;
काष्ठा _vcs_dpi_display_pipe_params_st;

काष्ठा dcn21_resource_pool अणु
	काष्ठा resource_pool base;
पूर्ण;
काष्ठा resource_pool *dcn21_create_resource_pool(
		स्थिर काष्ठा dc_init_data *init_data,
		काष्ठा dc *dc);

#पूर्ण_अगर /* _DCN21_RESOURCE_H_ */
