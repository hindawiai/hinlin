<शैली गुरु>
/* r128_drv.h -- Private header क्रम r128 driver -*- linux-c -*-
 * Created: Mon Dec 13 09:51:11 1999 by faith@precisioninsight.com
 */
/*
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
 * Authors:
 *    Rickard E. (Rik) Faith <faith@valinux.com>
 *    Kevin E. Martin <martin@valinux.com>
 *    Gareth Hughes <gareth@valinux.com>
 *    Michel Doडटzer <daenzerm@student.ethz.ch>
 */

#अगर_अघोषित __R128_DRV_H__
#घोषणा __R128_DRV_H__

#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/irqवापस.h>

#समावेश <drm/drm_ioctl.h>
#समावेश <drm/drm_legacy.h>
#समावेश <drm/r128_drm.h>

#समावेश "ati_pcigart.h"

/* General customization:
 */
#घोषणा DRIVER_AUTHOR		"Gareth Hughes, VA Linux Systems Inc."

#घोषणा DRIVER_NAME		"r128"
#घोषणा DRIVER_DESC		"ATI Rage 128"
#घोषणा DRIVER_DATE		"20030725"

/* Interface history:
 *
 * ??  - ??
 * 2.4 - Add support क्रम ycbcr textures (no new ioctls)
 * 2.5 - Add FLIP ioctl, disable FULLSCREEN.
 */
#घोषणा DRIVER_MAJOR		2
#घोषणा DRIVER_MINOR		5
#घोषणा DRIVER_PATCHLEVEL	0

#घोषणा GET_RING_HEAD(dev_priv)		R128_READ(R128_PM4_BUFFER_DL_RPTR)

प्रकार काष्ठा drm_r128_मुक्तlist अणु
	अचिन्हित पूर्णांक age;
	काष्ठा drm_buf *buf;
	काष्ठा drm_r128_मुक्तlist *next;
	काष्ठा drm_r128_मुक्तlist *prev;
पूर्ण drm_r128_मुक्तlist_t;

प्रकार काष्ठा drm_r128_ring_buffer अणु
	u32 *start;
	u32 *end;
	पूर्णांक size;
	पूर्णांक size_l2qw;

	u32 tail;
	u32 tail_mask;
	पूर्णांक space;

	पूर्णांक high_mark;
पूर्ण drm_r128_ring_buffer_t;

प्रकार काष्ठा drm_r128_निजी अणु
	drm_r128_ring_buffer_t ring;
	drm_r128_sarea_t *sarea_priv;

	पूर्णांक cce_mode;
	पूर्णांक cce_fअगरo_size;
	पूर्णांक cce_running;

	drm_r128_मुक्तlist_t *head;
	drm_r128_मुक्तlist_t *tail;

	पूर्णांक usec_समयout;
	पूर्णांक is_pci;
	अचिन्हित दीर्घ cce_buffers_offset;

	atomic_t idle_count;

	पूर्णांक page_flipping;
	पूर्णांक current_page;
	u32 crtc_offset;
	u32 crtc_offset_cntl;

	atomic_t vbl_received;

	u32 color_fmt;
	अचिन्हित पूर्णांक front_offset;
	अचिन्हित पूर्णांक front_pitch;
	अचिन्हित पूर्णांक back_offset;
	अचिन्हित पूर्णांक back_pitch;

	u32 depth_fmt;
	अचिन्हित पूर्णांक depth_offset;
	अचिन्हित पूर्णांक depth_pitch;
	अचिन्हित पूर्णांक span_offset;

	u32 front_pitch_offset_c;
	u32 back_pitch_offset_c;
	u32 depth_pitch_offset_c;
	u32 span_pitch_offset_c;

	drm_local_map_t *sarea;
	drm_local_map_t *mmio;
	drm_local_map_t *cce_ring;
	drm_local_map_t *ring_rptr;
	drm_local_map_t *agp_textures;
	काष्ठा drm_ati_pcigart_info gart_info;
पूर्ण drm_r128_निजी_t;

