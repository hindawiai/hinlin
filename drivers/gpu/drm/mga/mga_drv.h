<शैली गुरु>
/* mga_drv.h -- Private header क्रम the Matrox G200/G400 driver -*- linux-c -*-
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
 * VA LINUX SYSTEMS AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Authors:
 *    Gareth Hughes <gareth@valinux.com>
 */

#अगर_अघोषित __MGA_DRV_H__
#घोषणा __MGA_DRV_H__

#समावेश <linux/irqवापस.h>
#समावेश <linux/pci.h>
#समावेश <linux/slab.h>

#समावेश <drm/drm_agpsupport.h>
#समावेश <drm/drm_device.h>
#समावेश <drm/drm_file.h>
#समावेश <drm/drm_ioctl.h>
#समावेश <drm/drm_irq.h>
#समावेश <drm/drm_legacy.h>
#समावेश <drm/drm_prपूर्णांक.h>
#समावेश <drm/drm_sarea.h>
#समावेश <drm/drm_vblank.h>
#समावेश <drm/mga_drm.h>

/* General customization:
 */

#घोषणा DRIVER_AUTHOR		"Gareth Hughes, VA Linux Systems Inc."

#घोषणा DRIVER_NAME		"mga"
#घोषणा DRIVER_DESC		"Matrox G200/G400"
#घोषणा DRIVER_DATE		"20051102"

#घोषणा DRIVER_MAJOR		3
#घोषणा DRIVER_MINOR		2
#घोषणा DRIVER_PATCHLEVEL	1

प्रकार काष्ठा drm_mga_primary_buffer अणु
	u8 *start;
	u8 *end;
	पूर्णांक size;

	u32 tail;
	पूर्णांक space;
	अस्थिर दीर्घ wrapped;

	अस्थिर u32 *status;

	u32 last_flush;
	u32 last_wrap;

	u32 high_mark;
पूर्ण drm_mga_primary_buffer_t;

प्रकार काष्ठा drm_mga_मुक्तlist अणु
	काष्ठा drm_mga_मुक्तlist *next;
	काष्ठा drm_mga_मुक्तlist *prev;
	drm_mga_age_t age;
	काष्ठा drm_buf *buf;
पूर्ण drm_mga_मुक्तlist_t;

प्रकार काष्ठा अणु
	drm_mga_मुक्तlist_t *list_entry;
	पूर्णांक discard;
	पूर्णांक dispatched;
पूर्ण drm_mga_buf_priv_t;

प्रकार काष्ठा drm_mga_निजी अणु
	drm_mga_primary_buffer_t prim;
	drm_mga_sarea_t *sarea_priv;

	drm_mga_मुक्तlist_t *head;
	drm_mga_मुक्तlist_t *tail;

	अचिन्हित पूर्णांक warp_pipe;
	अचिन्हित दीर्घ warp_pipe_phys[MGA_MAX_WARP_PIPES];

	पूर्णांक chipset;
	पूर्णांक usec_समयout;

	/**
	 * If set, the new DMA initialization sequence was used.  This is
	 * primarilly used to select how the driver should uninitialized its
	 * पूर्णांकernal DMA काष्ठाures.
	 */
	पूर्णांक used_new_dma_init;

	/**
	 * If AGP memory is used क्रम DMA buffers, this will be the value
	 * \c MGA_PAGPXFER.  Otherwise, it will be zero (क्रम a PCI transfer).
	 */
	u32 dma_access;

	/**
	 * If AGP memory is used क्रम DMA buffers, this will be the value
	 * \c MGA_WAGP_ENABLE.  Otherwise, it will be zero (क्रम a PCI
	 * transfer).
	 */
	u32 wagp_enable;

	/**
	 * \नame MMIO region parameters.
	 *
	 * \sa drm_mga_निजी_t::mmio
	 */
	/*@अणु */
	resource_माप_प्रकार mmio_base;	   /**< Bus address of base of MMIO. */
	resource_माप_प्रकार mmio_size;	   /**< Size of the MMIO region. */
	/*@पूर्ण */

	u32 clear_cmd;
	u32 maccess;

	atomic_t vbl_received;          /**< Number of vblanks received. */
	रुको_queue_head_t fence_queue;
	atomic_t last_fence_retired;
	u32 next_fence_to_post;

	अचिन्हित पूर्णांक fb_cpp;
	अचिन्हित पूर्णांक front_offset;
	अचिन्हित पूर्णांक front_pitch;
	अचिन्हित पूर्णांक back_offset;
	अचिन्हित पूर्णांक back_pitch;

	अचिन्हित पूर्णांक depth_cpp;
	अचिन्हित पूर्णांक depth_offset;
	अचिन्हित पूर्णांक depth_pitch;

	अचिन्हित पूर्णांक texture_offset;
	अचिन्हित पूर्णांक texture_size;

	drm_local_map_t *sarea;
	drm_local_map_t *mmio;
	drm_local_map_t *status;
	drm_local_map_t *warp;
	drm_local_map_t *primary;
	drm_local_map_t *agp_textures;

	अचिन्हित दीर्घ agp_handle;
	अचिन्हित पूर्णांक agp_size;
