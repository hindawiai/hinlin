<शैली गुरु>
/*
 * net/tipc/netlink.h: Include file क्रम TIPC netlink code
 *
 * Copyright (c) 2014, Ericsson AB
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

#अगर_अघोषित _TIPC_NETLINK_H
#घोषणा _TIPC_NETLINK_H
#समावेश <net/netlink.h>

बाह्य काष्ठा genl_family tipc_genl_family;

काष्ठा tipc_nl_msg अणु
	काष्ठा sk_buff *skb;
	u32 portid;
	u32 seq;
पूर्ण;

बाह्य स्थिर काष्ठा nla_policy tipc_nl_name_table_policy[];
बाह्य स्थिर काष्ठा nla_policy tipc_nl_sock_policy[];
बाह्य स्थिर काष्ठा nla_policy tipc_nl_net_policy[];
बाह्य स्थिर काष्ठा nla_policy tipc_nl_link_policy[];
बाह्य स्थिर काष्ठा nla_policy tipc_nl_node_policy[];
बाह्य स्थिर काष्ठा nla_policy tipc_nl_prop_policy[];
बाह्य स्थिर काष्ठा nla_policy tipc_nl_bearer_policy[];
बाह्य स्थिर काष्ठा nla_policy tipc_nl_media_policy[];
बाह्य स्थिर काष्ठा nla_policy tipc_nl_udp_policy[];
बाह्य स्थिर काष्ठा nla_policy tipc_nl_monitor_policy[];

पूर्णांक tipc_netlink_start(व्योम);
पूर्णांक tipc_netlink_compat_start(व्योम);
व्योम tipc_netlink_stop(व्योम);
व्योम tipc_netlink_compat_stop(व्योम);

#पूर्ण_अगर
