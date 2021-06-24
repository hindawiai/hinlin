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

#अगर_अघोषित __AMDGPU_IRQ_H__
#घोषणा __AMDGPU_IRQ_H__

#समावेश <linux/irqकरोमुख्य.h>
#समावेश "soc15_ih_clientid.h"
#समावेश "amdgpu_ih.h"

#घोषणा AMDGPU_MAX_IRQ_SRC_ID		0x100
#घोषणा AMDGPU_MAX_IRQ_CLIENT_ID	0x100

#घोषणा AMDGPU_IRQ_CLIENTID_LEGACY	0
#घोषणा AMDGPU_IRQ_CLIENTID_MAX		SOC15_IH_CLIENTID_MAX

#घोषणा AMDGPU_IRQ_SRC_DATA_MAX_SIZE_DW	4

काष्ठा amdgpu_device;

क्रमागत amdgpu_पूर्णांकerrupt_state अणु
	AMDGPU_IRQ_STATE_DISABLE,
	AMDGPU_IRQ_STATE_ENABLE,
पूर्ण;

काष्ठा amdgpu_iv_entry अणु
	काष्ठा amdgpu_ih_ring *ih;
	अचिन्हित client_id;
	अचिन्हित src_id;
	अचिन्हित ring_id;
	अचिन्हित vmid;
	अचिन्हित vmid_src;
	uपूर्णांक64_t बारtamp;
	अचिन्हित बारtamp_src;
	अचिन्हित pasid;
	अचिन्हित pasid_src;
	अचिन्हित src_data[AMDGPU_IRQ_SRC_DATA_MAX_SIZE_DW];
	स्थिर uपूर्णांक32_t *iv_entry;
पूर्ण;

काष्ठा amdgpu_irq_src अणु
	अचिन्हित				num_types;
	atomic_t				*enabled_types;
	स्थिर काष्ठा amdgpu_irq_src_funcs	*funcs;
पूर्ण;

काष्ठा amdgpu_irq_client अणु
	काष्ठा amdgpu_irq_src **sources;
पूर्ण;

/* provided by पूर्णांकerrupt generating IP blocks */
काष्ठा amdgpu_irq_src_funcs अणु
	पूर्णांक (*set)(काष्ठा amdgpu_device *adev, काष्ठा amdgpu_irq_src *source,
		   अचिन्हित type, क्रमागत amdgpu_पूर्णांकerrupt_state state);

	पूर्णांक (*process)(काष्ठा amdgpu_device *adev,
		       काष्ठा amdgpu_irq_src *source,
		       काष्ठा amdgpu_iv_entry *entry);
पूर्ण;

काष्ठा amdgpu_irq अणु
	bool				installed;
	spinlock_t			lock;
	/* पूर्णांकerrupt sources */
	काष्ठा amdgpu_irq_client	client[AMDGPU_IRQ_CLIENTID_MAX];

	/* status, etc. */
	bool				msi_enabled; /* msi enabled */

	/* पूर्णांकerrupt rings */
	काष्ठा amdgpu_ih_ring		ih, ih1, ih2, ih_soft;
	स्थिर काष्ठा amdgpu_ih_funcs    *ih_funcs;
	काष्ठा work_काष्ठा		ih1_work, ih2_work, ih_soft_work;
	काष्ठा amdgpu_irq_src		self_irq;

	/* gen irq stuff */
	काष्ठा irq_करोमुख्य		*करोमुख्य; /* GPU irq controller करोमुख्य */
	अचिन्हित			virq[AMDGPU_MAX_IRQ_SRC_ID];
	uपूर्णांक32_t                        srbm_soft_reset;
पूर्ण;

व्योम amdgpu_irq_disable_all(काष्ठा amdgpu_device *adev);
irqवापस_t amdgpu_irq_handler(पूर्णांक irq, व्योम *arg);

पूर्णांक amdgpu_irq_init(काष्ठा amdgpu_device *adev);
व्योम amdgpu_irq_fini(काष्ठा amdgpu_device *adev);
पूर्णांक amdgpu_irq_add_id(काष्ठा amdgpu_device *adev,
		      अचिन्हित client_id, अचिन्हित src_id,
		      काष्ठा amdgpu_irq_src *source);
व्योम amdgpu_irq_dispatch(काष्ठा amdgpu_device *adev,
			 काष्ठा amdgpu_ih_ring *ih);
व्योम amdgpu_irq_delegate(काष्ठा amdgpu_device *adev,
			 काष्ठा amdgpu_iv_entry *entry,
			 अचिन्हित पूर्णांक num_dw);
पूर्णांक amdgpu_irq_update(काष्ठा amdgpu_device *adev, काष्ठा amdgpu_irq_src *src,
		      अचिन्हित type);
पूर्णांक amdgpu_irq_get(काष्ठा amdgpu_device *adev, काष्ठा amdgpu_irq_src *src,
		   अचिन्हित type);
पूर्णांक amdgpu_irq_put(काष्ठा amdgpu_device *adev, काष्ठा amdgpu_irq_src *src,
		   अचिन्हित type);
bool amdgpu_irq_enabled(काष्ठा amdgpu_device *adev, काष्ठा amdgpu_irq_src *src,
			अचिन्हित type);
व्योम amdgpu_irq_gpu_reset_resume_helper(काष्ठा amdgpu_device *adev);

पूर्णांक amdgpu_irq_add_करोमुख्य(काष्ठा amdgpu_device *adev);
व्योम amdgpu_irq_हटाओ_करोमुख्य(काष्ठा amdgpu_device *adev);
अचिन्हित amdgpu_irq_create_mapping(काष्ठा amdgpu_device *adev, अचिन्हित src_id);

#पूर्ण_अगर
