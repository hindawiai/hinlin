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
#समावेश <linux/slab.h>
#समावेश <linux/init.h>
#समावेश <linux/err.h>
#समावेश <linux/atomic.h>
#समावेश <linux/uaccess.h>

#समावेश "ap_bus.h"
#समावेश "zcrypt_api.h"
#समावेश "zcrypt_error.h"
#समावेश "zcrypt_msgtype50.h"

/* >= CEX3A: 4096 bits */
#घोषणा CEX3A_MAX_MOD_SIZE 512

/* CEX2A: max outputdatalength + type80_hdr */
#घोषणा CEX2A_MAX_RESPONSE_SIZE 0x110

/* >= CEX3A: 512 bit modulus, (max outputdatalength) + type80_hdr */
#घोषणा CEX3A_MAX_RESPONSE_SIZE 0x210

MODULE_AUTHOR("IBM Corporation");
MODULE_DESCRIPTION("Cryptographic Accelerator (message type 50), " \
		   "Copyright IBM Corp. 2001, 2012");
MODULE_LICENSE("GPL");

/**
 * The type 50 message family is associated with a CEXxA cards.
 *
 * The four members of the family are described below.
 *
 * Note that all अचिन्हित अक्षर arrays are right-justअगरied and left-padded
 * with zeroes.
 *
 * Note that all reserved fields must be zeroes.
 */
काष्ठा type50_hdr अणु
	अचिन्हित अक्षर	reserved1;
	अचिन्हित अक्षर	msg_type_code;	/* 0x50 */
	अचिन्हित लघु	msg_len;
	अचिन्हित अक्षर	reserved2;
	अचिन्हित अक्षर	ignored;
	अचिन्हित लघु	reserved3;
पूर्ण __packed;

#घोषणा TYPE50_TYPE_CODE	0x50

#घोषणा TYPE50_MEB1_FMT		0x0001
#घोषणा TYPE50_MEB2_FMT		0x0002
#घोषणा TYPE50_MEB3_FMT		0x0003
#घोषणा TYPE50_CRB1_FMT		0x0011
#घोषणा TYPE50_CRB2_FMT		0x0012
#घोषणा TYPE50_CRB3_FMT		0x0013

/* Mod-Exp, with a small modulus */
काष्ठा type50_meb1_msg अणु
	काष्ठा type50_hdr header;
	अचिन्हित लघु	keyblock_type;	/* 0x0001 */
	अचिन्हित अक्षर	reserved[6];
	अचिन्हित अक्षर	exponent[128];
	अचिन्हित अक्षर	modulus[128];
	अचिन्हित अक्षर	message[128];
पूर्ण __packed;

/* Mod-Exp, with a large modulus */
काष्ठा type50_meb2_msg अणु
	काष्ठा type50_hdr header;
	अचिन्हित लघु	keyblock_type;	/* 0x0002 */
	अचिन्हित अक्षर	reserved[6];
	अचिन्हित अक्षर	exponent[256];
	अचिन्हित अक्षर	modulus[256];
	अचिन्हित अक्षर	message[256];
पूर्ण __packed;

/* Mod-Exp, with a larger modulus */
काष्ठा type50_meb3_msg अणु
	काष्ठा type50_hdr header;
	अचिन्हित लघु	keyblock_type;	/* 0x0003 */
	अचिन्हित अक्षर	reserved[6];
	अचिन्हित अक्षर	exponent[512];
	अचिन्हित अक्षर	modulus[512];
	अचिन्हित अक्षर	message[512];
पूर्ण __packed;

/* CRT, with a small modulus */
काष्ठा type50_crb1_msg अणु
	काष्ठा type50_hdr header;
	अचिन्हित लघु	keyblock_type;	/* 0x0011 */
	अचिन्हित अक्षर	reserved[6];
	अचिन्हित अक्षर	p[64];
	अचिन्हित अक्षर	q[64];
	अचिन्हित अक्षर	dp[64];
	अचिन्हित अक्षर	dq[64];
	अचिन्हित अक्षर	u[64];
	अचिन्हित अक्षर	message[128];
पूर्ण __packed;

