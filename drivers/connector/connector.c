<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *	connector.c
 *
 * 2004+ Copyright (c) Evgeniy Polyakov <zbr@ioremap.net>
 * All rights reserved.
 */

#समावेश <linux/compiler.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/list.h>
#समावेश <linux/skbuff.h>
#समावेश <net/netlink.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/connector.h>
#समावेश <linux/slab.h>
#समावेश <linux/mutex.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/spinlock.h>

#समावेश <net/sock.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Evgeniy Polyakov <zbr@ioremap.net>");
MODULE_DESCRIPTION("Generic userspace <-> kernelspace connector.");
MODULE_ALIAS_NET_PF_PROTO(PF_NETLINK, NETLINK_CONNECTOR);

अटल काष्ठा cn_dev cdev;

अटल पूर्णांक cn_alपढ़ोy_initialized;

/*
 * Sends mult (multiple) cn_msg at a समय.
 *
 * msg->seq and msg->ack are used to determine message genealogy.
 * When someone sends message it माला_दो there locally unique sequence
 * and अक्रमom acknowledge numbers.  Sequence number may be copied पूर्णांकo
 * nlmsghdr->nlmsg_seq too.
 *
 * Sequence number is incremented with each message to be sent.
 *
 * If we expect a reply to our message then the sequence number in
 * received message MUST be the same as in original message, and
 * acknowledge number MUST be the same + 1.
 *
 * If we receive a message and its sequence number is not equal to the
 * one we are expecting then it is a new message.
 *
 * If we receive a message and its sequence number is the same as one
 * we are expecting but it's acknowledgement number is not equal to
 * the acknowledgement number in the original message + 1, then it is
 * a new message.
 *
 * If msg->len != len, then additional cn_msg messages are expected following
 * the first msg.
 *
 * The message is sent to, the portid अगर given, the group अगर given, both अगर
 * both, or अगर both are zero then the group is looked up and sent there.
 */
पूर्णांक cn_netlink_send_mult(काष्ठा cn_msg *msg, u16 len, u32 portid, u32 __group,
	gfp_t gfp_mask)
अणु
	काष्ठा cn_callback_entry *__cbq;
	अचिन्हित पूर्णांक size;
	काष्ठा sk_buff *skb;
	काष्ठा nlmsghdr *nlh;
	काष्ठा cn_msg *data;
	काष्ठा cn_dev *dev = &cdev;
	u32 group = 0;
	पूर्णांक found = 0;

	अगर (portid || __group) अणु
		group = __group;
	पूर्ण अन्यथा अणु
		spin_lock_bh(&dev->cbdev->queue_lock);
		list_क्रम_each_entry(__cbq, &dev->cbdev->queue_list,
				    callback_entry) अणु
			अगर (cn_cb_equal(&__cbq->id.id, &msg->id)) अणु
				found = 1;
				group = __cbq->group;
				अवरोध;
			पूर्ण
		पूर्ण
		spin_unlock_bh(&dev->cbdev->queue_lock);

		अगर (!found)
			वापस -ENODEV;
	पूर्ण

	अगर (!portid && !netlink_has_listeners(dev->nls, group))
		वापस -ESRCH;

	size = माप(*msg) + len;

	skb = nlmsg_new(size, gfp_mask);
	अगर (!skb)
		वापस -ENOMEM;

	nlh = nlmsg_put(skb, 0, msg->seq, NLMSG_DONE, size, 0);
	अगर (!nlh) अणु
		kमुक्त_skb(skb);
		वापस -EMSGSIZE;
	पूर्ण

	data = nlmsg_data(nlh);

	स_नकल(data, msg, size);

	NETLINK_CB(skb).dst_group = group;

	अगर (group)
		वापस netlink_broadcast(dev->nls, skb, portid, group,
					 gfp_mask);
	वापस netlink_unicast(dev->nls, skb, portid,
			!gfpflags_allow_blocking(gfp_mask));
पूर्ण
EXPORT_SYMBOL_GPL(cn_netlink_send_mult);

/* same as cn_netlink_send_mult except msg->len is used क्रम len */
पूर्णांक cn_netlink_send(काष्ठा cn_msg *msg, u32 portid, u32 __group,
	gfp_t gfp_mask)
अणु
	वापस cn_netlink_send_mult(msg, msg->len, portid, __group, gfp_mask);
पूर्ण
EXPORT_SYMBOL_GPL(cn_netlink_send);

/*
 * Callback helper - queues work and setup deकाष्ठाor क्रम given data.
 */
अटल पूर्णांक cn_call_callback(काष्ठा sk_buff *skb)
अणु
	काष्ठा nlmsghdr *nlh;
	काष्ठा cn_callback_entry *i, *cbq = शून्य;
	काष्ठा cn_dev *dev = &cdev;
	काष्ठा cn_msg *msg = nlmsg_data(nlmsg_hdr(skb));
	काष्ठा netlink_skb_parms *nsp = &NETLINK_CB(skb);
	पूर्णांक err = -ENODEV;

	/* verअगरy msg->len is within skb */
	nlh = nlmsg_hdr(skb);
	अगर (nlh->nlmsg_len < NLMSG_HDRLEN + माप(काष्ठा cn_msg) + msg->len)
		वापस -EINVAL;

	spin_lock_bh(&dev->cbdev->queue_lock);
	list_क्रम_each_entry(i, &dev->cbdev->queue_list, callback_entry) अणु
		अगर (cn_cb_equal(&i->id.id, &msg->id)) अणु
			refcount_inc(&i->refcnt);
			cbq = i;
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock_bh(&dev->cbdev->queue_lock);

	अगर (cbq != शून्य) अणु
		cbq->callback(msg, nsp);
		kमुक्त_skb(skb);
		cn_queue_release_callback(cbq);
		err = 0;
	पूर्ण

	वापस err;
पूर्ण

/*
 * Main netlink receiving function.
 *
 * It checks skb, netlink header and msg sizes, and calls callback helper.
 */
अटल व्योम cn_rx_skb(काष्ठा sk_buff *skb)
अणु
	काष्ठा nlmsghdr *nlh;
	पूर्णांक len, err;

	अगर (skb->len >= NLMSG_HDRLEN) अणु
		nlh = nlmsg_hdr(skb);
		len = nlmsg_len(nlh);

		अगर (len < (पूर्णांक)माप(काष्ठा cn_msg) ||
		    skb->len < nlh->nlmsg_len ||
		    len > CONNECTOR_MAX_MSG_SIZE)
			वापस;

		err = cn_call_callback(skb_get(skb));
		अगर (err < 0)
			kमुक्त_skb(skb);
	पूर्ण
पूर्ण

/*
 * Callback add routing - adds callback with given ID and name.
 * If there is रेजिस्टरed callback with the same ID it will not be added.
 *
 * May sleep.
 */
पूर्णांक cn_add_callback(स्थिर काष्ठा cb_id *id, स्थिर अक्षर *name,
		    व्योम (*callback)(काष्ठा cn_msg *,
				     काष्ठा netlink_skb_parms *))
अणु
	काष्ठा cn_dev *dev = &cdev;

	अगर (!cn_alपढ़ोy_initialized)
		वापस -EAGAIN;

	वापस cn_queue_add_callback(dev->cbdev, name, id, callback);
पूर्ण
EXPORT_SYMBOL_GPL(cn_add_callback);

/*
 * Callback हटाओ routing - हटाओs callback
 * with given ID.
 * If there is no रेजिस्टरed callback with given
 * ID nothing happens.
 *
 * May sleep जबतक रुकोing क्रम reference counter to become zero.
 */
व्योम cn_del_callback(स्थिर काष्ठा cb_id *id)
अणु
	काष्ठा cn_dev *dev = &cdev;

	cn_queue_del_callback(dev->cbdev, id);
पूर्ण
EXPORT_SYMBOL_GPL(cn_del_callback);

अटल पूर्णांक __maybe_unused cn_proc_show(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा cn_queue_dev *dev = cdev.cbdev;
	काष्ठा cn_callback_entry *cbq;

	seq_म_लिखो(m, "Name            ID\n");

	spin_lock_bh(&dev->queue_lock);

	list_क्रम_each_entry(cbq, &dev->queue_list, callback_entry) अणु
		seq_म_लिखो(m, "%-15s %u:%u\n",
			   cbq->id.name,
			   cbq->id.id.idx,
			   cbq->id.id.val);
	पूर्ण

	spin_unlock_bh(&dev->queue_lock);

	वापस 0;
पूर्ण

अटल पूर्णांक cn_init(व्योम)
अणु
	काष्ठा cn_dev *dev = &cdev;
	काष्ठा netlink_kernel_cfg cfg = अणु
		.groups	= CN_NETLINK_USERS + 0xf,
		.input	= cn_rx_skb,
	पूर्ण;

	dev->nls = netlink_kernel_create(&init_net, NETLINK_CONNECTOR, &cfg);
	अगर (!dev->nls)
		वापस -EIO;

	dev->cbdev = cn_queue_alloc_dev("cqueue", dev->nls);
	अगर (!dev->cbdev) अणु
		netlink_kernel_release(dev->nls);
		वापस -EINVAL;
	पूर्ण

	cn_alपढ़ोy_initialized = 1;

	proc_create_single("connector", S_IRUGO, init_net.proc_net, cn_proc_show);

	वापस 0;
पूर्ण

अटल व्योम cn_fini(व्योम)
अणु
	काष्ठा cn_dev *dev = &cdev;

	cn_alपढ़ोy_initialized = 0;

	हटाओ_proc_entry("connector", init_net.proc_net);

	cn_queue_मुक्त_dev(dev->cbdev);
	netlink_kernel_release(dev->nls);
पूर्ण

subsys_initcall(cn_init);
module_निकास(cn_fini);
