<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB
// Copyright (c) 2019 Mellanox Technologies.

#समावेश <net/inet6_hashtables.h>
#समावेश "en_accel/en_accel.h"
#समावेश "en_accel/tls.h"
#समावेश "en_accel/ktls_txrx.h"
#समावेश "en_accel/ktls_utils.h"
#समावेश "en_accel/fs_tcp.h"

काष्ठा accel_rule अणु
	काष्ठा work_काष्ठा work;
	काष्ठा mlx5e_priv *priv;
	काष्ठा mlx5_flow_handle *rule;
पूर्ण;

#घोषणा PROGRESS_PARAMS_WRITE_UNIT	64
#घोषणा PROGRESS_PARAMS_PADDED_SIZE	\
		(ALIGN(माप(काष्ठा mlx5_wqe_tls_progress_params_seg), \
		       PROGRESS_PARAMS_WRITE_UNIT))

काष्ठा mlx5e_ktls_rx_resync_buf अणु
	जोड़ अणु
		काष्ठा mlx5_wqe_tls_progress_params_seg progress;
		u8 pad[PROGRESS_PARAMS_PADDED_SIZE];
	पूर्ण ____cacheline_aligned_in_smp;
	dma_addr_t dma_addr;
	काष्ठा mlx5e_ktls_offload_context_rx *priv_rx;
पूर्ण;

क्रमागत अणु
	MLX5E_PRIV_RX_FLAG_DELETING,
	MLX5E_NUM_PRIV_RX_FLAGS,
पूर्ण;

काष्ठा mlx5e_ktls_rx_resync_ctx अणु
	काष्ठा tls_offload_resync_async core;
	काष्ठा work_काष्ठा work;
	काष्ठा mlx5e_priv *priv;
	refcount_t refcnt;
	__be64 sw_rcd_sn_be;
	u32 seq;
पूर्ण;

काष्ठा mlx5e_ktls_offload_context_rx अणु
	काष्ठा tls12_crypto_info_aes_gcm_128 crypto_info;
	काष्ठा accel_rule rule;
	काष्ठा sock *sk;
	काष्ठा mlx5e_rq_stats *rq_stats;
	काष्ठा mlx5e_tls_sw_stats *sw_stats;
	काष्ठा completion add_ctx;
	u32 tirn;
	u32 key_id;
	u32 rxq;
	DECLARE_BITMAP(flags, MLX5E_NUM_PRIV_RX_FLAGS);

	/* resync */
	काष्ठा mlx5e_ktls_rx_resync_ctx resync;
	काष्ठा list_head list;
पूर्ण;

अटल bool mlx5e_ktls_priv_rx_put(काष्ठा mlx5e_ktls_offload_context_rx *priv_rx)
अणु
	अगर (!refcount_dec_and_test(&priv_rx->resync.refcnt))
		वापस false;

	kमुक्त(priv_rx);
	वापस true;
पूर्ण

अटल व्योम mlx5e_ktls_priv_rx_get(काष्ठा mlx5e_ktls_offload_context_rx *priv_rx)
अणु
	refcount_inc(&priv_rx->resync.refcnt);
पूर्ण

काष्ठा mlx5e_ktls_resync_resp अणु
	/* protects list changes */
	spinlock_t lock;
	काष्ठा list_head list;
पूर्ण;

व्योम mlx5e_ktls_rx_resync_destroy_resp_list(काष्ठा mlx5e_ktls_resync_resp *resp_list)
अणु
	kvमुक्त(resp_list);
पूर्ण

काष्ठा mlx5e_ktls_resync_resp *
mlx5e_ktls_rx_resync_create_resp_list(व्योम)
अणु
	काष्ठा mlx5e_ktls_resync_resp *resp_list;

	resp_list = kvzalloc(माप(*resp_list), GFP_KERNEL);
	अगर (!resp_list)
		वापस ERR_PTR(-ENOMEM);

	INIT_LIST_HEAD(&resp_list->list);
	spin_lock_init(&resp_list->lock);

	वापस resp_list;
पूर्ण

