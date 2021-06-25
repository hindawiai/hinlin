<शैली गुरु>
/*
* Copyright 2020 Advanced Micro Devices, Inc.
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
#समावेश "dcn301_hubbub.h"
#समावेश "reg_helper.h"

#घोषणा REG(reg)\
	hubbub1->regs->reg
#घोषणा DC_LOGGER \
	hubbub1->base.ctx->logger
#घोषणा CTX \
	hubbub1->base.ctx

#अघोषित FN
#घोषणा FN(reg_name, field_name) \
	hubbub1->shअगरts->field_name, hubbub1->masks->field_name

#घोषणा REG(reg)\
	hubbub1->regs->reg

#घोषणा CTX \
	hubbub1->base.ctx

#अघोषित FN
#घोषणा FN(reg_name, field_name) \
	hubbub1->shअगरts->field_name, hubbub1->masks->field_name


अटल स्थिर काष्ठा hubbub_funcs hubbub301_funcs = अणु
	.update_dchub = hubbub2_update_dchub,
	.init_dchub_sys_ctx = hubbub21_init_dchub,
	.init_vm_ctx = hubbub2_init_vm_ctx,
	.dcc_support_swizzle = hubbub3_dcc_support_swizzle,
	.dcc_support_pixel_क्रमmat = hubbub2_dcc_support_pixel_क्रमmat,
	.get_dcc_compression_cap = hubbub3_get_dcc_compression_cap,
	.wm_पढ़ो_state = hubbub21_wm_पढ़ो_state,
	.get_dchub_ref_freq = hubbub2_get_dchub_ref_freq,
	.program_watermarks = hubbub3_program_watermarks,
	.allow_self_refresh_control = hubbub1_allow_self_refresh_control,
	.is_allow_self_refresh_enabled = hubbub1_is_allow_self_refresh_enabled,
	.क्रमce_wm_propagate_to_pipes = hubbub3_क्रमce_wm_propagate_to_pipes,
	.क्रमce_pstate_change_control = hubbub3_क्रमce_pstate_change_control,
पूर्ण;

व्योम hubbub301_स्थिरruct(काष्ठा dcn20_hubbub *hubbub3,
	काष्ठा dc_context *ctx,
	स्थिर काष्ठा dcn_hubbub_रेजिस्टरs *hubbub_regs,
	स्थिर काष्ठा dcn_hubbub_shअगरt *hubbub_shअगरt,
	स्थिर काष्ठा dcn_hubbub_mask *hubbub_mask)
अणु
	hubbub3->base.ctx = ctx;
	hubbub3->base.funcs = &hubbub301_funcs;
	hubbub3->regs = hubbub_regs;
	hubbub3->shअगरts = hubbub_shअगरt;
	hubbub3->masks = hubbub_mask;

	hubbub3->debug_test_index_pstate = 0xB;
	hubbub3->detile_buf_size = 184 * 1024; /* 184KB क्रम DCN3 */
पूर्ण
