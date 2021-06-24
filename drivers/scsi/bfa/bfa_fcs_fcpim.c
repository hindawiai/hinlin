<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2005-2014 Brocade Communications Systems, Inc.
 * Copyright (c) 2014- QLogic Corporation.
 * All rights reserved
 * www.qlogic.com
 *
 * Linux driver क्रम QLogic BR-series Fibre Channel Host Bus Adapter.
 */

/*
 *  fcpim.c - FCP initiator mode i-t nexus state machine
 */

#समावेश "bfad_drv.h"
#समावेश "bfa_fcs.h"
#समावेश "bfa_fcbuild.h"
#समावेश "bfad_im.h"

BFA_TRC_खाता(FCS, FCPIM);

/*
 * क्रमward declarations
 */
अटल व्योम	bfa_fcs_itnim_समयout(व्योम *arg);
अटल व्योम	bfa_fcs_itnim_मुक्त(काष्ठा bfa_fcs_itnim_s *itnim);
अटल व्योम	bfa_fcs_itnim_send_prli(व्योम *itnim_cbarg,
					काष्ठा bfa_fcxp_s *fcxp_alloced);
अटल व्योम	bfa_fcs_itnim_prli_response(व्योम *fcsarg,
			 काष्ठा bfa_fcxp_s *fcxp, व्योम *cbarg,
			    bfa_status_t req_status, u32 rsp_len,
			    u32 resid_len, काष्ठा fchs_s *rsp_fchs);
अटल व्योम	bfa_fcs_itnim_aen_post(काष्ठा bfa_fcs_itnim_s *itnim,
			क्रमागत bfa_itnim_aen_event event);

अटल व्योम	bfa_fcs_itnim_sm_offline(काष्ठा bfa_fcs_itnim_s *itnim,
					 क्रमागत bfa_fcs_itnim_event event);
अटल व्योम	bfa_fcs_itnim_sm_prli_send(काष्ठा bfa_fcs_itnim_s *itnim,
					   क्रमागत bfa_fcs_itnim_event event);
अटल व्योम	bfa_fcs_itnim_sm_prli(काष्ठा bfa_fcs_itnim_s *itnim,
				      क्रमागत bfa_fcs_itnim_event event);
अटल व्योम	bfa_fcs_itnim_sm_prli_retry(काष्ठा bfa_fcs_itnim_s *itnim,
					    क्रमागत bfa_fcs_itnim_event event);
अटल व्योम	bfa_fcs_itnim_sm_hcb_online(काष्ठा bfa_fcs_itnim_s *itnim,
					    क्रमागत bfa_fcs_itnim_event event);
अटल व्योम	bfa_fcs_itnim_sm_hal_rport_online(काष्ठा bfa_fcs_itnim_s *itnim,
					क्रमागत bfa_fcs_itnim_event event);
अटल व्योम	bfa_fcs_itnim_sm_online(काष्ठा bfa_fcs_itnim_s *itnim,
					क्रमागत bfa_fcs_itnim_event event);
अटल व्योम	bfa_fcs_itnim_sm_hcb_offline(काष्ठा bfa_fcs_itnim_s *itnim,
					     क्रमागत bfa_fcs_itnim_event event);
अटल व्योम	bfa_fcs_itnim_sm_initiator(काष्ठा bfa_fcs_itnim_s *itnim,
					   क्रमागत bfa_fcs_itnim_event event);

अटल काष्ठा bfa_sm_table_s itnim_sm_table[] = अणु
	अणुBFA_SM(bfa_fcs_itnim_sm_offline), BFA_ITNIM_OFFLINEपूर्ण,
	अणुBFA_SM(bfa_fcs_itnim_sm_prli_send), BFA_ITNIM_PRLI_SENDपूर्ण,
	अणुBFA_SM(bfa_fcs_itnim_sm_prli), BFA_ITNIM_PRLI_SENTपूर्ण,
	अणुBFA_SM(bfa_fcs_itnim_sm_prli_retry), BFA_ITNIM_PRLI_RETRYपूर्ण,
	अणुBFA_SM(bfa_fcs_itnim_sm_hcb_online), BFA_ITNIM_HCB_ONLINEपूर्ण,
	अणुBFA_SM(bfa_fcs_itnim_sm_online), BFA_ITNIM_ONLINEपूर्ण,
	अणुBFA_SM(bfa_fcs_itnim_sm_hcb_offline), BFA_ITNIM_HCB_OFFLINEपूर्ण,
	अणुBFA_SM(bfa_fcs_itnim_sm_initiator), BFA_ITNIM_INITIATIORपूर्ण,
पूर्ण;

/*
 *  fcs_itnim_sm FCS itnim state machine
 */

अटल व्योम
bfa_fcs_itnim_sm_offline(काष्ठा bfa_fcs_itnim_s *itnim,
		 क्रमागत bfa_fcs_itnim_event event)
