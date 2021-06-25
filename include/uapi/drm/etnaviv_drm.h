<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * Copyright (C) 2015 Etnaviv Project
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy it
 * under the terms of the GNU General Public License version 2 as published by
 * the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License क्रम
 * more details.
 *
 * You should have received a copy of the GNU General Public License aदीर्घ with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#अगर_अघोषित __ETNAVIV_DRM_H__
#घोषणा __ETNAVIV_DRM_H__

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

/* समयouts are specअगरied in घड़ी-monotonic असलolute बार (to simplअगरy
 * restarting पूर्णांकerrupted ioctls).  The following काष्ठा is logically the
 * same as 'struct timespec' but 32/64b ABI safe.
 */
काष्ठा drm_etnaviv_बारpec अणु
	__s64 tv_sec;          /* seconds */
	__s64 tv_nsec;         /* nanoseconds */
पूर्ण;

#घोषणा ETNAVIV_PARAM_GPU_MODEL                     0x01
#घोषणा ETNAVIV_PARAM_GPU_REVISION                  0x02
#घोषणा ETNAVIV_PARAM_GPU_FEATURES_0                0x03
#घोषणा ETNAVIV_PARAM_GPU_FEATURES_1                0x04
#घोषणा ETNAVIV_PARAM_GPU_FEATURES_2                0x05
#घोषणा ETNAVIV_PARAM_GPU_FEATURES_3                0x06
#घोषणा ETNAVIV_PARAM_GPU_FEATURES_4                0x07
#घोषणा ETNAVIV_PARAM_GPU_FEATURES_5                0x08
#घोषणा ETNAVIV_PARAM_GPU_FEATURES_6                0x09
#घोषणा ETNAVIV_PARAM_GPU_FEATURES_7                0x0a
#घोषणा ETNAVIV_PARAM_GPU_FEATURES_8                0x0b
#घोषणा ETNAVIV_PARAM_GPU_FEATURES_9                0x0c
#घोषणा ETNAVIV_PARAM_GPU_FEATURES_10               0x0d
#घोषणा ETNAVIV_PARAM_GPU_FEATURES_11               0x0e
#घोषणा ETNAVIV_PARAM_GPU_FEATURES_12               0x0f

#घोषणा ETNAVIV_PARAM_GPU_STREAM_COUNT              0x10
#घोषणा ETNAVIV_PARAM_GPU_REGISTER_MAX              0x11
#घोषणा ETNAVIV_PARAM_GPU_THREAD_COUNT              0x12
#घोषणा ETNAVIV_PARAM_GPU_VERTEX_CACHE_SIZE         0x13
#घोषणा ETNAVIV_PARAM_GPU_SHADER_CORE_COUNT         0x14
#घोषणा ETNAVIV_PARAM_GPU_PIXEL_PIPES               0x15
#घोषणा ETNAVIV_PARAM_GPU_VERTEX_OUTPUT_BUFFER_SIZE 0x16
#घोषणा ETNAVIV_PARAM_GPU_BUFFER_SIZE               0x17
#घोषणा ETNAVIV_PARAM_GPU_INSTRUCTION_COUNT         0x18
#घोषणा ETNAVIV_PARAM_GPU_NUM_CONSTANTS             0x19
#घोषणा ETNAVIV_PARAM_GPU_NUM_VARYINGS              0x1a
#घोषणा ETNAVIV_PARAM_SOFTPIN_START_ADDR            0x1b

#घोषणा ETNA_MAX_PIPES 4

काष्ठा drm_etnaviv_param अणु
	__u32 pipe;           /* in */
	__u32 param;          /* in, ETNAVIV_PARAM_x */
	__u64 value;          /* out (get_param) or in (set_param) */
पूर्ण;

/*
 * GEM buffers:
 */

#घोषणा ETNA_BO_CACHE_MASK   0x000f0000
/* cache modes */
#घोषणा ETNA_BO_CACHED       0x00010000
#घोषणा ETNA_BO_WC           0x00020000
#घोषणा ETNA_BO_UNCACHED     0x00040000
/* map flags */
#घोषणा ETNA_BO_FORCE_MMU    0x00100000

