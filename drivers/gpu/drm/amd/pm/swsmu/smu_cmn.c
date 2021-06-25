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

#घोषणा SWSMU_CODE_LAYER_L4

#समावेश "amdgpu.h"
#समावेश "amdgpu_smu.h"
#समावेश "smu_cmn.h"
#समावेश "soc15_common.h"

/*
 * DO NOT use these क्रम err/warn/info/debug messages.
 * Use dev_err, dev_warn, dev_info and dev_dbg instead.
 * They are more MGPU मित्रly.
 */
#अघोषित pr_err
#अघोषित pr_warn
#अघोषित pr_info
#अघोषित pr_debug

/*
 * Although these are defined in each ASIC's specअगरic header file.
 * They share the same definitions and values. That makes common
 * APIs क्रम SMC messages issuing क्रम all ASICs possible.
 */
#घोषणा mmMP1_SMN_C2PMSG_66                                                                            0x0282
#घोषणा mmMP1_SMN_C2PMSG_66_BASE_IDX                                                                   0

#घोषणा mmMP1_SMN_C2PMSG_82                                                                            0x0292
#घोषणा mmMP1_SMN_C2PMSG_82_BASE_IDX                                                                   0

#घोषणा mmMP1_SMN_C2PMSG_90                                                                            0x029a
#घोषणा mmMP1_SMN_C2PMSG_90_BASE_IDX                                                                   0

#घोषणा MP1_C2PMSG_90__CONTENT_MASK                                                                    0xFFFFFFFFL

#अघोषित __SMU_DUMMY_MAP
#घोषणा __SMU_DUMMY_MAP(type)	#type
अटल स्थिर अक्षर* __smu_message_names[] = अणु
	SMU_MESSAGE_TYPES
पूर्ण;

अटल स्थिर अक्षर *smu_get_message_name(काष्ठा smu_context *smu,
					क्रमागत smu_message_type type)
अणु
	अगर (type < 0 || type >= SMU_MSG_MAX_COUNT)
		वापस "unknown smu message";

	वापस __smu_message_names[type];
पूर्ण

अटल व्योम smu_cmn_पढ़ो_arg(काष्ठा smu_context *smu,
			     uपूर्णांक32_t *arg)
अणु
	काष्ठा amdgpu_device *adev = smu->adev;

	*arg = RREG32_SOC15(MP1, 0, mmMP1_SMN_C2PMSG_82);
पूर्ण

पूर्णांक smu_cmn_रुको_क्रम_response(काष्ठा smu_context *smu)
अणु
	काष्ठा amdgpu_device *adev = smu->adev;
	uपूर्णांक32_t cur_value, i, समयout = adev->usec_समयout * 20;

	क्रम (i = 0; i < समयout; i++) अणु
		cur_value = RREG32_SOC15(MP1, 0, mmMP1_SMN_C2PMSG_90);
		अगर ((cur_value & MP1_C2PMSG_90__CONTENT_MASK) != 0)
			वापस cur_value;

		udelay(1);
	पूर्ण

	/* समयout means wrong logic */
	अगर (i == समयout)
		वापस -ETIME;

	वापस RREG32_SOC15(MP1, 0, mmMP1_SMN_C2PMSG_90);
पूर्ण

पूर्णांक smu_cmn_send_msg_without_रुकोing(काष्ठा smu_context *smu,
				     uपूर्णांक16_t msg, uपूर्णांक32_t param)
अणु
	काष्ठा amdgpu_device *adev = smu->adev;
	पूर्णांक ret;

	ret = smu_cmn_रुको_क्रम_response(smu);
	अगर (ret != 0x1) अणु
		dev_err(adev->dev, "Msg issuing pre-check failed and "
		       "SMU may be not in the right state!\n");
		अगर (ret != -ETIME)
			ret = -EIO;
		वापस ret;
	पूर्ण

	WREG32_SOC15(MP1, 0, mmMP1_SMN_C2PMSG_90, 0);
	WREG32_SOC15(MP1, 0, mmMP1_SMN_C2PMSG_82, param);
	WREG32_SOC15(MP1, 0, mmMP1_SMN_C2PMSG_66, msg);

	वापस 0;
