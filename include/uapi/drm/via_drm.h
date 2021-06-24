<शैली गुरु>
/*
 * Copyright 1998-2003 VIA Technologies, Inc. All Rights Reserved.
 * Copyright 2001-2003 S3 Graphics, Inc. All Rights Reserved.
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
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. IN NO EVENT SHALL
 * VIA, S3 GRAPHICS, AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */
#अगर_अघोषित _VIA_DRM_H_
#घोषणा _VIA_DRM_H_

#समावेश "drm.h"

#अगर defined(__cplusplus)
बाह्य "C" अणु
#पूर्ण_अगर

/* WARNING: These defines must be the same as what the Xserver uses.
 * अगर you change them, you must change the defines in the Xserver.
 */

#अगर_अघोषित _VIA_DEFINES_
#घोषणा _VIA_DEFINES_


#घोषणा VIA_NR_SAREA_CLIPRECTS		8
#घोषणा VIA_NR_XVMC_PORTS               10
#घोषणा VIA_NR_XVMC_LOCKS               5
#घोषणा VIA_MAX_CACHELINE_SIZE          64
#घोषणा XVMCLOCKPTR(saPriv,lockNo)					\
	((अस्थिर काष्ठा drm_hw_lock *)(((((अचिन्हित दीर्घ) (saPriv)->XvMCLockArea) + \
				      (VIA_MAX_CACHELINE_SIZE - 1)) &	\
				     ~(VIA_MAX_CACHELINE_SIZE - 1)) +	\
				    VIA_MAX_CACHELINE_SIZE*(lockNo)))

/* Each region is a minimum of 64k, and there are at most 64 of them.
 */
#घोषणा VIA_NR_TEX_REGIONS 64
#घोषणा VIA_LOG_MIN_TEX_REGION_SIZE 16
#पूर्ण_अगर

#घोषणा VIA_UPLOAD_TEX0IMAGE  0x1	/* handled clientside */
#घोषणा VIA_UPLOAD_TEX1IMAGE  0x2	/* handled clientside */
#घोषणा VIA_UPLOAD_CTX        0x4
#घोषणा VIA_UPLOAD_BUFFERS    0x8
#घोषणा VIA_UPLOAD_TEX0       0x10
#घोषणा VIA_UPLOAD_TEX1       0x20
#घोषणा VIA_UPLOAD_CLIPRECTS  0x40
#घोषणा VIA_UPLOAD_ALL        0xff

/* VIA specअगरic ioctls */
#घोषणा DRM_VIA_ALLOCMEM	0x00
#घोषणा DRM_VIA_FREEMEM	        0x01
#घोषणा DRM_VIA_AGP_INIT	0x02
#घोषणा DRM_VIA_FB_INIT	        0x03
#घोषणा DRM_VIA_MAP_INIT	0x04
#घोषणा DRM_VIA_DEC_FUTEX       0x05
#घोषणा NOT_USED
#घोषणा DRM_VIA_DMA_INIT	0x07
#घोषणा DRM_VIA_CMDBUFFER	0x08
#घोषणा DRM_VIA_FLUSH	        0x09
#घोषणा DRM_VIA_PCICMD	        0x0a
#घोषणा DRM_VIA_CMDBUF_SIZE	0x0b
#घोषणा NOT_USED
#घोषणा DRM_VIA_WAIT_IRQ        0x0d
#घोषणा DRM_VIA_DMA_BLIT        0x0e
#घोषणा DRM_VIA_BLIT_SYNC       0x0f

