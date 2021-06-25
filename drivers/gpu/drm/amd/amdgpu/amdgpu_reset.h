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

#अगर_अघोषित __AMDGPU_RESET_H__
#घोषणा __AMDGPU_RESET_H__

#समावेश "amdgpu.h"

क्रमागत AMDGPU_RESET_FLAGS अणु

	AMDGPU_NEED_FULL_RESET = 0,
	AMDGPU_SKIP_HW_RESET = 1,
पूर्ण;

काष्ठा amdgpu_reset_context अणु
	क्रमागत amd_reset_method method;
	काष्ठा amdgpu_device *reset_req_dev;
	काष्ठा amdgpu_job *job;
	काष्ठा amdgpu_hive_info *hive;
	अचिन्हित दीर्घ flags;
पूर्ण;

काष्ठा amdgpu_reset_handler अणु
	क्रमागत amd_reset_method reset_method;
	काष्ठा list_head handler_list;
	पूर्णांक (*prepare_env)(काष्ठा amdgpu_reset_control *reset_ctl,
			   काष्ठा amdgpu_reset_context *context);
	पूर्णांक (*prepare_hwcontext)(काष्ठा amdgpu_reset_control *reset_ctl,
				 काष्ठा amdgpu_reset_context *context);
	पूर्णांक (*perक्रमm_reset)(काष्ठा amdgpu_reset_control *reset_ctl,
			     काष्ठा amdgpu_reset_context *context);
	पूर्णांक (*restore_hwcontext)(काष्ठा amdgpu_reset_control *reset_ctl,
				 काष्ठा amdgpu_reset_context *context);
	पूर्णांक (*restore_env)(काष्ठा amdgpu_reset_control *reset_ctl,
			   काष्ठा amdgpu_reset_context *context);

	पूर्णांक (*करो_reset)(काष्ठा amdgpu_device *adev);
पूर्ण;

काष्ठा amdgpu_reset_control अणु
	व्योम *handle;
	काष्ठा work_काष्ठा reset_work;
	काष्ठा mutex reset_lock;
	काष्ठा list_head reset_handlers;
	atomic_t in_reset;
	क्रमागत amd_reset_method active_reset;
	काष्ठा amdgpu_reset_handler *(*get_reset_handler)(
		काष्ठा amdgpu_reset_control *reset_ctl,
		काष्ठा amdgpu_reset_context *context);
	व्योम (*async_reset)(काष्ठा work_काष्ठा *work);
पूर्ण;

पूर्णांक amdgpu_reset_init(काष्ठा amdgpu_device *adev);
पूर्णांक amdgpu_reset_fini(काष्ठा amdgpu_device *adev);

पूर्णांक amdgpu_reset_prepare_hwcontext(काष्ठा amdgpu_device *adev,
				   काष्ठा amdgpu_reset_context *reset_context);

पूर्णांक amdgpu_reset_perक्रमm_reset(काष्ठा amdgpu_device *adev,
			       काष्ठा amdgpu_reset_context *reset_context);

पूर्णांक amdgpu_reset_add_handler(काष्ठा amdgpu_reset_control *reset_ctl,
			     काष्ठा amdgpu_reset_handler *handler);

#पूर्ण_अगर