पूर्ण

पूर्णांक smu_cmn_send_smc_msg_with_param(काष्ठा smu_context *smu,
				    क्रमागत smu_message_type msg,
				    uपूर्णांक32_t param,
				    uपूर्णांक32_t *पढ़ो_arg)
अणु
	काष्ठा amdgpu_device *adev = smu->adev;
	पूर्णांक ret = 0, index = 0;

	अगर (smu->adev->in_pci_err_recovery)
		वापस 0;

	index = smu_cmn_to_asic_specअगरic_index(smu,
					       CMN2ASIC_MAPPING_MSG,
					       msg);
	अगर (index < 0)
		वापस index == -EACCES ? 0 : index;

	mutex_lock(&smu->message_lock);
	ret = smu_cmn_send_msg_without_रुकोing(smu, (uपूर्णांक16_t)index, param);
	अगर (ret)
		जाओ out;

	ret = smu_cmn_रुको_क्रम_response(smu);
	अगर (ret != 0x1) अणु
		अगर (ret == -ETIME) अणु
			dev_err(adev->dev, "message: %15s (%d) \tparam: 0x%08x is timeout (no response)\n",
				smu_get_message_name(smu, msg), index, param);
		पूर्ण अन्यथा अणु
			dev_err(adev->dev, "failed send message: %15s (%d) \tparam: 0x%08x response %#x\n",
				smu_get_message_name(smu, msg), index, param,
				ret);
			ret = -EIO;
		पूर्ण
		जाओ out;
	पूर्ण

	अगर (पढ़ो_arg)
		smu_cmn_पढ़ो_arg(smu, पढ़ो_arg);

	ret = 0; /* 0 as driver वापस value */
out:
	mutex_unlock(&smu->message_lock);
	वापस ret;
पूर्ण

पूर्णांक smu_cmn_send_smc_msg(काष्ठा smu_context *smu,
			 क्रमागत smu_message_type msg,
			 uपूर्णांक32_t *पढ़ो_arg)
अणु
	वापस smu_cmn_send_smc_msg_with_param(smu,
					       msg,
					       0,
					       पढ़ो_arg);
पूर्ण

पूर्णांक smu_cmn_to_asic_specअगरic_index(काष्ठा smu_context *smu,
				   क्रमागत smu_cmn2asic_mapping_type type,
				   uपूर्णांक32_t index)
अणु
	काष्ठा cmn2asic_msg_mapping msg_mapping;
	काष्ठा cmn2asic_mapping mapping;

	चयन (type) अणु
	हाल CMN2ASIC_MAPPING_MSG:
		अगर (index >= SMU_MSG_MAX_COUNT ||
		    !smu->message_map)
			वापस -EINVAL;

		msg_mapping = smu->message_map[index];
		अगर (!msg_mapping.valid_mapping)
			वापस -EINVAL;

		अगर (amdgpu_sriov_vf(smu->adev) &&
		    !msg_mapping.valid_in_vf)
			वापस -EACCES;

		वापस msg_mapping.map_to;

	हाल CMN2ASIC_MAPPING_CLK:
		अगर (index >= SMU_CLK_COUNT ||
		    !smu->घड़ी_map)
			वापस -EINVAL;

		mapping = smu->घड़ी_map[index];
		अगर (!mapping.valid_mapping)
			वापस -EINVAL;

		वापस mapping.map_to;

	हाल CMN2ASIC_MAPPING_FEATURE:
		अगर (index >= SMU_FEATURE_COUNT ||
		    !smu->feature_map)
			वापस -EINVAL;

		mapping = smu->feature_map[index];
		अगर (!mapping.valid_mapping)
			वापस -EINVAL;

		वापस mapping.map_to;

	हाल CMN2ASIC_MAPPING_TABLE:
		अगर (index >= SMU_TABLE_COUNT ||
		    !smu->table_map)
			वापस -EINVAL;

		mapping = smu->table_map[index];
		अगर (!mapping.valid_mapping)
			वापस -EINVAL;

		वापस mapping.map_to;

	हाल CMN2ASIC_MAPPING_PWR:
		अगर (index >= SMU_POWER_SOURCE_COUNT ||
		    !smu->pwr_src_map)
			वापस -EINVAL;

		mapping = smu->pwr_src_map[index];
		अगर (!mapping.valid_mapping)
			वापस -EINVAL;

		वापस mapping.map_to;

	हाल CMN2ASIC_MAPPING_WORKLOAD:
		अगर (index > PP_SMC_POWER_PROखाता_CUSTOM ||
		    !smu->workload_map)
			वापस -EINVAL;

		mapping = smu->workload_map[index];
		अगर (!mapping.valid_mapping)
			वापस -EINVAL;

		वापस mapping.map_to;

	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