#घोषणा DRM_IOCTL_VIA_ALLOCMEM	  DRM_IOWR(DRM_COMMAND_BASE + DRM_VIA_ALLOCMEM, drm_via_mem_t)
#घोषणा DRM_IOCTL_VIA_FREEMEM	  DRM_IOW( DRM_COMMAND_BASE + DRM_VIA_FREEMEM, drm_via_mem_t)
#घोषणा DRM_IOCTL_VIA_AGP_INIT	  DRM_IOWR(DRM_COMMAND_BASE + DRM_VIA_AGP_INIT, drm_via_agp_t)
#घोषणा DRM_IOCTL_VIA_FB_INIT	  DRM_IOWR(DRM_COMMAND_BASE + DRM_VIA_FB_INIT, drm_via_fb_t)
#घोषणा DRM_IOCTL_VIA_MAP_INIT	  DRM_IOWR(DRM_COMMAND_BASE + DRM_VIA_MAP_INIT, drm_via_init_t)
#घोषणा DRM_IOCTL_VIA_DEC_FUTEX   DRM_IOW( DRM_COMMAND_BASE + DRM_VIA_DEC_FUTEX, drm_via_futex_t)
#घोषणा DRM_IOCTL_VIA_DMA_INIT	  DRM_IOWR(DRM_COMMAND_BASE + DRM_VIA_DMA_INIT, drm_via_dma_init_t)
#घोषणा DRM_IOCTL_VIA_CMDBUFFER	  DRM_IOW( DRM_COMMAND_BASE + DRM_VIA_CMDBUFFER, drm_via_cmdbuffer_t)
#घोषणा DRM_IOCTL_VIA_FLUSH	  DRM_IO(  DRM_COMMAND_BASE + DRM_VIA_FLUSH)
#घोषणा DRM_IOCTL_VIA_PCICMD	  DRM_IOW( DRM_COMMAND_BASE + DRM_VIA_PCICMD, drm_via_cmdbuffer_t)
#घोषणा DRM_IOCTL_VIA_CMDBUF_SIZE DRM_IOWR( DRM_COMMAND_BASE + DRM_VIA_CMDBUF_SIZE, \
					    drm_via_cmdbuf_माप_प्रकार)
#घोषणा DRM_IOCTL_VIA_WAIT_IRQ    DRM_IOWR( DRM_COMMAND_BASE + DRM_VIA_WAIT_IRQ, drm_via_irqरुको_t)
#घोषणा DRM_IOCTL_VIA_DMA_BLIT    DRM_IOW(DRM_COMMAND_BASE + DRM_VIA_DMA_BLIT, drm_via_dmablit_t)
#घोषणा DRM_IOCTL_VIA_BLIT_SYNC   DRM_IOW(DRM_COMMAND_BASE + DRM_VIA_BLIT_SYNC, drm_via_blitsync_t)

/* Indices पूर्णांकo buf.Setup where various bits of state are mirrored per
 * context and per buffer.  These can be fired at the card as a unit,
 * or in a piecewise fashion as required.
 */

#घोषणा VIA_TEX_SETUP_SIZE 8

/* Flags क्रम clear ioctl
 */
#घोषणा VIA_FRONT   0x1
#घोषणा VIA_BACK    0x2
#घोषणा VIA_DEPTH   0x4
#घोषणा VIA_STENCIL 0x8
#घोषणा VIA_MEM_VIDEO   0	/* matches drm स्थिरant */
#घोषणा VIA_MEM_AGP     1	/* matches drm स्थिरant */
#घोषणा VIA_MEM_SYSTEM  2
#घोषणा VIA_MEM_MIXED   3
#घोषणा VIA_MEM_UNKNOWN 4

प्रकार काष्ठा अणु
	__u32 offset;
	__u32 size;
पूर्ण drm_via_agp_t;

प्रकार काष्ठा अणु
	__u32 offset;
	__u32 size;
पूर्ण drm_via_fb_t;

प्रकार काष्ठा अणु
	__u32 context;
	__u32 type;
	__u32 size;
	अचिन्हित दीर्घ index;
	अचिन्हित दीर्घ offset;
पूर्ण drm_via_mem_t;

प्रकार काष्ठा _drm_via_init अणु
	क्रमागत अणु
		VIA_INIT_MAP = 0x01,
		VIA_CLEANUP_MAP = 0x02
	पूर्ण func;

	अचिन्हित दीर्घ sarea_priv_offset;
	अचिन्हित दीर्घ fb_offset;
	अचिन्हित दीर्घ mmio_offset;
	अचिन्हित दीर्घ agpAddr;
पूर्ण drm_via_init_t;

प्रकार काष्ठा _drm_via_futex अणु
	क्रमागत अणु
		VIA_FUTEX_WAIT = 0x00,
		VIA_FUTEX_WAKE = 0X01
	पूर्ण func;
	__u32 ms;
	__u32 lock;
	__u32 val;
पूर्ण drm_via_futex_t;

प्रकार काष्ठा _drm_via_dma_init अणु
	क्रमागत अणु
		VIA_INIT_DMA = 0x01,
		VIA_CLEANUP_DMA = 0x02,
		VIA_DMA_INITIALIZED = 0x03
	पूर्ण func;

	अचिन्हित दीर्घ offset;
	अचिन्हित दीर्घ size;
	अचिन्हित दीर्घ reg_छोड़ो_addr;
पूर्ण drm_via_dma_init_t;

