<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * 25-Jul-1998 Major changes to allow क्रम ip chain table
 *
 * 3-Jan-2000 Named tables to allow packet selection क्रम dअगरferent uses.
 */

/*
 * 	Format of an IP firewall descriptor
 *
 * 	src, dst, src_mask, dst_mask are always stored in network byte order.
 * 	flags are stored in host byte order (of course).
 * 	Port numbers are stored in HOST byte order.
 */
#अगर_अघोषित _IPTABLES_H
#घोषणा _IPTABLES_H

#समावेश <linux/अगर.h>
#समावेश <linux/in.h>
#समावेश <linux/init.h>
#समावेश <linux/ip.h>
#समावेश <linux/skbuff.h>
#समावेश <uapi/linux/netfilter_ipv4/ip_tables.h>

पूर्णांक ipt_रेजिस्टर_table(काष्ठा net *net, स्थिर काष्ठा xt_table *table,
		       स्थिर काष्ठा ipt_replace *repl,
		       स्थिर काष्ठा nf_hook_ops *ops);

व्योम ipt_unरेजिस्टर_table_pre_निकास(काष्ठा net *net, स्थिर अक्षर *name);
व्योम ipt_unरेजिस्टर_table_निकास(काष्ठा net *net, स्थिर अक्षर *name);

/* Standard entry. */
काष्ठा ipt_standard अणु
	काष्ठा ipt_entry entry;
	काष्ठा xt_standard_target target;
पूर्ण;

काष्ठा ipt_error अणु
	काष्ठा ipt_entry entry;
	काष्ठा xt_error_target target;
पूर्ण;

#घोषणा IPT_ENTRY_INIT(__size)						       \
अणु									       \
	.target_offset	= माप(काष्ठा ipt_entry),			       \
	.next_offset	= (__size),					       \
पूर्ण

#घोषणा IPT_STANDARD_INIT(__verdict)					       \
अणु									       \
	.entry		= IPT_ENTRY_INIT(माप(काष्ठा ipt_standard)),	       \
	.target		= XT_TARGET_INIT(XT_STANDARD_TARGET,		       \
					 माप(काष्ठा xt_standard_target)),   \
	.target.verdict	= -(__verdict) - 1,				       \
पूर्ण

#घोषणा IPT_ERROR_INIT							       \
अणु									       \
	.entry		= IPT_ENTRY_INIT(माप(काष्ठा ipt_error)),	       \
	.target		= XT_TARGET_INIT(XT_ERROR_TARGET,		       \
					 माप(काष्ठा xt_error_target)),      \
	.target.errorname = "ERROR",					       \
पूर्ण

बाह्य व्योम *ipt_alloc_initial_table(स्थिर काष्ठा xt_table *);
बाह्य अचिन्हित पूर्णांक ipt_करो_table(काष्ठा sk_buff *skb,
				 स्थिर काष्ठा nf_hook_state *state,
				 काष्ठा xt_table *table);

#अगर_घोषित CONFIG_NETFILTER_XTABLES_COMPAT
#समावेश <net/compat.h>

काष्ठा compat_ipt_entry अणु
	काष्ठा ipt_ip ip;
	compat_uपूर्णांक_t nfcache;
	__u16 target_offset;
	__u16 next_offset;
	compat_uपूर्णांक_t comefrom;
	काष्ठा compat_xt_counters counters;
	अचिन्हित अक्षर elems[];
पूर्ण;

/* Helper functions */
अटल अंतरभूत काष्ठा xt_entry_target *
compat_ipt_get_target(काष्ठा compat_ipt_entry *e)
अणु
	वापस (व्योम *)e + e->target_offset;
पूर्ण

#पूर्ण_अगर /* CONFIG_COMPAT */
#पूर्ण_अगर /* _IPTABLES_H */
