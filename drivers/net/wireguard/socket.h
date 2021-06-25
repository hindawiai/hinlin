<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2015-2019 Jason A. Donenfeld <Jason@zx2c4.com>. All Rights Reserved.
 */

#अगर_अघोषित _WG_SOCKET_H
#घोषणा _WG_SOCKET_H

#समावेश <linux/netdevice.h>
#समावेश <linux/udp.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/अगर_ether.h>

पूर्णांक wg_socket_init(काष्ठा wg_device *wg, u16 port);
व्योम wg_socket_reinit(काष्ठा wg_device *wg, काष्ठा sock *new4,
		      काष्ठा sock *new6);
पूर्णांक wg_socket_send_buffer_to_peer(काष्ठा wg_peer *peer, व्योम *data,
				  माप_प्रकार len, u8 ds);
पूर्णांक wg_socket_send_skb_to_peer(काष्ठा wg_peer *peer, काष्ठा sk_buff *skb,
			       u8 ds);
पूर्णांक wg_socket_send_buffer_as_reply_to_skb(काष्ठा wg_device *wg,
					  काष्ठा sk_buff *in_skb,
					  व्योम *out_buffer, माप_प्रकार len);

पूर्णांक wg_socket_endpoपूर्णांक_from_skb(काष्ठा endpoपूर्णांक *endpoपूर्णांक,
				स्थिर काष्ठा sk_buff *skb);
व्योम wg_socket_set_peer_endpoपूर्णांक(काष्ठा wg_peer *peer,
				 स्थिर काष्ठा endpoपूर्णांक *endpoपूर्णांक);
व्योम wg_socket_set_peer_endpoपूर्णांक_from_skb(काष्ठा wg_peer *peer,
					  स्थिर काष्ठा sk_buff *skb);
व्योम wg_socket_clear_peer_endpoपूर्णांक_src(काष्ठा wg_peer *peer);

#अगर defined(CONFIG_DYNAMIC_DEBUG) || defined(DEBUG)
#घोषणा net_dbg_skb_ratelimited(fmt, dev, skb, ...) करो अणु                       \
		काष्ठा endpoपूर्णांक __endpoपूर्णांक;                                    \
		wg_socket_endpoपूर्णांक_from_skb(&__endpoपूर्णांक, skb);                 \
		net_dbg_ratelimited(fmt, dev, &__endpoपूर्णांक.addr,                \
				    ##__VA_ARGS__);                            \
	पूर्ण जबतक (0)
#अन्यथा
#घोषणा net_dbg_skb_ratelimited(fmt, skb, ...)
#पूर्ण_अगर

#पूर्ण_अगर /* _WG_SOCKET_H */
