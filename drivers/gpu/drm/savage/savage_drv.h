<शैली गुरु>
/* savage_drv.h -- Private header क्रम the savage driver */
/*
 * Copyright 2004  Felix Kuehling
 * All Rights Reserved.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sub license,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the
 * next paragraph) shall be included in all copies or substantial portions
 * of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NON-INFRINGEMENT. IN NO EVENT SHALL FELIX KUEHLING BE LIABLE FOR
 * ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
 * CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#अगर_अघोषित __SAVAGE_DRV_H__
#घोषणा __SAVAGE_DRV_H__

#समावेश <linux/पन.स>

#समावेश <drm/drm_ioctl.h>
#समावेश <drm/drm_legacy.h>
#समावेश <drm/savage_drm.h>

#घोषणा DRIVER_AUTHOR	"Felix Kuehling"

#घोषणा DRIVER_NAME	"savage"
#घोषणा DRIVER_DESC	"Savage3D/MX/IX, Savage4, SuperSavage, Twister, ProSavage[DDR]"
#घोषणा DRIVER_DATE	"20050313"

#घोषणा DRIVER_MAJOR		2
#घोषणा DRIVER_MINOR		4
#घोषणा DRIVER_PATCHLEVEL	1
/* Interface history:
 *
 * 1.x   The DRM driver from the VIA/S3 code drop, basically a dummy
 * 2.0   The first real DRM
 * 2.1   Scissors रेजिस्टरs managed by the DRM, 3D operations clipped by
 *       cliprects of the cmdbuf ioctl
 * 2.2   Implemented SAVAGE_CMD_DMA_IDX and SAVAGE_CMD_VB_IDX
 * 2.3   Event counters used by BCI_EVENT_EMIT/WAIT ioctls are now 32 bits
 *       wide and thus very दीर्घ lived (unlikely to ever wrap). The size
 *       in the काष्ठा was 32 bits beक्रमe, but only 16 bits were used
 * 2.4   Implemented command DMA. Now drm_savage_init_t.cmd_dma_offset is
 *       actually used
 */

प्रकार काष्ठा drm_savage_age अणु
	uपूर्णांक16_t event;
	अचिन्हित पूर्णांक wrap;
पूर्ण drm_savage_age_t;

प्रकार काष्ठा drm_savage_buf_priv अणु
	काष्ठा drm_savage_buf_priv *next;
	काष्ठा drm_savage_buf_priv *prev;
	drm_savage_age_t age;
	काष्ठा drm_buf *buf;
पूर्ण drm_savage_buf_priv_t;

प्रकार काष्ठा drm_savage_dma_page अणु
	drm_savage_age_t age;
	अचिन्हित पूर्णांक used, flushed;
पूर्ण drm_savage_dma_page_t;
#घोषणा SAVAGE_DMA_PAGE_SIZE 1024	/* in dwords */
/* Fake DMA buffer size in bytes. 4 pages. Allows a maximum command
 * size of 16kbytes or 4k entries. Minimum requirement would be
 * 10kbytes क्रम 255 40-byte vertices in one drawing command. */
#घोषणा SAVAGE_FAKE_DMA_SIZE (SAVAGE_DMA_PAGE_SIZE*4*4)

/* पूर्णांकeresting bits of hardware state that are saved in dev_priv */
प्रकार जोड़ अणु
	काष्ठा drm_savage_common_state अणु
		uपूर्णांक32_t vbaddr;
	पूर्ण common;
	काष्ठा अणु
		अचिन्हित अक्षर pad[माप(काष्ठा drm_savage_common_state)];
		uपूर्णांक32_t texctrl, texaddr;
		uपूर्णांक32_t scstart, new_scstart;
		uपूर्णांक32_t scend, new_scend;
	पूर्ण s3d;
	काष्ठा अणु
		अचिन्हित अक्षर pad[माप(काष्ठा drm_savage_common_state)];
		uपूर्णांक32_t texdescr, texaddr0, texaddr1;
		uपूर्णांक32_t drawctrl0, new_drawctrl0;
		uपूर्णांक32_t drawctrl1, new_drawctrl1;
	पूर्ण s4;
