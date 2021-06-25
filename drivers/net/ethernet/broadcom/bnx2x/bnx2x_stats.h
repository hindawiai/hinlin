<शैली गुरु>
/* bnx2x_stats.h: QLogic Everest network driver.
 *
 * Copyright (c) 2007-2013 Broadcom Corporation
 * Copyright (c) 2014 QLogic Corporation
 * All rights reserved
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation.
 *
 * Maपूर्णांकained by: Ariel Elior <ariel.elior@qlogic.com>
 * Written by: Eliezer Tamir
 * Based on code from Michael Chan's bnx2 driver
 * UDP CSUM errata workaround by Arik Gendelman
 * Slowpath and fastpath rework by Vladislav Zolotarov
 * Statistics and Link management by Yitchak Gertner
 *
 */
#अगर_अघोषित BNX2X_STATS_H
#घोषणा BNX2X_STATS_H

#समावेश <linux/types.h>

काष्ठा nig_stats अणु
	u32 brb_discard;
	u32 brb_packet;
	u32 brb_truncate;
	u32 flow_ctrl_discard;
	u32 flow_ctrl_octets;
	u32 flow_ctrl_packet;
	u32 mng_discard;
	u32 mng_octet_inp;
	u32 mng_octet_out;
	u32 mng_packet_inp;
	u32 mng_packet_out;
	u32 pbf_octets;
	u32 pbf_packet;
	u32 safc_inp;
	u32 egress_mac_pkt0_lo;
	u32 egress_mac_pkt0_hi;
	u32 egress_mac_pkt1_lo;
	u32 egress_mac_pkt1_hi;
पूर्ण;

क्रमागत bnx2x_stats_event अणु
	STATS_EVENT_PMF = 0,
	STATS_EVENT_LINK_UP,
	STATS_EVENT_UPDATE,
	STATS_EVENT_STOP,
	STATS_EVENT_MAX
पूर्ण;

क्रमागत bnx2x_stats_state अणु
	STATS_STATE_DISABLED = 0,
	STATS_STATE_ENABLED,
	STATS_STATE_MAX
पूर्ण;

