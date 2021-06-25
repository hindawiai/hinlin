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

#समावेश "amdgpu.h"
#समावेश "amdgpu_sdma.h"
#समावेश "amdgpu_ras.h"

#घोषणा AMDGPU_CSA_SDMA_SIZE 64
/* SDMA CSA reside in the 3rd page of CSA */
#घोषणा AMDGPU_CSA_SDMA_OFFSET (4096 * 2)

/*
 * GPU SDMA IP block helpers function.
 */

काष्ठा amdgpu_sdma_instance *amdgpu_sdma_get_instance_from_ring(काष्ठा amdgpu_ring *ring)
अणु
	काष्ठा amdgpu_device *adev = ring->adev;
	पूर्णांक i;

	क्रम (i = 0; i < adev->sdma.num_instances; i++)
		अगर (ring == &adev->sdma.instance[i].ring ||
		    ring == &adev->sdma.instance[i].page)
			वापस &adev->sdma.instance[i];

	वापस शून्य;
पूर्ण

पूर्णांक amdgpu_sdma_get_index_from_ring(काष्ठा amdgpu_ring *ring, uपूर्णांक32_t *index)
अणु
	काष्ठा amdgpu_device *adev = ring->adev;
	पूर्णांक i;

	क्रम (i = 0; i < adev->sdma.num_instances; i++) अणु
		अगर (ring == &adev->sdma.instance[i].ring ||
			ring == &adev->sdma.instance[i].page) अणु
			*index = i;
			वापस 0;
		पूर्ण
	पूर्ण

	वापस -EINVAL;
पूर्ण

uपूर्णांक64_t amdgpu_sdma_get_csa_mc_addr(काष्ठा amdgpu_ring *ring,
				     अचिन्हित vmid)
अणु
	काष्ठा amdgpu_device *adev = ring->adev;
	uपूर्णांक64_t csa_mc_addr;
	uपूर्णांक32_t index = 0;
	पूर्णांक r;

	/* करोn't enable OS preemption on SDMA under SRIOV */
	अगर (amdgpu_sriov_vf(adev) || vmid == 0 || !amdgpu_mcbp)
		वापस 0;

	r = amdgpu_sdma_get_index_from_ring(ring, &index);

	अगर (r || index > 31)
		csa_mc_addr = 0;
	अन्यथा
		csa_mc_addr = amdgpu_csa_vaddr(adev) +
			AMDGPU_CSA_SDMA_OFFSET +
			index * AMDGPU_CSA_SDMA_SIZE;

	वापस csa_mc_addr;
पूर्ण

पूर्णांक amdgpu_sdma_ras_late_init(काष्ठा amdgpu_device *adev,
			      व्योम *ras_ih_info)
अणु
	पूर्णांक r, i;
	काष्ठा ras_ih_अगर *ih_info = (काष्ठा ras_ih_अगर *)ras_ih_info;
	काष्ठा ras_fs_अगर fs_info = अणु
		.sysfs_name = "sdma_err_count",
	पूर्ण;

	अगर (!ih_info)
		वापस -EINVAL;

	अगर (!adev->sdma.ras_अगर) अणु
		adev->sdma.ras_अगर = kदो_स्मृति(माप(काष्ठा ras_common_अगर), GFP_KERNEL);
		अगर (!adev->sdma.ras_अगर)
			वापस -ENOMEM;
		adev->sdma.ras_अगर->block = AMDGPU_RAS_BLOCK__SDMA;
		adev->sdma.ras_अगर->type = AMDGPU_RAS_ERROR__MULTI_UNCORRECTABLE;
		adev->sdma.ras_अगर->sub_block_index = 0;
		म_नकल(adev->sdma.ras_अगर->name, "sdma");
	पूर्ण
	fs_info.head = ih_info->head = *adev->sdma.ras_अगर;

	r = amdgpu_ras_late_init(adev, adev->sdma.ras_अगर,
				 &fs_info, ih_info);
	अगर (r)
		जाओ मुक्त;

	अगर (amdgpu_ras_is_supported(adev, adev->sdma.ras_अगर->block)) अणु
		क्रम (i = 0; i < adev->sdma.num_instances; i++) अणु
			r = amdgpu_irq_get(adev, &adev->sdma.ecc_irq,
				AMDGPU_SDMA_IRQ_INSTANCE0 + i);
			अगर (r)
				जाओ late_fini;
		पूर्ण
	पूर्ण अन्यथा अणु
		r = 0;
		जाओ मुक्त;
	पूर्ण

	वापस 0;

late_fini:
	amdgpu_ras_late_fini(adev, adev->sdma.ras_अगर, ih_info);
मुक्त:
	kमुक्त(adev->sdma.ras_अगर);
	adev->sdma.ras_अगर = शून्य;
	वापस r;
पूर्ण

व्योम amdgpu_sdma_ras_fini(काष्ठा amdgpu_device *adev)
अणु
	अगर (amdgpu_ras_is_supported(adev, AMDGPU_RAS_BLOCK__SDMA) &&
			adev->sdma.ras_अगर) अणु
		काष्ठा ras_common_अगर *ras_अगर = adev->sdma.ras_अगर;
		काष्ठा ras_ih_अगर ih_info = अणु
			.head = *ras_अगर,
			/* the cb member will not be used by
			 * amdgpu_ras_पूर्णांकerrupt_हटाओ_handler, init it only
			 * to cheat the check in ras_late_fini
			 */
			.cb = amdgpu_sdma_process_ras_data_cb,
		पूर्ण;

		amdgpu_ras_late_fini(adev, ras_अगर, &ih_info);
		kमुक्त(ras_अगर);
	पूर्ण
पूर्ण

पूर्णांक amdgpu_sdma_process_ras_data_cb(काष्ठा amdgpu_device *adev,
		व्योम *err_data,
		काष्ठा amdgpu_iv_entry *entry)
अणु
	kgd2kfd_set_sram_ecc_flag(adev->kfd.dev);
	amdgpu_ras_reset_gpu(adev);

	वापस AMDGPU_RAS_SUCCESS;
पूर्ण

पूर्णांक amdgpu_sdma_process_ecc_irq(काष्ठा amdgpu_device *adev,
				      काष्ठा amdgpu_irq_src *source,
				      काष्ठा amdgpu_iv_entry *entry)
अणु
	काष्ठा ras_common_अगर *ras_अगर = adev->sdma.ras_अगर;
	काष्ठा ras_dispatch_अगर ih_data = अणु
		.entry = entry,
	पूर्ण;

	अगर (!ras_अगर)
		वापस 0;

	ih_data.head = *ras_अगर;

	amdgpu_ras_पूर्णांकerrupt_dispatch(adev, &ih_data);
	वापस 0;
पूर्ण
