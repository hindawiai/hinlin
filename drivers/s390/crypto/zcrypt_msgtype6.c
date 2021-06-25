<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 *  Copyright IBM Corp. 2001, 2012
 *  Author(s): Robert Burroughs
 *	       Eric Rossman (edrossma@us.ibm.com)
 *
 *  Hotplug & misc device support: Jochen Roehrig (roehrig@de.ibm.com)
 *  Major cleanup & driver split: Martin Schwidefsky <schwidefsky@de.ibm.com>
 *				  Ralph Wuerthner <rwuerthn@de.ibm.com>
 *  MSGTYPE reकाष्ठा:		  Holger Dengler <hd@linux.vnet.ibm.com>
 */

#घोषणा KMSG_COMPONENT "zcrypt"
#घोषणा pr_fmt(fmt) KMSG_COMPONENT ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/err.h>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <linux/atomic.h>
#समावेश <linux/uaccess.h>

#समावेश "ap_bus.h"
#समावेश "zcrypt_api.h"
#समावेश "zcrypt_error.h"
#समावेश "zcrypt_msgtype6.h"
#समावेश "zcrypt_cca_key.h"

#घोषणा CEXXC_MAX_ICA_RESPONSE_SIZE 0x77c /* max size type86 v2 reply	    */

#घोषणा CEIL4(x) ((((x)+3)/4)*4)

काष्ठा response_type अणु
	काष्ठा completion work;
	पूर्णांक type;
पूर्ण;
#घोषणा CEXXC_RESPONSE_TYPE_ICA  0
#घोषणा CEXXC_RESPONSE_TYPE_XCRB 1
#घोषणा CEXXC_RESPONSE_TYPE_EP11 2

MODULE_AUTHOR("IBM Corporation");
MODULE_DESCRIPTION("Cryptographic Coprocessor (message type 6), " \
		   "Copyright IBM Corp. 2001, 2012");
MODULE_LICENSE("GPL");

/**
 * CPRB
 *	  Note that all लघुs, पूर्णांकs and दीर्घs are little-endian.
 *	  All poपूर्णांकer fields are 32-bits दीर्घ, and mean nothing
 *
 *	  A request CPRB is followed by a request_parameter_block.
 *
 *	  The request (or reply) parameter block is organized thus:
 *	    function code
 *	    VUD block
 *	    key block
 */
काष्ठा CPRB अणु
	अचिन्हित लघु cprb_len;	/* CPRB length			 */
	अचिन्हित अक्षर cprb_ver_id;	/* CPRB version id.		 */
	अचिन्हित अक्षर pad_000;		/* Alignment pad byte.		 */
	अचिन्हित अक्षर srpi_rtcode[4];	/* SRPI वापस code LELONG	 */
	अचिन्हित अक्षर srpi_verb;	/* SRPI verb type		 */
	अचिन्हित अक्षर flags;		/* flags			 */
	अचिन्हित अक्षर func_id[2];	/* function id			 */
	अचिन्हित अक्षर checkpoपूर्णांक_flag;	/*				 */
	अचिन्हित अक्षर resv2;		/* reserved			 */
	अचिन्हित लघु req_parml;	/* request parameter buffer	 */
					/* length 16-bit little endian	 */
	अचिन्हित अक्षर req_parmp[4];	/* request parameter buffer	 *
					 * poपूर्णांकer (means nothing: the	 *
					 * parameter buffer follows	 *
					 * the CPRB).			 */
	अचिन्हित अक्षर req_datal[4];	/* request data buffer		 */
					/* length	  ULELONG	 */
	अचिन्हित अक्षर req_datap[4];	/* request data buffer		 */
					/* poपूर्णांकer			 */
	अचिन्हित लघु rpl_parml;	/* reply  parameter buffer	 */
					/* length 16-bit little endian	 */
	अचिन्हित अक्षर pad_001[2];	/* Alignment pad bytes. ULESHORT */
	अचिन्हित अक्षर rpl_parmp[4];	/* reply parameter buffer	 *
					 * poपूर्णांकer (means nothing: the	 *
					 * parameter buffer follows	 *
					 * the CPRB).			 */
	अचिन्हित अक्षर rpl_datal[4];	/* reply data buffer len ULELONG */
	अचिन्हित अक्षर rpl_datap[4];	/* reply data buffer		 */
					/* poपूर्णांकer			 */
	अचिन्हित लघु ccp_rscode;	/* server reason code	ULESHORT */
	अचिन्हित लघु ccp_rtcode;	/* server वापस code	ULESHORT */
	अचिन्हित अक्षर repd_parml[2];	/* replied parameter len ULESHORT*/
	अचिन्हित अक्षर mac_data_len[2];	/* Mac Data Length	ULESHORT */
	अचिन्हित अक्षर repd_datal[4];	/* replied data length	ULELONG	 */
	अचिन्हित अक्षर req_pc[2];	/* PC identअगरier		 */
	अचिन्हित अक्षर res_origin[8];	/* resource origin		 */
	अचिन्हित अक्षर mac_value[8];	/* Mac Value			 */
	अचिन्हित अक्षर logon_id[8];	/* Logon Identअगरier		 */
	अचिन्हित अक्षर usage_करोमुख्य[2];	/* cdx				 */
	अचिन्हित अक्षर resv3[18];	/* reserved क्रम requestor	 */
	अचिन्हित लघु svr_namel;	/* server name length  ULESHORT	 */
	अचिन्हित अक्षर svr_name[8];	/* server name			 */
पूर्ण __packed;

काष्ठा function_and_rules_block अणु
	अचिन्हित अक्षर function_code[2];
	अचिन्हित लघु ulen;
	अचिन्हित अक्षर only_rule[8];
पूर्ण __packed;

/**
 * The following is used to initialize the CPRBX passed to the CEXxC/CEXxP
 * card in a type6 message. The 3 fields that must be filled in at execution
 * समय are  req_parml, rpl_parml and usage_करोमुख्य.
 * Everything about this पूर्णांकerface is ascii/big-endian, since the
 * device करोes *not* have 'Intel inside'.
 *
 * The CPRBX is followed immediately by the parm block.
 * The parm block contains:
 * - function code ('PD' 0x5044 or 'PK' 0x504B)
 * - rule block (one of:)
 *   + 0x000A 'PKCS-1.2' (MCL2 'PD')
 *   + 0x000A 'ZERO-PAD' (MCL2 'PK')
 *   + 0x000A 'ZERO-PAD' (MCL3 'PD' or CEX2C 'PD')
 *   + 0x000A 'MRP     ' (MCL3 'PK' or CEX2C 'PK')
 * - VUD block
 */
अटल स्थिर काष्ठा CPRBX अटल_cprbx = अणु
	.cprb_len	=  0x00DC,
	.cprb_ver_id	=  0x02,
	.func_id	= अणु0x54, 0x32पूर्ण,
पूर्ण;

पूर्णांक speed_idx_cca(पूर्णांक req_type)
अणु
	चयन (req_type) अणु
	हाल 0x4142:
	हाल 0x4149:
	हाल 0x414D:
	हाल 0x4341:
	हाल 0x4344:
	हाल 0x4354:
	हाल 0x4358:
	हाल 0x444B:
	हाल 0x4558:
	हाल 0x4643:
	हाल 0x4651:
	हाल 0x4C47:
	हाल 0x4C4B:
	हाल 0x4C51:
	हाल 0x4F48:
	हाल 0x504F:
	हाल 0x5053:
	हाल 0x5058:
	हाल 0x5343:
	हाल 0x5344:
	हाल 0x5345:
	हाल 0x5350:
		वापस LOW;
	हाल 0x414B:
	हाल 0x4345:
	हाल 0x4349:
	हाल 0x434D:
	हाल 0x4847:
	हाल 0x4849:
	हाल 0x484D:
	हाल 0x4850:
	हाल 0x4851:
	हाल 0x4954:
	हाल 0x4958:
	हाल 0x4B43:
	हाल 0x4B44:
	हाल 0x4B45:
	हाल 0x4B47:
	हाल 0x4B48:
	हाल 0x4B49:
	हाल 0x4B4E:
	हाल 0x4B50:
	हाल 0x4B52:
	हाल 0x4B54:
	हाल 0x4B58:
	हाल 0x4D50:
	हाल 0x4D53:
	हाल 0x4D56:
	हाल 0x4D58:
	हाल 0x5044:
	हाल 0x5045:
	हाल 0x5046:
	हाल 0x5047:
	हाल 0x5049:
	हाल 0x504B:
	हाल 0x504D:
	हाल 0x5254:
	हाल 0x5347:
	हाल 0x5349:
	हाल 0x534B:
	हाल 0x534D:
	हाल 0x5356:
	हाल 0x5358:
	हाल 0x5443:
	हाल 0x544B:
	हाल 0x5647:
		वापस HIGH;
	शेष:
		वापस MEDIUM;
	पूर्ण
