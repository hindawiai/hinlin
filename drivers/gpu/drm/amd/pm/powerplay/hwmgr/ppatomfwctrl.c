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
 */

#समावेश "ppatomfwctrl.h"
#समावेश "atomfirmware.h"
#समावेश "atom.h"
#समावेश "pp_debug.h"

अटल स्थिर जोड़ atom_voltage_object_v4 *pp_atomfwctrl_lookup_voltage_type_v4(
		स्थिर काष्ठा atom_voltage_objects_info_v4_1 *voltage_object_info_table,
		uपूर्णांक8_t voltage_type, uपूर्णांक8_t voltage_mode)
अणु
	अचिन्हित पूर्णांक size = le16_to_cpu(
			voltage_object_info_table->table_header.काष्ठाuresize);
	अचिन्हित पूर्णांक offset =
			दुरत्व(काष्ठा atom_voltage_objects_info_v4_1, voltage_object[0]);
	अचिन्हित दीर्घ start = (अचिन्हित दीर्घ)voltage_object_info_table;

	जबतक (offset < size) अणु
		स्थिर जोड़ atom_voltage_object_v4 *voltage_object =
			(स्थिर जोड़ atom_voltage_object_v4 *)(start + offset);

		अगर (voltage_type == voltage_object->gpio_voltage_obj.header.voltage_type &&
		    voltage_mode == voltage_object->gpio_voltage_obj.header.voltage_mode)
			वापस voltage_object;

		offset += le16_to_cpu(voltage_object->gpio_voltage_obj.header.object_size);

	पूर्ण

	वापस शून्य;
पूर्ण

अटल काष्ठा atom_voltage_objects_info_v4_1 *pp_atomfwctrl_get_voltage_info_table(
		काष्ठा pp_hwmgr *hwmgr)
अणु
	स्थिर व्योम *table_address;
	uपूर्णांक16_t idx;

	idx = GetIndexIntoMasterDataTable(voltageobject_info);
	table_address = smu_atom_get_data_table(hwmgr->adev,
						idx, शून्य, शून्य, शून्य);

	PP_ASSERT_WITH_CODE(table_address,
			"Error retrieving BIOS Table Address!",
			वापस शून्य);

	वापस (काष्ठा atom_voltage_objects_info_v4_1 *)table_address;
पूर्ण

/*
 * Returns TRUE अगर the given voltage type is controlled by GPIO pins.
 * voltage_type is one of SET_VOLTAGE_TYPE_ASIC_VDDC, SET_VOLTAGE_TYPE_ASIC_MVDDC, SET_VOLTAGE_TYPE_ASIC_MVDDQ.
 * voltage_mode is one of ATOM_SET_VOLTAGE, ATOM_SET_VOLTAGE_PHASE
 */
bool pp_atomfwctrl_is_voltage_controlled_by_gpio_v4(काष्ठा pp_hwmgr *hwmgr,
		uपूर्णांक8_t voltage_type, uपूर्णांक8_t voltage_mode)
अणु
	काष्ठा atom_voltage_objects_info_v4_1 *voltage_info =
			(काष्ठा atom_voltage_objects_info_v4_1 *)
			pp_atomfwctrl_get_voltage_info_table(hwmgr);
	bool ret;

	/* If we cannot find the table करो NOT try to control this voltage. */
	PP_ASSERT_WITH_CODE(voltage_info,
			"Could not find Voltage Table in BIOS.",
			वापस false);

	ret = (pp_atomfwctrl_lookup_voltage_type_v4(voltage_info,
			voltage_type, voltage_mode)) ? true : false;

	वापस ret;
पूर्ण

पूर्णांक pp_atomfwctrl_get_voltage_table_v4(काष्ठा pp_hwmgr *hwmgr,
		uपूर्णांक8_t voltage_type, uपूर्णांक8_t voltage_mode,
		काष्ठा pp_atomfwctrl_voltage_table *voltage_table)
