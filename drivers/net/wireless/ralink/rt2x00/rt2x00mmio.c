<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
	Copyright (C) 2004 - 2009 Ivo van Doorn <IvDoorn@gmail.com>
	<http://rt2x00.serialmonkey.com>

 */

/*
	Module: rt2x00mmio
	Abstract: rt2x00 generic mmio device routines.
 */

#समावेश <linux/dma-mapping.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>

#समावेश "rt2x00.h"
#समावेश "rt2x00mmio.h"

/*
 * Register access.
 */
पूर्णांक rt2x00mmio_regbusy_पढ़ो(काष्ठा rt2x00_dev *rt2x00dev,
			    स्थिर अचिन्हित पूर्णांक offset,
			    स्थिर काष्ठा rt2x00_field32 field,
			    u32 *reg)
अणु
	अचिन्हित पूर्णांक i;

	अगर (!test_bit(DEVICE_STATE_PRESENT, &rt2x00dev->flags))
		वापस 0;

	क्रम (i = 0; i < REGISTER_BUSY_COUNT; i++) अणु
		*reg = rt2x00mmio_रेजिस्टर_पढ़ो(rt2x00dev, offset);
		अगर (!rt2x00_get_field32(*reg, field))
			वापस 1;
		udelay(REGISTER_BUSY_DELAY);
	पूर्ण

	prपूर्णांकk_once(KERN_ERR "%s() Indirect register access failed: "
	      "offset=0x%.08x, value=0x%.08x\n", __func__, offset, *reg);
	*reg = ~0;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(rt2x00mmio_regbusy_पढ़ो);

bool rt2x00mmio_rxकरोne(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	काष्ठा data_queue *queue = rt2x00dev->rx;
	काष्ठा queue_entry *entry;
	काष्ठा queue_entry_priv_mmio *entry_priv;
	काष्ठा skb_frame_desc *skbdesc;
	पूर्णांक max_rx = 16;

	जबतक (--max_rx) अणु
		entry = rt2x00queue_get_entry(queue, Q_INDEX);
		entry_priv = entry->priv_data;

		अगर (rt2x00dev->ops->lib->get_entry_state(entry))
			अवरोध;

		/*
		 * Fill in desc fields of the skb descriptor
		 */
		skbdesc = get_skb_frame_desc(entry->skb);
		skbdesc->desc = entry_priv->desc;
		skbdesc->desc_len = entry->queue->desc_size;

		/*
		 * DMA is alपढ़ोy करोne, notअगरy rt2x00lib that
		 * it finished successfully.
		 */
		rt2x00lib_dmastart(entry);
		rt2x00lib_dmaकरोne(entry);

		/*
		 * Send the frame to rt2x00lib क्रम further processing.
		 */
		rt2x00lib_rxकरोne(entry, GFP_ATOMIC);
	पूर्ण

	वापस !max_rx;
पूर्ण
EXPORT_SYMBOL_GPL(rt2x00mmio_rxकरोne);

व्योम rt2x00mmio_flush_queue(काष्ठा data_queue *queue, bool drop)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; !rt2x00queue_empty(queue) && i < 10; i++)
		msleep(50);
पूर्ण
EXPORT_SYMBOL_GPL(rt2x00mmio_flush_queue);

/*
 * Device initialization handlers.
 */
अटल पूर्णांक rt2x00mmio_alloc_queue_dma(काष्ठा rt2x00_dev *rt2x00dev,
				      काष्ठा data_queue *queue)
अणु
	काष्ठा queue_entry_priv_mmio *entry_priv;
	व्योम *addr;
	dma_addr_t dma;
	अचिन्हित पूर्णांक i;

	/*
	 * Allocate DMA memory क्रम descriptor and buffer.
	 */
	addr = dma_alloc_coherent(rt2x00dev->dev,
				  queue->limit * queue->desc_size, &dma,
				  GFP_KERNEL);
	अगर (!addr)
		वापस -ENOMEM;

	/*
	 * Initialize all queue entries to contain valid addresses.
	 */
	क्रम (i = 0; i < queue->limit; i++) अणु
		entry_priv = queue->entries[i].priv_data;
		entry_priv->desc = addr + i * queue->desc_size;
		entry_priv->desc_dma = dma + i * queue->desc_size;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम rt2x00mmio_मुक्त_queue_dma(काष्ठा rt2x00_dev *rt2x00dev,
				      काष्ठा data_queue *queue)
अणु
	काष्ठा queue_entry_priv_mmio *entry_priv =
	    queue->entries[0].priv_data;

	अगर (entry_priv->desc)
		dma_मुक्त_coherent(rt2x00dev->dev,
				  queue->limit * queue->desc_size,
				  entry_priv->desc, entry_priv->desc_dma);
	entry_priv->desc = शून्य;
पूर्ण

पूर्णांक rt2x00mmio_initialize(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	काष्ठा data_queue *queue;
	पूर्णांक status;

	/*
	 * Allocate DMA
	 */
	queue_क्रम_each(rt2x00dev, queue) अणु
		status = rt2x00mmio_alloc_queue_dma(rt2x00dev, queue);
		अगर (status)
			जाओ निकास;
	पूर्ण

	/*
	 * Register पूर्णांकerrupt handler.
	 */
	status = request_irq(rt2x00dev->irq,
			     rt2x00dev->ops->lib->irq_handler,
			     IRQF_SHARED, rt2x00dev->name, rt2x00dev);
	अगर (status) अणु
		rt2x00_err(rt2x00dev, "IRQ %d allocation failed (error %d)\n",
			   rt2x00dev->irq, status);
		जाओ निकास;
	पूर्ण

	वापस 0;

निकास:
	queue_क्रम_each(rt2x00dev, queue)
		rt2x00mmio_मुक्त_queue_dma(rt2x00dev, queue);

	वापस status;
पूर्ण
EXPORT_SYMBOL_GPL(rt2x00mmio_initialize);

व्योम rt2x00mmio_uninitialize(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	काष्ठा data_queue *queue;

	/*
	 * Free irq line.
	 */
	मुक्त_irq(rt2x00dev->irq, rt2x00dev);

	/*
	 * Free DMA
	 */
	queue_क्रम_each(rt2x00dev, queue)
		rt2x00mmio_मुक्त_queue_dma(rt2x00dev, queue);
पूर्ण
EXPORT_SYMBOL_GPL(rt2x00mmio_uninitialize);

/*
 * rt2x00mmio module inक्रमmation.
 */
MODULE_AUTHOR(DRV_PROJECT);
MODULE_VERSION(DRV_VERSION);
MODULE_DESCRIPTION("rt2x00 mmio library");
MODULE_LICENSE("GPL");
