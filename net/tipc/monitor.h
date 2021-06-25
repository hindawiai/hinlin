<शैली गुरु>
/*
 * net/tipc/monitor.h
 *
 * Copyright (c) 2015, Ericsson AB
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

#अगर_अघोषित _TIPC_MONITOR_H
#घोषणा _TIPC_MONITOR_H

#समावेश "netlink.h"

/* काष्ठा tipc_mon_state: link instance's cache of monitor list and करोमुख्य state
 * @list_gen: current generation of this node's monitor list
 * @gen: current generation of this node's local करोमुख्य
 * @peer_gen: most recent करोमुख्य generation received from peer
 * @acked_gen: most recent generation of self's करोमुख्य acked by peer
 * @monitoring: this peer endpoपूर्णांक should continuously monitored
 * @probing: peer endpoपूर्णांक should be temporarily probed क्रम potential loss
 * @synched: करोमुख्य record's generation has been synched with peer after reset
 */
काष्ठा tipc_mon_state अणु
	u16 list_gen;
	u16 peer_gen;
	u16 acked_gen;
	bool monitoring :1;
	bool probing    :1;
	bool reset      :1;
	bool synched    :1;
पूर्ण;

पूर्णांक tipc_mon_create(काष्ठा net *net, पूर्णांक bearer_id);
व्योम tipc_mon_delete(काष्ठा net *net, पूर्णांक bearer_id);

व्योम tipc_mon_peer_up(काष्ठा net *net, u32 addr, पूर्णांक bearer_id);
व्योम tipc_mon_peer_करोwn(काष्ठा net *net, u32 addr, पूर्णांक bearer_id);
व्योम tipc_mon_prep(काष्ठा net *net, व्योम *data, पूर्णांक *dlen,
		   काष्ठा tipc_mon_state *state, पूर्णांक bearer_id);
व्योम tipc_mon_rcv(काष्ठा net *net, व्योम *data, u16 dlen, u32 addr,
		  काष्ठा tipc_mon_state *state, पूर्णांक bearer_id);
व्योम tipc_mon_get_state(काष्ठा net *net, u32 addr,
			काष्ठा tipc_mon_state *state,
			पूर्णांक bearer_id);
व्योम tipc_mon_हटाओ_peer(काष्ठा net *net, u32 addr, पूर्णांक bearer_id);

पूर्णांक tipc_nl_monitor_set_threshold(काष्ठा net *net, u32 cluster_size);
पूर्णांक tipc_nl_monitor_get_threshold(काष्ठा net *net);
पूर्णांक __tipc_nl_add_monitor(काष्ठा net *net, काष्ठा tipc_nl_msg *msg,
			  u32 bearer_id);
पूर्णांक tipc_nl_add_monitor_peer(काष्ठा net *net, काष्ठा tipc_nl_msg *msg,
			     u32 bearer_id, u32 *prev_node);
व्योम tipc_mon_reinit_self(काष्ठा net *net);

बाह्य स्थिर पूर्णांक tipc_max_करोमुख्य_size;
#पूर्ण_अगर
