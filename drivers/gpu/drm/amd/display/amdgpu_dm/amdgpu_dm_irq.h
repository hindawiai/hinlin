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

#अगर_अघोषित __AMDGPU_DM_IRQ_H__
#घोषणा __AMDGPU_DM_IRQ_H__

#समावेश "irq_types.h" /* DAL irq definitions */

/*
 * Display Manager IRQ-related पूर्णांकerfaces (क्रम use by DAL).
 */

/**
 * amdgpu_dm_irq_init - Initialize पूर्णांकernal काष्ठाures of 'amdgpu_dm_irq'.
 *
 * This function should be called exactly once - during DM initialization.
 *
 * Returns:
 *	0 - success
 *	non-zero - error
 */
पूर्णांक amdgpu_dm_irq_init(काष्ठा amdgpu_device *adev);

/**
 * amdgpu_dm_irq_fini - deallocate पूर्णांकernal काष्ठाures of 'amdgpu_dm_irq'.
 *
 * This function should be called exactly once - during DM deकाष्ठाion.
 *
 */
व्योम amdgpu_dm_irq_fini(काष्ठा amdgpu_device *adev);

/**
 * amdgpu_dm_irq_रेजिस्टर_पूर्णांकerrupt - रेजिस्टर irq handler क्रम Display block.
 *
 * @adev: AMD DRM device
 * @पूर्णांक_params: parameters क्रम the irq
 * @ih: poपूर्णांकer to the irq hander function
 * @handler_args: arguments which will be passed to ih
 *
 * Returns:
 * 	IRQ Handler Index on success.
 * 	शून्य on failure.
 *
 * Cannot be called from an पूर्णांकerrupt handler.
 */
व्योम *amdgpu_dm_irq_रेजिस्टर_पूर्णांकerrupt(काष्ठा amdgpu_device *adev,
				       काष्ठा dc_पूर्णांकerrupt_params *पूर्णांक_params,
				       व्योम (*ih)(व्योम *),
				       व्योम *handler_args);

/**
 * amdgpu_dm_irq_unरेजिस्टर_पूर्णांकerrupt - unरेजिस्टर handler which was रेजिस्टरed
 *	by amdgpu_dm_irq_रेजिस्टर_पूर्णांकerrupt().
 *
 * @adev: AMD DRM device.
 * @ih_index: irq handler index which was वापसed by
 *	amdgpu_dm_irq_रेजिस्टर_पूर्णांकerrupt
 */
व्योम amdgpu_dm_irq_unरेजिस्टर_पूर्णांकerrupt(काष्ठा amdgpu_device *adev,
					क्रमागत dc_irq_source irq_source,
					व्योम *ih_index);

व्योम amdgpu_dm_set_irq_funcs(काष्ठा amdgpu_device *adev);

व्योम amdgpu_dm_hpd_init(काष्ठा amdgpu_device *adev);
व्योम amdgpu_dm_hpd_fini(काष्ठा amdgpu_device *adev);

/**
 * amdgpu_dm_irq_suspend - disable ASIC पूर्णांकerrupt during suspend.
 *
 */
पूर्णांक amdgpu_dm_irq_suspend(काष्ठा amdgpu_device *adev);

/**
 * amdgpu_dm_irq_resume_early - enable HPDRX ASIC पूर्णांकerrupts during resume.
 * amdgpu_dm_irq_resume - enable ASIC पूर्णांकerrupt during resume.
 *
 */
पूर्णांक amdgpu_dm_irq_resume_early(काष्ठा amdgpu_device *adev);
पूर्णांक amdgpu_dm_irq_resume_late(काष्ठा amdgpu_device *adev);

#पूर्ण_अगर /* __AMDGPU_DM_IRQ_H__ */
