<शैली गुरु>
/* i810_drv.h -- Private header क्रम the Matrox g200/g400 driver -*- linux-c -*-
 * Created: Mon Dec 13 01:50:01 1999 by jharपंचांगann@precisioninsight.com
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
 * PRECISION INSIGHT AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 * Authors: Rickard E. (Rik) Faith <faith@valinux.com>
 *	    Jeff Harपंचांगann <jharपंचांगann@valinux.com>
 *
 */

#अगर_अघोषित _I810_DRV_H_
#घोषणा _I810_DRV_H_

#समावेश <drm/drm_ioctl.h>
#समावेश <drm/drm_legacy.h>
#समावेश <drm/i810_drm.h>

/* General customization:
 */

#घोषणा DRIVER_AUTHOR		"VA Linux Systems Inc."

#घोषणा DRIVER_NAME		"i810"
#घोषणा DRIVER_DESC		"Intel i810"
#घोषणा DRIVER_DATE		"20030605"

/* Interface history
 *
 * 1.1   - XFree86 4.1
 * 1.2   - XvMC पूर्णांकerfaces
 *       - XFree86 4.2
 * 1.2.1 - Disable copying code (leave stub ioctls क्रम backwards compatibility)
 *       - Remove requirement क्रम पूर्णांकerrupt (leave stubs again)
 * 1.3   - Add page flipping.
 * 1.4   - fix DRM पूर्णांकerface
 */
#घोषणा DRIVER_MAJOR		1
#घोषणा DRIVER_MINOR		4
#घोषणा DRIVER_PATCHLEVEL	0

प्रकार काष्ठा drm_i810_buf_priv अणु
	u32 *in_use;
	पूर्णांक my_use_idx;
	पूर्णांक currently_mapped;
	व्योम *भव;
	व्योम *kernel_भव;
	drm_local_map_t map;
पूर्ण drm_i810_buf_priv_t;

प्रकार काष्ठा _drm_i810_ring_buffer अणु
	पूर्णांक tail_mask;
	अचिन्हित दीर्घ Start;
	अचिन्हित दीर्घ End;
	अचिन्हित दीर्घ Size;
	u8 *भव_start;
	पूर्णांक head;
	पूर्णांक tail;
	पूर्णांक space;
	drm_local_map_t map;
पूर्ण drm_i810_ring_buffer_t;

प्रकार काष्ठा drm_i810_निजी अणु
	काष्ठा drm_local_map *sarea_map;
	काष्ठा drm_local_map *mmio_map;

	drm_i810_sarea_t *sarea_priv;
	drm_i810_ring_buffer_t ring;

	व्योम *hw_status_page;
	अचिन्हित दीर्घ counter;

	dma_addr_t dma_status_page;

	काष्ठा drm_buf *mmap_buffer;

	u32 front_di1, back_di1, zi1;

	पूर्णांक back_offset;
	पूर्णांक depth_offset;
	पूर्णांक overlay_offset;
	पूर्णांक overlay_physical;
	पूर्णांक w, h;
	पूर्णांक pitch;
	पूर्णांक back_pitch;
	पूर्णांक depth_pitch;

	पूर्णांक करो_boxes;
	पूर्णांक dma_used;

	पूर्णांक current_page;
	पूर्णांक page_flipping;

	रुको_queue_head_t irq_queue;
	atomic_t irq_received;
	atomic_t irq_emitted;

	पूर्णांक front_offset;
पूर्ण drm_i810_निजी_t;

				/* i810_dma.c */
बाह्य पूर्णांक i810_driver_dma_quiescent(काष्ठा drm_device *dev);
व्योम i810_driver_reclaim_buffers(काष्ठा drm_device *dev,
			         काष्ठा drm_file *file_priv);
बाह्य पूर्णांक i810_driver_load(काष्ठा drm_device *, अचिन्हित दीर्घ flags);
बाह्य व्योम i810_driver_lastबंद(काष्ठा drm_device *dev);
बाह्य व्योम i810_driver_preबंद(काष्ठा drm_device *dev,
				 काष्ठा drm_file *file_priv);

बाह्य दीर्घ i810_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg);
बाह्य स्थिर काष्ठा drm_ioctl_desc i810_ioctls[];
बाह्य पूर्णांक i810_max_ioctl;

#घोषणा I810_BASE(reg)		((अचिन्हित दीर्घ) \
				dev_priv->mmio_map->handle)
#घोषणा I810_ADDR(reg)		(I810_BASE(reg) + reg)
#घोषणा I810_DEREF(reg)		(*(__अस्थिर__ पूर्णांक *)I810_ADDR(reg))
#घोषणा I810_READ(reg)		I810_DEREF(reg)
#घोषणा I810_WRITE(reg, val)	करो अणु I810_DEREF(reg) = val; पूर्ण जबतक (0)
#घोषणा I810_DEREF16(reg)	(*(__अस्थिर__ u16 *)I810_ADDR(reg))
#घोषणा I810_READ16(reg)	I810_DEREF16(reg)
#घोषणा I810_WRITE16(reg, val)	करो अणु I810_DEREF16(reg) = val; पूर्ण जबतक (0)

#घोषणा I810_VERBOSE 0
#घोषणा RING_LOCALS	अचिन्हित पूर्णांक outring, ringmask; \
			अस्थिर अक्षर *virt;

#घोषणा BEGIN_LP_RING(n) करो अणु					\
	अगर (I810_VERBOSE)					\
		DRM_DEBUG("BEGIN_LP_RING(%d)\n", n);		\
	अगर (dev_priv->ring.space < n*4)				\
		i810_रुको_ring(dev, n*4);			\
	dev_priv->ring.space -= n*4;				\
	outring = dev_priv->ring.tail;				\
	ringmask = dev_priv->ring.tail_mask;			\
	virt = dev_priv->ring.भव_start;			\
