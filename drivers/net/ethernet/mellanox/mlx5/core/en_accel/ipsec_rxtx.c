<शैली गुरु>
/*
 * Copyright (c) 2017 Mellanox Technologies. All rights reserved.
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

#समावेश <crypto/aead.h>
#समावेश <net/xfrm.h>
#समावेश <net/esp.h>
#समावेश "accel/ipsec_offload.h"
#समावेश "en_accel/ipsec_rxtx.h"
#समावेश "en_accel/ipsec.h"
#समावेश "accel/accel.h"
#समावेश "en.h"

क्रमागत अणु
	MLX5E_IPSEC_RX_SYNDROME_DECRYPTED = 0x11,
	MLX5E_IPSEC_RX_SYNDROME_AUTH_FAILED = 0x12,
	MLX5E_IPSEC_RX_SYNDROME_BAD_PROTO = 0x17,
पूर्ण;

काष्ठा mlx5e_ipsec_rx_metadata अणु
	अचिन्हित अक्षर   nexthdr;
	__be32		sa_handle;
पूर्ण __packed;

क्रमागत अणु
	MLX5E_IPSEC_TX_SYNDROME_OFFLOAD = 0x8,
	MLX5E_IPSEC_TX_SYNDROME_OFFLOAD_WITH_LSO_TCP = 0x9,
पूर्ण;

काष्ठा mlx5e_ipsec_tx_metadata अणु
	__be16 mss_inv;         /* 1/MSS in 16bit fixed poपूर्णांक, only क्रम LSO */
	__be16 seq;             /* LSBs of the first TCP seq, only क्रम LSO */
	u8     esp_next_proto;  /* Next protocol of ESP */
पूर्ण __packed;

काष्ठा mlx5e_ipsec_metadata अणु
	अचिन्हित अक्षर syndrome;
	जोड़ अणु
		अचिन्हित अक्षर raw[5];
		/* from FPGA to host, on successful decrypt */
		काष्ठा mlx5e_ipsec_rx_metadata rx;
		/* from host to FPGA */
		काष्ठा mlx5e_ipsec_tx_metadata tx;
	पूर्ण __packed content;
	/* packet type ID field	*/
	__be16 ethertype;
पूर्ण __packed;

#घोषणा MAX_LSO_MSS 2048

/* Pre-calculated (Q0.16) fixed-poपूर्णांक inverse 1/x function */
अटल __be16 mlx5e_ipsec_inverse_table[MAX_LSO_MSS];

अटल अंतरभूत __be16 mlx5e_ipsec_mss_inv(काष्ठा sk_buff *skb)
अणु
	वापस mlx5e_ipsec_inverse_table[skb_shinfo(skb)->gso_size];
पूर्ण

अटल काष्ठा mlx5e_ipsec_metadata *mlx5e_ipsec_add_metadata(काष्ठा sk_buff *skb)
अणु
	काष्ठा mlx5e_ipsec_metadata *mdata;
	काष्ठा ethhdr *eth;

	अगर (unlikely(skb_cow_head(skb, माप(*mdata))))
		वापस ERR_PTR(-ENOMEM);

	eth = (काष्ठा ethhdr *)skb_push(skb, माप(*mdata));
	skb->mac_header -= माप(*mdata);
	mdata = (काष्ठा mlx5e_ipsec_metadata *)(eth + 1);

	स_हटाओ(skb->data, skb->data + माप(*mdata),
		2 * ETH_ALEN);

	eth->h_proto = cpu_to_be16(MLX5E_METADATA_ETHER_TYPE);

	स_रखो(mdata->content.raw, 0, माप(mdata->content.raw));
	वापस mdata;
पूर्ण

