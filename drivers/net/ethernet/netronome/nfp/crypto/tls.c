<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-2-Clause)
/* Copyright (C) 2019 Netronome Systems, Inc. */

#समावेश <linux/bitfield.h>
#समावेश <linux/ipv6.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/माला.स>
#समावेश <net/inet6_hashtables.h>
#समावेश <net/tls.h>

#समावेश "../ccm.h"
#समावेश "../nfp_net.h"
#समावेश "crypto.h"
#समावेश "fw.h"

#घोषणा NFP_NET_TLS_CCM_MBOX_OPS_MASK		\
	(BIT(NFP_CCM_TYPE_CRYPTO_RESET) |	\
	 BIT(NFP_CCM_TYPE_CRYPTO_ADD) |		\
	 BIT(NFP_CCM_TYPE_CRYPTO_DEL) |		\
	 BIT(NFP_CCM_TYPE_CRYPTO_UPDATE))

#घोषणा NFP_NET_TLS_OPCODE_MASK_RX			\
	BIT(NFP_NET_CRYPTO_OP_TLS_1_2_AES_GCM_128_DEC)

#घोषणा NFP_NET_TLS_OPCODE_MASK_TX			\
	BIT(NFP_NET_CRYPTO_OP_TLS_1_2_AES_GCM_128_ENC)

#घोषणा NFP_NET_TLS_OPCODE_MASK						\
	(NFP_NET_TLS_OPCODE_MASK_RX | NFP_NET_TLS_OPCODE_MASK_TX)

अटल व्योम nfp_net_crypto_set_op(काष्ठा nfp_net *nn, u8 opcode, bool on)
अणु
	u32 off, val;

	off = nn->tlv_caps.crypto_enable_off + round_करोwn(opcode / 8, 4);

	val = nn_पढ़ोl(nn, off);
	अगर (on)
		val |= BIT(opcode & 31);
	अन्यथा
		val &= ~BIT(opcode & 31);
	nn_ग_लिखोl(nn, off, val);
पूर्ण

अटल bool
__nfp_net_tls_conn_cnt_changed(काष्ठा nfp_net *nn, पूर्णांक add,
			       क्रमागत tls_offload_ctx_dir direction)
अणु
	u8 opcode;
	पूर्णांक cnt;

	अगर (direction == TLS_OFFLOAD_CTX_सूची_TX) अणु
		opcode = NFP_NET_CRYPTO_OP_TLS_1_2_AES_GCM_128_ENC;
		nn->ktls_tx_conn_cnt += add;
		cnt = nn->ktls_tx_conn_cnt;
		nn->dp.ktls_tx = !!nn->ktls_tx_conn_cnt;
	पूर्ण अन्यथा अणु
		opcode = NFP_NET_CRYPTO_OP_TLS_1_2_AES_GCM_128_DEC;
		nn->ktls_rx_conn_cnt += add;
		cnt = nn->ktls_rx_conn_cnt;
	पूर्ण

	/* Care only about 0 -> 1 and 1 -> 0 transitions */
	अगर (cnt > 1)
		वापस false;

	nfp_net_crypto_set_op(nn, opcode, cnt);
	वापस true;
पूर्ण

अटल पूर्णांक
nfp_net_tls_conn_cnt_changed(काष्ठा nfp_net *nn, पूर्णांक add,
			     क्रमागत tls_offload_ctx_dir direction)
अणु
	पूर्णांक ret = 0;

	/* Use the BAR lock to protect the connection counts */
	nn_ctrl_bar_lock(nn);
	अगर (__nfp_net_tls_conn_cnt_changed(nn, add, direction)) अणु
		ret = __nfp_net_reconfig(nn, NFP_NET_CFG_UPDATE_CRYPTO);
		/* Unकरो the cnt adjusपंचांगent अगर failed */
		अगर (ret)
			__nfp_net_tls_conn_cnt_changed(nn, -add, direction);
	पूर्ण
	nn_ctrl_bar_unlock(nn);

	वापस ret;
पूर्ण

अटल पूर्णांक
nfp_net_tls_conn_add(काष्ठा nfp_net *nn, क्रमागत tls_offload_ctx_dir direction)
अणु
	वापस nfp_net_tls_conn_cnt_changed(nn, 1, direction);
पूर्ण

अटल पूर्णांक
nfp_net_tls_conn_हटाओ(काष्ठा nfp_net *nn, क्रमागत tls_offload_ctx_dir direction)
अणु
	वापस nfp_net_tls_conn_cnt_changed(nn, -1, direction);
