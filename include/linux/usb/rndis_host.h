<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Host Side support क्रम RNDIS Networking Links
 * Copyright (C) 2005 by David Brownell
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 *
 * You should have received a copy of the GNU General Public License
 * aदीर्घ with this program; अगर not, ग_लिखो to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#अगर_अघोषित	__LINUX_USB_RNDIS_HOST_H
#घोषणा	__LINUX_USB_RNDIS_HOST_H

#समावेश <linux/rndis.h>

/*
 * CONTROL uses CDC "encapsulated commands" with funky notअगरications.
 *  - control-out:  SEND_ENCAPSULATED
 *  - पूर्णांकerrupt-in:  RESPONSE_AVAILABLE
 *  - control-in:  GET_ENCAPSULATED
 *
 * We'll try to ignore the RESPONSE_AVAILABLE notअगरications.
 *
 * REVISIT some RNDIS implementations seem to have curious issues still
 * to be resolved.
 */
काष्ठा rndis_msg_hdr अणु
	__le32	msg_type;			/* RNDIS_MSG_* */
	__le32	msg_len;
	/* followed by data that varies between messages */
	__le32	request_id;
	__le32	status;
	/* ... and more */
पूर्ण __attribute__ ((packed));

/* MS-Winकरोws uses this strange size, but RNDIS spec says 1024 minimum */
#घोषणा	CONTROL_BUFFER_SIZE		1025

/* RNDIS defines an (असलurdly huge) 10 second control समयout,
 * but ActiveSync seems to use a more usual 5 second समयout
 * (which matches the USB 2.0 spec).
 */
#घोषणा	RNDIS_CONTROL_TIMEOUT_MS	(5 * 1000)

काष्ठा rndis_data_hdr अणु
	__le32	msg_type;		/* RNDIS_MSG_PACKET */
	__le32	msg_len;		/* rndis_data_hdr + data_len + pad */
	__le32	data_offset;		/* 36 -- right after header */
	__le32	data_len;		/* ... real packet size */

	__le32	oob_data_offset;	/* zero */
	__le32	oob_data_len;		/* zero */
	__le32	num_oob;		/* zero */
	__le32	packet_data_offset;	/* zero */

	__le32	packet_data_len;	/* zero */
	__le32	vc_handle;		/* zero */
	__le32	reserved;		/* zero */
पूर्ण __attribute__ ((packed));

काष्ठा rndis_init अणु		/* OUT */
	/* header and: */
	__le32	msg_type;			/* RNDIS_MSG_INIT */
	__le32	msg_len;			/* 24 */
	__le32	request_id;
	__le32	major_version;			/* of rndis (1.0) */
	__le32	minor_version;
	__le32	max_transfer_size;
पूर्ण __attribute__ ((packed));

काष्ठा rndis_init_c अणु		/* IN */
	/* header and: */
	__le32	msg_type;			/* RNDIS_MSG_INIT_C */
	__le32	msg_len;
	__le32	request_id;
	__le32	status;
	__le32	major_version;			/* of rndis (1.0) */
	__le32	minor_version;
	__le32	device_flags;
	__le32	medium;				/* zero == 802.3 */
	__le32	max_packets_per_message;
	__le32	max_transfer_size;
	__le32	packet_alignment;		/* max 7; (1<<n) bytes */
	__le32	af_list_offset;			/* zero */
	__le32	af_list_size;			/* zero */
पूर्ण __attribute__ ((packed));

काष्ठा rndis_halt अणु		/* OUT (no reply) */
	/* header and: */
	__le32	msg_type;			/* RNDIS_MSG_HALT */
	__le32	msg_len;
	__le32	request_id;
पूर्ण __attribute__ ((packed));

काष्ठा rndis_query अणु		/* OUT */
	/* header and: */
	__le32	msg_type;			/* RNDIS_MSG_QUERY */
	__le32	msg_len;
	__le32	request_id;
	__le32	oid;
	__le32	len;
	__le32	offset;
/*?*/	__le32	handle;				/* zero */
पूर्ण __attribute__ ((packed));

