<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/*
 * Copyright (c) 2005-2011 Atheros Communications Inc.
 * Copyright (c) 2011-2017 Qualcomm Atheros, Inc.
 * Copyright (c) 2018 The Linux Foundation. All rights reserved.
 */

#समावेश "hif.h"
#समावेश "ce.h"
#समावेश "debug.h"

/*
 * Support क्रम Copy Engine hardware, which is मुख्यly used क्रम
 * communication between Host and Target over a PCIe पूर्णांकerconnect.
 */

/*
 * A single CopyEngine (CE) comprises two "rings":
 *   a source ring
 *   a destination ring
 *
 * Each ring consists of a number of descriptors which specअगरy
 * an address, length, and meta-data.
 *
 * Typically, one side of the PCIe/AHB/SNOC पूर्णांकerconnect (Host or Target)
 * controls one ring and the other side controls the other ring.
 * The source side chooses when to initiate a transfer and it
 * chooses what to send (buffer address, length). The destination
 * side keeps a supply of "anonymous receive buffers" available and
 * it handles incoming data as it arrives (when the destination
 * receives an पूर्णांकerrupt).
 *
 * The sender may send a simple buffer (address/length) or it may
 * send a small list of buffers.  When a small list is sent, hardware
 * "gathers" these and they end up in a single destination buffer
 * with a single पूर्णांकerrupt.
 *
 * There are several "contexts" managed by this layer -- more, it
 * may seem -- than should be needed. These are provided मुख्यly क्रम
 * maximum flexibility and especially to facilitate a simpler HIF
 * implementation. There are per-CopyEngine recv, send, and watermark
 * contexts. These are supplied by the caller when a recv, send,
 * or watermark handler is established and they are echoed back to
 * the caller when the respective callbacks are invoked. There is
 * also a per-transfer context supplied by the caller when a buffer
 * (or sendlist) is sent and when a buffer is enqueued क्रम recv.
 * These per-transfer contexts are echoed back to the caller when
 * the buffer is sent/received.
 */

अटल अंतरभूत u32 shaकरोw_sr_wr_ind_addr(काष्ठा ath10k *ar,
					काष्ठा ath10k_ce_pipe *ce_state)
अणु
	u32 ce_id = ce_state->id;
	u32 addr = 0;

	चयन (ce_id) अणु
	हाल 0:
		addr = 0x00032000;
		अवरोध;
	हाल 3:
		addr = 0x0003200C;
		अवरोध;
	हाल 4:
		addr = 0x00032010;
		अवरोध;
	हाल 5:
		addr = 0x00032014;
		अवरोध;
	हाल 7:
		addr = 0x0003201C;
		अवरोध;
	शेष:
		ath10k_warn(ar, "invalid CE id: %d", ce_id);
		अवरोध;
	पूर्ण
	वापस addr;
पूर्ण

अटल अंतरभूत u32 shaकरोw_dst_wr_ind_addr(काष्ठा ath10k *ar,
					 काष्ठा ath10k_ce_pipe *ce_state)
अणु
	u32 ce_id = ce_state->id;
	u32 addr = 0;

	चयन (ce_id) अणु
	हाल 1:
		addr = 0x00032034;
		अवरोध;
	हाल 2:
		addr = 0x00032038;
		अवरोध;
	हाल 5:
		addr = 0x00032044;
		अवरोध;
	हाल 7:
		addr = 0x0003204C;
		अवरोध;
	हाल 8:
		addr = 0x00032050;
		अवरोध;
	हाल 9:
		addr = 0x00032054;
		अवरोध;
	हाल 10:
		addr = 0x00032058;
		अवरोध;
	हाल 11:
		addr = 0x0003205C;
		अवरोध;
	शेष:
		ath10k_warn(ar, "invalid CE id: %d", ce_id);
		अवरोध;
	पूर्ण

	वापस addr;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक
ath10k_set_ring_byte(अचिन्हित पूर्णांक offset,
		     काष्ठा ath10k_hw_ce_regs_addr_map *addr_map)
अणु
	वापस ((offset << addr_map->lsb) & addr_map->mask);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक
ath10k_get_ring_byte(अचिन्हित पूर्णांक offset,
		     काष्ठा ath10k_hw_ce_regs_addr_map *addr_map)
अणु
	वापस ((offset & addr_map->mask) >> (addr_map->lsb));
पूर्ण

अटल अंतरभूत u32 ath10k_ce_पढ़ो32(काष्ठा ath10k *ar, u32 offset)
अणु
	काष्ठा ath10k_ce *ce = ath10k_ce_priv(ar);

	वापस ce->bus_ops->पढ़ो32(ar, offset);
पूर्ण

अटल अंतरभूत व्योम ath10k_ce_ग_लिखो32(काष्ठा ath10k *ar, u32 offset, u32 value)
अणु
	काष्ठा ath10k_ce *ce = ath10k_ce_priv(ar);

	ce->bus_ops->ग_लिखो32(ar, offset, value);
पूर्ण

अटल अंतरभूत व्योम ath10k_ce_dest_ring_ग_लिखो_index_set(काष्ठा ath10k *ar,
						       u32 ce_ctrl_addr,
						       अचिन्हित पूर्णांक n)
अणु
	ath10k_ce_ग_लिखो32(ar, ce_ctrl_addr +
			  ar->hw_ce_regs->dst_wr_index_addr, n);
पूर्ण

अटल अंतरभूत u32 ath10k_ce_dest_ring_ग_लिखो_index_get(काष्ठा ath10k *ar,
						      u32 ce_ctrl_addr)
अणु
	वापस ath10k_ce_पढ़ो32(ar, ce_ctrl_addr +
				ar->hw_ce_regs->dst_wr_index_addr);
पूर्ण

अटल अंतरभूत व्योम ath10k_ce_src_ring_ग_लिखो_index_set(काष्ठा ath10k *ar,
						      u32 ce_ctrl_addr,
						      अचिन्हित पूर्णांक n)
अणु
	ath10k_ce_ग_लिखो32(ar, ce_ctrl_addr +
			  ar->hw_ce_regs->sr_wr_index_addr, n);
पूर्ण

अटल अंतरभूत u32 ath10k_ce_src_ring_ग_लिखो_index_get(काष्ठा ath10k *ar,
						     u32 ce_ctrl_addr)
अणु
	वापस ath10k_ce_पढ़ो32(ar, ce_ctrl_addr +
				ar->hw_ce_regs->sr_wr_index_addr);
पूर्ण

अटल अंतरभूत u32 ath10k_ce_src_ring_पढ़ो_index_from_ddr(काष्ठा ath10k *ar,
							 u32 ce_id)
अणु
	काष्ठा ath10k_ce *ce = ath10k_ce_priv(ar);

	वापस ce->vaddr_rri[ce_id] & CE_DDR_RRI_MASK;
पूर्ण

अटल अंतरभूत u32 ath10k_ce_src_ring_पढ़ो_index_get(काष्ठा ath10k *ar,
						    u32 ce_ctrl_addr)
अणु
	काष्ठा ath10k_ce *ce = ath10k_ce_priv(ar);
	u32 ce_id = COPY_ENGINE_ID(ce_ctrl_addr);
	काष्ठा ath10k_ce_pipe *ce_state = &ce->ce_states[ce_id];
	u32 index;

	अगर (ar->hw_params.rri_on_ddr &&
	    (ce_state->attr_flags & CE_ATTR_DIS_INTR))
		index = ath10k_ce_src_ring_पढ़ो_index_from_ddr(ar, ce_id);
	अन्यथा
		index = ath10k_ce_पढ़ो32(ar, ce_ctrl_addr +
					 ar->hw_ce_regs->current_srri_addr);

	वापस index;
पूर्ण

अटल अंतरभूत व्योम
ath10k_ce_shaकरोw_src_ring_ग_लिखो_index_set(काष्ठा ath10k *ar,
					  काष्ठा ath10k_ce_pipe *ce_state,
					  अचिन्हित पूर्णांक value)
अणु
	ath10k_ce_ग_लिखो32(ar, shaकरोw_sr_wr_ind_addr(ar, ce_state), value);
पूर्ण

अटल अंतरभूत व्योम
ath10k_ce_shaकरोw_dest_ring_ग_लिखो_index_set(काष्ठा ath10k *ar,
					   काष्ठा ath10k_ce_pipe *ce_state,
					   अचिन्हित पूर्णांक value)
अणु
	ath10k_ce_ग_लिखो32(ar, shaकरोw_dst_wr_ind_addr(ar, ce_state), value);
पूर्ण

अटल अंतरभूत व्योम ath10k_ce_src_ring_base_addr_set(काष्ठा ath10k *ar,
						    u32 ce_id,
						    u64 addr)
अणु
	काष्ठा ath10k_ce *ce = ath10k_ce_priv(ar);
	काष्ठा ath10k_ce_pipe *ce_state = &ce->ce_states[ce_id];
	u32 ce_ctrl_addr = ath10k_ce_base_address(ar, ce_id);
	u32 addr_lo = lower_32_bits(addr);

	ath10k_ce_ग_लिखो32(ar, ce_ctrl_addr +
			  ar->hw_ce_regs->sr_base_addr_lo, addr_lo);

	अगर (ce_state->ops->ce_set_src_ring_base_addr_hi) अणु
		ce_state->ops->ce_set_src_ring_base_addr_hi(ar, ce_ctrl_addr,
							    addr);
	पूर्ण
पूर्ण

अटल व्योम ath10k_ce_set_src_ring_base_addr_hi(काष्ठा ath10k *ar,
						u32 ce_ctrl_addr,
						u64 addr)
अणु
	u32 addr_hi = upper_32_bits(addr) & CE_DESC_ADDR_HI_MASK;

	ath10k_ce_ग_लिखो32(ar, ce_ctrl_addr +
			  ar->hw_ce_regs->sr_base_addr_hi, addr_hi);
पूर्ण

अटल अंतरभूत व्योम ath10k_ce_src_ring_size_set(काष्ठा ath10k *ar,
					       u32 ce_ctrl_addr,
					       अचिन्हित पूर्णांक n)
अणु
	ath10k_ce_ग_लिखो32(ar, ce_ctrl_addr +
			  ar->hw_ce_regs->sr_size_addr, n);
पूर्ण

अटल अंतरभूत व्योम ath10k_ce_src_ring_dmax_set(काष्ठा ath10k *ar,
					       u32 ce_ctrl_addr,
					       अचिन्हित पूर्णांक n)
अणु
	काष्ठा ath10k_hw_ce_ctrl1 *ctrl_regs = ar->hw_ce_regs->ctrl1_regs;

	u32 ctrl1_addr = ath10k_ce_पढ़ो32(ar, ce_ctrl_addr +
					  ctrl_regs->addr);

	ath10k_ce_ग_लिखो32(ar, ce_ctrl_addr + ctrl_regs->addr,
			  (ctrl1_addr &  ~(ctrl_regs->dmax->mask)) |
			  ath10k_set_ring_byte(n, ctrl_regs->dmax));
पूर्ण

अटल अंतरभूत व्योम ath10k_ce_src_ring_byte_swap_set(काष्ठा ath10k *ar,
						    u32 ce_ctrl_addr,
						    अचिन्हित पूर्णांक n)
