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

#समावेश "reg_helper.h"
#समावेश "core_types.h"
#समावेश "dcn20/dcn20_dccg.h"
#समावेश "dcn21_dccg.h"

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

व्योम dccg21_update_dpp_dto(काष्ठा dccg *dccg, पूर्णांक dpp_inst, पूर्णांक req_dppclk)
अणु
	काष्ठा dcn_dccg *dccg_dcn = TO_DCN_DCCG(dccg);

	अगर (dccg->ref_dppclk) अणु
		पूर्णांक ref_dppclk = dccg->ref_dppclk;
		पूर्णांक modulo = ref_dppclk / 10000;
		पूर्णांक phase;

		अगर (req_dppclk) अणु
			/*
			 * program DPP DTO phase and modulo as below
			 * phase = उच्चमानing(dpp_pipe_clk_mhz / 10)
			 * module = trunc(dpp_global_clk_mhz / 10)
			 *
			 * storing frequencies in रेजिस्टरs allow dmcub fw
			 * to run समय lower घड़ीs when possible क्रम घातer saving
			 *
			 * उच्चमानing phase and truncate modulo guarentees the भागided
			 * करोwn per pipe dpp घड़ी has high enough frequency
			 */
			phase = (req_dppclk + 9999) / 10000;

			अगर (phase > modulo) अणु
				/* phase > modulo result in screen corruption
				 * ie phase = 30, mod = 29 क्रम 4k@60 HDMI
				 * in these हाल we करोn't want pipe घड़ी to be भागided
				 */
				phase = modulo;
			पूर्ण
		पूर्ण अन्यथा अणु
			/*
			 *  set phase to 10 अगर dpp isn't used to
			 *  prevent hard hang अगर access dpp रेजिस्टर
			 *  on unused pipe
			 *
			 *  DTO should be on to भागide करोwn un-used
			 *  pipe घड़ी क्रम घातer saving
			 */
			phase = 10;
		पूर्ण

		REG_SET_2(DPPCLK_DTO_PARAM[dpp_inst], 0,
				DPPCLK0_DTO_PHASE, phase,
				DPPCLK0_DTO_MODULO, modulo);

		REG_UPDATE(DPPCLK_DTO_CTRL,
				DPPCLK_DTO_ENABLE[dpp_inst], 1);
	पूर्ण

	dccg->pipe_dppclk_khz[dpp_inst] = req_dppclk;
पूर्ण


अटल स्थिर काष्ठा dccg_funcs dccg21_funcs = अणु
	.update_dpp_dto = dccg21_update_dpp_dto,
	.get_dccg_ref_freq = dccg2_get_dccg_ref_freq,
	.dccg_init = dccg2_init
पूर्ण;

काष्ठा dccg *dccg21_create(
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
	base->funcs = &dccg21_funcs;

	dccg_dcn->regs = regs;
	dccg_dcn->dccg_shअगरt = dccg_shअगरt;
	dccg_dcn->dccg_mask = dccg_mask;

	वापस &dccg_dcn->base;
पूर्ण
