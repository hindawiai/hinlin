<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Xenbus code क्रम netअगर backend
 *
 * Copyright (C) 2005 Rusty Russell <rusty@rustcorp.com.au>
 * Copyright (C) 2005 XenSource Ltd
*/

#समावेश "common.h"
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/rtnetlink.h>

अटल पूर्णांक connect_data_rings(काष्ठा backend_info *be,
			      काष्ठा xenvअगर_queue *queue);
अटल व्योम connect(काष्ठा backend_info *be);
अटल पूर्णांक पढ़ो_xenbus_vअगर_flags(काष्ठा backend_info *be);
अटल पूर्णांक backend_create_xenvअगर(काष्ठा backend_info *be);
अटल व्योम unरेजिस्टर_hotplug_status_watch(काष्ठा backend_info *be);
अटल व्योम xen_unरेजिस्टर_watchers(काष्ठा xenvअगर *vअगर);
अटल व्योम set_backend_state(काष्ठा backend_info *be,
			      क्रमागत xenbus_state state);

#अगर_घोषित CONFIG_DEBUG_FS
काष्ठा dentry *xen_netback_dbg_root = शून्य;

अटल पूर्णांक xenvअगर_पढ़ो_io_ring(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा xenvअगर_queue *queue = m->निजी;
	काष्ठा xen_netअगर_tx_back_ring *tx_ring = &queue->tx;
	काष्ठा xen_netअगर_rx_back_ring *rx_ring = &queue->rx;
	काष्ठा netdev_queue *dev_queue;

	अगर (tx_ring->sring) अणु
		काष्ठा xen_netअगर_tx_sring *sring = tx_ring->sring;

		seq_म_लिखो(m, "Queue %d\nTX: nr_ents %u\n", queue->id,
			   tx_ring->nr_ents);
		seq_म_लिखो(m, "req prod %u (%d) cons %u (%d) event %u (%d)\n",
			   sring->req_prod,
			   sring->req_prod - sring->rsp_prod,
			   tx_ring->req_cons,
			   tx_ring->req_cons - sring->rsp_prod,
			   sring->req_event,
			   sring->req_event - sring->rsp_prod);
		seq_म_लिखो(m, "rsp prod %u (base) pvt %u (%d) event %u (%d)\n",
			   sring->rsp_prod,
			   tx_ring->rsp_prod_pvt,
			   tx_ring->rsp_prod_pvt - sring->rsp_prod,
			   sring->rsp_event,
			   sring->rsp_event - sring->rsp_prod);
		seq_म_लिखो(m, "pending prod %u pending cons %u nr_pending_reqs %u\n",
			   queue->pending_prod,
			   queue->pending_cons,
			   nr_pending_reqs(queue));
		seq_म_लिखो(m, "dealloc prod %u dealloc cons %u dealloc_queue %u\n\n",
			   queue->dealloc_prod,
			   queue->dealloc_cons,
			   queue->dealloc_prod - queue->dealloc_cons);
	पूर्ण

	अगर (rx_ring->sring) अणु
		काष्ठा xen_netअगर_rx_sring *sring = rx_ring->sring;

		seq_म_लिखो(m, "RX: nr_ents %u\n", rx_ring->nr_ents);
		seq_म_लिखो(m, "req prod %u (%d) cons %u (%d) event %u (%d)\n",
			   sring->req_prod,
			   sring->req_prod - sring->rsp_prod,
			   rx_ring->req_cons,
			   rx_ring->req_cons - sring->rsp_prod,
			   sring->req_event,
			   sring->req_event - sring->rsp_prod);
		seq_म_लिखो(m, "rsp prod %u (base) pvt %u (%d) event %u (%d)\n\n",
			   sring->rsp_prod,
			   rx_ring->rsp_prod_pvt,
			   rx_ring->rsp_prod_pvt - sring->rsp_prod,
			   sring->rsp_event,
			   sring->rsp_event - sring->rsp_prod);
	पूर्ण

	seq_म_लिखो(m, "NAPI state: %lx NAPI weight: %d TX queue len %u\n"
		   "Credit timer_pending: %d, credit: %lu, usec: %lu\n"
		   "remaining: %lu, expires: %lu, now: %lu\n",
		   queue->napi.state, queue->napi.weight,
		   skb_queue_len(&queue->tx_queue),
		   समयr_pending(&queue->credit_समयout),
		   queue->credit_bytes,
		   queue->credit_usec,
		   queue->reमुख्यing_credit,
		   queue->credit_समयout.expires,
		   jअगरfies);

	dev_queue = netdev_get_tx_queue(queue->vअगर->dev, queue->id);

	seq_म_लिखो(m, "\nRx internal queue: len %u max %u pkts %u %s\n",
		   queue->rx_queue_len, queue->rx_queue_max,
		   skb_queue_len(&queue->rx_queue),
		   netअगर_tx_queue_stopped(dev_queue) ? "stopped" : "running");

	वापस 0;
पूर्ण

#घोषणा XENVIF_KICK_STR "kick"
#घोषणा BUFFER_SIZE     32

अटल sमाप_प्रकार
xenvअगर_ग_लिखो_io_ring(काष्ठा file *filp, स्थिर अक्षर __user *buf, माप_प्रकार count,
		     loff_t *ppos)
अणु
	काष्ठा xenvअगर_queue *queue =
		((काष्ठा seq_file *)filp->निजी_data)->निजी;
	पूर्णांक len;
	अक्षर ग_लिखो[BUFFER_SIZE];

	/* करोn't allow partial ग_लिखोs and check the length */
	अगर (*ppos != 0)
		वापस 0;
	अगर (count >= माप(ग_लिखो))
		वापस -ENOSPC;

	len = simple_ग_लिखो_to_buffer(ग_लिखो,
				     माप(ग_लिखो) - 1,
				     ppos,
				     buf,
				     count);
	अगर (len < 0)
		वापस len;

	ग_लिखो[len] = '\0';

	अगर (!म_भेदन(ग_लिखो, XENVIF_KICK_STR, माप(XENVIF_KICK_STR) - 1))
		xenvअगर_पूर्णांकerrupt(0, (व्योम *)queue);
	अन्यथा अणु
		pr_warn("Unknown command to io_ring_q%d. Available: kick\n",
			queue->id);
		count = -EINVAL;
	पूर्ण
	वापस count;
पूर्ण

अटल पूर्णांक xenvअगर_io_ring_खोलो(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	पूर्णांक ret;
	व्योम *queue = शून्य;

	अगर (inode->i_निजी)
		queue = inode->i_निजी;
	ret = single_खोलो(filp, xenvअगर_पढ़ो_io_ring, queue);
	filp->f_mode |= FMODE_PWRITE;
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा file_operations xenvअगर_dbg_io_ring_ops_fops = अणु
	.owner = THIS_MODULE,
	.खोलो = xenvअगर_io_ring_खोलो,
	.पढ़ो = seq_पढ़ो,
	.llseek = seq_lseek,
	.release = single_release,
	.ग_लिखो = xenvअगर_ग_लिखो_io_ring,
पूर्ण;

अटल पूर्णांक xenvअगर_ctrl_show(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा xenvअगर *vअगर = m->निजी;

	xenvअगर_dump_hash_info(vअगर, m);

	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(xenvअगर_ctrl);

अटल व्योम xenvअगर_debugfs_addअगर(काष्ठा xenvअगर *vअगर)
अणु
	पूर्णांक i;

	vअगर->xenvअगर_dbg_root = debugfs_create_dir(vअगर->dev->name,
						  xen_netback_dbg_root);
	क्रम (i = 0; i < vअगर->num_queues; ++i) अणु
		अक्षर filename[माप("io_ring_q") + 4];

		snम_लिखो(filename, माप(filename), "io_ring_q%d", i);
		debugfs_create_file(filename, 0600, vअगर->xenvअगर_dbg_root,
				    &vअगर->queues[i],
				    &xenvअगर_dbg_io_ring_ops_fops);
	पूर्ण

	अगर (vअगर->ctrl_irq)
		debugfs_create_file("ctrl", 0400, vअगर->xenvअगर_dbg_root, vअगर,
				    &xenvअगर_ctrl_fops);
पूर्ण

अटल व्योम xenvअगर_debugfs_delअगर(काष्ठा xenvअगर *vअगर)
अणु
	debugfs_हटाओ_recursive(vअगर->xenvअगर_dbg_root);
	vअगर->xenvअगर_dbg_root = शून्य;
पूर्ण
#पूर्ण_अगर /* CONFIG_DEBUG_FS */

/*
 * Handle the creation of the hotplug script environment.  We add the script
 * and vअगर variables to the environment, क्रम the benefit of the vअगर-* hotplug
 * scripts.
 */
अटल पूर्णांक netback_uevent(काष्ठा xenbus_device *xdev,
			  काष्ठा kobj_uevent_env *env)
अणु
	काष्ठा backend_info *be = dev_get_drvdata(&xdev->dev);

	अगर (!be)
		वापस 0;

	अगर (add_uevent_var(env, "script=%s", be->hotplug_script))
		वापस -ENOMEM;

	अगर (!be->vअगर)
		वापस 0;

	वापस add_uevent_var(env, "vif=%s", be->vअगर->dev->name);
पूर्ण


अटल पूर्णांक backend_create_xenvअगर(काष्ठा backend_info *be)
अणु
	पूर्णांक err;
	दीर्घ handle;
	काष्ठा xenbus_device *dev = be->dev;
	काष्ठा xenvअगर *vअगर;

	अगर (be->vअगर != शून्य)
		वापस 0;

	err = xenbus_म_पूछो(XBT_NIL, dev->nodename, "handle", "%li", &handle);
	अगर (err != 1) अणु
		xenbus_dev_fatal(dev, err, "reading handle");
		वापस (err < 0) ? err : -EINVAL;
	पूर्ण

	vअगर = xenvअगर_alloc(&dev->dev, dev->otherend_id, handle);
	अगर (IS_ERR(vअगर)) अणु
		err = PTR_ERR(vअगर);
		xenbus_dev_fatal(dev, err, "creating interface");
		वापस err;
	पूर्ण
	be->vअगर = vअगर;
	vअगर->be = be;

	kobject_uevent(&dev->dev.kobj, KOBJ_ONLINE);
	वापस 0;
पूर्ण

अटल व्योम backend_disconnect(काष्ठा backend_info *be)
अणु
	काष्ठा xenvअगर *vअगर = be->vअगर;

	अगर (vअगर) अणु
		अचिन्हित पूर्णांक num_queues = vअगर->num_queues;
		अचिन्हित पूर्णांक queue_index;

		xen_unरेजिस्टर_watchers(vअगर);
#अगर_घोषित CONFIG_DEBUG_FS
		xenvअगर_debugfs_delअगर(vअगर);
#पूर्ण_अगर /* CONFIG_DEBUG_FS */
		xenvअगर_disconnect_data(vअगर);

		/* At this poपूर्णांक some of the handlers may still be active
		 * so we need to have additional synchronization here.
		 */
		vअगर->num_queues = 0;
		synchronize_net();

		क्रम (queue_index = 0; queue_index < num_queues; ++queue_index)
			xenvअगर_deinit_queue(&vअगर->queues[queue_index]);

		vमुक्त(vअगर->queues);
		vअगर->queues = शून्य;

		xenvअगर_disconnect_ctrl(vअगर);
	पूर्ण
पूर्ण

अटल व्योम backend_connect(काष्ठा backend_info *be)
अणु
	अगर (be->vअगर)
		connect(be);
पूर्ण

अटल अंतरभूत व्योम backend_चयन_state(काष्ठा backend_info *be,
					क्रमागत xenbus_state state)
अणु
	काष्ठा xenbus_device *dev = be->dev;

	pr_debug("%s -> %s\n", dev->nodename, xenbus_strstate(state));
	be->state = state;

	/* If we are रुकोing क्रम a hotplug script then defer the
	 * actual xenbus state change.
	 */
	अगर (!be->have_hotplug_status_watch)
		xenbus_चयन_state(dev, state);
पूर्ण

/* Handle backend state transitions:
 *
 * The backend state starts in Initialising and the following transitions are
 * allowed.
 *
 * Initialising -> InitWait -> Connected
 *          \
 *           \        ^    \         |
 *            \       |     \        |
 *             \      |      \       |
 *              \     |       \      |
 *               \    |        \     |
 *                \   |         \    |
 *                 V  |          V   V
 *
 *                  Closed  <-> Closing
 *
 * The state argument specअगरies the eventual state of the backend and the
 * function transitions to that state via the लघुest path.
 */
अटल व्योम set_backend_state(काष्ठा backend_info *be,
			      क्रमागत xenbus_state state)
अणु
	जबतक (be->state != state) अणु
		चयन (be->state) अणु
		हाल XenbusStateInitialising:
			चयन (state) अणु
			हाल XenbusStateInitWait:
			हाल XenbusStateConnected:
			हाल XenbusStateClosing:
				backend_चयन_state(be, XenbusStateInitWait);
				अवरोध;
			हाल XenbusStateClosed:
				backend_चयन_state(be, XenbusStateClosed);
				अवरोध;
			शेष:
				BUG();
			पूर्ण
			अवरोध;
		हाल XenbusStateClosed:
			चयन (state) अणु
			हाल XenbusStateInitWait:
			हाल XenbusStateConnected:
				backend_चयन_state(be, XenbusStateInitWait);
				अवरोध;
			हाल XenbusStateClosing:
				backend_चयन_state(be, XenbusStateClosing);
				अवरोध;
			शेष:
				BUG();
			पूर्ण
			अवरोध;
		हाल XenbusStateInitWait:
			चयन (state) अणु
			हाल XenbusStateConnected:
				backend_connect(be);
				backend_चयन_state(be, XenbusStateConnected);
				अवरोध;
			हाल XenbusStateClosing:
			हाल XenbusStateClosed:
				backend_चयन_state(be, XenbusStateClosing);
				अवरोध;
			शेष:
				BUG();
			पूर्ण
			अवरोध;
		हाल XenbusStateConnected:
			चयन (state) अणु
			हाल XenbusStateInitWait:
			हाल XenbusStateClosing:
			हाल XenbusStateClosed:
				backend_disconnect(be);
				backend_चयन_state(be, XenbusStateClosing);
				अवरोध;
			शेष:
				BUG();
			पूर्ण
			अवरोध;
		हाल XenbusStateClosing:
			चयन (state) अणु
			हाल XenbusStateInitWait:
			हाल XenbusStateConnected:
			हाल XenbusStateClosed:
				backend_चयन_state(be, XenbusStateClosed);
				अवरोध;
			शेष:
				BUG();
			पूर्ण
			अवरोध;
		शेष:
			BUG();
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम पढ़ो_xenbus_frontend_xdp(काष्ठा backend_info *be,
				      काष्ठा xenbus_device *dev)
अणु
	काष्ठा xenvअगर *vअगर = be->vअगर;
	u16 headroom;
	पूर्णांक err;

	err = xenbus_म_पूछो(XBT_NIL, dev->otherend,
			   "xdp-headroom", "%hu", &headroom);
	अगर (err != 1) अणु
		vअगर->xdp_headroom = 0;
		वापस;
	पूर्ण
	अगर (headroom > XEN_NETIF_MAX_XDP_HEADROOM)
		headroom = XEN_NETIF_MAX_XDP_HEADROOM;
	vअगर->xdp_headroom = headroom;
पूर्ण

/*
 * Callback received when the frontend's state changes.
 */
अटल व्योम frontend_changed(काष्ठा xenbus_device *dev,
			     क्रमागत xenbus_state frontend_state)
अणु
	काष्ठा backend_info *be = dev_get_drvdata(&dev->dev);

	pr_debug("%s -> %s\n", dev->otherend, xenbus_strstate(frontend_state));

	be->frontend_state = frontend_state;

	चयन (frontend_state) अणु
	हाल XenbusStateInitialising:
		set_backend_state(be, XenbusStateInitWait);
		अवरोध;

	हाल XenbusStateInitialised:
		अवरोध;

	हाल XenbusStateConnected:
		set_backend_state(be, XenbusStateConnected);
		अवरोध;

	हाल XenbusStateReconfiguring:
		पढ़ो_xenbus_frontend_xdp(be, dev);
		xenbus_चयन_state(dev, XenbusStateReconfigured);
		अवरोध;

	हाल XenbusStateClosing:
		set_backend_state(be, XenbusStateClosing);
		अवरोध;

	हाल XenbusStateClosed:
		set_backend_state(be, XenbusStateClosed);
		अगर (xenbus_dev_is_online(dev))
			अवरोध;
		fallthrough;	/* अगर not online */
	हाल XenbusStateUnknown:
		set_backend_state(be, XenbusStateClosed);
		device_unरेजिस्टर(&dev->dev);
		अवरोध;

	शेष:
		xenbus_dev_fatal(dev, -EINVAL, "saw state %d at frontend",
				 frontend_state);
		अवरोध;
	पूर्ण
पूर्ण


अटल व्योम xen_net_पढ़ो_rate(काष्ठा xenbus_device *dev,
			      अचिन्हित दीर्घ *bytes, अचिन्हित दीर्घ *usec)
अणु
	अक्षर *s, *e;
	अचिन्हित दीर्घ b, u;
	अक्षर *ratestr;

	/* Default to unlimited bandwidth. */
	*bytes = ~0UL;
	*usec = 0;

	ratestr = xenbus_पढ़ो(XBT_NIL, dev->nodename, "rate", शून्य);
	अगर (IS_ERR(ratestr))
		वापस;

	s = ratestr;
	b = simple_म_से_अदीर्घ(s, &e, 10);
	अगर ((s == e) || (*e != ','))
		जाओ fail;

	s = e + 1;
	u = simple_म_से_अदीर्घ(s, &e, 10);
	अगर ((s == e) || (*e != '\0'))
		जाओ fail;

	*bytes = b;
	*usec = u;

	kमुक्त(ratestr);
	वापस;

 fail:
	pr_warn("Failed to parse network rate limit. Traffic unlimited.\n");
	kमुक्त(ratestr);
पूर्ण

अटल पूर्णांक xen_net_पढ़ो_mac(काष्ठा xenbus_device *dev, u8 mac[])
अणु
	अक्षर *s, *e, *macstr;
	पूर्णांक i;

	macstr = s = xenbus_पढ़ो(XBT_NIL, dev->nodename, "mac", शून्य);
	अगर (IS_ERR(macstr))
		वापस PTR_ERR(macstr);

	क्रम (i = 0; i < ETH_ALEN; i++) अणु
		mac[i] = simple_म_से_अदीर्घ(s, &e, 16);
		अगर ((s == e) || (*e != ((i == ETH_ALEN-1) ? '\0' : ':'))) अणु
			kमुक्त(macstr);
			वापस -ENOENT;
		पूर्ण
		s = e+1;
	पूर्ण

	kमुक्त(macstr);
	वापस 0;
पूर्ण

अटल व्योम xen_net_rate_changed(काष्ठा xenbus_watch *watch,
				 स्थिर अक्षर *path, स्थिर अक्षर *token)
अणु
	काष्ठा xenvअगर *vअगर = container_of(watch, काष्ठा xenvअगर, credit_watch);
	काष्ठा xenbus_device *dev = xenvअगर_to_xenbus_device(vअगर);
	अचिन्हित दीर्घ   credit_bytes;
	अचिन्हित दीर्घ   credit_usec;
	अचिन्हित पूर्णांक queue_index;

	xen_net_पढ़ो_rate(dev, &credit_bytes, &credit_usec);
	क्रम (queue_index = 0; queue_index < vअगर->num_queues; queue_index++) अणु
		काष्ठा xenvअगर_queue *queue = &vअगर->queues[queue_index];

		queue->credit_bytes = credit_bytes;
		queue->credit_usec = credit_usec;
		अगर (!mod_समयr_pending(&queue->credit_समयout, jअगरfies) &&
			queue->reमुख्यing_credit > queue->credit_bytes) अणु
			queue->reमुख्यing_credit = queue->credit_bytes;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक xen_रेजिस्टर_credit_watch(काष्ठा xenbus_device *dev,
				     काष्ठा xenvअगर *vअगर)
अणु
	पूर्णांक err = 0;
	अक्षर *node;
	अचिन्हित maxlen = म_माप(dev->nodename) + माप("/rate");

	अगर (vअगर->credit_watch.node)
		वापस -EADDRINUSE;

	node = kदो_स्मृति(maxlen, GFP_KERNEL);
	अगर (!node)
		वापस -ENOMEM;
	snम_लिखो(node, maxlen, "%s/rate", dev->nodename);
	vअगर->credit_watch.node = node;
	vअगर->credit_watch.will_handle = शून्य;
	vअगर->credit_watch.callback = xen_net_rate_changed;
	err = रेजिस्टर_xenbus_watch(&vअगर->credit_watch);
	अगर (err) अणु
		pr_err("Failed to set watcher %s\n", vअगर->credit_watch.node);
		kमुक्त(node);
		vअगर->credit_watch.node = शून्य;
		vअगर->credit_watch.will_handle = शून्य;
		vअगर->credit_watch.callback = शून्य;
	पूर्ण
	वापस err;
पूर्ण

अटल व्योम xen_unरेजिस्टर_credit_watch(काष्ठा xenvअगर *vअगर)
अणु
	अगर (vअगर->credit_watch.node) अणु
		unरेजिस्टर_xenbus_watch(&vअगर->credit_watch);
		kमुक्त(vअगर->credit_watch.node);
		vअगर->credit_watch.node = शून्य;
	पूर्ण
पूर्ण

अटल व्योम xen_mcast_ctrl_changed(काष्ठा xenbus_watch *watch,
				   स्थिर अक्षर *path, स्थिर अक्षर *token)
अणु
	काष्ठा xenvअगर *vअगर = container_of(watch, काष्ठा xenvअगर,
					  mcast_ctrl_watch);
	काष्ठा xenbus_device *dev = xenvअगर_to_xenbus_device(vअगर);

	vअगर->multicast_control = !!xenbus_पढ़ो_अचिन्हित(dev->otherend,
					"request-multicast-control", 0);
पूर्ण

अटल पूर्णांक xen_रेजिस्टर_mcast_ctrl_watch(काष्ठा xenbus_device *dev,
					 काष्ठा xenvअगर *vअगर)
अणु
	पूर्णांक err = 0;
	अक्षर *node;
	अचिन्हित maxlen = म_माप(dev->otherend) +
		माप("/request-multicast-control");

	अगर (vअगर->mcast_ctrl_watch.node) अणु
		pr_err_ratelimited("Watch is already registered\n");
		वापस -EADDRINUSE;
	पूर्ण

	node = kदो_स्मृति(maxlen, GFP_KERNEL);
	अगर (!node) अणु
		pr_err("Failed to allocate memory for watch\n");
		वापस -ENOMEM;
	पूर्ण
	snम_लिखो(node, maxlen, "%s/request-multicast-control",
		 dev->otherend);
	vअगर->mcast_ctrl_watch.node = node;
	vअगर->mcast_ctrl_watch.will_handle = शून्य;
	vअगर->mcast_ctrl_watch.callback = xen_mcast_ctrl_changed;
	err = रेजिस्टर_xenbus_watch(&vअगर->mcast_ctrl_watch);
	अगर (err) अणु
		pr_err("Failed to set watcher %s\n",
		       vअगर->mcast_ctrl_watch.node);
		kमुक्त(node);
		vअगर->mcast_ctrl_watch.node = शून्य;
		vअगर->mcast_ctrl_watch.will_handle = शून्य;
		vअगर->mcast_ctrl_watch.callback = शून्य;
	पूर्ण
	वापस err;
पूर्ण

अटल व्योम xen_unरेजिस्टर_mcast_ctrl_watch(काष्ठा xenvअगर *vअगर)
अणु
	अगर (vअगर->mcast_ctrl_watch.node) अणु
		unरेजिस्टर_xenbus_watch(&vअगर->mcast_ctrl_watch);
		kमुक्त(vअगर->mcast_ctrl_watch.node);
		vअगर->mcast_ctrl_watch.node = शून्य;
	पूर्ण
पूर्ण

अटल व्योम xen_रेजिस्टर_watchers(काष्ठा xenbus_device *dev,
				  काष्ठा xenvअगर *vअगर)
अणु
	xen_रेजिस्टर_credit_watch(dev, vअगर);
	xen_रेजिस्टर_mcast_ctrl_watch(dev, vअगर);
पूर्ण

अटल व्योम xen_unरेजिस्टर_watchers(काष्ठा xenvअगर *vअगर)
अणु
	xen_unरेजिस्टर_mcast_ctrl_watch(vअगर);
	xen_unरेजिस्टर_credit_watch(vअगर);
पूर्ण

अटल व्योम unरेजिस्टर_hotplug_status_watch(काष्ठा backend_info *be)
अणु
	अगर (be->have_hotplug_status_watch) अणु
		unरेजिस्टर_xenbus_watch(&be->hotplug_status_watch);
		kमुक्त(be->hotplug_status_watch.node);
	पूर्ण
	be->have_hotplug_status_watch = 0;
पूर्ण

अटल व्योम hotplug_status_changed(काष्ठा xenbus_watch *watch,
				   स्थिर अक्षर *path,
				   स्थिर अक्षर *token)
अणु
	काष्ठा backend_info *be = container_of(watch,
					       काष्ठा backend_info,
					       hotplug_status_watch);
	अक्षर *str;
	अचिन्हित पूर्णांक len;

	str = xenbus_पढ़ो(XBT_NIL, be->dev->nodename, "hotplug-status", &len);
	अगर (IS_ERR(str))
		वापस;
	अगर (len == माप("connected")-1 && !स_भेद(str, "connected", len)) अणु
		/* Complete any pending state change */
		xenbus_चयन_state(be->dev, be->state);

		/* Not पूर्णांकerested in this watch anymore. */
		unरेजिस्टर_hotplug_status_watch(be);
		xenbus_rm(XBT_NIL, be->dev->nodename, "hotplug-status");
	पूर्ण
	kमुक्त(str);
पूर्ण

अटल पूर्णांक connect_ctrl_ring(काष्ठा backend_info *be)
अणु
	काष्ठा xenbus_device *dev = be->dev;
	काष्ठा xenvअगर *vअगर = be->vअगर;
	अचिन्हित पूर्णांक val;
	grant_ref_t ring_ref;
	अचिन्हित पूर्णांक evtchn;
	पूर्णांक err;

	err = xenbus_म_पूछो(XBT_NIL, dev->otherend,
			   "ctrl-ring-ref", "%u", &val);
	अगर (err < 0)
		जाओ करोne; /* The frontend करोes not have a control ring */

	ring_ref = val;

	err = xenbus_म_पूछो(XBT_NIL, dev->otherend,
			   "event-channel-ctrl", "%u", &val);
	अगर (err < 0) अणु
		xenbus_dev_fatal(dev, err,
				 "reading %s/event-channel-ctrl",
				 dev->otherend);
		जाओ fail;
	पूर्ण

	evtchn = val;

	err = xenvअगर_connect_ctrl(vअगर, ring_ref, evtchn);
	अगर (err) अणु
		xenbus_dev_fatal(dev, err,
				 "mapping shared-frame %u port %u",
				 ring_ref, evtchn);
		जाओ fail;
	पूर्ण

करोne:
	वापस 0;

fail:
	वापस err;
पूर्ण

अटल व्योम connect(काष्ठा backend_info *be)
अणु
	पूर्णांक err;
	काष्ठा xenbus_device *dev = be->dev;
	अचिन्हित दीर्घ credit_bytes, credit_usec;
	अचिन्हित पूर्णांक queue_index;
	अचिन्हित पूर्णांक requested_num_queues;
	काष्ठा xenvअगर_queue *queue;

	/* Check whether the frontend requested multiple queues
	 * and पढ़ो the number requested.
	 */
	requested_num_queues = xenbus_पढ़ो_अचिन्हित(dev->otherend,
					"multi-queue-num-queues", 1);
	अगर (requested_num_queues > xenvअगर_max_queues) अणु
		/* buggy or malicious guest */
		xenbus_dev_fatal(dev, -EINVAL,
				 "guest requested %u queues, exceeding the maximum of %u.",
				 requested_num_queues, xenvअगर_max_queues);
		वापस;
	पूर्ण

	err = xen_net_पढ़ो_mac(dev, be->vअगर->fe_dev_addr);
	अगर (err) अणु
		xenbus_dev_fatal(dev, err, "parsing %s/mac", dev->nodename);
		वापस;
	पूर्ण

	xen_net_पढ़ो_rate(dev, &credit_bytes, &credit_usec);
	xen_unरेजिस्टर_watchers(be->vअगर);
	xen_रेजिस्टर_watchers(dev, be->vअगर);
	पढ़ो_xenbus_vअगर_flags(be);

	err = connect_ctrl_ring(be);
	अगर (err) अणु
		xenbus_dev_fatal(dev, err, "connecting control ring");
		वापस;
	पूर्ण

	/* Use the number of queues requested by the frontend */
	be->vअगर->queues = vzalloc(array_size(requested_num_queues,
					     माप(काष्ठा xenvअगर_queue)));
	अगर (!be->vअगर->queues) अणु
		xenbus_dev_fatal(dev, -ENOMEM,
				 "allocating queues");
		वापस;
	पूर्ण

	be->vअगर->num_queues = requested_num_queues;
	be->vअगर->stalled_queues = requested_num_queues;

	क्रम (queue_index = 0; queue_index < requested_num_queues; ++queue_index) अणु
		queue = &be->vअगर->queues[queue_index];
		queue->vअगर = be->vअगर;
		queue->id = queue_index;
		snम_लिखो(queue->name, माप(queue->name), "%s-q%u",
				be->vअगर->dev->name, queue->id);

		err = xenvअगर_init_queue(queue);
		अगर (err) अणु
			/* xenvअगर_init_queue() cleans up after itself on
			 * failure, but we need to clean up any previously
			 * initialised queues. Set num_queues to i so that
			 * earlier queues can be destroyed using the regular
			 * disconnect logic.
			 */
			be->vअगर->num_queues = queue_index;
			जाओ err;
		पूर्ण

		queue->credit_bytes = credit_bytes;
		queue->reमुख्यing_credit = credit_bytes;
		queue->credit_usec = credit_usec;

		err = connect_data_rings(be, queue);
		अगर (err) अणु
			/* connect_data_rings() cleans up after itself on
			 * failure, but we need to clean up after
			 * xenvअगर_init_queue() here, and also clean up any
			 * previously initialised queues.
			 */
			xenvअगर_deinit_queue(queue);
			be->vअगर->num_queues = queue_index;
			जाओ err;
		पूर्ण
	पूर्ण

#अगर_घोषित CONFIG_DEBUG_FS
	xenvअगर_debugfs_addअगर(be->vअगर);
#पूर्ण_अगर /* CONFIG_DEBUG_FS */

	/* Initialisation completed, tell core driver the number of
	 * active queues.
	 */
	rtnl_lock();
	netअगर_set_real_num_tx_queues(be->vअगर->dev, requested_num_queues);
	netअगर_set_real_num_rx_queues(be->vअगर->dev, requested_num_queues);
	rtnl_unlock();

	xenvअगर_carrier_on(be->vअगर);

	unरेजिस्टर_hotplug_status_watch(be);
	अगर (xenbus_exists(XBT_NIL, dev->nodename, "hotplug-status")) अणु
		err = xenbus_watch_pathfmt(dev, &be->hotplug_status_watch,
					   शून्य, hotplug_status_changed,
					   "%s/%s", dev->nodename,
					   "hotplug-status");
		अगर (err)
			जाओ err;
		be->have_hotplug_status_watch = 1;
	पूर्ण

	netअगर_tx_wake_all_queues(be->vअगर->dev);

	वापस;

err:
	अगर (be->vअगर->num_queues > 0)
		xenvअगर_disconnect_data(be->vअगर); /* Clean up existing queues */
	क्रम (queue_index = 0; queue_index < be->vअगर->num_queues; ++queue_index)
		xenvअगर_deinit_queue(&be->vअगर->queues[queue_index]);
	vमुक्त(be->vअगर->queues);
	be->vअगर->queues = शून्य;
	be->vअगर->num_queues = 0;
	xenvअगर_disconnect_ctrl(be->vअगर);
	वापस;
पूर्ण


अटल पूर्णांक connect_data_rings(काष्ठा backend_info *be,
			      काष्ठा xenvअगर_queue *queue)
अणु
	काष्ठा xenbus_device *dev = be->dev;
	अचिन्हित पूर्णांक num_queues = queue->vअगर->num_queues;
	अचिन्हित दीर्घ tx_ring_ref, rx_ring_ref;
	अचिन्हित पूर्णांक tx_evtchn, rx_evtchn;
	पूर्णांक err;
	अक्षर *xspath;
	माप_प्रकार xspathsize;
	स्थिर माप_प्रकार xenstore_path_ext_size = 11; /* sufficient क्रम "/queue-NNN" */

	/* If the frontend requested 1 queue, or we have fallen back
	 * to single queue due to lack of frontend support क्रम multi-
	 * queue, expect the reमुख्यing XenStore keys in the toplevel
	 * directory. Otherwise, expect them in a subdirectory called
	 * queue-N.
	 */
	अगर (num_queues == 1) अणु
		xspath = kzalloc(म_माप(dev->otherend) + 1, GFP_KERNEL);
		अगर (!xspath) अणु
			xenbus_dev_fatal(dev, -ENOMEM,
					 "reading ring references");
			वापस -ENOMEM;
		पूर्ण
		म_नकल(xspath, dev->otherend);
	पूर्ण अन्यथा अणु
		xspathsize = म_माप(dev->otherend) + xenstore_path_ext_size;
		xspath = kzalloc(xspathsize, GFP_KERNEL);
		अगर (!xspath) अणु
			xenbus_dev_fatal(dev, -ENOMEM,
					 "reading ring references");
			वापस -ENOMEM;
		पूर्ण
		snम_लिखो(xspath, xspathsize, "%s/queue-%u", dev->otherend,
			 queue->id);
	पूर्ण

	err = xenbus_gather(XBT_NIL, xspath,
			    "tx-ring-ref", "%lu", &tx_ring_ref,
			    "rx-ring-ref", "%lu", &rx_ring_ref, शून्य);
	अगर (err) अणु
		xenbus_dev_fatal(dev, err,
				 "reading %s/ring-ref",
				 xspath);
		जाओ err;
	पूर्ण

	/* Try split event channels first, then single event channel. */
	err = xenbus_gather(XBT_NIL, xspath,
			    "event-channel-tx", "%u", &tx_evtchn,
			    "event-channel-rx", "%u", &rx_evtchn, शून्य);
	अगर (err < 0) अणु
		err = xenbus_म_पूछो(XBT_NIL, xspath,
				   "event-channel", "%u", &tx_evtchn);
		अगर (err < 0) अणु
			xenbus_dev_fatal(dev, err,
					 "reading %s/event-channel(-tx/rx)",
					 xspath);
			जाओ err;
		पूर्ण
		rx_evtchn = tx_evtchn;
	पूर्ण

	/* Map the shared frame, irq etc. */
	err = xenvअगर_connect_data(queue, tx_ring_ref, rx_ring_ref,
				  tx_evtchn, rx_evtchn);
	अगर (err) अणु
		xenbus_dev_fatal(dev, err,
				 "mapping shared-frames %lu/%lu port tx %u rx %u",
				 tx_ring_ref, rx_ring_ref,
				 tx_evtchn, rx_evtchn);
		जाओ err;
	पूर्ण

	err = 0;
err: /* Regular वापस falls through with err == 0 */
	kमुक्त(xspath);
	वापस err;
पूर्ण

अटल पूर्णांक पढ़ो_xenbus_vअगर_flags(काष्ठा backend_info *be)
अणु
	काष्ठा xenvअगर *vअगर = be->vअगर;
	काष्ठा xenbus_device *dev = be->dev;
	अचिन्हित पूर्णांक rx_copy;
	पूर्णांक err;

	err = xenbus_म_पूछो(XBT_NIL, dev->otherend, "request-rx-copy", "%u",
			   &rx_copy);
	अगर (err == -ENOENT) अणु
		err = 0;
		rx_copy = 0;
	पूर्ण
	अगर (err < 0) अणु
		xenbus_dev_fatal(dev, err, "reading %s/request-rx-copy",
				 dev->otherend);
		वापस err;
	पूर्ण
	अगर (!rx_copy)
		वापस -EOPNOTSUPP;

	अगर (!xenbus_पढ़ो_अचिन्हित(dev->otherend, "feature-rx-notify", 0)) अणु
		/* - Reduce drain समयout to poll more frequently क्रम
		 *   Rx requests.
		 * - Disable Rx stall detection.
		 */
		be->vअगर->drain_समयout = msecs_to_jअगरfies(30);
		be->vअगर->stall_समयout = 0;
	पूर्ण

	vअगर->can_sg = !!xenbus_पढ़ो_अचिन्हित(dev->otherend, "feature-sg", 0);

	vअगर->gso_mask = 0;

	अगर (xenbus_पढ़ो_अचिन्हित(dev->otherend, "feature-gso-tcpv4", 0))
		vअगर->gso_mask |= GSO_BIT(TCPV4);

	अगर (xenbus_पढ़ो_अचिन्हित(dev->otherend, "feature-gso-tcpv6", 0))
		vअगर->gso_mask |= GSO_BIT(TCPV6);

	vअगर->ip_csum = !xenbus_पढ़ो_अचिन्हित(dev->otherend,
					     "feature-no-csum-offload", 0);

	vअगर->ipv6_csum = !!xenbus_पढ़ो_अचिन्हित(dev->otherend,
						"feature-ipv6-csum-offload", 0);

	पढ़ो_xenbus_frontend_xdp(be, dev);

	वापस 0;
पूर्ण

अटल पूर्णांक netback_हटाओ(काष्ठा xenbus_device *dev)
अणु
	काष्ठा backend_info *be = dev_get_drvdata(&dev->dev);

	unरेजिस्टर_hotplug_status_watch(be);
	अगर (be->vअगर) अणु
		kobject_uevent(&dev->dev.kobj, KOBJ_OFFLINE);
		backend_disconnect(be);
		xenvअगर_मुक्त(be->vअगर);
		be->vअगर = शून्य;
	पूर्ण
	kमुक्त(be->hotplug_script);
	kमुक्त(be);
	dev_set_drvdata(&dev->dev, शून्य);
	वापस 0;
पूर्ण

/*
 * Entry poपूर्णांक to this code when a new device is created.  Allocate the basic
 * काष्ठाures and चयन to InitWait.
 */
अटल पूर्णांक netback_probe(काष्ठा xenbus_device *dev,
			 स्थिर काष्ठा xenbus_device_id *id)
अणु
	स्थिर अक्षर *message;
	काष्ठा xenbus_transaction xbt;
	पूर्णांक err;
	पूर्णांक sg;
	स्थिर अक्षर *script;
	काष्ठा backend_info *be = kzalloc(माप(*be), GFP_KERNEL);

	अगर (!be) अणु
		xenbus_dev_fatal(dev, -ENOMEM,
				 "allocating backend structure");
		वापस -ENOMEM;
	पूर्ण

	be->dev = dev;
	dev_set_drvdata(&dev->dev, be);

	sg = 1;

	करो अणु
		err = xenbus_transaction_start(&xbt);
		अगर (err) अणु
			xenbus_dev_fatal(dev, err, "starting transaction");
			जाओ fail;
		पूर्ण

		err = xenbus_म_लिखो(xbt, dev->nodename, "feature-sg", "%d", sg);
		अगर (err) अणु
			message = "writing feature-sg";
			जाओ पात_transaction;
		पूर्ण

		err = xenbus_म_लिखो(xbt, dev->nodename, "feature-gso-tcpv4",
				    "%d", sg);
		अगर (err) अणु
			message = "writing feature-gso-tcpv4";
			जाओ पात_transaction;
		पूर्ण

		err = xenbus_म_लिखो(xbt, dev->nodename, "feature-gso-tcpv6",
				    "%d", sg);
		अगर (err) अणु
			message = "writing feature-gso-tcpv6";
			जाओ पात_transaction;
		पूर्ण

		/* We support partial checksum setup क्रम IPv6 packets */
		err = xenbus_म_लिखो(xbt, dev->nodename,
				    "feature-ipv6-csum-offload",
				    "%d", 1);
		अगर (err) अणु
			message = "writing feature-ipv6-csum-offload";
			जाओ पात_transaction;
		पूर्ण

		/* We support rx-copy path. */
		err = xenbus_म_लिखो(xbt, dev->nodename,
				    "feature-rx-copy", "%d", 1);
		अगर (err) अणु
			message = "writing feature-rx-copy";
			जाओ पात_transaction;
		पूर्ण

		/* we can adjust a headroom क्रम netfront XDP processing */
		err = xenbus_म_लिखो(xbt, dev->nodename,
				    "feature-xdp-headroom", "%d",
				    provides_xdp_headroom);
		अगर (err) अणु
			message = "writing feature-xdp-headroom";
			जाओ पात_transaction;
		पूर्ण

		/* We करोn't support rx-flip path (except old guests who
		 * करोn't grok this feature flag).
		 */
		err = xenbus_म_लिखो(xbt, dev->nodename,
				    "feature-rx-flip", "%d", 0);
		अगर (err) अणु
			message = "writing feature-rx-flip";
			जाओ पात_transaction;
		पूर्ण

		/* We support dynamic multicast-control. */
		err = xenbus_म_लिखो(xbt, dev->nodename,
				    "feature-multicast-control", "%d", 1);
		अगर (err) अणु
			message = "writing feature-multicast-control";
			जाओ पात_transaction;
		पूर्ण

		err = xenbus_म_लिखो(xbt, dev->nodename,
				    "feature-dynamic-multicast-control",
				    "%d", 1);
		अगर (err) अणु
			message = "writing feature-dynamic-multicast-control";
			जाओ पात_transaction;
		पूर्ण

		err = xenbus_transaction_end(xbt, 0);
	पूर्ण जबतक (err == -EAGAIN);

	अगर (err) अणु
		xenbus_dev_fatal(dev, err, "completing transaction");
		जाओ fail;
	पूर्ण

	/* Split event channels support, this is optional so it is not
	 * put inside the above loop.
	 */
	err = xenbus_म_लिखो(XBT_NIL, dev->nodename,
			    "feature-split-event-channels",
			    "%u", separate_tx_rx_irq);
	अगर (err)
		pr_debug("Error writing feature-split-event-channels\n");

	/* Multi-queue support: This is an optional feature. */
	err = xenbus_म_लिखो(XBT_NIL, dev->nodename,
			    "multi-queue-max-queues", "%u", xenvअगर_max_queues);
	अगर (err)
		pr_debug("Error writing multi-queue-max-queues\n");

	err = xenbus_म_लिखो(XBT_NIL, dev->nodename,
			    "feature-ctrl-ring",
			    "%u", true);
	अगर (err)
		pr_debug("Error writing feature-ctrl-ring\n");

	backend_चयन_state(be, XenbusStateInitWait);

	script = xenbus_पढ़ो(XBT_NIL, dev->nodename, "script", शून्य);
	अगर (IS_ERR(script)) अणु
		err = PTR_ERR(script);
		xenbus_dev_fatal(dev, err, "reading script");
		जाओ fail;
	पूर्ण

	be->hotplug_script = script;

	/* This kicks hotplug scripts, so करो it immediately. */
	err = backend_create_xenvअगर(be);
	अगर (err)
		जाओ fail;

	वापस 0;

पात_transaction:
	xenbus_transaction_end(xbt, 1);
	xenbus_dev_fatal(dev, err, "%s", message);
fail:
	pr_debug("failed\n");
	netback_हटाओ(dev);
	वापस err;
पूर्ण

अटल स्थिर काष्ठा xenbus_device_id netback_ids[] = अणु
	अणु "vif" पूर्ण,
	अणु "" पूर्ण
पूर्ण;

अटल काष्ठा xenbus_driver netback_driver = अणु
	.ids = netback_ids,
	.probe = netback_probe,
	.हटाओ = netback_हटाओ,
	.uevent = netback_uevent,
	.otherend_changed = frontend_changed,
	.allow_rebind = true,
पूर्ण;

पूर्णांक xenvअगर_xenbus_init(व्योम)
अणु
	वापस xenbus_रेजिस्टर_backend(&netback_driver);
पूर्ण

व्योम xenvअगर_xenbus_fini(व्योम)
अणु
	वापस xenbus_unरेजिस्टर_driver(&netback_driver);
पूर्ण
