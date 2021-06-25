<शैली गुरु>
/*
 * Copyright (C) 2013 Red Hat
 * Author: Rob Clark <robdclark@gmail.com>
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
 */

#अगर_अघोषित __MSM_DRM_H__
#घोषणा __MSM_DRM_H__

#समावेश "drm.h"

#अगर defined(__cplusplus)
बाह्य "C" अणु
#पूर्ण_अगर

/* Please note that modअगरications to all काष्ठाs defined here are
 * subject to backwards-compatibility स्थिरraपूर्णांकs:
 *  1) Do not use poपूर्णांकers, use __u64 instead क्रम 32 bit / 64 bit
 *     user/kernel compatibility
 *  2) Keep fields aligned to their size
 *  3) Because of how drm_ioctl() works, we can add new fields at
 *     the end of an ioctl अगर some care is taken: drm_ioctl() will
 *     zero out the new fields at the tail of the ioctl, so a zero
 *     value should have a backwards compatible meaning.  And क्रम
 *     output params, userspace won't see the newly added output
 *     fields.. so that has to be somehow ok.
 */

#घोषणा MSM_PIPE_NONE        0x00
#घोषणा MSM_PIPE_2D0         0x01
#घोषणा MSM_PIPE_2D1         0x02
#घोषणा MSM_PIPE_3D0         0x10

/* The pipe-id just uses the lower bits, so can be OR'd with flags in
 * the upper 16 bits (which could be extended further, अगर needed, maybe
 * we extend/overload the pipe-id some day to deal with multiple rings,
 * but even then I करोn't think we need the full lower 16 bits).
 */
#घोषणा MSM_PIPE_ID_MASK     0xffff
#घोषणा MSM_PIPE_ID(x)       ((x) & MSM_PIPE_ID_MASK)
#घोषणा MSM_PIPE_FLAGS(x)    ((x) & ~MSM_PIPE_ID_MASK)

/* समयouts are specअगरied in घड़ी-monotonic असलolute बार (to simplअगरy
 * restarting पूर्णांकerrupted ioctls).  The following काष्ठा is logically the
 * same as 'struct timespec' but 32/64b ABI safe.
 */
काष्ठा drm_msm_बारpec अणु
	__s64 tv_sec;          /* seconds */
	__s64 tv_nsec;         /* nanoseconds */
पूर्ण;

#घोषणा MSM_PARAM_GPU_ID     0x01
#घोषणा MSM_PARAM_GMEM_SIZE  0x02
#घोषणा MSM_PARAM_CHIP_ID    0x03
#घोषणा MSM_PARAM_MAX_FREQ   0x04
#घोषणा MSM_PARAM_TIMESTAMP  0x05
#घोषणा MSM_PARAM_GMEM_BASE  0x06
#घोषणा MSM_PARAM_NR_RINGS   0x07
#घोषणा MSM_PARAM_PP_PGTABLE 0x08  /* => 1 क्रम per-process pagetables, अन्यथा 0 */
#घोषणा MSM_PARAM_FAULTS     0x09
#घोषणा MSM_PARAM_SUSPENDS   0x0a

काष्ठा drm_msm_param अणु
	__u32 pipe;           /* in, MSM_PIPE_x */
	__u32 param;          /* in, MSM_PARAM_x */
	__u64 value;          /* out (get_param) or in (set_param) */
पूर्ण;

/*
 * GEM buffers:
 */

#घोषणा MSM_BO_SCANOUT       0x00000001     /* scanout capable */
#घोषणा MSM_BO_GPU_READONLY  0x00000002
#घोषणा MSM_BO_CACHE_MASK    0x000f0000
/* cache modes */
#घोषणा MSM_BO_CACHED        0x00010000
#घोषणा MSM_BO_WC            0x00020000
#घोषणा MSM_BO_UNCACHED      0x00040000

#घोषणा MSM_BO_FLAGS         (MSM_BO_SCANOUT | \
                              MSM_BO_GPU_READONLY | \
                              MSM_BO_CACHED | \
                              MSM_BO_WC | \
                              MSM_BO_UNCACHED)

काष्ठा drm_msm_gem_new अणु
	__u64 size;           /* in */
	__u32 flags;          /* in, mask of MSM_BO_x */
	__u32 handle;         /* out */
पूर्ण;

/* Get or set GEM buffer info.  The requested value can be passed
 * directly in 'value', or for data larger than 64b 'value' is a
 * poपूर्णांकer to userspace buffer, with 'len' specअगरying the number of
 * bytes copied पूर्णांकo that buffer.  For info वापसed by poपूर्णांकer,
 * calling the GEM_INFO ioctl with null 'value' will वापस the
 * required buffer size in 'len'
 */
