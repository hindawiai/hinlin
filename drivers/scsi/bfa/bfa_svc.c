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

#समावेश "bfad_drv.h"
#समावेश "bfad_im.h"
#समावेश "bfa_plog.h"
#समावेश "bfa_cs.h"
#समावेश "bfa_modules.h"

BFA_TRC_खाता(HAL, FCXP);

/*
 * LPS related definitions
 */
#घोषणा BFA_LPS_MIN_LPORTS      (1)
#घोषणा BFA_LPS_MAX_LPORTS      (256)

/*
 * Maximum Vports supported per physical port or vf.
 */
#घोषणा BFA_LPS_MAX_VPORTS_SUPP_CB  255
#घोषणा BFA_LPS_MAX_VPORTS_SUPP_CT  190


/*
 * FC PORT related definitions
 */
/*
 * The port is considered disabled अगर corresponding physical port or IOC are
 * disabled explicitly
 */
#घोषणा BFA_PORT_IS_DISABLED(bfa) \
	((bfa_fcport_is_disabled(bfa) == BFA_TRUE) || \
	(bfa_ioc_is_disabled(&bfa->ioc) == BFA_TRUE))

/*
 * BFA port state machine events
 */
क्रमागत bfa_fcport_sm_event अणु
	BFA_FCPORT_SM_START	= 1,	/*  start port state machine	*/
	BFA_FCPORT_SM_STOP	= 2,	/*  stop port state machine	*/
	BFA_FCPORT_SM_ENABLE	= 3,	/*  enable port		*/
	BFA_FCPORT_SM_DISABLE	= 4,	/*  disable port state machine */
	BFA_FCPORT_SM_FWRSP	= 5,	/*  firmware enable/disable rsp */
	BFA_FCPORT_SM_LINKUP	= 6,	/*  firmware linkup event	*/
	BFA_FCPORT_SM_LINKDOWN	= 7,	/*  firmware linkup करोwn	*/
	BFA_FCPORT_SM_QRESUME	= 8,	/*  CQ space available	*/
	BFA_FCPORT_SM_HWFAIL	= 9,	/*  IOC h/w failure		*/
	BFA_FCPORT_SM_DPORTENABLE = 10, /*  enable dport      */
	BFA_FCPORT_SM_DPORTDISABLE = 11,/*  disable dport     */
	BFA_FCPORT_SM_FAA_MISCONFIG = 12,	/* FAA misconfiguratin */
	BFA_FCPORT_SM_DDPORTENABLE  = 13,	/* enable ddport	*/
	BFA_FCPORT_SM_DDPORTDISABLE = 14,	/* disable ddport	*/
पूर्ण;

/*
 * BFA port link notअगरication state machine events
 */

क्रमागत bfa_fcport_ln_sm_event अणु
	BFA_FCPORT_LN_SM_LINKUP		= 1,	/*  linkup event	*/
	BFA_FCPORT_LN_SM_LINKDOWN	= 2,	/*  linkकरोwn event	*/
	BFA_FCPORT_LN_SM_NOTIFICATION	= 3	/*  करोne notअगरication	*/
पूर्ण;

/*
 * RPORT related definitions
 */
#घोषणा bfa_rport_offline_cb(__rp) करो अणु					\
	अगर ((__rp)->bfa->fcs)						\
		bfa_cb_rport_offline((__rp)->rport_drv);      \
	अन्यथा अणु								\
		bfa_cb_queue((__rp)->bfa, &(__rp)->hcb_qe,		\
				__bfa_cb_rport_offline, (__rp));      \
	पूर्ण								\
पूर्ण जबतक (0)

#घोषणा bfa_rport_online_cb(__rp) करो अणु					\
	अगर ((__rp)->bfa->fcs)						\
		bfa_cb_rport_online((__rp)->rport_drv);      \
	अन्यथा अणु								\
		bfa_cb_queue((__rp)->bfa, &(__rp)->hcb_qe,		\
				  __bfa_cb_rport_online, (__rp));      \
		पूर्ण							\
पूर्ण जबतक (0)

/*
 * क्रमward declarations FCXP related functions
 */
अटल व्योम	__bfa_fcxp_send_cbfn(व्योम *cbarg, bfa_boolean_t complete);
अटल व्योम	hal_fcxp_rx_plog(काष्ठा bfa_s *bfa, काष्ठा bfa_fcxp_s *fcxp,
				काष्ठा bfi_fcxp_send_rsp_s *fcxp_rsp);
अटल व्योम	hal_fcxp_tx_plog(काष्ठा bfa_s *bfa, u32 reqlen,
				काष्ठा bfa_fcxp_s *fcxp, काष्ठा fchs_s *fchs);
अटल व्योम	bfa_fcxp_qresume(व्योम *cbarg);
अटल व्योम	bfa_fcxp_queue(काष्ठा bfa_fcxp_s *fcxp,
				काष्ठा bfi_fcxp_send_req_s *send_req);

/*
 * क्रमward declarations क्रम LPS functions
 */
अटल व्योम bfa_lps_login_rsp(काष्ठा bfa_s *bfa,
				काष्ठा bfi_lps_login_rsp_s *rsp);
अटल व्योम bfa_lps_no_res(काष्ठा bfa_lps_s *first_lps, u8 count);
अटल व्योम bfa_lps_logout_rsp(काष्ठा bfa_s *bfa,
				काष्ठा bfi_lps_logout_rsp_s *rsp);
अटल व्योम bfa_lps_reqq_resume(व्योम *lps_arg);
अटल व्योम bfa_lps_मुक्त(काष्ठा bfa_lps_s *lps);
अटल व्योम bfa_lps_send_login(काष्ठा bfa_lps_s *lps);
अटल व्योम bfa_lps_send_logout(काष्ठा bfa_lps_s *lps);
अटल व्योम bfa_lps_send_set_n2n_pid(काष्ठा bfa_lps_s *lps);
अटल व्योम bfa_lps_login_comp(काष्ठा bfa_lps_s *lps);
अटल व्योम bfa_lps_logout_comp(काष्ठा bfa_lps_s *lps);
अटल व्योम bfa_lps_cvl_event(काष्ठा bfa_lps_s *lps);

/*
 * क्रमward declaration क्रम LPS state machine
 */
अटल व्योम bfa_lps_sm_init(काष्ठा bfa_lps_s *lps, क्रमागत bfa_lps_event event);
अटल व्योम bfa_lps_sm_login(काष्ठा bfa_lps_s *lps, क्रमागत bfa_lps_event event);
अटल व्योम bfa_lps_sm_loginरुको(काष्ठा bfa_lps_s *lps, क्रमागत bfa_lps_event
					event);
अटल व्योम bfa_lps_sm_online(काष्ठा bfa_lps_s *lps, क्रमागत bfa_lps_event event);
अटल व्योम bfa_lps_sm_online_n2n_pid_रुको(काष्ठा bfa_lps_s *lps,
					क्रमागत bfa_lps_event event);
अटल व्योम bfa_lps_sm_logout(काष्ठा bfa_lps_s *lps, क्रमागत bfa_lps_event event);
अटल व्योम bfa_lps_sm_logoरुको(काष्ठा bfa_lps_s *lps, क्रमागत bfa_lps_event
					event);

/*
 * क्रमward declaration क्रम FC Port functions
 */
अटल bfa_boolean_t bfa_fcport_send_enable(काष्ठा bfa_fcport_s *fcport);
अटल bfa_boolean_t bfa_fcport_send_disable(काष्ठा bfa_fcport_s *fcport);
अटल व्योम bfa_fcport_update_linkinfo(काष्ठा bfa_fcport_s *fcport);
अटल व्योम bfa_fcport_reset_linkinfo(काष्ठा bfa_fcport_s *fcport);
अटल व्योम bfa_fcport_set_wwns(काष्ठा bfa_fcport_s *fcport);
अटल व्योम __bfa_cb_fcport_event(व्योम *cbarg, bfa_boolean_t complete);
अटल व्योम bfa_fcport_scn(काष्ठा bfa_fcport_s *fcport,
			क्रमागत bfa_port_linkstate event, bfa_boolean_t trunk);
अटल व्योम bfa_fcport_queue_cb(काष्ठा bfa_fcport_ln_s *ln,
				क्रमागत bfa_port_linkstate event);
अटल व्योम __bfa_cb_fcport_stats_clr(व्योम *cbarg, bfa_boolean_t complete);
अटल व्योम bfa_fcport_stats_get_समयout(व्योम *cbarg);
अटल व्योम bfa_fcport_stats_clr_समयout(व्योम *cbarg);
अटल व्योम bfa_trunk_iocdisable(काष्ठा bfa_s *bfa);

/*
 * क्रमward declaration क्रम FC PORT state machine
 */
अटल व्योम     bfa_fcport_sm_uninit(काष्ठा bfa_fcport_s *fcport,
					क्रमागत bfa_fcport_sm_event event);
अटल व्योम     bfa_fcport_sm_enabling_qरुको(काष्ठा bfa_fcport_s *fcport,
					क्रमागत bfa_fcport_sm_event event);
अटल व्योम     bfa_fcport_sm_enabling(काष्ठा bfa_fcport_s *fcport,
					क्रमागत bfa_fcport_sm_event event);
अटल व्योम     bfa_fcport_sm_linkकरोwn(काष्ठा bfa_fcport_s *fcport,
					क्रमागत bfa_fcport_sm_event event);
अटल व्योम     bfa_fcport_sm_linkup(काष्ठा bfa_fcport_s *fcport,
					क्रमागत bfa_fcport_sm_event event);
अटल व्योम     bfa_fcport_sm_disabling(काष्ठा bfa_fcport_s *fcport,
					क्रमागत bfa_fcport_sm_event event);
अटल व्योम     bfa_fcport_sm_disabling_qरुको(काष्ठा bfa_fcport_s *fcport,
					क्रमागत bfa_fcport_sm_event event);
अटल व्योम     bfa_fcport_sm_toggling_qरुको(काष्ठा bfa_fcport_s *fcport,
					क्रमागत bfa_fcport_sm_event event);
अटल व्योम     bfa_fcport_sm_disabled(काष्ठा bfa_fcport_s *fcport,
					क्रमागत bfa_fcport_sm_event event);
अटल व्योम     bfa_fcport_sm_stopped(काष्ठा bfa_fcport_s *fcport,
					क्रमागत bfa_fcport_sm_event event);
अटल व्योम     bfa_fcport_sm_iocकरोwn(काष्ठा bfa_fcport_s *fcport,
					क्रमागत bfa_fcport_sm_event event);
अटल व्योम     bfa_fcport_sm_iocfail(काष्ठा bfa_fcport_s *fcport,
					क्रमागत bfa_fcport_sm_event event);
अटल व्योम	bfa_fcport_sm_dport(काष्ठा bfa_fcport_s *fcport,
					क्रमागत bfa_fcport_sm_event event);
अटल व्योम     bfa_fcport_sm_ddport(काष्ठा bfa_fcport_s *fcport,
					क्रमागत bfa_fcport_sm_event event);
अटल व्योम	bfa_fcport_sm_faa_misconfig(काष्ठा bfa_fcport_s *fcport,
					क्रमागत bfa_fcport_sm_event event);

अटल व्योम     bfa_fcport_ln_sm_dn(काष्ठा bfa_fcport_ln_s *ln,
					क्रमागत bfa_fcport_ln_sm_event event);
अटल व्योम     bfa_fcport_ln_sm_dn_nf(काष्ठा bfa_fcport_ln_s *ln,
					क्रमागत bfa_fcport_ln_sm_event event);
अटल व्योम     bfa_fcport_ln_sm_dn_up_nf(काष्ठा bfa_fcport_ln_s *ln,
					क्रमागत bfa_fcport_ln_sm_event event);
अटल व्योम     bfa_fcport_ln_sm_up(काष्ठा bfa_fcport_ln_s *ln,
					क्रमागत bfa_fcport_ln_sm_event event);
अटल व्योम     bfa_fcport_ln_sm_up_nf(काष्ठा bfa_fcport_ln_s *ln,
					क्रमागत bfa_fcport_ln_sm_event event);
अटल व्योम     bfa_fcport_ln_sm_up_dn_nf(काष्ठा bfa_fcport_ln_s *ln,
					क्रमागत bfa_fcport_ln_sm_event event);
अटल व्योम     bfa_fcport_ln_sm_up_dn_up_nf(काष्ठा bfa_fcport_ln_s *ln,
					क्रमागत bfa_fcport_ln_sm_event event);

अटल काष्ठा bfa_sm_table_s hal_port_sm_table[] = अणु
	अणुBFA_SM(bfa_fcport_sm_uninit), BFA_PORT_ST_UNINITपूर्ण,
	अणुBFA_SM(bfa_fcport_sm_enabling_qरुको), BFA_PORT_ST_ENABLING_QWAITपूर्ण,
	अणुBFA_SM(bfa_fcport_sm_enabling), BFA_PORT_ST_ENABLINGपूर्ण,
	अणुBFA_SM(bfa_fcport_sm_linkकरोwn), BFA_PORT_ST_LINKDOWNपूर्ण,
	अणुBFA_SM(bfa_fcport_sm_linkup), BFA_PORT_ST_LINKUPपूर्ण,
	अणुBFA_SM(bfa_fcport_sm_disabling_qरुको), BFA_PORT_ST_DISABLING_QWAITपूर्ण,
	अणुBFA_SM(bfa_fcport_sm_toggling_qरुको), BFA_PORT_ST_TOGGLING_QWAITपूर्ण,
	अणुBFA_SM(bfa_fcport_sm_disabling), BFA_PORT_ST_DISABLINGपूर्ण,
	अणुBFA_SM(bfa_fcport_sm_disabled), BFA_PORT_ST_DISABLEDपूर्ण,
	अणुBFA_SM(bfa_fcport_sm_stopped), BFA_PORT_ST_STOPPEDपूर्ण,
	अणुBFA_SM(bfa_fcport_sm_iocकरोwn), BFA_PORT_ST_IOCDOWNपूर्ण,
	अणुBFA_SM(bfa_fcport_sm_iocfail), BFA_PORT_ST_IOCDOWNपूर्ण,
	अणुBFA_SM(bfa_fcport_sm_dport), BFA_PORT_ST_DPORTपूर्ण,
	अणुBFA_SM(bfa_fcport_sm_ddport), BFA_PORT_ST_DDPORTपूर्ण,
	अणुBFA_SM(bfa_fcport_sm_faa_misconfig), BFA_PORT_ST_FAA_MISCONFIGपूर्ण,
पूर्ण;


/*
 * क्रमward declaration क्रम RPORT related functions
 */
अटल काष्ठा bfa_rport_s *bfa_rport_alloc(काष्ठा bfa_rport_mod_s *rp_mod);
अटल व्योम		bfa_rport_मुक्त(काष्ठा bfa_rport_s *rport);
अटल bfa_boolean_t	bfa_rport_send_fwcreate(काष्ठा bfa_rport_s *rp);
अटल bfa_boolean_t	bfa_rport_send_fwdelete(काष्ठा bfa_rport_s *rp);
अटल bfa_boolean_t	bfa_rport_send_fwspeed(काष्ठा bfa_rport_s *rp);
अटल व्योम		__bfa_cb_rport_online(व्योम *cbarg,
						bfa_boolean_t complete);
अटल व्योम		__bfa_cb_rport_offline(व्योम *cbarg,
						bfa_boolean_t complete);

/*
 * क्रमward declaration क्रम RPORT state machine
 */
अटल व्योम     bfa_rport_sm_uninit(काष्ठा bfa_rport_s *rp,
					क्रमागत bfa_rport_event event);
अटल व्योम     bfa_rport_sm_created(काष्ठा bfa_rport_s *rp,
					क्रमागत bfa_rport_event event);
अटल व्योम     bfa_rport_sm_fwcreate(काष्ठा bfa_rport_s *rp,
					क्रमागत bfa_rport_event event);
अटल व्योम     bfa_rport_sm_online(काष्ठा bfa_rport_s *rp,
					क्रमागत bfa_rport_event event);
अटल व्योम     bfa_rport_sm_fwdelete(काष्ठा bfa_rport_s *rp,
					क्रमागत bfa_rport_event event);
अटल व्योम     bfa_rport_sm_offline(काष्ठा bfa_rport_s *rp,
					क्रमागत bfa_rport_event event);
अटल व्योम     bfa_rport_sm_deleting(काष्ठा bfa_rport_s *rp,
					क्रमागत bfa_rport_event event);
अटल व्योम     bfa_rport_sm_offline_pending(काष्ठा bfa_rport_s *rp,
					क्रमागत bfa_rport_event event);
अटल व्योम     bfa_rport_sm_delete_pending(काष्ठा bfa_rport_s *rp,
					क्रमागत bfa_rport_event event);
अटल व्योम     bfa_rport_sm_iocdisable(काष्ठा bfa_rport_s *rp,
					क्रमागत bfa_rport_event event);
अटल व्योम     bfa_rport_sm_fwcreate_qfull(काष्ठा bfa_rport_s *rp,
					क्रमागत bfa_rport_event event);
अटल व्योम     bfa_rport_sm_fwdelete_qfull(काष्ठा bfa_rport_s *rp,
					क्रमागत bfa_rport_event event);
अटल व्योम     bfa_rport_sm_deleting_qfull(काष्ठा bfa_rport_s *rp,
					क्रमागत bfa_rport_event event);

/*
 * PLOG related definitions
 */
अटल पूर्णांक
plkd_validate_logrec(काष्ठा bfa_plog_rec_s *pl_rec)
अणु
	अगर ((pl_rec->log_type != BFA_PL_LOG_TYPE_INT) &&
		(pl_rec->log_type != BFA_PL_LOG_TYPE_STRING))
		वापस 1;

	अगर ((pl_rec->log_type != BFA_PL_LOG_TYPE_INT) &&
		(pl_rec->log_num_पूर्णांकs > BFA_PL_INT_LOG_SZ))
		वापस 1;

	वापस 0;
पूर्ण

अटल व्योम
bfa_plog_add(काष्ठा bfa_plog_s *plog, काष्ठा bfa_plog_rec_s *pl_rec)
अणु
	u16 tail;
	काष्ठा bfa_plog_rec_s *pl_recp;

	अगर (plog->plog_enabled == 0)
		वापस;

	अगर (plkd_validate_logrec(pl_rec)) अणु
		WARN_ON(1);
		वापस;
	पूर्ण

	tail = plog->tail;

	pl_recp = &(plog->plog_recs[tail]);

	स_नकल(pl_recp, pl_rec, माप(काष्ठा bfa_plog_rec_s));

	pl_recp->tv = kसमय_get_real_seconds();
	BFA_PL_LOG_REC_INCR(plog->tail);

	अगर (plog->head == plog->tail)
		BFA_PL_LOG_REC_INCR(plog->head);
पूर्ण

व्योम
bfa_plog_init(काष्ठा bfa_plog_s *plog)
अणु
	स_रखो((अक्षर *)plog, 0, माप(काष्ठा bfa_plog_s));

	स_नकल(plog->plog_sig, BFA_PL_SIG_STR, BFA_PL_SIG_LEN);
	plog->head = plog->tail = 0;
	plog->plog_enabled = 1;
पूर्ण

व्योम
bfa_plog_str(काष्ठा bfa_plog_s *plog, क्रमागत bfa_plog_mid mid,
		क्रमागत bfa_plog_eid event,
		u16 misc, अक्षर *log_str)
अणु
	काष्ठा bfa_plog_rec_s  lp;

	अगर (plog->plog_enabled) अणु
		स_रखो(&lp, 0, माप(काष्ठा bfa_plog_rec_s));
		lp.mid = mid;
		lp.eid = event;
		lp.log_type = BFA_PL_LOG_TYPE_STRING;
		lp.misc = misc;
		strlcpy(lp.log_entry.string_log, log_str,
			BFA_PL_STRING_LOG_SZ);
		lp.log_entry.string_log[BFA_PL_STRING_LOG_SZ - 1] = '\0';
		bfa_plog_add(plog, &lp);
	पूर्ण
पूर्ण

व्योम
bfa_plog_पूर्णांकarr(काष्ठा bfa_plog_s *plog, क्रमागत bfa_plog_mid mid,
		क्रमागत bfa_plog_eid event,
		u16 misc, u32 *पूर्णांकarr, u32 num_पूर्णांकs)
अणु
	काष्ठा bfa_plog_rec_s  lp;
	u32 i;

	अगर (num_पूर्णांकs > BFA_PL_INT_LOG_SZ)
		num_पूर्णांकs = BFA_PL_INT_LOG_SZ;

	अगर (plog->plog_enabled) अणु
		स_रखो(&lp, 0, माप(काष्ठा bfa_plog_rec_s));
		lp.mid = mid;
		lp.eid = event;
		lp.log_type = BFA_PL_LOG_TYPE_INT;
		lp.misc = misc;

		क्रम (i = 0; i < num_पूर्णांकs; i++)
			lp.log_entry.पूर्णांक_log[i] = पूर्णांकarr[i];

		lp.log_num_पूर्णांकs = (u8) num_पूर्णांकs;

		bfa_plog_add(plog, &lp);
	पूर्ण
पूर्ण

व्योम
bfa_plog_fchdr(काष्ठा bfa_plog_s *plog, क्रमागत bfa_plog_mid mid,
			क्रमागत bfa_plog_eid event,
			u16 misc, काष्ठा fchs_s *fchdr)
अणु
	काष्ठा bfa_plog_rec_s  lp;
	u32	*पंचांगp_पूर्णांक = (u32 *) fchdr;
	u32	पूर्णांकs[BFA_PL_INT_LOG_SZ];

	अगर (plog->plog_enabled) अणु
		स_रखो(&lp, 0, माप(काष्ठा bfa_plog_rec_s));

		पूर्णांकs[0] = पंचांगp_पूर्णांक[0];
		पूर्णांकs[1] = पंचांगp_पूर्णांक[1];
		पूर्णांकs[2] = पंचांगp_पूर्णांक[4];

		bfa_plog_पूर्णांकarr(plog, mid, event, misc, पूर्णांकs, 3);
	पूर्ण
पूर्ण

व्योम
bfa_plog_fchdr_and_pl(काष्ठा bfa_plog_s *plog, क्रमागत bfa_plog_mid mid,
		      क्रमागत bfa_plog_eid event, u16 misc, काष्ठा fchs_s *fchdr,
		      u32 pld_w0)
अणु
	काष्ठा bfa_plog_rec_s  lp;
	u32	*पंचांगp_पूर्णांक = (u32 *) fchdr;
	u32	पूर्णांकs[BFA_PL_INT_LOG_SZ];

	अगर (plog->plog_enabled) अणु
		स_रखो(&lp, 0, माप(काष्ठा bfa_plog_rec_s));

		पूर्णांकs[0] = पंचांगp_पूर्णांक[0];
		पूर्णांकs[1] = पंचांगp_पूर्णांक[1];
		पूर्णांकs[2] = पंचांगp_पूर्णांक[4];
		पूर्णांकs[3] = pld_w0;

		bfa_plog_पूर्णांकarr(plog, mid, event, misc, पूर्णांकs, 4);
	पूर्ण
पूर्ण


/*
 *  fcxp_pvt BFA FCXP निजी functions
 */

अटल व्योम
claim_fcxps_mem(काष्ठा bfa_fcxp_mod_s *mod)
अणु
	u16	i;
	काष्ठा bfa_fcxp_s *fcxp;

	fcxp = (काष्ठा bfa_fcxp_s *) bfa_mem_kva_curp(mod);
	स_रखो(fcxp, 0, माप(काष्ठा bfa_fcxp_s) * mod->num_fcxps);

	INIT_LIST_HEAD(&mod->fcxp_req_मुक्त_q);
	INIT_LIST_HEAD(&mod->fcxp_rsp_मुक्त_q);
	INIT_LIST_HEAD(&mod->fcxp_active_q);
	INIT_LIST_HEAD(&mod->fcxp_req_unused_q);
	INIT_LIST_HEAD(&mod->fcxp_rsp_unused_q);

	mod->fcxp_list = fcxp;

	क्रम (i = 0; i < mod->num_fcxps; i++) अणु
		fcxp->fcxp_mod = mod;
		fcxp->fcxp_tag = i;

		अगर (i < (mod->num_fcxps / 2)) अणु
			list_add_tail(&fcxp->qe, &mod->fcxp_req_मुक्त_q);
			fcxp->req_rsp = BFA_TRUE;
		पूर्ण अन्यथा अणु
			list_add_tail(&fcxp->qe, &mod->fcxp_rsp_मुक्त_q);
			fcxp->req_rsp = BFA_FALSE;
		पूर्ण

		bfa_reqq_winit(&fcxp->reqq_wqe, bfa_fcxp_qresume, fcxp);
		fcxp->reqq_रुकोing = BFA_FALSE;

		fcxp = fcxp + 1;
	पूर्ण

	bfa_mem_kva_curp(mod) = (व्योम *)fcxp;
पूर्ण

व्योम
bfa_fcxp_meminfo(काष्ठा bfa_iocfc_cfg_s *cfg, काष्ठा bfa_meminfo_s *minfo,
		काष्ठा bfa_s *bfa)
अणु
	काष्ठा bfa_fcxp_mod_s *fcxp_mod = BFA_FCXP_MOD(bfa);
	काष्ठा bfa_mem_kva_s *fcxp_kva = BFA_MEM_FCXP_KVA(bfa);
	काष्ठा bfa_mem_dma_s *seg_ptr;
	u16	nsegs, idx, per_seg_fcxp;
	u16	num_fcxps = cfg->fwcfg.num_fcxp_reqs;
	u32	per_fcxp_sz;

	अगर (num_fcxps == 0)
		वापस;

	अगर (cfg->drvcfg.min_cfg)
		per_fcxp_sz = 2 * BFA_FCXP_MAX_IBUF_SZ;
	अन्यथा
		per_fcxp_sz = BFA_FCXP_MAX_IBUF_SZ + BFA_FCXP_MAX_LBUF_SZ;

	/* dma memory */
	nsegs = BFI_MEM_DMA_NSEGS(num_fcxps, per_fcxp_sz);
	per_seg_fcxp = BFI_MEM_NREQS_SEG(per_fcxp_sz);

	bfa_mem_dma_seg_iter(fcxp_mod, seg_ptr, nsegs, idx) अणु
		अगर (num_fcxps >= per_seg_fcxp) अणु
			num_fcxps -= per_seg_fcxp;
			bfa_mem_dma_setup(minfo, seg_ptr,
				per_seg_fcxp * per_fcxp_sz);
		पूर्ण अन्यथा
			bfa_mem_dma_setup(minfo, seg_ptr,
				num_fcxps * per_fcxp_sz);
	पूर्ण

	/* kva memory */
	bfa_mem_kva_setup(minfo, fcxp_kva,
		cfg->fwcfg.num_fcxp_reqs * माप(काष्ठा bfa_fcxp_s));
पूर्ण

व्योम
bfa_fcxp_attach(काष्ठा bfa_s *bfa, व्योम *bfad, काष्ठा bfa_iocfc_cfg_s *cfg,
		काष्ठा bfa_pcidev_s *pcidev)
अणु
	काष्ठा bfa_fcxp_mod_s *mod = BFA_FCXP_MOD(bfa);

	mod->bfa = bfa;
	mod->num_fcxps = cfg->fwcfg.num_fcxp_reqs;

	/*
	 * Initialize FCXP request and response payload sizes.
	 */
	mod->req_pld_sz = mod->rsp_pld_sz = BFA_FCXP_MAX_IBUF_SZ;
	अगर (!cfg->drvcfg.min_cfg)
		mod->rsp_pld_sz = BFA_FCXP_MAX_LBUF_SZ;

	INIT_LIST_HEAD(&mod->req_रुको_q);
	INIT_LIST_HEAD(&mod->rsp_रुको_q);

	claim_fcxps_mem(mod);
पूर्ण

व्योम
bfa_fcxp_iocdisable(काष्ठा bfa_s *bfa)
अणु
	काष्ठा bfa_fcxp_mod_s *mod = BFA_FCXP_MOD(bfa);
	काष्ठा bfa_fcxp_s *fcxp;
	काष्ठा list_head	      *qe, *qen;

	/* Enqueue unused fcxp resources to मुक्त_q */
	list_splice_tail_init(&mod->fcxp_req_unused_q, &mod->fcxp_req_मुक्त_q);
	list_splice_tail_init(&mod->fcxp_rsp_unused_q, &mod->fcxp_rsp_मुक्त_q);

	list_क्रम_each_safe(qe, qen, &mod->fcxp_active_q) अणु
		fcxp = (काष्ठा bfa_fcxp_s *) qe;
		अगर (fcxp->caller == शून्य) अणु
			fcxp->send_cbfn(fcxp->caller, fcxp, fcxp->send_cbarg,
					BFA_STATUS_IOC_FAILURE, 0, 0, शून्य);
			bfa_fcxp_मुक्त(fcxp);
		पूर्ण अन्यथा अणु
			fcxp->rsp_status = BFA_STATUS_IOC_FAILURE;
			bfa_cb_queue(bfa, &fcxp->hcb_qe,
				     __bfa_fcxp_send_cbfn, fcxp);
		पूर्ण
	पूर्ण
पूर्ण

अटल काष्ठा bfa_fcxp_s *
bfa_fcxp_get(काष्ठा bfa_fcxp_mod_s *fm, bfa_boolean_t req)
अणु
	काष्ठा bfa_fcxp_s *fcxp;

	अगर (req)
		bfa_q_deq(&fm->fcxp_req_मुक्त_q, &fcxp);
	अन्यथा
		bfa_q_deq(&fm->fcxp_rsp_मुक्त_q, &fcxp);

	अगर (fcxp)
		list_add_tail(&fcxp->qe, &fm->fcxp_active_q);

	वापस fcxp;
पूर्ण

अटल व्योम
bfa_fcxp_init_reqrsp(काष्ठा bfa_fcxp_s *fcxp,
	       काष्ठा bfa_s *bfa,
	       u8 *use_ibuf,
	       u32 *nr_sgles,
	       bfa_fcxp_get_sgaddr_t *r_sga_cbfn,
	       bfa_fcxp_get_sglen_t *r_sglen_cbfn,
	       काष्ठा list_head *r_sgpg_q,
	       पूर्णांक n_sgles,
	       bfa_fcxp_get_sgaddr_t sga_cbfn,
	       bfa_fcxp_get_sglen_t sglen_cbfn)
अणु

	WARN_ON(bfa == शून्य);

	bfa_trc(bfa, fcxp->fcxp_tag);

	अगर (n_sgles == 0) अणु
		*use_ibuf = 1;
	पूर्ण अन्यथा अणु
		WARN_ON(*sga_cbfn == शून्य);
		WARN_ON(*sglen_cbfn == शून्य);

		*use_ibuf = 0;
		*r_sga_cbfn = sga_cbfn;
		*r_sglen_cbfn = sglen_cbfn;

		*nr_sgles = n_sgles;

		/*
		 * alloc required sgpgs
		 */
		अगर (n_sgles > BFI_SGE_INLINE)
			WARN_ON(1);
	पूर्ण

पूर्ण

अटल व्योम
bfa_fcxp_init(काष्ठा bfa_fcxp_s *fcxp,
	       व्योम *caller, काष्ठा bfa_s *bfa, पूर्णांक nreq_sgles,
	       पूर्णांक nrsp_sgles, bfa_fcxp_get_sgaddr_t req_sga_cbfn,
	       bfa_fcxp_get_sglen_t req_sglen_cbfn,
	       bfa_fcxp_get_sgaddr_t rsp_sga_cbfn,
	       bfa_fcxp_get_sglen_t rsp_sglen_cbfn)
अणु

	WARN_ON(bfa == शून्य);

	bfa_trc(bfa, fcxp->fcxp_tag);

	fcxp->caller = caller;

	bfa_fcxp_init_reqrsp(fcxp, bfa,
		&fcxp->use_ireqbuf, &fcxp->nreq_sgles, &fcxp->req_sga_cbfn,
		&fcxp->req_sglen_cbfn, &fcxp->req_sgpg_q,
		nreq_sgles, req_sga_cbfn, req_sglen_cbfn);

	bfa_fcxp_init_reqrsp(fcxp, bfa,
		&fcxp->use_irspbuf, &fcxp->nrsp_sgles, &fcxp->rsp_sga_cbfn,
		&fcxp->rsp_sglen_cbfn, &fcxp->rsp_sgpg_q,
		nrsp_sgles, rsp_sga_cbfn, rsp_sglen_cbfn);

पूर्ण

अटल व्योम
bfa_fcxp_put(काष्ठा bfa_fcxp_s *fcxp)
अणु
	काष्ठा bfa_fcxp_mod_s *mod = fcxp->fcxp_mod;
	काष्ठा bfa_fcxp_wqe_s *wqe;

	अगर (fcxp->req_rsp)
		bfa_q_deq(&mod->req_रुको_q, &wqe);
	अन्यथा
		bfa_q_deq(&mod->rsp_रुको_q, &wqe);

	अगर (wqe) अणु
		bfa_trc(mod->bfa, fcxp->fcxp_tag);

		bfa_fcxp_init(fcxp, wqe->caller, wqe->bfa, wqe->nreq_sgles,
			wqe->nrsp_sgles, wqe->req_sga_cbfn,
			wqe->req_sglen_cbfn, wqe->rsp_sga_cbfn,
			wqe->rsp_sglen_cbfn);

		wqe->alloc_cbfn(wqe->alloc_cbarg, fcxp);
		वापस;
	पूर्ण

	WARN_ON(!bfa_q_is_on_q(&mod->fcxp_active_q, fcxp));
	list_del(&fcxp->qe);

	अगर (fcxp->req_rsp)
		list_add_tail(&fcxp->qe, &mod->fcxp_req_मुक्त_q);
	अन्यथा
		list_add_tail(&fcxp->qe, &mod->fcxp_rsp_मुक्त_q);
पूर्ण

अटल व्योम
bfa_fcxp_null_comp(व्योम *bfad_fcxp, काष्ठा bfa_fcxp_s *fcxp, व्योम *cbarg,
		   bfa_status_t req_status, u32 rsp_len,
		   u32 resid_len, काष्ठा fchs_s *rsp_fchs)
अणु
	/* discarded fcxp completion */
पूर्ण

अटल व्योम
__bfa_fcxp_send_cbfn(व्योम *cbarg, bfa_boolean_t complete)
अणु
	काष्ठा bfa_fcxp_s *fcxp = cbarg;

	अगर (complete) अणु
		fcxp->send_cbfn(fcxp->caller, fcxp, fcxp->send_cbarg,
				fcxp->rsp_status, fcxp->rsp_len,
				fcxp->residue_len, &fcxp->rsp_fchs);
	पूर्ण अन्यथा अणु
		bfa_fcxp_मुक्त(fcxp);
	पूर्ण
पूर्ण

अटल व्योम
hal_fcxp_send_comp(काष्ठा bfa_s *bfa, काष्ठा bfi_fcxp_send_rsp_s *fcxp_rsp)
अणु
	काष्ठा bfa_fcxp_mod_s	*mod = BFA_FCXP_MOD(bfa);
	काष्ठा bfa_fcxp_s	*fcxp;
	u16		fcxp_tag = be16_to_cpu(fcxp_rsp->fcxp_tag);

	bfa_trc(bfa, fcxp_tag);

	fcxp_rsp->rsp_len = be32_to_cpu(fcxp_rsp->rsp_len);

	/*
	 * @toकरो f/w should not set residue to non-0 when everything
	 *	 is received.
	 */
	अगर (fcxp_rsp->req_status == BFA_STATUS_OK)
		fcxp_rsp->residue_len = 0;
	अन्यथा
		fcxp_rsp->residue_len = be32_to_cpu(fcxp_rsp->residue_len);

	fcxp = BFA_FCXP_FROM_TAG(mod, fcxp_tag);

	WARN_ON(fcxp->send_cbfn == शून्य);

	hal_fcxp_rx_plog(mod->bfa, fcxp, fcxp_rsp);

	अगर (fcxp->send_cbfn != शून्य) अणु
		bfa_trc(mod->bfa, (शून्य == fcxp->caller));
		अगर (fcxp->caller == शून्य) अणु
			fcxp->send_cbfn(fcxp->caller, fcxp, fcxp->send_cbarg,
					fcxp_rsp->req_status, fcxp_rsp->rsp_len,
					fcxp_rsp->residue_len, &fcxp_rsp->fchs);
			/*
			 * fcxp स्वतःmatically मुक्तd on वापस from the callback
			 */
			bfa_fcxp_मुक्त(fcxp);
		पूर्ण अन्यथा अणु
			fcxp->rsp_status = fcxp_rsp->req_status;
			fcxp->rsp_len = fcxp_rsp->rsp_len;
			fcxp->residue_len = fcxp_rsp->residue_len;
			fcxp->rsp_fchs = fcxp_rsp->fchs;

			bfa_cb_queue(bfa, &fcxp->hcb_qe,
					__bfa_fcxp_send_cbfn, fcxp);
		पूर्ण
	पूर्ण अन्यथा अणु
		bfa_trc(bfa, (शून्य == fcxp->send_cbfn));
	पूर्ण
