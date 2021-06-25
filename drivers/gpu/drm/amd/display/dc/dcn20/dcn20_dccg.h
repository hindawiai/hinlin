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

#अगर_अघोषित __DCN20_DCCG_H__
#घोषणा __DCN20_DCCG_H__

#समावेश "dccg.h"

#घोषणा DCCG_COMMON_REG_LIST_DCN_BASE() \
	SR(DPPCLK_DTO_CTRL),\
	DCCG_SRII(DTO_PARAM, DPPCLK, 0),\
	DCCG_SRII(DTO_PARAM, DPPCLK, 1),\
	DCCG_SRII(DTO_PARAM, DPPCLK, 2),\
	DCCG_SRII(DTO_PARAM, DPPCLK, 3),\
	SR(REFCLK_CNTL)

#घोषणा DCCG_REG_LIST_DCN2() \
	DCCG_COMMON_REG_LIST_DCN_BASE(),\
	DCCG_SRII(DTO_PARAM, DPPCLK, 4),\
	DCCG_SRII(DTO_PARAM, DPPCLK, 5)

#घोषणा DCCG_SF(reg_name, field_name, post_fix)\
	.field_name = reg_name ## __ ## field_name ## post_fix

#घोषणा DCCG_SFI(reg_name, field_name, field_prefix, inst, post_fix)\
	.field_prefix ## _ ## field_name[inst] = reg_name ## __ ## field_prefix ## inst ## _ ## field_name ## post_fix

#घोषणा DCCG_COMMON_MASK_SH_LIST_DCN_COMMON_BASE(mask_sh) \
	DCCG_SFI(DPPCLK_DTO_CTRL, DTO_ENABLE, DPPCLK, 0, mask_sh),\
	DCCG_SFI(DPPCLK_DTO_CTRL, DTO_DB_EN, DPPCLK, 0, mask_sh),\
	DCCG_SFI(DPPCLK_DTO_CTRL, DTO_ENABLE, DPPCLK, 1, mask_sh),\
	DCCG_SFI(DPPCLK_DTO_CTRL, DTO_DB_EN, DPPCLK, 1, mask_sh),\
	DCCG_SFI(DPPCLK_DTO_CTRL, DTO_ENABLE, DPPCLK, 2, mask_sh),\
	DCCG_SFI(DPPCLK_DTO_CTRL, DTO_DB_EN, DPPCLK, 2, mask_sh),\
	DCCG_SFI(DPPCLK_DTO_CTRL, DTO_ENABLE, DPPCLK, 3, mask_sh),\
	DCCG_SFI(DPPCLK_DTO_CTRL, DTO_DB_EN, DPPCLK, 3, mask_sh),\
	DCCG_SF(DPPCLK0_DTO_PARAM, DPPCLK0_DTO_PHASE, mask_sh),\
	DCCG_SF(DPPCLK0_DTO_PARAM, DPPCLK0_DTO_MODULO, mask_sh),\
	DCCG_SF(REFCLK_CNTL, REFCLK_CLOCK_EN, mask_sh),\
	DCCG_SF(REFCLK_CNTL, REFCLK_SRC_SEL, mask_sh)

#घोषणा DCCG_MASK_SH_LIST_DCN2(mask_sh) \
	DCCG_COMMON_MASK_SH_LIST_DCN_COMMON_BASE(mask_sh),\
	DCCG_SFI(DPPCLK_DTO_CTRL, DTO_ENABLE, DPPCLK, 4, mask_sh),\
	DCCG_SFI(DPPCLK_DTO_CTRL, DTO_DB_EN, DPPCLK, 4, mask_sh),\
	DCCG_SFI(DPPCLK_DTO_CTRL, DTO_ENABLE, DPPCLK, 5, mask_sh),\
	DCCG_SFI(DPPCLK_DTO_CTRL, DTO_DB_EN, DPPCLK, 5, mask_sh)

#घोषणा DCCG_REG_FIELD_LIST(type) \
	type DPPCLK0_DTO_PHASE;\
	type DPPCLK0_DTO_MODULO;\
	type DPPCLK_DTO_ENABLE[6];\
	type DPPCLK_DTO_DB_EN[6];\
	type REFCLK_CLOCK_EN;\
	type REFCLK_SRC_SEL;

#घोषणा DCCG3_REG_FIELD_LIST(type) \
	type PHYASYMCLK_FORCE_EN;\
	type PHYASYMCLK_FORCE_SRC_SEL;\
	type PHYBSYMCLK_FORCE_EN;\
	type PHYBSYMCLK_FORCE_SRC_SEL;\
	type PHYCSYMCLK_FORCE_EN;\
	type PHYCSYMCLK_FORCE_SRC_SEL;

काष्ठा dccg_shअगरt अणु
	DCCG_REG_FIELD_LIST(uपूर्णांक8_t)
	DCCG3_REG_FIELD_LIST(uपूर्णांक8_t)
पूर्ण;

काष्ठा dccg_mask अणु
	DCCG_REG_FIELD_LIST(uपूर्णांक32_t)
	DCCG3_REG_FIELD_LIST(uपूर्णांक32_t)
पूर्ण;

काष्ठा dccg_रेजिस्टरs अणु
	uपूर्णांक32_t DPPCLK_DTO_CTRL;
	uपूर्णांक32_t DPPCLK_DTO_PARAM[6];
	uपूर्णांक32_t REFCLK_CNTL;
	uपूर्णांक32_t HDMICHARCLK_CLOCK_CNTL[6];
	uपूर्णांक32_t PHYASYMCLK_CLOCK_CNTL;
	uपूर्णांक32_t PHYBSYMCLK_CLOCK_CNTL;
	uपूर्णांक32_t PHYCSYMCLK_CLOCK_CNTL;
पूर्ण;

काष्ठा dcn_dccg अणु
	काष्ठा dccg base;
	स्थिर काष्ठा dccg_रेजिस्टरs *regs;
	स्थिर काष्ठा dccg_shअगरt *dccg_shअगरt;
	स्थिर काष्ठा dccg_mask *dccg_mask;
पूर्ण;

व्योम dccg2_update_dpp_dto(काष्ठा dccg *dccg, पूर्णांक dpp_inst, पूर्णांक req_dppclk);

व्योम dccg2_get_dccg_ref_freq(काष्ठा dccg *dccg,
		अचिन्हित पूर्णांक xtalin_freq_inKhz,
		अचिन्हित पूर्णांक *dccg_ref_freq_inKhz);

व्योम dccg2_init(काष्ठा dccg *dccg);

काष्ठा dccg *dccg2_create(
	काष्ठा dc_context *ctx,
	स्थिर काष्ठा dccg_रेजिस्टरs *regs,
	स्थिर काष्ठा dccg_shअगरt *dccg_shअगरt,
	स्थिर काष्ठा dccg_mask *dccg_mask);

व्योम dcn_dccg_destroy(काष्ठा dccg **dccg);

#पूर्ण_अगर //__DCN20_DCCG_H__
