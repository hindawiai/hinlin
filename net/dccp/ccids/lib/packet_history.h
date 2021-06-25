<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *  Packet RX/TX history data काष्ठाures and routines क्रम TFRC-based protocols.
 *
 *  Copyright (c) 2007   The University of Aberdeen, Scotland, UK
 *  Copyright (c) 2005-6 The University of Waikato, Hamilton, New Zealand.
 *
 *  This code has been developed by the University of Waikato WAND
 *  research group. For further inक्रमmation please see https://www.wand.net.nz/
 *  or e-mail Ian McDonald - ian.mcकरोnald@jandi.co.nz
 *
 *  This code also uses code from Lulea University, rereleased as GPL by its
 *  authors:
 *  Copyright (c) 2003 Nils-Erik Mattsson, Joacim Haggmark, Magnus Erixzon
 *
 *  Changes to meet Linux coding standards, to make it meet latest ccid3 draft
 *  and to make it work as a loadable module in the DCCP stack written by
 *  Arnalकरो Carvalho de Melo <acme@conectiva.com.br>.
 *
 *  Copyright (c) 2005 Arnalकरो Carvalho de Melo <acme@conectiva.com.br>
 */

#अगर_अघोषित _DCCP_PKT_HIST_
#घोषणा _DCCP_PKT_HIST_

#समावेश <linux/list.h>
#समावेश <linux/slab.h>
#समावेश "tfrc.h"

/**
 *  tfrc_tx_hist_entry  -  Simple singly-linked TX history list
 *  @next:  next oldest entry (LIFO order)
 *  @seqno: sequence number of this entry
 *  @stamp: send समय of packet with sequence number @seqno
 */
काष्ठा tfrc_tx_hist_entry अणु
	काष्ठा tfrc_tx_hist_entry *next;
	u64			  seqno;
	kसमय_प्रकार			  stamp;
पूर्ण;

अटल अंतरभूत काष्ठा tfrc_tx_hist_entry *
	tfrc_tx_hist_find_entry(काष्ठा tfrc_tx_hist_entry *head, u64 seqno)
अणु
	जबतक (head != शून्य && head->seqno != seqno)
		head = head->next;
	वापस head;
पूर्ण

पूर्णांक tfrc_tx_hist_add(काष्ठा tfrc_tx_hist_entry **headp, u64 seqno);
व्योम tfrc_tx_hist_purge(काष्ठा tfrc_tx_hist_entry **headp);

/* Subtraction a-b modulo-16, respects circular wrap-around */
#घोषणा SUB16(a, b) (((a) + 16 - (b)) & 0xF)

/* Number of packets to रुको after a missing packet (RFC 4342, 6.1) */
#घोषणा TFRC_NDUPACK 3

/**
 * tfrc_rx_hist_entry - Store inक्रमmation about a single received packet
 * @tfrchrx_seqno:	DCCP packet sequence number
 * @tfrchrx_ccval:	winकरोw counter value of packet (RFC 4342, 8.1)
 * @tfrchrx_ndp:	the NDP count (अगर any) of the packet
 * @tfrchrx_tstamp:	actual receive समय of packet
 */
काष्ठा tfrc_rx_hist_entry अणु
	u64		 tfrchrx_seqno:48,
			 tfrchrx_ccval:4,
			 tfrchrx_type:4;
	u64		 tfrchrx_ndp:48;
	kसमय_प्रकार		 tfrchrx_tstamp;
पूर्ण;

/**
 * tfrc_rx_hist  -  RX history काष्ठाure क्रम TFRC-based protocols
 * @ring:		Packet history क्रम RTT sampling and loss detection
 * @loss_count:		Number of entries in circular history
 * @loss_start:		Movable index (क्रम loss detection)
 * @rtt_sample_prev:	Used during RTT sampling, poपूर्णांकs to candidate entry
 */
काष्ठा tfrc_rx_hist अणु
	काष्ठा tfrc_rx_hist_entry *ring[TFRC_NDUPACK + 1];
	u8			  loss_count:2,
				  loss_start:2;
#घोषणा rtt_sample_prev		  loss_start
पूर्ण;

/**
 * tfrc_rx_hist_index - index to reach n-th entry after loss_start
 */
अटल अंतरभूत u8 tfrc_rx_hist_index(स्थिर काष्ठा tfrc_rx_hist *h, स्थिर u8 n)
अणु
	वापस (h->loss_start + n) & TFRC_NDUPACK;
पूर्ण

/**
 * tfrc_rx_hist_last_rcv - entry with highest-received-seqno so far
 */
अटल अंतरभूत काष्ठा tfrc_rx_hist_entry *
			tfrc_rx_hist_last_rcv(स्थिर काष्ठा tfrc_rx_hist *h)
अणु
	वापस h->ring[tfrc_rx_hist_index(h, h->loss_count)];
पूर्ण

/**
 * tfrc_rx_hist_entry - वापस the n-th history entry after loss_start
 */
अटल अंतरभूत काष्ठा tfrc_rx_hist_entry *
			tfrc_rx_hist_entry(स्थिर काष्ठा tfrc_rx_hist *h, स्थिर u8 n)
अणु
	वापस h->ring[tfrc_rx_hist_index(h, n)];
पूर्ण

/**
 * tfrc_rx_hist_loss_prev - entry with highest-received-seqno beक्रमe loss was detected
 */
अटल अंतरभूत काष्ठा tfrc_rx_hist_entry *
			tfrc_rx_hist_loss_prev(स्थिर काष्ठा tfrc_rx_hist *h)
अणु
	वापस h->ring[h->loss_start];
पूर्ण

/* indicate whether previously a packet was detected missing */
अटल अंतरभूत bool tfrc_rx_hist_loss_pending(स्थिर काष्ठा tfrc_rx_hist *h)
अणु
	वापस h->loss_count > 0;
पूर्ण

व्योम tfrc_rx_hist_add_packet(काष्ठा tfrc_rx_hist *h, स्थिर काष्ठा sk_buff *skb,
			     स्थिर u64 ndp);

पूर्णांक tfrc_rx_hist_duplicate(काष्ठा tfrc_rx_hist *h, काष्ठा sk_buff *skb);

काष्ठा tfrc_loss_hist;
पूर्णांक tfrc_rx_handle_loss(काष्ठा tfrc_rx_hist *h, काष्ठा tfrc_loss_hist *lh,
			काष्ठा sk_buff *skb, स्थिर u64 ndp,
			u32 (*first_li)(काष्ठा sock *sk), काष्ठा sock *sk);
u32 tfrc_rx_hist_sample_rtt(काष्ठा tfrc_rx_hist *h, स्थिर काष्ठा sk_buff *skb);
पूर्णांक tfrc_rx_hist_alloc(काष्ठा tfrc_rx_hist *h);
व्योम tfrc_rx_hist_purge(काष्ठा tfrc_rx_hist *h);

#पूर्ण_अगर /* _DCCP_PKT_HIST_ */
