<शैली गुरु>
/* r128_drm.h -- Public header क्रम the r128 driver -*- linux-c -*-
 * Created: Wed Apr  5 19:24:19 2000 by kevin@precisioninsight.com
 */
/*
 * Copyright 2000 Precision Insight, Inc., Cedar Park, Texas.
 * Copyright 2000 VA Linux Systems, Inc., Sunnyvale, Calअगरornia.
 * All rights reserved.
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
 * PRECISION INSIGHT AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 * Authors:
 *    Gareth Hughes <gareth@valinux.com>
 *    Kevin E. Martin <martin@valinux.com>
 */

#अगर_अघोषित __R128_DRM_H__
#घोषणा __R128_DRM_H__

#समावेश "drm.h"

#अगर defined(__cplusplus)
बाह्य "C" अणु
#पूर्ण_अगर

/* WARNING: If you change any of these defines, make sure to change the
 * defines in the X server file (r128_sarea.h)
 */
#अगर_अघोषित __R128_SAREA_DEFINES__
#घोषणा __R128_SAREA_DEFINES__

/* What needs to be changed क्रम the current vertex buffer?
 */
#घोषणा R128_UPLOAD_CONTEXT		0x001
#घोषणा R128_UPLOAD_SETUP		0x002
#घोषणा R128_UPLOAD_TEX0		0x004
#घोषणा R128_UPLOAD_TEX1		0x008
#घोषणा R128_UPLOAD_TEX0IMAGES		0x010
#घोषणा R128_UPLOAD_TEX1IMAGES		0x020
#घोषणा R128_UPLOAD_CORE		0x040
#घोषणा R128_UPLOAD_MASKS		0x080
#घोषणा R128_UPLOAD_WINDOW		0x100
#घोषणा R128_UPLOAD_CLIPRECTS		0x200	/* handled client-side */
#घोषणा R128_REQUIRE_QUIESCENCE		0x400
#घोषणा R128_UPLOAD_ALL			0x7ff

#घोषणा R128_FRONT			0x1
#घोषणा R128_BACK			0x2
#घोषणा R128_DEPTH			0x4

/* Primitive types
 */
#घोषणा R128_POINTS			0x1
#घोषणा R128_LINES			0x2
#घोषणा R128_LINE_STRIP			0x3
#घोषणा R128_TRIANGLES			0x4
#घोषणा R128_TRIANGLE_FAN		0x5
#घोषणा R128_TRIANGLE_STRIP		0x6

/* Vertex/indirect buffer size
 */
#घोषणा R128_BUFFER_SIZE		16384

/* Byte offsets क्रम indirect buffer data
 */
#घोषणा R128_INDEX_PRIM_OFFSET		20
#घोषणा R128_HOSTDATA_BLIT_OFFSET	32

/* Keep these small क्रम testing.
 */
#घोषणा R128_NR_SAREA_CLIPRECTS		12

/* There are 2 heaps (local/AGP).  Each region within a heap is a
 *  minimum of 64k, and there are at most 64 of them per heap.
 */
#घोषणा R128_LOCAL_TEX_HEAP		0
#घोषणा R128_AGP_TEX_HEAP		1
#घोषणा R128_NR_TEX_HEAPS		2
#घोषणा R128_NR_TEX_REGIONS		64
#घोषणा R128_LOG_TEX_GRANULARITY	16

#घोषणा R128_NR_CONTEXT_REGS		12

#घोषणा R128_MAX_TEXTURE_LEVELS		11
#घोषणा R128_MAX_TEXTURE_UNITS		2

#पूर्ण_अगर				/* __R128_SAREA_DEFINES__ */

