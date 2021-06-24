<शैली गुरु>
/* net/tipc/socket.h: Include file क्रम TIPC socket code
 *
 * Copyright (c) 2014-2016, Ericsson AB
 * All rights reserved.
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary क्रमm must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    करोcumentation and/or other materials provided with the distribution.
 * 3. Neither the names of the copyright holders nor the names of its
 *    contributors may be used to enकरोrse or promote products derived from
 *    this software without specअगरic prior written permission.
 *
 * Alternatively, this software may be distributed under the terms of the
 * GNU General Public License ("GPL") version 2 as published by the Free
 * Software Foundation.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#अगर_अघोषित _TIPC_SOCK_H
#घोषणा _TIPC_SOCK_H

#समावेश <net/sock.h>
#समावेश <net/genetlink.h>

/* Compatibility values क्रम deprecated message based flow control */
#घोषणा FLOWCTL_MSG_WIN 512
#घोषणा FLOWCTL_MSG_LIM ((FLOWCTL_MSG_WIN * 2 + 1) * SKB_TRUESIZE(MAX_MSG_SIZE))

#घोषणा FLOWCTL_BLK_SZ 1024

/* Socket receive buffer sizes */
#घोषणा RCVBUF_MIN  (FLOWCTL_BLK_SZ * 512)
#घोषणा RCVBUF_DEF  (FLOWCTL_BLK_SZ * 1024 * 2)
#घोषणा RCVBUF_MAX  (FLOWCTL_BLK_SZ * 1024 * 16)

काष्ठा tipc_sock;

पूर्णांक tipc_socket_init(व्योम);
व्योम tipc_socket_stop(व्योम);
व्योम tipc_sk_rcv(काष्ठा net *net, काष्ठा sk_buff_head *inputq);
व्योम tipc_sk_mcast_rcv(काष्ठा net *net, काष्ठा sk_buff_head *arrvq,
		       काष्ठा sk_buff_head *inputq);
व्योम tipc_sk_reinit(काष्ठा net *net);
पूर्णांक tipc_sk_rht_init(काष्ठा net *net);
व्योम tipc_sk_rht_destroy(काष्ठा net *net);
पूर्णांक tipc_nl_sk_dump(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb);
पूर्णांक tipc_nl_publ_dump(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb);
पूर्णांक tipc_sk_fill_sock_diag(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb,
			   काष्ठा tipc_sock *tsk, u32 sk_filter_state,
			   u64 (*tipc_diag_gen_cookie)(काष्ठा sock *sk));
पूर्णांक tipc_nl_sk_walk(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb,
		    पूर्णांक (*skb_handler)(काष्ठा sk_buff *skb,
				       काष्ठा netlink_callback *cb,
				       काष्ठा tipc_sock *tsk));
पूर्णांक tipc_dump_start(काष्ठा netlink_callback *cb);
पूर्णांक __tipc_dump_start(काष्ठा netlink_callback *cb, काष्ठा net *net);
पूर्णांक tipc_dump_करोne(काष्ठा netlink_callback *cb);
u32 tipc_sock_get_portid(काष्ठा sock *sk);
bool tipc_sk_overlimit1(काष्ठा sock *sk, काष्ठा sk_buff *skb);
bool tipc_sk_overlimit2(काष्ठा sock *sk, काष्ठा sk_buff *skb);
पूर्णांक tipc_sk_bind(काष्ठा socket *sock, काष्ठा sockaddr *skaddr, पूर्णांक alen);
पूर्णांक tsk_set_importance(काष्ठा sock *sk, पूर्णांक imp);

#पूर्ण_अगर
