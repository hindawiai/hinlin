<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2005-2014 Brocade Communications Systems, Inc.
 * Copyright (c) 2014- QLogic Corporation.
 * All rights reserved
 * www.qlogic.com
 *
 * Linux driver क्रम QLogic BR-series Fibre Channel Host Bus Adapter.
 */

#अगर_अघोषित __BFA_FCPIM_H__
#घोषणा __BFA_FCPIM_H__

#समावेश "bfa.h"
#समावेश "bfa_svc.h"
#समावेश "bfi_ms.h"
#समावेश "bfa_defs_svc.h"
#समावेश "bfa_cs.h"

/* FCP module related definitions */
#घोषणा BFA_IO_MAX	BFI_IO_MAX
#घोषणा BFA_FWTIO_MAX	2000

काष्ठा bfa_fcp_mod_s;
काष्ठा bfa_iotag_s अणु
	काष्ठा list_head	qe;	/* queue element	*/
	u16	tag;			/* FW IO tag		*/
पूर्ण;

काष्ठा bfa_itn_s अणु
	bfa_isr_func_t isr;
पूर्ण;

व्योम bfa_itn_create(काष्ठा bfa_s *bfa, काष्ठा bfa_rport_s *rport,
		व्योम (*isr)(काष्ठा bfa_s *bfa, काष्ठा bfi_msg_s *m));
व्योम bfa_itn_isr(काष्ठा bfa_s *bfa, काष्ठा bfi_msg_s *m);
व्योम bfa_iotag_attach(काष्ठा bfa_fcp_mod_s *fcp);
व्योम bfa_fcp_res_recfg(काष्ठा bfa_s *bfa, u16 num_ioim_fw, u16 max_ioim_fw);

#घोषणा BFA_FCP_MOD(_hal)	(&(_hal)->modules.fcp_mod)
#घोषणा BFA_MEM_FCP_KVA(__bfa)	(&(BFA_FCP_MOD(__bfa)->kva_seg))
#घोषणा BFA_IOTAG_FROM_TAG(_fcp, _tag)	\
	(&(_fcp)->iotag_arr[(_tag & BFA_IOIM_IOTAG_MASK)])
#घोषणा BFA_ITN_FROM_TAG(_fcp, _tag)	\
	((_fcp)->itn_arr + ((_tag) & ((_fcp)->num_itns - 1)))
#घोषणा BFA_SNSINFO_FROM_TAG(_fcp, _tag) \
	bfa_mem_get_dmabuf_kva(_fcp, (_tag & BFA_IOIM_IOTAG_MASK),	\
	BFI_IOIM_SNSLEN)


#घोषणा BFA_ITNIM_MIN   32
#घोषणा BFA_ITNIM_MAX   1024

#घोषणा BFA_IOIM_MIN	8
#घोषणा BFA_IOIM_MAX	2000

#घोषणा BFA_TSKIM_MIN   4
#घोषणा BFA_TSKIM_MAX   512
#घोषणा BFA_FCPIM_PATHTOV_DEF	(30 * 1000)	/* in millisecs */
#घोषणा BFA_FCPIM_PATHTOV_MAX	(90 * 1000)	/* in millisecs */


#घोषणा bfa_itnim_ioprofile_update(__itnim, __index)			\
	(__itnim->ioprofile.iocomps[__index]++)

#घोषणा BFA_IOIM_RETRY_TAG_OFFSET 11
#घोषणा BFA_IOIM_IOTAG_MASK 0x07ff /* 2K IOs */
#घोषणा BFA_IOIM_RETRY_MAX 7

/* Buckets are are 512 bytes to 2MB */
अटल अंतरभूत u32
bfa_ioim_get_index(u32 n) अणु
	पूर्णांक pos = 0;
	अगर (n >= (1UL)<<22)
		वापस BFA_IOBUCKET_MAX - 1;
	n >>= 8;
	अगर (n >= (1UL)<<16) अणु
		n >>= 16;
		pos += 16;
	पूर्ण
	अगर (n >= 1 << 8) अणु
		n >>= 8;
		pos += 8;
	पूर्ण
	अगर (n >= 1 << 4) अणु
		n >>= 4;
		pos += 4;
	पूर्ण
	अगर (n >= 1 << 2) अणु
		n >>= 2;
		pos += 2;
	पूर्ण
	अगर (n >= 1 << 1)
		pos += 1;

	वापस (n == 0) ? (0) : pos;