प्रकार काष्ठा अणु
	/* Context state - can be written in one large chunk */
	अचिन्हित पूर्णांक dst_pitch_offset_c;
	अचिन्हित पूर्णांक dp_gui_master_cntl_c;
	अचिन्हित पूर्णांक sc_top_left_c;
	अचिन्हित पूर्णांक sc_bottom_right_c;
	अचिन्हित पूर्णांक z_offset_c;
	अचिन्हित पूर्णांक z_pitch_c;
	अचिन्हित पूर्णांक z_sten_cntl_c;
	अचिन्हित पूर्णांक tex_cntl_c;
	अचिन्हित पूर्णांक misc_3d_state_cntl_reg;
	अचिन्हित पूर्णांक texture_clr_cmp_clr_c;
	अचिन्हित पूर्णांक texture_clr_cmp_msk_c;
	अचिन्हित पूर्णांक fog_color_c;

	/* Texture state */
	अचिन्हित पूर्णांक tex_size_pitch_c;
	अचिन्हित पूर्णांक स्थिरant_color_c;

	/* Setup state */
	अचिन्हित पूर्णांक pm4_vc_fpu_setup;
	अचिन्हित पूर्णांक setup_cntl;

	/* Mask state */
	अचिन्हित पूर्णांक dp_ग_लिखो_mask;
	अचिन्हित पूर्णांक sten_ref_mask_c;
	अचिन्हित पूर्णांक plane_3d_mask_c;

	/* Winकरोw state */
	अचिन्हित पूर्णांक winकरोw_xy_offset;

	/* Core state */
	अचिन्हित पूर्णांक scale_3d_cntl;
पूर्ण drm_r128_context_regs_t;

/* Setup रेजिस्टरs क्रम each texture unit
 */
प्रकार काष्ठा अणु
	अचिन्हित पूर्णांक tex_cntl;
	अचिन्हित पूर्णांक tex_combine_cntl;
	अचिन्हित पूर्णांक tex_size_pitch;
	अचिन्हित पूर्णांक tex_offset[R128_MAX_TEXTURE_LEVELS];
	अचिन्हित पूर्णांक tex_border_color;
पूर्ण drm_r128_texture_regs_t;

प्रकार काष्ठा drm_r128_sarea अणु
	/* The channel क्रम communication of state inक्रमmation to the kernel
	 * on firing a vertex buffer.
	 */
	drm_r128_context_regs_t context_state;
	drm_r128_texture_regs_t tex_state[R128_MAX_TEXTURE_UNITS];
	अचिन्हित पूर्णांक dirty;
	अचिन्हित पूर्णांक vertsize;
	अचिन्हित पूर्णांक vc_क्रमmat;

	/* The current cliprects, or a subset thereof.
	 */
	काष्ठा drm_clip_rect boxes[R128_NR_SAREA_CLIPRECTS];
	अचिन्हित पूर्णांक nbox;

	/* Counters क्रम client-side throttling of rendering clients.
	 */
	अचिन्हित पूर्णांक last_frame;
	अचिन्हित पूर्णांक last_dispatch;

	काष्ठा drm_tex_region tex_list[R128_NR_TEX_HEAPS][R128_NR_TEX_REGIONS + 1];
	अचिन्हित पूर्णांक tex_age[R128_NR_TEX_HEAPS];
	पूर्णांक ctx_owner;
	पूर्णांक pfAllowPageFlip;	/* number of 3d winकरोws (0,1,2 or more) */
	पूर्णांक pfCurrentPage;	/* which buffer is being displayed? */
पूर्ण drm_r128_sarea_t;

/* WARNING: If you change any of these defines, make sure to change the
 * defines in the Xserver file (xf86drmR128.h)
 */

/* Rage 128 specअगरic ioctls
 * The device specअगरic ioctl range is 0x40 to 0x79.
 */
#घोषणा DRM_R128_INIT       0x00
#घोषणा DRM_R128_CCE_START  0x01
#घोषणा DRM_R128_CCE_STOP   0x02
#घोषणा DRM_R128_CCE_RESET  0x03
#घोषणा DRM_R128_CCE_IDLE   0x04
/* 0x05 not used */
#घोषणा DRM_R128_RESET      0x06
#घोषणा DRM_R128_SWAP       0x07
#घोषणा DRM_R128_CLEAR      0x08
#घोषणा DRM_R128_VERTEX     0x09
#घोषणा DRM_R128_INDICES    0x0a
#घोषणा DRM_R128_BLIT       0x0b
#घोषणा DRM_R128_DEPTH      0x0c
#घोषणा DRM_R128_STIPPLE    0x0d
/* 0x0e not used */
#घोषणा DRM_R128_INसूचीECT   0x0f
#घोषणा DRM_R128_FULLSCREEN 0x10
#घोषणा DRM_R128_CLEAR2     0x11
#घोषणा DRM_R128_GETPARAM   0x12
#घोषणा DRM_R128_FLIP       0x13

