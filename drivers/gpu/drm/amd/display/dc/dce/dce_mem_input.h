<शैली गुरु>
/*
 * Copyright 2016 Advanced Micro Devices, Inc.
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
#अगर_अघोषित __DCE_MEM_INPUT_H__
#घोषणा __DCE_MEM_INPUT_H__

#समावेश "dc_hw_types.h"
#समावेश "mem_input.h"

#घोषणा TO_DCE_MEM_INPUT(mem_input)\
	container_of(mem_input, काष्ठा dce_mem_input, base)

#घोषणा MI_DCE_BASE_REG_LIST(id)\
	SRI(GRPH_ENABLE, DCP, id),\
	SRI(GRPH_CONTROL, DCP, id),\
	SRI(GRPH_X_START, DCP, id),\
	SRI(GRPH_Y_START, DCP, id),\
	SRI(GRPH_X_END, DCP, id),\
	SRI(GRPH_Y_END, DCP, id),\
	SRI(GRPH_PITCH, DCP, id),\
	SRI(HW_ROTATION, DCP, id),\
	SRI(GRPH_SWAP_CNTL, DCP, id),\
	SRI(PRESCALE_GRPH_CONTROL, DCP, id),\
	SRI(GRPH_UPDATE, DCP, id),\
	SRI(GRPH_FLIP_CONTROL, DCP, id),\
	SRI(GRPH_PRIMARY_SURFACE_ADDRESS, DCP, id),\
	SRI(GRPH_PRIMARY_SURFACE_ADDRESS_HIGH, DCP, id),\
	SRI(GRPH_SECONDARY_SURFACE_ADDRESS, DCP, id),\
	SRI(GRPH_SECONDARY_SURFACE_ADDRESS_HIGH, DCP, id),\
	SRI(DPG_PIPE_ARBITRATION_CONTROL1, DMIF_PG, id),\
	SRI(DPG_WATERMARK_MASK_CONTROL, DMIF_PG, id),\
	SRI(DPG_PIPE_URGENCY_CONTROL, DMIF_PG, id),\
	SRI(DPG_PIPE_STUTTER_CONTROL, DMIF_PG, id),\
	SRI(DMIF_BUFFER_CONTROL, PIPE, id)

#घोषणा MI_DCE_PTE_REG_LIST(id)\
	SRI(DVMM_PTE_CONTROL, DCP, id),\
	SRI(DVMM_PTE_ARB_CONTROL, DCP, id)

#अगर defined(CONFIG_DRM_AMD_DC_SI)
#घोषणा MI_DCE6_REG_LIST(id)\
	SRI(GRPH_ENABLE, DCP, id),\
	SRI(GRPH_CONTROL, DCP, id),\
	SRI(GRPH_X_START, DCP, id),\
	SRI(GRPH_Y_START, DCP, id),\
	SRI(GRPH_X_END, DCP, id),\
	SRI(GRPH_Y_END, DCP, id),\
	SRI(GRPH_PITCH, DCP, id),\
	SRI(GRPH_SWAP_CNTL, DCP, id),\
	SRI(PRESCALE_GRPH_CONTROL, DCP, id),\
	SRI(GRPH_UPDATE, DCP, id),\
	SRI(GRPH_FLIP_CONTROL, DCP, id),\
	SRI(GRPH_PRIMARY_SURFACE_ADDRESS, DCP, id),\
	SRI(GRPH_PRIMARY_SURFACE_ADDRESS_HIGH, DCP, id),\
	SRI(GRPH_SECONDARY_SURFACE_ADDRESS, DCP, id),\
	SRI(GRPH_SECONDARY_SURFACE_ADDRESS_HIGH, DCP, id),\
	SRI(DPG_PIPE_ARBITRATION_CONTROL1, DMIF_PG, id),\
	SRI(DPG_PIPE_ARBITRATION_CONTROL3, DMIF_PG, id),\
	SRI(DPG_PIPE_NB_PSTATE_CHANGE_CONTROL, DMIF_PG, id),\
	SRI(DPG_PIPE_URGENCY_CONTROL, DMIF_PG, id),\
	SRI(DPG_PIPE_STUTTER_CONTROL, DMIF_PG, id),\
	SRI(DMIF_BUFFER_CONTROL, PIPE, id)
#पूर्ण_अगर

#घोषणा MI_DCE8_REG_LIST(id)\
	MI_DCE_BASE_REG_LIST(id),\
	SRI(DPG_PIPE_NB_PSTATE_CHANGE_CONTROL, DMIF_PG, id)

#घोषणा MI_DCE11_2_REG_LIST(id)\
	MI_DCE8_REG_LIST(id),\
	SRI(GRPH_PIPE_OUTSTANDING_REQUEST_LIMIT, DCP, id)

#घोषणा MI_DCE11_REG_LIST(id)\
	MI_DCE11_2_REG_LIST(id),\
	MI_DCE_PTE_REG_LIST(id)

#घोषणा MI_DCE12_REG_LIST(id)\
	MI_DCE_BASE_REG_LIST(id),\
	MI_DCE_PTE_REG_LIST(id),\
	SRI(GRPH_PIPE_OUTSTANDING_REQUEST_LIMIT, DCP, id),\
	SRI(DPG_PIPE_STUTTER_CONTROL2, DMIF_PG, id),\
	SRI(DPG_PIPE_LOW_POWER_CONTROL, DMIF_PG, id),\
	SR(DCHUB_FB_LOCATION),\
	SR(DCHUB_AGP_BASE),\
	SR(DCHUB_AGP_BOT),\
	SR(DCHUB_AGP_TOP)

काष्ठा dce_mem_input_रेजिस्टरs अणु
	/* DCP */
	uपूर्णांक32_t GRPH_ENABLE;
	uपूर्णांक32_t GRPH_CONTROL;
	uपूर्णांक32_t GRPH_X_START;
	uपूर्णांक32_t GRPH_Y_START;
	uपूर्णांक32_t GRPH_X_END;
	uपूर्णांक32_t GRPH_Y_END;
	uपूर्णांक32_t GRPH_PITCH;
	uपूर्णांक32_t HW_ROTATION;
	uपूर्णांक32_t GRPH_SWAP_CNTL;
	uपूर्णांक32_t PRESCALE_GRPH_CONTROL;
	uपूर्णांक32_t GRPH_PIPE_OUTSTANDING_REQUEST_LIMIT;
	uपूर्णांक32_t DVMM_PTE_CONTROL;
	uपूर्णांक32_t DVMM_PTE_ARB_CONTROL;
	uपूर्णांक32_t GRPH_UPDATE;
	uपूर्णांक32_t GRPH_FLIP_CONTROL;
	uपूर्णांक32_t GRPH_PRIMARY_SURFACE_ADDRESS;
	uपूर्णांक32_t GRPH_PRIMARY_SURFACE_ADDRESS_HIGH;
	uपूर्णांक32_t GRPH_SECONDARY_SURFACE_ADDRESS;
	uपूर्णांक32_t GRPH_SECONDARY_SURFACE_ADDRESS_HIGH;
	/* DMIF_PG */
	uपूर्णांक32_t DPG_PIPE_ARBITRATION_CONTROL1;
