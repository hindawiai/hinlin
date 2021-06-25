<शैली गुरु>
/*
 * Copyright 2016 Intel Corporation
 * All Rights Reserved.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modअगरy, merge, publish,
 * distribute, sub license, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to करो so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice (including the
 * next paragraph) shall be included in all copies or substantial portions
 * of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT.
 * IN NO EVENT SHALL TUNGSTEN GRAPHICS AND/OR ITS SUPPLIERS BE LIABLE FOR
 * ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */

#अगर_अघोषित _UAPI_VGEM_DRM_H_
#घोषणा _UAPI_VGEM_DRM_H_

#समावेश "drm.h"

#अगर defined(__cplusplus)
बाह्य "C" अणु
#पूर्ण_अगर

/* Please note that modअगरications to all काष्ठाs defined here are
 * subject to backwards-compatibility स्थिरraपूर्णांकs.
 */
#घोषणा DRM_VGEM_FENCE_ATTACH	0x1
#घोषणा DRM_VGEM_FENCE_SIGNAL	0x2

#घोषणा DRM_IOCTL_VGEM_FENCE_ATTACH	DRM_IOWR( DRM_COMMAND_BASE + DRM_VGEM_FENCE_ATTACH, काष्ठा drm_vgem_fence_attach)
#घोषणा DRM_IOCTL_VGEM_FENCE_SIGNAL	DRM_IOW( DRM_COMMAND_BASE + DRM_VGEM_FENCE_SIGNAL, काष्ठा drm_vgem_fence_संकेत)

काष्ठा drm_vgem_fence_attach अणु
	__u32 handle;
	__u32 flags;
#घोषणा VGEM_FENCE_WRITE	0x1
	__u32 out_fence;
	__u32 pad;
पूर्ण;

काष्ठा drm_vgem_fence_संकेत अणु
	__u32 fence;
	__u32 flags;
पूर्ण;

#अगर defined(__cplusplus)
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* _UAPI_VGEM_DRM_H_ */
