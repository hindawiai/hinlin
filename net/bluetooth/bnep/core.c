<शैली गुरु>
/*
   BNEP implementation क्रम Linux Bluetooth stack (BlueZ).
   Copyright (C) 2001-2002 Inventel Systemes
   Written 2001-2002 by
	Clथऊment Moreau <clement.moreau@inventel.fr>
	David Libault  <david.libault@inventel.fr>

   Copyright (C) 2002 Maxim Krasnyansky <maxk@qualcomm.com>

   This program is मुक्त software; you can redistribute it and/or modअगरy
   it under the terms of the GNU General Public License version 2 as
   published by the Free Software Foundation;

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
   OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT OF THIRD PARTY RIGHTS.
   IN NO EVENT SHALL THE COPYRIGHT HOLDER(S) AND AUTHOR(S) BE LIABLE FOR ANY
   CLAIM, OR ANY SPECIAL INसूचीECT OR CONSEQUENTIAL DAMAGES, OR ANY DAMAGES
   WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
   ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
   OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.

   ALL LIABILITY, INCLUDING LIABILITY FOR INFRINGEMENT OF ANY PATENTS,
   COPYRIGHTS, TRADEMARKS OR OTHER RIGHTS, RELATING TO USE OF THIS
   SOFTWARE IS DISCLAIMED.
*/

#समावेश <linux/module.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/file.h>
#समावेश <linux/etherdevice.h>
#समावेश <यंत्र/unaligned.h>

#समावेश <net/bluetooth/bluetooth.h>
#समावेश <net/bluetooth/l2cap.h>
#समावेश <net/bluetooth/hci_core.h>

#समावेश "bnep.h"

#घोषणा VERSION "1.3"

अटल bool compress_src = true;
अटल bool compress_dst = true;

अटल LIST_HEAD(bnep_session_list);
अटल DECLARE_RWSEM(bnep_session_sem);

अटल काष्ठा bnep_session *__bnep_get_session(u8 *dst)
अणु
	काष्ठा bnep_session *s;

	BT_DBG("");

	list_क्रम_each_entry(s, &bnep_session_list, list)
		अगर (ether_addr_equal(dst, s->eh.h_source))
			वापस s;

	वापस शून्य;
पूर्ण

अटल व्योम __bnep_link_session(काष्ठा bnep_session *s)
अणु
	list_add(&s->list, &bnep_session_list);
पूर्ण

अटल व्योम __bnep_unlink_session(काष्ठा bnep_session *s)
अणु
	list_del(&s->list);
पूर्ण

अटल पूर्णांक bnep_send(काष्ठा bnep_session *s, व्योम *data, माप_प्रकार len)
अणु
	काष्ठा socket *sock = s->sock;
	काष्ठा kvec iv = अणु data, len पूर्ण;

	वापस kernel_sendmsg(sock, &s->msg, &iv, 1, len);
पूर्ण

अटल पूर्णांक bnep_send_rsp(काष्ठा bnep_session *s, u8 ctrl, u16 resp)
अणु
	काष्ठा bnep_control_rsp rsp;
	rsp.type = BNEP_CONTROL;
	rsp.ctrl = ctrl;
	rsp.resp = htons(resp);
	वापस bnep_send(s, &rsp, माप(rsp));
पूर्ण

#अगर_घोषित CONFIG_BT_BNEP_PROTO_FILTER
अटल अंतरभूत व्योम bnep_set_शेष_proto_filter(काष्ठा bnep_session *s)
अणु
	/* (IPv4, ARP)  */
	s->proto_filter[0].start = ETH_P_IP;
	s->proto_filter[0].end   = ETH_P_ARP;
	/* (RARP, AppleTalk) */
	s->proto_filter[1].start = ETH_P_RARP;
	s->proto_filter[1].end   = ETH_P_AARP;
	/* (IPX, IPv6) */
	s->proto_filter[2].start = ETH_P_IPX;
	s->proto_filter[2].end   = ETH_P_IPV6;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक bnep_ctrl_set_netfilter(काष्ठा bnep_session *s, __be16 *data, पूर्णांक len)
