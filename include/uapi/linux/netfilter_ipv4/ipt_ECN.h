<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/* Header file क्रम iptables ipt_ECN target
 *
 * (C) 2002 by Harald Welte <laक्रमge@gnumonks.org>
 *
 * This software is distributed under GNU GPL v2, 1991
 * 
 * ipt_ECN.h,v 1.3 2002/05/29 12:17:40 laक्रमge Exp
*/
#अगर_अघोषित _IPT_ECN_TARGET_H
#घोषणा _IPT_ECN_TARGET_H

#समावेश <linux/types.h>
#समावेश <linux/netfilter/xt_DSCP.h>

#घोषणा IPT_ECN_IP_MASK	(~XT_DSCP_MASK)

#घोषणा IPT_ECN_OP_SET_IP	0x01	/* set ECN bits of IPv4 header */
#घोषणा IPT_ECN_OP_SET_ECE	0x10	/* set ECE bit of TCP header */
#घोषणा IPT_ECN_OP_SET_CWR	0x20	/* set CWR bit of TCP header */

#घोषणा IPT_ECN_OP_MASK		0xce

काष्ठा ipt_ECN_info अणु
	__u8 operation;	/* bitset of operations */
	__u8 ip_ect;	/* ECT codepoपूर्णांक of IPv4 header, pre-shअगरted */
	जोड़ अणु
		काष्ठा अणु
			__u8 ece:1, cwr:1; /* TCP ECT bits */
		पूर्ण tcp;
	पूर्ण proto;
पूर्ण;

#पूर्ण_अगर /* _IPT_ECN_TARGET_H */