अणु
	bfa_trc(itnim->fcs, itnim->rport->pwwn);
	bfa_trc(itnim->fcs, event);

	चयन (event) अणु
	हाल BFA_FCS_ITNIM_SM_FCS_ONLINE:
		bfa_sm_set_state(itnim, bfa_fcs_itnim_sm_prli_send);
		itnim->prli_retries = 0;
		bfa_fcs_itnim_send_prli(itnim, शून्य);
		अवरोध;

	हाल BFA_FCS_ITNIM_SM_OFFLINE:
		bfa_sm_send_event(itnim->rport, RPSM_EVENT_FC4_OFFLINE);
		अवरोध;

	हाल BFA_FCS_ITNIM_SM_INITIATOR:
		bfa_sm_set_state(itnim, bfa_fcs_itnim_sm_initiator);
		अवरोध;

	हाल BFA_FCS_ITNIM_SM_DELETE:
		bfa_fcs_itnim_मुक्त(itnim);
		अवरोध;

	शेष:
		bfa_sm_fault(itnim->fcs, event);
	पूर्ण

पूर्ण

अटल व्योम
bfa_fcs_itnim_sm_prli_send(काष्ठा bfa_fcs_itnim_s *itnim,
		 क्रमागत bfa_fcs_itnim_event event)
अणु
	bfa_trc(itnim->fcs, itnim->rport->pwwn);
	bfa_trc(itnim->fcs, event);

	चयन (event) अणु
	हाल BFA_FCS_ITNIM_SM_FRMSENT:
		bfa_sm_set_state(itnim, bfa_fcs_itnim_sm_prli);
		अवरोध;

	हाल BFA_FCS_ITNIM_SM_INITIATOR:
		bfa_sm_set_state(itnim, bfa_fcs_itnim_sm_initiator);
		bfa_fcxp_walloc_cancel(itnim->fcs->bfa, &itnim->fcxp_wqe);
		bfa_sm_send_event(itnim->rport, RPSM_EVENT_FC4_FCS_ONLINE);
		अवरोध;

	हाल BFA_FCS_ITNIM_SM_OFFLINE:
		bfa_sm_set_state(itnim, bfa_fcs_itnim_sm_offline);
		bfa_fcxp_walloc_cancel(itnim->fcs->bfa, &itnim->fcxp_wqe);
		bfa_sm_send_event(itnim->rport, RPSM_EVENT_FC4_OFFLINE);
		अवरोध;

	हाल BFA_FCS_ITNIM_SM_DELETE:
		bfa_sm_set_state(itnim, bfa_fcs_itnim_sm_offline);
		bfa_fcxp_walloc_cancel(itnim->fcs->bfa, &itnim->fcxp_wqe);
		bfa_fcs_itnim_मुक्त(itnim);
		अवरोध;

	शेष:
		bfa_sm_fault(itnim->fcs, event);
	पूर्ण
पूर्ण

अटल व्योम
bfa_fcs_itnim_sm_prli(काष्ठा bfa_fcs_itnim_s *itnim,
		 क्रमागत bfa_fcs_itnim_event event)
अणु
	bfa_trc(itnim->fcs, itnim->rport->pwwn);
	bfa_trc(itnim->fcs, event);

	चयन (event) अणु
	हाल BFA_FCS_ITNIM_SM_RSP_OK:
		अगर (itnim->rport->scsi_function == BFA_RPORT_INITIATOR)
			bfa_sm_set_state(itnim, bfa_fcs_itnim_sm_initiator);
		अन्यथा
			bfa_sm_set_state(itnim,
				bfa_fcs_itnim_sm_hal_rport_online);

		bfa_sm_send_event(itnim->rport, RPSM_EVENT_FC4_FCS_ONLINE);
		अवरोध;

	हाल BFA_FCS_ITNIM_SM_RSP_ERROR:
		bfa_sm_set_state(itnim, bfa_fcs_itnim_sm_prli_retry);
		bfa_समयr_start(itnim->fcs->bfa, &itnim->समयr,
				bfa_fcs_itnim_समयout, itnim,
				BFA_FCS_RETRY_TIMEOUT);
		अवरोध;

	हाल BFA_FCS_ITNIM_SM_RSP_NOT_SUPP:
		bfa_sm_set_state(itnim, bfa_fcs_itnim_sm_offline);
		अवरोध;

	हाल BFA_FCS_ITNIM_SM_OFFLINE:
		bfa_sm_set_state(itnim, bfa_fcs_itnim_sm_offline);
		bfa_fcxp_discard(itnim->fcxp);
		bfa_sm_send_event(itnim->rport, RPSM_EVENT_FC4_OFFLINE);
		अवरोध;

	हाल BFA_FCS_ITNIM_SM_INITIATOR:
		bfa_sm_set_state(itnim, bfa_fcs_itnim_sm_initiator);
		bfa_fcxp_discard(itnim->fcxp);
		bfa_sm_send_event(itnim->rport, RPSM_EVENT_FC4_FCS_ONLINE);
		अवरोध;

	हाल BFA_FCS_ITNIM_SM_DELETE:
		bfa_sm_set_state(itnim, bfa_fcs_itnim_sm_offline);
		bfa_fcxp_discard(itnim->fcxp);
		bfa_fcs_itnim_मुक्त(itnim);
		अवरोध;

	शेष:
		bfa_sm_fault(itnim->fcs, event);
	पूर्ण
