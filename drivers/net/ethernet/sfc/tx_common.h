<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/****************************************************************************
 * Driver क्रम Solarflare network controllers and boards
 * Copyright 2018 Solarflare Communications Inc.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy it
 * under the terms of the GNU General Public License version 2 as published
 * by the Free Software Foundation, incorporated herein by reference.
 */

#अगर_अघोषित EFX_TX_COMMON_H
#घोषणा EFX_TX_COMMON_H

पूर्णांक efx_probe_tx_queue(काष्ठा efx_tx_queue *tx_queue);
व्योम efx_init_tx_queue(काष्ठा efx_tx_queue *tx_queue);
व्योम efx_fini_tx_queue(काष्ठा efx_tx_queue *tx_queue);
व्योम efx_हटाओ_tx_queue(काष्ठा efx_tx_queue *tx_queue);

व्योम efx_dequeue_buffer(काष्ठा efx_tx_queue *tx_queue,
			काष्ठा efx_tx_buffer *buffer,
			अचिन्हित पूर्णांक *pkts_compl,
			अचिन्हित पूर्णांक *bytes_compl);

अटल अंतरभूत bool efx_tx_buffer_in_use(काष्ठा efx_tx_buffer *buffer)
अणु
	वापस buffer->len || (buffer->flags & EFX_TX_BUF_OPTION);
पूर्ण

व्योम efx_xmit_करोne_check_empty(काष्ठा efx_tx_queue *tx_queue);
व्योम efx_xmit_करोne(काष्ठा efx_tx_queue *tx_queue, अचिन्हित पूर्णांक index);

व्योम efx_enqueue_unwind(काष्ठा efx_tx_queue *tx_queue,
			अचिन्हित पूर्णांक insert_count);

काष्ठा efx_tx_buffer *efx_tx_map_chunk(काष्ठा efx_tx_queue *tx_queue,
				       dma_addr_t dma_addr, माप_प्रकार len);
पूर्णांक efx_tx_tso_header_length(काष्ठा sk_buff *skb);
पूर्णांक efx_tx_map_data(काष्ठा efx_tx_queue *tx_queue, काष्ठा sk_buff *skb,
		    अचिन्हित पूर्णांक segment_count);

अचिन्हित पूर्णांक efx_tx_max_skb_descs(काष्ठा efx_nic *efx);
पूर्णांक efx_tx_tso_fallback(काष्ठा efx_tx_queue *tx_queue, काष्ठा sk_buff *skb);

बाह्य bool efx_separate_tx_channels;
#पूर्ण_अगर