पूर्ण

पूर्णांक speed_idx_ep11(पूर्णांक req_type)
अणु
	चयन (req_type) अणु
	हाल  1:
	हाल  2:
	हाल 36:
	हाल 37:
	हाल 38:
	हाल 39:
	हाल 40:
		वापस LOW;
	हाल 17:
	हाल 18:
	हाल 19:
	हाल 20:
	हाल 21:
	हाल 22:
	हाल 26:
	हाल 30:
	हाल 31:
	हाल 32:
	हाल 33:
	हाल 34:
	हाल 35:
		वापस HIGH;
	शेष:
		वापस MEDIUM;
	पूर्ण
पूर्ण


/**
 * Convert a ICAMEX message to a type6 MEX message.
 *
 * @zq: crypto device poपूर्णांकer
 * @ap_msg: poपूर्णांकer to AP message
 * @mex: poपूर्णांकer to user input data
 *
 * Returns 0 on success or negative त्रुटि_सं value.
 */
अटल पूर्णांक ICAMEX_msg_to_type6MEX_msgX(काष्ठा zcrypt_queue *zq,
				       काष्ठा ap_message *ap_msg,
				       काष्ठा ica_rsa_modexpo *mex)
अणु
	अटल काष्ठा type6_hdr अटल_type6_hdrX = अणु
		.type		=  0x06,
		.offset1	=  0x00000058,
		.agent_id	= अणु'C', 'A',पूर्ण,
		.function_code	= अणु'P', 'K'पूर्ण,
	पूर्ण;
	अटल काष्ठा function_and_rules_block अटल_pke_fnr = अणु
		.function_code	= अणु'P', 'K'पूर्ण,
		.ulen		= 10,
		.only_rule	= अणु'M', 'R', 'P', ' ', ' ', ' ', ' ', ' 'पूर्ण
	पूर्ण;
	काष्ठा अणु
		काष्ठा type6_hdr hdr;
		काष्ठा CPRBX cprbx;
		काष्ठा function_and_rules_block fr;
		अचिन्हित लघु length;
		अक्षर text[0];
	पूर्ण __packed * msg = ap_msg->msg;
	पूर्णांक size;

	/*
	 * The inputdatalength was a selection criteria in the dispatching
	 * function zcrypt_rsa_modexpo(). However, make sure the following
	 * copy_from_user() never exceeds the allocated buffer space.
	 */
	अगर (WARN_ON_ONCE(mex->inputdatalength > PAGE_SIZE))
		वापस -EINVAL;

	/* VUD.ciphertext */
	msg->length = mex->inputdatalength + 2;
	अगर (copy_from_user(msg->text, mex->inputdata, mex->inputdatalength))
		वापस -EFAULT;

	/* Set up key which is located after the variable length text. */
	size = zcrypt_type6_mex_key_en(mex, msg->text+mex->inputdatalength);
	अगर (size < 0)
		वापस size;
	size += माप(*msg) + mex->inputdatalength;

	/* message header, cprbx and f&r */
	msg->hdr = अटल_type6_hdrX;
	msg->hdr.ToCardLen1 = size - माप(msg->hdr);
	msg->hdr.FromCardLen1 = CEXXC_MAX_ICA_RESPONSE_SIZE - माप(msg->hdr);

	msg->cprbx = अटल_cprbx;
	msg->cprbx.करोमुख्य = AP_QID_QUEUE(zq->queue->qid);
	msg->cprbx.rpl_msgbl = msg->hdr.FromCardLen1;

	msg->fr = अटल_pke_fnr;

	msg->cprbx.req_parml = size - माप(msg->hdr) - माप(msg->cprbx);

	ap_msg->len = size;
	वापस 0;
पूर्ण

/**
 * Convert a ICACRT message to a type6 CRT message.
 *
 * @zq: crypto device poपूर्णांकer
 * @ap_msg: poपूर्णांकer to AP message
 * @crt: poपूर्णांकer to user input data
 *
 * Returns 0 on success or negative त्रुटि_सं value.
 */
अटल पूर्णांक ICACRT_msg_to_type6CRT_msgX(काष्ठा zcrypt_queue *zq,
				       काष्ठा ap_message *ap_msg,
				       काष्ठा ica_rsa_modexpo_crt *crt)
अणु
	अटल काष्ठा type6_hdr अटल_type6_hdrX = अणु
		.type		=  0x06,
		.offset1	=  0x00000058,
		.agent_id	= अणु'C', 'A',पूर्ण,
		.function_code	= अणु'P', 'D'पूर्ण,
	पूर्ण;
	अटल काष्ठा function_and_rules_block अटल_pkd_fnr = अणु
		.function_code	= अणु'P', 'D'पूर्ण,
		.ulen		= 10,
		.only_rule	= अणु'Z', 'E', 'R', 'O', '-', 'P', 'A', 'D'पूर्ण
	पूर्ण;

	काष्ठा अणु
		काष्ठा type6_hdr hdr;
		काष्ठा CPRBX cprbx;
		काष्ठा function_and_rules_block fr;
		अचिन्हित लघु length;
		अक्षर text[0];
	पूर्ण __packed * msg = ap_msg->msg;
	पूर्णांक size;

	/*
	 * The inputdatalength was a selection criteria in the dispatching
	 * function zcrypt_rsa_crt(). However, make sure the following
	 * copy_from_user() never exceeds the allocated buffer space.
	 */
	अगर (WARN_ON_ONCE(crt->inputdatalength > PAGE_SIZE))
		वापस -EINVAL;

	/* VUD.ciphertext */
	msg->length = crt->inputdatalength + 2;
	अगर (copy_from_user(msg->text, crt->inputdata, crt->inputdatalength))
		वापस -EFAULT;

	/* Set up key which is located after the variable length text. */
	size = zcrypt_type6_crt_key(crt, msg->text + crt->inputdatalength);
	अगर (size < 0)
		वापस size;
	size += माप(*msg) + crt->inputdatalength;	/* total size of msg */

	/* message header, cprbx and f&r */
	msg->hdr = अटल_type6_hdrX;
	msg->hdr.ToCardLen1 = size -  माप(msg->hdr);
	msg->hdr.FromCardLen1 = CEXXC_MAX_ICA_RESPONSE_SIZE - माप(msg->hdr);

	msg->cprbx = अटल_cprbx;
	msg->cprbx.करोमुख्य = AP_QID_QUEUE(zq->queue->qid);
	msg->cprbx.req_parml = msg->cprbx.rpl_msgbl =
		size - माप(msg->hdr) - माप(msg->cprbx);

	msg->fr = अटल_pkd_fnr;

	ap_msg->len = size;
	वापस 0;
पूर्ण

/**
 * Convert a XCRB message to a type6 CPRB message.
 *
 * @zq: crypto device poपूर्णांकer
 * @ap_msg: poपूर्णांकer to AP message
 * @xcRB: poपूर्णांकer to user input data
 *
 * Returns 0 on success or -EFAULT, -EINVAL.
 */
काष्ठा type86_fmt2_msg अणु
	काष्ठा type86_hdr hdr;
	काष्ठा type86_fmt2_ext fmt2;