/* CRT, with a large modulus */
काष्ठा type50_crb2_msg अणु
	काष्ठा type50_hdr header;
	अचिन्हित लघु	keyblock_type;	/* 0x0012 */
	अचिन्हित अक्षर	reserved[6];
	अचिन्हित अक्षर	p[128];
	अचिन्हित अक्षर	q[128];
	अचिन्हित अक्षर	dp[128];
	अचिन्हित अक्षर	dq[128];
	अचिन्हित अक्षर	u[128];
	अचिन्हित अक्षर	message[256];
पूर्ण __packed;

/* CRT, with a larger modulus */
काष्ठा type50_crb3_msg अणु
	काष्ठा type50_hdr header;
	अचिन्हित लघु	keyblock_type;	/* 0x0013 */
	अचिन्हित अक्षर	reserved[6];
	अचिन्हित अक्षर	p[256];
	अचिन्हित अक्षर	q[256];
	अचिन्हित अक्षर	dp[256];
	अचिन्हित अक्षर	dq[256];
	अचिन्हित अक्षर	u[256];
	अचिन्हित अक्षर	message[512];
पूर्ण __packed;

/**
 * The type 80 response family is associated with a CEXxA cards.
 *
 * Note that all अचिन्हित अक्षर arrays are right-justअगरied and left-padded
 * with zeroes.
 *
 * Note that all reserved fields must be zeroes.
 */

#घोषणा TYPE80_RSP_CODE 0x80

काष्ठा type80_hdr अणु
	अचिन्हित अक्षर	reserved1;
	अचिन्हित अक्षर	type;		/* 0x80 */
	अचिन्हित लघु	len;
	अचिन्हित अक्षर	code;		/* 0x00 */
	अचिन्हित अक्षर	reserved2[3];
	अचिन्हित अक्षर	reserved3[8];
पूर्ण __packed;

अचिन्हित पूर्णांक get_rsa_modex_fc(काष्ठा ica_rsa_modexpo *mex, पूर्णांक *fcode)
अणु

	अगर (!mex->inputdatalength)
		वापस -EINVAL;

	अगर (mex->inputdatalength <= 128)	/* 1024 bit */
		*fcode = MEX_1K;
	अन्यथा अगर (mex->inputdatalength <= 256)	/* 2048 bit */
		*fcode = MEX_2K;
	अन्यथा					/* 4096 bit */
		*fcode = MEX_4K;

	वापस 0;
पूर्ण

अचिन्हित पूर्णांक get_rsa_crt_fc(काष्ठा ica_rsa_modexpo_crt *crt, पूर्णांक *fcode)
अणु

	अगर (!crt->inputdatalength)
		वापस -EINVAL;

	अगर (crt->inputdatalength <= 128)	/* 1024 bit */
		*fcode = CRT_1K;
	अन्यथा अगर (crt->inputdatalength <= 256)	/* 2048 bit */
		*fcode = CRT_2K;
	अन्यथा					/* 4096 bit */
		*fcode = CRT_4K;

	वापस 0;
पूर्ण

/**
 * Convert a ICAMEX message to a type50 MEX message.
 *
 * @zq: crypto queue poपूर्णांकer
 * @ap_msg: crypto request poपूर्णांकer
 * @mex: poपूर्णांकer to user input data
 *
 * Returns 0 on success or -EFAULT.
 */
अटल पूर्णांक ICAMEX_msg_to_type50MEX_msg(काष्ठा zcrypt_queue *zq,
				       काष्ठा ap_message *ap_msg,
				       काष्ठा ica_rsa_modexpo *mex)
