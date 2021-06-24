<शैली गुरु>
/*
 * Copyright 2014 Advanced Micro Devices, Inc.
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

#अगर_अघोषित __AMDGPU_ATOMBIOS_H__
#घोषणा __AMDGPU_ATOMBIOS_H__

काष्ठा atom_घड़ी_भागiders अणु
	u32 post_भाग;
	जोड़ अणु
		काष्ठा अणु
#अगर_घोषित __BIG_ENDIAN
			u32 reserved : 6;
			u32 whole_fb_भाग : 12;
			u32 frac_fb_भाग : 14;
#अन्यथा
			u32 frac_fb_भाग : 14;
			u32 whole_fb_भाग : 12;
			u32 reserved : 6;
#पूर्ण_अगर
		पूर्ण;
		u32 fb_भाग;
	पूर्ण;
	u32 ref_भाग;
	bool enable_post_भाग;
	bool enable_dithen;
	u32 vco_mode;
	u32 real_घड़ी;
	/* added क्रम CI */
	u32 post_भागider;
	u32 flags;
पूर्ण;

काष्ठा atom_mpll_param अणु
	जोड़ अणु
		काष्ठा अणु
#अगर_घोषित __BIG_ENDIAN
			u32 reserved : 8;
			u32 clkfrac : 12;
			u32 clkf : 12;
#अन्यथा
			u32 clkf : 12;
			u32 clkfrac : 12;
			u32 reserved : 8;
#पूर्ण_अगर
		पूर्ण;
		u32 fb_भाग;
	पूर्ण;
	u32 post_भाग;
	u32 bwcntl;
	u32 dll_speed;
	u32 vco_mode;
	u32 yclk_sel;
	u32 qdr;
	u32 half_rate;
पूर्ण;

#घोषणा MEM_TYPE_GDDR5  0x50
#घोषणा MEM_TYPE_GDDR4  0x40
#घोषणा MEM_TYPE_GDDR3  0x30
#घोषणा MEM_TYPE_DDR2   0x20
#घोषणा MEM_TYPE_GDDR1  0x10
#घोषणा MEM_TYPE_DDR3   0xb0
#घोषणा MEM_TYPE_MASK   0xf0

काष्ठा atom_memory_info अणु
	u8 mem_venकरोr;
	u8 mem_type;
पूर्ण;

#घोषणा MAX_AC_TIMING_ENTRIES 16

काष्ठा atom_memory_घड़ी_range_table
अणु
	u8 num_entries;
	u8 rsv[3];
	u32 mclk[MAX_AC_TIMING_ENTRIES];
पूर्ण;

#घोषणा VBIOS_MC_REGISTER_ARRAY_SIZE 32
#घोषणा VBIOS_MAX_AC_TIMING_ENTRIES 20

काष्ठा atom_mc_reg_entry अणु
	u32 mclk_max;
	u32 mc_data[VBIOS_MC_REGISTER_ARRAY_SIZE];
पूर्ण;

काष्ठा atom_mc_रेजिस्टर_address अणु
	u16 s1;
	u8 pre_reg_data;
पूर्ण;

काष्ठा atom_mc_reg_table अणु
	u8 last;
	u8 num_entries;
	काष्ठा atom_mc_reg_entry mc_reg_table_entry[VBIOS_MAX_AC_TIMING_ENTRIES];
	काष्ठा atom_mc_रेजिस्टर_address mc_reg_address[VBIOS_MC_REGISTER_ARRAY_SIZE];
पूर्ण;

#घोषणा MAX_VOLTAGE_ENTRIES 32

काष्ठा atom_voltage_table_entry
अणु
	u16 value;
	u32 smio_low;
पूर्ण;

काष्ठा atom_voltage_table
अणु
	u32 count;
	u32 mask_low;
	u32 phase_delay;
	काष्ठा atom_voltage_table_entry entries[MAX_VOLTAGE_ENTRIES];
पूर्ण;

काष्ठा amdgpu_gpio_rec
amdgpu_atombios_lookup_gpio(काष्ठा amdgpu_device *adev,
			    u8 id);

काष्ठा amdgpu_i2c_bus_rec amdgpu_atombios_lookup_i2c_gpio(काष्ठा amdgpu_device *adev,
							  uपूर्णांक8_t id);