अणु
	काष्ठा atom_voltage_objects_info_v4_1 *voltage_info =
			(काष्ठा atom_voltage_objects_info_v4_1 *)
			pp_atomfwctrl_get_voltage_info_table(hwmgr);
	स्थिर जोड़ atom_voltage_object_v4 *voltage_object;
	अचिन्हित पूर्णांक i;
	पूर्णांक result = 0;

	PP_ASSERT_WITH_CODE(voltage_info,
			"Could not find Voltage Table in BIOS.",
			वापस -1);

	voltage_object = pp_atomfwctrl_lookup_voltage_type_v4(voltage_info,
			voltage_type, voltage_mode);

	अगर (!voltage_object)
		वापस -1;

	voltage_table->count = 0;
	अगर (voltage_mode == VOLTAGE_OBJ_GPIO_LUT) अणु
		PP_ASSERT_WITH_CODE(
				(voltage_object->gpio_voltage_obj.gpio_entry_num <=
				PP_ATOMFWCTRL_MAX_VOLTAGE_ENTRIES),
				"Too many voltage entries!",
				result = -1);

		अगर (!result) अणु
			क्रम (i = 0; i < voltage_object->gpio_voltage_obj.
							gpio_entry_num; i++) अणु
				voltage_table->entries[i].value =
						le16_to_cpu(voltage_object->gpio_voltage_obj.
						voltage_gpio_lut[i].voltage_level_mv);
				voltage_table->entries[i].smio_low =
						le32_to_cpu(voltage_object->gpio_voltage_obj.
						voltage_gpio_lut[i].voltage_gpio_reg_val);
			पूर्ण
			voltage_table->count =
					voltage_object->gpio_voltage_obj.gpio_entry_num;
			voltage_table->mask_low =
					le32_to_cpu(
					voltage_object->gpio_voltage_obj.gpio_mask_val);
			voltage_table->phase_delay =
					voltage_object->gpio_voltage_obj.phase_delay_us;
		पूर्ण
	पूर्ण अन्यथा अगर (voltage_mode == VOLTAGE_OBJ_SVID2) अणु
		voltage_table->psi1_enable =
			(voltage_object->svid2_voltage_obj.loadline_psi1 & 0x20) >> 5;
		voltage_table->psi0_enable =
			voltage_object->svid2_voltage_obj.psi0_enable & 0x1;
		voltage_table->max_vid_step =
			voltage_object->svid2_voltage_obj.maxvstep;
		voltage_table->telemetry_offset =
			voltage_object->svid2_voltage_obj.telemetry_offset;
		voltage_table->telemetry_slope =
			voltage_object->svid2_voltage_obj.telemetry_gain;
	पूर्ण अन्यथा
		PP_ASSERT_WITH_CODE(false,
				"Unsupported Voltage Object Mode!",
				result = -1);

	वापस result;
पूर्ण

 
अटल काष्ठा atom_gpio_pin_lut_v2_1 *pp_atomfwctrl_get_gpio_lookup_table(
		काष्ठा pp_hwmgr *hwmgr)
अणु
	स्थिर व्योम *table_address;
	uपूर्णांक16_t idx;

	idx = GetIndexIntoMasterDataTable(gpio_pin_lut);
	table_address =	smu_atom_get_data_table(hwmgr->adev,
			idx, शून्य, शून्य, शून्य);
	PP_ASSERT_WITH_CODE(table_address,
			"Error retrieving BIOS Table Address!",
			वापस शून्य);

	वापस (काष्ठा atom_gpio_pin_lut_v2_1 *)table_address;
पूर्ण

अटल bool pp_atomfwctrl_lookup_gpio_pin(
		काष्ठा atom_gpio_pin_lut_v2_1 *gpio_lookup_table,
		स्थिर uपूर्णांक32_t pin_id,
		काष्ठा pp_atomfwctrl_gpio_pin_assignment *gpio_pin_assignment)
अणु
	अचिन्हित पूर्णांक size = le16_to_cpu(
			gpio_lookup_table->table_header.काष्ठाuresize);
	अचिन्हित पूर्णांक offset =
			दुरत्व(काष्ठा atom_gpio_pin_lut_v2_1, gpio_pin[0]);
	अचिन्हित दीर्घ start = (अचिन्हित दीर्घ)gpio_lookup_table;

	जबतक (offset < size) अणु
		स्थिर काष्ठा  atom_gpio_pin_assignment *pin_assignment =
				(स्थिर काष्ठा  atom_gpio_pin_assignment *)(start + offset);

		अगर (pin_id == pin_assignment->gpio_id)  अणु
			gpio_pin_assignment->uc_gpio_pin_bit_shअगरt =
					pin_assignment->gpio_bitshअगरt;
			gpio_pin_assignment->us_gpio_pin_aindex =
					le16_to_cpu(pin_assignment->data_a_reg_index);
			वापस true;
		पूर्ण
		offset += दुरत्व(काष्ठा atom_gpio_pin_assignment, gpio_id) + 1;
	पूर्ण
	वापस false;
पूर्ण

/*
 * Returns TRUE अगर the given pin id find in lookup table.
 */
bool pp_atomfwctrl_get_pp_assign_pin(काष्ठा pp_hwmgr *hwmgr,
		स्थिर uपूर्णांक32_t pin_id,
		काष्ठा pp_atomfwctrl_gpio_pin_assignment *gpio_pin_assignment)
अणु
	bool ret = false;
	काष्ठा atom_gpio_pin_lut_v2_1 *gpio_lookup_table =
			pp_atomfwctrl_get_gpio_lookup_table(hwmgr);

	/* If we cannot find the table करो NOT try to control this voltage. */
	PP_ASSERT_WITH_CODE(gpio_lookup_table,
			"Could not find GPIO lookup Table in BIOS.",
			वापस false);

	ret = pp_atomfwctrl_lookup_gpio_pin(gpio_lookup_table,
			pin_id, gpio_pin_assignment);

	वापस ret;