अणु
	काष्ठा ath10k_hw_ce_ctrl1 *ctrl_regs = ar->hw_ce_regs->ctrl1_regs;

	u32 ctrl1_addr = ath10k_ce_पढ़ो32(ar, ce_ctrl_addr +
					  ctrl_regs->addr);

	ath10k_ce_ग_लिखो32(ar, ce_ctrl_addr + ctrl_regs->addr,
			  (ctrl1_addr & ~(ctrl_regs->src_ring->mask)) |
			  ath10k_set_ring_byte(n, ctrl_regs->src_ring));
पूर्ण

अटल अंतरभूत व्योम ath10k_ce_dest_ring_byte_swap_set(काष्ठा ath10k *ar,
						     u32 ce_ctrl_addr,
						     अचिन्हित पूर्णांक n)
अणु
	काष्ठा ath10k_hw_ce_ctrl1 *ctrl_regs = ar->hw_ce_regs->ctrl1_regs;

	u32 ctrl1_addr = ath10k_ce_पढ़ो32(ar, ce_ctrl_addr +
					  ctrl_regs->addr);

	ath10k_ce_ग_लिखो32(ar, ce_ctrl_addr + ctrl_regs->addr,
			  (ctrl1_addr & ~(ctrl_regs->dst_ring->mask)) |
			  ath10k_set_ring_byte(n, ctrl_regs->dst_ring));
पूर्ण

अटल अंतरभूत
	u32 ath10k_ce_dest_ring_पढ़ो_index_from_ddr(काष्ठा ath10k *ar, u32 ce_id)
अणु
	काष्ठा ath10k_ce *ce = ath10k_ce_priv(ar);

	वापस (ce->vaddr_rri[ce_id] >> CE_DDR_DRRI_SHIFT) &
		CE_DDR_RRI_MASK;
पूर्ण

अटल अंतरभूत u32 ath10k_ce_dest_ring_पढ़ो_index_get(काष्ठा ath10k *ar,
						     u32 ce_ctrl_addr)
अणु
	काष्ठा ath10k_ce *ce = ath10k_ce_priv(ar);
	u32 ce_id = COPY_ENGINE_ID(ce_ctrl_addr);
	काष्ठा ath10k_ce_pipe *ce_state = &ce->ce_states[ce_id];
	u32 index;

	अगर (ar->hw_params.rri_on_ddr &&
	    (ce_state->attr_flags & CE_ATTR_DIS_INTR))
		index = ath10k_ce_dest_ring_पढ़ो_index_from_ddr(ar, ce_id);
	अन्यथा
		index = ath10k_ce_पढ़ो32(ar, ce_ctrl_addr +
					 ar->hw_ce_regs->current_drri_addr);

	वापस index;
पूर्ण

अटल अंतरभूत व्योम ath10k_ce_dest_ring_base_addr_set(काष्ठा ath10k *ar,
						     u32 ce_id,
						     u64 addr)
अणु
	काष्ठा ath10k_ce *ce = ath10k_ce_priv(ar);
	काष्ठा ath10k_ce_pipe *ce_state = &ce->ce_states[ce_id];
	u32 ce_ctrl_addr = ath10k_ce_base_address(ar, ce_id);
	u32 addr_lo = lower_32_bits(addr);

	ath10k_ce_ग_लिखो32(ar, ce_ctrl_addr +
			  ar->hw_ce_regs->dr_base_addr_lo, addr_lo);

	अगर (ce_state->ops->ce_set_dest_ring_base_addr_hi) अणु
		ce_state->ops->ce_set_dest_ring_base_addr_hi(ar, ce_ctrl_addr,
							     addr);
	पूर्ण
पूर्ण

अटल व्योम ath10k_ce_set_dest_ring_base_addr_hi(काष्ठा ath10k *ar,
						 u32 ce_ctrl_addr,
						 u64 addr)
अणु
	u32 addr_hi = upper_32_bits(addr) & CE_DESC_ADDR_HI_MASK;
	u32 reg_value;

	reg_value = ath10k_ce_पढ़ो32(ar, ce_ctrl_addr +
				     ar->hw_ce_regs->dr_base_addr_hi);
	reg_value &= ~CE_DESC_ADDR_HI_MASK;
	reg_value |= addr_hi;
	ath10k_ce_ग_लिखो32(ar, ce_ctrl_addr +
			  ar->hw_ce_regs->dr_base_addr_hi, reg_value);
पूर्ण

अटल अंतरभूत व्योम ath10k_ce_dest_ring_size_set(काष्ठा ath10k *ar,
						u32 ce_ctrl_addr,
						अचिन्हित पूर्णांक n)
अणु
	ath10k_ce_ग_लिखो32(ar, ce_ctrl_addr +
			  ar->hw_ce_regs->dr_size_addr, n);
पूर्ण

अटल अंतरभूत व्योम ath10k_ce_src_ring_highmark_set(काष्ठा ath10k *ar,
						   u32 ce_ctrl_addr,
						   अचिन्हित पूर्णांक n)
अणु
	काष्ठा ath10k_hw_ce_dst_src_wm_regs *srcr_wm = ar->hw_ce_regs->wm_srcr;
	u32 addr = ath10k_ce_पढ़ो32(ar, ce_ctrl_addr + srcr_wm->addr);

	ath10k_ce_ग_लिखो32(ar, ce_ctrl_addr + srcr_wm->addr,
			  (addr & ~(srcr_wm->wm_high->mask)) |
			  (ath10k_set_ring_byte(n, srcr_wm->wm_high)));
पूर्ण

अटल अंतरभूत व्योम ath10k_ce_src_ring_lowmark_set(काष्ठा ath10k *ar,
						  u32 ce_ctrl_addr,
						  अचिन्हित पूर्णांक n)
अणु
	काष्ठा ath10k_hw_ce_dst_src_wm_regs *srcr_wm = ar->hw_ce_regs->wm_srcr;
	u32 addr = ath10k_ce_पढ़ो32(ar, ce_ctrl_addr + srcr_wm->addr);

	ath10k_ce_ग_लिखो32(ar, ce_ctrl_addr + srcr_wm->addr,
			  (addr & ~(srcr_wm->wm_low->mask)) |
			  (ath10k_set_ring_byte(n, srcr_wm->wm_low)));
पूर्ण

अटल अंतरभूत व्योम ath10k_ce_dest_ring_highmark_set(काष्ठा ath10k *ar,
						    u32 ce_ctrl_addr,
						    अचिन्हित पूर्णांक n)
अणु
	काष्ठा ath10k_hw_ce_dst_src_wm_regs *dstr_wm = ar->hw_ce_regs->wm_dstr;
	u32 addr = ath10k_ce_पढ़ो32(ar, ce_ctrl_addr + dstr_wm->addr);

	ath10k_ce_ग_लिखो32(ar, ce_ctrl_addr + dstr_wm->addr,
			  (addr & ~(dstr_wm->wm_high->mask)) |
			  (ath10k_set_ring_byte(n, dstr_wm->wm_high)));
पूर्ण

अटल अंतरभूत व्योम ath10k_ce_dest_ring_lowmark_set(काष्ठा ath10k *ar,
						   u32 ce_ctrl_addr,
						   अचिन्हित पूर्णांक n)
अणु
	काष्ठा ath10k_hw_ce_dst_src_wm_regs *dstr_wm = ar->hw_ce_regs->wm_dstr;
	u32 addr = ath10k_ce_पढ़ो32(ar, ce_ctrl_addr + dstr_wm->addr);

	ath10k_ce_ग_लिखो32(ar, ce_ctrl_addr + dstr_wm->addr,
			  (addr & ~(dstr_wm->wm_low->mask)) |
			  (ath10k_set_ring_byte(n, dstr_wm->wm_low)));
पूर्ण

अटल अंतरभूत व्योम ath10k_ce_copy_complete_पूर्णांकer_enable(काष्ठा ath10k *ar,
							u32 ce_ctrl_addr)
अणु
	काष्ठा ath10k_hw_ce_host_ie *host_ie = ar->hw_ce_regs->host_ie;

	u32 host_ie_addr = ath10k_ce_पढ़ो32(ar, ce_ctrl_addr +
					    ar->hw_ce_regs->host_ie_addr);

	ath10k_ce_ग_लिखो32(ar, ce_ctrl_addr + ar->hw_ce_regs->host_ie_addr,
			  host_ie_addr | host_ie->copy_complete->mask);
पूर्ण

अटल अंतरभूत व्योम ath10k_ce_copy_complete_पूर्णांकr_disable(काष्ठा ath10k *ar,
							u32 ce_ctrl_addr)
अणु
	काष्ठा ath10k_hw_ce_host_ie *host_ie = ar->hw_ce_regs->host_ie;

	u32 host_ie_addr = ath10k_ce_पढ़ो32(ar, ce_ctrl_addr +
					    ar->hw_ce_regs->host_ie_addr);

	ath10k_ce_ग_लिखो32(ar, ce_ctrl_addr + ar->hw_ce_regs->host_ie_addr,
			  host_ie_addr & ~(host_ie->copy_complete->mask));
पूर्ण

अटल अंतरभूत व्योम ath10k_ce_watermark_पूर्णांकr_disable(काष्ठा ath10k *ar,
						    u32 ce_ctrl_addr)
अणु
	काष्ठा ath10k_hw_ce_host_wm_regs *wm_regs = ar->hw_ce_regs->wm_regs;

	u32 host_ie_addr = ath10k_ce_पढ़ो32(ar, ce_ctrl_addr +
					    ar->hw_ce_regs->host_ie_addr);

	ath10k_ce_ग_लिखो32(ar, ce_ctrl_addr + ar->hw_ce_regs->host_ie_addr,
			  host_ie_addr & ~(wm_regs->wm_mask));
पूर्ण

अटल अंतरभूत व्योम ath10k_ce_error_पूर्णांकr_enable(काष्ठा ath10k *ar,
					       u32 ce_ctrl_addr)
अणु
	काष्ठा ath10k_hw_ce_misc_regs *misc_regs = ar->hw_ce_regs->misc_regs;

	u32 misc_ie_addr = ath10k_ce_पढ़ो32(ar, ce_ctrl_addr +
					    ar->hw_ce_regs->misc_ie_addr);

	ath10k_ce_ग_लिखो32(ar,
			  ce_ctrl_addr + ar->hw_ce_regs->misc_ie_addr,
			  misc_ie_addr | misc_regs->err_mask);
पूर्ण

अटल अंतरभूत व्योम ath10k_ce_error_पूर्णांकr_disable(काष्ठा ath10k *ar,
						u32 ce_ctrl_addr)
अणु
	काष्ठा ath10k_hw_ce_misc_regs *misc_regs = ar->hw_ce_regs->misc_regs;

	u32 misc_ie_addr = ath10k_ce_पढ़ो32(ar,
			ce_ctrl_addr + ar->hw_ce_regs->misc_ie_addr);

	ath10k_ce_ग_लिखो32(ar,
			  ce_ctrl_addr + ar->hw_ce_regs->misc_ie_addr,
			  misc_ie_addr & ~(misc_regs->err_mask));
पूर्ण

अटल अंतरभूत व्योम ath10k_ce_engine_पूर्णांक_status_clear(काष्ठा ath10k *ar,
						     u32 ce_ctrl_addr,
						     अचिन्हित पूर्णांक mask)
अणु
	काष्ठा ath10k_hw_ce_host_wm_regs *wm_regs = ar->hw_ce_regs->wm_regs;

	ath10k_ce_ग_लिखो32(ar, ce_ctrl_addr + wm_regs->addr, mask);
