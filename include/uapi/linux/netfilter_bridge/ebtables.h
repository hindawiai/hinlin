<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
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

#अगर_अघोषित _UAPI__LINUX_BRIDGE_EFF_H
#घोषणा _UAPI__LINUX_BRIDGE_EFF_H
#समावेश <linux/types.h>
#समावेश <linux/अगर.h>
#समावेश <linux/netfilter_bridge.h>

#घोषणा EBT_TABLE_MAXNAMELEN 32
#घोषणा EBT_CHAIN_MAXNAMELEN EBT_TABLE_MAXNAMELEN
#घोषणा EBT_FUNCTION_MAXNAMELEN EBT_TABLE_MAXNAMELEN
#घोषणा EBT_EXTENSION_MAXNAMELEN 31

/* verdicts >0 are "branches" */
#घोषणा EBT_ACCEPT   -1
#घोषणा EBT_DROP     -2
#घोषणा EBT_CONTINUE -3
#घोषणा EBT_RETURN   -4
#घोषणा NUM_STANDARD_TARGETS   4
/* ebtables target modules store the verdict inside an पूर्णांक. We can
 * reclaim a part of this पूर्णांक क्रम backwards compatible extensions.
 * The 4 lsb are more than enough to store the verdict. */
#घोषणा EBT_VERDICT_BITS 0x0000000F

काष्ठा xt_match;
काष्ठा xt_target;

काष्ठा ebt_counter अणु
	__u64 pcnt;
	__u64 bcnt;
पूर्ण;

काष्ठा ebt_replace अणु
	अक्षर name[EBT_TABLE_MAXNAMELEN];
	अचिन्हित पूर्णांक valid_hooks;
	/* nr of rules in the table */
	अचिन्हित पूर्णांक nentries;
	/* total size of the entries */
	अचिन्हित पूर्णांक entries_size;
	/* start of the chains */
	काष्ठा ebt_entries __user *hook_entry[NF_BR_NUMHOOKS];
	/* nr of counters userspace expects back */
	अचिन्हित पूर्णांक num_counters;
	/* where the kernel will put the old counters */
	काष्ठा ebt_counter __user *counters;
	अक्षर __user *entries;
पूर्ण;

काष्ठा ebt_replace_kernel अणु
	अक्षर name[EBT_TABLE_MAXNAMELEN];
	अचिन्हित पूर्णांक valid_hooks;
	/* nr of rules in the table */
	अचिन्हित पूर्णांक nentries;
	/* total size of the entries */
	अचिन्हित पूर्णांक entries_size;
	/* start of the chains */
	काष्ठा ebt_entries *hook_entry[NF_BR_NUMHOOKS];
	/* nr of counters userspace expects back */
	अचिन्हित पूर्णांक num_counters;
	/* where the kernel will put the old counters */
	काष्ठा ebt_counter *counters;
	अक्षर *entries;
पूर्ण;

काष्ठा ebt_entries अणु
	/* this field is always set to zero
	 * See EBT_ENTRY_OR_ENTRIES.
	 * Must be same size as ebt_entry.biपंचांगask */
	अचिन्हित पूर्णांक distinguisher;
	/* the chain name */
	अक्षर name[EBT_CHAIN_MAXNAMELEN];
	/* counter offset क्रम this chain */
	अचिन्हित पूर्णांक counter_offset;
	/* one standard (accept, drop, वापस) per hook */
	पूर्णांक policy;
	/* nr. of entries */
	अचिन्हित पूर्णांक nentries;
	/* entry list */
	अक्षर data[0] __attribute__ ((aligned (__alignof__(काष्ठा ebt_replace))));
पूर्ण;

/* used क्रम the biपंचांगask of काष्ठा ebt_entry */

/* This is a hack to make a dअगरference between an ebt_entry काष्ठा and an
 * ebt_entries काष्ठा when traversing the entries from start to end.
 * Using this simplअगरies the code a lot, जबतक still being able to use
 * ebt_entries.
 * Contrary, iptables करोesn't use something like ebt_entries and thereक्रमe uses
 * dअगरferent techniques क्रम naming the policy and such. So, iptables करोesn't
 * need a hack like this.
 */
