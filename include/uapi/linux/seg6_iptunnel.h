<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ WITH Linux-syscall-note */
/*
 *  SR-IPv6 implementation
 *
 *  Author:
 *  David Lebrun <david.lebrun@uclouvain.be>
 *
 *
 *  This program is मुक्त software; you can redistribute it and/or
 *      modअगरy it under the terms of the GNU General Public License
 *      as published by the Free Software Foundation; either version
 *      2 of the License, or (at your option) any later version.
 */

#अगर_अघोषित _UAPI_LINUX_SEG6_IPTUNNEL_H
#घोषणा _UAPI_LINUX_SEG6_IPTUNNEL_H

#समावेश <linux/seg6.h>		/* For काष्ठा ipv6_sr_hdr. */

क्रमागत अणु
	SEG6_IPTUNNEL_UNSPEC,
	SEG6_IPTUNNEL_SRH,
	__SEG6_IPTUNNEL_MAX,
पूर्ण;
#घोषणा SEG6_IPTUNNEL_MAX (__SEG6_IPTUNNEL_MAX - 1)

काष्ठा seg6_iptunnel_encap अणु
	पूर्णांक mode;
	काष्ठा ipv6_sr_hdr srh[0];
पूर्ण;

#घोषणा SEG6_IPTUN_ENCAP_SIZE(x) ((माप(*x)) + (((x)->srh->hdrlen + 1) << 3))

क्रमागत अणु
	SEG6_IPTUN_MODE_INLINE,
	SEG6_IPTUN_MODE_ENCAP,
	SEG6_IPTUN_MODE_L2ENCAP,
पूर्ण;

#पूर्ण_अगर
