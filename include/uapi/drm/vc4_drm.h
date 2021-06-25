<शैली गुरु>
/*
 * Copyright तऊ 2014-2015 Broadcom
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

#अगर_अघोषित _UAPI_VC4_DRM_H_
#घोषणा _UAPI_VC4_DRM_H_

#समावेश "drm.h"

#अगर defined(__cplusplus)
बाह्य "C" अणु
#पूर्ण_अगर

#घोषणा DRM_VC4_SUBMIT_CL                         0x00
#घोषणा DRM_VC4_WAIT_SEQNO                        0x01
#घोषणा DRM_VC4_WAIT_BO                           0x02
#घोषणा DRM_VC4_CREATE_BO                         0x03
#घोषणा DRM_VC4_MMAP_BO                           0x04
#घोषणा DRM_VC4_CREATE_SHADER_BO                  0x05
#घोषणा DRM_VC4_GET_HANG_STATE                    0x06
#घोषणा DRM_VC4_GET_PARAM                         0x07
#घोषणा DRM_VC4_SET_TILING                        0x08
#घोषणा DRM_VC4_GET_TILING                        0x09
#घोषणा DRM_VC4_LABEL_BO                          0x0a
#घोषणा DRM_VC4_GEM_MADVISE                       0x0b
#घोषणा DRM_VC4_PERFMON_CREATE                    0x0c
#घोषणा DRM_VC4_PERFMON_DESTROY                   0x0d
#घोषणा DRM_VC4_PERFMON_GET_VALUES                0x0e

#घोषणा DRM_IOCTL_VC4_SUBMIT_CL           DRM_IOWR(DRM_COMMAND_BASE + DRM_VC4_SUBMIT_CL, काष्ठा drm_vc4_submit_cl)
#घोषणा DRM_IOCTL_VC4_WAIT_SEQNO          DRM_IOWR(DRM_COMMAND_BASE + DRM_VC4_WAIT_SEQNO, काष्ठा drm_vc4_रुको_seqno)
#घोषणा DRM_IOCTL_VC4_WAIT_BO             DRM_IOWR(DRM_COMMAND_BASE + DRM_VC4_WAIT_BO, काष्ठा drm_vc4_रुको_bo)
#घोषणा DRM_IOCTL_VC4_CREATE_BO           DRM_IOWR(DRM_COMMAND_BASE + DRM_VC4_CREATE_BO, काष्ठा drm_vc4_create_bo)
#घोषणा DRM_IOCTL_VC4_MMAP_BO             DRM_IOWR(DRM_COMMAND_BASE + DRM_VC4_MMAP_BO, काष्ठा drm_vc4_mmap_bo)
#घोषणा DRM_IOCTL_VC4_CREATE_SHADER_BO    DRM_IOWR(DRM_COMMAND_BASE + DRM_VC4_CREATE_SHADER_BO, काष्ठा drm_vc4_create_shader_bo)
#घोषणा DRM_IOCTL_VC4_GET_HANG_STATE      DRM_IOWR(DRM_COMMAND_BASE + DRM_VC4_GET_HANG_STATE, काष्ठा drm_vc4_get_hang_state)
#घोषणा DRM_IOCTL_VC4_GET_PARAM           DRM_IOWR(DRM_COMMAND_BASE + DRM_VC4_GET_PARAM, काष्ठा drm_vc4_get_param)
#घोषणा DRM_IOCTL_VC4_SET_TILING          DRM_IOWR(DRM_COMMAND_BASE + DRM_VC4_SET_TILING, काष्ठा drm_vc4_set_tiling)
#घोषणा DRM_IOCTL_VC4_GET_TILING          DRM_IOWR(DRM_COMMAND_BASE + DRM_VC4_GET_TILING, काष्ठा drm_vc4_get_tiling)
#घोषणा DRM_IOCTL_VC4_LABEL_BO            DRM_IOWR(DRM_COMMAND_BASE + DRM_VC4_LABEL_BO, काष्ठा drm_vc4_label_bo)
#घोषणा DRM_IOCTL_VC4_GEM_MADVISE         DRM_IOWR(DRM_COMMAND_BASE + DRM_VC4_GEM_MADVISE, काष्ठा drm_vc4_gem_madvise)
#घोषणा DRM_IOCTL_VC4_PERFMON_CREATE      DRM_IOWR(DRM_COMMAND_BASE + DRM_VC4_PERFMON_CREATE, काष्ठा drm_vc4_perfmon_create)
#घोषणा DRM_IOCTL_VC4_PERFMON_DESTROY     DRM_IOWR(DRM_COMMAND_BASE + DRM_VC4_PERFMON_DESTROY, काष्ठा drm_vc4_perfmon_destroy)
#घोषणा DRM_IOCTL_VC4_PERFMON_GET_VALUES  DRM_IOWR(DRM_COMMAND_BASE + DRM_VC4_PERFMON_GET_VALUES, काष्ठा drm_vc4_perfmon_get_values)

काष्ठा drm_vc4_submit_rcl_surface अणु
	__u32 hindex; /* Handle index, or ~0 अगर not present. */
	__u32 offset; /* Offset to start of buffer. */
	/*
	 * Bits क्रम either render config (color_ग_लिखो) or load/store packet.
	 * Bits should all be 0 क्रम MSAA load/stores.
	 */
	__u16 bits;

