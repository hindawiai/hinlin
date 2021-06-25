<शैली गुरु>
/* SPDX-License-Identअगरier: ((GPL-2.0 WITH Linux-syscall-note) OR BSD-3-Clause) */
/*
 * include/uapi/linux/tipc.h: Header क्रम TIPC socket पूर्णांकerface
 *
 * Copyright (c) 2003-2006, 2015-2016 Ericsson AB
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

#अगर_अघोषित _LINUX_TIPC_H_
#घोषणा _LINUX_TIPC_H_

#समावेश <linux/types.h>
#समावेश <linux/sockios.h>

/*
 * TIPC addressing primitives
 */

काष्ठा tipc_socket_addr अणु
	__u32 ref;
	__u32 node;
पूर्ण;

काष्ठा tipc_service_addr अणु
	__u32 type;
	__u32 instance;
पूर्ण;

काष्ठा tipc_service_range अणु
	__u32 type;
	__u32 lower;
	__u32 upper;
पूर्ण;

/*
 * Application-accessible service types
 */

#घोषणा TIPC_NODE_STATE		0	/* node state service type */
#घोषणा TIPC_TOP_SRV		1	/* topology server service type */
#घोषणा TIPC_LINK_STATE		2	/* link state service type */
#घोषणा TIPC_RESERVED_TYPES	64	/* lowest user-allowed service type */

/*
 * Publication scopes when binding service / service range
 */
क्रमागत tipc_scope अणु
	TIPC_CLUSTER_SCOPE = 2, /* 0 can also be used */
	TIPC_NODE_SCOPE    = 3
पूर्ण;

/*
 * Limiting values क्रम messages
 */

#घोषणा TIPC_MAX_USER_MSG_SIZE	66000U

/*
 * Message importance levels
 */

#घोषणा TIPC_LOW_IMPORTANCE		0
#घोषणा TIPC_MEDIUM_IMPORTANCE		1
#घोषणा TIPC_HIGH_IMPORTANCE		2
#घोषणा TIPC_CRITICAL_IMPORTANCE	3

/*
 * Msg rejection/connection shutकरोwn reasons
 */

#घोषणा TIPC_OK			0
#घोषणा TIPC_ERR_NO_NAME	1
#घोषणा TIPC_ERR_NO_PORT	2
#घोषणा TIPC_ERR_NO_NODE	3
#घोषणा TIPC_ERR_OVERLOAD	4
#घोषणा TIPC_CONN_SHUTDOWN	5

/*
 * TIPC topology subscription service definitions
 */

#घोषणा TIPC_SUB_PORTS          0x01    /* filter: evt at each match */
#घोषणा TIPC_SUB_SERVICE        0x02    /* filter: evt at first up/last करोwn */
#घोषणा TIPC_SUB_CANCEL         0x04    /* filter: cancel a subscription */

#घोषणा TIPC_WAIT_FOREVER	(~0)	/* समयout क्रम permanent subscription */

काष्ठा tipc_subscr अणु
	काष्ठा tipc_service_range seq;	/* range of पूर्णांकerest */
	__u32 समयout;			/* subscription duration (in ms) */
	__u32 filter;			/* biपंचांगask of filter options */
	अक्षर usr_handle[8];		/* available क्रम subscriber use */
पूर्ण;

#घोषणा TIPC_PUBLISHED		1	/* खुलाation event */
#घोषणा TIPC_WITHDRAWN		2	/* withdrawal event */
#घोषणा TIPC_SUBSCR_TIMEOUT	3	/* subscription समयout event */

काष्ठा tipc_event अणु
	__u32 event;			/* event type */
	__u32 found_lower;		/* matching range */
	__u32 found_upper;		/*    "      "    */
	काष्ठा tipc_socket_addr port;	/* associated socket */
	काष्ठा tipc_subscr s;		/* associated subscription */
पूर्ण;

/*
 * Socket API
 */

