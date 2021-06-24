<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __NETNS_MIB_H__
#घोषणा __NETNS_MIB_H__

#समावेश <net/snmp.h>

काष्ठा netns_mib अणु
	DEFINE_SNMP_STAT(काष्ठा ipstats_mib, ip_statistics);
#अगर IS_ENABLED(CONFIG_IPV6)
	DEFINE_SNMP_STAT(काष्ठा ipstats_mib, ipv6_statistics);
#पूर्ण_अगर

	DEFINE_SNMP_STAT(काष्ठा tcp_mib, tcp_statistics);
	DEFINE_SNMP_STAT(काष्ठा linux_mib, net_statistics);

	DEFINE_SNMP_STAT(काष्ठा udp_mib, udp_statistics);
#अगर IS_ENABLED(CONFIG_IPV6)
	DEFINE_SNMP_STAT(काष्ठा udp_mib, udp_stats_in6);
#पूर्ण_अगर

#अगर_घोषित CONFIG_XFRM_STATISTICS
	DEFINE_SNMP_STAT(काष्ठा linux_xfrm_mib, xfrm_statistics);
#पूर्ण_अगर
#अगर IS_ENABLED(CONFIG_TLS)
	DEFINE_SNMP_STAT(काष्ठा linux_tls_mib, tls_statistics);
#पूर्ण_अगर
#अगर_घोषित CONFIG_MPTCP
	DEFINE_SNMP_STAT(काष्ठा mptcp_mib, mptcp_statistics);
#पूर्ण_अगर

	DEFINE_SNMP_STAT(काष्ठा udp_mib, udplite_statistics);
#अगर IS_ENABLED(CONFIG_IPV6)
	DEFINE_SNMP_STAT(काष्ठा udp_mib, udplite_stats_in6);
#पूर्ण_अगर

	DEFINE_SNMP_STAT(काष्ठा icmp_mib, icmp_statistics);
	DEFINE_SNMP_STAT_ATOMIC(काष्ठा icmpmsg_mib, icmpmsg_statistics);
#अगर IS_ENABLED(CONFIG_IPV6)
	DEFINE_SNMP_STAT(काष्ठा icmpv6_mib, icmpv6_statistics);
	DEFINE_SNMP_STAT_ATOMIC(काष्ठा icmpv6msg_mib, icmpv6msg_statistics);
	काष्ठा proc_dir_entry *proc_net_devsnmp6;
#पूर्ण_अगर
पूर्ण;

#पूर्ण_अगर
