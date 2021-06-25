<शैली गुरु>
/*
 * Copyright 2017 Advanced Micro Devices, Inc.
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
 *
 */
/*
 * dce100_resource.h
 *
 *  Created on: 2016-01-20
 *      Author: qyang
 */

#अगर_अघोषित DCE100_RESOURCE_H_
#घोषणा DCE100_RESOURCE_H_

काष्ठा dc;
काष्ठा resource_pool;
काष्ठा dc_validation_set;

काष्ठा resource_pool *dce100_create_resource_pool(
	uपूर्णांक8_t num_भव_links,
	काष्ठा dc *dc);

क्रमागत dc_status dce100_validate_plane(स्थिर काष्ठा dc_plane_state *plane_state, काष्ठा dc_caps *caps);

क्रमागत dc_status dce100_add_stream_to_ctx(
		काष्ठा dc *dc,
		काष्ठा dc_state *new_ctx,
		काष्ठा dc_stream_state *dc_stream);

काष्ठा stream_encoder *dce100_find_first_मुक्त_match_stream_enc_क्रम_link(
		काष्ठा resource_context *res_ctx,
		स्थिर काष्ठा resource_pool *pool,
		काष्ठा dc_stream_state *stream);

#पूर्ण_अगर /* DCE100_RESOURCE_H_ */
