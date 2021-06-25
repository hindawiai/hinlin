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
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/slab.h>
#समावेश <linux/fb.h>

#समावेश "vega10_processpptables.h"
#समावेश "ppatomfwctrl.h"
#समावेश "atomfirmware.h"
#समावेश "pp_debug.h"
#समावेश "cgs_common.h"
#समावेश "vega10_pptable.h"

#घोषणा NUM_DSPCLK_LEVELS 8
#घोषणा VEGA10_ENGINECLOCK_HARDMAX 198000

अटल व्योम set_hw_cap(काष्ठा pp_hwmgr *hwmgr, bool enable,
		क्रमागत phm_platक्रमm_caps cap)
अणु
	अगर (enable)
		phm_cap_set(hwmgr->platक्रमm_descriptor.platक्रमmCaps, cap);
	अन्यथा
		phm_cap_unset(hwmgr->platक्रमm_descriptor.platक्रमmCaps, cap);
पूर्ण

अटल स्थिर व्योम *get_घातerplay_table(काष्ठा pp_hwmgr *hwmgr)
अणु
	पूर्णांक index = GetIndexIntoMasterDataTable(घातerplayinfo);

	u16 size;
	u8 frev, crev;
	स्थिर व्योम *table_address = hwmgr->soft_pp_table;

	अगर (!table_address) अणु
		table_address = (ATOM_Vega10_POWERPLAYTABLE *)
				smu_atom_get_data_table(hwmgr->adev, index,
						&size, &frev, &crev);

		hwmgr->soft_pp_table = table_address;	/*Cache the result in RAM.*/
		hwmgr->soft_pp_table_size = size;
	पूर्ण

	वापस table_address;
पूर्ण

अटल पूर्णांक check_घातerplay_tables(
		काष्ठा pp_hwmgr *hwmgr,
		स्थिर ATOM_Vega10_POWERPLAYTABLE *घातerplay_table)
अणु
	स्थिर ATOM_Vega10_State_Array *state_arrays;

	state_arrays = (ATOM_Vega10_State_Array *)(((अचिन्हित दीर्घ)घातerplay_table) +
		le16_to_cpu(घातerplay_table->usStateArrayOffset));

	PP_ASSERT_WITH_CODE((घातerplay_table->sHeader.क्रमmat_revision >=
			ATOM_Vega10_TABLE_REVISION_VEGA10),
		"Unsupported PPTable format!", वापस -1);
	PP_ASSERT_WITH_CODE(घातerplay_table->usStateArrayOffset,
		"State table is not set!", वापस -1);
	PP_ASSERT_WITH_CODE(घातerplay_table->sHeader.काष्ठाuresize > 0,
		"Invalid PowerPlay Table!", वापस -1);
	PP_ASSERT_WITH_CODE(state_arrays->ucNumEntries > 0,
		"Invalid PowerPlay Table!", वापस -1);

	वापस 0;
पूर्ण

अटल पूर्णांक set_platक्रमm_caps(काष्ठा pp_hwmgr *hwmgr, uपूर्णांक32_t घातerplay_caps)
अणु
	set_hw_cap(
			hwmgr,
			0 != (घातerplay_caps & ATOM_VEGA10_PP_PLATFORM_CAP_POWERPLAY),
			PHM_Platक्रमmCaps_PowerPlaySupport);

	set_hw_cap(
			hwmgr,
			0 != (घातerplay_caps & ATOM_VEGA10_PP_PLATFORM_CAP_SBIOSPOWERSOURCE),
			PHM_Platक्रमmCaps_BiosPowerSourceControl);

	set_hw_cap(
			hwmgr,
			0 != (घातerplay_caps & ATOM_VEGA10_PP_PLATFORM_CAP_HARDWAREDC),
			PHM_Platक्रमmCaps_AutomaticDCTransition);

	set_hw_cap(
			hwmgr,
			0 != (घातerplay_caps & ATOM_VEGA10_PP_PLATFORM_CAP_BACO),
			PHM_Platक्रमmCaps_BACO);

	set_hw_cap(
			hwmgr,
			0 != (घातerplay_caps & ATOM_VEGA10_PP_PLATFORM_COMBINE_PCC_WITH_THERMAL_SIGNAL),
			PHM_Platक्रमmCaps_CombinePCCWithThermalSignal);

	वापस 0;
पूर्ण

अटल पूर्णांक init_thermal_controller(
		काष्ठा pp_hwmgr *hwmgr,
		स्थिर ATOM_Vega10_POWERPLAYTABLE *घातerplay_table)
