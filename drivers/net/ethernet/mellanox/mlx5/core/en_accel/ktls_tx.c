<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB
// Copyright (c) 2019 Mellanox Technologies.

#समावेश "en_accel/tls.h"
#समावेश "en_accel/ktls_txrx.h"
#समावेश "en_accel/ktls_utils.h"

काष्ठा mlx5e_dump_wqe अणु
	काष्ठा mlx5_wqe_ctrl_seg ctrl;
	काष्ठा mlx5_wqe_data_seg data;
पूर्ण;

#घोषणा MLX5E_KTLS_DUMP_WQEBBS \
	(DIV_ROUND_UP(माप(काष्ठा mlx5e_dump_wqe), MLX5_SEND_WQE_BB))

अटल u8
mlx5e_ktls_dumps_num_wqes(काष्ठा mlx5e_params *params, अचिन्हित पूर्णांक nfrags,
			  अचिन्हित पूर्णांक sync_len)
अणु
	/* Given the MTU and sync_len, calculates an upper bound क्रम the
	 * number of DUMP WQEs needed क्रम the TX resync of a record.
	 */
	वापस nfrags + DIV_ROUND_UP(sync_len, MLX5E_SW2HW_MTU(params, params->sw_mtu));
पूर्ण

u16 mlx5e_ktls_get_stop_room(काष्ठा mlx5e_params *params)
अणु
	u16 num_dumps, stop_room = 0;

	num_dumps = mlx5e_ktls_dumps_num_wqes(params, MAX_SKB_FRAGS, TLS_MAX_PAYLOAD_SIZE);

	stop_room += mlx5e_stop_room_क्रम_wqe(MLX5E_TLS_SET_STATIC_PARAMS_WQEBBS);
	stop_room += mlx5e_stop_room_क्रम_wqe(MLX5E_TLS_SET_PROGRESS_PARAMS_WQEBBS);
	stop_room += num_dumps * mlx5e_stop_room_क्रम_wqe(MLX5E_KTLS_DUMP_WQEBBS);

	वापस stop_room;
पूर्ण

अटल पूर्णांक mlx5e_ktls_create_tis(काष्ठा mlx5_core_dev *mdev, u32 *tisn)
अणु
	u32 in[MLX5_ST_SZ_DW(create_tis_in)] = अणुपूर्ण;
	व्योम *tisc;

	tisc = MLX5_ADDR_OF(create_tis_in, in, ctx);

	MLX5_SET(tisc, tisc, tls_en, 1);

	वापस mlx5e_create_tis(mdev, in, tisn);
पूर्ण

काष्ठा mlx5e_ktls_offload_context_tx अणु
	काष्ठा tls_offload_context_tx *tx_ctx;
	काष्ठा tls12_crypto_info_aes_gcm_128 crypto_info;
	काष्ठा mlx5e_tls_sw_stats *sw_stats;
	u32 expected_seq;
	u32 tisn;
	u32 key_id;
	bool ctx_post_pending;
पूर्ण;

अटल व्योम
mlx5e_set_ktls_tx_priv_ctx(काष्ठा tls_context *tls_ctx,
			   काष्ठा mlx5e_ktls_offload_context_tx *priv_tx)
अणु
	काष्ठा mlx5e_ktls_offload_context_tx **ctx =
		__tls_driver_ctx(tls_ctx, TLS_OFFLOAD_CTX_सूची_TX);

	BUILD_BUG_ON(माप(काष्ठा mlx5e_ktls_offload_context_tx *) >
		     TLS_OFFLOAD_CONTEXT_SIZE_TX);

	*ctx = priv_tx;
पूर्ण

अटल काष्ठा mlx5e_ktls_offload_context_tx *
mlx5e_get_ktls_tx_priv_ctx(काष्ठा tls_context *tls_ctx)
अणु
	काष्ठा mlx5e_ktls_offload_context_tx **ctx =
		__tls_driver_ctx(tls_ctx, TLS_OFFLOAD_CTX_सूची_TX);

	वापस *ctx;
पूर्ण

पूर्णांक mlx5e_ktls_add_tx(काष्ठा net_device *netdev, काष्ठा sock *sk,
		      काष्ठा tls_crypto_info *crypto_info, u32 start_offload_tcp_sn)
