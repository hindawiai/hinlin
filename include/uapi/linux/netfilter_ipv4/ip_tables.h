<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
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

#अगर_अघोषित _UAPI_IPTABLES_H
#घोषणा _UAPI_IPTABLES_H

#समावेश <linux/types.h>
#समावेश <linux/compiler.h>
#समावेश <linux/अगर.h>
#समावेश <linux/netfilter_ipv4.h>

#समावेश <linux/netfilter/x_tables.h>

#अगर_अघोषित __KERNEL__
#घोषणा IPT_FUNCTION_MAXNAMELEN XT_FUNCTION_MAXNAMELEN
#घोषणा IPT_TABLE_MAXNAMELEN XT_TABLE_MAXNAMELEN
#घोषणा ipt_match xt_match
#घोषणा ipt_target xt_target
#घोषणा ipt_table xt_table
#घोषणा ipt_get_revision xt_get_revision
#घोषणा ipt_entry_match xt_entry_match
#घोषणा ipt_entry_target xt_entry_target
#घोषणा ipt_standard_target xt_standard_target
#घोषणा ipt_error_target xt_error_target
#घोषणा ipt_counters xt_counters
#घोषणा IPT_CONTINUE XT_CONTINUE
#घोषणा IPT_RETURN XT_RETURN

/* This group is older than old (iptables < v1.4.0-rc1~89) */
#समावेश <linux/netfilter/xt_tcpudp.h>
#घोषणा ipt_udp xt_udp
#घोषणा ipt_tcp xt_tcp
#घोषणा IPT_TCP_INV_SRCPT	XT_TCP_INV_SRCPT
#घोषणा IPT_TCP_INV_DSTPT	XT_TCP_INV_DSTPT
#घोषणा IPT_TCP_INV_FLAGS	XT_TCP_INV_FLAGS
#घोषणा IPT_TCP_INV_OPTION	XT_TCP_INV_OPTION
#घोषणा IPT_TCP_INV_MASK	XT_TCP_INV_MASK
#घोषणा IPT_UDP_INV_SRCPT	XT_UDP_INV_SRCPT
#घोषणा IPT_UDP_INV_DSTPT	XT_UDP_INV_DSTPT
#घोषणा IPT_UDP_INV_MASK	XT_UDP_INV_MASK

/* The argument to IPT_SO_ADD_COUNTERS. */
#घोषणा ipt_counters_info xt_counters_info
/* Standard वापस verdict, or करो jump. */
#घोषणा IPT_STANDARD_TARGET XT_STANDARD_TARGET
/* Error verdict. */
#घोषणा IPT_ERROR_TARGET XT_ERROR_TARGET