काष्ठा rndis_query_c अणु		/* IN */
	/* header and: */
	__le32	msg_type;			/* RNDIS_MSG_QUERY_C */
	__le32	msg_len;
	__le32	request_id;
	__le32	status;
	__le32	len;
	__le32	offset;
पूर्ण __attribute__ ((packed));

काष्ठा rndis_set अणु		/* OUT */
	/* header and: */
	__le32	msg_type;			/* RNDIS_MSG_SET */
	__le32	msg_len;
	__le32	request_id;
	__le32	oid;
	__le32	len;
	__le32	offset;
/*?*/	__le32	handle;				/* zero */
पूर्ण __attribute__ ((packed));

काष्ठा rndis_set_c अणु		/* IN */
	/* header and: */
	__le32	msg_type;			/* RNDIS_MSG_SET_C */
	__le32	msg_len;
	__le32	request_id;
	__le32	status;
पूर्ण __attribute__ ((packed));

काष्ठा rndis_reset अणु		/* IN */
	/* header and: */
	__le32	msg_type;			/* RNDIS_MSG_RESET */
	__le32	msg_len;
	__le32	reserved;
पूर्ण __attribute__ ((packed));

काष्ठा rndis_reset_c अणु		/* OUT */
	/* header and: */
	__le32	msg_type;			/* RNDIS_MSG_RESET_C */
	__le32	msg_len;
	__le32	status;
	__le32	addressing_lost;
पूर्ण __attribute__ ((packed));

काष्ठा rndis_indicate अणु		/* IN (unrequested) */
	/* header and: */
	__le32	msg_type;			/* RNDIS_MSG_INDICATE */
	__le32	msg_len;
	__le32	status;
	__le32	length;
	__le32	offset;
/**/	__le32	diag_status;
	__le32	error_offset;
/**/	__le32	message;
पूर्ण __attribute__ ((packed));

काष्ठा rndis_keepalive अणु	/* OUT (optionally IN) */
	/* header and: */
	__le32	msg_type;			/* RNDIS_MSG_KEEPALIVE */
	__le32	msg_len;
	__le32	request_id;
पूर्ण __attribute__ ((packed));

काष्ठा rndis_keepalive_c अणु	/* IN (optionally OUT) */
	/* header and: */
	__le32	msg_type;			/* RNDIS_MSG_KEEPALIVE_C */
	__le32	msg_len;
	__le32	request_id;
	__le32	status;
पूर्ण __attribute__ ((packed));

/* शेष filter used with RNDIS devices */
#घोषणा RNDIS_DEFAULT_FILTER ( \
	RNDIS_PACKET_TYPE_सूचीECTED | \
	RNDIS_PACKET_TYPE_BROADCAST | \
	RNDIS_PACKET_TYPE_ALL_MULTICAST | \
	RNDIS_PACKET_TYPE_PROMISCUOUS)

/* Flags to require specअगरic physical medium type क्रम generic_rndis_bind() */
#घोषणा FLAG_RNDIS_PHYM_NOT_WIRELESS	0x0001
#घोषणा FLAG_RNDIS_PHYM_WIRELESS	0x0002

/* Flags क्रम driver_info::data */
#घोषणा RNDIS_DRIVER_DATA_POLL_STATUS	1	/* poll status beक्रमe control */

बाह्य व्योम rndis_status(काष्ठा usbnet *dev, काष्ठा urb *urb);
बाह्य पूर्णांक
rndis_command(काष्ठा usbnet *dev, काष्ठा rndis_msg_hdr *buf, पूर्णांक buflen);
बाह्य पूर्णांक
generic_rndis_bind(काष्ठा usbnet *dev, काष्ठा usb_पूर्णांकerface *पूर्णांकf, पूर्णांक flags);
बाह्य व्योम rndis_unbind(काष्ठा usbnet *dev, काष्ठा usb_पूर्णांकerface *पूर्णांकf);
बाह्य पूर्णांक rndis_rx_fixup(काष्ठा usbnet *dev, काष्ठा sk_buff *skb);
बाह्य काष्ठा sk_buff *
rndis_tx_fixup(काष्ठा usbnet *dev, काष्ठा sk_buff *skb, gfp_t flags);

#पूर्ण_अगर	/* __LINUX_USB_RNDIS_HOST_H */
