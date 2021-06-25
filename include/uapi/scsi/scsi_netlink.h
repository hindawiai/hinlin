<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ WITH Linux-syscall-note */
/*
 *  SCSI Transport Netlink Interface
 *    Used क्रम the posting of outbound SCSI transport events
 *
 *  Copyright (C) 2006   James Smart, Emulex Corporation
 */
#अगर_अघोषित SCSI_NETLINK_H
#घोषणा SCSI_NETLINK_H

#समावेश <linux/netlink.h>
#समावेश <linux/types.h>

/*
 * This file पूर्णांकended to be included by both kernel and user space
 */

/* Single Netlink Message type to send all SCSI Transport messages */
#घोषणा SCSI_TRANSPORT_MSG		NLMSG_MIN_TYPE + 1

/* SCSI Transport Broadcast Groups */
	/* leaving groups 0 and 1 unasचिन्हित */
#घोषणा SCSI_NL_GRP_FC_EVENTS		(1<<2)		/* Group 2 */
#घोषणा SCSI_NL_GRP_CNT			3


/* SCSI_TRANSPORT_MSG event message header */
काष्ठा scsi_nl_hdr अणु
	__u8 version;
	__u8 transport;
	__u16 magic;
	__u16 msgtype;
	__u16 msglen;
पूर्ण __attribute__((aligned(माप(__u64))));

/* scsi_nl_hdr->version value */
#घोषणा SCSI_NL_VERSION				1

/* scsi_nl_hdr->magic value */
#घोषणा SCSI_NL_MAGIC				0xA1B2

/* scsi_nl_hdr->transport value */
#घोषणा SCSI_NL_TRANSPORT			0
#घोषणा SCSI_NL_TRANSPORT_FC			1
#घोषणा SCSI_NL_MAX_TRANSPORTS			2

/* Transport-based scsi_nl_hdr->msgtype values are defined in each transport */

/*
 * GENERIC SCSI scsi_nl_hdr->msgtype Values
 */
	/* kernel -> user */
#घोषणा SCSI_NL_SHOST_VENDOR			0x0001
	/* user -> kernel */
/* SCSI_NL_SHOST_VENDOR msgtype is kernel->user and user->kernel */


/*
 * Message Structures :
 */

/* macro to round up message lengths to 8byte boundary */
#घोषणा SCSI_NL_MSGALIGN(len)		(((len) + 7) & ~7)


/*
 * SCSI HOST Venकरोr Unique messages :
 *   SCSI_NL_SHOST_VENDOR
 *
 * Note: The Venकरोr Unique message payload will begin directly after
 * 	 this काष्ठाure, with the length of the payload per vmsg_datalen.
 *
 * Note: When specअगरying venकरोr_id, be sure to पढ़ो the Venकरोr Type and ID
 *   क्रमmatting requirements specअगरied below
 */
काष्ठा scsi_nl_host_venकरोr_msg अणु
	काष्ठा scsi_nl_hdr snlh;		/* must be 1st element ! */
	__u64 venकरोr_id;
	__u16 host_no;
	__u16 vmsg_datalen;
पूर्ण __attribute__((aligned(माप(__u64))));


/*
 * Venकरोr ID:
 *   If transports post venकरोr-unique events, they must pass a well-known
 *   32-bit venकरोr identअगरier. This identअगरier consists of 8 bits indicating
 *   the "type" of identअगरier contained, and 24 bits of id data.
 *
 *   Identअगरiers क्रम each type:
 *    PCI :  ID data is the 16 bit PCI Registered Venकरोr ID
 */
#घोषणा SCSI_NL_VID_TYPE_SHIFT		56
#घोषणा SCSI_NL_VID_TYPE_MASK		((__u64)0xFF << SCSI_NL_VID_TYPE_SHIFT)
#घोषणा SCSI_NL_VID_TYPE_PCI		((__u64)0x01 << SCSI_NL_VID_TYPE_SHIFT)
#घोषणा SCSI_NL_VID_ID_MASK		(~ SCSI_NL_VID_TYPE_MASK)


#घोषणा INIT_SCSI_NL_HDR(hdr, t, mtype, mlen)			\
	अणु							\
	(hdr)->version = SCSI_NL_VERSION;			\
	(hdr)->transport = t;					\
	(hdr)->magic = SCSI_NL_MAGIC;				\
	(hdr)->msgtype = mtype;					\
	(hdr)->msglen = mlen;					\
	पूर्ण

#पूर्ण_अगर /* SCSI_NETLINK_H */

