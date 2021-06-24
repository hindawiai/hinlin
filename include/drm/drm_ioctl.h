<शैली गुरु>
/*
 * Internal Header क्रम the Direct Rendering Manager
 *
 * Copyright 1999 Precision Insight, Inc., Cedar Park, Texas.
 * Copyright 2000 VA Linux Systems, Inc., Sunnyvale, Calअगरornia.
 * Copyright (c) 2009-2010, Code Aurora Forum.
 * All rights reserved.
 *
 * Author: Rickard E. (Rik) Faith <faith@valinux.com>
 * Author: Gareth Hughes <gareth@valinux.com>
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
 * VA LINUX SYSTEMS AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#अगर_अघोषित _DRM_IOCTL_H_
#घोषणा _DRM_IOCTL_H_

#समावेश <linux/types.h>
#समावेश <linux/bitops.h>

#समावेश <यंत्र/ioctl.h>

काष्ठा drm_device;
काष्ठा drm_file;
काष्ठा file;

/**
 * drm_ioctl_t - DRM ioctl function type.
 * @dev: DRM device inode
 * @data: निजी poपूर्णांकer of the ioctl call
 * @file_priv: DRM file this ioctl was made on
 *
 * This is the DRM ioctl प्रकार. Note that drm_ioctl() has alrady copied @data
 * पूर्णांकo kernel-space, and will also copy it back, depending upon the पढ़ो/ग_लिखो
 * settings in the ioctl command code.
 */
प्रकार पूर्णांक drm_ioctl_t(काष्ठा drm_device *dev, व्योम *data,
			काष्ठा drm_file *file_priv);

/**
 * drm_ioctl_compat_t - compatibility DRM ioctl function type.
 * @filp: file poपूर्णांकer
 * @cmd: ioctl command code
 * @arg: DRM file this ioctl was made on
 *
 * Just a प्रकार to make declaring an array of compatibility handlers easier.
 * New drivers shouldn't screw up the काष्ठाure layout क्रम their ioctl
 * काष्ठाures and hence never need this.
 */
प्रकार पूर्णांक drm_ioctl_compat_t(काष्ठा file *filp, अचिन्हित पूर्णांक cmd,
			       अचिन्हित दीर्घ arg);

#घोषणा DRM_IOCTL_NR(n)                _IOC_NR(n)
#घोषणा DRM_MAJOR       226

/**
 * क्रमागत drm_ioctl_flags - DRM ioctl flags
 *
 * Various flags that can be set in &drm_ioctl_desc.flags to control how
 * userspace can use a given ioctl.
 */
क्रमागत drm_ioctl_flags अणु
	/**
	 * @DRM_AUTH:
	 *
	 * This is क्रम ioctl which are used क्रम rendering, and require that the
	 * file descriptor is either क्रम a render node, or अगर it's a
	 * legacy/primary node, then it must be authenticated.
	 */
	DRM_AUTH		= BIT(0),
	/**
	 * @DRM_MASTER:
	 *
	 * This must be set क्रम any ioctl which can change the modeset or
	 * display state. Userspace must call the ioctl through a primary node,
	 * जबतक it is the active master.
	 *
	 * Note that पढ़ो-only modeset ioctl can also be called by
	 * unauthenticated clients, or when a master is not the currently active
	 * one.
	 */
	DRM_MASTER		= BIT(1),
	/**
	 * @DRM_ROOT_ONLY:
	 *
	 * Anything that could potentially wreak a master file descriptor needs
	 * to have this flag set. Current that's only क्रम the SETMASTER and
	 * DROPMASTER ioctl, which e.g. logind can call to क्रमce a non-behaving
	 * master (display compositor) पूर्णांकo compliance.
	 *
	 * This is equivalent to callers with the SYSADMIN capability.
	 */
	DRM_ROOT_ONLY		= BIT(2),
	/**
	 * @DRM_UNLOCKED:
	 *
	 * Whether &drm_ioctl_desc.func should be called with the DRM BKL held
	 * or not. Enक्रमced as the शेष क्रम all modern drivers, hence there
	 * should never be a need to set this flag.
	 *
	 * Do not use anywhere अन्यथा than क्रम the VBLANK_WAIT IOCTL, which is the
	 * only legacy IOCTL which needs this.
	 */
	DRM_UNLOCKED		= BIT(4),
	/**
	 * @DRM_RENDER_ALLOW:
	 *
	 * This is used क्रम all ioctl needed क्रम rendering only, क्रम drivers
	 * which support render nodes. This should be all new render drivers,
	 * and hence it should be always set क्रम any ioctl with DRM_AUTH set.
	 * Note though that पढ़ो-only query ioctl might have this set, but have
	 * not set DRM_AUTH because they करो not require authentication.
	 */
	DRM_RENDER_ALLOW	= BIT(5),
पूर्ण;

/**
 * काष्ठा drm_ioctl_desc - DRM driver ioctl entry
 * @cmd: ioctl command number, without flags
 * @flags: a biपंचांगask of &क्रमागत drm_ioctl_flags
 * @func: handler क्रम this ioctl
 * @name: user-पढ़ोable name क्रम debug output
 *
 * For convenience it's easier to create these using the DRM_IOCTL_DEF_DRV()
 * macro.
 */
काष्ठा drm_ioctl_desc अणु
	अचिन्हित पूर्णांक cmd;
	क्रमागत drm_ioctl_flags flags;
	drm_ioctl_t *func;
	स्थिर अक्षर *name;
पूर्ण;

/**
 * DRM_IOCTL_DEF_DRV() - helper macro to fill out a &काष्ठा drm_ioctl_desc
 * @ioctl: ioctl command suffix
 * @_func: handler क्रम the ioctl
 * @_flags: a biपंचांगask of &क्रमागत drm_ioctl_flags
 *
 * Small helper macro to create a &काष्ठा drm_ioctl_desc entry. The ioctl
 * command number is स्थिरructed by prepending ``DRM_IOCTL\_`` and passing that
 * to DRM_IOCTL_NR().
 */
#घोषणा DRM_IOCTL_DEF_DRV(ioctl, _func, _flags)				\
	[DRM_IOCTL_NR(DRM_IOCTL_##ioctl) - DRM_COMMAND_BASE] = अणु	\
		.cmd = DRM_IOCTL_##ioctl,				\
		.func = _func,						\
		.flags = _flags,					\
		.name = #ioctl						\
	पूर्ण

पूर्णांक drm_ioctl_permit(u32 flags, काष्ठा drm_file *file_priv);
दीर्घ drm_ioctl(काष्ठा file *filp, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg);
दीर्घ drm_ioctl_kernel(काष्ठा file *, drm_ioctl_t, व्योम *, u32);
#अगर_घोषित CONFIG_COMPAT
दीर्घ drm_compat_ioctl(काष्ठा file *filp, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg);
#अन्यथा
/* Let drm_compat_ioctl be asचिन्हित to .compat_ioctl unconditionally */
#घोषणा drm_compat_ioctl शून्य
#पूर्ण_अगर
bool drm_ioctl_flags(अचिन्हित पूर्णांक nr, अचिन्हित पूर्णांक *flags);

पूर्णांक drm_noop(काष्ठा drm_device *dev, व्योम *data,
	     काष्ठा drm_file *file_priv);
पूर्णांक drm_invalid_op(काष्ठा drm_device *dev, व्योम *data,
		   काष्ठा drm_file *file_priv);

#पूर्ण_अगर /* _DRM_IOCTL_H_ */
