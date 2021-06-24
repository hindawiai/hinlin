<शैली गुरु>
/*
 * Copyright 2020 Advanced Micro Devices, Inc.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 *  and/or sell copies of the Software, and to permit persons to whom the
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

#अगर_अघोषित __DC_PANEL_CNTL__DCN301_H__
#घोषणा __DC_PANEL_CNTL__DCN301_H__

#समावेश "panel_cntl.h"
#समावेश "dce/dce_panel_cntl.h"


#घोषणा DCN301_PANEL_CNTL_REG_LIST(id)\
	SRIR(PWRSEQ_CNTL, CNTL, PANEL_PWRSEQ, id), \
	SRIR(PWRSEQ_STATE, STATE, PANEL_PWRSEQ, id), \
	SRIR(PWRSEQ_REF_DIV, REF_DIV, PANEL_PWRSEQ, id), \
	SRIR(BL_PWM_CNTL, CNTL, BL_PWM, id), \
	SRIR(BL_PWM_CNTL2, CNTL2, BL_PWM, id), \
	SRIR(BL_PWM_PERIOD_CNTL, PERIOD_CNTL, BL_PWM, id), \
	SRIR(BL_PWM_GRP1_REG_LOCK, GRP1_REG_LOCK, BL_PWM, id)

#घोषणा DCN301_PANEL_CNTL_SF(reg_name, field_name, post_fix)\
	.field_name = reg_name ## __ ## field_name ## post_fix

#घोषणा DCN301_PANEL_CNTL_MASK_SH_LIST(mask_sh) \
	DCN301_PANEL_CNTL_SF(PANEL_PWRSEQ0_CNTL, PANEL_BLON, mask_sh),\
	DCN301_PANEL_CNTL_SF(PANEL_PWRSEQ0_CNTL, PANEL_DIGON, mask_sh),\
	DCN301_PANEL_CNTL_SF(PANEL_PWRSEQ0_CNTL, PANEL_DIGON_OVRD, mask_sh),\
	DCN301_PANEL_CNTL_SF(PANEL_PWRSEQ0_STATE, PANEL_PWRSEQ_TARGET_STATE_R, mask_sh), \
	DCN301_PANEL_CNTL_SF(PANEL_PWRSEQ0_REF_DIV, BL_PWM_REF_DIV, mask_sh), \
	DCN301_PANEL_CNTL_SF(BL_PWM0_PERIOD_CNTL, BL_PWM_PERIOD, mask_sh), \
	DCN301_PANEL_CNTL_SF(BL_PWM0_PERIOD_CNTL, BL_PWM_PERIOD_BITCNT, mask_sh), \
	DCN301_PANEL_CNTL_SF(BL_PWM0_CNTL, BL_ACTIVE_INT_FRAC_CNT, mask_sh), \
	DCN301_PANEL_CNTL_SF(BL_PWM0_CNTL, BL_PWM_FRACTIONAL_EN, mask_sh), \
	DCN301_PANEL_CNTL_SF(BL_PWM0_CNTL, BL_PWM_EN, mask_sh), \
	DCN301_PANEL_CNTL_SF(BL_PWM0_GRP1_REG_LOCK, BL_PWM_GRP1_IGNORE_MASTER_LOCK_EN, mask_sh), \
	DCN301_PANEL_CNTL_SF(BL_PWM0_GRP1_REG_LOCK, BL_PWM_GRP1_REG_LOCK, mask_sh), \
	DCN301_PANEL_CNTL_SF(BL_PWM0_GRP1_REG_LOCK, BL_PWM_GRP1_REG_UPDATE_PENDING, mask_sh)

#घोषणा DCN301_PANEL_CNTL_REG_FIELD_LIST(type) \
	type PANEL_BLON;\
	type PANEL_DIGON;\
	type PANEL_DIGON_OVRD;\
	type PANEL_PWRSEQ_TARGET_STATE_R; \
	type BL_PWM_EN; \
	type BL_ACTIVE_INT_FRAC_CNT; \
	type BL_PWM_FRACTIONAL_EN; \
	type BL_PWM_PERIOD; \
	type BL_PWM_PERIOD_BITCNT; \
	type BL_PWM_GRP1_IGNORE_MASTER_LOCK_EN; \
	type BL_PWM_GRP1_REG_LOCK; \
	type BL_PWM_GRP1_REG_UPDATE_PENDING; \
	type BL_PWM_REF_DIV

काष्ठा dcn301_panel_cntl_shअगरt अणु
	DCN301_PANEL_CNTL_REG_FIELD_LIST(uपूर्णांक8_t);
पूर्ण;

काष्ठा dcn301_panel_cntl_mask अणु
	DCN301_PANEL_CNTL_REG_FIELD_LIST(uपूर्णांक32_t);
पूर्ण;

काष्ठा dcn301_panel_cntl अणु
	काष्ठा panel_cntl base;
	स्थिर काष्ठा dce_panel_cntl_रेजिस्टरs *regs;
	स्थिर काष्ठा dcn301_panel_cntl_shअगरt *shअगरt;
	स्थिर काष्ठा dcn301_panel_cntl_mask *mask;
पूर्ण;

व्योम dcn301_panel_cntl_स्थिरruct(
	काष्ठा dcn301_panel_cntl *panel_cntl,
	स्थिर काष्ठा panel_cntl_init_data *init_data,
	स्थिर काष्ठा dce_panel_cntl_रेजिस्टरs *regs,
	स्थिर काष्ठा dcn301_panel_cntl_shअगरt *shअगरt,
	स्थिर काष्ठा dcn301_panel_cntl_mask *mask);

#पूर्ण_अगर /* __DC_PANEL_CNTL__DCN301_H__ */
