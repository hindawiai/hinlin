<शैली गुरु>
/*
 * Copyright 2011 Advanced Micro Devices, Inc.
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
 * Authors: Alex Deucher
 */

#समावेश "amdgpu.h"
#समावेश "amdgpu_atombios.h"
#समावेश "amdgpu_i2c.h"
#समावेश "amdgpu_dpm.h"
#समावेश "atom.h"
#समावेश "amd_pcie.h"
#समावेश "amdgpu_display.h"
#समावेश "hwmgr.h"
#समावेश <linux/घातer_supply.h>

#घोषणा WIDTH_4K 3840

व्योम amdgpu_dpm_prपूर्णांक_class_info(u32 class, u32 class2)
अणु
	स्थिर अक्षर *s;

	चयन (class & ATOM_PPLIB_CLASSIFICATION_UI_MASK) अणु
	हाल ATOM_PPLIB_CLASSIFICATION_UI_NONE:
	शेष:
		s = "none";
		अवरोध;
	हाल ATOM_PPLIB_CLASSIFICATION_UI_BATTERY:
		s = "battery";
		अवरोध;
	हाल ATOM_PPLIB_CLASSIFICATION_UI_BALANCED:
		s = "balanced";
		अवरोध;
	हाल ATOM_PPLIB_CLASSIFICATION_UI_PERFORMANCE:
		s = "performance";
		अवरोध;
	पूर्ण
	prपूर्णांकk("\tui class: %s\n", s);
	prपूर्णांकk("\tinternal class:");
	अगर (((class & ~ATOM_PPLIB_CLASSIFICATION_UI_MASK) == 0) &&
	    (class2 == 0))
		pr_cont(" none");
	अन्यथा अणु
		अगर (class & ATOM_PPLIB_CLASSIFICATION_BOOT)
			pr_cont(" boot");
		अगर (class & ATOM_PPLIB_CLASSIFICATION_THERMAL)
			pr_cont(" thermal");
		अगर (class & ATOM_PPLIB_CLASSIFICATION_LIMITEDPOWERSOURCE)
			pr_cont(" limited_pwr");
		अगर (class & ATOM_PPLIB_CLASSIFICATION_REST)
			pr_cont(" rest");
		अगर (class & ATOM_PPLIB_CLASSIFICATION_FORCED)
			pr_cont(" forced");
		अगर (class & ATOM_PPLIB_CLASSIFICATION_3DPERFORMANCE)
			pr_cont(" 3d_perf");
		अगर (class & ATOM_PPLIB_CLASSIFICATION_OVERDRIVETEMPLATE)
			pr_cont(" ovrdrv");
		अगर (class & ATOM_PPLIB_CLASSIFICATION_UVDSTATE)
			pr_cont(" uvd");
		अगर (class & ATOM_PPLIB_CLASSIFICATION_3DLOW)
			pr_cont(" 3d_low");
		अगर (class & ATOM_PPLIB_CLASSIFICATION_ACPI)
			pr_cont(" acpi");
		अगर (class & ATOM_PPLIB_CLASSIFICATION_HD2STATE)
			pr_cont(" uvd_hd2");
		अगर (class & ATOM_PPLIB_CLASSIFICATION_HDSTATE)
			pr_cont(" uvd_hd");
		अगर (class & ATOM_PPLIB_CLASSIFICATION_SDSTATE)
			pr_cont(" uvd_sd");
		अगर (class2 & ATOM_PPLIB_CLASSIFICATION2_LIMITEDPOWERSOURCE_2)
			pr_cont(" limited_pwr2");
		अगर (class2 & ATOM_PPLIB_CLASSIFICATION2_ULV)
			pr_cont(" ulv");
		अगर (class2 & ATOM_PPLIB_CLASSIFICATION2_MVC)
			pr_cont(" uvd_mvc");
	पूर्ण
	pr_cont("\n");
पूर्ण

व्योम amdgpu_dpm_prपूर्णांक_cap_info(u32 caps)
अणु
	prपूर्णांकk("\tcaps:");
	अगर (caps & ATOM_PPLIB_SINGLE_DISPLAY_ONLY)
		pr_cont(" single_disp");
	अगर (caps & ATOM_PPLIB_SUPPORTS_VIDEO_PLAYBACK)
		pr_cont(" video");
	अगर (caps & ATOM_PPLIB_DISALLOW_ON_DC)
		pr_cont(" no_dc");
	pr_cont("\n");
पूर्ण

व्योम amdgpu_dpm_prपूर्णांक_ps_status(काष्ठा amdgpu_device *adev,
				काष्ठा amdgpu_ps *rps)
अणु
	prपूर्णांकk("\tstatus:");
	अगर (rps == adev->pm.dpm.current_ps)
		pr_cont(" c");
	अगर (rps == adev->pm.dpm.requested_ps)
		pr_cont(" r");
	अगर (rps == adev->pm.dpm.boot_ps)
		pr_cont(" b");
	pr_cont("\n");
पूर्ण

