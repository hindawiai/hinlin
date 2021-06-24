<शैली गुरु>
/**************************************************************************
 *
 * Copyright तऊ 2009-2015 VMware, Inc., Palo Alto, CA., USA
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
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. IN NO EVENT SHALL
 * THE COPYRIGHT HOLDERS, AUTHORS AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
 * USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 **************************************************************************/

#अगर_अघोषित __VMWGFX_DRM_H__
#घोषणा __VMWGFX_DRM_H__

#समावेश "drm.h"

#अगर defined(__cplusplus)
बाह्य "C" अणु
#पूर्ण_अगर

#घोषणा DRM_VMW_MAX_SURFACE_FACES 6
#घोषणा DRM_VMW_MAX_MIP_LEVELS 24


#घोषणा DRM_VMW_GET_PARAM            0
#घोषणा DRM_VMW_ALLOC_DMABUF         1
#घोषणा DRM_VMW_ALLOC_BO             1
#घोषणा DRM_VMW_UNREF_DMABUF         2
#घोषणा DRM_VMW_HANDLE_CLOSE         2
#घोषणा DRM_VMW_CURSOR_BYPASS        3
/* guarded by DRM_VMW_PARAM_NUM_STREAMS != 0*/
#घोषणा DRM_VMW_CONTROL_STREAM       4
#घोषणा DRM_VMW_CLAIM_STREAM         5
#घोषणा DRM_VMW_UNREF_STREAM         6
/* guarded by DRM_VMW_PARAM_3D == 1 */
#घोषणा DRM_VMW_CREATE_CONTEXT       7
#घोषणा DRM_VMW_UNREF_CONTEXT        8
#घोषणा DRM_VMW_CREATE_SURFACE       9
#घोषणा DRM_VMW_UNREF_SURFACE        10
#घोषणा DRM_VMW_REF_SURFACE          11
#घोषणा DRM_VMW_EXECBUF              12
#घोषणा DRM_VMW_GET_3D_CAP           13
#घोषणा DRM_VMW_FENCE_WAIT           14
#घोषणा DRM_VMW_FENCE_SIGNALED       15
#घोषणा DRM_VMW_FENCE_UNREF          16
#घोषणा DRM_VMW_FENCE_EVENT          17
#घोषणा DRM_VMW_PRESENT              18
#घोषणा DRM_VMW_PRESENT_READBACK     19
#घोषणा DRM_VMW_UPDATE_LAYOUT        20
#घोषणा DRM_VMW_CREATE_SHADER        21
#घोषणा DRM_VMW_UNREF_SHADER         22
#घोषणा DRM_VMW_GB_SURFACE_CREATE    23
#घोषणा DRM_VMW_GB_SURFACE_REF       24
#घोषणा DRM_VMW_SYNCCPU              25
#घोषणा DRM_VMW_CREATE_EXTENDED_CONTEXT 26
#घोषणा DRM_VMW_GB_SURFACE_CREATE_EXT   27
#घोषणा DRM_VMW_GB_SURFACE_REF_EXT      28
#घोषणा DRM_VMW_MSG                     29

/*************************************************************************/
/**
 * DRM_VMW_GET_PARAM - get device inक्रमmation.
 *
 * DRM_VMW_PARAM_FIFO_OFFSET:
 * Offset to use to map the first page of the FIFO पढ़ो-only.
 * The fअगरo is mapped using the mmap() प्रणाली call on the drm device.
 *
 * DRM_VMW_PARAM_OVERLAY_IOCTL:
 * Does the driver support the overlay ioctl.
 *
 * DRM_VMW_PARAM_SM4_1
 * SM4_1 support is enabled.
 *
 * DRM_VMW_PARAM_SM5
 * SM5 support is enabled.
 */

#घोषणा DRM_VMW_PARAM_NUM_STREAMS      0
#घोषणा DRM_VMW_PARAM_NUM_FREE_STREAMS 1
#घोषणा DRM_VMW_PARAM_3D               2
#घोषणा DRM_VMW_PARAM_HW_CAPS          3
#घोषणा DRM_VMW_PARAM_FIFO_CAPS        4
#घोषणा DRM_VMW_PARAM_MAX_FB_SIZE      5
#घोषणा DRM_VMW_PARAM_FIFO_HW_VERSION  6
#घोषणा DRM_VMW_PARAM_MAX_SURF_MEMORY  7
#घोषणा DRM_VMW_PARAM_3D_CAPS_SIZE     8
#घोषणा DRM_VMW_PARAM_MAX_MOB_MEMORY   9
#घोषणा DRM_VMW_PARAM_MAX_MOB_SIZE     10
#घोषणा DRM_VMW_PARAM_SCREEN_TARGET    11
#घोषणा DRM_VMW_PARAM_DX               12
#घोषणा DRM_VMW_PARAM_HW_CAPS2         13
#घोषणा DRM_VMW_PARAM_SM4_1            14
#घोषणा DRM_VMW_PARAM_SM5              15

/**
 * क्रमागत drm_vmw_handle_type - handle type क्रम ref ioctls
 *
 */
क्रमागत drm_vmw_handle_type अणु
	DRM_VMW_HANDLE_LEGACY = 0,
	DRM_VMW_HANDLE_PRIME = 1
पूर्ण;

/**
 * काष्ठा drm_vmw_getparam_arg
 *
 * @value: Returned value. //Out
 * @param: Parameter to query. //In.
 *
 * Argument to the DRM_VMW_GET_PARAM Ioctl.
 */

काष्ठा drm_vmw_getparam_arg अणु
	__u64 value;
	__u32 param;
	__u32 pad64;
पूर्ण;

/*************************************************************************/
/**
 * DRM_VMW_CREATE_CONTEXT - Create a host context.
 *
 * Allocates a device unique context id, and queues a create context command
 * क्रम the host. Does not रुको क्रम host completion.
 */

