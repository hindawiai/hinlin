<शैली गुरु>
/*
 * Copyright (c) 2018 Redpine Signals Inc.
 *
 * Permission to use, copy, modअगरy, and/or distribute this software क्रम any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, सूचीECT, INसूचीECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#अगर_अघोषित __RSI_COEX_H__
#घोषणा __RSI_COEX_H__

#समावेश "rsi_common.h"

#अगर_घोषित CONFIG_RSI_COEX
#घोषणा COMMON_CARD_READY_IND           0
#घोषणा NUM_COEX_TX_QUEUES              5

काष्ठा rsi_coex_ctrl_block अणु
	काष्ठा rsi_common *priv;
	काष्ठा sk_buff_head coex_tx_qs[NUM_COEX_TX_QUEUES];
	काष्ठा rsi_thपढ़ो coex_tx_thपढ़ो;
पूर्ण;

पूर्णांक rsi_coex_attach(काष्ठा rsi_common *common);
व्योम rsi_coex_detach(काष्ठा rsi_common *common);
पूर्णांक rsi_coex_send_pkt(व्योम *priv, काष्ठा sk_buff *skb, u8 proto_type);
पूर्णांक rsi_coex_recv_pkt(काष्ठा rsi_common *common, u8 *msg);
#पूर्ण_अगर
#पूर्ण_अगर
