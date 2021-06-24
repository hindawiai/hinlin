<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Atlantic Network Driver
 * Copyright (C) 2020 Marvell International Ltd.
 */

#समावेश "aq_macsec.h"
#समावेश "aq_nic.h"
#समावेश <linux/rtnetlink.h>

#समावेश "macsec/macsec_api.h"
#घोषणा AQ_MACSEC_KEY_LEN_128_BIT 16
#घोषणा AQ_MACSEC_KEY_LEN_192_BIT 24
#घोषणा AQ_MACSEC_KEY_LEN_256_BIT 32

क्रमागत aq_clear_type अणु
	/* update HW configuration */
	AQ_CLEAR_HW = BIT(0),
	/* update SW configuration (busy bits, poपूर्णांकers) */
	AQ_CLEAR_SW = BIT(1),
	/* update both HW and SW configuration */
	AQ_CLEAR_ALL = AQ_CLEAR_HW | AQ_CLEAR_SW,
पूर्ण;

अटल पूर्णांक aq_clear_txsc(काष्ठा aq_nic_s *nic, स्थिर पूर्णांक txsc_idx,
			 क्रमागत aq_clear_type clear_type);
अटल पूर्णांक aq_clear_txsa(काष्ठा aq_nic_s *nic, काष्ठा aq_macsec_txsc *aq_txsc,
			 स्थिर पूर्णांक sa_num, क्रमागत aq_clear_type clear_type);
अटल पूर्णांक aq_clear_rxsc(काष्ठा aq_nic_s *nic, स्थिर पूर्णांक rxsc_idx,
			 क्रमागत aq_clear_type clear_type);
अटल पूर्णांक aq_clear_rxsa(काष्ठा aq_nic_s *nic, काष्ठा aq_macsec_rxsc *aq_rxsc,
			 स्थिर पूर्णांक sa_num, क्रमागत aq_clear_type clear_type);
अटल पूर्णांक aq_clear_secy(काष्ठा aq_nic_s *nic, स्थिर काष्ठा macsec_secy *secy,
			 क्रमागत aq_clear_type clear_type);
अटल पूर्णांक aq_apply_macsec_cfg(काष्ठा aq_nic_s *nic);
अटल पूर्णांक aq_apply_secy_cfg(काष्ठा aq_nic_s *nic,
			     स्थिर काष्ठा macsec_secy *secy);

अटल व्योम aq_ether_addr_to_mac(u32 mac[2], अचिन्हित अक्षर *emac)
अणु
	u32 पंचांगp[2] = अणु 0 पूर्ण;

	स_नकल(((u8 *)पंचांगp) + 2, emac, ETH_ALEN);

	mac[0] = swab32(पंचांगp[1]);
	mac[1] = swab32(पंचांगp[0]);
पूर्ण

/* There's a 1:1 mapping between SecY and TX SC */
अटल पूर्णांक aq_get_txsc_idx_from_secy(काष्ठा aq_macsec_cfg *macsec_cfg,
				     स्थिर काष्ठा macsec_secy *secy)
अणु
	पूर्णांक i;

	अगर (unlikely(!secy))
		वापस -1;

	क्रम (i = 0; i < AQ_MACSEC_MAX_SC; i++) अणु
		अगर (macsec_cfg->aq_txsc[i].sw_secy == secy)
			वापस i;
	पूर्ण
	वापस -1;
पूर्ण

अटल पूर्णांक aq_get_rxsc_idx_from_rxsc(काष्ठा aq_macsec_cfg *macsec_cfg,
				     स्थिर काष्ठा macsec_rx_sc *rxsc)
अणु
	पूर्णांक i;

	अगर (unlikely(!rxsc))
		वापस -1;

	क्रम (i = 0; i < AQ_MACSEC_MAX_SC; i++) अणु
		अगर (macsec_cfg->aq_rxsc[i].sw_rxsc == rxsc)
			वापस i;
	पूर्ण

	वापस -1;
पूर्ण

अटल पूर्णांक aq_get_txsc_idx_from_sc_idx(स्थिर क्रमागत aq_macsec_sc_sa sc_sa,
				       स्थिर पूर्णांक sc_idx)
अणु
	चयन (sc_sa) अणु
	हाल aq_macsec_sa_sc_4sa_8sc:
		वापस sc_idx >> 2;
	हाल aq_macsec_sa_sc_2sa_16sc:
		वापस sc_idx >> 1;
	हाल aq_macsec_sa_sc_1sa_32sc:
		वापस sc_idx;
	शेष:
		WARN_ONCE(true, "Invalid sc_sa");
	पूर्ण
	वापस -1;
पूर्ण

/* Rotate keys u32[8] */
अटल व्योम aq_rotate_keys(u32 (*key)[8], स्थिर पूर्णांक key_len)
अणु
	u32 पंचांगp[8] = अणु 0 पूर्ण;

	स_नकल(&पंचांगp, key, माप(पंचांगp));
	स_रखो(*key, 0, माप(*key));

	अगर (key_len == AQ_MACSEC_KEY_LEN_128_BIT) अणु
		(*key)[0] = swab32(पंचांगp[3]);
		(*key)[1] = swab32(पंचांगp[2]);
		(*key)[2] = swab32(पंचांगp[1]);
		(*key)[3] = swab32(पंचांगp[0]);
	पूर्ण अन्यथा अगर (key_len == AQ_MACSEC_KEY_LEN_192_BIT) अणु
		(*key)[0] = swab32(पंचांगp[5]);
		(*key)[1] = swab32(पंचांगp[4]);
		(*key)[2] = swab32(पंचांगp[3]);
		(*key)[3] = swab32(पंचांगp[2]);
		(*key)[4] = swab32(पंचांगp[1]);
		(*key)[5] = swab32(पंचांगp[0]);
	पूर्ण अन्यथा अगर (key_len == AQ_MACSEC_KEY_LEN_256_BIT) अणु
		(*key)[0] = swab32(पंचांगp[7]);
		(*key)[1] = swab32(पंचांगp[6]);
		(*key)[2] = swab32(पंचांगp[5]);
		(*key)[3] = swab32(पंचांगp[4]);
		(*key)[4] = swab32(पंचांगp[3]);
		(*key)[5] = swab32(पंचांगp[2]);
		(*key)[6] = swab32(पंचांगp[1]);
		(*key)[7] = swab32(पंचांगp[0]);
	पूर्ण अन्यथा अणु
		pr_warn("Rotate_keys: invalid key_len\n");
	पूर्ण
पूर्ण

#घोषणा STATS_2x32_TO_64(stat_field)                                           \
	(((u64)stat_field[1] << 32) | stat_field[0])

अटल पूर्णांक aq_get_macsec_common_stats(काष्ठा aq_hw_s *hw,
				      काष्ठा aq_macsec_common_stats *stats)
अणु
	काष्ठा aq_mss_ingress_common_counters ingress_counters;
	काष्ठा aq_mss_egress_common_counters egress_counters;
	पूर्णांक ret;

	/* MACSEC counters */
	ret = aq_mss_get_ingress_common_counters(hw, &ingress_counters);
	अगर (unlikely(ret))
		वापस ret;

	stats->in.ctl_pkts = STATS_2x32_TO_64(ingress_counters.ctl_pkts);
	stats->in.tagged_miss_pkts =
		STATS_2x32_TO_64(ingress_counters.tagged_miss_pkts);
	stats->in.untagged_miss_pkts =
		STATS_2x32_TO_64(ingress_counters.untagged_miss_pkts);
	stats->in.notag_pkts = STATS_2x32_TO_64(ingress_counters.notag_pkts);
	stats->in.untagged_pkts =
		STATS_2x32_TO_64(ingress_counters.untagged_pkts);
	stats->in.bad_tag_pkts =
		STATS_2x32_TO_64(ingress_counters.bad_tag_pkts);
	stats->in.no_sci_pkts = STATS_2x32_TO_64(ingress_counters.no_sci_pkts);
	stats->in.unknown_sci_pkts =
		STATS_2x32_TO_64(ingress_counters.unknown_sci_pkts);
	stats->in.ctrl_prt_pass_pkts =
		STATS_2x32_TO_64(ingress_counters.ctrl_prt_pass_pkts);
	stats->in.unctrl_prt_pass_pkts =
		STATS_2x32_TO_64(ingress_counters.unctrl_prt_pass_pkts);
	stats->in.ctrl_prt_fail_pkts =
		STATS_2x32_TO_64(ingress_counters.ctrl_prt_fail_pkts);
	stats->in.unctrl_prt_fail_pkts =
		STATS_2x32_TO_64(ingress_counters.unctrl_prt_fail_pkts);
	stats->in.too_दीर्घ_pkts =
		STATS_2x32_TO_64(ingress_counters.too_दीर्घ_pkts);
	stats->in.igpoc_ctl_pkts =
		STATS_2x32_TO_64(ingress_counters.igpoc_ctl_pkts);
	stats->in.ecc_error_pkts =
		STATS_2x32_TO_64(ingress_counters.ecc_error_pkts);
	stats->in.unctrl_hit_drop_redir =
		STATS_2x32_TO_64(ingress_counters.unctrl_hit_drop_redir);

	ret = aq_mss_get_egress_common_counters(hw, &egress_counters);
	अगर (unlikely(ret))
		वापस ret;
	stats->out.ctl_pkts = STATS_2x32_TO_64(egress_counters.ctl_pkt);
	stats->out.unknown_sa_pkts =
		STATS_2x32_TO_64(egress_counters.unknown_sa_pkts);
	stats->out.untagged_pkts =
		STATS_2x32_TO_64(egress_counters.untagged_pkts);
	stats->out.too_दीर्घ = STATS_2x32_TO_64(egress_counters.too_दीर्घ);
	stats->out.ecc_error_pkts =
		STATS_2x32_TO_64(egress_counters.ecc_error_pkts);
	stats->out.unctrl_hit_drop_redir =
		STATS_2x32_TO_64(egress_counters.unctrl_hit_drop_redir);

	वापस 0;
