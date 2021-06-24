<शैली गुरु>
/*
 * Copyright (c) 2017, Mellanox Technologies, Ltd.  All rights reserved.
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
 */

#समावेश "lib/mlx5.h"
#समावेश "en.h"
#समावेश "en_accel/tls.h"
#समावेश "en_accel/en_accel.h"

अटल अचिन्हित पूर्णांक stats_grps_num(काष्ठा mlx5e_priv *priv)
अणु
	वापस !priv->profile->stats_grps_num ? 0 :
		priv->profile->stats_grps_num(priv);
पूर्ण

अचिन्हित पूर्णांक mlx5e_stats_total_num(काष्ठा mlx5e_priv *priv)
अणु
	mlx5e_stats_grp_t *stats_grps = priv->profile->stats_grps;
	स्थिर अचिन्हित पूर्णांक num_stats_grps = stats_grps_num(priv);
	अचिन्हित पूर्णांक total = 0;
	पूर्णांक i;

	क्रम (i = 0; i < num_stats_grps; i++)
		total += stats_grps[i]->get_num_stats(priv);

	वापस total;
पूर्ण

व्योम mlx5e_stats_update_nकरो_stats(काष्ठा mlx5e_priv *priv)
अणु
	mlx5e_stats_grp_t *stats_grps = priv->profile->stats_grps;
	स्थिर अचिन्हित पूर्णांक num_stats_grps = stats_grps_num(priv);
	पूर्णांक i;

	क्रम (i = num_stats_grps - 1; i >= 0; i--)
		अगर (stats_grps[i]->update_stats &&
		    stats_grps[i]->update_stats_mask & MLX5E_NDO_UPDATE_STATS)
			stats_grps[i]->update_stats(priv);
पूर्ण

व्योम mlx5e_stats_update(काष्ठा mlx5e_priv *priv)
अणु
	mlx5e_stats_grp_t *stats_grps = priv->profile->stats_grps;
	स्थिर अचिन्हित पूर्णांक num_stats_grps = stats_grps_num(priv);
	पूर्णांक i;

	क्रम (i = num_stats_grps - 1; i >= 0; i--)
		अगर (stats_grps[i]->update_stats)
			stats_grps[i]->update_stats(priv);
पूर्ण

व्योम mlx5e_stats_fill(काष्ठा mlx5e_priv *priv, u64 *data, पूर्णांक idx)
अणु
	mlx5e_stats_grp_t *stats_grps = priv->profile->stats_grps;
	स्थिर अचिन्हित पूर्णांक num_stats_grps = stats_grps_num(priv);
	पूर्णांक i;

	क्रम (i = 0; i < num_stats_grps; i++)
		idx = stats_grps[i]->fill_stats(priv, data, idx);
पूर्ण

व्योम mlx5e_stats_fill_strings(काष्ठा mlx5e_priv *priv, u8 *data)
अणु
	mlx5e_stats_grp_t *stats_grps = priv->profile->stats_grps;
	स्थिर अचिन्हित पूर्णांक num_stats_grps = stats_grps_num(priv);
	पूर्णांक i, idx = 0;

	क्रम (i = 0; i < num_stats_grps; i++)
		idx = stats_grps[i]->fill_strings(priv, data, idx);
पूर्ण

/* Concrete NIC Stats */

अटल स्थिर काष्ठा counter_desc sw_stats_desc[] = अणु
	अणु MLX5E_DECLARE_STAT(काष्ठा mlx5e_sw_stats, rx_packets) पूर्ण,
	अणु MLX5E_DECLARE_STAT(काष्ठा mlx5e_sw_stats, rx_bytes) पूर्ण,
	अणु MLX5E_DECLARE_STAT(काष्ठा mlx5e_sw_stats, tx_packets) पूर्ण,
	अणु MLX5E_DECLARE_STAT(काष्ठा mlx5e_sw_stats, tx_bytes) पूर्ण,
	अणु MLX5E_DECLARE_STAT(काष्ठा mlx5e_sw_stats, tx_tso_packets) पूर्ण,
	अणु MLX5E_DECLARE_STAT(काष्ठा mlx5e_sw_stats, tx_tso_bytes) पूर्ण,
	अणु MLX5E_DECLARE_STAT(काष्ठा mlx5e_sw_stats, tx_tso_inner_packets) पूर्ण,
	अणु MLX5E_DECLARE_STAT(काष्ठा mlx5e_sw_stats, tx_tso_inner_bytes) पूर्ण,
	अणु MLX5E_DECLARE_STAT(काष्ठा mlx5e_sw_stats, tx_added_vlan_packets) पूर्ण,
	अणु MLX5E_DECLARE_STAT(काष्ठा mlx5e_sw_stats, tx_nop) पूर्ण,
	अणु MLX5E_DECLARE_STAT(काष्ठा mlx5e_sw_stats, tx_mpwqe_blks) पूर्ण,
	अणु MLX5E_DECLARE_STAT(काष्ठा mlx5e_sw_stats, tx_mpwqe_pkts) पूर्ण,

#अगर_घोषित CONFIG_MLX5_EN_TLS
	अणु MLX5E_DECLARE_STAT(काष्ठा mlx5e_sw_stats, tx_tls_encrypted_packets) पूर्ण,
	अणु MLX5E_DECLARE_STAT(काष्ठा mlx5e_sw_stats, tx_tls_encrypted_bytes) पूर्ण,
	अणु MLX5E_DECLARE_STAT(काष्ठा mlx5e_sw_stats, tx_tls_ooo) पूर्ण,
	अणु MLX5E_DECLARE_STAT(काष्ठा mlx5e_sw_stats, tx_tls_dump_packets) पूर्ण,
	अणु MLX5E_DECLARE_STAT(काष्ठा mlx5e_sw_stats, tx_tls_dump_bytes) पूर्ण,
	अणु MLX5E_DECLARE_STAT(काष्ठा mlx5e_sw_stats, tx_tls_resync_bytes) पूर्ण,
	अणु MLX5E_DECLARE_STAT(काष्ठा mlx5e_sw_stats, tx_tls_skip_no_sync_data) पूर्ण,
	अणु MLX5E_DECLARE_STAT(काष्ठा mlx5e_sw_stats, tx_tls_drop_no_sync_data) पूर्ण,
	अणु MLX5E_DECLARE_STAT(काष्ठा mlx5e_sw_stats, tx_tls_drop_bypass_req) पूर्ण,
#पूर्ण_अगर

	अणु MLX5E_DECLARE_STAT(काष्ठा mlx5e_sw_stats, rx_lro_packets) पूर्ण,
	अणु MLX5E_DECLARE_STAT(काष्ठा mlx5e_sw_stats, rx_lro_bytes) पूर्ण,
	अणु MLX5E_DECLARE_STAT(काष्ठा mlx5e_sw_stats, rx_ecn_mark) पूर्ण,
	अणु MLX5E_DECLARE_STAT(काष्ठा mlx5e_sw_stats, rx_हटाओd_vlan_packets) पूर्ण,
	अणु MLX5E_DECLARE_STAT(काष्ठा mlx5e_sw_stats, rx_csum_unnecessary) पूर्ण,
	अणु MLX5E_DECLARE_STAT(काष्ठा mlx5e_sw_stats, rx_csum_none) पूर्ण,
	अणु MLX5E_DECLARE_STAT(काष्ठा mlx5e_sw_stats, rx_csum_complete) पूर्ण,
	अणु MLX5E_DECLARE_STAT(काष्ठा mlx5e_sw_stats, rx_csum_complete_tail) पूर्ण,
	अणु MLX5E_DECLARE_STAT(काष्ठा mlx5e_sw_stats, rx_csum_complete_tail_slow) पूर्ण,
	अणु MLX5E_DECLARE_STAT(काष्ठा mlx5e_sw_stats, rx_csum_unnecessary_inner) पूर्ण,
	अणु MLX5E_DECLARE_STAT(काष्ठा mlx5e_sw_stats, rx_xdp_drop) पूर्ण,
	अणु MLX5E_DECLARE_STAT(काष्ठा mlx5e_sw_stats, rx_xdp_redirect) पूर्ण,
	अणु MLX5E_DECLARE_STAT(काष्ठा mlx5e_sw_stats, rx_xdp_tx_xmit) पूर्ण,
	अणु MLX5E_DECLARE_STAT(काष्ठा mlx5e_sw_stats, rx_xdp_tx_mpwqe) पूर्ण,
	अणु MLX5E_DECLARE_STAT(काष्ठा mlx5e_sw_stats, rx_xdp_tx_inlnw) पूर्ण,
	अणु MLX5E_DECLARE_STAT(काष्ठा mlx5e_sw_stats, rx_xdp_tx_nops) पूर्ण,
	अणु MLX5E_DECLARE_STAT(काष्ठा mlx5e_sw_stats, rx_xdp_tx_full) पूर्ण,
	अणु MLX5E_DECLARE_STAT(काष्ठा mlx5e_sw_stats, rx_xdp_tx_err) पूर्ण,
	अणु MLX5E_DECLARE_STAT(काष्ठा mlx5e_sw_stats, rx_xdp_tx_cqe) पूर्ण,
	अणु MLX5E_DECLARE_STAT(काष्ठा mlx5e_sw_stats, tx_csum_none) पूर्ण,
	अणु MLX5E_DECLARE_STAT(काष्ठा mlx5e_sw_stats, tx_csum_partial) पूर्ण,
	अणु MLX5E_DECLARE_STAT(काष्ठा mlx5e_sw_stats, tx_csum_partial_inner) पूर्ण,
	अणु MLX5E_DECLARE_STAT(काष्ठा mlx5e_sw_stats, tx_queue_stopped) पूर्ण,
	अणु MLX5E_DECLARE_STAT(काष्ठा mlx5e_sw_stats, tx_queue_dropped) पूर्ण,
	अणु MLX5E_DECLARE_STAT(काष्ठा mlx5e_sw_stats, tx_xmit_more) पूर्ण,
	अणु MLX5E_DECLARE_STAT(काष्ठा mlx5e_sw_stats, tx_recover) पूर्ण,
	अणु MLX5E_DECLARE_STAT(काष्ठा mlx5e_sw_stats, tx_cqes) पूर्ण,
	अणु MLX5E_DECLARE_STAT(काष्ठा mlx5e_sw_stats, tx_queue_wake) पूर्ण,
	अणु MLX5E_DECLARE_STAT(काष्ठा mlx5e_sw_stats, tx_cqe_err) पूर्ण,
	अणु MLX5E_DECLARE_STAT(काष्ठा mlx5e_sw_stats, tx_xdp_xmit) पूर्ण,
	अणु MLX5E_DECLARE_STAT(काष्ठा mlx5e_sw_stats, tx_xdp_mpwqe) पूर्ण,
	अणु MLX5E_DECLARE_STAT(काष्ठा mlx5e_sw_stats, tx_xdp_inlnw) पूर्ण,
	अणु MLX5E_DECLARE_STAT(काष्ठा mlx5e_sw_stats, tx_xdp_nops) पूर्ण,
	अणु MLX5E_DECLARE_STAT(काष्ठा mlx5e_sw_stats, tx_xdp_full) पूर्ण,
	अणु MLX5E_DECLARE_STAT(काष्ठा mlx5e_sw_stats, tx_xdp_err) पूर्ण,
	अणु MLX5E_DECLARE_STAT(काष्ठा mlx5e_sw_stats, tx_xdp_cqes) पूर्ण,
	अणु MLX5E_DECLARE_STAT(काष्ठा mlx5e_sw_stats, rx_wqe_err) पूर्ण,
	अणु MLX5E_DECLARE_STAT(काष्ठा mlx5e_sw_stats, rx_mpwqe_filler_cqes) पूर्ण,
	अणु MLX5E_DECLARE_STAT(काष्ठा mlx5e_sw_stats, rx_mpwqe_filler_strides) पूर्ण,
	अणु MLX5E_DECLARE_STAT(काष्ठा mlx5e_sw_stats, rx_oversize_pkts_sw_drop) पूर्ण,
	अणु MLX5E_DECLARE_STAT(काष्ठा mlx5e_sw_stats, rx_buff_alloc_err) पूर्ण,
	अणु MLX5E_DECLARE_STAT(काष्ठा mlx5e_sw_stats, rx_cqe_compress_blks) पूर्ण,
	अणु MLX5E_DECLARE_STAT(काष्ठा mlx5e_sw_stats, rx_cqe_compress_pkts) पूर्ण,
	अणु MLX5E_DECLARE_STAT(काष्ठा mlx5e_sw_stats, rx_cache_reuse) पूर्ण,
	अणु MLX5E_DECLARE_STAT(काष्ठा mlx5e_sw_stats, rx_cache_full) पूर्ण,
	अणु MLX5E_DECLARE_STAT(काष्ठा mlx5e_sw_stats, rx_cache_empty) पूर्ण,
	अणु MLX5E_DECLARE_STAT(काष्ठा mlx5e_sw_stats, rx_cache_busy) पूर्ण,
	अणु MLX5E_DECLARE_STAT(काष्ठा mlx5e_sw_stats, rx_cache_waive) पूर्ण,
	अणु MLX5E_DECLARE_STAT(काष्ठा mlx5e_sw_stats, rx_congst_umr) पूर्ण,
	अणु MLX5E_DECLARE_STAT(काष्ठा mlx5e_sw_stats, rx_arfs_err) पूर्ण,
	अणु MLX5E_DECLARE_STAT(काष्ठा mlx5e_sw_stats, rx_recover) पूर्ण,
#अगर_घोषित CONFIG_MLX5_EN_TLS
	अणु MLX5E_DECLARE_STAT(काष्ठा mlx5e_sw_stats, rx_tls_decrypted_packets) पूर्ण,
	अणु MLX5E_DECLARE_STAT(काष्ठा mlx5e_sw_stats, rx_tls_decrypted_bytes) पूर्ण,
	अणु MLX5E_DECLARE_STAT(काष्ठा mlx5e_sw_stats, rx_tls_resync_req_pkt) पूर्ण,
	अणु MLX5E_DECLARE_STAT(काष्ठा mlx5e_sw_stats, rx_tls_resync_req_start) पूर्ण,
	अणु MLX5E_DECLARE_STAT(काष्ठा mlx5e_sw_stats, rx_tls_resync_req_end) पूर्ण,
	अणु MLX5E_DECLARE_STAT(काष्ठा mlx5e_sw_stats, rx_tls_resync_req_skip) पूर्ण,
	अणु MLX5E_DECLARE_STAT(काष्ठा mlx5e_sw_stats, rx_tls_resync_res_ok) पूर्ण,
	अणु MLX5E_DECLARE_STAT(काष्ठा mlx5e_sw_stats, rx_tls_resync_res_retry) पूर्ण,
	अणु MLX5E_DECLARE_STAT(काष्ठा mlx5e_sw_stats, rx_tls_resync_res_skip) पूर्ण,
	अणु MLX5E_DECLARE_STAT(काष्ठा mlx5e_sw_stats, rx_tls_err) पूर्ण,
#पूर्ण_अगर
	अणु MLX5E_DECLARE_STAT(काष्ठा mlx5e_sw_stats, ch_events) पूर्ण,
	अणु MLX5E_DECLARE_STAT(काष्ठा mlx5e_sw_stats, ch_poll) पूर्ण,
	अणु MLX5E_DECLARE_STAT(काष्ठा mlx5e_sw_stats, ch_arm) पूर्ण,
	अणु MLX5E_DECLARE_STAT(काष्ठा mlx5e_sw_stats, ch_aff_change) पूर्ण,
	अणु MLX5E_DECLARE_STAT(काष्ठा mlx5e_sw_stats, ch_क्रमce_irq) पूर्ण,
	अणु MLX5E_DECLARE_STAT(काष्ठा mlx5e_sw_stats, ch_eq_rearm) पूर्ण,
	अणु MLX5E_DECLARE_STAT(काष्ठा mlx5e_sw_stats, rx_xsk_packets) पूर्ण,
	अणु MLX5E_DECLARE_STAT(काष्ठा mlx5e_sw_stats, rx_xsk_bytes) पूर्ण,
	अणु MLX5E_DECLARE_STAT(काष्ठा mlx5e_sw_stats, rx_xsk_csum_complete) पूर्ण,
	अणु MLX5E_DECLARE_STAT(काष्ठा mlx5e_sw_stats, rx_xsk_csum_unnecessary) पूर्ण,
	अणु MLX5E_DECLARE_STAT(काष्ठा mlx5e_sw_stats, rx_xsk_csum_unnecessary_inner) पूर्ण,
	अणु MLX5E_DECLARE_STAT(काष्ठा mlx5e_sw_stats, rx_xsk_csum_none) पूर्ण,
	अणु MLX5E_DECLARE_STAT(काष्ठा mlx5e_sw_stats, rx_xsk_ecn_mark) पूर्ण,
	अणु MLX5E_DECLARE_STAT(काष्ठा mlx5e_sw_stats, rx_xsk_हटाओd_vlan_packets) पूर्ण,
	अणु MLX5E_DECLARE_STAT(काष्ठा mlx5e_sw_stats, rx_xsk_xdp_drop) पूर्ण,
	अणु MLX5E_DECLARE_STAT(काष्ठा mlx5e_sw_stats, rx_xsk_xdp_redirect) पूर्ण,
	अणु MLX5E_DECLARE_STAT(काष्ठा mlx5e_sw_stats, rx_xsk_wqe_err) पूर्ण,
	अणु MLX5E_DECLARE_STAT(काष्ठा mlx5e_sw_stats, rx_xsk_mpwqe_filler_cqes) पूर्ण,
	अणु MLX5E_DECLARE_STAT(काष्ठा mlx5e_sw_stats, rx_xsk_mpwqe_filler_strides) पूर्ण,
	अणु MLX5E_DECLARE_STAT(काष्ठा mlx5e_sw_stats, rx_xsk_oversize_pkts_sw_drop) पूर्ण,
	अणु MLX5E_DECLARE_STAT(काष्ठा mlx5e_sw_stats, rx_xsk_buff_alloc_err) पूर्ण,
	अणु MLX5E_DECLARE_STAT(काष्ठा mlx5e_sw_stats, rx_xsk_cqe_compress_blks) पूर्ण,
	अणु MLX5E_DECLARE_STAT(काष्ठा mlx5e_sw_stats, rx_xsk_cqe_compress_pkts) पूर्ण,
	अणु MLX5E_DECLARE_STAT(काष्ठा mlx5e_sw_stats, rx_xsk_congst_umr) पूर्ण,
	अणु MLX5E_DECLARE_STAT(काष्ठा mlx5e_sw_stats, rx_xsk_arfs_err) पूर्ण,
	अणु MLX5E_DECLARE_STAT(काष्ठा mlx5e_sw_stats, tx_xsk_xmit) पूर्ण,
	अणु MLX5E_DECLARE_STAT(काष्ठा mlx5e_sw_stats, tx_xsk_mpwqe) पूर्ण,
	अणु MLX5E_DECLARE_STAT(काष्ठा mlx5e_sw_stats, tx_xsk_inlnw) पूर्ण,
	अणु MLX5E_DECLARE_STAT(काष्ठा mlx5e_sw_stats, tx_xsk_full) पूर्ण,
	अणु MLX5E_DECLARE_STAT(काष्ठा mlx5e_sw_stats, tx_xsk_err) पूर्ण,
	अणु MLX5E_DECLARE_STAT(काष्ठा mlx5e_sw_stats, tx_xsk_cqes) पूर्ण,
