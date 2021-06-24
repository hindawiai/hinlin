<शैली गुरु>
/* mga_drm.h -- Public header क्रम the Matrox g200/g400 driver -*- linux-c -*-
 * Created: Tue Jan 25 01:50:01 1999 by jharपंचांगann@precisioninsight.com
 *
 * Copyright 1999 Precision Insight, Inc., Cedar Park, Texas.
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
 * VA LINUX SYSTEMS AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Authors:
 *    Jeff Harपंचांगann <jharपंचांगann@valinux.com>
 *    Keith Whitwell <keith@tungstengraphics.com>
 *
 * Rewritten by:
 *    Gareth Hughes <gareth@valinux.com>
 */

#अगर_अघोषित __MGA_DRM_H__
#घोषणा __MGA_DRM_H__

#समावेश "drm.h"

#अगर defined(__cplusplus)
बाह्य "C" अणु
#पूर्ण_अगर

/* WARNING: If you change any of these defines, make sure to change the
 * defines in the Xserver file (mga_sarea.h)
 */

#अगर_अघोषित __MGA_SAREA_DEFINES__
#घोषणा __MGA_SAREA_DEFINES__

/* WARP pipe flags
 */
#घोषणा MGA_F			0x1	/* fog */
#घोषणा MGA_A			0x2	/* alpha */
#घोषणा MGA_S			0x4	/* specular */
#घोषणा MGA_T2			0x8	/* multitexture */

#घोषणा MGA_WARP_TGZ		0
#घोषणा MGA_WARP_TGZF		(MGA_F)
#घोषणा MGA_WARP_TGZA		(MGA_A)
#घोषणा MGA_WARP_TGZAF		(MGA_F|MGA_A)
#घोषणा MGA_WARP_TGZS		(MGA_S)
#घोषणा MGA_WARP_TGZSF		(MGA_S|MGA_F)
#घोषणा MGA_WARP_TGZSA		(MGA_S|MGA_A)
#घोषणा MGA_WARP_TGZSAF		(MGA_S|MGA_F|MGA_A)
#घोषणा MGA_WARP_T2GZ		(MGA_T2)
#घोषणा MGA_WARP_T2GZF		(MGA_T2|MGA_F)
#घोषणा MGA_WARP_T2GZA		(MGA_T2|MGA_A)
#घोषणा MGA_WARP_T2GZAF		(MGA_T2|MGA_A|MGA_F)
#घोषणा MGA_WARP_T2GZS		(MGA_T2|MGA_S)
#घोषणा MGA_WARP_T2GZSF		(MGA_T2|MGA_S|MGA_F)
#घोषणा MGA_WARP_T2GZSA		(MGA_T2|MGA_S|MGA_A)
#घोषणा MGA_WARP_T2GZSAF	(MGA_T2|MGA_S|MGA_F|MGA_A)

#घोषणा MGA_MAX_G200_PIPES	8	/* no multitex */
#घोषणा MGA_MAX_G400_PIPES	16
#घोषणा MGA_MAX_WARP_PIPES	MGA_MAX_G400_PIPES
#घोषणा MGA_WARP_UCODE_SIZE	32768	/* in bytes */

#घोषणा MGA_CARD_TYPE_G200	1
#घोषणा MGA_CARD_TYPE_G400	2
#घोषणा MGA_CARD_TYPE_G450	3	/* not currently used */
#घोषणा MGA_CARD_TYPE_G550	4

#घोषणा MGA_FRONT		0x1
#घोषणा MGA_BACK		0x2
#घोषणा MGA_DEPTH		0x4

/* What needs to be changed क्रम the current vertex dma buffer?
 */