पूर्ण __packed;

अटल पूर्णांक XCRB_msg_to_type6CPRB_msgX(bool userspace, काष्ठा ap_message *ap_msg,
				      काष्ठा ica_xcRB *xcRB,
				      अचिन्हित पूर्णांक *fcode,
				      अचिन्हित लघु **करोm)
अणु
	अटल काष्ठा type6_hdr अटल_type6_hdrX = अणु
		.type		=  0x06,
		.offset1	=  0x00000058,
	पूर्ण;
	काष्ठा अणु
		काष्ठा type6_hdr hdr;
		काष्ठा CPRBX cprbx;
	पूर्ण __packed * msg = ap_msg->msg;

	पूर्णांक rcblen = CEIL4(xcRB->request_control_blk_length);
	पूर्णांक replylen, req_sumlen, resp_sumlen;
	अक्षर *req_data = ap_msg->msg + माप(काष्ठा type6_hdr) + rcblen;
	अक्षर *function_code;

	अगर (CEIL4(xcRB->request_control_blk_length) <
			xcRB->request_control_blk_length)
		वापस -EINVAL; /* overflow after alignment*/

	/* length checks */
	ap_msg->len = माप(काष्ठा type6_hdr) +
		CEIL4(xcRB->request_control_blk_length) +
		xcRB->request_data_length;
	अगर (ap_msg->len > MSGTYPE06_MAX_MSG_SIZE)
		वापस -EINVAL;

	/*
	 * Overflow check
	 * sum must be greater (or equal) than the largest opeअक्रम
	 */
	req_sumlen = CEIL4(xcRB->request_control_blk_length) +
			xcRB->request_data_length;
	अगर ((CEIL4(xcRB->request_control_blk_length) <=
						xcRB->request_data_length) ?
		(req_sumlen < xcRB->request_data_length) :
		(req_sumlen < CEIL4(xcRB->request_control_blk_length))) अणु
		वापस -EINVAL;
	पूर्ण

	अगर (CEIL4(xcRB->reply_control_blk_length) <
			xcRB->reply_control_blk_length)
		वापस -EINVAL; /* overflow after alignment*/

	replylen = माप(काष्ठा type86_fmt2_msg) +
		CEIL4(xcRB->reply_control_blk_length) +
		xcRB->reply_data_length;
	अगर (replylen > MSGTYPE06_MAX_MSG_SIZE)
		वापस -EINVAL;

	/*
	 * Overflow check
	 * sum must be greater (or equal) than the largest opeअक्रम
	 */
	resp_sumlen = CEIL4(xcRB->reply_control_blk_length) +
			xcRB->reply_data_length;
	अगर ((CEIL4(xcRB->reply_control_blk_length) <= xcRB->reply_data_length) ?
		(resp_sumlen < xcRB->reply_data_length) :
		(resp_sumlen < CEIL4(xcRB->reply_control_blk_length))) अणु
		वापस -EINVAL;
	पूर्ण

	/* prepare type6 header */
	msg->hdr = अटल_type6_hdrX;
	स_नकल(msg->hdr.agent_id, &(xcRB->agent_ID), माप(xcRB->agent_ID));
	msg->hdr.ToCardLen1 = xcRB->request_control_blk_length;
	अगर (xcRB->request_data_length) अणु
		msg->hdr.offset2 = msg->hdr.offset1 + rcblen;
		msg->hdr.ToCardLen2 = xcRB->request_data_length;
	पूर्ण
	msg->hdr.FromCardLen1 = xcRB->reply_control_blk_length;
	msg->hdr.FromCardLen2 = xcRB->reply_data_length;

	/* prepare CPRB */
	अगर (z_copy_from_user(userspace, &(msg->cprbx), xcRB->request_control_blk_addr,
			     xcRB->request_control_blk_length))
		वापस -EFAULT;
	अगर (msg->cprbx.cprb_len + माप(msg->hdr.function_code) >
	    xcRB->request_control_blk_length)
		वापस -EINVAL;
	function_code = ((अचिन्हित अक्षर *)&msg->cprbx) + msg->cprbx.cprb_len;
	स_नकल(msg->hdr.function_code, function_code,
	       माप(msg->hdr.function_code));

	*fcode = (msg->hdr.function_code[0] << 8) | msg->hdr.function_code[1];
	*करोm = (अचिन्हित लघु *)&msg->cprbx.करोमुख्य;

	अगर (स_भेद(function_code, "US", 2) == 0
	    || स_भेद(function_code, "AU", 2) == 0)
		ap_msg->flags |= AP_MSG_FLAG_SPECIAL;

#अगर_घोषित CONFIG_ZCRYPT_DEBUG
	अगर (ap_msg->fi.flags & AP_FI_FLAG_TOGGLE_SPECIAL)
		ap_msg->flags ^= AP_MSG_FLAG_SPECIAL;
#पूर्ण_अगर

	/* copy data block */
	अगर (xcRB->request_data_length &&
	    z_copy_from_user(userspace, req_data, xcRB->request_data_address,
			     xcRB->request_data_length))
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल पूर्णांक xcrb_msg_to_type6_ep11cprb_msgx(bool userspace, काष्ठा ap_message *ap_msg,
					   काष्ठा ep11_urb *xcRB,
					   अचिन्हित पूर्णांक *fcode)
अणु
	अचिन्हित पूर्णांक lfmt;
	अटल काष्ठा type6_hdr अटल_type6_ep11_hdr = अणु
		.type		=  0x06,
		.rqid		= अणु0x00, 0x01पूर्ण,
		.function_code	= अणु0x00, 0x00पूर्ण,
		.agent_id[0]	=  0x58,	/* अणु'X'पूर्ण */
		.agent_id[1]	=  0x43,	/* अणु'C'पूर्ण */
		.offset1	=  0x00000058,
	पूर्ण;

	काष्ठा अणु
		काष्ठा type6_hdr hdr;
		काष्ठा ep11_cprb cprbx;
		अचिन्हित अक्षर	pld_tag;	/* fixed value 0x30 */
		अचिन्हित अक्षर	pld_lenfmt;	/* payload length क्रमmat */
	पूर्ण __packed * msg = ap_msg->msg;

	काष्ठा pld_hdr अणु
		अचिन्हित अक्षर	func_tag;	/* fixed value 0x4 */
		अचिन्हित अक्षर	func_len;	/* fixed value 0x4 */
		अचिन्हित पूर्णांक	func_val;	/* function ID	   */
		अचिन्हित अक्षर	करोm_tag;	/* fixed value 0x4 */
		अचिन्हित अक्षर	करोm_len;	/* fixed value 0x4 */
		अचिन्हित पूर्णांक	करोm_val;	/* करोमुख्य id	   */
	पूर्ण __packed * payload_hdr = शून्य;

	अगर (CEIL4(xcRB->req_len) < xcRB->req_len)
		वापस -EINVAL; /* overflow after alignment*/

	/* length checks */
	ap_msg->len = माप(काष्ठा type6_hdr) + xcRB->req_len;
	अगर (CEIL4(xcRB->req_len) > MSGTYPE06_MAX_MSG_SIZE -
				   (माप(काष्ठा type6_hdr)))
		वापस -EINVAL;

	अगर (CEIL4(xcRB->resp_len) < xcRB->resp_len)
		वापस -EINVAL; /* overflow after alignment*/

	अगर (CEIL4(xcRB->resp_len) > MSGTYPE06_MAX_MSG_SIZE -
				    (माप(काष्ठा type86_fmt2_msg)))
		वापस -EINVAL;

	/* prepare type6 header */
	msg->hdr = अटल_type6_ep11_hdr;
	msg->hdr.ToCardLen1   = xcRB->req_len;
	msg->hdr.FromCardLen1 = xcRB->resp_len;

	/* Import CPRB data from the ioctl input parameter */
	अगर (z_copy_from_user(userspace, &(msg->cprbx.cprb_len),
			     (अक्षर __क्रमce __user *)xcRB->req, xcRB->req_len)) अणु
		वापस -EFAULT;
	पूर्ण

	अगर ((msg->pld_lenfmt & 0x80) == 0x80) अणु /*ext.len.fmt 2 or 3*/
		चयन (msg->pld_lenfmt & 0x03) अणु
		हाल 1:
			lfmt = 2;
			अवरोध;
		हाल 2:
			lfmt = 3;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अणु
		lfmt = 1; /* length क्रमmat #1 */
	पूर्ण
	payload_hdr = (काष्ठा pld_hdr *)((&(msg->pld_lenfmt))+lfmt);
	*fcode = payload_hdr->func_val & 0xFFFF;

	/* enable special processing based on the cprbs flags special bit */
	अगर (msg->cprbx.flags & 0x20)
		ap_msg->flags |= AP_MSG_FLAG_SPECIAL;

