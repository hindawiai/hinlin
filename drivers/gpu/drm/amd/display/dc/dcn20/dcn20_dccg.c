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

#समावेश <linux/slab.h>

#समावेश "reg_helper.h"
#समावेश "core_types.h"
#समावेश "dcn20_dccg.h"

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

व्योम dccg2_update_dpp_dto(काष्ठा dccg *dccg, पूर्णांक dpp_inst, पूर्णांक req_dppclk)
अणु
	काष्ठा dcn_dccg *dccg_dcn = TO_DCN_DCCG(dccg);

	अगर (dccg->ref_dppclk && req_dppclk) अणु
		पूर्णांक ref_dppclk = dccg->ref_dppclk;
		पूर्णांक modulo, phase;

		// phase / modulo = dpp pipe clk / dpp global clk
		modulo = 0xff;   // use FF at the end
		phase = ((modulo * req_dppclk) + ref_dppclk - 1) / ref_dppclk;

		अगर (phase > 0xff) अणु
			ASSERT(false);
			phase = 0xff;
		पूर्ण

		REG_SET_2(DPPCLK_DTO_PARAM[dpp_inst], 0,
				DPPCLK0_DTO_PHASE, phase,
				DPPCLK0_DTO_MODULO, modulo);
		REG_UPDATE(DPPCLK_DTO_CTRL,
				DPPCLK_DTO_ENABLE[dpp_inst], 1);
	पूर्ण अन्यथा अणु
		REG_UPDATE(DPPCLK_DTO_CTRL,
				DPPCLK_DTO_ENABLE[dpp_inst], 0);
	पूर्ण

	dccg->pipe_dppclk_khz[dpp_inst] = req_dppclk;
पूर्ण

व्योम dccg2_get_dccg_ref_freq(काष्ठा dccg *dccg,
		अचिन्हित पूर्णांक xtalin_freq_inKhz,
		अचिन्हित पूर्णांक *dccg_ref_freq_inKhz)
अणु
	काष्ठा dcn_dccg *dccg_dcn = TO_DCN_DCCG(dccg);
	uपूर्णांक32_t clk_en = 0;
	uपूर्णांक32_t clk_sel = 0;

	REG_GET_2(REFCLK_CNTL, REFCLK_CLOCK_EN, &clk_en, REFCLK_SRC_SEL, &clk_sel);

	अगर (clk_en != 0) अणु
		// DCN20 has never been validated क्रम non-xtalin as reference
		// frequency.  There's actually no way क्रम DC to determine what
		// frequency a non-xtalin source is.
		ASSERT_CRITICAL(false);
	पूर्ण

	*dccg_ref_freq_inKhz = xtalin_freq_inKhz;

	वापस;
पूर्ण

व्योम dccg2_init(काष्ठा dccg *dccg)
अणु
पूर्ण

अटल स्थिर काष्ठा dccg_funcs dccg2_funcs = अणु
	.update_dpp_dto = dccg2_update_dpp_dto,
	.get_dccg_ref_freq = dccg2_get_dccg_ref_freq,
	.dccg_init = dccg2_init
पूर्ण;

काष्ठा dccg *dccg2_create(
	काष्ठा dc_context *ctx,
	स्थिर काष्ठा dccg_रेजिस्टरs *regs,
	स्थिर काष्ठा dccg_shअगरt *dccg_shअगरt,
	स्थिर काष्ठा dccg_mask *dccg_mask)
अणु
	काष्ठा dcn_dccg *dccg_dcn = kzalloc(माप(*dccg_dcn), GFP_ATOMIC);
	काष्ठा dccg *base;

	अगर (dccg_dcn == शून्य) अणु
		BREAK_TO_DEBUGGER();
		वापस शून्य;
	पूर्ण

	base = &dccg_dcn->base;
	base->ctx = ctx;
	base->funcs = &dccg2_funcs;

	dccg_dcn->regs = regs;
	dccg_dcn->dccg_shअगरt = dccg_shअगरt;
	dccg_dcn->dccg_mask = dccg_mask;

	वापस &dccg_dcn->base;
पूर्ण

व्योम dcn_dccg_destroy(काष्ठा dccg **dccg)
अणु
	काष्ठा dcn_dccg *dccg_dcn = TO_DCN_DCCG(*dccg);

	kमुक्त(dccg_dcn);
	*dccg = शून्य;
पूर्ण
