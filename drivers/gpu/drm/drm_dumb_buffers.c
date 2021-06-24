<शैली गुरु>
/*
 * Copyright (c) 2006-2008 Intel Corporation
 * Copyright (c) 2007 Dave Airlie <airlied@linux.ie>
 * Copyright (c) 2008 Red Hat Inc.
 * Copyright (c) 2016 Intel Corporation
 *
 * Permission to use, copy, modअगरy, distribute, and sell this software and its
 * करोcumentation क्रम any purpose is hereby granted without fee, provided that
 * the above copyright notice appear in all copies and that both that copyright
 * notice and this permission notice appear in supporting करोcumentation, and
 * that the name of the copyright holders not be used in advertising or
 * खुलाity pertaining to distribution of the software without specअगरic,
 * written prior permission.  The copyright holders make no representations
 * about the suitability of this software क्रम any purpose.  It is provided "as
 * is" without express or implied warranty.
 *
 * THE COPYRIGHT HOLDERS DISCLAIM ALL WARRANTIES WITH REGARD TO THIS SOFTWARE,
 * INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO
 * EVENT SHALL THE COPYRIGHT HOLDERS BE LIABLE FOR ANY SPECIAL, INसूचीECT OR
 * CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE,
 * DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 * TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE
 * OF THIS SOFTWARE.
 */

#समावेश <drm/drm_device.h>
#समावेश <drm/drm_drv.h>
#समावेश <drm/drm_gem.h>
#समावेश <drm/drm_mode.h>

#समावेश "drm_crtc_internal.h"
#समावेश "drm_internal.h"

/**
 * DOC: overview
 *
 * The KMS API करोesn't standardize backing storage object creation and leaves it
 * to driver-specअगरic ioctls. Furthermore actually creating a buffer object even
 * क्रम GEM-based drivers is करोne through a driver-specअगरic ioctl - GEM only has
 * a common userspace पूर्णांकerface क्रम sharing and destroying objects. While not an
 * issue क्रम full-fledged graphics stacks that include device-specअगरic userspace
 * components (in libdrm क्रम instance), this limit makes DRM-based early boot
 * graphics unnecessarily complex.
 *
 * Dumb objects partly alleviate the problem by providing a standard API to
 * create dumb buffers suitable क्रम scanout, which can then be used to create
 * KMS frame buffers.
 *
 * To support dumb objects drivers must implement the &drm_driver.dumb_create
 * and &drm_driver.dumb_map_offset operations (the latter शेषs to
 * drm_gem_dumb_map_offset() अगर not set). Drivers that करोn't use GEM handles
 * additionally need to implement the &drm_driver.dumb_destroy operation. See
 * the callbacks क्रम further details.
 *
 * Note that dumb objects may not be used क्रम gpu acceleration, as has been
 * attempted on some ARM embedded platक्रमms. Such drivers really must have
 * a hardware-specअगरic ioctl to allocate suitable buffer objects.
 */

पूर्णांक drm_mode_create_dumb(काष्ठा drm_device *dev,
			 काष्ठा drm_mode_create_dumb *args,
			 काष्ठा drm_file *file_priv)
अणु
	u32 cpp, stride, size;

	अगर (!dev->driver->dumb_create)
		वापस -ENOSYS;
	अगर (!args->width || !args->height || !args->bpp)
		वापस -EINVAL;

	/* overflow checks क्रम 32bit size calculations */
	अगर (args->bpp > U32_MAX - 8)
		वापस -EINVAL;
	cpp = DIV_ROUND_UP(args->bpp, 8);
	अगर (cpp > U32_MAX / args->width)
		वापस -EINVAL;
	stride = cpp * args->width;
	अगर (args->height > U32_MAX / stride)
		वापस -EINVAL;

	/* test क्रम wrap-around */
	size = args->height * stride;
	अगर (PAGE_ALIGN(size) == 0)
		वापस -EINVAL;

	/*
	 * handle, pitch and size are output parameters. Zero them out to
	 * prevent drivers from accidentally using uninitialized data. Since
	 * not all existing userspace is clearing these fields properly we
	 * cannot reject IOCTL with garbage in them.
	 */
	args->handle = 0;
	args->pitch = 0;
	args->size = 0;

	वापस dev->driver->dumb_create(file_priv, dev, args);
पूर्ण

पूर्णांक drm_mode_create_dumb_ioctl(काष्ठा drm_device *dev,
			       व्योम *data, काष्ठा drm_file *file_priv)
अणु
	वापस drm_mode_create_dumb(dev, data, file_priv);
पूर्ण

/**
 * drm_mode_mmap_dumb_ioctl - create an mmap offset क्रम a dumb backing storage buffer
 * @dev: DRM device
 * @data: ioctl data
 * @file_priv: DRM file info
 *
 * Allocate an offset in the drm device node's address space to be able to
 * memory map a dumb buffer.
 *
 * Called by the user via ioctl.
 *
 * Returns:
 * Zero on success, negative त्रुटि_सं on failure.
 */
पूर्णांक drm_mode_mmap_dumb_ioctl(काष्ठा drm_device *dev,
			     व्योम *data, काष्ठा drm_file *file_priv)
अणु
	काष्ठा drm_mode_map_dumb *args = data;

	अगर (!dev->driver->dumb_create)
		वापस -ENOSYS;

	अगर (dev->driver->dumb_map_offset)
		वापस dev->driver->dumb_map_offset(file_priv, dev,
						    args->handle,
						    &args->offset);
	अन्यथा
		वापस drm_gem_dumb_map_offset(file_priv, dev, args->handle,
					       &args->offset);
पूर्ण

पूर्णांक drm_mode_destroy_dumb(काष्ठा drm_device *dev, u32 handle,
			  काष्ठा drm_file *file_priv)
अणु
	अगर (!dev->driver->dumb_create)
		वापस -ENOSYS;

	अगर (dev->driver->dumb_destroy)
		वापस dev->driver->dumb_destroy(file_priv, dev, handle);
	अन्यथा
		वापस drm_gem_dumb_destroy(file_priv, dev, handle);
पूर्ण

पूर्णांक drm_mode_destroy_dumb_ioctl(काष्ठा drm_device *dev,
				व्योम *data, काष्ठा drm_file *file_priv)
अणु
	काष्ठा drm_mode_destroy_dumb *args = data;

	वापस drm_mode_destroy_dumb(dev, args->handle, file_priv);
पूर्ण
