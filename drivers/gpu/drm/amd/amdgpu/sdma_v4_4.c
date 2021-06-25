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
 *
 */
#समावेश "amdgpu.h"
#समावेश "sdma/sdma_4_4_0_offset.h"
#समावेश "sdma/sdma_4_4_0_sh_mask.h"
#समावेश "soc15.h"
#समावेश "amdgpu_ras.h"

#घोषणा SDMA1_REG_OFFSET 0x600
#घोषणा SDMA2_REG_OFFSET 0x1cda0
#घोषणा SDMA3_REG_OFFSET 0x1d1a0
#घोषणा SDMA4_REG_OFFSET 0x1d5a0

/* helper function that allow only use sdma0 रेजिस्टर offset
 * to calculate रेजिस्टर offset क्रम all the sdma instances */
अटल uपूर्णांक32_t sdma_v4_4_get_reg_offset(काष्ठा amdgpu_device *adev,
					 uपूर्णांक32_t instance,
					 uपूर्णांक32_t offset)
अणु
	uपूर्णांक32_t sdma_base = adev->reg_offset[SDMA0_HWIP][0][0];

	चयन (instance) अणु
	हाल 0:
		वापस (sdma_base + offset);
	हाल 1:
		वापस (sdma_base + SDMA1_REG_OFFSET + offset);
	हाल 2:
		वापस (sdma_base + SDMA2_REG_OFFSET + offset);
	हाल 3:
		वापस (sdma_base + SDMA3_REG_OFFSET + offset);
	हाल 4:
		वापस (sdma_base + SDMA4_REG_OFFSET + offset);
	शेष:
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा soc15_ras_field_entry sdma_v4_4_ras_fields[] = अणु
	अणु "SDMA_MBANK_DATA_BUF0_SED", SOC15_REG_ENTRY(SDMA0, 0, regSDMA0_EDC_COUNTER),
	SOC15_REG_FIELD(SDMA0_EDC_COUNTER, SDMA_MBANK_DATA_BUF0_SED),
	0, 0,
	पूर्ण,
	अणु "SDMA_MBANK_DATA_BUF1_SED", SOC15_REG_ENTRY(SDMA0, 0, regSDMA0_EDC_COUNTER),
	SOC15_REG_FIELD(SDMA0_EDC_COUNTER, SDMA_MBANK_DATA_BUF1_SED),
	0, 0,
	पूर्ण,
	अणु "SDMA_MBANK_DATA_BUF2_SED", SOC15_REG_ENTRY(SDMA0, 0, regSDMA0_EDC_COUNTER),
	SOC15_REG_FIELD(SDMA0_EDC_COUNTER, SDMA_MBANK_DATA_BUF2_SED),
	0, 0,
	पूर्ण,
	अणु "SDMA_MBANK_DATA_BUF3_SED", SOC15_REG_ENTRY(SDMA0, 0, regSDMA0_EDC_COUNTER),
	SOC15_REG_FIELD(SDMA0_EDC_COUNTER, SDMA_MBANK_DATA_BUF3_SED),
	0, 0,
	पूर्ण,
	अणु "SDMA_MBANK_DATA_BUF4_SED", SOC15_REG_ENTRY(SDMA0, 0, regSDMA0_EDC_COUNTER),
	SOC15_REG_FIELD(SDMA0_EDC_COUNTER, SDMA_MBANK_DATA_BUF4_SED),
	0, 0,
	पूर्ण,
	अणु "SDMA_MBANK_DATA_BUF5_SED", SOC15_REG_ENTRY(SDMA0, 0, regSDMA0_EDC_COUNTER),
	SOC15_REG_FIELD(SDMA0_EDC_COUNTER, SDMA_MBANK_DATA_BUF5_SED),
	0, 0,
	पूर्ण,
	अणु "SDMA_MBANK_DATA_BUF6_SED", SOC15_REG_ENTRY(SDMA0, 0, regSDMA0_EDC_COUNTER),
	SOC15_REG_FIELD(SDMA0_EDC_COUNTER, SDMA_MBANK_DATA_BUF6_SED),
	0, 0,
	पूर्ण,
	अणु "SDMA_MBANK_DATA_BUF7_SED", SOC15_REG_ENTRY(SDMA0, 0, regSDMA0_EDC_COUNTER),
	SOC15_REG_FIELD(SDMA0_EDC_COUNTER, SDMA_MBANK_DATA_BUF7_SED),
	0, 0,
	पूर्ण,
	अणु "SDMA_MBANK_DATA_BUF8_SED", SOC15_REG_ENTRY(SDMA0, 0, regSDMA0_EDC_COUNTER),
	SOC15_REG_FIELD(SDMA0_EDC_COUNTER, SDMA_MBANK_DATA_BUF8_SED),
	0, 0,
	पूर्ण,
	अणु "SDMA_MBANK_DATA_BUF9_SED", SOC15_REG_ENTRY(SDMA0, 0, regSDMA0_EDC_COUNTER),
	SOC15_REG_FIELD(SDMA0_EDC_COUNTER, SDMA_MBANK_DATA_BUF9_SED),
	0, 0,
	पूर्ण,
	अणु "SDMA_MBANK_DATA_BUF10_SED", SOC15_REG_ENTRY(SDMA0, 0, regSDMA0_EDC_COUNTER),
	SOC15_REG_FIELD(SDMA0_EDC_COUNTER, SDMA_MBANK_DATA_BUF10_SED),
	0, 0,
	पूर्ण,
	अणु "SDMA_MBANK_DATA_BUF11_SED", SOC15_REG_ENTRY(SDMA0, 0, regSDMA0_EDC_COUNTER),
	SOC15_REG_FIELD(SDMA0_EDC_COUNTER, SDMA_MBANK_DATA_BUF11_SED),
	0, 0,
	पूर्ण,
	अणु "SDMA_MBANK_DATA_BUF12_SED", SOC15_REG_ENTRY(SDMA0, 0, regSDMA0_EDC_COUNTER),
	SOC15_REG_FIELD(SDMA0_EDC_COUNTER, SDMA_MBANK_DATA_BUF12_SED),
	0, 0,
	पूर्ण,
	अणु "SDMA_MBANK_DATA_BUF13_SED", SOC15_REG_ENTRY(SDMA0, 0, regSDMA0_EDC_COUNTER),
	SOC15_REG_FIELD(SDMA0_EDC_COUNTER, SDMA_MBANK_DATA_BUF13_SED),
	0, 0,
	पूर्ण,
	अणु "SDMA_MBANK_DATA_BUF14_SED", SOC15_REG_ENTRY(SDMA0, 0, regSDMA0_EDC_COUNTER),
	SOC15_REG_FIELD(SDMA0_EDC_COUNTER, SDMA_MBANK_DATA_BUF14_SED),
	0, 0,
	पूर्ण,
	अणु "SDMA_MBANK_DATA_BUF15_SED", SOC15_REG_ENTRY(SDMA0, 0, regSDMA0_EDC_COUNTER),
	SOC15_REG_FIELD(SDMA0_EDC_COUNTER, SDMA_MBANK_DATA_BUF15_SED),
	0, 0,
	पूर्ण,
	अणु "SDMA_UCODE_BUF_SED", SOC15_REG_ENTRY(SDMA0, 0, regSDMA0_EDC_COUNTER2),
	SOC15_REG_FIELD(SDMA0_EDC_COUNTER2, SDMA_UCODE_BUF_SED),
	0, 0,
	पूर्ण,
	अणु "SDMA_RB_CMD_BUF_SED", SOC15_REG_ENTRY(SDMA0, 0, regSDMA0_EDC_COUNTER2),
	SOC15_REG_FIELD(SDMA0_EDC_COUNTER2, SDMA_RB_CMD_BUF_SED),
	0, 0,
	पूर्ण,
	अणु "SDMA_IB_CMD_BUF_SED", SOC15_REG_ENTRY(SDMA0, 0, regSDMA0_EDC_COUNTER2),
	SOC15_REG_FIELD(SDMA0_EDC_COUNTER2, SDMA_IB_CMD_BUF_SED),
	0, 0,
	पूर्ण,
	अणु "SDMA_UTCL1_RD_FIFO_SED", SOC15_REG_ENTRY(SDMA0, 0, regSDMA0_EDC_COUNTER2),
	SOC15_REG_FIELD(SDMA0_EDC_COUNTER2, SDMA_UTCL1_RD_FIFO_SED),
	0, 0,
	पूर्ण,
	अणु "SDMA_UTCL1_RDBST_FIFO_SED", SOC15_REG_ENTRY(SDMA0, 0, regSDMA0_EDC_COUNTER2),
	SOC15_REG_FIELD(SDMA0_EDC_COUNTER2, SDMA_UTCL1_RDBST_FIFO_SED),
	0, 0,
	पूर्ण,
	अणु "SDMA_DATA_LUT_FIFO_SED", SOC15_REG_ENTRY(SDMA0, 0, regSDMA0_EDC_COUNTER2),
	SOC15_REG_FIELD(SDMA0_EDC_COUNTER2, SDMA_DATA_LUT_FIFO_SED),
	0, 0,
	पूर्ण,
	अणु "SDMA_SPLIT_DATA_BUF_SED", SOC15_REG_ENTRY(SDMA0, 0, regSDMA0_EDC_COUNTER2),
	SOC15_REG_FIELD(SDMA0_EDC_COUNTER2, SDMA_SPLIT_DATA_BUF_SED),
	0, 0,
	पूर्ण,
	अणु "SDMA_MC_WR_ADDR_FIFO_SED", SOC15_REG_ENTRY(SDMA0, 0, regSDMA0_EDC_COUNTER2),
	SOC15_REG_FIELD(SDMA0_EDC_COUNTER2, SDMA_MC_WR_ADDR_FIFO_SED),
	0, 0,
	पूर्ण,
	अणु "SDMA_MC_RDRET_BUF_SED", SOC15_REG_ENTRY(SDMA0, 0, regSDMA0_EDC_COUNTER2),
	SOC15_REG_FIELD(SDMA0_EDC_COUNTER2, SDMA_MC_WR_ADDR_FIFO_SED),
	0, 0,
	पूर्ण,
