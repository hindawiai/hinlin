<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _I810_DRM_H_
#घोषणा _I810_DRM_H_

#समावेश "drm.h"

#अगर defined(__cplusplus)
बाह्य "C" अणु
#पूर्ण_अगर

/* WARNING: These defines must be the same as what the Xserver uses.
 * अगर you change them, you must change the defines in the Xserver.
 */

#अगर_अघोषित _I810_DEFINES_
#घोषणा _I810_DEFINES_

#घोषणा I810_DMA_BUF_ORDER		12
#घोषणा I810_DMA_BUF_SZ 		(1<<I810_DMA_BUF_ORDER)
#घोषणा I810_DMA_BUF_NR 		256
#घोषणा I810_NR_SAREA_CLIPRECTS 	8

/* Each region is a minimum of 64k, and there are at most 64 of them.
 */
#घोषणा I810_NR_TEX_REGIONS 64
#घोषणा I810_LOG_MIN_TEX_REGION_SIZE 16
#पूर्ण_अगर

#घोषणा I810_UPLOAD_TEX0IMAGE  0x1	/* handled clientside */
#घोषणा I810_UPLOAD_TEX1IMAGE  0x2	/* handled clientside */
#घोषणा I810_UPLOAD_CTX        0x4
#घोषणा I810_UPLOAD_BUFFERS    0x8
#घोषणा I810_UPLOAD_TEX0       0x10
#घोषणा I810_UPLOAD_TEX1       0x20
#घोषणा I810_UPLOAD_CLIPRECTS  0x40

/* Indices पूर्णांकo buf.Setup where various bits of state are mirrored per
 * context and per buffer.  These can be fired at the card as a unit,
 * or in a piecewise fashion as required.
 */

/* Destbuffer state
 *    - backbuffer linear offset and pitch -- invarient in the current dri
 *    - zbuffer linear offset and pitch -- also invarient
 *    - drawing origin in back and depth buffers.
 *
 * Keep the depth/back buffer state here to accommodate निजी buffers
 * in the future.
 */
#घोषणा I810_DESTREG_DI0  0	/* CMD_OP_DESTBUFFER_INFO (2 dwords) */
#घोषणा I810_DESTREG_DI1  1
#घोषणा I810_DESTREG_DV0  2	/* GFX_OP_DESTBUFFER_VARS (2 dwords) */
#घोषणा I810_DESTREG_DV1  3
#घोषणा I810_DESTREG_DR0  4	/* GFX_OP_DRAWRECT_INFO (4 dwords) */
#घोषणा I810_DESTREG_DR1  5
#घोषणा I810_DESTREG_DR2  6
#घोषणा I810_DESTREG_DR3  7
#घोषणा I810_DESTREG_DR4  8
#घोषणा I810_DEST_SETUP_SIZE 10

/* Context state
 */
#घोषणा I810_CTXREG_CF0   0	/* GFX_OP_COLOR_FACTOR */
#घोषणा I810_CTXREG_CF1   1
#घोषणा I810_CTXREG_ST0   2	/* GFX_OP_STIPPLE */
#घोषणा I810_CTXREG_ST1   3
#घोषणा I810_CTXREG_VF    4	/* GFX_OP_VERTEX_FMT */
#घोषणा I810_CTXREG_MT    5	/* GFX_OP_MAP_TEXELS */
#घोषणा I810_CTXREG_MC0   6	/* GFX_OP_MAP_COLOR_STAGES - stage 0 */
#घोषणा I810_CTXREG_MC1   7	/* GFX_OP_MAP_COLOR_STAGES - stage 1 */
#घोषणा I810_CTXREG_MC2   8	/* GFX_OP_MAP_COLOR_STAGES - stage 2 */
#घोषणा I810_CTXREG_MA0   9	/* GFX_OP_MAP_ALPHA_STAGES - stage 0 */
#घोषणा I810_CTXREG_MA1   10	/* GFX_OP_MAP_ALPHA_STAGES - stage 1 */
#घोषणा I810_CTXREG_MA2   11	/* GFX_OP_MAP_ALPHA_STAGES - stage 2 */
#घोषणा I810_CTXREG_SDM   12	/* GFX_OP_SRC_DEST_MONO */
#घोषणा I810_CTXREG_FOG   13	/* GFX_OP_FOG_COLOR */
#घोषणा I810_CTXREG_B1    14	/* GFX_OP_BOOL_1 */
#घोषणा I810_CTXREG_B2    15	/* GFX_OP_BOOL_2 */
#घोषणा I810_CTXREG_LCS   16	/* GFX_OP_LINEWIDTH_CULL_SHADE_MODE */
#घोषणा I810_CTXREG_PV    17	/* GFX_OP_PV_RULE -- Invarient! */
#घोषणा I810_CTXREG_ZA    18	/* GFX_OP_ZBIAS_ALPHAFUNC */
#घोषणा I810_CTXREG_AA    19	/* GFX_OP_ANTIALIAS */
#घोषणा I810_CTX_SETUP_SIZE 20

