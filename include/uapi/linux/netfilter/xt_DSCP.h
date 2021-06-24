<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/* x_tables module क्रम setting the IPv4/IPv6 DSCP field
 *
 * (C) 2002 Harald Welte <laक्रमge@gnumonks.org>
 * based on ipt_FTOS.c (C) 2000 by Matthew G. Marsh <mgm@paktronix.com>
 * This software is distributed under GNU GPL v2, 1991
 *
 * See RFC2474 क्रम a description of the DSCP field within the IP Header.
 *
 * xt_DSCP.h,v 1.7 2002/03/14 12:03:13 laक्रमge Exp
*/
#अगर_अघोषित _XT_DSCP_TARGET_H
#घोषणा _XT_DSCP_TARGET_H
#समावेश <linux/netfilter/xt_dscp.h>
#समावेश <linux/types.h>

/* target info */
काष्ठा xt_DSCP_info अणु
	__u8 dscp;
पूर्ण;

काष्ठा xt_tos_target_info अणु
	__u8 tos_value;
	__u8 tos_mask;
पूर्ण;

#पूर्ण_अगर /* _XT_DSCP_TARGET_H */
