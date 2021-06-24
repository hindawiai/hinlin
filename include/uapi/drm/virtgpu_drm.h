<शैली गुरु>
/*
 * Copyright 2013 Red Hat
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
 * THE AUTHORS AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */
#अगर_अघोषित VIRTGPU_DRM_H
#घोषणा VIRTGPU_DRM_H

#समावेश "drm.h"

#अगर defined(__cplusplus)
बाह्य "C" अणु
#पूर्ण_अगर

/* Please note that modअगरications to all काष्ठाs defined here are
 * subject to backwards-compatibility स्थिरraपूर्णांकs.
 *
 * Do not use poपूर्णांकers, use __u64 instead क्रम 32 bit / 64 bit user/kernel
 * compatibility Keep fields aligned to their size
 */

#घोषणा DRM_VIRTGPU_MAP         0x01
#घोषणा DRM_VIRTGPU_EXECBUFFER  0x02
#घोषणा DRM_VIRTGPU_GETPARAM    0x03
#घोषणा DRM_VIRTGPU_RESOURCE_CREATE 0x04
#घोषणा DRM_VIRTGPU_RESOURCE_INFO     0x05
#घोषणा DRM_VIRTGPU_TRANSFER_FROM_HOST 0x06
#घोषणा DRM_VIRTGPU_TRANSFER_TO_HOST 0x07
#घोषणा DRM_VIRTGPU_WAIT     0x08
#घोषणा DRM_VIRTGPU_GET_CAPS  0x09
#घोषणा DRM_VIRTGPU_RESOURCE_CREATE_BLOB 0x0a

#घोषणा VIRTGPU_EXECBUF_FENCE_FD_IN	0x01
#घोषणा VIRTGPU_EXECBUF_FENCE_FD_OUT	0x02
#घोषणा VIRTGPU_EXECBUF_FLAGS  (\
		VIRTGPU_EXECBUF_FENCE_FD_IN |\
		VIRTGPU_EXECBUF_FENCE_FD_OUT |\
		0)

काष्ठा drm_virtgpu_map अणु
	__u64 offset; /* use क्रम mmap प्रणाली call */
	__u32 handle;
	__u32 pad;
पूर्ण;

काष्ठा drm_virtgpu_execbuffer अणु
	__u32 flags;
	__u32 size;
	__u64 command; /* व्योम* */
	__u64 bo_handles;
	__u32 num_bo_handles;
	__s32 fence_fd; /* in/out fence fd (see VIRTGPU_EXECBUF_FENCE_FD_IN/OUT) */
पूर्ण;

#घोषणा VIRTGPU_PARAM_3D_FEATURES 1 /* करो we have 3D features in the hw */
#घोषणा VIRTGPU_PARAM_CAPSET_QUERY_FIX 2 /* करो we have the capset fix */
#घोषणा VIRTGPU_PARAM_RESOURCE_BLOB 3 /* DRM_VIRTGPU_RESOURCE_CREATE_BLOB */
#घोषणा VIRTGPU_PARAM_HOST_VISIBLE 4 /* Host blob resources are mappable */
#घोषणा VIRTGPU_PARAM_CROSS_DEVICE 5 /* Cross virtio-device resource sharing  */

काष्ठा drm_virtgpu_getparam अणु
	__u64 param;
	__u64 value;
पूर्ण;

/* NO_BO flags? NO resource flag? */
/* resource flag क्रम y_0_top */
काष्ठा drm_virtgpu_resource_create अणु
	__u32 target;
	__u32 क्रमmat;
	__u32 bind;
	__u32 width;
	__u32 height;
	__u32 depth;
	__u32 array_size;
	__u32 last_level;
	__u32 nr_samples;
	__u32 flags;
	__u32 bo_handle; /* अगर this is set - recreate a new resource attached to this bo ? */
	__u32 res_handle;  /* वापसed by kernel */
	__u32 size;        /* validate transfer in the host */
	__u32 stride;      /* validate transfer in the host */
पूर्ण;

काष्ठा drm_virtgpu_resource_info अणु
	__u32 bo_handle;
	__u32 res_handle;
	__u32 size;
	__u32 blob_mem;
पूर्ण;

काष्ठा drm_virtgpu_3d_box अणु
	__u32 x;
	__u32 y;
	__u32 z;
	__u32 w;
	__u32 h;
	__u32 d;
पूर्ण;

काष्ठा drm_virtgpu_3d_transfer_to_host अणु
	__u32 bo_handle;
	काष्ठा drm_virtgpu_3d_box box;
	__u32 level;
	__u32 offset;
	__u32 stride;
	__u32 layer_stride;
पूर्ण;

