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

#अगर_अघोषित __AMDGPU_SDMA_H__
#घोषणा __AMDGPU_SDMA_H__

/* max number of IP instances */
#घोषणा AMDGPU_MAX_SDMA_INSTANCES		8

क्रमागत amdgpu_sdma_irq अणु
	AMDGPU_SDMA_IRQ_INSTANCE0  = 0,
	AMDGPU_SDMA_IRQ_INSTANCE1,
	AMDGPU_SDMA_IRQ_INSTANCE2,
	AMDGPU_SDMA_IRQ_INSTANCE3,
	AMDGPU_SDMA_IRQ_INSTANCE4,
	AMDGPU_SDMA_IRQ_INSTANCE5,
	AMDGPU_SDMA_IRQ_INSTANCE6,
	AMDGPU_SDMA_IRQ_INSTANCE7,
	AMDGPU_SDMA_IRQ_LAST
पूर्ण;

काष्ठा amdgpu_sdma_instance अणु
	/* SDMA firmware */
	स्थिर काष्ठा firmware	*fw;
	uपूर्णांक32_t		fw_version;
	uपूर्णांक32_t		feature_version;

	काष्ठा amdgpu_ring	ring;
	काष्ठा amdgpu_ring	page;
	bool			burst_nop;
पूर्ण;

काष्ठा amdgpu_sdma_ras_funcs अणु
	पूर्णांक (*ras_late_init)(काष्ठा amdgpu_device *adev,
			व्योम *ras_ih_info);
	व्योम (*ras_fini)(काष्ठा amdgpu_device *adev);
	पूर्णांक (*query_ras_error_count)(काष्ठा amdgpu_device *adev,
			uपूर्णांक32_t instance, व्योम *ras_error_status);
	व्योम (*reset_ras_error_count)(काष्ठा amdgpu_device *adev);
पूर्ण;

काष्ठा amdgpu_sdma अणु
	काष्ठा amdgpu_sdma_instance instance[AMDGPU_MAX_SDMA_INSTANCES];
	काष्ठा amdgpu_irq_src	trap_irq;
	काष्ठा amdgpu_irq_src	illegal_inst_irq;
	काष्ठा amdgpu_irq_src	ecc_irq;
	काष्ठा amdgpu_irq_src	vm_hole_irq;
	काष्ठा amdgpu_irq_src	करोorbell_invalid_irq;
	काष्ठा amdgpu_irq_src	pool_समयout_irq;
	काष्ठा amdgpu_irq_src	srbm_ग_लिखो_irq;

	पूर्णांक			num_instances;
	uपूर्णांक32_t                    srbm_soft_reset;
	bool			has_page_queue;
	काष्ठा ras_common_अगर	*ras_अगर;
	स्थिर काष्ठा amdgpu_sdma_ras_funcs	*funcs;
पूर्ण;

/*
 * Provided by hw blocks that can move/clear data.  e.g., gfx or sdma
 * But currently, we use sdma to move data.
 */
काष्ठा amdgpu_buffer_funcs अणु
	/* maximum bytes in a single operation */
	uपूर्णांक32_t	copy_max_bytes;

	/* number of dw to reserve per operation */
	अचिन्हित	copy_num_dw;

	/* used क्रम buffer migration */
	व्योम (*emit_copy_buffer)(काष्ठा amdgpu_ib *ib,
				 /* src addr in bytes */
				 uपूर्णांक64_t src_offset,
				 /* dst addr in bytes */
				 uपूर्णांक64_t dst_offset,
				 /* number of byte to transfer */
				 uपूर्णांक32_t byte_count,
				 bool पंचांगz);

	/* maximum bytes in a single operation */
	uपूर्णांक32_t	fill_max_bytes;

	/* number of dw to reserve per operation */
	अचिन्हित	fill_num_dw;

	/* used क्रम buffer clearing */
	व्योम (*emit_fill_buffer)(काष्ठा amdgpu_ib *ib,
				 /* value to ग_लिखो to memory */
				 uपूर्णांक32_t src_data,
				 /* dst addr in bytes */
				 uपूर्णांक64_t dst_offset,
				 /* number of byte to fill */
				 uपूर्णांक32_t byte_count);
पूर्ण;

#घोषणा amdgpu_emit_copy_buffer(adev, ib, s, d, b, t) (adev)->mman.buffer_funcs->emit_copy_buffer((ib),  (s), (d), (b), (t))
#घोषणा amdgpu_emit_fill_buffer(adev, ib, s, d, b) (adev)->mman.buffer_funcs->emit_fill_buffer((ib), (s), (d), (b))

काष्ठा amdgpu_sdma_instance *
amdgpu_sdma_get_instance_from_ring(काष्ठा amdgpu_ring *ring);
पूर्णांक amdgpu_sdma_get_index_from_ring(काष्ठा amdgpu_ring *ring, uपूर्णांक32_t *index);
uपूर्णांक64_t amdgpu_sdma_get_csa_mc_addr(काष्ठा amdgpu_ring *ring, अचिन्हित vmid);
पूर्णांक amdgpu_sdma_ras_late_init(काष्ठा amdgpu_device *adev,
			      व्योम *ras_ih_info);
व्योम amdgpu_sdma_ras_fini(काष्ठा amdgpu_device *adev);
पूर्णांक amdgpu_sdma_process_ras_data_cb(काष्ठा amdgpu_device *adev,
		व्योम *err_data,
		काष्ठा amdgpu_iv_entry *entry);
पूर्णांक amdgpu_sdma_process_ecc_irq(काष्ठा amdgpu_device *adev,
				      काष्ठा amdgpu_irq_src *source,
				      काष्ठा amdgpu_iv_entry *entry);
#पूर्ण_अगर