अणु
	काष्ठा mlx5e_ktls_offload_context_tx *priv_tx;
	काष्ठा tls_context *tls_ctx;
	काष्ठा mlx5_core_dev *mdev;
	काष्ठा mlx5e_priv *priv;
	पूर्णांक err;

	tls_ctx = tls_get_ctx(sk);
	priv = netdev_priv(netdev);
	mdev = priv->mdev;

	priv_tx = kzalloc(माप(*priv_tx), GFP_KERNEL);
	अगर (!priv_tx)
		वापस -ENOMEM;

	err = mlx5_ktls_create_key(mdev, crypto_info, &priv_tx->key_id);
	अगर (err)
		जाओ err_create_key;

	priv_tx->sw_stats = &priv->tls->sw_stats;
	priv_tx->expected_seq = start_offload_tcp_sn;
	priv_tx->crypto_info  =
		*(काष्ठा tls12_crypto_info_aes_gcm_128 *)crypto_info;
	priv_tx->tx_ctx = tls_offload_ctx_tx(tls_ctx);

	mlx5e_set_ktls_tx_priv_ctx(tls_ctx, priv_tx);

	err = mlx5e_ktls_create_tis(mdev, &priv_tx->tisn);
	अगर (err)
		जाओ err_create_tis;

	priv_tx->ctx_post_pending = true;
	atomic64_inc(&priv_tx->sw_stats->tx_tls_ctx);

	वापस 0;

err_create_tis:
	mlx5_ktls_destroy_key(mdev, priv_tx->key_id);
err_create_key:
	kमुक्त(priv_tx);
	वापस err;
पूर्ण

व्योम mlx5e_ktls_del_tx(काष्ठा net_device *netdev, काष्ठा tls_context *tls_ctx)
अणु
	काष्ठा mlx5e_ktls_offload_context_tx *priv_tx;
	काष्ठा mlx5_core_dev *mdev;
	काष्ठा mlx5e_priv *priv;

	priv_tx = mlx5e_get_ktls_tx_priv_ctx(tls_ctx);
	priv = netdev_priv(netdev);
	mdev = priv->mdev;

	mlx5e_destroy_tis(mdev, priv_tx->tisn);
	mlx5_ktls_destroy_key(mdev, priv_tx->key_id);
	kमुक्त(priv_tx);
पूर्ण

अटल व्योम tx_fill_wi(काष्ठा mlx5e_txqsq *sq,
		       u16 pi, u8 num_wqebbs, u32 num_bytes,
		       काष्ठा page *page)
अणु
	काष्ठा mlx5e_tx_wqe_info *wi = &sq->db.wqe_info[pi];

	*wi = (काष्ठा mlx5e_tx_wqe_info) अणु
		.num_wqebbs = num_wqebbs,
		.num_bytes  = num_bytes,
		.resync_dump_frag_page = page,
	पूर्ण;
पूर्ण

अटल bool
mlx5e_ktls_tx_offload_test_and_clear_pending(काष्ठा mlx5e_ktls_offload_context_tx *priv_tx)
अणु
	bool ret = priv_tx->ctx_post_pending;

	priv_tx->ctx_post_pending = false;

	वापस ret;
पूर्ण

अटल व्योम
post_अटल_params(काष्ठा mlx5e_txqsq *sq,
		   काष्ठा mlx5e_ktls_offload_context_tx *priv_tx,
		   bool fence)
अणु
	काष्ठा mlx5e_set_tls_अटल_params_wqe *wqe;
	u16 pi, num_wqebbs;

	num_wqebbs = MLX5E_TLS_SET_STATIC_PARAMS_WQEBBS;
	pi = mlx5e_txqsq_get_next_pi(sq, num_wqebbs);
	wqe = MLX5E_TLS_FETCH_SET_STATIC_PARAMS_WQE(sq, pi);
	mlx5e_ktls_build_अटल_params(wqe, sq->pc, sq->sqn, &priv_tx->crypto_info,
				       priv_tx->tisn, priv_tx->key_id, 0, fence,
				       TLS_OFFLOAD_CTX_सूची_TX);
	tx_fill_wi(sq, pi, num_wqebbs, 0, शून्य);
	sq->pc += num_wqebbs;
पूर्ण

अटल व्योम
post_progress_params(काष्ठा mlx5e_txqsq *sq,
		     काष्ठा mlx5e_ktls_offload_context_tx *priv_tx,
		     bool fence)
