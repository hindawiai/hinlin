<शैली गुरु>
/*
 * net/tipc/bcast.h: Include file क्रम TIPC broadcast code
 *
 * Copyright (c) 2003-2006, 2014-2015, Ericsson AB
 * Copyright (c) 2005, 2010-2011, Wind River Systems
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

#अगर_अघोषित _TIPC_BCAST_H
#घोषणा _TIPC_BCAST_H

#समावेश "core.h"

काष्ठा tipc_node;
काष्ठा tipc_msg;
काष्ठा tipc_nl_msg;
काष्ठा tipc_nlist;
काष्ठा tipc_nitem;
बाह्य स्थिर अक्षर tipc_bclink_name[];
बाह्य अचिन्हित दीर्घ sysctl_tipc_bc_retruni;

#घोषणा TIPC_METHOD_EXPIRE msecs_to_jअगरfies(5000)

#घोषणा BCLINK_MODE_BCAST  0x1
#घोषणा BCLINK_MODE_RCAST  0x2
#घोषणा BCLINK_MODE_SEL    0x4

काष्ठा tipc_nlist अणु
	काष्ठा list_head list;
	u32 self;
	u16 remote;
	bool local;
पूर्ण;

व्योम tipc_nlist_init(काष्ठा tipc_nlist *nl, u32 self);
व्योम tipc_nlist_purge(काष्ठा tipc_nlist *nl);
व्योम tipc_nlist_add(काष्ठा tipc_nlist *nl, u32 node);
व्योम tipc_nlist_del(काष्ठा tipc_nlist *nl, u32 node);

/* Cookie to be used between socket and broadcast layer
 * @rcast: replicast (instead of broadcast) was used at previous xmit
 * @mandatory: broadcast/replicast indication was set by user
 * @deferredq: defer queue to make message in order
 * @expires: re-evaluate non-mandatory transmit method अगर we are past this
 */
काष्ठा tipc_mc_method अणु
	bool rcast;
	bool mandatory;
	काष्ठा sk_buff_head deferredq;
	अचिन्हित दीर्घ expires;
पूर्ण;

पूर्णांक tipc_bcast_init(काष्ठा net *net);
व्योम tipc_bcast_stop(काष्ठा net *net);
व्योम tipc_bcast_add_peer(काष्ठा net *net, काष्ठा tipc_link *l,
			 काष्ठा sk_buff_head *xmitq);
व्योम tipc_bcast_हटाओ_peer(काष्ठा net *net, काष्ठा tipc_link *rcv_bcl);
व्योम tipc_bcast_inc_bearer_dst_cnt(काष्ठा net *net, पूर्णांक bearer_id);
व्योम tipc_bcast_dec_bearer_dst_cnt(काष्ठा net *net, पूर्णांक bearer_id);
पूर्णांक  tipc_bcast_get_mtu(काष्ठा net *net);
व्योम tipc_bcast_toggle_rcast(काष्ठा net *net, bool supp);
पूर्णांक tipc_mcast_xmit(काष्ठा net *net, काष्ठा sk_buff_head *pkts,
		    काष्ठा tipc_mc_method *method, काष्ठा tipc_nlist *dests,
		    u16 *cong_link_cnt);
पूर्णांक tipc_bcast_xmit(काष्ठा net *net, काष्ठा sk_buff_head *pkts,
		    u16 *cong_link_cnt);
पूर्णांक tipc_bcast_rcv(काष्ठा net *net, काष्ठा tipc_link *l, काष्ठा sk_buff *skb);
व्योम tipc_bcast_ack_rcv(काष्ठा net *net, काष्ठा tipc_link *l,
			काष्ठा tipc_msg *hdr);
पूर्णांक tipc_bcast_sync_rcv(काष्ठा net *net, काष्ठा tipc_link *l,
			काष्ठा tipc_msg *hdr,
			काष्ठा sk_buff_head *retrq);
पूर्णांक tipc_nl_add_bc_link(काष्ठा net *net, काष्ठा tipc_nl_msg *msg,
			काष्ठा tipc_link *bcl);
पूर्णांक tipc_nl_bc_link_set(काष्ठा net *net, काष्ठा nlattr *attrs[]);
पूर्णांक tipc_bclink_reset_stats(काष्ठा net *net, काष्ठा tipc_link *l);

u32 tipc_bcast_get_mode(काष्ठा net *net);
u32 tipc_bcast_get_broadcast_ratio(काष्ठा net *net);

व्योम tipc_mcast_filter_msg(काष्ठा net *net, काष्ठा sk_buff_head *defq,
			   काष्ठा sk_buff_head *inputq);

अटल अंतरभूत व्योम tipc_bcast_lock(काष्ठा net *net)
अणु
	spin_lock_bh(&tipc_net(net)->bघड़ी);
पूर्ण

अटल अंतरभूत व्योम tipc_bcast_unlock(काष्ठा net *net)
अणु
	spin_unlock_bh(&tipc_net(net)->bघड़ी);
पूर्ण

अटल अंतरभूत काष्ठा tipc_link *tipc_bc_sndlink(काष्ठा net *net)
अणु
	वापस tipc_net(net)->bcl;
पूर्ण

#पूर्ण_अगर
