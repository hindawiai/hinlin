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

#अगर_अघोषित __AMDGPU_UVD_H__
#घोषणा __AMDGPU_UVD_H__

#घोषणा AMDGPU_DEFAULT_UVD_HANDLES	10
#घोषणा AMDGPU_MAX_UVD_HANDLES		40
#घोषणा AMDGPU_UVD_STACK_SIZE		(200*1024)
#घोषणा AMDGPU_UVD_HEAP_SIZE		(256*1024)
#घोषणा AMDGPU_UVD_SESSION_SIZE		(50*1024)
#घोषणा AMDGPU_UVD_FIRMWARE_OFFSET	256

#घोषणा AMDGPU_MAX_UVD_INSTANCES			2

#घोषणा AMDGPU_UVD_FIRMWARE_SIZE(adev)    \
	(AMDGPU_GPU_PAGE_ALIGN(le32_to_cpu(((स्थिर काष्ठा common_firmware_header *)(adev)->uvd.fw->data)->ucode_size_bytes) + \
			       8) - AMDGPU_UVD_FIRMWARE_OFFSET)

काष्ठा amdgpu_uvd_inst अणु
	काष्ठा amdgpu_bo	*vcpu_bo;
	व्योम			*cpu_addr;
	uपूर्णांक64_t		gpu_addr;
	व्योम			*saved_bo;
	काष्ठा amdgpu_ring	ring;
	काष्ठा amdgpu_ring	ring_enc[AMDGPU_MAX_UVD_ENC_RINGS];
	काष्ठा amdgpu_irq_src	irq;
	uपूर्णांक32_t                srbm_soft_reset;
पूर्ण;

#घोषणा AMDGPU_UVD_HARVEST_UVD0 (1 << 0)
#घोषणा AMDGPU_UVD_HARVEST_UVD1 (1 << 1)

काष्ठा amdgpu_uvd अणु
	स्थिर काष्ठा firmware	*fw;	/* UVD firmware */
	अचिन्हित		fw_version;
	अचिन्हित		max_handles;
	अचिन्हित		num_enc_rings;
	uपूर्णांक8_t			num_uvd_inst;
	bool			address_64_bit;
	bool			use_ctx_buf;
	काष्ठा amdgpu_uvd_inst	inst[AMDGPU_MAX_UVD_INSTANCES];
	काष्ठा drm_file		*filp[AMDGPU_MAX_UVD_HANDLES];
	atomic_t		handles[AMDGPU_MAX_UVD_HANDLES];
	काष्ठा drm_sched_entity entity;
	काष्ठा delayed_work	idle_work;
	अचिन्हित		harvest_config;
	/* store image width to adjust nb memory state */
	अचिन्हित		decode_image_width;
	uपूर्णांक32_t                keyselect;
पूर्ण;

पूर्णांक amdgpu_uvd_sw_init(काष्ठा amdgpu_device *adev);
पूर्णांक amdgpu_uvd_sw_fini(काष्ठा amdgpu_device *adev);
पूर्णांक amdgpu_uvd_entity_init(काष्ठा amdgpu_device *adev);
पूर्णांक amdgpu_uvd_suspend(काष्ठा amdgpu_device *adev);
पूर्णांक amdgpu_uvd_resume(काष्ठा amdgpu_device *adev);
पूर्णांक amdgpu_uvd_get_create_msg(काष्ठा amdgpu_ring *ring, uपूर्णांक32_t handle,
			      काष्ठा dma_fence **fence);
पूर्णांक amdgpu_uvd_get_destroy_msg(काष्ठा amdgpu_ring *ring, uपूर्णांक32_t handle,
			       bool direct, काष्ठा dma_fence **fence);
व्योम amdgpu_uvd_मुक्त_handles(काष्ठा amdgpu_device *adev,
			     काष्ठा drm_file *filp);
पूर्णांक amdgpu_uvd_ring_parse_cs(काष्ठा amdgpu_cs_parser *parser, uपूर्णांक32_t ib_idx);
व्योम amdgpu_uvd_ring_begin_use(काष्ठा amdgpu_ring *ring);
व्योम amdgpu_uvd_ring_end_use(काष्ठा amdgpu_ring *ring);
पूर्णांक amdgpu_uvd_ring_test_ib(काष्ठा amdgpu_ring *ring, दीर्घ समयout);
uपूर्णांक32_t amdgpu_uvd_used_handles(काष्ठा amdgpu_device *adev);

#पूर्ण_अगर