#घोषणा MSM_INFO_GET_OFFSET	0x00   /* get mmap() offset, वापसed by value */
#घोषणा MSM_INFO_GET_IOVA	0x01   /* get iova, वापसed by value */
#घोषणा MSM_INFO_SET_NAME	0x02   /* set the debug name (by poपूर्णांकer) */
#घोषणा MSM_INFO_GET_NAME	0x03   /* get debug name, वापसed by poपूर्णांकer */

काष्ठा drm_msm_gem_info अणु
	__u32 handle;         /* in */
	__u32 info;           /* in - one of MSM_INFO_* */
	__u64 value;          /* in or out */
	__u32 len;            /* in or out */
	__u32 pad;
पूर्ण;

#घोषणा MSM_PREP_READ        0x01
#घोषणा MSM_PREP_WRITE       0x02
#घोषणा MSM_PREP_NOSYNC      0x04

#घोषणा MSM_PREP_FLAGS       (MSM_PREP_READ | MSM_PREP_WRITE | MSM_PREP_NOSYNC)

काष्ठा drm_msm_gem_cpu_prep अणु
	__u32 handle;         /* in */
	__u32 op;             /* in, mask of MSM_PREP_x */
	काष्ठा drm_msm_बारpec समयout;   /* in */
पूर्ण;

काष्ठा drm_msm_gem_cpu_fini अणु
	__u32 handle;         /* in */
पूर्ण;

/*
 * Cmdstream Submission:
 */

/* The value written पूर्णांकo the cmdstream is logically:
 *
 *   ((relocbuf->gpuaddr + reloc_offset) << shअगरt) | or
 *
 * When we have GPU's w/ >32bit ptrs, it should be possible to deal
 * with this by emit'ing two reloc entries with appropriate shअगरt
 * values.  Or a new MSM_SUBMIT_CMD_x type would also be an option.
 *
 * NOTE that reloc's must be sorted by order of increasing submit_offset,
 * otherwise EINVAL.
 */
काष्ठा drm_msm_gem_submit_reloc अणु
	__u32 submit_offset;  /* in, offset from submit_bo */
	__u32 or;             /* in, value OR'd with result */
	__s32 shअगरt;          /* in, amount of left shअगरt (can be negative) */
	__u32 reloc_idx;      /* in, index of reloc_bo buffer */
	__u64 reloc_offset;   /* in, offset from start of reloc_bo */
पूर्ण;

/* submit-types:
 *   BUF - this cmd buffer is executed normally.
 *   IB_TARGET_BUF - this cmd buffer is an IB target.  Reloc's are
 *      processed normally, but the kernel करोes not setup an IB to
 *      this buffer in the first-level ringbuffer
 *   CTX_RESTORE_BUF - only executed अगर there has been a GPU context
 *      चयन since the last SUBMIT ioctl
 */
#घोषणा MSM_SUBMIT_CMD_BUF             0x0001
#घोषणा MSM_SUBMIT_CMD_IB_TARGET_BUF   0x0002
#घोषणा MSM_SUBMIT_CMD_CTX_RESTORE_BUF 0x0003
काष्ठा drm_msm_gem_submit_cmd अणु
	__u32 type;           /* in, one of MSM_SUBMIT_CMD_x */
	__u32 submit_idx;     /* in, index of submit_bo cmdstream buffer */
	__u32 submit_offset;  /* in, offset पूर्णांकo submit_bo */
	__u32 size;           /* in, cmdstream size */
	__u32 pad;
	__u32 nr_relocs;      /* in, number of submit_reloc's */
	__u64 relocs;         /* in, ptr to array of submit_reloc's */
पूर्ण;

/* Each buffer referenced अन्यथाwhere in the cmdstream submit (ie. the
 * cmdstream buffer(s) themselves or reloc entries) has one (and only
 * one) entry in the submit->bos[] table.
 *
 * As a optimization, the current buffer (gpu भव address) can be
 * passed back through the 'presumed' field.  If on a subsequent reloc,
 * userspace passes back a 'presumed' address that is still valid,
 * then patching the cmdstream क्रम this entry is skipped.  This can
 * aव्योम kernel needing to map/access the cmdstream bo in the common
 * हाल.
 */
#घोषणा MSM_SUBMIT_BO_READ             0x0001
#घोषणा MSM_SUBMIT_BO_WRITE            0x0002
#घोषणा MSM_SUBMIT_BO_DUMP             0x0004

#घोषणा MSM_SUBMIT_BO_FLAGS            (MSM_SUBMIT_BO_READ | \
					MSM_SUBMIT_BO_WRITE | \
					MSM_SUBMIT_BO_DUMP)

काष्ठा drm_msm_gem_submit_bo अणु
	__u32 flags;          /* in, mask of MSM_SUBMIT_BO_x */
	__u32 handle;         /* in, GEM handle */
	__u64 presumed;       /* in/out, presumed buffer address */