पूर्ण drm_savage_state_t;

/* these chip tags should match the ones in the 2D driver in savage_regs.h. */
क्रमागत savage_family अणु
	S3_UNKNOWN = 0,
	S3_SAVAGE3D,
	S3_SAVAGE_MX,
	S3_SAVAGE4,
	S3_PROSAVAGE,
	S3_TWISTER,
	S3_PROSAVAGEDDR,
	S3_SUPERSAVAGE,
	S3_SAVAGE2000,
	S3_LAST
पूर्ण;

बाह्य स्थिर काष्ठा drm_ioctl_desc savage_ioctls[];
बाह्य पूर्णांक savage_max_ioctl;

#घोषणा S3_SAVAGE3D_SERIES(chip)  ((chip>=S3_SAVAGE3D) && (chip<=S3_SAVAGE_MX))

#घोषणा S3_SAVAGE4_SERIES(chip)  ((chip==S3_SAVAGE4)            \
                                  || (chip==S3_PROSAVAGE)       \
                                  || (chip==S3_TWISTER)         \
                                  || (chip==S3_PROSAVAGEDDR))

#घोषणा	S3_SAVAGE_MOBILE_SERIES(chip)	((chip==S3_SAVAGE_MX) || (chip==S3_SUPERSAVAGE))

#घोषणा S3_SAVAGE_SERIES(chip)    ((chip>=S3_SAVAGE3D) && (chip<=S3_SAVAGE2000))

#घोषणा S3_MOBILE_TWISTER_SERIES(chip)   ((chip==S3_TWISTER)    \
                                          ||(chip==S3_PROSAVAGEDDR))

/* flags */
#घोषणा SAVAGE_IS_AGP 1

प्रकार काष्ठा drm_savage_निजी अणु
	drm_savage_sarea_t *sarea_priv;

	drm_savage_buf_priv_t head, tail;

	/* who am I? */
	क्रमागत savage_family chipset;

	अचिन्हित पूर्णांक cob_size;
	अचिन्हित पूर्णांक bci_threshold_lo, bci_threshold_hi;
	अचिन्हित पूर्णांक dma_type;

	/* frame buffer layout */
	अचिन्हित पूर्णांक fb_bpp;
	अचिन्हित पूर्णांक front_offset, front_pitch;
	अचिन्हित पूर्णांक back_offset, back_pitch;
	अचिन्हित पूर्णांक depth_bpp;
	अचिन्हित पूर्णांक depth_offset, depth_pitch;

	/* biपंचांगap descriptors क्रम swap and clear */
	अचिन्हित पूर्णांक front_bd, back_bd, depth_bd;

	/* local textures */
	अचिन्हित पूर्णांक texture_offset;
	अचिन्हित पूर्णांक texture_size;

	/* memory regions in physical memory */
	drm_local_map_t *sarea;
	drm_local_map_t *mmio;
	drm_local_map_t *fb;
	drm_local_map_t *aperture;
	drm_local_map_t *status;
	drm_local_map_t *agp_textures;
	drm_local_map_t *cmd_dma;
	drm_local_map_t fake_dma;

	पूर्णांक mtrr_handles[3];

	/* BCI and status-related stuff */
	अस्थिर uपूर्णांक32_t *status_ptr, *bci_ptr;
	uपूर्णांक32_t status_used_mask;
	uपूर्णांक16_t event_counter;
	अचिन्हित पूर्णांक event_wrap;

	/* Savage4 command DMA */
	drm_savage_dma_page_t *dma_pages;
	अचिन्हित पूर्णांक nr_dma_pages, first_dma_page, current_dma_page;
	drm_savage_age_t last_dma_age;

	/* saved hw state क्रम global/local check on S3D */
	uपूर्णांक32_t hw_draw_ctrl, hw_zbuf_ctrl;
	/* and क्रम scissors (global, so करोn't emit अगर not changed) */
	uपूर्णांक32_t hw_scissors_start, hw_scissors_end;

	drm_savage_state_t state;

	/* after emitting a रुको cmd Savage3D needs 63 nops beक्रमe next DMA */
	अचिन्हित पूर्णांक रुकोing;

	/* config/hardware-dependent function poपूर्णांकers */
	पूर्णांक (*रुको_fअगरo) (काष्ठा drm_savage_निजी * dev_priv, अचिन्हित पूर्णांक n);
	पूर्णांक (*रुको_evnt) (काष्ठा drm_savage_निजी * dev_priv, uपूर्णांक16_t e);
	/* Err, there is a macro रुको_event in include/linux/रुको.h.
	 * Aव्योम unwanted macro expansion. */
	व्योम (*emit_clip_rect) (काष्ठा drm_savage_निजी * dev_priv,
				स्थिर काष्ठा drm_clip_rect * pbox);
	व्योम (*dma_flush) (काष्ठा drm_savage_निजी * dev_priv);