अटल पूर्णांक mlx5e_ktls_create_tir(काष्ठा mlx5_core_dev *mdev, u32 *tirn, u32 rqtn)
अणु
	पूर्णांक err, inlen;
	व्योम *tirc;
	u32 *in;

	inlen = MLX5_ST_SZ_BYTES(create_tir_in);
	in = kvzalloc(inlen, GFP_KERNEL);
	अगर (!in)
		वापस -ENOMEM;

	tirc = MLX5_ADDR_OF(create_tir_in, in, ctx);

	MLX5_SET(tirc, tirc, transport_करोमुख्य, mdev->mlx5e_res.hw_objs.td.tdn);
	MLX5_SET(tirc, tirc, disp_type, MLX5_TIRC_DISP_TYPE_INसूचीECT);
	MLX5_SET(tirc, tirc, rx_hash_fn, MLX5_RX_HASH_FN_INVERTED_XOR8);
	MLX5_SET(tirc, tirc, indirect_table, rqtn);
	MLX5_SET(tirc, tirc, tls_en, 1);
	MLX5_SET(tirc, tirc, self_lb_block,
		 MLX5_TIRC_SELF_LB_BLOCK_BLOCK_UNICAST |
		 MLX5_TIRC_SELF_LB_BLOCK_BLOCK_MULTICAST);

	err = mlx5_core_create_tir(mdev, in, tirn);

	kvमुक्त(in);
	वापस err;
पूर्ण

अटल व्योम accel_rule_handle_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा mlx5e_ktls_offload_context_rx *priv_rx;
	काष्ठा accel_rule *accel_rule;
	काष्ठा mlx5_flow_handle *rule;

	accel_rule = container_of(work, काष्ठा accel_rule, work);
	priv_rx = container_of(accel_rule, काष्ठा mlx5e_ktls_offload_context_rx, rule);
	अगर (unlikely(test_bit(MLX5E_PRIV_RX_FLAG_DELETING, priv_rx->flags)))
		जाओ out;

	rule = mlx5e_accel_fs_add_sk(accel_rule->priv, priv_rx->sk,
				     priv_rx->tirn, MLX5_FS_DEFAULT_FLOW_TAG);
	अगर (!IS_ERR_OR_शून्य(rule))
		accel_rule->rule = rule;
out:
	complete(&priv_rx->add_ctx);
पूर्ण

अटल व्योम accel_rule_init(काष्ठा accel_rule *rule, काष्ठा mlx5e_priv *priv)
अणु
	INIT_WORK(&rule->work, accel_rule_handle_work);
	rule->priv = priv;
पूर्ण

अटल व्योम icosq_fill_wi(काष्ठा mlx5e_icosq *sq, u16 pi,
			  काष्ठा mlx5e_icosq_wqe_info *wi)
अणु
	sq->db.wqe_info[pi] = *wi;
पूर्ण

अटल काष्ठा mlx5_wqe_ctrl_seg *
post_अटल_params(काष्ठा mlx5e_icosq *sq,
		   काष्ठा mlx5e_ktls_offload_context_rx *priv_rx)
अणु
	काष्ठा mlx5e_set_tls_अटल_params_wqe *wqe;
	काष्ठा mlx5e_icosq_wqe_info wi;
	u16 pi, num_wqebbs;

	num_wqebbs = MLX5E_TLS_SET_STATIC_PARAMS_WQEBBS;
	अगर (unlikely(!mlx5e_icosq_can_post_wqe(sq, num_wqebbs)))
		वापस ERR_PTR(-ENOSPC);

	pi = mlx5e_icosq_get_next_pi(sq, num_wqebbs);
	wqe = MLX5E_TLS_FETCH_SET_STATIC_PARAMS_WQE(sq, pi);
	mlx5e_ktls_build_अटल_params(wqe, sq->pc, sq->sqn, &priv_rx->crypto_info,
				       priv_rx->tirn, priv_rx->key_id,
				       priv_rx->resync.seq, false,
				       TLS_OFFLOAD_CTX_सूची_RX);
	wi = (काष्ठा mlx5e_icosq_wqe_info) अणु
		.wqe_type = MLX5E_ICOSQ_WQE_UMR_TLS,
		.num_wqebbs = num_wqebbs,
		.tls_set_params.priv_rx = priv_rx,
	पूर्ण;
	icosq_fill_wi(sq, pi, &wi);
	sq->pc += num_wqebbs;

	वापस &wqe->ctrl;
पूर्ण

अटल काष्ठा mlx5_wqe_ctrl_seg *
post_progress_params(काष्ठा mlx5e_icosq *sq,
		     काष्ठा mlx5e_ktls_offload_context_rx *priv_rx,
		     u32 next_record_tcp_sn)