पूर्ण;

/* Valid submit ioctl flags: */
#घोषणा MSM_SUBMIT_NO_IMPLICIT   0x80000000 /* disable implicit sync */
#घोषणा MSM_SUBMIT_FENCE_FD_IN   0x40000000 /* enable input fence_fd */
#घोषणा MSM_SUBMIT_FENCE_FD_OUT  0x20000000 /* enable output fence_fd */
#घोषणा MSM_SUBMIT_SUDO          0x10000000 /* run submitted cmds from RB */
#घोषणा MSM_SUBMIT_SYNCOBJ_IN    0x08000000 /* enable input syncobj */
#घोषणा MSM_SUBMIT_SYNCOBJ_OUT   0x04000000 /* enable output syncobj */
#घोषणा MSM_SUBMIT_FLAGS                ( \
		MSM_SUBMIT_NO_IMPLICIT   | \
		MSM_SUBMIT_FENCE_FD_IN   | \
		MSM_SUBMIT_FENCE_FD_OUT  | \
		MSM_SUBMIT_SUDO          | \
		MSM_SUBMIT_SYNCOBJ_IN    | \
		MSM_SUBMIT_SYNCOBJ_OUT   | \
		0)

#घोषणा MSM_SUBMIT_SYNCOBJ_RESET 0x00000001 /* Reset syncobj after रुको. */
#घोषणा MSM_SUBMIT_SYNCOBJ_FLAGS        ( \
		MSM_SUBMIT_SYNCOBJ_RESET | \
		0)

काष्ठा drm_msm_gem_submit_syncobj अणु
	__u32 handle;     /* in, syncobj handle. */
	__u32 flags;      /* in, from MSM_SUBMIT_SYNCOBJ_FLAGS */
	__u64 poपूर्णांक;      /* in, समयpoपूर्णांक क्रम समयline syncobjs. */
पूर्ण;

/* Each cmdstream submit consists of a table of buffers involved, and
 * one or more cmdstream buffers.  This allows क्रम conditional execution
 * (context-restore), and IB buffers needed क्रम per tile/bin draw cmds.
 */
काष्ठा drm_msm_gem_submit अणु
	__u32 flags;          /* MSM_PIPE_x | MSM_SUBMIT_x */
	__u32 fence;          /* out */
	__u32 nr_bos;         /* in, number of submit_bo's */
	__u32 nr_cmds;        /* in, number of submit_cmd's */
	__u64 bos;            /* in, ptr to array of submit_bo's */
	__u64 cmds;           /* in, ptr to array of submit_cmd's */
	__s32 fence_fd;       /* in/out fence fd (see MSM_SUBMIT_FENCE_FD_IN/OUT) */
	__u32 queueid;        /* in, submitqueue id */
	__u64 in_syncobjs;    /* in, ptr to array of drm_msm_gem_submit_syncobj */
	__u64 out_syncobjs;   /* in, ptr to array of drm_msm_gem_submit_syncobj */
	__u32 nr_in_syncobjs; /* in, number of entries in in_syncobj */
	__u32 nr_out_syncobjs; /* in, number of entries in out_syncobj. */
	__u32 syncobj_stride; /* in, stride of syncobj arrays. */
	__u32 pad;            /*in, reserved क्रम future use, always 0. */

पूर्ण;

/* The normal way to synchronize with the GPU is just to CPU_PREP on
 * a buffer अगर you need to access it from the CPU (other cmdstream
 * submission from same or other contexts, PAGE_FLIP ioctl, etc, all
 * handle the required synchronization under the hood).  This ioctl
 * मुख्यly just exists as a way to implement the gallium pipe_fence
 * APIs without requiring a dummy bo to synchronize on.
 */
काष्ठा drm_msm_रुको_fence अणु
	__u32 fence;          /* in */
	__u32 pad;
	काष्ठा drm_msm_बारpec समयout;   /* in */
	__u32 queueid;         /* in, submitqueue id */
पूर्ण;

/* madvise provides a way to tell the kernel in हाल a buffers contents
 * can be discarded under memory pressure, which is useful क्रम userspace
 * bo cache where we want to optimistically hold on to buffer allocate
 * and potential mmap, but allow the pages to be discarded under memory
 * pressure.
 *
 * Typical usage would involve madvise(DONTNEED) when buffer enters BO
 * cache, and madvise(WILLNEED) अगर trying to recycle buffer from BO cache.
 * In the WILLNEED हाल, 'retained' indicates to userspace whether the
 * backing pages still exist.
 */
#घोषणा MSM_MADV_WILLNEED 0       /* backing pages are needed, status वापसed in 'retained' */
#घोषणा MSM_MADV_DONTNEED 1       /* backing pages not needed */
#घोषणा __MSM_MADV_PURGED 2       /* पूर्णांकernal state */

