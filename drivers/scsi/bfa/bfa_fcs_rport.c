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
 *  rport.c Remote port implementation.
 */

#समावेश "bfad_drv.h"
#समावेश "bfad_im.h"
#समावेश "bfa_fcs.h"
#समावेश "bfa_fcbuild.h"

BFA_TRC_खाता(FCS, RPORT);

अटल u32
bfa_fcs_rport_del_समयout = BFA_FCS_RPORT_DEF_DEL_TIMEOUT * 1000;
	 /* In millisecs */
/*
 * bfa_fcs_rport_max_logins is max count of bfa_fcs_rports
 * whereas DEF_CFG_NUM_RPORTS is max count of bfa_rports
 */
अटल u32 bfa_fcs_rport_max_logins = BFA_FCS_MAX_RPORT_LOGINS;

/*
 * क्रमward declarations
 */
अटल काष्ठा bfa_fcs_rport_s *bfa_fcs_rport_alloc(
		काष्ठा bfa_fcs_lport_s *port, wwn_t pwwn, u32 rpid);
अटल व्योम	bfa_fcs_rport_मुक्त(काष्ठा bfa_fcs_rport_s *rport);
अटल व्योम	bfa_fcs_rport_hal_online(काष्ठा bfa_fcs_rport_s *rport);
अटल व्योम	bfa_fcs_rport_fcs_online_action(काष्ठा bfa_fcs_rport_s *rport);
अटल व्योम	bfa_fcs_rport_hal_online_action(काष्ठा bfa_fcs_rport_s *rport);
अटल व्योम	bfa_fcs_rport_fcs_offline_action(काष्ठा bfa_fcs_rport_s *rport);
अटल व्योम	bfa_fcs_rport_hal_offline_action(काष्ठा bfa_fcs_rport_s *rport);
अटल व्योम	bfa_fcs_rport_update(काष्ठा bfa_fcs_rport_s *rport,
					काष्ठा fc_logi_s *plogi);
अटल व्योम	bfa_fcs_rport_समयout(व्योम *arg);
अटल व्योम	bfa_fcs_rport_send_plogi(व्योम *rport_cbarg,
					 काष्ठा bfa_fcxp_s *fcxp_alloced);
अटल व्योम	bfa_fcs_rport_send_plogiacc(व्योम *rport_cbarg,
					काष्ठा bfa_fcxp_s *fcxp_alloced);
अटल व्योम	bfa_fcs_rport_plogi_response(व्योम *fcsarg,
				काष्ठा bfa_fcxp_s *fcxp, व्योम *cbarg,
				bfa_status_t req_status, u32 rsp_len,
				u32 resid_len, काष्ठा fchs_s *rsp_fchs);
अटल व्योम	bfa_fcs_rport_send_adisc(व्योम *rport_cbarg,
					 काष्ठा bfa_fcxp_s *fcxp_alloced);
अटल व्योम	bfa_fcs_rport_adisc_response(व्योम *fcsarg,
				काष्ठा bfa_fcxp_s *fcxp, व्योम *cbarg,
				bfa_status_t req_status, u32 rsp_len,
				u32 resid_len, काष्ठा fchs_s *rsp_fchs);
अटल व्योम	bfa_fcs_rport_send_nsdisc(व्योम *rport_cbarg,
					 काष्ठा bfa_fcxp_s *fcxp_alloced);
अटल व्योम	bfa_fcs_rport_gidpn_response(व्योम *fcsarg,
				काष्ठा bfa_fcxp_s *fcxp, व्योम *cbarg,
				bfa_status_t req_status, u32 rsp_len,
				u32 resid_len, काष्ठा fchs_s *rsp_fchs);
अटल व्योम	bfa_fcs_rport_gpnid_response(व्योम *fcsarg,
				काष्ठा bfa_fcxp_s *fcxp, व्योम *cbarg,
				bfa_status_t req_status, u32 rsp_len,
				u32 resid_len, काष्ठा fchs_s *rsp_fchs);
अटल व्योम	bfa_fcs_rport_send_logo(व्योम *rport_cbarg,
					काष्ठा bfa_fcxp_s *fcxp_alloced);
अटल व्योम	bfa_fcs_rport_send_logo_acc(व्योम *rport_cbarg);
अटल व्योम	bfa_fcs_rport_process_prli(काष्ठा bfa_fcs_rport_s *rport,
					काष्ठा fchs_s *rx_fchs, u16 len);
अटल व्योम	bfa_fcs_rport_send_ls_rjt(काष्ठा bfa_fcs_rport_s *rport,
				काष्ठा fchs_s *rx_fchs, u8 reason_code,
					  u8 reason_code_expl);
अटल व्योम	bfa_fcs_rport_process_adisc(काष्ठा bfa_fcs_rport_s *rport,
				काष्ठा fchs_s *rx_fchs, u16 len);
अटल व्योम bfa_fcs_rport_send_prlo_acc(काष्ठा bfa_fcs_rport_s *rport);
अटल व्योम	bfa_fcs_rport_hal_offline(काष्ठा bfa_fcs_rport_s *rport);

अटल व्योम	bfa_fcs_rport_sm_uninit(काष्ठा bfa_fcs_rport_s *rport,
					क्रमागत rport_event event);
अटल व्योम	bfa_fcs_rport_sm_plogi_sending(काष्ठा bfa_fcs_rport_s *rport,
						क्रमागत rport_event event);
अटल व्योम	bfa_fcs_rport_sm_plogiacc_sending(काष्ठा bfa_fcs_rport_s *rport,
						  क्रमागत rport_event event);
अटल व्योम	bfa_fcs_rport_sm_plogi_retry(काष्ठा bfa_fcs_rport_s *rport,
						क्रमागत rport_event event);
अटल व्योम	bfa_fcs_rport_sm_plogi(काष्ठा bfa_fcs_rport_s *rport,
					क्रमागत rport_event event);
अटल व्योम	bfa_fcs_rport_sm_fc4_fcs_online(काष्ठा bfa_fcs_rport_s *rport,
					क्रमागत rport_event event);
अटल व्योम	bfa_fcs_rport_sm_hal_online(काष्ठा bfa_fcs_rport_s *rport,
						क्रमागत rport_event event);
अटल व्योम	bfa_fcs_rport_sm_online(काष्ठा bfa_fcs_rport_s *rport,
					क्रमागत rport_event event);
अटल व्योम	bfa_fcs_rport_sm_nsquery_sending(काष्ठा bfa_fcs_rport_s *rport,
						 क्रमागत rport_event event);
अटल व्योम	bfa_fcs_rport_sm_nsquery(काष्ठा bfa_fcs_rport_s *rport,
					 क्रमागत rport_event event);
अटल व्योम	bfa_fcs_rport_sm_adisc_online_sending(
			काष्ठा bfa_fcs_rport_s *rport, क्रमागत rport_event event);
अटल व्योम	bfa_fcs_rport_sm_adisc_online(काष्ठा bfa_fcs_rport_s *rport,
					क्रमागत rport_event event);
अटल व्योम	bfa_fcs_rport_sm_adisc_offline_sending(काष्ठा bfa_fcs_rport_s
					*rport, क्रमागत rport_event event);
अटल व्योम	bfa_fcs_rport_sm_adisc_offline(काष्ठा bfa_fcs_rport_s *rport,
					क्रमागत rport_event event);
अटल व्योम	bfa_fcs_rport_sm_fc4_logorcv(काष्ठा bfa_fcs_rport_s *rport,
						क्रमागत rport_event event);
अटल व्योम	bfa_fcs_rport_sm_fc4_logosend(काष्ठा bfa_fcs_rport_s *rport,
						क्रमागत rport_event event);
अटल व्योम	bfa_fcs_rport_sm_fc4_offline(काष्ठा bfa_fcs_rport_s *rport,
						क्रमागत rport_event event);
अटल व्योम	bfa_fcs_rport_sm_hcb_offline(काष्ठा bfa_fcs_rport_s *rport,
						क्रमागत rport_event event);
अटल व्योम	bfa_fcs_rport_sm_hcb_logorcv(काष्ठा bfa_fcs_rport_s *rport,
						क्रमागत rport_event event);
अटल व्योम	bfa_fcs_rport_sm_hcb_logosend(काष्ठा bfa_fcs_rport_s *rport,
						क्रमागत rport_event event);
अटल व्योम	bfa_fcs_rport_sm_logo_sending(काष्ठा bfa_fcs_rport_s *rport,
						क्रमागत rport_event event);
अटल व्योम	bfa_fcs_rport_sm_offline(काष्ठा bfa_fcs_rport_s *rport,
					 क्रमागत rport_event event);
अटल व्योम	bfa_fcs_rport_sm_nsdisc_sending(काष्ठा bfa_fcs_rport_s *rport,
						क्रमागत rport_event event);
अटल व्योम	bfa_fcs_rport_sm_nsdisc_retry(काष्ठा bfa_fcs_rport_s *rport,
						क्रमागत rport_event event);
अटल व्योम	bfa_fcs_rport_sm_nsdisc_sent(काष्ठा bfa_fcs_rport_s *rport,
						क्रमागत rport_event event);
अटल व्योम	bfa_fcs_rport_sm_nsdisc_sent(काष्ठा bfa_fcs_rport_s *rport,
						क्रमागत rport_event event);
अटल व्योम	bfa_fcs_rport_sm_fc4_off_delete(काष्ठा bfa_fcs_rport_s *rport,
						क्रमागत rport_event event);
अटल व्योम	bfa_fcs_rport_sm_delete_pending(काष्ठा bfa_fcs_rport_s *rport,
						क्रमागत rport_event event);

अटल काष्ठा bfa_sm_table_s rport_sm_table[] = अणु
	अणुBFA_SM(bfa_fcs_rport_sm_uninit), BFA_RPORT_UNINITपूर्ण,
	अणुBFA_SM(bfa_fcs_rport_sm_plogi_sending), BFA_RPORT_PLOGIपूर्ण,
	अणुBFA_SM(bfa_fcs_rport_sm_plogiacc_sending), BFA_RPORT_ONLINEपूर्ण,
	अणुBFA_SM(bfa_fcs_rport_sm_plogi_retry), BFA_RPORT_PLOGI_RETRYपूर्ण,
	अणुBFA_SM(bfa_fcs_rport_sm_plogi), BFA_RPORT_PLOGIपूर्ण,
	अणुBFA_SM(bfa_fcs_rport_sm_fc4_fcs_online), BFA_RPORT_ONLINEपूर्ण,
	अणुBFA_SM(bfa_fcs_rport_sm_hal_online), BFA_RPORT_ONLINEपूर्ण,
	अणुBFA_SM(bfa_fcs_rport_sm_online), BFA_RPORT_ONLINEपूर्ण,
	अणुBFA_SM(bfa_fcs_rport_sm_nsquery_sending), BFA_RPORT_NSQUERYपूर्ण,
	अणुBFA_SM(bfa_fcs_rport_sm_nsquery), BFA_RPORT_NSQUERYपूर्ण,
	अणुBFA_SM(bfa_fcs_rport_sm_adisc_online_sending), BFA_RPORT_ADISCपूर्ण,
	अणुBFA_SM(bfa_fcs_rport_sm_adisc_online), BFA_RPORT_ADISCपूर्ण,
	अणुBFA_SM(bfa_fcs_rport_sm_adisc_offline_sending), BFA_RPORT_ADISCपूर्ण,
	अणुBFA_SM(bfa_fcs_rport_sm_adisc_offline), BFA_RPORT_ADISCपूर्ण,
	अणुBFA_SM(bfa_fcs_rport_sm_fc4_logorcv), BFA_RPORT_LOGORCVपूर्ण,
	अणुBFA_SM(bfa_fcs_rport_sm_fc4_logosend), BFA_RPORT_LOGOपूर्ण,
	अणुBFA_SM(bfa_fcs_rport_sm_fc4_offline), BFA_RPORT_OFFLINEपूर्ण,
	अणुBFA_SM(bfa_fcs_rport_sm_hcb_offline), BFA_RPORT_OFFLINEपूर्ण,
	अणुBFA_SM(bfa_fcs_rport_sm_hcb_logorcv), BFA_RPORT_LOGORCVपूर्ण,
	अणुBFA_SM(bfa_fcs_rport_sm_hcb_logosend), BFA_RPORT_LOGOपूर्ण,
	अणुBFA_SM(bfa_fcs_rport_sm_logo_sending), BFA_RPORT_LOGOपूर्ण,
	अणुBFA_SM(bfa_fcs_rport_sm_offline), BFA_RPORT_OFFLINEपूर्ण,
	अणुBFA_SM(bfa_fcs_rport_sm_nsdisc_sending), BFA_RPORT_NSDISCपूर्ण,
	अणुBFA_SM(bfa_fcs_rport_sm_nsdisc_retry), BFA_RPORT_NSDISCपूर्ण,
	अणुBFA_SM(bfa_fcs_rport_sm_nsdisc_sent), BFA_RPORT_NSDISCपूर्ण,
पूर्ण;

/*
 *		Beginning state.
 */
अटल व्योम
bfa_fcs_rport_sm_uninit(काष्ठा bfa_fcs_rport_s *rport, क्रमागत rport_event event)
अणु
	bfa_trc(rport->fcs, rport->pwwn);
	bfa_trc(rport->fcs, rport->pid);
	bfa_trc(rport->fcs, event);

	चयन (event) अणु
	हाल RPSM_EVENT_PLOGI_SEND:
		bfa_sm_set_state(rport, bfa_fcs_rport_sm_plogi_sending);
		rport->plogi_retries = 0;
		bfa_fcs_rport_send_plogi(rport, शून्य);
		अवरोध;

	हाल RPSM_EVENT_PLOGI_RCVD:
		bfa_sm_set_state(rport, bfa_fcs_rport_sm_plogiacc_sending);
		bfa_fcs_rport_send_plogiacc(rport, शून्य);
		अवरोध;

	हाल RPSM_EVENT_PLOGI_COMP:
		bfa_sm_set_state(rport, bfa_fcs_rport_sm_hal_online);
		bfa_fcs_rport_hal_online(rport);
		अवरोध;

	हाल RPSM_EVENT_ADDRESS_CHANGE:
	हाल RPSM_EVENT_ADDRESS_DISC:
		bfa_sm_set_state(rport, bfa_fcs_rport_sm_nsdisc_sending);
		rport->ns_retries = 0;
		bfa_fcs_rport_send_nsdisc(rport, शून्य);
		अवरोध;
	शेष:
		bfa_sm_fault(rport->fcs, event);
	पूर्ण
पूर्ण

/*
 *		PLOGI is being sent.
 */
अटल व्योम
bfa_fcs_rport_sm_plogi_sending(काष्ठा bfa_fcs_rport_s *rport,
	 क्रमागत rport_event event)
अणु
	bfa_trc(rport->fcs, rport->pwwn);
	bfa_trc(rport->fcs, rport->pid);
	bfa_trc(rport->fcs, event);

	चयन (event) अणु
	हाल RPSM_EVENT_FCXP_SENT:
		bfa_sm_set_state(rport, bfa_fcs_rport_sm_plogi);
		अवरोध;

	हाल RPSM_EVENT_DELETE:
		bfa_sm_set_state(rport, bfa_fcs_rport_sm_uninit);
		bfa_fcxp_walloc_cancel(rport->fcs->bfa, &rport->fcxp_wqe);
		bfa_fcs_rport_मुक्त(rport);
		अवरोध;

	हाल RPSM_EVENT_PLOGI_RCVD:
		bfa_sm_set_state(rport, bfa_fcs_rport_sm_plogiacc_sending);
		bfa_fcxp_walloc_cancel(rport->fcs->bfa, &rport->fcxp_wqe);
		bfa_fcs_rport_send_plogiacc(rport, शून्य);
		अवरोध;

	हाल RPSM_EVENT_SCN_OFFLINE:
		bfa_sm_set_state(rport, bfa_fcs_rport_sm_offline);
		bfa_fcxp_walloc_cancel(rport->fcs->bfa, &rport->fcxp_wqe);
		bfa_समयr_start(rport->fcs->bfa, &rport->समयr,
				bfa_fcs_rport_समयout, rport,
				bfa_fcs_rport_del_समयout);
		अवरोध;
	हाल RPSM_EVENT_ADDRESS_CHANGE:
	हाल RPSM_EVENT_FAB_SCN:
		/* query the NS */
		bfa_fcxp_walloc_cancel(rport->fcs->bfa, &rport->fcxp_wqe);
		WARN_ON(!(bfa_fcport_get_topology(rport->port->fcs->bfa) !=
					BFA_PORT_TOPOLOGY_LOOP));
		bfa_sm_set_state(rport, bfa_fcs_rport_sm_nsdisc_sending);
		rport->ns_retries = 0;
		bfa_fcs_rport_send_nsdisc(rport, शून्य);
		अवरोध;

	हाल RPSM_EVENT_LOGO_IMP:
		rport->pid = 0;
		bfa_sm_set_state(rport, bfa_fcs_rport_sm_offline);
		bfa_fcxp_walloc_cancel(rport->fcs->bfa, &rport->fcxp_wqe);
		bfa_समयr_start(rport->fcs->bfa, &rport->समयr,
				bfa_fcs_rport_समयout, rport,
				bfa_fcs_rport_del_समयout);
		अवरोध;


	शेष:
		bfa_sm_fault(rport->fcs, event);
	पूर्ण
पूर्ण

/*
 *		PLOGI is being sent.
 */
अटल व्योम
bfa_fcs_rport_sm_plogiacc_sending(काष्ठा bfa_fcs_rport_s *rport,
	 क्रमागत rport_event event)
अणु
	bfa_trc(rport->fcs, rport->pwwn);
	bfa_trc(rport->fcs, rport->pid);
	bfa_trc(rport->fcs, event);

	चयन (event) अणु
	हाल RPSM_EVENT_FCXP_SENT:
		bfa_sm_set_state(rport, bfa_fcs_rport_sm_fc4_fcs_online);
		bfa_fcs_rport_fcs_online_action(rport);
		अवरोध;

	हाल RPSM_EVENT_DELETE:
		bfa_sm_set_state(rport, bfa_fcs_rport_sm_uninit);
		bfa_fcxp_walloc_cancel(rport->fcs->bfa, &rport->fcxp_wqe);
		bfa_fcs_rport_मुक्त(rport);
		अवरोध;

	हाल RPSM_EVENT_PLOGI_RCVD:
	हाल RPSM_EVENT_PLOGI_COMP:
	हाल RPSM_EVENT_FAB_SCN:
		/*
		 * Ignore, SCN is possibly online notअगरication.
		 */
		अवरोध;

	हाल RPSM_EVENT_SCN_OFFLINE:
		bfa_sm_set_state(rport, bfa_fcs_rport_sm_offline);
		bfa_fcxp_walloc_cancel(rport->fcs->bfa, &rport->fcxp_wqe);
		bfa_समयr_start(rport->fcs->bfa, &rport->समयr,
				bfa_fcs_rport_समयout, rport,
				bfa_fcs_rport_del_समयout);
		अवरोध;

	हाल RPSM_EVENT_ADDRESS_CHANGE:
		bfa_fcxp_walloc_cancel(rport->fcs->bfa, &rport->fcxp_wqe);
		bfa_sm_set_state(rport, bfa_fcs_rport_sm_nsdisc_sending);
		rport->ns_retries = 0;
		bfa_fcs_rport_send_nsdisc(rport, शून्य);
		अवरोध;

	हाल RPSM_EVENT_LOGO_IMP:
		rport->pid = 0;
		bfa_sm_set_state(rport, bfa_fcs_rport_sm_offline);
		bfa_fcxp_walloc_cancel(rport->fcs->bfa, &rport->fcxp_wqe);
		bfa_समयr_start(rport->fcs->bfa, &rport->समयr,
				bfa_fcs_rport_समयout, rport,
				bfa_fcs_rport_del_समयout);
		अवरोध;

	हाल RPSM_EVENT_HCB_OFFLINE:
		/*
		 * Ignore BFA callback, on a PLOGI receive we call bfa offline.
		 */
		अवरोध;

	शेष:
		bfa_sm_fault(rport->fcs, event);
	पूर्ण