पूर्ण

/*
 * Guts of ath10k_ce_send.
 * The caller takes responsibility क्रम any needed locking.
 */
अटल पूर्णांक _ath10k_ce_send_nolock(काष्ठा ath10k_ce_pipe *ce_state,
				  व्योम *per_transfer_context,
				  dma_addr_t buffer,
				  अचिन्हित पूर्णांक nbytes,
				  अचिन्हित पूर्णांक transfer_id,
				  अचिन्हित पूर्णांक flags)
अणु
	काष्ठा ath10k *ar = ce_state->ar;
	काष्ठा ath10k_ce_ring *src_ring = ce_state->src_ring;
	काष्ठा ce_desc *desc, sdesc;
	अचिन्हित पूर्णांक nentries_mask = src_ring->nentries_mask;
	अचिन्हित पूर्णांक sw_index = src_ring->sw_index;
	अचिन्हित पूर्णांक ग_लिखो_index = src_ring->ग_लिखो_index;
	u32 ctrl_addr = ce_state->ctrl_addr;
	u32 desc_flags = 0;
	पूर्णांक ret = 0;

	अगर (nbytes > ce_state->src_sz_max)
		ath10k_warn(ar, "%s: send more we can (nbytes: %d, max: %d)\n",
			    __func__, nbytes, ce_state->src_sz_max);

	अगर (unlikely(CE_RING_DELTA(nentries_mask,
				   ग_लिखो_index, sw_index - 1) <= 0)) अणु
		ret = -ENOSR;
		जाओ निकास;
	पूर्ण

	desc = CE_SRC_RING_TO_DESC(src_ring->base_addr_owner_space,
				   ग_लिखो_index);

	desc_flags |= SM(transfer_id, CE_DESC_FLAGS_META_DATA);

	अगर (flags & CE_SEND_FLAG_GATHER)
		desc_flags |= CE_DESC_FLAGS_GATHER;
	अगर (flags & CE_SEND_FLAG_BYTE_SWAP)
		desc_flags |= CE_DESC_FLAGS_BYTE_SWAP;

	sdesc.addr   = __cpu_to_le32(buffer);
	sdesc.nbytes = __cpu_to_le16(nbytes);
	sdesc.flags  = __cpu_to_le16(desc_flags);

	*desc = sdesc;

	src_ring->per_transfer_context[ग_लिखो_index] = per_transfer_context;

	/* Update Source Ring Write Index */
	ग_लिखो_index = CE_RING_IDX_INCR(nentries_mask, ग_लिखो_index);

	/* WORKAROUND */
	अगर (!(flags & CE_SEND_FLAG_GATHER))
		ath10k_ce_src_ring_ग_लिखो_index_set(ar, ctrl_addr, ग_लिखो_index);

	src_ring->ग_लिखो_index = ग_लिखो_index;
निकास:
	वापस ret;
पूर्ण

अटल पूर्णांक _ath10k_ce_send_nolock_64(काष्ठा ath10k_ce_pipe *ce_state,
				     व्योम *per_transfer_context,
				     dma_addr_t buffer,
				     अचिन्हित पूर्णांक nbytes,
				     अचिन्हित पूर्णांक transfer_id,
				     अचिन्हित पूर्णांक flags)
अणु
	काष्ठा ath10k *ar = ce_state->ar;
	काष्ठा ath10k_ce_ring *src_ring = ce_state->src_ring;
	काष्ठा ce_desc_64 *desc, sdesc;
	अचिन्हित पूर्णांक nentries_mask = src_ring->nentries_mask;
	अचिन्हित पूर्णांक sw_index;
	अचिन्हित पूर्णांक ग_लिखो_index = src_ring->ग_लिखो_index;
	u32 ctrl_addr = ce_state->ctrl_addr;
	__le32 *addr;
	u32 desc_flags = 0;
	पूर्णांक ret = 0;

	अगर (test_bit(ATH10K_FLAG_CRASH_FLUSH, &ar->dev_flags))
		वापस -ESHUTDOWN;

	अगर (nbytes > ce_state->src_sz_max)
		ath10k_warn(ar, "%s: send more we can (nbytes: %d, max: %d)\n",
			    __func__, nbytes, ce_state->src_sz_max);

	अगर (ar->hw_params.rri_on_ddr)
		sw_index = ath10k_ce_src_ring_पढ़ो_index_from_ddr(ar, ce_state->id);
	अन्यथा
		sw_index = src_ring->sw_index;

	अगर (unlikely(CE_RING_DELTA(nentries_mask,
				   ग_लिखो_index, sw_index - 1) <= 0)) अणु
		ret = -ENOSR;
		जाओ निकास;
	पूर्ण

	desc = CE_SRC_RING_TO_DESC_64(src_ring->base_addr_owner_space,
				      ग_लिखो_index);

	desc_flags |= SM(transfer_id, CE_DESC_FLAGS_META_DATA);

	अगर (flags & CE_SEND_FLAG_GATHER)
		desc_flags |= CE_DESC_FLAGS_GATHER;

	अगर (flags & CE_SEND_FLAG_BYTE_SWAP)
		desc_flags |= CE_DESC_FLAGS_BYTE_SWAP;

	addr = (__le32 *)&sdesc.addr;

	flags |= upper_32_bits(buffer) & CE_DESC_ADDR_HI_MASK;
	addr[0] = __cpu_to_le32(buffer);
	addr[1] = __cpu_to_le32(flags);
	अगर (flags & CE_SEND_FLAG_GATHER)
		addr[1] |= __cpu_to_le32(CE_WCN3990_DESC_FLAGS_GATHER);
	अन्यथा
		addr[1] &= ~(__cpu_to_le32(CE_WCN3990_DESC_FLAGS_GATHER));

	sdesc.nbytes = __cpu_to_le16(nbytes);
	sdesc.flags  = __cpu_to_le16(desc_flags);

	*desc = sdesc;

	src_ring->per_transfer_context[ग_लिखो_index] = per_transfer_context;

	/* Update Source Ring Write Index */
	ग_लिखो_index = CE_RING_IDX_INCR(nentries_mask, ग_लिखो_index);

	अगर (!(flags & CE_SEND_FLAG_GATHER)) अणु
		अगर (ar->hw_params.shaकरोw_reg_support)
			ath10k_ce_shaकरोw_src_ring_ग_लिखो_index_set(ar, ce_state,
								  ग_लिखो_index);
		अन्यथा
			ath10k_ce_src_ring_ग_लिखो_index_set(ar, ctrl_addr,
							   ग_लिखो_index);
	पूर्ण

	src_ring->ग_लिखो_index = ग_लिखो_index;
निकास:
	वापस ret;
पूर्ण

पूर्णांक ath10k_ce_send_nolock(काष्ठा ath10k_ce_pipe *ce_state,
			  व्योम *per_transfer_context,
			  dma_addr_t buffer,
			  अचिन्हित पूर्णांक nbytes,
			  अचिन्हित पूर्णांक transfer_id,
			  अचिन्हित पूर्णांक flags)
अणु
	वापस ce_state->ops->ce_send_nolock(ce_state, per_transfer_context,
				    buffer, nbytes, transfer_id, flags);
पूर्ण
EXPORT_SYMBOL(ath10k_ce_send_nolock);

व्योम __ath10k_ce_send_revert(काष्ठा ath10k_ce_pipe *pipe)
अणु
	काष्ठा ath10k *ar = pipe->ar;
	काष्ठा ath10k_ce *ce = ath10k_ce_priv(ar);
	काष्ठा ath10k_ce_ring *src_ring = pipe->src_ring;
	u32 ctrl_addr = pipe->ctrl_addr;

	lockdep_निश्चित_held(&ce->ce_lock);

	/*
	 * This function must be called only अगर there is an incomplete
	 * scatter-gather transfer (beक्रमe index रेजिस्टर is updated)
	 * that needs to be cleaned up.
	 */
	अगर (WARN_ON_ONCE(src_ring->ग_लिखो_index == src_ring->sw_index))
		वापस;

	अगर (WARN_ON_ONCE(src_ring->ग_लिखो_index ==
			 ath10k_ce_src_ring_ग_लिखो_index_get(ar, ctrl_addr)))
		वापस;

	src_ring->ग_लिखो_index--;
	src_ring->ग_लिखो_index &= src_ring->nentries_mask;

	src_ring->per_transfer_context[src_ring->ग_लिखो_index] = शून्य;
पूर्ण
EXPORT_SYMBOL(__ath10k_ce_send_revert);

पूर्णांक ath10k_ce_send(काष्ठा ath10k_ce_pipe *ce_state,
		   व्योम *per_transfer_context,
		   dma_addr_t buffer,
		   अचिन्हित पूर्णांक nbytes,
		   अचिन्हित पूर्णांक transfer_id,
		   अचिन्हित पूर्णांक flags)
अणु
	काष्ठा ath10k *ar = ce_state->ar;
	काष्ठा ath10k_ce *ce = ath10k_ce_priv(ar);
	पूर्णांक ret;

	spin_lock_bh(&ce->ce_lock);
	ret = ath10k_ce_send_nolock(ce_state, per_transfer_context,
				    buffer, nbytes, transfer_id, flags);
	spin_unlock_bh(&ce->ce_lock);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(ath10k_ce_send);

पूर्णांक ath10k_ce_num_मुक्त_src_entries(काष्ठा ath10k_ce_pipe *pipe)
अणु
	काष्ठा ath10k *ar = pipe->ar;
	काष्ठा ath10k_ce *ce = ath10k_ce_priv(ar);
	पूर्णांक delta;

	spin_lock_bh(&ce->ce_lock);
	delta = CE_RING_DELTA(pipe->src_ring->nentries_mask,
			      pipe->src_ring->ग_लिखो_index,
			      pipe->src_ring->sw_index - 1);
	spin_unlock_bh(&ce->ce_lock);

	वापस delta;
पूर्ण
EXPORT_SYMBOL(ath10k_ce_num_मुक्त_src_entries);

पूर्णांक __ath10k_ce_rx_num_मुक्त_bufs(काष्ठा ath10k_ce_pipe *pipe)
अणु
	काष्ठा ath10k *ar = pipe->ar;
	काष्ठा ath10k_ce *ce = ath10k_ce_priv(ar);
	काष्ठा ath10k_ce_ring *dest_ring = pipe->dest_ring;
	अचिन्हित पूर्णांक nentries_mask = dest_ring->nentries_mask;
	अचिन्हित पूर्णांक ग_लिखो_index = dest_ring->ग_लिखो_index;
	अचिन्हित पूर्णांक sw_index = dest_ring->sw_index;

	lockdep_निश्चित_held(&ce->ce_lock);

	वापस CE_RING_DELTA(nentries_mask, ग_लिखो_index, sw_index - 1);
पूर्ण
EXPORT_SYMBOL(__ath10k_ce_rx_num_मुक्त_bufs);

अटल पूर्णांक __ath10k_ce_rx_post_buf(काष्ठा ath10k_ce_pipe *pipe, व्योम *ctx,
				   dma_addr_t paddr)