अणु
	स्थिर ATOM_Vega10_Thermal_Controller *thermal_controller;
	स्थिर Vega10_PPTable_Generic_SubTable_Header *header;
	स्थिर ATOM_Vega10_Fan_Table *fan_table_v1;
	स्थिर ATOM_Vega10_Fan_Table_V2 *fan_table_v2;
	स्थिर ATOM_Vega10_Fan_Table_V3 *fan_table_v3;

	thermal_controller = (ATOM_Vega10_Thermal_Controller *)
			(((अचिन्हित दीर्घ)घातerplay_table) +
			le16_to_cpu(घातerplay_table->usThermalControllerOffset));

	PP_ASSERT_WITH_CODE((घातerplay_table->usThermalControllerOffset != 0),
			"Thermal controller table not set!", वापस -EINVAL);

	hwmgr->thermal_controller.ucType = thermal_controller->ucType;
	hwmgr->thermal_controller.ucI2cLine = thermal_controller->ucI2cLine;
	hwmgr->thermal_controller.ucI2cAddress = thermal_controller->ucI2cAddress;

	hwmgr->thermal_controller.fanInfo.bNoFan =
			(0 != (thermal_controller->ucFanParameters &
			ATOM_VEGA10_PP_FANPARAMETERS_NOFAN));

	hwmgr->thermal_controller.fanInfo.ucTachometerPulsesPerRevolution =
			thermal_controller->ucFanParameters &
			ATOM_VEGA10_PP_FANPARAMETERS_TACHOMETER_PULSES_PER_REVOLUTION_MASK;

	hwmgr->thermal_controller.fanInfo.ulMinRPM =
			thermal_controller->ucFanMinRPM * 100UL;
	hwmgr->thermal_controller.fanInfo.ulMaxRPM =
			thermal_controller->ucFanMaxRPM * 100UL;

	hwmgr->thermal_controller.advanceFanControlParameters.ulCycleDelay
			= 100000;

	set_hw_cap(
			hwmgr,
			ATOM_VEGA10_PP_THERMALCONTROLLER_NONE != hwmgr->thermal_controller.ucType,
			PHM_Platक्रमmCaps_ThermalController);

	अगर (!घातerplay_table->usFanTableOffset)
		वापस 0;

	header = (स्थिर Vega10_PPTable_Generic_SubTable_Header *)
			(((अचिन्हित दीर्घ)घातerplay_table) +
			le16_to_cpu(घातerplay_table->usFanTableOffset));

	अगर (header->ucRevId == 10) अणु
		fan_table_v1 = (ATOM_Vega10_Fan_Table *)header;

		PP_ASSERT_WITH_CODE((fan_table_v1->ucRevId >= 8),
				"Invalid Input Fan Table!", वापस -EINVAL);

		phm_cap_set(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
				PHM_Platक्रमmCaps_MicrocodeFanControl);

		hwmgr->thermal_controller.advanceFanControlParameters.usFanOutputSensitivity =
				le16_to_cpu(fan_table_v1->usFanOutputSensitivity);
		hwmgr->thermal_controller.advanceFanControlParameters.usMaxFanRPM =
				le16_to_cpu(fan_table_v1->usFanRPMMax);
		hwmgr->thermal_controller.advanceFanControlParameters.usFanRPMMaxLimit =
				le16_to_cpu(fan_table_v1->usThrottlingRPM);
		hwmgr->thermal_controller.advanceFanControlParameters.ulMinFanSCLKAcousticLimit =
				le16_to_cpu(fan_table_v1->usFanAcousticLimit);
		hwmgr->thermal_controller.advanceFanControlParameters.usTMax =
				le16_to_cpu(fan_table_v1->usTargetTemperature);
		hwmgr->thermal_controller.advanceFanControlParameters.usPWMMin =
				le16_to_cpu(fan_table_v1->usMinimumPWMLimit);
		hwmgr->thermal_controller.advanceFanControlParameters.ulTargetGfxClk =
				le16_to_cpu(fan_table_v1->usTargetGfxClk);
		hwmgr->thermal_controller.advanceFanControlParameters.usFanGainEdge =
				le16_to_cpu(fan_table_v1->usFanGainEdge);
		hwmgr->thermal_controller.advanceFanControlParameters.usFanGainHotspot =
				le16_to_cpu(fan_table_v1->usFanGainHotspot);
		hwmgr->thermal_controller.advanceFanControlParameters.usFanGainLiquid =
				le16_to_cpu(fan_table_v1->usFanGainLiquid);
		hwmgr->thermal_controller.advanceFanControlParameters.usFanGainVrVddc =
				le16_to_cpu(fan_table_v1->usFanGainVrVddc);
		hwmgr->thermal_controller.advanceFanControlParameters.usFanGainVrMvdd =
				le16_to_cpu(fan_table_v1->usFanGainVrMvdd);
		hwmgr->thermal_controller.advanceFanControlParameters.usFanGainPlx =
				le16_to_cpu(fan_table_v1->usFanGainPlx);
		hwmgr->thermal_controller.advanceFanControlParameters.usFanGainHbm =
				le16_to_cpu(fan_table_v1->usFanGainHbm);

		hwmgr->thermal_controller.advanceFanControlParameters.ucEnableZeroRPM =
				fan_table_v1->ucEnableZeroRPM;
		hwmgr->thermal_controller.advanceFanControlParameters.usZeroRPMStopTemperature =
				le16_to_cpu(fan_table_v1->usFanStopTemperature);
		hwmgr->thermal_controller.advanceFanControlParameters.usZeroRPMStartTemperature =
				le16_to_cpu(fan_table_v1->usFanStartTemperature);
	पूर्ण अन्यथा अगर (header->ucRevId == 0xb) अणु
		fan_table_v2 = (ATOM_Vega10_Fan_Table_V2 *)header;

		hwmgr->thermal_controller.fanInfo.ucTachometerPulsesPerRevolution =
				fan_table_v2->ucFanParameters & ATOM_VEGA10_PP_FANPARAMETERS_TACHOMETER_PULSES_PER_REVOLUTION_MASK;
		hwmgr->thermal_controller.fanInfo.ulMinRPM = fan_table_v2->ucFanMinRPM * 100UL;
		hwmgr->thermal_controller.fanInfo.ulMaxRPM = fan_table_v2->ucFanMaxRPM * 100UL;
		phm_cap_set(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
				PHM_Platक्रमmCaps_MicrocodeFanControl);
		hwmgr->thermal_controller.advanceFanControlParameters.usFanOutputSensitivity =
				le16_to_cpu(fan_table_v2->usFanOutputSensitivity);
		hwmgr->thermal_controller.advanceFanControlParameters.usMaxFanRPM =
				fan_table_v2->ucFanMaxRPM * 100UL;
		hwmgr->thermal_controller.advanceFanControlParameters.usFanRPMMaxLimit =
				le16_to_cpu(fan_table_v2->usThrottlingRPM);
		hwmgr->thermal_controller.advanceFanControlParameters.ulMinFanSCLKAcousticLimit =
				le16_to_cpu(fan_table_v2->usFanAcousticLimitRpm);
		hwmgr->thermal_controller.advanceFanControlParameters.usTMax =
				le16_to_cpu(fan_table_v2->usTargetTemperature);
		hwmgr->thermal_controller.advanceFanControlParameters.usPWMMin =
				le16_to_cpu(fan_table_v2->usMinimumPWMLimit);
		hwmgr->thermal_controller.advanceFanControlParameters.ulTargetGfxClk =
				le16_to_cpu(fan_table_v2->usTargetGfxClk);
		hwmgr->thermal_controller.advanceFanControlParameters.usFanGainEdge =
				le16_to_cpu(fan_table_v2->usFanGainEdge);
		hwmgr->thermal_controller.advanceFanControlParameters.usFanGainHotspot =
				le16_to_cpu(fan_table_v2->usFanGainHotspot);
		hwmgr->thermal_controller.advanceFanControlParameters.usFanGainLiquid =
				le16_to_cpu(fan_table_v2->usFanGainLiquid);
		hwmgr->thermal_controller.advanceFanControlParameters.usFanGainVrVddc =
				le16_to_cpu(fan_table_v2->usFanGainVrVddc);
		hwmgr->thermal_controller.advanceFanControlParameters.usFanGainVrMvdd =
				le16_to_cpu(fan_table_v2->usFanGainVrMvdd);
		hwmgr->thermal_controller.advanceFanControlParameters.usFanGainPlx =
				le16_to_cpu(fan_table_v2->usFanGainPlx);
		hwmgr->thermal_controller.advanceFanControlParameters.usFanGainHbm =
				le16_to_cpu(fan_table_v2->usFanGainHbm);

		hwmgr->thermal_controller.advanceFanControlParameters.ucEnableZeroRPM =
				fan_table_v2->ucEnableZeroRPM;
		hwmgr->thermal_controller.advanceFanControlParameters.usZeroRPMStopTemperature =
				le16_to_cpu(fan_table_v2->usFanStopTemperature);
		hwmgr->thermal_controller.advanceFanControlParameters.usZeroRPMStartTemperature =
				le16_to_cpu(fan_table_v2->usFanStartTemperature);
	पूर्ण अन्यथा अगर (header->ucRevId > 0xb) अणु
		fan_table_v3 = (ATOM_Vega10_Fan_Table_V3 *)header;

		hwmgr->thermal_controller.fanInfo.ucTachometerPulsesPerRevolution =
				fan_table_v3->ucFanParameters & ATOM_VEGA10_PP_FANPARAMETERS_TACHOMETER_PULSES_PER_REVOLUTION_MASK;
		hwmgr->thermal_controller.fanInfo.ulMinRPM = fan_table_v3->ucFanMinRPM * 100UL;
		hwmgr->thermal_controller.fanInfo.ulMaxRPM = fan_table_v3->ucFanMaxRPM * 100UL;
		phm_cap_set(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
				PHM_Platक्रमmCaps_MicrocodeFanControl);
		hwmgr->thermal_controller.advanceFanControlParameters.usFanOutputSensitivity =
				le16_to_cpu(fan_table_v3->usFanOutputSensitivity);
		hwmgr->thermal_controller.advanceFanControlParameters.usMaxFanRPM =
				fan_table_v3->ucFanMaxRPM * 100UL;
		hwmgr->thermal_controller.advanceFanControlParameters.usFanRPMMaxLimit =
				le16_to_cpu(fan_table_v3->usThrottlingRPM);
		hwmgr->thermal_controller.advanceFanControlParameters.ulMinFanSCLKAcousticLimit =
				le16_to_cpu(fan_table_v3->usFanAcousticLimitRpm);
		hwmgr->thermal_controller.advanceFanControlParameters.usTMax =
				le16_to_cpu(fan_table_v3->usTargetTemperature);
		hwmgr->thermal_controller.advanceFanControlParameters.usPWMMin =
				le16_to_cpu(fan_table_v3->usMinimumPWMLimit);
		hwmgr->thermal_controller.advanceFanControlParameters.ulTargetGfxClk =
				le16_to_cpu(fan_table_v3->usTargetGfxClk);
		hwmgr->thermal_controller.advanceFanControlParameters.usFanGainEdge =
				le16_to_cpu(fan_table_v3->usFanGainEdge);
		hwmgr->thermal_controller.advanceFanControlParameters.usFanGainHotspot =
				le16_to_cpu(fan_table_v3->usFanGainHotspot);
		hwmgr->thermal_controller.advanceFanControlParameters.usFanGainLiquid =
				le16_to_cpu(fan_table_v3->usFanGainLiquid);
		hwmgr->thermal_controller.advanceFanControlParameters.usFanGainVrVddc =
				le16_to_cpu(fan_table_v3->usFanGainVrVddc);
		hwmgr->thermal_controller.advanceFanControlParameters.usFanGainVrMvdd =
				le16_to_cpu(fan_table_v3->usFanGainVrMvdd);
		hwmgr->thermal_controller.advanceFanControlParameters.usFanGainPlx =
				le16_to_cpu(fan_table_v3->usFanGainPlx);
		hwmgr->thermal_controller.advanceFanControlParameters.usFanGainHbm =
				le16_to_cpu(fan_table_v3->usFanGainHbm);

		hwmgr->thermal_controller.advanceFanControlParameters.ucEnableZeroRPM =
				fan_table_v3->ucEnableZeroRPM;
		hwmgr->thermal_controller.advanceFanControlParameters.usZeroRPMStopTemperature =
				le16_to_cpu(fan_table_v3->usFanStopTemperature);
		hwmgr->thermal_controller.advanceFanControlParameters.usZeroRPMStartTemperature =
				le16_to_cpu(fan_table_v3->usFanStartTemperature);
		hwmgr->thermal_controller.advanceFanControlParameters.usMGpuThrottlingRPMLimit =
				le16_to_cpu(fan_table_v3->usMGpuThrottlingRPM);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक init_over_drive_limits(
		काष्ठा pp_hwmgr *hwmgr,
		स्थिर ATOM_Vega10_POWERPLAYTABLE *घातerplay_table)