#घोषणा VC4_SUBMIT_RCL_SURFACE_READ_IS_FULL_RES		(1 << 0)
	__u16 flags;
पूर्ण;

/**
 * काष्ठा drm_vc4_submit_cl - ioctl argument क्रम submitting commands to the 3D
 * engine.
 *
 * Drivers typically use GPU BOs to store batchbuffers / command lists and
 * their associated state.  However, because the VC4 lacks an MMU, we have to
 * करो validation of memory accesses by the GPU commands.  If we were to store
 * our commands in BOs, we'd need to करो uncached पढ़ोback from them to करो the
 * validation process, which is too expensive.  Instead, userspace accumulates
 * commands and associated state in plain memory, then the kernel copies the
 * data to its own address space, and then validates and stores it in a GPU
 * BO.
 */
काष्ठा drm_vc4_submit_cl अणु
	/* Poपूर्णांकer to the binner command list.
	 *
	 * This is the first set of commands executed, which runs the
	 * coordinate shader to determine where primitives land on the screen,
	 * then ग_लिखोs out the state updates and draw calls necessary per tile
	 * to the tile allocation BO.
	 */
	__u64 bin_cl;

	/* Poपूर्णांकer to the shader records.
	 *
	 * Shader records are the काष्ठाures पढ़ो by the hardware that contain
	 * poपूर्णांकers to unअगरorms, shaders, and vertex attributes.  The
	 * reference to the shader record has enough inक्रमmation to determine
	 * how many poपूर्णांकers are necessary (fixed number क्रम shaders/unअगरorms,
	 * and an attribute count), so those BO indices पूर्णांकo bo_handles are
	 * just stored as __u32s beक्रमe each shader record passed in.
	 */
	__u64 shader_rec;

	/* Poपूर्णांकer to unअगरorm data and texture handles क्रम the textures
	 * referenced by the shader.
	 *
	 * For each shader state record, there is a set of unअगरorm data in the
	 * order referenced by the record (FS, VS, then CS).  Each set of
	 * unअगरorm data has a __u32 index पूर्णांकo bo_handles per texture
	 * sample operation, in the order the QPU_W_TMUn_S ग_लिखोs appear in
	 * the program.  Following the texture BO handle indices is the actual
	 * unअगरorm data.
	 *
	 * The inभागidual unअगरorm state blocks करोn't have sizes passed in,
	 * because the kernel has to determine the sizes anyway during shader
	 * code validation.
	 */
	__u64 unअगरorms;
	__u64 bo_handles;

	/* Size in bytes of the binner command list. */
	__u32 bin_cl_size;
	/* Size in bytes of the set of shader records. */
	__u32 shader_rec_size;
	/* Number of shader records.
	 *
	 * This could just be computed from the contents of shader_records and
	 * the address bits of references to them from the bin CL, but it
	 * keeps the kernel from having to resize some allocations it makes.
	 */
	__u32 shader_rec_count;
	/* Size in bytes of the unअगरorm state. */
	__u32 unअगरorms_size;

	/* Number of BO handles passed in (size is that बार 4). */
	__u32 bo_handle_count;

	/* RCL setup: */
	__u16 width;
	__u16 height;
	__u8 min_x_tile;
	__u8 min_y_tile;
	__u8 max_x_tile;
	__u8 max_y_tile;
	काष्ठा drm_vc4_submit_rcl_surface color_पढ़ो;
	काष्ठा drm_vc4_submit_rcl_surface color_ग_लिखो;
	काष्ठा drm_vc4_submit_rcl_surface zs_पढ़ो;
	काष्ठा drm_vc4_submit_rcl_surface zs_ग_लिखो;
	काष्ठा drm_vc4_submit_rcl_surface msaa_color_ग_लिखो;
	काष्ठा drm_vc4_submit_rcl_surface msaa_zs_ग_लिखो;
	__u32 clear_color[2];
	__u32 clear_z;
	__u8 clear_s;

	__u32 pad:24;