/**
 * काष्ठा drm_vmw_context_arg
 *
 * @cid: Device unique context ID.
 *
 * Output argument to the DRM_VMW_CREATE_CONTEXT Ioctl.
 * Input argument to the DRM_VMW_UNREF_CONTEXT Ioctl.
 */

काष्ठा drm_vmw_context_arg अणु
	__s32 cid;
	__u32 pad64;
पूर्ण;

/*************************************************************************/
/**
 * DRM_VMW_UNREF_CONTEXT - Create a host context.
 *
 * Frees a global context id, and queues a destroy host command क्रम the host.
 * Does not रुको क्रम host completion. The context ID can be used directly
 * in the command stream and shows up as the same context ID on the host.
 */

/*************************************************************************/
/**
 * DRM_VMW_CREATE_SURFACE - Create a host suface.
 *
 * Allocates a device unique surface id, and queues a create surface command
 * क्रम the host. Does not रुको क्रम host completion. The surface ID can be
 * used directly in the command stream and shows up as the same surface
 * ID on the host.
 */

/**
 * काष्ठा drm_wmv_surface_create_req
 *
 * @flags: Surface flags as understood by the host.
 * @क्रमmat: Surface क्रमmat as understood by the host.
 * @mip_levels: Number of mip levels क्रम each face.
 * An unused face should have 0 encoded.
 * @size_addr: Address of a user-space array of sruct drm_vmw_size
 * cast to an __u64 क्रम 32-64 bit compatibility.
 * The size of the array should equal the total number of mipmap levels.
 * @shareable: Boolean whether other clients (as identअगरied by file descriptors)
 * may reference this surface.
 * @scanout: Boolean whether the surface is पूर्णांकended to be used as a
 * scanout.
 *
 * Input data to the DRM_VMW_CREATE_SURFACE Ioctl.
 * Output data from the DRM_VMW_REF_SURFACE Ioctl.
 */

काष्ठा drm_vmw_surface_create_req अणु
	__u32 flags;
	__u32 क्रमmat;
	__u32 mip_levels[DRM_VMW_MAX_SURFACE_FACES];
	__u64 size_addr;
	__s32 shareable;
	__s32 scanout;
पूर्ण;

/**
 * काष्ठा drm_wmv_surface_arg
 *
 * @sid: Surface id of created surface or surface to destroy or reference.
 * @handle_type: Handle type क्रम DRM_VMW_REF_SURFACE Ioctl.
 *
 * Output data from the DRM_VMW_CREATE_SURFACE Ioctl.
 * Input argument to the DRM_VMW_UNREF_SURFACE Ioctl.
 * Input argument to the DRM_VMW_REF_SURFACE Ioctl.
 */

काष्ठा drm_vmw_surface_arg अणु
	__s32 sid;
	क्रमागत drm_vmw_handle_type handle_type;
पूर्ण;

/**
 * काष्ठा drm_vmw_size ioctl.
 *
 * @width - mip level width
 * @height - mip level height
 * @depth - mip level depth
 *
 * Description of a mip level.
 * Input data to the DRM_WMW_CREATE_SURFACE Ioctl.
 */

काष्ठा drm_vmw_size अणु
	__u32 width;
	__u32 height;
	__u32 depth;
	__u32 pad64;
पूर्ण;

/**
 * जोड़ drm_vmw_surface_create_arg
 *
 * @rep: Output data as described above.
 * @req: Input data as described above.
 *
 * Argument to the DRM_VMW_CREATE_SURFACE Ioctl.
 */

जोड़ drm_vmw_surface_create_arg अणु
	काष्ठा drm_vmw_surface_arg rep;
	काष्ठा drm_vmw_surface_create_req req;
पूर्ण;

/*************************************************************************/
/**
 * DRM_VMW_REF_SURFACE - Reference a host surface.
 *
 * Puts a reference on a host surface with a give sid, as previously
 * वापसed by the DRM_VMW_CREATE_SURFACE ioctl.
 * A reference will make sure the surface isn't destroyed जबतक we hold
 * it and will allow the calling client to use the surface ID in the command
 * stream.
 *
 * On successful वापस, the Ioctl वापसs the surface inक्रमmation given
 * in the DRM_VMW_CREATE_SURFACE ioctl.
 */

/**
 * जोड़ drm_vmw_surface_reference_arg
 *
 * @rep: Output data as described above.
 * @req: Input data as described above.
 *
 * Argument to the DRM_VMW_REF_SURFACE Ioctl.
 */

जोड़ drm_vmw_surface_reference_arg अणु
	काष्ठा drm_vmw_surface_create_req rep;
	काष्ठा drm_vmw_surface_arg req;
पूर्ण;

/*************************************************************************/
/**
 * DRM_VMW_UNREF_SURFACE - Unreference a host surface.
 *
 * Clear a reference previously put on a host surface.
 * When all references are gone, including the one implicitly placed
 * on creation,
 * a destroy surface command will be queued क्रम the host.
 * Does not रुको क्रम completion.
 */

/*************************************************************************/
/**
 * DRM_VMW_EXECBUF
 *
 * Submit a command buffer क्रम execution on the host, and वापस a
 * fence seqno that when संकेतed, indicates that the command buffer has
 * executed.
 */

/**
 * काष्ठा drm_vmw_execbuf_arg
 *
 * @commands: User-space address of a command buffer cast to an __u64.
 * @command-size: Size in bytes of the command buffer.
 * @throttle-us: Sleep until software is less than @throttle_us
 * microseconds ahead of hardware. The driver may round this value
 * to the nearest kernel tick.
 * @fence_rep: User-space address of a काष्ठा drm_vmw_fence_rep cast to an
 * __u64.
 * @version: Allows expanding the execbuf ioctl parameters without अवरोधing
 * backwards compatibility, since user-space will always tell the kernel
 * which version it uses.
 * @flags: Execbuf flags.
 * @imported_fence_fd:  FD क्रम a fence imported from another device
 *
 * Argument to the DRM_VMW_EXECBUF Ioctl.
 */

