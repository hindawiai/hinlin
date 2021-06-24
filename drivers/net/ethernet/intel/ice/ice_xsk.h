<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright (c) 2019, Intel Corporation. */

#अगर_अघोषित _ICE_XSK_H_
#घोषणा _ICE_XSK_H_
#समावेश "ice_txrx.h"
#समावेश "ice.h"

काष्ठा ice_vsi;

#अगर_घोषित CONFIG_XDP_SOCKETS
पूर्णांक ice_xsk_pool_setup(काष्ठा ice_vsi *vsi, काष्ठा xsk_buff_pool *pool,
		       u16 qid);
पूर्णांक ice_clean_rx_irq_zc(काष्ठा ice_ring *rx_ring, पूर्णांक budget);
bool ice_clean_tx_irq_zc(काष्ठा ice_ring *xdp_ring, पूर्णांक budget);
पूर्णांक ice_xsk_wakeup(काष्ठा net_device *netdev, u32 queue_id, u32 flags);
bool ice_alloc_rx_bufs_zc(काष्ठा ice_ring *rx_ring, u16 count);
bool ice_xsk_any_rx_ring_ena(काष्ठा ice_vsi *vsi);
व्योम ice_xsk_clean_rx_ring(काष्ठा ice_ring *rx_ring);
व्योम ice_xsk_clean_xdp_ring(काष्ठा ice_ring *xdp_ring);
#अन्यथा
अटल अंतरभूत पूर्णांक
ice_xsk_pool_setup(काष्ठा ice_vsi __always_unused *vsi,
		   काष्ठा xsk_buff_pool __always_unused *pool,
		   u16 __always_unused qid)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक
ice_clean_rx_irq_zc(काष्ठा ice_ring __always_unused *rx_ring,
		    पूर्णांक __always_unused budget)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत bool
ice_clean_tx_irq_zc(काष्ठा ice_ring __always_unused *xdp_ring,
		    पूर्णांक __always_unused budget)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत bool
ice_alloc_rx_bufs_zc(काष्ठा ice_ring __always_unused *rx_ring,
		     u16 __always_unused count)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत bool ice_xsk_any_rx_ring_ena(काष्ठा ice_vsi __always_unused *vsi)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत पूर्णांक
ice_xsk_wakeup(काष्ठा net_device __always_unused *netdev,
	       u32 __always_unused queue_id, u32 __always_unused flags)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

#घोषणा ice_xsk_clean_rx_ring(rx_ring) करो अणुपूर्ण जबतक (0)
#घोषणा ice_xsk_clean_xdp_ring(xdp_ring) करो अणुपूर्ण जबतक (0)
#पूर्ण_अगर /* CONFIG_XDP_SOCKETS */
#पूर्ण_अगर /* !_ICE_XSK_H_ */