अणु
	काष्ठा mlx5e_set_tls_progress_params_wqe *wqe;
	काष्ठा mlx5e_icosq_wqe_info wi;
	u16 pi, num_wqebbs;

	num_wqebbs = MLX5E_TLS_SET_PROGRESS_PARAMS_WQEBBS;
	अगर (unlikely(!mlx5e_icosq_can_post_wqe(sq, num_wqebbs)))
		वापस ERR_PTR(-ENOSPC);

	pi = mlx5e_icosq_get_next_pi(sq, num_wqebbs);
	wqe = MLX5E_TLS_FETCH_SET_PROGRESS_PARAMS_WQE(sq, pi);
	mlx5e_ktls_build_progress_params(wqe, sq->pc, sq->sqn, priv_rx->tirn, false,
					 next_record_tcp_sn,
					 TLS_OFFLOAD_CTX_सूची_RX);
	wi = (काष्ठा mlx5e_icosq_wqe_info) अणु
		.wqe_type = MLX5E_ICOSQ_WQE_SET_PSV_TLS,
		.num_wqebbs = num_wqebbs,
		.tls_set_params.priv_rx = priv_rx,
	पूर्ण;

	icosq_fill_wi(sq, pi, &wi);
	sq->pc += num_wqebbs;

	वापस &wqe->ctrl;
पूर्ण

अटल पूर्णांक post_rx_param_wqes(काष्ठा mlx5e_channel *c,
			      काष्ठा mlx5e_ktls_offload_context_rx *priv_rx,
			      u32 next_record_tcp_sn)
अणु
	काष्ठा mlx5_wqe_ctrl_seg *cseg;
	काष्ठा mlx5e_icosq *sq;
	पूर्णांक err;

	err = 0;
	sq = &c->async_icosq;
	spin_lock_bh(&c->async_icosq_lock);

	cseg = post_अटल_params(sq, priv_rx);
	अगर (IS_ERR(cseg))
		जाओ err_out;
	cseg = post_progress_params(sq, priv_rx, next_record_tcp_sn);
	अगर (IS_ERR(cseg))
		जाओ err_out;

	mlx5e_notअगरy_hw(&sq->wq, sq->pc, sq->uar_map, cseg);
unlock:
	spin_unlock_bh(&c->async_icosq_lock);

	वापस err;

err_out:
	priv_rx->rq_stats->tls_resync_req_skip++;
	err = PTR_ERR(cseg);
	complete(&priv_rx->add_ctx);
	जाओ unlock;
पूर्ण

अटल व्योम
mlx5e_set_ktls_rx_priv_ctx(काष्ठा tls_context *tls_ctx,
			   काष्ठा mlx5e_ktls_offload_context_rx *priv_rx)
अणु
	काष्ठा mlx5e_ktls_offload_context_rx **ctx =
		__tls_driver_ctx(tls_ctx, TLS_OFFLOAD_CTX_सूची_RX);

	BUILD_BUG_ON(माप(काष्ठा mlx5e_ktls_offload_context_rx *) >
		     TLS_OFFLOAD_CONTEXT_SIZE_RX);

	*ctx = priv_rx;
पूर्ण

अटल काष्ठा mlx5e_ktls_offload_context_rx *
mlx5e_get_ktls_rx_priv_ctx(काष्ठा tls_context *tls_ctx)
अणु
	काष्ठा mlx5e_ktls_offload_context_rx **ctx =
		__tls_driver_ctx(tls_ctx, TLS_OFFLOAD_CTX_सूची_RX);

	वापस *ctx;
पूर्ण

/* Re-sync */
/* Runs in work context */
अटल पूर्णांक
resync_post_get_progress_params(काष्ठा mlx5e_icosq *sq,
				काष्ठा mlx5e_ktls_offload_context_rx *priv_rx)
