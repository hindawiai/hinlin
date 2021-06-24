<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
/*
 * Copyright तऊ 2014-2018 Broadcom
 * Copyright तऊ 2019 Collabora ltd.
 */
#अगर_अघोषित _PANFROST_DRM_H_
#घोषणा _PANFROST_DRM_H_

#समावेश "drm.h"

#अगर defined(__cplusplus)
बाह्य "C" अणु
#पूर्ण_अगर

#घोषणा DRM_PANFROST_SUBMIT			0x00
#घोषणा DRM_PANFROST_WAIT_BO			0x01
#घोषणा DRM_PANFROST_CREATE_BO			0x02
#घोषणा DRM_PANFROST_MMAP_BO			0x03
#घोषणा DRM_PANFROST_GET_PARAM			0x04
#घोषणा DRM_PANFROST_GET_BO_OFFSET		0x05
#घोषणा DRM_PANFROST_PERFCNT_ENABLE		0x06
#घोषणा DRM_PANFROST_PERFCNT_DUMP		0x07
#घोषणा DRM_PANFROST_MADVISE			0x08

#घोषणा DRM_IOCTL_PANFROST_SUBMIT		DRM_IOW(DRM_COMMAND_BASE + DRM_PANFROST_SUBMIT, काष्ठा drm_panfrost_submit)
#घोषणा DRM_IOCTL_PANFROST_WAIT_BO		DRM_IOW(DRM_COMMAND_BASE + DRM_PANFROST_WAIT_BO, काष्ठा drm_panfrost_रुको_bo)
#घोषणा DRM_IOCTL_PANFROST_CREATE_BO		DRM_IOWR(DRM_COMMAND_BASE + DRM_PANFROST_CREATE_BO, काष्ठा drm_panfrost_create_bo)
#घोषणा DRM_IOCTL_PANFROST_MMAP_BO		DRM_IOWR(DRM_COMMAND_BASE + DRM_PANFROST_MMAP_BO, काष्ठा drm_panfrost_mmap_bo)
#घोषणा DRM_IOCTL_PANFROST_GET_PARAM		DRM_IOWR(DRM_COMMAND_BASE + DRM_PANFROST_GET_PARAM, काष्ठा drm_panfrost_get_param)
#घोषणा DRM_IOCTL_PANFROST_GET_BO_OFFSET	DRM_IOWR(DRM_COMMAND_BASE + DRM_PANFROST_GET_BO_OFFSET, काष्ठा drm_panfrost_get_bo_offset)
#घोषणा DRM_IOCTL_PANFROST_MADVISE		DRM_IOWR(DRM_COMMAND_BASE + DRM_PANFROST_MADVISE, काष्ठा drm_panfrost_madvise)

/*
 * Unstable ioctl(s): only exposed when the unsafe unstable_ioctls module
 * param is set to true.
 * All these ioctl(s) are subject to deprecation, so please करोn't rely on
 * them क्रम anything but debugging purpose.
 */
#घोषणा DRM_IOCTL_PANFROST_PERFCNT_ENABLE	DRM_IOW(DRM_COMMAND_BASE + DRM_PANFROST_PERFCNT_ENABLE, काष्ठा drm_panfrost_perfcnt_enable)
#घोषणा DRM_IOCTL_PANFROST_PERFCNT_DUMP		DRM_IOW(DRM_COMMAND_BASE + DRM_PANFROST_PERFCNT_DUMP, काष्ठा drm_panfrost_perfcnt_dump)

#घोषणा PANFROST_JD_REQ_FS (1 << 0)
/**
 * काष्ठा drm_panfrost_submit - ioctl argument क्रम submitting commands to the 3D
 * engine.
 *
 * This asks the kernel to have the GPU execute a render command list.
 */
काष्ठा drm_panfrost_submit अणु

	/** Address to GPU mapping of job descriptor */
	__u64 jc;

	/** An optional array of sync objects to रुको on beक्रमe starting this job. */
	__u64 in_syncs;

	/** Number of sync objects to रुको on beक्रमe starting this job. */
	__u32 in_sync_count;

	/** An optional sync object to place the completion fence in. */
	__u32 out_sync;

	/** Poपूर्णांकer to a u32 array of the BOs that are referenced by the job. */
	__u64 bo_handles;

	/** Number of BO handles passed in (size is that बार 4). */
	__u32 bo_handle_count;

	/** A combination of PANFROST_JD_REQ_* */
	__u32 requirements;
पूर्ण;

/**
 * काष्ठा drm_panfrost_रुको_bo - ioctl argument क्रम रुकोing क्रम
 * completion of the last DRM_PANFROST_SUBMIT on a BO.
 *
 * This is useful क्रम हालs where multiple processes might be
 * rendering to a BO and you want to रुको क्रम all rendering to be
 * completed.
 */
काष्ठा drm_panfrost_रुको_bo अणु
	__u32 handle;
	__u32 pad;
	__s64 समयout_ns;	/* असलolute */
पूर्ण;

#घोषणा PANFROST_BO_NOEXEC	1
#घोषणा PANFROST_BO_HEAP	2

/**
 * काष्ठा drm_panfrost_create_bo - ioctl argument क्रम creating Panfrost BOs.
 *
 * There are currently no values क्रम the flags argument, but it may be
 * used in a future extension.
 */