पूर्ण

/*
 *		PLOGI is sent.
 */
अटल व्योम
bfa_fcs_rport_sm_plogi_retry(काष्ठा bfa_fcs_rport_s *rport,
			क्रमागत rport_event event)
अणु
	bfa_trc(rport->fcs, rport->pwwn);
	bfa_trc(rport->fcs, rport->pid);
	bfa_trc(rport->fcs, event);

	चयन (event) अणु
	हाल RPSM_EVENT_TIMEOUT:
		bfa_sm_set_state(rport, bfa_fcs_rport_sm_plogi_sending);
		bfa_fcs_rport_send_plogi(rport, शून्य);
		अवरोध;

	हाल RPSM_EVENT_DELETE:
		bfa_sm_set_state(rport, bfa_fcs_rport_sm_uninit);
		bfa_समयr_stop(&rport->समयr);
		bfa_fcs_rport_मुक्त(rport);
		अवरोध;

	हाल RPSM_EVENT_PRLO_RCVD:
	हाल RPSM_EVENT_LOGO_RCVD:
		अवरोध;

	हाल RPSM_EVENT_PLOGI_RCVD:
		bfa_sm_set_state(rport, bfa_fcs_rport_sm_plogiacc_sending);
		bfa_समयr_stop(&rport->समयr);
		bfa_fcs_rport_send_plogiacc(rport, शून्य);
		अवरोध;

	हाल RPSM_EVENT_SCN_OFFLINE:
		bfa_sm_set_state(rport, bfa_fcs_rport_sm_offline);
		bfa_समयr_stop(&rport->समयr);
		bfa_समयr_start(rport->fcs->bfa, &rport->समयr,
				bfa_fcs_rport_समयout, rport,
				bfa_fcs_rport_del_समयout);
		अवरोध;

	हाल RPSM_EVENT_ADDRESS_CHANGE:
	हाल RPSM_EVENT_FAB_SCN:
		bfa_समयr_stop(&rport->समयr);
		WARN_ON(!(bfa_fcport_get_topology(rport->port->fcs->bfa) !=
					BFA_PORT_TOPOLOGY_LOOP));
		bfa_sm_set_state(rport, bfa_fcs_rport_sm_nsdisc_sending);
		rport->ns_retries = 0;
		bfa_fcs_rport_send_nsdisc(rport, शून्य);
		अवरोध;

	हाल RPSM_EVENT_LOGO_IMP:
		rport->pid = 0;
		bfa_sm_set_state(rport, bfa_fcs_rport_sm_offline);
		bfa_समयr_stop(&rport->समयr);
		bfa_समयr_start(rport->fcs->bfa, &rport->समयr,
				bfa_fcs_rport_समयout, rport,
				bfa_fcs_rport_del_समयout);
		अवरोध;

	हाल RPSM_EVENT_PLOGI_COMP:
		bfa_sm_set_state(rport, bfa_fcs_rport_sm_fc4_fcs_online);
		bfa_समयr_stop(&rport->समयr);
		bfa_fcs_rport_fcs_online_action(rport);
		अवरोध;

	शेष:
		bfa_sm_fault(rport->fcs, event);
	पूर्ण
पूर्ण

/*
 *		PLOGI is sent.
 */
अटल व्योम
bfa_fcs_rport_sm_plogi(काष्ठा bfa_fcs_rport_s *rport, क्रमागत rport_event event)
अणु
	bfa_trc(rport->fcs, rport->pwwn);
	bfa_trc(rport->fcs, rport->pid);
	bfa_trc(rport->fcs, event);

	चयन (event) अणु
	हाल RPSM_EVENT_ACCEPTED:
		bfa_sm_set_state(rport, bfa_fcs_rport_sm_fc4_fcs_online);
		rport->plogi_retries = 0;
		bfa_fcs_rport_fcs_online_action(rport);
		अवरोध;

	हाल RPSM_EVENT_LOGO_RCVD:
		bfa_fcs_rport_send_logo_acc(rport);
		fallthrough;
	हाल RPSM_EVENT_PRLO_RCVD:
		अगर (rport->prlo == BFA_TRUE)
			bfa_fcs_rport_send_prlo_acc(rport);

		bfa_fcxp_discard(rport->fcxp);
		fallthrough;
	हाल RPSM_EVENT_FAILED:
		अगर (rport->plogi_retries < BFA_FCS_RPORT_MAX_RETRIES) अणु
			rport->plogi_retries++;
			bfa_sm_set_state(rport, bfa_fcs_rport_sm_plogi_retry);
			bfa_समयr_start(rport->fcs->bfa, &rport->समयr,
					bfa_fcs_rport_समयout, rport,
					BFA_FCS_RETRY_TIMEOUT);
		पूर्ण अन्यथा अणु
			bfa_stats(rport->port, rport_del_max_plogi_retry);
			rport->old_pid = rport->pid;
			rport->pid = 0;
			bfa_sm_set_state(rport, bfa_fcs_rport_sm_offline);
			bfa_समयr_start(rport->fcs->bfa, &rport->समयr,
					bfa_fcs_rport_समयout, rport,
					bfa_fcs_rport_del_समयout);
		पूर्ण
		अवरोध;

	हाल RPSM_EVENT_SCN_ONLINE:
		अवरोध;

	हाल RPSM_EVENT_SCN_OFFLINE:
		bfa_sm_set_state(rport, bfa_fcs_rport_sm_offline);
		bfa_fcxp_discard(rport->fcxp);
		bfa_समयr_start(rport->fcs->bfa, &rport->समयr,
				bfa_fcs_rport_समयout, rport,
				bfa_fcs_rport_del_समयout);
		अवरोध;

	हाल RPSM_EVENT_PLOGI_RETRY:
		rport->plogi_retries = 0;
		bfa_sm_set_state(rport, bfa_fcs_rport_sm_plogi_retry);
		bfa_समयr_start(rport->fcs->bfa, &rport->समयr,
				bfa_fcs_rport_समयout, rport,
				(FC_RA_TOV * 1000));
		अवरोध;

	हाल RPSM_EVENT_LOGO_IMP:
		rport->pid = 0;
		bfa_sm_set_state(rport, bfa_fcs_rport_sm_offline);
		bfa_fcxp_discard(rport->fcxp);
		bfa_समयr_start(rport->fcs->bfa, &rport->समयr,
				bfa_fcs_rport_समयout, rport,
				bfa_fcs_rport_del_समयout);
		अवरोध;

	हाल RPSM_EVENT_ADDRESS_CHANGE:
	हाल RPSM_EVENT_FAB_SCN:
		bfa_fcxp_discard(rport->fcxp);
		WARN_ON(!(bfa_fcport_get_topology(rport->port->fcs->bfa) !=
					BFA_PORT_TOPOLOGY_LOOP));
		bfa_sm_set_state(rport, bfa_fcs_rport_sm_nsdisc_sending);
		rport->ns_retries = 0;
		bfa_fcs_rport_send_nsdisc(rport, शून्य);
		अवरोध;

	हाल RPSM_EVENT_PLOGI_RCVD:
		bfa_sm_set_state(rport, bfa_fcs_rport_sm_plogiacc_sending);
		bfa_fcxp_discard(rport->fcxp);
		bfa_fcs_rport_send_plogiacc(rport, शून्य);
		अवरोध;

	हाल RPSM_EVENT_DELETE:
		bfa_sm_set_state(rport, bfa_fcs_rport_sm_uninit);
		bfa_fcxp_discard(rport->fcxp);
		bfa_fcs_rport_मुक्त(rport);
		अवरोध;

	हाल RPSM_EVENT_PLOGI_COMP:
		bfa_sm_set_state(rport, bfa_fcs_rport_sm_fc4_fcs_online);
		bfa_fcxp_discard(rport->fcxp);
		bfa_fcs_rport_fcs_online_action(rport);
		अवरोध;

	शेष:
		bfa_sm_fault(rport->fcs, event);
	पूर्ण
पूर्ण

/*
 * PLOGI is करोne. Aरुको bfa_fcs_itnim to ascertain the scsi function
 */
अटल व्योम
bfa_fcs_rport_sm_fc4_fcs_online(काष्ठा bfa_fcs_rport_s *rport,
				क्रमागत rport_event event)
अणु
	bfa_trc(rport->fcs, rport->pwwn);
	bfa_trc(rport->fcs, rport->pid);
	bfa_trc(rport->fcs, event);

	चयन (event) अणु
	हाल RPSM_EVENT_FC4_FCS_ONLINE:
		अगर (rport->scsi_function == BFA_RPORT_INITIATOR) अणु
			अगर (!BFA_FCS_PID_IS_WKA(rport->pid))
				bfa_fcs_rpf_rport_online(rport);
			bfa_sm_set_state(rport, bfa_fcs_rport_sm_online);
			अवरोध;
		पूर्ण

		अगर (!rport->bfa_rport)
			rport->bfa_rport =
				bfa_rport_create(rport->fcs->bfa, rport);

		अगर (rport->bfa_rport) अणु
			bfa_sm_set_state(rport, bfa_fcs_rport_sm_hal_online);
			bfa_fcs_rport_hal_online(rport);
		पूर्ण अन्यथा अणु
			bfa_sm_set_state(rport, bfa_fcs_rport_sm_fc4_logosend);
			bfa_fcs_rport_fcs_offline_action(rport);
		पूर्ण
		अवरोध;

	हाल RPSM_EVENT_PLOGI_RCVD:
		bfa_sm_set_state(rport, bfa_fcs_rport_sm_fc4_offline);
		rport->plogi_pending = BFA_TRUE;
		bfa_fcs_rport_fcs_offline_action(rport);
		अवरोध;

	हाल RPSM_EVENT_PLOGI_COMP:
	हाल RPSM_EVENT_LOGO_IMP:
	हाल RPSM_EVENT_ADDRESS_CHANGE:
	हाल RPSM_EVENT_FAB_SCN:
	हाल RPSM_EVENT_SCN_OFFLINE:
		bfa_sm_set_state(rport, bfa_fcs_rport_sm_fc4_offline);
		bfa_fcs_rport_fcs_offline_action(rport);
		अवरोध;

	हाल RPSM_EVENT_LOGO_RCVD:
	हाल RPSM_EVENT_PRLO_RCVD:
		bfa_sm_set_state(rport, bfa_fcs_rport_sm_fc4_logorcv);
		bfa_fcs_rport_fcs_offline_action(rport);
		अवरोध;

	हाल RPSM_EVENT_DELETE:
		bfa_sm_set_state(rport, bfa_fcs_rport_sm_fc4_logosend);
		bfa_fcs_rport_fcs_offline_action(rport);
		अवरोध;

	शेष:
		bfa_sm_fault(rport->fcs, event);
		अवरोध;
	पूर्ण
पूर्ण

/*
 *		PLOGI is complete. Aरुकोing BFA rport online callback. FC-4s
 *		are offline.
 */
अटल व्योम
bfa_fcs_rport_sm_hal_online(काष्ठा bfa_fcs_rport_s *rport,
			क्रमागत rport_event event)
अणु
	bfa_trc(rport->fcs, rport->pwwn);
	bfa_trc(rport->fcs, rport->pid);
	bfa_trc(rport->fcs, event);

	चयन (event) अणु
	हाल RPSM_EVENT_HCB_ONLINE:
		bfa_sm_set_state(rport, bfa_fcs_rport_sm_online);
		bfa_fcs_rport_hal_online_action(rport);
		अवरोध;

	हाल RPSM_EVENT_PLOGI_COMP:
		अवरोध;

	हाल RPSM_EVENT_PRLO_RCVD:
	हाल RPSM_EVENT_LOGO_RCVD:
		bfa_sm_set_state(rport, bfa_fcs_rport_sm_fc4_logorcv);
		bfa_fcs_rport_fcs_offline_action(rport);
		अवरोध;

	हाल RPSM_EVENT_FAB_SCN:
	हाल RPSM_EVENT_LOGO_IMP:
	हाल RPSM_EVENT_ADDRESS_CHANGE:
	हाल RPSM_EVENT_SCN_OFFLINE:
		bfa_sm_set_state(rport, bfa_fcs_rport_sm_fc4_offline);
		bfa_fcs_rport_fcs_offline_action(rport);
		अवरोध;

	हाल RPSM_EVENT_PLOGI_RCVD:
		rport->plogi_pending = BFA_TRUE;
		bfa_sm_set_state(rport, bfa_fcs_rport_sm_fc4_offline);
		bfa_fcs_rport_fcs_offline_action(rport);
		अवरोध;

	हाल RPSM_EVENT_DELETE:
		bfa_sm_set_state(rport, bfa_fcs_rport_sm_fc4_logosend);
		bfa_fcs_rport_fcs_offline_action(rport);
		अवरोध;

	शेष:
		bfa_sm_fault(rport->fcs, event);
	पूर्ण
पूर्ण

/*
 *		Rport is ONLINE. FC-4s active.
 */
अटल व्योम
bfa_fcs_rport_sm_online(काष्ठा bfa_fcs_rport_s *rport, क्रमागत rport_event event)
अणु
	bfa_trc(rport->fcs, rport->pwwn);
	bfa_trc(rport->fcs, rport->pid);
	bfa_trc(rport->fcs, event);

	चयन (event) अणु
	हाल RPSM_EVENT_FAB_SCN:
		अगर (bfa_fcs_fabric_is_चयनed(rport->port->fabric)) अणु
			bfa_sm_set_state(rport,
					 bfa_fcs_rport_sm_nsquery_sending);
			rport->ns_retries = 0;
			bfa_fcs_rport_send_nsdisc(rport, शून्य);
		पूर्ण अन्यथा अणु
			bfa_sm_set_state(rport,
				bfa_fcs_rport_sm_adisc_online_sending);
			bfa_fcs_rport_send_adisc(rport, शून्य);
		पूर्ण
		अवरोध;

	हाल RPSM_EVENT_PLOGI_RCVD:
	हाल RPSM_EVENT_LOGO_IMP:
	हाल RPSM_EVENT_ADDRESS_CHANGE:
	हाल RPSM_EVENT_SCN_OFFLINE:
		bfa_sm_set_state(rport, bfa_fcs_rport_sm_fc4_offline);
		bfa_fcs_rport_hal_offline_action(rport);
		अवरोध;

	हाल RPSM_EVENT_DELETE:
		bfa_sm_set_state(rport, bfa_fcs_rport_sm_fc4_logosend);
		bfa_fcs_rport_hal_offline_action(rport);
		अवरोध;

	हाल RPSM_EVENT_LOGO_RCVD:
	हाल RPSM_EVENT_PRLO_RCVD:
		bfa_sm_set_state(rport, bfa_fcs_rport_sm_fc4_logorcv);
		bfa_fcs_rport_hal_offline_action(rport);
		अवरोध;

	हाल RPSM_EVENT_SCN_ONLINE:
	हाल RPSM_EVENT_PLOGI_COMP:
		अवरोध;

	शेष:
		bfa_sm_fault(rport->fcs, event);
	पूर्ण
पूर्ण

/*
 *		An SCN event is received in ONLINE state. NS query is being sent
 *		prior to ADISC authentication with rport. FC-4s are छोड़ोd.
 */
अटल व्योम
bfa_fcs_rport_sm_nsquery_sending(काष्ठा bfa_fcs_rport_s *rport,
	 क्रमागत rport_event event)
अणु
	bfa_trc(rport->fcs, rport->pwwn);
	bfa_trc(rport->fcs, rport->pid);
	bfa_trc(rport->fcs, event);

	चयन (event) अणु
	हाल RPSM_EVENT_FCXP_SENT:
		bfa_sm_set_state(rport, bfa_fcs_rport_sm_nsquery);
		अवरोध;

	हाल RPSM_EVENT_DELETE:
		bfa_sm_set_state(rport, bfa_fcs_rport_sm_fc4_logosend);
		bfa_fcxp_walloc_cancel(rport->fcs->bfa, &rport->fcxp_wqe);
		bfa_fcs_rport_hal_offline_action(rport);
		अवरोध;

	हाल RPSM_EVENT_FAB_SCN:
		/*
		 * ignore SCN, रुको क्रम response to query itself
		 */
		अवरोध;

	हाल RPSM_EVENT_LOGO_RCVD:
	हाल RPSM_EVENT_PRLO_RCVD:
		bfa_sm_set_state(rport, bfa_fcs_rport_sm_fc4_logorcv);
		bfa_fcxp_walloc_cancel(rport->fcs->bfa, &rport->fcxp_wqe);
		bfa_fcs_rport_hal_offline_action(rport);
		अवरोध;

	हाल RPSM_EVENT_LOGO_IMP:
	हाल RPSM_EVENT_PLOGI_RCVD:
	हाल RPSM_EVENT_ADDRESS_CHANGE:
	हाल RPSM_EVENT_PLOGI_COMP:
		bfa_sm_set_state(rport, bfa_fcs_rport_sm_fc4_offline);
		bfa_fcxp_walloc_cancel(rport->fcs->bfa, &rport->fcxp_wqe);
		bfa_fcs_rport_hal_offline_action(rport);
		अवरोध;

	शेष:
		bfa_sm_fault(rport->fcs, event);
	पूर्ण
पूर्ण

/*
 *	An SCN event is received in ONLINE state. NS query is sent to rport.
 *	FC-4s are छोड़ोd.
 */
