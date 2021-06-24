<शैली गुरु>
/*
 * net/tipc/group.h: Include file क्रम TIPC group unicast/multicast functions
 *
 * Copyright (c) 2017, Ericsson AB
 * Copyright (c) 2020, Red Hat Inc
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

#अगर_अघोषित _TIPC_GROUP_H
#घोषणा _TIPC_GROUP_H

#समावेश "core.h"

काष्ठा tipc_group;
काष्ठा tipc_member;
काष्ठा tipc_msg;

काष्ठा tipc_group *tipc_group_create(काष्ठा net *net, u32 portid,
				     काष्ठा tipc_group_req *mreq,
				     bool *group_is_खोलो);
व्योम tipc_group_join(काष्ठा net *net, काष्ठा tipc_group *grp, पूर्णांक *sk_rcv_buf);
व्योम tipc_group_delete(काष्ठा net *net, काष्ठा tipc_group *grp);
व्योम tipc_group_add_member(काष्ठा tipc_group *grp, u32 node,
			   u32 port, u32 instance);
काष्ठा tipc_nlist *tipc_group_dests(काष्ठा tipc_group *grp);
व्योम tipc_group_self(काष्ठा tipc_group *grp, काष्ठा tipc_service_range *seq,
		     पूर्णांक *scope);
u32 tipc_group_exclude(काष्ठा tipc_group *grp);
व्योम tipc_group_filter_msg(काष्ठा tipc_group *grp,
			   काष्ठा sk_buff_head *inputq,
			   काष्ठा sk_buff_head *xmitq);
व्योम tipc_group_member_evt(काष्ठा tipc_group *grp, bool *wakeup,
			   पूर्णांक *sk_rcvbuf, काष्ठा tipc_msg *hdr,
			   काष्ठा sk_buff_head *inputq,
			   काष्ठा sk_buff_head *xmitq);
व्योम tipc_group_proto_rcv(काष्ठा tipc_group *grp, bool *wakeup,
			  काष्ठा tipc_msg *hdr,
			  काष्ठा sk_buff_head *inputq,
			  काष्ठा sk_buff_head *xmitq);
व्योम tipc_group_update_bc_members(काष्ठा tipc_group *grp, पूर्णांक len, bool ack);
bool tipc_group_cong(काष्ठा tipc_group *grp, u32 dnode, u32 dport,
		     पूर्णांक len, काष्ठा tipc_member **m);
bool tipc_group_bc_cong(काष्ठा tipc_group *grp, पूर्णांक len);
व्योम tipc_group_update_rcv_win(काष्ठा tipc_group *grp, पूर्णांक blks, u32 node,
			       u32 port, काष्ठा sk_buff_head *xmitq);
u16 tipc_group_bc_snd_nxt(काष्ठा tipc_group *grp);
व्योम tipc_group_update_member(काष्ठा tipc_member *m, पूर्णांक len);
पूर्णांक tipc_group_fill_sock_diag(काष्ठा tipc_group *grp, काष्ठा sk_buff *skb);
#पूर्ण_अगर