पूर्ण

अटल काष्ठा sk_buff *
nfp_net_tls_alloc_simple(काष्ठा nfp_net *nn, माप_प्रकार req_sz, gfp_t flags)
अणु
	वापस nfp_ccm_mbox_msg_alloc(nn, req_sz,
				      माप(काष्ठा nfp_crypto_reply_simple),
				      flags);
पूर्ण

अटल पूर्णांक
nfp_net_tls_communicate_simple(काष्ठा nfp_net *nn, काष्ठा sk_buff *skb,
			       स्थिर अक्षर *name, क्रमागत nfp_ccm_type type)
अणु
	काष्ठा nfp_crypto_reply_simple *reply;
	पूर्णांक err;

	err = __nfp_ccm_mbox_communicate(nn, skb, type,
					 माप(*reply), माप(*reply),
					 type == NFP_CCM_TYPE_CRYPTO_DEL);
	अगर (err) अणु
		nn_dp_warn(&nn->dp, "failed to %s TLS: %d\n", name, err);
		वापस err;
	पूर्ण

	reply = (व्योम *)skb->data;
	err = -be32_to_cpu(reply->error);
	अगर (err)
		nn_dp_warn(&nn->dp, "failed to %s TLS, fw replied: %d\n",
			   name, err);
	dev_consume_skb_any(skb);

	वापस err;
पूर्ण

अटल व्योम nfp_net_tls_del_fw(काष्ठा nfp_net *nn, __be32 *fw_handle)
अणु
	काष्ठा nfp_crypto_req_del *req;
	काष्ठा sk_buff *skb;

	skb = nfp_net_tls_alloc_simple(nn, माप(*req), GFP_KERNEL);
	अगर (!skb)
		वापस;

	req = (व्योम *)skb->data;
	req->ep_id = 0;
	स_नकल(req->handle, fw_handle, माप(req->handle));

	nfp_net_tls_communicate_simple(nn, skb, "delete",
				       NFP_CCM_TYPE_CRYPTO_DEL);
पूर्ण

अटल व्योम
nfp_net_tls_set_ipver_vlan(काष्ठा nfp_crypto_req_add_front *front, u8 ipver)
अणु
	front->ipver_vlan = cpu_to_be16(FIELD_PREP(NFP_NET_TLS_IPVER, ipver) |
					FIELD_PREP(NFP_NET_TLS_VLAN,
						   NFP_NET_TLS_VLAN_UNUSED));
पूर्ण

अटल व्योम
nfp_net_tls_assign_conn_id(काष्ठा nfp_net *nn,
			   काष्ठा nfp_crypto_req_add_front *front)
अणु
	u32 len;
	u64 id;

	id = atomic64_inc_वापस(&nn->ktls_conn_id_gen);
	len = front->key_len - NFP_NET_TLS_NON_ADDR_KEY_LEN;

	स_नकल(front->l3_addrs, &id, माप(id));
	स_रखो(front->l3_addrs + माप(id), 0, len - माप(id));
पूर्ण

अटल काष्ठा nfp_crypto_req_add_back *
nfp_net_tls_set_ipv4(काष्ठा nfp_net *nn, काष्ठा nfp_crypto_req_add_v4 *req,
		     काष्ठा sock *sk, पूर्णांक direction)
अणु
	काष्ठा inet_sock *inet = inet_sk(sk);

	req->front.key_len += माप(__be32) * 2;

	अगर (direction == TLS_OFFLOAD_CTX_सूची_TX) अणु
		nfp_net_tls_assign_conn_id(nn, &req->front);
	पूर्ण अन्यथा अणु
		req->src_ip = inet->inet_daddr;
		req->dst_ip = inet->inet_saddr;
	पूर्ण

	वापस &req->back;
पूर्ण

अटल काष्ठा nfp_crypto_req_add_back *
nfp_net_tls_set_ipv6(काष्ठा nfp_net *nn, काष्ठा nfp_crypto_req_add_v6 *req,
		     काष्ठा sock *sk, पूर्णांक direction)
अणु
#अगर IS_ENABLED(CONFIG_IPV6)
	काष्ठा ipv6_pinfo *np = inet6_sk(sk);

	req->front.key_len += माप(काष्ठा in6_addr) * 2;

	अगर (direction == TLS_OFFLOAD_CTX_सूची_TX) अणु
		nfp_net_tls_assign_conn_id(nn, &req->front);
	पूर्ण अन्यथा अणु
		स_नकल(req->src_ip, &sk->sk_v6_daddr, माप(req->src_ip));
		स_नकल(req->dst_ip, &np->saddr, माप(req->dst_ip));
	पूर्ण

