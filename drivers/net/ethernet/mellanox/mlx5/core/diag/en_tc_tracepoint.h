<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB */
/* Copyright (c) 2019 Mellanox Technologies. */

#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM mlx5

#अगर !defined(_MLX5_TC_TP_) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _MLX5_TC_TP_

#समावेश <linux/tracepoपूर्णांक.h>
#समावेश <linux/trace_seq.h>
#समावेश <net/flow_offload.h>
#समावेश "en_rep.h"

#घोषणा __parse_action(ids, num) parse_action(p, ids, num)

व्योम put_ids_to_array(पूर्णांक *ids,
		      स्थिर काष्ठा flow_action_entry *entries,
		      अचिन्हित पूर्णांक num);

स्थिर अक्षर *parse_action(काष्ठा trace_seq *p,
			 पूर्णांक *ids,
			 अचिन्हित पूर्णांक num);

DECLARE_EVENT_CLASS(mlx5e_flower_ढाँचा,
		    TP_PROTO(स्थिर काष्ठा flow_cls_offload *f),
		    TP_ARGS(f),
		    TP_STRUCT__entry(__field(व्योम *, cookie)
				     __field(अचिन्हित पूर्णांक, num)
				     __dynamic_array(पूर्णांक, ids, f->rule ?
					     f->rule->action.num_entries : 0)
				     ),
		    TP_fast_assign(__entry->cookie = (व्योम *)f->cookie;
			__entry->num = (f->rule ?
				f->rule->action.num_entries : 0);
			अगर (__entry->num)
				put_ids_to_array(__get_dynamic_array(ids),
						 f->rule->action.entries,
						 f->rule->action.num_entries);
			),
		    TP_prपूर्णांकk("cookie=%p actions= %s\n",
			      __entry->cookie, __entry->num ?
				      __parse_action(__get_dynamic_array(ids),
						     __entry->num) : "NULL"
			      )
);

DEFINE_EVENT(mlx5e_flower_ढाँचा, mlx5e_configure_flower,
	     TP_PROTO(स्थिर काष्ठा flow_cls_offload *f),
	     TP_ARGS(f)
	     );

DEFINE_EVENT(mlx5e_flower_ढाँचा, mlx5e_delete_flower,
	     TP_PROTO(स्थिर काष्ठा flow_cls_offload *f),
	     TP_ARGS(f)
	     );

TRACE_EVENT(mlx5e_stats_flower,
	    TP_PROTO(स्थिर काष्ठा flow_cls_offload *f),
	    TP_ARGS(f),
	    TP_STRUCT__entry(__field(व्योम *, cookie)
			     __field(u64, bytes)
			     __field(u64, packets)
			     __field(u64, lastused)
			     ),
	    TP_fast_assign(__entry->cookie = (व्योम *)f->cookie;
		__entry->bytes = f->stats.bytes;
		__entry->packets = f->stats.pkts;
		__entry->lastused = f->stats.lastused;
		),
	    TP_prपूर्णांकk("cookie=%p bytes=%llu packets=%llu lastused=%llu\n",
		      __entry->cookie, __entry->bytes,
		      __entry->packets, __entry->lastused
		      )
);

TRACE_EVENT(mlx5e_tc_update_neigh_used_value,
	    TP_PROTO(स्थिर काष्ठा mlx5e_neigh_hash_entry *nhe, bool neigh_used),
	    TP_ARGS(nhe, neigh_used),
	    TP_STRUCT__entry(__string(devname, nhe->neigh_dev->name)
			     __array(u8, v4, 4)
			     __array(u8, v6, 16)
			     __field(bool, neigh_used)
			     ),
	    TP_fast_assign(स्थिर काष्ठा mlx5e_neigh *mn = &nhe->m_neigh;
			काष्ठा in6_addr *pin6;
			__be32 *p32;

			__assign_str(devname, nhe->neigh_dev->name);
			__entry->neigh_used = neigh_used;

			p32 = (__be32 *)__entry->v4;
			pin6 = (काष्ठा in6_addr *)__entry->v6;
			अगर (mn->family == AF_INET) अणु
				*p32 = mn->dst_ip.v4;
				ipv6_addr_set_v4mapped(*p32, pin6);
			पूर्ण अन्यथा अगर (mn->family == AF_INET6) अणु
				*pin6 = mn->dst_ip.v6;
			पूर्ण
			),
	    TP_prपूर्णांकk("netdev: %s IPv4: %pI4 IPv6: %pI6c neigh_used=%d\n",
		      __get_str(devname), __entry->v4, __entry->v6,
		      __entry->neigh_used
		      )
);

#पूर्ण_अगर /* _MLX5_TC_TP_ */

/* This part must be outside protection */
#अघोषित TRACE_INCLUDE_PATH
#घोषणा TRACE_INCLUDE_PATH ./diag
#अघोषित TRACE_INCLUDE_खाता
#घोषणा TRACE_INCLUDE_खाता en_tc_tracepoपूर्णांक
#समावेश <trace/define_trace.h>