#अगर defined(CONFIG_DRM_AMD_DC_SI)
	uपूर्णांक32_t DPG_PIPE_ARBITRATION_CONTROL3;
#पूर्ण_अगर
	uपूर्णांक32_t DPG_WATERMARK_MASK_CONTROL;
	uपूर्णांक32_t DPG_PIPE_URGENCY_CONTROL;
	uपूर्णांक32_t DPG_PIPE_URGENT_LEVEL_CONTROL;
	uपूर्णांक32_t DPG_PIPE_NB_PSTATE_CHANGE_CONTROL;
	uपूर्णांक32_t DPG_PIPE_LOW_POWER_CONTROL;
	uपूर्णांक32_t DPG_PIPE_STUTTER_CONTROL;
	uपूर्णांक32_t DPG_PIPE_STUTTER_CONTROL2;
	/* DCI */
	uपूर्णांक32_t DMIF_BUFFER_CONTROL;
	/* MC_HUB */
	uपूर्णांक32_t MC_HUB_RDREQ_DMIF_LIMIT;
	/*DCHUB*/
	uपूर्णांक32_t DCHUB_FB_LOCATION;
	uपूर्णांक32_t DCHUB_AGP_BASE;
	uपूर्णांक32_t DCHUB_AGP_BOT;
	uपूर्णांक32_t DCHUB_AGP_TOP;
पूर्ण;

/* Set_Filed_क्रम_Block */
#घोषणा SFB(blk_name, reg_name, field_name, post_fix)\
	.field_name = blk_name ## reg_name ## __ ## field_name ## post_fix