पूर्ण drm_savage_निजी_t;

/* ioctls */
बाह्य पूर्णांक savage_bci_cmdbuf(काष्ठा drm_device *dev, व्योम *data, काष्ठा drm_file *file_priv);
बाह्य पूर्णांक savage_bci_buffers(काष्ठा drm_device *dev, व्योम *data, काष्ठा drm_file *file_priv);

/* BCI functions */
बाह्य uपूर्णांक16_t savage_bci_emit_event(drm_savage_निजी_t * dev_priv,
				      अचिन्हित पूर्णांक flags);
बाह्य व्योम savage_मुक्तlist_put(काष्ठा drm_device * dev, काष्ठा drm_buf * buf);
बाह्य व्योम savage_dma_reset(drm_savage_निजी_t * dev_priv);
बाह्य व्योम savage_dma_रुको(drm_savage_निजी_t * dev_priv, अचिन्हित पूर्णांक page);
बाह्य uपूर्णांक32_t *savage_dma_alloc(drm_savage_निजी_t * dev_priv,
				  अचिन्हित पूर्णांक n);
बाह्य पूर्णांक savage_driver_load(काष्ठा drm_device *dev, अचिन्हित दीर्घ chipset);
बाह्य पूर्णांक savage_driver_firstखोलो(काष्ठा drm_device *dev);
बाह्य व्योम savage_driver_lastबंद(काष्ठा drm_device *dev);
बाह्य व्योम savage_driver_unload(काष्ठा drm_device *dev);
बाह्य व्योम savage_reclaim_buffers(काष्ठा drm_device *dev,
				   काष्ठा drm_file *file_priv);

/* state functions */
बाह्य व्योम savage_emit_clip_rect_s3d(drm_savage_निजी_t * dev_priv,
				      स्थिर काष्ठा drm_clip_rect * pbox);
बाह्य व्योम savage_emit_clip_rect_s4(drm_savage_निजी_t * dev_priv,
				     स्थिर काष्ठा drm_clip_rect * pbox);

#घोषणा SAVAGE_FB_SIZE_S3	0x01000000	/*  16MB */
#घोषणा SAVAGE_FB_SIZE_S4	0x02000000	/*  32MB */
#घोषणा SAVAGE_MMIO_SIZE        0x00080000	/* 512kB */
#घोषणा SAVAGE_APERTURE_OFFSET  0x02000000	/*  32MB */
#घोषणा SAVAGE_APERTURE_SIZE    0x05000000	/* 5 tiled surfaces, 16MB each */

#घोषणा SAVAGE_BCI_OFFSET       0x00010000	/* offset of the BCI region
						 * inside the MMIO region */
#घोषणा SAVAGE_BCI_FIFO_SIZE	32	/* number of entries in on-chip
					 * BCI FIFO */

/*
 * MMIO रेजिस्टरs
 */
#घोषणा SAVAGE_STATUS_WORD0		0x48C00
#घोषणा SAVAGE_STATUS_WORD1		0x48C04
#घोषणा SAVAGE_ALT_STATUS_WORD0 	0x48C60

