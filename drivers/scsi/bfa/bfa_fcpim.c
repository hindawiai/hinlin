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
#समावेश "bfa_modules.h"

BFA_TRC_खाता(HAL, FCPIM);

/*
 *  BFA ITNIM Related definitions
 */
अटल व्योम bfa_itnim_update_del_itn_stats(काष्ठा bfa_itnim_s *itnim);

#घोषणा BFA_ITNIM_FROM_TAG(_fcpim, _tag)                                \
	(((_fcpim)->itnim_arr + ((_tag) & ((_fcpim)->num_itnims - 1))))

#घोषणा bfa_fcpim_additn(__itnim)					\
	list_add_tail(&(__itnim)->qe, &(__itnim)->fcpim->itnim_q)
#घोषणा bfa_fcpim_delitn(__itnim)	करो अणु				\
	WARN_ON(!bfa_q_is_on_q(&(__itnim)->fcpim->itnim_q, __itnim));   \
	bfa_itnim_update_del_itn_stats(__itnim);      \
	list_del(&(__itnim)->qe);      \
	WARN_ON(!list_empty(&(__itnim)->io_q));				\
	WARN_ON(!list_empty(&(__itnim)->io_cleanup_q));			\
	WARN_ON(!list_empty(&(__itnim)->pending_q));			\
पूर्ण जबतक (0)

#घोषणा bfa_itnim_online_cb(__itnim) करो अणु				\
	अगर ((__itnim)->bfa->fcs)					\
		bfa_cb_itnim_online((__itnim)->ditn);      \
	अन्यथा अणु								\
		bfa_cb_queue((__itnim)->bfa, &(__itnim)->hcb_qe,	\
		__bfa_cb_itnim_online, (__itnim));      \
	पूर्ण								\
पूर्ण जबतक (0)

#घोषणा bfa_itnim_offline_cb(__itnim) करो अणु				\
	अगर ((__itnim)->bfa->fcs)					\
		bfa_cb_itnim_offline((__itnim)->ditn);      \
	अन्यथा अणु								\
		bfa_cb_queue((__itnim)->bfa, &(__itnim)->hcb_qe,	\
		__bfa_cb_itnim_offline, (__itnim));      \
	पूर्ण								\
पूर्ण जबतक (0)

#घोषणा bfa_itnim_sler_cb(__itnim) करो अणु					\
	अगर ((__itnim)->bfa->fcs)					\
		bfa_cb_itnim_sler((__itnim)->ditn);      \
	अन्यथा अणु								\
		bfa_cb_queue((__itnim)->bfa, &(__itnim)->hcb_qe,	\
		__bfa_cb_itnim_sler, (__itnim));      \
	पूर्ण								\
पूर्ण जबतक (0)

क्रमागत bfa_ioim_lm_ua_status अणु
	BFA_IOIM_LM_UA_RESET = 0,
	BFA_IOIM_LM_UA_SET = 1,
पूर्ण;

/*
 *  itnim state machine event
 */
क्रमागत bfa_itnim_event अणु
	BFA_ITNIM_SM_CREATE = 1,	/*  itnim is created */
	BFA_ITNIM_SM_ONLINE = 2,	/*  itnim is online */
	BFA_ITNIM_SM_OFFLINE = 3,	/*  itnim is offline */
	BFA_ITNIM_SM_FWRSP = 4,		/*  firmware response */
	BFA_ITNIM_SM_DELETE = 5,	/*  deleting an existing itnim */
	BFA_ITNIM_SM_CLEANUP = 6,	/*  IO cleanup completion */
	BFA_ITNIM_SM_SLER = 7,		/*  second level error recovery */
	BFA_ITNIM_SM_HWFAIL = 8,	/*  IOC h/w failure event */
	BFA_ITNIM_SM_QRESUME = 9,	/*  queue space available */
पूर्ण;

/*
 *  BFA IOIM related definitions
 */
#घोषणा bfa_ioim_move_to_comp_q(__ioim) करो अणु				\
	list_del(&(__ioim)->qe);					\
	list_add_tail(&(__ioim)->qe, &(__ioim)->fcpim->ioim_comp_q);	\
पूर्ण जबतक (0)


#घोषणा bfa_ioim_cb_profile_comp(__fcpim, __ioim) करो अणु			\
	अगर ((__fcpim)->profile_comp)					\
		(__fcpim)->profile_comp(__ioim);			\
पूर्ण जबतक (0)

#घोषणा bfa_ioim_cb_profile_start(__fcpim, __ioim) करो अणु			\
	अगर ((__fcpim)->profile_start)					\
		(__fcpim)->profile_start(__ioim);			\
पूर्ण जबतक (0)

/*
 * IO state machine events
 */
क्रमागत bfa_ioim_event अणु
	BFA_IOIM_SM_START	= 1,	/*  io start request from host */
	BFA_IOIM_SM_COMP_GOOD	= 2,	/*  io good comp, resource मुक्त */
	BFA_IOIM_SM_COMP	= 3,	/*  io comp, resource is मुक्त */
	BFA_IOIM_SM_COMP_UTAG	= 4,	/*  io comp, resource is मुक्त */
	BFA_IOIM_SM_DONE	= 5,	/*  io comp, resource not मुक्त */
	BFA_IOIM_SM_FREE	= 6,	/*  io resource is मुक्तd */
	BFA_IOIM_SM_ABORT	= 7,	/*  पात request from scsi stack */
	BFA_IOIM_SM_ABORT_COMP	= 8,	/*  पात from f/w */
	BFA_IOIM_SM_ABORT_DONE	= 9,	/*  पात completion from f/w */
	BFA_IOIM_SM_QRESUME	= 10,	/*  CQ space available to queue IO */
	BFA_IOIM_SM_SGALLOCED	= 11,	/*  SG page allocation successful */
	BFA_IOIM_SM_SQRETRY	= 12,	/*  sequence recovery retry */
	BFA_IOIM_SM_HCB		= 13,	/*  bfa callback complete */
	BFA_IOIM_SM_CLEANUP	= 14,	/*  IO cleanup from itnim */
	BFA_IOIM_SM_TMSTART	= 15,	/*  IO cleanup from tskim */
	BFA_IOIM_SM_TMDONE	= 16,	/*  IO cleanup from tskim */
	BFA_IOIM_SM_HWFAIL	= 17,	/*  IOC h/w failure event */
	BFA_IOIM_SM_IOTOV	= 18,	/*  ITN offline TOV */
पूर्ण;


/*
 *  BFA TSKIM related definitions
 */

/*
 * task management completion handling
 */
#घोषणा bfa_tskim_qcomp(__tskim, __cbfn) करो अणु				\
	bfa_cb_queue((__tskim)->bfa, &(__tskim)->hcb_qe, __cbfn, (__tskim));\
	bfa_tskim_notअगरy_comp(__tskim);      \
पूर्ण जबतक (0)

#घोषणा bfa_tskim_notअगरy_comp(__tskim) करो अणु				\
	अगर ((__tskim)->notअगरy)						\
		bfa_itnim_tskकरोne((__tskim)->itnim);      \
पूर्ण जबतक (0)


क्रमागत bfa_tskim_event अणु
	BFA_TSKIM_SM_START	= 1,	/*  TM command start		*/
	BFA_TSKIM_SM_DONE	= 2,	/*  TM completion		*/
	BFA_TSKIM_SM_QRESUME	= 3,	/*  resume after qfull		*/
	BFA_TSKIM_SM_HWFAIL	= 5,	/*  IOC h/w failure event	*/
	BFA_TSKIM_SM_HCB	= 6,	/*  BFA callback completion	*/
	BFA_TSKIM_SM_IOS_DONE	= 7,	/*  IO and sub TM completions	*/
	BFA_TSKIM_SM_CLEANUP	= 8,	/*  TM cleanup on ITN offline	*/
	BFA_TSKIM_SM_CLEANUP_DONE = 9,	/*  TM पात completion	*/
	BFA_TSKIM_SM_UTAG	= 10,	/*  TM completion unknown tag  */
पूर्ण;

/*
 * क्रमward declaration क्रम BFA ITNIM functions
 */
अटल व्योम     bfa_itnim_iocdisable_cleanup(काष्ठा bfa_itnim_s *itnim);
अटल bfa_boolean_t bfa_itnim_send_fwcreate(काष्ठा bfa_itnim_s *itnim);
अटल bfa_boolean_t bfa_itnim_send_fwdelete(काष्ठा bfa_itnim_s *itnim);
अटल व्योम     bfa_itnim_cleanp_comp(व्योम *itnim_cbarg);
अटल व्योम     bfa_itnim_cleanup(काष्ठा bfa_itnim_s *itnim);
अटल व्योम     __bfa_cb_itnim_online(व्योम *cbarg, bfa_boolean_t complete);
अटल व्योम     __bfa_cb_itnim_offline(व्योम *cbarg, bfa_boolean_t complete);
अटल व्योम     __bfa_cb_itnim_sler(व्योम *cbarg, bfa_boolean_t complete);
अटल व्योम     bfa_itnim_iotov_online(काष्ठा bfa_itnim_s *itnim);
अटल व्योम     bfa_itnim_iotov_cleanup(काष्ठा bfa_itnim_s *itnim);
अटल व्योम     bfa_itnim_iotov(व्योम *itnim_arg);
अटल व्योम     bfa_itnim_iotov_start(काष्ठा bfa_itnim_s *itnim);
अटल व्योम     bfa_itnim_iotov_stop(काष्ठा bfa_itnim_s *itnim);
अटल व्योम     bfa_itnim_iotov_delete(काष्ठा bfa_itnim_s *itnim);

/*
 * क्रमward declaration of ITNIM state machine
 */
अटल व्योम     bfa_itnim_sm_uninit(काष्ठा bfa_itnim_s *itnim,
					क्रमागत bfa_itnim_event event);
अटल व्योम     bfa_itnim_sm_created(काष्ठा bfa_itnim_s *itnim,
					क्रमागत bfa_itnim_event event);
अटल व्योम     bfa_itnim_sm_fwcreate(काष्ठा bfa_itnim_s *itnim,
					क्रमागत bfa_itnim_event event);
अटल व्योम     bfa_itnim_sm_delete_pending(काष्ठा bfa_itnim_s *itnim,
					क्रमागत bfa_itnim_event event);
अटल व्योम     bfa_itnim_sm_online(काष्ठा bfa_itnim_s *itnim,
					क्रमागत bfa_itnim_event event);
अटल व्योम     bfa_itnim_sm_sler(काष्ठा bfa_itnim_s *itnim,
					क्रमागत bfa_itnim_event event);
अटल व्योम     bfa_itnim_sm_cleanup_offline(काष्ठा bfa_itnim_s *itnim,
					क्रमागत bfa_itnim_event event);
अटल व्योम     bfa_itnim_sm_cleanup_delete(काष्ठा bfa_itnim_s *itnim,
					क्रमागत bfa_itnim_event event);
अटल व्योम     bfa_itnim_sm_fwdelete(काष्ठा bfa_itnim_s *itnim,
					क्रमागत bfa_itnim_event event);
अटल व्योम     bfa_itnim_sm_offline(काष्ठा bfa_itnim_s *itnim,
					क्रमागत bfa_itnim_event event);
अटल व्योम     bfa_itnim_sm_iocdisable(काष्ठा bfa_itnim_s *itnim,
					क्रमागत bfa_itnim_event event);
अटल व्योम     bfa_itnim_sm_deleting(काष्ठा bfa_itnim_s *itnim,
					क्रमागत bfa_itnim_event event);
अटल व्योम     bfa_itnim_sm_fwcreate_qfull(काष्ठा bfa_itnim_s *itnim,
					क्रमागत bfa_itnim_event event);
अटल व्योम     bfa_itnim_sm_fwdelete_qfull(काष्ठा bfa_itnim_s *itnim,
					क्रमागत bfa_itnim_event event);
अटल व्योम     bfa_itnim_sm_deleting_qfull(काष्ठा bfa_itnim_s *itnim,
					क्रमागत bfa_itnim_event event);

/*
 * क्रमward declaration क्रम BFA IOIM functions
 */
अटल bfa_boolean_t	bfa_ioim_send_ioreq(काष्ठा bfa_ioim_s *ioim);
अटल bfa_boolean_t	bfa_ioim_sgpg_alloc(काष्ठा bfa_ioim_s *ioim);
अटल bfa_boolean_t	bfa_ioim_send_पात(काष्ठा bfa_ioim_s *ioim);
अटल व्योम		bfa_ioim_notअगरy_cleanup(काष्ठा bfa_ioim_s *ioim);
अटल व्योम __bfa_cb_ioim_good_comp(व्योम *cbarg, bfa_boolean_t complete);
अटल व्योम __bfa_cb_ioim_comp(व्योम *cbarg, bfa_boolean_t complete);
अटल व्योम __bfa_cb_ioim_पात(व्योम *cbarg, bfa_boolean_t complete);
अटल व्योम __bfa_cb_ioim_failed(व्योम *cbarg, bfa_boolean_t complete);
अटल व्योम __bfa_cb_ioim_pathtov(व्योम *cbarg, bfa_boolean_t complete);
अटल bfa_boolean_t    bfa_ioim_is_पातable(काष्ठा bfa_ioim_s *ioim);

/*
 * क्रमward declaration of BFA IO state machine
 */
अटल व्योम     bfa_ioim_sm_uninit(काष्ठा bfa_ioim_s *ioim,
					क्रमागत bfa_ioim_event event);
अटल व्योम     bfa_ioim_sm_sgalloc(काष्ठा bfa_ioim_s *ioim,
					क्रमागत bfa_ioim_event event);
अटल व्योम     bfa_ioim_sm_active(काष्ठा bfa_ioim_s *ioim,
					क्रमागत bfa_ioim_event event);
अटल व्योम     bfa_ioim_sm_पात(काष्ठा bfa_ioim_s *ioim,
					क्रमागत bfa_ioim_event event);
अटल व्योम     bfa_ioim_sm_cleanup(काष्ठा bfa_ioim_s *ioim,
					क्रमागत bfa_ioim_event event);
अटल व्योम     bfa_ioim_sm_qfull(काष्ठा bfa_ioim_s *ioim,
					क्रमागत bfa_ioim_event event);
अटल व्योम     bfa_ioim_sm_पात_qfull(काष्ठा bfa_ioim_s *ioim,
					क्रमागत bfa_ioim_event event);
अटल व्योम     bfa_ioim_sm_cleanup_qfull(काष्ठा bfa_ioim_s *ioim,
					क्रमागत bfa_ioim_event event);
अटल व्योम     bfa_ioim_sm_hcb(काष्ठा bfa_ioim_s *ioim,
					क्रमागत bfa_ioim_event event);
अटल व्योम     bfa_ioim_sm_hcb_मुक्त(काष्ठा bfa_ioim_s *ioim,
					क्रमागत bfa_ioim_event event);
अटल व्योम     bfa_ioim_sm_resमुक्त(काष्ठा bfa_ioim_s *ioim,
					क्रमागत bfa_ioim_event event);
अटल व्योम	bfa_ioim_sm_cmnd_retry(काष्ठा bfa_ioim_s *ioim,
					क्रमागत bfa_ioim_event event);
/*
 * क्रमward declaration क्रम BFA TSKIM functions
 */
अटल व्योम     __bfa_cb_tskim_करोne(व्योम *cbarg, bfa_boolean_t complete);
अटल व्योम     __bfa_cb_tskim_failed(व्योम *cbarg, bfa_boolean_t complete);
अटल bfa_boolean_t bfa_tskim_match_scope(काष्ठा bfa_tskim_s *tskim,
					काष्ठा scsi_lun lun);
अटल व्योम     bfa_tskim_gather_ios(काष्ठा bfa_tskim_s *tskim);
अटल व्योम     bfa_tskim_cleanp_comp(व्योम *tskim_cbarg);
अटल व्योम     bfa_tskim_cleanup_ios(काष्ठा bfa_tskim_s *tskim);
अटल bfa_boolean_t bfa_tskim_send(काष्ठा bfa_tskim_s *tskim);
अटल bfa_boolean_t bfa_tskim_send_पात(काष्ठा bfa_tskim_s *tskim);
अटल व्योम     bfa_tskim_iocdisable_ios(काष्ठा bfa_tskim_s *tskim);

/*
 * क्रमward declaration of BFA TSKIM state machine
 */
अटल व्योम     bfa_tskim_sm_uninit(काष्ठा bfa_tskim_s *tskim,
					क्रमागत bfa_tskim_event event);
अटल व्योम     bfa_tskim_sm_active(काष्ठा bfa_tskim_s *tskim,
					क्रमागत bfa_tskim_event event);
अटल व्योम     bfa_tskim_sm_cleanup(काष्ठा bfa_tskim_s *tskim,
					क्रमागत bfa_tskim_event event);
अटल व्योम     bfa_tskim_sm_iocleanup(काष्ठा bfa_tskim_s *tskim,
					क्रमागत bfa_tskim_event event);
अटल व्योम     bfa_tskim_sm_qfull(काष्ठा bfa_tskim_s *tskim,
					क्रमागत bfa_tskim_event event);
अटल व्योम     bfa_tskim_sm_cleanup_qfull(काष्ठा bfa_tskim_s *tskim,
					क्रमागत bfa_tskim_event event);
अटल व्योम     bfa_tskim_sm_hcb(काष्ठा bfa_tskim_s *tskim,
					क्रमागत bfa_tskim_event event);
/*
 *  BFA FCP Initiator Mode module
 */

/*
 * Compute and वापस memory needed by FCP(im) module.
 */
अटल व्योम
bfa_fcpim_meminfo(काष्ठा bfa_iocfc_cfg_s *cfg, u32 *km_len)
अणु
	bfa_itnim_meminfo(cfg, km_len);

	/*
	 * IO memory
	 */
	*km_len += cfg->fwcfg.num_ioim_reqs *
	  (माप(काष्ठा bfa_ioim_s) + माप(काष्ठा bfa_ioim_sp_s));

	/*
	 * task management command memory
	 */
	अगर (cfg->fwcfg.num_tskim_reqs < BFA_TSKIM_MIN)
		cfg->fwcfg.num_tskim_reqs = BFA_TSKIM_MIN;
	*km_len += cfg->fwcfg.num_tskim_reqs * माप(काष्ठा bfa_tskim_s);
पूर्ण


अटल व्योम
bfa_fcpim_attach(काष्ठा bfa_fcp_mod_s *fcp, व्योम *bfad,
		काष्ठा bfa_iocfc_cfg_s *cfg, काष्ठा bfa_pcidev_s *pcidev)
अणु
	काष्ठा bfa_fcpim_s *fcpim = &fcp->fcpim;
	काष्ठा bfa_s *bfa = fcp->bfa;

	bfa_trc(bfa, cfg->drvcfg.path_tov);
	bfa_trc(bfa, cfg->fwcfg.num_rports);
	bfa_trc(bfa, cfg->fwcfg.num_ioim_reqs);
	bfa_trc(bfa, cfg->fwcfg.num_tskim_reqs);

	fcpim->fcp		= fcp;
	fcpim->bfa		= bfa;
	fcpim->num_itnims	= cfg->fwcfg.num_rports;
	fcpim->num_tskim_reqs = cfg->fwcfg.num_tskim_reqs;
	fcpim->path_tov		= cfg->drvcfg.path_tov;
	fcpim->delay_comp	= cfg->drvcfg.delay_comp;
	fcpim->profile_comp = शून्य;
	fcpim->profile_start = शून्य;

	bfa_itnim_attach(fcpim);
	bfa_tskim_attach(fcpim);
	bfa_ioim_attach(fcpim);
पूर्ण

व्योम
bfa_fcpim_iocdisable(काष्ठा bfa_fcp_mod_s *fcp)
अणु
	काष्ठा bfa_fcpim_s *fcpim = &fcp->fcpim;
	काष्ठा bfa_itnim_s *itnim;
	काष्ठा list_head *qe, *qen;

	/* Enqueue unused ioim resources to मुक्त_q */
	list_splice_tail_init(&fcpim->tskim_unused_q, &fcpim->tskim_मुक्त_q);

	list_क्रम_each_safe(qe, qen, &fcpim->itnim_q) अणु
		itnim = (काष्ठा bfa_itnim_s *) qe;
		bfa_itnim_iocdisable(itnim);
	पूर्ण
पूर्ण

व्योम
bfa_fcpim_path_tov_set(काष्ठा bfa_s *bfa, u16 path_tov)
अणु
	काष्ठा bfa_fcpim_s *fcpim = BFA_FCPIM(bfa);

	fcpim->path_tov = path_tov * 1000;
	अगर (fcpim->path_tov > BFA_FCPIM_PATHTOV_MAX)
		fcpim->path_tov = BFA_FCPIM_PATHTOV_MAX;
पूर्ण

