<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  net/dccp/diag.c
 *
 *  An implementation of the DCCP protocol
 *  Arnalकरो Carvalho de Melo <acme@mandriva.com>
 */


#समावेश <linux/module.h>
#समावेश <linux/inet_diag.h>

#समावेश "ccid.h"
#समावेश "dccp.h"

अटल व्योम dccp_get_info(काष्ठा sock *sk, काष्ठा tcp_info *info)
अणु
	काष्ठा dccp_sock *dp = dccp_sk(sk);
	स्थिर काष्ठा inet_connection_sock *icsk = inet_csk(sk);

	स_रखो(info, 0, माप(*info));

	info->tcpi_state	= sk->sk_state;
	info->tcpi_retransmits	= icsk->icsk_retransmits;
	info->tcpi_probes	= icsk->icsk_probes_out;
	info->tcpi_backoff	= icsk->icsk_backoff;
	info->tcpi_pmtu		= icsk->icsk_pmtu_cookie;

	अगर (dp->dccps_hc_rx_ackvec != शून्य)
		info->tcpi_options |= TCPI_OPT_SACK;

	अगर (dp->dccps_hc_rx_ccid != शून्य)
		ccid_hc_rx_get_info(dp->dccps_hc_rx_ccid, sk, info);

	अगर (dp->dccps_hc_tx_ccid != शून्य)
		ccid_hc_tx_get_info(dp->dccps_hc_tx_ccid, sk, info);
पूर्ण

अटल व्योम dccp_diag_get_info(काष्ठा sock *sk, काष्ठा inet_diag_msg *r,
			       व्योम *_info)
अणु
	r->idiag_rqueue = r->idiag_wqueue = 0;

	अगर (_info != शून्य)
		dccp_get_info(sk, _info);
पूर्ण

अटल व्योम dccp_diag_dump(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb,
			   स्थिर काष्ठा inet_diag_req_v2 *r)
अणु
	inet_diag_dump_icsk(&dccp_hashinfo, skb, cb, r);
पूर्ण

अटल पूर्णांक dccp_diag_dump_one(काष्ठा netlink_callback *cb,
			      स्थिर काष्ठा inet_diag_req_v2 *req)
अणु
	वापस inet_diag_dump_one_icsk(&dccp_hashinfo, cb, req);
पूर्ण

अटल स्थिर काष्ठा inet_diag_handler dccp_diag_handler = अणु
	.dump		 = dccp_diag_dump,
	.dump_one	 = dccp_diag_dump_one,
	.idiag_get_info	 = dccp_diag_get_info,
	.idiag_type	 = IPPROTO_DCCP,
	.idiag_info_size = माप(काष्ठा tcp_info),
पूर्ण;

अटल पूर्णांक __init dccp_diag_init(व्योम)
अणु
	वापस inet_diag_रेजिस्टर(&dccp_diag_handler);
पूर्ण

अटल व्योम __निकास dccp_diag_fini(व्योम)
अणु
	inet_diag_unरेजिस्टर(&dccp_diag_handler);
पूर्ण

module_init(dccp_diag_init);
module_निकास(dccp_diag_fini);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Arnaldo Carvalho de Melo <acme@mandriva.com>");
MODULE_DESCRIPTION("DCCP inet_diag handler");
MODULE_ALIAS_NET_PF_PROTO_TYPE(PF_NETLINK, NETLINK_SOCK_DIAG, 2-33 /* AF_INET - IPPROTO_DCCP */);