#घोषणा MGA_UPLOAD_CONTEXT	0x1
#घोषणा MGA_UPLOAD_TEX0		0x2
#घोषणा MGA_UPLOAD_TEX1		0x4
#घोषणा MGA_UPLOAD_PIPE		0x8
#घोषणा MGA_UPLOAD_TEX0IMAGE	0x10	/* handled client-side */
#घोषणा MGA_UPLOAD_TEX1IMAGE	0x20	/* handled client-side */
#घोषणा MGA_UPLOAD_2D		0x40
#घोषणा MGA_WAIT_AGE		0x80	/* handled client-side */
#घोषणा MGA_UPLOAD_CLIPRECTS	0x100	/* handled client-side */
#अगर 0
#घोषणा MGA_DMA_FLUSH		0x200	/* set when someone माला_लो the lock
					   quiescent */
#पूर्ण_अगर

/* 32 buffers of 64k each, total 2 meg.
 */
#घोषणा MGA_BUFFER_SIZE		(1 << 16)
#घोषणा MGA_NUM_BUFFERS		128

/* Keep these small क्रम testing.
 */
#घोषणा MGA_NR_SAREA_CLIPRECTS	8

/* 2 heaps (1 क्रम card, 1 क्रम agp), each भागided पूर्णांकo up to 128
 * regions, subject to a minimum region size of (1<<16) == 64k.
 *
 * Clients may subभागide regions पूर्णांकernally, but when sharing between
 * clients, the region size is the minimum granularity.
 */

#घोषणा MGA_CARD_HEAP			0
#घोषणा MGA_AGP_HEAP			1
#घोषणा MGA_NR_TEX_HEAPS		2
#घोषणा MGA_NR_TEX_REGIONS		16
#घोषणा MGA_LOG_MIN_TEX_REGION_SIZE	16

#घोषणा  DRM_MGA_IDLE_RETRY          2048

#पूर्ण_अगर				/* __MGA_SAREA_DEFINES__ */

/* Setup रेजिस्टरs क्रम 3D context
 */
प्रकार काष्ठा अणु
	अचिन्हित पूर्णांक dstorg;
	अचिन्हित पूर्णांक maccess;
	अचिन्हित पूर्णांक plnwt;
	अचिन्हित पूर्णांक dwgctl;
	अचिन्हित पूर्णांक alphactrl;
	अचिन्हित पूर्णांक fogcolor;
	अचिन्हित पूर्णांक wflag;
	अचिन्हित पूर्णांक tdualstage0;
	अचिन्हित पूर्णांक tdualstage1;
	अचिन्हित पूर्णांक fcol;
	अचिन्हित पूर्णांक stencil;
	अचिन्हित पूर्णांक stencilctl;
पूर्ण drm_mga_context_regs_t;

/* Setup रेजिस्टरs क्रम 2D, X server
 */
प्रकार काष्ठा अणु
	अचिन्हित पूर्णांक pitch;
पूर्ण drm_mga_server_regs_t;

/* Setup रेजिस्टरs क्रम each texture unit
 */
प्रकार काष्ठा अणु
	अचिन्हित पूर्णांक texctl;
	अचिन्हित पूर्णांक texctl2;
	अचिन्हित पूर्णांक texfilter;
	अचिन्हित पूर्णांक texbordercol;
	अचिन्हित पूर्णांक texorg;
	अचिन्हित पूर्णांक texwidth;
	अचिन्हित पूर्णांक texheight;
	अचिन्हित पूर्णांक texorg1;
	अचिन्हित पूर्णांक texorg2;
	अचिन्हित पूर्णांक texorg3;
	अचिन्हित पूर्णांक texorg4;
पूर्ण drm_mga_texture_regs_t;

/* General aging mechanism
 */
प्रकार काष्ठा अणु
	अचिन्हित पूर्णांक head;	/* Position of head poपूर्णांकer          */
	अचिन्हित पूर्णांक wrap;	/* Primary DMA wrap count            */
पूर्ण drm_mga_age_t;

