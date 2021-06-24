<शैली गुरु>
/* Copyright 2012-15 Advanced Micro Devices, Inc.
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

#अगर_अघोषित __DC_CLOCK_SOURCE_DCE_H__
#घोषणा __DC_CLOCK_SOURCE_DCE_H__

#समावेश "../inc/clock_source.h"

#घोषणा TO_DCE110_CLK_SRC(clk_src)\
	container_of(clk_src, काष्ठा dce110_clk_src, base)

#घोषणा CS_COMMON_REG_LIST_DCE_100_110(id) \
		SRI(RESYNC_CNTL, PIXCLK, id), \
		SRI(PLL_CNTL, BPHYC_PLL, id)

#घोषणा CS_COMMON_REG_LIST_DCE_80(id) \
		SRI(RESYNC_CNTL, PIXCLK, id), \
		SRI(PLL_CNTL, DCCG_PLL, id)

#घोषणा CS_COMMON_REG_LIST_DCE_112(id) \
		SRI(PIXCLK_RESYNC_CNTL, PHYPLL, id)


#घोषणा CS_SF(reg_name, field_name, post_fix)\
	.field_name = reg_name ## __ ## field_name ## post_fix

#घोषणा CS_COMMON_MASK_SH_LIST_DCE_COMMON_BASE(mask_sh)\
	CS_SF(PLL_CNTL, PLL_REF_DIV_SRC, mask_sh),\
	CS_SF(PIXCLK1_RESYNC_CNTL, DCCG_DEEP_COLOR_CNTL1, mask_sh),\
	CS_SF(PLL_POST_DIV, PLL_POST_DIV_PIXCLK, mask_sh),\
	CS_SF(PLL_REF_DIV, PLL_REF_DIV, mask_sh)

#घोषणा CS_COMMON_MASK_SH_LIST_DCE_112(mask_sh)\
	CS_SF(PHYPLLA_PIXCLK_RESYNC_CNTL, PHYPLLA_DCCG_DEEP_COLOR_CNTL, mask_sh),\
	CS_SF(PHYPLLA_PIXCLK_RESYNC_CNTL, PHYPLLA_PIXCLK_DOUBLE_RATE_ENABLE, mask_sh)

#घोषणा CS_COMMON_REG_LIST_DCN2_0(index, pllid) \
		SRI(PIXCLK_RESYNC_CNTL, PHYPLL, pllid),\
		SRII(PHASE, DP_DTO, 0),\
		SRII(PHASE, DP_DTO, 1),\
		SRII(PHASE, DP_DTO, 2),\
		SRII(PHASE, DP_DTO, 3),\
		SRII(PHASE, DP_DTO, 4),\
		SRII(PHASE, DP_DTO, 5),\
		SRII(MODULO, DP_DTO, 0),\
		SRII(MODULO, DP_DTO, 1),\
		SRII(MODULO, DP_DTO, 2),\
		SRII(MODULO, DP_DTO, 3),\
		SRII(MODULO, DP_DTO, 4),\
		SRII(MODULO, DP_DTO, 5),\
		SRII(PIXEL_RATE_CNTL, OTG, 0),\
		SRII(PIXEL_RATE_CNTL, OTG, 1),\
		SRII(PIXEL_RATE_CNTL, OTG, 2),\
		SRII(PIXEL_RATE_CNTL, OTG, 3),\
		SRII(PIXEL_RATE_CNTL, OTG, 4),\
		SRII(PIXEL_RATE_CNTL, OTG, 5)

#घोषणा CS_COMMON_REG_LIST_DCN2_1(index, pllid) \
		SRI(PIXCLK_RESYNC_CNTL, PHYPLL, pllid),\
		SRII(PHASE, DP_DTO, 0),\
		SRII(PHASE, DP_DTO, 1),\
		SRII(PHASE, DP_DTO, 2),\
		SRII(PHASE, DP_DTO, 3),\
		SRII(MODULO, DP_DTO, 0),\
		SRII(MODULO, DP_DTO, 1),\
		SRII(MODULO, DP_DTO, 2),\
		SRII(MODULO, DP_DTO, 3),\
		SRII(PIXEL_RATE_CNTL, OTG, 0),\
		SRII(PIXEL_RATE_CNTL, OTG, 1),\
		SRII(PIXEL_RATE_CNTL, OTG, 2),\
		SRII(PIXEL_RATE_CNTL, OTG, 3)

#अगर defined(CONFIG_DRM_AMD_DC_DCN)
#घोषणा CS_COMMON_REG_LIST_DCN3_0(index, pllid) \
		SRI(PIXCLK_RESYNC_CNTL, PHYPLL, pllid),\
		SRII(PHASE, DP_DTO, 0),\
		SRII(PHASE, DP_DTO, 1),\
		SRII(PHASE, DP_DTO, 2),\
		SRII(PHASE, DP_DTO, 3),\
		SRII(MODULO, DP_DTO, 0),\
		SRII(MODULO, DP_DTO, 1),\
		SRII(MODULO, DP_DTO, 2),\
		SRII(MODULO, DP_DTO, 3),\
		SRII(PIXEL_RATE_CNTL, OTG, 0),\
		SRII(PIXEL_RATE_CNTL, OTG, 1),\
		SRII(PIXEL_RATE_CNTL, OTG, 2),\
		SRII(PIXEL_RATE_CNTL, OTG, 3)

#घोषणा CS_COMMON_REG_LIST_DCN3_01(index, pllid) \
		SRI(PIXCLK_RESYNC_CNTL, PHYPLL, pllid),\
		SRII(PHASE, DP_DTO, 0),\
		SRII(PHASE, DP_DTO, 1),\
		SRII(PHASE, DP_DTO, 2),\
		SRII(PHASE, DP_DTO, 3),\
		SRII(MODULO, DP_DTO, 0),\
		SRII(MODULO, DP_DTO, 1),\
		SRII(MODULO, DP_DTO, 2),\
		SRII(MODULO, DP_DTO, 3),\
		SRII(PIXEL_RATE_CNTL, OTG, 0),\
		SRII(PIXEL_RATE_CNTL, OTG, 1),\
		SRII(PIXEL_RATE_CNTL, OTG, 2),\
		SRII(PIXEL_RATE_CNTL, OTG, 3)
#पूर्ण_अगर

#अगर defined(CONFIG_DRM_AMD_DC_DCN)
#घोषणा CS_COMMON_REG_LIST_DCN3_02(index, pllid) \
		SRI(PIXCLK_RESYNC_CNTL, PHYPLL, pllid),\
		SRII(PHASE, DP_DTO, 0),\
		SRII(PHASE, DP_DTO, 1),\
		SRII(PHASE, DP_DTO, 2),\
		SRII(PHASE, DP_DTO, 3),\
		SRII(PHASE, DP_DTO, 4),\
		SRII(MODULO, DP_DTO, 0),\
		SRII(MODULO, DP_DTO, 1),\
		SRII(MODULO, DP_DTO, 2),\
		SRII(MODULO, DP_DTO, 3),\
		SRII(MODULO, DP_DTO, 4),\
		SRII(PIXEL_RATE_CNTL, OTG, 0),\
		SRII(PIXEL_RATE_CNTL, OTG, 1),\
		SRII(PIXEL_RATE_CNTL, OTG, 2),\
		SRII(PIXEL_RATE_CNTL, OTG, 3),\
		SRII(PIXEL_RATE_CNTL, OTG, 4)

#पूर्ण_अगर
#घोषणा CS_COMMON_MASK_SH_LIST_DCN2_0(mask_sh)\
	CS_SF(DP_DTO0_PHASE, DP_DTO0_PHASE, mask_sh),\
	CS_SF(DP_DTO0_MODULO, DP_DTO0_MODULO, mask_sh),\
	CS_SF(PHYPLLA_PIXCLK_RESYNC_CNTL, PHYPLLA_DCCG_DEEP_COLOR_CNTL, mask_sh),\
	CS_SF(OTG0_PIXEL_RATE_CNTL, DP_DTO0_ENABLE, mask_sh)

#अगर defined(CONFIG_DRM_AMD_DC_DCN)

#घोषणा CS_COMMON_REG_LIST_DCN1_0(index, pllid) \
		SRI(PIXCLK_RESYNC_CNTL, PHYPLL, pllid),\
		SRII(PHASE, DP_DTO, 0),\
		SRII(PHASE, DP_DTO, 1),\
		SRII(PHASE, DP_DTO, 2),\
		SRII(PHASE, DP_DTO, 3),\
		SRII(MODULO, DP_DTO, 0),\
		SRII(MODULO, DP_DTO, 1),\
		SRII(MODULO, DP_DTO, 2),\
		SRII(MODULO, DP_DTO, 3),\
		SRII(PIXEL_RATE_CNTL, OTG, 0), \
		SRII(PIXEL_RATE_CNTL, OTG, 1), \
		SRII(PIXEL_RATE_CNTL, OTG, 2), \
		SRII(PIXEL_RATE_CNTL, OTG, 3)

#घोषणा CS_COMMON_MASK_SH_LIST_DCN1_0(mask_sh)\
	CS_SF(DP_DTO0_PHASE, DP_DTO0_PHASE, mask_sh),\
	CS_SF(DP_DTO0_MODULO, DP_DTO0_MODULO, mask_sh),\
	CS_SF(PHYPLLA_PIXCLK_RESYNC_CNTL, PHYPLLA_DCCG_DEEP_COLOR_CNTL, mask_sh),\
	CS_SF(OTG0_PIXEL_RATE_CNTL, DP_DTO0_ENABLE, mask_sh)

#पूर्ण_अगर

#घोषणा CS_REG_FIELD_LIST(type) \
	type PLL_REF_DIV_SRC; \
	type DCCG_DEEP_COLOR_CNTL1; \
	type PHYPLLA_DCCG_DEEP_COLOR_CNTL; \
	type PHYPLLA_PIXCLK_DOUBLE_RATE_ENABLE; \
	type PLL_POST_DIV_PIXCLK; \
	type PLL_REF_DIV; \
	type DP_DTO0_PHASE; \
	type DP_DTO0_MODULO; \
	type DP_DTO0_ENABLE;

काष्ठा dce110_clk_src_shअगरt अणु
	CS_REG_FIELD_LIST(uपूर्णांक8_t)
पूर्ण;

काष्ठा dce110_clk_src_maskअणु
	CS_REG_FIELD_LIST(uपूर्णांक32_t)
पूर्ण;

काष्ठा dce110_clk_src_regs अणु
	uपूर्णांक32_t RESYNC_CNTL;
	uपूर्णांक32_t PIXCLK_RESYNC_CNTL;
	uपूर्णांक32_t PLL_CNTL;

	/* below are क्रम DTO.
	 * toकरो: should probably use dअगरferent काष्ठा to not waste space
	 */
	uपूर्णांक32_t PHASE[MAX_PIPES];
	uपूर्णांक32_t MODULO[MAX_PIPES];
	uपूर्णांक32_t PIXEL_RATE_CNTL[MAX_PIPES];