पूर्ण drm_mga_निजी_t;

बाह्य स्थिर काष्ठा drm_ioctl_desc mga_ioctls[];
बाह्य पूर्णांक mga_max_ioctl;

				/* mga_dma.c */
बाह्य पूर्णांक mga_dma_bootstrap(काष्ठा drm_device *dev, व्योम *data,
			     काष्ठा drm_file *file_priv);
बाह्य पूर्णांक mga_dma_init(काष्ठा drm_device *dev, व्योम *data,
			काष्ठा drm_file *file_priv);
बाह्य पूर्णांक mga_getparam(काष्ठा drm_device *dev, व्योम *data,
			काष्ठा drm_file *file_priv);
बाह्य पूर्णांक mga_dma_flush(काष्ठा drm_device *dev, व्योम *data,
			 काष्ठा drm_file *file_priv);
बाह्य पूर्णांक mga_dma_reset(काष्ठा drm_device *dev, व्योम *data,
			 काष्ठा drm_file *file_priv);
बाह्य पूर्णांक mga_dma_buffers(काष्ठा drm_device *dev, व्योम *data,
			   काष्ठा drm_file *file_priv);
बाह्य पूर्णांक mga_driver_load(काष्ठा drm_device *dev, अचिन्हित दीर्घ flags);
बाह्य व्योम mga_driver_unload(काष्ठा drm_device *dev);
बाह्य व्योम mga_driver_lastबंद(काष्ठा drm_device *dev);
बाह्य पूर्णांक mga_driver_dma_quiescent(काष्ठा drm_device *dev);

बाह्य पूर्णांक mga_करो_रुको_क्रम_idle(drm_mga_निजी_t *dev_priv);

बाह्य व्योम mga_करो_dma_flush(drm_mga_निजी_t *dev_priv);
बाह्य व्योम mga_करो_dma_wrap_start(drm_mga_निजी_t *dev_priv);
बाह्य व्योम mga_करो_dma_wrap_end(drm_mga_निजी_t *dev_priv);

बाह्य पूर्णांक mga_मुक्तlist_put(काष्ठा drm_device *dev, काष्ठा drm_buf *buf);

				/* mga_warp.c */
बाह्य पूर्णांक mga_warp_install_microcode(drm_mga_निजी_t *dev_priv);
बाह्य पूर्णांक mga_warp_init(drm_mga_निजी_t *dev_priv);

				/* mga_irq.c */
बाह्य पूर्णांक mga_enable_vblank(काष्ठा drm_device *dev, अचिन्हित पूर्णांक pipe);
बाह्य व्योम mga_disable_vblank(काष्ठा drm_device *dev, अचिन्हित पूर्णांक pipe);
बाह्य u32 mga_get_vblank_counter(काष्ठा drm_device *dev, अचिन्हित पूर्णांक pipe);
बाह्य व्योम mga_driver_fence_रुको(काष्ठा drm_device *dev, अचिन्हित पूर्णांक *sequence);
बाह्य पूर्णांक mga_driver_vblank_रुको(काष्ठा drm_device *dev, अचिन्हित पूर्णांक *sequence);
बाह्य irqवापस_t mga_driver_irq_handler(पूर्णांक irq, व्योम *arg);
बाह्य व्योम mga_driver_irq_preinstall(काष्ठा drm_device *dev);
बाह्य पूर्णांक mga_driver_irq_postinstall(काष्ठा drm_device *dev);
बाह्य व्योम mga_driver_irq_uninstall(काष्ठा drm_device *dev);
बाह्य दीर्घ mga_compat_ioctl(काष्ठा file *filp, अचिन्हित पूर्णांक cmd,
			     अचिन्हित दीर्घ arg);

