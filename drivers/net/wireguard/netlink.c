<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2015-2019 Jason A. Donenfeld <Jason@zx2c4.com>. All Rights Reserved.
 */

#समावेश "netlink.h"
#समावेश "device.h"
#समावेश "peer.h"
#समावेश "socket.h"
#समावेश "queueing.h"
#समावेश "messages.h"

#समावेश <uapi/linux/wireguard.h>

#समावेश <linux/अगर.h>
#समावेश <net/genetlink.h>
#समावेश <net/sock.h>
#समावेश <crypto/algapi.h>

अटल काष्ठा genl_family genl_family;

अटल स्थिर काष्ठा nla_policy device_policy[WGDEVICE_A_MAX + 1] = अणु
	[WGDEVICE_A_IFINDEX]		= अणु .type = NLA_U32 पूर्ण,
	[WGDEVICE_A_IFNAME]		= अणु .type = NLA_NUL_STRING, .len = IFNAMSIZ - 1 पूर्ण,
	[WGDEVICE_A_PRIVATE_KEY]	= NLA_POLICY_EXACT_LEN(NOISE_PUBLIC_KEY_LEN),
	[WGDEVICE_A_PUBLIC_KEY]		= NLA_POLICY_EXACT_LEN(NOISE_PUBLIC_KEY_LEN),
	[WGDEVICE_A_FLAGS]		= अणु .type = NLA_U32 पूर्ण,
	[WGDEVICE_A_LISTEN_PORT]	= अणु .type = NLA_U16 पूर्ण,
	[WGDEVICE_A_FWMARK]		= अणु .type = NLA_U32 पूर्ण,
	[WGDEVICE_A_PEERS]		= अणु .type = NLA_NESTED पूर्ण
पूर्ण;

अटल स्थिर काष्ठा nla_policy peer_policy[WGPEER_A_MAX + 1] = अणु
	[WGPEER_A_PUBLIC_KEY]				= NLA_POLICY_EXACT_LEN(NOISE_PUBLIC_KEY_LEN),
	[WGPEER_A_PRESHARED_KEY]			= NLA_POLICY_EXACT_LEN(NOISE_SYMMETRIC_KEY_LEN),
	[WGPEER_A_FLAGS]				= अणु .type = NLA_U32 पूर्ण,
	[WGPEER_A_ENDPOINT]				= NLA_POLICY_MIN_LEN(माप(काष्ठा sockaddr)),
	[WGPEER_A_PERSISTENT_KEEPALIVE_INTERVAL]	= अणु .type = NLA_U16 पूर्ण,
	[WGPEER_A_LAST_HANDSHAKE_TIME]			= NLA_POLICY_EXACT_LEN(माप(काष्ठा __kernel_बारpec)),
	[WGPEER_A_RX_BYTES]				= अणु .type = NLA_U64 पूर्ण,
	[WGPEER_A_TX_BYTES]				= अणु .type = NLA_U64 पूर्ण,
	[WGPEER_A_ALLOWEDIPS]				= अणु .type = NLA_NESTED पूर्ण,
	[WGPEER_A_PROTOCOL_VERSION]			= अणु .type = NLA_U32 पूर्ण
पूर्ण;

अटल स्थिर काष्ठा nla_policy allowedip_policy[WGALLOWEDIP_A_MAX + 1] = अणु
	[WGALLOWEDIP_A_FAMILY]		= अणु .type = NLA_U16 पूर्ण,
	[WGALLOWEDIP_A_IPADDR]		= NLA_POLICY_MIN_LEN(माप(काष्ठा in_addr)),
	[WGALLOWEDIP_A_CIDR_MASK]	= अणु .type = NLA_U8 पूर्ण
पूर्ण;

अटल काष्ठा wg_device *lookup_पूर्णांकerface(काष्ठा nlattr **attrs,
					  काष्ठा sk_buff *skb)