प्रकार काष्ठा drm_r128_buf_priv अणु
	u32 age;
	पूर्णांक prim;
	पूर्णांक discard;
	पूर्णांक dispatched;
	drm_r128_मुक्तlist_t *list_entry;
पूर्ण drm_r128_buf_priv_t;

बाह्य स्थिर काष्ठा drm_ioctl_desc r128_ioctls[];
बाह्य पूर्णांक r128_max_ioctl;

				/* r128_cce.c */
बाह्य पूर्णांक r128_cce_init(काष्ठा drm_device *dev, व्योम *data, काष्ठा drm_file *file_priv);
बाह्य पूर्णांक r128_cce_start(काष्ठा drm_device *dev, व्योम *data, काष्ठा drm_file *file_priv);
बाह्य पूर्णांक r128_cce_stop(काष्ठा drm_device *dev, व्योम *data, काष्ठा drm_file *file_priv);
बाह्य पूर्णांक r128_cce_reset(काष्ठा drm_device *dev, व्योम *data, काष्ठा drm_file *file_priv);
बाह्य पूर्णांक r128_cce_idle(काष्ठा drm_device *dev, व्योम *data, काष्ठा drm_file *file_priv);
बाह्य पूर्णांक r128_engine_reset(काष्ठा drm_device *dev, व्योम *data, काष्ठा drm_file *file_priv);
बाह्य पूर्णांक r128_fullscreen(काष्ठा drm_device *dev, व्योम *data, काष्ठा drm_file *file_priv);
बाह्य पूर्णांक r128_cce_buffers(काष्ठा drm_device *dev, व्योम *data, काष्ठा drm_file *file_priv);

बाह्य पूर्णांक r128_cce_stipple(काष्ठा drm_device *dev, व्योम *data, काष्ठा drm_file *file_priv);
बाह्य पूर्णांक r128_cce_depth(काष्ठा drm_device *dev, व्योम *data, काष्ठा drm_file *file_priv);
बाह्य पूर्णांक r128_getparam(काष्ठा drm_device *dev, व्योम *data, काष्ठा drm_file *file_priv);

बाह्य व्योम r128_मुक्तlist_reset(काष्ठा drm_device *dev);

बाह्य पूर्णांक r128_रुको_ring(drm_r128_निजी_t *dev_priv, पूर्णांक n);

बाह्य पूर्णांक r128_करो_cce_idle(drm_r128_निजी_t *dev_priv);
बाह्य पूर्णांक r128_करो_cleanup_cce(काष्ठा drm_device *dev);

बाह्य पूर्णांक r128_enable_vblank(काष्ठा drm_device *dev, अचिन्हित पूर्णांक pipe);
बाह्य व्योम r128_disable_vblank(काष्ठा drm_device *dev, अचिन्हित पूर्णांक pipe);
बाह्य u32 r128_get_vblank_counter(काष्ठा drm_device *dev, अचिन्हित पूर्णांक pipe);
बाह्य irqवापस_t r128_driver_irq_handler(पूर्णांक irq, व्योम *arg);
बाह्य व्योम r128_driver_irq_preinstall(काष्ठा drm_device *dev);
बाह्य पूर्णांक r128_driver_irq_postinstall(काष्ठा drm_device *dev);
बाह्य व्योम r128_driver_irq_uninstall(काष्ठा drm_device *dev);
बाह्य व्योम r128_driver_lastबंद(काष्ठा drm_device *dev);
बाह्य पूर्णांक r128_driver_load(काष्ठा drm_device *dev, अचिन्हित दीर्घ flags);
बाह्य व्योम r128_driver_preबंद(काष्ठा drm_device *dev,
				 काष्ठा drm_file *file_priv);

बाह्य दीर्घ r128_compat_ioctl(काष्ठा file *filp, अचिन्हित पूर्णांक cmd,
			      अचिन्हित दीर्घ arg);

/* Register definitions, रेजिस्टर access macros and drmAddMap स्थिरants
 * क्रम Rage 128 kernel driver.
 */