#घोषणा mga_flush_ग_लिखो_combine()	wmb()

#घोषणा MGA_READ8(reg) \
	पढ़ोb(((व्योम __iomem *)dev_priv->mmio->handle) + (reg))
#घोषणा MGA_READ(reg) \
	पढ़ोl(((व्योम __iomem *)dev_priv->mmio->handle) + (reg))
#घोषणा MGA_WRITE8(reg, val) \
	ग_लिखोb(val, ((व्योम __iomem *)dev_priv->mmio->handle) + (reg))
#घोषणा MGA_WRITE(reg, val) \
	ग_लिखोl(val, ((व्योम __iomem *)dev_priv->mmio->handle) + (reg))

#घोषणा DWGREG0		0x1c00
#घोषणा DWGREG0_END	0x1dff
#घोषणा DWGREG1		0x2c00
#घोषणा DWGREG1_END	0x2dff

#घोषणा ISREG0(r)	(r >= DWGREG0 && r <= DWGREG0_END)
#घोषणा DMAREG0(r)	(u8)((r - DWGREG0) >> 2)
#घोषणा DMAREG1(r)	(u8)(((r - DWGREG1) >> 2) | 0x80)
#घोषणा DMAREG(r)	(ISREG0(r) ? DMAREG0(r) : DMAREG1(r))

/* ================================================================
 * Helper macross...
 */

#घोषणा MGA_EMIT_STATE(dev_priv, dirty)					\
करो अणु									\
	अगर ((dirty) & ~MGA_UPLOAD_CLIPRECTS) अणु				\
		अगर (dev_priv->chipset >= MGA_CARD_TYPE_G400)		\
			mga_g400_emit_state(dev_priv);			\
		अन्यथा							\
			mga_g200_emit_state(dev_priv);			\
	पूर्ण								\
पूर्ण जबतक (0)

#घोषणा WRAP_TEST_WITH_RETURN(dev_priv)					\
करो अणु									\
	अगर (test_bit(0, &dev_priv->prim.wrapped)) अणु			\
		अगर (mga_is_idle(dev_priv)) अणु				\
			mga_करो_dma_wrap_end(dev_priv);			\
		पूर्ण अन्यथा अगर (dev_priv->prim.space <			\
			   dev_priv->prim.high_mark) अणु			\
			अगर (MGA_DMA_DEBUG)				\
				DRM_INFO("wrap...\n");			\
			वापस -EBUSY;					\
		पूर्ण							\
	पूर्ण								\
पूर्ण जबतक (0)

#घोषणा WRAP_WAIT_WITH_RETURN(dev_priv)					\
करो अणु									\
	अगर (test_bit(0, &dev_priv->prim.wrapped)) अणु			\
		अगर (mga_करो_रुको_क्रम_idle(dev_priv) < 0) अणु		\
			अगर (MGA_DMA_DEBUG)				\
				DRM_INFO("wrap...\n");			\
			वापस -EBUSY;					\
		पूर्ण							\
		mga_करो_dma_wrap_end(dev_priv);				\
	पूर्ण								\
पूर्ण जबतक (0)

/* ================================================================
 * Primary DMA command stream
 */

#घोषणा MGA_VERBOSE	0

#घोषणा DMA_LOCALS	अचिन्हित पूर्णांक ग_लिखो; अस्थिर u8 *prim;

#घोषणा DMA_BLOCK_SIZE	(5 * माप(u32))

