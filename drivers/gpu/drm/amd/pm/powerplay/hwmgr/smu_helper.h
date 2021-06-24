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
#अगर_अघोषित _SMU_HELPER_H_
#घोषणा _SMU_HELPER_H_

काष्ठा pp_atomctrl_voltage_table;
काष्ठा pp_hwmgr;
काष्ठा phm_ppt_v1_voltage_lookup_table;
काष्ठा Watermarks_t;
काष्ठा pp_wm_sets_with_घड़ी_ranges_soc15;

uपूर्णांक8_t convert_to_vid(uपूर्णांक16_t vddc);
uपूर्णांक16_t convert_to_vddc(uपूर्णांक8_t vid);

काष्ठा watermark_row_generic_t अणु
	uपूर्णांक16_t MinClock;
	uपूर्णांक16_t MaxClock;
	uपूर्णांक16_t MinUclk;
	uपूर्णांक16_t MaxUclk;

	uपूर्णांक8_t  WmSetting;
	uपूर्णांक8_t  Padding[3];
पूर्ण;

काष्ठा watermarks अणु
	काष्ठा watermark_row_generic_t WatermarkRow[2][4];
	uपूर्णांक32_t     padding[7];
पूर्ण;

पूर्णांक phm_copy_घड़ी_limits_array(
	काष्ठा pp_hwmgr *hwmgr,
	uपूर्णांक32_t **pptable_info_array,
	स्थिर uपूर्णांक32_t *pptable_array,
	uपूर्णांक32_t घातer_saving_घड़ी_count);

पूर्णांक phm_copy_overdrive_settings_limits_array(
	काष्ठा pp_hwmgr *hwmgr,
	uपूर्णांक32_t **pptable_info_array,
	स्थिर uपूर्णांक32_t *pptable_array,
	uपूर्णांक32_t od_setting_count);

बाह्य पूर्णांक phm_रुको_क्रम_रेजिस्टर_unequal(काष्ठा pp_hwmgr *hwmgr,
					uपूर्णांक32_t index,
					uपूर्णांक32_t value, uपूर्णांक32_t mask);
बाह्य पूर्णांक phm_रुको_क्रम_indirect_रेजिस्टर_unequal(
				काष्ठा pp_hwmgr *hwmgr,
				uपूर्णांक32_t indirect_port, uपूर्णांक32_t index,
				uपूर्णांक32_t value, uपूर्णांक32_t mask);


बाह्य bool phm_cf_want_uvd_घातer_gating(काष्ठा pp_hwmgr *hwmgr);
बाह्य bool phm_cf_want_vce_घातer_gating(काष्ठा pp_hwmgr *hwmgr);
बाह्य bool phm_cf_want_microcode_fan_ctrl(काष्ठा pp_hwmgr *hwmgr);

बाह्य पूर्णांक phm_trim_voltage_table(काष्ठा pp_atomctrl_voltage_table *vol_table);
बाह्य पूर्णांक phm_get_svi2_mvdd_voltage_table(काष्ठा pp_atomctrl_voltage_table *vol_table, phm_ppt_v1_घड़ी_voltage_dependency_table *dep_table);
बाह्य पूर्णांक phm_get_svi2_vddci_voltage_table(काष्ठा pp_atomctrl_voltage_table *vol_table, phm_ppt_v1_घड़ी_voltage_dependency_table *dep_table);
बाह्य पूर्णांक phm_get_svi2_vdd_voltage_table(काष्ठा pp_atomctrl_voltage_table *vol_table, phm_ppt_v1_voltage_lookup_table *lookup_table);
बाह्य व्योम phm_trim_voltage_table_to_fit_state_table(uपूर्णांक32_t max_vol_steps, काष्ठा pp_atomctrl_voltage_table *vol_table);
बाह्य पूर्णांक phm_reset_single_dpm_table(व्योम *table, uपूर्णांक32_t count, पूर्णांक max);
बाह्य व्योम phm_setup_pcie_table_entry(व्योम *table, uपूर्णांक32_t index, uपूर्णांक32_t pcie_gen, uपूर्णांक32_t pcie_lanes);
बाह्य पूर्णांक32_t phm_get_dpm_level_enable_mask_value(व्योम *table);
बाह्य uपूर्णांक8_t phm_get_voltage_id(काष्ठा pp_atomctrl_voltage_table *voltage_table,
		uपूर्णांक32_t voltage);
बाह्य uपूर्णांक8_t phm_get_voltage_index(काष्ठा phm_ppt_v1_voltage_lookup_table *lookup_table, uपूर्णांक16_t voltage);
बाह्य uपूर्णांक16_t phm_find_बंदst_vddci(काष्ठा pp_atomctrl_voltage_table *vddci_table, uपूर्णांक16_t vddci);
बाह्य पूर्णांक phm_find_boot_level(व्योम *table, uपूर्णांक32_t value, uपूर्णांक32_t *boot_level);
बाह्य पूर्णांक phm_get_sclk_क्रम_voltage_evv(काष्ठा pp_hwmgr *hwmgr, phm_ppt_v1_voltage_lookup_table *lookup_table,
								uपूर्णांक16_t भव_voltage_id, पूर्णांक32_t *sclk);
