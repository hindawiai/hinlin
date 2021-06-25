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

#अगर_अघोषित __DC_RESOURCE_DCE112_H__
#घोषणा __DC_RESOURCE_DCE112_H__

#समावेश "core_types.h"

काष्ठा dc;
काष्ठा resource_pool;

काष्ठा resource_pool *dce112_create_resource_pool(
	uपूर्णांक8_t num_भव_links,
	काष्ठा dc *dc);

क्रमागत dc_status dce112_validate_with_context(
		काष्ठा dc *dc,
		स्थिर काष्ठा dc_validation_set set[],
		पूर्णांक set_count,
		काष्ठा dc_state *context,
		काष्ठा dc_state *old_context);

bool dce112_validate_bandwidth(
	काष्ठा dc *dc,
	काष्ठा dc_state *context,
	bool fast_validate);

क्रमागत dc_status dce112_add_stream_to_ctx(
		काष्ठा dc *dc,
		काष्ठा dc_state *new_ctx,
		काष्ठा dc_stream_state *dc_stream);


#पूर्ण_अगर /* __DC_RESOURCE_DCE112_H__ */