/* Texture state (per tex unit)
 */
#घोषणा I810_TEXREG_MI0  0	/* GFX_OP_MAP_INFO (4 dwords) */
#घोषणा I810_TEXREG_MI1  1
#घोषणा I810_TEXREG_MI2  2
#घोषणा I810_TEXREG_MI3  3
#घोषणा I810_TEXREG_MF   4	/* GFX_OP_MAP_FILTER */
#घोषणा I810_TEXREG_MLC  5	/* GFX_OP_MAP_LOD_CTL */
#घोषणा I810_TEXREG_MLL  6	/* GFX_OP_MAP_LOD_LIMITS */
#घोषणा I810_TEXREG_MCS  7	/* GFX_OP_MAP_COORD_SETS ??? */
#घोषणा I810_TEX_SETUP_SIZE 8

/* Flags क्रम clear ioctl
 */
#घोषणा I810_FRONT   0x1
#घोषणा I810_BACK    0x2
#घोषणा I810_DEPTH   0x4

प्रकार क्रमागत _drm_i810_init_func अणु
	I810_INIT_DMA = 0x01,
	I810_CLEANUP_DMA = 0x02,
	I810_INIT_DMA_1_4 = 0x03
पूर्ण drm_i810_init_func_t;

/* This is the init काष्ठाure after v1.2 */
प्रकार काष्ठा _drm_i810_init अणु
	drm_i810_init_func_t func;
	अचिन्हित पूर्णांक mmio_offset;
	अचिन्हित पूर्णांक buffers_offset;
	पूर्णांक sarea_priv_offset;
	अचिन्हित पूर्णांक ring_start;
	अचिन्हित पूर्णांक ring_end;
	अचिन्हित पूर्णांक ring_size;
	अचिन्हित पूर्णांक front_offset;
	अचिन्हित पूर्णांक back_offset;
	अचिन्हित पूर्णांक depth_offset;
	अचिन्हित पूर्णांक overlay_offset;
	अचिन्हित पूर्णांक overlay_physical;
	अचिन्हित पूर्णांक w;
	अचिन्हित पूर्णांक h;
	अचिन्हित पूर्णांक pitch;
	अचिन्हित पूर्णांक pitch_bits;
पूर्ण drm_i810_init_t;

/* This is the init काष्ठाure prior to v1.2 */
प्रकार काष्ठा _drm_i810_pre12_init अणु
	drm_i810_init_func_t func;
	अचिन्हित पूर्णांक mmio_offset;
	अचिन्हित पूर्णांक buffers_offset;
	पूर्णांक sarea_priv_offset;
	अचिन्हित पूर्णांक ring_start;
	अचिन्हित पूर्णांक ring_end;
	अचिन्हित पूर्णांक ring_size;
	अचिन्हित पूर्णांक front_offset;
	अचिन्हित पूर्णांक back_offset;
	अचिन्हित पूर्णांक depth_offset;
	अचिन्हित पूर्णांक w;
	अचिन्हित पूर्णांक h;
	अचिन्हित पूर्णांक pitch;
	अचिन्हित पूर्णांक pitch_bits;
पूर्ण drm_i810_pre12_init_t;

/* Warning: If you change the SAREA काष्ठाure you must change the Xserver
 * काष्ठाure as well */

प्रकार काष्ठा _drm_i810_tex_region अणु
	अचिन्हित अक्षर next, prev;	/* indices to क्रमm a circular LRU  */
	अचिन्हित अक्षर in_use;	/* owned by a client, or मुक्त? */
	पूर्णांक age;		/* tracked by clients to update local LRU's */