u16
bfa_fcpim_path_tov_get(काष्ठा bfa_s *bfa)
अणु
	काष्ठा bfa_fcpim_s *fcpim = BFA_FCPIM(bfa);

	वापस fcpim->path_tov / 1000;
पूर्ण

#घोषणा bfa_fcpim_add_iostats(__l, __r, __stats)	\
	(__l->__stats += __r->__stats)

व्योम
bfa_fcpim_add_stats(काष्ठा bfa_itnim_iostats_s *lstats,
		काष्ठा bfa_itnim_iostats_s *rstats)
अणु
	bfa_fcpim_add_iostats(lstats, rstats, total_ios);
	bfa_fcpim_add_iostats(lstats, rstats, qresumes);
	bfa_fcpim_add_iostats(lstats, rstats, no_iotags);
	bfa_fcpim_add_iostats(lstats, rstats, io_पातs);
	bfa_fcpim_add_iostats(lstats, rstats, no_tskims);
	bfa_fcpim_add_iostats(lstats, rstats, iocomp_ok);
	bfa_fcpim_add_iostats(lstats, rstats, iocomp_underrun);
	bfa_fcpim_add_iostats(lstats, rstats, iocomp_overrun);
	bfa_fcpim_add_iostats(lstats, rstats, iocomp_पातed);
	bfa_fcpim_add_iostats(lstats, rstats, iocomp_समयकरोut);
	bfa_fcpim_add_iostats(lstats, rstats, iocom_nexus_पात);
	bfa_fcpim_add_iostats(lstats, rstats, iocom_proto_err);
	bfa_fcpim_add_iostats(lstats, rstats, iocom_dअगर_err);
	bfa_fcpim_add_iostats(lstats, rstats, iocom_sqer_needed);
	bfa_fcpim_add_iostats(lstats, rstats, iocom_res_मुक्त);
	bfa_fcpim_add_iostats(lstats, rstats, iocom_hostabrts);
	bfa_fcpim_add_iostats(lstats, rstats, iocom_utags);
	bfa_fcpim_add_iostats(lstats, rstats, io_cleanups);
	bfa_fcpim_add_iostats(lstats, rstats, io_पंचांगपातs);
	bfa_fcpim_add_iostats(lstats, rstats, onlines);
	bfa_fcpim_add_iostats(lstats, rstats, offlines);
	bfa_fcpim_add_iostats(lstats, rstats, creates);
	bfa_fcpim_add_iostats(lstats, rstats, deletes);
	bfa_fcpim_add_iostats(lstats, rstats, create_comps);
	bfa_fcpim_add_iostats(lstats, rstats, delete_comps);
	bfa_fcpim_add_iostats(lstats, rstats, sler_events);
	bfa_fcpim_add_iostats(lstats, rstats, fw_create);
	bfa_fcpim_add_iostats(lstats, rstats, fw_delete);
	bfa_fcpim_add_iostats(lstats, rstats, ioc_disabled);
	bfa_fcpim_add_iostats(lstats, rstats, cleanup_comps);
	bfa_fcpim_add_iostats(lstats, rstats, पंचांग_cmnds);
	bfa_fcpim_add_iostats(lstats, rstats, पंचांग_fw_rsps);
	bfa_fcpim_add_iostats(lstats, rstats, पंचांग_success);
	bfa_fcpim_add_iostats(lstats, rstats, पंचांग_failures);
	bfa_fcpim_add_iostats(lstats, rstats, पंचांग_io_comps);
	bfa_fcpim_add_iostats(lstats, rstats, पंचांग_qresumes);
	bfa_fcpim_add_iostats(lstats, rstats, पंचांग_iocकरोwns);
	bfa_fcpim_add_iostats(lstats, rstats, पंचांग_cleanups);
	bfa_fcpim_add_iostats(lstats, rstats, पंचांग_cleanup_comps);
	bfa_fcpim_add_iostats(lstats, rstats, io_comps);
	bfa_fcpim_add_iostats(lstats, rstats, input_reqs);
	bfa_fcpim_add_iostats(lstats, rstats, output_reqs);
	bfa_fcpim_add_iostats(lstats, rstats, rd_throughput);
	bfa_fcpim_add_iostats(lstats, rstats, wr_throughput);
पूर्ण

bfa_status_t
bfa_fcpim_port_iostats(काष्ठा bfa_s *bfa,
		काष्ठा bfa_itnim_iostats_s *stats, u8 lp_tag)
अणु
	काष्ठा bfa_fcpim_s *fcpim = BFA_FCPIM(bfa);
	काष्ठा list_head *qe, *qen;
	काष्ठा bfa_itnim_s *itnim;

	/* accumulate IO stats from itnim */
	स_रखो(stats, 0, माप(काष्ठा bfa_itnim_iostats_s));
	list_क्रम_each_safe(qe, qen, &fcpim->itnim_q) अणु
		itnim = (काष्ठा bfa_itnim_s *) qe;
		अगर (itnim->rport->rport_info.lp_tag != lp_tag)
			जारी;
		bfa_fcpim_add_stats(stats, &(itnim->stats));
	पूर्ण
	वापस BFA_STATUS_OK;
पूर्ण

अटल व्योम
bfa_ioim_profile_comp(काष्ठा bfa_ioim_s *ioim)
अणु
	काष्ठा bfa_itnim_latency_s *io_lat =
			&(ioim->itnim->ioprofile.io_latency);
	u32 val, idx;

	val = (u32)(jअगरfies - ioim->start_समय);
	idx = bfa_ioim_get_index(scsi_bufflen((काष्ठा scsi_cmnd *)ioim->dio));
	bfa_itnim_ioprofile_update(ioim->itnim, idx);

	io_lat->count[idx]++;
	io_lat->min[idx] = (io_lat->min[idx] < val) ? io_lat->min[idx] : val;
	io_lat->max[idx] = (io_lat->max[idx] > val) ? io_lat->max[idx] : val;
	io_lat->avg[idx] += val;
पूर्ण

अटल व्योम
bfa_ioim_profile_start(काष्ठा bfa_ioim_s *ioim)
अणु
	ioim->start_समय = jअगरfies;
पूर्ण

bfa_status_t
bfa_fcpim_profile_on(काष्ठा bfa_s *bfa, समय64_t समय)
अणु
	काष्ठा bfa_itnim_s *itnim;
	काष्ठा bfa_fcpim_s *fcpim = BFA_FCPIM(bfa);
	काष्ठा list_head *qe, *qen;

	/* accumulate IO stats from itnim */
	list_क्रम_each_safe(qe, qen, &fcpim->itnim_q) अणु
		itnim = (काष्ठा bfa_itnim_s *) qe;
		bfa_itnim_clear_stats(itnim);
	पूर्ण
	fcpim->io_profile = BFA_TRUE;
	fcpim->io_profile_start_समय = समय;
	fcpim->profile_comp = bfa_ioim_profile_comp;
	fcpim->profile_start = bfa_ioim_profile_start;
	वापस BFA_STATUS_OK;
पूर्ण

bfa_status_t
bfa_fcpim_profile_off(काष्ठा bfa_s *bfa)
अणु
	काष्ठा bfa_fcpim_s *fcpim = BFA_FCPIM(bfa);
	fcpim->io_profile = BFA_FALSE;
	fcpim->io_profile_start_समय = 0;
	fcpim->profile_comp = शून्य;
	fcpim->profile_start = शून्य;
	वापस BFA_STATUS_OK;
पूर्ण

u16
bfa_fcpim_qdepth_get(काष्ठा bfa_s *bfa)
अणु
	काष्ठा bfa_fcpim_s *fcpim = BFA_FCPIM(bfa);

	वापस fcpim->q_depth;
पूर्ण

/*
 *  BFA ITNIM module state machine functions
 */

/*
 * Beginning/unallocated state - no events expected.
 */
अटल व्योम
bfa_itnim_sm_uninit(काष्ठा bfa_itnim_s *itnim, क्रमागत bfa_itnim_event event)
अणु
	bfa_trc(itnim->bfa, itnim->rport->rport_tag);
	bfa_trc(itnim->bfa, event);

	चयन (event) अणु
	हाल BFA_ITNIM_SM_CREATE:
		bfa_sm_set_state(itnim, bfa_itnim_sm_created);
		itnim->is_online = BFA_FALSE;
		bfa_fcpim_additn(itnim);
		अवरोध;

	शेष:
		bfa_sm_fault(itnim->bfa, event);
	पूर्ण
पूर्ण

/*
 * Beginning state, only online event expected.
 */
अटल व्योम
bfa_itnim_sm_created(काष्ठा bfa_itnim_s *itnim, क्रमागत bfa_itnim_event event)
अणु
	bfa_trc(itnim->bfa, itnim->rport->rport_tag);
	bfa_trc(itnim->bfa, event);

	चयन (event) अणु
	हाल BFA_ITNIM_SM_ONLINE:
		अगर (bfa_itnim_send_fwcreate(itnim))
			bfa_sm_set_state(itnim, bfa_itnim_sm_fwcreate);
		अन्यथा
			bfa_sm_set_state(itnim, bfa_itnim_sm_fwcreate_qfull);
		अवरोध;

	हाल BFA_ITNIM_SM_DELETE:
		bfa_sm_set_state(itnim, bfa_itnim_sm_uninit);
		bfa_fcpim_delitn(itnim);
		अवरोध;

	हाल BFA_ITNIM_SM_HWFAIL:
		bfa_sm_set_state(itnim, bfa_itnim_sm_iocdisable);
		अवरोध;

	शेष:
		bfa_sm_fault(itnim->bfa, event);
	पूर्ण
पूर्ण

/*
 *	Waiting क्रम itnim create response from firmware.
 */
अटल व्योम
bfa_itnim_sm_fwcreate(काष्ठा bfa_itnim_s *itnim, क्रमागत bfa_itnim_event event)
अणु
	bfa_trc(itnim->bfa, itnim->rport->rport_tag);
	bfa_trc(itnim->bfa, event);

	चयन (event) अणु
	हाल BFA_ITNIM_SM_FWRSP:
		bfa_sm_set_state(itnim, bfa_itnim_sm_online);
		itnim->is_online = BFA_TRUE;
		bfa_itnim_iotov_online(itnim);
		bfa_itnim_online_cb(itnim);
		अवरोध;

	हाल BFA_ITNIM_SM_DELETE:
		bfa_sm_set_state(itnim, bfa_itnim_sm_delete_pending);
		अवरोध;

	हाल BFA_ITNIM_SM_OFFLINE:
		अगर (bfa_itnim_send_fwdelete(itnim))
			bfa_sm_set_state(itnim, bfa_itnim_sm_fwdelete);
		अन्यथा
			bfa_sm_set_state(itnim, bfa_itnim_sm_fwdelete_qfull);
		अवरोध;

	हाल BFA_ITNIM_SM_HWFAIL:
		bfa_sm_set_state(itnim, bfa_itnim_sm_iocdisable);
		अवरोध;

	शेष:
		bfa_sm_fault(itnim->bfa, event);
	पूर्ण
पूर्ण

अटल व्योम
bfa_itnim_sm_fwcreate_qfull(काष्ठा bfa_itnim_s *itnim,
			क्रमागत bfa_itnim_event event)
अणु
	bfa_trc(itnim->bfa, itnim->rport->rport_tag);
	bfa_trc(itnim->bfa, event);

	चयन (event) अणु
	हाल BFA_ITNIM_SM_QRESUME:
		bfa_sm_set_state(itnim, bfa_itnim_sm_fwcreate);
		bfa_itnim_send_fwcreate(itnim);
		अवरोध;

	हाल BFA_ITNIM_SM_DELETE:
		bfa_sm_set_state(itnim, bfa_itnim_sm_uninit);
		bfa_reqq_wcancel(&itnim->reqq_रुको);
		bfa_fcpim_delitn(itnim);
		अवरोध;

	हाल BFA_ITNIM_SM_OFFLINE:
		bfa_sm_set_state(itnim, bfa_itnim_sm_offline);
		bfa_reqq_wcancel(&itnim->reqq_रुको);
		bfa_itnim_offline_cb(itnim);
		अवरोध;

	हाल BFA_ITNIM_SM_HWFAIL:
		bfa_sm_set_state(itnim, bfa_itnim_sm_iocdisable);
		bfa_reqq_wcancel(&itnim->reqq_रुको);
		अवरोध;

	शेष:
		bfa_sm_fault(itnim->bfa, event);
	पूर्ण
पूर्ण

/*
 * Waiting क्रम itnim create response from firmware, a delete is pending.
 */
अटल व्योम
bfa_itnim_sm_delete_pending(काष्ठा bfa_itnim_s *itnim,
				क्रमागत bfa_itnim_event event)
अणु
	bfa_trc(itnim->bfa, itnim->rport->rport_tag);
	bfa_trc(itnim->bfa, event);

	चयन (event) अणु
	हाल BFA_ITNIM_SM_FWRSP:
		अगर (bfa_itnim_send_fwdelete(itnim))
			bfa_sm_set_state(itnim, bfa_itnim_sm_deleting);
		अन्यथा
			bfa_sm_set_state(itnim, bfa_itnim_sm_deleting_qfull);
		अवरोध;

	हाल BFA_ITNIM_SM_HWFAIL:
		bfa_sm_set_state(itnim, bfa_itnim_sm_uninit);
		bfa_fcpim_delitn(itnim);
		अवरोध;

	शेष:
		bfa_sm_fault(itnim->bfa, event);
	पूर्ण
पूर्ण

/*
 * Online state - normal parking state.
 */
अटल व्योम
bfa_itnim_sm_online(काष्ठा bfa_itnim_s *itnim, क्रमागत bfa_itnim_event event)
अणु
	bfa_trc(itnim->bfa, itnim->rport->rport_tag);
	bfa_trc(itnim->bfa, event);

	चयन (event) अणु
	हाल BFA_ITNIM_SM_OFFLINE:
		bfa_sm_set_state(itnim, bfa_itnim_sm_cleanup_offline);
		itnim->is_online = BFA_FALSE;
		bfa_itnim_iotov_start(itnim);
		bfa_itnim_cleanup(itnim);
		अवरोध;

	हाल BFA_ITNIM_SM_DELETE:
		bfa_sm_set_state(itnim, bfa_itnim_sm_cleanup_delete);
		itnim->is_online = BFA_FALSE;
		bfa_itnim_cleanup(itnim);
		अवरोध;

	हाल BFA_ITNIM_SM_SLER:
		bfa_sm_set_state(itnim, bfa_itnim_sm_sler);
		itnim->is_online = BFA_FALSE;
		bfa_itnim_iotov_start(itnim);
		bfa_itnim_sler_cb(itnim);
		अवरोध;

	हाल BFA_ITNIM_SM_HWFAIL:
		bfa_sm_set_state(itnim, bfa_itnim_sm_iocdisable);
		itnim->is_online = BFA_FALSE;
		bfa_itnim_iotov_start(itnim);
		bfa_itnim_iocdisable_cleanup(itnim);
		अवरोध;

	शेष:
		bfa_sm_fault(itnim->bfa, event);
	पूर्ण
पूर्ण

/*
 * Second level error recovery need.
 */
अटल व्योम
bfa_itnim_sm_sler(काष्ठा bfa_itnim_s *itnim, क्रमागत bfa_itnim_event event)
अणु
	bfa_trc(itnim->bfa, itnim->rport->rport_tag);
	bfa_trc(itnim->bfa, event);

	चयन (event) अणु
	हाल BFA_ITNIM_SM_OFFLINE:
		bfa_sm_set_state(itnim, bfa_itnim_sm_cleanup_offline);
		bfa_itnim_cleanup(itnim);
		अवरोध;

	हाल BFA_ITNIM_SM_DELETE:
		bfa_sm_set_state(itnim, bfa_itnim_sm_cleanup_delete);
		bfa_itnim_cleanup(itnim);
		bfa_itnim_iotov_delete(itnim);
		अवरोध;

	हाल BFA_ITNIM_SM_HWFAIL:
		bfa_sm_set_state(itnim, bfa_itnim_sm_iocdisable);
		bfa_itnim_iocdisable_cleanup(itnim);
		अवरोध;

	शेष:
		bfa_sm_fault(itnim->bfa, event);
	पूर्ण
पूर्ण

/*
 * Going offline. Waiting क्रम active IO cleanup.
 */
अटल व्योम
bfa_itnim_sm_cleanup_offline(काष्ठा bfa_itnim_s *itnim,
				 क्रमागत bfa_itnim_event event)
अणु
	bfa_trc(itnim->bfa, itnim->rport->rport_tag);
	bfa_trc(itnim->bfa, event);

	चयन (event) अणु
	हाल BFA_ITNIM_SM_CLEANUP:
		अगर (bfa_itnim_send_fwdelete(itnim))
			bfa_sm_set_state(itnim, bfa_itnim_sm_fwdelete);
		अन्यथा
			bfa_sm_set_state(itnim, bfa_itnim_sm_fwdelete_qfull);
		अवरोध;

	हाल BFA_ITNIM_SM_DELETE:
		bfa_sm_set_state(itnim, bfa_itnim_sm_cleanup_delete);
		bfa_itnim_iotov_delete(itnim);
		अवरोध;

	हाल BFA_ITNIM_SM_HWFAIL:
		bfa_sm_set_state(itnim, bfa_itnim_sm_iocdisable);
		bfa_itnim_iocdisable_cleanup(itnim);
		bfa_itnim_offline_cb(itnim);
		अवरोध;

	हाल BFA_ITNIM_SM_SLER:
		अवरोध;

	शेष:
		bfa_sm_fault(itnim->bfa, event);
	पूर्ण
पूर्ण

/*
 * Deleting itnim. Waiting क्रम active IO cleanup.
 */
अटल व्योम
bfa_itnim_sm_cleanup_delete(काष्ठा bfa_itnim_s *itnim,
				क्रमागत bfa_itnim_event event)
अणु
	bfa_trc(itnim->bfa, itnim->rport->rport_tag);
	bfa_trc(itnim->bfa, event);

	चयन (event) अणु
	हाल BFA_ITNIM_SM_CLEANUP:
		अगर (bfa_itnim_send_fwdelete(itnim))
			bfa_sm_set_state(itnim, bfa_itnim_sm_deleting);
		अन्यथा
			bfa_sm_set_state(itnim, bfa_itnim_sm_deleting_qfull);
		अवरोध;

	हाल BFA_ITNIM_SM_HWFAIL:
		bfa_sm_set_state(itnim, bfa_itnim_sm_iocdisable);
		bfa_itnim_iocdisable_cleanup(itnim);
		अवरोध;

	शेष:
		bfa_sm_fault(itnim->bfa, event);
	पूर्ण
पूर्ण

/*
 * Rport offline. Fimrware itnim is being deleted - aरुकोing f/w response.
 */
अटल व्योम
bfa_itnim_sm_fwdelete(काष्ठा bfa_itnim_s *itnim, क्रमागत bfa_itnim_event event)
अणु
	bfa_trc(itnim->bfa, itnim->rport->rport_tag);
	bfa_trc(itnim->bfa, event);

	चयन (event) अणु
	हाल BFA_ITNIM_SM_FWRSP:
		bfa_sm_set_state(itnim, bfa_itnim_sm_offline);
		bfa_itnim_offline_cb(itnim);
		अवरोध;

	हाल BFA_ITNIM_SM_DELETE:
		bfa_sm_set_state(itnim, bfa_itnim_sm_deleting);
		अवरोध;

	हाल BFA_ITNIM_SM_HWFAIL:
		bfa_sm_set_state(itnim, bfa_itnim_sm_iocdisable);
		bfa_itnim_offline_cb(itnim);
		अवरोध;

	शेष:
		bfa_sm_fault(itnim->bfa, event);
	पूर्ण
पूर्ण

अटल व्योम
bfa_itnim_sm_fwdelete_qfull(काष्ठा bfa_itnim_s *itnim,
			क्रमागत bfa_itnim_event event)
अणु
	bfa_trc(itnim->bfa, itnim->rport->rport_tag);
	bfa_trc(itnim->bfa, event);

	चयन (event) अणु
	हाल BFA_ITNIM_SM_QRESUME:
		bfa_sm_set_state(itnim, bfa_itnim_sm_fwdelete);
		bfa_itnim_send_fwdelete(itnim);
		अवरोध;

	हाल BFA_ITNIM_SM_DELETE:
		bfa_sm_set_state(itnim, bfa_itnim_sm_deleting_qfull);
		अवरोध;

	हाल BFA_ITNIM_SM_HWFAIL:
		bfa_sm_set_state(itnim, bfa_itnim_sm_iocdisable);
		bfa_reqq_wcancel(&itnim->reqq_रुको);
		bfa_itnim_offline_cb(itnim);
		अवरोध;

	शेष:
		bfa_sm_fault(itnim->bfa, event);
	पूर्ण
पूर्ण

/*
 * Offline state.
 */
