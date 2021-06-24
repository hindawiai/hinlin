<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ WITH Linux-syscall-note */
/*
 *  IPv6 RPL-SR implementation
 *
 *  Author:
 *  (C) 2020 Alexander Aring <alex.aring@gmail.com>
 */

#अगर_अघोषित _UAPI_LINUX_RPL_IPTUNNEL_H
#घोषणा _UAPI_LINUX_RPL_IPTUNNEL_H

क्रमागत अणु
	RPL_IPTUNNEL_UNSPEC,
	RPL_IPTUNNEL_SRH,
	__RPL_IPTUNNEL_MAX,
पूर्ण;
#घोषणा RPL_IPTUNNEL_MAX (__RPL_IPTUNNEL_MAX - 1)

#घोषणा RPL_IPTUNNEL_SRH_SIZE(srh) (((srh)->hdrlen + 1) << 3)

#पूर्ण_अगर
