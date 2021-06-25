<शैली गुरु>
/* via_irq.c
 *
 * Copyright 2004 BEAM Ltd.
 * Copyright 2002 Tungsten Graphics, Inc.
 * Copyright 2005 Thomas Hellstrom.
 * All Rights Reserved.
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
 * BEAM LTD, TUNGSTEN GRAPHICS  AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 * Authors:
 *    Terry Barnaby <terry1@beam.ltd.uk>
 *    Keith Whitwell <keith@tungstengraphics.com>
 *    Thomas Hellstrom <unichrome@shipmail.org>
 *
 * This code provides standard DRM access to the Via Unichrome / Pro Vertical blank
 * पूर्णांकerrupt, as well as an infraकाष्ठाure to handle other पूर्णांकerrupts of the chip.
 * The refresh rate is also calculated क्रम video playback sync purposes.
 */

#समावेश <drm/drm_device.h>
#समावेश <drm/drm_vblank.h>
#समावेश <drm/via_drm.h>

#समावेश "via_drv.h"

#घोषणा VIA_REG_INTERRUPT       0x200

/* VIA_REG_INTERRUPT */
#घोषणा VIA_IRQ_GLOBAL	  (1 << 31)
#घोषणा VIA_IRQ_VBLANK_ENABLE   (1 << 19)
#घोषणा VIA_IRQ_VBLANK_PENDING  (1 << 3)
#घोषणा VIA_IRQ_HQV0_ENABLE     (1 << 11)
#घोषणा VIA_IRQ_HQV1_ENABLE     (1 << 25)
#घोषणा VIA_IRQ_HQV0_PENDING    (1 << 9)
#घोषणा VIA_IRQ_HQV1_PENDING    (1 << 10)
#घोषणा VIA_IRQ_DMA0_DD_ENABLE  (1 << 20)
#घोषणा VIA_IRQ_DMA0_TD_ENABLE  (1 << 21)
#घोषणा VIA_IRQ_DMA1_DD_ENABLE  (1 << 22)
#घोषणा VIA_IRQ_DMA1_TD_ENABLE  (1 << 23)
#घोषणा VIA_IRQ_DMA0_DD_PENDING (1 << 4)
#घोषणा VIA_IRQ_DMA0_TD_PENDING (1 << 5)
#घोषणा VIA_IRQ_DMA1_DD_PENDING (1 << 6)
#घोषणा VIA_IRQ_DMA1_TD_PENDING (1 << 7)


/*
 * Device-specअगरic IRQs go here. This type might need to be extended with
 * the रेजिस्टर अगर there are multiple IRQ control रेजिस्टरs.
 * Currently we activate the HQV पूर्णांकerrupts of  Unichrome Pro group A.
 */

अटल maskarray_t via_pro_group_a_irqs[] = अणु
	अणुVIA_IRQ_HQV0_ENABLE, VIA_IRQ_HQV0_PENDING, 0x000003D0, 0x00008010,
	 0x00000000 पूर्ण,
	अणुVIA_IRQ_HQV1_ENABLE, VIA_IRQ_HQV1_PENDING, 0x000013D0, 0x00008010,
	 0x00000000 पूर्ण,
	अणुVIA_IRQ_DMA0_TD_ENABLE, VIA_IRQ_DMA0_TD_PENDING, VIA_PCI_DMA_CSR0,
	 VIA_DMA_CSR_TA | VIA_DMA_CSR_TD, 0x00000008पूर्ण,
	अणुVIA_IRQ_DMA1_TD_ENABLE, VIA_IRQ_DMA1_TD_PENDING, VIA_PCI_DMA_CSR1,
	 VIA_DMA_CSR_TA | VIA_DMA_CSR_TD, 0x00000008पूर्ण,
पूर्ण;
अटल पूर्णांक via_num_pro_group_a = ARRAY_SIZE(via_pro_group_a_irqs);
अटल पूर्णांक via_irqmap_pro_group_a[] = अणु0, 1, -1, 2, -1, 3पूर्ण;

अटल maskarray_t via_unichrome_irqs[] = अणु
	अणुVIA_IRQ_DMA0_TD_ENABLE, VIA_IRQ_DMA0_TD_PENDING, VIA_PCI_DMA_CSR0,
	 VIA_DMA_CSR_TA | VIA_DMA_CSR_TD, 0x00000008पूर्ण,
	अणुVIA_IRQ_DMA1_TD_ENABLE, VIA_IRQ_DMA1_TD_PENDING, VIA_PCI_DMA_CSR1,
	 VIA_DMA_CSR_TA | VIA_DMA_CSR_TD, 0x00000008पूर्ण
