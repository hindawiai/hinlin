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

#अगर_अघोषित __DAL_DCCG_H__
#घोषणा __DAL_DCCG_H__

#समावेश "dc_types.h"
#समावेश "hw_shared.h"

काष्ठा dccg अणु
	काष्ठा dc_context *ctx;
	स्थिर काष्ठा dccg_funcs *funcs;
	पूर्णांक pipe_dppclk_khz[MAX_PIPES];
	पूर्णांक ref_dppclk;
पूर्ण;

काष्ठा dccg_funcs अणु
	व्योम (*update_dpp_dto)(काष्ठा dccg *dccg,
			पूर्णांक dpp_inst,
			पूर्णांक req_dppclk);
	व्योम (*get_dccg_ref_freq)(काष्ठा dccg *dccg,
			अचिन्हित पूर्णांक xtalin_freq_inKhz,
			अचिन्हित पूर्णांक *dccg_ref_freq_inKhz);
	व्योम (*dccg_init)(काष्ठा dccg *dccg);
पूर्ण;

#पूर्ण_अगर //__DAL_DCCG_H__