पूर्ण;

अटल व्योम sdma_v4_4_get_ras_error_count(काष्ठा amdgpu_device *adev,
					  uपूर्णांक32_t reg_offset,
					  uपूर्णांक32_t value,
					  uपूर्णांक32_t instance,
					  uपूर्णांक32_t *sec_count)
अणु
	uपूर्णांक32_t i;
	uपूर्णांक32_t sec_cnt;

	/* द्विगुन bits error (multiple bits) error detection is not supported */
	क्रम (i = 0; i < ARRAY_SIZE(sdma_v4_4_ras_fields); i++) अणु
		अगर (sdma_v4_4_ras_fields[i].reg_offset != reg_offset)
			जारी;

		/* the SDMA_EDC_COUNTER रेजिस्टर in each sdma instance
		 * shares the same sed shअगरt_mask
		 * */
		sec_cnt = (value &
			sdma_v4_4_ras_fields[i].sec_count_mask) >>
			sdma_v4_4_ras_fields[i].sec_count_shअगरt;
		अगर (sec_cnt) अणु
			dev_info(adev->dev, "Detected %s in SDMA%d, SED %d\n",
				 sdma_v4_4_ras_fields[i].name,
				 instance, sec_cnt);
			*sec_count += sec_cnt;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक sdma_v4_4_query_ras_error_count(काष्ठा amdgpu_device *adev,
					   uपूर्णांक32_t instance,
					   व्योम *ras_error_status)
