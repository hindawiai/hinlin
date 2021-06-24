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

#अगर_अघोषित __DCN20_CLK_MGR_H__
#घोषणा __DCN20_CLK_MGR_H__

व्योम dcn2_update_घड़ीs(काष्ठा clk_mgr *dccg,
			काष्ठा dc_state *context,
			bool safe_to_lower);

व्योम dcn2_update_घड़ीs_fpga(काष्ठा clk_mgr *clk_mgr,
			काष्ठा dc_state *context,
			bool safe_to_lower);
व्योम dcn20_update_घड़ीs_update_dpp_dto(काष्ठा clk_mgr_पूर्णांकernal *clk_mgr,
		काष्ठा dc_state *context, bool safe_to_lower);

व्योम dcn2_init_घड़ीs(काष्ठा clk_mgr *clk_mgr);

व्योम dcn20_clk_mgr_स्थिरruct(काष्ठा dc_context *ctx,
		काष्ठा clk_mgr_पूर्णांकernal *clk_mgr,
		काष्ठा pp_smu_funcs *pp_smu,
		काष्ठा dccg *dccg);

uपूर्णांक32_t dentist_get_did_from_भागider(पूर्णांक भागider);

व्योम dcn2_get_घड़ी(काष्ठा clk_mgr *clk_mgr,
		काष्ठा dc_state *context,
			क्रमागत dc_घड़ी_प्रकारype घड़ी_प्रकारype,
			काष्ठा dc_घड़ी_config *घड़ी_cfg);

व्योम dcn20_update_घड़ीs_update_dentist(काष्ठा clk_mgr_पूर्णांकernal *clk_mgr);

व्योम dcn2_पढ़ो_घड़ीs_from_hw_dentist(काष्ठा clk_mgr *clk_mgr_base);


#पूर्ण_अगर //__DCN20_CLK_MGR_H__
