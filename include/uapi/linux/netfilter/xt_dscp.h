<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/* x_tables module क्रम matching the IPv4/IPv6 DSCP field
 *
 * (C) 2002 Harald Welte <laक्रमge@gnumonks.org>
 * This software is distributed under GNU GPL v2, 1991
 *
 * See RFC2474 क्रम a description of the DSCP field within the IP Header.
 *
 * xt_dscp.h,v 1.3 2002/08/05 19:00:21 laक्रमge Exp
*/
#अगर_अघोषित _XT_DSCP_H
#घोषणा _XT_DSCP_H

#समावेश <linux/types.h>

#घोषणा XT_DSCP_MASK	0xfc	/* 11111100 */
#घोषणा XT_DSCP_SHIFT	2
#घोषणा XT_DSCP_MAX	0x3f	/* 00111111 */

/* match info */
काष्ठा xt_dscp_info अणु
	__u8 dscp;
	__u8 invert;
पूर्ण;

काष्ठा xt_tos_match_info अणु
	__u8 tos_mask;
	__u8 tos_value;
	__u8 invert;
पूर्ण;

#पूर्ण_अगर /* _XT_DSCP_H */