पूर्ण

अटल पूर्णांक aq_get_rxsa_stats(काष्ठा aq_hw_s *hw, स्थिर पूर्णांक sa_idx,
			     काष्ठा aq_macsec_rx_sa_stats *stats)
अणु
	काष्ठा aq_mss_ingress_sa_counters i_sa_counters;
	पूर्णांक ret;

	ret = aq_mss_get_ingress_sa_counters(hw, &i_sa_counters, sa_idx);
	अगर (unlikely(ret))
		वापस ret;

	stats->untagged_hit_pkts =
		STATS_2x32_TO_64(i_sa_counters.untagged_hit_pkts);
	stats->ctrl_hit_drop_redir_pkts =
		STATS_2x32_TO_64(i_sa_counters.ctrl_hit_drop_redir_pkts);
	stats->not_using_sa = STATS_2x32_TO_64(i_sa_counters.not_using_sa);
	stats->unused_sa = STATS_2x32_TO_64(i_sa_counters.unused_sa);
	stats->not_valid_pkts = STATS_2x32_TO_64(i_sa_counters.not_valid_pkts);
	stats->invalid_pkts = STATS_2x32_TO_64(i_sa_counters.invalid_pkts);
	stats->ok_pkts = STATS_2x32_TO_64(i_sa_counters.ok_pkts);
	stats->late_pkts = STATS_2x32_TO_64(i_sa_counters.late_pkts);
	stats->delayed_pkts = STATS_2x32_TO_64(i_sa_counters.delayed_pkts);
	stats->unchecked_pkts = STATS_2x32_TO_64(i_sa_counters.unchecked_pkts);
	stats->validated_octets =
		STATS_2x32_TO_64(i_sa_counters.validated_octets);
	stats->decrypted_octets =
		STATS_2x32_TO_64(i_sa_counters.decrypted_octets);

	वापस 0;
पूर्ण

अटल पूर्णांक aq_get_txsa_stats(काष्ठा aq_hw_s *hw, स्थिर पूर्णांक sa_idx,
			     काष्ठा aq_macsec_tx_sa_stats *stats)
अणु
	काष्ठा aq_mss_egress_sa_counters e_sa_counters;
	पूर्णांक ret;

	ret = aq_mss_get_egress_sa_counters(hw, &e_sa_counters, sa_idx);
	अगर (unlikely(ret))
		वापस ret;

	stats->sa_hit_drop_redirect =
		STATS_2x32_TO_64(e_sa_counters.sa_hit_drop_redirect);
	stats->sa_रक्षित2_pkts =
		STATS_2x32_TO_64(e_sa_counters.sa_रक्षित2_pkts);
	stats->sa_रक्षित_pkts =
		STATS_2x32_TO_64(e_sa_counters.sa_रक्षित_pkts);
	stats->sa_encrypted_pkts =
		STATS_2x32_TO_64(e_sa_counters.sa_encrypted_pkts);

	वापस 0;
पूर्ण

अटल पूर्णांक aq_get_txsa_next_pn(काष्ठा aq_hw_s *hw, स्थिर पूर्णांक sa_idx, u32 *pn)
अणु
	काष्ठा aq_mss_egress_sa_record sa_rec;
	पूर्णांक ret;

	ret = aq_mss_get_egress_sa_record(hw, &sa_rec, sa_idx);
	अगर (likely(!ret))
		*pn = sa_rec.next_pn;

	वापस ret;
पूर्ण

अटल पूर्णांक aq_get_rxsa_next_pn(काष्ठा aq_hw_s *hw, स्थिर पूर्णांक sa_idx, u32 *pn)
अणु
	काष्ठा aq_mss_ingress_sa_record sa_rec;
	पूर्णांक ret;

	ret = aq_mss_get_ingress_sa_record(hw, &sa_rec, sa_idx);
	अगर (likely(!ret))
		*pn = (!sa_rec.sat_nextpn) ? sa_rec.next_pn : 0;

	वापस ret;
पूर्ण

अटल पूर्णांक aq_get_txsc_stats(काष्ठा aq_hw_s *hw, स्थिर पूर्णांक sc_idx,
			     काष्ठा aq_macsec_tx_sc_stats *stats)
अणु
	काष्ठा aq_mss_egress_sc_counters e_sc_counters;
	पूर्णांक ret;

	ret = aq_mss_get_egress_sc_counters(hw, &e_sc_counters, sc_idx);
	अगर (unlikely(ret))
		वापस ret;

	stats->sc_रक्षित_pkts =
		STATS_2x32_TO_64(e_sc_counters.sc_रक्षित_pkts);
	stats->sc_encrypted_pkts =
		STATS_2x32_TO_64(e_sc_counters.sc_encrypted_pkts);
	stats->sc_रक्षित_octets =
		STATS_2x32_TO_64(e_sc_counters.sc_रक्षित_octets);
	stats->sc_encrypted_octets =
		STATS_2x32_TO_64(e_sc_counters.sc_encrypted_octets);

	वापस 0;
पूर्ण

अटल पूर्णांक aq_mकरो_dev_खोलो(काष्ठा macsec_context *ctx)
अणु
	काष्ठा aq_nic_s *nic = netdev_priv(ctx->netdev);
	पूर्णांक ret = 0;

	अगर (ctx->prepare)
		वापस 0;

	अगर (netअगर_carrier_ok(nic->ndev))
		ret = aq_apply_secy_cfg(nic, ctx->secy);

	वापस ret;
पूर्ण

अटल पूर्णांक aq_mकरो_dev_stop(काष्ठा macsec_context *ctx)
अणु
	काष्ठा aq_nic_s *nic = netdev_priv(ctx->netdev);
	पूर्णांक i;

	अगर (ctx->prepare)
		वापस 0;

	क्रम (i = 0; i < AQ_MACSEC_MAX_SC; i++) अणु
		अगर (nic->macsec_cfg->txsc_idx_busy & BIT(i))
			aq_clear_secy(nic, nic->macsec_cfg->aq_txsc[i].sw_secy,
				      AQ_CLEAR_HW);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक aq_set_txsc(काष्ठा aq_nic_s *nic, स्थिर पूर्णांक txsc_idx)
अणु
	काष्ठा aq_macsec_txsc *aq_txsc = &nic->macsec_cfg->aq_txsc[txsc_idx];
	काष्ठा aq_mss_egress_class_record tx_class_rec = अणु 0 पूर्ण;
	स्थिर काष्ठा macsec_secy *secy = aq_txsc->sw_secy;
	काष्ठा aq_mss_egress_sc_record sc_rec = अणु 0 पूर्ण;
	अचिन्हित पूर्णांक sc_idx = aq_txsc->hw_sc_idx;
	काष्ठा aq_hw_s *hw = nic->aq_hw;
	पूर्णांक ret = 0;

	aq_ether_addr_to_mac(tx_class_rec.mac_sa, secy->netdev->dev_addr);

	put_unaligned_be64((__क्रमce u64)secy->sci, tx_class_rec.sci);
	tx_class_rec.sci_mask = 0;

	tx_class_rec.sa_mask = 0x3f;

	tx_class_rec.action = 0; /* क्रमward to SA/SC table */
	tx_class_rec.valid = 1;

	tx_class_rec.sc_idx = sc_idx;

	tx_class_rec.sc_sa = nic->macsec_cfg->sc_sa;

	ret = aq_mss_set_egress_class_record(hw, &tx_class_rec, txsc_idx);
	अगर (ret)
		वापस ret;

	sc_rec.protect = secy->protect_frames;
	अगर (secy->tx_sc.encrypt)
		sc_rec.tci |= BIT(1);
	अगर (secy->tx_sc.scb)
		sc_rec.tci |= BIT(2);
	अगर (secy->tx_sc.send_sci)
		sc_rec.tci |= BIT(3);
	अगर (secy->tx_sc.end_station)
		sc_rec.tci |= BIT(4);
	/* The C bit is clear अगर and only अगर the Secure Data is
	 * exactly the same as the User Data and the ICV is 16 octets दीर्घ.
	 */
	अगर (!(secy->icv_len == 16 && !secy->tx_sc.encrypt))
		sc_rec.tci |= BIT(0);

	sc_rec.an_roll = 0;

	चयन (secy->key_len) अणु
	हाल AQ_MACSEC_KEY_LEN_128_BIT:
		sc_rec.sak_len = 0;
		अवरोध;
	हाल AQ_MACSEC_KEY_LEN_192_BIT:
		sc_rec.sak_len = 1;
		अवरोध;
	हाल AQ_MACSEC_KEY_LEN_256_BIT:
		sc_rec.sak_len = 2;
		अवरोध;
	शेष:
		WARN_ONCE(true, "Invalid sc_sa");
		वापस -EINVAL;
	पूर्ण

	sc_rec.curr_an = secy->tx_sc.encoding_sa;
	sc_rec.valid = 1;
	sc_rec.fresh = 1;

	वापस aq_mss_set_egress_sc_record(hw, &sc_rec, sc_idx);
पूर्ण

अटल u32 aq_sc_idx_max(स्थिर क्रमागत aq_macsec_sc_sa sc_sa)
अणु
	u32 result = 0;

	चयन (sc_sa) अणु
	हाल aq_macsec_sa_sc_4sa_8sc:
		result = 8;
		अवरोध;
	हाल aq_macsec_sa_sc_2sa_16sc:
		result = 16;
		अवरोध;
	हाल aq_macsec_sa_sc_1sa_32sc:
		result = 32;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस result;
पूर्ण

