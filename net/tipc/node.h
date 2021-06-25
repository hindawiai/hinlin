<शैली गुरु>
/*
 * net/tipc/node.h: Include file क्रम TIPC node management routines
 *
 * Copyright (c) 2000-2006, 2014-2016, Ericsson AB
 * Copyright (c) 2005, 2010-2014, Wind River Systems
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

#अगर_अघोषित _TIPC_NODE_H
#घोषणा _TIPC_NODE_H

#समावेश "addr.h"
#समावेश "net.h"
#समावेश "bearer.h"
#समावेश "msg.h"

/* Optional capabilities supported by this code version
 */
क्रमागत अणु
	TIPC_SYN_BIT          = (1),
	TIPC_BCAST_SYNCH      = (1 << 1),
	TIPC_BCAST_STATE_NACK = (1 << 2),
	TIPC_BLOCK_FLOWCTL    = (1 << 3),
	TIPC_BCAST_RCAST      = (1 << 4),
	TIPC_NODE_ID128       = (1 << 5),
	TIPC_LINK_PROTO_SEQNO = (1 << 6),
	TIPC_MCAST_RBCTL      = (1 << 7),
	TIPC_GAP_ACK_BLOCK    = (1 << 8),
	TIPC_TUNNEL_ENHANCED  = (1 << 9),
	TIPC_NAGLE            = (1 << 10),
	TIPC_NAMED_BCAST      = (1 << 11)
पूर्ण;

#घोषणा TIPC_NODE_CAPABILITIES (TIPC_SYN_BIT           |  \
				TIPC_BCAST_SYNCH       |   \
				TIPC_BCAST_STATE_NACK  |   \
				TIPC_BCAST_RCAST       |   \
				TIPC_BLOCK_FLOWCTL     |   \
				TIPC_NODE_ID128        |   \
				TIPC_LINK_PROTO_SEQNO  |   \
				TIPC_MCAST_RBCTL       |   \
				TIPC_GAP_ACK_BLOCK     |   \
				TIPC_TUNNEL_ENHANCED   |   \
				TIPC_NAGLE             |   \
				TIPC_NAMED_BCAST)

#घोषणा INVALID_BEARER_ID -1

व्योम tipc_node_stop(काष्ठा net *net);
bool tipc_node_get_id(काष्ठा net *net, u32 addr, u8 *id);
u32 tipc_node_get_addr(काष्ठा tipc_node *node);
अक्षर *tipc_node_get_id_str(काष्ठा tipc_node *node);
व्योम tipc_node_put(काष्ठा tipc_node *node);
व्योम tipc_node_get(काष्ठा tipc_node *node);
काष्ठा tipc_node *tipc_node_create(काष्ठा net *net, u32 addr, u8 *peer_id,
				   u16 capabilities, u32 hash_mixes,
				   bool preliminary);
#अगर_घोषित CONFIG_TIPC_CRYPTO
काष्ठा tipc_crypto *tipc_node_crypto_rx(काष्ठा tipc_node *__n);
काष्ठा tipc_crypto *tipc_node_crypto_rx_by_list(काष्ठा list_head *pos);
काष्ठा tipc_crypto *tipc_node_crypto_rx_by_addr(काष्ठा net *net, u32 addr);
#पूर्ण_अगर
u32 tipc_node_try_addr(काष्ठा net *net, u8 *id, u32 addr);
व्योम tipc_node_check_dest(काष्ठा net *net, u32 onode, u8 *peer_id128,
			  काष्ठा tipc_bearer *bearer,
			  u16 capabilities, u32 signature, u32 hash_mixes,
			  काष्ठा tipc_media_addr *maddr,
			  bool *respond, bool *dupl_addr);
व्योम tipc_node_delete_links(काष्ठा net *net, पूर्णांक bearer_id);
व्योम tipc_node_apply_property(काष्ठा net *net, काष्ठा tipc_bearer *b, पूर्णांक prop);
पूर्णांक tipc_node_get_linkname(काष्ठा net *net, u32 bearer_id, u32 node,
			   अक्षर *linkname, माप_प्रकार len);
पूर्णांक tipc_node_xmit(काष्ठा net *net, काष्ठा sk_buff_head *list, u32 dnode,
		   पूर्णांक selector);
पूर्णांक tipc_node_distr_xmit(काष्ठा net *net, काष्ठा sk_buff_head *list);
पूर्णांक tipc_node_xmit_skb(काष्ठा net *net, काष्ठा sk_buff *skb, u32 dest,
		       u32 selector);
व्योम tipc_node_subscribe(काष्ठा net *net, काष्ठा list_head *subscr, u32 addr);
व्योम tipc_node_unsubscribe(काष्ठा net *net, काष्ठा list_head *subscr, u32 addr);
व्योम tipc_node_broadcast(काष्ठा net *net, काष्ठा sk_buff *skb, पूर्णांक rc_dests);
पूर्णांक tipc_node_add_conn(काष्ठा net *net, u32 dnode, u32 port, u32 peer_port);
व्योम tipc_node_हटाओ_conn(काष्ठा net *net, u32 dnode, u32 port);
पूर्णांक tipc_node_get_mtu(काष्ठा net *net, u32 addr, u32 sel, bool connected);
bool tipc_node_is_up(काष्ठा net *net, u32 addr);
u16 tipc_node_get_capabilities(काष्ठा net *net, u32 addr);
पूर्णांक tipc_nl_node_dump(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb);
पूर्णांक tipc_nl_node_dump_link(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb);
पूर्णांक tipc_nl_node_reset_link_stats(काष्ठा sk_buff *skb, काष्ठा genl_info *info);
पूर्णांक tipc_nl_node_get_link(काष्ठा sk_buff *skb, काष्ठा genl_info *info);
पूर्णांक tipc_nl_node_set_link(काष्ठा sk_buff *skb, काष्ठा genl_info *info);
पूर्णांक tipc_nl_peer_rm(काष्ठा sk_buff *skb, काष्ठा genl_info *info);

पूर्णांक tipc_nl_node_set_monitor(काष्ठा sk_buff *skb, काष्ठा genl_info *info);
पूर्णांक tipc_nl_node_get_monitor(काष्ठा sk_buff *skb, काष्ठा genl_info *info);
पूर्णांक tipc_nl_node_dump_monitor(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb);
पूर्णांक tipc_nl_node_dump_monitor_peer(काष्ठा sk_buff *skb,
				   काष्ठा netlink_callback *cb);
#अगर_घोषित CONFIG_TIPC_CRYPTO
पूर्णांक tipc_nl_node_set_key(काष्ठा sk_buff *skb, काष्ठा genl_info *info);
पूर्णांक tipc_nl_node_flush_key(काष्ठा sk_buff *skb, काष्ठा genl_info *info);
#पूर्ण_अगर
व्योम tipc_node_pre_cleanup_net(काष्ठा net *निकास_net);
#पूर्ण_अगर
