<शैली गुरु>
/*
 * Copyright 2012-15 Advanced Micro Devices, Inc.
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

#अगर_अघोषित __DC_PANEL_CNTL__DCE_H__
#घोषणा __DC_PANEL_CNTL__DCE_H__

#समावेश "panel_cntl.h"

/* set रेजिस्टर offset with instance */
#घोषणा DCE_PANEL_CNTL_SR(reg_name, block)\
	.reg_name = mm ## block ## _ ## reg_name

#घोषणा DCE_PANEL_CNTL_REG_LIST()\
	DCE_PANEL_CNTL_SR(PWRSEQ_CNTL, LVTMA), \
	DCE_PANEL_CNTL_SR(PWRSEQ_STATE, LVTMA), \
	DCE_PANEL_CNTL_SR(PWRSEQ_REF_DIV, LVTMA), \
	SR(BL_PWM_CNTL), \
	SR(BL_PWM_CNTL2), \
	SR(BL_PWM_PERIOD_CNTL), \
	SR(BL_PWM_GRP1_REG_LOCK), \
	SR(BIOS_SCRATCH_2)

#घोषणा DCN_PANEL_CNTL_SR(reg_name, block)\
	.reg_name = BASE(mm ## block ## _ ## reg_name ## _BASE_IDX) + \
					mm ## block ## _ ## reg_name

#घोषणा DCN_PANEL_CNTL_REG_LIST()\
	DCN_PANEL_CNTL_SR(PWRSEQ_CNTL, LVTMA), \
	DCN_PANEL_CNTL_SR(PWRSEQ_STATE, LVTMA), \
	DCN_PANEL_CNTL_SR(PWRSEQ_REF_DIV, LVTMA), \
	SR(BL_PWM_CNTL), \
	SR(BL_PWM_CNTL2), \
	SR(BL_PWM_PERIOD_CNTL), \
	SR(BL_PWM_GRP1_REG_LOCK), \
	NBIO_SR(BIOS_SCRATCH_2)

#घोषणा DCE_PANEL_CNTL_SF(reg_name, field_name, post_fix)\
	.field_name = reg_name ## __ ## field_name ## post_fix

#घोषणा DCE_PANEL_CNTL_MASK_SH_LIST(mask_sh) \
	DCE_PANEL_CNTL_SF(LVTMA_PWRSEQ_CNTL, LVTMA_BLON, mask_sh),\
	DCE_PANEL_CNTL_SF(LVTMA_PWRSEQ_CNTL, LVTMA_BLON_OVRD, mask_sh),\
	DCE_PANEL_CNTL_SF(LVTMA_PWRSEQ_CNTL, LVTMA_DIGON, mask_sh),\
	DCE_PANEL_CNTL_SF(LVTMA_PWRSEQ_CNTL, LVTMA_DIGON_OVRD, mask_sh),\
	DCE_PANEL_CNTL_SF(LVTMA_PWRSEQ_CNTL, LVTMA_PWRSEQ_TARGET_STATE, mask_sh), \
	DCE_PANEL_CNTL_SF(LVTMA_PWRSEQ_STATE, LVTMA_PWRSEQ_TARGET_STATE_R, mask_sh), \
	DCE_PANEL_CNTL_SF(LVTMA_PWRSEQ_REF_DIV, BL_PWM_REF_DIV, mask_sh), \
	DCE_PANEL_CNTL_SF(BL_PWM_PERIOD_CNTL, BL_PWM_PERIOD, mask_sh), \
	DCE_PANEL_CNTL_SF(BL_PWM_PERIOD_CNTL, BL_PWM_PERIOD_BITCNT, mask_sh), \
	DCE_PANEL_CNTL_SF(BL_PWM_CNTL, BL_ACTIVE_INT_FRAC_CNT, mask_sh), \
	DCE_PANEL_CNTL_SF(BL_PWM_CNTL, BL_PWM_FRACTIONAL_EN, mask_sh), \
	DCE_PANEL_CNTL_SF(BL_PWM_CNTL, BL_PWM_EN, mask_sh), \
	DCE_PANEL_CNTL_SF(BL_PWM_GRP1_REG_LOCK, BL_PWM_GRP1_IGNORE_MASTER_LOCK_EN, mask_sh), \
	DCE_PANEL_CNTL_SF(BL_PWM_GRP1_REG_LOCK, BL_PWM_GRP1_REG_LOCK, mask_sh), \
	DCE_PANEL_CNTL_SF(BL_PWM_GRP1_REG_LOCK, BL_PWM_GRP1_REG_UPDATE_PENDING, mask_sh)

#घोषणा DCE_PANEL_CNTL_REG_FIELD_LIST(type) \
	type LVTMA_BLON;\
	type LVTMA_BLON_OVRD;\
	type LVTMA_DIGON;\
	type LVTMA_DIGON_OVRD;\
	type LVTMA_PWRSEQ_TARGET_STATE; \
	type LVTMA_PWRSEQ_TARGET_STATE_R; \
	type BL_PWM_REF_DIV; \
	type BL_PWM_EN; \
	type BL_ACTIVE_INT_FRAC_CNT; \
	type BL_PWM_FRACTIONAL_EN; \
	type BL_PWM_PERIOD; \
	type BL_PWM_PERIOD_BITCNT; \
	type BL_PWM_GRP1_IGNORE_MASTER_LOCK_EN; \
	type BL_PWM_GRP1_REG_LOCK; \
	type BL_PWM_GRP1_REG_UPDATE_PENDING

काष्ठा dce_panel_cntl_shअगरt अणु
	DCE_PANEL_CNTL_REG_FIELD_LIST(uपूर्णांक8_t);
पूर्ण;

काष्ठा dce_panel_cntl_mask अणु
	DCE_PANEL_CNTL_REG_FIELD_LIST(uपूर्णांक32_t);
पूर्ण;

काष्ठा dce_panel_cntl_रेजिस्टरs अणु
	uपूर्णांक32_t PWRSEQ_CNTL;
	uपूर्णांक32_t PWRSEQ_STATE;
	uपूर्णांक32_t BL_PWM_CNTL;
	uपूर्णांक32_t BL_PWM_CNTL2;
	uपूर्णांक32_t BL_PWM_PERIOD_CNTL;
	uपूर्णांक32_t BL_PWM_GRP1_REG_LOCK;
	uपूर्णांक32_t PWRSEQ_REF_DIV;
	uपूर्णांक32_t BIOS_SCRATCH_2;
पूर्ण;

काष्ठा dce_panel_cntl अणु
	काष्ठा panel_cntl base;
	स्थिर काष्ठा dce_panel_cntl_रेजिस्टरs *regs;
	स्थिर काष्ठा dce_panel_cntl_shअगरt *shअगरt;
	स्थिर काष्ठा dce_panel_cntl_mask *mask;
पूर्ण;

व्योम dce_panel_cntl_स्थिरruct(
	काष्ठा dce_panel_cntl *panel_cntl,
	स्थिर काष्ठा panel_cntl_init_data *init_data,
	स्थिर काष्ठा dce_panel_cntl_रेजिस्टरs *regs,
	स्थिर काष्ठा dce_panel_cntl_shअगरt *shअगरt,
	स्थिर काष्ठा dce_panel_cntl_mask *mask);

#पूर्ण_अगर /* __DC_PANEL_CNTL__DCE_H__ */
