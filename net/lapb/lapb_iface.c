<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *	LAPB release 002
 *
 *	This code REQUIRES 2.1.15 or higher/ NET3.038
 *
 *	History
 *	LAPB 001	Jonathan Naylor	Started Coding
 *	LAPB 002	Jonathan Naylor	New समयr architecture.
 *	2000-10-29	Henner Eisen	lapb_data_indication() वापस status.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/types.h>
#समावेश <linux/socket.h>
#समावेश <linux/in.h>
#समावेश <linux/kernel.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/समयr.h>
#समावेश <linux/माला.स>
#समावेश <linux/sockios.h>
#समावेश <linux/net.h>
#समावेश <linux/inet.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/slab.h>
#समावेश <net/sock.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/fcntl.h>
#समावेश <linux/mm.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/स्थिति.स>
#समावेश <linux/init.h>
#समावेश <net/lapb.h>

अटल LIST_HEAD(lapb_list);
अटल DEFINE_RWLOCK(lapb_list_lock);

/*
 *	Free an allocated lapb control block.
 */
अटल व्योम lapb_मुक्त_cb(काष्ठा lapb_cb *lapb)
अणु
	kमुक्त(lapb);
पूर्ण

अटल __अंतरभूत__ व्योम lapb_hold(काष्ठा lapb_cb *lapb)
अणु
	refcount_inc(&lapb->refcnt);
पूर्ण

अटल __अंतरभूत__ व्योम lapb_put(काष्ठा lapb_cb *lapb)
अणु
	अगर (refcount_dec_and_test(&lapb->refcnt))
		lapb_मुक्त_cb(lapb);
पूर्ण

/*
 *	Socket removal during an पूर्णांकerrupt is now safe.
 */
अटल व्योम __lapb_हटाओ_cb(काष्ठा lapb_cb *lapb)
अणु
	अगर (lapb->node.next) अणु
		list_del(&lapb->node);
		lapb_put(lapb);
	पूर्ण
पूर्ण

/*
 *	Add a socket to the bound sockets list.
 */
अटल व्योम __lapb_insert_cb(काष्ठा lapb_cb *lapb)
अणु
	list_add(&lapb->node, &lapb_list);
	lapb_hold(lapb);
पूर्ण

अटल काष्ठा lapb_cb *__lapb_devtoकाष्ठा(काष्ठा net_device *dev)
अणु
	काष्ठा list_head *entry;
	काष्ठा lapb_cb *lapb, *use = शून्य;

	list_क्रम_each(entry, &lapb_list) अणु
		lapb = list_entry(entry, काष्ठा lapb_cb, node);
		अगर (lapb->dev == dev) अणु
			use = lapb;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (use)
		lapb_hold(use);

	वापस use;
पूर्ण

अटल काष्ठा lapb_cb *lapb_devtoकाष्ठा(काष्ठा net_device *dev)
अणु
	काष्ठा lapb_cb *rc;

	पढ़ो_lock_bh(&lapb_list_lock);
	rc = __lapb_devtoकाष्ठा(dev);
	पढ़ो_unlock_bh(&lapb_list_lock);

	वापस rc;
पूर्ण
/*
 *	Create an empty LAPB control block.
 */
अटल काष्ठा lapb_cb *lapb_create_cb(व्योम)
अणु
	काष्ठा lapb_cb *lapb = kzalloc(माप(*lapb), GFP_ATOMIC);

	अगर (!lapb)
		जाओ out;

	skb_queue_head_init(&lapb->ग_लिखो_queue);
	skb_queue_head_init(&lapb->ack_queue);

	समयr_setup(&lapb->t1समयr, शून्य, 0);
	समयr_setup(&lapb->t2समयr, शून्य, 0);
	lapb->t1समयr_running = false;
	lapb->t2समयr_running = false;

	lapb->t1      = LAPB_DEFAULT_T1;
	lapb->t2      = LAPB_DEFAULT_T2;
	lapb->n2      = LAPB_DEFAULT_N2;
	lapb->mode    = LAPB_DEFAULT_MODE;
	lapb->winकरोw  = LAPB_DEFAULT_WINDOW;
	lapb->state   = LAPB_STATE_0;

	spin_lock_init(&lapb->lock);
	refcount_set(&lapb->refcnt, 1);
