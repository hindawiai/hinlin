<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * 	Format of an ARP firewall descriptor
 *
 * 	src, tgt, src_mask, tgt_mask, arpop, arpop_mask are always stored in
 *	network byte order.
 * 	flags are stored in host byte order (of course).
 */
#अगर_अघोषित _ARPTABLES_H
#घोषणा _ARPTABLES_H

#समावेश <linux/अगर.h>
#समावेश <linux/in.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/skbuff.h>
#समावेश <uapi/linux/netfilter_arp/arp_tables.h>

/* Standard entry. */
काष्ठा arpt_standard अणु
	काष्ठा arpt_entry entry;
	काष्ठा xt_standard_target target;
पूर्ण;

काष्ठा arpt_error अणु
	काष्ठा arpt_entry entry;
	काष्ठा xt_error_target target;
पूर्ण;

#घोषणा ARPT_ENTRY_INIT(__size)						       \
अणु									       \
	.target_offset	= माप(काष्ठा arpt_entry),			       \
	.next_offset	= (__size),					       \
पूर्ण

#घोषणा ARPT_STANDARD_INIT(__verdict)					       \
अणु									       \
	.entry		= ARPT_ENTRY_INIT(माप(काष्ठा arpt_standard)),       \
	.target		= XT_TARGET_INIT(XT_STANDARD_TARGET,		       \
					 माप(काष्ठा xt_standard_target)), \
	.target.verdict	= -(__verdict) - 1,				       \
पूर्ण

#घोषणा ARPT_ERROR_INIT							       \
अणु									       \
	.entry		= ARPT_ENTRY_INIT(माप(काष्ठा arpt_error)),	       \
	.target		= XT_TARGET_INIT(XT_ERROR_TARGET,		       \
					 माप(काष्ठा xt_error_target)),      \
	.target.errorname = "ERROR",					       \
पूर्ण

बाह्य व्योम *arpt_alloc_initial_table(स्थिर काष्ठा xt_table *);
पूर्णांक arpt_रेजिस्टर_table(काष्ठा net *net, स्थिर काष्ठा xt_table *table,
			स्थिर काष्ठा arpt_replace *repl,
			स्थिर काष्ठा nf_hook_ops *ops);
व्योम arpt_unरेजिस्टर_table(काष्ठा net *net, स्थिर अक्षर *name);
व्योम arpt_unरेजिस्टर_table_pre_निकास(काष्ठा net *net, स्थिर अक्षर *name);
बाह्य अचिन्हित पूर्णांक arpt_करो_table(काष्ठा sk_buff *skb,
				  स्थिर काष्ठा nf_hook_state *state,
				  काष्ठा xt_table *table);

#अगर_घोषित CONFIG_NETFILTER_XTABLES_COMPAT
#समावेश <net/compat.h>

काष्ठा compat_arpt_entry अणु
	काष्ठा arpt_arp arp;
	__u16 target_offset;
	__u16 next_offset;
	compat_uपूर्णांक_t comefrom;
	काष्ठा compat_xt_counters counters;
	अचिन्हित अक्षर elems[];
पूर्ण;

अटल अंतरभूत काष्ठा xt_entry_target *
compat_arpt_get_target(काष्ठा compat_arpt_entry *e)
अणु
	वापस (व्योम *)e + e->target_offset;
पूर्ण

#पूर्ण_अगर /* CONFIG_COMPAT */
#पूर्ण_अगर /* _ARPTABLES_H */