पूर्णांक smu_cmn_feature_is_supported(काष्ठा smu_context *smu,
				 क्रमागत smu_feature_mask mask)
अणु
	काष्ठा smu_feature *feature = &smu->smu_feature;
	पूर्णांक feature_id;
	पूर्णांक ret = 0;

	feature_id = smu_cmn_to_asic_specअगरic_index(smu,
						    CMN2ASIC_MAPPING_FEATURE,
						    mask);
	अगर (feature_id < 0)
		वापस 0;

	WARN_ON(feature_id > feature->feature_num);

	mutex_lock(&feature->mutex);
	ret = test_bit(feature_id, feature->supported);
	mutex_unlock(&feature->mutex);

	वापस ret;
पूर्ण

पूर्णांक smu_cmn_feature_is_enabled(काष्ठा smu_context *smu,
			       क्रमागत smu_feature_mask mask)
अणु
	काष्ठा smu_feature *feature = &smu->smu_feature;
	काष्ठा amdgpu_device *adev = smu->adev;
	पूर्णांक feature_id;
	पूर्णांक ret = 0;

	अगर (smu->is_apu && adev->family < AMDGPU_FAMILY_VGH)
		वापस 1;

	feature_id = smu_cmn_to_asic_specअगरic_index(smu,
						    CMN2ASIC_MAPPING_FEATURE,
						    mask);
	अगर (feature_id < 0)
		वापस 0;

	WARN_ON(feature_id > feature->feature_num);

	mutex_lock(&feature->mutex);
	ret = test_bit(feature_id, feature->enabled);
	mutex_unlock(&feature->mutex);

	वापस ret;
पूर्ण

bool smu_cmn_clk_dpm_is_enabled(काष्ठा smu_context *smu,
				क्रमागत smu_clk_type clk_type)
अणु
	क्रमागत smu_feature_mask feature_id = 0;

	चयन (clk_type) अणु
	हाल SMU_MCLK:
	हाल SMU_UCLK:
		feature_id = SMU_FEATURE_DPM_UCLK_BIT;
		अवरोध;
	हाल SMU_GFXCLK:
	हाल SMU_SCLK:
		feature_id = SMU_FEATURE_DPM_GFXCLK_BIT;
		अवरोध;
	हाल SMU_SOCCLK:
		feature_id = SMU_FEATURE_DPM_SOCCLK_BIT;
		अवरोध;
	शेष:
		वापस true;
	पूर्ण

	अगर (!smu_cmn_feature_is_enabled(smu, feature_id))
		वापस false;

	वापस true;
पूर्ण

पूर्णांक smu_cmn_get_enabled_mask(काष्ठा smu_context *smu,
			     uपूर्णांक32_t *feature_mask,
			     uपूर्णांक32_t num)
अणु
	uपूर्णांक32_t feature_mask_high = 0, feature_mask_low = 0;
	काष्ठा smu_feature *feature = &smu->smu_feature;
	पूर्णांक ret = 0;

	अगर (!feature_mask || num < 2)
		वापस -EINVAL;

	अगर (biपंचांगap_empty(feature->enabled, feature->feature_num)) अणु
		ret = smu_cmn_send_smc_msg(smu, SMU_MSG_GetEnabledSmuFeaturesHigh, &feature_mask_high);
		अगर (ret)
			वापस ret;

		ret = smu_cmn_send_smc_msg(smu, SMU_MSG_GetEnabledSmuFeaturesLow, &feature_mask_low);
		अगर (ret)
			वापस ret;

		feature_mask[0] = feature_mask_low;
		feature_mask[1] = feature_mask_high;
	पूर्ण अन्यथा अणु
		biपंचांगap_copy((अचिन्हित दीर्घ *)feature_mask, feature->enabled,
			     feature->feature_num);
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक smu_cmn_get_enabled_32_bits_mask(काष्ठा smu_context *smu,
					uपूर्णांक32_t *feature_mask,
					uपूर्णांक32_t num)