अणु
	काष्ठा mlx5e_get_tls_progress_params_wqe *wqe;
	काष्ठा mlx5e_ktls_rx_resync_buf *buf;
	काष्ठा mlx5e_icosq_wqe_info wi;
	काष्ठा mlx5_wqe_ctrl_seg *cseg;
	काष्ठा mlx5_seg_get_psv *psv;
	काष्ठा device *pdev;
	पूर्णांक err;
	u16 pi;

	buf = kzalloc(माप(*buf), GFP_KERNEL);
	अगर (unlikely(!buf)) अणु
		err = -ENOMEM;
		जाओ err_out;
	पूर्ण

	pdev = mlx5_core_dma_dev(sq->channel->priv->mdev);
	buf->dma_addr = dma_map_single(pdev, &buf->progress,
				       PROGRESS_PARAMS_PADDED_SIZE, DMA_FROM_DEVICE);
	अगर (unlikely(dma_mapping_error(pdev, buf->dma_addr))) अणु
		err = -ENOMEM;
		जाओ err_मुक्त;
	पूर्ण

	buf->priv_rx = priv_rx;

	spin_lock_bh(&sq->channel->async_icosq_lock);

	अगर (unlikely(!mlx5e_icosq_can_post_wqe(sq, MLX5E_KTLS_GET_PROGRESS_WQEBBS))) अणु
		spin_unlock_bh(&sq->channel->async_icosq_lock);
		err = -ENOSPC;
		जाओ err_dma_unmap;
	पूर्ण

	pi = mlx5e_icosq_get_next_pi(sq, MLX5E_KTLS_GET_PROGRESS_WQEBBS);
	wqe = MLX5E_TLS_FETCH_GET_PROGRESS_PARAMS_WQE(sq, pi);

#घोषणा GET_PSV_DS_CNT (DIV_ROUND_UP(माप(*wqe), MLX5_SEND_WQE_DS))

	cseg = &wqe->ctrl;
	cseg->opmod_idx_opcode =
		cpu_to_be32((sq->pc << 8) | MLX5_OPCODE_GET_PSV |
			    (MLX5_OPC_MOD_TLS_TIR_PROGRESS_PARAMS << 24));
	cseg->qpn_ds =
		cpu_to_be32((sq->sqn << MLX5_WQE_CTRL_QPN_SHIFT) | GET_PSV_DS_CNT);

	psv = &wqe->psv;
	psv->num_psv      = 1 << 4;
	psv->l_key        = sq->channel->mkey_be;
	psv->psv_index[0] = cpu_to_be32(priv_rx->tirn);
	psv->va           = cpu_to_be64(buf->dma_addr);

	wi = (काष्ठा mlx5e_icosq_wqe_info) अणु
		.wqe_type = MLX5E_ICOSQ_WQE_GET_PSV_TLS,
		.num_wqebbs = MLX5E_KTLS_GET_PROGRESS_WQEBBS,
		.tls_get_params.buf = buf,
	पूर्ण;
	icosq_fill_wi(sq, pi, &wi);
	sq->pc++;
	mlx5e_notअगरy_hw(&sq->wq, sq->pc, sq->uar_map, cseg);
	spin_unlock_bh(&sq->channel->async_icosq_lock);

	वापस 0;

err_dma_unmap:
	dma_unmap_single(pdev, buf->dma_addr, PROGRESS_PARAMS_PADDED_SIZE, DMA_FROM_DEVICE);
err_मुक्त:
	kमुक्त(buf);
err_out:
	priv_rx->rq_stats->tls_resync_req_skip++;
	वापस err;
पूर्ण

/* Function is called with elevated refcount.
 * It decreases it only अगर no WQE is posted.
 */
अटल व्योम resync_handle_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा mlx5e_ktls_offload_context_rx *priv_rx;
	काष्ठा mlx5e_ktls_rx_resync_ctx *resync;
	काष्ठा mlx5e_channel *c;
	काष्ठा mlx5e_icosq *sq;

	resync = container_of(work, काष्ठा mlx5e_ktls_rx_resync_ctx, work);
	priv_rx = container_of(resync, काष्ठा mlx5e_ktls_offload_context_rx, resync);

	अगर (unlikely(test_bit(MLX5E_PRIV_RX_FLAG_DELETING, priv_rx->flags))) अणु
		mlx5e_ktls_priv_rx_put(priv_rx);
		वापस;
	पूर्ण

	c = resync->priv->channels.c[priv_rx->rxq];
	sq = &c->async_icosq;

	अगर (resync_post_get_progress_params(sq, priv_rx))
		mlx5e_ktls_priv_rx_put(priv_rx);
पूर्ण

अटल व्योम resync_init(काष्ठा mlx5e_ktls_rx_resync_ctx *resync,
			काष्ठा mlx5e_priv *priv)