#अगर_घोषित CONFIG_ZCRYPT_DEBUG
	अगर (ap_msg->fi.flags & AP_FI_FLAG_TOGGLE_SPECIAL)
		ap_msg->flags ^= AP_MSG_FLAG_SPECIAL;
#पूर्ण_अगर

	वापस 0;
पूर्ण

/**
 * Copy results from a type 86 ICA reply message back to user space.
 *
 * @zq: crypto device poपूर्णांकer
 * @reply: reply AP message.
 * @data: poपूर्णांकer to user output data
 * @length: size of user output data
 *
 * Returns 0 on success or -EINVAL, -EFAULT, -EAGAIN in हाल of an error.
 */
काष्ठा type86x_reply अणु
	काष्ठा type86_hdr hdr;
	काष्ठा type86_fmt2_ext fmt2;
	काष्ठा CPRBX cprbx;
	अचिन्हित अक्षर pad[4];	/* 4 byte function code/rules block ? */
	अचिन्हित लघु length;
	अक्षर text[];
पूर्ण __packed;

काष्ठा type86_ep11_reply अणु
	काष्ठा type86_hdr hdr;
	काष्ठा type86_fmt2_ext fmt2;
	काष्ठा ep11_cprb cprbx;
पूर्ण __packed;

अटल पूर्णांक convert_type86_ica(काष्ठा zcrypt_queue *zq,
			  काष्ठा ap_message *reply,
			  अक्षर __user *outputdata,
			  अचिन्हित पूर्णांक outputdatalength)
अणु
	अटल अचिन्हित अक्षर अटल_pad[] = अणु
		0x00, 0x02,
		0x1B, 0x7B, 0x5D, 0xB5, 0x75, 0x01, 0x3D, 0xFD,
		0x8D, 0xD1, 0xC7, 0x03, 0x2D, 0x09, 0x23, 0x57,
		0x89, 0x49, 0xB9, 0x3F, 0xBB, 0x99, 0x41, 0x5B,
		0x75, 0x21, 0x7B, 0x9D, 0x3B, 0x6B, 0x51, 0x39,
		0xBB, 0x0D, 0x35, 0xB9, 0x89, 0x0F, 0x93, 0xA5,
		0x0B, 0x47, 0xF1, 0xD3, 0xBB, 0xCB, 0xF1, 0x9D,
		0x23, 0x73, 0x71, 0xFF, 0xF3, 0xF5, 0x45, 0xFB,
		0x61, 0x29, 0x23, 0xFD, 0xF1, 0x29, 0x3F, 0x7F,
		0x17, 0xB7, 0x1B, 0xA9, 0x19, 0xBD, 0x57, 0xA9,
		0xD7, 0x95, 0xA3, 0xCB, 0xED, 0x1D, 0xDB, 0x45,
		0x7D, 0x11, 0xD1, 0x51, 0x1B, 0xED, 0x71, 0xE9,
		0xB1, 0xD1, 0xAB, 0xAB, 0x21, 0x2B, 0x1B, 0x9F,
		0x3B, 0x9F, 0xF7, 0xF7, 0xBD, 0x63, 0xEB, 0xAD,
		0xDF, 0xB3, 0x6F, 0x5B, 0xDB, 0x8D, 0xA9, 0x5D,
		0xE3, 0x7D, 0x77, 0x49, 0x47, 0xF5, 0xA7, 0xFD,
		0xAB, 0x2F, 0x27, 0x35, 0x77, 0xD3, 0x49, 0xC9,
		0x09, 0xEB, 0xB1, 0xF9, 0xBF, 0x4B, 0xCB, 0x2B,
		0xEB, 0xEB, 0x05, 0xFF, 0x7D, 0xC7, 0x91, 0x8B,
		0x09, 0x83, 0xB9, 0xB9, 0x69, 0x33, 0x39, 0x6B,
		0x79, 0x75, 0x19, 0xBF, 0xBB, 0x07, 0x1D, 0xBD,
		0x29, 0xBF, 0x39, 0x95, 0x93, 0x1D, 0x35, 0xC7,
		0xC9, 0x4D, 0xE5, 0x97, 0x0B, 0x43, 0x9B, 0xF1,
		0x16, 0x93, 0x03, 0x1F, 0xA5, 0xFB, 0xDB, 0xF3,
		0x27, 0x4F, 0x27, 0x61, 0x05, 0x1F, 0xB9, 0x23,
		0x2F, 0xC3, 0x81, 0xA9, 0x23, 0x71, 0x55, 0x55,
		0xEB, 0xED, 0x41, 0xE5, 0xF3, 0x11, 0xF1, 0x43,
		0x69, 0x03, 0xBD, 0x0B, 0x37, 0x0F, 0x51, 0x8F,
		0x0B, 0xB5, 0x89, 0x5B, 0x67, 0xA9, 0xD9, 0x4F,
		0x01, 0xF9, 0x21, 0x77, 0x37, 0x73, 0x79, 0xC5,
		0x7F, 0x51, 0xC1, 0xCF, 0x97, 0xA1, 0x75, 0xAD,
		0x35, 0x9D, 0xD3, 0xD3, 0xA7, 0x9D, 0x5D, 0x41,
		0x6F, 0x65, 0x1B, 0xCF, 0xA9, 0x87, 0x91, 0x09
	पूर्ण;
	काष्ठा type86x_reply *msg = reply->msg;
	अचिन्हित लघु service_rc, service_rs;
	अचिन्हित पूर्णांक reply_len, pad_len;
	अक्षर *data;

	service_rc = msg->cprbx.ccp_rtcode;
	अगर (unlikely(service_rc != 0)) अणु
		service_rs = msg->cprbx.ccp_rscode;
		अगर ((service_rc == 8 && service_rs == 66) ||
		    (service_rc == 8 && service_rs == 65) ||
		    (service_rc == 8 && service_rs == 72) ||
		    (service_rc == 8 && service_rs == 770) ||
		    (service_rc == 12 && service_rs == 769)) अणु
			ZCRYPT_DBF_WARN("dev=%02x.%04x rc/rs=%d/%d => rc=EINVAL\n",
					AP_QID_CARD(zq->queue->qid),
					AP_QID_QUEUE(zq->queue->qid),
					(पूर्णांक) service_rc, (पूर्णांक) service_rs);
			वापस -EINVAL;
		पूर्ण
		zq->online = 0;
		pr_err("Crypto dev=%02x.%04x rc/rs=%d/%d online=0 rc=EAGAIN\n",
		       AP_QID_CARD(zq->queue->qid),
		       AP_QID_QUEUE(zq->queue->qid),
		       (पूर्णांक) service_rc, (पूर्णांक) service_rs);
		ZCRYPT_DBF_ERR("dev=%02x.%04x rc/rs=%d/%d => online=0 rc=EAGAIN\n",
			       AP_QID_CARD(zq->queue->qid),
			       AP_QID_QUEUE(zq->queue->qid),
			       (पूर्णांक) service_rc, (पूर्णांक) service_rs);
		वापस -EAGAIN;
	पूर्ण
	data = msg->text;
	reply_len = msg->length - 2;
	अगर (reply_len > outputdatalength)
		वापस -EINVAL;
	/*
	 * For all encipher requests, the length of the ciphertext (reply_len)
	 * will always equal the modulus length. For MEX decipher requests
	 * the output needs to get padded. Minimum pad size is 10.
	 *
	 * Currently, the हालs where padding will be added is क्रम:
	 * - PCIXCC_MCL2 using a CRT क्रमm token (since PKD didn't support
	 *   ZERO-PAD and CRT is only supported क्रम PKD requests)
	 * - PCICC, always
	 */
	pad_len = outputdatalength - reply_len;
	अगर (pad_len > 0) अणु
		अगर (pad_len < 10)
			वापस -EINVAL;
		/* 'restore' padding left in the CEXXC card. */
		अगर (copy_to_user(outputdata, अटल_pad, pad_len - 1))
			वापस -EFAULT;
		अगर (put_user(0, outputdata + pad_len - 1))
			वापस -EFAULT;
	पूर्ण
	/* Copy the crypto response to user space. */
	अगर (copy_to_user(outputdata + pad_len, data, reply_len))
		वापस -EFAULT;
	वापस 0;
