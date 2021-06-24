<शैली गुरु>
/* Broadcom NetXtreme-C/E network driver.
 *
 * Copyright (c) 2016-2017 Broadcom Limited
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation.
 */

#अगर_अघोषित BNXT_XDP_H
#घोषणा BNXT_XDP_H

काष्ठा bnxt_sw_tx_bd *bnxt_xmit_bd(काष्ठा bnxt *bp,
				   काष्ठा bnxt_tx_ring_info *txr,
				   dma_addr_t mapping, u32 len);
व्योम bnxt_tx_पूर्णांक_xdp(काष्ठा bnxt *bp, काष्ठा bnxt_napi *bnapi, पूर्णांक nr_pkts);
bool bnxt_rx_xdp(काष्ठा bnxt *bp, काष्ठा bnxt_rx_ring_info *rxr, u16 cons,
		 काष्ठा page *page, u8 **data_ptr, अचिन्हित पूर्णांक *len,
		 u8 *event);
पूर्णांक bnxt_xdp(काष्ठा net_device *dev, काष्ठा netdev_bpf *xdp);
पूर्णांक bnxt_xdp_xmit(काष्ठा net_device *dev, पूर्णांक num_frames,
		  काष्ठा xdp_frame **frames, u32 flags);

#पूर्ण_अगर
