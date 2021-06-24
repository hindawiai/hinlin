<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0 WITH Linux-syscall-note) OR MIT */
/* Copyright 2017-2018 Qiang Yu <yuq825@gmail.com> */

#अगर_अघोषित __LIMA_DRM_H__
#घोषणा __LIMA_DRM_H__

#समावेश "drm.h"

#अगर defined(__cplusplus)
बाह्य "C" अणु
#पूर्ण_अगर

क्रमागत drm_lima_param_gpu_id अणु
	DRM_LIMA_PARAM_GPU_ID_UNKNOWN,
	DRM_LIMA_PARAM_GPU_ID_MALI400,
	DRM_LIMA_PARAM_GPU_ID_MALI450,
पूर्ण;

क्रमागत drm_lima_param अणु
	DRM_LIMA_PARAM_GPU_ID,
	DRM_LIMA_PARAM_NUM_PP,
	DRM_LIMA_PARAM_GP_VERSION,
	DRM_LIMA_PARAM_PP_VERSION,
पूर्ण;

/**
 * get various inक्रमmation of the GPU
 */
काष्ठा drm_lima_get_param अणु
	__u32 param; /* in, value in क्रमागत drm_lima_param */
	__u32 pad;   /* pad, must be zero */
	__u64 value; /* out, parameter value */
पूर्ण;

/*
 * heap buffer dynamically increase backup memory size when GP task fail
 * due to lack of heap memory. size field of heap buffer is an up bound of
 * the backup memory which can be set to a fairly large value.
 */
#घोषणा LIMA_BO_FLAG_HEAP  (1 << 0)

/**
 * create a buffer क्रम used by GPU
 */
काष्ठा drm_lima_gem_create अणु
	__u32 size;    /* in, buffer size */
	__u32 flags;   /* in, buffer flags */
	__u32 handle;  /* out, GEM buffer handle */
	__u32 pad;     /* pad, must be zero */
पूर्ण;

/**
 * get inक्रमmation of a buffer
 */
काष्ठा drm_lima_gem_info अणु
	__u32 handle;  /* in, GEM buffer handle */
	__u32 va;      /* out, भव address mapped पूर्णांकo GPU MMU */
	__u64 offset;  /* out, used to mmap this buffer to CPU */
पूर्ण;

#घोषणा LIMA_SUBMIT_BO_READ   0x01
#घोषणा LIMA_SUBMIT_BO_WRITE  0x02

/* buffer inक्रमmation used by one task */
काष्ठा drm_lima_gem_submit_bo अणु
	__u32 handle;  /* in, GEM buffer handle */
	__u32 flags;   /* in, buffer पढ़ो/ग_लिखो by GPU */
पूर्ण;

#घोषणा LIMA_GP_FRAME_REG_NUM 6

/* frame used to setup GP क्रम each task */
काष्ठा drm_lima_gp_frame अणु
	__u32 frame[LIMA_GP_FRAME_REG_NUM];
पूर्ण;

#घोषणा LIMA_PP_FRAME_REG_NUM 23
#घोषणा LIMA_PP_WB_REG_NUM 12

/* frame used to setup mali400 GPU PP क्रम each task */
काष्ठा drm_lima_m400_pp_frame अणु
	__u32 frame[LIMA_PP_FRAME_REG_NUM];
	__u32 num_pp;
	__u32 wb[3 * LIMA_PP_WB_REG_NUM];
	__u32 plbu_array_address[4];
	__u32 fragment_stack_address[4];
पूर्ण;

/* frame used to setup mali450 GPU PP क्रम each task */
काष्ठा drm_lima_m450_pp_frame अणु
	__u32 frame[LIMA_PP_FRAME_REG_NUM];
	__u32 num_pp;
	__u32 wb[3 * LIMA_PP_WB_REG_NUM];
	__u32 use_dlbu;
	__u32 _pad;
	जोड़ अणु
		__u32 plbu_array_address[8];
		__u32 dlbu_regs[4];
	पूर्ण;
	__u32 fragment_stack_address[8];
पूर्ण;

#घोषणा LIMA_PIPE_GP  0x00
#घोषणा LIMA_PIPE_PP  0x01

