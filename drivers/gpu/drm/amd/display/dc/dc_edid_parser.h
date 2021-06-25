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

#अगर_अघोषित _DC_EDID_PARSER_H_
#घोषणा _DC_EDID_PARSER_H_

#समावेश "core_types.h"

bool dc_edid_parser_send_cea(काष्ठा dc *dc,
		पूर्णांक offset,
		पूर्णांक total_length,
		uपूर्णांक8_t *data,
		पूर्णांक length);

bool dc_edid_parser_recv_cea_ack(काष्ठा dc *dc, पूर्णांक *offset);

bool dc_edid_parser_recv_amd_vsdb(काष्ठा dc *dc,
		पूर्णांक *version,
		पूर्णांक *min_frame_rate,
		पूर्णांक *max_frame_rate);

#पूर्ण_अगर /* _DC_EDID_PARSER_H_ */