पूर्ण

/**
 * Copy results from a type 86 XCRB reply message back to user space.
 *
 * @zq: crypto device poपूर्णांकer
 * @reply: reply AP message.
 * @xcRB: poपूर्णांकer to XCRB
 *
 * Returns 0 on success or -EINVAL, -EFAULT, -EAGAIN in हाल of an error.
 */
अटल पूर्णांक convert_type86_xcrb(bool userspace, काष्ठा zcrypt_queue *zq,
			       काष्ठा ap_message *reply,
			       काष्ठा ica_xcRB *xcRB)
अणु
	काष्ठा type86_fmt2_msg *msg = reply->msg;
	अक्षर *data = reply->msg;

	/* Copy CPRB to user */
	अगर (z_copy_to_user(userspace, xcRB->reply_control_blk_addr,
			   data + msg->fmt2.offset1, msg->fmt2.count1))
		वापस -EFAULT;
	xcRB->reply_control_blk_length = msg->fmt2.count1;

	/* Copy data buffer to user */
	अगर (msg->fmt2.count2)
		अगर (z_copy_to_user(userspace, xcRB->reply_data_addr,
				   data + msg->fmt2.offset2, msg->fmt2.count2))
			वापस -EFAULT;
	xcRB->reply_data_length = msg->fmt2.count2;
	वापस 0;
पूर्ण

/**
 * Copy results from a type 86 EP11 XCRB reply message back to user space.
 *
 * @zq: crypto device poपूर्णांकer
 * @reply: reply AP message.
 * @xcRB: poपूर्णांकer to EP11 user request block
 *
 * Returns 0 on success or -EINVAL, -EFAULT, -EAGAIN in हाल of an error.
 */
अटल पूर्णांक convert_type86_ep11_xcrb(bool userspace, काष्ठा zcrypt_queue *zq,
				    काष्ठा ap_message *reply,
				    काष्ठा ep11_urb *xcRB)
अणु
	काष्ठा type86_fmt2_msg *msg = reply->msg;
	अक्षर *data = reply->msg;

	अगर (xcRB->resp_len < msg->fmt2.count1)
		वापस -EINVAL;

	/* Copy response CPRB to user */
	अगर (z_copy_to_user(userspace, (अक्षर __क्रमce __user *)xcRB->resp,
			   data + msg->fmt2.offset1, msg->fmt2.count1))
		वापस -EFAULT;
	xcRB->resp_len = msg->fmt2.count1;
	वापस 0;
पूर्ण

अटल पूर्णांक convert_type86_rng(काष्ठा zcrypt_queue *zq,
			  काष्ठा ap_message *reply,
			  अक्षर *buffer)
अणु
	काष्ठा अणु
		काष्ठा type86_hdr hdr;
		काष्ठा type86_fmt2_ext fmt2;
		काष्ठा CPRBX cprbx;
	पूर्ण __packed * msg = reply->msg;
	अक्षर *data = reply->msg;

	अगर (msg->cprbx.ccp_rtcode != 0 || msg->cprbx.ccp_rscode != 0)
		वापस -EINVAL;
	स_नकल(buffer, data + msg->fmt2.offset2, msg->fmt2.count2);
	वापस msg->fmt2.count2;
पूर्ण

अटल पूर्णांक convert_response_ica(काष्ठा zcrypt_queue *zq,
			    काष्ठा ap_message *reply,
			    अक्षर __user *outputdata,
			    अचिन्हित पूर्णांक outputdatalength)
अणु
	काष्ठा type86x_reply *msg = reply->msg;

	चयन (msg->hdr.type) अणु
	हाल TYPE82_RSP_CODE:
	हाल TYPE88_RSP_CODE:
		वापस convert_error(zq, reply);
	हाल TYPE86_RSP_CODE:
		अगर (msg->cprbx.ccp_rtcode &&
		   (msg->cprbx.ccp_rscode == 0x14f) &&
		   (outputdatalength > 256)) अणु
			अगर (zq->zcard->max_exp_bit_length <= 17) अणु
				zq->zcard->max_exp_bit_length = 17;
				वापस -EAGAIN;
			पूर्ण अन्यथा
				वापस -EINVAL;
		पूर्ण
		अगर (msg->hdr.reply_code)
			वापस convert_error(zq, reply);
		अगर (msg->cprbx.cprb_ver_id == 0x02)
			वापस convert_type86_ica(zq, reply,
						  outputdata, outputdatalength);
		fallthrough;	/* wrong cprb version is an unknown response */
	शेष:
		/* Unknown response type, this should NEVER EVER happen */
		zq->online = 0;
		pr_err("Crypto dev=%02x.%04x unknown response type 0x%02x => online=0 rc=EAGAIN\n",
		       AP_QID_CARD(zq->queue->qid),
		       AP_QID_QUEUE(zq->queue->qid),
		       (पूर्णांक) msg->hdr.type);
		ZCRYPT_DBF_ERR("dev=%02x.%04x unknown response type 0x%02x => online=0 rc=EAGAIN\n",
			       AP_QID_CARD(zq->queue->qid),
			       AP_QID_QUEUE(zq->queue->qid),
			       (पूर्णांक) msg->hdr.type);
		वापस -EAGAIN;
	पूर्ण
पूर्ण

अटल पूर्णांक convert_response_xcrb(bool userspace, काष्ठा zcrypt_queue *zq,
				 काष्ठा ap_message *reply,
				 काष्ठा ica_xcRB *xcRB)
अणु
	काष्ठा type86x_reply *msg = reply->msg;

	चयन (msg->hdr.type) अणु
	हाल TYPE82_RSP_CODE:
	हाल TYPE88_RSP_CODE:
		xcRB->status = 0x0008044DL; /* HDD_InvalidParm */
		वापस convert_error(zq, reply);
	हाल TYPE86_RSP_CODE:
		अगर (msg->hdr.reply_code) अणु
			स_नकल(&(xcRB->status), msg->fmt2.apfs, माप(u32));
			वापस convert_error(zq, reply);
		पूर्ण
		अगर (msg->cprbx.cprb_ver_id == 0x02)
			वापस convert_type86_xcrb(userspace, zq, reply, xcRB);
		fallthrough;	/* wrong cprb version is an unknown response */
	शेष: /* Unknown response type, this should NEVER EVER happen */
		xcRB->status = 0x0008044DL; /* HDD_InvalidParm */
		zq->online = 0;
		pr_err("Crypto dev=%02x.%04x unknown response type 0x%02x => online=0 rc=EAGAIN\n",
		       AP_QID_CARD(zq->queue->qid),
		       AP_QID_QUEUE(zq->queue->qid),
		       (पूर्णांक) msg->hdr.type);
		ZCRYPT_DBF_ERR("dev=%02x.%04x unknown response type 0x%02x => online=0 rc=EAGAIN\n",
			       AP_QID_CARD(zq->queue->qid),
			       AP_QID_QUEUE(zq->queue->qid),
			       (पूर्णांक) msg->hdr.type);
		वापस -EAGAIN;
	पूर्ण
