<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* XDP sockets monitoring support
 *
 * Copyright(c) 2019 Intel Corporation.
 *
 * Author: Bjथघrn Tथघpel <bjorn.topel@पूर्णांकel.com>
 */

#समावेश <linux/module.h>
#समावेश <net/xdp_sock.h>
#समावेश <linux/xdp_diag.h>
#समावेश <linux/sock_diag.h>

#समावेश "xsk_queue.h"
#समावेश "xsk.h"

अटल पूर्णांक xsk_diag_put_info(स्थिर काष्ठा xdp_sock *xs, काष्ठा sk_buff *nlskb)
अणु
	काष्ठा xdp_diag_info di = अणुपूर्ण;

	di.अगरindex = xs->dev ? xs->dev->अगरindex : 0;
	di.queue_id = xs->queue_id;
	वापस nla_put(nlskb, XDP_DIAG_INFO, माप(di), &di);
पूर्ण

अटल पूर्णांक xsk_diag_put_ring(स्थिर काष्ठा xsk_queue *queue, पूर्णांक nl_type,
			     काष्ठा sk_buff *nlskb)
अणु
	काष्ठा xdp_diag_ring dr = अणुपूर्ण;

	dr.entries = queue->nentries;
	वापस nla_put(nlskb, nl_type, माप(dr), &dr);
पूर्ण

अटल पूर्णांक xsk_diag_put_rings_cfg(स्थिर काष्ठा xdp_sock *xs,
				  काष्ठा sk_buff *nlskb)
अणु
	पूर्णांक err = 0;

	अगर (xs->rx)
		err = xsk_diag_put_ring(xs->rx, XDP_DIAG_RX_RING, nlskb);
	अगर (!err && xs->tx)
		err = xsk_diag_put_ring(xs->tx, XDP_DIAG_TX_RING, nlskb);
	वापस err;
पूर्ण

अटल पूर्णांक xsk_diag_put_umem(स्थिर काष्ठा xdp_sock *xs, काष्ठा sk_buff *nlskb)
अणु
	काष्ठा xsk_buff_pool *pool = xs->pool;
	काष्ठा xdp_umem *umem = xs->umem;
	काष्ठा xdp_diag_umem du = अणुपूर्ण;
	पूर्णांक err;

	अगर (!umem)
		वापस 0;

	du.id = umem->id;
	du.size = umem->size;
	du.num_pages = umem->npgs;
	du.chunk_size = umem->chunk_size;
	du.headroom = umem->headroom;
	du.अगरindex = (pool && pool->netdev) ? pool->netdev->अगरindex : 0;
	du.queue_id = pool ? pool->queue_id : 0;
	du.flags = 0;
	अगर (umem->zc)
		du.flags |= XDP_DU_F_ZEROCOPY;
	du.refs = refcount_पढ़ो(&umem->users);

	err = nla_put(nlskb, XDP_DIAG_UMEM, माप(du), &du);
	अगर (!err && pool && pool->fq)
		err = xsk_diag_put_ring(pool->fq,
					XDP_DIAG_UMEM_FILL_RING, nlskb);
	अगर (!err && pool && pool->cq)
		err = xsk_diag_put_ring(pool->cq,
					XDP_DIAG_UMEM_COMPLETION_RING, nlskb);
	वापस err;
पूर्ण

अटल पूर्णांक xsk_diag_put_stats(स्थिर काष्ठा xdp_sock *xs, काष्ठा sk_buff *nlskb)
अणु
	काष्ठा xdp_diag_stats du = अणुपूर्ण;

	du.n_rx_dropped = xs->rx_dropped;
	du.n_rx_invalid = xskq_nb_invalid_descs(xs->rx);
	du.n_rx_full = xs->rx_queue_full;
	du.n_fill_ring_empty = xs->pool ? xskq_nb_queue_empty_descs(xs->pool->fq) : 0;
	du.n_tx_invalid = xskq_nb_invalid_descs(xs->tx);
	du.n_tx_ring_empty = xskq_nb_queue_empty_descs(xs->tx);
	वापस nla_put(nlskb, XDP_DIAG_STATS, माप(du), &du);
पूर्ण

अटल पूर्णांक xsk_diag_fill(काष्ठा sock *sk, काष्ठा sk_buff *nlskb,
			 काष्ठा xdp_diag_req *req,
			 काष्ठा user_namespace *user_ns,
			 u32 portid, u32 seq, u32 flags, पूर्णांक sk_ino)