#घोषणा DRM_IOCTL_R128_INIT       DRM_IOW( DRM_COMMAND_BASE + DRM_R128_INIT, drm_r128_init_t)
#घोषणा DRM_IOCTL_R128_CCE_START  DRM_IO(  DRM_COMMAND_BASE + DRM_R128_CCE_START)
#घोषणा DRM_IOCTL_R128_CCE_STOP   DRM_IOW( DRM_COMMAND_BASE + DRM_R128_CCE_STOP, drm_r128_cce_stop_t)
#घोषणा DRM_IOCTL_R128_CCE_RESET  DRM_IO(  DRM_COMMAND_BASE + DRM_R128_CCE_RESET)
#घोषणा DRM_IOCTL_R128_CCE_IDLE   DRM_IO(  DRM_COMMAND_BASE + DRM_R128_CCE_IDLE)
/* 0x05 not used */
#घोषणा DRM_IOCTL_R128_RESET      DRM_IO(  DRM_COMMAND_BASE + DRM_R128_RESET)
#घोषणा DRM_IOCTL_R128_SWAP       DRM_IO(  DRM_COMMAND_BASE + DRM_R128_SWAP)
#घोषणा DRM_IOCTL_R128_CLEAR      DRM_IOW( DRM_COMMAND_BASE + DRM_R128_CLEAR, drm_r128_clear_t)
#घोषणा DRM_IOCTL_R128_VERTEX     DRM_IOW( DRM_COMMAND_BASE + DRM_R128_VERTEX, drm_r128_vertex_t)
#घोषणा DRM_IOCTL_R128_INDICES    DRM_IOW( DRM_COMMAND_BASE + DRM_R128_INDICES, drm_r128_indices_t)
#घोषणा DRM_IOCTL_R128_BLIT       DRM_IOW( DRM_COMMAND_BASE + DRM_R128_BLIT, drm_r128_blit_t)
#घोषणा DRM_IOCTL_R128_DEPTH      DRM_IOW( DRM_COMMAND_BASE + DRM_R128_DEPTH, drm_r128_depth_t)
#घोषणा DRM_IOCTL_R128_STIPPLE    DRM_IOW( DRM_COMMAND_BASE + DRM_R128_STIPPLE, drm_r128_stipple_t)
/* 0x0e not used */
#घोषणा DRM_IOCTL_R128_INसूचीECT   DRM_IOWR(DRM_COMMAND_BASE + DRM_R128_INसूचीECT, drm_r128_indirect_t)
#घोषणा DRM_IOCTL_R128_FULLSCREEN DRM_IOW( DRM_COMMAND_BASE + DRM_R128_FULLSCREEN, drm_r128_fullscreen_t)
#घोषणा DRM_IOCTL_R128_CLEAR2     DRM_IOW( DRM_COMMAND_BASE + DRM_R128_CLEAR2, drm_r128_clear2_t)
#घोषणा DRM_IOCTL_R128_GETPARAM   DRM_IOWR( DRM_COMMAND_BASE + DRM_R128_GETPARAM, drm_r128_getparam_t)
#घोषणा DRM_IOCTL_R128_FLIP       DRM_IO(  DRM_COMMAND_BASE + DRM_R128_FLIP)

