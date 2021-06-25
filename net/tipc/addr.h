<शैली गुरु>
/*
 * net/tipc/addr.h: Include file क्रम TIPC address utility routines
 *
 * Copyright (c) 2000-2006, 2018, Ericsson AB
 * Copyright (c) 2004-2005, Wind River Systems
 * Copyright (c) 2020-2021, Red Hat Inc
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

#अगर_अघोषित _TIPC_ADDR_H
#घोषणा _TIPC_ADDR_H

#समावेश <linux/types.h>
#समावेश <linux/tipc.h>
#समावेश <net/net_namespace.h>
#समावेश <net/netns/generic.h>
#समावेश "core.h"

/* Struct tipc_uaddr: पूर्णांकernal version of काष्ठा sockaddr_tipc.
 * Must be kept aligned both regarding field positions and size.
 */
काष्ठा tipc_uaddr अणु
	अचिन्हित लघु family;
	अचिन्हित अक्षर addrtype;
	चिन्हित अक्षर scope;
	जोड़ अणु
		काष्ठा अणु
			काष्ठा tipc_service_addr sa;
			u32 lookup_node;
		पूर्ण;
		काष्ठा tipc_service_range sr;
		काष्ठा tipc_socket_addr sk;
	पूर्ण;
पूर्ण;

अटल अंतरभूत व्योम tipc_uaddr(काष्ठा tipc_uaddr *ua, u32 atype, u32 scope,
			      u32 type, u32 lower, u32 upper)
अणु
	ua->family = AF_TIPC;
	ua->addrtype = atype;
	ua->scope = scope;
	ua->sr.type = type;
	ua->sr.lower = lower;
	ua->sr.upper = upper;
पूर्ण

अटल अंतरभूत bool tipc_uaddr_valid(काष्ठा tipc_uaddr *ua, पूर्णांक len)
अणु
	u32 atype;

	अगर (len < माप(काष्ठा sockaddr_tipc))
		वापस false;
	atype = ua->addrtype;
	अगर (ua->family != AF_TIPC)
		वापस false;
	अगर (atype == TIPC_SERVICE_ADDR || atype == TIPC_SOCKET_ADDR)
		वापस true;
	अगर (atype == TIPC_SERVICE_RANGE)
		वापस ua->sr.upper >= ua->sr.lower;
	वापस false;
पूर्ण

अटल अंतरभूत u32 tipc_own_addr(काष्ठा net *net)
अणु
	वापस tipc_net(net)->node_addr;
पूर्ण

अटल अंतरभूत u8 *tipc_own_id(काष्ठा net *net)
अणु
	काष्ठा tipc_net *tn = tipc_net(net);

	अगर (!म_माप(tn->node_id_string))
		वापस शून्य;
	वापस tn->node_id;
पूर्ण

अटल अंतरभूत अक्षर *tipc_own_id_string(काष्ठा net *net)
अणु
	वापस tipc_net(net)->node_id_string;
पूर्ण

अटल अंतरभूत u32 tipc_cluster_mask(u32 addr)
अणु
	वापस addr & TIPC_ZONE_CLUSTER_MASK;
पूर्ण

अटल अंतरभूत पूर्णांक tipc_node2scope(u32 node)
अणु
	वापस node ? TIPC_NODE_SCOPE : TIPC_CLUSTER_SCOPE;
पूर्ण

अटल अंतरभूत पूर्णांक tipc_scope2node(काष्ठा net *net, पूर्णांक sc)
अणु
	वापस sc != TIPC_NODE_SCOPE ? 0 : tipc_own_addr(net);
पूर्ण

अटल अंतरभूत पूर्णांक in_own_node(काष्ठा net *net, u32 addr)
अणु
	वापस addr == tipc_own_addr(net) || !addr;
पूर्ण

bool tipc_in_scope(bool legacy_क्रमmat, u32 करोमुख्य, u32 addr);
व्योम tipc_set_node_id(काष्ठा net *net, u8 *id);
व्योम tipc_set_node_addr(काष्ठा net *net, u32 addr);
अक्षर *tipc_nodeid2string(अक्षर *str, u8 *id);
u32 tipc_node_id2hash(u8 *id128);

#पूर्ण_अगर
