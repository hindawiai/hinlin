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


#अगर_अघोषित _DCE_CLK_MGR_H_
#घोषणा _DCE_CLK_MGR_H_

#समावेश "dc.h"

/* functions shared by other dce clk mgrs */
पूर्णांक dce_adjust_dp_ref_freq_क्रम_ss(काष्ठा clk_mgr_पूर्णांकernal *clk_mgr_dce, पूर्णांक dp_ref_clk_khz);
पूर्णांक dce_get_dp_ref_freq_khz(काष्ठा clk_mgr *clk_mgr_base);
क्रमागत dm_pp_घड़ीs_state dce_get_required_घड़ीs_state(
	काष्ठा clk_mgr *clk_mgr_base,
	काष्ठा dc_state *context);

uपूर्णांक32_t dce_get_max_pixel_घड़ी_क्रम_all_paths(काष्ठा dc_state *context);


व्योम dce_clk_mgr_स्थिरruct(
		काष्ठा dc_context *ctx,
		काष्ठा clk_mgr_पूर्णांकernal *clk_mgr_dce);

व्योम dce_घड़ी_पढ़ो_ss_info(काष्ठा clk_mgr_पूर्णांकernal *dccg_dce);

पूर्णांक dce12_get_dp_ref_freq_khz(काष्ठा clk_mgr *dccg);

पूर्णांक dce_set_घड़ी(
	काष्ठा clk_mgr *clk_mgr_base,
	पूर्णांक requested_clk_khz);


व्योम dce_clk_mgr_destroy(काष्ठा clk_mgr **clk_mgr);

पूर्णांक dentist_get_भागider_from_did(पूर्णांक did);

#पूर्ण_अगर /* _DCE_CLK_MGR_H_ */