काष्ठा bnx2x_eth_stats अणु
	u32 total_bytes_received_hi;
	u32 total_bytes_received_lo;
	u32 total_bytes_transmitted_hi;
	u32 total_bytes_transmitted_lo;
	u32 total_unicast_packets_received_hi;
	u32 total_unicast_packets_received_lo;
	u32 total_multicast_packets_received_hi;
	u32 total_multicast_packets_received_lo;
	u32 total_broadcast_packets_received_hi;
	u32 total_broadcast_packets_received_lo;
	u32 total_unicast_packets_transmitted_hi;
	u32 total_unicast_packets_transmitted_lo;
	u32 total_multicast_packets_transmitted_hi;
	u32 total_multicast_packets_transmitted_lo;
	u32 total_broadcast_packets_transmitted_hi;
	u32 total_broadcast_packets_transmitted_lo;
	u32 valid_bytes_received_hi;
	u32 valid_bytes_received_lo;

	u32 error_bytes_received_hi;
	u32 error_bytes_received_lo;
	u32 etherstatsoverrsizepkts_hi;
	u32 etherstatsoverrsizepkts_lo;
	u32 no_buff_discard_hi;
	u32 no_buff_discard_lo;

	u32 rx_stat_अगरhcinbaकरोctets_hi;
	u32 rx_stat_अगरhcinbaकरोctets_lo;
	u32 tx_stat_अगरhcoutbaकरोctets_hi;
	u32 tx_stat_अगरhcoutbaकरोctets_lo;
	u32 rx_stat_करोt3statsfcserrors_hi;
	u32 rx_stat_करोt3statsfcserrors_lo;
	u32 rx_stat_करोt3statsalignmenterrors_hi;
	u32 rx_stat_करोt3statsalignmenterrors_lo;
	u32 rx_stat_करोt3statscarriersenseerrors_hi;
	u32 rx_stat_करोt3statscarriersenseerrors_lo;
	u32 rx_stat_falsecarriererrors_hi;
	u32 rx_stat_falsecarriererrors_lo;
	u32 rx_stat_etherstatsundersizepkts_hi;
	u32 rx_stat_etherstatsundersizepkts_lo;
	u32 rx_stat_करोt3statsframestooदीर्घ_hi;
	u32 rx_stat_करोt3statsframestooदीर्घ_lo;
	u32 rx_stat_etherstatsfragments_hi;
	u32 rx_stat_etherstatsfragments_lo;
	u32 rx_stat_etherstatsjabbers_hi;
	u32 rx_stat_etherstatsjabbers_lo;
	u32 rx_stat_maccontrolframesreceived_hi;
	u32 rx_stat_maccontrolframesreceived_lo;
	u32 rx_stat_bmac_xpf_hi;
	u32 rx_stat_bmac_xpf_lo;
	u32 rx_stat_bmac_xcf_hi;
	u32 rx_stat_bmac_xcf_lo;
	u32 rx_stat_xofख_स्थितिeentered_hi;
	u32 rx_stat_xofख_स्थितिeentered_lo;
	u32 rx_stat_xonछोड़ोframesreceived_hi;
	u32 rx_stat_xonछोड़ोframesreceived_lo;
	u32 rx_stat_xoffछोड़ोframesreceived_hi;
	u32 rx_stat_xoffछोड़ोframesreceived_lo;
	u32 tx_stat_outxonsent_hi;
	u32 tx_stat_outxonsent_lo;
	u32 tx_stat_outxoffsent_hi;
	u32 tx_stat_outxoffsent_lo;
	u32 tx_stat_flowcontrolकरोne_hi;
	u32 tx_stat_flowcontrolकरोne_lo;
	u32 tx_stat_etherstatscollisions_hi;
	u32 tx_stat_etherstatscollisions_lo;
	u32 tx_stat_करोt3statssinglecollisionframes_hi;
	u32 tx_stat_करोt3statssinglecollisionframes_lo;
	u32 tx_stat_करोt3statsmultiplecollisionframes_hi;
	u32 tx_stat_करोt3statsmultiplecollisionframes_lo;
	u32 tx_stat_करोt3statsdeferredtransmissions_hi;
	u32 tx_stat_करोt3statsdeferredtransmissions_lo;
	u32 tx_stat_करोt3statsexcessivecollisions_hi;
	u32 tx_stat_करोt3statsexcessivecollisions_lo;
	u32 tx_stat_करोt3statslatecollisions_hi;
	u32 tx_stat_करोt3statslatecollisions_lo;
	u32 tx_stat_etherstatspkts64octets_hi;
	u32 tx_stat_etherstatspkts64octets_lo;
	u32 tx_stat_etherstatspkts65octetsto127octets_hi;
	u32 tx_stat_etherstatspkts65octetsto127octets_lo;
	u32 tx_stat_etherstatspkts128octetsto255octets_hi;
	u32 tx_stat_etherstatspkts128octetsto255octets_lo;
	u32 tx_stat_etherstatspkts256octetsto511octets_hi;
	u32 tx_stat_etherstatspkts256octetsto511octets_lo;
	u32 tx_stat_etherstatspkts512octetsto1023octets_hi;
	u32 tx_stat_etherstatspkts512octetsto1023octets_lo;
	u32 tx_stat_etherstatspkts1024octetsto1522octets_hi;
	u32 tx_stat_etherstatspkts1024octetsto1522octets_lo;
	u32 tx_stat_etherstatspktsover1522octets_hi;
	u32 tx_stat_etherstatspktsover1522octets_lo;
	u32 tx_stat_bmac_2047_hi;
	u32 tx_stat_bmac_2047_lo;
	u32 tx_stat_bmac_4095_hi;
	u32 tx_stat_bmac_4095_lo;
	u32 tx_stat_bmac_9216_hi;
	u32 tx_stat_bmac_9216_lo;
	u32 tx_stat_bmac_16383_hi;
	u32 tx_stat_bmac_16383_lo;
	u32 tx_stat_करोt3statsपूर्णांकernalmactransmiterrors_hi;
	u32 tx_stat_करोt3statsपूर्णांकernalmactransmiterrors_lo;
	u32 tx_stat_bmac_ufl_hi;
	u32 tx_stat_bmac_ufl_lo;

	u32 छोड़ो_frames_received_hi;
	u32 छोड़ो_frames_received_lo;
	u32 छोड़ो_frames_sent_hi;
	u32 छोड़ो_frames_sent_lo;

	u32 etherstatspkts1024octetsto1522octets_hi;
	u32 etherstatspkts1024octetsto1522octets_lo;
	u32 etherstatspktsover1522octets_hi;
	u32 etherstatspktsover1522octets_lo;

	u32 brb_drop_hi;
	u32 brb_drop_lo;
	u32 brb_truncate_hi;
	u32 brb_truncate_lo;

	u32 mac_filter_discard;
	u32 mf_tag_discard;
	u32 brb_truncate_discard;
	u32 mac_discard;

	u32 driver_xoff;
	u32 rx_err_discard_pkt;
	u32 rx_skb_alloc_failed;
	u32 hw_csum_err;

	u32 nig_समयr_max;

	/* TPA */
	u32 total_tpa_aggregations_hi;
	u32 total_tpa_aggregations_lo;
	u32 total_tpa_aggregated_frames_hi;
	u32 total_tpa_aggregated_frames_lo;
	u32 total_tpa_bytes_hi;
	u32 total_tpa_bytes_lo;

	/* PFC */
	u32 pfc_frames_received_hi;
	u32 pfc_frames_received_lo;
	u32 pfc_frames_sent_hi;
	u32 pfc_frames_sent_lo;

	/* Recovery */
	u32 recoverable_error;
	u32 unrecoverable_error;
	u32 driver_filtered_tx_pkt;
	/* src: Clear-on-Read रेजिस्टर; Will not survive PMF Migration */
	u32 eee_tx_lpi;

	/* PTP */
	u32 ptp_skip_tx_ts;