पूर्ण

/*
 * क्रमward declarations
 */
काष्ठा bfa_ioim_s;
काष्ठा bfa_tskim_s;
काष्ठा bfad_ioim_s;
काष्ठा bfad_tskim_s;

प्रकार व्योम    (*bfa_fcpim_profile_t) (काष्ठा bfa_ioim_s *ioim);

काष्ठा bfa_fcpim_s अणु
	काष्ठा bfa_s		*bfa;
	काष्ठा bfa_fcp_mod_s	*fcp;
	काष्ठा bfa_itnim_s	*itnim_arr;
	काष्ठा bfa_ioim_s	*ioim_arr;
	काष्ठा bfa_ioim_sp_s	*ioim_sp_arr;
	काष्ठा bfa_tskim_s	*tskim_arr;
	पूर्णांक			num_itnims;
	पूर्णांक			num_tskim_reqs;
	u32			path_tov;
	u16			q_depth;
	u8			reqq;		/*  Request queue to be used */
	काष्ठा list_head	itnim_q;	/*  queue of active itnim */
	काष्ठा list_head	ioim_resमुक्त_q; /*  IOs रुकोing क्रम f/w */
	काष्ठा list_head	ioim_comp_q;	/*  IO global comp Q	*/
	काष्ठा list_head	tskim_मुक्त_q;
	काष्ठा list_head	tskim_unused_q;	/* Unused tskim Q */
	u32			ios_active;	/*  current active IOs	*/
	u32			delay_comp;
	काष्ठा bfa_fcpim_del_itn_stats_s del_itn_stats;
	bfa_boolean_t		ioredirect;
	bfa_boolean_t		io_profile;
	समय64_t		io_profile_start_समय;
	bfa_fcpim_profile_t     profile_comp;
	bfa_fcpim_profile_t     profile_start;
पूर्ण;

/* Max FCP dma segs required */
#घोषणा BFA_FCP_DMA_SEGS	BFI_IOIM_SNSBUF_SEGS

काष्ठा bfa_fcp_mod_s अणु
	काष्ठा bfa_s		*bfa;
	काष्ठा list_head	iotag_ioim_मुक्त_q;	/* मुक्त IO resources */
	काष्ठा list_head	iotag_tio_मुक्त_q;	/* मुक्त IO resources */
	काष्ठा list_head	iotag_unused_q;	/* unused IO resources*/
	काष्ठा bfa_iotag_s	*iotag_arr;
	काष्ठा bfa_itn_s	*itn_arr;
	पूर्णांक			max_ioim_reqs;
	पूर्णांक			num_ioim_reqs;
	पूर्णांक			num_fwtio_reqs;
	पूर्णांक			num_itns;
	काष्ठा bfa_dma_s	snsbase[BFA_FCP_DMA_SEGS];
	काष्ठा bfa_fcpim_s	fcpim;
	काष्ठा bfa_mem_dma_s	dma_seg[BFA_FCP_DMA_SEGS];
	काष्ठा bfa_mem_kva_s	kva_seg;
	पूर्णांक			throttle_update_required;
पूर्ण;

/*
 * BFA IO (initiator mode)
 */
काष्ठा bfa_ioim_s अणु
	काष्ठा list_head	qe;		/*  queue elememt	*/
	bfa_sm_t		sm;		/*  BFA ioim state machine */
	काष्ठा bfa_s		*bfa;		/*  BFA module	*/
	काष्ठा bfa_fcpim_s	*fcpim;		/*  parent fcpim module */
	काष्ठा bfa_itnim_s	*itnim;		/*  i-t-n nexus क्रम this IO  */
	काष्ठा bfad_ioim_s	*dio;		/*  driver IO handle	*/
	u16			iotag;		/*  FWI IO tag	*/
	u16			पात_tag;	/*  unqiue पात request tag */
	u16			nsges;		/*  number of SG elements */
	u16			nsgpgs;		/*  number of SG pages	*/
	काष्ठा bfa_sgpg_s	*sgpg;		/*  first SG page	*/
	काष्ठा list_head	sgpg_q;		/*  allocated SG pages	*/
	काष्ठा bfa_cb_qe_s	hcb_qe;		/*  bfa callback qelem	*/
	bfa_cb_cbfn_t		io_cbfn;	/*  IO completion handler */
	काष्ठा bfa_ioim_sp_s	*iosp;		/*  slow-path IO handling */
	u8			reqq;		/*  Request queue क्रम I/O */
	u8			mode;		/*  IO is passthrough or not */
	u64			start_समय;	/*  IO's Profile start val */
