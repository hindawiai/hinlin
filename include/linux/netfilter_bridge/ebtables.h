<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *  ebtables
 *
 *	Authors:
 *	Bart De Schuymer		<bdschuym@panकरोra.be>
 *
 *  ebtables.c,v 2.0, April, 2002
 *
 *  This code is strongly inspired by the iptables code which is
 *  Copyright (C) 1999 Paul `Rusty' Russell & Michael J. Neuling
 */
#अगर_अघोषित __LINUX_BRIDGE_EFF_H
#घोषणा __LINUX_BRIDGE_EFF_H

#समावेश <linux/अगर.h>
#समावेश <linux/अगर_ether.h>
#समावेश <uapi/linux/netfilter_bridge/ebtables.h>

काष्ठा ebt_match अणु
	काष्ठा list_head list;
	स्थिर अक्षर name[EBT_FUNCTION_MAXNAMELEN];
	bool (*match)(स्थिर काष्ठा sk_buff *skb, स्थिर काष्ठा net_device *in,
		स्थिर काष्ठा net_device *out, स्थिर काष्ठा xt_match *match,
		स्थिर व्योम *matchinfo, पूर्णांक offset, अचिन्हित पूर्णांक protoff,
		bool *hotdrop);
	bool (*checkentry)(स्थिर अक्षर *table, स्थिर व्योम *entry,
		स्थिर काष्ठा xt_match *match, व्योम *matchinfo,
		अचिन्हित पूर्णांक hook_mask);
	व्योम (*destroy)(स्थिर काष्ठा xt_match *match, व्योम *matchinfo);
	अचिन्हित पूर्णांक matchsize;
	u_पूर्णांक8_t revision;
	u_पूर्णांक8_t family;
	काष्ठा module *me;
पूर्ण;

काष्ठा ebt_watcher अणु
	काष्ठा list_head list;
	स्थिर अक्षर name[EBT_FUNCTION_MAXNAMELEN];
	अचिन्हित पूर्णांक (*target)(काष्ठा sk_buff *skb,
		स्थिर काष्ठा net_device *in, स्थिर काष्ठा net_device *out,
		अचिन्हित पूर्णांक hook_num, स्थिर काष्ठा xt_target *target,
		स्थिर व्योम *targinfo);
	bool (*checkentry)(स्थिर अक्षर *table, स्थिर व्योम *entry,
		स्थिर काष्ठा xt_target *target, व्योम *targinfo,
		अचिन्हित पूर्णांक hook_mask);
	व्योम (*destroy)(स्थिर काष्ठा xt_target *target, व्योम *targinfo);
	अचिन्हित पूर्णांक tarमाला_लोize;
	u_पूर्णांक8_t revision;
	u_पूर्णांक8_t family;
	काष्ठा module *me;
पूर्ण;

काष्ठा ebt_target अणु
	काष्ठा list_head list;
	स्थिर अक्षर name[EBT_FUNCTION_MAXNAMELEN];
	/* वापसs one of the standard EBT_* verdicts */
	अचिन्हित पूर्णांक (*target)(काष्ठा sk_buff *skb,
		स्थिर काष्ठा net_device *in, स्थिर काष्ठा net_device *out,
		अचिन्हित पूर्णांक hook_num, स्थिर काष्ठा xt_target *target,
		स्थिर व्योम *targinfo);
	bool (*checkentry)(स्थिर अक्षर *table, स्थिर व्योम *entry,
		स्थिर काष्ठा xt_target *target, व्योम *targinfo,
		अचिन्हित पूर्णांक hook_mask);
	व्योम (*destroy)(स्थिर काष्ठा xt_target *target, व्योम *targinfo);
	अचिन्हित पूर्णांक tarमाला_लोize;
	u_पूर्णांक8_t revision;
	u_पूर्णांक8_t family;
	काष्ठा module *me;
पूर्ण;

/* used क्रम jumping from and पूर्णांकo user defined chains (udc) */
काष्ठा ebt_chainstack अणु
	काष्ठा ebt_entries *chaininfo; /* poपूर्णांकer to chain data */
	काष्ठा ebt_entry *e; /* poपूर्णांकer to entry data */
	अचिन्हित पूर्णांक n; /* n'th entry */
पूर्ण;

काष्ठा ebt_table_info अणु
	/* total size of the entries */
	अचिन्हित पूर्णांक entries_size;
	अचिन्हित पूर्णांक nentries;
	/* poपूर्णांकers to the start of the chains */
	काष्ठा ebt_entries *hook_entry[NF_BR_NUMHOOKS];
	/* room to मुख्यtain the stack used क्रम jumping from and पूर्णांकo udc */
	काष्ठा ebt_chainstack **chainstack;
	अक्षर *entries;
	काष्ठा ebt_counter counters[] ____cacheline_aligned;
पूर्ण;

काष्ठा ebt_table अणु
	काष्ठा list_head list;
	अक्षर name[EBT_TABLE_MAXNAMELEN];
	काष्ठा ebt_replace_kernel *table;
	अचिन्हित पूर्णांक valid_hooks;
	rwlock_t lock;
	/* e.g. could be the table explicitly only allows certain
	 * matches, tarमाला_लो, ... 0 == let it in */
	पूर्णांक (*check)(स्थिर काष्ठा ebt_table_info *info,
	   अचिन्हित पूर्णांक valid_hooks);
	/* the data used by the kernel */
	काष्ठा ebt_table_info *निजी;
	काष्ठा nf_hook_ops *ops;
	काष्ठा module *me;
पूर्ण;

#घोषणा EBT_ALIGN(s) (((s) + (__alignof__(काष्ठा _xt_align)-1)) & \
		     ~(__alignof__(काष्ठा _xt_align)-1))

बाह्य पूर्णांक ebt_रेजिस्टर_table(काष्ठा net *net,
			      स्थिर काष्ठा ebt_table *table,
			      स्थिर काष्ठा nf_hook_ops *ops);
बाह्य व्योम ebt_unरेजिस्टर_table(काष्ठा net *net, स्थिर अक्षर *tablename);
व्योम ebt_unरेजिस्टर_table_pre_निकास(काष्ठा net *net, स्थिर अक्षर *tablename);
बाह्य अचिन्हित पूर्णांक ebt_करो_table(काष्ठा sk_buff *skb,
				 स्थिर काष्ठा nf_hook_state *state,
				 काष्ठा ebt_table *table);

/* True अगर the hook mask denotes that the rule is in a base chain,
 * used in the check() functions */
#घोषणा BASE_CHAIN (par->hook_mask & (1 << NF_BR_NUMHOOKS))
/* Clear the bit in the hook mask that tells अगर the rule is on a base chain */
#घोषणा CLEAR_BASE_CHAIN_BIT (par->hook_mask &= ~(1 << NF_BR_NUMHOOKS))

अटल अंतरभूत bool ebt_invalid_target(पूर्णांक target)
अणु
	वापस (target < -NUM_STANDARD_TARGETS || target >= 0);
पूर्ण

#पूर्ण_अगर