अणु
	काष्ठा net_device *dev = शून्य;

	अगर (!attrs[WGDEVICE_A_IFINDEX] == !attrs[WGDEVICE_A_IFNAME])
		वापस ERR_PTR(-EBADR);
	अगर (attrs[WGDEVICE_A_IFINDEX])
		dev = dev_get_by_index(sock_net(skb->sk),
				       nla_get_u32(attrs[WGDEVICE_A_IFINDEX]));
	अन्यथा अगर (attrs[WGDEVICE_A_IFNAME])
		dev = dev_get_by_name(sock_net(skb->sk),
				      nla_data(attrs[WGDEVICE_A_IFNAME]));
	अगर (!dev)
		वापस ERR_PTR(-ENODEV);
	अगर (!dev->rtnl_link_ops || !dev->rtnl_link_ops->kind ||
	    म_भेद(dev->rtnl_link_ops->kind, KBUILD_MODNAME)) अणु
		dev_put(dev);
		वापस ERR_PTR(-EOPNOTSUPP);
	पूर्ण
	वापस netdev_priv(dev);
पूर्ण

अटल पूर्णांक get_allowedips(काष्ठा sk_buff *skb, स्थिर u8 *ip, u8 cidr,
			  पूर्णांक family)
अणु
	काष्ठा nlattr *allowedip_nest;

	allowedip_nest = nla_nest_start(skb, 0);
	अगर (!allowedip_nest)
		वापस -EMSGSIZE;

	अगर (nla_put_u8(skb, WGALLOWEDIP_A_CIDR_MASK, cidr) ||
	    nla_put_u16(skb, WGALLOWEDIP_A_FAMILY, family) ||
	    nla_put(skb, WGALLOWEDIP_A_IPADDR, family == AF_INET6 ?
		    माप(काष्ठा in6_addr) : माप(काष्ठा in_addr), ip)) अणु
		nla_nest_cancel(skb, allowedip_nest);
		वापस -EMSGSIZE;
	पूर्ण

	nla_nest_end(skb, allowedip_nest);
	वापस 0;
पूर्ण

काष्ठा dump_ctx अणु
	काष्ठा wg_device *wg;
	काष्ठा wg_peer *next_peer;
	u64 allowedips_seq;
	काष्ठा allowedips_node *next_allowedip;
पूर्ण;

#घोषणा DUMP_CTX(cb) ((काष्ठा dump_ctx *)(cb)->args)

अटल पूर्णांक
get_peer(काष्ठा wg_peer *peer, काष्ठा sk_buff *skb, काष्ठा dump_ctx *ctx)
अणु

	काष्ठा nlattr *allowedips_nest, *peer_nest = nla_nest_start(skb, 0);
	काष्ठा allowedips_node *allowedips_node = ctx->next_allowedip;
	bool fail;

	अगर (!peer_nest)
		वापस -EMSGSIZE;

	करोwn_पढ़ो(&peer->handshake.lock);
	fail = nla_put(skb, WGPEER_A_PUBLIC_KEY, NOISE_PUBLIC_KEY_LEN,
		       peer->handshake.remote_अटल);
	up_पढ़ो(&peer->handshake.lock);
	अगर (fail)
		जाओ err;

	अगर (!allowedips_node) अणु
		स्थिर काष्ठा __kernel_बारpec last_handshake = अणु
			.tv_sec = peer->wallसमय_last_handshake.tv_sec,
			.tv_nsec = peer->wallसमय_last_handshake.tv_nsec
		पूर्ण;

		करोwn_पढ़ो(&peer->handshake.lock);
		fail = nla_put(skb, WGPEER_A_PRESHARED_KEY,
			       NOISE_SYMMETRIC_KEY_LEN,
			       peer->handshake.preshared_key);
		up_पढ़ो(&peer->handshake.lock);
		अगर (fail)
			जाओ err;

		अगर (nla_put(skb, WGPEER_A_LAST_HANDSHAKE_TIME,
			    माप(last_handshake), &last_handshake) ||
		    nla_put_u16(skb, WGPEER_A_PERSISTENT_KEEPALIVE_INTERVAL,
				peer->persistent_keepalive_पूर्णांकerval) ||
		    nla_put_u64_64bit(skb, WGPEER_A_TX_BYTES, peer->tx_bytes,
				      WGPEER_A_UNSPEC) ||
		    nla_put_u64_64bit(skb, WGPEER_A_RX_BYTES, peer->rx_bytes,
				      WGPEER_A_UNSPEC) ||
		    nla_put_u32(skb, WGPEER_A_PROTOCOL_VERSION, 1))
			जाओ err;

		पढ़ो_lock_bh(&peer->endpoपूर्णांक_lock);
		अगर (peer->endpoपूर्णांक.addr.sa_family == AF_INET)
			fail = nla_put(skb, WGPEER_A_ENDPOINT,
				       माप(peer->endpoपूर्णांक.addr4),
				       &peer->endpoपूर्णांक.addr4);
		अन्यथा अगर (peer->endpoपूर्णांक.addr.sa_family == AF_INET6)
			fail = nla_put(skb, WGPEER_A_ENDPOINT,
				       माप(peer->endpoपूर्णांक.addr6),
				       &peer->endpoपूर्णांक.addr6);
		पढ़ो_unlock_bh(&peer->endpoपूर्णांक_lock);
		अगर (fail)
			जाओ err;
		allowedips_node =
			list_first_entry_or_null(&peer->allowedips_list,
					काष्ठा allowedips_node, peer_list);
	पूर्ण
	अगर (!allowedips_node)
		जाओ no_allowedips;
	अगर (!ctx->allowedips_seq)
		ctx->allowedips_seq = peer->device->peer_allowedips.seq;
	अन्यथा अगर (ctx->allowedips_seq != peer->device->peer_allowedips.seq)
		जाओ no_allowedips;

	allowedips_nest = nla_nest_start(skb, WGPEER_A_ALLOWEDIPS);
	अगर (!allowedips_nest)
		जाओ err;

	list_क्रम_each_entry_from(allowedips_node, &peer->allowedips_list,
				 peer_list) अणु
		u8 cidr, ip[16] __aligned(__alignof(u64));
		पूर्णांक family;

		family = wg_allowedips_पढ़ो_node(allowedips_node, ip, &cidr);
		अगर (get_allowedips(skb, ip, cidr, family)) अणु
			nla_nest_end(skb, allowedips_nest);
			nla_nest_end(skb, peer_nest);
			ctx->next_allowedip = allowedips_node;
			वापस -EMSGSIZE;
		पूर्ण
	पूर्ण
	nla_nest_end(skb, allowedips_nest);
