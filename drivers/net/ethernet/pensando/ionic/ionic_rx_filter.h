<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright(c) 2017 - 2019 Pensanकरो Systems, Inc */

#अगर_अघोषित _IONIC_RX_FILTER_H_
#घोषणा _IONIC_RX_FILTER_H_

#घोषणा IONIC_RXQ_INDEX_ANY		(0xFFFF)
काष्ठा ionic_rx_filter अणु
	u32 flow_id;
	u32 filter_id;
	u16 rxq_index;
	काष्ठा ionic_rx_filter_add_cmd cmd;
	काष्ठा hlist_node by_hash;
	काष्ठा hlist_node by_id;
पूर्ण;

#घोषणा IONIC_RX_FILTER_HASH_BITS	10
#घोषणा IONIC_RX_FILTER_HLISTS		BIT(IONIC_RX_FILTER_HASH_BITS)
#घोषणा IONIC_RX_FILTER_HLISTS_MASK	(IONIC_RX_FILTER_HLISTS - 1)
काष्ठा ionic_rx_filters अणु
	spinlock_t lock;				    /* filter list lock */
	काष्ठा hlist_head by_hash[IONIC_RX_FILTER_HLISTS];  /* by skb hash */
	काष्ठा hlist_head by_id[IONIC_RX_FILTER_HLISTS];    /* by filter_id */
पूर्ण;

व्योम ionic_rx_filter_मुक्त(काष्ठा ionic_lअगर *lअगर, काष्ठा ionic_rx_filter *f);
व्योम ionic_rx_filter_replay(काष्ठा ionic_lअगर *lअगर);
पूर्णांक ionic_rx_filters_init(काष्ठा ionic_lअगर *lअगर);
व्योम ionic_rx_filters_deinit(काष्ठा ionic_lअगर *lअगर);
पूर्णांक ionic_rx_filter_save(काष्ठा ionic_lअगर *lअगर, u32 flow_id, u16 rxq_index,
			 u32 hash, काष्ठा ionic_admin_ctx *ctx);
काष्ठा ionic_rx_filter *ionic_rx_filter_by_vlan(काष्ठा ionic_lअगर *lअगर, u16 vid);
काष्ठा ionic_rx_filter *ionic_rx_filter_by_addr(काष्ठा ionic_lअगर *lअगर, स्थिर u8 *addr);
काष्ठा ionic_rx_filter *ionic_rx_filter_rxsteer(काष्ठा ionic_lअगर *lअगर);

#पूर्ण_अगर /* _IONIC_RX_FILTER_H_ */