#घोषणा SAVAGE_FIFO_USED_MASK_S3D	0x0001ffff
#घोषणा SAVAGE_FIFO_USED_MASK_S4	0x001fffff

/* Copied from savage_bci.h in the 2D driver with some renaming. */

/* Biपंचांगap descriptors */
#घोषणा SAVAGE_BD_STRIDE_SHIFT 0
#घोषणा SAVAGE_BD_BPP_SHIFT   16
#घोषणा SAVAGE_BD_TILE_SHIFT  24
#घोषणा SAVAGE_BD_BW_DISABLE  (1<<28)
/* common: */
#घोषणा	SAVAGE_BD_TILE_LINEAR		0
/* savage4, MX, IX, 3D */
#घोषणा	SAVAGE_BD_TILE_16BPP		2
#घोषणा	SAVAGE_BD_TILE_32BPP		3
/* twister, prosavage, DDR, supersavage, 2000 */
#घोषणा	SAVAGE_BD_TILE_DEST		1
#घोषणा	SAVAGE_BD_TILE_TEXTURE		2
/* GBD - BCI enable */
/* savage4, MX, IX, 3D */
#घोषणा SAVAGE_GBD_BCI_ENABLE                    8
/* twister, prosavage, DDR, supersavage, 2000 */
#घोषणा SAVAGE_GBD_BCI_ENABLE_TWISTER            0

#घोषणा SAVAGE_GBD_BIG_ENDIAN                    4
#घोषणा SAVAGE_GBD_LITTLE_ENDIAN                 0
#घोषणा SAVAGE_GBD_64                            1

/*  Global Biपंचांगap Descriptor */
#घोषणा SAVAGE_BCI_GLB_BD_LOW             0x8168
#घोषणा SAVAGE_BCI_GLB_BD_HIGH            0x816C

/*
 * BCI रेजिस्टरs
 */
/* Savage4/Twister/ProSavage 3D रेजिस्टरs */
#घोषणा SAVAGE_DRAWLOCALCTRL_S4		0x1e
#घोषणा SAVAGE_TEXPALADDR_S4		0x1f
#घोषणा SAVAGE_TEXCTRL0_S4		0x20
#घोषणा SAVAGE_TEXCTRL1_S4		0x21
#घोषणा SAVAGE_TEXADDR0_S4		0x22
#घोषणा SAVAGE_TEXADDR1_S4		0x23
#घोषणा SAVAGE_TEXBLEND0_S4		0x24
#घोषणा SAVAGE_TEXBLEND1_S4		0x25
#घोषणा SAVAGE_TEXXPRCLR_S4		0x26	/* never used */
#घोषणा SAVAGE_TEXDESCR_S4		0x27
#घोषणा SAVAGE_FOGTABLE_S4		0x28
#घोषणा SAVAGE_FOGCTRL_S4		0x30
#घोषणा SAVAGE_STENCILCTRL_S4		0x31
#घोषणा SAVAGE_ZBUFCTRL_S4		0x32
#घोषणा SAVAGE_ZBUFOFF_S4		0x33
#घोषणा SAVAGE_DESTCTRL_S4		0x34
#घोषणा SAVAGE_DRAWCTRL0_S4		0x35
#घोषणा SAVAGE_DRAWCTRL1_S4		0x36
#घोषणा SAVAGE_ZWATERMARK_S4		0x37
#घोषणा SAVAGE_DESTTEXRWWATERMARK_S4	0x38
#घोषणा SAVAGE_TEXBLENDCOLOR_S4		0x39
/* Savage3D/MX/IX 3D रेजिस्टरs */
#घोषणा SAVAGE_TEXPALADDR_S3D		0x18
#घोषणा SAVAGE_TEXXPRCLR_S3D		0x19	/* never used */
#घोषणा SAVAGE_TEXADDR_S3D		0x1A
#घोषणा SAVAGE_TEXDESCR_S3D		0x1B
#घोषणा SAVAGE_TEXCTRL_S3D		0x1C
#घोषणा SAVAGE_FOGTABLE_S3D		0x20
#घोषणा SAVAGE_FOGCTRL_S3D		0x30
#घोषणा SAVAGE_DRAWCTRL_S3D		0x31
#घोषणा SAVAGE_ZBUFCTRL_S3D		0x32
#घोषणा SAVAGE_ZBUFOFF_S3D		0x33
#घोषणा SAVAGE_DESTCTRL_S3D		0x34
#घोषणा SAVAGE_SCSTART_S3D		0x35
#घोषणा SAVAGE_SCEND_S3D		0x36
#घोषणा SAVAGE_ZWATERMARK_S3D		0x37
#घोषणा SAVAGE_DESTTEXRWWATERMARK_S3D	0x38
/* common stuff */
#घोषणा SAVAGE_VERTBUFADDR		0x3e
#घोषणा SAVAGE_BITPLANEWTMASK		0xd7
#घोषणा SAVAGE_DMABUFADDR		0x51