#घोषणा BEGIN_DMA(n)							\
करो अणु									\
	अगर (MGA_VERBOSE) अणु						\
		DRM_INFO("BEGIN_DMA(%d)\n", (n));			\
		DRM_INFO("   space=0x%x req=0x%zx\n",			\
			 dev_priv->prim.space, (n) * DMA_BLOCK_SIZE);	\
	पूर्ण								\
	prim = dev_priv->prim.start;					\
	ग_लिखो = dev_priv->prim.tail;					\
पूर्ण जबतक (0)

#घोषणा BEGIN_DMA_WRAP()						\
करो अणु									\
	अगर (MGA_VERBOSE) अणु						\
		DRM_INFO("BEGIN_DMA()\n");				\
		DRM_INFO("   space=0x%x\n", dev_priv->prim.space);	\
	पूर्ण								\
	prim = dev_priv->prim.start;					\
	ग_लिखो = dev_priv->prim.tail;					\
पूर्ण जबतक (0)

#घोषणा ADVANCE_DMA()							\
करो अणु									\
	dev_priv->prim.tail = ग_लिखो;					\
	अगर (MGA_VERBOSE)						\
		DRM_INFO("ADVANCE_DMA() tail=0x%05x sp=0x%x\n",		\
			 ग_लिखो, dev_priv->prim.space);			\
पूर्ण जबतक (0)

#घोषणा FLUSH_DMA()							\
करो अणु									\
	अगर (0) अणु							\
		DRM_INFO("\n");						\
		DRM_INFO("   tail=0x%06x head=0x%06lx\n",		\
			 dev_priv->prim.tail,				\
			 (अचिन्हित दीर्घ)(MGA_READ(MGA_PRIMADDRESS) -	\
					 dev_priv->primary->offset));	\
	पूर्ण								\
	अगर (!test_bit(0, &dev_priv->prim.wrapped)) अणु			\
		अगर (dev_priv->prim.space < dev_priv->prim.high_mark)	\
			mga_करो_dma_wrap_start(dev_priv);		\
		अन्यथा							\
			mga_करो_dma_flush(dev_priv);			\
	पूर्ण								\
पूर्ण जबतक (0)

/* Never use this, always use DMA_BLOCK(...) क्रम primary DMA output.
 */
#घोषणा DMA_WRITE(offset, val)						\
करो अणु									\
	अगर (MGA_VERBOSE)						\
		DRM_INFO("   DMA_WRITE( 0x%08x ) at 0x%04zx\n",		\
			 (u32)(val), ग_लिखो + (offset) * माप(u32));	\
	*(अस्थिर u32 *)(prim + ग_लिखो + (offset) * माप(u32)) = val;	\
पूर्ण जबतक (0)

#घोषणा DMA_BLOCK(reg0, val0, reg1, val1, reg2, val2, reg3, val3)	\
करो अणु									\
	DMA_WRITE(0, ((DMAREG(reg0) << 0) |				\
		      (DMAREG(reg1) << 8) |				\
		      (DMAREG(reg2) << 16) |				\
		      (DMAREG(reg3) << 24)));				\
	DMA_WRITE(1, val0);						\
	DMA_WRITE(2, val1);						\
	DMA_WRITE(3, val2);						\
	DMA_WRITE(4, val3);						\
	ग_लिखो += DMA_BLOCK_SIZE;					\
पूर्ण जबतक (0)

/* Buffer aging via primary DMA stream head poपूर्णांकer.
 */

#घोषणा SET_AGE(age, h, w)						\
करो अणु									\
	(age)->head = h;						\
	(age)->wrap = w;						\
पूर्ण जबतक (0)

#घोषणा TEST_AGE(age, h, w)		((age)->wrap < w ||		\
					 ((age)->wrap == w &&		\
					  (age)->head < h))

#घोषणा AGE_BUFFER(buf_priv)						\
करो अणु									\
	drm_mga_मुक्तlist_t *entry = (buf_priv)->list_entry;		\
	अगर ((buf_priv)->dispatched) अणु					\
		entry->age.head = (dev_priv->prim.tail +		\
				   dev_priv->primary->offset);		\
		entry->age.wrap = dev_priv->sarea_priv->last_wrap;	\
	पूर्ण अन्यथा अणु							\
		entry->age.head = 0;					\
		entry->age.wrap = 0;					\
	पूर्ण								\
