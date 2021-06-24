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

#समावेश "kfd_mqd_manager.h"
#समावेश "amdgpu_amdkfd.h"
#समावेश "kfd_device_queue_manager.h"

/* Mapping queue priority to pipe priority, indexed by queue priority */
पूर्णांक pipe_priority_map[] = अणु
	KFD_PIPE_PRIORITY_CS_LOW,
	KFD_PIPE_PRIORITY_CS_LOW,
	KFD_PIPE_PRIORITY_CS_LOW,
	KFD_PIPE_PRIORITY_CS_LOW,
	KFD_PIPE_PRIORITY_CS_LOW,
	KFD_PIPE_PRIORITY_CS_LOW,
	KFD_PIPE_PRIORITY_CS_LOW,
	KFD_PIPE_PRIORITY_CS_MEDIUM,
	KFD_PIPE_PRIORITY_CS_MEDIUM,
	KFD_PIPE_PRIORITY_CS_MEDIUM,
	KFD_PIPE_PRIORITY_CS_MEDIUM,
	KFD_PIPE_PRIORITY_CS_HIGH,
	KFD_PIPE_PRIORITY_CS_HIGH,
	KFD_PIPE_PRIORITY_CS_HIGH,
	KFD_PIPE_PRIORITY_CS_HIGH,
	KFD_PIPE_PRIORITY_CS_HIGH
पूर्ण;

काष्ठा kfd_mem_obj *allocate_hiq_mqd(काष्ठा kfd_dev *dev, काष्ठा queue_properties *q)
अणु
	काष्ठा kfd_mem_obj *mqd_mem_obj = शून्य;

	mqd_mem_obj = kzalloc(माप(काष्ठा kfd_mem_obj), GFP_KERNEL);
	अगर (!mqd_mem_obj)
		वापस शून्य;

	mqd_mem_obj->gtt_mem = dev->dqm->hiq_sdma_mqd.gtt_mem;
	mqd_mem_obj->gpu_addr = dev->dqm->hiq_sdma_mqd.gpu_addr;
	mqd_mem_obj->cpu_ptr = dev->dqm->hiq_sdma_mqd.cpu_ptr;

	वापस mqd_mem_obj;
पूर्ण

काष्ठा kfd_mem_obj *allocate_sdma_mqd(काष्ठा kfd_dev *dev,
					काष्ठा queue_properties *q)
अणु
	काष्ठा kfd_mem_obj *mqd_mem_obj = शून्य;
	uपूर्णांक64_t offset;

	mqd_mem_obj = kzalloc(माप(काष्ठा kfd_mem_obj), GFP_KERNEL);
	अगर (!mqd_mem_obj)
		वापस शून्य;

	offset = (q->sdma_engine_id *
		dev->device_info->num_sdma_queues_per_engine +
		q->sdma_queue_id) *
		dev->dqm->mqd_mgrs[KFD_MQD_TYPE_SDMA]->mqd_size;

	offset += dev->dqm->mqd_mgrs[KFD_MQD_TYPE_HIQ]->mqd_size;

	mqd_mem_obj->gtt_mem = (व्योम *)((uपूर्णांक64_t)dev->dqm->hiq_sdma_mqd.gtt_mem
				+ offset);
	mqd_mem_obj->gpu_addr = dev->dqm->hiq_sdma_mqd.gpu_addr + offset;
	mqd_mem_obj->cpu_ptr = (uपूर्णांक32_t *)((uपूर्णांक64_t)
				dev->dqm->hiq_sdma_mqd.cpu_ptr + offset);

	वापस mqd_mem_obj;
पूर्ण

व्योम मुक्त_mqd_hiq_sdma(काष्ठा mqd_manager *mm, व्योम *mqd,
			काष्ठा kfd_mem_obj *mqd_mem_obj)
अणु
	WARN_ON(!mqd_mem_obj->gtt_mem);
	kमुक्त(mqd_mem_obj);
पूर्ण

व्योम mqd_symmetrically_map_cu_mask(काष्ठा mqd_manager *mm,
		स्थिर uपूर्णांक32_t *cu_mask, uपूर्णांक32_t cu_mask_count,
		uपूर्णांक32_t *se_mask)
अणु
	काष्ठा kfd_cu_info cu_info;
	uपूर्णांक32_t cu_per_se[KFD_MAX_NUM_SE] = अणु0पूर्ण;
	पूर्णांक i, se, sh, cu = 0;

	amdgpu_amdkfd_get_cu_info(mm->dev->kgd, &cu_info);

	अगर (cu_mask_count > cu_info.cu_active_number)
		cu_mask_count = cu_info.cu_active_number;

	क्रम (se = 0; se < cu_info.num_shader_engines; se++)
		क्रम (sh = 0; sh < cu_info.num_shader_arrays_per_engine; sh++)
			cu_per_se[se] += hweight32(cu_info.cu_biपंचांगap[se % 4][sh + (se / 4)]);

	/* Symmetrically map cu_mask to all SEs:
	 * cu_mask[0] bit0 -> se_mask[0] bit0;
	 * cu_mask[0] bit1 -> se_mask[1] bit0;
	 * ... (अगर # SE is 4)
	 * cu_mask[0] bit4 -> se_mask[0] bit1;
	 * ...
	 */
	se = 0;
	क्रम (i = 0; i < cu_mask_count; i++) अणु
		अगर (cu_mask[i / 32] & (1 << (i % 32)))
			se_mask[se] |= 1 << cu;

		करो अणु
			se++;
			अगर (se == cu_info.num_shader_engines) अणु
				se = 0;
				cu++;
			पूर्ण
		पूर्ण जबतक (cu >= cu_per_se[se] && cu < 32);
	पूर्ण
पूर्ण
