<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2016 Jason A. Donenfeld <Jason@zx2c4.com>. All Rights Reserved.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/cache.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/hrसमयr.h>
#समावेश <linux/kसमय.स>
#समावेश <linux/माला.स>
#समावेश <linux/net.h>
#समावेश <linux/siphash.h>
#समावेश <net/secure_seq.h>

#अगर IS_ENABLED(CONFIG_IPV6) || IS_ENABLED(CONFIG_INET)
#समावेश <linux/in6.h>
#समावेश <net/tcp.h>

अटल siphash_key_t net_secret __पढ़ो_mostly;
अटल siphash_key_t ts_secret __पढ़ो_mostly;

अटल __always_अंतरभूत व्योम net_secret_init(व्योम)
अणु
	net_get_अक्रमom_once(&net_secret, माप(net_secret));
पूर्ण

अटल __always_अंतरभूत व्योम ts_secret_init(व्योम)
अणु
	net_get_अक्रमom_once(&ts_secret, माप(ts_secret));
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_INET
अटल u32 seq_scale(u32 seq)
अणु
	/*
	 *	As बंद as possible to RFC 793, which
	 *	suggests using a 250 kHz घड़ी.
	 *	Further पढ़ोing shows this assumes 2 Mb/s networks.
	 *	For 10 Mb/s Ethernet, a 1 MHz घड़ी is appropriate.
	 *	For 10 Gb/s Ethernet, a 1 GHz घड़ी should be ok, but
	 *	we also need to limit the resolution so that the u32 seq
	 *	overlaps less than one समय per MSL (2 minutes).
	 *	Choosing a घड़ी of 64 ns period is OK. (period of 274 s)
	 */
	वापस seq + (kसमय_get_real_ns() >> 6);
पूर्ण
#पूर्ण_अगर

#अगर IS_ENABLED(CONFIG_IPV6)
u32 secure_tcpv6_ts_off(स्थिर काष्ठा net *net,
			स्थिर __be32 *saddr, स्थिर __be32 *daddr)
अणु
	स्थिर काष्ठा अणु
		काष्ठा in6_addr saddr;
		काष्ठा in6_addr daddr;
	पूर्ण __aligned(SIPHASH_ALIGNMENT) combined = अणु
		.saddr = *(काष्ठा in6_addr *)saddr,
		.daddr = *(काष्ठा in6_addr *)daddr,
	पूर्ण;

	अगर (net->ipv4.sysctl_tcp_बारtamps != 1)
		वापस 0;

	ts_secret_init();
	वापस siphash(&combined, दुरत्वend(typeof(combined), daddr),
		       &ts_secret);
पूर्ण
EXPORT_SYMBOL(secure_tcpv6_ts_off);

u32 secure_tcpv6_seq(स्थिर __be32 *saddr, स्थिर __be32 *daddr,
		     __be16 sport, __be16 dport)
अणु
	स्थिर काष्ठा अणु
		काष्ठा in6_addr saddr;
		काष्ठा in6_addr daddr;
		__be16 sport;
		__be16 dport;
	पूर्ण __aligned(SIPHASH_ALIGNMENT) combined = अणु
		.saddr = *(काष्ठा in6_addr *)saddr,
		.daddr = *(काष्ठा in6_addr *)daddr,
		.sport = sport,
		.dport = dport
	पूर्ण;
	u32 hash;

	net_secret_init();
	hash = siphash(&combined, दुरत्वend(typeof(combined), dport),
		       &net_secret);
	वापस seq_scale(hash);
पूर्ण
EXPORT_SYMBOL(secure_tcpv6_seq);

u32 secure_ipv6_port_ephemeral(स्थिर __be32 *saddr, स्थिर __be32 *daddr,
			       __be16 dport)