अणु
	काष्ठा ras_err_data *err_data = (काष्ठा ras_err_data *)ras_error_status;
	uपूर्णांक32_t sec_count = 0;
	uपूर्णांक32_t reg_value = 0;
	uपूर्णांक32_t reg_offset = 0;

	reg_offset = sdma_v4_4_get_reg_offset(adev, instance, regSDMA0_EDC_COUNTER);
	reg_value = RREG32(reg_offset);
	/* द्विगुन bit error is not supported */
	अगर (reg_value)
		sdma_v4_4_get_ras_error_count(adev, regSDMA0_EDC_COUNTER, reg_value,
					      instance, &sec_count);

	reg_offset = sdma_v4_4_get_reg_offset(adev, instance, regSDMA0_EDC_COUNTER2);
	reg_value = RREG32(reg_offset);
	/* द्विगुन bit error is not supported */
	अगर (reg_value)
		sdma_v4_4_get_ras_error_count(adev, regSDMA0_EDC_COUNTER2, reg_value,
					      instance, &sec_count);

	/*
	 * err_data->ue_count should be initialized to 0
	 * beक्रमe calling पूर्णांकo this function
	 *
	 * SDMA RAS supports single bit uncorrectable error detection.
	 * So, increment uncorrectable error count.
	 */
	err_data->ue_count += sec_count;

	/*
	 * SDMA RAS करोes not support correctable errors.
	 * Set ce count to 0.
	 */
	err_data->ce_count = 0;

	वापस 0;
पूर्ण;

अटल व्योम sdma_v4_4_reset_ras_error_count(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक i;
	uपूर्णांक32_t reg_offset;

	/* ग_लिखो 0 to EDC_COUNTER reg to clear sdma edc counters */
	अगर (amdgpu_ras_is_supported(adev, AMDGPU_RAS_BLOCK__SDMA)) अणु
		क्रम (i = 0; i < adev->sdma.num_instances; i++) अणु
			reg_offset = sdma_v4_4_get_reg_offset(adev, i, regSDMA0_EDC_COUNTER);
			WREG32(reg_offset, 0);
			reg_offset = sdma_v4_4_get_reg_offset(adev, i, regSDMA0_EDC_COUNTER2);
			WREG32(reg_offset, 0);
		पूर्ण
	पूर्ण
पूर्ण

स्थिर काष्ठा amdgpu_sdma_ras_funcs sdma_v4_4_ras_funcs = अणु
	.ras_late_init = amdgpu_sdma_ras_late_init,
	.ras_fini = amdgpu_sdma_ras_fini,
	.query_ras_error_count = sdma_v4_4_query_ras_error_count,
	.reset_ras_error_count = sdma_v4_4_reset_ras_error_count,
पूर्ण;
