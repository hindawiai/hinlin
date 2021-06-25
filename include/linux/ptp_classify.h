<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * PTP 1588 support
 *
 * This file implements a BPF that recognizes PTP event messages.
 *
 * Copyright (C) 2010 OMICRON electronics GmbH
 */

#अगर_अघोषित _PTP_CLASSIFY_H_
#घोषणा _PTP_CLASSIFY_H_

#समावेश <linux/ip.h>
#समावेश <linux/skbuff.h>

#घोषणा PTP_CLASS_NONE  0x00 /* not a PTP event message */
#घोषणा PTP_CLASS_V1    0x01 /* protocol version 1 */
#घोषणा PTP_CLASS_V2    0x02 /* protocol version 2 */
#घोषणा PTP_CLASS_VMASK 0x0f /* max protocol version is 15 */
#घोषणा PTP_CLASS_IPV4  0x10 /* event in an IPV4 UDP packet */
#घोषणा PTP_CLASS_IPV6  0x20 /* event in an IPV6 UDP packet */
#घोषणा PTP_CLASS_L2    0x40 /* event in a L2 packet */
#घोषणा PTP_CLASS_PMASK	0x70 /* mask क्रम the packet type field */
#घोषणा PTP_CLASS_VLAN	0x80 /* event in a VLAN tagged packet */

#घोषणा PTP_CLASS_V1_IPV4 (PTP_CLASS_V1 | PTP_CLASS_IPV4)
#घोषणा PTP_CLASS_V1_IPV6 (PTP_CLASS_V1 | PTP_CLASS_IPV6) /* probably DNE */
#घोषणा PTP_CLASS_V2_IPV4 (PTP_CLASS_V2 | PTP_CLASS_IPV4)
#घोषणा PTP_CLASS_V2_IPV6 (PTP_CLASS_V2 | PTP_CLASS_IPV6)
#घोषणा PTP_CLASS_V2_L2   (PTP_CLASS_V2 | PTP_CLASS_L2)
#घोषणा PTP_CLASS_V2_VLAN (PTP_CLASS_V2 | PTP_CLASS_VLAN)
#घोषणा PTP_CLASS_L4      (PTP_CLASS_IPV4 | PTP_CLASS_IPV6)

#घोषणा PTP_MSGTYPE_SYNC        0x0
#घोषणा PTP_MSGTYPE_DELAY_REQ   0x1
#घोषणा PTP_MSGTYPE_PDELAY_REQ  0x2
#घोषणा PTP_MSGTYPE_PDELAY_RESP 0x3

#घोषणा PTP_EV_PORT 319
#घोषणा PTP_GEN_BIT 0x08 /* indicates general message, अगर set in message type */

#घोषणा OFF_PTP_SOURCE_UUID	22 /* PTPv1 only */
#घोषणा OFF_PTP_SEQUENCE_ID	30

/* Below defines should actually be हटाओd at some poपूर्णांक in समय. */
#घोषणा IP6_HLEN	40
#घोषणा UDP_HLEN	8
#घोषणा OFF_IHL		14
#घोषणा IPV4_HLEN(data) (((काष्ठा iphdr *)(data + OFF_IHL))->ihl << 2)

काष्ठा घड़ी_identity अणु
	u8 id[8];
पूर्ण __packed;

काष्ठा port_identity अणु
	काष्ठा घड़ी_identity	घड़ी_identity;
	__be16			port_number;
पूर्ण __packed;

काष्ठा ptp_header अणु
	u8			tsmt;  /* transportSpecअगरic | messageType */
	u8			ver;   /* reserved          | versionPTP  */
	__be16			message_length;
	u8			करोमुख्य_number;
	u8			reserved1;
	u8			flag_field[2];
	__be64			correction;
	__be32			reserved2;
	काष्ठा port_identity	source_port_identity;
	__be16			sequence_id;
	u8			control;
	u8			log_message_पूर्णांकerval;
पूर्ण __packed;

#अगर defined(CONFIG_NET_PTP_CLASSIFY)
/**
 * ptp_classअगरy_raw - classअगरy a PTP packet
 * @skb: buffer
 *
 * Runs a minimal BPF dissector to classअगरy a network packet to
 * determine the PTP class. In हाल the skb करोes not contain any
 * PTP protocol data, PTP_CLASS_NONE will be वापसed, otherwise
 * PTP_CLASS_V1_IPVअणु4,6पूर्ण, PTP_CLASS_V2_IPVअणु4,6पूर्ण or
 * PTP_CLASS_V2_अणुL2,VLANपूर्ण, depending on the packet content.
 */
अचिन्हित पूर्णांक ptp_classअगरy_raw(स्थिर काष्ठा sk_buff *skb);

/**
 * ptp_parse_header - Get poपूर्णांकer to the PTP v2 header
 * @skb: packet buffer
 * @type: type of the packet (see ptp_classअगरy_raw())
 *
 * This function takes care of the VLAN, UDP, IPv4 and IPv6 headers. The length
 * is checked.
 *
 * Note, पूर्णांकernally skb_mac_header() is used. Make sure that the @skb is
 * initialized accordingly.
 *
 * Return: Poपूर्णांकer to the ptp v2 header or शून्य अगर not found
 */
काष्ठा ptp_header *ptp_parse_header(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक type);

/**
 * ptp_get_msgtype - Extract ptp message type from given header
 * @hdr: ptp header
 * @type: type of the packet (see ptp_classअगरy_raw())
 *
 * This function वापसs the message type क्रम a given ptp header. It takes care
 * of the dअगरferent ptp header versions (v1 or v2).
 *
 * Return: The message type
 */
अटल अंतरभूत u8 ptp_get_msgtype(स्थिर काष्ठा ptp_header *hdr,
				 अचिन्हित पूर्णांक type)
अणु
	u8 msgtype;

	अगर (unlikely(type & PTP_CLASS_V1)) अणु
		/* msg type is located at the control field क्रम ptp v1 */
		msgtype = hdr->control;
	पूर्ण अन्यथा अणु
		msgtype = hdr->tsmt & 0x0f;
	पूर्ण

	वापस msgtype;
पूर्ण

व्योम __init ptp_classअगरier_init(व्योम);
#अन्यथा
अटल अंतरभूत व्योम ptp_classअगरier_init(व्योम)
अणु
पूर्ण
अटल अंतरभूत अचिन्हित पूर्णांक ptp_classअगरy_raw(काष्ठा sk_buff *skb)
अणु
	वापस PTP_CLASS_NONE;
पूर्ण
अटल अंतरभूत काष्ठा ptp_header *ptp_parse_header(काष्ठा sk_buff *skb,
						  अचिन्हित पूर्णांक type)
अणु
	वापस शून्य;
पूर्ण
अटल अंतरभूत u8 ptp_get_msgtype(स्थिर काष्ठा ptp_header *hdr,
				 अचिन्हित पूर्णांक type)
अणु
	/* The वापस is meaningless. The stub function would not be
	 * executed since no available header from ptp_parse_header.
	 */
	वापस PTP_MSGTYPE_SYNC;
पूर्ण
#पूर्ण_अगर
#पूर्ण_अगर /* _PTP_CLASSIFY_H_ */