पूर्ण

अटल व्योम
hal_fcxp_tx_plog(काष्ठा bfa_s *bfa, u32 reqlen, काष्ठा bfa_fcxp_s *fcxp,
		 काष्ठा fchs_s *fchs)
अणु
	/*
	 * TODO: TX ox_id
	 */
	अगर (reqlen > 0) अणु
		अगर (fcxp->use_ireqbuf) अणु
			u32	pld_w0 =
				*((u32 *) BFA_FCXP_REQ_PLD(fcxp));

			bfa_plog_fchdr_and_pl(bfa->plog, BFA_PL_MID_HAL_FCXP,
					BFA_PL_EID_TX,
					reqlen + माप(काष्ठा fchs_s), fchs,
					pld_w0);
		पूर्ण अन्यथा अणु
			bfa_plog_fchdr(bfa->plog, BFA_PL_MID_HAL_FCXP,
					BFA_PL_EID_TX,
					reqlen + माप(काष्ठा fchs_s),
					fchs);
		पूर्ण
	पूर्ण अन्यथा अणु
		bfa_plog_fchdr(bfa->plog, BFA_PL_MID_HAL_FCXP, BFA_PL_EID_TX,
			       reqlen + माप(काष्ठा fchs_s), fchs);
	पूर्ण
पूर्ण

अटल व्योम
hal_fcxp_rx_plog(काष्ठा bfa_s *bfa, काष्ठा bfa_fcxp_s *fcxp,
		 काष्ठा bfi_fcxp_send_rsp_s *fcxp_rsp)
अणु
	अगर (fcxp_rsp->rsp_len > 0) अणु
		अगर (fcxp->use_irspbuf) अणु
			u32	pld_w0 =
				*((u32 *) BFA_FCXP_RSP_PLD(fcxp));

			bfa_plog_fchdr_and_pl(bfa->plog, BFA_PL_MID_HAL_FCXP,
					      BFA_PL_EID_RX,
					      (u16) fcxp_rsp->rsp_len,
					      &fcxp_rsp->fchs, pld_w0);
		पूर्ण अन्यथा अणु
			bfa_plog_fchdr(bfa->plog, BFA_PL_MID_HAL_FCXP,
				       BFA_PL_EID_RX,
				       (u16) fcxp_rsp->rsp_len,
				       &fcxp_rsp->fchs);
		पूर्ण
	पूर्ण अन्यथा अणु
		bfa_plog_fchdr(bfa->plog, BFA_PL_MID_HAL_FCXP, BFA_PL_EID_RX,
			       (u16) fcxp_rsp->rsp_len, &fcxp_rsp->fchs);
	पूर्ण
पूर्ण

/*
 * Handler to resume sending fcxp when space in available in cpe queue.
 */
अटल व्योम
bfa_fcxp_qresume(व्योम *cbarg)
अणु
	काष्ठा bfa_fcxp_s		*fcxp = cbarg;
	काष्ठा bfa_s			*bfa = fcxp->fcxp_mod->bfa;
	काष्ठा bfi_fcxp_send_req_s	*send_req;

	fcxp->reqq_रुकोing = BFA_FALSE;
	send_req = bfa_reqq_next(bfa, BFA_REQQ_FCXP);
	bfa_fcxp_queue(fcxp, send_req);
पूर्ण

/*
 * Queue fcxp send request to foimrware.
 */
अटल व्योम
bfa_fcxp_queue(काष्ठा bfa_fcxp_s *fcxp, काष्ठा bfi_fcxp_send_req_s *send_req)
अणु
	काष्ठा bfa_s			*bfa = fcxp->fcxp_mod->bfa;
	काष्ठा bfa_fcxp_req_info_s	*reqi = &fcxp->req_info;
	काष्ठा bfa_fcxp_rsp_info_s	*rspi = &fcxp->rsp_info;
	काष्ठा bfa_rport_s		*rport = reqi->bfa_rport;

	bfi_h2i_set(send_req->mh, BFI_MC_FCXP, BFI_FCXP_H2I_SEND_REQ,
		    bfa_fn_lpu(bfa));

	send_req->fcxp_tag = cpu_to_be16(fcxp->fcxp_tag);
	अगर (rport) अणु
		send_req->rport_fw_hndl = rport->fw_handle;
		send_req->max_frmsz = cpu_to_be16(rport->rport_info.max_frmsz);
		अगर (send_req->max_frmsz == 0)
			send_req->max_frmsz = cpu_to_be16(FC_MAX_PDUSZ);
	पूर्ण अन्यथा अणु
		send_req->rport_fw_hndl = 0;
		send_req->max_frmsz = cpu_to_be16(FC_MAX_PDUSZ);
	पूर्ण

	send_req->vf_id = cpu_to_be16(reqi->vf_id);
	send_req->lp_fwtag = bfa_lps_get_fwtag(bfa, reqi->lp_tag);
	send_req->class = reqi->class;
	send_req->rsp_समयout = rspi->rsp_समयout;
	send_req->cts = reqi->cts;
	send_req->fchs = reqi->fchs;

	send_req->req_len = cpu_to_be32(reqi->req_tot_len);
	send_req->rsp_maxlen = cpu_to_be32(rspi->rsp_maxlen);

	/*
	 * setup req sgles
	 */
	अगर (fcxp->use_ireqbuf == 1) अणु
		bfa_alen_set(&send_req->req_alen, reqi->req_tot_len,
					BFA_FCXP_REQ_PLD_PA(fcxp));
	पूर्ण अन्यथा अणु
		अगर (fcxp->nreq_sgles > 0) अणु
			WARN_ON(fcxp->nreq_sgles != 1);
			bfa_alen_set(&send_req->req_alen, reqi->req_tot_len,
				fcxp->req_sga_cbfn(fcxp->caller, 0));
		पूर्ण अन्यथा अणु
			WARN_ON(reqi->req_tot_len != 0);
			bfa_alen_set(&send_req->rsp_alen, 0, 0);
		पूर्ण
	पूर्ण

	/*
	 * setup rsp sgles
	 */
	अगर (fcxp->use_irspbuf == 1) अणु
		WARN_ON(rspi->rsp_maxlen > BFA_FCXP_MAX_LBUF_SZ);

		bfa_alen_set(&send_req->rsp_alen, rspi->rsp_maxlen,
					BFA_FCXP_RSP_PLD_PA(fcxp));
	पूर्ण अन्यथा अणु
		अगर (fcxp->nrsp_sgles > 0) अणु
			WARN_ON(fcxp->nrsp_sgles != 1);
			bfa_alen_set(&send_req->rsp_alen, rspi->rsp_maxlen,
				fcxp->rsp_sga_cbfn(fcxp->caller, 0));

		पूर्ण अन्यथा अणु
			WARN_ON(rspi->rsp_maxlen != 0);
			bfa_alen_set(&send_req->rsp_alen, 0, 0);
		पूर्ण
	पूर्ण

	hal_fcxp_tx_plog(bfa, reqi->req_tot_len, fcxp, &reqi->fchs);

	bfa_reqq_produce(bfa, BFA_REQQ_FCXP, send_req->mh);

	bfa_trc(bfa, bfa_reqq_pi(bfa, BFA_REQQ_FCXP));
	bfa_trc(bfa, bfa_reqq_ci(bfa, BFA_REQQ_FCXP));
पूर्ण

/*
 * Allocate an FCXP instance to send a response or to send a request
 * that has a response. Request/response buffers are allocated by caller.
 *
 * @param[in]	bfa		BFA bfa instance
 * @param[in]	nreq_sgles	Number of SG elements required क्रम request
 *				buffer. 0, अगर fcxp पूर्णांकernal buffers are	used.
 *				Use bfa_fcxp_get_reqbuf() to get the
 *				पूर्णांकernal req buffer.
 * @param[in]	req_sgles	SG elements describing request buffer. Will be
 *				copied in by BFA and hence can be मुक्तd on
 *				वापस from this function.
 * @param[in]	get_req_sga	function ptr to be called to get a request SG
 *				Address (given the sge index).
 * @param[in]	get_req_sglen	function ptr to be called to get a request SG
 *				len (given the sge index).
 * @param[in]	get_rsp_sga	function ptr to be called to get a response SG
 *				Address (given the sge index).
 * @param[in]	get_rsp_sglen	function ptr to be called to get a response SG
 *				len (given the sge index).
 * @param[in]	req		Allocated FCXP is used to send req or rsp?
 *				request - BFA_TRUE, response - BFA_FALSE
 *
 * @वापस FCXP instance. शून्य on failure.
 */
काष्ठा bfa_fcxp_s *
bfa_fcxp_req_rsp_alloc(व्योम *caller, काष्ठा bfa_s *bfa, पूर्णांक nreq_sgles,
		पूर्णांक nrsp_sgles, bfa_fcxp_get_sgaddr_t req_sga_cbfn,
		bfa_fcxp_get_sglen_t req_sglen_cbfn,
		bfa_fcxp_get_sgaddr_t rsp_sga_cbfn,
		bfa_fcxp_get_sglen_t rsp_sglen_cbfn, bfa_boolean_t req)
अणु
	काष्ठा bfa_fcxp_s *fcxp = शून्य;

	WARN_ON(bfa == शून्य);

	fcxp = bfa_fcxp_get(BFA_FCXP_MOD(bfa), req);
	अगर (fcxp == शून्य)
		वापस शून्य;

	bfa_trc(bfa, fcxp->fcxp_tag);

	bfa_fcxp_init(fcxp, caller, bfa, nreq_sgles, nrsp_sgles, req_sga_cbfn,
			req_sglen_cbfn, rsp_sga_cbfn, rsp_sglen_cbfn);

	वापस fcxp;
पूर्ण

/*
 * Get the पूर्णांकernal request buffer poपूर्णांकer
 *
 * @param[in]	fcxp	BFA fcxp poपूर्णांकer
 *
 * @वापस		poपूर्णांकer to the पूर्णांकernal request buffer
 */
व्योम *
bfa_fcxp_get_reqbuf(काष्ठा bfa_fcxp_s *fcxp)
अणु
	काष्ठा bfa_fcxp_mod_s *mod = fcxp->fcxp_mod;
	व्योम	*reqbuf;

	WARN_ON(fcxp->use_ireqbuf != 1);
	reqbuf = bfa_mem_get_dmabuf_kva(mod, fcxp->fcxp_tag,
				mod->req_pld_sz + mod->rsp_pld_sz);
	वापस reqbuf;
पूर्ण

u32
bfa_fcxp_get_reqbufsz(काष्ठा bfa_fcxp_s *fcxp)
अणु
	काष्ठा bfa_fcxp_mod_s *mod = fcxp->fcxp_mod;

	वापस mod->req_pld_sz;
पूर्ण

/*
 * Get the पूर्णांकernal response buffer poपूर्णांकer
 *
 * @param[in]	fcxp	BFA fcxp poपूर्णांकer
 *
 * @वापस		poपूर्णांकer to the पूर्णांकernal request buffer
 */
व्योम *
bfa_fcxp_get_rspbuf(काष्ठा bfa_fcxp_s *fcxp)
अणु
	काष्ठा bfa_fcxp_mod_s *mod = fcxp->fcxp_mod;
	व्योम	*fcxp_buf;

	WARN_ON(fcxp->use_irspbuf != 1);

	fcxp_buf = bfa_mem_get_dmabuf_kva(mod, fcxp->fcxp_tag,
				mod->req_pld_sz + mod->rsp_pld_sz);

	/* fcxp_buf = req_buf + rsp_buf :- add req_buf_sz to get to rsp_buf */
	वापस ((u8 *) fcxp_buf) + mod->req_pld_sz;
पूर्ण

/*
 * Free the BFA FCXP
 *
 * @param[in]	fcxp			BFA fcxp poपूर्णांकer
 *
 * @वापस		व्योम
 */
व्योम
bfa_fcxp_मुक्त(काष्ठा bfa_fcxp_s *fcxp)
अणु
	काष्ठा bfa_fcxp_mod_s *mod = fcxp->fcxp_mod;

	WARN_ON(fcxp == शून्य);
	bfa_trc(mod->bfa, fcxp->fcxp_tag);
	bfa_fcxp_put(fcxp);
पूर्ण

/*
 * Send a FCXP request
 *
 * @param[in]	fcxp	BFA fcxp poपूर्णांकer
 * @param[in]	rport	BFA rport poपूर्णांकer. Could be left शून्य क्रम WKA rports
 * @param[in]	vf_id	भव Fabric ID
 * @param[in]	lp_tag	lport tag
 * @param[in]	cts	use Continuous sequence
 * @param[in]	cos	fc Class of Service
 * @param[in]	reqlen	request length, करोes not include FCHS length
 * @param[in]	fchs	fc Header Poपूर्णांकer. The header content will be copied
 *			in by BFA.
 *
 * @param[in]	cbfn	call back function to be called on receiving
 *								the response
 * @param[in]	cbarg	arg क्रम cbfn
 * @param[in]	rsp_समयout
 *			response समयout
 *
 * @वापस		bfa_status_t
 */
व्योम
bfa_fcxp_send(काष्ठा bfa_fcxp_s *fcxp, काष्ठा bfa_rport_s *rport,
	      u16 vf_id, u8 lp_tag, bfa_boolean_t cts, क्रमागत fc_cos cos,
	      u32 reqlen, काष्ठा fchs_s *fchs, bfa_cb_fcxp_send_t cbfn,
	      व्योम *cbarg, u32 rsp_maxlen, u8 rsp_समयout)
अणु
	काष्ठा bfa_s			*bfa  = fcxp->fcxp_mod->bfa;
	काष्ठा bfa_fcxp_req_info_s	*reqi = &fcxp->req_info;
	काष्ठा bfa_fcxp_rsp_info_s	*rspi = &fcxp->rsp_info;
	काष्ठा bfi_fcxp_send_req_s	*send_req;

	bfa_trc(bfa, fcxp->fcxp_tag);

	/*
	 * setup request/response info
	 */
	reqi->bfa_rport = rport;
	reqi->vf_id = vf_id;
	reqi->lp_tag = lp_tag;
	reqi->class = cos;
	rspi->rsp_समयout = rsp_समयout;
	reqi->cts = cts;
	reqi->fchs = *fchs;
	reqi->req_tot_len = reqlen;
	rspi->rsp_maxlen = rsp_maxlen;
	fcxp->send_cbfn = cbfn ? cbfn : bfa_fcxp_null_comp;
	fcxp->send_cbarg = cbarg;

	/*
	 * If no room in CPE queue, रुको क्रम space in request queue
	 */
	send_req = bfa_reqq_next(bfa, BFA_REQQ_FCXP);
	अगर (!send_req) अणु
		bfa_trc(bfa, fcxp->fcxp_tag);
		fcxp->reqq_रुकोing = BFA_TRUE;
		bfa_reqq_रुको(bfa, BFA_REQQ_FCXP, &fcxp->reqq_wqe);
		वापस;
	पूर्ण

	bfa_fcxp_queue(fcxp, send_req);
पूर्ण

/*
 * Abort a BFA FCXP
 *
 * @param[in]	fcxp	BFA fcxp poपूर्णांकer
 *
 * @वापस		व्योम
 */
bfa_status_t
bfa_fcxp_पात(काष्ठा bfa_fcxp_s *fcxp)
अणु
	bfa_trc(fcxp->fcxp_mod->bfa, fcxp->fcxp_tag);
	WARN_ON(1);
	वापस BFA_STATUS_OK;
पूर्ण

व्योम
bfa_fcxp_req_rsp_alloc_रुको(काष्ठा bfa_s *bfa, काष्ठा bfa_fcxp_wqe_s *wqe,
	       bfa_fcxp_alloc_cbfn_t alloc_cbfn, व्योम *alloc_cbarg,
	       व्योम *caller, पूर्णांक nreq_sgles,
	       पूर्णांक nrsp_sgles, bfa_fcxp_get_sgaddr_t req_sga_cbfn,
	       bfa_fcxp_get_sglen_t req_sglen_cbfn,
	       bfa_fcxp_get_sgaddr_t rsp_sga_cbfn,
	       bfa_fcxp_get_sglen_t rsp_sglen_cbfn, bfa_boolean_t req)
अणु
	काष्ठा bfa_fcxp_mod_s *mod = BFA_FCXP_MOD(bfa);

	अगर (req)
		WARN_ON(!list_empty(&mod->fcxp_req_मुक्त_q));
	अन्यथा
		WARN_ON(!list_empty(&mod->fcxp_rsp_मुक्त_q));

	wqe->alloc_cbfn = alloc_cbfn;
	wqe->alloc_cbarg = alloc_cbarg;
	wqe->caller = caller;
	wqe->bfa = bfa;
	wqe->nreq_sgles = nreq_sgles;
	wqe->nrsp_sgles = nrsp_sgles;
	wqe->req_sga_cbfn = req_sga_cbfn;
	wqe->req_sglen_cbfn = req_sglen_cbfn;
	wqe->rsp_sga_cbfn = rsp_sga_cbfn;
	wqe->rsp_sglen_cbfn = rsp_sglen_cbfn;

	अगर (req)
		list_add_tail(&wqe->qe, &mod->req_रुको_q);
	अन्यथा
		list_add_tail(&wqe->qe, &mod->rsp_रुको_q);
पूर्ण

व्योम
bfa_fcxp_walloc_cancel(काष्ठा bfa_s *bfa, काष्ठा bfa_fcxp_wqe_s *wqe)
अणु
	काष्ठा bfa_fcxp_mod_s *mod = BFA_FCXP_MOD(bfa);

	WARN_ON(!bfa_q_is_on_q(&mod->req_रुको_q, wqe) ||
		!bfa_q_is_on_q(&mod->rsp_रुको_q, wqe));
	list_del(&wqe->qe);
पूर्ण

व्योम
bfa_fcxp_discard(काष्ठा bfa_fcxp_s *fcxp)
अणु
	/*
	 * If रुकोing क्रम room in request queue, cancel reqq रुको
	 * and मुक्त fcxp.
	 */
	अगर (fcxp->reqq_रुकोing) अणु
		fcxp->reqq_रुकोing = BFA_FALSE;
		bfa_reqq_wcancel(&fcxp->reqq_wqe);
		bfa_fcxp_मुक्त(fcxp);
		वापस;
	पूर्ण

	fcxp->send_cbfn = bfa_fcxp_null_comp;
पूर्ण

व्योम
bfa_fcxp_isr(काष्ठा bfa_s *bfa, काष्ठा bfi_msg_s *msg)
अणु
	चयन (msg->mhdr.msg_id) अणु
	हाल BFI_FCXP_I2H_SEND_RSP:
		hal_fcxp_send_comp(bfa, (काष्ठा bfi_fcxp_send_rsp_s *) msg);
		अवरोध;

	शेष:
		bfa_trc(bfa, msg->mhdr.msg_id);
		WARN_ON(1);
	पूर्ण
पूर्ण

u32
bfa_fcxp_get_maxrsp(काष्ठा bfa_s *bfa)
अणु
	काष्ठा bfa_fcxp_mod_s *mod = BFA_FCXP_MOD(bfa);

	वापस mod->rsp_pld_sz;
पूर्ण

व्योम
bfa_fcxp_res_recfg(काष्ठा bfa_s *bfa, u16 num_fcxp_fw)
अणु
	काष्ठा bfa_fcxp_mod_s	*mod = BFA_FCXP_MOD(bfa);
	काष्ठा list_head	*qe;
	पूर्णांक	i;

	क्रम (i = 0; i < (mod->num_fcxps - num_fcxp_fw); i++) अणु
		अगर (i < ((mod->num_fcxps - num_fcxp_fw) / 2)) अणु
			bfa_q_deq_tail(&mod->fcxp_req_मुक्त_q, &qe);
			list_add_tail(qe, &mod->fcxp_req_unused_q);
		पूर्ण अन्यथा अणु
			bfa_q_deq_tail(&mod->fcxp_rsp_मुक्त_q, &qe);
			list_add_tail(qe, &mod->fcxp_rsp_unused_q);
		पूर्ण
	पूर्ण
पूर्ण

/*
 *  BFA LPS state machine functions
 */

/*
 * Init state -- no login
 */
अटल व्योम
bfa_lps_sm_init(काष्ठा bfa_lps_s *lps, क्रमागत bfa_lps_event event)
अणु
	bfa_trc(lps->bfa, lps->bfa_tag);
	bfa_trc(lps->bfa, event);

	चयन (event) अणु
	हाल BFA_LPS_SM_LOGIN:
		अगर (bfa_reqq_full(lps->bfa, lps->reqq)) अणु
			bfa_sm_set_state(lps, bfa_lps_sm_loginरुको);
			bfa_reqq_रुको(lps->bfa, lps->reqq, &lps->wqe);
		पूर्ण अन्यथा अणु
			bfa_sm_set_state(lps, bfa_lps_sm_login);
			bfa_lps_send_login(lps);
		पूर्ण

		अगर (lps->fdisc)
			bfa_plog_str(lps->bfa->plog, BFA_PL_MID_LPS,
				BFA_PL_EID_LOGIN, 0, "FDISC Request");
		अन्यथा
			bfa_plog_str(lps->bfa->plog, BFA_PL_MID_LPS,
				BFA_PL_EID_LOGIN, 0, "FLOGI Request");
		अवरोध;

	हाल BFA_LPS_SM_LOGOUT:
		bfa_lps_logout_comp(lps);
		अवरोध;

	हाल BFA_LPS_SM_DELETE:
		bfa_lps_मुक्त(lps);
		अवरोध;

	हाल BFA_LPS_SM_RX_CVL:
	हाल BFA_LPS_SM_OFFLINE:
		अवरोध;

	हाल BFA_LPS_SM_FWRSP:
		/*
		 * Could happen when fabric detects loopback and discards
		 * the lps request. Fw will eventually sent out the समयout
		 * Just ignore
		 */
		अवरोध;
	हाल BFA_LPS_SM_SET_N2N_PID:
		/*
		 * When topology is set to loop, bfa_lps_set_n2n_pid() sends
		 * this event. Ignore this event.
		 */
		अवरोध;

	शेष:
		bfa_sm_fault(lps->bfa, event);
	पूर्ण
पूर्ण

/*
 * login is in progress -- aरुकोing response from firmware
 */
अटल व्योम
bfa_lps_sm_login(काष्ठा bfa_lps_s *lps, क्रमागत bfa_lps_event event)
अणु
	bfa_trc(lps->bfa, lps->bfa_tag);
	bfa_trc(lps->bfa, event);

	चयन (event) अणु
	हाल BFA_LPS_SM_FWRSP:
		अगर (lps->status == BFA_STATUS_OK) अणु
			bfa_sm_set_state(lps, bfa_lps_sm_online);
			अगर (lps->fdisc)
				bfa_plog_str(lps->bfa->plog, BFA_PL_MID_LPS,
					BFA_PL_EID_LOGIN, 0, "FDISC Accept");
			अन्यथा
				bfa_plog_str(lps->bfa->plog, BFA_PL_MID_LPS,
					BFA_PL_EID_LOGIN, 0, "FLOGI Accept");
			/* If N2N, send the asचिन्हित PID to FW */
			bfa_trc(lps->bfa, lps->fport);
			bfa_trc(lps->bfa, lps->lp_pid);

			अगर (!lps->fport && lps->lp_pid)
				bfa_sm_send_event(lps, BFA_LPS_SM_SET_N2N_PID);
		पूर्ण अन्यथा अणु
			bfa_sm_set_state(lps, bfa_lps_sm_init);
			अगर (lps->fdisc)
				bfa_plog_str(lps->bfa->plog, BFA_PL_MID_LPS,
					BFA_PL_EID_LOGIN, 0,
					"FDISC Fail (RJT or timeout)");
			अन्यथा
				bfa_plog_str(lps->bfa->plog, BFA_PL_MID_LPS,
					BFA_PL_EID_LOGIN, 0,
					"FLOGI Fail (RJT or timeout)");
		पूर्ण
		bfa_lps_login_comp(lps);
		अवरोध;

	हाल BFA_LPS_SM_OFFLINE:
	हाल BFA_LPS_SM_DELETE:
		bfa_sm_set_state(lps, bfa_lps_sm_init);
		अवरोध;

	हाल BFA_LPS_SM_SET_N2N_PID:
		bfa_trc(lps->bfa, lps->fport);
		bfa_trc(lps->bfa, lps->lp_pid);
		अवरोध;

	शेष:
		bfa_sm_fault(lps->bfa, event);
	पूर्ण
पूर्ण

/*
 * login pending - aरुकोing space in request queue
 */
अटल व्योम
bfa_lps_sm_loginरुको(काष्ठा bfa_lps_s *lps, क्रमागत bfa_lps_event event)
अणु
	bfa_trc(lps->bfa, lps->bfa_tag);
	bfa_trc(lps->bfa, event);

	चयन (event) अणु
	हाल BFA_LPS_SM_RESUME:
		bfa_sm_set_state(lps, bfa_lps_sm_login);
		bfa_lps_send_login(lps);
		अवरोध;

	हाल BFA_LPS_SM_OFFLINE:
	हाल BFA_LPS_SM_DELETE:
		bfa_sm_set_state(lps, bfa_lps_sm_init);
		bfa_reqq_wcancel(&lps->wqe);
		अवरोध;

	हाल BFA_LPS_SM_RX_CVL:
		/*
		 * Login was not even sent out; so when getting out
		 * of this state, it will appear like a login retry
		 * after Clear भव link
		 */
		अवरोध;

	शेष:
		bfa_sm_fault(lps->bfa, event);
	पूर्ण
पूर्ण

/*
 * login complete
 */
अटल व्योम
bfa_lps_sm_online(काष्ठा bfa_lps_s *lps, क्रमागत bfa_lps_event event)
अणु
	bfa_trc(lps->bfa, lps->bfa_tag);
	bfa_trc(lps->bfa, event);

	चयन (event) अणु
	हाल BFA_LPS_SM_LOGOUT:
		अगर (bfa_reqq_full(lps->bfa, lps->reqq)) अणु
			bfa_sm_set_state(lps, bfa_lps_sm_logoरुको);
			bfa_reqq_रुको(lps->bfa, lps->reqq, &lps->wqe);
		पूर्ण अन्यथा अणु
			bfa_sm_set_state(lps, bfa_lps_sm_logout);
			bfa_lps_send_logout(lps);
		पूर्ण
		bfa_plog_str(lps->bfa->plog, BFA_PL_MID_LPS,
			BFA_PL_EID_LOGO, 0, "Logout");
		अवरोध;

	हाल BFA_LPS_SM_RX_CVL:
		bfa_sm_set_state(lps, bfa_lps_sm_init);

		/* Let the vport module know about this event */
		bfa_lps_cvl_event(lps);
		bfa_plog_str(lps->bfa->plog, BFA_PL_MID_LPS,
			BFA_PL_EID_FIP_FCF_CVL, 0, "FCF Clear Virt. Link Rx");
		अवरोध;

	हाल BFA_LPS_SM_SET_N2N_PID:
		अगर (bfa_reqq_full(lps->bfa, lps->reqq)) अणु
			bfa_sm_set_state(lps, bfa_lps_sm_online_n2n_pid_रुको);
			bfa_reqq_रुको(lps->bfa, lps->reqq, &lps->wqe);
		पूर्ण अन्यथा
			bfa_lps_send_set_n2n_pid(lps);
		अवरोध;

	हाल BFA_LPS_SM_OFFLINE:
	हाल BFA_LPS_SM_DELETE:
		bfa_sm_set_state(lps, bfa_lps_sm_init);
		अवरोध;

	शेष:
		bfa_sm_fault(lps->bfa, event);
	पूर्ण
पूर्ण

/*
 * login complete
 */
अटल व्योम
bfa_lps_sm_online_n2n_pid_रुको(काष्ठा bfa_lps_s *lps, क्रमागत bfa_lps_event event)
अणु
	bfa_trc(lps->bfa, lps->bfa_tag);
	bfa_trc(lps->bfa, event);

	चयन (event) अणु
	हाल BFA_LPS_SM_RESUME:
		bfa_sm_set_state(lps, bfa_lps_sm_online);
		bfa_lps_send_set_n2n_pid(lps);
		अवरोध;

	हाल BFA_LPS_SM_LOGOUT:
		bfa_sm_set_state(lps, bfa_lps_sm_logoरुको);
		bfa_plog_str(lps->bfa->plog, BFA_PL_MID_LPS,
			BFA_PL_EID_LOGO, 0, "Logout");
		अवरोध;

	हाल BFA_LPS_SM_RX_CVL:
		bfa_sm_set_state(lps, bfa_lps_sm_init);
		bfa_reqq_wcancel(&lps->wqe);

		/* Let the vport module know about this event */
		bfa_lps_cvl_event(lps);
		bfa_plog_str(lps->bfa->plog, BFA_PL_MID_LPS,
			BFA_PL_EID_FIP_FCF_CVL, 0, "FCF Clear Virt. Link Rx");
		अवरोध;

	हाल BFA_LPS_SM_OFFLINE:
	हाल BFA_LPS_SM_DELETE:
		bfa_sm_set_state(lps, bfa_lps_sm_init);
		bfa_reqq_wcancel(&lps->wqe);
		अवरोध;

	शेष:
		bfa_sm_fault(lps->bfa, event);
	पूर्ण
पूर्ण

/*
 * logout in progress - aरुकोing firmware response
 */
अटल व्योम
bfa_lps_sm_logout(काष्ठा bfa_lps_s *lps, क्रमागत bfa_lps_event event)
अणु
	bfa_trc(lps->bfa, lps->bfa_tag);
	bfa_trc(lps->bfa, event);

	चयन (event) अणु
	हाल BFA_LPS_SM_FWRSP:
	हाल BFA_LPS_SM_OFFLINE:
		bfa_sm_set_state(lps, bfa_lps_sm_init);
		bfa_lps_logout_comp(lps);
		अवरोध;

	हाल BFA_LPS_SM_DELETE:
		bfa_sm_set_state(lps, bfa_lps_sm_init);
		अवरोध;

	शेष:
		bfa_sm_fault(lps->bfa, event);
	पूर्ण
पूर्ण

/*
 * logout pending -- aरुकोing space in request queue
 */
अटल व्योम
bfa_lps_sm_logoरुको(काष्ठा bfa_lps_s *lps, क्रमागत bfa_lps_event event)
अणु
	bfa_trc(lps->bfa, lps->bfa_tag);
	bfa_trc(lps->bfa, event);

	चयन (event) अणु
	हाल BFA_LPS_SM_RESUME:
		bfa_sm_set_state(lps, bfa_lps_sm_logout);
		bfa_lps_send_logout(lps);
		अवरोध;

	हाल BFA_LPS_SM_OFFLINE:
	हाल BFA_LPS_SM_DELETE:
		bfa_sm_set_state(lps, bfa_lps_sm_init);
		bfa_reqq_wcancel(&lps->wqe);
		अवरोध;

	शेष:
		bfa_sm_fault(lps->bfa, event);
	पूर्ण
पूर्ण



/*
 *  lps_pvt BFA LPS निजी functions
 */

/*
 * वापस memory requirement
 */
व्योम
bfa_lps_meminfo(काष्ठा bfa_iocfc_cfg_s *cfg, काष्ठा bfa_meminfo_s *minfo,
		काष्ठा bfa_s *bfa)
अणु
	काष्ठा bfa_mem_kva_s *lps_kva = BFA_MEM_LPS_KVA(bfa);

	अगर (cfg->drvcfg.min_cfg)
		bfa_mem_kva_setup(minfo, lps_kva,
			माप(काष्ठा bfa_lps_s) * BFA_LPS_MIN_LPORTS);
	अन्यथा
		bfa_mem_kva_setup(minfo, lps_kva,
			माप(काष्ठा bfa_lps_s) * BFA_LPS_MAX_LPORTS);
पूर्ण

/*
 * bfa module attach at initialization समय
 */
व्योम
bfa_lps_attach(काष्ठा bfa_s *bfa, व्योम *bfad, काष्ठा bfa_iocfc_cfg_s *cfg,
	काष्ठा bfa_pcidev_s *pcidev)
अणु
	काष्ठा bfa_lps_mod_s	*mod = BFA_LPS_MOD(bfa);
	काष्ठा bfa_lps_s	*lps;
	पूर्णांक			i;

	mod->num_lps = BFA_LPS_MAX_LPORTS;
	अगर (cfg->drvcfg.min_cfg)
		mod->num_lps = BFA_LPS_MIN_LPORTS;
	अन्यथा
		mod->num_lps = BFA_LPS_MAX_LPORTS;
	mod->lps_arr = lps = (काष्ठा bfa_lps_s *) bfa_mem_kva_curp(mod);

	bfa_mem_kva_curp(mod) += mod->num_lps * माप(काष्ठा bfa_lps_s);

	INIT_LIST_HEAD(&mod->lps_मुक्त_q);
	INIT_LIST_HEAD(&mod->lps_active_q);
	INIT_LIST_HEAD(&mod->lps_login_q);

	क्रम (i = 0; i < mod->num_lps; i++, lps++) अणु
		lps->bfa	= bfa;
		lps->bfa_tag	= (u8) i;
		lps->reqq	= BFA_REQQ_LPS;
		bfa_reqq_winit(&lps->wqe, bfa_lps_reqq_resume, lps);
		list_add_tail(&lps->qe, &mod->lps_मुक्त_q);
	पूर्ण
पूर्ण

/*
 * IOC in disabled state -- consider all lps offline
 */
व्योम
bfa_lps_iocdisable(काष्ठा bfa_s *bfa)
अणु
	काष्ठा bfa_lps_mod_s	*mod = BFA_LPS_MOD(bfa);
	काष्ठा bfa_lps_s	*lps;
	काष्ठा list_head		*qe, *qen;

	list_क्रम_each_safe(qe, qen, &mod->lps_active_q) अणु
		lps = (काष्ठा bfa_lps_s *) qe;
		bfa_sm_send_event(lps, BFA_LPS_SM_OFFLINE);
	पूर्ण
	list_क्रम_each_safe(qe, qen, &mod->lps_login_q) अणु
		lps = (काष्ठा bfa_lps_s *) qe;
		bfa_sm_send_event(lps, BFA_LPS_SM_OFFLINE);
	पूर्ण
	list_splice_tail_init(&mod->lps_login_q, &mod->lps_active_q);
पूर्ण

/*
 * Firmware login response
 */
