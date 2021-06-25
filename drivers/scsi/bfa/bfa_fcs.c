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
 *  bfa_fcs.c BFA FCS मुख्य
 */

#समावेश "bfad_drv.h"
#समावेश "bfad_im.h"
#समावेश "bfa_fcs.h"
#समावेश "bfa_fcbuild.h"

BFA_TRC_खाता(FCS, FCS);

/*
 *  fcs_api BFA FCS API
 */

अटल व्योम
bfa_fcs_निकास_comp(व्योम *fcs_cbarg)
अणु
	काष्ठा bfa_fcs_s      *fcs = fcs_cbarg;
	काष्ठा bfad_s         *bfad = fcs->bfad;

	complete(&bfad->comp);
पूर्ण

/*
 * fcs initialization, called once after bfa initialization is complete
 */
व्योम
bfa_fcs_init(काष्ठा bfa_fcs_s *fcs)
अणु
	bfa_sm_send_event(&fcs->fabric, BFA_FCS_FABRIC_SM_CREATE);
	bfa_trc(fcs, 0);
पूर्ण

/*
 *  fcs_api BFA FCS API
 */

/*
 * FCS update cfg - reset the pwwn/nwwn of fabric base logical port
 * with values learned during bfa_init firmware GETATTR REQ.
 */
व्योम
bfa_fcs_update_cfg(काष्ठा bfa_fcs_s *fcs)
अणु
	काष्ठा bfa_fcs_fabric_s *fabric = &fcs->fabric;
	काष्ठा bfa_lport_cfg_s *port_cfg = &fabric->bport.port_cfg;
	काष्ठा bfa_ioc_s *ioc = &fabric->fcs->bfa->ioc;

	port_cfg->nwwn = ioc->attr->nwwn;
	port_cfg->pwwn = ioc->attr->pwwn;
पूर्ण

/*
 * Stop FCS operations.
 */
व्योम
bfa_fcs_stop(काष्ठा bfa_fcs_s *fcs)
अणु
	bfa_wc_init(&fcs->wc, bfa_fcs_निकास_comp, fcs);
	bfa_wc_up(&fcs->wc);
	bfa_fcs_fabric_modstop(fcs);
	bfa_wc_रुको(&fcs->wc);
पूर्ण

/*
 * fcs pbc vport initialization
 */
व्योम
bfa_fcs_pbc_vport_init(काष्ठा bfa_fcs_s *fcs)
अणु
	पूर्णांक i, npbc_vports;
	काष्ठा bfi_pbc_vport_s pbc_vports[BFI_PBC_MAX_VPORTS];

	/* Initialize pbc vports */
	अगर (!fcs->min_cfg) अणु
		npbc_vports =
			bfa_iocfc_get_pbc_vports(fcs->bfa, pbc_vports);
		क्रम (i = 0; i < npbc_vports; i++)
			bfa_fcb_pbc_vport_create(fcs->bfa->bfad, pbc_vports[i]);
	पूर्ण
पूर्ण

/*
 *	brief
 *		FCS driver details initialization.
 *
 *	param[in]		fcs		FCS instance
 *	param[in]		driver_info	Driver Details
 *
 *	वापस None
 */
व्योम
bfa_fcs_driver_info_init(काष्ठा bfa_fcs_s *fcs,
			काष्ठा bfa_fcs_driver_info_s *driver_info)
अणु

	fcs->driver_info = *driver_info;

	bfa_fcs_fabric_psymb_init(&fcs->fabric);
	bfa_fcs_fabric_nsymb_init(&fcs->fabric);
पूर्ण

/*
 *	brief
 *		FCS instance cleanup and निकास.
 *
 *	param[in]		fcs			FCS instance
 *	वापस None
 */
व्योम
bfa_fcs_निकास(काष्ठा bfa_fcs_s *fcs)
अणु
	bfa_wc_init(&fcs->wc, bfa_fcs_निकास_comp, fcs);
	bfa_wc_up(&fcs->wc);
	bfa_trc(fcs, 0);
	bfa_lps_delete(fcs->fabric.lps);
	bfa_sm_send_event(&fcs->fabric, BFA_FCS_FABRIC_SM_DELETE);
	bfa_wc_रुको(&fcs->wc);
पूर्ण

/*
 * Fabric module implementation.
 */

#घोषणा BFA_FCS_FABRIC_RETRY_DELAY	(2000)	/* Milliseconds */
#घोषणा BFA_FCS_FABRIC_CLEANUP_DELAY	(10000)	/* Milliseconds */

#घोषणा bfa_fcs_fabric_set_opertype(__fabric) करो अणु			\
	अगर (bfa_fcport_get_topology((__fabric)->fcs->bfa)		\
				== BFA_PORT_TOPOLOGY_P2P) अणु		\
		अगर (fabric->fab_type == BFA_FCS_FABRIC_SWITCHED)	\
			(__fabric)->oper_type = BFA_PORT_TYPE_NPORT;	\
		अन्यथा							\
			(__fabric)->oper_type = BFA_PORT_TYPE_P2P;	\
	पूर्ण अन्यथा								\
		(__fabric)->oper_type = BFA_PORT_TYPE_NLPORT;		\
पूर्ण जबतक (0)

/*
 * क्रमward declarations
 */
अटल व्योम bfa_fcs_fabric_init(काष्ठा bfa_fcs_fabric_s *fabric);
अटल व्योम bfa_fcs_fabric_login(काष्ठा bfa_fcs_fabric_s *fabric);
अटल व्योम bfa_fcs_fabric_notअगरy_online(काष्ठा bfa_fcs_fabric_s *fabric);
अटल व्योम bfa_fcs_fabric_notअगरy_offline(काष्ठा bfa_fcs_fabric_s *fabric);
अटल व्योम bfa_fcs_fabric_delay(व्योम *cbarg);
अटल व्योम bfa_fcs_fabric_delete(काष्ठा bfa_fcs_fabric_s *fabric);
अटल व्योम bfa_fcs_fabric_delete_comp(व्योम *cbarg);
अटल व्योम bfa_fcs_fabric_stop(काष्ठा bfa_fcs_fabric_s *fabric);
अटल व्योम bfa_fcs_fabric_stop_comp(व्योम *cbarg);
अटल व्योम bfa_fcs_fabric_process_uf(काष्ठा bfa_fcs_fabric_s *fabric,
				      काष्ठा fchs_s *fchs, u16 len);
अटल व्योम bfa_fcs_fabric_process_flogi(काष्ठा bfa_fcs_fabric_s *fabric,
					 काष्ठा fchs_s *fchs, u16 len);
अटल व्योम bfa_fcs_fabric_send_flogi_acc(काष्ठा bfa_fcs_fabric_s *fabric);
अटल व्योम bfa_fcs_fabric_flogiacc_comp(व्योम *fcsarg,
					 काष्ठा bfa_fcxp_s *fcxp, व्योम *cbarg,
					 bfa_status_t status,
					 u32 rsp_len,
					 u32 resid_len,
					 काष्ठा fchs_s *rspfchs);

अटल व्योम	bfa_fcs_fabric_sm_uninit(काष्ठा bfa_fcs_fabric_s *fabric,
					 क्रमागत bfa_fcs_fabric_event event);
अटल व्योम	bfa_fcs_fabric_sm_created(काष्ठा bfa_fcs_fabric_s *fabric,
					  क्रमागत bfa_fcs_fabric_event event);
अटल व्योम	bfa_fcs_fabric_sm_linkकरोwn(काष्ठा bfa_fcs_fabric_s *fabric,
					   क्रमागत bfa_fcs_fabric_event event);
अटल व्योम	bfa_fcs_fabric_sm_flogi(काष्ठा bfa_fcs_fabric_s *fabric,
					क्रमागत bfa_fcs_fabric_event event);
अटल व्योम	bfa_fcs_fabric_sm_flogi_retry(काष्ठा bfa_fcs_fabric_s *fabric,
					      क्रमागत bfa_fcs_fabric_event event);
अटल व्योम	bfa_fcs_fabric_sm_auth(काष्ठा bfa_fcs_fabric_s *fabric,
				       क्रमागत bfa_fcs_fabric_event event);
अटल व्योम	bfa_fcs_fabric_sm_nofabric(काष्ठा bfa_fcs_fabric_s *fabric,
					   क्रमागत bfa_fcs_fabric_event event);
