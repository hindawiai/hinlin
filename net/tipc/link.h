<शैली गुरु>
/*
 * net/tipc/link.h: Include file क्रम TIPC link code
 *
 * Copyright (c) 1995-2006, 2013-2014, Ericsson AB
 * Copyright (c) 2004-2005, 2010-2011, Wind River Systems
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

#अगर_अघोषित _TIPC_LINK_H
#घोषणा _TIPC_LINK_H

#समावेश <net/genetlink.h>
#समावेश "msg.h"
#समावेश "node.h"

/* TIPC-specअगरic error codes
*/
#घोषणा ELINKCONG EAGAIN	/* link congestion <=> resource unavailable */

/* Link FSM events:
 */
क्रमागत अणु
	LINK_ESTABLISH_EVT       = 0xec1ab1e,
	LINK_PEER_RESET_EVT      = 0x9eed0e,
	LINK_FAILURE_EVT         = 0xfa110e,
	LINK_RESET_EVT           = 0x10ca1d0e,
	LINK_FAILOVER_BEGIN_EVT  = 0xfa110bee,
	LINK_FAILOVER_END_EVT    = 0xfa110ede,
	LINK_SYNCH_BEGIN_EVT     = 0xc1ccbee,
	LINK_SYNCH_END_EVT       = 0xc1ccede
पूर्ण;

/* Events वापसed from link at packet reception or at समयout
 */
क्रमागत अणु
	TIPC_LINK_UP_EVT       = 1,
	TIPC_LINK_DOWN_EVT     = (1 << 1),
	TIPC_LINK_SND_STATE    = (1 << 2)
पूर्ण;

/* Starting value क्रम maximum packet size negotiation on unicast links
 * (unless bearer MTU is less)
 */
#घोषणा MAX_PKT_DEFAULT 1500

bool tipc_link_create(काष्ठा net *net, अक्षर *अगर_name, पूर्णांक bearer_id,
		      पूर्णांक tolerance, अक्षर net_plane, u32 mtu, पूर्णांक priority,
		      u32 min_win, u32 max_win, u32 session, u32 ownnode,
		      u32 peer, u8 *peer_id, u16 peer_caps,
		      काष्ठा tipc_link *bc_sndlink,
		      काष्ठा tipc_link *bc_rcvlink,
		      काष्ठा sk_buff_head *inputq,
		      काष्ठा sk_buff_head *namedq,
		      काष्ठा tipc_link **link);
bool tipc_link_bc_create(काष्ठा net *net, u32 ownnode, u32 peer, u8 *peer_id,
			 पूर्णांक mtu, u32 min_win, u32 max_win, u16 peer_caps,
			 काष्ठा sk_buff_head *inputq,
			 काष्ठा sk_buff_head *namedq,
			 काष्ठा tipc_link *bc_sndlink,
			 काष्ठा tipc_link **link);
व्योम tipc_link_tnl_prepare(काष्ठा tipc_link *l, काष्ठा tipc_link *tnl,
			   पूर्णांक mtyp, काष्ठा sk_buff_head *xmitq);
व्योम tipc_link_create_dummy_tnl_msg(काष्ठा tipc_link *tnl,
				    काष्ठा sk_buff_head *xmitq);
व्योम tipc_link_failover_prepare(काष्ठा tipc_link *l, काष्ठा tipc_link *tnl,
				काष्ठा sk_buff_head *xmitq);
व्योम tipc_link_build_reset_msg(काष्ठा tipc_link *l, काष्ठा sk_buff_head *xmitq);
पूर्णांक tipc_link_fsm_evt(काष्ठा tipc_link *l, पूर्णांक evt);
bool tipc_link_is_up(काष्ठा tipc_link *l);
bool tipc_link_peer_is_करोwn(काष्ठा tipc_link *l);
bool tipc_link_is_reset(काष्ठा tipc_link *l);
bool tipc_link_is_establishing(काष्ठा tipc_link *l);
bool tipc_link_is_synching(काष्ठा tipc_link *l);
bool tipc_link_is_failingover(काष्ठा tipc_link *l);
bool tipc_link_is_blocked(काष्ठा tipc_link *l);
व्योम tipc_link_set_active(काष्ठा tipc_link *l, bool active);
व्योम tipc_link_reset(काष्ठा tipc_link *l);
व्योम tipc_link_reset_stats(काष्ठा tipc_link *l);
पूर्णांक tipc_link_xmit(काष्ठा tipc_link *link, काष्ठा sk_buff_head *list,
		   काष्ठा sk_buff_head *xmitq);
