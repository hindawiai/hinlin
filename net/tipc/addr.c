<शैली गुरु>
/*
 * net/tipc/addr.c: TIPC address utility routines
 *
 * Copyright (c) 2000-2006, 2018, Ericsson AB
 * Copyright (c) 2004-2005, 2010-2011, Wind River Systems
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

#समावेश "addr.h"
#समावेश "core.h"

bool tipc_in_scope(bool legacy_क्रमmat, u32 करोमुख्य, u32 addr)
अणु
	अगर (!करोमुख्य || (करोमुख्य == addr))
		वापस true;
	अगर (!legacy_क्रमmat)
		वापस false;
	अगर (करोमुख्य == tipc_cluster_mask(addr)) /* करोमुख्य <Z.C.0> */
		वापस true;
	अगर (करोमुख्य == (addr & TIPC_ZONE_CLUSTER_MASK)) /* करोमुख्य <Z.C.0> */
		वापस true;
	अगर (करोमुख्य == (addr & TIPC_ZONE_MASK)) /* करोमुख्य <Z.0.0> */
		वापस true;
	वापस false;
पूर्ण

व्योम tipc_set_node_id(काष्ठा net *net, u8 *id)
अणु
	काष्ठा tipc_net *tn = tipc_net(net);

	स_नकल(tn->node_id, id, NODE_ID_LEN);
	tipc_nodeid2string(tn->node_id_string, id);
	tn->trial_addr = hash128to32(id);
	pr_info("Node identity %s, cluster identity %u\n",
		tipc_own_id_string(net), tn->net_id);
पूर्ण

व्योम tipc_set_node_addr(काष्ठा net *net, u32 addr)
अणु
	काष्ठा tipc_net *tn = tipc_net(net);
	u8 node_id[NODE_ID_LEN] = अणु0,पूर्ण;

	tn->node_addr = addr;
	अगर (!tipc_own_id(net)) अणु
		प्र_लिखो(node_id, "%x", addr);
		tipc_set_node_id(net, node_id);
	पूर्ण
	tn->trial_addr = addr;
	tn->addr_trial_end = jअगरfies;
	pr_info("Node number set to %u\n", addr);
पूर्ण

अक्षर *tipc_nodeid2string(अक्षर *str, u8 *id)
अणु
	पूर्णांक i;
	u8 c;

	/* Alपढ़ोy a string ? */
	क्रम (i = 0; i < NODE_ID_LEN; i++) अणु
		c = id[i];
		अगर (c >= '0' && c <= '9')
			जारी;
		अगर (c >= 'A' && c <= 'Z')
			जारी;
		अगर (c >= 'a' && c <= 'z')
			जारी;
		अगर (c == '.')
			जारी;
		अगर (c == ':')
			जारी;
		अगर (c == '_')
			जारी;
		अगर (c == '-')
			जारी;
		अगर (c == '@')
			जारी;
		अगर (c != 0)
			अवरोध;
	पूर्ण
	अगर (i == NODE_ID_LEN) अणु
		स_नकल(str, id, NODE_ID_LEN);
		str[NODE_ID_LEN] = 0;
		वापस str;
	पूर्ण

	/* Translate to hex string */
	क्रम (i = 0; i < NODE_ID_LEN; i++)
		प्र_लिखो(&str[2 * i], "%02x", id[i]);

	/* Strip off trailing zeroes */
	क्रम (i = NODE_ID_STR_LEN - 2; str[i] == '0'; i--)
		str[i] = 0;

	वापस str;
पूर्ण
