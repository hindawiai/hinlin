<शैली गुरु>
/*
 * Copyright (c) 2018 Mellanox Technologies. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary क्रमms, with or
 *     without modअगरication, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary क्रमm must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the करोcumentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */

#समावेश "en_accel/tls.h"
#समावेश "en_accel/tls_rxtx.h"
#समावेश "accel/accel.h"

#समावेश <net/inet6_hashtables.h>
#समावेश <linux/ipv6.h>

#घोषणा SYNDROM_DECRYPTED  0x30
#घोषणा SYNDROM_RESYNC_REQUEST 0x31
#घोषणा SYNDROM_AUTH_FAILED 0x32

#घोषणा SYNDROME_OFFLOAD_REQUIRED 32
#घोषणा SYNDROME_SYNC 33

काष्ठा sync_info अणु
	u64 rcd_sn;
	s32 sync_len;
	पूर्णांक nr_frags;
	skb_frag_t frags[MAX_SKB_FRAGS];
पूर्ण;

काष्ठा recv_metadata_content अणु
	u8 syndrome;
	u8 reserved;
	__be32 sync_seq;
पूर्ण __packed;

काष्ठा send_metadata_content अणु
	/* One byte of syndrome followed by 3 bytes of swid */
	__be32 syndrome_swid;
	__be16 first_seq;
पूर्ण __packed;

काष्ठा mlx5e_tls_metadata अणु
	जोड़ अणु
		/* from fpga to host */
		काष्ठा recv_metadata_content recv;
		/* from host to fpga */
		काष्ठा send_metadata_content send;
		अचिन्हित अक्षर raw[6];
	पूर्ण __packed content;
	/* packet type ID field	*/
	__be16 ethertype;
पूर्ण __packed;

अटल पूर्णांक mlx5e_tls_add_metadata(काष्ठा sk_buff *skb, __be32 swid)
अणु
	काष्ठा mlx5e_tls_metadata *pet;
	काष्ठा ethhdr *eth;

	अगर (skb_cow_head(skb, माप(काष्ठा mlx5e_tls_metadata)))
		वापस -ENOMEM;

	eth = (काष्ठा ethhdr *)skb_push(skb, माप(काष्ठा mlx5e_tls_metadata));
	skb->mac_header -= माप(काष्ठा mlx5e_tls_metadata);
	pet = (काष्ठा mlx5e_tls_metadata *)(eth + 1);

	स_हटाओ(skb->data, skb->data + माप(काष्ठा mlx5e_tls_metadata),
		2 * ETH_ALEN);

	eth->h_proto = cpu_to_be16(MLX5E_METADATA_ETHER_TYPE);
	pet->content.send.syndrome_swid =
		htonl(SYNDROME_OFFLOAD_REQUIRED << 24) | swid;

	वापस 0;
पूर्ण

अटल पूर्णांक mlx5e_tls_get_sync_data(काष्ठा mlx5e_tls_offload_context_tx *context,
				   u32 tcp_seq, काष्ठा sync_info *info)
अणु
	पूर्णांक reमुख्यing, i = 0, ret = -EINVAL;
	काष्ठा tls_record_info *record;
	अचिन्हित दीर्घ flags;
	s32 sync_size;

	spin_lock_irqsave(&context->base.lock, flags);
	record = tls_get_record(&context->base, tcp_seq, &info->rcd_sn);

	अगर (unlikely(!record))
		जाओ out;

	sync_size = tcp_seq - tls_record_start_seq(record);
	info->sync_len = sync_size;
	अगर (unlikely(sync_size < 0)) अणु
		अगर (tls_record_is_start_marker(record))
			जाओ करोne;

		जाओ out;
	पूर्ण

	reमुख्यing = sync_size;
	जबतक (reमुख्यing > 0) अणु
		info->frags[i] = record->frags[i];
		__skb_frag_ref(&info->frags[i]);
		reमुख्यing -= skb_frag_size(&info->frags[i]);

		अगर (reमुख्यing < 0)
			skb_frag_size_add(&info->frags[i], reमुख्यing);

		i++;
	पूर्ण
	info->nr_frags = i;
करोne:
	ret = 0;
out:
	spin_unlock_irqrestore(&context->base.lock, flags);
	वापस ret;
पूर्ण

अटल व्योम mlx5e_tls_complete_sync_skb(काष्ठा sk_buff *skb,
					काष्ठा sk_buff *nskb, u32 tcp_seq,
					पूर्णांक headln, __be64 rcd_sn)
