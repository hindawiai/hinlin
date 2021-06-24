<शैली गुरु>
/*
 * Copyright 2018 Advanced Micro Devices, Inc.
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

#समावेश <linux/pci.h>
#समावेश <linux/reboot.h>

#समावेश "hwmgr.h"
#समावेश "pp_debug.h"
#समावेश "ppatomctrl.h"
#समावेश "ppsmc.h"
#समावेश "atom.h"
#समावेश "ivsrcid/thm/irqsrcs_thm_9_0.h"
#समावेश "ivsrcid/smuio/irqsrcs_smuio_9_0.h"
#समावेश "ivsrcid/ivsrcid_vislands30.h"

uपूर्णांक8_t convert_to_vid(uपूर्णांक16_t vddc)
अणु
	वापस (uपूर्णांक8_t) ((6200 - (vddc * VOLTAGE_SCALE)) / 25);
पूर्ण

uपूर्णांक16_t convert_to_vddc(uपूर्णांक8_t vid)
अणु
	वापस (uपूर्णांक16_t) ((6200 - (vid * 25)) / VOLTAGE_SCALE);
पूर्ण

पूर्णांक phm_copy_घड़ी_limits_array(
	काष्ठा pp_hwmgr *hwmgr,
	uपूर्णांक32_t **pptable_info_array,
	स्थिर uपूर्णांक32_t *pptable_array,
	uपूर्णांक32_t घातer_saving_घड़ी_count)
अणु
	uपूर्णांक32_t array_size, i;
	uपूर्णांक32_t *table;

	array_size = माप(uपूर्णांक32_t) * घातer_saving_घड़ी_count;
	table = kzalloc(array_size, GFP_KERNEL);
	अगर (शून्य == table)
		वापस -ENOMEM;

	क्रम (i = 0; i < घातer_saving_घड़ी_count; i++)
		table[i] = le32_to_cpu(pptable_array[i]);

	*pptable_info_array = table;

	वापस 0;
पूर्ण

पूर्णांक phm_copy_overdrive_settings_limits_array(
	काष्ठा pp_hwmgr *hwmgr,
	uपूर्णांक32_t **pptable_info_array,
	स्थिर uपूर्णांक32_t *pptable_array,
	uपूर्णांक32_t od_setting_count)
अणु
	uपूर्णांक32_t array_size, i;
	uपूर्णांक32_t *table;

	array_size = माप(uपूर्णांक32_t) * od_setting_count;
	table = kzalloc(array_size, GFP_KERNEL);
	अगर (शून्य == table)
		वापस -ENOMEM;

	क्रम (i = 0; i < od_setting_count; i++)
		table[i] = le32_to_cpu(pptable_array[i]);

	*pptable_info_array = table;

	वापस 0;
पूर्ण

uपूर्णांक32_t phm_set_field_to_u32(u32 offset, u32 original_data, u32 field, u32 size)
अणु
	u32 mask = 0;
	u32 shअगरt = 0;

	shअगरt = (offset % 4) << 3;
	अगर (size == माप(uपूर्णांक8_t))
		mask = 0xFF << shअगरt;
	अन्यथा अगर (size == माप(uपूर्णांक16_t))
		mask = 0xFFFF << shअगरt;

	original_data &= ~mask;
	original_data |= (field << shअगरt);
	वापस original_data;
पूर्ण

/*
 * Returns once the part of the रेजिस्टर indicated by the mask has
 * reached the given value.
 */
पूर्णांक phm_रुको_on_रेजिस्टर(काष्ठा pp_hwmgr *hwmgr, uपूर्णांक32_t index,
			 uपूर्णांक32_t value, uपूर्णांक32_t mask)
अणु
	uपूर्णांक32_t i;
	uपूर्णांक32_t cur_value;

	अगर (hwmgr == शून्य || hwmgr->device == शून्य) अणु
		pr_err("Invalid Hardware Manager!");
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 0; i < hwmgr->usec_समयout; i++) अणु
		cur_value = cgs_पढ़ो_रेजिस्टर(hwmgr->device, index);
		अगर ((cur_value & mask) == (value & mask))
			अवरोध;
		udelay(1);
	पूर्ण

	/* समयout means wrong logic*/
	अगर (i == hwmgr->usec_समयout)
		वापस -1;
	वापस 0;
