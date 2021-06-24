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

#अगर_अघोषित __DCN30_DCCG_H__
#घोषणा __DCN30_DCCG_H__

#समावेश "dcn20/dcn20_dccg.h"


#घोषणा DCCG_REG_LIST_DCN3AG() \
	DCCG_COMMON_REG_LIST_DCN_BASE(),\
	SR(PHYASYMCLK_CLOCK_CNTL),\
	SR(PHYBSYMCLK_CLOCK_CNTL),\
	SR(PHYCSYMCLK_CLOCK_CNTL)


#घोषणा DCCG_REG_LIST_DCN30() \
	DCCG_REG_LIST_DCN2(),\
	SR(PHYASYMCLK_CLOCK_CNTL),\
	SR(PHYBSYMCLK_CLOCK_CNTL),\
	SR(PHYCSYMCLK_CLOCK_CNTL)

#घोषणा DCCG_MASK_SH_LIST_DCN3(mask_sh) \
	DCCG_MASK_SH_LIST_DCN2(mask_sh),\
	DCCG_SF(PHYASYMCLK_CLOCK_CNTL, PHYASYMCLK_FORCE_EN, mask_sh),\
	DCCG_SF(PHYASYMCLK_CLOCK_CNTL, PHYASYMCLK_FORCE_SRC_SEL, mask_sh),\
	DCCG_SF(PHYBSYMCLK_CLOCK_CNTL, PHYBSYMCLK_FORCE_EN, mask_sh),\
	DCCG_SF(PHYBSYMCLK_CLOCK_CNTL, PHYBSYMCLK_FORCE_SRC_SEL, mask_sh),\
	DCCG_SF(PHYCSYMCLK_CLOCK_CNTL, PHYCSYMCLK_FORCE_EN, mask_sh),\
	DCCG_SF(PHYCSYMCLK_CLOCK_CNTL, PHYCSYMCLK_FORCE_SRC_SEL, mask_sh)

काष्ठा dccg *dccg3_create(
	काष्ठा dc_context *ctx,
	स्थिर काष्ठा dccg_रेजिस्टरs *regs,
	स्थिर काष्ठा dccg_shअगरt *dccg_shअगरt,
	स्थिर काष्ठा dccg_mask *dccg_mask);

काष्ठा dccg *dccg30_create(
	काष्ठा dc_context *ctx,
	स्थिर काष्ठा dccg_रेजिस्टरs *regs,
	स्थिर काष्ठा dccg_shअगरt *dccg_shअगरt,
	स्थिर काष्ठा dccg_mask *dccg_mask);

#पूर्ण_अगर //__DCN30_DCCG_H__
