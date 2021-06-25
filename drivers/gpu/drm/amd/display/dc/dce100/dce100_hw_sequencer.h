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

#अगर_अघोषित __DC_HWSS_DCE100_H__
#घोषणा __DC_HWSS_DCE100_H__

#समावेश "core_types.h"
#समावेश "hw_sequencer_private.h"

काष्ठा dc;
काष्ठा dc_state;

व्योम dce100_hw_sequencer_स्थिरruct(काष्ठा dc *dc);

व्योम dce100_prepare_bandwidth(
		काष्ठा dc *dc,
		काष्ठा dc_state *context);

व्योम dce100_optimize_bandwidth(
		काष्ठा dc *dc,
		काष्ठा dc_state *context);

bool dce100_enable_display_घातer_gating(काष्ठा dc *dc, uपूर्णांक8_t controller_id,
					काष्ठा dc_bios *dcb,
					क्रमागत pipe_gating_control घातer_gating);

#पूर्ण_अगर /* __DC_HWSS_DCE100_H__ */

