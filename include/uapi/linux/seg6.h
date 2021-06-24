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

#अगर_अघोषित _UAPI_LINUX_SEG6_H
#घोषणा _UAPI_LINUX_SEG6_H

#समावेश <linux/types.h>
#समावेश <linux/in6.h>		/* For काष्ठा in6_addr. */

/*
 * SRH
 */
काष्ठा ipv6_sr_hdr अणु
	__u8	nexthdr;
	__u8	hdrlen;
	__u8	type;
	__u8	segments_left;
	__u8	first_segment; /* Represents the last_entry field of SRH */
	__u8	flags;
	__u16	tag;

	काष्ठा in6_addr segments[0];
पूर्ण;

#घोषणा SR6_FLAG1_PROTECTED	(1 << 6)
#घोषणा SR6_FLAG1_OAM		(1 << 5)
#घोषणा SR6_FLAG1_ALERT		(1 << 4)
#घोषणा SR6_FLAG1_HMAC		(1 << 3)

#घोषणा SR6_TLV_INGRESS		1
#घोषणा SR6_TLV_EGRESS		2
#घोषणा SR6_TLV_OPAQUE		3
#घोषणा SR6_TLV_PADDING		4
#घोषणा SR6_TLV_HMAC		5

#घोषणा sr_has_hmac(srh) ((srh)->flags & SR6_FLAG1_HMAC)

काष्ठा sr6_tlv अणु
	__u8 type;
	__u8 len;
	__u8 data[0];
पूर्ण;

#पूर्ण_अगर