अटल पूर्णांक mlx5e_ipsec_हटाओ_trailer(काष्ठा sk_buff *skb, काष्ठा xfrm_state *x)
अणु
	अचिन्हित पूर्णांक alen = crypto_aead_authsize(x->data);
	काष्ठा ipv6hdr *ipv6hdr = ipv6_hdr(skb);
	काष्ठा iphdr *ipv4hdr = ip_hdr(skb);
	अचिन्हित पूर्णांक trailer_len;
	u8 plen;
	पूर्णांक ret;

	ret = skb_copy_bits(skb, skb->len - alen - 2, &plen, 1);
	अगर (unlikely(ret))
		वापस ret;

	trailer_len = alen + plen + 2;

	pskb_trim(skb, skb->len - trailer_len);
	अगर (skb->protocol == htons(ETH_P_IP)) अणु
		ipv4hdr->tot_len = htons(ntohs(ipv4hdr->tot_len) - trailer_len);
		ip_send_check(ipv4hdr);
	पूर्ण अन्यथा अणु
		ipv6hdr->payload_len = htons(ntohs(ipv6hdr->payload_len) -
					     trailer_len);
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम mlx5e_ipsec_set_swp(काष्ठा sk_buff *skb,
				काष्ठा mlx5_wqe_eth_seg *eseg, u8 mode,
				काष्ठा xfrm_offload *xo)
अणु
	काष्ठा mlx5e_swp_spec swp_spec = अणुपूर्ण;

	/* Tunnel Mode:
	 * SWP:      OutL3       InL3  InL4
	 * Pkt: MAC  IP     ESP  IP    L4
	 *
	 * Transport Mode:
	 * SWP:      OutL3       InL4
	 *           InL3
	 * Pkt: MAC  IP     ESP  L4
	 */
	swp_spec.l3_proto = skb->protocol;
	swp_spec.is_tun = mode == XFRM_MODE_TUNNEL;
	अगर (swp_spec.is_tun) अणु
		अगर (xo->proto == IPPROTO_IPV6) अणु
			swp_spec.tun_l3_proto = htons(ETH_P_IPV6);
			swp_spec.tun_l4_proto = inner_ipv6_hdr(skb)->nexthdr;
		पूर्ण अन्यथा अणु
			swp_spec.tun_l3_proto = htons(ETH_P_IP);
			swp_spec.tun_l4_proto = inner_ip_hdr(skb)->protocol;
		पूर्ण
	पूर्ण अन्यथा अणु
		swp_spec.tun_l3_proto = skb->protocol;
		swp_spec.tun_l4_proto = xo->proto;
	पूर्ण

	mlx5e_set_eseg_swp(skb, eseg, &swp_spec);
पूर्ण

व्योम mlx5e_ipsec_set_iv_esn(काष्ठा sk_buff *skb, काष्ठा xfrm_state *x,
			    काष्ठा xfrm_offload *xo)
अणु
	काष्ठा xfrm_replay_state_esn *replay_esn = x->replay_esn;
	__u32 oseq = replay_esn->oseq;
	पूर्णांक iv_offset;
	__be64 seqno;
	u32 seq_hi;

	अगर (unlikely(skb_is_gso(skb) && oseq < MLX5E_IPSEC_ESN_SCOPE_MID &&
		     MLX5E_IPSEC_ESN_SCOPE_MID < (oseq - skb_shinfo(skb)->gso_segs))) अणु
		seq_hi = xo->seq.hi - 1;
	पूर्ण अन्यथा अणु
		seq_hi = xo->seq.hi;
	पूर्ण

	/* Place the SN in the IV field */
	seqno = cpu_to_be64(xo->seq.low + ((u64)seq_hi << 32));
	iv_offset = skb_transport_offset(skb) + माप(काष्ठा ip_esp_hdr);
	skb_store_bits(skb, iv_offset, &seqno, 8);
पूर्ण

व्योम mlx5e_ipsec_set_iv(काष्ठा sk_buff *skb, काष्ठा xfrm_state *x,
			काष्ठा xfrm_offload *xo)
