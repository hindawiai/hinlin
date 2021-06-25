<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
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

#अगर_अघोषित _UAPI_IP6_TABLES_H
#घोषणा _UAPI_IP6_TABLES_H

#समावेश <linux/types.h>
#समावेश <linux/compiler.h>
#समावेश <linux/अगर.h>
#समावेश <linux/netfilter_ipv6.h>

#समावेश <linux/netfilter/x_tables.h>

#अगर_अघोषित __KERNEL__
#घोषणा IP6T_FUNCTION_MAXNAMELEN XT_FUNCTION_MAXNAMELEN
#घोषणा IP6T_TABLE_MAXNAMELEN XT_TABLE_MAXNAMELEN
#घोषणा ip6t_match xt_match
#घोषणा ip6t_target xt_target
#घोषणा ip6t_table xt_table
#घोषणा ip6t_get_revision xt_get_revision
#घोषणा ip6t_entry_match xt_entry_match
#घोषणा ip6t_entry_target xt_entry_target
#घोषणा ip6t_standard_target xt_standard_target
#घोषणा ip6t_error_target xt_error_target
#घोषणा ip6t_counters xt_counters
#घोषणा IP6T_CONTINUE XT_CONTINUE
#घोषणा IP6T_RETURN XT_RETURN

/* Pre-iptables-1.4.0 */
#समावेश <linux/netfilter/xt_tcpudp.h>
#घोषणा ip6t_tcp xt_tcp
#घोषणा ip6t_udp xt_udp
#घोषणा IP6T_TCP_INV_SRCPT	XT_TCP_INV_SRCPT
#घोषणा IP6T_TCP_INV_DSTPT	XT_TCP_INV_DSTPT
#घोषणा IP6T_TCP_INV_FLAGS	XT_TCP_INV_FLAGS
#घोषणा IP6T_TCP_INV_OPTION	XT_TCP_INV_OPTION
#घोषणा IP6T_TCP_INV_MASK	XT_TCP_INV_MASK
#घोषणा IP6T_UDP_INV_SRCPT	XT_UDP_INV_SRCPT
#घोषणा IP6T_UDP_INV_DSTPT	XT_UDP_INV_DSTPT
#घोषणा IP6T_UDP_INV_MASK	XT_UDP_INV_MASK

