<शैली गुरु>
/* savage_drm.h -- Public header क्रम the savage driver
 *
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

#अगर_अघोषित __SAVAGE_DRM_H__
#घोषणा __SAVAGE_DRM_H__

#समावेश "drm.h"

#अगर defined(__cplusplus)
बाह्य "C" अणु
#पूर्ण_अगर

#अगर_अघोषित __SAVAGE_SAREA_DEFINES__
#घोषणा __SAVAGE_SAREA_DEFINES__

/* 2 heaps (1 क्रम card, 1 क्रम agp), each भागided पूर्णांकo up to 128
 * regions, subject to a minimum region size of (1<<16) == 64k.
 *
 * Clients may subभागide regions पूर्णांकernally, but when sharing between
 * clients, the region size is the minimum granularity.
 */

#घोषणा SAVAGE_CARD_HEAP		0
#घोषणा SAVAGE_AGP_HEAP			1
#घोषणा SAVAGE_NR_TEX_HEAPS		2
#घोषणा SAVAGE_NR_TEX_REGIONS		16
#घोषणा SAVAGE_LOG_MIN_TEX_REGION_SIZE	16

#पूर्ण_अगर				/* __SAVAGE_SAREA_DEFINES__ */

प्रकार काष्ठा _drm_savage_sarea अणु
	/* LRU lists क्रम texture memory in agp space and on the card.
	 */
	काष्ठा drm_tex_region texList[SAVAGE_NR_TEX_HEAPS][SAVAGE_NR_TEX_REGIONS +
						      1];
	अचिन्हित पूर्णांक texAge[SAVAGE_NR_TEX_HEAPS];

	/* Mechanism to validate card state.
	 */
	पूर्णांक ctxOwner;
पूर्ण drm_savage_sarea_t, *drm_savage_sarea_ptr;

/* Savage-specअगरic ioctls
 */
#घोषणा DRM_SAVAGE_BCI_INIT		0x00
#घोषणा DRM_SAVAGE_BCI_CMDBUF           0x01
#घोषणा DRM_SAVAGE_BCI_EVENT_EMIT	0x02
#घोषणा DRM_SAVAGE_BCI_EVENT_WAIT	0x03

#घोषणा DRM_IOCTL_SAVAGE_BCI_INIT		DRM_IOW( DRM_COMMAND_BASE + DRM_SAVAGE_BCI_INIT, drm_savage_init_t)
#घोषणा DRM_IOCTL_SAVAGE_BCI_CMDBUF		DRM_IOW( DRM_COMMAND_BASE + DRM_SAVAGE_BCI_CMDBUF, drm_savage_cmdbuf_t)
#घोषणा DRM_IOCTL_SAVAGE_BCI_EVENT_EMIT	DRM_IOWR(DRM_COMMAND_BASE + DRM_SAVAGE_BCI_EVENT_EMIT, drm_savage_event_emit_t)
#घोषणा DRM_IOCTL_SAVAGE_BCI_EVENT_WAIT	DRM_IOW( DRM_COMMAND_BASE + DRM_SAVAGE_BCI_EVENT_WAIT, drm_savage_event_रुको_t)

#घोषणा SAVAGE_DMA_PCI	1
#घोषणा SAVAGE_DMA_AGP	3
प्रकार काष्ठा drm_savage_init अणु
	क्रमागत अणु
		SAVAGE_INIT_BCI = 1,
		SAVAGE_CLEANUP_BCI = 2
	पूर्ण func;
	अचिन्हित पूर्णांक sarea_priv_offset;

	/* some parameters */
	अचिन्हित पूर्णांक cob_size;
	अचिन्हित पूर्णांक bci_threshold_lo, bci_threshold_hi;
	अचिन्हित पूर्णांक dma_type;

	/* frame buffer layout */
	अचिन्हित पूर्णांक fb_bpp;
	अचिन्हित पूर्णांक front_offset, front_pitch;
	अचिन्हित पूर्णांक back_offset, back_pitch;
	अचिन्हित पूर्णांक depth_bpp;
	अचिन्हित पूर्णांक depth_offset, depth_pitch;

	/* local textures */
	अचिन्हित पूर्णांक texture_offset;
	अचिन्हित पूर्णांक texture_size;

	/* physical locations of non-permanent maps */
	अचिन्हित दीर्घ status_offset;
	अचिन्हित दीर्घ buffers_offset;
	अचिन्हित दीर्घ agp_textures_offset;
	अचिन्हित दीर्घ cmd_dma_offset;
पूर्ण drm_savage_init_t;

प्रकार जोड़ drm_savage_cmd_header drm_savage_cmd_header_t;
प्रकार काष्ठा drm_savage_cmdbuf अणु
	/* command buffer in client's address space */
	drm_savage_cmd_header_t __user *cmd_addr;
	अचिन्हित पूर्णांक size;	/* size of the command buffer in 64bit units */

	अचिन्हित पूर्णांक dma_idx;	/* DMA buffer index to use */
	पूर्णांक discard;		/* discard DMA buffer when करोne */
	/* vertex buffer in client's address space */
	अचिन्हित पूर्णांक __user *vb_addr;
	अचिन्हित पूर्णांक vb_size;	/* size of client vertex buffer in bytes */
	अचिन्हित पूर्णांक vb_stride;	/* stride of vertices in 32bit words */
	/* boxes in client's address space */
	काष्ठा drm_clip_rect __user *box_addr;
	अचिन्हित पूर्णांक nbox;	/* number of clipping boxes */