अटल व्योम
bfa_fcs_rport_sm_nsquery(काष्ठा bfa_fcs_rport_s *rport, क्रमागत rport_event event)
अणु
	bfa_trc(rport->fcs, rport->pwwn);
	bfa_trc(rport->fcs, rport->pid);
	bfa_trc(rport->fcs, event);

	चयन (event) अणु
	हाल RPSM_EVENT_ACCEPTED:
		bfa_sm_set_state(rport, bfa_fcs_rport_sm_adisc_online_sending);
		bfa_fcs_rport_send_adisc(rport, शून्य);
		अवरोध;

	हाल RPSM_EVENT_FAILED:
		rport->ns_retries++;
		अगर (rport->ns_retries < BFA_FCS_RPORT_MAX_RETRIES) अणु
			bfa_sm_set_state(rport,
					 bfa_fcs_rport_sm_nsquery_sending);
			bfa_fcs_rport_send_nsdisc(rport, शून्य);
		पूर्ण अन्यथा अणु
			bfa_sm_set_state(rport, bfa_fcs_rport_sm_fc4_offline);
			bfa_fcs_rport_hal_offline_action(rport);
		पूर्ण
		अवरोध;

	हाल RPSM_EVENT_DELETE:
		bfa_sm_set_state(rport, bfa_fcs_rport_sm_fc4_logosend);
		bfa_fcxp_discard(rport->fcxp);
		bfa_fcs_rport_hal_offline_action(rport);
		अवरोध;

	हाल RPSM_EVENT_FAB_SCN:
		अवरोध;

	हाल RPSM_EVENT_LOGO_RCVD:
	हाल RPSM_EVENT_PRLO_RCVD:
		bfa_sm_set_state(rport, bfa_fcs_rport_sm_fc4_logorcv);
		bfa_fcxp_discard(rport->fcxp);
		bfa_fcs_rport_hal_offline_action(rport);
		अवरोध;

	हाल RPSM_EVENT_PLOGI_COMP:
	हाल RPSM_EVENT_ADDRESS_CHANGE:
	हाल RPSM_EVENT_PLOGI_RCVD:
	हाल RPSM_EVENT_LOGO_IMP:
		bfa_sm_set_state(rport, bfa_fcs_rport_sm_fc4_offline);
		bfa_fcxp_discard(rport->fcxp);
		bfa_fcs_rport_hal_offline_action(rport);
		अवरोध;

	शेष:
		bfa_sm_fault(rport->fcs, event);
	पूर्ण
पूर्ण

/*
 *	An SCN event is received in ONLINE state. ADISC is being sent क्रम
 *	authenticating with rport. FC-4s are छोड़ोd.
 */
अटल व्योम
bfa_fcs_rport_sm_adisc_online_sending(काष्ठा bfa_fcs_rport_s *rport,
	 क्रमागत rport_event event)
अणु
	bfa_trc(rport->fcs, rport->pwwn);
	bfa_trc(rport->fcs, rport->pid);
	bfa_trc(rport->fcs, event);

	चयन (event) अणु
	हाल RPSM_EVENT_FCXP_SENT:
		bfa_sm_set_state(rport, bfa_fcs_rport_sm_adisc_online);
		अवरोध;

	हाल RPSM_EVENT_DELETE:
		bfa_sm_set_state(rport, bfa_fcs_rport_sm_fc4_logosend);
		bfa_fcxp_walloc_cancel(rport->fcs->bfa, &rport->fcxp_wqe);
		bfa_fcs_rport_hal_offline_action(rport);
		अवरोध;

	हाल RPSM_EVENT_LOGO_IMP:
	हाल RPSM_EVENT_ADDRESS_CHANGE:
		bfa_sm_set_state(rport, bfa_fcs_rport_sm_fc4_offline);
		bfa_fcxp_walloc_cancel(rport->fcs->bfa, &rport->fcxp_wqe);
		bfa_fcs_rport_hal_offline_action(rport);
		अवरोध;

	हाल RPSM_EVENT_LOGO_RCVD:
	हाल RPSM_EVENT_PRLO_RCVD:
		bfa_sm_set_state(rport, bfa_fcs_rport_sm_fc4_logorcv);
		bfa_fcxp_walloc_cancel(rport->fcs->bfa, &rport->fcxp_wqe);
		bfa_fcs_rport_hal_offline_action(rport);
		अवरोध;

	हाल RPSM_EVENT_FAB_SCN:
		अवरोध;

	हाल RPSM_EVENT_PLOGI_RCVD:
		bfa_sm_set_state(rport, bfa_fcs_rport_sm_fc4_offline);
		bfa_fcxp_walloc_cancel(rport->fcs->bfa, &rport->fcxp_wqe);
		bfa_fcs_rport_hal_offline_action(rport);
		अवरोध;

	शेष:
		bfa_sm_fault(rport->fcs, event);
	पूर्ण
पूर्ण

/*
 *		An SCN event is received in ONLINE state. ADISC is to rport.
 *		FC-4s are छोड़ोd.
 */
अटल व्योम
bfa_fcs_rport_sm_adisc_online(काष्ठा bfa_fcs_rport_s *rport,
				क्रमागत rport_event event)
अणु
	bfa_trc(rport->fcs, rport->pwwn);
	bfa_trc(rport->fcs, rport->pid);
	bfa_trc(rport->fcs, event);

	चयन (event) अणु
	हाल RPSM_EVENT_ACCEPTED:
		bfa_sm_set_state(rport, bfa_fcs_rport_sm_online);
		अवरोध;

	हाल RPSM_EVENT_PLOGI_RCVD:
		/*
		 * Too complex to cleanup FC-4 & rport and then acc to PLOGI.
		 * At least go offline when a PLOGI is received.
		 */
		bfa_fcxp_discard(rport->fcxp);
		fallthrough;

	हाल RPSM_EVENT_FAILED:
	हाल RPSM_EVENT_ADDRESS_CHANGE:
		bfa_sm_set_state(rport, bfa_fcs_rport_sm_fc4_offline);
		bfa_fcs_rport_hal_offline_action(rport);
		अवरोध;

	हाल RPSM_EVENT_DELETE:
		bfa_sm_set_state(rport, bfa_fcs_rport_sm_fc4_logosend);
		bfa_fcxp_discard(rport->fcxp);
		bfa_fcs_rport_hal_offline_action(rport);
		अवरोध;

	हाल RPSM_EVENT_FAB_SCN:
		/*
		 * alपढ़ोy processing RSCN
		 */
		अवरोध;

	हाल RPSM_EVENT_LOGO_IMP:
		bfa_sm_set_state(rport, bfa_fcs_rport_sm_fc4_offline);
		bfa_fcxp_discard(rport->fcxp);
		bfa_fcs_rport_hal_offline_action(rport);
		अवरोध;

	हाल RPSM_EVENT_LOGO_RCVD:
	हाल RPSM_EVENT_PRLO_RCVD:
		bfa_sm_set_state(rport, bfa_fcs_rport_sm_fc4_logorcv);
		bfa_fcxp_discard(rport->fcxp);
		bfa_fcs_rport_hal_offline_action(rport);
		अवरोध;

	शेष:
		bfa_sm_fault(rport->fcs, event);
	पूर्ण
पूर्ण

/*
 * ADISC is being sent क्रम authenticating with rport
 * Alपढ़ोy did offline actions.
 */
अटल व्योम
bfa_fcs_rport_sm_adisc_offline_sending(काष्ठा bfa_fcs_rport_s *rport,
	क्रमागत rport_event event)
अणु
	bfa_trc(rport->fcs, rport->pwwn);
	bfa_trc(rport->fcs, rport->pid);
	bfa_trc(rport->fcs, event);

	चयन (event) अणु
	हाल RPSM_EVENT_FCXP_SENT:
		bfa_sm_set_state(rport, bfa_fcs_rport_sm_adisc_offline);
		अवरोध;

	हाल RPSM_EVENT_DELETE:
	हाल RPSM_EVENT_SCN_OFFLINE:
	हाल RPSM_EVENT_LOGO_IMP:
	हाल RPSM_EVENT_LOGO_RCVD:
	हाल RPSM_EVENT_PRLO_RCVD:
		bfa_sm_set_state(rport, bfa_fcs_rport_sm_offline);
		bfa_fcxp_walloc_cancel(rport->fcs->bfa,
			&rport->fcxp_wqe);
		bfa_समयr_start(rport->fcs->bfa, &rport->समयr,
			bfa_fcs_rport_समयout, rport,
			bfa_fcs_rport_del_समयout);
		अवरोध;

	हाल RPSM_EVENT_PLOGI_RCVD:
		bfa_sm_set_state(rport, bfa_fcs_rport_sm_plogiacc_sending);
		bfa_fcxp_walloc_cancel(rport->fcs->bfa, &rport->fcxp_wqe);
		bfa_fcs_rport_send_plogiacc(rport, शून्य);
		अवरोध;

	शेष:
		bfa_sm_fault(rport->fcs, event);
	पूर्ण
पूर्ण

/*
 * ADISC to rport
 * Alपढ़ोy did offline actions
 */
अटल व्योम
bfa_fcs_rport_sm_adisc_offline(काष्ठा bfa_fcs_rport_s *rport,
			क्रमागत rport_event event)
अणु
	bfa_trc(rport->fcs, rport->pwwn);
	bfa_trc(rport->fcs, rport->pid);
	bfa_trc(rport->fcs, event);

	चयन (event) अणु
	हाल RPSM_EVENT_ACCEPTED:
		bfa_sm_set_state(rport, bfa_fcs_rport_sm_hal_online);
		bfa_fcs_rport_hal_online(rport);
		अवरोध;

	हाल RPSM_EVENT_PLOGI_RCVD:
		bfa_sm_set_state(rport, bfa_fcs_rport_sm_plogiacc_sending);
		bfa_fcxp_discard(rport->fcxp);
		bfa_fcs_rport_send_plogiacc(rport, शून्य);
		अवरोध;

	हाल RPSM_EVENT_FAILED:
		bfa_sm_set_state(rport, bfa_fcs_rport_sm_offline);
		bfa_समयr_start(rport->fcs->bfa, &rport->समयr,
			bfa_fcs_rport_समयout, rport,
			bfa_fcs_rport_del_समयout);
		अवरोध;

	हाल RPSM_EVENT_DELETE:
	हाल RPSM_EVENT_SCN_OFFLINE:
	हाल RPSM_EVENT_LOGO_IMP:
	हाल RPSM_EVENT_LOGO_RCVD:
	हाल RPSM_EVENT_PRLO_RCVD:
		bfa_sm_set_state(rport, bfa_fcs_rport_sm_offline);
		bfa_fcxp_discard(rport->fcxp);
		bfa_समयr_start(rport->fcs->bfa, &rport->समयr,
			bfa_fcs_rport_समयout, rport,
			bfa_fcs_rport_del_समयout);
		अवरोध;

	शेष:
		bfa_sm_fault(rport->fcs, event);
	पूर्ण
पूर्ण

/*
 * Rport has sent LOGO. Aरुकोing FC-4 offline completion callback.
 */
अटल व्योम
bfa_fcs_rport_sm_fc4_logorcv(काष्ठा bfa_fcs_rport_s *rport,
			क्रमागत rport_event event)
अणु
	bfa_trc(rport->fcs, rport->pwwn);
	bfa_trc(rport->fcs, rport->pid);
	bfa_trc(rport->fcs, event);

	चयन (event) अणु
	हाल RPSM_EVENT_FC4_OFFLINE:
		bfa_sm_set_state(rport, bfa_fcs_rport_sm_hcb_logorcv);
		bfa_fcs_rport_hal_offline(rport);
		अवरोध;

	हाल RPSM_EVENT_DELETE:
		अगर (rport->pid && (rport->prlo == BFA_TRUE))
			bfa_fcs_rport_send_prlo_acc(rport);
		अगर (rport->pid && (rport->prlo == BFA_FALSE))
			bfa_fcs_rport_send_logo_acc(rport);

		bfa_sm_set_state(rport, bfa_fcs_rport_sm_fc4_off_delete);
		अवरोध;

	हाल RPSM_EVENT_SCN_ONLINE:
	हाल RPSM_EVENT_SCN_OFFLINE:
	हाल RPSM_EVENT_HCB_ONLINE:
	हाल RPSM_EVENT_LOGO_RCVD:
	हाल RPSM_EVENT_PRLO_RCVD:
	हाल RPSM_EVENT_ADDRESS_CHANGE:
		अवरोध;

	शेष:
		bfa_sm_fault(rport->fcs, event);
	पूर्ण
पूर्ण

/*
 *		LOGO needs to be sent to rport. Aरुकोing FC-4 offline completion
 *		callback.
 */
अटल व्योम
bfa_fcs_rport_sm_fc4_logosend(काष्ठा bfa_fcs_rport_s *rport,
	 क्रमागत rport_event event)
अणु
	bfa_trc(rport->fcs, rport->pwwn);
	bfa_trc(rport->fcs, rport->pid);
	bfa_trc(rport->fcs, event);

	चयन (event) अणु
	हाल RPSM_EVENT_FC4_OFFLINE:
		bfa_sm_set_state(rport, bfa_fcs_rport_sm_hcb_logosend);
		bfa_fcs_rport_hal_offline(rport);
		अवरोध;

	हाल RPSM_EVENT_LOGO_RCVD:
		bfa_fcs_rport_send_logo_acc(rport);
		fallthrough;
	हाल RPSM_EVENT_PRLO_RCVD:
		अगर (rport->prlo == BFA_TRUE)
			bfa_fcs_rport_send_prlo_acc(rport);
		bfa_sm_set_state(rport, bfa_fcs_rport_sm_fc4_off_delete);
		अवरोध;

	हाल RPSM_EVENT_HCB_ONLINE:
	हाल RPSM_EVENT_DELETE:
		/* Rport is being deleted */
		अवरोध;

	शेष:
		bfa_sm_fault(rport->fcs, event);
	पूर्ण
पूर्ण

/*
 *	Rport is going offline. Aरुकोing FC-4 offline completion callback.
 */
अटल व्योम
bfa_fcs_rport_sm_fc4_offline(काष्ठा bfa_fcs_rport_s *rport,
			क्रमागत rport_event event)
अणु
	bfa_trc(rport->fcs, rport->pwwn);
	bfa_trc(rport->fcs, rport->pid);
	bfa_trc(rport->fcs, event);

	चयन (event) अणु
	हाल RPSM_EVENT_FC4_OFFLINE:
		bfa_sm_set_state(rport, bfa_fcs_rport_sm_hcb_offline);
		bfa_fcs_rport_hal_offline(rport);
		अवरोध;

	हाल RPSM_EVENT_SCN_ONLINE:
		अवरोध;
	हाल RPSM_EVENT_LOGO_RCVD:
		/*
		 * Rport is going offline. Just ack the logo
		 */
		bfa_fcs_rport_send_logo_acc(rport);
		अवरोध;

	हाल RPSM_EVENT_PRLO_RCVD:
		bfa_fcs_rport_send_prlo_acc(rport);
		अवरोध;

	हाल RPSM_EVENT_SCN_OFFLINE:
	हाल RPSM_EVENT_HCB_ONLINE:
	हाल RPSM_EVENT_FAB_SCN:
	हाल RPSM_EVENT_LOGO_IMP:
	हाल RPSM_EVENT_ADDRESS_CHANGE:
		/*
		 * rport is alपढ़ोy going offline.
		 * SCN - ignore and रुको till transitioning to offline state
		 */
		अवरोध;

	हाल RPSM_EVENT_DELETE:
		bfa_sm_set_state(rport, bfa_fcs_rport_sm_fc4_logosend);
		अवरोध;

	शेष:
		bfa_sm_fault(rport->fcs, event);
	पूर्ण
पूर्ण

/*
 *		Rport is offline. FC-4s are offline. Aरुकोing BFA rport offline
 *		callback.
 */
अटल व्योम
bfa_fcs_rport_sm_hcb_offline(काष्ठा bfa_fcs_rport_s *rport,
				क्रमागत rport_event event)
अणु
	bfa_trc(rport->fcs, rport->pwwn);
	bfa_trc(rport->fcs, rport->pid);
	bfa_trc(rport->fcs, event);

	चयन (event) अणु
	हाल RPSM_EVENT_HCB_OFFLINE:
		अगर (bfa_fcs_lport_is_online(rport->port) &&
		    (rport->plogi_pending)) अणु
			rport->plogi_pending = BFA_FALSE;
			bfa_sm_set_state(rport,
				bfa_fcs_rport_sm_plogiacc_sending);
			bfa_fcs_rport_send_plogiacc(rport, शून्य);
			अवरोध;
		पूर्ण
		fallthrough;

	हाल RPSM_EVENT_ADDRESS_CHANGE:
		अगर (!bfa_fcs_lport_is_online(rport->port)) अणु
			rport->pid = 0;
			bfa_sm_set_state(rport, bfa_fcs_rport_sm_offline);
			bfa_समयr_start(rport->fcs->bfa, &rport->समयr,
					bfa_fcs_rport_समयout, rport,
					bfa_fcs_rport_del_समयout);
			अवरोध;
		पूर्ण
		अगर (bfa_fcs_fabric_is_चयनed(rport->port->fabric)) अणु
			bfa_sm_set_state(rport,
				bfa_fcs_rport_sm_nsdisc_sending);
			rport->ns_retries = 0;
			bfa_fcs_rport_send_nsdisc(rport, शून्य);
		पूर्ण अन्यथा अगर (bfa_fcport_get_topology(rport->port->fcs->bfa) ==
					BFA_PORT_TOPOLOGY_LOOP) अणु
			अगर (rport->scn_online) अणु
				bfa_sm_set_state(rport,
					bfa_fcs_rport_sm_adisc_offline_sending);
				bfa_fcs_rport_send_adisc(rport, शून्य);
			पूर्ण अन्यथा अणु
				bfa_sm_set_state(rport,
					bfa_fcs_rport_sm_offline);
				bfa_समयr_start(rport->fcs->bfa, &rport->समयr,
					bfa_fcs_rport_समयout, rport,
					bfa_fcs_rport_del_समयout);
			पूर्ण
		पूर्ण अन्यथा अणु
			bfa_sm_set_state(rport, bfa_fcs_rport_sm_plogi_sending);
			rport->plogi_retries = 0;
			bfa_fcs_rport_send_plogi(rport, शून्य);
		पूर्ण
		अवरोध;

	हाल RPSM_EVENT_DELETE:
		bfa_sm_set_state(rport, bfa_fcs_rport_sm_uninit);
		bfa_fcs_rport_मुक्त(rport);
		अवरोध;

	हाल RPSM_EVENT_SCN_ONLINE:
	हाल RPSM_EVENT_SCN_OFFLINE:
	हाल RPSM_EVENT_FAB_SCN:
	हाल RPSM_EVENT_LOGO_RCVD:
	हाल RPSM_EVENT_PRLO_RCVD:
	हाल RPSM_EVENT_PLOGI_RCVD:
	हाल RPSM_EVENT_LOGO_IMP:
		/*
		 * Ignore, alपढ़ोy offline.
		 */
		अवरोध;

	शेष:
		bfa_sm_fault(rport->fcs, event);
	पूर्ण
पूर्ण

