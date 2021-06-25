<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Shared Memory Communications over RDMA (SMC-R) and RoCE
 *
 * Monitoring SMC transport protocol sockets
 *
 * Copyright IBM Corp. 2016
 *
 * Author(s):  Ursula Braun <ubraun@linux.vnet.ibm.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/init.h>
#समावेश <linux/sock_diag.h>
#समावेश <linux/inet_diag.h>
#समावेश <linux/smc_diag.h>
#समावेश <net/netlink.h>
#समावेश <net/smc.h>

#समावेश "smc.h"
#समावेश "smc_core.h"

काष्ठा smc_diag_dump_ctx अणु
	पूर्णांक pos[2];
पूर्ण;

अटल काष्ठा smc_diag_dump_ctx *smc_dump_context(काष्ठा netlink_callback *cb)
अणु
	वापस (काष्ठा smc_diag_dump_ctx *)cb->ctx;
पूर्ण

अटल व्योम smc_diag_msg_common_fill(काष्ठा smc_diag_msg *r, काष्ठा sock *sk)
अणु
	काष्ठा smc_sock *smc = smc_sk(sk);

	स_रखो(r, 0, माप(*r));
	r->diag_family = sk->sk_family;
	sock_diag_save_cookie(sk, r->id.idiag_cookie);
	अगर (!smc->clcsock)
		वापस;
	r->id.idiag_sport = htons(smc->clcsock->sk->sk_num);
	r->id.idiag_dport = smc->clcsock->sk->sk_dport;
	r->id.idiag_अगर = smc->clcsock->sk->sk_bound_dev_अगर;
	अगर (sk->sk_protocol == SMCPROTO_SMC) अणु
		r->id.idiag_src[0] = smc->clcsock->sk->sk_rcv_saddr;
		r->id.idiag_dst[0] = smc->clcsock->sk->sk_daddr;
#अगर IS_ENABLED(CONFIG_IPV6)
	पूर्ण अन्यथा अगर (sk->sk_protocol == SMCPROTO_SMC6) अणु
		स_नकल(&r->id.idiag_src, &smc->clcsock->sk->sk_v6_rcv_saddr,
		       माप(smc->clcsock->sk->sk_v6_rcv_saddr));
		स_नकल(&r->id.idiag_dst, &smc->clcsock->sk->sk_v6_daddr,
		       माप(smc->clcsock->sk->sk_v6_daddr));
#पूर्ण_अगर
	पूर्ण
पूर्ण

अटल पूर्णांक smc_diag_msg_attrs_fill(काष्ठा sock *sk, काष्ठा sk_buff *skb,
				   काष्ठा smc_diag_msg *r,
				   काष्ठा user_namespace *user_ns)
अणु
	अगर (nla_put_u8(skb, SMC_DIAG_SHUTDOWN, sk->sk_shutकरोwn))
		वापस 1;

	r->diag_uid = from_kuid_munged(user_ns, sock_i_uid(sk));
	r->diag_inode = sock_i_ino(sk);
	वापस 0;
पूर्ण

अटल पूर्णांक __smc_diag_dump(काष्ठा sock *sk, काष्ठा sk_buff *skb,
			   काष्ठा netlink_callback *cb,
			   स्थिर काष्ठा smc_diag_req *req,
			   काष्ठा nlattr *bc)