अटल व्योम	bfa_fcs_fabric_sm_evfp(काष्ठा bfa_fcs_fabric_s *fabric,
				       क्रमागत bfa_fcs_fabric_event event);
अटल व्योम	bfa_fcs_fabric_sm_evfp_करोne(काष्ठा bfa_fcs_fabric_s *fabric,
					    क्रमागत bfa_fcs_fabric_event event);
अटल व्योम	bfa_fcs_fabric_sm_isolated(काष्ठा bfa_fcs_fabric_s *fabric,
					   क्रमागत bfa_fcs_fabric_event event);
अटल व्योम	bfa_fcs_fabric_sm_deleting(काष्ठा bfa_fcs_fabric_s *fabric,
					   क्रमागत bfa_fcs_fabric_event event);
अटल व्योम	bfa_fcs_fabric_sm_stopping(काष्ठा bfa_fcs_fabric_s *fabric,
					   क्रमागत bfa_fcs_fabric_event event);
अटल व्योम	bfa_fcs_fabric_sm_cleanup(काष्ठा bfa_fcs_fabric_s *fabric,
					  क्रमागत bfa_fcs_fabric_event event);
/*
 *   Beginning state beक्रमe fabric creation.
 */
अटल व्योम
bfa_fcs_fabric_sm_uninit(काष्ठा bfa_fcs_fabric_s *fabric,
			 क्रमागत bfa_fcs_fabric_event event)
अणु
	bfa_trc(fabric->fcs, fabric->bport.port_cfg.pwwn);
	bfa_trc(fabric->fcs, event);

	चयन (event) अणु
	हाल BFA_FCS_FABRIC_SM_CREATE:
		bfa_sm_set_state(fabric, bfa_fcs_fabric_sm_created);
		bfa_fcs_fabric_init(fabric);
		bfa_fcs_lport_init(&fabric->bport, &fabric->bport.port_cfg);
		अवरोध;

	हाल BFA_FCS_FABRIC_SM_LINK_UP:
	हाल BFA_FCS_FABRIC_SM_LINK_DOWN:
		अवरोध;

	शेष:
		bfa_sm_fault(fabric->fcs, event);
	पूर्ण
पूर्ण

/*
 *   Beginning state beक्रमe fabric creation.
 */
अटल व्योम
bfa_fcs_fabric_sm_created(काष्ठा bfa_fcs_fabric_s *fabric,
			  क्रमागत bfa_fcs_fabric_event event)
अणु
	काष्ठा bfa_s	*bfa = fabric->fcs->bfa;

	bfa_trc(fabric->fcs, fabric->bport.port_cfg.pwwn);
	bfa_trc(fabric->fcs, event);

	चयन (event) अणु
	हाल BFA_FCS_FABRIC_SM_START:
		अगर (!bfa_fcport_is_linkup(fabric->fcs->bfa)) अणु
			bfa_sm_set_state(fabric, bfa_fcs_fabric_sm_linkकरोwn);
			अवरोध;
		पूर्ण
		अगर (bfa_fcport_get_topology(bfa) ==
				BFA_PORT_TOPOLOGY_LOOP) अणु
			fabric->fab_type = BFA_FCS_FABRIC_LOOP;
			fabric->bport.pid = bfa_fcport_get_myalpa(bfa);
			fabric->bport.pid = bfa_hton3b(fabric->bport.pid);
			bfa_sm_set_state(fabric,
					bfa_fcs_fabric_sm_online);
			bfa_fcs_fabric_set_opertype(fabric);
			bfa_fcs_lport_online(&fabric->bport);
		पूर्ण अन्यथा अणु
			bfa_sm_set_state(fabric, bfa_fcs_fabric_sm_flogi);
			bfa_fcs_fabric_login(fabric);
		पूर्ण
		अवरोध;

	हाल BFA_FCS_FABRIC_SM_LINK_UP:
	हाल BFA_FCS_FABRIC_SM_LINK_DOWN:
		अवरोध;

	हाल BFA_FCS_FABRIC_SM_DELETE:
		bfa_sm_set_state(fabric, bfa_fcs_fabric_sm_deleting);
		bfa_fcs_fabric_delete(fabric);
		अवरोध;

	शेष:
		bfa_sm_fault(fabric->fcs, event);
	पूर्ण
पूर्ण

/*
 *   Link is करोwn, aरुकोing LINK UP event from port. This is also the
 *   first state at fabric creation.
 */
अटल व्योम
bfa_fcs_fabric_sm_linkकरोwn(काष्ठा bfa_fcs_fabric_s *fabric,
			   क्रमागत bfa_fcs_fabric_event event)
अणु
	काष्ठा bfa_s	*bfa = fabric->fcs->bfa;

	bfa_trc(fabric->fcs, fabric->bport.port_cfg.pwwn);
	bfa_trc(fabric->fcs, event);

	चयन (event) अणु
	हाल BFA_FCS_FABRIC_SM_LINK_UP:
		अगर (bfa_fcport_get_topology(bfa) != BFA_PORT_TOPOLOGY_LOOP) अणु
			bfa_sm_set_state(fabric, bfa_fcs_fabric_sm_flogi);
			bfa_fcs_fabric_login(fabric);
			अवरोध;
		पूर्ण
		fabric->fab_type = BFA_FCS_FABRIC_LOOP;
		fabric->bport.pid = bfa_fcport_get_myalpa(bfa);
		fabric->bport.pid = bfa_hton3b(fabric->bport.pid);
		bfa_sm_set_state(fabric, bfa_fcs_fabric_sm_online);
		bfa_fcs_fabric_set_opertype(fabric);
		bfa_fcs_lport_online(&fabric->bport);
		अवरोध;

	हाल BFA_FCS_FABRIC_SM_RETRY_OP:
	हाल BFA_FCS_FABRIC_SM_LOOPBACK:
		अवरोध;

	हाल BFA_FCS_FABRIC_SM_DELETE:
		bfa_sm_set_state(fabric, bfa_fcs_fabric_sm_deleting);
		bfa_fcs_fabric_delete(fabric);
		अवरोध;

	हाल BFA_FCS_FABRIC_SM_STOP:
		bfa_sm_set_state(fabric, bfa_fcs_fabric_sm_cleanup);
		bfa_fcs_fabric_stop(fabric);
		अवरोध;

	शेष:
		bfa_sm_fault(fabric->fcs, event);
	पूर्ण
पूर्ण

/*
 *   FLOGI is in progress, aरुकोing FLOGI reply.
 */
अटल व्योम
bfa_fcs_fabric_sm_flogi(काष्ठा bfa_fcs_fabric_s *fabric,
			क्रमागत bfa_fcs_fabric_event event)
अणु
	bfa_trc(fabric->fcs, fabric->bport.port_cfg.pwwn);
	bfa_trc(fabric->fcs, event);

	चयन (event) अणु
	हाल BFA_FCS_FABRIC_SM_CONT_OP:

		bfa_fcport_set_tx_bbcredit(fabric->fcs->bfa,
					   fabric->bb_credit);
		fabric->fab_type = BFA_FCS_FABRIC_SWITCHED;

		अगर (fabric->auth_reqd && fabric->is_auth) अणु
			bfa_sm_set_state(fabric, bfa_fcs_fabric_sm_auth);
			bfa_trc(fabric->fcs, event);
		पूर्ण अन्यथा अणु
			bfa_sm_set_state(fabric, bfa_fcs_fabric_sm_online);
			bfa_fcs_fabric_notअगरy_online(fabric);
		पूर्ण
		अवरोध;

	हाल BFA_FCS_FABRIC_SM_RETRY_OP:
		bfa_sm_set_state(fabric, bfa_fcs_fabric_sm_flogi_retry);
		bfa_समयr_start(fabric->fcs->bfa, &fabric->delay_समयr,
				bfa_fcs_fabric_delay, fabric,
				BFA_FCS_FABRIC_RETRY_DELAY);
		अवरोध;

	हाल BFA_FCS_FABRIC_SM_LOOPBACK:
		bfa_sm_set_state(fabric, bfa_fcs_fabric_sm_loopback);
		bfa_sm_send_event(fabric->lps, BFA_LPS_SM_OFFLINE);
		bfa_fcs_fabric_set_opertype(fabric);
		अवरोध;

	हाल BFA_FCS_FABRIC_SM_NO_FABRIC:
		fabric->fab_type = BFA_FCS_FABRIC_N2N;
		bfa_fcport_set_tx_bbcredit(fabric->fcs->bfa,
					   fabric->bb_credit);
		bfa_fcs_fabric_notअगरy_online(fabric);
		bfa_sm_set_state(fabric, bfa_fcs_fabric_sm_nofabric);
		अवरोध;

	हाल BFA_FCS_FABRIC_SM_LINK_DOWN:
		bfa_sm_set_state(fabric, bfa_fcs_fabric_sm_linkकरोwn);
		bfa_sm_send_event(fabric->lps, BFA_LPS_SM_OFFLINE);
		अवरोध;

	हाल BFA_FCS_FABRIC_SM_DELETE:
		bfa_sm_set_state(fabric, bfa_fcs_fabric_sm_deleting);
		bfa_sm_send_event(fabric->lps, BFA_LPS_SM_OFFLINE);
		bfa_fcs_fabric_delete(fabric);
		अवरोध;

	शेष:
		bfa_sm_fault(fabric->fcs, event);
	पूर्ण