पूर्ण;

काष्ठा bnx2x_eth_q_stats अणु
	u32 total_unicast_bytes_received_hi;
	u32 total_unicast_bytes_received_lo;
	u32 total_broadcast_bytes_received_hi;
	u32 total_broadcast_bytes_received_lo;
	u32 total_multicast_bytes_received_hi;
	u32 total_multicast_bytes_received_lo;
	u32 total_bytes_received_hi;
	u32 total_bytes_received_lo;
	u32 total_unicast_bytes_transmitted_hi;
	u32 total_unicast_bytes_transmitted_lo;
	u32 total_broadcast_bytes_transmitted_hi;
	u32 total_broadcast_bytes_transmitted_lo;
	u32 total_multicast_bytes_transmitted_hi;
	u32 total_multicast_bytes_transmitted_lo;
	u32 total_bytes_transmitted_hi;
	u32 total_bytes_transmitted_lo;
	u32 total_unicast_packets_received_hi;
	u32 total_unicast_packets_received_lo;
	u32 total_multicast_packets_received_hi;
	u32 total_multicast_packets_received_lo;
	u32 total_broadcast_packets_received_hi;
	u32 total_broadcast_packets_received_lo;
	u32 total_unicast_packets_transmitted_hi;
	u32 total_unicast_packets_transmitted_lo;
	u32 total_multicast_packets_transmitted_hi;
	u32 total_multicast_packets_transmitted_lo;
	u32 total_broadcast_packets_transmitted_hi;
	u32 total_broadcast_packets_transmitted_lo;
	u32 valid_bytes_received_hi;
	u32 valid_bytes_received_lo;

	u32 etherstatsoverrsizepkts_hi;
	u32 etherstatsoverrsizepkts_lo;
	u32 no_buff_discard_hi;
	u32 no_buff_discard_lo;

	u32 driver_xoff;
	u32 rx_err_discard_pkt;
	u32 rx_skb_alloc_failed;
	u32 hw_csum_err;

	u32 total_packets_received_checksum_discarded_hi;
	u32 total_packets_received_checksum_discarded_lo;
	u32 total_packets_received_ttl0_discarded_hi;
	u32 total_packets_received_ttl0_discarded_lo;
	u32 total_transmitted_dropped_packets_error_hi;
	u32 total_transmitted_dropped_packets_error_lo;

	/* TPA */
	u32 total_tpa_aggregations_hi;
	u32 total_tpa_aggregations_lo;
	u32 total_tpa_aggregated_frames_hi;
	u32 total_tpa_aggregated_frames_lo;
	u32 total_tpa_bytes_hi;
	u32 total_tpa_bytes_lo;
	u32 driver_filtered_tx_pkt;
पूर्ण;

काष्ठा bnx2x_eth_stats_old अणु
	u32 rx_stat_करोt3statsframestooदीर्घ_hi;
	u32 rx_stat_करोt3statsframestooदीर्घ_lo;
पूर्ण;