#घोषणा LIMA_SUBMIT_FLAG_EXPLICIT_FENCE (1 << 0)

/**
 * submit a task to GPU
 *
 * User can always merge multi sync_file and drm_syncobj
 * पूर्णांकo one drm_syncobj as in_sync[0], but we reserve
 * in_sync[1] क्रम another task's out_sync to aव्योम the
 * export/import/merge pass when explicit sync.
 */
काष्ठा drm_lima_gem_submit अणु
	__u32 ctx;         /* in, context handle task is submitted to */
	__u32 pipe;        /* in, which pipe to use, GP/PP */
	__u32 nr_bos;      /* in, array length of bos field */
	__u32 frame_size;  /* in, size of frame field */
	__u64 bos;         /* in, array of drm_lima_gem_submit_bo */
	__u64 frame;       /* in, GP/PP frame */
	__u32 flags;       /* in, submit flags */
	__u32 out_sync;    /* in, drm_syncobj handle used to रुको task finish after submission */
	__u32 in_sync[2];  /* in, drm_syncobj handle used to रुको beक्रमe start this task */
पूर्ण;

#घोषणा LIMA_GEM_WAIT_READ   0x01
#घोषणा LIMA_GEM_WAIT_WRITE  0x02

/**
 * रुको pending GPU task finish of a buffer
 */
काष्ठा drm_lima_gem_रुको अणु
	__u32 handle;      /* in, GEM buffer handle */
	__u32 op;          /* in, CPU want to पढ़ो/ग_लिखो this buffer */
	__s64 समयout_ns;  /* in, रुको समयout in असलulute समय */
पूर्ण;

/**
 * create a context
 */
काष्ठा drm_lima_ctx_create अणु
	__u32 id;          /* out, context handle */
	__u32 _pad;        /* pad, must be zero */
पूर्ण;

/**
 * मुक्त a context
 */
काष्ठा drm_lima_ctx_मुक्त अणु
	__u32 id;          /* in, context handle */
	__u32 _pad;        /* pad, must be zero */
पूर्ण;

#घोषणा DRM_LIMA_GET_PARAM   0x00
#घोषणा DRM_LIMA_GEM_CREATE  0x01
#घोषणा DRM_LIMA_GEM_INFO    0x02
#घोषणा DRM_LIMA_GEM_SUBMIT  0x03
#घोषणा DRM_LIMA_GEM_WAIT    0x04
#घोषणा DRM_LIMA_CTX_CREATE  0x05
#घोषणा DRM_LIMA_CTX_FREE    0x06

#घोषणा DRM_IOCTL_LIMA_GET_PARAM DRM_IOWR(DRM_COMMAND_BASE + DRM_LIMA_GET_PARAM, काष्ठा drm_lima_get_param)
#घोषणा DRM_IOCTL_LIMA_GEM_CREATE DRM_IOWR(DRM_COMMAND_BASE + DRM_LIMA_GEM_CREATE, काष्ठा drm_lima_gem_create)
#घोषणा DRM_IOCTL_LIMA_GEM_INFO DRM_IOWR(DRM_COMMAND_BASE + DRM_LIMA_GEM_INFO, काष्ठा drm_lima_gem_info)
#घोषणा DRM_IOCTL_LIMA_GEM_SUBMIT DRM_IOW(DRM_COMMAND_BASE + DRM_LIMA_GEM_SUBMIT, काष्ठा drm_lima_gem_submit)
#घोषणा DRM_IOCTL_LIMA_GEM_WAIT DRM_IOW(DRM_COMMAND_BASE + DRM_LIMA_GEM_WAIT, काष्ठा drm_lima_gem_रुको)
#घोषणा DRM_IOCTL_LIMA_CTX_CREATE DRM_IOR(DRM_COMMAND_BASE + DRM_LIMA_CTX_CREATE, काष्ठा drm_lima_ctx_create)
#घोषणा DRM_IOCTL_LIMA_CTX_FREE DRM_IOW(DRM_COMMAND_BASE + DRM_LIMA_CTX_FREE, काष्ठा drm_lima_ctx_मुक्त)

#अगर defined(__cplusplus)
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* __LIMA_DRM_H__ */
