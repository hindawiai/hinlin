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

#समावेश "reg_helper.h"
#समावेश "clk_mgr_internal.h"
#समावेश "rv1_clk_mgr_clk.h"

#समावेश "ip/Discovery/hwid.h"
#समावेश "ip/Discovery/v1/ip_offset_1.h"
#समावेश "ip/CLK/clk_10_0_default.h"
#समावेश "ip/CLK/clk_10_0_offset.h"
#समावेश "ip/CLK/clk_10_0_reg.h"
#समावेश "ip/CLK/clk_10_0_sh_mask.h"

#समावेश "dce100/dce_clk_mgr.h"

#घोषणा CLK_BASE_INNER(inst) \
	CLK_BASE__INST ## inst ## _SEG0


#घोषणा CLK_REG(reg_name, block, inst)\
	CLK_BASE(mm ## block ## _ ## inst ## _ ## reg_name ## _BASE_IDX) + \
					mm ## block ## _ ## inst ## _ ## reg_name

#घोषणा REG(reg_name) \
	CLK_REG(reg_name, CLK0, 0)


/* Only used by testing framework*/
व्योम rv1_dump_clk_रेजिस्टरs(काष्ठा clk_state_रेजिस्टरs *regs, काष्ठा clk_bypass *bypass, काष्ठा clk_mgr *clk_mgr_base)
अणु
	काष्ठा clk_mgr_पूर्णांकernal *clk_mgr = TO_CLK_MGR_INTERNAL(clk_mgr_base);

		regs->CLK0_CLK8_CURRENT_CNT = REG_READ(CLK0_CLK8_CURRENT_CNT) / 10; //dcf clk

		bypass->dcfclk_bypass = REG_READ(CLK0_CLK8_BYPASS_CNTL) & 0x0007;
		अगर (bypass->dcfclk_bypass < 0 || bypass->dcfclk_bypass > 4)
			bypass->dcfclk_bypass = 0;


		regs->CLK0_CLK8_DS_CNTL = REG_READ(CLK0_CLK8_DS_CNTL) / 10;	//dcf deep sleep भागider

		regs->CLK0_CLK8_ALLOW_DS = REG_READ(CLK0_CLK8_ALLOW_DS); //dcf deep sleep allow

		regs->CLK0_CLK10_CURRENT_CNT = REG_READ(CLK0_CLK10_CURRENT_CNT) / 10; //dpref clk

		bypass->dispclk_pypass = REG_READ(CLK0_CLK10_BYPASS_CNTL) & 0x0007;
		अगर (bypass->dispclk_pypass < 0 || bypass->dispclk_pypass > 4)
			bypass->dispclk_pypass = 0;

		regs->CLK0_CLK11_CURRENT_CNT = REG_READ(CLK0_CLK11_CURRENT_CNT) / 10; //disp clk

		bypass->dprefclk_bypass = REG_READ(CLK0_CLK11_BYPASS_CNTL) & 0x0007;
		अगर (bypass->dprefclk_bypass < 0 || bypass->dprefclk_bypass > 4)
			bypass->dprefclk_bypass = 0;

पूर्ण