पूर्ण;

काष्ठा bfa_ioim_sp_s अणु
	काष्ठा bfi_msg_s	comp_rspmsg;	/*  IO comp f/w response */
	काष्ठा bfa_sgpg_wqe_s	sgpg_wqe;	/*  रुकोq elem क्रम sgpg	*/
	काष्ठा bfa_reqq_रुको_s	reqq_रुको;	/*  to रुको क्रम room in reqq */
	bfa_boolean_t		पात_explicit;	/*  पातed by OS	*/
	काष्ठा bfa_tskim_s	*tskim;		/*  Relevant TM cmd	*/
पूर्ण;

/*
 * BFA Task management command (initiator mode)
 */
काष्ठा bfa_tskim_s अणु
	काष्ठा list_head	qe;
	bfa_sm_t		sm;
	काष्ठा bfa_s		*bfa;	/*  BFA module  */
	काष्ठा bfa_fcpim_s	*fcpim;	/*  parent fcpim module	*/
	काष्ठा bfa_itnim_s	*itnim;	/*  i-t-n nexus क्रम this IO  */
	काष्ठा bfad_tskim_s	*dtsk;  /*  driver task mgmt cmnd	*/
	bfa_boolean_t		notअगरy;	/*  notअगरy itnim on TM comp  */
	काष्ठा scsi_lun		lun;	/*  lun अगर applicable	*/
	क्रमागत fcp_पंचांग_cmnd	पंचांग_cmnd; /*  task management command  */
	u16			tsk_tag; /*  FWI IO tag	*/
	u8			tsecs;	/*  समयout in seconds	*/
	काष्ठा bfa_reqq_रुको_s  reqq_रुको;   /*  to रुको क्रम room in reqq */
	काष्ठा list_head	io_q;	/*  queue of affected IOs	*/
	काष्ठा bfa_wc_s		wc;	/*  रुकोing counter	*/
	काष्ठा bfa_cb_qe_s	hcb_qe;	/*  bfa callback qelem	*/
	क्रमागत bfi_tskim_status   tsk_status;  /*  TM status	*/
पूर्ण;

/*
 * BFA i-t-n (initiator mode)
 */
काष्ठा bfa_itnim_s अणु
	काष्ठा list_head	qe;	/*  queue element	*/
	bfa_sm_t		sm;	/*  i-t-n im BFA state machine  */
	काष्ठा bfa_s		*bfa;	/*  bfa instance	*/
	काष्ठा bfa_rport_s	*rport;	/*  bfa rport	*/
	व्योम			*ditn;	/*  driver i-t-n काष्ठाure	*/
	काष्ठा bfi_mhdr_s	mhdr;	/*  pre-built mhdr	*/
	u8			msg_no;	/*  itnim/rport firmware handle */
	u8			reqq;	/*  CQ क्रम requests	*/
	काष्ठा bfa_cb_qe_s	hcb_qe;	/*  bfa callback qelem	*/
	काष्ठा list_head pending_q;	/*  queue of pending IO requests */
	काष्ठा list_head io_q;		/*  queue of active IO requests */
	काष्ठा list_head io_cleanup_q;	/*  IO being cleaned up	*/
	काष्ठा list_head tsk_q;		/*  queue of active TM commands */
	काष्ठा list_head  delay_comp_q; /*  queue of failed inflight cmds */
	bfa_boolean_t   seq_rec;	/*  SQER supported	*/
	bfa_boolean_t   is_online;	/*  itnim is ONLINE क्रम IO	*/
	bfa_boolean_t   iotov_active;	/*  IO TOV समयr is active	 */
	काष्ठा bfa_wc_s	wc;		/*  रुकोing counter	*/
	काष्ठा bfa_समयr_s समयr;	/*  pending IO TOV	 */
	काष्ठा bfa_reqq_रुको_s reqq_रुको; /*  to रुको क्रम room in reqq */
	काष्ठा bfa_fcpim_s *fcpim;	/*  fcpim module	*/
	काष्ठा bfa_itnim_iostats_s	stats;
	काष्ठा bfa_itnim_ioprofile_s  ioprofile;
