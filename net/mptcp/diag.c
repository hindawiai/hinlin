<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* MPTCP socket monitoring support
 *
 * Copyright (c) 2019 Red Hat
 *
 * Author: Davide Caratti <dcaratti@redhat.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/net.h>
#समावेश <linux/inet_diag.h>
#समावेश <net/netlink.h>
#समावेश <uapi/linux/mptcp.h>
#समावेश "protocol.h"

अटल पूर्णांक subflow_get_info(स्थिर काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा mptcp_subflow_context *sf;
	काष्ठा nlattr *start;
	u32 flags = 0;
	पूर्णांक err;

	start = nla_nest_start_noflag(skb, INET_ULP_INFO_MPTCP);
	अगर (!start)
		वापस -EMSGSIZE;

	rcu_पढ़ो_lock();
	sf = rcu_dereference(inet_csk(sk)->icsk_ulp_data);
	अगर (!sf) अणु
		err = 0;
		जाओ nla_failure;
	पूर्ण

	अगर (sf->mp_capable)
		flags |= MPTCP_SUBFLOW_FLAG_MCAP_REM;
	अगर (sf->request_mptcp)
		flags |= MPTCP_SUBFLOW_FLAG_MCAP_LOC;
	अगर (sf->mp_join)
		flags |= MPTCP_SUBFLOW_FLAG_JOIN_REM;
	अगर (sf->request_join)
		flags |= MPTCP_SUBFLOW_FLAG_JOIN_LOC;
	अगर (sf->backup)
		flags |= MPTCP_SUBFLOW_FLAG_BKUP_REM;
	अगर (sf->request_bkup)
		flags |= MPTCP_SUBFLOW_FLAG_BKUP_LOC;
	अगर (sf->fully_established)
		flags |= MPTCP_SUBFLOW_FLAG_FULLY_ESTABLISHED;
	अगर (sf->conn_finished)
		flags |= MPTCP_SUBFLOW_FLAG_CONNECTED;
	अगर (sf->map_valid)
		flags |= MPTCP_SUBFLOW_FLAG_MAPVALID;

	अगर (nla_put_u32(skb, MPTCP_SUBFLOW_ATTR_TOKEN_REM, sf->remote_token) ||
	    nla_put_u32(skb, MPTCP_SUBFLOW_ATTR_TOKEN_LOC, sf->token) ||
	    nla_put_u32(skb, MPTCP_SUBFLOW_ATTR_RELWRITE_SEQ,
			sf->rel_ग_लिखो_seq) ||
	    nla_put_u64_64bit(skb, MPTCP_SUBFLOW_ATTR_MAP_SEQ, sf->map_seq,
			      MPTCP_SUBFLOW_ATTR_PAD) ||
	    nla_put_u32(skb, MPTCP_SUBFLOW_ATTR_MAP_SFSEQ,
			sf->map_subflow_seq) ||
	    nla_put_u32(skb, MPTCP_SUBFLOW_ATTR_SSN_OFFSET, sf->ssn_offset) ||
	    nla_put_u16(skb, MPTCP_SUBFLOW_ATTR_MAP_DATALEN,
			sf->map_data_len) ||
	    nla_put_u32(skb, MPTCP_SUBFLOW_ATTR_FLAGS, flags) ||
	    nla_put_u8(skb, MPTCP_SUBFLOW_ATTR_ID_REM, sf->remote_id) ||
	    nla_put_u8(skb, MPTCP_SUBFLOW_ATTR_ID_LOC, sf->local_id)) अणु
		err = -EMSGSIZE;
		जाओ nla_failure;
	पूर्ण

	rcu_पढ़ो_unlock();
	nla_nest_end(skb, start);
	वापस 0;

nla_failure:
	rcu_पढ़ो_unlock();
	nla_nest_cancel(skb, start);
	वापस err;
पूर्ण

अटल माप_प्रकार subflow_get_info_size(स्थिर काष्ठा sock *sk)
अणु
	माप_प्रकार size = 0;

	size += nla_total_size(0) +	/* INET_ULP_INFO_MPTCP */
		nla_total_size(4) +	/* MPTCP_SUBFLOW_ATTR_TOKEN_REM */
		nla_total_size(4) +	/* MPTCP_SUBFLOW_ATTR_TOKEN_LOC */
		nla_total_size(4) +	/* MPTCP_SUBFLOW_ATTR_RELWRITE_SEQ */
		nla_total_size_64bit(8) +	/* MPTCP_SUBFLOW_ATTR_MAP_SEQ */
		nla_total_size(4) +	/* MPTCP_SUBFLOW_ATTR_MAP_SFSEQ */
		nla_total_size(2) +	/* MPTCP_SUBFLOW_ATTR_SSN_OFFSET */
		nla_total_size(2) +	/* MPTCP_SUBFLOW_ATTR_MAP_DATALEN */
		nla_total_size(4) +	/* MPTCP_SUBFLOW_ATTR_FLAGS */
		nla_total_size(1) +	/* MPTCP_SUBFLOW_ATTR_ID_REM */
		nla_total_size(1) +	/* MPTCP_SUBFLOW_ATTR_ID_LOC */
		0;
	वापस size;
पूर्ण

व्योम mptcp_diag_subflow_init(काष्ठा tcp_ulp_ops *ops)
अणु
	ops->get_info = subflow_get_info;
	ops->get_info_size = subflow_get_info_size;
पूर्ण
