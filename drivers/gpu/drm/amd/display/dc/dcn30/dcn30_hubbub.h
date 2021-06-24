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

#अगर_अघोषित __DC_HUBBUB_DCN30_H__
#घोषणा __DC_HUBBUB_DCN30_H__

#समावेश "dcn21/dcn21_hubbub.h"

#घोषणा HUBBUB_REG_LIST_DCN3AG(id)\
	HUBBUB_REG_LIST_DCN21()

#घोषणा HUBBUB_MASK_SH_LIST_DCN3AG(mask_sh)\
	HUBBUB_MASK_SH_LIST_DCN21(mask_sh)

#घोषणा HUBBUB_REG_LIST_DCN30(id)\
	HUBBUB_REG_LIST_DCN20_COMMON(), \
	HUBBUB_SR_WATERMARK_REG_LIST(), \
	SR(DCHUBBUB_ARB_FRAC_URG_BW_NOM_A),\
	SR(DCHUBBUB_ARB_FRAC_URG_BW_NOM_B),\
	SR(DCHUBBUB_ARB_FRAC_URG_BW_NOM_C),\
	SR(DCHUBBUB_ARB_FRAC_URG_BW_NOM_D),\
	SR(DCHUBBUB_ARB_FRAC_URG_BW_FLIP_A),\
	SR(DCHUBBUB_ARB_FRAC_URG_BW_FLIP_B),\
	SR(DCHUBBUB_ARB_FRAC_URG_BW_FLIP_C),\
	SR(DCHUBBUB_ARB_FRAC_URG_BW_FLIP_D),\
	SR(DCHUBBUB_ARB_REFCYC_PER_TRIP_TO_MEMORY_A),\
	SR(DCHUBBUB_ARB_REFCYC_PER_TRIP_TO_MEMORY_B),\
	SR(DCHUBBUB_ARB_REFCYC_PER_TRIP_TO_MEMORY_C),\
	SR(DCHUBBUB_ARB_REFCYC_PER_TRIP_TO_MEMORY_D)

