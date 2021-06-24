<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 *  Copyright IBM Corp. 2001, 2006
 *  Author(s): Robert Burroughs
 *	       Eric Rossman (edrossma@us.ibm.com)
 *
 *  Hotplug & misc device support: Jochen Roehrig (roehrig@de.ibm.com)
 *  Major cleanup & driver split: Martin Schwidefsky <schwidefsky@de.ibm.com>
 */

#अगर_अघोषित _ZCRYPT_ERROR_H_
#घोषणा _ZCRYPT_ERROR_H_

#समावेश <linux/atomic.h>
#समावेश "zcrypt_debug.h"
#समावेश "zcrypt_api.h"
#समावेश "zcrypt_msgtype6.h"

/**
 * Reply Messages
 *
 * Error reply messages are of two types:
 *    82:  Error (see below)
 *    88:  Error (see below)
 * Both type 82 and type 88 have the same काष्ठाure in the header.
 *
 * Request reply messages are of three known types:
 *    80:  Reply from a Type 50 Request (see CEX2A-RELATED STRUCTS)
 *    84:  Reply from a Type 4 Request (see PCICA-RELATED STRUCTS)
 *    86:  Reply from a Type 6 Request (see PCICC/PCIXCC/CEX2C-RELATED STRUCTS)
 *
 */
काष्ठा error_hdr अणु
	अचिन्हित अक्षर reserved1;	/* 0x00			*/
	अचिन्हित अक्षर type;		/* 0x82 or 0x88		*/
	अचिन्हित अक्षर reserved2[2];	/* 0x0000		*/
	अचिन्हित अक्षर reply_code;	/* reply code		*/
	अचिन्हित अक्षर reserved3[3];	/* 0x000000		*/
पूर्ण;

#घोषणा TYPE82_RSP_CODE 0x82
#घोषणा TYPE88_RSP_CODE 0x88

#घोषणा REP82_ERROR_MACHINE_FAILURE	    0x10
#घोषणा REP82_ERROR_PREEMPT_FAILURE	    0x12
#घोषणा REP82_ERROR_CHECKPT_FAILURE	    0x14
#घोषणा REP82_ERROR_MESSAGE_TYPE	    0x20
#घोषणा REP82_ERROR_INVALID_COMM_CD	    0x21 /* Type 84	*/
#घोषणा REP82_ERROR_INVALID_MSG_LEN	    0x23
#घोषणा REP82_ERROR_RESERVD_FIELD	    0x24 /* was 0x50	*/
#घोषणा REP82_ERROR_FORMAT_FIELD	    0x29
#घोषणा REP82_ERROR_INVALID_COMMAND	    0x30
#घोषणा REP82_ERROR_MALFORMED_MSG	    0x40
#घोषणा REP82_ERROR_INVALID_SPECIAL_CMD	    0x41
#घोषणा REP82_ERROR_RESERVED_FIELDO	    0x50 /* old value	*/
#घोषणा REP82_ERROR_WORD_ALIGNMENT	    0x60
#घोषणा REP82_ERROR_MESSAGE_LENGTH	    0x80
#घोषणा REP82_ERROR_OPERAND_INVALID	    0x82
#घोषणा REP82_ERROR_OPERAND_SIZE	    0x84
#घोषणा REP82_ERROR_EVEN_MOD_IN_OPND	    0x85
#घोषणा REP82_ERROR_RESERVED_FIELD	    0x88
#घोषणा REP82_ERROR_INVALID_DOMAIN_PENDING  0x8A
#घोषणा REP82_ERROR_FILTERED_BY_HYPERVISOR  0x8B
#घोषणा REP82_ERROR_TRANSPORT_FAIL	    0x90
#घोषणा REP82_ERROR_PACKET_TRUNCATED	    0xA0
#घोषणा REP82_ERROR_ZERO_BUFFER_LEN	    0xB0

#घोषणा REP88_ERROR_MODULE_FAILURE	    0x10
#घोषणा REP88_ERROR_MESSAGE_TYPE	    0x20
#घोषणा REP88_ERROR_MESSAGE_MALFORMD	    0x22
#घोषणा REP88_ERROR_MESSAGE_LENGTH	    0x23
#घोषणा REP88_ERROR_RESERVED_FIELD	    0x24
#घोषणा REP88_ERROR_KEY_TYPE		    0x34
#घोषणा REP88_ERROR_INVALID_KEY	    0x82 /* CEX2A	*/
#घोषणा REP88_ERROR_OPERAND		    0x84 /* CEX2A	*/
#घोषणा REP88_ERROR_OPERAND_EVEN_MOD	    0x85 /* CEX2A	*/