अटल व्योम
bfa_itnim_sm_offline(काष्ठा bfa_itnim_s *itnim, क्रमागत bfa_itnim_event event)
अणु
	bfa_trc(itnim->bfa, itnim->rport->rport_tag);
	bfa_trc(itnim->bfa, event);

	चयन (event) अणु
	हाल BFA_ITNIM_SM_DELETE:
		bfa_sm_set_state(itnim, bfa_itnim_sm_uninit);
		bfa_itnim_iotov_delete(itnim);
		bfa_fcpim_delitn(itnim);
		अवरोध;

	हाल BFA_ITNIM_SM_ONLINE:
		अगर (bfa_itnim_send_fwcreate(itnim))
			bfa_sm_set_state(itnim, bfa_itnim_sm_fwcreate);
		अन्यथा
			bfa_sm_set_state(itnim, bfa_itnim_sm_fwcreate_qfull);
		अवरोध;

	हाल BFA_ITNIM_SM_HWFAIL:
		bfa_sm_set_state(itnim, bfa_itnim_sm_iocdisable);
		अवरोध;

	शेष:
		bfa_sm_fault(itnim->bfa, event);
	पूर्ण
पूर्ण

अटल व्योम
bfa_itnim_sm_iocdisable(काष्ठा bfa_itnim_s *itnim,
				क्रमागत bfa_itnim_event event)
अणु
	bfa_trc(itnim->bfa, itnim->rport->rport_tag);
	bfa_trc(itnim->bfa, event);

	चयन (event) अणु
	हाल BFA_ITNIM_SM_DELETE:
		bfa_sm_set_state(itnim, bfa_itnim_sm_uninit);
		bfa_itnim_iotov_delete(itnim);
		bfa_fcpim_delitn(itnim);
		अवरोध;

	हाल BFA_ITNIM_SM_OFFLINE:
		bfa_itnim_offline_cb(itnim);
		अवरोध;

	हाल BFA_ITNIM_SM_ONLINE:
		अगर (bfa_itnim_send_fwcreate(itnim))
			bfa_sm_set_state(itnim, bfa_itnim_sm_fwcreate);
		अन्यथा
			bfa_sm_set_state(itnim, bfa_itnim_sm_fwcreate_qfull);
		अवरोध;

	हाल BFA_ITNIM_SM_HWFAIL:
		अवरोध;

	शेष:
		bfa_sm_fault(itnim->bfa, event);
	पूर्ण
पूर्ण

/*
 * Itnim is deleted, रुकोing क्रम firmware response to delete.
 */
अटल व्योम
bfa_itnim_sm_deleting(काष्ठा bfa_itnim_s *itnim, क्रमागत bfa_itnim_event event)
अणु
	bfa_trc(itnim->bfa, itnim->rport->rport_tag);
	bfa_trc(itnim->bfa, event);

	चयन (event) अणु
	हाल BFA_ITNIM_SM_FWRSP:
	हाल BFA_ITNIM_SM_HWFAIL:
		bfa_sm_set_state(itnim, bfa_itnim_sm_uninit);
		bfa_fcpim_delitn(itnim);
		अवरोध;

	शेष:
		bfa_sm_fault(itnim->bfa, event);
	पूर्ण
पूर्ण

अटल व्योम
bfa_itnim_sm_deleting_qfull(काष्ठा bfa_itnim_s *itnim,
		क्रमागत bfa_itnim_event event)
अणु
	bfa_trc(itnim->bfa, itnim->rport->rport_tag);
	bfa_trc(itnim->bfa, event);

	चयन (event) अणु
	हाल BFA_ITNIM_SM_QRESUME:
		bfa_sm_set_state(itnim, bfa_itnim_sm_deleting);
		bfa_itnim_send_fwdelete(itnim);
		अवरोध;

	हाल BFA_ITNIM_SM_HWFAIL:
		bfa_sm_set_state(itnim, bfa_itnim_sm_uninit);
		bfa_reqq_wcancel(&itnim->reqq_रुको);
		bfa_fcpim_delitn(itnim);
		अवरोध;

	शेष:
		bfa_sm_fault(itnim->bfa, event);
	पूर्ण
पूर्ण

/*
 * Initiate cleanup of all IOs on an IOC failure.
 */
अटल व्योम
bfa_itnim_iocdisable_cleanup(काष्ठा bfa_itnim_s *itnim)
अणु
	काष्ठा bfa_tskim_s *tskim;
	काष्ठा bfa_ioim_s *ioim;
	काष्ठा list_head	*qe, *qen;

	list_क्रम_each_safe(qe, qen, &itnim->tsk_q) अणु
		tskim = (काष्ठा bfa_tskim_s *) qe;
		bfa_tskim_iocdisable(tskim);
	पूर्ण

	list_क्रम_each_safe(qe, qen, &itnim->io_q) अणु
		ioim = (काष्ठा bfa_ioim_s *) qe;
		bfa_ioim_iocdisable(ioim);
	पूर्ण

	/*
	 * For IO request in pending queue, we pretend an early समयout.
	 */
	list_क्रम_each_safe(qe, qen, &itnim->pending_q) अणु
		ioim = (काष्ठा bfa_ioim_s *) qe;
		bfa_ioim_tov(ioim);
	पूर्ण

	list_क्रम_each_safe(qe, qen, &itnim->io_cleanup_q) अणु
		ioim = (काष्ठा bfa_ioim_s *) qe;
		bfa_ioim_iocdisable(ioim);
	पूर्ण
पूर्ण

/*
 * IO cleanup completion
 */
अटल व्योम
bfa_itnim_cleanp_comp(व्योम *itnim_cbarg)
अणु
	काष्ठा bfa_itnim_s *itnim = itnim_cbarg;

	bfa_stats(itnim, cleanup_comps);
	bfa_sm_send_event(itnim, BFA_ITNIM_SM_CLEANUP);
पूर्ण

/*
 * Initiate cleanup of all IOs.
 */
अटल व्योम
bfa_itnim_cleanup(काष्ठा bfa_itnim_s *itnim)
अणु
	काष्ठा bfa_ioim_s  *ioim;
	काष्ठा bfa_tskim_s *tskim;
	काष्ठा list_head	*qe, *qen;

	bfa_wc_init(&itnim->wc, bfa_itnim_cleanp_comp, itnim);

	list_क्रम_each_safe(qe, qen, &itnim->io_q) अणु
		ioim = (काष्ठा bfa_ioim_s *) qe;

		/*
		 * Move IO to a cleanup queue from active queue so that a later
		 * TM will not pickup this IO.
		 */
		list_del(&ioim->qe);
		list_add_tail(&ioim->qe, &itnim->io_cleanup_q);

		bfa_wc_up(&itnim->wc);
		bfa_ioim_cleanup(ioim);
	पूर्ण

	list_क्रम_each_safe(qe, qen, &itnim->tsk_q) अणु
		tskim = (काष्ठा bfa_tskim_s *) qe;
		bfa_wc_up(&itnim->wc);
		bfa_tskim_cleanup(tskim);
	पूर्ण

	bfa_wc_रुको(&itnim->wc);
पूर्ण

अटल व्योम
__bfa_cb_itnim_online(व्योम *cbarg, bfa_boolean_t complete)
अणु
	काष्ठा bfa_itnim_s *itnim = cbarg;

	अगर (complete)
		bfa_cb_itnim_online(itnim->ditn);
पूर्ण

अटल व्योम
__bfa_cb_itnim_offline(व्योम *cbarg, bfa_boolean_t complete)
अणु
	काष्ठा bfa_itnim_s *itnim = cbarg;

	अगर (complete)
		bfa_cb_itnim_offline(itnim->ditn);
पूर्ण

अटल व्योम
__bfa_cb_itnim_sler(व्योम *cbarg, bfa_boolean_t complete)
अणु
	काष्ठा bfa_itnim_s *itnim = cbarg;

	अगर (complete)
		bfa_cb_itnim_sler(itnim->ditn);
पूर्ण

/*
 * Call to resume any I/O requests रुकोing क्रम room in request queue.
 */
अटल व्योम
bfa_itnim_qresume(व्योम *cbarg)
अणु
	काष्ठा bfa_itnim_s *itnim = cbarg;

	bfa_sm_send_event(itnim, BFA_ITNIM_SM_QRESUME);
पूर्ण

/*
 *  bfa_itnim_खुला
 */

व्योम
bfa_itnim_ioकरोne(काष्ठा bfa_itnim_s *itnim)
अणु
	bfa_wc_करोwn(&itnim->wc);
पूर्ण

व्योम
bfa_itnim_tskकरोne(काष्ठा bfa_itnim_s *itnim)
अणु
	bfa_wc_करोwn(&itnim->wc);
पूर्ण

व्योम
bfa_itnim_meminfo(काष्ठा bfa_iocfc_cfg_s *cfg, u32 *km_len)
अणु
	/*
	 * ITN memory
	 */
	*km_len += cfg->fwcfg.num_rports * माप(काष्ठा bfa_itnim_s);
पूर्ण

व्योम
bfa_itnim_attach(काष्ठा bfa_fcpim_s *fcpim)
अणु
	काष्ठा bfa_s	*bfa = fcpim->bfa;
	काष्ठा bfa_fcp_mod_s	*fcp = fcpim->fcp;
	काष्ठा bfa_itnim_s *itnim;
	पूर्णांक	i, j;

	INIT_LIST_HEAD(&fcpim->itnim_q);

	itnim = (काष्ठा bfa_itnim_s *) bfa_mem_kva_curp(fcp);
	fcpim->itnim_arr = itnim;

	क्रम (i = 0; i < fcpim->num_itnims; i++, itnim++) अणु
		स_रखो(itnim, 0, माप(काष्ठा bfa_itnim_s));
		itnim->bfa = bfa;
		itnim->fcpim = fcpim;
		itnim->reqq = BFA_REQQ_QOS_LO;
		itnim->rport = BFA_RPORT_FROM_TAG(bfa, i);
		itnim->iotov_active = BFA_FALSE;
		bfa_reqq_winit(&itnim->reqq_रुको, bfa_itnim_qresume, itnim);

		INIT_LIST_HEAD(&itnim->io_q);
		INIT_LIST_HEAD(&itnim->io_cleanup_q);
		INIT_LIST_HEAD(&itnim->pending_q);
		INIT_LIST_HEAD(&itnim->tsk_q);
		INIT_LIST_HEAD(&itnim->delay_comp_q);
		क्रम (j = 0; j < BFA_IOBUCKET_MAX; j++)
			itnim->ioprofile.io_latency.min[j] = ~0;
		bfa_sm_set_state(itnim, bfa_itnim_sm_uninit);
	पूर्ण

	bfa_mem_kva_curp(fcp) = (u8 *) itnim;
पूर्ण

व्योम
bfa_itnim_iocdisable(काष्ठा bfa_itnim_s *itnim)
अणु
	bfa_stats(itnim, ioc_disabled);
	bfa_sm_send_event(itnim, BFA_ITNIM_SM_HWFAIL);
पूर्ण

अटल bfa_boolean_t
bfa_itnim_send_fwcreate(काष्ठा bfa_itnim_s *itnim)
अणु
	काष्ठा bfi_itn_create_req_s *m;

	itnim->msg_no++;

	/*
	 * check क्रम room in queue to send request now
	 */
	m = bfa_reqq_next(itnim->bfa, itnim->reqq);
	अगर (!m) अणु
		bfa_reqq_रुको(itnim->bfa, itnim->reqq, &itnim->reqq_रुको);
		वापस BFA_FALSE;
	पूर्ण

	bfi_h2i_set(m->mh, BFI_MC_ITN, BFI_ITN_H2I_CREATE_REQ,
			bfa_fn_lpu(itnim->bfa));
	m->fw_handle = itnim->rport->fw_handle;
	m->class = FC_CLASS_3;
	m->seq_rec = itnim->seq_rec;
	m->msg_no = itnim->msg_no;
	bfa_stats(itnim, fw_create);

	/*
	 * queue I/O message to firmware
	 */
	bfa_reqq_produce(itnim->bfa, itnim->reqq, m->mh);
	वापस BFA_TRUE;
पूर्ण

अटल bfa_boolean_t
bfa_itnim_send_fwdelete(काष्ठा bfa_itnim_s *itnim)
अणु
	काष्ठा bfi_itn_delete_req_s *m;

	/*
	 * check क्रम room in queue to send request now
	 */
	m = bfa_reqq_next(itnim->bfa, itnim->reqq);
	अगर (!m) अणु
		bfa_reqq_रुको(itnim->bfa, itnim->reqq, &itnim->reqq_रुको);
		वापस BFA_FALSE;
	पूर्ण

	bfi_h2i_set(m->mh, BFI_MC_ITN, BFI_ITN_H2I_DELETE_REQ,
			bfa_fn_lpu(itnim->bfa));
	m->fw_handle = itnim->rport->fw_handle;
	bfa_stats(itnim, fw_delete);

	/*
	 * queue I/O message to firmware
	 */
	bfa_reqq_produce(itnim->bfa, itnim->reqq, m->mh);
	वापस BFA_TRUE;
पूर्ण

/*
 * Cleanup all pending failed inflight requests.
 */
अटल व्योम
bfa_itnim_delayed_comp(काष्ठा bfa_itnim_s *itnim, bfa_boolean_t iotov)
अणु
	काष्ठा bfa_ioim_s *ioim;
	काष्ठा list_head *qe, *qen;

	list_क्रम_each_safe(qe, qen, &itnim->delay_comp_q) अणु
		ioim = (काष्ठा bfa_ioim_s *)qe;
		bfa_ioim_delayed_comp(ioim, iotov);
	पूर्ण
पूर्ण

/*
 * Start all pending IO requests.
 */
अटल व्योम
bfa_itnim_iotov_online(काष्ठा bfa_itnim_s *itnim)
अणु
	काष्ठा bfa_ioim_s *ioim;

	bfa_itnim_iotov_stop(itnim);

	/*
	 * Abort all inflight IO requests in the queue
	 */
	bfa_itnim_delayed_comp(itnim, BFA_FALSE);

	/*
	 * Start all pending IO requests.
	 */
	जबतक (!list_empty(&itnim->pending_q)) अणु
		bfa_q_deq(&itnim->pending_q, &ioim);
		list_add_tail(&ioim->qe, &itnim->io_q);
		bfa_ioim_start(ioim);
	पूर्ण
पूर्ण

/*
 * Fail all pending IO requests
 */
अटल व्योम
bfa_itnim_iotov_cleanup(काष्ठा bfa_itnim_s *itnim)
अणु
	काष्ठा bfa_ioim_s *ioim;

	/*
	 * Fail all inflight IO requests in the queue
	 */
	bfa_itnim_delayed_comp(itnim, BFA_TRUE);

	/*
	 * Fail any pending IO requests.
	 */
	जबतक (!list_empty(&itnim->pending_q)) अणु
		bfa_q_deq(&itnim->pending_q, &ioim);
		list_add_tail(&ioim->qe, &ioim->fcpim->ioim_comp_q);
		bfa_ioim_tov(ioim);
	पूर्ण
पूर्ण

/*
 * IO TOV समयr callback. Fail any pending IO requests.
 */
अटल व्योम
bfa_itnim_iotov(व्योम *itnim_arg)
अणु
	काष्ठा bfa_itnim_s *itnim = itnim_arg;

	itnim->iotov_active = BFA_FALSE;

	bfa_cb_itnim_tov_begin(itnim->ditn);
	bfa_itnim_iotov_cleanup(itnim);
	bfa_cb_itnim_tov(itnim->ditn);
पूर्ण

/*
 * Start IO TOV समयr क्रम failing back pending IO requests in offline state.
 */
अटल व्योम
bfa_itnim_iotov_start(काष्ठा bfa_itnim_s *itnim)
अणु
	अगर (itnim->fcpim->path_tov > 0) अणु

		itnim->iotov_active = BFA_TRUE;
		WARN_ON(!bfa_itnim_hold_io(itnim));
		bfa_समयr_start(itnim->bfa, &itnim->समयr,
			bfa_itnim_iotov, itnim, itnim->fcpim->path_tov);
	पूर्ण
पूर्ण

/*
 * Stop IO TOV समयr.
 */
अटल व्योम
bfa_itnim_iotov_stop(काष्ठा bfa_itnim_s *itnim)
अणु
	अगर (itnim->iotov_active) अणु
		itnim->iotov_active = BFA_FALSE;
		bfa_समयr_stop(&itnim->समयr);
	पूर्ण
पूर्ण

/*
 * Stop IO TOV समयr.
 */
अटल व्योम
bfa_itnim_iotov_delete(काष्ठा bfa_itnim_s *itnim)
अणु
	bfa_boolean_t pathtov_active = BFA_FALSE;

	अगर (itnim->iotov_active)
		pathtov_active = BFA_TRUE;

	bfa_itnim_iotov_stop(itnim);
	अगर (pathtov_active)
		bfa_cb_itnim_tov_begin(itnim->ditn);
	bfa_itnim_iotov_cleanup(itnim);
	अगर (pathtov_active)
		bfa_cb_itnim_tov(itnim->ditn);
पूर्ण

अटल व्योम
bfa_itnim_update_del_itn_stats(काष्ठा bfa_itnim_s *itnim)
अणु
	काष्ठा bfa_fcpim_s *fcpim = BFA_FCPIM(itnim->bfa);
	fcpim->del_itn_stats.del_itn_iocomp_पातed +=
		itnim->stats.iocomp_पातed;
	fcpim->del_itn_stats.del_itn_iocomp_समयकरोut +=
		itnim->stats.iocomp_समयकरोut;
	fcpim->del_itn_stats.del_itn_iocom_sqer_needed +=
		itnim->stats.iocom_sqer_needed;
	fcpim->del_itn_stats.del_itn_iocom_res_मुक्त +=
		itnim->stats.iocom_res_मुक्त;
	fcpim->del_itn_stats.del_itn_iocom_hostabrts +=
		itnim->stats.iocom_hostabrts;
	fcpim->del_itn_stats.del_itn_total_ios += itnim->stats.total_ios;
	fcpim->del_itn_stats.del_io_iocकरोwns += itnim->stats.io_iocकरोwns;
	fcpim->del_itn_stats.del_पंचांग_iocकरोwns += itnim->stats.पंचांग_iocकरोwns;
पूर्ण

/*
 * bfa_itnim_खुला
 */

/*
 * Itnim पूर्णांकerrupt processing.
 */
व्योम
bfa_itnim_isr(काष्ठा bfa_s *bfa, काष्ठा bfi_msg_s *m)
अणु
	काष्ठा bfa_fcpim_s *fcpim = BFA_FCPIM(bfa);
	जोड़ bfi_itn_i2h_msg_u msg;
	काष्ठा bfa_itnim_s *itnim;

	bfa_trc(bfa, m->mhdr.msg_id);

	msg.msg = m;

	चयन (m->mhdr.msg_id) अणु
	हाल BFI_ITN_I2H_CREATE_RSP:
		itnim = BFA_ITNIM_FROM_TAG(fcpim,
						msg.create_rsp->bfa_handle);
		WARN_ON(msg.create_rsp->status != BFA_STATUS_OK);
		bfa_stats(itnim, create_comps);
		bfa_sm_send_event(itnim, BFA_ITNIM_SM_FWRSP);
		अवरोध;

	हाल BFI_ITN_I2H_DELETE_RSP:
		itnim = BFA_ITNIM_FROM_TAG(fcpim,
						msg.delete_rsp->bfa_handle);
		WARN_ON(msg.delete_rsp->status != BFA_STATUS_OK);
		bfa_stats(itnim, delete_comps);
		bfa_sm_send_event(itnim, BFA_ITNIM_SM_FWRSP);
		अवरोध;

	हाल BFI_ITN_I2H_SLER_EVENT:
		itnim = BFA_ITNIM_FROM_TAG(fcpim,
						msg.sler_event->bfa_handle);
		bfa_stats(itnim, sler_events);
		bfa_sm_send_event(itnim, BFA_ITNIM_SM_SLER);
		अवरोध;

	शेष:
		bfa_trc(bfa, m->mhdr.msg_id);
		WARN_ON(1);
	पूर्ण
पूर्ण

/*
 * bfa_itnim_api
 */

काष्ठा bfa_itnim_s *
bfa_itnim_create(काष्ठा bfa_s *bfa, काष्ठा bfa_rport_s *rport, व्योम *ditn)
अणु
	काष्ठा bfa_fcpim_s *fcpim = BFA_FCPIM(bfa);
	काष्ठा bfa_itnim_s *itnim;

	bfa_itn_create(bfa, rport, bfa_itnim_isr);

	itnim = BFA_ITNIM_FROM_TAG(fcpim, rport->rport_tag);
	WARN_ON(itnim->rport != rport);

	itnim->ditn = ditn;

	bfa_stats(itnim, creates);
	bfa_sm_send_event(itnim, BFA_ITNIM_SM_CREATE);

	वापस itnim;