अणु
	स्थिर ATOM_Vega10_GFXCLK_Dependency_Table *gfxclk_dep_table =
			(स्थिर ATOM_Vega10_GFXCLK_Dependency_Table *)
			(((अचिन्हित दीर्घ) घातerplay_table) +
			le16_to_cpu(घातerplay_table->usGfxclkDependencyTableOffset));
	bool is_acg_enabled = false;
	ATOM_Vega10_GFXCLK_Dependency_Record_V2 *patom_record_v2;

	अगर (gfxclk_dep_table->ucRevId == 1) अणु
		patom_record_v2 =
			(ATOM_Vega10_GFXCLK_Dependency_Record_V2 *)gfxclk_dep_table->entries;
		is_acg_enabled =
			(bool)patom_record_v2[gfxclk_dep_table->ucNumEntries-1].ucACGEnable;
	पूर्ण

	अगर (घातerplay_table->ulMaxODEngineClock > VEGA10_ENGINECLOCK_HARDMAX &&
		!is_acg_enabled)
		hwmgr->platक्रमm_descriptor.overdriveLimit.engineClock =
			VEGA10_ENGINECLOCK_HARDMAX;
	अन्यथा
		hwmgr->platक्रमm_descriptor.overdriveLimit.engineClock =
			le32_to_cpu(घातerplay_table->ulMaxODEngineClock);
	hwmgr->platक्रमm_descriptor.overdriveLimit.memoryClock =
			le32_to_cpu(घातerplay_table->ulMaxODMemoryClock);

	hwmgr->platक्रमm_descriptor.minOverdriveVDDC = 0;
	hwmgr->platक्रमm_descriptor.maxOverdriveVDDC = 0;
	hwmgr->platक्रमm_descriptor.overdriveVDDCStep = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक get_mm_घड़ी_voltage_table(
		काष्ठा pp_hwmgr *hwmgr,
		phm_ppt_v1_mm_घड़ी_voltage_dependency_table **vega10_mm_table,
		स्थिर ATOM_Vega10_MM_Dependency_Table *mm_dependency_table)
अणु
	uपूर्णांक32_t i;
	स्थिर ATOM_Vega10_MM_Dependency_Record *mm_dependency_record;
	phm_ppt_v1_mm_घड़ी_voltage_dependency_table *mm_table;

	PP_ASSERT_WITH_CODE((mm_dependency_table->ucNumEntries != 0),
			"Invalid PowerPlay Table!", वापस -1);

	mm_table = kzalloc(काष्ठा_size(mm_table, entries, mm_dependency_table->ucNumEntries),
			   GFP_KERNEL);
	अगर (!mm_table)
		वापस -ENOMEM;

	mm_table->count = mm_dependency_table->ucNumEntries;

	क्रम (i = 0; i < mm_dependency_table->ucNumEntries; i++) अणु
		mm_dependency_record = &mm_dependency_table->entries[i];
		mm_table->entries[i].vddcInd = mm_dependency_record->ucVddcInd;
		mm_table->entries[i].samघड़ी =
				le32_to_cpu(mm_dependency_record->ulPSPClk);
		mm_table->entries[i].eclk = le32_to_cpu(mm_dependency_record->ulEClk);
		mm_table->entries[i].vclk = le32_to_cpu(mm_dependency_record->ulVClk);
		mm_table->entries[i].dclk = le32_to_cpu(mm_dependency_record->ulDClk);
	पूर्ण

	*vega10_mm_table = mm_table;

	वापस 0;
पूर्ण

अटल व्योम get_scl_sda_value(uपूर्णांक8_t line, uपूर्णांक8_t *scl, uपूर्णांक8_t* sda)
अणु
	चयन(line)अणु
	हाल Vega10_I2CLineID_DDC1:
		*scl = Vega10_I2C_DDC1CLK;
		*sda = Vega10_I2C_DDC1DATA;
		अवरोध;
	हाल Vega10_I2CLineID_DDC2:
		*scl = Vega10_I2C_DDC2CLK;
		*sda = Vega10_I2C_DDC2DATA;
		अवरोध;
	हाल Vega10_I2CLineID_DDC3:
		*scl = Vega10_I2C_DDC3CLK;
		*sda = Vega10_I2C_DDC3DATA;
		अवरोध;
	हाल Vega10_I2CLineID_DDC4:
		*scl = Vega10_I2C_DDC4CLK;
		*sda = Vega10_I2C_DDC4DATA;
		अवरोध;
	हाल Vega10_I2CLineID_DDC5:
		*scl = Vega10_I2C_DDC5CLK;
		*sda = Vega10_I2C_DDC5DATA;
		अवरोध;
	हाल Vega10_I2CLineID_DDC6:
		*scl = Vega10_I2C_DDC6CLK;
		*sda = Vega10_I2C_DDC6DATA;
		अवरोध;
	हाल Vega10_I2CLineID_SCLSDA:
		*scl = Vega10_I2C_SCL;
		*sda = Vega10_I2C_SDA;
		अवरोध;
	हाल Vega10_I2CLineID_DDCVGA:
		*scl = Vega10_I2C_DDCVGACLK;
		*sda = Vega10_I2C_DDCVGADATA;
		अवरोध;
	शेष:
		*scl = 0;
		*sda = 0;
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक get_tdp_table(
		काष्ठा pp_hwmgr *hwmgr,
		काष्ठा phm_tdp_table **info_tdp_table,
		स्थिर Vega10_PPTable_Generic_SubTable_Header *table)