out:
	वापस lapb;
पूर्ण

पूर्णांक lapb_रेजिस्टर(काष्ठा net_device *dev,
		  स्थिर काष्ठा lapb_रेजिस्टर_काष्ठा *callbacks)
अणु
	काष्ठा lapb_cb *lapb;
	पूर्णांक rc = LAPB_BADTOKEN;

	ग_लिखो_lock_bh(&lapb_list_lock);

	lapb = __lapb_devtoकाष्ठा(dev);
	अगर (lapb) अणु
		lapb_put(lapb);
		जाओ out;
	पूर्ण

	lapb = lapb_create_cb();
	rc = LAPB_NOMEM;
	अगर (!lapb)
		जाओ out;

	lapb->dev       = dev;
	lapb->callbacks = callbacks;

	__lapb_insert_cb(lapb);

	lapb_start_t1समयr(lapb);

	rc = LAPB_OK;
out:
	ग_लिखो_unlock_bh(&lapb_list_lock);
	वापस rc;
पूर्ण
EXPORT_SYMBOL(lapb_रेजिस्टर);

पूर्णांक lapb_unरेजिस्टर(काष्ठा net_device *dev)
अणु
	काष्ठा lapb_cb *lapb;
	पूर्णांक rc = LAPB_BADTOKEN;

	ग_लिखो_lock_bh(&lapb_list_lock);
	lapb = __lapb_devtoकाष्ठा(dev);
	अगर (!lapb)
		जाओ out;
	lapb_put(lapb);

	/* Wait क्रम other refs to "lapb" to drop */
	जबतक (refcount_पढ़ो(&lapb->refcnt) > 2)
		usleep_range(1, 10);

	spin_lock_bh(&lapb->lock);

	lapb_stop_t1समयr(lapb);
	lapb_stop_t2समयr(lapb);

	lapb_clear_queues(lapb);

	spin_unlock_bh(&lapb->lock);

	/* Wait क्रम running समयrs to stop */
	del_समयr_sync(&lapb->t1समयr);
	del_समयr_sync(&lapb->t2समयr);

	__lapb_हटाओ_cb(lapb);

	lapb_put(lapb);
	rc = LAPB_OK;
out:
	ग_लिखो_unlock_bh(&lapb_list_lock);
	वापस rc;
पूर्ण
EXPORT_SYMBOL(lapb_unरेजिस्टर);

पूर्णांक lapb_getparms(काष्ठा net_device *dev, काष्ठा lapb_parms_काष्ठा *parms)
अणु
	पूर्णांक rc = LAPB_BADTOKEN;
	काष्ठा lapb_cb *lapb = lapb_devtoकाष्ठा(dev);

	अगर (!lapb)
		जाओ out;

	spin_lock_bh(&lapb->lock);

	parms->t1      = lapb->t1 / HZ;
	parms->t2      = lapb->t2 / HZ;
	parms->n2      = lapb->n2;
	parms->n2count = lapb->n2count;
	parms->state   = lapb->state;
	parms->winकरोw  = lapb->winकरोw;
	parms->mode    = lapb->mode;

	अगर (!समयr_pending(&lapb->t1समयr))
		parms->t1समयr = 0;
	अन्यथा
		parms->t1समयr = (lapb->t1समयr.expires - jअगरfies) / HZ;

	अगर (!समयr_pending(&lapb->t2समयr))
		parms->t2समयr = 0;
	अन्यथा
		parms->t2समयr = (lapb->t2समयr.expires - jअगरfies) / HZ;

	spin_unlock_bh(&lapb->lock);
	lapb_put(lapb);
	rc = LAPB_OK;