पूर्ण

अटल पूर्णांक convert_response_ep11_xcrb(bool userspace, काष्ठा zcrypt_queue *zq,
				      काष्ठा ap_message *reply, काष्ठा ep11_urb *xcRB)
अणु
	काष्ठा type86_ep11_reply *msg = reply->msg;

	चयन (msg->hdr.type) अणु
	हाल TYPE82_RSP_CODE:
	हाल TYPE87_RSP_CODE:
		वापस convert_error(zq, reply);
	हाल TYPE86_RSP_CODE:
		अगर (msg->hdr.reply_code)
			वापस convert_error(zq, reply);
		अगर (msg->cprbx.cprb_ver_id == 0x04)
			वापस convert_type86_ep11_xcrb(userspace, zq, reply, xcRB);
		fallthrough;	/* wrong cprb version is an unknown resp */
	शेष: /* Unknown response type, this should NEVER EVER happen */
		zq->online = 0;
		pr_err("Crypto dev=%02x.%04x unknown response type 0x%02x => online=0 rc=EAGAIN\n",
		       AP_QID_CARD(zq->queue->qid),
		       AP_QID_QUEUE(zq->queue->qid),
		       (पूर्णांक) msg->hdr.type);
		ZCRYPT_DBF_ERR("dev=%02x.%04x unknown response type 0x%02x => online=0 rc=EAGAIN\n",
			       AP_QID_CARD(zq->queue->qid),
			       AP_QID_QUEUE(zq->queue->qid),
			       (पूर्णांक) msg->hdr.type);
		वापस -EAGAIN;
	पूर्ण
पूर्ण

अटल पूर्णांक convert_response_rng(काष्ठा zcrypt_queue *zq,
				 काष्ठा ap_message *reply,
				 अक्षर *data)
अणु
	काष्ठा type86x_reply *msg = reply->msg;

	चयन (msg->hdr.type) अणु
	हाल TYPE82_RSP_CODE:
	हाल TYPE88_RSP_CODE:
		वापस -EINVAL;
	हाल TYPE86_RSP_CODE:
		अगर (msg->hdr.reply_code)
			वापस -EINVAL;
		अगर (msg->cprbx.cprb_ver_id == 0x02)
			वापस convert_type86_rng(zq, reply, data);
		fallthrough;	/* wrong cprb version is an unknown response */
	शेष: /* Unknown response type, this should NEVER EVER happen */
		zq->online = 0;
		pr_err("Crypto dev=%02x.%04x unknown response type 0x%02x => online=0 rc=EAGAIN\n",
		       AP_QID_CARD(zq->queue->qid),
		       AP_QID_QUEUE(zq->queue->qid),
		       (पूर्णांक) msg->hdr.type);
		ZCRYPT_DBF_ERR("dev=%02x.%04x unknown response type 0x%02x => online=0 rc=EAGAIN\n",
			       AP_QID_CARD(zq->queue->qid),
			       AP_QID_QUEUE(zq->queue->qid),
			       (पूर्णांक) msg->hdr.type);
		वापस -EAGAIN;
	पूर्ण
पूर्ण

/**
 * This function is called from the AP bus code after a crypto request
 * "msg" has finished with the reply message "reply".
 * It is called from tasklet context.
 * @aq: poपूर्णांकer to the AP queue
 * @msg: poपूर्णांकer to the AP message
 * @reply: poपूर्णांकer to the AP reply message
 */
अटल व्योम zcrypt_msgtype6_receive(काष्ठा ap_queue *aq,
				  काष्ठा ap_message *msg,
				  काष्ठा ap_message *reply)
अणु
	अटल काष्ठा error_hdr error_reply = अणु
		.type = TYPE82_RSP_CODE,
		.reply_code = REP82_ERROR_MACHINE_FAILURE,
	पूर्ण;
	काष्ठा response_type *resp_type =
		(काष्ठा response_type *) msg->निजी;
	काष्ठा type86x_reply *t86r;
	पूर्णांक len;

	/* Copy the reply message to the request message buffer. */
	अगर (!reply)
		जाओ out;	/* ap_msg->rc indicates the error */
	t86r = reply->msg;
	अगर (t86r->hdr.type == TYPE86_RSP_CODE &&
		 t86r->cprbx.cprb_ver_id == 0x02) अणु
		चयन (resp_type->type) अणु
		हाल CEXXC_RESPONSE_TYPE_ICA:
			len = माप(काष्ठा type86x_reply) + t86r->length - 2;
			len = min_t(पूर्णांक, CEXXC_MAX_ICA_RESPONSE_SIZE, len);
			स_नकल(msg->msg, reply->msg, len);
			अवरोध;
		हाल CEXXC_RESPONSE_TYPE_XCRB:
			len = t86r->fmt2.offset2 + t86r->fmt2.count2;
			len = min_t(पूर्णांक, MSGTYPE06_MAX_MSG_SIZE, len);
			स_नकल(msg->msg, reply->msg, len);
			अवरोध;
		शेष:
			स_नकल(msg->msg, &error_reply, माप(error_reply));
		पूर्ण
	पूर्ण अन्यथा
		स_नकल(msg->msg, reply->msg, माप(error_reply));
out:
	complete(&(resp_type->work));
पूर्ण

/**
 * This function is called from the AP bus code after a crypto request
 * "msg" has finished with the reply message "reply".
 * It is called from tasklet context.
 * @aq: poपूर्णांकer to the AP queue
 * @msg: poपूर्णांकer to the AP message
 * @reply: poपूर्णांकer to the AP reply message
 */
अटल व्योम zcrypt_msgtype6_receive_ep11(काष्ठा ap_queue *aq,
					 काष्ठा ap_message *msg,
					 काष्ठा ap_message *reply)
अणु
	अटल काष्ठा error_hdr error_reply = अणु
		.type = TYPE82_RSP_CODE,
		.reply_code = REP82_ERROR_MACHINE_FAILURE,
	पूर्ण;
	काष्ठा response_type *resp_type =
		(काष्ठा response_type *)msg->निजी;
	काष्ठा type86_ep11_reply *t86r;
	पूर्णांक len;

	/* Copy the reply message to the request message buffer. */
	अगर (!reply)
		जाओ out;	/* ap_msg->rc indicates the error */
	t86r = reply->msg;
	अगर (t86r->hdr.type == TYPE86_RSP_CODE &&
	    t86r->cprbx.cprb_ver_id == 0x04) अणु
		चयन (resp_type->type) अणु
		हाल CEXXC_RESPONSE_TYPE_EP11:
			len = t86r->fmt2.offset1 + t86r->fmt2.count1;
			len = min_t(पूर्णांक, MSGTYPE06_MAX_MSG_SIZE, len);
			स_नकल(msg->msg, reply->msg, len);
			अवरोध;
		शेष:
			स_नकल(msg->msg, &error_reply, माप(error_reply));
		पूर्ण
	पूर्ण अन्यथा अणु
		स_नकल(msg->msg, reply->msg, माप(error_reply));
	पूर्ण
out:
	complete(&(resp_type->work));
पूर्ण

अटल atomic_t zcrypt_step = ATOMIC_INIT(0);

/**
 * The request distributor calls this function अगर it picked the CEXxC
 * device to handle a modexpo request.
 * @zq: poपूर्णांकer to zcrypt_queue काष्ठाure that identअगरies the
 *	CEXxC device to the request distributor
 * @mex: poपूर्णांकer to the modexpo request buffer
 */
अटल दीर्घ zcrypt_msgtype6_modexpo(काष्ठा zcrypt_queue *zq,
				    काष्ठा ica_rsa_modexpo *mex,
				    काष्ठा ap_message *ap_msg)
