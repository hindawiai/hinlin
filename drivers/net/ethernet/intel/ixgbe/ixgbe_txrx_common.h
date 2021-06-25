<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright(c) 2018 Intel Corporation. */

#अगर_अघोषित _IXGBE_TXRX_COMMON_H_
#घोषणा _IXGBE_TXRX_COMMON_H_

#घोषणा IXGBE_XDP_PASS		0
#घोषणा IXGBE_XDP_CONSUMED	BIT(0)
#घोषणा IXGBE_XDP_TX		BIT(1)
#घोषणा IXGBE_XDP_REसूची		BIT(2)

#घोषणा IXGBE_TXD_CMD (IXGBE_TXD_CMD_EOP | \
		       IXGBE_TXD_CMD_RS)

पूर्णांक ixgbe_xmit_xdp_ring(काष्ठा ixgbe_adapter *adapter,
			काष्ठा xdp_frame *xdpf);
bool ixgbe_cleanup_headers(काष्ठा ixgbe_ring *rx_ring,
			   जोड़ ixgbe_adv_rx_desc *rx_desc,
			   काष्ठा sk_buff *skb);
व्योम ixgbe_process_skb_fields(काष्ठा ixgbe_ring *rx_ring,
			      जोड़ ixgbe_adv_rx_desc *rx_desc,
			      काष्ठा sk_buff *skb);
व्योम ixgbe_rx_skb(काष्ठा ixgbe_q_vector *q_vector,
		  काष्ठा sk_buff *skb);
व्योम ixgbe_xdp_ring_update_tail(काष्ठा ixgbe_ring *ring);
व्योम ixgbe_irq_rearm_queues(काष्ठा ixgbe_adapter *adapter, u64 qmask);

व्योम ixgbe_txrx_ring_disable(काष्ठा ixgbe_adapter *adapter, पूर्णांक ring);
व्योम ixgbe_txrx_ring_enable(काष्ठा ixgbe_adapter *adapter, पूर्णांक ring);

काष्ठा xsk_buff_pool *ixgbe_xsk_pool(काष्ठा ixgbe_adapter *adapter,
				     काष्ठा ixgbe_ring *ring);
पूर्णांक ixgbe_xsk_pool_setup(काष्ठा ixgbe_adapter *adapter,
			 काष्ठा xsk_buff_pool *pool,
			 u16 qid);

व्योम ixgbe_zca_मुक्त(काष्ठा zero_copy_allocator *alloc, अचिन्हित दीर्घ handle);

bool ixgbe_alloc_rx_buffers_zc(काष्ठा ixgbe_ring *rx_ring, u16 cleaned_count);
पूर्णांक ixgbe_clean_rx_irq_zc(काष्ठा ixgbe_q_vector *q_vector,
			  काष्ठा ixgbe_ring *rx_ring,
			  स्थिर पूर्णांक budget);
व्योम ixgbe_xsk_clean_rx_ring(काष्ठा ixgbe_ring *rx_ring);
bool ixgbe_clean_xdp_tx_irq(काष्ठा ixgbe_q_vector *q_vector,
			    काष्ठा ixgbe_ring *tx_ring, पूर्णांक napi_budget);
पूर्णांक ixgbe_xsk_wakeup(काष्ठा net_device *dev, u32 queue_id, u32 flags);
व्योम ixgbe_xsk_clean_tx_ring(काष्ठा ixgbe_ring *tx_ring);

#पूर्ण_अगर /* #घोषणा _IXGBE_TXRX_COMMON_H_ */
