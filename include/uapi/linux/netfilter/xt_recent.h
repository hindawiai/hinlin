<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _LINUX_NETFILTER_XT_RECENT_H
#घोषणा _LINUX_NETFILTER_XT_RECENT_H 1

#समावेश <linux/types.h>
#समावेश <linux/netfilter.h>

क्रमागत अणु
	XT_RECENT_CHECK    = 1 << 0,
	XT_RECENT_SET      = 1 << 1,
	XT_RECENT_UPDATE   = 1 << 2,
	XT_RECENT_REMOVE   = 1 << 3,
	XT_RECENT_TTL      = 1 << 4,
	XT_RECENT_REAP     = 1 << 5,

	XT_RECENT_SOURCE   = 0,
	XT_RECENT_DEST     = 1,

	XT_RECENT_NAME_LEN = 200,
पूर्ण;

/* Only allowed with --rcheck and --update */
#घोषणा XT_RECENT_MODIFIERS (XT_RECENT_TTL|XT_RECENT_REAP)

#घोषणा XT_RECENT_VALID_FLAGS (XT_RECENT_CHECK|XT_RECENT_SET|XT_RECENT_UPDATE|\
			       XT_RECENT_REMOVE|XT_RECENT_TTL|XT_RECENT_REAP)

काष्ठा xt_recent_mtinfo अणु
	__u32 seconds;
	__u32 hit_count;
	__u8 check_set;
	__u8 invert;
	अक्षर name[XT_RECENT_NAME_LEN];
	__u8 side;
पूर्ण;

काष्ठा xt_recent_mtinfo_v1 अणु
	__u32 seconds;
	__u32 hit_count;
	__u8 check_set;
	__u8 invert;
	अक्षर name[XT_RECENT_NAME_LEN];
	__u8 side;
	जोड़ nf_inet_addr mask;
पूर्ण;

#पूर्ण_अगर /* _LINUX_NETFILTER_XT_RECENT_H */
