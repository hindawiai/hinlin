<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/****************************************************************************
 * Driver क्रम Solarflare network controllers and boards
 * Copyright 2005-2006 Fen Systems Ltd.
 * Copyright 2006-2015 Solarflare Communications Inc.
 */

#अगर_अघोषित EF4_TX_H
#घोषणा EF4_TX_H

#समावेश <linux/types.h>

/* Driver पूर्णांकernal tx-path related declarations. */

अचिन्हित पूर्णांक ef4_tx_limit_len(काष्ठा ef4_tx_queue *tx_queue,
			      dma_addr_t dma_addr, अचिन्हित पूर्णांक len);

u8 *ef4_tx_get_copy_buffer_limited(काष्ठा ef4_tx_queue *tx_queue,
				   काष्ठा ef4_tx_buffer *buffer, माप_प्रकार len);

पूर्णांक ef4_enqueue_skb_tso(काष्ठा ef4_tx_queue *tx_queue, काष्ठा sk_buff *skb,
			bool *data_mapped);

#पूर्ण_अगर /* EF4_TX_H */