अणु
	uपूर्णांक32_t table_size;
	काष्ठा phm_tdp_table *tdp_table;
	uपूर्णांक8_t scl;
	uपूर्णांक8_t sda;
	स्थिर ATOM_Vega10_PowerTune_Table *घातer_tune_table;
	स्थिर ATOM_Vega10_PowerTune_Table_V2 *घातer_tune_table_v2;
	स्थिर ATOM_Vega10_PowerTune_Table_V3 *घातer_tune_table_v3;

	table_size = माप(uपूर्णांक32_t) + माप(काष्ठा phm_tdp_table);

	tdp_table = kzalloc(table_size, GFP_KERNEL);

	अगर (!tdp_table)
		वापस -ENOMEM;

	अगर (table->ucRevId == 5) अणु
		घातer_tune_table = (ATOM_Vega10_PowerTune_Table *)table;
		tdp_table->usMaximumPowerDeliveryLimit = le16_to_cpu(घातer_tune_table->usSocketPowerLimit);
		tdp_table->usTDC = le16_to_cpu(घातer_tune_table->usTdcLimit);
		tdp_table->usEDCLimit = le16_to_cpu(घातer_tune_table->usEdcLimit);
		tdp_table->usSoftwareShutकरोwnTemp =
				le16_to_cpu(घातer_tune_table->usSoftwareShutकरोwnTemp);
		tdp_table->usTemperatureLimitTedge =
				le16_to_cpu(घातer_tune_table->usTemperatureLimitTedge);
		tdp_table->usTemperatureLimitHotspot =
				le16_to_cpu(घातer_tune_table->usTemperatureLimitHotSpot);
		tdp_table->usTemperatureLimitLiquid1 =
				le16_to_cpu(घातer_tune_table->usTemperatureLimitLiquid1);
		tdp_table->usTemperatureLimitLiquid2 =
				le16_to_cpu(घातer_tune_table->usTemperatureLimitLiquid2);
		tdp_table->usTemperatureLimitHBM =
				le16_to_cpu(घातer_tune_table->usTemperatureLimitHBM);
		tdp_table->usTemperatureLimitVrVddc =
				le16_to_cpu(घातer_tune_table->usTemperatureLimitVrSoc);
		tdp_table->usTemperatureLimitVrMvdd =
				le16_to_cpu(घातer_tune_table->usTemperatureLimitVrMem);
		tdp_table->usTemperatureLimitPlx =
				le16_to_cpu(घातer_tune_table->usTemperatureLimitPlx);
		tdp_table->ucLiquid1_I2C_address = घातer_tune_table->ucLiquid1_I2C_address;
		tdp_table->ucLiquid2_I2C_address = घातer_tune_table->ucLiquid2_I2C_address;
		tdp_table->ucLiquid_I2C_Line = घातer_tune_table->ucLiquid_I2C_LineSCL;
		tdp_table->ucLiquid_I2C_LineSDA = घातer_tune_table->ucLiquid_I2C_LineSDA;
		tdp_table->ucVr_I2C_address = घातer_tune_table->ucVr_I2C_address;
		tdp_table->ucVr_I2C_Line = घातer_tune_table->ucVr_I2C_LineSCL;
		tdp_table->ucVr_I2C_LineSDA = घातer_tune_table->ucVr_I2C_LineSDA;
		tdp_table->ucPlx_I2C_address = घातer_tune_table->ucPlx_I2C_address;
		tdp_table->ucPlx_I2C_Line = घातer_tune_table->ucPlx_I2C_LineSCL;
		tdp_table->ucPlx_I2C_LineSDA = घातer_tune_table->ucPlx_I2C_LineSDA;
		hwmgr->platक्रमm_descriptor.LoadLineSlope = le16_to_cpu(घातer_tune_table->usLoadLineResistance);
	पूर्ण अन्यथा अगर (table->ucRevId == 6) अणु
		घातer_tune_table_v2 = (ATOM_Vega10_PowerTune_Table_V2 *)table;
		tdp_table->usMaximumPowerDeliveryLimit = le16_to_cpu(घातer_tune_table_v2->usSocketPowerLimit);
		tdp_table->usTDC = le16_to_cpu(घातer_tune_table_v2->usTdcLimit);
		tdp_table->usEDCLimit = le16_to_cpu(घातer_tune_table_v2->usEdcLimit);
		tdp_table->usSoftwareShutकरोwnTemp =
				le16_to_cpu(घातer_tune_table_v2->usSoftwareShutकरोwnTemp);
		tdp_table->usTemperatureLimitTedge =
				le16_to_cpu(घातer_tune_table_v2->usTemperatureLimitTedge);
		tdp_table->usTemperatureLimitHotspot =
				le16_to_cpu(घातer_tune_table_v2->usTemperatureLimitHotSpot);
		tdp_table->usTemperatureLimitLiquid1 =
				le16_to_cpu(घातer_tune_table_v2->usTemperatureLimitLiquid1);
		tdp_table->usTemperatureLimitLiquid2 =
				le16_to_cpu(घातer_tune_table_v2->usTemperatureLimitLiquid2);
		tdp_table->usTemperatureLimitHBM =
				le16_to_cpu(घातer_tune_table_v2->usTemperatureLimitHBM);
		tdp_table->usTemperatureLimitVrVddc =
				le16_to_cpu(घातer_tune_table_v2->usTemperatureLimitVrSoc);
		tdp_table->usTemperatureLimitVrMvdd =
				le16_to_cpu(घातer_tune_table_v2->usTemperatureLimitVrMem);
		tdp_table->usTemperatureLimitPlx =
				le16_to_cpu(घातer_tune_table_v2->usTemperatureLimitPlx);
		tdp_table->ucLiquid1_I2C_address = घातer_tune_table_v2->ucLiquid1_I2C_address;
		tdp_table->ucLiquid2_I2C_address = घातer_tune_table_v2->ucLiquid2_I2C_address;

		get_scl_sda_value(घातer_tune_table_v2->ucLiquid_I2C_Line, &scl, &sda);

		tdp_table->ucLiquid_I2C_Line = scl;
		tdp_table->ucLiquid_I2C_LineSDA = sda;

		tdp_table->ucVr_I2C_address = घातer_tune_table_v2->ucVr_I2C_address;

		get_scl_sda_value(घातer_tune_table_v2->ucVr_I2C_Line, &scl, &sda);

		tdp_table->ucVr_I2C_Line = scl;
		tdp_table->ucVr_I2C_LineSDA = sda;
		tdp_table->ucPlx_I2C_address = घातer_tune_table_v2->ucPlx_I2C_address;

		get_scl_sda_value(घातer_tune_table_v2->ucPlx_I2C_Line, &scl, &sda);

		tdp_table->ucPlx_I2C_Line = scl;
		tdp_table->ucPlx_I2C_LineSDA = sda;

		hwmgr->platक्रमm_descriptor.LoadLineSlope =
					le16_to_cpu(घातer_tune_table_v2->usLoadLineResistance);
	पूर्ण अन्यथा अणु
		घातer_tune_table_v3 = (ATOM_Vega10_PowerTune_Table_V3 *)table;
		tdp_table->usMaximumPowerDeliveryLimit   = le16_to_cpu(घातer_tune_table_v3->usSocketPowerLimit);
		tdp_table->usTDC                         = le16_to_cpu(घातer_tune_table_v3->usTdcLimit);
		tdp_table->usEDCLimit                    = le16_to_cpu(घातer_tune_table_v3->usEdcLimit);
		tdp_table->usSoftwareShutकरोwnTemp        = le16_to_cpu(घातer_tune_table_v3->usSoftwareShutकरोwnTemp);
		tdp_table->usTemperatureLimitTedge       = le16_to_cpu(घातer_tune_table_v3->usTemperatureLimitTedge);
		tdp_table->usTemperatureLimitHotspot     = le16_to_cpu(घातer_tune_table_v3->usTemperatureLimitHotSpot);
		tdp_table->usTemperatureLimitLiquid1     = le16_to_cpu(घातer_tune_table_v3->usTemperatureLimitLiquid1);
		tdp_table->usTemperatureLimitLiquid2     = le16_to_cpu(घातer_tune_table_v3->usTemperatureLimitLiquid2);
		tdp_table->usTemperatureLimitHBM         = le16_to_cpu(घातer_tune_table_v3->usTemperatureLimitHBM);
		tdp_table->usTemperatureLimitVrVddc      = le16_to_cpu(घातer_tune_table_v3->usTemperatureLimitVrSoc);
		tdp_table->usTemperatureLimitVrMvdd      = le16_to_cpu(घातer_tune_table_v3->usTemperatureLimitVrMem);
		tdp_table->usTemperatureLimitPlx         = le16_to_cpu(घातer_tune_table_v3->usTemperatureLimitPlx);
		tdp_table->ucLiquid1_I2C_address         = घातer_tune_table_v3->ucLiquid1_I2C_address;
		tdp_table->ucLiquid2_I2C_address         = घातer_tune_table_v3->ucLiquid2_I2C_address;
		tdp_table->usBoostStartTemperature       = le16_to_cpu(घातer_tune_table_v3->usBoostStartTemperature);
		tdp_table->usBoostStopTemperature        = le16_to_cpu(घातer_tune_table_v3->usBoostStopTemperature);
		tdp_table->ulBoostClock                  = le32_to_cpu(घातer_tune_table_v3->ulBoostClock);

		get_scl_sda_value(घातer_tune_table_v3->ucLiquid_I2C_Line, &scl, &sda);

		tdp_table->ucLiquid_I2C_Line             = scl;
		tdp_table->ucLiquid_I2C_LineSDA          = sda;

		tdp_table->ucVr_I2C_address              = घातer_tune_table_v3->ucVr_I2C_address;

		get_scl_sda_value(घातer_tune_table_v3->ucVr_I2C_Line, &scl, &sda);

		tdp_table->ucVr_I2C_Line                 = scl;
		tdp_table->ucVr_I2C_LineSDA              = sda;

		tdp_table->ucPlx_I2C_address             = घातer_tune_table_v3->ucPlx_I2C_address;

		get_scl_sda_value(घातer_tune_table_v3->ucPlx_I2C_Line, &scl, &sda);

		tdp_table->ucPlx_I2C_Line                = scl;
		tdp_table->ucPlx_I2C_LineSDA             = sda;

		hwmgr->platक्रमm_descriptor.LoadLineSlope =
					le16_to_cpu(घातer_tune_table_v3->usLoadLineResistance);
	पूर्ण

	*info_tdp_table = tdp_table;

	वापस 0;
पूर्ण

अटल पूर्णांक get_socclk_voltage_dependency_table(
		काष्ठा pp_hwmgr *hwmgr,
		phm_ppt_v1_घड़ी_voltage_dependency_table **pp_vega10_clk_dep_table,
		स्थिर ATOM_Vega10_SOCCLK_Dependency_Table *clk_dep_table)
अणु
	uपूर्णांक32_t i;
	phm_ppt_v1_घड़ी_voltage_dependency_table *clk_table;

	PP_ASSERT_WITH_CODE(clk_dep_table->ucNumEntries,
		"Invalid PowerPlay Table!", वापस -1);

	clk_table = kzalloc(काष्ठा_size(clk_table, entries, clk_dep_table->ucNumEntries),
			    GFP_KERNEL);
	अगर (!clk_table)
		वापस -ENOMEM;

	clk_table->count = (uपूर्णांक32_t)clk_dep_table->ucNumEntries;

	क्रम (i = 0; i < clk_dep_table->ucNumEntries; i++) अणु
		clk_table->entries[i].vddInd =
				clk_dep_table->entries[i].ucVddInd;
		clk_table->entries[i].clk =
				le32_to_cpu(clk_dep_table->entries[i].ulClk);
	पूर्ण

	*pp_vega10_clk_dep_table = clk_table;

	वापस 0;
पूर्ण

अटल पूर्णांक get_mclk_voltage_dependency_table(
		काष्ठा pp_hwmgr *hwmgr,
		phm_ppt_v1_घड़ी_voltage_dependency_table **pp_vega10_mclk_dep_table,
		स्थिर ATOM_Vega10_MCLK_Dependency_Table *mclk_dep_table)
अणु
	uपूर्णांक32_t i;
	phm_ppt_v1_घड़ी_voltage_dependency_table *mclk_table;

	PP_ASSERT_WITH_CODE(mclk_dep_table->ucNumEntries,
		"Invalid PowerPlay Table!", वापस -1);

	mclk_table = kzalloc(काष्ठा_size(mclk_table, entries, mclk_dep_table->ucNumEntries),
			    GFP_KERNEL);
	अगर (!mclk_table)
		वापस -ENOMEM;

	mclk_table->count = (uपूर्णांक32_t)mclk_dep_table->ucNumEntries;

	क्रम (i = 0; i < mclk_dep_table->ucNumEntries; i++) अणु
		mclk_table->entries[i].vddInd =
				mclk_dep_table->entries[i].ucVddInd;
		mclk_table->entries[i].vddciInd =
				mclk_dep_table->entries[i].ucVddciInd;
		mclk_table->entries[i].mvddInd =
				mclk_dep_table->entries[i].ucVddMemInd;
		mclk_table->entries[i].clk =
				le32_to_cpu(mclk_dep_table->entries[i].ulMemClk);
	पूर्ण

	*pp_vega10_mclk_dep_table = mclk_table;

	वापस 0;
