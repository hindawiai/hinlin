<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB */
/* Copyright (c) 2019 Mellanox Technologies. */

#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM mlx5

#अगर !defined(_MLX5_EN_REP_TP_) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _MLX5_EN_REP_TP_

#समावेश <linux/tracepoपूर्णांक.h>
#समावेश <linux/trace_seq.h>
#समावेश "en_rep.h"

TRACE_EVENT(mlx5e_rep_neigh_update,
	    TP_PROTO(स्थिर काष्ठा mlx5e_neigh_hash_entry *nhe, स्थिर u8 *ha,
		     bool neigh_connected),
	    TP_ARGS(nhe, ha, neigh_connected),
	    TP_STRUCT__entry(__string(devname, nhe->neigh_dev->name)
			     __array(u8, ha, ETH_ALEN)
			     __array(u8, v4, 4)
			     __array(u8, v6, 16)
			     __field(bool, neigh_connected)
			     ),
	    TP_fast_assign(स्थिर काष्ठा mlx5e_neigh *mn = &nhe->m_neigh;
			काष्ठा in6_addr *pin6;
			__be32 *p32;

			__assign_str(devname, nhe->neigh_dev->name);
			__entry->neigh_connected = neigh_connected;
			स_नकल(__entry->ha, ha, ETH_ALEN);

			p32 = (__be32 *)__entry->v4;
			pin6 = (काष्ठा in6_addr *)__entry->v6;
			अगर (mn->family == AF_INET) अणु
				*p32 = mn->dst_ip.v4;
				ipv6_addr_set_v4mapped(*p32, pin6);
			पूर्ण अन्यथा अगर (mn->family == AF_INET6) अणु
				*pin6 = mn->dst_ip.v6;
			पूर्ण
			),
	    TP_prपूर्णांकk("netdev: %s MAC: %pM IPv4: %pI4 IPv6: %pI6c neigh_connected=%d\n",
		      __get_str(devname), __entry->ha,
		      __entry->v4, __entry->v6, __entry->neigh_connected
		      )
);

#पूर्ण_अगर /* _MLX5_EN_REP_TP_ */

/* This part must be outside protection */
#अघोषित TRACE_INCLUDE_PATH
#घोषणा TRACE_INCLUDE_PATH ./diag
#अघोषित TRACE_INCLUDE_खाता
#घोषणा TRACE_INCLUDE_खाता en_rep_tracepoपूर्णांक
#समावेश <trace/define_trace.h>
