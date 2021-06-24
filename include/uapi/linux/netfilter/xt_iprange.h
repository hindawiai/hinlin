<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _LINUX_NETFILTER_XT_IPRANGE_H
#घोषणा _LINUX_NETFILTER_XT_IPRANGE_H 1

#समावेश <linux/types.h>
#समावेश <linux/netfilter.h>

क्रमागत अणु
	IPRANGE_SRC     = 1 << 0,	/* match source IP address */
	IPRANGE_DST     = 1 << 1,	/* match destination IP address */
	IPRANGE_SRC_INV = 1 << 4,	/* negate the condition */
	IPRANGE_DST_INV = 1 << 5,	/* -"- */
पूर्ण;

काष्ठा xt_iprange_mtinfo अणु
	जोड़ nf_inet_addr src_min, src_max;
	जोड़ nf_inet_addr dst_min, dst_max;
	__u8 flags;
पूर्ण;

#पूर्ण_अगर /* _LINUX_NETFILTER_XT_IPRANGE_H */