/* texture enable bits (needed क्रम tex addr checking) */
#घोषणा SAVAGE_TEXCTRL_TEXEN_MASK	0x00010000	/* S3D */
#घोषणा SAVAGE_TEXDESCR_TEX0EN_MASK	0x02000000	/* S4 */
#घोषणा SAVAGE_TEXDESCR_TEX1EN_MASK	0x04000000	/* S4 */

/* Global fields in Savage4/Twister/ProSavage 3D रेजिस्टरs:
 *
 * All texture रेजिस्टरs and DrawLocalCtrl are local. All other
 * रेजिस्टरs are global. */

/* Global fields in Savage3D/MX/IX 3D रेजिस्टरs:
 *
 * All texture रेजिस्टरs are local. DrawCtrl and ZBufCtrl are
 * partially local. All other रेजिस्टरs are global.
 *
 * DrawCtrl global fields: cullMode, alphaTestCmpFunc, alphaTestEn, alphaRefVal
 * ZBufCtrl global fields: zCmpFunc, zBufEn
 */
#घोषणा SAVAGE_DRAWCTRL_S3D_GLOBAL	0x03f3c00c
#घोषणा SAVAGE_ZBUFCTRL_S3D_GLOBAL	0x00000027

/* Masks क्रम scissor bits (drawCtrl[01] on s4, scissorStart/End on s3d)
 */
#घोषणा SAVAGE_SCISSOR_MASK_S4		0x00fff7ff
#घोषणा SAVAGE_SCISSOR_MASK_S3D		0x07ff07ff

/*
 * BCI commands
 */
#घोषणा BCI_CMD_NOP                  0x40000000
#घोषणा BCI_CMD_RECT                 0x48000000
#घोषणा BCI_CMD_RECT_XP              0x01000000
#घोषणा BCI_CMD_RECT_YP              0x02000000
#घोषणा BCI_CMD_SCANLINE             0x50000000
#घोषणा BCI_CMD_LINE                 0x5C000000
#घोषणा BCI_CMD_LINE_LAST_PIXEL      0x58000000
#घोषणा BCI_CMD_BYTE_TEXT            0x63000000
#घोषणा BCI_CMD_NT_BYTE_TEXT         0x67000000
#घोषणा BCI_CMD_BIT_TEXT             0x6C000000
#घोषणा BCI_CMD_GET_ROP(cmd)         (((cmd) >> 16) & 0xFF)
#घोषणा BCI_CMD_SET_ROP(cmd, rop)    ((cmd) |= ((rop & 0xFF) << 16))
#घोषणा BCI_CMD_SEND_COLOR           0x00008000

#घोषणा BCI_CMD_CLIP_NONE            0x00000000
#घोषणा BCI_CMD_CLIP_CURRENT         0x00002000
#घोषणा BCI_CMD_CLIP_LR              0x00004000
#घोषणा BCI_CMD_CLIP_NEW             0x00006000

#घोषणा BCI_CMD_DEST_GBD             0x00000000
#घोषणा BCI_CMD_DEST_PBD             0x00000800
#घोषणा BCI_CMD_DEST_PBD_NEW         0x00000C00
#घोषणा BCI_CMD_DEST_SBD             0x00001000
#घोषणा BCI_CMD_DEST_SBD_NEW         0x00001400