/* fn वापसs 0 to जारी iteration */
#घोषणा IPT_MATCH_ITERATE(e, fn, args...) \
	XT_MATCH_ITERATE(काष्ठा ipt_entry, e, fn, ## args)

/* fn वापसs 0 to जारी iteration */
#घोषणा IPT_ENTRY_ITERATE(entries, size, fn, args...) \
	XT_ENTRY_ITERATE(काष्ठा ipt_entry, entries, size, fn, ## args)
#पूर्ण_अगर

/* Yes, Virginia, you have to zero the padding. */
काष्ठा ipt_ip अणु
	/* Source and destination IP addr */
	काष्ठा in_addr src, dst;
	/* Mask क्रम src and dest IP addr */
	काष्ठा in_addr smsk, dmsk;
	अक्षर inअगरace[IFNAMSIZ], outअगरace[IFNAMSIZ];
	अचिन्हित अक्षर inअगरace_mask[IFNAMSIZ], outअगरace_mask[IFNAMSIZ];

	/* Protocol, 0 = ANY */
	__u16 proto;

	/* Flags word */
	__u8 flags;
	/* Inverse flags */
	__u8 invflags;
पूर्ण;

/* Values क्रम "flag" field in काष्ठा ipt_ip (general ip काष्ठाure). */
#घोषणा IPT_F_FRAG		0x01	/* Set अगर rule is a fragment rule */
#घोषणा IPT_F_GOTO		0x02	/* Set अगर jump is a जाओ */
#घोषणा IPT_F_MASK		0x03	/* All possible flag bits mask. */

/* Values क्रम "inv" field in काष्ठा ipt_ip. */
#घोषणा IPT_INV_VIA_IN		0x01	/* Invert the sense of IN IFACE. */
#घोषणा IPT_INV_VIA_OUT		0x02	/* Invert the sense of OUT IFACE */
#घोषणा IPT_INV_TOS		0x04	/* Invert the sense of TOS. */
#घोषणा IPT_INV_SRCIP		0x08	/* Invert the sense of SRC IP. */
#घोषणा IPT_INV_DSTIP		0x10	/* Invert the sense of DST OP. */
#घोषणा IPT_INV_FRAG		0x20	/* Invert the sense of FRAG. */
#घोषणा IPT_INV_PROTO		XT_INV_PROTO
#घोषणा IPT_INV_MASK		0x7F	/* All possible flag bits mask. */

/* This काष्ठाure defines each of the firewall rules.  Consists of 3
   parts which are 1) general IP header stuff 2) match specअगरic
   stuff 3) the target to perक्रमm अगर the rule matches */
काष्ठा ipt_entry अणु
	काष्ठा ipt_ip ip;

	/* Mark with fields that we care about. */
	अचिन्हित पूर्णांक nfcache;

	/* Size of ipt_entry + matches */
	__u16 target_offset;
	/* Size of ipt_entry + matches + target */
	__u16 next_offset;

	/* Back poपूर्णांकer */
	अचिन्हित पूर्णांक comefrom;

	/* Packet and byte counters. */
	काष्ठा xt_counters counters;

	/* The matches (अगर any), then the target. */
	अचिन्हित अक्षर elems[0];
पूर्ण;

/*
 * New IP firewall options क्रम [gs]etsockopt at the RAW IP level.
 * Unlike BSD Linux inherits IP options so you करोn't have to use a raw
 * socket क्रम this. Instead we check rights in the calls.
 *
 * ATTENTION: check linux/in.h beक्रमe adding new number here.
 */
#घोषणा IPT_BASE_CTL		64

#घोषणा IPT_SO_SET_REPLACE	(IPT_BASE_CTL)
#घोषणा IPT_SO_SET_ADD_COUNTERS	(IPT_BASE_CTL + 1)
#घोषणा IPT_SO_SET_MAX		IPT_SO_SET_ADD_COUNTERS

#घोषणा IPT_SO_GET_INFO			(IPT_BASE_CTL)
#घोषणा IPT_SO_GET_ENTRIES		(IPT_BASE_CTL + 1)
#घोषणा IPT_SO_GET_REVISION_MATCH	(IPT_BASE_CTL + 2)
#घोषणा IPT_SO_GET_REVISION_TARGET	(IPT_BASE_CTL + 3)
#घोषणा IPT_SO_GET_MAX			IPT_SO_GET_REVISION_TARGET

/* ICMP matching stuff */
काष्ठा ipt_icmp अणु
	__u8 type;				/* type to match */
	__u8 code[2];				/* range of code */
	__u8 invflags;				/* Inverse flags */
पूर्ण;

/* Values क्रम "inv" field क्रम काष्ठा ipt_icmp. */
#घोषणा IPT_ICMP_INV	0x01	/* Invert the sense of type/code test */

/* The argument to IPT_SO_GET_INFO */
काष्ठा ipt_getinfo अणु
	/* Which table: caller fills this in. */
	अक्षर name[XT_TABLE_MAXNAMELEN];

	/* Kernel fills these in. */
	/* Which hook entry poपूर्णांकs are valid: biपंचांगask */
	अचिन्हित पूर्णांक valid_hooks;

	/* Hook entry poपूर्णांकs: one per netfilter hook. */
	अचिन्हित पूर्णांक hook_entry[NF_INET_NUMHOOKS];

	/* Underflow poपूर्णांकs. */
	अचिन्हित पूर्णांक underflow[NF_INET_NUMHOOKS];

	/* Number of entries */
	अचिन्हित पूर्णांक num_entries;

	/* Size of entries. */
	अचिन्हित पूर्णांक size;
पूर्ण;

/* The argument to IPT_SO_SET_REPLACE. */
काष्ठा ipt_replace अणु
	/* Which table. */
	अक्षर name[XT_TABLE_MAXNAMELEN];

	/* Which hook entry poपूर्णांकs are valid: biपंचांगask.  You can't
           change this. */
	अचिन्हित पूर्णांक valid_hooks;

	/* Number of entries */
	अचिन्हित पूर्णांक num_entries;

	/* Total size of new entries */
	अचिन्हित पूर्णांक size;

	/* Hook entry poपूर्णांकs. */
	अचिन्हित पूर्णांक hook_entry[NF_INET_NUMHOOKS];

	/* Underflow poपूर्णांकs. */
	अचिन्हित पूर्णांक underflow[NF_INET_NUMHOOKS];

	/* Inक्रमmation about old entries: */
	/* Number of counters (must be equal to current number of entries). */
	अचिन्हित पूर्णांक num_counters;
	/* The old entries' counters. */
	काष्ठा xt_counters __user *counters;

	/* The entries (hang off end: not really an array). */
	काष्ठा ipt_entry entries[0];
पूर्ण;

/* The argument to IPT_SO_GET_ENTRIES. */
काष्ठा ipt_get_entries अणु
	/* Which table: user fills this in. */
	अक्षर name[XT_TABLE_MAXNAMELEN];

	/* User fills this in: total entry size. */
	अचिन्हित पूर्णांक size;

	/* The entries. */
	काष्ठा ipt_entry entrytable[0];
पूर्ण;

/* Helper functions */
अटल __अंतरभूत__ काष्ठा xt_entry_target *
ipt_get_target(काष्ठा ipt_entry *e)
अणु
	वापस (काष्ठा xt_entry_target *)((अक्षर *)e + e->target_offset);
पूर्ण

/*
 *	Main firewall chains definitions and global var's definitions.
 */
#पूर्ण_अगर /* _UAPI_IPTABLES_H */
