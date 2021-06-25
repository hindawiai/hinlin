<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *
 *		SNMP MIB entries क्रम the IP subप्रणाली.
 *		
 *		Alan Cox <gw4pts@gw4pts.ampr.org>
 *
 *		We करोn't chose to implement SNMP in the kernel (this would
 *		be silly as SNMP is a pain in the backside in places). We करो
 *		however need to collect the MIB statistics and export them
 *		out of /proc (eventually)
 */
 
#अगर_अघोषित _SNMP_H
#घोषणा _SNMP_H

#समावेश <linux/cache.h>
#समावेश <linux/snmp.h>
#समावेश <linux/smp.h>

/*
 * Mibs are stored in array of अचिन्हित दीर्घ.
 */
/*
 * काष्ठा snmp_mibअणुपूर्ण
 *  - list of entries क्रम particular API (such as /proc/net/snmp)
 *  - name of entries.
 */
काष्ठा snmp_mib अणु
	स्थिर अक्षर *name;
	पूर्णांक entry;
पूर्ण;

#घोषणा SNMP_MIB_ITEM(_name,_entry)	अणु	\
	.name = _name,				\
	.entry = _entry,			\
पूर्ण

#घोषणा SNMP_MIB_SENTINEL अणु	\
	.name = शून्य,		\
	.entry = 0,		\
पूर्ण

/*
 * We use अचिन्हित दीर्घs क्रम most mibs but u64 क्रम ipstats.
 */
#समावेश <linux/u64_stats_sync.h>

/* IPstats */
#घोषणा IPSTATS_MIB_MAX	__IPSTATS_MIB_MAX
काष्ठा ipstats_mib अणु
	/* mibs[] must be first field of काष्ठा ipstats_mib */
	u64		mibs[IPSTATS_MIB_MAX];
	काष्ठा u64_stats_sync syncp;
पूर्ण;

/* ICMP */
#घोषणा ICMP_MIB_MAX	__ICMP_MIB_MAX
काष्ठा icmp_mib अणु
	अचिन्हित दीर्घ	mibs[ICMP_MIB_MAX];
पूर्ण;

#घोषणा ICMPMSG_MIB_MAX	__ICMPMSG_MIB_MAX
काष्ठा icmpmsg_mib अणु
	atomic_दीर्घ_t	mibs[ICMPMSG_MIB_MAX];
पूर्ण;

/* ICMP6 (IPv6-ICMP) */
#घोषणा ICMP6_MIB_MAX	__ICMP6_MIB_MAX
/* per network ns counters */
काष्ठा icmpv6_mib अणु
	अचिन्हित दीर्घ	mibs[ICMP6_MIB_MAX];
पूर्ण;
/* per device counters, (shared on all cpus) */
काष्ठा icmpv6_mib_device अणु
	atomic_दीर्घ_t	mibs[ICMP6_MIB_MAX];
पूर्ण;

#घोषणा ICMP6MSG_MIB_MAX  __ICMP6MSG_MIB_MAX
/* per network ns counters */
काष्ठा icmpv6msg_mib अणु
	atomic_दीर्घ_t	mibs[ICMP6MSG_MIB_MAX];
पूर्ण;
/* per device counters, (shared on all cpus) */
काष्ठा icmpv6msg_mib_device अणु
	atomic_दीर्घ_t	mibs[ICMP6MSG_MIB_MAX];
पूर्ण;


/* TCP */
#घोषणा TCP_MIB_MAX	__TCP_MIB_MAX
काष्ठा tcp_mib अणु
	अचिन्हित दीर्घ	mibs[TCP_MIB_MAX];
पूर्ण;

/* UDP */
#घोषणा UDP_MIB_MAX	__UDP_MIB_MAX
काष्ठा udp_mib अणु
	अचिन्हित दीर्घ	mibs[UDP_MIB_MAX];
पूर्ण;

/* Linux */
#घोषणा LINUX_MIB_MAX	__LINUX_MIB_MAX
काष्ठा linux_mib अणु
	अचिन्हित दीर्घ	mibs[LINUX_MIB_MAX];
पूर्ण;

/* Linux Xfrm */
#घोषणा LINUX_MIB_XFRMMAX	__LINUX_MIB_XFRMMAX
काष्ठा linux_xfrm_mib अणु
	अचिन्हित दीर्घ	mibs[LINUX_MIB_XFRMMAX];
पूर्ण;

/* Linux TLS */
#घोषणा LINUX_MIB_TLSMAX	__LINUX_MIB_TLSMAX
काष्ठा linux_tls_mib अणु
	अचिन्हित दीर्घ	mibs[LINUX_MIB_TLSMAX];
