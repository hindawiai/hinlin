<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Applied Micro X-Gene SoC Ethernet v2 Driver
 *
 * Copyright (c) 2017, Applied Micro Circuits Corporation
 * Author(s): Iyappan Subramanian <isubramanian@apm.com>
 *	      Keyur Chudgar <kchudgar@apm.com>
 */

#समावेश "main.h"

/* create circular linked list of descriptors */
व्योम xge_setup_desc(काष्ठा xge_desc_ring *ring)
अणु
	काष्ठा xge_raw_desc *raw_desc;
	dma_addr_t dma_h, next_dma;
	u16 offset;
	पूर्णांक i;

	क्रम (i = 0; i < XGENE_ENET_NUM_DESC; i++) अणु
		raw_desc = &ring->raw_desc[i];

		offset = (i + 1) & (XGENE_ENET_NUM_DESC - 1);
		next_dma = ring->dma_addr + (offset * XGENE_ENET_DESC_SIZE);

		raw_desc->m0 = cpu_to_le64(SET_BITS(E, 1) |
					   SET_BITS(PKT_SIZE, SLOT_EMPTY));
		dma_h = upper_32_bits(next_dma);
		raw_desc->m1 = cpu_to_le64(SET_BITS(NEXT_DESC_ADDRL, next_dma) |
					   SET_BITS(NEXT_DESC_ADDRH, dma_h));
	पूर्ण
पूर्ण

व्योम xge_update_tx_desc_addr(काष्ठा xge_pdata *pdata)
अणु
	काष्ठा xge_desc_ring *ring = pdata->tx_ring;
	dma_addr_t dma_addr = ring->dma_addr;

	xge_wr_csr(pdata, DMATXDESCL, dma_addr);
	xge_wr_csr(pdata, DMATXDESCH, upper_32_bits(dma_addr));

	ring->head = 0;
	ring->tail = 0;
पूर्ण

व्योम xge_update_rx_desc_addr(काष्ठा xge_pdata *pdata)
अणु
	काष्ठा xge_desc_ring *ring = pdata->rx_ring;
	dma_addr_t dma_addr = ring->dma_addr;

	xge_wr_csr(pdata, DMARXDESCL, dma_addr);
	xge_wr_csr(pdata, DMARXDESCH, upper_32_bits(dma_addr));

	ring->head = 0;
	ring->tail = 0;
पूर्ण

व्योम xge_पूर्णांकr_enable(काष्ठा xge_pdata *pdata)
अणु
	u32 data;

	data = RX_PKT_RCVD | TX_PKT_SENT;
	xge_wr_csr(pdata, DMAINTRMASK, data);
पूर्ण

व्योम xge_पूर्णांकr_disable(काष्ठा xge_pdata *pdata)
अणु
	xge_wr_csr(pdata, DMAINTRMASK, 0);
पूर्ण