पूर्ण;

काष्ठा dce110_clk_src अणु
	काष्ठा घड़ी_source base;
	स्थिर काष्ठा dce110_clk_src_regs *regs;
	स्थिर काष्ठा dce110_clk_src_mask *cs_mask;
	स्थिर काष्ठा dce110_clk_src_shअगरt *cs_shअगरt;
	काष्ठा dc_bios *bios;

	काष्ठा spपढ़ो_spectrum_data *dp_ss_params;
	uपूर्णांक32_t dp_ss_params_cnt;
	काष्ठा spपढ़ो_spectrum_data *hdmi_ss_params;
	uपूर्णांक32_t hdmi_ss_params_cnt;
	काष्ठा spपढ़ो_spectrum_data *dvi_ss_params;
	uपूर्णांक32_t dvi_ss_params_cnt;
	काष्ठा spपढ़ो_spectrum_data *lvds_ss_params;
	uपूर्णांक32_t lvds_ss_params_cnt;

	uपूर्णांक32_t ext_clk_khz;
	uपूर्णांक32_t ref_freq_khz;

	काष्ठा calc_pll_घड़ी_source calc_pll;
	काष्ठा calc_pll_घड़ी_source calc_pll_hdmi;
पूर्ण;

bool dce110_clk_src_स्थिरruct(
	काष्ठा dce110_clk_src *clk_src,
	काष्ठा dc_context *ctx,
	काष्ठा dc_bios *bios,
	क्रमागत घड़ी_source_id,
	स्थिर काष्ठा dce110_clk_src_regs *regs,
	स्थिर काष्ठा dce110_clk_src_shअगरt *cs_shअगरt,
	स्थिर काष्ठा dce110_clk_src_mask *cs_mask);