अणु
	पूर्णांक n;

	अगर (len < 2)
		वापस -EILSEQ;

	n = get_unaligned_be16(data);
	data++;
	len -= 2;

	अगर (len < n)
		वापस -EILSEQ;

	BT_DBG("filter len %d", n);

#अगर_घोषित CONFIG_BT_BNEP_PROTO_FILTER
	n /= 4;
	अगर (n <= BNEP_MAX_PROTO_FILTERS) अणु
		काष्ठा bnep_proto_filter *f = s->proto_filter;
		पूर्णांक i;

		क्रम (i = 0; i < n; i++) अणु
			f[i].start = get_unaligned_be16(data++);
			f[i].end   = get_unaligned_be16(data++);

			BT_DBG("proto filter start %d end %d",
				f[i].start, f[i].end);
		पूर्ण

		अगर (i < BNEP_MAX_PROTO_FILTERS)
			स_रखो(f + i, 0, माप(*f));

		अगर (n == 0)
			bnep_set_शेष_proto_filter(s);

		bnep_send_rsp(s, BNEP_FILTER_NET_TYPE_RSP, BNEP_SUCCESS);
	पूर्ण अन्यथा अणु
		bnep_send_rsp(s, BNEP_FILTER_NET_TYPE_RSP, BNEP_FILTER_LIMIT_REACHED);
	पूर्ण
#अन्यथा
	bnep_send_rsp(s, BNEP_FILTER_NET_TYPE_RSP, BNEP_FILTER_UNSUPPORTED_REQ);
#पूर्ण_अगर
	वापस 0;
पूर्ण

अटल पूर्णांक bnep_ctrl_set_mcfilter(काष्ठा bnep_session *s, u8 *data, पूर्णांक len)
अणु
	पूर्णांक n;

	अगर (len < 2)
		वापस -EILSEQ;

	n = get_unaligned_be16(data);
	data += 2;
	len -= 2;

	अगर (len < n)
		वापस -EILSEQ;

	BT_DBG("filter len %d", n);

#अगर_घोषित CONFIG_BT_BNEP_MC_FILTER
	n /= (ETH_ALEN * 2);

	अगर (n > 0) अणु
		पूर्णांक i;

		s->mc_filter = 0;

		/* Always send broadcast */
		set_bit(bnep_mc_hash(s->dev->broadcast), (uदीर्घ *) &s->mc_filter);

		/* Add address ranges to the multicast hash */
		क्रम (; n > 0; n--) अणु
			u8 a1[6], *a2;

			स_नकल(a1, data, ETH_ALEN);
			data += ETH_ALEN;
			a2 = data;
			data += ETH_ALEN;

			BT_DBG("mc filter %pMR -> %pMR", a1, a2);

			/* Iterate from a1 to a2 */
			set_bit(bnep_mc_hash(a1), (uदीर्घ *) &s->mc_filter);
			जबतक (स_भेद(a1, a2, 6) < 0 && s->mc_filter != ~0LL) अणु
				/* Increment a1 */
				i = 5;
				जबतक (i >= 0 && ++a1[i--] == 0)
					;

				set_bit(bnep_mc_hash(a1), (uदीर्घ *) &s->mc_filter);
			पूर्ण
		पूर्ण
	पूर्ण

	BT_DBG("mc filter hash 0x%llx", s->mc_filter);

	bnep_send_rsp(s, BNEP_FILTER_MULTI_ADDR_RSP, BNEP_SUCCESS);
#अन्यथा
	bnep_send_rsp(s, BNEP_FILTER_MULTI_ADDR_RSP, BNEP_FILTER_UNSUPPORTED_REQ);
#पूर्ण_अगर
	वापस 0;
पूर्ण

