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

#समावेश "dm_services.h"

/* include DCE11 रेजिस्टर header files */
#समावेश "dce/dce_11_0_d.h"
#समावेश "dce/dce_11_0_sh_mask.h"

#समावेश "dce/dce_opp.h"
#समावेश "dce110_opp_v.h"

/*****************************************/
/* Conकाष्ठाor, Deकाष्ठाor               */
/*****************************************/

अटल स्थिर काष्ठा opp_funcs funcs = अणु
		.opp_set_dyn_expansion = dce110_opp_set_dyn_expansion,
		.opp_destroy = dce110_opp_destroy,
		.opp_program_fmt = dce110_opp_program_fmt,
		.opp_program_bit_depth_reduction =
				dce110_opp_program_bit_depth_reduction
पूर्ण;

व्योम dce110_opp_v_स्थिरruct(काष्ठा dce110_opp *opp110,
	काष्ठा dc_context *ctx)
अणु
	opp110->base.funcs = &funcs;

	opp110->base.ctx = ctx;
पूर्ण