अटल u32 aq_to_hw_sc_idx(स्थिर u32 sc_idx, स्थिर क्रमागत aq_macsec_sc_sa sc_sa)
अणु
	चयन (sc_sa) अणु
	हाल aq_macsec_sa_sc_4sa_8sc:
		वापस sc_idx << 2;
	हाल aq_macsec_sa_sc_2sa_16sc:
		वापस sc_idx << 1;
	हाल aq_macsec_sa_sc_1sa_32sc:
		वापस sc_idx;
	शेष:
		WARN_ONCE(true, "Invalid sc_sa");
	पूर्ण

	वापस sc_idx;
पूर्ण

अटल क्रमागत aq_macsec_sc_sa sc_sa_from_num_an(स्थिर पूर्णांक num_an)
अणु
	क्रमागत aq_macsec_sc_sa sc_sa = aq_macsec_sa_sc_not_used;

	चयन (num_an) अणु
	हाल 4:
		sc_sa = aq_macsec_sa_sc_4sa_8sc;
		अवरोध;
	हाल 2:
		sc_sa = aq_macsec_sa_sc_2sa_16sc;
		अवरोध;
	हाल 1:
		sc_sa = aq_macsec_sa_sc_1sa_32sc;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस sc_sa;
पूर्ण

अटल पूर्णांक aq_mकरो_add_secy(काष्ठा macsec_context *ctx)
अणु
	काष्ठा aq_nic_s *nic = netdev_priv(ctx->netdev);
	काष्ठा aq_macsec_cfg *cfg = nic->macsec_cfg;
	स्थिर काष्ठा macsec_secy *secy = ctx->secy;
	क्रमागत aq_macsec_sc_sa sc_sa;
	u32 txsc_idx;
	पूर्णांक ret = 0;

	अगर (secy->xpn)
		वापस -EOPNOTSUPP;

	sc_sa = sc_sa_from_num_an(MACSEC_NUM_AN);
	अगर (sc_sa == aq_macsec_sa_sc_not_used)
		वापस -EINVAL;

	अगर (hweight32(cfg->txsc_idx_busy) >= aq_sc_idx_max(sc_sa))
		वापस -ENOSPC;

	txsc_idx = ffz(cfg->txsc_idx_busy);
	अगर (txsc_idx == AQ_MACSEC_MAX_SC)
		वापस -ENOSPC;

	अगर (ctx->prepare)
		वापस 0;

	cfg->sc_sa = sc_sa;
	cfg->aq_txsc[txsc_idx].hw_sc_idx = aq_to_hw_sc_idx(txsc_idx, sc_sa);
	cfg->aq_txsc[txsc_idx].sw_secy = secy;

	अगर (netअगर_carrier_ok(nic->ndev) && netअगर_running(secy->netdev))
		ret = aq_set_txsc(nic, txsc_idx);

	set_bit(txsc_idx, &cfg->txsc_idx_busy);

	वापस ret;
पूर्ण

अटल पूर्णांक aq_mकरो_upd_secy(काष्ठा macsec_context *ctx)
अणु
	काष्ठा aq_nic_s *nic = netdev_priv(ctx->netdev);
	स्थिर काष्ठा macsec_secy *secy = ctx->secy;
	पूर्णांक txsc_idx;
	पूर्णांक ret = 0;

	txsc_idx = aq_get_txsc_idx_from_secy(nic->macsec_cfg, secy);
	अगर (txsc_idx < 0)
		वापस -ENOENT;

	अगर (ctx->prepare)
		वापस 0;

	अगर (netअगर_carrier_ok(nic->ndev) && netअगर_running(secy->netdev))
		ret = aq_set_txsc(nic, txsc_idx);

	वापस ret;
पूर्ण

अटल पूर्णांक aq_clear_txsc(काष्ठा aq_nic_s *nic, स्थिर पूर्णांक txsc_idx,
			 क्रमागत aq_clear_type clear_type)
अणु
	काष्ठा aq_macsec_txsc *tx_sc = &nic->macsec_cfg->aq_txsc[txsc_idx];
	काष्ठा aq_mss_egress_class_record tx_class_rec = अणु 0 पूर्ण;
	काष्ठा aq_mss_egress_sc_record sc_rec = अणु 0 पूर्ण;
	काष्ठा aq_hw_s *hw = nic->aq_hw;
	पूर्णांक ret = 0;
	पूर्णांक sa_num;

	क्रम_each_set_bit (sa_num, &tx_sc->tx_sa_idx_busy, AQ_MACSEC_MAX_SA) अणु
		ret = aq_clear_txsa(nic, tx_sc, sa_num, clear_type);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (clear_type & AQ_CLEAR_HW) अणु
		ret = aq_mss_set_egress_class_record(hw, &tx_class_rec,
						     txsc_idx);
		अगर (ret)
			वापस ret;

		sc_rec.fresh = 1;
		ret = aq_mss_set_egress_sc_record(hw, &sc_rec,
						  tx_sc->hw_sc_idx);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (clear_type & AQ_CLEAR_SW) अणु
		clear_bit(txsc_idx, &nic->macsec_cfg->txsc_idx_busy);
		nic->macsec_cfg->aq_txsc[txsc_idx].sw_secy = शून्य;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक aq_mकरो_del_secy(काष्ठा macsec_context *ctx)
अणु
	काष्ठा aq_nic_s *nic = netdev_priv(ctx->netdev);
	पूर्णांक ret = 0;

	अगर (ctx->prepare)
		वापस 0;

	अगर (!nic->macsec_cfg)
		वापस 0;

	ret = aq_clear_secy(nic, ctx->secy, AQ_CLEAR_ALL);

	वापस ret;
पूर्ण

अटल पूर्णांक aq_update_txsa(काष्ठा aq_nic_s *nic, स्थिर अचिन्हित पूर्णांक sc_idx,
			  स्थिर काष्ठा macsec_secy *secy,
			  स्थिर काष्ठा macsec_tx_sa *tx_sa,
			  स्थिर अचिन्हित अक्षर *key, स्थिर अचिन्हित अक्षर an)
अणु
	स्थिर u32 next_pn = tx_sa->next_pn_halves.lower;
	काष्ठा aq_mss_egress_sakey_record key_rec;
	स्थिर अचिन्हित पूर्णांक sa_idx = sc_idx | an;
	काष्ठा aq_mss_egress_sa_record sa_rec;
	काष्ठा aq_hw_s *hw = nic->aq_hw;
	पूर्णांक ret = 0;

	स_रखो(&sa_rec, 0, माप(sa_rec));
	sa_rec.valid = tx_sa->active;
	sa_rec.fresh = 1;
	sa_rec.next_pn = next_pn;

	ret = aq_mss_set_egress_sa_record(hw, &sa_rec, sa_idx);
	अगर (ret)
		वापस ret;

	अगर (!key)
		वापस ret;

	स_रखो(&key_rec, 0, माप(key_rec));
	स_नकल(&key_rec.key, key, secy->key_len);

	aq_rotate_keys(&key_rec.key, secy->key_len);

	ret = aq_mss_set_egress_sakey_record(hw, &key_rec, sa_idx);

	वापस ret;
पूर्ण

अटल पूर्णांक aq_mकरो_add_txsa(काष्ठा macsec_context *ctx)
अणु
	काष्ठा aq_nic_s *nic = netdev_priv(ctx->netdev);
	काष्ठा aq_macsec_cfg *cfg = nic->macsec_cfg;
	स्थिर काष्ठा macsec_secy *secy = ctx->secy;
	काष्ठा aq_macsec_txsc *aq_txsc;
	पूर्णांक txsc_idx;
	पूर्णांक ret = 0;

	txsc_idx = aq_get_txsc_idx_from_secy(cfg, secy);
	अगर (txsc_idx < 0)
		वापस -EINVAL;

	अगर (ctx->prepare)
		वापस 0;

	aq_txsc = &cfg->aq_txsc[txsc_idx];
	set_bit(ctx->sa.assoc_num, &aq_txsc->tx_sa_idx_busy);

	स_नकल(aq_txsc->tx_sa_key[ctx->sa.assoc_num], ctx->sa.key,
	       secy->key_len);

	अगर (netअगर_carrier_ok(nic->ndev) && netअगर_running(secy->netdev))
		ret = aq_update_txsa(nic, aq_txsc->hw_sc_idx, secy,
				     ctx->sa.tx_sa, ctx->sa.key,
				     ctx->sa.assoc_num);

	वापस ret;
पूर्ण

अटल पूर्णांक aq_mकरो_upd_txsa(काष्ठा macsec_context *ctx)
अणु
	काष्ठा aq_nic_s *nic = netdev_priv(ctx->netdev);
	काष्ठा aq_macsec_cfg *cfg = nic->macsec_cfg;
	स्थिर काष्ठा macsec_secy *secy = ctx->secy;
	काष्ठा aq_macsec_txsc *aq_txsc;
	पूर्णांक txsc_idx;
	पूर्णांक ret = 0;

	txsc_idx = aq_get_txsc_idx_from_secy(cfg, secy);
	अगर (txsc_idx < 0)
		वापस -EINVAL;

	अगर (ctx->prepare)
		वापस 0;

	aq_txsc = &cfg->aq_txsc[txsc_idx];
	अगर (netअगर_carrier_ok(nic->ndev) && netअगर_running(secy->netdev))
		ret = aq_update_txsa(nic, aq_txsc->hw_sc_idx, secy,
				     ctx->sa.tx_sa, शून्य, ctx->sa.assoc_num);

	वापस ret;
पूर्ण

अटल पूर्णांक aq_clear_txsa(काष्ठा aq_nic_s *nic, काष्ठा aq_macsec_txsc *aq_txsc,
			 स्थिर पूर्णांक sa_num, क्रमागत aq_clear_type clear_type)
