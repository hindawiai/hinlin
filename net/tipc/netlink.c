<शैली गुरु>
/*
 * net/tipc/netlink.c: TIPC configuration handling
 *
 * Copyright (c) 2005-2006, 2014, Ericsson AB
 * Copyright (c) 2005-2007, Wind River Systems
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

#समावेश "core.h"
#समावेश "socket.h"
#समावेश "name_table.h"
#समावेश "bearer.h"
#समावेश "link.h"
#समावेश "node.h"
#समावेश "net.h"
#समावेश "udp_media.h"
#समावेश <net/genetlink.h>

अटल स्थिर काष्ठा nla_policy tipc_nl_policy[TIPC_NLA_MAX + 1] = अणु
	[TIPC_NLA_UNSPEC]	= अणु .type = NLA_UNSPEC, पूर्ण,
	[TIPC_NLA_BEARER]	= अणु .type = NLA_NESTED, पूर्ण,
	[TIPC_NLA_SOCK]		= अणु .type = NLA_NESTED, पूर्ण,
	[TIPC_NLA_PUBL]		= अणु .type = NLA_NESTED, पूर्ण,
	[TIPC_NLA_LINK]		= अणु .type = NLA_NESTED, पूर्ण,
	[TIPC_NLA_MEDIA]	= अणु .type = NLA_NESTED, पूर्ण,
	[TIPC_NLA_NODE]		= अणु .type = NLA_NESTED, पूर्ण,
	[TIPC_NLA_NET]		= अणु .type = NLA_NESTED, पूर्ण,
	[TIPC_NLA_NAME_TABLE]	= अणु .type = NLA_NESTED, पूर्ण,
	[TIPC_NLA_MON]		= अणु .type = NLA_NESTED, पूर्ण,
पूर्ण;

स्थिर काष्ठा nla_policy
tipc_nl_name_table_policy[TIPC_NLA_NAME_TABLE_MAX + 1] = अणु
	[TIPC_NLA_NAME_TABLE_UNSPEC]	= अणु .type = NLA_UNSPEC पूर्ण,
	[TIPC_NLA_NAME_TABLE_PUBL]	= अणु .type = NLA_NESTED पूर्ण
पूर्ण;

स्थिर काष्ठा nla_policy tipc_nl_monitor_policy[TIPC_NLA_MON_MAX + 1] = अणु
	[TIPC_NLA_MON_UNSPEC]			= अणु .type = NLA_UNSPEC पूर्ण,
	[TIPC_NLA_MON_REF]			= अणु .type = NLA_U32 पूर्ण,
	[TIPC_NLA_MON_ACTIVATION_THRESHOLD]	= अणु .type = NLA_U32 पूर्ण,
पूर्ण;

स्थिर काष्ठा nla_policy tipc_nl_sock_policy[TIPC_NLA_SOCK_MAX + 1] = अणु
	[TIPC_NLA_SOCK_UNSPEC]		= अणु .type = NLA_UNSPEC पूर्ण,
	[TIPC_NLA_SOCK_ADDR]		= अणु .type = NLA_U32 पूर्ण,
	[TIPC_NLA_SOCK_REF]		= अणु .type = NLA_U32 पूर्ण,
	[TIPC_NLA_SOCK_CON]		= अणु .type = NLA_NESTED पूर्ण,
	[TIPC_NLA_SOCK_HAS_PUBL]	= अणु .type = NLA_FLAG पूर्ण
पूर्ण;

स्थिर काष्ठा nla_policy tipc_nl_net_policy[TIPC_NLA_NET_MAX + 1] = अणु
	[TIPC_NLA_NET_UNSPEC]		= अणु .type = NLA_UNSPEC पूर्ण,
	[TIPC_NLA_NET_ID]		= अणु .type = NLA_U32 पूर्ण,
	[TIPC_NLA_NET_ADDR]		= अणु .type = NLA_U32 पूर्ण,
	[TIPC_NLA_NET_NODEID]		= अणु .type = NLA_U64 पूर्ण,
	[TIPC_NLA_NET_NODEID_W1]	= अणु .type = NLA_U64 पूर्ण,
	[TIPC_NLA_NET_ADDR_LEGACY]	= अणु .type = NLA_FLAG पूर्ण
पूर्ण;

स्थिर काष्ठा nla_policy tipc_nl_link_policy[TIPC_NLA_LINK_MAX + 1] = अणु
	[TIPC_NLA_LINK_UNSPEC]		= अणु .type = NLA_UNSPEC पूर्ण,
	[TIPC_NLA_LINK_NAME]		= अणु .type = NLA_STRING,
					    .len = TIPC_MAX_LINK_NAME पूर्ण,
	[TIPC_NLA_LINK_MTU]		= अणु .type = NLA_U32 पूर्ण,
	[TIPC_NLA_LINK_BROADCAST]	= अणु .type = NLA_FLAG पूर्ण,
	[TIPC_NLA_LINK_UP]		= अणु .type = NLA_FLAG पूर्ण,
	[TIPC_NLA_LINK_ACTIVE]		= अणु .type = NLA_FLAG पूर्ण,
	[TIPC_NLA_LINK_PROP]		= अणु .type = NLA_NESTED पूर्ण,
	[TIPC_NLA_LINK_STATS]		= अणु .type = NLA_NESTED पूर्ण,
	[TIPC_NLA_LINK_RX]		= अणु .type = NLA_U32 पूर्ण,
	[TIPC_NLA_LINK_TX]		= अणु .type = NLA_U32 पूर्ण
पूर्ण;

स्थिर काष्ठा nla_policy tipc_nl_node_policy[TIPC_NLA_NODE_MAX + 1] = अणु
	[TIPC_NLA_NODE_UNSPEC]		= अणु .type = NLA_UNSPEC पूर्ण,
	[TIPC_NLA_NODE_ADDR]		= अणु .type = NLA_U32 पूर्ण,
	[TIPC_NLA_NODE_UP]		= अणु .type = NLA_FLAG पूर्ण,
	[TIPC_NLA_NODE_ID]		= अणु .type = NLA_BINARY,
					    .len = TIPC_NODEID_LENपूर्ण,
	[TIPC_NLA_NODE_KEY]		= अणु .type = NLA_BINARY,
					    .len = TIPC_AEAD_KEY_SIZE_MAXपूर्ण,
	[TIPC_NLA_NODE_KEY_MASTER]	= अणु .type = NLA_FLAG पूर्ण,
	[TIPC_NLA_NODE_REKEYING]	= अणु .type = NLA_U32 पूर्ण,
पूर्ण;

/* Properties valid क्रम media, bearer and link */
स्थिर काष्ठा nla_policy tipc_nl_prop_policy[TIPC_NLA_PROP_MAX + 1] = अणु
	[TIPC_NLA_PROP_UNSPEC]		= अणु .type = NLA_UNSPEC पूर्ण,
	[TIPC_NLA_PROP_PRIO]		= अणु .type = NLA_U32 पूर्ण,
	[TIPC_NLA_PROP_TOL]		= अणु .type = NLA_U32 पूर्ण,
	[TIPC_NLA_PROP_WIN]		= अणु .type = NLA_U32 पूर्ण,
	[TIPC_NLA_PROP_MTU]		= अणु .type = NLA_U32 पूर्ण,
	[TIPC_NLA_PROP_BROADCAST]	= अणु .type = NLA_U32 पूर्ण,
	[TIPC_NLA_PROP_BROADCAST_RATIO]	= अणु .type = NLA_U32 पूर्ण