प्रकार काष्ठा _drm_mga_sarea अणु
	/* The channel क्रम communication of state inक्रमmation to the kernel
	 * on firing a vertex dma buffer.
	 */
	drm_mga_context_regs_t context_state;
	drm_mga_server_regs_t server_state;
	drm_mga_texture_regs_t tex_state[2];
	अचिन्हित पूर्णांक warp_pipe;
	अचिन्हित पूर्णांक dirty;
	अचिन्हित पूर्णांक vertsize;

	/* The current cliprects, or a subset thereof.
	 */
	काष्ठा drm_clip_rect boxes[MGA_NR_SAREA_CLIPRECTS];
	अचिन्हित पूर्णांक nbox;

	/* Inक्रमmation about the most recently used 3d drawable.  The
	 * client fills in the req_* fields, the server fills in the
	 * exported_ fields and माला_दो the cliprects पूर्णांकo boxes, above.
	 *
	 * The client clears the exported_drawable field beक्रमe
	 * clobbering the boxes data.
	 */
	अचिन्हित पूर्णांक req_drawable;	/* the X drawable id */
	अचिन्हित पूर्णांक req_draw_buffer;	/* MGA_FRONT or MGA_BACK */

	अचिन्हित पूर्णांक exported_drawable;
	अचिन्हित पूर्णांक exported_index;
	अचिन्हित पूर्णांक exported_stamp;
	अचिन्हित पूर्णांक exported_buffers;
	अचिन्हित पूर्णांक exported_nfront;
	अचिन्हित पूर्णांक exported_nback;
	पूर्णांक exported_back_x, exported_front_x, exported_w;
	पूर्णांक exported_back_y, exported_front_y, exported_h;
	काष्ठा drm_clip_rect exported_boxes[MGA_NR_SAREA_CLIPRECTS];

	/* Counters क्रम aging textures and क्रम client-side throttling.
	 */
	अचिन्हित पूर्णांक status[4];
	अचिन्हित पूर्णांक last_wrap;

	drm_mga_age_t last_frame;
	अचिन्हित पूर्णांक last_enqueue;	/* last समय a buffer was enqueued */
	अचिन्हित पूर्णांक last_dispatch;	/* age of the most recently dispatched buffer */
	अचिन्हित पूर्णांक last_quiescent;	/*  */

	/* LRU lists क्रम texture memory in agp space and on the card.
	 */
	काष्ठा drm_tex_region texList[MGA_NR_TEX_HEAPS][MGA_NR_TEX_REGIONS + 1];
	अचिन्हित पूर्णांक texAge[MGA_NR_TEX_HEAPS];

	/* Mechanism to validate card state.
	 */
	पूर्णांक ctxOwner;
पूर्ण drm_mga_sarea_t;

/* MGA specअगरic ioctls
 * The device specअगरic ioctl range is 0x40 to 0x79.
 */
#घोषणा DRM_MGA_INIT     0x00
#घोषणा DRM_MGA_FLUSH    0x01
#घोषणा DRM_MGA_RESET    0x02
#घोषणा DRM_MGA_SWAP     0x03
#घोषणा DRM_MGA_CLEAR    0x04
#घोषणा DRM_MGA_VERTEX   0x05
#घोषणा DRM_MGA_INDICES  0x06
#घोषणा DRM_MGA_ILOAD    0x07
#घोषणा DRM_MGA_BLIT     0x08
#घोषणा DRM_MGA_GETPARAM 0x09

/* 3.2:
 * ioctls क्रम operating on fences.
 */
#घोषणा DRM_MGA_SET_FENCE      0x0a
#घोषणा DRM_MGA_WAIT_FENCE     0x0b
#घोषणा DRM_MGA_DMA_BOOTSTRAP  0x0c

