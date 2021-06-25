<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright(c) 2008 Intel Corporation. All rights reserved.
 *
 * Maपूर्णांकained at www.Open-FCoE.org
 */

/*
 * Provide पूर्णांकerface to send ELS/CT FC frames
 */

#समावेश <linux/export.h>
#समावेश <यंत्र/unaligned.h>
#समावेश <scsi/fc/fc_gs.h>
#समावेश <scsi/fc/fc_ns.h>
#समावेश <scsi/fc/fc_els.h>
#समावेश <scsi/libfc.h>
#समावेश "fc_encode.h"
#समावेश "fc_libfc.h"

/**
 * fc_elsct_send() - Send an ELS or CT frame
 * @lport:	The local port to send the frame on
 * @did:	The destination ID क्रम the frame
 * @fp:		The frame to be sent
 * @op:		The operational code
 * @resp:	The callback routine when the response is received
 * @arg:	The argument to pass to the response callback routine
 * @समयr_msec: The समयout period क्रम the frame (in msecs)
 */
काष्ठा fc_seq *fc_elsct_send(काष्ठा fc_lport *lport, u32 did,
			     काष्ठा fc_frame *fp, अचिन्हित पूर्णांक op,
			     व्योम (*resp)(काष्ठा fc_seq *,
					  काष्ठा fc_frame *,
					  व्योम *),
			     व्योम *arg, u32 समयr_msec)
अणु
	क्रमागत fc_rctl r_ctl;
	क्रमागत fc_fh_type fh_type;
	पूर्णांक rc;

	/* ELS requests */
	अगर ((op >= ELS_LS_RJT) && (op <= ELS_AUTH_ELS))
		rc = fc_els_fill(lport, did, fp, op, &r_ctl, &fh_type);
	अन्यथा अणु
		/* CT requests */
		rc = fc_ct_fill(lport, did, fp, op, &r_ctl, &fh_type, &did);
	पूर्ण

	अगर (rc) अणु
		fc_frame_मुक्त(fp);
		वापस शून्य;
	पूर्ण

	fc_fill_fc_hdr(fp, r_ctl, did, lport->port_id, fh_type,
		       FC_FCTL_REQ, 0);

	वापस fc_exch_seq_send(lport, fp, resp, शून्य, arg, समयr_msec);
पूर्ण
EXPORT_SYMBOL(fc_elsct_send);

/**
 * fc_elsct_init() - Initialize the ELS/CT layer
 * @lport: The local port to initialize the ELS/CT layer क्रम
 */
पूर्णांक fc_elsct_init(काष्ठा fc_lport *lport)
अणु
	अगर (!lport->tt.elsct_send)
		lport->tt.elsct_send = fc_elsct_send;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(fc_elsct_init);

/**
 * fc_els_resp_type() - Return a string describing the ELS response
 * @fp: The frame poपूर्णांकer or possible error code
 */
स्थिर अक्षर *fc_els_resp_type(काष्ठा fc_frame *fp)
अणु
	स्थिर अक्षर *msg;
	काष्ठा fc_frame_header *fh;
	काष्ठा fc_ct_hdr *ct;

	अगर (IS_ERR(fp)) अणु
		चयन (-PTR_ERR(fp)) अणु
		हाल FC_NO_ERR:
			msg = "response no error";
			अवरोध;
		हाल FC_EX_TIMEOUT:
			msg = "response timeout";
			अवरोध;
		हाल FC_EX_CLOSED:
			msg = "response closed";
			अवरोध;
		शेष:
			msg = "response unknown error";
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		fh = fc_frame_header_get(fp);
		चयन (fh->fh_type) अणु
		हाल FC_TYPE_ELS:
			चयन (fc_frame_payload_op(fp)) अणु
			हाल ELS_LS_ACC:
				msg = "accept";
				अवरोध;
			हाल ELS_LS_RJT:
				msg = "reject";
				अवरोध;
			शेष:
				msg = "response unknown ELS";
				अवरोध;
			पूर्ण
			अवरोध;
		हाल FC_TYPE_CT:
			ct = fc_frame_payload_get(fp, माप(*ct));
			अगर (ct) अणु
				चयन (ntohs(ct->ct_cmd)) अणु
				हाल FC_FS_ACC:
					msg = "CT accept";
					अवरोध;
				हाल FC_FS_RJT:
					msg = "CT reject";
					अवरोध;
				शेष:
					msg = "response unknown CT";
					अवरोध;
				पूर्ण
			पूर्ण अन्यथा अणु
				msg = "short CT response";
			पूर्ण
			अवरोध;
		शेष:
			msg = "response not ELS or CT";
			अवरोध;
		पूर्ण
	पूर्ण
	वापस msg;
पूर्ण