पूर्ण

/*
 * Enter to SelfRefresh mode.
 * @param hwmgr
 */
पूर्णांक pp_atomfwctrl_enter_self_refresh(काष्ठा pp_hwmgr *hwmgr)
अणु
	/* 0 - no action
	 * 1 - leave घातer to video memory always on
	 */
	वापस 0;
पूर्ण

/** pp_atomfwctrl_get_gpu_pll_भागiders_vega10().
 *
 * @param hwmgr       input parameter: poपूर्णांकer to HwMgr
 * @param घड़ी_प्रकारype  input parameter: Clock type: 1 - GFXCLK, 2 - UCLK, 0 - All other घड़ीs
 * @param घड़ी_value input parameter: Clock
 * @param भागiders    output parameter:Clock भागiders
 */
पूर्णांक pp_atomfwctrl_get_gpu_pll_भागiders_vega10(काष्ठा pp_hwmgr *hwmgr,
		uपूर्णांक32_t घड़ी_प्रकारype, uपूर्णांक32_t घड़ी_value,
		काष्ठा pp_atomfwctrl_घड़ी_भागiders_soc15 *भागiders)
अणु
	काष्ठा amdgpu_device *adev = hwmgr->adev;
	काष्ठा compute_gpu_घड़ी_input_parameter_v1_8 pll_parameters;
	काष्ठा compute_gpu_घड़ी_output_parameter_v1_8 *pll_output;
	uपूर्णांक32_t idx;

	pll_parameters.gpuघड़ी_10khz = (uपूर्णांक32_t)घड़ी_value;
	pll_parameters.gpu_घड़ी_प्रकारype = घड़ी_प्रकारype;

	idx = GetIndexIntoMasterCmdTable(computegpuघड़ीparam);

	अगर (amdgpu_atom_execute_table(
		adev->mode_info.atom_context, idx, (uपूर्णांक32_t *)&pll_parameters))
		वापस -EINVAL;

	pll_output = (काष्ठा compute_gpu_घड़ी_output_parameter_v1_8 *)
			&pll_parameters;
	भागiders->ulClock = le32_to_cpu(pll_output->gpuघड़ी_10khz);
	भागiders->ulDid = le32_to_cpu(pll_output->dfs_did);
	भागiders->ulPll_fb_mult = le32_to_cpu(pll_output->pll_fb_mult);
	भागiders->ulPll_ss_fbsmult = le32_to_cpu(pll_output->pll_ss_fbsmult);
	भागiders->usPll_ss_slew_frac = le16_to_cpu(pll_output->pll_ss_slew_frac);
	भागiders->ucPll_ss_enable = pll_output->pll_ss_enable;

	वापस 0;
पूर्ण

पूर्णांक pp_atomfwctrl_get_avfs_inक्रमmation(काष्ठा pp_hwmgr *hwmgr,
		काष्ठा pp_atomfwctrl_avfs_parameters *param)