#घोषणा DRM_VMW_EXECBUF_VERSION 2

#घोषणा DRM_VMW_EXECBUF_FLAG_IMPORT_FENCE_FD (1 << 0)
#घोषणा DRM_VMW_EXECBUF_FLAG_EXPORT_FENCE_FD (1 << 1)

काष्ठा drm_vmw_execbuf_arg अणु
	__u64 commands;
	__u32 command_size;
	__u32 throttle_us;
	__u64 fence_rep;
	__u32 version;
	__u32 flags;
	__u32 context_handle;
	__s32 imported_fence_fd;
पूर्ण;

/**
 * काष्ठा drm_vmw_fence_rep
 *
 * @handle: Fence object handle क्रम fence associated with a command submission.
 * @mask: Fence flags relevant क्रम this fence object.
 * @seqno: Fence sequence number in fअगरo. A fence object with a lower
 * seqno will संकेत the EXEC flag beक्रमe a fence object with a higher
 * seqno. This can be used by user-space to aव्योम kernel calls to determine
 * whether a fence has संकेतed the EXEC flag. Note that @seqno will
 * wrap at 32-bit.
 * @passed_seqno: The highest seqno number processed by the hardware
 * so far. This can be used to mark user-space fence objects as संकेतed, and
 * to determine whether a fence seqno might be stale.
 * @fd: FD associated with the fence, -1 अगर not exported
 * @error: This member should've been set to -EFAULT on submission.
 * The following actions should be take on completion:
 * error == -EFAULT: Fence communication failed. The host is synchronized.
 * Use the last fence id पढ़ो from the FIFO fence रेजिस्टर.
 * error != 0 && error != -EFAULT:
 * Fence submission failed. The host is synchronized. Use the fence_seq member.
 * error == 0: All is OK, The host may not be synchronized.
 * Use the fence_seq member.
 *
 * Input / Output data to the DRM_VMW_EXECBUF Ioctl.
 */

काष्ठा drm_vmw_fence_rep अणु
	__u32 handle;
	__u32 mask;
	__u32 seqno;
	__u32 passed_seqno;
	__s32 fd;
	__s32 error;
पूर्ण;

/*************************************************************************/
/**
 * DRM_VMW_ALLOC_BO
 *
 * Allocate a buffer object that is visible also to the host.
 * NOTE: The buffer is
 * identअगरied by a handle and an offset, which are निजी to the guest, but
 * useable in the command stream. The guest kernel may translate these
 * and patch up the command stream accordingly. In the future, the offset may
 * be zero at all बार, or it may disappear from the पूर्णांकerface beक्रमe it is
 * fixed.
 *
 * The buffer object may stay user-space mapped in the guest at all बार,
 * and is thus suitable क्रम sub-allocation.
 *
 * Buffer objects are mapped using the mmap() syscall on the drm device.
 */

/**
 * काष्ठा drm_vmw_alloc_bo_req
 *
 * @size: Required minimum size of the buffer.
 *
 * Input data to the DRM_VMW_ALLOC_BO Ioctl.
 */

काष्ठा drm_vmw_alloc_bo_req अणु
	__u32 size;
	__u32 pad64;
पूर्ण;
#घोषणा drm_vmw_alloc_dmabuf_req drm_vmw_alloc_bo_req

/**
 * काष्ठा drm_vmw_bo_rep
 *
 * @map_handle: Offset to use in the mmap() call used to map the buffer.
 * @handle: Handle unique to this buffer. Used क्रम unreferencing.
 * @cur_gmr_id: GMR id to use in the command stream when this buffer is
 * referenced. See not above.
 * @cur_gmr_offset: Offset to use in the command stream when this buffer is
 * referenced. See note above.
 *
 * Output data from the DRM_VMW_ALLOC_BO Ioctl.
 */

काष्ठा drm_vmw_bo_rep अणु
	__u64 map_handle;
	__u32 handle;
	__u32 cur_gmr_id;
	__u32 cur_gmr_offset;
	__u32 pad64;
पूर्ण;
#घोषणा drm_vmw_dmabuf_rep drm_vmw_bo_rep

/**
 * जोड़ drm_vmw_alloc_bo_arg
 *
 * @req: Input data as described above.
 * @rep: Output data as described above.
 *
 * Argument to the DRM_VMW_ALLOC_BO Ioctl.
 */

जोड़ drm_vmw_alloc_bo_arg अणु
	काष्ठा drm_vmw_alloc_bo_req req;
	काष्ठा drm_vmw_bo_rep rep;
पूर्ण;
#घोषणा drm_vmw_alloc_dmabuf_arg drm_vmw_alloc_bo_arg

/*************************************************************************/
/**
 * DRM_VMW_CONTROL_STREAM - Control overlays, aka streams.
 *
 * This IOCTL controls the overlay units of the svga device.
 * The SVGA overlay units करोes not work like regular hardware units in
 * that they करो not स्वतःmaticaly पढ़ो back the contents of the given dma
 * buffer. But instead only पढ़ो back क्रम each call to this ioctl, and
 * at any poपूर्णांक between this call being made and a following call that
 * either changes the buffer or disables the stream.
 */

/**
 * काष्ठा drm_vmw_rect
 *
 * Defines a rectangle. Used in the overlay ioctl to define
 * source and destination rectangle.
 */

काष्ठा drm_vmw_rect अणु
	__s32 x;
	__s32 y;
	__u32 w;
	__u32 h;