पूर्ण;

#घोषणा bfa_itnim_is_online(_itnim) ((_itnim)->is_online)
#घोषणा BFA_FCPIM(_hal)	(&(_hal)->modules.fcp_mod.fcpim)
#घोषणा BFA_IOIM_TAG_2_ID(_iotag)	((_iotag) & BFA_IOIM_IOTAG_MASK)
#घोषणा BFA_IOIM_FROM_TAG(_fcpim, _iotag)	\
	(&fcpim->ioim_arr[(_iotag & BFA_IOIM_IOTAG_MASK)])
#घोषणा BFA_TSKIM_FROM_TAG(_fcpim, _पंचांगtag)	\
	(&fcpim->tskim_arr[_पंचांगtag & (fcpim->num_tskim_reqs - 1)])

#घोषणा bfa_io_profile_start_समय(_bfa)	\
	((_bfa)->modules.fcp_mod.fcpim.io_profile_start_समय)
#घोषणा bfa_fcpim_get_io_profile(_bfa)	\
	((_bfa)->modules.fcp_mod.fcpim.io_profile)
#घोषणा bfa_ioim_update_iotag(__ioim) करो अणु				\
	uपूर्णांक16_t k = (__ioim)->iotag >> BFA_IOIM_RETRY_TAG_OFFSET;	\
	k++; (__ioim)->iotag &= BFA_IOIM_IOTAG_MASK;			\
	(__ioim)->iotag |= k << BFA_IOIM_RETRY_TAG_OFFSET;		\
पूर्ण जबतक (0)

अटल अंतरभूत bfa_boolean_t
bfa_ioim_maxretry_reached(काष्ठा bfa_ioim_s *ioim)
अणु
	uपूर्णांक16_t k = ioim->iotag >> BFA_IOIM_RETRY_TAG_OFFSET;
	अगर (k < BFA_IOIM_RETRY_MAX)
		वापस BFA_FALSE;
	वापस BFA_TRUE;
पूर्ण

/*
 * function prototypes
 */
व्योम	bfa_ioim_attach(काष्ठा bfa_fcpim_s *fcpim);
व्योम	bfa_ioim_isr(काष्ठा bfa_s *bfa, काष्ठा bfi_msg_s *msg);
व्योम	bfa_ioim_good_comp_isr(काष्ठा bfa_s *bfa,
					काष्ठा bfi_msg_s *msg);
व्योम	bfa_ioim_cleanup(काष्ठा bfa_ioim_s *ioim);
व्योम	bfa_ioim_cleanup_पंचांग(काष्ठा bfa_ioim_s *ioim,
					काष्ठा bfa_tskim_s *tskim);
व्योम	bfa_ioim_iocdisable(काष्ठा bfa_ioim_s *ioim);
व्योम	bfa_ioim_tov(काष्ठा bfa_ioim_s *ioim);

व्योम	bfa_tskim_attach(काष्ठा bfa_fcpim_s *fcpim);
व्योम	bfa_tskim_isr(काष्ठा bfa_s *bfa, काष्ठा bfi_msg_s *msg);
व्योम	bfa_tskim_ioकरोne(काष्ठा bfa_tskim_s *tskim);
व्योम	bfa_tskim_iocdisable(काष्ठा bfa_tskim_s *tskim);
व्योम	bfa_tskim_cleanup(काष्ठा bfa_tskim_s *tskim);
व्योम	bfa_tskim_res_recfg(काष्ठा bfa_s *bfa, u16 num_tskim_fw);

