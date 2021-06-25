<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ WITH Linux-syscall-note */
/*
 * INET         An implementation of the TCP/IP protocol suite क्रम the LINUX
 *              operating प्रणाली.  INET is implemented using the  BSD Socket
 *              पूर्णांकerface as the means of communication with the user level.
 *
 *              Global definitions क्रम the ARCnet पूर्णांकerface.
 *
 * Authors:     David Woodhouse and Avery Pennarun
 *
 *              This program is मुक्त software; you can redistribute it and/or
 *              modअगरy it under the terms of the GNU General Public License
 *              as published by the Free Software Foundation; either version
 *              2 of the License, or (at your option) any later version.
 */

#अगर_अघोषित _LINUX_IF_ARCNET_H
#घोषणा _LINUX_IF_ARCNET_H

#समावेश <linux/types.h>
#समावेश <linux/अगर_ether.h>

/*
 *    These are the defined ARCnet Protocol ID's.
 */

/* CAP mode */
/* No macro but uses 1-8 */

/* RFC1201 Protocol ID's */
#घोषणा ARC_P_IP		212	/* 0xD4 */
#घोषणा ARC_P_IPV6		196	/* 0xC4: RFC2497 */
#घोषणा ARC_P_ARP		213	/* 0xD5 */
#घोषणा ARC_P_RARP		214	/* 0xD6 */
#घोषणा ARC_P_IPX		250	/* 0xFA */
#घोषणा ARC_P_NOVELL_EC		236	/* 0xEC */

/* Old RFC1051 Protocol ID's */
#घोषणा ARC_P_IP_RFC1051	240	/* 0xF0 */
#घोषणा ARC_P_ARP_RFC1051	241	/* 0xF1 */

/* MS LanMan/WfWg "NDIS" encapsulation */
#घोषणा ARC_P_ETHER		232	/* 0xE8 */

/* Unsupported/indirectly supported protocols */
#घोषणा ARC_P_DATAPOINT_BOOT	0	/* very old Datapoपूर्णांक equipment */
#घोषणा ARC_P_DATAPOINT_MOUNT	1
#घोषणा ARC_P_POWERLAN_BEACON	8	/* Probably ATA-Netbios related */
#घोषणा ARC_P_POWERLAN_BEACON2	243	/* 0xF3 */
#घोषणा ARC_P_LANSOFT		251	/* 0xFB - what is this? */
#घोषणा ARC_P_ATALK		0xDD

/* Hardware address length */
#घोषणा ARCNET_ALEN	1

/*
 * The RFC1201-specअगरic components of an arcnet packet header.
 */
काष्ठा arc_rfc1201 अणु
	__u8  proto;		/* protocol ID field - varies		*/
	__u8  split_flag;	/* क्रम use with split packets		*/
	__be16   sequence;	/* sequence number			*/
	__u8  payload[0];	/* space reमुख्यing in packet (504 bytes)*/
पूर्ण;
#घोषणा RFC1201_HDR_SIZE 4

/*
 * The RFC1051-specअगरic components.
 */
काष्ठा arc_rfc1051 अणु
	__u8 proto;		/* ARC_P_RFC1051_ARP/RFC1051_IP	*/
	__u8 payload[0];	/* 507 bytes			*/
पूर्ण;
#घोषणा RFC1051_HDR_SIZE 1

/*
 * The ethernet-encap-specअगरic components.  We have a real ethernet header
 * and some data.
 */
काष्ठा arc_eth_encap अणु
	__u8 proto;		/* Always ARC_P_ETHER			*/
	काष्ठा ethhdr eth;	/* standard ethernet header (yuck!)	*/
	__u8 payload[0];	/* 493 bytes				*/
पूर्ण;
#घोषणा ETH_ENCAP_HDR_SIZE 14

काष्ठा arc_cap अणु
	__u8 proto;
	__u8 cookie[माप(पूर्णांक)];
				/* Actually NOT sent over the network */
	जोड़ अणु
		__u8 ack;
		__u8 raw[0];	/* 507 bytes */
	पूर्ण mes;
पूर्ण;

/*
 * The data needed by the actual arcnet hardware.
 *
 * Now, in the real arcnet hardware, the third and fourth bytes are the
 * 'offset' specअगरication instead of the length, and the soft data is at
 * the _end_ of the 512-byte buffer.  We hide this complनिकासy inside the
 * driver.
 */
काष्ठा arc_hardware अणु
	__u8 source;		/* source ARCnet - filled in स्वतःmagically */
	__u8 dest;		/* destination ARCnet - 0 क्रम broadcast    */
	__u8 offset[2];		/* offset bytes (some weird semantics)     */
पूर्ण;
#घोषणा ARC_HDR_SIZE 4

/*
 * This is an ARCnet frame header, as seen by the kernel (and userspace,
 * when you करो a raw packet capture).
 */
काष्ठा archdr अणु
	/* hardware requirements */
	काष्ठा arc_hardware hard;

	/* arcnet encapsulation-specअगरic bits */
	जोड़ अणु
		काष्ठा arc_rfc1201   rfc1201;
		काष्ठा arc_rfc1051   rfc1051;
		काष्ठा arc_eth_encap eth_encap;
		काष्ठा arc_cap       cap;
		__u8 raw[0];	/* 508 bytes				*/
	पूर्ण soft;
पूर्ण;

#पूर्ण_अगर				/* _LINUX_IF_ARCNET_H */