अणु
	काष्ठा response_type resp_type = अणु
		.type = CEXXC_RESPONSE_TYPE_ICA,
	पूर्ण;
	पूर्णांक rc;

	ap_msg->msg = (व्योम *) get_zeroed_page(GFP_KERNEL);
	अगर (!ap_msg->msg)
		वापस -ENOMEM;
	ap_msg->receive = zcrypt_msgtype6_receive;
	ap_msg->psmid = (((अचिन्हित दीर्घ दीर्घ) current->pid) << 32) +
		atomic_inc_वापस(&zcrypt_step);
	ap_msg->निजी = &resp_type;
	rc = ICAMEX_msg_to_type6MEX_msgX(zq, ap_msg, mex);
	अगर (rc)
		जाओ out_मुक्त;
	init_completion(&resp_type.work);
	rc = ap_queue_message(zq->queue, ap_msg);
	अगर (rc)
		जाओ out_मुक्त;
	rc = रुको_क्रम_completion_पूर्णांकerruptible(&resp_type.work);
	अगर (rc == 0) अणु
		rc = ap_msg->rc;
		अगर (rc == 0)
			rc = convert_response_ica(zq, ap_msg,
						  mex->outputdata,
						  mex->outputdatalength);
	पूर्ण अन्यथा
		/* Signal pending. */
		ap_cancel_message(zq->queue, ap_msg);
out_मुक्त:
	मुक्त_page((अचिन्हित दीर्घ) ap_msg->msg);
	ap_msg->निजी = शून्य;
	ap_msg->msg = शून्य;
	वापस rc;
पूर्ण

/**
 * The request distributor calls this function अगर it picked the CEXxC
 * device to handle a modexpo_crt request.
 * @zq: poपूर्णांकer to zcrypt_queue काष्ठाure that identअगरies the
 *	CEXxC device to the request distributor
 * @crt: poपूर्णांकer to the modexpoc_crt request buffer
 */
अटल दीर्घ zcrypt_msgtype6_modexpo_crt(काष्ठा zcrypt_queue *zq,
					काष्ठा ica_rsa_modexpo_crt *crt,
					काष्ठा ap_message *ap_msg)
अणु
	काष्ठा response_type resp_type = अणु
		.type = CEXXC_RESPONSE_TYPE_ICA,
	पूर्ण;
	पूर्णांक rc;

	ap_msg->msg = (व्योम *) get_zeroed_page(GFP_KERNEL);
	अगर (!ap_msg->msg)
		वापस -ENOMEM;
	ap_msg->receive = zcrypt_msgtype6_receive;
	ap_msg->psmid = (((अचिन्हित दीर्घ दीर्घ) current->pid) << 32) +
		atomic_inc_वापस(&zcrypt_step);
	ap_msg->निजी = &resp_type;
	rc = ICACRT_msg_to_type6CRT_msgX(zq, ap_msg, crt);
	अगर (rc)
		जाओ out_मुक्त;
	init_completion(&resp_type.work);
	rc = ap_queue_message(zq->queue, ap_msg);
	अगर (rc)
		जाओ out_मुक्त;
	rc = रुको_क्रम_completion_पूर्णांकerruptible(&resp_type.work);
	अगर (rc == 0) अणु
		rc = ap_msg->rc;
		अगर (rc == 0)
			rc = convert_response_ica(zq, ap_msg,
						  crt->outputdata,
						  crt->outputdatalength);
	पूर्ण अन्यथा अणु
		/* Signal pending. */
		ap_cancel_message(zq->queue, ap_msg);
	पूर्ण
out_मुक्त:
	मुक्त_page((अचिन्हित दीर्घ) ap_msg->msg);
	ap_msg->निजी = शून्य;
	ap_msg->msg = शून्य;
	वापस rc;
पूर्ण

/**
 * Fetch function code from cprb.
 * Extracting the fc requires to copy the cprb from userspace.
 * So this function allocates memory and needs an ap_msg prepared
 * by the caller with ap_init_message(). Also the caller has to
 * make sure ap_release_message() is always called even on failure.
 */
अचिन्हित पूर्णांक get_cprb_fc(bool userspace, काष्ठा ica_xcRB *xcRB,
			 काष्ठा ap_message *ap_msg,
			 अचिन्हित पूर्णांक *func_code, अचिन्हित लघु **करोm)
अणु
	काष्ठा response_type resp_type = अणु
		.type = CEXXC_RESPONSE_TYPE_XCRB,
	पूर्ण;

	ap_msg->msg = kदो_स्मृति(MSGTYPE06_MAX_MSG_SIZE, GFP_KERNEL);
	अगर (!ap_msg->msg)
		वापस -ENOMEM;
	ap_msg->receive = zcrypt_msgtype6_receive;
	ap_msg->psmid = (((अचिन्हित दीर्घ दीर्घ) current->pid) << 32) +
				atomic_inc_वापस(&zcrypt_step);
	ap_msg->निजी = kmemdup(&resp_type, माप(resp_type), GFP_KERNEL);
	अगर (!ap_msg->निजी)
		वापस -ENOMEM;
	वापस XCRB_msg_to_type6CPRB_msgX(userspace, ap_msg, xcRB, func_code, करोm);
पूर्ण

/**
 * The request distributor calls this function अगर it picked the CEXxC
 * device to handle a send_cprb request.
 * @zq: poपूर्णांकer to zcrypt_queue काष्ठाure that identअगरies the
 *	CEXxC device to the request distributor
 * @xcRB: poपूर्णांकer to the send_cprb request buffer
 */
अटल दीर्घ zcrypt_msgtype6_send_cprb(bool userspace, काष्ठा zcrypt_queue *zq,
				      काष्ठा ica_xcRB *xcRB,
				      काष्ठा ap_message *ap_msg)
अणु
	पूर्णांक rc;
	काष्ठा response_type *rtype = (काष्ठा response_type *)(ap_msg->निजी);

	init_completion(&rtype->work);
	rc = ap_queue_message(zq->queue, ap_msg);
	अगर (rc)
		जाओ out;
	rc = रुको_क्रम_completion_पूर्णांकerruptible(&rtype->work);
	अगर (rc == 0) अणु
		rc = ap_msg->rc;
		अगर (rc == 0)
			rc = convert_response_xcrb(userspace, zq, ap_msg, xcRB);
	पूर्ण अन्यथा
		/* Signal pending. */
		ap_cancel_message(zq->queue, ap_msg);
out:
	वापस rc;
पूर्ण

/**
 * Fetch function code from ep11 cprb.
 * Extracting the fc requires to copy the ep11 cprb from userspace.
 * So this function allocates memory and needs an ap_msg prepared
 * by the caller with ap_init_message(). Also the caller has to
 * make sure ap_release_message() is always called even on failure.
 */
अचिन्हित पूर्णांक get_ep11cprb_fc(bool userspace, काष्ठा ep11_urb *xcrb,
			     काष्ठा ap_message *ap_msg,
			     अचिन्हित पूर्णांक *func_code)
अणु
	काष्ठा response_type resp_type = अणु
		.type = CEXXC_RESPONSE_TYPE_EP11,
	पूर्ण;

	ap_msg->msg = kदो_स्मृति(MSGTYPE06_MAX_MSG_SIZE, GFP_KERNEL);
	अगर (!ap_msg->msg)
		वापस -ENOMEM;
	ap_msg->receive = zcrypt_msgtype6_receive_ep11;
	ap_msg->psmid = (((अचिन्हित दीर्घ दीर्घ) current->pid) << 32) +
				atomic_inc_वापस(&zcrypt_step);
	ap_msg->निजी = kmemdup(&resp_type, माप(resp_type), GFP_KERNEL);
	अगर (!ap_msg->निजी)
		वापस -ENOMEM;
	वापस xcrb_msg_to_type6_ep11cprb_msgx(userspace, ap_msg, xcrb, func_code);
पूर्ण

/**
 * The request distributor calls this function अगर it picked the CEX4P
 * device to handle a send_ep11_cprb request.
 * @zq: poपूर्णांकer to zcrypt_queue काष्ठाure that identअगरies the
 *	  CEX4P device to the request distributor
 * @xcRB: poपूर्णांकer to the ep11 user request block
 */