पूर्ण


अटल व्योम
bfa_fcs_fabric_sm_flogi_retry(काष्ठा bfa_fcs_fabric_s *fabric,
			      क्रमागत bfa_fcs_fabric_event event)
अणु
	bfa_trc(fabric->fcs, fabric->bport.port_cfg.pwwn);
	bfa_trc(fabric->fcs, event);

	चयन (event) अणु
	हाल BFA_FCS_FABRIC_SM_DELAYED:
		bfa_sm_set_state(fabric, bfa_fcs_fabric_sm_flogi);
		bfa_fcs_fabric_login(fabric);
		अवरोध;

	हाल BFA_FCS_FABRIC_SM_LINK_DOWN:
		bfa_sm_set_state(fabric, bfa_fcs_fabric_sm_linkकरोwn);
		bfa_समयr_stop(&fabric->delay_समयr);
		अवरोध;

	हाल BFA_FCS_FABRIC_SM_DELETE:
		bfa_sm_set_state(fabric, bfa_fcs_fabric_sm_deleting);
		bfa_समयr_stop(&fabric->delay_समयr);
		bfa_fcs_fabric_delete(fabric);
		अवरोध;

	शेष:
		bfa_sm_fault(fabric->fcs, event);
	पूर्ण
पूर्ण

/*
 *   Authentication is in progress, aरुकोing authentication results.
 */
अटल व्योम
bfa_fcs_fabric_sm_auth(काष्ठा bfa_fcs_fabric_s *fabric,
		       क्रमागत bfa_fcs_fabric_event event)
अणु
	bfa_trc(fabric->fcs, fabric->bport.port_cfg.pwwn);
	bfa_trc(fabric->fcs, event);

	चयन (event) अणु
	हाल BFA_FCS_FABRIC_SM_AUTH_FAILED:
		bfa_sm_set_state(fabric, bfa_fcs_fabric_sm_auth_failed);
		bfa_sm_send_event(fabric->lps, BFA_LPS_SM_OFFLINE);
		अवरोध;

	हाल BFA_FCS_FABRIC_SM_AUTH_SUCCESS:
		bfa_sm_set_state(fabric, bfa_fcs_fabric_sm_online);
		bfa_fcs_fabric_notअगरy_online(fabric);
		अवरोध;

	हाल BFA_FCS_FABRIC_SM_PERF_EVFP:
		bfa_sm_set_state(fabric, bfa_fcs_fabric_sm_evfp);
		अवरोध;

	हाल BFA_FCS_FABRIC_SM_LINK_DOWN:
		bfa_sm_set_state(fabric, bfa_fcs_fabric_sm_linkकरोwn);
		bfa_sm_send_event(fabric->lps, BFA_LPS_SM_OFFLINE);
		अवरोध;

	हाल BFA_FCS_FABRIC_SM_DELETE:
		bfa_sm_set_state(fabric, bfa_fcs_fabric_sm_deleting);
		bfa_fcs_fabric_delete(fabric);
		अवरोध;

	शेष:
		bfa_sm_fault(fabric->fcs, event);
	पूर्ण
पूर्ण

/*
 *   Authentication failed
 */
व्योम
bfa_fcs_fabric_sm_auth_failed(काष्ठा bfa_fcs_fabric_s *fabric,
			      क्रमागत bfa_fcs_fabric_event event)
अणु
	bfa_trc(fabric->fcs, fabric->bport.port_cfg.pwwn);
	bfa_trc(fabric->fcs, event);

	चयन (event) अणु
	हाल BFA_FCS_FABRIC_SM_LINK_DOWN:
		bfa_sm_set_state(fabric, bfa_fcs_fabric_sm_linkकरोwn);
		bfa_fcs_fabric_notअगरy_offline(fabric);
		अवरोध;

	हाल BFA_FCS_FABRIC_SM_DELETE:
		bfa_sm_set_state(fabric, bfa_fcs_fabric_sm_deleting);
		bfa_fcs_fabric_delete(fabric);
		अवरोध;

	शेष:
		bfa_sm_fault(fabric->fcs, event);
	पूर्ण
पूर्ण

/*
 *   Port is in loopback mode.
 */
व्योम
bfa_fcs_fabric_sm_loopback(काष्ठा bfa_fcs_fabric_s *fabric,
			   क्रमागत bfa_fcs_fabric_event event)
अणु
	bfa_trc(fabric->fcs, fabric->bport.port_cfg.pwwn);
	bfa_trc(fabric->fcs, event);

	चयन (event) अणु
	हाल BFA_FCS_FABRIC_SM_LINK_DOWN:
		bfa_sm_set_state(fabric, bfa_fcs_fabric_sm_linkकरोwn);
		bfa_fcs_fabric_notअगरy_offline(fabric);
		अवरोध;

	हाल BFA_FCS_FABRIC_SM_DELETE:
		bfa_sm_set_state(fabric, bfa_fcs_fabric_sm_deleting);
		bfa_fcs_fabric_delete(fabric);
		अवरोध;

	शेष:
		bfa_sm_fault(fabric->fcs, event);
	पूर्ण
पूर्ण

/*
 *   There is no attached fabric - निजी loop or NPort-to-NPort topology.
 */
अटल व्योम
bfa_fcs_fabric_sm_nofabric(काष्ठा bfa_fcs_fabric_s *fabric,
			   क्रमागत bfa_fcs_fabric_event event)
अणु
	bfa_trc(fabric->fcs, fabric->bport.port_cfg.pwwn);
	bfa_trc(fabric->fcs, event);

	चयन (event) अणु
	हाल BFA_FCS_FABRIC_SM_LINK_DOWN:
		bfa_sm_set_state(fabric, bfa_fcs_fabric_sm_linkकरोwn);
		bfa_sm_send_event(fabric->lps, BFA_LPS_SM_OFFLINE);
		bfa_fcs_fabric_notअगरy_offline(fabric);
		अवरोध;

	हाल BFA_FCS_FABRIC_SM_DELETE:
		bfa_sm_set_state(fabric, bfa_fcs_fabric_sm_deleting);
		bfa_fcs_fabric_delete(fabric);
		अवरोध;

	हाल BFA_FCS_FABRIC_SM_NO_FABRIC:
		bfa_trc(fabric->fcs, fabric->bb_credit);
		bfa_fcport_set_tx_bbcredit(fabric->fcs->bfa,
					   fabric->bb_credit);
		अवरोध;

	हाल BFA_FCS_FABRIC_SM_RETRY_OP:
		अवरोध;

	शेष:
		bfa_sm_fault(fabric->fcs, event);
	पूर्ण
पूर्ण

/*
 *   Fabric is online - normal operating state.
 */
व्योम
bfa_fcs_fabric_sm_online(काष्ठा bfa_fcs_fabric_s *fabric,
			 क्रमागत bfa_fcs_fabric_event event)