अटल पूर्णांक bnep_rx_control(काष्ठा bnep_session *s, व्योम *data, पूर्णांक len)
अणु
	u8  cmd = *(u8 *)data;
	पूर्णांक err = 0;

	data++;
	len--;

	चयन (cmd) अणु
	हाल BNEP_CMD_NOT_UNDERSTOOD:
	हाल BNEP_SETUP_CONN_RSP:
	हाल BNEP_FILTER_NET_TYPE_RSP:
	हाल BNEP_FILTER_MULTI_ADDR_RSP:
		/* Ignore these क्रम now */
		अवरोध;

	हाल BNEP_FILTER_NET_TYPE_SET:
		err = bnep_ctrl_set_netfilter(s, data, len);
		अवरोध;

	हाल BNEP_FILTER_MULTI_ADDR_SET:
		err = bnep_ctrl_set_mcfilter(s, data, len);
		अवरोध;

	हाल BNEP_SETUP_CONN_REQ:
		/* Successful response should be sent only once */
		अगर (test_bit(BNEP_SETUP_RESPONSE, &s->flags) &&
		    !test_and_set_bit(BNEP_SETUP_RSP_SENT, &s->flags))
			err = bnep_send_rsp(s, BNEP_SETUP_CONN_RSP,
					    BNEP_SUCCESS);
		अन्यथा
			err = bnep_send_rsp(s, BNEP_SETUP_CONN_RSP,
					    BNEP_CONN_NOT_ALLOWED);
		अवरोध;

	शेष: अणु
			u8 pkt[3];
			pkt[0] = BNEP_CONTROL;
			pkt[1] = BNEP_CMD_NOT_UNDERSTOOD;
			pkt[2] = cmd;
			err = bnep_send(s, pkt, माप(pkt));
		पूर्ण
		अवरोध;
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक bnep_rx_extension(काष्ठा bnep_session *s, काष्ठा sk_buff *skb)
अणु
	काष्ठा bnep_ext_hdr *h;
	पूर्णांक err = 0;

	करो अणु
		h = (व्योम *) skb->data;
		अगर (!skb_pull(skb, माप(*h))) अणु
			err = -EILSEQ;
			अवरोध;
		पूर्ण

		BT_DBG("type 0x%x len %d", h->type, h->len);

		चयन (h->type & BNEP_TYPE_MASK) अणु
		हाल BNEP_EXT_CONTROL:
			bnep_rx_control(s, skb->data, skb->len);
			अवरोध;

		शेष:
			/* Unknown extension, skip it. */
			अवरोध;
		पूर्ण

		अगर (!skb_pull(skb, h->len)) अणु
			err = -EILSEQ;
			अवरोध;
		पूर्ण
	पूर्ण जबतक (!err && (h->type & BNEP_EXT_HEADER));

	वापस err;
पूर्ण

अटल u8 __bnep_rx_hlen[] = अणु
	ETH_HLEN,     /* BNEP_GENERAL */
	0,            /* BNEP_CONTROL */
	2,            /* BNEP_COMPRESSED */
	ETH_ALEN + 2, /* BNEP_COMPRESSED_SRC_ONLY */
	ETH_ALEN + 2  /* BNEP_COMPRESSED_DST_ONLY */
पूर्ण;

