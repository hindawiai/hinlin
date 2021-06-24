<शैली गुरु>
/*
 * Copyright 2012-17 Advanced Micro Devices, Inc.
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

#अगर defined(CONFIG_DRM_AMD_DC_DCN)

#समावेश "reg_helper.h"
#समावेश "resource.h"
#समावेश "dwb.h"
#समावेश "dcn10_dwb.h"


#घोषणा REG(reg)\
	dwbc10->dwbc_regs->reg

#घोषणा CTX \
	dwbc10->base.ctx

#अघोषित FN
#घोषणा FN(reg_name, field_name) \
	dwbc10->dwbc_shअगरt->field_name, dwbc10->dwbc_mask->field_name

#घोषणा TO_DCN10_DWBC(dwbc_base) \
	container_of(dwbc_base, काष्ठा dcn10_dwbc, base)

अटल bool dwb1_get_caps(काष्ठा dwbc *dwbc, काष्ठा dwb_caps *caps)
अणु
	अगर (caps) अणु
		caps->adapter_id = 0;	/* we only support 1 adapter currently */
		caps->hw_version = DCN_VERSION_1_0;
		caps->num_pipes = 2;
		स_रखो(&caps->reserved, 0, माप(caps->reserved));
		स_रखो(&caps->reserved2, 0, माप(caps->reserved2));
		caps->sw_version = dwb_ver_1_0;
		caps->caps.support_dwb = true;
		caps->caps.support_ogam = false;
		caps->caps.support_wbscl = true;
		caps->caps.support_ocsc = false;
		वापस true;
	पूर्ण अन्यथा अणु
		वापस false;
	पूर्ण
पूर्ण

अटल bool dwb1_enable(काष्ठा dwbc *dwbc, काष्ठा dc_dwb_params *params)
अणु
	काष्ठा dcn10_dwbc *dwbc10 = TO_DCN10_DWBC(dwbc);

	/* disable first. */
	dwbc->funcs->disable(dwbc);

	/* disable घातer gating */
	REG_UPDATE_5(WB_EC_CONFIG, DISPCLK_R_WB_GATE_DIS, 1,
		 DISPCLK_G_WB_GATE_DIS, 1, DISPCLK_G_WBSCL_GATE_DIS, 1,
		 WB_LB_LS_DIS, 1, WB_LUT_LS_DIS, 1);

	REG_UPDATE(WB_ENABLE, WB_ENABLE, 1);

	वापस true;
पूर्ण

अटल bool dwb1_disable(काष्ठा dwbc *dwbc)
अणु
	काष्ठा dcn10_dwbc *dwbc10 = TO_DCN10_DWBC(dwbc);

	/* disable CNV */
	REG_UPDATE(CNV_MODE, CNV_FRAME_CAPTURE_EN, 0);

	/* disable WB */
	REG_UPDATE(WB_ENABLE, WB_ENABLE, 0);

	/* soft reset */
	REG_UPDATE(WB_SOFT_RESET, WB_SOFT_RESET, 1);
	REG_UPDATE(WB_SOFT_RESET, WB_SOFT_RESET, 0);

	/* enable घातer gating */
	REG_UPDATE_5(WB_EC_CONFIG, DISPCLK_R_WB_GATE_DIS, 0,
		 DISPCLK_G_WB_GATE_DIS, 0, DISPCLK_G_WBSCL_GATE_DIS, 0,
		 WB_LB_LS_DIS, 0, WB_LUT_LS_DIS, 0);

	वापस true;
पूर्ण

स्थिर काष्ठा dwbc_funcs dcn10_dwbc_funcs = अणु
	.get_caps			= dwb1_get_caps,
	.enable				= dwb1_enable,
	.disable			= dwb1_disable,
	.update				= शून्य,
	.set_stereo			= शून्य,
	.set_new_content		= शून्य,
	.set_warmup			= शून्य,
	.dwb_set_scaler			= शून्य,
पूर्ण;

व्योम dcn10_dwbc_स्थिरruct(काष्ठा dcn10_dwbc *dwbc10,
		काष्ठा dc_context *ctx,
		स्थिर काष्ठा dcn10_dwbc_रेजिस्टरs *dwbc_regs,
		स्थिर काष्ठा dcn10_dwbc_shअगरt *dwbc_shअगरt,
		स्थिर काष्ठा dcn10_dwbc_mask *dwbc_mask,
		पूर्णांक inst)
अणु
	dwbc10->base.ctx = ctx;

	dwbc10->base.inst = inst;
	dwbc10->base.funcs = &dcn10_dwbc_funcs;

	dwbc10->dwbc_regs = dwbc_regs;
	dwbc10->dwbc_shअगरt = dwbc_shअगरt;
	dwbc10->dwbc_mask = dwbc_mask;
पूर्ण


#पूर्ण_अगर