अणु
	uपूर्णांक32_t feature_mask_en_low = 0;
	uपूर्णांक32_t feature_mask_en_high = 0;
	काष्ठा smu_feature *feature = &smu->smu_feature;
	पूर्णांक ret = 0;

	अगर (!feature_mask || num < 2)
		वापस -EINVAL;

	अगर (biपंचांगap_empty(feature->enabled, feature->feature_num)) अणु
		ret = smu_cmn_send_smc_msg_with_param(smu, SMU_MSG_GetEnabledSmuFeatures, 0,
										 &feature_mask_en_low);

		अगर (ret)
			वापस ret;

		ret = smu_cmn_send_smc_msg_with_param(smu, SMU_MSG_GetEnabledSmuFeatures, 1,
										 &feature_mask_en_high);

		अगर (ret)
			वापस ret;

		feature_mask[0] = feature_mask_en_low;
		feature_mask[1] = feature_mask_en_high;

	पूर्ण अन्यथा अणु
		biपंचांगap_copy((अचिन्हित दीर्घ *)feature_mask, feature->enabled,
				 feature->feature_num);
	पूर्ण

	वापस ret;

पूर्ण

पूर्णांक smu_cmn_feature_update_enable_state(काष्ठा smu_context *smu,
					uपूर्णांक64_t feature_mask,
					bool enabled)
अणु
	काष्ठा smu_feature *feature = &smu->smu_feature;
	पूर्णांक ret = 0;

	अगर (enabled) अणु
		ret = smu_cmn_send_smc_msg_with_param(smu,
						  SMU_MSG_EnableSmuFeaturesLow,
						  lower_32_bits(feature_mask),
						  शून्य);
		अगर (ret)
			वापस ret;
		ret = smu_cmn_send_smc_msg_with_param(smu,
						  SMU_MSG_EnableSmuFeaturesHigh,
						  upper_32_bits(feature_mask),
						  शून्य);
		अगर (ret)
			वापस ret;
	पूर्ण अन्यथा अणु
		ret = smu_cmn_send_smc_msg_with_param(smu,
						  SMU_MSG_DisableSmuFeaturesLow,
						  lower_32_bits(feature_mask),
						  शून्य);
		अगर (ret)
			वापस ret;
		ret = smu_cmn_send_smc_msg_with_param(smu,
						  SMU_MSG_DisableSmuFeaturesHigh,
						  upper_32_bits(feature_mask),
						  शून्य);
		अगर (ret)
			वापस ret;
	पूर्ण

	mutex_lock(&feature->mutex);
	अगर (enabled)
		biपंचांगap_or(feature->enabled, feature->enabled,
				(अचिन्हित दीर्घ *)(&feature_mask), SMU_FEATURE_MAX);
	अन्यथा
		biपंचांगap_andnot(feature->enabled, feature->enabled,
				(अचिन्हित दीर्घ *)(&feature_mask), SMU_FEATURE_MAX);
	mutex_unlock(&feature->mutex);

	वापस ret;
पूर्ण

पूर्णांक smu_cmn_feature_set_enabled(काष्ठा smu_context *smu,
				क्रमागत smu_feature_mask mask,
				bool enable)
अणु
	काष्ठा smu_feature *feature = &smu->smu_feature;
	पूर्णांक feature_id;

	feature_id = smu_cmn_to_asic_specअगरic_index(smu,
						    CMN2ASIC_MAPPING_FEATURE,
						    mask);
	अगर (feature_id < 0)
		वापस -EINVAL;

	WARN_ON(feature_id > feature->feature_num);

	वापस smu_cmn_feature_update_enable_state(smu,
					       1ULL << feature_id,
					       enable);