पूर्ण;

#घोषणा NUM_SW_COUNTERS			ARRAY_SIZE(sw_stats_desc)

अटल MLX5E_DECLARE_STATS_GRP_OP_NUM_STATS(sw)
अणु
	वापस NUM_SW_COUNTERS;
पूर्ण

अटल MLX5E_DECLARE_STATS_GRP_OP_FILL_STRS(sw)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < NUM_SW_COUNTERS; i++)
		म_नकल(data + (idx++) * ETH_GSTRING_LEN, sw_stats_desc[i].क्रमmat);
	वापस idx;
पूर्ण

अटल MLX5E_DECLARE_STATS_GRP_OP_FILL_STATS(sw)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < NUM_SW_COUNTERS; i++)
		data[idx++] = MLX5E_READ_CTR64_CPU(&priv->stats.sw, sw_stats_desc, i);
	वापस idx;
पूर्ण

अटल व्योम mlx5e_stats_grp_sw_update_stats_xdp_red(काष्ठा mlx5e_sw_stats *s,
						    काष्ठा mlx5e_xdpsq_stats *xdpsq_red_stats)
अणु
	s->tx_xdp_xmit  += xdpsq_red_stats->xmit;
	s->tx_xdp_mpwqe += xdpsq_red_stats->mpwqe;
	s->tx_xdp_inlnw += xdpsq_red_stats->inlnw;
	s->tx_xdp_nops  += xdpsq_red_stats->nops;
	s->tx_xdp_full  += xdpsq_red_stats->full;
	s->tx_xdp_err   += xdpsq_red_stats->err;
	s->tx_xdp_cqes  += xdpsq_red_stats->cqes;
पूर्ण

अटल व्योम mlx5e_stats_grp_sw_update_stats_xdpsq(काष्ठा mlx5e_sw_stats *s,
						  काष्ठा mlx5e_xdpsq_stats *xdpsq_stats)
अणु
	s->rx_xdp_tx_xmit  += xdpsq_stats->xmit;
	s->rx_xdp_tx_mpwqe += xdpsq_stats->mpwqe;
	s->rx_xdp_tx_inlnw += xdpsq_stats->inlnw;
	s->rx_xdp_tx_nops  += xdpsq_stats->nops;
	s->rx_xdp_tx_full  += xdpsq_stats->full;
	s->rx_xdp_tx_err   += xdpsq_stats->err;
	s->rx_xdp_tx_cqe   += xdpsq_stats->cqes;
पूर्ण

अटल व्योम mlx5e_stats_grp_sw_update_stats_xsksq(काष्ठा mlx5e_sw_stats *s,
						  काष्ठा mlx5e_xdpsq_stats *xsksq_stats)
अणु
	s->tx_xsk_xmit  += xsksq_stats->xmit;
	s->tx_xsk_mpwqe += xsksq_stats->mpwqe;
	s->tx_xsk_inlnw += xsksq_stats->inlnw;
	s->tx_xsk_full  += xsksq_stats->full;
	s->tx_xsk_err   += xsksq_stats->err;
	s->tx_xsk_cqes  += xsksq_stats->cqes;
पूर्ण

अटल व्योम mlx5e_stats_grp_sw_update_stats_xskrq(काष्ठा mlx5e_sw_stats *s,
						  काष्ठा mlx5e_rq_stats *xskrq_stats)
अणु
	s->rx_xsk_packets                += xskrq_stats->packets;
	s->rx_xsk_bytes                  += xskrq_stats->bytes;
	s->rx_xsk_csum_complete          += xskrq_stats->csum_complete;
	s->rx_xsk_csum_unnecessary       += xskrq_stats->csum_unnecessary;
	s->rx_xsk_csum_unnecessary_inner += xskrq_stats->csum_unnecessary_inner;
	s->rx_xsk_csum_none              += xskrq_stats->csum_none;
	s->rx_xsk_ecn_mark               += xskrq_stats->ecn_mark;
	s->rx_xsk_हटाओd_vlan_packets   += xskrq_stats->हटाओd_vlan_packets;
	s->rx_xsk_xdp_drop               += xskrq_stats->xdp_drop;
	s->rx_xsk_xdp_redirect           += xskrq_stats->xdp_redirect;
	s->rx_xsk_wqe_err                += xskrq_stats->wqe_err;
	s->rx_xsk_mpwqe_filler_cqes      += xskrq_stats->mpwqe_filler_cqes;
	s->rx_xsk_mpwqe_filler_strides   += xskrq_stats->mpwqe_filler_strides;
	s->rx_xsk_oversize_pkts_sw_drop  += xskrq_stats->oversize_pkts_sw_drop;
	s->rx_xsk_buff_alloc_err         += xskrq_stats->buff_alloc_err;
	s->rx_xsk_cqe_compress_blks      += xskrq_stats->cqe_compress_blks;
	s->rx_xsk_cqe_compress_pkts      += xskrq_stats->cqe_compress_pkts;
	s->rx_xsk_congst_umr             += xskrq_stats->congst_umr;
	s->rx_xsk_arfs_err               += xskrq_stats->arfs_err;
पूर्ण

अटल व्योम mlx5e_stats_grp_sw_update_stats_rq_stats(काष्ठा mlx5e_sw_stats *s,
						     काष्ठा mlx5e_rq_stats *rq_stats)
अणु
	s->rx_packets                 += rq_stats->packets;
	s->rx_bytes                   += rq_stats->bytes;
	s->rx_lro_packets             += rq_stats->lro_packets;
	s->rx_lro_bytes               += rq_stats->lro_bytes;
	s->rx_ecn_mark                += rq_stats->ecn_mark;
	s->rx_हटाओd_vlan_packets    += rq_stats->हटाओd_vlan_packets;
	s->rx_csum_none               += rq_stats->csum_none;
	s->rx_csum_complete           += rq_stats->csum_complete;
	s->rx_csum_complete_tail      += rq_stats->csum_complete_tail;
	s->rx_csum_complete_tail_slow += rq_stats->csum_complete_tail_slow;
	s->rx_csum_unnecessary        += rq_stats->csum_unnecessary;
	s->rx_csum_unnecessary_inner  += rq_stats->csum_unnecessary_inner;
	s->rx_xdp_drop                += rq_stats->xdp_drop;
	s->rx_xdp_redirect            += rq_stats->xdp_redirect;
	s->rx_wqe_err                 += rq_stats->wqe_err;
	s->rx_mpwqe_filler_cqes       += rq_stats->mpwqe_filler_cqes;
	s->rx_mpwqe_filler_strides    += rq_stats->mpwqe_filler_strides;
	s->rx_oversize_pkts_sw_drop   += rq_stats->oversize_pkts_sw_drop;
	s->rx_buff_alloc_err          += rq_stats->buff_alloc_err;
	s->rx_cqe_compress_blks       += rq_stats->cqe_compress_blks;
	s->rx_cqe_compress_pkts       += rq_stats->cqe_compress_pkts;
	s->rx_cache_reuse             += rq_stats->cache_reuse;
	s->rx_cache_full              += rq_stats->cache_full;
	s->rx_cache_empty             += rq_stats->cache_empty;
	s->rx_cache_busy              += rq_stats->cache_busy;
	s->rx_cache_waive             += rq_stats->cache_waive;
	s->rx_congst_umr              += rq_stats->congst_umr;
	s->rx_arfs_err                += rq_stats->arfs_err;
	s->rx_recover                 += rq_stats->recover;
#अगर_घोषित CONFIG_MLX5_EN_TLS
	s->rx_tls_decrypted_packets   += rq_stats->tls_decrypted_packets;
	s->rx_tls_decrypted_bytes     += rq_stats->tls_decrypted_bytes;
	s->rx_tls_resync_req_pkt      += rq_stats->tls_resync_req_pkt;
	s->rx_tls_resync_req_start    += rq_stats->tls_resync_req_start;
	s->rx_tls_resync_req_end      += rq_stats->tls_resync_req_end;
	s->rx_tls_resync_req_skip     += rq_stats->tls_resync_req_skip;
	s->rx_tls_resync_res_ok       += rq_stats->tls_resync_res_ok;
	s->rx_tls_resync_res_retry    += rq_stats->tls_resync_res_retry;
	s->rx_tls_resync_res_skip     += rq_stats->tls_resync_res_skip;
	s->rx_tls_err                 += rq_stats->tls_err;
#पूर्ण_अगर
पूर्ण

अटल व्योम mlx5e_stats_grp_sw_update_stats_ch_stats(काष्ठा mlx5e_sw_stats *s,
						     काष्ठा mlx5e_ch_stats *ch_stats)
अणु
	s->ch_events      += ch_stats->events;
	s->ch_poll        += ch_stats->poll;
	s->ch_arm         += ch_stats->arm;
	s->ch_aff_change  += ch_stats->aff_change;
	s->ch_क्रमce_irq   += ch_stats->क्रमce_irq;
	s->ch_eq_rearm    += ch_stats->eq_rearm;
पूर्ण

अटल व्योम mlx5e_stats_grp_sw_update_stats_sq(काष्ठा mlx5e_sw_stats *s,
					       काष्ठा mlx5e_sq_stats *sq_stats)
अणु
	s->tx_packets               += sq_stats->packets;
	s->tx_bytes                 += sq_stats->bytes;
	s->tx_tso_packets           += sq_stats->tso_packets;
	s->tx_tso_bytes             += sq_stats->tso_bytes;
	s->tx_tso_inner_packets     += sq_stats->tso_inner_packets;
	s->tx_tso_inner_bytes       += sq_stats->tso_inner_bytes;
	s->tx_added_vlan_packets    += sq_stats->added_vlan_packets;
	s->tx_nop                   += sq_stats->nop;
	s->tx_mpwqe_blks            += sq_stats->mpwqe_blks;
	s->tx_mpwqe_pkts            += sq_stats->mpwqe_pkts;
	s->tx_queue_stopped         += sq_stats->stopped;
	s->tx_queue_wake            += sq_stats->wake;
	s->tx_queue_dropped         += sq_stats->dropped;
	s->tx_cqe_err               += sq_stats->cqe_err;
	s->tx_recover               += sq_stats->recover;
	s->tx_xmit_more             += sq_stats->xmit_more;
	s->tx_csum_partial_inner    += sq_stats->csum_partial_inner;
	s->tx_csum_none             += sq_stats->csum_none;
	s->tx_csum_partial          += sq_stats->csum_partial;
#अगर_घोषित CONFIG_MLX5_EN_TLS
	s->tx_tls_encrypted_packets += sq_stats->tls_encrypted_packets;
	s->tx_tls_encrypted_bytes   += sq_stats->tls_encrypted_bytes;
	s->tx_tls_ooo               += sq_stats->tls_ooo;
	s->tx_tls_dump_bytes        += sq_stats->tls_dump_bytes;
	s->tx_tls_dump_packets      += sq_stats->tls_dump_packets;
	s->tx_tls_resync_bytes      += sq_stats->tls_resync_bytes;
	s->tx_tls_skip_no_sync_data += sq_stats->tls_skip_no_sync_data;
	s->tx_tls_drop_no_sync_data += sq_stats->tls_drop_no_sync_data;
	s->tx_tls_drop_bypass_req   += sq_stats->tls_drop_bypass_req;
#पूर्ण_अगर
	s->tx_cqes                  += sq_stats->cqes;
पूर्ण

अटल व्योम mlx5e_stats_grp_sw_update_stats_ptp(काष्ठा mlx5e_priv *priv,
						काष्ठा mlx5e_sw_stats *s)
अणु
	पूर्णांक i;

	अगर (!priv->tx_ptp_खोलोed && !priv->rx_ptp_खोलोed)
		वापस;

	mlx5e_stats_grp_sw_update_stats_ch_stats(s, &priv->ptp_stats.ch);

	अगर (priv->tx_ptp_खोलोed) अणु
		क्रम (i = 0; i < priv->max_खोलोed_tc; i++) अणु
			mlx5e_stats_grp_sw_update_stats_sq(s, &priv->ptp_stats.sq[i]);

			/* https://gcc.gnu.org/bugzilla/show_bug.cgi?id=92657 */
			barrier();
		पूर्ण
	पूर्ण
	अगर (priv->rx_ptp_खोलोed) अणु
		mlx5e_stats_grp_sw_update_stats_rq_stats(s, &priv->ptp_stats.rq);

		/* https://gcc.gnu.org/bugzilla/show_bug.cgi?id=92657 */
		barrier();
	पूर्ण
पूर्ण

अटल व्योम mlx5e_stats_grp_sw_update_stats_qos(काष्ठा mlx5e_priv *priv,
						काष्ठा mlx5e_sw_stats *s)
अणु
	काष्ठा mlx5e_sq_stats **stats;
	u16 max_qos_sqs;
	पूर्णांक i;

	/* Pairs with smp_store_release in mlx5e_खोलो_qos_sq. */
	max_qos_sqs = smp_load_acquire(&priv->htb.max_qos_sqs);
	stats = READ_ONCE(priv->htb.qos_sq_stats);

	क्रम (i = 0; i < max_qos_sqs; i++) अणु
		mlx5e_stats_grp_sw_update_stats_sq(s, READ_ONCE(stats[i]));

		/* https://gcc.gnu.org/bugzilla/show_bug.cgi?id=92657 */
		barrier();
	पूर्ण
पूर्ण

अटल MLX5E_DECLARE_STATS_GRP_OP_UPDATE_STATS(sw)
अणु
	काष्ठा mlx5e_sw_stats *s = &priv->stats.sw;
	पूर्णांक i;

	स_रखो(s, 0, माप(*s));

	क्रम (i = 0; i < priv->max_nch; i++) अणु
		काष्ठा mlx5e_channel_stats *channel_stats =
			&priv->channel_stats[i];
		पूर्णांक j;

		mlx5e_stats_grp_sw_update_stats_rq_stats(s, &channel_stats->rq);
		mlx5e_stats_grp_sw_update_stats_xdpsq(s, &channel_stats->rq_xdpsq);
		mlx5e_stats_grp_sw_update_stats_ch_stats(s, &channel_stats->ch);
		/* xdp redirect */
		mlx5e_stats_grp_sw_update_stats_xdp_red(s, &channel_stats->xdpsq);
		/* AF_XDP zero-copy */
		mlx5e_stats_grp_sw_update_stats_xskrq(s, &channel_stats->xskrq);
		mlx5e_stats_grp_sw_update_stats_xsksq(s, &channel_stats->xsksq);

		क्रम (j = 0; j < priv->max_खोलोed_tc; j++) अणु
			mlx5e_stats_grp_sw_update_stats_sq(s, &channel_stats->sq[j]);

			/* https://gcc.gnu.org/bugzilla/show_bug.cgi?id=92657 */
			barrier();
		पूर्ण
	पूर्ण
	mlx5e_stats_grp_sw_update_stats_ptp(priv, s);
	mlx5e_stats_grp_sw_update_stats_qos(priv, s);
पूर्ण

अटल स्थिर काष्ठा counter_desc q_stats_desc[] = अणु
	अणु MLX5E_DECLARE_STAT(काष्ठा mlx5e_qcounter_stats, rx_out_of_buffer) पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा counter_desc drop_rq_stats_desc[] = अणु
	अणु MLX5E_DECLARE_STAT(काष्ठा mlx5e_qcounter_stats, rx_अगर_करोwn_packets) पूर्ण,
पूर्ण;

#घोषणा NUM_Q_COUNTERS			ARRAY_SIZE(q_stats_desc)
#घोषणा NUM_DROP_RQ_COUNTERS		ARRAY_SIZE(drop_rq_stats_desc)

अटल MLX5E_DECLARE_STATS_GRP_OP_NUM_STATS(qcnt)
अणु
	पूर्णांक num_stats = 0;

	अगर (priv->q_counter)
		num_stats += NUM_Q_COUNTERS;

	अगर (priv->drop_rq_q_counter)
		num_stats += NUM_DROP_RQ_COUNTERS;

	वापस num_stats;
पूर्ण

अटल MLX5E_DECLARE_STATS_GRP_OP_FILL_STRS(qcnt)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < NUM_Q_COUNTERS && priv->q_counter; i++)
		म_नकल(data + (idx++) * ETH_GSTRING_LEN,
		       q_stats_desc[i].क्रमmat);

	क्रम (i = 0; i < NUM_DROP_RQ_COUNTERS && priv->drop_rq_q_counter; i++)
		म_नकल(data + (idx++) * ETH_GSTRING_LEN,
		       drop_rq_stats_desc[i].क्रमmat);

	वापस idx;
पूर्ण

अटल MLX5E_DECLARE_STATS_GRP_OP_FILL_STATS(qcnt)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < NUM_Q_COUNTERS && priv->q_counter; i++)
		data[idx++] = MLX5E_READ_CTR32_CPU(&priv->stats.qcnt,
						   q_stats_desc, i);
	क्रम (i = 0; i < NUM_DROP_RQ_COUNTERS && priv->drop_rq_q_counter; i++)
		data[idx++] = MLX5E_READ_CTR32_CPU(&priv->stats.qcnt,
						   drop_rq_stats_desc, i);
	वापस idx;
पूर्ण