अणु
	INIT_WORK(&resync->work, resync_handle_work);
	resync->priv = priv;
	refcount_set(&resync->refcnt, 1);
पूर्ण

/* Function can be called with the refcount being either elevated or not.
 * It करोes not affect the refcount.
 */
अटल व्योम resync_handle_seq_match(काष्ठा mlx5e_ktls_offload_context_rx *priv_rx,
				    काष्ठा mlx5e_channel *c)
अणु
	काष्ठा tls12_crypto_info_aes_gcm_128 *info = &priv_rx->crypto_info;
	काष्ठा mlx5e_ktls_resync_resp *ktls_resync;
	काष्ठा mlx5e_icosq *sq;
	bool trigger_poll;

	स_नकल(info->rec_seq, &priv_rx->resync.sw_rcd_sn_be, माप(info->rec_seq));

	sq = &c->async_icosq;
	ktls_resync = sq->ktls_resync;

	spin_lock_bh(&ktls_resync->lock);
	list_add_tail(&priv_rx->list, &ktls_resync->list);
	trigger_poll = !test_and_set_bit(MLX5E_SQ_STATE_PENDING_TLS_RX_RESYNC, &sq->state);
	spin_unlock_bh(&ktls_resync->lock);

	अगर (!trigger_poll)
		वापस;

	अगर (!napi_अगर_scheduled_mark_missed(&c->napi)) अणु
		spin_lock_bh(&c->async_icosq_lock);
		mlx5e_trigger_irq(sq);
		spin_unlock_bh(&c->async_icosq_lock);
	पूर्ण
पूर्ण

/* Function can be called with the refcount being either elevated or not.
 * It decreases the refcount and may मुक्त the kTLS priv context.
 * Refcount is not elevated only अगर tls_dev_del has been called, but GET_PSV was
 * alपढ़ोy in flight.
 */
व्योम mlx5e_ktls_handle_get_psv_completion(काष्ठा mlx5e_icosq_wqe_info *wi,
					  काष्ठा mlx5e_icosq *sq)
अणु
	काष्ठा mlx5e_ktls_rx_resync_buf *buf = wi->tls_get_params.buf;
	काष्ठा mlx5e_ktls_offload_context_rx *priv_rx;
	काष्ठा mlx5e_ktls_rx_resync_ctx *resync;
	u8 tracker_state, auth_state, *ctx;
	काष्ठा device *dev;
	u32 hw_seq;

	priv_rx = buf->priv_rx;
	resync = &priv_rx->resync;
	dev = mlx5_core_dma_dev(resync->priv->mdev);
	अगर (unlikely(test_bit(MLX5E_PRIV_RX_FLAG_DELETING, priv_rx->flags)))
		जाओ out;

	dma_sync_single_क्रम_cpu(dev, buf->dma_addr, PROGRESS_PARAMS_PADDED_SIZE,
				DMA_FROM_DEVICE);

	ctx = buf->progress.ctx;
	tracker_state = MLX5_GET(tls_progress_params, ctx, record_tracker_state);
	auth_state = MLX5_GET(tls_progress_params, ctx, auth_state);
	अगर (tracker_state != MLX5E_TLS_PROGRESS_PARAMS_RECORD_TRACKER_STATE_TRACKING ||
	    auth_state != MLX5E_TLS_PROGRESS_PARAMS_AUTH_STATE_NO_OFFLOAD) अणु
		priv_rx->rq_stats->tls_resync_req_skip++;
		जाओ out;
	पूर्ण

	hw_seq = MLX5_GET(tls_progress_params, ctx, hw_resync_tcp_sn);
	tls_offload_rx_resync_async_request_end(priv_rx->sk, cpu_to_be32(hw_seq));
	priv_rx->rq_stats->tls_resync_req_end++;
out:
	mlx5e_ktls_priv_rx_put(priv_rx);
	dma_unmap_single(dev, buf->dma_addr, PROGRESS_PARAMS_PADDED_SIZE, DMA_FROM_DEVICE);
	kमुक्त(buf);
पूर्ण

/* Runs in NAPI.
 * Function elevates the refcount, unless no work is queued.
 */