पूर्ण


/*
 * Returns once the part of the रेजिस्टर indicated by the mask has
 * reached the given value.The indirect space is described by giving
 * the memory-mapped index of the indirect index रेजिस्टर.
 */
पूर्णांक phm_रुको_on_indirect_रेजिस्टर(काष्ठा pp_hwmgr *hwmgr,
				uपूर्णांक32_t indirect_port,
				uपूर्णांक32_t index,
				uपूर्णांक32_t value,
				uपूर्णांक32_t mask)
अणु
	अगर (hwmgr == शून्य || hwmgr->device == शून्य) अणु
		pr_err("Invalid Hardware Manager!");
		वापस -EINVAL;
	पूर्ण

	cgs_ग_लिखो_रेजिस्टर(hwmgr->device, indirect_port, index);
	वापस phm_रुको_on_रेजिस्टर(hwmgr, indirect_port + 1, mask, value);
पूर्ण

पूर्णांक phm_रुको_क्रम_रेजिस्टर_unequal(काष्ठा pp_hwmgr *hwmgr,
					uपूर्णांक32_t index,
					uपूर्णांक32_t value, uपूर्णांक32_t mask)
अणु
	uपूर्णांक32_t i;
	uपूर्णांक32_t cur_value;

	अगर (hwmgr == शून्य || hwmgr->device == शून्य)
		वापस -EINVAL;

	क्रम (i = 0; i < hwmgr->usec_समयout; i++) अणु
		cur_value = cgs_पढ़ो_रेजिस्टर(hwmgr->device,
									index);
		अगर ((cur_value & mask) != (value & mask))
			अवरोध;
		udelay(1);
	पूर्ण

	/* समयout means wrong logic */
	अगर (i == hwmgr->usec_समयout)
		वापस -ETIME;
	वापस 0;
पूर्ण

पूर्णांक phm_रुको_क्रम_indirect_रेजिस्टर_unequal(काष्ठा pp_hwmgr *hwmgr,
						uपूर्णांक32_t indirect_port,
						uपूर्णांक32_t index,
						uपूर्णांक32_t value,
						uपूर्णांक32_t mask)
अणु
	अगर (hwmgr == शून्य || hwmgr->device == शून्य)
		वापस -EINVAL;

	cgs_ग_लिखो_रेजिस्टर(hwmgr->device, indirect_port, index);
	वापस phm_रुको_क्रम_रेजिस्टर_unequal(hwmgr, indirect_port + 1,
						value, mask);
पूर्ण

bool phm_cf_want_uvd_घातer_gating(काष्ठा pp_hwmgr *hwmgr)
अणु
	वापस phm_cap_enabled(hwmgr->platक्रमm_descriptor.platक्रमmCaps, PHM_Platक्रमmCaps_UVDPowerGating);
पूर्ण

bool phm_cf_want_vce_घातer_gating(काष्ठा pp_hwmgr *hwmgr)
अणु
	वापस phm_cap_enabled(hwmgr->platक्रमm_descriptor.platक्रमmCaps, PHM_Platक्रमmCaps_VCEPowerGating);
पूर्ण


पूर्णांक phm_trim_voltage_table(काष्ठा pp_atomctrl_voltage_table *vol_table)
अणु
	uपूर्णांक32_t i, j;
	uपूर्णांक16_t vvalue;
	bool found = false;
	काष्ठा pp_atomctrl_voltage_table *table;

	PP_ASSERT_WITH_CODE((शून्य != vol_table),
			"Voltage Table empty.", वापस -EINVAL);

	table = kzalloc(माप(काष्ठा pp_atomctrl_voltage_table),
			GFP_KERNEL);

	अगर (शून्य == table)
		वापस -EINVAL;

	table->mask_low = vol_table->mask_low;
	table->phase_delay = vol_table->phase_delay;

	क्रम (i = 0; i < vol_table->count; i++) अणु
		vvalue = vol_table->entries[i].value;
		found = false;

		क्रम (j = 0; j < table->count; j++) अणु
			अगर (vvalue == table->entries[j].value) अणु
				found = true;
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (!found) अणु
			table->entries[table->count].value = vvalue;
			table->entries[table->count].smio_low =
					vol_table->entries[i].smio_low;
			table->count++;
		पूर्ण
	पूर्ण

	स_नकल(vol_table, table, माप(काष्ठा pp_atomctrl_voltage_table));
	kमुक्त(table);
	table = शून्य;
	वापस 0;