पूर्ण

अटल व्योम
bfa_fcs_itnim_sm_hal_rport_online(काष्ठा bfa_fcs_itnim_s *itnim,
				क्रमागत bfa_fcs_itnim_event event)
अणु
	bfa_trc(itnim->fcs, itnim->rport->pwwn);
	bfa_trc(itnim->fcs, event);

	चयन (event) अणु
	हाल BFA_FCS_ITNIM_SM_HAL_ONLINE:
		अगर (!itnim->bfa_itnim)
			itnim->bfa_itnim = bfa_itnim_create(itnim->fcs->bfa,
					itnim->rport->bfa_rport, itnim);

		अगर (itnim->bfa_itnim) अणु
			bfa_sm_set_state(itnim, bfa_fcs_itnim_sm_hcb_online);
			bfa_itnim_online(itnim->bfa_itnim, itnim->seq_rec);
		पूर्ण अन्यथा अणु
			bfa_sm_set_state(itnim, bfa_fcs_itnim_sm_offline);
			bfa_sm_send_event(itnim->rport, RPSM_EVENT_DELETE);
		पूर्ण

		अवरोध;

	हाल BFA_FCS_ITNIM_SM_OFFLINE:
		bfa_sm_set_state(itnim, bfa_fcs_itnim_sm_offline);
		bfa_sm_send_event(itnim->rport, RPSM_EVENT_FC4_OFFLINE);
		अवरोध;

	हाल BFA_FCS_ITNIM_SM_DELETE:
		bfa_sm_set_state(itnim, bfa_fcs_itnim_sm_offline);
		bfa_fcs_itnim_मुक्त(itnim);
		अवरोध;

	शेष:
		bfa_sm_fault(itnim->fcs, event);
	पूर्ण
पूर्ण

अटल व्योम
bfa_fcs_itnim_sm_prli_retry(काष्ठा bfa_fcs_itnim_s *itnim,
			    क्रमागत bfa_fcs_itnim_event event)
अणु
	bfa_trc(itnim->fcs, itnim->rport->pwwn);
	bfa_trc(itnim->fcs, event);

	चयन (event) अणु
	हाल BFA_FCS_ITNIM_SM_TIMEOUT:
		अगर (itnim->prli_retries < BFA_FCS_RPORT_MAX_RETRIES) अणु
			itnim->prli_retries++;
			bfa_trc(itnim->fcs, itnim->prli_retries);
			bfa_sm_set_state(itnim, bfa_fcs_itnim_sm_prli_send);
			bfa_fcs_itnim_send_prli(itnim, शून्य);
		पूर्ण अन्यथा अणु
			/* invoke target offline */
			bfa_sm_set_state(itnim, bfa_fcs_itnim_sm_offline);
			bfa_sm_send_event(itnim->rport, RPSM_EVENT_LOGO_IMP);
		पूर्ण
		अवरोध;


	हाल BFA_FCS_ITNIM_SM_OFFLINE:
		bfa_sm_set_state(itnim, bfa_fcs_itnim_sm_offline);
		bfa_समयr_stop(&itnim->समयr);
		bfa_sm_send_event(itnim->rport, RPSM_EVENT_FC4_OFFLINE);
		अवरोध;

	हाल BFA_FCS_ITNIM_SM_INITIATOR:
		bfa_sm_set_state(itnim, bfa_fcs_itnim_sm_initiator);
		bfa_समयr_stop(&itnim->समयr);
		bfa_sm_send_event(itnim->rport, RPSM_EVENT_FC4_FCS_ONLINE);
		अवरोध;

	हाल BFA_FCS_ITNIM_SM_DELETE:
		bfa_sm_set_state(itnim, bfa_fcs_itnim_sm_offline);
		bfa_समयr_stop(&itnim->समयr);
		bfa_fcs_itnim_मुक्त(itnim);
		अवरोध;

	शेष:
		bfa_sm_fault(itnim->fcs, event);
	पूर्ण
पूर्ण

अटल व्योम
bfa_fcs_itnim_sm_hcb_online(काष्ठा bfa_fcs_itnim_s *itnim,
			    क्रमागत bfa_fcs_itnim_event event)
