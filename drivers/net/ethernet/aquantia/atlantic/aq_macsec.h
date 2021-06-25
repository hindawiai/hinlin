<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/* Atlantic Network Driver
 * Copyright (C) 2020 Marvell International Ltd.
 */

#अगर_अघोषित AQ_MACSEC_H
#घोषणा AQ_MACSEC_H

#समावेश <linux/netdevice.h>
#अगर IS_ENABLED(CONFIG_MACSEC)

#समावेश "net/macsec.h"

काष्ठा aq_nic_s;

#घोषणा AQ_MACSEC_MAX_SC 32
#घोषणा AQ_MACSEC_MAX_SA 32

क्रमागत aq_macsec_sc_sa अणु
	aq_macsec_sa_sc_4sa_8sc,
	aq_macsec_sa_sc_not_used,
	aq_macsec_sa_sc_2sa_16sc,
	aq_macsec_sa_sc_1sa_32sc,
पूर्ण;

काष्ठा aq_macsec_common_stats अणु
	/* Ingress Common Counters */
	काष्ठा अणु
		u64 ctl_pkts;
		u64 tagged_miss_pkts;
		u64 untagged_miss_pkts;
		u64 notag_pkts;
		u64 untagged_pkts;
		u64 bad_tag_pkts;
		u64 no_sci_pkts;
		u64 unknown_sci_pkts;
		u64 ctrl_prt_pass_pkts;
		u64 unctrl_prt_pass_pkts;
		u64 ctrl_prt_fail_pkts;
		u64 unctrl_prt_fail_pkts;
		u64 too_दीर्घ_pkts;
		u64 igpoc_ctl_pkts;
		u64 ecc_error_pkts;
		u64 unctrl_hit_drop_redir;
	पूर्ण in;

	/* Egress Common Counters */
	काष्ठा अणु
		u64 ctl_pkts;
		u64 unknown_sa_pkts;
		u64 untagged_pkts;
		u64 too_दीर्घ;
		u64 ecc_error_pkts;
		u64 unctrl_hit_drop_redir;
	पूर्ण out;
पूर्ण;

/* Ingress SA Counters */
काष्ठा aq_macsec_rx_sa_stats अणु
	u64 untagged_hit_pkts;
	u64 ctrl_hit_drop_redir_pkts;
	u64 not_using_sa;
	u64 unused_sa;
	u64 not_valid_pkts;
	u64 invalid_pkts;
	u64 ok_pkts;
	u64 late_pkts;
	u64 delayed_pkts;
	u64 unchecked_pkts;
	u64 validated_octets;
	u64 decrypted_octets;
पूर्ण;

/* Egress SA Counters */
काष्ठा aq_macsec_tx_sa_stats अणु
	u64 sa_hit_drop_redirect;
	u64 sa_रक्षित2_pkts;
	u64 sa_रक्षित_pkts;
	u64 sa_encrypted_pkts;
पूर्ण;

/* Egress SC Counters */
काष्ठा aq_macsec_tx_sc_stats अणु
	u64 sc_रक्षित_pkts;
	u64 sc_encrypted_pkts;
	u64 sc_रक्षित_octets;
	u64 sc_encrypted_octets;
पूर्ण;

काष्ठा aq_macsec_txsc अणु
	u32 hw_sc_idx;
	अचिन्हित दीर्घ tx_sa_idx_busy;
	स्थिर काष्ठा macsec_secy *sw_secy;
	u8 tx_sa_key[MACSEC_NUM_AN][MACSEC_KEYID_LEN];
	काष्ठा aq_macsec_tx_sc_stats stats;
	काष्ठा aq_macsec_tx_sa_stats tx_sa_stats[MACSEC_NUM_AN];
पूर्ण;

काष्ठा aq_macsec_rxsc अणु
	u32 hw_sc_idx;
	अचिन्हित दीर्घ rx_sa_idx_busy;
	स्थिर काष्ठा macsec_secy *sw_secy;
	स्थिर काष्ठा macsec_rx_sc *sw_rxsc;
	u8 rx_sa_key[MACSEC_NUM_AN][MACSEC_KEYID_LEN];
	काष्ठा aq_macsec_rx_sa_stats rx_sa_stats[MACSEC_NUM_AN];
पूर्ण;

काष्ठा aq_macsec_cfg अणु
	क्रमागत aq_macsec_sc_sa sc_sa;
	/* Egress channel configuration */
	अचिन्हित दीर्घ txsc_idx_busy;
	काष्ठा aq_macsec_txsc aq_txsc[AQ_MACSEC_MAX_SC];
	/* Ingress channel configuration */
	अचिन्हित दीर्घ rxsc_idx_busy;
	काष्ठा aq_macsec_rxsc aq_rxsc[AQ_MACSEC_MAX_SC];
	/* Statistics / counters */
	काष्ठा aq_macsec_common_stats stats;
पूर्ण;

बाह्य स्थिर काष्ठा macsec_ops aq_macsec_ops;

पूर्णांक aq_macsec_init(काष्ठा aq_nic_s *nic);
व्योम aq_macsec_मुक्त(काष्ठा aq_nic_s *nic);
पूर्णांक aq_macsec_enable(काष्ठा aq_nic_s *nic);
व्योम aq_macsec_work(काष्ठा aq_nic_s *nic);
u64 *aq_macsec_get_stats(काष्ठा aq_nic_s *nic, u64 *data);
पूर्णांक aq_macsec_rx_sa_cnt(काष्ठा aq_nic_s *nic);
पूर्णांक aq_macsec_tx_sc_cnt(काष्ठा aq_nic_s *nic);
पूर्णांक aq_macsec_tx_sa_cnt(काष्ठा aq_nic_s *nic);

#पूर्ण_अगर

#पूर्ण_अगर /* AQ_MACSEC_H */
