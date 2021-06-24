<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* L2TP netlink layer, क्रम management
 *
 * Copyright (c) 2008,2009,2010 Katalix Systems Ltd
 *
 * Partly based on the IrDA nelink implementation
 * (see net/irda/irnetlink.c) which is:
 * Copyright (c) 2007 Samuel Ortiz <samuel@sortiz.org>
 * which is in turn partly based on the wireless netlink code:
 * Copyright 2006 Johannes Berg <johannes@sipsolutions.net>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <net/sock.h>
#समावेश <net/genetlink.h>
#समावेश <net/udp.h>
#समावेश <linux/in.h>
#समावेश <linux/udp.h>
#समावेश <linux/socket.h>
#समावेश <linux/module.h>
#समावेश <linux/list.h>
#समावेश <net/net_namespace.h>

#समावेश <linux/l2tp.h>

#समावेश "l2tp_core.h"

अटल काष्ठा genl_family l2tp_nl_family;

अटल स्थिर काष्ठा genl_multicast_group l2tp_multicast_group[] = अणु
	अणु
		.name = L2TP_GENL_MCGROUP,
	पूर्ण,
पूर्ण;

अटल पूर्णांक l2tp_nl_tunnel_send(काष्ठा sk_buff *skb, u32 portid, u32 seq,
			       पूर्णांक flags, काष्ठा l2tp_tunnel *tunnel, u8 cmd);
अटल पूर्णांक l2tp_nl_session_send(काष्ठा sk_buff *skb, u32 portid, u32 seq,
				पूर्णांक flags, काष्ठा l2tp_session *session,
				u8 cmd);

/* Accessed under genl lock */
अटल स्थिर काष्ठा l2tp_nl_cmd_ops *l2tp_nl_cmd_ops[__L2TP_PWTYPE_MAX];

अटल काष्ठा l2tp_session *l2tp_nl_session_get(काष्ठा genl_info *info)
अणु
	u32 tunnel_id;
	u32 session_id;
	अक्षर *अगरname;
	काष्ठा l2tp_tunnel *tunnel;
	काष्ठा l2tp_session *session = शून्य;
	काष्ठा net *net = genl_info_net(info);

	अगर (info->attrs[L2TP_ATTR_IFNAME]) अणु
		अगरname = nla_data(info->attrs[L2TP_ATTR_IFNAME]);
		session = l2tp_session_get_by_अगरname(net, अगरname);
	पूर्ण अन्यथा अगर ((info->attrs[L2TP_ATTR_SESSION_ID]) &&
		   (info->attrs[L2TP_ATTR_CONN_ID])) अणु
		tunnel_id = nla_get_u32(info->attrs[L2TP_ATTR_CONN_ID]);
		session_id = nla_get_u32(info->attrs[L2TP_ATTR_SESSION_ID]);
		tunnel = l2tp_tunnel_get(net, tunnel_id);
		अगर (tunnel) अणु
			session = l2tp_tunnel_get_session(tunnel, session_id);
			l2tp_tunnel_dec_refcount(tunnel);
		पूर्ण
	पूर्ण

	वापस session;
पूर्ण