अणु
	काष्ठा smc_sock *smc = smc_sk(sk);
	काष्ठा smc_diag_fallback fallback;
	काष्ठा user_namespace *user_ns;
	काष्ठा smc_diag_msg *r;
	काष्ठा nlmsghdr *nlh;

	nlh = nlmsg_put(skb, NETLINK_CB(cb->skb).portid, cb->nlh->nlmsg_seq,
			cb->nlh->nlmsg_type, माप(*r), NLM_F_MULTI);
	अगर (!nlh)
		वापस -EMSGSIZE;

	r = nlmsg_data(nlh);
	smc_diag_msg_common_fill(r, sk);
	r->diag_state = sk->sk_state;
	अगर (smc->use_fallback)
		r->diag_mode = SMC_DIAG_MODE_FALLBACK_TCP;
	अन्यथा अगर (smc->conn.lgr && smc->conn.lgr->is_smcd)
		r->diag_mode = SMC_DIAG_MODE_SMCD;
	अन्यथा
		r->diag_mode = SMC_DIAG_MODE_SMCR;
	user_ns = sk_user_ns(NETLINK_CB(cb->skb).sk);
	अगर (smc_diag_msg_attrs_fill(sk, skb, r, user_ns))
		जाओ errout;

	fallback.reason = smc->fallback_rsn;
	fallback.peer_diagnosis = smc->peer_diagnosis;
	अगर (nla_put(skb, SMC_DIAG_FALLBACK, माप(fallback), &fallback) < 0)
		जाओ errout;

	अगर ((req->diag_ext & (1 << (SMC_DIAG_CONNINFO - 1))) &&
	    smc->conn.alert_token_local) अणु
		काष्ठा smc_connection *conn = &smc->conn;
		काष्ठा smc_diag_conninfo cinfo = अणु
			.token = conn->alert_token_local,
			.sndbuf_size = conn->sndbuf_desc ?
				conn->sndbuf_desc->len : 0,
			.rmbe_size = conn->rmb_desc ? conn->rmb_desc->len : 0,
			.peer_rmbe_size = conn->peer_rmbe_size,

			.rx_prod.wrap = conn->local_rx_ctrl.prod.wrap,
			.rx_prod.count = conn->local_rx_ctrl.prod.count,
			.rx_cons.wrap = conn->local_rx_ctrl.cons.wrap,
			.rx_cons.count = conn->local_rx_ctrl.cons.count,

			.tx_prod.wrap = conn->local_tx_ctrl.prod.wrap,
			.tx_prod.count = conn->local_tx_ctrl.prod.count,
			.tx_cons.wrap = conn->local_tx_ctrl.cons.wrap,
			.tx_cons.count = conn->local_tx_ctrl.cons.count,

			.tx_prod_flags =
				*(u8 *)&conn->local_tx_ctrl.prod_flags,
			.tx_conn_state_flags =
				*(u8 *)&conn->local_tx_ctrl.conn_state_flags,
			.rx_prod_flags = *(u8 *)&conn->local_rx_ctrl.prod_flags,
			.rx_conn_state_flags =
				*(u8 *)&conn->local_rx_ctrl.conn_state_flags,

			.tx_prep.wrap = conn->tx_curs_prep.wrap,
			.tx_prep.count = conn->tx_curs_prep.count,
			.tx_sent.wrap = conn->tx_curs_sent.wrap,
			.tx_sent.count = conn->tx_curs_sent.count,
			.tx_fin.wrap = conn->tx_curs_fin.wrap,
			.tx_fin.count = conn->tx_curs_fin.count,
		पूर्ण;

		अगर (nla_put(skb, SMC_DIAG_CONNINFO, माप(cinfo), &cinfo) < 0)
			जाओ errout;
	पूर्ण

	अगर (smc->conn.lgr && !smc->conn.lgr->is_smcd &&
	    (req->diag_ext & (1 << (SMC_DIAG_LGRINFO - 1))) &&
	    !list_empty(&smc->conn.lgr->list)) अणु
		काष्ठा smc_diag_lgrinfo linfo = अणु
			.role = smc->conn.lgr->role,
			.lnk[0].ibport = smc->conn.lnk->ibport,
			.lnk[0].link_id = smc->conn.lnk->link_id,
		पूर्ण;

		स_नकल(linfo.lnk[0].ibname,
		       smc->conn.lgr->lnk[0].smcibdev->ibdev->name,
		       माप(smc->conn.lnk->smcibdev->ibdev->name));
		smc_gid_be16_convert(linfo.lnk[0].gid,
				     smc->conn.lnk->gid);
		smc_gid_be16_convert(linfo.lnk[0].peer_gid,
				     smc->conn.lnk->peer_gid);

		अगर (nla_put(skb, SMC_DIAG_LGRINFO, माप(linfo), &linfo) < 0)
			जाओ errout;
	पूर्ण
	अगर (smc->conn.lgr && smc->conn.lgr->is_smcd &&
	    (req->diag_ext & (1 << (SMC_DIAG_DMBINFO - 1))) &&
	    !list_empty(&smc->conn.lgr->list)) अणु
		काष्ठा smc_connection *conn = &smc->conn;
		काष्ठा smcd_diag_dmbinfo dinfo;

		स_रखो(&dinfo, 0, माप(dinfo));

		dinfo.linkid = *((u32 *)conn->lgr->id);
		dinfo.peer_gid = conn->lgr->peer_gid;
		dinfo.my_gid = conn->lgr->smcd->local_gid;
		dinfo.token = conn->rmb_desc->token;
		dinfo.peer_token = conn->peer_token;

		अगर (nla_put(skb, SMC_DIAG_DMBINFO, माप(dinfo), &dinfo) < 0)
			जाओ errout;
	पूर्ण

	nlmsg_end(skb, nlh);
	वापस 0;