अणु
	स्थिर पूर्णांक sa_idx = aq_txsc->hw_sc_idx | sa_num;
	काष्ठा aq_hw_s *hw = nic->aq_hw;
	पूर्णांक ret = 0;

	अगर (clear_type & AQ_CLEAR_SW)
		clear_bit(sa_num, &aq_txsc->tx_sa_idx_busy);

	अगर ((clear_type & AQ_CLEAR_HW) && netअगर_carrier_ok(nic->ndev)) अणु
		काष्ठा aq_mss_egress_sakey_record key_rec;
		काष्ठा aq_mss_egress_sa_record sa_rec;

		स_रखो(&sa_rec, 0, माप(sa_rec));
		sa_rec.fresh = 1;

		ret = aq_mss_set_egress_sa_record(hw, &sa_rec, sa_idx);
		अगर (ret)
			वापस ret;

		स_रखो(&key_rec, 0, माप(key_rec));
		वापस aq_mss_set_egress_sakey_record(hw, &key_rec, sa_idx);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक aq_mकरो_del_txsa(काष्ठा macsec_context *ctx)
अणु
	काष्ठा aq_nic_s *nic = netdev_priv(ctx->netdev);
	काष्ठा aq_macsec_cfg *cfg = nic->macsec_cfg;
	पूर्णांक txsc_idx;
	पूर्णांक ret = 0;

	txsc_idx = aq_get_txsc_idx_from_secy(cfg, ctx->secy);
	अगर (txsc_idx < 0)
		वापस -EINVAL;

	अगर (ctx->prepare)
		वापस 0;

	ret = aq_clear_txsa(nic, &cfg->aq_txsc[txsc_idx], ctx->sa.assoc_num,
			    AQ_CLEAR_ALL);

	वापस ret;
पूर्ण

अटल पूर्णांक aq_rxsc_validate_frames(स्थिर क्रमागत macsec_validation_type validate)
अणु
	चयन (validate) अणु
	हाल MACSEC_VALIDATE_DISABLED:
		वापस 2;
	हाल MACSEC_VALIDATE_CHECK:
		वापस 1;
	हाल MACSEC_VALIDATE_STRICT:
		वापस 0;
	शेष:
		WARN_ONCE(true, "Invalid validation type");
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक aq_set_rxsc(काष्ठा aq_nic_s *nic, स्थिर u32 rxsc_idx)
अणु
	स्थिर काष्ठा aq_macsec_rxsc *aq_rxsc =
		&nic->macsec_cfg->aq_rxsc[rxsc_idx];
	काष्ठा aq_mss_ingress_preclass_record pre_class_record;
	स्थिर काष्ठा macsec_rx_sc *rx_sc = aq_rxsc->sw_rxsc;
	स्थिर काष्ठा macsec_secy *secy = aq_rxsc->sw_secy;
	स्थिर u32 hw_sc_idx = aq_rxsc->hw_sc_idx;
	काष्ठा aq_mss_ingress_sc_record sc_record;
	काष्ठा aq_hw_s *hw = nic->aq_hw;
	पूर्णांक ret = 0;

	स_रखो(&pre_class_record, 0, माप(pre_class_record));
	put_unaligned_be64((__क्रमce u64)rx_sc->sci, pre_class_record.sci);
	pre_class_record.sci_mask = 0xff;
	/* match all MACSEC ethertype packets */
	pre_class_record.eth_type = ETH_P_MACSEC;
	pre_class_record.eth_type_mask = 0x3;

	aq_ether_addr_to_mac(pre_class_record.mac_sa, (अक्षर *)&rx_sc->sci);
	pre_class_record.sa_mask = 0x3f;

	pre_class_record.an_mask = nic->macsec_cfg->sc_sa;
	pre_class_record.sc_idx = hw_sc_idx;
	/* strip SecTAG & क्रमward क्रम decryption */
	pre_class_record.action = 0x0;
	pre_class_record.valid = 1;

	ret = aq_mss_set_ingress_preclass_record(hw, &pre_class_record,
						 2 * rxsc_idx + 1);
	अगर (ret)
		वापस ret;

	/* If SCI is असलent, then match by SA alone */
	pre_class_record.sci_mask = 0;
	pre_class_record.sci_from_table = 1;

	ret = aq_mss_set_ingress_preclass_record(hw, &pre_class_record,
						 2 * rxsc_idx);
	अगर (ret)
		वापस ret;

	स_रखो(&sc_record, 0, माप(sc_record));
	sc_record.validate_frames =
		aq_rxsc_validate_frames(secy->validate_frames);
	अगर (secy->replay_protect) अणु
		sc_record.replay_protect = 1;
		sc_record.anti_replay_winकरोw = secy->replay_winकरोw;
	पूर्ण
	sc_record.valid = 1;
	sc_record.fresh = 1;

	ret = aq_mss_set_ingress_sc_record(hw, &sc_record, hw_sc_idx);
	अगर (ret)
		वापस ret;

	वापस ret;
पूर्ण

अटल पूर्णांक aq_mकरो_add_rxsc(काष्ठा macsec_context *ctx)
अणु
	काष्ठा aq_nic_s *nic = netdev_priv(ctx->netdev);
	काष्ठा aq_macsec_cfg *cfg = nic->macsec_cfg;
	स्थिर u32 rxsc_idx_max = aq_sc_idx_max(cfg->sc_sa);
	u32 rxsc_idx;
	पूर्णांक ret = 0;

	अगर (hweight32(cfg->rxsc_idx_busy) >= rxsc_idx_max)
		वापस -ENOSPC;

	rxsc_idx = ffz(cfg->rxsc_idx_busy);
	अगर (rxsc_idx >= rxsc_idx_max)
		वापस -ENOSPC;

	अगर (ctx->prepare)
		वापस 0;

	cfg->aq_rxsc[rxsc_idx].hw_sc_idx = aq_to_hw_sc_idx(rxsc_idx,
							   cfg->sc_sa);
	cfg->aq_rxsc[rxsc_idx].sw_secy = ctx->secy;
	cfg->aq_rxsc[rxsc_idx].sw_rxsc = ctx->rx_sc;

	अगर (netअगर_carrier_ok(nic->ndev) && netअगर_running(ctx->secy->netdev))
		ret = aq_set_rxsc(nic, rxsc_idx);

	अगर (ret < 0)
		वापस ret;

	set_bit(rxsc_idx, &cfg->rxsc_idx_busy);

	वापस 0;
पूर्ण

अटल पूर्णांक aq_mकरो_upd_rxsc(काष्ठा macsec_context *ctx)
अणु
	काष्ठा aq_nic_s *nic = netdev_priv(ctx->netdev);
	पूर्णांक rxsc_idx;
	पूर्णांक ret = 0;

	rxsc_idx = aq_get_rxsc_idx_from_rxsc(nic->macsec_cfg, ctx->rx_sc);
	अगर (rxsc_idx < 0)
		वापस -ENOENT;

	अगर (ctx->prepare)
		वापस 0;

	अगर (netअगर_carrier_ok(nic->ndev) && netअगर_running(ctx->secy->netdev))
		ret = aq_set_rxsc(nic, rxsc_idx);

	वापस ret;
पूर्ण

अटल पूर्णांक aq_clear_rxsc(काष्ठा aq_nic_s *nic, स्थिर पूर्णांक rxsc_idx,
			 क्रमागत aq_clear_type clear_type)
अणु
	काष्ठा aq_macsec_rxsc *rx_sc = &nic->macsec_cfg->aq_rxsc[rxsc_idx];
	काष्ठा aq_hw_s *hw = nic->aq_hw;
	पूर्णांक ret = 0;
	पूर्णांक sa_num;

	क्रम_each_set_bit (sa_num, &rx_sc->rx_sa_idx_busy, AQ_MACSEC_MAX_SA) अणु
		ret = aq_clear_rxsa(nic, rx_sc, sa_num, clear_type);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (clear_type & AQ_CLEAR_HW) अणु
		काष्ठा aq_mss_ingress_preclass_record pre_class_record;
		काष्ठा aq_mss_ingress_sc_record sc_record;

		स_रखो(&pre_class_record, 0, माप(pre_class_record));
		स_रखो(&sc_record, 0, माप(sc_record));

		ret = aq_mss_set_ingress_preclass_record(hw, &pre_class_record,
							 2 * rxsc_idx);
		अगर (ret)
			वापस ret;

		ret = aq_mss_set_ingress_preclass_record(hw, &pre_class_record,
							 2 * rxsc_idx + 1);
		अगर (ret)
			वापस ret;

		sc_record.fresh = 1;
		ret = aq_mss_set_ingress_sc_record(hw, &sc_record,
						   rx_sc->hw_sc_idx);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (clear_type & AQ_CLEAR_SW) अणु
		clear_bit(rxsc_idx, &nic->macsec_cfg->rxsc_idx_busy);
		rx_sc->sw_secy = शून्य;
		rx_sc->sw_rxsc = शून्य;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक aq_mकरो_del_rxsc(काष्ठा macsec_context *ctx)
अणु
	काष्ठा aq_nic_s *nic = netdev_priv(ctx->netdev);
	क्रमागत aq_clear_type clear_type = AQ_CLEAR_SW;
	पूर्णांक rxsc_idx;
	पूर्णांक ret = 0;

	rxsc_idx = aq_get_rxsc_idx_from_rxsc(nic->macsec_cfg, ctx->rx_sc);
	अगर (rxsc_idx < 0)
		वापस -ENOENT;

	अगर (ctx->prepare)
		वापस 0;

	अगर (netअगर_carrier_ok(nic->ndev))
		clear_type = AQ_CLEAR_ALL;

	ret = aq_clear_rxsc(nic, rxsc_idx, clear_type);

	वापस ret;