अणु
	काष्ठा mlx5e_set_tls_progress_params_wqe *wqe;
	u16 pi, num_wqebbs;

	num_wqebbs = MLX5E_TLS_SET_PROGRESS_PARAMS_WQEBBS;
	pi = mlx5e_txqsq_get_next_pi(sq, num_wqebbs);
	wqe = MLX5E_TLS_FETCH_SET_PROGRESS_PARAMS_WQE(sq, pi);
	mlx5e_ktls_build_progress_params(wqe, sq->pc, sq->sqn, priv_tx->tisn, fence, 0,
					 TLS_OFFLOAD_CTX_सूची_TX);
	tx_fill_wi(sq, pi, num_wqebbs, 0, शून्य);
	sq->pc += num_wqebbs;
पूर्ण

अटल व्योम
mlx5e_ktls_tx_post_param_wqes(काष्ठा mlx5e_txqsq *sq,
			      काष्ठा mlx5e_ktls_offload_context_tx *priv_tx,
			      bool skip_अटल_post, bool fence_first_post)
अणु
	bool progress_fence = skip_अटल_post || !fence_first_post;

	अगर (!skip_अटल_post)
		post_अटल_params(sq, priv_tx, fence_first_post);

	post_progress_params(sq, priv_tx, progress_fence);
पूर्ण

काष्ठा tx_sync_info अणु
	u64 rcd_sn;
	u32 sync_len;
	पूर्णांक nr_frags;
	skb_frag_t frags[MAX_SKB_FRAGS];
पूर्ण;

क्रमागत mlx5e_ktls_sync_retval अणु
	MLX5E_KTLS_SYNC_DONE,
	MLX5E_KTLS_SYNC_FAIL,
	MLX5E_KTLS_SYNC_SKIP_NO_DATA,
पूर्ण;

अटल क्रमागत mlx5e_ktls_sync_retval
tx_sync_info_get(काष्ठा mlx5e_ktls_offload_context_tx *priv_tx,
		 u32 tcp_seq, पूर्णांक datalen, काष्ठा tx_sync_info *info)
अणु
	काष्ठा tls_offload_context_tx *tx_ctx = priv_tx->tx_ctx;
	क्रमागत mlx5e_ktls_sync_retval ret = MLX5E_KTLS_SYNC_DONE;
	काष्ठा tls_record_info *record;
	पूर्णांक reमुख्यing, i = 0;
	अचिन्हित दीर्घ flags;
	bool ends_beक्रमe;

	spin_lock_irqsave(&tx_ctx->lock, flags);
	record = tls_get_record(tx_ctx, tcp_seq, &info->rcd_sn);

	अगर (unlikely(!record)) अणु
		ret = MLX5E_KTLS_SYNC_FAIL;
		जाओ out;
	पूर्ण

	/* There are the following हालs:
	 * 1. packet ends beक्रमe start marker: bypass offload.
	 * 2. packet starts beक्रमe start marker and ends after it: drop,
	 *    not supported, अवरोधs contract with kernel.
	 * 3. packet ends beक्रमe tls record info starts: drop,
	 *    this packet was alपढ़ोy acknowledged and its record info
	 *    was released.
	 */
	ends_beक्रमe = beक्रमe(tcp_seq + datalen - 1, tls_record_start_seq(record));

	अगर (unlikely(tls_record_is_start_marker(record))) अणु
		ret = ends_beक्रमe ? MLX5E_KTLS_SYNC_SKIP_NO_DATA : MLX5E_KTLS_SYNC_FAIL;
		जाओ out;
	पूर्ण अन्यथा अगर (ends_beक्रमe) अणु
		ret = MLX5E_KTLS_SYNC_FAIL;
		जाओ out;
	पूर्ण

	info->sync_len = tcp_seq - tls_record_start_seq(record);
	reमुख्यing = info->sync_len;
	जबतक (reमुख्यing > 0) अणु
		skb_frag_t *frag = &record->frags[i];

		get_page(skb_frag_page(frag));
		reमुख्यing -= skb_frag_size(frag);
		info->frags[i++] = *frag;
	पूर्ण
	/* reduce the part which will be sent with the original SKB */
	अगर (reमुख्यing < 0)
		skb_frag_size_add(&info->frags[i - 1], reमुख्यing);
	info->nr_frags = i;
out:
	spin_unlock_irqrestore(&tx_ctx->lock, flags);
	वापस ret;
पूर्ण

अटल व्योम
tx_post_resync_params(काष्ठा mlx5e_txqsq *sq,
		      काष्ठा mlx5e_ktls_offload_context_tx *priv_tx,
		      u64 rcd_sn)