out:
	वापस rc;
पूर्ण
EXPORT_SYMBOL(lapb_getparms);

पूर्णांक lapb_setparms(काष्ठा net_device *dev, काष्ठा lapb_parms_काष्ठा *parms)
अणु
	पूर्णांक rc = LAPB_BADTOKEN;
	काष्ठा lapb_cb *lapb = lapb_devtoकाष्ठा(dev);

	अगर (!lapb)
		जाओ out;

	spin_lock_bh(&lapb->lock);

	rc = LAPB_INVALUE;
	अगर (parms->t1 < 1 || parms->t2 < 1 || parms->n2 < 1)
		जाओ out_put;

	अगर (lapb->state == LAPB_STATE_0) अणु
		अगर (parms->mode & LAPB_EXTENDED) अणु
			अगर (parms->winकरोw < 1 || parms->winकरोw > 127)
				जाओ out_put;
		पूर्ण अन्यथा अणु
			अगर (parms->winकरोw < 1 || parms->winकरोw > 7)
				जाओ out_put;
		पूर्ण
		lapb->mode    = parms->mode;
		lapb->winकरोw  = parms->winकरोw;
	पूर्ण

	lapb->t1    = parms->t1 * HZ;
	lapb->t2    = parms->t2 * HZ;
	lapb->n2    = parms->n2;

	rc = LAPB_OK;
out_put:
	spin_unlock_bh(&lapb->lock);
	lapb_put(lapb);
out:
	वापस rc;
पूर्ण
EXPORT_SYMBOL(lapb_setparms);

पूर्णांक lapb_connect_request(काष्ठा net_device *dev)
अणु
	काष्ठा lapb_cb *lapb = lapb_devtoकाष्ठा(dev);
	पूर्णांक rc = LAPB_BADTOKEN;

	अगर (!lapb)
		जाओ out;

	spin_lock_bh(&lapb->lock);

	rc = LAPB_OK;
	अगर (lapb->state == LAPB_STATE_1)
		जाओ out_put;

	rc = LAPB_CONNECTED;
	अगर (lapb->state == LAPB_STATE_3 || lapb->state == LAPB_STATE_4)
		जाओ out_put;

	lapb_establish_data_link(lapb);

	lapb_dbg(0, "(%p) S0 -> S1\n", lapb->dev);
	lapb->state = LAPB_STATE_1;

	rc = LAPB_OK;
out_put:
	spin_unlock_bh(&lapb->lock);
	lapb_put(lapb);
out:
	वापस rc;
पूर्ण
EXPORT_SYMBOL(lapb_connect_request);

अटल पूर्णांक __lapb_disconnect_request(काष्ठा lapb_cb *lapb)
अणु
	चयन (lapb->state) अणु
	हाल LAPB_STATE_0:
		वापस LAPB_NOTCONNECTED;

	हाल LAPB_STATE_1:
		lapb_dbg(1, "(%p) S1 TX DISC(1)\n", lapb->dev);
		lapb_dbg(0, "(%p) S1 -> S0\n", lapb->dev);
		lapb_send_control(lapb, LAPB_DISC, LAPB_POLLON, LAPB_COMMAND);
		lapb->state = LAPB_STATE_0;
		lapb_start_t1समयr(lapb);
		वापस LAPB_NOTCONNECTED;

	हाल LAPB_STATE_2:
		वापस LAPB_OK;
	पूर्ण

	lapb_clear_queues(lapb);
	lapb->n2count = 0;
	lapb_send_control(lapb, LAPB_DISC, LAPB_POLLON, LAPB_COMMAND);
	lapb_start_t1समयr(lapb);
	lapb_stop_t2समयr(lapb);
	lapb->state = LAPB_STATE_2;

	lapb_dbg(1, "(%p) S3 DISC(1)\n", lapb->dev);
	lapb_dbg(0, "(%p) S3 -> S2\n", lapb->dev);

	वापस LAPB_OK;
पूर्ण

पूर्णांक lapb_disconnect_request(काष्ठा net_device *dev)
अणु
	काष्ठा lapb_cb *lapb = lapb_devtoकाष्ठा(dev);
	पूर्णांक rc = LAPB_BADTOKEN;

	अगर (!lapb)
		जाओ out;

	spin_lock_bh(&lapb->lock);

	rc = __lapb_disconnect_request(lapb);

	spin_unlock_bh(&lapb->lock);
	lapb_put(lapb);
out:
	वापस rc;
पूर्ण
EXPORT_SYMBOL(lapb_disconnect_request);

पूर्णांक lapb_data_request(काष्ठा net_device *dev, काष्ठा sk_buff *skb)
अणु
	काष्ठा lapb_cb *lapb = lapb_devtoकाष्ठा(dev);
	पूर्णांक rc = LAPB_BADTOKEN;

	अगर (!lapb)
		जाओ out;

	spin_lock_bh(&lapb->lock);

	rc = LAPB_NOTCONNECTED;
	अगर (lapb->state != LAPB_STATE_3 && lapb->state != LAPB_STATE_4)
		जाओ out_put;

	skb_queue_tail(&lapb->ग_लिखो_queue, skb);
	lapb_kick(lapb);
	rc = LAPB_OK;
out_put:
	spin_unlock_bh(&lapb->lock);
	lapb_put(lapb);
out:
	वापस rc;
पूर्ण
EXPORT_SYMBOL(lapb_data_request);

पूर्णांक lapb_data_received(काष्ठा net_device *dev, काष्ठा sk_buff *skb)
अणु
	काष्ठा lapb_cb *lapb = lapb_devtoकाष्ठा(dev);
	पूर्णांक rc = LAPB_BADTOKEN;

	अगर (lapb) अणु
		spin_lock_bh(&lapb->lock);
		lapb_data_input(lapb, skb);
		spin_unlock_bh(&lapb->lock);
		lapb_put(lapb);
		rc = LAPB_OK;
	पूर्ण

	वापस rc;
पूर्ण
EXPORT_SYMBOL(lapb_data_received);

व्योम lapb_connect_confirmation(काष्ठा lapb_cb *lapb, पूर्णांक reason)
अणु
	अगर (lapb->callbacks->connect_confirmation)
		lapb->callbacks->connect_confirmation(lapb->dev, reason);
पूर्ण

व्योम lapb_connect_indication(काष्ठा lapb_cb *lapb, पूर्णांक reason)
अणु
	अगर (lapb->callbacks->connect_indication)
		lapb->callbacks->connect_indication(lapb->dev, reason);
पूर्ण

व्योम lapb_disconnect_confirmation(काष्ठा lapb_cb *lapb, पूर्णांक reason)
अणु
	अगर (lapb->callbacks->disconnect_confirmation)
		lapb->callbacks->disconnect_confirmation(lapb->dev, reason);
पूर्ण

व्योम lapb_disconnect_indication(काष्ठा lapb_cb *lapb, पूर्णांक reason)
अणु
	अगर (lapb->callbacks->disconnect_indication)
		lapb->callbacks->disconnect_indication(lapb->dev, reason);
पूर्ण

पूर्णांक lapb_data_indication(काष्ठा lapb_cb *lapb, काष्ठा sk_buff *skb)
अणु
	अगर (lapb->callbacks->data_indication)
		वापस lapb->callbacks->data_indication(lapb->dev, skb);

	kमुक्त_skb(skb);
	वापस NET_RX_SUCCESS; /* For now; must be != NET_RX_DROP */
पूर्ण

पूर्णांक lapb_data_transmit(काष्ठा lapb_cb *lapb, काष्ठा sk_buff *skb)
अणु
	पूर्णांक used = 0;

	अगर (lapb->callbacks->data_transmit) अणु
		lapb->callbacks->data_transmit(lapb->dev, skb);
		used = 1;
	पूर्ण

	वापस used;
पूर्ण

/* Handle device status changes. */
अटल पूर्णांक lapb_device_event(काष्ठा notअगरier_block *this, अचिन्हित दीर्घ event,
			     व्योम *ptr)
अणु
	काष्ठा net_device *dev = netdev_notअगरier_info_to_dev(ptr);
	काष्ठा lapb_cb *lapb;

	अगर (!net_eq(dev_net(dev), &init_net))
		वापस NOTIFY_DONE;

	अगर (dev->type != ARPHRD_X25)
		वापस NOTIFY_DONE;

	lapb = lapb_devtoकाष्ठा(dev);
	अगर (!lapb)
		वापस NOTIFY_DONE;

	spin_lock_bh(&lapb->lock);

	चयन (event) अणु
	हाल NETDEV_UP:
		lapb_dbg(0, "(%p) Interface up: %s\n", dev, dev->name);

		अगर (netअगर_carrier_ok(dev)) अणु
			lapb_dbg(0, "(%p): Carrier is already up: %s\n", dev,
				 dev->name);
			अगर (lapb->mode & LAPB_DCE) अणु
				lapb_start_t1समयr(lapb);
			पूर्ण अन्यथा अणु
				अगर (lapb->state == LAPB_STATE_0) अणु
					lapb->state = LAPB_STATE_1;
					lapb_establish_data_link(lapb);
				पूर्ण
			पूर्ण
		पूर्ण
		अवरोध;
	हाल NETDEV_GOING_DOWN:
		अगर (netअगर_carrier_ok(dev))
			__lapb_disconnect_request(lapb);
		अवरोध;
	हाल NETDEV_DOWN:
		lapb_dbg(0, "(%p) Interface down: %s\n", dev, dev->name);
		lapb_dbg(0, "(%p) S%d -> S0\n", dev, lapb->state);
		lapb_clear_queues(lapb);
		lapb->state = LAPB_STATE_0;
		lapb->n2count   = 0;
		lapb_stop_t1समयr(lapb);
		lapb_stop_t2समयr(lapb);
		अवरोध;
	हाल NETDEV_CHANGE:
		अगर (netअगर_carrier_ok(dev)) अणु
			lapb_dbg(0, "(%p): Carrier detected: %s\n", dev,
				 dev->name);
			अगर (lapb->mode & LAPB_DCE) अणु
				lapb_start_t1समयr(lapb);
			पूर्ण अन्यथा अणु
				अगर (lapb->state == LAPB_STATE_0) अणु
					lapb->state = LAPB_STATE_1;
					lapb_establish_data_link(lapb);
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा अणु
			lapb_dbg(0, "(%p) Carrier lost: %s\n", dev, dev->name);
			lapb_dbg(0, "(%p) S%d -> S0\n", dev, lapb->state);
			lapb_clear_queues(lapb);
			lapb->state = LAPB_STATE_0;
			lapb->n2count   = 0;
			lapb_stop_t1समयr(lapb);
			lapb_stop_t2समयr(lapb);
		पूर्ण
		अवरोध;
	पूर्ण

	spin_unlock_bh(&lapb->lock);
	lapb_put(lapb);
	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा notअगरier_block lapb_dev_notअगरier = अणु
	.notअगरier_call = lapb_device_event,
पूर्ण;

अटल पूर्णांक __init lapb_init(व्योम)
अणु
	वापस रेजिस्टर_netdevice_notअगरier(&lapb_dev_notअगरier);
पूर्ण

अटल व्योम __निकास lapb_निकास(व्योम)
अणु
	WARN_ON(!list_empty(&lapb_list));

	unरेजिस्टर_netdevice_notअगरier(&lapb_dev_notअगरier);
पूर्ण

MODULE_AUTHOR("Jonathan Naylor <g4klx@g4klx.demon.co.uk>");
MODULE_DESCRIPTION("The X.25 Link Access Procedure B link layer protocol");
MODULE_LICENSE("GPL");

module_init(lapb_init);
module_निकास(lapb_निकास);