#घोषणा BCI_CMD_SRC_TRANSPARENT      0x00000200
#घोषणा BCI_CMD_SRC_SOLID            0x00000000
#घोषणा BCI_CMD_SRC_GBD              0x00000020
#घोषणा BCI_CMD_SRC_COLOR            0x00000040
#घोषणा BCI_CMD_SRC_MONO             0x00000060
#घोषणा BCI_CMD_SRC_PBD_COLOR        0x00000080
#घोषणा BCI_CMD_SRC_PBD_MONO         0x000000A0
#घोषणा BCI_CMD_SRC_PBD_COLOR_NEW    0x000000C0
#घोषणा BCI_CMD_SRC_PBD_MONO_NEW     0x000000E0
#घोषणा BCI_CMD_SRC_SBD_COLOR        0x00000100
#घोषणा BCI_CMD_SRC_SBD_MONO         0x00000120
#घोषणा BCI_CMD_SRC_SBD_COLOR_NEW    0x00000140
#घोषणा BCI_CMD_SRC_SBD_MONO_NEW     0x00000160

#घोषणा BCI_CMD_PAT_TRANSPARENT      0x00000010
#घोषणा BCI_CMD_PAT_NONE             0x00000000
#घोषणा BCI_CMD_PAT_COLOR            0x00000002
#घोषणा BCI_CMD_PAT_MONO             0x00000003
#घोषणा BCI_CMD_PAT_PBD_COLOR        0x00000004
#घोषणा BCI_CMD_PAT_PBD_MONO         0x00000005
#घोषणा BCI_CMD_PAT_PBD_COLOR_NEW    0x00000006
#घोषणा BCI_CMD_PAT_PBD_MONO_NEW     0x00000007
#घोषणा BCI_CMD_PAT_SBD_COLOR        0x00000008
#घोषणा BCI_CMD_PAT_SBD_MONO         0x00000009
#घोषणा BCI_CMD_PAT_SBD_COLOR_NEW    0x0000000A
#घोषणा BCI_CMD_PAT_SBD_MONO_NEW     0x0000000B

#घोषणा BCI_BD_BW_DISABLE            0x10000000
#घोषणा BCI_BD_TILE_MASK             0x03000000
#घोषणा BCI_BD_TILE_NONE             0x00000000
#घोषणा BCI_BD_TILE_16               0x02000000
#घोषणा BCI_BD_TILE_32               0x03000000
#घोषणा BCI_BD_GET_BPP(bd)           (((bd) >> 16) & 0xFF)
#घोषणा BCI_BD_SET_BPP(bd, bpp)      ((bd) |= (((bpp) & 0xFF) << 16))
#घोषणा BCI_BD_GET_STRIDE(bd)        ((bd) & 0xFFFF)
#घोषणा BCI_BD_SET_STRIDE(bd, st)    ((bd) |= ((st) & 0xFFFF))

#घोषणा BCI_CMD_SET_REGISTER            0x96000000

#घोषणा BCI_CMD_WAIT                    0xC0000000
#घोषणा BCI_CMD_WAIT_3D                 0x00010000
#घोषणा BCI_CMD_WAIT_2D                 0x00020000

#घोषणा BCI_CMD_UPDATE_EVENT_TAG        0x98000000