पूर्ण

पूर्णांक phm_get_svi2_mvdd_voltage_table(काष्ठा pp_atomctrl_voltage_table *vol_table,
		phm_ppt_v1_घड़ी_voltage_dependency_table *dep_table)
अणु
	uपूर्णांक32_t i;
	पूर्णांक result;

	PP_ASSERT_WITH_CODE((0 != dep_table->count),
			"Voltage Dependency Table empty.", वापस -EINVAL);

	PP_ASSERT_WITH_CODE((शून्य != vol_table),
			"vol_table empty.", वापस -EINVAL);

	vol_table->mask_low = 0;
	vol_table->phase_delay = 0;
	vol_table->count = dep_table->count;

	क्रम (i = 0; i < dep_table->count; i++) अणु
		vol_table->entries[i].value = dep_table->entries[i].mvdd;
		vol_table->entries[i].smio_low = 0;
	पूर्ण

	result = phm_trim_voltage_table(vol_table);
	PP_ASSERT_WITH_CODE((0 == result),
			"Failed to trim MVDD table.", वापस result);

	वापस 0;
पूर्ण

पूर्णांक phm_get_svi2_vddci_voltage_table(काष्ठा pp_atomctrl_voltage_table *vol_table,
		phm_ppt_v1_घड़ी_voltage_dependency_table *dep_table)
अणु
	uपूर्णांक32_t i;
	पूर्णांक result;

	PP_ASSERT_WITH_CODE((0 != dep_table->count),
			"Voltage Dependency Table empty.", वापस -EINVAL);

	PP_ASSERT_WITH_CODE((शून्य != vol_table),
			"vol_table empty.", वापस -EINVAL);

	vol_table->mask_low = 0;
	vol_table->phase_delay = 0;
	vol_table->count = dep_table->count;

	क्रम (i = 0; i < dep_table->count; i++) अणु
		vol_table->entries[i].value = dep_table->entries[i].vddci;
		vol_table->entries[i].smio_low = 0;
	पूर्ण

	result = phm_trim_voltage_table(vol_table);
	PP_ASSERT_WITH_CODE((0 == result),
			"Failed to trim VDDCI table.", वापस result);

	वापस 0;
पूर्ण

पूर्णांक phm_get_svi2_vdd_voltage_table(काष्ठा pp_atomctrl_voltage_table *vol_table,
		phm_ppt_v1_voltage_lookup_table *lookup_table)
अणु
	पूर्णांक i = 0;

	PP_ASSERT_WITH_CODE((0 != lookup_table->count),
			"Voltage Lookup Table empty.", वापस -EINVAL);

	PP_ASSERT_WITH_CODE((शून्य != vol_table),
			"vol_table empty.", वापस -EINVAL);

	vol_table->mask_low = 0;
	vol_table->phase_delay = 0;

	vol_table->count = lookup_table->count;

	क्रम (i = 0; i < vol_table->count; i++) अणु
		vol_table->entries[i].value = lookup_table->entries[i].us_vdd;
		vol_table->entries[i].smio_low = 0;
	पूर्ण

	वापस 0;
पूर्ण

व्योम phm_trim_voltage_table_to_fit_state_table(uपूर्णांक32_t max_vol_steps,
				काष्ठा pp_atomctrl_voltage_table *vol_table)
अणु
	अचिन्हित पूर्णांक i, dअगरf;

	अगर (vol_table->count <= max_vol_steps)
		वापस;

	dअगरf = vol_table->count - max_vol_steps;

	क्रम (i = 0; i < max_vol_steps; i++)
		vol_table->entries[i] = vol_table->entries[i + dअगरf];

	vol_table->count = max_vol_steps;

	वापस;
पूर्ण

पूर्णांक phm_reset_single_dpm_table(व्योम *table,
				uपूर्णांक32_t count, पूर्णांक max)
अणु
	पूर्णांक i;

	काष्ठा vi_dpm_table *dpm_table = (काष्ठा vi_dpm_table *)table;

	dpm_table->count = count > max ? max : count;

	क्रम (i = 0; i < dpm_table->count; i++)
		dpm_table->dpm_level[i].enabled = false;

	वापस 0;
