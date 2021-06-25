<शैली गुरु>
/*
 * Copyright 2015 Advanced Micro Devices, Inc.
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
#अगर_अघोषित _SMU8_SMUMGR_H_
#घोषणा _SMU8_SMUMGR_H_


#घोषणा MAX_NUM_FIRMWARE                        8
#घोषणा MAX_NUM_SCRATCH                         11
#घोषणा SMU8_SCRATCH_SIZE_NONGFX_CLOCKGATING      1024
#घोषणा SMU8_SCRATCH_SIZE_NONGFX_GOLDENSETTING    2048
#घोषणा SMU8_SCRATCH_SIZE_SDMA_METADATA           1024
#घोषणा SMU8_SCRATCH_SIZE_IH                      ((2*256+1)*4)

#घोषणा SMU_EnabledFeatureScoreboard_SclkDpmOn    0x00200000

क्रमागत smu8_scratch_entry अणु
	SMU8_SCRATCH_ENTRY_UCODE_ID_SDMA0 = 0,
	SMU8_SCRATCH_ENTRY_UCODE_ID_SDMA1,
	SMU8_SCRATCH_ENTRY_UCODE_ID_CP_CE,
	SMU8_SCRATCH_ENTRY_UCODE_ID_CP_PFP,
	SMU8_SCRATCH_ENTRY_UCODE_ID_CP_ME,
	SMU8_SCRATCH_ENTRY_UCODE_ID_CP_MEC_JT1,
	SMU8_SCRATCH_ENTRY_UCODE_ID_CP_MEC_JT2,
	SMU8_SCRATCH_ENTRY_UCODE_ID_GMCON_RENG,
	SMU8_SCRATCH_ENTRY_UCODE_ID_RLC_G,
	SMU8_SCRATCH_ENTRY_UCODE_ID_RLC_SCRATCH,
	SMU8_SCRATCH_ENTRY_UCODE_ID_RLC_SRM_ARAM,
	SMU8_SCRATCH_ENTRY_UCODE_ID_RLC_SRM_DRAM,
	SMU8_SCRATCH_ENTRY_UCODE_ID_DMCU_ERAM,
	SMU8_SCRATCH_ENTRY_UCODE_ID_DMCU_IRAM,
	SMU8_SCRATCH_ENTRY_UCODE_ID_POWER_PROFILING,
	SMU8_SCRATCH_ENTRY_DATA_ID_SDMA_HALT,
	SMU8_SCRATCH_ENTRY_DATA_ID_SYS_CLOCKGATING,
	SMU8_SCRATCH_ENTRY_DATA_ID_SDMA_RING_REGS,
	SMU8_SCRATCH_ENTRY_DATA_ID_NONGFX_REINIT,
	SMU8_SCRATCH_ENTRY_DATA_ID_SDMA_START,
	SMU8_SCRATCH_ENTRY_DATA_ID_IH_REGISTERS,
	SMU8_SCRATCH_ENTRY_SMU8_FUSION_CLKTABLE
पूर्ण;

काष्ठा smu8_buffer_entry अणु
	uपूर्णांक32_t data_size;
	uपूर्णांक64_t mc_addr;
	व्योम *kaddr;
	क्रमागत smu8_scratch_entry firmware_ID;
	काष्ठा amdgpu_bo *handle; /* as bo handle used when release bo */
पूर्ण;

काष्ठा smu8_रेजिस्टर_index_data_pair अणु
	uपूर्णांक32_t offset;
	uपूर्णांक32_t value;
पूर्ण;

काष्ठा smu8_ih_meta_data अणु
	uपूर्णांक32_t command;
	काष्ठा smu8_रेजिस्टर_index_data_pair रेजिस्टर_index_value_pair[1];
पूर्ण;

काष्ठा smu8_smumgr अणु
	uपूर्णांक8_t driver_buffer_length;
	uपूर्णांक8_t scratch_buffer_length;
	uपूर्णांक16_t toc_entry_used_count;
	uपूर्णांक16_t toc_entry_initialize_index;
	uपूर्णांक16_t toc_entry_घातer_profiling_index;
	uपूर्णांक16_t toc_entry_aram;
	uपूर्णांक16_t toc_entry_ih_रेजिस्टर_restore_task_index;
	uपूर्णांक16_t toc_entry_घड़ी_प्रकारable;
	uपूर्णांक16_t ih_रेजिस्टर_restore_task_size;
	uपूर्णांक16_t smu_buffer_used_bytes;

	काष्ठा smu8_buffer_entry toc_buffer;
	काष्ठा smu8_buffer_entry smu_buffer;
	काष्ठा smu8_buffer_entry firmware_buffer;
	काष्ठा smu8_buffer_entry driver_buffer[MAX_NUM_FIRMWARE];
	काष्ठा smu8_buffer_entry meta_data_buffer[MAX_NUM_FIRMWARE];
	काष्ठा smu8_buffer_entry scratch_buffer[MAX_NUM_SCRATCH];
पूर्ण;

#पूर्ण_अगर
