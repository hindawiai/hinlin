<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ WITH Linux-syscall-note */
/*
 *  FC Transport Netlink Interface
 *
 *  Copyright (C) 2006   James Smart, Emulex Corporation
 */
#अगर_अघोषित SCSI_NETLINK_FC_H
#घोषणा SCSI_NETLINK_FC_H

#समावेश <linux/types.h>
#समावेश <scsi/scsi_netlink.h>

/*
 * This file पूर्णांकended to be included by both kernel and user space
 */

/*
 * FC Transport Message Types
 */
	/* kernel -> user */
#घोषणा FC_NL_ASYNC_EVENT			0x0100
	/* user -> kernel */
/* none */


/*
 * Message Structures :
 */

/* macro to round up message lengths to 8byte boundary */
#घोषणा FC_NL_MSGALIGN(len)		(((len) + 7) & ~7)


/*
 * FC Transport Broadcast Event Message :
 *   FC_NL_ASYNC_EVENT
 *
 * Note: अगर Venकरोr Unique message, &event_data will be  start of
 * 	 venकरोr unique payload, and the length of the payload is
 *       per event_datalen
 *
 * Note: When specअगरying venकरोr_id, be sure to पढ़ो the Venकरोr Type and ID
 *   क्रमmatting requirements specअगरied in scsi_netlink.h
 */
काष्ठा fc_nl_event अणु
	काष्ठा scsi_nl_hdr snlh;		/* must be 1st element ! */
	__u64 seconds;
	__u64 venकरोr_id;
	__u16 host_no;
	__u16 event_datalen;
	__u32 event_num;
	__u32 event_code;
	__u32 event_data;
पूर्ण __attribute__((aligned(माप(__u64))));


#पूर्ण_अगर /* SCSI_NETLINK_FC_H */