अटल bool resync_queue_get_psv(काष्ठा sock *sk)
अणु
	काष्ठा mlx5e_ktls_offload_context_rx *priv_rx;
	काष्ठा mlx5e_ktls_rx_resync_ctx *resync;

	priv_rx = mlx5e_get_ktls_rx_priv_ctx(tls_get_ctx(sk));
	अगर (unlikely(!priv_rx))
		वापस false;

	अगर (unlikely(test_bit(MLX5E_PRIV_RX_FLAG_DELETING, priv_rx->flags)))
		वापस false;

	resync = &priv_rx->resync;
	mlx5e_ktls_priv_rx_get(priv_rx);
	अगर (unlikely(!queue_work(resync->priv->tls->rx_wq, &resync->work)))
		mlx5e_ktls_priv_rx_put(priv_rx);

	वापस true;
पूर्ण

/* Runs in NAPI */
अटल व्योम resync_update_sn(काष्ठा mlx5e_rq *rq, काष्ठा sk_buff *skb)
अणु
	काष्ठा ethhdr *eth = (काष्ठा ethhdr *)(skb->data);
	काष्ठा net_device *netdev = rq->netdev;
	काष्ठा sock *sk = शून्य;
	अचिन्हित पूर्णांक datalen;
	काष्ठा iphdr *iph;
	काष्ठा tcphdr *th;
	__be32 seq;
	पूर्णांक depth = 0;

	__vlan_get_protocol(skb, eth->h_proto, &depth);
	iph = (काष्ठा iphdr *)(skb->data + depth);

	अगर (iph->version == 4) अणु
		depth += माप(काष्ठा iphdr);
		th = (व्योम *)iph + माप(काष्ठा iphdr);

		sk = inet_lookup_established(dev_net(netdev), &tcp_hashinfo,
					     iph->saddr, th->source, iph->daddr,
					     th->dest, netdev->अगरindex);
#अगर IS_ENABLED(CONFIG_IPV6)
	पूर्ण अन्यथा अणु
		काष्ठा ipv6hdr *ipv6h = (काष्ठा ipv6hdr *)iph;

		depth += माप(काष्ठा ipv6hdr);
		th = (व्योम *)ipv6h + माप(काष्ठा ipv6hdr);

		sk = __inet6_lookup_established(dev_net(netdev), &tcp_hashinfo,
						&ipv6h->saddr, th->source,
						&ipv6h->daddr, ntohs(th->dest),
						netdev->अगरindex, 0);
#पूर्ण_अगर
	पूर्ण

	depth += माप(काष्ठा tcphdr);

	अगर (unlikely(!sk))
		वापस;

	अगर (unlikely(sk->sk_state == TCP_TIME_WAIT))
		जाओ unref;

	अगर (unlikely(!resync_queue_get_psv(sk)))
		जाओ unref;

	seq = th->seq;
	datalen = skb->len - depth;
	tls_offload_rx_resync_async_request_start(sk, seq, datalen);
	rq->stats->tls_resync_req_start++;

unref:
	sock_gen_put(sk);
पूर्ण

व्योम mlx5e_ktls_rx_resync(काष्ठा net_device *netdev, काष्ठा sock *sk,
			  u32 seq, u8 *rcd_sn)
अणु
	काष्ठा mlx5e_ktls_offload_context_rx *priv_rx;
	काष्ठा mlx5e_ktls_rx_resync_ctx *resync;
	काष्ठा mlx5e_priv *priv;
	काष्ठा mlx5e_channel *c;

	priv_rx = mlx5e_get_ktls_rx_priv_ctx(tls_get_ctx(sk));
	अगर (unlikely(!priv_rx))
		वापस;

	resync = &priv_rx->resync;
	resync->sw_rcd_sn_be = *(__be64 *)rcd_sn;
	resync->seq = seq;

	priv = netdev_priv(netdev);
	c = priv->channels.c[priv_rx->rxq];

	resync_handle_seq_match(priv_rx, c);
पूर्ण

/* End of resync section */

व्योम mlx5e_ktls_handle_rx_skb(काष्ठा mlx5e_rq *rq, काष्ठा sk_buff *skb,
			      काष्ठा mlx5_cqe64 *cqe, u32 *cqe_bcnt)