अणु
	स्थिर काष्ठा अणु
		काष्ठा in6_addr saddr;
		काष्ठा in6_addr daddr;
		__be16 dport;
	पूर्ण __aligned(SIPHASH_ALIGNMENT) combined = अणु
		.saddr = *(काष्ठा in6_addr *)saddr,
		.daddr = *(काष्ठा in6_addr *)daddr,
		.dport = dport
	पूर्ण;
	net_secret_init();
	वापस siphash(&combined, दुरत्वend(typeof(combined), dport),
		       &net_secret);
पूर्ण
EXPORT_SYMBOL(secure_ipv6_port_ephemeral);
#पूर्ण_अगर

#अगर_घोषित CONFIG_INET
u32 secure_tcp_ts_off(स्थिर काष्ठा net *net, __be32 saddr, __be32 daddr)
अणु
	अगर (net->ipv4.sysctl_tcp_बारtamps != 1)
		वापस 0;

	ts_secret_init();
	वापस siphash_2u32((__क्रमce u32)saddr, (__क्रमce u32)daddr,
			    &ts_secret);
पूर्ण

/* secure_tcp_seq_and_tsoff(a, b, 0, d) == secure_ipv4_port_ephemeral(a, b, d),
 * but क्रमtunately, `sport' cannot be 0 in any circumstances. If this changes,
 * it would be easy enough to have the क्रमmer function use siphash_4u32, passing
 * the arguments as separate u32.
 */
u32 secure_tcp_seq(__be32 saddr, __be32 daddr,
		   __be16 sport, __be16 dport)
अणु
	u32 hash;

	net_secret_init();
	hash = siphash_3u32((__क्रमce u32)saddr, (__क्रमce u32)daddr,
			    (__क्रमce u32)sport << 16 | (__क्रमce u32)dport,
			    &net_secret);
	वापस seq_scale(hash);
पूर्ण
EXPORT_SYMBOL_GPL(secure_tcp_seq);

u32 secure_ipv4_port_ephemeral(__be32 saddr, __be32 daddr, __be16 dport)
अणु
	net_secret_init();
	वापस siphash_3u32((__क्रमce u32)saddr, (__क्रमce u32)daddr,
			    (__क्रमce u16)dport, &net_secret);
पूर्ण
EXPORT_SYMBOL_GPL(secure_ipv4_port_ephemeral);
#पूर्ण_अगर

#अगर IS_ENABLED(CONFIG_IP_DCCP)
u64 secure_dccp_sequence_number(__be32 saddr, __be32 daddr,
				__be16 sport, __be16 dport)
अणु
	u64 seq;
	net_secret_init();
	seq = siphash_3u32((__क्रमce u32)saddr, (__क्रमce u32)daddr,
			   (__क्रमce u32)sport << 16 | (__क्रमce u32)dport,
			   &net_secret);
	seq += kसमय_get_real_ns();
	seq &= (1ull << 48) - 1;
	वापस seq;
पूर्ण
EXPORT_SYMBOL(secure_dccp_sequence_number);

#अगर IS_ENABLED(CONFIG_IPV6)
u64 secure_dccpv6_sequence_number(__be32 *saddr, __be32 *daddr,
				  __be16 sport, __be16 dport)
अणु
	स्थिर काष्ठा अणु
		काष्ठा in6_addr saddr;
		काष्ठा in6_addr daddr;
		__be16 sport;
		__be16 dport;
	पूर्ण __aligned(SIPHASH_ALIGNMENT) combined = अणु
		.saddr = *(काष्ठा in6_addr *)saddr,
		.daddr = *(काष्ठा in6_addr *)daddr,
		.sport = sport,
		.dport = dport
	पूर्ण;
	u64 seq;
	net_secret_init();
	seq = siphash(&combined, दुरत्वend(typeof(combined), dport),
		      &net_secret);
	seq += kसमय_get_real_ns();
	seq &= (1ull << 48) - 1;
	वापस seq;
पूर्ण
EXPORT_SYMBOL(secure_dccpv6_sequence_number);
#पूर्ण_अगर
#पूर्ण_अगर
