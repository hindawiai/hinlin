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

#अगर_अघोषित __RN_CLK_MGR_H__
#घोषणा __RN_CLK_MGR_H__

#समावेश "clk_mgr.h"
#समावेश "dm_pp_smu.h"

काष्ठा rn_clk_रेजिस्टरs अणु
	uपूर्णांक32_t CLK1_CLK0_CURRENT_CNT; /* DPREFCLK */
पूर्ण;

व्योम rn_clk_mgr_स्थिरruct(काष्ठा dc_context *ctx,
		काष्ठा clk_mgr_पूर्णांकernal *clk_mgr,
		काष्ठा pp_smu_funcs *pp_smu,
		काष्ठा dccg *dccg);

#पूर्ण_अगर //__RN_CLK_MGR_H__