काष्ठा drm_panfrost_create_bo अणु
	__u32 size;
	__u32 flags;
	/** Returned GEM handle क्रम the BO. */
	__u32 handle;
	/* Pad, must be zero-filled. */
	__u32 pad;
	/**
	 * Returned offset क्रम the BO in the GPU address space.  This offset
	 * is निजी to the DRM fd and is valid क्रम the lअगरeसमय of the GEM
	 * handle.
	 *
	 * This offset value will always be nonzero, since various HW
	 * units treat 0 specially.
	 */
	__u64 offset;
पूर्ण;

/**
 * काष्ठा drm_panfrost_mmap_bo - ioctl argument क्रम mapping Panfrost BOs.
 *
 * This करोesn't actually perक्रमm an mmap.  Instead, it वापसs the
 * offset you need to use in an mmap on the DRM device node.  This
 * means that tools like valgrind end up knowing about the mapped
 * memory.
 *
 * There are currently no values क्रम the flags argument, but it may be
 * used in a future extension.
 */
काष्ठा drm_panfrost_mmap_bo अणु
	/** Handle क्रम the object being mapped. */
	__u32 handle;
	__u32 flags;
	/** offset पूर्णांकo the drm node to use क्रम subsequent mmap call. */
	__u64 offset;
पूर्ण;

क्रमागत drm_panfrost_param अणु
	DRM_PANFROST_PARAM_GPU_PROD_ID,
	DRM_PANFROST_PARAM_GPU_REVISION,
	DRM_PANFROST_PARAM_SHADER_PRESENT,
	DRM_PANFROST_PARAM_TILER_PRESENT,
	DRM_PANFROST_PARAM_L2_PRESENT,
	DRM_PANFROST_PARAM_STACK_PRESENT,
	DRM_PANFROST_PARAM_AS_PRESENT,
	DRM_PANFROST_PARAM_JS_PRESENT,
	DRM_PANFROST_PARAM_L2_FEATURES,
	DRM_PANFROST_PARAM_CORE_FEATURES,
	DRM_PANFROST_PARAM_TILER_FEATURES,
	DRM_PANFROST_PARAM_MEM_FEATURES,
	DRM_PANFROST_PARAM_MMU_FEATURES,
	DRM_PANFROST_PARAM_THREAD_FEATURES,
	DRM_PANFROST_PARAM_MAX_THREADS,
	DRM_PANFROST_PARAM_THREAD_MAX_WORKGROUP_SZ,
	DRM_PANFROST_PARAM_THREAD_MAX_BARRIER_SZ,
	DRM_PANFROST_PARAM_COHERENCY_FEATURES,
	DRM_PANFROST_PARAM_TEXTURE_FEATURES0,
	DRM_PANFROST_PARAM_TEXTURE_FEATURES1,
	DRM_PANFROST_PARAM_TEXTURE_FEATURES2,
	DRM_PANFROST_PARAM_TEXTURE_FEATURES3,
	DRM_PANFROST_PARAM_JS_FEATURES0,
	DRM_PANFROST_PARAM_JS_FEATURES1,
	DRM_PANFROST_PARAM_JS_FEATURES2,
	DRM_PANFROST_PARAM_JS_FEATURES3,
	DRM_PANFROST_PARAM_JS_FEATURES4,
	DRM_PANFROST_PARAM_JS_FEATURES5,
	DRM_PANFROST_PARAM_JS_FEATURES6,
	DRM_PANFROST_PARAM_JS_FEATURES7,
	DRM_PANFROST_PARAM_JS_FEATURES8,
	DRM_PANFROST_PARAM_JS_FEATURES9,
	DRM_PANFROST_PARAM_JS_FEATURES10,
	DRM_PANFROST_PARAM_JS_FEATURES11,
	DRM_PANFROST_PARAM_JS_FEATURES12,
	DRM_PANFROST_PARAM_JS_FEATURES13,
	DRM_PANFROST_PARAM_JS_FEATURES14,
	DRM_PANFROST_PARAM_JS_FEATURES15,
	DRM_PANFROST_PARAM_NR_CORE_GROUPS,
	DRM_PANFROST_PARAM_THREAD_TLS_ALLOC,
पूर्ण;

काष्ठा drm_panfrost_get_param अणु
	__u32 param;
	__u32 pad;
	__u64 value;
पूर्ण;

/**
 * Returns the offset क्रम the BO in the GPU address space क्रम this DRM fd.
 * This is the same value वापसed by drm_panfrost_create_bo, अगर that was called
 * from this DRM fd.
 */
काष्ठा drm_panfrost_get_bo_offset अणु
	__u32 handle;
	__u32 pad;
	__u64 offset;
पूर्ण;

काष्ठा drm_panfrost_perfcnt_enable अणु
	__u32 enable;
	/*
	 * On bअगरrost we have 2 sets of counters, this parameter defines the
	 * one to track.
	 */
	__u32 counterset;
पूर्ण;

काष्ठा drm_panfrost_perfcnt_dump अणु
	__u64 buf_ptr;
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
#घोषणा PANFROST_MADV_WILLNEED 0	/* backing pages are needed, status वापसed in 'retained' */
#घोषणा PANFROST_MADV_DONTNEED 1	/* backing pages not needed */

काष्ठा drm_panfrost_madvise अणु
	__u32 handle;         /* in, GEM handle */
	__u32 madv;           /* in, PANFROST_MADV_x */
	__u32 retained;       /* out, whether backing store still exists */
पूर्ण;

#अगर defined(__cplusplus)
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* _PANFROST_DRM_H_ */