पूर्ण drm_i810_tex_region_t;

प्रकार काष्ठा _drm_i810_sarea अणु
	अचिन्हित पूर्णांक ContextState[I810_CTX_SETUP_SIZE];
	अचिन्हित पूर्णांक BufferState[I810_DEST_SETUP_SIZE];
	अचिन्हित पूर्णांक TexState[2][I810_TEX_SETUP_SIZE];
	अचिन्हित पूर्णांक dirty;

	अचिन्हित पूर्णांक nbox;
	काष्ठा drm_clip_rect boxes[I810_NR_SAREA_CLIPRECTS];

	/* Maपूर्णांकain an LRU of contiguous regions of texture space.  If
	 * you think you own a region of texture memory, and it has an
	 * age dअगरferent to the one you set, then you are mistaken and
	 * it has been stolen by another client.  If global texAge
	 * hasn't changed, there is no need to walk the list.
	 *
	 * These regions can be used as a proxy क्रम the fine-grained
	 * texture inक्रमmation of other clients - by मुख्यtaining them
	 * in the same lru which is used to age their own textures,
	 * clients have an approximate lru क्रम the whole of global
	 * texture space, and can make inक्रमmed decisions as to which
	 * areas to kick out.  There is no need to choose whether to
	 * kick out your own texture or someone अन्यथा's - simply eject
	 * them all in LRU order.
	 */

	drm_i810_tex_region_t texList[I810_NR_TEX_REGIONS + 1];
	/* Last elt is sentinal */
	पूर्णांक texAge;		/* last समय texture was uploaded */
	पूर्णांक last_enqueue;	/* last समय a buffer was enqueued */
	पूर्णांक last_dispatch;	/* age of the most recently dispatched buffer */
	पूर्णांक last_quiescent;	/*  */
	पूर्णांक ctxOwner;		/* last context to upload state */

	पूर्णांक vertex_prim;

	पूर्णांक pf_enabled;		/* is pageflipping allowed? */
	पूर्णांक pf_active;
	पूर्णांक pf_current_page;	/* which buffer is being displayed? */
पूर्ण drm_i810_sarea_t;

/* WARNING: If you change any of these defines, make sure to change the
 * defines in the Xserver file (xf86drmMga.h)
 */

/* i810 specअगरic ioctls
 * The device specअगरic ioctl range is 0x40 to 0x79.
 */
#घोषणा DRM_I810_INIT		0x00
#घोषणा DRM_I810_VERTEX		0x01
#घोषणा DRM_I810_CLEAR		0x02
#घोषणा DRM_I810_FLUSH		0x03
#घोषणा DRM_I810_GETAGE		0x04
#घोषणा DRM_I810_GETBUF		0x05
#घोषणा DRM_I810_SWAP		0x06
#घोषणा DRM_I810_COPY		0x07
#घोषणा DRM_I810_DOCOPY		0x08
#घोषणा DRM_I810_OV0INFO	0x09
#घोषणा DRM_I810_FSTATUS	0x0a
#घोषणा DRM_I810_OV0FLIP	0x0b
#घोषणा DRM_I810_MC		0x0c
#घोषणा DRM_I810_RSTATUS	0x0d
#घोषणा DRM_I810_FLIP		0x0e

