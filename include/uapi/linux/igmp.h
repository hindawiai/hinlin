<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ WITH Linux-syscall-note */
/*
 *	Linux NET3:	Internet Group Management Protocol  [IGMP]
 *
 *	Authors:
 *		Alan Cox <alan@lxorguk.ukuu.org.uk>
 *
 *	Extended to talk the BSD extended IGMP protocol of mrouted 3.6
 *
 *
 *	This program is मुक्त software; you can redistribute it and/or
 *	modअगरy it under the terms of the GNU General Public License
 *	as published by the Free Software Foundation; either version
 *	2 of the License, or (at your option) any later version.
 */

#अगर_अघोषित _UAPI_LINUX_IGMP_H
#घोषणा _UAPI_LINUX_IGMP_H

#समावेश <linux/types.h>
#समावेश <यंत्र/byteorder.h>

/*
 *	IGMP protocol काष्ठाures
 */

/*
 *	Header in on cable क्रमmat
 */

काष्ठा igmphdr अणु
	__u8 type;
	__u8 code;		/* For newer IGMP */
	__sum16 csum;
	__be32 group;
पूर्ण;

/* V3 group record types [grec_type] */
#घोषणा IGMPV3_MODE_IS_INCLUDE		1
#घोषणा IGMPV3_MODE_IS_EXCLUDE		2
#घोषणा IGMPV3_CHANGE_TO_INCLUDE	3
#घोषणा IGMPV3_CHANGE_TO_EXCLUDE	4
#घोषणा IGMPV3_ALLOW_NEW_SOURCES	5
#घोषणा IGMPV3_BLOCK_OLD_SOURCES	6

काष्ठा igmpv3_grec अणु
	__u8	grec_type;
	__u8	grec_auxwords;
	__be16	grec_nsrcs;
	__be32	grec_mca;
	__be32	grec_src[0];
पूर्ण;

काष्ठा igmpv3_report अणु
	__u8 type;
	__u8 resv1;
	__sum16 csum;
	__be16 resv2;
	__be16 ngrec;
	काष्ठा igmpv3_grec grec[0];
पूर्ण;

काष्ठा igmpv3_query अणु
	__u8 type;
	__u8 code;
	__sum16 csum;
	__be32 group;
#अगर defined(__LITTLE_ENDIAN_BITFIELD)
	__u8 qrv:3,
	     suppress:1,
	     resv:4;
#या_अगर defined(__BIG_ENDIAN_BITFIELD)
	__u8 resv:4,
	     suppress:1,
	     qrv:3;
#अन्यथा
#त्रुटि "Please fix <asm/byteorder.h>"
#पूर्ण_अगर
	__u8 qqic;
	__be16 nsrcs;
	__be32 srcs[0];
पूर्ण;

#घोषणा IGMP_HOST_MEMBERSHIP_QUERY	0x11	/* From RFC1112 */
#घोषणा IGMP_HOST_MEMBERSHIP_REPORT	0x12	/* Ditto */
#घोषणा IGMP_DVMRP			0x13	/* DVMRP routing */
#घोषणा IGMP_PIM			0x14	/* PIM routing */
#घोषणा IGMP_TRACE			0x15
#घोषणा IGMPV2_HOST_MEMBERSHIP_REPORT	0x16	/* V2 version of 0x12 */
#घोषणा IGMP_HOST_LEAVE_MESSAGE 	0x17
#घोषणा IGMPV3_HOST_MEMBERSHIP_REPORT	0x22	/* V3 version of 0x12 */

#घोषणा IGMP_MTRACE_RESP		0x1e
#घोषणा IGMP_MTRACE			0x1f

#घोषणा IGMP_MRDISC_ADV			0x30	/* From RFC4286 */

/*
 *	Use the BSD names क्रम these क्रम compatibility
 */

#घोषणा IGMP_DELAYING_MEMBER		0x01
#घोषणा IGMP_IDLE_MEMBER		0x02
#घोषणा IGMP_LAZY_MEMBER		0x03
#घोषणा IGMP_SLEEPING_MEMBER		0x04
#घोषणा IGMP_AWAKENING_MEMBER		0x05

#घोषणा IGMP_MINLEN			8

#घोषणा IGMP_MAX_HOST_REPORT_DELAY	10	/* max delay क्रम response to */
						/* query (in seconds)	*/

#घोषणा IGMP_TIMER_SCALE		10	/* denotes that the igmphdr->समयr field */
						/* specअगरies समय in 10th of seconds	 */

#घोषणा IGMP_AGE_THRESHOLD		400	/* If this host करोn't hear any IGMP V1	*/
						/* message in this period of समय,	*/
						/* revert to IGMP v2 router.		*/

#घोषणा IGMP_ALL_HOSTS		htonl(0xE0000001L)
#घोषणा IGMP_ALL_ROUTER 	htonl(0xE0000002L)
#घोषणा IGMPV3_ALL_MCR	 	htonl(0xE0000016L)
#घोषणा IGMP_LOCAL_GROUP	htonl(0xE0000000L)
#घोषणा IGMP_LOCAL_GROUP_MASK	htonl(0xFFFFFF00L)

/*
 * काष्ठा क्रम keeping the multicast list in
 */

#पूर्ण_अगर /* _UAPI_LINUX_IGMP_H */