अणु
	काष्ठा bfad_s *bfad = (काष्ठा bfad_s *)itnim->fcs->bfad;
	अक्षर	lpwwn_buf[BFA_STRING_32];
	अक्षर	rpwwn_buf[BFA_STRING_32];

	bfa_trc(itnim->fcs, itnim->rport->pwwn);
	bfa_trc(itnim->fcs, event);

	चयन (event) अणु
	हाल BFA_FCS_ITNIM_SM_HCB_ONLINE:
		bfa_sm_set_state(itnim, bfa_fcs_itnim_sm_online);
		bfa_fcb_itnim_online(itnim->itnim_drv);
		wwn2str(lpwwn_buf, bfa_fcs_lport_get_pwwn(itnim->rport->port));
		wwn2str(rpwwn_buf, itnim->rport->pwwn);
		BFA_LOG(KERN_INFO, bfad, bfa_log_level,
		"Target (WWN = %s) is online for initiator (WWN = %s)\n",
		rpwwn_buf, lpwwn_buf);
		bfa_fcs_itnim_aen_post(itnim, BFA_ITNIM_AEN_ONLINE);
		अवरोध;

	हाल BFA_FCS_ITNIM_SM_OFFLINE:
		bfa_sm_set_state(itnim, bfa_fcs_itnim_sm_hcb_offline);
		bfa_itnim_offline(itnim->bfa_itnim);
		अवरोध;

	हाल BFA_FCS_ITNIM_SM_DELETE:
		bfa_sm_set_state(itnim, bfa_fcs_itnim_sm_offline);
		bfa_fcs_itnim_मुक्त(itnim);
		अवरोध;

	शेष:
		bfa_sm_fault(itnim->fcs, event);
	पूर्ण
पूर्ण

अटल व्योम
bfa_fcs_itnim_sm_online(काष्ठा bfa_fcs_itnim_s *itnim,
		 क्रमागत bfa_fcs_itnim_event event)
अणु
	काष्ठा bfad_s *bfad = (काष्ठा bfad_s *)itnim->fcs->bfad;
	अक्षर	lpwwn_buf[BFA_STRING_32];
	अक्षर	rpwwn_buf[BFA_STRING_32];

	bfa_trc(itnim->fcs, itnim->rport->pwwn);
	bfa_trc(itnim->fcs, event);

	चयन (event) अणु
	हाल BFA_FCS_ITNIM_SM_OFFLINE:
		bfa_sm_set_state(itnim, bfa_fcs_itnim_sm_hcb_offline);
		bfa_fcb_itnim_offline(itnim->itnim_drv);
		bfa_itnim_offline(itnim->bfa_itnim);
		wwn2str(lpwwn_buf, bfa_fcs_lport_get_pwwn(itnim->rport->port));
		wwn2str(rpwwn_buf, itnim->rport->pwwn);
		अगर (bfa_fcs_lport_is_online(itnim->rport->port) == BFA_TRUE) अणु
			BFA_LOG(KERN_ERR, bfad, bfa_log_level,
			"Target (WWN = %s) connectivity lost for "
			"initiator (WWN = %s)\n", rpwwn_buf, lpwwn_buf);
			bfa_fcs_itnim_aen_post(itnim, BFA_ITNIM_AEN_DISCONNECT);
		पूर्ण अन्यथा अणु
			BFA_LOG(KERN_INFO, bfad, bfa_log_level,
			"Target (WWN = %s) offlined by initiator (WWN = %s)\n",
			rpwwn_buf, lpwwn_buf);
			bfa_fcs_itnim_aen_post(itnim, BFA_ITNIM_AEN_OFFLINE);
		पूर्ण
		अवरोध;

	हाल BFA_FCS_ITNIM_SM_DELETE:
		bfa_sm_set_state(itnim, bfa_fcs_itnim_sm_offline);
		bfa_fcs_itnim_मुक्त(itnim);
		अवरोध;

	शेष:
		bfa_sm_fault(itnim->fcs, event);
	पूर्ण
पूर्ण

अटल व्योम
bfa_fcs_itnim_sm_hcb_offline(काष्ठा bfa_fcs_itnim_s *itnim,
			     क्रमागत bfa_fcs_itnim_event event)
अणु
	bfa_trc(itnim->fcs, itnim->rport->pwwn);
	bfa_trc(itnim->fcs, event);

	चयन (event) अणु
	हाल BFA_FCS_ITNIM_SM_HCB_OFFLINE:
		bfa_sm_set_state(itnim, bfa_fcs_itnim_sm_offline);
		bfa_sm_send_event(itnim->rport, RPSM_EVENT_FC4_OFFLINE);
		अवरोध;

	हाल BFA_FCS_ITNIM_SM_DELETE:
		bfa_sm_set_state(itnim, bfa_fcs_itnim_sm_offline);
		bfa_fcs_itnim_मुक्त(itnim);
		अवरोध;

	शेष:
		bfa_sm_fault(itnim->fcs, event);
	पूर्ण