#घोषणा DRM_IOCTL_MGA_INIT     DRM_IOW( DRM_COMMAND_BASE + DRM_MGA_INIT, drm_mga_init_t)
#घोषणा DRM_IOCTL_MGA_FLUSH    DRM_IOW( DRM_COMMAND_BASE + DRM_MGA_FLUSH, काष्ठा drm_lock)
#घोषणा DRM_IOCTL_MGA_RESET    DRM_IO(  DRM_COMMAND_BASE + DRM_MGA_RESET)
#घोषणा DRM_IOCTL_MGA_SWAP     DRM_IO(  DRM_COMMAND_BASE + DRM_MGA_SWAP)
#घोषणा DRM_IOCTL_MGA_CLEAR    DRM_IOW( DRM_COMMAND_BASE + DRM_MGA_CLEAR, drm_mga_clear_t)
#घोषणा DRM_IOCTL_MGA_VERTEX   DRM_IOW( DRM_COMMAND_BASE + DRM_MGA_VERTEX, drm_mga_vertex_t)
#घोषणा DRM_IOCTL_MGA_INDICES  DRM_IOW( DRM_COMMAND_BASE + DRM_MGA_INDICES, drm_mga_indices_t)
#घोषणा DRM_IOCTL_MGA_ILOAD    DRM_IOW( DRM_COMMAND_BASE + DRM_MGA_ILOAD, drm_mga_iload_t)
#घोषणा DRM_IOCTL_MGA_BLIT     DRM_IOW( DRM_COMMAND_BASE + DRM_MGA_BLIT, drm_mga_blit_t)
#घोषणा DRM_IOCTL_MGA_GETPARAM DRM_IOWR(DRM_COMMAND_BASE + DRM_MGA_GETPARAM, drm_mga_getparam_t)
#घोषणा DRM_IOCTL_MGA_SET_FENCE     DRM_IOW( DRM_COMMAND_BASE + DRM_MGA_SET_FENCE, __u32)
#घोषणा DRM_IOCTL_MGA_WAIT_FENCE    DRM_IOWR(DRM_COMMAND_BASE + DRM_MGA_WAIT_FENCE, __u32)
#घोषणा DRM_IOCTL_MGA_DMA_BOOTSTRAP DRM_IOWR(DRM_COMMAND_BASE + DRM_MGA_DMA_BOOTSTRAP, drm_mga_dma_bootstrap_t)

प्रकार काष्ठा _drm_mga_warp_index अणु
	पूर्णांक installed;
	अचिन्हित दीर्घ phys_addr;
	पूर्णांक size;
पूर्ण drm_mga_warp_index_t;

प्रकार काष्ठा drm_mga_init अणु
	क्रमागत अणु
		MGA_INIT_DMA = 0x01,
		MGA_CLEANUP_DMA = 0x02
	पूर्ण func;

	अचिन्हित दीर्घ sarea_priv_offset;

	पूर्णांक chipset;
	पूर्णांक sgram;

	अचिन्हित पूर्णांक maccess;

	अचिन्हित पूर्णांक fb_cpp;
	अचिन्हित पूर्णांक front_offset, front_pitch;
	अचिन्हित पूर्णांक back_offset, back_pitch;

	अचिन्हित पूर्णांक depth_cpp;
	अचिन्हित पूर्णांक depth_offset, depth_pitch;

	अचिन्हित पूर्णांक texture_offset[MGA_NR_TEX_HEAPS];
	अचिन्हित पूर्णांक texture_size[MGA_NR_TEX_HEAPS];

	अचिन्हित दीर्घ fb_offset;
	अचिन्हित दीर्घ mmio_offset;
	अचिन्हित दीर्घ status_offset;
	अचिन्हित दीर्घ warp_offset;
	अचिन्हित दीर्घ primary_offset;
	अचिन्हित दीर्घ buffers_offset;
पूर्ण drm_mga_init_t;

