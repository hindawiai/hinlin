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
 */

#अगर_अघोषित __SMU_CMN_H__
#घोषणा __SMU_CMN_H__

#समावेश "amdgpu_smu.h"

#अगर defined(SWSMU_CODE_LAYER_L2) || defined(SWSMU_CODE_LAYER_L3) || defined(SWSMU_CODE_LAYER_L4)
पूर्णांक smu_cmn_send_msg_without_रुकोing(काष्ठा smu_context *smu,
				     uपूर्णांक16_t msg, uपूर्णांक32_t param);
पूर्णांक smu_cmn_send_smc_msg_with_param(काष्ठा smu_context *smu,
				    क्रमागत smu_message_type msg,
				    uपूर्णांक32_t param,
				    uपूर्णांक32_t *पढ़ो_arg);

पूर्णांक smu_cmn_send_smc_msg(काष्ठा smu_context *smu,
			 क्रमागत smu_message_type msg,
			 uपूर्णांक32_t *पढ़ो_arg);

पूर्णांक smu_cmn_रुको_क्रम_response(काष्ठा smu_context *smu);

पूर्णांक smu_cmn_to_asic_specअगरic_index(काष्ठा smu_context *smu,
				   क्रमागत smu_cmn2asic_mapping_type type,
				   uपूर्णांक32_t index);

पूर्णांक smu_cmn_feature_is_supported(काष्ठा smu_context *smu,
				 क्रमागत smu_feature_mask mask);

पूर्णांक smu_cmn_feature_is_enabled(काष्ठा smu_context *smu,
			       क्रमागत smu_feature_mask mask);

bool smu_cmn_clk_dpm_is_enabled(काष्ठा smu_context *smu,
				क्रमागत smu_clk_type clk_type);

पूर्णांक smu_cmn_get_enabled_mask(काष्ठा smu_context *smu,
			     uपूर्णांक32_t *feature_mask,
			     uपूर्णांक32_t num);

पूर्णांक smu_cmn_get_enabled_32_bits_mask(काष्ठा smu_context *smu,
					uपूर्णांक32_t *feature_mask,
					uपूर्णांक32_t num);

पूर्णांक smu_cmn_feature_update_enable_state(काष्ठा smu_context *smu,
					uपूर्णांक64_t feature_mask,
					bool enabled);

पूर्णांक smu_cmn_feature_set_enabled(काष्ठा smu_context *smu,
				क्रमागत smu_feature_mask mask,
				bool enable);

माप_प्रकार smu_cmn_get_pp_feature_mask(काष्ठा smu_context *smu,
				   अक्षर *buf);

पूर्णांक smu_cmn_set_pp_feature_mask(काष्ठा smu_context *smu,
				uपूर्णांक64_t new_mask);

पूर्णांक smu_cmn_disable_all_features_with_exception(काष्ठा smu_context *smu,
						क्रमागत smu_feature_mask mask);

पूर्णांक smu_cmn_get_smc_version(काष्ठा smu_context *smu,
			    uपूर्णांक32_t *अगर_version,
			    uपूर्णांक32_t *smu_version);

पूर्णांक smu_cmn_update_table(काष्ठा smu_context *smu,
			 क्रमागत smu_table_id table_index,
			 पूर्णांक argument,
			 व्योम *table_data,
			 bool drv2smu);

पूर्णांक smu_cmn_ग_लिखो_watermarks_table(काष्ठा smu_context *smu);

पूर्णांक smu_cmn_ग_लिखो_pptable(काष्ठा smu_context *smu);

पूर्णांक smu_cmn_get_metrics_table_locked(काष्ठा smu_context *smu,
				     व्योम *metrics_table,
				     bool bypass_cache);

पूर्णांक smu_cmn_get_metrics_table(काष्ठा smu_context *smu,
			      व्योम *metrics_table,
			      bool bypass_cache);

व्योम smu_cmn_init_soft_gpu_metrics(व्योम *table, uपूर्णांक8_t frev, uपूर्णांक8_t crev);

पूर्णांक smu_cmn_set_mp1_state(काष्ठा smu_context *smu,
			  क्रमागत pp_mp1_state mp1_state);

#पूर्ण_अगर
#पूर्ण_अगर
