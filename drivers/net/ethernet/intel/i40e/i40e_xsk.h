<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright(c) 2018 Intel Corporation. */

#अगर_अघोषित _I40E_XSK_H_
#घोषणा _I40E_XSK_H_

/* This value should match the pragma in the loop_unrolled_क्रम
 * macro. Why 4? It is strictly empirical. It seems to be a good
 * compromise between the advantage of having simultaneous outstanding
 * पढ़ोs to the DMA array that can hide each others latency and the
 * disadvantage of having a larger code path.
 */
#घोषणा PKTS_PER_BATCH 4

#अगर_घोषित __clang__
#घोषणा loop_unrolled_क्रम _Pragma("clang loop unroll_count(4)") क्रम
#या_अगर __GNUC__ >= 8
#घोषणा loop_unrolled_क्रम _Pragma("GCC unroll 4") क्रम
#अन्यथा
#घोषणा loop_unrolled_क्रम क्रम
#पूर्ण_अगर

काष्ठा i40e_vsi;
काष्ठा xsk_buff_pool;
काष्ठा zero_copy_allocator;

पूर्णांक i40e_queue_pair_disable(काष्ठा i40e_vsi *vsi, पूर्णांक queue_pair);
पूर्णांक i40e_queue_pair_enable(काष्ठा i40e_vsi *vsi, पूर्णांक queue_pair);
पूर्णांक i40e_xsk_pool_setup(काष्ठा i40e_vsi *vsi, काष्ठा xsk_buff_pool *pool,
			u16 qid);
bool i40e_alloc_rx_buffers_zc(काष्ठा i40e_ring *rx_ring, u16 cleaned_count);
पूर्णांक i40e_clean_rx_irq_zc(काष्ठा i40e_ring *rx_ring, पूर्णांक budget);

bool i40e_clean_xdp_tx_irq(काष्ठा i40e_vsi *vsi, काष्ठा i40e_ring *tx_ring);
पूर्णांक i40e_xsk_wakeup(काष्ठा net_device *dev, u32 queue_id, u32 flags);
पूर्णांक i40e_alloc_rx_bi_zc(काष्ठा i40e_ring *rx_ring);
व्योम i40e_clear_rx_bi_zc(काष्ठा i40e_ring *rx_ring);

#पूर्ण_अगर /* _I40E_XSK_H_ */
