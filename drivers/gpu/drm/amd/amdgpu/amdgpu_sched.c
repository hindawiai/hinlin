<शैली गुरु>
/*
 * Copyright 2017 Valve Corporation
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
 * Authors: Andres Rodriguez <andresx7@gmail.com>
 */

#समावेश <linux/fdtable.h>
#समावेश <linux/file.h>
#समावेश <linux/pid.h>

#समावेश <drm/amdgpu_drm.h>

#समावेश "amdgpu.h"
#समावेश "amdgpu_sched.h"
#समावेश "amdgpu_vm.h"

पूर्णांक amdgpu_to_sched_priority(पूर्णांक amdgpu_priority,
			     क्रमागत drm_sched_priority *prio)
अणु
	चयन (amdgpu_priority) अणु
	हाल AMDGPU_CTX_PRIORITY_VERY_HIGH:
		*prio = DRM_SCHED_PRIORITY_HIGH;
		अवरोध;
	हाल AMDGPU_CTX_PRIORITY_HIGH:
		*prio = DRM_SCHED_PRIORITY_HIGH;
		अवरोध;
	हाल AMDGPU_CTX_PRIORITY_NORMAL:
		*prio = DRM_SCHED_PRIORITY_NORMAL;
		अवरोध;
	हाल AMDGPU_CTX_PRIORITY_LOW:
	हाल AMDGPU_CTX_PRIORITY_VERY_LOW:
		*prio = DRM_SCHED_PRIORITY_MIN;
		अवरोध;
	हाल AMDGPU_CTX_PRIORITY_UNSET:
		*prio = DRM_SCHED_PRIORITY_UNSET;
		अवरोध;
	शेष:
		WARN(1, "Invalid context priority %d\n", amdgpu_priority);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक amdgpu_sched_process_priority_override(काष्ठा amdgpu_device *adev,
						  पूर्णांक fd,
						  क्रमागत drm_sched_priority priority)
अणु
	काष्ठा fd f = fdget(fd);
	काष्ठा amdgpu_fpriv *fpriv;
	काष्ठा amdgpu_ctx *ctx;
	uपूर्णांक32_t id;
	पूर्णांक r;

	अगर (!f.file)
		वापस -EINVAL;

	r = amdgpu_file_to_fpriv(f.file, &fpriv);
	अगर (r) अणु
		fdput(f);
		वापस r;
	पूर्ण

	idr_क्रम_each_entry(&fpriv->ctx_mgr.ctx_handles, ctx, id)
		amdgpu_ctx_priority_override(ctx, priority);

	fdput(f);
	वापस 0;
पूर्ण

अटल पूर्णांक amdgpu_sched_context_priority_override(काष्ठा amdgpu_device *adev,
						  पूर्णांक fd,
						  अचिन्हित ctx_id,
						  क्रमागत drm_sched_priority priority)
अणु
	काष्ठा fd f = fdget(fd);
	काष्ठा amdgpu_fpriv *fpriv;
	काष्ठा amdgpu_ctx *ctx;
	पूर्णांक r;

	अगर (!f.file)
		वापस -EINVAL;

	r = amdgpu_file_to_fpriv(f.file, &fpriv);
	अगर (r) अणु
		fdput(f);
		वापस r;
	पूर्ण

	ctx = amdgpu_ctx_get(fpriv, ctx_id);

	अगर (!ctx) अणु
		fdput(f);
		वापस -EINVAL;
	पूर्ण

	amdgpu_ctx_priority_override(ctx, priority);
	amdgpu_ctx_put(ctx);
	fdput(f);

	वापस 0;
पूर्ण

पूर्णांक amdgpu_sched_ioctl(काष्ठा drm_device *dev, व्योम *data,
		       काष्ठा drm_file *filp)
अणु
	जोड़ drm_amdgpu_sched *args = data;
	काष्ठा amdgpu_device *adev = drm_to_adev(dev);
	क्रमागत drm_sched_priority priority;
	पूर्णांक r;

	/* First check the op, then the op's argument.
	 */
	चयन (args->in.op) अणु
	हाल AMDGPU_SCHED_OP_PROCESS_PRIORITY_OVERRIDE:
	हाल AMDGPU_SCHED_OP_CONTEXT_PRIORITY_OVERRIDE:
		अवरोध;
	शेष:
		DRM_ERROR("Invalid sched op specified: %d\n", args->in.op);
		वापस -EINVAL;
	पूर्ण

	r = amdgpu_to_sched_priority(args->in.priority, &priority);
	अगर (r)
		वापस r;

	चयन (args->in.op) अणु
	हाल AMDGPU_SCHED_OP_PROCESS_PRIORITY_OVERRIDE:
		r = amdgpu_sched_process_priority_override(adev,
							   args->in.fd,
							   priority);
		अवरोध;
	हाल AMDGPU_SCHED_OP_CONTEXT_PRIORITY_OVERRIDE:
		r = amdgpu_sched_context_priority_override(adev,
							   args->in.fd,
							   args->in.ctx_id,
							   priority);
		अवरोध;
	शेष:
		/* Impossible.
		 */
		r = -EINVAL;
		अवरोध;
	पूर्ण

	वापस r;
पूर्ण