पूर्ण

अटल पूर्णांक aq_update_rxsa(काष्ठा aq_nic_s *nic, स्थिर अचिन्हित पूर्णांक sc_idx,
			  स्थिर काष्ठा macsec_secy *secy,
			  स्थिर काष्ठा macsec_rx_sa *rx_sa,
			  स्थिर अचिन्हित अक्षर *key, स्थिर अचिन्हित अक्षर an)
अणु
	काष्ठा aq_mss_ingress_sakey_record sa_key_record;
	स्थिर u32 next_pn = rx_sa->next_pn_halves.lower;
	काष्ठा aq_mss_ingress_sa_record sa_record;
	काष्ठा aq_hw_s *hw = nic->aq_hw;
	स्थिर पूर्णांक sa_idx = sc_idx | an;
	पूर्णांक ret = 0;

	स_रखो(&sa_record, 0, माप(sa_record));
	sa_record.valid = rx_sa->active;
	sa_record.fresh = 1;
	sa_record.next_pn = next_pn;

	ret = aq_mss_set_ingress_sa_record(hw, &sa_record, sa_idx);
	अगर (ret)
		वापस ret;

	अगर (!key)
		वापस ret;

	स_रखो(&sa_key_record, 0, माप(sa_key_record));
	स_नकल(&sa_key_record.key, key, secy->key_len);

	चयन (secy->key_len) अणु
	हाल AQ_MACSEC_KEY_LEN_128_BIT:
		sa_key_record.key_len = 0;
		अवरोध;
	हाल AQ_MACSEC_KEY_LEN_192_BIT:
		sa_key_record.key_len = 1;
		अवरोध;
	हाल AQ_MACSEC_KEY_LEN_256_BIT:
		sa_key_record.key_len = 2;
		अवरोध;
	शेष:
		वापस -1;
	पूर्ण

	aq_rotate_keys(&sa_key_record.key, secy->key_len);

	ret = aq_mss_set_ingress_sakey_record(hw, &sa_key_record, sa_idx);

	वापस ret;
पूर्ण

अटल पूर्णांक aq_mकरो_add_rxsa(काष्ठा macsec_context *ctx)
अणु
	स्थिर काष्ठा macsec_rx_sc *rx_sc = ctx->sa.rx_sa->sc;
	काष्ठा aq_nic_s *nic = netdev_priv(ctx->netdev);
	स्थिर काष्ठा macsec_secy *secy = ctx->secy;
	काष्ठा aq_macsec_rxsc *aq_rxsc;
	पूर्णांक rxsc_idx;
	पूर्णांक ret = 0;

	rxsc_idx = aq_get_rxsc_idx_from_rxsc(nic->macsec_cfg, rx_sc);
	अगर (rxsc_idx < 0)
		वापस -EINVAL;

	अगर (ctx->prepare)
		वापस 0;

	aq_rxsc = &nic->macsec_cfg->aq_rxsc[rxsc_idx];
	set_bit(ctx->sa.assoc_num, &aq_rxsc->rx_sa_idx_busy);

	स_नकल(aq_rxsc->rx_sa_key[ctx->sa.assoc_num], ctx->sa.key,
	       secy->key_len);

	अगर (netअगर_carrier_ok(nic->ndev) && netअगर_running(secy->netdev))
		ret = aq_update_rxsa(nic, aq_rxsc->hw_sc_idx, secy,
				     ctx->sa.rx_sa, ctx->sa.key,
				     ctx->sa.assoc_num);

	वापस ret;
पूर्ण

अटल पूर्णांक aq_mकरो_upd_rxsa(काष्ठा macsec_context *ctx)
अणु
	स्थिर काष्ठा macsec_rx_sc *rx_sc = ctx->sa.rx_sa->sc;
	काष्ठा aq_nic_s *nic = netdev_priv(ctx->netdev);
	काष्ठा aq_macsec_cfg *cfg = nic->macsec_cfg;
	स्थिर काष्ठा macsec_secy *secy = ctx->secy;
	पूर्णांक rxsc_idx;
	पूर्णांक ret = 0;

	rxsc_idx = aq_get_rxsc_idx_from_rxsc(cfg, rx_sc);
	अगर (rxsc_idx < 0)
		वापस -EINVAL;

	अगर (ctx->prepare)
		वापस 0;

	अगर (netअगर_carrier_ok(nic->ndev) && netअगर_running(secy->netdev))
		ret = aq_update_rxsa(nic, cfg->aq_rxsc[rxsc_idx].hw_sc_idx,
				     secy, ctx->sa.rx_sa, शून्य,
				     ctx->sa.assoc_num);

	वापस ret;
पूर्ण

अटल पूर्णांक aq_clear_rxsa(काष्ठा aq_nic_s *nic, काष्ठा aq_macsec_rxsc *aq_rxsc,
			 स्थिर पूर्णांक sa_num, क्रमागत aq_clear_type clear_type)
अणु
	पूर्णांक sa_idx = aq_rxsc->hw_sc_idx | sa_num;
	काष्ठा aq_hw_s *hw = nic->aq_hw;
	पूर्णांक ret = 0;

	अगर (clear_type & AQ_CLEAR_SW)
		clear_bit(sa_num, &aq_rxsc->rx_sa_idx_busy);

	अगर ((clear_type & AQ_CLEAR_HW) && netअगर_carrier_ok(nic->ndev)) अणु
		काष्ठा aq_mss_ingress_sakey_record sa_key_record;
		काष्ठा aq_mss_ingress_sa_record sa_record;

		स_रखो(&sa_key_record, 0, माप(sa_key_record));
		स_रखो(&sa_record, 0, माप(sa_record));
		sa_record.fresh = 1;
		ret = aq_mss_set_ingress_sa_record(hw, &sa_record, sa_idx);
		अगर (ret)
			वापस ret;

		वापस aq_mss_set_ingress_sakey_record(hw, &sa_key_record,
						       sa_idx);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक aq_mकरो_del_rxsa(काष्ठा macsec_context *ctx)
अणु
	स्थिर काष्ठा macsec_rx_sc *rx_sc = ctx->sa.rx_sa->sc;
	काष्ठा aq_nic_s *nic = netdev_priv(ctx->netdev);
	काष्ठा aq_macsec_cfg *cfg = nic->macsec_cfg;
	पूर्णांक rxsc_idx;
	पूर्णांक ret = 0;

	rxsc_idx = aq_get_rxsc_idx_from_rxsc(cfg, rx_sc);
	अगर (rxsc_idx < 0)
		वापस -EINVAL;

	अगर (ctx->prepare)
		वापस 0;

	ret = aq_clear_rxsa(nic, &cfg->aq_rxsc[rxsc_idx], ctx->sa.assoc_num,
			    AQ_CLEAR_ALL);

	वापस ret;
पूर्ण

अटल पूर्णांक aq_mकरो_get_dev_stats(काष्ठा macsec_context *ctx)
अणु
	काष्ठा aq_nic_s *nic = netdev_priv(ctx->netdev);
	काष्ठा aq_macsec_common_stats *stats = &nic->macsec_cfg->stats;
	काष्ठा aq_hw_s *hw = nic->aq_hw;

	अगर (ctx->prepare)
		वापस 0;

	aq_get_macsec_common_stats(hw, stats);

	ctx->stats.dev_stats->OutPktsUntagged = stats->out.untagged_pkts;
	ctx->stats.dev_stats->InPktsUntagged = stats->in.untagged_pkts;
	ctx->stats.dev_stats->OutPktsTooLong = stats->out.too_दीर्घ;
	ctx->stats.dev_stats->InPktsNoTag = stats->in.notag_pkts;
	ctx->stats.dev_stats->InPktsBadTag = stats->in.bad_tag_pkts;
	ctx->stats.dev_stats->InPktsUnknownSCI = stats->in.unknown_sci_pkts;
	ctx->stats.dev_stats->InPktsNoSCI = stats->in.no_sci_pkts;
	ctx->stats.dev_stats->InPktsOverrun = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक aq_mकरो_get_tx_sc_stats(काष्ठा macsec_context *ctx)
अणु
	काष्ठा aq_nic_s *nic = netdev_priv(ctx->netdev);
	काष्ठा aq_macsec_tx_sc_stats *stats;
	काष्ठा aq_hw_s *hw = nic->aq_hw;
	काष्ठा aq_macsec_txsc *aq_txsc;
	पूर्णांक txsc_idx;

	txsc_idx = aq_get_txsc_idx_from_secy(nic->macsec_cfg, ctx->secy);
	अगर (txsc_idx < 0)
		वापस -ENOENT;

	अगर (ctx->prepare)
		वापस 0;

	aq_txsc = &nic->macsec_cfg->aq_txsc[txsc_idx];
	stats = &aq_txsc->stats;
	aq_get_txsc_stats(hw, aq_txsc->hw_sc_idx, stats);

	ctx->stats.tx_sc_stats->OutPktsProtected = stats->sc_रक्षित_pkts;
	ctx->stats.tx_sc_stats->OutPktsEncrypted = stats->sc_encrypted_pkts;
	ctx->stats.tx_sc_stats->OutOctetsProtected = stats->sc_रक्षित_octets;
	ctx->stats.tx_sc_stats->OutOctetsEncrypted = stats->sc_encrypted_octets;

	वापस 0;
पूर्ण

