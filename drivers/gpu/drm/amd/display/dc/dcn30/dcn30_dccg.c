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

#समावेश "reg_helper.h"
#समावेश "core_types.h"
#समावेश "dcn30_dccg.h"

#घोषणा TO_DCN_DCCG(dccg)\
	container_of(dccg, काष्ठा dcn_dccg, base)

#घोषणा REG(reg) \
	(dccg_dcn->regs->reg)

#अघोषित FN
#घोषणा FN(reg_name, field_name) \
	dccg_dcn->dccg_shअगरt->field_name, dccg_dcn->dccg_mask->field_name

#घोषणा CTX \
	dccg_dcn->base.ctx
#घोषणा DC_LOGGER \
	dccg->ctx->logger


अटल स्थिर काष्ठा dccg_funcs dccg3_funcs = अणु
	.update_dpp_dto = dccg2_update_dpp_dto,
	.get_dccg_ref_freq = dccg2_get_dccg_ref_freq,
	.dccg_init = dccg2_init
पूर्ण;

काष्ठा dccg *dccg3_create(
	काष्ठा dc_context *ctx,
	स्थिर काष्ठा dccg_रेजिस्टरs *regs,
	स्थिर काष्ठा dccg_shअगरt *dccg_shअगरt,
	स्थिर काष्ठा dccg_mask *dccg_mask)
अणु
	काष्ठा dcn_dccg *dccg_dcn = kzalloc(माप(*dccg_dcn), GFP_KERNEL);
	काष्ठा dccg *base;

	अगर (dccg_dcn == शून्य) अणु
		BREAK_TO_DEBUGGER();
		वापस शून्य;
	पूर्ण

	base = &dccg_dcn->base;
	base->ctx = ctx;
	base->funcs = &dccg3_funcs;

	dccg_dcn->regs = regs;
	dccg_dcn->dccg_shअगरt = dccg_shअगरt;
	dccg_dcn->dccg_mask = dccg_mask;

	वापस &dccg_dcn->base;
पूर्ण

काष्ठा dccg *dccg30_create(
	काष्ठा dc_context *ctx,
	स्थिर काष्ठा dccg_रेजिस्टरs *regs,
	स्थिर काष्ठा dccg_shअगरt *dccg_shअगरt,
	स्थिर काष्ठा dccg_mask *dccg_mask)
अणु
	काष्ठा dcn_dccg *dccg_dcn = kzalloc(माप(*dccg_dcn), GFP_KERNEL);
	काष्ठा dccg *base;

	अगर (dccg_dcn == शून्य) अणु
		BREAK_TO_DEBUGGER();
		वापस शून्य;
	पूर्ण

	base = &dccg_dcn->base;
	base->ctx = ctx;
	base->funcs = &dccg3_funcs;

	dccg_dcn->regs = regs;
	dccg_dcn->dccg_shअगरt = dccg_shअगरt;
	dccg_dcn->dccg_mask = dccg_mask;

	वापस &dccg_dcn->base;
पूर्ण