पूर्ण

व्योम
bfa_itnim_delete(काष्ठा bfa_itnim_s *itnim)
अणु
	bfa_stats(itnim, deletes);
	bfa_sm_send_event(itnim, BFA_ITNIM_SM_DELETE);
पूर्ण

व्योम
bfa_itnim_online(काष्ठा bfa_itnim_s *itnim, bfa_boolean_t seq_rec)
अणु
	itnim->seq_rec = seq_rec;
	bfa_stats(itnim, onlines);
	bfa_sm_send_event(itnim, BFA_ITNIM_SM_ONLINE);
पूर्ण

व्योम
bfa_itnim_offline(काष्ठा bfa_itnim_s *itnim)
अणु
	bfa_stats(itnim, offlines);
	bfa_sm_send_event(itnim, BFA_ITNIM_SM_OFFLINE);
पूर्ण

/*
 * Return true अगर itnim is considered offline क्रम holding off IO request.
 * IO is not held अगर itnim is being deleted.
 */
bfa_boolean_t
bfa_itnim_hold_io(काष्ठा bfa_itnim_s *itnim)
अणु
	वापस itnim->fcpim->path_tov && itnim->iotov_active &&
		(bfa_sm_cmp_state(itnim, bfa_itnim_sm_fwcreate) ||
		 bfa_sm_cmp_state(itnim, bfa_itnim_sm_sler) ||
		 bfa_sm_cmp_state(itnim, bfa_itnim_sm_cleanup_offline) ||
		 bfa_sm_cmp_state(itnim, bfa_itnim_sm_fwdelete) ||
		 bfa_sm_cmp_state(itnim, bfa_itnim_sm_offline) ||
		 bfa_sm_cmp_state(itnim, bfa_itnim_sm_iocdisable));
पूर्ण

#घोषणा bfa_io_lat_घड़ी_res_भाग	HZ
#घोषणा bfa_io_lat_घड़ी_res_mul	1000
bfa_status_t
bfa_itnim_get_ioprofile(काष्ठा bfa_itnim_s *itnim,
			काष्ठा bfa_itnim_ioprofile_s *ioprofile)
अणु
	काष्ठा bfa_fcpim_s *fcpim;

	अगर (!itnim)
		वापस BFA_STATUS_NO_FCPIM_NEXUS;

	fcpim = BFA_FCPIM(itnim->bfa);

	अगर (!fcpim->io_profile)
		वापस BFA_STATUS_IOPROखाता_OFF;

	itnim->ioprofile.index = BFA_IOBUCKET_MAX;
	/* अचिन्हित 32-bit समय_प्रकार overflow here in y2106 */
	itnim->ioprofile.io_profile_start_समय =
				bfa_io_profile_start_समय(itnim->bfa);
	itnim->ioprofile.घड़ी_res_mul = bfa_io_lat_घड़ी_res_mul;
	itnim->ioprofile.घड़ी_res_भाग = bfa_io_lat_घड़ी_res_भाग;
	*ioprofile = itnim->ioprofile;

	वापस BFA_STATUS_OK;
पूर्ण

व्योम
bfa_itnim_clear_stats(काष्ठा bfa_itnim_s *itnim)
अणु
	पूर्णांक j;

	अगर (!itnim)
		वापस;

	स_रखो(&itnim->stats, 0, माप(itnim->stats));
	स_रखो(&itnim->ioprofile, 0, माप(itnim->ioprofile));
	क्रम (j = 0; j < BFA_IOBUCKET_MAX; j++)
		itnim->ioprofile.io_latency.min[j] = ~0;
पूर्ण

/*
 *  BFA IO module state machine functions
 */

/*
 * IO is not started (unallocated).
 */
अटल व्योम
bfa_ioim_sm_uninit(काष्ठा bfa_ioim_s *ioim, क्रमागत bfa_ioim_event event)
अणु
	चयन (event) अणु
	हाल BFA_IOIM_SM_START:
		अगर (!bfa_itnim_is_online(ioim->itnim)) अणु
			अगर (!bfa_itnim_hold_io(ioim->itnim)) अणु
				bfa_sm_set_state(ioim, bfa_ioim_sm_hcb);
				list_del(&ioim->qe);
				list_add_tail(&ioim->qe,
					&ioim->fcpim->ioim_comp_q);
				bfa_cb_queue(ioim->bfa, &ioim->hcb_qe,
						__bfa_cb_ioim_pathtov, ioim);
			पूर्ण अन्यथा अणु
				list_del(&ioim->qe);
				list_add_tail(&ioim->qe,
					&ioim->itnim->pending_q);
			पूर्ण
			अवरोध;
		पूर्ण

		अगर (ioim->nsges > BFI_SGE_INLINE) अणु
			अगर (!bfa_ioim_sgpg_alloc(ioim)) अणु
				bfa_sm_set_state(ioim, bfa_ioim_sm_sgalloc);
				वापस;
			पूर्ण
		पूर्ण

		अगर (!bfa_ioim_send_ioreq(ioim)) अणु
			bfa_sm_set_state(ioim, bfa_ioim_sm_qfull);
			अवरोध;
		पूर्ण

		bfa_sm_set_state(ioim, bfa_ioim_sm_active);
		अवरोध;

	हाल BFA_IOIM_SM_IOTOV:
		bfa_sm_set_state(ioim, bfa_ioim_sm_hcb);
		bfa_ioim_move_to_comp_q(ioim);
		bfa_cb_queue(ioim->bfa, &ioim->hcb_qe,
				__bfa_cb_ioim_pathtov, ioim);
		अवरोध;

	हाल BFA_IOIM_SM_ABORT:
		/*
		 * IO in pending queue can get पात requests. Complete पात
		 * requests immediately.
		 */
		bfa_sm_set_state(ioim, bfa_ioim_sm_hcb);
		WARN_ON(!bfa_q_is_on_q(&ioim->itnim->pending_q, ioim));
		bfa_cb_queue(ioim->bfa, &ioim->hcb_qe,
			__bfa_cb_ioim_पात, ioim);
		अवरोध;

	शेष:
		bfa_sm_fault(ioim->bfa, event);
	पूर्ण
पूर्ण

/*
 * IO is रुकोing क्रम SG pages.
 */
अटल व्योम
bfa_ioim_sm_sgalloc(काष्ठा bfa_ioim_s *ioim, क्रमागत bfa_ioim_event event)
अणु
	bfa_trc(ioim->bfa, ioim->iotag);
	bfa_trc(ioim->bfa, event);

	चयन (event) अणु
	हाल BFA_IOIM_SM_SGALLOCED:
		अगर (!bfa_ioim_send_ioreq(ioim)) अणु
			bfa_sm_set_state(ioim, bfa_ioim_sm_qfull);
			अवरोध;
		पूर्ण
		bfa_sm_set_state(ioim, bfa_ioim_sm_active);
		अवरोध;

	हाल BFA_IOIM_SM_CLEANUP:
		bfa_sm_set_state(ioim, bfa_ioim_sm_hcb);
		bfa_sgpg_wcancel(ioim->bfa, &ioim->iosp->sgpg_wqe);
		bfa_cb_queue(ioim->bfa, &ioim->hcb_qe, __bfa_cb_ioim_failed,
			      ioim);
		bfa_ioim_notअगरy_cleanup(ioim);
		अवरोध;

	हाल BFA_IOIM_SM_ABORT:
		bfa_sm_set_state(ioim, bfa_ioim_sm_hcb);
		bfa_sgpg_wcancel(ioim->bfa, &ioim->iosp->sgpg_wqe);
		bfa_ioim_move_to_comp_q(ioim);
		bfa_cb_queue(ioim->bfa, &ioim->hcb_qe, __bfa_cb_ioim_पात,
			      ioim);
		अवरोध;

	हाल BFA_IOIM_SM_HWFAIL:
		bfa_sm_set_state(ioim, bfa_ioim_sm_hcb);
		bfa_sgpg_wcancel(ioim->bfa, &ioim->iosp->sgpg_wqe);
		bfa_ioim_move_to_comp_q(ioim);
		bfa_cb_queue(ioim->bfa, &ioim->hcb_qe, __bfa_cb_ioim_failed,
			      ioim);
		अवरोध;

	शेष:
		bfa_sm_fault(ioim->bfa, event);
	पूर्ण
पूर्ण

/*
 * IO is active.
 */
अटल व्योम
bfa_ioim_sm_active(काष्ठा bfa_ioim_s *ioim, क्रमागत bfa_ioim_event event)
अणु
	चयन (event) अणु
	हाल BFA_IOIM_SM_COMP_GOOD:
		bfa_sm_set_state(ioim, bfa_ioim_sm_hcb);
		bfa_ioim_move_to_comp_q(ioim);
		bfa_cb_queue(ioim->bfa, &ioim->hcb_qe,
			      __bfa_cb_ioim_good_comp, ioim);
		अवरोध;

	हाल BFA_IOIM_SM_COMP:
		bfa_sm_set_state(ioim, bfa_ioim_sm_hcb);
		bfa_ioim_move_to_comp_q(ioim);
		bfa_cb_queue(ioim->bfa, &ioim->hcb_qe, __bfa_cb_ioim_comp,
			      ioim);
		अवरोध;

	हाल BFA_IOIM_SM_DONE:
		bfa_sm_set_state(ioim, bfa_ioim_sm_hcb_मुक्त);
		bfa_ioim_move_to_comp_q(ioim);
		bfa_cb_queue(ioim->bfa, &ioim->hcb_qe, __bfa_cb_ioim_comp,
			      ioim);
		अवरोध;

	हाल BFA_IOIM_SM_ABORT:
		ioim->iosp->पात_explicit = BFA_TRUE;
		ioim->io_cbfn = __bfa_cb_ioim_पात;

		अगर (bfa_ioim_send_पात(ioim))
			bfa_sm_set_state(ioim, bfa_ioim_sm_पात);
		अन्यथा अणु
			bfa_sm_set_state(ioim, bfa_ioim_sm_पात_qfull);
			bfa_stats(ioim->itnim, qरुको);
			bfa_reqq_रुको(ioim->bfa, ioim->reqq,
					  &ioim->iosp->reqq_रुको);
		पूर्ण
		अवरोध;

	हाल BFA_IOIM_SM_CLEANUP:
		ioim->iosp->पात_explicit = BFA_FALSE;
		ioim->io_cbfn = __bfa_cb_ioim_failed;

		अगर (bfa_ioim_send_पात(ioim))
			bfa_sm_set_state(ioim, bfa_ioim_sm_cleanup);
		अन्यथा अणु
			bfa_sm_set_state(ioim, bfa_ioim_sm_cleanup_qfull);
			bfa_stats(ioim->itnim, qरुको);
			bfa_reqq_रुको(ioim->bfa, ioim->reqq,
					  &ioim->iosp->reqq_रुको);
		पूर्ण
		अवरोध;

	हाल BFA_IOIM_SM_HWFAIL:
		bfa_sm_set_state(ioim, bfa_ioim_sm_hcb);
		bfa_ioim_move_to_comp_q(ioim);
		bfa_cb_queue(ioim->bfa, &ioim->hcb_qe, __bfa_cb_ioim_failed,
			      ioim);
		अवरोध;

	हाल BFA_IOIM_SM_SQRETRY:
		अगर (bfa_ioim_maxretry_reached(ioim)) अणु
			/* max retry reached, मुक्त IO */
			bfa_sm_set_state(ioim, bfa_ioim_sm_hcb_मुक्त);
			bfa_ioim_move_to_comp_q(ioim);
			bfa_cb_queue(ioim->bfa, &ioim->hcb_qe,
					__bfa_cb_ioim_failed, ioim);
			अवरोध;
		पूर्ण
		/* रुकोing क्रम IO tag resource मुक्त */
		bfa_sm_set_state(ioim, bfa_ioim_sm_cmnd_retry);
		अवरोध;

	शेष:
		bfa_sm_fault(ioim->bfa, event);
	पूर्ण
पूर्ण

/*
 * IO is retried with new tag.
 */
अटल व्योम
bfa_ioim_sm_cmnd_retry(काष्ठा bfa_ioim_s *ioim, क्रमागत bfa_ioim_event event)
अणु
	चयन (event) अणु
	हाल BFA_IOIM_SM_FREE:
		/* abts and rrq करोne. Now retry the IO with new tag */
		bfa_ioim_update_iotag(ioim);
		अगर (!bfa_ioim_send_ioreq(ioim)) अणु
			bfa_sm_set_state(ioim, bfa_ioim_sm_qfull);
			अवरोध;
		पूर्ण
		bfa_sm_set_state(ioim, bfa_ioim_sm_active);
	अवरोध;

	हाल BFA_IOIM_SM_CLEANUP:
		ioim->iosp->पात_explicit = BFA_FALSE;
		ioim->io_cbfn = __bfa_cb_ioim_failed;

		अगर (bfa_ioim_send_पात(ioim))
			bfa_sm_set_state(ioim, bfa_ioim_sm_cleanup);
		अन्यथा अणु
			bfa_sm_set_state(ioim, bfa_ioim_sm_cleanup_qfull);
			bfa_stats(ioim->itnim, qरुको);
			bfa_reqq_रुको(ioim->bfa, ioim->reqq,
					  &ioim->iosp->reqq_रुको);
		पूर्ण
	अवरोध;

	हाल BFA_IOIM_SM_HWFAIL:
		bfa_sm_set_state(ioim, bfa_ioim_sm_hcb);
		bfa_ioim_move_to_comp_q(ioim);
		bfa_cb_queue(ioim->bfa, &ioim->hcb_qe,
			 __bfa_cb_ioim_failed, ioim);
		अवरोध;

	हाल BFA_IOIM_SM_ABORT:
		/* in this state IO पात is करोne.
		 * Waiting क्रम IO tag resource मुक्त.
		 */
		bfa_sm_set_state(ioim, bfa_ioim_sm_hcb_मुक्त);
		bfa_cb_queue(ioim->bfa, &ioim->hcb_qe, __bfa_cb_ioim_पात,
			      ioim);
		अवरोध;

	शेष:
		bfa_sm_fault(ioim->bfa, event);
	पूर्ण
पूर्ण

/*
 * IO is being पातed, रुकोing क्रम completion from firmware.
 */
अटल व्योम
bfa_ioim_sm_पात(काष्ठा bfa_ioim_s *ioim, क्रमागत bfa_ioim_event event)
अणु
	bfa_trc(ioim->bfa, ioim->iotag);
	bfa_trc(ioim->bfa, event);

	चयन (event) अणु
	हाल BFA_IOIM_SM_COMP_GOOD:
	हाल BFA_IOIM_SM_COMP:
	हाल BFA_IOIM_SM_DONE:
	हाल BFA_IOIM_SM_FREE:
		अवरोध;

	हाल BFA_IOIM_SM_ABORT_DONE:
		bfa_sm_set_state(ioim, bfa_ioim_sm_hcb_मुक्त);
		bfa_cb_queue(ioim->bfa, &ioim->hcb_qe, __bfa_cb_ioim_पात,
			      ioim);
		अवरोध;

	हाल BFA_IOIM_SM_ABORT_COMP:
		bfa_sm_set_state(ioim, bfa_ioim_sm_hcb);
		bfa_ioim_move_to_comp_q(ioim);
		bfa_cb_queue(ioim->bfa, &ioim->hcb_qe, __bfa_cb_ioim_पात,
			      ioim);
		अवरोध;

	हाल BFA_IOIM_SM_COMP_UTAG:
		bfa_sm_set_state(ioim, bfa_ioim_sm_hcb);
		bfa_ioim_move_to_comp_q(ioim);
		bfa_cb_queue(ioim->bfa, &ioim->hcb_qe, __bfa_cb_ioim_पात,
			      ioim);
		अवरोध;

	हाल BFA_IOIM_SM_CLEANUP:
		WARN_ON(ioim->iosp->पात_explicit != BFA_TRUE);
		ioim->iosp->पात_explicit = BFA_FALSE;

		अगर (bfa_ioim_send_पात(ioim))
			bfa_sm_set_state(ioim, bfa_ioim_sm_cleanup);
		अन्यथा अणु
			bfa_sm_set_state(ioim, bfa_ioim_sm_cleanup_qfull);
			bfa_stats(ioim->itnim, qरुको);
			bfa_reqq_रुको(ioim->bfa, ioim->reqq,
					  &ioim->iosp->reqq_रुको);
		पूर्ण
		अवरोध;

	हाल BFA_IOIM_SM_HWFAIL:
		bfa_sm_set_state(ioim, bfa_ioim_sm_hcb);
		bfa_ioim_move_to_comp_q(ioim);
		bfa_cb_queue(ioim->bfa, &ioim->hcb_qe, __bfa_cb_ioim_failed,
			      ioim);
		अवरोध;

	शेष:
		bfa_sm_fault(ioim->bfa, event);
	पूर्ण
पूर्ण

/*
 * IO is being cleaned up (implicit पात), रुकोing क्रम completion from
 * firmware.
 */
अटल व्योम
bfa_ioim_sm_cleanup(काष्ठा bfa_ioim_s *ioim, क्रमागत bfa_ioim_event event)
अणु
	bfa_trc(ioim->bfa, ioim->iotag);
	bfa_trc(ioim->bfa, event);

	चयन (event) अणु
	हाल BFA_IOIM_SM_COMP_GOOD:
	हाल BFA_IOIM_SM_COMP:
	हाल BFA_IOIM_SM_DONE:
	हाल BFA_IOIM_SM_FREE:
		अवरोध;

	हाल BFA_IOIM_SM_ABORT:
		/*
		 * IO is alपढ़ोy being पातed implicitly
		 */
		ioim->io_cbfn = __bfa_cb_ioim_पात;
		अवरोध;

	हाल BFA_IOIM_SM_ABORT_DONE:
		bfa_sm_set_state(ioim, bfa_ioim_sm_hcb_मुक्त);
		bfa_cb_queue(ioim->bfa, &ioim->hcb_qe, ioim->io_cbfn, ioim);
		bfa_ioim_notअगरy_cleanup(ioim);
		अवरोध;

	हाल BFA_IOIM_SM_ABORT_COMP:
		bfa_sm_set_state(ioim, bfa_ioim_sm_hcb);
		bfa_cb_queue(ioim->bfa, &ioim->hcb_qe, ioim->io_cbfn, ioim);
		bfa_ioim_notअगरy_cleanup(ioim);
		अवरोध;

	हाल BFA_IOIM_SM_COMP_UTAG:
		bfa_sm_set_state(ioim, bfa_ioim_sm_hcb);
		bfa_cb_queue(ioim->bfa, &ioim->hcb_qe, ioim->io_cbfn, ioim);
		bfa_ioim_notअगरy_cleanup(ioim);
		अवरोध;

	हाल BFA_IOIM_SM_HWFAIL:
		bfa_sm_set_state(ioim, bfa_ioim_sm_hcb);
		bfa_ioim_move_to_comp_q(ioim);
		bfa_cb_queue(ioim->bfa, &ioim->hcb_qe, __bfa_cb_ioim_failed,
			      ioim);
		अवरोध;

	हाल BFA_IOIM_SM_CLEANUP:
		/*
		 * IO can be in cleanup state alपढ़ोy due to TM command.
		 * 2nd cleanup request comes from ITN offline event.
		 */
		अवरोध;

	शेष:
		bfa_sm_fault(ioim->bfa, event);
	पूर्ण
पूर्ण

/*
 * IO is रुकोing क्रम room in request CQ
 */
अटल व्योम
bfa_ioim_sm_qfull(काष्ठा bfa_ioim_s *ioim, क्रमागत bfa_ioim_event event)
अणु
	bfa_trc(ioim->bfa, ioim->iotag);
	bfa_trc(ioim->bfa, event);

	चयन (event) अणु
	हाल BFA_IOIM_SM_QRESUME:
		bfa_sm_set_state(ioim, bfa_ioim_sm_active);
		bfa_ioim_send_ioreq(ioim);
		अवरोध;

	हाल BFA_IOIM_SM_ABORT:
		bfa_sm_set_state(ioim, bfa_ioim_sm_hcb);
		bfa_reqq_wcancel(&ioim->iosp->reqq_रुको);
		bfa_ioim_move_to_comp_q(ioim);
		bfa_cb_queue(ioim->bfa, &ioim->hcb_qe, __bfa_cb_ioim_पात,
			      ioim);
		अवरोध;

	हाल BFA_IOIM_SM_CLEANUP:
		bfa_sm_set_state(ioim, bfa_ioim_sm_hcb);
		bfa_reqq_wcancel(&ioim->iosp->reqq_रुको);
		bfa_cb_queue(ioim->bfa, &ioim->hcb_qe, __bfa_cb_ioim_failed,
			      ioim);
		bfa_ioim_notअगरy_cleanup(ioim);
		अवरोध;

	हाल BFA_IOIM_SM_HWFAIL:
		bfa_sm_set_state(ioim, bfa_ioim_sm_hcb);
		bfa_reqq_wcancel(&ioim->iosp->reqq_रुको);
		bfa_ioim_move_to_comp_q(ioim);
		bfa_cb_queue(ioim->bfa, &ioim->hcb_qe, __bfa_cb_ioim_failed,
			      ioim);
		अवरोध;

	शेष:
		bfa_sm_fault(ioim->bfa, event);
	पूर्ण