अटल पूर्णांक aq_mकरो_get_tx_sa_stats(काष्ठा macsec_context *ctx)
अणु
	काष्ठा aq_nic_s *nic = netdev_priv(ctx->netdev);
	काष्ठा aq_macsec_cfg *cfg = nic->macsec_cfg;
	काष्ठा aq_macsec_tx_sa_stats *stats;
	काष्ठा aq_hw_s *hw = nic->aq_hw;
	स्थिर काष्ठा macsec_secy *secy;
	काष्ठा aq_macsec_txsc *aq_txsc;
	काष्ठा macsec_tx_sa *tx_sa;
	अचिन्हित पूर्णांक sa_idx;
	पूर्णांक txsc_idx;
	u32 next_pn;
	पूर्णांक ret;

	txsc_idx = aq_get_txsc_idx_from_secy(cfg, ctx->secy);
	अगर (txsc_idx < 0)
		वापस -EINVAL;

	अगर (ctx->prepare)
		वापस 0;

	aq_txsc = &cfg->aq_txsc[txsc_idx];
	sa_idx = aq_txsc->hw_sc_idx | ctx->sa.assoc_num;
	stats = &aq_txsc->tx_sa_stats[ctx->sa.assoc_num];
	ret = aq_get_txsa_stats(hw, sa_idx, stats);
	अगर (ret)
		वापस ret;

	ctx->stats.tx_sa_stats->OutPktsProtected = stats->sa_रक्षित_pkts;
	ctx->stats.tx_sa_stats->OutPktsEncrypted = stats->sa_encrypted_pkts;

	secy = aq_txsc->sw_secy;
	tx_sa = rcu_dereference_bh(secy->tx_sc.sa[ctx->sa.assoc_num]);
	ret = aq_get_txsa_next_pn(hw, sa_idx, &next_pn);
	अगर (ret == 0) अणु
		spin_lock_bh(&tx_sa->lock);
		tx_sa->next_pn = next_pn;
		spin_unlock_bh(&tx_sa->lock);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक aq_mकरो_get_rx_sc_stats(काष्ठा macsec_context *ctx)
अणु
	काष्ठा aq_nic_s *nic = netdev_priv(ctx->netdev);
	काष्ठा aq_macsec_cfg *cfg = nic->macsec_cfg;
	काष्ठा aq_macsec_rx_sa_stats *stats;
	काष्ठा aq_hw_s *hw = nic->aq_hw;
	काष्ठा aq_macsec_rxsc *aq_rxsc;
	अचिन्हित पूर्णांक sa_idx;
	पूर्णांक rxsc_idx;
	पूर्णांक ret = 0;
	पूर्णांक i;

	rxsc_idx = aq_get_rxsc_idx_from_rxsc(cfg, ctx->rx_sc);
	अगर (rxsc_idx < 0)
		वापस -ENOENT;

	अगर (ctx->prepare)
		वापस 0;

	aq_rxsc = &cfg->aq_rxsc[rxsc_idx];
	क्रम (i = 0; i < MACSEC_NUM_AN; i++) अणु
		अगर (!test_bit(i, &aq_rxsc->rx_sa_idx_busy))
			जारी;

		stats = &aq_rxsc->rx_sa_stats[i];
		sa_idx = aq_rxsc->hw_sc_idx | i;
		ret = aq_get_rxsa_stats(hw, sa_idx, stats);
		अगर (ret)
			अवरोध;

		ctx->stats.rx_sc_stats->InOctetsValidated +=
			stats->validated_octets;
		ctx->stats.rx_sc_stats->InOctetsDecrypted +=
			stats->decrypted_octets;
		ctx->stats.rx_sc_stats->InPktsUnchecked +=
			stats->unchecked_pkts;
		ctx->stats.rx_sc_stats->InPktsDelayed += stats->delayed_pkts;
		ctx->stats.rx_sc_stats->InPktsOK += stats->ok_pkts;
		ctx->stats.rx_sc_stats->InPktsInvalid += stats->invalid_pkts;
		ctx->stats.rx_sc_stats->InPktsLate += stats->late_pkts;
		ctx->stats.rx_sc_stats->InPktsNotValid += stats->not_valid_pkts;
		ctx->stats.rx_sc_stats->InPktsNotUsingSA += stats->not_using_sa;
		ctx->stats.rx_sc_stats->InPktsUnusedSA += stats->unused_sa;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक aq_mकरो_get_rx_sa_stats(काष्ठा macsec_context *ctx)
अणु
	काष्ठा aq_nic_s *nic = netdev_priv(ctx->netdev);
	काष्ठा aq_macsec_cfg *cfg = nic->macsec_cfg;
	काष्ठा aq_macsec_rx_sa_stats *stats;
	काष्ठा aq_hw_s *hw = nic->aq_hw;
	काष्ठा aq_macsec_rxsc *aq_rxsc;
	काष्ठा macsec_rx_sa *rx_sa;
	अचिन्हित पूर्णांक sa_idx;
	पूर्णांक rxsc_idx;
	u32 next_pn;
	पूर्णांक ret;

	rxsc_idx = aq_get_rxsc_idx_from_rxsc(cfg, ctx->rx_sc);
	अगर (rxsc_idx < 0)
		वापस -EINVAL;

	अगर (ctx->prepare)
		वापस 0;

	aq_rxsc = &cfg->aq_rxsc[rxsc_idx];
	stats = &aq_rxsc->rx_sa_stats[ctx->sa.assoc_num];
	sa_idx = aq_rxsc->hw_sc_idx | ctx->sa.assoc_num;
	ret = aq_get_rxsa_stats(hw, sa_idx, stats);
	अगर (ret)
		वापस ret;

	ctx->stats.rx_sa_stats->InPktsOK = stats->ok_pkts;
	ctx->stats.rx_sa_stats->InPktsInvalid = stats->invalid_pkts;
	ctx->stats.rx_sa_stats->InPktsNotValid = stats->not_valid_pkts;
	ctx->stats.rx_sa_stats->InPktsNotUsingSA = stats->not_using_sa;
	ctx->stats.rx_sa_stats->InPktsUnusedSA = stats->unused_sa;

	rx_sa = rcu_dereference_bh(aq_rxsc->sw_rxsc->sa[ctx->sa.assoc_num]);
	ret = aq_get_rxsa_next_pn(hw, sa_idx, &next_pn);
	अगर (ret == 0) अणु
		spin_lock_bh(&rx_sa->lock);
		rx_sa->next_pn = next_pn;
		spin_unlock_bh(&rx_sa->lock);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक apply_txsc_cfg(काष्ठा aq_nic_s *nic, स्थिर पूर्णांक txsc_idx)
अणु
	काष्ठा aq_macsec_txsc *aq_txsc = &nic->macsec_cfg->aq_txsc[txsc_idx];
	स्थिर काष्ठा macsec_secy *secy = aq_txsc->sw_secy;
	काष्ठा macsec_tx_sa *tx_sa;
	पूर्णांक ret = 0;
	पूर्णांक i;

	अगर (!netअगर_running(secy->netdev))
		वापस ret;

	ret = aq_set_txsc(nic, txsc_idx);
	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < MACSEC_NUM_AN; i++) अणु
		tx_sa = rcu_dereference_bh(secy->tx_sc.sa[i]);
		अगर (tx_sa) अणु
			ret = aq_update_txsa(nic, aq_txsc->hw_sc_idx, secy,
					     tx_sa, aq_txsc->tx_sa_key[i], i);
			अगर (ret)
				वापस ret;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक apply_rxsc_cfg(काष्ठा aq_nic_s *nic, स्थिर पूर्णांक rxsc_idx)
अणु
	काष्ठा aq_macsec_rxsc *aq_rxsc = &nic->macsec_cfg->aq_rxsc[rxsc_idx];
	स्थिर काष्ठा macsec_secy *secy = aq_rxsc->sw_secy;
	काष्ठा macsec_rx_sa *rx_sa;
	पूर्णांक ret = 0;
	पूर्णांक i;

	अगर (!netअगर_running(secy->netdev))
		वापस ret;

	ret = aq_set_rxsc(nic, rxsc_idx);
	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < MACSEC_NUM_AN; i++) अणु
		rx_sa = rcu_dereference_bh(aq_rxsc->sw_rxsc->sa[i]);
		अगर (rx_sa) अणु
			ret = aq_update_rxsa(nic, aq_rxsc->hw_sc_idx, secy,
					     rx_sa, aq_rxsc->rx_sa_key[i], i);
			अगर (ret)
				वापस ret;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक aq_clear_secy(काष्ठा aq_nic_s *nic, स्थिर काष्ठा macsec_secy *secy,
			 क्रमागत aq_clear_type clear_type)
अणु
	काष्ठा macsec_rx_sc *rx_sc;
	पूर्णांक txsc_idx;
	पूर्णांक rxsc_idx;
	पूर्णांक ret = 0;

	txsc_idx = aq_get_txsc_idx_from_secy(nic->macsec_cfg, secy);
	अगर (txsc_idx >= 0) अणु
		ret = aq_clear_txsc(nic, txsc_idx, clear_type);
		अगर (ret)
			वापस ret;
	पूर्ण

	क्रम (rx_sc = rcu_dereference_bh(secy->rx_sc); rx_sc;
	     rx_sc = rcu_dereference_bh(rx_sc->next)) अणु
		rxsc_idx = aq_get_rxsc_idx_from_rxsc(nic->macsec_cfg, rx_sc);
		अगर (rxsc_idx < 0)
			जारी;

		ret = aq_clear_rxsc(nic, rxsc_idx, clear_type);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक aq_apply_secy_cfg(काष्ठा aq_nic_s *nic,
			     स्थिर काष्ठा macsec_secy *secy)
अणु
	काष्ठा macsec_rx_sc *rx_sc;
	पूर्णांक txsc_idx;
	पूर्णांक rxsc_idx;
	पूर्णांक ret = 0;

	txsc_idx = aq_get_txsc_idx_from_secy(nic->macsec_cfg, secy);
	अगर (txsc_idx >= 0)
		apply_txsc_cfg(nic, txsc_idx);

	क्रम (rx_sc = rcu_dereference_bh(secy->rx_sc); rx_sc && rx_sc->active;
	     rx_sc = rcu_dereference_bh(rx_sc->next)) अणु
		rxsc_idx = aq_get_rxsc_idx_from_rxsc(nic->macsec_cfg, rx_sc);
		अगर (unlikely(rxsc_idx < 0))
			जारी;

		ret = apply_rxsc_cfg(nic, rxsc_idx);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक aq_apply_macsec_cfg(काष्ठा aq_nic_s *nic)
