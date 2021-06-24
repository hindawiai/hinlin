<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * NET		Generic infraकाष्ठाure क्रम INET6 connection oriented protocols.
 *
 * Authors:	Many people, see the TCPv6 sources
 *
 * 		From code originally in TCPv6
 */
#अगर_अघोषित _INET6_CONNECTION_SOCK_H
#घोषणा _INET6_CONNECTION_SOCK_H

#समावेश <linux/types.h>

काष्ठा request_sock;
काष्ठा sk_buff;
काष्ठा sock;
काष्ठा sockaddr;

काष्ठा dst_entry *inet6_csk_route_req(स्थिर काष्ठा sock *sk, काष्ठा flowi6 *fl6,
				      स्थिर काष्ठा request_sock *req, u8 proto);

व्योम inet6_csk_addr2sockaddr(काष्ठा sock *sk, काष्ठा sockaddr *uaddr);

पूर्णांक inet6_csk_xmit(काष्ठा sock *sk, काष्ठा sk_buff *skb, काष्ठा flowi *fl);

काष्ठा dst_entry *inet6_csk_update_pmtu(काष्ठा sock *sk, u32 mtu);
#पूर्ण_अगर /* _INET6_CONNECTION_SOCK_H */
