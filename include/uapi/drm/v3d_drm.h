<शैली गुरु>
/*
 * Copyright तऊ 2014-2018 Broadcom
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
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#अगर_अघोषित _V3D_DRM_H_
#घोषणा _V3D_DRM_H_

#समावेश "drm.h"

#अगर defined(__cplusplus)
बाह्य "C" अणु
#पूर्ण_अगर

#घोषणा DRM_V3D_SUBMIT_CL                         0x00
#घोषणा DRM_V3D_WAIT_BO                           0x01
#घोषणा DRM_V3D_CREATE_BO                         0x02
#घोषणा DRM_V3D_MMAP_BO                           0x03
#घोषणा DRM_V3D_GET_PARAM                         0x04
#घोषणा DRM_V3D_GET_BO_OFFSET                     0x05
#घोषणा DRM_V3D_SUBMIT_TFU                        0x06
#घोषणा DRM_V3D_SUBMIT_CSD                        0x07

#घोषणा DRM_IOCTL_V3D_SUBMIT_CL           DRM_IOWR(DRM_COMMAND_BASE + DRM_V3D_SUBMIT_CL, काष्ठा drm_v3d_submit_cl)
#घोषणा DRM_IOCTL_V3D_WAIT_BO             DRM_IOWR(DRM_COMMAND_BASE + DRM_V3D_WAIT_BO, काष्ठा drm_v3d_रुको_bo)
#घोषणा DRM_IOCTL_V3D_CREATE_BO           DRM_IOWR(DRM_COMMAND_BASE + DRM_V3D_CREATE_BO, काष्ठा drm_v3d_create_bo)
#घोषणा DRM_IOCTL_V3D_MMAP_BO             DRM_IOWR(DRM_COMMAND_BASE + DRM_V3D_MMAP_BO, काष्ठा drm_v3d_mmap_bo)
#घोषणा DRM_IOCTL_V3D_GET_PARAM           DRM_IOWR(DRM_COMMAND_BASE + DRM_V3D_GET_PARAM, काष्ठा drm_v3d_get_param)
#घोषणा DRM_IOCTL_V3D_GET_BO_OFFSET       DRM_IOWR(DRM_COMMAND_BASE + DRM_V3D_GET_BO_OFFSET, काष्ठा drm_v3d_get_bo_offset)
#घोषणा DRM_IOCTL_V3D_SUBMIT_TFU          DRM_IOW(DRM_COMMAND_BASE + DRM_V3D_SUBMIT_TFU, काष्ठा drm_v3d_submit_tfu)
#घोषणा DRM_IOCTL_V3D_SUBMIT_CSD          DRM_IOW(DRM_COMMAND_BASE + DRM_V3D_SUBMIT_CSD, काष्ठा drm_v3d_submit_csd)

#घोषणा DRM_V3D_SUBMIT_CL_FLUSH_CACHE             0x01

/**
 * काष्ठा drm_v3d_submit_cl - ioctl argument क्रम submitting commands to the 3D
 * engine.
 *
 * This asks the kernel to have the GPU execute an optional binner
 * command list, and a render command list.
 *
 * The L1T, slice, L2C, L2T, and GCA caches will be flushed beक्रमe
 * each CL executes.  The VCD cache should be flushed (अगर necessary)
 * by the submitted CLs.  The TLB ग_लिखोs are guaranteed to have been
 * flushed by the समय the render करोne IRQ happens, which is the
 * trigger क्रम out_sync.  Any dirtying of cachelines by the job (only
 * possible using TMU ग_लिखोs) must be flushed by the caller using the
 * DRM_V3D_SUBMIT_CL_FLUSH_CACHE_FLAG flag.
 */
काष्ठा drm_v3d_submit_cl अणु
	/* Poपूर्णांकer to the binner command list.
	 *
	 * This is the first set of commands executed, which runs the
	 * coordinate shader to determine where primitives land on the screen,
	 * then ग_लिखोs out the state updates and draw calls necessary per tile
	 * to the tile allocation BO.
	 *
	 * This BCL will block on any previous BCL submitted on the
	 * same FD, but not on any RCL or BCLs submitted by other
	 * clients -- that is left up to the submitter to control
	 * using in_sync_bcl अगर necessary.
	 */
	__u32 bcl_start;

	/** End address of the BCL (first byte after the BCL) */
	__u32 bcl_end;

	/* Offset of the render command list.
	 *
	 * This is the second set of commands executed, which will either
	 * execute the tiles that have been set up by the BCL, or a fixed set
	 * of tiles (in the हाल of RCL-only blits).
	 *
	 * This RCL will block on this submit's BCL, and any previous
	 * RCL submitted on the same FD, but not on any RCL or BCLs
	 * submitted by other clients -- that is left up to the
	 * submitter to control using in_sync_rcl अगर necessary.
	 */
	__u32 rcl_start;

	/** End address of the RCL (first byte after the RCL) */
	__u32 rcl_end;

	/** An optional sync object to रुको on beक्रमe starting the BCL. */
	__u32 in_sync_bcl;
	/** An optional sync object to रुको on beक्रमe starting the RCL. */
	__u32 in_sync_rcl;
	/** An optional sync object to place the completion fence in. */
	__u32 out_sync;

	/* Offset of the tile alloc memory
	 *
	 * This is optional on V3D 3.3 (where the CL can set the value) but
	 * required on V3D 4.1.
	 */
	__u32 qma;

	/** Size of the tile alloc memory. */
	__u32 qms;

	/** Offset of the tile state data array. */
	__u32 qts;

	/* Poपूर्णांकer to a u32 array of the BOs that are referenced by the job.
	 */
	__u64 bo_handles;

	/* Number of BO handles passed in (size is that बार 4). */
	__u32 bo_handle_count;

	__u32 flags;