#घोषणा BCI_CMD_DRAW_PRIM               0x80000000
#घोषणा BCI_CMD_DRAW_INDEXED_PRIM       0x88000000
#घोषणा BCI_CMD_DRAW_CONT               0x01000000
#घोषणा BCI_CMD_DRAW_TRILIST            0x00000000
#घोषणा BCI_CMD_DRAW_TRISTRIP           0x02000000
#घोषणा BCI_CMD_DRAW_TRIFAN             0x04000000
#घोषणा BCI_CMD_DRAW_SKIPFLAGS          0x000000ff
#घोषणा BCI_CMD_DRAW_NO_Z		0x00000001
#घोषणा BCI_CMD_DRAW_NO_W		0x00000002
#घोषणा BCI_CMD_DRAW_NO_CD		0x00000004
#घोषणा BCI_CMD_DRAW_NO_CS		0x00000008
#घोषणा BCI_CMD_DRAW_NO_U0		0x00000010
#घोषणा BCI_CMD_DRAW_NO_V0		0x00000020
#घोषणा BCI_CMD_DRAW_NO_UV0		0x00000030
#घोषणा BCI_CMD_DRAW_NO_U1		0x00000040
#घोषणा BCI_CMD_DRAW_NO_V1		0x00000080
#घोषणा BCI_CMD_DRAW_NO_UV1		0x000000c0

#घोषणा BCI_CMD_DMA			0xa8000000

#घोषणा BCI_W_H(w, h)                ((((h) << 16) | (w)) & 0x0FFF0FFF)
#घोषणा BCI_X_Y(x, y)                ((((y) << 16) | (x)) & 0x0FFF0FFF)
#घोषणा BCI_X_W(x, y)                ((((w) << 16) | (x)) & 0x0FFF0FFF)
#घोषणा BCI_CLIP_LR(l, r)            ((((r) << 16) | (l)) & 0x0FFF0FFF)
#घोषणा BCI_CLIP_TL(t, l)            ((((t) << 16) | (l)) & 0x0FFF0FFF)
#घोषणा BCI_CLIP_BR(b, r)            ((((b) << 16) | (r)) & 0x0FFF0FFF)

#घोषणा BCI_LINE_X_Y(x, y)           (((y) << 16) | ((x) & 0xFFFF))
#घोषणा BCI_LINE_STEPS(diag, axi)    (((axi) << 16) | ((diag) & 0xFFFF))
#घोषणा BCI_LINE_MISC(maj, ym, xp, yp, err) \
	(((maj) & 0x1FFF) | \
	((ym) ? 1<<13 : 0) | \
	((xp) ? 1<<14 : 0) | \
	((yp) ? 1<<15 : 0) | \
	((err) << 16))

/*
 * common commands
 */
#घोषणा BCI_SET_REGISTERS( first, n )			\
	BCI_WRITE(BCI_CMD_SET_REGISTER |		\
		  ((uपूर्णांक32_t)(n) & 0xff) << 16 |	\
		  ((uपूर्णांक32_t)(first) & 0xffff))
#घोषणा DMA_SET_REGISTERS( first, n )			\
	DMA_WRITE(BCI_CMD_SET_REGISTER |		\
		  ((uपूर्णांक32_t)(n) & 0xff) << 16 |	\
		  ((uपूर्णांक32_t)(first) & 0xffff))

#घोषणा BCI_DRAW_PRIMITIVE(n, type, skip)         \
        BCI_WRITE(BCI_CMD_DRAW_PRIM | (type) | (skip) | \
		  ((n) << 16))
#घोषणा DMA_DRAW_PRIMITIVE(n, type, skip)         \
        DMA_WRITE(BCI_CMD_DRAW_PRIM | (type) | (skip) | \
		  ((n) << 16))

#घोषणा BCI_DRAW_INDICES_S3D(n, type, i0)         \
        BCI_WRITE(BCI_CMD_DRAW_INDEXED_PRIM | (type) |  \
		  ((n) << 16) | (i0))

#घोषणा BCI_DRAW_INDICES_S4(n, type, skip)        \
        BCI_WRITE(BCI_CMD_DRAW_INDEXED_PRIM | (type) |  \
                  (skip) | ((n) << 16))

#घोषणा BCI_DMA(n)	\
	BCI_WRITE(BCI_CMD_DMA | (((n) >> 1) - 1))

/*
 * access to MMIO
 */
#घोषणा SAVAGE_READ(reg) \
       पढ़ोl(((व्योम __iomem *)dev_priv->mmio->handle) + (reg))
#घोषणा SAVAGE_WRITE(reg) \
	ग_लिखोl(val, ((व्योम __iomem *)dev_priv->mmio->handle) + (reg))

