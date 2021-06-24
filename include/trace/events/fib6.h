<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM fib6

#अगर !defined(_TRACE_FIB6_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _TRACE_FIB6_H

#समावेश <linux/in6.h>
#समावेश <net/flow.h>
#समावेश <net/ip6_fib.h>
#समावेश <linux/tracepoपूर्णांक.h>

TRACE_EVENT(fib6_table_lookup,

	TP_PROTO(स्थिर काष्ठा net *net, स्थिर काष्ठा fib6_result *res,
		 काष्ठा fib6_table *table, स्थिर काष्ठा flowi6 *flp),

	TP_ARGS(net, res, table, flp),

	TP_STRUCT__entry(
		__field(	u32,	tb_id		)
		__field(	पूर्णांक,	err		)
		__field(	पूर्णांक,	oअगर		)
		__field(	पूर्णांक,	iअगर		)
		__field(	__u8,	tos		)
		__field(	__u8,	scope		)
		__field(	__u8,	flags		)
		__array(	__u8,	src,	16	)
		__array(	__u8,	dst,	16	)
		__field(        u16,	sport		)
		__field(        u16,	dport		)
		__field(        u8,	proto		)
		__field(        u8,	rt_type		)
		__dynamic_array(	अक्षर,	name,	IFNAMSIZ )
		__array(		__u8,	gw,	16	 )
	),

	TP_fast_assign(
		काष्ठा in6_addr *in6;

		__entry->tb_id = table->tb6_id;
		__entry->err = ip6_rt_type_to_error(res->fib6_type);
		__entry->oअगर = flp->flowi6_oअगर;
		__entry->iअगर = flp->flowi6_iअगर;
		__entry->tos = ip6_tclass(flp->flowlabel);
		__entry->scope = flp->flowi6_scope;
		__entry->flags = flp->flowi6_flags;

		in6 = (काष्ठा in6_addr *)__entry->src;
		*in6 = flp->saddr;

		in6 = (काष्ठा in6_addr *)__entry->dst;
		*in6 = flp->daddr;

		__entry->proto = flp->flowi6_proto;
		अगर (__entry->proto == IPPROTO_TCP ||
		    __entry->proto == IPPROTO_UDP) अणु
			__entry->sport = ntohs(flp->fl6_sport);
			__entry->dport = ntohs(flp->fl6_dport);
		पूर्ण अन्यथा अणु
			__entry->sport = 0;
			__entry->dport = 0;
		पूर्ण

		अगर (res->nh && res->nh->fib_nh_dev) अणु
			__assign_str(name, res->nh->fib_nh_dev);
		पूर्ण अन्यथा अणु
			__assign_str(name, "-");
		पूर्ण
		अगर (res->f6i == net->ipv6.fib6_null_entry) अणु
			काष्ठा in6_addr in6_zero = अणुपूर्ण;

			in6 = (काष्ठा in6_addr *)__entry->gw;
			*in6 = in6_zero;

		पूर्ण अन्यथा अगर (res->nh) अणु
			in6 = (काष्ठा in6_addr *)__entry->gw;
			*in6 = res->nh->fib_nh_gw6;
		पूर्ण
	),

	TP_prपूर्णांकk("table %3u oif %d iif %d proto %u %pI6c/%u -> %pI6c/%u tos %d scope %d flags %x ==> dev %s gw %pI6c err %d",
		  __entry->tb_id, __entry->oअगर, __entry->iअगर, __entry->proto,
		  __entry->src, __entry->sport, __entry->dst, __entry->dport,
		  __entry->tos, __entry->scope, __entry->flags,
		  __get_str(name), __entry->gw, __entry->err)
);

#पूर्ण_अगर /* _TRACE_FIB6_H */

/* This part must be outside protection */
#समावेश <trace/define_trace.h>
