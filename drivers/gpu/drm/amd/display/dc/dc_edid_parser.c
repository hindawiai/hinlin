<शैली गुरु>
/*
 * Copyright 2021 Advanced Micro Devices, Inc.
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

#समावेश "dce/dce_dmcu.h"
#समावेश "dc_edid_parser.h"

bool dc_edid_parser_send_cea(काष्ठा dc *dc,
		पूर्णांक offset,
		पूर्णांक total_length,
		uपूर्णांक8_t *data,
		पूर्णांक length)
अणु
	काष्ठा dmcu *dmcu = dc->res_pool->dmcu;

	अगर (dmcu &&
	    dmcu->funcs->is_dmcu_initialized(dmcu) &&
	    dmcu->funcs->send_edid_cea) अणु
		वापस dmcu->funcs->send_edid_cea(dmcu,
				offset,
				total_length,
				data,
				length);
	पूर्ण

	वापस false;
पूर्ण

bool dc_edid_parser_recv_cea_ack(काष्ठा dc *dc, पूर्णांक *offset)
अणु
	काष्ठा dmcu *dmcu = dc->res_pool->dmcu;

	अगर (dmcu &&
	    dmcu->funcs->is_dmcu_initialized(dmcu) &&
	    dmcu->funcs->recv_edid_cea_ack) अणु
		वापस dmcu->funcs->recv_edid_cea_ack(dmcu, offset);
	पूर्ण

	वापस false;
पूर्ण

bool dc_edid_parser_recv_amd_vsdb(काष्ठा dc *dc,
		पूर्णांक *version,
		पूर्णांक *min_frame_rate,
		पूर्णांक *max_frame_rate)
अणु
	काष्ठा dmcu *dmcu = dc->res_pool->dmcu;

	अगर (dmcu &&
	    dmcu->funcs->is_dmcu_initialized(dmcu) &&
	    dmcu->funcs->recv_amd_vsdb) अणु
		वापस dmcu->funcs->recv_amd_vsdb(dmcu,
				version,
				min_frame_rate,
				max_frame_rate);
	पूर्ण

	वापस false;
पूर्ण
