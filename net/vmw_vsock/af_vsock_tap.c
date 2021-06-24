<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Tap functions क्रम AF_VSOCK sockets.
 *
 * Code based on net/netlink/af_netlink.c tap functions.
 */

#समावेश <linux/module.h>
#समावेश <net/sock.h>
#समावेश <net/af_vsock.h>
#समावेश <linux/अगर_arp.h>

अटल DEFINE_SPINLOCK(vsock_tap_lock);
अटल काष्ठा list_head vsock_tap_all __पढ़ो_mostly =
				LIST_HEAD_INIT(vsock_tap_all);

पूर्णांक vsock_add_tap(काष्ठा vsock_tap *vt)
अणु
	अगर (unlikely(vt->dev->type != ARPHRD_VSOCKMON))
		वापस -EINVAL;

	__module_get(vt->module);

	spin_lock(&vsock_tap_lock);
	list_add_rcu(&vt->list, &vsock_tap_all);
	spin_unlock(&vsock_tap_lock);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(vsock_add_tap);

पूर्णांक vsock_हटाओ_tap(काष्ठा vsock_tap *vt)
अणु
	काष्ठा vsock_tap *पंचांगp;
	bool found = false;

	spin_lock(&vsock_tap_lock);

	list_क्रम_each_entry(पंचांगp, &vsock_tap_all, list) अणु
		अगर (vt == पंचांगp) अणु
			list_del_rcu(&vt->list);
			found = true;
			जाओ out;
		पूर्ण
	पूर्ण

	pr_warn("vsock_remove_tap: %p not found\n", vt);
out:
	spin_unlock(&vsock_tap_lock);

	synchronize_net();

	अगर (found)
		module_put(vt->module);

	वापस found ? 0 : -ENODEV;
पूर्ण
EXPORT_SYMBOL_GPL(vsock_हटाओ_tap);

अटल पूर्णांक __vsock_deliver_tap_skb(काष्ठा sk_buff *skb,
				   काष्ठा net_device *dev)
अणु
	पूर्णांक ret = 0;
	काष्ठा sk_buff *nskb = skb_clone(skb, GFP_ATOMIC);

	अगर (nskb) अणु
		dev_hold(dev);

		nskb->dev = dev;
		ret = dev_queue_xmit(nskb);
		अगर (unlikely(ret > 0))
			ret = net_xmit_त्रुटि_सं(ret);

		dev_put(dev);
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम __vsock_deliver_tap(काष्ठा sk_buff *skb)
अणु
	पूर्णांक ret;
	काष्ठा vsock_tap *पंचांगp;

	list_क्रम_each_entry_rcu(पंचांगp, &vsock_tap_all, list) अणु
		ret = __vsock_deliver_tap_skb(skb, पंचांगp->dev);
		अगर (unlikely(ret))
			अवरोध;
	पूर्ण
पूर्ण

व्योम vsock_deliver_tap(काष्ठा sk_buff *build_skb(व्योम *opaque), व्योम *opaque)
अणु
	काष्ठा sk_buff *skb;

	rcu_पढ़ो_lock();

	अगर (likely(list_empty(&vsock_tap_all)))
		जाओ out;

	skb = build_skb(opaque);
	अगर (skb) अणु
		__vsock_deliver_tap(skb);
		consume_skb(skb);
	पूर्ण

out:
	rcu_पढ़ो_unlock();
पूर्ण
EXPORT_SYMBOL_GPL(vsock_deliver_tap);