पूर्ण

#अघोषित __SMU_DUMMY_MAP
#घोषणा __SMU_DUMMY_MAP(fea)	#fea
अटल स्थिर अक्षर* __smu_feature_names[] = अणु
	SMU_FEATURE_MASKS
पूर्ण;

अटल स्थिर अक्षर *smu_get_feature_name(काष्ठा smu_context *smu,
					क्रमागत smu_feature_mask feature)
अणु
	अगर (feature < 0 || feature >= SMU_FEATURE_COUNT)
		वापस "unknown smu feature";
	वापस __smu_feature_names[feature];
पूर्ण

माप_प्रकार smu_cmn_get_pp_feature_mask(काष्ठा smu_context *smu,
				   अक्षर *buf)
अणु
	uपूर्णांक32_t feature_mask[2] = अणु 0 पूर्ण;
	पूर्णांक feature_index = 0;
	uपूर्णांक32_t count = 0;
	पूर्णांक8_t sort_feature[SMU_FEATURE_COUNT];
	माप_प्रकार size = 0;
	पूर्णांक ret = 0, i;

	अगर (!smu->is_apu) अणु
		ret = smu_cmn_get_enabled_mask(smu,
						feature_mask,
						2);
		अगर (ret)
			वापस 0;
	पूर्ण अन्यथा अणु
		ret = smu_cmn_get_enabled_32_bits_mask(smu,
					feature_mask,
					2);
		अगर (ret)
			वापस 0;
	पूर्ण

	size =  प्र_लिखो(buf + size, "features high: 0x%08x low: 0x%08x\n",
			feature_mask[1], feature_mask[0]);

	स_रखो(sort_feature, -1, माप(sort_feature));

	क्रम (i = 0; i < SMU_FEATURE_COUNT; i++) अणु
		feature_index = smu_cmn_to_asic_specअगरic_index(smu,
							       CMN2ASIC_MAPPING_FEATURE,
							       i);
		अगर (feature_index < 0)
			जारी;

		sort_feature[feature_index] = i;
	पूर्ण

	size += प्र_लिखो(buf + size, "%-2s. %-20s  %-3s : %-s\n",
			"No", "Feature", "Bit", "State");

	क्रम (i = 0; i < SMU_FEATURE_COUNT; i++) अणु
		अगर (sort_feature[i] < 0)
			जारी;

		size += प्र_लिखो(buf + size, "%02d. %-20s (%2d) : %s\n",
				count++,
				smu_get_feature_name(smu, sort_feature[i]),
				i,
				!!smu_cmn_feature_is_enabled(smu, sort_feature[i]) ?
				"enabled" : "disabled");
	पूर्ण

	वापस size;
पूर्ण

पूर्णांक smu_cmn_set_pp_feature_mask(काष्ठा smu_context *smu,
				uपूर्णांक64_t new_mask)
अणु
	पूर्णांक ret = 0;
	uपूर्णांक32_t feature_mask[2] = अणु 0 पूर्ण;
	uपूर्णांक64_t feature_2_enabled = 0;
	uपूर्णांक64_t feature_2_disabled = 0;
	uपूर्णांक64_t feature_enables = 0;

	ret = smu_cmn_get_enabled_mask(smu,
				       feature_mask,
				       2);
	अगर (ret)
		वापस ret;

	feature_enables = ((uपूर्णांक64_t)feature_mask[1] << 32 |
			   (uपूर्णांक64_t)feature_mask[0]);

	feature_2_enabled  = ~feature_enables & new_mask;
	feature_2_disabled = feature_enables & ~new_mask;

	अगर (feature_2_enabled) अणु
		ret = smu_cmn_feature_update_enable_state(smu,
							  feature_2_enabled,
							  true);
		अगर (ret)
			वापस ret;
	पूर्ण
	अगर (feature_2_disabled) अणु
		ret = smu_cmn_feature_update_enable_state(smu,
							  feature_2_disabled,
							  false);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक smu_cmn_disable_all_features_with_exception(काष्ठा smu_context *smu,
						क्रमागत smu_feature_mask mask)