अणु
	काष्ठा tls12_crypto_info_aes_gcm_128 *info = &priv_tx->crypto_info;
	__be64 rn_be = cpu_to_be64(rcd_sn);
	bool skip_अटल_post;
	u16 rec_seq_sz;
	अक्षर *rec_seq;

	rec_seq = info->rec_seq;
	rec_seq_sz = माप(info->rec_seq);

	skip_अटल_post = !स_भेद(rec_seq, &rn_be, rec_seq_sz);
	अगर (!skip_अटल_post)
		स_नकल(rec_seq, &rn_be, rec_seq_sz);

	mlx5e_ktls_tx_post_param_wqes(sq, priv_tx, skip_अटल_post, true);
पूर्ण

अटल पूर्णांक
tx_post_resync_dump(काष्ठा mlx5e_txqsq *sq, skb_frag_t *frag, u32 tisn, bool first)
अणु
	काष्ठा mlx5_wqe_ctrl_seg *cseg;
	काष्ठा mlx5_wqe_data_seg *dseg;
	काष्ठा mlx5e_dump_wqe *wqe;
	dma_addr_t dma_addr = 0;
	u16 ds_cnt;
	पूर्णांक fsz;
	u16 pi;

	BUILD_BUG_ON(MLX5E_KTLS_DUMP_WQEBBS != 1);
	pi = mlx5_wq_cyc_ctr2ix(&sq->wq, sq->pc);
	wqe = MLX5E_TLS_FETCH_DUMP_WQE(sq, pi);

	ds_cnt = माप(*wqe) / MLX5_SEND_WQE_DS;

	cseg = &wqe->ctrl;
	dseg = &wqe->data;

	cseg->opmod_idx_opcode = cpu_to_be32((sq->pc << 8)  | MLX5_OPCODE_DUMP);
	cseg->qpn_ds           = cpu_to_be32((sq->sqn << 8) | ds_cnt);
	cseg->tis_tir_num      = cpu_to_be32(tisn << 8);
	cseg->fm_ce_se         = first ? MLX5_FENCE_MODE_INITIATOR_SMALL : 0;

	fsz = skb_frag_size(frag);
	dma_addr = skb_frag_dma_map(sq->pdev, frag, 0, fsz,
				    DMA_TO_DEVICE);
	अगर (unlikely(dma_mapping_error(sq->pdev, dma_addr)))
		वापस -ENOMEM;

	dseg->addr       = cpu_to_be64(dma_addr);
	dseg->lkey       = sq->mkey_be;
	dseg->byte_count = cpu_to_be32(fsz);
	mlx5e_dma_push(sq, dma_addr, fsz, MLX5E_DMA_MAP_PAGE);

	tx_fill_wi(sq, pi, MLX5E_KTLS_DUMP_WQEBBS, fsz, skb_frag_page(frag));
	sq->pc += MLX5E_KTLS_DUMP_WQEBBS;

	वापस 0;
पूर्ण

व्योम mlx5e_ktls_tx_handle_resync_dump_comp(काष्ठा mlx5e_txqsq *sq,
					   काष्ठा mlx5e_tx_wqe_info *wi,
					   u32 *dma_fअगरo_cc)
अणु
	काष्ठा mlx5e_sq_stats *stats;
	काष्ठा mlx5e_sq_dma *dma;

	dma = mlx5e_dma_get(sq, (*dma_fअगरo_cc)++);
	stats = sq->stats;

	mlx5e_tx_dma_unmap(sq->pdev, dma);
	put_page(wi->resync_dump_frag_page);
	stats->tls_dump_packets++;
	stats->tls_dump_bytes += wi->num_bytes;
पूर्ण

अटल व्योम tx_post_fence_nop(काष्ठा mlx5e_txqsq *sq)
अणु
	काष्ठा mlx5_wq_cyc *wq = &sq->wq;
	u16 pi = mlx5_wq_cyc_ctr2ix(wq, sq->pc);

	tx_fill_wi(sq, pi, 1, 0, शून्य);

	mlx5e_post_nop_fence(wq, sq->sqn, &sq->pc);
पूर्ण

अटल क्रमागत mlx5e_ktls_sync_retval
mlx5e_ktls_tx_handle_ooo(काष्ठा mlx5e_ktls_offload_context_tx *priv_tx,
			 काष्ठा mlx5e_txqsq *sq,
			 पूर्णांक datalen,
			 u32 seq)