पूर्ण जबतक (0)

#घोषणा ADVANCE_LP_RING() करो अणु					\
	अगर (I810_VERBOSE)					\
		DRM_DEBUG("ADVANCE_LP_RING\n");			\
	dev_priv->ring.tail = outring;				\
	I810_WRITE(LP_RING + RING_TAIL, outring);		\
पूर्ण जबतक (0)

#घोषणा OUT_RING(n) करो अणु					\
	अगर (I810_VERBOSE)					\
		DRM_DEBUG("   OUT_RING %x\n", (पूर्णांक)(n));	\
	*(अस्थिर अचिन्हित पूर्णांक *)(virt + outring) = n;		\
	outring += 4;						\
	outring &= ringmask;					\
पूर्ण जबतक (0)

#घोषणा GFX_OP_USER_INTERRUPT		((0<<29)|(2<<23))
#घोषणा GFX_OP_BREAKPOINT_INTERRUPT	((0<<29)|(1<<23))
#घोषणा CMD_REPORT_HEAD			(7<<23)
#घोषणा CMD_STORE_DWORD_IDX		((0x21<<23) | 0x1)
#घोषणा CMD_OP_BATCH_BUFFER  ((0x0<<29)|(0x30<<23)|0x1)

#घोषणा INST_PARSER_CLIENT   0x00000000
#घोषणा INST_OP_FLUSH        0x02000000
#घोषणा INST_FLUSH_MAP_CACHE 0x00000001

#घोषणा BB1_START_ADDR_MASK   (~0x7)
#घोषणा BB1_PROTECTED         (1<<0)
#घोषणा BB1_UNPROTECTED       (0<<0)
#घोषणा BB2_END_ADDR_MASK     (~0x7)

#घोषणा I810REG_HWSTAM		0x02098
#घोषणा I810REG_INT_IDENTITY_R	0x020a4
#घोषणा I810REG_INT_MASK_R	0x020a8
#घोषणा I810REG_INT_ENABLE_R	0x020a0

#घोषणा LP_RING			0x2030
#घोषणा HP_RING			0x2040
#घोषणा RING_TAIL		0x00
#घोषणा TAIL_ADDR		0x000FFFF8
#घोषणा RING_HEAD		0x04
#घोषणा HEAD_WRAP_COUNT		0xFFE00000
#घोषणा HEAD_WRAP_ONE		0x00200000
#घोषणा HEAD_ADDR		0x001FFFFC
#घोषणा RING_START		0x08
#घोषणा START_ADDR		0x00FFFFF8
#घोषणा RING_LEN		0x0C
#घोषणा RING_NR_PAGES		0x000FF000
#घोषणा RING_REPORT_MASK	0x00000006
#घोषणा RING_REPORT_64K		0x00000002
#घोषणा RING_REPORT_128K	0x00000004
#घोषणा RING_NO_REPORT		0x00000000
#घोषणा RING_VALID_MASK		0x00000001
#घोषणा RING_VALID		0x00000001
#घोषणा RING_INVALID		0x00000000

#घोषणा GFX_OP_SCISSOR         ((0x3<<29)|(0x1c<<24)|(0x10<<19))
#घोषणा SC_UPDATE_SCISSOR       (0x1<<1)
#घोषणा SC_ENABLE_MASK          (0x1<<0)
#घोषणा SC_ENABLE               (0x1<<0)

#घोषणा GFX_OP_SCISSOR_INFO    ((0x3<<29)|(0x1d<<24)|(0x81<<16)|(0x1))
#घोषणा SCI_YMIN_MASK      (0xffff<<16)
#घोषणा SCI_XMIN_MASK      (0xffff<<0)
#घोषणा SCI_YMAX_MASK      (0xffff<<16)
#घोषणा SCI_XMAX_MASK      (0xffff<<0)

#घोषणा GFX_OP_COLOR_FACTOR      ((0x3<<29)|(0x1d<<24)|(0x1<<16)|0x0)
#घोषणा GFX_OP_STIPPLE           ((0x3<<29)|(0x1d<<24)|(0x83<<16))
#घोषणा GFX_OP_MAP_INFO          ((0x3<<29)|(0x1d<<24)|0x2)
#घोषणा GFX_OP_DESTBUFFER_VARS   ((0x3<<29)|(0x1d<<24)|(0x85<<16)|0x0)
#घोषणा GFX_OP_DRAWRECT_INFO     ((0x3<<29)|(0x1d<<24)|(0x80<<16)|(0x3))
#घोषणा GFX_OP_PRIMITIVE         ((0x3<<29)|(0x1f<<24))

#घोषणा CMD_OP_Z_BUFFER_INFO     ((0x0<<29)|(0x16<<23))
#घोषणा CMD_OP_DESTBUFFER_INFO   ((0x0<<29)|(0x15<<23))
#घोषणा CMD_OP_FRONTBUFFER_INFO  ((0x0<<29)|(0x14<<23))
#घोषणा CMD_OP_WAIT_FOR_EVENT    ((0x0<<29)|(0x03<<23))

#घोषणा BR00_BITBLT_CLIENT   0x40000000
#घोषणा BR00_OP_COLOR_BLT    0x10000000
#घोषणा BR00_OP_SRC_COPY_BLT 0x10C00000
#घोषणा BR13_SOLID_PATTERN   0x80000000

#घोषणा WAIT_FOR_PLANE_A_SCANLINES (1<<1)
#घोषणा WAIT_FOR_PLANE_A_FLIP      (1<<2)
#घोषणा WAIT_FOR_VBLANK (1<<3)

#पूर्ण_अगर
