<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 *  Copyright IBM Corp. 2001, 2012
 *  Author(s): Robert Burroughs
 *	       Eric Rossman (edrossma@us.ibm.com)
 *
 *  Hotplug & misc device support: Jochen Roehrig (roehrig@de.ibm.com)
 *  Major cleanup & driver split: Martin Schwidefsky <schwidefsky@de.ibm.com>
 *  MSGTYPE reकाष्ठा:		  Holger Dengler <hd@linux.vnet.ibm.com>
 */

#अगर_अघोषित _ZCRYPT_MSGTYPE6_H_
#घोषणा _ZCRYPT_MSGTYPE6_H_

#समावेश <यंत्र/zcrypt.h>

#घोषणा MSGTYPE06_NAME			"zcrypt_msgtype6"
#घोषणा MSGTYPE06_VARIANT_DEFAULT	0
#घोषणा MSGTYPE06_VARIANT_NORNG		1
#घोषणा MSGTYPE06_VARIANT_EP11		2

#घोषणा MSGTYPE06_MAX_MSG_SIZE		(12*1024)

/**
 * The type 6 message family is associated with CEXxC/CEXxP cards.
 *
 * It contains a message header followed by a CPRB, both of which
 * are described below.
 *
 * Note that all reserved fields must be zeroes.
 */
काष्ठा type6_hdr अणु
	अचिन्हित अक्षर reserved1;	/* 0x00				*/
	अचिन्हित अक्षर type;		/* 0x06				*/
	अचिन्हित अक्षर reserved2[2];	/* 0x0000			*/
	अचिन्हित अक्षर right[4];		/* 0x00000000			*/
	अचिन्हित अक्षर reserved3[2];	/* 0x0000			*/
	अचिन्हित अक्षर reserved4[2];	/* 0x0000			*/
	अचिन्हित अक्षर apfs[4];		/* 0x00000000			*/
	अचिन्हित पूर्णांक  offset1;		/* 0x00000058 (offset to CPRB)	*/
	अचिन्हित पूर्णांक  offset2;		/* 0x00000000			*/
	अचिन्हित पूर्णांक  offset3;		/* 0x00000000			*/
	अचिन्हित पूर्णांक  offset4;		/* 0x00000000			*/
	अचिन्हित अक्षर agent_id[16];	/* 0x4341000000000000		*/
					/* 0x0000000000000000		*/
	अचिन्हित अक्षर rqid[2];		/* rqid.  पूर्णांकernal to 603	*/
	अचिन्हित अक्षर reserved5[2];	/* 0x0000			*/
	अचिन्हित अक्षर function_code[2];	/* क्रम PKD, 0x5044 (ascii 'PD')	*/
	अचिन्हित अक्षर reserved6[2];	/* 0x0000			*/
	अचिन्हित पूर्णांक  ToCardLen1;	/* (request CPRB len + 3) & -4	*/
	अचिन्हित पूर्णांक  ToCardLen2;	/* db len 0x00000000 क्रम PKD	*/
	अचिन्हित पूर्णांक  ToCardLen3;	/* 0x00000000			*/
	अचिन्हित पूर्णांक  ToCardLen4;	/* 0x00000000			*/
	अचिन्हित पूर्णांक  FromCardLen1;	/* response buffer length	*/
	अचिन्हित पूर्णांक  FromCardLen2;	/* db len 0x00000000 क्रम PKD	*/
	अचिन्हित पूर्णांक  FromCardLen3;	/* 0x00000000			*/
	अचिन्हित पूर्णांक  FromCardLen4;	/* 0x00000000			*/
पूर्ण __packed;

/**
 * The type 86 message family is associated with CEXxC/CEXxP cards.
 *
 * It contains a message header followed by a CPRB.  The CPRB is
 * the same as the request CPRB, which is described above.
 *
 * If क्रमmat is 1, an error condition exists and no data beyond
 * the 8-byte message header is of पूर्णांकerest.
 *
 * The non-error message is shown below.
 *
 * Note that all reserved fields must be zeroes.
 */
काष्ठा type86_hdr अणु
	अचिन्हित अक्षर reserved1;	/* 0x00				*/
	अचिन्हित अक्षर type;		/* 0x86				*/
	अचिन्हित अक्षर क्रमmat;		/* 0x01 (error) or 0x02 (ok)	*/
	अचिन्हित अक्षर reserved2;	/* 0x00				*/
	अचिन्हित अक्षर reply_code;	/* reply code (see above)	*/
	अचिन्हित अक्षर reserved3[3];	/* 0x000000			*/
