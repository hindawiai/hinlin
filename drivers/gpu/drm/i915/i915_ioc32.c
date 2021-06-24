<शैली गुरु>
/*
 * 32-bit ioctl compatibility routines क्रम the i915 DRM.
 *
 * Copyright (C) Paul Mackerras 2005
 * Copyright (C) Alan Hourihane 2005
 * All Rights Reserved.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHOR BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 *
 * Author: Alan Hourihane <alanh@fairlite.demon.co.uk>
 */
#समावेश <linux/compat.h>

#समावेश <drm/drm_ioctl.h>

#समावेश "i915_drv.h"
#समावेश "i915_ioc32.h"

काष्ठा drm_i915_getparam32 अणु
	s32 param;
	/*
	 * We screwed up the generic ioctl काष्ठा here and used a variable-sized
	 * poपूर्णांकer. Use u32 in the compat काष्ठा to match the 32bit poपूर्णांकer
	 * userspace expects.
	 */
	u32 value;
पूर्ण;

अटल पूर्णांक compat_i915_getparam(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
				अचिन्हित दीर्घ arg)
अणु
	काष्ठा drm_i915_getparam32 req32;
	काष्ठा drm_i915_getparam req;

	अगर (copy_from_user(&req32, (व्योम __user *)arg, माप(req32)))
		वापस -EFAULT;

	req.param = req32.param;
	req.value = compat_ptr(req32.value);

	वापस drm_ioctl_kernel(file, i915_getparam_ioctl, &req,
				DRM_RENDER_ALLOW);
पूर्ण

अटल drm_ioctl_compat_t *i915_compat_ioctls[] = अणु
	[DRM_I915_GETPARAM] = compat_i915_getparam,
पूर्ण;

/**
 * i915_ioc32_compat_ioctl - handle the mistakes of the past
 * @filp: the file poपूर्णांकer
 * @cmd: the ioctl command (and encoded flags)
 * @arg: the ioctl argument (from userspace)
 *
 * Called whenever a 32-bit process running under a 64-bit kernel
 * perक्रमms an ioctl on /dev/dri/card<n>.
 */
दीर्घ i915_ioc32_compat_ioctl(काष्ठा file *filp, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	अचिन्हित पूर्णांक nr = DRM_IOCTL_NR(cmd);
	drm_ioctl_compat_t *fn = शून्य;
	पूर्णांक ret;

	अगर (nr < DRM_COMMAND_BASE || nr >= DRM_COMMAND_END)
		वापस drm_compat_ioctl(filp, cmd, arg);

	अगर (nr < DRM_COMMAND_BASE + ARRAY_SIZE(i915_compat_ioctls))
		fn = i915_compat_ioctls[nr - DRM_COMMAND_BASE];

	अगर (fn != शून्य)
		ret = (*fn) (filp, cmd, arg);
	अन्यथा
		ret = drm_ioctl(filp, cmd, arg);

	वापस ret;
पूर्ण