अणु
	पूर्णांक ret = 0;
	पूर्णांक i;

	क्रम (i = 0; i < AQ_MACSEC_MAX_SC; i++) अणु
		अगर (nic->macsec_cfg->txsc_idx_busy & BIT(i)) अणु
			ret = apply_txsc_cfg(nic, i);
			अगर (ret)
				वापस ret;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < AQ_MACSEC_MAX_SC; i++) अणु
		अगर (nic->macsec_cfg->rxsc_idx_busy & BIT(i)) अणु
			ret = apply_rxsc_cfg(nic, i);
			अगर (ret)
				वापस ret;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक aq_sa_from_sa_idx(स्थिर क्रमागत aq_macsec_sc_sa sc_sa, स्थिर पूर्णांक sa_idx)
अणु
	चयन (sc_sa) अणु
	हाल aq_macsec_sa_sc_4sa_8sc:
		वापस sa_idx & 3;
	हाल aq_macsec_sa_sc_2sa_16sc:
		वापस sa_idx & 1;
	हाल aq_macsec_sa_sc_1sa_32sc:
		वापस 0;
	शेष:
		WARN_ONCE(true, "Invalid sc_sa");
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक aq_sc_idx_from_sa_idx(स्थिर क्रमागत aq_macsec_sc_sa sc_sa,
				 स्थिर पूर्णांक sa_idx)
अणु
	चयन (sc_sa) अणु
	हाल aq_macsec_sa_sc_4sa_8sc:
		वापस sa_idx & ~3;
	हाल aq_macsec_sa_sc_2sa_16sc:
		वापस sa_idx & ~1;
	हाल aq_macsec_sa_sc_1sa_32sc:
		वापस sa_idx;
	शेष:
		WARN_ONCE(true, "Invalid sc_sa");
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल व्योम aq_check_txsa_expiration(काष्ठा aq_nic_s *nic)
अणु
	u32 egress_sa_expired, egress_sa_threshold_expired;
	काष्ठा aq_macsec_cfg *cfg = nic->macsec_cfg;
	काष्ठा aq_hw_s *hw = nic->aq_hw;
	काष्ठा aq_macsec_txsc *aq_txsc;
	स्थिर काष्ठा macsec_secy *secy;
	पूर्णांक sc_idx = 0, txsc_idx = 0;
	क्रमागत aq_macsec_sc_sa sc_sa;
	काष्ठा macsec_tx_sa *tx_sa;
	अचिन्हित अक्षर an = 0;
	पूर्णांक ret;
	पूर्णांक i;

	sc_sa = cfg->sc_sa;

	ret = aq_mss_get_egress_sa_expired(hw, &egress_sa_expired);
	अगर (unlikely(ret))
		वापस;

	ret = aq_mss_get_egress_sa_threshold_expired(hw,
		&egress_sa_threshold_expired);

	क्रम (i = 0; i < AQ_MACSEC_MAX_SA; i++) अणु
		अगर (egress_sa_expired & BIT(i)) अणु
			an = aq_sa_from_sa_idx(sc_sa, i);
			sc_idx = aq_sc_idx_from_sa_idx(sc_sa, i);
			txsc_idx = aq_get_txsc_idx_from_sc_idx(sc_sa, sc_idx);
			अगर (txsc_idx < 0)
				जारी;

			aq_txsc = &cfg->aq_txsc[txsc_idx];
			अगर (!(cfg->txsc_idx_busy & BIT(txsc_idx))) अणु
				netdev_warn(nic->ndev,
					"PN threshold expired on invalid TX SC");
				जारी;
			पूर्ण

			secy = aq_txsc->sw_secy;
			अगर (!netअगर_running(secy->netdev)) अणु
				netdev_warn(nic->ndev,
					"PN threshold expired on down TX SC");
				जारी;
			पूर्ण

			अगर (unlikely(!(aq_txsc->tx_sa_idx_busy & BIT(an)))) अणु
				netdev_warn(nic->ndev,
					"PN threshold expired on invalid TX SA");
				जारी;
			पूर्ण

			tx_sa = rcu_dereference_bh(secy->tx_sc.sa[an]);
			macsec_pn_wrapped((काष्ठा macsec_secy *)secy, tx_sa);
		पूर्ण
	पूर्ण

	aq_mss_set_egress_sa_expired(hw, egress_sa_expired);
	अगर (likely(!ret))
		aq_mss_set_egress_sa_threshold_expired(hw,
			egress_sa_threshold_expired);
पूर्ण

स्थिर काष्ठा macsec_ops aq_macsec_ops = अणु
	.mकरो_dev_खोलो = aq_mकरो_dev_खोलो,
	.mकरो_dev_stop = aq_mकरो_dev_stop,
	.mकरो_add_secy = aq_mकरो_add_secy,
	.mकरो_upd_secy = aq_mकरो_upd_secy,
	.mकरो_del_secy = aq_mकरो_del_secy,
	.mकरो_add_rxsc = aq_mकरो_add_rxsc,
	.mकरो_upd_rxsc = aq_mकरो_upd_rxsc,
	.mकरो_del_rxsc = aq_mकरो_del_rxsc,
	.mकरो_add_rxsa = aq_mकरो_add_rxsa,
	.mकरो_upd_rxsa = aq_mकरो_upd_rxsa,
	.mकरो_del_rxsa = aq_mकरो_del_rxsa,
	.mकरो_add_txsa = aq_mकरो_add_txsa,
	.mकरो_upd_txsa = aq_mकरो_upd_txsa,
	.mकरो_del_txsa = aq_mकरो_del_txsa,
	.mकरो_get_dev_stats = aq_mकरो_get_dev_stats,
	.mकरो_get_tx_sc_stats = aq_mकरो_get_tx_sc_stats,
	.mकरो_get_tx_sa_stats = aq_mकरो_get_tx_sa_stats,
	.mकरो_get_rx_sc_stats = aq_mकरो_get_rx_sc_stats,
	.mकरो_get_rx_sa_stats = aq_mकरो_get_rx_sa_stats,
पूर्ण;

पूर्णांक aq_macsec_init(काष्ठा aq_nic_s *nic)
अणु
	काष्ठा aq_macsec_cfg *cfg;
	u32 caps_lo;

	अगर (!nic->aq_fw_ops->get_link_capabilities)
		वापस 0;

	caps_lo = nic->aq_fw_ops->get_link_capabilities(nic->aq_hw);

	अगर (!(caps_lo & BIT(CAPS_LO_MACSEC)))
		वापस 0;

	nic->macsec_cfg = kzalloc(माप(*cfg), GFP_KERNEL);
	अगर (!nic->macsec_cfg)
		वापस -ENOMEM;

	nic->ndev->features |= NETIF_F_HW_MACSEC;
	nic->ndev->macsec_ops = &aq_macsec_ops;

	वापस 0;
पूर्ण

व्योम aq_macsec_मुक्त(काष्ठा aq_nic_s *nic)
अणु
	kमुक्त(nic->macsec_cfg);
	nic->macsec_cfg = शून्य;
पूर्ण

पूर्णांक aq_macsec_enable(काष्ठा aq_nic_s *nic)
अणु
	u32 ctl_ether_types[1] = अणु ETH_P_PAE पूर्ण;
	काष्ठा macsec_msg_fw_response resp = अणु 0 पूर्ण;
	काष्ठा macsec_msg_fw_request msg = अणु 0 पूर्ण;
	काष्ठा aq_hw_s *hw = nic->aq_hw;
	पूर्णांक num_ctl_ether_types = 0;
	पूर्णांक index = 0, tbl_idx;
	पूर्णांक ret;

	अगर (!nic->macsec_cfg)
		वापस 0;

	rtnl_lock();

	अगर (nic->aq_fw_ops->send_macsec_req) अणु
		काष्ठा macsec_cfg_request cfg = अणु 0 पूर्ण;

		cfg.enabled = 1;
		cfg.egress_threshold = 0xffffffff;
		cfg.ingress_threshold = 0xffffffff;
		cfg.पूर्णांकerrupts_enabled = 1;

		msg.msg_type = macsec_cfg_msg;
		msg.cfg = cfg;

		ret = nic->aq_fw_ops->send_macsec_req(hw, &msg, &resp);
		अगर (ret)
			जाओ unlock;
	पूर्ण

	/* Init Ethertype bypass filters */
	क्रम (index = 0; index < ARRAY_SIZE(ctl_ether_types); index++) अणु
		काष्ठा aq_mss_ingress_prectlf_record rx_prectlf_rec;
		काष्ठा aq_mss_egress_ctlf_record tx_ctlf_rec;

		अगर (ctl_ether_types[index] == 0)
			जारी;

		स_रखो(&tx_ctlf_rec, 0, माप(tx_ctlf_rec));
		tx_ctlf_rec.eth_type = ctl_ether_types[index];
		tx_ctlf_rec.match_type = 4; /* Match eth_type only */
		tx_ctlf_rec.match_mask = 0xf; /* match क्रम eth_type */
		tx_ctlf_rec.action = 0; /* Bypass MACSEC modules */
		tbl_idx = NUMROWS_EGRESSCTLFRECORD - num_ctl_ether_types - 1;
		aq_mss_set_egress_ctlf_record(hw, &tx_ctlf_rec, tbl_idx);

		स_रखो(&rx_prectlf_rec, 0, माप(rx_prectlf_rec));
		rx_prectlf_rec.eth_type = ctl_ether_types[index];
		rx_prectlf_rec.match_type = 4; /* Match eth_type only */
		rx_prectlf_rec.match_mask = 0xf; /* match क्रम eth_type */
		rx_prectlf_rec.action = 0; /* Bypass MACSEC modules */
		tbl_idx =
			NUMROWS_INGRESSPRECTLFRECORD - num_ctl_ether_types - 1;
		aq_mss_set_ingress_prectlf_record(hw, &rx_prectlf_rec, tbl_idx);

		num_ctl_ether_types++;
	पूर्ण

	ret = aq_apply_macsec_cfg(nic);