errout:
	nlmsg_cancel(skb, nlh);
	वापस -EMSGSIZE;
पूर्ण

अटल पूर्णांक smc_diag_dump_proto(काष्ठा proto *prot, काष्ठा sk_buff *skb,
			       काष्ठा netlink_callback *cb, पूर्णांक p_type)
अणु
	काष्ठा smc_diag_dump_ctx *cb_ctx = smc_dump_context(cb);
	काष्ठा net *net = sock_net(skb->sk);
	पूर्णांक snum = cb_ctx->pos[p_type];
	काष्ठा nlattr *bc = शून्य;
	काष्ठा hlist_head *head;
	पूर्णांक rc = 0, num = 0;
	काष्ठा sock *sk;

	पढ़ो_lock(&prot->h.smc_hash->lock);
	head = &prot->h.smc_hash->ht;
	अगर (hlist_empty(head))
		जाओ out;

	sk_क्रम_each(sk, head) अणु
		अगर (!net_eq(sock_net(sk), net))
			जारी;
		अगर (num < snum)
			जाओ next;
		rc = __smc_diag_dump(sk, skb, cb, nlmsg_data(cb->nlh), bc);
		अगर (rc < 0)
			जाओ out;
next:
		num++;
	पूर्ण

out:
	पढ़ो_unlock(&prot->h.smc_hash->lock);
	cb_ctx->pos[p_type] = num;
	वापस rc;
पूर्ण

अटल पूर्णांक smc_diag_dump(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb)
अणु
	पूर्णांक rc = 0;

	rc = smc_diag_dump_proto(&smc_proto, skb, cb, SMCPROTO_SMC);
	अगर (!rc)
		smc_diag_dump_proto(&smc_proto6, skb, cb, SMCPROTO_SMC6);
	वापस skb->len;
पूर्ण

अटल पूर्णांक smc_diag_handler_dump(काष्ठा sk_buff *skb, काष्ठा nlmsghdr *h)
अणु
	काष्ठा net *net = sock_net(skb->sk);

	अगर (h->nlmsg_type == SOCK_DIAG_BY_FAMILY &&
	    h->nlmsg_flags & NLM_F_DUMP) अणु
		अणु
			काष्ठा netlink_dump_control c = अणु
				.dump = smc_diag_dump,
				.min_dump_alloc = SKB_WITH_OVERHEAD(32768),
			पूर्ण;
			वापस netlink_dump_start(net->diag_nlsk, skb, h, &c);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा sock_diag_handler smc_diag_handler = अणु
	.family = AF_SMC,
	.dump = smc_diag_handler_dump,
पूर्ण;

अटल पूर्णांक __init smc_diag_init(व्योम)
अणु
	वापस sock_diag_रेजिस्टर(&smc_diag_handler);
पूर्ण

अटल व्योम __निकास smc_diag_निकास(व्योम)
अणु
	sock_diag_unरेजिस्टर(&smc_diag_handler);
पूर्ण

module_init(smc_diag_init);
module_निकास(smc_diag_निकास);
MODULE_LICENSE("GPL");
MODULE_ALIAS_NET_PF_PROTO_TYPE(PF_NETLINK, NETLINK_SOCK_DIAG, 43 /* AF_SMC */);