पूर्ण;

स्थिर काष्ठा nla_policy tipc_nl_bearer_policy[TIPC_NLA_BEARER_MAX + 1]	= अणु
	[TIPC_NLA_BEARER_UNSPEC]	= अणु .type = NLA_UNSPEC पूर्ण,
	[TIPC_NLA_BEARER_NAME]		= अणु .type = NLA_STRING,
					    .len = TIPC_MAX_BEARER_NAME पूर्ण,
	[TIPC_NLA_BEARER_PROP]		= अणु .type = NLA_NESTED पूर्ण,
	[TIPC_NLA_BEARER_DOMAIN]	= अणु .type = NLA_U32 पूर्ण
पूर्ण;

स्थिर काष्ठा nla_policy tipc_nl_media_policy[TIPC_NLA_MEDIA_MAX + 1] = अणु
	[TIPC_NLA_MEDIA_UNSPEC]		= अणु .type = NLA_UNSPEC पूर्ण,
	[TIPC_NLA_MEDIA_NAME]		= अणु .type = NLA_STRING पूर्ण,
	[TIPC_NLA_MEDIA_PROP]		= अणु .type = NLA_NESTED पूर्ण
पूर्ण;

स्थिर काष्ठा nla_policy tipc_nl_udp_policy[TIPC_NLA_UDP_MAX + 1] = अणु
	[TIPC_NLA_UDP_UNSPEC]	= अणु.type = NLA_UNSPECपूर्ण,
	[TIPC_NLA_UDP_LOCAL]	= अणु.type = NLA_BINARY,
				   .len = माप(काष्ठा sockaddr_storage)पूर्ण,
	[TIPC_NLA_UDP_REMOTE]	= अणु.type = NLA_BINARY,
				   .len = माप(काष्ठा sockaddr_storage)पूर्ण,
पूर्ण;

/* Users of the legacy API (tipc-config) can't handle that we add operations,
 * so we have a separate genl handling क्रम the new API.
 */