बाह्य पूर्णांक phm_initializa_dynamic_state_adjusपंचांगent_rule_settings(काष्ठा pp_hwmgr *hwmgr);
बाह्य uपूर्णांक32_t phm_get_lowest_enabled_level(काष्ठा pp_hwmgr *hwmgr, uपूर्णांक32_t mask);
बाह्य व्योम phm_apply_dal_min_voltage_request(काष्ठा pp_hwmgr *hwmgr);

बाह्य पूर्णांक phm_get_voltage_evv_on_sclk(काष्ठा pp_hwmgr *hwmgr, uपूर्णांक8_t voltage_type,
				uपूर्णांक32_t sclk, uपूर्णांक16_t id, uपूर्णांक16_t *voltage);

बाह्य uपूर्णांक32_t phm_set_field_to_u32(u32 offset, u32 original_data, u32 field, u32 size);

बाह्य पूर्णांक phm_रुको_on_रेजिस्टर(काष्ठा pp_hwmgr *hwmgr, uपूर्णांक32_t index,
				uपूर्णांक32_t value, uपूर्णांक32_t mask);

बाह्य पूर्णांक phm_रुको_on_indirect_रेजिस्टर(काष्ठा pp_hwmgr *hwmgr,
				uपूर्णांक32_t indirect_port,
				uपूर्णांक32_t index,
				uपूर्णांक32_t value,
				uपूर्णांक32_t mask);

पूर्णांक phm_irq_process(काष्ठा amdgpu_device *adev,
			   काष्ठा amdgpu_irq_src *source,
			   काष्ठा amdgpu_iv_entry *entry);

पूर्णांक smu9_रेजिस्टर_irq_handlers(काष्ठा pp_hwmgr *hwmgr);

व्योम *smu_atom_get_data_table(व्योम *dev, uपूर्णांक32_t table, uपूर्णांक16_t *size,
						uपूर्णांक8_t *frev, uपूर्णांक8_t *crev);

पूर्णांक smu_get_voltage_dependency_table_ppt_v1(
	स्थिर काष्ठा phm_ppt_v1_घड़ी_voltage_dependency_table *allowed_dep_table,
		काष्ठा phm_ppt_v1_घड़ी_voltage_dependency_table *dep_table);

पूर्णांक smu_set_watermarks_क्रम_घड़ीs_ranges(व्योम *wt_table,
		काष्ठा dm_pp_wm_sets_with_घड़ी_ranges_soc15 *wm_with_घड़ी_ranges);

#घोषणा PHM_FIELD_SHIFT(reg, field) reg##__##field##__SHIFT
#घोषणा PHM_FIELD_MASK(reg, field) reg##__##field##_MASK

#घोषणा PHM_SET_FIELD(origval, reg, field, fieldval)	\
	(((origval) & ~PHM_FIELD_MASK(reg, field)) |	\
	 (PHM_FIELD_MASK(reg, field) & ((fieldval) << PHM_FIELD_SHIFT(reg, field))))

#घोषणा PHM_GET_FIELD(value, reg, field)	\
	(((value) & PHM_FIELD_MASK(reg, field)) >>	\
	 PHM_FIELD_SHIFT(reg, field))


/* Operations on named fields. */