#घोषणा VC4_SUBMIT_CL_USE_CLEAR_COLOR			(1 << 0)
/* By शेष, the kernel माला_लो to choose the order that the tiles are
 * rendered in.  If this is set, then the tiles will be rendered in a
 * raster order, with the right-to-left vs left-to-right and
 * top-to-bottom vs bottom-to-top dictated by
 * VC4_SUBMIT_CL_RCL_ORDER_INCREASING_*.  This allows overlapping
 * blits to be implemented using the 3D engine.
 */
#घोषणा VC4_SUBMIT_CL_FIXED_RCL_ORDER			(1 << 1)
#घोषणा VC4_SUBMIT_CL_RCL_ORDER_INCREASING_X		(1 << 2)
#घोषणा VC4_SUBMIT_CL_RCL_ORDER_INCREASING_Y		(1 << 3)
	__u32 flags;

	/* Returned value of the seqno of this render job (क्रम the
	 * रुको ioctl).
	 */
	__u64 seqno;

	/* ID of the perfmon to attach to this job. 0 means no perfmon. */
	__u32 perfmonid;

	/* Syncobj handle to रुको on. If set, processing of this render job
	 * will not start until the syncobj is संकेतed. 0 means ignore.
	 */
	__u32 in_sync;

	/* Syncobj handle to export fence to. If set, the fence in the syncobj
	 * will be replaced with a fence that संकेतs upon completion of this
	 * render job. 0 means ignore.
	 */
	__u32 out_sync;

	__u32 pad2;
पूर्ण;

/**
 * काष्ठा drm_vc4_रुको_seqno - ioctl argument क्रम रुकोing क्रम
 * DRM_VC4_SUBMIT_CL completion using its वापसed seqno.
 *
 * समयout_ns is the समयout in nanoseconds, where "0" means "करोn't
 * block, just वापस the status."
 */
काष्ठा drm_vc4_रुको_seqno अणु
	__u64 seqno;
	__u64 समयout_ns;
पूर्ण;

/**
 * काष्ठा drm_vc4_रुको_bo - ioctl argument क्रम रुकोing क्रम
 * completion of the last DRM_VC4_SUBMIT_CL on a BO.
 *
 * This is useful क्रम हालs where multiple processes might be
 * rendering to a BO and you want to रुको क्रम all rendering to be
 * completed.
 */
काष्ठा drm_vc4_रुको_bo अणु
	__u32 handle;
	__u32 pad;
	__u64 समयout_ns;
पूर्ण;

/**
 * काष्ठा drm_vc4_create_bo - ioctl argument क्रम creating VC4 BOs.
 *
 * There are currently no values क्रम the flags argument, but it may be
 * used in a future extension.
 */
काष्ठा drm_vc4_create_bo अणु
	__u32 size;
	__u32 flags;
	/** Returned GEM handle क्रम the BO. */
	__u32 handle;
	__u32 pad;
पूर्ण;

/**
 * काष्ठा drm_vc4_mmap_bo - ioctl argument क्रम mapping VC4 BOs.
 *
 * This करोesn't actually perक्रमm an mmap.  Instead, it वापसs the
 * offset you need to use in an mmap on the DRM device node.  This
 * means that tools like valgrind end up knowing about the mapped
 * memory.
 *
 * There are currently no values क्रम the flags argument, but it may be
 * used in a future extension.
 */
