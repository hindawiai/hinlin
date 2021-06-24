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

#अगर_अघोषित __DC_HWSS_DCN10_DEBUG_H__
#घोषणा __DC_HWSS_DCN10_DEBUG_H__

#समावेश "core_types.h"

काष्ठा dc;

व्योम dcn10_clear_status_bits(काष्ठा dc *dc, अचिन्हित पूर्णांक mask);

व्योम dcn10_log_hw_state(काष्ठा dc *dc,
		काष्ठा dc_log_buffer_ctx *log_ctx);

व्योम dcn10_get_hw_state(काष्ठा dc *dc,
		अक्षर *pBuf,
		अचिन्हित पूर्णांक bufSize,
		अचिन्हित पूर्णांक mask);

#पूर्ण_अगर /* __DC_HWSS_DCN10_DEBUG_H__ */
