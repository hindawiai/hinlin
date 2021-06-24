<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/* iptables module क्रम matching the ECN header in IPv4 and TCP header
 *
 * (C) 2002 Harald Welte <laक्रमge@gnumonks.org>
 *
 * This software is distributed under GNU GPL v2, 1991
 * 
 * ipt_ecn.h,v 1.4 2002/08/05 19:39:00 laक्रमge Exp
*/
#अगर_अघोषित _XT_ECN_H
#घोषणा _XT_ECN_H

#समावेश <linux/types.h>
#समावेश <linux/netfilter/xt_dscp.h>

#घोषणा XT_ECN_IP_MASK	(~XT_DSCP_MASK)

#घोषणा XT_ECN_OP_MATCH_IP	0x01
#घोषणा XT_ECN_OP_MATCH_ECE	0x10
#घोषणा XT_ECN_OP_MATCH_CWR	0x20

#घोषणा XT_ECN_OP_MATCH_MASK	0xce

/* match info */
काष्ठा xt_ecn_info अणु
	__u8 operation;
	__u8 invert;
	__u8 ip_ect;
	जोड़ अणु
		काष्ठा अणु
			__u8 ect;
		पूर्ण tcp;
	पूर्ण proto;
पूर्ण;

#पूर्ण_अगर /* _XT_ECN_H */