#घोषणा EBT_ENTRY_OR_ENTRIES 0x01
/* these are the normal masks */
#घोषणा EBT_NOPROTO 0x02
#घोषणा EBT_802_3 0x04
#घोषणा EBT_SOURCEMAC 0x08
#घोषणा EBT_DESTMAC 0x10
#घोषणा EBT_F_MASK (EBT_NOPROTO | EBT_802_3 | EBT_SOURCEMAC | EBT_DESTMAC \
   | EBT_ENTRY_OR_ENTRIES)

#घोषणा EBT_IPROTO 0x01
#घोषणा EBT_IIN 0x02
#घोषणा EBT_IOUT 0x04
#घोषणा EBT_ISOURCE 0x8
#घोषणा EBT_IDEST 0x10
#घोषणा EBT_ILOGICALIN 0x20
#घोषणा EBT_ILOGICALOUT 0x40
#घोषणा EBT_INV_MASK (EBT_IPROTO | EBT_IIN | EBT_IOUT | EBT_ILOGICALIN \
   | EBT_ILOGICALOUT | EBT_ISOURCE | EBT_IDEST)

काष्ठा ebt_entry_match अणु
	जोड़ अणु
		काष्ठा अणु
			अक्षर name[EBT_EXTENSION_MAXNAMELEN];
			__u8 revision;
		पूर्ण;
		काष्ठा xt_match *match;
	पूर्ण u;
	/* size of data */
	अचिन्हित पूर्णांक match_size;
	अचिन्हित अक्षर data[0] __attribute__ ((aligned (__alignof__(काष्ठा ebt_replace))));
पूर्ण;

काष्ठा ebt_entry_watcher अणु
	जोड़ अणु
		काष्ठा अणु
			अक्षर name[EBT_EXTENSION_MAXNAMELEN];
			__u8 revision;
		पूर्ण;
		काष्ठा xt_target *watcher;
	पूर्ण u;
	/* size of data */
	अचिन्हित पूर्णांक watcher_size;
	अचिन्हित अक्षर data[0] __attribute__ ((aligned (__alignof__(काष्ठा ebt_replace))));
पूर्ण;

काष्ठा ebt_entry_target अणु
	जोड़ अणु
		काष्ठा अणु
			अक्षर name[EBT_EXTENSION_MAXNAMELEN];
			__u8 revision;
		पूर्ण;
		काष्ठा xt_target *target;
	पूर्ण u;
	/* size of data */
	अचिन्हित पूर्णांक target_size;
	अचिन्हित अक्षर data[0] __attribute__ ((aligned (__alignof__(काष्ठा ebt_replace))));
पूर्ण;

#घोषणा EBT_STANDARD_TARGET "standard"
काष्ठा ebt_standard_target अणु
	काष्ठा ebt_entry_target target;
	पूर्णांक verdict;
पूर्ण;

/* one entry */
काष्ठा ebt_entry अणु
	/* this needs to be the first field */
	अचिन्हित पूर्णांक biपंचांगask;
	अचिन्हित पूर्णांक invflags;
	__be16 ethproto;
	/* the physical in-dev */
	अक्षर in[IFNAMSIZ];
	/* the logical in-dev */
	अक्षर logical_in[IFNAMSIZ];
	/* the physical out-dev */
	अक्षर out[IFNAMSIZ];
	/* the logical out-dev */
	अक्षर logical_out[IFNAMSIZ];
	अचिन्हित अक्षर sourcemac[ETH_ALEN];
	अचिन्हित अक्षर sourcemsk[ETH_ALEN];
	अचिन्हित अक्षर desपंचांगac[ETH_ALEN];
	अचिन्हित अक्षर desपंचांगsk[ETH_ALEN];
	/* माप ebt_entry + matches */
	अचिन्हित पूर्णांक watchers_offset;
	/* माप ebt_entry + matches + watchers */
	अचिन्हित पूर्णांक target_offset;
	/* माप ebt_entry + matches + watchers + target */
	अचिन्हित पूर्णांक next_offset;
	अचिन्हित अक्षर elems[0] __attribute__ ((aligned (__alignof__(काष्ठा ebt_replace))));
पूर्ण;