#अगर defined(CONFIG_DRM_AMD_DC_SI)
#घोषणा MI_GFX6_TILE_MASK_SH_LIST(mask_sh, blk)\
	SFB(blk, GRPH_CONTROL, GRPH_NUM_BANKS, mask_sh),\
	SFB(blk, GRPH_CONTROL, GRPH_BANK_WIDTH, mask_sh),\
	SFB(blk, GRPH_CONTROL, GRPH_BANK_HEIGHT, mask_sh),\
	SFB(blk, GRPH_CONTROL, GRPH_MACRO_TILE_ASPECT, mask_sh),\
	SFB(blk, GRPH_CONTROL, GRPH_TILE_SPLIT, mask_sh),\
	SFB(blk, GRPH_CONTROL, GRPH_PIPE_CONFIG, mask_sh),\
	SFB(blk, GRPH_CONTROL, GRPH_ARRAY_MODE, mask_sh),\
	SFB(blk, GRPH_CONTROL, GRPH_COLOR_EXPANSION_MODE, mask_sh)
#पूर्ण_अगर

#घोषणा MI_GFX8_TILE_MASK_SH_LIST(mask_sh, blk)\
	SFB(blk, GRPH_CONTROL, GRPH_NUM_BANKS, mask_sh),\
	SFB(blk, GRPH_CONTROL, GRPH_BANK_WIDTH, mask_sh),\
	SFB(blk, GRPH_CONTROL, GRPH_BANK_HEIGHT, mask_sh),\
	SFB(blk, GRPH_CONTROL, GRPH_MACRO_TILE_ASPECT, mask_sh),\
	SFB(blk, GRPH_CONTROL, GRPH_TILE_SPLIT, mask_sh),\
	SFB(blk, GRPH_CONTROL, GRPH_MICRO_TILE_MODE, mask_sh),\
	SFB(blk, GRPH_CONTROL, GRPH_PIPE_CONFIG, mask_sh),\
	SFB(blk, GRPH_CONTROL, GRPH_ARRAY_MODE, mask_sh),\
	SFB(blk, GRPH_CONTROL, GRPH_COLOR_EXPANSION_MODE, mask_sh)

#घोषणा MI_DCP_MASK_SH_LIST(mask_sh, blk)\
	SFB(blk, GRPH_ENABLE, GRPH_ENABLE, mask_sh),\
	SFB(blk, GRPH_CONTROL, GRPH_DEPTH, mask_sh),\
	SFB(blk, GRPH_CONTROL, GRPH_FORMAT, mask_sh),\
	SFB(blk, GRPH_CONTROL, GRPH_NUM_BANKS, mask_sh),\
	SFB(blk, GRPH_X_START, GRPH_X_START, mask_sh),\
	SFB(blk, GRPH_Y_START, GRPH_Y_START, mask_sh),\
	SFB(blk, GRPH_X_END, GRPH_X_END, mask_sh),\
	SFB(blk, GRPH_Y_END, GRPH_Y_END, mask_sh),\
	SFB(blk, GRPH_PITCH, GRPH_PITCH, mask_sh),\
	SFB(blk, HW_ROTATION, GRPH_ROTATION_ANGLE, mask_sh),\
	SFB(blk, GRPH_SWAP_CNTL, GRPH_RED_CROSSBAR, mask_sh),\
	SFB(blk, GRPH_SWAP_CNTL, GRPH_BLUE_CROSSBAR, mask_sh),\
	SFB(blk, PRESCALE_GRPH_CONTROL, GRPH_PRESCALE_SELECT, mask_sh),\
	SFB(blk, PRESCALE_GRPH_CONTROL, GRPH_PRESCALE_R_SIGN, mask_sh),\
	SFB(blk, PRESCALE_GRPH_CONTROL, GRPH_PRESCALE_G_SIGN, mask_sh),\
	SFB(blk, PRESCALE_GRPH_CONTROL, GRPH_PRESCALE_B_SIGN, mask_sh),\
	SFB(blk, GRPH_SECONDARY_SURFACE_ADDRESS_HIGH, GRPH_SECONDARY_SURFACE_ADDRESS_HIGH, mask_sh),\
	SFB(blk, GRPH_SECONDARY_SURFACE_ADDRESS, GRPH_SECONDARY_SURFACE_ADDRESS, mask_sh),\
	SFB(blk, GRPH_PRIMARY_SURFACE_ADDRESS_HIGH, GRPH_PRIMARY_SURFACE_ADDRESS_HIGH, mask_sh),\
	SFB(blk, GRPH_PRIMARY_SURFACE_ADDRESS, GRPH_PRIMARY_SURFACE_ADDRESS, mask_sh),\
	SFB(blk, GRPH_UPDATE, GRPH_SURFACE_UPDATE_PENDING, mask_sh),\
	SFB(blk, GRPH_UPDATE, GRPH_UPDATE_LOCK, mask_sh),\
	SFB(blk, GRPH_FLIP_CONTROL, GRPH_SURFACE_UPDATE_H_RETRACE_EN, mask_sh)