अणु
	अचिन्हित अक्षर *mod, *exp, *inp;
	पूर्णांक mod_len;

	mod_len = mex->inputdatalength;

	अगर (mod_len <= 128) अणु
		काष्ठा type50_meb1_msg *meb1 = ap_msg->msg;

		स_रखो(meb1, 0, माप(*meb1));
		ap_msg->len = माप(*meb1);
		meb1->header.msg_type_code = TYPE50_TYPE_CODE;
		meb1->header.msg_len = माप(*meb1);
		meb1->keyblock_type = TYPE50_MEB1_FMT;
		mod = meb1->modulus + माप(meb1->modulus) - mod_len;
		exp = meb1->exponent + माप(meb1->exponent) - mod_len;
		inp = meb1->message + माप(meb1->message) - mod_len;
	पूर्ण अन्यथा अगर (mod_len <= 256) अणु
		काष्ठा type50_meb2_msg *meb2 = ap_msg->msg;

		स_रखो(meb2, 0, माप(*meb2));
		ap_msg->len = माप(*meb2);
		meb2->header.msg_type_code = TYPE50_TYPE_CODE;
		meb2->header.msg_len = माप(*meb2);
		meb2->keyblock_type = TYPE50_MEB2_FMT;
		mod = meb2->modulus + माप(meb2->modulus) - mod_len;
		exp = meb2->exponent + माप(meb2->exponent) - mod_len;
		inp = meb2->message + माप(meb2->message) - mod_len;
	पूर्ण अन्यथा अगर (mod_len <= 512) अणु
		काष्ठा type50_meb3_msg *meb3 = ap_msg->msg;

		स_रखो(meb3, 0, माप(*meb3));
		ap_msg->len = माप(*meb3);
		meb3->header.msg_type_code = TYPE50_TYPE_CODE;
		meb3->header.msg_len = माप(*meb3);
		meb3->keyblock_type = TYPE50_MEB3_FMT;
		mod = meb3->modulus + माप(meb3->modulus) - mod_len;
		exp = meb3->exponent + माप(meb3->exponent) - mod_len;
		inp = meb3->message + माप(meb3->message) - mod_len;
	पूर्ण अन्यथा
		वापस -EINVAL;

	अगर (copy_from_user(mod, mex->n_modulus, mod_len) ||
	    copy_from_user(exp, mex->b_key, mod_len) ||
	    copy_from_user(inp, mex->inputdata, mod_len))
		वापस -EFAULT;

#अगर_घोषित CONFIG_ZCRYPT_DEBUG
	अगर (ap_msg->fi.flags & AP_FI_FLAG_TOGGLE_SPECIAL)
		ap_msg->flags ^= AP_MSG_FLAG_SPECIAL;
#पूर्ण_अगर

	वापस 0;
पूर्ण

/**
 * Convert a ICACRT message to a type50 CRT message.
 *
 * @zq: crypto queue poपूर्णांकer
 * @ap_msg: crypto request poपूर्णांकer
 * @crt: poपूर्णांकer to user input data
 *
 * Returns 0 on success or -EFAULT.
 */
अटल पूर्णांक ICACRT_msg_to_type50CRT_msg(काष्ठा zcrypt_queue *zq,
				       काष्ठा ap_message *ap_msg,
				       काष्ठा ica_rsa_modexpo_crt *crt)