अणु
	uपूर्णांक16_t idx;
	uपूर्णांक8_t क्रमmat_revision, content_revision;

	काष्ठा atom_asic_profiling_info_v4_1 *profile;
	काष्ठा atom_asic_profiling_info_v4_2 *profile_v4_2;

	idx = GetIndexIntoMasterDataTable(asic_profiling_info);
	profile = (काष्ठा atom_asic_profiling_info_v4_1 *)
			smu_atom_get_data_table(hwmgr->adev,
					idx, शून्य, शून्य, शून्य);

	अगर (!profile)
		वापस -1;

	क्रमmat_revision = ((काष्ठा atom_common_table_header *)profile)->क्रमmat_revision;
	content_revision = ((काष्ठा atom_common_table_header *)profile)->content_revision;

	अगर (क्रमmat_revision == 4 && content_revision == 1) अणु
		param->ulMaxVddc = le32_to_cpu(profile->maxvddc);
		param->ulMinVddc = le32_to_cpu(profile->minvddc);
		param->ulMeanNsigmaAcontant0 =
				le32_to_cpu(profile->avfs_meannsigma_acontant0);
		param->ulMeanNsigmaAcontant1 =
				le32_to_cpu(profile->avfs_meannsigma_acontant1);
		param->ulMeanNsigmaAcontant2 =
				le32_to_cpu(profile->avfs_meannsigma_acontant2);
		param->usMeanNsigmaDcTolSigma =
				le16_to_cpu(profile->avfs_meannsigma_dc_tol_sigma);
		param->usMeanNsigmaPlatक्रमmMean =
				le16_to_cpu(profile->avfs_meannsigma_platक्रमm_mean);
		param->usMeanNsigmaPlatक्रमmSigma =
				le16_to_cpu(profile->avfs_meannsigma_platक्रमm_sigma);
		param->ulGbVdroopTableCksoffA0 =
				le32_to_cpu(profile->gb_vdroop_table_cksoff_a0);
		param->ulGbVdroopTableCksoffA1 =
				le32_to_cpu(profile->gb_vdroop_table_cksoff_a1);
		param->ulGbVdroopTableCksoffA2 =
				le32_to_cpu(profile->gb_vdroop_table_cksoff_a2);
		param->ulGbVdroopTableCksonA0 =
				le32_to_cpu(profile->gb_vdroop_table_ckson_a0);
		param->ulGbVdroopTableCksonA1 =
				le32_to_cpu(profile->gb_vdroop_table_ckson_a1);
		param->ulGbVdroopTableCksonA2 =
				le32_to_cpu(profile->gb_vdroop_table_ckson_a2);
		param->ulGbFuseTableCksoffM1 =
				le32_to_cpu(profile->avfsgb_fuse_table_cksoff_m1);
		param->ulGbFuseTableCksoffM2 =
				le32_to_cpu(profile->avfsgb_fuse_table_cksoff_m2);
		param->ulGbFuseTableCksoffB =
				le32_to_cpu(profile->avfsgb_fuse_table_cksoff_b);
		param->ulGbFuseTableCksonM1 =
				le32_to_cpu(profile->avfsgb_fuse_table_ckson_m1);
		param->ulGbFuseTableCksonM2 =
				le32_to_cpu(profile->avfsgb_fuse_table_ckson_m2);
		param->ulGbFuseTableCksonB =
				le32_to_cpu(profile->avfsgb_fuse_table_ckson_b);

		param->ucEnableGbVdroopTableCkson =
				profile->enable_gb_vdroop_table_ckson;
		param->ucEnableGbFuseTableCkson =
				profile->enable_gb_fuse_table_ckson;
		param->usPsmAgeComfactor =
				le16_to_cpu(profile->psm_age_comfactor);

		param->ulDispclk2GfxclkM1 =
				le32_to_cpu(profile->dispclk2gfxclk_a);
		param->ulDispclk2GfxclkM2 =
				le32_to_cpu(profile->dispclk2gfxclk_b);
		param->ulDispclk2GfxclkB =
				le32_to_cpu(profile->dispclk2gfxclk_c);
		param->ulDcefclk2GfxclkM1 =
				le32_to_cpu(profile->dcefclk2gfxclk_a);
		param->ulDcefclk2GfxclkM2 =
				le32_to_cpu(profile->dcefclk2gfxclk_b);
		param->ulDcefclk2GfxclkB =
				le32_to_cpu(profile->dcefclk2gfxclk_c);
		param->ulPixelclk2GfxclkM1 =
				le32_to_cpu(profile->pixclk2gfxclk_a);
		param->ulPixelclk2GfxclkM2 =
				le32_to_cpu(profile->pixclk2gfxclk_b);
		param->ulPixelclk2GfxclkB =
				le32_to_cpu(profile->pixclk2gfxclk_c);
		param->ulPhyclk2GfxclkM1 =
				le32_to_cpu(profile->phyclk2gfxclk_a);
		param->ulPhyclk2GfxclkM2 =
				le32_to_cpu(profile->phyclk2gfxclk_b);
		param->ulPhyclk2GfxclkB =
				le32_to_cpu(profile->phyclk2gfxclk_c);
		param->ulAcgGbVdroopTableA0           = 0;
		param->ulAcgGbVdroopTableA1           = 0;
		param->ulAcgGbVdroopTableA2           = 0;
		param->ulAcgGbFuseTableM1             = 0;
		param->ulAcgGbFuseTableM2             = 0;
		param->ulAcgGbFuseTableB              = 0;
		param->ucAcgEnableGbVdroopTable       = 0;
		param->ucAcgEnableGbFuseTable         = 0;
	पूर्ण अन्यथा अगर (क्रमmat_revision == 4 && content_revision == 2) अणु
		profile_v4_2 = (काष्ठा atom_asic_profiling_info_v4_2 *)profile;
		param->ulMaxVddc = le32_to_cpu(profile_v4_2->maxvddc);
		param->ulMinVddc = le32_to_cpu(profile_v4_2->minvddc);
		param->ulMeanNsigmaAcontant0 =
				le32_to_cpu(profile_v4_2->avfs_meannsigma_acontant0);
		param->ulMeanNsigmaAcontant1 =
				le32_to_cpu(profile_v4_2->avfs_meannsigma_acontant1);
		param->ulMeanNsigmaAcontant2 =
				le32_to_cpu(profile_v4_2->avfs_meannsigma_acontant2);
		param->usMeanNsigmaDcTolSigma =
				le16_to_cpu(profile_v4_2->avfs_meannsigma_dc_tol_sigma);
		param->usMeanNsigmaPlatक्रमmMean =
				le16_to_cpu(profile_v4_2->avfs_meannsigma_platक्रमm_mean);
		param->usMeanNsigmaPlatक्रमmSigma =
				le16_to_cpu(profile_v4_2->avfs_meannsigma_platक्रमm_sigma);
		param->ulGbVdroopTableCksoffA0 =
				le32_to_cpu(profile_v4_2->gb_vdroop_table_cksoff_a0);
		param->ulGbVdroopTableCksoffA1 =
				le32_to_cpu(profile_v4_2->gb_vdroop_table_cksoff_a1);
		param->ulGbVdroopTableCksoffA2 =
				le32_to_cpu(profile_v4_2->gb_vdroop_table_cksoff_a2);
		param->ulGbVdroopTableCksonA0 =
				le32_to_cpu(profile_v4_2->gb_vdroop_table_ckson_a0);
		param->ulGbVdroopTableCksonA1 =
				le32_to_cpu(profile_v4_2->gb_vdroop_table_ckson_a1);
		param->ulGbVdroopTableCksonA2 =
				le32_to_cpu(profile_v4_2->gb_vdroop_table_ckson_a2);
		param->ulGbFuseTableCksoffM1 =
				le32_to_cpu(profile_v4_2->avfsgb_fuse_table_cksoff_m1);
		param->ulGbFuseTableCksoffM2 =
				le32_to_cpu(profile_v4_2->avfsgb_fuse_table_cksoff_m2);
		param->ulGbFuseTableCksoffB =
				le32_to_cpu(profile_v4_2->avfsgb_fuse_table_cksoff_b);
		param->ulGbFuseTableCksonM1 =
				le32_to_cpu(profile_v4_2->avfsgb_fuse_table_ckson_m1);
		param->ulGbFuseTableCksonM2 =
				le32_to_cpu(profile_v4_2->avfsgb_fuse_table_ckson_m2);
		param->ulGbFuseTableCksonB =
				le32_to_cpu(profile_v4_2->avfsgb_fuse_table_ckson_b);

		param->ucEnableGbVdroopTableCkson =
				profile_v4_2->enable_gb_vdroop_table_ckson;
		param->ucEnableGbFuseTableCkson =
				profile_v4_2->enable_gb_fuse_table_ckson;
		param->usPsmAgeComfactor =
				le16_to_cpu(profile_v4_2->psm_age_comfactor);

		param->ulDispclk2GfxclkM1 =
				le32_to_cpu(profile_v4_2->dispclk2gfxclk_a);
		param->ulDispclk2GfxclkM2 =
				le32_to_cpu(profile_v4_2->dispclk2gfxclk_b);
		param->ulDispclk2GfxclkB =
				le32_to_cpu(profile_v4_2->dispclk2gfxclk_c);
		param->ulDcefclk2GfxclkM1 =
				le32_to_cpu(profile_v4_2->dcefclk2gfxclk_a);
		param->ulDcefclk2GfxclkM2 =
				le32_to_cpu(profile_v4_2->dcefclk2gfxclk_b);
		param->ulDcefclk2GfxclkB =
				le32_to_cpu(profile_v4_2->dcefclk2gfxclk_c);
		param->ulPixelclk2GfxclkM1 =
				le32_to_cpu(profile_v4_2->pixclk2gfxclk_a);
		param->ulPixelclk2GfxclkM2 =
				le32_to_cpu(profile_v4_2->pixclk2gfxclk_b);
		param->ulPixelclk2GfxclkB =
				le32_to_cpu(profile_v4_2->pixclk2gfxclk_c);
		param->ulPhyclk2GfxclkM1 =
				le32_to_cpu(profile->phyclk2gfxclk_a);
		param->ulPhyclk2GfxclkM2 =
				le32_to_cpu(profile_v4_2->phyclk2gfxclk_b);
		param->ulPhyclk2GfxclkB =
				le32_to_cpu(profile_v4_2->phyclk2gfxclk_c);
		param->ulAcgGbVdroopTableA0 = le32_to_cpu(profile_v4_2->acg_gb_vdroop_table_a0);
		param->ulAcgGbVdroopTableA1 = le32_to_cpu(profile_v4_2->acg_gb_vdroop_table_a1);
		param->ulAcgGbVdroopTableA2 = le32_to_cpu(profile_v4_2->acg_gb_vdroop_table_a2);
		param->ulAcgGbFuseTableM1 = le32_to_cpu(profile_v4_2->acg_avfsgb_fuse_table_m1);
		param->ulAcgGbFuseTableM2 = le32_to_cpu(profile_v4_2->acg_avfsgb_fuse_table_m2);
		param->ulAcgGbFuseTableB = le32_to_cpu(profile_v4_2->acg_avfsgb_fuse_table_b);
		param->ucAcgEnableGbVdroopTable = le32_to_cpu(profile_v4_2->enable_acg_gb_vdroop_table);
		param->ucAcgEnableGbFuseTable = le32_to_cpu(profile_v4_2->enable_acg_gb_fuse_table);
	पूर्ण अन्यथा अणु
		pr_info("Invalid VBIOS AVFS ProfilingInfo Revision!\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक pp_atomfwctrl_get_gpio_inक्रमmation(काष्ठा pp_hwmgr *hwmgr,
		काष्ठा pp_atomfwctrl_gpio_parameters *param)
