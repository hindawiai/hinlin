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
#अगर_अघोषित _VIA_DRV_H_
#घोषणा _VIA_DRV_H_

#समावेश <linux/irqवापस.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/रुको.h>

#समावेश <drm/drm_ioctl.h>
#समावेश <drm/drm_legacy.h>
#समावेश <drm/drm_mm.h>
#समावेश <drm/via_drm.h>

#घोषणा DRIVER_AUTHOR	"Various"

#घोषणा DRIVER_NAME		"via"
#घोषणा DRIVER_DESC		"VIA Unichrome / Pro"
#घोषणा DRIVER_DATE		"20070202"

#घोषणा DRIVER_MAJOR		2
#घोषणा DRIVER_MINOR		11
#घोषणा DRIVER_PATCHLEVEL	1

#समावेश "via_verifier.h"

#समावेश "via_dmablit.h"

#घोषणा VIA_PCI_BUF_SIZE 60000
#घोषणा VIA_FIRE_BUF_SIZE  1024
#घोषणा VIA_NUM_IRQS 4

प्रकार काष्ठा drm_via_ring_buffer अणु
	drm_local_map_t map;
	अक्षर *भव_start;
पूर्ण drm_via_ring_buffer_t;

प्रकार uपूर्णांक32_t maskarray_t[5];

प्रकार काष्ठा drm_via_irq अणु
	atomic_t irq_received;
	uपूर्णांक32_t pending_mask;
	uपूर्णांक32_t enable_mask;
	रुको_queue_head_t irq_queue;
पूर्ण drm_via_irq_t;

प्रकार काष्ठा drm_via_निजी अणु
	drm_via_sarea_t *sarea_priv;
	drm_local_map_t *sarea;
	drm_local_map_t *fb;
	drm_local_map_t *mmio;
	अचिन्हित दीर्घ agpAddr;
	रुको_queue_head_t decoder_queue[VIA_NR_XVMC_LOCKS];
	अक्षर *dma_ptr;
	अचिन्हित पूर्णांक dma_low;
	अचिन्हित पूर्णांक dma_high;
	अचिन्हित पूर्णांक dma_offset;
	uपूर्णांक32_t dma_wrap;
	अस्थिर uपूर्णांक32_t *last_छोड़ो_ptr;
	अस्थिर uपूर्णांक32_t *hw_addr_ptr;
	drm_via_ring_buffer_t ring;
	kसमय_प्रकार last_vblank;
	पूर्णांक last_vblank_valid;
	kसमय_प्रकार nsec_per_vblank;
	atomic_t vbl_received;
	drm_via_state_t hc_state;
	अक्षर pci_buf[VIA_PCI_BUF_SIZE];
	स्थिर uपूर्णांक32_t *fire_offsets[VIA_FIRE_BUF_SIZE];
	uपूर्णांक32_t num_fire_offsets;
	पूर्णांक chipset;
	drm_via_irq_t via_irqs[VIA_NUM_IRQS];
	अचिन्हित num_irqs;
	maskarray_t *irq_masks;
	uपूर्णांक32_t irq_enable_mask;
	uपूर्णांक32_t irq_pending_mask;
	पूर्णांक *irq_map;
	अचिन्हित पूर्णांक idle_fault;
	पूर्णांक vram_initialized;
	काष्ठा drm_mm vram_mm;
	पूर्णांक agp_initialized;
	काष्ठा drm_mm agp_mm;
	/** Mapping of userspace keys to mm objects */
	काष्ठा idr object_idr;
	अचिन्हित दीर्घ vram_offset;
	अचिन्हित दीर्घ agp_offset;
	drm_via_blitq_t blit_queues[VIA_NUM_BLIT_ENGINES];
	uपूर्णांक32_t dma_dअगरf;
पूर्ण drm_via_निजी_t;

काष्ठा via_file_निजी अणु
	काष्ठा list_head obj_list;
पूर्ण;

क्रमागत via_family अणु
  VIA_OTHER = 0,     /* Baseline */
  VIA_PRO_GROUP_A,   /* Another video engine and DMA commands */
  VIA_DX9_0          /* Same video as pro_group_a, but 3D is unsupported */
पूर्ण;

/* VIA MMIO रेजिस्टर access */
अटल अंतरभूत u32 via_पढ़ो(काष्ठा drm_via_निजी *dev_priv, u32 reg)
अणु
	वापस पढ़ोl((व्योम __iomem *)(dev_priv->mmio->handle + reg));
पूर्ण

अटल अंतरभूत व्योम via_ग_लिखो(काष्ठा drm_via_निजी *dev_priv, u32 reg,
			     u32 val)
अणु
	ग_लिखोl(val, (व्योम __iomem *)(dev_priv->mmio->handle + reg));
पूर्ण

अटल अंतरभूत व्योम via_ग_लिखो8(काष्ठा drm_via_निजी *dev_priv, u32 reg,
			      u32 val)
अणु
	ग_लिखोb(val, (व्योम __iomem *)(dev_priv->mmio->handle + reg));
पूर्ण

अटल अंतरभूत व्योम via_ग_लिखो8_mask(काष्ठा drm_via_निजी *dev_priv,
				   u32 reg, u32 mask, u32 val)
अणु
	u32 पंचांगp;

	पंचांगp = पढ़ोb((व्योम __iomem *)(dev_priv->mmio->handle + reg));
	पंचांगp = (पंचांगp & ~mask) | (val & mask);
	ग_लिखोb(पंचांगp, (व्योम __iomem *)(dev_priv->mmio->handle + reg));