काष्ठा drm_vc4_mmap_bo अणु
	/** Handle क्रम the object being mapped. */
	__u32 handle;
	__u32 flags;
	/** offset पूर्णांकo the drm node to use क्रम subsequent mmap call. */
	__u64 offset;
पूर्ण;

/**
 * काष्ठा drm_vc4_create_shader_bo - ioctl argument क्रम creating VC4
 * shader BOs.
 *
 * Since allowing a shader to be overwritten जबतक it's also being
 * executed from would allow privlege escalation, shaders must be
 * created using this ioctl, and they can't be mmapped later.
 */
काष्ठा drm_vc4_create_shader_bo अणु
	/* Size of the data argument. */
	__u32 size;
	/* Flags, currently must be 0. */
	__u32 flags;

	/* Poपूर्णांकer to the data. */
	__u64 data;

	/** Returned GEM handle क्रम the BO. */
	__u32 handle;
	/* Pad, must be 0. */
	__u32 pad;
पूर्ण;

काष्ठा drm_vc4_get_hang_state_bo अणु
	__u32 handle;
	__u32 paddr;
	__u32 size;
	__u32 pad;
पूर्ण;

/**
 * काष्ठा drm_vc4_hang_state - ioctl argument क्रम collecting state
 * from a GPU hang क्रम analysis.
*/
काष्ठा drm_vc4_get_hang_state अणु
	/** Poपूर्णांकer to array of काष्ठा drm_vc4_get_hang_state_bo. */
	__u64 bo;
	/**
	 * On input, the size of the bo array.  Output is the number
	 * of bos to be वापसed.
	 */
	__u32 bo_count;

	__u32 start_bin, start_render;

	__u32 ct0ca, ct0ea;
	__u32 ct1ca, ct1ea;
	__u32 ct0cs, ct1cs;
	__u32 ct0ra0, ct1ra0;

	__u32 bpca, bpcs;
	__u32 bpoa, bpos;

	__u32 vpmbase;

	__u32 dbge;
	__u32 fdbgo;
	__u32 fdbgb;
	__u32 fdbgr;
	__u32 fdbgs;
	__u32 errstat;

	/* Pad that we may save more रेजिस्टरs पूर्णांकo in the future. */
	__u32 pad[16];
पूर्ण;

#घोषणा DRM_VC4_PARAM_V3D_IDENT0		0
#घोषणा DRM_VC4_PARAM_V3D_IDENT1		1
#घोषणा DRM_VC4_PARAM_V3D_IDENT2		2
#घोषणा DRM_VC4_PARAM_SUPPORTS_BRANCHES		3
#घोषणा DRM_VC4_PARAM_SUPPORTS_ETC1		4
#घोषणा DRM_VC4_PARAM_SUPPORTS_THREADED_FS	5
#घोषणा DRM_VC4_PARAM_SUPPORTS_FIXED_RCL_ORDER	6
#घोषणा DRM_VC4_PARAM_SUPPORTS_MADVISE		7
#घोषणा DRM_VC4_PARAM_SUPPORTS_PERFMON		8

काष्ठा drm_vc4_get_param अणु
	__u32 param;
	__u32 pad;
	__u64 value;
पूर्ण;

काष्ठा drm_vc4_get_tiling अणु
	__u32 handle;
	__u32 flags;
	__u64 modअगरier;
पूर्ण;

काष्ठा drm_vc4_set_tiling अणु
	__u32 handle;
	__u32 flags;
	__u64 modअगरier;
पूर्ण;

/**
 * काष्ठा drm_vc4_label_bo - Attach a name to a BO क्रम debug purposes.
 */
काष्ठा drm_vc4_label_bo अणु
	__u32 handle;
	__u32 len;
	__u64 name;
पूर्ण;

/*
 * States prefixed with '__' are पूर्णांकernal states and cannot be passed to the
 * DRM_IOCTL_VC4_GEM_MADVISE ioctl.
 */
#घोषणा VC4_MADV_WILLNEED			0
#घोषणा VC4_MADV_DONTNEED			1
#घोषणा __VC4_MADV_PURGED			2
#घोषणा __VC4_MADV_NOTSUPP			3