पूर्ण;
अटल पूर्णांक via_num_unichrome = ARRAY_SIZE(via_unichrome_irqs);
अटल पूर्णांक via_irqmap_unichrome[] = अणु-1, -1, -1, 0, -1, 1पूर्ण;


u32 via_get_vblank_counter(काष्ठा drm_device *dev, अचिन्हित पूर्णांक pipe)
अणु
	drm_via_निजी_t *dev_priv = dev->dev_निजी;

	अगर (pipe != 0)
		वापस 0;

	वापस atomic_पढ़ो(&dev_priv->vbl_received);
पूर्ण

irqवापस_t via_driver_irq_handler(पूर्णांक irq, व्योम *arg)
अणु
	काष्ठा drm_device *dev = (काष्ठा drm_device *) arg;
	drm_via_निजी_t *dev_priv = (drm_via_निजी_t *) dev->dev_निजी;
	u32 status;
	पूर्णांक handled = 0;
	kसमय_प्रकार cur_vblank;
	drm_via_irq_t *cur_irq = dev_priv->via_irqs;
	पूर्णांक i;

	status = via_पढ़ो(dev_priv, VIA_REG_INTERRUPT);
	अगर (status & VIA_IRQ_VBLANK_PENDING) अणु
		atomic_inc(&dev_priv->vbl_received);
		अगर (!(atomic_पढ़ो(&dev_priv->vbl_received) & 0x0F)) अणु
			cur_vblank = kसमय_get();
			अगर (dev_priv->last_vblank_valid) अणु
				dev_priv->nsec_per_vblank =
					kसमय_sub(cur_vblank,
						dev_priv->last_vblank) >> 4;
			पूर्ण
			dev_priv->last_vblank = cur_vblank;
			dev_priv->last_vblank_valid = 1;
		पूर्ण
		अगर (!(atomic_पढ़ो(&dev_priv->vbl_received) & 0xFF)) अणु
			DRM_DEBUG("nsec per vblank is: %llu\n",
				  kसमय_प्रकारo_ns(dev_priv->nsec_per_vblank));
		पूर्ण
		drm_handle_vblank(dev, 0);
		handled = 1;
	पूर्ण

	क्रम (i = 0; i < dev_priv->num_irqs; ++i) अणु
		अगर (status & cur_irq->pending_mask) अणु
			atomic_inc(&cur_irq->irq_received);
			wake_up(&cur_irq->irq_queue);
			handled = 1;
			अगर (dev_priv->irq_map[drm_via_irq_dma0_td] == i)
				via_dmablit_handler(dev, 0, 1);
			अन्यथा अगर (dev_priv->irq_map[drm_via_irq_dma1_td] == i)
				via_dmablit_handler(dev, 1, 1);
		पूर्ण
		cur_irq++;
	पूर्ण

	/* Acknowledge पूर्णांकerrupts */
	via_ग_लिखो(dev_priv, VIA_REG_INTERRUPT, status);


	अगर (handled)
		वापस IRQ_HANDLED;
	अन्यथा
		वापस IRQ_NONE;
पूर्ण

अटल __अंतरभूत__ व्योम viadrv_acknowledge_irqs(drm_via_निजी_t *dev_priv)
अणु
	u32 status;

	अगर (dev_priv) अणु
		/* Acknowledge पूर्णांकerrupts */
		status = via_पढ़ो(dev_priv, VIA_REG_INTERRUPT);
		via_ग_लिखो(dev_priv, VIA_REG_INTERRUPT, status |
			  dev_priv->irq_pending_mask);
	पूर्ण
पूर्ण

पूर्णांक via_enable_vblank(काष्ठा drm_device *dev, अचिन्हित पूर्णांक pipe)
अणु
	drm_via_निजी_t *dev_priv = dev->dev_निजी;
	u32 status;

	अगर (pipe != 0) अणु
		DRM_ERROR("%s:  bad crtc %u\n", __func__, pipe);
		वापस -EINVAL;
	पूर्ण

	status = via_पढ़ो(dev_priv, VIA_REG_INTERRUPT);
	via_ग_लिखो(dev_priv, VIA_REG_INTERRUPT, status | VIA_IRQ_VBLANK_ENABLE);

	via_ग_लिखो8(dev_priv, 0x83d4, 0x11);
	via_ग_लिखो8_mask(dev_priv, 0x83d5, 0x30, 0x30);

	वापस 0;
