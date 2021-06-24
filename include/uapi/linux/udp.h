<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ WITH Linux-syscall-note */
/*
 * INET		An implementation of the TCP/IP protocol suite क्रम the LINUX
 *		operating प्रणाली.  INET is implemented using the  BSD Socket
 *		पूर्णांकerface as the means of communication with the user level.
 *
 *		Definitions क्रम the UDP protocol.
 *
 * Version:	@(#)udp.h	1.0.2	04/28/93
 *
 * Author:	Fred N. van Kempen, <waltje@uWalt.NL.Mugnet.ORG>
 *
 *		This program is मुक्त software; you can redistribute it and/or
 *		modअगरy it under the terms of the GNU General Public License
 *		as published by the Free Software Foundation; either version
 *		2 of the License, or (at your option) any later version.
 */
#अगर_अघोषित _UAPI_LINUX_UDP_H
#घोषणा _UAPI_LINUX_UDP_H

#समावेश <linux/types.h>

काष्ठा udphdr अणु
	__be16	source;
	__be16	dest;
	__be16	len;
	__sum16	check;
पूर्ण;

/* UDP socket options */
#घोषणा UDP_CORK	1	/* Never send partially complete segments */
#घोषणा UDP_ENCAP	100	/* Set the socket to accept encapsulated packets */
#घोषणा UDP_NO_CHECK6_TX 101	/* Disable sending checksum क्रम UDP6X */
#घोषणा UDP_NO_CHECK6_RX 102	/* Disable accpeting checksum क्रम UDP6 */
#घोषणा UDP_SEGMENT	103	/* Set GSO segmentation size */
#घोषणा UDP_GRO		104	/* This socket can receive UDP GRO packets */

/* UDP encapsulation types */
#घोषणा UDP_ENCAP_ESPINUDP_NON_IKE	1 /* draft-ietf-ipsec-nat-t-ike-00/01 */
#घोषणा UDP_ENCAP_ESPINUDP	2 /* draft-ietf-ipsec-udp-encaps-06 */
#घोषणा UDP_ENCAP_L2TPINUDP	3 /* rfc2661 */
#घोषणा UDP_ENCAP_GTP0		4 /* GSM TS 09.60 */
#घोषणा UDP_ENCAP_GTP1U		5 /* 3GPP TS 29.060 */
#घोषणा UDP_ENCAP_RXRPC		6
#घोषणा TCP_ENCAP_ESPINTCP	7 /* Yikes, this is really xfrm encap types. */

#पूर्ण_अगर /* _UAPI_LINUX_UDP_H */