/*
 *		Rport is offline. FC-4s are offline. Aरुकोing BFA rport offline
 *		callback to send LOGO accept.
 */
अटल व्योम
bfa_fcs_rport_sm_hcb_logorcv(काष्ठा bfa_fcs_rport_s *rport,
			क्रमागत rport_event event)
अणु
	bfa_trc(rport->fcs, rport->pwwn);
	bfa_trc(rport->fcs, rport->pid);
	bfa_trc(rport->fcs, event);

	चयन (event) अणु
	हाल RPSM_EVENT_HCB_OFFLINE:
	हाल RPSM_EVENT_ADDRESS_CHANGE:
		अगर (rport->pid && (rport->prlo == BFA_TRUE))
			bfa_fcs_rport_send_prlo_acc(rport);
		अगर (rport->pid && (rport->prlo == BFA_FALSE))
			bfa_fcs_rport_send_logo_acc(rport);
		/*
		 * If the lport is online and अगर the rport is not a well
		 * known address port,
		 * we try to re-discover the r-port.
		 */
		अगर (bfa_fcs_lport_is_online(rport->port) &&
			(!BFA_FCS_PID_IS_WKA(rport->pid))) अणु
			अगर (bfa_fcs_fabric_is_चयनed(rport->port->fabric)) अणु
				bfa_sm_set_state(rport,
					bfa_fcs_rport_sm_nsdisc_sending);
				rport->ns_retries = 0;
				bfa_fcs_rport_send_nsdisc(rport, शून्य);
			पूर्ण अन्यथा अणु
				/* For N2N  Direct Attach, try to re-login */
				bfa_sm_set_state(rport,
					bfa_fcs_rport_sm_plogi_sending);
				rport->plogi_retries = 0;
				bfa_fcs_rport_send_plogi(rport, शून्य);
			पूर्ण
		पूर्ण अन्यथा अणु
			/*
			 * अगर it is not a well known address, reset the
			 * pid to 0.
			 */
			अगर (!BFA_FCS_PID_IS_WKA(rport->pid))
				rport->pid = 0;
			bfa_sm_set_state(rport, bfa_fcs_rport_sm_offline);
			bfa_समयr_start(rport->fcs->bfa, &rport->समयr,
					bfa_fcs_rport_समयout, rport,
					bfa_fcs_rport_del_समयout);
		पूर्ण
		अवरोध;

	हाल RPSM_EVENT_DELETE:
		bfa_sm_set_state(rport, bfa_fcs_rport_sm_delete_pending);
		अगर (rport->pid && (rport->prlo == BFA_TRUE))
			bfa_fcs_rport_send_prlo_acc(rport);
		अगर (rport->pid && (rport->prlo == BFA_FALSE))
			bfa_fcs_rport_send_logo_acc(rport);
		अवरोध;

	हाल RPSM_EVENT_LOGO_IMP:
		bfa_sm_set_state(rport, bfa_fcs_rport_sm_hcb_offline);
		अवरोध;

	हाल RPSM_EVENT_SCN_ONLINE:
	हाल RPSM_EVENT_SCN_OFFLINE:
	हाल RPSM_EVENT_LOGO_RCVD:
	हाल RPSM_EVENT_PRLO_RCVD:
		/*
		 * Ignore - alपढ़ोy processing a LOGO.
		 */
		अवरोध;

	शेष:
		bfa_sm_fault(rport->fcs, event);
	पूर्ण
पूर्ण

/*
 *		Rport is being deleted. FC-4s are offline.
 *  Aरुकोing BFA rport offline
 *		callback to send LOGO.
 */
अटल व्योम
bfa_fcs_rport_sm_hcb_logosend(काष्ठा bfa_fcs_rport_s *rport,
		 क्रमागत rport_event event)
अणु
	bfa_trc(rport->fcs, rport->pwwn);
	bfa_trc(rport->fcs, rport->pid);
	bfa_trc(rport->fcs, event);

	चयन (event) अणु
	हाल RPSM_EVENT_HCB_OFFLINE:
		bfa_sm_set_state(rport, bfa_fcs_rport_sm_logo_sending);
		bfa_fcs_rport_send_logo(rport, शून्य);
		अवरोध;

	हाल RPSM_EVENT_LOGO_RCVD:
		bfa_fcs_rport_send_logo_acc(rport);
		fallthrough;
	हाल RPSM_EVENT_PRLO_RCVD:
		अगर (rport->prlo == BFA_TRUE)
			bfa_fcs_rport_send_prlo_acc(rport);

		bfa_sm_set_state(rport, bfa_fcs_rport_sm_delete_pending);
		अवरोध;

	हाल RPSM_EVENT_SCN_ONLINE:
	हाल RPSM_EVENT_SCN_OFFLINE:
	हाल RPSM_EVENT_ADDRESS_CHANGE:
		अवरोध;

	शेष:
		bfa_sm_fault(rport->fcs, event);
	पूर्ण
पूर्ण

/*
 *		Rport is being deleted. FC-4s are offline. LOGO is being sent.
 */
अटल व्योम
bfa_fcs_rport_sm_logo_sending(काष्ठा bfa_fcs_rport_s *rport,
	 क्रमागत rport_event event)
अणु
	bfa_trc(rport->fcs, rport->pwwn);
	bfa_trc(rport->fcs, rport->pid);
	bfa_trc(rport->fcs, event);

	चयन (event) अणु
	हाल RPSM_EVENT_FCXP_SENT:
		/* Once LOGO is sent, we करोnot रुको क्रम the response */
		bfa_sm_set_state(rport, bfa_fcs_rport_sm_uninit);
		bfa_fcs_rport_मुक्त(rport);
		अवरोध;

	हाल RPSM_EVENT_SCN_ONLINE:
	हाल RPSM_EVENT_SCN_OFFLINE:
	हाल RPSM_EVENT_FAB_SCN:
	हाल RPSM_EVENT_ADDRESS_CHANGE:
		अवरोध;

	हाल RPSM_EVENT_LOGO_RCVD:
		bfa_fcs_rport_send_logo_acc(rport);
		fallthrough;
	हाल RPSM_EVENT_PRLO_RCVD:
		अगर (rport->prlo == BFA_TRUE)
			bfa_fcs_rport_send_prlo_acc(rport);

		bfa_sm_set_state(rport, bfa_fcs_rport_sm_uninit);
		bfa_fcxp_walloc_cancel(rport->fcs->bfa, &rport->fcxp_wqe);
		bfa_fcs_rport_मुक्त(rport);
		अवरोध;

	शेष:
		bfa_sm_fault(rport->fcs, event);
	पूर्ण
पूर्ण

/*
 *		Rport is offline. FC-4s are offline. BFA rport is offline.
 *		Timer active to delete stale rport.
 */
अटल व्योम
bfa_fcs_rport_sm_offline(काष्ठा bfa_fcs_rport_s *rport, क्रमागत rport_event event)
अणु
	bfa_trc(rport->fcs, rport->pwwn);
	bfa_trc(rport->fcs, rport->pid);
	bfa_trc(rport->fcs, event);

	चयन (event) अणु
	हाल RPSM_EVENT_TIMEOUT:
		bfa_sm_set_state(rport, bfa_fcs_rport_sm_uninit);
		bfa_fcs_rport_मुक्त(rport);
		अवरोध;

	हाल RPSM_EVENT_FAB_SCN:
	हाल RPSM_EVENT_ADDRESS_CHANGE:
		bfa_समयr_stop(&rport->समयr);
		WARN_ON(!(bfa_fcport_get_topology(rport->port->fcs->bfa) !=
					BFA_PORT_TOPOLOGY_LOOP));
		bfa_sm_set_state(rport, bfa_fcs_rport_sm_nsdisc_sending);
		rport->ns_retries = 0;
		bfa_fcs_rport_send_nsdisc(rport, शून्य);
		अवरोध;

	हाल RPSM_EVENT_DELETE:
		bfa_sm_set_state(rport, bfa_fcs_rport_sm_uninit);
		bfa_समयr_stop(&rport->समयr);
		bfa_fcs_rport_मुक्त(rport);
		अवरोध;

	हाल RPSM_EVENT_PLOGI_RCVD:
		bfa_sm_set_state(rport, bfa_fcs_rport_sm_plogiacc_sending);
		bfa_समयr_stop(&rport->समयr);
		bfa_fcs_rport_send_plogiacc(rport, शून्य);
		अवरोध;

	हाल RPSM_EVENT_LOGO_RCVD:
	हाल RPSM_EVENT_PRLO_RCVD:
	हाल RPSM_EVENT_LOGO_IMP:
	हाल RPSM_EVENT_SCN_OFFLINE:
		अवरोध;

	हाल RPSM_EVENT_PLOGI_COMP:
		bfa_sm_set_state(rport, bfa_fcs_rport_sm_fc4_fcs_online);
		bfa_समयr_stop(&rport->समयr);
		bfa_fcs_rport_fcs_online_action(rport);
		अवरोध;

	हाल RPSM_EVENT_SCN_ONLINE:
		bfa_समयr_stop(&rport->समयr);
		bfa_sm_set_state(rport, bfa_fcs_rport_sm_plogi_sending);
		bfa_fcs_rport_send_plogi(rport, शून्य);
		अवरोध;

	हाल RPSM_EVENT_PLOGI_SEND:
		bfa_समयr_stop(&rport->समयr);
		bfa_sm_set_state(rport, bfa_fcs_rport_sm_plogi_sending);
		rport->plogi_retries = 0;
		bfa_fcs_rport_send_plogi(rport, शून्य);
		अवरोध;

	शेष:
		bfa_sm_fault(rport->fcs, event);
	पूर्ण
पूर्ण

/*
 *	Rport address has changed. Nameserver discovery request is being sent.
 */
अटल व्योम
bfa_fcs_rport_sm_nsdisc_sending(काष्ठा bfa_fcs_rport_s *rport,
	 क्रमागत rport_event event)
अणु
	bfa_trc(rport->fcs, rport->pwwn);
	bfa_trc(rport->fcs, rport->pid);
	bfa_trc(rport->fcs, event);

	चयन (event) अणु
	हाल RPSM_EVENT_FCXP_SENT:
		bfa_sm_set_state(rport, bfa_fcs_rport_sm_nsdisc_sent);
		अवरोध;

	हाल RPSM_EVENT_DELETE:
		bfa_sm_set_state(rport, bfa_fcs_rport_sm_uninit);
		bfa_fcxp_walloc_cancel(rport->fcs->bfa, &rport->fcxp_wqe);
		bfa_fcs_rport_मुक्त(rport);
		अवरोध;

	हाल RPSM_EVENT_PLOGI_RCVD:
		bfa_sm_set_state(rport, bfa_fcs_rport_sm_plogiacc_sending);
		bfa_fcxp_walloc_cancel(rport->fcs->bfa, &rport->fcxp_wqe);
		bfa_fcs_rport_send_plogiacc(rport, शून्य);
		अवरोध;

	हाल RPSM_EVENT_FAB_SCN:
	हाल RPSM_EVENT_LOGO_RCVD:
	हाल RPSM_EVENT_PRLO_RCVD:
	हाल RPSM_EVENT_PLOGI_SEND:
		अवरोध;

	हाल RPSM_EVENT_ADDRESS_CHANGE:
		rport->ns_retries = 0; /* reset the retry count */
		अवरोध;

	हाल RPSM_EVENT_LOGO_IMP:
		bfa_sm_set_state(rport, bfa_fcs_rport_sm_offline);
		bfa_fcxp_walloc_cancel(rport->fcs->bfa, &rport->fcxp_wqe);
		bfa_समयr_start(rport->fcs->bfa, &rport->समयr,
				bfa_fcs_rport_समयout, rport,
				bfa_fcs_rport_del_समयout);
		अवरोध;

	हाल RPSM_EVENT_PLOGI_COMP:
		bfa_sm_set_state(rport, bfa_fcs_rport_sm_fc4_fcs_online);
		bfa_fcxp_walloc_cancel(rport->fcs->bfa, &rport->fcxp_wqe);
		bfa_fcs_rport_fcs_online_action(rport);
		अवरोध;

	शेष:
		bfa_sm_fault(rport->fcs, event);
	पूर्ण
पूर्ण

/*
 *		Nameserver discovery failed. Waiting क्रम समयout to retry.
 */
अटल व्योम
bfa_fcs_rport_sm_nsdisc_retry(काष्ठा bfa_fcs_rport_s *rport,
	 क्रमागत rport_event event)
अणु
	bfa_trc(rport->fcs, rport->pwwn);
	bfa_trc(rport->fcs, rport->pid);
	bfa_trc(rport->fcs, event);

	चयन (event) अणु
	हाल RPSM_EVENT_TIMEOUT:
		bfa_sm_set_state(rport, bfa_fcs_rport_sm_nsdisc_sending);
		bfa_fcs_rport_send_nsdisc(rport, शून्य);
		अवरोध;

	हाल RPSM_EVENT_FAB_SCN:
	हाल RPSM_EVENT_ADDRESS_CHANGE:
		bfa_sm_set_state(rport, bfa_fcs_rport_sm_nsdisc_sending);
		bfa_समयr_stop(&rport->समयr);
		rport->ns_retries = 0;
		bfa_fcs_rport_send_nsdisc(rport, शून्य);
		अवरोध;

	हाल RPSM_EVENT_DELETE:
		bfa_sm_set_state(rport, bfa_fcs_rport_sm_uninit);
		bfa_समयr_stop(&rport->समयr);
		bfa_fcs_rport_मुक्त(rport);
		अवरोध;

	हाल RPSM_EVENT_PLOGI_RCVD:
		bfa_sm_set_state(rport, bfa_fcs_rport_sm_plogiacc_sending);
		bfa_समयr_stop(&rport->समयr);
		bfa_fcs_rport_send_plogiacc(rport, शून्य);
		अवरोध;

	हाल RPSM_EVENT_LOGO_IMP:
		rport->pid = 0;
		bfa_sm_set_state(rport, bfa_fcs_rport_sm_offline);
		bfa_समयr_stop(&rport->समयr);
		bfa_समयr_start(rport->fcs->bfa, &rport->समयr,
				bfa_fcs_rport_समयout, rport,
				bfa_fcs_rport_del_समयout);
		अवरोध;

	हाल RPSM_EVENT_LOGO_RCVD:
		bfa_fcs_rport_send_logo_acc(rport);
		अवरोध;
	हाल RPSM_EVENT_PRLO_RCVD:
		bfa_fcs_rport_send_prlo_acc(rport);
		अवरोध;

	हाल RPSM_EVENT_PLOGI_COMP:
		bfa_sm_set_state(rport, bfa_fcs_rport_sm_fc4_fcs_online);
		bfa_समयr_stop(&rport->समयr);
		bfa_fcs_rport_fcs_online_action(rport);
		अवरोध;

	शेष:
		bfa_sm_fault(rport->fcs, event);
	पूर्ण
पूर्ण

/*
 *		Rport address has changed. Nameserver discovery request is sent.
 */
अटल व्योम
bfa_fcs_rport_sm_nsdisc_sent(काष्ठा bfa_fcs_rport_s *rport,
			क्रमागत rport_event event)
अणु
	bfa_trc(rport->fcs, rport->pwwn);
	bfa_trc(rport->fcs, rport->pid);
	bfa_trc(rport->fcs, event);

	चयन (event) अणु
	हाल RPSM_EVENT_ACCEPTED:
	हाल RPSM_EVENT_ADDRESS_CHANGE:
		अगर (rport->pid) अणु
			bfa_sm_set_state(rport, bfa_fcs_rport_sm_plogi_sending);
			bfa_fcs_rport_send_plogi(rport, शून्य);
		पूर्ण अन्यथा अणु
			bfa_sm_set_state(rport,
				 bfa_fcs_rport_sm_nsdisc_sending);
			rport->ns_retries = 0;
			bfa_fcs_rport_send_nsdisc(rport, शून्य);
		पूर्ण
		अवरोध;

	हाल RPSM_EVENT_FAILED:
		rport->ns_retries++;
		अगर (rport->ns_retries < BFA_FCS_RPORT_MAX_RETRIES) अणु
			bfa_sm_set_state(rport,
				 bfa_fcs_rport_sm_nsdisc_sending);
			bfa_fcs_rport_send_nsdisc(rport, शून्य);
		पूर्ण अन्यथा अणु
			rport->old_pid = rport->pid;
			rport->pid = 0;
			bfa_sm_set_state(rport, bfa_fcs_rport_sm_offline);
			bfa_समयr_start(rport->fcs->bfa, &rport->समयr,
					bfa_fcs_rport_समयout, rport,
					bfa_fcs_rport_del_समयout);
		पूर्ण
		अवरोध;

	हाल RPSM_EVENT_DELETE:
		bfa_sm_set_state(rport, bfa_fcs_rport_sm_uninit);
		bfa_fcxp_discard(rport->fcxp);
		bfa_fcs_rport_मुक्त(rport);
		अवरोध;

	हाल RPSM_EVENT_PLOGI_RCVD:
		bfa_sm_set_state(rport, bfa_fcs_rport_sm_plogiacc_sending);
		bfa_fcxp_discard(rport->fcxp);
		bfa_fcs_rport_send_plogiacc(rport, शून्य);
		अवरोध;

	हाल RPSM_EVENT_LOGO_IMP:
		rport->pid = 0;
		bfa_sm_set_state(rport, bfa_fcs_rport_sm_offline);
		bfa_fcxp_discard(rport->fcxp);
		bfa_समयr_start(rport->fcs->bfa, &rport->समयr,
				bfa_fcs_rport_समयout, rport,
				bfa_fcs_rport_del_समयout);
		अवरोध;


	हाल RPSM_EVENT_PRLO_RCVD:
		bfa_fcs_rport_send_prlo_acc(rport);
		अवरोध;
	हाल RPSM_EVENT_FAB_SCN:
		/*
		 * ignore, रुको क्रम NS query response
		 */
		अवरोध;

	हाल RPSM_EVENT_LOGO_RCVD:
		/*
		 * Not logged-in yet. Accept LOGO.
		 */
		bfa_fcs_rport_send_logo_acc(rport);
		अवरोध;

	हाल RPSM_EVENT_PLOGI_COMP:
		bfa_sm_set_state(rport, bfa_fcs_rport_sm_fc4_fcs_online);
		bfa_fcxp_discard(rport->fcxp);
		bfa_fcs_rport_fcs_online_action(rport);
		अवरोध;

	शेष:
		bfa_sm_fault(rport->fcs, event);
	पूर्ण
पूर्ण

/*
 * Rport needs to be deleted
 * रुकोing क्रम ITNIM clean up to finish
 */
अटल व्योम
bfa_fcs_rport_sm_fc4_off_delete(काष्ठा bfa_fcs_rport_s *rport,
				क्रमागत rport_event event)
