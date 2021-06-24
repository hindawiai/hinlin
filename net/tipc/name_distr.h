<शैली गुरु>
/*
 * net/tipc/name_distr.h: Include file क्रम TIPC name distribution code
 *
 * Copyright (c) 2000-2006, Ericsson AB
 * Copyright (c) 2005, Wind River Systems
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

#अगर_अघोषित _TIPC_NAME_DISTR_H
#घोषणा _TIPC_NAME_DISTR_H

#समावेश "name_table.h"

#घोषणा ITEM_SIZE माप(काष्ठा distr_item)

/**
 * काष्ठा distr_item - खुलाation info distributed to other nodes
 * @type: name sequence type
 * @lower: name sequence lower bound
 * @upper: name sequence upper bound
 * @port: publishing port reference
 * @key: खुलाation key
 *
 * ===> All fields are stored in network byte order. <===
 *
 * First 3 fields identअगरy (name or) name sequence being published.
 * Reference field uniquely identअगरies port that published name sequence.
 * Key field uniquely identअगरies खुलाation, in the event a port has
 * multiple खुलाations of the same name sequence.
 *
 * Note: There is no field that identअगरies the publishing node because it is
 * the same क्रम all items contained within a खुलाation message.
 */
काष्ठा distr_item अणु
	__be32 type;
	__be32 lower;
	__be32 upper;
	__be32 port;
	__be32 key;
पूर्ण;

व्योम tipc_named_bcast(काष्ठा net *net, काष्ठा sk_buff *skb);
काष्ठा sk_buff *tipc_named_publish(काष्ठा net *net, काष्ठा खुलाation *publ);
काष्ठा sk_buff *tipc_named_withdraw(काष्ठा net *net, काष्ठा खुलाation *publ);
व्योम tipc_named_node_up(काष्ठा net *net, u32 dnode, u16 capabilities);
व्योम tipc_named_rcv(काष्ठा net *net, काष्ठा sk_buff_head *namedq,
		    u16 *rcv_nxt, bool *खोलो);
व्योम tipc_named_reinit(काष्ठा net *net);
व्योम tipc_publ_notअगरy(काष्ठा net *net, काष्ठा list_head *nsub_list,
		      u32 addr, u16 capabilities);

#पूर्ण_अगर