पूर्ण

/*
 * Active IO is being पातed, रुकोing क्रम room in request CQ.
 */
अटल व्योम
bfa_ioim_sm_पात_qfull(काष्ठा bfa_ioim_s *ioim, क्रमागत bfa_ioim_event event)
अणु
	bfa_trc(ioim->bfa, ioim->iotag);
	bfa_trc(ioim->bfa, event);

	चयन (event) अणु
	हाल BFA_IOIM_SM_QRESUME:
		bfa_sm_set_state(ioim, bfa_ioim_sm_पात);
		bfa_ioim_send_पात(ioim);
		अवरोध;

	हाल BFA_IOIM_SM_CLEANUP:
		WARN_ON(ioim->iosp->पात_explicit != BFA_TRUE);
		ioim->iosp->पात_explicit = BFA_FALSE;
		bfa_sm_set_state(ioim, bfa_ioim_sm_cleanup_qfull);
		अवरोध;

	हाल BFA_IOIM_SM_COMP_GOOD:
	हाल BFA_IOIM_SM_COMP:
		bfa_sm_set_state(ioim, bfa_ioim_sm_hcb);
		bfa_reqq_wcancel(&ioim->iosp->reqq_रुको);
		bfa_ioim_move_to_comp_q(ioim);
		bfa_cb_queue(ioim->bfa, &ioim->hcb_qe, __bfa_cb_ioim_पात,
			      ioim);
		अवरोध;

	हाल BFA_IOIM_SM_DONE:
		bfa_sm_set_state(ioim, bfa_ioim_sm_hcb_मुक्त);
		bfa_reqq_wcancel(&ioim->iosp->reqq_रुको);
		bfa_ioim_move_to_comp_q(ioim);
		bfa_cb_queue(ioim->bfa, &ioim->hcb_qe, __bfa_cb_ioim_पात,
			      ioim);
		अवरोध;

	हाल BFA_IOIM_SM_HWFAIL:
		bfa_sm_set_state(ioim, bfa_ioim_sm_hcb);
		bfa_reqq_wcancel(&ioim->iosp->reqq_रुको);
		bfa_ioim_move_to_comp_q(ioim);
		bfa_cb_queue(ioim->bfa, &ioim->hcb_qe, __bfa_cb_ioim_failed,
			      ioim);
		अवरोध;

	शेष:
		bfa_sm_fault(ioim->bfa, event);
	पूर्ण
पूर्ण

/*
 * Active IO is being cleaned up, रुकोing क्रम room in request CQ.
 */
अटल व्योम
bfa_ioim_sm_cleanup_qfull(काष्ठा bfa_ioim_s *ioim, क्रमागत bfa_ioim_event event)
अणु
	bfa_trc(ioim->bfa, ioim->iotag);
	bfa_trc(ioim->bfa, event);

	चयन (event) अणु
	हाल BFA_IOIM_SM_QRESUME:
		bfa_sm_set_state(ioim, bfa_ioim_sm_cleanup);
		bfa_ioim_send_पात(ioim);
		अवरोध;

	हाल BFA_IOIM_SM_ABORT:
		/*
		 * IO is alपढ़ोy being cleaned up implicitly
		 */
		ioim->io_cbfn = __bfa_cb_ioim_पात;
		अवरोध;

	हाल BFA_IOIM_SM_COMP_GOOD:
	हाल BFA_IOIM_SM_COMP:
		bfa_sm_set_state(ioim, bfa_ioim_sm_hcb);
		bfa_reqq_wcancel(&ioim->iosp->reqq_रुको);
		bfa_cb_queue(ioim->bfa, &ioim->hcb_qe, ioim->io_cbfn, ioim);
		bfa_ioim_notअगरy_cleanup(ioim);
		अवरोध;

	हाल BFA_IOIM_SM_DONE:
		bfa_sm_set_state(ioim, bfa_ioim_sm_hcb_मुक्त);
		bfa_reqq_wcancel(&ioim->iosp->reqq_रुको);
		bfa_cb_queue(ioim->bfa, &ioim->hcb_qe, ioim->io_cbfn, ioim);
		bfa_ioim_notअगरy_cleanup(ioim);
		अवरोध;

	हाल BFA_IOIM_SM_HWFAIL:
		bfa_sm_set_state(ioim, bfa_ioim_sm_hcb);
		bfa_reqq_wcancel(&ioim->iosp->reqq_रुको);
		bfa_ioim_move_to_comp_q(ioim);
		bfa_cb_queue(ioim->bfa, &ioim->hcb_qe, __bfa_cb_ioim_failed,
			      ioim);
		अवरोध;

	शेष:
		bfa_sm_fault(ioim->bfa, event);
	पूर्ण
पूर्ण

/*
 * IO bfa callback is pending.
 */
अटल व्योम
bfa_ioim_sm_hcb(काष्ठा bfa_ioim_s *ioim, क्रमागत bfa_ioim_event event)
अणु
	चयन (event) अणु
	हाल BFA_IOIM_SM_HCB:
		bfa_sm_set_state(ioim, bfa_ioim_sm_uninit);
		bfa_ioim_मुक्त(ioim);
		अवरोध;

	हाल BFA_IOIM_SM_CLEANUP:
		bfa_ioim_notअगरy_cleanup(ioim);
		अवरोध;

	हाल BFA_IOIM_SM_HWFAIL:
		अवरोध;

	शेष:
		bfa_sm_fault(ioim->bfa, event);
	पूर्ण
पूर्ण

/*
 * IO bfa callback is pending. IO resource cannot be मुक्तd.
 */
अटल व्योम
bfa_ioim_sm_hcb_मुक्त(काष्ठा bfa_ioim_s *ioim, क्रमागत bfa_ioim_event event)
अणु
	bfa_trc(ioim->bfa, ioim->iotag);
	bfa_trc(ioim->bfa, event);

	चयन (event) अणु
	हाल BFA_IOIM_SM_HCB:
		bfa_sm_set_state(ioim, bfa_ioim_sm_resमुक्त);
		list_del(&ioim->qe);
		list_add_tail(&ioim->qe, &ioim->fcpim->ioim_resमुक्त_q);
		अवरोध;

	हाल BFA_IOIM_SM_FREE:
		bfa_sm_set_state(ioim, bfa_ioim_sm_hcb);
		अवरोध;

	हाल BFA_IOIM_SM_CLEANUP:
		bfa_ioim_notअगरy_cleanup(ioim);
		अवरोध;

	हाल BFA_IOIM_SM_HWFAIL:
		bfa_sm_set_state(ioim, bfa_ioim_sm_hcb);
		अवरोध;

	शेष:
		bfa_sm_fault(ioim->bfa, event);
	पूर्ण
पूर्ण

/*
 * IO is completed, रुकोing resource मुक्त from firmware.
 */
अटल व्योम
bfa_ioim_sm_resमुक्त(काष्ठा bfa_ioim_s *ioim, क्रमागत bfa_ioim_event event)
अणु
	bfa_trc(ioim->bfa, ioim->iotag);
	bfa_trc(ioim->bfa, event);

	चयन (event) अणु
	हाल BFA_IOIM_SM_FREE:
		bfa_sm_set_state(ioim, bfa_ioim_sm_uninit);
		bfa_ioim_मुक्त(ioim);
		अवरोध;

	हाल BFA_IOIM_SM_CLEANUP:
		bfa_ioim_notअगरy_cleanup(ioim);
		अवरोध;

	हाल BFA_IOIM_SM_HWFAIL:
		अवरोध;

	शेष:
		bfa_sm_fault(ioim->bfa, event);
	पूर्ण
पूर्ण

/*
 * This is called from bfa_fcpim_start after the bfa_init() with flash पढ़ो
 * is complete by driver. now invalidate the stale content of lun mask
 * like unit attention, rp tag and lp tag.
 */
व्योम
bfa_ioim_lm_init(काष्ठा bfa_s *bfa)
अणु
	काष्ठा bfa_lun_mask_s *lunm_list;
	पूर्णांक	i;

	अगर (bfa_get_lun_mask_status(bfa) == BFA_LUNMASK_MINCFG)
		वापस;

	lunm_list = bfa_get_lun_mask_list(bfa);
	क्रम (i = 0; i < MAX_LUN_MASK_CFG; i++) अणु
		lunm_list[i].ua = BFA_IOIM_LM_UA_RESET;
		lunm_list[i].lp_tag = BFA_LP_TAG_INVALID;
		lunm_list[i].rp_tag = BFA_RPORT_TAG_INVALID;
	पूर्ण
पूर्ण

अटल व्योम
__bfa_cb_ioim_good_comp(व्योम *cbarg, bfa_boolean_t complete)
अणु
	काष्ठा bfa_ioim_s *ioim = cbarg;

	अगर (!complete) अणु
		bfa_sm_send_event(ioim, BFA_IOIM_SM_HCB);
		वापस;
	पूर्ण

	bfa_cb_ioim_good_comp(ioim->bfa->bfad, ioim->dio);
पूर्ण

अटल व्योम
__bfa_cb_ioim_comp(व्योम *cbarg, bfa_boolean_t complete)
अणु
	काष्ठा bfa_ioim_s	*ioim = cbarg;
	काष्ठा bfi_ioim_rsp_s *m;
	u8	*snsinfo = शून्य;
	u8	sns_len = 0;
	s32	residue = 0;

	अगर (!complete) अणु
		bfa_sm_send_event(ioim, BFA_IOIM_SM_HCB);
		वापस;
	पूर्ण

	m = (काष्ठा bfi_ioim_rsp_s *) &ioim->iosp->comp_rspmsg;
	अगर (m->io_status == BFI_IOIM_STS_OK) अणु
		/*
		 * setup sense inक्रमmation, अगर present
		 */
		अगर ((m->scsi_status == SAM_STAT_CHECK_CONDITION) &&
					m->sns_len) अणु
			sns_len = m->sns_len;
			snsinfo = BFA_SNSINFO_FROM_TAG(ioim->fcpim->fcp,
						ioim->iotag);
		पूर्ण

		/*
		 * setup residue value correctly क्रम normal completions
		 */
		अगर (m->resid_flags == FCP_RESID_UNDER) अणु
			residue = be32_to_cpu(m->residue);
			bfa_stats(ioim->itnim, iocomp_underrun);
		पूर्ण
		अगर (m->resid_flags == FCP_RESID_OVER) अणु
			residue = be32_to_cpu(m->residue);
			residue = -residue;
			bfa_stats(ioim->itnim, iocomp_overrun);
		पूर्ण
	पूर्ण

	bfa_cb_ioim_करोne(ioim->bfa->bfad, ioim->dio, m->io_status,
			  m->scsi_status, sns_len, snsinfo, residue);
पूर्ण

व्योम
bfa_fcpim_lunmask_rp_update(काष्ठा bfa_s *bfa, wwn_t lp_wwn, wwn_t rp_wwn,
			u16 rp_tag, u8 lp_tag)
अणु
	काष्ठा bfa_lun_mask_s *lun_list;
	u8	i;

	अगर (bfa_get_lun_mask_status(bfa) == BFA_LUNMASK_MINCFG)
		वापस;

	lun_list = bfa_get_lun_mask_list(bfa);
	क्रम (i = 0; i < MAX_LUN_MASK_CFG; i++) अणु
		अगर (lun_list[i].state == BFA_IOIM_LUN_MASK_ACTIVE) अणु
			अगर ((lun_list[i].lp_wwn == lp_wwn) &&
			    (lun_list[i].rp_wwn == rp_wwn)) अणु
				lun_list[i].rp_tag = rp_tag;
				lun_list[i].lp_tag = lp_tag;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

/*
 * set UA क्रम all active luns in LM DB
 */
अटल व्योम
bfa_ioim_lm_set_ua(काष्ठा bfa_s *bfa)
अणु
	काष्ठा bfa_lun_mask_s	*lunm_list;
	पूर्णांक	i;

	lunm_list = bfa_get_lun_mask_list(bfa);
	क्रम (i = 0; i < MAX_LUN_MASK_CFG; i++) अणु
		अगर (lunm_list[i].state != BFA_IOIM_LUN_MASK_ACTIVE)
			जारी;
		lunm_list[i].ua = BFA_IOIM_LM_UA_SET;
	पूर्ण
पूर्ण

bfa_status_t
bfa_fcpim_lunmask_update(काष्ठा bfa_s *bfa, u32 update)
अणु
	काष्ठा bfa_lunmask_cfg_s	*lun_mask;

	bfa_trc(bfa, bfa_get_lun_mask_status(bfa));
	अगर (bfa_get_lun_mask_status(bfa) == BFA_LUNMASK_MINCFG)
		वापस BFA_STATUS_FAILED;

	अगर (bfa_get_lun_mask_status(bfa) == update)
		वापस BFA_STATUS_NO_CHANGE;

	lun_mask = bfa_get_lun_mask(bfa);
	lun_mask->status = update;

	अगर (bfa_get_lun_mask_status(bfa) == BFA_LUNMASK_ENABLED)
		bfa_ioim_lm_set_ua(bfa);

	वापस  bfa_dconf_update(bfa);
पूर्ण

bfa_status_t
bfa_fcpim_lunmask_clear(काष्ठा bfa_s *bfa)
अणु
	पूर्णांक i;
	काष्ठा bfa_lun_mask_s	*lunm_list;

	bfa_trc(bfa, bfa_get_lun_mask_status(bfa));
	अगर (bfa_get_lun_mask_status(bfa) == BFA_LUNMASK_MINCFG)
		वापस BFA_STATUS_FAILED;

	lunm_list = bfa_get_lun_mask_list(bfa);
	क्रम (i = 0; i < MAX_LUN_MASK_CFG; i++) अणु
		अगर (lunm_list[i].state == BFA_IOIM_LUN_MASK_ACTIVE) अणु
			अगर (lunm_list[i].rp_tag != BFA_RPORT_TAG_INVALID)
				bfa_rport_unset_lunmask(bfa,
				  BFA_RPORT_FROM_TAG(bfa, lunm_list[i].rp_tag));
		पूर्ण
	पूर्ण

	स_रखो(lunm_list, 0, माप(काष्ठा bfa_lun_mask_s) * MAX_LUN_MASK_CFG);
	वापस bfa_dconf_update(bfa);
पूर्ण

bfa_status_t
bfa_fcpim_lunmask_query(काष्ठा bfa_s *bfa, व्योम *buf)
अणु
	काष्ठा bfa_lunmask_cfg_s *lun_mask;

	bfa_trc(bfa, bfa_get_lun_mask_status(bfa));
	अगर (bfa_get_lun_mask_status(bfa) == BFA_LUNMASK_MINCFG)
		वापस BFA_STATUS_FAILED;

	lun_mask = bfa_get_lun_mask(bfa);
	स_नकल(buf, lun_mask, माप(काष्ठा bfa_lunmask_cfg_s));
	वापस BFA_STATUS_OK;
पूर्ण

bfa_status_t
bfa_fcpim_lunmask_add(काष्ठा bfa_s *bfa, u16 vf_id, wwn_t *pwwn,
		      wwn_t rpwwn, काष्ठा scsi_lun lun)
अणु
	काष्ठा bfa_lun_mask_s *lunm_list;
	काष्ठा bfa_rport_s *rp = शून्य;
	पूर्णांक i, मुक्त_index = MAX_LUN_MASK_CFG + 1;
	काष्ठा bfa_fcs_lport_s *port = शून्य;
	काष्ठा bfa_fcs_rport_s *rp_fcs;

	bfa_trc(bfa, bfa_get_lun_mask_status(bfa));
	अगर (bfa_get_lun_mask_status(bfa) == BFA_LUNMASK_MINCFG)
		वापस BFA_STATUS_FAILED;

	port = bfa_fcs_lookup_port(&((काष्ठा bfad_s *)bfa->bfad)->bfa_fcs,
				   vf_id, *pwwn);
	अगर (port) अणु
		*pwwn = port->port_cfg.pwwn;
		rp_fcs = bfa_fcs_lport_get_rport_by_pwwn(port, rpwwn);
		अगर (rp_fcs)
			rp = rp_fcs->bfa_rport;
	पूर्ण

	lunm_list = bfa_get_lun_mask_list(bfa);
	/* अगर entry exists */
	क्रम (i = 0; i < MAX_LUN_MASK_CFG; i++) अणु
		अगर (lunm_list[i].state != BFA_IOIM_LUN_MASK_ACTIVE)
			मुक्त_index = i;
		अगर ((lunm_list[i].lp_wwn == *pwwn) &&
		    (lunm_list[i].rp_wwn == rpwwn) &&
		    (scsilun_to_पूर्णांक((काष्ठा scsi_lun *)&lunm_list[i].lun) ==
		     scsilun_to_पूर्णांक((काष्ठा scsi_lun *)&lun)))
			वापस  BFA_STATUS_ENTRY_EXISTS;
	पूर्ण

	अगर (मुक्त_index > MAX_LUN_MASK_CFG)
		वापस BFA_STATUS_MAX_ENTRY_REACHED;

	अगर (rp) अणु
		lunm_list[मुक्त_index].lp_tag = bfa_lps_get_tag_from_pid(bfa,
						   rp->rport_info.local_pid);
		lunm_list[मुक्त_index].rp_tag = rp->rport_tag;
	पूर्ण अन्यथा अणु
		lunm_list[मुक्त_index].lp_tag = BFA_LP_TAG_INVALID;
		lunm_list[मुक्त_index].rp_tag = BFA_RPORT_TAG_INVALID;
	पूर्ण

	lunm_list[मुक्त_index].lp_wwn = *pwwn;
	lunm_list[मुक्त_index].rp_wwn = rpwwn;
	lunm_list[मुक्त_index].lun = lun;
	lunm_list[मुक्त_index].state = BFA_IOIM_LUN_MASK_ACTIVE;

	/* set क्रम all luns in this rp */
	क्रम (i = 0; i < MAX_LUN_MASK_CFG; i++) अणु
		अगर ((lunm_list[i].lp_wwn == *pwwn) &&
		    (lunm_list[i].rp_wwn == rpwwn))
			lunm_list[i].ua = BFA_IOIM_LM_UA_SET;
	पूर्ण

	वापस bfa_dconf_update(bfa);
पूर्ण

bfa_status_t
bfa_fcpim_lunmask_delete(काष्ठा bfa_s *bfa, u16 vf_id, wwn_t *pwwn,
			 wwn_t rpwwn, काष्ठा scsi_lun lun)
अणु
	काष्ठा bfa_lun_mask_s	*lunm_list;
	काष्ठा bfa_fcs_lport_s *port = शून्य;
	पूर्णांक	i;

	/* in min cfg lunm_list could be शून्य but  no commands should run. */
	अगर (bfa_get_lun_mask_status(bfa) == BFA_LUNMASK_MINCFG)
		वापस BFA_STATUS_FAILED;

	bfa_trc(bfa, bfa_get_lun_mask_status(bfa));
	bfa_trc(bfa, *pwwn);
	bfa_trc(bfa, rpwwn);
	bfa_trc(bfa, scsilun_to_पूर्णांक((काष्ठा scsi_lun *)&lun));

	अगर (*pwwn == 0) अणु
		port = bfa_fcs_lookup_port(
				&((काष्ठा bfad_s *)bfa->bfad)->bfa_fcs,
				vf_id, *pwwn);
		अगर (port)
			*pwwn = port->port_cfg.pwwn;
	पूर्ण

	lunm_list = bfa_get_lun_mask_list(bfa);
	क्रम (i = 0; i < MAX_LUN_MASK_CFG; i++) अणु
		अगर ((lunm_list[i].lp_wwn == *pwwn) &&
		    (lunm_list[i].rp_wwn == rpwwn) &&
		    (scsilun_to_पूर्णांक((काष्ठा scsi_lun *)&lunm_list[i].lun) ==
		     scsilun_to_पूर्णांक((काष्ठा scsi_lun *)&lun))) अणु
			lunm_list[i].lp_wwn = 0;
			lunm_list[i].rp_wwn = 0;
			पूर्णांक_to_scsilun(0, &lunm_list[i].lun);
			lunm_list[i].state = BFA_IOIM_LUN_MASK_INACTIVE;
			अगर (lunm_list[i].rp_tag != BFA_RPORT_TAG_INVALID) अणु
				lunm_list[i].rp_tag = BFA_RPORT_TAG_INVALID;
				lunm_list[i].lp_tag = BFA_LP_TAG_INVALID;
			पूर्ण
			वापस bfa_dconf_update(bfa);
		पूर्ण
	पूर्ण

	/* set क्रम all luns in this rp */
	क्रम (i = 0; i < MAX_LUN_MASK_CFG; i++) अणु
		अगर ((lunm_list[i].lp_wwn == *pwwn) &&
		    (lunm_list[i].rp_wwn == rpwwn))
			lunm_list[i].ua = BFA_IOIM_LM_UA_SET;
	पूर्ण

	वापस BFA_STATUS_ENTRY_NOT_EXISTS;