अणु
	uपूर्णांक64_t features_to_disable = U64_MAX;
	पूर्णांक skipped_feature_id;

	skipped_feature_id = smu_cmn_to_asic_specअगरic_index(smu,
							    CMN2ASIC_MAPPING_FEATURE,
							    mask);
	अगर (skipped_feature_id < 0)
		वापस -EINVAL;

	features_to_disable &= ~(1ULL << skipped_feature_id);

	वापस smu_cmn_feature_update_enable_state(smu,
						   features_to_disable,
						   0);
पूर्ण

पूर्णांक smu_cmn_get_smc_version(काष्ठा smu_context *smu,
			    uपूर्णांक32_t *अगर_version,
			    uपूर्णांक32_t *smu_version)
अणु
	पूर्णांक ret = 0;

	अगर (!अगर_version && !smu_version)
		वापस -EINVAL;

	अगर (smu->smc_fw_अगर_version && smu->smc_fw_version)
	अणु
		अगर (अगर_version)
			*अगर_version = smu->smc_fw_अगर_version;

		अगर (smu_version)
			*smu_version = smu->smc_fw_version;

		वापस 0;
	पूर्ण

	अगर (अगर_version) अणु
		ret = smu_cmn_send_smc_msg(smu, SMU_MSG_GetDriverIfVersion, अगर_version);
		अगर (ret)
			वापस ret;

		smu->smc_fw_अगर_version = *अगर_version;
	पूर्ण

	अगर (smu_version) अणु
		ret = smu_cmn_send_smc_msg(smu, SMU_MSG_GetSmuVersion, smu_version);
		अगर (ret)
			वापस ret;

		smu->smc_fw_version = *smu_version;
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक smu_cmn_update_table(काष्ठा smu_context *smu,
			 क्रमागत smu_table_id table_index,
			 पूर्णांक argument,
			 व्योम *table_data,
			 bool drv2smu)
अणु
	काष्ठा smu_table_context *smu_table = &smu->smu_table;
	काष्ठा amdgpu_device *adev = smu->adev;
	काष्ठा smu_table *table = &smu_table->driver_table;
	पूर्णांक table_id = smu_cmn_to_asic_specअगरic_index(smu,
						      CMN2ASIC_MAPPING_TABLE,
						      table_index);
	uपूर्णांक32_t table_size;
	पूर्णांक ret = 0;
	अगर (!table_data || table_id >= SMU_TABLE_COUNT || table_id < 0)
		वापस -EINVAL;

	table_size = smu_table->tables[table_index].size;

	अगर (drv2smu) अणु
		स_नकल(table->cpu_addr, table_data, table_size);
		/*
		 * Flush hdp cache: to guard the content seen by
		 * GPU is consitent with CPU.
		 */
		amdgpu_asic_flush_hdp(adev, शून्य);
	पूर्ण

	ret = smu_cmn_send_smc_msg_with_param(smu, drv2smu ?
					  SMU_MSG_TransferTableDram2Smu :
					  SMU_MSG_TransferTableSmu2Dram,
					  table_id | ((argument & 0xFFFF) << 16),
					  शून्य);
	अगर (ret)
		वापस ret;

	अगर (!drv2smu) अणु
		amdgpu_asic_invalidate_hdp(adev, शून्य);
		स_नकल(table_data, table->cpu_addr, table_size);
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक smu_cmn_ग_लिखो_watermarks_table(काष्ठा smu_context *smu)
अणु
	व्योम *watermarks_table = smu->smu_table.watermarks_table;

	अगर (!watermarks_table)
		वापस -EINVAL;

	वापस smu_cmn_update_table(smu,
				    SMU_TABLE_WATERMARKS,
				    0,
				    watermarks_table,
				    true);
पूर्ण

पूर्णांक smu_cmn_ग_लिखो_pptable(काष्ठा smu_context *smu)
अणु
	व्योम *pptable = smu->smu_table.driver_pptable;

	वापस smu_cmn_update_table(smu,
				    SMU_TABLE_PPTABLE,
				    0,
				    pptable,
				    true);