अणु
	काष्ठा mlx5e_rq_stats *stats = rq->stats;

	चयन (get_cqe_tls_offload(cqe)) अणु
	हाल CQE_TLS_OFFLOAD_DECRYPTED:
		skb->decrypted = 1;
		stats->tls_decrypted_packets++;
		stats->tls_decrypted_bytes += *cqe_bcnt;
		अवरोध;
	हाल CQE_TLS_OFFLOAD_RESYNC:
		stats->tls_resync_req_pkt++;
		resync_update_sn(rq, skb);
		अवरोध;
	शेष: /* CQE_TLS_OFFLOAD_ERROR: */
		stats->tls_err++;
		अवरोध;
	पूर्ण
पूर्ण

व्योम mlx5e_ktls_handle_ctx_completion(काष्ठा mlx5e_icosq_wqe_info *wi)
अणु
	काष्ठा mlx5e_ktls_offload_context_rx *priv_rx = wi->tls_set_params.priv_rx;
	काष्ठा accel_rule *rule = &priv_rx->rule;

	अगर (unlikely(test_bit(MLX5E_PRIV_RX_FLAG_DELETING, priv_rx->flags))) अणु
		complete(&priv_rx->add_ctx);
		वापस;
	पूर्ण
	queue_work(rule->priv->tls->rx_wq, &rule->work);
पूर्ण

अटल पूर्णांक mlx5e_ktls_sk_get_rxq(काष्ठा sock *sk)
अणु
	पूर्णांक rxq = sk_rx_queue_get(sk);

	अगर (unlikely(rxq == -1))
		rxq = 0;

	वापस rxq;
पूर्ण

पूर्णांक mlx5e_ktls_add_rx(काष्ठा net_device *netdev, काष्ठा sock *sk,
		      काष्ठा tls_crypto_info *crypto_info,
		      u32 start_offload_tcp_sn)
अणु
	काष्ठा mlx5e_ktls_offload_context_rx *priv_rx;
	काष्ठा mlx5e_ktls_rx_resync_ctx *resync;
	काष्ठा tls_context *tls_ctx;
	काष्ठा mlx5_core_dev *mdev;
	काष्ठा mlx5e_priv *priv;
	पूर्णांक rxq, err;
	u32 rqtn;

	tls_ctx = tls_get_ctx(sk);
	priv = netdev_priv(netdev);
	mdev = priv->mdev;
	priv_rx = kzalloc(माप(*priv_rx), GFP_KERNEL);
	अगर (unlikely(!priv_rx))
		वापस -ENOMEM;

	err = mlx5_ktls_create_key(mdev, crypto_info, &priv_rx->key_id);
	अगर (err)
		जाओ err_create_key;

	priv_rx->crypto_info  =
		*(काष्ठा tls12_crypto_info_aes_gcm_128 *)crypto_info;

	rxq = mlx5e_ktls_sk_get_rxq(sk);
	priv_rx->rxq = rxq;
	priv_rx->sk = sk;

	priv_rx->rq_stats = &priv->channel_stats[rxq].rq;
	priv_rx->sw_stats = &priv->tls->sw_stats;
	mlx5e_set_ktls_rx_priv_ctx(tls_ctx, priv_rx);

	rqtn = priv->direct_tir[rxq].rqt.rqtn;

	err = mlx5e_ktls_create_tir(mdev, &priv_rx->tirn, rqtn);
	अगर (err)
		जाओ err_create_tir;

	init_completion(&priv_rx->add_ctx);

	accel_rule_init(&priv_rx->rule, priv);
	resync = &priv_rx->resync;
	resync_init(resync, priv);
	tls_offload_ctx_rx(tls_ctx)->resync_async = &resync->core;
	tls_offload_rx_resync_set_type(sk, TLS_OFFLOAD_SYNC_TYPE_DRIVER_REQ_ASYNC);

	err = post_rx_param_wqes(priv->channels.c[rxq], priv_rx, start_offload_tcp_sn);
	अगर (err)
		जाओ err_post_wqes;

	atomic64_inc(&priv_rx->sw_stats->rx_tls_ctx);

	वापस 0;

err_post_wqes:
	mlx5_core_destroy_tir(mdev, priv_rx->tirn);
err_create_tir:
	mlx5_ktls_destroy_key(mdev, priv_rx->key_id);
err_create_key:
	kमुक्त(priv_rx);
	वापस err;
पूर्ण