पूर्ण

अटल व्योम
__bfa_cb_ioim_failed(व्योम *cbarg, bfa_boolean_t complete)
अणु
	काष्ठा bfa_ioim_s *ioim = cbarg;

	अगर (!complete) अणु
		bfa_sm_send_event(ioim, BFA_IOIM_SM_HCB);
		वापस;
	पूर्ण

	bfa_cb_ioim_करोne(ioim->bfa->bfad, ioim->dio, BFI_IOIM_STS_ABORTED,
			  0, 0, शून्य, 0);
पूर्ण

अटल व्योम
__bfa_cb_ioim_pathtov(व्योम *cbarg, bfa_boolean_t complete)
अणु
	काष्ठा bfa_ioim_s *ioim = cbarg;

	bfa_stats(ioim->itnim, path_tov_expired);
	अगर (!complete) अणु
		bfa_sm_send_event(ioim, BFA_IOIM_SM_HCB);
		वापस;
	पूर्ण

	bfa_cb_ioim_करोne(ioim->bfa->bfad, ioim->dio, BFI_IOIM_STS_PATHTOV,
			  0, 0, शून्य, 0);
पूर्ण

अटल व्योम
__bfa_cb_ioim_पात(व्योम *cbarg, bfa_boolean_t complete)
अणु
	काष्ठा bfa_ioim_s *ioim = cbarg;

	अगर (!complete) अणु
		bfa_sm_send_event(ioim, BFA_IOIM_SM_HCB);
		वापस;
	पूर्ण

	bfa_cb_ioim_पात(ioim->bfa->bfad, ioim->dio);
पूर्ण

अटल व्योम
bfa_ioim_sgpg_alloced(व्योम *cbarg)
अणु
	काष्ठा bfa_ioim_s *ioim = cbarg;

	ioim->nsgpgs = BFA_SGPG_NPAGE(ioim->nsges);
	list_splice_tail_init(&ioim->iosp->sgpg_wqe.sgpg_q, &ioim->sgpg_q);
	ioim->sgpg = bfa_q_first(&ioim->sgpg_q);
	bfa_sm_send_event(ioim, BFA_IOIM_SM_SGALLOCED);
पूर्ण

/*
 * Send I/O request to firmware.
 */
अटल	bfa_boolean_t
bfa_ioim_send_ioreq(काष्ठा bfa_ioim_s *ioim)
अणु
	काष्ठा bfa_itnim_s *itnim = ioim->itnim;
	काष्ठा bfi_ioim_req_s *m;
	अटल काष्ठा fcp_cmnd_s cmnd_z0 = अणु अणु अणु 0 पूर्ण पूर्ण पूर्ण;
	काष्ठा bfi_sge_s *sge, *sgpge;
	u32	pgdlen = 0;
	u32	fcp_dl;
	u64 addr;
	काष्ठा scatterlist *sg;
	काष्ठा bfa_sgpg_s *sgpg;
	काष्ठा scsi_cmnd *cmnd = (काष्ठा scsi_cmnd *) ioim->dio;
	u32 i, sge_id, pgcumsz;
	क्रमागत dma_data_direction dmadir;

	/*
	 * check क्रम room in queue to send request now
	 */
	m = bfa_reqq_next(ioim->bfa, ioim->reqq);
	अगर (!m) अणु
		bfa_stats(ioim->itnim, qरुको);
		bfa_reqq_रुको(ioim->bfa, ioim->reqq,
				  &ioim->iosp->reqq_रुको);
		वापस BFA_FALSE;
	पूर्ण

	/*
	 * build i/o request message next
	 */
	m->io_tag = cpu_to_be16(ioim->iotag);
	m->rport_hdl = ioim->itnim->rport->fw_handle;
	m->io_समयout = 0;

	sge = &m->sges[0];
	sgpg = ioim->sgpg;
	sge_id = 0;
	sgpge = शून्य;
	pgcumsz = 0;
	scsi_क्रम_each_sg(cmnd, sg, ioim->nsges, i) अणु
		अगर (i == 0) अणु
			/* build अंतरभूत IO SG element */
			addr = bfa_sgaddr_le(sg_dma_address(sg));
			sge->sga = *(जोड़ bfi_addr_u *) &addr;
			pgdlen = sg_dma_len(sg);
			sge->sg_len = pgdlen;
			sge->flags = (ioim->nsges > BFI_SGE_INLINE) ?
					BFI_SGE_DATA_CPL : BFI_SGE_DATA_LAST;
			bfa_sge_to_be(sge);
			sge++;
		पूर्ण अन्यथा अणु
			अगर (sge_id == 0)
				sgpge = sgpg->sgpg->sges;

			addr = bfa_sgaddr_le(sg_dma_address(sg));
			sgpge->sga = *(जोड़ bfi_addr_u *) &addr;
			sgpge->sg_len = sg_dma_len(sg);
			pgcumsz += sgpge->sg_len;

			/* set flags */
			अगर (i < (ioim->nsges - 1) &&
					sge_id < (BFI_SGPG_DATA_SGES - 1))
				sgpge->flags = BFI_SGE_DATA;
			अन्यथा अगर (i < (ioim->nsges - 1))
				sgpge->flags = BFI_SGE_DATA_CPL;
			अन्यथा
				sgpge->flags = BFI_SGE_DATA_LAST;

			bfa_sge_to_le(sgpge);

			sgpge++;
			अगर (i == (ioim->nsges - 1)) अणु
				sgpge->flags = BFI_SGE_PGDLEN;
				sgpge->sga.a32.addr_lo = 0;
				sgpge->sga.a32.addr_hi = 0;
				sgpge->sg_len = pgcumsz;
				bfa_sge_to_le(sgpge);
			पूर्ण अन्यथा अगर (++sge_id == BFI_SGPG_DATA_SGES) अणु
				sgpg = (काष्ठा bfa_sgpg_s *) bfa_q_next(sgpg);
				sgpge->flags = BFI_SGE_LINK;
				sgpge->sga = sgpg->sgpg_pa;
				sgpge->sg_len = pgcumsz;
				bfa_sge_to_le(sgpge);
				sge_id = 0;
				pgcumsz = 0;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (ioim->nsges > BFI_SGE_INLINE) अणु
		sge->sga = ioim->sgpg->sgpg_pa;
	पूर्ण अन्यथा अणु
		sge->sga.a32.addr_lo = 0;
		sge->sga.a32.addr_hi = 0;
	पूर्ण
	sge->sg_len = pgdlen;
	sge->flags = BFI_SGE_PGDLEN;
	bfa_sge_to_be(sge);

	/*
	 * set up I/O command parameters
	 */
	m->cmnd = cmnd_z0;
	पूर्णांक_to_scsilun(cmnd->device->lun, &m->cmnd.lun);
	dmadir = cmnd->sc_data_direction;
	अगर (dmadir == DMA_TO_DEVICE)
		m->cmnd.iodir = FCP_IOसूची_WRITE;
	अन्यथा अगर (dmadir == DMA_FROM_DEVICE)
		m->cmnd.iodir = FCP_IOसूची_READ;
	अन्यथा
		m->cmnd.iodir = FCP_IOसूची_NONE;

	m->cmnd.cdb = *(काष्ठा scsi_cdb_s *) cmnd->cmnd;
	fcp_dl = scsi_bufflen(cmnd);
	m->cmnd.fcp_dl = cpu_to_be32(fcp_dl);

	/*
	 * set up I/O message header
	 */
	चयन (m->cmnd.iodir) अणु
	हाल FCP_IOसूची_READ:
		bfi_h2i_set(m->mh, BFI_MC_IOIM_READ, 0, bfa_fn_lpu(ioim->bfa));
		bfa_stats(itnim, input_reqs);
		ioim->itnim->stats.rd_throughput += fcp_dl;
		अवरोध;
	हाल FCP_IOसूची_WRITE:
		bfi_h2i_set(m->mh, BFI_MC_IOIM_WRITE, 0, bfa_fn_lpu(ioim->bfa));
		bfa_stats(itnim, output_reqs);
		ioim->itnim->stats.wr_throughput += fcp_dl;
		अवरोध;
	हाल FCP_IOसूची_RW:
		bfa_stats(itnim, input_reqs);
		bfa_stats(itnim, output_reqs);
		fallthrough;
	शेष:
		bfi_h2i_set(m->mh, BFI_MC_IOIM_IO, 0, bfa_fn_lpu(ioim->bfa));
	पूर्ण
	अगर (itnim->seq_rec ||
	    (scsi_bufflen(cmnd) & (माप(u32) - 1)))
		bfi_h2i_set(m->mh, BFI_MC_IOIM_IO, 0, bfa_fn_lpu(ioim->bfa));

	/*
	 * queue I/O message to firmware
	 */
	bfa_reqq_produce(ioim->bfa, ioim->reqq, m->mh);
	वापस BFA_TRUE;
पूर्ण

/*
 * Setup any additional SG pages needed.Inline SG element is setup
 * at queuing समय.
 */
अटल bfa_boolean_t
bfa_ioim_sgpg_alloc(काष्ठा bfa_ioim_s *ioim)
अणु
	u16	nsgpgs;

	WARN_ON(ioim->nsges <= BFI_SGE_INLINE);

	/*
	 * allocate SG pages needed
	 */
	nsgpgs = BFA_SGPG_NPAGE(ioim->nsges);
	अगर (!nsgpgs)
		वापस BFA_TRUE;

	अगर (bfa_sgpg_दो_स्मृति(ioim->bfa, &ioim->sgpg_q, nsgpgs)
	    != BFA_STATUS_OK) अणु
		bfa_sgpg_रुको(ioim->bfa, &ioim->iosp->sgpg_wqe, nsgpgs);
		वापस BFA_FALSE;
	पूर्ण

	ioim->nsgpgs = nsgpgs;
	ioim->sgpg = bfa_q_first(&ioim->sgpg_q);

	वापस BFA_TRUE;
पूर्ण

/*
 * Send I/O पात request to firmware.
 */
अटल	bfa_boolean_t
bfa_ioim_send_पात(काष्ठा bfa_ioim_s *ioim)
अणु
	काष्ठा bfi_ioim_पात_req_s *m;
	क्रमागत bfi_ioim_h2i	msgop;

	/*
	 * check क्रम room in queue to send request now
	 */
	m = bfa_reqq_next(ioim->bfa, ioim->reqq);
	अगर (!m)
		वापस BFA_FALSE;

	/*
	 * build i/o request message next
	 */
	अगर (ioim->iosp->पात_explicit)
		msgop = BFI_IOIM_H2I_IOABORT_REQ;
	अन्यथा
		msgop = BFI_IOIM_H2I_IOCLEANUP_REQ;

	bfi_h2i_set(m->mh, BFI_MC_IOIM, msgop, bfa_fn_lpu(ioim->bfa));
	m->io_tag    = cpu_to_be16(ioim->iotag);
	m->पात_tag = ++ioim->पात_tag;

	/*
	 * queue I/O message to firmware
	 */
	bfa_reqq_produce(ioim->bfa, ioim->reqq, m->mh);
	वापस BFA_TRUE;
पूर्ण

/*
 * Call to resume any I/O requests रुकोing क्रम room in request queue.
 */
अटल व्योम
bfa_ioim_qresume(व्योम *cbarg)
अणु
	काष्ठा bfa_ioim_s *ioim = cbarg;

	bfa_stats(ioim->itnim, qresumes);
	bfa_sm_send_event(ioim, BFA_IOIM_SM_QRESUME);
पूर्ण


अटल व्योम
bfa_ioim_notअगरy_cleanup(काष्ठा bfa_ioim_s *ioim)
अणु
	/*
	 * Move IO from itnim queue to fcpim global queue since itnim will be
	 * मुक्तd.
	 */
	list_del(&ioim->qe);
	list_add_tail(&ioim->qe, &ioim->fcpim->ioim_comp_q);

	अगर (!ioim->iosp->tskim) अणु
		अगर (ioim->fcpim->delay_comp && ioim->itnim->iotov_active) अणु
			bfa_cb_dequeue(&ioim->hcb_qe);
			list_del(&ioim->qe);
			list_add_tail(&ioim->qe, &ioim->itnim->delay_comp_q);
		पूर्ण
		bfa_itnim_ioकरोne(ioim->itnim);
	पूर्ण अन्यथा
		bfa_wc_करोwn(&ioim->iosp->tskim->wc);
पूर्ण

अटल bfa_boolean_t
bfa_ioim_is_पातable(काष्ठा bfa_ioim_s *ioim)
अणु
	अगर ((bfa_sm_cmp_state(ioim, bfa_ioim_sm_uninit) &&
	    (!bfa_q_is_on_q(&ioim->itnim->pending_q, ioim)))	||
	    (bfa_sm_cmp_state(ioim, bfa_ioim_sm_पात))		||
	    (bfa_sm_cmp_state(ioim, bfa_ioim_sm_पात_qfull))	||
	    (bfa_sm_cmp_state(ioim, bfa_ioim_sm_hcb))		||
	    (bfa_sm_cmp_state(ioim, bfa_ioim_sm_hcb_मुक्त))	||
	    (bfa_sm_cmp_state(ioim, bfa_ioim_sm_resमुक्त)))
		वापस BFA_FALSE;

	वापस BFA_TRUE;
पूर्ण

व्योम
bfa_ioim_delayed_comp(काष्ठा bfa_ioim_s *ioim, bfa_boolean_t iotov)
अणु
	/*
	 * If path tov समयr expired, failback with PATHTOV status - these
	 * IO requests are not normally retried by IO stack.
	 *
	 * Otherwise device cameback online and fail it with normal failed
	 * status so that IO stack retries these failed IO requests.
	 */
	अगर (iotov)
		ioim->io_cbfn = __bfa_cb_ioim_pathtov;
	अन्यथा अणु
		ioim->io_cbfn = __bfa_cb_ioim_failed;
		bfa_stats(ioim->itnim, iocom_nexus_पात);
	पूर्ण
	bfa_cb_queue(ioim->bfa, &ioim->hcb_qe, ioim->io_cbfn, ioim);

	/*
	 * Move IO to fcpim global queue since itnim will be
	 * मुक्तd.
	 */
	list_del(&ioim->qe);
	list_add_tail(&ioim->qe, &ioim->fcpim->ioim_comp_q);
पूर्ण


/*
 * Memory allocation and initialization.
 */
व्योम
bfa_ioim_attach(काष्ठा bfa_fcpim_s *fcpim)
अणु
	काष्ठा bfa_ioim_s		*ioim;
	काष्ठा bfa_fcp_mod_s	*fcp = fcpim->fcp;
	काष्ठा bfa_ioim_sp_s	*iosp;
	u16		i;

	/*
	 * claim memory first
	 */
	ioim = (काष्ठा bfa_ioim_s *) bfa_mem_kva_curp(fcp);
	fcpim->ioim_arr = ioim;
	bfa_mem_kva_curp(fcp) = (u8 *) (ioim + fcpim->fcp->num_ioim_reqs);

	iosp = (काष्ठा bfa_ioim_sp_s *) bfa_mem_kva_curp(fcp);
	fcpim->ioim_sp_arr = iosp;
	bfa_mem_kva_curp(fcp) = (u8 *) (iosp + fcpim->fcp->num_ioim_reqs);

	/*
	 * Initialize ioim मुक्त queues
	 */
	INIT_LIST_HEAD(&fcpim->ioim_resमुक्त_q);
	INIT_LIST_HEAD(&fcpim->ioim_comp_q);

	क्रम (i = 0; i < fcpim->fcp->num_ioim_reqs;
	     i++, ioim++, iosp++) अणु
		/*
		 * initialize IOIM
		 */
		स_रखो(ioim, 0, माप(काष्ठा bfa_ioim_s));
		ioim->iotag   = i;
		ioim->bfa     = fcpim->bfa;
		ioim->fcpim   = fcpim;
		ioim->iosp    = iosp;
		INIT_LIST_HEAD(&ioim->sgpg_q);
		bfa_reqq_winit(&ioim->iosp->reqq_रुको,
				   bfa_ioim_qresume, ioim);
		bfa_sgpg_winit(&ioim->iosp->sgpg_wqe,
				   bfa_ioim_sgpg_alloced, ioim);
		bfa_sm_set_state(ioim, bfa_ioim_sm_uninit);
	पूर्ण
पूर्ण

व्योम
bfa_ioim_isr(काष्ठा bfa_s *bfa, काष्ठा bfi_msg_s *m)
अणु
	काष्ठा bfa_fcpim_s *fcpim = BFA_FCPIM(bfa);
	काष्ठा bfi_ioim_rsp_s *rsp = (काष्ठा bfi_ioim_rsp_s *) m;
	काष्ठा bfa_ioim_s *ioim;
	u16	iotag;
	क्रमागत bfa_ioim_event evt = BFA_IOIM_SM_COMP;

	iotag = be16_to_cpu(rsp->io_tag);

	ioim = BFA_IOIM_FROM_TAG(fcpim, iotag);
	WARN_ON(ioim->iotag != iotag);

	bfa_trc(ioim->bfa, ioim->iotag);
	bfa_trc(ioim->bfa, rsp->io_status);
	bfa_trc(ioim->bfa, rsp->reuse_io_tag);

	अगर (bfa_sm_cmp_state(ioim, bfa_ioim_sm_active))
		ioim->iosp->comp_rspmsg = *m;

	चयन (rsp->io_status) अणु
	हाल BFI_IOIM_STS_OK:
		bfa_stats(ioim->itnim, iocomp_ok);
		अगर (rsp->reuse_io_tag == 0)
			evt = BFA_IOIM_SM_DONE;
		अन्यथा
			evt = BFA_IOIM_SM_COMP;
		अवरोध;

	हाल BFI_IOIM_STS_TIMEDOUT:
		bfa_stats(ioim->itnim, iocomp_समयकरोut);
		fallthrough;
	हाल BFI_IOIM_STS_ABORTED:
		rsp->io_status = BFI_IOIM_STS_ABORTED;
		bfa_stats(ioim->itnim, iocomp_पातed);
		अगर (rsp->reuse_io_tag == 0)
			evt = BFA_IOIM_SM_DONE;
		अन्यथा
			evt = BFA_IOIM_SM_COMP;
		अवरोध;

	हाल BFI_IOIM_STS_PROTO_ERR:
		bfa_stats(ioim->itnim, iocom_proto_err);
		WARN_ON(!rsp->reuse_io_tag);
		evt = BFA_IOIM_SM_COMP;
		अवरोध;

	हाल BFI_IOIM_STS_SQER_NEEDED:
		bfa_stats(ioim->itnim, iocom_sqer_needed);
		WARN_ON(rsp->reuse_io_tag != 0);
		evt = BFA_IOIM_SM_SQRETRY;
		अवरोध;

	हाल BFI_IOIM_STS_RES_FREE:
		bfa_stats(ioim->itnim, iocom_res_मुक्त);
		evt = BFA_IOIM_SM_FREE;
		अवरोध;

	हाल BFI_IOIM_STS_HOST_ABORTED:
		bfa_stats(ioim->itnim, iocom_hostabrts);
		अगर (rsp->पात_tag != ioim->पात_tag) अणु
			bfa_trc(ioim->bfa, rsp->पात_tag);
			bfa_trc(ioim->bfa, ioim->पात_tag);
			वापस;
		पूर्ण

		अगर (rsp->reuse_io_tag)
			evt = BFA_IOIM_SM_ABORT_COMP;
		अन्यथा
			evt = BFA_IOIM_SM_ABORT_DONE;
		अवरोध;

	हाल BFI_IOIM_STS_UTAG:
		bfa_stats(ioim->itnim, iocom_utags);
		evt = BFA_IOIM_SM_COMP_UTAG;
		अवरोध;

	शेष:
		WARN_ON(1);
	पूर्ण

	bfa_sm_send_event(ioim, evt);
पूर्ण

व्योम
bfa_ioim_good_comp_isr(काष्ठा bfa_s *bfa, काष्ठा bfi_msg_s *m)
अणु
	काष्ठा bfa_fcpim_s *fcpim = BFA_FCPIM(bfa);
	काष्ठा bfi_ioim_rsp_s *rsp = (काष्ठा bfi_ioim_rsp_s *) m;
	काष्ठा bfa_ioim_s *ioim;
	u16	iotag;

	iotag = be16_to_cpu(rsp->io_tag);

	ioim = BFA_IOIM_FROM_TAG(fcpim, iotag);
	WARN_ON(ioim->iotag != iotag);

	bfa_ioim_cb_profile_comp(fcpim, ioim);

	bfa_sm_send_event(ioim, BFA_IOIM_SM_COMP_GOOD);