अटल पूर्णांक bnep_rx_frame(काष्ठा bnep_session *s, काष्ठा sk_buff *skb)
अणु
	काष्ठा net_device *dev = s->dev;
	काष्ठा sk_buff *nskb;
	u8 type, ctrl_type;

	dev->stats.rx_bytes += skb->len;

	type = *(u8 *) skb->data;
	skb_pull(skb, 1);
	ctrl_type = *(u8 *)skb->data;

	अगर ((type & BNEP_TYPE_MASK) >= माप(__bnep_rx_hlen))
		जाओ badframe;

	अगर ((type & BNEP_TYPE_MASK) == BNEP_CONTROL) अणु
		अगर (bnep_rx_control(s, skb->data, skb->len) < 0) अणु
			dev->stats.tx_errors++;
			kमुक्त_skb(skb);
			वापस 0;
		पूर्ण

		अगर (!(type & BNEP_EXT_HEADER)) अणु
			kमुक्त_skb(skb);
			वापस 0;
		पूर्ण

		/* Verअगरy and pull ctrl message since it's alपढ़ोy processed */
		चयन (ctrl_type) अणु
		हाल BNEP_SETUP_CONN_REQ:
			/* Pull: ctrl type (1 b), len (1 b), data (len bytes) */
			अगर (!skb_pull(skb, 2 + *(u8 *)(skb->data + 1) * 2))
				जाओ badframe;
			अवरोध;
		हाल BNEP_FILTER_MULTI_ADDR_SET:
		हाल BNEP_FILTER_NET_TYPE_SET:
			/* Pull: ctrl type (1 b), len (2 b), data (len bytes) */
			अगर (!skb_pull(skb, 3 + *(u16 *)(skb->data + 1) * 2))
				जाओ badframe;
			अवरोध;
		शेष:
			kमुक्त_skb(skb);
			वापस 0;
		पूर्ण
	पूर्ण अन्यथा अणु
		skb_reset_mac_header(skb);

		/* Verअगरy and pull out header */
		अगर (!skb_pull(skb, __bnep_rx_hlen[type & BNEP_TYPE_MASK]))
			जाओ badframe;

		s->eh.h_proto = get_unaligned((__be16 *) (skb->data - 2));
	पूर्ण

	अगर (type & BNEP_EXT_HEADER) अणु
		अगर (bnep_rx_extension(s, skb) < 0)
			जाओ badframe;
	पूर्ण

	/* Strip 802.1p header */
	अगर (ntohs(s->eh.h_proto) == ETH_P_8021Q) अणु
		अगर (!skb_pull(skb, 4))
			जाओ badframe;
		s->eh.h_proto = get_unaligned((__be16 *) (skb->data - 2));
	पूर्ण

	/* We have to alloc new skb and copy data here :(. Because original skb
	 * may not be modअगरied and because of the alignment requirements. */
	nskb = alloc_skb(2 + ETH_HLEN + skb->len, GFP_KERNEL);
	अगर (!nskb) अणु
		dev->stats.rx_dropped++;
		kमुक्त_skb(skb);
		वापस -ENOMEM;
	पूर्ण
	skb_reserve(nskb, 2);

	/* Decompress header and स्थिरruct ether frame */
	चयन (type & BNEP_TYPE_MASK) अणु
	हाल BNEP_COMPRESSED:
		__skb_put_data(nskb, &s->eh, ETH_HLEN);
		अवरोध;

	हाल BNEP_COMPRESSED_SRC_ONLY:
		__skb_put_data(nskb, s->eh.h_dest, ETH_ALEN);
		__skb_put_data(nskb, skb_mac_header(skb), ETH_ALEN);
		put_unaligned(s->eh.h_proto, (__be16 *) __skb_put(nskb, 2));
		अवरोध;

	हाल BNEP_COMPRESSED_DST_ONLY:
		__skb_put_data(nskb, skb_mac_header(skb), ETH_ALEN);
		__skb_put_data(nskb, s->eh.h_source, ETH_ALEN + 2);
		अवरोध;

	हाल BNEP_GENERAL:
		__skb_put_data(nskb, skb_mac_header(skb), ETH_ALEN * 2);
		put_unaligned(s->eh.h_proto, (__be16 *) __skb_put(nskb, 2));
		अवरोध;
	पूर्ण

	skb_copy_from_linear_data(skb, __skb_put(nskb, skb->len), skb->len);
	kमुक्त_skb(skb);

	dev->stats.rx_packets++;
	nskb->ip_summed = CHECKSUM_NONE;
	nskb->protocol  = eth_type_trans(nskb, dev);
	netअगर_rx_ni(nskb);
	वापस 0;

badframe:
	dev->stats.rx_errors++;
	kमुक्त_skb(skb);
	वापस 0;
पूर्ण

अटल u8 __bnep_tx_types[] = अणु
	BNEP_GENERAL,
	BNEP_COMPRESSED_SRC_ONLY,
	BNEP_COMPRESSED_DST_ONLY,
	BNEP_COMPRESSED
पूर्ण;

