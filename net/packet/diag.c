<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#समावेश <linux/module.h>
#समावेश <linux/sock_diag.h>
#समावेश <linux/net.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/packet_diag.h>
#समावेश <linux/percpu.h>
#समावेश <net/net_namespace.h>
#समावेश <net/sock.h>

#समावेश "internal.h"

अटल पूर्णांक pdiag_put_info(स्थिर काष्ठा packet_sock *po, काष्ठा sk_buff *nlskb)
अणु
	काष्ठा packet_diag_info pinfo;

	pinfo.pdi_index = po->अगरindex;
	pinfo.pdi_version = po->tp_version;
	pinfo.pdi_reserve = po->tp_reserve;
	pinfo.pdi_copy_thresh = po->copy_thresh;
	pinfo.pdi_tstamp = po->tp_tstamp;

	pinfo.pdi_flags = 0;
	अगर (po->running)
		pinfo.pdi_flags |= PDI_RUNNING;
	अगर (po->auxdata)
		pinfo.pdi_flags |= PDI_AUXDATA;
	अगर (po->origdev)
		pinfo.pdi_flags |= PDI_ORIGDEV;
	अगर (po->has_vnet_hdr)
		pinfo.pdi_flags |= PDI_VNETHDR;
	अगर (po->tp_loss)
		pinfo.pdi_flags |= PDI_LOSS;

	वापस nla_put(nlskb, PACKET_DIAG_INFO, माप(pinfo), &pinfo);
पूर्ण

अटल पूर्णांक pdiag_put_mclist(स्थिर काष्ठा packet_sock *po, काष्ठा sk_buff *nlskb)
अणु
	काष्ठा nlattr *mca;
	काष्ठा packet_mclist *ml;

	mca = nla_nest_start_noflag(nlskb, PACKET_DIAG_MCLIST);
	अगर (!mca)
		वापस -EMSGSIZE;

	rtnl_lock();
	क्रम (ml = po->mclist; ml; ml = ml->next) अणु
		काष्ठा packet_diag_mclist *dml;

		dml = nla_reserve_nohdr(nlskb, माप(*dml));
		अगर (!dml) अणु
			rtnl_unlock();
			nla_nest_cancel(nlskb, mca);
			वापस -EMSGSIZE;
		पूर्ण

		dml->pdmc_index = ml->अगरindex;
		dml->pdmc_type = ml->type;
		dml->pdmc_alen = ml->alen;
		dml->pdmc_count = ml->count;
		BUILD_BUG_ON(माप(dml->pdmc_addr) != माप(ml->addr));
		स_नकल(dml->pdmc_addr, ml->addr, माप(ml->addr));
	पूर्ण

	rtnl_unlock();
	nla_nest_end(nlskb, mca);

	वापस 0;
पूर्ण

अटल पूर्णांक pdiag_put_ring(काष्ठा packet_ring_buffer *ring, पूर्णांक ver, पूर्णांक nl_type,
		काष्ठा sk_buff *nlskb)
अणु
	काष्ठा packet_diag_ring pdr;

	अगर (!ring->pg_vec)
		वापस 0;

	pdr.pdr_block_size = ring->pg_vec_pages << PAGE_SHIFT;
	pdr.pdr_block_nr = ring->pg_vec_len;
	pdr.pdr_frame_size = ring->frame_size;
	pdr.pdr_frame_nr = ring->frame_max + 1;

	अगर (ver > TPACKET_V2) अणु
		pdr.pdr_retire_पंचांगo = ring->prb_bdqc.retire_blk_tov;
		pdr.pdr_माप_priv = ring->prb_bdqc.blk_माप_priv;
		pdr.pdr_features = ring->prb_bdqc.feature_req_word;
	पूर्ण अन्यथा अणु
		pdr.pdr_retire_पंचांगo = 0;
		pdr.pdr_माप_priv = 0;
		pdr.pdr_features = 0;
	पूर्ण

	वापस nla_put(nlskb, nl_type, माप(pdr), &pdr);
पूर्ण

अटल पूर्णांक pdiag_put_rings_cfg(काष्ठा packet_sock *po, काष्ठा sk_buff *skb)
अणु
	पूर्णांक ret;

	mutex_lock(&po->pg_vec_lock);
	ret = pdiag_put_ring(&po->rx_ring, po->tp_version,
			PACKET_DIAG_RX_RING, skb);
	अगर (!ret)
		ret = pdiag_put_ring(&po->tx_ring, po->tp_version,
				PACKET_DIAG_TX_RING, skb);
	mutex_unlock(&po->pg_vec_lock);

	वापस ret;
पूर्ण