#अगर defined(CONFIG_DRM_AMD_DC_SI)
#घोषणा MI_DCP_MASK_SH_LIST_DCE6(mask_sh, blk)\
	SFB(blk, GRPH_ENABLE, GRPH_ENABLE, mask_sh),\
	SFB(blk, GRPH_CONTROL, GRPH_DEPTH, mask_sh),\
	SFB(blk, GRPH_CONTROL, GRPH_FORMAT, mask_sh),\
	SFB(blk, GRPH_CONTROL, GRPH_NUM_BANKS, mask_sh),\
	SFB(blk, GRPH_X_START, GRPH_X_START, mask_sh),\
	SFB(blk, GRPH_Y_START, GRPH_Y_START, mask_sh),\
	SFB(blk, GRPH_X_END, GRPH_X_END, mask_sh),\
	SFB(blk, GRPH_Y_END, GRPH_Y_END, mask_sh),\
	SFB(blk, GRPH_PITCH, GRPH_PITCH, mask_sh),\
	SFB(blk, GRPH_SWAP_CNTL, GRPH_RED_CROSSBAR, mask_sh),\
	SFB(blk, GRPH_SWAP_CNTL, GRPH_BLUE_CROSSBAR, mask_sh),\
	SFB(blk, PRESCALE_GRPH_CONTROL, GRPH_PRESCALE_SELECT, mask_sh),\
	SFB(blk, PRESCALE_GRPH_CONTROL, GRPH_PRESCALE_R_SIGN, mask_sh),\
	SFB(blk, PRESCALE_GRPH_CONTROL, GRPH_PRESCALE_G_SIGN, mask_sh),\
	SFB(blk, PRESCALE_GRPH_CONTROL, GRPH_PRESCALE_B_SIGN, mask_sh),\
	SFB(blk, GRPH_SECONDARY_SURFACE_ADDRESS_HIGH, GRPH_SECONDARY_SURFACE_ADDRESS_HIGH, mask_sh),\
	SFB(blk, GRPH_SECONDARY_SURFACE_ADDRESS, GRPH_SECONDARY_SURFACE_ADDRESS, mask_sh),\
	SFB(blk, GRPH_PRIMARY_SURFACE_ADDRESS_HIGH, GRPH_PRIMARY_SURFACE_ADDRESS_HIGH, mask_sh),\
	SFB(blk, GRPH_PRIMARY_SURFACE_ADDRESS, GRPH_PRIMARY_SURFACE_ADDRESS, mask_sh),\
	SFB(blk, GRPH_UPDATE, GRPH_SURFACE_UPDATE_PENDING, mask_sh),\
	SFB(blk, GRPH_UPDATE, GRPH_UPDATE_LOCK, mask_sh),\
	SFB(blk, GRPH_FLIP_CONTROL, GRPH_SURFACE_UPDATE_H_RETRACE_EN, mask_sh)
#पूर्ण_अगर

#घोषणा MI_DCP_DCE11_MASK_SH_LIST(mask_sh, blk)\
	SFB(blk, GRPH_PIPE_OUTSTANDING_REQUEST_LIMIT, GRPH_PIPE_OUTSTANDING_REQUEST_LIMIT, mask_sh)

#घोषणा MI_DCP_PTE_MASK_SH_LIST(mask_sh, blk)\
	SFB(blk, DVMM_PTE_CONTROL, DVMM_PAGE_WIDTH, mask_sh),\
	SFB(blk, DVMM_PTE_CONTROL, DVMM_PAGE_HEIGHT, mask_sh),\
	SFB(blk, DVMM_PTE_CONTROL, DVMM_MIN_PTE_BEFORE_FLIP, mask_sh),\
	SFB(blk, DVMM_PTE_ARB_CONTROL, DVMM_PTE_REQ_PER_CHUNK, mask_sh),\
	SFB(blk, DVMM_PTE_ARB_CONTROL, DVMM_MAX_PTE_REQ_OUTSTANDING, mask_sh)

