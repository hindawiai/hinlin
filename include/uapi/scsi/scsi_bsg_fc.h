<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ WITH Linux-syscall-note */
/*
 *  FC Transport BSG Interface
 *
 *  Copyright (C) 2008   James Smart, Emulex Corporation
 */

#अगर_अघोषित SCSI_BSG_FC_H
#घोषणा SCSI_BSG_FC_H

#समावेश <linux/types.h>

/*
 * This file पूर्णांकended to be included by both kernel and user space
 */

/*
 * FC Transport SGIO v4 BSG Message Support
 */

/* Default BSG request समयout (in seconds) */
#घोषणा FC_DEFAULT_BSG_TIMEOUT		(10 * HZ)


/*
 * Request Message Codes supported by the FC Transport
 */

/* define the class masks क्रम the message codes */
#घोषणा FC_BSG_CLS_MASK		0xF0000000	/* find object class */
#घोषणा FC_BSG_HST_MASK		0x80000000	/* fc host class */
#घोषणा FC_BSG_RPT_MASK		0x40000000	/* fc rport class */

	/* fc_host Message Codes */
#घोषणा FC_BSG_HST_ADD_RPORT		(FC_BSG_HST_MASK | 0x00000001)
#घोषणा FC_BSG_HST_DEL_RPORT		(FC_BSG_HST_MASK | 0x00000002)
#घोषणा FC_BSG_HST_ELS_NOLOGIN		(FC_BSG_HST_MASK | 0x00000003)
#घोषणा FC_BSG_HST_CT			(FC_BSG_HST_MASK | 0x00000004)
#घोषणा FC_BSG_HST_VENDOR		(FC_BSG_HST_MASK | 0x000000FF)

	/* fc_rport Message Codes */
#घोषणा FC_BSG_RPT_ELS			(FC_BSG_RPT_MASK | 0x00000001)
#घोषणा FC_BSG_RPT_CT			(FC_BSG_RPT_MASK | 0x00000002)



/*
 * FC Address Identअगरiers in Message Structures :
 *
 *   Whenever a command payload contains a FC Address Identअगरier
 *   (aka port_id), the value is effectively in big-endian
 *   order, thus the array elements are decoded as follows:
 *     element [0] is bits 23:16 of the FC Address Identअगरier
 *     element [1] is bits 15:8 of the FC Address Identअगरier
 *     element [2] is bits 7:0 of the FC Address Identअगरier
 */


/*
 * FC Host Messages
 */

/* FC_BSG_HST_ADDR_PORT : */

/* Request:
 * This message requests the FC host to login to the remote port
 * at the specअगरied N_Port_Id.  The remote port is to be क्रमागतerated
 * with the transport upon completion of the login.
 */
काष्ठा fc_bsg_host_add_rport अणु
	__u8	reserved;

	/* FC Address Identier of the remote port to login to */
	__u8	port_id[3];
पूर्ण;

/* Response:
 * There is no additional response data - fc_bsg_reply->result is sufficient
 */


/* FC_BSG_HST_DEL_RPORT : */

/* Request:
 * This message requests the FC host to हटाओ an क्रमागतerated
 * remote port and to terminate the login to it.
 *
 * Note: The driver is मुक्त to reject this request अगर it desires to
 * reमुख्य logged in with the remote port.
 */
काष्ठा fc_bsg_host_del_rport अणु
	__u8	reserved;

	/* FC Address Identier of the remote port to logout of */
	__u8	port_id[3];
पूर्ण;

/* Response:
 * There is no additional response data - fc_bsg_reply->result is sufficient
 */


/* FC_BSG_HST_ELS_NOLOGIN : */

/* Request:
 * This message requests the FC_Host to send an ELS to a specअगरic
 * N_Port_ID. The host करोes not need to log पूर्णांकo the remote port,
 * nor करोes it need to क्रमागतerate the rport क्रम further traffic
 * (although, the FC host is मुक्त to करो so अगर it desires).
 */
काष्ठा fc_bsg_host_els अणु
	/*
	 * ELS Command Code being sent (must be the same as byte 0
	 * of the payload)
	 */
	__u8	command_code;

	/* FC Address Identier of the remote port to send the ELS to */
	__u8	port_id[3];
पूर्ण;

/* Response:
 */
/* fc_bsg_ctels_reply->status values */
#घोषणा FC_CTELS_STATUS_OK	0x00000000
#घोषणा FC_CTELS_STATUS_REJECT	0x00000001
#घोषणा FC_CTELS_STATUS_P_RJT	0x00000002
#घोषणा FC_CTELS_STATUS_F_RJT	0x00000003
#घोषणा FC_CTELS_STATUS_P_BSY	0x00000004
#घोषणा FC_CTELS_STATUS_F_BSY	0x00000006
काष्ठा fc_bsg_ctels_reply अणु
	/*
	 * Note: An ELS LS_RJT may be reported in 2 ways:
	 *  a) A status of FC_CTELS_STATUS_OK is वापसed. The caller
	 *     is to look पूर्णांकo the ELS receive payload to determine
	 *     LS_ACC or LS_RJT (by contents of word 0). The reject
	 *     data will be in word 1.
	 *  b) A status of FC_CTELS_STATUS_REJECT is वापसed, The
	 *     rjt_data field will contain valid data.
	 *
	 * Note: ELS LS_ACC is determined by an FC_CTELS_STATUS_OK, and
	 *   the receive payload word 0 indicates LS_ACC
	 *   (e.g. value is 0x02xxxxxx).
	 *
	 * Note: Similarly, a CT Reject may be reported in 2 ways:
	 *  a) A status of FC_CTELS_STATUS_OK is वापसed. The caller
	 *     is to look पूर्णांकo the CT receive payload to determine
	 *     Accept or Reject (by contents of word 2). The reject
	 *     data will be in word 3.
	 *  b) A status of FC_CTELS_STATUS_REJECT is वापसed, The
	 *     rjt_data field will contain valid data.
	 *
	 * Note: x_RJT/BSY status will indicae that the rjt_data field
	 *   is valid and contains the reason/explanation values.
	 */
	__u32	status;		/* See FC_CTELS_STATUS_xxx */

	/* valid अगर status is not FC_CTELS_STATUS_OK */
	काष्ठा	अणु
		__u8	action;		/* fragment_id क्रम CT REJECT */
		__u8	reason_code;
		__u8	reason_explanation;
		__u8	venकरोr_unique;
	पूर्ण rjt_data;