पूर्ण

अटल पूर्णांक get_gfxclk_voltage_dependency_table(
		काष्ठा pp_hwmgr *hwmgr,
		काष्ठा phm_ppt_v1_घड़ी_voltage_dependency_table
			**pp_vega10_clk_dep_table,
		स्थिर ATOM_Vega10_GFXCLK_Dependency_Table *clk_dep_table)
अणु
	uपूर्णांक32_t i;
	काष्ठा phm_ppt_v1_घड़ी_voltage_dependency_table
				*clk_table;
	ATOM_Vega10_GFXCLK_Dependency_Record_V2 *patom_record_v2;

	PP_ASSERT_WITH_CODE((clk_dep_table->ucNumEntries != 0),
			"Invalid PowerPlay Table!", वापस -1);

	clk_table = kzalloc(काष्ठा_size(clk_table, entries, clk_dep_table->ucNumEntries),
			    GFP_KERNEL);
	अगर (!clk_table)
		वापस -ENOMEM;

	clk_table->count = clk_dep_table->ucNumEntries;

	अगर (clk_dep_table->ucRevId == 0) अणु
		क्रम (i = 0; i < clk_table->count; i++) अणु
			clk_table->entries[i].vddInd =
				clk_dep_table->entries[i].ucVddInd;
			clk_table->entries[i].clk =
				le32_to_cpu(clk_dep_table->entries[i].ulClk);
			clk_table->entries[i].cks_enable =
				(((le16_to_cpu(clk_dep_table->entries[i].usCKSVOffsetandDisable) & 0x8000)
						>> 15) == 0) ? 1 : 0;
			clk_table->entries[i].cks_voffset =
				le16_to_cpu(clk_dep_table->entries[i].usCKSVOffsetandDisable) & 0x7F;
			clk_table->entries[i].sclk_offset =
				le16_to_cpu(clk_dep_table->entries[i].usAVFSOffset);
		पूर्ण
	पूर्ण अन्यथा अगर (clk_dep_table->ucRevId == 1) अणु
		patom_record_v2 = (ATOM_Vega10_GFXCLK_Dependency_Record_V2 *)clk_dep_table->entries;
		क्रम (i = 0; i < clk_table->count; i++) अणु
			clk_table->entries[i].vddInd =
					patom_record_v2->ucVddInd;
			clk_table->entries[i].clk =
					le32_to_cpu(patom_record_v2->ulClk);
			clk_table->entries[i].cks_enable =
					(((le16_to_cpu(patom_record_v2->usCKSVOffsetandDisable) & 0x8000)
							>> 15) == 0) ? 1 : 0;
			clk_table->entries[i].cks_voffset =
					le16_to_cpu(patom_record_v2->usCKSVOffsetandDisable) & 0x7F;
			clk_table->entries[i].sclk_offset =
					le16_to_cpu(patom_record_v2->usAVFSOffset);
			patom_record_v2++;
		पूर्ण
	पूर्ण अन्यथा अणु
		kमुक्त(clk_table);
		PP_ASSERT_WITH_CODE(false,
			"Unsupported GFXClockDependencyTable Revision!",
			वापस -EINVAL);
	पूर्ण

	*pp_vega10_clk_dep_table = clk_table;

	वापस 0;
पूर्ण

अटल पूर्णांक get_pix_clk_voltage_dependency_table(
		काष्ठा pp_hwmgr *hwmgr,
		काष्ठा phm_ppt_v1_घड़ी_voltage_dependency_table
			**pp_vega10_clk_dep_table,
		स्थिर  ATOM_Vega10_PIXCLK_Dependency_Table *clk_dep_table)
अणु
	uपूर्णांक32_t i;
	काष्ठा phm_ppt_v1_घड़ी_voltage_dependency_table
				*clk_table;

	PP_ASSERT_WITH_CODE((clk_dep_table->ucNumEntries != 0),
			"Invalid PowerPlay Table!", वापस -1);

	clk_table = kzalloc(काष्ठा_size(clk_table, entries, clk_dep_table->ucNumEntries),
			    GFP_KERNEL);
	अगर (!clk_table)
		वापस -ENOMEM;

	clk_table->count = clk_dep_table->ucNumEntries;

	क्रम (i = 0; i < clk_table->count; i++) अणु
		clk_table->entries[i].vddInd =
				clk_dep_table->entries[i].ucVddInd;
		clk_table->entries[i].clk =
				le32_to_cpu(clk_dep_table->entries[i].ulClk);
	पूर्ण

	*pp_vega10_clk_dep_table = clk_table;

	वापस 0;
पूर्ण

अटल पूर्णांक get_dcefclk_voltage_dependency_table(
		काष्ठा pp_hwmgr *hwmgr,
		काष्ठा phm_ppt_v1_घड़ी_voltage_dependency_table
			**pp_vega10_clk_dep_table,
		स्थिर ATOM_Vega10_DCEFCLK_Dependency_Table *clk_dep_table)
अणु
	uपूर्णांक32_t i;
	uपूर्णांक8_t num_entries;
	काष्ठा phm_ppt_v1_घड़ी_voltage_dependency_table
				*clk_table;
	uपूर्णांक32_t dev_id;
	uपूर्णांक32_t rev_id;
	काष्ठा amdgpu_device *adev = hwmgr->adev;

	PP_ASSERT_WITH_CODE((clk_dep_table->ucNumEntries != 0),
			"Invalid PowerPlay Table!", वापस -1);

/*
 * workaround needed to add another DPM level क्रम pioneer cards
 * as VBIOS is locked करोwn.
 * This DPM level was added to support 3DPM monitors @ 4K120Hz
 *
 */
	dev_id = adev->pdev->device;
	rev_id = adev->pdev->revision;

	अगर (dev_id == 0x6863 && rev_id == 0 &&
		clk_dep_table->entries[clk_dep_table->ucNumEntries - 1].ulClk < 90000)
		num_entries = clk_dep_table->ucNumEntries + 1 > NUM_DSPCLK_LEVELS ?
				NUM_DSPCLK_LEVELS : clk_dep_table->ucNumEntries + 1;
	अन्यथा
		num_entries = clk_dep_table->ucNumEntries;


	clk_table = kzalloc(काष्ठा_size(clk_table, entries, num_entries),
			    GFP_KERNEL);
	अगर (!clk_table)
		वापस -ENOMEM;

	clk_table->count = (uपूर्णांक32_t)num_entries;

	क्रम (i = 0; i < clk_dep_table->ucNumEntries; i++) अणु
		clk_table->entries[i].vddInd =
				clk_dep_table->entries[i].ucVddInd;
		clk_table->entries[i].clk =
				le32_to_cpu(clk_dep_table->entries[i].ulClk);
	पूर्ण

	अगर (i < num_entries) अणु
		clk_table->entries[i].vddInd = clk_dep_table->entries[i-1].ucVddInd;
		clk_table->entries[i].clk = 90000;
	पूर्ण

	*pp_vega10_clk_dep_table = clk_table;

	वापस 0;
पूर्ण

अटल पूर्णांक get_pcie_table(काष्ठा pp_hwmgr *hwmgr,
		काष्ठा phm_ppt_v1_pcie_table **vega10_pcie_table,
		स्थिर Vega10_PPTable_Generic_SubTable_Header *table)
अणु
	uपूर्णांक32_t i, pcie_count;
	काष्ठा phm_ppt_v1_pcie_table *pcie_table;
	काष्ठा phm_ppt_v2_inक्रमmation *table_info =
			(काष्ठा phm_ppt_v2_inक्रमmation *)(hwmgr->pptable);
	स्थिर ATOM_Vega10_PCIE_Table *atom_pcie_table =
			(ATOM_Vega10_PCIE_Table *)table;

	PP_ASSERT_WITH_CODE(atom_pcie_table->ucNumEntries,
			"Invalid PowerPlay Table!",
			वापस 0);

	pcie_table = kzalloc(काष्ठा_size(pcie_table, entries, atom_pcie_table->ucNumEntries),
			     GFP_KERNEL);
	अगर (!pcie_table)
		वापस -ENOMEM;

	pcie_count = table_info->vdd_dep_on_sclk->count;
	अगर (atom_pcie_table->ucNumEntries <= pcie_count)
		pcie_count = atom_pcie_table->ucNumEntries;
	अन्यथा
		pr_info("Number of Pcie Entries exceed the number of"
				" GFXCLK Dpm Levels!"
				" Disregarding the excess entries...\n");

	pcie_table->count = pcie_count;

	क्रम (i = 0; i < pcie_count; i++) अणु
		pcie_table->entries[i].gen_speed =
				atom_pcie_table->entries[i].ucPCIEGenSpeed;
		pcie_table->entries[i].lane_width =
				atom_pcie_table->entries[i].ucPCIELaneWidth;
		pcie_table->entries[i].pcie_sclk =
				atom_pcie_table->entries[i].ulLCLK;
	पूर्ण

	*vega10_pcie_table = pcie_table;

	वापस 0;
