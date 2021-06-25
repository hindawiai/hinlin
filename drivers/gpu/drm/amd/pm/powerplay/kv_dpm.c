<शैली गुरु>
/*
 * Copyright 2013 Advanced Micro Devices, Inc.
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

#समावेश "amdgpu.h"
#समावेश "amdgpu_pm.h"
#समावेश "cikd.h"
#समावेश "atom.h"
#समावेश "amdgpu_atombios.h"
#समावेश "amdgpu_dpm.h"
#समावेश "kv_dpm.h"
#समावेश "gfx_v7_0.h"
#समावेश <linux/seq_file.h>

#समावेश "smu/smu_7_0_0_d.h"
#समावेश "smu/smu_7_0_0_sh_mask.h"

#समावेश "gca/gfx_7_2_d.h"
#समावेश "gca/gfx_7_2_sh_mask.h"

#घोषणा KV_MAX_DEEPSLEEP_DIVIDER_ID     5
#घोषणा KV_MINIMUM_ENGINE_CLOCK         800
#घोषणा SMC_RAM_END                     0x40000

अटल स्थिर काष्ठा amd_pm_funcs kv_dpm_funcs;

अटल व्योम kv_dpm_set_irq_funcs(काष्ठा amdgpu_device *adev);
अटल पूर्णांक kv_enable_nb_dpm(काष्ठा amdgpu_device *adev,
			    bool enable);
अटल व्योम kv_init_graphics_levels(काष्ठा amdgpu_device *adev);
अटल पूर्णांक kv_calculate_ds_भागider(काष्ठा amdgpu_device *adev);
अटल पूर्णांक kv_calculate_nbps_level_settings(काष्ठा amdgpu_device *adev);
अटल पूर्णांक kv_calculate_dpm_settings(काष्ठा amdgpu_device *adev);
अटल व्योम kv_enable_new_levels(काष्ठा amdgpu_device *adev);
अटल व्योम kv_program_nbps_index_settings(काष्ठा amdgpu_device *adev,
					   काष्ठा amdgpu_ps *new_rps);
अटल पूर्णांक kv_set_enabled_level(काष्ठा amdgpu_device *adev, u32 level);
अटल पूर्णांक kv_set_enabled_levels(काष्ठा amdgpu_device *adev);
अटल पूर्णांक kv_क्रमce_dpm_highest(काष्ठा amdgpu_device *adev);
अटल पूर्णांक kv_क्रमce_dpm_lowest(काष्ठा amdgpu_device *adev);
अटल व्योम kv_apply_state_adjust_rules(काष्ठा amdgpu_device *adev,
					काष्ठा amdgpu_ps *new_rps,
					काष्ठा amdgpu_ps *old_rps);
अटल पूर्णांक kv_set_thermal_temperature_range(काष्ठा amdgpu_device *adev,
					    पूर्णांक min_temp, पूर्णांक max_temp);
अटल पूर्णांक kv_init_fps_limits(काष्ठा amdgpu_device *adev);

अटल व्योम kv_dpm_घातergate_samu(काष्ठा amdgpu_device *adev, bool gate);
अटल व्योम kv_dpm_घातergate_acp(काष्ठा amdgpu_device *adev, bool gate);


अटल u32 kv_convert_vid2_to_vid7(काष्ठा amdgpu_device *adev,
				   काष्ठा sumo_vid_mapping_table *vid_mapping_table,
				   u32 vid_2bit)
अणु
	काष्ठा amdgpu_घड़ी_voltage_dependency_table *vddc_sclk_table =
		&adev->pm.dpm.dyn_state.vddc_dependency_on_sclk;
	u32 i;

	अगर (vddc_sclk_table && vddc_sclk_table->count) अणु
		अगर (vid_2bit < vddc_sclk_table->count)
			वापस vddc_sclk_table->entries[vid_2bit].v;
		अन्यथा
			वापस vddc_sclk_table->entries[vddc_sclk_table->count - 1].v;
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < vid_mapping_table->num_entries; i++) अणु
			अगर (vid_mapping_table->entries[i].vid_2bit == vid_2bit)
				वापस vid_mapping_table->entries[i].vid_7bit;
		पूर्ण
		वापस vid_mapping_table->entries[vid_mapping_table->num_entries - 1].vid_7bit;
	पूर्ण
पूर्ण

अटल u32 kv_convert_vid7_to_vid2(काष्ठा amdgpu_device *adev,
				   काष्ठा sumo_vid_mapping_table *vid_mapping_table,
				   u32 vid_7bit)
अणु
	काष्ठा amdgpu_घड़ी_voltage_dependency_table *vddc_sclk_table =
		&adev->pm.dpm.dyn_state.vddc_dependency_on_sclk;
	u32 i;

	अगर (vddc_sclk_table && vddc_sclk_table->count) अणु
		क्रम (i = 0; i < vddc_sclk_table->count; i++) अणु
			अगर (vddc_sclk_table->entries[i].v == vid_7bit)
				वापस i;
		पूर्ण
		वापस vddc_sclk_table->count - 1;
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < vid_mapping_table->num_entries; i++) अणु
			अगर (vid_mapping_table->entries[i].vid_7bit == vid_7bit)
				वापस vid_mapping_table->entries[i].vid_2bit;
		पूर्ण

		वापस vid_mapping_table->entries[vid_mapping_table->num_entries - 1].vid_2bit;
	पूर्ण
पूर्ण

अटल व्योम sumo_take_smu_control(काष्ठा amdgpu_device *adev, bool enable)
अणु
/* This bit selects who handles display phy घातergating.
 * Clear the bit to let atom handle it.
 * Set it to let the driver handle it.
 * For now we just let atom handle it.
 */
#अगर 0
	u32 v = RREG32(mmDOUT_SCRATCH3);

	अगर (enable)
		v |= 0x4;
	अन्यथा
		v &= 0xFFFFFFFB;

	WREG32(mmDOUT_SCRATCH3, v);
#पूर्ण_अगर
पूर्ण

अटल व्योम sumo_स्थिरruct_sclk_voltage_mapping_table(काष्ठा amdgpu_device *adev,
						      काष्ठा sumo_sclk_voltage_mapping_table *sclk_voltage_mapping_table,
						      ATOM_AVAILABLE_SCLK_LIST *table)
अणु
	u32 i;
	u32 n = 0;
	u32 prev_sclk = 0;

	क्रम (i = 0; i < SUMO_MAX_HARDWARE_POWERLEVELS; i++) अणु
		अगर (table[i].ulSupportedSCLK > prev_sclk) अणु
			sclk_voltage_mapping_table->entries[n].sclk_frequency =
				table[i].ulSupportedSCLK;
			sclk_voltage_mapping_table->entries[n].vid_2bit =
				table[i].usVoltageIndex;
			prev_sclk = table[i].ulSupportedSCLK;
			n++;
		पूर्ण
	पूर्ण

	sclk_voltage_mapping_table->num_max_dpm_entries = n;
पूर्ण

अटल व्योम sumo_स्थिरruct_vid_mapping_table(काष्ठा amdgpu_device *adev,
					     काष्ठा sumo_vid_mapping_table *vid_mapping_table,
					     ATOM_AVAILABLE_SCLK_LIST *table)
अणु
	u32 i, j;

	क्रम (i = 0; i < SUMO_MAX_HARDWARE_POWERLEVELS; i++) अणु
		अगर (table[i].ulSupportedSCLK != 0) अणु
			vid_mapping_table->entries[table[i].usVoltageIndex].vid_7bit =
				table[i].usVoltageID;
			vid_mapping_table->entries[table[i].usVoltageIndex].vid_2bit =
				table[i].usVoltageIndex;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < SUMO_MAX_NUMBER_VOLTAGES; i++) अणु
		अगर (vid_mapping_table->entries[i].vid_7bit == 0) अणु
			क्रम (j = i + 1; j < SUMO_MAX_NUMBER_VOLTAGES; j++) अणु
				अगर (vid_mapping_table->entries[j].vid_7bit != 0) अणु
					vid_mapping_table->entries[i] =
						vid_mapping_table->entries[j];
					vid_mapping_table->entries[j].vid_7bit = 0;
					अवरोध;
				पूर्ण
			पूर्ण

			अगर (j == SUMO_MAX_NUMBER_VOLTAGES)
				अवरोध;
		पूर्ण
	पूर्ण

	vid_mapping_table->num_entries = i;
पूर्ण

#अगर 0
अटल स्थिर काष्ठा kv_lcac_config_values sx_local_cac_cfg_kv[] =
अणु
	अणु  0,       4,        1    पूर्ण,
	अणु  1,       4,        1    पूर्ण,
	अणु  2,       5,        1    पूर्ण,
	अणु  3,       4,        2    पूर्ण,
	अणु  4,       1,        1    पूर्ण,
	अणु  5,       5,        2    पूर्ण,
	अणु  6,       6,        1    पूर्ण,
	अणु  7,       9,        2    पूर्ण,
	अणु 0xffffffff पूर्ण
पूर्ण;

अटल स्थिर काष्ठा kv_lcac_config_values mc0_local_cac_cfg_kv[] =
अणु
	अणु  0,       4,        1    पूर्ण,
	अणु 0xffffffff पूर्ण
पूर्ण;

अटल स्थिर काष्ठा kv_lcac_config_values mc1_local_cac_cfg_kv[] =
अणु
	अणु  0,       4,        1    पूर्ण,
	अणु 0xffffffff पूर्ण
पूर्ण;

अटल स्थिर काष्ठा kv_lcac_config_values mc2_local_cac_cfg_kv[] =
अणु
	अणु  0,       4,        1    पूर्ण,
	अणु 0xffffffff पूर्ण
पूर्ण;

अटल स्थिर काष्ठा kv_lcac_config_values mc3_local_cac_cfg_kv[] =
अणु
	अणु  0,       4,        1    पूर्ण,
	अणु 0xffffffff पूर्ण
पूर्ण;

अटल स्थिर काष्ठा kv_lcac_config_values cpl_local_cac_cfg_kv[] =
अणु
	अणु  0,       4,        1    पूर्ण,
	अणु  1,       4,        1    पूर्ण,
	अणु  2,       5,        1    पूर्ण,
	अणु  3,       4,        1    पूर्ण,
	अणु  4,       1,        1    पूर्ण,
	अणु  5,       5,        1    पूर्ण,
	अणु  6,       6,        1    पूर्ण,
	अणु  7,       9,        1    पूर्ण,
	अणु  8,       4,        1    पूर्ण,
	अणु  9,       2,        1    पूर्ण,
	अणु  10,      3,        1    पूर्ण,
	अणु  11,      6,        1    पूर्ण,
	अणु  12,      8,        2    पूर्ण,
	अणु  13,      1,        1    पूर्ण,
	अणु  14,      2,        1    पूर्ण,
	अणु  15,      3,        1    पूर्ण,
	अणु  16,      1,        1    पूर्ण,
	अणु  17,      4,        1    पूर्ण,
	अणु  18,      3,        1    पूर्ण,
	अणु  19,      1,        1    पूर्ण,
	अणु  20,      8,        1    पूर्ण,
	अणु  21,      5,        1    पूर्ण,
	अणु  22,      1,        1    पूर्ण,
	अणु  23,      1,        1    पूर्ण,
	अणु  24,      4,        1    पूर्ण,
	अणु  27,      6,        1    पूर्ण,
	अणु  28,      1,        1    पूर्ण,
	अणु 0xffffffff पूर्ण
पूर्ण;

अटल स्थिर काष्ठा kv_lcac_config_reg sx0_cac_config_reg[] =
अणु
	अणु 0xc0400d00, 0x003e0000, 17, 0x3fc00000, 22, 0x0001fffe, 1, 0x00000001, 0 पूर्ण
पूर्ण;

अटल स्थिर काष्ठा kv_lcac_config_reg mc0_cac_config_reg[] =
अणु
	अणु 0xc0400d30, 0x003e0000, 17, 0x3fc00000, 22, 0x0001fffe, 1, 0x00000001, 0 पूर्ण
पूर्ण;

अटल स्थिर काष्ठा kv_lcac_config_reg mc1_cac_config_reg[] =
अणु
	अणु 0xc0400d3c, 0x003e0000, 17, 0x3fc00000, 22, 0x0001fffe, 1, 0x00000001, 0 पूर्ण
पूर्ण;

अटल स्थिर काष्ठा kv_lcac_config_reg mc2_cac_config_reg[] =
अणु
	अणु 0xc0400d48, 0x003e0000, 17, 0x3fc00000, 22, 0x0001fffe, 1, 0x00000001, 0 पूर्ण
पूर्ण;

अटल स्थिर काष्ठा kv_lcac_config_reg mc3_cac_config_reg[] =
अणु
	अणु 0xc0400d54, 0x003e0000, 17, 0x3fc00000, 22, 0x0001fffe, 1, 0x00000001, 0 पूर्ण
पूर्ण;

अटल स्थिर काष्ठा kv_lcac_config_reg cpl_cac_config_reg[] =
अणु
	अणु 0xc0400d80, 0x003e0000, 17, 0x3fc00000, 22, 0x0001fffe, 1, 0x00000001, 0 पूर्ण
पूर्ण;
#पूर्ण_अगर

अटल स्थिर काष्ठा kv_pt_config_reg didt_config_kv[] =
अणु
	अणु 0x10, 0x000000ff, 0, 0x0, KV_CONFIGREG_DIDT_IND पूर्ण,
	अणु 0x10, 0x0000ff00, 8, 0x0, KV_CONFIGREG_DIDT_IND पूर्ण,
	अणु 0x10, 0x00ff0000, 16, 0x0, KV_CONFIGREG_DIDT_IND पूर्ण,
	अणु 0x10, 0xff000000, 24, 0x0, KV_CONFIGREG_DIDT_IND पूर्ण,
	अणु 0x11, 0x000000ff, 0, 0x0, KV_CONFIGREG_DIDT_IND पूर्ण,
	अणु 0x11, 0x0000ff00, 8, 0x0, KV_CONFIGREG_DIDT_IND पूर्ण,
	अणु 0x11, 0x00ff0000, 16, 0x0, KV_CONFIGREG_DIDT_IND पूर्ण,
	अणु 0x11, 0xff000000, 24, 0x0, KV_CONFIGREG_DIDT_IND पूर्ण,
	अणु 0x12, 0x000000ff, 0, 0x0, KV_CONFIGREG_DIDT_IND पूर्ण,
	अणु 0x12, 0x0000ff00, 8, 0x0, KV_CONFIGREG_DIDT_IND पूर्ण,
	अणु 0x12, 0x00ff0000, 16, 0x0, KV_CONFIGREG_DIDT_IND पूर्ण,
	अणु 0x12, 0xff000000, 24, 0x0, KV_CONFIGREG_DIDT_IND पूर्ण,
	अणु 0x2, 0x00003fff, 0, 0x4, KV_CONFIGREG_DIDT_IND पूर्ण,
	अणु 0x2, 0x03ff0000, 16, 0x80, KV_CONFIGREG_DIDT_IND पूर्ण,
	अणु 0x2, 0x78000000, 27, 0x3, KV_CONFIGREG_DIDT_IND पूर्ण,
	अणु 0x1, 0x0000ffff, 0, 0x3FFF, KV_CONFIGREG_DIDT_IND पूर्ण,
	अणु 0x1, 0xffff0000, 16, 0x3FFF, KV_CONFIGREG_DIDT_IND पूर्ण,
	अणु 0x0, 0x00000001, 0, 0x0, KV_CONFIGREG_DIDT_IND पूर्ण,
	अणु 0x30, 0x000000ff, 0, 0x0, KV_CONFIGREG_DIDT_IND पूर्ण,
	अणु 0x30, 0x0000ff00, 8, 0x0, KV_CONFIGREG_DIDT_IND पूर्ण,
	अणु 0x30, 0x00ff0000, 16, 0x0, KV_CONFIGREG_DIDT_IND पूर्ण,
	अणु 0x30, 0xff000000, 24, 0x0, KV_CONFIGREG_DIDT_IND पूर्ण,
	अणु 0x31, 0x000000ff, 0, 0x0, KV_CONFIGREG_DIDT_IND पूर्ण,
	अणु 0x31, 0x0000ff00, 8, 0x0, KV_CONFIGREG_DIDT_IND पूर्ण,
	अणु 0x31, 0x00ff0000, 16, 0x0, KV_CONFIGREG_DIDT_IND पूर्ण,
	अणु 0x31, 0xff000000, 24, 0x0, KV_CONFIGREG_DIDT_IND पूर्ण,
	अणु 0x32, 0x000000ff, 0, 0x0, KV_CONFIGREG_DIDT_IND पूर्ण,
	अणु 0x32, 0x0000ff00, 8, 0x0, KV_CONFIGREG_DIDT_IND पूर्ण,
	अणु 0x32, 0x00ff0000, 16, 0x0, KV_CONFIGREG_DIDT_IND पूर्ण,
	अणु 0x32, 0xff000000, 24, 0x0, KV_CONFIGREG_DIDT_IND पूर्ण,
	अणु 0x22, 0x00003fff, 0, 0x4, KV_CONFIGREG_DIDT_IND पूर्ण,
	अणु 0x22, 0x03ff0000, 16, 0x80, KV_CONFIGREG_DIDT_IND पूर्ण,
	अणु 0x22, 0x78000000, 27, 0x3, KV_CONFIGREG_DIDT_IND पूर्ण,
	अणु 0x21, 0x0000ffff, 0, 0x3FFF, KV_CONFIGREG_DIDT_IND पूर्ण,
	अणु 0x21, 0xffff0000, 16, 0x3FFF, KV_CONFIGREG_DIDT_IND पूर्ण,
	अणु 0x20, 0x00000001, 0, 0x0, KV_CONFIGREG_DIDT_IND पूर्ण,
	अणु 0x50, 0x000000ff, 0, 0x0, KV_CONFIGREG_DIDT_IND पूर्ण,
	अणु 0x50, 0x0000ff00, 8, 0x0, KV_CONFIGREG_DIDT_IND पूर्ण,
	अणु 0x50, 0x00ff0000, 16, 0x0, KV_CONFIGREG_DIDT_IND पूर्ण,
	अणु 0x50, 0xff000000, 24, 0x0, KV_CONFIGREG_DIDT_IND पूर्ण,
	अणु 0x51, 0x000000ff, 0, 0x0, KV_CONFIGREG_DIDT_IND पूर्ण,
	अणु 0x51, 0x0000ff00, 8, 0x0, KV_CONFIGREG_DIDT_IND पूर्ण,
	अणु 0x51, 0x00ff0000, 16, 0x0, KV_CONFIGREG_DIDT_IND पूर्ण,
	अणु 0x51, 0xff000000, 24, 0x0, KV_CONFIGREG_DIDT_IND पूर्ण,
	अणु 0x52, 0x000000ff, 0, 0x0, KV_CONFIGREG_DIDT_IND पूर्ण,
	अणु 0x52, 0x0000ff00, 8, 0x0, KV_CONFIGREG_DIDT_IND पूर्ण,
	अणु 0x52, 0x00ff0000, 16, 0x0, KV_CONFIGREG_DIDT_IND पूर्ण,
	अणु 0x52, 0xff000000, 24, 0x0, KV_CONFIGREG_DIDT_IND पूर्ण,
	अणु 0x42, 0x00003fff, 0, 0x4, KV_CONFIGREG_DIDT_IND पूर्ण,
	अणु 0x42, 0x03ff0000, 16, 0x80, KV_CONFIGREG_DIDT_IND पूर्ण,
	अणु 0x42, 0x78000000, 27, 0x3, KV_CONFIGREG_DIDT_IND पूर्ण,
	अणु 0x41, 0x0000ffff, 0, 0x3FFF, KV_CONFIGREG_DIDT_IND पूर्ण,
	अणु 0x41, 0xffff0000, 16, 0x3FFF, KV_CONFIGREG_DIDT_IND पूर्ण,
	अणु 0x40, 0x00000001, 0, 0x0, KV_CONFIGREG_DIDT_IND पूर्ण,
	अणु 0x70, 0x000000ff, 0, 0x0, KV_CONFIGREG_DIDT_IND पूर्ण,
	अणु 0x70, 0x0000ff00, 8, 0x0, KV_CONFIGREG_DIDT_IND पूर्ण,
	अणु 0x70, 0x00ff0000, 16, 0x0, KV_CONFIGREG_DIDT_IND पूर्ण,
	अणु 0x70, 0xff000000, 24, 0x0, KV_CONFIGREG_DIDT_IND पूर्ण,
	अणु 0x71, 0x000000ff, 0, 0x0, KV_CONFIGREG_DIDT_IND पूर्ण,
	अणु 0x71, 0x0000ff00, 8, 0x0, KV_CONFIGREG_DIDT_IND पूर्ण,
	अणु 0x71, 0x00ff0000, 16, 0x0, KV_CONFIGREG_DIDT_IND पूर्ण,
	अणु 0x71, 0xff000000, 24, 0x0, KV_CONFIGREG_DIDT_IND पूर्ण,
	अणु 0x72, 0x000000ff, 0, 0x0, KV_CONFIGREG_DIDT_IND पूर्ण,
	अणु 0x72, 0x0000ff00, 8, 0x0, KV_CONFIGREG_DIDT_IND पूर्ण,
	अणु 0x72, 0x00ff0000, 16, 0x0, KV_CONFIGREG_DIDT_IND पूर्ण,
	अणु 0x72, 0xff000000, 24, 0x0, KV_CONFIGREG_DIDT_IND पूर्ण,
	अणु 0x62, 0x00003fff, 0, 0x4, KV_CONFIGREG_DIDT_IND पूर्ण,
	अणु 0x62, 0x03ff0000, 16, 0x80, KV_CONFIGREG_DIDT_IND पूर्ण,
	अणु 0x62, 0x78000000, 27, 0x3, KV_CONFIGREG_DIDT_IND पूर्ण,
	अणु 0x61, 0x0000ffff, 0, 0x3FFF, KV_CONFIGREG_DIDT_IND पूर्ण,
	अणु 0x61, 0xffff0000, 16, 0x3FFF, KV_CONFIGREG_DIDT_IND पूर्ण,
	अणु 0x60, 0x00000001, 0, 0x0, KV_CONFIGREG_DIDT_IND पूर्ण,
	अणु 0xFFFFFFFF पूर्ण