पूर्ण

व्योम phm_setup_pcie_table_entry(
	व्योम *table,
	uपूर्णांक32_t index, uपूर्णांक32_t pcie_gen,
	uपूर्णांक32_t pcie_lanes)
अणु
	काष्ठा vi_dpm_table *dpm_table = (काष्ठा vi_dpm_table *)table;
	dpm_table->dpm_level[index].value = pcie_gen;
	dpm_table->dpm_level[index].param1 = pcie_lanes;
	dpm_table->dpm_level[index].enabled = 1;
पूर्ण

पूर्णांक32_t phm_get_dpm_level_enable_mask_value(व्योम *table)
अणु
	पूर्णांक32_t i;
	पूर्णांक32_t mask = 0;
	काष्ठा vi_dpm_table *dpm_table = (काष्ठा vi_dpm_table *)table;

	क्रम (i = dpm_table->count; i > 0; i--) अणु
		mask = mask << 1;
		अगर (dpm_table->dpm_level[i - 1].enabled)
			mask |= 0x1;
		अन्यथा
			mask &= 0xFFFFFFFE;
	पूर्ण

	वापस mask;
पूर्ण

uपूर्णांक8_t phm_get_voltage_index(
		काष्ठा phm_ppt_v1_voltage_lookup_table *lookup_table, uपूर्णांक16_t voltage)
अणु
	uपूर्णांक8_t count = (uपूर्णांक8_t) (lookup_table->count);
	uपूर्णांक8_t i;

	PP_ASSERT_WITH_CODE((शून्य != lookup_table),
			"Lookup Table empty.", वापस 0);
	PP_ASSERT_WITH_CODE((0 != count),
			"Lookup Table empty.", वापस 0);

	क्रम (i = 0; i < lookup_table->count; i++) अणु
		/* find first voltage equal or bigger than requested */
		अगर (lookup_table->entries[i].us_vdd >= voltage)
			वापस i;
	पूर्ण
	/* voltage is bigger than max voltage in the table */
	वापस i - 1;
पूर्ण

uपूर्णांक8_t phm_get_voltage_id(pp_atomctrl_voltage_table *voltage_table,
		uपूर्णांक32_t voltage)
अणु
	uपूर्णांक8_t count = (uपूर्णांक8_t) (voltage_table->count);
	uपूर्णांक8_t i = 0;

	PP_ASSERT_WITH_CODE((शून्य != voltage_table),
		"Voltage Table empty.", वापस 0;);
	PP_ASSERT_WITH_CODE((0 != count),
		"Voltage Table empty.", वापस 0;);

	क्रम (i = 0; i < count; i++) अणु
		/* find first voltage bigger than requested */
		अगर (voltage_table->entries[i].value >= voltage)
			वापस i;
	पूर्ण

	/* voltage is bigger than max voltage in the table */
	वापस i - 1;
पूर्ण

uपूर्णांक16_t phm_find_बंदst_vddci(काष्ठा pp_atomctrl_voltage_table *vddci_table, uपूर्णांक16_t vddci)
अणु
	uपूर्णांक32_t  i;

	क्रम (i = 0; i < vddci_table->count; i++) अणु
		अगर (vddci_table->entries[i].value >= vddci)
			वापस vddci_table->entries[i].value;
	पूर्ण

	pr_debug("vddci is larger than max value in vddci_table\n");
	वापस vddci_table->entries[i-1].value;
पूर्ण

पूर्णांक phm_find_boot_level(व्योम *table,
		uपूर्णांक32_t value, uपूर्णांक32_t *boot_level)
अणु
	पूर्णांक result = -EINVAL;
	uपूर्णांक32_t i;
	काष्ठा vi_dpm_table *dpm_table = (काष्ठा vi_dpm_table *)table;

	क्रम (i = 0; i < dpm_table->count; i++) अणु
		अगर (value == dpm_table->dpm_level[i].value) अणु
			*boot_level = i;
			result = 0;
		पूर्ण
	पूर्ण

	वापस result;
पूर्ण