#पूर्ण_अगर
	वापस &req->back;
पूर्ण

अटल व्योम
nfp_net_tls_set_l4(काष्ठा nfp_crypto_req_add_front *front,
		   काष्ठा nfp_crypto_req_add_back *back, काष्ठा sock *sk,
		   पूर्णांक direction)
अणु
	काष्ठा inet_sock *inet = inet_sk(sk);

	front->l4_proto = IPPROTO_TCP;

	अगर (direction == TLS_OFFLOAD_CTX_सूची_TX) अणु
		back->src_port = 0;
		back->dst_port = 0;
	पूर्ण अन्यथा अणु
		back->src_port = inet->inet_dport;
		back->dst_port = inet->inet_sport;
	पूर्ण
पूर्ण

अटल u8 nfp_tls_1_2_dir_to_opcode(क्रमागत tls_offload_ctx_dir direction)
अणु
	चयन (direction) अणु
	हाल TLS_OFFLOAD_CTX_सूची_TX:
		वापस NFP_NET_CRYPTO_OP_TLS_1_2_AES_GCM_128_ENC;
	हाल TLS_OFFLOAD_CTX_सूची_RX:
		वापस NFP_NET_CRYPTO_OP_TLS_1_2_AES_GCM_128_DEC;
	शेष:
		WARN_ON_ONCE(1);
		वापस 0;
	पूर्ण
पूर्ण

अटल bool
nfp_net_cipher_supported(काष्ठा nfp_net *nn, u16 cipher_type,
			 क्रमागत tls_offload_ctx_dir direction)
अणु
	u8 bit;

	चयन (cipher_type) अणु
	हाल TLS_CIPHER_AES_GCM_128:
		अगर (direction == TLS_OFFLOAD_CTX_सूची_TX)
			bit = NFP_NET_CRYPTO_OP_TLS_1_2_AES_GCM_128_ENC;
		अन्यथा
			bit = NFP_NET_CRYPTO_OP_TLS_1_2_AES_GCM_128_DEC;
		अवरोध;
	शेष:
		वापस false;
	पूर्ण

	वापस nn->tlv_caps.crypto_ops & BIT(bit);
पूर्ण

अटल पूर्णांक
nfp_net_tls_add(काष्ठा net_device *netdev, काष्ठा sock *sk,
		क्रमागत tls_offload_ctx_dir direction,
		काष्ठा tls_crypto_info *crypto_info,
		u32 start_offload_tcp_sn)
अणु
	काष्ठा tls12_crypto_info_aes_gcm_128 *tls_ci;
	काष्ठा nfp_net *nn = netdev_priv(netdev);
	काष्ठा nfp_crypto_req_add_front *front;
	काष्ठा nfp_net_tls_offload_ctx *ntls;
	काष्ठा nfp_crypto_req_add_back *back;
	काष्ठा nfp_crypto_reply_add *reply;
	काष्ठा sk_buff *skb;
	माप_प्रकार req_sz;
	व्योम *req;
	bool ipv6;
	पूर्णांक err;

	BUILD_BUG_ON(माप(काष्ठा nfp_net_tls_offload_ctx) >
		     TLS_DRIVER_STATE_SIZE_TX);
	BUILD_BUG_ON(दुरत्व(काष्ठा nfp_net_tls_offload_ctx, rx_end) >
		     TLS_DRIVER_STATE_SIZE_RX);

	अगर (!nfp_net_cipher_supported(nn, crypto_info->cipher_type, direction))
		वापस -EOPNOTSUPP;

	चयन (sk->sk_family) अणु
#अगर IS_ENABLED(CONFIG_IPV6)
	हाल AF_INET6:
		अगर (sk->sk_ipv6only ||
		    ipv6_addr_type(&sk->sk_v6_daddr) != IPV6_ADDR_MAPPED) अणु
			req_sz = माप(काष्ठा nfp_crypto_req_add_v6);
			ipv6 = true;
			अवरोध;
		पूर्ण
		fallthrough;
