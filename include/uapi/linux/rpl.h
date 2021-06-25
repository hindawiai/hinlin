<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ WITH Linux-syscall-note */
/*
 *  IPv6 RPL-SR implementation
 *
 *  Author:
 *  (C) 2020 Alexander Aring <alex.aring@gmail.com>
 */

#अगर_अघोषित _UAPI_LINUX_RPL_H
#घोषणा _UAPI_LINUX_RPL_H

#समावेश <यंत्र/byteorder.h>
#समावेश <linux/types.h>
#समावेश <linux/in6.h>

/*
 * RPL SR Header
 */
काष्ठा ipv6_rpl_sr_hdr अणु
	__u8	nexthdr;
	__u8	hdrlen;
	__u8	type;
	__u8	segments_left;
#अगर defined(__LITTLE_ENDIAN_BITFIELD)
	__u32	cmpre:4,
		cmpri:4,
		reserved:4,
		pad:4,
		reserved1:16;
#या_अगर defined(__BIG_ENDIAN_BITFIELD)
	__u32	cmpri:4,
		cmpre:4,
		pad:4,
		reserved:20;
#अन्यथा
#त्रुटि  "Please fix <asm/byteorder.h>"
#पूर्ण_अगर

	जोड़ अणु
		काष्ठा in6_addr addr[0];
		__u8 data[0];
	पूर्ण segments;
पूर्ण __attribute__((packed));

#घोषणा rpl_segaddr	segments.addr
#घोषणा rpl_segdata	segments.data

#पूर्ण_अगर