काष्ठा drm_etnaviv_gem_new अणु
	__u64 size;           /* in */
	__u32 flags;          /* in, mask of ETNA_BO_x */
	__u32 handle;         /* out */
पूर्ण;

काष्ठा drm_etnaviv_gem_info अणु
	__u32 handle;         /* in */
	__u32 pad;
	__u64 offset;         /* out, offset to pass to mmap() */
पूर्ण;

#घोषणा ETNA_PREP_READ        0x01
#घोषणा ETNA_PREP_WRITE       0x02
#घोषणा ETNA_PREP_NOSYNC      0x04

काष्ठा drm_etnaviv_gem_cpu_prep अणु
	__u32 handle;         /* in */
	__u32 op;             /* in, mask of ETNA_PREP_x */
	काष्ठा drm_etnaviv_बारpec समयout;   /* in */
पूर्ण;

काष्ठा drm_etnaviv_gem_cpu_fini अणु
	__u32 handle;         /* in */
	__u32 flags;          /* in, placeholder क्रम now, no defined values */
पूर्ण;

/*
 * Cmdstream Submission:
 */

/* The value written पूर्णांकo the cmdstream is logically:
 * relocbuf->gpuaddr + reloc_offset
 *
 * NOTE that reloc's must be sorted by order of increasing submit_offset,
 * otherwise EINVAL.
 */
काष्ठा drm_etnaviv_gem_submit_reloc अणु
	__u32 submit_offset;  /* in, offset from submit_bo */
	__u32 reloc_idx;      /* in, index of reloc_bo buffer */
	__u64 reloc_offset;   /* in, offset from start of reloc_bo */
	__u32 flags;          /* in, placeholder क्रम now, no defined values */
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
 * If the submit is a softpin submit (ETNA_SUBMIT_SOFTPIN) the 'presumed'
 * field is पूर्णांकerpreted as the fixed location to map the bo पूर्णांकo the gpu
 * भव address space. If the kernel is unable to map the buffer at
 * this location the submit will fail. This means userspace is responsible
 * क्रम the whole gpu भव address management.
 */
#घोषणा ETNA_SUBMIT_BO_READ             0x0001
#घोषणा ETNA_SUBMIT_BO_WRITE            0x0002
काष्ठा drm_etnaviv_gem_submit_bo अणु
	__u32 flags;          /* in, mask of ETNA_SUBMIT_BO_x */
	__u32 handle;         /* in, GEM handle */
	__u64 presumed;       /* in/out, presumed buffer address */
पूर्ण;

/* perक्रमmance monitor request (pmr) */
#घोषणा ETNA_PM_PROCESS_PRE             0x0001
#घोषणा ETNA_PM_PROCESS_POST            0x0002
काष्ठा drm_etnaviv_gem_submit_pmr अणु
	__u32 flags;          /* in, when to process request (ETNA_PM_PROCESS_x) */
	__u8  करोमुख्य;         /* in, pm करोमुख्य */
	__u8  pad;
	__u16 संकेत;         /* in, pm संकेत */
	__u32 sequence;       /* in, sequence number */
	__u32 पढ़ो_offset;    /* in, offset from पढ़ो_bo */
	__u32 पढ़ो_idx;       /* in, index of पढ़ो_bo buffer */
पूर्ण;

/* Each cmdstream submit consists of a table of buffers involved, and
 * one or more cmdstream buffers.  This allows क्रम conditional execution
 * (context-restore), and IB buffers needed क्रम per tile/bin draw cmds.
 */
#घोषणा ETNA_SUBMIT_NO_IMPLICIT         0x0001
#घोषणा ETNA_SUBMIT_FENCE_FD_IN         0x0002
#घोषणा ETNA_SUBMIT_FENCE_FD_OUT        0x0004
#घोषणा ETNA_SUBMIT_SOFTPIN             0x0008
#घोषणा ETNA_SUBMIT_FLAGS		(ETNA_SUBMIT_NO_IMPLICIT | \
					 ETNA_SUBMIT_FENCE_FD_IN | \
					 ETNA_SUBMIT_FENCE_FD_OUT| \
					 ETNA_SUBMIT_SOFTPIN)
