<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (c) 2014-2015 Hisilicon Limited.
 */

#समावेश <linux/dma-mapping.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/of.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/slab.h>
#समावेश "hnae.h"

#घोषणा cls_to_ae_dev(dev) container_of(dev, काष्ठा hnae_ae_dev, cls_dev)

अटल काष्ठा class *hnae_class;

अटल व्योम
hnae_list_add(spinlock_t *lock, काष्ठा list_head *node, काष्ठा list_head *head)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(lock, flags);
	list_add_tail_rcu(node, head);
	spin_unlock_irqrestore(lock, flags);
पूर्ण

अटल व्योम hnae_list_del(spinlock_t *lock, काष्ठा list_head *node)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(lock, flags);
	list_del_rcu(node);
	spin_unlock_irqrestore(lock, flags);
पूर्ण

अटल पूर्णांक hnae_alloc_buffer(काष्ठा hnae_ring *ring, काष्ठा hnae_desc_cb *cb)
अणु
	अचिन्हित पूर्णांक order = hnae_page_order(ring);
	काष्ठा page *p = dev_alloc_pages(order);

	अगर (!p)
		वापस -ENOMEM;

	cb->priv = p;
	cb->page_offset = 0;
	cb->reuse_flag = 0;
	cb->buf  = page_address(p);
	cb->length = hnae_page_size(ring);
	cb->type = DESC_TYPE_PAGE;

	वापस 0;
पूर्ण

अटल व्योम hnae_मुक्त_buffer(काष्ठा hnae_ring *ring, काष्ठा hnae_desc_cb *cb)
अणु
	अगर (unlikely(!cb->priv))
		वापस;

	अगर (cb->type == DESC_TYPE_SKB)
		dev_kमुक्त_skb_any((काष्ठा sk_buff *)cb->priv);
	अन्यथा अगर (unlikely(is_rx_ring(ring)))
		put_page((काष्ठा page *)cb->priv);

	cb->priv = शून्य;
पूर्ण

अटल पूर्णांक hnae_map_buffer(काष्ठा hnae_ring *ring, काष्ठा hnae_desc_cb *cb)
अणु
	cb->dma = dma_map_page(ring_to_dev(ring), cb->priv, 0,
			       cb->length, ring_to_dma_dir(ring));

	अगर (dma_mapping_error(ring_to_dev(ring), cb->dma))
		वापस -EIO;

	वापस 0;
पूर्ण

अटल व्योम hnae_unmap_buffer(काष्ठा hnae_ring *ring, काष्ठा hnae_desc_cb *cb)
अणु
	अगर (cb->type == DESC_TYPE_SKB)
		dma_unmap_single(ring_to_dev(ring), cb->dma, cb->length,
				 ring_to_dma_dir(ring));
	अन्यथा अगर (cb->length)
		dma_unmap_page(ring_to_dev(ring), cb->dma, cb->length,
			       ring_to_dma_dir(ring));
पूर्ण

अटल काष्ठा hnae_buf_ops hnae_bops = अणु
	.alloc_buffer = hnae_alloc_buffer,
	.मुक्त_buffer = hnae_मुक्त_buffer,
	.map_buffer = hnae_map_buffer,
	.unmap_buffer = hnae_unmap_buffer,
पूर्ण;

अटल पूर्णांक __ae_match(काष्ठा device *dev, स्थिर व्योम *data)
अणु
	काष्ठा hnae_ae_dev *hdev = cls_to_ae_dev(dev);

	अगर (dev_of_node(hdev->dev))
		वापस (data == &hdev->dev->of_node->fwnode);
	अन्यथा अगर (is_acpi_node(hdev->dev->fwnode))
		वापस (data == hdev->dev->fwnode);

	dev_err(dev, "__ae_match cannot read cfg data from OF or acpi\n");
	वापस 0;
पूर्ण

अटल काष्ठा hnae_ae_dev *find_ae(स्थिर काष्ठा fwnode_handle *fwnode)
अणु
	काष्ठा device *dev;

	WARN_ON(!fwnode);

	dev = class_find_device(hnae_class, शून्य, fwnode, __ae_match);

	वापस dev ? cls_to_ae_dev(dev) : शून्य;
पूर्ण

अटल व्योम hnae_मुक्त_buffers(काष्ठा hnae_ring *ring)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ring->desc_num; i++)
		hnae_मुक्त_buffer_detach(ring, i);
पूर्ण

/* Allocate memory क्रम raw pkg, and map with dma */
अटल पूर्णांक hnae_alloc_buffers(काष्ठा hnae_ring *ring)
अणु
	पूर्णांक i, j, ret;

	क्रम (i = 0; i < ring->desc_num; i++) अणु
		ret = hnae_alloc_buffer_attach(ring, i);
		अगर (ret)
			जाओ out_buffer_fail;
	पूर्ण

	वापस 0;

out_buffer_fail:
	क्रम (j = i - 1; j >= 0; j--)
		hnae_मुक्त_buffer_detach(ring, j);
	वापस ret;
पूर्ण

/* मुक्त desc aदीर्घ with its attached buffer */
अटल व्योम hnae_मुक्त_desc(काष्ठा hnae_ring *ring)
अणु
	dma_unmap_single(ring_to_dev(ring), ring->desc_dma_addr,
			 ring->desc_num * माप(ring->desc[0]),
			 ring_to_dma_dir(ring));
	ring->desc_dma_addr = 0;
	kमुक्त(ring->desc);
	ring->desc = शून्य;
पूर्ण

/* alloc desc, without buffer attached */
अटल पूर्णांक hnae_alloc_desc(काष्ठा hnae_ring *ring)
अणु
	पूर्णांक size = ring->desc_num * माप(ring->desc[0]);

	ring->desc = kzalloc(size, GFP_KERNEL);
	अगर (!ring->desc)
		वापस -ENOMEM;

	ring->desc_dma_addr = dma_map_single(ring_to_dev(ring),
		ring->desc, size, ring_to_dma_dir(ring));
	अगर (dma_mapping_error(ring_to_dev(ring), ring->desc_dma_addr)) अणु
		ring->desc_dma_addr = 0;
		kमुक्त(ring->desc);
		ring->desc = शून्य;
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

/* fini ring, also मुक्त the buffer क्रम the ring */
अटल व्योम hnae_fini_ring(काष्ठा hnae_ring *ring)
अणु
	अगर (is_rx_ring(ring))
		hnae_मुक्त_buffers(ring);

	hnae_मुक्त_desc(ring);
	kमुक्त(ring->desc_cb);
	ring->desc_cb = शून्य;
	ring->next_to_clean = 0;
	ring->next_to_use = 0;
पूर्ण

/* init ring, and with buffer क्रम rx ring */
अटल पूर्णांक
hnae_init_ring(काष्ठा hnae_queue *q, काष्ठा hnae_ring *ring, पूर्णांक flags)
अणु
	पूर्णांक ret;

	अगर (ring->desc_num <= 0 || ring->buf_size <= 0)
		वापस -EINVAL;

	ring->q = q;
	ring->flags = flags;
	ring->coal_param = q->handle->coal_param;
	निश्चित(!ring->desc && !ring->desc_cb && !ring->desc_dma_addr);

	/* not matter क्रम tx or rx ring, the ntc and ntc start from 0 */
	निश्चित(ring->next_to_use == 0);
	निश्चित(ring->next_to_clean == 0);

	ring->desc_cb = kसुस्मृति(ring->desc_num, माप(ring->desc_cb[0]),
			GFP_KERNEL);
	अगर (!ring->desc_cb) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	ret = hnae_alloc_desc(ring);
	अगर (ret)
		जाओ out_with_desc_cb;

	अगर (is_rx_ring(ring)) अणु
		ret = hnae_alloc_buffers(ring);
		अगर (ret)
			जाओ out_with_desc;
	पूर्ण

	वापस 0;

out_with_desc:
	hnae_मुक्त_desc(ring);
out_with_desc_cb:
	kमुक्त(ring->desc_cb);
	ring->desc_cb = शून्य;
out:
	वापस ret;
पूर्ण

अटल पूर्णांक hnae_init_queue(काष्ठा hnae_handle *h, काष्ठा hnae_queue *q,
			   काष्ठा hnae_ae_dev *dev)
अणु
	पूर्णांक ret;

	q->dev = dev;
	q->handle = h;

	ret = hnae_init_ring(q, &q->tx_ring, q->tx_ring.flags | RINGF_सूची);
	अगर (ret)
		जाओ out;

	ret = hnae_init_ring(q, &q->rx_ring, q->rx_ring.flags & ~RINGF_सूची);
	अगर (ret)
		जाओ out_with_tx_ring;

	अगर (dev->ops->init_queue)
		dev->ops->init_queue(q);

	वापस 0;

out_with_tx_ring:
	hnae_fini_ring(&q->tx_ring);
out:
	वापस ret;
पूर्ण

अटल व्योम hnae_fini_queue(काष्ठा hnae_queue *q)
अणु
	अगर (q->dev->ops->fini_queue)
		q->dev->ops->fini_queue(q);

	hnae_fini_ring(&q->tx_ring);
	hnae_fini_ring(&q->rx_ring);
पूर्ण

/*
 * ae_chain - define ae chain head
 */
अटल RAW_NOTIFIER_HEAD(ae_chain);

पूर्णांक hnae_रेजिस्टर_notअगरier(काष्ठा notअगरier_block *nb)
अणु
	वापस raw_notअगरier_chain_रेजिस्टर(&ae_chain, nb);
पूर्ण
EXPORT_SYMBOL(hnae_रेजिस्टर_notअगरier);

व्योम hnae_unरेजिस्टर_notअगरier(काष्ठा notअगरier_block *nb)
अणु
	अगर (raw_notअगरier_chain_unरेजिस्टर(&ae_chain, nb))
		dev_err(शून्य, "notifier chain unregister fail\n");
पूर्ण
EXPORT_SYMBOL(hnae_unरेजिस्टर_notअगरier);

पूर्णांक hnae_reinit_handle(काष्ठा hnae_handle *handle)
अणु
	पूर्णांक i, j;
	पूर्णांक ret;

	क्रम (i = 0; i < handle->q_num; i++) /* मुक्त ring*/
		hnae_fini_queue(handle->qs[i]);

	अगर (handle->dev->ops->reset)
		handle->dev->ops->reset(handle);

	क्रम (i = 0; i < handle->q_num; i++) अणु/* reinit ring*/
		ret = hnae_init_queue(handle, handle->qs[i], handle->dev);
		अगर (ret)
			जाओ out_when_init_queue;
	पूर्ण
	वापस 0;
out_when_init_queue:
	क्रम (j = i - 1; j >= 0; j--)
		hnae_fini_queue(handle->qs[j]);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(hnae_reinit_handle);

/* hnae_get_handle - get a handle from the AE
 * @owner_dev: the dev use this handle
 * @ae_id: the id of the ae to be used
 * @ae_opts: the options set क्रम the handle
 * @bops: the callbacks क्रम buffer management
 *
 * वापस handle ptr or ERR_PTR
 */
काष्ठा hnae_handle *hnae_get_handle(काष्ठा device *owner_dev,
				    स्थिर काष्ठा fwnode_handle	*fwnode,
				    u32 port_id,
				    काष्ठा hnae_buf_ops *bops)
अणु
	काष्ठा hnae_ae_dev *dev;
	काष्ठा hnae_handle *handle;
	पूर्णांक i, j;
	पूर्णांक ret;

	dev = find_ae(fwnode);
	अगर (!dev)
		वापस ERR_PTR(-ENODEV);

	handle = dev->ops->get_handle(dev, port_id);
	अगर (IS_ERR(handle)) अणु
		put_device(&dev->cls_dev);
		वापस handle;
	पूर्ण

	handle->dev = dev;
	handle->owner_dev = owner_dev;
	handle->bops = bops ? bops : &hnae_bops;
	handle->eport_id = port_id;

	क्रम (i = 0; i < handle->q_num; i++) अणु
		ret = hnae_init_queue(handle, handle->qs[i], dev);
		अगर (ret)
			जाओ out_when_init_queue;
	पूर्ण

	__module_get(dev->owner);

	hnae_list_add(&dev->lock, &handle->node, &dev->handle_list);

	वापस handle;