अटल MLX5E_DECLARE_STATS_GRP_OP_UPDATE_STATS(qcnt)
अणु
	काष्ठा mlx5e_qcounter_stats *qcnt = &priv->stats.qcnt;
	u32 out[MLX5_ST_SZ_DW(query_q_counter_out)] = अणुपूर्ण;
	u32 in[MLX5_ST_SZ_DW(query_q_counter_in)] = अणुपूर्ण;
	पूर्णांक ret;

	MLX5_SET(query_q_counter_in, in, opcode, MLX5_CMD_OP_QUERY_Q_COUNTER);

	अगर (priv->q_counter) अणु
		MLX5_SET(query_q_counter_in, in, counter_set_id,
			 priv->q_counter);
		ret = mlx5_cmd_exec_inout(priv->mdev, query_q_counter, in, out);
		अगर (!ret)
			qcnt->rx_out_of_buffer = MLX5_GET(query_q_counter_out,
							  out, out_of_buffer);
	पूर्ण

	अगर (priv->drop_rq_q_counter) अणु
		MLX5_SET(query_q_counter_in, in, counter_set_id,
			 priv->drop_rq_q_counter);
		ret = mlx5_cmd_exec_inout(priv->mdev, query_q_counter, in, out);
		अगर (!ret)
			qcnt->rx_अगर_करोwn_packets = MLX5_GET(query_q_counter_out,
							    out, out_of_buffer);
	पूर्ण
पूर्ण

#घोषणा VNIC_ENV_OFF(c) MLX5_BYTE_OFF(query_vnic_env_out, c)
अटल स्थिर काष्ठा counter_desc vnic_env_stats_steer_desc[] = अणु
	अणु "rx_steer_missed_packets",
		VNIC_ENV_OFF(vport_env.nic_receive_steering_discard) पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा counter_desc vnic_env_stats_dev_oob_desc[] = अणु
	अणु "dev_internal_queue_oob",
		VNIC_ENV_OFF(vport_env.पूर्णांकernal_rq_out_of_buffer) पूर्ण,
पूर्ण;

#घोषणा NUM_VNIC_ENV_STEER_COUNTERS(dev) \
	(MLX5_CAP_GEN(dev, nic_receive_steering_discard) ? \
	 ARRAY_SIZE(vnic_env_stats_steer_desc) : 0)
#घोषणा NUM_VNIC_ENV_DEV_OOB_COUNTERS(dev) \
	(MLX5_CAP_GEN(dev, vnic_env_पूर्णांक_rq_oob) ? \
	 ARRAY_SIZE(vnic_env_stats_dev_oob_desc) : 0)

अटल MLX5E_DECLARE_STATS_GRP_OP_NUM_STATS(vnic_env)
अणु
	वापस NUM_VNIC_ENV_STEER_COUNTERS(priv->mdev) +
		NUM_VNIC_ENV_DEV_OOB_COUNTERS(priv->mdev);
पूर्ण

अटल MLX5E_DECLARE_STATS_GRP_OP_FILL_STRS(vnic_env)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < NUM_VNIC_ENV_STEER_COUNTERS(priv->mdev); i++)
		म_नकल(data + (idx++) * ETH_GSTRING_LEN,
		       vnic_env_stats_steer_desc[i].क्रमmat);

	क्रम (i = 0; i < NUM_VNIC_ENV_DEV_OOB_COUNTERS(priv->mdev); i++)
		म_नकल(data + (idx++) * ETH_GSTRING_LEN,
		       vnic_env_stats_dev_oob_desc[i].क्रमmat);
	वापस idx;
पूर्ण

अटल MLX5E_DECLARE_STATS_GRP_OP_FILL_STATS(vnic_env)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < NUM_VNIC_ENV_STEER_COUNTERS(priv->mdev); i++)
		data[idx++] = MLX5E_READ_CTR64_BE(priv->stats.vnic.query_vnic_env_out,
						  vnic_env_stats_steer_desc, i);

	क्रम (i = 0; i < NUM_VNIC_ENV_DEV_OOB_COUNTERS(priv->mdev); i++)
		data[idx++] = MLX5E_READ_CTR32_BE(priv->stats.vnic.query_vnic_env_out,
						  vnic_env_stats_dev_oob_desc, i);
	वापस idx;
पूर्ण

अटल MLX5E_DECLARE_STATS_GRP_OP_UPDATE_STATS(vnic_env)
अणु
	u32 *out = (u32 *)priv->stats.vnic.query_vnic_env_out;
	u32 in[MLX5_ST_SZ_DW(query_vnic_env_in)] = अणुपूर्ण;
	काष्ठा mlx5_core_dev *mdev = priv->mdev;

	अगर (!MLX5_CAP_GEN(priv->mdev, nic_receive_steering_discard))
		वापस;

	MLX5_SET(query_vnic_env_in, in, opcode, MLX5_CMD_OP_QUERY_VNIC_ENV);
	mlx5_cmd_exec_inout(mdev, query_vnic_env, in, out);
पूर्ण

#घोषणा VPORT_COUNTER_OFF(c) MLX5_BYTE_OFF(query_vport_counter_out, c)
अटल स्थिर काष्ठा counter_desc vport_stats_desc[] = अणु
	अणु "rx_vport_unicast_packets",
		VPORT_COUNTER_OFF(received_eth_unicast.packets) पूर्ण,
	अणु "rx_vport_unicast_bytes",
		VPORT_COUNTER_OFF(received_eth_unicast.octets) पूर्ण,
	अणु "tx_vport_unicast_packets",
		VPORT_COUNTER_OFF(transmitted_eth_unicast.packets) पूर्ण,
	अणु "tx_vport_unicast_bytes",
		VPORT_COUNTER_OFF(transmitted_eth_unicast.octets) पूर्ण,
	अणु "rx_vport_multicast_packets",
		VPORT_COUNTER_OFF(received_eth_multicast.packets) पूर्ण,
	अणु "rx_vport_multicast_bytes",
		VPORT_COUNTER_OFF(received_eth_multicast.octets) पूर्ण,
	अणु "tx_vport_multicast_packets",
		VPORT_COUNTER_OFF(transmitted_eth_multicast.packets) पूर्ण,
	अणु "tx_vport_multicast_bytes",
		VPORT_COUNTER_OFF(transmitted_eth_multicast.octets) पूर्ण,
	अणु "rx_vport_broadcast_packets",
		VPORT_COUNTER_OFF(received_eth_broadcast.packets) पूर्ण,
	अणु "rx_vport_broadcast_bytes",
		VPORT_COUNTER_OFF(received_eth_broadcast.octets) पूर्ण,
	अणु "tx_vport_broadcast_packets",
		VPORT_COUNTER_OFF(transmitted_eth_broadcast.packets) पूर्ण,
	अणु "tx_vport_broadcast_bytes",
		VPORT_COUNTER_OFF(transmitted_eth_broadcast.octets) पूर्ण,
	अणु "rx_vport_rdma_unicast_packets",
		VPORT_COUNTER_OFF(received_ib_unicast.packets) पूर्ण,
	अणु "rx_vport_rdma_unicast_bytes",
		VPORT_COUNTER_OFF(received_ib_unicast.octets) पूर्ण,
	अणु "tx_vport_rdma_unicast_packets",
		VPORT_COUNTER_OFF(transmitted_ib_unicast.packets) पूर्ण,
	अणु "tx_vport_rdma_unicast_bytes",
		VPORT_COUNTER_OFF(transmitted_ib_unicast.octets) पूर्ण,
	अणु "rx_vport_rdma_multicast_packets",
		VPORT_COUNTER_OFF(received_ib_multicast.packets) पूर्ण,
	अणु "rx_vport_rdma_multicast_bytes",
		VPORT_COUNTER_OFF(received_ib_multicast.octets) पूर्ण,
	अणु "tx_vport_rdma_multicast_packets",
		VPORT_COUNTER_OFF(transmitted_ib_multicast.packets) पूर्ण,
	अणु "tx_vport_rdma_multicast_bytes",
		VPORT_COUNTER_OFF(transmitted_ib_multicast.octets) पूर्ण,
पूर्ण;

#घोषणा NUM_VPORT_COUNTERS		ARRAY_SIZE(vport_stats_desc)

अटल MLX5E_DECLARE_STATS_GRP_OP_NUM_STATS(vport)
अणु
	वापस NUM_VPORT_COUNTERS;
पूर्ण

अटल MLX5E_DECLARE_STATS_GRP_OP_FILL_STRS(vport)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < NUM_VPORT_COUNTERS; i++)
		म_नकल(data + (idx++) * ETH_GSTRING_LEN, vport_stats_desc[i].क्रमmat);
	वापस idx;
पूर्ण

अटल MLX5E_DECLARE_STATS_GRP_OP_FILL_STATS(vport)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < NUM_VPORT_COUNTERS; i++)
		data[idx++] = MLX5E_READ_CTR64_BE(priv->stats.vport.query_vport_out,
						  vport_stats_desc, i);
	वापस idx;
पूर्ण

अटल MLX5E_DECLARE_STATS_GRP_OP_UPDATE_STATS(vport)
अणु
	u32 *out = (u32 *)priv->stats.vport.query_vport_out;
	u32 in[MLX5_ST_SZ_DW(query_vport_counter_in)] = अणुपूर्ण;
	काष्ठा mlx5_core_dev *mdev = priv->mdev;

	MLX5_SET(query_vport_counter_in, in, opcode, MLX5_CMD_OP_QUERY_VPORT_COUNTER);
	mlx5_cmd_exec_inout(mdev, query_vport_counter, in, out);
पूर्ण

#घोषणा PPORT_802_3_OFF(c) \
	MLX5_BYTE_OFF(ppcnt_reg, \
		      counter_set.eth_802_3_cntrs_grp_data_layout.c##_high)
अटल स्थिर काष्ठा counter_desc pport_802_3_stats_desc[] = अणु
	अणु "tx_packets_phy", PPORT_802_3_OFF(a_frames_transmitted_ok) पूर्ण,
	अणु "rx_packets_phy", PPORT_802_3_OFF(a_frames_received_ok) पूर्ण,
	अणु "rx_crc_errors_phy", PPORT_802_3_OFF(a_frame_check_sequence_errors) पूर्ण,
	अणु "tx_bytes_phy", PPORT_802_3_OFF(a_octets_transmitted_ok) पूर्ण,
	अणु "rx_bytes_phy", PPORT_802_3_OFF(a_octets_received_ok) पूर्ण,
	अणु "tx_multicast_phy", PPORT_802_3_OFF(a_multicast_frames_xmitted_ok) पूर्ण,
	अणु "tx_broadcast_phy", PPORT_802_3_OFF(a_broadcast_frames_xmitted_ok) पूर्ण,
	अणु "rx_multicast_phy", PPORT_802_3_OFF(a_multicast_frames_received_ok) पूर्ण,
	अणु "rx_broadcast_phy", PPORT_802_3_OFF(a_broadcast_frames_received_ok) पूर्ण,
	अणु "rx_in_range_len_errors_phy", PPORT_802_3_OFF(a_in_range_length_errors) पूर्ण,
	अणु "rx_out_of_range_len_phy", PPORT_802_3_OFF(a_out_of_range_length_field) पूर्ण,
	अणु "rx_oversize_pkts_phy", PPORT_802_3_OFF(a_frame_too_दीर्घ_errors) पूर्ण,
	अणु "rx_symbol_err_phy", PPORT_802_3_OFF(a_symbol_error_during_carrier) पूर्ण,
	अणु "tx_mac_control_phy", PPORT_802_3_OFF(a_mac_control_frames_transmitted) पूर्ण,
	अणु "rx_mac_control_phy", PPORT_802_3_OFF(a_mac_control_frames_received) पूर्ण,
	अणु "rx_unsupported_op_phy", PPORT_802_3_OFF(a_unsupported_opcodes_received) पूर्ण,
	अणु "rx_pause_ctrl_phy", PPORT_802_3_OFF(a_छोड़ो_mac_ctrl_frames_received) पूर्ण,
	अणु "tx_pause_ctrl_phy", PPORT_802_3_OFF(a_छोड़ो_mac_ctrl_frames_transmitted) पूर्ण,
पूर्ण;

#घोषणा NUM_PPORT_802_3_COUNTERS	ARRAY_SIZE(pport_802_3_stats_desc)

अटल MLX5E_DECLARE_STATS_GRP_OP_NUM_STATS(802_3)
अणु
	वापस NUM_PPORT_802_3_COUNTERS;
पूर्ण

अटल MLX5E_DECLARE_STATS_GRP_OP_FILL_STRS(802_3)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < NUM_PPORT_802_3_COUNTERS; i++)
		म_नकल(data + (idx++) * ETH_GSTRING_LEN, pport_802_3_stats_desc[i].क्रमmat);
	वापस idx;
पूर्ण

अटल MLX5E_DECLARE_STATS_GRP_OP_FILL_STATS(802_3)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < NUM_PPORT_802_3_COUNTERS; i++)
		data[idx++] = MLX5E_READ_CTR64_BE(&priv->stats.pport.IEEE_802_3_counters,
						  pport_802_3_stats_desc, i);
	वापस idx;
पूर्ण

#घोषणा MLX5_BASIC_PPCNT_SUPPORTED(mdev) \
	(MLX5_CAP_GEN(mdev, pcam_reg) ? MLX5_CAP_PCAM_REG(mdev, ppcnt) : 1)

अटल MLX5E_DECLARE_STATS_GRP_OP_UPDATE_STATS(802_3)
अणु
	काष्ठा mlx5e_pport_stats *pstats = &priv->stats.pport;
	काष्ठा mlx5_core_dev *mdev = priv->mdev;
	u32 in[MLX5_ST_SZ_DW(ppcnt_reg)] = अणु0पूर्ण;
	पूर्णांक sz = MLX5_ST_SZ_BYTES(ppcnt_reg);
	व्योम *out;

	अगर (!MLX5_BASIC_PPCNT_SUPPORTED(mdev))
		वापस;

	MLX5_SET(ppcnt_reg, in, local_port, 1);
	out = pstats->IEEE_802_3_counters;
	MLX5_SET(ppcnt_reg, in, grp, MLX5_IEEE_802_3_COUNTERS_GROUP);
	mlx5_core_access_reg(mdev, in, sz, out, sz, MLX5_REG_PPCNT, 0, 0);
पूर्ण

