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

#अगर_अघोषित __AMDGPU_VCE_H__
#घोषणा __AMDGPU_VCE_H__

#घोषणा AMDGPU_MAX_VCE_HANDLES	16
#घोषणा AMDGPU_VCE_FIRMWARE_OFFSET 256

#घोषणा AMDGPU_VCE_HARVEST_VCE0 (1 << 0)
#घोषणा AMDGPU_VCE_HARVEST_VCE1 (1 << 1)

#घोषणा AMDGPU_VCE_FW_53_45	((53 << 24) | (45 << 16))

काष्ठा amdgpu_vce अणु
	काष्ठा amdgpu_bo	*vcpu_bo;
	uपूर्णांक64_t		gpu_addr;
	व्योम			*cpu_addr;
	व्योम			*saved_bo;
	अचिन्हित		fw_version;
	अचिन्हित		fb_version;
	atomic_t		handles[AMDGPU_MAX_VCE_HANDLES];
	काष्ठा drm_file		*filp[AMDGPU_MAX_VCE_HANDLES];
	uपूर्णांक32_t		img_size[AMDGPU_MAX_VCE_HANDLES];
	काष्ठा delayed_work	idle_work;
	काष्ठा mutex		idle_mutex;
	स्थिर काष्ठा firmware	*fw;	/* VCE firmware */
	काष्ठा amdgpu_ring	ring[AMDGPU_MAX_VCE_RINGS];
	काष्ठा amdgpu_irq_src	irq;
	अचिन्हित		harvest_config;
	काष्ठा drm_sched_entity	entity;
	uपूर्णांक32_t                srbm_soft_reset;
	अचिन्हित		num_rings;
पूर्ण;

पूर्णांक amdgpu_vce_sw_init(काष्ठा amdgpu_device *adev, अचिन्हित दीर्घ size);
पूर्णांक amdgpu_vce_sw_fini(काष्ठा amdgpu_device *adev);
पूर्णांक amdgpu_vce_entity_init(काष्ठा amdgpu_device *adev);
पूर्णांक amdgpu_vce_suspend(काष्ठा amdgpu_device *adev);
पूर्णांक amdgpu_vce_resume(काष्ठा amdgpu_device *adev);
व्योम amdgpu_vce_मुक्त_handles(काष्ठा amdgpu_device *adev, काष्ठा drm_file *filp);
पूर्णांक amdgpu_vce_ring_parse_cs(काष्ठा amdgpu_cs_parser *p, uपूर्णांक32_t ib_idx);
पूर्णांक amdgpu_vce_ring_parse_cs_vm(काष्ठा amdgpu_cs_parser *p, uपूर्णांक32_t ib_idx);
व्योम amdgpu_vce_ring_emit_ib(काष्ठा amdgpu_ring *ring, काष्ठा amdgpu_job *job,
				काष्ठा amdgpu_ib *ib, uपूर्णांक32_t flags);
व्योम amdgpu_vce_ring_emit_fence(काष्ठा amdgpu_ring *ring, u64 addr, u64 seq,
				अचिन्हित flags);
पूर्णांक amdgpu_vce_ring_test_ring(काष्ठा amdgpu_ring *ring);
पूर्णांक amdgpu_vce_ring_test_ib(काष्ठा amdgpu_ring *ring, दीर्घ समयout);
व्योम amdgpu_vce_ring_begin_use(काष्ठा amdgpu_ring *ring);
व्योम amdgpu_vce_ring_end_use(काष्ठा amdgpu_ring *ring);
अचिन्हित amdgpu_vce_ring_get_emit_ib_size(काष्ठा amdgpu_ring *ring);
अचिन्हित amdgpu_vce_ring_get_dma_frame_size(काष्ठा amdgpu_ring *ring);

#पूर्ण_अगर
