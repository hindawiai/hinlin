<शैली गुरु>
/*
 * Copyright (C) 2019  Advanced Micro Devices, Inc.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN
 * AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
#अगर_अघोषित __AMDGPU_UMC_H__
#घोषणा __AMDGPU_UMC_H__

/*
 * (addr / 256) * 8192, the higher 26 bits in ErrorAddr
 * is the index of 8KB block
 */
#घोषणा ADDR_OF_8KB_BLOCK(addr)			(((addr) & ~0xffULL) << 5)
/* channel index is the index of 256B block */
#घोषणा ADDR_OF_256B_BLOCK(channel_index)	((channel_index) << 8)
/* offset in 256B block */
#घोषणा OFFSET_IN_256B_BLOCK(addr)		((addr) & 0xffULL)

#घोषणा LOOP_UMC_INST(umc_inst) क्रम ((umc_inst) = 0; (umc_inst) < adev->umc.umc_inst_num; (umc_inst)++)
#घोषणा LOOP_UMC_CH_INST(ch_inst) क्रम ((ch_inst) = 0; (ch_inst) < adev->umc.channel_inst_num; (ch_inst)++)
#घोषणा LOOP_UMC_INST_AND_CH(umc_inst, ch_inst) LOOP_UMC_INST((umc_inst)) LOOP_UMC_CH_INST((ch_inst))

काष्ठा amdgpu_umc_ras_funcs अणु
	व्योम (*err_cnt_init)(काष्ठा amdgpu_device *adev);
	पूर्णांक (*ras_late_init)(काष्ठा amdgpu_device *adev);
	व्योम (*ras_fini)(काष्ठा amdgpu_device *adev);
	व्योम (*query_ras_error_count)(काष्ठा amdgpu_device *adev,
				      व्योम *ras_error_status);
	व्योम (*query_ras_error_address)(काष्ठा amdgpu_device *adev,
					व्योम *ras_error_status);
पूर्ण;

काष्ठा amdgpu_umc_funcs अणु
	व्योम (*init_रेजिस्टरs)(काष्ठा amdgpu_device *adev);
पूर्ण;

काष्ठा amdgpu_umc अणु
	/* max error count in one ras query call */
	uपूर्णांक32_t max_ras_err_cnt_per_query;
	/* number of umc channel instance with memory map रेजिस्टर access */
	uपूर्णांक32_t channel_inst_num;
	/* number of umc instance with memory map रेजिस्टर access */
	uपूर्णांक32_t umc_inst_num;
	/* UMC regiser per channel offset */
	uपूर्णांक32_t channel_offs;
	/* channel index table of पूर्णांकerleaved memory */
	स्थिर uपूर्णांक32_t *channel_idx_tbl;
	काष्ठा ras_common_अगर *ras_अगर;

	स्थिर काष्ठा amdgpu_umc_funcs *funcs;
	स्थिर काष्ठा amdgpu_umc_ras_funcs *ras_funcs;
पूर्ण;

पूर्णांक amdgpu_umc_ras_late_init(काष्ठा amdgpu_device *adev);
व्योम amdgpu_umc_ras_fini(काष्ठा amdgpu_device *adev);
पूर्णांक amdgpu_umc_process_ras_data_cb(काष्ठा amdgpu_device *adev,
		व्योम *ras_error_status,
		काष्ठा amdgpu_iv_entry *entry);
पूर्णांक amdgpu_umc_process_ecc_irq(काष्ठा amdgpu_device *adev,
		काष्ठा amdgpu_irq_src *source,
		काष्ठा amdgpu_iv_entry *entry);
#पूर्ण_अगर
