<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * 	Format of an ARP firewall descriptor
 *
 * 	src, tgt, src_mask, tgt_mask, arpop, arpop_mask are always stored in
 *	network byte order.
 * 	flags are stored in host byte order (of course).
 */

#अगर_अघोषित _UAPI_ARPTABLES_H
#घोषणा _UAPI_ARPTABLES_H

#समावेश <linux/types.h>
#समावेश <linux/compiler.h>
#समावेश <linux/अगर.h>
#समावेश <linux/netfilter_arp.h>

#समावेश <linux/netfilter/x_tables.h>

#अगर_अघोषित __KERNEL__
#घोषणा ARPT_FUNCTION_MAXNAMELEN XT_FUNCTION_MAXNAMELEN
#घोषणा ARPT_TABLE_MAXNAMELEN XT_TABLE_MAXNAMELEN
#घोषणा arpt_entry_target xt_entry_target
#घोषणा arpt_standard_target xt_standard_target
#घोषणा arpt_error_target xt_error_target
#घोषणा ARPT_CONTINUE XT_CONTINUE
#घोषणा ARPT_RETURN XT_RETURN
#घोषणा arpt_counters_info xt_counters_info
#घोषणा arpt_counters xt_counters
#घोषणा ARPT_STANDARD_TARGET XT_STANDARD_TARGET
#घोषणा ARPT_ERROR_TARGET XT_ERROR_TARGET
#घोषणा ARPT_ENTRY_ITERATE(entries, size, fn, args...) \
	XT_ENTRY_ITERATE(काष्ठा arpt_entry, entries, size, fn, ## args)
#पूर्ण_अगर

#घोषणा ARPT_DEV_ADDR_LEN_MAX 16

काष्ठा arpt_devaddr_info अणु
	अक्षर addr[ARPT_DEV_ADDR_LEN_MAX];
	अक्षर mask[ARPT_DEV_ADDR_LEN_MAX];
पूर्ण;

/* Yes, Virginia, you have to zero the padding. */
काष्ठा arpt_arp अणु
	/* Source and target IP addr */
	काष्ठा in_addr src, tgt;
	/* Mask क्रम src and target IP addr */
	काष्ठा in_addr smsk, पंचांगsk;

	/* Device hw address length, src+target device addresses */
	__u8 arhln, arhln_mask;
	काष्ठा arpt_devaddr_info src_devaddr;
	काष्ठा arpt_devaddr_info tgt_devaddr;

	/* ARP operation code. */
	__be16 arpop, arpop_mask;

	/* ARP hardware address and protocol address क्रमmat. */
	__be16 arhrd, arhrd_mask;
	__be16 arpro, arpro_mask;

	/* The protocol address length is only accepted अगर it is 4
	 * so there is no use in offering a way to करो filtering on it.
	 */

	अक्षर inअगरace[IFNAMSIZ], outअगरace[IFNAMSIZ];
	अचिन्हित अक्षर inअगरace_mask[IFNAMSIZ], outअगरace_mask[IFNAMSIZ];

	/* Flags word */
	__u8 flags;
	/* Inverse flags */
	__u16 invflags;
पूर्ण;

/* Values क्रम "flag" field in काष्ठा arpt_ip (general arp काष्ठाure).
 * No flags defined yet.
 */
#घोषणा ARPT_F_MASK		0x00	/* All possible flag bits mask. */

/* Values क्रम "inv" field in काष्ठा arpt_arp. */
#घोषणा ARPT_INV_VIA_IN		0x0001	/* Invert the sense of IN IFACE. */
#घोषणा ARPT_INV_VIA_OUT	0x0002	/* Invert the sense of OUT IFACE */
#घोषणा ARPT_INV_SRCIP		0x0004	/* Invert the sense of SRC IP. */
#घोषणा ARPT_INV_TGTIP		0x0008	/* Invert the sense of TGT IP. */
#घोषणा ARPT_INV_SRCDEVADDR	0x0010	/* Invert the sense of SRC DEV ADDR. */
#घोषणा ARPT_INV_TGTDEVADDR	0x0020	/* Invert the sense of TGT DEV ADDR. */
#घोषणा ARPT_INV_ARPOP		0x0040	/* Invert the sense of ARP OP. */
#घोषणा ARPT_INV_ARPHRD		0x0080	/* Invert the sense of ARP HRD. */
#घोषणा ARPT_INV_ARPPRO		0x0100	/* Invert the sense of ARP PRO. */
#घोषणा ARPT_INV_ARPHLN		0x0200	/* Invert the sense of ARP HLN. */
#घोषणा ARPT_INV_MASK		0x03FF	/* All possible flag bits mask. */

/* This काष्ठाure defines each of the firewall rules.  Consists of 3
   parts which are 1) general ARP header stuff 2) match specअगरic
   stuff 3) the target to perक्रमm अगर the rule matches */
काष्ठा arpt_entry
अणु
	काष्ठा arpt_arp arp;

	/* Size of arpt_entry + matches */
	__u16 target_offset;
	/* Size of arpt_entry + matches + target */
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
#घोषणा ARPT_BASE_CTL		96

#घोषणा ARPT_SO_SET_REPLACE		(ARPT_BASE_CTL)
#घोषणा ARPT_SO_SET_ADD_COUNTERS	(ARPT_BASE_CTL + 1)
#घोषणा ARPT_SO_SET_MAX			ARPT_SO_SET_ADD_COUNTERS

#घोषणा ARPT_SO_GET_INFO		(ARPT_BASE_CTL)
#घोषणा ARPT_SO_GET_ENTRIES		(ARPT_BASE_CTL + 1)
/* #घोषणा ARPT_SO_GET_REVISION_MATCH	(APRT_BASE_CTL + 2) */
#घोषणा ARPT_SO_GET_REVISION_TARGET	(ARPT_BASE_CTL + 3)
#घोषणा ARPT_SO_GET_MAX			(ARPT_SO_GET_REVISION_TARGET)

/* The argument to ARPT_SO_GET_INFO */
काष्ठा arpt_getinfo अणु
	/* Which table: caller fills this in. */
	अक्षर name[XT_TABLE_MAXNAMELEN];

	/* Kernel fills these in. */
	/* Which hook entry poपूर्णांकs are valid: biपंचांगask */
	अचिन्हित पूर्णांक valid_hooks;

	/* Hook entry poपूर्णांकs: one per netfilter hook. */
	अचिन्हित पूर्णांक hook_entry[NF_ARP_NUMHOOKS];

	/* Underflow poपूर्णांकs. */
	अचिन्हित पूर्णांक underflow[NF_ARP_NUMHOOKS];

	/* Number of entries */
	अचिन्हित पूर्णांक num_entries;

	/* Size of entries. */
	अचिन्हित पूर्णांक size;
पूर्ण;

/* The argument to ARPT_SO_SET_REPLACE. */
काष्ठा arpt_replace अणु
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
	अचिन्हित पूर्णांक hook_entry[NF_ARP_NUMHOOKS];

	/* Underflow poपूर्णांकs. */
	अचिन्हित पूर्णांक underflow[NF_ARP_NUMHOOKS];

	/* Inक्रमmation about old entries: */
	/* Number of counters (must be equal to current number of entries). */
	अचिन्हित पूर्णांक num_counters;
	/* The old entries' counters. */
	काष्ठा xt_counters __user *counters;

	/* The entries (hang off end: not really an array). */
	काष्ठा arpt_entry entries[0];
पूर्ण;

/* The argument to ARPT_SO_GET_ENTRIES. */
काष्ठा arpt_get_entries अणु
	/* Which table: user fills this in. */
	अक्षर name[XT_TABLE_MAXNAMELEN];

	/* User fills this in: total entry size. */
	अचिन्हित पूर्णांक size;

	/* The entries. */
	काष्ठा arpt_entry entrytable[0];
पूर्ण;

/* Helper functions */
अटल __अंतरभूत__ काष्ठा xt_entry_target *arpt_get_target(काष्ठा arpt_entry *e)
अणु
	वापस (काष्ठा xt_entry_target *)((अक्षर *)e + e->target_offset);
पूर्ण

/*
 *	Main firewall chains definitions and global var's definitions.
 */
#पूर्ण_अगर /* _UAPI_ARPTABLES_H */