/*
 * access to the burst command पूर्णांकerface (BCI)
 */
#घोषणा SAVAGE_BCI_DEBUG 1

#घोषणा BCI_LOCALS    अस्थिर uपूर्णांक32_t *bci_ptr;

#घोषणा BEGIN_BCI( n ) करो अणु			\
	dev_priv->रुको_fअगरo(dev_priv, (n));	\
	bci_ptr = dev_priv->bci_ptr;		\
पूर्ण जबतक(0)

#घोषणा BCI_WRITE( val ) *bci_ptr++ = (uपूर्णांक32_t)(val)

/*
 * command DMA support
 */
#घोषणा SAVAGE_DMA_DEBUG 1

#घोषणा DMA_LOCALS   uपूर्णांक32_t *dma_ptr;

#घोषणा BEGIN_DMA( n ) करो अणु						\
	अचिन्हित पूर्णांक cur = dev_priv->current_dma_page;			\
	अचिन्हित पूर्णांक rest = SAVAGE_DMA_PAGE_SIZE -			\
		dev_priv->dma_pages[cur].used;				\
	अगर ((n) > rest) अणु						\
		dma_ptr = savage_dma_alloc(dev_priv, (n));		\
	पूर्ण अन्यथा अणु /* fast path क्रम small allocations */			\
		dma_ptr = (uपूर्णांक32_t *)dev_priv->cmd_dma->handle +	\
			cur * SAVAGE_DMA_PAGE_SIZE +			\
			dev_priv->dma_pages[cur].used;			\
		अगर (dev_priv->dma_pages[cur].used == 0)			\
			savage_dma_रुको(dev_priv, cur);			\
		dev_priv->dma_pages[cur].used += (n);			\
	पूर्ण								\
पूर्ण जबतक(0)

#घोषणा DMA_WRITE( val ) *dma_ptr++ = (uपूर्णांक32_t)(val)

#घोषणा DMA_COPY(src, n) करो अणु					\
	स_नकल(dma_ptr, (src), (n)*4);				\
	dma_ptr += n;						\
पूर्ण जबतक(0)

#अगर SAVAGE_DMA_DEBUG
#घोषणा DMA_COMMIT() करो अणु						\
	अचिन्हित पूर्णांक cur = dev_priv->current_dma_page;			\
	uपूर्णांक32_t *expected = (uपूर्णांक32_t *)dev_priv->cmd_dma->handle +	\
			cur * SAVAGE_DMA_PAGE_SIZE +			\
			dev_priv->dma_pages[cur].used;			\
	अगर (dma_ptr != expected) अणु					\
		DRM_ERROR("DMA allocation and use don't match: "	\
			  "%p != %p\n", expected, dma_ptr);		\
		savage_dma_reset(dev_priv);				\
	पूर्ण								\
पूर्ण जबतक(0)
#अन्यथा
#घोषणा DMA_COMMIT() करो अणु/* nothing */पूर्ण जबतक(0)
#पूर्ण_अगर

#घोषणा DMA_FLUSH() dev_priv->dma_flush(dev_priv)

/* Buffer aging via event tag
 */

#घोषणा UPDATE_EVENT_COUNTER( ) करो अणु			\
	अगर (dev_priv->status_ptr) अणु			\
		uपूर्णांक16_t count;				\
		/* coordinate with Xserver */		\
		count = dev_priv->status_ptr[1023];	\
		अगर (count < dev_priv->event_counter)	\
			dev_priv->event_wrap++;		\
		dev_priv->event_counter = count;	\
	पूर्ण						\
पूर्ण जबतक(0)

#घोषणा SET_AGE( age, e, w ) करो अणु	\
	(age)->event = e;		\
	(age)->wrap = w;		\
पूर्ण जबतक(0)

#घोषणा TEST_AGE( age, e, w )				\
	( (age)->wrap < (w) || ( (age)->wrap == (w) && (age)->event <= (e) ) )

#पूर्ण_अगर				/* __SAVAGE_DRV_H__ */