अणु
	काष्ठा mlx5e_tls_metadata *pet;
	u8 syndrome = SYNDROME_SYNC;
	काष्ठा iphdr *iph;
	काष्ठा tcphdr *th;
	पूर्णांक data_len, mss;

	nskb->dev = skb->dev;
	skb_reset_mac_header(nskb);
	skb_set_network_header(nskb, skb_network_offset(skb));
	skb_set_transport_header(nskb, skb_transport_offset(skb));
	स_नकल(nskb->data, skb->data, headln);
	स_नकल(nskb->data + headln, &rcd_sn, माप(rcd_sn));

	iph = ip_hdr(nskb);
	iph->tot_len = htons(nskb->len - skb_network_offset(nskb));
	th = tcp_hdr(nskb);
	data_len = nskb->len - headln;
	tcp_seq -= data_len;
	th->seq = htonl(tcp_seq);

	mss = nskb->dev->mtu - (headln - skb_network_offset(nskb));
	skb_shinfo(nskb)->gso_size = 0;
	अगर (data_len > mss) अणु
		skb_shinfo(nskb)->gso_size = mss;
		skb_shinfo(nskb)->gso_segs = DIV_ROUND_UP(data_len, mss);
	पूर्ण
	skb_shinfo(nskb)->gso_type = skb_shinfo(skb)->gso_type;

	pet = (काष्ठा mlx5e_tls_metadata *)(nskb->data + माप(काष्ठा ethhdr));
	स_नकल(pet, &syndrome, माप(syndrome));
	pet->content.send.first_seq = htons(tcp_seq);

	/* MLX5 devices करोn't care about the checksum partial start, offset
	 * and pseuकरो header
	 */
	nskb->ip_summed = CHECKSUM_PARTIAL;

	nskb->queue_mapping = skb->queue_mapping;
पूर्ण

अटल bool mlx5e_tls_handle_ooo(काष्ठा mlx5e_tls_offload_context_tx *context,
				 काष्ठा mlx5e_txqsq *sq, काष्ठा sk_buff *skb,
				 काष्ठा mlx5e_tls *tls)
अणु
	u32 tcp_seq = ntohl(tcp_hdr(skb)->seq);
	काष्ठा sync_info info;
	काष्ठा sk_buff *nskb;
	पूर्णांक linear_len = 0;
	पूर्णांक headln;
	पूर्णांक i;

	sq->stats->tls_ooo++;

	अगर (mlx5e_tls_get_sync_data(context, tcp_seq, &info)) अणु
		/* We might get here अगर a retransmission reaches the driver
		 * after the relevant record is acked.
		 * It should be safe to drop the packet in this हाल
		 */
		atomic64_inc(&tls->sw_stats.tx_tls_drop_no_sync_data);
		जाओ err_out;
	पूर्ण

	अगर (unlikely(info.sync_len < 0)) अणु
		u32 payload;

		headln = skb_transport_offset(skb) + tcp_hdrlen(skb);
		payload = skb->len - headln;
		अगर (likely(payload <= -info.sync_len))
			/* SKB payload करोesn't require offload
			 */
			वापस true;

		atomic64_inc(&tls->sw_stats.tx_tls_drop_bypass_required);
		जाओ err_out;
	पूर्ण

	अगर (unlikely(mlx5e_tls_add_metadata(skb, context->swid))) अणु
		atomic64_inc(&tls->sw_stats.tx_tls_drop_metadata);
		जाओ err_out;
	पूर्ण

	headln = skb_transport_offset(skb) + tcp_hdrlen(skb);
	linear_len += headln + माप(info.rcd_sn);
	nskb = alloc_skb(linear_len, GFP_ATOMIC);
	अगर (unlikely(!nskb)) अणु
		atomic64_inc(&tls->sw_stats.tx_tls_drop_resync_alloc);
		जाओ err_out;
	पूर्ण

	context->expected_seq = tcp_seq + skb->len - headln;
	skb_put(nskb, linear_len);
	क्रम (i = 0; i < info.nr_frags; i++)
		skb_shinfo(nskb)->frags[i] = info.frags[i];

	skb_shinfo(nskb)->nr_frags = info.nr_frags;
	nskb->data_len = info.sync_len;
	nskb->len += info.sync_len;
	sq->stats->tls_resync_bytes += nskb->len;
	mlx5e_tls_complete_sync_skb(skb, nskb, tcp_seq, headln,
				    cpu_to_be64(info.rcd_sn));
	mlx5e_sq_xmit_simple(sq, nskb, true);

	वापस true;

err_out:
	dev_kमुक्त_skb_any(skb);
	वापस false;
पूर्ण

bool mlx5e_tls_handle_tx_skb(काष्ठा net_device *netdev, काष्ठा mlx5e_txqsq *sq,
			     काष्ठा sk_buff *skb, काष्ठा mlx5e_accel_tx_tls_state *state)