अणु
	काष्ठा ath10k *ar = pipe->ar;
	काष्ठा ath10k_ce *ce = ath10k_ce_priv(ar);
	काष्ठा ath10k_ce_ring *dest_ring = pipe->dest_ring;
	अचिन्हित पूर्णांक nentries_mask = dest_ring->nentries_mask;
	अचिन्हित पूर्णांक ग_लिखो_index = dest_ring->ग_लिखो_index;
	अचिन्हित पूर्णांक sw_index = dest_ring->sw_index;
	काष्ठा ce_desc *base = dest_ring->base_addr_owner_space;
	काष्ठा ce_desc *desc = CE_DEST_RING_TO_DESC(base, ग_लिखो_index);
	u32 ctrl_addr = pipe->ctrl_addr;

	lockdep_निश्चित_held(&ce->ce_lock);

	अगर ((pipe->id != 5) &&
	    CE_RING_DELTA(nentries_mask, ग_लिखो_index, sw_index - 1) == 0)
		वापस -ENOSPC;

	desc->addr = __cpu_to_le32(paddr);
	desc->nbytes = 0;

	dest_ring->per_transfer_context[ग_लिखो_index] = ctx;
	ग_लिखो_index = CE_RING_IDX_INCR(nentries_mask, ग_लिखो_index);
	ath10k_ce_dest_ring_ग_लिखो_index_set(ar, ctrl_addr, ग_लिखो_index);
	dest_ring->ग_लिखो_index = ग_लिखो_index;

	वापस 0;
पूर्ण

अटल पूर्णांक __ath10k_ce_rx_post_buf_64(काष्ठा ath10k_ce_pipe *pipe,
				      व्योम *ctx,
				      dma_addr_t paddr)
अणु
	काष्ठा ath10k *ar = pipe->ar;
	काष्ठा ath10k_ce *ce = ath10k_ce_priv(ar);
	काष्ठा ath10k_ce_ring *dest_ring = pipe->dest_ring;
	अचिन्हित पूर्णांक nentries_mask = dest_ring->nentries_mask;
	अचिन्हित पूर्णांक ग_लिखो_index = dest_ring->ग_लिखो_index;
	अचिन्हित पूर्णांक sw_index = dest_ring->sw_index;
	काष्ठा ce_desc_64 *base = dest_ring->base_addr_owner_space;
	काष्ठा ce_desc_64 *desc =
			CE_DEST_RING_TO_DESC_64(base, ग_लिखो_index);
	u32 ctrl_addr = pipe->ctrl_addr;

	lockdep_निश्चित_held(&ce->ce_lock);

	अगर (CE_RING_DELTA(nentries_mask, ग_लिखो_index, sw_index - 1) == 0)
		वापस -ENOSPC;

	desc->addr = __cpu_to_le64(paddr);
	desc->addr &= __cpu_to_le64(CE_DESC_ADDR_MASK);

	desc->nbytes = 0;

	dest_ring->per_transfer_context[ग_लिखो_index] = ctx;
	ग_लिखो_index = CE_RING_IDX_INCR(nentries_mask, ग_लिखो_index);
	ath10k_ce_dest_ring_ग_लिखो_index_set(ar, ctrl_addr, ग_लिखो_index);
	dest_ring->ग_लिखो_index = ग_लिखो_index;

	वापस 0;
पूर्ण

व्योम ath10k_ce_rx_update_ग_लिखो_idx(काष्ठा ath10k_ce_pipe *pipe, u32 nentries)
अणु
	काष्ठा ath10k *ar = pipe->ar;
	काष्ठा ath10k_ce_ring *dest_ring = pipe->dest_ring;
	अचिन्हित पूर्णांक nentries_mask = dest_ring->nentries_mask;
	अचिन्हित पूर्णांक ग_लिखो_index = dest_ring->ग_लिखो_index;
	u32 ctrl_addr = pipe->ctrl_addr;
	u32 cur_ग_लिखो_idx = ath10k_ce_dest_ring_ग_लिखो_index_get(ar, ctrl_addr);

	/* Prevent CE ring stuck issue that will occur when ring is full.
	 * Make sure that ग_लिखो index is 1 less than पढ़ो index.
	 */
	अगर (((cur_ग_लिखो_idx + nentries) & nentries_mask) == dest_ring->sw_index)
		nentries -= 1;

	ग_लिखो_index = CE_RING_IDX_ADD(nentries_mask, ग_लिखो_index, nentries);
	ath10k_ce_dest_ring_ग_लिखो_index_set(ar, ctrl_addr, ग_लिखो_index);
	dest_ring->ग_लिखो_index = ग_लिखो_index;
पूर्ण
EXPORT_SYMBOL(ath10k_ce_rx_update_ग_लिखो_idx);

पूर्णांक ath10k_ce_rx_post_buf(काष्ठा ath10k_ce_pipe *pipe, व्योम *ctx,
			  dma_addr_t paddr)
अणु
	काष्ठा ath10k *ar = pipe->ar;
	काष्ठा ath10k_ce *ce = ath10k_ce_priv(ar);
	पूर्णांक ret;

	spin_lock_bh(&ce->ce_lock);
	ret = pipe->ops->ce_rx_post_buf(pipe, ctx, paddr);
	spin_unlock_bh(&ce->ce_lock);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(ath10k_ce_rx_post_buf);

/*
 * Guts of ath10k_ce_completed_recv_next.
 * The caller takes responsibility क्रम any necessary locking.
 */
अटल पूर्णांक
	 _ath10k_ce_completed_recv_next_nolock(काष्ठा ath10k_ce_pipe *ce_state,
					       व्योम **per_transfer_contextp,
					       अचिन्हित पूर्णांक *nbytesp)
अणु
	काष्ठा ath10k_ce_ring *dest_ring = ce_state->dest_ring;
	अचिन्हित पूर्णांक nentries_mask = dest_ring->nentries_mask;
	अचिन्हित पूर्णांक sw_index = dest_ring->sw_index;

	काष्ठा ce_desc *base = dest_ring->base_addr_owner_space;
	काष्ठा ce_desc *desc = CE_DEST_RING_TO_DESC(base, sw_index);
	काष्ठा ce_desc sdesc;
	u16 nbytes;

	/* Copy in one go क्रम perक्रमmance reasons */
	sdesc = *desc;

	nbytes = __le16_to_cpu(sdesc.nbytes);
	अगर (nbytes == 0) अणु
		/*
		 * This बंदs a relatively unusual race where the Host
		 * sees the updated DRRI beक्रमe the update to the
		 * corresponding descriptor has completed. We treat this
		 * as a descriptor that is not yet करोne.
		 */
		वापस -EIO;
	पूर्ण

	desc->nbytes = 0;

	/* Return data from completed destination descriptor */
	*nbytesp = nbytes;

	अगर (per_transfer_contextp)
		*per_transfer_contextp =
			dest_ring->per_transfer_context[sw_index];

	/* Copy engine 5 (HTT Rx) will reuse the same transfer context.
	 * So update transfer context all CEs except CE5.
	 */
	अगर (ce_state->id != 5)
		dest_ring->per_transfer_context[sw_index] = शून्य;

	/* Update sw_index */
	sw_index = CE_RING_IDX_INCR(nentries_mask, sw_index);
	dest_ring->sw_index = sw_index;

	वापस 0;
पूर्ण

अटल पूर्णांक
_ath10k_ce_completed_recv_next_nolock_64(काष्ठा ath10k_ce_pipe *ce_state,
					 व्योम **per_transfer_contextp,
					 अचिन्हित पूर्णांक *nbytesp)
अणु
	काष्ठा ath10k_ce_ring *dest_ring = ce_state->dest_ring;
	अचिन्हित पूर्णांक nentries_mask = dest_ring->nentries_mask;
	अचिन्हित पूर्णांक sw_index = dest_ring->sw_index;
	काष्ठा ce_desc_64 *base = dest_ring->base_addr_owner_space;
	काष्ठा ce_desc_64 *desc =
		CE_DEST_RING_TO_DESC_64(base, sw_index);
	काष्ठा ce_desc_64 sdesc;
	u16 nbytes;

	/* Copy in one go क्रम perक्रमmance reasons */
	sdesc = *desc;

	nbytes = __le16_to_cpu(sdesc.nbytes);
	अगर (nbytes == 0) अणु
		/* This बंदs a relatively unusual race where the Host
		 * sees the updated DRRI beक्रमe the update to the
		 * corresponding descriptor has completed. We treat this
		 * as a descriptor that is not yet करोne.
		 */
		वापस -EIO;
	पूर्ण

	desc->nbytes = 0;

	/* Return data from completed destination descriptor */
	*nbytesp = nbytes;

	अगर (per_transfer_contextp)
		*per_transfer_contextp =
			dest_ring->per_transfer_context[sw_index];

	/* Copy engine 5 (HTT Rx) will reuse the same transfer context.
	 * So update transfer context all CEs except CE5.
	 */
	अगर (ce_state->id != 5)
		dest_ring->per_transfer_context[sw_index] = शून्य;

	/* Update sw_index */
	sw_index = CE_RING_IDX_INCR(nentries_mask, sw_index);
	dest_ring->sw_index = sw_index;

	वापस 0;
पूर्ण

पूर्णांक ath10k_ce_completed_recv_next_nolock(काष्ठा ath10k_ce_pipe *ce_state,
					 व्योम **per_transfer_ctx,
					 अचिन्हित पूर्णांक *nbytesp)
अणु
	वापस ce_state->ops->ce_completed_recv_next_nolock(ce_state,
							    per_transfer_ctx,
							    nbytesp);
पूर्ण
EXPORT_SYMBOL(ath10k_ce_completed_recv_next_nolock);

पूर्णांक ath10k_ce_completed_recv_next(काष्ठा ath10k_ce_pipe *ce_state,
				  व्योम **per_transfer_contextp,
				  अचिन्हित पूर्णांक *nbytesp)
अणु
	काष्ठा ath10k *ar = ce_state->ar;
	काष्ठा ath10k_ce *ce = ath10k_ce_priv(ar);
	पूर्णांक ret;

	spin_lock_bh(&ce->ce_lock);
	ret = ce_state->ops->ce_completed_recv_next_nolock(ce_state,
						   per_transfer_contextp,
						   nbytesp);

	spin_unlock_bh(&ce->ce_lock);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(ath10k_ce_completed_recv_next);

अटल पूर्णांक _ath10k_ce_revoke_recv_next(काष्ठा ath10k_ce_pipe *ce_state,
				       व्योम **per_transfer_contextp,
				       dma_addr_t *bufferp)
अणु
	काष्ठा ath10k_ce_ring *dest_ring;
	अचिन्हित पूर्णांक nentries_mask;
	अचिन्हित पूर्णांक sw_index;
	अचिन्हित पूर्णांक ग_लिखो_index;
	पूर्णांक ret;
	काष्ठा ath10k *ar;
	काष्ठा ath10k_ce *ce;

	dest_ring = ce_state->dest_ring;

	अगर (!dest_ring)
		वापस -EIO;

	ar = ce_state->ar;
	ce = ath10k_ce_priv(ar);

	spin_lock_bh(&ce->ce_lock);

	nentries_mask = dest_ring->nentries_mask;
	sw_index = dest_ring->sw_index;
	ग_लिखो_index = dest_ring->ग_लिखो_index;
	अगर (ग_लिखो_index != sw_index) अणु
		काष्ठा ce_desc *base = dest_ring->base_addr_owner_space;
		काष्ठा ce_desc *desc = CE_DEST_RING_TO_DESC(base, sw_index);

		/* Return data from completed destination descriptor */
		*bufferp = __le32_to_cpu(desc->addr);

		अगर (per_transfer_contextp)
			*per_transfer_contextp =
				dest_ring->per_transfer_context[sw_index];

		/* sanity */
		dest_ring->per_transfer_context[sw_index] = शून्य;
		desc->nbytes = 0;

		/* Update sw_index */
		sw_index = CE_RING_IDX_INCR(nentries_mask, sw_index);
		dest_ring->sw_index = sw_index;
		ret = 0;
	पूर्ण अन्यथा अणु
		ret = -EIO;
	पूर्ण

	spin_unlock_bh(&ce->ce_lock);

	वापस ret;