अटल अंतरभूत पूर्णांक convert_error(काष्ठा zcrypt_queue *zq,
				काष्ठा ap_message *reply)
अणु
	काष्ठा error_hdr *ehdr = reply->msg;
	पूर्णांक card = AP_QID_CARD(zq->queue->qid);
	पूर्णांक queue = AP_QID_QUEUE(zq->queue->qid);

	चयन (ehdr->reply_code) अणु
	हाल REP82_ERROR_INVALID_MSG_LEN:	 /* 0x23 */
	हाल REP82_ERROR_RESERVD_FIELD:		 /* 0x24 */
	हाल REP82_ERROR_FORMAT_FIELD:		 /* 0x29 */
	हाल REP82_ERROR_MALFORMED_MSG:		 /* 0x40 */
	हाल REP82_ERROR_INVALID_SPECIAL_CMD:	 /* 0x41 */
	हाल REP82_ERROR_MESSAGE_LENGTH:	 /* 0x80 */
	हाल REP82_ERROR_OPERAND_INVALID:	 /* 0x82 */
	हाल REP82_ERROR_OPERAND_SIZE:		 /* 0x84 */
	हाल REP82_ERROR_EVEN_MOD_IN_OPND:	 /* 0x85 */
	हाल REP82_ERROR_INVALID_DOMAIN_PENDING: /* 0x8A */
	हाल REP82_ERROR_FILTERED_BY_HYPERVISOR: /* 0x8B */
	हाल REP82_ERROR_PACKET_TRUNCATED:	 /* 0xA0 */
	हाल REP88_ERROR_MESSAGE_MALFORMD:	 /* 0x22 */
	हाल REP88_ERROR_KEY_TYPE:		 /* 0x34 */
		/* RY indicates malक्रमmed request */
		ZCRYPT_DBF(DBF_WARN,
			   "dev=%02x.%04x RY=0x%02x => rc=EINVAL\n",
			   card, queue, ehdr->reply_code);
		वापस -EINVAL;
	हाल REP82_ERROR_MACHINE_FAILURE:	 /* 0x10 */
	हाल REP82_ERROR_MESSAGE_TYPE:		 /* 0x20 */
	हाल REP82_ERROR_TRANSPORT_FAIL:	 /* 0x90 */
		/*
		 * Msg to wrong type or card/infraकाष्ठाure failure.
		 * Trigger rescan of the ap bus, trigger retry request.
		 */
		atomic_set(&zcrypt_rescan_req, 1);
		/* For type 86 response show the apfs value (failure reason) */
		अगर (ehdr->reply_code == REP82_ERROR_TRANSPORT_FAIL &&
		    ehdr->type == TYPE86_RSP_CODE) अणु
			काष्ठा अणु
				काष्ठा type86_hdr hdr;
				काष्ठा type86_fmt2_ext fmt2;
			पूर्ण __packed * head = reply->msg;
			अचिन्हित पूर्णांक apfs = *((u32 *)head->fmt2.apfs);

			ZCRYPT_DBF(DBF_WARN,
				   "dev=%02x.%04x RY=0x%02x apfs=0x%x => bus rescan, rc=EAGAIN\n",
				   card, queue, ehdr->reply_code, apfs);
		पूर्ण अन्यथा
			ZCRYPT_DBF(DBF_WARN,
				   "dev=%02x.%04x RY=0x%02x => bus rescan, rc=EAGAIN\n",
				   card, queue, ehdr->reply_code);
		वापस -EAGAIN;
	शेष:
		/* Assume request is valid and a retry will be worth it */
		ZCRYPT_DBF(DBF_WARN,
			   "dev=%02x.%04x RY=0x%02x => rc=EAGAIN\n",
			   card, queue, ehdr->reply_code);
		वापस -EAGAIN;
	पूर्ण
पूर्ण

#पूर्ण_अगर /* _ZCRYPT_ERROR_H_ */