पूर्ण __packed;

#घोषणा TYPE86_RSP_CODE 0x86
#घोषणा TYPE87_RSP_CODE 0x87
#घोषणा TYPE86_FMT2	0x02

काष्ठा type86_fmt2_ext अणु
	अचिन्हित अक्षर	  reserved[4];	/* 0x00000000			*/
	अचिन्हित अक्षर	  apfs[4];	/* final status			*/
	अचिन्हित पूर्णांक	  count1;	/* length of CPRB + parameters	*/
	अचिन्हित पूर्णांक	  offset1;	/* offset to CPRB		*/
	अचिन्हित पूर्णांक	  count2;	/* 0x00000000			*/
	अचिन्हित पूर्णांक	  offset2;	/* db offset 0x00000000 क्रम PKD	*/
	अचिन्हित पूर्णांक	  count3;	/* 0x00000000			*/
	अचिन्हित पूर्णांक	  offset3;	/* 0x00000000			*/
	अचिन्हित पूर्णांक	  count4;	/* 0x00000000			*/
	अचिन्हित पूर्णांक	  offset4;	/* 0x00000000			*/
पूर्ण __packed;

अचिन्हित पूर्णांक get_cprb_fc(bool userspace, काष्ठा ica_xcRB *, काष्ठा ap_message *,
			 अचिन्हित पूर्णांक *, अचिन्हित लघु **);
अचिन्हित पूर्णांक get_ep11cprb_fc(bool userspace, काष्ठा ep11_urb *, काष्ठा ap_message *,
			     अचिन्हित पूर्णांक *);
अचिन्हित पूर्णांक get_rng_fc(काष्ठा ap_message *, पूर्णांक *, अचिन्हित पूर्णांक *);

#घोषणा LOW	10
#घोषणा MEDIUM	100
#घोषणा HIGH	500

पूर्णांक speed_idx_cca(पूर्णांक);
पूर्णांक speed_idx_ep11(पूर्णांक);

/**
 * Prepare a type6 CPRB message क्रम अक्रमom number generation
 *
 * @ap_dev: AP device poपूर्णांकer
 * @ap_msg: poपूर्णांकer to AP message
 */
अटल अंतरभूत व्योम rng_type6CPRB_msgX(काष्ठा ap_message *ap_msg,
				      अचिन्हित पूर्णांक अक्रमom_number_length,
				      अचिन्हित पूर्णांक *करोमुख्य)
अणु
	काष्ठा अणु
		काष्ठा type6_hdr hdr;
		काष्ठा CPRBX cprbx;
		अक्षर function_code[2];
		लघु पूर्णांक rule_length;
		अक्षर rule[8];
		लघु पूर्णांक verb_length;
		लघु पूर्णांक key_length;
	पूर्ण __packed * msg = ap_msg->msg;
	अटल काष्ठा type6_hdr अटल_type6_hdrX = अणु
		.type		= 0x06,
		.offset1	= 0x00000058,
		.agent_id	= अणु'C', 'A'पूर्ण,
		.function_code	= अणु'R', 'L'पूर्ण,
		.ToCardLen1	= माप(*msg) - माप(msg->hdr),
		.FromCardLen1	= माप(*msg) - माप(msg->hdr),
	पूर्ण;
	अटल काष्ठा CPRBX local_cprbx = अणु
		.cprb_len	= 0x00dc,
		.cprb_ver_id	= 0x02,
		.func_id	= अणु0x54, 0x32पूर्ण,
		.req_parml	= माप(*msg) - माप(msg->hdr) -
				  माप(msg->cprbx),
		.rpl_msgbl	= माप(*msg) - माप(msg->hdr),
	पूर्ण;

	msg->hdr = अटल_type6_hdrX;
	msg->hdr.FromCardLen2 = अक्रमom_number_length,
	msg->cprbx = local_cprbx;
	msg->cprbx.rpl_datal = अक्रमom_number_length,
	स_नकल(msg->function_code, msg->hdr.function_code, 0x02);
	msg->rule_length = 0x0a;
	स_नकल(msg->rule, "RANDOM  ", 8);
	msg->verb_length = 0x02;
	msg->key_length = 0x02;
	ap_msg->len = माप(*msg);
	*करोमुख्य = (अचिन्हित लघु)msg->cprbx.करोमुख्य;
पूर्ण

व्योम zcrypt_msgtype6_init(व्योम);
व्योम zcrypt_msgtype6_निकास(व्योम);

#पूर्ण_अगर /* _ZCRYPT_MSGTYPE6_H_ */