bool dce112_clk_src_स्थिरruct(
	काष्ठा dce110_clk_src *clk_src,
	काष्ठा dc_context *ctx,
	काष्ठा dc_bios *bios,
	क्रमागत घड़ी_source_id id,
	स्थिर काष्ठा dce110_clk_src_regs *regs,
	स्थिर काष्ठा dce110_clk_src_shअगरt *cs_shअगरt,
	स्थिर काष्ठा dce110_clk_src_mask *cs_mask);

bool dcn20_clk_src_स्थिरruct(
	काष्ठा dce110_clk_src *clk_src,
	काष्ठा dc_context *ctx,
	काष्ठा dc_bios *bios,
	क्रमागत घड़ी_source_id id,
	स्थिर काष्ठा dce110_clk_src_regs *regs,
	स्थिर काष्ठा dce110_clk_src_shअगरt *cs_shअगरt,
	स्थिर काष्ठा dce110_clk_src_mask *cs_mask);

#अगर defined(CONFIG_DRM_AMD_DC_DCN)
bool dcn3_clk_src_स्थिरruct(
	काष्ठा dce110_clk_src *clk_src,
	काष्ठा dc_context *ctx,
	काष्ठा dc_bios *bios,
	क्रमागत घड़ी_source_id id,
	स्थिर काष्ठा dce110_clk_src_regs *regs,
	स्थिर काष्ठा dce110_clk_src_shअगरt *cs_shअगरt,
	स्थिर काष्ठा dce110_clk_src_mask *cs_mask);