no_allowedips:
	nla_nest_end(skb, peer_nest);
	ctx->next_allowedip = शून्य;
	ctx->allowedips_seq = 0;
	वापस 0;
err:
	nla_nest_cancel(skb, peer_nest);
	वापस -EMSGSIZE;
पूर्ण

अटल पूर्णांक wg_get_device_start(काष्ठा netlink_callback *cb)
अणु
	काष्ठा wg_device *wg;

	wg = lookup_पूर्णांकerface(genl_dumpit_info(cb)->attrs, cb->skb);
	अगर (IS_ERR(wg))
		वापस PTR_ERR(wg);
	DUMP_CTX(cb)->wg = wg;
	वापस 0;
पूर्ण

अटल पूर्णांक wg_get_device_dump(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb)
अणु
	काष्ठा wg_peer *peer, *next_peer_cursor;
	काष्ठा dump_ctx *ctx = DUMP_CTX(cb);
	काष्ठा wg_device *wg = ctx->wg;
	काष्ठा nlattr *peers_nest;
	पूर्णांक ret = -EMSGSIZE;
	bool करोne = true;
	व्योम *hdr;

	rtnl_lock();
	mutex_lock(&wg->device_update_lock);
	cb->seq = wg->device_update_gen;
	next_peer_cursor = ctx->next_peer;

	hdr = genlmsg_put(skb, NETLINK_CB(cb->skb).portid, cb->nlh->nlmsg_seq,
			  &genl_family, NLM_F_MULTI, WG_CMD_GET_DEVICE);
	अगर (!hdr)
		जाओ out;
	genl_dump_check_consistent(cb, hdr);

	अगर (!ctx->next_peer) अणु
		अगर (nla_put_u16(skb, WGDEVICE_A_LISTEN_PORT,
				wg->incoming_port) ||
		    nla_put_u32(skb, WGDEVICE_A_FWMARK, wg->fwmark) ||
		    nla_put_u32(skb, WGDEVICE_A_IFINDEX, wg->dev->अगरindex) ||
		    nla_put_string(skb, WGDEVICE_A_IFNAME, wg->dev->name))
			जाओ out;

		करोwn_पढ़ो(&wg->अटल_identity.lock);
		अगर (wg->अटल_identity.has_identity) अणु
			अगर (nla_put(skb, WGDEVICE_A_PRIVATE_KEY,
				    NOISE_PUBLIC_KEY_LEN,
				    wg->अटल_identity.अटल_निजी) ||
			    nla_put(skb, WGDEVICE_A_PUBLIC_KEY,
				    NOISE_PUBLIC_KEY_LEN,
				    wg->अटल_identity.अटल_खुला)) अणु
				up_पढ़ो(&wg->अटल_identity.lock);
				जाओ out;
			पूर्ण
		पूर्ण
		up_पढ़ो(&wg->अटल_identity.lock);
	पूर्ण

	peers_nest = nla_nest_start(skb, WGDEVICE_A_PEERS);
	अगर (!peers_nest)
		जाओ out;
	ret = 0;
	/* If the last cursor was हटाओd via list_del_init in peer_हटाओ, then
	 * we just treat this the same as there being no more peers left. The
	 * reason is that seq_nr should indicate to userspace that this isn't a
	 * coherent dump anyway, so they'll try again.
	 */
	अगर (list_empty(&wg->peer_list) ||
	    (ctx->next_peer && list_empty(&ctx->next_peer->peer_list))) अणु
		nla_nest_cancel(skb, peers_nest);
		जाओ out;
	पूर्ण
	lockdep_निश्चित_held(&wg->device_update_lock);
	peer = list_prepare_entry(ctx->next_peer, &wg->peer_list, peer_list);
	list_क्रम_each_entry_जारी(peer, &wg->peer_list, peer_list) अणु
		अगर (get_peer(peer, skb, ctx)) अणु
			करोne = false;
			अवरोध;
		पूर्ण
		next_peer_cursor = peer;
	पूर्ण
	nla_nest_end(skb, peers_nest);

