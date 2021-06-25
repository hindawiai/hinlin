<शैली गुरु>
/*
 * Copyright 2021 Advanced Micro Devices, Inc.
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

#समावेश "amdgpu_reset.h"
#समावेश "aldebaran.h"

पूर्णांक amdgpu_reset_add_handler(काष्ठा amdgpu_reset_control *reset_ctl,
			     काष्ठा amdgpu_reset_handler *handler)
अणु
	/* TODO: Check अगर handler exists? */
	list_add_tail(&handler->handler_list, &reset_ctl->reset_handlers);
	वापस 0;
पूर्ण

पूर्णांक amdgpu_reset_init(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक ret = 0;

	चयन (adev->asic_type) अणु
	हाल CHIP_ALDEBARAN:
		ret = aldebaran_reset_init(adev);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक amdgpu_reset_fini(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक ret = 0;

	चयन (adev->asic_type) अणु
	हाल CHIP_ALDEBARAN:
		ret = aldebaran_reset_fini(adev);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक amdgpu_reset_prepare_hwcontext(काष्ठा amdgpu_device *adev,
				   काष्ठा amdgpu_reset_context *reset_context)
अणु
	काष्ठा amdgpu_reset_handler *reset_handler = शून्य;

	अगर (adev->reset_cntl && adev->reset_cntl->get_reset_handler)
		reset_handler = adev->reset_cntl->get_reset_handler(
			adev->reset_cntl, reset_context);
	अगर (!reset_handler)
		वापस -ENOSYS;

	वापस reset_handler->prepare_hwcontext(adev->reset_cntl,
						reset_context);
पूर्ण

पूर्णांक amdgpu_reset_perक्रमm_reset(काष्ठा amdgpu_device *adev,
			       काष्ठा amdgpu_reset_context *reset_context)
अणु
	पूर्णांक ret;
	काष्ठा amdgpu_reset_handler *reset_handler = शून्य;

	अगर (adev->reset_cntl)
		reset_handler = adev->reset_cntl->get_reset_handler(
			adev->reset_cntl, reset_context);
	अगर (!reset_handler)
		वापस -ENOSYS;

	ret = reset_handler->perक्रमm_reset(adev->reset_cntl, reset_context);
	अगर (ret)
		वापस ret;

	वापस reset_handler->restore_hwcontext(adev->reset_cntl,
						reset_context);
पूर्ण
