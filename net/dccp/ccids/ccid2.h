<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *  Copyright (c) 2005 Andrea Bittau <a.bittau@cs.ucl.ac.uk>
 */
#अगर_अघोषित _DCCP_CCID2_H_
#घोषणा _DCCP_CCID2_H_

#समावेश <linux/समयr.h>
#समावेश <linux/types.h>
#समावेश "../ccid.h"
#समावेश "../dccp.h"

/*
 * CCID-2 बारtamping faces the same issues as TCP बारtamping.
 * Hence we reuse/share as much of the code as possible.
 */
#घोषणा ccid2_jअगरfies32	((u32)jअगरfies)

/* NUMDUPACK parameter from RFC 4341, p. 6 */
#घोषणा NUMDUPACK	3

काष्ठा ccid2_seq अणु
	u64			ccid2s_seq;
	u32			ccid2s_sent;
	पूर्णांक			ccid2s_acked;
	काष्ठा ccid2_seq	*ccid2s_prev;
	काष्ठा ccid2_seq	*ccid2s_next;
पूर्ण;

#घोषणा CCID2_SEQBUF_LEN 1024
#घोषणा CCID2_SEQBUF_MAX 128

/*
 * Multiple of congestion winकरोw to keep the sequence winकरोw at
 * (RFC 4340 7.5.2)
 */
#घोषणा CCID2_WIN_CHANGE_FACTOR 5

/**
 * काष्ठा ccid2_hc_tx_sock - CCID2 TX half connection
 * @tx_अणुcwnd,ssthresh,pipeपूर्ण: as per RFC 4341, section 5
 * @tx_packets_acked:	     Ack counter क्रम deriving cwnd growth (RFC 3465)
 * @tx_srtt:		     smoothed RTT estimate, scaled by 2^3
 * @tx_mdev:		     smoothed RTT variation, scaled by 2^2
 * @tx_mdev_max:	     maximum of @mdev during one flight
 * @tx_rttvar:		     moving average/maximum of @mdev_max
 * @tx_rto:		     RTO value deriving from SRTT and RTTVAR (RFC 2988)
 * @tx_rtt_seq:		     to decay RTTVAR at most once per flight
 * @tx_cwnd_used:	     actually used cwnd, W_used of RFC 2861
 * @tx_expected_wnd:	     moving average of @tx_cwnd_used
 * @tx_cwnd_stamp:	     to track idle periods in CWV
 * @tx_lsndसमय:	     last समय (in jअगरfies) a data packet was sent
 * @tx_rpseq:		     last consecutive seqno
 * @tx_rpdupack:	     dupacks since rpseq
 * @tx_av_chunks:	     list of Ack Vectors received on current skb
 */
काष्ठा ccid2_hc_tx_sock अणु
	u32			tx_cwnd;
	u32			tx_ssthresh;
	u32			tx_pipe;
	u32			tx_packets_acked;
	काष्ठा ccid2_seq	*tx_seqbuf[CCID2_SEQBUF_MAX];
	पूर्णांक			tx_seqbufc;
	काष्ठा ccid2_seq	*tx_seqh;
	काष्ठा ccid2_seq	*tx_seqt;

	/* RTT measurement: variables/principles are the same as in TCP */
	u32			tx_srtt,
				tx_mdev,
				tx_mdev_max,
				tx_rttvar,
				tx_rto;
	u64			tx_rtt_seq:48;
	काष्ठा समयr_list	tx_rtoसमयr;
	काष्ठा sock		*sk;

	/* Congestion Winकरोw validation (optional, RFC 2861) */
	u32			tx_cwnd_used,
				tx_expected_wnd,
				tx_cwnd_stamp,
				tx_lsndसमय;

	u64			tx_rpseq;
	पूर्णांक			tx_rpdupack;
	u32			tx_last_cong;
	u64			tx_high_ack;
	काष्ठा list_head	tx_av_chunks;
पूर्ण;

अटल अंतरभूत bool ccid2_cwnd_network_limited(काष्ठा ccid2_hc_tx_sock *hc)
अणु
	वापस hc->tx_pipe >= hc->tx_cwnd;
पूर्ण

/*
 * Convert RFC 3390 larger initial winकरोw पूर्णांकo an equivalent number of packets.
 * This is based on the numbers specअगरied in RFC 5681, 3.1.
 */
अटल अंतरभूत u32 rfc3390_bytes_to_packets(स्थिर u32 smss)
अणु
	वापस smss <= 1095 ? 4 : (smss > 2190 ? 2 : 3);
पूर्ण

/**
 * काष्ठा ccid2_hc_rx_sock  -  Receiving end of CCID-2 half-connection
 * @rx_num_data_pkts: number of data packets received since last feedback
 */
काष्ठा ccid2_hc_rx_sock अणु
	u32	rx_num_data_pkts;
पूर्ण;

अटल अंतरभूत काष्ठा ccid2_hc_tx_sock *ccid2_hc_tx_sk(स्थिर काष्ठा sock *sk)
अणु
	वापस ccid_priv(dccp_sk(sk)->dccps_hc_tx_ccid);
पूर्ण

अटल अंतरभूत काष्ठा ccid2_hc_rx_sock *ccid2_hc_rx_sk(स्थिर काष्ठा sock *sk)
अणु
	वापस ccid_priv(dccp_sk(sk)->dccps_hc_rx_ccid);
पूर्ण
#पूर्ण_अगर /* _DCCP_CCID2_H_ */