व्योम	bfa_itnim_meminfo(काष्ठा bfa_iocfc_cfg_s *cfg, u32 *km_len);
व्योम	bfa_itnim_attach(काष्ठा bfa_fcpim_s *fcpim);
व्योम	bfa_itnim_iocdisable(काष्ठा bfa_itnim_s *itnim);
व्योम	bfa_itnim_isr(काष्ठा bfa_s *bfa, काष्ठा bfi_msg_s *msg);
व्योम	bfa_itnim_ioकरोne(काष्ठा bfa_itnim_s *itnim);
व्योम	bfa_itnim_tskकरोne(काष्ठा bfa_itnim_s *itnim);
bfa_boolean_t   bfa_itnim_hold_io(काष्ठा bfa_itnim_s *itnim);

/*
 * bfa fcpim module API functions
 */
व्योम	bfa_fcpim_path_tov_set(काष्ठा bfa_s *bfa, u16 path_tov);
u16	bfa_fcpim_path_tov_get(काष्ठा bfa_s *bfa);
u16	bfa_fcpim_qdepth_get(काष्ठा bfa_s *bfa);
bfa_status_t bfa_fcpim_port_iostats(काष्ठा bfa_s *bfa,
			काष्ठा bfa_itnim_iostats_s *stats, u8 lp_tag);
व्योम bfa_fcpim_add_stats(काष्ठा bfa_itnim_iostats_s *fcpim_stats,
			काष्ठा bfa_itnim_iostats_s *itnim_stats);
bfa_status_t bfa_fcpim_profile_on(काष्ठा bfa_s *bfa, समय64_t समय);
bfa_status_t bfa_fcpim_profile_off(काष्ठा bfa_s *bfa);

#घोषणा bfa_fcpim_ioredirect_enabled(__bfa)				\
	(((काष्ठा bfa_fcpim_s *)(BFA_FCPIM(__bfa)))->ioredirect)

#घोषणा bfa_fcpim_get_next_reqq(__bfa, __qid)				\
अणु									\
	काष्ठा bfa_fcpim_s *__fcpim = BFA_FCPIM(__bfa);      \
	__fcpim->reqq++;						\
	__fcpim->reqq &= (BFI_IOC_MAX_CQS - 1);      \
	*(__qid) = __fcpim->reqq;					\
पूर्ण

#घोषणा bfa_iocfc_map_msg_to_qid(__msg, __qid)				\
	*(__qid) = (u8)((__msg) & (BFI_IOC_MAX_CQS - 1));
/*
 * bfa itnim API functions
 */
काष्ठा bfa_itnim_s *bfa_itnim_create(काष्ठा bfa_s *bfa,
		काष्ठा bfa_rport_s *rport, व्योम *itnim);
व्योम bfa_itnim_delete(काष्ठा bfa_itnim_s *itnim);
व्योम bfa_itnim_online(काष्ठा bfa_itnim_s *itnim, bfa_boolean_t seq_rec);
व्योम bfa_itnim_offline(काष्ठा bfa_itnim_s *itnim);
व्योम bfa_itnim_clear_stats(काष्ठा bfa_itnim_s *itnim);
bfa_status_t bfa_itnim_get_ioprofile(काष्ठा bfa_itnim_s *itnim,
			काष्ठा bfa_itnim_ioprofile_s *ioprofile);

#घोषणा bfa_itnim_get_reqq(__ioim) (((काष्ठा bfa_ioim_s *)__ioim)->itnim->reqq)

/*
 * BFA completion callback क्रम bfa_itnim_online().
 */
व्योम	bfa_cb_itnim_online(व्योम *itnim);

/*
 * BFA completion callback क्रम bfa_itnim_offline().
 */
व्योम	bfa_cb_itnim_offline(व्योम *itnim);
व्योम	bfa_cb_itnim_tov_begin(व्योम *itnim);
व्योम	bfa_cb_itnim_tov(व्योम *itnim);

/*
 * BFA notअगरication to FCS/driver क्रम second level error recovery.
 * Atleast one I/O request has समयकरोut and target is unresponsive to
 * repeated पात requests. Second level error recovery should be initiated
 * by starting implicit logout and recovery procedures.
 */
व्योम	bfa_cb_itnim_sler(व्योम *itnim);

/*
 * bfa ioim API functions
 */