#घोषणा DRM_IOCTL_I810_INIT		DRM_IOW( DRM_COMMAND_BASE + DRM_I810_INIT, drm_i810_init_t)
#घोषणा DRM_IOCTL_I810_VERTEX		DRM_IOW( DRM_COMMAND_BASE + DRM_I810_VERTEX, drm_i810_vertex_t)
#घोषणा DRM_IOCTL_I810_CLEAR		DRM_IOW( DRM_COMMAND_BASE + DRM_I810_CLEAR, drm_i810_clear_t)
#घोषणा DRM_IOCTL_I810_FLUSH		DRM_IO(  DRM_COMMAND_BASE + DRM_I810_FLUSH)
#घोषणा DRM_IOCTL_I810_GETAGE		DRM_IO(  DRM_COMMAND_BASE + DRM_I810_GETAGE)
#घोषणा DRM_IOCTL_I810_GETBUF		DRM_IOWR(DRM_COMMAND_BASE + DRM_I810_GETBUF, drm_i810_dma_t)
#घोषणा DRM_IOCTL_I810_SWAP		DRM_IO(  DRM_COMMAND_BASE + DRM_I810_SWAP)
#घोषणा DRM_IOCTL_I810_COPY		DRM_IOW( DRM_COMMAND_BASE + DRM_I810_COPY, drm_i810_copy_t)
#घोषणा DRM_IOCTL_I810_DOCOPY		DRM_IO(  DRM_COMMAND_BASE + DRM_I810_DOCOPY)
#घोषणा DRM_IOCTL_I810_OV0INFO		DRM_IOR( DRM_COMMAND_BASE + DRM_I810_OV0INFO, drm_i810_overlay_t)
#घोषणा DRM_IOCTL_I810_FSTATUS		DRM_IO ( DRM_COMMAND_BASE + DRM_I810_FSTATUS)
#घोषणा DRM_IOCTL_I810_OV0FLIP		DRM_IO ( DRM_COMMAND_BASE + DRM_I810_OV0FLIP)
#घोषणा DRM_IOCTL_I810_MC		DRM_IOW( DRM_COMMAND_BASE + DRM_I810_MC, drm_i810_mc_t)
#घोषणा DRM_IOCTL_I810_RSTATUS		DRM_IO ( DRM_COMMAND_BASE + DRM_I810_RSTATUS)
#घोषणा DRM_IOCTL_I810_FLIP             DRM_IO ( DRM_COMMAND_BASE + DRM_I810_FLIP)

प्रकार काष्ठा _drm_i810_clear अणु
	पूर्णांक clear_color;
	पूर्णांक clear_depth;
	पूर्णांक flags;
पूर्ण drm_i810_clear_t;

/* These may be placeholders अगर we have more cliprects than
 * I810_NR_SAREA_CLIPRECTS.  In that हाल, the client sets discard to
 * false, indicating that the buffer will be dispatched again with a
 * new set of cliprects.
 */
प्रकार काष्ठा _drm_i810_vertex अणु
	पूर्णांक idx;		/* buffer index */
	पूर्णांक used;		/* nr bytes in use */
	पूर्णांक discard;		/* client is finished with the buffer? */
पूर्ण drm_i810_vertex_t;

प्रकार काष्ठा _drm_i810_copy_t अणु
	पूर्णांक idx;		/* buffer index */
	पूर्णांक used;		/* nr bytes in use */
	व्योम *address;		/* Address to copy from */
पूर्ण drm_i810_copy_t;

#घोषणा PR_TRIANGLES         (0x0<<18)
#घोषणा PR_TRISTRIP_0        (0x1<<18)
#घोषणा PR_TRISTRIP_1        (0x2<<18)
#घोषणा PR_TRIFAN            (0x3<<18)
#घोषणा PR_POLYGON           (0x4<<18)
#घोषणा PR_LINES             (0x5<<18)
#घोषणा PR_LINESTRIP         (0x6<<18)
#घोषणा PR_RECTS             (0x7<<18)
#घोषणा PR_MASK              (0x7<<18)

प्रकार काष्ठा drm_i810_dma अणु
	व्योम *भव;
	पूर्णांक request_idx;
	पूर्णांक request_size;
	पूर्णांक granted;
पूर्ण drm_i810_dma_t;

प्रकार काष्ठा _drm_i810_overlay_t अणु
	अचिन्हित पूर्णांक offset;	/* Address of the Overlay Regs */
	अचिन्हित पूर्णांक physical;
पूर्ण drm_i810_overlay_t;

प्रकार काष्ठा _drm_i810_mc अणु
	पूर्णांक idx;		/* buffer index */
	पूर्णांक used;		/* nr bytes in use */
	पूर्णांक num_blocks;		/* number of GFXBlocks */
	पूर्णांक *length;		/* List of lengths क्रम GFXBlocks (FUTURE) */
	अचिन्हित पूर्णांक last_render;	/* Last Render Request */
पूर्ण drm_i810_mc_t;

#अगर defined(__cplusplus)
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर				/* _I810_DRM_H_ */
