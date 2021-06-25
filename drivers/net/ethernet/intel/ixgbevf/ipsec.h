<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright(c) 2018 Oracle and/or its affiliates. All rights reserved. */

#अगर_अघोषित _IXGBEVF_IPSEC_H_
#घोषणा _IXGBEVF_IPSEC_H_

#घोषणा IXGBE_IPSEC_MAX_SA_COUNT	1024
#घोषणा IXGBE_IPSEC_BASE_RX_INDEX	0
#घोषणा IXGBE_IPSEC_BASE_TX_INDEX	IXGBE_IPSEC_MAX_SA_COUNT
#घोषणा IXGBE_IPSEC_AUTH_BITS		128

#घोषणा IXGBE_RXMOD_VALID		0x00000001
#घोषणा IXGBE_RXMOD_PROTO_ESP		0x00000004
#घोषणा IXGBE_RXMOD_DECRYPT		0x00000008
#घोषणा IXGBE_RXMOD_IPV6		0x00000010

काष्ठा rx_sa अणु
	काष्ठा hlist_node hlist;
	काष्ठा xfrm_state *xs;
	__be32 ipaddr[4];
	u32 key[4];
	u32 salt;
	u32 mode;
	u32 pfsa;
	bool used;
	bool decrypt;
पूर्ण;

काष्ठा rx_ip_sa अणु
	__be32 ipaddr[4];
	u32 ref_cnt;
	bool used;
पूर्ण;

काष्ठा tx_sa अणु
	काष्ठा xfrm_state *xs;
	u32 key[4];
	u32 salt;
	u32 pfsa;
	bool encrypt;
	bool used;
पूर्ण;

काष्ठा ixgbevf_ipsec_tx_data अणु
	u32 flags;
	u16 trailer_len;
	u16 pfsa;
पूर्ण;

काष्ठा ixgbevf_ipsec अणु
	u16 num_rx_sa;
	u16 num_tx_sa;
	काष्ठा rx_sa *rx_tbl;
	काष्ठा tx_sa *tx_tbl;
	DECLARE_HASHTABLE(rx_sa_list, 10);
पूर्ण;

काष्ठा sa_mbx_msg अणु
	__be32 spi;
	u8 flags;
	u8 proto;
	u16 family;
	__be32 addr[4];
	u32 key[5];
पूर्ण;
#पूर्ण_अगर /* _IXGBEVF_IPSEC_H_ */
