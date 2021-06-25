<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/****************************************************************************
 * Driver क्रम Solarflare network controllers and boards
 * Copyright 2005-2019 Solarflare Communications Inc.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy it
 * under the terms of the GNU General Public License version 2 as published
 * by the Free Software Foundation, incorporated herein by reference.
 */

#समावेश "net_driver.h"
#समावेश "ef100_rx.h"
#समावेश "rx_common.h"
#समावेश "efx.h"
#समावेश "nic_common.h"
#समावेश "mcdi_functions.h"
#समावेश "ef100_regs.h"
#समावेश "ef100_nic.h"
#समावेश "io.h"

/* Get the value of a field in the RX prefix */
#घोषणा PREFIX_OFFSET_W(_f)	(ESF_GZ_RX_PREFIX_ ## _f ## _LBN / 32)
#घोषणा PREFIX_OFFSET_B(_f)	(ESF_GZ_RX_PREFIX_ ## _f ## _LBN % 32)
#घोषणा PREFIX_WIDTH_MASK(_f)	((1UL << ESF_GZ_RX_PREFIX_ ## _f ## _WIDTH) - 1)
#घोषणा PREFIX_WORD(_p, _f)	le32_to_cpu((__क्रमce __le32)(_p)[PREFIX_OFFSET_W(_f)])
#घोषणा PREFIX_FIELD(_p, _f)	((PREFIX_WORD(_p, _f) >> PREFIX_OFFSET_B(_f)) & \
				 PREFIX_WIDTH_MASK(_f))

#घोषणा ESF_GZ_RX_PREFIX_NT_OR_INNER_L3_CLASS_LBN	\
		(ESF_GZ_RX_PREFIX_CLASS_LBN + ESF_GZ_RX_PREFIX_HCLASS_NT_OR_INNER_L3_CLASS_LBN)
#घोषणा ESF_GZ_RX_PREFIX_NT_OR_INNER_L3_CLASS_WIDTH	\
		ESF_GZ_RX_PREFIX_HCLASS_NT_OR_INNER_L3_CLASS_WIDTH

bool ef100_rx_buf_hash_valid(स्थिर u8 *prefix)
अणु
	वापस PREFIX_FIELD(prefix, RSS_HASH_VALID);
पूर्ण

अटल bool ef100_has_fcs_error(काष्ठा efx_channel *channel, u32 *prefix)
अणु
	u16 rxclass;
	u8 l2status;

	rxclass = le16_to_cpu((__क्रमce __le16)PREFIX_FIELD(prefix, CLASS));
	l2status = PREFIX_FIELD(&rxclass, HCLASS_L2_STATUS);

	अगर (likely(l2status == ESE_GZ_RH_HCLASS_L2_STATUS_OK))
		/* Everything is ok */
		वापस false;

	अगर (l2status == ESE_GZ_RH_HCLASS_L2_STATUS_FCS_ERR)
		channel->n_rx_eth_crc_err++;
	वापस true;
पूर्ण

व्योम __ef100_rx_packet(काष्ठा efx_channel *channel)
अणु
	काष्ठा efx_rx_buffer *rx_buf = efx_rx_buffer(&channel->rx_queue, channel->rx_pkt_index);
	काष्ठा efx_nic *efx = channel->efx;
	u8 *eh = efx_rx_buf_va(rx_buf);
	__wsum csum = 0;
	u32 *prefix;

	prefix = (u32 *)(eh - ESE_GZ_RX_PKT_PREFIX_LEN);

	अगर (ef100_has_fcs_error(channel, prefix) &&
	    unlikely(!(efx->net_dev->features & NETIF_F_RXALL)))
		जाओ out;

	rx_buf->len = le16_to_cpu((__क्रमce __le16)PREFIX_FIELD(prefix, LENGTH));
	अगर (rx_buf->len <= माप(काष्ठा ethhdr)) अणु
		अगर (net_ratelimit())
			netअगर_err(channel->efx, rx_err, channel->efx->net_dev,
				  "RX packet too small (%d)\n", rx_buf->len);
		++channel->n_rx_frm_trunc;
		जाओ out;
	पूर्ण

	अगर (likely(efx->net_dev->features & NETIF_F_RXCSUM)) अणु
		अगर (PREFIX_FIELD(prefix, NT_OR_INNER_L3_CLASS) == 1) अणु
			++channel->n_rx_ip_hdr_chksum_err;
		पूर्ण अन्यथा अणु
			u16 sum = be16_to_cpu((__क्रमce __be16)PREFIX_FIELD(prefix, CSUM_FRAME));

			csum = (__क्रमce __wsum) sum;
		पूर्ण
	पूर्ण

	अगर (channel->type->receive_skb) अणु
		काष्ठा efx_rx_queue *rx_queue =
			efx_channel_get_rx_queue(channel);

		/* no support क्रम special channels yet, so just discard */
		WARN_ON_ONCE(1);
		efx_मुक्त_rx_buffers(rx_queue, rx_buf, 1);
		जाओ out;
	पूर्ण

	efx_rx_packet_gro(channel, rx_buf, channel->rx_pkt_n_frags, eh, csum);