अटल पूर्णांक bnep_tx_frame(काष्ठा bnep_session *s, काष्ठा sk_buff *skb)
अणु
	काष्ठा ethhdr *eh = (व्योम *) skb->data;
	काष्ठा socket *sock = s->sock;
	काष्ठा kvec iv[3];
	पूर्णांक len = 0, il = 0;
	u8 type = 0;

	BT_DBG("skb %p dev %p type %d", skb, skb->dev, skb->pkt_type);

	अगर (!skb->dev) अणु
		/* Control frame sent by us */
		जाओ send;
	पूर्ण

	iv[il++] = (काष्ठा kvec) अणु &type, 1 पूर्ण;
	len++;

	अगर (compress_src && ether_addr_equal(eh->h_dest, s->eh.h_source))
		type |= 0x01;

	अगर (compress_dst && ether_addr_equal(eh->h_source, s->eh.h_dest))
		type |= 0x02;

	अगर (type)
		skb_pull(skb, ETH_ALEN * 2);

	type = __bnep_tx_types[type];
	चयन (type) अणु
	हाल BNEP_COMPRESSED_SRC_ONLY:
		iv[il++] = (काष्ठा kvec) अणु eh->h_source, ETH_ALEN पूर्ण;
		len += ETH_ALEN;
		अवरोध;

	हाल BNEP_COMPRESSED_DST_ONLY:
		iv[il++] = (काष्ठा kvec) अणु eh->h_dest, ETH_ALEN पूर्ण;
		len += ETH_ALEN;
		अवरोध;
	पूर्ण

send:
	iv[il++] = (काष्ठा kvec) अणु skb->data, skb->len पूर्ण;
	len += skb->len;

	/* FIXME: linearize skb */
	अणु
		len = kernel_sendmsg(sock, &s->msg, iv, il, len);
	पूर्ण
	kमुक्त_skb(skb);

	अगर (len > 0) अणु
		s->dev->stats.tx_bytes += len;
		s->dev->stats.tx_packets++;
		वापस 0;
	पूर्ण

	वापस len;
पूर्ण

अटल पूर्णांक bnep_session(व्योम *arg)
अणु
	काष्ठा bnep_session *s = arg;
	काष्ठा net_device *dev = s->dev;
	काष्ठा sock *sk = s->sock->sk;
	काष्ठा sk_buff *skb;
	DEFINE_WAIT_FUNC(रुको, woken_wake_function);

	BT_DBG("");

	set_user_nice(current, -15);

	add_रुको_queue(sk_sleep(sk), &रुको);
	जबतक (1) अणु
		अगर (atomic_पढ़ो(&s->terminate))
			अवरोध;
		/* RX */
		जबतक ((skb = skb_dequeue(&sk->sk_receive_queue))) अणु
			skb_orphan(skb);
			अगर (!skb_linearize(skb))
				bnep_rx_frame(s, skb);
			अन्यथा
				kमुक्त_skb(skb);
		पूर्ण

		अगर (sk->sk_state != BT_CONNECTED)
			अवरोध;

		/* TX */
		जबतक ((skb = skb_dequeue(&sk->sk_ग_लिखो_queue)))
			अगर (bnep_tx_frame(s, skb))
				अवरोध;
		netअगर_wake_queue(dev);

		/*
		 * रुको_woken() perक्रमms the necessary memory barriers
		 * क्रम us; see the header comment क्रम this primitive.
		 */
		रुको_woken(&रुको, TASK_INTERRUPTIBLE, MAX_SCHEDULE_TIMEOUT);
	पूर्ण
	हटाओ_रुको_queue(sk_sleep(sk), &रुको);

	/* Cleanup session */
	करोwn_ग_लिखो(&bnep_session_sem);

	/* Delete network device */
	unरेजिस्टर_netdev(dev);

	/* Wakeup user-space polling क्रम socket errors */
	s->sock->sk->sk_err = EUNATCH;

	wake_up_पूर्णांकerruptible(sk_sleep(s->sock->sk));

	/* Release the socket */
	fput(s->sock->file);

	__bnep_unlink_session(s);

	up_ग_लिखो(&bnep_session_sem);
	मुक्त_netdev(dev);
	module_put_and_निकास(0);
	वापस 0;