पूर्ण जबतक (0)

#घोषणा MGA_ENGINE_IDLE_MASK		(MGA_SOFTRAPEN |		\
					 MGA_DWGENGSTS |		\
					 MGA_ENDPRDMASTS)
#घोषणा MGA_DMA_IDLE_MASK		(MGA_SOFTRAPEN |		\
					 MGA_ENDPRDMASTS)

#घोषणा MGA_DMA_DEBUG			0

/* A reduced set of the mga रेजिस्टरs.
 */
#घोषणा MGA_CRTC_INDEX			0x1fd4
#घोषणा MGA_CRTC_DATA			0x1fd5

/* CRTC11 */
#घोषणा MGA_VINTCLR			(1 << 4)
#घोषणा MGA_VINTEN			(1 << 5)

#घोषणा MGA_ALPHACTRL			0x2c7c
#घोषणा MGA_AR0				0x1c60
#घोषणा MGA_AR1				0x1c64
#घोषणा MGA_AR2				0x1c68
#घोषणा MGA_AR3				0x1c6c
#घोषणा MGA_AR4				0x1c70
#घोषणा MGA_AR5				0x1c74
#घोषणा MGA_AR6				0x1c78

#घोषणा MGA_CXBNDRY			0x1c80
#घोषणा MGA_CXLEFT			0x1ca0
#घोषणा MGA_CXRIGHT			0x1ca4

#घोषणा MGA_DMAPAD			0x1c54
#घोषणा MGA_DSTORG			0x2cb8
#घोषणा MGA_DWGCTL			0x1c00
#	define MGA_OPCOD_MASK			(15 << 0)
#	define MGA_OPCOD_TRAP			(4 << 0)
#	define MGA_OPCOD_TEXTURE_TRAP		(6 << 0)
#	define MGA_OPCOD_BITBLT			(8 << 0)
#	define MGA_OPCOD_ILOAD			(9 << 0)
#	define MGA_ATYPE_MASK			(7 << 4)
#	define MGA_ATYPE_RPL			(0 << 4)
#	define MGA_ATYPE_RSTR			(1 << 4)
#	define MGA_ATYPE_ZI			(3 << 4)
#	define MGA_ATYPE_BLK			(4 << 4)
#	define MGA_ATYPE_I			(7 << 4)
#	define MGA_LINEAR			(1 << 7)
#	define MGA_ZMODE_MASK			(7 << 8)
#	define MGA_ZMODE_NOZCMP			(0 << 8)
#	define MGA_ZMODE_ZE			(2 << 8)
#	define MGA_ZMODE_ZNE			(3 << 8)
#	define MGA_ZMODE_ZLT			(4 << 8)
#	define MGA_ZMODE_ZLTE			(5 << 8)
#	define MGA_ZMODE_ZGT			(6 << 8)
#	define MGA_ZMODE_ZGTE			(7 << 8)
#	define MGA_SOLID			(1 << 11)
#	define MGA_ARZERO			(1 << 12)
#	define MGA_SGNZERO			(1 << 13)
#	define MGA_SHIFTZERO			(1 << 14)
#	define MGA_BOP_MASK			(15 << 16)
#	define MGA_BOP_ZERO			(0 << 16)
#	define MGA_BOP_DST			(10 << 16)
#	define MGA_BOP_SRC			(12 << 16)
#	define MGA_BOP_ONE			(15 << 16)
#	define MGA_TRANS_SHIFT			20
#	define MGA_TRANS_MASK			(15 << 20)
#	define MGA_BLTMOD_MASK			(15 << 25)
#	define MGA_BLTMOD_BMONOLEF		(0 << 25)
#	define MGA_BLTMOD_BMONOWF		(4 << 25)
#	define MGA_BLTMOD_PLAN			(1 << 25)
#	define MGA_BLTMOD_BFCOL			(2 << 25)
#	define MGA_BLTMOD_BU32BGR		(3 << 25)
#	define MGA_BLTMOD_BU32RGB		(7 << 25)
#	define MGA_BLTMOD_BU24BGR		(11 << 25)
#	define MGA_BLTMOD_BU24RGB		(15 << 25)
#	define MGA_PATTERN			(1 << 29)
#	define MGA_TRANSC			(1 << 30)
#	define MGA_CLIPDIS			(1 << 31)
#घोषणा MGA_DWGSYNC			0x2c4c