अटल व्योम
bfa_lps_login_rsp(काष्ठा bfa_s *bfa, काष्ठा bfi_lps_login_rsp_s *rsp)
अणु
	काष्ठा bfa_lps_mod_s	*mod = BFA_LPS_MOD(bfa);
	काष्ठा bfa_lps_s	*lps;

	WARN_ON(rsp->bfa_tag >= mod->num_lps);
	lps = BFA_LPS_FROM_TAG(mod, rsp->bfa_tag);

	lps->status = rsp->status;
	चयन (rsp->status) अणु
	हाल BFA_STATUS_OK:
		lps->fw_tag	= rsp->fw_tag;
		lps->fport	= rsp->f_port;
		अगर (lps->fport)
			lps->lp_pid = rsp->lp_pid;
		lps->npiv_en	= rsp->npiv_en;
		lps->pr_bbcred	= be16_to_cpu(rsp->bb_credit);
		lps->pr_pwwn	= rsp->port_name;
		lps->pr_nwwn	= rsp->node_name;
		lps->auth_req	= rsp->auth_req;
		lps->lp_mac	= rsp->lp_mac;
		lps->brcd_चयन = rsp->brcd_चयन;
		lps->fcf_mac	= rsp->fcf_mac;

		अवरोध;

	हाल BFA_STATUS_FABRIC_RJT:
		lps->lsrjt_rsn = rsp->lsrjt_rsn;
		lps->lsrjt_expl = rsp->lsrjt_expl;

		अवरोध;

	हाल BFA_STATUS_EPROTOCOL:
		lps->ext_status = rsp->ext_status;

		अवरोध;

	हाल BFA_STATUS_VPORT_MAX:
		अगर (rsp->ext_status)
			bfa_lps_no_res(lps, rsp->ext_status);
		अवरोध;

	शेष:
		/* Nothing to करो with other status */
		अवरोध;
	पूर्ण

	list_del(&lps->qe);
	list_add_tail(&lps->qe, &mod->lps_active_q);
	bfa_sm_send_event(lps, BFA_LPS_SM_FWRSP);
पूर्ण

अटल व्योम
bfa_lps_no_res(काष्ठा bfa_lps_s *first_lps, u8 count)
अणु
	काष्ठा bfa_s		*bfa = first_lps->bfa;
	काष्ठा bfa_lps_mod_s	*mod = BFA_LPS_MOD(bfa);
	काष्ठा list_head	*qe, *qe_next;
	काष्ठा bfa_lps_s	*lps;

	bfa_trc(bfa, count);

	qe = bfa_q_next(first_lps);

	जबतक (count && qe) अणु
		qe_next = bfa_q_next(qe);
		lps = (काष्ठा bfa_lps_s *)qe;
		bfa_trc(bfa, lps->bfa_tag);
		lps->status = first_lps->status;
		list_del(&lps->qe);
		list_add_tail(&lps->qe, &mod->lps_active_q);
		bfa_sm_send_event(lps, BFA_LPS_SM_FWRSP);
		qe = qe_next;
		count--;
	पूर्ण
पूर्ण

/*
 * Firmware logout response
 */
अटल व्योम
bfa_lps_logout_rsp(काष्ठा bfa_s *bfa, काष्ठा bfi_lps_logout_rsp_s *rsp)
अणु
	काष्ठा bfa_lps_mod_s	*mod = BFA_LPS_MOD(bfa);
	काष्ठा bfa_lps_s	*lps;

	WARN_ON(rsp->bfa_tag >= mod->num_lps);
	lps = BFA_LPS_FROM_TAG(mod, rsp->bfa_tag);

	bfa_sm_send_event(lps, BFA_LPS_SM_FWRSP);
पूर्ण

/*
 * Firmware received a Clear भव link request (क्रम FCoE)
 */
अटल व्योम
bfa_lps_rx_cvl_event(काष्ठा bfa_s *bfa, काष्ठा bfi_lps_cvl_event_s *cvl)
अणु
	काष्ठा bfa_lps_mod_s	*mod = BFA_LPS_MOD(bfa);
	काष्ठा bfa_lps_s	*lps;

	lps = BFA_LPS_FROM_TAG(mod, cvl->bfa_tag);

	bfa_sm_send_event(lps, BFA_LPS_SM_RX_CVL);
पूर्ण

/*
 * Space is available in request queue, resume queueing request to firmware.
 */
अटल व्योम
bfa_lps_reqq_resume(व्योम *lps_arg)
अणु
	काष्ठा bfa_lps_s	*lps = lps_arg;

	bfa_sm_send_event(lps, BFA_LPS_SM_RESUME);
पूर्ण

/*
 * lps is मुक्तd -- triggered by vport delete
 */
अटल व्योम
bfa_lps_मुक्त(काष्ठा bfa_lps_s *lps)
अणु
	काष्ठा bfa_lps_mod_s	*mod = BFA_LPS_MOD(lps->bfa);

	lps->lp_pid = 0;
	list_del(&lps->qe);
	list_add_tail(&lps->qe, &mod->lps_मुक्त_q);
पूर्ण

/*
 * send login request to firmware
 */
अटल व्योम
bfa_lps_send_login(काष्ठा bfa_lps_s *lps)
अणु
	काष्ठा bfa_lps_mod_s	*mod = BFA_LPS_MOD(lps->bfa);
	काष्ठा bfi_lps_login_req_s	*m;

	m = bfa_reqq_next(lps->bfa, lps->reqq);
	WARN_ON(!m);

	bfi_h2i_set(m->mh, BFI_MC_LPS, BFI_LPS_H2I_LOGIN_REQ,
		bfa_fn_lpu(lps->bfa));

	m->bfa_tag	= lps->bfa_tag;
	m->alpa		= lps->alpa;
	m->pdu_size	= cpu_to_be16(lps->pdusz);
	m->pwwn		= lps->pwwn;
	m->nwwn		= lps->nwwn;
	m->fdisc	= lps->fdisc;
	m->auth_en	= lps->auth_en;

	bfa_reqq_produce(lps->bfa, lps->reqq, m->mh);
	list_del(&lps->qe);
	list_add_tail(&lps->qe, &mod->lps_login_q);
पूर्ण

/*
 * send logout request to firmware
 */
अटल व्योम
bfa_lps_send_logout(काष्ठा bfa_lps_s *lps)
अणु
	काष्ठा bfi_lps_logout_req_s *m;

	m = bfa_reqq_next(lps->bfa, lps->reqq);
	WARN_ON(!m);

	bfi_h2i_set(m->mh, BFI_MC_LPS, BFI_LPS_H2I_LOGOUT_REQ,
		bfa_fn_lpu(lps->bfa));

	m->fw_tag = lps->fw_tag;
	m->port_name = lps->pwwn;
	bfa_reqq_produce(lps->bfa, lps->reqq, m->mh);
पूर्ण

/*
 * send n2n pid set request to firmware
 */
अटल व्योम
bfa_lps_send_set_n2n_pid(काष्ठा bfa_lps_s *lps)
अणु
	काष्ठा bfi_lps_n2n_pid_req_s *m;

	m = bfa_reqq_next(lps->bfa, lps->reqq);
	WARN_ON(!m);

	bfi_h2i_set(m->mh, BFI_MC_LPS, BFI_LPS_H2I_N2N_PID_REQ,
		bfa_fn_lpu(lps->bfa));

	m->fw_tag = lps->fw_tag;
	m->lp_pid = lps->lp_pid;
	bfa_reqq_produce(lps->bfa, lps->reqq, m->mh);
पूर्ण

/*
 * Indirect login completion handler क्रम non-fcs
 */
अटल व्योम
bfa_lps_login_comp_cb(व्योम *arg, bfa_boolean_t complete)
अणु
	काष्ठा bfa_lps_s *lps	= arg;

	अगर (!complete)
		वापस;

	अगर (lps->fdisc)
		bfa_cb_lps_fdisc_comp(lps->bfa->bfad, lps->uarg, lps->status);
	अन्यथा
		bfa_cb_lps_flogi_comp(lps->bfa->bfad, lps->uarg, lps->status);
पूर्ण

/*
 * Login completion handler -- direct call क्रम fcs, queue क्रम others
 */
अटल व्योम
bfa_lps_login_comp(काष्ठा bfa_lps_s *lps)
अणु
	अगर (!lps->bfa->fcs) अणु
		bfa_cb_queue(lps->bfa, &lps->hcb_qe, bfa_lps_login_comp_cb,
			lps);
		वापस;
	पूर्ण

	अगर (lps->fdisc)
		bfa_cb_lps_fdisc_comp(lps->bfa->bfad, lps->uarg, lps->status);
	अन्यथा
		bfa_cb_lps_flogi_comp(lps->bfa->bfad, lps->uarg, lps->status);
पूर्ण

/*
 * Indirect logout completion handler क्रम non-fcs
 */
अटल व्योम
bfa_lps_logout_comp_cb(व्योम *arg, bfa_boolean_t complete)
अणु
	काष्ठा bfa_lps_s *lps	= arg;

	अगर (!complete)
		वापस;

	अगर (lps->fdisc)
		bfa_cb_lps_fdisclogo_comp(lps->bfa->bfad, lps->uarg);
	अन्यथा
		bfa_cb_lps_flogo_comp(lps->bfa->bfad, lps->uarg);
पूर्ण

/*
 * Logout completion handler -- direct call क्रम fcs, queue क्रम others
 */
अटल व्योम
bfa_lps_logout_comp(काष्ठा bfa_lps_s *lps)
अणु
	अगर (!lps->bfa->fcs) अणु
		bfa_cb_queue(lps->bfa, &lps->hcb_qe, bfa_lps_logout_comp_cb,
			lps);
		वापस;
	पूर्ण
	अगर (lps->fdisc)
		bfa_cb_lps_fdisclogo_comp(lps->bfa->bfad, lps->uarg);
पूर्ण

/*
 * Clear भव link completion handler क्रम non-fcs
 */
अटल व्योम
bfa_lps_cvl_event_cb(व्योम *arg, bfa_boolean_t complete)
अणु
	काष्ठा bfa_lps_s *lps	= arg;

	अगर (!complete)
		वापस;

	/* Clear भव link to base port will result in link करोwn */
	अगर (lps->fdisc)
		bfa_cb_lps_cvl_event(lps->bfa->bfad, lps->uarg);
पूर्ण

/*
 * Received Clear भव link event --direct call क्रम fcs,
 * queue क्रम others
 */
अटल व्योम
bfa_lps_cvl_event(काष्ठा bfa_lps_s *lps)
अणु
	अगर (!lps->bfa->fcs) अणु
		bfa_cb_queue(lps->bfa, &lps->hcb_qe, bfa_lps_cvl_event_cb,
			lps);
		वापस;
	पूर्ण

	/* Clear भव link to base port will result in link करोwn */
	अगर (lps->fdisc)
		bfa_cb_lps_cvl_event(lps->bfa->bfad, lps->uarg);
पूर्ण



/*
 *  lps_खुला BFA LPS खुला functions
 */

u32
bfa_lps_get_max_vport(काष्ठा bfa_s *bfa)
अणु
	अगर (bfa_ioc_devid(&bfa->ioc) == BFA_PCI_DEVICE_ID_CT)
		वापस BFA_LPS_MAX_VPORTS_SUPP_CT;
	अन्यथा
		वापस BFA_LPS_MAX_VPORTS_SUPP_CB;
पूर्ण

/*
 * Allocate a lport srvice tag.
 */
काष्ठा bfa_lps_s  *
bfa_lps_alloc(काष्ठा bfa_s *bfa)
अणु
	काष्ठा bfa_lps_mod_s	*mod = BFA_LPS_MOD(bfa);
	काष्ठा bfa_lps_s	*lps = शून्य;

	bfa_q_deq(&mod->lps_मुक्त_q, &lps);

	अगर (lps == शून्य)
		वापस शून्य;

	list_add_tail(&lps->qe, &mod->lps_active_q);

	bfa_sm_set_state(lps, bfa_lps_sm_init);
	वापस lps;
पूर्ण

/*
 * Free lport service tag. This can be called anyसमय after an alloc.
 * No need to रुको क्रम any pending login/logout completions.
 */
व्योम
bfa_lps_delete(काष्ठा bfa_lps_s *lps)
अणु
	bfa_sm_send_event(lps, BFA_LPS_SM_DELETE);
पूर्ण

/*
 * Initiate a lport login.
 */
व्योम
bfa_lps_flogi(काष्ठा bfa_lps_s *lps, व्योम *uarg, u8 alpa, u16 pdusz,
	wwn_t pwwn, wwn_t nwwn, bfa_boolean_t auth_en)
अणु
	lps->uarg	= uarg;
	lps->alpa	= alpa;
	lps->pdusz	= pdusz;
	lps->pwwn	= pwwn;
	lps->nwwn	= nwwn;
	lps->fdisc	= BFA_FALSE;
	lps->auth_en	= auth_en;
	bfa_sm_send_event(lps, BFA_LPS_SM_LOGIN);
पूर्ण

/*
 * Initiate a lport fdisc login.
 */
व्योम
bfa_lps_fdisc(काष्ठा bfa_lps_s *lps, व्योम *uarg, u16 pdusz, wwn_t pwwn,
	wwn_t nwwn)
अणु
	lps->uarg	= uarg;
	lps->alpa	= 0;
	lps->pdusz	= pdusz;
	lps->pwwn	= pwwn;
	lps->nwwn	= nwwn;
	lps->fdisc	= BFA_TRUE;
	lps->auth_en	= BFA_FALSE;
	bfa_sm_send_event(lps, BFA_LPS_SM_LOGIN);
पूर्ण


/*
 * Initiate a lport FDSIC logout.
 */
व्योम
bfa_lps_fdisclogo(काष्ठा bfa_lps_s *lps)
अणु
	bfa_sm_send_event(lps, BFA_LPS_SM_LOGOUT);
पूर्ण

u8
bfa_lps_get_fwtag(काष्ठा bfa_s *bfa, u8 lp_tag)
अणु
	काष्ठा bfa_lps_mod_s    *mod = BFA_LPS_MOD(bfa);

	वापस BFA_LPS_FROM_TAG(mod, lp_tag)->fw_tag;
पूर्ण

/*
 * Return lport services tag given the pid
 */
u8
bfa_lps_get_tag_from_pid(काष्ठा bfa_s *bfa, u32 pid)
अणु
	काष्ठा bfa_lps_mod_s	*mod = BFA_LPS_MOD(bfa);
	काष्ठा bfa_lps_s	*lps;
	पूर्णांक			i;

	क्रम (i = 0, lps = mod->lps_arr; i < mod->num_lps; i++, lps++) अणु
		अगर (lps->lp_pid == pid)
			वापस lps->bfa_tag;
	पूर्ण

	/* Return base port tag anyway */
	वापस 0;
पूर्ण


/*
 * वापस port id asचिन्हित to the base lport
 */
u32
bfa_lps_get_base_pid(काष्ठा bfa_s *bfa)
अणु
	काष्ठा bfa_lps_mod_s	*mod = BFA_LPS_MOD(bfa);

	वापस BFA_LPS_FROM_TAG(mod, 0)->lp_pid;
पूर्ण

/*
 * Set PID in हाल of n2n (which is asचिन्हित during PLOGI)
 */
व्योम
bfa_lps_set_n2n_pid(काष्ठा bfa_lps_s *lps, uपूर्णांक32_t n2n_pid)
अणु
	bfa_trc(lps->bfa, lps->bfa_tag);
	bfa_trc(lps->bfa, n2n_pid);

	lps->lp_pid = n2n_pid;
	bfa_sm_send_event(lps, BFA_LPS_SM_SET_N2N_PID);
पूर्ण

/*
 * LPS firmware message class handler.
 */
व्योम
bfa_lps_isr(काष्ठा bfa_s *bfa, काष्ठा bfi_msg_s *m)
अणु
	जोड़ bfi_lps_i2h_msg_u	msg;

	bfa_trc(bfa, m->mhdr.msg_id);
	msg.msg = m;

	चयन (m->mhdr.msg_id) अणु
	हाल BFI_LPS_I2H_LOGIN_RSP:
		bfa_lps_login_rsp(bfa, msg.login_rsp);
		अवरोध;

	हाल BFI_LPS_I2H_LOGOUT_RSP:
		bfa_lps_logout_rsp(bfa, msg.logout_rsp);
		अवरोध;

	हाल BFI_LPS_I2H_CVL_EVENT:
		bfa_lps_rx_cvl_event(bfa, msg.cvl_event);
		अवरोध;

	शेष:
		bfa_trc(bfa, m->mhdr.msg_id);
		WARN_ON(1);
	पूर्ण
पूर्ण

अटल व्योम
bfa_fcport_aen_post(काष्ठा bfa_fcport_s *fcport, क्रमागत bfa_port_aen_event event)
अणु
	काष्ठा bfad_s *bfad = (काष्ठा bfad_s *)fcport->bfa->bfad;
	काष्ठा bfa_aen_entry_s  *aen_entry;

	bfad_get_aen_entry(bfad, aen_entry);
	अगर (!aen_entry)
		वापस;

	aen_entry->aen_data.port.ioc_type = bfa_get_type(fcport->bfa);
	aen_entry->aen_data.port.pwwn = fcport->pwwn;

	/* Send the AEN notअगरication */
	bfad_im_post_venकरोr_event(aen_entry, bfad, ++fcport->bfa->bfa_aen_seq,
				  BFA_AEN_CAT_PORT, event);
पूर्ण

/*
 * FC PORT state machine functions
 */
अटल व्योम
bfa_fcport_sm_uninit(काष्ठा bfa_fcport_s *fcport,
			क्रमागत bfa_fcport_sm_event event)
अणु
	bfa_trc(fcport->bfa, event);

	चयन (event) अणु
	हाल BFA_FCPORT_SM_START:
		/*
		 * Start event after IOC is configured and BFA is started.
		 */
		fcport->use_flash_cfg = BFA_TRUE;

		अगर (bfa_fcport_send_enable(fcport)) अणु
			bfa_trc(fcport->bfa, BFA_TRUE);
			bfa_sm_set_state(fcport, bfa_fcport_sm_enabling);
		पूर्ण अन्यथा अणु
			bfa_trc(fcport->bfa, BFA_FALSE);
			bfa_sm_set_state(fcport,
					bfa_fcport_sm_enabling_qरुको);
		पूर्ण
		अवरोध;

	हाल BFA_FCPORT_SM_ENABLE:
		/*
		 * Port is persistently configured to be in enabled state. Do
		 * not change state. Port enabling is करोne when START event is
		 * received.
		 */
		अवरोध;

	हाल BFA_FCPORT_SM_DISABLE:
		/*
		 * If a port is persistently configured to be disabled, the
		 * first event will a port disable request.
		 */
		bfa_sm_set_state(fcport, bfa_fcport_sm_disabled);
		अवरोध;

	हाल BFA_FCPORT_SM_HWFAIL:
		bfa_sm_set_state(fcport, bfa_fcport_sm_iocकरोwn);
		अवरोध;

	शेष:
		bfa_sm_fault(fcport->bfa, event);
	पूर्ण
पूर्ण

अटल व्योम
bfa_fcport_sm_enabling_qरुको(काष्ठा bfa_fcport_s *fcport,
				क्रमागत bfa_fcport_sm_event event)
अणु
	अक्षर pwwn_buf[BFA_STRING_32];
	काष्ठा bfad_s *bfad = (काष्ठा bfad_s *)fcport->bfa->bfad;
	bfa_trc(fcport->bfa, event);

	चयन (event) अणु
	हाल BFA_FCPORT_SM_QRESUME:
		bfa_sm_set_state(fcport, bfa_fcport_sm_enabling);
		bfa_fcport_send_enable(fcport);
		अवरोध;

	हाल BFA_FCPORT_SM_STOP:
		bfa_reqq_wcancel(&fcport->reqq_रुको);
		bfa_sm_set_state(fcport, bfa_fcport_sm_stopped);
		अवरोध;

	हाल BFA_FCPORT_SM_ENABLE:
		/*
		 * Alपढ़ोy enable is in progress.
		 */
		अवरोध;

	हाल BFA_FCPORT_SM_DISABLE:
		/*
		 * Just send disable request to firmware when room becomes
		 * available in request queue.
		 */
		bfa_sm_set_state(fcport, bfa_fcport_sm_disabled);
		bfa_reqq_wcancel(&fcport->reqq_रुको);
		bfa_plog_str(fcport->bfa->plog, BFA_PL_MID_HAL,
				BFA_PL_EID_PORT_DISABLE, 0, "Port Disable");
		wwn2str(pwwn_buf, fcport->pwwn);
		BFA_LOG(KERN_INFO, bfad, bfa_log_level,
			"Base port disabled: WWN = %s\n", pwwn_buf);
		bfa_fcport_aen_post(fcport, BFA_PORT_AEN_DISABLE);
		अवरोध;

	हाल BFA_FCPORT_SM_LINKUP:
	हाल BFA_FCPORT_SM_LINKDOWN:
		/*
		 * Possible to get link events when करोing back-to-back
		 * enable/disables.
		 */
		अवरोध;

	हाल BFA_FCPORT_SM_HWFAIL:
		bfa_reqq_wcancel(&fcport->reqq_रुको);
		bfa_sm_set_state(fcport, bfa_fcport_sm_iocकरोwn);
		अवरोध;

	हाल BFA_FCPORT_SM_FAA_MISCONFIG:
		bfa_fcport_reset_linkinfo(fcport);
		bfa_fcport_aen_post(fcport, BFA_PORT_AEN_DISCONNECT);
		bfa_sm_set_state(fcport, bfa_fcport_sm_faa_misconfig);
		अवरोध;

	शेष:
		bfa_sm_fault(fcport->bfa, event);
	पूर्ण
पूर्ण

अटल व्योम
bfa_fcport_sm_enabling(काष्ठा bfa_fcport_s *fcport,
						क्रमागत bfa_fcport_sm_event event)
अणु
	अक्षर pwwn_buf[BFA_STRING_32];
	काष्ठा bfad_s *bfad = (काष्ठा bfad_s *)fcport->bfa->bfad;
	bfa_trc(fcport->bfa, event);

	चयन (event) अणु
	हाल BFA_FCPORT_SM_FWRSP:
	हाल BFA_FCPORT_SM_LINKDOWN:
		bfa_sm_set_state(fcport, bfa_fcport_sm_linkकरोwn);
		अवरोध;

	हाल BFA_FCPORT_SM_LINKUP:
		bfa_fcport_update_linkinfo(fcport);
		bfa_sm_set_state(fcport, bfa_fcport_sm_linkup);

		WARN_ON(!fcport->event_cbfn);
		bfa_fcport_scn(fcport, BFA_PORT_LINKUP, BFA_FALSE);
		अवरोध;

	हाल BFA_FCPORT_SM_ENABLE:
		/*
		 * Alपढ़ोy being enabled.
		 */
		अवरोध;

	हाल BFA_FCPORT_SM_DISABLE:
		अगर (bfa_fcport_send_disable(fcport))
			bfa_sm_set_state(fcport, bfa_fcport_sm_disabling);
		अन्यथा
			bfa_sm_set_state(fcport,
					 bfa_fcport_sm_disabling_qरुको);

		bfa_plog_str(fcport->bfa->plog, BFA_PL_MID_HAL,
				BFA_PL_EID_PORT_DISABLE, 0, "Port Disable");
		wwn2str(pwwn_buf, fcport->pwwn);
		BFA_LOG(KERN_INFO, bfad, bfa_log_level,
			"Base port disabled: WWN = %s\n", pwwn_buf);
		bfa_fcport_aen_post(fcport, BFA_PORT_AEN_DISABLE);
		अवरोध;

	हाल BFA_FCPORT_SM_STOP:
		bfa_sm_set_state(fcport, bfa_fcport_sm_stopped);
		अवरोध;

	हाल BFA_FCPORT_SM_HWFAIL:
		bfa_sm_set_state(fcport, bfa_fcport_sm_iocकरोwn);
		अवरोध;

	हाल BFA_FCPORT_SM_FAA_MISCONFIG:
		bfa_fcport_reset_linkinfo(fcport);
		bfa_fcport_aen_post(fcport, BFA_PORT_AEN_DISCONNECT);
		bfa_sm_set_state(fcport, bfa_fcport_sm_faa_misconfig);
		अवरोध;

	शेष:
		bfa_sm_fault(fcport->bfa, event);
	पूर्ण
पूर्ण

अटल व्योम
bfa_fcport_sm_linkकरोwn(काष्ठा bfa_fcport_s *fcport,
						क्रमागत bfa_fcport_sm_event event)
अणु
	काष्ठा bfi_fcport_event_s *pevent = fcport->event_arg.i2hmsg.event;
	अक्षर pwwn_buf[BFA_STRING_32];
	काष्ठा bfad_s *bfad = (काष्ठा bfad_s *)fcport->bfa->bfad;

	bfa_trc(fcport->bfa, event);

	चयन (event) अणु
	हाल BFA_FCPORT_SM_LINKUP:
		bfa_fcport_update_linkinfo(fcport);
		bfa_sm_set_state(fcport, bfa_fcport_sm_linkup);
		WARN_ON(!fcport->event_cbfn);
		bfa_plog_str(fcport->bfa->plog, BFA_PL_MID_HAL,
				BFA_PL_EID_PORT_ST_CHANGE, 0, "Port Linkup");
		अगर (!bfa_ioc_get_fcmode(&fcport->bfa->ioc)) अणु

			bfa_trc(fcport->bfa,
				pevent->link_state.attr.vc_fcf.fcf.fipenabled);
			bfa_trc(fcport->bfa,
				pevent->link_state.attr.vc_fcf.fcf.fipfailed);

			अगर (pevent->link_state.attr.vc_fcf.fcf.fipfailed)
				bfa_plog_str(fcport->bfa->plog, BFA_PL_MID_HAL,
					BFA_PL_EID_FIP_FCF_DISC, 0,
					"FIP FCF Discovery Failed");
			अन्यथा
				bfa_plog_str(fcport->bfa->plog, BFA_PL_MID_HAL,
					BFA_PL_EID_FIP_FCF_DISC, 0,
					"FIP FCF Discovered");
		पूर्ण

		bfa_fcport_scn(fcport, BFA_PORT_LINKUP, BFA_FALSE);
		wwn2str(pwwn_buf, fcport->pwwn);
		BFA_LOG(KERN_INFO, bfad, bfa_log_level,
			"Base port online: WWN = %s\n", pwwn_buf);
		bfa_fcport_aen_post(fcport, BFA_PORT_AEN_ONLINE);

		/* If QoS is enabled and it is not online, send AEN */
		अगर (fcport->cfg.qos_enabled &&
		    fcport->qos_attr.state != BFA_QOS_ONLINE)
			bfa_fcport_aen_post(fcport, BFA_PORT_AEN_QOS_NEG);
		अवरोध;

	हाल BFA_FCPORT_SM_LINKDOWN:
		/*
		 * Possible to get link करोwn event.
		 */
		अवरोध;

	हाल BFA_FCPORT_SM_ENABLE:
		/*
		 * Alपढ़ोy enabled.
		 */
		अवरोध;

	हाल BFA_FCPORT_SM_DISABLE:
		अगर (bfa_fcport_send_disable(fcport))
			bfa_sm_set_state(fcport, bfa_fcport_sm_disabling);
		अन्यथा
			bfa_sm_set_state(fcport,
					 bfa_fcport_sm_disabling_qरुको);

		bfa_plog_str(fcport->bfa->plog, BFA_PL_MID_HAL,
				BFA_PL_EID_PORT_DISABLE, 0, "Port Disable");
		wwn2str(pwwn_buf, fcport->pwwn);
		BFA_LOG(KERN_INFO, bfad, bfa_log_level,
			"Base port disabled: WWN = %s\n", pwwn_buf);
		bfa_fcport_aen_post(fcport, BFA_PORT_AEN_DISABLE);
		अवरोध;

	हाल BFA_FCPORT_SM_STOP:
		bfa_sm_set_state(fcport, bfa_fcport_sm_stopped);
		अवरोध;

	हाल BFA_FCPORT_SM_HWFAIL:
		bfa_sm_set_state(fcport, bfa_fcport_sm_iocकरोwn);
		अवरोध;

	हाल BFA_FCPORT_SM_FAA_MISCONFIG:
		bfa_fcport_reset_linkinfo(fcport);
		bfa_fcport_aen_post(fcport, BFA_PORT_AEN_DISCONNECT);
		bfa_sm_set_state(fcport, bfa_fcport_sm_faa_misconfig);
		अवरोध;

	शेष:
		bfa_sm_fault(fcport->bfa, event);
	पूर्ण
पूर्ण

अटल व्योम
bfa_fcport_sm_linkup(काष्ठा bfa_fcport_s *fcport,
	क्रमागत bfa_fcport_sm_event event)
अणु
	अक्षर pwwn_buf[BFA_STRING_32];
	काष्ठा bfad_s *bfad = (काष्ठा bfad_s *)fcport->bfa->bfad;

	bfa_trc(fcport->bfa, event);

	चयन (event) अणु
	हाल BFA_FCPORT_SM_ENABLE:
		/*
		 * Alपढ़ोy enabled.
		 */
		अवरोध;

	हाल BFA_FCPORT_SM_DISABLE:
		अगर (bfa_fcport_send_disable(fcport))
			bfa_sm_set_state(fcport, bfa_fcport_sm_disabling);
		अन्यथा
			bfa_sm_set_state(fcport,
					 bfa_fcport_sm_disabling_qरुको);

		bfa_fcport_reset_linkinfo(fcport);
		bfa_fcport_scn(fcport, BFA_PORT_LINKDOWN, BFA_FALSE);
		bfa_plog_str(fcport->bfa->plog, BFA_PL_MID_HAL,
				BFA_PL_EID_PORT_DISABLE, 0, "Port Disable");
		wwn2str(pwwn_buf, fcport->pwwn);
		BFA_LOG(KERN_INFO, bfad, bfa_log_level,
			"Base port offline: WWN = %s\n", pwwn_buf);
		bfa_fcport_aen_post(fcport, BFA_PORT_AEN_OFFLINE);
		BFA_LOG(KERN_INFO, bfad, bfa_log_level,
			"Base port disabled: WWN = %s\n", pwwn_buf);
		bfa_fcport_aen_post(fcport, BFA_PORT_AEN_DISABLE);
		अवरोध;

	हाल BFA_FCPORT_SM_LINKDOWN:
		bfa_sm_set_state(fcport, bfa_fcport_sm_linkकरोwn);
		bfa_fcport_reset_linkinfo(fcport);
		bfa_fcport_scn(fcport, BFA_PORT_LINKDOWN, BFA_FALSE);
		bfa_plog_str(fcport->bfa->plog, BFA_PL_MID_HAL,
				BFA_PL_EID_PORT_ST_CHANGE, 0, "Port Linkdown");
		wwn2str(pwwn_buf, fcport->pwwn);
		अगर (BFA_PORT_IS_DISABLED(fcport->bfa)) अणु
			BFA_LOG(KERN_INFO, bfad, bfa_log_level,
				"Base port offline: WWN = %s\n", pwwn_buf);
			bfa_fcport_aen_post(fcport, BFA_PORT_AEN_OFFLINE);
		पूर्ण अन्यथा अणु
			BFA_LOG(KERN_ERR, bfad, bfa_log_level,
				"Base port (WWN = %s) "
				"lost fabric connectivity\n", pwwn_buf);
			bfa_fcport_aen_post(fcport, BFA_PORT_AEN_DISCONNECT);
		पूर्ण
		अवरोध;

	हाल BFA_FCPORT_SM_STOP:
		bfa_sm_set_state(fcport, bfa_fcport_sm_stopped);
		bfa_fcport_reset_linkinfo(fcport);
		wwn2str(pwwn_buf, fcport->pwwn);
		अगर (BFA_PORT_IS_DISABLED(fcport->bfa)) अणु
			BFA_LOG(KERN_INFO, bfad, bfa_log_level,
				"Base port offline: WWN = %s\n", pwwn_buf);
			bfa_fcport_aen_post(fcport, BFA_PORT_AEN_OFFLINE);
		पूर्ण अन्यथा अणु
			BFA_LOG(KERN_ERR, bfad, bfa_log_level,
				"Base port (WWN = %s) "
				"lost fabric connectivity\n", pwwn_buf);
			bfa_fcport_aen_post(fcport, BFA_PORT_AEN_DISCONNECT);
		पूर्ण
		अवरोध;

	हाल BFA_FCPORT_SM_HWFAIL:
		bfa_sm_set_state(fcport, bfa_fcport_sm_iocकरोwn);
		bfa_fcport_reset_linkinfo(fcport);
		bfa_fcport_scn(fcport, BFA_PORT_LINKDOWN, BFA_FALSE);
		wwn2str(pwwn_buf, fcport->pwwn);
		अगर (BFA_PORT_IS_DISABLED(fcport->bfa)) अणु
			BFA_LOG(KERN_INFO, bfad, bfa_log_level,
				"Base port offline: WWN = %s\n", pwwn_buf);
			bfa_fcport_aen_post(fcport, BFA_PORT_AEN_OFFLINE);
		पूर्ण अन्यथा अणु
			BFA_LOG(KERN_ERR, bfad, bfa_log_level,
				"Base port (WWN = %s) "
				"lost fabric connectivity\n", pwwn_buf);
			bfa_fcport_aen_post(fcport, BFA_PORT_AEN_DISCONNECT);
		पूर्ण
		अवरोध;

	हाल BFA_FCPORT_SM_FAA_MISCONFIG:
		bfa_fcport_reset_linkinfo(fcport);
		bfa_fcport_aen_post(fcport, BFA_PORT_AEN_DISCONNECT);
		bfa_sm_set_state(fcport, bfa_fcport_sm_faa_misconfig);
		अवरोध;

	शेष:
		bfa_sm_fault(fcport->bfa, event);
	पूर्ण
पूर्ण

अटल व्योम
bfa_fcport_sm_disabling_qरुको(काष्ठा bfa_fcport_s *fcport,
				 क्रमागत bfa_fcport_sm_event event)
अणु
	bfa_trc(fcport->bfa, event);

	चयन (event) अणु
	हाल BFA_FCPORT_SM_QRESUME:
		bfa_sm_set_state(fcport, bfa_fcport_sm_disabling);
		bfa_fcport_send_disable(fcport);
		अवरोध;

	हाल BFA_FCPORT_SM_STOP:
		bfa_sm_set_state(fcport, bfa_fcport_sm_stopped);
		bfa_reqq_wcancel(&fcport->reqq_रुको);
		अवरोध;

	हाल BFA_FCPORT_SM_ENABLE:
		bfa_sm_set_state(fcport, bfa_fcport_sm_toggling_qरुको);
		अवरोध;

	हाल BFA_FCPORT_SM_DISABLE:
		/*
		 * Alपढ़ोy being disabled.
		 */
		अवरोध;

	हाल BFA_FCPORT_SM_LINKUP:
	हाल BFA_FCPORT_SM_LINKDOWN:
		/*
		 * Possible to get link events when करोing back-to-back
		 * enable/disables.
		 */
		अवरोध;

	हाल BFA_FCPORT_SM_HWFAIL:
		bfa_sm_set_state(fcport, bfa_fcport_sm_iocfail);
		bfa_reqq_wcancel(&fcport->reqq_रुको);
		अवरोध;

	हाल BFA_FCPORT_SM_FAA_MISCONFIG:
		bfa_fcport_reset_linkinfo(fcport);
		bfa_fcport_aen_post(fcport, BFA_PORT_AEN_DISCONNECT);
		bfa_sm_set_state(fcport, bfa_fcport_sm_faa_misconfig);
		अवरोध;

	शेष:
		bfa_sm_fault(fcport->bfa, event);
	पूर्ण
पूर्ण

अटल व्योम
bfa_fcport_sm_toggling_qरुको(काष्ठा bfa_fcport_s *fcport,
				 क्रमागत bfa_fcport_sm_event event)
अणु
	bfa_trc(fcport->bfa, event);

	चयन (event) अणु
	हाल BFA_FCPORT_SM_QRESUME:
		bfa_sm_set_state(fcport, bfa_fcport_sm_disabling);
		bfa_fcport_send_disable(fcport);
		अगर (bfa_fcport_send_enable(fcport))
			bfa_sm_set_state(fcport, bfa_fcport_sm_enabling);
		अन्यथा
			bfa_sm_set_state(fcport,
					 bfa_fcport_sm_enabling_qरुको);
		अवरोध;

	हाल BFA_FCPORT_SM_STOP:
		bfa_sm_set_state(fcport, bfa_fcport_sm_stopped);
		bfa_reqq_wcancel(&fcport->reqq_रुको);
		अवरोध;

	हाल BFA_FCPORT_SM_ENABLE:
		अवरोध;

	हाल BFA_FCPORT_SM_DISABLE:
		bfa_sm_set_state(fcport, bfa_fcport_sm_disabling_qरुको);
		अवरोध;

	हाल BFA_FCPORT_SM_LINKUP:
	हाल BFA_FCPORT_SM_LINKDOWN:
		/*
		 * Possible to get link events when करोing back-to-back
		 * enable/disables.
		 */
		अवरोध;

	हाल BFA_FCPORT_SM_HWFAIL:
		bfa_sm_set_state(fcport, bfa_fcport_sm_iocfail);
		bfa_reqq_wcancel(&fcport->reqq_रुको);
		अवरोध;

	शेष:
		bfa_sm_fault(fcport->bfa, event);
	पूर्ण