पूर्ण

/*
 * This state is set when a discovered rport is also in पूर्णांकiator mode.
 * This ITN is marked as no_op and is not active and will not be truned पूर्णांकo
 * online state.
 */
अटल व्योम
bfa_fcs_itnim_sm_initiator(काष्ठा bfa_fcs_itnim_s *itnim,
		 क्रमागत bfa_fcs_itnim_event event)
अणु
	bfa_trc(itnim->fcs, itnim->rport->pwwn);
	bfa_trc(itnim->fcs, event);

	चयन (event) अणु
	हाल BFA_FCS_ITNIM_SM_OFFLINE:
		bfa_sm_set_state(itnim, bfa_fcs_itnim_sm_offline);
		bfa_sm_send_event(itnim->rport, RPSM_EVENT_FC4_OFFLINE);
		अवरोध;

	/*
	 * fcs_online is expected here क्रम well known initiator ports
	 */
	हाल BFA_FCS_ITNIM_SM_FCS_ONLINE:
		bfa_sm_send_event(itnim->rport, RPSM_EVENT_FC4_FCS_ONLINE);
		अवरोध;

	हाल BFA_FCS_ITNIM_SM_RSP_ERROR:
	हाल BFA_FCS_ITNIM_SM_INITIATOR:
		अवरोध;

	हाल BFA_FCS_ITNIM_SM_DELETE:
		bfa_sm_set_state(itnim, bfa_fcs_itnim_sm_offline);
		bfa_fcs_itnim_मुक्त(itnim);
		अवरोध;

	शेष:
		bfa_sm_fault(itnim->fcs, event);
	पूर्ण
पूर्ण

अटल व्योम
bfa_fcs_itnim_aen_post(काष्ठा bfa_fcs_itnim_s *itnim,
			क्रमागत bfa_itnim_aen_event event)
अणु
	काष्ठा bfa_fcs_rport_s *rport = itnim->rport;
	काष्ठा bfad_s *bfad = (काष्ठा bfad_s *)itnim->fcs->bfad;
	काष्ठा bfa_aen_entry_s	*aen_entry;

	/* Don't post events क्रम well known addresses */
	अगर (BFA_FCS_PID_IS_WKA(rport->pid))
		वापस;

	bfad_get_aen_entry(bfad, aen_entry);
	अगर (!aen_entry)
		वापस;

	aen_entry->aen_data.itnim.vf_id = rport->port->fabric->vf_id;
	aen_entry->aen_data.itnim.ppwwn = bfa_fcs_lport_get_pwwn(
					bfa_fcs_get_base_port(itnim->fcs));
	aen_entry->aen_data.itnim.lpwwn = bfa_fcs_lport_get_pwwn(rport->port);
	aen_entry->aen_data.itnim.rpwwn = rport->pwwn;

	/* Send the AEN notअगरication */
	bfad_im_post_venकरोr_event(aen_entry, bfad, ++rport->fcs->fcs_aen_seq,
				  BFA_AEN_CAT_ITNIM, event);
पूर्ण

अटल व्योम
bfa_fcs_itnim_send_prli(व्योम *itnim_cbarg, काष्ठा bfa_fcxp_s *fcxp_alloced)
अणु
	काष्ठा bfa_fcs_itnim_s *itnim = itnim_cbarg;
	काष्ठा bfa_fcs_rport_s *rport = itnim->rport;
	काष्ठा bfa_fcs_lport_s *port = rport->port;
	काष्ठा fchs_s	fchs;
	काष्ठा bfa_fcxp_s *fcxp;
	पूर्णांक		len;

	bfa_trc(itnim->fcs, itnim->rport->pwwn);

	fcxp = fcxp_alloced ? fcxp_alloced :
	       bfa_fcs_fcxp_alloc(port->fcs, BFA_TRUE);
	अगर (!fcxp) अणु
		itnim->stats.fcxp_alloc_रुको++;
		bfa_fcs_fcxp_alloc_रुको(port->fcs->bfa, &itnim->fcxp_wqe,
				bfa_fcs_itnim_send_prli, itnim, BFA_TRUE);
		वापस;
	पूर्ण
	itnim->fcxp = fcxp;

	len = fc_prli_build(&fchs, bfa_fcxp_get_reqbuf(fcxp),
			    itnim->rport->pid, bfa_fcs_lport_get_fcid(port), 0);

	bfa_fcxp_send(fcxp, rport->bfa_rport, port->fabric->vf_id, port->lp_tag,
		      BFA_FALSE, FC_CLASS_3, len, &fchs,
		      bfa_fcs_itnim_prli_response, (व्योम *)itnim,
		      FC_MAX_PDUSZ, FC_ELS_TOV);

	itnim->stats.prli_sent++;
	bfa_sm_send_event(itnim, BFA_FCS_ITNIM_SM_FRMSENT);