अणु
	पूर्णांक iv_offset;
	__be64 seqno;

	/* Place the SN in the IV field */
	seqno = cpu_to_be64(xo->seq.low + ((u64)xo->seq.hi << 32));
	iv_offset = skb_transport_offset(skb) + माप(काष्ठा ip_esp_hdr);
	skb_store_bits(skb, iv_offset, &seqno, 8);
पूर्ण

अटल व्योम mlx5e_ipsec_set_metadata(काष्ठा sk_buff *skb,
				     काष्ठा mlx5e_ipsec_metadata *mdata,
				     काष्ठा xfrm_offload *xo)
अणु
	काष्ठा ip_esp_hdr *esph;
	काष्ठा tcphdr *tcph;

	अगर (skb_is_gso(skb)) अणु
		/* Add LSO metadata indication */
		esph = ip_esp_hdr(skb);
		tcph = inner_tcp_hdr(skb);
		netdev_dbg(skb->dev, "   Offloading GSO packet outer L3 %u; L4 %u; Inner L3 %u; L4 %u\n",
			   skb->network_header,
			   skb->transport_header,
			   skb->inner_network_header,
			   skb->inner_transport_header);
		netdev_dbg(skb->dev, "   Offloading GSO packet of len %u; mss %u; TCP sp %u dp %u seq 0x%x ESP seq 0x%x\n",
			   skb->len, skb_shinfo(skb)->gso_size,
			   ntohs(tcph->source), ntohs(tcph->dest),
			   ntohl(tcph->seq), ntohl(esph->seq_no));
		mdata->syndrome = MLX5E_IPSEC_TX_SYNDROME_OFFLOAD_WITH_LSO_TCP;
		mdata->content.tx.mss_inv = mlx5e_ipsec_mss_inv(skb);
		mdata->content.tx.seq = htons(ntohl(tcph->seq) & 0xFFFF);
	पूर्ण अन्यथा अणु
		mdata->syndrome = MLX5E_IPSEC_TX_SYNDROME_OFFLOAD;
	पूर्ण
	mdata->content.tx.esp_next_proto = xo->proto;

	netdev_dbg(skb->dev, "   TX metadata syndrome %u proto %u mss_inv %04x seq %04x\n",
		   mdata->syndrome, mdata->content.tx.esp_next_proto,
		   ntohs(mdata->content.tx.mss_inv),
		   ntohs(mdata->content.tx.seq));
पूर्ण

व्योम mlx5e_ipsec_handle_tx_wqe(काष्ठा mlx5e_tx_wqe *wqe,
			       काष्ठा mlx5e_accel_tx_ipsec_state *ipsec_st,
			       काष्ठा mlx5_wqe_अंतरभूत_seg *inlseg)
अणु
	inlseg->byte_count = cpu_to_be32(ipsec_st->tailen | MLX5_INLINE_SEG);
	esp_output_fill_trailer((u8 *)inlseg->data, 0, ipsec_st->plen, ipsec_st->xo->proto);
पूर्ण

अटल पूर्णांक mlx5e_ipsec_set_state(काष्ठा mlx5e_priv *priv,
				 काष्ठा sk_buff *skb,
				 काष्ठा xfrm_state *x,
				 काष्ठा xfrm_offload *xo,
				 काष्ठा mlx5e_accel_tx_ipsec_state *ipsec_st)
अणु
	अचिन्हित पूर्णांक blksize, clen, alen, plen;
	काष्ठा crypto_aead *aead;
	अचिन्हित पूर्णांक tailen;

	ipsec_st->x = x;
	ipsec_st->xo = xo;
	अगर (mlx5_is_ipsec_device(priv->mdev)) अणु
		aead = x->data;
		alen = crypto_aead_authsize(aead);
		blksize = ALIGN(crypto_aead_blocksize(aead), 4);
		clen = ALIGN(skb->len + 2, blksize);
		plen = max_t(u32, clen - skb->len, 4);
		tailen = plen + alen;
		ipsec_st->plen = plen;
		ipsec_st->tailen = tailen;
	पूर्ण

	वापस 0;
पूर्ण