अटल __अंतरभूत__ काष्ठा ebt_entry_target *
ebt_get_target(काष्ठा ebt_entry *e)
अणु
	वापस (काष्ठा ebt_entry_target *)((अक्षर *)e + e->target_offset);
पूर्ण

/* अणुg,sपूर्णetsockopt numbers */
#घोषणा EBT_BASE_CTL            128

#घोषणा EBT_SO_SET_ENTRIES      (EBT_BASE_CTL)
#घोषणा EBT_SO_SET_COUNTERS     (EBT_SO_SET_ENTRIES+1)
#घोषणा EBT_SO_SET_MAX          (EBT_SO_SET_COUNTERS+1)

#घोषणा EBT_SO_GET_INFO         (EBT_BASE_CTL)
#घोषणा EBT_SO_GET_ENTRIES      (EBT_SO_GET_INFO+1)
#घोषणा EBT_SO_GET_INIT_INFO    (EBT_SO_GET_ENTRIES+1)
#घोषणा EBT_SO_GET_INIT_ENTRIES (EBT_SO_GET_INIT_INFO+1)
#घोषणा EBT_SO_GET_MAX          (EBT_SO_GET_INIT_ENTRIES+1)


/* blatently stolen from ip_tables.h
 * fn वापसs 0 to जारी iteration */
#घोषणा EBT_MATCH_ITERATE(e, fn, args...)                   \
(अणु                                                          \
	अचिन्हित पूर्णांक __i;                                   \
	पूर्णांक __ret = 0;                                      \
	काष्ठा ebt_entry_match *__match;                    \
	                                                    \
	क्रम (__i = माप(काष्ठा ebt_entry);                \
	     __i < (e)->watchers_offset;                    \
	     __i += __match->match_size +                   \
	     माप(काष्ठा ebt_entry_match)) अणु              \
		__match = (व्योम *)(e) + __i;                \
		                                            \
		__ret = fn(__match , ## args);              \
		अगर (__ret != 0)                             \
			अवरोध;                              \
	पूर्ण                                                   \
	अगर (__ret == 0) अणु                                   \
		अगर (__i != (e)->watchers_offset)            \
			__ret = -EINVAL;                    \
	पूर्ण                                                   \
	__ret;                                              \
पूर्ण)

#घोषणा EBT_WATCHER_ITERATE(e, fn, args...)                 \
(अणु                                                          \
	अचिन्हित पूर्णांक __i;                                   \
	पूर्णांक __ret = 0;                                      \
	काष्ठा ebt_entry_watcher *__watcher;                \
	                                                    \
	क्रम (__i = e->watchers_offset;                      \
	     __i < (e)->target_offset;                      \
	     __i += __watcher->watcher_size +               \
	     माप(काष्ठा ebt_entry_watcher)) अणु            \
		__watcher = (व्योम *)(e) + __i;              \
		                                            \
		__ret = fn(__watcher , ## args);            \
		अगर (__ret != 0)                             \
			अवरोध;                              \
	पूर्ण                                                   \
	अगर (__ret == 0) अणु                                   \
		अगर (__i != (e)->target_offset)              \
			__ret = -EINVAL;                    \
	पूर्ण                                                   \
	__ret;                                              \
पूर्ण)

#घोषणा EBT_ENTRY_ITERATE(entries, size, fn, args...)       \
(अणु                                                          \
	अचिन्हित पूर्णांक __i;                                   \
	पूर्णांक __ret = 0;                                      \
	काष्ठा ebt_entry *__entry;                          \
	                                                    \
	क्रम (__i = 0; __i < (size);) अणु                      \
		__entry = (व्योम *)(entries) + __i;          \
		__ret = fn(__entry , ## args);              \
		अगर (__ret != 0)                             \
			अवरोध;                              \
		अगर (__entry->biपंचांगask != 0)                  \
			__i += __entry->next_offset;        \
		अन्यथा                                        \
			__i += माप(काष्ठा ebt_entries);  \
	पूर्ण                                                   \
	अगर (__ret == 0) अणु                                   \
		अगर (__i != (size))                          \
			__ret = -EINVAL;                    \
	पूर्ण                                                   \
	__ret;                                              \
पूर्ण)

#पूर्ण_अगर /* _UAPI__LINUX_BRIDGE_EFF_H */