पूर्ण;

/**
 * काष्ठा drm_vmw_control_stream_arg
 *
 * @stream_id: Stearm to control
 * @enabled: If false all following arguments are ignored.
 * @handle: Handle to buffer क्रम getting data from.
 * @क्रमmat: Format of the overlay as understood by the host.
 * @width: Width of the overlay.
 * @height: Height of the overlay.
 * @size: Size of the overlay in bytes.
 * @pitch: Array of pitches, the two last are only used क्रम YUV12 क्रमmats.
 * @offset: Offset from start of dma buffer to overlay.
 * @src: Source rect, must be within the defined area above.
 * @dst: Destination rect, x and y may be negative.
 *
 * Argument to the DRM_VMW_CONTROL_STREAM Ioctl.
 */

काष्ठा drm_vmw_control_stream_arg अणु
	__u32 stream_id;
	__u32 enabled;

	__u32 flags;
	__u32 color_key;

	__u32 handle;
	__u32 offset;
	__s32 क्रमmat;
	__u32 size;
	__u32 width;
	__u32 height;
	__u32 pitch[3];

	__u32 pad64;
	काष्ठा drm_vmw_rect src;
	काष्ठा drm_vmw_rect dst;
पूर्ण;

/*************************************************************************/
/**
 * DRM_VMW_CURSOR_BYPASS - Give extra inक्रमmation about cursor bypass.
 *
 */

#घोषणा DRM_VMW_CURSOR_BYPASS_ALL    (1 << 0)
#घोषणा DRM_VMW_CURSOR_BYPASS_FLAGS       (1)

/**
 * काष्ठा drm_vmw_cursor_bypass_arg
 *
 * @flags: Flags.
 * @crtc_id: Crtc id, only used अगर DMR_CURSOR_BYPASS_ALL isn't passed.
 * @xpos: X position of cursor.
 * @ypos: Y position of cursor.
 * @xhot: X hotspot.
 * @yhot: Y hotspot.
 *
 * Argument to the DRM_VMW_CURSOR_BYPASS Ioctl.
 */

काष्ठा drm_vmw_cursor_bypass_arg अणु
	__u32 flags;
	__u32 crtc_id;
	__s32 xpos;
	__s32 ypos;
	__s32 xhot;
	__s32 yhot;
पूर्ण;

/*************************************************************************/
/**
 * DRM_VMW_CLAIM_STREAM - Claim a single stream.
 */

/**
 * काष्ठा drm_vmw_context_arg
 *
 * @stream_id: Device unique context ID.
 *
 * Output argument to the DRM_VMW_CREATE_CONTEXT Ioctl.
 * Input argument to the DRM_VMW_UNREF_CONTEXT Ioctl.
 */

काष्ठा drm_vmw_stream_arg अणु
	__u32 stream_id;
	__u32 pad64;
पूर्ण;

/*************************************************************************/
/**
 * DRM_VMW_UNREF_STREAM - Unclaim a stream.
 *
 * Return a single stream that was claimed by this process. Also makes
 * sure that the stream has been stopped.
 */

/*************************************************************************/
/**
 * DRM_VMW_GET_3D_CAP
 *
 * Read 3D capabilities from the FIFO
 *
 */

/**
 * काष्ठा drm_vmw_get_3d_cap_arg
 *
 * @buffer: Poपूर्णांकer to a buffer क्रम capability data, cast to an __u64
 * @size: Max size to copy
 *
 * Input argument to the DRM_VMW_GET_3D_CAP_IOCTL
 * ioctls.
 */

काष्ठा drm_vmw_get_3d_cap_arg अणु
	__u64 buffer;
	__u32 max_size;
	__u32 pad64;
पूर्ण;

/*************************************************************************/
/**
 * DRM_VMW_FENCE_WAIT
 *
 * Waits क्रम a fence object to संकेत. The रुको is पूर्णांकerruptible, so that
 * संकेतs may be delivered during the पूर्णांकerrupt. The रुको may समयout,
 * in which हाल the calls वापसs -EBUSY. If the रुको is restarted,
 * that is restarting without resetting @cookie_valid to zero,
 * the समयout is computed from the first call.
 *
 * The flags argument to the DRM_VMW_FENCE_WAIT ioctl indicates what to रुको
 * on:
 * DRM_VMW_FENCE_FLAG_EXEC: All commands ahead of the fence in the command
 * stream
 * have executed.
 * DRM_VMW_FENCE_FLAG_QUERY: All query results resulting from query finish
 * commands
 * in the buffer given to the EXECBUF ioctl वापसing the fence object handle
 * are available to user-space.
 *
 * DRM_VMW_WAIT_OPTION_UNREF: If this रुको option is given, and the
 * fenc रुको ioctl वापसs 0, the fence object has been unreferenced after
 * the रुको.
 */

#घोषणा DRM_VMW_FENCE_FLAG_EXEC   (1 << 0)
#घोषणा DRM_VMW_FENCE_FLAG_QUERY  (1 << 1)

#घोषणा DRM_VMW_WAIT_OPTION_UNREF (1 << 0)

/**
 * काष्ठा drm_vmw_fence_रुको_arg
 *
 * @handle: Fence object handle as वापसed by the DRM_VMW_EXECBUF ioctl.
 * @cookie_valid: Must be reset to 0 on first call. Left alone on restart.
 * @kernel_cookie: Set to 0 on first call. Left alone on restart.
 * @समयout_us: Wait समयout in microseconds. 0 क्रम indefinite समयout.
 * @lazy: Set to 1 अगर timing is not critical. Allow more than a kernel tick
 * beक्रमe वापसing.
 * @flags: Fence flags to रुको on.
 * @रुको_options: Options that control the behaviour of the रुको ioctl.
 *
 * Input argument to the DRM_VMW_FENCE_WAIT ioctl.
 */