अणु
	काष्ठा xdp_sock *xs = xdp_sk(sk);
	काष्ठा xdp_diag_msg *msg;
	काष्ठा nlmsghdr *nlh;

	nlh = nlmsg_put(nlskb, portid, seq, SOCK_DIAG_BY_FAMILY, माप(*msg),
			flags);
	अगर (!nlh)
		वापस -EMSGSIZE;

	msg = nlmsg_data(nlh);
	स_रखो(msg, 0, माप(*msg));
	msg->xdiag_family = AF_XDP;
	msg->xdiag_type = sk->sk_type;
	msg->xdiag_ino = sk_ino;
	sock_diag_save_cookie(sk, msg->xdiag_cookie);

	mutex_lock(&xs->mutex);
	अगर ((req->xdiag_show & XDP_SHOW_INFO) && xsk_diag_put_info(xs, nlskb))
		जाओ out_nlmsg_trim;

	अगर ((req->xdiag_show & XDP_SHOW_INFO) &&
	    nla_put_u32(nlskb, XDP_DIAG_UID,
			from_kuid_munged(user_ns, sock_i_uid(sk))))
		जाओ out_nlmsg_trim;

	अगर ((req->xdiag_show & XDP_SHOW_RING_CFG) &&
	    xsk_diag_put_rings_cfg(xs, nlskb))
		जाओ out_nlmsg_trim;

	अगर ((req->xdiag_show & XDP_SHOW_UMEM) &&
	    xsk_diag_put_umem(xs, nlskb))
		जाओ out_nlmsg_trim;

	अगर ((req->xdiag_show & XDP_SHOW_MEMINFO) &&
	    sock_diag_put_meminfo(sk, nlskb, XDP_DIAG_MEMINFO))
		जाओ out_nlmsg_trim;

	अगर ((req->xdiag_show & XDP_SHOW_STATS) &&
	    xsk_diag_put_stats(xs, nlskb))
		जाओ out_nlmsg_trim;

	mutex_unlock(&xs->mutex);
	nlmsg_end(nlskb, nlh);
	वापस 0;

out_nlmsg_trim:
	mutex_unlock(&xs->mutex);
	nlmsg_cancel(nlskb, nlh);
	वापस -EMSGSIZE;
पूर्ण

अटल पूर्णांक xsk_diag_dump(काष्ठा sk_buff *nlskb, काष्ठा netlink_callback *cb)
अणु
	काष्ठा xdp_diag_req *req = nlmsg_data(cb->nlh);
	काष्ठा net *net = sock_net(nlskb->sk);
	पूर्णांक num = 0, s_num = cb->args[0];
	काष्ठा sock *sk;

	mutex_lock(&net->xdp.lock);

	sk_क्रम_each(sk, &net->xdp.list) अणु
		अगर (!net_eq(sock_net(sk), net))
			जारी;
		अगर (num++ < s_num)
			जारी;

		अगर (xsk_diag_fill(sk, nlskb, req,
				  sk_user_ns(NETLINK_CB(cb->skb).sk),
				  NETLINK_CB(cb->skb).portid,
				  cb->nlh->nlmsg_seq, NLM_F_MULTI,
				  sock_i_ino(sk)) < 0) अणु
			num--;
			अवरोध;
		पूर्ण
	पूर्ण

	mutex_unlock(&net->xdp.lock);
	cb->args[0] = num;
	वापस nlskb->len;
पूर्ण

अटल पूर्णांक xsk_diag_handler_dump(काष्ठा sk_buff *nlskb, काष्ठा nlmsghdr *hdr)
अणु
	काष्ठा netlink_dump_control c = अणु .dump = xsk_diag_dump पूर्ण;
	पूर्णांक hdrlen = माप(काष्ठा xdp_diag_req);
	काष्ठा net *net = sock_net(nlskb->sk);

	अगर (nlmsg_len(hdr) < hdrlen)
		वापस -EINVAL;

	अगर (!(hdr->nlmsg_flags & NLM_F_DUMP))
		वापस -EOPNOTSUPP;

	वापस netlink_dump_start(net->diag_nlsk, nlskb, hdr, &c);
पूर्ण

अटल स्थिर काष्ठा sock_diag_handler xsk_diag_handler = अणु
	.family = AF_XDP,
	.dump = xsk_diag_handler_dump,
पूर्ण;

अटल पूर्णांक __init xsk_diag_init(व्योम)
अणु
	वापस sock_diag_रेजिस्टर(&xsk_diag_handler);
पूर्ण

अटल व्योम __निकास xsk_diag_निकास(व्योम)
अणु
	sock_diag_unरेजिस्टर(&xsk_diag_handler);
पूर्ण

module_init(xsk_diag_init);
module_निकास(xsk_diag_निकास);
MODULE_LICENSE("GPL");
MODULE_ALIAS_NET_PF_PROTO_TYPE(PF_NETLINK, NETLINK_SOCK_DIAG, AF_XDP);