अणु
	काष्ठा atom_smu_info_v3_1 *info;
	uपूर्णांक16_t idx;

	idx = GetIndexIntoMasterDataTable(smu_info);
	info = (काष्ठा atom_smu_info_v3_1 *)
		smu_atom_get_data_table(hwmgr->adev,
				idx, शून्य, शून्य, शून्य);

	अगर (!info) अणु
		pr_info("Error retrieving BIOS smu_info Table Address!");
		वापस -1;
	पूर्ण

	param->ucAcDcGpio       = info->ac_dc_gpio_bit;
	param->ucAcDcPolarity   = info->ac_dc_polarity;
	param->ucVR0HotGpio     = info->vr0hot_gpio_bit;
	param->ucVR0HotPolarity = info->vr0hot_polarity;
	param->ucVR1HotGpio     = info->vr1hot_gpio_bit;
	param->ucVR1HotPolarity = info->vr1hot_polarity;
	param->ucFwCtfGpio      = info->fw_ctf_gpio_bit;
	param->ucFwCtfPolarity  = info->fw_ctf_polarity;

	वापस 0;
पूर्ण

पूर्णांक pp_atomfwctrl_get_clk_inक्रमmation_by_clkid(काष्ठा pp_hwmgr *hwmgr,
					       uपूर्णांक8_t clk_id, uपूर्णांक8_t syspll_id,
					       uपूर्णांक32_t *frequency)