#घोषणा R128_AUX_SC_CNTL		0x1660
#	define R128_AUX1_SC_EN			(1 << 0)
#	define R128_AUX1_SC_MODE_OR		(0 << 1)
#	define R128_AUX1_SC_MODE_न_अंकD		(1 << 1)
#	define R128_AUX2_SC_EN			(1 << 2)
#	define R128_AUX2_SC_MODE_OR		(0 << 3)
#	define R128_AUX2_SC_MODE_न_अंकD		(1 << 3)
#	define R128_AUX3_SC_EN			(1 << 4)
#	define R128_AUX3_SC_MODE_OR		(0 << 5)
#	define R128_AUX3_SC_MODE_न_अंकD		(1 << 5)
#घोषणा R128_AUX1_SC_LEFT		0x1664
#घोषणा R128_AUX1_SC_RIGHT		0x1668
#घोषणा R128_AUX1_SC_TOP		0x166c
#घोषणा R128_AUX1_SC_BOTTOM		0x1670
#घोषणा R128_AUX2_SC_LEFT		0x1674
#घोषणा R128_AUX2_SC_RIGHT		0x1678
#घोषणा R128_AUX2_SC_TOP		0x167c
#घोषणा R128_AUX2_SC_BOTTOM		0x1680
#घोषणा R128_AUX3_SC_LEFT		0x1684
#घोषणा R128_AUX3_SC_RIGHT		0x1688
#घोषणा R128_AUX3_SC_TOP		0x168c
#घोषणा R128_AUX3_SC_BOTTOM		0x1690

#घोषणा R128_BRUSH_DATA0		0x1480
#घोषणा R128_BUS_CNTL			0x0030
#	define R128_BUS_MASTER_DIS		(1 << 6)

#घोषणा R128_CLOCK_CNTL_INDEX		0x0008
#घोषणा R128_CLOCK_CNTL_DATA		0x000c
#	define R128_PLL_WR_EN			(1 << 7)
#घोषणा R128_CONSTANT_COLOR_C		0x1d34
#घोषणा R128_CRTC_OFFSET		0x0224
#घोषणा R128_CRTC_OFFSET_CNTL		0x0228
#	define R128_CRTC_OFFSET_FLIP_CNTL	(1 << 16)

#घोषणा R128_DP_GUI_MASTER_CNTL		0x146c
#       define R128_GMC_SRC_PITCH_OFFSET_CNTL	(1    <<  0)
#       define R128_GMC_DST_PITCH_OFFSET_CNTL	(1    <<  1)
#	define R128_GMC_BRUSH_SOLID_COLOR	(13   <<  4)
#	define R128_GMC_BRUSH_NONE		(15   <<  4)
#	define R128_GMC_DST_16BPP		(4    <<  8)
#	define R128_GMC_DST_24BPP		(5    <<  8)
#	define R128_GMC_DST_32BPP		(6    <<  8)
#       define R128_GMC_DST_DATATYPE_SHIFT	8
#	define R128_GMC_SRC_DATATYPE_COLOR	(3    << 12)
#	define R128_DP_SRC_SOURCE_MEMORY	(2    << 24)
#	define R128_DP_SRC_SOURCE_HOST_DATA	(3    << 24)
#	define R128_GMC_CLR_CMP_CNTL_DIS	(1    << 28)
#	define R128_GMC_AUX_CLIP_DIS		(1    << 29)
#	define R128_GMC_WR_MSK_DIS		(1    << 30)
#	define R128_ROP3_S			0x00cc0000
#	define R128_ROP3_P			0x00f00000
#घोषणा R128_DP_WRITE_MASK		0x16cc
#घोषणा R128_DST_PITCH_OFFSET_C		0x1c80
#	define R128_DST_TILE			(1 << 31)

#घोषणा R128_GEN_INT_CNTL		0x0040
#	define R128_CRTC_VBLANK_INT_EN		(1 <<  0)
#घोषणा R128_GEN_INT_STATUS		0x0044
#	define R128_CRTC_VBLANK_INT		(1 <<  0)
#	define R128_CRTC_VBLANK_INT_AK		(1 <<  0)
#घोषणा R128_GEN_RESET_CNTL		0x00f0
#	define R128_SOFT_RESET_GUI		(1 <<  0)