पूर्ण

अटल पूर्णांक _ath10k_ce_revoke_recv_next_64(काष्ठा ath10k_ce_pipe *ce_state,
					  व्योम **per_transfer_contextp,
					  dma_addr_t *bufferp)
अणु
	काष्ठा ath10k_ce_ring *dest_ring;
	अचिन्हित पूर्णांक nentries_mask;
	अचिन्हित पूर्णांक sw_index;
	अचिन्हित पूर्णांक ग_लिखो_index;
	पूर्णांक ret;
	काष्ठा ath10k *ar;
	काष्ठा ath10k_ce *ce;

	dest_ring = ce_state->dest_ring;

	अगर (!dest_ring)
		वापस -EIO;

	ar = ce_state->ar;
	ce = ath10k_ce_priv(ar);

	spin_lock_bh(&ce->ce_lock);

	nentries_mask = dest_ring->nentries_mask;
	sw_index = dest_ring->sw_index;
	ग_लिखो_index = dest_ring->ग_लिखो_index;
	अगर (ग_लिखो_index != sw_index) अणु
		काष्ठा ce_desc_64 *base = dest_ring->base_addr_owner_space;
		काष्ठा ce_desc_64 *desc =
			CE_DEST_RING_TO_DESC_64(base, sw_index);

		/* Return data from completed destination descriptor */
		*bufferp = __le64_to_cpu(desc->addr);

		अगर (per_transfer_contextp)
			*per_transfer_contextp =
				dest_ring->per_transfer_context[sw_index];

		/* sanity */
		dest_ring->per_transfer_context[sw_index] = शून्य;
		desc->nbytes = 0;

		/* Update sw_index */
		sw_index = CE_RING_IDX_INCR(nentries_mask, sw_index);
		dest_ring->sw_index = sw_index;
		ret = 0;
	पूर्ण अन्यथा अणु
		ret = -EIO;
	पूर्ण

	spin_unlock_bh(&ce->ce_lock);

	वापस ret;
पूर्ण

पूर्णांक ath10k_ce_revoke_recv_next(काष्ठा ath10k_ce_pipe *ce_state,
			       व्योम **per_transfer_contextp,
			       dma_addr_t *bufferp)
अणु
	वापस ce_state->ops->ce_revoke_recv_next(ce_state,
						  per_transfer_contextp,
						  bufferp);
पूर्ण
EXPORT_SYMBOL(ath10k_ce_revoke_recv_next);

/*
 * Guts of ath10k_ce_completed_send_next.
 * The caller takes responsibility क्रम any necessary locking.
 */
अटल पूर्णांक _ath10k_ce_completed_send_next_nolock(काष्ठा ath10k_ce_pipe *ce_state,
						 व्योम **per_transfer_contextp)
अणु
	काष्ठा ath10k_ce_ring *src_ring = ce_state->src_ring;
	u32 ctrl_addr = ce_state->ctrl_addr;
	काष्ठा ath10k *ar = ce_state->ar;
	अचिन्हित पूर्णांक nentries_mask = src_ring->nentries_mask;
	अचिन्हित पूर्णांक sw_index = src_ring->sw_index;
	अचिन्हित पूर्णांक पढ़ो_index;
	काष्ठा ce_desc *desc;

	अगर (src_ring->hw_index == sw_index) अणु
		/*
		 * The SW completion index has caught up with the cached
		 * version of the HW completion index.
		 * Update the cached HW completion index to see whether
		 * the SW has really caught up to the HW, or अगर the cached
		 * value of the HW index has become stale.
		 */

		पढ़ो_index = ath10k_ce_src_ring_पढ़ो_index_get(ar, ctrl_addr);
		अगर (पढ़ो_index == 0xffffffff)
			वापस -ENODEV;

		पढ़ो_index &= nentries_mask;
		src_ring->hw_index = पढ़ो_index;
	पूर्ण

	अगर (ar->hw_params.rri_on_ddr)
		पढ़ो_index = ath10k_ce_src_ring_पढ़ो_index_get(ar, ctrl_addr);
	अन्यथा
		पढ़ो_index = src_ring->hw_index;

	अगर (पढ़ो_index == sw_index)
		वापस -EIO;

	अगर (per_transfer_contextp)
		*per_transfer_contextp =
			src_ring->per_transfer_context[sw_index];

	/* sanity */
	src_ring->per_transfer_context[sw_index] = शून्य;
	desc = CE_SRC_RING_TO_DESC(src_ring->base_addr_owner_space,
				   sw_index);
	desc->nbytes = 0;

	/* Update sw_index */
	sw_index = CE_RING_IDX_INCR(nentries_mask, sw_index);
	src_ring->sw_index = sw_index;

	वापस 0;
पूर्ण

अटल पूर्णांक _ath10k_ce_completed_send_next_nolock_64(काष्ठा ath10k_ce_pipe *ce_state,
						    व्योम **per_transfer_contextp)
अणु
	काष्ठा ath10k_ce_ring *src_ring = ce_state->src_ring;
	u32 ctrl_addr = ce_state->ctrl_addr;
	काष्ठा ath10k *ar = ce_state->ar;
	अचिन्हित पूर्णांक nentries_mask = src_ring->nentries_mask;
	अचिन्हित पूर्णांक sw_index = src_ring->sw_index;
	अचिन्हित पूर्णांक पढ़ो_index;
	काष्ठा ce_desc_64 *desc;

	अगर (src_ring->hw_index == sw_index) अणु
		/*
		 * The SW completion index has caught up with the cached
		 * version of the HW completion index.
		 * Update the cached HW completion index to see whether
		 * the SW has really caught up to the HW, or अगर the cached
		 * value of the HW index has become stale.
		 */

		पढ़ो_index = ath10k_ce_src_ring_पढ़ो_index_get(ar, ctrl_addr);
		अगर (पढ़ो_index == 0xffffffff)
			वापस -ENODEV;

		पढ़ो_index &= nentries_mask;
		src_ring->hw_index = पढ़ो_index;
	पूर्ण

	अगर (ar->hw_params.rri_on_ddr)
		पढ़ो_index = ath10k_ce_src_ring_पढ़ो_index_get(ar, ctrl_addr);
	अन्यथा
		पढ़ो_index = src_ring->hw_index;

	अगर (पढ़ो_index == sw_index)
		वापस -EIO;

	अगर (per_transfer_contextp)
		*per_transfer_contextp =
			src_ring->per_transfer_context[sw_index];

	/* sanity */
	src_ring->per_transfer_context[sw_index] = शून्य;
	desc = CE_SRC_RING_TO_DESC_64(src_ring->base_addr_owner_space,
				      sw_index);
	desc->nbytes = 0;

	/* Update sw_index */
	sw_index = CE_RING_IDX_INCR(nentries_mask, sw_index);
	src_ring->sw_index = sw_index;

	वापस 0;
पूर्ण

पूर्णांक ath10k_ce_completed_send_next_nolock(काष्ठा ath10k_ce_pipe *ce_state,
					 व्योम **per_transfer_contextp)
अणु
	वापस ce_state->ops->ce_completed_send_next_nolock(ce_state,
							    per_transfer_contextp);
पूर्ण
EXPORT_SYMBOL(ath10k_ce_completed_send_next_nolock);

अटल व्योम ath10k_ce_extract_desc_data(काष्ठा ath10k *ar,
					काष्ठा ath10k_ce_ring *src_ring,
					u32 sw_index,
					dma_addr_t *bufferp,
					u32 *nbytesp,
					u32 *transfer_idp)
अणु
		काष्ठा ce_desc *base = src_ring->base_addr_owner_space;
		काष्ठा ce_desc *desc = CE_SRC_RING_TO_DESC(base, sw_index);

		/* Return data from completed source descriptor */
		*bufferp = __le32_to_cpu(desc->addr);
		*nbytesp = __le16_to_cpu(desc->nbytes);
		*transfer_idp = MS(__le16_to_cpu(desc->flags),
				   CE_DESC_FLAGS_META_DATA);
पूर्ण

अटल व्योम ath10k_ce_extract_desc_data_64(काष्ठा ath10k *ar,
					   काष्ठा ath10k_ce_ring *src_ring,
					   u32 sw_index,
					   dma_addr_t *bufferp,
					   u32 *nbytesp,
					   u32 *transfer_idp)
अणु
		काष्ठा ce_desc_64 *base = src_ring->base_addr_owner_space;
		काष्ठा ce_desc_64 *desc =
			CE_SRC_RING_TO_DESC_64(base, sw_index);

		/* Return data from completed source descriptor */
		*bufferp = __le64_to_cpu(desc->addr);
		*nbytesp = __le16_to_cpu(desc->nbytes);
		*transfer_idp = MS(__le16_to_cpu(desc->flags),
				   CE_DESC_FLAGS_META_DATA);
पूर्ण

/* NB: Modeled after ath10k_ce_completed_send_next */
पूर्णांक ath10k_ce_cancel_send_next(काष्ठा ath10k_ce_pipe *ce_state,
			       व्योम **per_transfer_contextp,
			       dma_addr_t *bufferp,
			       अचिन्हित पूर्णांक *nbytesp,
			       अचिन्हित पूर्णांक *transfer_idp)
अणु
	काष्ठा ath10k_ce_ring *src_ring;
	अचिन्हित पूर्णांक nentries_mask;
	अचिन्हित पूर्णांक sw_index;
	अचिन्हित पूर्णांक ग_लिखो_index;
	पूर्णांक ret;
	काष्ठा ath10k *ar;
	काष्ठा ath10k_ce *ce;

	src_ring = ce_state->src_ring;

	अगर (!src_ring)
		वापस -EIO;

	ar = ce_state->ar;
	ce = ath10k_ce_priv(ar);

	spin_lock_bh(&ce->ce_lock);

	nentries_mask = src_ring->nentries_mask;
	sw_index = src_ring->sw_index;
	ग_लिखो_index = src_ring->ग_लिखो_index;

	अगर (ग_लिखो_index != sw_index) अणु
		ce_state->ops->ce_extract_desc_data(ar, src_ring, sw_index,
						    bufferp, nbytesp,
						    transfer_idp);

		अगर (per_transfer_contextp)
			*per_transfer_contextp =
				src_ring->per_transfer_context[sw_index];

		/* sanity */
		src_ring->per_transfer_context[sw_index] = शून्य;

		/* Update sw_index */
		sw_index = CE_RING_IDX_INCR(nentries_mask, sw_index);
		src_ring->sw_index = sw_index;
		ret = 0;
	पूर्ण अन्यथा अणु
		ret = -EIO;
	पूर्ण

	spin_unlock_bh(&ce->ce_lock);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(ath10k_ce_cancel_send_next);

पूर्णांक ath10k_ce_completed_send_next(काष्ठा ath10k_ce_pipe *ce_state,
				  व्योम **per_transfer_contextp)
