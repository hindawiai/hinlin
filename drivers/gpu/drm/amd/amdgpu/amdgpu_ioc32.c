<शैली गुरु>
/**
 * \पile amdgpu_ioc32.c
 *
 * 32-bit ioctl compatibility routines क्रम the AMDGPU DRM.
 *
 * \चuthor Paul Mackerras <paulus@samba.org>
 *
 * Copyright (C) Paul Mackerras 2005
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

#समावेश <drm/amdgpu_drm.h>
#समावेश <drm/drm_ioctl.h>

#समावेश "amdgpu_drv.h"

दीर्घ amdgpu_kms_compat_ioctl(काष्ठा file *filp, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	अचिन्हित पूर्णांक nr = DRM_IOCTL_NR(cmd);
	पूर्णांक ret;

	अगर (nr < DRM_COMMAND_BASE)
		वापस drm_compat_ioctl(filp, cmd, arg);

	ret = amdgpu_drm_ioctl(filp, cmd, arg);

	वापस ret;
पूर्ण