अणु
	पूर्णांक mod_len, लघु_len;
	अचिन्हित अक्षर *p, *q, *dp, *dq, *u, *inp;

	mod_len = crt->inputdatalength;
	लघु_len = (mod_len + 1) / 2;

	/*
	 * CEX2A and CEX3A w/o FW update can handle requests up to
	 * 256 byte modulus (2k keys).
	 * CEX3A with FW update and newer CEXxA cards are able to handle
	 * 512 byte modulus (4k keys).
	 */
	अगर (mod_len <= 128) अणु		/* up to 1024 bit key size */
		काष्ठा type50_crb1_msg *crb1 = ap_msg->msg;

		स_रखो(crb1, 0, माप(*crb1));
		ap_msg->len = माप(*crb1);
		crb1->header.msg_type_code = TYPE50_TYPE_CODE;
		crb1->header.msg_len = माप(*crb1);
		crb1->keyblock_type = TYPE50_CRB1_FMT;
		p = crb1->p + माप(crb1->p) - लघु_len;
		q = crb1->q + माप(crb1->q) - लघु_len;
		dp = crb1->dp + माप(crb1->dp) - लघु_len;
		dq = crb1->dq + माप(crb1->dq) - लघु_len;
		u = crb1->u + माप(crb1->u) - लघु_len;
		inp = crb1->message + माप(crb1->message) - mod_len;
	पूर्ण अन्यथा अगर (mod_len <= 256) अणु	/* up to 2048 bit key size */
		काष्ठा type50_crb2_msg *crb2 = ap_msg->msg;

		स_रखो(crb2, 0, माप(*crb2));
		ap_msg->len = माप(*crb2);
		crb2->header.msg_type_code = TYPE50_TYPE_CODE;
		crb2->header.msg_len = माप(*crb2);
		crb2->keyblock_type = TYPE50_CRB2_FMT;
		p = crb2->p + माप(crb2->p) - लघु_len;
		q = crb2->q + माप(crb2->q) - लघु_len;
		dp = crb2->dp + माप(crb2->dp) - लघु_len;
		dq = crb2->dq + माप(crb2->dq) - लघु_len;
		u = crb2->u + माप(crb2->u) - लघु_len;
		inp = crb2->message + माप(crb2->message) - mod_len;
	पूर्ण अन्यथा अगर ((mod_len <= 512) &&	/* up to 4096 bit key size */
		   (zq->zcard->max_mod_size == CEX3A_MAX_MOD_SIZE)) अणु
		काष्ठा type50_crb3_msg *crb3 = ap_msg->msg;

		स_रखो(crb3, 0, माप(*crb3));
		ap_msg->len = माप(*crb3);
		crb3->header.msg_type_code = TYPE50_TYPE_CODE;
		crb3->header.msg_len = माप(*crb3);
		crb3->keyblock_type = TYPE50_CRB3_FMT;
		p = crb3->p + माप(crb3->p) - लघु_len;
		q = crb3->q + माप(crb3->q) - लघु_len;
		dp = crb3->dp + माप(crb3->dp) - लघु_len;
		dq = crb3->dq + माप(crb3->dq) - लघु_len;
		u = crb3->u + माप(crb3->u) - लघु_len;
		inp = crb3->message + माप(crb3->message) - mod_len;
	पूर्ण अन्यथा
		वापस -EINVAL;

	/*
	 * correct the offset of p, bp and mult_inv according zcrypt.h
	 * block size right aligned (skip the first byte)
	 */
	अगर (copy_from_user(p, crt->np_prime + MSGTYPE_ADJUSTMENT, लघु_len) ||
	    copy_from_user(q, crt->nq_prime, लघु_len) ||
	    copy_from_user(dp, crt->bp_key + MSGTYPE_ADJUSTMENT, लघु_len) ||
	    copy_from_user(dq, crt->bq_key, लघु_len) ||
	    copy_from_user(u, crt->u_mult_inv + MSGTYPE_ADJUSTMENT, लघु_len) ||
	    copy_from_user(inp, crt->inputdata, mod_len))
		वापस -EFAULT;

#अगर_घोषित CONFIG_ZCRYPT_DEBUG
	अगर (ap_msg->fi.flags & AP_FI_FLAG_TOGGLE_SPECIAL)
		ap_msg->flags ^= AP_MSG_FLAG_SPECIAL;
#पूर्ण_अगर

	वापस 0;
पूर्ण

/**
 * Copy results from a type 80 reply message back to user space.
 *
 * @zq: crypto device poपूर्णांकer
 * @reply: reply AP message.
 * @data: poपूर्णांकer to user output data
 * @length: size of user output data
 *
 * Returns 0 on success or -EFAULT.
 */
अटल पूर्णांक convert_type80(काष्ठा zcrypt_queue *zq,
			  काष्ठा ap_message *reply,
			  अक्षर __user *outputdata,
			  अचिन्हित पूर्णांक outputdatalength)
अणु
	काष्ठा type80_hdr *t80h = reply->msg;
	अचिन्हित अक्षर *data;

	अगर (t80h->len < माप(*t80h) + outputdatalength) अणु
		/* The result is too लघु, the CEXxA card may not करो that.. */
		zq->online = 0;
		pr_err("Crypto dev=%02x.%04x code=0x%02x => online=0 rc=EAGAIN\n",
		       AP_QID_CARD(zq->queue->qid),
		       AP_QID_QUEUE(zq->queue->qid),
		       t80h->code);
		ZCRYPT_DBF_ERR("dev=%02x.%04x code=0x%02x => online=0 rc=EAGAIN\n",
			       AP_QID_CARD(zq->queue->qid),
			       AP_QID_QUEUE(zq->queue->qid),
			       t80h->code);
		वापस -EAGAIN;
	पूर्ण
	अगर (zq->zcard->user_space_type == ZCRYPT_CEX2A)
		BUG_ON(t80h->len > CEX2A_MAX_RESPONSE_SIZE);
	अन्यथा
		BUG_ON(t80h->len > CEX3A_MAX_RESPONSE_SIZE);
	data = reply->msg + t80h->len - outputdatalength;
	अगर (copy_to_user(outputdata, data, outputdatalength))
		वापस -EFAULT;
	वापस 0;