#घोषणा MGA_FCOL			0x1c24
#घोषणा MGA_FIFOSTATUS			0x1e10
#घोषणा MGA_FOGCOL			0x1cf4
#घोषणा MGA_FXBNDRY			0x1c84
#घोषणा MGA_FXLEFT			0x1ca8
#घोषणा MGA_FXRIGHT			0x1cac

#घोषणा MGA_ICLEAR			0x1e18
#	define MGA_SOFTRAPICLR			(1 << 0)
#	define MGA_VLINEICLR			(1 << 5)
#घोषणा MGA_IEN				0x1e1c
#	define MGA_SOFTRAPIEN			(1 << 0)
#	define MGA_VLINEIEN			(1 << 5)

#घोषणा MGA_LEN				0x1c5c

#घोषणा MGA_MACCESS			0x1c04

#घोषणा MGA_PITCH			0x1c8c
#घोषणा MGA_PLNWT			0x1c1c
#घोषणा MGA_PRIMADDRESS			0x1e58
#	define MGA_DMA_GENERAL			(0 << 0)
#	define MGA_DMA_BLIT			(1 << 0)
#	define MGA_DMA_VECTOR			(2 << 0)
#	define MGA_DMA_VERTEX			(3 << 0)
#घोषणा MGA_PRIMEND			0x1e5c
#	define MGA_PRIMNOSTART			(1 << 0)
#	define MGA_PAGPXFER			(1 << 1)
#घोषणा MGA_PRIMPTR			0x1e50
#	define MGA_PRIMPTREN0			(1 << 0)
#	define MGA_PRIMPTREN1			(1 << 1)

#घोषणा MGA_RST				0x1e40
#	define MGA_SOFTRESET			(1 << 0)
#	define MGA_SOFTEXTRST			(1 << 1)

#घोषणा MGA_SECADDRESS			0x2c40
#घोषणा MGA_SECEND			0x2c44
#घोषणा MGA_SETUPADDRESS		0x2cd0
#घोषणा MGA_SETUPEND			0x2cd4
#घोषणा MGA_SGN				0x1c58
#घोषणा MGA_SOFTRAP			0x2c48
#घोषणा MGA_SRCORG			0x2cb4
#	define MGA_SRMMAP_MASK			(1 << 0)
#	define MGA_SRCMAP_FB			(0 << 0)
#	define MGA_SRCMAP_SYSMEM		(1 << 0)
#	define MGA_SRCACC_MASK			(1 << 1)
#	define MGA_SRCACC_PCI			(0 << 1)
#	define MGA_SRCACC_AGP			(1 << 1)
#घोषणा MGA_STATUS			0x1e14
#	define MGA_SOFTRAPEN			(1 << 0)
#	define MGA_VSYNCPEN			(1 << 4)
#	define MGA_VLINEPEN			(1 << 5)
#	define MGA_DWGENGSTS			(1 << 16)
#	define MGA_ENDPRDMASTS			(1 << 17)
#घोषणा MGA_STENCIL			0x2cc8
#घोषणा MGA_STENCILCTL			0x2ccc

