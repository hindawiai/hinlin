<शैली गुरु>
/*
 * Copyright 2005 Stephane Marchesin.
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
 * VA LINUX SYSTEMS AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#अगर_अघोषित __NOUVEAU_DRM_H__
#घोषणा __NOUVEAU_DRM_H__

#घोषणा DRM_NOUVEAU_EVENT_NVIF                                       0x80000000

#समावेश "drm.h"

#अगर defined(__cplusplus)
बाह्य "C" अणु
#पूर्ण_अगर

#घोषणा NOUVEAU_GEM_DOMAIN_CPU       (1 << 0)
#घोषणा NOUVEAU_GEM_DOMAIN_VRAM      (1 << 1)
#घोषणा NOUVEAU_GEM_DOMAIN_GART      (1 << 2)
#घोषणा NOUVEAU_GEM_DOMAIN_MAPPABLE  (1 << 3)
#घोषणा NOUVEAU_GEM_DOMAIN_COHERENT  (1 << 4)

#घोषणा NOUVEAU_GEM_TILE_COMP        0x00030000 /* nv50-only */
#घोषणा NOUVEAU_GEM_TILE_LAYOUT_MASK 0x0000ff00
#घोषणा NOUVEAU_GEM_TILE_16BPP       0x00000001
#घोषणा NOUVEAU_GEM_TILE_32BPP       0x00000002
#घोषणा NOUVEAU_GEM_TILE_ZETA        0x00000004
#घोषणा NOUVEAU_GEM_TILE_NONCONTIG   0x00000008

काष्ठा drm_nouveau_gem_info अणु
	__u32 handle;
	__u32 करोमुख्य;
	__u64 size;
	__u64 offset;
	__u64 map_handle;
	__u32 tile_mode;
	__u32 tile_flags;
पूर्ण;

काष्ठा drm_nouveau_gem_new अणु
	काष्ठा drm_nouveau_gem_info info;
	__u32 channel_hपूर्णांक;
	__u32 align;
पूर्ण;

#घोषणा NOUVEAU_GEM_MAX_BUFFERS 1024
काष्ठा drm_nouveau_gem_pushbuf_bo_presumed अणु
	__u32 valid;
	__u32 करोमुख्य;
	__u64 offset;
पूर्ण;

काष्ठा drm_nouveau_gem_pushbuf_bo अणु
	__u64 user_priv;
	__u32 handle;
	__u32 पढ़ो_करोमुख्यs;
	__u32 ग_लिखो_करोमुख्यs;
	__u32 valid_करोमुख्यs;
	काष्ठा drm_nouveau_gem_pushbuf_bo_presumed presumed;
पूर्ण;

#घोषणा NOUVEAU_GEM_RELOC_LOW  (1 << 0)
#घोषणा NOUVEAU_GEM_RELOC_HIGH (1 << 1)
#घोषणा NOUVEAU_GEM_RELOC_OR   (1 << 2)
#घोषणा NOUVEAU_GEM_MAX_RELOCS 1024
काष्ठा drm_nouveau_gem_pushbuf_reloc अणु
	__u32 reloc_bo_index;
	__u32 reloc_bo_offset;
	__u32 bo_index;
	__u32 flags;
	__u32 data;
	__u32 vor;
	__u32 tor;
पूर्ण;

#घोषणा NOUVEAU_GEM_MAX_PUSH 512
काष्ठा drm_nouveau_gem_pushbuf_push अणु
	__u32 bo_index;
	__u32 pad;
	__u64 offset;
	__u64 length;
पूर्ण;

काष्ठा drm_nouveau_gem_pushbuf अणु
	__u32 channel;
	__u32 nr_buffers;
	__u64 buffers;
	__u32 nr_relocs;
	__u32 nr_push;
	__u64 relocs;
	__u64 push;
	__u32 suffix0;
	__u32 suffix1;
#घोषणा NOUVEAU_GEM_PUSHBUF_SYNC                                    (1ULL << 0)
	__u64 vram_available;
	__u64 gart_available;
पूर्ण;

#घोषणा NOUVEAU_GEM_CPU_PREP_NOWAIT                                  0x00000001
#घोषणा NOUVEAU_GEM_CPU_PREP_WRITE                                   0x00000004
काष्ठा drm_nouveau_gem_cpu_prep अणु
	__u32 handle;
	__u32 flags;
पूर्ण;

काष्ठा drm_nouveau_gem_cpu_fini अणु
	__u32 handle;
पूर्ण;

