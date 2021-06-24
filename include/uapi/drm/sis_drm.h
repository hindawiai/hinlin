<शैली गुरु>
/* sis_drv.h -- Private header क्रम sis driver -*- linux-c -*- */
/*
 * Copyright 2005 Eric Anholt
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
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */

#अगर_अघोषित __SIS_DRM_H__
#घोषणा __SIS_DRM_H__

#समावेश "drm.h"

#अगर defined(__cplusplus)
बाह्य "C" अणु
#पूर्ण_अगर

/* SiS specअगरic ioctls */
#घोषणा NOT_USED_0_3
#घोषणा DRM_SIS_FB_ALLOC	0x04
#घोषणा DRM_SIS_FB_FREE	        0x05
#घोषणा NOT_USED_6_12
#घोषणा DRM_SIS_AGP_INIT	0x13
#घोषणा DRM_SIS_AGP_ALLOC	0x14
#घोषणा DRM_SIS_AGP_FREE	0x15
#घोषणा DRM_SIS_FB_INIT	        0x16

#घोषणा DRM_IOCTL_SIS_FB_ALLOC		DRM_IOWR(DRM_COMMAND_BASE + DRM_SIS_FB_ALLOC, drm_sis_mem_t)
#घोषणा DRM_IOCTL_SIS_FB_FREE		DRM_IOW( DRM_COMMAND_BASE + DRM_SIS_FB_FREE, drm_sis_mem_t)
#घोषणा DRM_IOCTL_SIS_AGP_INIT		DRM_IOWR(DRM_COMMAND_BASE + DRM_SIS_AGP_INIT, drm_sis_agp_t)
#घोषणा DRM_IOCTL_SIS_AGP_ALLOC		DRM_IOWR(DRM_COMMAND_BASE + DRM_SIS_AGP_ALLOC, drm_sis_mem_t)
#घोषणा DRM_IOCTL_SIS_AGP_FREE		DRM_IOW( DRM_COMMAND_BASE + DRM_SIS_AGP_FREE, drm_sis_mem_t)
#घोषणा DRM_IOCTL_SIS_FB_INIT		DRM_IOW( DRM_COMMAND_BASE + DRM_SIS_FB_INIT, drm_sis_fb_t)
/*
#घोषणा DRM_IOCTL_SIS_FLIP		DRM_IOW( 0x48, drm_sis_flip_t)
#घोषणा DRM_IOCTL_SIS_FLIP_INIT		DRM_IO(  0x49)
#घोषणा DRM_IOCTL_SIS_FLIP_FINAL	DRM_IO(  0x50)
*/

प्रकार काष्ठा अणु
	पूर्णांक context;
	अचिन्हित दीर्घ offset;
	अचिन्हित दीर्घ size;
	अचिन्हित दीर्घ मुक्त;
पूर्ण drm_sis_mem_t;

प्रकार काष्ठा अणु
	अचिन्हित दीर्घ offset, size;
पूर्ण drm_sis_agp_t;

प्रकार काष्ठा अणु
	अचिन्हित दीर्घ offset, size;
पूर्ण drm_sis_fb_t;

#अगर defined(__cplusplus)
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर				/* __SIS_DRM_H__ */