व्योम amdgpu_atombios_i2c_init(काष्ठा amdgpu_device *adev);

bool amdgpu_atombios_has_dce_engine_info(काष्ठा amdgpu_device *adev);

bool amdgpu_atombios_get_connector_info_from_object_table(काष्ठा amdgpu_device *adev);

पूर्णांक amdgpu_atombios_get_घड़ी_info(काष्ठा amdgpu_device *adev);

पूर्णांक amdgpu_atombios_get_gfx_info(काष्ठा amdgpu_device *adev);

पूर्णांक amdgpu_atombios_get_vram_width(काष्ठा amdgpu_device *adev);

bool amdgpu_atombios_get_asic_ss_info(काष्ठा amdgpu_device *adev,
				      काष्ठा amdgpu_atom_ss *ss,
				      पूर्णांक id, u32 घड़ी);

पूर्णांक amdgpu_atombios_get_घड़ी_भागiders(काष्ठा amdgpu_device *adev,
				       u8 घड़ी_प्रकारype,
				       u32 घड़ी,
				       bool strobe_mode,
				       काष्ठा atom_घड़ी_भागiders *भागiders);

पूर्णांक amdgpu_atombios_get_memory_pll_भागiders(काष्ठा amdgpu_device *adev,
					    u32 घड़ी,
					    bool strobe_mode,
					    काष्ठा atom_mpll_param *mpll_param);

व्योम amdgpu_atombios_set_engine_dram_timings(काष्ठा amdgpu_device *adev,
					     u32 eng_घड़ी, u32 mem_घड़ी);

bool
amdgpu_atombios_is_voltage_gpio(काष्ठा amdgpu_device *adev,
				u8 voltage_type, u8 voltage_mode);

पूर्णांक amdgpu_atombios_get_voltage_table(काष्ठा amdgpu_device *adev,
				      u8 voltage_type, u8 voltage_mode,
				      काष्ठा atom_voltage_table *voltage_table);

पूर्णांक amdgpu_atombios_init_mc_reg_table(काष्ठा amdgpu_device *adev,
				      u8 module_index,
				      काष्ठा atom_mc_reg_table *reg_table);

bool amdgpu_atombios_has_gpu_भवization_table(काष्ठा amdgpu_device *adev);

व्योम amdgpu_atombios_scratch_regs_lock(काष्ठा amdgpu_device *adev, bool lock);
व्योम amdgpu_atombios_scratch_regs_engine_hung(काष्ठा amdgpu_device *adev,
					      bool hung);
bool amdgpu_atombios_scratch_need_asic_init(काष्ठा amdgpu_device *adev);

व्योम amdgpu_atombios_copy_swap(u8 *dst, u8 *src, u8 num_bytes, bool to_le);
पूर्णांक amdgpu_atombios_get_max_vddc(काष्ठा amdgpu_device *adev, u8 voltage_type,
			     u16 voltage_id, u16 *voltage);
पूर्णांक amdgpu_atombios_get_leakage_vddc_based_on_leakage_idx(काष्ठा amdgpu_device *adev,
						      u16 *voltage,
						      u16 leakage_idx);
व्योम amdgpu_atombios_get_शेष_voltages(काष्ठा amdgpu_device *adev,
					  u16 *vddc, u16 *vddci, u16 *mvdd);
पूर्णांक amdgpu_atombios_get_घड़ी_भागiders(काष्ठा amdgpu_device *adev,
				       u8 घड़ी_प्रकारype,
				       u32 घड़ी,
				       bool strobe_mode,
				       काष्ठा atom_घड़ी_भागiders *भागiders);
पूर्णांक amdgpu_atombios_get_svi2_info(काष्ठा amdgpu_device *adev,
			      u8 voltage_type,
			      u8 *svd_gpio_id, u8 *svc_gpio_id);

पूर्णांक amdgpu_atombios_get_data_table(काष्ठा amdgpu_device *adev,
				   uपूर्णांक32_t table,
				   uपूर्णांक16_t *size,
				   uपूर्णांक8_t *frev,
				   uपूर्णांक8_t *crev,
				   uपूर्णांक8_t **addr);

व्योम amdgpu_atombios_fini(काष्ठा amdgpu_device *adev);
पूर्णांक amdgpu_atombios_init(काष्ठा amdgpu_device *adev);

#पूर्ण_अगर
