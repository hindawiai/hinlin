<शैली गुरु>
/*
 * net/tipc/net.h: Include file क्रम TIPC network routing code
 *
 * Copyright (c) 1995-2006, 2014, Ericsson AB
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

#अगर_अघोषित _TIPC_NET_H
#घोषणा _TIPC_NET_H

#समावेश <net/genetlink.h>

बाह्य स्थिर काष्ठा nla_policy tipc_nl_net_policy[];

पूर्णांक tipc_net_init(काष्ठा net *net, u8 *node_id, u32 addr);
व्योम tipc_net_finalize_work(काष्ठा work_काष्ठा *work);
व्योम tipc_sched_net_finalize(काष्ठा net *net, u32 addr);
व्योम tipc_net_stop(काष्ठा net *net);
पूर्णांक tipc_nl_net_dump(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb);
पूर्णांक tipc_nl_net_set(काष्ठा sk_buff *skb, काष्ठा genl_info *info);
पूर्णांक __tipc_nl_net_set(काष्ठा sk_buff *skb, काष्ठा genl_info *info);
पूर्णांक tipc_nl_net_addr_legacy_get(काष्ठा sk_buff *skb, काष्ठा genl_info *info);

#पूर्ण_अगर