out:
	अगर (!ret && !करोne && next_peer_cursor)
		wg_peer_get(next_peer_cursor);
	wg_peer_put(ctx->next_peer);
	mutex_unlock(&wg->device_update_lock);
	rtnl_unlock();

	अगर (ret) अणु
		genlmsg_cancel(skb, hdr);
		वापस ret;
	पूर्ण
	genlmsg_end(skb, hdr);
	अगर (करोne) अणु
		ctx->next_peer = शून्य;
		वापस 0;
	पूर्ण
	ctx->next_peer = next_peer_cursor;
	वापस skb->len;

	/* At this poपूर्णांक, we can't really deal ourselves with safely zeroing out
	 * the निजी key material after usage. This will need an additional API
	 * in the kernel क्रम marking skbs as zero_on_मुक्त.
	 */
पूर्ण

अटल पूर्णांक wg_get_device_करोne(काष्ठा netlink_callback *cb)
अणु
	काष्ठा dump_ctx *ctx = DUMP_CTX(cb);

	अगर (ctx->wg)
		dev_put(ctx->wg->dev);
	wg_peer_put(ctx->next_peer);
	वापस 0;
पूर्ण

अटल पूर्णांक set_port(काष्ठा wg_device *wg, u16 port)
अणु
	काष्ठा wg_peer *peer;

	अगर (wg->incoming_port == port)
		वापस 0;
	list_क्रम_each_entry(peer, &wg->peer_list, peer_list)
		wg_socket_clear_peer_endpoपूर्णांक_src(peer);
	अगर (!netअगर_running(wg->dev)) अणु
		wg->incoming_port = port;
		वापस 0;
	पूर्ण
	वापस wg_socket_init(wg, port);
पूर्ण

अटल पूर्णांक set_allowedip(काष्ठा wg_peer *peer, काष्ठा nlattr **attrs)
अणु
	पूर्णांक ret = -EINVAL;
	u16 family;
	u8 cidr;

	अगर (!attrs[WGALLOWEDIP_A_FAMILY] || !attrs[WGALLOWEDIP_A_IPADDR] ||
	    !attrs[WGALLOWEDIP_A_CIDR_MASK])
		वापस ret;
	family = nla_get_u16(attrs[WGALLOWEDIP_A_FAMILY]);
	cidr = nla_get_u8(attrs[WGALLOWEDIP_A_CIDR_MASK]);

	अगर (family == AF_INET && cidr <= 32 &&
	    nla_len(attrs[WGALLOWEDIP_A_IPADDR]) == माप(काष्ठा in_addr))
		ret = wg_allowedips_insert_v4(
			&peer->device->peer_allowedips,
			nla_data(attrs[WGALLOWEDIP_A_IPADDR]), cidr, peer,
			&peer->device->device_update_lock);
	अन्यथा अगर (family == AF_INET6 && cidr <= 128 &&
		 nla_len(attrs[WGALLOWEDIP_A_IPADDR]) == माप(काष्ठा in6_addr))
		ret = wg_allowedips_insert_v6(
			&peer->device->peer_allowedips,
			nla_data(attrs[WGALLOWEDIP_A_IPADDR]), cidr, peer,
			&peer->device->device_update_lock);

	वापस ret;