#घोषणा ETNA_PIPE_3D      0x00
#घोषणा ETNA_PIPE_2D      0x01
#घोषणा ETNA_PIPE_VG      0x02
काष्ठा drm_etnaviv_gem_submit अणु
	__u32 fence;          /* out */
	__u32 pipe;           /* in */
	__u32 exec_state;     /* in, initial execution state (ETNA_PIPE_x) */
	__u32 nr_bos;         /* in, number of submit_bo's */
	__u32 nr_relocs;      /* in, number of submit_reloc's */
	__u32 stream_size;    /* in, cmdstream size */
	__u64 bos;            /* in, ptr to array of submit_bo's */
	__u64 relocs;         /* in, ptr to array of submit_reloc's */
	__u64 stream;         /* in, ptr to cmdstream */
	__u32 flags;          /* in, mask of ETNA_SUBMIT_x */
	__s32 fence_fd;       /* in/out, fence fd (see ETNA_SUBMIT_FENCE_FD_x) */
	__u64 pmrs;           /* in, ptr to array of submit_pmr's */
	__u32 nr_pmrs;        /* in, number of submit_pmr's */
	__u32 pad;
पूर्ण;

/* The normal way to synchronize with the GPU is just to CPU_PREP on
 * a buffer अगर you need to access it from the CPU (other cmdstream
 * submission from same or other contexts, PAGE_FLIP ioctl, etc, all
 * handle the required synchronization under the hood).  This ioctl
 * मुख्यly just exists as a way to implement the gallium pipe_fence
 * APIs without requiring a dummy bo to synchronize on.
 */
#घोषणा ETNA_WAIT_NONBLOCK      0x01
काष्ठा drm_etnaviv_रुको_fence अणु
	__u32 pipe;           /* in */
	__u32 fence;          /* in */
	__u32 flags;          /* in, mask of ETNA_WAIT_x */
	__u32 pad;
	काष्ठा drm_etnaviv_बारpec समयout;   /* in */
पूर्ण;

#घोषणा ETNA_USERPTR_READ	0x01
#घोषणा ETNA_USERPTR_WRITE	0x02
काष्ठा drm_etnaviv_gem_userptr अणु
	__u64 user_ptr;	/* in, page aligned user poपूर्णांकer */
	__u64 user_size;	/* in, page aligned user size */
	__u32 flags;		/* in, flags */
	__u32 handle;	/* out, non-zero handle */
पूर्ण;

काष्ठा drm_etnaviv_gem_रुको अणु
	__u32 pipe;				/* in */
	__u32 handle;				/* in, bo to be रुकोed क्रम */
	__u32 flags;				/* in, mask of ETNA_WAIT_x  */
	__u32 pad;
	काष्ठा drm_etnaviv_बारpec समयout;	/* in */
पूर्ण;

/*
 * Perक्रमmance Monitor (PM):
 */

काष्ठा drm_etnaviv_pm_करोमुख्य अणु
	__u32 pipe;       /* in */
	__u8  iter;       /* in/out, select pm करोमुख्य at index iter */
	__u8  id;         /* out, id of करोमुख्य */
	__u16 nr_संकेतs; /* out, how many संकेतs करोes this करोमुख्य provide */
	अक्षर  name[64];   /* out, name of करोमुख्य */
पूर्ण;

काष्ठा drm_etnaviv_pm_संकेत अणु
	__u32 pipe;       /* in */
	__u8  करोमुख्य;     /* in, pm करोमुख्य index */
	__u8  pad;
	__u16 iter;       /* in/out, select pm source at index iter */
	__u16 id;         /* out, id of संकेत */
	अक्षर  name[64];   /* out, name of करोमुख्य */
पूर्ण;