पूर्ण;

अटल काष्ठा kv_ps *kv_get_ps(काष्ठा amdgpu_ps *rps)
अणु
	काष्ठा kv_ps *ps = rps->ps_priv;

	वापस ps;
पूर्ण

अटल काष्ठा kv_घातer_info *kv_get_pi(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा kv_घातer_info *pi = adev->pm.dpm.priv;

	वापस pi;
पूर्ण

#अगर 0
अटल व्योम kv_program_local_cac_table(काष्ठा amdgpu_device *adev,
				       स्थिर काष्ठा kv_lcac_config_values *local_cac_table,
				       स्थिर काष्ठा kv_lcac_config_reg *local_cac_reg)
अणु
	u32 i, count, data;
	स्थिर काष्ठा kv_lcac_config_values *values = local_cac_table;

	जबतक (values->block_id != 0xffffffff) अणु
		count = values->संकेत_id;
		क्रम (i = 0; i < count; i++) अणु
			data = ((values->block_id << local_cac_reg->block_shअगरt) &
				local_cac_reg->block_mask);
			data |= ((i << local_cac_reg->संकेत_shअगरt) &
				 local_cac_reg->संकेत_mask);
			data |= ((values->t << local_cac_reg->t_shअगरt) &
				 local_cac_reg->t_mask);
			data |= ((1 << local_cac_reg->enable_shअगरt) &
				 local_cac_reg->enable_mask);
			WREG32_SMC(local_cac_reg->cntl, data);
		पूर्ण
		values++;
	पूर्ण
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक kv_program_pt_config_रेजिस्टरs(काष्ठा amdgpu_device *adev,
					  स्थिर काष्ठा kv_pt_config_reg *cac_config_regs)
अणु
	स्थिर काष्ठा kv_pt_config_reg *config_regs = cac_config_regs;
	u32 data;
	u32 cache = 0;

	अगर (config_regs == शून्य)
		वापस -EINVAL;

	जबतक (config_regs->offset != 0xFFFFFFFF) अणु
		अगर (config_regs->type == KV_CONFIGREG_CACHE) अणु
			cache |= ((config_regs->value << config_regs->shअगरt) & config_regs->mask);
		पूर्ण अन्यथा अणु
			चयन (config_regs->type) अणु
			हाल KV_CONFIGREG_SMC_IND:
				data = RREG32_SMC(config_regs->offset);
				अवरोध;
			हाल KV_CONFIGREG_DIDT_IND:
				data = RREG32_DIDT(config_regs->offset);
				अवरोध;
			शेष:
				data = RREG32(config_regs->offset);
				अवरोध;
			पूर्ण

			data &= ~config_regs->mask;
			data |= ((config_regs->value << config_regs->shअगरt) & config_regs->mask);
			data |= cache;
			cache = 0;

			चयन (config_regs->type) अणु
			हाल KV_CONFIGREG_SMC_IND:
				WREG32_SMC(config_regs->offset, data);
				अवरोध;
			हाल KV_CONFIGREG_DIDT_IND:
				WREG32_DIDT(config_regs->offset, data);
				अवरोध;
			शेष:
				WREG32(config_regs->offset, data);
				अवरोध;
			पूर्ण
		पूर्ण
		config_regs++;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम kv_करो_enable_didt(काष्ठा amdgpu_device *adev, bool enable)
अणु
	काष्ठा kv_घातer_info *pi = kv_get_pi(adev);
	u32 data;

	अगर (pi->caps_sq_ramping) अणु
		data = RREG32_DIDT(ixDIDT_SQ_CTRL0);
		अगर (enable)
			data |= DIDT_SQ_CTRL0__DIDT_CTRL_EN_MASK;
		अन्यथा
			data &= ~DIDT_SQ_CTRL0__DIDT_CTRL_EN_MASK;
		WREG32_DIDT(ixDIDT_SQ_CTRL0, data);
	पूर्ण

	अगर (pi->caps_db_ramping) अणु
		data = RREG32_DIDT(ixDIDT_DB_CTRL0);
		अगर (enable)
			data |= DIDT_DB_CTRL0__DIDT_CTRL_EN_MASK;
		अन्यथा
			data &= ~DIDT_DB_CTRL0__DIDT_CTRL_EN_MASK;
		WREG32_DIDT(ixDIDT_DB_CTRL0, data);
	पूर्ण

	अगर (pi->caps_td_ramping) अणु
		data = RREG32_DIDT(ixDIDT_TD_CTRL0);
		अगर (enable)
			data |= DIDT_TD_CTRL0__DIDT_CTRL_EN_MASK;
		अन्यथा
			data &= ~DIDT_TD_CTRL0__DIDT_CTRL_EN_MASK;
		WREG32_DIDT(ixDIDT_TD_CTRL0, data);
	पूर्ण

	अगर (pi->caps_tcp_ramping) अणु
		data = RREG32_DIDT(ixDIDT_TCP_CTRL0);
		अगर (enable)
			data |= DIDT_TCP_CTRL0__DIDT_CTRL_EN_MASK;
		अन्यथा
			data &= ~DIDT_TCP_CTRL0__DIDT_CTRL_EN_MASK;
		WREG32_DIDT(ixDIDT_TCP_CTRL0, data);
	पूर्ण
पूर्ण

अटल पूर्णांक kv_enable_didt(काष्ठा amdgpu_device *adev, bool enable)
अणु
	काष्ठा kv_घातer_info *pi = kv_get_pi(adev);
	पूर्णांक ret;

	अगर (pi->caps_sq_ramping ||
	    pi->caps_db_ramping ||
	    pi->caps_td_ramping ||
	    pi->caps_tcp_ramping) अणु
		amdgpu_gfx_rlc_enter_safe_mode(adev);

		अगर (enable) अणु
			ret = kv_program_pt_config_रेजिस्टरs(adev, didt_config_kv);
			अगर (ret) अणु
				amdgpu_gfx_rlc_निकास_safe_mode(adev);
				वापस ret;
			पूर्ण
		पूर्ण

		kv_करो_enable_didt(adev, enable);

		amdgpu_gfx_rlc_निकास_safe_mode(adev);
	पूर्ण

	वापस 0;
पूर्ण

#अगर 0
अटल व्योम kv_initialize_hardware_cac_manager(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा kv_घातer_info *pi = kv_get_pi(adev);

	अगर (pi->caps_cac) अणु
		WREG32_SMC(ixLCAC_SX0_OVR_SEL, 0);
		WREG32_SMC(ixLCAC_SX0_OVR_VAL, 0);
		kv_program_local_cac_table(adev, sx_local_cac_cfg_kv, sx0_cac_config_reg);

		WREG32_SMC(ixLCAC_MC0_OVR_SEL, 0);
		WREG32_SMC(ixLCAC_MC0_OVR_VAL, 0);
		kv_program_local_cac_table(adev, mc0_local_cac_cfg_kv, mc0_cac_config_reg);

		WREG32_SMC(ixLCAC_MC1_OVR_SEL, 0);
		WREG32_SMC(ixLCAC_MC1_OVR_VAL, 0);
		kv_program_local_cac_table(adev, mc1_local_cac_cfg_kv, mc1_cac_config_reg);

		WREG32_SMC(ixLCAC_MC2_OVR_SEL, 0);
		WREG32_SMC(ixLCAC_MC2_OVR_VAL, 0);
		kv_program_local_cac_table(adev, mc2_local_cac_cfg_kv, mc2_cac_config_reg);

		WREG32_SMC(ixLCAC_MC3_OVR_SEL, 0);
		WREG32_SMC(ixLCAC_MC3_OVR_VAL, 0);
		kv_program_local_cac_table(adev, mc3_local_cac_cfg_kv, mc3_cac_config_reg);

		WREG32_SMC(ixLCAC_CPL_OVR_SEL, 0);
		WREG32_SMC(ixLCAC_CPL_OVR_VAL, 0);
		kv_program_local_cac_table(adev, cpl_local_cac_cfg_kv, cpl_cac_config_reg);
	पूर्ण
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक kv_enable_smc_cac(काष्ठा amdgpu_device *adev, bool enable)
अणु
	काष्ठा kv_घातer_info *pi = kv_get_pi(adev);
	पूर्णांक ret = 0;

	अगर (pi->caps_cac) अणु
		अगर (enable) अणु
			ret = amdgpu_kv_notअगरy_message_to_smu(adev, PPSMC_MSG_EnableCac);
			अगर (ret)
				pi->cac_enabled = false;
			अन्यथा
				pi->cac_enabled = true;
		पूर्ण अन्यथा अगर (pi->cac_enabled) अणु
			amdgpu_kv_notअगरy_message_to_smu(adev, PPSMC_MSG_DisableCac);
			pi->cac_enabled = false;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक kv_process_firmware_header(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा kv_घातer_info *pi = kv_get_pi(adev);
	u32 पंचांगp;
	पूर्णांक ret;

	ret = amdgpu_kv_पढ़ो_smc_sram_dword(adev, SMU7_FIRMWARE_HEADER_LOCATION +
				     दुरत्व(SMU7_Firmware_Header, DpmTable),
				     &पंचांगp, pi->sram_end);

	अगर (ret == 0)
		pi->dpm_table_start = पंचांगp;

	ret = amdgpu_kv_पढ़ो_smc_sram_dword(adev, SMU7_FIRMWARE_HEADER_LOCATION +
				     दुरत्व(SMU7_Firmware_Header, SoftRegisters),
				     &पंचांगp, pi->sram_end);

	अगर (ret == 0)
		pi->soft_regs_start = पंचांगp;

	वापस ret;
पूर्ण

अटल पूर्णांक kv_enable_dpm_voltage_scaling(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा kv_घातer_info *pi = kv_get_pi(adev);
	पूर्णांक ret;

	pi->graphics_voltage_change_enable = 1;

	ret = amdgpu_kv_copy_bytes_to_smc(adev,
				   pi->dpm_table_start +
				   दुरत्व(SMU7_Fusion_DpmTable, GraphicsVoltageChangeEnable),
				   &pi->graphics_voltage_change_enable,
				   माप(u8), pi->sram_end);

	वापस ret;
पूर्ण

अटल पूर्णांक kv_set_dpm_पूर्णांकerval(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा kv_घातer_info *pi = kv_get_pi(adev);
	पूर्णांक ret;

	pi->graphics_पूर्णांकerval = 1;

	ret = amdgpu_kv_copy_bytes_to_smc(adev,
				   pi->dpm_table_start +
				   दुरत्व(SMU7_Fusion_DpmTable, GraphicsInterval),
				   &pi->graphics_पूर्णांकerval,
				   माप(u8), pi->sram_end);

	वापस ret;
पूर्ण

अटल पूर्णांक kv_set_dpm_boot_state(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा kv_घातer_info *pi = kv_get_pi(adev);
	पूर्णांक ret;

	ret = amdgpu_kv_copy_bytes_to_smc(adev,
				   pi->dpm_table_start +
				   दुरत्व(SMU7_Fusion_DpmTable, GraphicsBootLevel),
				   &pi->graphics_boot_level,
				   माप(u8), pi->sram_end);

	वापस ret;
पूर्ण

अटल व्योम kv_program_vc(काष्ठा amdgpu_device *adev)
अणु
	WREG32_SMC(ixCG_FREQ_TRAN_VOTING_0, 0x3FFFC100);
पूर्ण

अटल व्योम kv_clear_vc(काष्ठा amdgpu_device *adev)
अणु
	WREG32_SMC(ixCG_FREQ_TRAN_VOTING_0, 0);
पूर्ण

अटल पूर्णांक kv_set_भागider_value(काष्ठा amdgpu_device *adev,
				u32 index, u32 sclk)
अणु
	काष्ठा kv_घातer_info *pi = kv_get_pi(adev);
	काष्ठा atom_घड़ी_भागiders भागiders;
	पूर्णांक ret;

	ret = amdgpu_atombios_get_घड़ी_भागiders(adev, COMPUTE_ENGINE_PLL_PARAM,
						 sclk, false, &भागiders);
	अगर (ret)
		वापस ret;

	pi->graphics_level[index].SclkDid = (u8)भागiders.post_भाग;
	pi->graphics_level[index].SclkFrequency = cpu_to_be32(sclk);

	वापस 0;
पूर्ण

अटल u16 kv_convert_8bit_index_to_voltage(काष्ठा amdgpu_device *adev,
					    u16 voltage)
अणु
	वापस 6200 - (voltage * 25);
पूर्ण

अटल u16 kv_convert_2bit_index_to_voltage(काष्ठा amdgpu_device *adev,
					    u32 vid_2bit)
अणु
	काष्ठा kv_घातer_info *pi = kv_get_pi(adev);
	u32 vid_8bit = kv_convert_vid2_to_vid7(adev,
					       &pi->sys_info.vid_mapping_table,
					       vid_2bit);

	वापस kv_convert_8bit_index_to_voltage(adev, (u16)vid_8bit);
पूर्ण


अटल पूर्णांक kv_set_vid(काष्ठा amdgpu_device *adev, u32 index, u32 vid)
अणु
	काष्ठा kv_घातer_info *pi = kv_get_pi(adev);

	pi->graphics_level[index].VoltageDownH = (u8)pi->voltage_drop_t;
	pi->graphics_level[index].MinVddNb =
		cpu_to_be32(kv_convert_2bit_index_to_voltage(adev, vid));

	वापस 0;
पूर्ण

अटल पूर्णांक kv_set_at(काष्ठा amdgpu_device *adev, u32 index, u32 at)
अणु
	काष्ठा kv_घातer_info *pi = kv_get_pi(adev);

	pi->graphics_level[index].AT = cpu_to_be16((u16)at);

	वापस 0;
पूर्ण

अटल व्योम kv_dpm_घातer_level_enable(काष्ठा amdgpu_device *adev,
				      u32 index, bool enable)
अणु
	काष्ठा kv_घातer_info *pi = kv_get_pi(adev);

	pi->graphics_level[index].EnabledForActivity = enable ? 1 : 0;
पूर्ण

अटल व्योम kv_start_dpm(काष्ठा amdgpu_device *adev)
अणु
	u32 पंचांगp = RREG32_SMC(ixGENERAL_PWRMGT);

	पंचांगp |= GENERAL_PWRMGT__GLOBAL_PWRMGT_EN_MASK;
	WREG32_SMC(ixGENERAL_PWRMGT, पंचांगp);

	amdgpu_kv_smc_dpm_enable(adev, true);
पूर्ण

अटल व्योम kv_stop_dpm(काष्ठा amdgpu_device *adev)
अणु
	amdgpu_kv_smc_dpm_enable(adev, false);
पूर्ण

अटल व्योम kv_start_am(काष्ठा amdgpu_device *adev)
अणु
	u32 sclk_pwrmgt_cntl = RREG32_SMC(ixSCLK_PWRMGT_CNTL);

	sclk_pwrmgt_cntl &= ~(SCLK_PWRMGT_CNTL__RESET_SCLK_CNT_MASK |
			SCLK_PWRMGT_CNTL__RESET_BUSY_CNT_MASK);
	sclk_pwrmgt_cntl |= SCLK_PWRMGT_CNTL__DYNAMIC_PM_EN_MASK;

	WREG32_SMC(ixSCLK_PWRMGT_CNTL, sclk_pwrmgt_cntl);
पूर्ण

अटल व्योम kv_reset_am(काष्ठा amdgpu_device *adev)
अणु
	u32 sclk_pwrmgt_cntl = RREG32_SMC(ixSCLK_PWRMGT_CNTL);

	sclk_pwrmgt_cntl |= (SCLK_PWRMGT_CNTL__RESET_SCLK_CNT_MASK |
			SCLK_PWRMGT_CNTL__RESET_BUSY_CNT_MASK);

	WREG32_SMC(ixSCLK_PWRMGT_CNTL, sclk_pwrmgt_cntl);
पूर्ण

अटल पूर्णांक kv_मुक्तze_sclk_dpm(काष्ठा amdgpu_device *adev, bool मुक्तze)
अणु
	वापस amdgpu_kv_notअगरy_message_to_smu(adev, मुक्तze ?
					PPSMC_MSG_SCLKDPM_FreezeLevel : PPSMC_MSG_SCLKDPM_Unमुक्तzeLevel);
पूर्ण

अटल पूर्णांक kv_क्रमce_lowest_valid(काष्ठा amdgpu_device *adev)
अणु
	वापस kv_क्रमce_dpm_lowest(adev);
पूर्ण

अटल पूर्णांक kv_unक्रमce_levels(काष्ठा amdgpu_device *adev)
अणु
	अगर (adev->asic_type == CHIP_KABINI || adev->asic_type == CHIP_MULLINS)
		वापस amdgpu_kv_notअगरy_message_to_smu(adev, PPSMC_MSG_NoForcedLevel);
	अन्यथा
		वापस kv_set_enabled_levels(adev);
पूर्ण

अटल पूर्णांक kv_update_sclk_t(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा kv_घातer_info *pi = kv_get_pi(adev);
	u32 low_sclk_पूर्णांकerrupt_t = 0;
	पूर्णांक ret = 0;

	अगर (pi->caps_sclk_throttle_low_notअगरication) अणु
		low_sclk_पूर्णांकerrupt_t = cpu_to_be32(pi->low_sclk_पूर्णांकerrupt_t);

		ret = amdgpu_kv_copy_bytes_to_smc(adev,
					   pi->dpm_table_start +
					   दुरत्व(SMU7_Fusion_DpmTable, LowSclkInterruptT),
					   (u8 *)&low_sclk_पूर्णांकerrupt_t,
					   माप(u32), pi->sram_end);
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक kv_program_bootup_state(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा kv_घातer_info *pi = kv_get_pi(adev);
	u32 i;
	काष्ठा amdgpu_घड़ी_voltage_dependency_table *table =
		&adev->pm.dpm.dyn_state.vddc_dependency_on_sclk;

	अगर (table && table->count) अणु
		क्रम (i = pi->graphics_dpm_level_count - 1; i > 0; i--) अणु
			अगर (table->entries[i].clk == pi->boot_pl.sclk)
				अवरोध;
		पूर्ण

		pi->graphics_boot_level = (u8)i;
		kv_dpm_घातer_level_enable(adev, i, true);
	पूर्ण अन्यथा अणु
		काष्ठा sumo_sclk_voltage_mapping_table *table =
			&pi->sys_info.sclk_voltage_mapping_table;

		अगर (table->num_max_dpm_entries == 0)
			वापस -EINVAL;

		क्रम (i = pi->graphics_dpm_level_count - 1; i > 0; i--) अणु
			अगर (table->entries[i].sclk_frequency == pi->boot_pl.sclk)
				अवरोध;
		पूर्ण

		pi->graphics_boot_level = (u8)i;
		kv_dpm_घातer_level_enable(adev, i, true);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक kv_enable_स्वतः_thermal_throttling(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा kv_घातer_info *pi = kv_get_pi(adev);
	पूर्णांक ret;

	pi->graphics_therm_throttle_enable = 1;

	ret = amdgpu_kv_copy_bytes_to_smc(adev,
				   pi->dpm_table_start +
				   दुरत्व(SMU7_Fusion_DpmTable, GraphicsThermThrottleEnable),
				   &pi->graphics_therm_throttle_enable,
				   माप(u8), pi->sram_end);

	वापस ret;
पूर्ण

अटल पूर्णांक kv_upload_dpm_settings(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा kv_घातer_info *pi = kv_get_pi(adev);
	पूर्णांक ret;

	ret = amdgpu_kv_copy_bytes_to_smc(adev,
				   pi->dpm_table_start +
				   दुरत्व(SMU7_Fusion_DpmTable, GraphicsLevel),
				   (u8 *)&pi->graphics_level,
				   माप(SMU7_Fusion_GraphicsLevel) * SMU7_MAX_LEVELS_GRAPHICS,
				   pi->sram_end);

	अगर (ret)
		वापस ret;

	ret = amdgpu_kv_copy_bytes_to_smc(adev,
				   pi->dpm_table_start +
				   दुरत्व(SMU7_Fusion_DpmTable, GraphicsDpmLevelCount),
				   &pi->graphics_dpm_level_count,
				   माप(u8), pi->sram_end);

	वापस ret;
पूर्ण

अटल u32 kv_get_घड़ी_dअगरference(u32 a, u32 b)
अणु
	वापस (a >= b) ? a - b : b - a;
पूर्ण

अटल u32 kv_get_clk_bypass(काष्ठा amdgpu_device *adev, u32 clk)
अणु
	काष्ठा kv_घातer_info *pi = kv_get_pi(adev);
	u32 value;

	अगर (pi->caps_enable_dfs_bypass) अणु
		अगर (kv_get_घड़ी_dअगरference(clk, 40000) < 200)
			value = 3;
		अन्यथा अगर (kv_get_घड़ी_dअगरference(clk, 30000) < 200)
			value = 2;
		अन्यथा अगर (kv_get_घड़ी_dअगरference(clk, 20000) < 200)
			value = 7;
		अन्यथा अगर (kv_get_घड़ी_dअगरference(clk, 15000) < 200)
			value = 6;
		अन्यथा अगर (kv_get_घड़ी_dअगरference(clk, 10000) < 200)
			value = 8;
		अन्यथा
			value = 0;
	पूर्ण अन्यथा अणु
		value = 0;
	पूर्ण

	वापस value;
पूर्ण

अटल पूर्णांक kv_populate_uvd_table(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा kv_घातer_info *pi = kv_get_pi(adev);
	काष्ठा amdgpu_uvd_घड़ी_voltage_dependency_table *table =
		&adev->pm.dpm.dyn_state.uvd_घड़ी_voltage_dependency_table;
	काष्ठा atom_घड़ी_भागiders भागiders;
	पूर्णांक ret;
	u32 i;

	अगर (table == शून्य || table->count == 0)
		वापस 0;

	pi->uvd_level_count = 0;
	क्रम (i = 0; i < table->count; i++) अणु
		अगर (pi->high_voltage_t &&
		    (pi->high_voltage_t < table->entries[i].v))
			अवरोध;

		pi->uvd_level[i].VclkFrequency = cpu_to_be32(table->entries[i].vclk);
		pi->uvd_level[i].DclkFrequency = cpu_to_be32(table->entries[i].dclk);
		pi->uvd_level[i].MinVddNb = cpu_to_be16(table->entries[i].v);

		pi->uvd_level[i].VClkBypassCntl =
			(u8)kv_get_clk_bypass(adev, table->entries[i].vclk);
		pi->uvd_level[i].DClkBypassCntl =
			(u8)kv_get_clk_bypass(adev, table->entries[i].dclk);

		ret = amdgpu_atombios_get_घड़ी_भागiders(adev, COMPUTE_ENGINE_PLL_PARAM,
							 table->entries[i].vclk, false, &भागiders);
		अगर (ret)
			वापस ret;
		pi->uvd_level[i].VclkDivider = (u8)भागiders.post_भाग;

		ret = amdgpu_atombios_get_घड़ी_भागiders(adev, COMPUTE_ENGINE_PLL_PARAM,
							 table->entries[i].dclk, false, &भागiders);
		अगर (ret)
			वापस ret;
		pi->uvd_level[i].DclkDivider = (u8)भागiders.post_भाग;

		pi->uvd_level_count++;
	पूर्ण

	ret = amdgpu_kv_copy_bytes_to_smc(adev,
				   pi->dpm_table_start +
				   दुरत्व(SMU7_Fusion_DpmTable, UvdLevelCount),
				   (u8 *)&pi->uvd_level_count,
				   माप(u8), pi->sram_end);
	अगर (ret)
		वापस ret;

	pi->uvd_पूर्णांकerval = 1;

	ret = amdgpu_kv_copy_bytes_to_smc(adev,
				   pi->dpm_table_start +
				   दुरत्व(SMU7_Fusion_DpmTable, UVDInterval),
				   &pi->uvd_पूर्णांकerval,
				   माप(u8), pi->sram_end);
	अगर (ret)
		वापस ret;

	ret = amdgpu_kv_copy_bytes_to_smc(adev,
				   pi->dpm_table_start +
				   दुरत्व(SMU7_Fusion_DpmTable, UvdLevel),
				   (u8 *)&pi->uvd_level,
				   माप(SMU7_Fusion_UvdLevel) * SMU7_MAX_LEVELS_UVD,
				   pi->sram_end);

	वापस ret;

पूर्ण

अटल पूर्णांक kv_populate_vce_table(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा kv_घातer_info *pi = kv_get_pi(adev);
	पूर्णांक ret;
	u32 i;
	काष्ठा amdgpu_vce_घड़ी_voltage_dependency_table *table =
		&adev->pm.dpm.dyn_state.vce_घड़ी_voltage_dependency_table;
	काष्ठा atom_घड़ी_भागiders भागiders;

	अगर (table == शून्य || table->count == 0)
		वापस 0;

	pi->vce_level_count = 0;
	क्रम (i = 0; i < table->count; i++) अणु
		अगर (pi->high_voltage_t &&
		    pi->high_voltage_t < table->entries[i].v)
			अवरोध;

		pi->vce_level[i].Frequency = cpu_to_be32(table->entries[i].evclk);
		pi->vce_level[i].MinVoltage = cpu_to_be16(table->entries[i].v);

		pi->vce_level[i].ClkBypassCntl =
			(u8)kv_get_clk_bypass(adev, table->entries[i].evclk);

		ret = amdgpu_atombios_get_घड़ी_भागiders(adev, COMPUTE_ENGINE_PLL_PARAM,
							 table->entries[i].evclk, false, &भागiders);
		अगर (ret)
			वापस ret;
		pi->vce_level[i].Divider = (u8)भागiders.post_भाग;

		pi->vce_level_count++;
	पूर्ण

	ret = amdgpu_kv_copy_bytes_to_smc(adev,
				   pi->dpm_table_start +
				   दुरत्व(SMU7_Fusion_DpmTable, VceLevelCount),
				   (u8 *)&pi->vce_level_count,
				   माप(u8),
				   pi->sram_end);
	अगर (ret)
		वापस ret;

	pi->vce_पूर्णांकerval = 1;

	ret = amdgpu_kv_copy_bytes_to_smc(adev,
				   pi->dpm_table_start +
				   दुरत्व(SMU7_Fusion_DpmTable, VCEInterval),
				   (u8 *)&pi->vce_पूर्णांकerval,
				   माप(u8),
				   pi->sram_end);
	अगर (ret)
		वापस ret;

	ret = amdgpu_kv_copy_bytes_to_smc(adev,
				   pi->dpm_table_start +
				   दुरत्व(SMU7_Fusion_DpmTable, VceLevel),
				   (u8 *)&pi->vce_level,
				   माप(SMU7_Fusion_ExtClkLevel) * SMU7_MAX_LEVELS_VCE,
				   pi->sram_end);

	वापस ret;
पूर्ण

अटल पूर्णांक kv_populate_samu_table(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा kv_घातer_info *pi = kv_get_pi(adev);
	काष्ठा amdgpu_घड़ी_voltage_dependency_table *table =
		&adev->pm.dpm.dyn_state.samu_घड़ी_voltage_dependency_table;
	काष्ठा atom_घड़ी_भागiders भागiders;
	पूर्णांक ret;
	u32 i;

	अगर (table == शून्य || table->count == 0)
		वापस 0;

	pi->samu_level_count = 0;
	क्रम (i = 0; i < table->count; i++) अणु
		अगर (pi->high_voltage_t &&
		    pi->high_voltage_t < table->entries[i].v)
			अवरोध;

		pi->samu_level[i].Frequency = cpu_to_be32(table->entries[i].clk);
		pi->samu_level[i].MinVoltage = cpu_to_be16(table->entries[i].v);

		pi->samu_level[i].ClkBypassCntl =
			(u8)kv_get_clk_bypass(adev, table->entries[i].clk);

		ret = amdgpu_atombios_get_घड़ी_भागiders(adev, COMPUTE_ENGINE_PLL_PARAM,
							 table->entries[i].clk, false, &भागiders);
		अगर (ret)
			वापस ret;
		pi->samu_level[i].Divider = (u8)भागiders.post_भाग;

		pi->samu_level_count++;
	पूर्ण

	ret = amdgpu_kv_copy_bytes_to_smc(adev,
				   pi->dpm_table_start +
				   दुरत्व(SMU7_Fusion_DpmTable, SamuLevelCount),
				   (u8 *)&pi->samu_level_count,
				   माप(u8),
				   pi->sram_end);
	अगर (ret)
		वापस ret;

	pi->samu_पूर्णांकerval = 1;

	ret = amdgpu_kv_copy_bytes_to_smc(adev,
				   pi->dpm_table_start +
				   दुरत्व(SMU7_Fusion_DpmTable, SAMUInterval),
				   (u8 *)&pi->samu_पूर्णांकerval,
				   माप(u8),
				   pi->sram_end);
	अगर (ret)
		वापस ret;

	ret = amdgpu_kv_copy_bytes_to_smc(adev,
				   pi->dpm_table_start +
				   दुरत्व(SMU7_Fusion_DpmTable, SamuLevel),
				   (u8 *)&pi->samu_level,
				   माप(SMU7_Fusion_ExtClkLevel) * SMU7_MAX_LEVELS_SAMU,
				   pi->sram_end);
	अगर (ret)
		वापस ret;

	वापस ret;
पूर्ण


अटल पूर्णांक kv_populate_acp_table(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा kv_घातer_info *pi = kv_get_pi(adev);
	काष्ठा amdgpu_घड़ी_voltage_dependency_table *table =
		&adev->pm.dpm.dyn_state.acp_घड़ी_voltage_dependency_table;
	काष्ठा atom_घड़ी_भागiders भागiders;
	पूर्णांक ret;
	u32 i;

	अगर (table == शून्य || table->count == 0)
		वापस 0;

	pi->acp_level_count = 0;
	क्रम (i = 0; i < table->count; i++) अणु
		pi->acp_level[i].Frequency = cpu_to_be32(table->entries[i].clk);
		pi->acp_level[i].MinVoltage = cpu_to_be16(table->entries[i].v);

		ret = amdgpu_atombios_get_घड़ी_भागiders(adev, COMPUTE_ENGINE_PLL_PARAM,
							 table->entries[i].clk, false, &भागiders);
		अगर (ret)
			वापस ret;
		pi->acp_level[i].Divider = (u8)भागiders.post_भाग;

		pi->acp_level_count++;
	पूर्ण

	ret = amdgpu_kv_copy_bytes_to_smc(adev,
				   pi->dpm_table_start +
				   दुरत्व(SMU7_Fusion_DpmTable, AcpLevelCount),
				   (u8 *)&pi->acp_level_count,
				   माप(u8),
				   pi->sram_end);
	अगर (ret)
		वापस ret;

	pi->acp_पूर्णांकerval = 1;

	ret = amdgpu_kv_copy_bytes_to_smc(adev,
				   pi->dpm_table_start +
				   दुरत्व(SMU7_Fusion_DpmTable, ACPInterval),
				   (u8 *)&pi->acp_पूर्णांकerval,
				   माप(u8),
				   pi->sram_end);
	अगर (ret)
		वापस ret;

	ret = amdgpu_kv_copy_bytes_to_smc(adev,
				   pi->dpm_table_start +
				   दुरत्व(SMU7_Fusion_DpmTable, AcpLevel),
				   (u8 *)&pi->acp_level,
				   माप(SMU7_Fusion_ExtClkLevel) * SMU7_MAX_LEVELS_ACP,
				   pi->sram_end);
	अगर (ret)
		वापस ret;

	वापस ret;
पूर्ण

अटल व्योम kv_calculate_dfs_bypass_settings(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा kv_घातer_info *pi = kv_get_pi(adev);
	u32 i;
	काष्ठा amdgpu_घड़ी_voltage_dependency_table *table =
		&adev->pm.dpm.dyn_state.vddc_dependency_on_sclk;

	अगर (table && table->count) अणु
		क्रम (i = 0; i < pi->graphics_dpm_level_count; i++) अणु
			अगर (pi->caps_enable_dfs_bypass) अणु
				अगर (kv_get_घड़ी_dअगरference(table->entries[i].clk, 40000) < 200)
					pi->graphics_level[i].ClkBypassCntl = 3;
				अन्यथा अगर (kv_get_घड़ी_dअगरference(table->entries[i].clk, 30000) < 200)
					pi->graphics_level[i].ClkBypassCntl = 2;
				अन्यथा अगर (kv_get_घड़ी_dअगरference(table->entries[i].clk, 26600) < 200)
					pi->graphics_level[i].ClkBypassCntl = 7;
				अन्यथा अगर (kv_get_घड़ी_dअगरference(table->entries[i].clk , 20000) < 200)
					pi->graphics_level[i].ClkBypassCntl = 6;
				अन्यथा अगर (kv_get_घड़ी_dअगरference(table->entries[i].clk , 10000) < 200)
					pi->graphics_level[i].ClkBypassCntl = 8;
				अन्यथा
					pi->graphics_level[i].ClkBypassCntl = 0;
			पूर्ण अन्यथा अणु
				pi->graphics_level[i].ClkBypassCntl = 0;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		काष्ठा sumo_sclk_voltage_mapping_table *table =
			&pi->sys_info.sclk_voltage_mapping_table;
		क्रम (i = 0; i < pi->graphics_dpm_level_count; i++) अणु
			अगर (pi->caps_enable_dfs_bypass) अणु
				अगर (kv_get_घड़ी_dअगरference(table->entries[i].sclk_frequency, 40000) < 200)
					pi->graphics_level[i].ClkBypassCntl = 3;
				अन्यथा अगर (kv_get_घड़ी_dअगरference(table->entries[i].sclk_frequency, 30000) < 200)
					pi->graphics_level[i].ClkBypassCntl = 2;
				अन्यथा अगर (kv_get_घड़ी_dअगरference(table->entries[i].sclk_frequency, 26600) < 200)
					pi->graphics_level[i].ClkBypassCntl = 7;
				अन्यथा अगर (kv_get_घड़ी_dअगरference(table->entries[i].sclk_frequency, 20000) < 200)
					pi->graphics_level[i].ClkBypassCntl = 6;
				अन्यथा अगर (kv_get_घड़ी_dअगरference(table->entries[i].sclk_frequency, 10000) < 200)
					pi->graphics_level[i].ClkBypassCntl = 8;
				अन्यथा
					pi->graphics_level[i].ClkBypassCntl = 0;
			पूर्ण अन्यथा अणु
				pi->graphics_level[i].ClkBypassCntl = 0;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक kv_enable_ulv(काष्ठा amdgpu_device *adev, bool enable)
अणु
	वापस amdgpu_kv_notअगरy_message_to_smu(adev, enable ?
					PPSMC_MSG_EnableULV : PPSMC_MSG_DisableULV);
पूर्ण

अटल व्योम kv_reset_acp_boot_level(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा kv_घातer_info *pi = kv_get_pi(adev);

	pi->acp_boot_level = 0xff;
पूर्ण

अटल व्योम kv_update_current_ps(काष्ठा amdgpu_device *adev,
				 काष्ठा amdgpu_ps *rps)
अणु
	काष्ठा kv_ps *new_ps = kv_get_ps(rps);
	काष्ठा kv_घातer_info *pi = kv_get_pi(adev);

	pi->current_rps = *rps;
	pi->current_ps = *new_ps;
	pi->current_rps.ps_priv = &pi->current_ps;
	adev->pm.dpm.current_ps = &pi->current_rps;
पूर्ण

अटल व्योम kv_update_requested_ps(काष्ठा amdgpu_device *adev,
				   काष्ठा amdgpu_ps *rps)
अणु
	काष्ठा kv_ps *new_ps = kv_get_ps(rps);
	काष्ठा kv_घातer_info *pi = kv_get_pi(adev);

	pi->requested_rps = *rps;
	pi->requested_ps = *new_ps;
	pi->requested_rps.ps_priv = &pi->requested_ps;
	adev->pm.dpm.requested_ps = &pi->requested_rps;
पूर्ण

अटल व्योम kv_dpm_enable_bapm(व्योम *handle, bool enable)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;
	काष्ठा kv_घातer_info *pi = kv_get_pi(adev);
	पूर्णांक ret;

	अगर (pi->bapm_enable) अणु
		ret = amdgpu_kv_smc_bapm_enable(adev, enable);
		अगर (ret)
			DRM_ERROR("amdgpu_kv_smc_bapm_enable failed\n");
	पूर्ण
पूर्ण

अटल पूर्णांक kv_dpm_enable(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा kv_घातer_info *pi = kv_get_pi(adev);
	पूर्णांक ret;

	ret = kv_process_firmware_header(adev);
	अगर (ret) अणु
		DRM_ERROR("kv_process_firmware_header failed\n");
		वापस ret;
	पूर्ण
	kv_init_fps_limits(adev);
	kv_init_graphics_levels(adev);
	ret = kv_program_bootup_state(adev);
	अगर (ret) अणु
		DRM_ERROR("kv_program_bootup_state failed\n");
		वापस ret;
	पूर्ण
	kv_calculate_dfs_bypass_settings(adev);
	ret = kv_upload_dpm_settings(adev);
	अगर (ret) अणु
		DRM_ERROR("kv_upload_dpm_settings failed\n");
		वापस ret;
	पूर्ण
	ret = kv_populate_uvd_table(adev);
	अगर (ret) अणु
		DRM_ERROR("kv_populate_uvd_table failed\n");
		वापस ret;
	पूर्ण
	ret = kv_populate_vce_table(adev);
	अगर (ret) अणु
		DRM_ERROR("kv_populate_vce_table failed\n");
		वापस ret;
	पूर्ण
	ret = kv_populate_samu_table(adev);
	अगर (ret) अणु
		DRM_ERROR("kv_populate_samu_table failed\n");
		वापस ret;
	पूर्ण
	ret = kv_populate_acp_table(adev);
	अगर (ret) अणु
		DRM_ERROR("kv_populate_acp_table failed\n");
		वापस ret;
	पूर्ण
	kv_program_vc(adev);
#अगर 0
	kv_initialize_hardware_cac_manager(adev);
#पूर्ण_अगर
	kv_start_am(adev);
	अगर (pi->enable_स्वतः_thermal_throttling) अणु
		ret = kv_enable_स्वतः_thermal_throttling(adev);
		अगर (ret) अणु
			DRM_ERROR("kv_enable_auto_thermal_throttling failed\n");
			वापस ret;
		पूर्ण
	पूर्ण
	ret = kv_enable_dpm_voltage_scaling(adev);
	अगर (ret) अणु
		DRM_ERROR("kv_enable_dpm_voltage_scaling failed\n");
		वापस ret;
	पूर्ण
	ret = kv_set_dpm_पूर्णांकerval(adev);
	अगर (ret) अणु
		DRM_ERROR("kv_set_dpm_interval failed\n");
		वापस ret;
	पूर्ण
	ret = kv_set_dpm_boot_state(adev);
	अगर (ret) अणु
		DRM_ERROR("kv_set_dpm_boot_state failed\n");
		वापस ret;
	पूर्ण
	ret = kv_enable_ulv(adev, true);
	अगर (ret) अणु
		DRM_ERROR("kv_enable_ulv failed\n");
		वापस ret;
	पूर्ण
	kv_start_dpm(adev);
	ret = kv_enable_didt(adev, true);
	अगर (ret) अणु
		DRM_ERROR("kv_enable_didt failed\n");
		वापस ret;
	पूर्ण
	ret = kv_enable_smc_cac(adev, true);
	अगर (ret) अणु
		DRM_ERROR("kv_enable_smc_cac failed\n");
		वापस ret;
	पूर्ण

	kv_reset_acp_boot_level(adev);

	ret = amdgpu_kv_smc_bapm_enable(adev, false);
	अगर (ret) अणु
		DRM_ERROR("amdgpu_kv_smc_bapm_enable failed\n");
		वापस ret;
	पूर्ण

	अगर (adev->irq.installed &&
	    amdgpu_is_पूर्णांकernal_thermal_sensor(adev->pm.पूर्णांक_thermal_type)) अणु
		ret = kv_set_thermal_temperature_range(adev, KV_TEMP_RANGE_MIN, KV_TEMP_RANGE_MAX);
		अगर (ret) अणु
			DRM_ERROR("kv_set_thermal_temperature_range failed\n");
			वापस ret;
		पूर्ण
		amdgpu_irq_get(adev, &adev->pm.dpm.thermal.irq,
			       AMDGPU_THERMAL_IRQ_LOW_TO_HIGH);
		amdgpu_irq_get(adev, &adev->pm.dpm.thermal.irq,
			       AMDGPU_THERMAL_IRQ_HIGH_TO_LOW);
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम kv_dpm_disable(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा kv_घातer_info *pi = kv_get_pi(adev);

	amdgpu_irq_put(adev, &adev->pm.dpm.thermal.irq,
		       AMDGPU_THERMAL_IRQ_LOW_TO_HIGH);
	amdgpu_irq_put(adev, &adev->pm.dpm.thermal.irq,
		       AMDGPU_THERMAL_IRQ_HIGH_TO_LOW);

	amdgpu_kv_smc_bapm_enable(adev, false);

	अगर (adev->asic_type == CHIP_MULLINS)
		kv_enable_nb_dpm(adev, false);

	/* घातerup blocks */
	kv_dpm_घातergate_acp(adev, false);
	kv_dpm_घातergate_samu(adev, false);
	अगर (pi->caps_vce_pg) /* घातer on the VCE block */
		amdgpu_kv_notअगरy_message_to_smu(adev, PPSMC_MSG_VCEPowerON);
	अगर (pi->caps_uvd_pg) /* घातer on the UVD block */
		amdgpu_kv_notअगरy_message_to_smu(adev, PPSMC_MSG_UVDPowerON);

	kv_enable_smc_cac(adev, false);
	kv_enable_didt(adev, false);
	kv_clear_vc(adev);
	kv_stop_dpm(adev);
	kv_enable_ulv(adev, false);
	kv_reset_am(adev);

	kv_update_current_ps(adev, adev->pm.dpm.boot_ps);
पूर्ण

#अगर 0
अटल पूर्णांक kv_ग_लिखो_smc_soft_रेजिस्टर(काष्ठा amdgpu_device *adev,
				      u16 reg_offset, u32 value)
अणु
	काष्ठा kv_घातer_info *pi = kv_get_pi(adev);

	वापस amdgpu_kv_copy_bytes_to_smc(adev, pi->soft_regs_start + reg_offset,
				    (u8 *)&value, माप(u16), pi->sram_end);
पूर्ण

अटल पूर्णांक kv_पढ़ो_smc_soft_रेजिस्टर(काष्ठा amdgpu_device *adev,
				     u16 reg_offset, u32 *value)
अणु
	काष्ठा kv_घातer_info *pi = kv_get_pi(adev);

	वापस amdgpu_kv_पढ़ो_smc_sram_dword(adev, pi->soft_regs_start + reg_offset,
				      value, pi->sram_end);
पूर्ण
#पूर्ण_अगर

अटल व्योम kv_init_sclk_t(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा kv_घातer_info *pi = kv_get_pi(adev);

	pi->low_sclk_पूर्णांकerrupt_t = 0;
पूर्ण

अटल पूर्णांक kv_init_fps_limits(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा kv_घातer_info *pi = kv_get_pi(adev);
	पूर्णांक ret = 0;

	अगर (pi->caps_fps) अणु
		u16 पंचांगp;

		पंचांगp = 45;
		pi->fps_high_t = cpu_to_be16(पंचांगp);
		ret = amdgpu_kv_copy_bytes_to_smc(adev,
					   pi->dpm_table_start +
					   दुरत्व(SMU7_Fusion_DpmTable, FpsHighT),
					   (u8 *)&pi->fps_high_t,
					   माप(u16), pi->sram_end);

		पंचांगp = 30;
		pi->fps_low_t = cpu_to_be16(पंचांगp);

		ret = amdgpu_kv_copy_bytes_to_smc(adev,
					   pi->dpm_table_start +
					   दुरत्व(SMU7_Fusion_DpmTable, FpsLowT),
					   (u8 *)&pi->fps_low_t,
					   माप(u16), pi->sram_end);

	पूर्ण
	वापस ret;
पूर्ण

अटल व्योम kv_init_घातergate_state(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा kv_घातer_info *pi = kv_get_pi(adev);

	pi->uvd_घातer_gated = false;
	pi->vce_घातer_gated = false;
	pi->samu_घातer_gated = false;
	pi->acp_घातer_gated = false;

पूर्ण

अटल पूर्णांक kv_enable_uvd_dpm(काष्ठा amdgpu_device *adev, bool enable)
अणु
	वापस amdgpu_kv_notअगरy_message_to_smu(adev, enable ?
					PPSMC_MSG_UVDDPM_Enable : PPSMC_MSG_UVDDPM_Disable);
पूर्ण

अटल पूर्णांक kv_enable_vce_dpm(काष्ठा amdgpu_device *adev, bool enable)
अणु
	वापस amdgpu_kv_notअगरy_message_to_smu(adev, enable ?
					PPSMC_MSG_VCEDPM_Enable : PPSMC_MSG_VCEDPM_Disable);
पूर्ण

अटल पूर्णांक kv_enable_samu_dpm(काष्ठा amdgpu_device *adev, bool enable)
अणु
	वापस amdgpu_kv_notअगरy_message_to_smu(adev, enable ?
					PPSMC_MSG_SAMUDPM_Enable : PPSMC_MSG_SAMUDPM_Disable);
पूर्ण

अटल पूर्णांक kv_enable_acp_dpm(काष्ठा amdgpu_device *adev, bool enable)
अणु
	वापस amdgpu_kv_notअगरy_message_to_smu(adev, enable ?
					PPSMC_MSG_ACPDPM_Enable : PPSMC_MSG_ACPDPM_Disable);
पूर्ण

अटल पूर्णांक kv_update_uvd_dpm(काष्ठा amdgpu_device *adev, bool gate)
अणु
	काष्ठा kv_घातer_info *pi = kv_get_pi(adev);
	काष्ठा amdgpu_uvd_घड़ी_voltage_dependency_table *table =
		&adev->pm.dpm.dyn_state.uvd_घड़ी_voltage_dependency_table;
	पूर्णांक ret;
	u32 mask;

	अगर (!gate) अणु
		अगर (table->count)
			pi->uvd_boot_level = table->count - 1;
		अन्यथा
			pi->uvd_boot_level = 0;

		अगर (!pi->caps_uvd_dpm || pi->caps_stable_p_state) अणु
			mask = 1 << pi->uvd_boot_level;
		पूर्ण अन्यथा अणु
			mask = 0x1f;
		पूर्ण

		ret = amdgpu_kv_copy_bytes_to_smc(adev,
					   pi->dpm_table_start +
					   दुरत्व(SMU7_Fusion_DpmTable, UvdBootLevel),
					   (uपूर्णांक8_t *)&pi->uvd_boot_level,
					   माप(u8), pi->sram_end);
		अगर (ret)
			वापस ret;

		amdgpu_kv_send_msg_to_smc_with_parameter(adev,
						  PPSMC_MSG_UVDDPM_SetEnabledMask,
						  mask);
	पूर्ण

	वापस kv_enable_uvd_dpm(adev, !gate);
पूर्ण

अटल u8 kv_get_vce_boot_level(काष्ठा amdgpu_device *adev, u32 evclk)
अणु
	u8 i;
	काष्ठा amdgpu_vce_घड़ी_voltage_dependency_table *table =
		&adev->pm.dpm.dyn_state.vce_घड़ी_voltage_dependency_table;

	क्रम (i = 0; i < table->count; i++) अणु
		अगर (table->entries[i].evclk >= evclk)
			अवरोध;
	पूर्ण

	वापस i;
पूर्ण

अटल पूर्णांक kv_update_vce_dpm(काष्ठा amdgpu_device *adev,
			     काष्ठा amdgpu_ps *amdgpu_new_state,
			     काष्ठा amdgpu_ps *amdgpu_current_state)
अणु
	काष्ठा kv_घातer_info *pi = kv_get_pi(adev);
	काष्ठा amdgpu_vce_घड़ी_voltage_dependency_table *table =
		&adev->pm.dpm.dyn_state.vce_घड़ी_voltage_dependency_table;
	पूर्णांक ret;

	अगर (amdgpu_new_state->evclk > 0 && amdgpu_current_state->evclk == 0) अणु
		अगर (pi->caps_stable_p_state)
			pi->vce_boot_level = table->count - 1;
		अन्यथा
			pi->vce_boot_level = kv_get_vce_boot_level(adev, amdgpu_new_state->evclk);

		ret = amdgpu_kv_copy_bytes_to_smc(adev,
					   pi->dpm_table_start +
					   दुरत्व(SMU7_Fusion_DpmTable, VceBootLevel),
					   (u8 *)&pi->vce_boot_level,
					   माप(u8),
					   pi->sram_end);
		अगर (ret)
			वापस ret;

		अगर (pi->caps_stable_p_state)
			amdgpu_kv_send_msg_to_smc_with_parameter(adev,
							  PPSMC_MSG_VCEDPM_SetEnabledMask,
							  (1 << pi->vce_boot_level));
		kv_enable_vce_dpm(adev, true);
	पूर्ण अन्यथा अगर (amdgpu_new_state->evclk == 0 && amdgpu_current_state->evclk > 0) अणु
		kv_enable_vce_dpm(adev, false);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक kv_update_samu_dpm(काष्ठा amdgpu_device *adev, bool gate)
अणु
	काष्ठा kv_घातer_info *pi = kv_get_pi(adev);
	काष्ठा amdgpu_घड़ी_voltage_dependency_table *table =
		&adev->pm.dpm.dyn_state.samu_घड़ी_voltage_dependency_table;
	पूर्णांक ret;

	अगर (!gate) अणु
		अगर (pi->caps_stable_p_state)
			pi->samu_boot_level = table->count - 1;
		अन्यथा
			pi->samu_boot_level = 0;

		ret = amdgpu_kv_copy_bytes_to_smc(adev,
					   pi->dpm_table_start +
					   दुरत्व(SMU7_Fusion_DpmTable, SamuBootLevel),
					   (u8 *)&pi->samu_boot_level,
					   माप(u8),
					   pi->sram_end);
		अगर (ret)
			वापस ret;

		अगर (pi->caps_stable_p_state)
			amdgpu_kv_send_msg_to_smc_with_parameter(adev,
							  PPSMC_MSG_SAMUDPM_SetEnabledMask,
							  (1 << pi->samu_boot_level));
	पूर्ण

	वापस kv_enable_samu_dpm(adev, !gate);
पूर्ण

अटल u8 kv_get_acp_boot_level(काष्ठा amdgpu_device *adev)
अणु
	u8 i;
	काष्ठा amdgpu_घड़ी_voltage_dependency_table *table =
		&adev->pm.dpm.dyn_state.acp_घड़ी_voltage_dependency_table;

	क्रम (i = 0; i < table->count; i++) अणु
		अगर (table->entries[i].clk >= 0) /* XXX */
			अवरोध;
	पूर्ण

	अगर (i >= table->count)
		i = table->count - 1;

	वापस i;
पूर्ण

अटल व्योम kv_update_acp_boot_level(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा kv_घातer_info *pi = kv_get_pi(adev);
	u8 acp_boot_level;

	अगर (!pi->caps_stable_p_state) अणु
		acp_boot_level = kv_get_acp_boot_level(adev);
		अगर (acp_boot_level != pi->acp_boot_level) अणु
			pi->acp_boot_level = acp_boot_level;
			amdgpu_kv_send_msg_to_smc_with_parameter(adev,
							  PPSMC_MSG_ACPDPM_SetEnabledMask,
							  (1 << pi->acp_boot_level));
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक kv_update_acp_dpm(काष्ठा amdgpu_device *adev, bool gate)
अणु
	काष्ठा kv_घातer_info *pi = kv_get_pi(adev);
	काष्ठा amdgpu_घड़ी_voltage_dependency_table *table =
		&adev->pm.dpm.dyn_state.acp_घड़ी_voltage_dependency_table;
	पूर्णांक ret;

	अगर (!gate) अणु
		अगर (pi->caps_stable_p_state)
			pi->acp_boot_level = table->count - 1;
		अन्यथा
			pi->acp_boot_level = kv_get_acp_boot_level(adev);

		ret = amdgpu_kv_copy_bytes_to_smc(adev,
					   pi->dpm_table_start +
					   दुरत्व(SMU7_Fusion_DpmTable, AcpBootLevel),
					   (u8 *)&pi->acp_boot_level,
					   माप(u8),
					   pi->sram_end);
		अगर (ret)
			वापस ret;

		अगर (pi->caps_stable_p_state)
			amdgpu_kv_send_msg_to_smc_with_parameter(adev,
							  PPSMC_MSG_ACPDPM_SetEnabledMask,
							  (1 << pi->acp_boot_level));
	पूर्ण

	वापस kv_enable_acp_dpm(adev, !gate);
पूर्ण

अटल व्योम kv_dpm_घातergate_uvd(व्योम *handle, bool gate)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;
	काष्ठा kv_घातer_info *pi = kv_get_pi(adev);

	pi->uvd_घातer_gated = gate;

	अगर (gate) अणु
		/* stop the UVD block */
		amdgpu_device_ip_set_घातergating_state(adev, AMD_IP_BLOCK_TYPE_UVD,
						       AMD_PG_STATE_GATE);
		kv_update_uvd_dpm(adev, gate);
		अगर (pi->caps_uvd_pg)
			/* घातer off the UVD block */
			amdgpu_kv_notअगरy_message_to_smu(adev, PPSMC_MSG_UVDPowerOFF);
	पूर्ण अन्यथा अणु
		अगर (pi->caps_uvd_pg)
			/* घातer on the UVD block */
			amdgpu_kv_notअगरy_message_to_smu(adev, PPSMC_MSG_UVDPowerON);
			/* re-init the UVD block */
		kv_update_uvd_dpm(adev, gate);

		amdgpu_device_ip_set_घातergating_state(adev, AMD_IP_BLOCK_TYPE_UVD,
						       AMD_PG_STATE_UNGATE);
	पूर्ण
पूर्ण

अटल व्योम kv_dpm_घातergate_vce(व्योम *handle, bool gate)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;
	काष्ठा kv_घातer_info *pi = kv_get_pi(adev);

	pi->vce_घातer_gated = gate;

	अगर (gate) अणु
		/* stop the VCE block */
		amdgpu_device_ip_set_घातergating_state(adev, AMD_IP_BLOCK_TYPE_VCE,
						       AMD_PG_STATE_GATE);
		kv_enable_vce_dpm(adev, false);
		अगर (pi->caps_vce_pg) /* घातer off the VCE block */
			amdgpu_kv_notअगरy_message_to_smu(adev, PPSMC_MSG_VCEPowerOFF);
	पूर्ण अन्यथा अणु
		अगर (pi->caps_vce_pg) /* घातer on the VCE block */
			amdgpu_kv_notअगरy_message_to_smu(adev, PPSMC_MSG_VCEPowerON);
		kv_enable_vce_dpm(adev, true);
		/* re-init the VCE block */
		amdgpu_device_ip_set_घातergating_state(adev, AMD_IP_BLOCK_TYPE_VCE,
						       AMD_PG_STATE_UNGATE);
	पूर्ण
पूर्ण


अटल व्योम kv_dpm_घातergate_samu(काष्ठा amdgpu_device *adev, bool gate)
अणु
	काष्ठा kv_घातer_info *pi = kv_get_pi(adev);

	अगर (pi->samu_घातer_gated == gate)
		वापस;

	pi->samu_घातer_gated = gate;

	अगर (gate) अणु
		kv_update_samu_dpm(adev, true);
		अगर (pi->caps_samu_pg)
			amdgpu_kv_notअगरy_message_to_smu(adev, PPSMC_MSG_SAMPowerOFF);
	पूर्ण अन्यथा अणु
		अगर (pi->caps_samu_pg)
			amdgpu_kv_notअगरy_message_to_smu(adev, PPSMC_MSG_SAMPowerON);
		kv_update_samu_dpm(adev, false);
	पूर्ण
पूर्ण

अटल व्योम kv_dpm_घातergate_acp(काष्ठा amdgpu_device *adev, bool gate)
अणु
	काष्ठा kv_घातer_info *pi = kv_get_pi(adev);

	अगर (pi->acp_घातer_gated == gate)
		वापस;

	अगर (adev->asic_type == CHIP_KABINI || adev->asic_type == CHIP_MULLINS)
		वापस;

	pi->acp_घातer_gated = gate;

	अगर (gate) अणु
		kv_update_acp_dpm(adev, true);
		अगर (pi->caps_acp_pg)
			amdgpu_kv_notअगरy_message_to_smu(adev, PPSMC_MSG_ACPPowerOFF);
	पूर्ण अन्यथा अणु
		अगर (pi->caps_acp_pg)
			amdgpu_kv_notअगरy_message_to_smu(adev, PPSMC_MSG_ACPPowerON);
		kv_update_acp_dpm(adev, false);
	पूर्ण
पूर्ण

अटल व्योम kv_set_valid_घड़ी_range(काष्ठा amdgpu_device *adev,
				     काष्ठा amdgpu_ps *new_rps)
अणु
	काष्ठा kv_ps *new_ps = kv_get_ps(new_rps);
	काष्ठा kv_घातer_info *pi = kv_get_pi(adev);
	u32 i;
	काष्ठा amdgpu_घड़ी_voltage_dependency_table *table =
		&adev->pm.dpm.dyn_state.vddc_dependency_on_sclk;

	अगर (table && table->count) अणु
		क्रम (i = 0; i < pi->graphics_dpm_level_count; i++) अणु
			अगर ((table->entries[i].clk >= new_ps->levels[0].sclk) ||
			    (i == (pi->graphics_dpm_level_count - 1))) अणु
				pi->lowest_valid = i;
				अवरोध;
			पूर्ण
		पूर्ण

		क्रम (i = pi->graphics_dpm_level_count - 1; i > 0; i--) अणु
			अगर (table->entries[i].clk <= new_ps->levels[new_ps->num_levels - 1].sclk)
				अवरोध;
		पूर्ण
		pi->highest_valid = i;

		अगर (pi->lowest_valid > pi->highest_valid) अणु
			अगर ((new_ps->levels[0].sclk - table->entries[pi->highest_valid].clk) >
			    (table->entries[pi->lowest_valid].clk - new_ps->levels[new_ps->num_levels - 1].sclk))
				pi->highest_valid = pi->lowest_valid;
			अन्यथा
				pi->lowest_valid =  pi->highest_valid;
		पूर्ण
	पूर्ण अन्यथा अणु
		काष्ठा sumo_sclk_voltage_mapping_table *table =
			&pi->sys_info.sclk_voltage_mapping_table;

		क्रम (i = 0; i < (पूर्णांक)pi->graphics_dpm_level_count; i++) अणु
			अगर (table->entries[i].sclk_frequency >= new_ps->levels[0].sclk ||
			    i == (पूर्णांक)(pi->graphics_dpm_level_count - 1)) अणु
				pi->lowest_valid = i;
				अवरोध;
			पूर्ण
		पूर्ण

		क्रम (i = pi->graphics_dpm_level_count - 1; i > 0; i--) अणु
			अगर (table->entries[i].sclk_frequency <=
			    new_ps->levels[new_ps->num_levels - 1].sclk)
				अवरोध;
		पूर्ण
		pi->highest_valid = i;

		अगर (pi->lowest_valid > pi->highest_valid) अणु
			अगर ((new_ps->levels[0].sclk -
			     table->entries[pi->highest_valid].sclk_frequency) >
			    (table->entries[pi->lowest_valid].sclk_frequency -
			     new_ps->levels[new_ps->num_levels -1].sclk))
				pi->highest_valid = pi->lowest_valid;
			अन्यथा
				pi->lowest_valid =  pi->highest_valid;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक kv_update_dfs_bypass_settings(काष्ठा amdgpu_device *adev,
					 काष्ठा amdgpu_ps *new_rps)
अणु
	काष्ठा kv_ps *new_ps = kv_get_ps(new_rps);
	काष्ठा kv_घातer_info *pi = kv_get_pi(adev);
	पूर्णांक ret = 0;
	u8 clk_bypass_cntl;

	अगर (pi->caps_enable_dfs_bypass) अणु
		clk_bypass_cntl = new_ps->need_dfs_bypass ?
			pi->graphics_level[pi->graphics_boot_level].ClkBypassCntl : 0;
		ret = amdgpu_kv_copy_bytes_to_smc(adev,
					   (pi->dpm_table_start +
					    दुरत्व(SMU7_Fusion_DpmTable, GraphicsLevel) +
					    (pi->graphics_boot_level * माप(SMU7_Fusion_GraphicsLevel)) +
					    दुरत्व(SMU7_Fusion_GraphicsLevel, ClkBypassCntl)),
					   &clk_bypass_cntl,
					   माप(u8), pi->sram_end);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक kv_enable_nb_dpm(काष्ठा amdgpu_device *adev,
			    bool enable)
अणु
	काष्ठा kv_घातer_info *pi = kv_get_pi(adev);
	पूर्णांक ret = 0;

	अगर (enable) अणु
		अगर (pi->enable_nb_dpm && !pi->nb_dpm_enabled) अणु
			ret = amdgpu_kv_notअगरy_message_to_smu(adev, PPSMC_MSG_NBDPM_Enable);
			अगर (ret == 0)
				pi->nb_dpm_enabled = true;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (pi->enable_nb_dpm && pi->nb_dpm_enabled) अणु
			ret = amdgpu_kv_notअगरy_message_to_smu(adev, PPSMC_MSG_NBDPM_Disable);
			अगर (ret == 0)
				pi->nb_dpm_enabled = false;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक kv_dpm_क्रमce_perक्रमmance_level(व्योम *handle,
					  क्रमागत amd_dpm_क्रमced_level level)
अणु
	पूर्णांक ret;
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	अगर (level == AMD_DPM_FORCED_LEVEL_HIGH) अणु
		ret = kv_क्रमce_dpm_highest(adev);
		अगर (ret)
			वापस ret;
	पूर्ण अन्यथा अगर (level == AMD_DPM_FORCED_LEVEL_LOW) अणु
		ret = kv_क्रमce_dpm_lowest(adev);
		अगर (ret)
			वापस ret;
	पूर्ण अन्यथा अगर (level == AMD_DPM_FORCED_LEVEL_AUTO) अणु
		ret = kv_unक्रमce_levels(adev);
		अगर (ret)
			वापस ret;
	पूर्ण

	adev->pm.dpm.क्रमced_level = level;

	वापस 0;
पूर्ण

अटल पूर्णांक kv_dpm_pre_set_घातer_state(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;
	काष्ठा kv_घातer_info *pi = kv_get_pi(adev);
	काष्ठा amdgpu_ps requested_ps = *adev->pm.dpm.requested_ps;
	काष्ठा amdgpu_ps *new_ps = &requested_ps;

	kv_update_requested_ps(adev, new_ps);

	kv_apply_state_adjust_rules(adev,
				    &pi->requested_rps,
				    &pi->current_rps);

	वापस 0;
पूर्ण

अटल पूर्णांक kv_dpm_set_घातer_state(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;
	काष्ठा kv_घातer_info *pi = kv_get_pi(adev);
	काष्ठा amdgpu_ps *new_ps = &pi->requested_rps;
	काष्ठा amdgpu_ps *old_ps = &pi->current_rps;
	पूर्णांक ret;

	अगर (pi->bapm_enable) अणु
		ret = amdgpu_kv_smc_bapm_enable(adev, adev->pm.ac_घातer);
		अगर (ret) अणु
			DRM_ERROR("amdgpu_kv_smc_bapm_enable failed\n");
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (adev->asic_type == CHIP_KABINI || adev->asic_type == CHIP_MULLINS) अणु
		अगर (pi->enable_dpm) अणु
			kv_set_valid_घड़ी_range(adev, new_ps);
			kv_update_dfs_bypass_settings(adev, new_ps);
			ret = kv_calculate_ds_भागider(adev);
			अगर (ret) अणु
				DRM_ERROR("kv_calculate_ds_divider failed\n");
				वापस ret;
			पूर्ण
			kv_calculate_nbps_level_settings(adev);
			kv_calculate_dpm_settings(adev);
			kv_क्रमce_lowest_valid(adev);
			kv_enable_new_levels(adev);
			kv_upload_dpm_settings(adev);
			kv_program_nbps_index_settings(adev, new_ps);
			kv_unक्रमce_levels(adev);
			kv_set_enabled_levels(adev);
			kv_क्रमce_lowest_valid(adev);
			kv_unक्रमce_levels(adev);

			ret = kv_update_vce_dpm(adev, new_ps, old_ps);
			अगर (ret) अणु
				DRM_ERROR("kv_update_vce_dpm failed\n");
				वापस ret;
			पूर्ण
			kv_update_sclk_t(adev);
			अगर (adev->asic_type == CHIP_MULLINS)
				kv_enable_nb_dpm(adev, true);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (pi->enable_dpm) अणु
			kv_set_valid_घड़ी_range(adev, new_ps);
			kv_update_dfs_bypass_settings(adev, new_ps);
			ret = kv_calculate_ds_भागider(adev);
			अगर (ret) अणु
				DRM_ERROR("kv_calculate_ds_divider failed\n");
				वापस ret;
			पूर्ण
			kv_calculate_nbps_level_settings(adev);
			kv_calculate_dpm_settings(adev);
			kv_मुक्तze_sclk_dpm(adev, true);
			kv_upload_dpm_settings(adev);
			kv_program_nbps_index_settings(adev, new_ps);
			kv_मुक्तze_sclk_dpm(adev, false);
			kv_set_enabled_levels(adev);
			ret = kv_update_vce_dpm(adev, new_ps, old_ps);
			अगर (ret) अणु
				DRM_ERROR("kv_update_vce_dpm failed\n");
				वापस ret;
			पूर्ण
			kv_update_acp_boot_level(adev);
			kv_update_sclk_t(adev);
			kv_enable_nb_dpm(adev, true);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम kv_dpm_post_set_घातer_state(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;
	काष्ठा kv_घातer_info *pi = kv_get_pi(adev);
	काष्ठा amdgpu_ps *new_ps = &pi->requested_rps;

	kv_update_current_ps(adev, new_ps);
पूर्ण

अटल व्योम kv_dpm_setup_asic(काष्ठा amdgpu_device *adev)
अणु
	sumo_take_smu_control(adev, true);
	kv_init_घातergate_state(adev);
	kv_init_sclk_t(adev);
पूर्ण

#अगर 0
अटल व्योम kv_dpm_reset_asic(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा kv_घातer_info *pi = kv_get_pi(adev);

	अगर (adev->asic_type == CHIP_KABINI || adev->asic_type == CHIP_MULLINS) अणु
		kv_क्रमce_lowest_valid(adev);
		kv_init_graphics_levels(adev);
		kv_program_bootup_state(adev);
		kv_upload_dpm_settings(adev);
		kv_क्रमce_lowest_valid(adev);
		kv_unक्रमce_levels(adev);
	पूर्ण अन्यथा अणु
		kv_init_graphics_levels(adev);
		kv_program_bootup_state(adev);
		kv_मुक्तze_sclk_dpm(adev, true);
		kv_upload_dpm_settings(adev);
		kv_मुक्तze_sclk_dpm(adev, false);
		kv_set_enabled_level(adev, pi->graphics_boot_level);
	पूर्ण
पूर्ण
#पूर्ण_अगर

अटल व्योम kv_स्थिरruct_max_घातer_limits_table(काष्ठा amdgpu_device *adev,
						काष्ठा amdgpu_घड़ी_and_voltage_limits *table)
अणु
	काष्ठा kv_घातer_info *pi = kv_get_pi(adev);

	अगर (pi->sys_info.sclk_voltage_mapping_table.num_max_dpm_entries > 0) अणु
		पूर्णांक idx = pi->sys_info.sclk_voltage_mapping_table.num_max_dpm_entries - 1;
		table->sclk =
			pi->sys_info.sclk_voltage_mapping_table.entries[idx].sclk_frequency;
		table->vddc =
			kv_convert_2bit_index_to_voltage(adev,
							 pi->sys_info.sclk_voltage_mapping_table.entries[idx].vid_2bit);
	पूर्ण

	table->mclk = pi->sys_info.nbp_memory_घड़ी[0];
पूर्ण

अटल व्योम kv_patch_voltage_values(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक i;
	काष्ठा amdgpu_uvd_घड़ी_voltage_dependency_table *uvd_table =
		&adev->pm.dpm.dyn_state.uvd_घड़ी_voltage_dependency_table;
	काष्ठा amdgpu_vce_घड़ी_voltage_dependency_table *vce_table =
		&adev->pm.dpm.dyn_state.vce_घड़ी_voltage_dependency_table;
	काष्ठा amdgpu_घड़ी_voltage_dependency_table *samu_table =
		&adev->pm.dpm.dyn_state.samu_घड़ी_voltage_dependency_table;
	काष्ठा amdgpu_घड़ी_voltage_dependency_table *acp_table =
		&adev->pm.dpm.dyn_state.acp_घड़ी_voltage_dependency_table;

	अगर (uvd_table->count) अणु
		क्रम (i = 0; i < uvd_table->count; i++)
			uvd_table->entries[i].v =
				kv_convert_8bit_index_to_voltage(adev,
								 uvd_table->entries[i].v);
	पूर्ण

	अगर (vce_table->count) अणु
		क्रम (i = 0; i < vce_table->count; i++)
			vce_table->entries[i].v =
				kv_convert_8bit_index_to_voltage(adev,
								 vce_table->entries[i].v);
	पूर्ण

	अगर (samu_table->count) अणु
		क्रम (i = 0; i < samu_table->count; i++)
			samu_table->entries[i].v =
				kv_convert_8bit_index_to_voltage(adev,
								 samu_table->entries[i].v);
	पूर्ण

	अगर (acp_table->count) अणु
		क्रम (i = 0; i < acp_table->count; i++)
			acp_table->entries[i].v =
				kv_convert_8bit_index_to_voltage(adev,
								 acp_table->entries[i].v);
	पूर्ण

पूर्ण

अटल व्योम kv_स्थिरruct_boot_state(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा kv_घातer_info *pi = kv_get_pi(adev);

	pi->boot_pl.sclk = pi->sys_info.bootup_sclk;
	pi->boot_pl.vddc_index = pi->sys_info.bootup_nb_voltage_index;
	pi->boot_pl.ds_भागider_index = 0;
	pi->boot_pl.ss_भागider_index = 0;
	pi->boot_pl.allow_gnb_slow = 1;
	pi->boot_pl.क्रमce_nbp_state = 0;
	pi->boot_pl.display_wm = 0;
	pi->boot_pl.vce_wm = 0;
पूर्ण

अटल पूर्णांक kv_क्रमce_dpm_highest(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक ret;
	u32 enable_mask, i;

	ret = amdgpu_kv_dpm_get_enable_mask(adev, &enable_mask);
	अगर (ret)
		वापस ret;

	क्रम (i = SMU7_MAX_LEVELS_GRAPHICS - 1; i > 0; i--) अणु
		अगर (enable_mask & (1 << i))
			अवरोध;
	पूर्ण

	अगर (adev->asic_type == CHIP_KABINI || adev->asic_type == CHIP_MULLINS)
		वापस amdgpu_kv_send_msg_to_smc_with_parameter(adev, PPSMC_MSG_DPM_ForceState, i);
	अन्यथा
		वापस kv_set_enabled_level(adev, i);
पूर्ण

अटल पूर्णांक kv_क्रमce_dpm_lowest(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक ret;
	u32 enable_mask, i;

	ret = amdgpu_kv_dpm_get_enable_mask(adev, &enable_mask);
	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < SMU7_MAX_LEVELS_GRAPHICS; i++) अणु
		अगर (enable_mask & (1 << i))
			अवरोध;
	पूर्ण

	अगर (adev->asic_type == CHIP_KABINI || adev->asic_type == CHIP_MULLINS)
		वापस amdgpu_kv_send_msg_to_smc_with_parameter(adev, PPSMC_MSG_DPM_ForceState, i);
	अन्यथा
		वापस kv_set_enabled_level(adev, i);
पूर्ण

अटल u8 kv_get_sleep_भागider_id_from_घड़ी(काष्ठा amdgpu_device *adev,
					     u32 sclk, u32 min_sclk_in_sr)
अणु
	काष्ठा kv_घातer_info *pi = kv_get_pi(adev);
	u32 i;
	u32 temp;
	u32 min = max(min_sclk_in_sr, (u32)KV_MINIMUM_ENGINE_CLOCK);

	अगर (sclk < min)
		वापस 0;

	अगर (!pi->caps_sclk_ds)
		वापस 0;

	क्रम (i = KV_MAX_DEEPSLEEP_DIVIDER_ID; i > 0; i--) अणु
		temp = sclk >> i;
		अगर (temp >= min)
			अवरोध;
	पूर्ण

	वापस (u8)i;
पूर्ण

अटल पूर्णांक kv_get_high_voltage_limit(काष्ठा amdgpu_device *adev, पूर्णांक *limit)
अणु
	काष्ठा kv_घातer_info *pi = kv_get_pi(adev);
	काष्ठा amdgpu_घड़ी_voltage_dependency_table *table =
		&adev->pm.dpm.dyn_state.vddc_dependency_on_sclk;
	पूर्णांक i;

	अगर (table && table->count) अणु
		क्रम (i = table->count - 1; i >= 0; i--) अणु
			अगर (pi->high_voltage_t &&
			    (kv_convert_8bit_index_to_voltage(adev, table->entries[i].v) <=
			     pi->high_voltage_t)) अणु
				*limit = i;
				वापस 0;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		काष्ठा sumo_sclk_voltage_mapping_table *table =
			&pi->sys_info.sclk_voltage_mapping_table;

		क्रम (i = table->num_max_dpm_entries - 1; i >= 0; i--) अणु
			अगर (pi->high_voltage_t &&
			    (kv_convert_2bit_index_to_voltage(adev, table->entries[i].vid_2bit) <=
			     pi->high_voltage_t)) अणु
				*limit = i;
				वापस 0;
			पूर्ण
		पूर्ण
	पूर्ण

	*limit = 0;
	वापस 0;
पूर्ण

अटल व्योम kv_apply_state_adjust_rules(काष्ठा amdgpu_device *adev,
					काष्ठा amdgpu_ps *new_rps,
					काष्ठा amdgpu_ps *old_rps)
अणु
	काष्ठा kv_ps *ps = kv_get_ps(new_rps);
	काष्ठा kv_घातer_info *pi = kv_get_pi(adev);
	u32 min_sclk = 10000; /* ??? */
	u32 sclk, mclk = 0;
	पूर्णांक i, limit;
	bool क्रमce_high;
	काष्ठा amdgpu_घड़ी_voltage_dependency_table *table =
		&adev->pm.dpm.dyn_state.vddc_dependency_on_sclk;
	u32 stable_p_state_sclk = 0;
	काष्ठा amdgpu_घड़ी_and_voltage_limits *max_limits =
		&adev->pm.dpm.dyn_state.max_घड़ी_voltage_on_ac;

	अगर (new_rps->vce_active) अणु
		new_rps->evclk = adev->pm.dpm.vce_states[adev->pm.dpm.vce_level].evclk;
		new_rps->ecclk = adev->pm.dpm.vce_states[adev->pm.dpm.vce_level].ecclk;
	पूर्ण अन्यथा अणु
		new_rps->evclk = 0;
		new_rps->ecclk = 0;
	पूर्ण

	mclk = max_limits->mclk;
	sclk = min_sclk;

	अगर (pi->caps_stable_p_state) अणु
		stable_p_state_sclk = (max_limits->sclk * 75) / 100;

		क्रम (i = table->count - 1; i >= 0; i--) अणु
			अगर (stable_p_state_sclk >= table->entries[i].clk) अणु
				stable_p_state_sclk = table->entries[i].clk;
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (i > 0)
			stable_p_state_sclk = table->entries[0].clk;

		sclk = stable_p_state_sclk;
	पूर्ण

	अगर (new_rps->vce_active) अणु
		अगर (sclk < adev->pm.dpm.vce_states[adev->pm.dpm.vce_level].sclk)
			sclk = adev->pm.dpm.vce_states[adev->pm.dpm.vce_level].sclk;
	पूर्ण

	ps->need_dfs_bypass = true;

	क्रम (i = 0; i < ps->num_levels; i++) अणु
		अगर (ps->levels[i].sclk < sclk)
			ps->levels[i].sclk = sclk;
	पूर्ण

	अगर (table && table->count) अणु
		क्रम (i = 0; i < ps->num_levels; i++) अणु
			अगर (pi->high_voltage_t &&
			    (pi->high_voltage_t <
			     kv_convert_8bit_index_to_voltage(adev, ps->levels[i].vddc_index))) अणु
				kv_get_high_voltage_limit(adev, &limit);
				ps->levels[i].sclk = table->entries[limit].clk;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		काष्ठा sumo_sclk_voltage_mapping_table *table =
			&pi->sys_info.sclk_voltage_mapping_table;

		क्रम (i = 0; i < ps->num_levels; i++) अणु
			अगर (pi->high_voltage_t &&
			    (pi->high_voltage_t <
			     kv_convert_8bit_index_to_voltage(adev, ps->levels[i].vddc_index))) अणु
				kv_get_high_voltage_limit(adev, &limit);
				ps->levels[i].sclk = table->entries[limit].sclk_frequency;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (pi->caps_stable_p_state) अणु
		क्रम (i = 0; i < ps->num_levels; i++) अणु
			ps->levels[i].sclk = stable_p_state_sclk;
		पूर्ण
	पूर्ण

	pi->video_start = new_rps->dclk || new_rps->vclk ||
		new_rps->evclk || new_rps->ecclk;

	अगर ((new_rps->class & ATOM_PPLIB_CLASSIFICATION_UI_MASK) ==
	    ATOM_PPLIB_CLASSIFICATION_UI_BATTERY)
		pi->battery_state = true;
	अन्यथा
		pi->battery_state = false;

	अगर (adev->asic_type == CHIP_KABINI || adev->asic_type == CHIP_MULLINS) अणु
		ps->dpm0_pg_nb_ps_lo = 0x1;
		ps->dpm0_pg_nb_ps_hi = 0x0;
		ps->dpmx_nb_ps_lo = 0x1;
		ps->dpmx_nb_ps_hi = 0x0;
	पूर्ण अन्यथा अणु
		ps->dpm0_pg_nb_ps_lo = 0x3;
		ps->dpm0_pg_nb_ps_hi = 0x0;
		ps->dpmx_nb_ps_lo = 0x3;
		ps->dpmx_nb_ps_hi = 0x0;

		अगर (pi->sys_info.nb_dpm_enable) अणु
			क्रमce_high = (mclk >= pi->sys_info.nbp_memory_घड़ी[3]) ||
				pi->video_start || (adev->pm.dpm.new_active_crtc_count >= 3) ||
				pi->disable_nb_ps3_in_battery;
			ps->dpm0_pg_nb_ps_lo = क्रमce_high ? 0x2 : 0x3;
			ps->dpm0_pg_nb_ps_hi = 0x2;
			ps->dpmx_nb_ps_lo = क्रमce_high ? 0x2 : 0x3;
			ps->dpmx_nb_ps_hi = 0x2;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम kv_dpm_घातer_level_enabled_क्रम_throttle(काष्ठा amdgpu_device *adev,
						    u32 index, bool enable)
अणु
	काष्ठा kv_घातer_info *pi = kv_get_pi(adev);

	pi->graphics_level[index].EnabledForThrottle = enable ? 1 : 0;
पूर्ण

अटल पूर्णांक kv_calculate_ds_भागider(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा kv_घातer_info *pi = kv_get_pi(adev);
	u32 sclk_in_sr = 10000; /* ??? */
	u32 i;

	अगर (pi->lowest_valid > pi->highest_valid)
		वापस -EINVAL;

	क्रम (i = pi->lowest_valid; i <= pi->highest_valid; i++) अणु
		pi->graphics_level[i].DeepSleepDivId =
			kv_get_sleep_भागider_id_from_घड़ी(adev,
							   be32_to_cpu(pi->graphics_level[i].SclkFrequency),
							   sclk_in_sr);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक kv_calculate_nbps_level_settings(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा kv_घातer_info *pi = kv_get_pi(adev);
	u32 i;
	bool क्रमce_high;
	काष्ठा amdgpu_घड़ी_and_voltage_limits *max_limits =
		&adev->pm.dpm.dyn_state.max_घड़ी_voltage_on_ac;
	u32 mclk = max_limits->mclk;

	अगर (pi->lowest_valid > pi->highest_valid)
		वापस -EINVAL;

	अगर (adev->asic_type == CHIP_KABINI || adev->asic_type == CHIP_MULLINS) अणु
		क्रम (i = pi->lowest_valid; i <= pi->highest_valid; i++) अणु
			pi->graphics_level[i].GnbSlow = 1;
			pi->graphics_level[i].ForceNbPs1 = 0;
			pi->graphics_level[i].UpH = 0;
		पूर्ण

		अगर (!pi->sys_info.nb_dpm_enable)
			वापस 0;

		क्रमce_high = ((mclk >= pi->sys_info.nbp_memory_घड़ी[3]) ||
			      (adev->pm.dpm.new_active_crtc_count >= 3) || pi->video_start);

		अगर (क्रमce_high) अणु
			क्रम (i = pi->lowest_valid; i <= pi->highest_valid; i++)
				pi->graphics_level[i].GnbSlow = 0;
		पूर्ण अन्यथा अणु
			अगर (pi->battery_state)
				pi->graphics_level[0].ForceNbPs1 = 1;

			pi->graphics_level[1].GnbSlow = 0;
			pi->graphics_level[2].GnbSlow = 0;
			pi->graphics_level[3].GnbSlow = 0;
			pi->graphics_level[4].GnbSlow = 0;
		पूर्ण
	पूर्ण अन्यथा अणु
		क्रम (i = pi->lowest_valid; i <= pi->highest_valid; i++) अणु
			pi->graphics_level[i].GnbSlow = 1;
			pi->graphics_level[i].ForceNbPs1 = 0;
			pi->graphics_level[i].UpH = 0;
		पूर्ण

		अगर (pi->sys_info.nb_dpm_enable && pi->battery_state) अणु
			pi->graphics_level[pi->lowest_valid].UpH = 0x28;
			pi->graphics_level[pi->lowest_valid].GnbSlow = 0;
			अगर (pi->lowest_valid != pi->highest_valid)
				pi->graphics_level[pi->lowest_valid].ForceNbPs1 = 1;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक kv_calculate_dpm_settings(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा kv_घातer_info *pi = kv_get_pi(adev);
	u32 i;

	अगर (pi->lowest_valid > pi->highest_valid)
		वापस -EINVAL;

	क्रम (i = pi->lowest_valid; i <= pi->highest_valid; i++)
		pi->graphics_level[i].DisplayWatermark = (i == pi->highest_valid) ? 1 : 0;

	वापस 0;
पूर्ण

अटल व्योम kv_init_graphics_levels(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा kv_घातer_info *pi = kv_get_pi(adev);
	u32 i;
	काष्ठा amdgpu_घड़ी_voltage_dependency_table *table =
		&adev->pm.dpm.dyn_state.vddc_dependency_on_sclk;

	अगर (table && table->count) अणु
		u32 vid_2bit;

		pi->graphics_dpm_level_count = 0;
		क्रम (i = 0; i < table->count; i++) अणु
			अगर (pi->high_voltage_t &&
			    (pi->high_voltage_t <
			     kv_convert_8bit_index_to_voltage(adev, table->entries[i].v)))
				अवरोध;

			kv_set_भागider_value(adev, i, table->entries[i].clk);
			vid_2bit = kv_convert_vid7_to_vid2(adev,
							   &pi->sys_info.vid_mapping_table,
							   table->entries[i].v);
			kv_set_vid(adev, i, vid_2bit);
			kv_set_at(adev, i, pi->at[i]);
			kv_dpm_घातer_level_enabled_क्रम_throttle(adev, i, true);
			pi->graphics_dpm_level_count++;
		पूर्ण
	पूर्ण अन्यथा अणु
		काष्ठा sumo_sclk_voltage_mapping_table *table =
			&pi->sys_info.sclk_voltage_mapping_table;

		pi->graphics_dpm_level_count = 0;
		क्रम (i = 0; i < table->num_max_dpm_entries; i++) अणु
			अगर (pi->high_voltage_t &&
			    pi->high_voltage_t <
			    kv_convert_2bit_index_to_voltage(adev, table->entries[i].vid_2bit))
				अवरोध;

			kv_set_भागider_value(adev, i, table->entries[i].sclk_frequency);
			kv_set_vid(adev, i, table->entries[i].vid_2bit);
			kv_set_at(adev, i, pi->at[i]);
			kv_dpm_घातer_level_enabled_क्रम_throttle(adev, i, true);
			pi->graphics_dpm_level_count++;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < SMU7_MAX_LEVELS_GRAPHICS; i++)
		kv_dpm_घातer_level_enable(adev, i, false);
पूर्ण

अटल व्योम kv_enable_new_levels(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा kv_घातer_info *pi = kv_get_pi(adev);
	u32 i;

	क्रम (i = 0; i < SMU7_MAX_LEVELS_GRAPHICS; i++) अणु
		अगर (i >= pi->lowest_valid && i <= pi->highest_valid)
			kv_dpm_घातer_level_enable(adev, i, true);
	पूर्ण
पूर्ण

अटल पूर्णांक kv_set_enabled_level(काष्ठा amdgpu_device *adev, u32 level)
अणु
	u32 new_mask = (1 << level);

	वापस amdgpu_kv_send_msg_to_smc_with_parameter(adev,
						 PPSMC_MSG_SCLKDPM_SetEnabledMask,
						 new_mask);
पूर्ण

अटल पूर्णांक kv_set_enabled_levels(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा kv_घातer_info *pi = kv_get_pi(adev);
	u32 i, new_mask = 0;

	क्रम (i = pi->lowest_valid; i <= pi->highest_valid; i++)
		new_mask |= (1 << i);

	वापस amdgpu_kv_send_msg_to_smc_with_parameter(adev,
						 PPSMC_MSG_SCLKDPM_SetEnabledMask,
						 new_mask);
पूर्ण

अटल व्योम kv_program_nbps_index_settings(काष्ठा amdgpu_device *adev,
					   काष्ठा amdgpu_ps *new_rps)
अणु
	काष्ठा kv_ps *new_ps = kv_get_ps(new_rps);
	काष्ठा kv_घातer_info *pi = kv_get_pi(adev);
	u32 nbdpmconfig1;

	अगर (adev->asic_type == CHIP_KABINI || adev->asic_type == CHIP_MULLINS)
		वापस;

	अगर (pi->sys_info.nb_dpm_enable) अणु
		nbdpmconfig1 = RREG32_SMC(ixNB_DPM_CONFIG_1);
		nbdpmconfig1 &= ~(NB_DPM_CONFIG_1__Dpm0PgNbPsLo_MASK |
				NB_DPM_CONFIG_1__Dpm0PgNbPsHi_MASK |
				NB_DPM_CONFIG_1__DpmXNbPsLo_MASK |
				NB_DPM_CONFIG_1__DpmXNbPsHi_MASK);
		nbdpmconfig1 |= (new_ps->dpm0_pg_nb_ps_lo << NB_DPM_CONFIG_1__Dpm0PgNbPsLo__SHIFT) |
				(new_ps->dpm0_pg_nb_ps_hi << NB_DPM_CONFIG_1__Dpm0PgNbPsHi__SHIFT) |
				(new_ps->dpmx_nb_ps_lo << NB_DPM_CONFIG_1__DpmXNbPsLo__SHIFT) |
				(new_ps->dpmx_nb_ps_hi << NB_DPM_CONFIG_1__DpmXNbPsHi__SHIFT);
		WREG32_SMC(ixNB_DPM_CONFIG_1, nbdpmconfig1);
	पूर्ण
पूर्ण

अटल पूर्णांक kv_set_thermal_temperature_range(काष्ठा amdgpu_device *adev,
					    पूर्णांक min_temp, पूर्णांक max_temp)
अणु
	पूर्णांक low_temp = 0 * 1000;
	पूर्णांक high_temp = 255 * 1000;
	u32 पंचांगp;

	अगर (low_temp < min_temp)
		low_temp = min_temp;
	अगर (high_temp > max_temp)
		high_temp = max_temp;
	अगर (high_temp < low_temp) अणु
		DRM_ERROR("invalid thermal range: %d - %d\n", low_temp, high_temp);
		वापस -EINVAL;
	पूर्ण

	पंचांगp = RREG32_SMC(ixCG_THERMAL_INT_CTRL);
	पंचांगp &= ~(CG_THERMAL_INT_CTRL__DIG_THERM_INTH_MASK |
		CG_THERMAL_INT_CTRL__DIG_THERM_INTL_MASK);
	पंचांगp |= ((49 + (high_temp / 1000)) << CG_THERMAL_INT_CTRL__DIG_THERM_INTH__SHIFT) |
		((49 + (low_temp / 1000)) << CG_THERMAL_INT_CTRL__DIG_THERM_INTL__SHIFT);
	WREG32_SMC(ixCG_THERMAL_INT_CTRL, पंचांगp);

	adev->pm.dpm.thermal.min_temp = low_temp;
	adev->pm.dpm.thermal.max_temp = high_temp;

	वापस 0;
पूर्ण

जोड़ igp_info अणु
	काष्ठा _ATOM_INTEGRATED_SYSTEM_INFO info;
	काष्ठा _ATOM_INTEGRATED_SYSTEM_INFO_V2 info_2;
	काष्ठा _ATOM_INTEGRATED_SYSTEM_INFO_V5 info_5;
	काष्ठा _ATOM_INTEGRATED_SYSTEM_INFO_V6 info_6;
	काष्ठा _ATOM_INTEGRATED_SYSTEM_INFO_V1_7 info_7;
	काष्ठा _ATOM_INTEGRATED_SYSTEM_INFO_V1_8 info_8;
पूर्ण;

अटल पूर्णांक kv_parse_sys_info_table(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा kv_घातer_info *pi = kv_get_pi(adev);
	काष्ठा amdgpu_mode_info *mode_info = &adev->mode_info;
	पूर्णांक index = GetIndexIntoMasterTable(DATA, IntegratedSystemInfo);
	जोड़ igp_info *igp_info;
	u8 frev, crev;
	u16 data_offset;
	पूर्णांक i;

	अगर (amdgpu_atom_parse_data_header(mode_info->atom_context, index, शून्य,
				   &frev, &crev, &data_offset)) अणु
		igp_info = (जोड़ igp_info *)(mode_info->atom_context->bios +
					      data_offset);

		अगर (crev != 8) अणु
			DRM_ERROR("Unsupported IGP table: %d %d\n", frev, crev);
			वापस -EINVAL;
		पूर्ण
		pi->sys_info.bootup_sclk = le32_to_cpu(igp_info->info_8.ulBootUpEngineClock);
		pi->sys_info.bootup_uma_clk = le32_to_cpu(igp_info->info_8.ulBootUpUMAClock);
		pi->sys_info.bootup_nb_voltage_index =
			le16_to_cpu(igp_info->info_8.usBootUpNBVoltage);
		अगर (igp_info->info_8.ucHtcTmpLmt == 0)
			pi->sys_info.htc_पंचांगp_lmt = 203;
		अन्यथा
			pi->sys_info.htc_पंचांगp_lmt = igp_info->info_8.ucHtcTmpLmt;
		अगर (igp_info->info_8.ucHtcHystLmt == 0)
			pi->sys_info.htc_hyst_lmt = 5;
		अन्यथा
			pi->sys_info.htc_hyst_lmt = igp_info->info_8.ucHtcHystLmt;
		अगर (pi->sys_info.htc_पंचांगp_lmt <= pi->sys_info.htc_hyst_lmt) अणु
			DRM_ERROR("The htcTmpLmt should be larger than htcHystLmt.\n");
		पूर्ण

		अगर (le32_to_cpu(igp_info->info_8.ulSystemConfig) & (1 << 3))
			pi->sys_info.nb_dpm_enable = true;
		अन्यथा
			pi->sys_info.nb_dpm_enable = false;

		क्रम (i = 0; i < KV_NUM_NBPSTATES; i++) अणु
			pi->sys_info.nbp_memory_घड़ी[i] =
				le32_to_cpu(igp_info->info_8.ulNbpStateMemclkFreq[i]);
			pi->sys_info.nbp_n_घड़ी[i] =
				le32_to_cpu(igp_info->info_8.ulNbpStateNClkFreq[i]);
		पूर्ण
		अगर (le32_to_cpu(igp_info->info_8.ulGPUCapInfo) &
		    SYS_INFO_GPUCAPS__ENABEL_DFS_BYPASS)
			pi->caps_enable_dfs_bypass = true;

		sumo_स्थिरruct_sclk_voltage_mapping_table(adev,
							  &pi->sys_info.sclk_voltage_mapping_table,
							  igp_info->info_8.sAvail_SCLK);

		sumo_स्थिरruct_vid_mapping_table(adev,
						 &pi->sys_info.vid_mapping_table,
						 igp_info->info_8.sAvail_SCLK);

		kv_स्थिरruct_max_घातer_limits_table(adev,
						    &adev->pm.dpm.dyn_state.max_घड़ी_voltage_on_ac);
	पूर्ण
	वापस 0;
पूर्ण

जोड़ घातer_info अणु
	काष्ठा _ATOM_POWERPLAY_INFO info;
	काष्ठा _ATOM_POWERPLAY_INFO_V2 info_2;
	काष्ठा _ATOM_POWERPLAY_INFO_V3 info_3;
	काष्ठा _ATOM_PPLIB_POWERPLAYTABLE pplib;
	काष्ठा _ATOM_PPLIB_POWERPLAYTABLE2 pplib2;
	काष्ठा _ATOM_PPLIB_POWERPLAYTABLE3 pplib3;
पूर्ण;

जोड़ pplib_घड़ी_info अणु
	काष्ठा _ATOM_PPLIB_R600_CLOCK_INFO r600;
	काष्ठा _ATOM_PPLIB_RS780_CLOCK_INFO rs780;
	काष्ठा _ATOM_PPLIB_EVERGREEN_CLOCK_INFO evergreen;
	काष्ठा _ATOM_PPLIB_SUMO_CLOCK_INFO sumo;
पूर्ण;

जोड़ pplib_घातer_state अणु
	काष्ठा _ATOM_PPLIB_STATE v1;
	काष्ठा _ATOM_PPLIB_STATE_V2 v2;
पूर्ण;

अटल व्योम kv_patch_boot_state(काष्ठा amdgpu_device *adev,
				काष्ठा kv_ps *ps)
अणु
	काष्ठा kv_घातer_info *pi = kv_get_pi(adev);

	ps->num_levels = 1;
	ps->levels[0] = pi->boot_pl;
पूर्ण

अटल व्योम kv_parse_pplib_non_घड़ी_info(काष्ठा amdgpu_device *adev,
					  काष्ठा amdgpu_ps *rps,
					  काष्ठा _ATOM_PPLIB_NONCLOCK_INFO *non_घड़ी_info,
					  u8 table_rev)
अणु
	काष्ठा kv_ps *ps = kv_get_ps(rps);

	rps->caps = le32_to_cpu(non_घड़ी_info->ulCapsAndSettings);
	rps->class = le16_to_cpu(non_घड़ी_info->usClassअगरication);
	rps->class2 = le16_to_cpu(non_घड़ी_info->usClassअगरication2);

	अगर (ATOM_PPLIB_NONCLOCKINFO_VER1 < table_rev) अणु
		rps->vclk = le32_to_cpu(non_घड़ी_info->ulVCLK);
		rps->dclk = le32_to_cpu(non_घड़ी_info->ulDCLK);
	पूर्ण अन्यथा अणु
		rps->vclk = 0;
		rps->dclk = 0;
	पूर्ण

	अगर (rps->class & ATOM_PPLIB_CLASSIFICATION_BOOT) अणु
		adev->pm.dpm.boot_ps = rps;
		kv_patch_boot_state(adev, ps);
	पूर्ण
	अगर (rps->class & ATOM_PPLIB_CLASSIFICATION_UVDSTATE)
		adev->pm.dpm.uvd_ps = rps;
पूर्ण

अटल व्योम kv_parse_pplib_घड़ी_info(काष्ठा amdgpu_device *adev,
				      काष्ठा amdgpu_ps *rps, पूर्णांक index,
					जोड़ pplib_घड़ी_info *घड़ी_info)
अणु
	काष्ठा kv_घातer_info *pi = kv_get_pi(adev);
	काष्ठा kv_ps *ps = kv_get_ps(rps);
	काष्ठा kv_pl *pl = &ps->levels[index];
	u32 sclk;

	sclk = le16_to_cpu(घड़ी_info->sumo.usEngineClockLow);
	sclk |= घड़ी_info->sumo.ucEngineClockHigh << 16;
	pl->sclk = sclk;
	pl->vddc_index = घड़ी_info->sumo.vddcIndex;

	ps->num_levels = index + 1;

	अगर (pi->caps_sclk_ds) अणु
		pl->ds_भागider_index = 5;
		pl->ss_भागider_index = 5;
	पूर्ण
पूर्ण

अटल पूर्णांक kv_parse_घातer_table(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा amdgpu_mode_info *mode_info = &adev->mode_info;
	काष्ठा _ATOM_PPLIB_NONCLOCK_INFO *non_घड़ी_info;
	जोड़ pplib_घातer_state *घातer_state;
	पूर्णांक i, j, k, non_घड़ी_array_index, घड़ी_array_index;
	जोड़ pplib_घड़ी_info *घड़ी_info;
	काष्ठा _StateArray *state_array;
	काष्ठा _ClockInfoArray *घड़ी_info_array;
	काष्ठा _NonClockInfoArray *non_घड़ी_info_array;
	जोड़ घातer_info *घातer_info;
	पूर्णांक index = GetIndexIntoMasterTable(DATA, PowerPlayInfo);
	u16 data_offset;
	u8 frev, crev;
	u8 *घातer_state_offset;
	काष्ठा kv_ps *ps;

	अगर (!amdgpu_atom_parse_data_header(mode_info->atom_context, index, शून्य,
				   &frev, &crev, &data_offset))
		वापस -EINVAL;
	घातer_info = (जोड़ घातer_info *)(mode_info->atom_context->bios + data_offset);

	amdgpu_add_thermal_controller(adev);

	state_array = (काष्ठा _StateArray *)
		(mode_info->atom_context->bios + data_offset +
		 le16_to_cpu(घातer_info->pplib.usStateArrayOffset));
	घड़ी_info_array = (काष्ठा _ClockInfoArray *)
		(mode_info->atom_context->bios + data_offset +
		 le16_to_cpu(घातer_info->pplib.usClockInfoArrayOffset));
	non_घड़ी_info_array = (काष्ठा _NonClockInfoArray *)
		(mode_info->atom_context->bios + data_offset +
		 le16_to_cpu(घातer_info->pplib.usNonClockInfoArrayOffset));

	adev->pm.dpm.ps = kसुस्मृति(state_array->ucNumEntries,
				  माप(काष्ठा amdgpu_ps),
				  GFP_KERNEL);
	अगर (!adev->pm.dpm.ps)
		वापस -ENOMEM;
	घातer_state_offset = (u8 *)state_array->states;
	क्रम (i = 0; i < state_array->ucNumEntries; i++) अणु
		u8 *idx;
		घातer_state = (जोड़ pplib_घातer_state *)घातer_state_offset;
		non_घड़ी_array_index = घातer_state->v2.nonClockInfoIndex;
		non_घड़ी_info = (काष्ठा _ATOM_PPLIB_NONCLOCK_INFO *)
			&non_घड़ी_info_array->nonClockInfo[non_घड़ी_array_index];
		ps = kzalloc(माप(काष्ठा kv_ps), GFP_KERNEL);
		अगर (ps == शून्य) अणु
			kमुक्त(adev->pm.dpm.ps);
			वापस -ENOMEM;
		पूर्ण
		adev->pm.dpm.ps[i].ps_priv = ps;
		k = 0;
		idx = (u8 *)&घातer_state->v2.घड़ीInfoIndex[0];
		क्रम (j = 0; j < घातer_state->v2.ucNumDPMLevels; j++) अणु
			घड़ी_array_index = idx[j];
			अगर (घड़ी_array_index >= घड़ी_info_array->ucNumEntries)
				जारी;
			अगर (k >= SUMO_MAX_HARDWARE_POWERLEVELS)
				अवरोध;
			घड़ी_info = (जोड़ pplib_घड़ी_info *)
				((u8 *)&घड़ी_info_array->घड़ीInfo[0] +
				 (घड़ी_array_index * घड़ी_info_array->ucEntrySize));
			kv_parse_pplib_घड़ी_info(adev,
						  &adev->pm.dpm.ps[i], k,
						  घड़ी_info);
			k++;
		पूर्ण
		kv_parse_pplib_non_घड़ी_info(adev, &adev->pm.dpm.ps[i],
					      non_घड़ी_info,
					      non_घड़ी_info_array->ucEntrySize);
		घातer_state_offset += 2 + घातer_state->v2.ucNumDPMLevels;
	पूर्ण
	adev->pm.dpm.num_ps = state_array->ucNumEntries;

	/* fill in the vce घातer states */
	क्रम (i = 0; i < adev->pm.dpm.num_of_vce_states; i++) अणु
		u32 sclk;
		घड़ी_array_index = adev->pm.dpm.vce_states[i].clk_idx;
		घड़ी_info = (जोड़ pplib_घड़ी_info *)
			&घड़ी_info_array->घड़ीInfo[घड़ी_array_index * घड़ी_info_array->ucEntrySize];
		sclk = le16_to_cpu(घड़ी_info->sumo.usEngineClockLow);
		sclk |= घड़ी_info->sumo.ucEngineClockHigh << 16;
		adev->pm.dpm.vce_states[i].sclk = sclk;
		adev->pm.dpm.vce_states[i].mclk = 0;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक kv_dpm_init(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा kv_घातer_info *pi;
	पूर्णांक ret, i;

	pi = kzalloc(माप(काष्ठा kv_घातer_info), GFP_KERNEL);
	अगर (pi == शून्य)
		वापस -ENOMEM;
	adev->pm.dpm.priv = pi;

	ret = amdgpu_get_platक्रमm_caps(adev);
	अगर (ret)
		वापस ret;

	ret = amdgpu_parse_extended_घातer_table(adev);
	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < SUMO_MAX_HARDWARE_POWERLEVELS; i++)
		pi->at[i] = TRINITY_AT_DFLT;

	pi->sram_end = SMC_RAM_END;

	pi->enable_nb_dpm = true;

	pi->caps_घातer_containment = true;
	pi->caps_cac = true;
	pi->enable_didt = false;
	अगर (pi->enable_didt) अणु
		pi->caps_sq_ramping = true;
		pi->caps_db_ramping = true;
		pi->caps_td_ramping = true;
		pi->caps_tcp_ramping = true;
	पूर्ण

	अगर (adev->pm.pp_feature & PP_SCLK_DEEP_SLEEP_MASK)
		pi->caps_sclk_ds = true;
	अन्यथा
		pi->caps_sclk_ds = false;

	pi->enable_स्वतः_thermal_throttling = true;
	pi->disable_nb_ps3_in_battery = false;
	अगर (amdgpu_bapm == 0)
		pi->bapm_enable = false;
	अन्यथा
		pi->bapm_enable = true;
	pi->voltage_drop_t = 0;
	pi->caps_sclk_throttle_low_notअगरication = false;
	pi->caps_fps = false; /* true? */
	pi->caps_uvd_pg = (adev->pg_flags & AMD_PG_SUPPORT_UVD) ? true : false;
	pi->caps_uvd_dpm = true;
	pi->caps_vce_pg = (adev->pg_flags & AMD_PG_SUPPORT_VCE) ? true : false;
	pi->caps_samu_pg = (adev->pg_flags & AMD_PG_SUPPORT_SAMU) ? true : false;
	pi->caps_acp_pg = (adev->pg_flags & AMD_PG_SUPPORT_ACP) ? true : false;
	pi->caps_stable_p_state = false;

	ret = kv_parse_sys_info_table(adev);
	अगर (ret)
		वापस ret;

	kv_patch_voltage_values(adev);
	kv_स्थिरruct_boot_state(adev);

	ret = kv_parse_घातer_table(adev);
	अगर (ret)
		वापस ret;

	pi->enable_dpm = true;

	वापस 0;
पूर्ण

अटल व्योम
kv_dpm_debugfs_prपूर्णांक_current_perक्रमmance_level(व्योम *handle,
					       काष्ठा seq_file *m)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;
	काष्ठा kv_घातer_info *pi = kv_get_pi(adev);
	u32 current_index =
		(RREG32_SMC(ixTARGET_AND_CURRENT_PROखाता_INDEX) &
		TARGET_AND_CURRENT_PROखाता_INDEX__CURR_SCLK_INDEX_MASK) >>
		TARGET_AND_CURRENT_PROखाता_INDEX__CURR_SCLK_INDEX__SHIFT;
	u32 sclk, पंचांगp;
	u16 vddc;

	अगर (current_index >= SMU__NUM_SCLK_DPM_STATE) अणु
		seq_म_लिखो(m, "invalid dpm profile %d\n", current_index);
	पूर्ण अन्यथा अणु
		sclk = be32_to_cpu(pi->graphics_level[current_index].SclkFrequency);
		पंचांगp = (RREG32_SMC(ixSMU_VOLTAGE_STATUS) &
			SMU_VOLTAGE_STATUS__SMU_VOLTAGE_CURRENT_LEVEL_MASK) >>
			SMU_VOLTAGE_STATUS__SMU_VOLTAGE_CURRENT_LEVEL__SHIFT;
		vddc = kv_convert_8bit_index_to_voltage(adev, (u16)पंचांगp);
		seq_म_लिखो(m, "uvd    %sabled\n", pi->uvd_घातer_gated ? "dis" : "en");
		seq_म_लिखो(m, "vce    %sabled\n", pi->vce_घातer_gated ? "dis" : "en");
		seq_म_लिखो(m, "power level %d    sclk: %u vddc: %u\n",
			   current_index, sclk, vddc);
	पूर्ण
पूर्ण

अटल व्योम
kv_dpm_prपूर्णांक_घातer_state(व्योम *handle, व्योम *request_ps)
अणु
	पूर्णांक i;
	काष्ठा amdgpu_ps *rps = (काष्ठा amdgpu_ps *)request_ps;
	काष्ठा kv_ps *ps = kv_get_ps(rps);
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	amdgpu_dpm_prपूर्णांक_class_info(rps->class, rps->class2);
	amdgpu_dpm_prपूर्णांक_cap_info(rps->caps);
	prपूर्णांकk("\tuvd    vclk: %d dclk: %d\n", rps->vclk, rps->dclk);
	क्रम (i = 0; i < ps->num_levels; i++) अणु
		काष्ठा kv_pl *pl = &ps->levels[i];
		prपूर्णांकk("\t\tpower level %d    sclk: %u vddc: %u\n",
		       i, pl->sclk,
		       kv_convert_8bit_index_to_voltage(adev, pl->vddc_index));
	पूर्ण
	amdgpu_dpm_prपूर्णांक_ps_status(adev, rps);
पूर्ण

अटल व्योम kv_dpm_fini(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < adev->pm.dpm.num_ps; i++) अणु
		kमुक्त(adev->pm.dpm.ps[i].ps_priv);
	पूर्ण
	kमुक्त(adev->pm.dpm.ps);
	kमुक्त(adev->pm.dpm.priv);
	amdgpu_मुक्त_extended_घातer_table(adev);
पूर्ण

अटल व्योम kv_dpm_display_configuration_changed(व्योम *handle)
अणु

पूर्ण

अटल u32 kv_dpm_get_sclk(व्योम *handle, bool low)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;
	काष्ठा kv_घातer_info *pi = kv_get_pi(adev);
	काष्ठा kv_ps *requested_state = kv_get_ps(&pi->requested_rps);

	अगर (low)
		वापस requested_state->levels[0].sclk;
	अन्यथा
		वापस requested_state->levels[requested_state->num_levels - 1].sclk;
पूर्ण

अटल u32 kv_dpm_get_mclk(व्योम *handle, bool low)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;
	काष्ठा kv_घातer_info *pi = kv_get_pi(adev);

	वापस pi->sys_info.bootup_uma_clk;
पूर्ण

/* get temperature in millidegrees */
अटल पूर्णांक kv_dpm_get_temp(व्योम *handle)
अणु
	u32 temp;
	पूर्णांक actual_temp = 0;
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	temp = RREG32_SMC(0xC0300E0C);

	अगर (temp)
		actual_temp = (temp / 8) - 49;
	अन्यथा
		actual_temp = 0;

	actual_temp = actual_temp * 1000;

	वापस actual_temp;
पूर्ण

अटल पूर्णांक kv_dpm_early_init(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	adev->घातerplay.pp_funcs = &kv_dpm_funcs;
	adev->घातerplay.pp_handle = adev;
	kv_dpm_set_irq_funcs(adev);

	वापस 0;
पूर्ण

अटल पूर्णांक kv_dpm_late_init(व्योम *handle)
अणु
	/* घातerकरोwn unused blocks क्रम now */
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	अगर (!adev->pm.dpm_enabled)
		वापस 0;

	kv_dpm_घातergate_acp(adev, true);
	kv_dpm_घातergate_samu(adev, true);

	वापस 0;
पूर्ण

अटल पूर्णांक kv_dpm_sw_init(व्योम *handle)
अणु
	पूर्णांक ret;
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	ret = amdgpu_irq_add_id(adev, AMDGPU_IRQ_CLIENTID_LEGACY, 230,
				&adev->pm.dpm.thermal.irq);
	अगर (ret)
		वापस ret;

	ret = amdgpu_irq_add_id(adev, AMDGPU_IRQ_CLIENTID_LEGACY, 231,
				&adev->pm.dpm.thermal.irq);
	अगर (ret)
		वापस ret;

	/* शेष to balanced state */
	adev->pm.dpm.state = POWER_STATE_TYPE_BALANCED;
	adev->pm.dpm.user_state = POWER_STATE_TYPE_BALANCED;
	adev->pm.dpm.क्रमced_level = AMD_DPM_FORCED_LEVEL_AUTO;
	adev->pm.शेष_sclk = adev->घड़ी.शेष_sclk;
	adev->pm.शेष_mclk = adev->घड़ी.शेष_mclk;
	adev->pm.current_sclk = adev->घड़ी.शेष_sclk;
	adev->pm.current_mclk = adev->घड़ी.शेष_mclk;
	adev->pm.पूर्णांक_thermal_type = THERMAL_TYPE_NONE;

	अगर (amdgpu_dpm == 0)
		वापस 0;

	INIT_WORK(&adev->pm.dpm.thermal.work, amdgpu_dpm_thermal_work_handler);
	mutex_lock(&adev->pm.mutex);
	ret = kv_dpm_init(adev);
	अगर (ret)
		जाओ dpm_failed;
	adev->pm.dpm.current_ps = adev->pm.dpm.requested_ps = adev->pm.dpm.boot_ps;
	अगर (amdgpu_dpm == 1)
		amdgpu_pm_prपूर्णांक_घातer_states(adev);
	mutex_unlock(&adev->pm.mutex);
	DRM_INFO("amdgpu: dpm initialized\n");

	वापस 0;

dpm_failed:
	kv_dpm_fini(adev);
	mutex_unlock(&adev->pm.mutex);
	DRM_ERROR("amdgpu: dpm initialization failed\n");
	वापस ret;
पूर्ण

अटल पूर्णांक kv_dpm_sw_fini(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	flush_work(&adev->pm.dpm.thermal.work);

	mutex_lock(&adev->pm.mutex);
	kv_dpm_fini(adev);
	mutex_unlock(&adev->pm.mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक kv_dpm_hw_init(व्योम *handle)
अणु
	पूर्णांक ret;
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	अगर (!amdgpu_dpm)
		वापस 0;

	mutex_lock(&adev->pm.mutex);
	kv_dpm_setup_asic(adev);
	ret = kv_dpm_enable(adev);
	अगर (ret)
		adev->pm.dpm_enabled = false;
	अन्यथा
		adev->pm.dpm_enabled = true;
	mutex_unlock(&adev->pm.mutex);
	amdgpu_pm_compute_घड़ीs(adev);
	वापस ret;
पूर्ण

अटल पूर्णांक kv_dpm_hw_fini(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	अगर (adev->pm.dpm_enabled) अणु
		mutex_lock(&adev->pm.mutex);
		kv_dpm_disable(adev);
		mutex_unlock(&adev->pm.mutex);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक kv_dpm_suspend(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	अगर (adev->pm.dpm_enabled) अणु
		mutex_lock(&adev->pm.mutex);
		/* disable dpm */
		kv_dpm_disable(adev);
		/* reset the घातer state */
		adev->pm.dpm.current_ps = adev->pm.dpm.requested_ps = adev->pm.dpm.boot_ps;
		mutex_unlock(&adev->pm.mutex);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक kv_dpm_resume(व्योम *handle)
अणु
	पूर्णांक ret;
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	अगर (adev->pm.dpm_enabled) अणु
		/* asic init will reset to the boot state */
		mutex_lock(&adev->pm.mutex);
		kv_dpm_setup_asic(adev);
		ret = kv_dpm_enable(adev);
		अगर (ret)
			adev->pm.dpm_enabled = false;
		अन्यथा
			adev->pm.dpm_enabled = true;
		mutex_unlock(&adev->pm.mutex);
		अगर (adev->pm.dpm_enabled)
			amdgpu_pm_compute_घड़ीs(adev);
	पूर्ण
	वापस 0;
पूर्ण

अटल bool kv_dpm_is_idle(व्योम *handle)
अणु
	वापस true;
पूर्ण

अटल पूर्णांक kv_dpm_रुको_क्रम_idle(व्योम *handle)
अणु
	वापस 0;
पूर्ण


अटल पूर्णांक kv_dpm_soft_reset(व्योम *handle)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक kv_dpm_set_पूर्णांकerrupt_state(काष्ठा amdgpu_device *adev,
				      काष्ठा amdgpu_irq_src *src,
				      अचिन्हित type,
				      क्रमागत amdgpu_पूर्णांकerrupt_state state)
अणु
	u32 cg_thermal_पूर्णांक;

	चयन (type) अणु
	हाल AMDGPU_THERMAL_IRQ_LOW_TO_HIGH:
		चयन (state) अणु
		हाल AMDGPU_IRQ_STATE_DISABLE:
			cg_thermal_पूर्णांक = RREG32_SMC(ixCG_THERMAL_INT_CTRL);
			cg_thermal_पूर्णांक &= ~CG_THERMAL_INT_CTRL__THERM_INTH_MASK_MASK;
			WREG32_SMC(ixCG_THERMAL_INT_CTRL, cg_thermal_पूर्णांक);
			अवरोध;
		हाल AMDGPU_IRQ_STATE_ENABLE:
			cg_thermal_पूर्णांक = RREG32_SMC(ixCG_THERMAL_INT_CTRL);
			cg_thermal_पूर्णांक |= CG_THERMAL_INT_CTRL__THERM_INTH_MASK_MASK;
			WREG32_SMC(ixCG_THERMAL_INT_CTRL, cg_thermal_पूर्णांक);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;

	हाल AMDGPU_THERMAL_IRQ_HIGH_TO_LOW:
		चयन (state) अणु
		हाल AMDGPU_IRQ_STATE_DISABLE:
			cg_thermal_पूर्णांक = RREG32_SMC(ixCG_THERMAL_INT_CTRL);
			cg_thermal_पूर्णांक &= ~CG_THERMAL_INT_CTRL__THERM_INTL_MASK_MASK;
			WREG32_SMC(ixCG_THERMAL_INT_CTRL, cg_thermal_पूर्णांक);
			अवरोध;
		हाल AMDGPU_IRQ_STATE_ENABLE:
			cg_thermal_पूर्णांक = RREG32_SMC(ixCG_THERMAL_INT_CTRL);
			cg_thermal_पूर्णांक |= CG_THERMAL_INT_CTRL__THERM_INTL_MASK_MASK;
			WREG32_SMC(ixCG_THERMAL_INT_CTRL, cg_thermal_पूर्णांक);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक kv_dpm_process_पूर्णांकerrupt(काष्ठा amdgpu_device *adev,
				    काष्ठा amdgpu_irq_src *source,
				    काष्ठा amdgpu_iv_entry *entry)
अणु
	bool queue_thermal = false;

	अगर (entry == शून्य)
		वापस -EINVAL;

	चयन (entry->src_id) अणु
	हाल 230: /* thermal low to high */
		DRM_DEBUG("IH: thermal low to high\n");
		adev->pm.dpm.thermal.high_to_low = false;
		queue_thermal = true;
		अवरोध;
	हाल 231: /* thermal high to low */
		DRM_DEBUG("IH: thermal high to low\n");
		adev->pm.dpm.thermal.high_to_low = true;
		queue_thermal = true;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	अगर (queue_thermal)
		schedule_work(&adev->pm.dpm.thermal.work);

	वापस 0;
पूर्ण

अटल पूर्णांक kv_dpm_set_घड़ीgating_state(व्योम *handle,
					  क्रमागत amd_घड़ीgating_state state)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक kv_dpm_set_घातergating_state(व्योम *handle,
					  क्रमागत amd_घातergating_state state)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत bool kv_are_घातer_levels_equal(स्थिर काष्ठा kv_pl *kv_cpl1,
						स्थिर काष्ठा kv_pl *kv_cpl2)
अणु
	वापस ((kv_cpl1->sclk == kv_cpl2->sclk) &&
		  (kv_cpl1->vddc_index == kv_cpl2->vddc_index) &&
		  (kv_cpl1->ds_भागider_index == kv_cpl2->ds_भागider_index) &&
		  (kv_cpl1->क्रमce_nbp_state == kv_cpl2->क्रमce_nbp_state));
पूर्ण

अटल पूर्णांक kv_check_state_equal(व्योम *handle,
				व्योम *current_ps,
				व्योम *request_ps,
				bool *equal)
अणु
	काष्ठा kv_ps *kv_cps;
	काष्ठा kv_ps *kv_rps;
	पूर्णांक i;
	काष्ठा amdgpu_ps *cps = (काष्ठा amdgpu_ps *)current_ps;
	काष्ठा amdgpu_ps *rps = (काष्ठा amdgpu_ps *)request_ps;
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	अगर (adev == शून्य || cps == शून्य || rps == शून्य || equal == शून्य)
		वापस -EINVAL;

	kv_cps = kv_get_ps(cps);
	kv_rps = kv_get_ps(rps);

	अगर (kv_cps == शून्य) अणु
		*equal = false;
		वापस 0;
	पूर्ण

	अगर (kv_cps->num_levels != kv_rps->num_levels) अणु
		*equal = false;
		वापस 0;
	पूर्ण

	क्रम (i = 0; i < kv_cps->num_levels; i++) अणु
		अगर (!kv_are_घातer_levels_equal(&(kv_cps->levels[i]),
					&(kv_rps->levels[i]))) अणु
			*equal = false;
			वापस 0;
		पूर्ण
	पूर्ण

	/* If all perक्रमmance levels are the same try to use the UVD घड़ीs to अवरोध the tie.*/
	*equal = ((cps->vclk == rps->vclk) && (cps->dclk == rps->dclk));
	*equal &= ((cps->evclk == rps->evclk) && (cps->ecclk == rps->ecclk));

	वापस 0;
पूर्ण

अटल पूर्णांक kv_dpm_पढ़ो_sensor(व्योम *handle, पूर्णांक idx,
			      व्योम *value, पूर्णांक *size)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;
	काष्ठा kv_घातer_info *pi = kv_get_pi(adev);
	uपूर्णांक32_t sclk;
	u32 pl_index =
		(RREG32_SMC(ixTARGET_AND_CURRENT_PROखाता_INDEX) &
		TARGET_AND_CURRENT_PROखाता_INDEX__CURR_SCLK_INDEX_MASK) >>
		TARGET_AND_CURRENT_PROखाता_INDEX__CURR_SCLK_INDEX__SHIFT;

	/* size must be at least 4 bytes क्रम all sensors */
	अगर (*size < 4)
		वापस -EINVAL;

	चयन (idx) अणु
	हाल AMDGPU_PP_SENSOR_GFX_SCLK:
		अगर (pl_index < SMU__NUM_SCLK_DPM_STATE) अणु
			sclk = be32_to_cpu(
				pi->graphics_level[pl_index].SclkFrequency);
			*((uपूर्णांक32_t *)value) = sclk;
			*size = 4;
			वापस 0;
		पूर्ण
		वापस -EINVAL;
	हाल AMDGPU_PP_SENSOR_GPU_TEMP:
		*((uपूर्णांक32_t *)value) = kv_dpm_get_temp(adev);
		*size = 4;
		वापस 0;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक kv_set_घातergating_by_smu(व्योम *handle,
				uपूर्णांक32_t block_type, bool gate)
अणु
	चयन (block_type) अणु
	हाल AMD_IP_BLOCK_TYPE_UVD:
		kv_dpm_घातergate_uvd(handle, gate);
		अवरोध;
	हाल AMD_IP_BLOCK_TYPE_VCE:
		kv_dpm_घातergate_vce(handle, gate);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा amd_ip_funcs kv_dpm_ip_funcs = अणु
	.name = "kv_dpm",
	.early_init = kv_dpm_early_init,
	.late_init = kv_dpm_late_init,
	.sw_init = kv_dpm_sw_init,
	.sw_fini = kv_dpm_sw_fini,
	.hw_init = kv_dpm_hw_init,
	.hw_fini = kv_dpm_hw_fini,
	.suspend = kv_dpm_suspend,
	.resume = kv_dpm_resume,
	.is_idle = kv_dpm_is_idle,
	.रुको_क्रम_idle = kv_dpm_रुको_क्रम_idle,
	.soft_reset = kv_dpm_soft_reset,
	.set_घड़ीgating_state = kv_dpm_set_घड़ीgating_state,
	.set_घातergating_state = kv_dpm_set_घातergating_state,
पूर्ण;

स्थिर काष्ठा amdgpu_ip_block_version kv_smu_ip_block =
अणु
	.type = AMD_IP_BLOCK_TYPE_SMC,
	.major = 1,
	.minor = 0,
	.rev = 0,
	.funcs = &kv_dpm_ip_funcs,
पूर्ण;

अटल स्थिर काष्ठा amd_pm_funcs kv_dpm_funcs = अणु
	.pre_set_घातer_state = &kv_dpm_pre_set_घातer_state,
	.set_घातer_state = &kv_dpm_set_घातer_state,
	.post_set_घातer_state = &kv_dpm_post_set_घातer_state,
	.display_configuration_changed = &kv_dpm_display_configuration_changed,
	.get_sclk = &kv_dpm_get_sclk,
	.get_mclk = &kv_dpm_get_mclk,
	.prपूर्णांक_घातer_state = &kv_dpm_prपूर्णांक_घातer_state,
	.debugfs_prपूर्णांक_current_perक्रमmance_level = &kv_dpm_debugfs_prपूर्णांक_current_perक्रमmance_level,
	.क्रमce_perक्रमmance_level = &kv_dpm_क्रमce_perक्रमmance_level,
	.set_घातergating_by_smu = kv_set_घातergating_by_smu,
	.enable_bapm = &kv_dpm_enable_bapm,
	.get_vce_घड़ी_state = amdgpu_get_vce_घड़ी_state,
	.check_state_equal = kv_check_state_equal,
	.पढ़ो_sensor = &kv_dpm_पढ़ो_sensor,
पूर्ण;

अटल स्थिर काष्ठा amdgpu_irq_src_funcs kv_dpm_irq_funcs = अणु
	.set = kv_dpm_set_पूर्णांकerrupt_state,
	.process = kv_dpm_process_पूर्णांकerrupt,
पूर्ण;

अटल व्योम kv_dpm_set_irq_funcs(काष्ठा amdgpu_device *adev)
अणु
	adev->pm.dpm.thermal.irq.num_types = AMDGPU_THERMAL_IRQ_LAST;
	adev->pm.dpm.thermal.irq.funcs = &kv_dpm_irq_funcs;
पूर्ण