पूर्ण

अटल काष्ठा device *bnep_get_device(काष्ठा bnep_session *session)
अणु
	काष्ठा l2cap_conn *conn = l2cap_pi(session->sock->sk)->chan->conn;

	अगर (!conn || !conn->hcon)
		वापस शून्य;

	वापस &conn->hcon->dev;
पूर्ण

अटल काष्ठा device_type bnep_type = अणु
	.name	= "bluetooth",
पूर्ण;

पूर्णांक bnep_add_connection(काष्ठा bnep_connadd_req *req, काष्ठा socket *sock)
अणु
	u32 valid_flags = BIT(BNEP_SETUP_RESPONSE);
	काष्ठा net_device *dev;
	काष्ठा bnep_session *s, *ss;
	u8 dst[ETH_ALEN], src[ETH_ALEN];
	पूर्णांक err;

	BT_DBG("");

	अगर (!l2cap_is_socket(sock))
		वापस -EBADFD;

	अगर (req->flags & ~valid_flags)
		वापस -EINVAL;

	baswap((व्योम *) dst, &l2cap_pi(sock->sk)->chan->dst);
	baswap((व्योम *) src, &l2cap_pi(sock->sk)->chan->src);

	/* session काष्ठा allocated as निजी part of net_device */
	dev = alloc_netdev(माप(काष्ठा bnep_session),
			   (*req->device) ? req->device : "bnep%d",
			   NET_NAME_UNKNOWN,
			   bnep_net_setup);
	अगर (!dev)
		वापस -ENOMEM;

	करोwn_ग_लिखो(&bnep_session_sem);

	ss = __bnep_get_session(dst);
	अगर (ss && ss->state == BT_CONNECTED) अणु
		err = -EEXIST;
		जाओ failed;
	पूर्ण

	s = netdev_priv(dev);

	/* This is rx header thereक्रमe addresses are swapped.
	 * ie. eh.h_dest is our local address. */
	स_नकल(s->eh.h_dest,   &src, ETH_ALEN);
	स_नकल(s->eh.h_source, &dst, ETH_ALEN);
	स_नकल(dev->dev_addr, s->eh.h_dest, ETH_ALEN);

	s->dev   = dev;
	s->sock  = sock;
	s->role  = req->role;
	s->state = BT_CONNECTED;
	s->flags = req->flags;

	s->msg.msg_flags = MSG_NOSIGNAL;

#अगर_घोषित CONFIG_BT_BNEP_MC_FILTER
	/* Set शेष mc filter to not filter out any mc addresses
	 * as defined in the BNEP specअगरication (revision 0.95a)
	 * http://grouper.ieee.org/groups/802/15/Bluetooth/BNEP.pdf
	 */
	s->mc_filter = ~0LL;
#पूर्ण_अगर

#अगर_घोषित CONFIG_BT_BNEP_PROTO_FILTER
	/* Set शेष protocol filter */
	bnep_set_शेष_proto_filter(s);
#पूर्ण_अगर

	SET_NETDEV_DEV(dev, bnep_get_device(s));
	SET_NETDEV_DEVTYPE(dev, &bnep_type);

	err = रेजिस्टर_netdev(dev);
	अगर (err)
		जाओ failed;

	__bnep_link_session(s);

	__module_get(THIS_MODULE);
	s->task = kthपढ़ो_run(bnep_session, s, "kbnepd %s", dev->name);
	अगर (IS_ERR(s->task)) अणु
		/* Session thपढ़ो start failed, gotta cleanup. */
		module_put(THIS_MODULE);
		unरेजिस्टर_netdev(dev);
		__bnep_unlink_session(s);
		err = PTR_ERR(s->task);
		जाओ failed;
	पूर्ण

	up_ग_लिखो(&bnep_session_sem);
	म_नकल(req->device, dev->name);
	वापस 0;