#घोषणा MGA_TDUALSTAGE0			0x2cf8
#घोषणा MGA_TDUALSTAGE1			0x2cfc
#घोषणा MGA_TEXBORDERCOL		0x2c5c
#घोषणा MGA_TEXCTL			0x2c30
#घोषणा MGA_TEXCTL2			0x2c3c
#	define MGA_DUALTEX			(1 << 7)
#	define MGA_G400_TC2_MAGIC		(1 << 15)
#	define MGA_MAP1_ENABLE			(1 << 31)
#घोषणा MGA_TEXFILTER			0x2c58
#घोषणा MGA_TEXHEIGHT			0x2c2c
#घोषणा MGA_TEXORG			0x2c24
#	define MGA_TEXORGMAP_MASK		(1 << 0)
#	define MGA_TEXORGMAP_FB			(0 << 0)
#	define MGA_TEXORGMAP_SYSMEM		(1 << 0)
#	define MGA_TEXORGACC_MASK		(1 << 1)
#	define MGA_TEXORGACC_PCI		(0 << 1)
#	define MGA_TEXORGACC_AGP		(1 << 1)
#घोषणा MGA_TEXORG1			0x2ca4
#घोषणा MGA_TEXORG2			0x2ca8
#घोषणा MGA_TEXORG3			0x2cac
#घोषणा MGA_TEXORG4			0x2cb0
#घोषणा MGA_TEXTRANS			0x2c34
#घोषणा MGA_TEXTRANSHIGH		0x2c38
#घोषणा MGA_TEXWIDTH			0x2c28

#घोषणा MGA_WACCEPTSEQ			0x1dd4
#घोषणा MGA_WCODEADDR			0x1e6c
#घोषणा MGA_WFLAG			0x1dc4
#घोषणा MGA_WFLAG1			0x1de0
#घोषणा MGA_WFLAGNB			0x1e64
#घोषणा MGA_WFLAGNB1			0x1e08
#घोषणा MGA_WGETMSB			0x1dc8
#घोषणा MGA_WIADDR			0x1dc0
#घोषणा MGA_WIADDR2			0x1dd8
#	define MGA_WMODE_SUSPEND		(0 << 0)
#	define MGA_WMODE_RESUME			(1 << 0)
#	define MGA_WMODE_JUMP			(2 << 0)
#	define MGA_WMODE_START			(3 << 0)
#	define MGA_WAGP_ENABLE			(1 << 2)
#घोषणा MGA_WMISC			0x1e70
#	define MGA_WUCODECACHE_ENABLE		(1 << 0)
#	define MGA_WMASTER_ENABLE		(1 << 1)
#	define MGA_WCACHEFLUSH_ENABLE		(1 << 3)
#घोषणा MGA_WVRTXSZ			0x1dcc

#घोषणा MGA_YBOT			0x1c9c
#घोषणा MGA_YDST			0x1c90
#घोषणा MGA_YDSTLEN			0x1c88
#घोषणा MGA_YDSTORG			0x1c94
#घोषणा MGA_YTOP			0x1c98

#घोषणा MGA_ZORG			0x1c0c

/* This finishes the current batch of commands
 */
#घोषणा MGA_EXEC			0x0100

/* AGP PLL encoding (क्रम G200 only).
 */
#घोषणा MGA_AGP_PLL			0x1e4c
#	define MGA_AGP2XPLL_DISABLE		(0 << 0)
#	define MGA_AGP2XPLL_ENABLE		(1 << 0)

/* Warp रेजिस्टरs
 */