पूर्ण

अटल पूर्णांक set_peer(काष्ठा wg_device *wg, काष्ठा nlattr **attrs)
अणु
	u8 *खुला_key = शून्य, *preshared_key = शून्य;
	काष्ठा wg_peer *peer = शून्य;
	u32 flags = 0;
	पूर्णांक ret;

	ret = -EINVAL;
	अगर (attrs[WGPEER_A_PUBLIC_KEY] &&
	    nla_len(attrs[WGPEER_A_PUBLIC_KEY]) == NOISE_PUBLIC_KEY_LEN)
		खुला_key = nla_data(attrs[WGPEER_A_PUBLIC_KEY]);
	अन्यथा
		जाओ out;
	अगर (attrs[WGPEER_A_PRESHARED_KEY] &&
	    nla_len(attrs[WGPEER_A_PRESHARED_KEY]) == NOISE_SYMMETRIC_KEY_LEN)
		preshared_key = nla_data(attrs[WGPEER_A_PRESHARED_KEY]);

	अगर (attrs[WGPEER_A_FLAGS])
		flags = nla_get_u32(attrs[WGPEER_A_FLAGS]);
	ret = -EOPNOTSUPP;
	अगर (flags & ~__WGPEER_F_ALL)
		जाओ out;

	ret = -EPFNOSUPPORT;
	अगर (attrs[WGPEER_A_PROTOCOL_VERSION]) अणु
		अगर (nla_get_u32(attrs[WGPEER_A_PROTOCOL_VERSION]) != 1)
			जाओ out;
	पूर्ण

	peer = wg_pubkey_hashtable_lookup(wg->peer_hashtable,
					  nla_data(attrs[WGPEER_A_PUBLIC_KEY]));
	ret = 0;
	अगर (!peer) अणु /* Peer करोesn't exist yet. Add a new one. */
		अगर (flags & (WGPEER_F_REMOVE_ME | WGPEER_F_UPDATE_ONLY))
			जाओ out;

		/* The peer is new, so there aren't allowed IPs to हटाओ. */
		flags &= ~WGPEER_F_REPLACE_ALLOWEDIPS;

		करोwn_पढ़ो(&wg->अटल_identity.lock);
		अगर (wg->अटल_identity.has_identity &&
		    !स_भेद(nla_data(attrs[WGPEER_A_PUBLIC_KEY]),
			    wg->अटल_identity.अटल_खुला,
			    NOISE_PUBLIC_KEY_LEN)) अणु
			/* We silently ignore peers that have the same खुला
			 * key as the device. The reason we करो it silently is
			 * that we'd like क्रम people to be able to reuse the
			 * same set of API calls across peers.
			 */
			up_पढ़ो(&wg->अटल_identity.lock);
			ret = 0;
			जाओ out;
		पूर्ण
		up_पढ़ो(&wg->अटल_identity.lock);

		peer = wg_peer_create(wg, खुला_key, preshared_key);
		अगर (IS_ERR(peer)) अणु
			ret = PTR_ERR(peer);
			peer = शून्य;
			जाओ out;
		पूर्ण
		/* Take additional reference, as though we've just been
		 * looked up.
		 */
		wg_peer_get(peer);
	पूर्ण

	अगर (flags & WGPEER_F_REMOVE_ME) अणु
		wg_peer_हटाओ(peer);
		जाओ out;
	पूर्ण

	अगर (preshared_key) अणु
		करोwn_ग_लिखो(&peer->handshake.lock);
		स_नकल(&peer->handshake.preshared_key, preshared_key,
		       NOISE_SYMMETRIC_KEY_LEN);
		up_ग_लिखो(&peer->handshake.lock);
	पूर्ण

	अगर (attrs[WGPEER_A_ENDPOINT]) अणु
		काष्ठा sockaddr *addr = nla_data(attrs[WGPEER_A_ENDPOINT]);
		माप_प्रकार len = nla_len(attrs[WGPEER_A_ENDPOINT]);

		अगर ((len == माप(काष्ठा sockaddr_in) &&
		     addr->sa_family == AF_INET) ||
		    (len == माप(काष्ठा sockaddr_in6) &&
		     addr->sa_family == AF_INET6)) अणु
			काष्ठा endpoपूर्णांक endpoपूर्णांक = अणु अणु अणु 0 पूर्ण पूर्ण पूर्ण;

			स_नकल(&endpoपूर्णांक.addr, addr, len);
			wg_socket_set_peer_endpoपूर्णांक(peer, &endpoपूर्णांक);
		पूर्ण
	पूर्ण

	अगर (flags & WGPEER_F_REPLACE_ALLOWEDIPS)
		wg_allowedips_हटाओ_by_peer(&wg->peer_allowedips, peer,
					     &wg->device_update_lock);

	अगर (attrs[WGPEER_A_ALLOWEDIPS]) अणु
		काष्ठा nlattr *attr, *allowedip[WGALLOWEDIP_A_MAX + 1];
		पूर्णांक rem;

		nla_क्रम_each_nested(attr, attrs[WGPEER_A_ALLOWEDIPS], rem) अणु
			ret = nla_parse_nested(allowedip, WGALLOWEDIP_A_MAX,
					       attr, allowedip_policy, शून्य);
			अगर (ret < 0)
				जाओ out;
			ret = set_allowedip(peer, allowedip);
			अगर (ret < 0)
				जाओ out;
		पूर्ण
	पूर्ण

	अगर (attrs[WGPEER_A_PERSISTENT_KEEPALIVE_INTERVAL]) अणु
		स्थिर u16 persistent_keepalive_पूर्णांकerval = nla_get_u16(
				attrs[WGPEER_A_PERSISTENT_KEEPALIVE_INTERVAL]);
		स्थिर bool send_keepalive =
			!peer->persistent_keepalive_पूर्णांकerval &&
			persistent_keepalive_पूर्णांकerval &&
			netअगर_running(wg->dev);

		peer->persistent_keepalive_पूर्णांकerval = persistent_keepalive_पूर्णांकerval;
		अगर (send_keepalive)
			wg_packet_send_keepalive(peer);
	पूर्ण

	अगर (netअगर_running(wg->dev))
		wg_packet_send_staged_packets(peer);