पूर्ण

अटल पूर्णांक get_hard_limits(
		काष्ठा pp_hwmgr *hwmgr,
		काष्ठा phm_घड़ी_and_voltage_limits *limits,
		स्थिर ATOM_Vega10_Hard_Limit_Table *limit_table)
अणु
	PP_ASSERT_WITH_CODE(limit_table->ucNumEntries,
			"Invalid PowerPlay Table!", वापस -1);

	/* currently we always take entries[0] parameters */
	limits->sclk = le32_to_cpu(limit_table->entries[0].ulSOCCLKLimit);
	limits->mclk = le32_to_cpu(limit_table->entries[0].ulMCLKLimit);
	limits->gfxclk = le32_to_cpu(limit_table->entries[0].ulGFXCLKLimit);
	limits->vddc = le16_to_cpu(limit_table->entries[0].usVddcLimit);
	limits->vddci = le16_to_cpu(limit_table->entries[0].usVddciLimit);
	limits->vddmem = le16_to_cpu(limit_table->entries[0].usVddMemLimit);

	वापस 0;
पूर्ण

अटल पूर्णांक get_valid_clk(
		काष्ठा pp_hwmgr *hwmgr,
		काष्ठा phm_घड़ी_array **clk_table,
		स्थिर phm_ppt_v1_घड़ी_voltage_dependency_table *clk_volt_pp_table)
अणु
	uपूर्णांक32_t i;
	काष्ठा phm_घड़ी_array *table;

	PP_ASSERT_WITH_CODE(clk_volt_pp_table->count,
			"Invalid PowerPlay Table!", वापस -1);

	table = kzalloc(काष्ठा_size(table, values, clk_volt_pp_table->count),
			GFP_KERNEL);
	अगर (!table)
		वापस -ENOMEM;

	table->count = (uपूर्णांक32_t)clk_volt_pp_table->count;

	क्रम (i = 0; i < table->count; i++)
		table->values[i] = (uपूर्णांक32_t)clk_volt_pp_table->entries[i].clk;

	*clk_table = table;

	वापस 0;
पूर्ण

अटल पूर्णांक init_घातerplay_extended_tables(
		काष्ठा pp_hwmgr *hwmgr,
		स्थिर ATOM_Vega10_POWERPLAYTABLE *घातerplay_table)
अणु
	पूर्णांक result = 0;
	काष्ठा phm_ppt_v2_inक्रमmation *pp_table_info =
		(काष्ठा phm_ppt_v2_inक्रमmation *)(hwmgr->pptable);

	स्थिर ATOM_Vega10_MM_Dependency_Table *mm_dependency_table =
			(स्थिर ATOM_Vega10_MM_Dependency_Table *)
			(((अचिन्हित दीर्घ) घातerplay_table) +
			le16_to_cpu(घातerplay_table->usMMDependencyTableOffset));
	स्थिर Vega10_PPTable_Generic_SubTable_Header *घातer_tune_table =
			(स्थिर Vega10_PPTable_Generic_SubTable_Header *)
			(((अचिन्हित दीर्घ) घातerplay_table) +
			le16_to_cpu(घातerplay_table->usPowerTuneTableOffset));
	स्थिर ATOM_Vega10_SOCCLK_Dependency_Table *socclk_dep_table =
			(स्थिर ATOM_Vega10_SOCCLK_Dependency_Table *)
			(((अचिन्हित दीर्घ) घातerplay_table) +
			le16_to_cpu(घातerplay_table->usSocclkDependencyTableOffset));
	स्थिर ATOM_Vega10_GFXCLK_Dependency_Table *gfxclk_dep_table =
			(स्थिर ATOM_Vega10_GFXCLK_Dependency_Table *)
			(((अचिन्हित दीर्घ) घातerplay_table) +
			le16_to_cpu(घातerplay_table->usGfxclkDependencyTableOffset));
	स्थिर ATOM_Vega10_DCEFCLK_Dependency_Table *dcefclk_dep_table =
			(स्थिर ATOM_Vega10_DCEFCLK_Dependency_Table *)
			(((अचिन्हित दीर्घ) घातerplay_table) +
			le16_to_cpu(घातerplay_table->usDcefclkDependencyTableOffset));
	स्थिर ATOM_Vega10_MCLK_Dependency_Table *mclk_dep_table =
			(स्थिर ATOM_Vega10_MCLK_Dependency_Table *)
			(((अचिन्हित दीर्घ) घातerplay_table) +
			le16_to_cpu(घातerplay_table->usMclkDependencyTableOffset));
	स्थिर ATOM_Vega10_Hard_Limit_Table *hard_limits =
			(स्थिर ATOM_Vega10_Hard_Limit_Table *)
			(((अचिन्हित दीर्घ) घातerplay_table) +
			le16_to_cpu(घातerplay_table->usHardLimitTableOffset));
	स्थिर Vega10_PPTable_Generic_SubTable_Header *pcie_table =
			(स्थिर Vega10_PPTable_Generic_SubTable_Header *)
			(((अचिन्हित दीर्घ) घातerplay_table) +
			le16_to_cpu(घातerplay_table->usPCIETableOffset));
	स्थिर ATOM_Vega10_PIXCLK_Dependency_Table *pixclk_dep_table =
			(स्थिर ATOM_Vega10_PIXCLK_Dependency_Table *)
			(((अचिन्हित दीर्घ) घातerplay_table) +
			le16_to_cpu(घातerplay_table->usPixclkDependencyTableOffset));
	स्थिर ATOM_Vega10_PHYCLK_Dependency_Table *phyclk_dep_table =
			(स्थिर ATOM_Vega10_PHYCLK_Dependency_Table *)
			(((अचिन्हित दीर्घ) घातerplay_table) +
			le16_to_cpu(घातerplay_table->usPhyClkDependencyTableOffset));
	स्थिर ATOM_Vega10_DISPCLK_Dependency_Table *dispclk_dep_table =
			(स्थिर ATOM_Vega10_DISPCLK_Dependency_Table *)
			(((अचिन्हित दीर्घ) घातerplay_table) +
			le16_to_cpu(घातerplay_table->usDispClkDependencyTableOffset));

	pp_table_info->vdd_dep_on_socclk = शून्य;
	pp_table_info->vdd_dep_on_sclk = शून्य;
	pp_table_info->vdd_dep_on_mclk = शून्य;
	pp_table_info->vdd_dep_on_dcefclk = शून्य;
	pp_table_info->mm_dep_table = शून्य;
	pp_table_info->tdp_table = शून्य;
	pp_table_info->vdd_dep_on_pixclk = शून्य;
	pp_table_info->vdd_dep_on_phyclk = शून्य;
	pp_table_info->vdd_dep_on_dispclk = शून्य;

	अगर (घातerplay_table->usMMDependencyTableOffset)
		result = get_mm_घड़ी_voltage_table(hwmgr,
				&pp_table_info->mm_dep_table,
				mm_dependency_table);

	अगर (!result && घातerplay_table->usPowerTuneTableOffset)
		result = get_tdp_table(hwmgr,
				&pp_table_info->tdp_table,
				घातer_tune_table);

	अगर (!result && घातerplay_table->usSocclkDependencyTableOffset)
		result = get_socclk_voltage_dependency_table(hwmgr,
				&pp_table_info->vdd_dep_on_socclk,
				socclk_dep_table);

	अगर (!result && घातerplay_table->usGfxclkDependencyTableOffset)
		result = get_gfxclk_voltage_dependency_table(hwmgr,
				&pp_table_info->vdd_dep_on_sclk,
				gfxclk_dep_table);

	अगर (!result && घातerplay_table->usPixclkDependencyTableOffset)
		result = get_pix_clk_voltage_dependency_table(hwmgr,
				&pp_table_info->vdd_dep_on_pixclk,
				(स्थिर ATOM_Vega10_PIXCLK_Dependency_Table*)
				pixclk_dep_table);

	अगर (!result && घातerplay_table->usPhyClkDependencyTableOffset)
		result = get_pix_clk_voltage_dependency_table(hwmgr,
				&pp_table_info->vdd_dep_on_phyclk,
				(स्थिर ATOM_Vega10_PIXCLK_Dependency_Table *)
				phyclk_dep_table);

	अगर (!result && घातerplay_table->usDispClkDependencyTableOffset)
		result = get_pix_clk_voltage_dependency_table(hwmgr,
				&pp_table_info->vdd_dep_on_dispclk,
				(स्थिर ATOM_Vega10_PIXCLK_Dependency_Table *)
				dispclk_dep_table);

	अगर (!result && घातerplay_table->usDcefclkDependencyTableOffset)
		result = get_dcefclk_voltage_dependency_table(hwmgr,
				&pp_table_info->vdd_dep_on_dcefclk,
				dcefclk_dep_table);

	अगर (!result && घातerplay_table->usMclkDependencyTableOffset)
		result = get_mclk_voltage_dependency_table(hwmgr,
				&pp_table_info->vdd_dep_on_mclk,
				mclk_dep_table);

	अगर (!result && घातerplay_table->usPCIETableOffset)
		result = get_pcie_table(hwmgr,
				&pp_table_info->pcie_table,
				pcie_table);

	अगर (!result && घातerplay_table->usHardLimitTableOffset)
		result = get_hard_limits(hwmgr,
				&pp_table_info->max_घड़ी_voltage_on_dc,
				hard_limits);

	hwmgr->dyn_state.max_घड़ी_voltage_on_dc.sclk =
			pp_table_info->max_घड़ी_voltage_on_dc.sclk;
	hwmgr->dyn_state.max_घड़ी_voltage_on_dc.mclk =
			pp_table_info->max_घड़ी_voltage_on_dc.mclk;
	hwmgr->dyn_state.max_घड़ी_voltage_on_dc.vddc =
			pp_table_info->max_घड़ी_voltage_on_dc.vddc;
	hwmgr->dyn_state.max_घड़ी_voltage_on_dc.vddci =
			pp_table_info->max_घड़ी_voltage_on_dc.vddci;

	अगर (!result &&
		pp_table_info->vdd_dep_on_socclk &&
		pp_table_info->vdd_dep_on_socclk->count)
		result = get_valid_clk(hwmgr,
				&pp_table_info->valid_socclk_values,
				pp_table_info->vdd_dep_on_socclk);

	अगर (!result &&
		pp_table_info->vdd_dep_on_sclk &&
		pp_table_info->vdd_dep_on_sclk->count)
		result = get_valid_clk(hwmgr,
				&pp_table_info->valid_sclk_values,
				pp_table_info->vdd_dep_on_sclk);

	अगर (!result &&
		pp_table_info->vdd_dep_on_dcefclk &&
		pp_table_info->vdd_dep_on_dcefclk->count)
		result = get_valid_clk(hwmgr,
				&pp_table_info->valid_dcefclk_values,
				pp_table_info->vdd_dep_on_dcefclk);

	अगर (!result &&
		pp_table_info->vdd_dep_on_mclk &&
		pp_table_info->vdd_dep_on_mclk->count)
		result = get_valid_clk(hwmgr,
				&pp_table_info->valid_mclk_values,
				pp_table_info->vdd_dep_on_mclk);

	वापस result;