#घोषणा DRM_NOUVEAU_GETPARAM           0x00 /* deprecated */
#घोषणा DRM_NOUVEAU_SETPARAM           0x01 /* deprecated */
#घोषणा DRM_NOUVEAU_CHANNEL_ALLOC      0x02 /* deprecated */
#घोषणा DRM_NOUVEAU_CHANNEL_FREE       0x03 /* deprecated */
#घोषणा DRM_NOUVEAU_GROBJ_ALLOC        0x04 /* deprecated */
#घोषणा DRM_NOUVEAU_NOTIFIEROBJ_ALLOC  0x05 /* deprecated */
#घोषणा DRM_NOUVEAU_GPUOBJ_FREE        0x06 /* deprecated */
#घोषणा DRM_NOUVEAU_NVIF               0x07
#घोषणा DRM_NOUVEAU_SVM_INIT           0x08
#घोषणा DRM_NOUVEAU_SVM_BIND           0x09
#घोषणा DRM_NOUVEAU_GEM_NEW            0x40
#घोषणा DRM_NOUVEAU_GEM_PUSHBUF        0x41
#घोषणा DRM_NOUVEAU_GEM_CPU_PREP       0x42
#घोषणा DRM_NOUVEAU_GEM_CPU_FINI       0x43
#घोषणा DRM_NOUVEAU_GEM_INFO           0x44

काष्ठा drm_nouveau_svm_init अणु
	__u64 unmanaged_addr;
	__u64 unmanaged_size;
पूर्ण;

काष्ठा drm_nouveau_svm_bind अणु
	__u64 header;
	__u64 बहु_शुरू;
	__u64 बहु_पूर्ण;
	__u64 npages;
	__u64 stride;
	__u64 result;
	__u64 reserved0;
	__u64 reserved1;
पूर्ण;

#घोषणा NOUVEAU_SVM_BIND_COMMAND_SHIFT          0
#घोषणा NOUVEAU_SVM_BIND_COMMAND_BITS           8
#घोषणा NOUVEAU_SVM_BIND_COMMAND_MASK           ((1 << 8) - 1)
#घोषणा NOUVEAU_SVM_BIND_PRIORITY_SHIFT         8
#घोषणा NOUVEAU_SVM_BIND_PRIORITY_BITS          8
#घोषणा NOUVEAU_SVM_BIND_PRIORITY_MASK          ((1 << 8) - 1)
#घोषणा NOUVEAU_SVM_BIND_TARGET_SHIFT           16
#घोषणा NOUVEAU_SVM_BIND_TARGET_BITS            32
#घोषणा NOUVEAU_SVM_BIND_TARGET_MASK            0xffffffff

/*
 * Below is use to validate ioctl argument, userspace can also use it to make
 * sure that no bit are set beyond known fields क्रम a given kernel version.
 */
#घोषणा NOUVEAU_SVM_BIND_VALID_BITS     48
#घोषणा NOUVEAU_SVM_BIND_VALID_MASK     ((1ULL << NOUVEAU_SVM_BIND_VALID_BITS) - 1)


/*
 * NOUVEAU_BIND_COMMAND__MIGRATE: synchronous migrate to target memory.
 * result: number of page successfuly migrate to the target memory.
 */
#घोषणा NOUVEAU_SVM_BIND_COMMAND__MIGRATE               0

/*
 * NOUVEAU_SVM_BIND_HEADER_TARGET__GPU_VRAM: target the GPU VRAM memory.
 */
#घोषणा NOUVEAU_SVM_BIND_TARGET__GPU_VRAM               (1UL << 31)


#घोषणा DRM_IOCTL_NOUVEAU_SVM_INIT           DRM_IOWR(DRM_COMMAND_BASE + DRM_NOUVEAU_SVM_INIT, काष्ठा drm_nouveau_svm_init)
#घोषणा DRM_IOCTL_NOUVEAU_SVM_BIND           DRM_IOWR(DRM_COMMAND_BASE + DRM_NOUVEAU_SVM_BIND, काष्ठा drm_nouveau_svm_bind)

#घोषणा DRM_IOCTL_NOUVEAU_GEM_NEW            DRM_IOWR(DRM_COMMAND_BASE + DRM_NOUVEAU_GEM_NEW, काष्ठा drm_nouveau_gem_new)
#घोषणा DRM_IOCTL_NOUVEAU_GEM_PUSHBUF        DRM_IOWR(DRM_COMMAND_BASE + DRM_NOUVEAU_GEM_PUSHBUF, काष्ठा drm_nouveau_gem_pushbuf)
#घोषणा DRM_IOCTL_NOUVEAU_GEM_CPU_PREP       DRM_IOW (DRM_COMMAND_BASE + DRM_NOUVEAU_GEM_CPU_PREP, काष्ठा drm_nouveau_gem_cpu_prep)
#घोषणा DRM_IOCTL_NOUVEAU_GEM_CPU_FINI       DRM_IOW (DRM_COMMAND_BASE + DRM_NOUVEAU_GEM_CPU_FINI, काष्ठा drm_nouveau_gem_cpu_fini)
#घोषणा DRM_IOCTL_NOUVEAU_GEM_INFO           DRM_IOWR(DRM_COMMAND_BASE + DRM_NOUVEAU_GEM_INFO, काष्ठा drm_nouveau_gem_info)

#अगर defined(__cplusplus)
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* __NOUVEAU_DRM_H__ */