अणु
	काष्ठा mlx5e_sq_stats *stats = sq->stats;
	क्रमागत mlx5e_ktls_sync_retval ret;
	काष्ठा tx_sync_info info = अणुपूर्ण;
	पूर्णांक i = 0;

	ret = tx_sync_info_get(priv_tx, seq, datalen, &info);
	अगर (unlikely(ret != MLX5E_KTLS_SYNC_DONE)) अणु
		अगर (ret == MLX5E_KTLS_SYNC_SKIP_NO_DATA) अणु
			stats->tls_skip_no_sync_data++;
			वापस MLX5E_KTLS_SYNC_SKIP_NO_DATA;
		पूर्ण
		/* We might get here अगर a retransmission reaches the driver
		 * after the relevant record is acked.
		 * It should be safe to drop the packet in this हाल
		 */
		stats->tls_drop_no_sync_data++;
		जाओ err_out;
	पूर्ण

	stats->tls_ooo++;

	tx_post_resync_params(sq, priv_tx, info.rcd_sn);

	/* If no dump WQE was sent, we need to have a fence NOP WQE beक्रमe the
	 * actual data xmit.
	 */
	अगर (!info.nr_frags) अणु
		tx_post_fence_nop(sq);
		वापस MLX5E_KTLS_SYNC_DONE;
	पूर्ण

	क्रम (; i < info.nr_frags; i++) अणु
		अचिन्हित पूर्णांक orig_fsz, frag_offset = 0, n = 0;
		skb_frag_t *f = &info.frags[i];

		orig_fsz = skb_frag_size(f);

		करो अणु
			bool fence = !(i || frag_offset);
			अचिन्हित पूर्णांक fsz;

			n++;
			fsz = min_t(अचिन्हित पूर्णांक, sq->hw_mtu, orig_fsz - frag_offset);
			skb_frag_size_set(f, fsz);
			अगर (tx_post_resync_dump(sq, f, priv_tx->tisn, fence)) अणु
				page_ref_add(skb_frag_page(f), n - 1);
				जाओ err_out;
			पूर्ण

			skb_frag_off_add(f, fsz);
			frag_offset += fsz;
		पूर्ण जबतक (frag_offset < orig_fsz);

		page_ref_add(skb_frag_page(f), n - 1);
	पूर्ण

	वापस MLX5E_KTLS_SYNC_DONE;

err_out:
	क्रम (; i < info.nr_frags; i++)
		/* The put_page() here unकरोes the page ref obtained in tx_sync_info_get().
		 * Page refs obtained क्रम the DUMP WQEs above (by page_ref_add) will be
		 * released only upon their completions (or in mlx5e_मुक्त_txqsq_descs,
		 * अगर channel बंदs).
		 */
		put_page(skb_frag_page(&info.frags[i]));

	वापस MLX5E_KTLS_SYNC_FAIL;
पूर्ण

bool mlx5e_ktls_handle_tx_skb(काष्ठा tls_context *tls_ctx, काष्ठा mlx5e_txqsq *sq,
			      काष्ठा sk_buff *skb, पूर्णांक datalen,
			      काष्ठा mlx5e_accel_tx_tls_state *state)
अणु
	काष्ठा mlx5e_ktls_offload_context_tx *priv_tx;
	काष्ठा mlx5e_sq_stats *stats = sq->stats;
	u32 seq;

	priv_tx = mlx5e_get_ktls_tx_priv_ctx(tls_ctx);

	अगर (unlikely(mlx5e_ktls_tx_offload_test_and_clear_pending(priv_tx))) अणु
		mlx5e_ktls_tx_post_param_wqes(sq, priv_tx, false, false);
	पूर्ण

	seq = ntohl(tcp_hdr(skb)->seq);
	अगर (unlikely(priv_tx->expected_seq != seq)) अणु
		क्रमागत mlx5e_ktls_sync_retval ret =
			mlx5e_ktls_tx_handle_ooo(priv_tx, sq, datalen, seq);

		चयन (ret) अणु
		हाल MLX5E_KTLS_SYNC_DONE:
			अवरोध;
		हाल MLX5E_KTLS_SYNC_SKIP_NO_DATA:
			अगर (likely(!skb->decrypted))
				जाओ out;
			WARN_ON_ONCE(1);
			fallthrough;
		हाल MLX5E_KTLS_SYNC_FAIL:
			जाओ err_out;
		पूर्ण
	पूर्ण

	priv_tx->expected_seq = seq + datalen;

	state->tls_tisn = priv_tx->tisn;

	stats->tls_encrypted_packets += skb_is_gso(skb) ? skb_shinfo(skb)->gso_segs : 1;
	stats->tls_encrypted_bytes   += datalen;

out:
	वापस true;

err_out:
	dev_kमुक्त_skb_any(skb);
	वापस false;
पूर्ण