पूर्ण

अटल व्योम
bfa_fcport_sm_disabling(काष्ठा bfa_fcport_s *fcport,
						क्रमागत bfa_fcport_sm_event event)
अणु
	अक्षर pwwn_buf[BFA_STRING_32];
	काष्ठा bfad_s *bfad = (काष्ठा bfad_s *)fcport->bfa->bfad;
	bfa_trc(fcport->bfa, event);

	चयन (event) अणु
	हाल BFA_FCPORT_SM_FWRSP:
		bfa_sm_set_state(fcport, bfa_fcport_sm_disabled);
		अवरोध;

	हाल BFA_FCPORT_SM_DISABLE:
		/*
		 * Alपढ़ोy being disabled.
		 */
		अवरोध;

	हाल BFA_FCPORT_SM_ENABLE:
		अगर (bfa_fcport_send_enable(fcport))
			bfa_sm_set_state(fcport, bfa_fcport_sm_enabling);
		अन्यथा
			bfa_sm_set_state(fcport,
					 bfa_fcport_sm_enabling_qरुको);

		bfa_plog_str(fcport->bfa->plog, BFA_PL_MID_HAL,
				BFA_PL_EID_PORT_ENABLE, 0, "Port Enable");
		wwn2str(pwwn_buf, fcport->pwwn);
		BFA_LOG(KERN_INFO, bfad, bfa_log_level,
			"Base port enabled: WWN = %s\n", pwwn_buf);
		bfa_fcport_aen_post(fcport, BFA_PORT_AEN_ENABLE);
		अवरोध;

	हाल BFA_FCPORT_SM_STOP:
		bfa_sm_set_state(fcport, bfa_fcport_sm_stopped);
		अवरोध;

	हाल BFA_FCPORT_SM_LINKUP:
	हाल BFA_FCPORT_SM_LINKDOWN:
		/*
		 * Possible to get link events when करोing back-to-back
		 * enable/disables.
		 */
		अवरोध;

	हाल BFA_FCPORT_SM_HWFAIL:
		bfa_sm_set_state(fcport, bfa_fcport_sm_iocfail);
		अवरोध;

	शेष:
		bfa_sm_fault(fcport->bfa, event);
	पूर्ण
पूर्ण

अटल व्योम
bfa_fcport_sm_disabled(काष्ठा bfa_fcport_s *fcport,
						क्रमागत bfa_fcport_sm_event event)
अणु
	अक्षर pwwn_buf[BFA_STRING_32];
	काष्ठा bfad_s *bfad = (काष्ठा bfad_s *)fcport->bfa->bfad;
	bfa_trc(fcport->bfa, event);

	चयन (event) अणु
	हाल BFA_FCPORT_SM_START:
		/*
		 * Ignore start event क्रम a port that is disabled.
		 */
		अवरोध;

	हाल BFA_FCPORT_SM_STOP:
		bfa_sm_set_state(fcport, bfa_fcport_sm_stopped);
		अवरोध;

	हाल BFA_FCPORT_SM_ENABLE:
		अगर (bfa_fcport_send_enable(fcport))
			bfa_sm_set_state(fcport, bfa_fcport_sm_enabling);
		अन्यथा
			bfa_sm_set_state(fcport,
					 bfa_fcport_sm_enabling_qरुको);

		bfa_plog_str(fcport->bfa->plog, BFA_PL_MID_HAL,
				BFA_PL_EID_PORT_ENABLE, 0, "Port Enable");
		wwn2str(pwwn_buf, fcport->pwwn);
		BFA_LOG(KERN_INFO, bfad, bfa_log_level,
			"Base port enabled: WWN = %s\n", pwwn_buf);
		bfa_fcport_aen_post(fcport, BFA_PORT_AEN_ENABLE);
		अवरोध;

	हाल BFA_FCPORT_SM_DISABLE:
		/*
		 * Alपढ़ोy disabled.
		 */
		अवरोध;

	हाल BFA_FCPORT_SM_HWFAIL:
		bfa_sm_set_state(fcport, bfa_fcport_sm_iocfail);
		अवरोध;

	हाल BFA_FCPORT_SM_DPORTENABLE:
		bfa_sm_set_state(fcport, bfa_fcport_sm_dport);
		अवरोध;

	हाल BFA_FCPORT_SM_DDPORTENABLE:
		bfa_sm_set_state(fcport, bfa_fcport_sm_ddport);
		अवरोध;

	शेष:
		bfa_sm_fault(fcport->bfa, event);
	पूर्ण
पूर्ण

अटल व्योम
bfa_fcport_sm_stopped(काष्ठा bfa_fcport_s *fcport,
			 क्रमागत bfa_fcport_sm_event event)
अणु
	bfa_trc(fcport->bfa, event);

	चयन (event) अणु
	हाल BFA_FCPORT_SM_START:
		अगर (bfa_fcport_send_enable(fcport))
			bfa_sm_set_state(fcport, bfa_fcport_sm_enabling);
		अन्यथा
			bfa_sm_set_state(fcport,
					 bfa_fcport_sm_enabling_qरुको);
		अवरोध;

	शेष:
		/*
		 * Ignore all other events.
		 */
		;
	पूर्ण
पूर्ण

/*
 * Port is enabled. IOC is करोwn/failed.
 */
अटल व्योम
bfa_fcport_sm_iocकरोwn(काष्ठा bfa_fcport_s *fcport,
			 क्रमागत bfa_fcport_sm_event event)
अणु
	bfa_trc(fcport->bfa, event);

	चयन (event) अणु
	हाल BFA_FCPORT_SM_START:
		अगर (bfa_fcport_send_enable(fcport))
			bfa_sm_set_state(fcport, bfa_fcport_sm_enabling);
		अन्यथा
			bfa_sm_set_state(fcport,
					 bfa_fcport_sm_enabling_qरुको);
		अवरोध;

	शेष:
		/*
		 * Ignore all events.
		 */
		;
	पूर्ण
पूर्ण

/*
 * Port is disabled. IOC is करोwn/failed.
 */
अटल व्योम
bfa_fcport_sm_iocfail(काष्ठा bfa_fcport_s *fcport,
			 क्रमागत bfa_fcport_sm_event event)
अणु
	bfa_trc(fcport->bfa, event);

	चयन (event) अणु
	हाल BFA_FCPORT_SM_START:
		bfa_sm_set_state(fcport, bfa_fcport_sm_disabled);
		अवरोध;

	हाल BFA_FCPORT_SM_ENABLE:
		bfa_sm_set_state(fcport, bfa_fcport_sm_iocकरोwn);
		अवरोध;

	शेष:
		/*
		 * Ignore all events.
		 */
		;
	पूर्ण
पूर्ण

अटल व्योम
bfa_fcport_sm_dport(काष्ठा bfa_fcport_s *fcport, क्रमागत bfa_fcport_sm_event event)
अणु
	bfa_trc(fcport->bfa, event);

	चयन (event) अणु
	हाल BFA_FCPORT_SM_DPORTENABLE:
	हाल BFA_FCPORT_SM_DISABLE:
	हाल BFA_FCPORT_SM_ENABLE:
	हाल BFA_FCPORT_SM_START:
		/*
		 * Ignore event क्रम a port that is dport
		 */
		अवरोध;

	हाल BFA_FCPORT_SM_STOP:
		bfa_sm_set_state(fcport, bfa_fcport_sm_stopped);
		अवरोध;

	हाल BFA_FCPORT_SM_HWFAIL:
		bfa_sm_set_state(fcport, bfa_fcport_sm_iocfail);
		अवरोध;

	हाल BFA_FCPORT_SM_DPORTDISABLE:
		bfa_sm_set_state(fcport, bfa_fcport_sm_disabled);
		अवरोध;

	शेष:
		bfa_sm_fault(fcport->bfa, event);
	पूर्ण
पूर्ण

अटल व्योम
bfa_fcport_sm_ddport(काष्ठा bfa_fcport_s *fcport,
			क्रमागत bfa_fcport_sm_event event)
अणु
	bfa_trc(fcport->bfa, event);

	चयन (event) अणु
	हाल BFA_FCPORT_SM_DISABLE:
	हाल BFA_FCPORT_SM_DDPORTDISABLE:
		bfa_sm_set_state(fcport, bfa_fcport_sm_disabled);
		अवरोध;

	हाल BFA_FCPORT_SM_DPORTENABLE:
	हाल BFA_FCPORT_SM_DPORTDISABLE:
	हाल BFA_FCPORT_SM_ENABLE:
	हाल BFA_FCPORT_SM_START:
		/*
		 * Ignore event क्रम a port that is ddport
		 */
		अवरोध;

	हाल BFA_FCPORT_SM_STOP:
		bfa_sm_set_state(fcport, bfa_fcport_sm_stopped);
		अवरोध;

	हाल BFA_FCPORT_SM_HWFAIL:
		bfa_sm_set_state(fcport, bfa_fcport_sm_iocfail);
		अवरोध;

	शेष:
		bfa_sm_fault(fcport->bfa, event);
	पूर्ण
पूर्ण

अटल व्योम
bfa_fcport_sm_faa_misconfig(काष्ठा bfa_fcport_s *fcport,
			    क्रमागत bfa_fcport_sm_event event)
अणु
	bfa_trc(fcport->bfa, event);

	चयन (event) अणु
	हाल BFA_FCPORT_SM_DPORTENABLE:
	हाल BFA_FCPORT_SM_ENABLE:
	हाल BFA_FCPORT_SM_START:
		/*
		 * Ignore event क्रम a port as there is FAA misconfig
		 */
		अवरोध;

	हाल BFA_FCPORT_SM_DISABLE:
		अगर (bfa_fcport_send_disable(fcport))
			bfa_sm_set_state(fcport, bfa_fcport_sm_disabling);
		अन्यथा
			bfa_sm_set_state(fcport, bfa_fcport_sm_disabling_qरुको);

		bfa_fcport_reset_linkinfo(fcport);
		bfa_fcport_scn(fcport, BFA_PORT_LINKDOWN, BFA_FALSE);
		bfa_plog_str(fcport->bfa->plog, BFA_PL_MID_HAL,
			     BFA_PL_EID_PORT_DISABLE, 0, "Port Disable");
		bfa_fcport_aen_post(fcport, BFA_PORT_AEN_DISABLE);
		अवरोध;

	हाल BFA_FCPORT_SM_STOP:
		bfa_sm_set_state(fcport, bfa_fcport_sm_stopped);
		अवरोध;

	हाल BFA_FCPORT_SM_HWFAIL:
		bfa_fcport_reset_linkinfo(fcport);
		bfa_fcport_scn(fcport, BFA_PORT_LINKDOWN, BFA_FALSE);
		bfa_sm_set_state(fcport, bfa_fcport_sm_iocकरोwn);
		अवरोध;

	शेष:
		bfa_sm_fault(fcport->bfa, event);
	पूर्ण
पूर्ण

/*
 * Link state is करोwn
 */
अटल व्योम
bfa_fcport_ln_sm_dn(काष्ठा bfa_fcport_ln_s *ln,
		क्रमागत bfa_fcport_ln_sm_event event)
अणु
	bfa_trc(ln->fcport->bfa, event);

	चयन (event) अणु
	हाल BFA_FCPORT_LN_SM_LINKUP:
		bfa_sm_set_state(ln, bfa_fcport_ln_sm_up_nf);
		bfa_fcport_queue_cb(ln, BFA_PORT_LINKUP);
		अवरोध;

	शेष:
		bfa_sm_fault(ln->fcport->bfa, event);
	पूर्ण
पूर्ण

/*
 * Link state is रुकोing क्रम करोwn notअगरication
 */
अटल व्योम
bfa_fcport_ln_sm_dn_nf(काष्ठा bfa_fcport_ln_s *ln,
		क्रमागत bfa_fcport_ln_sm_event event)
अणु
	bfa_trc(ln->fcport->bfa, event);

	चयन (event) अणु
	हाल BFA_FCPORT_LN_SM_LINKUP:
		bfa_sm_set_state(ln, bfa_fcport_ln_sm_dn_up_nf);
		अवरोध;

	हाल BFA_FCPORT_LN_SM_NOTIFICATION:
		bfa_sm_set_state(ln, bfa_fcport_ln_sm_dn);
		अवरोध;

	शेष:
		bfa_sm_fault(ln->fcport->bfa, event);
	पूर्ण
पूर्ण

/*
 * Link state is रुकोing क्रम करोwn notअगरication and there is a pending up
 */
अटल व्योम
bfa_fcport_ln_sm_dn_up_nf(काष्ठा bfa_fcport_ln_s *ln,
		क्रमागत bfa_fcport_ln_sm_event event)
अणु
	bfa_trc(ln->fcport->bfa, event);

	चयन (event) अणु
	हाल BFA_FCPORT_LN_SM_LINKDOWN:
		bfa_sm_set_state(ln, bfa_fcport_ln_sm_dn_nf);
		अवरोध;

	हाल BFA_FCPORT_LN_SM_NOTIFICATION:
		bfa_sm_set_state(ln, bfa_fcport_ln_sm_up_nf);
		bfa_fcport_queue_cb(ln, BFA_PORT_LINKUP);
		अवरोध;

	शेष:
		bfa_sm_fault(ln->fcport->bfa, event);
	पूर्ण
पूर्ण

/*
 * Link state is up
 */
अटल व्योम
bfa_fcport_ln_sm_up(काष्ठा bfa_fcport_ln_s *ln,
		क्रमागत bfa_fcport_ln_sm_event event)
अणु
	bfa_trc(ln->fcport->bfa, event);

	चयन (event) अणु
	हाल BFA_FCPORT_LN_SM_LINKDOWN:
		bfa_sm_set_state(ln, bfa_fcport_ln_sm_dn_nf);
		bfa_fcport_queue_cb(ln, BFA_PORT_LINKDOWN);
		अवरोध;

	शेष:
		bfa_sm_fault(ln->fcport->bfa, event);
	पूर्ण
पूर्ण

/*
 * Link state is रुकोing क्रम up notअगरication
 */
अटल व्योम
bfa_fcport_ln_sm_up_nf(काष्ठा bfa_fcport_ln_s *ln,
		क्रमागत bfa_fcport_ln_sm_event event)
अणु
	bfa_trc(ln->fcport->bfa, event);

	चयन (event) अणु
	हाल BFA_FCPORT_LN_SM_LINKDOWN:
		bfa_sm_set_state(ln, bfa_fcport_ln_sm_up_dn_nf);
		अवरोध;

	हाल BFA_FCPORT_LN_SM_NOTIFICATION:
		bfa_sm_set_state(ln, bfa_fcport_ln_sm_up);
		अवरोध;

	शेष:
		bfa_sm_fault(ln->fcport->bfa, event);
	पूर्ण
पूर्ण

/*
 * Link state is रुकोing क्रम up notअगरication and there is a pending करोwn
 */
अटल व्योम
bfa_fcport_ln_sm_up_dn_nf(काष्ठा bfa_fcport_ln_s *ln,
		क्रमागत bfa_fcport_ln_sm_event event)
अणु
	bfa_trc(ln->fcport->bfa, event);

	चयन (event) अणु
	हाल BFA_FCPORT_LN_SM_LINKUP:
		bfa_sm_set_state(ln, bfa_fcport_ln_sm_up_dn_up_nf);
		अवरोध;

	हाल BFA_FCPORT_LN_SM_NOTIFICATION:
		bfa_sm_set_state(ln, bfa_fcport_ln_sm_dn_nf);
		bfa_fcport_queue_cb(ln, BFA_PORT_LINKDOWN);
		अवरोध;

	शेष:
		bfa_sm_fault(ln->fcport->bfa, event);
	पूर्ण
पूर्ण

/*
 * Link state is रुकोing क्रम up notअगरication and there are pending करोwn and up
 */
अटल व्योम
bfa_fcport_ln_sm_up_dn_up_nf(काष्ठा bfa_fcport_ln_s *ln,
			क्रमागत bfa_fcport_ln_sm_event event)
अणु
	bfa_trc(ln->fcport->bfa, event);

	चयन (event) अणु
	हाल BFA_FCPORT_LN_SM_LINKDOWN:
		bfa_sm_set_state(ln, bfa_fcport_ln_sm_up_dn_nf);
		अवरोध;

	हाल BFA_FCPORT_LN_SM_NOTIFICATION:
		bfa_sm_set_state(ln, bfa_fcport_ln_sm_dn_up_nf);
		bfa_fcport_queue_cb(ln, BFA_PORT_LINKDOWN);
		अवरोध;

	शेष:
		bfa_sm_fault(ln->fcport->bfa, event);
	पूर्ण
पूर्ण

अटल व्योम
__bfa_cb_fcport_event(व्योम *cbarg, bfa_boolean_t complete)
अणु
	काष्ठा bfa_fcport_ln_s *ln = cbarg;

	अगर (complete)
		ln->fcport->event_cbfn(ln->fcport->event_cbarg, ln->ln_event);
	अन्यथा
		bfa_sm_send_event(ln, BFA_FCPORT_LN_SM_NOTIFICATION);
पूर्ण

/*
 * Send SCN notअगरication to upper layers.
 * trunk - false अगर caller is fcport to ignore fcport event in trunked mode
 */
अटल व्योम
bfa_fcport_scn(काष्ठा bfa_fcport_s *fcport, क्रमागत bfa_port_linkstate event,
	bfa_boolean_t trunk)
अणु
	अगर (fcport->cfg.trunked && !trunk)
		वापस;

	चयन (event) अणु
	हाल BFA_PORT_LINKUP:
		bfa_sm_send_event(&fcport->ln, BFA_FCPORT_LN_SM_LINKUP);
		अवरोध;
	हाल BFA_PORT_LINKDOWN:
		bfa_sm_send_event(&fcport->ln, BFA_FCPORT_LN_SM_LINKDOWN);
		अवरोध;
	शेष:
		WARN_ON(1);
	पूर्ण
पूर्ण

अटल व्योम
bfa_fcport_queue_cb(काष्ठा bfa_fcport_ln_s *ln, क्रमागत bfa_port_linkstate event)
अणु
	काष्ठा bfa_fcport_s *fcport = ln->fcport;

	अगर (fcport->bfa->fcs) अणु
		fcport->event_cbfn(fcport->event_cbarg, event);
		bfa_sm_send_event(ln, BFA_FCPORT_LN_SM_NOTIFICATION);
	पूर्ण अन्यथा अणु
		ln->ln_event = event;
		bfa_cb_queue(fcport->bfa, &ln->ln_qe,
			__bfa_cb_fcport_event, ln);
	पूर्ण
पूर्ण

#घोषणा FCPORT_STATS_DMA_SZ (BFA_ROUNDUP(माप(जोड़ bfa_fcport_stats_u), \
							BFA_CACHELINE_SZ))

व्योम
bfa_fcport_meminfo(काष्ठा bfa_iocfc_cfg_s *cfg, काष्ठा bfa_meminfo_s *minfo,
		   काष्ठा bfa_s *bfa)
अणु
	काष्ठा bfa_mem_dma_s *fcport_dma = BFA_MEM_FCPORT_DMA(bfa);

	bfa_mem_dma_setup(minfo, fcport_dma, FCPORT_STATS_DMA_SZ);
पूर्ण

अटल व्योम
bfa_fcport_qresume(व्योम *cbarg)
अणु
	काष्ठा bfa_fcport_s *fcport = cbarg;

	bfa_sm_send_event(fcport, BFA_FCPORT_SM_QRESUME);
पूर्ण

अटल व्योम
bfa_fcport_mem_claim(काष्ठा bfa_fcport_s *fcport)
अणु
	काष्ठा bfa_mem_dma_s *fcport_dma = &fcport->fcport_dma;

	fcport->stats_kva = bfa_mem_dma_virt(fcport_dma);
	fcport->stats_pa  = bfa_mem_dma_phys(fcport_dma);
	fcport->stats = (जोड़ bfa_fcport_stats_u *)
				bfa_mem_dma_virt(fcport_dma);
पूर्ण

/*
 * Memory initialization.
 */
व्योम
bfa_fcport_attach(काष्ठा bfa_s *bfa, व्योम *bfad, काष्ठा bfa_iocfc_cfg_s *cfg,
		काष्ठा bfa_pcidev_s *pcidev)
अणु
	काष्ठा bfa_fcport_s *fcport = BFA_FCPORT_MOD(bfa);
	काष्ठा bfa_port_cfg_s *port_cfg = &fcport->cfg;
	काष्ठा bfa_fcport_ln_s *ln = &fcport->ln;

	fcport->bfa = bfa;
	ln->fcport = fcport;

	bfa_fcport_mem_claim(fcport);

	bfa_sm_set_state(fcport, bfa_fcport_sm_uninit);
	bfa_sm_set_state(ln, bfa_fcport_ln_sm_dn);

	/*
	 * initialize समय stamp क्रम stats reset
	 */
	fcport->stats_reset_समय = kसमय_get_seconds();
	fcport->stats_dma_पढ़ोy = BFA_FALSE;

	/*
	 * initialize and set शेष configuration
	 */
	port_cfg->topology = BFA_PORT_TOPOLOGY_P2P;
	port_cfg->speed = BFA_PORT_SPEED_AUTO;
	port_cfg->trunked = BFA_FALSE;
	port_cfg->maxfrsize = 0;

	port_cfg->trl_def_speed = BFA_PORT_SPEED_1GBPS;
	port_cfg->qos_bw.high = BFA_QOS_BW_HIGH;
	port_cfg->qos_bw.med = BFA_QOS_BW_MED;
	port_cfg->qos_bw.low = BFA_QOS_BW_LOW;

	fcport->fec_state = BFA_FEC_OFFLINE;

	INIT_LIST_HEAD(&fcport->stats_pending_q);
	INIT_LIST_HEAD(&fcport->statsclr_pending_q);

	bfa_reqq_winit(&fcport->reqq_रुको, bfa_fcport_qresume, fcport);
पूर्ण

व्योम
bfa_fcport_start(काष्ठा bfa_s *bfa)
अणु
	bfa_sm_send_event(BFA_FCPORT_MOD(bfa), BFA_FCPORT_SM_START);
पूर्ण

/*
 * Called when IOC failure is detected.
 */
व्योम
bfa_fcport_iocdisable(काष्ठा bfa_s *bfa)
अणु
	काष्ठा bfa_fcport_s *fcport = BFA_FCPORT_MOD(bfa);

	bfa_sm_send_event(fcport, BFA_FCPORT_SM_HWFAIL);
	bfa_trunk_iocdisable(bfa);
पूर्ण

/*
 * Update loop info in fcport क्रम SCN online
 */
अटल व्योम
bfa_fcport_update_loop_info(काष्ठा bfa_fcport_s *fcport,
			काष्ठा bfa_fcport_loop_info_s *loop_info)
अणु
	fcport->myalpa = loop_info->myalpa;
	fcport->alpabm_valid =
			loop_info->alpabm_val;
	स_नकल(fcport->alpabm.alpa_bm,
			loop_info->alpabm.alpa_bm,
			माप(काष्ठा fc_alpabm_s));
पूर्ण

अटल व्योम
bfa_fcport_update_linkinfo(काष्ठा bfa_fcport_s *fcport)
अणु
	काष्ठा bfi_fcport_event_s *pevent = fcport->event_arg.i2hmsg.event;
	काष्ठा bfa_fcport_trunk_s *trunk = &fcport->trunk;

	fcport->speed = pevent->link_state.speed;
	fcport->topology = pevent->link_state.topology;

	अगर (fcport->topology == BFA_PORT_TOPOLOGY_LOOP) अणु
		bfa_fcport_update_loop_info(fcport,
				&pevent->link_state.attr.loop_info);
		वापस;
	पूर्ण

	/* QoS Details */
	fcport->qos_attr = pevent->link_state.qos_attr;
	fcport->qos_vc_attr = pevent->link_state.attr.vc_fcf.qos_vc_attr;

	अगर (fcport->cfg.bb_cr_enabled)
		fcport->bbcr_attr = pevent->link_state.attr.bbcr_attr;

	fcport->fec_state = pevent->link_state.fec_state;

	/*
	 * update trunk state अगर applicable
	 */
	अगर (!fcport->cfg.trunked)
		trunk->attr.state = BFA_TRUNK_DISABLED;

	/* update FCoE specअगरic */
	fcport->fcoe_vlan =
		be16_to_cpu(pevent->link_state.attr.vc_fcf.fcf.vlan);

	bfa_trc(fcport->bfa, fcport->speed);
	bfa_trc(fcport->bfa, fcport->topology);
पूर्ण

अटल व्योम
bfa_fcport_reset_linkinfo(काष्ठा bfa_fcport_s *fcport)
अणु
	fcport->speed = BFA_PORT_SPEED_UNKNOWN;
	fcport->topology = BFA_PORT_TOPOLOGY_NONE;
	fcport->fec_state = BFA_FEC_OFFLINE;
पूर्ण

/*
 * Send port enable message to firmware.
 */
अटल bfa_boolean_t
bfa_fcport_send_enable(काष्ठा bfa_fcport_s *fcport)
अणु
	काष्ठा bfi_fcport_enable_req_s *m;

	/*
	 * Increment message tag beक्रमe queue check, so that responses to old
	 * requests are discarded.
	 */
	fcport->msgtag++;

	/*
	 * check क्रम room in queue to send request now
	 */
	m = bfa_reqq_next(fcport->bfa, BFA_REQQ_PORT);
	अगर (!m) अणु
		bfa_reqq_रुको(fcport->bfa, BFA_REQQ_PORT,
							&fcport->reqq_रुको);
		वापस BFA_FALSE;
	पूर्ण

	bfi_h2i_set(m->mh, BFI_MC_FCPORT, BFI_FCPORT_H2I_ENABLE_REQ,
			bfa_fn_lpu(fcport->bfa));
	m->nwwn = fcport->nwwn;
	m->pwwn = fcport->pwwn;
	m->port_cfg = fcport->cfg;
	m->msgtag = fcport->msgtag;
	m->port_cfg.maxfrsize = cpu_to_be16(fcport->cfg.maxfrsize);
	 m->use_flash_cfg = fcport->use_flash_cfg;
	bfa_dma_be_addr_set(m->stats_dma_addr, fcport->stats_pa);
	bfa_trc(fcport->bfa, m->stats_dma_addr.a32.addr_lo);
	bfa_trc(fcport->bfa, m->stats_dma_addr.a32.addr_hi);

	/*
	 * queue I/O message to firmware
	 */
	bfa_reqq_produce(fcport->bfa, BFA_REQQ_PORT, m->mh);
	वापस BFA_TRUE;
पूर्ण

/*
 * Send port disable message to firmware.
 */
अटल	bfa_boolean_t
bfa_fcport_send_disable(काष्ठा bfa_fcport_s *fcport)
अणु
	काष्ठा bfi_fcport_req_s *m;

	/*
	 * Increment message tag beक्रमe queue check, so that responses to old
	 * requests are discarded.
	 */
	fcport->msgtag++;

	/*
	 * check क्रम room in queue to send request now
	 */
	m = bfa_reqq_next(fcport->bfa, BFA_REQQ_PORT);
	अगर (!m) अणु
		bfa_reqq_रुको(fcport->bfa, BFA_REQQ_PORT,
							&fcport->reqq_रुको);
		वापस BFA_FALSE;
	पूर्ण

	bfi_h2i_set(m->mh, BFI_MC_FCPORT, BFI_FCPORT_H2I_DISABLE_REQ,
			bfa_fn_lpu(fcport->bfa));
	m->msgtag = fcport->msgtag;

	/*
	 * queue I/O message to firmware
	 */
	bfa_reqq_produce(fcport->bfa, BFA_REQQ_PORT, m->mh);

	वापस BFA_TRUE;
पूर्ण

अटल व्योम
bfa_fcport_set_wwns(काष्ठा bfa_fcport_s *fcport)
अणु
	fcport->pwwn = fcport->bfa->ioc.attr->pwwn;
	fcport->nwwn = fcport->bfa->ioc.attr->nwwn;

	bfa_trc(fcport->bfa, fcport->pwwn);
	bfa_trc(fcport->bfa, fcport->nwwn);
पूर्ण

अटल व्योम
bfa_fcport_qos_stats_swap(काष्ठा bfa_qos_stats_s *d,
	काष्ठा bfa_qos_stats_s *s)
अणु
	u32	*dip = (u32 *) d;
	__be32	*sip = (__be32 *) s;
	पूर्णांक		i;

	/* Now swap the 32 bit fields */
	क्रम (i = 0; i < (माप(काष्ठा bfa_qos_stats_s)/माप(u32)); ++i)
		dip[i] = be32_to_cpu(sip[i]);
पूर्ण

अटल व्योम
bfa_fcport_fcoe_stats_swap(काष्ठा bfa_fcoe_stats_s *d,
	काष्ठा bfa_fcoe_stats_s *s)
अणु
	u32	*dip = (u32 *) d;
	__be32	*sip = (__be32 *) s;
	पूर्णांक		i;

	क्रम (i = 0; i < ((माप(काष्ठा bfa_fcoe_stats_s))/माप(u32));
	     i = i + 2) अणु
#अगर_घोषित __BIG_ENDIAN
		dip[i] = be32_to_cpu(sip[i]);
		dip[i + 1] = be32_to_cpu(sip[i + 1]);
#अन्यथा
		dip[i] = be32_to_cpu(sip[i + 1]);
		dip[i + 1] = be32_to_cpu(sip[i]);
#पूर्ण_अगर
	पूर्ण
पूर्ण

अटल व्योम
__bfa_cb_fcport_stats_get(व्योम *cbarg, bfa_boolean_t complete)
अणु
	काष्ठा bfa_fcport_s *fcport = (काष्ठा bfa_fcport_s *)cbarg;
	काष्ठा bfa_cb_pending_q_s *cb;
	काष्ठा list_head *qe, *qen;
	जोड़ bfa_fcport_stats_u *ret;

	अगर (complete) अणु
		समय64_t समय = kसमय_get_seconds();

		list_क्रम_each_safe(qe, qen, &fcport->stats_pending_q) अणु
			bfa_q_deq(&fcport->stats_pending_q, &qe);
			cb = (काष्ठा bfa_cb_pending_q_s *)qe;
			अगर (fcport->stats_status == BFA_STATUS_OK) अणु
				ret = (जोड़ bfa_fcport_stats_u *)cb->data;
				/* Swap FC QoS or FCoE stats */
				अगर (bfa_ioc_get_fcmode(&fcport->bfa->ioc))
					bfa_fcport_qos_stats_swap(&ret->fcqos,
							&fcport->stats->fcqos);
				अन्यथा अणु
					bfa_fcport_fcoe_stats_swap(&ret->fcoe,
							&fcport->stats->fcoe);
					ret->fcoe.secs_reset =
						समय - fcport->stats_reset_समय;
				पूर्ण
			पूर्ण
			bfa_cb_queue_status(fcport->bfa, &cb->hcb_qe,
					fcport->stats_status);
		पूर्ण
		fcport->stats_status = BFA_STATUS_OK;
	पूर्ण अन्यथा अणु
		INIT_LIST_HEAD(&fcport->stats_pending_q);
		fcport->stats_status = BFA_STATUS_OK;
	पूर्ण
पूर्ण

अटल व्योम
bfa_fcport_stats_get_समयout(व्योम *cbarg)
अणु
	काष्ठा bfa_fcport_s *fcport = (काष्ठा bfa_fcport_s *) cbarg;

	bfa_trc(fcport->bfa, fcport->stats_qfull);

	अगर (fcport->stats_qfull) अणु
		bfa_reqq_wcancel(&fcport->stats_reqq_रुको);
		fcport->stats_qfull = BFA_FALSE;
	पूर्ण

	fcport->stats_status = BFA_STATUS_ETIMER;
	__bfa_cb_fcport_stats_get(fcport, BFA_TRUE);
पूर्ण

अटल व्योम
bfa_fcport_send_stats_get(व्योम *cbarg)
अणु
	काष्ठा bfa_fcport_s *fcport = (काष्ठा bfa_fcport_s *) cbarg;
	काष्ठा bfi_fcport_req_s *msg;

	msg = bfa_reqq_next(fcport->bfa, BFA_REQQ_PORT);

	अगर (!msg) अणु
		fcport->stats_qfull = BFA_TRUE;
		bfa_reqq_winit(&fcport->stats_reqq_रुको,
				bfa_fcport_send_stats_get, fcport);
		bfa_reqq_रुको(fcport->bfa, BFA_REQQ_PORT,
				&fcport->stats_reqq_रुको);
		वापस;
	पूर्ण
	fcport->stats_qfull = BFA_FALSE;

	स_रखो(msg, 0, माप(काष्ठा bfi_fcport_req_s));
	bfi_h2i_set(msg->mh, BFI_MC_FCPORT, BFI_FCPORT_H2I_STATS_GET_REQ,
			bfa_fn_lpu(fcport->bfa));
	bfa_reqq_produce(fcport->bfa, BFA_REQQ_PORT, msg->mh);
पूर्ण

अटल व्योम
__bfa_cb_fcport_stats_clr(व्योम *cbarg, bfa_boolean_t complete)
अणु
	काष्ठा bfa_fcport_s *fcport = (काष्ठा bfa_fcport_s *) cbarg;
	काष्ठा bfa_cb_pending_q_s *cb;
	काष्ठा list_head *qe, *qen;

	अगर (complete) अणु
		/*
		 * re-initialize समय stamp क्रम stats reset
		 */
		fcport->stats_reset_समय = kसमय_get_seconds();
		list_क्रम_each_safe(qe, qen, &fcport->statsclr_pending_q) अणु
			bfa_q_deq(&fcport->statsclr_pending_q, &qe);
			cb = (काष्ठा bfa_cb_pending_q_s *)qe;
			bfa_cb_queue_status(fcport->bfa, &cb->hcb_qe,
						fcport->stats_status);
		पूर्ण
		fcport->stats_status = BFA_STATUS_OK;
	पूर्ण अन्यथा अणु
		INIT_LIST_HEAD(&fcport->statsclr_pending_q);
		fcport->stats_status = BFA_STATUS_OK;
	पूर्ण
पूर्ण

अटल व्योम
bfa_fcport_stats_clr_समयout(व्योम *cbarg)
अणु
	काष्ठा bfa_fcport_s *fcport = (काष्ठा bfa_fcport_s *) cbarg;

	bfa_trc(fcport->bfa, fcport->stats_qfull);

	अगर (fcport->stats_qfull) अणु
		bfa_reqq_wcancel(&fcport->stats_reqq_रुको);
		fcport->stats_qfull = BFA_FALSE;
	पूर्ण

	fcport->stats_status = BFA_STATUS_ETIMER;
	__bfa_cb_fcport_stats_clr(fcport, BFA_TRUE);
पूर्ण

अटल व्योम
bfa_fcport_send_stats_clear(व्योम *cbarg)
अणु
	काष्ठा bfa_fcport_s *fcport = (काष्ठा bfa_fcport_s *) cbarg;
	काष्ठा bfi_fcport_req_s *msg;

	msg = bfa_reqq_next(fcport->bfa, BFA_REQQ_PORT);

	अगर (!msg) अणु
		fcport->stats_qfull = BFA_TRUE;
		bfa_reqq_winit(&fcport->stats_reqq_रुको,
				bfa_fcport_send_stats_clear, fcport);
		bfa_reqq_रुको(fcport->bfa, BFA_REQQ_PORT,
						&fcport->stats_reqq_रुको);
		वापस;
	पूर्ण
	fcport->stats_qfull = BFA_FALSE;

	स_रखो(msg, 0, माप(काष्ठा bfi_fcport_req_s));
	bfi_h2i_set(msg->mh, BFI_MC_FCPORT, BFI_FCPORT_H2I_STATS_CLEAR_REQ,
			bfa_fn_lpu(fcport->bfa));
	bfa_reqq_produce(fcport->bfa, BFA_REQQ_PORT, msg->mh);
पूर्ण

/*
 * Handle trunk SCN event from firmware.
 */
