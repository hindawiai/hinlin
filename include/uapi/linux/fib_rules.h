<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित __LINUX_FIB_RULES_H
#घोषणा __LINUX_FIB_RULES_H

#समावेश <linux/types.h>
#समावेश <linux/rtnetlink.h>

/* rule is permanent, and cannot be deleted */
#घोषणा FIB_RULE_PERMANENT	0x00000001
#घोषणा FIB_RULE_INVERT		0x00000002
#घोषणा FIB_RULE_UNRESOLVED	0x00000004
#घोषणा FIB_RULE_IIF_DETACHED	0x00000008
#घोषणा FIB_RULE_DEV_DETACHED	FIB_RULE_IIF_DETACHED
#घोषणा FIB_RULE_OIF_DETACHED	0x00000010

/* try to find source address in routing lookups */
#घोषणा FIB_RULE_FIND_SADDR	0x00010000

काष्ठा fib_rule_hdr अणु
	__u8		family;
	__u8		dst_len;
	__u8		src_len;
	__u8		tos;

	__u8		table;
	__u8		res1;   /* reserved */
	__u8		res2;	/* reserved */
	__u8		action;

	__u32		flags;
पूर्ण;

काष्ठा fib_rule_uid_range अणु
	__u32		start;
	__u32		end;
पूर्ण;

काष्ठा fib_rule_port_range अणु
	__u16		start;
	__u16		end;
पूर्ण;

क्रमागत अणु
	FRA_UNSPEC,
	FRA_DST,	/* destination address */
	FRA_SRC,	/* source address */
	FRA_IIFNAME,	/* पूर्णांकerface name */
#घोषणा FRA_IFNAME	FRA_IIFNAME
	FRA_GOTO,	/* target to jump to (FR_ACT_GOTO) */
	FRA_UNUSED2,
	FRA_PRIORITY,	/* priority/preference */
	FRA_UNUSED3,
	FRA_UNUSED4,
	FRA_UNUSED5,
	FRA_FWMARK,	/* mark */
	FRA_FLOW,	/* flow/class id */
	FRA_TUN_ID,
	FRA_SUPPRESS_IFGROUP,
	FRA_SUPPRESS_PREFIXLEN,
	FRA_TABLE,	/* Extended table id */
	FRA_FWMASK,	/* mask क्रम netfilter mark */
	FRA_OIFNAME,
	FRA_PAD,
	FRA_L3MDEV,	/* iअगर or oअगर is l3mdev जाओ its table */
	FRA_UID_RANGE,	/* UID range */
	FRA_PROTOCOL,   /* Originator of the rule */
	FRA_IP_PROTO,	/* ip proto */
	FRA_SPORT_RANGE, /* sport */
	FRA_DPORT_RANGE, /* dport */
	__FRA_MAX
पूर्ण;

#घोषणा FRA_MAX (__FRA_MAX - 1)

क्रमागत अणु
	FR_ACT_UNSPEC,
	FR_ACT_TO_TBL,		/* Pass to fixed table */
	FR_ACT_GOTO,		/* Jump to another rule */
	FR_ACT_NOP,		/* No operation */
	FR_ACT_RES3,
	FR_ACT_RES4,
	FR_ACT_BLACKHOLE,	/* Drop without notअगरication */
	FR_ACT_UNREACHABLE,	/* Drop with ENETUNREACH */
	FR_ACT_PROHIBIT,	/* Drop with EACCES */
	__FR_ACT_MAX,
पूर्ण;

#घोषणा FR_ACT_MAX (__FR_ACT_MAX - 1)

#पूर्ण_अगर
