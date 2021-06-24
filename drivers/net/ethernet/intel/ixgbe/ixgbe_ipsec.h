<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright(c) 2017 Oracle and/or its affiliates. All rights reserved. */

#अगर_अघोषित _IXGBE_IPSEC_H_
#घोषणा _IXGBE_IPSEC_H_

#घोषणा IXGBE_IPSEC_MAX_SA_COUNT	1024
#घोषणा IXGBE_IPSEC_MAX_RX_IP_COUNT	128
#घोषणा IXGBE_IPSEC_BASE_RX_INDEX	0
#घोषणा IXGBE_IPSEC_BASE_TX_INDEX	IXGBE_IPSEC_MAX_SA_COUNT
#घोषणा IXGBE_IPSEC_AUTH_BITS		128

#घोषणा IXGBE_RXTXIDX_IPS_EN		0x00000001
#घोषणा IXGBE_RXIDX_TBL_SHIFT		1
क्रमागत ixgbe_ipsec_tbl_sel अणु
	ips_rx_ip_tbl	=	0x01,
	ips_rx_spi_tbl	=	0x02,
	ips_rx_key_tbl	=	0x03,
पूर्ण;

#घोषणा IXGBE_RXTXIDX_IDX_SHIFT		3
#घोषणा IXGBE_RXTXIDX_READ		0x40000000
#घोषणा IXGBE_RXTXIDX_WRITE		0x80000000

#घोषणा IXGBE_RXMOD_VALID		0x00000001
#घोषणा IXGBE_RXMOD_PROTO_ESP		0x00000004
#घोषणा IXGBE_RXMOD_DECRYPT		0x00000008
#घोषणा IXGBE_RXMOD_IPV6		0x00000010
#घोषणा IXGBE_RXTXMOD_VF		0x00000020

काष्ठा rx_sa अणु
	काष्ठा hlist_node hlist;
	काष्ठा xfrm_state *xs;
	__be32 ipaddr[4];
	u32 key[4];
	u32 salt;
	u32 mode;
	u8  iptbl_ind;
	bool used;
	bool decrypt;
	u32 vf;
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
	u32 mode;
	bool encrypt;
	bool used;
	u32 vf;
पूर्ण;

काष्ठा ixgbe_ipsec_tx_data अणु
	u32 flags;
	u16 trailer_len;
	u16 sa_idx;
पूर्ण;

काष्ठा ixgbe_ipsec अणु
	u16 num_rx_sa;
	u16 num_tx_sa;
	काष्ठा rx_ip_sa *ip_tbl;
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
#पूर्ण_अगर /* _IXGBE_IPSEC_H_ */