failed:
	up_ग_लिखो(&bnep_session_sem);
	मुक्त_netdev(dev);
	वापस err;
पूर्ण

पूर्णांक bnep_del_connection(काष्ठा bnep_conndel_req *req)
अणु
	u32 valid_flags = 0;
	काष्ठा bnep_session *s;
	पूर्णांक  err = 0;

	BT_DBG("");

	अगर (req->flags & ~valid_flags)
		वापस -EINVAL;

	करोwn_पढ़ो(&bnep_session_sem);

	s = __bnep_get_session(req->dst);
	अगर (s) अणु
		atomic_inc(&s->terminate);
		wake_up_पूर्णांकerruptible(sk_sleep(s->sock->sk));
	पूर्ण अन्यथा
		err = -ENOENT;

	up_पढ़ो(&bnep_session_sem);
	वापस err;
पूर्ण

अटल व्योम __bnep_copy_ci(काष्ठा bnep_conninfo *ci, काष्ठा bnep_session *s)
अणु
	u32 valid_flags = BIT(BNEP_SETUP_RESPONSE);

	स_रखो(ci, 0, माप(*ci));
	स_नकल(ci->dst, s->eh.h_source, ETH_ALEN);
	म_नकल(ci->device, s->dev->name);
	ci->flags = s->flags & valid_flags;
	ci->state = s->state;
	ci->role  = s->role;
पूर्ण

पूर्णांक bnep_get_connlist(काष्ठा bnep_connlist_req *req)
अणु
	काष्ठा bnep_session *s;
	पूर्णांक err = 0, n = 0;

	करोwn_पढ़ो(&bnep_session_sem);

	list_क्रम_each_entry(s, &bnep_session_list, list) अणु
		काष्ठा bnep_conninfo ci;

		__bnep_copy_ci(&ci, s);

		अगर (copy_to_user(req->ci, &ci, माप(ci))) अणु
			err = -EFAULT;
			अवरोध;
		पूर्ण

		अगर (++n >= req->cnum)
			अवरोध;

		req->ci++;
	पूर्ण
	req->cnum = n;

	up_पढ़ो(&bnep_session_sem);
	वापस err;
पूर्ण

पूर्णांक bnep_get_conninfo(काष्ठा bnep_conninfo *ci)
अणु
	काष्ठा bnep_session *s;
	पूर्णांक err = 0;

	करोwn_पढ़ो(&bnep_session_sem);

	s = __bnep_get_session(ci->dst);
	अगर (s)
		__bnep_copy_ci(ci, s);
	अन्यथा
		err = -ENOENT;

	up_पढ़ो(&bnep_session_sem);
	वापस err;
पूर्ण

अटल पूर्णांक __init bnep_init(व्योम)
अणु
	अक्षर flt[50] = "";

#अगर_घोषित CONFIG_BT_BNEP_PROTO_FILTER
	म_जोड़ो(flt, "protocol ");
#पूर्ण_अगर

#अगर_घोषित CONFIG_BT_BNEP_MC_FILTER
	म_जोड़ो(flt, "multicast");
#पूर्ण_अगर

	BT_INFO("BNEP (Ethernet Emulation) ver %s", VERSION);
	अगर (flt[0])
		BT_INFO("BNEP filters: %s", flt);

	bnep_sock_init();
	वापस 0;
पूर्ण

अटल व्योम __निकास bnep_निकास(व्योम)
अणु
	bnep_sock_cleanup();
पूर्ण

module_init(bnep_init);
module_निकास(bnep_निकास);

module_param(compress_src, bool, 0644);
MODULE_PARM_DESC(compress_src, "Compress sources headers");

module_param(compress_dst, bool, 0644);
MODULE_PARM_DESC(compress_dst, "Compress destination headers");

MODULE_AUTHOR("Marcel Holtmann <marcel@holtmann.org>");
MODULE_DESCRIPTION("Bluetooth BNEP ver " VERSION);
MODULE_VERSION(VERSION);
MODULE_LICENSE("GPL");
MODULE_ALIAS("bt-proto-4");
