<शैली गुरु>
/**
 * Copyright (c) 2017 Redpine Signals Inc.
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

#अगर_अघोषित __RSI_HEADER_H__
#घोषणा __RSI_HEADER_H__

#समावेश <linux/skbuff.h>

/* HAL queue inक्रमmation */
#घोषणा RSI_COEX_Q			0x0
#घोषणा RSI_BT_Q			0x2
#घोषणा RSI_WLAN_Q                      0x3
#घोषणा RSI_WIFI_MGMT_Q                 0x4
#घोषणा RSI_WIFI_DATA_Q                 0x5
#घोषणा RSI_BT_MGMT_Q			0x6
#घोषणा RSI_BT_DATA_Q			0x7

क्रमागत rsi_coex_queues अणु
	RSI_COEX_Q_INVALID = -1,
	RSI_COEX_Q_COMMON = 0,
	RSI_COEX_Q_BT,
	RSI_COEX_Q_WLAN
पूर्ण;

क्रमागत rsi_host_पूर्णांकf अणु
	RSI_HOST_INTF_SDIO = 0,
	RSI_HOST_INTF_USB
पूर्ण;

काष्ठा rsi_proto_ops अणु
	पूर्णांक (*coex_send_pkt)(व्योम *priv, काष्ठा sk_buff *skb, u8 hal_queue);
	क्रमागत rsi_host_पूर्णांकf (*get_host_पूर्णांकf)(व्योम *priv);
	व्योम (*set_bt_context)(व्योम *priv, व्योम *context);
पूर्ण;

काष्ठा rsi_mod_ops अणु
	पूर्णांक (*attach)(व्योम *priv, काष्ठा rsi_proto_ops *ops);
	व्योम (*detach)(व्योम *priv);
	पूर्णांक (*recv_pkt)(व्योम *priv, स्थिर u8 *msg);
पूर्ण;

बाह्य स्थिर काष्ठा rsi_mod_ops rsi_bt_ops;
#पूर्ण_अगर
