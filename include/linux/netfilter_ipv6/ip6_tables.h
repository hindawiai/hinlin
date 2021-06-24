<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * 25-Jul-1998 Major changes to allow क्रम ip chain table
 *
 * 3-Jan-2000 Named tables to allow packet selection क्रम dअगरferent uses.
 */

/*
 * 	Format of an IP6 firewall descriptor
 *
 * 	src, dst, src_mask, dst_mask are always stored in network byte order.
 * 	flags are stored in host byte order (of course).
 * 	Port numbers are stored in HOST byte order.
 */
#अगर_अघोषित _IP6_TABLES_H
#घोषणा _IP6_TABLES_H

#समावेश <linux/अगर.h>
#समावेश <linux/in6.h>
#समावेश <linux/init.h>
#समावेश <linux/ipv6.h>
#समावेश <linux/skbuff.h>
#समावेश <uapi/linux/netfilter_ipv6/ip6_tables.h>

बाह्य व्योम *ip6t_alloc_initial_table(स्थिर काष्ठा xt_table *);

पूर्णांक ip6t_रेजिस्टर_table(काष्ठा net *net, स्थिर काष्ठा xt_table *table,
			स्थिर काष्ठा ip6t_replace *repl,
			स्थिर काष्ठा nf_hook_ops *ops);
व्योम ip6t_unरेजिस्टर_table_pre_निकास(काष्ठा net *net, स्थिर अक्षर *name);
व्योम ip6t_unरेजिस्टर_table_निकास(काष्ठा net *net, स्थिर अक्षर *name);
बाह्य अचिन्हित पूर्णांक ip6t_करो_table(काष्ठा sk_buff *skb,
				  स्थिर काष्ठा nf_hook_state *state,
				  काष्ठा xt_table *table);

#अगर_घोषित CONFIG_NETFILTER_XTABLES_COMPAT
#समावेश <net/compat.h>

काष्ठा compat_ip6t_entry अणु
	काष्ठा ip6t_ip6 ipv6;
	compat_uपूर्णांक_t nfcache;
	__u16 target_offset;
	__u16 next_offset;
	compat_uपूर्णांक_t comefrom;
	काष्ठा compat_xt_counters counters;
	अचिन्हित अक्षर elems[];
पूर्ण;

अटल अंतरभूत काष्ठा xt_entry_target *
compat_ip6t_get_target(काष्ठा compat_ip6t_entry *e)
अणु
	वापस (व्योम *)e + e->target_offset;
पूर्ण

#पूर्ण_अगर /* CONFIG_COMPAT */
#पूर्ण_अगर /* _IP6_TABLES_H */
