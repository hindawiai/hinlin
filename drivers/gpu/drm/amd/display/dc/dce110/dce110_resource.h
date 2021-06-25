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

#अगर_अघोषित __DC_RESOURCE_DCE110_H__
#घोषणा __DC_RESOURCE_DCE110_H__

#समावेश "core_types.h"

काष्ठा dc;
काष्ठा resource_pool;

#घोषणा TO_DCE110_RES_POOL(pool)\
	container_of(pool, काष्ठा dce110_resource_pool, base)

काष्ठा dce110_resource_pool अणु
	काष्ठा resource_pool base;
पूर्ण;

व्योम dce110_resource_build_pipe_hw_param(काष्ठा pipe_ctx *pipe_ctx);

काष्ठा resource_pool *dce110_create_resource_pool(
	uपूर्णांक8_t num_भव_links,
	काष्ठा dc *dc,
	काष्ठा hw_asic_id asic_id);

काष्ठा stream_encoder *dce110_find_first_मुक्त_match_stream_enc_क्रम_link(
		काष्ठा resource_context *res_ctx,
		स्थिर काष्ठा resource_pool *pool,
		काष्ठा dc_stream_state *stream);

#पूर्ण_अगर /* __DC_RESOURCE_DCE110_H__ */

