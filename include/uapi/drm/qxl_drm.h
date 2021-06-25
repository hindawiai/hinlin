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
#अगर_अघोषित QXL_DRM_H
#घोषणा QXL_DRM_H

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

#घोषणा QXL_GEM_DOMAIN_CPU 0
#घोषणा QXL_GEM_DOMAIN_VRAM 1
#घोषणा QXL_GEM_DOMAIN_SURFACE 2

#घोषणा DRM_QXL_ALLOC       0x00
#घोषणा DRM_QXL_MAP         0x01
#घोषणा DRM_QXL_EXECBUFFER  0x02
#घोषणा DRM_QXL_UPDATE_AREA 0x03
#घोषणा DRM_QXL_GETPARAM    0x04
#घोषणा DRM_QXL_CLIENTCAP   0x05

#घोषणा DRM_QXL_ALLOC_SURF  0x06

काष्ठा drm_qxl_alloc अणु
	__u32 size;
	__u32 handle; /* 0 is an invalid handle */
पूर्ण;

काष्ठा drm_qxl_map अणु
	__u64 offset; /* use क्रम mmap प्रणाली call */
	__u32 handle;
	__u32 pad;
पूर्ण;

/*
 * dest is the bo we are writing the relocation पूर्णांकo
 * src is bo we are relocating.
 * *(dest_handle.base_addr + dest_offset) = physical_address(src_handle.addr +
 * src_offset)
 */
#घोषणा QXL_RELOC_TYPE_BO 1
#घोषणा QXL_RELOC_TYPE_SURF 2

काष्ठा drm_qxl_reloc अणु
	__u64 src_offset; /* offset पूर्णांकo src_handle or src buffer */
	__u64 dst_offset; /* offset in dest handle */
	__u32 src_handle; /* dest handle to compute address from */
	__u32 dst_handle; /* 0 अगर to command buffer */
	__u32 reloc_type;
	__u32 pad;
पूर्ण;

काष्ठा drm_qxl_command अणु
	__u64		command; /* व्योम* */
	__u64		relocs; /* काष्ठा drm_qxl_reloc* */
	__u32		type;
	__u32		command_size;
	__u32		relocs_num;
	__u32                pad;
पूर्ण;

काष्ठा drm_qxl_execbuffer अणु
	__u32		flags;		/* क्रम future use */
	__u32		commands_num;
	__u64		commands;	/* काष्ठा drm_qxl_command* */
पूर्ण;

काष्ठा drm_qxl_update_area अणु
	__u32 handle;
	__u32 top;
	__u32 left;
	__u32 bottom;
	__u32 right;
	__u32 pad;
पूर्ण;

#घोषणा QXL_PARAM_NUM_SURFACES 1 /* rom->n_surfaces */
#घोषणा QXL_PARAM_MAX_RELOCS 2
काष्ठा drm_qxl_getparam अणु
	__u64 param;
	__u64 value;
पूर्ण;

/* these are one bit values */
काष्ठा drm_qxl_clientcap अणु
	__u32 index;
	__u32 pad;
पूर्ण;

काष्ठा drm_qxl_alloc_surf अणु
	__u32 क्रमmat;
	__u32 width;
	__u32 height;
	__s32 stride;
	__u32 handle;
	__u32 pad;
पूर्ण;

#घोषणा DRM_IOCTL_QXL_ALLOC \
	DRM_IOWR(DRM_COMMAND_BASE + DRM_QXL_ALLOC, काष्ठा drm_qxl_alloc)

#घोषणा DRM_IOCTL_QXL_MAP \
	DRM_IOWR(DRM_COMMAND_BASE + DRM_QXL_MAP, काष्ठा drm_qxl_map)

#घोषणा DRM_IOCTL_QXL_EXECBUFFER \
	DRM_IOW(DRM_COMMAND_BASE + DRM_QXL_EXECBUFFER,\
		काष्ठा drm_qxl_execbuffer)

#घोषणा DRM_IOCTL_QXL_UPDATE_AREA \
	DRM_IOW(DRM_COMMAND_BASE + DRM_QXL_UPDATE_AREA,\
		काष्ठा drm_qxl_update_area)

#घोषणा DRM_IOCTL_QXL_GETPARAM \
	DRM_IOWR(DRM_COMMAND_BASE + DRM_QXL_GETPARAM,\
		काष्ठा drm_qxl_getparam)

#घोषणा DRM_IOCTL_QXL_CLIENTCAP \
	DRM_IOW(DRM_COMMAND_BASE + DRM_QXL_CLIENTCAP,\
		काष्ठा drm_qxl_clientcap)

#घोषणा DRM_IOCTL_QXL_ALLOC_SURF \
	DRM_IOWR(DRM_COMMAND_BASE + DRM_QXL_ALLOC_SURF,\
		काष्ठा drm_qxl_alloc_surf)

#अगर defined(__cplusplus)
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर
