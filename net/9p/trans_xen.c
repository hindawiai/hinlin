<शैली गुरु>
/*
 * linux/fs/9p/trans_xen
 *
 * Xen transport layer.
 *
 * Copyright (C) 2017 by Stefano Stabellini <stefano@aporeto.com>
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License version 2
 * as published by the Free Software Foundation; or, when distributed
 * separately from the Linux kernel or incorporated पूर्णांकo other
 * software packages, subject to the following license:
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a copy
 * of this source file (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy, modअगरy,
 * merge, publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to करो so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#समावेश <xen/events.h>
#समावेश <xen/grant_table.h>
#समावेश <xen/xen.h>
#समावेश <xen/xenbus.h>
#समावेश <xen/पूर्णांकerface/io/9pfs.h>

#समावेश <linux/module.h>
#समावेश <linux/spinlock.h>
#समावेश <net/9p/9p.h>
#समावेश <net/9p/client.h>
#समावेश <net/9p/transport.h>

#घोषणा XEN_9PFS_NUM_RINGS 2
#घोषणा XEN_9PFS_RING_ORDER 9
#घोषणा XEN_9PFS_RING_SIZE(ring)  XEN_FLEX_RING_SIZE(ring->पूर्णांकf->ring_order)

काष्ठा xen_9pfs_header अणु
	uपूर्णांक32_t size;
	uपूर्णांक8_t id;
	uपूर्णांक16_t tag;

	/* uपूर्णांक8_t sdata[]; */
पूर्ण __attribute__((packed));

/* One per ring, more than one per 9pfs share */
काष्ठा xen_9pfs_dataring अणु
	काष्ठा xen_9pfs_front_priv *priv;

	काष्ठा xen_9pfs_data_पूर्णांकf *पूर्णांकf;
	grant_ref_t ref;
	पूर्णांक evtchn;
	पूर्णांक irq;
	/* protect a ring from concurrent accesses */
	spinlock_t lock;

	काष्ठा xen_9pfs_data data;
	रुको_queue_head_t wq;
	काष्ठा work_काष्ठा work;
पूर्ण;

/* One per 9pfs share */
काष्ठा xen_9pfs_front_priv अणु
	काष्ठा list_head list;
	काष्ठा xenbus_device *dev;
	अक्षर *tag;
	काष्ठा p9_client *client;

	पूर्णांक num_rings;
	काष्ठा xen_9pfs_dataring *rings;
पूर्ण;

अटल LIST_HEAD(xen_9pfs_devs);
अटल DEFINE_RWLOCK(xen_9pfs_lock);

/* We करोn't currently allow canceling of requests */
अटल पूर्णांक p9_xen_cancel(काष्ठा p9_client *client, काष्ठा p9_req_t *req)
अणु
	वापस 1;
पूर्ण

अटल पूर्णांक p9_xen_create(काष्ठा p9_client *client, स्थिर अक्षर *addr, अक्षर *args)
अणु
	काष्ठा xen_9pfs_front_priv *priv;

	अगर (addr == शून्य)
		वापस -EINVAL;

	पढ़ो_lock(&xen_9pfs_lock);
	list_क्रम_each_entry(priv, &xen_9pfs_devs, list) अणु
		अगर (!म_भेद(priv->tag, addr)) अणु
			priv->client = client;
			पढ़ो_unlock(&xen_9pfs_lock);
			वापस 0;
		पूर्ण
	पूर्ण
	पढ़ो_unlock(&xen_9pfs_lock);
	वापस -EINVAL;
पूर्ण

अटल व्योम p9_xen_बंद(काष्ठा p9_client *client)
अणु
	काष्ठा xen_9pfs_front_priv *priv;

	पढ़ो_lock(&xen_9pfs_lock);
	list_क्रम_each_entry(priv, &xen_9pfs_devs, list) अणु
		अगर (priv->client == client) अणु
			priv->client = शून्य;
			पढ़ो_unlock(&xen_9pfs_lock);
			वापस;
		पूर्ण
	पूर्ण
	पढ़ो_unlock(&xen_9pfs_lock);
पूर्ण

अटल bool p9_xen_ग_लिखो_toकरो(काष्ठा xen_9pfs_dataring *ring, RING_IDX size)
अणु
	RING_IDX cons, prod;

	cons = ring->पूर्णांकf->out_cons;
	prod = ring->पूर्णांकf->out_prod;
	virt_mb();

	वापस XEN_9PFS_RING_SIZE(ring) -
		xen_9pfs_queued(prod, cons, XEN_9PFS_RING_SIZE(ring)) >= size;
पूर्ण

अटल पूर्णांक p9_xen_request(काष्ठा p9_client *client, काष्ठा p9_req_t *p9_req)
अणु
	काष्ठा xen_9pfs_front_priv *priv = शून्य;
	RING_IDX cons, prod, masked_cons, masked_prod;
	अचिन्हित दीर्घ flags;
	u32 size = p9_req->tc.size;
	काष्ठा xen_9pfs_dataring *ring;
	पूर्णांक num;

	पढ़ो_lock(&xen_9pfs_lock);
	list_क्रम_each_entry(priv, &xen_9pfs_devs, list) अणु
		अगर (priv->client == client)
			अवरोध;
	पूर्ण
	पढ़ो_unlock(&xen_9pfs_lock);
	अगर (!priv || priv->client != client)
		वापस -EINVAL;

	num = p9_req->tc.tag % priv->num_rings;
	ring = &priv->rings[num];

again:
	जबतक (रुको_event_समाप्तable(ring->wq,
				   p9_xen_ग_लिखो_toकरो(ring, size)) != 0)
		;

	spin_lock_irqsave(&ring->lock, flags);
	cons = ring->पूर्णांकf->out_cons;
	prod = ring->पूर्णांकf->out_prod;
	virt_mb();

	अगर (XEN_9PFS_RING_SIZE(ring) -
	    xen_9pfs_queued(prod, cons, XEN_9PFS_RING_SIZE(ring)) < size) अणु
		spin_unlock_irqrestore(&ring->lock, flags);
		जाओ again;
	पूर्ण

	masked_prod = xen_9pfs_mask(prod, XEN_9PFS_RING_SIZE(ring));
	masked_cons = xen_9pfs_mask(cons, XEN_9PFS_RING_SIZE(ring));

	xen_9pfs_ग_लिखो_packet(ring->data.out, p9_req->tc.sdata, size,
			      &masked_prod, masked_cons,
			      XEN_9PFS_RING_SIZE(ring));

	p9_req->status = REQ_STATUS_SENT;
	virt_wmb();			/* ग_लिखो ring beक्रमe updating poपूर्णांकer */
	prod += size;
	ring->पूर्णांकf->out_prod = prod;
	spin_unlock_irqrestore(&ring->lock, flags);
	notअगरy_remote_via_irq(ring->irq);
	p9_req_put(p9_req);

	वापस 0;
पूर्ण

अटल व्योम p9_xen_response(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा xen_9pfs_front_priv *priv;
	काष्ठा xen_9pfs_dataring *ring;
	RING_IDX cons, prod, masked_cons, masked_prod;
	काष्ठा xen_9pfs_header h;
	काष्ठा p9_req_t *req;
	पूर्णांक status;

	ring = container_of(work, काष्ठा xen_9pfs_dataring, work);
	priv = ring->priv;

	जबतक (1) अणु
		cons = ring->पूर्णांकf->in_cons;
		prod = ring->पूर्णांकf->in_prod;
		virt_rmb();

		अगर (xen_9pfs_queued(prod, cons, XEN_9PFS_RING_SIZE(ring)) <
		    माप(h)) अणु
			notअगरy_remote_via_irq(ring->irq);
			वापस;
		पूर्ण

		masked_prod = xen_9pfs_mask(prod, XEN_9PFS_RING_SIZE(ring));
		masked_cons = xen_9pfs_mask(cons, XEN_9PFS_RING_SIZE(ring));

		/* First, पढ़ो just the header */
		xen_9pfs_पढ़ो_packet(&h, ring->data.in, माप(h),
				     masked_prod, &masked_cons,
				     XEN_9PFS_RING_SIZE(ring));

		req = p9_tag_lookup(priv->client, h.tag);
		अगर (!req || req->status != REQ_STATUS_SENT) अणु
			dev_warn(&priv->dev->dev, "Wrong req tag=%x\n", h.tag);
			cons += h.size;
			virt_mb();
			ring->पूर्णांकf->in_cons = cons;
			जारी;
		पूर्ण

		स_नकल(&req->rc, &h, माप(h));
		req->rc.offset = 0;

		masked_cons = xen_9pfs_mask(cons, XEN_9PFS_RING_SIZE(ring));
		/* Then, पढ़ो the whole packet (including the header) */
		xen_9pfs_पढ़ो_packet(req->rc.sdata, ring->data.in, h.size,
				     masked_prod, &masked_cons,
				     XEN_9PFS_RING_SIZE(ring));

		virt_mb();
		cons += h.size;
		ring->पूर्णांकf->in_cons = cons;

		status = (req->status != REQ_STATUS_ERROR) ?
			REQ_STATUS_RCVD : REQ_STATUS_ERROR;

		p9_client_cb(priv->client, req, status);
	पूर्ण
पूर्ण

अटल irqवापस_t xen_9pfs_front_event_handler(पूर्णांक irq, व्योम *r)
अणु
	काष्ठा xen_9pfs_dataring *ring = r;

	अगर (!ring || !ring->priv->client) अणु
		/* ignore spurious पूर्णांकerrupt */
		वापस IRQ_HANDLED;
	पूर्ण

	wake_up_पूर्णांकerruptible(&ring->wq);
	schedule_work(&ring->work);

	वापस IRQ_HANDLED;
पूर्ण

अटल काष्ठा p9_trans_module p9_xen_trans = अणु
	.name = "xen",
	.maxsize = 1 << (XEN_9PFS_RING_ORDER + XEN_PAGE_SHIFT - 2),
	.def = 1,
	.create = p9_xen_create,
	.बंद = p9_xen_बंद,
	.request = p9_xen_request,
	.cancel = p9_xen_cancel,
	.owner = THIS_MODULE,
पूर्ण;

अटल स्थिर काष्ठा xenbus_device_id xen_9pfs_front_ids[] = अणु
	अणु "9pfs" पूर्ण,
	अणु "" पूर्ण
पूर्ण;

अटल व्योम xen_9pfs_front_मुक्त(काष्ठा xen_9pfs_front_priv *priv)
अणु
	पूर्णांक i, j;

	ग_लिखो_lock(&xen_9pfs_lock);
	list_del(&priv->list);
	ग_लिखो_unlock(&xen_9pfs_lock);

	क्रम (i = 0; i < priv->num_rings; i++) अणु
		अगर (!priv->rings[i].पूर्णांकf)
			अवरोध;
		अगर (priv->rings[i].irq > 0)
			unbind_from_irqhandler(priv->rings[i].irq, priv->dev);
		अगर (priv->rings[i].data.in) अणु
			क्रम (j = 0;
			     j < (1 << priv->rings[i].पूर्णांकf->ring_order);
			     j++) अणु
				grant_ref_t ref;

				ref = priv->rings[i].पूर्णांकf->ref[j];
				gnttab_end_क्रमeign_access(ref, 0, 0);
			पूर्ण
			मुक्त_pages((अचिन्हित दीर्घ)priv->rings[i].data.in,
				   priv->rings[i].पूर्णांकf->ring_order -
				   (PAGE_SHIFT - XEN_PAGE_SHIFT));
		पूर्ण
		gnttab_end_क्रमeign_access(priv->rings[i].ref, 0, 0);
		मुक्त_page((अचिन्हित दीर्घ)priv->rings[i].पूर्णांकf);
	पूर्ण
	kमुक्त(priv->rings);
	kमुक्त(priv->tag);
	kमुक्त(priv);
पूर्ण

अटल पूर्णांक xen_9pfs_front_हटाओ(काष्ठा xenbus_device *dev)
अणु
	काष्ठा xen_9pfs_front_priv *priv = dev_get_drvdata(&dev->dev);

	dev_set_drvdata(&dev->dev, शून्य);
	xen_9pfs_front_मुक्त(priv);
	वापस 0;
पूर्ण

अटल पूर्णांक xen_9pfs_front_alloc_dataring(काष्ठा xenbus_device *dev,
					 काष्ठा xen_9pfs_dataring *ring,
					 अचिन्हित पूर्णांक order)
अणु
	पूर्णांक i = 0;
	पूर्णांक ret = -ENOMEM;
	व्योम *bytes = शून्य;

	init_रुकोqueue_head(&ring->wq);
	spin_lock_init(&ring->lock);
	INIT_WORK(&ring->work, p9_xen_response);

	ring->पूर्णांकf = (काष्ठा xen_9pfs_data_पूर्णांकf *)get_zeroed_page(GFP_KERNEL);
	अगर (!ring->पूर्णांकf)
		वापस ret;
	ret = gnttab_grant_क्रमeign_access(dev->otherend_id,
					  virt_to_gfn(ring->पूर्णांकf), 0);
	अगर (ret < 0)
		जाओ out;
	ring->ref = ret;
	bytes = (व्योम *)__get_मुक्त_pages(GFP_KERNEL | __GFP_ZERO,
			order - (PAGE_SHIFT - XEN_PAGE_SHIFT));
	अगर (!bytes) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण
	क्रम (; i < (1 << order); i++) अणु
		ret = gnttab_grant_क्रमeign_access(
				dev->otherend_id, virt_to_gfn(bytes) + i, 0);
		अगर (ret < 0)
			जाओ out;
		ring->पूर्णांकf->ref[i] = ret;
	पूर्ण
	ring->पूर्णांकf->ring_order = order;
	ring->data.in = bytes;
	ring->data.out = bytes + XEN_FLEX_RING_SIZE(order);

	ret = xenbus_alloc_evtchn(dev, &ring->evtchn);
	अगर (ret)
		जाओ out;
	ring->irq = bind_evtchn_to_irqhandler(ring->evtchn,
					      xen_9pfs_front_event_handler,
					      0, "xen_9pfs-frontend", ring);
	अगर (ring->irq >= 0)
		वापस 0;

	xenbus_मुक्त_evtchn(dev, ring->evtchn);
	ret = ring->irq;
out:
	अगर (bytes) अणु
		क्रम (i--; i >= 0; i--)
			gnttab_end_क्रमeign_access(ring->पूर्णांकf->ref[i], 0, 0);
		मुक्त_pages((अचिन्हित दीर्घ)bytes,
			   ring->पूर्णांकf->ring_order -
			   (PAGE_SHIFT - XEN_PAGE_SHIFT));
	पूर्ण
	gnttab_end_क्रमeign_access(ring->ref, 0, 0);
	मुक्त_page((अचिन्हित दीर्घ)ring->पूर्णांकf);
	वापस ret;
पूर्ण

अटल पूर्णांक xen_9pfs_front_probe(काष्ठा xenbus_device *dev,
				स्थिर काष्ठा xenbus_device_id *id)
अणु
	पूर्णांक ret, i;
	काष्ठा xenbus_transaction xbt;
	काष्ठा xen_9pfs_front_priv *priv = शून्य;
	अक्षर *versions;
	अचिन्हित पूर्णांक max_rings, max_ring_order, len = 0;

	versions = xenbus_पढ़ो(XBT_NIL, dev->otherend, "versions", &len);
	अगर (IS_ERR(versions))
		वापस PTR_ERR(versions);
	अगर (म_भेद(versions, "1")) अणु
		kमुक्त(versions);
		वापस -EINVAL;
	पूर्ण
	kमुक्त(versions);
	max_rings = xenbus_पढ़ो_अचिन्हित(dev->otherend, "max-rings", 0);
	अगर (max_rings < XEN_9PFS_NUM_RINGS)
		वापस -EINVAL;
	max_ring_order = xenbus_पढ़ो_अचिन्हित(dev->otherend,
					      "max-ring-page-order", 0);
	अगर (max_ring_order > XEN_9PFS_RING_ORDER)
		max_ring_order = XEN_9PFS_RING_ORDER;
	अगर (p9_xen_trans.maxsize > XEN_FLEX_RING_SIZE(max_ring_order))
		p9_xen_trans.maxsize = XEN_FLEX_RING_SIZE(max_ring_order) / 2;

	priv = kzalloc(माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->dev = dev;
	priv->num_rings = XEN_9PFS_NUM_RINGS;
	priv->rings = kसुस्मृति(priv->num_rings, माप(*priv->rings),
			      GFP_KERNEL);
	अगर (!priv->rings) अणु
		kमुक्त(priv);
		वापस -ENOMEM;
	पूर्ण

	क्रम (i = 0; i < priv->num_rings; i++) अणु
		priv->rings[i].priv = priv;
		ret = xen_9pfs_front_alloc_dataring(dev, &priv->rings[i],
						    max_ring_order);
		अगर (ret < 0)
			जाओ error;
	पूर्ण

 again:
	ret = xenbus_transaction_start(&xbt);
	अगर (ret) अणु
		xenbus_dev_fatal(dev, ret, "starting transaction");
		जाओ error;
	पूर्ण
	ret = xenbus_म_लिखो(xbt, dev->nodename, "version", "%u", 1);
	अगर (ret)
		जाओ error_xenbus;
	ret = xenbus_म_लिखो(xbt, dev->nodename, "num-rings", "%u",
			    priv->num_rings);
	अगर (ret)
		जाओ error_xenbus;
	क्रम (i = 0; i < priv->num_rings; i++) अणु
		अक्षर str[16];

		BUILD_BUG_ON(XEN_9PFS_NUM_RINGS > 9);
		प्र_लिखो(str, "ring-ref%d", i);
		ret = xenbus_म_लिखो(xbt, dev->nodename, str, "%d",
				    priv->rings[i].ref);
		अगर (ret)
			जाओ error_xenbus;

		प्र_लिखो(str, "event-channel-%d", i);
		ret = xenbus_म_लिखो(xbt, dev->nodename, str, "%u",
				    priv->rings[i].evtchn);
		अगर (ret)
			जाओ error_xenbus;
	पूर्ण
	priv->tag = xenbus_पढ़ो(xbt, dev->nodename, "tag", शून्य);
	अगर (IS_ERR(priv->tag)) अणु
		ret = PTR_ERR(priv->tag);
		जाओ error_xenbus;
	पूर्ण
	ret = xenbus_transaction_end(xbt, 0);
	अगर (ret) अणु
		अगर (ret == -EAGAIN)
			जाओ again;
		xenbus_dev_fatal(dev, ret, "completing transaction");
		जाओ error;
	पूर्ण

	ग_लिखो_lock(&xen_9pfs_lock);
	list_add_tail(&priv->list, &xen_9pfs_devs);
	ग_लिखो_unlock(&xen_9pfs_lock);
	dev_set_drvdata(&dev->dev, priv);
	xenbus_चयन_state(dev, XenbusStateInitialised);

	वापस 0;

 error_xenbus:
	xenbus_transaction_end(xbt, 1);
	xenbus_dev_fatal(dev, ret, "writing xenstore");
 error:
	dev_set_drvdata(&dev->dev, शून्य);
	xen_9pfs_front_मुक्त(priv);
	वापस ret;
पूर्ण

अटल पूर्णांक xen_9pfs_front_resume(काष्ठा xenbus_device *dev)
अणु
	dev_warn(&dev->dev, "suspend/resume unsupported\n");
	वापस 0;
पूर्ण

अटल व्योम xen_9pfs_front_changed(काष्ठा xenbus_device *dev,
				   क्रमागत xenbus_state backend_state)
अणु
	चयन (backend_state) अणु
	हाल XenbusStateReconfiguring:
	हाल XenbusStateReconfigured:
	हाल XenbusStateInitialising:
	हाल XenbusStateInitialised:
	हाल XenbusStateUnknown:
		अवरोध;

	हाल XenbusStateInitWait:
		अवरोध;

	हाल XenbusStateConnected:
		xenbus_चयन_state(dev, XenbusStateConnected);
		अवरोध;

	हाल XenbusStateClosed:
		अगर (dev->state == XenbusStateClosed)
			अवरोध;
		fallthrough;	/* Missed the backend's CLOSING state */
	हाल XenbusStateClosing:
		xenbus_frontend_बंदd(dev);
		अवरोध;
	पूर्ण
पूर्ण

अटल काष्ठा xenbus_driver xen_9pfs_front_driver = अणु
	.ids = xen_9pfs_front_ids,
	.probe = xen_9pfs_front_probe,
	.हटाओ = xen_9pfs_front_हटाओ,
	.resume = xen_9pfs_front_resume,
	.otherend_changed = xen_9pfs_front_changed,
पूर्ण;

अटल पूर्णांक p9_trans_xen_init(व्योम)
अणु
	पूर्णांक rc;

	अगर (!xen_करोमुख्य())
		वापस -ENODEV;

	pr_info("Initialising Xen transport for 9pfs\n");

	v9fs_रेजिस्टर_trans(&p9_xen_trans);
	rc = xenbus_रेजिस्टर_frontend(&xen_9pfs_front_driver);
	अगर (rc)
		v9fs_unरेजिस्टर_trans(&p9_xen_trans);

	वापस rc;
पूर्ण
module_init(p9_trans_xen_init);

अटल व्योम p9_trans_xen_निकास(व्योम)
अणु
	v9fs_unरेजिस्टर_trans(&p9_xen_trans);
	वापस xenbus_unरेजिस्टर_driver(&xen_9pfs_front_driver);
पूर्ण
module_निकास(p9_trans_xen_निकास);

MODULE_AUTHOR("Stefano Stabellini <stefano@aporeto.com>");
MODULE_DESCRIPTION("Xen Transport for 9P");
MODULE_LICENSE("GPL");
