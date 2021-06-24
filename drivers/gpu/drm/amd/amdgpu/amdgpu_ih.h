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

#अगर_अघोषित __AMDGPU_IH_H__
#घोषणा __AMDGPU_IH_H__

/* Maximum number of IVs processed at once */
#घोषणा AMDGPU_IH_MAX_NUM_IVS	32

काष्ठा amdgpu_device;
काष्ठा amdgpu_iv_entry;

काष्ठा amdgpu_ih_regs अणु
	uपूर्णांक32_t ih_rb_base;
	uपूर्णांक32_t ih_rb_base_hi;
	uपूर्णांक32_t ih_rb_cntl;
	uपूर्णांक32_t ih_rb_wptr;
	uपूर्णांक32_t ih_rb_rptr;
	uपूर्णांक32_t ih_करोorbell_rptr;
	uपूर्णांक32_t ih_rb_wptr_addr_lo;
	uपूर्णांक32_t ih_rb_wptr_addr_hi;
	uपूर्णांक32_t psp_reg_id;
पूर्ण;

/*
 * R6xx+ IH ring
 */
काष्ठा amdgpu_ih_ring अणु
	अचिन्हित		ring_size;
	uपूर्णांक32_t		ptr_mask;
	u32			करोorbell_index;
	bool			use_करोorbell;
	bool			use_bus_addr;

	काष्ठा amdgpu_bo	*ring_obj;
	अस्थिर uपूर्णांक32_t	*ring;
	uपूर्णांक64_t		gpu_addr;

	uपूर्णांक64_t		wptr_addr;
	अस्थिर uपूर्णांक32_t	*wptr_cpu;

	uपूर्णांक64_t		rptr_addr;
	अस्थिर uपूर्णांक32_t	*rptr_cpu;

	bool                    enabled;
	अचिन्हित		rptr;
	काष्ठा amdgpu_ih_regs	ih_regs;

	/* For रुकोing on IH processing at checkpoपूर्णांक. */
	रुको_queue_head_t रुको_process;
पूर्ण;

/* provided by the ih block */
काष्ठा amdgpu_ih_funcs अणु
	/* ring पढ़ो/ग_लिखो ptr handling, called from पूर्णांकerrupt context */
	u32 (*get_wptr)(काष्ठा amdgpu_device *adev, काष्ठा amdgpu_ih_ring *ih);
	व्योम (*decode_iv)(काष्ठा amdgpu_device *adev, काष्ठा amdgpu_ih_ring *ih,
			  काष्ठा amdgpu_iv_entry *entry);
	व्योम (*set_rptr)(काष्ठा amdgpu_device *adev, काष्ठा amdgpu_ih_ring *ih);
पूर्ण;

#घोषणा amdgpu_ih_get_wptr(adev, ih) (adev)->irq.ih_funcs->get_wptr((adev), (ih))
#घोषणा amdgpu_ih_decode_iv(adev, iv) \
	(adev)->irq.ih_funcs->decode_iv((adev), (ih), (iv))
#घोषणा amdgpu_ih_set_rptr(adev, ih) (adev)->irq.ih_funcs->set_rptr((adev), (ih))

पूर्णांक amdgpu_ih_ring_init(काष्ठा amdgpu_device *adev, काष्ठा amdgpu_ih_ring *ih,
			अचिन्हित ring_size, bool use_bus_addr);
व्योम amdgpu_ih_ring_fini(काष्ठा amdgpu_device *adev, काष्ठा amdgpu_ih_ring *ih);
व्योम amdgpu_ih_ring_ग_लिखो(काष्ठा amdgpu_ih_ring *ih, स्थिर uपूर्णांक32_t *iv,
			  अचिन्हित पूर्णांक num_dw);
पूर्णांक amdgpu_ih_रुको_on_checkpoपूर्णांक_process(काष्ठा amdgpu_device *adev,
					काष्ठा amdgpu_ih_ring *ih);
पूर्णांक amdgpu_ih_process(काष्ठा amdgpu_device *adev, काष्ठा amdgpu_ih_ring *ih);
व्योम amdgpu_ih_decode_iv_helper(काष्ठा amdgpu_device *adev,
				काष्ठा amdgpu_ih_ring *ih,
				काष्ठा amdgpu_iv_entry *entry);
#पूर्ण_अगर