#घोषणा ip6t_counters_info xt_counters_info
#घोषणा IP6T_STANDARD_TARGET XT_STANDARD_TARGET
#घोषणा IP6T_ERROR_TARGET XT_ERROR_TARGET
#घोषणा IP6T_MATCH_ITERATE(e, fn, args...) \
	XT_MATCH_ITERATE(काष्ठा ip6t_entry, e, fn, ## args)
#घोषणा IP6T_ENTRY_ITERATE(entries, size, fn, args...) \
	XT_ENTRY_ITERATE(काष्ठा ip6t_entry, entries, size, fn, ## args)
#पूर्ण_अगर

/* Yes, Virginia, you have to zero the padding. */
काष्ठा ip6t_ip6 अणु
	/* Source and destination IP6 addr */
	काष्ठा in6_addr src, dst;		
	/* Mask क्रम src and dest IP6 addr */
	काष्ठा in6_addr smsk, dmsk;
	अक्षर inअगरace[IFNAMSIZ], outअगरace[IFNAMSIZ];
	अचिन्हित अक्षर inअगरace_mask[IFNAMSIZ], outअगरace_mask[IFNAMSIZ];

	/* Upper protocol number
	 * - The allowed value is 0 (any) or protocol number of last parsable
	 *   header, which is 50 (ESP), 59 (No Next Header), 135 (MH), or
	 *   the non IPv6 extension headers.
	 * - The protocol numbers of IPv6 extension headers except of ESP and
	 *   MH करो not match any packets.
	 * - You also need to set IP6T_FLAGS_PROTO to "flags" to check protocol.
	 */
	__u16 proto;
	/* TOS to match अगरf flags & IP6T_F_TOS */
	__u8 tos;

	/* Flags word */
	__u8 flags;
	/* Inverse flags */
	__u8 invflags;
पूर्ण;

/* Values क्रम "flag" field in काष्ठा ip6t_ip6 (general ip6 काष्ठाure). */
#घोषणा IP6T_F_PROTO		0x01	/* Set अगर rule cares about upper 
					   protocols */
#घोषणा IP6T_F_TOS		0x02	/* Match the TOS. */
#घोषणा IP6T_F_GOTO		0x04	/* Set अगर jump is a जाओ */
#घोषणा IP6T_F_MASK		0x07	/* All possible flag bits mask. */

/* Values क्रम "inv" field in काष्ठा ip6t_ip6. */
#घोषणा IP6T_INV_VIA_IN		0x01	/* Invert the sense of IN IFACE. */
#घोषणा IP6T_INV_VIA_OUT		0x02	/* Invert the sense of OUT IFACE */
#घोषणा IP6T_INV_TOS		0x04	/* Invert the sense of TOS. */
#घोषणा IP6T_INV_SRCIP		0x08	/* Invert the sense of SRC IP. */
#घोषणा IP6T_INV_DSTIP		0x10	/* Invert the sense of DST OP. */
#घोषणा IP6T_INV_FRAG		0x20	/* Invert the sense of FRAG. */
#घोषणा IP6T_INV_PROTO		XT_INV_PROTO
#घोषणा IP6T_INV_MASK		0x7F	/* All possible flag bits mask. */

/* This काष्ठाure defines each of the firewall rules.  Consists of 3
   parts which are 1) general IP header stuff 2) match specअगरic
   stuff 3) the target to perक्रमm अगर the rule matches */
काष्ठा ip6t_entry अणु
	काष्ठा ip6t_ip6 ipv6;

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

/* Standard entry */
काष्ठा ip6t_standard अणु
	काष्ठा ip6t_entry entry;
	काष्ठा xt_standard_target target;
पूर्ण;

काष्ठा ip6t_error अणु
	काष्ठा ip6t_entry entry;
	काष्ठा xt_error_target target;
पूर्ण;

#घोषणा IP6T_ENTRY_INIT(__size)						       \
अणु									       \
	.target_offset	= माप(काष्ठा ip6t_entry),			       \
	.next_offset	= (__size),					       \
पूर्ण

#घोषणा IP6T_STANDARD_INIT(__verdict)					       \
अणु									       \
	.entry		= IP6T_ENTRY_INIT(माप(काष्ठा ip6t_standard)),       \
	.target		= XT_TARGET_INIT(XT_STANDARD_TARGET,		       \
					 माप(काष्ठा xt_standard_target)),   \
	.target.verdict	= -(__verdict) - 1,				       \
पूर्ण

#घोषणा IP6T_ERROR_INIT							       \
अणु									       \
	.entry		= IP6T_ENTRY_INIT(माप(काष्ठा ip6t_error)),	       \
	.target		= XT_TARGET_INIT(XT_ERROR_TARGET,		       \
					 माप(काष्ठा xt_error_target)),      \
	.target.errorname = "ERROR",					       \
पूर्ण

/*
 * New IP firewall options क्रम [gs]etsockopt at the RAW IP level.
 * Unlike BSD Linux inherits IP options so you करोn't have to use
 * a raw socket क्रम this. Instead we check rights in the calls.
 *
 * ATTENTION: check linux/in6.h beक्रमe adding new number here.
 */
#घोषणा IP6T_BASE_CTL			64

#घोषणा IP6T_SO_SET_REPLACE		(IP6T_BASE_CTL)
#घोषणा IP6T_SO_SET_ADD_COUNTERS	(IP6T_BASE_CTL + 1)
#घोषणा IP6T_SO_SET_MAX			IP6T_SO_SET_ADD_COUNTERS

#घोषणा IP6T_SO_GET_INFO		(IP6T_BASE_CTL)
#घोषणा IP6T_SO_GET_ENTRIES		(IP6T_BASE_CTL + 1)
#घोषणा IP6T_SO_GET_REVISION_MATCH	(IP6T_BASE_CTL + 4)
#घोषणा IP6T_SO_GET_REVISION_TARGET	(IP6T_BASE_CTL + 5)
#घोषणा IP6T_SO_GET_MAX			IP6T_SO_GET_REVISION_TARGET

/* obtain original address अगर REसूचीECT'd connection */
#घोषणा IP6T_SO_ORIGINAL_DST            80

/* ICMP matching stuff */
काष्ठा ip6t_icmp अणु
	__u8 type;				/* type to match */
	__u8 code[2];				/* range of code */
	__u8 invflags;				/* Inverse flags */
पूर्ण;

/* Values क्रम "inv" field क्रम काष्ठा ipt_icmp. */
#घोषणा IP6T_ICMP_INV	0x01	/* Invert the sense of type/code test */

/* The argument to IP6T_SO_GET_INFO */
काष्ठा ip6t_getinfo अणु
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

/* The argument to IP6T_SO_SET_REPLACE. */
काष्ठा ip6t_replace अणु
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
	काष्ठा ip6t_entry entries[0];
पूर्ण;

/* The argument to IP6T_SO_GET_ENTRIES. */
काष्ठा ip6t_get_entries अणु
	/* Which table: user fills this in. */
	अक्षर name[XT_TABLE_MAXNAMELEN];

	/* User fills this in: total entry size. */
	अचिन्हित पूर्णांक size;

	/* The entries. */
	काष्ठा ip6t_entry entrytable[0];
पूर्ण;

/* Helper functions */
अटल __अंतरभूत__ काष्ठा xt_entry_target *
ip6t_get_target(काष्ठा ip6t_entry *e)
अणु
	वापस (काष्ठा xt_entry_target *)((अक्षर *)e + e->target_offset);
पूर्ण

/*
 *	Main firewall chains definitions and global var's definitions.
 */

#पूर्ण_अगर /* _UAPI_IP6_TABLES_H */