अणु
	bfa_trc(rport->fcs, rport->pwwn);
	bfa_trc(rport->fcs, rport->pid);
	bfa_trc(rport->fcs, event);

	चयन (event) अणु
	हाल RPSM_EVENT_FC4_OFFLINE:
		bfa_sm_set_state(rport, bfa_fcs_rport_sm_delete_pending);
		bfa_fcs_rport_hal_offline(rport);
		अवरोध;

	हाल RPSM_EVENT_DELETE:
	हाल RPSM_EVENT_PLOGI_RCVD:
		/* Ignore these events */
		अवरोध;

	शेष:
		bfa_sm_fault(rport->fcs, event);
		अवरोध;
	पूर्ण
पूर्ण

/*
 * RPort needs to be deleted
 * रुकोing क्रम BFA/FW to finish current processing
 */
अटल व्योम
bfa_fcs_rport_sm_delete_pending(काष्ठा bfa_fcs_rport_s *rport,
				क्रमागत rport_event event)
अणु
	bfa_trc(rport->fcs, rport->pwwn);
	bfa_trc(rport->fcs, rport->pid);
	bfa_trc(rport->fcs, event);

	चयन (event) अणु
	हाल RPSM_EVENT_HCB_OFFLINE:
		bfa_sm_set_state(rport, bfa_fcs_rport_sm_uninit);
		bfa_fcs_rport_मुक्त(rport);
		अवरोध;

	हाल RPSM_EVENT_DELETE:
	हाल RPSM_EVENT_LOGO_IMP:
	हाल RPSM_EVENT_PLOGI_RCVD:
		/* Ignore these events */
		अवरोध;

	शेष:
		bfa_sm_fault(rport->fcs, event);
	पूर्ण
पूर्ण

/*
 *  fcs_rport_निजी FCS RPORT provate functions
 */

अटल व्योम
bfa_fcs_rport_send_plogi(व्योम *rport_cbarg, काष्ठा bfa_fcxp_s *fcxp_alloced)
अणु
	काष्ठा bfa_fcs_rport_s *rport = rport_cbarg;
	काष्ठा bfa_fcs_lport_s *port = rport->port;
	काष्ठा fchs_s	fchs;
	पूर्णांक		len;
	काष्ठा bfa_fcxp_s *fcxp;

	bfa_trc(rport->fcs, rport->pwwn);

	fcxp = fcxp_alloced ? fcxp_alloced :
	       bfa_fcs_fcxp_alloc(port->fcs, BFA_TRUE);
	अगर (!fcxp) अणु
		bfa_fcs_fcxp_alloc_रुको(port->fcs->bfa, &rport->fcxp_wqe,
				bfa_fcs_rport_send_plogi, rport, BFA_TRUE);
		वापस;
	पूर्ण
	rport->fcxp = fcxp;

	len = fc_plogi_build(&fchs, bfa_fcxp_get_reqbuf(fcxp), rport->pid,
				bfa_fcs_lport_get_fcid(port), 0,
				port->port_cfg.pwwn, port->port_cfg.nwwn,
				bfa_fcport_get_maxfrsize(port->fcs->bfa),
				bfa_fcport_get_rx_bbcredit(port->fcs->bfa));

	bfa_fcxp_send(fcxp, शून्य, port->fabric->vf_id, port->lp_tag, BFA_FALSE,
			FC_CLASS_3, len, &fchs, bfa_fcs_rport_plogi_response,
			(व्योम *)rport, FC_MAX_PDUSZ, FC_ELS_TOV);

	rport->stats.plogis++;
	bfa_sm_send_event(rport, RPSM_EVENT_FCXP_SENT);
पूर्ण

अटल व्योम
bfa_fcs_rport_plogi_response(व्योम *fcsarg, काष्ठा bfa_fcxp_s *fcxp, व्योम *cbarg,
				bfa_status_t req_status, u32 rsp_len,
				u32 resid_len, काष्ठा fchs_s *rsp_fchs)
अणु
	काष्ठा bfa_fcs_rport_s *rport = (काष्ठा bfa_fcs_rport_s *) cbarg;
	काष्ठा fc_logi_s	*plogi_rsp;
	काष्ठा fc_ls_rjt_s	*ls_rjt;
	काष्ठा bfa_fcs_rport_s *twin;
	काष्ठा list_head	*qe;

	bfa_trc(rport->fcs, rport->pwwn);

	/*
	 * Sanity Checks
	 */
	अगर (req_status != BFA_STATUS_OK) अणु
		bfa_trc(rport->fcs, req_status);
		rport->stats.plogi_failed++;
		bfa_sm_send_event(rport, RPSM_EVENT_FAILED);
		वापस;
	पूर्ण

	plogi_rsp = (काष्ठा fc_logi_s *) BFA_FCXP_RSP_PLD(fcxp);

	/*
	 * Check क्रम failure first.
	 */
	अगर (plogi_rsp->els_cmd.els_code != FC_ELS_ACC) अणु
		ls_rjt = (काष्ठा fc_ls_rjt_s *) BFA_FCXP_RSP_PLD(fcxp);

		bfa_trc(rport->fcs, ls_rjt->reason_code);
		bfa_trc(rport->fcs, ls_rjt->reason_code_expl);

		अगर ((ls_rjt->reason_code == FC_LS_RJT_RSN_UNABLE_TO_PERF_CMD) &&
		 (ls_rjt->reason_code_expl == FC_LS_RJT_EXP_INSUFF_RES)) अणु
			rport->stats.rjt_insuff_res++;
			bfa_sm_send_event(rport, RPSM_EVENT_PLOGI_RETRY);
			वापस;
		पूर्ण

		rport->stats.plogi_rejects++;
		bfa_sm_send_event(rport, RPSM_EVENT_FAILED);
		वापस;
	पूर्ण

	/*
	 * PLOGI is complete. Make sure this device is not one of the known
	 * device with a new FC port address.
	 */
	list_क्रम_each(qe, &rport->port->rport_q) अणु
		twin = (काष्ठा bfa_fcs_rport_s *) qe;
		अगर (twin == rport)
			जारी;
		अगर (!rport->pwwn && (plogi_rsp->port_name == twin->pwwn)) अणु
			bfa_trc(rport->fcs, twin->pid);
			bfa_trc(rport->fcs, rport->pid);

			/* Update plogi stats in twin */
			twin->stats.plogis  += rport->stats.plogis;
			twin->stats.plogi_rejects  +=
				 rport->stats.plogi_rejects;
			twin->stats.plogi_समयouts  +=
				 rport->stats.plogi_समयouts;
			twin->stats.plogi_failed +=
				 rport->stats.plogi_failed;
			twin->stats.plogi_rcvd	  += rport->stats.plogi_rcvd;
			twin->stats.plogi_accs++;

			bfa_sm_send_event(rport, RPSM_EVENT_DELETE);

			bfa_fcs_rport_update(twin, plogi_rsp);
			twin->pid = rsp_fchs->s_id;
			bfa_sm_send_event(twin, RPSM_EVENT_PLOGI_COMP);
			वापस;
		पूर्ण
	पूर्ण

	/*
	 * Normal login path -- no evil twins.
	 */
	rport->stats.plogi_accs++;
	bfa_fcs_rport_update(rport, plogi_rsp);
	bfa_sm_send_event(rport, RPSM_EVENT_ACCEPTED);
पूर्ण

अटल व्योम
bfa_fcs_rport_send_plogiacc(व्योम *rport_cbarg, काष्ठा bfa_fcxp_s *fcxp_alloced)
अणु
	काष्ठा bfa_fcs_rport_s *rport = rport_cbarg;
	काष्ठा bfa_fcs_lport_s *port = rport->port;
	काष्ठा fchs_s		fchs;
	पूर्णांक		len;
	काष्ठा bfa_fcxp_s *fcxp;

	bfa_trc(rport->fcs, rport->pwwn);
	bfa_trc(rport->fcs, rport->reply_oxid);

	fcxp = fcxp_alloced ? fcxp_alloced :
	       bfa_fcs_fcxp_alloc(port->fcs, BFA_FALSE);
	अगर (!fcxp) अणु
		bfa_fcs_fcxp_alloc_रुको(port->fcs->bfa, &rport->fcxp_wqe,
				bfa_fcs_rport_send_plogiacc, rport, BFA_FALSE);
		वापस;
	पूर्ण
	rport->fcxp = fcxp;

	len = fc_plogi_acc_build(&fchs, bfa_fcxp_get_reqbuf(fcxp),
				 rport->pid, bfa_fcs_lport_get_fcid(port),
				 rport->reply_oxid, port->port_cfg.pwwn,
				 port->port_cfg.nwwn,
				 bfa_fcport_get_maxfrsize(port->fcs->bfa),
				 bfa_fcport_get_rx_bbcredit(port->fcs->bfa));

	bfa_fcxp_send(fcxp, शून्य, port->fabric->vf_id, port->lp_tag, BFA_FALSE,
			FC_CLASS_3, len, &fchs, शून्य, शून्य, FC_MAX_PDUSZ, 0);

	bfa_sm_send_event(rport, RPSM_EVENT_FCXP_SENT);
पूर्ण

अटल व्योम
bfa_fcs_rport_send_adisc(व्योम *rport_cbarg, काष्ठा bfa_fcxp_s *fcxp_alloced)
अणु
	काष्ठा bfa_fcs_rport_s *rport = rport_cbarg;
	काष्ठा bfa_fcs_lport_s *port = rport->port;
	काष्ठा fchs_s		fchs;
	पूर्णांक		len;
	काष्ठा bfa_fcxp_s *fcxp;

	bfa_trc(rport->fcs, rport->pwwn);

	fcxp = fcxp_alloced ? fcxp_alloced :
	       bfa_fcs_fcxp_alloc(port->fcs, BFA_TRUE);
	अगर (!fcxp) अणु
		bfa_fcs_fcxp_alloc_रुको(port->fcs->bfa, &rport->fcxp_wqe,
				bfa_fcs_rport_send_adisc, rport, BFA_TRUE);
		वापस;
	पूर्ण
	rport->fcxp = fcxp;

	len = fc_adisc_build(&fchs, bfa_fcxp_get_reqbuf(fcxp), rport->pid,
				bfa_fcs_lport_get_fcid(port), 0,
				port->port_cfg.pwwn, port->port_cfg.nwwn);

	bfa_fcxp_send(fcxp, शून्य, port->fabric->vf_id, port->lp_tag, BFA_FALSE,
			FC_CLASS_3, len, &fchs, bfa_fcs_rport_adisc_response,
			rport, FC_MAX_PDUSZ, FC_ELS_TOV);

	rport->stats.adisc_sent++;
	bfa_sm_send_event(rport, RPSM_EVENT_FCXP_SENT);
पूर्ण

अटल व्योम
bfa_fcs_rport_adisc_response(व्योम *fcsarg, काष्ठा bfa_fcxp_s *fcxp, व्योम *cbarg,
				bfa_status_t req_status, u32 rsp_len,
				u32 resid_len, काष्ठा fchs_s *rsp_fchs)
अणु
	काष्ठा bfa_fcs_rport_s *rport = (काष्ठा bfa_fcs_rport_s *) cbarg;
	व्योम		*pld = bfa_fcxp_get_rspbuf(fcxp);
	काष्ठा fc_ls_rjt_s	*ls_rjt;

	अगर (req_status != BFA_STATUS_OK) अणु
		bfa_trc(rport->fcs, req_status);
		rport->stats.adisc_failed++;
		bfa_sm_send_event(rport, RPSM_EVENT_FAILED);
		वापस;
	पूर्ण

	अगर (fc_adisc_rsp_parse((काष्ठा fc_adisc_s *)pld, rsp_len, rport->pwwn,
				rport->nwwn)  == FC_PARSE_OK) अणु
		rport->stats.adisc_accs++;
		bfa_sm_send_event(rport, RPSM_EVENT_ACCEPTED);
		वापस;
	पूर्ण

	rport->stats.adisc_rejects++;
	ls_rjt = pld;
	bfa_trc(rport->fcs, ls_rjt->els_cmd.els_code);
	bfa_trc(rport->fcs, ls_rjt->reason_code);
	bfa_trc(rport->fcs, ls_rjt->reason_code_expl);
	bfa_sm_send_event(rport, RPSM_EVENT_FAILED);
पूर्ण

अटल व्योम
bfa_fcs_rport_send_nsdisc(व्योम *rport_cbarg, काष्ठा bfa_fcxp_s *fcxp_alloced)
अणु
	काष्ठा bfa_fcs_rport_s *rport = rport_cbarg;
	काष्ठा bfa_fcs_lport_s *port = rport->port;
	काष्ठा fchs_s	fchs;
	काष्ठा bfa_fcxp_s *fcxp;
	पूर्णांक		len;
	bfa_cb_fcxp_send_t cbfn;

	bfa_trc(rport->fcs, rport->pid);

	fcxp = fcxp_alloced ? fcxp_alloced :
	       bfa_fcs_fcxp_alloc(port->fcs, BFA_TRUE);
	अगर (!fcxp) अणु
		bfa_fcs_fcxp_alloc_रुको(port->fcs->bfa, &rport->fcxp_wqe,
				bfa_fcs_rport_send_nsdisc, rport, BFA_TRUE);
		वापस;
	पूर्ण
	rport->fcxp = fcxp;

	अगर (rport->pwwn) अणु
		len = fc_gidpn_build(&fchs, bfa_fcxp_get_reqbuf(fcxp),
				bfa_fcs_lport_get_fcid(port), 0, rport->pwwn);
		cbfn = bfa_fcs_rport_gidpn_response;
	पूर्ण अन्यथा अणु
		len = fc_gpnid_build(&fchs, bfa_fcxp_get_reqbuf(fcxp),
				bfa_fcs_lport_get_fcid(port), 0, rport->pid);
		cbfn = bfa_fcs_rport_gpnid_response;
	पूर्ण

	bfa_fcxp_send(fcxp, शून्य, port->fabric->vf_id, port->lp_tag, BFA_FALSE,
			FC_CLASS_3, len, &fchs, cbfn,
			(व्योम *)rport, FC_MAX_PDUSZ, FC_FCCT_TOV);

	bfa_sm_send_event(rport, RPSM_EVENT_FCXP_SENT);
पूर्ण

अटल व्योम
bfa_fcs_rport_gidpn_response(व्योम *fcsarg, काष्ठा bfa_fcxp_s *fcxp, व्योम *cbarg,
				bfa_status_t req_status, u32 rsp_len,
				u32 resid_len, काष्ठा fchs_s *rsp_fchs)
अणु
	काष्ठा bfa_fcs_rport_s *rport = (काष्ठा bfa_fcs_rport_s *) cbarg;
	काष्ठा ct_hdr_s	*cthdr;
	काष्ठा fcgs_gidpn_resp_s	*gidpn_rsp;
	काष्ठा bfa_fcs_rport_s	*twin;
	काष्ठा list_head	*qe;

	bfa_trc(rport->fcs, rport->pwwn);

	cthdr = (काष्ठा ct_hdr_s *) BFA_FCXP_RSP_PLD(fcxp);
	cthdr->cmd_rsp_code = be16_to_cpu(cthdr->cmd_rsp_code);

	अगर (cthdr->cmd_rsp_code == CT_RSP_ACCEPT) अणु
		/* Check अगर the pid is the same as beक्रमe. */
		gidpn_rsp = (काष्ठा fcgs_gidpn_resp_s *) (cthdr + 1);

		अगर (gidpn_rsp->dap == rport->pid) अणु
			/* Device is online  */
			bfa_sm_send_event(rport, RPSM_EVENT_ACCEPTED);
		पूर्ण अन्यथा अणु
			/*
			 * Device's PID has changed. We need to cleanup
			 * and re-login. If there is another device with
			 * the the newly discovered pid, send an scn notice
			 * so that its new pid can be discovered.
			 */
			list_क्रम_each(qe, &rport->port->rport_q) अणु
				twin = (काष्ठा bfa_fcs_rport_s *) qe;
				अगर (twin == rport)
					जारी;
				अगर (gidpn_rsp->dap == twin->pid) अणु
					bfa_trc(rport->fcs, twin->pid);
					bfa_trc(rport->fcs, rport->pid);

					twin->pid = 0;
					bfa_sm_send_event(twin,
					 RPSM_EVENT_ADDRESS_CHANGE);
				पूर्ण
			पूर्ण
			rport->pid = gidpn_rsp->dap;
			bfa_sm_send_event(rport, RPSM_EVENT_ADDRESS_CHANGE);
		पूर्ण
		वापस;
	पूर्ण

	/*
	 * Reject Response
	 */
	चयन (cthdr->reason_code) अणु
	हाल CT_RSN_LOGICAL_BUSY:
		/*
		 * Need to retry
		 */
		bfa_sm_send_event(rport, RPSM_EVENT_TIMEOUT);
		अवरोध;

	हाल CT_RSN_UNABLE_TO_PERF:
		/*
		 * device करोesn't exist : Start समयr to cleanup this later.
		 */
		bfa_sm_send_event(rport, RPSM_EVENT_FAILED);
		अवरोध;

	शेष:
		bfa_sm_send_event(rport, RPSM_EVENT_FAILED);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम
bfa_fcs_rport_gpnid_response(व्योम *fcsarg, काष्ठा bfa_fcxp_s *fcxp, व्योम *cbarg,
				bfa_status_t req_status, u32 rsp_len,
				u32 resid_len, काष्ठा fchs_s *rsp_fchs)
अणु
	काष्ठा bfa_fcs_rport_s *rport = (काष्ठा bfa_fcs_rport_s *) cbarg;
	काष्ठा ct_hdr_s	*cthdr;

	bfa_trc(rport->fcs, rport->pwwn);

	cthdr = (काष्ठा ct_hdr_s *) BFA_FCXP_RSP_PLD(fcxp);
	cthdr->cmd_rsp_code = be16_to_cpu(cthdr->cmd_rsp_code);

	अगर (cthdr->cmd_rsp_code == CT_RSP_ACCEPT) अणु
		bfa_sm_send_event(rport, RPSM_EVENT_ACCEPTED);
		वापस;
	पूर्ण

	/*
	 * Reject Response
	 */
	चयन (cthdr->reason_code) अणु
	हाल CT_RSN_LOGICAL_BUSY:
		/*
		 * Need to retry
		 */
		bfa_sm_send_event(rport, RPSM_EVENT_TIMEOUT);
		अवरोध;

	हाल CT_RSN_UNABLE_TO_PERF:
		/*
		 * device करोesn't exist : Start समयr to cleanup this later.
		 */
		bfa_sm_send_event(rport, RPSM_EVENT_FAILED);
		अवरोध;

	शेष:
		bfa_sm_send_event(rport, RPSM_EVENT_FAILED);
		अवरोध;
	पूर्ण
पूर्ण

/*
 *	Called to send a logout to the rport.
 */