काष्ठा sk_buff_head *tipc_link_inputq(काष्ठा tipc_link *l);
u16 tipc_link_rcv_nxt(काष्ठा tipc_link *l);
u16 tipc_link_acked(काष्ठा tipc_link *l);
u32 tipc_link_id(काष्ठा tipc_link *l);
अक्षर *tipc_link_name(काष्ठा tipc_link *l);
u32 tipc_link_state(काष्ठा tipc_link *l);
अक्षर tipc_link_plane(काष्ठा tipc_link *l);
पूर्णांक tipc_link_prio(काष्ठा tipc_link *l);
पूर्णांक tipc_link_min_win(काष्ठा tipc_link *l);
पूर्णांक tipc_link_max_win(काष्ठा tipc_link *l);
व्योम tipc_link_update_caps(काष्ठा tipc_link *l, u16 capabilities);
bool tipc_link_validate_msg(काष्ठा tipc_link *l, काष्ठा tipc_msg *hdr);
अचिन्हित दीर्घ tipc_link_tolerance(काष्ठा tipc_link *l);
व्योम tipc_link_set_tolerance(काष्ठा tipc_link *l, u32 tol,
			     काष्ठा sk_buff_head *xmitq);
व्योम tipc_link_set_prio(काष्ठा tipc_link *l, u32 prio,
			काष्ठा sk_buff_head *xmitq);
व्योम tipc_link_set_पात_limit(काष्ठा tipc_link *l, u32 limit);
व्योम tipc_link_set_queue_limits(काष्ठा tipc_link *l, u32 min_win, u32 max_win);
पूर्णांक __tipc_nl_add_link(काष्ठा net *net, काष्ठा tipc_nl_msg *msg,
		       काष्ठा tipc_link *link, पूर्णांक nlflags);
पूर्णांक tipc_nl_parse_link_prop(काष्ठा nlattr *prop, काष्ठा nlattr *props[]);
पूर्णांक tipc_link_समयout(काष्ठा tipc_link *l, काष्ठा sk_buff_head *xmitq);
पूर्णांक tipc_link_rcv(काष्ठा tipc_link *l, काष्ठा sk_buff *skb,
		  काष्ठा sk_buff_head *xmitq);
पूर्णांक tipc_link_build_state_msg(काष्ठा tipc_link *l, काष्ठा sk_buff_head *xmitq);
व्योम tipc_link_add_bc_peer(काष्ठा tipc_link *snd_l,
			   काष्ठा tipc_link *uc_l,
			   काष्ठा sk_buff_head *xmitq);
व्योम tipc_link_हटाओ_bc_peer(काष्ठा tipc_link *snd_l,
			      काष्ठा tipc_link *rcv_l,
			      काष्ठा sk_buff_head *xmitq);
पूर्णांक tipc_link_bc_peers(काष्ठा tipc_link *l);
व्योम tipc_link_set_mtu(काष्ठा tipc_link *l, पूर्णांक mtu);
पूर्णांक tipc_link_mtu(काष्ठा tipc_link *l);
पूर्णांक tipc_link_mss(काष्ठा tipc_link *l);
u16 tipc_get_gap_ack_blks(काष्ठा tipc_gap_ack_blks **ga, काष्ठा tipc_link *l,
			  काष्ठा tipc_msg *hdr, bool uc);
पूर्णांक tipc_link_bc_ack_rcv(काष्ठा tipc_link *l, u16 acked, u16 gap,
			 काष्ठा tipc_gap_ack_blks *ga,
			 काष्ठा sk_buff_head *xmitq,
			 काष्ठा sk_buff_head *retrq);
व्योम tipc_link_build_bc_sync_msg(काष्ठा tipc_link *l,
				 काष्ठा sk_buff_head *xmitq);
व्योम tipc_link_bc_init_rcv(काष्ठा tipc_link *l, काष्ठा tipc_msg *hdr);
पूर्णांक tipc_link_bc_sync_rcv(काष्ठा tipc_link *l,   काष्ठा tipc_msg *hdr,
			  काष्ठा sk_buff_head *xmitq);
पूर्णांक tipc_link_bc_nack_rcv(काष्ठा tipc_link *l, काष्ठा sk_buff *skb,
			  काष्ठा sk_buff_head *xmitq);
bool tipc_link_too_silent(काष्ठा tipc_link *l);
काष्ठा net *tipc_link_net(काष्ठा tipc_link *l);
#पूर्ण_अगर