काष्ठा drm_vmw_fence_रुको_arg अणु
	__u32 handle;
	__s32  cookie_valid;
	__u64 kernel_cookie;
	__u64 समयout_us;
	__s32 lazy;
	__s32 flags;
	__s32 रुको_options;
	__s32 pad64;
पूर्ण;

/*************************************************************************/
/**
 * DRM_VMW_FENCE_SIGNALED
 *
 * Checks अगर a fence object is संकेतed..
 */

/**
 * काष्ठा drm_vmw_fence_संकेतed_arg
 *
 * @handle: Fence object handle as वापसed by the DRM_VMW_EXECBUF ioctl.
 * @flags: Fence object flags input to DRM_VMW_FENCE_SIGNALED ioctl
 * @संकेतed: Out: Flags संकेतed.
 * @sequence: Out: Highest sequence passed so far. Can be used to संकेत the
 * EXEC flag of user-space fence objects.
 *
 * Input/Output argument to the DRM_VMW_FENCE_SIGNALED and DRM_VMW_FENCE_UNREF
 * ioctls.
 */

काष्ठा drm_vmw_fence_संकेतed_arg अणु
	 __u32 handle;
	 __u32 flags;
	 __s32 संकेतed;
	 __u32 passed_seqno;
	 __u32 संकेतed_flags;
	 __u32 pad64;
पूर्ण;

/*************************************************************************/
/**
 * DRM_VMW_FENCE_UNREF
 *
 * Unreferences a fence object, and causes it to be destroyed अगर there are no
 * other references to it.
 *
 */

/**
 * काष्ठा drm_vmw_fence_arg
 *
 * @handle: Fence object handle as वापसed by the DRM_VMW_EXECBUF ioctl.
 *
 * Input/Output argument to the DRM_VMW_FENCE_UNREF ioctl..
 */

काष्ठा drm_vmw_fence_arg अणु
	 __u32 handle;
	 __u32 pad64;
पूर्ण;


/*************************************************************************/
/**
 * DRM_VMW_FENCE_EVENT
 *
 * Queues an event on a fence to be delivered on the drm अक्षरacter device
 * when the fence has संकेतed the DRM_VMW_FENCE_FLAG_EXEC flag.
 * Optionally the approximate समय when the fence संकेतed is
 * given by the event.
 */

/*
 * The event type
 */
#घोषणा DRM_VMW_EVENT_FENCE_SIGNALED 0x80000000

काष्ठा drm_vmw_event_fence अणु
	काष्ठा drm_event base;
	__u64 user_data;
	__u32 tv_sec;
	__u32 tv_usec;
पूर्ण;

/*
 * Flags that may be given to the command.
 */
/* Request fence संकेतed समय on the event. */
#घोषणा DRM_VMW_FE_FLAG_REQ_TIME (1 << 0)

/**
 * काष्ठा drm_vmw_fence_event_arg
 *
 * @fence_rep: Poपूर्णांकer to fence_rep काष्ठाure cast to __u64 or 0 अगर
 * the fence is not supposed to be referenced by user-space.
 * @user_info: Info to be delivered with the event.
 * @handle: Attach the event to this fence only.
 * @flags: A set of flags as defined above.
 */
काष्ठा drm_vmw_fence_event_arg अणु
	__u64 fence_rep;
	__u64 user_data;
	__u32 handle;
	__u32 flags;
पूर्ण;


/*************************************************************************/
/**
 * DRM_VMW_PRESENT
 *
 * Executes an SVGA present on a given fb क्रम a given surface. The surface
 * is placed on the framebuffer. Cliprects are given relative to the given
 * poपूर्णांक (the poपूर्णांक disignated by dest_अणुx|yपूर्ण).
 *
 */

/**
 * काष्ठा drm_vmw_present_arg
 * @fb_id: framebuffer id to present / पढ़ो back from.
 * @sid: Surface id to present from.
 * @dest_x: X placement coordinate क्रम surface.
 * @dest_y: Y placement coordinate क्रम surface.
 * @clips_ptr: Poपूर्णांकer to an array of clip rects cast to an __u64.
 * @num_clips: Number of cliprects given relative to the framebuffer origin,
 * in the same coordinate space as the frame buffer.
 * @pad64: Unused 64-bit padding.
 *
 * Input argument to the DRM_VMW_PRESENT ioctl.
 */

काष्ठा drm_vmw_present_arg अणु
	__u32 fb_id;
	__u32 sid;
	__s32 dest_x;
	__s32 dest_y;
	__u64 clips_ptr;
	__u32 num_clips;
	__u32 pad64;
पूर्ण;


/*************************************************************************/
/**
 * DRM_VMW_PRESENT_READBACK
 *
 * Executes an SVGA present पढ़ोback from a given fb to the dma buffer
 * currently bound as the fb. If there is no dma buffer bound to the fb,
 * an error will be वापसed.
 *
 */

/**
 * काष्ठा drm_vmw_present_arg
 * @fb_id: fb_id to present / पढ़ो back from.
 * @num_clips: Number of cliprects.
 * @clips_ptr: Poपूर्णांकer to an array of clip rects cast to an __u64.
 * @fence_rep: Poपूर्णांकer to a काष्ठा drm_vmw_fence_rep, cast to an __u64.
 * If this member is शून्य, then the ioctl should not वापस a fence.
 */

काष्ठा drm_vmw_present_पढ़ोback_arg अणु
	 __u32 fb_id;
	 __u32 num_clips;
	 __u64 clips_ptr;
	 __u64 fence_rep;
पूर्ण;