प्रकार काष्ठा _drm_via_cmdbuffer अणु
	अक्षर __user *buf;
	अचिन्हित दीर्घ size;
पूर्ण drm_via_cmdbuffer_t;

/* Warning: If you change the SAREA काष्ठाure you must change the Xserver
 * काष्ठाure as well */

प्रकार काष्ठा _drm_via_tex_region अणु
	अचिन्हित अक्षर next, prev;	/* indices to क्रमm a circular LRU  */
	अचिन्हित अक्षर inUse;	/* owned by a client, or मुक्त? */
	पूर्णांक age;		/* tracked by clients to update local LRU's */
पूर्ण drm_via_tex_region_t;

प्रकार काष्ठा _drm_via_sarea अणु
	अचिन्हित पूर्णांक dirty;
	अचिन्हित पूर्णांक nbox;
	काष्ठा drm_clip_rect boxes[VIA_NR_SAREA_CLIPRECTS];
	drm_via_tex_region_t texList[VIA_NR_TEX_REGIONS + 1];
	पूर्णांक texAge;		/* last समय texture was uploaded */
	पूर्णांक ctxOwner;		/* last context to upload state */
	पूर्णांक vertexPrim;

	/*
	 * Below is क्रम XvMC.
	 * We want the lock पूर्णांकegers alone on, and aligned to, a cache line.
	 * Thereक्रमe this somewhat strange स्थिरruct.
	 */

	अक्षर XvMCLockArea[VIA_MAX_CACHELINE_SIZE * (VIA_NR_XVMC_LOCKS + 1)];

	अचिन्हित पूर्णांक XvMCDisplaying[VIA_NR_XVMC_PORTS];
	अचिन्हित पूर्णांक XvMCSubPicOn[VIA_NR_XVMC_PORTS];
	अचिन्हित पूर्णांक XvMCCtxNoGrabbed;	/* Last context to hold decoder */

	/* Used by the 3d driver only at this poपूर्णांक, क्रम pageflipping:
	 */
	अचिन्हित पूर्णांक pfCurrentOffset;
पूर्ण drm_via_sarea_t;

प्रकार काष्ठा _drm_via_cmdbuf_size अणु
	क्रमागत अणु
		VIA_CMDBUF_SPACE = 0x01,
		VIA_CMDBUF_LAG = 0x02
	पूर्ण func;
	पूर्णांक रुको;
	__u32 size;
पूर्ण drm_via_cmdbuf_माप_प्रकार;

प्रकार क्रमागत अणु
	VIA_IRQ_ABSOLUTE = 0x0,
	VIA_IRQ_RELATIVE = 0x1,
	VIA_IRQ_SIGNAL = 0x10000000,
	VIA_IRQ_FORCE_SEQUENCE = 0x20000000
पूर्ण via_irq_seq_type_t;

#घोषणा VIA_IRQ_FLAGS_MASK 0xF0000000

क्रमागत drm_via_irqs अणु
	drm_via_irq_hqv0 = 0,
	drm_via_irq_hqv1,
	drm_via_irq_dma0_dd,
	drm_via_irq_dma0_td,
	drm_via_irq_dma1_dd,
	drm_via_irq_dma1_td,
	drm_via_irq_num
पूर्ण;

काष्ठा drm_via_रुको_irq_request अणु
	अचिन्हित irq;
	via_irq_seq_type_t type;
	__u32 sequence;
	__u32 संकेत;
पूर्ण;

प्रकार जोड़ drm_via_irqरुको अणु
	काष्ठा drm_via_रुको_irq_request request;
	काष्ठा drm_रुको_vblank_reply reply;
पूर्ण drm_via_irqरुको_t;

प्रकार काष्ठा drm_via_blitsync अणु
	__u32 sync_handle;
	अचिन्हित engine;
पूर्ण drm_via_blitsync_t;

/* - * Below,"flags" is currently unused but will be used क्रम possible future
 * extensions like kernel space bounce buffers क्रम bad alignments and
 * blit engine busy-रुको polling क्रम better latency in the असलence of
 * पूर्णांकerrupts.
 */

प्रकार काष्ठा drm_via_dmablit अणु
	__u32 num_lines;
	__u32 line_length;

	__u32 fb_addr;
	__u32 fb_stride;

	अचिन्हित अक्षर *mem_addr;
	__u32 mem_stride;

	__u32 flags;
	पूर्णांक to_fb;

	drm_via_blitsync_t sync;
पूर्ण drm_via_dmablit_t;

#अगर defined(__cplusplus)
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर				/* _VIA_DRM_H_ */
