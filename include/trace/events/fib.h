<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM fib

#अगर !defined(_TRACE_FIB_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _TRACE_FIB_H

#समावेश <linux/skbuff.h>
#समावेश <linux/netdevice.h>
#समावेश <net/ip_fib.h>
#समावेश <linux/tracepoपूर्णांक.h>

TRACE_EVENT(fib_table_lookup,

	TP_PROTO(u32 tb_id, स्थिर काष्ठा flowi4 *flp,
		 स्थिर काष्ठा fib_nh_common *nhc, पूर्णांक err),

	TP_ARGS(tb_id, flp, nhc, err),

	TP_STRUCT__entry(
		__field(	u32,	tb_id		)
		__field(	पूर्णांक,	err		)
		__field(	पूर्णांक,	oअगर		)
		__field(	पूर्णांक,	iअगर		)
		__field(	u8,	proto		)
		__field(	__u8,	tos		)
		__field(	__u8,	scope		)
		__field(	__u8,	flags		)
		__array(	__u8,	src,	4	)
		__array(	__u8,	dst,	4	)
		__array(	__u8,	gw4,	4	)
		__array(	__u8,	gw6,	16	)
		__field(	u16,	sport		)
		__field(	u16,	dport		)
		__dynamic_array(अक्षर,  name,   IFNAMSIZ )
	),

	TP_fast_assign(
		काष्ठा in6_addr in6_zero = अणुपूर्ण;
		काष्ठा net_device *dev;
		काष्ठा in6_addr *in6;
		__be32 *p32;

		__entry->tb_id = tb_id;
		__entry->err = err;
		__entry->oअगर = flp->flowi4_oअगर;
		__entry->iअगर = flp->flowi4_iअगर;
		__entry->tos = flp->flowi4_tos;
		__entry->scope = flp->flowi4_scope;
		__entry->flags = flp->flowi4_flags;

		p32 = (__be32 *) __entry->src;
		*p32 = flp->saddr;

		p32 = (__be32 *) __entry->dst;
		*p32 = flp->daddr;

		__entry->proto = flp->flowi4_proto;
		अगर (__entry->proto == IPPROTO_TCP ||
		    __entry->proto == IPPROTO_UDP) अणु
			__entry->sport = ntohs(flp->fl4_sport);
			__entry->dport = ntohs(flp->fl4_dport);
		पूर्ण अन्यथा अणु
			__entry->sport = 0;
			__entry->dport = 0;
		पूर्ण

		dev = nhc ? nhc->nhc_dev : शून्य;
		__assign_str(name, dev ? dev->name : "-");

		अगर (nhc) अणु
			अगर (nhc->nhc_gw_family == AF_INET) अणु
				p32 = (__be32 *) __entry->gw4;
				*p32 = nhc->nhc_gw.ipv4;

				in6 = (काष्ठा in6_addr *)__entry->gw6;
				*in6 = in6_zero;
			पूर्ण अन्यथा अगर (nhc->nhc_gw_family == AF_INET6) अणु
				p32 = (__be32 *) __entry->gw4;
				*p32 = 0;

				in6 = (काष्ठा in6_addr *)__entry->gw6;
				*in6 = nhc->nhc_gw.ipv6;
			पूर्ण
		पूर्ण अन्यथा अणु
			p32 = (__be32 *) __entry->gw4;
			*p32 = 0;

			in6 = (काष्ठा in6_addr *)__entry->gw6;
			*in6 = in6_zero;
		पूर्ण
	),

	TP_prपूर्णांकk("table %u oif %d iif %d proto %u %pI4/%u -> %pI4/%u tos %d scope %d flags %x ==> dev %s gw %pI4/%pI6c err %d",
		  __entry->tb_id, __entry->oअगर, __entry->iअगर, __entry->proto,
		  __entry->src, __entry->sport, __entry->dst, __entry->dport,
		  __entry->tos, __entry->scope, __entry->flags,
		  __get_str(name), __entry->gw4, __entry->gw6, __entry->err)
);
#पूर्ण_अगर /* _TRACE_FIB_H */

/* This part must be outside protection */
#समावेश <trace/define_trace.h>