unlock:
	rtnl_unlock();
	वापस ret;
पूर्ण

व्योम aq_macsec_work(काष्ठा aq_nic_s *nic)
अणु
	अगर (!nic->macsec_cfg)
		वापस;

	अगर (!netअगर_carrier_ok(nic->ndev))
		वापस;

	rtnl_lock();
	aq_check_txsa_expiration(nic);
	rtnl_unlock();
पूर्ण

पूर्णांक aq_macsec_rx_sa_cnt(काष्ठा aq_nic_s *nic)
अणु
	काष्ठा aq_macsec_cfg *cfg = nic->macsec_cfg;
	पूर्णांक i, cnt = 0;

	अगर (!cfg)
		वापस 0;

	क्रम (i = 0; i < AQ_MACSEC_MAX_SC; i++) अणु
		अगर (!test_bit(i, &cfg->rxsc_idx_busy))
			जारी;
		cnt += hweight_दीर्घ(cfg->aq_rxsc[i].rx_sa_idx_busy);
	पूर्ण

	वापस cnt;
पूर्ण

पूर्णांक aq_macsec_tx_sc_cnt(काष्ठा aq_nic_s *nic)
अणु
	अगर (!nic->macsec_cfg)
		वापस 0;

	वापस hweight_दीर्घ(nic->macsec_cfg->txsc_idx_busy);
पूर्ण

पूर्णांक aq_macsec_tx_sa_cnt(काष्ठा aq_nic_s *nic)
अणु
	काष्ठा aq_macsec_cfg *cfg = nic->macsec_cfg;
	पूर्णांक i, cnt = 0;

	अगर (!cfg)
		वापस 0;

	क्रम (i = 0; i < AQ_MACSEC_MAX_SC; i++) अणु
		अगर (!test_bit(i, &cfg->txsc_idx_busy))
			जारी;
		cnt += hweight_दीर्घ(cfg->aq_txsc[i].tx_sa_idx_busy);
	पूर्ण

	वापस cnt;
पूर्ण

अटल पूर्णांक aq_macsec_update_stats(काष्ठा aq_nic_s *nic)
अणु
	काष्ठा aq_macsec_cfg *cfg = nic->macsec_cfg;
	काष्ठा aq_hw_s *hw = nic->aq_hw;
	काष्ठा aq_macsec_txsc *aq_txsc;
	काष्ठा aq_macsec_rxsc *aq_rxsc;
	पूर्णांक i, sa_idx, assoc_num;
	पूर्णांक ret = 0;

	aq_get_macsec_common_stats(hw, &cfg->stats);

	क्रम (i = 0; i < AQ_MACSEC_MAX_SC; i++) अणु
		अगर (!(cfg->txsc_idx_busy & BIT(i)))
			जारी;
		aq_txsc = &cfg->aq_txsc[i];

		ret = aq_get_txsc_stats(hw, aq_txsc->hw_sc_idx,
					&aq_txsc->stats);
		अगर (ret)
			वापस ret;

		क्रम (assoc_num = 0; assoc_num < MACSEC_NUM_AN; assoc_num++) अणु
			अगर (!test_bit(assoc_num, &aq_txsc->tx_sa_idx_busy))
				जारी;
			sa_idx = aq_txsc->hw_sc_idx | assoc_num;
			ret = aq_get_txsa_stats(hw, sa_idx,
					      &aq_txsc->tx_sa_stats[assoc_num]);
			अगर (ret)
				वापस ret;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < AQ_MACSEC_MAX_SC; i++) अणु
		अगर (!(test_bit(i, &cfg->rxsc_idx_busy)))
			जारी;
		aq_rxsc = &cfg->aq_rxsc[i];

		क्रम (assoc_num = 0; assoc_num < MACSEC_NUM_AN; assoc_num++) अणु
			अगर (!test_bit(assoc_num, &aq_rxsc->rx_sa_idx_busy))
				जारी;
			sa_idx = aq_rxsc->hw_sc_idx | assoc_num;

			ret = aq_get_rxsa_stats(hw, sa_idx,
					      &aq_rxsc->rx_sa_stats[assoc_num]);
			अगर (ret)
				वापस ret;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

u64 *aq_macsec_get_stats(काष्ठा aq_nic_s *nic, u64 *data)
अणु
	काष्ठा aq_macsec_cfg *cfg = nic->macsec_cfg;
	काष्ठा aq_macsec_common_stats *common_stats;
	काष्ठा aq_macsec_tx_sc_stats *txsc_stats;
	काष्ठा aq_macsec_tx_sa_stats *txsa_stats;
	काष्ठा aq_macsec_rx_sa_stats *rxsa_stats;
	काष्ठा aq_macsec_txsc *aq_txsc;
	काष्ठा aq_macsec_rxsc *aq_rxsc;
	अचिन्हित पूर्णांक assoc_num;
	अचिन्हित पूर्णांक sc_num;
	अचिन्हित पूर्णांक i = 0U;

	अगर (!cfg)
		वापस data;

	aq_macsec_update_stats(nic);

	common_stats = &cfg->stats;
	data[i] = common_stats->in.ctl_pkts;
	data[++i] = common_stats->in.tagged_miss_pkts;
	data[++i] = common_stats->in.untagged_miss_pkts;
	data[++i] = common_stats->in.notag_pkts;
	data[++i] = common_stats->in.untagged_pkts;
	data[++i] = common_stats->in.bad_tag_pkts;
	data[++i] = common_stats->in.no_sci_pkts;
	data[++i] = common_stats->in.unknown_sci_pkts;
	data[++i] = common_stats->in.ctrl_prt_pass_pkts;
	data[++i] = common_stats->in.unctrl_prt_pass_pkts;
	data[++i] = common_stats->in.ctrl_prt_fail_pkts;
	data[++i] = common_stats->in.unctrl_prt_fail_pkts;
	data[++i] = common_stats->in.too_दीर्घ_pkts;
	data[++i] = common_stats->in.igpoc_ctl_pkts;
	data[++i] = common_stats->in.ecc_error_pkts;
	data[++i] = common_stats->in.unctrl_hit_drop_redir;
	data[++i] = common_stats->out.ctl_pkts;
	data[++i] = common_stats->out.unknown_sa_pkts;
	data[++i] = common_stats->out.untagged_pkts;
	data[++i] = common_stats->out.too_दीर्घ;
	data[++i] = common_stats->out.ecc_error_pkts;
	data[++i] = common_stats->out.unctrl_hit_drop_redir;

	क्रम (sc_num = 0; sc_num < AQ_MACSEC_MAX_SC; sc_num++) अणु
		अगर (!(test_bit(sc_num, &cfg->txsc_idx_busy)))
			जारी;

		aq_txsc = &cfg->aq_txsc[sc_num];
		txsc_stats = &aq_txsc->stats;

		data[++i] = txsc_stats->sc_रक्षित_pkts;
		data[++i] = txsc_stats->sc_encrypted_pkts;
		data[++i] = txsc_stats->sc_रक्षित_octets;
		data[++i] = txsc_stats->sc_encrypted_octets;

		क्रम (assoc_num = 0; assoc_num < MACSEC_NUM_AN; assoc_num++) अणु
			अगर (!test_bit(assoc_num, &aq_txsc->tx_sa_idx_busy))
				जारी;

			txsa_stats = &aq_txsc->tx_sa_stats[assoc_num];

			data[++i] = txsa_stats->sa_hit_drop_redirect;
			data[++i] = txsa_stats->sa_रक्षित2_pkts;
			data[++i] = txsa_stats->sa_रक्षित_pkts;
			data[++i] = txsa_stats->sa_encrypted_pkts;
		पूर्ण
	पूर्ण

	क्रम (sc_num = 0; sc_num < AQ_MACSEC_MAX_SC; sc_num++) अणु
		अगर (!(test_bit(sc_num, &cfg->rxsc_idx_busy)))
			जारी;

		aq_rxsc = &cfg->aq_rxsc[sc_num];

		क्रम (assoc_num = 0; assoc_num < MACSEC_NUM_AN; assoc_num++) अणु
			अगर (!test_bit(assoc_num, &aq_rxsc->rx_sa_idx_busy))
				जारी;

			rxsa_stats = &aq_rxsc->rx_sa_stats[assoc_num];

			data[++i] = rxsa_stats->untagged_hit_pkts;
			data[++i] = rxsa_stats->ctrl_hit_drop_redir_pkts;
			data[++i] = rxsa_stats->not_using_sa;
			data[++i] = rxsa_stats->unused_sa;
			data[++i] = rxsa_stats->not_valid_pkts;
			data[++i] = rxsa_stats->invalid_pkts;
			data[++i] = rxsa_stats->ok_pkts;
			data[++i] = rxsa_stats->late_pkts;
			data[++i] = rxsa_stats->delayed_pkts;
			data[++i] = rxsa_stats->unchecked_pkts;
			data[++i] = rxsa_stats->validated_octets;
			data[++i] = rxsa_stats->decrypted_octets;
		पूर्ण
	पूर्ण

	i++;

	data += i;

	वापस data;
पूर्ण