out:
	wg_peer_put(peer);
	अगर (attrs[WGPEER_A_PRESHARED_KEY])
		memzero_explicit(nla_data(attrs[WGPEER_A_PRESHARED_KEY]),
				 nla_len(attrs[WGPEER_A_PRESHARED_KEY]));
	वापस ret;
पूर्ण

अटल पूर्णांक wg_set_device(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा wg_device *wg = lookup_पूर्णांकerface(info->attrs, skb);
	u32 flags = 0;
	पूर्णांक ret;

	अगर (IS_ERR(wg)) अणु
		ret = PTR_ERR(wg);
		जाओ out_nodev;
	पूर्ण

	rtnl_lock();
	mutex_lock(&wg->device_update_lock);

	अगर (info->attrs[WGDEVICE_A_FLAGS])
		flags = nla_get_u32(info->attrs[WGDEVICE_A_FLAGS]);
	ret = -EOPNOTSUPP;
	अगर (flags & ~__WGDEVICE_F_ALL)
		जाओ out;

	अगर (info->attrs[WGDEVICE_A_LISTEN_PORT] || info->attrs[WGDEVICE_A_FWMARK]) अणु
		काष्ठा net *net;
		rcu_पढ़ो_lock();
		net = rcu_dereference(wg->creating_net);
		ret = !net || !ns_capable(net->user_ns, CAP_NET_ADMIN) ? -EPERM : 0;
		rcu_पढ़ो_unlock();
		अगर (ret)
			जाओ out;
	पूर्ण

	++wg->device_update_gen;

	अगर (info->attrs[WGDEVICE_A_FWMARK]) अणु
		काष्ठा wg_peer *peer;

		wg->fwmark = nla_get_u32(info->attrs[WGDEVICE_A_FWMARK]);
		list_क्रम_each_entry(peer, &wg->peer_list, peer_list)
			wg_socket_clear_peer_endpoपूर्णांक_src(peer);
	पूर्ण

	अगर (info->attrs[WGDEVICE_A_LISTEN_PORT]) अणु
		ret = set_port(wg,
			nla_get_u16(info->attrs[WGDEVICE_A_LISTEN_PORT]));
		अगर (ret)
			जाओ out;
	पूर्ण

	अगर (flags & WGDEVICE_F_REPLACE_PEERS)
		wg_peer_हटाओ_all(wg);

	अगर (info->attrs[WGDEVICE_A_PRIVATE_KEY] &&
	    nla_len(info->attrs[WGDEVICE_A_PRIVATE_KEY]) ==
		    NOISE_PUBLIC_KEY_LEN) अणु
		u8 *निजी_key = nla_data(info->attrs[WGDEVICE_A_PRIVATE_KEY]);
		u8 खुला_key[NOISE_PUBLIC_KEY_LEN];
		काष्ठा wg_peer *peer, *temp;

		अगर (!crypto_memneq(wg->अटल_identity.अटल_निजी,
				   निजी_key, NOISE_PUBLIC_KEY_LEN))
			जाओ skip_set_निजी_key;

		/* We हटाओ beक्रमe setting, to prevent race, which means करोing
		 * two 25519-genpub ops.
		 */
		अगर (curve25519_generate_खुला(खुला_key, निजी_key)) अणु
			peer = wg_pubkey_hashtable_lookup(wg->peer_hashtable,
							  खुला_key);
			अगर (peer) अणु
				wg_peer_put(peer);
				wg_peer_हटाओ(peer);
			पूर्ण
		पूर्ण

		करोwn_ग_लिखो(&wg->अटल_identity.lock);
		wg_noise_set_अटल_identity_निजी_key(&wg->अटल_identity,
							 निजी_key);
		list_क्रम_each_entry_safe(peer, temp, &wg->peer_list,
					 peer_list) अणु
			wg_noise_precompute_अटल_अटल(peer);
			wg_noise_expire_current_peer_keypairs(peer);
		पूर्ण
		wg_cookie_checker_precompute_device_keys(&wg->cookie_checker);
		up_ग_लिखो(&wg->अटल_identity.lock);
	पूर्ण
skip_set_निजी_key:

	अगर (info->attrs[WGDEVICE_A_PEERS]) अणु
		काष्ठा nlattr *attr, *peer[WGPEER_A_MAX + 1];
		पूर्णांक rem;

		nla_क्रम_each_nested(attr, info->attrs[WGDEVICE_A_PEERS], rem) अणु
			ret = nla_parse_nested(peer, WGPEER_A_MAX, attr,
					       peer_policy, शून्य);
			अगर (ret < 0)
				जाओ out;
			ret = set_peer(wg, peer);
			अगर (ret < 0)
				जाओ out;
		पूर्ण
	पूर्ण
	ret = 0;

out:
	mutex_unlock(&wg->device_update_lock);
	rtnl_unlock();
	dev_put(wg->dev);
out_nodev:
	अगर (info->attrs[WGDEVICE_A_PRIVATE_KEY])
		memzero_explicit(nla_data(info->attrs[WGDEVICE_A_PRIVATE_KEY]),
				 nla_len(info->attrs[WGDEVICE_A_PRIVATE_KEY]));
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा genl_ops genl_ops[] = अणु
	अणु
		.cmd = WG_CMD_GET_DEVICE,
		.start = wg_get_device_start,
		.dumpit = wg_get_device_dump,
		.करोne = wg_get_device_करोne,
		.flags = GENL_UNS_ADMIN_PERM
	पूर्ण, अणु
		.cmd = WG_CMD_SET_DEVICE,
		.करोit = wg_set_device,
		.flags = GENL_UNS_ADMIN_PERM
	पूर्ण
पूर्ण;

अटल काष्ठा genl_family genl_family __ro_after_init = अणु
	.ops = genl_ops,
	.n_ops = ARRAY_SIZE(genl_ops),
	.name = WG_GENL_NAME,
	.version = WG_GENL_VERSION,
	.maxattr = WGDEVICE_A_MAX,
	.module = THIS_MODULE,
	.policy = device_policy,
	.netnsok = true
पूर्ण;

पूर्णांक __init wg_genetlink_init(व्योम)
अणु
	वापस genl_रेजिस्टर_family(&genl_family);
पूर्ण

व्योम __निकास wg_genetlink_uninit(व्योम)
अणु
	genl_unरेजिस्टर_family(&genl_family);
पूर्ण