काष्ठा drm_msm_gem_madvise अणु
	__u32 handle;         /* in, GEM handle */
	__u32 madv;           /* in, MSM_MADV_x */
	__u32 retained;       /* out, whether backing store still exists */
पूर्ण;

/*
 * Draw queues allow the user to set specअगरic submission parameter. Command
 * submissions specअगरy a specअगरic submitqueue to use.  ID 0 is reserved क्रम
 * backwards compatibility as a "default" submitqueue
 */

#घोषणा MSM_SUBMITQUEUE_FLAGS (0)

काष्ठा drm_msm_submitqueue अणु
	__u32 flags;   /* in, MSM_SUBMITQUEUE_x */
	__u32 prio;    /* in, Priority level */
	__u32 id;      /* out, identअगरier */
पूर्ण;

#घोषणा MSM_SUBMITQUEUE_PARAM_FAULTS   0

काष्ठा drm_msm_submitqueue_query अणु
	__u64 data;
	__u32 id;
	__u32 param;
	__u32 len;
	__u32 pad;
पूर्ण;

#घोषणा DRM_MSM_GET_PARAM              0x00
/* placeholder:
#घोषणा DRM_MSM_SET_PARAM              0x01
 */
#घोषणा DRM_MSM_GEM_NEW                0x02
#घोषणा DRM_MSM_GEM_INFO               0x03
#घोषणा DRM_MSM_GEM_CPU_PREP           0x04
#घोषणा DRM_MSM_GEM_CPU_FINI           0x05
#घोषणा DRM_MSM_GEM_SUBMIT             0x06
#घोषणा DRM_MSM_WAIT_FENCE             0x07
#घोषणा DRM_MSM_GEM_MADVISE            0x08
/* placeholder:
#घोषणा DRM_MSM_GEM_SVM_NEW            0x09
 */
#घोषणा DRM_MSM_SUBMITQUEUE_NEW        0x0A
#घोषणा DRM_MSM_SUBMITQUEUE_CLOSE      0x0B
#घोषणा DRM_MSM_SUBMITQUEUE_QUERY      0x0C

#घोषणा DRM_IOCTL_MSM_GET_PARAM        DRM_IOWR(DRM_COMMAND_BASE + DRM_MSM_GET_PARAM, काष्ठा drm_msm_param)
#घोषणा DRM_IOCTL_MSM_GEM_NEW          DRM_IOWR(DRM_COMMAND_BASE + DRM_MSM_GEM_NEW, काष्ठा drm_msm_gem_new)
#घोषणा DRM_IOCTL_MSM_GEM_INFO         DRM_IOWR(DRM_COMMAND_BASE + DRM_MSM_GEM_INFO, काष्ठा drm_msm_gem_info)
#घोषणा DRM_IOCTL_MSM_GEM_CPU_PREP     DRM_IOW (DRM_COMMAND_BASE + DRM_MSM_GEM_CPU_PREP, काष्ठा drm_msm_gem_cpu_prep)
#घोषणा DRM_IOCTL_MSM_GEM_CPU_FINI     DRM_IOW (DRM_COMMAND_BASE + DRM_MSM_GEM_CPU_FINI, काष्ठा drm_msm_gem_cpu_fini)
#घोषणा DRM_IOCTL_MSM_GEM_SUBMIT       DRM_IOWR(DRM_COMMAND_BASE + DRM_MSM_GEM_SUBMIT, काष्ठा drm_msm_gem_submit)
#घोषणा DRM_IOCTL_MSM_WAIT_FENCE       DRM_IOW (DRM_COMMAND_BASE + DRM_MSM_WAIT_FENCE, काष्ठा drm_msm_रुको_fence)
#घोषणा DRM_IOCTL_MSM_GEM_MADVISE      DRM_IOWR(DRM_COMMAND_BASE + DRM_MSM_GEM_MADVISE, काष्ठा drm_msm_gem_madvise)
#घोषणा DRM_IOCTL_MSM_SUBMITQUEUE_NEW    DRM_IOWR(DRM_COMMAND_BASE + DRM_MSM_SUBMITQUEUE_NEW, काष्ठा drm_msm_submitqueue)
#घोषणा DRM_IOCTL_MSM_SUBMITQUEUE_CLOSE  DRM_IOW (DRM_COMMAND_BASE + DRM_MSM_SUBMITQUEUE_CLOSE, __u32)
#घोषणा DRM_IOCTL_MSM_SUBMITQUEUE_QUERY  DRM_IOW (DRM_COMMAND_BASE + DRM_MSM_SUBMITQUEUE_QUERY, काष्ठा drm_msm_submitqueue_query)

#अगर defined(__cplusplus)
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* __MSM_DRM_H__ */