पूर्ण

अटल पूर्णांक get_vddc_lookup_table(
		काष्ठा pp_hwmgr	*hwmgr,
		phm_ppt_v1_voltage_lookup_table	**lookup_table,
		स्थिर ATOM_Vega10_Voltage_Lookup_Table *vddc_lookup_pp_tables,
		uपूर्णांक32_t max_levels)
अणु
	uपूर्णांक32_t i;
	phm_ppt_v1_voltage_lookup_table *table;

	PP_ASSERT_WITH_CODE((vddc_lookup_pp_tables->ucNumEntries != 0),
			"Invalid SOC_VDDD Lookup Table!", वापस 1);

	table = kzalloc(काष्ठा_size(table, entries, max_levels), GFP_KERNEL);
	अगर (!table)
		वापस -ENOMEM;

	table->count = vddc_lookup_pp_tables->ucNumEntries;

	क्रम (i = 0; i < vddc_lookup_pp_tables->ucNumEntries; i++)
		table->entries[i].us_vdd =
				le16_to_cpu(vddc_lookup_pp_tables->entries[i].usVdd);

	*lookup_table = table;

	वापस 0;
पूर्ण

अटल पूर्णांक init_dpm_2_parameters(
		काष्ठा pp_hwmgr *hwmgr,
		स्थिर ATOM_Vega10_POWERPLAYTABLE *घातerplay_table)
अणु
	पूर्णांक result = 0;
	काष्ठा phm_ppt_v2_inक्रमmation *pp_table_info =
			(काष्ठा phm_ppt_v2_inक्रमmation *)(hwmgr->pptable);
	uपूर्णांक32_t disable_घातer_control = 0;

	pp_table_info->us_ulv_voltage_offset =
		le16_to_cpu(घातerplay_table->usUlvVoltageOffset);

	pp_table_info->us_ulv_smnclk_did =
			le16_to_cpu(घातerplay_table->usUlvSmnclkDid);
	pp_table_info->us_ulv_mp1clk_did =
			le16_to_cpu(घातerplay_table->usUlvMp1clkDid);
	pp_table_info->us_ulv_gfxclk_bypass =
			le16_to_cpu(घातerplay_table->usUlvGfxclkBypass);
	pp_table_info->us_gfxclk_slew_rate =
			le16_to_cpu(घातerplay_table->usGfxclkSlewRate);
	pp_table_info->uc_gfx_dpm_voltage_mode  =
			le16_to_cpu(घातerplay_table->ucGfxVoltageMode);
	pp_table_info->uc_soc_dpm_voltage_mode  =
			le16_to_cpu(घातerplay_table->ucSocVoltageMode);
	pp_table_info->uc_uclk_dpm_voltage_mode =
			le16_to_cpu(घातerplay_table->ucUclkVoltageMode);
	pp_table_info->uc_uvd_dpm_voltage_mode  =
			le16_to_cpu(घातerplay_table->ucUvdVoltageMode);
	pp_table_info->uc_vce_dpm_voltage_mode  =
			le16_to_cpu(घातerplay_table->ucVceVoltageMode);
	pp_table_info->uc_mp0_dpm_voltage_mode  =
			le16_to_cpu(घातerplay_table->ucMp0VoltageMode);
	pp_table_info->uc_dcef_dpm_voltage_mode =
			le16_to_cpu(घातerplay_table->ucDcefVoltageMode);

	pp_table_info->ppm_parameter_table = शून्य;
	pp_table_info->vddc_lookup_table = शून्य;
	pp_table_info->vddmem_lookup_table = शून्य;
	pp_table_info->vddci_lookup_table = शून्य;

	/* TDP limits */
	hwmgr->platक्रमm_descriptor.TDPODLimit =
		le16_to_cpu(घातerplay_table->usPowerControlLimit);
	hwmgr->platक्रमm_descriptor.TDPAdjusपंचांगent = 0;
	hwmgr->platक्रमm_descriptor.VidAdjusपंचांगent = 0;
	hwmgr->platक्रमm_descriptor.VidAdjusपंचांगentPolarity = 0;
	hwmgr->platक्रमm_descriptor.VidMinLimit = 0;
	hwmgr->platक्रमm_descriptor.VidMaxLimit = 1500000;
	hwmgr->platक्रमm_descriptor.VidStep = 6250;

	disable_घातer_control = 0;
	अगर (!disable_घातer_control) अणु
		/* enable TDP overdrive (PowerControl) feature as well अगर supported */
		अगर (hwmgr->platक्रमm_descriptor.TDPODLimit)
			phm_cap_set(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
			PHM_Platक्रमmCaps_PowerControl);
	पूर्ण

	अगर (घातerplay_table->usVddcLookupTableOffset) अणु
		स्थिर ATOM_Vega10_Voltage_Lookup_Table *vddc_table =
				(ATOM_Vega10_Voltage_Lookup_Table *)
				(((अचिन्हित दीर्घ)घातerplay_table) +
				le16_to_cpu(घातerplay_table->usVddcLookupTableOffset));
		result = get_vddc_lookup_table(hwmgr,
				&pp_table_info->vddc_lookup_table, vddc_table, 8);
	पूर्ण

	अगर (घातerplay_table->usVddmemLookupTableOffset) अणु
		स्थिर ATOM_Vega10_Voltage_Lookup_Table *vdd_mem_table =
				(ATOM_Vega10_Voltage_Lookup_Table *)
				(((अचिन्हित दीर्घ)घातerplay_table) +
				le16_to_cpu(घातerplay_table->usVddmemLookupTableOffset));
		result = get_vddc_lookup_table(hwmgr,
				&pp_table_info->vddmem_lookup_table, vdd_mem_table, 4);
	पूर्ण

	अगर (घातerplay_table->usVddciLookupTableOffset) अणु
		स्थिर ATOM_Vega10_Voltage_Lookup_Table *vddci_table =
				(ATOM_Vega10_Voltage_Lookup_Table *)
				(((अचिन्हित दीर्घ)घातerplay_table) +
				le16_to_cpu(घातerplay_table->usVddciLookupTableOffset));
		result = get_vddc_lookup_table(hwmgr,
				&pp_table_info->vddci_lookup_table, vddci_table, 4);
	पूर्ण

	वापस result;
पूर्ण