अटल व्योम
bfa_fcs_rport_send_logo(व्योम *rport_cbarg, काष्ठा bfa_fcxp_s *fcxp_alloced)
अणु
	काष्ठा bfa_fcs_rport_s *rport = rport_cbarg;
	काष्ठा bfa_fcs_lport_s *port;
	काष्ठा fchs_s	fchs;
	काष्ठा bfa_fcxp_s *fcxp;
	u16	len;

	bfa_trc(rport->fcs, rport->pid);

	port = rport->port;

	fcxp = fcxp_alloced ? fcxp_alloced :
	       bfa_fcs_fcxp_alloc(port->fcs, BFA_FALSE);
	अगर (!fcxp) अणु
		bfa_fcs_fcxp_alloc_रुको(port->fcs->bfa, &rport->fcxp_wqe,
				bfa_fcs_rport_send_logo, rport, BFA_FALSE);
		वापस;
	पूर्ण
	rport->fcxp = fcxp;

	len = fc_logo_build(&fchs, bfa_fcxp_get_reqbuf(fcxp), rport->pid,
				bfa_fcs_lport_get_fcid(port), 0,
				bfa_fcs_lport_get_pwwn(port));

	bfa_fcxp_send(fcxp, शून्य, port->fabric->vf_id, port->lp_tag, BFA_FALSE,
			FC_CLASS_3, len, &fchs, शून्य,
			rport, FC_MAX_PDUSZ, FC_ELS_TOV);

	rport->stats.logos++;
	bfa_fcxp_discard(rport->fcxp);
	bfa_sm_send_event(rport, RPSM_EVENT_FCXP_SENT);
पूर्ण

/*
 *	Send ACC क्रम a LOGO received.
 */
अटल व्योम
bfa_fcs_rport_send_logo_acc(व्योम *rport_cbarg)
अणु
	काष्ठा bfa_fcs_rport_s *rport = rport_cbarg;
	काष्ठा bfa_fcs_lport_s *port;
	काष्ठा fchs_s	fchs;
	काष्ठा bfa_fcxp_s *fcxp;
	u16	len;

	bfa_trc(rport->fcs, rport->pid);

	port = rport->port;

	fcxp = bfa_fcs_fcxp_alloc(port->fcs, BFA_FALSE);
	अगर (!fcxp)
		वापस;

	rport->stats.logo_rcvd++;
	len = fc_logo_acc_build(&fchs, bfa_fcxp_get_reqbuf(fcxp),
				rport->pid, bfa_fcs_lport_get_fcid(port),
				rport->reply_oxid);

	bfa_fcxp_send(fcxp, शून्य, port->fabric->vf_id, port->lp_tag, BFA_FALSE,
			FC_CLASS_3, len, &fchs, शून्य, शून्य, FC_MAX_PDUSZ, 0);
पूर्ण

/*
 *	brief
 *	This routine will be called by bfa_समयr on समयr समयouts.
 *
 *	param[in]	rport			- poपूर्णांकer to bfa_fcs_lport_ns_t.
 *	param[out]	rport_status	- poपूर्णांकer to वापस vport status in
 *
 *	वापस
 *		व्योम
 *
 *	Special Considerations:
 *
 *	note
 */
अटल व्योम
bfa_fcs_rport_समयout(व्योम *arg)
अणु
	काष्ठा bfa_fcs_rport_s *rport = (काष्ठा bfa_fcs_rport_s *) arg;

	rport->stats.plogi_समयouts++;
	bfa_stats(rport->port, rport_plogi_समयouts);
	bfa_sm_send_event(rport, RPSM_EVENT_TIMEOUT);
पूर्ण

अटल व्योम
bfa_fcs_rport_process_prli(काष्ठा bfa_fcs_rport_s *rport,
			काष्ठा fchs_s *rx_fchs, u16 len)
अणु
	काष्ठा bfa_fcxp_s *fcxp;
	काष्ठा fchs_s	fchs;
	काष्ठा bfa_fcs_lport_s *port = rport->port;
	काष्ठा fc_prli_s	*prli;

	bfa_trc(port->fcs, rx_fchs->s_id);
	bfa_trc(port->fcs, rx_fchs->d_id);

	rport->stats.prli_rcvd++;

	/*
	 * We are in Initiator Mode
	 */
	prli = (काष्ठा fc_prli_s *) (rx_fchs + 1);

	अगर (prli->parampage.servparams.target) अणु
		/*
		 * PRLI from a target ?
		 * Send the Acc.
		 * PRLI sent by us will be used to transition the IT nexus,
		 * once the response is received from the target.
		 */
		bfa_trc(port->fcs, rx_fchs->s_id);
		rport->scsi_function = BFA_RPORT_TARGET;
	पूर्ण अन्यथा अणु
		bfa_trc(rport->fcs, prli->parampage.type);
		rport->scsi_function = BFA_RPORT_INITIATOR;
		bfa_fcs_itnim_is_initiator(rport->itnim);
	पूर्ण

	fcxp = bfa_fcs_fcxp_alloc(port->fcs, BFA_FALSE);
	अगर (!fcxp)
		वापस;

	len = fc_prli_acc_build(&fchs, bfa_fcxp_get_reqbuf(fcxp),
				rx_fchs->s_id, bfa_fcs_lport_get_fcid(port),
				rx_fchs->ox_id, port->port_cfg.roles);

	bfa_fcxp_send(fcxp, शून्य, port->fabric->vf_id, port->lp_tag, BFA_FALSE,
			FC_CLASS_3, len, &fchs, शून्य, शून्य, FC_MAX_PDUSZ, 0);
पूर्ण

अटल व्योम
bfa_fcs_rport_process_rpsc(काष्ठा bfa_fcs_rport_s *rport,
			काष्ठा fchs_s *rx_fchs, u16 len)
अणु
	काष्ठा bfa_fcxp_s *fcxp;
	काष्ठा fchs_s	fchs;
	काष्ठा bfa_fcs_lport_s *port = rport->port;
	काष्ठा fc_rpsc_speed_info_s speeds;
	काष्ठा bfa_port_attr_s pport_attr;

	bfa_trc(port->fcs, rx_fchs->s_id);
	bfa_trc(port->fcs, rx_fchs->d_id);

	rport->stats.rpsc_rcvd++;
	speeds.port_speed_cap =
		RPSC_SPEED_CAP_1G | RPSC_SPEED_CAP_2G | RPSC_SPEED_CAP_4G |
		RPSC_SPEED_CAP_8G;

	/*
	 * get curent speed from pport attributes from BFA
	 */
	bfa_fcport_get_attr(port->fcs->bfa, &pport_attr);

	speeds.port_op_speed = fc_bfa_speed_to_rpsc_operspeed(pport_attr.speed);

	fcxp = bfa_fcs_fcxp_alloc(port->fcs, BFA_FALSE);
	अगर (!fcxp)
		वापस;

	len = fc_rpsc_acc_build(&fchs, bfa_fcxp_get_reqbuf(fcxp),
				rx_fchs->s_id, bfa_fcs_lport_get_fcid(port),
				rx_fchs->ox_id, &speeds);

	bfa_fcxp_send(fcxp, शून्य, port->fabric->vf_id, port->lp_tag, BFA_FALSE,
			FC_CLASS_3, len, &fchs, शून्य, शून्य, FC_MAX_PDUSZ, 0);
पूर्ण

अटल व्योम
bfa_fcs_rport_process_adisc(काष्ठा bfa_fcs_rport_s *rport,
			काष्ठा fchs_s *rx_fchs, u16 len)
अणु
	काष्ठा bfa_fcxp_s *fcxp;
	काष्ठा fchs_s	fchs;
	काष्ठा bfa_fcs_lport_s *port = rport->port;

	bfa_trc(port->fcs, rx_fchs->s_id);
	bfa_trc(port->fcs, rx_fchs->d_id);

	rport->stats.adisc_rcvd++;

	/*
	 * Accept अगर the itnim क्रम this rport is online.
	 * Else reject the ADISC.
	 */
	अगर (bfa_fcs_itnim_get_online_state(rport->itnim) == BFA_STATUS_OK) अणु

		fcxp = bfa_fcs_fcxp_alloc(port->fcs, BFA_FALSE);
		अगर (!fcxp)
			वापस;

		len = fc_adisc_acc_build(&fchs, bfa_fcxp_get_reqbuf(fcxp),
			 rx_fchs->s_id, bfa_fcs_lport_get_fcid(port),
			 rx_fchs->ox_id, port->port_cfg.pwwn,
			 port->port_cfg.nwwn);

		bfa_fcxp_send(fcxp, शून्य, port->fabric->vf_id, port->lp_tag,
				BFA_FALSE, FC_CLASS_3, len, &fchs, शून्य, शून्य,
				FC_MAX_PDUSZ, 0);
	पूर्ण अन्यथा अणु
		rport->stats.adisc_rejected++;
		bfa_fcs_rport_send_ls_rjt(rport, rx_fchs,
					  FC_LS_RJT_RSN_UNABLE_TO_PERF_CMD,
					  FC_LS_RJT_EXP_LOGIN_REQUIRED);
	पूर्ण
पूर्ण

अटल व्योम
bfa_fcs_rport_hal_online(काष्ठा bfa_fcs_rport_s *rport)
अणु
	काष्ठा bfa_fcs_lport_s *port = rport->port;
	काष्ठा bfa_rport_info_s rport_info;

	rport_info.pid = rport->pid;
	rport_info.local_pid = port->pid;
	rport_info.lp_tag = port->lp_tag;
	rport_info.vf_id = port->fabric->vf_id;
	rport_info.vf_en = port->fabric->is_vf;
	rport_info.fc_class = rport->fc_cos;
	rport_info.cisc = rport->cisc;
	rport_info.max_frmsz = rport->maxfrsize;
	bfa_rport_online(rport->bfa_rport, &rport_info);
पूर्ण

अटल व्योम
bfa_fcs_rport_hal_offline(काष्ठा bfa_fcs_rport_s *rport)
अणु
	अगर (rport->bfa_rport)
		bfa_sm_send_event(rport->bfa_rport, BFA_RPORT_SM_OFFLINE);
	अन्यथा
		bfa_cb_rport_offline(rport);
पूर्ण

अटल काष्ठा bfa_fcs_rport_s *
bfa_fcs_rport_alloc(काष्ठा bfa_fcs_lport_s *port, wwn_t pwwn, u32 rpid)
अणु
	काष्ठा bfa_fcs_s	*fcs = port->fcs;
	काष्ठा bfa_fcs_rport_s *rport;
	काष्ठा bfad_rport_s	*rport_drv;

	/*
	 * allocate rport
	 */
	अगर (fcs->num_rport_logins >= bfa_fcs_rport_max_logins) अणु
		bfa_trc(fcs, rpid);
		वापस शून्य;
	पूर्ण

	अगर (bfa_fcb_rport_alloc(fcs->bfad, &rport, &rport_drv)
		!= BFA_STATUS_OK) अणु
		bfa_trc(fcs, rpid);
		वापस शून्य;
	पूर्ण

	/*
	 * Initialize r-port
	 */
	rport->port = port;
	rport->fcs = fcs;
	rport->rp_drv = rport_drv;
	rport->pid = rpid;
	rport->pwwn = pwwn;
	rport->old_pid = 0;

	rport->bfa_rport = शून्य;

	/*
	 * allocate FC-4s
	 */
	WARN_ON(!bfa_fcs_lport_is_initiator(port));

	अगर (bfa_fcs_lport_is_initiator(port)) अणु
		rport->itnim = bfa_fcs_itnim_create(rport);
		अगर (!rport->itnim) अणु
			bfa_trc(fcs, rpid);
			kमुक्त(rport_drv);
			वापस शून्य;
		पूर्ण
	पूर्ण

	bfa_fcs_lport_add_rport(port, rport);
	fcs->num_rport_logins++;

	bfa_sm_set_state(rport, bfa_fcs_rport_sm_uninit);

	/* Initialize the Rport Features(RPF) Sub Module  */
	अगर (!BFA_FCS_PID_IS_WKA(rport->pid))
		bfa_fcs_rpf_init(rport);

	वापस rport;
पूर्ण


अटल व्योम
bfa_fcs_rport_मुक्त(काष्ठा bfa_fcs_rport_s *rport)
अणु
	काष्ठा bfa_fcs_lport_s *port = rport->port;
	काष्ठा bfa_fcs_s *fcs = port->fcs;

	/*
	 * - delete FC-4s
	 * - delete BFA rport
	 * - हटाओ from queue of rports
	 */
	rport->plogi_pending = BFA_FALSE;

	अगर (bfa_fcs_lport_is_initiator(port)) अणु
		bfa_fcs_itnim_delete(rport->itnim);
		अगर (rport->pid != 0 && !BFA_FCS_PID_IS_WKA(rport->pid))
			bfa_fcs_rpf_rport_offline(rport);
	पूर्ण

	अगर (rport->bfa_rport) अणु
		bfa_sm_send_event(rport->bfa_rport, BFA_RPORT_SM_DELETE);
		rport->bfa_rport = शून्य;
	पूर्ण

	bfa_fcs_lport_del_rport(port, rport);
	fcs->num_rport_logins--;
	kमुक्त(rport->rp_drv);
पूर्ण

अटल व्योम
bfa_fcs_rport_aen_post(काष्ठा bfa_fcs_rport_s *rport,
			क्रमागत bfa_rport_aen_event event,
			काष्ठा bfa_rport_aen_data_s *data)
अणु
	काष्ठा bfa_fcs_lport_s *port = rport->port;
	काष्ठा bfad_s *bfad = (काष्ठा bfad_s *)port->fcs->bfad;
	काष्ठा bfa_aen_entry_s  *aen_entry;

	bfad_get_aen_entry(bfad, aen_entry);
	अगर (!aen_entry)
		वापस;

	अगर (event == BFA_RPORT_AEN_QOS_PRIO)
		aen_entry->aen_data.rport.priv.qos = data->priv.qos;
	अन्यथा अगर (event == BFA_RPORT_AEN_QOS_FLOWID)
		aen_entry->aen_data.rport.priv.qos = data->priv.qos;

	aen_entry->aen_data.rport.vf_id = rport->port->fabric->vf_id;
	aen_entry->aen_data.rport.ppwwn = bfa_fcs_lport_get_pwwn(
					bfa_fcs_get_base_port(rport->fcs));
	aen_entry->aen_data.rport.lpwwn = bfa_fcs_lport_get_pwwn(rport->port);
	aen_entry->aen_data.rport.rpwwn = rport->pwwn;

	/* Send the AEN notअगरication */
	bfad_im_post_venकरोr_event(aen_entry, bfad, ++rport->fcs->fcs_aen_seq,
				  BFA_AEN_CAT_RPORT, event);
पूर्ण

अटल व्योम
bfa_fcs_rport_fcs_online_action(काष्ठा bfa_fcs_rport_s *rport)
अणु
	अगर ((!rport->pid) || (!rport->pwwn)) अणु
		bfa_trc(rport->fcs, rport->pid);
		bfa_sm_fault(rport->fcs, rport->pid);
	पूर्ण

	bfa_sm_send_event(rport->itnim, BFA_FCS_ITNIM_SM_FCS_ONLINE);
पूर्ण

अटल व्योम
bfa_fcs_rport_hal_online_action(काष्ठा bfa_fcs_rport_s *rport)
अणु
	काष्ठा bfa_fcs_lport_s *port = rport->port;
	काष्ठा bfad_s *bfad = (काष्ठा bfad_s *)port->fcs->bfad;
	अक्षर	lpwwn_buf[BFA_STRING_32];
	अक्षर	rpwwn_buf[BFA_STRING_32];

	rport->stats.onlines++;

	अगर ((!rport->pid) || (!rport->pwwn)) अणु
		bfa_trc(rport->fcs, rport->pid);
		bfa_sm_fault(rport->fcs, rport->pid);
	पूर्ण

	अगर (bfa_fcs_lport_is_initiator(port)) अणु
		bfa_fcs_itnim_brp_online(rport->itnim);
		अगर (!BFA_FCS_PID_IS_WKA(rport->pid))
			bfa_fcs_rpf_rport_online(rport);
	पूर्ण

	wwn2str(lpwwn_buf, bfa_fcs_lport_get_pwwn(port));
	wwn2str(rpwwn_buf, rport->pwwn);
	अगर (!BFA_FCS_PID_IS_WKA(rport->pid)) अणु
		BFA_LOG(KERN_INFO, bfad, bfa_log_level,
		"Remote port (WWN = %s) online for logical port (WWN = %s)\n",
		rpwwn_buf, lpwwn_buf);
		bfa_fcs_rport_aen_post(rport, BFA_RPORT_AEN_ONLINE, शून्य);
	पूर्ण
पूर्ण

अटल व्योम
bfa_fcs_rport_fcs_offline_action(काष्ठा bfa_fcs_rport_s *rport)
अणु
	अगर (!BFA_FCS_PID_IS_WKA(rport->pid))
		bfa_fcs_rpf_rport_offline(rport);

	bfa_fcs_itnim_rport_offline(rport->itnim);
पूर्ण

अटल व्योम
bfa_fcs_rport_hal_offline_action(काष्ठा bfa_fcs_rport_s *rport)
अणु
	काष्ठा bfa_fcs_lport_s *port = rport->port;
	काष्ठा bfad_s *bfad = (काष्ठा bfad_s *)port->fcs->bfad;
	अक्षर	lpwwn_buf[BFA_STRING_32];
	अक्षर	rpwwn_buf[BFA_STRING_32];

	अगर (!rport->bfa_rport) अणु
		bfa_fcs_rport_fcs_offline_action(rport);
		वापस;
	पूर्ण

	rport->stats.offlines++;

	wwn2str(lpwwn_buf, bfa_fcs_lport_get_pwwn(port));
	wwn2str(rpwwn_buf, rport->pwwn);
	अगर (!BFA_FCS_PID_IS_WKA(rport->pid)) अणु
		अगर (bfa_fcs_lport_is_online(rport->port) == BFA_TRUE) अणु
			BFA_LOG(KERN_ERR, bfad, bfa_log_level,
				"Remote port (WWN = %s) connectivity lost for "
				"logical port (WWN = %s)\n",
				rpwwn_buf, lpwwn_buf);
			bfa_fcs_rport_aen_post(rport,
				BFA_RPORT_AEN_DISCONNECT, शून्य);
		पूर्ण अन्यथा अणु
			BFA_LOG(KERN_INFO, bfad, bfa_log_level,
				"Remote port (WWN = %s) offlined by "
				"logical port (WWN = %s)\n",
				rpwwn_buf, lpwwn_buf);
			bfa_fcs_rport_aen_post(rport,
				BFA_RPORT_AEN_OFFLINE, शून्य);
		पूर्ण
	पूर्ण

	अगर (bfa_fcs_lport_is_initiator(port)) अणु
		bfa_fcs_itnim_rport_offline(rport->itnim);
		अगर (!BFA_FCS_PID_IS_WKA(rport->pid))
			bfa_fcs_rpf_rport_offline(rport);
	पूर्ण
पूर्ण

/*
 * Update rport parameters from PLOGI or PLOGI accept.
 */