/*************************************************************************/
/**
 * DRM_VMW_UPDATE_LAYOUT - Update layout
 *
 * Updates the preferred modes and connection status क्रम connectors. The
 * command consists of one drm_vmw_update_layout_arg poपूर्णांकing to an array
 * of num_outमाला_दो drm_vmw_rect's.
 */

/**
 * काष्ठा drm_vmw_update_layout_arg
 *
 * @num_outमाला_दो: number of active connectors
 * @rects: poपूर्णांकer to array of drm_vmw_rect cast to an __u64
 *
 * Input argument to the DRM_VMW_UPDATE_LAYOUT Ioctl.
 */
काष्ठा drm_vmw_update_layout_arg अणु
	__u32 num_outमाला_दो;
	__u32 pad64;
	__u64 rects;
पूर्ण;


/*************************************************************************/
/**
 * DRM_VMW_CREATE_SHADER - Create shader
 *
 * Creates a shader and optionally binds it to a dma buffer containing
 * the shader byte-code.
 */

/**
 * क्रमागत drm_vmw_shader_type - Shader types
 */
क्रमागत drm_vmw_shader_type अणु
	drm_vmw_shader_type_vs = 0,
	drm_vmw_shader_type_ps,
पूर्ण;


/**
 * काष्ठा drm_vmw_shader_create_arg
 *
 * @shader_type: Shader type of the shader to create.
 * @size: Size of the byte-code in bytes.
 * where the shader byte-code starts
 * @buffer_handle: Buffer handle identअगरying the buffer containing the
 * shader byte-code
 * @shader_handle: On successful completion contains a handle that
 * can be used to subsequently identअगरy the shader.
 * @offset: Offset in bytes पूर्णांकo the buffer given by @buffer_handle,
 *
 * Input / Output argument to the DRM_VMW_CREATE_SHADER Ioctl.
 */
काष्ठा drm_vmw_shader_create_arg अणु
	क्रमागत drm_vmw_shader_type shader_type;
	__u32 size;
	__u32 buffer_handle;
	__u32 shader_handle;
	__u64 offset;
पूर्ण;

/*************************************************************************/
/**
 * DRM_VMW_UNREF_SHADER - Unreferences a shader
 *
 * Destroys a user-space reference to a shader, optionally destroying
 * it.
 */

/**
 * काष्ठा drm_vmw_shader_arg
 *
 * @handle: Handle identअगरying the shader to destroy.
 *
 * Input argument to the DRM_VMW_UNREF_SHADER ioctl.
 */
काष्ठा drm_vmw_shader_arg अणु
	__u32 handle;
	__u32 pad64;
पूर्ण;

/*************************************************************************/
/**
 * DRM_VMW_GB_SURFACE_CREATE - Create a host guest-backed surface.
 *
 * Allocates a surface handle and queues a create surface command
 * क्रम the host on the first use of the surface. The surface ID can
 * be used as the surface ID in commands referencing the surface.
 */

/**
 * क्रमागत drm_vmw_surface_flags
 *
 * @drm_vmw_surface_flag_shareable:     Whether the surface is shareable
 * @drm_vmw_surface_flag_scanout:       Whether the surface is a scanout
 *                                      surface.
 * @drm_vmw_surface_flag_create_buffer: Create a backup buffer अगर none is
 *                                      given.
 * @drm_vmw_surface_flag_coherent:      Back surface with coherent memory.
 */
क्रमागत drm_vmw_surface_flags अणु
	drm_vmw_surface_flag_shareable = (1 << 0),
	drm_vmw_surface_flag_scanout = (1 << 1),
	drm_vmw_surface_flag_create_buffer = (1 << 2),
	drm_vmw_surface_flag_coherent = (1 << 3),
पूर्ण;

/**
 * काष्ठा drm_vmw_gb_surface_create_req
 *
 * @svga3d_flags:     SVGA3d surface flags क्रम the device.
 * @क्रमmat:           SVGA3d क्रमmat.
 * @mip_level:        Number of mip levels क्रम all faces.
 * @drm_surface_flags Flags as described above.
 * @multisample_count Future use. Set to 0.
 * @स्वतःgen_filter    Future use. Set to 0.
 * @buffer_handle     Buffer handle of backup buffer. SVGA3D_INVALID_ID
 *                    अगर none.
 * @base_size         Size of the base mip level क्रम all faces.
 * @array_size        Must be zero क्रम non-DX hardware, and अगर non-zero
 *                    svga3d_flags must have proper bind flags setup.
 *
 * Input argument to the  DRM_VMW_GB_SURFACE_CREATE Ioctl.
 * Part of output argument क्रम the DRM_VMW_GB_SURFACE_REF Ioctl.
 */
काष्ठा drm_vmw_gb_surface_create_req अणु
	__u32 svga3d_flags;
	__u32 क्रमmat;
	__u32 mip_levels;
	क्रमागत drm_vmw_surface_flags drm_surface_flags;
	__u32 multisample_count;
	__u32 स्वतःgen_filter;
	__u32 buffer_handle;
	__u32 array_size;
	काष्ठा drm_vmw_size base_size;
पूर्ण;

/**
 * काष्ठा drm_vmw_gb_surface_create_rep
 *
 * @handle:            Surface handle.
 * @backup_size:       Size of backup buffers क्रम this surface.
 * @buffer_handle:     Handle of backup buffer. SVGA3D_INVALID_ID अगर none.
 * @buffer_size:       Actual size of the buffer identअगरied by
 *                     @buffer_handle
 * @buffer_map_handle: Offset पूर्णांकo device address space क्रम the buffer
 *                     identअगरied by @buffer_handle.
 *
 * Part of output argument क्रम the DRM_VMW_GB_SURFACE_REF ioctl.
 * Output argument क्रम the DRM_VMW_GB_SURFACE_CREATE ioctl.
 */