व्योम mlx5e_ipsec_tx_build_eseg(काष्ठा mlx5e_priv *priv, काष्ठा sk_buff *skb,
			       काष्ठा mlx5_wqe_eth_seg *eseg)
अणु
	काष्ठा xfrm_offload *xo = xfrm_offload(skb);
	काष्ठा xfrm_encap_पंचांगpl  *encap;
	काष्ठा xfrm_state *x;
	काष्ठा sec_path *sp;
	u8 l3_proto;

	sp = skb_sec_path(skb);
	अगर (unlikely(sp->len != 1))
		वापस;

	x = xfrm_input_state(skb);
	अगर (unlikely(!x))
		वापस;

	अगर (unlikely(!x->xso.offload_handle ||
		     (skb->protocol != htons(ETH_P_IP) &&
		      skb->protocol != htons(ETH_P_IPV6))))
		वापस;

	mlx5e_ipsec_set_swp(skb, eseg, x->props.mode, xo);

	l3_proto = (x->props.family == AF_INET) ?
		   ((काष्ठा iphdr *)skb_network_header(skb))->protocol :
		   ((काष्ठा ipv6hdr *)skb_network_header(skb))->nexthdr;

	अगर (mlx5_is_ipsec_device(priv->mdev)) अणु
		eseg->flow_table_metadata |= cpu_to_be32(MLX5_ETH_WQE_FT_META_IPSEC);
		eseg->trailer |= cpu_to_be32(MLX5_ETH_WQE_INSERT_TRAILER);
		encap = x->encap;
		अगर (!encap) अणु
			eseg->trailer |= (l3_proto == IPPROTO_ESP) ?
				cpu_to_be32(MLX5_ETH_WQE_TRAILER_HDR_OUTER_IP_ASSOC) :
				cpu_to_be32(MLX5_ETH_WQE_TRAILER_HDR_OUTER_L4_ASSOC);
		पूर्ण अन्यथा अगर (encap->encap_type == UDP_ENCAP_ESPINUDP) अणु
			eseg->trailer |= (l3_proto == IPPROTO_ESP) ?
				cpu_to_be32(MLX5_ETH_WQE_TRAILER_HDR_INNER_IP_ASSOC) :
				cpu_to_be32(MLX5_ETH_WQE_TRAILER_HDR_INNER_L4_ASSOC);
		पूर्ण
	पूर्ण
पूर्ण

bool mlx5e_ipsec_handle_tx_skb(काष्ठा net_device *netdev,
			       काष्ठा sk_buff *skb,
			       काष्ठा mlx5e_accel_tx_ipsec_state *ipsec_st)
अणु
	काष्ठा mlx5e_priv *priv = netdev_priv(netdev);
	काष्ठा xfrm_offload *xo = xfrm_offload(skb);
	काष्ठा mlx5e_ipsec_sa_entry *sa_entry;
	काष्ठा mlx5e_ipsec_metadata *mdata;
	काष्ठा xfrm_state *x;
	काष्ठा sec_path *sp;

	sp = skb_sec_path(skb);
	अगर (unlikely(sp->len != 1)) अणु
		atomic64_inc(&priv->ipsec->sw_stats.ipsec_tx_drop_bundle);
		जाओ drop;
	पूर्ण

	x = xfrm_input_state(skb);
	अगर (unlikely(!x)) अणु
		atomic64_inc(&priv->ipsec->sw_stats.ipsec_tx_drop_no_state);
		जाओ drop;
	पूर्ण

	अगर (unlikely(!x->xso.offload_handle ||
		     (skb->protocol != htons(ETH_P_IP) &&
		      skb->protocol != htons(ETH_P_IPV6)))) अणु
		atomic64_inc(&priv->ipsec->sw_stats.ipsec_tx_drop_not_ip);
		जाओ drop;
	पूर्ण

	अगर (!skb_is_gso(skb))
		अगर (unlikely(mlx5e_ipsec_हटाओ_trailer(skb, x))) अणु
			atomic64_inc(&priv->ipsec->sw_stats.ipsec_tx_drop_trailer);
			जाओ drop;
		पूर्ण

	अगर (MLX5_CAP_GEN(priv->mdev, fpga)) अणु
		mdata = mlx5e_ipsec_add_metadata(skb);
		अगर (IS_ERR(mdata)) अणु
			atomic64_inc(&priv->ipsec->sw_stats.ipsec_tx_drop_metadata);
			जाओ drop;
		पूर्ण
	पूर्ण

	sa_entry = (काष्ठा mlx5e_ipsec_sa_entry *)x->xso.offload_handle;
	sa_entry->set_iv_op(skb, x, xo);
	अगर (MLX5_CAP_GEN(priv->mdev, fpga))
		mlx5e_ipsec_set_metadata(skb, mdata, xo);

	mlx5e_ipsec_set_state(priv, skb, x, xo, ipsec_st);

	वापस true;