पूर्ण drm_savage_cmdbuf_t;

#घोषणा SAVAGE_WAIT_2D  0x1	/* रुको क्रम 2D idle beक्रमe updating event tag */
#घोषणा SAVAGE_WAIT_3D  0x2	/* रुको क्रम 3D idle beक्रमe updating event tag */
#घोषणा SAVAGE_WAIT_IRQ 0x4	/* emit or रुको क्रम IRQ, not implemented yet */
प्रकार काष्ठा drm_savage_event अणु
	अचिन्हित पूर्णांक count;
	अचिन्हित पूर्णांक flags;
पूर्ण drm_savage_event_emit_t, drm_savage_event_रुको_t;

/* Commands क्रम the cmdbuf ioctl
 */
#घोषणा SAVAGE_CMD_STATE	0	/* a range of state रेजिस्टरs */
#घोषणा SAVAGE_CMD_DMA_PRIM	1	/* vertices from DMA buffer */
#घोषणा SAVAGE_CMD_VB_PRIM	2	/* vertices from client vertex buffer */
#घोषणा SAVAGE_CMD_DMA_IDX	3	/* indexed vertices from DMA buffer */
#घोषणा SAVAGE_CMD_VB_IDX	4	/* indexed vertices client vertex buffer */
#घोषणा SAVAGE_CMD_CLEAR	5	/* clear buffers */
#घोषणा SAVAGE_CMD_SWAP		6	/* swap buffers */

/* Primitive types
*/
#घोषणा SAVAGE_PRIM_TRILIST	0	/* triangle list */
#घोषणा SAVAGE_PRIM_TRISTRIP	1	/* triangle strip */
#घोषणा SAVAGE_PRIM_TRIFAN	2	/* triangle fan */
#घोषणा SAVAGE_PRIM_TRILIST_201	3	/* reorder verts क्रम correct flat
					 * shading on s3d */

/* Skip flags (vertex क्रमmat)
 */
#घोषणा SAVAGE_SKIP_Z		0x01
#घोषणा SAVAGE_SKIP_W		0x02
#घोषणा SAVAGE_SKIP_C0		0x04
#घोषणा SAVAGE_SKIP_C1		0x08
#घोषणा SAVAGE_SKIP_S0		0x10
#घोषणा SAVAGE_SKIP_T0		0x20
#घोषणा SAVAGE_SKIP_ST0		0x30
#घोषणा SAVAGE_SKIP_S1		0x40
#घोषणा SAVAGE_SKIP_T1		0x80
#घोषणा SAVAGE_SKIP_ST1		0xc0
#घोषणा SAVAGE_SKIP_ALL_S3D	0x3f
#घोषणा SAVAGE_SKIP_ALL_S4	0xff

/* Buffer names क्रम clear command
 */
#घोषणा SAVAGE_FRONT		0x1
#घोषणा SAVAGE_BACK		0x2
#घोषणा SAVAGE_DEPTH		0x4

/* 64-bit command header
 */
जोड़ drm_savage_cmd_header अणु
	काष्ठा अणु
		अचिन्हित अक्षर cmd;	/* command */
		अचिन्हित अक्षर pad0;
		अचिन्हित लघु pad1;
		अचिन्हित लघु pad2;
		अचिन्हित लघु pad3;
	पूर्ण cmd;			/* generic */
	काष्ठा अणु
		अचिन्हित अक्षर cmd;
		अचिन्हित अक्षर global;	/* need idle engine? */
		अचिन्हित लघु count;	/* number of consecutive रेजिस्टरs */
		अचिन्हित लघु start;	/* first रेजिस्टर */
		अचिन्हित लघु pad3;
	पूर्ण state;		/* SAVAGE_CMD_STATE */
	काष्ठा अणु
		अचिन्हित अक्षर cmd;
		अचिन्हित अक्षर prim;	/* primitive type */
		अचिन्हित लघु skip;	/* vertex क्रमmat (skip flags) */
		अचिन्हित लघु count;	/* number of vertices */
		अचिन्हित लघु start;	/* first vertex in DMA/vertex buffer */
	पूर्ण prim;			/* SAVAGE_CMD_DMA_PRIM, SAVAGE_CMD_VB_PRIM */
	काष्ठा अणु
		अचिन्हित अक्षर cmd;
		अचिन्हित अक्षर prim;
		अचिन्हित लघु skip;
		अचिन्हित लघु count;	/* number of indices that follow */
		अचिन्हित लघु pad3;
	पूर्ण idx;			/* SAVAGE_CMD_DMA_IDX, SAVAGE_CMD_VB_IDX */
	काष्ठा अणु
		अचिन्हित अक्षर cmd;
		अचिन्हित अक्षर pad0;
		अचिन्हित लघु pad1;
		अचिन्हित पूर्णांक flags;
	पूर्ण clear0;		/* SAVAGE_CMD_CLEAR */
	काष्ठा अणु
		अचिन्हित पूर्णांक mask;
		अचिन्हित पूर्णांक value;
	पूर्ण clear1;		/* SAVAGE_CMD_CLEAR data */
पूर्ण;

#अगर defined(__cplusplus)
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर
