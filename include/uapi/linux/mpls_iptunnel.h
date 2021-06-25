<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ WITH Linux-syscall-note */
/*
 *	mpls tunnel api
 *
 *	Authors:
 *		Roopa Prabhu <roopa@cumulusnetworks.com>
 *
 *	This program is मुक्त software; you can redistribute it and/or
 *	modअगरy it under the terms of the GNU General Public License
 *	as published by the Free Software Foundation; either version
 *	2 of the License, or (at your option) any later version.
 */

#अगर_अघोषित _UAPI_LINUX_MPLS_IPTUNNEL_H
#घोषणा _UAPI_LINUX_MPLS_IPTUNNEL_H

/* MPLS tunnel attributes
 * [RTA_ENCAP] = अणु
 *     [MPLS_IPTUNNEL_DST]
 *     [MPLS_IPTUNNEL_TTL]
 * पूर्ण
 */
क्रमागत अणु
	MPLS_IPTUNNEL_UNSPEC,
	MPLS_IPTUNNEL_DST,
	MPLS_IPTUNNEL_TTL,
	__MPLS_IPTUNNEL_MAX,
पूर्ण;
#घोषणा MPLS_IPTUNNEL_MAX (__MPLS_IPTUNNEL_MAX - 1)

#पूर्ण_अगर /* _UAPI_LINUX_MPLS_IPTUNNEL_H */