पूर्ण

अटल व्योम
bfa_fcs_itnim_prli_response(व्योम *fcsarg, काष्ठा bfa_fcxp_s *fcxp, व्योम *cbarg,
			    bfa_status_t req_status, u32 rsp_len,
			    u32 resid_len, काष्ठा fchs_s *rsp_fchs)
अणु
	काष्ठा bfa_fcs_itnim_s *itnim = (काष्ठा bfa_fcs_itnim_s *) cbarg;
	काष्ठा fc_els_cmd_s *els_cmd;
	काष्ठा fc_prli_s *prli_resp;
	काष्ठा fc_ls_rjt_s *ls_rjt;
	काष्ठा fc_prli_params_s *sparams;

	bfa_trc(itnim->fcs, req_status);

	/*
	 * Sanity Checks
	 */
	अगर (req_status != BFA_STATUS_OK) अणु
		itnim->stats.prli_rsp_err++;
		bfa_sm_send_event(itnim, BFA_FCS_ITNIM_SM_RSP_ERROR);
		वापस;
	पूर्ण

	els_cmd = (काष्ठा fc_els_cmd_s *) BFA_FCXP_RSP_PLD(fcxp);

	अगर (els_cmd->els_code == FC_ELS_ACC) अणु
		prli_resp = (काष्ठा fc_prli_s *) els_cmd;

		अगर (fc_prli_rsp_parse(prli_resp, rsp_len) != FC_PARSE_OK) अणु
			bfa_trc(itnim->fcs, rsp_len);
			/*
			 * Check अगर this  r-port is also in Initiator mode.
			 * If so, we need to set this ITN as a no-op.
			 */
			अगर (prli_resp->parampage.servparams.initiator) अणु
				bfa_trc(itnim->fcs, prli_resp->parampage.type);
				itnim->rport->scsi_function =
						BFA_RPORT_INITIATOR;
				itnim->stats.prli_rsp_acc++;
				itnim->stats.initiator++;
				bfa_sm_send_event(itnim,
						  BFA_FCS_ITNIM_SM_RSP_OK);
				वापस;
			पूर्ण

			itnim->stats.prli_rsp_parse_err++;
			वापस;
		पूर्ण
		itnim->rport->scsi_function = BFA_RPORT_TARGET;

		sparams = &prli_resp->parampage.servparams;
		itnim->seq_rec	     = sparams->retry;
		itnim->rec_support   = sparams->rec_support;
		itnim->task_retry_id = sparams->task_retry_id;
		itnim->conf_comp     = sparams->confirm;

		itnim->stats.prli_rsp_acc++;
		bfa_sm_send_event(itnim, BFA_FCS_ITNIM_SM_RSP_OK);
	पूर्ण अन्यथा अणु
		ls_rjt = (काष्ठा fc_ls_rjt_s *) BFA_FCXP_RSP_PLD(fcxp);

		bfa_trc(itnim->fcs, ls_rjt->reason_code);
		bfa_trc(itnim->fcs, ls_rjt->reason_code_expl);

		itnim->stats.prli_rsp_rjt++;
		अगर (ls_rjt->reason_code == FC_LS_RJT_RSN_CMD_NOT_SUPP) अणु
			bfa_sm_send_event(itnim, BFA_FCS_ITNIM_SM_RSP_NOT_SUPP);
			वापस;
		पूर्ण
		bfa_sm_send_event(itnim, BFA_FCS_ITNIM_SM_RSP_ERROR);
	पूर्ण
पूर्ण

अटल व्योम
bfa_fcs_itnim_समयout(व्योम *arg)
अणु
	काष्ठा bfa_fcs_itnim_s *itnim = (काष्ठा bfa_fcs_itnim_s *) arg;

	itnim->stats.समयout++;
	bfa_sm_send_event(itnim, BFA_FCS_ITNIM_SM_TIMEOUT);
पूर्ण

अटल व्योम
bfa_fcs_itnim_मुक्त(काष्ठा bfa_fcs_itnim_s *itnim)
अणु
	अगर (itnim->bfa_itnim) अणु
		bfa_itnim_delete(itnim->bfa_itnim);
		itnim->bfa_itnim = शून्य;
	पूर्ण

	bfa_fcb_itnim_मुक्त(itnim->fcs->bfad, itnim->itnim_drv);
पूर्ण



/*
 *  itnim_खुला FCS ITNIM खुला पूर्णांकerfaces
 */

/*
 *	Called by rport when a new rport is created.
 *
 * @param[in] rport	-  remote port.
 */