काष्ठा bfa_ioim_s	*bfa_ioim_alloc(काष्ठा bfa_s *bfa,
					काष्ठा bfad_ioim_s *dio,
					काष्ठा bfa_itnim_s *itnim,
					u16 nsgles);

व्योम		bfa_ioim_मुक्त(काष्ठा bfa_ioim_s *ioim);
व्योम		bfa_ioim_start(काष्ठा bfa_ioim_s *ioim);
bfa_status_t	bfa_ioim_पात(काष्ठा bfa_ioim_s *ioim);
व्योम		bfa_ioim_delayed_comp(काष्ठा bfa_ioim_s *ioim,
				      bfa_boolean_t iotov);
/*
 * I/O completion notअगरication.
 *
 * @param[in]		dio			driver IO काष्ठाure
 * @param[in]		io_status		IO completion status
 * @param[in]		scsi_status		SCSI status वापसed by target
 * @param[in]		sns_len			SCSI sense length, 0 अगर none
 * @param[in]		sns_info		SCSI sense data, अगर any
 * @param[in]		residue			Residual length
 *
 * @वापस None
 */
व्योम bfa_cb_ioim_करोne(व्योम *bfad, काष्ठा bfad_ioim_s *dio,
			क्रमागत bfi_ioim_status io_status,
			u8 scsi_status, पूर्णांक sns_len,
			u8 *sns_info, s32 residue);

/*
 * I/O good completion notअगरication.
 */
व्योम bfa_cb_ioim_good_comp(व्योम *bfad, काष्ठा bfad_ioim_s *dio);

/*
 * I/O पात completion notअगरication
 */
व्योम bfa_cb_ioim_पात(व्योम *bfad, काष्ठा bfad_ioim_s *dio);

/*
 * bfa tskim API functions
 */
काष्ठा bfa_tskim_s *bfa_tskim_alloc(काष्ठा bfa_s *bfa,
			काष्ठा bfad_tskim_s *dtsk);
व्योम bfa_tskim_मुक्त(काष्ठा bfa_tskim_s *tskim);
व्योम bfa_tskim_start(काष्ठा bfa_tskim_s *tskim,
			काष्ठा bfa_itnim_s *itnim, काष्ठा scsi_lun lun,
			क्रमागत fcp_पंचांग_cmnd पंचांग, u8 t_secs);
व्योम bfa_cb_tskim_करोne(व्योम *bfad, काष्ठा bfad_tskim_s *dtsk,
			क्रमागत bfi_tskim_status tsk_status);

व्योम	bfa_fcpim_lunmask_rp_update(काष्ठा bfa_s *bfa, wwn_t lp_wwn,
			wwn_t rp_wwn, u16 rp_tag, u8 lp_tag);
bfa_status_t	bfa_fcpim_lunmask_update(काष्ठा bfa_s *bfa, u32 on_off);
bfa_status_t	bfa_fcpim_lunmask_query(काष्ठा bfa_s *bfa, व्योम *buf);
bfa_status_t	bfa_fcpim_lunmask_delete(काष्ठा bfa_s *bfa, u16 vf_id,
				wwn_t *pwwn, wwn_t rpwwn, काष्ठा scsi_lun lun);
bfa_status_t	bfa_fcpim_lunmask_add(काष्ठा bfa_s *bfa, u16 vf_id,
				wwn_t *pwwn, wwn_t rpwwn, काष्ठा scsi_lun lun);
bfa_status_t	bfa_fcpim_lunmask_clear(काष्ठा bfa_s *bfa);
u16		bfa_fcpim_पढ़ो_throttle(काष्ठा bfa_s *bfa);
bfa_status_t	bfa_fcpim_ग_लिखो_throttle(काष्ठा bfa_s *bfa, u16 value);
bfa_status_t	bfa_fcpim_throttle_set(काष्ठा bfa_s *bfa, u16 value);
bfa_status_t	bfa_fcpim_throttle_get(काष्ठा bfa_s *bfa, व्योम *buf);
u16     bfa_fcpim_get_throttle_cfg(काष्ठा bfa_s *bfa, u16 drv_cfg_param);

#पूर्ण_अगर /* __BFA_FCPIM_H__ */