out_when_init_queue:
	क्रम (j = i - 1; j >= 0; j--)
		hnae_fini_queue(handle->qs[j]);

	put_device(&dev->cls_dev);

	वापस ERR_PTR(-ENOMEM);
पूर्ण
EXPORT_SYMBOL(hnae_get_handle);

व्योम hnae_put_handle(काष्ठा hnae_handle *h)
अणु
	काष्ठा hnae_ae_dev *dev = h->dev;
	पूर्णांक i;

	क्रम (i = 0; i < h->q_num; i++)
		hnae_fini_queue(h->qs[i]);

	अगर (h->dev->ops->reset)
		h->dev->ops->reset(h);

	hnae_list_del(&dev->lock, &h->node);

	अगर (dev->ops->put_handle)
		dev->ops->put_handle(h);

	module_put(dev->owner);

	put_device(&dev->cls_dev);
पूर्ण
EXPORT_SYMBOL(hnae_put_handle);

अटल व्योम hnae_release(काष्ठा device *dev)
अणु
पूर्ण

/**
 * hnae_ae_रेजिस्टर - रेजिस्टर a AE engine to hnae framework
 * @hdev: the hnae ae engine device
 * @owner:  the module who provides this dev
 * NOTE: the duplicated name will not be checked
 */
पूर्णांक hnae_ae_रेजिस्टर(काष्ठा hnae_ae_dev *hdev, काष्ठा module *owner)
अणु
	अटल atomic_t id = ATOMIC_INIT(-1);
	पूर्णांक ret;

	अगर (!hdev->dev)
		वापस -ENODEV;

	अगर (!hdev->ops || !hdev->ops->get_handle ||
	    !hdev->ops->toggle_ring_irq ||
	    !hdev->ops->get_status || !hdev->ops->adjust_link)
		वापस -EINVAL;

	hdev->owner = owner;
	hdev->id = (पूर्णांक)atomic_inc_वापस(&id);
	hdev->cls_dev.parent = hdev->dev;
	hdev->cls_dev.class = hnae_class;
	hdev->cls_dev.release = hnae_release;
	(व्योम)dev_set_name(&hdev->cls_dev, "hnae%d", hdev->id);
	ret = device_रेजिस्टर(&hdev->cls_dev);
	अगर (ret)
		वापस ret;

	__module_get(THIS_MODULE);

	INIT_LIST_HEAD(&hdev->handle_list);
	spin_lock_init(&hdev->lock);

	ret = raw_notअगरier_call_chain(&ae_chain, HNAE_AE_REGISTER, शून्य);
	अगर (ret)
		dev_dbg(hdev->dev,
			"has not notifier for AE: %s\n", hdev->name);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(hnae_ae_रेजिस्टर);

/**
 * hnae_ae_unरेजिस्टर - unरेजिस्टरs a HNAE AE engine
 * @hdev: the device to unरेजिस्टर
 */
व्योम hnae_ae_unरेजिस्टर(काष्ठा hnae_ae_dev *hdev)
अणु
	device_unरेजिस्टर(&hdev->cls_dev);
	module_put(THIS_MODULE);
पूर्ण
EXPORT_SYMBOL(hnae_ae_unरेजिस्टर);

अटल पूर्णांक __init hnae_init(व्योम)
अणु
	hnae_class = class_create(THIS_MODULE, "hnae");
	वापस PTR_ERR_OR_ZERO(hnae_class);
पूर्ण

अटल व्योम __निकास hnae_निकास(व्योम)
अणु
	class_destroy(hnae_class);
पूर्ण

subsys_initcall(hnae_init);
module_निकास(hnae_निकास);

MODULE_AUTHOR("Hisilicon, Inc.");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Hisilicon Network Acceleration Engine Framework");

/* vi: set tw=78 noet: */
