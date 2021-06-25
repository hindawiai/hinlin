<शैली गुरु>
/*
 * net/tipc/core.h: Include file क्रम TIPC global declarations
 *
 * Copyright (c) 2005-2006, 2013-2018 Ericsson AB
 * Copyright (c) 2005-2007, 2010-2013, Wind River Systems
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

#अगर_अघोषित _TIPC_CORE_H
#घोषणा _TIPC_CORE_H

#समावेश <linux/tipc.h>
#समावेश <linux/tipc_config.h>
#समावेश <linux/tipc_netlink.h>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/mm.h>
#समावेश <linux/समयr.h>
#समावेश <linux/माला.स>
#समावेश <linux/uaccess.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/atomic.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/in.h>
#समावेश <linux/list.h>
#समावेश <linux/slab.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/etherdevice.h>
#समावेश <net/netns/generic.h>
#समावेश <linux/rhashtable.h>
#समावेश <net/genetlink.h>
#समावेश <net/netns/hash.h>

#अगर_घोषित pr_fmt
#अघोषित pr_fmt
#पूर्ण_अगर

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

काष्ठा tipc_node;
काष्ठा tipc_bearer;
काष्ठा tipc_bc_base;
काष्ठा tipc_link;
काष्ठा tipc_name_table;
काष्ठा tipc_topsrv;
काष्ठा tipc_monitor;
#अगर_घोषित CONFIG_TIPC_CRYPTO
काष्ठा tipc_crypto;
#पूर्ण_अगर

#घोषणा TIPC_MOD_VER "2.0.0"

#घोषणा NODE_HTABLE_SIZE       512
#घोषणा MAX_BEARERS	         3
#घोषणा TIPC_DEF_MON_THRESHOLD  32
#घोषणा NODE_ID_LEN             16
#घोषणा NODE_ID_STR_LEN        (NODE_ID_LEN * 2 + 1)

बाह्य अचिन्हित पूर्णांक tipc_net_id __पढ़ो_mostly;
बाह्य पूर्णांक sysctl_tipc_rmem[3] __पढ़ो_mostly;
बाह्य पूर्णांक sysctl_tipc_named_समयout __पढ़ो_mostly;

काष्ठा tipc_net अणु
	u8  node_id[NODE_ID_LEN];
	u32 node_addr;
	u32 trial_addr;
	अचिन्हित दीर्घ addr_trial_end;
	अक्षर node_id_string[NODE_ID_STR_LEN];
	पूर्णांक net_id;
	पूर्णांक अक्रमom;
	bool legacy_addr_क्रमmat;

	/* Node table and node list */
	spinlock_t node_list_lock;
	काष्ठा hlist_head node_htable[NODE_HTABLE_SIZE];
	काष्ठा list_head node_list;
	u32 num_nodes;
	u32 num_links;

	/* Neighbor monitoring list */
	काष्ठा tipc_monitor *monitors[MAX_BEARERS];
	पूर्णांक mon_threshold;

	/* Bearer list */
	काष्ठा tipc_bearer __rcu *bearer_list[MAX_BEARERS + 1];

	/* Broadcast link */
	spinlock_t bघड़ी;
	काष्ठा tipc_bc_base *bcbase;
	काष्ठा tipc_link *bcl;

	/* Socket hash table */
	काष्ठा rhashtable sk_rht;

	/* Name table */
	spinlock_t nametbl_lock;
	काष्ठा name_table *nametbl;

	/* Topology subscription server */
	काष्ठा tipc_topsrv *topsrv;
	atomic_t subscription_count;

	/* Cluster capabilities */
	u16 capabilities;

	/* Tracing of node पूर्णांकernal messages */
	काष्ठा packet_type loopback_pt;

#अगर_घोषित CONFIG_TIPC_CRYPTO
	/* TX crypto handler */
	काष्ठा tipc_crypto *crypto_tx;
#पूर्ण_अगर
	/* Work item क्रम net finalize */
	काष्ठा work_काष्ठा work;
	/* The numbers of work queues in schedule */
	atomic_t wq_count;
पूर्ण;

अटल अंतरभूत काष्ठा tipc_net *tipc_net(काष्ठा net *net)
अणु
	वापस net_generic(net, tipc_net_id);
पूर्ण

अटल अंतरभूत पूर्णांक tipc_netid(काष्ठा net *net)
अणु
	वापस tipc_net(net)->net_id;
पूर्ण

अटल अंतरभूत काष्ठा list_head *tipc_nodes(काष्ठा net *net)
अणु
	वापस &tipc_net(net)->node_list;
पूर्ण

अटल अंतरभूत काष्ठा name_table *tipc_name_table(काष्ठा net *net)
अणु
	वापस tipc_net(net)->nametbl;
पूर्ण

अटल अंतरभूत काष्ठा tipc_topsrv *tipc_topsrv(काष्ठा net *net)
अणु
	वापस tipc_net(net)->topsrv;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक tipc_hashfn(u32 addr)
अणु
	वापस addr & (NODE_HTABLE_SIZE - 1);
पूर्ण

अटल अंतरभूत u16 mod(u16 x)
अणु
	वापस x & 0xffffu;
पूर्ण

अटल अंतरभूत पूर्णांक less_eq(u16 left, u16 right)
अणु
	वापस mod(right - left) < 32768u;
पूर्ण

अटल अंतरभूत पूर्णांक more(u16 left, u16 right)
अणु
	वापस !less_eq(left, right);
पूर्ण

अटल अंतरभूत पूर्णांक less(u16 left, u16 right)
अणु
	वापस less_eq(left, right) && (mod(right) != mod(left));
पूर्ण

अटल अंतरभूत पूर्णांक in_range(u16 val, u16 min, u16 max)
अणु
	वापस !less(val, min) && !more(val, max);
पूर्ण

अटल अंतरभूत u32 tipc_net_hash_mixes(काष्ठा net *net, पूर्णांक tn_अक्रम)
अणु
	वापस net_hash_mix(&init_net) ^ net_hash_mix(net) ^ tn_अक्रम;
पूर्ण

अटल अंतरभूत u32 hash128to32(अक्षर *bytes)
अणु
	__be32 *पंचांगp = (__be32 *)bytes;
	u32 res;

	res = ntohl(पंचांगp[0] ^ पंचांगp[1] ^ पंचांगp[2] ^ पंचांगp[3]);
	अगर (likely(res))
		वापस res;
	वापस  ntohl(पंचांगp[0] | पंचांगp[1] | पंचांगp[2] | पंचांगp[3]);
पूर्ण

#अगर_घोषित CONFIG_SYSCTL
पूर्णांक tipc_रेजिस्टर_sysctl(व्योम);
व्योम tipc_unरेजिस्टर_sysctl(व्योम);
#अन्यथा
#घोषणा tipc_रेजिस्टर_sysctl() 0
#घोषणा tipc_unरेजिस्टर_sysctl()
#पूर्ण_अगर
#पूर्ण_अगर