drop:
	kमुक्त_skb(skb);
	वापस false;
पूर्ण

अटल अंतरभूत काष्ठा xfrm_state *
mlx5e_ipsec_build_sp(काष्ठा net_device *netdev, काष्ठा sk_buff *skb,
		     काष्ठा mlx5e_ipsec_metadata *mdata)
अणु
	काष्ठा mlx5e_priv *priv = netdev_priv(netdev);
	काष्ठा xfrm_offload *xo;
	काष्ठा xfrm_state *xs;
	काष्ठा sec_path *sp;
	u32 sa_handle;

	sp = secpath_set(skb);
	अगर (unlikely(!sp)) अणु
		atomic64_inc(&priv->ipsec->sw_stats.ipsec_rx_drop_sp_alloc);
		वापस शून्य;
	पूर्ण

	sa_handle = be32_to_cpu(mdata->content.rx.sa_handle);
	xs = mlx5e_ipsec_sadb_rx_lookup(priv->ipsec, sa_handle);
	अगर (unlikely(!xs)) अणु
		atomic64_inc(&priv->ipsec->sw_stats.ipsec_rx_drop_sadb_miss);
		वापस शून्य;
	पूर्ण

	sp = skb_sec_path(skb);
	sp->xvec[sp->len++] = xs;
	sp->olen++;

	xo = xfrm_offload(skb);
	xo->flags = CRYPTO_DONE;
	चयन (mdata->syndrome) अणु
	हाल MLX5E_IPSEC_RX_SYNDROME_DECRYPTED:
		xo->status = CRYPTO_SUCCESS;
		अगर (likely(priv->ipsec->no_trailer)) अणु
			xo->flags |= XFRM_ESP_NO_TRAILER;
			xo->proto = mdata->content.rx.nexthdr;
		पूर्ण
		अवरोध;
	हाल MLX5E_IPSEC_RX_SYNDROME_AUTH_FAILED:
		xo->status = CRYPTO_TUNNEL_ESP_AUTH_FAILED;
		अवरोध;
	हाल MLX5E_IPSEC_RX_SYNDROME_BAD_PROTO:
		xo->status = CRYPTO_INVALID_PROTOCOL;
		अवरोध;
	शेष:
		atomic64_inc(&priv->ipsec->sw_stats.ipsec_rx_drop_syndrome);
		वापस शून्य;
	पूर्ण
	वापस xs;
पूर्ण

काष्ठा sk_buff *mlx5e_ipsec_handle_rx_skb(काष्ठा net_device *netdev,
					  काष्ठा sk_buff *skb, u32 *cqe_bcnt)
अणु
	काष्ठा mlx5e_ipsec_metadata *mdata;
	काष्ठा xfrm_state *xs;

	अगर (!is_metadata_hdr_valid(skb))
		वापस skb;

	/* Use the metadata */
	mdata = (काष्ठा mlx5e_ipsec_metadata *)(skb->data + ETH_HLEN);
	xs = mlx5e_ipsec_build_sp(netdev, skb, mdata);
	अगर (unlikely(!xs)) अणु
		kमुक्त_skb(skb);
		वापस शून्य;
	पूर्ण

	हटाओ_metadata_hdr(skb);
	*cqe_bcnt -= MLX5E_METADATA_ETHER_LEN;

	वापस skb;