#घोषणा R128_GUI_SCRATCH_REG0		0x15e0
#घोषणा R128_GUI_SCRATCH_REG1		0x15e4
#घोषणा R128_GUI_SCRATCH_REG2		0x15e8
#घोषणा R128_GUI_SCRATCH_REG3		0x15ec
#घोषणा R128_GUI_SCRATCH_REG4		0x15f0
#घोषणा R128_GUI_SCRATCH_REG5		0x15f4

#घोषणा R128_GUI_STAT			0x1740
#	define R128_GUI_FIFOCNT_MASK		0x0fff
#	define R128_GUI_ACTIVE			(1 << 31)

#घोषणा R128_MCLK_CNTL			0x000f
#	define R128_FORCE_GCP			(1 << 16)
#	define R128_FORCE_PIPE3D_CP		(1 << 17)
#	define R128_FORCE_RCP			(1 << 18)

#घोषणा R128_PC_GUI_CTLSTAT		0x1748
#घोषणा R128_PC_NGUI_CTLSTAT		0x0184
#	define R128_PC_FLUSH_GUI		(3 << 0)
#	define R128_PC_RI_GUI			(1 << 2)
#	define R128_PC_FLUSH_ALL		0x00ff
#	define R128_PC_BUSY			(1 << 31)

#घोषणा R128_PCI_GART_PAGE		0x017c
#घोषणा R128_PRIM_TEX_CNTL_C		0x1cb0

#घोषणा R128_SCALE_3D_CNTL		0x1a00
#घोषणा R128_SEC_TEX_CNTL_C		0x1d00
#घोषणा R128_SEC_TEXTURE_BORDER_COLOR_C	0x1d3c
#घोषणा R128_SETUP_CNTL			0x1bc4
#घोषणा R128_STEN_REF_MASK_C		0x1d40

#घोषणा R128_TEX_CNTL_C			0x1c9c
#	define R128_TEX_CACHE_FLUSH		(1 << 23)

#घोषणा R128_WAIT_UNTIL			0x1720
#	define R128_EVENT_CRTC_OFFSET		(1 << 0)
#घोषणा R128_WINDOW_XY_OFFSET		0x1bcc

/* CCE रेजिस्टरs
 */
#घोषणा R128_PM4_BUFFER_OFFSET		0x0700
#घोषणा R128_PM4_BUFFER_CNTL		0x0704
#	define R128_PM4_MASK			(15 << 28)
#	define R128_PM4_NONPM4			(0  << 28)
#	define R128_PM4_192PIO			(1  << 28)
#	define R128_PM4_192BM			(2  << 28)
#	define R128_PM4_128PIO_64INDBM		(3  << 28)
#	define R128_PM4_128BM_64INDBM		(4  << 28)
#	define R128_PM4_64PIO_128INDBM		(5  << 28)
#	define R128_PM4_64BM_128INDBM		(6  << 28)
#	define R128_PM4_64PIO_64VCBM_64INDBM	(7  << 28)
#	define R128_PM4_64BM_64VCBM_64INDBM	(8  << 28)
#	define R128_PM4_64PIO_64VCPIO_64INDPIO	(15 << 28)
#	define R128_PM4_BUFFER_CNTL_NOUPDATE	(1  << 27)

#घोषणा R128_PM4_BUFFER_WM_CNTL		0x0708
#	define R128_WMA_SHIFT			0
#	define R128_WMB_SHIFT			8
#	define R128_WMC_SHIFT			16
#	define R128_WB_WM_SHIFT			24

#घोषणा R128_PM4_BUFFER_DL_RPTR_ADDR	0x070c
#घोषणा R128_PM4_BUFFER_DL_RPTR		0x0710
#घोषणा R128_PM4_BUFFER_DL_WPTR		0x0714
#	define R128_PM4_BUFFER_DL_DONE		(1 << 31)

#घोषणा R128_PM4_VC_FPU_SETUP		0x071c

#घोषणा R128_PM4_IW_INDOFF		0x0738
#घोषणा R128_PM4_IW_INDSIZE		0x073c