#घोषणा DRM_ETNAVIV_GET_PARAM          0x00
/* placeholder:
#घोषणा DRM_ETNAVIV_SET_PARAM          0x01
 */
#घोषणा DRM_ETNAVIV_GEM_NEW            0x02
#घोषणा DRM_ETNAVIV_GEM_INFO           0x03
#घोषणा DRM_ETNAVIV_GEM_CPU_PREP       0x04
#घोषणा DRM_ETNAVIV_GEM_CPU_FINI       0x05
#घोषणा DRM_ETNAVIV_GEM_SUBMIT         0x06
#घोषणा DRM_ETNAVIV_WAIT_FENCE         0x07
#घोषणा DRM_ETNAVIV_GEM_USERPTR        0x08
#घोषणा DRM_ETNAVIV_GEM_WAIT           0x09
#घोषणा DRM_ETNAVIV_PM_QUERY_DOM       0x0a
#घोषणा DRM_ETNAVIV_PM_QUERY_SIG       0x0b
#घोषणा DRM_ETNAVIV_NUM_IOCTLS         0x0c

#घोषणा DRM_IOCTL_ETNAVIV_GET_PARAM    DRM_IOWR(DRM_COMMAND_BASE + DRM_ETNAVIV_GET_PARAM, काष्ठा drm_etnaviv_param)
#घोषणा DRM_IOCTL_ETNAVIV_GEM_NEW      DRM_IOWR(DRM_COMMAND_BASE + DRM_ETNAVIV_GEM_NEW, काष्ठा drm_etnaviv_gem_new)
#घोषणा DRM_IOCTL_ETNAVIV_GEM_INFO     DRM_IOWR(DRM_COMMAND_BASE + DRM_ETNAVIV_GEM_INFO, काष्ठा drm_etnaviv_gem_info)
#घोषणा DRM_IOCTL_ETNAVIV_GEM_CPU_PREP DRM_IOW(DRM_COMMAND_BASE + DRM_ETNAVIV_GEM_CPU_PREP, काष्ठा drm_etnaviv_gem_cpu_prep)
#घोषणा DRM_IOCTL_ETNAVIV_GEM_CPU_FINI DRM_IOW(DRM_COMMAND_BASE + DRM_ETNAVIV_GEM_CPU_FINI, काष्ठा drm_etnaviv_gem_cpu_fini)
#घोषणा DRM_IOCTL_ETNAVIV_GEM_SUBMIT   DRM_IOWR(DRM_COMMAND_BASE + DRM_ETNAVIV_GEM_SUBMIT, काष्ठा drm_etnaviv_gem_submit)
#घोषणा DRM_IOCTL_ETNAVIV_WAIT_FENCE   DRM_IOW(DRM_COMMAND_BASE + DRM_ETNAVIV_WAIT_FENCE, काष्ठा drm_etnaviv_रुको_fence)
#घोषणा DRM_IOCTL_ETNAVIV_GEM_USERPTR  DRM_IOWR(DRM_COMMAND_BASE + DRM_ETNAVIV_GEM_USERPTR, काष्ठा drm_etnaviv_gem_userptr)
#घोषणा DRM_IOCTL_ETNAVIV_GEM_WAIT     DRM_IOW(DRM_COMMAND_BASE + DRM_ETNAVIV_GEM_WAIT, काष्ठा drm_etnaviv_gem_रुको)
#घोषणा DRM_IOCTL_ETNAVIV_PM_QUERY_DOM DRM_IOWR(DRM_COMMAND_BASE + DRM_ETNAVIV_PM_QUERY_DOM, काष्ठा drm_etnaviv_pm_करोमुख्य)
#घोषणा DRM_IOCTL_ETNAVIV_PM_QUERY_SIG DRM_IOWR(DRM_COMMAND_BASE + DRM_ETNAVIV_PM_QUERY_SIG, काष्ठा drm_etnaviv_pm_संकेत)

#अगर defined(__cplusplus)
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* __ETNAVIV_DRM_H__ */