अटल व्योम
bfa_trunk_scn(काष्ठा bfa_fcport_s *fcport, काष्ठा bfi_fcport_trunk_scn_s *scn)
अणु
	काष्ठा bfa_fcport_trunk_s *trunk = &fcport->trunk;
	काष्ठा bfi_fcport_trunk_link_s *tlink;
	काष्ठा bfa_trunk_link_attr_s *lattr;
	क्रमागत bfa_trunk_state state_prev;
	पूर्णांक i;
	पूर्णांक link_bm = 0;

	bfa_trc(fcport->bfa, fcport->cfg.trunked);
	WARN_ON(scn->trunk_state != BFA_TRUNK_ONLINE &&
		   scn->trunk_state != BFA_TRUNK_OFFLINE);

	bfa_trc(fcport->bfa, trunk->attr.state);
	bfa_trc(fcport->bfa, scn->trunk_state);
	bfa_trc(fcport->bfa, scn->trunk_speed);

	/*
	 * Save off new state क्रम trunk attribute query
	 */
	state_prev = trunk->attr.state;
	अगर (fcport->cfg.trunked && (trunk->attr.state != BFA_TRUNK_DISABLED))
		trunk->attr.state = scn->trunk_state;
	trunk->attr.speed = scn->trunk_speed;
	क्रम (i = 0; i < BFA_TRUNK_MAX_PORTS; i++) अणु
		lattr = &trunk->attr.link_attr[i];
		tlink = &scn->tlink[i];

		lattr->link_state = tlink->state;
		lattr->trunk_wwn  = tlink->trunk_wwn;
		lattr->fctl	  = tlink->fctl;
		lattr->speed	  = tlink->speed;
		lattr->deskew	  = be32_to_cpu(tlink->deskew);

		अगर (tlink->state == BFA_TRUNK_LINK_STATE_UP) अणु
			fcport->speed	 = tlink->speed;
			fcport->topology = BFA_PORT_TOPOLOGY_P2P;
			link_bm |= 1 << i;
		पूर्ण

		bfa_trc(fcport->bfa, lattr->link_state);
		bfa_trc(fcport->bfa, lattr->trunk_wwn);
		bfa_trc(fcport->bfa, lattr->fctl);
		bfa_trc(fcport->bfa, lattr->speed);
		bfa_trc(fcport->bfa, lattr->deskew);
	पूर्ण

	चयन (link_bm) अणु
	हाल 3:
		bfa_plog_str(fcport->bfa->plog, BFA_PL_MID_HAL,
			BFA_PL_EID_TRUNK_SCN, 0, "Trunk up(0,1)");
		अवरोध;
	हाल 2:
		bfa_plog_str(fcport->bfa->plog, BFA_PL_MID_HAL,
			BFA_PL_EID_TRUNK_SCN, 0, "Trunk up(-,1)");
		अवरोध;
	हाल 1:
		bfa_plog_str(fcport->bfa->plog, BFA_PL_MID_HAL,
			BFA_PL_EID_TRUNK_SCN, 0, "Trunk up(0,-)");
		अवरोध;
	शेष:
		bfa_plog_str(fcport->bfa->plog, BFA_PL_MID_HAL,
			BFA_PL_EID_TRUNK_SCN, 0, "Trunk down");
	पूर्ण

	/*
	 * Notअगरy upper layers अगर trunk state changed.
	 */
	अगर ((state_prev != trunk->attr.state) ||
		(scn->trunk_state == BFA_TRUNK_OFFLINE)) अणु
		bfa_fcport_scn(fcport, (scn->trunk_state == BFA_TRUNK_ONLINE) ?
			BFA_PORT_LINKUP : BFA_PORT_LINKDOWN, BFA_TRUE);
	पूर्ण
पूर्ण

अटल व्योम
bfa_trunk_iocdisable(काष्ठा bfa_s *bfa)
अणु
	काष्ठा bfa_fcport_s *fcport = BFA_FCPORT_MOD(bfa);
	पूर्णांक i = 0;

	/*
	 * In trunked mode, notअगरy upper layers that link is करोwn
	 */
	अगर (fcport->cfg.trunked) अणु
		अगर (fcport->trunk.attr.state == BFA_TRUNK_ONLINE)
			bfa_fcport_scn(fcport, BFA_PORT_LINKDOWN, BFA_TRUE);

		fcport->trunk.attr.state = BFA_TRUNK_OFFLINE;
		fcport->trunk.attr.speed = BFA_PORT_SPEED_UNKNOWN;
		क्रम (i = 0; i < BFA_TRUNK_MAX_PORTS; i++) अणु
			fcport->trunk.attr.link_attr[i].trunk_wwn = 0;
			fcport->trunk.attr.link_attr[i].fctl =
						BFA_TRUNK_LINK_FCTL_NORMAL;
			fcport->trunk.attr.link_attr[i].link_state =
						BFA_TRUNK_LINK_STATE_DN_LINKDN;
			fcport->trunk.attr.link_attr[i].speed =
						BFA_PORT_SPEED_UNKNOWN;
			fcport->trunk.attr.link_attr[i].deskew = 0;
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Called to initialize port attributes
 */
व्योम
bfa_fcport_init(काष्ठा bfa_s *bfa)
अणु
	काष्ठा bfa_fcport_s *fcport = BFA_FCPORT_MOD(bfa);

	/*
	 * Initialize port attributes from IOC hardware data.
	 */
	bfa_fcport_set_wwns(fcport);
	अगर (fcport->cfg.maxfrsize == 0)
		fcport->cfg.maxfrsize = bfa_ioc_maxfrsize(&bfa->ioc);
	fcport->cfg.rx_bbcredit = bfa_ioc_rx_bbcredit(&bfa->ioc);
	fcport->speed_sup = bfa_ioc_speed_sup(&bfa->ioc);

	अगर (bfa_fcport_is_pbcdisabled(bfa))
		bfa->modules.port.pbc_disabled = BFA_TRUE;

	WARN_ON(!fcport->cfg.maxfrsize);
	WARN_ON(!fcport->cfg.rx_bbcredit);
	WARN_ON(!fcport->speed_sup);
पूर्ण

/*
 * Firmware message handler.
 */
व्योम
bfa_fcport_isr(काष्ठा bfa_s *bfa, काष्ठा bfi_msg_s *msg)
अणु
	काष्ठा bfa_fcport_s *fcport = BFA_FCPORT_MOD(bfa);
	जोड़ bfi_fcport_i2h_msg_u i2hmsg;

	i2hmsg.msg = msg;
	fcport->event_arg.i2hmsg = i2hmsg;

	bfa_trc(bfa, msg->mhdr.msg_id);
	bfa_trc(bfa, bfa_sm_to_state(hal_port_sm_table, fcport->sm));

	चयन (msg->mhdr.msg_id) अणु
	हाल BFI_FCPORT_I2H_ENABLE_RSP:
		अगर (fcport->msgtag == i2hmsg.penable_rsp->msgtag) अणु

			fcport->stats_dma_पढ़ोy = BFA_TRUE;
			अगर (fcport->use_flash_cfg) अणु
				fcport->cfg = i2hmsg.penable_rsp->port_cfg;
				fcport->cfg.maxfrsize =
					cpu_to_be16(fcport->cfg.maxfrsize);
				fcport->cfg.path_tov =
					cpu_to_be16(fcport->cfg.path_tov);
				fcport->cfg.q_depth =
					cpu_to_be16(fcport->cfg.q_depth);

				अगर (fcport->cfg.trunked)
					fcport->trunk.attr.state =
						BFA_TRUNK_OFFLINE;
				अन्यथा
					fcport->trunk.attr.state =
						BFA_TRUNK_DISABLED;
				fcport->qos_attr.qos_bw =
					i2hmsg.penable_rsp->port_cfg.qos_bw;
				fcport->use_flash_cfg = BFA_FALSE;
			पूर्ण

			अगर (fcport->cfg.qos_enabled)
				fcport->qos_attr.state = BFA_QOS_OFFLINE;
			अन्यथा
				fcport->qos_attr.state = BFA_QOS_DISABLED;

			fcport->qos_attr.qos_bw_op =
					i2hmsg.penable_rsp->port_cfg.qos_bw;

			अगर (fcport->cfg.bb_cr_enabled)
				fcport->bbcr_attr.state = BFA_BBCR_OFFLINE;
			अन्यथा
				fcport->bbcr_attr.state = BFA_BBCR_DISABLED;

			bfa_sm_send_event(fcport, BFA_FCPORT_SM_FWRSP);
		पूर्ण
		अवरोध;

	हाल BFI_FCPORT_I2H_DISABLE_RSP:
		अगर (fcport->msgtag == i2hmsg.penable_rsp->msgtag)
			bfa_sm_send_event(fcport, BFA_FCPORT_SM_FWRSP);
		अवरोध;

	हाल BFI_FCPORT_I2H_EVENT:
		अगर (fcport->cfg.bb_cr_enabled)
			fcport->bbcr_attr.state = BFA_BBCR_OFFLINE;
		अन्यथा
			fcport->bbcr_attr.state = BFA_BBCR_DISABLED;

		अगर (i2hmsg.event->link_state.linkstate == BFA_PORT_LINKUP)
			bfa_sm_send_event(fcport, BFA_FCPORT_SM_LINKUP);
		अन्यथा अणु
			अगर (i2hmsg.event->link_state.linkstate_rsn ==
			    BFA_PORT_LINKSTATE_RSN_FAA_MISCONFIG)
				bfa_sm_send_event(fcport,
						  BFA_FCPORT_SM_FAA_MISCONFIG);
			अन्यथा
				bfa_sm_send_event(fcport,
						  BFA_FCPORT_SM_LINKDOWN);
		पूर्ण
		fcport->qos_attr.qos_bw_op =
				i2hmsg.event->link_state.qos_attr.qos_bw_op;
		अवरोध;

	हाल BFI_FCPORT_I2H_TRUNK_SCN:
		bfa_trunk_scn(fcport, i2hmsg.trunk_scn);
		अवरोध;

	हाल BFI_FCPORT_I2H_STATS_GET_RSP:
		/*
		 * check क्रम समयr pop beक्रमe processing the rsp
		 */
		अगर (list_empty(&fcport->stats_pending_q) ||
		    (fcport->stats_status == BFA_STATUS_ETIMER))
			अवरोध;

		bfa_समयr_stop(&fcport->समयr);
		fcport->stats_status = i2hmsg.pstatsget_rsp->status;
		__bfa_cb_fcport_stats_get(fcport, BFA_TRUE);
		अवरोध;

	हाल BFI_FCPORT_I2H_STATS_CLEAR_RSP:
		/*
		 * check क्रम समयr pop beक्रमe processing the rsp
		 */
		अगर (list_empty(&fcport->statsclr_pending_q) ||
		    (fcport->stats_status == BFA_STATUS_ETIMER))
			अवरोध;

		bfa_समयr_stop(&fcport->समयr);
		fcport->stats_status = BFA_STATUS_OK;
		__bfa_cb_fcport_stats_clr(fcport, BFA_TRUE);
		अवरोध;

	हाल BFI_FCPORT_I2H_ENABLE_AEN:
		bfa_sm_send_event(fcport, BFA_FCPORT_SM_ENABLE);
		अवरोध;

	हाल BFI_FCPORT_I2H_DISABLE_AEN:
		bfa_sm_send_event(fcport, BFA_FCPORT_SM_DISABLE);
		अवरोध;

	शेष:
		WARN_ON(1);
	अवरोध;
	पूर्ण
पूर्ण

/*
 * Registered callback क्रम port events.
 */
व्योम
bfa_fcport_event_रेजिस्टर(काष्ठा bfa_s *bfa,
				व्योम (*cbfn) (व्योम *cbarg,
				क्रमागत bfa_port_linkstate event),
				व्योम *cbarg)
अणु
	काष्ठा bfa_fcport_s *fcport = BFA_FCPORT_MOD(bfa);

	fcport->event_cbfn = cbfn;
	fcport->event_cbarg = cbarg;
पूर्ण

bfa_status_t
bfa_fcport_enable(काष्ठा bfa_s *bfa)
अणु
	काष्ठा bfa_fcport_s *fcport = BFA_FCPORT_MOD(bfa);

	अगर (bfa_fcport_is_pbcdisabled(bfa))
		वापस BFA_STATUS_PBC;

	अगर (bfa_ioc_is_disabled(&bfa->ioc))
		वापस BFA_STATUS_IOC_DISABLED;

	अगर (fcport->diag_busy)
		वापस BFA_STATUS_DIAG_BUSY;

	bfa_sm_send_event(BFA_FCPORT_MOD(bfa), BFA_FCPORT_SM_ENABLE);
	वापस BFA_STATUS_OK;
पूर्ण

bfa_status_t
bfa_fcport_disable(काष्ठा bfa_s *bfa)
अणु
	अगर (bfa_fcport_is_pbcdisabled(bfa))
		वापस BFA_STATUS_PBC;

	अगर (bfa_ioc_is_disabled(&bfa->ioc))
		वापस BFA_STATUS_IOC_DISABLED;

	bfa_sm_send_event(BFA_FCPORT_MOD(bfa), BFA_FCPORT_SM_DISABLE);
	वापस BFA_STATUS_OK;
पूर्ण

/* If PBC is disabled on port, वापस error */
bfa_status_t
bfa_fcport_is_pbcdisabled(काष्ठा bfa_s *bfa)
अणु
	काष्ठा bfa_fcport_s *fcport = BFA_FCPORT_MOD(bfa);
	काष्ठा bfa_iocfc_s *iocfc = &bfa->iocfc;
	काष्ठा bfi_iocfc_cfgrsp_s *cfgrsp = iocfc->cfgrsp;

	अगर (cfgrsp->pbc_cfg.port_enabled == BFI_PBC_PORT_DISABLED) अणु
		bfa_trc(bfa, fcport->pwwn);
		वापस BFA_STATUS_PBC;
	पूर्ण
	वापस BFA_STATUS_OK;
पूर्ण

/*
 * Configure port speed.
 */
bfa_status_t
bfa_fcport_cfg_speed(काष्ठा bfa_s *bfa, क्रमागत bfa_port_speed speed)
अणु
	काष्ठा bfa_fcport_s *fcport = BFA_FCPORT_MOD(bfa);

	bfa_trc(bfa, speed);

	अगर (fcport->cfg.trunked == BFA_TRUE)
		वापस BFA_STATUS_TRUNK_ENABLED;
	अगर ((fcport->cfg.topology == BFA_PORT_TOPOLOGY_LOOP) &&
			(speed == BFA_PORT_SPEED_16GBPS))
		वापस BFA_STATUS_UNSUPP_SPEED;
	अगर ((speed != BFA_PORT_SPEED_AUTO) && (speed > fcport->speed_sup)) अणु
		bfa_trc(bfa, fcport->speed_sup);
		वापस BFA_STATUS_UNSUPP_SPEED;
	पूर्ण

	/* Port speed entered needs to be checked */
	अगर (bfa_ioc_get_type(&fcport->bfa->ioc) == BFA_IOC_TYPE_FC) अणु
		/* For CT2, 1G is not supported */
		अगर ((speed == BFA_PORT_SPEED_1GBPS) &&
		    (bfa_asic_id_ct2(bfa->ioc.pcidev.device_id)))
			वापस BFA_STATUS_UNSUPP_SPEED;

		/* Alपढ़ोy checked क्रम Auto Speed and Max Speed supp */
		अगर (!(speed == BFA_PORT_SPEED_1GBPS ||
		      speed == BFA_PORT_SPEED_2GBPS ||
		      speed == BFA_PORT_SPEED_4GBPS ||
		      speed == BFA_PORT_SPEED_8GBPS ||
		      speed == BFA_PORT_SPEED_16GBPS ||
		      speed == BFA_PORT_SPEED_AUTO))
			वापस BFA_STATUS_UNSUPP_SPEED;
	पूर्ण अन्यथा अणु
		अगर (speed != BFA_PORT_SPEED_10GBPS)
			वापस BFA_STATUS_UNSUPP_SPEED;
	पूर्ण

	fcport->cfg.speed = speed;

	वापस BFA_STATUS_OK;
पूर्ण

/*
 * Get current speed.
 */
क्रमागत bfa_port_speed
bfa_fcport_get_speed(काष्ठा bfa_s *bfa)
अणु
	काष्ठा bfa_fcport_s *fcport = BFA_FCPORT_MOD(bfa);

	वापस fcport->speed;
पूर्ण

/*
 * Configure port topology.
 */
bfa_status_t
bfa_fcport_cfg_topology(काष्ठा bfa_s *bfa, क्रमागत bfa_port_topology topology)
अणु
	काष्ठा bfa_fcport_s *fcport = BFA_FCPORT_MOD(bfa);

	bfa_trc(bfa, topology);
	bfa_trc(bfa, fcport->cfg.topology);

	चयन (topology) अणु
	हाल BFA_PORT_TOPOLOGY_P2P:
		अवरोध;

	हाल BFA_PORT_TOPOLOGY_LOOP:
		अगर ((bfa_fcport_is_qos_enabled(bfa) != BFA_FALSE) ||
			(fcport->qos_attr.state != BFA_QOS_DISABLED))
			वापस BFA_STATUS_ERROR_QOS_ENABLED;
		अगर (fcport->cfg.ratelimit != BFA_FALSE)
			वापस BFA_STATUS_ERROR_TRL_ENABLED;
		अगर ((bfa_fcport_is_trunk_enabled(bfa) != BFA_FALSE) ||
			(fcport->trunk.attr.state != BFA_TRUNK_DISABLED))
			वापस BFA_STATUS_ERROR_TRUNK_ENABLED;
		अगर ((bfa_fcport_get_speed(bfa) == BFA_PORT_SPEED_16GBPS) ||
			(fcport->cfg.speed == BFA_PORT_SPEED_16GBPS))
			वापस BFA_STATUS_UNSUPP_SPEED;
		अगर (bfa_mfg_is_mezz(bfa->ioc.attr->card_type))
			वापस BFA_STATUS_LOOP_UNSUPP_MEZZ;
		अगर (bfa_fcport_is_dport(bfa) != BFA_FALSE)
			वापस BFA_STATUS_DPORT_ERR;
		अगर (bfa_fcport_is_ddport(bfa) != BFA_FALSE)
			वापस BFA_STATUS_DPORT_ERR;
		अवरोध;

	हाल BFA_PORT_TOPOLOGY_AUTO:
		अवरोध;

	शेष:
		वापस BFA_STATUS_EINVAL;
	पूर्ण

	fcport->cfg.topology = topology;
	वापस BFA_STATUS_OK;
पूर्ण

/*
 * Get current topology.
 */
क्रमागत bfa_port_topology
bfa_fcport_get_topology(काष्ठा bfa_s *bfa)
अणु
	काष्ठा bfa_fcport_s *fcport = BFA_FCPORT_MOD(bfa);

	वापस fcport->topology;
पूर्ण

/*
 * Get config topology.
 */
क्रमागत bfa_port_topology
bfa_fcport_get_cfg_topology(काष्ठा bfa_s *bfa)
अणु
	काष्ठा bfa_fcport_s *fcport = BFA_FCPORT_MOD(bfa);

	वापस fcport->cfg.topology;
पूर्ण

bfa_status_t
bfa_fcport_cfg_hardalpa(काष्ठा bfa_s *bfa, u8 alpa)
अणु
	काष्ठा bfa_fcport_s *fcport = BFA_FCPORT_MOD(bfa);

	bfa_trc(bfa, alpa);
	bfa_trc(bfa, fcport->cfg.cfg_hardalpa);
	bfa_trc(bfa, fcport->cfg.hardalpa);

	fcport->cfg.cfg_hardalpa = BFA_TRUE;
	fcport->cfg.hardalpa = alpa;

	वापस BFA_STATUS_OK;
पूर्ण

bfa_status_t
bfa_fcport_clr_hardalpa(काष्ठा bfa_s *bfa)
अणु
	काष्ठा bfa_fcport_s *fcport = BFA_FCPORT_MOD(bfa);

	bfa_trc(bfa, fcport->cfg.cfg_hardalpa);
	bfa_trc(bfa, fcport->cfg.hardalpa);

	fcport->cfg.cfg_hardalpa = BFA_FALSE;
	वापस BFA_STATUS_OK;
पूर्ण

bfa_boolean_t
bfa_fcport_get_hardalpa(काष्ठा bfa_s *bfa, u8 *alpa)
अणु
	काष्ठा bfa_fcport_s *fcport = BFA_FCPORT_MOD(bfa);

	*alpa = fcport->cfg.hardalpa;
	वापस fcport->cfg.cfg_hardalpa;
पूर्ण

u8
bfa_fcport_get_myalpa(काष्ठा bfa_s *bfa)
अणु
	काष्ठा bfa_fcport_s *fcport = BFA_FCPORT_MOD(bfa);

	वापस fcport->myalpa;
पूर्ण

bfa_status_t
bfa_fcport_cfg_maxfrsize(काष्ठा bfa_s *bfa, u16 maxfrsize)
अणु
	काष्ठा bfa_fcport_s *fcport = BFA_FCPORT_MOD(bfa);

	bfa_trc(bfa, maxfrsize);
	bfa_trc(bfa, fcport->cfg.maxfrsize);

	/* with in range */
	अगर ((maxfrsize > FC_MAX_PDUSZ) || (maxfrsize < FC_MIN_PDUSZ))
		वापस BFA_STATUS_INVLD_DFSZ;

	/* घातer of 2, अगर not the max frame size of 2112 */
	अगर ((maxfrsize != FC_MAX_PDUSZ) && (maxfrsize & (maxfrsize - 1)))
		वापस BFA_STATUS_INVLD_DFSZ;

	fcport->cfg.maxfrsize = maxfrsize;
	वापस BFA_STATUS_OK;
पूर्ण

u16
bfa_fcport_get_maxfrsize(काष्ठा bfa_s *bfa)
अणु
	काष्ठा bfa_fcport_s *fcport = BFA_FCPORT_MOD(bfa);

	वापस fcport->cfg.maxfrsize;
पूर्ण

u8
bfa_fcport_get_rx_bbcredit(काष्ठा bfa_s *bfa)
अणु
	अगर (bfa_fcport_get_topology(bfa) != BFA_PORT_TOPOLOGY_LOOP)
		वापस (BFA_FCPORT_MOD(bfa))->cfg.rx_bbcredit;

	अन्यथा
		वापस 0;
पूर्ण

व्योम
bfa_fcport_set_tx_bbcredit(काष्ठा bfa_s *bfa, u16 tx_bbcredit)
अणु
	काष्ठा bfa_fcport_s *fcport = BFA_FCPORT_MOD(bfa);

	fcport->cfg.tx_bbcredit = (u8)tx_bbcredit;
पूर्ण

/*
 * Get port attributes.
 */

wwn_t
bfa_fcport_get_wwn(काष्ठा bfa_s *bfa, bfa_boolean_t node)
अणु
	काष्ठा bfa_fcport_s *fcport = BFA_FCPORT_MOD(bfa);
	अगर (node)
		वापस fcport->nwwn;
	अन्यथा
		वापस fcport->pwwn;
पूर्ण

व्योम
bfa_fcport_get_attr(काष्ठा bfa_s *bfa, काष्ठा bfa_port_attr_s *attr)
अणु
	काष्ठा bfa_fcport_s *fcport = BFA_FCPORT_MOD(bfa);

	स_रखो(attr, 0, माप(काष्ठा bfa_port_attr_s));

	attr->nwwn = fcport->nwwn;
	attr->pwwn = fcport->pwwn;

	attr->factorypwwn =  bfa->ioc.attr->mfg_pwwn;
	attr->factorynwwn =  bfa->ioc.attr->mfg_nwwn;

	स_नकल(&attr->pport_cfg, &fcport->cfg,
		माप(काष्ठा bfa_port_cfg_s));
	/* speed attributes */
	attr->pport_cfg.speed = fcport->cfg.speed;
	attr->speed_supported = fcport->speed_sup;
	attr->speed = fcport->speed;
	attr->cos_supported = FC_CLASS_3;

	/* topology attributes */
	attr->pport_cfg.topology = fcport->cfg.topology;
	attr->topology = fcport->topology;
	attr->pport_cfg.trunked = fcport->cfg.trunked;

	/* beacon attributes */
	attr->beacon = fcport->beacon;
	attr->link_e2e_beacon = fcport->link_e2e_beacon;

	attr->pport_cfg.path_tov  = bfa_fcpim_path_tov_get(bfa);
	attr->pport_cfg.q_depth  = bfa_fcpim_qdepth_get(bfa);
	attr->port_state = bfa_sm_to_state(hal_port_sm_table, fcport->sm);

	attr->fec_state = fcport->fec_state;

	/* PBC Disabled State */
	अगर (bfa_fcport_is_pbcdisabled(bfa))
		attr->port_state = BFA_PORT_ST_PREBOOT_DISABLED;
	अन्यथा अणु
		अगर (bfa_ioc_is_disabled(&fcport->bfa->ioc))
			attr->port_state = BFA_PORT_ST_IOCDIS;
		अन्यथा अगर (bfa_ioc_fw_mismatch(&fcport->bfa->ioc))
			attr->port_state = BFA_PORT_ST_FWMISMATCH;
	पूर्ण

	/* FCoE vlan */
	attr->fcoe_vlan = fcport->fcoe_vlan;
पूर्ण

#घोषणा BFA_FCPORT_STATS_TOV	1000

/*
 * Fetch port statistics (FCQoS or FCoE).
 */
bfa_status_t
bfa_fcport_get_stats(काष्ठा bfa_s *bfa, काष्ठा bfa_cb_pending_q_s *cb)
अणु
	काष्ठा bfa_fcport_s *fcport = BFA_FCPORT_MOD(bfa);

	अगर (!bfa_iocfc_is_operational(bfa) ||
	    !fcport->stats_dma_पढ़ोy)
		वापस BFA_STATUS_IOC_NON_OP;

	अगर (!list_empty(&fcport->statsclr_pending_q))
		वापस BFA_STATUS_DEVBUSY;

	अगर (list_empty(&fcport->stats_pending_q)) अणु
		list_add_tail(&cb->hcb_qe.qe, &fcport->stats_pending_q);
		bfa_fcport_send_stats_get(fcport);
		bfa_समयr_start(bfa, &fcport->समयr,
				bfa_fcport_stats_get_समयout,
				fcport, BFA_FCPORT_STATS_TOV);
	पूर्ण अन्यथा
		list_add_tail(&cb->hcb_qe.qe, &fcport->stats_pending_q);

	वापस BFA_STATUS_OK;
पूर्ण

/*
 * Reset port statistics (FCQoS or FCoE).
 */
bfa_status_t
bfa_fcport_clear_stats(काष्ठा bfa_s *bfa, काष्ठा bfa_cb_pending_q_s *cb)
अणु
	काष्ठा bfa_fcport_s *fcport = BFA_FCPORT_MOD(bfa);

	अगर (!bfa_iocfc_is_operational(bfa) ||
	    !fcport->stats_dma_पढ़ोy)
		वापस BFA_STATUS_IOC_NON_OP;

	अगर (!list_empty(&fcport->stats_pending_q))
		वापस BFA_STATUS_DEVBUSY;

	अगर (list_empty(&fcport->statsclr_pending_q)) अणु
		list_add_tail(&cb->hcb_qe.qe, &fcport->statsclr_pending_q);
		bfa_fcport_send_stats_clear(fcport);
		bfa_समयr_start(bfa, &fcport->समयr,
				bfa_fcport_stats_clr_समयout,
				fcport, BFA_FCPORT_STATS_TOV);
	पूर्ण अन्यथा
		list_add_tail(&cb->hcb_qe.qe, &fcport->statsclr_pending_q);

	वापस BFA_STATUS_OK;
पूर्ण

/*
 * Fetch port attributes.
 */
bfa_boolean_t
bfa_fcport_is_disabled(काष्ठा bfa_s *bfa)
अणु
	काष्ठा bfa_fcport_s *fcport = BFA_FCPORT_MOD(bfa);

	वापस bfa_sm_to_state(hal_port_sm_table, fcport->sm) ==
		BFA_PORT_ST_DISABLED;

पूर्ण

bfa_boolean_t
bfa_fcport_is_dport(काष्ठा bfa_s *bfa)
अणु
	काष्ठा bfa_fcport_s *fcport = BFA_FCPORT_MOD(bfa);

	वापस (bfa_sm_to_state(hal_port_sm_table, fcport->sm) ==
		BFA_PORT_ST_DPORT);
पूर्ण

bfa_boolean_t
bfa_fcport_is_ddport(काष्ठा bfa_s *bfa)
अणु
	काष्ठा bfa_fcport_s *fcport = BFA_FCPORT_MOD(bfa);

	वापस (bfa_sm_to_state(hal_port_sm_table, fcport->sm) ==
		BFA_PORT_ST_DDPORT);
पूर्ण

bfa_status_t
bfa_fcport_set_qos_bw(काष्ठा bfa_s *bfa, काष्ठा bfa_qos_bw_s *qos_bw)
अणु
	काष्ठा bfa_fcport_s *fcport = BFA_FCPORT_MOD(bfa);
	क्रमागत bfa_ioc_type_e ioc_type = bfa_get_type(bfa);

	bfa_trc(bfa, ioc_type);

	अगर ((qos_bw->high == 0) || (qos_bw->med == 0) || (qos_bw->low == 0))
		वापस BFA_STATUS_QOS_BW_INVALID;

	अगर ((qos_bw->high + qos_bw->med + qos_bw->low) != 100)
		वापस BFA_STATUS_QOS_BW_INVALID;

	अगर ((qos_bw->med > qos_bw->high) || (qos_bw->low > qos_bw->med) ||
	    (qos_bw->low > qos_bw->high))
		वापस BFA_STATUS_QOS_BW_INVALID;

	अगर ((ioc_type == BFA_IOC_TYPE_FC) &&
	    (fcport->cfg.topology != BFA_PORT_TOPOLOGY_LOOP))
		fcport->cfg.qos_bw = *qos_bw;

	वापस BFA_STATUS_OK;
पूर्ण

bfa_boolean_t
bfa_fcport_is_ratelim(काष्ठा bfa_s *bfa)
अणु
	काष्ठा bfa_fcport_s *fcport = BFA_FCPORT_MOD(bfa);

	वापस fcport->cfg.ratelimit ? BFA_TRUE : BFA_FALSE;

पूर्ण

/*
 *	Enable/Disable FAA feature in port config
 */
व्योम
bfa_fcport_cfg_faa(काष्ठा bfa_s *bfa, u8 state)
अणु
	काष्ठा bfa_fcport_s *fcport = BFA_FCPORT_MOD(bfa);

	bfa_trc(bfa, state);
	fcport->cfg.faa_state = state;
पूर्ण

/*
 * Get शेष minimum ratelim speed
 */
क्रमागत bfa_port_speed
bfa_fcport_get_ratelim_speed(काष्ठा bfa_s *bfa)
अणु
	काष्ठा bfa_fcport_s *fcport = BFA_FCPORT_MOD(bfa);

	bfa_trc(bfa, fcport->cfg.trl_def_speed);
	वापस fcport->cfg.trl_def_speed;

पूर्ण

व्योम
bfa_fcport_beacon(व्योम *dev, bfa_boolean_t beacon,
		  bfa_boolean_t link_e2e_beacon)
अणु
	काष्ठा bfa_s *bfa = dev;
	काष्ठा bfa_fcport_s *fcport = BFA_FCPORT_MOD(bfa);

	bfa_trc(bfa, beacon);
	bfa_trc(bfa, link_e2e_beacon);
	bfa_trc(bfa, fcport->beacon);
	bfa_trc(bfa, fcport->link_e2e_beacon);

	fcport->beacon = beacon;
	fcport->link_e2e_beacon = link_e2e_beacon;
पूर्ण

bfa_boolean_t
bfa_fcport_is_linkup(काष्ठा bfa_s *bfa)
अणु
	काष्ठा bfa_fcport_s *fcport = BFA_FCPORT_MOD(bfa);

	वापस	(!fcport->cfg.trunked &&
		 bfa_sm_cmp_state(fcport, bfa_fcport_sm_linkup)) ||
		(fcport->cfg.trunked &&
		 fcport->trunk.attr.state == BFA_TRUNK_ONLINE);
पूर्ण

bfa_boolean_t
bfa_fcport_is_qos_enabled(काष्ठा bfa_s *bfa)
अणु
	काष्ठा bfa_fcport_s *fcport = BFA_FCPORT_MOD(bfa);

	वापस fcport->cfg.qos_enabled;
पूर्ण

bfa_boolean_t
bfa_fcport_is_trunk_enabled(काष्ठा bfa_s *bfa)
अणु
	काष्ठा bfa_fcport_s *fcport = BFA_FCPORT_MOD(bfa);

	वापस fcport->cfg.trunked;
पूर्ण

bfa_status_t
bfa_fcport_cfg_bbcr(काष्ठा bfa_s *bfa, bfa_boolean_t on_off, u8 bb_scn)
अणु
	काष्ठा bfa_fcport_s *fcport = BFA_FCPORT_MOD(bfa);

	bfa_trc(bfa, on_off);

	अगर (bfa_ioc_get_type(&fcport->bfa->ioc) != BFA_IOC_TYPE_FC)
		वापस BFA_STATUS_BBCR_FC_ONLY;

	अगर (bfa_mfg_is_mezz(bfa->ioc.attr->card_type) &&
		(bfa->ioc.attr->card_type != BFA_MFG_TYPE_CHINOOK))
		वापस BFA_STATUS_CMD_NOTSUPP_MEZZ;

	अगर (on_off) अणु
		अगर (fcport->cfg.topology == BFA_PORT_TOPOLOGY_LOOP)
			वापस BFA_STATUS_TOPOLOGY_LOOP;

		अगर (fcport->cfg.qos_enabled)
			वापस BFA_STATUS_ERROR_QOS_ENABLED;

		अगर (fcport->cfg.trunked)
			वापस BFA_STATUS_TRUNK_ENABLED;

		अगर ((fcport->cfg.speed != BFA_PORT_SPEED_AUTO) &&
			(fcport->cfg.speed < bfa_ioc_speed_sup(&bfa->ioc)))
			वापस BFA_STATUS_ERR_BBCR_SPEED_UNSUPPORT;

		अगर (bfa_ioc_speed_sup(&bfa->ioc) < BFA_PORT_SPEED_8GBPS)
			वापस BFA_STATUS_FEATURE_NOT_SUPPORTED;

		अगर (fcport->cfg.bb_cr_enabled) अणु
			अगर (bb_scn != fcport->cfg.bb_scn)
				वापस BFA_STATUS_BBCR_CFG_NO_CHANGE;
			अन्यथा
				वापस BFA_STATUS_NO_CHANGE;
		पूर्ण

		अगर ((bb_scn == 0) || (bb_scn > BFA_BB_SCN_MAX))
			bb_scn = BFA_BB_SCN_DEF;

		fcport->cfg.bb_cr_enabled = on_off;
		fcport->cfg.bb_scn = bb_scn;
	पूर्ण अन्यथा अणु
		अगर (!fcport->cfg.bb_cr_enabled)
			वापस BFA_STATUS_NO_CHANGE;

		fcport->cfg.bb_cr_enabled = on_off;
		fcport->cfg.bb_scn = 0;
	पूर्ण

	वापस BFA_STATUS_OK;
पूर्ण

bfa_status_t
bfa_fcport_get_bbcr_attr(काष्ठा bfa_s *bfa,
		काष्ठा bfa_bbcr_attr_s *bbcr_attr)
अणु
	काष्ठा bfa_fcport_s *fcport = BFA_FCPORT_MOD(bfa);

	अगर (bfa_ioc_get_type(&fcport->bfa->ioc) != BFA_IOC_TYPE_FC)
		वापस BFA_STATUS_BBCR_FC_ONLY;

	अगर (fcport->cfg.topology == BFA_PORT_TOPOLOGY_LOOP)
		वापस BFA_STATUS_TOPOLOGY_LOOP;

	*bbcr_attr = fcport->bbcr_attr;

	वापस BFA_STATUS_OK;
पूर्ण