#पूर्ण_अगर
	हाल AF_INET:
		req_sz = माप(काष्ठा nfp_crypto_req_add_v4);
		ipv6 = false;
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	err = nfp_net_tls_conn_add(nn, direction);
	अगर (err)
		वापस err;

	skb = nfp_ccm_mbox_msg_alloc(nn, req_sz, माप(*reply), GFP_KERNEL);
	अगर (!skb) अणु
		err = -ENOMEM;
		जाओ err_conn_हटाओ;
	पूर्ण

	front = (व्योम *)skb->data;
	front->ep_id = 0;
	front->key_len = NFP_NET_TLS_NON_ADDR_KEY_LEN;
	front->opcode = nfp_tls_1_2_dir_to_opcode(direction);
	स_रखो(front->resv, 0, माप(front->resv));

	nfp_net_tls_set_ipver_vlan(front, ipv6 ? 6 : 4);

	req = (व्योम *)skb->data;
	अगर (ipv6)
		back = nfp_net_tls_set_ipv6(nn, req, sk, direction);
	अन्यथा
		back = nfp_net_tls_set_ipv4(nn, req, sk, direction);

	nfp_net_tls_set_l4(front, back, sk, direction);

	back->counter = 0;
	back->tcp_seq = cpu_to_be32(start_offload_tcp_sn);

	tls_ci = (काष्ठा tls12_crypto_info_aes_gcm_128 *)crypto_info;
	स_नकल(back->key, tls_ci->key, TLS_CIPHER_AES_GCM_128_KEY_SIZE);
	स_रखो(&back->key[TLS_CIPHER_AES_GCM_128_KEY_SIZE / 4], 0,
	       माप(back->key) - TLS_CIPHER_AES_GCM_128_KEY_SIZE);
	स_नकल(back->iv, tls_ci->iv, TLS_CIPHER_AES_GCM_128_IV_SIZE);
	स_नकल(&back->salt, tls_ci->salt, TLS_CIPHER_AES_GCM_128_SALT_SIZE);
	स_नकल(back->rec_no, tls_ci->rec_seq, माप(tls_ci->rec_seq));

	/* Get an extra ref on the skb so we can wipe the key after */
	skb_get(skb);

	err = nfp_ccm_mbox_communicate(nn, skb, NFP_CCM_TYPE_CRYPTO_ADD,
				       माप(*reply), माप(*reply));
	reply = (व्योम *)skb->data;

	/* We depend on CCM MBOX code not पुनः_स्मृतिating skb we sent
	 * so we can clear the key material out of the memory.
	 */
	अगर (!WARN_ON_ONCE((u8 *)back < skb->head ||
			  (u8 *)back > skb_end_poपूर्णांकer(skb)) &&
	    !WARN_ON_ONCE((u8 *)&reply[1] > (u8 *)back))
		memzero_explicit(back, माप(*back));
	dev_consume_skb_any(skb); /* the extra ref from skb_get() above */

	अगर (err) अणु
		nn_dp_warn(&nn->dp, "failed to add TLS: %d (%d)\n",
			   err, direction == TLS_OFFLOAD_CTX_सूची_TX);
		/* communicate मुक्तs skb on error */
		जाओ err_conn_हटाओ;
	पूर्ण

	err = -be32_to_cpu(reply->error);
	अगर (err) अणु
		अगर (err == -ENOSPC) अणु
			अगर (!atomic_fetch_inc(&nn->ktls_no_space))
				nn_info(nn, "HW TLS table full\n");
		पूर्ण अन्यथा अणु
			nn_dp_warn(&nn->dp,
				   "failed to add TLS, FW replied: %d\n", err);
		पूर्ण
		जाओ err_मुक्त_skb;
	पूर्ण

	अगर (!reply->handle[0] && !reply->handle[1]) अणु
		nn_dp_warn(&nn->dp, "FW returned NULL handle\n");
		err = -EINVAL;
		जाओ err_fw_हटाओ;
	पूर्ण

	ntls = tls_driver_ctx(sk, direction);
	स_नकल(ntls->fw_handle, reply->handle, माप(ntls->fw_handle));
	अगर (direction == TLS_OFFLOAD_CTX_सूची_TX)
		ntls->next_seq = start_offload_tcp_sn;
	dev_consume_skb_any(skb);

	अगर (direction == TLS_OFFLOAD_CTX_सूची_TX)
		वापस 0;

	अगर (!nn->tlv_caps.tls_resync_ss)
		tls_offload_rx_resync_set_type(sk, TLS_OFFLOAD_SYNC_TYPE_CORE_NEXT_HINT);

	वापस 0;

err_fw_हटाओ:
	nfp_net_tls_del_fw(nn, reply->handle);