#अगर_अघोषित AF_TIPC
#घोषणा AF_TIPC		30
#पूर्ण_अगर

#अगर_अघोषित PF_TIPC
#घोषणा PF_TIPC		AF_TIPC
#पूर्ण_अगर

#अगर_अघोषित SOL_TIPC
#घोषणा SOL_TIPC	271
#पूर्ण_अगर

#घोषणा TIPC_ADDR_MCAST         1
#घोषणा TIPC_SERVICE_RANGE      1
#घोषणा TIPC_SERVICE_ADDR       2
#घोषणा TIPC_SOCKET_ADDR        3

काष्ठा sockaddr_tipc अणु
	अचिन्हित लघु family;
	अचिन्हित अक्षर  addrtype;
	चिन्हित   अक्षर  scope;
	जोड़ अणु
		काष्ठा tipc_socket_addr id;
		काष्ठा tipc_service_range nameseq;
		काष्ठा अणु
			काष्ठा tipc_service_addr name;
			__u32 करोमुख्य;
		पूर्ण name;
	पूर्ण addr;
पूर्ण;

/*
 * Ancillary data objects supported by recvmsg()
 */

#घोषणा TIPC_ERRINFO	1	/* error info */
#घोषणा TIPC_RETDATA	2	/* वापसed data */
#घोषणा TIPC_DESTNAME	3	/* destination name */

/*
 * TIPC-specअगरic socket option names
 */

#घोषणा TIPC_IMPORTANCE		127	/* Default: TIPC_LOW_IMPORTANCE */
#घोषणा TIPC_SRC_DROPPABLE	128	/* Default: based on socket type */
#घोषणा TIPC_DEST_DROPPABLE	129	/* Default: based on socket type */
#घोषणा TIPC_CONN_TIMEOUT	130	/* Default: 8000 (ms)  */
#घोषणा TIPC_NODE_RECVQ_DEPTH	131	/* Default: none (पढ़ो only) */
#घोषणा TIPC_SOCK_RECVQ_DEPTH	132	/* Default: none (पढ़ो only) */
#घोषणा TIPC_MCAST_BROADCAST    133     /* Default: TIPC selects. No arg */
#घोषणा TIPC_MCAST_REPLICAST    134     /* Default: TIPC selects. No arg */
#घोषणा TIPC_GROUP_JOIN         135     /* Takes काष्ठा tipc_group_req* */
#घोषणा TIPC_GROUP_LEAVE        136     /* No argument */
#घोषणा TIPC_SOCK_RECVQ_USED    137     /* Default: none (पढ़ो only) */
#घोषणा TIPC_NODELAY            138     /* Default: false */

/*
 * Flag values
 */
#घोषणा TIPC_GROUP_LOOPBACK     0x1  /* Receive copy of sent msg when match */
#घोषणा TIPC_GROUP_MEMBER_EVTS  0x2  /* Receive membership events in socket */

काष्ठा tipc_group_req अणु
	__u32 type;      /* group id */
	__u32 instance;  /* member id */
	__u32 scope;     /* cluster/node */
	__u32 flags;
पूर्ण;

/*
 * Maximum sizes of TIPC bearer-related names (including terminating शून्य)
 * The string क्रमmatting क्रम each name element is:
 * media: media
 * पूर्णांकerface: media:पूर्णांकerface name
 * link: node:पूर्णांकerface-node:पूर्णांकerface
 */
#घोषणा TIPC_NODEID_LEN         16
#घोषणा TIPC_MAX_MEDIA_NAME	16
#घोषणा TIPC_MAX_IF_NAME	16
#घोषणा TIPC_MAX_BEARER_NAME	32
#घोषणा TIPC_MAX_LINK_NAME	68

#घोषणा SIOCGETLINKNAME        SIOCPROTOPRIVATE
#घोषणा SIOCGETNODEID          (SIOCPROTOPRIVATE + 1)