पूर्णांक phm_get_sclk_क्रम_voltage_evv(काष्ठा pp_hwmgr *hwmgr,
	phm_ppt_v1_voltage_lookup_table *lookup_table,
	uपूर्णांक16_t भव_voltage_id, पूर्णांक32_t *sclk)
अणु
	uपूर्णांक8_t entry_id;
	uपूर्णांक8_t voltage_id;
	काष्ठा phm_ppt_v1_inक्रमmation *table_info =
			(काष्ठा phm_ppt_v1_inक्रमmation *)(hwmgr->pptable);

	PP_ASSERT_WITH_CODE(lookup_table->count != 0, "Lookup table is empty", वापस -EINVAL);

	/* search क्रम leakage voltage ID 0xff01 ~ 0xff08 and sckl */
	क्रम (entry_id = 0; entry_id < table_info->vdd_dep_on_sclk->count; entry_id++) अणु
		voltage_id = table_info->vdd_dep_on_sclk->entries[entry_id].vddInd;
		अगर (lookup_table->entries[voltage_id].us_vdd == भव_voltage_id)
			अवरोध;
	पूर्ण

	अगर (entry_id >= table_info->vdd_dep_on_sclk->count) अणु
		pr_debug("Can't find requested voltage id in vdd_dep_on_sclk table\n");
		वापस -EINVAL;
	पूर्ण

	*sclk = table_info->vdd_dep_on_sclk->entries[entry_id].clk;

	वापस 0;
पूर्ण

/**
 * phm_initializa_dynamic_state_adjusपंचांगent_rule_settings - Initialize Dynamic State Adjusपंचांगent Rule Settings
 *
 * @hwmgr:  the address of the घातerplay hardware manager.
 */