bool dcn301_clk_src_स्थिरruct(
	काष्ठा dce110_clk_src *clk_src,
	काष्ठा dc_context *ctx,
	काष्ठा dc_bios *bios,
	क्रमागत घड़ी_source_id id,
	स्थिर काष्ठा dce110_clk_src_regs *regs,
	स्थिर काष्ठा dce110_clk_src_shअगरt *cs_shअगरt,
	स्थिर काष्ठा dce110_clk_src_mask *cs_mask);
#पूर्ण_अगर

/* this table is use to find *1.001 and /1.001 pixel rates from non-precise pixel rate */
काष्ठा pixel_rate_range_table_entry अणु
	अचिन्हित पूर्णांक range_min_khz;
	अचिन्हित पूर्णांक range_max_khz;
	अचिन्हित पूर्णांक target_pixel_rate_khz;
	अचिन्हित लघु mult_factor;
	अचिन्हित लघु भाग_factor;
पूर्ण;

#अगर defined(CONFIG_DRM_AMD_DC_DCN)
बाह्य स्थिर काष्ठा pixel_rate_range_table_entry video_optimized_pixel_rates[];
स्थिर काष्ठा pixel_rate_range_table_entry *look_up_in_video_optimized_rate_tlb(
		अचिन्हित पूर्णांक pixel_rate_khz);
#पूर्ण_अगर

#पूर्ण_अगर