काष्ठा bnx2x_eth_q_stats_old अणु
	/* Fields to perserve over fw reset*/
	u32 total_unicast_bytes_received_hi;
	u32 total_unicast_bytes_received_lo;
	u32 total_broadcast_bytes_received_hi;
	u32 total_broadcast_bytes_received_lo;
	u32 total_multicast_bytes_received_hi;
	u32 total_multicast_bytes_received_lo;
	u32 total_unicast_bytes_transmitted_hi;
	u32 total_unicast_bytes_transmitted_lo;
	u32 total_broadcast_bytes_transmitted_hi;
	u32 total_broadcast_bytes_transmitted_lo;
	u32 total_multicast_bytes_transmitted_hi;
	u32 total_multicast_bytes_transmitted_lo;
	u32 total_tpa_bytes_hi;
	u32 total_tpa_bytes_lo;

	/* Fields to perserve last of */
	u32 total_bytes_received_hi;
	u32 total_bytes_received_lo;
	u32 total_bytes_transmitted_hi;
	u32 total_bytes_transmitted_lo;
	u32 total_unicast_packets_received_hi;
	u32 total_unicast_packets_received_lo;
	u32 total_multicast_packets_received_hi;
	u32 total_multicast_packets_received_lo;
	u32 total_broadcast_packets_received_hi;
	u32 total_broadcast_packets_received_lo;
	u32 total_unicast_packets_transmitted_hi;
	u32 total_unicast_packets_transmitted_lo;
	u32 total_multicast_packets_transmitted_hi;
	u32 total_multicast_packets_transmitted_lo;
	u32 total_broadcast_packets_transmitted_hi;
	u32 total_broadcast_packets_transmitted_lo;
	u32 valid_bytes_received_hi;
	u32 valid_bytes_received_lo;

	u32 total_tpa_bytes_hi_old;
	u32 total_tpa_bytes_lo_old;

	u32 driver_xoff_old;
	u32 rx_err_discard_pkt_old;
	u32 rx_skb_alloc_failed_old;
	u32 hw_csum_err_old;
	u32 driver_filtered_tx_pkt_old;
पूर्ण;

काष्ठा bnx2x_net_stats_old अणु
	 u32 rx_dropped;
पूर्ण;

काष्ठा bnx2x_fw_port_stats_old अणु
	 u32 mac_filter_discard;
	 u32 mf_tag_discard;
	 u32 brb_truncate_discard;
	 u32 mac_discard;
पूर्ण;

/****************************************************************************
* Macros
****************************************************************************/

/* sum[hi:lo] += add[hi:lo] */
#घोषणा ADD_64(s_hi, a_hi, s_lo, a_lo) \
	करो अणु \
		s_lo += a_lo; \
		s_hi += a_hi + ((s_lo < a_lo) ? 1 : 0); \
	पूर्ण जबतक (0)

#घोषणा LE32_0 ((__क्रमce __le32) 0)
#घोषणा LE16_0 ((__क्रमce __le16) 0)

/* The _क्रमce is क्रम हालs where high value is 0 */
#घोषणा ADD_64_LE(s_hi, a_hi_le, s_lo, a_lo_le) \
		ADD_64(s_hi, le32_to_cpu(a_hi_le), \
		       s_lo, le32_to_cpu(a_lo_le))

#घोषणा ADD_64_LE16(s_hi, a_hi_le, s_lo, a_lo_le) \
		ADD_64(s_hi, le16_to_cpu(a_hi_le), \
		       s_lo, le16_to_cpu(a_lo_le))

/* dअगरference = minuend - subtrahend */
#घोषणा DIFF_64(d_hi, m_hi, s_hi, d_lo, m_lo, s_lo) \
	करो अणु \
		अगर (m_lo < s_lo) अणु \
			/* underflow */ \
			d_hi = m_hi - s_hi; \
			अगर (d_hi > 0) अणु \
				/* we can 'loan' 1 */ \
				d_hi--; \
				d_lo = m_lo + (अच_पूर्णांक_उच्च - s_lo) + 1; \
			पूर्ण अन्यथा अणु \
				/* m_hi <= s_hi */ \
				d_hi = 0; \
				d_lo = 0; \
			पूर्ण \
		पूर्ण अन्यथा अणु \
			/* m_lo >= s_lo */ \
			अगर (m_hi < s_hi) अणु \
				d_hi = 0; \
				d_lo = 0; \
			पूर्ण अन्यथा अणु \
				/* m_hi >= s_hi */ \
				d_hi = m_hi - s_hi; \
				d_lo = m_lo - s_lo; \
			पूर्ण \
		पूर्ण \
	पूर्ण जबतक (0)