अणु
	काष्ठा ath10k *ar = ce_state->ar;
	काष्ठा ath10k_ce *ce = ath10k_ce_priv(ar);
	पूर्णांक ret;

	spin_lock_bh(&ce->ce_lock);
	ret = ath10k_ce_completed_send_next_nolock(ce_state,
						   per_transfer_contextp);
	spin_unlock_bh(&ce->ce_lock);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(ath10k_ce_completed_send_next);

/*
 * Guts of पूर्णांकerrupt handler क्रम per-engine पूर्णांकerrupts on a particular CE.
 *
 * Invokes रेजिस्टरed callbacks क्रम recv_complete,
 * send_complete, and watermarks.
 */
व्योम ath10k_ce_per_engine_service(काष्ठा ath10k *ar, अचिन्हित पूर्णांक ce_id)
अणु
	काष्ठा ath10k_ce *ce = ath10k_ce_priv(ar);
	काष्ठा ath10k_ce_pipe *ce_state = &ce->ce_states[ce_id];
	काष्ठा ath10k_hw_ce_host_wm_regs *wm_regs = ar->hw_ce_regs->wm_regs;
	u32 ctrl_addr = ce_state->ctrl_addr;

	/*
	 * Clear beक्रमe handling
	 *
	 * Misc CE पूर्णांकerrupts are not being handled, but still need
	 * to be cleared.
	 *
	 * NOTE: When the last copy engine पूर्णांकerrupt is cleared the
	 * hardware will go to sleep.  Once this happens any access to
	 * the CE रेजिस्टरs can cause a hardware fault.
	 */
	ath10k_ce_engine_पूर्णांक_status_clear(ar, ctrl_addr,
					  wm_regs->cc_mask | wm_regs->wm_mask);

	अगर (ce_state->recv_cb)
		ce_state->recv_cb(ce_state);

	अगर (ce_state->send_cb)
		ce_state->send_cb(ce_state);
पूर्ण
EXPORT_SYMBOL(ath10k_ce_per_engine_service);

/*
 * Handler क्रम per-engine पूर्णांकerrupts on ALL active CEs.
 * This is used in हालs where the प्रणाली is sharing a
 * single पूर्णांकerrput क्रम all CEs
 */

व्योम ath10k_ce_per_engine_service_any(काष्ठा ath10k *ar)
अणु
	पूर्णांक ce_id;
	u32 पूर्णांकr_summary;

	पूर्णांकr_summary = ath10k_ce_पूर्णांकerrupt_summary(ar);

	क्रम (ce_id = 0; पूर्णांकr_summary && (ce_id < CE_COUNT); ce_id++) अणु
		अगर (पूर्णांकr_summary & (1 << ce_id))
			पूर्णांकr_summary &= ~(1 << ce_id);
		अन्यथा
			/* no पूर्णांकr pending on this CE */
			जारी;

		ath10k_ce_per_engine_service(ar, ce_id);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(ath10k_ce_per_engine_service_any);

/*
 * Adjust पूर्णांकerrupts क्रम the copy complete handler.
 * If it's needed क्रम either send or recv, then unmask
 * this पूर्णांकerrupt; otherwise, mask it.
 *
 * Called with ce_lock held.
 */
अटल व्योम ath10k_ce_per_engine_handler_adjust(काष्ठा ath10k_ce_pipe *ce_state)
अणु
	u32 ctrl_addr = ce_state->ctrl_addr;
	काष्ठा ath10k *ar = ce_state->ar;
	bool disable_copy_compl_पूर्णांकr = ce_state->attr_flags & CE_ATTR_DIS_INTR;

	अगर ((!disable_copy_compl_पूर्णांकr) &&
	    (ce_state->send_cb || ce_state->recv_cb))
		ath10k_ce_copy_complete_पूर्णांकer_enable(ar, ctrl_addr);
	अन्यथा
		ath10k_ce_copy_complete_पूर्णांकr_disable(ar, ctrl_addr);

	ath10k_ce_watermark_पूर्णांकr_disable(ar, ctrl_addr);
पूर्ण

व्योम ath10k_ce_disable_पूर्णांकerrupt(काष्ठा ath10k *ar, पूर्णांक ce_id)
अणु
	काष्ठा ath10k_ce *ce = ath10k_ce_priv(ar);
	काष्ठा ath10k_ce_pipe *ce_state;
	u32 ctrl_addr;

	ce_state  = &ce->ce_states[ce_id];
	अगर (ce_state->attr_flags & CE_ATTR_POLL)
		वापस;

	ctrl_addr = ath10k_ce_base_address(ar, ce_id);

	ath10k_ce_copy_complete_पूर्णांकr_disable(ar, ctrl_addr);
	ath10k_ce_error_पूर्णांकr_disable(ar, ctrl_addr);
	ath10k_ce_watermark_पूर्णांकr_disable(ar, ctrl_addr);
पूर्ण
EXPORT_SYMBOL(ath10k_ce_disable_पूर्णांकerrupt);

व्योम ath10k_ce_disable_पूर्णांकerrupts(काष्ठा ath10k *ar)
अणु
	पूर्णांक ce_id;

	क्रम (ce_id = 0; ce_id < CE_COUNT; ce_id++)
		ath10k_ce_disable_पूर्णांकerrupt(ar, ce_id);
पूर्ण
EXPORT_SYMBOL(ath10k_ce_disable_पूर्णांकerrupts);

व्योम ath10k_ce_enable_पूर्णांकerrupt(काष्ठा ath10k *ar, पूर्णांक ce_id)
अणु
	काष्ठा ath10k_ce *ce = ath10k_ce_priv(ar);
	काष्ठा ath10k_ce_pipe *ce_state;

	ce_state  = &ce->ce_states[ce_id];
	अगर (ce_state->attr_flags & CE_ATTR_POLL)
		वापस;

	ath10k_ce_per_engine_handler_adjust(ce_state);
पूर्ण
EXPORT_SYMBOL(ath10k_ce_enable_पूर्णांकerrupt);

व्योम ath10k_ce_enable_पूर्णांकerrupts(काष्ठा ath10k *ar)
अणु
	पूर्णांक ce_id;

	/* Enable पूर्णांकerrupts क्रम copy engine that
	 * are not using polling mode.
	 */
	क्रम (ce_id = 0; ce_id < CE_COUNT; ce_id++)
		ath10k_ce_enable_पूर्णांकerrupt(ar, ce_id);
पूर्ण
EXPORT_SYMBOL(ath10k_ce_enable_पूर्णांकerrupts);

अटल पूर्णांक ath10k_ce_init_src_ring(काष्ठा ath10k *ar,
				   अचिन्हित पूर्णांक ce_id,
				   स्थिर काष्ठा ce_attr *attr)
अणु
	काष्ठा ath10k_ce *ce = ath10k_ce_priv(ar);
	काष्ठा ath10k_ce_pipe *ce_state = &ce->ce_states[ce_id];
	काष्ठा ath10k_ce_ring *src_ring = ce_state->src_ring;
	u32 nentries, ctrl_addr = ath10k_ce_base_address(ar, ce_id);

	nentries = roundup_घात_of_two(attr->src_nentries);

	अगर (ar->hw_params.target_64bit)
		स_रखो(src_ring->base_addr_owner_space, 0,
		       nentries * माप(काष्ठा ce_desc_64));
	अन्यथा
		स_रखो(src_ring->base_addr_owner_space, 0,
		       nentries * माप(काष्ठा ce_desc));

	src_ring->sw_index = ath10k_ce_src_ring_पढ़ो_index_get(ar, ctrl_addr);
	src_ring->sw_index &= src_ring->nentries_mask;
	src_ring->hw_index = src_ring->sw_index;

	src_ring->ग_लिखो_index =
		ath10k_ce_src_ring_ग_लिखो_index_get(ar, ctrl_addr);
	src_ring->ग_लिखो_index &= src_ring->nentries_mask;

	ath10k_ce_src_ring_base_addr_set(ar, ce_id,
					 src_ring->base_addr_ce_space);
	ath10k_ce_src_ring_size_set(ar, ctrl_addr, nentries);
	ath10k_ce_src_ring_dmax_set(ar, ctrl_addr, attr->src_sz_max);
	ath10k_ce_src_ring_byte_swap_set(ar, ctrl_addr, 0);
	ath10k_ce_src_ring_lowmark_set(ar, ctrl_addr, 0);
	ath10k_ce_src_ring_highmark_set(ar, ctrl_addr, nentries);

	ath10k_dbg(ar, ATH10K_DBG_BOOT,
		   "boot init ce src ring id %d entries %d base_addr %pK\n",
		   ce_id, nentries, src_ring->base_addr_owner_space);

	वापस 0;
पूर्ण

अटल पूर्णांक ath10k_ce_init_dest_ring(काष्ठा ath10k *ar,
				    अचिन्हित पूर्णांक ce_id,
				    स्थिर काष्ठा ce_attr *attr)
अणु
	काष्ठा ath10k_ce *ce = ath10k_ce_priv(ar);
	काष्ठा ath10k_ce_pipe *ce_state = &ce->ce_states[ce_id];
	काष्ठा ath10k_ce_ring *dest_ring = ce_state->dest_ring;
	u32 nentries, ctrl_addr = ath10k_ce_base_address(ar, ce_id);

	nentries = roundup_घात_of_two(attr->dest_nentries);

	अगर (ar->hw_params.target_64bit)
		स_रखो(dest_ring->base_addr_owner_space, 0,
		       nentries * माप(काष्ठा ce_desc_64));
	अन्यथा
		स_रखो(dest_ring->base_addr_owner_space, 0,
		       nentries * माप(काष्ठा ce_desc));

	dest_ring->sw_index = ath10k_ce_dest_ring_पढ़ो_index_get(ar, ctrl_addr);
	dest_ring->sw_index &= dest_ring->nentries_mask;
	dest_ring->ग_लिखो_index =
		ath10k_ce_dest_ring_ग_लिखो_index_get(ar, ctrl_addr);
	dest_ring->ग_लिखो_index &= dest_ring->nentries_mask;

	ath10k_ce_dest_ring_base_addr_set(ar, ce_id,
					  dest_ring->base_addr_ce_space);
	ath10k_ce_dest_ring_size_set(ar, ctrl_addr, nentries);
	ath10k_ce_dest_ring_byte_swap_set(ar, ctrl_addr, 0);
	ath10k_ce_dest_ring_lowmark_set(ar, ctrl_addr, 0);
	ath10k_ce_dest_ring_highmark_set(ar, ctrl_addr, nentries);

	ath10k_dbg(ar, ATH10K_DBG_BOOT,
		   "boot ce dest ring id %d entries %d base_addr %pK\n",
		   ce_id, nentries, dest_ring->base_addr_owner_space);

	वापस 0;
पूर्ण

अटल पूर्णांक ath10k_ce_alloc_shaकरोw_base(काष्ठा ath10k *ar,
				       काष्ठा ath10k_ce_ring *src_ring,
				       u32 nentries)
अणु
	src_ring->shaकरोw_base_unaligned = kसुस्मृति(nentries,
						  माप(काष्ठा ce_desc_64),
						  GFP_KERNEL);
	अगर (!src_ring->shaकरोw_base_unaligned)
		वापस -ENOMEM;

	src_ring->shaकरोw_base = (काष्ठा ce_desc_64 *)
			PTR_ALIGN(src_ring->shaकरोw_base_unaligned,
				  CE_DESC_RING_ALIGN);
	वापस 0;