पूर्ण;

/**
 * काष्ठा drm_v3d_रुको_bo - ioctl argument क्रम रुकोing क्रम
 * completion of the last DRM_V3D_SUBMIT_CL on a BO.
 *
 * This is useful क्रम हालs where multiple processes might be
 * rendering to a BO and you want to रुको क्रम all rendering to be
 * completed.
 */
काष्ठा drm_v3d_रुको_bo अणु
	__u32 handle;
	__u32 pad;
	__u64 समयout_ns;
पूर्ण;

/**
 * काष्ठा drm_v3d_create_bo - ioctl argument क्रम creating V3D BOs.
 *
 * There are currently no values क्रम the flags argument, but it may be
 * used in a future extension.
 */
काष्ठा drm_v3d_create_bo अणु
	__u32 size;
	__u32 flags;
	/** Returned GEM handle क्रम the BO. */
	__u32 handle;
	/**
	 * Returned offset क्रम the BO in the V3D address space.  This offset
	 * is निजी to the DRM fd and is valid क्रम the lअगरeसमय of the GEM
	 * handle.
	 *
	 * This offset value will always be nonzero, since various HW
	 * units treat 0 specially.
	 */
	__u32 offset;
पूर्ण;

/**
 * काष्ठा drm_v3d_mmap_bo - ioctl argument क्रम mapping V3D BOs.
 *
 * This करोesn't actually perक्रमm an mmap.  Instead, it वापसs the
 * offset you need to use in an mmap on the DRM device node.  This
 * means that tools like valgrind end up knowing about the mapped
 * memory.
 *
 * There are currently no values क्रम the flags argument, but it may be
 * used in a future extension.
 */
काष्ठा drm_v3d_mmap_bo अणु
	/** Handle क्रम the object being mapped. */
	__u32 handle;
	__u32 flags;
	/** offset पूर्णांकo the drm node to use क्रम subsequent mmap call. */
	__u64 offset;
पूर्ण;

क्रमागत drm_v3d_param अणु
	DRM_V3D_PARAM_V3D_UIFCFG,
	DRM_V3D_PARAM_V3D_HUB_IDENT1,
	DRM_V3D_PARAM_V3D_HUB_IDENT2,
	DRM_V3D_PARAM_V3D_HUB_IDENT3,
	DRM_V3D_PARAM_V3D_CORE0_IDENT0,
	DRM_V3D_PARAM_V3D_CORE0_IDENT1,
	DRM_V3D_PARAM_V3D_CORE0_IDENT2,
	DRM_V3D_PARAM_SUPPORTS_TFU,
	DRM_V3D_PARAM_SUPPORTS_CSD,
	DRM_V3D_PARAM_SUPPORTS_CACHE_FLUSH,
पूर्ण;

काष्ठा drm_v3d_get_param अणु
	__u32 param;
	__u32 pad;
	__u64 value;
पूर्ण;

/**
 * Returns the offset क्रम the BO in the V3D address space क्रम this DRM fd.
 * This is the same value वापसed by drm_v3d_create_bo, अगर that was called
 * from this DRM fd.
 */
काष्ठा drm_v3d_get_bo_offset अणु
	__u32 handle;
	__u32 offset;
पूर्ण;

काष्ठा drm_v3d_submit_tfu अणु
	__u32 icfg;
	__u32 iia;
	__u32 iis;
	__u32 ica;
	__u32 iua;
	__u32 ioa;
	__u32 ios;
	__u32 coef[4];
	/* First handle is the output BO, following are other inमाला_दो.
	 * 0 क्रम unused.
	 */
	__u32 bo_handles[4];
	/* sync object to block on beक्रमe running the TFU job.  Each TFU
	 * job will execute in the order submitted to its FD.  Synchronization
	 * against rendering jobs requires using sync objects.
	 */
	__u32 in_sync;
	/* Sync object to संकेत when the TFU job is करोne. */
	__u32 out_sync;
पूर्ण;

/* Submits a compute shader क्रम dispatch.  This job will block on any
 * previous compute shaders submitted on this fd, and any other
 * synchronization must be perक्रमmed with in_sync/out_sync.
 */
काष्ठा drm_v3d_submit_csd अणु
	__u32 cfg[7];
	__u32 coef[4];

	/* Poपूर्णांकer to a u32 array of the BOs that are referenced by the job.
	 */
	__u64 bo_handles;

	/* Number of BO handles passed in (size is that बार 4). */
	__u32 bo_handle_count;

	/* sync object to block on beक्रमe running the CSD job.  Each
	 * CSD job will execute in the order submitted to its FD.
	 * Synchronization against rendering/TFU jobs or CSD from
	 * other fds requires using sync objects.
	 */
	__u32 in_sync;
	/* Sync object to संकेत when the CSD job is करोne. */
	__u32 out_sync;
पूर्ण;

#अगर defined(__cplusplus)
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* _V3D_DRM_H_ */
