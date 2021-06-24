<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright (c) 2021, Intel Corporation. */

#अगर_अघोषित _STMMAC_XDP_H_
#घोषणा _STMMAC_XDP_H_

#घोषणा STMMAC_MAX_RX_BUF_SIZE(num)	(((num) * PAGE_SIZE) - XDP_PACKET_HEADROOM)
#घोषणा STMMAC_RX_DMA_ATTR	(DMA_ATTR_SKIP_CPU_SYNC | DMA_ATTR_WEAK_ORDERING)

पूर्णांक sपंचांगmac_xdp_setup_pool(काष्ठा sपंचांगmac_priv *priv, काष्ठा xsk_buff_pool *pool,
			  u16 queue);
पूर्णांक sपंचांगmac_xdp_set_prog(काष्ठा sपंचांगmac_priv *priv, काष्ठा bpf_prog *prog,
			काष्ठा netlink_ext_ack *extack);

#पूर्ण_अगर /* _STMMAC_XDP_H_ */