अटल स्थिर काष्ठा genl_ops tipc_genl_v2_ops[] = अणु
	अणु
		.cmd	= TIPC_NL_BEARER_DISABLE,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit	= tipc_nl_bearer_disable,
	पूर्ण,
	अणु
		.cmd	= TIPC_NL_BEARER_ENABLE,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit	= tipc_nl_bearer_enable,
	पूर्ण,
	अणु
		.cmd	= TIPC_NL_BEARER_GET,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit	= tipc_nl_bearer_get,
		.dumpit	= tipc_nl_bearer_dump,
	पूर्ण,
	अणु
		.cmd	= TIPC_NL_BEARER_ADD,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit	= tipc_nl_bearer_add,
	पूर्ण,
	अणु
		.cmd	= TIPC_NL_BEARER_SET,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit	= tipc_nl_bearer_set,
	पूर्ण,
	अणु
		.cmd	= TIPC_NL_SOCK_GET,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.start = tipc_dump_start,
		.dumpit	= tipc_nl_sk_dump,
		.करोne	= tipc_dump_करोne,
	पूर्ण,
	अणु
		.cmd	= TIPC_NL_PUBL_GET,
		.validate = GENL_DONT_VALIDATE_STRICT |
			    GENL_DONT_VALIDATE_DUMP_STRICT,
		.dumpit	= tipc_nl_publ_dump,
	पूर्ण,
	अणु
		.cmd	= TIPC_NL_LINK_GET,
		.validate = GENL_DONT_VALIDATE_STRICT,
		.करोit   = tipc_nl_node_get_link,
		.dumpit	= tipc_nl_node_dump_link,
	पूर्ण,
	अणु
		.cmd	= TIPC_NL_LINK_SET,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit	= tipc_nl_node_set_link,
	पूर्ण,
	अणु
		.cmd	= TIPC_NL_LINK_RESET_STATS,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit   = tipc_nl_node_reset_link_stats,
	पूर्ण,
	अणु
		.cmd	= TIPC_NL_MEDIA_GET,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit	= tipc_nl_media_get,
		.dumpit	= tipc_nl_media_dump,
	पूर्ण,
	अणु
		.cmd	= TIPC_NL_MEDIA_SET,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit	= tipc_nl_media_set,
	पूर्ण,
	अणु
		.cmd	= TIPC_NL_NODE_GET,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.dumpit	= tipc_nl_node_dump,
	पूर्ण,
	अणु
		.cmd	= TIPC_NL_NET_GET,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.dumpit	= tipc_nl_net_dump,
	पूर्ण,
	अणु
		.cmd	= TIPC_NL_NET_SET,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit	= tipc_nl_net_set,
	पूर्ण,
	अणु
		.cmd	= TIPC_NL_NAME_TABLE_GET,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.dumpit	= tipc_nl_name_table_dump,
	पूर्ण,
	अणु
		.cmd	= TIPC_NL_MON_SET,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit	= tipc_nl_node_set_monitor,
	पूर्ण,
	अणु
		.cmd	= TIPC_NL_MON_GET,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit	= tipc_nl_node_get_monitor,
		.dumpit	= tipc_nl_node_dump_monitor,
	पूर्ण,
	अणु
		.cmd	= TIPC_NL_MON_PEER_GET,
		.validate = GENL_DONT_VALIDATE_STRICT |
			    GENL_DONT_VALIDATE_DUMP_STRICT,
		.dumpit	= tipc_nl_node_dump_monitor_peer,
	पूर्ण,
	अणु
		.cmd	= TIPC_NL_PEER_REMOVE,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit	= tipc_nl_peer_rm,
	पूर्ण,
#अगर_घोषित CONFIG_TIPC_MEDIA_UDP
	अणु
		.cmd	= TIPC_NL_UDP_GET_REMOTEIP,
		.validate = GENL_DONT_VALIDATE_STRICT |
			    GENL_DONT_VALIDATE_DUMP_STRICT,
		.dumpit	= tipc_udp_nl_dump_remoteip,
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_TIPC_CRYPTO
	अणु
		.cmd	= TIPC_NL_KEY_SET,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit	= tipc_nl_node_set_key,
	पूर्ण,
	अणु
		.cmd	= TIPC_NL_KEY_FLUSH,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit	= tipc_nl_node_flush_key,
	पूर्ण,
#पूर्ण_अगर
	अणु
		.cmd	= TIPC_NL_ADDR_LEGACY_GET,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit	= tipc_nl_net_addr_legacy_get,
	पूर्ण,
पूर्ण;

काष्ठा genl_family tipc_genl_family __ro_after_init = अणु
	.name		= TIPC_GENL_V2_NAME,
	.version	= TIPC_GENL_V2_VERSION,
	.hdrsize	= 0,
	.maxattr	= TIPC_NLA_MAX,
	.policy		= tipc_nl_policy,
	.netnsok	= true,
	.module		= THIS_MODULE,
	.ops		= tipc_genl_v2_ops,
	.n_ops		= ARRAY_SIZE(tipc_genl_v2_ops),
पूर्ण;

पूर्णांक __init tipc_netlink_start(व्योम)
अणु
	पूर्णांक res;

	res = genl_रेजिस्टर_family(&tipc_genl_family);
	अगर (res) अणु
		pr_err("Failed to register netlink interface\n");
		वापस res;
	पूर्ण
	वापस 0;
पूर्ण

व्योम tipc_netlink_stop(व्योम)
अणु
	genl_unरेजिस्टर_family(&tipc_genl_family);
पूर्ण