प्रकार काष्ठा drm_r128_init अणु
	क्रमागत अणु
		R128_INIT_CCE = 0x01,
		R128_CLEANUP_CCE = 0x02
	पूर्ण func;
	अचिन्हित दीर्घ sarea_priv_offset;
	पूर्णांक is_pci;
	पूर्णांक cce_mode;
	पूर्णांक cce_secure;
	पूर्णांक ring_size;
	पूर्णांक usec_समयout;

	अचिन्हित पूर्णांक fb_bpp;
	अचिन्हित पूर्णांक front_offset, front_pitch;
	अचिन्हित पूर्णांक back_offset, back_pitch;
	अचिन्हित पूर्णांक depth_bpp;
	अचिन्हित पूर्णांक depth_offset, depth_pitch;
	अचिन्हित पूर्णांक span_offset;

	अचिन्हित दीर्घ fb_offset;
	अचिन्हित दीर्घ mmio_offset;
	अचिन्हित दीर्घ ring_offset;
	अचिन्हित दीर्घ ring_rptr_offset;
	अचिन्हित दीर्घ buffers_offset;
	अचिन्हित दीर्घ agp_textures_offset;
पूर्ण drm_r128_init_t;

प्रकार काष्ठा drm_r128_cce_stop अणु
	पूर्णांक flush;
	पूर्णांक idle;
पूर्ण drm_r128_cce_stop_t;

प्रकार काष्ठा drm_r128_clear अणु
	अचिन्हित पूर्णांक flags;
	अचिन्हित पूर्णांक clear_color;
	अचिन्हित पूर्णांक clear_depth;
	अचिन्हित पूर्णांक color_mask;
	अचिन्हित पूर्णांक depth_mask;
पूर्ण drm_r128_clear_t;

प्रकार काष्ठा drm_r128_vertex अणु
	पूर्णांक prim;
	पूर्णांक idx;		/* Index of vertex buffer */
	पूर्णांक count;		/* Number of vertices in buffer */
	पूर्णांक discard;		/* Client finished with buffer? */
पूर्ण drm_r128_vertex_t;

प्रकार काष्ठा drm_r128_indices अणु
	पूर्णांक prim;
	पूर्णांक idx;
	पूर्णांक start;
	पूर्णांक end;
	पूर्णांक discard;		/* Client finished with buffer? */
पूर्ण drm_r128_indices_t;

प्रकार काष्ठा drm_r128_blit अणु
	पूर्णांक idx;
	पूर्णांक pitch;
	पूर्णांक offset;
	पूर्णांक क्रमmat;
	अचिन्हित लघु x, y;
	अचिन्हित लघु width, height;
पूर्ण drm_r128_blit_t;

प्रकार काष्ठा drm_r128_depth अणु
	क्रमागत अणु
		R128_WRITE_SPAN = 0x01,
		R128_WRITE_PIXELS = 0x02,
		R128_READ_SPAN = 0x03,
		R128_READ_PIXELS = 0x04
	पूर्ण func;
	पूर्णांक n;
	पूर्णांक __user *x;
	पूर्णांक __user *y;
	अचिन्हित पूर्णांक __user *buffer;
	अचिन्हित अक्षर __user *mask;
पूर्ण drm_r128_depth_t;

प्रकार काष्ठा drm_r128_stipple अणु
	अचिन्हित पूर्णांक __user *mask;
पूर्ण drm_r128_stipple_t;

प्रकार काष्ठा drm_r128_indirect अणु
	पूर्णांक idx;
	पूर्णांक start;
	पूर्णांक end;
	पूर्णांक discard;
पूर्ण drm_r128_indirect_t;

प्रकार काष्ठा drm_r128_fullscreen अणु
	क्रमागत अणु
		R128_INIT_FULLSCREEN = 0x01,
		R128_CLEANUP_FULLSCREEN = 0x02
	पूर्ण func;
पूर्ण drm_r128_fullscreen_t;

/* 2.3: An ioctl to get parameters that aren't available to the 3d
 * client any other way.
 */
#घोषणा R128_PARAM_IRQ_NR            1

प्रकार काष्ठा drm_r128_getparam अणु
	पूर्णांक param;
	व्योम __user *value;
पूर्ण drm_r128_getparam_t;

#अगर defined(__cplusplus)
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर
