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

#अगर_अघोषित __SOC15_H__
#घोषणा __SOC15_H__

#समावेश "nbio_v6_1.h"
#समावेश "nbio_v7_0.h"
#समावेश "nbio_v7_4.h"

#घोषणा SOC15_FLUSH_GPU_TLB_NUM_WREG		6
#घोषणा SOC15_FLUSH_GPU_TLB_NUM_REG_WAIT	3

बाह्य स्थिर काष्ठा amd_ip_funcs soc15_common_ip_funcs;

काष्ठा soc15_reg_golden अणु
	u32	hwip;
	u32	instance;
	u32	segment;
	u32	reg;
	u32	and_mask;
	u32	or_mask;
पूर्ण;

काष्ठा soc15_reg_rlcg अणु
	u32	hwip;
	u32	instance;
	u32	segment;
	u32	reg;
पूर्ण;

काष्ठा soc15_reg अणु
	uपूर्णांक32_t hwip;
	uपूर्णांक32_t inst;
	uपूर्णांक32_t seg;
	uपूर्णांक32_t reg_offset;
पूर्ण;

काष्ठा soc15_reg_entry अणु
	uपूर्णांक32_t hwip;
	uपूर्णांक32_t inst;
	uपूर्णांक32_t seg;
	uपूर्णांक32_t reg_offset;
	uपूर्णांक32_t reg_value;
	uपूर्णांक32_t se_num;
	uपूर्णांक32_t instance;
पूर्ण;

काष्ठा soc15_allowed_रेजिस्टर_entry अणु
	uपूर्णांक32_t hwip;
	uपूर्णांक32_t inst;
	uपूर्णांक32_t seg;
	uपूर्णांक32_t reg_offset;
	bool grbm_indexed;
पूर्ण;

काष्ठा soc15_ras_field_entry अणु
	स्थिर अक्षर *name;
	uपूर्णांक32_t hwip;
	uपूर्णांक32_t inst;
	uपूर्णांक32_t seg;
	uपूर्णांक32_t reg_offset;
	uपूर्णांक32_t sec_count_mask;
	uपूर्णांक32_t sec_count_shअगरt;
	uपूर्णांक32_t ded_count_mask;
	uपूर्णांक32_t ded_count_shअगरt;
पूर्ण;

#घोषणा SOC15_REG_ENTRY(ip, inst, reg)	ip##_HWIP, inst, reg##_BASE_IDX, reg

#घोषणा SOC15_REG_ENTRY_OFFSET(entry)	(adev->reg_offset[entry.hwip][entry.inst][entry.seg] + entry.reg_offset)

#घोषणा SOC15_REG_GOLDEN_VALUE(ip, inst, reg, and_mask, or_mask) \
	अणु ip##_HWIP, inst, reg##_BASE_IDX, reg, and_mask, or_mask पूर्ण

#घोषणा SOC15_REG_FIELD(reg, field) reg##__##field##_MASK, reg##__##field##__SHIFT

#घोषणा SOC15_REG_FIELD_VAL(val, mask, shअगरt)	(((val) & mask) >> shअगरt)

#घोषणा SOC15_RAS_REG_FIELD_VAL(val, entry, field) SOC15_REG_FIELD_VAL((val), (entry).field##_count_mask, (entry).field##_count_shअगरt)

व्योम soc15_grbm_select(काष्ठा amdgpu_device *adev,
		    u32 me, u32 pipe, u32 queue, u32 vmid);
व्योम soc15_set_virt_ops(काष्ठा amdgpu_device *adev);
पूर्णांक soc15_set_ip_blocks(काष्ठा amdgpu_device *adev);

व्योम soc15_program_रेजिस्टर_sequence(काष्ठा amdgpu_device *adev,
					     स्थिर काष्ठा soc15_reg_golden *रेजिस्टरs,
					     स्थिर u32 array_size);

पूर्णांक vega10_reg_base_init(काष्ठा amdgpu_device *adev);
पूर्णांक vega20_reg_base_init(काष्ठा amdgpu_device *adev);
पूर्णांक arct_reg_base_init(काष्ठा amdgpu_device *adev);
पूर्णांक aldebaran_reg_base_init(काष्ठा amdgpu_device *adev);

व्योम vega10_करोorbell_index_init(काष्ठा amdgpu_device *adev);
व्योम vega20_करोorbell_index_init(काष्ठा amdgpu_device *adev);
#पूर्ण_अगर