व्योम
bfa_fcport_dportenable(काष्ठा bfa_s *bfa)
अणु
	/*
	 * Assume caller check क्रम port is in disable state
	 */
	bfa_sm_send_event(BFA_FCPORT_MOD(bfa), BFA_FCPORT_SM_DPORTENABLE);
	bfa_port_set_dportenabled(&bfa->modules.port, BFA_TRUE);
पूर्ण

व्योम
bfa_fcport_dportdisable(काष्ठा bfa_s *bfa)
अणु
	/*
	 * Assume caller check क्रम port is in disable state
	 */
	bfa_sm_send_event(BFA_FCPORT_MOD(bfa), BFA_FCPORT_SM_DPORTDISABLE);
	bfa_port_set_dportenabled(&bfa->modules.port, BFA_FALSE);
पूर्ण

अटल व्योम
bfa_fcport_ddportenable(काष्ठा bfa_s *bfa)
अणु
	/*
	 * Assume caller check क्रम port is in disable state
	 */
	bfa_sm_send_event(BFA_FCPORT_MOD(bfa), BFA_FCPORT_SM_DDPORTENABLE);
पूर्ण

अटल व्योम
bfa_fcport_ddportdisable(काष्ठा bfa_s *bfa)
अणु
	/*
	 * Assume caller check क्रम port is in disable state
	 */
	bfa_sm_send_event(BFA_FCPORT_MOD(bfa), BFA_FCPORT_SM_DDPORTDISABLE);
पूर्ण

/*
 * Rport State machine functions
 */
/*
 * Beginning state, only online event expected.
 */
अटल व्योम
bfa_rport_sm_uninit(काष्ठा bfa_rport_s *rp, क्रमागत bfa_rport_event event)
अणु
	bfa_trc(rp->bfa, rp->rport_tag);
	bfa_trc(rp->bfa, event);

	चयन (event) अणु
	हाल BFA_RPORT_SM_CREATE:
		bfa_stats(rp, sm_un_cr);
		bfa_sm_set_state(rp, bfa_rport_sm_created);
		अवरोध;

	शेष:
		bfa_stats(rp, sm_un_unexp);
		bfa_sm_fault(rp->bfa, event);
	पूर्ण
पूर्ण

अटल व्योम
bfa_rport_sm_created(काष्ठा bfa_rport_s *rp, क्रमागत bfa_rport_event event)
अणु
	bfa_trc(rp->bfa, rp->rport_tag);
	bfa_trc(rp->bfa, event);

	चयन (event) अणु
	हाल BFA_RPORT_SM_ONLINE:
		bfa_stats(rp, sm_cr_on);
		अगर (bfa_rport_send_fwcreate(rp))
			bfa_sm_set_state(rp, bfa_rport_sm_fwcreate);
		अन्यथा
			bfa_sm_set_state(rp, bfa_rport_sm_fwcreate_qfull);
		अवरोध;

	हाल BFA_RPORT_SM_DELETE:
		bfa_stats(rp, sm_cr_del);
		bfa_sm_set_state(rp, bfa_rport_sm_uninit);
		bfa_rport_मुक्त(rp);
		अवरोध;

	हाल BFA_RPORT_SM_HWFAIL:
		bfa_stats(rp, sm_cr_hwf);
		bfa_sm_set_state(rp, bfa_rport_sm_iocdisable);
		अवरोध;

	शेष:
		bfa_stats(rp, sm_cr_unexp);
		bfa_sm_fault(rp->bfa, event);
	पूर्ण
पूर्ण

/*
 * Waiting क्रम rport create response from firmware.
 */
अटल व्योम
bfa_rport_sm_fwcreate(काष्ठा bfa_rport_s *rp, क्रमागत bfa_rport_event event)
अणु
	bfa_trc(rp->bfa, rp->rport_tag);
	bfa_trc(rp->bfa, event);

	चयन (event) अणु
	हाल BFA_RPORT_SM_FWRSP:
		bfa_stats(rp, sm_fwc_rsp);
		bfa_sm_set_state(rp, bfa_rport_sm_online);
		bfa_rport_online_cb(rp);
		अवरोध;

	हाल BFA_RPORT_SM_DELETE:
		bfa_stats(rp, sm_fwc_del);
		bfa_sm_set_state(rp, bfa_rport_sm_delete_pending);
		अवरोध;

	हाल BFA_RPORT_SM_OFFLINE:
		bfa_stats(rp, sm_fwc_off);
		bfa_sm_set_state(rp, bfa_rport_sm_offline_pending);
		अवरोध;

	हाल BFA_RPORT_SM_HWFAIL:
		bfa_stats(rp, sm_fwc_hwf);
		bfa_sm_set_state(rp, bfa_rport_sm_iocdisable);
		अवरोध;

	शेष:
		bfa_stats(rp, sm_fwc_unexp);
		bfa_sm_fault(rp->bfa, event);
	पूर्ण
पूर्ण

/*
 * Request queue is full, aरुकोing queue resume to send create request.
 */
अटल व्योम
bfa_rport_sm_fwcreate_qfull(काष्ठा bfa_rport_s *rp, क्रमागत bfa_rport_event event)
अणु
	bfa_trc(rp->bfa, rp->rport_tag);
	bfa_trc(rp->bfa, event);

	चयन (event) अणु
	हाल BFA_RPORT_SM_QRESUME:
		bfa_sm_set_state(rp, bfa_rport_sm_fwcreate);
		bfa_rport_send_fwcreate(rp);
		अवरोध;

	हाल BFA_RPORT_SM_DELETE:
		bfa_stats(rp, sm_fwc_del);
		bfa_sm_set_state(rp, bfa_rport_sm_uninit);
		bfa_reqq_wcancel(&rp->reqq_रुको);
		bfa_rport_मुक्त(rp);
		अवरोध;

	हाल BFA_RPORT_SM_OFFLINE:
		bfa_stats(rp, sm_fwc_off);
		bfa_sm_set_state(rp, bfa_rport_sm_offline);
		bfa_reqq_wcancel(&rp->reqq_रुको);
		bfa_rport_offline_cb(rp);
		अवरोध;

	हाल BFA_RPORT_SM_HWFAIL:
		bfa_stats(rp, sm_fwc_hwf);
		bfa_sm_set_state(rp, bfa_rport_sm_iocdisable);
		bfa_reqq_wcancel(&rp->reqq_रुको);
		अवरोध;

	शेष:
		bfa_stats(rp, sm_fwc_unexp);
		bfa_sm_fault(rp->bfa, event);
	पूर्ण
पूर्ण

/*
 * Online state - normal parking state.
 */
अटल व्योम
bfa_rport_sm_online(काष्ठा bfa_rport_s *rp, क्रमागत bfa_rport_event event)
अणु
	काष्ठा bfi_rport_qos_scn_s *qos_scn;

	bfa_trc(rp->bfa, rp->rport_tag);
	bfa_trc(rp->bfa, event);

	चयन (event) अणु
	हाल BFA_RPORT_SM_OFFLINE:
		bfa_stats(rp, sm_on_off);
		अगर (bfa_rport_send_fwdelete(rp))
			bfa_sm_set_state(rp, bfa_rport_sm_fwdelete);
		अन्यथा
			bfa_sm_set_state(rp, bfa_rport_sm_fwdelete_qfull);
		अवरोध;

	हाल BFA_RPORT_SM_DELETE:
		bfa_stats(rp, sm_on_del);
		अगर (bfa_rport_send_fwdelete(rp))
			bfa_sm_set_state(rp, bfa_rport_sm_deleting);
		अन्यथा
			bfa_sm_set_state(rp, bfa_rport_sm_deleting_qfull);
		अवरोध;

	हाल BFA_RPORT_SM_HWFAIL:
		bfa_stats(rp, sm_on_hwf);
		bfa_sm_set_state(rp, bfa_rport_sm_iocdisable);
		अवरोध;

	हाल BFA_RPORT_SM_SET_SPEED:
		bfa_rport_send_fwspeed(rp);
		अवरोध;

	हाल BFA_RPORT_SM_QOS_SCN:
		qos_scn = (काष्ठा bfi_rport_qos_scn_s *) rp->event_arg.fw_msg;
		rp->qos_attr = qos_scn->new_qos_attr;
		bfa_trc(rp->bfa, qos_scn->old_qos_attr.qos_flow_id);
		bfa_trc(rp->bfa, qos_scn->new_qos_attr.qos_flow_id);
		bfa_trc(rp->bfa, qos_scn->old_qos_attr.qos_priority);
		bfa_trc(rp->bfa, qos_scn->new_qos_attr.qos_priority);

		qos_scn->old_qos_attr.qos_flow_id  =
			be32_to_cpu(qos_scn->old_qos_attr.qos_flow_id);
		qos_scn->new_qos_attr.qos_flow_id  =
			be32_to_cpu(qos_scn->new_qos_attr.qos_flow_id);

		अगर (qos_scn->old_qos_attr.qos_flow_id !=
			qos_scn->new_qos_attr.qos_flow_id)
			bfa_cb_rport_qos_scn_flowid(rp->rport_drv,
						    qos_scn->old_qos_attr,
						    qos_scn->new_qos_attr);
		अगर (qos_scn->old_qos_attr.qos_priority !=
			qos_scn->new_qos_attr.qos_priority)
			bfa_cb_rport_qos_scn_prio(rp->rport_drv,
						  qos_scn->old_qos_attr,
						  qos_scn->new_qos_attr);
		अवरोध;

	शेष:
		bfa_stats(rp, sm_on_unexp);
		bfa_sm_fault(rp->bfa, event);
	पूर्ण
पूर्ण

/*
 * Firmware rport is being deleted - aरुकोing f/w response.
 */
अटल व्योम
bfa_rport_sm_fwdelete(काष्ठा bfa_rport_s *rp, क्रमागत bfa_rport_event event)
अणु
	bfa_trc(rp->bfa, rp->rport_tag);
	bfa_trc(rp->bfa, event);

	चयन (event) अणु
	हाल BFA_RPORT_SM_FWRSP:
		bfa_stats(rp, sm_fwd_rsp);
		bfa_sm_set_state(rp, bfa_rport_sm_offline);
		bfa_rport_offline_cb(rp);
		अवरोध;

	हाल BFA_RPORT_SM_DELETE:
		bfa_stats(rp, sm_fwd_del);
		bfa_sm_set_state(rp, bfa_rport_sm_deleting);
		अवरोध;

	हाल BFA_RPORT_SM_HWFAIL:
		bfa_stats(rp, sm_fwd_hwf);
		bfa_sm_set_state(rp, bfa_rport_sm_iocdisable);
		bfa_rport_offline_cb(rp);
		अवरोध;

	शेष:
		bfa_stats(rp, sm_fwd_unexp);
		bfa_sm_fault(rp->bfa, event);
	पूर्ण
पूर्ण

अटल व्योम
bfa_rport_sm_fwdelete_qfull(काष्ठा bfa_rport_s *rp, क्रमागत bfa_rport_event event)
अणु
	bfa_trc(rp->bfa, rp->rport_tag);
	bfa_trc(rp->bfa, event);

	चयन (event) अणु
	हाल BFA_RPORT_SM_QRESUME:
		bfa_sm_set_state(rp, bfa_rport_sm_fwdelete);
		bfa_rport_send_fwdelete(rp);
		अवरोध;

	हाल BFA_RPORT_SM_DELETE:
		bfa_stats(rp, sm_fwd_del);
		bfa_sm_set_state(rp, bfa_rport_sm_deleting_qfull);
		अवरोध;

	हाल BFA_RPORT_SM_HWFAIL:
		bfa_stats(rp, sm_fwd_hwf);
		bfa_sm_set_state(rp, bfa_rport_sm_iocdisable);
		bfa_reqq_wcancel(&rp->reqq_रुको);
		bfa_rport_offline_cb(rp);
		अवरोध;

	शेष:
		bfa_stats(rp, sm_fwd_unexp);
		bfa_sm_fault(rp->bfa, event);
	पूर्ण
पूर्ण

/*
 * Offline state.
 */
अटल व्योम
bfa_rport_sm_offline(काष्ठा bfa_rport_s *rp, क्रमागत bfa_rport_event event)
अणु
	bfa_trc(rp->bfa, rp->rport_tag);
	bfa_trc(rp->bfa, event);

	चयन (event) अणु
	हाल BFA_RPORT_SM_DELETE:
		bfa_stats(rp, sm_off_del);
		bfa_sm_set_state(rp, bfa_rport_sm_uninit);
		bfa_rport_मुक्त(rp);
		अवरोध;

	हाल BFA_RPORT_SM_ONLINE:
		bfa_stats(rp, sm_off_on);
		अगर (bfa_rport_send_fwcreate(rp))
			bfa_sm_set_state(rp, bfa_rport_sm_fwcreate);
		अन्यथा
			bfa_sm_set_state(rp, bfa_rport_sm_fwcreate_qfull);
		अवरोध;

	हाल BFA_RPORT_SM_HWFAIL:
		bfa_stats(rp, sm_off_hwf);
		bfa_sm_set_state(rp, bfa_rport_sm_iocdisable);
		अवरोध;

	हाल BFA_RPORT_SM_OFFLINE:
		bfa_rport_offline_cb(rp);
		अवरोध;

	शेष:
		bfa_stats(rp, sm_off_unexp);
		bfa_sm_fault(rp->bfa, event);
	पूर्ण
पूर्ण

/*
 * Rport is deleted, रुकोing क्रम firmware response to delete.
 */
अटल व्योम
bfa_rport_sm_deleting(काष्ठा bfa_rport_s *rp, क्रमागत bfa_rport_event event)
अणु
	bfa_trc(rp->bfa, rp->rport_tag);
	bfa_trc(rp->bfa, event);

	चयन (event) अणु
	हाल BFA_RPORT_SM_FWRSP:
		bfa_stats(rp, sm_del_fwrsp);
		bfa_sm_set_state(rp, bfa_rport_sm_uninit);
		bfa_rport_मुक्त(rp);
		अवरोध;

	हाल BFA_RPORT_SM_HWFAIL:
		bfa_stats(rp, sm_del_hwf);
		bfa_sm_set_state(rp, bfa_rport_sm_uninit);
		bfa_rport_मुक्त(rp);
		अवरोध;

	शेष:
		bfa_sm_fault(rp->bfa, event);
	पूर्ण
पूर्ण

अटल व्योम
bfa_rport_sm_deleting_qfull(काष्ठा bfa_rport_s *rp, क्रमागत bfa_rport_event event)
अणु
	bfa_trc(rp->bfa, rp->rport_tag);
	bfa_trc(rp->bfa, event);

	चयन (event) अणु
	हाल BFA_RPORT_SM_QRESUME:
		bfa_stats(rp, sm_del_fwrsp);
		bfa_sm_set_state(rp, bfa_rport_sm_deleting);
		bfa_rport_send_fwdelete(rp);
		अवरोध;

	हाल BFA_RPORT_SM_HWFAIL:
		bfa_stats(rp, sm_del_hwf);
		bfa_sm_set_state(rp, bfa_rport_sm_uninit);
		bfa_reqq_wcancel(&rp->reqq_रुको);
		bfa_rport_मुक्त(rp);
		अवरोध;

	शेष:
		bfa_sm_fault(rp->bfa, event);
	पूर्ण
पूर्ण

/*
 * Waiting क्रम rport create response from firmware. A delete is pending.
 */
अटल व्योम
bfa_rport_sm_delete_pending(काष्ठा bfa_rport_s *rp,
				क्रमागत bfa_rport_event event)
अणु
	bfa_trc(rp->bfa, rp->rport_tag);
	bfa_trc(rp->bfa, event);

	चयन (event) अणु
	हाल BFA_RPORT_SM_FWRSP:
		bfa_stats(rp, sm_delp_fwrsp);
		अगर (bfa_rport_send_fwdelete(rp))
			bfa_sm_set_state(rp, bfa_rport_sm_deleting);
		अन्यथा
			bfa_sm_set_state(rp, bfa_rport_sm_deleting_qfull);
		अवरोध;

	हाल BFA_RPORT_SM_HWFAIL:
		bfa_stats(rp, sm_delp_hwf);
		bfa_sm_set_state(rp, bfa_rport_sm_uninit);
		bfa_rport_मुक्त(rp);
		अवरोध;

	शेष:
		bfa_stats(rp, sm_delp_unexp);
		bfa_sm_fault(rp->bfa, event);
	पूर्ण
पूर्ण

/*
 * Waiting क्रम rport create response from firmware. Rport offline is pending.
 */
अटल व्योम
bfa_rport_sm_offline_pending(काष्ठा bfa_rport_s *rp,
				 क्रमागत bfa_rport_event event)
अणु
	bfa_trc(rp->bfa, rp->rport_tag);
	bfa_trc(rp->bfa, event);

	चयन (event) अणु
	हाल BFA_RPORT_SM_FWRSP:
		bfa_stats(rp, sm_offp_fwrsp);
		अगर (bfa_rport_send_fwdelete(rp))
			bfa_sm_set_state(rp, bfa_rport_sm_fwdelete);
		अन्यथा
			bfa_sm_set_state(rp, bfa_rport_sm_fwdelete_qfull);
		अवरोध;

	हाल BFA_RPORT_SM_DELETE:
		bfa_stats(rp, sm_offp_del);
		bfa_sm_set_state(rp, bfa_rport_sm_delete_pending);
		अवरोध;

	हाल BFA_RPORT_SM_HWFAIL:
		bfa_stats(rp, sm_offp_hwf);
		bfa_sm_set_state(rp, bfa_rport_sm_iocdisable);
		bfa_rport_offline_cb(rp);
		अवरोध;

	शेष:
		bfa_stats(rp, sm_offp_unexp);
		bfa_sm_fault(rp->bfa, event);
	पूर्ण
पूर्ण

/*
 * IOC h/w failed.
 */
अटल व्योम
bfa_rport_sm_iocdisable(काष्ठा bfa_rport_s *rp, क्रमागत bfa_rport_event event)
अणु
	bfa_trc(rp->bfa, rp->rport_tag);
	bfa_trc(rp->bfa, event);

	चयन (event) अणु
	हाल BFA_RPORT_SM_OFFLINE:
		bfa_stats(rp, sm_iocd_off);
		bfa_rport_offline_cb(rp);
		अवरोध;

	हाल BFA_RPORT_SM_DELETE:
		bfa_stats(rp, sm_iocd_del);
		bfa_sm_set_state(rp, bfa_rport_sm_uninit);
		bfa_rport_मुक्त(rp);
		अवरोध;

	हाल BFA_RPORT_SM_ONLINE:
		bfa_stats(rp, sm_iocd_on);
		अगर (bfa_rport_send_fwcreate(rp))
			bfa_sm_set_state(rp, bfa_rport_sm_fwcreate);
		अन्यथा
			bfa_sm_set_state(rp, bfa_rport_sm_fwcreate_qfull);
		अवरोध;

	हाल BFA_RPORT_SM_HWFAIL:
		अवरोध;

	शेष:
		bfa_stats(rp, sm_iocd_unexp);
		bfa_sm_fault(rp->bfa, event);
	पूर्ण
पूर्ण



/*
 *  bfa_rport_निजी BFA rport निजी functions
 */

अटल व्योम
__bfa_cb_rport_online(व्योम *cbarg, bfa_boolean_t complete)
अणु
	काष्ठा bfa_rport_s *rp = cbarg;

	अगर (complete)
		bfa_cb_rport_online(rp->rport_drv);
पूर्ण

अटल व्योम
__bfa_cb_rport_offline(व्योम *cbarg, bfa_boolean_t complete)
अणु
	काष्ठा bfa_rport_s *rp = cbarg;

	अगर (complete)
		bfa_cb_rport_offline(rp->rport_drv);
पूर्ण

अटल व्योम
bfa_rport_qresume(व्योम *cbarg)
अणु
	काष्ठा bfa_rport_s	*rp = cbarg;

	bfa_sm_send_event(rp, BFA_RPORT_SM_QRESUME);
पूर्ण

व्योम
bfa_rport_meminfo(काष्ठा bfa_iocfc_cfg_s *cfg, काष्ठा bfa_meminfo_s *minfo,
		काष्ठा bfa_s *bfa)
अणु
	काष्ठा bfa_mem_kva_s *rport_kva = BFA_MEM_RPORT_KVA(bfa);

	अगर (cfg->fwcfg.num_rports < BFA_RPORT_MIN)
		cfg->fwcfg.num_rports = BFA_RPORT_MIN;

	/* kva memory */
	bfa_mem_kva_setup(minfo, rport_kva,
		cfg->fwcfg.num_rports * माप(काष्ठा bfa_rport_s));
पूर्ण

व्योम
bfa_rport_attach(काष्ठा bfa_s *bfa, व्योम *bfad, काष्ठा bfa_iocfc_cfg_s *cfg,
		काष्ठा bfa_pcidev_s *pcidev)
अणु
	काष्ठा bfa_rport_mod_s *mod = BFA_RPORT_MOD(bfa);
	काष्ठा bfa_rport_s *rp;
	u16 i;

	INIT_LIST_HEAD(&mod->rp_मुक्त_q);
	INIT_LIST_HEAD(&mod->rp_active_q);
	INIT_LIST_HEAD(&mod->rp_unused_q);

	rp = (काष्ठा bfa_rport_s *) bfa_mem_kva_curp(mod);
	mod->rps_list = rp;
	mod->num_rports = cfg->fwcfg.num_rports;

	WARN_ON(!mod->num_rports ||
		   (mod->num_rports & (mod->num_rports - 1)));

	क्रम (i = 0; i < mod->num_rports; i++, rp++) अणु
		स_रखो(rp, 0, माप(काष्ठा bfa_rport_s));
		rp->bfa = bfa;
		rp->rport_tag = i;
		bfa_sm_set_state(rp, bfa_rport_sm_uninit);

		/*
		 *  - is unused
		 */
		अगर (i)
			list_add_tail(&rp->qe, &mod->rp_मुक्त_q);

		bfa_reqq_winit(&rp->reqq_रुको, bfa_rport_qresume, rp);
	पूर्ण

	/*
	 * consume memory
	 */
	bfa_mem_kva_curp(mod) = (u8 *) rp;
पूर्ण

व्योम
bfa_rport_iocdisable(काष्ठा bfa_s *bfa)
अणु
	काष्ठा bfa_rport_mod_s *mod = BFA_RPORT_MOD(bfa);
	काष्ठा bfa_rport_s *rport;
	काष्ठा list_head *qe, *qen;

	/* Enqueue unused rport resources to मुक्त_q */
	list_splice_tail_init(&mod->rp_unused_q, &mod->rp_मुक्त_q);

	list_क्रम_each_safe(qe, qen, &mod->rp_active_q) अणु
		rport = (काष्ठा bfa_rport_s *) qe;
		bfa_sm_send_event(rport, BFA_RPORT_SM_HWFAIL);
	पूर्ण
पूर्ण

अटल काष्ठा bfa_rport_s *
bfa_rport_alloc(काष्ठा bfa_rport_mod_s *mod)
अणु
	काष्ठा bfa_rport_s *rport;

	bfa_q_deq(&mod->rp_मुक्त_q, &rport);
	अगर (rport)
		list_add_tail(&rport->qe, &mod->rp_active_q);

	वापस rport;
पूर्ण

अटल व्योम
bfa_rport_मुक्त(काष्ठा bfa_rport_s *rport)
अणु
	काष्ठा bfa_rport_mod_s *mod = BFA_RPORT_MOD(rport->bfa);

	WARN_ON(!bfa_q_is_on_q(&mod->rp_active_q, rport));
	list_del(&rport->qe);
	list_add_tail(&rport->qe, &mod->rp_मुक्त_q);
पूर्ण

अटल bfa_boolean_t
bfa_rport_send_fwcreate(काष्ठा bfa_rport_s *rp)
अणु
	काष्ठा bfi_rport_create_req_s *m;

	/*
	 * check क्रम room in queue to send request now
	 */
	m = bfa_reqq_next(rp->bfa, BFA_REQQ_RPORT);
	अगर (!m) अणु
		bfa_reqq_रुको(rp->bfa, BFA_REQQ_RPORT, &rp->reqq_रुको);
		वापस BFA_FALSE;
	पूर्ण

	bfi_h2i_set(m->mh, BFI_MC_RPORT, BFI_RPORT_H2I_CREATE_REQ,
			bfa_fn_lpu(rp->bfa));
	m->bfa_handle = rp->rport_tag;
	m->max_frmsz = cpu_to_be16(rp->rport_info.max_frmsz);
	m->pid = rp->rport_info.pid;
	m->lp_fwtag = bfa_lps_get_fwtag(rp->bfa, (u8)rp->rport_info.lp_tag);
	m->local_pid = rp->rport_info.local_pid;
	m->fc_class = rp->rport_info.fc_class;
	m->vf_en = rp->rport_info.vf_en;
	m->vf_id = rp->rport_info.vf_id;
	m->cisc = rp->rport_info.cisc;

	/*
	 * queue I/O message to firmware
	 */
	bfa_reqq_produce(rp->bfa, BFA_REQQ_RPORT, m->mh);
	वापस BFA_TRUE;
पूर्ण

अटल bfa_boolean_t
bfa_rport_send_fwdelete(काष्ठा bfa_rport_s *rp)
अणु
	काष्ठा bfi_rport_delete_req_s *m;

	/*
	 * check क्रम room in queue to send request now
	 */
	m = bfa_reqq_next(rp->bfa, BFA_REQQ_RPORT);
	अगर (!m) अणु
		bfa_reqq_रुको(rp->bfa, BFA_REQQ_RPORT, &rp->reqq_रुको);
		वापस BFA_FALSE;
	पूर्ण

	bfi_h2i_set(m->mh, BFI_MC_RPORT, BFI_RPORT_H2I_DELETE_REQ,
			bfa_fn_lpu(rp->bfa));
	m->fw_handle = rp->fw_handle;

	/*
	 * queue I/O message to firmware
	 */
	bfa_reqq_produce(rp->bfa, BFA_REQQ_RPORT, m->mh);
	वापस BFA_TRUE;
पूर्ण

अटल bfa_boolean_t
bfa_rport_send_fwspeed(काष्ठा bfa_rport_s *rp)
अणु
	काष्ठा bfa_rport_speed_req_s *m;

	/*
	 * check क्रम room in queue to send request now
	 */
	m = bfa_reqq_next(rp->bfa, BFA_REQQ_RPORT);
	अगर (!m) अणु
		bfa_trc(rp->bfa, rp->rport_info.speed);
		वापस BFA_FALSE;
	पूर्ण

	bfi_h2i_set(m->mh, BFI_MC_RPORT, BFI_RPORT_H2I_SET_SPEED_REQ,
			bfa_fn_lpu(rp->bfa));
	m->fw_handle = rp->fw_handle;
	m->speed = (u8)rp->rport_info.speed;

	/*
	 * queue I/O message to firmware
	 */
	bfa_reqq_produce(rp->bfa, BFA_REQQ_RPORT, m->mh);
	वापस BFA_TRUE;
पूर्ण



/*
 *  bfa_rport_खुला
 */

/*
 * Rport पूर्णांकerrupt processing.
 */
व्योम
bfa_rport_isr(काष्ठा bfa_s *bfa, काष्ठा bfi_msg_s *m)
अणु
	जोड़ bfi_rport_i2h_msg_u msg;
	काष्ठा bfa_rport_s *rp;

	bfa_trc(bfa, m->mhdr.msg_id);

	msg.msg = m;

	चयन (m->mhdr.msg_id) अणु
	हाल BFI_RPORT_I2H_CREATE_RSP:
		rp = BFA_RPORT_FROM_TAG(bfa, msg.create_rsp->bfa_handle);
		rp->fw_handle = msg.create_rsp->fw_handle;
		rp->qos_attr = msg.create_rsp->qos_attr;
		bfa_rport_set_lunmask(bfa, rp);
		WARN_ON(msg.create_rsp->status != BFA_STATUS_OK);
		bfa_sm_send_event(rp, BFA_RPORT_SM_FWRSP);
		अवरोध;

	हाल BFI_RPORT_I2H_DELETE_RSP:
		rp = BFA_RPORT_FROM_TAG(bfa, msg.delete_rsp->bfa_handle);
		WARN_ON(msg.delete_rsp->status != BFA_STATUS_OK);
		bfa_rport_unset_lunmask(bfa, rp);
		bfa_sm_send_event(rp, BFA_RPORT_SM_FWRSP);
		अवरोध;

	हाल BFI_RPORT_I2H_QOS_SCN:
		rp = BFA_RPORT_FROM_TAG(bfa, msg.qos_scn_evt->bfa_handle);
		rp->event_arg.fw_msg = msg.qos_scn_evt;
		bfa_sm_send_event(rp, BFA_RPORT_SM_QOS_SCN);
		अवरोध;

	हाल BFI_RPORT_I2H_LIP_SCN_ONLINE:
		bfa_fcport_update_loop_info(BFA_FCPORT_MOD(bfa),
				&msg.lip_scn->loop_info);
		bfa_cb_rport_scn_online(bfa);
		अवरोध;

	हाल BFI_RPORT_I2H_LIP_SCN_OFFLINE:
		bfa_cb_rport_scn_offline(bfa);
		अवरोध;

	हाल BFI_RPORT_I2H_NO_DEV:
		rp = BFA_RPORT_FROM_TAG(bfa, msg.lip_scn->bfa_handle);
		bfa_cb_rport_scn_no_dev(rp->rport_drv);
		अवरोध;

	शेष:
		bfa_trc(bfa, m->mhdr.msg_id);
		WARN_ON(1);
	पूर्ण
पूर्ण

व्योम
bfa_rport_res_recfg(काष्ठा bfa_s *bfa, u16 num_rport_fw)
अणु
	काष्ठा bfa_rport_mod_s	*mod = BFA_RPORT_MOD(bfa);
	काष्ठा list_head	*qe;
	पूर्णांक	i;

	क्रम (i = 0; i < (mod->num_rports - num_rport_fw); i++) अणु
		bfa_q_deq_tail(&mod->rp_मुक्त_q, &qe);
		list_add_tail(qe, &mod->rp_unused_q);
	पूर्ण
पूर्ण

/*
 *  bfa_rport_api
 */

काष्ठा bfa_rport_s *
bfa_rport_create(काष्ठा bfa_s *bfa, व्योम *rport_drv)
अणु
	काष्ठा bfa_rport_s *rp;

	rp = bfa_rport_alloc(BFA_RPORT_MOD(bfa));

	अगर (rp == शून्य)
		वापस शून्य;

	rp->bfa = bfa;
	rp->rport_drv = rport_drv;
	स_रखो(&rp->stats, 0, माप(rp->stats));

	WARN_ON(!bfa_sm_cmp_state(rp, bfa_rport_sm_uninit));
	bfa_sm_send_event(rp, BFA_RPORT_SM_CREATE);

	वापस rp;
पूर्ण

व्योम
bfa_rport_online(काष्ठा bfa_rport_s *rport, काष्ठा bfa_rport_info_s *rport_info)
अणु
	WARN_ON(rport_info->max_frmsz == 0);

	/*
	 * Some JBODs are seen to be not setting PDU size correctly in PLOGI
	 * responses. Default to minimum size.
	 */
	अगर (rport_info->max_frmsz == 0) अणु
		bfa_trc(rport->bfa, rport->rport_tag);
		rport_info->max_frmsz = FC_MIN_PDUSZ;
	पूर्ण

	rport->rport_info = *rport_info;
	bfa_sm_send_event(rport, BFA_RPORT_SM_ONLINE);
पूर्ण

व्योम
bfa_rport_speed(काष्ठा bfa_rport_s *rport, क्रमागत bfa_port_speed speed)
अणु
	WARN_ON(speed == 0);
	WARN_ON(speed == BFA_PORT_SPEED_AUTO);

	अगर (rport) अणु
		rport->rport_info.speed = speed;
		bfa_sm_send_event(rport, BFA_RPORT_SM_SET_SPEED);
	पूर्ण
पूर्ण

/* Set Rport LUN Mask */
व्योम
bfa_rport_set_lunmask(काष्ठा bfa_s *bfa, काष्ठा bfa_rport_s *rp)
अणु
	काष्ठा bfa_lps_mod_s	*lps_mod = BFA_LPS_MOD(bfa);
	wwn_t	lp_wwn, rp_wwn;
	u8 lp_tag = (u8)rp->rport_info.lp_tag;

	rp_wwn = ((काष्ठा bfa_fcs_rport_s *)rp->rport_drv)->pwwn;
	lp_wwn = (BFA_LPS_FROM_TAG(lps_mod, rp->rport_info.lp_tag))->pwwn;

	BFA_LPS_FROM_TAG(lps_mod, rp->rport_info.lp_tag)->lun_mask =
					rp->lun_mask = BFA_TRUE;
	bfa_fcpim_lunmask_rp_update(bfa, lp_wwn, rp_wwn, rp->rport_tag, lp_tag);
पूर्ण

/* Unset Rport LUN mask */
व्योम
bfa_rport_unset_lunmask(काष्ठा bfa_s *bfa, काष्ठा bfa_rport_s *rp)
अणु
	काष्ठा bfa_lps_mod_s	*lps_mod = BFA_LPS_MOD(bfa);
	wwn_t	lp_wwn, rp_wwn;

	rp_wwn = ((काष्ठा bfa_fcs_rport_s *)rp->rport_drv)->pwwn;
	lp_wwn = (BFA_LPS_FROM_TAG(lps_mod, rp->rport_info.lp_tag))->pwwn;

	BFA_LPS_FROM_TAG(lps_mod, rp->rport_info.lp_tag)->lun_mask =
				rp->lun_mask = BFA_FALSE;
	bfa_fcpim_lunmask_rp_update(bfa, lp_wwn, rp_wwn,
			BFA_RPORT_TAG_INVALID, BFA_LP_TAG_INVALID);
पूर्ण

/*
 * SGPG related functions
 */

/*
 * Compute and वापस memory needed by FCP(im) module.
 */
व्योम
bfa_sgpg_meminfo(काष्ठा bfa_iocfc_cfg_s *cfg, काष्ठा bfa_meminfo_s *minfo,
		काष्ठा bfa_s *bfa)
अणु
	काष्ठा bfa_sgpg_mod_s *sgpg_mod = BFA_SGPG_MOD(bfa);
	काष्ठा bfa_mem_kva_s *sgpg_kva = BFA_MEM_SGPG_KVA(bfa);
	काष्ठा bfa_mem_dma_s *seg_ptr;
	u16	nsegs, idx, per_seg_sgpg, num_sgpg;
	u32	sgpg_sz = माप(काष्ठा bfi_sgpg_s);

	अगर (cfg->drvcfg.num_sgpgs < BFA_SGPG_MIN)
		cfg->drvcfg.num_sgpgs = BFA_SGPG_MIN;
	अन्यथा अगर (cfg->drvcfg.num_sgpgs > BFA_SGPG_MAX)
		cfg->drvcfg.num_sgpgs = BFA_SGPG_MAX;

	num_sgpg = cfg->drvcfg.num_sgpgs;

	nsegs = BFI_MEM_DMA_NSEGS(num_sgpg, sgpg_sz);
	per_seg_sgpg = BFI_MEM_NREQS_SEG(sgpg_sz);

	bfa_mem_dma_seg_iter(sgpg_mod, seg_ptr, nsegs, idx) अणु
		अगर (num_sgpg >= per_seg_sgpg) अणु
			num_sgpg -= per_seg_sgpg;
			bfa_mem_dma_setup(minfo, seg_ptr,
					per_seg_sgpg * sgpg_sz);
		पूर्ण अन्यथा
			bfa_mem_dma_setup(minfo, seg_ptr,
					num_sgpg * sgpg_sz);
	पूर्ण

	/* kva memory */
	bfa_mem_kva_setup(minfo, sgpg_kva,
		cfg->drvcfg.num_sgpgs * माप(काष्ठा bfa_sgpg_s));
पूर्ण

व्योम
bfa_sgpg_attach(काष्ठा bfa_s *bfa, व्योम *bfad, काष्ठा bfa_iocfc_cfg_s *cfg,
		काष्ठा bfa_pcidev_s *pcidev)