काष्ठा drm_vc4_gem_madvise अणु
	__u32 handle;
	__u32 madv;
	__u32 retained;
	__u32 pad;
पूर्ण;

क्रमागत अणु
	VC4_PERFCNT_FEP_VALID_PRIMS_NO_RENDER,
	VC4_PERFCNT_FEP_VALID_PRIMS_RENDER,
	VC4_PERFCNT_FEP_CLIPPED_QUADS,
	VC4_PERFCNT_FEP_VALID_QUADS,
	VC4_PERFCNT_TLB_QUADS_NOT_PASSING_STENCIL,
	VC4_PERFCNT_TLB_QUADS_NOT_PASSING_Z_AND_STENCIL,
	VC4_PERFCNT_TLB_QUADS_PASSING_Z_AND_STENCIL,
	VC4_PERFCNT_TLB_QUADS_ZERO_COVERAGE,
	VC4_PERFCNT_TLB_QUADS_NON_ZERO_COVERAGE,
	VC4_PERFCNT_TLB_QUADS_WRITTEN_TO_COLOR_BUF,
	VC4_PERFCNT_PLB_PRIMS_OUTSIDE_VIEWPORT,
	VC4_PERFCNT_PLB_PRIMS_NEED_CLIPPING,
	VC4_PERFCNT_PSE_PRIMS_REVERSED,
	VC4_PERFCNT_QPU_TOTAL_IDLE_CYCLES,
	VC4_PERFCNT_QPU_TOTAL_CLK_CYCLES_VERTEX_COORD_SHADING,
	VC4_PERFCNT_QPU_TOTAL_CLK_CYCLES_FRAGMENT_SHADING,
	VC4_PERFCNT_QPU_TOTAL_CLK_CYCLES_EXEC_VALID_INST,
	VC4_PERFCNT_QPU_TOTAL_CLK_CYCLES_WAITING_TMUS,
	VC4_PERFCNT_QPU_TOTAL_CLK_CYCLES_WAITING_SCOREBOARD,
	VC4_PERFCNT_QPU_TOTAL_CLK_CYCLES_WAITING_VARYINGS,
	VC4_PERFCNT_QPU_TOTAL_INST_CACHE_HIT,
	VC4_PERFCNT_QPU_TOTAL_INST_CACHE_MISS,
	VC4_PERFCNT_QPU_TOTAL_UNIFORM_CACHE_HIT,
	VC4_PERFCNT_QPU_TOTAL_UNIFORM_CACHE_MISS,
	VC4_PERFCNT_TMU_TOTAL_TEXT_QUADS_PROCESSED,
	VC4_PERFCNT_TMU_TOTAL_TEXT_CACHE_MISS,
	VC4_PERFCNT_VPM_TOTAL_CLK_CYCLES_VDW_STALLED,
	VC4_PERFCNT_VPM_TOTAL_CLK_CYCLES_VCD_STALLED,
	VC4_PERFCNT_L2C_TOTAL_L2_CACHE_HIT,
	VC4_PERFCNT_L2C_TOTAL_L2_CACHE_MISS,
	VC4_PERFCNT_NUM_EVENTS,
पूर्ण;

#घोषणा DRM_VC4_MAX_PERF_COUNTERS	16

काष्ठा drm_vc4_perfmon_create अणु
	__u32 id;
	__u32 ncounters;
	__u8 events[DRM_VC4_MAX_PERF_COUNTERS];
पूर्ण;

काष्ठा drm_vc4_perfmon_destroy अणु
	__u32 id;
पूर्ण;

/*
 * Returns the values of the perक्रमmance counters tracked by this
 * perfmon (as an array of ncounters u64 values).
 *
 * No implicit synchronization is perक्रमmed, so the user has to
 * guarantee that any jobs using this perfmon have alपढ़ोy been
 * completed  (probably by blocking on the seqno वापसed by the
 * last exec that used the perfmon).
 */
काष्ठा drm_vc4_perfmon_get_values अणु
	__u32 id;
	__u64 values_ptr;
पूर्ण;

#अगर defined(__cplusplus)
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* _UAPI_VC4_DRM_H_ */