पूर्ण

अटल पूर्णांक convert_response_cex2a(काष्ठा zcrypt_queue *zq,
				  काष्ठा ap_message *reply,
				  अक्षर __user *outputdata,
				  अचिन्हित पूर्णांक outputdatalength)
अणु
	/* Response type byte is the second byte in the response. */
	अचिन्हित अक्षर rtype = ((अचिन्हित अक्षर *) reply->msg)[1];

	चयन (rtype) अणु
	हाल TYPE82_RSP_CODE:
	हाल TYPE88_RSP_CODE:
		वापस convert_error(zq, reply);
	हाल TYPE80_RSP_CODE:
		वापस convert_type80(zq, reply,
				      outputdata, outputdatalength);
	शेष: /* Unknown response type, this should NEVER EVER happen */
		zq->online = 0;
		pr_err("Crypto dev=%02x.%04x unknown response type 0x%02x => online=0 rc=EAGAIN\n",
		       AP_QID_CARD(zq->queue->qid),
		       AP_QID_QUEUE(zq->queue->qid),
		       (पूर्णांक) rtype);
		ZCRYPT_DBF_ERR("dev=%02x.%04x unknown response type 0x%02x => online=0 rc=EAGAIN\n",
			       AP_QID_CARD(zq->queue->qid),
			       AP_QID_QUEUE(zq->queue->qid),
			       (पूर्णांक) rtype);
		वापस -EAGAIN;
	पूर्ण
पूर्ण

/**
 * This function is called from the AP bus code after a crypto request
 * "msg" has finished with the reply message "reply".
 * It is called from tasklet context.
 * @aq: poपूर्णांकer to the AP device
 * @msg: poपूर्णांकer to the AP message
 * @reply: poपूर्णांकer to the AP reply message
 */
अटल व्योम zcrypt_cex2a_receive(काष्ठा ap_queue *aq,
				 काष्ठा ap_message *msg,
				 काष्ठा ap_message *reply)
अणु
	अटल काष्ठा error_hdr error_reply = अणु
		.type = TYPE82_RSP_CODE,
		.reply_code = REP82_ERROR_MACHINE_FAILURE,
	पूर्ण;
	काष्ठा type80_hdr *t80h;
	पूर्णांक len;

	/* Copy the reply message to the request message buffer. */
	अगर (!reply)
		जाओ out;	/* ap_msg->rc indicates the error */
	t80h = reply->msg;
	अगर (t80h->type == TYPE80_RSP_CODE) अणु
		अगर (aq->ap_dev.device_type == AP_DEVICE_TYPE_CEX2A)
			len = min_t(पूर्णांक, CEX2A_MAX_RESPONSE_SIZE, t80h->len);
		अन्यथा
			len = min_t(पूर्णांक, CEX3A_MAX_RESPONSE_SIZE, t80h->len);
		स_नकल(msg->msg, reply->msg, len);
	पूर्ण अन्यथा
		स_नकल(msg->msg, reply->msg, माप(error_reply));
out:
	complete((काष्ठा completion *) msg->निजी);
पूर्ण

अटल atomic_t zcrypt_step = ATOMIC_INIT(0);

/**
 * The request distributor calls this function अगर it picked the CEXxA
 * device to handle a modexpo request.
 * @zq: poपूर्णांकer to zcrypt_queue काष्ठाure that identअगरies the
 *	CEXxA device to the request distributor
 * @mex: poपूर्णांकer to the modexpo request buffer
 */
अटल दीर्घ zcrypt_cex2a_modexpo(काष्ठा zcrypt_queue *zq,
				 काष्ठा ica_rsa_modexpo *mex,
				 काष्ठा ap_message *ap_msg)