अणु
	काष्ठा bfa_sgpg_mod_s *mod = BFA_SGPG_MOD(bfa);
	काष्ठा bfa_sgpg_s *hsgpg;
	काष्ठा bfi_sgpg_s *sgpg;
	u64 align_len;
	काष्ठा bfa_mem_dma_s *seg_ptr;
	u32	sgpg_sz = माप(काष्ठा bfi_sgpg_s);
	u16	i, idx, nsegs, per_seg_sgpg, num_sgpg;

	जोड़ अणु
		u64 pa;
		जोड़ bfi_addr_u addr;
	पूर्ण sgpg_pa, sgpg_pa_पंचांगp;

	INIT_LIST_HEAD(&mod->sgpg_q);
	INIT_LIST_HEAD(&mod->sgpg_रुको_q);

	bfa_trc(bfa, cfg->drvcfg.num_sgpgs);

	mod->मुक्त_sgpgs = mod->num_sgpgs = cfg->drvcfg.num_sgpgs;

	num_sgpg = cfg->drvcfg.num_sgpgs;
	nsegs = BFI_MEM_DMA_NSEGS(num_sgpg, sgpg_sz);

	/* dma/kva mem claim */
	hsgpg = (काष्ठा bfa_sgpg_s *) bfa_mem_kva_curp(mod);

	bfa_mem_dma_seg_iter(mod, seg_ptr, nsegs, idx) अणु

		अगर (!bfa_mem_dma_virt(seg_ptr))
			अवरोध;

		align_len = BFA_SGPG_ROUNDUP(bfa_mem_dma_phys(seg_ptr)) -
					     bfa_mem_dma_phys(seg_ptr);

		sgpg = (काष्ठा bfi_sgpg_s *)
			(((u8 *) bfa_mem_dma_virt(seg_ptr)) + align_len);
		sgpg_pa.pa = bfa_mem_dma_phys(seg_ptr) + align_len;
		WARN_ON(sgpg_pa.pa & (sgpg_sz - 1));

		per_seg_sgpg = (seg_ptr->mem_len - (u32)align_len) / sgpg_sz;

		क्रम (i = 0; num_sgpg > 0 && i < per_seg_sgpg; i++, num_sgpg--) अणु
			स_रखो(hsgpg, 0, माप(*hsgpg));
			स_रखो(sgpg, 0, माप(*sgpg));

			hsgpg->sgpg = sgpg;
			sgpg_pa_पंचांगp.pa = bfa_sgaddr_le(sgpg_pa.pa);
			hsgpg->sgpg_pa = sgpg_pa_पंचांगp.addr;
			list_add_tail(&hsgpg->qe, &mod->sgpg_q);

			sgpg++;
			hsgpg++;
			sgpg_pa.pa += sgpg_sz;
		पूर्ण
	पूर्ण

	bfa_mem_kva_curp(mod) = (u8 *) hsgpg;
पूर्ण

bfa_status_t
bfa_sgpg_दो_स्मृति(काष्ठा bfa_s *bfa, काष्ठा list_head *sgpg_q, पूर्णांक nsgpgs)
अणु
	काष्ठा bfa_sgpg_mod_s *mod = BFA_SGPG_MOD(bfa);
	काष्ठा bfa_sgpg_s *hsgpg;
	पूर्णांक i;

	अगर (mod->मुक्त_sgpgs < nsgpgs)
		वापस BFA_STATUS_ENOMEM;

	क्रम (i = 0; i < nsgpgs; i++) अणु
		bfa_q_deq(&mod->sgpg_q, &hsgpg);
		WARN_ON(!hsgpg);
		list_add_tail(&hsgpg->qe, sgpg_q);
	पूर्ण

	mod->मुक्त_sgpgs -= nsgpgs;
	वापस BFA_STATUS_OK;
पूर्ण

व्योम
bfa_sgpg_mमुक्त(काष्ठा bfa_s *bfa, काष्ठा list_head *sgpg_q, पूर्णांक nsgpg)
अणु
	काष्ठा bfa_sgpg_mod_s *mod = BFA_SGPG_MOD(bfa);
	काष्ठा bfa_sgpg_wqe_s *wqe;

	mod->मुक्त_sgpgs += nsgpg;
	WARN_ON(mod->मुक्त_sgpgs > mod->num_sgpgs);

	list_splice_tail_init(sgpg_q, &mod->sgpg_q);

	अगर (list_empty(&mod->sgpg_रुको_q))
		वापस;

	/*
	 * satisfy as many रुकोing requests as possible
	 */
	करो अणु
		wqe = bfa_q_first(&mod->sgpg_रुको_q);
		अगर (mod->मुक्त_sgpgs < wqe->nsgpg)
			nsgpg = mod->मुक्त_sgpgs;
		अन्यथा
			nsgpg = wqe->nsgpg;
		bfa_sgpg_दो_स्मृति(bfa, &wqe->sgpg_q, nsgpg);
		wqe->nsgpg -= nsgpg;
		अगर (wqe->nsgpg == 0) अणु
			list_del(&wqe->qe);
			wqe->cbfn(wqe->cbarg);
		पूर्ण
	पूर्ण जबतक (mod->मुक्त_sgpgs && !list_empty(&mod->sgpg_रुको_q));
पूर्ण

व्योम
bfa_sgpg_रुको(काष्ठा bfa_s *bfa, काष्ठा bfa_sgpg_wqe_s *wqe, पूर्णांक nsgpg)
अणु
	काष्ठा bfa_sgpg_mod_s *mod = BFA_SGPG_MOD(bfa);

	WARN_ON(nsgpg <= 0);
	WARN_ON(nsgpg <= mod->मुक्त_sgpgs);

	wqe->nsgpg_total = wqe->nsgpg = nsgpg;

	/*
	 * allocate any left to this one first
	 */
	अगर (mod->मुक्त_sgpgs) अणु
		/*
		 * no one अन्यथा is रुकोing क्रम SGPG
		 */
		WARN_ON(!list_empty(&mod->sgpg_रुको_q));
		list_splice_tail_init(&mod->sgpg_q, &wqe->sgpg_q);
		wqe->nsgpg -= mod->मुक्त_sgpgs;
		mod->मुक्त_sgpgs = 0;
	पूर्ण

	list_add_tail(&wqe->qe, &mod->sgpg_रुको_q);
पूर्ण

व्योम
bfa_sgpg_wcancel(काष्ठा bfa_s *bfa, काष्ठा bfa_sgpg_wqe_s *wqe)
अणु
	काष्ठा bfa_sgpg_mod_s *mod = BFA_SGPG_MOD(bfa);

	WARN_ON(!bfa_q_is_on_q(&mod->sgpg_रुको_q, wqe));
	list_del(&wqe->qe);

	अगर (wqe->nsgpg_total != wqe->nsgpg)
		bfa_sgpg_mमुक्त(bfa, &wqe->sgpg_q,
				   wqe->nsgpg_total - wqe->nsgpg);
पूर्ण

व्योम
bfa_sgpg_winit(काष्ठा bfa_sgpg_wqe_s *wqe, व्योम (*cbfn) (व्योम *cbarg),
		   व्योम *cbarg)
अणु
	INIT_LIST_HEAD(&wqe->sgpg_q);
	wqe->cbfn = cbfn;
	wqe->cbarg = cbarg;
पूर्ण

/*
 *  UF related functions
 */
/*
 *****************************************************************************
 * Internal functions
 *****************************************************************************
 */
अटल व्योम
__bfa_cb_uf_recv(व्योम *cbarg, bfa_boolean_t complete)
अणु
	काष्ठा bfa_uf_s   *uf = cbarg;
	काष्ठा bfa_uf_mod_s *ufm = BFA_UF_MOD(uf->bfa);

	अगर (complete)
		ufm->ufrecv(ufm->cbarg, uf);
पूर्ण

अटल व्योम
claim_uf_post_msgs(काष्ठा bfa_uf_mod_s *ufm)
अणु
	काष्ठा bfi_uf_buf_post_s *uf_bp_msg;
	u16 i;
	u16 buf_len;

	ufm->uf_buf_posts = (काष्ठा bfi_uf_buf_post_s *) bfa_mem_kva_curp(ufm);
	uf_bp_msg = ufm->uf_buf_posts;

	क्रम (i = 0, uf_bp_msg = ufm->uf_buf_posts; i < ufm->num_ufs;
	     i++, uf_bp_msg++) अणु
		स_रखो(uf_bp_msg, 0, माप(काष्ठा bfi_uf_buf_post_s));

		uf_bp_msg->buf_tag = i;
		buf_len = माप(काष्ठा bfa_uf_buf_s);
		uf_bp_msg->buf_len = cpu_to_be16(buf_len);
		bfi_h2i_set(uf_bp_msg->mh, BFI_MC_UF, BFI_UF_H2I_BUF_POST,
			    bfa_fn_lpu(ufm->bfa));
		bfa_alen_set(&uf_bp_msg->alen, buf_len, ufm_pbs_pa(ufm, i));
	पूर्ण

	/*
	 * advance poपूर्णांकer beyond consumed memory
	 */
	bfa_mem_kva_curp(ufm) = (u8 *) uf_bp_msg;
पूर्ण

अटल व्योम
claim_ufs(काष्ठा bfa_uf_mod_s *ufm)
अणु
	u16 i;
	काष्ठा bfa_uf_s   *uf;

	/*
	 * Claim block of memory क्रम UF list
	 */
	ufm->uf_list = (काष्ठा bfa_uf_s *) bfa_mem_kva_curp(ufm);

	/*
	 * Initialize UFs and queue it in UF मुक्त queue
	 */
	क्रम (i = 0, uf = ufm->uf_list; i < ufm->num_ufs; i++, uf++) अणु
		स_रखो(uf, 0, माप(काष्ठा bfa_uf_s));
		uf->bfa = ufm->bfa;
		uf->uf_tag = i;
		uf->pb_len = BFA_PER_UF_DMA_SZ;
		uf->buf_kva = bfa_mem_get_dmabuf_kva(ufm, i, BFA_PER_UF_DMA_SZ);
		uf->buf_pa = ufm_pbs_pa(ufm, i);
		list_add_tail(&uf->qe, &ufm->uf_मुक्त_q);
	पूर्ण

	/*
	 * advance memory poपूर्णांकer
	 */
	bfa_mem_kva_curp(ufm) = (u8 *) uf;
पूर्ण

अटल व्योम
uf_mem_claim(काष्ठा bfa_uf_mod_s *ufm)
अणु
	claim_ufs(ufm);
	claim_uf_post_msgs(ufm);
पूर्ण

व्योम
bfa_uf_meminfo(काष्ठा bfa_iocfc_cfg_s *cfg, काष्ठा bfa_meminfo_s *minfo,
		काष्ठा bfa_s *bfa)
अणु
	काष्ठा bfa_uf_mod_s *ufm = BFA_UF_MOD(bfa);
	काष्ठा bfa_mem_kva_s *uf_kva = BFA_MEM_UF_KVA(bfa);
	u32	num_ufs = cfg->fwcfg.num_uf_bufs;
	काष्ठा bfa_mem_dma_s *seg_ptr;
	u16	nsegs, idx, per_seg_uf = 0;

	nsegs = BFI_MEM_DMA_NSEGS(num_ufs, BFA_PER_UF_DMA_SZ);
	per_seg_uf = BFI_MEM_NREQS_SEG(BFA_PER_UF_DMA_SZ);

	bfa_mem_dma_seg_iter(ufm, seg_ptr, nsegs, idx) अणु
		अगर (num_ufs >= per_seg_uf) अणु
			num_ufs -= per_seg_uf;
			bfa_mem_dma_setup(minfo, seg_ptr,
				per_seg_uf * BFA_PER_UF_DMA_SZ);
		पूर्ण अन्यथा
			bfa_mem_dma_setup(minfo, seg_ptr,
				num_ufs * BFA_PER_UF_DMA_SZ);
	पूर्ण

	/* kva memory */
	bfa_mem_kva_setup(minfo, uf_kva, cfg->fwcfg.num_uf_bufs *
		(माप(काष्ठा bfa_uf_s) + माप(काष्ठा bfi_uf_buf_post_s)));
पूर्ण

व्योम
bfa_uf_attach(काष्ठा bfa_s *bfa, व्योम *bfad, काष्ठा bfa_iocfc_cfg_s *cfg,
		काष्ठा bfa_pcidev_s *pcidev)
अणु
	काष्ठा bfa_uf_mod_s *ufm = BFA_UF_MOD(bfa);

	ufm->bfa = bfa;
	ufm->num_ufs = cfg->fwcfg.num_uf_bufs;
	INIT_LIST_HEAD(&ufm->uf_मुक्त_q);
	INIT_LIST_HEAD(&ufm->uf_posted_q);
	INIT_LIST_HEAD(&ufm->uf_unused_q);

	uf_mem_claim(ufm);
पूर्ण

अटल काष्ठा bfa_uf_s *
bfa_uf_get(काष्ठा bfa_uf_mod_s *uf_mod)
अणु
	काष्ठा bfa_uf_s   *uf;

	bfa_q_deq(&uf_mod->uf_मुक्त_q, &uf);
	वापस uf;
पूर्ण

अटल व्योम
bfa_uf_put(काष्ठा bfa_uf_mod_s *uf_mod, काष्ठा bfa_uf_s *uf)
अणु
	list_add_tail(&uf->qe, &uf_mod->uf_मुक्त_q);
पूर्ण

अटल bfa_status_t
bfa_uf_post(काष्ठा bfa_uf_mod_s *ufm, काष्ठा bfa_uf_s *uf)
अणु
	काष्ठा bfi_uf_buf_post_s *uf_post_msg;

	uf_post_msg = bfa_reqq_next(ufm->bfa, BFA_REQQ_FCXP);
	अगर (!uf_post_msg)
		वापस BFA_STATUS_FAILED;

	स_नकल(uf_post_msg, &ufm->uf_buf_posts[uf->uf_tag],
		      माप(काष्ठा bfi_uf_buf_post_s));
	bfa_reqq_produce(ufm->bfa, BFA_REQQ_FCXP, uf_post_msg->mh);

	bfa_trc(ufm->bfa, uf->uf_tag);

	list_add_tail(&uf->qe, &ufm->uf_posted_q);
	वापस BFA_STATUS_OK;
पूर्ण

अटल व्योम
bfa_uf_post_all(काष्ठा bfa_uf_mod_s *uf_mod)
अणु
	काष्ठा bfa_uf_s   *uf;

	जबतक ((uf = bfa_uf_get(uf_mod)) != शून्य) अणु
		अगर (bfa_uf_post(uf_mod, uf) != BFA_STATUS_OK)
			अवरोध;
	पूर्ण
पूर्ण

अटल व्योम
uf_recv(काष्ठा bfa_s *bfa, काष्ठा bfi_uf_frm_rcvd_s *m)
अणु
	काष्ठा bfa_uf_mod_s *ufm = BFA_UF_MOD(bfa);
	u16 uf_tag = m->buf_tag;
	काष्ठा bfa_uf_s *uf = &ufm->uf_list[uf_tag];
	काष्ठा bfa_uf_buf_s *uf_buf;
	uपूर्णांक8_t *buf;

	uf_buf = (काष्ठा bfa_uf_buf_s *)
			bfa_mem_get_dmabuf_kva(ufm, uf_tag, uf->pb_len);
	buf = &uf_buf->d[0];

	m->frm_len = be16_to_cpu(m->frm_len);
	m->xfr_len = be16_to_cpu(m->xfr_len);

	list_del(&uf->qe);	/* dequeue from posted queue */

	uf->data_ptr = buf;
	uf->data_len = m->xfr_len;

	WARN_ON(uf->data_len < माप(काष्ठा fchs_s));

	अगर (uf->data_len == माप(काष्ठा fchs_s)) अणु
		bfa_plog_fchdr(bfa->plog, BFA_PL_MID_HAL_UF, BFA_PL_EID_RX,
			       uf->data_len, (काष्ठा fchs_s *)buf);
	पूर्ण अन्यथा अणु
		u32 pld_w0 = *((u32 *) (buf + माप(काष्ठा fchs_s)));
		bfa_plog_fchdr_and_pl(bfa->plog, BFA_PL_MID_HAL_UF,
				      BFA_PL_EID_RX, uf->data_len,
				      (काष्ठा fchs_s *)buf, pld_w0);
	पूर्ण

	अगर (bfa->fcs)
		__bfa_cb_uf_recv(uf, BFA_TRUE);
	अन्यथा
		bfa_cb_queue(bfa, &uf->hcb_qe, __bfa_cb_uf_recv, uf);
पूर्ण

व्योम
bfa_uf_iocdisable(काष्ठा bfa_s *bfa)
अणु
	काष्ठा bfa_uf_mod_s *ufm = BFA_UF_MOD(bfa);
	काष्ठा bfa_uf_s *uf;
	काष्ठा list_head *qe, *qen;

	/* Enqueue unused uf resources to मुक्त_q */
	list_splice_tail_init(&ufm->uf_unused_q, &ufm->uf_मुक्त_q);

	list_क्रम_each_safe(qe, qen, &ufm->uf_posted_q) अणु
		uf = (काष्ठा bfa_uf_s *) qe;
		list_del(&uf->qe);
		bfa_uf_put(ufm, uf);
	पूर्ण
पूर्ण

व्योम
bfa_uf_start(काष्ठा bfa_s *bfa)
अणु
	bfa_uf_post_all(BFA_UF_MOD(bfa));
पूर्ण

/*
 * Register handler क्रम all unsolicted receive frames.
 *
 * @param[in]	bfa		BFA instance
 * @param[in]	ufrecv	receive handler function
 * @param[in]	cbarg	receive handler arg
 */
व्योम
bfa_uf_recv_रेजिस्टर(काष्ठा bfa_s *bfa, bfa_cb_uf_recv_t ufrecv, व्योम *cbarg)
अणु
	काष्ठा bfa_uf_mod_s *ufm = BFA_UF_MOD(bfa);

	ufm->ufrecv = ufrecv;
	ufm->cbarg = cbarg;
पूर्ण

/*
 *	Free an unsolicited frame back to BFA.
 *
 * @param[in]		uf		unsolicited frame to be मुक्तd
 *
 * @वापस None
 */
व्योम
bfa_uf_मुक्त(काष्ठा bfa_uf_s *uf)
अणु
	bfa_uf_put(BFA_UF_MOD(uf->bfa), uf);
	bfa_uf_post_all(BFA_UF_MOD(uf->bfa));
पूर्ण



/*
 *  uf_pub BFA uf module खुला functions
 */
व्योम
bfa_uf_isr(काष्ठा bfa_s *bfa, काष्ठा bfi_msg_s *msg)
अणु
	bfa_trc(bfa, msg->mhdr.msg_id);

	चयन (msg->mhdr.msg_id) अणु
	हाल BFI_UF_I2H_FRM_RCVD:
		uf_recv(bfa, (काष्ठा bfi_uf_frm_rcvd_s *) msg);
		अवरोध;

	शेष:
		bfa_trc(bfa, msg->mhdr.msg_id);
		WARN_ON(1);
	पूर्ण
पूर्ण

व्योम
bfa_uf_res_recfg(काष्ठा bfa_s *bfa, u16 num_uf_fw)
अणु
	काष्ठा bfa_uf_mod_s	*mod = BFA_UF_MOD(bfa);
	काष्ठा list_head	*qe;
	पूर्णांक	i;

	क्रम (i = 0; i < (mod->num_ufs - num_uf_fw); i++) अणु
		bfa_q_deq_tail(&mod->uf_मुक्त_q, &qe);
		list_add_tail(qe, &mod->uf_unused_q);
	पूर्ण
पूर्ण

/*
 *	Dport क्रमward declaration
 */

क्रमागत bfa_dport_test_state_e अणु
	BFA_DPORT_ST_DISABLED	= 0,	/*!< dport is disabled */
	BFA_DPORT_ST_INP	= 1,	/*!< test in progress */
	BFA_DPORT_ST_COMP	= 2,	/*!< test complete successfully */
	BFA_DPORT_ST_NO_SFP	= 3,	/*!< sfp is not present */
	BFA_DPORT_ST_NOTSTART	= 4,	/*!< test not start dport is enabled */
पूर्ण;

/*
 * BFA DPORT state machine events
 */
क्रमागत bfa_dport_sm_event अणु
	BFA_DPORT_SM_ENABLE	= 1,	/* dport enable event         */
	BFA_DPORT_SM_DISABLE    = 2,    /* dport disable event        */
	BFA_DPORT_SM_FWRSP      = 3,    /* fw enable/disable rsp      */
	BFA_DPORT_SM_QRESUME    = 4,    /* CQ space available         */
	BFA_DPORT_SM_HWFAIL     = 5,    /* IOC h/w failure            */
	BFA_DPORT_SM_START	= 6,	/* re-start dport test        */
	BFA_DPORT_SM_REQFAIL	= 7,	/* request failure            */
	BFA_DPORT_SM_SCN	= 8,	/* state change notअगरy frm fw */
पूर्ण;

अटल व्योम bfa_dport_sm_disabled(काष्ठा bfa_dport_s *dport,
				  क्रमागत bfa_dport_sm_event event);
अटल व्योम bfa_dport_sm_enabling_qरुको(काष्ठा bfa_dport_s *dport,
				  क्रमागत bfa_dport_sm_event event);
अटल व्योम bfa_dport_sm_enabling(काष्ठा bfa_dport_s *dport,
				  क्रमागत bfa_dport_sm_event event);
अटल व्योम bfa_dport_sm_enabled(काष्ठा bfa_dport_s *dport,
				 क्रमागत bfa_dport_sm_event event);
अटल व्योम bfa_dport_sm_disabling_qरुको(काष्ठा bfa_dport_s *dport,
				 क्रमागत bfa_dport_sm_event event);
अटल व्योम bfa_dport_sm_disabling(काष्ठा bfa_dport_s *dport,
				   क्रमागत bfa_dport_sm_event event);
अटल व्योम bfa_dport_sm_starting_qरुको(काष्ठा bfa_dport_s *dport,
					क्रमागत bfa_dport_sm_event event);
अटल व्योम bfa_dport_sm_starting(काष्ठा bfa_dport_s *dport,
				  क्रमागत bfa_dport_sm_event event);
अटल व्योम bfa_dport_sm_dynamic_disabling(काष्ठा bfa_dport_s *dport,
				   क्रमागत bfa_dport_sm_event event);
अटल व्योम bfa_dport_sm_dynamic_disabling_qरुको(काष्ठा bfa_dport_s *dport,
				   क्रमागत bfa_dport_sm_event event);
अटल व्योम bfa_dport_qresume(व्योम *cbarg);
अटल व्योम bfa_dport_req_comp(काष्ठा bfa_dport_s *dport,
				काष्ठा bfi_diag_dport_rsp_s *msg);
अटल व्योम bfa_dport_scn(काष्ठा bfa_dport_s *dport,
				काष्ठा bfi_diag_dport_scn_s *msg);

/*
 *	BFA fcdiag module
 */
#घोषणा BFA_DIAG_QTEST_TOV	1000    /* msec */

/*
 *	Set port status to busy
 */
अटल व्योम
bfa_fcdiag_set_busy_status(काष्ठा bfa_fcdiag_s *fcdiag)
अणु
	काष्ठा bfa_fcport_s *fcport = BFA_FCPORT_MOD(fcdiag->bfa);

	अगर (fcdiag->lb.lock)
		fcport->diag_busy = BFA_TRUE;
	अन्यथा
		fcport->diag_busy = BFA_FALSE;
पूर्ण

व्योम
bfa_fcdiag_attach(काष्ठा bfa_s *bfa, व्योम *bfad, काष्ठा bfa_iocfc_cfg_s *cfg,
		काष्ठा bfa_pcidev_s *pcidev)
अणु
	काष्ठा bfa_fcdiag_s *fcdiag = BFA_FCDIAG_MOD(bfa);
	काष्ठा bfa_dport_s  *dport = &fcdiag->dport;

	fcdiag->bfa             = bfa;
	fcdiag->trcmod  = bfa->trcmod;
	/* The common DIAG attach bfa_diag_attach() will करो all memory claim */
	dport->bfa = bfa;
	bfa_sm_set_state(dport, bfa_dport_sm_disabled);
	bfa_reqq_winit(&dport->reqq_रुको, bfa_dport_qresume, dport);
	dport->cbfn = शून्य;
	dport->cbarg = शून्य;
	dport->test_state = BFA_DPORT_ST_DISABLED;
	स_रखो(&dport->result, 0, माप(काष्ठा bfa_diag_dport_result_s));
पूर्ण

व्योम
bfa_fcdiag_iocdisable(काष्ठा bfa_s *bfa)
अणु
	काष्ठा bfa_fcdiag_s *fcdiag = BFA_FCDIAG_MOD(bfa);
	काष्ठा bfa_dport_s *dport = &fcdiag->dport;

	bfa_trc(fcdiag, fcdiag->lb.lock);
	अगर (fcdiag->lb.lock) अणु
		fcdiag->lb.status = BFA_STATUS_IOC_FAILURE;
		fcdiag->lb.cbfn(fcdiag->lb.cbarg, fcdiag->lb.status);
		fcdiag->lb.lock = 0;
		bfa_fcdiag_set_busy_status(fcdiag);
	पूर्ण

	bfa_sm_send_event(dport, BFA_DPORT_SM_HWFAIL);
पूर्ण

अटल व्योम
bfa_fcdiag_queuetest_समयout(व्योम *cbarg)
अणु
	काष्ठा bfa_fcdiag_s       *fcdiag = cbarg;
	काष्ठा bfa_diag_qtest_result_s *res = fcdiag->qtest.result;

	bfa_trc(fcdiag, fcdiag->qtest.all);
	bfa_trc(fcdiag, fcdiag->qtest.count);

	fcdiag->qtest.समयr_active = 0;

	res->status = BFA_STATUS_ETIMER;
	res->count  = QTEST_CNT_DEFAULT - fcdiag->qtest.count;
	अगर (fcdiag->qtest.all)
		res->queue  = fcdiag->qtest.all;

	bfa_trc(fcdiag, BFA_STATUS_ETIMER);
	fcdiag->qtest.status = BFA_STATUS_ETIMER;
	fcdiag->qtest.cbfn(fcdiag->qtest.cbarg, fcdiag->qtest.status);
	fcdiag->qtest.lock = 0;
पूर्ण

अटल bfa_status_t
bfa_fcdiag_queuetest_send(काष्ठा bfa_fcdiag_s *fcdiag)
अणु
	u32	i;
	काष्ठा bfi_diag_qtest_req_s *req;

	req = bfa_reqq_next(fcdiag->bfa, fcdiag->qtest.queue);
	अगर (!req)
		वापस BFA_STATUS_DEVBUSY;

	/* build host command */
	bfi_h2i_set(req->mh, BFI_MC_DIAG, BFI_DIAG_H2I_QTEST,
		bfa_fn_lpu(fcdiag->bfa));

	क्रम (i = 0; i < BFI_LMSG_PL_WSZ; i++)
		req->data[i] = QTEST_PAT_DEFAULT;

	bfa_trc(fcdiag, fcdiag->qtest.queue);
	/* ring करोor bell */
	bfa_reqq_produce(fcdiag->bfa, fcdiag->qtest.queue, req->mh);
	वापस BFA_STATUS_OK;
पूर्ण

अटल व्योम
bfa_fcdiag_queuetest_comp(काष्ठा bfa_fcdiag_s *fcdiag,
			bfi_diag_qtest_rsp_t *rsp)
अणु
	काष्ठा bfa_diag_qtest_result_s *res = fcdiag->qtest.result;
	bfa_status_t status = BFA_STATUS_OK;
	पूर्णांक i;

	/* Check समयr, should still be active   */
	अगर (!fcdiag->qtest.समयr_active) अणु
		bfa_trc(fcdiag, fcdiag->qtest.समयr_active);
		वापस;
	पूर्ण

	/* update count */
	fcdiag->qtest.count--;

	/* Check result */
	क्रम (i = 0; i < BFI_LMSG_PL_WSZ; i++) अणु
		अगर (rsp->data[i] != ~(QTEST_PAT_DEFAULT)) अणु
			res->status = BFA_STATUS_DATACORRUPTED;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (res->status == BFA_STATUS_OK) अणु
		अगर (fcdiag->qtest.count > 0) अणु
			status = bfa_fcdiag_queuetest_send(fcdiag);
			अगर (status == BFA_STATUS_OK)
				वापस;
			अन्यथा
				res->status = status;
		पूर्ण अन्यथा अगर (fcdiag->qtest.all > 0 &&
			fcdiag->qtest.queue < (BFI_IOC_MAX_CQS - 1)) अणु
			fcdiag->qtest.count = QTEST_CNT_DEFAULT;
			fcdiag->qtest.queue++;
			status = bfa_fcdiag_queuetest_send(fcdiag);
			अगर (status == BFA_STATUS_OK)
				वापस;
			अन्यथा
				res->status = status;
		पूर्ण
	पूर्ण

	/* Stop समयr when we comp all queue */
	अगर (fcdiag->qtest.समयr_active) अणु
		bfa_समयr_stop(&fcdiag->qtest.समयr);
		fcdiag->qtest.समयr_active = 0;
	पूर्ण
	res->queue = fcdiag->qtest.queue;
	res->count = QTEST_CNT_DEFAULT - fcdiag->qtest.count;
	bfa_trc(fcdiag, res->count);
	bfa_trc(fcdiag, res->status);
	fcdiag->qtest.status = res->status;
	fcdiag->qtest.cbfn(fcdiag->qtest.cbarg, fcdiag->qtest.status);
	fcdiag->qtest.lock = 0;
पूर्ण

अटल व्योम
bfa_fcdiag_loopback_comp(काष्ठा bfa_fcdiag_s *fcdiag,
			काष्ठा bfi_diag_lb_rsp_s *rsp)
अणु
	काष्ठा bfa_diag_loopback_result_s *res = fcdiag->lb.result;

	res->numtxmfrm  = be32_to_cpu(rsp->res.numtxmfrm);
	res->numosffrm  = be32_to_cpu(rsp->res.numosffrm);
	res->numrcvfrm  = be32_to_cpu(rsp->res.numrcvfrm);
	res->badfrminf  = be32_to_cpu(rsp->res.badfrminf);
	res->badfrmnum  = be32_to_cpu(rsp->res.badfrmnum);
	res->status     = rsp->res.status;
	fcdiag->lb.status = rsp->res.status;
	bfa_trc(fcdiag, fcdiag->lb.status);
	fcdiag->lb.cbfn(fcdiag->lb.cbarg, fcdiag->lb.status);
	fcdiag->lb.lock = 0;
	bfa_fcdiag_set_busy_status(fcdiag);
पूर्ण

अटल bfa_status_t
bfa_fcdiag_loopback_send(काष्ठा bfa_fcdiag_s *fcdiag,
			काष्ठा bfa_diag_loopback_s *loopback)
अणु
	काष्ठा bfi_diag_lb_req_s *lb_req;

	lb_req = bfa_reqq_next(fcdiag->bfa, BFA_REQQ_DIAG);
	अगर (!lb_req)
		वापस BFA_STATUS_DEVBUSY;

	/* build host command */
	bfi_h2i_set(lb_req->mh, BFI_MC_DIAG, BFI_DIAG_H2I_LOOPBACK,
		bfa_fn_lpu(fcdiag->bfa));

	lb_req->lb_mode = loopback->lb_mode;
	lb_req->speed = loopback->speed;
	lb_req->loopcnt = loopback->loopcnt;
	lb_req->pattern = loopback->pattern;

	/* ring करोor bell */
	bfa_reqq_produce(fcdiag->bfa, BFA_REQQ_DIAG, lb_req->mh);

	bfa_trc(fcdiag, loopback->lb_mode);
	bfa_trc(fcdiag, loopback->speed);
	bfa_trc(fcdiag, loopback->loopcnt);
	bfa_trc(fcdiag, loopback->pattern);
	वापस BFA_STATUS_OK;
पूर्ण

/*
 *	cpe/rme पूर्णांकr handler
 */
व्योम
bfa_fcdiag_पूर्णांकr(काष्ठा bfa_s *bfa, काष्ठा bfi_msg_s *msg)
अणु
	काष्ठा bfa_fcdiag_s *fcdiag = BFA_FCDIAG_MOD(bfa);

	चयन (msg->mhdr.msg_id) अणु
	हाल BFI_DIAG_I2H_LOOPBACK:
		bfa_fcdiag_loopback_comp(fcdiag,
				(काष्ठा bfi_diag_lb_rsp_s *) msg);
		अवरोध;
	हाल BFI_DIAG_I2H_QTEST:
		bfa_fcdiag_queuetest_comp(fcdiag, (bfi_diag_qtest_rsp_t *)msg);
		अवरोध;
	हाल BFI_DIAG_I2H_DPORT:
		bfa_dport_req_comp(&fcdiag->dport,
				(काष्ठा bfi_diag_dport_rsp_s *)msg);
		अवरोध;
	हाल BFI_DIAG_I2H_DPORT_SCN:
		bfa_dport_scn(&fcdiag->dport,
				(काष्ठा bfi_diag_dport_scn_s *)msg);
		अवरोध;
	शेष:
		bfa_trc(fcdiag, msg->mhdr.msg_id);
		WARN_ON(1);
	पूर्ण
पूर्ण

/*
 *	Loopback test
 *
 *   @param[in] *bfa            - bfa data काष्ठा
 *   @param[in] opmode          - port operation mode
 *   @param[in] speed           - port speed
 *   @param[in] lpcnt           - loop count
 *   @param[in] pat                     - pattern to build packet
 *   @param[in] *result         - pt to bfa_diag_loopback_result_t data काष्ठा
 *   @param[in] cbfn            - callback function
 *   @param[in] cbarg           - callback functioin arg
 *
 *   @param[out]
 */
bfa_status_t
bfa_fcdiag_loopback(काष्ठा bfa_s *bfa, क्रमागत bfa_port_opmode opmode,
		क्रमागत bfa_port_speed speed, u32 lpcnt, u32 pat,
		काष्ठा bfa_diag_loopback_result_s *result, bfa_cb_diag_t cbfn,
		व्योम *cbarg)
अणु
	काष्ठा  bfa_diag_loopback_s loopback;
	काष्ठा bfa_port_attr_s attr;
	bfa_status_t status;
	काष्ठा bfa_fcdiag_s *fcdiag = BFA_FCDIAG_MOD(bfa);

	अगर (!bfa_iocfc_is_operational(bfa))
		वापस BFA_STATUS_IOC_NON_OP;

	/* अगर port is PBC disabled, वापस error */
	अगर (bfa_fcport_is_pbcdisabled(bfa)) अणु
		bfa_trc(fcdiag, BFA_STATUS_PBC);
		वापस BFA_STATUS_PBC;
	पूर्ण

	अगर (bfa_fcport_is_disabled(bfa) == BFA_FALSE) अणु
		bfa_trc(fcdiag, opmode);
		वापस BFA_STATUS_PORT_NOT_DISABLED;
	पूर्ण

	/*
	 * Check अगर input speed is supported by the port mode
	 */
	अगर (bfa_ioc_get_type(&bfa->ioc) == BFA_IOC_TYPE_FC) अणु
		अगर (!(speed == BFA_PORT_SPEED_1GBPS ||
		      speed == BFA_PORT_SPEED_2GBPS ||
		      speed == BFA_PORT_SPEED_4GBPS ||
		      speed == BFA_PORT_SPEED_8GBPS ||
		      speed == BFA_PORT_SPEED_16GBPS ||
		      speed == BFA_PORT_SPEED_AUTO)) अणु
			bfa_trc(fcdiag, speed);
			वापस BFA_STATUS_UNSUPP_SPEED;
		पूर्ण
		bfa_fcport_get_attr(bfa, &attr);
		bfa_trc(fcdiag, attr.speed_supported);
		अगर (speed > attr.speed_supported)
			वापस BFA_STATUS_UNSUPP_SPEED;
	पूर्ण अन्यथा अणु
		अगर (speed != BFA_PORT_SPEED_10GBPS) अणु
			bfa_trc(fcdiag, speed);
			वापस BFA_STATUS_UNSUPP_SPEED;
		पूर्ण
	पूर्ण

	/*
	 * For CT2, 1G is not supported
	 */
	अगर ((speed == BFA_PORT_SPEED_1GBPS) &&
	    (bfa_asic_id_ct2(bfa->ioc.pcidev.device_id))) अणु
		bfa_trc(fcdiag, speed);
		वापस BFA_STATUS_UNSUPP_SPEED;
	पूर्ण

	/* For Mezz card, port speed entered needs to be checked */
	अगर (bfa_mfg_is_mezz(bfa->ioc.attr->card_type)) अणु
		अगर (bfa_ioc_get_type(&bfa->ioc) == BFA_IOC_TYPE_FC) अणु
			अगर (!(speed == BFA_PORT_SPEED_1GBPS ||
			      speed == BFA_PORT_SPEED_2GBPS ||
			      speed == BFA_PORT_SPEED_4GBPS ||
			      speed == BFA_PORT_SPEED_8GBPS ||
			      speed == BFA_PORT_SPEED_16GBPS ||
			      speed == BFA_PORT_SPEED_AUTO))
				वापस BFA_STATUS_UNSUPP_SPEED;
		पूर्ण अन्यथा अणु
			अगर (speed != BFA_PORT_SPEED_10GBPS)
				वापस BFA_STATUS_UNSUPP_SPEED;
		पूर्ण
	पूर्ण
	/* check to see अगर fcport is dport */
	अगर (bfa_fcport_is_dport(bfa)) अणु
		bfa_trc(fcdiag, fcdiag->lb.lock);
		वापस BFA_STATUS_DPORT_ENABLED;
	पूर्ण
	/* check to see अगर there is another deकाष्ठाive diag cmd running */
	अगर (fcdiag->lb.lock) अणु
		bfa_trc(fcdiag, fcdiag->lb.lock);
		वापस BFA_STATUS_DEVBUSY;
	पूर्ण

	fcdiag->lb.lock = 1;
	loopback.lb_mode = opmode;
	loopback.speed = speed;
	loopback.loopcnt = lpcnt;
	loopback.pattern = pat;
	fcdiag->lb.result = result;
	fcdiag->lb.cbfn = cbfn;
	fcdiag->lb.cbarg = cbarg;
	स_रखो(result, 0, माप(काष्ठा bfa_diag_loopback_result_s));
	bfa_fcdiag_set_busy_status(fcdiag);

	/* Send msg to fw */
	status = bfa_fcdiag_loopback_send(fcdiag, &loopback);
	वापस status;