#घोषणा R128_PM4_STAT			0x07b8
#	define R128_PM4_FIFOCNT_MASK		0x0fff
#	define R128_PM4_BUSY			(1 << 16)
#	define R128_PM4_GUI_ACTIVE		(1 << 31)

#घोषणा R128_PM4_MICROCODE_ADDR		0x07d4
#घोषणा R128_PM4_MICROCODE_RADDR	0x07d8
#घोषणा R128_PM4_MICROCODE_DATAH	0x07dc
#घोषणा R128_PM4_MICROCODE_DATAL	0x07e0

#घोषणा R128_PM4_BUFFER_ADDR		0x07f0
#घोषणा R128_PM4_MICRO_CNTL		0x07fc
#	define R128_PM4_MICRO_FREERUN		(1 << 30)

#घोषणा R128_PM4_FIFO_DATA_EVEN		0x1000
#घोषणा R128_PM4_FIFO_DATA_ODD		0x1004

/* CCE command packets
 */
#घोषणा R128_CCE_PACKET0		0x00000000
#घोषणा R128_CCE_PACKET1		0x40000000
#घोषणा R128_CCE_PACKET2		0x80000000
#घोषणा R128_CCE_PACKET3		0xC0000000
#	define R128_CNTL_HOSTDATA_BLT		0x00009400
#	define R128_CNTL_PAINT_MULTI		0x00009A00
#	define R128_CNTL_BITBLT_MULTI		0x00009B00
#	define R128_3D_RNDR_GEN_INDX_PRIM	0x00002300

#घोषणा R128_CCE_PACKET_MASK		0xC0000000
#घोषणा R128_CCE_PACKET_COUNT_MASK	0x3fff0000
#घोषणा R128_CCE_PACKET0_REG_MASK	0x000007ff
#घोषणा R128_CCE_PACKET1_REG0_MASK	0x000007ff
#घोषणा R128_CCE_PACKET1_REG1_MASK	0x003ff800

#घोषणा R128_CCE_VC_CNTL_PRIM_TYPE_NONE		0x00000000
#घोषणा R128_CCE_VC_CNTL_PRIM_TYPE_POINT	0x00000001
#घोषणा R128_CCE_VC_CNTL_PRIM_TYPE_LINE		0x00000002
#घोषणा R128_CCE_VC_CNTL_PRIM_TYPE_POLY_LINE	0x00000003
#घोषणा R128_CCE_VC_CNTL_PRIM_TYPE_TRI_LIST	0x00000004
#घोषणा R128_CCE_VC_CNTL_PRIM_TYPE_TRI_FAN	0x00000005
#घोषणा R128_CCE_VC_CNTL_PRIM_TYPE_TRI_STRIP	0x00000006
#घोषणा R128_CCE_VC_CNTL_PRIM_TYPE_TRI_TYPE2	0x00000007
#घोषणा R128_CCE_VC_CNTL_PRIM_WALK_IND		0x00000010
#घोषणा R128_CCE_VC_CNTL_PRIM_WALK_LIST		0x00000020
#घोषणा R128_CCE_VC_CNTL_PRIM_WALK_RING		0x00000030
#घोषणा R128_CCE_VC_CNTL_NUM_SHIFT		16

#घोषणा R128_DATATYPE_VQ		0
#घोषणा R128_DATATYPE_CI4		1
#घोषणा R128_DATATYPE_CI8		2
#घोषणा R128_DATATYPE_ARGB1555		3
#घोषणा R128_DATATYPE_RGB565		4
#घोषणा R128_DATATYPE_RGB888		5
#घोषणा R128_DATATYPE_ARGB8888		6
#घोषणा R128_DATATYPE_RGB332		7
#घोषणा R128_DATATYPE_Y8		8
#घोषणा R128_DATATYPE_RGB8		9
#घोषणा R128_DATATYPE_CI16		10
#घोषणा R128_DATATYPE_YVYU422		11
#घोषणा R128_DATATYPE_VYUY422		12
#घोषणा R128_DATATYPE_AYUV444		14
#घोषणा R128_DATATYPE_ARGB4444		15

