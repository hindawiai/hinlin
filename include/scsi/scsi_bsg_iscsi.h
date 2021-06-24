<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *  iSCSI Transport BSG Interface
 *
 *  Copyright (C) 2009   James Smart, Emulex Corporation
 */

#अगर_अघोषित SCSI_BSG_ISCSI_H
#घोषणा SCSI_BSG_ISCSI_H

/*
 * This file पूर्णांकended to be included by both kernel and user space
 */

#समावेश <scsi/scsi.h>

/*
 * iSCSI Transport SGIO v4 BSG Message Support
 */

/* Default BSG request समयout (in seconds) */
#घोषणा ISCSI_DEFAULT_BSG_TIMEOUT      (10 * HZ)


/*
 * Request Message Codes supported by the iSCSI Transport
 */

/* define the class masks क्रम the message codes */
#घोषणा ISCSI_BSG_CLS_MASK     0xF0000000      /* find object class */
#घोषणा ISCSI_BSG_HST_MASK     0x80000000      /* iscsi host class */

/* iscsi host Message Codes */
#घोषणा ISCSI_BSG_HST_VENDOR           (ISCSI_BSG_HST_MASK | 0x000000FF)


/*
 * iSCSI Host Messages
 */

/* ISCSI_BSG_HST_VENDOR : */

/* Request:
 * Note: When specअगरying venकरोr_id, be sure to पढ़ो the Venकरोr Type and ID
 *   क्रमmatting requirements specअगरied in scsi_netlink.h
 */
काष्ठा iscsi_bsg_host_venकरोr अणु
	/*
	 * Identअगरies the venकरोr that the message is क्रमmatted क्रम. This
	 * should be the recipient of the message.
	 */
	uपूर्णांक64_t venकरोr_id;

	/* start of venकरोr command area */
	uपूर्णांक32_t venकरोr_cmd[];
पूर्ण;

/* Response:
 */
काष्ठा iscsi_bsg_host_venकरोr_reply अणु
	/* start of venकरोr response area */
	uपूर्णांक32_t venकरोr_rsp[0];
पूर्ण;


/* request (CDB) काष्ठाure of the sg_io_v4 */
काष्ठा iscsi_bsg_request अणु
	uपूर्णांक32_t msgcode;
	जोड़ अणु
		काष्ठा iscsi_bsg_host_venकरोr    h_venकरोr;
	पूर्ण rqst_data;
पूर्ण __attribute__((packed));


/* response (request sense data) काष्ठाure of the sg_io_v4 */
काष्ठा iscsi_bsg_reply अणु
	/*
	 * The completion result. Result exists in two क्रमms:
	 * अगर negative, it is an -Exxx प्रणाली त्रुटि_सं value. There will
	 * be no further reply inक्रमmation supplied.
	 * अन्यथा, it's the 4-byte scsi error result, with driver, host,
	 * msg and status fields. The per-msgcode reply काष्ठाure
	 * will contain valid data.
	 */
	uपूर्णांक32_t result;

	/* If there was reply_payload, how much was recevied ? */
	uपूर्णांक32_t reply_payload_rcv_len;

	जोड़ अणु
		काष्ठा iscsi_bsg_host_venकरोr_reply      venकरोr_reply;
	पूर्ण reply_data;
पूर्ण;


#पूर्ण_अगर /* SCSI_BSG_ISCSI_H */