काष्ठा drm_virtgpu_3d_transfer_from_host अणु
	__u32 bo_handle;
	काष्ठा drm_virtgpu_3d_box box;
	__u32 level;
	__u32 offset;
	__u32 stride;
	__u32 layer_stride;
पूर्ण;

#घोषणा VIRTGPU_WAIT_NOWAIT 1 /* like it */
काष्ठा drm_virtgpu_3d_रुको अणु
	__u32 handle; /* 0 is an invalid handle */
	__u32 flags;
पूर्ण;

काष्ठा drm_virtgpu_get_caps अणु
	__u32 cap_set_id;
	__u32 cap_set_ver;
	__u64 addr;
	__u32 size;
	__u32 pad;
पूर्ण;

काष्ठा drm_virtgpu_resource_create_blob अणु
#घोषणा VIRTGPU_BLOB_MEM_GUEST             0x0001
#घोषणा VIRTGPU_BLOB_MEM_HOST3D            0x0002
#घोषणा VIRTGPU_BLOB_MEM_HOST3D_GUEST      0x0003

#घोषणा VIRTGPU_BLOB_FLAG_USE_MAPPABLE     0x0001
#घोषणा VIRTGPU_BLOB_FLAG_USE_SHAREABLE    0x0002
#घोषणा VIRTGPU_BLOB_FLAG_USE_CROSS_DEVICE 0x0004
	/* zero is invalid blob_mem */
	__u32 blob_mem;
	__u32 blob_flags;
	__u32 bo_handle;
	__u32 res_handle;
	__u64 size;

	/*
	 * क्रम 3D contexts with VIRTGPU_BLOB_MEM_HOST3D_GUEST and
	 * VIRTGPU_BLOB_MEM_HOST3D otherwise, must be zero.
	 */
	__u32 pad;
	__u32 cmd_size;
	__u64 cmd;
	__u64 blob_id;
पूर्ण;

#घोषणा DRM_IOCTL_VIRTGPU_MAP \
	DRM_IOWR(DRM_COMMAND_BASE + DRM_VIRTGPU_MAP, काष्ठा drm_virtgpu_map)

#घोषणा DRM_IOCTL_VIRTGPU_EXECBUFFER \
	DRM_IOWR(DRM_COMMAND_BASE + DRM_VIRTGPU_EXECBUFFER,\
		काष्ठा drm_virtgpu_execbuffer)

#घोषणा DRM_IOCTL_VIRTGPU_GETPARAM \
	DRM_IOWR(DRM_COMMAND_BASE + DRM_VIRTGPU_GETPARAM,\
		काष्ठा drm_virtgpu_getparam)

#घोषणा DRM_IOCTL_VIRTGPU_RESOURCE_CREATE			\
	DRM_IOWR(DRM_COMMAND_BASE + DRM_VIRTGPU_RESOURCE_CREATE,	\
		काष्ठा drm_virtgpu_resource_create)

#घोषणा DRM_IOCTL_VIRTGPU_RESOURCE_INFO \
	DRM_IOWR(DRM_COMMAND_BASE + DRM_VIRTGPU_RESOURCE_INFO, \
		 काष्ठा drm_virtgpu_resource_info)

#घोषणा DRM_IOCTL_VIRTGPU_TRANSFER_FROM_HOST \
	DRM_IOWR(DRM_COMMAND_BASE + DRM_VIRTGPU_TRANSFER_FROM_HOST,	\
		काष्ठा drm_virtgpu_3d_transfer_from_host)

#घोषणा DRM_IOCTL_VIRTGPU_TRANSFER_TO_HOST \
	DRM_IOWR(DRM_COMMAND_BASE + DRM_VIRTGPU_TRANSFER_TO_HOST,	\
		काष्ठा drm_virtgpu_3d_transfer_to_host)

#घोषणा DRM_IOCTL_VIRTGPU_WAIT				\
	DRM_IOWR(DRM_COMMAND_BASE + DRM_VIRTGPU_WAIT,	\
		काष्ठा drm_virtgpu_3d_रुको)

#घोषणा DRM_IOCTL_VIRTGPU_GET_CAPS \
	DRM_IOWR(DRM_COMMAND_BASE + DRM_VIRTGPU_GET_CAPS, \
	काष्ठा drm_virtgpu_get_caps)

#घोषणा DRM_IOCTL_VIRTGPU_RESOURCE_CREATE_BLOB				\
	DRM_IOWR(DRM_COMMAND_BASE + DRM_VIRTGPU_RESOURCE_CREATE_BLOB,	\
		काष्ठा drm_virtgpu_resource_create_blob)

#अगर defined(__cplusplus)
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर
