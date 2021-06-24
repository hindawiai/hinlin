<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * 	cn_test.c
 * 
 * 2004+ Copyright (c) Evgeniy Polyakov <zbr@ioremap.net>
 * All rights reserved.
 */

#घोषणा pr_fmt(fmt) "cn_test: " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/slab.h>
#समावेश <linux/समयr.h>

#समावेश <linux/connector.h>

अटल काष्ठा cb_id cn_test_id = अणु CN_NETLINK_USERS + 3, 0x456 पूर्ण;
अटल अक्षर cn_test_name[] = "cn_test";
अटल काष्ठा sock *nls;
अटल काष्ठा समयr_list cn_test_समयr;

अटल व्योम cn_test_callback(काष्ठा cn_msg *msg, काष्ठा netlink_skb_parms *nsp)
अणु
	pr_info("%s: %lu: idx=%x, val=%x, seq=%u, ack=%u, len=%d: %s.\n",
	        __func__, jअगरfies, msg->id.idx, msg->id.val,
	        msg->seq, msg->ack, msg->len,
	        msg->len ? (अक्षर *)msg->data : "");
पूर्ण

/*
 * Do not हटाओ this function even अगर no one is using it as
 * this is an example of how to get notअगरications about new
 * connector user registration
 */
#अगर 0
अटल पूर्णांक cn_test_want_notअगरy(व्योम)
अणु
	काष्ठा cn_ctl_msg *ctl;
	काष्ठा cn_notअगरy_req *req;
	काष्ठा cn_msg *msg = शून्य;
	पूर्णांक size, size0;
	काष्ठा sk_buff *skb;
	काष्ठा nlmsghdr *nlh;
	u32 group = 1;

	size0 = माप(*msg) + माप(*ctl) + 3 * माप(*req);

	size = NLMSG_SPACE(size0);

	skb = alloc_skb(size, GFP_ATOMIC);
	अगर (!skb) अणु
		pr_err("failed to allocate new skb with size=%u\n", size);
		वापस -ENOMEM;
	पूर्ण

	nlh = nlmsg_put(skb, 0, 0x123, NLMSG_DONE, size - माप(*nlh), 0);
	अगर (!nlh) अणु
		kमुक्त_skb(skb);
		वापस -EMSGSIZE;
	पूर्ण

	msg = nlmsg_data(nlh);

	स_रखो(msg, 0, size0);

	msg->id.idx = -1;
	msg->id.val = -1;
	msg->seq = 0x123;
	msg->ack = 0x345;
	msg->len = size0 - माप(*msg);

	ctl = (काष्ठा cn_ctl_msg *)(msg + 1);

	ctl->idx_notअगरy_num = 1;
	ctl->val_notअगरy_num = 2;
	ctl->group = group;
	ctl->len = msg->len - माप(*ctl);

	req = (काष्ठा cn_notअगरy_req *)(ctl + 1);

	/*
	 * Idx.
	 */
	req->first = cn_test_id.idx;
	req->range = 10;

	/*
	 * Val 0.
	 */
	req++;
	req->first = cn_test_id.val;
	req->range = 10;

	/*
	 * Val 1.
	 */
	req++;
	req->first = cn_test_id.val + 20;
	req->range = 10;

	NETLINK_CB(skb).dst_group = ctl->group;
	//netlink_broadcast(nls, skb, 0, ctl->group, GFP_ATOMIC);
	netlink_unicast(nls, skb, 0, 0);

	pr_info("request was sent: group=0x%x\n", ctl->group);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल u32 cn_test_समयr_counter;
अटल व्योम cn_test_समयr_func(काष्ठा समयr_list *unused)
अणु
	काष्ठा cn_msg *m;
	अक्षर data[32];

	pr_debug("%s: timer fired\n", __func__);

	m = kzalloc(माप(*m) + माप(data), GFP_ATOMIC);
	अगर (m) अणु

		स_नकल(&m->id, &cn_test_id, माप(m->id));
		m->seq = cn_test_समयr_counter;
		m->len = माप(data);

		m->len =
		    scnम_लिखो(data, माप(data), "counter = %u",
			      cn_test_समयr_counter) + 1;

		स_नकल(m + 1, data, m->len);

		cn_netlink_send(m, 0, 0, GFP_ATOMIC);
		kमुक्त(m);
	पूर्ण

	cn_test_समयr_counter++;

	mod_समयr(&cn_test_समयr, jअगरfies + msecs_to_jअगरfies(1000));
पूर्ण

अटल पूर्णांक cn_test_init(व्योम)
अणु
	पूर्णांक err;

	err = cn_add_callback(&cn_test_id, cn_test_name, cn_test_callback);
	अगर (err)
		जाओ err_out;
	cn_test_id.val++;
	err = cn_add_callback(&cn_test_id, cn_test_name, cn_test_callback);
	अगर (err) अणु
		cn_del_callback(&cn_test_id);
		जाओ err_out;
	पूर्ण

	समयr_setup(&cn_test_समयr, cn_test_समयr_func, 0);
	mod_समयr(&cn_test_समयr, jअगरfies + msecs_to_jअगरfies(1000));

	pr_info("initialized with id={%u.%u}\n",
		cn_test_id.idx, cn_test_id.val);

	वापस 0;

      err_out:
	अगर (nls && nls->sk_socket)
		sock_release(nls->sk_socket);

	वापस err;
पूर्ण

अटल व्योम cn_test_fini(व्योम)
अणु
	del_समयr_sync(&cn_test_समयr);
	cn_del_callback(&cn_test_id);
	cn_test_id.val--;
	cn_del_callback(&cn_test_id);
	अगर (nls && nls->sk_socket)
		sock_release(nls->sk_socket);
पूर्ण

module_init(cn_test_init);
module_निकास(cn_test_fini);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Evgeniy Polyakov <zbr@ioremap.net>");
MODULE_DESCRIPTION("Connector's test module");