अटल दीर्घ zcrypt_msgtype6_send_ep11_cprb(bool userspace, काष्ठा zcrypt_queue *zq,
					   काष्ठा ep11_urb *xcrb,
					   काष्ठा ap_message *ap_msg)
अणु
	पूर्णांक rc;
	अचिन्हित पूर्णांक lfmt;
	काष्ठा response_type *rtype = (काष्ठा response_type *)(ap_msg->निजी);
	काष्ठा अणु
		काष्ठा type6_hdr hdr;
		काष्ठा ep11_cprb cprbx;
		अचिन्हित अक्षर	pld_tag;	/* fixed value 0x30 */
		अचिन्हित अक्षर	pld_lenfmt;	/* payload length क्रमmat */
	पूर्ण __packed * msg = ap_msg->msg;
	काष्ठा pld_hdr अणु
		अचिन्हित अक्षर	func_tag;	/* fixed value 0x4 */
		अचिन्हित अक्षर	func_len;	/* fixed value 0x4 */
		अचिन्हित पूर्णांक	func_val;	/* function ID	   */
		अचिन्हित अक्षर	करोm_tag;	/* fixed value 0x4 */
		अचिन्हित अक्षर	करोm_len;	/* fixed value 0x4 */
		अचिन्हित पूर्णांक	करोm_val;	/* करोमुख्य id	   */
	पूर्ण __packed * payload_hdr = शून्य;


	/**
	 * The target करोमुख्य field within the cprb body/payload block will be
	 * replaced by the usage करोमुख्य क्रम non-management commands only.
	 * Thereक्रमe we check the first bit of the 'flags' parameter क्रम
	 * management command indication.
	 *   0 - non management command
	 *   1 - management command
	 */
	अगर (!((msg->cprbx.flags & 0x80) == 0x80)) अणु
		msg->cprbx.target_id = (अचिन्हित पूर्णांक)
					AP_QID_QUEUE(zq->queue->qid);

		अगर ((msg->pld_lenfmt & 0x80) == 0x80) अणु /*ext.len.fmt 2 or 3*/
			चयन (msg->pld_lenfmt & 0x03) अणु
			हाल 1:
				lfmt = 2;
				अवरोध;
			हाल 2:
				lfmt = 3;
				अवरोध;
			शेष:
				वापस -EINVAL;
			पूर्ण
		पूर्ण अन्यथा अणु
			lfmt = 1; /* length क्रमmat #1 */
		पूर्ण
		payload_hdr = (काष्ठा pld_hdr *)((&(msg->pld_lenfmt))+lfmt);
		payload_hdr->करोm_val = (अचिन्हित पूर्णांक)
					AP_QID_QUEUE(zq->queue->qid);
	पूर्ण

	init_completion(&rtype->work);
	rc = ap_queue_message(zq->queue, ap_msg);
	अगर (rc)
		जाओ out;
	rc = रुको_क्रम_completion_पूर्णांकerruptible(&rtype->work);
	अगर (rc == 0) अणु
		rc = ap_msg->rc;
		अगर (rc == 0)
			rc = convert_response_ep11_xcrb(userspace, zq, ap_msg, xcrb);
	पूर्ण अन्यथा
		/* Signal pending. */
		ap_cancel_message(zq->queue, ap_msg);
out:
	वापस rc;
पूर्ण

अचिन्हित पूर्णांक get_rng_fc(काष्ठा ap_message *ap_msg, पूर्णांक *func_code,
						   अचिन्हित पूर्णांक *करोमुख्य)
अणु
	काष्ठा response_type resp_type = अणु
		.type = CEXXC_RESPONSE_TYPE_XCRB,
	पूर्ण;

	ap_msg->msg = kदो_स्मृति(MSGTYPE06_MAX_MSG_SIZE, GFP_KERNEL);
	अगर (!ap_msg->msg)
		वापस -ENOMEM;
	ap_msg->receive = zcrypt_msgtype6_receive;
	ap_msg->psmid = (((अचिन्हित दीर्घ दीर्घ) current->pid) << 32) +
				atomic_inc_वापस(&zcrypt_step);
	ap_msg->निजी = kmemdup(&resp_type, माप(resp_type), GFP_KERNEL);
	अगर (!ap_msg->निजी)
		वापस -ENOMEM;

	rng_type6CPRB_msgX(ap_msg, ZCRYPT_RNG_BUFFER_SIZE, करोमुख्य);

	*func_code = HWRNG;
	वापस 0;
पूर्ण

/**
 * The request distributor calls this function अगर it picked the CEXxC
 * device to generate अक्रमom data.
 * @zq: poपूर्णांकer to zcrypt_queue काष्ठाure that identअगरies the
 *	CEXxC device to the request distributor
 * @buffer: poपूर्णांकer to a memory page to वापस अक्रमom data
 */
अटल दीर्घ zcrypt_msgtype6_rng(काष्ठा zcrypt_queue *zq,
				अक्षर *buffer, काष्ठा ap_message *ap_msg)
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
	काष्ठा response_type *rtype = (काष्ठा response_type *)(ap_msg->निजी);
	पूर्णांक rc;

	msg->cprbx.करोमुख्य = AP_QID_QUEUE(zq->queue->qid);

	init_completion(&rtype->work);
	rc = ap_queue_message(zq->queue, ap_msg);
	अगर (rc)
		जाओ out;
	rc = रुको_क्रम_completion_पूर्णांकerruptible(&rtype->work);
	अगर (rc == 0) अणु
		rc = ap_msg->rc;
		अगर (rc == 0)
			rc = convert_response_rng(zq, ap_msg, buffer);
	पूर्ण अन्यथा
		/* Signal pending. */
		ap_cancel_message(zq->queue, ap_msg);
out:
	वापस rc;
पूर्ण

/**
 * The crypto operations क्रम a CEXxC card.
 */
अटल काष्ठा zcrypt_ops zcrypt_msgtype6_norng_ops = अणु
	.owner = THIS_MODULE,
	.name = MSGTYPE06_NAME,
	.variant = MSGTYPE06_VARIANT_NORNG,
	.rsa_modexpo = zcrypt_msgtype6_modexpo,
	.rsa_modexpo_crt = zcrypt_msgtype6_modexpo_crt,
	.send_cprb = zcrypt_msgtype6_send_cprb,
पूर्ण;

अटल काष्ठा zcrypt_ops zcrypt_msgtype6_ops = अणु
	.owner = THIS_MODULE,
	.name = MSGTYPE06_NAME,
	.variant = MSGTYPE06_VARIANT_DEFAULT,
	.rsa_modexpo = zcrypt_msgtype6_modexpo,
	.rsa_modexpo_crt = zcrypt_msgtype6_modexpo_crt,
	.send_cprb = zcrypt_msgtype6_send_cprb,
	.rng = zcrypt_msgtype6_rng,
पूर्ण;

अटल काष्ठा zcrypt_ops zcrypt_msgtype6_ep11_ops = अणु
	.owner = THIS_MODULE,
	.name = MSGTYPE06_NAME,
	.variant = MSGTYPE06_VARIANT_EP11,
	.rsa_modexpo = शून्य,
	.rsa_modexpo_crt = शून्य,
	.send_ep11_cprb = zcrypt_msgtype6_send_ep11_cprb,
पूर्ण;

व्योम __init zcrypt_msgtype6_init(व्योम)
अणु
	zcrypt_msgtype_रेजिस्टर(&zcrypt_msgtype6_norng_ops);
	zcrypt_msgtype_रेजिस्टर(&zcrypt_msgtype6_ops);
	zcrypt_msgtype_रेजिस्टर(&zcrypt_msgtype6_ep11_ops);
पूर्ण

व्योम __निकास zcrypt_msgtype6_निकास(व्योम)
अणु
	zcrypt_msgtype_unरेजिस्टर(&zcrypt_msgtype6_norng_ops);
	zcrypt_msgtype_unरेजिस्टर(&zcrypt_msgtype6_ops);
	zcrypt_msgtype_unरेजिस्टर(&zcrypt_msgtype6_ep11_ops);
पूर्ण