पूर्ण

/*
 *	DIAG queue test command
 *
 *   @param[in] *bfa            - bfa data काष्ठा
 *   @param[in] क्रमce           - 1: करोn't करो ioc op checking
 *   @param[in] queue           - queue no. to test
 *   @param[in] *result         - pt to bfa_diag_qtest_result_t data काष्ठा
 *   @param[in] cbfn            - callback function
 *   @param[in] *cbarg          - callback functioin arg
 *
 *   @param[out]
 */
bfa_status_t
bfa_fcdiag_queuetest(काष्ठा bfa_s *bfa, u32 क्रमce, u32 queue,
		काष्ठा bfa_diag_qtest_result_s *result, bfa_cb_diag_t cbfn,
		व्योम *cbarg)
अणु
	काष्ठा bfa_fcdiag_s *fcdiag = BFA_FCDIAG_MOD(bfa);
	bfa_status_t status;
	bfa_trc(fcdiag, क्रमce);
	bfa_trc(fcdiag, queue);

	अगर (!क्रमce && !bfa_iocfc_is_operational(bfa))
		वापस BFA_STATUS_IOC_NON_OP;

	/* check to see अगर there is another deकाष्ठाive diag cmd running */
	अगर (fcdiag->qtest.lock) अणु
		bfa_trc(fcdiag, fcdiag->qtest.lock);
		वापस BFA_STATUS_DEVBUSY;
	पूर्ण

	/* Initialization */
	fcdiag->qtest.lock = 1;
	fcdiag->qtest.cbfn = cbfn;
	fcdiag->qtest.cbarg = cbarg;
	fcdiag->qtest.result = result;
	fcdiag->qtest.count = QTEST_CNT_DEFAULT;

	/* Init test results */
	fcdiag->qtest.result->status = BFA_STATUS_OK;
	fcdiag->qtest.result->count  = 0;

	/* send */
	अगर (queue < BFI_IOC_MAX_CQS) अणु
		fcdiag->qtest.result->queue  = (u8)queue;
		fcdiag->qtest.queue = (u8)queue;
		fcdiag->qtest.all   = 0;
	पूर्ण अन्यथा अणु
		fcdiag->qtest.result->queue  = 0;
		fcdiag->qtest.queue = 0;
		fcdiag->qtest.all   = 1;
	पूर्ण
	status = bfa_fcdiag_queuetest_send(fcdiag);

	/* Start a समयr */
	अगर (status == BFA_STATUS_OK) अणु
		bfa_समयr_start(bfa, &fcdiag->qtest.समयr,
				bfa_fcdiag_queuetest_समयout, fcdiag,
				BFA_DIAG_QTEST_TOV);
		fcdiag->qtest.समयr_active = 1;
	पूर्ण
	वापस status;
पूर्ण

/*
 * DIAG PLB is running
 *
 *   @param[in] *bfa    - bfa data काष्ठा
 *
 *   @param[out]
 */
bfa_status_t
bfa_fcdiag_lb_is_running(काष्ठा bfa_s *bfa)
अणु
	काष्ठा bfa_fcdiag_s *fcdiag = BFA_FCDIAG_MOD(bfa);
	वापस fcdiag->lb.lock ?  BFA_STATUS_DIAG_BUSY : BFA_STATUS_OK;
पूर्ण

/*
 *	D-port
 */
#घोषणा bfa_dport_result_start(__dport, __mode) करो अणु				\
		(__dport)->result.start_समय = kसमय_get_real_seconds();	\
		(__dport)->result.status = DPORT_TEST_ST_INPRG;			\
		(__dport)->result.mode = (__mode);				\
		(__dport)->result.rp_pwwn = (__dport)->rp_pwwn;			\
		(__dport)->result.rp_nwwn = (__dport)->rp_nwwn;			\
		(__dport)->result.lpcnt = (__dport)->lpcnt;			\
पूर्ण जबतक (0)

अटल bfa_boolean_t bfa_dport_send_req(काष्ठा bfa_dport_s *dport,
					क्रमागत bfi_dport_req req);
अटल व्योम
bfa_cb_fcdiag_dport(काष्ठा bfa_dport_s *dport, bfa_status_t bfa_status)
अणु
	अगर (dport->cbfn != शून्य) अणु
		dport->cbfn(dport->cbarg, bfa_status);
		dport->cbfn = शून्य;
		dport->cbarg = शून्य;
	पूर्ण
पूर्ण

अटल व्योम
bfa_dport_sm_disabled(काष्ठा bfa_dport_s *dport, क्रमागत bfa_dport_sm_event event)
अणु
	bfa_trc(dport->bfa, event);

	चयन (event) अणु
	हाल BFA_DPORT_SM_ENABLE:
		bfa_fcport_dportenable(dport->bfa);
		अगर (bfa_dport_send_req(dport, BFI_DPORT_ENABLE))
			bfa_sm_set_state(dport, bfa_dport_sm_enabling);
		अन्यथा
			bfa_sm_set_state(dport, bfa_dport_sm_enabling_qरुको);
		अवरोध;

	हाल BFA_DPORT_SM_DISABLE:
		/* Alपढ़ोy disabled */
		अवरोध;

	हाल BFA_DPORT_SM_HWFAIL:
		/* ignore */
		अवरोध;

	हाल BFA_DPORT_SM_SCN:
		अगर (dport->i2hmsg.scn.state ==  BFI_DPORT_SCN_DDPORT_ENABLE) अणु
			bfa_fcport_ddportenable(dport->bfa);
			dport->dynamic = BFA_TRUE;
			dport->test_state = BFA_DPORT_ST_NOTSTART;
			bfa_sm_set_state(dport, bfa_dport_sm_enabled);
		पूर्ण अन्यथा अणु
			bfa_trc(dport->bfa, dport->i2hmsg.scn.state);
			WARN_ON(1);
		पूर्ण
		अवरोध;

	शेष:
		bfa_sm_fault(dport->bfa, event);
	पूर्ण
पूर्ण

अटल व्योम
bfa_dport_sm_enabling_qरुको(काष्ठा bfa_dport_s *dport,
			    क्रमागत bfa_dport_sm_event event)
अणु
	bfa_trc(dport->bfa, event);

	चयन (event) अणु
	हाल BFA_DPORT_SM_QRESUME:
		bfa_sm_set_state(dport, bfa_dport_sm_enabling);
		bfa_dport_send_req(dport, BFI_DPORT_ENABLE);
		अवरोध;

	हाल BFA_DPORT_SM_HWFAIL:
		bfa_reqq_wcancel(&dport->reqq_रुको);
		bfa_sm_set_state(dport, bfa_dport_sm_disabled);
		bfa_cb_fcdiag_dport(dport, BFA_STATUS_FAILED);
		अवरोध;

	शेष:
		bfa_sm_fault(dport->bfa, event);
	पूर्ण
पूर्ण

अटल व्योम
bfa_dport_sm_enabling(काष्ठा bfa_dport_s *dport, क्रमागत bfa_dport_sm_event event)
अणु
	bfa_trc(dport->bfa, event);

	चयन (event) अणु
	हाल BFA_DPORT_SM_FWRSP:
		स_रखो(&dport->result, 0,
				माप(काष्ठा bfa_diag_dport_result_s));
		अगर (dport->i2hmsg.rsp.status == BFA_STATUS_DPORT_INV_SFP) अणु
			dport->test_state = BFA_DPORT_ST_NO_SFP;
		पूर्ण अन्यथा अणु
			dport->test_state = BFA_DPORT_ST_INP;
			bfa_dport_result_start(dport, BFA_DPORT_OPMODE_AUTO);
		पूर्ण
		bfa_sm_set_state(dport, bfa_dport_sm_enabled);
		अवरोध;

	हाल BFA_DPORT_SM_REQFAIL:
		dport->test_state = BFA_DPORT_ST_DISABLED;
		bfa_fcport_dportdisable(dport->bfa);
		bfa_sm_set_state(dport, bfa_dport_sm_disabled);
		अवरोध;

	हाल BFA_DPORT_SM_HWFAIL:
		bfa_sm_set_state(dport, bfa_dport_sm_disabled);
		bfa_cb_fcdiag_dport(dport, BFA_STATUS_FAILED);
		अवरोध;

	शेष:
		bfa_sm_fault(dport->bfa, event);
	पूर्ण
पूर्ण

अटल व्योम
bfa_dport_sm_enabled(काष्ठा bfa_dport_s *dport, क्रमागत bfa_dport_sm_event event)
अणु
	bfa_trc(dport->bfa, event);

	चयन (event) अणु
	हाल BFA_DPORT_SM_START:
		अगर (bfa_dport_send_req(dport, BFI_DPORT_START))
			bfa_sm_set_state(dport, bfa_dport_sm_starting);
		अन्यथा
			bfa_sm_set_state(dport, bfa_dport_sm_starting_qरुको);
		अवरोध;

	हाल BFA_DPORT_SM_DISABLE:
		bfa_fcport_dportdisable(dport->bfa);
		अगर (bfa_dport_send_req(dport, BFI_DPORT_DISABLE))
			bfa_sm_set_state(dport, bfa_dport_sm_disabling);
		अन्यथा
			bfa_sm_set_state(dport, bfa_dport_sm_disabling_qरुको);
		अवरोध;

	हाल BFA_DPORT_SM_HWFAIL:
		bfa_sm_set_state(dport, bfa_dport_sm_disabled);
		अवरोध;

	हाल BFA_DPORT_SM_SCN:
		चयन (dport->i2hmsg.scn.state) अणु
		हाल BFI_DPORT_SCN_TESTCOMP:
			dport->test_state = BFA_DPORT_ST_COMP;
			अवरोध;

		हाल BFI_DPORT_SCN_TESTSTART:
			dport->test_state = BFA_DPORT_ST_INP;
			अवरोध;

		हाल BFI_DPORT_SCN_TESTSKIP:
		हाल BFI_DPORT_SCN_SUBTESTSTART:
			/* no state change */
			अवरोध;

		हाल BFI_DPORT_SCN_SFP_REMOVED:
			dport->test_state = BFA_DPORT_ST_NO_SFP;
			अवरोध;

		हाल BFI_DPORT_SCN_DDPORT_DISABLE:
			bfa_fcport_ddportdisable(dport->bfa);

			अगर (bfa_dport_send_req(dport, BFI_DPORT_DYN_DISABLE))
				bfa_sm_set_state(dport,
					 bfa_dport_sm_dynamic_disabling);
			अन्यथा
				bfa_sm_set_state(dport,
					 bfa_dport_sm_dynamic_disabling_qरुको);
			अवरोध;

		हाल BFI_DPORT_SCN_FCPORT_DISABLE:
			bfa_fcport_ddportdisable(dport->bfa);

			bfa_sm_set_state(dport, bfa_dport_sm_disabled);
			dport->dynamic = BFA_FALSE;
			अवरोध;

		शेष:
			bfa_trc(dport->bfa, dport->i2hmsg.scn.state);
			bfa_sm_fault(dport->bfa, event);
		पूर्ण
		अवरोध;
	शेष:
		bfa_sm_fault(dport->bfa, event);
	पूर्ण
पूर्ण

अटल व्योम
bfa_dport_sm_disabling_qरुको(काष्ठा bfa_dport_s *dport,
			     क्रमागत bfa_dport_sm_event event)
अणु
	bfa_trc(dport->bfa, event);

	चयन (event) अणु
	हाल BFA_DPORT_SM_QRESUME:
		bfa_sm_set_state(dport, bfa_dport_sm_disabling);
		bfa_dport_send_req(dport, BFI_DPORT_DISABLE);
		अवरोध;

	हाल BFA_DPORT_SM_HWFAIL:
		bfa_sm_set_state(dport, bfa_dport_sm_disabled);
		bfa_reqq_wcancel(&dport->reqq_रुको);
		bfa_cb_fcdiag_dport(dport, BFA_STATUS_OK);
		अवरोध;

	हाल BFA_DPORT_SM_SCN:
		/* ignore */
		अवरोध;

	शेष:
		bfa_sm_fault(dport->bfa, event);
	पूर्ण
पूर्ण

अटल व्योम
bfa_dport_sm_disabling(काष्ठा bfa_dport_s *dport, क्रमागत bfa_dport_sm_event event)
अणु
	bfa_trc(dport->bfa, event);

	चयन (event) अणु
	हाल BFA_DPORT_SM_FWRSP:
		dport->test_state = BFA_DPORT_ST_DISABLED;
		bfa_sm_set_state(dport, bfa_dport_sm_disabled);
		अवरोध;

	हाल BFA_DPORT_SM_HWFAIL:
		bfa_sm_set_state(dport, bfa_dport_sm_disabled);
		bfa_cb_fcdiag_dport(dport, BFA_STATUS_OK);
		अवरोध;

	हाल BFA_DPORT_SM_SCN:
		/* no state change */
		अवरोध;

	शेष:
		bfa_sm_fault(dport->bfa, event);
	पूर्ण
पूर्ण

अटल व्योम
bfa_dport_sm_starting_qरुको(काष्ठा bfa_dport_s *dport,
			    क्रमागत bfa_dport_sm_event event)
अणु
	bfa_trc(dport->bfa, event);

	चयन (event) अणु
	हाल BFA_DPORT_SM_QRESUME:
		bfa_sm_set_state(dport, bfa_dport_sm_starting);
		bfa_dport_send_req(dport, BFI_DPORT_START);
		अवरोध;

	हाल BFA_DPORT_SM_HWFAIL:
		bfa_reqq_wcancel(&dport->reqq_रुको);
		bfa_sm_set_state(dport, bfa_dport_sm_disabled);
		bfa_cb_fcdiag_dport(dport, BFA_STATUS_FAILED);
		अवरोध;

	शेष:
		bfa_sm_fault(dport->bfa, event);
	पूर्ण
पूर्ण

अटल व्योम
bfa_dport_sm_starting(काष्ठा bfa_dport_s *dport, क्रमागत bfa_dport_sm_event event)
अणु
	bfa_trc(dport->bfa, event);

	चयन (event) अणु
	हाल BFA_DPORT_SM_FWRSP:
		स_रखो(&dport->result, 0,
				माप(काष्ठा bfa_diag_dport_result_s));
		अगर (dport->i2hmsg.rsp.status == BFA_STATUS_DPORT_INV_SFP) अणु
			dport->test_state = BFA_DPORT_ST_NO_SFP;
		पूर्ण अन्यथा अणु
			dport->test_state = BFA_DPORT_ST_INP;
			bfa_dport_result_start(dport, BFA_DPORT_OPMODE_MANU);
		पूर्ण
		fallthrough;

	हाल BFA_DPORT_SM_REQFAIL:
		bfa_sm_set_state(dport, bfa_dport_sm_enabled);
		अवरोध;

	हाल BFA_DPORT_SM_HWFAIL:
		bfa_sm_set_state(dport, bfa_dport_sm_disabled);
		bfa_cb_fcdiag_dport(dport, BFA_STATUS_FAILED);
		अवरोध;

	शेष:
		bfa_sm_fault(dport->bfa, event);
	पूर्ण
पूर्ण

अटल व्योम
bfa_dport_sm_dynamic_disabling(काष्ठा bfa_dport_s *dport,
			       क्रमागत bfa_dport_sm_event event)
अणु
	bfa_trc(dport->bfa, event);

	चयन (event) अणु
	हाल BFA_DPORT_SM_SCN:
		चयन (dport->i2hmsg.scn.state) अणु
		हाल BFI_DPORT_SCN_DDPORT_DISABLED:
			bfa_sm_set_state(dport, bfa_dport_sm_disabled);
			dport->dynamic = BFA_FALSE;
			bfa_fcport_enable(dport->bfa);
			अवरोध;

		शेष:
			bfa_trc(dport->bfa, dport->i2hmsg.scn.state);
			bfa_sm_fault(dport->bfa, event);

		पूर्ण
		अवरोध;

	हाल BFA_DPORT_SM_HWFAIL:
		bfa_sm_set_state(dport, bfa_dport_sm_disabled);
		bfa_cb_fcdiag_dport(dport, BFA_STATUS_OK);
		अवरोध;

	शेष:
		bfa_sm_fault(dport->bfa, event);
	पूर्ण
पूर्ण

अटल व्योम
bfa_dport_sm_dynamic_disabling_qरुको(काष्ठा bfa_dport_s *dport,
			    क्रमागत bfa_dport_sm_event event)
अणु
	bfa_trc(dport->bfa, event);

	चयन (event) अणु
	हाल BFA_DPORT_SM_QRESUME:
		bfa_sm_set_state(dport, bfa_dport_sm_dynamic_disabling);
		bfa_dport_send_req(dport, BFI_DPORT_DYN_DISABLE);
		अवरोध;

	हाल BFA_DPORT_SM_HWFAIL:
		bfa_sm_set_state(dport, bfa_dport_sm_disabled);
		bfa_reqq_wcancel(&dport->reqq_रुको);
		bfa_cb_fcdiag_dport(dport, BFA_STATUS_OK);
		अवरोध;

	हाल BFA_DPORT_SM_SCN:
		/* ignore */
		अवरोध;

	शेष:
		bfa_sm_fault(dport->bfa, event);
	पूर्ण
पूर्ण

अटल bfa_boolean_t
bfa_dport_send_req(काष्ठा bfa_dport_s *dport, क्रमागत bfi_dport_req req)
अणु
	काष्ठा bfi_diag_dport_req_s *m;

	/*
	 * check क्रम room in queue to send request now
	 */
	m = bfa_reqq_next(dport->bfa, BFA_REQQ_DIAG);
	अगर (!m) अणु
		bfa_reqq_रुको(dport->bfa, BFA_REQQ_PORT, &dport->reqq_रुको);
		वापस BFA_FALSE;
	पूर्ण

	bfi_h2i_set(m->mh, BFI_MC_DIAG, BFI_DIAG_H2I_DPORT,
		    bfa_fn_lpu(dport->bfa));
	m->req  = req;
	अगर ((req == BFI_DPORT_ENABLE) || (req == BFI_DPORT_START)) अणु
		m->lpcnt = cpu_to_be32(dport->lpcnt);
		m->payload = cpu_to_be32(dport->payload);
	पूर्ण

	/*
	 * queue I/O message to firmware
	 */
	bfa_reqq_produce(dport->bfa, BFA_REQQ_DIAG, m->mh);

	वापस BFA_TRUE;
पूर्ण

अटल व्योम
bfa_dport_qresume(व्योम *cbarg)
अणु
	काष्ठा bfa_dport_s *dport = cbarg;

	bfa_sm_send_event(dport, BFA_DPORT_SM_QRESUME);
पूर्ण

अटल व्योम
bfa_dport_req_comp(काष्ठा bfa_dport_s *dport, काष्ठा bfi_diag_dport_rsp_s *msg)
अणु
	msg->status = cpu_to_be32(msg->status);
	dport->i2hmsg.rsp.status = msg->status;
	dport->rp_pwwn = msg->pwwn;
	dport->rp_nwwn = msg->nwwn;

	अगर ((msg->status == BFA_STATUS_OK) ||
	    (msg->status == BFA_STATUS_DPORT_NO_SFP)) अणु
		bfa_trc(dport->bfa, msg->status);
		bfa_trc(dport->bfa, dport->rp_pwwn);
		bfa_trc(dport->bfa, dport->rp_nwwn);
		bfa_sm_send_event(dport, BFA_DPORT_SM_FWRSP);

	पूर्ण अन्यथा अणु
		bfa_trc(dport->bfa, msg->status);
		bfa_sm_send_event(dport, BFA_DPORT_SM_REQFAIL);
	पूर्ण
	bfa_cb_fcdiag_dport(dport, msg->status);
पूर्ण

अटल bfa_boolean_t
bfa_dport_is_sending_req(काष्ठा bfa_dport_s *dport)
अणु
	अगर (bfa_sm_cmp_state(dport, bfa_dport_sm_enabling)	||
	    bfa_sm_cmp_state(dport, bfa_dport_sm_enabling_qरुको) ||
	    bfa_sm_cmp_state(dport, bfa_dport_sm_disabling)	||
	    bfa_sm_cmp_state(dport, bfa_dport_sm_disabling_qरुको) ||
	    bfa_sm_cmp_state(dport, bfa_dport_sm_starting)	||
	    bfa_sm_cmp_state(dport, bfa_dport_sm_starting_qरुको)) अणु
		वापस BFA_TRUE;
	पूर्ण अन्यथा अणु
		वापस BFA_FALSE;
	पूर्ण
पूर्ण

अटल व्योम
bfa_dport_scn(काष्ठा bfa_dport_s *dport, काष्ठा bfi_diag_dport_scn_s *msg)
अणु
	पूर्णांक i;
	uपूर्णांक8_t subtesttype;

	bfa_trc(dport->bfa, msg->state);
	dport->i2hmsg.scn.state = msg->state;

	चयन (dport->i2hmsg.scn.state) अणु
	हाल BFI_DPORT_SCN_TESTCOMP:
		dport->result.end_समय = kसमय_get_real_seconds();
		bfa_trc(dport->bfa, dport->result.end_समय);

		dport->result.status = msg->info.testcomp.status;
		bfa_trc(dport->bfa, dport->result.status);

		dport->result.roundtrip_latency =
			cpu_to_be32(msg->info.testcomp.latency);
		dport->result.est_cable_distance =
			cpu_to_be32(msg->info.testcomp.distance);
		dport->result.buffer_required =
			be16_to_cpu(msg->info.testcomp.numbuffer);

		dport->result.frmsz = be16_to_cpu(msg->info.testcomp.frm_sz);
		dport->result.speed = msg->info.testcomp.speed;

		bfa_trc(dport->bfa, dport->result.roundtrip_latency);
		bfa_trc(dport->bfa, dport->result.est_cable_distance);
		bfa_trc(dport->bfa, dport->result.buffer_required);
		bfa_trc(dport->bfa, dport->result.frmsz);
		bfa_trc(dport->bfa, dport->result.speed);

		क्रम (i = DPORT_TEST_ELOOP; i < DPORT_TEST_MAX; i++) अणु
			dport->result.subtest[i].status =
				msg->info.testcomp.subtest_status[i];
			bfa_trc(dport->bfa, dport->result.subtest[i].status);
		पूर्ण
		अवरोध;

	हाल BFI_DPORT_SCN_TESTSKIP:
	हाल BFI_DPORT_SCN_DDPORT_ENABLE:
		स_रखो(&dport->result, 0,
				माप(काष्ठा bfa_diag_dport_result_s));
		अवरोध;

	हाल BFI_DPORT_SCN_TESTSTART:
		स_रखो(&dport->result, 0,
				माप(काष्ठा bfa_diag_dport_result_s));
		dport->rp_pwwn = msg->info.teststart.pwwn;
		dport->rp_nwwn = msg->info.teststart.nwwn;
		dport->lpcnt = cpu_to_be32(msg->info.teststart.numfrm);
		bfa_dport_result_start(dport, msg->info.teststart.mode);
		अवरोध;

	हाल BFI_DPORT_SCN_SUBTESTSTART:
		subtesttype = msg->info.teststart.type;
		dport->result.subtest[subtesttype].start_समय =
			kसमय_get_real_seconds();
		dport->result.subtest[subtesttype].status =
			DPORT_TEST_ST_INPRG;

		bfa_trc(dport->bfa, subtesttype);
		bfa_trc(dport->bfa,
			dport->result.subtest[subtesttype].start_समय);
		अवरोध;

	हाल BFI_DPORT_SCN_SFP_REMOVED:
	हाल BFI_DPORT_SCN_DDPORT_DISABLED:
	हाल BFI_DPORT_SCN_DDPORT_DISABLE:
	हाल BFI_DPORT_SCN_FCPORT_DISABLE:
		dport->result.status = DPORT_TEST_ST_IDLE;
		अवरोध;

	शेष:
		bfa_sm_fault(dport->bfa, msg->state);
	पूर्ण

	bfa_sm_send_event(dport, BFA_DPORT_SM_SCN);
पूर्ण

/*
 * Dport enable
 *
 * @param[in] *bfa            - bfa data काष्ठा
 */
bfa_status_t
bfa_dport_enable(काष्ठा bfa_s *bfa, u32 lpcnt, u32 pat,
				bfa_cb_diag_t cbfn, व्योम *cbarg)
अणु
	काष्ठा bfa_fcdiag_s *fcdiag = BFA_FCDIAG_MOD(bfa);
	काष्ठा bfa_dport_s  *dport = &fcdiag->dport;

	/*
	 * Dport is not support in MEZZ card
	 */
	अगर (bfa_mfg_is_mezz(dport->bfa->ioc.attr->card_type)) अणु
		bfa_trc(dport->bfa, BFA_STATUS_PBC);
		वापस BFA_STATUS_CMD_NOTSUPP_MEZZ;
	पूर्ण

	/*
	 * Dport is supported in CT2 or above
	 */
	अगर (!(bfa_asic_id_ct2(dport->bfa->ioc.pcidev.device_id))) अणु
		bfa_trc(dport->bfa, dport->bfa->ioc.pcidev.device_id);
		वापस BFA_STATUS_FEATURE_NOT_SUPPORTED;
	पूर्ण

	/*
	 * Check to see अगर IOC is करोwn
	*/
	अगर (!bfa_iocfc_is_operational(bfa))
		वापस BFA_STATUS_IOC_NON_OP;

	/* अगर port is PBC disabled, वापस error */
	अगर (bfa_fcport_is_pbcdisabled(bfa)) अणु
		bfa_trc(dport->bfa, BFA_STATUS_PBC);
		वापस BFA_STATUS_PBC;
	पूर्ण

	/*
	 * Check अगर port mode is FC port
	 */
	अगर (bfa_ioc_get_type(&bfa->ioc) != BFA_IOC_TYPE_FC) अणु
		bfa_trc(dport->bfa, bfa_ioc_get_type(&bfa->ioc));
		वापस BFA_STATUS_CMD_NOTSUPP_CNA;
	पूर्ण

	/*
	 * Check अगर port is in LOOP mode
	 */
	अगर ((bfa_fcport_get_cfg_topology(bfa) == BFA_PORT_TOPOLOGY_LOOP) ||
	    (bfa_fcport_get_topology(bfa) == BFA_PORT_TOPOLOGY_LOOP)) अणु
		bfa_trc(dport->bfa, 0);
		वापस BFA_STATUS_TOPOLOGY_LOOP;
	पूर्ण

	/*
	 * Check अगर port is TRUNK mode
	 */
	अगर (bfa_fcport_is_trunk_enabled(bfa)) अणु
		bfa_trc(dport->bfa, 0);
		वापस BFA_STATUS_ERROR_TRUNK_ENABLED;
	पूर्ण

	/*
	 * Check अगर diag loopback is running
	 */
	अगर (bfa_fcdiag_lb_is_running(bfa)) अणु
		bfa_trc(dport->bfa, 0);
		वापस BFA_STATUS_DIAG_BUSY;
	पूर्ण

	/*
	 * Check to see अगर port is disable or in dport state
	 */
	अगर ((bfa_fcport_is_disabled(bfa) == BFA_FALSE) &&
	    (bfa_fcport_is_dport(bfa) == BFA_FALSE)) अणु
		bfa_trc(dport->bfa, 0);
		वापस BFA_STATUS_PORT_NOT_DISABLED;
	पूर्ण

	/*
	 * Check अगर dport is in dynamic mode
	 */
	अगर (dport->dynamic)
		वापस BFA_STATUS_DDPORT_ERR;

	/*
	 * Check अगर dport is busy
	 */
	अगर (bfa_dport_is_sending_req(dport))
		वापस BFA_STATUS_DEVBUSY;

	/*
	 * Check अगर dport is alपढ़ोy enabled
	 */
	अगर (bfa_sm_cmp_state(dport, bfa_dport_sm_enabled)) अणु
		bfa_trc(dport->bfa, 0);
		वापस BFA_STATUS_DPORT_ENABLED;
	पूर्ण

	bfa_trc(dport->bfa, lpcnt);
	bfa_trc(dport->bfa, pat);
	dport->lpcnt = (lpcnt) ? lpcnt : DPORT_ENABLE_LOOPCNT_DEFAULT;
	dport->payload = (pat) ? pat : LB_PATTERN_DEFAULT;
	dport->cbfn = cbfn;
	dport->cbarg = cbarg;

	bfa_sm_send_event(dport, BFA_DPORT_SM_ENABLE);
	वापस BFA_STATUS_OK;
पूर्ण

/*
 *	Dport disable
 *
 *	@param[in] *bfa            - bfa data काष्ठा
 */
bfa_status_t
bfa_dport_disable(काष्ठा bfa_s *bfa, bfa_cb_diag_t cbfn, व्योम *cbarg)
अणु
	काष्ठा bfa_fcdiag_s *fcdiag = BFA_FCDIAG_MOD(bfa);
	काष्ठा bfa_dport_s *dport = &fcdiag->dport;

	अगर (bfa_ioc_is_disabled(&bfa->ioc))
		वापस BFA_STATUS_IOC_DISABLED;

	/* अगर port is PBC disabled, वापस error */
	अगर (bfa_fcport_is_pbcdisabled(bfa)) अणु
		bfa_trc(dport->bfa, BFA_STATUS_PBC);
		वापस BFA_STATUS_PBC;
	पूर्ण

	/*
	 * Check अगर dport is in dynamic mode
	 */
	अगर (dport->dynamic) अणु
		वापस BFA_STATUS_DDPORT_ERR;
	पूर्ण

	/*
	 * Check to see अगर port is disable or in dport state
	 */
	अगर ((bfa_fcport_is_disabled(bfa) == BFA_FALSE) &&
	    (bfa_fcport_is_dport(bfa) == BFA_FALSE)) अणु
		bfa_trc(dport->bfa, 0);
		वापस BFA_STATUS_PORT_NOT_DISABLED;
	पूर्ण

	/*
	 * Check अगर dport is busy
	 */
	अगर (bfa_dport_is_sending_req(dport))
		वापस BFA_STATUS_DEVBUSY;

	/*
	 * Check अगर dport is alपढ़ोy disabled
	 */
	अगर (bfa_sm_cmp_state(dport, bfa_dport_sm_disabled)) अणु
		bfa_trc(dport->bfa, 0);
		वापस BFA_STATUS_DPORT_DISABLED;
	पूर्ण

	dport->cbfn = cbfn;
	dport->cbarg = cbarg;

	bfa_sm_send_event(dport, BFA_DPORT_SM_DISABLE);
	वापस BFA_STATUS_OK;
पूर्ण

/*
 * Dport start -- restart dport test
 *
 *   @param[in] *bfa		- bfa data काष्ठा
 */
bfa_status_t
bfa_dport_start(काष्ठा bfa_s *bfa, u32 lpcnt, u32 pat,
			bfa_cb_diag_t cbfn, व्योम *cbarg)
अणु
	काष्ठा bfa_fcdiag_s *fcdiag = BFA_FCDIAG_MOD(bfa);
	काष्ठा bfa_dport_s *dport = &fcdiag->dport;

	/*
	 * Check to see अगर IOC is करोwn
	 */
	अगर (!bfa_iocfc_is_operational(bfa))
		वापस BFA_STATUS_IOC_NON_OP;

	/*
	 * Check अगर dport is in dynamic mode
	 */
	अगर (dport->dynamic)
		वापस BFA_STATUS_DDPORT_ERR;

	/*
	 * Check अगर dport is busy
	 */
	अगर (bfa_dport_is_sending_req(dport))
		वापस BFA_STATUS_DEVBUSY;

	/*
	 * Check अगर dport is in enabled state.
	 * Test can only be restart when previous test has completed
	 */
	अगर (!bfa_sm_cmp_state(dport, bfa_dport_sm_enabled)) अणु
		bfa_trc(dport->bfa, 0);
		वापस BFA_STATUS_DPORT_DISABLED;

	पूर्ण अन्यथा अणु
		अगर (dport->test_state == BFA_DPORT_ST_NO_SFP)
			वापस BFA_STATUS_DPORT_INV_SFP;

		अगर (dport->test_state == BFA_DPORT_ST_INP)
			वापस BFA_STATUS_DEVBUSY;

		WARN_ON(dport->test_state != BFA_DPORT_ST_COMP);
	पूर्ण

	bfa_trc(dport->bfa, lpcnt);
	bfa_trc(dport->bfa, pat);

	dport->lpcnt = (lpcnt) ? lpcnt : DPORT_ENABLE_LOOPCNT_DEFAULT;
	dport->payload = (pat) ? pat : LB_PATTERN_DEFAULT;

	dport->cbfn = cbfn;
	dport->cbarg = cbarg;

	bfa_sm_send_event(dport, BFA_DPORT_SM_START);
	वापस BFA_STATUS_OK;
पूर्ण

/*
 * Dport show -- वापस dport test result
 *
 *   @param[in] *bfa		- bfa data काष्ठा
 */
bfa_status_t
bfa_dport_show(काष्ठा bfa_s *bfa, काष्ठा bfa_diag_dport_result_s *result)
अणु
	काष्ठा bfa_fcdiag_s *fcdiag = BFA_FCDIAG_MOD(bfa);
	काष्ठा bfa_dport_s *dport = &fcdiag->dport;

	/*
	 * Check to see अगर IOC is करोwn
	 */
	अगर (!bfa_iocfc_is_operational(bfa))
		वापस BFA_STATUS_IOC_NON_OP;

	/*
	 * Check अगर dport is busy
	 */
	अगर (bfa_dport_is_sending_req(dport))
		वापस BFA_STATUS_DEVBUSY;

	/*
	 * Check अगर dport is in enabled state.
	 */
	अगर (!bfa_sm_cmp_state(dport, bfa_dport_sm_enabled)) अणु
		bfa_trc(dport->bfa, 0);
		वापस BFA_STATUS_DPORT_DISABLED;

	पूर्ण

	/*
	 * Check अगर there is SFP
	 */
	अगर (dport->test_state == BFA_DPORT_ST_NO_SFP)
		वापस BFA_STATUS_DPORT_INV_SFP;

	स_नकल(result, &dport->result, माप(काष्ठा bfa_diag_dport_result_s));

	वापस BFA_STATUS_OK;
पूर्ण