#अगर defined(CONFIG_DRM_AMD_DC_SI)
#घोषणा MI_DMIF_PG_MASK_SH_LIST_DCE6(mask_sh, blk)\
	SFB(blk, DPG_PIPE_ARBITRATION_CONTROL1, PIXEL_DURATION, mask_sh),\
	SFB(blk, DPG_PIPE_URGENCY_CONTROL, URGENCY_LOW_WATERMARK, mask_sh),\
	SFB(blk, DPG_PIPE_URGENCY_CONTROL, URGENCY_HIGH_WATERMARK, mask_sh),\
	SFB(blk, DPG_PIPE_STUTTER_CONTROL, STUTTER_ENABLE, mask_sh),\
	SFB(blk, DPG_PIPE_STUTTER_CONTROL, STUTTER_IGNORE_FBC, mask_sh),\
	SF(PIPE0_DMIF_BUFFER_CONTROL, DMIF_BUFFERS_ALLOCATED, mask_sh),\
	SF(PIPE0_DMIF_BUFFER_CONTROL, DMIF_BUFFERS_ALLOCATION_COMPLETED, mask_sh)

#घोषणा MI_DMIF_PG_MASK_SH_DCE6(mask_sh, blk)\
	SFB(blk, DPG_PIPE_ARBITRATION_CONTROL3, URGENCY_WATERMARK_MASK, mask_sh),\
	SFB(blk, DPG_PIPE_STUTTER_CONTROL, STUTTER_EXIT_SELF_REFRESH_WATERMARK_MASK, mask_sh),\
	SFB(blk, DPG_PIPE_STUTTER_CONTROL, STUTTER_EXIT_SELF_REFRESH_WATERMARK, mask_sh),\
	SFB(blk, DPG_PIPE_NB_PSTATE_CHANGE_CONTROL, NB_PSTATE_CHANGE_WATERMARK_MASK, mask_sh),\
	SFB(blk, DPG_PIPE_NB_PSTATE_CHANGE_CONTROL, NB_PSTATE_CHANGE_ENABLE, mask_sh),\
	SFB(blk, DPG_PIPE_NB_PSTATE_CHANGE_CONTROL, NB_PSTATE_CHANGE_URGENT_DURING_REQUEST, mask_sh),\
	SFB(blk, DPG_PIPE_NB_PSTATE_CHANGE_CONTROL, NB_PSTATE_CHANGE_NOT_SELF_REFRESH_DURING_REQUEST, mask_sh),\
	SFB(blk, DPG_PIPE_NB_PSTATE_CHANGE_CONTROL, NB_PSTATE_CHANGE_WATERMARK, mask_sh)

#घोषणा MI_DCE6_MASK_SH_LIST(mask_sh)\
	MI_DCP_MASK_SH_LIST_DCE6(mask_sh, ),\
	MI_DMIF_PG_MASK_SH_LIST_DCE6(mask_sh, ),\
	MI_DMIF_PG_MASK_SH_DCE6(mask_sh, ),\
	MI_GFX6_TILE_MASK_SH_LIST(mask_sh, )
#पूर्ण_अगर

#घोषणा MI_DMIF_PG_MASK_SH_LIST(mask_sh, blk)\
	SFB(blk, DPG_PIPE_ARBITRATION_CONTROL1, PIXEL_DURATION, mask_sh),\
	SFB(blk, DPG_WATERMARK_MASK_CONTROL, URGENCY_WATERMARK_MASK, mask_sh),\
	SFB(blk, DPG_WATERMARK_MASK_CONTROL, STUTTER_EXIT_SELF_REFRESH_WATERMARK_MASK, mask_sh),\
	SFB(blk, DPG_PIPE_URGENCY_CONTROL, URGENCY_LOW_WATERMARK, mask_sh),\
	SFB(blk, DPG_PIPE_URGENCY_CONTROL, URGENCY_HIGH_WATERMARK, mask_sh),\
	SFB(blk, DPG_PIPE_STUTTER_CONTROL, STUTTER_ENABLE, mask_sh),\
	SFB(blk, DPG_PIPE_STUTTER_CONTROL, STUTTER_IGNORE_FBC, mask_sh),\
	SF(PIPE0_DMIF_BUFFER_CONTROL, DMIF_BUFFERS_ALLOCATED, mask_sh),\
	SF(PIPE0_DMIF_BUFFER_CONTROL, DMIF_BUFFERS_ALLOCATION_COMPLETED, mask_sh)