#घोषणा MGA_WR0				0x2d00
#घोषणा MGA_WR1				0x2d04
#घोषणा MGA_WR2				0x2d08
#घोषणा MGA_WR3				0x2d0c
#घोषणा MGA_WR4				0x2d10
#घोषणा MGA_WR5				0x2d14
#घोषणा MGA_WR6				0x2d18
#घोषणा MGA_WR7				0x2d1c
#घोषणा MGA_WR8				0x2d20
#घोषणा MGA_WR9				0x2d24
#घोषणा MGA_WR10			0x2d28
#घोषणा MGA_WR11			0x2d2c
#घोषणा MGA_WR12			0x2d30
#घोषणा MGA_WR13			0x2d34
#घोषणा MGA_WR14			0x2d38
#घोषणा MGA_WR15			0x2d3c
#घोषणा MGA_WR16			0x2d40
#घोषणा MGA_WR17			0x2d44
#घोषणा MGA_WR18			0x2d48
#घोषणा MGA_WR19			0x2d4c
#घोषणा MGA_WR20			0x2d50
#घोषणा MGA_WR21			0x2d54
#घोषणा MGA_WR22			0x2d58
#घोषणा MGA_WR23			0x2d5c
#घोषणा MGA_WR24			0x2d60
#घोषणा MGA_WR25			0x2d64
#घोषणा MGA_WR26			0x2d68
#घोषणा MGA_WR27			0x2d6c
#घोषणा MGA_WR28			0x2d70
#घोषणा MGA_WR29			0x2d74
#घोषणा MGA_WR30			0x2d78
#घोषणा MGA_WR31			0x2d7c
#घोषणा MGA_WR32			0x2d80
#घोषणा MGA_WR33			0x2d84
#घोषणा MGA_WR34			0x2d88
#घोषणा MGA_WR35			0x2d8c
#घोषणा MGA_WR36			0x2d90
#घोषणा MGA_WR37			0x2d94
#घोषणा MGA_WR38			0x2d98
#घोषणा MGA_WR39			0x2d9c
#घोषणा MGA_WR40			0x2da0
#घोषणा MGA_WR41			0x2da4
#घोषणा MGA_WR42			0x2da8
#घोषणा MGA_WR43			0x2dac
#घोषणा MGA_WR44			0x2db0
#घोषणा MGA_WR45			0x2db4
#घोषणा MGA_WR46			0x2db8
#घोषणा MGA_WR47			0x2dbc
#घोषणा MGA_WR48			0x2dc0
#घोषणा MGA_WR49			0x2dc4
#घोषणा MGA_WR50			0x2dc8
#घोषणा MGA_WR51			0x2dcc
#घोषणा MGA_WR52			0x2dd0
#घोषणा MGA_WR53			0x2dd4
#घोषणा MGA_WR54			0x2dd8
#घोषणा MGA_WR55			0x2ddc
#घोषणा MGA_WR56			0x2de0
#घोषणा MGA_WR57			0x2de4
#घोषणा MGA_WR58			0x2de8
#घोषणा MGA_WR59			0x2dec
#घोषणा MGA_WR60			0x2df0
#घोषणा MGA_WR61			0x2df4
#घोषणा MGA_WR62			0x2df8
#घोषणा MGA_WR63			0x2dfc
#	define MGA_G400_WR_MAGIC		(1 << 6)
#	define MGA_G400_WR56_MAGIC		0x46480000	/* 12800.0f */

#घोषणा MGA_ILOAD_ALIGN		64
#घोषणा MGA_ILOAD_MASK		(MGA_ILOAD_ALIGN - 1)

#घोषणा MGA_DWGCTL_FLUSH	(MGA_OPCOD_TEXTURE_TRAP |		\
				 MGA_ATYPE_I |				\
				 MGA_ZMODE_NOZCMP |			\
				 MGA_ARZERO |				\
				 MGA_SGNZERO |				\
				 MGA_BOP_SRC |				\
				 (15 << MGA_TRANS_SHIFT))

#घोषणा MGA_DWGCTL_CLEAR	(MGA_OPCOD_TRAP |			\
				 MGA_ZMODE_NOZCMP |			\
				 MGA_SOLID |				\
				 MGA_ARZERO |				\
				 MGA_SGNZERO |				\
				 MGA_SHIFTZERO |			\
				 MGA_BOP_SRC |				\
				 (0 << MGA_TRANS_SHIFT) |		\
				 MGA_BLTMOD_BMONOLEF |			\
				 MGA_TRANSC |				\
				 MGA_CLIPDIS)

#घोषणा MGA_DWGCTL_COPY		(MGA_OPCOD_BITBLT |			\
				 MGA_ATYPE_RPL |			\
				 MGA_SGNZERO |				\
				 MGA_SHIFTZERO |			\
				 MGA_BOP_SRC |				\
				 (0 << MGA_TRANS_SHIFT) |		\
				 MGA_BLTMOD_BFCOL |			\
				 MGA_CLIPDIS)

/* Simple idle test.
 */
अटल __अंतरभूत__ पूर्णांक mga_is_idle(drm_mga_निजी_t *dev_priv)
अणु
	u32 status = MGA_READ(MGA_STATUS) & MGA_ENGINE_IDLE_MASK;
	वापस (status == MGA_ENDPRDMASTS);
पूर्ण

#पूर्ण_अगर