पूर्ण;


/* FC_BSG_HST_CT : */

/* Request:
 * This message requests that a CT Request be perक्रमmed with the
 * indicated N_Port_ID. The driver is responsible क्रम logging in with
 * the fabric and/or N_Port_ID, etc as per FC rules. This request करोes
 * not mandate that the driver must क्रमागतerate the destination in the
 * transport. The driver is allowed to decide whether to क्रमागतerate it,
 * and whether to tear it करोwn after the request.
 */
काष्ठा fc_bsg_host_ct अणु
	__u8	reserved;

	/* FC Address Identier of the remote port to send the ELS to */
	__u8	port_id[3];

	/*
	 * We need words 0-2 of the generic preamble क्रम the LLD's
	 */
	__u32	preamble_word0;	/* revision & IN_ID */
	__u32	preamble_word1;	/* GS_Type, GS_SubType, Options, Rsvd */
	__u32	preamble_word2;	/* Cmd Code, Max Size */

पूर्ण;
/* Response:
 *
 * The reply काष्ठाure is an fc_bsg_ctels_reply काष्ठाure
 */


/* FC_BSG_HST_VENDOR : */

/* Request:
 * Note: When specअगरying venकरोr_id, be sure to पढ़ो the Venकरोr Type and ID
 *   क्रमmatting requirements specअगरied in scsi_netlink.h
 */
काष्ठा fc_bsg_host_venकरोr अणु
	/*
	 * Identअगरies the venकरोr that the message is क्रमmatted क्रम. This
	 * should be the recipient of the message.
	 */
	__u64 venकरोr_id;

	/* start of venकरोr command area */
	__u32 venकरोr_cmd[0];
पूर्ण;

/* Response:
 */
काष्ठा fc_bsg_host_venकरोr_reply अणु
	/* start of venकरोr response area */
	__u32 venकरोr_rsp[0];
पूर्ण;



/*
 * FC Remote Port Messages
 */

/* FC_BSG_RPT_ELS : */

/* Request:
 * This message requests that an ELS be perक्रमmed with the rport.
 */
काष्ठा fc_bsg_rport_els अणु
	/*
	 * ELS Command Code being sent (must be the same as
	 * byte 0 of the payload)
	 */
	__u8 els_code;
पूर्ण;

/* Response:
 *
 * The reply काष्ठाure is an fc_bsg_ctels_reply काष्ठाure
 */


/* FC_BSG_RPT_CT : */

/* Request:
 * This message requests that a CT Request be perक्रमmed with the rport.
 */
काष्ठा fc_bsg_rport_ct अणु
	/*
	 * We need words 0-2 of the generic preamble क्रम the LLD's
	 */
	__u32	preamble_word0;	/* revision & IN_ID */
	__u32	preamble_word1;	/* GS_Type, GS_SubType, Options, Rsvd */
	__u32	preamble_word2;	/* Cmd Code, Max Size */
पूर्ण;
/* Response:
 *
 * The reply काष्ठाure is an fc_bsg_ctels_reply काष्ठाure
 */




/* request (CDB) काष्ठाure of the sg_io_v4 */
काष्ठा fc_bsg_request अणु
	__u32 msgcode;
	जोड़ अणु
		काष्ठा fc_bsg_host_add_rport	h_addrport;
		काष्ठा fc_bsg_host_del_rport	h_delrport;
		काष्ठा fc_bsg_host_els		h_els;
		काष्ठा fc_bsg_host_ct		h_ct;
		काष्ठा fc_bsg_host_venकरोr	h_venकरोr;

		काष्ठा fc_bsg_rport_els		r_els;
		काष्ठा fc_bsg_rport_ct		r_ct;
	पूर्ण rqst_data;
पूर्ण __attribute__((packed));


/* response (request sense data) काष्ठाure of the sg_io_v4 */
काष्ठा fc_bsg_reply अणु
	/*
	 * The completion result. Result exists in two क्रमms:
	 *  अगर negative, it is an -Exxx प्रणाली त्रुटि_सं value. There will
	 *    be no further reply inक्रमmation supplied.
	 *  अन्यथा, it's the 4-byte scsi error result, with driver, host,
	 *    msg and status fields. The per-msgcode reply काष्ठाure
	 *    will contain valid data.
	 */
	__u32 result;

	/* If there was reply_payload, how much was recevied ? */
	__u32 reply_payload_rcv_len;

	जोड़ अणु
		काष्ठा fc_bsg_host_venकरोr_reply		venकरोr_reply;

		काष्ठा fc_bsg_ctels_reply		ctels_reply;
	पूर्ण reply_data;
पूर्ण;


#पूर्ण_अगर /* SCSI_BSG_FC_H */