अणु
	काष्ठा amdgpu_device *adev = hwmgr->adev;
	काष्ठा atom_get_smu_घड़ी_info_parameters_v3_1   parameters;
	काष्ठा atom_get_smu_घड़ी_info_output_parameters_v3_1 *output;
	uपूर्णांक32_t ix;

	parameters.clk_id = clk_id;
	parameters.syspll_id = syspll_id;
	parameters.command = GET_SMU_CLOCK_INFO_V3_1_GET_CLOCK_FREQ;
	parameters.dfsdid = 0;

	ix = GetIndexIntoMasterCmdTable(माला_लोmuघड़ीinfo);

	अगर (amdgpu_atom_execute_table(
		adev->mode_info.atom_context, ix, (uपूर्णांक32_t *)&parameters))
		वापस -EINVAL;

	output = (काष्ठा atom_get_smu_घड़ी_info_output_parameters_v3_1 *)&parameters;
	*frequency = le32_to_cpu(output->atom_smu_outअ_दोlkfreq.smu_घड़ी_freq_hz) / 10000;

	वापस 0;
पूर्ण

अटल व्योम pp_atomfwctrl_copy_vbios_bootup_values_3_2(काष्ठा pp_hwmgr *hwmgr,
			काष्ठा pp_atomfwctrl_bios_boot_up_values *boot_values,
			काष्ठा atom_firmware_info_v3_2 *fw_info)
अणु
	uपूर्णांक32_t frequency = 0;

	boot_values->ulRevision = fw_info->firmware_revision;
	boot_values->ulGfxClk   = fw_info->bootup_sclk_in10khz;
	boot_values->ulUClk     = fw_info->bootup_mclk_in10khz;
	boot_values->usVddc     = fw_info->bootup_vddc_mv;
	boot_values->usVddci    = fw_info->bootup_vddci_mv;
	boot_values->usMvddc    = fw_info->bootup_mvddc_mv;
	boot_values->usVddGfx   = fw_info->bootup_vddgfx_mv;
	boot_values->ucCoolingID = fw_info->coolingsolution_id;
	boot_values->ulSocClk   = 0;
	boot_values->ulDCEFClk   = 0;

	अगर (!pp_atomfwctrl_get_clk_inक्रमmation_by_clkid(hwmgr, SMU11_SYSPLL0_SOCCLK_ID, SMU11_SYSPLL0_ID, &frequency))
		boot_values->ulSocClk   = frequency;

	अगर (!pp_atomfwctrl_get_clk_inक्रमmation_by_clkid(hwmgr, SMU11_SYSPLL0_DCEFCLK_ID, SMU11_SYSPLL0_ID, &frequency))
		boot_values->ulDCEFClk  = frequency;

	अगर (!pp_atomfwctrl_get_clk_inक्रमmation_by_clkid(hwmgr, SMU11_SYSPLL0_ECLK_ID, SMU11_SYSPLL0_ID, &frequency))
		boot_values->ulEClk     = frequency;

	अगर (!pp_atomfwctrl_get_clk_inक्रमmation_by_clkid(hwmgr, SMU11_SYSPLL0_VCLK_ID, SMU11_SYSPLL0_ID, &frequency))
		boot_values->ulVClk     = frequency;

	अगर (!pp_atomfwctrl_get_clk_inक्रमmation_by_clkid(hwmgr, SMU11_SYSPLL0_DCLK_ID, SMU11_SYSPLL0_ID, &frequency))
		boot_values->ulDClk     = frequency;

	अगर (!pp_atomfwctrl_get_clk_inक्रमmation_by_clkid(hwmgr, SMU11_SYSPLL1_0_FCLK_ID, SMU11_SYSPLL1_2_ID, &frequency))
		boot_values->ulFClk     = frequency;