पूर्ण

व्योम via_disable_vblank(काष्ठा drm_device *dev, अचिन्हित पूर्णांक pipe)
अणु
	drm_via_निजी_t *dev_priv = dev->dev_निजी;
	u32 status;

	status = via_पढ़ो(dev_priv, VIA_REG_INTERRUPT);
	via_ग_लिखो(dev_priv, VIA_REG_INTERRUPT, status & ~VIA_IRQ_VBLANK_ENABLE);

	via_ग_लिखो8(dev_priv, 0x83d4, 0x11);
	via_ग_लिखो8_mask(dev_priv, 0x83d5, 0x30, 0);

	अगर (pipe != 0)
		DRM_ERROR("%s:  bad crtc %u\n", __func__, pipe);
पूर्ण

अटल पूर्णांक
via_driver_irq_रुको(काष्ठा drm_device *dev, अचिन्हित पूर्णांक irq, पूर्णांक क्रमce_sequence,
		    अचिन्हित पूर्णांक *sequence)
अणु
	drm_via_निजी_t *dev_priv = (drm_via_निजी_t *) dev->dev_निजी;
	अचिन्हित पूर्णांक cur_irq_sequence;
	drm_via_irq_t *cur_irq;
	पूर्णांक ret = 0;
	maskarray_t *masks;
	पूर्णांक real_irq;

	DRM_DEBUG("\n");

	अगर (!dev_priv) अणु
		DRM_ERROR("called with no initialization\n");
		वापस -EINVAL;
	पूर्ण

	अगर (irq >= drm_via_irq_num) अणु
		DRM_ERROR("Trying to wait on unknown irq %d\n", irq);
		वापस -EINVAL;
	पूर्ण

	real_irq = dev_priv->irq_map[irq];

	अगर (real_irq < 0) अणु
		DRM_ERROR("Video IRQ %d not available on this hardware.\n",
			  irq);
		वापस -EINVAL;
	पूर्ण

	masks = dev_priv->irq_masks;
	cur_irq = dev_priv->via_irqs + real_irq;

	अगर (masks[real_irq][2] && !क्रमce_sequence) अणु
		VIA_WAIT_ON(ret, cur_irq->irq_queue, 3 * HZ,
			    ((via_पढ़ो(dev_priv, masks[irq][2]) & masks[irq][3]) ==
			     masks[irq][4]));
		cur_irq_sequence = atomic_पढ़ो(&cur_irq->irq_received);
	पूर्ण अन्यथा अणु
		VIA_WAIT_ON(ret, cur_irq->irq_queue, 3 * HZ,
			    (((cur_irq_sequence =
			       atomic_पढ़ो(&cur_irq->irq_received)) -
			      *sequence) <= (1 << 23)));
	पूर्ण
	*sequence = cur_irq_sequence;
	वापस ret;
पूर्ण


/*
 * drm_dma.h hooks
 */

व्योम via_driver_irq_preinstall(काष्ठा drm_device *dev)
अणु
	drm_via_निजी_t *dev_priv = (drm_via_निजी_t *) dev->dev_निजी;
	u32 status;
	drm_via_irq_t *cur_irq;
	पूर्णांक i;

	DRM_DEBUG("dev_priv: %p\n", dev_priv);
	अगर (dev_priv) अणु
		cur_irq = dev_priv->via_irqs;

		dev_priv->irq_enable_mask = VIA_IRQ_VBLANK_ENABLE;
		dev_priv->irq_pending_mask = VIA_IRQ_VBLANK_PENDING;

		अगर (dev_priv->chipset == VIA_PRO_GROUP_A ||
		    dev_priv->chipset == VIA_DX9_0) अणु
			dev_priv->irq_masks = via_pro_group_a_irqs;
			dev_priv->num_irqs = via_num_pro_group_a;
			dev_priv->irq_map = via_irqmap_pro_group_a;
		पूर्ण अन्यथा अणु
			dev_priv->irq_masks = via_unichrome_irqs;
			dev_priv->num_irqs = via_num_unichrome;
			dev_priv->irq_map = via_irqmap_unichrome;
		पूर्ण

		क्रम (i = 0; i < dev_priv->num_irqs; ++i) अणु
			atomic_set(&cur_irq->irq_received, 0);
			cur_irq->enable_mask = dev_priv->irq_masks[i][0];
			cur_irq->pending_mask = dev_priv->irq_masks[i][1];
			init_रुकोqueue_head(&cur_irq->irq_queue);
			dev_priv->irq_enable_mask |= cur_irq->enable_mask;
			dev_priv->irq_pending_mask |= cur_irq->pending_mask;
			cur_irq++;

			DRM_DEBUG("Initializing IRQ %d\n", i);
		पूर्ण

		dev_priv->last_vblank_valid = 0;

		/* Clear VSync पूर्णांकerrupt regs */
		status = via_पढ़ो(dev_priv, VIA_REG_INTERRUPT);
		via_ग_लिखो(dev_priv, VIA_REG_INTERRUPT, status &
			  ~(dev_priv->irq_enable_mask));

		/* Clear bits अगर they're alपढ़ोy high */
		viadrv_acknowledge_irqs(dev_priv);
	पूर्ण