अटल व्योम
bfa_fcs_rport_update(काष्ठा bfa_fcs_rport_s *rport, काष्ठा fc_logi_s *plogi)
अणु
	bfa_fcs_lport_t *port = rport->port;

	/*
	 * - port name
	 * - node name
	 */
	rport->pwwn = plogi->port_name;
	rport->nwwn = plogi->node_name;

	/*
	 * - class of service
	 */
	rport->fc_cos = 0;
	अगर (plogi->class3.class_valid)
		rport->fc_cos = FC_CLASS_3;

	अगर (plogi->class2.class_valid)
		rport->fc_cos |= FC_CLASS_2;

	/*
	 * - CISC
	 * - MAX receive frame size
	 */
	rport->cisc = plogi->csp.cisc;
	अगर (be16_to_cpu(plogi->class3.rxsz) < be16_to_cpu(plogi->csp.rxsz))
		rport->maxfrsize = be16_to_cpu(plogi->class3.rxsz);
	अन्यथा
		rport->maxfrsize = be16_to_cpu(plogi->csp.rxsz);

	bfa_trc(port->fcs, be16_to_cpu(plogi->csp.bbcred));
	bfa_trc(port->fcs, port->fabric->bb_credit);
	/*
	 * Direct Attach P2P mode :
	 * This is to handle a bug (233476) in IBM tarमाला_लो in Direct Attach
	 *  Mode. Basically, in FLOGI Accept the target would have
	 * erroneously set the BB Credit to the value used in the FLOGI
	 * sent by the HBA. It uses the correct value (its own BB credit)
	 * in PLOGI.
	 */
	अगर ((!bfa_fcs_fabric_is_चयनed(port->fabric))	 &&
		(be16_to_cpu(plogi->csp.bbcred) < port->fabric->bb_credit)) अणु

		bfa_trc(port->fcs, be16_to_cpu(plogi->csp.bbcred));
		bfa_trc(port->fcs, port->fabric->bb_credit);

		port->fabric->bb_credit = be16_to_cpu(plogi->csp.bbcred);
		bfa_fcport_set_tx_bbcredit(port->fcs->bfa,
					  port->fabric->bb_credit);
	पूर्ण

पूर्ण

/*
 *	Called to handle LOGO received from an existing remote port.
 */
अटल व्योम
bfa_fcs_rport_process_logo(काष्ठा bfa_fcs_rport_s *rport, काष्ठा fchs_s *fchs)
अणु
	rport->reply_oxid = fchs->ox_id;
	bfa_trc(rport->fcs, rport->reply_oxid);

	rport->prlo = BFA_FALSE;
	rport->stats.logo_rcvd++;
	bfa_sm_send_event(rport, RPSM_EVENT_LOGO_RCVD);
पूर्ण



/*
 *  fcs_rport_खुला FCS rport खुला पूर्णांकerfaces
 */

/*
 *	Called by bport/vport to create a remote port instance क्रम a discovered
 *	remote device.
 *
 * @param[in] port	- base port or vport
 * @param[in] rpid	- remote port ID
 *
 * @वापस None
 */
काष्ठा bfa_fcs_rport_s *
bfa_fcs_rport_create(काष्ठा bfa_fcs_lport_s *port, u32 rpid)
अणु
	काष्ठा bfa_fcs_rport_s *rport;

	bfa_trc(port->fcs, rpid);
	rport = bfa_fcs_rport_alloc(port, WWN_शून्य, rpid);
	अगर (!rport)
		वापस शून्य;

	bfa_sm_send_event(rport, RPSM_EVENT_PLOGI_SEND);
	वापस rport;
पूर्ण

/*
 * Called to create a rport क्रम which only the wwn is known.
 *
 * @param[in] port	- base port
 * @param[in] rpwwn	- remote port wwn
 *
 * @वापस None
 */
काष्ठा bfa_fcs_rport_s *
bfa_fcs_rport_create_by_wwn(काष्ठा bfa_fcs_lport_s *port, wwn_t rpwwn)
अणु
	काष्ठा bfa_fcs_rport_s *rport;
	bfa_trc(port->fcs, rpwwn);
	rport = bfa_fcs_rport_alloc(port, rpwwn, 0);
	अगर (!rport)
		वापस शून्य;

	bfa_sm_send_event(rport, RPSM_EVENT_ADDRESS_DISC);
	वापस rport;
पूर्ण
/*
 * Called by bport in निजी loop topology to indicate that a
 * rport has been discovered and plogi has been completed.
 *
 * @param[in] port	- base port or vport
 * @param[in] rpid	- remote port ID
 */
व्योम
bfa_fcs_rport_start(काष्ठा bfa_fcs_lport_s *port, काष्ठा fchs_s *fchs,
	 काष्ठा fc_logi_s *plogi)
अणु
	काष्ठा bfa_fcs_rport_s *rport;

	rport = bfa_fcs_rport_alloc(port, WWN_शून्य, fchs->s_id);
	अगर (!rport)
		वापस;

	bfa_fcs_rport_update(rport, plogi);

	bfa_sm_send_event(rport, RPSM_EVENT_PLOGI_COMP);
पूर्ण

/*
 *	Called by bport/vport to handle PLOGI received from a new remote port.
 *	If an existing rport करोes a plogi, it will be handled separately.
 */
व्योम
bfa_fcs_rport_plogi_create(काष्ठा bfa_fcs_lport_s *port, काष्ठा fchs_s *fchs,
				काष्ठा fc_logi_s *plogi)
अणु
	काष्ठा bfa_fcs_rport_s *rport;

	rport = bfa_fcs_rport_alloc(port, plogi->port_name, fchs->s_id);
	अगर (!rport)
		वापस;

	bfa_fcs_rport_update(rport, plogi);

	rport->reply_oxid = fchs->ox_id;
	bfa_trc(rport->fcs, rport->reply_oxid);

	rport->stats.plogi_rcvd++;
	bfa_sm_send_event(rport, RPSM_EVENT_PLOGI_RCVD);
पूर्ण

/*
 *	Called by bport/vport to handle PLOGI received from an existing
 *	 remote port.
 */
व्योम
bfa_fcs_rport_plogi(काष्ठा bfa_fcs_rport_s *rport, काष्ठा fchs_s *rx_fchs,
			काष्ठा fc_logi_s *plogi)
अणु
	/*
	 * @toकरो Handle P2P and initiator-initiator.
	 */

	bfa_fcs_rport_update(rport, plogi);

	rport->reply_oxid = rx_fchs->ox_id;
	bfa_trc(rport->fcs, rport->reply_oxid);

	rport->pid = rx_fchs->s_id;
	bfa_trc(rport->fcs, rport->pid);

	rport->stats.plogi_rcvd++;
	bfa_sm_send_event(rport, RPSM_EVENT_PLOGI_RCVD);
पूर्ण


/*
 *	Called by bport/vport to notअगरy SCN क्रम the remote port
 */
व्योम
bfa_fcs_rport_scn(काष्ठा bfa_fcs_rport_s *rport)
अणु
	rport->stats.rscns++;
	bfa_sm_send_event(rport, RPSM_EVENT_FAB_SCN);
पूर्ण

/*
 *	brief
 *	This routine BFA callback क्रम bfa_rport_online() call.
 *
 *	param[in]	cb_arg	-  rport काष्ठा.
 *
 *	वापस
 *		व्योम
 *
 *	Special Considerations:
 *
 *	note
 */
व्योम
bfa_cb_rport_online(व्योम *cbarg)
अणु

	काष्ठा bfa_fcs_rport_s *rport = (काष्ठा bfa_fcs_rport_s *) cbarg;

	bfa_trc(rport->fcs, rport->pwwn);
	bfa_sm_send_event(rport, RPSM_EVENT_HCB_ONLINE);
पूर्ण

/*
 *	brief
 *	This routine BFA callback क्रम bfa_rport_offline() call.
 *
 *	param[in]	rport	-
 *
 *	वापस
 *		व्योम
 *
 *	Special Considerations:
 *
 *	note
 */
व्योम
bfa_cb_rport_offline(व्योम *cbarg)
अणु
	काष्ठा bfa_fcs_rport_s *rport = (काष्ठा bfa_fcs_rport_s *) cbarg;

	bfa_trc(rport->fcs, rport->pwwn);
	bfa_sm_send_event(rport, RPSM_EVENT_HCB_OFFLINE);
पूर्ण

/*
 *	brief
 *	This routine is a अटल BFA callback when there is a QoS flow_id
 *	change notअगरication
 *
 *	param[in]	rport	-
 *
 *	वापस
 *		व्योम
 *
 *	Special Considerations:
 *
 *	note
 */
व्योम
bfa_cb_rport_qos_scn_flowid(व्योम *cbarg,
		काष्ठा bfa_rport_qos_attr_s old_qos_attr,
		काष्ठा bfa_rport_qos_attr_s new_qos_attr)
अणु
	काष्ठा bfa_fcs_rport_s *rport = (काष्ठा bfa_fcs_rport_s *) cbarg;
	काष्ठा bfa_rport_aen_data_s aen_data;

	bfa_trc(rport->fcs, rport->pwwn);
	aen_data.priv.qos = new_qos_attr;
	bfa_fcs_rport_aen_post(rport, BFA_RPORT_AEN_QOS_FLOWID, &aen_data);
पूर्ण

व्योम
bfa_cb_rport_scn_online(काष्ठा bfa_s *bfa)
अणु
	काष्ठा bfa_fcs_s *fcs = &((काष्ठा bfad_s *)bfa->bfad)->bfa_fcs;
	काष्ठा bfa_fcs_lport_s *port = bfa_fcs_get_base_port(fcs);
	काष्ठा bfa_fcs_rport_s *rp;
	काष्ठा list_head *qe;

	list_क्रम_each(qe, &port->rport_q) अणु
		rp = (काष्ठा bfa_fcs_rport_s *) qe;
		bfa_sm_send_event(rp, RPSM_EVENT_SCN_ONLINE);
		rp->scn_online = BFA_TRUE;
	पूर्ण

	अगर (bfa_fcs_lport_is_online(port))
		bfa_fcs_lport_lip_scn_online(port);
पूर्ण

व्योम
bfa_cb_rport_scn_no_dev(व्योम *rport)
अणु
	काष्ठा bfa_fcs_rport_s *rp = rport;

	bfa_sm_send_event(rp, RPSM_EVENT_SCN_OFFLINE);
	rp->scn_online = BFA_FALSE;
पूर्ण

व्योम
bfa_cb_rport_scn_offline(काष्ठा bfa_s *bfa)
अणु
	काष्ठा bfa_fcs_s *fcs = &((काष्ठा bfad_s *)bfa->bfad)->bfa_fcs;
	काष्ठा bfa_fcs_lport_s *port = bfa_fcs_get_base_port(fcs);
	काष्ठा bfa_fcs_rport_s *rp;
	काष्ठा list_head *qe;

	list_क्रम_each(qe, &port->rport_q) अणु
		rp = (काष्ठा bfa_fcs_rport_s *) qe;
		bfa_sm_send_event(rp, RPSM_EVENT_SCN_OFFLINE);
		rp->scn_online = BFA_FALSE;
	पूर्ण
पूर्ण

/*
 *	brief
 *	This routine is a अटल BFA callback when there is a QoS priority
 *	change notअगरication
 *
 *	param[in]	rport	-
 *
 *	वापस
 *		व्योम
 *
 *	Special Considerations:
 *
 *	note
 */
व्योम
bfa_cb_rport_qos_scn_prio(व्योम *cbarg,
		काष्ठा bfa_rport_qos_attr_s old_qos_attr,
		काष्ठा bfa_rport_qos_attr_s new_qos_attr)
अणु
	काष्ठा bfa_fcs_rport_s *rport = (काष्ठा bfa_fcs_rport_s *) cbarg;
	काष्ठा bfa_rport_aen_data_s aen_data;

	bfa_trc(rport->fcs, rport->pwwn);
	aen_data.priv.qos = new_qos_attr;
	bfa_fcs_rport_aen_post(rport, BFA_RPORT_AEN_QOS_PRIO, &aen_data);
पूर्ण

/*
 *		Called to process any unsolicted frames from this remote port
 */
व्योम
bfa_fcs_rport_uf_recv(काष्ठा bfa_fcs_rport_s *rport,
			काष्ठा fchs_s *fchs, u16 len)
अणु
	काष्ठा bfa_fcs_lport_s *port = rport->port;
	काष्ठा fc_els_cmd_s	*els_cmd;

	bfa_trc(rport->fcs, fchs->s_id);
	bfa_trc(rport->fcs, fchs->d_id);
	bfa_trc(rport->fcs, fchs->type);

	अगर (fchs->type != FC_TYPE_ELS)
		वापस;

	els_cmd = (काष्ठा fc_els_cmd_s *) (fchs + 1);

	bfa_trc(rport->fcs, els_cmd->els_code);

	चयन (els_cmd->els_code) अणु
	हाल FC_ELS_LOGO:
		bfa_stats(port, plogi_rcvd);
		bfa_fcs_rport_process_logo(rport, fchs);
		अवरोध;

	हाल FC_ELS_ADISC:
		bfa_stats(port, adisc_rcvd);
		bfa_fcs_rport_process_adisc(rport, fchs, len);
		अवरोध;

	हाल FC_ELS_PRLO:
		bfa_stats(port, prlo_rcvd);
		अगर (bfa_fcs_lport_is_initiator(port))
			bfa_fcs_fcpim_uf_recv(rport->itnim, fchs, len);
		अवरोध;

	हाल FC_ELS_PRLI:
		bfa_stats(port, prli_rcvd);
		bfa_fcs_rport_process_prli(rport, fchs, len);
		अवरोध;

	हाल FC_ELS_RPSC:
		bfa_stats(port, rpsc_rcvd);
		bfa_fcs_rport_process_rpsc(rport, fchs, len);
		अवरोध;

	शेष:
		bfa_stats(port, un_handled_els_rcvd);
		bfa_fcs_rport_send_ls_rjt(rport, fchs,
					  FC_LS_RJT_RSN_CMD_NOT_SUPP,
					  FC_LS_RJT_EXP_NO_ADDL_INFO);
		अवरोध;
	पूर्ण
पूर्ण

/* send best हाल  acc to prlo */
अटल व्योम
bfa_fcs_rport_send_prlo_acc(काष्ठा bfa_fcs_rport_s *rport)
अणु
	काष्ठा bfa_fcs_lport_s *port = rport->port;
	काष्ठा fchs_s	fchs;
	काष्ठा bfa_fcxp_s *fcxp;
	पूर्णांक		len;

	bfa_trc(rport->fcs, rport->pid);

	fcxp = bfa_fcs_fcxp_alloc(port->fcs, BFA_FALSE);
	अगर (!fcxp)
		वापस;
	len = fc_prlo_acc_build(&fchs, bfa_fcxp_get_reqbuf(fcxp),
			rport->pid, bfa_fcs_lport_get_fcid(port),
			rport->reply_oxid, 0);

	bfa_fcxp_send(fcxp, rport->bfa_rport, port->fabric->vf_id,
		port->lp_tag, BFA_FALSE, FC_CLASS_3, len, &fchs,
		शून्य, शून्य, FC_MAX_PDUSZ, 0);
पूर्ण

/*
 * Send a LS reject
 */
अटल व्योम
bfa_fcs_rport_send_ls_rjt(काष्ठा bfa_fcs_rport_s *rport, काष्ठा fchs_s *rx_fchs,
			  u8 reason_code, u8 reason_code_expl)
अणु
	काष्ठा bfa_fcs_lport_s *port = rport->port;
	काष्ठा fchs_s	fchs;
	काष्ठा bfa_fcxp_s *fcxp;
	पूर्णांक		len;

	bfa_trc(rport->fcs, rx_fchs->s_id);

	fcxp = bfa_fcs_fcxp_alloc(rport->fcs, BFA_FALSE);
	अगर (!fcxp)
		वापस;

	len = fc_ls_rjt_build(&fchs, bfa_fcxp_get_reqbuf(fcxp),
				rx_fchs->s_id, bfa_fcs_lport_get_fcid(port),
				rx_fchs->ox_id, reason_code, reason_code_expl);

	bfa_fcxp_send(fcxp, शून्य, port->fabric->vf_id, port->lp_tag,
			BFA_FALSE, FC_CLASS_3, len, &fchs, शून्य, शून्य,
			FC_MAX_PDUSZ, 0);
पूर्ण

/*
 * Return state of rport.
 */
पूर्णांक
bfa_fcs_rport_get_state(काष्ठा bfa_fcs_rport_s *rport)
अणु
	वापस bfa_sm_to_state(rport_sm_table, rport->sm);
पूर्ण


/*
 *	brief
 *		 Called by the Driver to set rport delete/ageout समयout
 *
 *	param[in]		rport समयout value in seconds.
 *
 *	वापस None
 */
व्योम
bfa_fcs_rport_set_del_समयout(u8 rport_पंचांगo)
अणु
	/* convert to Millisecs */
	अगर (rport_पंचांगo > 0)
		bfa_fcs_rport_del_समयout = rport_पंचांगo * 1000;
पूर्ण
व्योम
bfa_fcs_rport_prlo(काष्ठा bfa_fcs_rport_s *rport, __be16 ox_id)
अणु
	bfa_trc(rport->fcs, rport->pid);

	rport->prlo = BFA_TRUE;
	rport->reply_oxid = ox_id;
	bfa_sm_send_event(rport, RPSM_EVENT_PRLO_RCVD);
पूर्ण

/*
 * Called by BFAD to set the max limit on number of bfa_fcs_rport allocation
 * which limits number of concurrent logins to remote ports
 */
व्योम
bfa_fcs_rport_set_max_logins(u32 max_logins)
अणु
	अगर (max_logins > 0)
		bfa_fcs_rport_max_logins = max_logins;
पूर्ण

व्योम
bfa_fcs_rport_get_attr(काष्ठा bfa_fcs_rport_s *rport,
		काष्ठा bfa_rport_attr_s *rport_attr)