out:
	channel->rx_pkt_n_frags = 0;
पूर्ण

अटल व्योम ef100_rx_packet(काष्ठा efx_rx_queue *rx_queue, अचिन्हित पूर्णांक index)
अणु
	काष्ठा efx_rx_buffer *rx_buf = efx_rx_buffer(rx_queue, index);
	काष्ठा efx_channel *channel = efx_rx_queue_channel(rx_queue);
	काष्ठा efx_nic *efx = rx_queue->efx;

	++rx_queue->rx_packets;

	netअगर_vdbg(efx, rx_status, efx->net_dev,
		   "RX queue %d received id %x\n",
		   efx_rx_queue_index(rx_queue), index);

	efx_sync_rx_buffer(efx, rx_buf, efx->rx_dma_len);

	prefetch(efx_rx_buf_va(rx_buf));

	rx_buf->page_offset += efx->rx_prefix_size;

	efx_recycle_rx_pages(channel, rx_buf, 1);

	efx_rx_flush_packet(channel);
	channel->rx_pkt_n_frags = 1;
	channel->rx_pkt_index = index;
पूर्ण

व्योम efx_ef100_ev_rx(काष्ठा efx_channel *channel, स्थिर efx_qword_t *p_event)
अणु
	काष्ठा efx_rx_queue *rx_queue = efx_channel_get_rx_queue(channel);
	अचिन्हित पूर्णांक n_packets =
		EFX_QWORD_FIELD(*p_event, ESF_GZ_EV_RXPKTS_NUM_PKT);
	पूर्णांक i;

	WARN_ON_ONCE(!n_packets);
	अगर (n_packets > 1)
		++channel->n_rx_merge_events;

	channel->irq_mod_score += 2 * n_packets;

	क्रम (i = 0; i < n_packets; ++i) अणु
		ef100_rx_packet(rx_queue,
				rx_queue->हटाओd_count & rx_queue->ptr_mask);
		++rx_queue->हटाओd_count;
	पूर्ण
पूर्ण

व्योम ef100_rx_ग_लिखो(काष्ठा efx_rx_queue *rx_queue)
अणु
	काष्ठा efx_rx_buffer *rx_buf;
	अचिन्हित पूर्णांक idx;
	efx_qword_t *rxd;
	efx_dword_t rxdb;

	जबतक (rx_queue->notअगरied_count != rx_queue->added_count) अणु
		idx = rx_queue->notअगरied_count & rx_queue->ptr_mask;
		rx_buf = efx_rx_buffer(rx_queue, idx);
		rxd = efx_rx_desc(rx_queue, idx);

		EFX_POPULATE_QWORD_1(*rxd, ESF_GZ_RX_BUF_ADDR, rx_buf->dma_addr);

		++rx_queue->notअगरied_count;
	पूर्ण

	wmb();
	EFX_POPULATE_DWORD_1(rxdb, ERF_GZ_RX_RING_PIDX,
			     rx_queue->added_count & rx_queue->ptr_mask);
	efx_ग_लिखोd_page(rx_queue->efx, &rxdb,
			ER_GZ_RX_RING_DOORBELL, efx_rx_queue_index(rx_queue));
पूर्ण