अणु
	काष्ठा completion work;
	पूर्णांक rc;

	अगर (zq->zcard->user_space_type == ZCRYPT_CEX2A)
		ap_msg->msg = kदो_स्मृति(MSGTYPE50_CRB2_MAX_MSG_SIZE, GFP_KERNEL);
	अन्यथा
		ap_msg->msg = kदो_स्मृति(MSGTYPE50_CRB3_MAX_MSG_SIZE, GFP_KERNEL);
	अगर (!ap_msg->msg)
		वापस -ENOMEM;
	ap_msg->receive = zcrypt_cex2a_receive;
	ap_msg->psmid = (((अचिन्हित दीर्घ दीर्घ) current->pid) << 32) +
		atomic_inc_वापस(&zcrypt_step);
	ap_msg->निजी = &work;
	rc = ICAMEX_msg_to_type50MEX_msg(zq, ap_msg, mex);
	अगर (rc)
		जाओ out;
	init_completion(&work);
	rc = ap_queue_message(zq->queue, ap_msg);
	अगर (rc)
		जाओ out;
	rc = रुको_क्रम_completion_पूर्णांकerruptible(&work);
	अगर (rc == 0) अणु
		rc = ap_msg->rc;
		अगर (rc == 0)
			rc = convert_response_cex2a(zq, ap_msg,
						    mex->outputdata,
						    mex->outputdatalength);
	पूर्ण अन्यथा
		/* Signal pending. */
		ap_cancel_message(zq->queue, ap_msg);
out:
	ap_msg->निजी = शून्य;
	वापस rc;
पूर्ण

/**
 * The request distributor calls this function अगर it picked the CEXxA
 * device to handle a modexpo_crt request.
 * @zq: poपूर्णांकer to zcrypt_queue काष्ठाure that identअगरies the
 *	CEXxA device to the request distributor
 * @crt: poपूर्णांकer to the modexpoc_crt request buffer
 */
अटल दीर्घ zcrypt_cex2a_modexpo_crt(काष्ठा zcrypt_queue *zq,
				     काष्ठा ica_rsa_modexpo_crt *crt,
				     काष्ठा ap_message *ap_msg)
अणु
	काष्ठा completion work;
	पूर्णांक rc;

	अगर (zq->zcard->user_space_type == ZCRYPT_CEX2A)
		ap_msg->msg = kदो_स्मृति(MSGTYPE50_CRB2_MAX_MSG_SIZE, GFP_KERNEL);
	अन्यथा
		ap_msg->msg = kदो_स्मृति(MSGTYPE50_CRB3_MAX_MSG_SIZE, GFP_KERNEL);
	अगर (!ap_msg->msg)
		वापस -ENOMEM;
	ap_msg->receive = zcrypt_cex2a_receive;
	ap_msg->psmid = (((अचिन्हित दीर्घ दीर्घ) current->pid) << 32) +
		atomic_inc_वापस(&zcrypt_step);
	ap_msg->निजी = &work;
	rc = ICACRT_msg_to_type50CRT_msg(zq, ap_msg, crt);
	अगर (rc)
		जाओ out;
	init_completion(&work);
	rc = ap_queue_message(zq->queue, ap_msg);
	अगर (rc)
		जाओ out;
	rc = रुको_क्रम_completion_पूर्णांकerruptible(&work);
	अगर (rc == 0) अणु
		rc = ap_msg->rc;
		अगर (rc == 0)
			rc = convert_response_cex2a(zq, ap_msg,
						    crt->outputdata,
						    crt->outputdatalength);
	पूर्ण अन्यथा
		/* Signal pending. */
		ap_cancel_message(zq->queue, ap_msg);
out:
	ap_msg->निजी = शून्य;
	वापस rc;
पूर्ण

/**
 * The crypto operations क्रम message type 50.
 */
अटल काष्ठा zcrypt_ops zcrypt_msgtype50_ops = अणु
	.rsa_modexpo = zcrypt_cex2a_modexpo,
	.rsa_modexpo_crt = zcrypt_cex2a_modexpo_crt,
	.owner = THIS_MODULE,
	.name = MSGTYPE50_NAME,
	.variant = MSGTYPE50_VARIANT_DEFAULT,
पूर्ण;

व्योम __init zcrypt_msgtype50_init(व्योम)
अणु
	zcrypt_msgtype_रेजिस्टर(&zcrypt_msgtype50_ops);
पूर्ण

व्योम __निकास zcrypt_msgtype50_निकास(व्योम)
अणु
	zcrypt_msgtype_unरेजिस्टर(&zcrypt_msgtype50_ops);
पूर्ण
