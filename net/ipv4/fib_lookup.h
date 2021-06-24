<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _FIB_LOOKUP_H
#घोषणा _FIB_LOOKUP_H

#समावेश <linux/types.h>
#समावेश <linux/list.h>
#समावेश <net/ip_fib.h>
#समावेश <net/nexthop.h>

काष्ठा fib_alias अणु
	काष्ठा hlist_node	fa_list;
	काष्ठा fib_info		*fa_info;
	u8			fa_tos;
	u8			fa_type;
	u8			fa_state;
	u8			fa_slen;
	u32			tb_id;
	s16			fa_शेष;
	u8			offload:1,
				trap:1,
				offload_failed:1,
				unused:5;
	काष्ठा rcu_head		rcu;
पूर्ण;

#घोषणा FA_S_ACCESSED	0x01

/* Dont ग_लिखो on fa_state unless needed, to keep it shared on all cpus */
अटल अंतरभूत व्योम fib_alias_accessed(काष्ठा fib_alias *fa)
अणु
	अगर (!(fa->fa_state & FA_S_ACCESSED))
		fa->fa_state |= FA_S_ACCESSED;
पूर्ण

/* Exported by fib_semantics.c */
व्योम fib_release_info(काष्ठा fib_info *);
काष्ठा fib_info *fib_create_info(काष्ठा fib_config *cfg,
				 काष्ठा netlink_ext_ack *extack);
पूर्णांक fib_nh_match(काष्ठा net *net, काष्ठा fib_config *cfg, काष्ठा fib_info *fi,
		 काष्ठा netlink_ext_ack *extack);
bool fib_metrics_match(काष्ठा fib_config *cfg, काष्ठा fib_info *fi);
पूर्णांक fib_dump_info(काष्ठा sk_buff *skb, u32 pid, u32 seq, पूर्णांक event,
		  स्थिर काष्ठा fib_rt_info *fri, अचिन्हित पूर्णांक flags);
व्योम rपंचांगsg_fib(पूर्णांक event, __be32 key, काष्ठा fib_alias *fa, पूर्णांक dst_len,
	       u32 tb_id, स्थिर काष्ठा nl_info *info, अचिन्हित पूर्णांक nlm_flags);
माप_प्रकार fib_nlmsg_size(काष्ठा fib_info *fi);

अटल अंतरभूत व्योम fib_result_assign(काष्ठा fib_result *res,
				     काष्ठा fib_info *fi)
अणु
	/* we used to play games with refcounts, but we now use RCU */
	res->fi = fi;
	res->nhc = fib_info_nhc(fi, 0);
पूर्ण

काष्ठा fib_prop अणु
	पूर्णांक	error;
	u8	scope;
पूर्ण;

बाह्य स्थिर काष्ठा fib_prop fib_props[RTN_MAX + 1];

#पूर्ण_अगर /* _FIB_LOOKUP_H */