err_मुक्त_skb:
	dev_consume_skb_any(skb);
err_conn_हटाओ:
	nfp_net_tls_conn_हटाओ(nn, direction);
	वापस err;
पूर्ण

अटल व्योम
nfp_net_tls_del(काष्ठा net_device *netdev, काष्ठा tls_context *tls_ctx,
		क्रमागत tls_offload_ctx_dir direction)
अणु
	काष्ठा nfp_net *nn = netdev_priv(netdev);
	काष्ठा nfp_net_tls_offload_ctx *ntls;

	nfp_net_tls_conn_हटाओ(nn, direction);

	ntls = __tls_driver_ctx(tls_ctx, direction);
	nfp_net_tls_del_fw(nn, ntls->fw_handle);
पूर्ण

अटल पूर्णांक
nfp_net_tls_resync(काष्ठा net_device *netdev, काष्ठा sock *sk, u32 seq,
		   u8 *rcd_sn, क्रमागत tls_offload_ctx_dir direction)
अणु
	काष्ठा nfp_net *nn = netdev_priv(netdev);
	काष्ठा nfp_net_tls_offload_ctx *ntls;
	काष्ठा nfp_crypto_req_update *req;
	क्रमागत nfp_ccm_type type;
	काष्ठा sk_buff *skb;
	gfp_t flags;
	पूर्णांक err;

	flags = direction == TLS_OFFLOAD_CTX_सूची_TX ? GFP_KERNEL : GFP_ATOMIC;
	skb = nfp_net_tls_alloc_simple(nn, माप(*req), flags);
	अगर (!skb)
		वापस -ENOMEM;

	ntls = tls_driver_ctx(sk, direction);
	req = (व्योम *)skb->data;
	req->ep_id = 0;
	req->opcode = nfp_tls_1_2_dir_to_opcode(direction);
	स_रखो(req->resv, 0, माप(req->resv));
	स_नकल(req->handle, ntls->fw_handle, माप(ntls->fw_handle));
	req->tcp_seq = cpu_to_be32(seq);
	स_नकल(req->rec_no, rcd_sn, माप(req->rec_no));

	type = NFP_CCM_TYPE_CRYPTO_UPDATE;
	अगर (direction == TLS_OFFLOAD_CTX_सूची_TX) अणु
		err = nfp_net_tls_communicate_simple(nn, skb, "sync", type);
		अगर (err)
			वापस err;
		ntls->next_seq = seq;
	पूर्ण अन्यथा अणु
		अगर (nn->tlv_caps.tls_resync_ss)
			type = NFP_CCM_TYPE_CRYPTO_RESYNC;
		nfp_ccm_mbox_post(nn, skb, type,
				  माप(काष्ठा nfp_crypto_reply_simple));
		atomic_inc(&nn->ktls_rx_resync_sent);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा tlsdev_ops nfp_net_tls_ops = अणु
	.tls_dev_add = nfp_net_tls_add,
	.tls_dev_del = nfp_net_tls_del,
	.tls_dev_resync = nfp_net_tls_resync,
पूर्ण;

पूर्णांक nfp_net_tls_rx_resync_req(काष्ठा net_device *netdev,
			      काष्ठा nfp_net_tls_resync_req *req,
			      व्योम *pkt, अचिन्हित पूर्णांक pkt_len)
अणु
	काष्ठा nfp_net *nn = netdev_priv(netdev);
	काष्ठा nfp_net_tls_offload_ctx *ntls;
	काष्ठा ipv6hdr *ipv6h;
	काष्ठा tcphdr *th;
	काष्ठा iphdr *iph;
	काष्ठा sock *sk;
	__be32 tcp_seq;
	पूर्णांक err;

	iph = pkt + req->l3_offset;
	ipv6h = pkt + req->l3_offset;
	th = pkt + req->l4_offset;

	अगर ((u8 *)&th[1] > (u8 *)pkt + pkt_len) अणु
		netdev_warn_once(netdev, "invalid TLS RX resync request (l3_off: %hhu l4_off: %hhu pkt_len: %u)\n",
				 req->l3_offset, req->l4_offset, pkt_len);
		err = -EINVAL;
		जाओ err_cnt_ign;
	पूर्ण

	चयन (ipv6h->version) अणु
	हाल 4:
		sk = inet_lookup_established(dev_net(netdev), &tcp_hashinfo,
					     iph->saddr, th->source, iph->daddr,
					     th->dest, netdev->अगरindex);
		अवरोध;