#घोषणा UPDATE_STAT64(s, t) \
	करो अणु \
		DIFF_64(dअगरf.hi, new->s##_hi, pstats->mac_stx[0].t##_hi, \
			dअगरf.lo, new->s##_lo, pstats->mac_stx[0].t##_lo); \
		pstats->mac_stx[0].t##_hi = new->s##_hi; \
		pstats->mac_stx[0].t##_lo = new->s##_lo; \
		ADD_64(pstats->mac_stx[1].t##_hi, dअगरf.hi, \
		       pstats->mac_stx[1].t##_lo, dअगरf.lo); \
	पूर्ण जबतक (0)

#घोषणा UPDATE_STAT64_NIG(s, t) \
	करो अणु \
		DIFF_64(dअगरf.hi, new->s##_hi, old->s##_hi, \
			dअगरf.lo, new->s##_lo, old->s##_lo); \
		ADD_64(estats->t##_hi, dअगरf.hi, \
		       estats->t##_lo, dअगरf.lo); \
	पूर्ण जबतक (0)

/* sum[hi:lo] += add */
#घोषणा ADD_EXTEND_64(s_hi, s_lo, a) \
	करो अणु \
		s_lo += a; \
		s_hi += (s_lo < a) ? 1 : 0; \
	पूर्ण जबतक (0)

#घोषणा ADD_STAT64(dअगरf, t) \
	करो अणु \
		ADD_64(pstats->mac_stx[1].t##_hi, new->dअगरf##_hi, \
		       pstats->mac_stx[1].t##_lo, new->dअगरf##_lo); \
	पूर्ण जबतक (0)

#घोषणा UPDATE_EXTEND_STAT(s) \
	करो अणु \
		ADD_EXTEND_64(pstats->mac_stx[1].s##_hi, \
			      pstats->mac_stx[1].s##_lo, \
			      new->s); \
	पूर्ण जबतक (0)

#घोषणा UPDATE_EXTEND_TSTAT_X(s, t, size) \
	करो अणु \
		dअगरf = le##size##_to_cpu(tclient->s) - \
		       le##size##_to_cpu(old_tclient->s); \
		old_tclient->s = tclient->s; \
		ADD_EXTEND_64(qstats->t##_hi, qstats->t##_lo, dअगरf); \
	पूर्ण जबतक (0)

#घोषणा UPDATE_EXTEND_TSTAT(s, t) UPDATE_EXTEND_TSTAT_X(s, t, 32)

#घोषणा UPDATE_EXTEND_E_TSTAT(s, t, size) \
	करो अणु \
		UPDATE_EXTEND_TSTAT_X(s, t, size); \
		ADD_EXTEND_64(estats->t##_hi, estats->t##_lo, dअगरf); \
	पूर्ण जबतक (0)

#घोषणा UPDATE_EXTEND_USTAT(s, t) \
	करो अणु \
		dअगरf = le32_to_cpu(uclient->s) - le32_to_cpu(old_uclient->s); \
		old_uclient->s = uclient->s; \
		ADD_EXTEND_64(qstats->t##_hi, qstats->t##_lo, dअगरf); \
	पूर्ण जबतक (0)

#घोषणा UPDATE_EXTEND_E_USTAT(s, t) \
	करो अणु \
		UPDATE_EXTEND_USTAT(s, t); \
		ADD_EXTEND_64(estats->t##_hi, estats->t##_lo, dअगरf); \
	पूर्ण जबतक (0)

#घोषणा UPDATE_EXTEND_XSTAT(s, t) \
	करो अणु \
		dअगरf = le32_to_cpu(xclient->s) - le32_to_cpu(old_xclient->s); \
		old_xclient->s = xclient->s; \
		ADD_EXTEND_64(qstats->t##_hi, qstats->t##_lo, dअगरf); \
	पूर्ण जबतक (0)

#घोषणा UPDATE_QSTAT(s, t) \
	करो अणु \
		qstats->t##_lo = qstats_old->t##_lo + le32_to_cpu(s.lo); \
		qstats->t##_hi = qstats_old->t##_hi + le32_to_cpu(s.hi) \
			+ ((qstats->t##_lo < qstats_old->t##_lo) ? 1 : 0); \
	पूर्ण जबतक (0)

#घोषणा UPDATE_QSTAT_OLD(f) \
	करो अणु \
		qstats_old->f = qstats->f; \
	पूर्ण जबतक (0)

#घोषणा UPDATE_ESTAT_QSTAT_64(s) \
	करो अणु \
		ADD_64(estats->s##_hi, qstats->s##_hi, \
		       estats->s##_lo, qstats->s##_lo); \
		SUB_64(estats->s##_hi, qstats_old->s##_hi_old, \
		       estats->s##_lo, qstats_old->s##_lo_old); \
		qstats_old->s##_hi_old = qstats->s##_hi; \
		qstats_old->s##_lo_old = qstats->s##_lo; \
	पूर्ण जबतक (0)

#घोषणा UPDATE_ESTAT_QSTAT(s) \
	करो अणु \
		estats->s += qstats->s; \
		estats->s -= qstats_old->s##_old; \
		qstats_old->s##_old = qstats->s; \
	पूर्ण जबतक (0)

#घोषणा UPDATE_FSTAT_QSTAT(s) \
	करो अणु \
		ADD_64(ख_स्थितिs->s##_hi, qstats->s##_hi, \
		       ख_स्थितिs->s##_lo, qstats->s##_lo); \
		SUB_64(ख_स्थितिs->s##_hi, qstats_old->s##_hi, \
		       ख_स्थितिs->s##_lo, qstats_old->s##_lo); \
		estats->s##_hi = ख_स्थितिs->s##_hi; \
		estats->s##_lo = ख_स्थितिs->s##_lo; \
		qstats_old->s##_hi = qstats->s##_hi; \
		qstats_old->s##_lo = qstats->s##_lo; \
	पूर्ण जबतक (0)

#घोषणा UPDATE_FW_STAT(s) \
	करो अणु \
		estats->s = le32_to_cpu(tport->s) + fwstats->s; \
	पूर्ण जबतक (0)

#घोषणा UPDATE_FW_STAT_OLD(f) \
	करो अणु \
		fwstats->f = estats->f; \
	पूर्ण जबतक (0)

#घोषणा UPDATE_ESTAT(s, t) \
	करो अणु \
		SUB_64(estats->s##_hi, estats_old->t##_hi, \
		       estats->s##_lo, estats_old->t##_lo); \
		ADD_64(estats->s##_hi, estats->t##_hi, \
		       estats->s##_lo, estats->t##_lo); \
		estats_old->t##_hi = estats->t##_hi; \
		estats_old->t##_lo = estats->t##_lo; \
	पूर्ण जबतक (0)

/* minuend -= subtrahend */
#घोषणा SUB_64(m_hi, s_hi, m_lo, s_lo) \
	करो अणु \
		DIFF_64(m_hi, m_hi, s_hi, m_lo, m_lo, s_lo); \
	पूर्ण जबतक (0)

/* minuend[hi:lo] -= subtrahend */
#घोषणा SUB_EXTEND_64(m_hi, m_lo, s) \
	करो अणु \
		SUB_64(m_hi, 0, m_lo, s); \
	पूर्ण जबतक (0)

#घोषणा SUB_EXTEND_USTAT(s, t) \
	करो अणु \
		dअगरf = le32_to_cpu(uclient->s) - le32_to_cpu(old_uclient->s); \
		SUB_EXTEND_64(qstats->t##_hi, qstats->t##_lo, dअगरf); \
	पूर्ण जबतक (0)

/* क्रमward */
काष्ठा bnx2x;

व्योम bnx2x_स_रखो_stats(काष्ठा bnx2x *bp);
व्योम bnx2x_stats_init(काष्ठा bnx2x *bp);
व्योम bnx2x_stats_handle(काष्ठा bnx2x *bp, क्रमागत bnx2x_stats_event event);
पूर्णांक bnx2x_stats_safe_exec(काष्ठा bnx2x *bp,
			  व्योम (func_to_exec)(व्योम *cookie),
			  व्योम *cookie);

/**
 * bnx2x_save_statistics - save statistics when unloading.
 *
 * @bp:		driver handle
 */
व्योम bnx2x_save_statistics(काष्ठा bnx2x *bp);

व्योम bnx2x_afex_collect_stats(काष्ठा bnx2x *bp, व्योम *व्योम_afex_stats,
			      u32 stats_type);
#पूर्ण_अगर /* BNX2X_STATS_H */