अणु
	काष्ठा bfa_s	*bfa = fabric->fcs->bfa;

	bfa_trc(fabric->fcs, fabric->bport.port_cfg.pwwn);
	bfa_trc(fabric->fcs, event);

	चयन (event) अणु
	हाल BFA_FCS_FABRIC_SM_LINK_DOWN:
		bfa_sm_set_state(fabric, bfa_fcs_fabric_sm_linkकरोwn);
		अगर (bfa_fcport_get_topology(bfa) == BFA_PORT_TOPOLOGY_LOOP) अणु
			bfa_fcs_lport_offline(&fabric->bport);
		पूर्ण अन्यथा अणु
			bfa_sm_send_event(fabric->lps, BFA_LPS_SM_OFFLINE);
			bfa_fcs_fabric_notअगरy_offline(fabric);
		पूर्ण
		अवरोध;

	हाल BFA_FCS_FABRIC_SM_DELETE:
		bfa_sm_set_state(fabric, bfa_fcs_fabric_sm_deleting);
		bfa_fcs_fabric_delete(fabric);
		अवरोध;

	हाल BFA_FCS_FABRIC_SM_STOP:
		bfa_sm_set_state(fabric, bfa_fcs_fabric_sm_stopping);
		bfa_fcs_fabric_stop(fabric);
		अवरोध;

	हाल BFA_FCS_FABRIC_SM_AUTH_FAILED:
		bfa_sm_set_state(fabric, bfa_fcs_fabric_sm_auth_failed);
		bfa_sm_send_event(fabric->lps, BFA_LPS_SM_OFFLINE);
		अवरोध;

	हाल BFA_FCS_FABRIC_SM_AUTH_SUCCESS:
		अवरोध;

	शेष:
		bfa_sm_fault(fabric->fcs, event);
	पूर्ण
पूर्ण

/*
 *   Exchanging भव fabric parameters.
 */
अटल व्योम
bfa_fcs_fabric_sm_evfp(काष्ठा bfa_fcs_fabric_s *fabric,
		       क्रमागत bfa_fcs_fabric_event event)
अणु
	bfa_trc(fabric->fcs, fabric->bport.port_cfg.pwwn);
	bfa_trc(fabric->fcs, event);

	चयन (event) अणु
	हाल BFA_FCS_FABRIC_SM_CONT_OP:
		bfa_sm_set_state(fabric, bfa_fcs_fabric_sm_evfp_करोne);
		अवरोध;

	हाल BFA_FCS_FABRIC_SM_ISOLATE:
		bfa_sm_set_state(fabric, bfa_fcs_fabric_sm_isolated);
		अवरोध;

	शेष:
		bfa_sm_fault(fabric->fcs, event);
	पूर्ण
पूर्ण

/*
 *   EVFP exchange complete and VFT tagging is enabled.
 */
अटल व्योम
bfa_fcs_fabric_sm_evfp_करोne(काष्ठा bfa_fcs_fabric_s *fabric,
			    क्रमागत bfa_fcs_fabric_event event)
अणु
	bfa_trc(fabric->fcs, fabric->bport.port_cfg.pwwn);
	bfa_trc(fabric->fcs, event);
पूर्ण

/*
 *   Port is isolated after EVFP exchange due to VF_ID mismatch (N and F).
 */
अटल व्योम
bfa_fcs_fabric_sm_isolated(काष्ठा bfa_fcs_fabric_s *fabric,
			   क्रमागत bfa_fcs_fabric_event event)
अणु
	काष्ठा bfad_s *bfad = (काष्ठा bfad_s *)fabric->fcs->bfad;
	अक्षर	pwwn_ptr[BFA_STRING_32];

	bfa_trc(fabric->fcs, fabric->bport.port_cfg.pwwn);
	bfa_trc(fabric->fcs, event);
	wwn2str(pwwn_ptr, fabric->bport.port_cfg.pwwn);

	BFA_LOG(KERN_INFO, bfad, bfa_log_level,
		"Port is isolated due to VF_ID mismatch. "
		"PWWN: %s Port VF_ID: %04x switch port VF_ID: %04x.",
		pwwn_ptr, fabric->fcs->port_vfid,
		fabric->event_arg.swp_vfid);
पूर्ण

/*
 *   Fabric is being deleted, aरुकोing vport delete completions.
 */
अटल व्योम
bfa_fcs_fabric_sm_deleting(काष्ठा bfa_fcs_fabric_s *fabric,
			   क्रमागत bfa_fcs_fabric_event event)
अणु
	bfa_trc(fabric->fcs, fabric->bport.port_cfg.pwwn);
	bfa_trc(fabric->fcs, event);

	चयन (event) अणु
	हाल BFA_FCS_FABRIC_SM_DELCOMP:
		bfa_sm_set_state(fabric, bfa_fcs_fabric_sm_uninit);
		bfa_wc_करोwn(&fabric->fcs->wc);
		अवरोध;

	हाल BFA_FCS_FABRIC_SM_LINK_UP:
		अवरोध;

	हाल BFA_FCS_FABRIC_SM_LINK_DOWN:
		bfa_fcs_fabric_notअगरy_offline(fabric);
		अवरोध;

	शेष:
		bfa_sm_fault(fabric->fcs, event);
	पूर्ण
पूर्ण

/*
 * Fabric is being stopped, aरुकोing vport stop completions.
 */
अटल व्योम
bfa_fcs_fabric_sm_stopping(काष्ठा bfa_fcs_fabric_s *fabric,
			   क्रमागत bfa_fcs_fabric_event event)
अणु
	काष्ठा bfa_s	*bfa = fabric->fcs->bfa;

	bfa_trc(fabric->fcs, fabric->bport.port_cfg.pwwn);
	bfa_trc(fabric->fcs, event);

	चयन (event) अणु
	हाल BFA_FCS_FABRIC_SM_STOPCOMP:
		अगर (bfa_fcport_get_topology(bfa) == BFA_PORT_TOPOLOGY_LOOP) अणु
			bfa_sm_set_state(fabric, bfa_fcs_fabric_sm_created);
		पूर्ण अन्यथा अणु
			bfa_sm_set_state(fabric, bfa_fcs_fabric_sm_cleanup);
			bfa_sm_send_event(fabric->lps, BFA_LPS_SM_LOGOUT);
		पूर्ण
		अवरोध;

	हाल BFA_FCS_FABRIC_SM_LINK_UP:
		अवरोध;

	हाल BFA_FCS_FABRIC_SM_LINK_DOWN:
		अगर (bfa_fcport_get_topology(bfa) == BFA_PORT_TOPOLOGY_LOOP)
			bfa_sm_set_state(fabric, bfa_fcs_fabric_sm_created);
		अन्यथा
			bfa_sm_set_state(fabric, bfa_fcs_fabric_sm_cleanup);
		अवरोध;

	शेष:
		bfa_sm_fault(fabric->fcs, event);
	पूर्ण
पूर्ण

/*
 * Fabric is being stopped, cleanup without FLOGO
 */
अटल व्योम
bfa_fcs_fabric_sm_cleanup(काष्ठा bfa_fcs_fabric_s *fabric,
			  क्रमागत bfa_fcs_fabric_event event)
अणु
	bfa_trc(fabric->fcs, fabric->bport.port_cfg.pwwn);
	bfa_trc(fabric->fcs, event);

	चयन (event) अणु
	हाल BFA_FCS_FABRIC_SM_STOPCOMP:
	हाल BFA_FCS_FABRIC_SM_LOGOCOMP:
		bfa_sm_set_state(fabric, bfa_fcs_fabric_sm_created);
		bfa_wc_करोwn(&(fabric->fcs)->wc);
		अवरोध;

	हाल BFA_FCS_FABRIC_SM_LINK_DOWN:
		/*
		 * Ignore - can get this event अगर we get notअगरied about IOC करोwn
		 * beक्रमe the fabric completion callbk is करोne.
		 */
		अवरोध;

	शेष:
		bfa_sm_fault(fabric->fcs, event);
	पूर्ण
पूर्ण

/*
 *  fcs_fabric_निजी fabric निजी functions
 */

अटल व्योम
bfa_fcs_fabric_init(काष्ठा bfa_fcs_fabric_s *fabric)
अणु
	काष्ठा bfa_lport_cfg_s *port_cfg = &fabric->bport.port_cfg;

	port_cfg->roles = BFA_LPORT_ROLE_FCP_IM;
	port_cfg->nwwn = fabric->fcs->bfa->ioc.attr->nwwn;
	port_cfg->pwwn = fabric->fcs->bfa->ioc.attr->pwwn;
पूर्ण

/*
 * Port Symbolic Name Creation क्रम base port.
 */