अटल पूर्णांक vega10_pp_tables_initialize(काष्ठा pp_hwmgr *hwmgr)
अणु
	पूर्णांक result = 0;
	स्थिर ATOM_Vega10_POWERPLAYTABLE *घातerplay_table;

	hwmgr->pptable = kzalloc(माप(काष्ठा phm_ppt_v2_inक्रमmation), GFP_KERNEL);

	PP_ASSERT_WITH_CODE((hwmgr->pptable != शून्य),
			    "Failed to allocate hwmgr->pptable!", वापस -ENOMEM);

	घातerplay_table = get_घातerplay_table(hwmgr);

	PP_ASSERT_WITH_CODE((घातerplay_table != शून्य),
		"Missing PowerPlay Table!", वापस -1);

	result = check_घातerplay_tables(hwmgr, घातerplay_table);

	PP_ASSERT_WITH_CODE((result == 0),
			    "check_powerplay_tables failed", वापस result);

	result = set_platक्रमm_caps(hwmgr,
				   le32_to_cpu(घातerplay_table->ulPlatक्रमmCaps));

	PP_ASSERT_WITH_CODE((result == 0),
			    "set_platform_caps failed", वापस result);

	result = init_thermal_controller(hwmgr, घातerplay_table);

	PP_ASSERT_WITH_CODE((result == 0),
			    "init_thermal_controller failed", वापस result);

	result = init_over_drive_limits(hwmgr, घातerplay_table);

	PP_ASSERT_WITH_CODE((result == 0),
			    "init_over_drive_limits failed", वापस result);

	result = init_घातerplay_extended_tables(hwmgr, घातerplay_table);

	PP_ASSERT_WITH_CODE((result == 0),
			    "init_powerplay_extended_tables failed", वापस result);

	result = init_dpm_2_parameters(hwmgr, घातerplay_table);

	PP_ASSERT_WITH_CODE((result == 0),
			    "init_dpm_2_parameters failed", वापस result);

	वापस result;
पूर्ण

अटल पूर्णांक vega10_pp_tables_uninitialize(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा phm_ppt_v2_inक्रमmation *pp_table_info =
			(काष्ठा phm_ppt_v2_inक्रमmation *)(hwmgr->pptable);

	kमुक्त(pp_table_info->vdd_dep_on_sclk);
	pp_table_info->vdd_dep_on_sclk = शून्य;

	kमुक्त(pp_table_info->vdd_dep_on_mclk);
	pp_table_info->vdd_dep_on_mclk = शून्य;

	kमुक्त(pp_table_info->valid_mclk_values);
	pp_table_info->valid_mclk_values = शून्य;

	kमुक्त(pp_table_info->valid_sclk_values);
	pp_table_info->valid_sclk_values = शून्य;

	kमुक्त(pp_table_info->vddc_lookup_table);
	pp_table_info->vddc_lookup_table = शून्य;

	kमुक्त(pp_table_info->vddmem_lookup_table);
	pp_table_info->vddmem_lookup_table = शून्य;

	kमुक्त(pp_table_info->vddci_lookup_table);
	pp_table_info->vddci_lookup_table = शून्य;

	kमुक्त(pp_table_info->ppm_parameter_table);
	pp_table_info->ppm_parameter_table = शून्य;

	kमुक्त(pp_table_info->mm_dep_table);
	pp_table_info->mm_dep_table = शून्य;

	kमुक्त(pp_table_info->cac_dtp_table);
	pp_table_info->cac_dtp_table = शून्य;

	kमुक्त(hwmgr->dyn_state.cac_dtp_table);
	hwmgr->dyn_state.cac_dtp_table = शून्य;

	kमुक्त(pp_table_info->tdp_table);
	pp_table_info->tdp_table = शून्य;

	kमुक्त(hwmgr->pptable);
	hwmgr->pptable = शून्य;

	वापस 0;
पूर्ण

स्थिर काष्ठा pp_table_func vega10_pptable_funcs = अणु
	.pptable_init = vega10_pp_tables_initialize,
	.pptable_fini = vega10_pp_tables_uninitialize,
पूर्ण;

पूर्णांक vega10_get_number_of_घातerplay_table_entries(काष्ठा pp_hwmgr *hwmgr)
अणु
	स्थिर ATOM_Vega10_State_Array *state_arrays;
	स्थिर ATOM_Vega10_POWERPLAYTABLE *pp_table = get_घातerplay_table(hwmgr);

	PP_ASSERT_WITH_CODE((pp_table != शून्य),
			"Missing PowerPlay Table!", वापस -1);
	PP_ASSERT_WITH_CODE((pp_table->sHeader.क्रमmat_revision >=
			ATOM_Vega10_TABLE_REVISION_VEGA10),
			"Incorrect PowerPlay table revision!", वापस -1);

	state_arrays = (ATOM_Vega10_State_Array *)(((अचिन्हित दीर्घ)pp_table) +
			le16_to_cpu(pp_table->usStateArrayOffset));

	वापस (uपूर्णांक32_t)(state_arrays->ucNumEntries);
पूर्ण

अटल uपूर्णांक32_t make_classअगरication_flags(काष्ठा pp_hwmgr *hwmgr,
		uपूर्णांक16_t classअगरication, uपूर्णांक16_t classअगरication2)
अणु
	uपूर्णांक32_t result = 0;

	अगर (classअगरication & ATOM_PPLIB_CLASSIFICATION_BOOT)
		result |= PP_StateClassअगरicationFlag_Boot;

	अगर (classअगरication & ATOM_PPLIB_CLASSIFICATION_THERMAL)
		result |= PP_StateClassअगरicationFlag_Thermal;

	अगर (classअगरication & ATOM_PPLIB_CLASSIFICATION_LIMITEDPOWERSOURCE)
		result |= PP_StateClassअगरicationFlag_LimitedPowerSource;

	अगर (classअगरication & ATOM_PPLIB_CLASSIFICATION_REST)
		result |= PP_StateClassअगरicationFlag_Rest;

	अगर (classअगरication & ATOM_PPLIB_CLASSIFICATION_FORCED)
		result |= PP_StateClassअगरicationFlag_Forced;

	अगर (classअगरication & ATOM_PPLIB_CLASSIFICATION_ACPI)
		result |= PP_StateClassअगरicationFlag_ACPI;

	अगर (classअगरication2 & ATOM_PPLIB_CLASSIFICATION2_LIMITEDPOWERSOURCE_2)
		result |= PP_StateClassअगरicationFlag_LimitedPowerSource_2;

	वापस result;
पूर्ण

पूर्णांक vega10_get_घातerplay_table_entry(काष्ठा pp_hwmgr *hwmgr,
		uपूर्णांक32_t entry_index, काष्ठा pp_घातer_state *घातer_state,
		पूर्णांक (*call_back_func)(काष्ठा pp_hwmgr *, व्योम *,
				काष्ठा pp_घातer_state *, व्योम *, uपूर्णांक32_t))
अणु
	पूर्णांक result = 0;
	स्थिर ATOM_Vega10_State_Array *state_arrays;
	स्थिर ATOM_Vega10_State *state_entry;
	स्थिर ATOM_Vega10_POWERPLAYTABLE *pp_table =
			get_घातerplay_table(hwmgr);

	PP_ASSERT_WITH_CODE(pp_table, "Missing PowerPlay Table!",
			वापस -1;);
	घातer_state->classअगरication.bios_index = entry_index;

	अगर (pp_table->sHeader.क्रमmat_revision >=
			ATOM_Vega10_TABLE_REVISION_VEGA10) अणु
		state_arrays = (ATOM_Vega10_State_Array *)
				(((अचिन्हित दीर्घ)pp_table) +
				le16_to_cpu(pp_table->usStateArrayOffset));

		PP_ASSERT_WITH_CODE(pp_table->usStateArrayOffset > 0,
				"Invalid PowerPlay Table State Array Offset.",
				वापस -1);
		PP_ASSERT_WITH_CODE(state_arrays->ucNumEntries > 0,
				"Invalid PowerPlay Table State Array.",
				वापस -1);
		PP_ASSERT_WITH_CODE((entry_index <= state_arrays->ucNumEntries),
				"Invalid PowerPlay Table State Array Entry.",
				वापस -1);

		state_entry = &(state_arrays->states[entry_index]);

		result = call_back_func(hwmgr, (व्योम *)state_entry, घातer_state,
				(व्योम *)pp_table,
				make_classअगरication_flags(hwmgr,
					le16_to_cpu(state_entry->usClassअगरication),
					le16_to_cpu(state_entry->usClassअगरication2)));
	पूर्ण

	अगर (!result && (घातer_state->classअगरication.flags &
			PP_StateClassअगरicationFlag_Boot))
		result = hwmgr->hwmgr_func->patch_boot_state(hwmgr, &(घातer_state->hardware));

	वापस result;
पूर्ण

पूर्णांक vega10_baco_set_cap(काष्ठा pp_hwmgr *hwmgr)
अणु
	पूर्णांक result = 0;

	स्थिर ATOM_Vega10_POWERPLAYTABLE *घातerplay_table;

	घातerplay_table = get_घातerplay_table(hwmgr);

	PP_ASSERT_WITH_CODE((घातerplay_table != शून्य),
		"Missing PowerPlay Table!", वापस -1);

	result = check_घातerplay_tables(hwmgr, घातerplay_table);

	PP_ASSERT_WITH_CODE((result == 0),
			    "check_powerplay_tables failed", वापस result);

	set_hw_cap(
			hwmgr,
			0 != (le32_to_cpu(घातerplay_table->ulPlatक्रमmCaps) & ATOM_VEGA10_PP_PLATFORM_CAP_BACO),
			PHM_Platक्रमmCaps_BACO);
	वापस result;
पूर्ण