काष्ठा tipc_sioc_ln_req अणु
	__u32 peer;
	__u32 bearer_id;
	अक्षर linkname[TIPC_MAX_LINK_NAME];
पूर्ण;

काष्ठा tipc_sioc_nodeid_req अणु
	__u32 peer;
	अक्षर node_id[TIPC_NODEID_LEN];
पूर्ण;

/*
 * TIPC Crypto, AEAD
 */
#घोषणा TIPC_AEAD_ALG_NAME		(32)

काष्ठा tipc_aead_key अणु
	अक्षर alg_name[TIPC_AEAD_ALG_NAME];
	अचिन्हित पूर्णांक keylen;	/* in bytes */
	अक्षर key[];
पूर्ण;

#घोषणा TIPC_AEAD_KEYLEN_MIN		(16 + 4)
#घोषणा TIPC_AEAD_KEYLEN_MAX		(32 + 4)
#घोषणा TIPC_AEAD_KEY_SIZE_MAX		(माप(काष्ठा tipc_aead_key) + \
							TIPC_AEAD_KEYLEN_MAX)

अटल अंतरभूत पूर्णांक tipc_aead_key_size(काष्ठा tipc_aead_key *key)
अणु
	वापस माप(*key) + key->keylen;
पूर्ण

#घोषणा TIPC_REKEYING_NOW		(~0U)

/* The macros and functions below are deprecated:
 */

#घोषणा TIPC_CFG_SRV		0
#घोषणा TIPC_ZONE_SCOPE         1

#घोषणा TIPC_ADDR_NAMESEQ	1
#घोषणा TIPC_ADDR_NAME		2
#घोषणा TIPC_ADDR_ID		3

#घोषणा TIPC_NODE_BITS          12
#घोषणा TIPC_CLUSTER_BITS       12
#घोषणा TIPC_ZONE_BITS          8

#घोषणा TIPC_NODE_OFFSET        0
#घोषणा TIPC_CLUSTER_OFFSET     TIPC_NODE_BITS
#घोषणा TIPC_ZONE_OFFSET        (TIPC_CLUSTER_OFFSET + TIPC_CLUSTER_BITS)

#घोषणा TIPC_NODE_SIZE          ((1UL << TIPC_NODE_BITS) - 1)
#घोषणा TIPC_CLUSTER_SIZE       ((1UL << TIPC_CLUSTER_BITS) - 1)
#घोषणा TIPC_ZONE_SIZE          ((1UL << TIPC_ZONE_BITS) - 1)

#घोषणा TIPC_NODE_MASK		(TIPC_NODE_SIZE << TIPC_NODE_OFFSET)
#घोषणा TIPC_CLUSTER_MASK	(TIPC_CLUSTER_SIZE << TIPC_CLUSTER_OFFSET)
#घोषणा TIPC_ZONE_MASK		(TIPC_ZONE_SIZE << TIPC_ZONE_OFFSET)

#घोषणा TIPC_ZONE_CLUSTER_MASK (TIPC_ZONE_MASK | TIPC_CLUSTER_MASK)

#घोषणा tipc_portid tipc_socket_addr
#घोषणा tipc_name tipc_service_addr
#घोषणा tipc_name_seq tipc_service_range

अटल अंतरभूत __u32 tipc_addr(अचिन्हित पूर्णांक zone,
			      अचिन्हित पूर्णांक cluster,
			      अचिन्हित पूर्णांक node)
अणु
	वापस (zone << TIPC_ZONE_OFFSET) |
		(cluster << TIPC_CLUSTER_OFFSET) |
		node;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक tipc_zone(__u32 addr)
अणु
	वापस addr >> TIPC_ZONE_OFFSET;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक tipc_cluster(__u32 addr)
अणु
	वापस (addr & TIPC_CLUSTER_MASK) >> TIPC_CLUSTER_OFFSET;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक tipc_node(__u32 addr)
अणु
	वापस addr & TIPC_NODE_MASK;
पूर्ण

#पूर्ण_अगर