पूर्ण;

#घोषणा DEFINE_SNMP_STAT(type, name)	\
	__typeof__(type) __percpu *name
#घोषणा DEFINE_SNMP_STAT_ATOMIC(type, name)	\
	__typeof__(type) *name
#घोषणा DECLARE_SNMP_STAT(type, name)	\
	बाह्य __typeof__(type) __percpu *name

#घोषणा __SNMP_INC_STATS(mib, field)	\
			__this_cpu_inc(mib->mibs[field])

#घोषणा SNMP_INC_STATS_ATOMIC_LONG(mib, field)	\
			atomic_दीर्घ_inc(&mib->mibs[field])

#घोषणा SNMP_INC_STATS(mib, field)	\
			this_cpu_inc(mib->mibs[field])

#घोषणा SNMP_DEC_STATS(mib, field)	\
			this_cpu_dec(mib->mibs[field])

#घोषणा __SNMP_ADD_STATS(mib, field, addend)	\
			__this_cpu_add(mib->mibs[field], addend)

#घोषणा SNMP_ADD_STATS(mib, field, addend)	\
			this_cpu_add(mib->mibs[field], addend)
#घोषणा SNMP_UPD_PO_STATS(mib, basefield, addend)	\
	करो अणु \
		__typeof__((mib->mibs) + 0) ptr = mib->mibs;	\
		this_cpu_inc(ptr[basefield##PKTS]);		\
		this_cpu_add(ptr[basefield##OCTETS], addend);	\
	पूर्ण जबतक (0)
#घोषणा __SNMP_UPD_PO_STATS(mib, basefield, addend)	\
	करो अणु \
		__typeof__((mib->mibs) + 0) ptr = mib->mibs;	\
		__this_cpu_inc(ptr[basefield##PKTS]);		\
		__this_cpu_add(ptr[basefield##OCTETS], addend);	\
	पूर्ण जबतक (0)


#अगर BITS_PER_LONG==32

#घोषणा __SNMP_ADD_STATS64(mib, field, addend) 				\
	करो अणु								\
		__typeof__(*mib) *ptr = raw_cpu_ptr(mib);		\
		u64_stats_update_begin(&ptr->syncp);			\
		ptr->mibs[field] += addend;				\
		u64_stats_update_end(&ptr->syncp);			\
	पूर्ण जबतक (0)

#घोषणा SNMP_ADD_STATS64(mib, field, addend) 				\
	करो अणु								\
		local_bh_disable();					\
		__SNMP_ADD_STATS64(mib, field, addend);			\
		local_bh_enable();				\
	पूर्ण जबतक (0)

#घोषणा __SNMP_INC_STATS64(mib, field) SNMP_ADD_STATS64(mib, field, 1)
#घोषणा SNMP_INC_STATS64(mib, field) SNMP_ADD_STATS64(mib, field, 1)
#घोषणा __SNMP_UPD_PO_STATS64(mib, basefield, addend)			\
	करो अणु								\
		__typeof__(*mib) *ptr;				\
		ptr = raw_cpu_ptr((mib));				\
		u64_stats_update_begin(&ptr->syncp);			\
		ptr->mibs[basefield##PKTS]++;				\
		ptr->mibs[basefield##OCTETS] += addend;			\
		u64_stats_update_end(&ptr->syncp);			\
	पूर्ण जबतक (0)
#घोषणा SNMP_UPD_PO_STATS64(mib, basefield, addend)			\
	करो अणु								\
		local_bh_disable();					\
		__SNMP_UPD_PO_STATS64(mib, basefield, addend);		\
		local_bh_enable();				\
	पूर्ण जबतक (0)
#अन्यथा
#घोषणा __SNMP_INC_STATS64(mib, field)		__SNMP_INC_STATS(mib, field)
#घोषणा SNMP_INC_STATS64(mib, field)		SNMP_INC_STATS(mib, field)
#घोषणा SNMP_DEC_STATS64(mib, field)		SNMP_DEC_STATS(mib, field)
#घोषणा __SNMP_ADD_STATS64(mib, field, addend)	__SNMP_ADD_STATS(mib, field, addend)
#घोषणा SNMP_ADD_STATS64(mib, field, addend)	SNMP_ADD_STATS(mib, field, addend)
#घोषणा SNMP_UPD_PO_STATS64(mib, basefield, addend) SNMP_UPD_PO_STATS(mib, basefield, addend)
#घोषणा __SNMP_UPD_PO_STATS64(mib, basefield, addend) __SNMP_UPD_PO_STATS(mib, basefield, addend)
#पूर्ण_अगर

#पूर्ण_अगर