पूर्ण

अटल व्योम pp_atomfwctrl_copy_vbios_bootup_values_3_1(काष्ठा pp_hwmgr *hwmgr,
			काष्ठा pp_atomfwctrl_bios_boot_up_values *boot_values,
			काष्ठा atom_firmware_info_v3_1 *fw_info)
अणु
	uपूर्णांक32_t frequency = 0;

	boot_values->ulRevision = fw_info->firmware_revision;
	boot_values->ulGfxClk   = fw_info->bootup_sclk_in10khz;
	boot_values->ulUClk     = fw_info->bootup_mclk_in10khz;
	boot_values->usVddc     = fw_info->bootup_vddc_mv;
	boot_values->usVddci    = fw_info->bootup_vddci_mv;
	boot_values->usMvddc    = fw_info->bootup_mvddc_mv;
	boot_values->usVddGfx   = fw_info->bootup_vddgfx_mv;
	boot_values->ucCoolingID = fw_info->coolingsolution_id;
	boot_values->ulSocClk   = 0;
	boot_values->ulDCEFClk   = 0;

	अगर (!pp_atomfwctrl_get_clk_inक्रमmation_by_clkid(hwmgr, SMU9_SYSPLL0_SOCCLK_ID, 0, &frequency))
		boot_values->ulSocClk   = frequency;

	अगर (!pp_atomfwctrl_get_clk_inक्रमmation_by_clkid(hwmgr, SMU9_SYSPLL0_DCEFCLK_ID, 0, &frequency))
		boot_values->ulDCEFClk  = frequency;

	अगर (!pp_atomfwctrl_get_clk_inक्रमmation_by_clkid(hwmgr, SMU9_SYSPLL0_ECLK_ID, 0, &frequency))
		boot_values->ulEClk     = frequency;

	अगर (!pp_atomfwctrl_get_clk_inक्रमmation_by_clkid(hwmgr, SMU9_SYSPLL0_VCLK_ID, 0, &frequency))
		boot_values->ulVClk     = frequency;

	अगर (!pp_atomfwctrl_get_clk_inक्रमmation_by_clkid(hwmgr, SMU9_SYSPLL0_DCLK_ID, 0, &frequency))
		boot_values->ulDClk     = frequency;
पूर्ण

पूर्णांक pp_atomfwctrl_get_vbios_bootup_values(काष्ठा pp_hwmgr *hwmgr,
			काष्ठा pp_atomfwctrl_bios_boot_up_values *boot_values)
अणु
	काष्ठा atom_firmware_info_v3_2 *fwinfo_3_2;
	काष्ठा atom_firmware_info_v3_1 *fwinfo_3_1;
	काष्ठा atom_common_table_header *info = शून्य;
	uपूर्णांक16_t ix;

	ix = GetIndexIntoMasterDataTable(firmwareinfo);
	info = (काष्ठा atom_common_table_header *)
		smu_atom_get_data_table(hwmgr->adev,
				ix, शून्य, शून्य, शून्य);

	अगर (!info) अणु
		pr_info("Error retrieving BIOS firmwareinfo!");
		वापस -EINVAL;
	पूर्ण

	अगर ((info->क्रमmat_revision == 3) && (info->content_revision == 2)) अणु
		fwinfo_3_2 = (काष्ठा atom_firmware_info_v3_2 *)info;
		pp_atomfwctrl_copy_vbios_bootup_values_3_2(hwmgr,
				boot_values, fwinfo_3_2);
	पूर्ण अन्यथा अगर ((info->क्रमmat_revision == 3) && (info->content_revision == 1)) अणु
		fwinfo_3_1 = (काष्ठा atom_firmware_info_v3_1 *)info;
		pp_atomfwctrl_copy_vbios_bootup_values_3_1(hwmgr,
				boot_values, fwinfo_3_1);
	पूर्ण अन्यथा अणु
		pr_info("Fw info table revision does not match!");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक pp_atomfwctrl_get_smc_dpm_inक्रमmation(काष्ठा pp_hwmgr *hwmgr,
		काष्ठा pp_atomfwctrl_smc_dpm_parameters *param)