पूर्ण

पूर्णांक via_driver_irq_postinstall(काष्ठा drm_device *dev)
अणु
	drm_via_निजी_t *dev_priv = (drm_via_निजी_t *) dev->dev_निजी;
	u32 status;

	DRM_DEBUG("fun: %s\n", __func__);
	अगर (!dev_priv)
		वापस -EINVAL;

	status = via_पढ़ो(dev_priv, VIA_REG_INTERRUPT);
	via_ग_लिखो(dev_priv, VIA_REG_INTERRUPT, status | VIA_IRQ_GLOBAL
		  | dev_priv->irq_enable_mask);

	/* Some magic, oh क्रम some data sheets ! */
	via_ग_लिखो8(dev_priv, 0x83d4, 0x11);
	via_ग_लिखो8_mask(dev_priv, 0x83d5, 0x30, 0x30);

	वापस 0;
पूर्ण

व्योम via_driver_irq_uninstall(काष्ठा drm_device *dev)
अणु
	drm_via_निजी_t *dev_priv = (drm_via_निजी_t *) dev->dev_निजी;
	u32 status;

	DRM_DEBUG("\n");
	अगर (dev_priv) अणु

		/* Some more magic, oh क्रम some data sheets ! */

		via_ग_लिखो8(dev_priv, 0x83d4, 0x11);
		via_ग_लिखो8_mask(dev_priv, 0x83d5, 0x30, 0);

		status = via_पढ़ो(dev_priv, VIA_REG_INTERRUPT);
		via_ग_लिखो(dev_priv, VIA_REG_INTERRUPT, status &
			  ~(VIA_IRQ_VBLANK_ENABLE | dev_priv->irq_enable_mask));
	पूर्ण
पूर्ण

पूर्णांक via_रुको_irq(काष्ठा drm_device *dev, व्योम *data, काष्ठा drm_file *file_priv)
अणु
	drm_via_irqरुको_t *irqरुको = data;
	काष्ठा बारpec64 now;
	पूर्णांक ret = 0;
	drm_via_निजी_t *dev_priv = (drm_via_निजी_t *) dev->dev_निजी;
	drm_via_irq_t *cur_irq = dev_priv->via_irqs;
	पूर्णांक क्रमce_sequence;

	अगर (irqरुको->request.irq >= dev_priv->num_irqs) अणु
		DRM_ERROR("Trying to wait on unknown irq %d\n",
			  irqरुको->request.irq);
		वापस -EINVAL;
	पूर्ण

	cur_irq += irqरुको->request.irq;

	चयन (irqरुको->request.type & ~VIA_IRQ_FLAGS_MASK) अणु
	हाल VIA_IRQ_RELATIVE:
		irqरुको->request.sequence +=
			atomic_पढ़ो(&cur_irq->irq_received);
		irqरुको->request.type &= ~_DRM_VBLANK_RELATIVE;
		अवरोध;
	हाल VIA_IRQ_ABSOLUTE:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (irqरुको->request.type & VIA_IRQ_SIGNAL) अणु
		DRM_ERROR("Signals on Via IRQs not implemented yet.\n");
		वापस -EINVAL;
	पूर्ण

	क्रमce_sequence = (irqरुको->request.type & VIA_IRQ_FORCE_SEQUENCE);

	ret = via_driver_irq_रुको(dev, irqरुको->request.irq, क्रमce_sequence,
				  &irqरुको->request.sequence);
	kसमय_get_ts64(&now);
	irqरुको->reply.tval_sec = now.tv_sec;
	irqरुको->reply.tval_usec = now.tv_nsec / NSEC_PER_USEC;

	वापस ret;
पूर्ण
