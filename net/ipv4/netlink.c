<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#समावेश <linux/netlink.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/types.h>
#समावेश <net/net_namespace.h>
#समावेश <net/netlink.h>
#समावेश <linux/in6.h>
#समावेश <net/ip.h>

पूर्णांक rपंचांग_getroute_parse_ip_proto(काष्ठा nlattr *attr, u8 *ip_proto, u8 family,
				काष्ठा netlink_ext_ack *extack)
अणु
	*ip_proto = nla_get_u8(attr);

	चयन (*ip_proto) अणु
	हाल IPPROTO_TCP:
	हाल IPPROTO_UDP:
		वापस 0;
	हाल IPPROTO_ICMP:
		अगर (family != AF_INET)
			अवरोध;
		वापस 0;
#अगर IS_ENABLED(CONFIG_IPV6)
	हाल IPPROTO_ICMPV6:
		अगर (family != AF_INET6)
			अवरोध;
		वापस 0;
#पूर्ण_अगर
	पूर्ण
	NL_SET_ERR_MSG(extack, "Unsupported ip proto");
	वापस -EOPNOTSUPP;
पूर्ण
EXPORT_SYMBOL_GPL(rपंचांग_getroute_parse_ip_proto);