#घोषणा HUBBUB_MASK_SH_LIST_DCN30(mask_sh)\
	HUBBUB_MASK_SH_LIST_DCN_COMMON(mask_sh), \
	HUBBUB_MASK_SH_LIST_STUTTER(mask_sh), \
	HUBBUB_SF(DCHUBBUB_GLOBAL_TIMER_CNTL, DCHUBBUB_GLOBAL_TIMER_REFDIV, mask_sh), \
	HUBBUB_SF(DCN_VM_FB_LOCATION_BASE, FB_BASE, mask_sh), \
	HUBBUB_SF(DCN_VM_FB_LOCATION_TOP, FB_TOP, mask_sh), \
	HUBBUB_SF(DCN_VM_FB_OFFSET, FB_OFFSET, mask_sh), \
	HUBBUB_SF(DCN_VM_AGP_BOT, AGP_BOT, mask_sh), \
	HUBBUB_SF(DCN_VM_AGP_TOP, AGP_TOP, mask_sh), \
	HUBBUB_SF(DCN_VM_AGP_BASE, AGP_BASE, mask_sh), \
	HUBBUB_SF(DCHUBBUB_ARB_FRAC_URG_BW_FLIP_A, DCHUBBUB_ARB_FRAC_URG_BW_FLIP_A, mask_sh), \
	HUBBUB_SF(DCHUBBUB_ARB_FRAC_URG_BW_FLIP_B, DCHUBBUB_ARB_FRAC_URG_BW_FLIP_B, mask_sh), \
	HUBBUB_SF(DCHUBBUB_ARB_FRAC_URG_BW_FLIP_C, DCHUBBUB_ARB_FRAC_URG_BW_FLIP_C, mask_sh), \
	HUBBUB_SF(DCHUBBUB_ARB_FRAC_URG_BW_FLIP_D, DCHUBBUB_ARB_FRAC_URG_BW_FLIP_D, mask_sh), \
	HUBBUB_SF(DCHUBBUB_ARB_FRAC_URG_BW_NOM_A, DCHUBBUB_ARB_FRAC_URG_BW_NOM_A, mask_sh), \
	HUBBUB_SF(DCHUBBUB_ARB_FRAC_URG_BW_NOM_B, DCHUBBUB_ARB_FRAC_URG_BW_NOM_B, mask_sh), \
	HUBBUB_SF(DCHUBBUB_ARB_FRAC_URG_BW_NOM_C, DCHUBBUB_ARB_FRAC_URG_BW_NOM_C, mask_sh), \
	HUBBUB_SF(DCHUBBUB_ARB_FRAC_URG_BW_NOM_D, DCHUBBUB_ARB_FRAC_URG_BW_NOM_D, mask_sh), \
	HUBBUB_SF(DCHUBBUB_ARB_REFCYC_PER_TRIP_TO_MEMORY_A, DCHUBBUB_ARB_REFCYC_PER_TRIP_TO_MEMORY_A, mask_sh), \
	HUBBUB_SF(DCHUBBUB_ARB_REFCYC_PER_TRIP_TO_MEMORY_B, DCHUBBUB_ARB_REFCYC_PER_TRIP_TO_MEMORY_B, mask_sh), \
	HUBBUB_SF(DCHUBBUB_ARB_REFCYC_PER_TRIP_TO_MEMORY_C, DCHUBBUB_ARB_REFCYC_PER_TRIP_TO_MEMORY_C, mask_sh), \
	HUBBUB_SF(DCHUBBUB_ARB_REFCYC_PER_TRIP_TO_MEMORY_D, DCHUBBUB_ARB_REFCYC_PER_TRIP_TO_MEMORY_D, mask_sh), \
	HUBBUB_SF(DCHUBBUB_ARB_DATA_URGENCY_WATERMARK_A, DCHUBBUB_ARB_VM_ROW_URGENCY_WATERMARK_A, mask_sh), \
	HUBBUB_SF(DCHUBBUB_ARB_DATA_URGENCY_WATERMARK_B, DCHUBBUB_ARB_VM_ROW_URGENCY_WATERMARK_B, mask_sh), \
	HUBBUB_SF(DCHUBBUB_ARB_DATA_URGENCY_WATERMARK_C, DCHUBBUB_ARB_VM_ROW_URGENCY_WATERMARK_C, mask_sh), \
	HUBBUB_SF(DCHUBBUB_ARB_DATA_URGENCY_WATERMARK_D, DCHUBBUB_ARB_VM_ROW_URGENCY_WATERMARK_D, mask_sh), \
	HUBBUB_SF(DCHUBBUB_ARB_ALLOW_SR_ENTER_WATERMARK_A, DCHUBBUB_ARB_VM_ROW_ALLOW_SR_ENTER_WATERMARK_A, mask_sh), \
	HUBBUB_SF(DCHUBBUB_ARB_ALLOW_SR_ENTER_WATERMARK_B, DCHUBBUB_ARB_VM_ROW_ALLOW_SR_ENTER_WATERMARK_B, mask_sh), \
	HUBBUB_SF(DCHUBBUB_ARB_ALLOW_SR_ENTER_WATERMARK_C, DCHUBBUB_ARB_VM_ROW_ALLOW_SR_ENTER_WATERMARK_C, mask_sh), \
	HUBBUB_SF(DCHUBBUB_ARB_ALLOW_SR_ENTER_WATERMARK_D, DCHUBBUB_ARB_VM_ROW_ALLOW_SR_ENTER_WATERMARK_D, mask_sh), \
	HUBBUB_SF(DCHUBBUB_ARB_ALLOW_SR_EXIT_WATERMARK_A, DCHUBBUB_ARB_VM_ROW_ALLOW_SR_EXIT_WATERMARK_A, mask_sh), \
	HUBBUB_SF(DCHUBBUB_ARB_ALLOW_SR_EXIT_WATERMARK_B, DCHUBBUB_ARB_VM_ROW_ALLOW_SR_EXIT_WATERMARK_B, mask_sh), \
	HUBBUB_SF(DCHUBBUB_ARB_ALLOW_SR_EXIT_WATERMARK_C, DCHUBBUB_ARB_VM_ROW_ALLOW_SR_EXIT_WATERMARK_C, mask_sh), \
	HUBBUB_SF(DCHUBBUB_ARB_ALLOW_SR_EXIT_WATERMARK_D, DCHUBBUB_ARB_VM_ROW_ALLOW_SR_EXIT_WATERMARK_D, mask_sh), \
	HUBBUB_SF(DCHUBBUB_ARB_ALLOW_DRAM_CLK_CHANGE_WATERMARK_A, DCHUBBUB_ARB_VM_ROW_ALLOW_DRAM_CLK_CHANGE_WATERMARK_A, mask_sh), \
	HUBBUB_SF(DCHUBBUB_ARB_ALLOW_DRAM_CLK_CHANGE_WATERMARK_B, DCHUBBUB_ARB_VM_ROW_ALLOW_DRAM_CLK_CHANGE_WATERMARK_B, mask_sh), \
	HUBBUB_SF(DCHUBBUB_ARB_ALLOW_DRAM_CLK_CHANGE_WATERMARK_C, DCHUBBUB_ARB_VM_ROW_ALLOW_DRAM_CLK_CHANGE_WATERMARK_C, mask_sh), \
	HUBBUB_SF(DCHUBBUB_ARB_ALLOW_DRAM_CLK_CHANGE_WATERMARK_D, DCHUBBUB_ARB_VM_ROW_ALLOW_DRAM_CLK_CHANGE_WATERMARK_D, mask_sh)

व्योम hubbub3_स्थिरruct(काष्ठा dcn20_hubbub *hubbub3,
	काष्ठा dc_context *ctx,
	स्थिर काष्ठा dcn_hubbub_रेजिस्टरs *hubbub_regs,
	स्थिर काष्ठा dcn_hubbub_shअगरt *hubbub_shअगरt,
	स्थिर काष्ठा dcn_hubbub_mask *hubbub_mask);

पूर्णांक hubbub3_init_dchub_sys_ctx(काष्ठा hubbub *hubbub,
		काष्ठा dcn_hubbub_phys_addr_config *pa_config);

bool hubbub3_dcc_support_swizzle(
		क्रमागत swizzle_mode_values swizzle,
		अचिन्हित पूर्णांक bytes_per_element,
		क्रमागत segment_order *segment_order_horz,
		क्रमागत segment_order *segment_order_vert);

व्योम hubbub3_क्रमce_wm_propagate_to_pipes(काष्ठा hubbub *hubbub);

bool hubbub3_get_dcc_compression_cap(काष्ठा hubbub *hubbub,
		स्थिर काष्ठा dc_dcc_surface_param *input,
		काष्ठा dc_surface_dcc_cap *output);

bool hubbub3_program_watermarks(
		काष्ठा hubbub *hubbub,
		काष्ठा dcn_watermark_set *watermarks,
		अचिन्हित पूर्णांक refclk_mhz,
		bool safe_to_lower);

व्योम hubbub3_क्रमce_pstate_change_control(काष्ठा hubbub *hubbub,
		bool क्रमce, bool allow);

व्योम hubbub3_init_watermarks(काष्ठा hubbub *hubbub);

#पूर्ण_अगर
