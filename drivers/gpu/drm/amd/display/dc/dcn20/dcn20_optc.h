<शैली गुरु>
/*
 * Copyright 2012-15 Advanced Micro Devices, Inc.
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

#अगर_अघोषित __DC_OPTC_DCN20_H__
#घोषणा __DC_OPTC_DCN20_H__

#समावेश "../dcn10/dcn10_optc.h"

#घोषणा TG_COMMON_REG_LIST_DCN2_0(inst) \
	TG_COMMON_REG_LIST_DCN(inst),\
	SRI(OTG_GLOBAL_CONTROL1, OTG, inst),\
	SRI(OTG_GLOBAL_CONTROL2, OTG, inst),\
	SRI(OTG_GSL_WINDOW_X, OTG, inst),\
	SRI(OTG_GSL_WINDOW_Y, OTG, inst),\
	SRI(OTG_VUPDATE_KEEPOUT, OTG, inst),\
	SRI(OTG_DSC_START_POSITION, OTG, inst),\
	SRI(OTG_CRC_CNTL2, OTG, inst),\
	SRI(OPTC_DATA_FORMAT_CONTROL, ODM, inst),\
	SRI(OPTC_BYTES_PER_PIXEL, ODM, inst),\
	SRI(OPTC_WIDTH_CONTROL, ODM, inst),\
	SRI(OPTC_MEMORY_CONFIG, ODM, inst),\
	SR(DWB_SOURCE_SELECT),\
	SRI(OTG_MANUAL_FLOW_CONTROL, OTG, inst)

#घोषणा TG_COMMON_MASK_SH_LIST_DCN2_0(mask_sh)\
	TG_COMMON_MASK_SH_LIST_DCN(mask_sh),\
	SF(OTG0_OTG_GLOBAL_CONTROL1, MASTER_UPDATE_LOCK_DB_X, mask_sh),\
	SF(OTG0_OTG_GLOBAL_CONTROL1, MASTER_UPDATE_LOCK_DB_Y, mask_sh),\
	SF(OTG0_OTG_GLOBAL_CONTROL1, MASTER_UPDATE_LOCK_DB_EN, mask_sh),\
	SF(OTG0_OTG_GLOBAL_CONTROL2, GLOBAL_UPDATE_LOCK_EN, mask_sh),\
	SF(OTG0_OTG_GLOBAL_CONTROL2, DIG_UPDATE_LOCATION, mask_sh),\
	SF(OTG0_OTG_DOUBLE_BUFFER_CONTROL, OTG_RANGE_TIMING_DBUF_UPDATE_MODE, mask_sh),\
	SF(OTG0_OTG_GSL_WINDOW_X, OTG_GSL_WINDOW_START_X, mask_sh),\
	SF(OTG0_OTG_GSL_WINDOW_X, OTG_GSL_WINDOW_END_X, mask_sh), \
	SF(OTG0_OTG_GSL_WINDOW_Y, OTG_GSL_WINDOW_START_Y, mask_sh),\
	SF(OTG0_OTG_GSL_WINDOW_Y, OTG_GSL_WINDOW_END_Y, mask_sh),\
	SF(OTG0_OTG_GSL_CONTROL, OTG_GSL_MASTER_MODE, mask_sh), \
	SF(OTG0_OTG_GSL_CONTROL, OTG_MASTER_UPDATE_LOCK_GSL_EN, mask_sh), \
	SF(OTG0_OTG_DSC_START_POSITION, OTG_DSC_START_POSITION_X, mask_sh), \
	SF(OTG0_OTG_DSC_START_POSITION, OTG_DSC_START_POSITION_LINE_NUM, mask_sh),\
	SF(OTG0_OTG_CRC_CNTL2, OTG_CRC_DSC_MODE, mask_sh),\
	SF(OTG0_OTG_CRC_CNTL2, OTG_CRC_DATA_STREAM_COMBINE_MODE, mask_sh),\
	SF(OTG0_OTG_CRC_CNTL2, OTG_CRC_DATA_STREAM_SPLIT_MODE, mask_sh),\
	SF(OTG0_OTG_CRC_CNTL2, OTG_CRC_DATA_FORMAT, mask_sh),\
	SF(ODM0_OPTC_DATA_SOURCE_SELECT, OPTC_SEG0_SRC_SEL, mask_sh),\
	SF(ODM0_OPTC_DATA_SOURCE_SELECT, OPTC_SEG1_SRC_SEL, mask_sh),\
	SF(ODM0_OPTC_DATA_SOURCE_SELECT, OPTC_NUM_OF_INPUT_SEGMENT, mask_sh),\
	SF(ODM0_OPTC_MEMORY_CONFIG, OPTC_MEM_SEL, mask_sh),\
	SF(ODM0_OPTC_DATA_FORMAT_CONTROL, OPTC_DATA_FORMAT, mask_sh),\
	SF(ODM0_OPTC_DATA_FORMAT_CONTROL, OPTC_DSC_MODE, mask_sh),\
	SF(ODM0_OPTC_BYTES_PER_PIXEL, OPTC_DSC_BYTES_PER_PIXEL, mask_sh),\
	SF(ODM0_OPTC_WIDTH_CONTROL, OPTC_DSC_SLICE_WIDTH, mask_sh),\
	SF(ODM0_OPTC_WIDTH_CONTROL, OPTC_SEGMENT_WIDTH, mask_sh),\
	SF(DWB_SOURCE_SELECT, OPTC_DWB0_SOURCE_SELECT, mask_sh),\
	SF(DWB_SOURCE_SELECT, OPTC_DWB1_SOURCE_SELECT, mask_sh),\
	SF(OTG0_OTG_MANUAL_FLOW_CONTROL, MANUAL_FLOW_CONTROL, mask_sh)

व्योम dcn20_timing_generator_init(काष्ठा optc *optc);

bool optc2_enable_crtc(काष्ठा timing_generator *optc);

व्योम optc2_set_gsl(काष्ठा timing_generator *optc,
		स्थिर काष्ठा gsl_params *params);

व्योम optc2_set_gsl_source_select(काष्ठा timing_generator *optc,
		पूर्णांक group_idx,
		uपूर्णांक32_t gsl_पढ़ोy_संकेत);

व्योम optc2_set_dsc_config(काष्ठा timing_generator *optc,
					क्रमागत optc_dsc_mode dsc_mode,
					uपूर्णांक32_t dsc_bytes_per_pixel,
					uपूर्णांक32_t dsc_slice_width);

व्योम optc2_set_odm_bypass(काष्ठा timing_generator *optc,
		स्थिर काष्ठा dc_crtc_timing *dc_crtc_timing);

व्योम optc2_set_odm_combine(काष्ठा timing_generator *optc, पूर्णांक *opp_id, पूर्णांक opp_cnt,
		काष्ठा dc_crtc_timing *timing);

व्योम optc2_get_optc_source(काष्ठा timing_generator *optc,
		uपूर्णांक32_t *num_of_src_opp,
		uपूर्णांक32_t *src_opp_id_0,
		uपूर्णांक32_t *src_opp_id_1);

व्योम optc2_triplebuffer_lock(काष्ठा timing_generator *optc);
व्योम optc2_triplebuffer_unlock(काष्ठा timing_generator *optc);
व्योम optc2_lock_द्विगुनbuffer_disable(काष्ठा timing_generator *optc);
व्योम optc2_lock_द्विगुनbuffer_enable(काष्ठा timing_generator *optc);
व्योम optc2_setup_manual_trigger(काष्ठा timing_generator *optc);
व्योम optc2_program_manual_trigger(काष्ठा timing_generator *optc);
bool optc2_is_two_pixels_per_contaपूर्णांकer(स्थिर काष्ठा dc_crtc_timing *timing);
bool optc2_configure_crc(काष्ठा timing_generator *optc,
			  स्थिर काष्ठा crc_params *params);
#पूर्ण_अगर /* __DC_OPTC_DCN20_H__ */