#घोषणा MLX5E_READ_CTR64_BE_F(ptr, set, c)		\
	be64_to_cpu(*(__be64 *)((अक्षर *)ptr +		\
		MLX5_BYTE_OFF(ppcnt_reg,		\
			      counter_set.set.c##_high)))

अटल पूर्णांक mlx5e_stats_get_ieee(काष्ठा mlx5_core_dev *mdev,
				u32 *ppcnt_ieee_802_3)
अणु
	u32 in[MLX5_ST_SZ_DW(ppcnt_reg)] = अणुपूर्ण;
	पूर्णांक sz = MLX5_ST_SZ_BYTES(ppcnt_reg);

	अगर (!MLX5_BASIC_PPCNT_SUPPORTED(mdev))
		वापस -EOPNOTSUPP;

	MLX5_SET(ppcnt_reg, in, local_port, 1);
	MLX5_SET(ppcnt_reg, in, grp, MLX5_IEEE_802_3_COUNTERS_GROUP);
	वापस mlx5_core_access_reg(mdev, in, sz, ppcnt_ieee_802_3,
				    sz, MLX5_REG_PPCNT, 0, 0);
पूर्ण

व्योम mlx5e_stats_छोड़ो_get(काष्ठा mlx5e_priv *priv,
			   काष्ठा ethtool_छोड़ो_stats *छोड़ो_stats)
अणु
	u32 ppcnt_ieee_802_3[MLX5_ST_SZ_DW(ppcnt_reg)];
	काष्ठा mlx5_core_dev *mdev = priv->mdev;

	अगर (mlx5e_stats_get_ieee(mdev, ppcnt_ieee_802_3))
		वापस;

	छोड़ो_stats->tx_छोड़ो_frames =
		MLX5E_READ_CTR64_BE_F(ppcnt_ieee_802_3,
				      eth_802_3_cntrs_grp_data_layout,
				      a_छोड़ो_mac_ctrl_frames_transmitted);
	छोड़ो_stats->rx_छोड़ो_frames =
		MLX5E_READ_CTR64_BE_F(ppcnt_ieee_802_3,
				      eth_802_3_cntrs_grp_data_layout,
				      a_छोड़ो_mac_ctrl_frames_received);
पूर्ण

व्योम mlx5e_stats_eth_phy_get(काष्ठा mlx5e_priv *priv,
			     काष्ठा ethtool_eth_phy_stats *phy_stats)
अणु
	u32 ppcnt_ieee_802_3[MLX5_ST_SZ_DW(ppcnt_reg)];
	काष्ठा mlx5_core_dev *mdev = priv->mdev;

	अगर (mlx5e_stats_get_ieee(mdev, ppcnt_ieee_802_3))
		वापस;

	phy_stats->SymbolErrorDuringCarrier =
		MLX5E_READ_CTR64_BE_F(ppcnt_ieee_802_3,
				      eth_802_3_cntrs_grp_data_layout,
				      a_symbol_error_during_carrier);
पूर्ण

व्योम mlx5e_stats_eth_mac_get(काष्ठा mlx5e_priv *priv,
			     काष्ठा ethtool_eth_mac_stats *mac_stats)
अणु
	u32 ppcnt_ieee_802_3[MLX5_ST_SZ_DW(ppcnt_reg)];
	काष्ठा mlx5_core_dev *mdev = priv->mdev;

	अगर (mlx5e_stats_get_ieee(mdev, ppcnt_ieee_802_3))
		वापस;

#घोषणा RD(name)							\
	MLX5E_READ_CTR64_BE_F(ppcnt_ieee_802_3,				\
			      eth_802_3_cntrs_grp_data_layout,		\
			      name)

	mac_stats->FramesTransmittedOK	= RD(a_frames_transmitted_ok);
	mac_stats->FramesReceivedOK	= RD(a_frames_received_ok);
	mac_stats->FrameCheckSequenceErrors = RD(a_frame_check_sequence_errors);
	mac_stats->OctetsTransmittedOK	= RD(a_octets_transmitted_ok);
	mac_stats->OctetsReceivedOK	= RD(a_octets_received_ok);
	mac_stats->MulticastFramesXmittedOK = RD(a_multicast_frames_xmitted_ok);
	mac_stats->BroadcastFramesXmittedOK = RD(a_broadcast_frames_xmitted_ok);
	mac_stats->MulticastFramesReceivedOK = RD(a_multicast_frames_received_ok);
	mac_stats->BroadcastFramesReceivedOK = RD(a_broadcast_frames_received_ok);
	mac_stats->InRangeLengthErrors	= RD(a_in_range_length_errors);
	mac_stats->OutOfRangeLengthField = RD(a_out_of_range_length_field);
	mac_stats->FrameTooLongErrors	= RD(a_frame_too_दीर्घ_errors);
#अघोषित RD
पूर्ण

व्योम mlx5e_stats_eth_ctrl_get(काष्ठा mlx5e_priv *priv,
			      काष्ठा ethtool_eth_ctrl_stats *ctrl_stats)
अणु
	u32 ppcnt_ieee_802_3[MLX5_ST_SZ_DW(ppcnt_reg)];
	काष्ठा mlx5_core_dev *mdev = priv->mdev;

	अगर (mlx5e_stats_get_ieee(mdev, ppcnt_ieee_802_3))
		वापस;

	ctrl_stats->MACControlFramesTransmitted =
		MLX5E_READ_CTR64_BE_F(ppcnt_ieee_802_3,
				      eth_802_3_cntrs_grp_data_layout,
				      a_mac_control_frames_transmitted);
	ctrl_stats->MACControlFramesReceived =
		MLX5E_READ_CTR64_BE_F(ppcnt_ieee_802_3,
				      eth_802_3_cntrs_grp_data_layout,
				      a_mac_control_frames_received);
	ctrl_stats->UnsupportedOpcodesReceived =
		MLX5E_READ_CTR64_BE_F(ppcnt_ieee_802_3,
				      eth_802_3_cntrs_grp_data_layout,
				      a_unsupported_opcodes_received);
पूर्ण

#घोषणा PPORT_2863_OFF(c) \
	MLX5_BYTE_OFF(ppcnt_reg, \
		      counter_set.eth_2863_cntrs_grp_data_layout.c##_high)
अटल स्थिर काष्ठा counter_desc pport_2863_stats_desc[] = अणु
	अणु "rx_discards_phy", PPORT_2863_OFF(अगर_in_discards) पूर्ण,
	अणु "tx_discards_phy", PPORT_2863_OFF(अगर_out_discards) पूर्ण,
	अणु "tx_errors_phy", PPORT_2863_OFF(अगर_out_errors) पूर्ण,
पूर्ण;

#घोषणा NUM_PPORT_2863_COUNTERS		ARRAY_SIZE(pport_2863_stats_desc)

अटल MLX5E_DECLARE_STATS_GRP_OP_NUM_STATS(2863)
अणु
	वापस NUM_PPORT_2863_COUNTERS;
पूर्ण

अटल MLX5E_DECLARE_STATS_GRP_OP_FILL_STRS(2863)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < NUM_PPORT_2863_COUNTERS; i++)
		म_नकल(data + (idx++) * ETH_GSTRING_LEN, pport_2863_stats_desc[i].क्रमmat);
	वापस idx;
पूर्ण

अटल MLX5E_DECLARE_STATS_GRP_OP_FILL_STATS(2863)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < NUM_PPORT_2863_COUNTERS; i++)
		data[idx++] = MLX5E_READ_CTR64_BE(&priv->stats.pport.RFC_2863_counters,
						  pport_2863_stats_desc, i);
	वापस idx;
पूर्ण

अटल MLX5E_DECLARE_STATS_GRP_OP_UPDATE_STATS(2863)
अणु
	काष्ठा mlx5e_pport_stats *pstats = &priv->stats.pport;
	काष्ठा mlx5_core_dev *mdev = priv->mdev;
	u32 in[MLX5_ST_SZ_DW(ppcnt_reg)] = अणु0पूर्ण;
	पूर्णांक sz = MLX5_ST_SZ_BYTES(ppcnt_reg);
	व्योम *out;

	MLX5_SET(ppcnt_reg, in, local_port, 1);
	out = pstats->RFC_2863_counters;
	MLX5_SET(ppcnt_reg, in, grp, MLX5_RFC_2863_COUNTERS_GROUP);
	mlx5_core_access_reg(mdev, in, sz, out, sz, MLX5_REG_PPCNT, 0, 0);
पूर्ण

#घोषणा PPORT_2819_OFF(c) \
	MLX5_BYTE_OFF(ppcnt_reg, \
		      counter_set.eth_2819_cntrs_grp_data_layout.c##_high)
अटल स्थिर काष्ठा counter_desc pport_2819_stats_desc[] = अणु
	अणु "rx_undersize_pkts_phy", PPORT_2819_OFF(ether_stats_undersize_pkts) पूर्ण,
	अणु "rx_fragments_phy", PPORT_2819_OFF(ether_stats_fragments) पूर्ण,
	अणु "rx_jabbers_phy", PPORT_2819_OFF(ether_stats_jabbers) पूर्ण,
	अणु "rx_64_bytes_phy", PPORT_2819_OFF(ether_stats_pkts64octets) पूर्ण,
	अणु "rx_65_to_127_bytes_phy", PPORT_2819_OFF(ether_stats_pkts65to127octets) पूर्ण,
	अणु "rx_128_to_255_bytes_phy", PPORT_2819_OFF(ether_stats_pkts128to255octets) पूर्ण,
	अणु "rx_256_to_511_bytes_phy", PPORT_2819_OFF(ether_stats_pkts256to511octets) पूर्ण,
	अणु "rx_512_to_1023_bytes_phy", PPORT_2819_OFF(ether_stats_pkts512to1023octets) पूर्ण,
	अणु "rx_1024_to_1518_bytes_phy", PPORT_2819_OFF(ether_stats_pkts1024to1518octets) पूर्ण,
	अणु "rx_1519_to_2047_bytes_phy", PPORT_2819_OFF(ether_stats_pkts1519to2047octets) पूर्ण,
	अणु "rx_2048_to_4095_bytes_phy", PPORT_2819_OFF(ether_stats_pkts2048to4095octets) पूर्ण,
	अणु "rx_4096_to_8191_bytes_phy", PPORT_2819_OFF(ether_stats_pkts4096to8191octets) पूर्ण,
	अणु "rx_8192_to_10239_bytes_phy", PPORT_2819_OFF(ether_stats_pkts8192to10239octets) पूर्ण,
पूर्ण;

#घोषणा NUM_PPORT_2819_COUNTERS		ARRAY_SIZE(pport_2819_stats_desc)

अटल MLX5E_DECLARE_STATS_GRP_OP_NUM_STATS(2819)
अणु
	वापस NUM_PPORT_2819_COUNTERS;
पूर्ण

अटल MLX5E_DECLARE_STATS_GRP_OP_FILL_STRS(2819)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < NUM_PPORT_2819_COUNTERS; i++)
		म_नकल(data + (idx++) * ETH_GSTRING_LEN, pport_2819_stats_desc[i].क्रमmat);
	वापस idx;
पूर्ण

अटल MLX5E_DECLARE_STATS_GRP_OP_FILL_STATS(2819)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < NUM_PPORT_2819_COUNTERS; i++)
		data[idx++] = MLX5E_READ_CTR64_BE(&priv->stats.pport.RFC_2819_counters,
						  pport_2819_stats_desc, i);
	वापस idx;
पूर्ण

अटल MLX5E_DECLARE_STATS_GRP_OP_UPDATE_STATS(2819)
अणु
	काष्ठा mlx5e_pport_stats *pstats = &priv->stats.pport;
	काष्ठा mlx5_core_dev *mdev = priv->mdev;
	u32 in[MLX5_ST_SZ_DW(ppcnt_reg)] = अणु0पूर्ण;
	पूर्णांक sz = MLX5_ST_SZ_BYTES(ppcnt_reg);
	व्योम *out;

	अगर (!MLX5_BASIC_PPCNT_SUPPORTED(mdev))
		वापस;

	MLX5_SET(ppcnt_reg, in, local_port, 1);
	out = pstats->RFC_2819_counters;
	MLX5_SET(ppcnt_reg, in, grp, MLX5_RFC_2819_COUNTERS_GROUP);
	mlx5_core_access_reg(mdev, in, sz, out, sz, MLX5_REG_PPCNT, 0, 0);
पूर्ण

अटल स्थिर काष्ठा ethtool_rmon_hist_range mlx5e_rmon_ranges[] = अणु
	अणु    0,    64 पूर्ण,
	अणु   65,   127 पूर्ण,
	अणु  128,   255 पूर्ण,
	अणु  256,   511 पूर्ण,
	अणु  512,  1023 पूर्ण,
	अणु 1024,  1518 पूर्ण,
	अणु 1519,  2047 पूर्ण,
	अणु 2048,  4095 पूर्ण,
	अणु 4096,  8191 पूर्ण,
	अणु 8192, 10239 पूर्ण,
	अणुपूर्ण
पूर्ण;

व्योम mlx5e_stats_rmon_get(काष्ठा mlx5e_priv *priv,
			  काष्ठा ethtool_rmon_stats *rmon,
			  स्थिर काष्ठा ethtool_rmon_hist_range **ranges)
अणु
	u32 ppcnt_RFC_2819_counters[MLX5_ST_SZ_DW(ppcnt_reg)];
	काष्ठा mlx5_core_dev *mdev = priv->mdev;
	u32 in[MLX5_ST_SZ_DW(ppcnt_reg)] = अणु0पूर्ण;
	पूर्णांक sz = MLX5_ST_SZ_BYTES(ppcnt_reg);

	MLX5_SET(ppcnt_reg, in, local_port, 1);
	MLX5_SET(ppcnt_reg, in, grp, MLX5_RFC_2819_COUNTERS_GROUP);
	अगर (mlx5_core_access_reg(mdev, in, sz, ppcnt_RFC_2819_counters,
				 sz, MLX5_REG_PPCNT, 0, 0))
		वापस;

#घोषणा RD(name)						\
	MLX5E_READ_CTR64_BE_F(ppcnt_RFC_2819_counters,		\
			      eth_2819_cntrs_grp_data_layout,	\
			      name)

	rmon->undersize_pkts	= RD(ether_stats_undersize_pkts);
	rmon->fragments		= RD(ether_stats_fragments);
	rmon->jabbers		= RD(ether_stats_jabbers);

	rmon->hist[0]		= RD(ether_stats_pkts64octets);
	rmon->hist[1]		= RD(ether_stats_pkts65to127octets);
	rmon->hist[2]		= RD(ether_stats_pkts128to255octets);
	rmon->hist[3]		= RD(ether_stats_pkts256to511octets);
	rmon->hist[4]		= RD(ether_stats_pkts512to1023octets);
	rmon->hist[5]		= RD(ether_stats_pkts1024to1518octets);
	rmon->hist[6]		= RD(ether_stats_pkts1519to2047octets);
	rmon->hist[7]		= RD(ether_stats_pkts2048to4095octets);
	rmon->hist[8]		= RD(ether_stats_pkts4096to8191octets);
	rmon->hist[9]		= RD(ether_stats_pkts8192to10239octets);
#अघोषित RD

	*ranges = mlx5e_rmon_ranges;
पूर्ण

#घोषणा PPORT_PHY_STATISTICAL_OFF(c) \
	MLX5_BYTE_OFF(ppcnt_reg, \
		      counter_set.phys_layer_statistical_cntrs.c##_high)
अटल स्थिर काष्ठा counter_desc pport_phy_statistical_stats_desc[] = अणु
	अणु "rx_pcs_symbol_err_phy", PPORT_PHY_STATISTICAL_OFF(phy_symbol_errors) पूर्ण,
	अणु "rx_corrected_bits_phy", PPORT_PHY_STATISTICAL_OFF(phy_corrected_bits) पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा counter_desc
pport_phy_statistical_err_lanes_stats_desc[] = अणु
	अणु "rx_err_lane_0_phy", PPORT_PHY_STATISTICAL_OFF(phy_corrected_bits_lane0) पूर्ण,
	अणु "rx_err_lane_1_phy", PPORT_PHY_STATISTICAL_OFF(phy_corrected_bits_lane1) पूर्ण,
	अणु "rx_err_lane_2_phy", PPORT_PHY_STATISTICAL_OFF(phy_corrected_bits_lane2) पूर्ण,
	अणु "rx_err_lane_3_phy", PPORT_PHY_STATISTICAL_OFF(phy_corrected_bits_lane3) पूर्ण,
पूर्ण;

#घोषणा NUM_PPORT_PHY_STATISTICAL_COUNTERS \
	ARRAY_SIZE(pport_phy_statistical_stats_desc)
#घोषणा NUM_PPORT_PHY_STATISTICAL_PER_LANE_COUNTERS \
	ARRAY_SIZE(pport_phy_statistical_err_lanes_stats_desc)

अटल MLX5E_DECLARE_STATS_GRP_OP_NUM_STATS(phy)
अणु
	काष्ठा mlx5_core_dev *mdev = priv->mdev;
	पूर्णांक num_stats;

	/* "1" क्रम link_करोwn_events special counter */
	num_stats = 1;

	num_stats += MLX5_CAP_PCAM_FEATURE(mdev, ppcnt_statistical_group) ?
		     NUM_PPORT_PHY_STATISTICAL_COUNTERS : 0;

	num_stats += MLX5_CAP_PCAM_FEATURE(mdev, per_lane_error_counters) ?
		     NUM_PPORT_PHY_STATISTICAL_PER_LANE_COUNTERS : 0;

	वापस num_stats;
पूर्ण

अटल MLX5E_DECLARE_STATS_GRP_OP_FILL_STRS(phy)
अणु
	काष्ठा mlx5_core_dev *mdev = priv->mdev;
	पूर्णांक i;

	म_नकल(data + (idx++) * ETH_GSTRING_LEN, "link_down_events_phy");

	अगर (!MLX5_CAP_PCAM_FEATURE(mdev, ppcnt_statistical_group))
		वापस idx;

	क्रम (i = 0; i < NUM_PPORT_PHY_STATISTICAL_COUNTERS; i++)
		म_नकल(data + (idx++) * ETH_GSTRING_LEN,
		       pport_phy_statistical_stats_desc[i].क्रमmat);

	अगर (MLX5_CAP_PCAM_FEATURE(mdev, per_lane_error_counters))
		क्रम (i = 0; i < NUM_PPORT_PHY_STATISTICAL_PER_LANE_COUNTERS; i++)
			म_नकल(data + (idx++) * ETH_GSTRING_LEN,
			       pport_phy_statistical_err_lanes_stats_desc[i].क्रमmat);

	वापस idx;
पूर्ण

अटल MLX5E_DECLARE_STATS_GRP_OP_FILL_STATS(phy)
अणु
	काष्ठा mlx5_core_dev *mdev = priv->mdev;
	पूर्णांक i;

	/* link_करोwn_events_phy has special handling since it is not stored in __be64 क्रमmat */
	data[idx++] = MLX5_GET(ppcnt_reg, priv->stats.pport.phy_counters,
			       counter_set.phys_layer_cntrs.link_करोwn_events);

	अगर (!MLX5_CAP_PCAM_FEATURE(mdev, ppcnt_statistical_group))
		वापस idx;

	क्रम (i = 0; i < NUM_PPORT_PHY_STATISTICAL_COUNTERS; i++)
		data[idx++] =
			MLX5E_READ_CTR64_BE(&priv->stats.pport.phy_statistical_counters,
					    pport_phy_statistical_stats_desc, i);

	अगर (MLX5_CAP_PCAM_FEATURE(mdev, per_lane_error_counters))
		क्रम (i = 0; i < NUM_PPORT_PHY_STATISTICAL_PER_LANE_COUNTERS; i++)
			data[idx++] =
				MLX5E_READ_CTR64_BE(&priv->stats.pport.phy_statistical_counters,
						    pport_phy_statistical_err_lanes_stats_desc,
						    i);
	वापस idx;
पूर्ण

अटल MLX5E_DECLARE_STATS_GRP_OP_UPDATE_STATS(phy)
अणु
	काष्ठा mlx5e_pport_stats *pstats = &priv->stats.pport;
	काष्ठा mlx5_core_dev *mdev = priv->mdev;
	u32 in[MLX5_ST_SZ_DW(ppcnt_reg)] = अणु0पूर्ण;
	पूर्णांक sz = MLX5_ST_SZ_BYTES(ppcnt_reg);
	व्योम *out;

	MLX5_SET(ppcnt_reg, in, local_port, 1);
	out = pstats->phy_counters;
	MLX5_SET(ppcnt_reg, in, grp, MLX5_PHYSICAL_LAYER_COUNTERS_GROUP);
	mlx5_core_access_reg(mdev, in, sz, out, sz, MLX5_REG_PPCNT, 0, 0);

	अगर (!MLX5_CAP_PCAM_FEATURE(mdev, ppcnt_statistical_group))
		वापस;

	out = pstats->phy_statistical_counters;
	MLX5_SET(ppcnt_reg, in, grp, MLX5_PHYSICAL_LAYER_STATISTICAL_GROUP);
	mlx5_core_access_reg(mdev, in, sz, out, sz, MLX5_REG_PPCNT, 0, 0);
पूर्ण

व्योम mlx5e_stats_fec_get(काष्ठा mlx5e_priv *priv,
			 काष्ठा ethtool_fec_stats *fec_stats)
अणु
	u32 ppcnt_phy_statistical[MLX5_ST_SZ_DW(ppcnt_reg)];
	काष्ठा mlx5_core_dev *mdev = priv->mdev;
	u32 in[MLX5_ST_SZ_DW(ppcnt_reg)] = अणु0पूर्ण;
	पूर्णांक sz = MLX5_ST_SZ_BYTES(ppcnt_reg);

	अगर (!MLX5_CAP_PCAM_FEATURE(mdev, ppcnt_statistical_group))
		वापस;

	MLX5_SET(ppcnt_reg, in, local_port, 1);
	MLX5_SET(ppcnt_reg, in, grp, MLX5_PHYSICAL_LAYER_STATISTICAL_GROUP);
	अगर (mlx5_core_access_reg(mdev, in, sz, ppcnt_phy_statistical,
				 sz, MLX5_REG_PPCNT, 0, 0))
		वापस;

	fec_stats->corrected_bits.total =
		MLX5E_READ_CTR64_BE_F(ppcnt_phy_statistical,
				      phys_layer_statistical_cntrs,
				      phy_corrected_bits);
पूर्ण

#घोषणा PPORT_ETH_EXT_OFF(c) \
	MLX5_BYTE_OFF(ppcnt_reg, \
		      counter_set.eth_extended_cntrs_grp_data_layout.c##_high)
अटल स्थिर काष्ठा counter_desc pport_eth_ext_stats_desc[] = अणु
	अणु "rx_buffer_passed_thres_phy", PPORT_ETH_EXT_OFF(rx_buffer_almost_full) पूर्ण,
पूर्ण;

#घोषणा NUM_PPORT_ETH_EXT_COUNTERS	ARRAY_SIZE(pport_eth_ext_stats_desc)

अटल MLX5E_DECLARE_STATS_GRP_OP_NUM_STATS(eth_ext)
अणु
	अगर (MLX5_CAP_PCAM_FEATURE((priv)->mdev, rx_buffer_fullness_counters))
		वापस NUM_PPORT_ETH_EXT_COUNTERS;

	वापस 0;
पूर्ण

अटल MLX5E_DECLARE_STATS_GRP_OP_FILL_STRS(eth_ext)
अणु
	पूर्णांक i;

	अगर (MLX5_CAP_PCAM_FEATURE((priv)->mdev, rx_buffer_fullness_counters))
		क्रम (i = 0; i < NUM_PPORT_ETH_EXT_COUNTERS; i++)
			म_नकल(data + (idx++) * ETH_GSTRING_LEN,
			       pport_eth_ext_stats_desc[i].क्रमmat);
	वापस idx;
पूर्ण

अटल MLX5E_DECLARE_STATS_GRP_OP_FILL_STATS(eth_ext)
अणु
	पूर्णांक i;

	अगर (MLX5_CAP_PCAM_FEATURE((priv)->mdev, rx_buffer_fullness_counters))
		क्रम (i = 0; i < NUM_PPORT_ETH_EXT_COUNTERS; i++)
			data[idx++] =
				MLX5E_READ_CTR64_BE(&priv->stats.pport.eth_ext_counters,
						    pport_eth_ext_stats_desc, i);
	वापस idx;
पूर्ण

अटल MLX5E_DECLARE_STATS_GRP_OP_UPDATE_STATS(eth_ext)
अणु
	काष्ठा mlx5e_pport_stats *pstats = &priv->stats.pport;
	काष्ठा mlx5_core_dev *mdev = priv->mdev;
	u32 in[MLX5_ST_SZ_DW(ppcnt_reg)] = अणु0पूर्ण;
	पूर्णांक sz = MLX5_ST_SZ_BYTES(ppcnt_reg);
	व्योम *out;

	अगर (!MLX5_CAP_PCAM_FEATURE(mdev, rx_buffer_fullness_counters))
		वापस;

	MLX5_SET(ppcnt_reg, in, local_port, 1);
	out = pstats->eth_ext_counters;
	MLX5_SET(ppcnt_reg, in, grp, MLX5_ETHERNET_EXTENDED_COUNTERS_GROUP);
	mlx5_core_access_reg(mdev, in, sz, out, sz, MLX5_REG_PPCNT, 0, 0);
पूर्ण

#घोषणा PCIE_PERF_OFF(c) \
	MLX5_BYTE_OFF(mpcnt_reg, counter_set.pcie_perf_cntrs_grp_data_layout.c)
अटल स्थिर काष्ठा counter_desc pcie_perf_stats_desc[] = अणु
	अणु "rx_pci_signal_integrity", PCIE_PERF_OFF(rx_errors) पूर्ण,
	अणु "tx_pci_signal_integrity", PCIE_PERF_OFF(tx_errors) पूर्ण,
पूर्ण;

#घोषणा PCIE_PERF_OFF64(c) \
	MLX5_BYTE_OFF(mpcnt_reg, counter_set.pcie_perf_cntrs_grp_data_layout.c##_high)
अटल स्थिर काष्ठा counter_desc pcie_perf_stats_desc64[] = अणु
	अणु "outbound_pci_buffer_overflow", PCIE_PERF_OFF64(tx_overflow_buffer_pkt) पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा counter_desc pcie_perf_stall_stats_desc[] = अणु
	अणु "outbound_pci_stalled_rd", PCIE_PERF_OFF(outbound_stalled_पढ़ोs) पूर्ण,
	अणु "outbound_pci_stalled_wr", PCIE_PERF_OFF(outbound_stalled_ग_लिखोs) पूर्ण,
	अणु "outbound_pci_stalled_rd_events", PCIE_PERF_OFF(outbound_stalled_पढ़ोs_events) पूर्ण,
	अणु "outbound_pci_stalled_wr_events", PCIE_PERF_OFF(outbound_stalled_ग_लिखोs_events) पूर्ण,
पूर्ण;

#घोषणा NUM_PCIE_PERF_COUNTERS		ARRAY_SIZE(pcie_perf_stats_desc)
#घोषणा NUM_PCIE_PERF_COUNTERS64	ARRAY_SIZE(pcie_perf_stats_desc64)
#घोषणा NUM_PCIE_PERF_STALL_COUNTERS	ARRAY_SIZE(pcie_perf_stall_stats_desc)

अटल MLX5E_DECLARE_STATS_GRP_OP_NUM_STATS(pcie)
अणु
	पूर्णांक num_stats = 0;

	अगर (MLX5_CAP_MCAM_FEATURE((priv)->mdev, pcie_perक्रमmance_group))
		num_stats += NUM_PCIE_PERF_COUNTERS;

	अगर (MLX5_CAP_MCAM_FEATURE((priv)->mdev, tx_overflow_buffer_pkt))
		num_stats += NUM_PCIE_PERF_COUNTERS64;

	अगर (MLX5_CAP_MCAM_FEATURE((priv)->mdev, pcie_outbound_stalled))
		num_stats += NUM_PCIE_PERF_STALL_COUNTERS;

	वापस num_stats;
पूर्ण

अटल MLX5E_DECLARE_STATS_GRP_OP_FILL_STRS(pcie)
अणु
	पूर्णांक i;

	अगर (MLX5_CAP_MCAM_FEATURE((priv)->mdev, pcie_perक्रमmance_group))
		क्रम (i = 0; i < NUM_PCIE_PERF_COUNTERS; i++)
			म_नकल(data + (idx++) * ETH_GSTRING_LEN,
			       pcie_perf_stats_desc[i].क्रमmat);

	अगर (MLX5_CAP_MCAM_FEATURE((priv)->mdev, tx_overflow_buffer_pkt))
		क्रम (i = 0; i < NUM_PCIE_PERF_COUNTERS64; i++)
			म_नकल(data + (idx++) * ETH_GSTRING_LEN,
			       pcie_perf_stats_desc64[i].क्रमmat);

	अगर (MLX5_CAP_MCAM_FEATURE((priv)->mdev, pcie_outbound_stalled))
		क्रम (i = 0; i < NUM_PCIE_PERF_STALL_COUNTERS; i++)
			म_नकल(data + (idx++) * ETH_GSTRING_LEN,
			       pcie_perf_stall_stats_desc[i].क्रमmat);
	वापस idx;
पूर्ण

अटल MLX5E_DECLARE_STATS_GRP_OP_FILL_STATS(pcie)
अणु
	पूर्णांक i;

	अगर (MLX5_CAP_MCAM_FEATURE((priv)->mdev, pcie_perक्रमmance_group))
		क्रम (i = 0; i < NUM_PCIE_PERF_COUNTERS; i++)
			data[idx++] =
				MLX5E_READ_CTR32_BE(&priv->stats.pcie.pcie_perf_counters,
						    pcie_perf_stats_desc, i);

	अगर (MLX5_CAP_MCAM_FEATURE((priv)->mdev, tx_overflow_buffer_pkt))
		क्रम (i = 0; i < NUM_PCIE_PERF_COUNTERS64; i++)
			data[idx++] =
				MLX5E_READ_CTR64_BE(&priv->stats.pcie.pcie_perf_counters,
						    pcie_perf_stats_desc64, i);

	अगर (MLX5_CAP_MCAM_FEATURE((priv)->mdev, pcie_outbound_stalled))
		क्रम (i = 0; i < NUM_PCIE_PERF_STALL_COUNTERS; i++)
			data[idx++] =
				MLX5E_READ_CTR32_BE(&priv->stats.pcie.pcie_perf_counters,
						    pcie_perf_stall_stats_desc, i);
	वापस idx;
पूर्ण

अटल MLX5E_DECLARE_STATS_GRP_OP_UPDATE_STATS(pcie)
अणु
	काष्ठा mlx5e_pcie_stats *pcie_stats = &priv->stats.pcie;
	काष्ठा mlx5_core_dev *mdev = priv->mdev;
	u32 in[MLX5_ST_SZ_DW(mpcnt_reg)] = अणु0पूर्ण;
	पूर्णांक sz = MLX5_ST_SZ_BYTES(mpcnt_reg);
	व्योम *out;

	अगर (!MLX5_CAP_MCAM_FEATURE(mdev, pcie_perक्रमmance_group))
		वापस;

	out = pcie_stats->pcie_perf_counters;
	MLX5_SET(mpcnt_reg, in, grp, MLX5_PCIE_PERFORMANCE_COUNTERS_GROUP);
	mlx5_core_access_reg(mdev, in, sz, out, sz, MLX5_REG_MPCNT, 0, 0);
पूर्ण

#घोषणा PPORT_PER_TC_PRIO_OFF(c) \
	MLX5_BYTE_OFF(ppcnt_reg, \
		      counter_set.eth_per_tc_prio_grp_data_layout.c##_high)

अटल स्थिर काष्ठा counter_desc pport_per_tc_prio_stats_desc[] = अणु
	अणु "rx_prio%d_buf_discard", PPORT_PER_TC_PRIO_OFF(no_buffer_discard_uc) पूर्ण,
पूर्ण;

#घोषणा NUM_PPORT_PER_TC_PRIO_COUNTERS	ARRAY_SIZE(pport_per_tc_prio_stats_desc)

#घोषणा PPORT_PER_TC_CONGEST_PRIO_OFF(c) \
	MLX5_BYTE_OFF(ppcnt_reg, \
		      counter_set.eth_per_tc_congest_prio_grp_data_layout.c##_high)

अटल स्थिर काष्ठा counter_desc pport_per_tc_congest_prio_stats_desc[] = अणु
	अणु "rx_prio%d_cong_discard", PPORT_PER_TC_CONGEST_PRIO_OFF(wred_discard) पूर्ण,
	अणु "rx_prio%d_marked", PPORT_PER_TC_CONGEST_PRIO_OFF(ecn_marked_tc) पूर्ण,
पूर्ण;

#घोषणा NUM_PPORT_PER_TC_CONGEST_PRIO_COUNTERS \
	ARRAY_SIZE(pport_per_tc_congest_prio_stats_desc)

अटल पूर्णांक mlx5e_grp_per_tc_prio_get_num_stats(काष्ठा mlx5e_priv *priv)
अणु
	काष्ठा mlx5_core_dev *mdev = priv->mdev;

	अगर (!MLX5_CAP_GEN(mdev, sbcam_reg))
		वापस 0;

	वापस NUM_PPORT_PER_TC_PRIO_COUNTERS * NUM_PPORT_PRIO;
पूर्ण

अटल MLX5E_DECLARE_STATS_GRP_OP_FILL_STRS(per_port_buff_congest)
अणु
	काष्ठा mlx5_core_dev *mdev = priv->mdev;
	पूर्णांक i, prio;

	अगर (!MLX5_CAP_GEN(mdev, sbcam_reg))
		वापस idx;

	क्रम (prio = 0; prio < NUM_PPORT_PRIO; prio++) अणु
		क्रम (i = 0; i < NUM_PPORT_PER_TC_PRIO_COUNTERS; i++)
			प्र_लिखो(data + (idx++) * ETH_GSTRING_LEN,
				pport_per_tc_prio_stats_desc[i].क्रमmat, prio);
		क्रम (i = 0; i < NUM_PPORT_PER_TC_CONGEST_PRIO_COUNTERS; i++)
			प्र_लिखो(data + (idx++) * ETH_GSTRING_LEN,
				pport_per_tc_congest_prio_stats_desc[i].क्रमmat, prio);
	पूर्ण

	वापस idx;
पूर्ण

अटल MLX5E_DECLARE_STATS_GRP_OP_FILL_STATS(per_port_buff_congest)
अणु
	काष्ठा mlx5e_pport_stats *pport = &priv->stats.pport;
	काष्ठा mlx5_core_dev *mdev = priv->mdev;
	पूर्णांक i, prio;

	अगर (!MLX5_CAP_GEN(mdev, sbcam_reg))
		वापस idx;

	क्रम (prio = 0; prio < NUM_PPORT_PRIO; prio++) अणु
		क्रम (i = 0; i < NUM_PPORT_PER_TC_PRIO_COUNTERS; i++)
			data[idx++] =
				MLX5E_READ_CTR64_BE(&pport->per_tc_prio_counters[prio],
						    pport_per_tc_prio_stats_desc, i);
		क्रम (i = 0; i < NUM_PPORT_PER_TC_CONGEST_PRIO_COUNTERS ; i++)
			data[idx++] =
				MLX5E_READ_CTR64_BE(&pport->per_tc_congest_prio_counters[prio],
						    pport_per_tc_congest_prio_stats_desc, i);
	पूर्ण

	वापस idx;
पूर्ण

अटल व्योम mlx5e_grp_per_tc_prio_update_stats(काष्ठा mlx5e_priv *priv)
अणु
	काष्ठा mlx5e_pport_stats *pstats = &priv->stats.pport;
	काष्ठा mlx5_core_dev *mdev = priv->mdev;
	u32 in[MLX5_ST_SZ_DW(ppcnt_reg)] = अणुपूर्ण;
	पूर्णांक sz = MLX5_ST_SZ_BYTES(ppcnt_reg);
	व्योम *out;
	पूर्णांक prio;

	अगर (!MLX5_CAP_GEN(mdev, sbcam_reg))
		वापस;

	MLX5_SET(ppcnt_reg, in, pnat, 2);
	MLX5_SET(ppcnt_reg, in, grp, MLX5_PER_TRAFFIC_CLASS_COUNTERS_GROUP);
	क्रम (prio = 0; prio < NUM_PPORT_PRIO; prio++) अणु
		out = pstats->per_tc_prio_counters[prio];
		MLX5_SET(ppcnt_reg, in, prio_tc, prio);
		mlx5_core_access_reg(mdev, in, sz, out, sz, MLX5_REG_PPCNT, 0, 0);
	पूर्ण
पूर्ण

अटल पूर्णांक mlx5e_grp_per_tc_congest_prio_get_num_stats(काष्ठा mlx5e_priv *priv)
अणु
	काष्ठा mlx5_core_dev *mdev = priv->mdev;

	अगर (!MLX5_CAP_GEN(mdev, sbcam_reg))
		वापस 0;

	वापस NUM_PPORT_PER_TC_CONGEST_PRIO_COUNTERS * NUM_PPORT_PRIO;
पूर्ण

अटल व्योम mlx5e_grp_per_tc_congest_prio_update_stats(काष्ठा mlx5e_priv *priv)
अणु
	काष्ठा mlx5e_pport_stats *pstats = &priv->stats.pport;
	काष्ठा mlx5_core_dev *mdev = priv->mdev;
	u32 in[MLX5_ST_SZ_DW(ppcnt_reg)] = अणुपूर्ण;
	पूर्णांक sz = MLX5_ST_SZ_BYTES(ppcnt_reg);
	व्योम *out;
	पूर्णांक prio;

	अगर (!MLX5_CAP_GEN(mdev, sbcam_reg))
		वापस;

	MLX5_SET(ppcnt_reg, in, pnat, 2);
	MLX5_SET(ppcnt_reg, in, grp, MLX5_PER_TRAFFIC_CLASS_CONGESTION_GROUP);
	क्रम (prio = 0; prio < NUM_PPORT_PRIO; prio++) अणु
		out = pstats->per_tc_congest_prio_counters[prio];
		MLX5_SET(ppcnt_reg, in, prio_tc, prio);
		mlx5_core_access_reg(mdev, in, sz, out, sz, MLX5_REG_PPCNT, 0, 0);
	पूर्ण
पूर्ण

अटल MLX5E_DECLARE_STATS_GRP_OP_NUM_STATS(per_port_buff_congest)
अणु
	वापस mlx5e_grp_per_tc_prio_get_num_stats(priv) +
		mlx5e_grp_per_tc_congest_prio_get_num_stats(priv);
पूर्ण

अटल MLX5E_DECLARE_STATS_GRP_OP_UPDATE_STATS(per_port_buff_congest)
अणु
	mlx5e_grp_per_tc_prio_update_stats(priv);
	mlx5e_grp_per_tc_congest_prio_update_stats(priv);
पूर्ण

#घोषणा PPORT_PER_PRIO_OFF(c) \
	MLX5_BYTE_OFF(ppcnt_reg, \
		      counter_set.eth_per_prio_grp_data_layout.c##_high)
अटल स्थिर काष्ठा counter_desc pport_per_prio_traffic_stats_desc[] = अणु
	अणु "rx_prio%d_bytes", PPORT_PER_PRIO_OFF(rx_octets) पूर्ण,
	अणु "rx_prio%d_packets", PPORT_PER_PRIO_OFF(rx_frames) पूर्ण,
	अणु "rx_prio%d_discards", PPORT_PER_PRIO_OFF(rx_discards) पूर्ण,
	अणु "tx_prio%d_bytes", PPORT_PER_PRIO_OFF(tx_octets) पूर्ण,
	अणु "tx_prio%d_packets", PPORT_PER_PRIO_OFF(tx_frames) पूर्ण,
पूर्ण;

#घोषणा NUM_PPORT_PER_PRIO_TRAFFIC_COUNTERS	ARRAY_SIZE(pport_per_prio_traffic_stats_desc)

अटल पूर्णांक mlx5e_grp_per_prio_traffic_get_num_stats(व्योम)
अणु
	वापस NUM_PPORT_PER_PRIO_TRAFFIC_COUNTERS * NUM_PPORT_PRIO;
पूर्ण

अटल पूर्णांक mlx5e_grp_per_prio_traffic_fill_strings(काष्ठा mlx5e_priv *priv,
						   u8 *data,
						   पूर्णांक idx)
अणु
	पूर्णांक i, prio;

	क्रम (prio = 0; prio < NUM_PPORT_PRIO; prio++) अणु
		क्रम (i = 0; i < NUM_PPORT_PER_PRIO_TRAFFIC_COUNTERS; i++)
			प्र_लिखो(data + (idx++) * ETH_GSTRING_LEN,
				pport_per_prio_traffic_stats_desc[i].क्रमmat, prio);
	पूर्ण

	वापस idx;
पूर्ण

अटल पूर्णांक mlx5e_grp_per_prio_traffic_fill_stats(काष्ठा mlx5e_priv *priv,
						 u64 *data,
						 पूर्णांक idx)
अणु
	पूर्णांक i, prio;

	क्रम (prio = 0; prio < NUM_PPORT_PRIO; prio++) अणु
		क्रम (i = 0; i < NUM_PPORT_PER_PRIO_TRAFFIC_COUNTERS; i++)
			data[idx++] =
				MLX5E_READ_CTR64_BE(&priv->stats.pport.per_prio_counters[prio],
						    pport_per_prio_traffic_stats_desc, i);
	पूर्ण

	वापस idx;
पूर्ण

अटल स्थिर काष्ठा counter_desc pport_per_prio_pfc_stats_desc[] = अणु
	/* %s is "global" or "prio{i}" */
	अणु "rx_%s_pause", PPORT_PER_PRIO_OFF(rx_छोड़ो) पूर्ण,
	अणु "rx_%s_pause_duration", PPORT_PER_PRIO_OFF(rx_छोड़ो_duration) पूर्ण,
	अणु "tx_%s_pause", PPORT_PER_PRIO_OFF(tx_छोड़ो) पूर्ण,
	अणु "tx_%s_pause_duration", PPORT_PER_PRIO_OFF(tx_छोड़ो_duration) पूर्ण,
	अणु "rx_%s_pause_transition", PPORT_PER_PRIO_OFF(rx_छोड़ो_transition) पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा counter_desc pport_pfc_stall_stats_desc[] = अणु
	अणु "tx_pause_storm_warning_events", PPORT_PER_PRIO_OFF(device_stall_minor_watermark_cnt) पूर्ण,
	अणु "tx_pause_storm_error_events", PPORT_PER_PRIO_OFF(device_stall_critical_watermark_cnt) पूर्ण,
पूर्ण;

#घोषणा NUM_PPORT_PER_PRIO_PFC_COUNTERS		ARRAY_SIZE(pport_per_prio_pfc_stats_desc)
#घोषणा NUM_PPORT_PFC_STALL_COUNTERS(priv)	(ARRAY_SIZE(pport_pfc_stall_stats_desc) * \
						 MLX5_CAP_PCAM_FEATURE((priv)->mdev, pfcc_mask) * \
						 MLX5_CAP_DEBUG((priv)->mdev, stall_detect))

अटल अचिन्हित दीर्घ mlx5e_query_pfc_combined(काष्ठा mlx5e_priv *priv)
अणु
	काष्ठा mlx5_core_dev *mdev = priv->mdev;
	u8 pfc_en_tx;
	u8 pfc_en_rx;
	पूर्णांक err;

	अगर (MLX5_CAP_GEN(mdev, port_type) != MLX5_CAP_PORT_TYPE_ETH)
		वापस 0;

	err = mlx5_query_port_pfc(mdev, &pfc_en_tx, &pfc_en_rx);

	वापस err ? 0 : pfc_en_tx | pfc_en_rx;
पूर्ण

अटल bool mlx5e_query_global_छोड़ो_combined(काष्ठा mlx5e_priv *priv)
अणु
	काष्ठा mlx5_core_dev *mdev = priv->mdev;
	u32 rx_छोड़ो;
	u32 tx_छोड़ो;
	पूर्णांक err;

	अगर (MLX5_CAP_GEN(mdev, port_type) != MLX5_CAP_PORT_TYPE_ETH)
		वापस false;

	err = mlx5_query_port_छोड़ो(mdev, &rx_छोड़ो, &tx_छोड़ो);

	वापस err ? false : rx_छोड़ो | tx_छोड़ो;
पूर्ण

अटल पूर्णांक mlx5e_grp_per_prio_pfc_get_num_stats(काष्ठा mlx5e_priv *priv)
अणु
	वापस (mlx5e_query_global_छोड़ो_combined(priv) +
		hweight8(mlx5e_query_pfc_combined(priv))) *
		NUM_PPORT_PER_PRIO_PFC_COUNTERS +
		NUM_PPORT_PFC_STALL_COUNTERS(priv);
पूर्ण

अटल पूर्णांक mlx5e_grp_per_prio_pfc_fill_strings(काष्ठा mlx5e_priv *priv,
					       u8 *data,
					       पूर्णांक idx)
अणु
	अचिन्हित दीर्घ pfc_combined;
	पूर्णांक i, prio;

	pfc_combined = mlx5e_query_pfc_combined(priv);
	क्रम_each_set_bit(prio, &pfc_combined, NUM_PPORT_PRIO) अणु
		क्रम (i = 0; i < NUM_PPORT_PER_PRIO_PFC_COUNTERS; i++) अणु
			अक्षर pfc_string[ETH_GSTRING_LEN];

			snम_लिखो(pfc_string, माप(pfc_string), "prio%d", prio);
			प्र_लिखो(data + (idx++) * ETH_GSTRING_LEN,
				pport_per_prio_pfc_stats_desc[i].क्रमmat, pfc_string);
		पूर्ण
	पूर्ण

	अगर (mlx5e_query_global_छोड़ो_combined(priv)) अणु
		क्रम (i = 0; i < NUM_PPORT_PER_PRIO_PFC_COUNTERS; i++) अणु
			प्र_लिखो(data + (idx++) * ETH_GSTRING_LEN,
				pport_per_prio_pfc_stats_desc[i].क्रमmat, "global");
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < NUM_PPORT_PFC_STALL_COUNTERS(priv); i++)
		म_नकल(data + (idx++) * ETH_GSTRING_LEN,
		       pport_pfc_stall_stats_desc[i].क्रमmat);

	वापस idx;
पूर्ण

अटल पूर्णांक mlx5e_grp_per_prio_pfc_fill_stats(काष्ठा mlx5e_priv *priv,
					     u64 *data,
					     पूर्णांक idx)
अणु
	अचिन्हित दीर्घ pfc_combined;
	पूर्णांक i, prio;

	pfc_combined = mlx5e_query_pfc_combined(priv);
	क्रम_each_set_bit(prio, &pfc_combined, NUM_PPORT_PRIO) अणु
		क्रम (i = 0; i < NUM_PPORT_PER_PRIO_PFC_COUNTERS; i++) अणु
			data[idx++] =
				MLX5E_READ_CTR64_BE(&priv->stats.pport.per_prio_counters[prio],
						    pport_per_prio_pfc_stats_desc, i);
		पूर्ण
	पूर्ण

	अगर (mlx5e_query_global_छोड़ो_combined(priv)) अणु
		क्रम (i = 0; i < NUM_PPORT_PER_PRIO_PFC_COUNTERS; i++) अणु
			data[idx++] =
				MLX5E_READ_CTR64_BE(&priv->stats.pport.per_prio_counters[0],
						    pport_per_prio_pfc_stats_desc, i);
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < NUM_PPORT_PFC_STALL_COUNTERS(priv); i++)
		data[idx++] = MLX5E_READ_CTR64_BE(&priv->stats.pport.per_prio_counters[0],
						  pport_pfc_stall_stats_desc, i);

	वापस idx;
पूर्ण

अटल MLX5E_DECLARE_STATS_GRP_OP_NUM_STATS(per_prio)
अणु
	वापस mlx5e_grp_per_prio_traffic_get_num_stats() +
		mlx5e_grp_per_prio_pfc_get_num_stats(priv);
पूर्ण

अटल MLX5E_DECLARE_STATS_GRP_OP_FILL_STRS(per_prio)
अणु
	idx = mlx5e_grp_per_prio_traffic_fill_strings(priv, data, idx);
	idx = mlx5e_grp_per_prio_pfc_fill_strings(priv, data, idx);
	वापस idx;
पूर्ण

अटल MLX5E_DECLARE_STATS_GRP_OP_FILL_STATS(per_prio)
अणु
	idx = mlx5e_grp_per_prio_traffic_fill_stats(priv, data, idx);
	idx = mlx5e_grp_per_prio_pfc_fill_stats(priv, data, idx);
	वापस idx;
पूर्ण

अटल MLX5E_DECLARE_STATS_GRP_OP_UPDATE_STATS(per_prio)
अणु
	काष्ठा mlx5e_pport_stats *pstats = &priv->stats.pport;
	काष्ठा mlx5_core_dev *mdev = priv->mdev;
	u32 in[MLX5_ST_SZ_DW(ppcnt_reg)] = अणु0पूर्ण;
	पूर्णांक sz = MLX5_ST_SZ_BYTES(ppcnt_reg);
	पूर्णांक prio;
	व्योम *out;

	अगर (!MLX5_BASIC_PPCNT_SUPPORTED(mdev))
		वापस;

	MLX5_SET(ppcnt_reg, in, local_port, 1);
	MLX5_SET(ppcnt_reg, in, grp, MLX5_PER_PRIORITY_COUNTERS_GROUP);
	क्रम (prio = 0; prio < NUM_PPORT_PRIO; prio++) अणु
		out = pstats->per_prio_counters[prio];
		MLX5_SET(ppcnt_reg, in, prio_tc, prio);
		mlx5_core_access_reg(mdev, in, sz, out, sz,
				     MLX5_REG_PPCNT, 0, 0);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा counter_desc mlx5e_pme_status_desc[] = अणु
	अणु "module_unplug",       माप(u64) * MLX5_MODULE_STATUS_UNPLUGGED पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा counter_desc mlx5e_pme_error_desc[] = अणु
	अणु "module_bus_stuck",    माप(u64) * MLX5_MODULE_EVENT_ERROR_BUS_STUCK पूर्ण,
	अणु "module_high_temp",    माप(u64) * MLX5_MODULE_EVENT_ERROR_HIGH_TEMPERATURE पूर्ण,
	अणु "module_bad_shorted",  माप(u64) * MLX5_MODULE_EVENT_ERROR_BAD_CABLE पूर्ण,
पूर्ण;

#घोषणा NUM_PME_STATUS_STATS		ARRAY_SIZE(mlx5e_pme_status_desc)
#घोषणा NUM_PME_ERR_STATS		ARRAY_SIZE(mlx5e_pme_error_desc)

अटल MLX5E_DECLARE_STATS_GRP_OP_NUM_STATS(pme)
अणु
	वापस NUM_PME_STATUS_STATS + NUM_PME_ERR_STATS;
पूर्ण

अटल MLX5E_DECLARE_STATS_GRP_OP_FILL_STRS(pme)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < NUM_PME_STATUS_STATS; i++)
		म_नकल(data + (idx++) * ETH_GSTRING_LEN, mlx5e_pme_status_desc[i].क्रमmat);

	क्रम (i = 0; i < NUM_PME_ERR_STATS; i++)
		म_नकल(data + (idx++) * ETH_GSTRING_LEN, mlx5e_pme_error_desc[i].क्रमmat);

	वापस idx;
पूर्ण

अटल MLX5E_DECLARE_STATS_GRP_OP_FILL_STATS(pme)
अणु
	काष्ठा mlx5_pme_stats pme_stats;
	पूर्णांक i;

	mlx5_get_pme_stats(priv->mdev, &pme_stats);

	क्रम (i = 0; i < NUM_PME_STATUS_STATS; i++)
		data[idx++] = MLX5E_READ_CTR64_CPU(pme_stats.status_counters,
						   mlx5e_pme_status_desc, i);

	क्रम (i = 0; i < NUM_PME_ERR_STATS; i++)
		data[idx++] = MLX5E_READ_CTR64_CPU(pme_stats.error_counters,
						   mlx5e_pme_error_desc, i);

	वापस idx;
पूर्ण

अटल MLX5E_DECLARE_STATS_GRP_OP_UPDATE_STATS(pme) अणु वापस; पूर्ण

अटल MLX5E_DECLARE_STATS_GRP_OP_NUM_STATS(tls)
अणु
	वापस mlx5e_tls_get_count(priv);
पूर्ण

अटल MLX5E_DECLARE_STATS_GRP_OP_FILL_STRS(tls)
अणु
	वापस idx + mlx5e_tls_get_strings(priv, data + idx * ETH_GSTRING_LEN);
पूर्ण

अटल MLX5E_DECLARE_STATS_GRP_OP_FILL_STATS(tls)
अणु
	वापस idx + mlx5e_tls_get_stats(priv, data + idx);
पूर्ण

अटल MLX5E_DECLARE_STATS_GRP_OP_UPDATE_STATS(tls) अणु वापस; पूर्ण

अटल स्थिर काष्ठा counter_desc rq_stats_desc[] = अणु
	अणु MLX5E_DECLARE_RX_STAT(काष्ठा mlx5e_rq_stats, packets) पूर्ण,
	अणु MLX5E_DECLARE_RX_STAT(काष्ठा mlx5e_rq_stats, bytes) पूर्ण,
	अणु MLX5E_DECLARE_RX_STAT(काष्ठा mlx5e_rq_stats, csum_complete) पूर्ण,
	अणु MLX5E_DECLARE_RX_STAT(काष्ठा mlx5e_rq_stats, csum_complete_tail) पूर्ण,
	अणु MLX5E_DECLARE_RX_STAT(काष्ठा mlx5e_rq_stats, csum_complete_tail_slow) पूर्ण,
	अणु MLX5E_DECLARE_RX_STAT(काष्ठा mlx5e_rq_stats, csum_unnecessary) पूर्ण,
	अणु MLX5E_DECLARE_RX_STAT(काष्ठा mlx5e_rq_stats, csum_unnecessary_inner) पूर्ण,
	अणु MLX5E_DECLARE_RX_STAT(काष्ठा mlx5e_rq_stats, csum_none) पूर्ण,
	अणु MLX5E_DECLARE_RX_STAT(काष्ठा mlx5e_rq_stats, xdp_drop) पूर्ण,
	अणु MLX5E_DECLARE_RX_STAT(काष्ठा mlx5e_rq_stats, xdp_redirect) पूर्ण,
	अणु MLX5E_DECLARE_RX_STAT(काष्ठा mlx5e_rq_stats, lro_packets) पूर्ण,
	अणु MLX5E_DECLARE_RX_STAT(काष्ठा mlx5e_rq_stats, lro_bytes) पूर्ण,
	अणु MLX5E_DECLARE_RX_STAT(काष्ठा mlx5e_rq_stats, ecn_mark) पूर्ण,
	अणु MLX5E_DECLARE_RX_STAT(काष्ठा mlx5e_rq_stats, हटाओd_vlan_packets) पूर्ण,
	अणु MLX5E_DECLARE_RX_STAT(काष्ठा mlx5e_rq_stats, wqe_err) पूर्ण,
	अणु MLX5E_DECLARE_RX_STAT(काष्ठा mlx5e_rq_stats, mpwqe_filler_cqes) पूर्ण,
	अणु MLX5E_DECLARE_RX_STAT(काष्ठा mlx5e_rq_stats, mpwqe_filler_strides) पूर्ण,
	अणु MLX5E_DECLARE_RX_STAT(काष्ठा mlx5e_rq_stats, oversize_pkts_sw_drop) पूर्ण,
	अणु MLX5E_DECLARE_RX_STAT(काष्ठा mlx5e_rq_stats, buff_alloc_err) पूर्ण,
	अणु MLX5E_DECLARE_RX_STAT(काष्ठा mlx5e_rq_stats, cqe_compress_blks) पूर्ण,
	अणु MLX5E_DECLARE_RX_STAT(काष्ठा mlx5e_rq_stats, cqe_compress_pkts) पूर्ण,
	अणु MLX5E_DECLARE_RX_STAT(काष्ठा mlx5e_rq_stats, cache_reuse) पूर्ण,
	अणु MLX5E_DECLARE_RX_STAT(काष्ठा mlx5e_rq_stats, cache_full) पूर्ण,
	अणु MLX5E_DECLARE_RX_STAT(काष्ठा mlx5e_rq_stats, cache_empty) पूर्ण,
	अणु MLX5E_DECLARE_RX_STAT(काष्ठा mlx5e_rq_stats, cache_busy) पूर्ण,
	अणु MLX5E_DECLARE_RX_STAT(काष्ठा mlx5e_rq_stats, cache_waive) पूर्ण,
	अणु MLX5E_DECLARE_RX_STAT(काष्ठा mlx5e_rq_stats, congst_umr) पूर्ण,
	अणु MLX5E_DECLARE_RX_STAT(काष्ठा mlx5e_rq_stats, arfs_err) पूर्ण,
	अणु MLX5E_DECLARE_RX_STAT(काष्ठा mlx5e_rq_stats, recover) पूर्ण,
#अगर_घोषित CONFIG_MLX5_EN_TLS
	अणु MLX5E_DECLARE_RX_STAT(काष्ठा mlx5e_rq_stats, tls_decrypted_packets) पूर्ण,
	अणु MLX5E_DECLARE_RX_STAT(काष्ठा mlx5e_rq_stats, tls_decrypted_bytes) पूर्ण,
	अणु MLX5E_DECLARE_RX_STAT(काष्ठा mlx5e_rq_stats, tls_resync_req_pkt) पूर्ण,
	अणु MLX5E_DECLARE_RX_STAT(काष्ठा mlx5e_rq_stats, tls_resync_req_start) पूर्ण,
	अणु MLX5E_DECLARE_RX_STAT(काष्ठा mlx5e_rq_stats, tls_resync_req_end) पूर्ण,
	अणु MLX5E_DECLARE_RX_STAT(काष्ठा mlx5e_rq_stats, tls_resync_req_skip) पूर्ण,
	अणु MLX5E_DECLARE_RX_STAT(काष्ठा mlx5e_rq_stats, tls_resync_res_ok) पूर्ण,
	अणु MLX5E_DECLARE_RX_STAT(काष्ठा mlx5e_rq_stats, tls_resync_res_retry) पूर्ण,
	अणु MLX5E_DECLARE_RX_STAT(काष्ठा mlx5e_rq_stats, tls_resync_res_skip) पूर्ण,
	अणु MLX5E_DECLARE_RX_STAT(काष्ठा mlx5e_rq_stats, tls_err) पूर्ण,
#पूर्ण_अगर
पूर्ण;

अटल स्थिर काष्ठा counter_desc sq_stats_desc[] = अणु
	अणु MLX5E_DECLARE_TX_STAT(काष्ठा mlx5e_sq_stats, packets) पूर्ण,
	अणु MLX5E_DECLARE_TX_STAT(काष्ठा mlx5e_sq_stats, bytes) पूर्ण,
	अणु MLX5E_DECLARE_TX_STAT(काष्ठा mlx5e_sq_stats, tso_packets) पूर्ण,
	अणु MLX5E_DECLARE_TX_STAT(काष्ठा mlx5e_sq_stats, tso_bytes) पूर्ण,
	अणु MLX5E_DECLARE_TX_STAT(काष्ठा mlx5e_sq_stats, tso_inner_packets) पूर्ण,
	अणु MLX5E_DECLARE_TX_STAT(काष्ठा mlx5e_sq_stats, tso_inner_bytes) पूर्ण,
	अणु MLX5E_DECLARE_TX_STAT(काष्ठा mlx5e_sq_stats, csum_partial) पूर्ण,
	अणु MLX5E_DECLARE_TX_STAT(काष्ठा mlx5e_sq_stats, csum_partial_inner) पूर्ण,
	अणु MLX5E_DECLARE_TX_STAT(काष्ठा mlx5e_sq_stats, added_vlan_packets) पूर्ण,
	अणु MLX5E_DECLARE_TX_STAT(काष्ठा mlx5e_sq_stats, nop) पूर्ण,
	अणु MLX5E_DECLARE_TX_STAT(काष्ठा mlx5e_sq_stats, mpwqe_blks) पूर्ण,
	अणु MLX5E_DECLARE_TX_STAT(काष्ठा mlx5e_sq_stats, mpwqe_pkts) पूर्ण,
#अगर_घोषित CONFIG_MLX5_EN_TLS
	अणु MLX5E_DECLARE_TX_STAT(काष्ठा mlx5e_sq_stats, tls_encrypted_packets) पूर्ण,
	अणु MLX5E_DECLARE_TX_STAT(काष्ठा mlx5e_sq_stats, tls_encrypted_bytes) पूर्ण,
	अणु MLX5E_DECLARE_TX_STAT(काष्ठा mlx5e_sq_stats, tls_ooo) पूर्ण,
	अणु MLX5E_DECLARE_TX_STAT(काष्ठा mlx5e_sq_stats, tls_dump_packets) पूर्ण,
	अणु MLX5E_DECLARE_TX_STAT(काष्ठा mlx5e_sq_stats, tls_dump_bytes) पूर्ण,
	अणु MLX5E_DECLARE_TX_STAT(काष्ठा mlx5e_sq_stats, tls_resync_bytes) पूर्ण,
	अणु MLX5E_DECLARE_TX_STAT(काष्ठा mlx5e_sq_stats, tls_skip_no_sync_data) पूर्ण,
	अणु MLX5E_DECLARE_TX_STAT(काष्ठा mlx5e_sq_stats, tls_drop_no_sync_data) पूर्ण,
	अणु MLX5E_DECLARE_TX_STAT(काष्ठा mlx5e_sq_stats, tls_drop_bypass_req) पूर्ण,
#पूर्ण_अगर
	अणु MLX5E_DECLARE_TX_STAT(काष्ठा mlx5e_sq_stats, csum_none) पूर्ण,
	अणु MLX5E_DECLARE_TX_STAT(काष्ठा mlx5e_sq_stats, stopped) पूर्ण,
	अणु MLX5E_DECLARE_TX_STAT(काष्ठा mlx5e_sq_stats, dropped) पूर्ण,
	अणु MLX5E_DECLARE_TX_STAT(काष्ठा mlx5e_sq_stats, xmit_more) पूर्ण,
	अणु MLX5E_DECLARE_TX_STAT(काष्ठा mlx5e_sq_stats, recover) पूर्ण,
	अणु MLX5E_DECLARE_TX_STAT(काष्ठा mlx5e_sq_stats, cqes) पूर्ण,
	अणु MLX5E_DECLARE_TX_STAT(काष्ठा mlx5e_sq_stats, wake) पूर्ण,
	अणु MLX5E_DECLARE_TX_STAT(काष्ठा mlx5e_sq_stats, cqe_err) पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा counter_desc rq_xdpsq_stats_desc[] = अणु
	अणु MLX5E_DECLARE_RQ_XDPSQ_STAT(काष्ठा mlx5e_xdpsq_stats, xmit) पूर्ण,
	अणु MLX5E_DECLARE_RQ_XDPSQ_STAT(काष्ठा mlx5e_xdpsq_stats, mpwqe) पूर्ण,
	अणु MLX5E_DECLARE_RQ_XDPSQ_STAT(काष्ठा mlx5e_xdpsq_stats, inlnw) पूर्ण,
	अणु MLX5E_DECLARE_RQ_XDPSQ_STAT(काष्ठा mlx5e_xdpsq_stats, nops) पूर्ण,
	अणु MLX5E_DECLARE_RQ_XDPSQ_STAT(काष्ठा mlx5e_xdpsq_stats, full) पूर्ण,
	अणु MLX5E_DECLARE_RQ_XDPSQ_STAT(काष्ठा mlx5e_xdpsq_stats, err) पूर्ण,
	अणु MLX5E_DECLARE_RQ_XDPSQ_STAT(काष्ठा mlx5e_xdpsq_stats, cqes) पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा counter_desc xdpsq_stats_desc[] = अणु
	अणु MLX5E_DECLARE_XDPSQ_STAT(काष्ठा mlx5e_xdpsq_stats, xmit) पूर्ण,
	अणु MLX5E_DECLARE_XDPSQ_STAT(काष्ठा mlx5e_xdpsq_stats, mpwqe) पूर्ण,
	अणु MLX5E_DECLARE_XDPSQ_STAT(काष्ठा mlx5e_xdpsq_stats, inlnw) पूर्ण,
	अणु MLX5E_DECLARE_XDPSQ_STAT(काष्ठा mlx5e_xdpsq_stats, nops) पूर्ण,
	अणु MLX5E_DECLARE_XDPSQ_STAT(काष्ठा mlx5e_xdpsq_stats, full) पूर्ण,
	अणु MLX5E_DECLARE_XDPSQ_STAT(काष्ठा mlx5e_xdpsq_stats, err) पूर्ण,
	अणु MLX5E_DECLARE_XDPSQ_STAT(काष्ठा mlx5e_xdpsq_stats, cqes) पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा counter_desc xskrq_stats_desc[] = अणु
	अणु MLX5E_DECLARE_XSKRQ_STAT(काष्ठा mlx5e_rq_stats, packets) पूर्ण,
	अणु MLX5E_DECLARE_XSKRQ_STAT(काष्ठा mlx5e_rq_stats, bytes) पूर्ण,
	अणु MLX5E_DECLARE_XSKRQ_STAT(काष्ठा mlx5e_rq_stats, csum_complete) पूर्ण,
	अणु MLX5E_DECLARE_XSKRQ_STAT(काष्ठा mlx5e_rq_stats, csum_unnecessary) पूर्ण,
	अणु MLX5E_DECLARE_XSKRQ_STAT(काष्ठा mlx5e_rq_stats, csum_unnecessary_inner) पूर्ण,
	अणु MLX5E_DECLARE_XSKRQ_STAT(काष्ठा mlx5e_rq_stats, csum_none) पूर्ण,
	अणु MLX5E_DECLARE_XSKRQ_STAT(काष्ठा mlx5e_rq_stats, ecn_mark) पूर्ण,
	अणु MLX5E_DECLARE_XSKRQ_STAT(काष्ठा mlx5e_rq_stats, हटाओd_vlan_packets) पूर्ण,
	अणु MLX5E_DECLARE_XSKRQ_STAT(काष्ठा mlx5e_rq_stats, xdp_drop) पूर्ण,
	अणु MLX5E_DECLARE_XSKRQ_STAT(काष्ठा mlx5e_rq_stats, xdp_redirect) पूर्ण,
	अणु MLX5E_DECLARE_XSKRQ_STAT(काष्ठा mlx5e_rq_stats, wqe_err) पूर्ण,
	अणु MLX5E_DECLARE_XSKRQ_STAT(काष्ठा mlx5e_rq_stats, mpwqe_filler_cqes) पूर्ण,
	अणु MLX5E_DECLARE_XSKRQ_STAT(काष्ठा mlx5e_rq_stats, mpwqe_filler_strides) पूर्ण,
	अणु MLX5E_DECLARE_XSKRQ_STAT(काष्ठा mlx5e_rq_stats, oversize_pkts_sw_drop) पूर्ण,
	अणु MLX5E_DECLARE_XSKRQ_STAT(काष्ठा mlx5e_rq_stats, buff_alloc_err) पूर्ण,
	अणु MLX5E_DECLARE_XSKRQ_STAT(काष्ठा mlx5e_rq_stats, cqe_compress_blks) पूर्ण,
	अणु MLX5E_DECLARE_XSKRQ_STAT(काष्ठा mlx5e_rq_stats, cqe_compress_pkts) पूर्ण,
	अणु MLX5E_DECLARE_XSKRQ_STAT(काष्ठा mlx5e_rq_stats, congst_umr) पूर्ण,
	अणु MLX5E_DECLARE_XSKRQ_STAT(काष्ठा mlx5e_rq_stats, arfs_err) पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा counter_desc xsksq_stats_desc[] = अणु
	अणु MLX5E_DECLARE_XSKSQ_STAT(काष्ठा mlx5e_xdpsq_stats, xmit) पूर्ण,
	अणु MLX5E_DECLARE_XSKSQ_STAT(काष्ठा mlx5e_xdpsq_stats, mpwqe) पूर्ण,
	अणु MLX5E_DECLARE_XSKSQ_STAT(काष्ठा mlx5e_xdpsq_stats, inlnw) पूर्ण,
	अणु MLX5E_DECLARE_XSKSQ_STAT(काष्ठा mlx5e_xdpsq_stats, full) पूर्ण,
	अणु MLX5E_DECLARE_XSKSQ_STAT(काष्ठा mlx5e_xdpsq_stats, err) पूर्ण,
	अणु MLX5E_DECLARE_XSKSQ_STAT(काष्ठा mlx5e_xdpsq_stats, cqes) पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा counter_desc ch_stats_desc[] = अणु
	अणु MLX5E_DECLARE_CH_STAT(काष्ठा mlx5e_ch_stats, events) पूर्ण,
	अणु MLX5E_DECLARE_CH_STAT(काष्ठा mlx5e_ch_stats, poll) पूर्ण,
	अणु MLX5E_DECLARE_CH_STAT(काष्ठा mlx5e_ch_stats, arm) पूर्ण,
	अणु MLX5E_DECLARE_CH_STAT(काष्ठा mlx5e_ch_stats, aff_change) पूर्ण,
	अणु MLX5E_DECLARE_CH_STAT(काष्ठा mlx5e_ch_stats, क्रमce_irq) पूर्ण,
	अणु MLX5E_DECLARE_CH_STAT(काष्ठा mlx5e_ch_stats, eq_rearm) पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा counter_desc ptp_sq_stats_desc[] = अणु
	अणु MLX5E_DECLARE_PTP_TX_STAT(काष्ठा mlx5e_sq_stats, packets) पूर्ण,
	अणु MLX5E_DECLARE_PTP_TX_STAT(काष्ठा mlx5e_sq_stats, bytes) पूर्ण,
	अणु MLX5E_DECLARE_PTP_TX_STAT(काष्ठा mlx5e_sq_stats, csum_partial) पूर्ण,
	अणु MLX5E_DECLARE_PTP_TX_STAT(काष्ठा mlx5e_sq_stats, csum_partial_inner) पूर्ण,
	अणु MLX5E_DECLARE_PTP_TX_STAT(काष्ठा mlx5e_sq_stats, added_vlan_packets) पूर्ण,
	अणु MLX5E_DECLARE_PTP_TX_STAT(काष्ठा mlx5e_sq_stats, nop) पूर्ण,
	अणु MLX5E_DECLARE_PTP_TX_STAT(काष्ठा mlx5e_sq_stats, csum_none) पूर्ण,
	अणु MLX5E_DECLARE_PTP_TX_STAT(काष्ठा mlx5e_sq_stats, stopped) पूर्ण,
	अणु MLX5E_DECLARE_PTP_TX_STAT(काष्ठा mlx5e_sq_stats, dropped) पूर्ण,
	अणु MLX5E_DECLARE_PTP_TX_STAT(काष्ठा mlx5e_sq_stats, xmit_more) पूर्ण,
	अणु MLX5E_DECLARE_PTP_TX_STAT(काष्ठा mlx5e_sq_stats, recover) पूर्ण,
	अणु MLX5E_DECLARE_PTP_TX_STAT(काष्ठा mlx5e_sq_stats, cqes) पूर्ण,
	अणु MLX5E_DECLARE_PTP_TX_STAT(काष्ठा mlx5e_sq_stats, wake) पूर्ण,
	अणु MLX5E_DECLARE_PTP_TX_STAT(काष्ठा mlx5e_sq_stats, cqe_err) पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा counter_desc ptp_ch_stats_desc[] = अणु
	अणु MLX5E_DECLARE_PTP_CH_STAT(काष्ठा mlx5e_ch_stats, events) पूर्ण,
	अणु MLX5E_DECLARE_PTP_CH_STAT(काष्ठा mlx5e_ch_stats, poll) पूर्ण,
	अणु MLX5E_DECLARE_PTP_CH_STAT(काष्ठा mlx5e_ch_stats, arm) पूर्ण,
	अणु MLX5E_DECLARE_PTP_CH_STAT(काष्ठा mlx5e_ch_stats, eq_rearm) पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा counter_desc ptp_cq_stats_desc[] = अणु
	अणु MLX5E_DECLARE_PTP_CQ_STAT(काष्ठा mlx5e_ptp_cq_stats, cqe) पूर्ण,
	अणु MLX5E_DECLARE_PTP_CQ_STAT(काष्ठा mlx5e_ptp_cq_stats, err_cqe) पूर्ण,
	अणु MLX5E_DECLARE_PTP_CQ_STAT(काष्ठा mlx5e_ptp_cq_stats, पात) पूर्ण,
	अणु MLX5E_DECLARE_PTP_CQ_STAT(काष्ठा mlx5e_ptp_cq_stats, पात_असल_dअगरf_ns) पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा counter_desc ptp_rq_stats_desc[] = अणु
	अणु MLX5E_DECLARE_PTP_RQ_STAT(काष्ठा mlx5e_rq_stats, packets) पूर्ण,
	अणु MLX5E_DECLARE_PTP_RQ_STAT(काष्ठा mlx5e_rq_stats, bytes) पूर्ण,
	अणु MLX5E_DECLARE_PTP_RQ_STAT(काष्ठा mlx5e_rq_stats, csum_complete) पूर्ण,
	अणु MLX5E_DECLARE_PTP_RQ_STAT(काष्ठा mlx5e_rq_stats, csum_complete_tail) पूर्ण,
	अणु MLX5E_DECLARE_PTP_RQ_STAT(काष्ठा mlx5e_rq_stats, csum_complete_tail_slow) पूर्ण,
	अणु MLX5E_DECLARE_PTP_RQ_STAT(काष्ठा mlx5e_rq_stats, csum_unnecessary) पूर्ण,
	अणु MLX5E_DECLARE_PTP_RQ_STAT(काष्ठा mlx5e_rq_stats, csum_unnecessary_inner) पूर्ण,
	अणु MLX5E_DECLARE_PTP_RQ_STAT(काष्ठा mlx5e_rq_stats, csum_none) पूर्ण,
	अणु MLX5E_DECLARE_PTP_RQ_STAT(काष्ठा mlx5e_rq_stats, xdp_drop) पूर्ण,
	अणु MLX5E_DECLARE_PTP_RQ_STAT(काष्ठा mlx5e_rq_stats, xdp_redirect) पूर्ण,
	अणु MLX5E_DECLARE_PTP_RQ_STAT(काष्ठा mlx5e_rq_stats, lro_packets) पूर्ण,
	अणु MLX5E_DECLARE_PTP_RQ_STAT(काष्ठा mlx5e_rq_stats, lro_bytes) पूर्ण,
	अणु MLX5E_DECLARE_PTP_RQ_STAT(काष्ठा mlx5e_rq_stats, ecn_mark) पूर्ण,
	अणु MLX5E_DECLARE_PTP_RQ_STAT(काष्ठा mlx5e_rq_stats, हटाओd_vlan_packets) पूर्ण,
	अणु MLX5E_DECLARE_PTP_RQ_STAT(काष्ठा mlx5e_rq_stats, wqe_err) पूर्ण,
	अणु MLX5E_DECLARE_PTP_RQ_STAT(काष्ठा mlx5e_rq_stats, mpwqe_filler_cqes) पूर्ण,
	अणु MLX5E_DECLARE_PTP_RQ_STAT(काष्ठा mlx5e_rq_stats, mpwqe_filler_strides) पूर्ण,
	अणु MLX5E_DECLARE_PTP_RQ_STAT(काष्ठा mlx5e_rq_stats, oversize_pkts_sw_drop) पूर्ण,
	अणु MLX5E_DECLARE_PTP_RQ_STAT(काष्ठा mlx5e_rq_stats, buff_alloc_err) पूर्ण,
	अणु MLX5E_DECLARE_PTP_RQ_STAT(काष्ठा mlx5e_rq_stats, cqe_compress_blks) पूर्ण,
	अणु MLX5E_DECLARE_PTP_RQ_STAT(काष्ठा mlx5e_rq_stats, cqe_compress_pkts) पूर्ण,
	अणु MLX5E_DECLARE_PTP_RQ_STAT(काष्ठा mlx5e_rq_stats, cache_reuse) पूर्ण,
	अणु MLX5E_DECLARE_PTP_RQ_STAT(काष्ठा mlx5e_rq_stats, cache_full) पूर्ण,
	अणु MLX5E_DECLARE_PTP_RQ_STAT(काष्ठा mlx5e_rq_stats, cache_empty) पूर्ण,
	अणु MLX5E_DECLARE_PTP_RQ_STAT(काष्ठा mlx5e_rq_stats, cache_busy) पूर्ण,
	अणु MLX5E_DECLARE_PTP_RQ_STAT(काष्ठा mlx5e_rq_stats, cache_waive) पूर्ण,
	अणु MLX5E_DECLARE_PTP_RQ_STAT(काष्ठा mlx5e_rq_stats, congst_umr) पूर्ण,
	अणु MLX5E_DECLARE_PTP_RQ_STAT(काष्ठा mlx5e_rq_stats, arfs_err) पूर्ण,
	अणु MLX5E_DECLARE_PTP_RQ_STAT(काष्ठा mlx5e_rq_stats, recover) पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा counter_desc qos_sq_stats_desc[] = अणु
	अणु MLX5E_DECLARE_QOS_TX_STAT(काष्ठा mlx5e_sq_stats, packets) पूर्ण,
	अणु MLX5E_DECLARE_QOS_TX_STAT(काष्ठा mlx5e_sq_stats, bytes) पूर्ण,
	अणु MLX5E_DECLARE_QOS_TX_STAT(काष्ठा mlx5e_sq_stats, tso_packets) पूर्ण,
	अणु MLX5E_DECLARE_QOS_TX_STAT(काष्ठा mlx5e_sq_stats, tso_bytes) पूर्ण,
	अणु MLX5E_DECLARE_QOS_TX_STAT(काष्ठा mlx5e_sq_stats, tso_inner_packets) पूर्ण,
	अणु MLX5E_DECLARE_QOS_TX_STAT(काष्ठा mlx5e_sq_stats, tso_inner_bytes) पूर्ण,
	अणु MLX5E_DECLARE_QOS_TX_STAT(काष्ठा mlx5e_sq_stats, csum_partial) पूर्ण,
	अणु MLX5E_DECLARE_QOS_TX_STAT(काष्ठा mlx5e_sq_stats, csum_partial_inner) पूर्ण,
	अणु MLX5E_DECLARE_QOS_TX_STAT(काष्ठा mlx5e_sq_stats, added_vlan_packets) पूर्ण,
	अणु MLX5E_DECLARE_QOS_TX_STAT(काष्ठा mlx5e_sq_stats, nop) पूर्ण,
	अणु MLX5E_DECLARE_QOS_TX_STAT(काष्ठा mlx5e_sq_stats, mpwqe_blks) पूर्ण,
	अणु MLX5E_DECLARE_QOS_TX_STAT(काष्ठा mlx5e_sq_stats, mpwqe_pkts) पूर्ण,
#अगर_घोषित CONFIG_MLX5_EN_TLS
	अणु MLX5E_DECLARE_QOS_TX_STAT(काष्ठा mlx5e_sq_stats, tls_encrypted_packets) पूर्ण,
	अणु MLX5E_DECLARE_QOS_TX_STAT(काष्ठा mlx5e_sq_stats, tls_encrypted_bytes) पूर्ण,
	अणु MLX5E_DECLARE_QOS_TX_STAT(काष्ठा mlx5e_sq_stats, tls_ooo) पूर्ण,
	अणु MLX5E_DECLARE_QOS_TX_STAT(काष्ठा mlx5e_sq_stats, tls_dump_packets) पूर्ण,
	अणु MLX5E_DECLARE_QOS_TX_STAT(काष्ठा mlx5e_sq_stats, tls_dump_bytes) पूर्ण,
	अणु MLX5E_DECLARE_QOS_TX_STAT(काष्ठा mlx5e_sq_stats, tls_resync_bytes) पूर्ण,
	अणु MLX5E_DECLARE_QOS_TX_STAT(काष्ठा mlx5e_sq_stats, tls_skip_no_sync_data) पूर्ण,
	अणु MLX5E_DECLARE_QOS_TX_STAT(काष्ठा mlx5e_sq_stats, tls_drop_no_sync_data) पूर्ण,
	अणु MLX5E_DECLARE_QOS_TX_STAT(काष्ठा mlx5e_sq_stats, tls_drop_bypass_req) पूर्ण,
#पूर्ण_अगर
	अणु MLX5E_DECLARE_QOS_TX_STAT(काष्ठा mlx5e_sq_stats, csum_none) पूर्ण,
	अणु MLX5E_DECLARE_QOS_TX_STAT(काष्ठा mlx5e_sq_stats, stopped) पूर्ण,
	अणु MLX5E_DECLARE_QOS_TX_STAT(काष्ठा mlx5e_sq_stats, dropped) पूर्ण,
	अणु MLX5E_DECLARE_QOS_TX_STAT(काष्ठा mlx5e_sq_stats, xmit_more) पूर्ण,
	अणु MLX5E_DECLARE_QOS_TX_STAT(काष्ठा mlx5e_sq_stats, recover) पूर्ण,
	अणु MLX5E_DECLARE_QOS_TX_STAT(काष्ठा mlx5e_sq_stats, cqes) पूर्ण,
	अणु MLX5E_DECLARE_QOS_TX_STAT(काष्ठा mlx5e_sq_stats, wake) पूर्ण,
	अणु MLX5E_DECLARE_QOS_TX_STAT(काष्ठा mlx5e_sq_stats, cqe_err) पूर्ण,
पूर्ण;

#घोषणा NUM_RQ_STATS			ARRAY_SIZE(rq_stats_desc)
#घोषणा NUM_SQ_STATS			ARRAY_SIZE(sq_stats_desc)
#घोषणा NUM_XDPSQ_STATS			ARRAY_SIZE(xdpsq_stats_desc)
#घोषणा NUM_RQ_XDPSQ_STATS		ARRAY_SIZE(rq_xdpsq_stats_desc)
#घोषणा NUM_XSKRQ_STATS			ARRAY_SIZE(xskrq_stats_desc)
#घोषणा NUM_XSKSQ_STATS			ARRAY_SIZE(xsksq_stats_desc)
#घोषणा NUM_CH_STATS			ARRAY_SIZE(ch_stats_desc)
#घोषणा NUM_PTP_SQ_STATS		ARRAY_SIZE(ptp_sq_stats_desc)
#घोषणा NUM_PTP_CH_STATS		ARRAY_SIZE(ptp_ch_stats_desc)
#घोषणा NUM_PTP_CQ_STATS		ARRAY_SIZE(ptp_cq_stats_desc)
#घोषणा NUM_PTP_RQ_STATS                ARRAY_SIZE(ptp_rq_stats_desc)
#घोषणा NUM_QOS_SQ_STATS		ARRAY_SIZE(qos_sq_stats_desc)

अटल MLX5E_DECLARE_STATS_GRP_OP_NUM_STATS(qos)
अणु
	/* Pairs with smp_store_release in mlx5e_खोलो_qos_sq. */
	वापस NUM_QOS_SQ_STATS * smp_load_acquire(&priv->htb.max_qos_sqs);
पूर्ण

अटल MLX5E_DECLARE_STATS_GRP_OP_FILL_STRS(qos)
अणु
	/* Pairs with smp_store_release in mlx5e_खोलो_qos_sq. */
	u16 max_qos_sqs = smp_load_acquire(&priv->htb.max_qos_sqs);
	पूर्णांक i, qid;

	क्रम (qid = 0; qid < max_qos_sqs; qid++)
		क्रम (i = 0; i < NUM_QOS_SQ_STATS; i++)
			प्र_लिखो(data + (idx++) * ETH_GSTRING_LEN,
				qos_sq_stats_desc[i].क्रमmat, qid);

	वापस idx;
पूर्ण

अटल MLX5E_DECLARE_STATS_GRP_OP_FILL_STATS(qos)
अणु
	काष्ठा mlx5e_sq_stats **stats;
	u16 max_qos_sqs;
	पूर्णांक i, qid;

	/* Pairs with smp_store_release in mlx5e_खोलो_qos_sq. */
	max_qos_sqs = smp_load_acquire(&priv->htb.max_qos_sqs);
	stats = READ_ONCE(priv->htb.qos_sq_stats);

	क्रम (qid = 0; qid < max_qos_sqs; qid++) अणु
		काष्ठा mlx5e_sq_stats *s = READ_ONCE(stats[qid]);

		क्रम (i = 0; i < NUM_QOS_SQ_STATS; i++)
			data[idx++] = MLX5E_READ_CTR64_CPU(s, qos_sq_stats_desc, i);
	पूर्ण

	वापस idx;
पूर्ण

अटल MLX5E_DECLARE_STATS_GRP_OP_UPDATE_STATS(qos) अणु वापस; पूर्ण

अटल MLX5E_DECLARE_STATS_GRP_OP_NUM_STATS(ptp)
अणु
	पूर्णांक num = NUM_PTP_CH_STATS;

	अगर (!priv->tx_ptp_खोलोed && !priv->rx_ptp_खोलोed)
		वापस 0;

	अगर (priv->tx_ptp_खोलोed)
		num += (NUM_PTP_SQ_STATS + NUM_PTP_CQ_STATS) * priv->max_खोलोed_tc;
	अगर (priv->rx_ptp_खोलोed)
		num += NUM_PTP_RQ_STATS;

	वापस num;
पूर्ण

अटल MLX5E_DECLARE_STATS_GRP_OP_FILL_STRS(ptp)
अणु
	पूर्णांक i, tc;

	अगर (!priv->tx_ptp_खोलोed && !priv->rx_ptp_खोलोed)
		वापस idx;

	क्रम (i = 0; i < NUM_PTP_CH_STATS; i++)
		प्र_लिखो(data + (idx++) * ETH_GSTRING_LEN,
			ptp_ch_stats_desc[i].क्रमmat);

	अगर (priv->tx_ptp_खोलोed) अणु
		क्रम (tc = 0; tc < priv->max_खोलोed_tc; tc++)
			क्रम (i = 0; i < NUM_PTP_SQ_STATS; i++)
				प्र_लिखो(data + (idx++) * ETH_GSTRING_LEN,
					ptp_sq_stats_desc[i].क्रमmat, tc);

		क्रम (tc = 0; tc < priv->max_खोलोed_tc; tc++)
			क्रम (i = 0; i < NUM_PTP_CQ_STATS; i++)
				प्र_लिखो(data + (idx++) * ETH_GSTRING_LEN,
					ptp_cq_stats_desc[i].क्रमmat, tc);
	पूर्ण
	अगर (priv->rx_ptp_खोलोed) अणु
		क्रम (i = 0; i < NUM_PTP_RQ_STATS; i++)
			प्र_लिखो(data + (idx++) * ETH_GSTRING_LEN,
				ptp_rq_stats_desc[i].क्रमmat);
	पूर्ण
	वापस idx;
पूर्ण

अटल MLX5E_DECLARE_STATS_GRP_OP_FILL_STATS(ptp)
अणु
	पूर्णांक i, tc;

	अगर (!priv->tx_ptp_खोलोed && !priv->rx_ptp_खोलोed)
		वापस idx;

	क्रम (i = 0; i < NUM_PTP_CH_STATS; i++)
		data[idx++] =
			MLX5E_READ_CTR64_CPU(&priv->ptp_stats.ch,
					     ptp_ch_stats_desc, i);

	अगर (priv->tx_ptp_खोलोed) अणु
		क्रम (tc = 0; tc < priv->max_खोलोed_tc; tc++)
			क्रम (i = 0; i < NUM_PTP_SQ_STATS; i++)
				data[idx++] =
					MLX5E_READ_CTR64_CPU(&priv->ptp_stats.sq[tc],
							     ptp_sq_stats_desc, i);

		क्रम (tc = 0; tc < priv->max_खोलोed_tc; tc++)
			क्रम (i = 0; i < NUM_PTP_CQ_STATS; i++)
				data[idx++] =
					MLX5E_READ_CTR64_CPU(&priv->ptp_stats.cq[tc],
							     ptp_cq_stats_desc, i);
	पूर्ण
	अगर (priv->rx_ptp_खोलोed) अणु
		क्रम (i = 0; i < NUM_PTP_RQ_STATS; i++)
			data[idx++] =
				MLX5E_READ_CTR64_CPU(&priv->ptp_stats.rq,
						     ptp_rq_stats_desc, i);
	पूर्ण
	वापस idx;
पूर्ण

अटल MLX5E_DECLARE_STATS_GRP_OP_UPDATE_STATS(ptp) अणु वापस; पूर्ण

अटल MLX5E_DECLARE_STATS_GRP_OP_NUM_STATS(channels)
अणु
	पूर्णांक max_nch = priv->max_nch;

	वापस (NUM_RQ_STATS * max_nch) +
	       (NUM_CH_STATS * max_nch) +
	       (NUM_SQ_STATS * max_nch * priv->max_खोलोed_tc) +
	       (NUM_RQ_XDPSQ_STATS * max_nch) +
	       (NUM_XDPSQ_STATS * max_nch) +
	       (NUM_XSKRQ_STATS * max_nch * priv->xsk.ever_used) +
	       (NUM_XSKSQ_STATS * max_nch * priv->xsk.ever_used);
पूर्ण

अटल MLX5E_DECLARE_STATS_GRP_OP_FILL_STRS(channels)
अणु
	bool is_xsk = priv->xsk.ever_used;
	पूर्णांक max_nch = priv->max_nch;
	पूर्णांक i, j, tc;

	क्रम (i = 0; i < max_nch; i++)
		क्रम (j = 0; j < NUM_CH_STATS; j++)
			प्र_लिखो(data + (idx++) * ETH_GSTRING_LEN,
				ch_stats_desc[j].क्रमmat, i);

	क्रम (i = 0; i < max_nch; i++) अणु
		क्रम (j = 0; j < NUM_RQ_STATS; j++)
			प्र_लिखो(data + (idx++) * ETH_GSTRING_LEN,
				rq_stats_desc[j].क्रमmat, i);
		क्रम (j = 0; j < NUM_XSKRQ_STATS * is_xsk; j++)
			प्र_लिखो(data + (idx++) * ETH_GSTRING_LEN,
				xskrq_stats_desc[j].क्रमmat, i);
		क्रम (j = 0; j < NUM_RQ_XDPSQ_STATS; j++)
			प्र_लिखो(data + (idx++) * ETH_GSTRING_LEN,
				rq_xdpsq_stats_desc[j].क्रमmat, i);
	पूर्ण

	क्रम (tc = 0; tc < priv->max_खोलोed_tc; tc++)
		क्रम (i = 0; i < max_nch; i++)
			क्रम (j = 0; j < NUM_SQ_STATS; j++)
				प्र_लिखो(data + (idx++) * ETH_GSTRING_LEN,
					sq_stats_desc[j].क्रमmat,
					i + tc * max_nch);

	क्रम (i = 0; i < max_nch; i++) अणु
		क्रम (j = 0; j < NUM_XSKSQ_STATS * is_xsk; j++)
			प्र_लिखो(data + (idx++) * ETH_GSTRING_LEN,
				xsksq_stats_desc[j].क्रमmat, i);
		क्रम (j = 0; j < NUM_XDPSQ_STATS; j++)
			प्र_लिखो(data + (idx++) * ETH_GSTRING_LEN,
				xdpsq_stats_desc[j].क्रमmat, i);
	पूर्ण

	वापस idx;
पूर्ण

अटल MLX5E_DECLARE_STATS_GRP_OP_FILL_STATS(channels)
अणु
	bool is_xsk = priv->xsk.ever_used;
	पूर्णांक max_nch = priv->max_nch;
	पूर्णांक i, j, tc;

	क्रम (i = 0; i < max_nch; i++)
		क्रम (j = 0; j < NUM_CH_STATS; j++)
			data[idx++] =
				MLX5E_READ_CTR64_CPU(&priv->channel_stats[i].ch,
						     ch_stats_desc, j);

	क्रम (i = 0; i < max_nch; i++) अणु
		क्रम (j = 0; j < NUM_RQ_STATS; j++)
			data[idx++] =
				MLX5E_READ_CTR64_CPU(&priv->channel_stats[i].rq,
						     rq_stats_desc, j);
		क्रम (j = 0; j < NUM_XSKRQ_STATS * is_xsk; j++)
			data[idx++] =
				MLX5E_READ_CTR64_CPU(&priv->channel_stats[i].xskrq,
						     xskrq_stats_desc, j);
		क्रम (j = 0; j < NUM_RQ_XDPSQ_STATS; j++)
			data[idx++] =
				MLX5E_READ_CTR64_CPU(&priv->channel_stats[i].rq_xdpsq,
						     rq_xdpsq_stats_desc, j);
	पूर्ण

	क्रम (tc = 0; tc < priv->max_खोलोed_tc; tc++)
		क्रम (i = 0; i < max_nch; i++)
			क्रम (j = 0; j < NUM_SQ_STATS; j++)
				data[idx++] =
					MLX5E_READ_CTR64_CPU(&priv->channel_stats[i].sq[tc],
							     sq_stats_desc, j);

	क्रम (i = 0; i < max_nch; i++) अणु
		क्रम (j = 0; j < NUM_XSKSQ_STATS * is_xsk; j++)
			data[idx++] =
				MLX5E_READ_CTR64_CPU(&priv->channel_stats[i].xsksq,
						     xsksq_stats_desc, j);
		क्रम (j = 0; j < NUM_XDPSQ_STATS; j++)
			data[idx++] =
				MLX5E_READ_CTR64_CPU(&priv->channel_stats[i].xdpsq,
						     xdpsq_stats_desc, j);
	पूर्ण

	वापस idx;
पूर्ण

अटल MLX5E_DECLARE_STATS_GRP_OP_UPDATE_STATS(channels) अणु वापस; पूर्ण

MLX5E_DEFINE_STATS_GRP(sw, 0);
MLX5E_DEFINE_STATS_GRP(qcnt, MLX5E_NDO_UPDATE_STATS);
MLX5E_DEFINE_STATS_GRP(vnic_env, 0);
MLX5E_DEFINE_STATS_GRP(vport, MLX5E_NDO_UPDATE_STATS);
MLX5E_DEFINE_STATS_GRP(802_3, MLX5E_NDO_UPDATE_STATS);
MLX5E_DEFINE_STATS_GRP(2863, 0);
MLX5E_DEFINE_STATS_GRP(2819, 0);
MLX5E_DEFINE_STATS_GRP(phy, 0);
MLX5E_DEFINE_STATS_GRP(pcie, 0);
MLX5E_DEFINE_STATS_GRP(per_prio, 0);
MLX5E_DEFINE_STATS_GRP(pme, 0);
MLX5E_DEFINE_STATS_GRP(channels, 0);
MLX5E_DEFINE_STATS_GRP(per_port_buff_congest, 0);
MLX5E_DEFINE_STATS_GRP(eth_ext, 0);
अटल MLX5E_DEFINE_STATS_GRP(tls, 0);
अटल MLX5E_DEFINE_STATS_GRP(ptp, 0);
अटल MLX5E_DEFINE_STATS_GRP(qos, 0);

/* The stats groups order is opposite to the update_stats() order calls */
mlx5e_stats_grp_t mlx5e_nic_stats_grps[] = अणु
	&MLX5E_STATS_GRP(sw),
	&MLX5E_STATS_GRP(qcnt),
	&MLX5E_STATS_GRP(vnic_env),
	&MLX5E_STATS_GRP(vport),
	&MLX5E_STATS_GRP(802_3),
	&MLX5E_STATS_GRP(2863),
	&MLX5E_STATS_GRP(2819),
	&MLX5E_STATS_GRP(phy),
	&MLX5E_STATS_GRP(eth_ext),
	&MLX5E_STATS_GRP(pcie),
	&MLX5E_STATS_GRP(per_prio),
	&MLX5E_STATS_GRP(pme),
#अगर_घोषित CONFIG_MLX5_EN_IPSEC
	&MLX5E_STATS_GRP(ipsec_sw),
	&MLX5E_STATS_GRP(ipsec_hw),
#पूर्ण_अगर
	&MLX5E_STATS_GRP(tls),
	&MLX5E_STATS_GRP(channels),
	&MLX5E_STATS_GRP(per_port_buff_congest),
	&MLX5E_STATS_GRP(ptp),
	&MLX5E_STATS_GRP(qos),
पूर्ण;

अचिन्हित पूर्णांक mlx5e_nic_stats_grps_num(काष्ठा mlx5e_priv *priv)
अणु
	वापस ARRAY_SIZE(mlx5e_nic_stats_grps);
पूर्ण