#घोषणा MI_DMIF_PG_MASK_SH_DCE(mask_sh, blk)\
	SFB(blk, DPG_PIPE_STUTTER_CONTROL, STUTTER_EXIT_SELF_REFRESH_WATERMARK, mask_sh),\
	SFB(blk, DPG_WATERMARK_MASK_CONTROL, NB_PSTATE_CHANGE_WATERMARK_MASK, mask_sh),\
	SFB(blk, DPG_PIPE_NB_PSTATE_CHANGE_CONTROL, NB_PSTATE_CHANGE_ENABLE, mask_sh),\
	SFB(blk, DPG_PIPE_NB_PSTATE_CHANGE_CONTROL, NB_PSTATE_CHANGE_URGENT_DURING_REQUEST, mask_sh),\
	SFB(blk, DPG_PIPE_NB_PSTATE_CHANGE_CONTROL, NB_PSTATE_CHANGE_NOT_SELF_REFRESH_DURING_REQUEST, mask_sh),\
	SFB(blk, DPG_PIPE_NB_PSTATE_CHANGE_CONTROL, NB_PSTATE_CHANGE_WATERMARK, mask_sh)

#घोषणा MI_DCE8_MASK_SH_LIST(mask_sh)\
	MI_DCP_MASK_SH_LIST(mask_sh, ),\
	MI_DMIF_PG_MASK_SH_LIST(mask_sh, ),\
	MI_DMIF_PG_MASK_SH_DCE(mask_sh, ),\
	MI_GFX8_TILE_MASK_SH_LIST(mask_sh, )

#घोषणा MI_DCE11_2_MASK_SH_LIST(mask_sh)\
	MI_DCE8_MASK_SH_LIST(mask_sh),\
	MI_DCP_DCE11_MASK_SH_LIST(mask_sh, )

#घोषणा MI_DCE11_MASK_SH_LIST(mask_sh)\
	MI_DCE11_2_MASK_SH_LIST(mask_sh),\
	MI_DCP_PTE_MASK_SH_LIST(mask_sh, )

#घोषणा MI_GFX9_TILE_MASK_SH_LIST(mask_sh, blk)\
	SFB(blk, GRPH_CONTROL, GRPH_SW_MODE, mask_sh),\
	SFB(blk, GRPH_CONTROL, GRPH_SE_ENABLE, mask_sh),\
	SFB(blk, GRPH_CONTROL, GRPH_NUM_SHADER_ENGINES, mask_sh),\
	SFB(blk, GRPH_CONTROL, GRPH_NUM_PIPES, mask_sh),\
	SFB(blk, GRPH_CONTROL, GRPH_COLOR_EXPANSION_MODE, mask_sh)

#घोषणा MI_DCE12_DMIF_PG_MASK_SH_LIST(mask_sh, blk)\
	SFB(blk, DPG_PIPE_STUTTER_CONTROL2, STUTTER_EXIT_SELF_REFRESH_WATERMARK, mask_sh),\
	SFB(blk, DPG_PIPE_STUTTER_CONTROL2, STUTTER_ENTER_SELF_REFRESH_WATERMARK, mask_sh),\
	SFB(blk, DPG_PIPE_URGENT_LEVEL_CONTROL, URGENT_LEVEL_LOW_WATERMARK, mask_sh),\
	SFB(blk, DPG_PIPE_URGENT_LEVEL_CONTROL, URGENT_LEVEL_HIGH_WATERMARK, mask_sh),\
	SFB(blk, DPG_PIPE_URGENCY_CONTROL, URGENCY_LOW_WATERMARK, mask_sh),\
	SFB(blk, DPG_PIPE_URGENCY_CONTROL, URGENCY_HIGH_WATERMARK, mask_sh),\
	SFB(blk, DPG_WATERMARK_MASK_CONTROL, PSTATE_CHANGE_WATERMARK_MASK, mask_sh),\
	SFB(blk, DPG_PIPE_LOW_POWER_CONTROL, PSTATE_CHANGE_ENABLE, mask_sh),\
	SFB(blk, DPG_PIPE_LOW_POWER_CONTROL, PSTATE_CHANGE_URGENT_DURING_REQUEST, mask_sh),\
	SFB(blk, DPG_PIPE_LOW_POWER_CONTROL, PSTATE_CHANGE_NOT_SELF_REFRESH_DURING_REQUEST, mask_sh),\
	SFB(blk, DPG_PIPE_LOW_POWER_CONTROL, PSTATE_CHANGE_WATERMARK, mask_sh)