व्योम
bfa_fcs_fabric_psymb_init(काष्ठा bfa_fcs_fabric_s *fabric)
अणु
	काष्ठा bfa_lport_cfg_s *port_cfg = &fabric->bport.port_cfg;
	अक्षर model[BFA_ADAPTER_MODEL_NAME_LEN] = अणु0पूर्ण;
	काष्ठा bfa_fcs_driver_info_s *driver_info = &fabric->fcs->driver_info;

	bfa_ioc_get_adapter_model(&fabric->fcs->bfa->ioc, model);

	/* Model name/number */
	strlcpy(port_cfg->sym_name.symname, model,
		BFA_SYMNAME_MAXLEN);
	strlcat(port_cfg->sym_name.symname, BFA_FCS_PORT_SYMBNAME_SEPARATOR,
		BFA_SYMNAME_MAXLEN);

	/* Driver Version */
	strlcat(port_cfg->sym_name.symname, driver_info->version,
		BFA_SYMNAME_MAXLEN);
	strlcat(port_cfg->sym_name.symname, BFA_FCS_PORT_SYMBNAME_SEPARATOR,
		BFA_SYMNAME_MAXLEN);

	/* Host machine name */
	strlcat(port_cfg->sym_name.symname,
		driver_info->host_machine_name,
		BFA_SYMNAME_MAXLEN);
	strlcat(port_cfg->sym_name.symname, BFA_FCS_PORT_SYMBNAME_SEPARATOR,
		BFA_SYMNAME_MAXLEN);

	/*
	 * Host OS Info :
	 * If OS Patch Info is not there, करो not truncate any bytes from the
	 * OS name string and instead copy the entire OS info string (64 bytes).
	 */
	अगर (driver_info->host_os_patch[0] == '\0') अणु
		strlcat(port_cfg->sym_name.symname,
			driver_info->host_os_name,
			BFA_SYMNAME_MAXLEN);
		strlcat(port_cfg->sym_name.symname,
			BFA_FCS_PORT_SYMBNAME_SEPARATOR,
			BFA_SYMNAME_MAXLEN);
	पूर्ण अन्यथा अणु
		strlcat(port_cfg->sym_name.symname,
			driver_info->host_os_name,
			BFA_SYMNAME_MAXLEN);
		strlcat(port_cfg->sym_name.symname,
			BFA_FCS_PORT_SYMBNAME_SEPARATOR,
			BFA_SYMNAME_MAXLEN);

		/* Append host OS Patch Info */
		strlcat(port_cfg->sym_name.symname,
			driver_info->host_os_patch,
			BFA_SYMNAME_MAXLEN);
	पूर्ण

	/* null terminate */
	port_cfg->sym_name.symname[BFA_SYMNAME_MAXLEN - 1] = 0;
पूर्ण

/*
 * Node Symbolic Name Creation क्रम base port and all vports
 */
व्योम
bfa_fcs_fabric_nsymb_init(काष्ठा bfa_fcs_fabric_s *fabric)
अणु
	काष्ठा bfa_lport_cfg_s *port_cfg = &fabric->bport.port_cfg;
	अक्षर model[BFA_ADAPTER_MODEL_NAME_LEN] = अणु0पूर्ण;
	काष्ठा bfa_fcs_driver_info_s *driver_info = &fabric->fcs->driver_info;

	bfa_ioc_get_adapter_model(&fabric->fcs->bfa->ioc, model);

	/* Model name/number */
	strlcpy(port_cfg->node_sym_name.symname, model,
		BFA_SYMNAME_MAXLEN);
	strlcat(port_cfg->node_sym_name.symname,
			BFA_FCS_PORT_SYMBNAME_SEPARATOR,
			BFA_SYMNAME_MAXLEN);

	/* Driver Version */
	strlcat(port_cfg->node_sym_name.symname, (अक्षर *)driver_info->version,
		BFA_SYMNAME_MAXLEN);
	strlcat(port_cfg->node_sym_name.symname,
			BFA_FCS_PORT_SYMBNAME_SEPARATOR,
			BFA_SYMNAME_MAXLEN);

	/* Host machine name */
	strlcat(port_cfg->node_sym_name.symname,
		driver_info->host_machine_name,
		BFA_SYMNAME_MAXLEN);
	strlcat(port_cfg->node_sym_name.symname,
			BFA_FCS_PORT_SYMBNAME_SEPARATOR,
			BFA_SYMNAME_MAXLEN);

	/* null terminate */
	port_cfg->node_sym_name.symname[BFA_SYMNAME_MAXLEN - 1] = 0;
पूर्ण

/*
 * bfa lps login completion callback
 */
व्योम
bfa_cb_lps_flogi_comp(व्योम *bfad, व्योम *uarg, bfa_status_t status)
अणु
	काष्ठा bfa_fcs_fabric_s *fabric = uarg;

	bfa_trc(fabric->fcs, fabric->bport.port_cfg.pwwn);
	bfa_trc(fabric->fcs, status);

	चयन (status) अणु
	हाल BFA_STATUS_OK:
		fabric->stats.flogi_accepts++;
		अवरोध;

	हाल BFA_STATUS_INVALID_MAC:
		/* Only क्रम CNA */
		fabric->stats.flogi_acc_err++;
		bfa_sm_send_event(fabric, BFA_FCS_FABRIC_SM_RETRY_OP);

		वापस;

	हाल BFA_STATUS_EPROTOCOL:
		चयन (fabric->lps->ext_status) अणु
		हाल BFA_EPROTO_BAD_ACCEPT:
			fabric->stats.flogi_acc_err++;
			अवरोध;

		हाल BFA_EPROTO_UNKNOWN_RSP:
			fabric->stats.flogi_unknown_rsp++;
			अवरोध;

		शेष:
			अवरोध;
		पूर्ण
		bfa_sm_send_event(fabric, BFA_FCS_FABRIC_SM_RETRY_OP);

		वापस;

	हाल BFA_STATUS_FABRIC_RJT:
		fabric->stats.flogi_rejects++;
		bfa_sm_send_event(fabric, BFA_FCS_FABRIC_SM_RETRY_OP);
		वापस;

	शेष:
		fabric->stats.flogi_rsp_err++;
		bfa_sm_send_event(fabric, BFA_FCS_FABRIC_SM_RETRY_OP);
		वापस;
	पूर्ण

	fabric->bb_credit = fabric->lps->pr_bbcred;
	bfa_trc(fabric->fcs, fabric->bb_credit);

	अगर (!(fabric->lps->brcd_चयन))
		fabric->fabric_name =  fabric->lps->pr_nwwn;

	/*
	 * Check port type. It should be 1 = F-port.
	 */
	अगर (fabric->lps->fport) अणु
		fabric->bport.pid = fabric->lps->lp_pid;
		fabric->is_npiv = fabric->lps->npiv_en;
		fabric->is_auth = fabric->lps->auth_req;
		bfa_sm_send_event(fabric, BFA_FCS_FABRIC_SM_CONT_OP);
	पूर्ण अन्यथा अणु
		/*
		 * Nport-2-Nport direct attached
		 */
		fabric->bport.port_topo.pn2n.rem_port_wwn =
			fabric->lps->pr_pwwn;
		fabric->fab_type = BFA_FCS_FABRIC_N2N;
		bfa_sm_send_event(fabric, BFA_FCS_FABRIC_SM_NO_FABRIC);
	पूर्ण

	bfa_trc(fabric->fcs, fabric->bport.pid);
	bfa_trc(fabric->fcs, fabric->is_npiv);
	bfa_trc(fabric->fcs, fabric->is_auth);
पूर्ण
/*
 *		Allocate and send FLOGI.
 */
अटल व्योम
bfa_fcs_fabric_login(काष्ठा bfa_fcs_fabric_s *fabric)
अणु
	काष्ठा bfa_s		*bfa = fabric->fcs->bfa;
	काष्ठा bfa_lport_cfg_s	*pcfg = &fabric->bport.port_cfg;
	u8			alpa = 0;


	bfa_lps_flogi(fabric->lps, fabric, alpa, bfa_fcport_get_maxfrsize(bfa),
		      pcfg->pwwn, pcfg->nwwn, fabric->auth_reqd);

	fabric->stats.flogi_sent++;
पूर्ण

अटल व्योम
bfa_fcs_fabric_notअगरy_online(काष्ठा bfa_fcs_fabric_s *fabric)
अणु
	काष्ठा bfa_fcs_vport_s *vport;
	काष्ठा list_head	      *qe, *qen;

	bfa_trc(fabric->fcs, fabric->fabric_name);

	bfa_fcs_fabric_set_opertype(fabric);
	fabric->stats.fabric_onlines++;

	/*
	 * notअगरy online event to base and then भव ports
	 */
	bfa_fcs_lport_online(&fabric->bport);

	list_क्रम_each_safe(qe, qen, &fabric->vport_q) अणु
		vport = (काष्ठा bfa_fcs_vport_s *) qe;
		bfa_fcs_vport_online(vport);
	पूर्ण