अटल पूर्णांक pdiag_put_fanout(काष्ठा packet_sock *po, काष्ठा sk_buff *nlskb)
अणु
	पूर्णांक ret = 0;

	mutex_lock(&fanout_mutex);
	अगर (po->fanout) अणु
		u32 val;

		val = (u32)po->fanout->id | ((u32)po->fanout->type << 16);
		ret = nla_put_u32(nlskb, PACKET_DIAG_FANOUT, val);
	पूर्ण
	mutex_unlock(&fanout_mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक sk_diag_fill(काष्ठा sock *sk, काष्ठा sk_buff *skb,
			काष्ठा packet_diag_req *req,
			bool may_report_filterinfo,
			काष्ठा user_namespace *user_ns,
			u32 portid, u32 seq, u32 flags, पूर्णांक sk_ino)
अणु
	काष्ठा nlmsghdr *nlh;
	काष्ठा packet_diag_msg *rp;
	काष्ठा packet_sock *po = pkt_sk(sk);

	nlh = nlmsg_put(skb, portid, seq, SOCK_DIAG_BY_FAMILY, माप(*rp), flags);
	अगर (!nlh)
		वापस -EMSGSIZE;

	rp = nlmsg_data(nlh);
	rp->pdiag_family = AF_PACKET;
	rp->pdiag_type = sk->sk_type;
	rp->pdiag_num = ntohs(po->num);
	rp->pdiag_ino = sk_ino;
	sock_diag_save_cookie(sk, rp->pdiag_cookie);

	अगर ((req->pdiag_show & PACKET_SHOW_INFO) &&
			pdiag_put_info(po, skb))
		जाओ out_nlmsg_trim;

	अगर ((req->pdiag_show & PACKET_SHOW_INFO) &&
	    nla_put_u32(skb, PACKET_DIAG_UID,
			from_kuid_munged(user_ns, sock_i_uid(sk))))
		जाओ out_nlmsg_trim;

	अगर ((req->pdiag_show & PACKET_SHOW_MCLIST) &&
			pdiag_put_mclist(po, skb))
		जाओ out_nlmsg_trim;

	अगर ((req->pdiag_show & PACKET_SHOW_RING_CFG) &&
			pdiag_put_rings_cfg(po, skb))
		जाओ out_nlmsg_trim;

	अगर ((req->pdiag_show & PACKET_SHOW_FANOUT) &&
			pdiag_put_fanout(po, skb))
		जाओ out_nlmsg_trim;

	अगर ((req->pdiag_show & PACKET_SHOW_MEMINFO) &&
	    sock_diag_put_meminfo(sk, skb, PACKET_DIAG_MEMINFO))
		जाओ out_nlmsg_trim;

	अगर ((req->pdiag_show & PACKET_SHOW_FILTER) &&
	    sock_diag_put_filterinfo(may_report_filterinfo, sk, skb,
				     PACKET_DIAG_FILTER))
		जाओ out_nlmsg_trim;

	nlmsg_end(skb, nlh);
	वापस 0;

out_nlmsg_trim:
	nlmsg_cancel(skb, nlh);
	वापस -EMSGSIZE;
पूर्ण

अटल पूर्णांक packet_diag_dump(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb)
अणु
	पूर्णांक num = 0, s_num = cb->args[0];
	काष्ठा packet_diag_req *req;
	काष्ठा net *net;
	काष्ठा sock *sk;
	bool may_report_filterinfo;

	net = sock_net(skb->sk);
	req = nlmsg_data(cb->nlh);
	may_report_filterinfo = netlink_net_capable(cb->skb, CAP_NET_ADMIN);

	mutex_lock(&net->packet.sklist_lock);
	sk_क्रम_each(sk, &net->packet.sklist) अणु
		अगर (!net_eq(sock_net(sk), net))
			जारी;
		अगर (num < s_num)
			जाओ next;

		अगर (sk_diag_fill(sk, skb, req,
				 may_report_filterinfo,
				 sk_user_ns(NETLINK_CB(cb->skb).sk),
				 NETLINK_CB(cb->skb).portid,
				 cb->nlh->nlmsg_seq, NLM_F_MULTI,
				 sock_i_ino(sk)) < 0)
			जाओ करोne;
next:
		num++;
	पूर्ण
करोne:
	mutex_unlock(&net->packet.sklist_lock);
	cb->args[0] = num;

	वापस skb->len;
पूर्ण

अटल पूर्णांक packet_diag_handler_dump(काष्ठा sk_buff *skb, काष्ठा nlmsghdr *h)
अणु
	पूर्णांक hdrlen = माप(काष्ठा packet_diag_req);
	काष्ठा net *net = sock_net(skb->sk);
	काष्ठा packet_diag_req *req;

	अगर (nlmsg_len(h) < hdrlen)
		वापस -EINVAL;

	req = nlmsg_data(h);
	/* Make it possible to support protocol filtering later */
	अगर (req->sdiag_protocol)
		वापस -EINVAL;

	अगर (h->nlmsg_flags & NLM_F_DUMP) अणु
		काष्ठा netlink_dump_control c = अणु
			.dump = packet_diag_dump,
		पूर्ण;
		वापस netlink_dump_start(net->diag_nlsk, skb, h, &c);
	पूर्ण अन्यथा
		वापस -EOPNOTSUPP;
पूर्ण

अटल स्थिर काष्ठा sock_diag_handler packet_diag_handler = अणु
	.family = AF_PACKET,
	.dump = packet_diag_handler_dump,
पूर्ण;

अटल पूर्णांक __init packet_diag_init(व्योम)
अणु
	वापस sock_diag_रेजिस्टर(&packet_diag_handler);
पूर्ण

अटल व्योम __निकास packet_diag_निकास(व्योम)
अणु
	sock_diag_unरेजिस्टर(&packet_diag_handler);
पूर्ण

module_init(packet_diag_init);
module_निकास(packet_diag_निकास);
MODULE_LICENSE("GPL");
MODULE_ALIAS_NET_PF_PROTO_TYPE(PF_NETLINK, NETLINK_SOCK_DIAG, 17 /* AF_PACKET */);