पूर्ण

/*
 * Called by itnim to clean up IO जबतक going offline.
 */
व्योम
bfa_ioim_cleanup(काष्ठा bfa_ioim_s *ioim)
अणु
	bfa_trc(ioim->bfa, ioim->iotag);
	bfa_stats(ioim->itnim, io_cleanups);

	ioim->iosp->tskim = शून्य;
	bfa_sm_send_event(ioim, BFA_IOIM_SM_CLEANUP);
पूर्ण

व्योम
bfa_ioim_cleanup_पंचांग(काष्ठा bfa_ioim_s *ioim, काष्ठा bfa_tskim_s *tskim)
अणु
	bfa_trc(ioim->bfa, ioim->iotag);
	bfa_stats(ioim->itnim, io_पंचांगपातs);

	ioim->iosp->tskim = tskim;
	bfa_sm_send_event(ioim, BFA_IOIM_SM_CLEANUP);
पूर्ण

/*
 * IOC failure handling.
 */
व्योम
bfa_ioim_iocdisable(काष्ठा bfa_ioim_s *ioim)
अणु
	bfa_trc(ioim->bfa, ioim->iotag);
	bfa_stats(ioim->itnim, io_iocकरोwns);
	bfa_sm_send_event(ioim, BFA_IOIM_SM_HWFAIL);
पूर्ण

/*
 * IO offline TOV popped. Fail the pending IO.
 */
व्योम
bfa_ioim_tov(काष्ठा bfa_ioim_s *ioim)
अणु
	bfa_trc(ioim->bfa, ioim->iotag);
	bfa_sm_send_event(ioim, BFA_IOIM_SM_IOTOV);
पूर्ण


/*
 * Allocate IOIM resource क्रम initiator mode I/O request.
 */
काष्ठा bfa_ioim_s *
bfa_ioim_alloc(काष्ठा bfa_s *bfa, काष्ठा bfad_ioim_s *dio,
		काष्ठा bfa_itnim_s *itnim, u16 nsges)
अणु
	काष्ठा bfa_fcpim_s *fcpim = BFA_FCPIM(bfa);
	काष्ठा bfa_ioim_s *ioim;
	काष्ठा bfa_iotag_s *iotag = शून्य;

	/*
	 * alocate IOIM resource
	 */
	bfa_q_deq(&fcpim->fcp->iotag_ioim_मुक्त_q, &iotag);
	अगर (!iotag) अणु
		bfa_stats(itnim, no_iotags);
		वापस शून्य;
	पूर्ण

	ioim = BFA_IOIM_FROM_TAG(fcpim, iotag->tag);

	ioim->dio = dio;
	ioim->itnim = itnim;
	ioim->nsges = nsges;
	ioim->nsgpgs = 0;

	bfa_stats(itnim, total_ios);
	fcpim->ios_active++;

	list_add_tail(&ioim->qe, &itnim->io_q);

	वापस ioim;
पूर्ण

व्योम
bfa_ioim_मुक्त(काष्ठा bfa_ioim_s *ioim)
अणु
	काष्ठा bfa_fcpim_s *fcpim = ioim->fcpim;
	काष्ठा bfa_iotag_s *iotag;

	अगर (ioim->nsgpgs > 0)
		bfa_sgpg_mमुक्त(ioim->bfa, &ioim->sgpg_q, ioim->nsgpgs);

	bfa_stats(ioim->itnim, io_comps);
	fcpim->ios_active--;

	ioim->iotag &= BFA_IOIM_IOTAG_MASK;

	WARN_ON(!(ioim->iotag <
		(fcpim->fcp->num_ioim_reqs + fcpim->fcp->num_fwtio_reqs)));
	iotag = BFA_IOTAG_FROM_TAG(fcpim->fcp, ioim->iotag);

	अगर (ioim->iotag < fcpim->fcp->num_ioim_reqs)
		list_add_tail(&iotag->qe, &fcpim->fcp->iotag_ioim_मुक्त_q);
	अन्यथा
		list_add_tail(&iotag->qe, &fcpim->fcp->iotag_tio_मुक्त_q);

	list_del(&ioim->qe);
पूर्ण

व्योम
bfa_ioim_start(काष्ठा bfa_ioim_s *ioim)
अणु
	bfa_ioim_cb_profile_start(ioim->fcpim, ioim);

	/*
	 * Obtain the queue over which this request has to be issued
	 */
	ioim->reqq = bfa_fcpim_ioredirect_enabled(ioim->bfa) ?
			BFA_FALSE : bfa_itnim_get_reqq(ioim);

	bfa_sm_send_event(ioim, BFA_IOIM_SM_START);
पूर्ण

/*
 * Driver I/O पात request.
 */
bfa_status_t
bfa_ioim_पात(काष्ठा bfa_ioim_s *ioim)
अणु

	bfa_trc(ioim->bfa, ioim->iotag);

	अगर (!bfa_ioim_is_पातable(ioim))
		वापस BFA_STATUS_FAILED;

	bfa_stats(ioim->itnim, io_पातs);
	bfa_sm_send_event(ioim, BFA_IOIM_SM_ABORT);

	वापस BFA_STATUS_OK;
पूर्ण

/*
 *  BFA TSKIM state machine functions
 */

/*
 * Task management command beginning state.
 */
अटल व्योम
bfa_tskim_sm_uninit(काष्ठा bfa_tskim_s *tskim, क्रमागत bfa_tskim_event event)
अणु
	bfa_trc(tskim->bfa, tskim->tsk_tag << 16 | event);

	चयन (event) अणु
	हाल BFA_TSKIM_SM_START:
		bfa_sm_set_state(tskim, bfa_tskim_sm_active);
		bfa_tskim_gather_ios(tskim);

		/*
		 * If device is offline, करो not send TM on wire. Just cleanup
		 * any pending IO requests and complete TM request.
		 */
		अगर (!bfa_itnim_is_online(tskim->itnim)) अणु
			bfa_sm_set_state(tskim, bfa_tskim_sm_iocleanup);
			tskim->tsk_status = BFI_TSKIM_STS_OK;
			bfa_tskim_cleanup_ios(tskim);
			वापस;
		पूर्ण

		अगर (!bfa_tskim_send(tskim)) अणु
			bfa_sm_set_state(tskim, bfa_tskim_sm_qfull);
			bfa_stats(tskim->itnim, पंचांग_qरुको);
			bfa_reqq_रुको(tskim->bfa, tskim->itnim->reqq,
					  &tskim->reqq_रुको);
		पूर्ण
		अवरोध;

	शेष:
		bfa_sm_fault(tskim->bfa, event);
	पूर्ण
पूर्ण

/*
 * TM command is active, aरुकोing completion from firmware to
 * cleanup IO requests in TM scope.
 */
अटल व्योम
bfa_tskim_sm_active(काष्ठा bfa_tskim_s *tskim, क्रमागत bfa_tskim_event event)
अणु
	bfa_trc(tskim->bfa, tskim->tsk_tag << 16 | event);

	चयन (event) अणु
	हाल BFA_TSKIM_SM_DONE:
		bfa_sm_set_state(tskim, bfa_tskim_sm_iocleanup);
		bfa_tskim_cleanup_ios(tskim);
		अवरोध;

	हाल BFA_TSKIM_SM_CLEANUP:
		bfa_sm_set_state(tskim, bfa_tskim_sm_cleanup);
		अगर (!bfa_tskim_send_पात(tskim)) अणु
			bfa_sm_set_state(tskim, bfa_tskim_sm_cleanup_qfull);
			bfa_stats(tskim->itnim, पंचांग_qरुको);
			bfa_reqq_रुको(tskim->bfa, tskim->itnim->reqq,
				&tskim->reqq_रुको);
		पूर्ण
		अवरोध;

	हाल BFA_TSKIM_SM_HWFAIL:
		bfa_sm_set_state(tskim, bfa_tskim_sm_hcb);
		bfa_tskim_iocdisable_ios(tskim);
		bfa_tskim_qcomp(tskim, __bfa_cb_tskim_failed);
		अवरोध;

	शेष:
		bfa_sm_fault(tskim->bfa, event);
	पूर्ण
पूर्ण

/*
 * An active TM is being cleaned up since ITN is offline. Aरुकोing cleanup
 * completion event from firmware.
 */
अटल व्योम
bfa_tskim_sm_cleanup(काष्ठा bfa_tskim_s *tskim, क्रमागत bfa_tskim_event event)
अणु
	bfa_trc(tskim->bfa, tskim->tsk_tag << 16 | event);

	चयन (event) अणु
	हाल BFA_TSKIM_SM_DONE:
		/*
		 * Ignore and रुको क्रम ABORT completion from firmware.
		 */
		अवरोध;

	हाल BFA_TSKIM_SM_UTAG:
	हाल BFA_TSKIM_SM_CLEANUP_DONE:
		bfa_sm_set_state(tskim, bfa_tskim_sm_iocleanup);
		bfa_tskim_cleanup_ios(tskim);
		अवरोध;

	हाल BFA_TSKIM_SM_HWFAIL:
		bfa_sm_set_state(tskim, bfa_tskim_sm_hcb);
		bfa_tskim_iocdisable_ios(tskim);
		bfa_tskim_qcomp(tskim, __bfa_cb_tskim_failed);
		अवरोध;

	शेष:
		bfa_sm_fault(tskim->bfa, event);
	पूर्ण
पूर्ण

अटल व्योम
bfa_tskim_sm_iocleanup(काष्ठा bfa_tskim_s *tskim, क्रमागत bfa_tskim_event event)
अणु
	bfa_trc(tskim->bfa, tskim->tsk_tag << 16 | event);

	चयन (event) अणु
	हाल BFA_TSKIM_SM_IOS_DONE:
		bfa_sm_set_state(tskim, bfa_tskim_sm_hcb);
		bfa_tskim_qcomp(tskim, __bfa_cb_tskim_करोne);
		अवरोध;

	हाल BFA_TSKIM_SM_CLEANUP:
		/*
		 * Ignore, TM command completed on wire.
		 * Notअगरy TM conmpletion on IO cleanup completion.
		 */
		अवरोध;

	हाल BFA_TSKIM_SM_HWFAIL:
		bfa_sm_set_state(tskim, bfa_tskim_sm_hcb);
		bfa_tskim_iocdisable_ios(tskim);
		bfa_tskim_qcomp(tskim, __bfa_cb_tskim_failed);
		अवरोध;

	शेष:
		bfa_sm_fault(tskim->bfa, event);
	पूर्ण
पूर्ण

/*
 * Task management command is रुकोing क्रम room in request CQ
 */
अटल व्योम
bfa_tskim_sm_qfull(काष्ठा bfa_tskim_s *tskim, क्रमागत bfa_tskim_event event)
अणु
	bfa_trc(tskim->bfa, tskim->tsk_tag << 16 | event);

	चयन (event) अणु
	हाल BFA_TSKIM_SM_QRESUME:
		bfa_sm_set_state(tskim, bfa_tskim_sm_active);
		bfa_tskim_send(tskim);
		अवरोध;

	हाल BFA_TSKIM_SM_CLEANUP:
		/*
		 * No need to send TM on wire since ITN is offline.
		 */
		bfa_sm_set_state(tskim, bfa_tskim_sm_iocleanup);
		bfa_reqq_wcancel(&tskim->reqq_रुको);
		bfa_tskim_cleanup_ios(tskim);
		अवरोध;

	हाल BFA_TSKIM_SM_HWFAIL:
		bfa_sm_set_state(tskim, bfa_tskim_sm_hcb);
		bfa_reqq_wcancel(&tskim->reqq_रुको);
		bfa_tskim_iocdisable_ios(tskim);
		bfa_tskim_qcomp(tskim, __bfa_cb_tskim_failed);
		अवरोध;

	शेष:
		bfa_sm_fault(tskim->bfa, event);
	पूर्ण
पूर्ण

/*
 * Task management command is active, aरुकोing क्रम room in request CQ
 * to send clean up request.
 */
अटल व्योम
bfa_tskim_sm_cleanup_qfull(काष्ठा bfa_tskim_s *tskim,
		क्रमागत bfa_tskim_event event)
अणु
	bfa_trc(tskim->bfa, tskim->tsk_tag << 16 | event);

	चयन (event) अणु
	हाल BFA_TSKIM_SM_DONE:
		bfa_reqq_wcancel(&tskim->reqq_रुको);
		fallthrough;
	हाल BFA_TSKIM_SM_QRESUME:
		bfa_sm_set_state(tskim, bfa_tskim_sm_cleanup);
		bfa_tskim_send_पात(tskim);
		अवरोध;

	हाल BFA_TSKIM_SM_HWFAIL:
		bfa_sm_set_state(tskim, bfa_tskim_sm_hcb);
		bfa_reqq_wcancel(&tskim->reqq_रुको);
		bfa_tskim_iocdisable_ios(tskim);
		bfa_tskim_qcomp(tskim, __bfa_cb_tskim_failed);
		अवरोध;

	शेष:
		bfa_sm_fault(tskim->bfa, event);
	पूर्ण
पूर्ण

/*
 * BFA callback is pending
 */
अटल व्योम
bfa_tskim_sm_hcb(काष्ठा bfa_tskim_s *tskim, क्रमागत bfa_tskim_event event)
अणु
	bfa_trc(tskim->bfa, tskim->tsk_tag << 16 | event);

	चयन (event) अणु
	हाल BFA_TSKIM_SM_HCB:
		bfa_sm_set_state(tskim, bfa_tskim_sm_uninit);
		bfa_tskim_मुक्त(tskim);
		अवरोध;

	हाल BFA_TSKIM_SM_CLEANUP:
		bfa_tskim_notअगरy_comp(tskim);
		अवरोध;

	हाल BFA_TSKIM_SM_HWFAIL:
		अवरोध;

	शेष:
		bfa_sm_fault(tskim->bfa, event);
	पूर्ण
पूर्ण

अटल व्योम
__bfa_cb_tskim_करोne(व्योम *cbarg, bfa_boolean_t complete)
अणु
	काष्ठा bfa_tskim_s *tskim = cbarg;

	अगर (!complete) अणु
		bfa_sm_send_event(tskim, BFA_TSKIM_SM_HCB);
		वापस;
	पूर्ण

	bfa_stats(tskim->itnim, पंचांग_success);
	bfa_cb_tskim_करोne(tskim->bfa->bfad, tskim->dtsk, tskim->tsk_status);
पूर्ण

अटल व्योम
__bfa_cb_tskim_failed(व्योम *cbarg, bfa_boolean_t complete)
अणु
	काष्ठा bfa_tskim_s *tskim = cbarg;

	अगर (!complete) अणु
		bfa_sm_send_event(tskim, BFA_TSKIM_SM_HCB);
		वापस;
	पूर्ण

	bfa_stats(tskim->itnim, पंचांग_failures);
	bfa_cb_tskim_करोne(tskim->bfa->bfad, tskim->dtsk,
				BFI_TSKIM_STS_FAILED);
पूर्ण

अटल bfa_boolean_t
bfa_tskim_match_scope(काष्ठा bfa_tskim_s *tskim, काष्ठा scsi_lun lun)
अणु
	चयन (tskim->पंचांग_cmnd) अणु
	हाल FCP_TM_TARGET_RESET:
		वापस BFA_TRUE;

	हाल FCP_TM_ABORT_TASK_SET:
	हाल FCP_TM_CLEAR_TASK_SET:
	हाल FCP_TM_LUN_RESET:
	हाल FCP_TM_CLEAR_ACA:
		वापस !स_भेद(&tskim->lun, &lun, माप(lun));

	शेष:
		WARN_ON(1);
	पूर्ण

	वापस BFA_FALSE;
पूर्ण

/*
 * Gather affected IO requests and task management commands.
 */
अटल व्योम
bfa_tskim_gather_ios(काष्ठा bfa_tskim_s *tskim)
अणु
	काष्ठा bfa_itnim_s *itnim = tskim->itnim;
	काष्ठा bfa_ioim_s *ioim;
	काष्ठा list_head *qe, *qen;
	काष्ठा scsi_cmnd *cmnd;
	काष्ठा scsi_lun scsilun;

	INIT_LIST_HEAD(&tskim->io_q);

	/*
	 * Gather any active IO requests first.
	 */
	list_क्रम_each_safe(qe, qen, &itnim->io_q) अणु
		ioim = (काष्ठा bfa_ioim_s *) qe;
		cmnd = (काष्ठा scsi_cmnd *) ioim->dio;
		पूर्णांक_to_scsilun(cmnd->device->lun, &scsilun);
		अगर (bfa_tskim_match_scope(tskim, scsilun)) अणु
			list_del(&ioim->qe);
			list_add_tail(&ioim->qe, &tskim->io_q);
		पूर्ण
	पूर्ण

	/*
	 * Failback any pending IO requests immediately.
	 */
	list_क्रम_each_safe(qe, qen, &itnim->pending_q) अणु
		ioim = (काष्ठा bfa_ioim_s *) qe;
		cmnd = (काष्ठा scsi_cmnd *) ioim->dio;
		पूर्णांक_to_scsilun(cmnd->device->lun, &scsilun);
		अगर (bfa_tskim_match_scope(tskim, scsilun)) अणु
			list_del(&ioim->qe);
			list_add_tail(&ioim->qe, &ioim->fcpim->ioim_comp_q);
			bfa_ioim_tov(ioim);
		पूर्ण
	पूर्ण
पूर्ण

/*
 * IO cleanup completion
 */
अटल व्योम
bfa_tskim_cleanp_comp(व्योम *tskim_cbarg)
अणु
	काष्ठा bfa_tskim_s *tskim = tskim_cbarg;

	bfa_stats(tskim->itnim, पंचांग_io_comps);
	bfa_sm_send_event(tskim, BFA_TSKIM_SM_IOS_DONE);
पूर्ण

/*
 * Gather affected IO requests and task management commands.
 */
अटल व्योम
bfa_tskim_cleanup_ios(काष्ठा bfa_tskim_s *tskim)
अणु
	काष्ठा bfa_ioim_s *ioim;
	काष्ठा list_head	*qe, *qen;

	bfa_wc_init(&tskim->wc, bfa_tskim_cleanp_comp, tskim);

	list_क्रम_each_safe(qe, qen, &tskim->io_q) अणु
		ioim = (काष्ठा bfa_ioim_s *) qe;
		bfa_wc_up(&tskim->wc);
		bfa_ioim_cleanup_पंचांग(ioim, tskim);
	पूर्ण

	bfa_wc_रुको(&tskim->wc);
पूर्ण

/*
 * Send task management request to firmware.
 */
अटल bfa_boolean_t
bfa_tskim_send(काष्ठा bfa_tskim_s *tskim)
अणु
	काष्ठा bfa_itnim_s *itnim = tskim->itnim;
	काष्ठा bfi_tskim_req_s *m;

	/*
	 * check क्रम room in queue to send request now
	 */
	m = bfa_reqq_next(tskim->bfa, itnim->reqq);
	अगर (!m)
		वापस BFA_FALSE;

	/*
	 * build i/o request message next
	 */
	bfi_h2i_set(m->mh, BFI_MC_TSKIM, BFI_TSKIM_H2I_TM_REQ,
			bfa_fn_lpu(tskim->bfa));

	m->tsk_tag = cpu_to_be16(tskim->tsk_tag);
	m->itn_fhdl = tskim->itnim->rport->fw_handle;
	m->t_secs = tskim->tsecs;
	m->lun = tskim->lun;
	m->पंचांग_flags = tskim->पंचांग_cmnd;

	/*
	 * queue I/O message to firmware
	 */
	bfa_reqq_produce(tskim->bfa, itnim->reqq, m->mh);
	वापस BFA_TRUE;
पूर्ण

/*
 * Send पात request to cleanup an active TM to firmware.
 */
अटल bfa_boolean_t
bfa_tskim_send_पात(काष्ठा bfa_tskim_s *tskim)
अणु
	काष्ठा bfa_itnim_s	*itnim = tskim->itnim;
	काष्ठा bfi_tskim_पातreq_s	*m;

	/*
	 * check क्रम room in queue to send request now
	 */
	m = bfa_reqq_next(tskim->bfa, itnim->reqq);
	अगर (!m)
		वापस BFA_FALSE;

	/*
	 * build i/o request message next
	 */
	bfi_h2i_set(m->mh, BFI_MC_TSKIM, BFI_TSKIM_H2I_ABORT_REQ,
			bfa_fn_lpu(tskim->bfa));

	m->tsk_tag  = cpu_to_be16(tskim->tsk_tag);

	/*
	 * queue I/O message to firmware
	 */
	bfa_reqq_produce(tskim->bfa, itnim->reqq, m->mh);
	वापस BFA_TRUE;