पूर्ण

अटल काष्ठा ath10k_ce_ring *
ath10k_ce_alloc_src_ring(काष्ठा ath10k *ar, अचिन्हित पूर्णांक ce_id,
			 स्थिर काष्ठा ce_attr *attr)
अणु
	काष्ठा ath10k_ce_ring *src_ring;
	u32 nentries = attr->src_nentries;
	dma_addr_t base_addr;
	पूर्णांक ret;

	nentries = roundup_घात_of_two(nentries);

	src_ring = kzalloc(काष्ठा_size(src_ring, per_transfer_context,
				       nentries), GFP_KERNEL);
	अगर (src_ring == शून्य)
		वापस ERR_PTR(-ENOMEM);

	src_ring->nentries = nentries;
	src_ring->nentries_mask = nentries - 1;

	/*
	 * Legacy platक्रमms that करो not support cache
	 * coherent DMA are unsupported
	 */
	src_ring->base_addr_owner_space_unaligned =
		dma_alloc_coherent(ar->dev,
				   (nentries * माप(काष्ठा ce_desc) +
				    CE_DESC_RING_ALIGN),
				   &base_addr, GFP_KERNEL);
	अगर (!src_ring->base_addr_owner_space_unaligned) अणु
		kमुक्त(src_ring);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	src_ring->base_addr_ce_space_unaligned = base_addr;

	src_ring->base_addr_owner_space =
			PTR_ALIGN(src_ring->base_addr_owner_space_unaligned,
				  CE_DESC_RING_ALIGN);
	src_ring->base_addr_ce_space =
			ALIGN(src_ring->base_addr_ce_space_unaligned,
			      CE_DESC_RING_ALIGN);

	अगर (ar->hw_params.shaकरोw_reg_support) अणु
		ret = ath10k_ce_alloc_shaकरोw_base(ar, src_ring, nentries);
		अगर (ret) अणु
			dma_मुक्त_coherent(ar->dev,
					  (nentries * माप(काष्ठा ce_desc) +
					   CE_DESC_RING_ALIGN),
					  src_ring->base_addr_owner_space_unaligned,
					  base_addr);
			kमुक्त(src_ring);
			वापस ERR_PTR(ret);
		पूर्ण
	पूर्ण

	वापस src_ring;
पूर्ण

अटल काष्ठा ath10k_ce_ring *
ath10k_ce_alloc_src_ring_64(काष्ठा ath10k *ar, अचिन्हित पूर्णांक ce_id,
			    स्थिर काष्ठा ce_attr *attr)
अणु
	काष्ठा ath10k_ce_ring *src_ring;
	u32 nentries = attr->src_nentries;
	dma_addr_t base_addr;
	पूर्णांक ret;

	nentries = roundup_घात_of_two(nentries);

	src_ring = kzalloc(काष्ठा_size(src_ring, per_transfer_context,
				       nentries), GFP_KERNEL);
	अगर (!src_ring)
		वापस ERR_PTR(-ENOMEM);

	src_ring->nentries = nentries;
	src_ring->nentries_mask = nentries - 1;

	/* Legacy platक्रमms that करो not support cache
	 * coherent DMA are unsupported
	 */
	src_ring->base_addr_owner_space_unaligned =
		dma_alloc_coherent(ar->dev,
				   (nentries * माप(काष्ठा ce_desc_64) +
				    CE_DESC_RING_ALIGN),
				   &base_addr, GFP_KERNEL);
	अगर (!src_ring->base_addr_owner_space_unaligned) अणु
		kमुक्त(src_ring);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	src_ring->base_addr_ce_space_unaligned = base_addr;

	src_ring->base_addr_owner_space =
			PTR_ALIGN(src_ring->base_addr_owner_space_unaligned,
				  CE_DESC_RING_ALIGN);
	src_ring->base_addr_ce_space =
			ALIGN(src_ring->base_addr_ce_space_unaligned,
			      CE_DESC_RING_ALIGN);

	अगर (ar->hw_params.shaकरोw_reg_support) अणु
		ret = ath10k_ce_alloc_shaकरोw_base(ar, src_ring, nentries);
		अगर (ret) अणु
			dma_मुक्त_coherent(ar->dev,
					  (nentries * माप(काष्ठा ce_desc_64) +
					   CE_DESC_RING_ALIGN),
					  src_ring->base_addr_owner_space_unaligned,
					  base_addr);
			kमुक्त(src_ring);
			वापस ERR_PTR(ret);
		पूर्ण
	पूर्ण

	वापस src_ring;
पूर्ण

अटल काष्ठा ath10k_ce_ring *
ath10k_ce_alloc_dest_ring(काष्ठा ath10k *ar, अचिन्हित पूर्णांक ce_id,
			  स्थिर काष्ठा ce_attr *attr)
अणु
	काष्ठा ath10k_ce_ring *dest_ring;
	u32 nentries;
	dma_addr_t base_addr;

	nentries = roundup_घात_of_two(attr->dest_nentries);

	dest_ring = kzalloc(काष्ठा_size(dest_ring, per_transfer_context,
					nentries), GFP_KERNEL);
	अगर (dest_ring == शून्य)
		वापस ERR_PTR(-ENOMEM);

	dest_ring->nentries = nentries;
	dest_ring->nentries_mask = nentries - 1;

	/*
	 * Legacy platक्रमms that करो not support cache
	 * coherent DMA are unsupported
	 */
	dest_ring->base_addr_owner_space_unaligned =
		dma_alloc_coherent(ar->dev,
				   (nentries * माप(काष्ठा ce_desc) +
				    CE_DESC_RING_ALIGN),
				   &base_addr, GFP_KERNEL);
	अगर (!dest_ring->base_addr_owner_space_unaligned) अणु
		kमुक्त(dest_ring);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	dest_ring->base_addr_ce_space_unaligned = base_addr;

	dest_ring->base_addr_owner_space =
			PTR_ALIGN(dest_ring->base_addr_owner_space_unaligned,
				  CE_DESC_RING_ALIGN);
	dest_ring->base_addr_ce_space =
				ALIGN(dest_ring->base_addr_ce_space_unaligned,
				      CE_DESC_RING_ALIGN);

	वापस dest_ring;
पूर्ण

अटल काष्ठा ath10k_ce_ring *
ath10k_ce_alloc_dest_ring_64(काष्ठा ath10k *ar, अचिन्हित पूर्णांक ce_id,
			     स्थिर काष्ठा ce_attr *attr)
अणु
	काष्ठा ath10k_ce_ring *dest_ring;
	u32 nentries;
	dma_addr_t base_addr;

	nentries = roundup_घात_of_two(attr->dest_nentries);

	dest_ring = kzalloc(काष्ठा_size(dest_ring, per_transfer_context,
					nentries), GFP_KERNEL);
	अगर (!dest_ring)
		वापस ERR_PTR(-ENOMEM);

	dest_ring->nentries = nentries;
	dest_ring->nentries_mask = nentries - 1;

	/* Legacy platक्रमms that करो not support cache
	 * coherent DMA are unsupported
	 */
	dest_ring->base_addr_owner_space_unaligned =
		dma_alloc_coherent(ar->dev,
				   (nentries * माप(काष्ठा ce_desc_64) +
				    CE_DESC_RING_ALIGN),
				   &base_addr, GFP_KERNEL);
	अगर (!dest_ring->base_addr_owner_space_unaligned) अणु
		kमुक्त(dest_ring);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	dest_ring->base_addr_ce_space_unaligned = base_addr;

	/* Correctly initialize memory to 0 to prevent garbage
	 * data crashing प्रणाली when करोwnload firmware
	 */
	dest_ring->base_addr_owner_space =
			PTR_ALIGN(dest_ring->base_addr_owner_space_unaligned,
				  CE_DESC_RING_ALIGN);
	dest_ring->base_addr_ce_space =
			ALIGN(dest_ring->base_addr_ce_space_unaligned,
			      CE_DESC_RING_ALIGN);

	वापस dest_ring;
पूर्ण

/*
 * Initialize a Copy Engine based on caller-supplied attributes.
 * This may be called once to initialize both source and destination
 * rings or it may be called twice क्रम separate source and destination
 * initialization. It may be that only one side or the other is
 * initialized by software/firmware.
 */
पूर्णांक ath10k_ce_init_pipe(काष्ठा ath10k *ar, अचिन्हित पूर्णांक ce_id,
			स्थिर काष्ठा ce_attr *attr)
अणु
	पूर्णांक ret;

	अगर (attr->src_nentries) अणु
		ret = ath10k_ce_init_src_ring(ar, ce_id, attr);
		अगर (ret) अणु
			ath10k_err(ar, "Failed to initialize CE src ring for ID: %d (%d)\n",
				   ce_id, ret);
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (attr->dest_nentries) अणु
		ret = ath10k_ce_init_dest_ring(ar, ce_id, attr);
		अगर (ret) अणु
			ath10k_err(ar, "Failed to initialize CE dest ring for ID: %d (%d)\n",
				   ce_id, ret);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(ath10k_ce_init_pipe);

अटल व्योम ath10k_ce_deinit_src_ring(काष्ठा ath10k *ar, अचिन्हित पूर्णांक ce_id)
अणु
	u32 ctrl_addr = ath10k_ce_base_address(ar, ce_id);

	ath10k_ce_src_ring_base_addr_set(ar, ce_id, 0);
	ath10k_ce_src_ring_size_set(ar, ctrl_addr, 0);
	ath10k_ce_src_ring_dmax_set(ar, ctrl_addr, 0);
	ath10k_ce_src_ring_highmark_set(ar, ctrl_addr, 0);
पूर्ण

अटल व्योम ath10k_ce_deinit_dest_ring(काष्ठा ath10k *ar, अचिन्हित पूर्णांक ce_id)
अणु
	u32 ctrl_addr = ath10k_ce_base_address(ar, ce_id);

	ath10k_ce_dest_ring_base_addr_set(ar, ce_id, 0);
	ath10k_ce_dest_ring_size_set(ar, ctrl_addr, 0);
	ath10k_ce_dest_ring_highmark_set(ar, ctrl_addr, 0);
पूर्ण

व्योम ath10k_ce_deinit_pipe(काष्ठा ath10k *ar, अचिन्हित पूर्णांक ce_id)
अणु
	ath10k_ce_deinit_src_ring(ar, ce_id);
	ath10k_ce_deinit_dest_ring(ar, ce_id);
पूर्ण
EXPORT_SYMBOL(ath10k_ce_deinit_pipe);

अटल व्योम _ath10k_ce_मुक्त_pipe(काष्ठा ath10k *ar, पूर्णांक ce_id)
अणु
	काष्ठा ath10k_ce *ce = ath10k_ce_priv(ar);
	काष्ठा ath10k_ce_pipe *ce_state = &ce->ce_states[ce_id];

	अगर (ce_state->src_ring) अणु
		अगर (ar->hw_params.shaकरोw_reg_support)
			kमुक्त(ce_state->src_ring->shaकरोw_base_unaligned);
		dma_मुक्त_coherent(ar->dev,
				  (ce_state->src_ring->nentries *
				   माप(काष्ठा ce_desc) +
				   CE_DESC_RING_ALIGN),
				  ce_state->src_ring->base_addr_owner_space,
				  ce_state->src_ring->base_addr_ce_space);
		kमुक्त(ce_state->src_ring);
	पूर्ण

	अगर (ce_state->dest_ring) अणु
		dma_मुक्त_coherent(ar->dev,
				  (ce_state->dest_ring->nentries *
				   माप(काष्ठा ce_desc) +
				   CE_DESC_RING_ALIGN),
				  ce_state->dest_ring->base_addr_owner_space,
				  ce_state->dest_ring->base_addr_ce_space);
		kमुक्त(ce_state->dest_ring);
	पूर्ण

	ce_state->src_ring = शून्य;
	ce_state->dest_ring = शून्य;