पूर्ण

अटल व्योम
bfa_fcs_fabric_notअगरy_offline(काष्ठा bfa_fcs_fabric_s *fabric)
अणु
	काष्ठा bfa_fcs_vport_s *vport;
	काष्ठा list_head	      *qe, *qen;

	bfa_trc(fabric->fcs, fabric->fabric_name);
	fabric->stats.fabric_offlines++;

	/*
	 * notअगरy offline event first to vports and then base port.
	 */
	list_क्रम_each_safe(qe, qen, &fabric->vport_q) अणु
		vport = (काष्ठा bfa_fcs_vport_s *) qe;
		bfa_fcs_vport_offline(vport);
	पूर्ण

	bfa_fcs_lport_offline(&fabric->bport);

	fabric->fabric_name = 0;
	fabric->fabric_ip_addr[0] = 0;
पूर्ण

अटल व्योम
bfa_fcs_fabric_delay(व्योम *cbarg)
अणु
	काष्ठा bfa_fcs_fabric_s *fabric = cbarg;

	bfa_sm_send_event(fabric, BFA_FCS_FABRIC_SM_DELAYED);
पूर्ण

/*
 * Stop all vports and रुको क्रम vport stop completions.
 */
अटल व्योम
bfa_fcs_fabric_stop(काष्ठा bfa_fcs_fabric_s *fabric)
अणु
	काष्ठा bfa_fcs_vport_s *vport;
	काष्ठा list_head	*qe, *qen;

	bfa_wc_init(&fabric->stop_wc, bfa_fcs_fabric_stop_comp, fabric);

	list_क्रम_each_safe(qe, qen, &fabric->vport_q) अणु
		vport = (काष्ठा bfa_fcs_vport_s *) qe;
		bfa_wc_up(&fabric->stop_wc);
		bfa_fcs_vport_fcs_stop(vport);
	पूर्ण

	bfa_wc_up(&fabric->stop_wc);
	bfa_fcs_lport_stop(&fabric->bport);
	bfa_wc_रुको(&fabric->stop_wc);
पूर्ण

/*
 * Delete all vports and रुको क्रम vport delete completions.
 */
अटल व्योम
bfa_fcs_fabric_delete(काष्ठा bfa_fcs_fabric_s *fabric)
अणु
	काष्ठा bfa_fcs_vport_s *vport;
	काष्ठा list_head	      *qe, *qen;

	list_क्रम_each_safe(qe, qen, &fabric->vport_q) अणु
		vport = (काष्ठा bfa_fcs_vport_s *) qe;
		bfa_fcs_vport_fcs_delete(vport);
	पूर्ण

	bfa_fcs_lport_delete(&fabric->bport);
	bfa_wc_रुको(&fabric->wc);
पूर्ण

अटल व्योम
bfa_fcs_fabric_delete_comp(व्योम *cbarg)
अणु
	काष्ठा bfa_fcs_fabric_s *fabric = cbarg;

	bfa_sm_send_event(fabric, BFA_FCS_FABRIC_SM_DELCOMP);
पूर्ण

अटल व्योम
bfa_fcs_fabric_stop_comp(व्योम *cbarg)
अणु
	काष्ठा bfa_fcs_fabric_s *fabric = cbarg;

	bfa_sm_send_event(fabric, BFA_FCS_FABRIC_SM_STOPCOMP);
पूर्ण

/*
 *  fcs_fabric_खुला fabric खुला functions
 */

/*
 * Fabric module stop -- stop FCS actions
 */
व्योम
bfa_fcs_fabric_modstop(काष्ठा bfa_fcs_s *fcs)
अणु
	काष्ठा bfa_fcs_fabric_s *fabric;

	bfa_trc(fcs, 0);
	fabric = &fcs->fabric;
	bfa_sm_send_event(fabric, BFA_FCS_FABRIC_SM_STOP);
पूर्ण

/*
 * Fabric module start -- kick starts FCS actions
 */
व्योम
bfa_fcs_fabric_modstart(काष्ठा bfa_fcs_s *fcs)
अणु
	काष्ठा bfa_fcs_fabric_s *fabric;

	bfa_trc(fcs, 0);
	fabric = &fcs->fabric;
	bfa_sm_send_event(fabric, BFA_FCS_FABRIC_SM_START);
पूर्ण


/*
 *   Link up notअगरication from BFA physical port module.
 */
व्योम
bfa_fcs_fabric_link_up(काष्ठा bfa_fcs_fabric_s *fabric)
अणु
	bfa_trc(fabric->fcs, fabric->bport.port_cfg.pwwn);
	bfa_sm_send_event(fabric, BFA_FCS_FABRIC_SM_LINK_UP);
पूर्ण

/*
 *   Link करोwn notअगरication from BFA physical port module.
 */
व्योम
bfa_fcs_fabric_link_करोwn(काष्ठा bfa_fcs_fabric_s *fabric)
अणु
	bfa_trc(fabric->fcs, fabric->bport.port_cfg.pwwn);
	bfa_sm_send_event(fabric, BFA_FCS_FABRIC_SM_LINK_DOWN);
पूर्ण

/*
 *   A child vport is being created in the fabric.
 *
 *   Call from vport module at vport creation. A list of base port and vports
 *   beदीर्घing to a fabric is मुख्यtained to propagate link events.
 *
 *   param[in] fabric - Fabric instance. This can be a base fabric or vf.
 *   param[in] vport  - Vport being created.
 *
 *   @वापस None (always succeeds)
 */
व्योम
bfa_fcs_fabric_addvport(काष्ठा bfa_fcs_fabric_s *fabric,
			काष्ठा bfa_fcs_vport_s *vport)
अणु
	/*
	 * - add vport to fabric's vport_q
	 */
	bfa_trc(fabric->fcs, fabric->vf_id);

	list_add_tail(&vport->qe, &fabric->vport_q);
	fabric->num_vports++;
	bfa_wc_up(&fabric->wc);
पूर्ण

/*
 *   A child vport is being deleted from fabric.
 *
 *   Vport is being deleted.
 */
व्योम
bfa_fcs_fabric_delvport(काष्ठा bfa_fcs_fabric_s *fabric,
			काष्ठा bfa_fcs_vport_s *vport)
अणु
	list_del(&vport->qe);
	fabric->num_vports--;
	bfa_wc_करोwn(&fabric->wc);
पूर्ण


/*
 * Lookup क्रम a vport within a fabric given its pwwn
 */
काष्ठा bfa_fcs_vport_s *
bfa_fcs_fabric_vport_lookup(काष्ठा bfa_fcs_fabric_s *fabric, wwn_t pwwn)
अणु
	काष्ठा bfa_fcs_vport_s *vport;
	काष्ठा list_head	      *qe;

	list_क्रम_each(qe, &fabric->vport_q) अणु
		vport = (काष्ठा bfa_fcs_vport_s *) qe;
		अगर (bfa_fcs_lport_get_pwwn(&vport->lport) == pwwn)
			वापस vport;
	पूर्ण

	वापस शून्य;
पूर्ण


/*
 *  Get OUI of the attached चयन.
 *
 *  Note : Use of this function should be aव्योमed as much as possible.
 *         This function should be used only अगर there is any requirement
*          to check क्रम FOS version below 6.3.
 *         To check अगर the attached fabric is a brocade fabric, use
 *         bfa_lps_is_brcd_fabric() which works क्रम FOS versions 6.3
 *         or above only.
 */

u16
bfa_fcs_fabric_get_चयन_oui(काष्ठा bfa_fcs_fabric_s *fabric)
अणु
	wwn_t fab_nwwn;
	u8 *पंचांगp;
	u16 oui;

	fab_nwwn = fabric->lps->pr_nwwn;

	पंचांगp = (u8 *)&fab_nwwn;
	oui = (पंचांगp[3] << 8) | पंचांगp[4];

	वापस oui;
पूर्ण
/*
 *		Unsolicited frame receive handling.
 */
व्योम
bfa_fcs_fabric_uf_recv(काष्ठा bfa_fcs_fabric_s *fabric, काष्ठा fchs_s *fchs,
		       u16 len)
