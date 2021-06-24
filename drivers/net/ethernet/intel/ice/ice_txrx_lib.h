<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright (c) 2019, Intel Corporation. */

#अगर_अघोषित _ICE_TXRX_LIB_H_
#घोषणा _ICE_TXRX_LIB_H_
#समावेश "ice.h"

/**
 * ice_test_staterr - tests bits in Rx descriptor status and error fields
 * @rx_desc: poपूर्णांकer to receive descriptor (in le64 क्रमmat)
 * @stat_err_bits: value to mask
 *
 * This function करोes some fast chicanery in order to वापस the
 * value of the mask which is really only used क्रम boolean tests.
 * The status_error_len करोesn't need to be shअगरted because it begins
 * at offset zero.
 */
अटल अंतरभूत bool
ice_test_staterr(जोड़ ice_32b_rx_flex_desc *rx_desc, स्थिर u16 stat_err_bits)
अणु
	वापस !!(rx_desc->wb.status_error0 & cpu_to_le16(stat_err_bits));
पूर्ण

अटल अंतरभूत __le64
ice_build_ctob(u64 td_cmd, u64 td_offset, अचिन्हित पूर्णांक size, u64 td_tag)
अणु
	वापस cpu_to_le64(ICE_TX_DESC_DTYPE_DATA |
			   (td_cmd    << ICE_TXD_QW1_CMD_S) |
			   (td_offset << ICE_TXD_QW1_OFFSET_S) |
			   ((u64)size << ICE_TXD_QW1_TX_BUF_SZ_S) |
			   (td_tag    << ICE_TXD_QW1_L2TAG1_S));
पूर्ण

/**
 * ice_xdp_ring_update_tail - Updates the XDP Tx ring tail रेजिस्टर
 * @xdp_ring: XDP Tx ring
 *
 * This function updates the XDP Tx ring tail रेजिस्टर.
 */
अटल अंतरभूत व्योम ice_xdp_ring_update_tail(काष्ठा ice_ring *xdp_ring)
अणु
	/* Force memory ग_लिखोs to complete beक्रमe letting h/w
	 * know there are new descriptors to fetch.
	 */
	wmb();
	ग_लिखोl_relaxed(xdp_ring->next_to_use, xdp_ring->tail);
पूर्ण

व्योम ice_finalize_xdp_rx(काष्ठा ice_ring *rx_ring, अचिन्हित पूर्णांक xdp_res);
पूर्णांक ice_xmit_xdp_buff(काष्ठा xdp_buff *xdp, काष्ठा ice_ring *xdp_ring);
पूर्णांक ice_xmit_xdp_ring(व्योम *data, u16 size, काष्ठा ice_ring *xdp_ring);
व्योम ice_release_rx_desc(काष्ठा ice_ring *rx_ring, u16 val);
व्योम
ice_process_skb_fields(काष्ठा ice_ring *rx_ring,
		       जोड़ ice_32b_rx_flex_desc *rx_desc,
		       काष्ठा sk_buff *skb, u8 ptype);
व्योम
ice_receive_skb(काष्ठा ice_ring *rx_ring, काष्ठा sk_buff *skb, u16 vlan_tag);
#पूर्ण_अगर /* !_ICE_TXRX_LIB_H_ */