अणु
	काष्ठा mlx5e_priv *priv = netdev_priv(netdev);
	काष्ठा mlx5e_tls_offload_context_tx *context;
	काष्ठा tls_context *tls_ctx;
	u32 expected_seq;
	पूर्णांक datalen;
	u32 skb_seq;

	datalen = skb->len - (skb_transport_offset(skb) + tcp_hdrlen(skb));
	अगर (!datalen)
		वापस true;

	mlx5e_tx_mpwqe_ensure_complete(sq);

	tls_ctx = tls_get_ctx(skb->sk);
	अगर (WARN_ON_ONCE(tls_ctx->netdev != netdev))
		जाओ err_out;

	अगर (mlx5_accel_is_ktls_tx(sq->mdev))
		वापस mlx5e_ktls_handle_tx_skb(tls_ctx, sq, skb, datalen, state);

	/* FPGA */
	skb_seq = ntohl(tcp_hdr(skb)->seq);
	context = mlx5e_get_tls_tx_context(tls_ctx);
	expected_seq = context->expected_seq;

	अगर (unlikely(expected_seq != skb_seq))
		वापस mlx5e_tls_handle_ooo(context, sq, skb, priv->tls);

	अगर (unlikely(mlx5e_tls_add_metadata(skb, context->swid))) अणु
		atomic64_inc(&priv->tls->sw_stats.tx_tls_drop_metadata);
		dev_kमुक्त_skb_any(skb);
		वापस false;
	पूर्ण

	context->expected_seq = skb_seq + datalen;
	वापस true;

err_out:
	dev_kमुक्त_skb_any(skb);
	वापस false;
पूर्ण

अटल पूर्णांक tls_update_resync_sn(काष्ठा net_device *netdev,
				काष्ठा sk_buff *skb,
				काष्ठा mlx5e_tls_metadata *mdata)
अणु
	काष्ठा sock *sk = शून्य;
	काष्ठा iphdr *iph;
	काष्ठा tcphdr *th;
	__be32 seq;

	अगर (mdata->ethertype != htons(ETH_P_IP))
		वापस -EINVAL;

	iph = (काष्ठा iphdr *)(mdata + 1);

	th = ((व्योम *)iph) + iph->ihl * 4;

	अगर (iph->version == 4) अणु
		sk = inet_lookup_established(dev_net(netdev), &tcp_hashinfo,
					     iph->saddr, th->source, iph->daddr,
					     th->dest, netdev->अगरindex);
#अगर IS_ENABLED(CONFIG_IPV6)
	पूर्ण अन्यथा अणु
		काष्ठा ipv6hdr *ipv6h = (काष्ठा ipv6hdr *)iph;

		sk = __inet6_lookup_established(dev_net(netdev), &tcp_hashinfo,
						&ipv6h->saddr, th->source,
						&ipv6h->daddr, ntohs(th->dest),
						netdev->अगरindex, 0);
#पूर्ण_अगर
	पूर्ण
	अगर (!sk || sk->sk_state == TCP_TIME_WAIT) अणु
		काष्ठा mlx5e_priv *priv = netdev_priv(netdev);

		atomic64_inc(&priv->tls->sw_stats.rx_tls_drop_resync_request);
		जाओ out;
	पूर्ण

	skb->sk = sk;
	skb->deकाष्ठाor = sock_edemux;

	स_नकल(&seq, &mdata->content.recv.sync_seq, माप(seq));
	tls_offload_rx_resync_request(sk, seq);
out:
	वापस 0;
पूर्ण

/* FPGA tls rx handler */
व्योम mlx5e_tls_handle_rx_skb_metadata(काष्ठा mlx5e_rq *rq, काष्ठा sk_buff *skb,
				      u32 *cqe_bcnt)
अणु
	काष्ठा mlx5e_tls_metadata *mdata;
	काष्ठा mlx5e_priv *priv;

	/* Use the metadata */
	mdata = (काष्ठा mlx5e_tls_metadata *)(skb->data + ETH_HLEN);
	चयन (mdata->content.recv.syndrome) अणु
	हाल SYNDROM_DECRYPTED:
		skb->decrypted = 1;
		अवरोध;
	हाल SYNDROM_RESYNC_REQUEST:
		tls_update_resync_sn(rq->netdev, skb, mdata);
		priv = netdev_priv(rq->netdev);
		atomic64_inc(&priv->tls->sw_stats.rx_tls_resync_request);
		अवरोध;
	हाल SYNDROM_AUTH_FAILED:
		/* Authentication failure will be observed and verअगरied by kTLS */
		priv = netdev_priv(rq->netdev);
		atomic64_inc(&priv->tls->sw_stats.rx_tls_auth_fail);
		अवरोध;
	शेष:
		/* Bypass the metadata header to others */
		वापस;
	पूर्ण

	हटाओ_metadata_hdr(skb);
	*cqe_bcnt -= MLX5E_METADATA_ETHER_LEN;
पूर्ण

u16 mlx5e_tls_get_stop_room(काष्ठा mlx5_core_dev *mdev, काष्ठा mlx5e_params *params)
अणु
	अगर (!mlx5_accel_is_tls_device(mdev))
		वापस 0;

	अगर (mlx5_accel_is_ktls_device(mdev))
		वापस mlx5e_ktls_get_stop_room(params);

	/* FPGA */
	/* Resync SKB. */
	वापस mlx5e_stop_room_क्रम_wqe(MLX5_SEND_WQE_MAX_WQEBBS);
पूर्ण