अणु
	u32	pid = fchs->d_id;
	काष्ठा bfa_fcs_vport_s *vport;
	काष्ठा list_head	      *qe;
	काष्ठा fc_els_cmd_s *els_cmd = (काष्ठा fc_els_cmd_s *) (fchs + 1);
	काष्ठा fc_logi_s *flogi = (काष्ठा fc_logi_s *) els_cmd;

	bfa_trc(fabric->fcs, len);
	bfa_trc(fabric->fcs, pid);

	/*
	 * Look क्रम our own FLOGI frames being looped back. This means an
	 * बाह्यal loopback cable is in place. Our own FLOGI frames are
	 * someबार looped back when चयन port माला_लो temporarily bypassed.
	 */
	अगर ((pid == bfa_ntoh3b(FC_FABRIC_PORT)) &&
	    (els_cmd->els_code == FC_ELS_FLOGI) &&
	    (flogi->port_name == bfa_fcs_lport_get_pwwn(&fabric->bport))) अणु
		bfa_sm_send_event(fabric, BFA_FCS_FABRIC_SM_LOOPBACK);
		वापस;
	पूर्ण

	/*
	 * FLOGI/EVFP exchanges should be consumed by base fabric.
	 */
	अगर (fchs->d_id == bfa_hton3b(FC_FABRIC_PORT)) अणु
		bfa_trc(fabric->fcs, pid);
		bfa_fcs_fabric_process_uf(fabric, fchs, len);
		वापस;
	पूर्ण

	अगर (fabric->bport.pid == pid) अणु
		/*
		 * All authentication frames should be routed to auth
		 */
		bfa_trc(fabric->fcs, els_cmd->els_code);
		अगर (els_cmd->els_code == FC_ELS_AUTH) अणु
			bfa_trc(fabric->fcs, els_cmd->els_code);
			वापस;
		पूर्ण

		bfa_trc(fabric->fcs, *(u8 *) ((u8 *) fchs));
		bfa_fcs_lport_uf_recv(&fabric->bport, fchs, len);
		वापस;
	पूर्ण

	/*
	 * look क्रम a matching local port ID
	 */
	list_क्रम_each(qe, &fabric->vport_q) अणु
		vport = (काष्ठा bfa_fcs_vport_s *) qe;
		अगर (vport->lport.pid == pid) अणु
			bfa_fcs_lport_uf_recv(&vport->lport, fchs, len);
			वापस;
		पूर्ण
	पूर्ण

	अगर (!bfa_fcs_fabric_is_चयनed(fabric))
		bfa_fcs_lport_uf_recv(&fabric->bport, fchs, len);

	bfa_trc(fabric->fcs, fchs->type);
पूर्ण

/*
 *		Unsolicited frames to be processed by fabric.
 */
अटल व्योम
bfa_fcs_fabric_process_uf(काष्ठा bfa_fcs_fabric_s *fabric, काष्ठा fchs_s *fchs,
			  u16 len)
अणु
	काष्ठा fc_els_cmd_s *els_cmd = (काष्ठा fc_els_cmd_s *) (fchs + 1);

	bfa_trc(fabric->fcs, els_cmd->els_code);

	चयन (els_cmd->els_code) अणु
	हाल FC_ELS_FLOGI:
		bfa_fcs_fabric_process_flogi(fabric, fchs, len);
		अवरोध;

	शेष:
		/*
		 * need to generate a LS_RJT
		 */
		अवरोध;
	पूर्ण
पूर्ण

/*
 *	Process	incoming FLOGI
 */
अटल व्योम
bfa_fcs_fabric_process_flogi(काष्ठा bfa_fcs_fabric_s *fabric,
			काष्ठा fchs_s *fchs, u16 len)
अणु
	काष्ठा fc_logi_s *flogi = (काष्ठा fc_logi_s *) (fchs + 1);
	काष्ठा bfa_fcs_lport_s *bport = &fabric->bport;

	bfa_trc(fabric->fcs, fchs->s_id);

	fabric->stats.flogi_rcvd++;
	/*
	 * Check port type. It should be 0 = n-port.
	 */
	अगर (flogi->csp.port_type) अणु
		/*
		 * @toकरो: may need to send a LS_RJT
		 */
		bfa_trc(fabric->fcs, flogi->port_name);
		fabric->stats.flogi_rejected++;
		वापस;
	पूर्ण

	fabric->bb_credit = be16_to_cpu(flogi->csp.bbcred);
	bport->port_topo.pn2n.rem_port_wwn = flogi->port_name;
	bport->port_topo.pn2n.reply_oxid = fchs->ox_id;

	/*
	 * Send a Flogi Acc
	 */
	bfa_fcs_fabric_send_flogi_acc(fabric);
	bfa_sm_send_event(fabric, BFA_FCS_FABRIC_SM_NO_FABRIC);
पूर्ण

अटल व्योम
bfa_fcs_fabric_send_flogi_acc(काष्ठा bfa_fcs_fabric_s *fabric)
अणु
	काष्ठा bfa_lport_cfg_s *pcfg = &fabric->bport.port_cfg;
	काष्ठा bfa_fcs_lport_n2n_s *n2n_port = &fabric->bport.port_topo.pn2n;
	काष्ठा bfa_s	  *bfa = fabric->fcs->bfa;
	काष्ठा bfa_fcxp_s *fcxp;
	u16	reqlen;
	काष्ठा fchs_s	fchs;

	fcxp = bfa_fcs_fcxp_alloc(fabric->fcs, BFA_FALSE);
	/*
	 * Do not expect this failure -- expect remote node to retry
	 */
	अगर (!fcxp)
		वापस;

	reqlen = fc_flogi_acc_build(&fchs, bfa_fcxp_get_reqbuf(fcxp),
				    bfa_hton3b(FC_FABRIC_PORT),
				    n2n_port->reply_oxid, pcfg->pwwn,
				    pcfg->nwwn,
				    bfa_fcport_get_maxfrsize(bfa),
				    bfa_fcport_get_rx_bbcredit(bfa), 0);

	bfa_fcxp_send(fcxp, शून्य, fabric->vf_id, fabric->lps->bfa_tag,
		      BFA_FALSE, FC_CLASS_3,
		      reqlen, &fchs, bfa_fcs_fabric_flogiacc_comp, fabric,
		      FC_MAX_PDUSZ, 0);
पूर्ण

/*
 *   Flogi Acc completion callback.
 */
अटल व्योम
bfa_fcs_fabric_flogiacc_comp(व्योम *fcsarg, काष्ठा bfa_fcxp_s *fcxp, व्योम *cbarg,
			     bfa_status_t status, u32 rsp_len,
			     u32 resid_len, काष्ठा fchs_s *rspfchs)
अणु
	काष्ठा bfa_fcs_fabric_s *fabric = cbarg;

	bfa_trc(fabric->fcs, status);
पूर्ण


/*
 * Send AEN notअगरication
 */
अटल व्योम
bfa_fcs_fabric_aen_post(काष्ठा bfa_fcs_lport_s *port,
			क्रमागत bfa_port_aen_event event)
अणु
	काष्ठा bfad_s *bfad = (काष्ठा bfad_s *)port->fabric->fcs->bfad;
	काष्ठा bfa_aen_entry_s  *aen_entry;

	bfad_get_aen_entry(bfad, aen_entry);
	अगर (!aen_entry)
		वापस;

	aen_entry->aen_data.port.pwwn = bfa_fcs_lport_get_pwwn(port);
	aen_entry->aen_data.port.fwwn = bfa_fcs_lport_get_fabric_name(port);

	/* Send the AEN notअगरication */
	bfad_im_post_venकरोr_event(aen_entry, bfad, ++port->fcs->fcs_aen_seq,
				  BFA_AEN_CAT_PORT, event);
पूर्ण

/*
 *
 * @param[in] fabric - fabric
 * @param[in] wwn_t - new fabric name
 *
 * @वापस - none
 */
व्योम
bfa_fcs_fabric_set_fabric_name(काष्ठा bfa_fcs_fabric_s *fabric,
			       wwn_t fabric_name)
