<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-1.0+ WITH Linux-syscall-note */
/* Header file क्रम kernel module to match connection tracking inक्रमmation.
 * GPL (C) 2001  Marc Boucher (marc@mbsi.ca).
 */

#अगर_अघोषित _XT_CONNTRACK_H
#घोषणा _XT_CONNTRACK_H

#समावेश <linux/types.h>
#समावेश <linux/netfilter.h>
#समावेश <linux/netfilter/nf_conntrack_tuple_common.h>

#घोषणा XT_CONNTRACK_STATE_BIT(ctinfo) (1 << ((ctinfo)%IP_CT_IS_REPLY+1))
#घोषणा XT_CONNTRACK_STATE_INVALID (1 << 0)

#घोषणा XT_CONNTRACK_STATE_SNAT (1 << (IP_CT_NUMBER + 1))
#घोषणा XT_CONNTRACK_STATE_DNAT (1 << (IP_CT_NUMBER + 2))
#घोषणा XT_CONNTRACK_STATE_UNTRACKED (1 << (IP_CT_NUMBER + 3))

/* flags, invflags: */
क्रमागत अणु
	XT_CONNTRACK_STATE        = 1 << 0,
	XT_CONNTRACK_PROTO        = 1 << 1,
	XT_CONNTRACK_ORIGSRC      = 1 << 2,
	XT_CONNTRACK_ORIGDST      = 1 << 3,
	XT_CONNTRACK_REPLSRC      = 1 << 4,
	XT_CONNTRACK_REPLDST      = 1 << 5,
	XT_CONNTRACK_STATUS       = 1 << 6,
	XT_CONNTRACK_EXPIRES      = 1 << 7,
	XT_CONNTRACK_ORIGSRC_PORT = 1 << 8,
	XT_CONNTRACK_ORIGDST_PORT = 1 << 9,
	XT_CONNTRACK_REPLSRC_PORT = 1 << 10,
	XT_CONNTRACK_REPLDST_PORT = 1 << 11,
	XT_CONNTRACK_सूचीECTION    = 1 << 12,
	XT_CONNTRACK_STATE_ALIAS  = 1 << 13,
पूर्ण;

काष्ठा xt_conntrack_mtinfo1 अणु
	जोड़ nf_inet_addr origsrc_addr, origsrc_mask;
	जोड़ nf_inet_addr origdst_addr, origdst_mask;
	जोड़ nf_inet_addr replsrc_addr, replsrc_mask;
	जोड़ nf_inet_addr repldst_addr, repldst_mask;
	__u32 expires_min, expires_max;
	__u16 l4proto;
	__be16 origsrc_port, origdst_port;
	__be16 replsrc_port, repldst_port;
	__u16 match_flags, invert_flags;
	__u8 state_mask, status_mask;
पूर्ण;

काष्ठा xt_conntrack_mtinfo2 अणु
	जोड़ nf_inet_addr origsrc_addr, origsrc_mask;
	जोड़ nf_inet_addr origdst_addr, origdst_mask;
	जोड़ nf_inet_addr replsrc_addr, replsrc_mask;
	जोड़ nf_inet_addr repldst_addr, repldst_mask;
	__u32 expires_min, expires_max;
	__u16 l4proto;
	__be16 origsrc_port, origdst_port;
	__be16 replsrc_port, repldst_port;
	__u16 match_flags, invert_flags;
	__u16 state_mask, status_mask;
पूर्ण;

काष्ठा xt_conntrack_mtinfo3 अणु
	जोड़ nf_inet_addr origsrc_addr, origsrc_mask;
	जोड़ nf_inet_addr origdst_addr, origdst_mask;
	जोड़ nf_inet_addr replsrc_addr, replsrc_mask;
	जोड़ nf_inet_addr repldst_addr, repldst_mask;
	__u32 expires_min, expires_max;
	__u16 l4proto;
	__u16 origsrc_port, origdst_port;
	__u16 replsrc_port, repldst_port;
	__u16 match_flags, invert_flags;
	__u16 state_mask, status_mask;
	__u16 origsrc_port_high, origdst_port_high;
	__u16 replsrc_port_high, repldst_port_high;
पूर्ण;

#पूर्ण_अगर /*_XT_CONNTRACK_H*/