अटल पूर्णांक l2tp_nl_cmd_noop(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा sk_buff *msg;
	व्योम *hdr;
	पूर्णांक ret = -ENOBUFS;

	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	अगर (!msg) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	hdr = genlmsg_put(msg, info->snd_portid, info->snd_seq,
			  &l2tp_nl_family, 0, L2TP_CMD_NOOP);
	अगर (!hdr) अणु
		ret = -EMSGSIZE;
		जाओ err_out;
	पूर्ण

	genlmsg_end(msg, hdr);

	वापस genlmsg_unicast(genl_info_net(info), msg, info->snd_portid);

err_out:
	nlmsg_मुक्त(msg);

out:
	वापस ret;
पूर्ण

अटल पूर्णांक l2tp_tunnel_notअगरy(काष्ठा genl_family *family,
			      काष्ठा genl_info *info,
			      काष्ठा l2tp_tunnel *tunnel,
			      u8 cmd)
अणु
	काष्ठा sk_buff *msg;
	पूर्णांक ret;

	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	अगर (!msg)
		वापस -ENOMEM;

	ret = l2tp_nl_tunnel_send(msg, info->snd_portid, info->snd_seq,
				  NLM_F_ACK, tunnel, cmd);

	अगर (ret >= 0) अणु
		ret = genlmsg_multicast_allns(family, msg, 0, 0, GFP_ATOMIC);
		/* We करोn't care अगर no one is listening */
		अगर (ret == -ESRCH)
			ret = 0;
		वापस ret;
	पूर्ण

	nlmsg_मुक्त(msg);

	वापस ret;
पूर्ण

अटल पूर्णांक l2tp_session_notअगरy(काष्ठा genl_family *family,
			       काष्ठा genl_info *info,
			       काष्ठा l2tp_session *session,
			       u8 cmd)
अणु
	काष्ठा sk_buff *msg;
	पूर्णांक ret;

	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	अगर (!msg)
		वापस -ENOMEM;

	ret = l2tp_nl_session_send(msg, info->snd_portid, info->snd_seq,
				   NLM_F_ACK, session, cmd);

	अगर (ret >= 0) अणु
		ret = genlmsg_multicast_allns(family, msg, 0, 0, GFP_ATOMIC);
		/* We करोn't care अगर no one is listening */
		अगर (ret == -ESRCH)
			ret = 0;
		वापस ret;
	पूर्ण

	nlmsg_मुक्त(msg);

	वापस ret;
पूर्ण

अटल पूर्णांक l2tp_nl_cmd_tunnel_create_get_addr(काष्ठा nlattr **attrs, काष्ठा l2tp_tunnel_cfg *cfg)
अणु
	अगर (attrs[L2TP_ATTR_UDP_SPORT])
		cfg->local_udp_port = nla_get_u16(attrs[L2TP_ATTR_UDP_SPORT]);
	अगर (attrs[L2TP_ATTR_UDP_DPORT])
		cfg->peer_udp_port = nla_get_u16(attrs[L2TP_ATTR_UDP_DPORT]);
	cfg->use_udp_checksums = nla_get_flag(attrs[L2TP_ATTR_UDP_CSUM]);

	/* Must have either AF_INET or AF_INET6 address क्रम source and destination */
#अगर IS_ENABLED(CONFIG_IPV6)
	अगर (attrs[L2TP_ATTR_IP6_SADDR] && attrs[L2TP_ATTR_IP6_DADDR]) अणु
		cfg->local_ip6 = nla_data(attrs[L2TP_ATTR_IP6_SADDR]);
		cfg->peer_ip6 = nla_data(attrs[L2TP_ATTR_IP6_DADDR]);
		cfg->udp6_zero_tx_checksums = nla_get_flag(attrs[L2TP_ATTR_UDP_ZERO_CSUM6_TX]);
		cfg->udp6_zero_rx_checksums = nla_get_flag(attrs[L2TP_ATTR_UDP_ZERO_CSUM6_RX]);
		वापस 0;
	पूर्ण
#पूर्ण_अगर
	अगर (attrs[L2TP_ATTR_IP_SADDR] && attrs[L2TP_ATTR_IP_DADDR]) अणु
		cfg->local_ip.s_addr = nla_get_in_addr(attrs[L2TP_ATTR_IP_SADDR]);
		cfg->peer_ip.s_addr = nla_get_in_addr(attrs[L2TP_ATTR_IP_DADDR]);
		वापस 0;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक l2tp_nl_cmd_tunnel_create(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	u32 tunnel_id;
	u32 peer_tunnel_id;
	पूर्णांक proto_version;
	पूर्णांक fd = -1;
	पूर्णांक ret = 0;
	काष्ठा l2tp_tunnel_cfg cfg = अणु 0, पूर्ण;
	काष्ठा l2tp_tunnel *tunnel;
	काष्ठा net *net = genl_info_net(info);
	काष्ठा nlattr **attrs = info->attrs;

	अगर (!attrs[L2TP_ATTR_CONN_ID]) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण
	tunnel_id = nla_get_u32(attrs[L2TP_ATTR_CONN_ID]);

	अगर (!attrs[L2TP_ATTR_PEER_CONN_ID]) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण
	peer_tunnel_id = nla_get_u32(attrs[L2TP_ATTR_PEER_CONN_ID]);

	अगर (!attrs[L2TP_ATTR_PROTO_VERSION]) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण
	proto_version = nla_get_u8(attrs[L2TP_ATTR_PROTO_VERSION]);

	अगर (!attrs[L2TP_ATTR_ENCAP_TYPE]) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण
	cfg.encap = nla_get_u16(attrs[L2TP_ATTR_ENCAP_TYPE]);

	/* Managed tunnels take the tunnel socket from userspace.
	 * Unmanaged tunnels must call out the source and destination addresses
	 * क्रम the kernel to create the tunnel socket itself.
	 */
	अगर (attrs[L2TP_ATTR_FD]) अणु
		fd = nla_get_u32(attrs[L2TP_ATTR_FD]);
	पूर्ण अन्यथा अणु
		ret = l2tp_nl_cmd_tunnel_create_get_addr(attrs, &cfg);
		अगर (ret < 0)
			जाओ out;
	पूर्ण

	ret = -EINVAL;
	चयन (cfg.encap) अणु
	हाल L2TP_ENCAPTYPE_UDP:
	हाल L2TP_ENCAPTYPE_IP:
		ret = l2tp_tunnel_create(fd, proto_version, tunnel_id,
					 peer_tunnel_id, &cfg, &tunnel);
		अवरोध;
	पूर्ण

	अगर (ret < 0)
		जाओ out;

	l2tp_tunnel_inc_refcount(tunnel);
	ret = l2tp_tunnel_रेजिस्टर(tunnel, net, &cfg);
	अगर (ret < 0) अणु
		kमुक्त(tunnel);
		जाओ out;
	पूर्ण
	ret = l2tp_tunnel_notअगरy(&l2tp_nl_family, info, tunnel,
				 L2TP_CMD_TUNNEL_CREATE);
	l2tp_tunnel_dec_refcount(tunnel);

out:
	वापस ret;
पूर्ण

अटल पूर्णांक l2tp_nl_cmd_tunnel_delete(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा l2tp_tunnel *tunnel;
	u32 tunnel_id;
	पूर्णांक ret = 0;
	काष्ठा net *net = genl_info_net(info);

	अगर (!info->attrs[L2TP_ATTR_CONN_ID]) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण
	tunnel_id = nla_get_u32(info->attrs[L2TP_ATTR_CONN_ID]);

	tunnel = l2tp_tunnel_get(net, tunnel_id);
	अगर (!tunnel) अणु
		ret = -ENODEV;
		जाओ out;
	पूर्ण

	l2tp_tunnel_notअगरy(&l2tp_nl_family, info,
			   tunnel, L2TP_CMD_TUNNEL_DELETE);

	l2tp_tunnel_delete(tunnel);

	l2tp_tunnel_dec_refcount(tunnel);

out:
	वापस ret;
पूर्ण

अटल पूर्णांक l2tp_nl_cmd_tunnel_modअगरy(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा l2tp_tunnel *tunnel;
	u32 tunnel_id;
	पूर्णांक ret = 0;
	काष्ठा net *net = genl_info_net(info);

	अगर (!info->attrs[L2TP_ATTR_CONN_ID]) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण
	tunnel_id = nla_get_u32(info->attrs[L2TP_ATTR_CONN_ID]);

	tunnel = l2tp_tunnel_get(net, tunnel_id);
	अगर (!tunnel) अणु
		ret = -ENODEV;
		जाओ out;
	पूर्ण

	ret = l2tp_tunnel_notअगरy(&l2tp_nl_family, info,
				 tunnel, L2TP_CMD_TUNNEL_MODIFY);

	l2tp_tunnel_dec_refcount(tunnel);

out:
	वापस ret;
पूर्ण

#अगर IS_ENABLED(CONFIG_IPV6)
अटल पूर्णांक l2tp_nl_tunnel_send_addr6(काष्ठा sk_buff *skb, काष्ठा sock *sk,
				     क्रमागत l2tp_encap_type encap)
अणु
	काष्ठा inet_sock *inet = inet_sk(sk);
	काष्ठा ipv6_pinfo *np = inet6_sk(sk);

	चयन (encap) अणु
	हाल L2TP_ENCAPTYPE_UDP:
		अगर (udp_get_no_check6_tx(sk) &&
		    nla_put_flag(skb, L2TP_ATTR_UDP_ZERO_CSUM6_TX))
			वापस -1;
		अगर (udp_get_no_check6_rx(sk) &&
		    nla_put_flag(skb, L2TP_ATTR_UDP_ZERO_CSUM6_RX))
			वापस -1;
		अगर (nla_put_u16(skb, L2TP_ATTR_UDP_SPORT, ntohs(inet->inet_sport)) ||
		    nla_put_u16(skb, L2TP_ATTR_UDP_DPORT, ntohs(inet->inet_dport)))
			वापस -1;
		fallthrough;
	हाल L2TP_ENCAPTYPE_IP:
		अगर (nla_put_in6_addr(skb, L2TP_ATTR_IP6_SADDR, &np->saddr) ||
		    nla_put_in6_addr(skb, L2TP_ATTR_IP6_DADDR, &sk->sk_v6_daddr))
			वापस -1;
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक l2tp_nl_tunnel_send_addr4(काष्ठा sk_buff *skb, काष्ठा sock *sk,
				     क्रमागत l2tp_encap_type encap)
अणु
	काष्ठा inet_sock *inet = inet_sk(sk);

	चयन (encap) अणु
	हाल L2TP_ENCAPTYPE_UDP:
		अगर (nla_put_u8(skb, L2TP_ATTR_UDP_CSUM, !sk->sk_no_check_tx) ||
		    nla_put_u16(skb, L2TP_ATTR_UDP_SPORT, ntohs(inet->inet_sport)) ||
		    nla_put_u16(skb, L2TP_ATTR_UDP_DPORT, ntohs(inet->inet_dport)))
			वापस -1;
		fallthrough;
	हाल L2TP_ENCAPTYPE_IP:
		अगर (nla_put_in_addr(skb, L2TP_ATTR_IP_SADDR, inet->inet_saddr) ||
		    nla_put_in_addr(skb, L2TP_ATTR_IP_DADDR, inet->inet_daddr))
			वापस -1;
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

/* Append attributes क्रम the tunnel address, handling the dअगरferent attribute types
 * used क्रम dअगरferent tunnel encapsulation and AF_INET v.s. AF_INET6.
 */
अटल पूर्णांक l2tp_nl_tunnel_send_addr(काष्ठा sk_buff *skb, काष्ठा l2tp_tunnel *tunnel)
अणु
	काष्ठा sock *sk = tunnel->sock;

	अगर (!sk)
		वापस 0;

#अगर IS_ENABLED(CONFIG_IPV6)
	अगर (sk->sk_family == AF_INET6)
		वापस l2tp_nl_tunnel_send_addr6(skb, sk, tunnel->encap);
#पूर्ण_अगर
	वापस l2tp_nl_tunnel_send_addr4(skb, sk, tunnel->encap);
पूर्ण

अटल पूर्णांक l2tp_nl_tunnel_send(काष्ठा sk_buff *skb, u32 portid, u32 seq, पूर्णांक flags,
			       काष्ठा l2tp_tunnel *tunnel, u8 cmd)
अणु
	व्योम *hdr;
	काष्ठा nlattr *nest;

	hdr = genlmsg_put(skb, portid, seq, &l2tp_nl_family, flags, cmd);
	अगर (!hdr)
		वापस -EMSGSIZE;

	अगर (nla_put_u8(skb, L2TP_ATTR_PROTO_VERSION, tunnel->version) ||
	    nla_put_u32(skb, L2TP_ATTR_CONN_ID, tunnel->tunnel_id) ||
	    nla_put_u32(skb, L2TP_ATTR_PEER_CONN_ID, tunnel->peer_tunnel_id) ||
	    nla_put_u32(skb, L2TP_ATTR_DEBUG, 0) ||
	    nla_put_u16(skb, L2TP_ATTR_ENCAP_TYPE, tunnel->encap))
		जाओ nla_put_failure;

	nest = nla_nest_start_noflag(skb, L2TP_ATTR_STATS);
	अगर (!nest)
		जाओ nla_put_failure;

	अगर (nla_put_u64_64bit(skb, L2TP_ATTR_TX_PACKETS,
			      atomic_दीर्घ_पढ़ो(&tunnel->stats.tx_packets),
			      L2TP_ATTR_STATS_PAD) ||
	    nla_put_u64_64bit(skb, L2TP_ATTR_TX_BYTES,
			      atomic_दीर्घ_पढ़ो(&tunnel->stats.tx_bytes),
			      L2TP_ATTR_STATS_PAD) ||
	    nla_put_u64_64bit(skb, L2TP_ATTR_TX_ERRORS,
			      atomic_दीर्घ_पढ़ो(&tunnel->stats.tx_errors),
			      L2TP_ATTR_STATS_PAD) ||
	    nla_put_u64_64bit(skb, L2TP_ATTR_RX_PACKETS,
			      atomic_दीर्घ_पढ़ो(&tunnel->stats.rx_packets),
			      L2TP_ATTR_STATS_PAD) ||
	    nla_put_u64_64bit(skb, L2TP_ATTR_RX_BYTES,
			      atomic_दीर्घ_पढ़ो(&tunnel->stats.rx_bytes),
			      L2TP_ATTR_STATS_PAD) ||
	    nla_put_u64_64bit(skb, L2TP_ATTR_RX_SEQ_DISCARDS,
			      atomic_दीर्घ_पढ़ो(&tunnel->stats.rx_seq_discards),
			      L2TP_ATTR_STATS_PAD) ||
	    nla_put_u64_64bit(skb, L2TP_ATTR_RX_COOKIE_DISCARDS,
			      atomic_दीर्घ_पढ़ो(&tunnel->stats.rx_cookie_discards),
			      L2TP_ATTR_STATS_PAD) ||
	    nla_put_u64_64bit(skb, L2TP_ATTR_RX_OOS_PACKETS,
			      atomic_दीर्घ_पढ़ो(&tunnel->stats.rx_oos_packets),
			      L2TP_ATTR_STATS_PAD) ||
	    nla_put_u64_64bit(skb, L2TP_ATTR_RX_ERRORS,
			      atomic_दीर्घ_पढ़ो(&tunnel->stats.rx_errors),
			      L2TP_ATTR_STATS_PAD) ||
	    nla_put_u64_64bit(skb, L2TP_ATTR_RX_INVALID,
			      atomic_दीर्घ_पढ़ो(&tunnel->stats.rx_invalid),
			      L2TP_ATTR_STATS_PAD))
		जाओ nla_put_failure;
	nla_nest_end(skb, nest);

	अगर (l2tp_nl_tunnel_send_addr(skb, tunnel))
		जाओ nla_put_failure;

	genlmsg_end(skb, hdr);
	वापस 0;

nla_put_failure:
	genlmsg_cancel(skb, hdr);
	वापस -1;
पूर्ण

अटल पूर्णांक l2tp_nl_cmd_tunnel_get(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा l2tp_tunnel *tunnel;
	काष्ठा sk_buff *msg;
	u32 tunnel_id;
	पूर्णांक ret = -ENOBUFS;
	काष्ठा net *net = genl_info_net(info);

	अगर (!info->attrs[L2TP_ATTR_CONN_ID]) अणु
		ret = -EINVAL;
		जाओ err;
	पूर्ण

	tunnel_id = nla_get_u32(info->attrs[L2TP_ATTR_CONN_ID]);

	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	अगर (!msg) अणु
		ret = -ENOMEM;
		जाओ err;
	पूर्ण

	tunnel = l2tp_tunnel_get(net, tunnel_id);
	अगर (!tunnel) अणु
		ret = -ENODEV;
		जाओ err_nlmsg;
	पूर्ण

	ret = l2tp_nl_tunnel_send(msg, info->snd_portid, info->snd_seq,
				  NLM_F_ACK, tunnel, L2TP_CMD_TUNNEL_GET);
	अगर (ret < 0)
		जाओ err_nlmsg_tunnel;

	l2tp_tunnel_dec_refcount(tunnel);

	वापस genlmsg_unicast(net, msg, info->snd_portid);

err_nlmsg_tunnel:
	l2tp_tunnel_dec_refcount(tunnel);
err_nlmsg:
	nlmsg_मुक्त(msg);
err:
	वापस ret;
पूर्ण

अटल पूर्णांक l2tp_nl_cmd_tunnel_dump(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb)
अणु
	पूर्णांक ti = cb->args[0];
	काष्ठा l2tp_tunnel *tunnel;
	काष्ठा net *net = sock_net(skb->sk);

	क्रम (;;) अणु
		tunnel = l2tp_tunnel_get_nth(net, ti);
		अगर (!tunnel)
			जाओ out;

		अगर (l2tp_nl_tunnel_send(skb, NETLINK_CB(cb->skb).portid,
					cb->nlh->nlmsg_seq, NLM_F_MULTI,
					tunnel, L2TP_CMD_TUNNEL_GET) < 0) अणु
			l2tp_tunnel_dec_refcount(tunnel);
			जाओ out;
		पूर्ण
		l2tp_tunnel_dec_refcount(tunnel);

		ti++;
	पूर्ण

out:
	cb->args[0] = ti;

	वापस skb->len;
पूर्ण

अटल पूर्णांक l2tp_nl_cmd_session_create(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	u32 tunnel_id = 0;
	u32 session_id;
	u32 peer_session_id;
	पूर्णांक ret = 0;
	काष्ठा l2tp_tunnel *tunnel;
	काष्ठा l2tp_session *session;
	काष्ठा l2tp_session_cfg cfg = अणु 0, पूर्ण;
	काष्ठा net *net = genl_info_net(info);

	अगर (!info->attrs[L2TP_ATTR_CONN_ID]) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	tunnel_id = nla_get_u32(info->attrs[L2TP_ATTR_CONN_ID]);
	tunnel = l2tp_tunnel_get(net, tunnel_id);
	अगर (!tunnel) अणु
		ret = -ENODEV;
		जाओ out;
	पूर्ण

	अगर (!info->attrs[L2TP_ATTR_SESSION_ID]) अणु
		ret = -EINVAL;
		जाओ out_tunnel;
	पूर्ण
	session_id = nla_get_u32(info->attrs[L2TP_ATTR_SESSION_ID]);

	अगर (!info->attrs[L2TP_ATTR_PEER_SESSION_ID]) अणु
		ret = -EINVAL;
		जाओ out_tunnel;
	पूर्ण
	peer_session_id = nla_get_u32(info->attrs[L2TP_ATTR_PEER_SESSION_ID]);

	अगर (!info->attrs[L2TP_ATTR_PW_TYPE]) अणु
		ret = -EINVAL;
		जाओ out_tunnel;
	पूर्ण
	cfg.pw_type = nla_get_u16(info->attrs[L2TP_ATTR_PW_TYPE]);
	अगर (cfg.pw_type >= __L2TP_PWTYPE_MAX) अणु
		ret = -EINVAL;
		जाओ out_tunnel;
	पूर्ण

	/* L2TPv2 only accepts PPP pseuकरो-wires */
	अगर (tunnel->version == 2 && cfg.pw_type != L2TP_PWTYPE_PPP) अणु
		ret = -EPROTONOSUPPORT;
		जाओ out_tunnel;
	पूर्ण

	अगर (tunnel->version > 2) अणु
		अगर (info->attrs[L2TP_ATTR_L2SPEC_TYPE]) अणु
			cfg.l2specअगरic_type = nla_get_u8(info->attrs[L2TP_ATTR_L2SPEC_TYPE]);
			अगर (cfg.l2specअगरic_type != L2TP_L2SPECTYPE_DEFAULT &&
			    cfg.l2specअगरic_type != L2TP_L2SPECTYPE_NONE) अणु
				ret = -EINVAL;
				जाओ out_tunnel;
			पूर्ण
		पूर्ण अन्यथा अणु
			cfg.l2specअगरic_type = L2TP_L2SPECTYPE_DEFAULT;
		पूर्ण

		अगर (info->attrs[L2TP_ATTR_COOKIE]) अणु
			u16 len = nla_len(info->attrs[L2TP_ATTR_COOKIE]);

			अगर (len > 8) अणु
				ret = -EINVAL;
				जाओ out_tunnel;
			पूर्ण
			cfg.cookie_len = len;
			स_नकल(&cfg.cookie[0], nla_data(info->attrs[L2TP_ATTR_COOKIE]), len);
		पूर्ण
		अगर (info->attrs[L2TP_ATTR_PEER_COOKIE]) अणु
			u16 len = nla_len(info->attrs[L2TP_ATTR_PEER_COOKIE]);

			अगर (len > 8) अणु
				ret = -EINVAL;
				जाओ out_tunnel;
			पूर्ण
			cfg.peer_cookie_len = len;
			स_नकल(&cfg.peer_cookie[0], nla_data(info->attrs[L2TP_ATTR_PEER_COOKIE]), len);
		पूर्ण
		अगर (info->attrs[L2TP_ATTR_IFNAME])
			cfg.अगरname = nla_data(info->attrs[L2TP_ATTR_IFNAME]);
	पूर्ण

	अगर (info->attrs[L2TP_ATTR_RECV_SEQ])
		cfg.recv_seq = nla_get_u8(info->attrs[L2TP_ATTR_RECV_SEQ]);

	अगर (info->attrs[L2TP_ATTR_SEND_SEQ])
		cfg.send_seq = nla_get_u8(info->attrs[L2TP_ATTR_SEND_SEQ]);

	अगर (info->attrs[L2TP_ATTR_LNS_MODE])
		cfg.lns_mode = nla_get_u8(info->attrs[L2TP_ATTR_LNS_MODE]);

	अगर (info->attrs[L2TP_ATTR_RECV_TIMEOUT])
		cfg.reorder_समयout = nla_get_msecs(info->attrs[L2TP_ATTR_RECV_TIMEOUT]);

#अगर_घोषित CONFIG_MODULES
	अगर (!l2tp_nl_cmd_ops[cfg.pw_type]) अणु
		genl_unlock();
		request_module("net-l2tp-type-%u", cfg.pw_type);
		genl_lock();
	पूर्ण
#पूर्ण_अगर
	अगर (!l2tp_nl_cmd_ops[cfg.pw_type] || !l2tp_nl_cmd_ops[cfg.pw_type]->session_create) अणु
		ret = -EPROTONOSUPPORT;
		जाओ out_tunnel;
	पूर्ण

	ret = l2tp_nl_cmd_ops[cfg.pw_type]->session_create(net, tunnel,
							   session_id,
							   peer_session_id,
							   &cfg);

	अगर (ret >= 0) अणु
		session = l2tp_tunnel_get_session(tunnel, session_id);
		अगर (session) अणु
			ret = l2tp_session_notअगरy(&l2tp_nl_family, info, session,
						  L2TP_CMD_SESSION_CREATE);
			l2tp_session_dec_refcount(session);
		पूर्ण
	पूर्ण

out_tunnel:
	l2tp_tunnel_dec_refcount(tunnel);
out:
	वापस ret;
पूर्ण

अटल पूर्णांक l2tp_nl_cmd_session_delete(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	पूर्णांक ret = 0;
	काष्ठा l2tp_session *session;
	u16 pw_type;

	session = l2tp_nl_session_get(info);
	अगर (!session) अणु
		ret = -ENODEV;
		जाओ out;
	पूर्ण

	l2tp_session_notअगरy(&l2tp_nl_family, info,
			    session, L2TP_CMD_SESSION_DELETE);

	pw_type = session->pwtype;
	अगर (pw_type < __L2TP_PWTYPE_MAX)
		अगर (l2tp_nl_cmd_ops[pw_type] && l2tp_nl_cmd_ops[pw_type]->session_delete)
			l2tp_nl_cmd_ops[pw_type]->session_delete(session);

	l2tp_session_dec_refcount(session);

out:
	वापस ret;
पूर्ण

अटल पूर्णांक l2tp_nl_cmd_session_modअगरy(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	पूर्णांक ret = 0;
	काष्ठा l2tp_session *session;

	session = l2tp_nl_session_get(info);
	अगर (!session) अणु
		ret = -ENODEV;
		जाओ out;
	पूर्ण

	अगर (info->attrs[L2TP_ATTR_RECV_SEQ])
		session->recv_seq = nla_get_u8(info->attrs[L2TP_ATTR_RECV_SEQ]);

	अगर (info->attrs[L2TP_ATTR_SEND_SEQ]) अणु
		session->send_seq = nla_get_u8(info->attrs[L2TP_ATTR_SEND_SEQ]);
		l2tp_session_set_header_len(session, session->tunnel->version);
	पूर्ण

	अगर (info->attrs[L2TP_ATTR_LNS_MODE])
		session->lns_mode = nla_get_u8(info->attrs[L2TP_ATTR_LNS_MODE]);

	अगर (info->attrs[L2TP_ATTR_RECV_TIMEOUT])
		session->reorder_समयout = nla_get_msecs(info->attrs[L2TP_ATTR_RECV_TIMEOUT]);

	ret = l2tp_session_notअगरy(&l2tp_nl_family, info,
				  session, L2TP_CMD_SESSION_MODIFY);

	l2tp_session_dec_refcount(session);

out:
	वापस ret;
पूर्ण

अटल पूर्णांक l2tp_nl_session_send(काष्ठा sk_buff *skb, u32 portid, u32 seq, पूर्णांक flags,
				काष्ठा l2tp_session *session, u8 cmd)
अणु
	व्योम *hdr;
	काष्ठा nlattr *nest;
	काष्ठा l2tp_tunnel *tunnel = session->tunnel;

	hdr = genlmsg_put(skb, portid, seq, &l2tp_nl_family, flags, cmd);
	अगर (!hdr)
		वापस -EMSGSIZE;

	अगर (nla_put_u32(skb, L2TP_ATTR_CONN_ID, tunnel->tunnel_id) ||
	    nla_put_u32(skb, L2TP_ATTR_SESSION_ID, session->session_id) ||
	    nla_put_u32(skb, L2TP_ATTR_PEER_CONN_ID, tunnel->peer_tunnel_id) ||
	    nla_put_u32(skb, L2TP_ATTR_PEER_SESSION_ID, session->peer_session_id) ||
	    nla_put_u32(skb, L2TP_ATTR_DEBUG, 0) ||
	    nla_put_u16(skb, L2TP_ATTR_PW_TYPE, session->pwtype))
		जाओ nla_put_failure;

	अगर ((session->अगरname[0] &&
	     nla_put_string(skb, L2TP_ATTR_IFNAME, session->अगरname)) ||
	    (session->cookie_len &&
	     nla_put(skb, L2TP_ATTR_COOKIE, session->cookie_len, session->cookie)) ||
	    (session->peer_cookie_len &&
	     nla_put(skb, L2TP_ATTR_PEER_COOKIE, session->peer_cookie_len, session->peer_cookie)) ||
	    nla_put_u8(skb, L2TP_ATTR_RECV_SEQ, session->recv_seq) ||
	    nla_put_u8(skb, L2TP_ATTR_SEND_SEQ, session->send_seq) ||
	    nla_put_u8(skb, L2TP_ATTR_LNS_MODE, session->lns_mode) ||
	    (l2tp_tunnel_uses_xfrm(tunnel) &&
	     nla_put_u8(skb, L2TP_ATTR_USING_IPSEC, 1)) ||
	    (session->reorder_समयout &&
	     nla_put_msecs(skb, L2TP_ATTR_RECV_TIMEOUT,
			   session->reorder_समयout, L2TP_ATTR_PAD)))
		जाओ nla_put_failure;

	nest = nla_nest_start_noflag(skb, L2TP_ATTR_STATS);
	अगर (!nest)
		जाओ nla_put_failure;

	अगर (nla_put_u64_64bit(skb, L2TP_ATTR_TX_PACKETS,
			      atomic_दीर्घ_पढ़ो(&session->stats.tx_packets),
			      L2TP_ATTR_STATS_PAD) ||
	    nla_put_u64_64bit(skb, L2TP_ATTR_TX_BYTES,
			      atomic_दीर्घ_पढ़ो(&session->stats.tx_bytes),
			      L2TP_ATTR_STATS_PAD) ||
	    nla_put_u64_64bit(skb, L2TP_ATTR_TX_ERRORS,
			      atomic_दीर्घ_पढ़ो(&session->stats.tx_errors),
			      L2TP_ATTR_STATS_PAD) ||
	    nla_put_u64_64bit(skb, L2TP_ATTR_RX_PACKETS,
			      atomic_दीर्घ_पढ़ो(&session->stats.rx_packets),
			      L2TP_ATTR_STATS_PAD) ||
	    nla_put_u64_64bit(skb, L2TP_ATTR_RX_BYTES,
			      atomic_दीर्घ_पढ़ो(&session->stats.rx_bytes),
			      L2TP_ATTR_STATS_PAD) ||
	    nla_put_u64_64bit(skb, L2TP_ATTR_RX_SEQ_DISCARDS,
			      atomic_दीर्घ_पढ़ो(&session->stats.rx_seq_discards),
			      L2TP_ATTR_STATS_PAD) ||
	    nla_put_u64_64bit(skb, L2TP_ATTR_RX_COOKIE_DISCARDS,
			      atomic_दीर्घ_पढ़ो(&session->stats.rx_cookie_discards),
			      L2TP_ATTR_STATS_PAD) ||
	    nla_put_u64_64bit(skb, L2TP_ATTR_RX_OOS_PACKETS,
			      atomic_दीर्घ_पढ़ो(&session->stats.rx_oos_packets),
			      L2TP_ATTR_STATS_PAD) ||
	    nla_put_u64_64bit(skb, L2TP_ATTR_RX_ERRORS,
			      atomic_दीर्घ_पढ़ो(&session->stats.rx_errors),
			      L2TP_ATTR_STATS_PAD) ||
	    nla_put_u64_64bit(skb, L2TP_ATTR_RX_INVALID,
			      atomic_दीर्घ_पढ़ो(&session->stats.rx_invalid),
			      L2TP_ATTR_STATS_PAD))
		जाओ nla_put_failure;
	nla_nest_end(skb, nest);

	genlmsg_end(skb, hdr);
	वापस 0;

 nla_put_failure:
	genlmsg_cancel(skb, hdr);
	वापस -1;
पूर्ण

अटल पूर्णांक l2tp_nl_cmd_session_get(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा l2tp_session *session;
	काष्ठा sk_buff *msg;
	पूर्णांक ret;

	session = l2tp_nl_session_get(info);
	अगर (!session) अणु
		ret = -ENODEV;
		जाओ err;
	पूर्ण

	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	अगर (!msg) अणु
		ret = -ENOMEM;
		जाओ err_ref;
	पूर्ण

	ret = l2tp_nl_session_send(msg, info->snd_portid, info->snd_seq,
				   0, session, L2TP_CMD_SESSION_GET);
	अगर (ret < 0)
		जाओ err_ref_msg;

	ret = genlmsg_unicast(genl_info_net(info), msg, info->snd_portid);

	l2tp_session_dec_refcount(session);

	वापस ret;

err_ref_msg:
	nlmsg_मुक्त(msg);
err_ref:
	l2tp_session_dec_refcount(session);
err:
	वापस ret;
पूर्ण

अटल पूर्णांक l2tp_nl_cmd_session_dump(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb)
अणु
	काष्ठा net *net = sock_net(skb->sk);
	काष्ठा l2tp_session *session;
	काष्ठा l2tp_tunnel *tunnel = शून्य;
	पूर्णांक ti = cb->args[0];
	पूर्णांक si = cb->args[1];

	क्रम (;;) अणु
		अगर (!tunnel) अणु
			tunnel = l2tp_tunnel_get_nth(net, ti);
			अगर (!tunnel)
				जाओ out;
		पूर्ण

		session = l2tp_session_get_nth(tunnel, si);
		अगर (!session) अणु
			ti++;
			l2tp_tunnel_dec_refcount(tunnel);
			tunnel = शून्य;
			si = 0;
			जारी;
		पूर्ण

		अगर (l2tp_nl_session_send(skb, NETLINK_CB(cb->skb).portid,
					 cb->nlh->nlmsg_seq, NLM_F_MULTI,
					 session, L2TP_CMD_SESSION_GET) < 0) अणु
			l2tp_session_dec_refcount(session);
			l2tp_tunnel_dec_refcount(tunnel);
			अवरोध;
		पूर्ण
		l2tp_session_dec_refcount(session);

		si++;
	पूर्ण

out:
	cb->args[0] = ti;
	cb->args[1] = si;

	वापस skb->len;
पूर्ण

अटल स्थिर काष्ठा nla_policy l2tp_nl_policy[L2TP_ATTR_MAX + 1] = अणु
	[L2TP_ATTR_NONE]		= अणु .type = NLA_UNSPEC, पूर्ण,
	[L2TP_ATTR_PW_TYPE]		= अणु .type = NLA_U16, पूर्ण,
	[L2TP_ATTR_ENCAP_TYPE]		= अणु .type = NLA_U16, पूर्ण,
	[L2TP_ATTR_OFFSET]		= अणु .type = NLA_U16, पूर्ण,
	[L2TP_ATTR_DATA_SEQ]		= अणु .type = NLA_U8, पूर्ण,
	[L2TP_ATTR_L2SPEC_TYPE]		= अणु .type = NLA_U8, पूर्ण,
	[L2TP_ATTR_L2SPEC_LEN]		= अणु .type = NLA_U8, पूर्ण,
	[L2TP_ATTR_PROTO_VERSION]	= अणु .type = NLA_U8, पूर्ण,
	[L2TP_ATTR_CONN_ID]		= अणु .type = NLA_U32, पूर्ण,
	[L2TP_ATTR_PEER_CONN_ID]	= अणु .type = NLA_U32, पूर्ण,
	[L2TP_ATTR_SESSION_ID]		= अणु .type = NLA_U32, पूर्ण,
	[L2TP_ATTR_PEER_SESSION_ID]	= अणु .type = NLA_U32, पूर्ण,
	[L2TP_ATTR_UDP_CSUM]		= अणु .type = NLA_U8, पूर्ण,
	[L2TP_ATTR_VLAN_ID]		= अणु .type = NLA_U16, पूर्ण,
	[L2TP_ATTR_DEBUG]		= अणु .type = NLA_U32, पूर्ण,
	[L2TP_ATTR_RECV_SEQ]		= अणु .type = NLA_U8, पूर्ण,
	[L2TP_ATTR_SEND_SEQ]		= अणु .type = NLA_U8, पूर्ण,
	[L2TP_ATTR_LNS_MODE]		= अणु .type = NLA_U8, पूर्ण,
	[L2TP_ATTR_USING_IPSEC]		= अणु .type = NLA_U8, पूर्ण,
	[L2TP_ATTR_RECV_TIMEOUT]	= अणु .type = NLA_MSECS, पूर्ण,
	[L2TP_ATTR_FD]			= अणु .type = NLA_U32, पूर्ण,
	[L2TP_ATTR_IP_SADDR]		= अणु .type = NLA_U32, पूर्ण,
	[L2TP_ATTR_IP_DADDR]		= अणु .type = NLA_U32, पूर्ण,
	[L2TP_ATTR_UDP_SPORT]		= अणु .type = NLA_U16, पूर्ण,
	[L2TP_ATTR_UDP_DPORT]		= अणु .type = NLA_U16, पूर्ण,
	[L2TP_ATTR_MTU]			= अणु .type = NLA_U16, पूर्ण,
	[L2TP_ATTR_MRU]			= अणु .type = NLA_U16, पूर्ण,
	[L2TP_ATTR_STATS]		= अणु .type = NLA_NESTED, पूर्ण,
	[L2TP_ATTR_IP6_SADDR] = अणु
		.type = NLA_BINARY,
		.len = माप(काष्ठा in6_addr),
	पूर्ण,
	[L2TP_ATTR_IP6_DADDR] = अणु
		.type = NLA_BINARY,
		.len = माप(काष्ठा in6_addr),
	पूर्ण,
	[L2TP_ATTR_IFNAME] = अणु
		.type = NLA_NUL_STRING,
		.len = IFNAMSIZ - 1,
	पूर्ण,
	[L2TP_ATTR_COOKIE] = अणु
		.type = NLA_BINARY,
		.len = 8,
	पूर्ण,
	[L2TP_ATTR_PEER_COOKIE] = अणु
		.type = NLA_BINARY,
		.len = 8,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा genl_small_ops l2tp_nl_ops[] = अणु
	अणु
		.cmd = L2TP_CMD_NOOP,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = l2tp_nl_cmd_noop,
		/* can be retrieved by unprivileged users */
	पूर्ण,
	अणु
		.cmd = L2TP_CMD_TUNNEL_CREATE,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = l2tp_nl_cmd_tunnel_create,
		.flags = GENL_UNS_ADMIN_PERM,
	पूर्ण,
	अणु
		.cmd = L2TP_CMD_TUNNEL_DELETE,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = l2tp_nl_cmd_tunnel_delete,
		.flags = GENL_UNS_ADMIN_PERM,
	पूर्ण,
	अणु
		.cmd = L2TP_CMD_TUNNEL_MODIFY,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = l2tp_nl_cmd_tunnel_modअगरy,
		.flags = GENL_UNS_ADMIN_PERM,
	पूर्ण,
	अणु
		.cmd = L2TP_CMD_TUNNEL_GET,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = l2tp_nl_cmd_tunnel_get,
		.dumpit = l2tp_nl_cmd_tunnel_dump,
		.flags = GENL_UNS_ADMIN_PERM,
	पूर्ण,
	अणु
		.cmd = L2TP_CMD_SESSION_CREATE,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = l2tp_nl_cmd_session_create,
		.flags = GENL_UNS_ADMIN_PERM,
	पूर्ण,
	अणु
		.cmd = L2TP_CMD_SESSION_DELETE,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = l2tp_nl_cmd_session_delete,
		.flags = GENL_UNS_ADMIN_PERM,
	पूर्ण,
	अणु
		.cmd = L2TP_CMD_SESSION_MODIFY,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = l2tp_nl_cmd_session_modअगरy,
		.flags = GENL_UNS_ADMIN_PERM,
	पूर्ण,
	अणु
		.cmd = L2TP_CMD_SESSION_GET,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = l2tp_nl_cmd_session_get,
		.dumpit = l2tp_nl_cmd_session_dump,
		.flags = GENL_UNS_ADMIN_PERM,
	पूर्ण,
पूर्ण;

अटल काष्ठा genl_family l2tp_nl_family __ro_after_init = अणु
	.name		= L2TP_GENL_NAME,
	.version	= L2TP_GENL_VERSION,
	.hdrsize	= 0,
	.maxattr	= L2TP_ATTR_MAX,
	.policy = l2tp_nl_policy,
	.netnsok	= true,
	.module		= THIS_MODULE,
	.small_ops	= l2tp_nl_ops,
	.n_small_ops	= ARRAY_SIZE(l2tp_nl_ops),
	.mcgrps		= l2tp_multicast_group,
	.n_mcgrps	= ARRAY_SIZE(l2tp_multicast_group),
पूर्ण;

पूर्णांक l2tp_nl_रेजिस्टर_ops(क्रमागत l2tp_pwtype pw_type, स्थिर काष्ठा l2tp_nl_cmd_ops *ops)
अणु
	पूर्णांक ret;

	ret = -EINVAL;
	अगर (pw_type >= __L2TP_PWTYPE_MAX)
		जाओ err;

	genl_lock();
	ret = -EBUSY;
	अगर (l2tp_nl_cmd_ops[pw_type])
		जाओ out;

	l2tp_nl_cmd_ops[pw_type] = ops;
	ret = 0;

out:
	genl_unlock();
err:
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(l2tp_nl_रेजिस्टर_ops);

व्योम l2tp_nl_unरेजिस्टर_ops(क्रमागत l2tp_pwtype pw_type)
अणु
	अगर (pw_type < __L2TP_PWTYPE_MAX) अणु
		genl_lock();
		l2tp_nl_cmd_ops[pw_type] = शून्य;
		genl_unlock();
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(l2tp_nl_unरेजिस्टर_ops);

अटल पूर्णांक __init l2tp_nl_init(व्योम)
अणु
	pr_info("L2TP netlink interface\n");
	वापस genl_रेजिस्टर_family(&l2tp_nl_family);
पूर्ण

अटल व्योम l2tp_nl_cleanup(व्योम)
अणु
	genl_unरेजिस्टर_family(&l2tp_nl_family);
पूर्ण

module_init(l2tp_nl_init);
module_निकास(l2tp_nl_cleanup);

MODULE_AUTHOR("James Chapman <jchapman@katalix.com>");
MODULE_DESCRIPTION("L2TP netlink");
MODULE_LICENSE("GPL");
MODULE_VERSION("1.0");
MODULE_ALIAS_GENL_FAMILY("l2tp");