अणु
	काष्ठा bfad_s *bfad = (काष्ठा bfad_s *)fabric->fcs->bfad;
	अक्षर	pwwn_ptr[BFA_STRING_32];
	अक्षर	fwwn_ptr[BFA_STRING_32];

	bfa_trc(fabric->fcs, fabric_name);

	अगर (fabric->fabric_name == 0) अणु
		/*
		 * With BRCD चयनes, we करोn't get Fabric Name in FLOGI.
		 * Don't generate a fabric name change event in this हाल.
		 */
		fabric->fabric_name = fabric_name;
	पूर्ण अन्यथा अणु
		fabric->fabric_name = fabric_name;
		wwn2str(pwwn_ptr, bfa_fcs_lport_get_pwwn(&fabric->bport));
		wwn2str(fwwn_ptr,
			bfa_fcs_lport_get_fabric_name(&fabric->bport));
		BFA_LOG(KERN_WARNING, bfad, bfa_log_level,
			"Base port WWN = %s Fabric WWN = %s\n",
			pwwn_ptr, fwwn_ptr);
		bfa_fcs_fabric_aen_post(&fabric->bport,
				BFA_PORT_AEN_FABRIC_NAME_CHANGE);
	पूर्ण
पूर्ण

व्योम
bfa_cb_lps_flogo_comp(व्योम *bfad, व्योम *uarg)
अणु
	काष्ठा bfa_fcs_fabric_s *fabric = uarg;
	bfa_sm_send_event(fabric, BFA_FCS_FABRIC_SM_LOGOCOMP);
पूर्ण

/*
 *	Returns FCS vf काष्ठाure क्रम a given vf_id.
 *
 *	param[in]	vf_id - VF_ID
 *
 *	वापस
 *	If lookup succeeds, retuns fcs vf object, otherwise वापसs शून्य
 */
bfa_fcs_vf_t   *
bfa_fcs_vf_lookup(काष्ठा bfa_fcs_s *fcs, u16 vf_id)
अणु
	bfa_trc(fcs, vf_id);
	अगर (vf_id == FC_VF_ID_शून्य)
		वापस &fcs->fabric;

	वापस शून्य;
पूर्ण

/*
 *	Return the list of local logical ports present in the given VF.
 *
 *	@param[in]	vf	vf क्रम which logical ports are वापसed
 *	@param[out]	lpwwn	वापसed logical port wwn list
 *	@param[in,out]	nlports in:size of lpwwn list;
 *				out:total elements present,
 *				actual elements वापसed is limited by the size
 */
व्योम
bfa_fcs_vf_get_ports(bfa_fcs_vf_t *vf, wwn_t lpwwn[], पूर्णांक *nlports)
अणु
	काष्ठा list_head *qe;
	काष्ठा bfa_fcs_vport_s *vport;
	पूर्णांक	i = 0;
	काष्ठा bfa_fcs_s	*fcs;

	अगर (vf == शून्य || lpwwn == शून्य || *nlports == 0)
		वापस;

	fcs = vf->fcs;

	bfa_trc(fcs, vf->vf_id);
	bfa_trc(fcs, (uपूर्णांक32_t) *nlports);

	lpwwn[i++] = vf->bport.port_cfg.pwwn;

	list_क्रम_each(qe, &vf->vport_q) अणु
		अगर (i >= *nlports)
			अवरोध;

		vport = (काष्ठा bfa_fcs_vport_s *) qe;
		lpwwn[i++] = vport->lport.port_cfg.pwwn;
	पूर्ण

	bfa_trc(fcs, i);
	*nlports = i;
पूर्ण

/*
 * BFA FCS PPORT ( physical port)
 */
अटल व्योम
bfa_fcs_port_event_handler(व्योम *cbarg, क्रमागत bfa_port_linkstate event)
अणु
	काष्ठा bfa_fcs_s      *fcs = cbarg;

	bfa_trc(fcs, event);

	चयन (event) अणु
	हाल BFA_PORT_LINKUP:
		bfa_fcs_fabric_link_up(&fcs->fabric);
		अवरोध;

	हाल BFA_PORT_LINKDOWN:
		bfa_fcs_fabric_link_करोwn(&fcs->fabric);
		अवरोध;

	शेष:
		WARN_ON(1);
	पूर्ण
पूर्ण

/*
 * BFA FCS UF ( Unsolicited Frames)
 */

/*
 *		BFA callback क्रम unsolicited frame receive handler.
 *
 * @param[in]		cbarg		callback arg क्रम receive handler
 * @param[in]		uf		unsolicited frame descriptor
 *
 * @वापस None
 */
अटल व्योम
bfa_fcs_uf_recv(व्योम *cbarg, काष्ठा bfa_uf_s *uf)
अणु
	काष्ठा bfa_fcs_s	*fcs = (काष्ठा bfa_fcs_s *) cbarg;
	काष्ठा fchs_s	*fchs = bfa_uf_get_frmbuf(uf);
	u16	len = bfa_uf_get_frmlen(uf);
	काष्ठा fc_vft_s *vft;
	काष्ठा bfa_fcs_fabric_s *fabric;

	/*
	 * check क्रम VFT header
	 */
	अगर (fchs->routing == FC_RTG_EXT_HDR &&
	    fchs->cat_info == FC_CAT_VFT_HDR) अणु
		bfa_stats(fcs, uf.tagged);
		vft = bfa_uf_get_frmbuf(uf);
		अगर (fcs->port_vfid == vft->vf_id)
			fabric = &fcs->fabric;
		अन्यथा
			fabric = bfa_fcs_vf_lookup(fcs, (u16) vft->vf_id);

		/*
		 * drop frame अगर vfid is unknown
		 */
		अगर (!fabric) अणु
			WARN_ON(1);
			bfa_stats(fcs, uf.vfid_unknown);
			bfa_uf_मुक्त(uf);
			वापस;
		पूर्ण

		/*
		 * skip vft header
		 */
		fchs = (काष्ठा fchs_s *) (vft + 1);
		len -= माप(काष्ठा fc_vft_s);

		bfa_trc(fcs, vft->vf_id);
	पूर्ण अन्यथा अणु
		bfa_stats(fcs, uf.untagged);
		fabric = &fcs->fabric;
	पूर्ण

	bfa_trc(fcs, ((u32 *) fchs)[0]);
	bfa_trc(fcs, ((u32 *) fchs)[1]);
	bfa_trc(fcs, ((u32 *) fchs)[2]);
	bfa_trc(fcs, ((u32 *) fchs)[3]);
	bfa_trc(fcs, ((u32 *) fchs)[4]);
	bfa_trc(fcs, ((u32 *) fchs)[5]);
	bfa_trc(fcs, len);

	bfa_fcs_fabric_uf_recv(fabric, fchs, len);
	bfa_uf_मुक्त(uf);
पूर्ण

/*
 * fcs attach -- called once to initialize data काष्ठाures at driver attach समय
 */
व्योम
bfa_fcs_attach(काष्ठा bfa_fcs_s *fcs, काष्ठा bfa_s *bfa, काष्ठा bfad_s *bfad,
	       bfa_boolean_t min_cfg)
अणु
	काष्ठा bfa_fcs_fabric_s *fabric = &fcs->fabric;

	fcs->bfa = bfa;
	fcs->bfad = bfad;
	fcs->min_cfg = min_cfg;
	fcs->num_rport_logins = 0;

	bfa->fcs = BFA_TRUE;
	fcbuild_init();

	bfa_fcport_event_रेजिस्टर(fcs->bfa, bfa_fcs_port_event_handler, fcs);
	bfa_uf_recv_रेजिस्टर(fcs->bfa, bfa_fcs_uf_recv, fcs);

	स_रखो(fabric, 0, माप(काष्ठा bfa_fcs_fabric_s));

	/*
	 * Initialize base fabric.
	 */
	fabric->fcs = fcs;
	INIT_LIST_HEAD(&fabric->vport_q);
	INIT_LIST_HEAD(&fabric->vf_q);
	fabric->lps = bfa_lps_alloc(fcs->bfa);
	WARN_ON(!fabric->lps);

	/*
	 * Initialize fabric delete completion handler. Fabric deletion is
	 * complete when the last vport delete is complete.
	 */
	bfa_wc_init(&fabric->wc, bfa_fcs_fabric_delete_comp, fabric);
	bfa_wc_up(&fabric->wc); /* For the base port */

	bfa_sm_set_state(fabric, bfa_fcs_fabric_sm_uninit);
	bfa_fcs_lport_attach(&fabric->bport, fabric->fcs, FC_VF_ID_शून्य, शून्य);
पूर्ण