काष्ठा bfa_fcs_itnim_s *
bfa_fcs_itnim_create(काष्ठा bfa_fcs_rport_s *rport)
अणु
	काष्ठा bfa_fcs_lport_s *port = rport->port;
	काष्ठा bfa_fcs_itnim_s *itnim;
	काष्ठा bfad_itnim_s   *itnim_drv;
	पूर्णांक ret;

	/*
	 * call bfad to allocate the itnim
	 */
	ret = bfa_fcb_itnim_alloc(port->fcs->bfad, &itnim, &itnim_drv);
	अगर (ret) अणु
		bfa_trc(port->fcs, rport->pwwn);
		वापस शून्य;
	पूर्ण

	/*
	 * Initialize itnim
	 */
	itnim->rport = rport;
	itnim->fcs = rport->fcs;
	itnim->itnim_drv = itnim_drv;

	itnim->bfa_itnim     = शून्य;
	itnim->seq_rec	     = BFA_FALSE;
	itnim->rec_support   = BFA_FALSE;
	itnim->conf_comp     = BFA_FALSE;
	itnim->task_retry_id = BFA_FALSE;

	/*
	 * Set State machine
	 */
	bfa_sm_set_state(itnim, bfa_fcs_itnim_sm_offline);

	वापस itnim;
पूर्ण

/*
 *	Called by rport to delete  the instance of FCPIM.
 *
 * @param[in] rport	-  remote port.
 */
व्योम
bfa_fcs_itnim_delete(काष्ठा bfa_fcs_itnim_s *itnim)
अणु
	bfa_trc(itnim->fcs, itnim->rport->pid);
	bfa_sm_send_event(itnim, BFA_FCS_ITNIM_SM_DELETE);
पूर्ण

/*
 * Notअगरication from rport that PLOGI is complete to initiate FC-4 session.
 */
व्योम
bfa_fcs_itnim_brp_online(काष्ठा bfa_fcs_itnim_s *itnim)
अणु
	itnim->stats.onlines++;

	अगर (!BFA_FCS_PID_IS_WKA(itnim->rport->pid))
		bfa_sm_send_event(itnim, BFA_FCS_ITNIM_SM_HAL_ONLINE);
पूर्ण

/*
 * Called by rport to handle a remote device offline.
 */
व्योम
bfa_fcs_itnim_rport_offline(काष्ठा bfa_fcs_itnim_s *itnim)
अणु
	itnim->stats.offlines++;
	bfa_sm_send_event(itnim, BFA_FCS_ITNIM_SM_OFFLINE);
पूर्ण

/*
 * Called by rport when remote port is known to be an initiator from
 * PRLI received.
 */
व्योम
bfa_fcs_itnim_is_initiator(काष्ठा bfa_fcs_itnim_s *itnim)
अणु
	bfa_trc(itnim->fcs, itnim->rport->pid);
	itnim->stats.initiator++;
	bfa_sm_send_event(itnim, BFA_FCS_ITNIM_SM_INITIATOR);
पूर्ण

/*
 * Called by rport to check अगर the itnim is online.
 */
bfa_status_t
bfa_fcs_itnim_get_online_state(काष्ठा bfa_fcs_itnim_s *itnim)
अणु
	bfa_trc(itnim->fcs, itnim->rport->pid);
	चयन (bfa_sm_to_state(itnim_sm_table, itnim->sm)) अणु
	हाल BFA_ITNIM_ONLINE:
	हाल BFA_ITNIM_INITIATIOR:
		वापस BFA_STATUS_OK;

	शेष:
		वापस BFA_STATUS_NO_FCPIM_NEXUS;
	पूर्ण
पूर्ण

/*
 * BFA completion callback क्रम bfa_itnim_online().
 */
व्योम
bfa_cb_itnim_online(व्योम *cbarg)
अणु
	काष्ठा bfa_fcs_itnim_s *itnim = (काष्ठा bfa_fcs_itnim_s *) cbarg;

	bfa_trc(itnim->fcs, itnim->rport->pwwn);
	bfa_sm_send_event(itnim, BFA_FCS_ITNIM_SM_HCB_ONLINE);
पूर्ण

/*
 * BFA completion callback क्रम bfa_itnim_offline().
 */
व्योम
bfa_cb_itnim_offline(व्योम *cb_arg)
अणु
	काष्ठा bfa_fcs_itnim_s *itnim = (काष्ठा bfa_fcs_itnim_s *) cb_arg;

	bfa_trc(itnim->fcs, itnim->rport->pwwn);
	bfa_sm_send_event(itnim, BFA_FCS_ITNIM_SM_HCB_OFFLINE);
पूर्ण

/*
 * Mark the beginning of PATH TOV handling. IO completion callbacks
 * are still pending.
 */
व्योम
bfa_cb_itnim_tov_begin(व्योम *cb_arg)
अणु
	काष्ठा bfa_fcs_itnim_s *itnim = (काष्ठा bfa_fcs_itnim_s *) cb_arg;

	bfa_trc(itnim->fcs, itnim->rport->pwwn);