/* Constants */
#घोषणा R128_AGP_OFFSET			0x02000000

#घोषणा R128_WATERMARK_L		16
#घोषणा R128_WATERMARK_M		8
#घोषणा R128_WATERMARK_N		8
#घोषणा R128_WATERMARK_K		128

#घोषणा R128_MAX_USEC_TIMEOUT		100000	/* 100 ms */

#घोषणा R128_LAST_FRAME_REG		R128_GUI_SCRATCH_REG0
#घोषणा R128_LAST_DISPATCH_REG		R128_GUI_SCRATCH_REG1
#घोषणा R128_MAX_VB_AGE			0x7fffffff
#घोषणा R128_MAX_VB_VERTS		(0xffff)

#घोषणा R128_RING_HIGH_MARK		128

#घोषणा R128_PERFORMANCE_BOXES		0

#घोषणा R128_PCIGART_TABLE_SIZE         32768

#घोषणा R128_READ(reg)		पढ़ोl(((व्योम __iomem *)dev_priv->mmio->handle) + (reg))
#घोषणा R128_WRITE(reg, val)	ग_लिखोl(val, ((व्योम __iomem *)dev_priv->mmio->handle) + (reg))
#घोषणा R128_READ8(reg)		पढ़ोb(((व्योम __iomem *)dev_priv->mmio->handle) + (reg))
#घोषणा R128_WRITE8(reg, val)	ग_लिखोb(val, ((व्योम __iomem *)dev_priv->mmio->handle) + (reg))

#घोषणा R128_WRITE_PLL(addr, val)					\
करो अणु									\
	R128_WRITE8(R128_CLOCK_CNTL_INDEX,				\
		    ((addr) & 0x1f) | R128_PLL_WR_EN);			\
	R128_WRITE(R128_CLOCK_CNTL_DATA, (val));			\
पूर्ण जबतक (0)

#घोषणा CCE_PACKET0(reg, n)		(R128_CCE_PACKET0 |		\
					 ((n) << 16) | ((reg) >> 2))
#घोषणा CCE_PACKET1(reg0, reg1)		(R128_CCE_PACKET1 |		\
					 (((reg1) >> 2) << 11) | ((reg0) >> 2))
#घोषणा CCE_PACKET2()			(R128_CCE_PACKET2)
#घोषणा CCE_PACKET3(pkt, n)		(R128_CCE_PACKET3 |		\
					 (pkt) | ((n) << 16))

अटल __अंतरभूत__ व्योम r128_update_ring_snapshot(drm_r128_निजी_t *dev_priv)
अणु
	drm_r128_ring_buffer_t *ring = &dev_priv->ring;
	ring->space = (GET_RING_HEAD(dev_priv) - ring->tail) * माप(u32);
	अगर (ring->space <= 0)
		ring->space += ring->size;
पूर्ण

/* ================================================================
 * Misc helper macros
 */

#घोषणा DEV_INIT_TEST_WITH_RETURN(_dev_priv)				\
करो अणु									\
	अगर (!_dev_priv) अणु						\
		DRM_ERROR("called with no initialization\n");		\
		वापस -EINVAL;						\
	पूर्ण								\
पूर्ण जबतक (0)

#घोषणा RING_SPACE_TEST_WITH_RETURN(dev_priv)				\
करो अणु									\
	drm_r128_ring_buffer_t *ring = &dev_priv->ring; पूर्णांक i;		\
	अगर (ring->space < ring->high_mark) अणु				\
		क्रम (i = 0 ; i < dev_priv->usec_समयout ; i++) अणु	\
			r128_update_ring_snapshot(dev_priv);		\
			अगर (ring->space >= ring->high_mark)		\
				जाओ __ring_space_करोne;			\
			udelay(1);					\
		पूर्ण							\
		DRM_ERROR("ring space check failed!\n");		\
		वापस -EBUSY;						\
	पूर्ण								\
 __ring_space_करोne:							\
	;								\
पूर्ण जबतक (0)

