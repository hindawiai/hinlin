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

#समावेश "core_types.h"
#समावेश "clk_mgr_internal.h"
#समावेश "rv1_clk_mgr.h"
#समावेश "rv2_clk_mgr.h"
#समावेश "dce112/dce112_clk_mgr.h"

अटल काष्ठा clk_mgr_पूर्णांकernal_funcs rv2_clk_पूर्णांकernal_funcs = अणु
	.set_dispclk = dce112_set_dispclk,
	.set_dprefclk = dce112_set_dprefclk
पूर्ण;

व्योम rv2_clk_mgr_स्थिरruct(काष्ठा dc_context *ctx, काष्ठा clk_mgr_पूर्णांकernal *clk_mgr, काष्ठा pp_smu_funcs *pp_smu)

अणु
	rv1_clk_mgr_स्थिरruct(ctx, clk_mgr, pp_smu);

	clk_mgr->funcs = &rv2_clk_पूर्णांकernal_funcs;
पूर्ण