पूर्ण

/*
 * Poll in a loop रुकोing क्रम 'contidition' to be true.
 * Note: A direct replacement with रुको_event_पूर्णांकerruptible_समयout()
 *       will not work unless driver is updated to emit wake_up()
 *       in relevant places that can impact the 'condition'
 *
 * Returns:
 *   ret keeps current value अगर 'condition' becomes true
 *   ret = -BUSY अगर समयout happens
 *   ret = -EINTR अगर a संकेत पूर्णांकerrupted the रुकोing period
 */
#घोषणा VIA_WAIT_ON( ret, queue, समयout, condition )		\
करो अणु								\
	DECLARE_WAITQUEUE(entry, current);			\
	अचिन्हित दीर्घ end = jअगरfies + (समयout);		\
	add_रुको_queue(&(queue), &entry);			\
								\
	क्रम (;;) अणु						\
		__set_current_state(TASK_INTERRUPTIBLE);	\
		अगर (condition)					\
			अवरोध;					\
		अगर (समय_after_eq(jअगरfies, end)) अणु		\
			ret = -EBUSY;				\
			अवरोध;					\
		पूर्ण						\
		schedule_समयout((HZ/100 > 1) ? HZ/100 : 1);	\
		अगर (संकेत_pending(current)) अणु			\
			ret = -EINTR;				\
			अवरोध;					\
		पूर्ण						\
	पूर्ण							\
	__set_current_state(TASK_RUNNING);			\
	हटाओ_रुको_queue(&(queue), &entry);			\
पूर्ण जबतक (0)

बाह्य स्थिर काष्ठा drm_ioctl_desc via_ioctls[];
बाह्य पूर्णांक via_max_ioctl;

बाह्य पूर्णांक via_fb_init(काष्ठा drm_device *dev, व्योम *data, काष्ठा drm_file *file_priv);
बाह्य पूर्णांक via_mem_alloc(काष्ठा drm_device *dev, व्योम *data, काष्ठा drm_file *file_priv);
बाह्य पूर्णांक via_mem_मुक्त(काष्ठा drm_device *dev, व्योम *data, काष्ठा drm_file *file_priv);
बाह्य पूर्णांक via_agp_init(काष्ठा drm_device *dev, व्योम *data, काष्ठा drm_file *file_priv);
बाह्य पूर्णांक via_map_init(काष्ठा drm_device *dev, व्योम *data, काष्ठा drm_file *file_priv);
बाह्य पूर्णांक via_decoder_futex(काष्ठा drm_device *dev, व्योम *data, काष्ठा drm_file *file_priv);
बाह्य पूर्णांक via_रुको_irq(काष्ठा drm_device *dev, व्योम *data, काष्ठा drm_file *file_priv);
बाह्य पूर्णांक via_dma_blit_sync(काष्ठा drm_device *dev, व्योम *data, काष्ठा drm_file *file_priv);
बाह्य पूर्णांक via_dma_blit(काष्ठा drm_device *dev, व्योम *data, काष्ठा drm_file *file_priv);

बाह्य पूर्णांक via_driver_load(काष्ठा drm_device *dev, अचिन्हित दीर्घ chipset);
बाह्य व्योम via_driver_unload(काष्ठा drm_device *dev);

बाह्य पूर्णांक via_init_context(काष्ठा drm_device *dev, पूर्णांक context);
बाह्य पूर्णांक via_final_context(काष्ठा drm_device *dev, पूर्णांक context);

बाह्य पूर्णांक via_करो_cleanup_map(काष्ठा drm_device *dev);
बाह्य u32 via_get_vblank_counter(काष्ठा drm_device *dev, अचिन्हित पूर्णांक pipe);
बाह्य पूर्णांक via_enable_vblank(काष्ठा drm_device *dev, अचिन्हित पूर्णांक pipe);
बाह्य व्योम via_disable_vblank(काष्ठा drm_device *dev, अचिन्हित पूर्णांक pipe);

बाह्य irqवापस_t via_driver_irq_handler(पूर्णांक irq, व्योम *arg);
बाह्य व्योम via_driver_irq_preinstall(काष्ठा drm_device *dev);
बाह्य पूर्णांक via_driver_irq_postinstall(काष्ठा drm_device *dev);
बाह्य व्योम via_driver_irq_uninstall(काष्ठा drm_device *dev);

बाह्य पूर्णांक via_dma_cleanup(काष्ठा drm_device *dev);
बाह्य व्योम via_init_command_verअगरier(व्योम);
बाह्य पूर्णांक via_driver_dma_quiescent(काष्ठा drm_device *dev);
बाह्य व्योम via_init_futex(drm_via_निजी_t *dev_priv);
बाह्य व्योम via_cleanup_futex(drm_via_निजी_t *dev_priv);
बाह्य व्योम via_release_futex(drm_via_निजी_t *dev_priv, पूर्णांक context);

बाह्य व्योम via_reclaim_buffers_locked(काष्ठा drm_device *dev,
				       काष्ठा drm_file *file_priv);
बाह्य व्योम via_lastबंद(काष्ठा drm_device *dev);

बाह्य व्योम via_dmablit_handler(काष्ठा drm_device *dev, पूर्णांक engine, पूर्णांक from_irq);
बाह्य व्योम via_init_dmablit(काष्ठा drm_device *dev);

#पूर्ण_अगर