पूर्ण

पूर्णांक smu_cmn_get_metrics_table_locked(काष्ठा smu_context *smu,
				     व्योम *metrics_table,
				     bool bypass_cache)
अणु
	काष्ठा smu_table_context *smu_table= &smu->smu_table;
	uपूर्णांक32_t table_size =
		smu_table->tables[SMU_TABLE_SMU_METRICS].size;
	पूर्णांक ret = 0;

	अगर (bypass_cache ||
	    !smu_table->metrics_समय ||
	    समय_after(jअगरfies, smu_table->metrics_समय + msecs_to_jअगरfies(1))) अणु
		ret = smu_cmn_update_table(smu,
				       SMU_TABLE_SMU_METRICS,
				       0,
				       smu_table->metrics_table,
				       false);
		अगर (ret) अणु
			dev_info(smu->adev->dev, "Failed to export SMU metrics table!\n");
			वापस ret;
		पूर्ण
		smu_table->metrics_समय = jअगरfies;
	पूर्ण

	अगर (metrics_table)
		स_नकल(metrics_table, smu_table->metrics_table, table_size);

	वापस 0;
पूर्ण

पूर्णांक smu_cmn_get_metrics_table(काष्ठा smu_context *smu,
			      व्योम *metrics_table,
			      bool bypass_cache)
अणु
	पूर्णांक ret = 0;

	mutex_lock(&smu->metrics_lock);
	ret = smu_cmn_get_metrics_table_locked(smu,
					       metrics_table,
					       bypass_cache);
	mutex_unlock(&smu->metrics_lock);

	वापस ret;
पूर्ण

व्योम smu_cmn_init_soft_gpu_metrics(व्योम *table, uपूर्णांक8_t frev, uपूर्णांक8_t crev)
अणु
	काष्ठा metrics_table_header *header = (काष्ठा metrics_table_header *)table;
	uपूर्णांक16_t काष्ठाure_size;

#घोषणा METRICS_VERSION(a, b)	((a << 16) | b )

	चयन (METRICS_VERSION(frev, crev)) अणु
	हाल METRICS_VERSION(1, 0):
		काष्ठाure_size = माप(काष्ठा gpu_metrics_v1_0);
		अवरोध;
	हाल METRICS_VERSION(1, 1):
		काष्ठाure_size = माप(काष्ठा gpu_metrics_v1_1);
		अवरोध;
	हाल METRICS_VERSION(2, 0):
		काष्ठाure_size = माप(काष्ठा gpu_metrics_v2_0);
		अवरोध;
	हाल METRICS_VERSION(2, 1):
		काष्ठाure_size = माप(काष्ठा gpu_metrics_v2_1);
		अवरोध;
	शेष:
		वापस;
	पूर्ण

#अघोषित METRICS_VERSION

	स_रखो(header, 0xFF, काष्ठाure_size);

	header->क्रमmat_revision = frev;
	header->content_revision = crev;
	header->काष्ठाure_size = काष्ठाure_size;

पूर्ण

पूर्णांक smu_cmn_set_mp1_state(काष्ठा smu_context *smu,
			  क्रमागत pp_mp1_state mp1_state)
अणु
	क्रमागत smu_message_type msg;
	पूर्णांक ret;

	चयन (mp1_state) अणु
	हाल PP_MP1_STATE_SHUTDOWN:
		msg = SMU_MSG_PrepareMp1ForShutकरोwn;
		अवरोध;
	हाल PP_MP1_STATE_UNLOAD:
		msg = SMU_MSG_PrepareMp1ForUnload;
		अवरोध;
	हाल PP_MP1_STATE_RESET:
		msg = SMU_MSG_PrepareMp1ForReset;
		अवरोध;
	हाल PP_MP1_STATE_NONE:
	शेष:
		वापस 0;
	पूर्ण

	ret = smu_cmn_send_smc_msg(smu, msg, शून्य);
	अगर (ret)
		dev_err(smu->adev->dev, "[PrepareMp1] Failed!\n");

	वापस ret;
पूर्ण