#घोषणा MI_GFX9_DCHUB_MASK_SH_LIST(mask_sh)\
	SF(DCHUB_FB_LOCATION, FB_TOP, mask_sh),\
	SF(DCHUB_FB_LOCATION, FB_BASE, mask_sh),\
	SF(DCHUB_AGP_BASE, AGP_BASE, mask_sh),\
	SF(DCHUB_AGP_BOT, AGP_BOT, mask_sh),\
	SF(DCHUB_AGP_TOP, AGP_TOP, mask_sh)

#घोषणा MI_DCE12_MASK_SH_LIST(mask_sh)\
	MI_DCP_MASK_SH_LIST(mask_sh, DCP0_),\
	SF(DCP0_GRPH_SECONDARY_SURFACE_ADDRESS, GRPH_SECONDARY_DFQ_ENABLE, mask_sh),\
	MI_DCP_DCE11_MASK_SH_LIST(mask_sh, DCP0_),\
	MI_DCP_PTE_MASK_SH_LIST(mask_sh, DCP0_),\
	MI_DMIF_PG_MASK_SH_LIST(mask_sh, DMIF_PG0_),\
	MI_DCE12_DMIF_PG_MASK_SH_LIST(mask_sh, DMIF_PG0_),\
	MI_GFX9_TILE_MASK_SH_LIST(mask_sh, DCP0_),\
	MI_GFX9_DCHUB_MASK_SH_LIST(mask_sh)

#घोषणा MI_REG_FIELD_LIST(type) \
	type GRPH_ENABLE; \
	type GRPH_X_START; \
	type GRPH_Y_START; \
	type GRPH_X_END; \
	type GRPH_Y_END; \
	type GRPH_PITCH; \
	type GRPH_ROTATION_ANGLE; \
	type GRPH_RED_CROSSBAR; \
	type GRPH_BLUE_CROSSBAR; \
	type GRPH_PRESCALE_SELECT; \
	type GRPH_PRESCALE_R_SIGN; \
	type GRPH_PRESCALE_G_SIGN; \
	type GRPH_PRESCALE_B_SIGN; \
	type GRPH_PIPE_OUTSTANDING_REQUEST_LIMIT; \
	type DVMM_PAGE_WIDTH; \
	type DVMM_PAGE_HEIGHT; \
	type DVMM_MIN_PTE_BEFORE_FLIP; \
	type DVMM_PTE_REQ_PER_CHUNK; \
	type DVMM_MAX_PTE_REQ_OUTSTANDING; \
	type GRPH_DEPTH; \
	type GRPH_FORMAT; \
	type GRPH_NUM_BANKS; \
	type GRPH_BANK_WIDTH;\
	type GRPH_BANK_HEIGHT;\
	type GRPH_MACRO_TILE_ASPECT;\
	type GRPH_TILE_SPLIT;\
	type GRPH_MICRO_TILE_MODE;\
	type GRPH_PIPE_CONFIG;\
	type GRPH_ARRAY_MODE;\
	type GRPH_COLOR_EXPANSION_MODE;\
	type GRPH_SW_MODE; \
	type GRPH_SE_ENABLE; \
	type GRPH_NUM_SHADER_ENGINES; \
	type GRPH_NUM_PIPES; \
	type GRPH_SECONDARY_SURFACE_ADDRESS_HIGH; \
	type GRPH_SECONDARY_SURFACE_ADDRESS; \
	type GRPH_SECONDARY_DFQ_ENABLE; \
	type GRPH_PRIMARY_SURFACE_ADDRESS_HIGH; \
	type GRPH_PRIMARY_SURFACE_ADDRESS; \
	type GRPH_SURFACE_UPDATE_PENDING; \
	type GRPH_SURFACE_UPDATE_H_RETRACE_EN; \
	type GRPH_UPDATE_LOCK; \
	type PIXEL_DURATION; \
	type URGENCY_WATERMARK_MASK; \
	type PSTATE_CHANGE_WATERMARK_MASK; \
	type NB_PSTATE_CHANGE_WATERMARK_MASK; \
	type STUTTER_EXIT_SELF_REFRESH_WATERMARK_MASK; \
	type URGENCY_LOW_WATERMARK; \
	type URGENCY_HIGH_WATERMARK; \
	type URGENT_LEVEL_LOW_WATERMARK;\
	type URGENT_LEVEL_HIGH_WATERMARK;\
	type NB_PSTATE_CHANGE_ENABLE; \
	type NB_PSTATE_CHANGE_URGENT_DURING_REQUEST; \
	type NB_PSTATE_CHANGE_NOT_SELF_REFRESH_DURING_REQUEST; \
	type NB_PSTATE_CHANGE_WATERMARK; \
	type PSTATE_CHANGE_ENABLE; \
	type PSTATE_CHANGE_URGENT_DURING_REQUEST; \
	type PSTATE_CHANGE_NOT_SELF_REFRESH_DURING_REQUEST; \
	type PSTATE_CHANGE_WATERMARK; \
	type STUTTER_ENABLE; \
	type STUTTER_IGNORE_FBC; \
	type STUTTER_EXIT_SELF_REFRESH_WATERMARK; \
	type STUTTER_ENTER_SELF_REFRESH_WATERMARK; \
	type DMIF_BUFFERS_ALLOCATED; \
	type DMIF_BUFFERS_ALLOCATION_COMPLETED; \
	type ENABLE; /* MC_HUB_RDREQ_DMIF_LIMIT */\
	type FB_BASE; \
	type FB_TOP; \
	type AGP_BASE; \
	type AGP_TOP; \
	type AGP_BOT; \