काष्ठा drm_vmw_gb_surface_create_rep अणु
	__u32 handle;
	__u32 backup_size;
	__u32 buffer_handle;
	__u32 buffer_size;
	__u64 buffer_map_handle;
पूर्ण;

/**
 * जोड़ drm_vmw_gb_surface_create_arg
 *
 * @req: Input argument as described above.
 * @rep: Output argument as described above.
 *
 * Argument to the DRM_VMW_GB_SURFACE_CREATE ioctl.
 */
जोड़ drm_vmw_gb_surface_create_arg अणु
	काष्ठा drm_vmw_gb_surface_create_rep rep;
	काष्ठा drm_vmw_gb_surface_create_req req;
पूर्ण;

/*************************************************************************/
/**
 * DRM_VMW_GB_SURFACE_REF - Reference a host surface.
 *
 * Puts a reference on a host surface with a given handle, as previously
 * वापसed by the DRM_VMW_GB_SURFACE_CREATE ioctl.
 * A reference will make sure the surface isn't destroyed जबतक we hold
 * it and will allow the calling client to use the surface handle in
 * the command stream.
 *
 * On successful वापस, the Ioctl वापसs the surface inक्रमmation given
 * to and वापसed from the DRM_VMW_GB_SURFACE_CREATE ioctl.
 */

/**
 * काष्ठा drm_vmw_gb_surface_reference_arg
 *
 * @creq: The data used as input when the surface was created, as described
 *        above at "struct drm_vmw_gb_surface_create_req"
 * @crep: Additional data output when the surface was created, as described
 *        above at "struct drm_vmw_gb_surface_create_rep"
 *
 * Output Argument to the DRM_VMW_GB_SURFACE_REF ioctl.
 */
काष्ठा drm_vmw_gb_surface_ref_rep अणु
	काष्ठा drm_vmw_gb_surface_create_req creq;
	काष्ठा drm_vmw_gb_surface_create_rep crep;
पूर्ण;

/**
 * जोड़ drm_vmw_gb_surface_reference_arg
 *
 * @req: Input data as described above at "struct drm_vmw_surface_arg"
 * @rep: Output data as described above at "struct drm_vmw_gb_surface_ref_rep"
 *
 * Argument to the DRM_VMW_GB_SURFACE_REF Ioctl.
 */
जोड़ drm_vmw_gb_surface_reference_arg अणु
	काष्ठा drm_vmw_gb_surface_ref_rep rep;
	काष्ठा drm_vmw_surface_arg req;
पूर्ण;


/*************************************************************************/
/**
 * DRM_VMW_SYNCCPU - Sync a DMA buffer / MOB क्रम CPU access.
 *
 * Idles any previously submitted GPU operations on the buffer and
 * by शेष blocks command submissions that reference the buffer.
 * If the file descriptor used to grab a blocking CPU sync is बंदd, the
 * cpu sync is released.
 * The flags argument indicates how the grab / release operation should be
 * perक्रमmed:
 */

/**
 * क्रमागत drm_vmw_synccpu_flags - Synccpu flags:
 *
 * @drm_vmw_synccpu_पढ़ो: Sync क्रम पढ़ो. If sync is करोne क्रम पढ़ो only, it's a
 * hपूर्णांक to the kernel to allow command submissions that references the buffer
 * क्रम पढ़ो-only.
 * @drm_vmw_synccpu_ग_लिखो: Sync क्रम ग_लिखो. Block all command submissions
 * referencing this buffer.
 * @drm_vmw_synccpu_करोntblock: Dont रुको क्रम GPU idle, but rather वापस
 * -EBUSY should the buffer be busy.
 * @drm_vmw_synccpu_allow_cs: Allow command submission that touches the buffer
 * जबतक the buffer is synced क्रम CPU. This is similar to the GEM bo idle
 * behavior.
 */
क्रमागत drm_vmw_synccpu_flags अणु
	drm_vmw_synccpu_पढ़ो = (1 << 0),
	drm_vmw_synccpu_ग_लिखो = (1 << 1),
	drm_vmw_synccpu_करोntblock = (1 << 2),
	drm_vmw_synccpu_allow_cs = (1 << 3)
पूर्ण;

/**
 * क्रमागत drm_vmw_synccpu_op - Synccpu operations:
 *
 * @drm_vmw_synccpu_grab:    Grab the buffer क्रम CPU operations
 * @drm_vmw_synccpu_release: Release a previous grab.
 */
क्रमागत drm_vmw_synccpu_op अणु
	drm_vmw_synccpu_grab,
	drm_vmw_synccpu_release
पूर्ण;

/**
 * काष्ठा drm_vmw_synccpu_arg
 *
 * @op:			     The synccpu operation as described above.
 * @handle:		     Handle identअगरying the buffer object.
 * @flags:		     Flags as described above.
 */
काष्ठा drm_vmw_synccpu_arg अणु
	क्रमागत drm_vmw_synccpu_op op;
	क्रमागत drm_vmw_synccpu_flags flags;
	__u32 handle;
	__u32 pad64;
पूर्ण;

/*************************************************************************/
/**
 * DRM_VMW_CREATE_EXTENDED_CONTEXT - Create a host context.
 *
 * Allocates a device unique context id, and queues a create context command
 * क्रम the host. Does not रुको क्रम host completion.
 */
क्रमागत drm_vmw_extended_context अणु
	drm_vmw_context_legacy,
	drm_vmw_context_dx
पूर्ण;

/**
 * जोड़ drm_vmw_extended_context_arg
 *
 * @req: Context type.
 * @rep: Context identअगरier.
 *
 * Argument to the DRM_VMW_CREATE_EXTENDED_CONTEXT Ioctl.
 */