#अगर IS_ENABLED(CONFIG_IPV6)
	हाल 6:
		sk = __inet6_lookup_established(dev_net(netdev), &tcp_hashinfo,
						&ipv6h->saddr, th->source,
						&ipv6h->daddr, ntohs(th->dest),
						netdev->अगरindex, 0);
		अवरोध;
#पूर्ण_अगर
	शेष:
		netdev_warn_once(netdev, "invalid TLS RX resync request (l3_off: %hhu l4_off: %hhu ipver: %u)\n",
				 req->l3_offset, req->l4_offset, iph->version);
		err = -EINVAL;
		जाओ err_cnt_ign;
	पूर्ण

	err = 0;
	अगर (!sk)
		जाओ err_cnt_ign;
	अगर (!tls_is_sk_rx_device_offloaded(sk) ||
	    sk->sk_shutकरोwn & RCV_SHUTDOWN)
		जाओ err_put_sock;

	ntls = tls_driver_ctx(sk, TLS_OFFLOAD_CTX_सूची_RX);
	/* some FW versions can't report the handle and report 0s */
	अगर (स_प्रथम_inv(&req->fw_handle, 0, माप(req->fw_handle)) &&
	    स_भेद(&req->fw_handle, &ntls->fw_handle, माप(ntls->fw_handle)))
		जाओ err_put_sock;

	/* copy to ensure alignment */
	स_नकल(&tcp_seq, &req->tcp_seq, माप(tcp_seq));
	tls_offload_rx_resync_request(sk, tcp_seq);
	atomic_inc(&nn->ktls_rx_resync_req);

	sock_gen_put(sk);
	वापस 0;

err_put_sock:
	sock_gen_put(sk);
err_cnt_ign:
	atomic_inc(&nn->ktls_rx_resync_ign);
	वापस err;
पूर्ण

अटल पूर्णांक nfp_net_tls_reset(काष्ठा nfp_net *nn)
अणु
	काष्ठा nfp_crypto_req_reset *req;
	काष्ठा sk_buff *skb;

	skb = nfp_net_tls_alloc_simple(nn, माप(*req), GFP_KERNEL);
	अगर (!skb)
		वापस -ENOMEM;

	req = (व्योम *)skb->data;
	req->ep_id = 0;

	वापस nfp_net_tls_communicate_simple(nn, skb, "reset",
					      NFP_CCM_TYPE_CRYPTO_RESET);
पूर्ण

पूर्णांक nfp_net_tls_init(काष्ठा nfp_net *nn)
अणु
	काष्ठा net_device *netdev = nn->dp.netdev;
	पूर्णांक err;

	अगर (!(nn->tlv_caps.crypto_ops & NFP_NET_TLS_OPCODE_MASK))
		वापस 0;

	अगर ((nn->tlv_caps.mbox_cmsg_types & NFP_NET_TLS_CCM_MBOX_OPS_MASK) !=
	    NFP_NET_TLS_CCM_MBOX_OPS_MASK)
		वापस 0;

	अगर (!nfp_ccm_mbox_fits(nn, माप(काष्ठा nfp_crypto_req_add_v6))) अणु
		nn_warn(nn, "disabling TLS offload - mbox too small: %d\n",
			nn->tlv_caps.mbox_len);
		वापस 0;
	पूर्ण

	err = nfp_net_tls_reset(nn);
	अगर (err)
		वापस err;

	nn_ctrl_bar_lock(nn);
	nn_ग_लिखोl(nn, nn->tlv_caps.crypto_enable_off, 0);
	err = __nfp_net_reconfig(nn, NFP_NET_CFG_UPDATE_CRYPTO);
	nn_ctrl_bar_unlock(nn);
	अगर (err)
		वापस err;

	अगर (nn->tlv_caps.crypto_ops & NFP_NET_TLS_OPCODE_MASK_RX) अणु
		netdev->hw_features |= NETIF_F_HW_TLS_RX;
		netdev->features |= NETIF_F_HW_TLS_RX;
	पूर्ण
	अगर (nn->tlv_caps.crypto_ops & NFP_NET_TLS_OPCODE_MASK_TX) अणु
		netdev->hw_features |= NETIF_F_HW_TLS_TX;
		netdev->features |= NETIF_F_HW_TLS_TX;
	पूर्ण

	netdev->tlsdev_ops = &nfp_net_tls_ops;

	वापस 0;
पूर्ण