#घोषणा VB_AGE_TEST_WITH_RETURN(dev_priv)				\
करो अणु									\
	drm_r128_sarea_t *sarea_priv = dev_priv->sarea_priv;		\
	अगर (sarea_priv->last_dispatch >= R128_MAX_VB_AGE) अणु		\
		पूर्णांक __ret = r128_करो_cce_idle(dev_priv);			\
		अगर (__ret)						\
			वापस __ret;					\
		sarea_priv->last_dispatch = 0;				\
		r128_मुक्तlist_reset(dev);				\
	पूर्ण								\
पूर्ण जबतक (0)

#घोषणा R128_WAIT_UNTIL_PAGE_FLIPPED() करो अणु				\
	OUT_RING(CCE_PACKET0(R128_WAIT_UNTIL, 0));			\
	OUT_RING(R128_EVENT_CRTC_OFFSET);				\
पूर्ण जबतक (0)

/* ================================================================
 * Ring control
 */

#घोषणा R128_VERBOSE	0

#घोषणा RING_LOCALS							\
	पूर्णांक ग_लिखो, _nr; अचिन्हित पूर्णांक tail_mask; अस्थिर u32 *ring;

#घोषणा BEGIN_RING(n) करो अणु						\
	अगर (R128_VERBOSE)						\
		DRM_INFO("BEGIN_RING(%d)\n", (n));			\
	अगर (dev_priv->ring.space <= (n) * माप(u32)) अणु		\
		COMMIT_RING();						\
		r128_रुको_ring(dev_priv, (n) * माप(u32));		\
	पूर्ण								\
	_nr = n; dev_priv->ring.space -= (n) * माप(u32);		\
	ring = dev_priv->ring.start;					\
	ग_लिखो = dev_priv->ring.tail;					\
	tail_mask = dev_priv->ring.tail_mask;				\
पूर्ण जबतक (0)

/* You can set this to zero अगर you want.  If the card locks up, you'll
 * need to keep this set.  It works around a bug in early revs of the
 * Rage 128 chipset, where the CCE would पढ़ो 32 dwords past the end of
 * the ring buffer beक्रमe wrapping around.
 */
#घोषणा R128_BROKEN_CCE	1

#घोषणा ADVANCE_RING() करो अणु						\
	अगर (R128_VERBOSE)						\
		DRM_INFO("ADVANCE_RING() wr=0x%06x tail=0x%06x\n",	\
			 ग_लिखो, dev_priv->ring.tail);			\
	अगर (R128_BROKEN_CCE && ग_लिखो < 32)				\
		स_नकल(dev_priv->ring.end,				\
		       dev_priv->ring.start,				\
		       ग_लिखो * माप(u32));				\
	अगर (((dev_priv->ring.tail + _nr) & tail_mask) != ग_लिखो)		\
		DRM_ERROR(						\
			"ADVANCE_RING(): mismatch: nr: %x write: %x line: %d\n",	\
			((dev_priv->ring.tail + _nr) & tail_mask),	\
			ग_लिखो, __LINE__);				\
	अन्यथा								\
		dev_priv->ring.tail = ग_लिखो;				\
पूर्ण जबतक (0)

#घोषणा COMMIT_RING() करो अणु						\
	अगर (R128_VERBOSE)						\
		DRM_INFO("COMMIT_RING() tail=0x%06x\n",			\
			 dev_priv->ring.tail);				\
	mb();						\
	R128_WRITE(R128_PM4_BUFFER_DL_WPTR, dev_priv->ring.tail);	\
	R128_READ(R128_PM4_BUFFER_DL_WPTR);				\
पूर्ण जबतक (0)

#घोषणा OUT_RING(x) करो अणु						\
	अगर (R128_VERBOSE)						\
		DRM_INFO("   OUT_RING( 0x%08x ) at 0x%x\n",		\
			 (अचिन्हित पूर्णांक)(x), ग_लिखो);			\
	ring[ग_लिखो++] = cpu_to_le32(x);					\
	ग_लिखो &= tail_mask;						\
पूर्ण जबतक (0)

#पूर्ण_अगर				/* __R128_DRV_H__ */