अणु
	काष्ठा atom_smc_dpm_info_v4_1 *info;
	uपूर्णांक16_t ix;

	ix = GetIndexIntoMasterDataTable(smc_dpm_info);
	info = (काष्ठा atom_smc_dpm_info_v4_1 *)
		smu_atom_get_data_table(hwmgr->adev,
				ix, शून्य, शून्य, शून्य);
	अगर (!info) अणु
		pr_info("Error retrieving BIOS Table Address!");
		वापस -EINVAL;
	पूर्ण

	param->liquid1_i2c_address = info->liquid1_i2c_address;
	param->liquid2_i2c_address = info->liquid2_i2c_address;
	param->vr_i2c_address = info->vr_i2c_address;
	param->plx_i2c_address = info->plx_i2c_address;

	param->liquid_i2c_linescl = info->liquid_i2c_linescl;
	param->liquid_i2c_linesda = info->liquid_i2c_linesda;
	param->vr_i2c_linescl = info->vr_i2c_linescl;
	param->vr_i2c_linesda = info->vr_i2c_linesda;

	param->plx_i2c_linescl = info->plx_i2c_linescl;
	param->plx_i2c_linesda = info->plx_i2c_linesda;
	param->vrsensorpresent = info->vrsensorpresent;
	param->liquidsensorpresent = info->liquidsensorpresent;

	param->maxvoltagestepgfx = info->maxvoltagestepgfx;
	param->maxvoltagestepsoc = info->maxvoltagestepsoc;

	param->vddgfxvrmapping = info->vddgfxvrmapping;
	param->vddsocvrmapping = info->vddsocvrmapping;
	param->vddmem0vrmapping = info->vddmem0vrmapping;
	param->vddmem1vrmapping = info->vddmem1vrmapping;

	param->gfxulvphasesheddingmask = info->gfxulvphasesheddingmask;
	param->soculvphasesheddingmask = info->soculvphasesheddingmask;

	param->gfxmaxcurrent = info->gfxmaxcurrent;
	param->gfxoffset = info->gfxoffset;
	param->padding_telemetrygfx = info->padding_telemetrygfx;

	param->socmaxcurrent = info->socmaxcurrent;
	param->socoffset = info->socoffset;
	param->padding_telemetrysoc = info->padding_telemetrysoc;

	param->mem0maxcurrent = info->mem0maxcurrent;
	param->mem0offset = info->mem0offset;
	param->padding_telemetrymem0 = info->padding_telemetrymem0;

	param->mem1maxcurrent = info->mem1maxcurrent;
	param->mem1offset = info->mem1offset;
	param->padding_telemetrymem1 = info->padding_telemetrymem1;

	param->acdcgpio = info->acdcgpio;
	param->acdcpolarity = info->acdcpolarity;
	param->vr0hotgpio = info->vr0hotgpio;
	param->vr0hotpolarity = info->vr0hotpolarity;

	param->vr1hotgpio = info->vr1hotgpio;
	param->vr1hotpolarity = info->vr1hotpolarity;
	param->padding1 = info->padding1;
	param->padding2 = info->padding2;

	param->ledpin0 = info->ledpin0;
	param->ledpin1 = info->ledpin1;
	param->ledpin2 = info->ledpin2;

	param->pllgfxclkspपढ़ोenabled = info->pllgfxclkspपढ़ोenabled;
	param->pllgfxclkspपढ़ोpercent = info->pllgfxclkspपढ़ोpercent;
	param->pllgfxclkspपढ़ोfreq = info->pllgfxclkspपढ़ोfreq;

	param->uclkspपढ़ोenabled = info->uclkspपढ़ोenabled;
	param->uclkspपढ़ोpercent = info->uclkspपढ़ोpercent;
	param->uclkspपढ़ोfreq = info->uclkspपढ़ोfreq;

	param->socclkspपढ़ोenabled = info->socclkspपढ़ोenabled;
	param->socclkspपढ़ोpercent = info->socclkspपढ़ोpercent;
	param->socclkspपढ़ोfreq = info->socclkspपढ़ोfreq;

	param->acggfxclkspपढ़ोenabled = info->acggfxclkspपढ़ोenabled;
	param->acggfxclkspपढ़ोpercent = info->acggfxclkspपढ़ोpercent;
	param->acggfxclkspपढ़ोfreq = info->acggfxclkspपढ़ोfreq;

	param->Vr2_I2C_address = info->Vr2_I2C_address;

	वापस 0;
पूर्ण