पूर्ण

क्रमागत अणु
	MLX5E_IPSEC_OFFLOAD_RX_SYNDROME_DECRYPTED,
	MLX5E_IPSEC_OFFLOAD_RX_SYNDROME_AUTH_FAILED,
	MLX5E_IPSEC_OFFLOAD_RX_SYNDROME_BAD_TRAILER,
पूर्ण;

व्योम mlx5e_ipsec_offload_handle_rx_skb(काष्ठा net_device *netdev,
				       काष्ठा sk_buff *skb,
				       काष्ठा mlx5_cqe64 *cqe)
अणु
	u32 ipsec_meta_data = be32_to_cpu(cqe->ft_metadata);
	काष्ठा mlx5e_priv *priv;
	काष्ठा xfrm_offload *xo;
	काष्ठा xfrm_state *xs;
	काष्ठा sec_path *sp;
	u32  sa_handle;

	sa_handle = MLX5_IPSEC_METADATA_HANDLE(ipsec_meta_data);
	priv = netdev_priv(netdev);
	sp = secpath_set(skb);
	अगर (unlikely(!sp)) अणु
		atomic64_inc(&priv->ipsec->sw_stats.ipsec_rx_drop_sp_alloc);
		वापस;
	पूर्ण

	xs = mlx5e_ipsec_sadb_rx_lookup(priv->ipsec, sa_handle);
	अगर (unlikely(!xs)) अणु
		atomic64_inc(&priv->ipsec->sw_stats.ipsec_rx_drop_sadb_miss);
		वापस;
	पूर्ण

	sp = skb_sec_path(skb);
	sp->xvec[sp->len++] = xs;
	sp->olen++;

	xo = xfrm_offload(skb);
	xo->flags = CRYPTO_DONE;

	चयन (MLX5_IPSEC_METADATA_SYNDROM(ipsec_meta_data)) अणु
	हाल MLX5E_IPSEC_OFFLOAD_RX_SYNDROME_DECRYPTED:
		xo->status = CRYPTO_SUCCESS;
		अगर (WARN_ON_ONCE(priv->ipsec->no_trailer))
			xo->flags |= XFRM_ESP_NO_TRAILER;
		अवरोध;
	हाल MLX5E_IPSEC_OFFLOAD_RX_SYNDROME_AUTH_FAILED:
		xo->status = CRYPTO_TUNNEL_ESP_AUTH_FAILED;
		अवरोध;
	हाल MLX5E_IPSEC_OFFLOAD_RX_SYNDROME_BAD_TRAILER:
		xo->status = CRYPTO_INVALID_PACKET_SYNTAX;
		अवरोध;
	शेष:
		atomic64_inc(&priv->ipsec->sw_stats.ipsec_rx_drop_syndrome);
	पूर्ण
पूर्ण

व्योम mlx5e_ipsec_build_inverse_table(व्योम)
अणु
	u16 mss_inv;
	u32 mss;

	/* Calculate 1/x inverse table क्रम use in GSO data path.
	 * Using this table, we provide the IPSec accelerator with the value of
	 * 1/gso_size so that it can infer the position of each segment inside
	 * the GSO, and increment the ESP sequence number, and generate the IV.
	 * The HW needs this value in Q0.16 fixed-poपूर्णांक number क्रमmat
	 */
	mlx5e_ipsec_inverse_table[1] = htons(0xFFFF);
	क्रम (mss = 2; mss < MAX_LSO_MSS; mss++) अणु
		mss_inv = भाग_u64(1ULL << 32, mss) >> 16;
		mlx5e_ipsec_inverse_table[mss] = htons(mss_inv);
	पूर्ण
पूर्ण
