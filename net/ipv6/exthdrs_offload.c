<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *	IPV6 GSO/GRO offload support
 *	Linux INET6 implementation
 *
 *      IPV6 Extension Header GSO/GRO support
 */
#समावेश <net/protocol.h>
#समावेश "ip6_offload.h"

अटल स्थिर काष्ठा net_offload rthdr_offload = अणु
	.flags		=	INET6_PROTO_GSO_EXTHDR,
पूर्ण;

अटल स्थिर काष्ठा net_offload dstopt_offload = अणु
	.flags		=	INET6_PROTO_GSO_EXTHDR,
पूर्ण;

पूर्णांक __init ipv6_exthdrs_offload_init(व्योम)
अणु
	पूर्णांक ret;

	ret = inet6_add_offload(&rthdr_offload, IPPROTO_ROUTING);
	अगर (ret)
		जाओ out;

	ret = inet6_add_offload(&dstopt_offload, IPPROTO_DSTOPTS);
	अगर (ret)
		जाओ out_rt;

out:
	वापस ret;

out_rt:
	inet6_del_offload(&rthdr_offload, IPPROTO_ROUTING);
	जाओ out;
पूर्ण
