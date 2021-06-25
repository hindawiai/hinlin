<शैली गुरु>
/*
 * \पile r128_ioc32.c
 *
 * 32-bit ioctl compatibility routines क्रम the R128 DRM.
 *
 * \चuthor Dave Airlie <airlied@linux.ie> with code from patches by Egbert Eich
 *
 * Copyright (C) Paul Mackerras 2005
 * Copyright (C) Egbert Eich 2003,2004
 * Copyright (C) Dave Airlie 2005
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
 */

#समावेश <linux/compat.h>

#समावेश <drm/r128_drm.h>

#समावेश "r128_drv.h"

प्रकार काष्ठा drm_r128_init32 अणु
	पूर्णांक func;
	अचिन्हित पूर्णांक sarea_priv_offset;
	पूर्णांक is_pci;
	पूर्णांक cce_mode;
	पूर्णांक cce_secure;
	पूर्णांक ring_size;
	पूर्णांक usec_समयout;

	अचिन्हित पूर्णांक fb_bpp;
	अचिन्हित पूर्णांक front_offset, front_pitch;
	अचिन्हित पूर्णांक back_offset, back_pitch;
	अचिन्हित पूर्णांक depth_bpp;
	अचिन्हित पूर्णांक depth_offset, depth_pitch;
	अचिन्हित पूर्णांक span_offset;

	अचिन्हित पूर्णांक fb_offset;
	अचिन्हित पूर्णांक mmio_offset;
	अचिन्हित पूर्णांक ring_offset;
	अचिन्हित पूर्णांक ring_rptr_offset;
	अचिन्हित पूर्णांक buffers_offset;
	अचिन्हित पूर्णांक agp_textures_offset;
पूर्ण drm_r128_init32_t;

अटल पूर्णांक compat_r128_init(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
			    अचिन्हित दीर्घ arg)
अणु
	drm_r128_init32_t init32;
	drm_r128_init_t init;

	अगर (copy_from_user(&init32, (व्योम __user *)arg, माप(init32)))
		वापस -EFAULT;

	init.func = init32.func;
	init.sarea_priv_offset = init32.sarea_priv_offset;
	init.is_pci = init32.is_pci;
	init.cce_mode = init32.cce_mode;
	init.cce_secure = init32.cce_secure;
	init.ring_size = init32.ring_size;
	init.usec_समयout = init32.usec_समयout;
	init.fb_bpp = init32.fb_bpp;
	init.front_offset = init32.front_offset;
	init.front_pitch = init32.front_pitch;
	init.back_offset = init32.back_offset;
	init.back_pitch = init32.back_pitch;
	init.depth_bpp = init32.depth_bpp;
	init.depth_offset = init32.depth_offset;
	init.depth_pitch = init32.depth_pitch;
	init.span_offset = init32.span_offset;
	init.fb_offset = init32.fb_offset;
	init.mmio_offset = init32.mmio_offset;
	init.ring_offset = init32.ring_offset;
	init.ring_rptr_offset = init32.ring_rptr_offset;
	init.buffers_offset = init32.buffers_offset;
	init.agp_textures_offset = init32.agp_textures_offset;

	वापस drm_ioctl_kernel(file, r128_cce_init, &init,
			DRM_AUTH|DRM_MASTER|DRM_ROOT_ONLY);
पूर्ण

प्रकार काष्ठा drm_r128_depth32 अणु
	पूर्णांक func;
	पूर्णांक n;
	u32 x;
	u32 y;
	u32 buffer;
	u32 mask;
पूर्ण drm_r128_depth32_t;

अटल पूर्णांक compat_r128_depth(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
			     अचिन्हित दीर्घ arg)
अणु
	drm_r128_depth32_t depth32;
	drm_r128_depth_t depth;

	अगर (copy_from_user(&depth32, (व्योम __user *)arg, माप(depth32)))
		वापस -EFAULT;

	depth.func = depth32.func;
	depth.n = depth32.n;
	depth.x = compat_ptr(depth32.x);
	depth.y = compat_ptr(depth32.y);
	depth.buffer = compat_ptr(depth32.buffer);
	depth.mask = compat_ptr(depth32.mask);

	वापस drm_ioctl_kernel(file, r128_cce_depth, &depth, DRM_AUTH);
पूर्ण

प्रकार काष्ठा drm_r128_stipple32 अणु
	u32 mask;
पूर्ण drm_r128_stipple32_t;

अटल पूर्णांक compat_r128_stipple(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
			       अचिन्हित दीर्घ arg)
अणु
	drm_r128_stipple32_t stipple32;
	drm_r128_stipple_t stipple;

	अगर (copy_from_user(&stipple32, (व्योम __user *)arg, माप(stipple32)))
		वापस -EFAULT;

	stipple.mask = compat_ptr(stipple32.mask);

	वापस drm_ioctl_kernel(file, r128_cce_stipple, &stipple, DRM_AUTH);
पूर्ण

प्रकार काष्ठा drm_r128_getparam32 अणु
	पूर्णांक param;
	u32 value;
पूर्ण drm_r128_getparam32_t;

अटल पूर्णांक compat_r128_getparam(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
				अचिन्हित दीर्घ arg)
अणु
	drm_r128_getparam32_t getparam32;
	drm_r128_getparam_t getparam;

	अगर (copy_from_user(&getparam32, (व्योम __user *)arg, माप(getparam32)))
		वापस -EFAULT;

	getparam.param = getparam32.param;
	getparam.value = compat_ptr(getparam32.value);

	वापस drm_ioctl_kernel(file, r128_getparam, &getparam, DRM_AUTH);
पूर्ण

drm_ioctl_compat_t *r128_compat_ioctls[] = अणु
	[DRM_R128_INIT] = compat_r128_init,
	[DRM_R128_DEPTH] = compat_r128_depth,
	[DRM_R128_STIPPLE] = compat_r128_stipple,
	[DRM_R128_GETPARAM] = compat_r128_getparam,
पूर्ण;

/**
 * r128_compat_ioctl - Called whenever a 32-bit process running under
 *                     a 64-bit kernel perक्रमms an ioctl on /dev/dri/card<n>.
 *
 * @filp: file poपूर्णांकer.
 * @cmd: command.
 * @arg: user argument.
 * वापस: zero on success or negative number on failure.
 */
दीर्घ r128_compat_ioctl(काष्ठा file *filp, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	अचिन्हित पूर्णांक nr = DRM_IOCTL_NR(cmd);
	drm_ioctl_compat_t *fn = शून्य;
	पूर्णांक ret;

	अगर (nr < DRM_COMMAND_BASE)
		वापस drm_compat_ioctl(filp, cmd, arg);

	अगर (nr < DRM_COMMAND_BASE + ARRAY_SIZE(r128_compat_ioctls))
		fn = r128_compat_ioctls[nr - DRM_COMMAND_BASE];

	अगर (fn != शून्य)
		ret = (*fn) (filp, cmd, arg);
	अन्यथा
		ret = drm_ioctl(filp, cmd, arg);

	वापस ret;
पूर्ण