पूर्ण

/*
 * Call to resume task management cmnd रुकोing क्रम room in request queue.
 */
अटल व्योम
bfa_tskim_qresume(व्योम *cbarg)
अणु
	काष्ठा bfa_tskim_s *tskim = cbarg;

	bfa_stats(tskim->itnim, पंचांग_qresumes);
	bfa_sm_send_event(tskim, BFA_TSKIM_SM_QRESUME);
पूर्ण

/*
 * Cleanup IOs associated with a task mangement command on IOC failures.
 */
अटल व्योम
bfa_tskim_iocdisable_ios(काष्ठा bfa_tskim_s *tskim)
अणु
	काष्ठा bfa_ioim_s *ioim;
	काष्ठा list_head	*qe, *qen;

	list_क्रम_each_safe(qe, qen, &tskim->io_q) अणु
		ioim = (काष्ठा bfa_ioim_s *) qe;
		bfa_ioim_iocdisable(ioim);
	पूर्ण
पूर्ण

/*
 * Notअगरication on completions from related ioim.
 */
व्योम
bfa_tskim_ioकरोne(काष्ठा bfa_tskim_s *tskim)
अणु
	bfa_wc_करोwn(&tskim->wc);
पूर्ण

/*
 * Handle IOC h/w failure notअगरication from itnim.
 */
व्योम
bfa_tskim_iocdisable(काष्ठा bfa_tskim_s *tskim)
अणु
	tskim->notअगरy = BFA_FALSE;
	bfa_stats(tskim->itnim, पंचांग_iocकरोwns);
	bfa_sm_send_event(tskim, BFA_TSKIM_SM_HWFAIL);
पूर्ण

/*
 * Cleanup TM command and associated IOs as part of ITNIM offline.
 */
व्योम
bfa_tskim_cleanup(काष्ठा bfa_tskim_s *tskim)
अणु
	tskim->notअगरy = BFA_TRUE;
	bfa_stats(tskim->itnim, पंचांग_cleanups);
	bfa_sm_send_event(tskim, BFA_TSKIM_SM_CLEANUP);
पूर्ण

/*
 * Memory allocation and initialization.
 */
व्योम
bfa_tskim_attach(काष्ठा bfa_fcpim_s *fcpim)
अणु
	काष्ठा bfa_tskim_s *tskim;
	काष्ठा bfa_fcp_mod_s	*fcp = fcpim->fcp;
	u16	i;

	INIT_LIST_HEAD(&fcpim->tskim_मुक्त_q);
	INIT_LIST_HEAD(&fcpim->tskim_unused_q);

	tskim = (काष्ठा bfa_tskim_s *) bfa_mem_kva_curp(fcp);
	fcpim->tskim_arr = tskim;

	क्रम (i = 0; i < fcpim->num_tskim_reqs; i++, tskim++) अणु
		/*
		 * initialize TSKIM
		 */
		स_रखो(tskim, 0, माप(काष्ठा bfa_tskim_s));
		tskim->tsk_tag = i;
		tskim->bfa	= fcpim->bfa;
		tskim->fcpim	= fcpim;
		tskim->notअगरy  = BFA_FALSE;
		bfa_reqq_winit(&tskim->reqq_रुको, bfa_tskim_qresume,
					tskim);
		bfa_sm_set_state(tskim, bfa_tskim_sm_uninit);

		list_add_tail(&tskim->qe, &fcpim->tskim_मुक्त_q);
	पूर्ण

	bfa_mem_kva_curp(fcp) = (u8 *) tskim;
पूर्ण

व्योम
bfa_tskim_isr(काष्ठा bfa_s *bfa, काष्ठा bfi_msg_s *m)
अणु
	काष्ठा bfa_fcpim_s *fcpim = BFA_FCPIM(bfa);
	काष्ठा bfi_tskim_rsp_s *rsp = (काष्ठा bfi_tskim_rsp_s *) m;
	काष्ठा bfa_tskim_s *tskim;
	u16	tsk_tag = be16_to_cpu(rsp->tsk_tag);

	tskim = BFA_TSKIM_FROM_TAG(fcpim, tsk_tag);
	WARN_ON(tskim->tsk_tag != tsk_tag);

	tskim->tsk_status = rsp->tsk_status;

	/*
	 * Firmware sends BFI_TSKIM_STS_ABORTED status क्रम पात
	 * requests. All other statuses are क्रम normal completions.
	 */
	अगर (rsp->tsk_status == BFI_TSKIM_STS_ABORTED) अणु
		bfa_stats(tskim->itnim, पंचांग_cleanup_comps);
		bfa_sm_send_event(tskim, BFA_TSKIM_SM_CLEANUP_DONE);
	पूर्ण अन्यथा अगर (rsp->tsk_status == BFI_TSKIM_STS_UTAG) अणु
		bfa_sm_send_event(tskim, BFA_TSKIM_SM_UTAG);
	पूर्ण अन्यथा अणु
		bfa_stats(tskim->itnim, पंचांग_fw_rsps);
		bfa_sm_send_event(tskim, BFA_TSKIM_SM_DONE);
	पूर्ण
पूर्ण


काष्ठा bfa_tskim_s *
bfa_tskim_alloc(काष्ठा bfa_s *bfa, काष्ठा bfad_tskim_s *dtsk)
अणु
	काष्ठा bfa_fcpim_s *fcpim = BFA_FCPIM(bfa);
	काष्ठा bfa_tskim_s *tskim;

	bfa_q_deq(&fcpim->tskim_मुक्त_q, &tskim);

	अगर (tskim)
		tskim->dtsk = dtsk;

	वापस tskim;
पूर्ण

व्योम
bfa_tskim_मुक्त(काष्ठा bfa_tskim_s *tskim)
अणु
	WARN_ON(!bfa_q_is_on_q_func(&tskim->itnim->tsk_q, &tskim->qe));
	list_del(&tskim->qe);
	list_add_tail(&tskim->qe, &tskim->fcpim->tskim_मुक्त_q);
पूर्ण

/*
 * Start a task management command.
 *
 * @param[in]	tskim	BFA task management command instance
 * @param[in]	itnim	i-t nexus क्रम the task management command
 * @param[in]	lun	lun, अगर applicable
 * @param[in]	पंचांग_cmnd	Task management command code.
 * @param[in]	t_secs	Timeout in seconds
 *
 * @वापस None.
 */
व्योम
bfa_tskim_start(काष्ठा bfa_tskim_s *tskim, काष्ठा bfa_itnim_s *itnim,
			काष्ठा scsi_lun lun,
			क्रमागत fcp_पंचांग_cmnd पंचांग_cmnd, u8 tsecs)
अणु
	tskim->itnim	= itnim;
	tskim->lun	= lun;
	tskim->पंचांग_cmnd = पंचांग_cmnd;
	tskim->tsecs	= tsecs;
	tskim->notअगरy  = BFA_FALSE;
	bfa_stats(itnim, पंचांग_cmnds);

	list_add_tail(&tskim->qe, &itnim->tsk_q);
	bfa_sm_send_event(tskim, BFA_TSKIM_SM_START);
पूर्ण

व्योम
bfa_tskim_res_recfg(काष्ठा bfa_s *bfa, u16 num_tskim_fw)
अणु
	काष्ठा bfa_fcpim_s	*fcpim = BFA_FCPIM(bfa);
	काष्ठा list_head	*qe;
	पूर्णांक	i;

	क्रम (i = 0; i < (fcpim->num_tskim_reqs - num_tskim_fw); i++) अणु
		bfa_q_deq_tail(&fcpim->tskim_मुक्त_q, &qe);
		list_add_tail(qe, &fcpim->tskim_unused_q);
	पूर्ण
पूर्ण

व्योम
bfa_fcp_meminfo(काष्ठा bfa_iocfc_cfg_s *cfg, काष्ठा bfa_meminfo_s *minfo,
		काष्ठा bfa_s *bfa)
अणु
	काष्ठा bfa_fcp_mod_s *fcp = BFA_FCP_MOD(bfa);
	काष्ठा bfa_mem_kva_s *fcp_kva = BFA_MEM_FCP_KVA(bfa);
	काष्ठा bfa_mem_dma_s *seg_ptr;
	u16	nsegs, idx, per_seg_ios, num_io_req;
	u32	km_len = 0;

	/*
	 * ZERO क्रम num_ioim_reqs and num_fwtio_reqs is allowed config value.
	 * So अगर the values are non zero, adjust them appropriately.
	 */
	अगर (cfg->fwcfg.num_ioim_reqs &&
	    cfg->fwcfg.num_ioim_reqs < BFA_IOIM_MIN)
		cfg->fwcfg.num_ioim_reqs = BFA_IOIM_MIN;
	अन्यथा अगर (cfg->fwcfg.num_ioim_reqs > BFA_IOIM_MAX)
		cfg->fwcfg.num_ioim_reqs = BFA_IOIM_MAX;

	अगर (cfg->fwcfg.num_fwtio_reqs > BFA_FWTIO_MAX)
		cfg->fwcfg.num_fwtio_reqs = BFA_FWTIO_MAX;

	num_io_req = (cfg->fwcfg.num_ioim_reqs + cfg->fwcfg.num_fwtio_reqs);
	अगर (num_io_req > BFA_IO_MAX) अणु
		अगर (cfg->fwcfg.num_ioim_reqs && cfg->fwcfg.num_fwtio_reqs) अणु
			cfg->fwcfg.num_ioim_reqs = BFA_IO_MAX/2;
			cfg->fwcfg.num_fwtio_reqs = BFA_IO_MAX/2;
		पूर्ण अन्यथा अगर (cfg->fwcfg.num_fwtio_reqs)
			cfg->fwcfg.num_fwtio_reqs = BFA_FWTIO_MAX;
		अन्यथा
			cfg->fwcfg.num_ioim_reqs = BFA_IOIM_MAX;
	पूर्ण

	bfa_fcpim_meminfo(cfg, &km_len);

	num_io_req = (cfg->fwcfg.num_ioim_reqs + cfg->fwcfg.num_fwtio_reqs);
	km_len += num_io_req * माप(काष्ठा bfa_iotag_s);
	km_len += cfg->fwcfg.num_rports * माप(काष्ठा bfa_itn_s);

	/* dma memory */
	nsegs = BFI_MEM_DMA_NSEGS(num_io_req, BFI_IOIM_SNSLEN);
	per_seg_ios = BFI_MEM_NREQS_SEG(BFI_IOIM_SNSLEN);

	bfa_mem_dma_seg_iter(fcp, seg_ptr, nsegs, idx) अणु
		अगर (num_io_req >= per_seg_ios) अणु
			num_io_req -= per_seg_ios;
			bfa_mem_dma_setup(minfo, seg_ptr,
				per_seg_ios * BFI_IOIM_SNSLEN);
		पूर्ण अन्यथा
			bfa_mem_dma_setup(minfo, seg_ptr,
				num_io_req * BFI_IOIM_SNSLEN);
	पूर्ण

	/* kva memory */
	bfa_mem_kva_setup(minfo, fcp_kva, km_len);
पूर्ण

व्योम
bfa_fcp_attach(काष्ठा bfa_s *bfa, व्योम *bfad, काष्ठा bfa_iocfc_cfg_s *cfg,
		काष्ठा bfa_pcidev_s *pcidev)
अणु
	काष्ठा bfa_fcp_mod_s *fcp = BFA_FCP_MOD(bfa);
	काष्ठा bfa_mem_dma_s *seg_ptr;
	u16	idx, nsegs, num_io_req;

	fcp->max_ioim_reqs = cfg->fwcfg.num_ioim_reqs;
	fcp->num_ioim_reqs = cfg->fwcfg.num_ioim_reqs;
	fcp->num_fwtio_reqs  = cfg->fwcfg.num_fwtio_reqs;
	fcp->num_itns   = cfg->fwcfg.num_rports;
	fcp->bfa = bfa;

	/*
	 * Setup the pool of snsbase addr's, that is passed to fw as
	 * part of bfi_iocfc_cfg_s.
	 */
	num_io_req = (cfg->fwcfg.num_ioim_reqs + cfg->fwcfg.num_fwtio_reqs);
	nsegs = BFI_MEM_DMA_NSEGS(num_io_req, BFI_IOIM_SNSLEN);

	bfa_mem_dma_seg_iter(fcp, seg_ptr, nsegs, idx) अणु

		अगर (!bfa_mem_dma_virt(seg_ptr))
			अवरोध;

		fcp->snsbase[idx].pa = bfa_mem_dma_phys(seg_ptr);
		fcp->snsbase[idx].kva = bfa_mem_dma_virt(seg_ptr);
		bfa_iocfc_set_snsbase(bfa, idx, fcp->snsbase[idx].pa);
	पूर्ण

	fcp->throttle_update_required = 1;
	bfa_fcpim_attach(fcp, bfad, cfg, pcidev);

	bfa_iotag_attach(fcp);

	fcp->itn_arr = (काष्ठा bfa_itn_s *) bfa_mem_kva_curp(fcp);
	bfa_mem_kva_curp(fcp) = (u8 *)fcp->itn_arr +
			(fcp->num_itns * माप(काष्ठा bfa_itn_s));
	स_रखो(fcp->itn_arr, 0,
			(fcp->num_itns * माप(काष्ठा bfa_itn_s)));
पूर्ण

व्योम
bfa_fcp_iocdisable(काष्ठा bfa_s *bfa)
अणु
	काष्ठा bfa_fcp_mod_s *fcp = BFA_FCP_MOD(bfa);

	bfa_fcpim_iocdisable(fcp);
पूर्ण

व्योम
bfa_fcp_res_recfg(काष्ठा bfa_s *bfa, u16 num_ioim_fw, u16 max_ioim_fw)
अणु
	काष्ठा bfa_fcp_mod_s	*mod = BFA_FCP_MOD(bfa);
	काष्ठा list_head	*qe;
	पूर्णांक	i;

	/* Update io throttle value only once during driver load समय */
	अगर (!mod->throttle_update_required)
		वापस;

	क्रम (i = 0; i < (mod->num_ioim_reqs - num_ioim_fw); i++) अणु
		bfa_q_deq_tail(&mod->iotag_ioim_मुक्त_q, &qe);
		list_add_tail(qe, &mod->iotag_unused_q);
	पूर्ण

	अगर (mod->num_ioim_reqs != num_ioim_fw) अणु
		bfa_trc(bfa, mod->num_ioim_reqs);
		bfa_trc(bfa, num_ioim_fw);
	पूर्ण

	mod->max_ioim_reqs = max_ioim_fw;
	mod->num_ioim_reqs = num_ioim_fw;
	mod->throttle_update_required = 0;
पूर्ण

व्योम
bfa_itn_create(काष्ठा bfa_s *bfa, काष्ठा bfa_rport_s *rport,
		व्योम (*isr)(काष्ठा bfa_s *bfa, काष्ठा bfi_msg_s *m))
अणु
	काष्ठा bfa_fcp_mod_s *fcp = BFA_FCP_MOD(bfa);
	काष्ठा bfa_itn_s *itn;

	itn =  BFA_ITN_FROM_TAG(fcp, rport->rport_tag);
	itn->isr = isr;
पूर्ण

/*
 * Itn पूर्णांकerrupt processing.
 */
व्योम
bfa_itn_isr(काष्ठा bfa_s *bfa, काष्ठा bfi_msg_s *m)
अणु
	काष्ठा bfa_fcp_mod_s *fcp = BFA_FCP_MOD(bfa);
	जोड़ bfi_itn_i2h_msg_u msg;
	काष्ठा bfa_itn_s *itn;

	msg.msg = m;
	itn =  BFA_ITN_FROM_TAG(fcp, msg.create_rsp->bfa_handle);

	अगर (itn->isr)
		itn->isr(bfa, m);
	अन्यथा
		WARN_ON(1);
पूर्ण

व्योम
bfa_iotag_attach(काष्ठा bfa_fcp_mod_s *fcp)
अणु
	काष्ठा bfa_iotag_s *iotag;
	u16	num_io_req, i;

	iotag = (काष्ठा bfa_iotag_s *) bfa_mem_kva_curp(fcp);
	fcp->iotag_arr = iotag;

	INIT_LIST_HEAD(&fcp->iotag_ioim_मुक्त_q);
	INIT_LIST_HEAD(&fcp->iotag_tio_मुक्त_q);
	INIT_LIST_HEAD(&fcp->iotag_unused_q);

	num_io_req = fcp->num_ioim_reqs + fcp->num_fwtio_reqs;
	क्रम (i = 0; i < num_io_req; i++, iotag++) अणु
		स_रखो(iotag, 0, माप(काष्ठा bfa_iotag_s));
		iotag->tag = i;
		अगर (i < fcp->num_ioim_reqs)
			list_add_tail(&iotag->qe, &fcp->iotag_ioim_मुक्त_q);
		अन्यथा
			list_add_tail(&iotag->qe, &fcp->iotag_tio_मुक्त_q);
	पूर्ण

	bfa_mem_kva_curp(fcp) = (u8 *) iotag;
पूर्ण


/*
 * To send config req, first try to use throttle value from flash
 * If 0, then use driver parameter
 * We need to use min(flash_val, drv_val) because
 * memory allocation was करोne based on this cfg'd value
 */
u16
bfa_fcpim_get_throttle_cfg(काष्ठा bfa_s *bfa, u16 drv_cfg_param)
अणु
	u16 पंचांगp;
	काष्ठा bfa_fcp_mod_s *fcp = BFA_FCP_MOD(bfa);

	/*
	 * If throttle value from flash is alपढ़ोy in effect after driver is
	 * loaded then until next load, always वापस current value instead
	 * of actual flash value
	 */
	अगर (!fcp->throttle_update_required)
		वापस (u16)fcp->num_ioim_reqs;

	पंचांगp = bfa_dconf_पढ़ो_data_valid(bfa) ? bfa_fcpim_पढ़ो_throttle(bfa) : 0;
	अगर (!पंचांगp || (पंचांगp > drv_cfg_param))
		पंचांगp = drv_cfg_param;

	वापस पंचांगp;
पूर्ण

bfa_status_t
bfa_fcpim_ग_लिखो_throttle(काष्ठा bfa_s *bfa, u16 value)
अणु
	अगर (!bfa_dconf_get_min_cfg(bfa)) अणु
		BFA_DCONF_MOD(bfa)->dconf->throttle_cfg.value = value;
		BFA_DCONF_MOD(bfa)->dconf->throttle_cfg.is_valid = 1;
		वापस BFA_STATUS_OK;
	पूर्ण

	वापस BFA_STATUS_FAILED;
पूर्ण

u16
bfa_fcpim_पढ़ो_throttle(काष्ठा bfa_s *bfa)
अणु
	काष्ठा bfa_throttle_cfg_s *throttle_cfg =
			&(BFA_DCONF_MOD(bfa)->dconf->throttle_cfg);

	वापस ((!bfa_dconf_get_min_cfg(bfa)) ?
	       ((throttle_cfg->is_valid == 1) ? (throttle_cfg->value) : 0) : 0);
पूर्ण

bfa_status_t
bfa_fcpim_throttle_set(काष्ठा bfa_s *bfa, u16 value)
अणु
	/* in min cfg no commands should run. */
	अगर ((bfa_dconf_get_min_cfg(bfa) == BFA_TRUE) ||
	    (!bfa_dconf_पढ़ो_data_valid(bfa)))
		वापस BFA_STATUS_FAILED;

	bfa_fcpim_ग_लिखो_throttle(bfa, value);

	वापस bfa_dconf_update(bfa);
पूर्ण

bfa_status_t
bfa_fcpim_throttle_get(काष्ठा bfa_s *bfa, व्योम *buf)
अणु
	काष्ठा bfa_fcpim_s *fcpim = BFA_FCPIM(bfa);
	काष्ठा bfa_defs_fcpim_throttle_s throttle;

	अगर ((bfa_dconf_get_min_cfg(bfa) == BFA_TRUE) ||
	    (!bfa_dconf_पढ़ो_data_valid(bfa)))
		वापस BFA_STATUS_FAILED;

	स_रखो(&throttle, 0, माप(काष्ठा bfa_defs_fcpim_throttle_s));

	throttle.cur_value = (u16)(fcpim->fcp->num_ioim_reqs);
	throttle.cfg_value = bfa_fcpim_पढ़ो_throttle(bfa);
	अगर (!throttle.cfg_value)
		throttle.cfg_value = throttle.cur_value;
	throttle.max_value = (u16)(fcpim->fcp->max_ioim_reqs);
	स_नकल(buf, &throttle, माप(काष्ठा bfa_defs_fcpim_throttle_s));

	वापस BFA_STATUS_OK;
पूर्ण