काष्ठा dce_mem_input_shअगरt अणु
	MI_REG_FIELD_LIST(uपूर्णांक8_t)
पूर्ण;

काष्ठा dce_mem_input_mask अणु
	MI_REG_FIELD_LIST(uपूर्णांक32_t)
पूर्ण;

काष्ठा dce_mem_input_wa अणु
	uपूर्णांक8_t single_head_rdreq_dmअगर_limit;
पूर्ण;

काष्ठा dce_mem_input अणु
	काष्ठा mem_input base;

	स्थिर काष्ठा dce_mem_input_रेजिस्टरs *regs;
	स्थिर काष्ठा dce_mem_input_shअगरt *shअगरts;
	स्थिर काष्ठा dce_mem_input_mask *masks;

	काष्ठा dce_mem_input_wa wa;
पूर्ण;

व्योम dce_mem_input_स्थिरruct(
	काष्ठा dce_mem_input *dce_mi,
	काष्ठा dc_context *ctx,
	पूर्णांक inst,
	स्थिर काष्ठा dce_mem_input_रेजिस्टरs *regs,
	स्थिर काष्ठा dce_mem_input_shअगरt *mi_shअगरt,
	स्थिर काष्ठा dce_mem_input_mask *mi_mask);

#अगर defined(CONFIG_DRM_AMD_DC_SI)
व्योम dce60_mem_input_स्थिरruct(
	काष्ठा dce_mem_input *dce_mi,
	काष्ठा dc_context *ctx,
	पूर्णांक inst,
	स्थिर काष्ठा dce_mem_input_रेजिस्टरs *regs,
	स्थिर काष्ठा dce_mem_input_shअगरt *mi_shअगरt,
	स्थिर काष्ठा dce_mem_input_mask *mi_mask);
#पूर्ण_अगर

व्योम dce112_mem_input_स्थिरruct(
	काष्ठा dce_mem_input *dce_mi,
	काष्ठा dc_context *ctx,
	पूर्णांक inst,
	स्थिर काष्ठा dce_mem_input_रेजिस्टरs *regs,
	स्थिर काष्ठा dce_mem_input_shअगरt *mi_shअगरt,
	स्थिर काष्ठा dce_mem_input_mask *mi_mask);

व्योम dce120_mem_input_स्थिरruct(
	काष्ठा dce_mem_input *dce_mi,
	काष्ठा dc_context *ctx,
	पूर्णांक inst,
	स्थिर काष्ठा dce_mem_input_रेजिस्टरs *regs,
	स्थिर काष्ठा dce_mem_input_shअगरt *mi_shअगरt,
	स्थिर काष्ठा dce_mem_input_mask *mi_mask);

#पूर्ण_अगर /*__DCE_MEM_INPUT_H__*/
