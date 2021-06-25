<शैली गुरु>
/*
 * Copyright (c) 2014, Lorenzo Bianconi <lorenzo.bianconi83@gmail.com>
 *
 * Permission to use, copy, modअगरy, and/or distribute this software क्रम any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, सूचीECT, INसूचीECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#अगर_अघोषित DYNACK_H
#घोषणा DYNACK_H

#घोषणा ATH_DYN_BUF	64

काष्ठा ath_hw;
काष्ठा ath_node;

/**
 * काष्ठा ath_dyn_rxbuf - ACK frame ring buffer
 * @h_rb: ring buffer head
 * @t_rb: ring buffer tail
 * @tstamp: ACK RX बारtamp buffer
 */
काष्ठा ath_dyn_rxbuf अणु
	u16 h_rb, t_rb;
	u32 tstamp[ATH_DYN_BUF];
पूर्ण;

काष्ठा ts_info अणु
	u32 tstamp;
	u32 dur;
पूर्ण;

काष्ठा haddr_pair अणु
	u8 h_dest[ETH_ALEN];
	u8 h_src[ETH_ALEN];
पूर्ण;

/**
 * काष्ठा ath_dyn_txbuf - tx frame ring buffer
 * @h_rb: ring buffer head
 * @t_rb: ring buffer tail
 * @addr: dest/src address pair क्रम a given TX frame
 * @ts: TX frame बारtamp buffer
 */
काष्ठा ath_dyn_txbuf अणु
	u16 h_rb, t_rb;
	काष्ठा haddr_pair addr[ATH_DYN_BUF];
	काष्ठा ts_info ts[ATH_DYN_BUF];
पूर्ण;

/**
 * काष्ठा ath_dynack - dynack processing info
 * @enabled: enable dyn ack processing
 * @ackto: current ACK समयout
 * @lto: last ACK समयout computation
 * @nodes: ath_node linked list
 * @qlock: ts queue spinlock
 * @ack_rbf: ACK ts ring buffer
 * @st_rbf: status ts ring buffer
 */
काष्ठा ath_dynack अणु
	bool enabled;
	पूर्णांक ackto;
	अचिन्हित दीर्घ lto;

	काष्ठा list_head nodes;

	/* protect बारtamp queue access */
	spinlock_t qlock;
	काष्ठा ath_dyn_rxbuf ack_rbf;
	काष्ठा ath_dyn_txbuf st_rbf;
पूर्ण;

#अगर defined(CONFIG_ATH9K_DYNACK)
व्योम ath_dynack_reset(काष्ठा ath_hw *ah);
व्योम ath_dynack_node_init(काष्ठा ath_hw *ah, काष्ठा ath_node *an);
व्योम ath_dynack_node_deinit(काष्ठा ath_hw *ah, काष्ठा ath_node *an);
व्योम ath_dynack_init(काष्ठा ath_hw *ah);
व्योम ath_dynack_sample_ack_ts(काष्ठा ath_hw *ah, काष्ठा sk_buff *skb, u32 ts);
व्योम ath_dynack_sample_tx_ts(काष्ठा ath_hw *ah, काष्ठा sk_buff *skb,
			     काष्ठा ath_tx_status *ts,
			     काष्ठा ieee80211_sta *sta);
#अन्यथा
अटल अंतरभूत व्योम ath_dynack_init(काष्ठा ath_hw *ah) अणुपूर्ण
अटल अंतरभूत व्योम ath_dynack_node_init(काष्ठा ath_hw *ah,
					काष्ठा ath_node *an) अणुपूर्ण
अटल अंतरभूत व्योम ath_dynack_node_deinit(काष्ठा ath_hw *ah,
					  काष्ठा ath_node *an) अणुपूर्ण
अटल अंतरभूत व्योम ath_dynack_sample_ack_ts(काष्ठा ath_hw *ah,
					    काष्ठा sk_buff *skb, u32 ts) अणुपूर्ण
अटल अंतरभूत व्योम ath_dynack_sample_tx_ts(काष्ठा ath_hw *ah,
					   काष्ठा sk_buff *skb,
					   काष्ठा ath_tx_status *ts,
					   काष्ठा ieee80211_sta *sta) अणुपूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* DYNACK_H */