अणु
	काष्ठा bfa_rport_qos_attr_s qos_attr;
	काष्ठा bfa_fcs_lport_s *port = rport->port;
	bfa_port_speed_t rport_speed = rport->rpf.rpsc_speed;
	काष्ठा bfa_port_attr_s port_attr;

	bfa_fcport_get_attr(rport->fcs->bfa, &port_attr);

	स_रखो(rport_attr, 0, माप(काष्ठा bfa_rport_attr_s));
	स_रखो(&qos_attr, 0, माप(काष्ठा bfa_rport_qos_attr_s));

	rport_attr->pid = rport->pid;
	rport_attr->pwwn = rport->pwwn;
	rport_attr->nwwn = rport->nwwn;
	rport_attr->cos_supported = rport->fc_cos;
	rport_attr->df_sz = rport->maxfrsize;
	rport_attr->state = bfa_fcs_rport_get_state(rport);
	rport_attr->fc_cos = rport->fc_cos;
	rport_attr->cisc = rport->cisc;
	rport_attr->scsi_function = rport->scsi_function;
	rport_attr->curr_speed  = rport->rpf.rpsc_speed;
	rport_attr->asचिन्हित_speed  = rport->rpf.asचिन्हित_speed;

	अगर (rport->bfa_rport) अणु
		qos_attr.qos_priority = rport->bfa_rport->qos_attr.qos_priority;
		qos_attr.qos_flow_id =
			cpu_to_be32(rport->bfa_rport->qos_attr.qos_flow_id);
	पूर्ण
	rport_attr->qos_attr = qos_attr;

	rport_attr->trl_enक्रमced = BFA_FALSE;
	अगर (bfa_fcport_is_ratelim(port->fcs->bfa) &&
	    (rport->scsi_function == BFA_RPORT_TARGET)) अणु
		अगर (rport_speed == BFA_PORT_SPEED_UNKNOWN)
			rport_speed =
				bfa_fcport_get_ratelim_speed(rport->fcs->bfa);

		अगर ((bfa_fcs_lport_get_rport_max_speed(port) !=
		    BFA_PORT_SPEED_UNKNOWN) && (rport_speed < port_attr.speed))
			rport_attr->trl_enक्रमced = BFA_TRUE;
	पूर्ण
पूर्ण

/*
 * Remote port implementation.
 */

/*
 *  fcs_rport_api FCS rport API.
 */

काष्ठा bfa_fcs_rport_s *
bfa_fcs_rport_lookup(काष्ठा bfa_fcs_lport_s *port, wwn_t rpwwn)
अणु
	काष्ठा bfa_fcs_rport_s *rport;

	rport = bfa_fcs_lport_get_rport_by_pwwn(port, rpwwn);
	अगर (rport == शून्य) अणु
		/*
		 * TBD Error handling
		 */
	पूर्ण

	वापस rport;
पूर्ण

काष्ठा bfa_fcs_rport_s *
bfa_fcs_rport_lookup_by_nwwn(काष्ठा bfa_fcs_lport_s *port, wwn_t rnwwn)
अणु
	काष्ठा bfa_fcs_rport_s *rport;

	rport = bfa_fcs_lport_get_rport_by_nwwn(port, rnwwn);
	अगर (rport == शून्य) अणु
		/*
		 * TBD Error handling
		 */
	पूर्ण

	वापस rport;
पूर्ण

/*
 * Remote port features (RPF) implementation.
 */

#घोषणा BFA_FCS_RPF_RETRIES	(3)
#घोषणा BFA_FCS_RPF_RETRY_TIMEOUT  (1000) /* 1 sec (In millisecs) */

अटल व्योम     bfa_fcs_rpf_send_rpsc2(व्योम *rport_cbarg,
				काष्ठा bfa_fcxp_s *fcxp_alloced);
अटल व्योम     bfa_fcs_rpf_rpsc2_response(व्योम *fcsarg,
			काष्ठा bfa_fcxp_s *fcxp,
			व्योम *cbarg,
			bfa_status_t req_status,
			u32 rsp_len,
			u32 resid_len,
			काष्ठा fchs_s *rsp_fchs);

अटल व्योम     bfa_fcs_rpf_समयout(व्योम *arg);

/*
 *  fcs_rport_ftrs_sm FCS rport state machine events
 */

क्रमागत rpf_event अणु
	RPFSM_EVENT_RPORT_OFFLINE  = 1, /* Rport offline		*/
	RPFSM_EVENT_RPORT_ONLINE   = 2,	/* Rport online			*/
	RPFSM_EVENT_FCXP_SENT      = 3,	/* Frame from has been sent	*/
	RPFSM_EVENT_TIMEOUT	   = 4, /* Rport SM समयout event	*/
	RPFSM_EVENT_RPSC_COMP      = 5,
	RPFSM_EVENT_RPSC_FAIL      = 6,
	RPFSM_EVENT_RPSC_ERROR     = 7,
पूर्ण;

अटल व्योम	bfa_fcs_rpf_sm_uninit(काष्ठा bfa_fcs_rpf_s *rpf,
					क्रमागत rpf_event event);
अटल व्योम     bfa_fcs_rpf_sm_rpsc_sending(काष्ठा bfa_fcs_rpf_s *rpf,
				       क्रमागत rpf_event event);
अटल व्योम     bfa_fcs_rpf_sm_rpsc(काष्ठा bfa_fcs_rpf_s *rpf,
				       क्रमागत rpf_event event);
अटल व्योम	bfa_fcs_rpf_sm_rpsc_retry(काष्ठा bfa_fcs_rpf_s *rpf,
					क्रमागत rpf_event event);
अटल व्योम     bfa_fcs_rpf_sm_offline(काष्ठा bfa_fcs_rpf_s *rpf,
					क्रमागत rpf_event event);
अटल व्योम     bfa_fcs_rpf_sm_online(काष्ठा bfa_fcs_rpf_s *rpf,
					क्रमागत rpf_event event);

अटल व्योम
bfa_fcs_rpf_sm_uninit(काष्ठा bfa_fcs_rpf_s *rpf, क्रमागत rpf_event event)
अणु
	काष्ठा bfa_fcs_rport_s *rport = rpf->rport;
	काष्ठा bfa_fcs_fabric_s *fabric = &rport->fcs->fabric;

	bfa_trc(rport->fcs, rport->pwwn);
	bfa_trc(rport->fcs, rport->pid);
	bfa_trc(rport->fcs, event);

	चयन (event) अणु
	हाल RPFSM_EVENT_RPORT_ONLINE:
		/* Send RPSC2 to a Brocade fabric only. */
		अगर ((!BFA_FCS_PID_IS_WKA(rport->pid)) &&
			((rport->port->fabric->lps->brcd_चयन) ||
			(bfa_fcs_fabric_get_चयन_oui(fabric) ==
						BFA_FCS_BRCD_SWITCH_OUI))) अणु
			bfa_sm_set_state(rpf, bfa_fcs_rpf_sm_rpsc_sending);
			rpf->rpsc_retries = 0;
			bfa_fcs_rpf_send_rpsc2(rpf, शून्य);
		पूर्ण
		अवरोध;

	हाल RPFSM_EVENT_RPORT_OFFLINE:
		अवरोध;

	शेष:
		bfa_sm_fault(rport->fcs, event);
	पूर्ण
पूर्ण

अटल व्योम
bfa_fcs_rpf_sm_rpsc_sending(काष्ठा bfa_fcs_rpf_s *rpf, क्रमागत rpf_event event)
अणु
	काष्ठा bfa_fcs_rport_s *rport = rpf->rport;

	bfa_trc(rport->fcs, event);

	चयन (event) अणु
	हाल RPFSM_EVENT_FCXP_SENT:
		bfa_sm_set_state(rpf, bfa_fcs_rpf_sm_rpsc);
		अवरोध;

	हाल RPFSM_EVENT_RPORT_OFFLINE:
		bfa_sm_set_state(rpf, bfa_fcs_rpf_sm_offline);
		bfa_fcxp_walloc_cancel(rport->fcs->bfa, &rpf->fcxp_wqe);
		rpf->rpsc_retries = 0;
		अवरोध;

	शेष:
		bfa_sm_fault(rport->fcs, event);
	पूर्ण
पूर्ण

अटल व्योम
bfa_fcs_rpf_sm_rpsc(काष्ठा bfa_fcs_rpf_s *rpf, क्रमागत rpf_event event)
अणु
	काष्ठा bfa_fcs_rport_s *rport = rpf->rport;

	bfa_trc(rport->fcs, rport->pid);
	bfa_trc(rport->fcs, event);

	चयन (event) अणु
	हाल RPFSM_EVENT_RPSC_COMP:
		bfa_sm_set_state(rpf, bfa_fcs_rpf_sm_online);
		/* Update speed info in f/w via BFA */
		अगर (rpf->rpsc_speed != BFA_PORT_SPEED_UNKNOWN)
			bfa_rport_speed(rport->bfa_rport, rpf->rpsc_speed);
		अन्यथा अगर (rpf->asचिन्हित_speed != BFA_PORT_SPEED_UNKNOWN)
			bfa_rport_speed(rport->bfa_rport, rpf->asचिन्हित_speed);
		अवरोध;

	हाल RPFSM_EVENT_RPSC_FAIL:
		/* RPSC not supported by rport */
		bfa_sm_set_state(rpf, bfa_fcs_rpf_sm_online);
		अवरोध;

	हाल RPFSM_EVENT_RPSC_ERROR:
		/* need to retry...delayed a bit. */
		अगर (rpf->rpsc_retries++ < BFA_FCS_RPF_RETRIES) अणु
			bfa_समयr_start(rport->fcs->bfa, &rpf->समयr,
				    bfa_fcs_rpf_समयout, rpf,
				    BFA_FCS_RPF_RETRY_TIMEOUT);
			bfa_sm_set_state(rpf, bfa_fcs_rpf_sm_rpsc_retry);
		पूर्ण अन्यथा अणु
			bfa_sm_set_state(rpf, bfa_fcs_rpf_sm_online);
		पूर्ण
		अवरोध;

	हाल RPFSM_EVENT_RPORT_OFFLINE:
		bfa_sm_set_state(rpf, bfa_fcs_rpf_sm_offline);
		bfa_fcxp_discard(rpf->fcxp);
		rpf->rpsc_retries = 0;
		अवरोध;

	शेष:
		bfa_sm_fault(rport->fcs, event);
	पूर्ण
पूर्ण

अटल व्योम
bfa_fcs_rpf_sm_rpsc_retry(काष्ठा bfa_fcs_rpf_s *rpf, क्रमागत rpf_event event)
अणु
	काष्ठा bfa_fcs_rport_s *rport = rpf->rport;

	bfa_trc(rport->fcs, rport->pid);
	bfa_trc(rport->fcs, event);

	चयन (event) अणु
	हाल RPFSM_EVENT_TIMEOUT:
		/* re-send the RPSC */
		bfa_sm_set_state(rpf, bfa_fcs_rpf_sm_rpsc_sending);
		bfa_fcs_rpf_send_rpsc2(rpf, शून्य);
		अवरोध;

	हाल RPFSM_EVENT_RPORT_OFFLINE:
		bfa_समयr_stop(&rpf->समयr);
		bfa_sm_set_state(rpf, bfa_fcs_rpf_sm_offline);
		rpf->rpsc_retries = 0;
		अवरोध;

	शेष:
		bfa_sm_fault(rport->fcs, event);
	पूर्ण
पूर्ण

अटल व्योम
bfa_fcs_rpf_sm_online(काष्ठा bfa_fcs_rpf_s *rpf, क्रमागत rpf_event event)
अणु
	काष्ठा bfa_fcs_rport_s *rport = rpf->rport;

	bfa_trc(rport->fcs, rport->pwwn);
	bfa_trc(rport->fcs, rport->pid);
	bfa_trc(rport->fcs, event);

	चयन (event) अणु
	हाल RPFSM_EVENT_RPORT_OFFLINE:
		bfa_sm_set_state(rpf, bfa_fcs_rpf_sm_offline);
		rpf->rpsc_retries = 0;
		अवरोध;

	शेष:
		bfa_sm_fault(rport->fcs, event);
	पूर्ण
पूर्ण

अटल व्योम
bfa_fcs_rpf_sm_offline(काष्ठा bfa_fcs_rpf_s *rpf, क्रमागत rpf_event event)
अणु
	काष्ठा bfa_fcs_rport_s *rport = rpf->rport;

	bfa_trc(rport->fcs, rport->pwwn);
	bfa_trc(rport->fcs, rport->pid);
	bfa_trc(rport->fcs, event);

	चयन (event) अणु
	हाल RPFSM_EVENT_RPORT_ONLINE:
		bfa_sm_set_state(rpf, bfa_fcs_rpf_sm_rpsc_sending);
		bfa_fcs_rpf_send_rpsc2(rpf, शून्य);
		अवरोध;

	हाल RPFSM_EVENT_RPORT_OFFLINE:
		अवरोध;

	शेष:
		bfa_sm_fault(rport->fcs, event);
	पूर्ण
पूर्ण
/*
 * Called when Rport is created.
 */
व्योम
bfa_fcs_rpf_init(काष्ठा bfa_fcs_rport_s *rport)
अणु
	काष्ठा bfa_fcs_rpf_s *rpf = &rport->rpf;

	bfa_trc(rport->fcs, rport->pid);
	rpf->rport = rport;

	bfa_sm_set_state(rpf, bfa_fcs_rpf_sm_uninit);
पूर्ण

/*
 * Called when Rport becomes online
 */
व्योम
bfa_fcs_rpf_rport_online(काष्ठा bfa_fcs_rport_s *rport)
अणु
	bfa_trc(rport->fcs, rport->pid);

	अगर (__fcs_min_cfg(rport->port->fcs))
		वापस;

	अगर (bfa_fcs_fabric_is_चयनed(rport->port->fabric))
		bfa_sm_send_event(&rport->rpf, RPFSM_EVENT_RPORT_ONLINE);
पूर्ण

/*
 * Called when Rport becomes offline
 */
व्योम
bfa_fcs_rpf_rport_offline(काष्ठा bfa_fcs_rport_s *rport)
अणु
	bfa_trc(rport->fcs, rport->pid);

	अगर (__fcs_min_cfg(rport->port->fcs))
		वापस;

	rport->rpf.rpsc_speed = 0;
	bfa_sm_send_event(&rport->rpf, RPFSM_EVENT_RPORT_OFFLINE);
पूर्ण

अटल व्योम
bfa_fcs_rpf_समयout(व्योम *arg)
अणु
	काष्ठा bfa_fcs_rpf_s *rpf = (काष्ठा bfa_fcs_rpf_s *) arg;
	काष्ठा bfa_fcs_rport_s *rport = rpf->rport;

	bfa_trc(rport->fcs, rport->pid);
	bfa_sm_send_event(rpf, RPFSM_EVENT_TIMEOUT);
पूर्ण

अटल व्योम
bfa_fcs_rpf_send_rpsc2(व्योम *rpf_cbarg, काष्ठा bfa_fcxp_s *fcxp_alloced)
अणु
	काष्ठा bfa_fcs_rpf_s *rpf = (काष्ठा bfa_fcs_rpf_s *)rpf_cbarg;
	काष्ठा bfa_fcs_rport_s *rport = rpf->rport;
	काष्ठा bfa_fcs_lport_s *port = rport->port;
	काष्ठा fchs_s	fchs;
	पूर्णांक		len;
	काष्ठा bfa_fcxp_s *fcxp;

	bfa_trc(rport->fcs, rport->pwwn);

	fcxp = fcxp_alloced ? fcxp_alloced :
	       bfa_fcs_fcxp_alloc(port->fcs, BFA_TRUE);
	अगर (!fcxp) अणु
		bfa_fcs_fcxp_alloc_रुको(port->fcs->bfa, &rpf->fcxp_wqe,
				bfa_fcs_rpf_send_rpsc2, rpf, BFA_TRUE);
		वापस;
	पूर्ण
	rpf->fcxp = fcxp;

	len = fc_rpsc2_build(&fchs, bfa_fcxp_get_reqbuf(fcxp), rport->pid,
			    bfa_fcs_lport_get_fcid(port), &rport->pid, 1);

	bfa_fcxp_send(fcxp, शून्य, port->fabric->vf_id, port->lp_tag, BFA_FALSE,
			  FC_CLASS_3, len, &fchs, bfa_fcs_rpf_rpsc2_response,
			  rpf, FC_MAX_PDUSZ, FC_ELS_TOV);
	rport->stats.rpsc_sent++;
	bfa_sm_send_event(rpf, RPFSM_EVENT_FCXP_SENT);

पूर्ण

अटल व्योम
bfa_fcs_rpf_rpsc2_response(व्योम *fcsarg, काष्ठा bfa_fcxp_s *fcxp, व्योम *cbarg,
			    bfa_status_t req_status, u32 rsp_len,
			    u32 resid_len, काष्ठा fchs_s *rsp_fchs)
अणु
	काष्ठा bfa_fcs_rpf_s *rpf = (काष्ठा bfa_fcs_rpf_s *) cbarg;
	काष्ठा bfa_fcs_rport_s *rport = rpf->rport;
	काष्ठा fc_ls_rjt_s *ls_rjt;
	काष्ठा fc_rpsc2_acc_s *rpsc2_acc;
	u16	num_ents;

	bfa_trc(rport->fcs, req_status);

	अगर (req_status != BFA_STATUS_OK) अणु
		bfa_trc(rport->fcs, req_status);
		अगर (req_status == BFA_STATUS_ETIMER)
			rport->stats.rpsc_failed++;
		bfa_sm_send_event(rpf, RPFSM_EVENT_RPSC_ERROR);
		वापस;
	पूर्ण

	rpsc2_acc = (काष्ठा fc_rpsc2_acc_s *) BFA_FCXP_RSP_PLD(fcxp);
	अगर (rpsc2_acc->els_cmd == FC_ELS_ACC) अणु
		rport->stats.rpsc_accs++;
		num_ents = be16_to_cpu(rpsc2_acc->num_pids);
		bfa_trc(rport->fcs, num_ents);
		अगर (num_ents > 0) अणु
			WARN_ON(be32_to_cpu(rpsc2_acc->port_info[0].pid) !=
						bfa_ntoh3b(rport->pid));
			bfa_trc(rport->fcs,
				be32_to_cpu(rpsc2_acc->port_info[0].pid));
			bfa_trc(rport->fcs,
				be16_to_cpu(rpsc2_acc->port_info[0].speed));
			bfa_trc(rport->fcs,
				be16_to_cpu(rpsc2_acc->port_info[0].index));
			bfa_trc(rport->fcs,
				rpsc2_acc->port_info[0].type);

			अगर (rpsc2_acc->port_info[0].speed == 0) अणु
				bfa_sm_send_event(rpf, RPFSM_EVENT_RPSC_ERROR);
				वापस;
			पूर्ण

			rpf->rpsc_speed = fc_rpsc_operspeed_to_bfa_speed(
				be16_to_cpu(rpsc2_acc->port_info[0].speed));

			bfa_sm_send_event(rpf, RPFSM_EVENT_RPSC_COMP);
		पूर्ण
	पूर्ण अन्यथा अणु
		ls_rjt = (काष्ठा fc_ls_rjt_s *) BFA_FCXP_RSP_PLD(fcxp);
		bfa_trc(rport->fcs, ls_rjt->reason_code);
		bfa_trc(rport->fcs, ls_rjt->reason_code_expl);
		rport->stats.rpsc_rejects++;
		अगर (ls_rjt->reason_code == FC_LS_RJT_RSN_CMD_NOT_SUPP)
			bfa_sm_send_event(rpf, RPFSM_EVENT_RPSC_FAIL);
		अन्यथा
			bfa_sm_send_event(rpf, RPFSM_EVENT_RPSC_ERROR);
	पूर्ण
पूर्ण
