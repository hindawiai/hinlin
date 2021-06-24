<शैली गुरु>
/*
 * Copyright 2019 Advanced Micro Devices, Inc.
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

#अगर_अघोषित __AMDGPU_MES_H__
#घोषणा __AMDGPU_MES_H__

#घोषणा AMDGPU_MES_MAX_COMPUTE_PIPES        8
#घोषणा AMDGPU_MES_MAX_GFX_PIPES            2
#घोषणा AMDGPU_MES_MAX_SDMA_PIPES           2

क्रमागत amdgpu_mes_priority_level अणु
	AMDGPU_MES_PRIORITY_LEVEL_LOW       = 0,
	AMDGPU_MES_PRIORITY_LEVEL_NORMAL    = 1,
	AMDGPU_MES_PRIORITY_LEVEL_MEDIUM    = 2,
	AMDGPU_MES_PRIORITY_LEVEL_HIGH      = 3,
	AMDGPU_MES_PRIORITY_LEVEL_REALTIME  = 4,
	AMDGPU_MES_PRIORITY_NUM_LEVELS
पूर्ण;

काष्ठा amdgpu_mes_funcs;

काष्ठा amdgpu_mes अणु
	काष्ठा amdgpu_device            *adev;

	uपूर्णांक32_t                        total_max_queue;
	uपूर्णांक32_t                        करोorbell_id_offset;
	uपूर्णांक32_t                        max_करोorbell_slices;

	uपूर्णांक64_t                        शेष_process_quantum;
	uपूर्णांक64_t                        शेष_gang_quantum;

	काष्ठा amdgpu_ring              ring;

	स्थिर काष्ठा firmware           *fw;

	/* mes ucode */
	काष्ठा amdgpu_bo		*ucode_fw_obj;
	uपूर्णांक64_t			ucode_fw_gpu_addr;
	uपूर्णांक32_t			*ucode_fw_ptr;
	uपूर्णांक32_t                        ucode_fw_version;
	uपूर्णांक64_t                        uc_start_addr;

	/* mes ucode data */
	काष्ठा amdgpu_bo		*data_fw_obj;
	uपूर्णांक64_t			data_fw_gpu_addr;
	uपूर्णांक32_t			*data_fw_ptr;
	uपूर्णांक32_t                        data_fw_version;
	uपूर्णांक64_t                        data_start_addr;

	/* eop gpu obj */
	काष्ठा amdgpu_bo		*eop_gpu_obj;
	uपूर्णांक64_t                        eop_gpu_addr;

	व्योम                            *mqd_backup;

	uपूर्णांक32_t                        vmid_mask_gfxhub;
	uपूर्णांक32_t                        vmid_mask_mmhub;
	uपूर्णांक32_t                        compute_hqd_mask[AMDGPU_MES_MAX_COMPUTE_PIPES];
	uपूर्णांक32_t                        gfx_hqd_mask[AMDGPU_MES_MAX_GFX_PIPES];
	uपूर्णांक32_t                        sdma_hqd_mask[AMDGPU_MES_MAX_SDMA_PIPES];
	uपूर्णांक32_t                        agreegated_करोorbells[AMDGPU_MES_PRIORITY_NUM_LEVELS];
	uपूर्णांक32_t                        sch_ctx_offs;
	uपूर्णांक64_t			sch_ctx_gpu_addr;
	uपूर्णांक64_t			*sch_ctx_ptr;
	uपूर्णांक32_t			query_status_fence_offs;
	uपूर्णांक64_t			query_status_fence_gpu_addr;
	uपूर्णांक64_t			*query_status_fence_ptr;

	/* ip specअगरic functions */
	स्थिर काष्ठा amdgpu_mes_funcs   *funcs;
पूर्ण;

काष्ठा mes_add_queue_input अणु
	uपूर्णांक32_t	process_id;
	uपूर्णांक64_t	page_table_base_addr;
	uपूर्णांक64_t	process_बहु_शुरू;
	uपूर्णांक64_t	process_बहु_पूर्ण;
	uपूर्णांक64_t	process_quantum;
	uपूर्णांक64_t	process_context_addr;
	uपूर्णांक64_t	gang_quantum;
	uपूर्णांक64_t	gang_context_addr;
	uपूर्णांक32_t	inprocess_gang_priority;
	uपूर्णांक32_t	gang_global_priority_level;
	uपूर्णांक32_t	करोorbell_offset;
	uपूर्णांक64_t	mqd_addr;
	uपूर्णांक64_t	wptr_addr;
	uपूर्णांक32_t	queue_type;
	uपूर्णांक32_t	paging;
पूर्ण;

काष्ठा mes_हटाओ_queue_input अणु
	uपूर्णांक32_t	करोorbell_offset;
	uपूर्णांक64_t	gang_context_addr;
पूर्ण;

काष्ठा mes_suspend_gang_input अणु
	bool		suspend_all_gangs;
	uपूर्णांक64_t	gang_context_addr;
	uपूर्णांक64_t	suspend_fence_addr;
	uपूर्णांक32_t	suspend_fence_value;
पूर्ण;

काष्ठा mes_resume_gang_input अणु
	bool		resume_all_gangs;
	uपूर्णांक64_t	gang_context_addr;
पूर्ण;

काष्ठा amdgpu_mes_funcs अणु
	पूर्णांक (*add_hw_queue)(काष्ठा amdgpu_mes *mes,
			    काष्ठा mes_add_queue_input *input);

	पूर्णांक (*हटाओ_hw_queue)(काष्ठा amdgpu_mes *mes,
			       काष्ठा mes_हटाओ_queue_input *input);

	पूर्णांक (*suspend_gang)(काष्ठा amdgpu_mes *mes,
			    काष्ठा mes_suspend_gang_input *input);

	पूर्णांक (*resume_gang)(काष्ठा amdgpu_mes *mes,
			   काष्ठा mes_resume_gang_input *input);
पूर्ण;

#पूर्ण_अगर /* __AMDGPU_MES_H__ */