पूर्णांक phm_initializa_dynamic_state_adjusपंचांगent_rule_settings(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा phm_घड़ी_voltage_dependency_table *table_clk_vlt;
	काष्ठा phm_ppt_v1_inक्रमmation *pptable_info = (काष्ठा phm_ppt_v1_inक्रमmation *)(hwmgr->pptable);

	/* initialize vddc_dep_on_dal_pwrl table */
	table_clk_vlt = kzalloc(काष्ठा_size(table_clk_vlt, entries, 4),
				GFP_KERNEL);

	अगर (शून्य == table_clk_vlt) अणु
		pr_err("Can not allocate space for vddc_dep_on_dal_pwrl! \n");
		वापस -ENOMEM;
	पूर्ण अन्यथा अणु
		table_clk_vlt->count = 4;
		table_clk_vlt->entries[0].clk = PP_DAL_POWERLEVEL_ULTRALOW;
		अगर (hwmgr->chip_id >= CHIP_POLARIS10 &&
		    hwmgr->chip_id <= CHIP_VEGAM)
			table_clk_vlt->entries[0].v = 700;
		अन्यथा
			table_clk_vlt->entries[0].v = 0;
		table_clk_vlt->entries[1].clk = PP_DAL_POWERLEVEL_LOW;
		अगर (hwmgr->chip_id >= CHIP_POLARIS10 &&
		    hwmgr->chip_id <= CHIP_VEGAM)
			table_clk_vlt->entries[1].v = 740;
		अन्यथा
			table_clk_vlt->entries[1].v = 720;
		table_clk_vlt->entries[2].clk = PP_DAL_POWERLEVEL_NOMINAL;
		अगर (hwmgr->chip_id >= CHIP_POLARIS10 &&
		    hwmgr->chip_id <= CHIP_VEGAM)
			table_clk_vlt->entries[2].v = 800;
		अन्यथा
			table_clk_vlt->entries[2].v = 810;
		table_clk_vlt->entries[3].clk = PP_DAL_POWERLEVEL_PERFORMANCE;
		table_clk_vlt->entries[3].v = 900;
		अगर (pptable_info != शून्य)
			pptable_info->vddc_dep_on_dal_pwrl = table_clk_vlt;
		hwmgr->dyn_state.vddc_dep_on_dal_pwrl = table_clk_vlt;
	पूर्ण

	वापस 0;
पूर्ण

uपूर्णांक32_t phm_get_lowest_enabled_level(काष्ठा pp_hwmgr *hwmgr, uपूर्णांक32_t mask)
अणु
	uपूर्णांक32_t level = 0;

	जबतक (0 == (mask & (1 << level)))
		level++;

	वापस level;
पूर्ण

व्योम phm_apply_dal_min_voltage_request(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा phm_ppt_v1_inक्रमmation *table_info =
			(काष्ठा phm_ppt_v1_inक्रमmation *)hwmgr->pptable;
	काष्ठा phm_घड़ी_voltage_dependency_table *table =
				table_info->vddc_dep_on_dal_pwrl;
	काष्ठा phm_ppt_v1_घड़ी_voltage_dependency_table *vddc_table;
	क्रमागत PP_DAL_POWERLEVEL dal_घातer_level = hwmgr->dal_घातer_level;
	uपूर्णांक32_t req_vddc = 0, req_volt, i;

	अगर (!table || table->count <= 0
		|| dal_घातer_level < PP_DAL_POWERLEVEL_ULTRALOW
		|| dal_घातer_level > PP_DAL_POWERLEVEL_PERFORMANCE)
		वापस;

	क्रम (i = 0; i < table->count; i++) अणु
		अगर (dal_घातer_level == table->entries[i].clk) अणु
			req_vddc = table->entries[i].v;
			अवरोध;
		पूर्ण
	पूर्ण

	vddc_table = table_info->vdd_dep_on_sclk;
	क्रम (i = 0; i < vddc_table->count; i++) अणु
		अगर (req_vddc <= vddc_table->entries[i].vddc) अणु
			req_volt = (((uपूर्णांक32_t)vddc_table->entries[i].vddc) * VOLTAGE_SCALE);
			smum_send_msg_to_smc_with_parameter(hwmgr,
					PPSMC_MSG_VddC_Request,
					req_volt,
					शून्य);
			वापस;
		पूर्ण
	पूर्ण
	pr_err("DAL requested level can not"
			" found a available voltage in VDDC DPM Table \n");
पूर्ण

पूर्णांक phm_get_voltage_evv_on_sclk(काष्ठा pp_hwmgr *hwmgr, uपूर्णांक8_t voltage_type,
				uपूर्णांक32_t sclk, uपूर्णांक16_t id, uपूर्णांक16_t *voltage)
अणु
	uपूर्णांक32_t vol;
	पूर्णांक ret = 0;

	अगर (hwmgr->chip_id < CHIP_TONGA) अणु
		ret = atomctrl_get_voltage_evv(hwmgr, id, voltage);
	पूर्ण अन्यथा अगर (hwmgr->chip_id < CHIP_POLARIS10) अणु
		ret = atomctrl_get_voltage_evv_on_sclk(hwmgr, voltage_type, sclk, id, voltage);
		अगर (*voltage >= 2000 || *voltage == 0)
			*voltage = 1150;
	पूर्ण अन्यथा अणु
		ret = atomctrl_get_voltage_evv_on_sclk_ai(hwmgr, voltage_type, sclk, id, &vol);
		*voltage = (uपूर्णांक16_t)(vol/100);
	पूर्ण
	वापस ret;
पूर्ण


पूर्णांक phm_irq_process(काष्ठा amdgpu_device *adev,
			   काष्ठा amdgpu_irq_src *source,
			   काष्ठा amdgpu_iv_entry *entry)
अणु
	uपूर्णांक32_t client_id = entry->client_id;
	uपूर्णांक32_t src_id = entry->src_id;

	अगर (client_id == AMDGPU_IRQ_CLIENTID_LEGACY) अणु
		अगर (src_id == VISLANDS30_IV_SRCID_CG_TSS_THERMAL_LOW_TO_HIGH) अणु
			dev_emerg(adev->dev, "ERROR: GPU over temperature range(SW CTF) detected!\n");
			/*
			 * SW CTF just occurred.
			 * Try to करो a graceful shutकरोwn to prevent further damage.
			 */
			dev_emerg(adev->dev, "ERROR: System is going to shutdown due to GPU SW CTF!\n");
			orderly_घातeroff(true);
		पूर्ण अन्यथा अगर (src_id == VISLANDS30_IV_SRCID_CG_TSS_THERMAL_HIGH_TO_LOW)
			dev_emerg(adev->dev, "ERROR: GPU under temperature range detected!\n");
		अन्यथा अगर (src_id == VISLANDS30_IV_SRCID_GPIO_19) अणु
			dev_emerg(adev->dev, "ERROR: GPU HW Critical Temperature Fault(aka CTF) detected!\n");
			/*
			 * HW CTF just occurred. Shutकरोwn to prevent further damage.
			 */
			dev_emerg(adev->dev, "ERROR: System is going to shutdown due to GPU HW CTF!\n");
			orderly_घातeroff(true);
		पूर्ण
	पूर्ण अन्यथा अगर (client_id == SOC15_IH_CLIENTID_THM) अणु
		अगर (src_id == 0) अणु
			dev_emerg(adev->dev, "ERROR: GPU over temperature range(SW CTF) detected!\n");
			/*
			 * SW CTF just occurred.
			 * Try to करो a graceful shutकरोwn to prevent further damage.
			 */
			dev_emerg(adev->dev, "ERROR: System is going to shutdown due to GPU SW CTF!\n");
			orderly_घातeroff(true);
		पूर्ण अन्यथा
			dev_emerg(adev->dev, "ERROR: GPU under temperature range detected!\n");
	पूर्ण अन्यथा अगर (client_id == SOC15_IH_CLIENTID_ROM_SMUIO) अणु
		dev_emerg(adev->dev, "ERROR: GPU HW Critical Temperature Fault(aka CTF) detected!\n");
		/*
		 * HW CTF just occurred. Shutकरोwn to prevent further damage.
		 */
		dev_emerg(adev->dev, "ERROR: System is going to shutdown due to GPU HW CTF!\n");
		orderly_घातeroff(true);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा amdgpu_irq_src_funcs smu9_irq_funcs = अणु
	.process = phm_irq_process,
पूर्ण;

पूर्णांक smu9_रेजिस्टर_irq_handlers(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा amdgpu_irq_src *source =
		kzalloc(माप(काष्ठा amdgpu_irq_src), GFP_KERNEL);

	अगर (!source)
		वापस -ENOMEM;

	source->funcs = &smu9_irq_funcs;

	amdgpu_irq_add_id((काष्ठा amdgpu_device *)(hwmgr->adev),
			SOC15_IH_CLIENTID_THM,
			THM_9_0__SRCID__THM_DIG_THERM_L2H,
			source);
	amdgpu_irq_add_id((काष्ठा amdgpu_device *)(hwmgr->adev),
			SOC15_IH_CLIENTID_THM,
			THM_9_0__SRCID__THM_DIG_THERM_H2L,
			source);

	/* Register CTF(GPIO_19) पूर्णांकerrupt */
	amdgpu_irq_add_id((काष्ठा amdgpu_device *)(hwmgr->adev),
			SOC15_IH_CLIENTID_ROM_SMUIO,
			SMUIO_9_0__SRCID__SMUIO_GPIO19,
			source);

	वापस 0;
पूर्ण

व्योम *smu_atom_get_data_table(व्योम *dev, uपूर्णांक32_t table, uपूर्णांक16_t *size,
						uपूर्णांक8_t *frev, uपूर्णांक8_t *crev)
अणु
	काष्ठा amdgpu_device *adev = dev;
	uपूर्णांक16_t data_start;

	अगर (amdgpu_atom_parse_data_header(
		    adev->mode_info.atom_context, table, size,
		    frev, crev, &data_start))
		वापस (uपूर्णांक8_t *)adev->mode_info.atom_context->bios +
			data_start;

	वापस शून्य;
पूर्ण

पूर्णांक smu_get_voltage_dependency_table_ppt_v1(
			स्थिर काष्ठा phm_ppt_v1_घड़ी_voltage_dependency_table *allowed_dep_table,
			काष्ठा phm_ppt_v1_घड़ी_voltage_dependency_table *dep_table)
अणु
	uपूर्णांक8_t i = 0;
	PP_ASSERT_WITH_CODE((0 != allowed_dep_table->count),
				"Voltage Lookup Table empty",
				वापस -EINVAL);

	dep_table->count = allowed_dep_table->count;
	क्रम (i=0; i<dep_table->count; i++) अणु
		dep_table->entries[i].clk = allowed_dep_table->entries[i].clk;
		dep_table->entries[i].vddInd = allowed_dep_table->entries[i].vddInd;
		dep_table->entries[i].vdd_offset = allowed_dep_table->entries[i].vdd_offset;
		dep_table->entries[i].vddc = allowed_dep_table->entries[i].vddc;
		dep_table->entries[i].vddgfx = allowed_dep_table->entries[i].vddgfx;
		dep_table->entries[i].vddci = allowed_dep_table->entries[i].vddci;
		dep_table->entries[i].mvdd = allowed_dep_table->entries[i].mvdd;
		dep_table->entries[i].phases = allowed_dep_table->entries[i].phases;
		dep_table->entries[i].cks_enable = allowed_dep_table->entries[i].cks_enable;
		dep_table->entries[i].cks_voffset = allowed_dep_table->entries[i].cks_voffset;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक smu_set_watermarks_क्रम_घड़ीs_ranges(व्योम *wt_table,
		काष्ठा dm_pp_wm_sets_with_घड़ी_ranges_soc15 *wm_with_घड़ी_ranges)
अणु
	uपूर्णांक32_t i;
	काष्ठा watermarks *table = wt_table;

	अगर (!table || !wm_with_घड़ी_ranges)
		वापस -EINVAL;

	अगर (wm_with_घड़ी_ranges->num_wm_dmअगर_sets > 4 || wm_with_घड़ी_ranges->num_wm_mcअगर_sets > 4)
		वापस -EINVAL;

	क्रम (i = 0; i < wm_with_घड़ी_ranges->num_wm_dmअगर_sets; i++) अणु
		table->WatermarkRow[1][i].MinClock =
			cpu_to_le16((uपूर्णांक16_t)
			(wm_with_घड़ी_ranges->wm_dmअगर_घड़ीs_ranges[i].wm_min_dcfclk_clk_in_khz /
			1000));
		table->WatermarkRow[1][i].MaxClock =
			cpu_to_le16((uपूर्णांक16_t)
			(wm_with_घड़ी_ranges->wm_dmअगर_घड़ीs_ranges[i].wm_max_dcfclk_clk_in_khz /
			1000));
		table->WatermarkRow[1][i].MinUclk =
			cpu_to_le16((uपूर्णांक16_t)
			(wm_with_घड़ी_ranges->wm_dmअगर_घड़ीs_ranges[i].wm_min_mem_clk_in_khz /
			1000));
		table->WatermarkRow[1][i].MaxUclk =
			cpu_to_le16((uपूर्णांक16_t)
			(wm_with_घड़ी_ranges->wm_dmअगर_घड़ीs_ranges[i].wm_max_mem_clk_in_khz /
			1000));
		table->WatermarkRow[1][i].WmSetting = (uपूर्णांक8_t)
				wm_with_घड़ी_ranges->wm_dmअगर_घड़ीs_ranges[i].wm_set_id;
	पूर्ण

	क्रम (i = 0; i < wm_with_घड़ी_ranges->num_wm_mcअगर_sets; i++) अणु
		table->WatermarkRow[0][i].MinClock =
			cpu_to_le16((uपूर्णांक16_t)
			(wm_with_घड़ी_ranges->wm_mcअगर_घड़ीs_ranges[i].wm_min_socclk_clk_in_khz /
			1000));
		table->WatermarkRow[0][i].MaxClock =
			cpu_to_le16((uपूर्णांक16_t)
			(wm_with_घड़ी_ranges->wm_mcअगर_घड़ीs_ranges[i].wm_max_socclk_clk_in_khz /
			1000));
		table->WatermarkRow[0][i].MinUclk =
			cpu_to_le16((uपूर्णांक16_t)
			(wm_with_घड़ी_ranges->wm_mcअगर_घड़ीs_ranges[i].wm_min_mem_clk_in_khz /
			1000));
		table->WatermarkRow[0][i].MaxUclk =
			cpu_to_le16((uपूर्णांक16_t)
			(wm_with_घड़ी_ranges->wm_mcअगर_घड़ीs_ranges[i].wm_max_mem_clk_in_khz /
			1000));
		table->WatermarkRow[0][i].WmSetting = (uपूर्णांक8_t)
				wm_with_घड़ी_ranges->wm_mcअगर_घड़ीs_ranges[i].wm_set_id;
	पूर्ण
	वापस 0;
पूर्ण
