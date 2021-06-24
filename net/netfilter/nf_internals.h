<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _NF_INTERNALS_H
#घोषणा _NF_INTERNALS_H

#समावेश <linux/list.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/netdevice.h>

/* nf_conntrack_netlink.c: applied on tuple filters */
#घोषणा CTA_FILTER_F_CTA_IP_SRC			(1 << 0)
#घोषणा CTA_FILTER_F_CTA_IP_DST			(1 << 1)
#घोषणा CTA_FILTER_F_CTA_TUPLE_ZONE		(1 << 2)
#घोषणा CTA_FILTER_F_CTA_PROTO_NUM		(1 << 3)
#घोषणा CTA_FILTER_F_CTA_PROTO_SRC_PORT		(1 << 4)
#घोषणा CTA_FILTER_F_CTA_PROTO_DST_PORT		(1 << 5)
#घोषणा CTA_FILTER_F_CTA_PROTO_ICMP_TYPE	(1 << 6)
#घोषणा CTA_FILTER_F_CTA_PROTO_ICMP_CODE	(1 << 7)
#घोषणा CTA_FILTER_F_CTA_PROTO_ICMP_ID		(1 << 8)
#घोषणा CTA_FILTER_F_CTA_PROTO_ICMPV6_TYPE	(1 << 9)
#घोषणा CTA_FILTER_F_CTA_PROTO_ICMPV6_CODE	(1 << 10)
#घोषणा CTA_FILTER_F_CTA_PROTO_ICMPV6_ID	(1 << 11)
#घोषणा CTA_FILTER_F_MAX			(1 << 12)
#घोषणा CTA_FILTER_F_ALL			(CTA_FILTER_F_MAX-1)
#घोषणा CTA_FILTER_FLAG(ctattr) CTA_FILTER_F_ ## ctattr

/* nf_queue.c */
व्योम nf_queue_nf_hook_drop(काष्ठा net *net);

/* nf_log.c */
पूर्णांक __init netfilter_log_init(व्योम);

/* core.c */
व्योम nf_hook_entries_delete_raw(काष्ठा nf_hook_entries __rcu **pp,
				स्थिर काष्ठा nf_hook_ops *reg);
पूर्णांक nf_hook_entries_insert_raw(काष्ठा nf_hook_entries __rcu **pp,
				स्थिर काष्ठा nf_hook_ops *reg);
#पूर्ण_अगर
