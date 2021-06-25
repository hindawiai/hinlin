<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* Applied Micro X-Gene SoC Ethernet Driver
 *
 * Copyright (c) 2015, Applied Micro Circuits Corporation
 * Author: Iyappan Subramanian <isubramanian@apm.com>
 */

#समावेश "xgene_enet_main.h"
#समावेश "xgene_enet_hw.h"
#समावेश "xgene_enet_ring2.h"

अटल व्योम xgene_enet_ring_init(काष्ठा xgene_enet_desc_ring *ring)
अणु
	u32 *ring_cfg = ring->state;
	u64 addr = ring->dma;

	अगर (xgene_enet_ring_owner(ring->id) == RING_OWNER_CPU) अणु
		ring_cfg[0] |= SET_VAL(X2_INTLINE, ring->id & RING_BUFNUM_MASK);
		ring_cfg[3] |= SET_BIT(X2_DEQINTEN);
	पूर्ण
	ring_cfg[0] |= SET_VAL(X2_CFGCRID, 2);

	addr >>= 8;
	ring_cfg[2] |= QCOHERENT | SET_VAL(RINGADDRL, addr);

	addr >>= 27;
	ring_cfg[3] |= SET_VAL(RINGSIZE, ring->cfgsize)
		    | ACCEPTLERR
		    | SET_VAL(RINGADDRH, addr);
	ring_cfg[4] |= SET_VAL(X2_SELTHRSH, 1);
	ring_cfg[5] |= SET_BIT(X2_QBASE_AM) | SET_BIT(X2_MSG_AM);
पूर्ण

अटल व्योम xgene_enet_ring_set_type(काष्ठा xgene_enet_desc_ring *ring)
अणु
	u32 *ring_cfg = ring->state;
	bool is_bufpool;
	u32 val;

	is_bufpool = xgene_enet_is_bufpool(ring->id);
	val = (is_bufpool) ? RING_BUFPOOL : RING_REGULAR;
	ring_cfg[4] |= SET_VAL(X2_RINGTYPE, val);
	अगर (is_bufpool)
		ring_cfg[3] |= SET_VAL(RINGMODE, BUFPOOL_MODE);
पूर्ण

अटल व्योम xgene_enet_ring_set_recombbuf(काष्ठा xgene_enet_desc_ring *ring)
अणु
	u32 *ring_cfg = ring->state;

	ring_cfg[3] |= RECOMBBUF;
	ring_cfg[4] |= SET_VAL(X2_RECOMTIMEOUT, 0x7);
पूर्ण

अटल व्योम xgene_enet_ring_wr32(काष्ठा xgene_enet_desc_ring *ring,
				 u32 offset, u32 data)
अणु
	काष्ठा xgene_enet_pdata *pdata = netdev_priv(ring->ndev);

	ioग_लिखो32(data, pdata->ring_csr_addr + offset);
पूर्ण

अटल व्योम xgene_enet_ग_लिखो_ring_state(काष्ठा xgene_enet_desc_ring *ring)
अणु
	काष्ठा xgene_enet_pdata *pdata = netdev_priv(ring->ndev);
	पूर्णांक i;

	xgene_enet_ring_wr32(ring, CSR_RING_CONFIG, ring->num);
	क्रम (i = 0; i < pdata->ring_ops->num_ring_config; i++) अणु
		xgene_enet_ring_wr32(ring, CSR_RING_WR_BASE + (i * 4),
				     ring->state[i]);
	पूर्ण
पूर्ण

अटल व्योम xgene_enet_clr_ring_state(काष्ठा xgene_enet_desc_ring *ring)
अणु
	स_रखो(ring->state, 0, माप(ring->state));
	xgene_enet_ग_लिखो_ring_state(ring);
पूर्ण

अटल व्योम xgene_enet_set_ring_state(काष्ठा xgene_enet_desc_ring *ring)
अणु
	क्रमागत xgene_ring_owner owner;

	xgene_enet_ring_set_type(ring);

	owner = xgene_enet_ring_owner(ring->id);
	अगर (owner == RING_OWNER_ETH0 || owner == RING_OWNER_ETH1)
		xgene_enet_ring_set_recombbuf(ring);

	xgene_enet_ring_init(ring);
	xgene_enet_ग_लिखो_ring_state(ring);
पूर्ण