व्योम mlx5e_ktls_del_rx(काष्ठा net_device *netdev, काष्ठा tls_context *tls_ctx)
अणु
	काष्ठा mlx5e_ktls_offload_context_rx *priv_rx;
	काष्ठा mlx5e_ktls_rx_resync_ctx *resync;
	काष्ठा mlx5_core_dev *mdev;
	काष्ठा mlx5e_priv *priv;

	priv = netdev_priv(netdev);
	mdev = priv->mdev;

	priv_rx = mlx5e_get_ktls_rx_priv_ctx(tls_ctx);
	set_bit(MLX5E_PRIV_RX_FLAG_DELETING, priv_rx->flags);
	mlx5e_set_ktls_rx_priv_ctx(tls_ctx, शून्य);
	synchronize_net(); /* Sync with NAPI */
	अगर (!cancel_work_sync(&priv_rx->rule.work))
		/* completion is needed, as the priv_rx in the add flow
		 * is मुख्यtained on the wqe info (wi), not on the socket.
		 */
		रुको_क्रम_completion(&priv_rx->add_ctx);
	resync = &priv_rx->resync;
	अगर (cancel_work_sync(&resync->work))
		mlx5e_ktls_priv_rx_put(priv_rx);

	atomic64_inc(&priv_rx->sw_stats->rx_tls_del);
	अगर (priv_rx->rule.rule)
		mlx5e_accel_fs_del_sk(priv_rx->rule.rule);

	mlx5_core_destroy_tir(mdev, priv_rx->tirn);
	mlx5_ktls_destroy_key(mdev, priv_rx->key_id);
	/* priv_rx should normally be मुक्तd here, but अगर there is an outstanding
	 * GET_PSV, deallocation will be delayed until the CQE क्रम GET_PSV is
	 * processed.
	 */
	mlx5e_ktls_priv_rx_put(priv_rx);
पूर्ण

bool mlx5e_ktls_rx_handle_resync_list(काष्ठा mlx5e_channel *c, पूर्णांक budget)
अणु
	काष्ठा mlx5e_ktls_offload_context_rx *priv_rx, *पंचांगp;
	काष्ठा mlx5e_ktls_resync_resp *ktls_resync;
	काष्ठा mlx5_wqe_ctrl_seg *db_cseg;
	काष्ठा mlx5e_icosq *sq;
	LIST_HEAD(local_list);
	पूर्णांक i, j;

	sq = &c->async_icosq;

	अगर (unlikely(!test_bit(MLX5E_SQ_STATE_ENABLED, &sq->state)))
		वापस false;

	ktls_resync = sq->ktls_resync;
	db_cseg = शून्य;
	i = 0;

	spin_lock(&ktls_resync->lock);
	list_क्रम_each_entry_safe(priv_rx, पंचांगp, &ktls_resync->list, list) अणु
		list_move(&priv_rx->list, &local_list);
		अगर (++i == budget)
			अवरोध;
	पूर्ण
	अगर (list_empty(&ktls_resync->list))
		clear_bit(MLX5E_SQ_STATE_PENDING_TLS_RX_RESYNC, &sq->state);
	spin_unlock(&ktls_resync->lock);

	spin_lock(&c->async_icosq_lock);
	क्रम (j = 0; j < i; j++) अणु
		काष्ठा mlx5_wqe_ctrl_seg *cseg;

		priv_rx = list_first_entry(&local_list,
					   काष्ठा mlx5e_ktls_offload_context_rx,
					   list);
		cseg = post_अटल_params(sq, priv_rx);
		अगर (IS_ERR(cseg))
			अवरोध;
		list_del(&priv_rx->list);
		db_cseg = cseg;
	पूर्ण
	अगर (db_cseg)
		mlx5e_notअगरy_hw(&sq->wq, sq->pc, sq->uar_map, db_cseg);
	spin_unlock(&c->async_icosq_lock);

	priv_rx->rq_stats->tls_resync_res_ok += j;

	अगर (!list_empty(&local_list)) अणु
		/* This happens only अगर ICOSQ is full.
		 * There is no need to mark busy or explicitly ask क्रम a NAPI cycle,
		 * it will be triggered by the outstanding ICOSQ completions.
		 */
		spin_lock(&ktls_resync->lock);
		list_splice(&local_list, &ktls_resync->list);
		set_bit(MLX5E_SQ_STATE_PENDING_TLS_RX_RESYNC, &sq->state);
		spin_unlock(&ktls_resync->lock);
		priv_rx->rq_stats->tls_resync_res_retry++;
	पूर्ण

	वापस i == budget;
पूर्ण