प्रकार काष्ठा drm_mga_dma_bootstrap अणु
	/**
	 * \नame AGP texture region
	 *
	 * On वापस from the DRM_MGA_DMA_BOOTSTRAP ioctl, these fields will
	 * be filled in with the actual AGP texture settings.
	 *
	 * \warning
	 * If these fields are non-zero, but dma_mga_dma_bootstrap::agp_mode
	 * is zero, it means that PCI memory (most likely through the use of
	 * an IOMMU) is being used क्रम "AGP" textures.
	 */
	/*@अणु */
	अचिन्हित दीर्घ texture_handle; /**< Handle used to map AGP textures. */
	__u32 texture_size;	      /**< Size of the AGP texture region. */
	/*@पूर्ण */

	/**
	 * Requested size of the primary DMA region.
	 *
	 * On वापस from the DRM_MGA_DMA_BOOTSTRAP ioctl, this field will be
	 * filled in with the actual AGP mode.  If AGP was not available
	 */
	__u32 primary_size;

	/**
	 * Requested number of secondary DMA buffers.
	 *
	 * On वापस from the DRM_MGA_DMA_BOOTSTRAP ioctl, this field will be
	 * filled in with the actual number of secondary DMA buffers
	 * allocated.  Particularly when PCI DMA is used, this may be
	 * (subtantially) less than the number requested.
	 */
	__u32 secondary_bin_count;

	/**
	 * Requested size of each secondary DMA buffer.
	 *
	 * While the kernel \म is मुक्त to reduce
	 * dma_mga_dma_bootstrap::secondary_bin_count, it is \म not allowed
	 * to reduce dma_mga_dma_bootstrap::secondary_bin_size.
	 */
	__u32 secondary_bin_size;

	/**
	 * Bit-wise mask of AGPSTAT2_* values.  Currently only \c AGPSTAT2_1X,
	 * \c AGPSTAT2_2X, and \c AGPSTAT2_4X are supported.  If this value is
	 * zero, it means that PCI DMA should be used, even अगर AGP is
	 * possible.
	 *
	 * On वापस from the DRM_MGA_DMA_BOOTSTRAP ioctl, this field will be
	 * filled in with the actual AGP mode.  If AGP was not available
	 * (i.e., PCI DMA was used), this value will be zero.
	 */
	__u32 agp_mode;

	/**
	 * Desired AGP GART size, measured in megabytes.
	 */
	__u8 agp_size;
पूर्ण drm_mga_dma_bootstrap_t;

प्रकार काष्ठा drm_mga_clear अणु
	अचिन्हित पूर्णांक flags;
	अचिन्हित पूर्णांक clear_color;
	अचिन्हित पूर्णांक clear_depth;
	अचिन्हित पूर्णांक color_mask;
	अचिन्हित पूर्णांक depth_mask;
पूर्ण drm_mga_clear_t;

प्रकार काष्ठा drm_mga_vertex अणु
	पूर्णांक idx;		/* buffer to queue */
	पूर्णांक used;		/* bytes in use */
	पूर्णांक discard;		/* client finished with buffer?  */
पूर्ण drm_mga_vertex_t;

प्रकार काष्ठा drm_mga_indices अणु
	पूर्णांक idx;		/* buffer to queue */
	अचिन्हित पूर्णांक start;
	अचिन्हित पूर्णांक end;
	पूर्णांक discard;		/* client finished with buffer?  */
पूर्ण drm_mga_indices_t;

प्रकार काष्ठा drm_mga_iload अणु
	पूर्णांक idx;
	अचिन्हित पूर्णांक dstorg;
	अचिन्हित पूर्णांक length;
पूर्ण drm_mga_iload_t;

प्रकार काष्ठा _drm_mga_blit अणु
	अचिन्हित पूर्णांक planemask;
	अचिन्हित पूर्णांक srcorg;
	अचिन्हित पूर्णांक dstorg;
	पूर्णांक src_pitch, dst_pitch;
	पूर्णांक delta_sx, delta_sy;
	पूर्णांक delta_dx, delta_dy;
	पूर्णांक height, ydir;	/* flip image vertically */
	पूर्णांक source_pitch, dest_pitch;
पूर्ण drm_mga_blit_t;

/* 3.1: An ioctl to get parameters that aren't available to the 3d
 * client any other way.
 */
#घोषणा MGA_PARAM_IRQ_NR            1

/* 3.2: Query the actual card type.  The DDX only distinguishes between
 * G200 chips and non-G200 chips, which it calls G400.  It turns out that
 * there are some very sublte dअगरferences between the G4x0 chips and the G550
 * chips.  Using this parameter query, a client-side driver can detect the
 * dअगरference between a G4x0 and a G550.
 */
#घोषणा MGA_PARAM_CARD_TYPE         2

प्रकार काष्ठा drm_mga_getparam अणु
	पूर्णांक param;
	व्योम __user *value;
पूर्ण drm_mga_getparam_t;

#अगर defined(__cplusplus)
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर
