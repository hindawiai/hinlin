<शैली गुरु>
/*
 * Copyright 2012-16 Advanced Micro Devices, Inc.
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

#अगर_अघोषित DAL_DC_DCE_DCE112_CLK_MGR_H_
#घोषणा DAL_DC_DCE_DCE112_CLK_MGR_H_


व्योम dce112_clk_mgr_स्थिरruct(
		काष्ठा dc_context *ctx,
		काष्ठा clk_mgr_पूर्णांकernal *clk_mgr);

/* functions shared with other clk mgr */
पूर्णांक dce112_set_घड़ी(काष्ठा clk_mgr *clk_mgr_base, पूर्णांक requested_clk_khz);
पूर्णांक dce112_set_dispclk(काष्ठा clk_mgr_पूर्णांकernal *clk_mgr, पूर्णांक requested_clk_khz);
पूर्णांक dce112_set_dprefclk(काष्ठा clk_mgr_पूर्णांकernal *clk_mgr);

#पूर्ण_अगर /* DAL_DC_DCE_DCE112_CLK_MGR_H_ */