पूर्ण

अटल व्योम _ath10k_ce_मुक्त_pipe_64(काष्ठा ath10k *ar, पूर्णांक ce_id)
अणु
	काष्ठा ath10k_ce *ce = ath10k_ce_priv(ar);
	काष्ठा ath10k_ce_pipe *ce_state = &ce->ce_states[ce_id];

	अगर (ce_state->src_ring) अणु
		अगर (ar->hw_params.shaकरोw_reg_support)
			kमुक्त(ce_state->src_ring->shaकरोw_base_unaligned);
		dma_मुक्त_coherent(ar->dev,
				  (ce_state->src_ring->nentries *
				   माप(काष्ठा ce_desc_64) +
				   CE_DESC_RING_ALIGN),
				  ce_state->src_ring->base_addr_owner_space,
				  ce_state->src_ring->base_addr_ce_space);
		kमुक्त(ce_state->src_ring);
	पूर्ण

	अगर (ce_state->dest_ring) अणु
		dma_मुक्त_coherent(ar->dev,
				  (ce_state->dest_ring->nentries *
				   माप(काष्ठा ce_desc_64) +
				   CE_DESC_RING_ALIGN),
				  ce_state->dest_ring->base_addr_owner_space,
				  ce_state->dest_ring->base_addr_ce_space);
		kमुक्त(ce_state->dest_ring);
	पूर्ण

	ce_state->src_ring = शून्य;
	ce_state->dest_ring = शून्य;
पूर्ण

व्योम ath10k_ce_मुक्त_pipe(काष्ठा ath10k *ar, पूर्णांक ce_id)
अणु
	काष्ठा ath10k_ce *ce = ath10k_ce_priv(ar);
	काष्ठा ath10k_ce_pipe *ce_state = &ce->ce_states[ce_id];

	ce_state->ops->ce_मुक्त_pipe(ar, ce_id);
पूर्ण
EXPORT_SYMBOL(ath10k_ce_मुक्त_pipe);

व्योम ath10k_ce_dump_रेजिस्टरs(काष्ठा ath10k *ar,
			      काष्ठा ath10k_fw_crash_data *crash_data)
अणु
	काष्ठा ath10k_ce *ce = ath10k_ce_priv(ar);
	काष्ठा ath10k_ce_crash_data ce_data;
	u32 addr, id;

	lockdep_निश्चित_held(&ar->dump_mutex);

	ath10k_err(ar, "Copy Engine register dump:\n");

	spin_lock_bh(&ce->ce_lock);
	क्रम (id = 0; id < CE_COUNT; id++) अणु
		addr = ath10k_ce_base_address(ar, id);
		ce_data.base_addr = cpu_to_le32(addr);

		ce_data.src_wr_idx =
			cpu_to_le32(ath10k_ce_src_ring_ग_लिखो_index_get(ar, addr));
		ce_data.src_r_idx =
			cpu_to_le32(ath10k_ce_src_ring_पढ़ो_index_get(ar, addr));
		ce_data.dst_wr_idx =
			cpu_to_le32(ath10k_ce_dest_ring_ग_लिखो_index_get(ar, addr));
		ce_data.dst_r_idx =
			cpu_to_le32(ath10k_ce_dest_ring_पढ़ो_index_get(ar, addr));

		अगर (crash_data)
			crash_data->ce_crash_data[id] = ce_data;

		ath10k_err(ar, "[%02d]: 0x%08x %3u %3u %3u %3u", id,
			   le32_to_cpu(ce_data.base_addr),
			   le32_to_cpu(ce_data.src_wr_idx),
			   le32_to_cpu(ce_data.src_r_idx),
			   le32_to_cpu(ce_data.dst_wr_idx),
			   le32_to_cpu(ce_data.dst_r_idx));
	पूर्ण

	spin_unlock_bh(&ce->ce_lock);
पूर्ण
EXPORT_SYMBOL(ath10k_ce_dump_रेजिस्टरs);

अटल स्थिर काष्ठा ath10k_ce_ops ce_ops = अणु
	.ce_alloc_src_ring = ath10k_ce_alloc_src_ring,
	.ce_alloc_dst_ring = ath10k_ce_alloc_dest_ring,
	.ce_rx_post_buf = __ath10k_ce_rx_post_buf,
	.ce_completed_recv_next_nolock = _ath10k_ce_completed_recv_next_nolock,
	.ce_revoke_recv_next = _ath10k_ce_revoke_recv_next,
	.ce_extract_desc_data = ath10k_ce_extract_desc_data,
	.ce_मुक्त_pipe = _ath10k_ce_मुक्त_pipe,
	.ce_send_nolock = _ath10k_ce_send_nolock,
	.ce_set_src_ring_base_addr_hi = शून्य,
	.ce_set_dest_ring_base_addr_hi = शून्य,
	.ce_completed_send_next_nolock = _ath10k_ce_completed_send_next_nolock,
पूर्ण;

अटल स्थिर काष्ठा ath10k_ce_ops ce_64_ops = अणु
	.ce_alloc_src_ring = ath10k_ce_alloc_src_ring_64,
	.ce_alloc_dst_ring = ath10k_ce_alloc_dest_ring_64,
	.ce_rx_post_buf = __ath10k_ce_rx_post_buf_64,
	.ce_completed_recv_next_nolock =
				_ath10k_ce_completed_recv_next_nolock_64,
	.ce_revoke_recv_next = _ath10k_ce_revoke_recv_next_64,
	.ce_extract_desc_data = ath10k_ce_extract_desc_data_64,
	.ce_मुक्त_pipe = _ath10k_ce_मुक्त_pipe_64,
	.ce_send_nolock = _ath10k_ce_send_nolock_64,
	.ce_set_src_ring_base_addr_hi = ath10k_ce_set_src_ring_base_addr_hi,
	.ce_set_dest_ring_base_addr_hi = ath10k_ce_set_dest_ring_base_addr_hi,
	.ce_completed_send_next_nolock = _ath10k_ce_completed_send_next_nolock_64,
पूर्ण;

अटल व्योम ath10k_ce_set_ops(काष्ठा ath10k *ar,
			      काष्ठा ath10k_ce_pipe *ce_state)
अणु
	चयन (ar->hw_rev) अणु
	हाल ATH10K_HW_WCN3990:
		ce_state->ops = &ce_64_ops;
		अवरोध;
	शेष:
		ce_state->ops = &ce_ops;
		अवरोध;
	पूर्ण
पूर्ण

पूर्णांक ath10k_ce_alloc_pipe(काष्ठा ath10k *ar, पूर्णांक ce_id,
			 स्थिर काष्ठा ce_attr *attr)
अणु
	काष्ठा ath10k_ce *ce = ath10k_ce_priv(ar);
	काष्ठा ath10k_ce_pipe *ce_state = &ce->ce_states[ce_id];
	पूर्णांक ret;

	ath10k_ce_set_ops(ar, ce_state);
	/* Make sure there's enough CE ringbuffer entries क्रम HTT TX to aव्योम
	 * additional TX locking checks.
	 *
	 * For the lack of a better place करो the check here.
	 */
	BUILD_BUG_ON(2 * TARGET_NUM_MSDU_DESC >
		     (CE_HTT_H2T_MSG_SRC_NENTRIES - 1));
	BUILD_BUG_ON(2 * TARGET_10_4_NUM_MSDU_DESC_PFC >
		     (CE_HTT_H2T_MSG_SRC_NENTRIES - 1));
	BUILD_BUG_ON(2 * TARGET_TLV_NUM_MSDU_DESC >
		     (CE_HTT_H2T_MSG_SRC_NENTRIES - 1));

	ce_state->ar = ar;
	ce_state->id = ce_id;
	ce_state->ctrl_addr = ath10k_ce_base_address(ar, ce_id);
	ce_state->attr_flags = attr->flags;
	ce_state->src_sz_max = attr->src_sz_max;

	अगर (attr->src_nentries)
		ce_state->send_cb = attr->send_cb;

	अगर (attr->dest_nentries)
		ce_state->recv_cb = attr->recv_cb;

	अगर (attr->src_nentries) अणु
		ce_state->src_ring =
			ce_state->ops->ce_alloc_src_ring(ar, ce_id, attr);
		अगर (IS_ERR(ce_state->src_ring)) अणु
			ret = PTR_ERR(ce_state->src_ring);
			ath10k_err(ar, "failed to alloc CE src ring %d: %d\n",
				   ce_id, ret);
			ce_state->src_ring = शून्य;
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (attr->dest_nentries) अणु
		ce_state->dest_ring = ce_state->ops->ce_alloc_dst_ring(ar,
									ce_id,
									attr);
		अगर (IS_ERR(ce_state->dest_ring)) अणु
			ret = PTR_ERR(ce_state->dest_ring);
			ath10k_err(ar, "failed to alloc CE dest ring %d: %d\n",
				   ce_id, ret);
			ce_state->dest_ring = शून्य;
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(ath10k_ce_alloc_pipe);

व्योम ath10k_ce_alloc_rri(काष्ठा ath10k *ar)
अणु
	पूर्णांक i;
	u32 value;
	u32 ctrl1_regs;
	u32 ce_base_addr;
	काष्ठा ath10k_ce *ce = ath10k_ce_priv(ar);

	ce->vaddr_rri = dma_alloc_coherent(ar->dev,
					   (CE_COUNT * माप(u32)),
					   &ce->paddr_rri, GFP_KERNEL);

	अगर (!ce->vaddr_rri)
		वापस;

	ath10k_ce_ग_लिखो32(ar, ar->hw_ce_regs->ce_rri_low,
			  lower_32_bits(ce->paddr_rri));
	ath10k_ce_ग_लिखो32(ar, ar->hw_ce_regs->ce_rri_high,
			  (upper_32_bits(ce->paddr_rri) &
			  CE_DESC_ADDR_HI_MASK));

	क्रम (i = 0; i < CE_COUNT; i++) अणु
		ctrl1_regs = ar->hw_ce_regs->ctrl1_regs->addr;
		ce_base_addr = ath10k_ce_base_address(ar, i);
		value = ath10k_ce_पढ़ो32(ar, ce_base_addr + ctrl1_regs);
		value |= ar->hw_ce_regs->upd->mask;
		ath10k_ce_ग_लिखो32(ar, ce_base_addr + ctrl1_regs, value);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(ath10k_ce_alloc_rri);

व्योम ath10k_ce_मुक्त_rri(काष्ठा ath10k *ar)
अणु
	काष्ठा ath10k_ce *ce = ath10k_ce_priv(ar);

	dma_मुक्त_coherent(ar->dev, (CE_COUNT * माप(u32)),
			  ce->vaddr_rri,
			  ce->paddr_rri);
पूर्ण
EXPORT_SYMBOL(ath10k_ce_मुक्त_rri);