जोड़ drm_vmw_extended_context_arg अणु
	क्रमागत drm_vmw_extended_context req;
	काष्ठा drm_vmw_context_arg rep;
पूर्ण;

/*************************************************************************/
/*
 * DRM_VMW_HANDLE_CLOSE - Close a user-space handle and release its
 * underlying resource.
 *
 * Note that this ioctl is overlaid on the deprecated DRM_VMW_UNREF_DMABUF
 * Ioctl.
 */

/**
 * काष्ठा drm_vmw_handle_बंद_arg
 *
 * @handle: Handle to बंद.
 *
 * Argument to the DRM_VMW_HANDLE_CLOSE Ioctl.
 */
काष्ठा drm_vmw_handle_बंद_arg अणु
	__u32 handle;
	__u32 pad64;
पूर्ण;
#घोषणा drm_vmw_unref_dmabuf_arg drm_vmw_handle_बंद_arg

/*************************************************************************/
/**
 * DRM_VMW_GB_SURFACE_CREATE_EXT - Create a host guest-backed surface.
 *
 * Allocates a surface handle and queues a create surface command
 * क्रम the host on the first use of the surface. The surface ID can
 * be used as the surface ID in commands referencing the surface.
 *
 * This new command extends DRM_VMW_GB_SURFACE_CREATE by adding version
 * parameter and 64 bit svga flag.
 */

/**
 * क्रमागत drm_vmw_surface_version
 *
 * @drm_vmw_surface_gb_v1: Corresponds to current gb surface क्रमmat with
 * svga3d surface flags split पूर्णांकo 2, upper half and lower half.
 */
क्रमागत drm_vmw_surface_version अणु
	drm_vmw_gb_surface_v1,
पूर्ण;

/**
 * काष्ठा drm_vmw_gb_surface_create_ext_req
 *
 * @base: Surface create parameters.
 * @version: Version of surface create ioctl.
 * @svga3d_flags_upper_32_bits: Upper 32 bits of svga3d flags.
 * @multisample_pattern: Multisampling pattern when msaa is supported.
 * @quality_level: Precision settings क्रम each sample.
 * @buffer_byte_stride: Buffer byte stride.
 * @must_be_zero: Reserved क्रम future usage.
 *
 * Input argument to the  DRM_VMW_GB_SURFACE_CREATE_EXT Ioctl.
 * Part of output argument क्रम the DRM_VMW_GB_SURFACE_REF_EXT Ioctl.
 */
काष्ठा drm_vmw_gb_surface_create_ext_req अणु
	काष्ठा drm_vmw_gb_surface_create_req base;
	क्रमागत drm_vmw_surface_version version;
	__u32 svga3d_flags_upper_32_bits;
	__u32 multisample_pattern;
	__u32 quality_level;
	__u32 buffer_byte_stride;
	__u32 must_be_zero;
पूर्ण;

/**
 * जोड़ drm_vmw_gb_surface_create_ext_arg
 *
 * @req: Input argument as described above.
 * @rep: Output argument as described above.
 *
 * Argument to the DRM_VMW_GB_SURFACE_CREATE_EXT ioctl.
 */
जोड़ drm_vmw_gb_surface_create_ext_arg अणु
	काष्ठा drm_vmw_gb_surface_create_rep rep;
	काष्ठा drm_vmw_gb_surface_create_ext_req req;
पूर्ण;

/*************************************************************************/
/**
 * DRM_VMW_GB_SURFACE_REF_EXT - Reference a host surface.
 *
 * Puts a reference on a host surface with a given handle, as previously
 * वापसed by the DRM_VMW_GB_SURFACE_CREATE_EXT ioctl.
 * A reference will make sure the surface isn't destroyed जबतक we hold
 * it and will allow the calling client to use the surface handle in
 * the command stream.
 *
 * On successful वापस, the Ioctl वापसs the surface inक्रमmation given
 * to and वापसed from the DRM_VMW_GB_SURFACE_CREATE_EXT ioctl.
 */

/**
 * काष्ठा drm_vmw_gb_surface_ref_ext_rep
 *
 * @creq: The data used as input when the surface was created, as described
 *        above at "struct drm_vmw_gb_surface_create_ext_req"
 * @crep: Additional data output when the surface was created, as described
 *        above at "struct drm_vmw_gb_surface_create_rep"
 *
 * Output Argument to the DRM_VMW_GB_SURFACE_REF_EXT ioctl.
 */
काष्ठा drm_vmw_gb_surface_ref_ext_rep अणु
	काष्ठा drm_vmw_gb_surface_create_ext_req creq;
	काष्ठा drm_vmw_gb_surface_create_rep crep;
पूर्ण;

/**
 * जोड़ drm_vmw_gb_surface_reference_ext_arg
 *
 * @req: Input data as described above at "struct drm_vmw_surface_arg"
 * @rep: Output data as described above at
 *       "struct drm_vmw_gb_surface_ref_ext_rep"
 *
 * Argument to the DRM_VMW_GB_SURFACE_REF Ioctl.
 */
जोड़ drm_vmw_gb_surface_reference_ext_arg अणु
	काष्ठा drm_vmw_gb_surface_ref_ext_rep rep;
	काष्ठा drm_vmw_surface_arg req;
पूर्ण;

/**
 * काष्ठा drm_vmw_msg_arg
 *
 * @send: Poपूर्णांकer to user-space msg string (null terminated).
 * @receive: Poपूर्णांकer to user-space receive buffer.
 * @send_only: Boolean whether this is only sending or receiving too.
 *
 * Argument to the DRM_VMW_MSG ioctl.
 */
काष्ठा drm_vmw_msg_arg अणु
	__u64 send;
	__u64 receive;
	__s32 send_only;
	__u32 receive_len;
पूर्ण;

#अगर defined(__cplusplus)
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर
