<शैली गुरु>
/*
 * \पile mga_ioc32.c
 *
 * 32-bit ioctl compatibility routines क्रम the MGA DRM.
 *
 * \चuthor Dave Airlie <airlied@linux.ie> with code from patches by Egbert Eich
 *
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

#समावेश "mga_drv.h"

प्रकार काष्ठा drm32_mga_init अणु
	पूर्णांक func;
	u32 sarea_priv_offset;
	पूर्णांक chipset;
	पूर्णांक sgram;
	अचिन्हित पूर्णांक maccess;
	अचिन्हित पूर्णांक fb_cpp;
	अचिन्हित पूर्णांक front_offset, front_pitch;
	अचिन्हित पूर्णांक back_offset, back_pitch;
	अचिन्हित पूर्णांक depth_cpp;
	अचिन्हित पूर्णांक depth_offset, depth_pitch;
	अचिन्हित पूर्णांक texture_offset[MGA_NR_TEX_HEAPS];
	अचिन्हित पूर्णांक texture_size[MGA_NR_TEX_HEAPS];
	u32 fb_offset;
	u32 mmio_offset;
	u32 status_offset;
	u32 warp_offset;
	u32 primary_offset;
	u32 buffers_offset;
पूर्ण drm_mga_init32_t;

अटल पूर्णांक compat_mga_init(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
			   अचिन्हित दीर्घ arg)
अणु
	drm_mga_init32_t init32;
	drm_mga_init_t init;

	अगर (copy_from_user(&init32, (व्योम __user *)arg, माप(init32)))
		वापस -EFAULT;

	init.func = init32.func;
	init.sarea_priv_offset = init32.sarea_priv_offset;
	स_नकल(&init.chipset, &init32.chipset,
		दुरत्व(drm_mga_init_t, fb_offset) -
		दुरत्व(drm_mga_init_t, chipset));
	init.fb_offset = init32.fb_offset;
	init.mmio_offset = init32.mmio_offset;
	init.status_offset = init32.status_offset;
	init.warp_offset = init32.warp_offset;
	init.primary_offset = init32.primary_offset;
	init.buffers_offset = init32.buffers_offset;

	वापस drm_ioctl_kernel(file, mga_dma_init, &init,
				DRM_AUTH|DRM_MASTER|DRM_ROOT_ONLY);
पूर्ण

प्रकार काष्ठा drm_mga_getparam32 अणु
	पूर्णांक param;
	u32 value;
पूर्ण drm_mga_getparam32_t;

अटल पूर्णांक compat_mga_getparam(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
			       अचिन्हित दीर्घ arg)
अणु
	drm_mga_getparam32_t getparam32;
	drm_mga_getparam_t getparam;

	अगर (copy_from_user(&getparam32, (व्योम __user *)arg, माप(getparam32)))
		वापस -EFAULT;

	getparam.param = getparam32.param;
	getparam.value = compat_ptr(getparam32.value);
	वापस drm_ioctl_kernel(file, mga_getparam, &getparam, DRM_AUTH);
पूर्ण

प्रकार काष्ठा drm_mga_drm_bootstrap32 अणु
	u32 texture_handle;
	u32 texture_size;
	u32 primary_size;
	u32 secondary_bin_count;
	u32 secondary_bin_size;
	u32 agp_mode;
	u8 agp_size;
पूर्ण drm_mga_dma_bootstrap32_t;

अटल पूर्णांक compat_mga_dma_bootstrap(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
				    अचिन्हित दीर्घ arg)
अणु
	drm_mga_dma_bootstrap32_t dma_bootstrap32;
	drm_mga_dma_bootstrap_t dma_bootstrap;
	पूर्णांक err;

	अगर (copy_from_user(&dma_bootstrap32, (व्योम __user *)arg,
			   माप(dma_bootstrap32)))
		वापस -EFAULT;

	dma_bootstrap.texture_handle = dma_bootstrap32.texture_handle;
	dma_bootstrap.texture_size = dma_bootstrap32.texture_size;
	dma_bootstrap.primary_size = dma_bootstrap32.primary_size;
	dma_bootstrap.secondary_bin_count = dma_bootstrap32.secondary_bin_count;
	dma_bootstrap.secondary_bin_size = dma_bootstrap32.secondary_bin_size;
	dma_bootstrap.agp_mode = dma_bootstrap32.agp_mode;
	dma_bootstrap.agp_size = dma_bootstrap32.agp_size;

	err = drm_ioctl_kernel(file, mga_dma_bootstrap, &dma_bootstrap,
				DRM_AUTH|DRM_MASTER|DRM_ROOT_ONLY);
	अगर (err)
		वापस err;

	dma_bootstrap32.texture_handle = dma_bootstrap.texture_handle;
	dma_bootstrap32.texture_size = dma_bootstrap.texture_size;
	dma_bootstrap32.primary_size = dma_bootstrap.primary_size;
	dma_bootstrap32.secondary_bin_count = dma_bootstrap.secondary_bin_count;
	dma_bootstrap32.secondary_bin_size = dma_bootstrap.secondary_bin_size;
	dma_bootstrap32.agp_mode = dma_bootstrap.agp_mode;
	dma_bootstrap32.agp_size = dma_bootstrap.agp_size;
	अगर (copy_to_user((व्योम __user *)arg, &dma_bootstrap32,
			 माप(dma_bootstrap32)))
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल काष्ठा अणु
	drm_ioctl_compat_t *fn;
	अक्षर *name;
पूर्ण mga_compat_ioctls[] = अणु
#घोषणा DRM_IOCTL32_DEF(n, f)[DRM_##n] = अणु.fn = f, .name = #nपूर्ण
	DRM_IOCTL32_DEF(MGA_INIT, compat_mga_init),
	DRM_IOCTL32_DEF(MGA_GETPARAM, compat_mga_getparam),
	DRM_IOCTL32_DEF(MGA_DMA_BOOTSTRAP, compat_mga_dma_bootstrap),
पूर्ण;

/**
 * mga_compat_ioctl - Called whenever a 32-bit process running under
 *                    a 64-bit kernel perक्रमms an ioctl on /dev/dri/card<n>.
 *
 * @filp: file poपूर्णांकer.
 * @cmd:  command.
 * @arg:  user argument.
 * वापस: zero on success or negative number on failure.
 */
दीर्घ mga_compat_ioctl(काष्ठा file *filp, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	अचिन्हित पूर्णांक nr = DRM_IOCTL_NR(cmd);
	काष्ठा drm_file *file_priv = filp->निजी_data;
	drm_ioctl_compat_t *fn = शून्य;
	पूर्णांक ret;

	अगर (nr < DRM_COMMAND_BASE)
		वापस drm_compat_ioctl(filp, cmd, arg);

	अगर (nr >= DRM_COMMAND_BASE + ARRAY_SIZE(mga_compat_ioctls))
		वापस drm_ioctl(filp, cmd, arg);

	fn = mga_compat_ioctls[nr - DRM_COMMAND_BASE].fn;
	अगर (!fn)
		वापस drm_ioctl(filp, cmd, arg);

	DRM_DEBUG("pid=%d, dev=0x%lx, auth=%d, %s\n",
		  task_pid_nr(current),
		  (दीर्घ)old_encode_dev(file_priv->minor->kdev->devt),
		  file_priv->authenticated,
		  mga_compat_ioctls[nr - DRM_COMMAND_BASE].name);
	ret = (*fn) (filp, cmd, arg);
	अगर (ret)
		DRM_DEBUG("ret = %d\n", ret);
	वापस ret;
पूर्ण