#घोषणा PHM_READ_FIELD(device, reg, field)	\
	PHM_GET_FIELD(cgs_पढ़ो_रेजिस्टर(device, mm##reg), reg, field)

#घोषणा PHM_READ_INसूचीECT_FIELD(device, port, reg, field)	\
	PHM_GET_FIELD(cgs_पढ़ो_ind_रेजिस्टर(device, port, ix##reg),	\
			reg, field)

#घोषणा PHM_READ_VFPF_INसूचीECT_FIELD(device, port, reg, field)	\
	PHM_GET_FIELD(cgs_पढ़ो_ind_रेजिस्टर(device, port, ix##reg),	\
			reg, field)

#घोषणा PHM_WRITE_FIELD(device, reg, field, fieldval)	\
	cgs_ग_लिखो_रेजिस्टर(device, mm##reg, PHM_SET_FIELD(	\
				cgs_पढ़ो_रेजिस्टर(device, mm##reg), reg, field, fieldval))

#घोषणा PHM_WRITE_INसूचीECT_FIELD(device, port, reg, field, fieldval)	\
	cgs_ग_लिखो_ind_रेजिस्टर(device, port, ix##reg,	\
			PHM_SET_FIELD(cgs_पढ़ो_ind_रेजिस्टर(device, port, ix##reg),	\
				reg, field, fieldval))

#घोषणा PHM_WRITE_VFPF_INसूचीECT_FIELD(device, port, reg, field, fieldval)	\
	cgs_ग_लिखो_ind_रेजिस्टर(device, port, ix##reg,	\
			PHM_SET_FIELD(cgs_पढ़ो_ind_रेजिस्टर(device, port, ix##reg),	\
				reg, field, fieldval))

#घोषणा PHM_WAIT_INसूचीECT_REGISTER_GIVEN_INDEX(hwmgr, port, index, value, mask)        \
       phm_रुको_on_indirect_रेजिस्टर(hwmgr, mm##port##_INDEX, index, value, mask)


#घोषणा PHM_WAIT_INसूचीECT_REGISTER(hwmgr, port, reg, value, mask)      \
       PHM_WAIT_INसूचीECT_REGISTER_GIVEN_INDEX(hwmgr, port, ix##reg, value, mask)

#घोषणा PHM_WAIT_INसूचीECT_FIELD(hwmgr, port, reg, field, fieldval)	\
	PHM_WAIT_INसूचीECT_REGISTER(hwmgr, port, reg, (fieldval)	\
			<< PHM_FIELD_SHIFT(reg, field), PHM_FIELD_MASK(reg, field))

#घोषणा PHM_WAIT_INसूचीECT_REGISTER_UNEQUAL_GIVEN_INDEX(hwmgr, port, index, value, mask)    \
		phm_रुको_क्रम_indirect_रेजिस्टर_unequal(hwmgr,                   \
				mm##port##_INDEX, index, value, mask)

#घोषणा PHM_WAIT_INसूचीECT_REGISTER_UNEQUAL(hwmgr, port, reg, value, mask)    \
		PHM_WAIT_INसूचीECT_REGISTER_UNEQUAL_GIVEN_INDEX(hwmgr, port, ix##reg, value, mask)

#घोषणा PHM_WAIT_INसूचीECT_FIELD_UNEQUAL(hwmgr, port, reg, field, fieldval)                          \
		PHM_WAIT_INसूचीECT_REGISTER_UNEQUAL(hwmgr, port, reg, \
				(fieldval) << PHM_FIELD_SHIFT(reg, field), \
					PHM_FIELD_MASK(reg, field) )


#घोषणा PHM_WAIT_VFPF_INसूचीECT_REGISTER_UNEQUAL_GIVEN_INDEX(hwmgr,	\
				port, index, value, mask)		\
	phm_रुको_क्रम_indirect_रेजिस्टर_unequal(hwmgr,			\
		mm##port##_INDEX_11, index, value, mask)

#घोषणा PHM_WAIT_VFPF_INसूचीECT_REGISTER_UNEQUAL(hwmgr, port, reg, value, mask)     \
		PHM_WAIT_VFPF_INसूचीECT_REGISTER_UNEQUAL_GIVEN_INDEX(hwmgr, port, ix##reg, value, mask)

#घोषणा PHM_WAIT_VFPF_INसूचीECT_FIELD_UNEQUAL(hwmgr, port, reg, field, fieldval) \
	PHM_WAIT_VFPF_INसूचीECT_REGISTER_UNEQUAL(hwmgr, port, reg,	\
		(fieldval) << PHM_FIELD_SHIFT(reg, field),		\
		PHM_FIELD_MASK(reg, field))


#घोषणा PHM_WAIT_VFPF_INसूचीECT_REGISTER_GIVEN_INDEX(hwmgr,		\
				port, index, value, mask)		\
	phm_रुको_on_indirect_रेजिस्टर(hwmgr,				\
		mm##port##_INDEX_11, index, value, mask)

#घोषणा PHM_WAIT_VFPF_INसूचीECT_REGISTER(hwmgr, port, reg, value, mask) \
	PHM_WAIT_VFPF_INसूचीECT_REGISTER_GIVEN_INDEX(hwmgr, port, ix##reg, value, mask)

#घोषणा PHM_WAIT_VFPF_INसूचीECT_FIELD(hwmgr, port, reg, field, fieldval) \
	PHM_WAIT_VFPF_INसूचीECT_REGISTER(hwmgr, port, reg,		\
		(fieldval) << PHM_FIELD_SHIFT(reg, field),		\
		PHM_FIELD_MASK(reg, field))

#घोषणा PHM_WAIT_REGISTER_UNEQUAL_GIVEN_INDEX(hwmgr,         \
							index, value, mask) \
		phm_रुको_क्रम_रेजिस्टर_unequal(hwmgr,            \
					index, value, mask)

#घोषणा PHM_WAIT_REGISTER_UNEQUAL(hwmgr, reg, value, mask)		\
	PHM_WAIT_REGISTER_UNEQUAL_GIVEN_INDEX(hwmgr,			\
				mm##reg, value, mask)

#घोषणा PHM_WAIT_FIELD_UNEQUAL(hwmgr, reg, field, fieldval)		\
	PHM_WAIT_REGISTER_UNEQUAL(hwmgr, reg,				\
		(fieldval) << PHM_FIELD_SHIFT(reg, field),		\
		PHM_FIELD_MASK(reg, field))

#पूर्ण_अगर /* _SMU_HELPER_H_ */