व्योम amdgpu_dpm_get_active_displays(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा drm_device *ddev = adev_to_drm(adev);
	काष्ठा drm_crtc *crtc;
	काष्ठा amdgpu_crtc *amdgpu_crtc;

	adev->pm.dpm.new_active_crtcs = 0;
	adev->pm.dpm.new_active_crtc_count = 0;
	अगर (adev->mode_info.num_crtc && adev->mode_info.mode_config_initialized) अणु
		list_क्रम_each_entry(crtc,
				    &ddev->mode_config.crtc_list, head) अणु
			amdgpu_crtc = to_amdgpu_crtc(crtc);
			अगर (amdgpu_crtc->enabled) अणु
				adev->pm.dpm.new_active_crtcs |= (1 << amdgpu_crtc->crtc_id);
				adev->pm.dpm.new_active_crtc_count++;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण


u32 amdgpu_dpm_get_vblank_समय(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा drm_device *dev = adev_to_drm(adev);
	काष्ठा drm_crtc *crtc;
	काष्ठा amdgpu_crtc *amdgpu_crtc;
	u32 vblank_in_pixels;
	u32 vblank_समय_us = 0xffffffff; /* अगर the displays are off, vblank समय is max */

	अगर (adev->mode_info.num_crtc && adev->mode_info.mode_config_initialized) अणु
		list_क्रम_each_entry(crtc, &dev->mode_config.crtc_list, head) अणु
			amdgpu_crtc = to_amdgpu_crtc(crtc);
			अगर (crtc->enabled && amdgpu_crtc->enabled && amdgpu_crtc->hw_mode.घड़ी) अणु
				vblank_in_pixels =
					amdgpu_crtc->hw_mode.crtc_htotal *
					(amdgpu_crtc->hw_mode.crtc_vblank_end -
					amdgpu_crtc->hw_mode.crtc_vdisplay +
					(amdgpu_crtc->v_border * 2));

				vblank_समय_us = vblank_in_pixels * 1000 / amdgpu_crtc->hw_mode.घड़ी;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस vblank_समय_us;
पूर्ण

u32 amdgpu_dpm_get_vrefresh(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा drm_device *dev = adev_to_drm(adev);
	काष्ठा drm_crtc *crtc;
	काष्ठा amdgpu_crtc *amdgpu_crtc;
	u32 vrefresh = 0;

	अगर (adev->mode_info.num_crtc && adev->mode_info.mode_config_initialized) अणु
		list_क्रम_each_entry(crtc, &dev->mode_config.crtc_list, head) अणु
			amdgpu_crtc = to_amdgpu_crtc(crtc);
			अगर (crtc->enabled && amdgpu_crtc->enabled && amdgpu_crtc->hw_mode.घड़ी) अणु
				vrefresh = drm_mode_vrefresh(&amdgpu_crtc->hw_mode);
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस vrefresh;
पूर्ण

bool amdgpu_is_पूर्णांकernal_thermal_sensor(क्रमागत amdgpu_पूर्णांक_thermal_type sensor)
अणु
	चयन (sensor) अणु
	हाल THERMAL_TYPE_RV6XX:
	हाल THERMAL_TYPE_RV770:
	हाल THERMAL_TYPE_EVERGREEN:
	हाल THERMAL_TYPE_SUMO:
	हाल THERMAL_TYPE_NI:
	हाल THERMAL_TYPE_SI:
	हाल THERMAL_TYPE_CI:
	हाल THERMAL_TYPE_KV:
		वापस true;
	हाल THERMAL_TYPE_ADT7473_WITH_INTERNAL:
	हाल THERMAL_TYPE_EMC2103_WITH_INTERNAL:
		वापस false; /* need special handling */
	हाल THERMAL_TYPE_NONE:
	हाल THERMAL_TYPE_EXTERNAL:
	हाल THERMAL_TYPE_EXTERNAL_GPIO:
	शेष:
		वापस false;
	पूर्ण
पूर्ण

जोड़ घातer_info अणु
	काष्ठा _ATOM_POWERPLAY_INFO info;
	काष्ठा _ATOM_POWERPLAY_INFO_V2 info_2;
	काष्ठा _ATOM_POWERPLAY_INFO_V3 info_3;
	काष्ठा _ATOM_PPLIB_POWERPLAYTABLE pplib;
	काष्ठा _ATOM_PPLIB_POWERPLAYTABLE2 pplib2;
	काष्ठा _ATOM_PPLIB_POWERPLAYTABLE3 pplib3;
	काष्ठा _ATOM_PPLIB_POWERPLAYTABLE4 pplib4;
	काष्ठा _ATOM_PPLIB_POWERPLAYTABLE5 pplib5;
पूर्ण;

जोड़ fan_info अणु
	काष्ठा _ATOM_PPLIB_FANTABLE fan;
	काष्ठा _ATOM_PPLIB_FANTABLE2 fan2;
	काष्ठा _ATOM_PPLIB_FANTABLE3 fan3;
पूर्ण;

अटल पूर्णांक amdgpu_parse_clk_voltage_dep_table(काष्ठा amdgpu_घड़ी_voltage_dependency_table *amdgpu_table,
					      ATOM_PPLIB_Clock_Voltage_Dependency_Table *atom_table)
अणु
	u32 size = atom_table->ucNumEntries *
		माप(काष्ठा amdgpu_घड़ी_voltage_dependency_entry);
	पूर्णांक i;
	ATOM_PPLIB_Clock_Voltage_Dependency_Record *entry;

	amdgpu_table->entries = kzalloc(size, GFP_KERNEL);
	अगर (!amdgpu_table->entries)
		वापस -ENOMEM;

	entry = &atom_table->entries[0];
	क्रम (i = 0; i < atom_table->ucNumEntries; i++) अणु
		amdgpu_table->entries[i].clk = le16_to_cpu(entry->usClockLow) |
			(entry->ucClockHigh << 16);
		amdgpu_table->entries[i].v = le16_to_cpu(entry->usVoltage);
		entry = (ATOM_PPLIB_Clock_Voltage_Dependency_Record *)
			((u8 *)entry + माप(ATOM_PPLIB_Clock_Voltage_Dependency_Record));
	पूर्ण
	amdgpu_table->count = atom_table->ucNumEntries;

	वापस 0;
पूर्ण

पूर्णांक amdgpu_get_platक्रमm_caps(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा amdgpu_mode_info *mode_info = &adev->mode_info;
	जोड़ घातer_info *घातer_info;
	पूर्णांक index = GetIndexIntoMasterTable(DATA, PowerPlayInfo);
	u16 data_offset;
	u8 frev, crev;

	अगर (!amdgpu_atom_parse_data_header(mode_info->atom_context, index, शून्य,
				   &frev, &crev, &data_offset))
		वापस -EINVAL;
	घातer_info = (जोड़ घातer_info *)(mode_info->atom_context->bios + data_offset);

	adev->pm.dpm.platक्रमm_caps = le32_to_cpu(घातer_info->pplib.ulPlatक्रमmCaps);
	adev->pm.dpm.backbias_response_समय = le16_to_cpu(घातer_info->pplib.usBackbiasTime);
	adev->pm.dpm.voltage_response_समय = le16_to_cpu(घातer_info->pplib.usVoltageTime);

	वापस 0;
पूर्ण

/* माप(ATOM_PPLIB_EXTENDEDHEADER) */
#घोषणा SIZE_OF_ATOM_PPLIB_EXTENDEDHEADER_V2 12
#घोषणा SIZE_OF_ATOM_PPLIB_EXTENDEDHEADER_V3 14
#घोषणा SIZE_OF_ATOM_PPLIB_EXTENDEDHEADER_V4 16
#घोषणा SIZE_OF_ATOM_PPLIB_EXTENDEDHEADER_V5 18
#घोषणा SIZE_OF_ATOM_PPLIB_EXTENDEDHEADER_V6 20
#घोषणा SIZE_OF_ATOM_PPLIB_EXTENDEDHEADER_V7 22
#घोषणा SIZE_OF_ATOM_PPLIB_EXTENDEDHEADER_V8 24
#घोषणा SIZE_OF_ATOM_PPLIB_EXTENDEDHEADER_V9 26

पूर्णांक amdgpu_parse_extended_घातer_table(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा amdgpu_mode_info *mode_info = &adev->mode_info;
	जोड़ घातer_info *घातer_info;
	जोड़ fan_info *fan_info;
	ATOM_PPLIB_Clock_Voltage_Dependency_Table *dep_table;
	पूर्णांक index = GetIndexIntoMasterTable(DATA, PowerPlayInfo);
	u16 data_offset;
	u8 frev, crev;
	पूर्णांक ret, i;

	अगर (!amdgpu_atom_parse_data_header(mode_info->atom_context, index, शून्य,
				   &frev, &crev, &data_offset))
		वापस -EINVAL;
	घातer_info = (जोड़ घातer_info *)(mode_info->atom_context->bios + data_offset);

	/* fan table */
	अगर (le16_to_cpu(घातer_info->pplib.usTableSize) >=
	    माप(काष्ठा _ATOM_PPLIB_POWERPLAYTABLE3)) अणु
		अगर (घातer_info->pplib3.usFanTableOffset) अणु
			fan_info = (जोड़ fan_info *)(mode_info->atom_context->bios + data_offset +
						      le16_to_cpu(घातer_info->pplib3.usFanTableOffset));
			adev->pm.dpm.fan.t_hyst = fan_info->fan.ucTHyst;
			adev->pm.dpm.fan.t_min = le16_to_cpu(fan_info->fan.usTMin);
			adev->pm.dpm.fan.t_med = le16_to_cpu(fan_info->fan.usTMed);
			adev->pm.dpm.fan.t_high = le16_to_cpu(fan_info->fan.usTHigh);
			adev->pm.dpm.fan.pwm_min = le16_to_cpu(fan_info->fan.usPWMMin);
			adev->pm.dpm.fan.pwm_med = le16_to_cpu(fan_info->fan.usPWMMed);
			adev->pm.dpm.fan.pwm_high = le16_to_cpu(fan_info->fan.usPWMHigh);
			अगर (fan_info->fan.ucFanTableFormat >= 2)
				adev->pm.dpm.fan.t_max = le16_to_cpu(fan_info->fan2.usTMax);
			अन्यथा
				adev->pm.dpm.fan.t_max = 10900;
			adev->pm.dpm.fan.cycle_delay = 100000;
			अगर (fan_info->fan.ucFanTableFormat >= 3) अणु
				adev->pm.dpm.fan.control_mode = fan_info->fan3.ucFanControlMode;
				adev->pm.dpm.fan.शेष_max_fan_pwm =
					le16_to_cpu(fan_info->fan3.usFanPWMMax);
				adev->pm.dpm.fan.शेष_fan_output_sensitivity = 4836;
				adev->pm.dpm.fan.fan_output_sensitivity =
					le16_to_cpu(fan_info->fan3.usFanOutputSensitivity);
			पूर्ण
			adev->pm.dpm.fan.ucode_fan_control = true;
		पूर्ण
	पूर्ण

	/* घड़ी dependancy tables, shedding tables */
	अगर (le16_to_cpu(घातer_info->pplib.usTableSize) >=
	    माप(काष्ठा _ATOM_PPLIB_POWERPLAYTABLE4)) अणु
		अगर (घातer_info->pplib4.usVddcDependencyOnSCLKOffset) अणु
			dep_table = (ATOM_PPLIB_Clock_Voltage_Dependency_Table *)
				(mode_info->atom_context->bios + data_offset +
				 le16_to_cpu(घातer_info->pplib4.usVddcDependencyOnSCLKOffset));
			ret = amdgpu_parse_clk_voltage_dep_table(&adev->pm.dpm.dyn_state.vddc_dependency_on_sclk,
								 dep_table);
			अगर (ret) अणु
				amdgpu_मुक्त_extended_घातer_table(adev);
				वापस ret;
			पूर्ण
		पूर्ण
		अगर (घातer_info->pplib4.usVddciDependencyOnMCLKOffset) अणु
			dep_table = (ATOM_PPLIB_Clock_Voltage_Dependency_Table *)
				(mode_info->atom_context->bios + data_offset +
				 le16_to_cpu(घातer_info->pplib4.usVddciDependencyOnMCLKOffset));
			ret = amdgpu_parse_clk_voltage_dep_table(&adev->pm.dpm.dyn_state.vddci_dependency_on_mclk,
								 dep_table);
			अगर (ret) अणु
				amdgpu_मुक्त_extended_घातer_table(adev);
				वापस ret;
			पूर्ण
		पूर्ण
		अगर (घातer_info->pplib4.usVddcDependencyOnMCLKOffset) अणु
			dep_table = (ATOM_PPLIB_Clock_Voltage_Dependency_Table *)
				(mode_info->atom_context->bios + data_offset +
				 le16_to_cpu(घातer_info->pplib4.usVddcDependencyOnMCLKOffset));
			ret = amdgpu_parse_clk_voltage_dep_table(&adev->pm.dpm.dyn_state.vddc_dependency_on_mclk,
								 dep_table);
			अगर (ret) अणु
				amdgpu_मुक्त_extended_घातer_table(adev);
				वापस ret;
			पूर्ण
		पूर्ण
		अगर (घातer_info->pplib4.usMvddDependencyOnMCLKOffset) अणु
			dep_table = (ATOM_PPLIB_Clock_Voltage_Dependency_Table *)
				(mode_info->atom_context->bios + data_offset +
				 le16_to_cpu(घातer_info->pplib4.usMvddDependencyOnMCLKOffset));
			ret = amdgpu_parse_clk_voltage_dep_table(&adev->pm.dpm.dyn_state.mvdd_dependency_on_mclk,
								 dep_table);
			अगर (ret) अणु
				amdgpu_मुक्त_extended_घातer_table(adev);
				वापस ret;
			पूर्ण
		पूर्ण
		अगर (घातer_info->pplib4.usMaxClockVoltageOnDCOffset) अणु
			ATOM_PPLIB_Clock_Voltage_Limit_Table *clk_v =
				(ATOM_PPLIB_Clock_Voltage_Limit_Table *)
				(mode_info->atom_context->bios + data_offset +
				 le16_to_cpu(घातer_info->pplib4.usMaxClockVoltageOnDCOffset));
			अगर (clk_v->ucNumEntries) अणु
				adev->pm.dpm.dyn_state.max_घड़ी_voltage_on_dc.sclk =
					le16_to_cpu(clk_v->entries[0].usSclkLow) |
					(clk_v->entries[0].ucSclkHigh << 16);
				adev->pm.dpm.dyn_state.max_घड़ी_voltage_on_dc.mclk =
					le16_to_cpu(clk_v->entries[0].usMclkLow) |
					(clk_v->entries[0].ucMclkHigh << 16);
				adev->pm.dpm.dyn_state.max_घड़ी_voltage_on_dc.vddc =
					le16_to_cpu(clk_v->entries[0].usVddc);
				adev->pm.dpm.dyn_state.max_घड़ी_voltage_on_dc.vddci =
					le16_to_cpu(clk_v->entries[0].usVddci);
			पूर्ण
		पूर्ण
		अगर (घातer_info->pplib4.usVddcPhaseShedLimitsTableOffset) अणु
			ATOM_PPLIB_PhaseSheddingLimits_Table *psl =
				(ATOM_PPLIB_PhaseSheddingLimits_Table *)
				(mode_info->atom_context->bios + data_offset +
				 le16_to_cpu(घातer_info->pplib4.usVddcPhaseShedLimitsTableOffset));
			ATOM_PPLIB_PhaseSheddingLimits_Record *entry;

			adev->pm.dpm.dyn_state.phase_shedding_limits_table.entries =
				kसुस्मृति(psl->ucNumEntries,
					माप(काष्ठा amdgpu_phase_shedding_limits_entry),
					GFP_KERNEL);
			अगर (!adev->pm.dpm.dyn_state.phase_shedding_limits_table.entries) अणु
				amdgpu_मुक्त_extended_घातer_table(adev);
				वापस -ENOMEM;
			पूर्ण

			entry = &psl->entries[0];
			क्रम (i = 0; i < psl->ucNumEntries; i++) अणु
				adev->pm.dpm.dyn_state.phase_shedding_limits_table.entries[i].sclk =
					le16_to_cpu(entry->usSclkLow) | (entry->ucSclkHigh << 16);
				adev->pm.dpm.dyn_state.phase_shedding_limits_table.entries[i].mclk =
					le16_to_cpu(entry->usMclkLow) | (entry->ucMclkHigh << 16);
				adev->pm.dpm.dyn_state.phase_shedding_limits_table.entries[i].voltage =
					le16_to_cpu(entry->usVoltage);
				entry = (ATOM_PPLIB_PhaseSheddingLimits_Record *)
					((u8 *)entry + माप(ATOM_PPLIB_PhaseSheddingLimits_Record));
			पूर्ण
			adev->pm.dpm.dyn_state.phase_shedding_limits_table.count =
				psl->ucNumEntries;
		पूर्ण
	पूर्ण

	/* cac data */
	अगर (le16_to_cpu(घातer_info->pplib.usTableSize) >=
	    माप(काष्ठा _ATOM_PPLIB_POWERPLAYTABLE5)) अणु
		adev->pm.dpm.tdp_limit = le32_to_cpu(घातer_info->pplib5.ulTDPLimit);
		adev->pm.dpm.near_tdp_limit = le32_to_cpu(घातer_info->pplib5.ulNearTDPLimit);
		adev->pm.dpm.near_tdp_limit_adjusted = adev->pm.dpm.near_tdp_limit;
		adev->pm.dpm.tdp_od_limit = le16_to_cpu(घातer_info->pplib5.usTDPODLimit);
		अगर (adev->pm.dpm.tdp_od_limit)
			adev->pm.dpm.घातer_control = true;
		अन्यथा
			adev->pm.dpm.घातer_control = false;
		adev->pm.dpm.tdp_adjusपंचांगent = 0;
		adev->pm.dpm.sq_ramping_threshold = le32_to_cpu(घातer_info->pplib5.ulSQRampingThreshold);
		adev->pm.dpm.cac_leakage = le32_to_cpu(घातer_info->pplib5.ulCACLeakage);
		adev->pm.dpm.load_line_slope = le16_to_cpu(घातer_info->pplib5.usLoadLineSlope);
		अगर (घातer_info->pplib5.usCACLeakageTableOffset) अणु
			ATOM_PPLIB_CAC_Leakage_Table *cac_table =
				(ATOM_PPLIB_CAC_Leakage_Table *)
				(mode_info->atom_context->bios + data_offset +
				 le16_to_cpu(घातer_info->pplib5.usCACLeakageTableOffset));
			ATOM_PPLIB_CAC_Leakage_Record *entry;
			u32 size = cac_table->ucNumEntries * माप(काष्ठा amdgpu_cac_leakage_table);
			adev->pm.dpm.dyn_state.cac_leakage_table.entries = kzalloc(size, GFP_KERNEL);
			अगर (!adev->pm.dpm.dyn_state.cac_leakage_table.entries) अणु
				amdgpu_मुक्त_extended_घातer_table(adev);
				वापस -ENOMEM;
			पूर्ण
			entry = &cac_table->entries[0];
			क्रम (i = 0; i < cac_table->ucNumEntries; i++) अणु
				अगर (adev->pm.dpm.platक्रमm_caps & ATOM_PP_PLATFORM_CAP_EVV) अणु
					adev->pm.dpm.dyn_state.cac_leakage_table.entries[i].vddc1 =
						le16_to_cpu(entry->usVddc1);
					adev->pm.dpm.dyn_state.cac_leakage_table.entries[i].vddc2 =
						le16_to_cpu(entry->usVddc2);
					adev->pm.dpm.dyn_state.cac_leakage_table.entries[i].vddc3 =
						le16_to_cpu(entry->usVddc3);
				पूर्ण अन्यथा अणु
					adev->pm.dpm.dyn_state.cac_leakage_table.entries[i].vddc =
						le16_to_cpu(entry->usVddc);
					adev->pm.dpm.dyn_state.cac_leakage_table.entries[i].leakage =
						le32_to_cpu(entry->ulLeakageValue);
				पूर्ण
				entry = (ATOM_PPLIB_CAC_Leakage_Record *)
					((u8 *)entry + माप(ATOM_PPLIB_CAC_Leakage_Record));
			पूर्ण
			adev->pm.dpm.dyn_state.cac_leakage_table.count = cac_table->ucNumEntries;
		पूर्ण
	पूर्ण

	/* ext tables */
	अगर (le16_to_cpu(घातer_info->pplib.usTableSize) >=
	    माप(काष्ठा _ATOM_PPLIB_POWERPLAYTABLE3)) अणु
		ATOM_PPLIB_EXTENDEDHEADER *ext_hdr = (ATOM_PPLIB_EXTENDEDHEADER *)
			(mode_info->atom_context->bios + data_offset +
			 le16_to_cpu(घातer_info->pplib3.usExtendendedHeaderOffset));
		अगर ((le16_to_cpu(ext_hdr->usSize) >= SIZE_OF_ATOM_PPLIB_EXTENDEDHEADER_V2) &&
			ext_hdr->usVCETableOffset) अणु
			VCEClockInfoArray *array = (VCEClockInfoArray *)
				(mode_info->atom_context->bios + data_offset +
				 le16_to_cpu(ext_hdr->usVCETableOffset) + 1);
			ATOM_PPLIB_VCE_Clock_Voltage_Limit_Table *limits =
				(ATOM_PPLIB_VCE_Clock_Voltage_Limit_Table *)
				(mode_info->atom_context->bios + data_offset +
				 le16_to_cpu(ext_hdr->usVCETableOffset) + 1 +
				 1 + array->ucNumEntries * माप(VCEClockInfo));
			ATOM_PPLIB_VCE_State_Table *states =
				(ATOM_PPLIB_VCE_State_Table *)
				(mode_info->atom_context->bios + data_offset +
				 le16_to_cpu(ext_hdr->usVCETableOffset) + 1 +
				 1 + (array->ucNumEntries * माप (VCEClockInfo)) +
				 1 + (limits->numEntries * माप(ATOM_PPLIB_VCE_Clock_Voltage_Limit_Record)));
			ATOM_PPLIB_VCE_Clock_Voltage_Limit_Record *entry;
			ATOM_PPLIB_VCE_State_Record *state_entry;
			VCEClockInfo *vce_clk;
			u32 size = limits->numEntries *
				माप(काष्ठा amdgpu_vce_घड़ी_voltage_dependency_entry);
			adev->pm.dpm.dyn_state.vce_घड़ी_voltage_dependency_table.entries =
				kzalloc(size, GFP_KERNEL);
			अगर (!adev->pm.dpm.dyn_state.vce_घड़ी_voltage_dependency_table.entries) अणु
				amdgpu_मुक्त_extended_घातer_table(adev);
				वापस -ENOMEM;
			पूर्ण
			adev->pm.dpm.dyn_state.vce_घड़ी_voltage_dependency_table.count =
				limits->numEntries;
			entry = &limits->entries[0];
			state_entry = &states->entries[0];
			क्रम (i = 0; i < limits->numEntries; i++) अणु
				vce_clk = (VCEClockInfo *)
					((u8 *)&array->entries[0] +
					 (entry->ucVCEClockInfoIndex * माप(VCEClockInfo)));
				adev->pm.dpm.dyn_state.vce_घड़ी_voltage_dependency_table.entries[i].evclk =
					le16_to_cpu(vce_clk->usEVClkLow) | (vce_clk->ucEVClkHigh << 16);
				adev->pm.dpm.dyn_state.vce_घड़ी_voltage_dependency_table.entries[i].ecclk =
					le16_to_cpu(vce_clk->usECClkLow) | (vce_clk->ucECClkHigh << 16);
				adev->pm.dpm.dyn_state.vce_घड़ी_voltage_dependency_table.entries[i].v =
					le16_to_cpu(entry->usVoltage);
				entry = (ATOM_PPLIB_VCE_Clock_Voltage_Limit_Record *)
					((u8 *)entry + माप(ATOM_PPLIB_VCE_Clock_Voltage_Limit_Record));
			पूर्ण
			adev->pm.dpm.num_of_vce_states =
					states->numEntries > AMD_MAX_VCE_LEVELS ?
					AMD_MAX_VCE_LEVELS : states->numEntries;
			क्रम (i = 0; i < adev->pm.dpm.num_of_vce_states; i++) अणु
				vce_clk = (VCEClockInfo *)
					((u8 *)&array->entries[0] +
					 (state_entry->ucVCEClockInfoIndex * माप(VCEClockInfo)));
				adev->pm.dpm.vce_states[i].evclk =
					le16_to_cpu(vce_clk->usEVClkLow) | (vce_clk->ucEVClkHigh << 16);
				adev->pm.dpm.vce_states[i].ecclk =
					le16_to_cpu(vce_clk->usECClkLow) | (vce_clk->ucECClkHigh << 16);
				adev->pm.dpm.vce_states[i].clk_idx =
					state_entry->ucClockInfoIndex & 0x3f;
				adev->pm.dpm.vce_states[i].pstate =
					(state_entry->ucClockInfoIndex & 0xc0) >> 6;
				state_entry = (ATOM_PPLIB_VCE_State_Record *)
					((u8 *)state_entry + माप(ATOM_PPLIB_VCE_State_Record));
			पूर्ण
		पूर्ण
		अगर ((le16_to_cpu(ext_hdr->usSize) >= SIZE_OF_ATOM_PPLIB_EXTENDEDHEADER_V3) &&
			ext_hdr->usUVDTableOffset) अणु
			UVDClockInfoArray *array = (UVDClockInfoArray *)
				(mode_info->atom_context->bios + data_offset +
				 le16_to_cpu(ext_hdr->usUVDTableOffset) + 1);
			ATOM_PPLIB_UVD_Clock_Voltage_Limit_Table *limits =
				(ATOM_PPLIB_UVD_Clock_Voltage_Limit_Table *)
				(mode_info->atom_context->bios + data_offset +
				 le16_to_cpu(ext_hdr->usUVDTableOffset) + 1 +
				 1 + (array->ucNumEntries * माप (UVDClockInfo)));
			ATOM_PPLIB_UVD_Clock_Voltage_Limit_Record *entry;
			u32 size = limits->numEntries *
				माप(काष्ठा amdgpu_uvd_घड़ी_voltage_dependency_entry);
			adev->pm.dpm.dyn_state.uvd_घड़ी_voltage_dependency_table.entries =
				kzalloc(size, GFP_KERNEL);
			अगर (!adev->pm.dpm.dyn_state.uvd_घड़ी_voltage_dependency_table.entries) अणु
				amdgpu_मुक्त_extended_घातer_table(adev);
				वापस -ENOMEM;
			पूर्ण
			adev->pm.dpm.dyn_state.uvd_घड़ी_voltage_dependency_table.count =
				limits->numEntries;
			entry = &limits->entries[0];
			क्रम (i = 0; i < limits->numEntries; i++) अणु
				UVDClockInfo *uvd_clk = (UVDClockInfo *)
					((u8 *)&array->entries[0] +
					 (entry->ucUVDClockInfoIndex * माप(UVDClockInfo)));
				adev->pm.dpm.dyn_state.uvd_घड़ी_voltage_dependency_table.entries[i].vclk =
					le16_to_cpu(uvd_clk->usVClkLow) | (uvd_clk->ucVClkHigh << 16);
				adev->pm.dpm.dyn_state.uvd_घड़ी_voltage_dependency_table.entries[i].dclk =
					le16_to_cpu(uvd_clk->usDClkLow) | (uvd_clk->ucDClkHigh << 16);
				adev->pm.dpm.dyn_state.uvd_घड़ी_voltage_dependency_table.entries[i].v =
					le16_to_cpu(entry->usVoltage);
				entry = (ATOM_PPLIB_UVD_Clock_Voltage_Limit_Record *)
					((u8 *)entry + माप(ATOM_PPLIB_UVD_Clock_Voltage_Limit_Record));
			पूर्ण
		पूर्ण
		अगर ((le16_to_cpu(ext_hdr->usSize) >= SIZE_OF_ATOM_PPLIB_EXTENDEDHEADER_V4) &&
			ext_hdr->usSAMUTableOffset) अणु
			ATOM_PPLIB_SAMClk_Voltage_Limit_Table *limits =
				(ATOM_PPLIB_SAMClk_Voltage_Limit_Table *)
				(mode_info->atom_context->bios + data_offset +
				 le16_to_cpu(ext_hdr->usSAMUTableOffset) + 1);
			ATOM_PPLIB_SAMClk_Voltage_Limit_Record *entry;
			u32 size = limits->numEntries *
				माप(काष्ठा amdgpu_घड़ी_voltage_dependency_entry);
			adev->pm.dpm.dyn_state.samu_घड़ी_voltage_dependency_table.entries =
				kzalloc(size, GFP_KERNEL);
			अगर (!adev->pm.dpm.dyn_state.samu_घड़ी_voltage_dependency_table.entries) अणु
				amdgpu_मुक्त_extended_घातer_table(adev);
				वापस -ENOMEM;
			पूर्ण
			adev->pm.dpm.dyn_state.samu_घड़ी_voltage_dependency_table.count =
				limits->numEntries;
			entry = &limits->entries[0];
			क्रम (i = 0; i < limits->numEntries; i++) अणु
				adev->pm.dpm.dyn_state.samu_घड़ी_voltage_dependency_table.entries[i].clk =
					le16_to_cpu(entry->usSAMClockLow) | (entry->ucSAMClockHigh << 16);
				adev->pm.dpm.dyn_state.samu_घड़ी_voltage_dependency_table.entries[i].v =
					le16_to_cpu(entry->usVoltage);
				entry = (ATOM_PPLIB_SAMClk_Voltage_Limit_Record *)
					((u8 *)entry + माप(ATOM_PPLIB_SAMClk_Voltage_Limit_Record));
			पूर्ण
		पूर्ण
		अगर ((le16_to_cpu(ext_hdr->usSize) >= SIZE_OF_ATOM_PPLIB_EXTENDEDHEADER_V5) &&
		    ext_hdr->usPPMTableOffset) अणु
			ATOM_PPLIB_PPM_Table *ppm = (ATOM_PPLIB_PPM_Table *)
				(mode_info->atom_context->bios + data_offset +
				 le16_to_cpu(ext_hdr->usPPMTableOffset));
			adev->pm.dpm.dyn_state.ppm_table =
				kzalloc(माप(काष्ठा amdgpu_ppm_table), GFP_KERNEL);
			अगर (!adev->pm.dpm.dyn_state.ppm_table) अणु
				amdgpu_मुक्त_extended_घातer_table(adev);
				वापस -ENOMEM;
			पूर्ण
			adev->pm.dpm.dyn_state.ppm_table->ppm_design = ppm->ucPpmDesign;
			adev->pm.dpm.dyn_state.ppm_table->cpu_core_number =
				le16_to_cpu(ppm->usCpuCoreNumber);
			adev->pm.dpm.dyn_state.ppm_table->platक्रमm_tdp =
				le32_to_cpu(ppm->ulPlatक्रमmTDP);
			adev->pm.dpm.dyn_state.ppm_table->small_ac_platक्रमm_tdp =
				le32_to_cpu(ppm->ulSmallACPlatक्रमmTDP);
			adev->pm.dpm.dyn_state.ppm_table->platक्रमm_tdc =
				le32_to_cpu(ppm->ulPlatक्रमmTDC);
			adev->pm.dpm.dyn_state.ppm_table->small_ac_platक्रमm_tdc =
				le32_to_cpu(ppm->ulSmallACPlatक्रमmTDC);
			adev->pm.dpm.dyn_state.ppm_table->apu_tdp =
				le32_to_cpu(ppm->ulApuTDP);
			adev->pm.dpm.dyn_state.ppm_table->dgpu_tdp =
				le32_to_cpu(ppm->ulDGpuTDP);
			adev->pm.dpm.dyn_state.ppm_table->dgpu_ulv_घातer =
				le32_to_cpu(ppm->ulDGpuUlvPower);
			adev->pm.dpm.dyn_state.ppm_table->tj_max =
				le32_to_cpu(ppm->ulTjmax);
		पूर्ण
		अगर ((le16_to_cpu(ext_hdr->usSize) >= SIZE_OF_ATOM_PPLIB_EXTENDEDHEADER_V6) &&
			ext_hdr->usACPTableOffset) अणु
			ATOM_PPLIB_ACPClk_Voltage_Limit_Table *limits =
				(ATOM_PPLIB_ACPClk_Voltage_Limit_Table *)
				(mode_info->atom_context->bios + data_offset +
				 le16_to_cpu(ext_hdr->usACPTableOffset) + 1);
			ATOM_PPLIB_ACPClk_Voltage_Limit_Record *entry;
			u32 size = limits->numEntries *
				माप(काष्ठा amdgpu_घड़ी_voltage_dependency_entry);
			adev->pm.dpm.dyn_state.acp_घड़ी_voltage_dependency_table.entries =
				kzalloc(size, GFP_KERNEL);
			अगर (!adev->pm.dpm.dyn_state.acp_घड़ी_voltage_dependency_table.entries) अणु
				amdgpu_मुक्त_extended_घातer_table(adev);
				वापस -ENOMEM;
			पूर्ण
			adev->pm.dpm.dyn_state.acp_घड़ी_voltage_dependency_table.count =
				limits->numEntries;
			entry = &limits->entries[0];
			क्रम (i = 0; i < limits->numEntries; i++) अणु
				adev->pm.dpm.dyn_state.acp_घड़ी_voltage_dependency_table.entries[i].clk =
					le16_to_cpu(entry->usACPClockLow) | (entry->ucACPClockHigh << 16);
				adev->pm.dpm.dyn_state.acp_घड़ी_voltage_dependency_table.entries[i].v =
					le16_to_cpu(entry->usVoltage);
				entry = (ATOM_PPLIB_ACPClk_Voltage_Limit_Record *)
					((u8 *)entry + माप(ATOM_PPLIB_ACPClk_Voltage_Limit_Record));
			पूर्ण
		पूर्ण
		अगर ((le16_to_cpu(ext_hdr->usSize) >= SIZE_OF_ATOM_PPLIB_EXTENDEDHEADER_V7) &&
			ext_hdr->usPowerTuneTableOffset) अणु
			u8 rev = *(u8 *)(mode_info->atom_context->bios + data_offset +
					 le16_to_cpu(ext_hdr->usPowerTuneTableOffset));
			ATOM_PowerTune_Table *pt;
			adev->pm.dpm.dyn_state.cac_tdp_table =
				kzalloc(माप(काष्ठा amdgpu_cac_tdp_table), GFP_KERNEL);
			अगर (!adev->pm.dpm.dyn_state.cac_tdp_table) अणु
				amdgpu_मुक्त_extended_घातer_table(adev);
				वापस -ENOMEM;
			पूर्ण
			अगर (rev > 0) अणु
				ATOM_PPLIB_POWERTUNE_Table_V1 *ppt = (ATOM_PPLIB_POWERTUNE_Table_V1 *)
					(mode_info->atom_context->bios + data_offset +
					 le16_to_cpu(ext_hdr->usPowerTuneTableOffset));
				adev->pm.dpm.dyn_state.cac_tdp_table->maximum_घातer_delivery_limit =
					ppt->usMaximumPowerDeliveryLimit;
				pt = &ppt->घातer_tune_table;
			पूर्ण अन्यथा अणु
				ATOM_PPLIB_POWERTUNE_Table *ppt = (ATOM_PPLIB_POWERTUNE_Table *)
					(mode_info->atom_context->bios + data_offset +
					 le16_to_cpu(ext_hdr->usPowerTuneTableOffset));
				adev->pm.dpm.dyn_state.cac_tdp_table->maximum_घातer_delivery_limit = 255;
				pt = &ppt->घातer_tune_table;
			पूर्ण
			adev->pm.dpm.dyn_state.cac_tdp_table->tdp = le16_to_cpu(pt->usTDP);
			adev->pm.dpm.dyn_state.cac_tdp_table->configurable_tdp =
				le16_to_cpu(pt->usConfigurableTDP);
			adev->pm.dpm.dyn_state.cac_tdp_table->tdc = le16_to_cpu(pt->usTDC);
			adev->pm.dpm.dyn_state.cac_tdp_table->battery_घातer_limit =
				le16_to_cpu(pt->usBatteryPowerLimit);
			adev->pm.dpm.dyn_state.cac_tdp_table->small_घातer_limit =
				le16_to_cpu(pt->usSmallPowerLimit);
			adev->pm.dpm.dyn_state.cac_tdp_table->low_cac_leakage =
				le16_to_cpu(pt->usLowCACLeakage);
			adev->pm.dpm.dyn_state.cac_tdp_table->high_cac_leakage =
				le16_to_cpu(pt->usHighCACLeakage);
		पूर्ण
		अगर ((le16_to_cpu(ext_hdr->usSize) >= SIZE_OF_ATOM_PPLIB_EXTENDEDHEADER_V8) &&
				ext_hdr->usSclkVddgfxTableOffset) अणु
			dep_table = (ATOM_PPLIB_Clock_Voltage_Dependency_Table *)
				(mode_info->atom_context->bios + data_offset +
				 le16_to_cpu(ext_hdr->usSclkVddgfxTableOffset));
			ret = amdgpu_parse_clk_voltage_dep_table(
					&adev->pm.dpm.dyn_state.vddgfx_dependency_on_sclk,
					dep_table);
			अगर (ret) अणु
				kमुक्त(adev->pm.dpm.dyn_state.vddgfx_dependency_on_sclk.entries);
				वापस ret;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

व्योम amdgpu_मुक्त_extended_घातer_table(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा amdgpu_dpm_dynamic_state *dyn_state = &adev->pm.dpm.dyn_state;

	kमुक्त(dyn_state->vddc_dependency_on_sclk.entries);
	kमुक्त(dyn_state->vddci_dependency_on_mclk.entries);
	kमुक्त(dyn_state->vddc_dependency_on_mclk.entries);
	kमुक्त(dyn_state->mvdd_dependency_on_mclk.entries);
	kमुक्त(dyn_state->cac_leakage_table.entries);
	kमुक्त(dyn_state->phase_shedding_limits_table.entries);
	kमुक्त(dyn_state->ppm_table);
	kमुक्त(dyn_state->cac_tdp_table);
	kमुक्त(dyn_state->vce_घड़ी_voltage_dependency_table.entries);
	kमुक्त(dyn_state->uvd_घड़ी_voltage_dependency_table.entries);
	kमुक्त(dyn_state->samu_घड़ी_voltage_dependency_table.entries);
	kमुक्त(dyn_state->acp_घड़ी_voltage_dependency_table.entries);
	kमुक्त(dyn_state->vddgfx_dependency_on_sclk.entries);
पूर्ण

अटल स्थिर अक्षर *pp_lib_thermal_controller_names[] = अणु
	"NONE",
	"lm63",
	"adm1032",
	"adm1030",
	"max6649",
	"lm64",
	"f75375",
	"RV6xx",
	"RV770",
	"adt7473",
	"NONE",
	"External GPIO",
	"Evergreen",
	"emc2103",
	"Sumo",
	"Northern Islands",
	"Southern Islands",
	"lm96163",
	"Sea Islands",
	"Kaveri/Kabini",
पूर्ण;

व्योम amdgpu_add_thermal_controller(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा amdgpu_mode_info *mode_info = &adev->mode_info;
	ATOM_PPLIB_POWERPLAYTABLE *घातer_table;
	पूर्णांक index = GetIndexIntoMasterTable(DATA, PowerPlayInfo);
	ATOM_PPLIB_THERMALCONTROLLER *controller;
	काष्ठा amdgpu_i2c_bus_rec i2c_bus;
	u16 data_offset;
	u8 frev, crev;

	अगर (!amdgpu_atom_parse_data_header(mode_info->atom_context, index, शून्य,
				   &frev, &crev, &data_offset))
		वापस;
	घातer_table = (ATOM_PPLIB_POWERPLAYTABLE *)
		(mode_info->atom_context->bios + data_offset);
	controller = &घातer_table->sThermalController;

	/* add the i2c bus क्रम thermal/fan chip */
	अगर (controller->ucType > 0) अणु
		अगर (controller->ucFanParameters & ATOM_PP_FANPARAMETERS_NOFAN)
			adev->pm.no_fan = true;
		adev->pm.fan_pulses_per_revolution =
			controller->ucFanParameters & ATOM_PP_FANPARAMETERS_TACHOMETER_PULSES_PER_REVOLUTION_MASK;
		अगर (adev->pm.fan_pulses_per_revolution) अणु
			adev->pm.fan_min_rpm = controller->ucFanMinRPM;
			adev->pm.fan_max_rpm = controller->ucFanMaxRPM;
		पूर्ण
		अगर (controller->ucType == ATOM_PP_THERMALCONTROLLER_RV6xx) अणु
			DRM_INFO("Internal thermal controller %s fan control\n",
				 (controller->ucFanParameters &
				  ATOM_PP_FANPARAMETERS_NOFAN) ? "without" : "with");
			adev->pm.पूर्णांक_thermal_type = THERMAL_TYPE_RV6XX;
		पूर्ण अन्यथा अगर (controller->ucType == ATOM_PP_THERMALCONTROLLER_RV770) अणु
			DRM_INFO("Internal thermal controller %s fan control\n",
				 (controller->ucFanParameters &
				  ATOM_PP_FANPARAMETERS_NOFAN) ? "without" : "with");
			adev->pm.पूर्णांक_thermal_type = THERMAL_TYPE_RV770;
		पूर्ण अन्यथा अगर (controller->ucType == ATOM_PP_THERMALCONTROLLER_EVERGREEN) अणु
			DRM_INFO("Internal thermal controller %s fan control\n",
				 (controller->ucFanParameters &
				  ATOM_PP_FANPARAMETERS_NOFAN) ? "without" : "with");
			adev->pm.पूर्णांक_thermal_type = THERMAL_TYPE_EVERGREEN;
		पूर्ण अन्यथा अगर (controller->ucType == ATOM_PP_THERMALCONTROLLER_SUMO) अणु
			DRM_INFO("Internal thermal controller %s fan control\n",
				 (controller->ucFanParameters &
				  ATOM_PP_FANPARAMETERS_NOFAN) ? "without" : "with");
			adev->pm.पूर्णांक_thermal_type = THERMAL_TYPE_SUMO;
		पूर्ण अन्यथा अगर (controller->ucType == ATOM_PP_THERMALCONTROLLER_NISLANDS) अणु
			DRM_INFO("Internal thermal controller %s fan control\n",
				 (controller->ucFanParameters &
				  ATOM_PP_FANPARAMETERS_NOFAN) ? "without" : "with");
			adev->pm.पूर्णांक_thermal_type = THERMAL_TYPE_NI;
		पूर्ण अन्यथा अगर (controller->ucType == ATOM_PP_THERMALCONTROLLER_SISLANDS) अणु
			DRM_INFO("Internal thermal controller %s fan control\n",
				 (controller->ucFanParameters &
				  ATOM_PP_FANPARAMETERS_NOFAN) ? "without" : "with");
			adev->pm.पूर्णांक_thermal_type = THERMAL_TYPE_SI;
		पूर्ण अन्यथा अगर (controller->ucType == ATOM_PP_THERMALCONTROLLER_CISLANDS) अणु
			DRM_INFO("Internal thermal controller %s fan control\n",
				 (controller->ucFanParameters &
				  ATOM_PP_FANPARAMETERS_NOFAN) ? "without" : "with");
			adev->pm.पूर्णांक_thermal_type = THERMAL_TYPE_CI;
		पूर्ण अन्यथा अगर (controller->ucType == ATOM_PP_THERMALCONTROLLER_KAVERI) अणु
			DRM_INFO("Internal thermal controller %s fan control\n",
				 (controller->ucFanParameters &
				  ATOM_PP_FANPARAMETERS_NOFAN) ? "without" : "with");
			adev->pm.पूर्णांक_thermal_type = THERMAL_TYPE_KV;
		पूर्ण अन्यथा अगर (controller->ucType == ATOM_PP_THERMALCONTROLLER_EXTERNAL_GPIO) अणु
			DRM_INFO("External GPIO thermal controller %s fan control\n",
				 (controller->ucFanParameters &
				  ATOM_PP_FANPARAMETERS_NOFAN) ? "without" : "with");
			adev->pm.पूर्णांक_thermal_type = THERMAL_TYPE_EXTERNAL_GPIO;
		पूर्ण अन्यथा अगर (controller->ucType ==
			   ATOM_PP_THERMALCONTROLLER_ADT7473_WITH_INTERNAL) अणु
			DRM_INFO("ADT7473 with internal thermal controller %s fan control\n",
				 (controller->ucFanParameters &
				  ATOM_PP_FANPARAMETERS_NOFAN) ? "without" : "with");
			adev->pm.पूर्णांक_thermal_type = THERMAL_TYPE_ADT7473_WITH_INTERNAL;
		पूर्ण अन्यथा अगर (controller->ucType ==
			   ATOM_PP_THERMALCONTROLLER_EMC2103_WITH_INTERNAL) अणु
			DRM_INFO("EMC2103 with internal thermal controller %s fan control\n",
				 (controller->ucFanParameters &
				  ATOM_PP_FANPARAMETERS_NOFAN) ? "without" : "with");
			adev->pm.पूर्णांक_thermal_type = THERMAL_TYPE_EMC2103_WITH_INTERNAL;
		पूर्ण अन्यथा अगर (controller->ucType < ARRAY_SIZE(pp_lib_thermal_controller_names)) अणु
			DRM_INFO("Possible %s thermal controller at 0x%02x %s fan control\n",
				 pp_lib_thermal_controller_names[controller->ucType],
				 controller->ucI2cAddress >> 1,
				 (controller->ucFanParameters &
				  ATOM_PP_FANPARAMETERS_NOFAN) ? "without" : "with");
			adev->pm.पूर्णांक_thermal_type = THERMAL_TYPE_EXTERNAL;
			i2c_bus = amdgpu_atombios_lookup_i2c_gpio(adev, controller->ucI2cLine);
			adev->pm.i2c_bus = amdgpu_i2c_lookup(adev, &i2c_bus);
			अगर (adev->pm.i2c_bus) अणु
				काष्ठा i2c_board_info info = अणु पूर्ण;
				स्थिर अक्षर *name = pp_lib_thermal_controller_names[controller->ucType];
				info.addr = controller->ucI2cAddress >> 1;
				strlcpy(info.type, name, माप(info.type));
				i2c_new_client_device(&adev->pm.i2c_bus->adapter, &info);
			पूर्ण
		पूर्ण अन्यथा अणु
			DRM_INFO("Unknown thermal controller type %d at 0x%02x %s fan control\n",
				 controller->ucType,
				 controller->ucI2cAddress >> 1,
				 (controller->ucFanParameters &
				  ATOM_PP_FANPARAMETERS_NOFAN) ? "without" : "with");
		पूर्ण
	पूर्ण
पूर्ण

क्रमागत amdgpu_pcie_gen amdgpu_get_pcie_gen_support(काष्ठा amdgpu_device *adev,
						 u32 sys_mask,
						 क्रमागत amdgpu_pcie_gen asic_gen,
						 क्रमागत amdgpu_pcie_gen शेष_gen)
अणु
	चयन (asic_gen) अणु
	हाल AMDGPU_PCIE_GEN1:
		वापस AMDGPU_PCIE_GEN1;
	हाल AMDGPU_PCIE_GEN2:
		वापस AMDGPU_PCIE_GEN2;
	हाल AMDGPU_PCIE_GEN3:
		वापस AMDGPU_PCIE_GEN3;
	शेष:
		अगर ((sys_mask & CAIL_PCIE_LINK_SPEED_SUPPORT_GEN3) &&
		    (शेष_gen == AMDGPU_PCIE_GEN3))
			वापस AMDGPU_PCIE_GEN3;
		अन्यथा अगर ((sys_mask & CAIL_PCIE_LINK_SPEED_SUPPORT_GEN2) &&
			 (शेष_gen == AMDGPU_PCIE_GEN2))
			वापस AMDGPU_PCIE_GEN2;
		अन्यथा
			वापस AMDGPU_PCIE_GEN1;
	पूर्ण
	वापस AMDGPU_PCIE_GEN1;
पूर्ण

काष्ठा amd_vce_state*
amdgpu_get_vce_घड़ी_state(व्योम *handle, u32 idx)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	अगर (idx < adev->pm.dpm.num_of_vce_states)
		वापस &adev->pm.dpm.vce_states[idx];

	वापस शून्य;
पूर्ण

पूर्णांक amdgpu_dpm_get_sclk(काष्ठा amdgpu_device *adev, bool low)
अणु
	स्थिर काष्ठा amd_pm_funcs *pp_funcs = adev->घातerplay.pp_funcs;

	वापस pp_funcs->get_sclk((adev)->घातerplay.pp_handle, (low));
पूर्ण

पूर्णांक amdgpu_dpm_get_mclk(काष्ठा amdgpu_device *adev, bool low)
अणु
	स्थिर काष्ठा amd_pm_funcs *pp_funcs = adev->घातerplay.pp_funcs;

	वापस pp_funcs->get_mclk((adev)->घातerplay.pp_handle, (low));
पूर्ण

पूर्णांक amdgpu_dpm_set_घातergating_by_smu(काष्ठा amdgpu_device *adev, uपूर्णांक32_t block_type, bool gate)
अणु
	पूर्णांक ret = 0;
	स्थिर काष्ठा amd_pm_funcs *pp_funcs = adev->घातerplay.pp_funcs;

	चयन (block_type) अणु
	हाल AMD_IP_BLOCK_TYPE_UVD:
	हाल AMD_IP_BLOCK_TYPE_VCE:
		अगर (pp_funcs && pp_funcs->set_घातergating_by_smu) अणु
			/*
			 * TODO: need a better lock mechanism
			 *
			 * Here adev->pm.mutex lock protection is enक्रमced on
			 * UVD and VCE हालs only. Since क्रम other हालs, there
			 * may be alपढ़ोy lock protection in amdgpu_pm.c.
			 * This is a quick fix क्रम the deadlock issue below.
			 *     NFO: task ocltst:2028 blocked क्रम more than 120 seconds.
			 *     Taपूर्णांकed: G           OE     5.0.0-37-generic #40~18.04.1-Ubuntu
			 *     echo 0 > /proc/sys/kernel/hung_task_समयout_secs" disables this message.
			 *     cltst          D    0  2028   2026 0x00000000
			 *     all Trace:
			 *     __schedule+0x2c0/0x870
			 *     schedule+0x2c/0x70
			 *     schedule_preempt_disabled+0xe/0x10
			 *     __mutex_lock.isra.9+0x26d/0x4e0
			 *     __mutex_lock_slowpath+0x13/0x20
			 *     ? __mutex_lock_slowpath+0x13/0x20
			 *     mutex_lock+0x2f/0x40
			 *     amdgpu_dpm_set_घातergating_by_smu+0x64/0xe0 [amdgpu]
			 *     gfx_v8_0_enable_gfx_अटल_mg_घातer_gating+0x3c/0x70 [amdgpu]
			 *     gfx_v8_0_set_घातergating_state+0x66/0x260 [amdgpu]
			 *     amdgpu_device_ip_set_घातergating_state+0x62/0xb0 [amdgpu]
			 *     pp_dpm_क्रमce_perक्रमmance_level+0xe7/0x100 [amdgpu]
			 *     amdgpu_set_dpm_क्रमced_perक्रमmance_level+0x129/0x330 [amdgpu]
			 */
			mutex_lock(&adev->pm.mutex);
			ret = (pp_funcs->set_घातergating_by_smu(
				(adev)->घातerplay.pp_handle, block_type, gate));
			mutex_unlock(&adev->pm.mutex);
		पूर्ण
		अवरोध;
	हाल AMD_IP_BLOCK_TYPE_GFX:
	हाल AMD_IP_BLOCK_TYPE_VCN:
	हाल AMD_IP_BLOCK_TYPE_SDMA:
	हाल AMD_IP_BLOCK_TYPE_JPEG:
	हाल AMD_IP_BLOCK_TYPE_GMC:
	हाल AMD_IP_BLOCK_TYPE_ACP:
		अगर (pp_funcs && pp_funcs->set_घातergating_by_smu) अणु
			ret = (pp_funcs->set_घातergating_by_smu(
				(adev)->घातerplay.pp_handle, block_type, gate));
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक amdgpu_dpm_baco_enter(काष्ठा amdgpu_device *adev)
अणु
	स्थिर काष्ठा amd_pm_funcs *pp_funcs = adev->घातerplay.pp_funcs;
	व्योम *pp_handle = adev->घातerplay.pp_handle;
	पूर्णांक ret = 0;

	अगर (!pp_funcs || !pp_funcs->set_asic_baco_state)
		वापस -ENOENT;

	/* enter BACO state */
	ret = pp_funcs->set_asic_baco_state(pp_handle, 1);

	वापस ret;
पूर्ण

पूर्णांक amdgpu_dpm_baco_निकास(काष्ठा amdgpu_device *adev)
अणु
	स्थिर काष्ठा amd_pm_funcs *pp_funcs = adev->घातerplay.pp_funcs;
	व्योम *pp_handle = adev->घातerplay.pp_handle;
	पूर्णांक ret = 0;

	अगर (!pp_funcs || !pp_funcs->set_asic_baco_state)
		वापस -ENOENT;

	/* निकास BACO state */
	ret = pp_funcs->set_asic_baco_state(pp_handle, 0);

	वापस ret;
पूर्ण

पूर्णांक amdgpu_dpm_set_mp1_state(काष्ठा amdgpu_device *adev,
			     क्रमागत pp_mp1_state mp1_state)
अणु
	पूर्णांक ret = 0;
	स्थिर काष्ठा amd_pm_funcs *pp_funcs = adev->घातerplay.pp_funcs;

	अगर (pp_funcs && pp_funcs->set_mp1_state) अणु
		ret = pp_funcs->set_mp1_state(
				adev->घातerplay.pp_handle,
				mp1_state);
	पूर्ण

	वापस ret;
पूर्ण

bool amdgpu_dpm_is_baco_supported(काष्ठा amdgpu_device *adev)
अणु
	स्थिर काष्ठा amd_pm_funcs *pp_funcs = adev->घातerplay.pp_funcs;
	व्योम *pp_handle = adev->घातerplay.pp_handle;
	bool baco_cap;

	अगर (!pp_funcs || !pp_funcs->get_asic_baco_capability)
		वापस false;

	अगर (pp_funcs->get_asic_baco_capability(pp_handle, &baco_cap))
		वापस false;

	वापस baco_cap;
पूर्ण

पूर्णांक amdgpu_dpm_mode2_reset(काष्ठा amdgpu_device *adev)
अणु
	स्थिर काष्ठा amd_pm_funcs *pp_funcs = adev->घातerplay.pp_funcs;
	व्योम *pp_handle = adev->घातerplay.pp_handle;

	अगर (!pp_funcs || !pp_funcs->asic_reset_mode_2)
		वापस -ENOENT;

	वापस pp_funcs->asic_reset_mode_2(pp_handle);
पूर्ण

पूर्णांक amdgpu_dpm_baco_reset(काष्ठा amdgpu_device *adev)
अणु
	स्थिर काष्ठा amd_pm_funcs *pp_funcs = adev->घातerplay.pp_funcs;
	व्योम *pp_handle = adev->घातerplay.pp_handle;
	पूर्णांक ret = 0;

	अगर (!pp_funcs || !pp_funcs->set_asic_baco_state)
		वापस -ENOENT;

	/* enter BACO state */
	ret = pp_funcs->set_asic_baco_state(pp_handle, 1);
	अगर (ret)
		वापस ret;

	/* निकास BACO state */
	ret = pp_funcs->set_asic_baco_state(pp_handle, 0);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

bool amdgpu_dpm_is_mode1_reset_supported(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा smu_context *smu = &adev->smu;

	अगर (is_support_sw_smu(adev))
		वापस smu_mode1_reset_is_support(smu);

	वापस false;
पूर्ण

पूर्णांक amdgpu_dpm_mode1_reset(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा smu_context *smu = &adev->smu;

	अगर (is_support_sw_smu(adev))
		वापस smu_mode1_reset(smu);

	वापस -EOPNOTSUPP;
पूर्ण

पूर्णांक amdgpu_dpm_चयन_घातer_profile(काष्ठा amdgpu_device *adev,
				    क्रमागत PP_SMC_POWER_PROखाता type,
				    bool en)
अणु
	स्थिर काष्ठा amd_pm_funcs *pp_funcs = adev->घातerplay.pp_funcs;
	पूर्णांक ret = 0;

	अगर (amdgpu_sriov_vf(adev))
		वापस 0;

	अगर (pp_funcs && pp_funcs->चयन_घातer_profile)
		ret = pp_funcs->चयन_घातer_profile(
			adev->घातerplay.pp_handle, type, en);

	वापस ret;
पूर्ण

पूर्णांक amdgpu_dpm_set_xgmi_pstate(काष्ठा amdgpu_device *adev,
			       uपूर्णांक32_t pstate)
अणु
	स्थिर काष्ठा amd_pm_funcs *pp_funcs = adev->घातerplay.pp_funcs;
	पूर्णांक ret = 0;

	अगर (pp_funcs && pp_funcs->set_xgmi_pstate)
		ret = pp_funcs->set_xgmi_pstate(adev->घातerplay.pp_handle,
								pstate);

	वापस ret;
पूर्ण

पूर्णांक amdgpu_dpm_set_df_cstate(काष्ठा amdgpu_device *adev,
			     uपूर्णांक32_t cstate)
अणु
	पूर्णांक ret = 0;
	स्थिर काष्ठा amd_pm_funcs *pp_funcs = adev->घातerplay.pp_funcs;
	व्योम *pp_handle = adev->घातerplay.pp_handle;

	अगर (pp_funcs && pp_funcs->set_df_cstate)
		ret = pp_funcs->set_df_cstate(pp_handle, cstate);

	वापस ret;
पूर्ण

पूर्णांक amdgpu_dpm_allow_xgmi_घातer_करोwn(काष्ठा amdgpu_device *adev, bool en)
अणु
	काष्ठा smu_context *smu = &adev->smu;

	अगर (is_support_sw_smu(adev))
		वापस smu_allow_xgmi_घातer_करोwn(smu, en);

	वापस 0;
पूर्ण

पूर्णांक amdgpu_dpm_enable_mgpu_fan_boost(काष्ठा amdgpu_device *adev)
अणु
	व्योम *pp_handle = adev->घातerplay.pp_handle;
	स्थिर काष्ठा amd_pm_funcs *pp_funcs =
			adev->घातerplay.pp_funcs;
	पूर्णांक ret = 0;

	अगर (pp_funcs && pp_funcs->enable_mgpu_fan_boost)
		ret = pp_funcs->enable_mgpu_fan_boost(pp_handle);

	वापस ret;
पूर्ण

पूर्णांक amdgpu_dpm_set_घड़ीgating_by_smu(काष्ठा amdgpu_device *adev,
				      uपूर्णांक32_t msg_id)
अणु
	व्योम *pp_handle = adev->घातerplay.pp_handle;
	स्थिर काष्ठा amd_pm_funcs *pp_funcs =
			adev->घातerplay.pp_funcs;
	पूर्णांक ret = 0;

	अगर (pp_funcs && pp_funcs->set_घड़ीgating_by_smu)
		ret = pp_funcs->set_घड़ीgating_by_smu(pp_handle,
						       msg_id);

	वापस ret;
पूर्ण

पूर्णांक amdgpu_dpm_smu_i2c_bus_access(काष्ठा amdgpu_device *adev,
				  bool acquire)
अणु
	व्योम *pp_handle = adev->घातerplay.pp_handle;
	स्थिर काष्ठा amd_pm_funcs *pp_funcs =
			adev->घातerplay.pp_funcs;
	पूर्णांक ret = -EOPNOTSUPP;

	अगर (pp_funcs && pp_funcs->smu_i2c_bus_access)
		ret = pp_funcs->smu_i2c_bus_access(pp_handle,
						   acquire);

	वापस ret;
पूर्ण

व्योम amdgpu_pm_acpi_event_handler(काष्ठा amdgpu_device *adev)
अणु
	अगर (adev->pm.dpm_enabled) अणु
		mutex_lock(&adev->pm.mutex);
		अगर (घातer_supply_is_प्रणाली_supplied() > 0)
			adev->pm.ac_घातer = true;
		अन्यथा
			adev->pm.ac_घातer = false;
		अगर (adev->घातerplay.pp_funcs &&
		    adev->घातerplay.pp_funcs->enable_bapm)
			amdgpu_dpm_enable_bapm(adev, adev->pm.ac_घातer);
		mutex_unlock(&adev->pm.mutex);

		अगर (is_support_sw_smu(adev))
			smu_set_ac_dc(&adev->smu);
	पूर्ण
पूर्ण

पूर्णांक amdgpu_dpm_पढ़ो_sensor(काष्ठा amdgpu_device *adev, क्रमागत amd_pp_sensors sensor,
			   व्योम *data, uपूर्णांक32_t *size)
अणु
	स्थिर काष्ठा amd_pm_funcs *pp_funcs = adev->घातerplay.pp_funcs;
	पूर्णांक ret = 0;

	अगर (!data || !size)
		वापस -EINVAL;

	अगर (pp_funcs && pp_funcs->पढ़ो_sensor)
		ret = pp_funcs->पढ़ो_sensor((adev)->घातerplay.pp_handle,
								    sensor, data, size);
	अन्यथा
		ret = -EINVAL;

	वापस ret;
पूर्ण

व्योम amdgpu_dpm_thermal_work_handler(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा amdgpu_device *adev =
		container_of(work, काष्ठा amdgpu_device,
			     pm.dpm.thermal.work);
	/* चयन to the thermal state */
	क्रमागत amd_pm_state_type dpm_state = POWER_STATE_TYPE_INTERNAL_THERMAL;
	पूर्णांक temp, size = माप(temp);

	अगर (!adev->pm.dpm_enabled)
		वापस;

	अगर (!amdgpu_dpm_पढ़ो_sensor(adev, AMDGPU_PP_SENSOR_GPU_TEMP,
				    (व्योम *)&temp, &size)) अणु
		अगर (temp < adev->pm.dpm.thermal.min_temp)
			/* चयन back the user state */
			dpm_state = adev->pm.dpm.user_state;
	पूर्ण अन्यथा अणु
		अगर (adev->pm.dpm.thermal.high_to_low)
			/* चयन back the user state */
			dpm_state = adev->pm.dpm.user_state;
	पूर्ण
	mutex_lock(&adev->pm.mutex);
	अगर (dpm_state == POWER_STATE_TYPE_INTERNAL_THERMAL)
		adev->pm.dpm.thermal_active = true;
	अन्यथा
		adev->pm.dpm.thermal_active = false;
	adev->pm.dpm.state = dpm_state;
	mutex_unlock(&adev->pm.mutex);

	amdgpu_pm_compute_घड़ीs(adev);
पूर्ण

अटल काष्ठा amdgpu_ps *amdgpu_dpm_pick_घातer_state(काष्ठा amdgpu_device *adev,
						     क्रमागत amd_pm_state_type dpm_state)
अणु
	पूर्णांक i;
	काष्ठा amdgpu_ps *ps;
	u32 ui_class;
	bool single_display = (adev->pm.dpm.new_active_crtc_count < 2) ?
		true : false;

	/* check अगर the vblank period is too लघु to adjust the mclk */
	अगर (single_display && adev->घातerplay.pp_funcs->vblank_too_लघु) अणु
		अगर (amdgpu_dpm_vblank_too_लघु(adev))
			single_display = false;
	पूर्ण

	/* certain older asics have a separare 3D perक्रमmance state,
	 * so try that first अगर the user selected perक्रमmance
	 */
	अगर (dpm_state == POWER_STATE_TYPE_PERFORMANCE)
		dpm_state = POWER_STATE_TYPE_INTERNAL_3DPERF;
	/* balanced states करोn't exist at the moment */
	अगर (dpm_state == POWER_STATE_TYPE_BALANCED)
		dpm_state = POWER_STATE_TYPE_PERFORMANCE;

restart_search:
	/* Pick the best घातer state based on current conditions */
	क्रम (i = 0; i < adev->pm.dpm.num_ps; i++) अणु
		ps = &adev->pm.dpm.ps[i];
		ui_class = ps->class & ATOM_PPLIB_CLASSIFICATION_UI_MASK;
		चयन (dpm_state) अणु
		/* user states */
		हाल POWER_STATE_TYPE_BATTERY:
			अगर (ui_class == ATOM_PPLIB_CLASSIFICATION_UI_BATTERY) अणु
				अगर (ps->caps & ATOM_PPLIB_SINGLE_DISPLAY_ONLY) अणु
					अगर (single_display)
						वापस ps;
				पूर्ण अन्यथा
					वापस ps;
			पूर्ण
			अवरोध;
		हाल POWER_STATE_TYPE_BALANCED:
			अगर (ui_class == ATOM_PPLIB_CLASSIFICATION_UI_BALANCED) अणु
				अगर (ps->caps & ATOM_PPLIB_SINGLE_DISPLAY_ONLY) अणु
					अगर (single_display)
						वापस ps;
				पूर्ण अन्यथा
					वापस ps;
			पूर्ण
			अवरोध;
		हाल POWER_STATE_TYPE_PERFORMANCE:
			अगर (ui_class == ATOM_PPLIB_CLASSIFICATION_UI_PERFORMANCE) अणु
				अगर (ps->caps & ATOM_PPLIB_SINGLE_DISPLAY_ONLY) अणु
					अगर (single_display)
						वापस ps;
				पूर्ण अन्यथा
					वापस ps;
			पूर्ण
			अवरोध;
		/* पूर्णांकernal states */
		हाल POWER_STATE_TYPE_INTERNAL_UVD:
			अगर (adev->pm.dpm.uvd_ps)
				वापस adev->pm.dpm.uvd_ps;
			अन्यथा
				अवरोध;
		हाल POWER_STATE_TYPE_INTERNAL_UVD_SD:
			अगर (ps->class & ATOM_PPLIB_CLASSIFICATION_SDSTATE)
				वापस ps;
			अवरोध;
		हाल POWER_STATE_TYPE_INTERNAL_UVD_HD:
			अगर (ps->class & ATOM_PPLIB_CLASSIFICATION_HDSTATE)
				वापस ps;
			अवरोध;
		हाल POWER_STATE_TYPE_INTERNAL_UVD_HD2:
			अगर (ps->class & ATOM_PPLIB_CLASSIFICATION_HD2STATE)
				वापस ps;
			अवरोध;
		हाल POWER_STATE_TYPE_INTERNAL_UVD_MVC:
			अगर (ps->class2 & ATOM_PPLIB_CLASSIFICATION2_MVC)
				वापस ps;
			अवरोध;
		हाल POWER_STATE_TYPE_INTERNAL_BOOT:
			वापस adev->pm.dpm.boot_ps;
		हाल POWER_STATE_TYPE_INTERNAL_THERMAL:
			अगर (ps->class & ATOM_PPLIB_CLASSIFICATION_THERMAL)
				वापस ps;
			अवरोध;
		हाल POWER_STATE_TYPE_INTERNAL_ACPI:
			अगर (ps->class & ATOM_PPLIB_CLASSIFICATION_ACPI)
				वापस ps;
			अवरोध;
		हाल POWER_STATE_TYPE_INTERNAL_ULV:
			अगर (ps->class2 & ATOM_PPLIB_CLASSIFICATION2_ULV)
				वापस ps;
			अवरोध;
		हाल POWER_STATE_TYPE_INTERNAL_3DPERF:
			अगर (ps->class & ATOM_PPLIB_CLASSIFICATION_3DPERFORMANCE)
				वापस ps;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण
	/* use a fallback state अगर we didn't match */
	चयन (dpm_state) अणु
	हाल POWER_STATE_TYPE_INTERNAL_UVD_SD:
		dpm_state = POWER_STATE_TYPE_INTERNAL_UVD_HD;
		जाओ restart_search;
	हाल POWER_STATE_TYPE_INTERNAL_UVD_HD:
	हाल POWER_STATE_TYPE_INTERNAL_UVD_HD2:
	हाल POWER_STATE_TYPE_INTERNAL_UVD_MVC:
		अगर (adev->pm.dpm.uvd_ps) अणु
			वापस adev->pm.dpm.uvd_ps;
		पूर्ण अन्यथा अणु
			dpm_state = POWER_STATE_TYPE_PERFORMANCE;
			जाओ restart_search;
		पूर्ण
	हाल POWER_STATE_TYPE_INTERNAL_THERMAL:
		dpm_state = POWER_STATE_TYPE_INTERNAL_ACPI;
		जाओ restart_search;
	हाल POWER_STATE_TYPE_INTERNAL_ACPI:
		dpm_state = POWER_STATE_TYPE_BATTERY;
		जाओ restart_search;
	हाल POWER_STATE_TYPE_BATTERY:
	हाल POWER_STATE_TYPE_BALANCED:
	हाल POWER_STATE_TYPE_INTERNAL_3DPERF:
		dpm_state = POWER_STATE_TYPE_PERFORMANCE;
		जाओ restart_search;
	शेष:
		अवरोध;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम amdgpu_dpm_change_घातer_state_locked(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा amdgpu_ps *ps;
	क्रमागत amd_pm_state_type dpm_state;
	पूर्णांक ret;
	bool equal = false;

	/* अगर dpm init failed */
	अगर (!adev->pm.dpm_enabled)
		वापस;

	अगर (adev->pm.dpm.user_state != adev->pm.dpm.state) अणु
		/* add other state override checks here */
		अगर ((!adev->pm.dpm.thermal_active) &&
		    (!adev->pm.dpm.uvd_active))
			adev->pm.dpm.state = adev->pm.dpm.user_state;
	पूर्ण
	dpm_state = adev->pm.dpm.state;

	ps = amdgpu_dpm_pick_घातer_state(adev, dpm_state);
	अगर (ps)
		adev->pm.dpm.requested_ps = ps;
	अन्यथा
		वापस;

	अगर (amdgpu_dpm == 1 && adev->घातerplay.pp_funcs->prपूर्णांक_घातer_state) अणु
		prपूर्णांकk("switching from power state:\n");
		amdgpu_dpm_prपूर्णांक_घातer_state(adev, adev->pm.dpm.current_ps);
		prपूर्णांकk("switching to power state:\n");
		amdgpu_dpm_prपूर्णांक_घातer_state(adev, adev->pm.dpm.requested_ps);
	पूर्ण

	/* update whether vce is active */
	ps->vce_active = adev->pm.dpm.vce_active;
	अगर (adev->घातerplay.pp_funcs->display_configuration_changed)
		amdgpu_dpm_display_configuration_changed(adev);

	ret = amdgpu_dpm_pre_set_घातer_state(adev);
	अगर (ret)
		वापस;

	अगर (adev->घातerplay.pp_funcs->check_state_equal) अणु
		अगर (0 != amdgpu_dpm_check_state_equal(adev, adev->pm.dpm.current_ps, adev->pm.dpm.requested_ps, &equal))
			equal = false;
	पूर्ण

	अगर (equal)
		वापस;

	amdgpu_dpm_set_घातer_state(adev);
	amdgpu_dpm_post_set_घातer_state(adev);

	adev->pm.dpm.current_active_crtcs = adev->pm.dpm.new_active_crtcs;
	adev->pm.dpm.current_active_crtc_count = adev->pm.dpm.new_active_crtc_count;

	अगर (adev->घातerplay.pp_funcs->क्रमce_perक्रमmance_level) अणु
		अगर (adev->pm.dpm.thermal_active) अणु
			क्रमागत amd_dpm_क्रमced_level level = adev->pm.dpm.क्रमced_level;
			/* क्रमce low perf level क्रम thermal */
			amdgpu_dpm_क्रमce_perक्रमmance_level(adev, AMD_DPM_FORCED_LEVEL_LOW);
			/* save the user's level */
			adev->pm.dpm.क्रमced_level = level;
		पूर्ण अन्यथा अणु
			/* otherwise, user selected level */
			amdgpu_dpm_क्रमce_perक्रमmance_level(adev, adev->pm.dpm.क्रमced_level);
		पूर्ण
	पूर्ण
पूर्ण

व्योम amdgpu_pm_compute_घड़ीs(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक i = 0;

	अगर (!adev->pm.dpm_enabled)
		वापस;

	अगर (adev->mode_info.num_crtc)
		amdgpu_display_bandwidth_update(adev);

	क्रम (i = 0; i < AMDGPU_MAX_RINGS; i++) अणु
		काष्ठा amdgpu_ring *ring = adev->rings[i];
		अगर (ring && ring->sched.पढ़ोy)
			amdgpu_fence_रुको_empty(ring);
	पूर्ण

	अगर (adev->घातerplay.pp_funcs->dispatch_tasks) अणु
		अगर (!amdgpu_device_has_dc_support(adev)) अणु
			mutex_lock(&adev->pm.mutex);
			amdgpu_dpm_get_active_displays(adev);
			adev->pm.pm_display_cfg.num_display = adev->pm.dpm.new_active_crtc_count;
			adev->pm.pm_display_cfg.vrefresh = amdgpu_dpm_get_vrefresh(adev);
			adev->pm.pm_display_cfg.min_vblank_समय = amdgpu_dpm_get_vblank_समय(adev);
			/* we have issues with mclk चयनing with
			 * refresh rates over 120 hz on the non-DC code.
			 */
			अगर (adev->pm.pm_display_cfg.vrefresh > 120)
				adev->pm.pm_display_cfg.min_vblank_समय = 0;
			अगर (adev->घातerplay.pp_funcs->display_configuration_change)
				adev->घातerplay.pp_funcs->display_configuration_change(
							adev->घातerplay.pp_handle,
							&adev->pm.pm_display_cfg);
			mutex_unlock(&adev->pm.mutex);
		पूर्ण
		amdgpu_dpm_dispatch_task(adev, AMD_PP_TASK_DISPLAY_CONFIG_CHANGE, शून्य);
	पूर्ण अन्यथा अणु
		mutex_lock(&adev->pm.mutex);
		amdgpu_dpm_get_active_displays(adev);
		amdgpu_dpm_change_घातer_state_locked(adev);
		mutex_unlock(&adev->pm.mutex);
	पूर्ण
पूर्ण

व्योम amdgpu_dpm_enable_uvd(काष्ठा amdgpu_device *adev, bool enable)
अणु
	पूर्णांक ret = 0;

	अगर (adev->family == AMDGPU_FAMILY_SI) अणु
		mutex_lock(&adev->pm.mutex);
		अगर (enable) अणु
			adev->pm.dpm.uvd_active = true;
			adev->pm.dpm.state = POWER_STATE_TYPE_INTERNAL_UVD;
		पूर्ण अन्यथा अणु
			adev->pm.dpm.uvd_active = false;
		पूर्ण
		mutex_unlock(&adev->pm.mutex);

		amdgpu_pm_compute_घड़ीs(adev);
	पूर्ण अन्यथा अणु
		ret = amdgpu_dpm_set_घातergating_by_smu(adev, AMD_IP_BLOCK_TYPE_UVD, !enable);
		अगर (ret)
			DRM_ERROR("Dpm %s uvd failed, ret = %d. \n",
				  enable ? "enable" : "disable", ret);

		/* enable/disable Low Memory PState क्रम UVD (4k videos) */
		अगर (adev->asic_type == CHIP_STONEY &&
			adev->uvd.decode_image_width >= WIDTH_4K) अणु
			काष्ठा pp_hwmgr *hwmgr = adev->घातerplay.pp_handle;

			अगर (hwmgr && hwmgr->hwmgr_func &&
			    hwmgr->hwmgr_func->update_nbdpm_pstate)
				hwmgr->hwmgr_func->update_nbdpm_pstate(hwmgr,
								       !enable,
								       true);
		पूर्ण
	पूर्ण
पूर्ण

व्योम amdgpu_dpm_enable_vce(काष्ठा amdgpu_device *adev, bool enable)
अणु
	पूर्णांक ret = 0;

	अगर (adev->family == AMDGPU_FAMILY_SI) अणु
		mutex_lock(&adev->pm.mutex);
		अगर (enable) अणु
			adev->pm.dpm.vce_active = true;
			/* XXX select vce level based on ring/task */
			adev->pm.dpm.vce_level = AMD_VCE_LEVEL_AC_ALL;
		पूर्ण अन्यथा अणु
			adev->pm.dpm.vce_active = false;
		पूर्ण
		mutex_unlock(&adev->pm.mutex);

		amdgpu_pm_compute_घड़ीs(adev);
	पूर्ण अन्यथा अणु
		ret = amdgpu_dpm_set_घातergating_by_smu(adev, AMD_IP_BLOCK_TYPE_VCE, !enable);
		अगर (ret)
			DRM_ERROR("Dpm %s vce failed, ret = %d. \n",
				  enable ? "enable" : "disable", ret);
	पूर्ण
पूर्ण

व्योम amdgpu_pm_prपूर्णांक_घातer_states(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक i;

	अगर (adev->घातerplay.pp_funcs->prपूर्णांक_घातer_state == शून्य)
		वापस;

	क्रम (i = 0; i < adev->pm.dpm.num_ps; i++)
		amdgpu_dpm_prपूर्णांक_घातer_state(adev, &adev->pm.dpm.ps[i]);

पूर्ण

व्योम amdgpu_dpm_enable_jpeg(काष्ठा amdgpu_device *adev, bool enable)
अणु
	पूर्णांक ret = 0;

	ret = amdgpu_dpm_set_घातergating_by_smu(adev, AMD_IP_BLOCK_TYPE_JPEG, !enable);
	अगर (ret)
		DRM_ERROR("Dpm %s jpeg failed, ret = %d. \n",
			  enable ? "enable" : "disable", ret);
पूर्ण

पूर्णांक amdgpu_pm_load_smu_firmware(काष्ठा amdgpu_device *adev, uपूर्णांक32_t *smu_version)
अणु
	पूर्णांक r;

	अगर (adev->घातerplay.pp_funcs && adev->घातerplay.pp_funcs->load_firmware) अणु
		r = adev->घातerplay.pp_funcs->load_firmware(adev->घातerplay.pp_handle);
		अगर (r) अणु
			pr_err("smu firmware loading failed\n");
			वापस r;
		पूर्ण

		अगर (smu_version)
			*smu_version = adev->pm.fw_version;
	पूर्ण

	वापस 0;
पूर्ण