अटल व्योम xgene_enet_set_ring_id(काष्ठा xgene_enet_desc_ring *ring)
अणु
	u32 ring_id_val, ring_id_buf;
	bool is_bufpool;

	अगर (xgene_enet_ring_owner(ring->id) == RING_OWNER_CPU)
		वापस;

	is_bufpool = xgene_enet_is_bufpool(ring->id);

	ring_id_val = ring->id & GENMASK(9, 0);
	ring_id_val |= OVERWRITE;

	ring_id_buf = (ring->num << 9) & GENMASK(18, 9);
	ring_id_buf |= PREFETCH_BUF_EN;

	अगर (is_bufpool)
		ring_id_buf |= IS_BUFFER_POOL;

	xgene_enet_ring_wr32(ring, CSR_RING_ID, ring_id_val);
	xgene_enet_ring_wr32(ring, CSR_RING_ID_BUF, ring_id_buf);
पूर्ण

अटल व्योम xgene_enet_clr_desc_ring_id(काष्ठा xgene_enet_desc_ring *ring)
अणु
	u32 ring_id;

	ring_id = ring->id | OVERWRITE;
	xgene_enet_ring_wr32(ring, CSR_RING_ID, ring_id);
	xgene_enet_ring_wr32(ring, CSR_RING_ID_BUF, 0);
पूर्ण

अटल काष्ठा xgene_enet_desc_ring *xgene_enet_setup_ring(
				    काष्ठा xgene_enet_desc_ring *ring)
अणु
	bool is_bufpool;
	u32 addr, i;

	xgene_enet_clr_ring_state(ring);
	xgene_enet_set_ring_state(ring);
	xgene_enet_set_ring_id(ring);

	ring->slots = xgene_enet_get_numslots(ring->id, ring->size);

	is_bufpool = xgene_enet_is_bufpool(ring->id);
	अगर (is_bufpool || xgene_enet_ring_owner(ring->id) != RING_OWNER_CPU)
		वापस ring;

	addr = CSR_VMID0_INTR_MBOX + (4 * (ring->id & RING_BUFNUM_MASK));
	xgene_enet_ring_wr32(ring, addr, ring->irq_mbox_dma >> 10);

	क्रम (i = 0; i < ring->slots; i++)
		xgene_enet_mark_desc_slot_empty(&ring->raw_desc[i]);

	वापस ring;
पूर्ण

अटल व्योम xgene_enet_clear_ring(काष्ठा xgene_enet_desc_ring *ring)
अणु
	xgene_enet_clr_desc_ring_id(ring);
	xgene_enet_clr_ring_state(ring);
पूर्ण

अटल व्योम xgene_enet_wr_cmd(काष्ठा xgene_enet_desc_ring *ring, पूर्णांक count)
अणु
	u32 data = 0;

	अगर (xgene_enet_ring_owner(ring->id) == RING_OWNER_CPU) अणु
		data = SET_VAL(X2_INTLINE, ring->id & RING_BUFNUM_MASK) |
		       INTR_CLEAR;
	पूर्ण
	data |= (count & GENMASK(16, 0));

	ioग_लिखो32(data, ring->cmd);
पूर्ण

अटल u32 xgene_enet_ring_len(काष्ठा xgene_enet_desc_ring *ring)
अणु
	u32 __iomem *cmd_base = ring->cmd_base;
	u32 ring_state, num_msgs;

	ring_state = ioपढ़ो32(&cmd_base[1]);
	num_msgs = GET_VAL(X2_NUMMSGSINQ, ring_state);

	वापस num_msgs;
पूर्ण

अटल व्योम xgene_enet_setup_coalescing(काष्ठा xgene_enet_desc_ring *ring)
अणु
	u32 data = 0x77777777;

	xgene_enet_ring_wr32(ring, CSR_PBM_COAL, 0x8e);
	xgene_enet_ring_wr32(ring, CSR_PBM_CTICK0, data);
	xgene_enet_ring_wr32(ring, CSR_PBM_CTICK1, data);
	xgene_enet_ring_wr32(ring, CSR_PBM_CTICK2, data);
	xgene_enet_ring_wr32(ring, CSR_PBM_CTICK3, data);
	xgene_enet_ring_wr32(ring, CSR_THRESHOLD0_SET1, 0x08);
	xgene_enet_ring_wr32(ring, CSR_THRESHOLD1_SET1, 0x10);
पूर्ण

काष्ठा xgene_ring_ops xgene_ring2_ops = अणु
	.num_ring_config = X2_NUM_RING_CONFIG,
	.num_ring_id_shअगरt = 13,
	.setup = xgene_enet_setup_ring,
	.clear = xgene_enet_clear_ring,
	.wr_cmd = xgene_enet_wr_cmd,
	.len = xgene_enet_ring_len,
	.coalesce = xgene_enet_setup_coalescing,
पूर्ण;