पूर्ण

/*
 * Mark the end of PATH TOV handling. All pending IOs are alपढ़ोy cleaned up.
 */
व्योम
bfa_cb_itnim_tov(व्योम *cb_arg)
अणु
	काष्ठा bfa_fcs_itnim_s *itnim = (काष्ठा bfa_fcs_itnim_s *) cb_arg;
	काष्ठा bfad_itnim_s *itnim_drv = itnim->itnim_drv;

	bfa_trc(itnim->fcs, itnim->rport->pwwn);
	itnim_drv->state = ITNIM_STATE_TIMEOUT;
पूर्ण

/*
 *		BFA notअगरication to FCS/driver क्रम second level error recovery.
 *
 * Atleast one I/O request has समयकरोut and target is unresponsive to
 * repeated पात requests. Second level error recovery should be initiated
 * by starting implicit logout and recovery procedures.
 */
व्योम
bfa_cb_itnim_sler(व्योम *cb_arg)
अणु
	काष्ठा bfa_fcs_itnim_s *itnim = (काष्ठा bfa_fcs_itnim_s *) cb_arg;

	itnim->stats.sler++;
	bfa_trc(itnim->fcs, itnim->rport->pwwn);
	bfa_sm_send_event(itnim->rport, RPSM_EVENT_LOGO_IMP);
पूर्ण

काष्ठा bfa_fcs_itnim_s *
bfa_fcs_itnim_lookup(काष्ठा bfa_fcs_lport_s *port, wwn_t rpwwn)
अणु
	काष्ठा bfa_fcs_rport_s *rport;
	rport = bfa_fcs_rport_lookup(port, rpwwn);

	अगर (!rport)
		वापस शून्य;

	WARN_ON(rport->itnim == शून्य);
	वापस rport->itnim;
पूर्ण

bfa_status_t
bfa_fcs_itnim_attr_get(काष्ठा bfa_fcs_lport_s *port, wwn_t rpwwn,
		       काष्ठा bfa_itnim_attr_s *attr)
अणु
	काष्ठा bfa_fcs_itnim_s *itnim = शून्य;

	itnim = bfa_fcs_itnim_lookup(port, rpwwn);

	अगर (itnim == शून्य)
		वापस BFA_STATUS_NO_FCPIM_NEXUS;

	attr->state	    = bfa_sm_to_state(itnim_sm_table, itnim->sm);
	attr->retry	    = itnim->seq_rec;
	attr->rec_support   = itnim->rec_support;
	attr->conf_comp	    = itnim->conf_comp;
	attr->task_retry_id = itnim->task_retry_id;
	वापस BFA_STATUS_OK;
पूर्ण

bfa_status_t
bfa_fcs_itnim_stats_get(काष्ठा bfa_fcs_lport_s *port, wwn_t rpwwn,
			काष्ठा bfa_itnim_stats_s *stats)
अणु
	काष्ठा bfa_fcs_itnim_s *itnim = शून्य;

	WARN_ON(port == शून्य);

	itnim = bfa_fcs_itnim_lookup(port, rpwwn);

	अगर (itnim == शून्य)
		वापस BFA_STATUS_NO_FCPIM_NEXUS;

	स_नकल(stats, &itnim->stats, माप(काष्ठा bfa_itnim_stats_s));

	वापस BFA_STATUS_OK;
पूर्ण

bfa_status_t
bfa_fcs_itnim_stats_clear(काष्ठा bfa_fcs_lport_s *port, wwn_t rpwwn)
अणु
	काष्ठा bfa_fcs_itnim_s *itnim = शून्य;

	WARN_ON(port == शून्य);

	itnim = bfa_fcs_itnim_lookup(port, rpwwn);

	अगर (itnim == शून्य)
		वापस BFA_STATUS_NO_FCPIM_NEXUS;

	स_रखो(&itnim->stats, 0, माप(काष्ठा bfa_itnim_stats_s));
	वापस BFA_STATUS_OK;
पूर्ण

व्योम
bfa_fcs_fcpim_uf_recv(काष्ठा bfa_fcs_itnim_s *itnim,
			काष्ठा fchs_s *fchs, u16 len)
अणु
	काष्ठा fc_els_cmd_s *els_cmd;

	bfa_trc(itnim->fcs, fchs->type);

	अगर (fchs->type != FC_TYPE_ELS)
		वापस;

	els_cmd = (काष्ठा fc_els_cmd_s *) (fchs + 1);

	bfa_trc(itnim->fcs, els_cmd->els_code);

	चयन (els_cmd->els_code) अणु
	हाल FC_ELS_PRLO:
		bfa_fcs_rport_prlo(itnim->rport, fchs->ox_id);
		अवरोध;

	शेष:
		WARN_ON(1);
	पूर्ण
पूर्ण
