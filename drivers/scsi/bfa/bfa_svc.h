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

#अगर_अघोषित __BFA_SVC_H__
#घोषणा __BFA_SVC_H__

#समावेश "bfa_cs.h"
#समावेश "bfi_ms.h"


/*
 * Scatter-gather DMA related defines
 */
#घोषणा BFA_SGPG_MIN	(16)
#घोषणा BFA_SGPG_MAX	(8192)

/*
 * Alignment macro क्रम SG page allocation
 */
#घोषणा BFA_SGPG_ROUNDUP(_l) (((_l) + (माप(काष्ठा bfi_sgpg_s) - 1))	\
			      & ~(माप(काष्ठा bfi_sgpg_s) - 1))

काष्ठा bfa_sgpg_wqe_s अणु
	काष्ठा list_head qe;	/*  queue sg page element	*/
	पूर्णांक	nsgpg;		/*  pages to be allocated	*/
	पूर्णांक	nsgpg_total;	/*  total pages required	*/
	व्योम	(*cbfn) (व्योम *cbarg);	/*  callback function	*/
	व्योम	*cbarg;		/*  callback arg		*/
	काष्ठा list_head sgpg_q;	/*  queue of alloced sgpgs	*/
पूर्ण;

काष्ठा bfa_sgpg_s अणु
	काष्ठा list_head  qe;	/*  queue sg page element	*/
	काष्ठा bfi_sgpg_s *sgpg;	/*  va of SG page		*/
	जोड़ bfi_addr_u sgpg_pa;	/*  pa of SG page		*/
पूर्ण;

/*
 * Given number of SG elements, BFA_SGPG_NPAGE() वापसs the number of
 * SG pages required.
 */
#घोषणा BFA_SGPG_NPAGE(_nsges)  (((_nsges) / BFI_SGPG_DATA_SGES) + 1)

/* Max SGPG dma segs required */
#घोषणा BFA_SGPG_DMA_SEGS	\
	BFI_MEM_DMA_NSEGS(BFA_SGPG_MAX, (uपूर्णांक32_t)माप(काष्ठा bfi_sgpg_s))

काष्ठा bfa_sgpg_mod_s अणु
	काष्ठा bfa_s *bfa;
	पूर्णांक		num_sgpgs;	/*  number of SG pages		*/
	पूर्णांक		मुक्त_sgpgs;	/*  number of मुक्त SG pages	*/
	काष्ठा list_head	sgpg_q;		/*  queue of मुक्त SG pages */
	काष्ठा list_head	sgpg_रुको_q;	/*  रुको queue क्रम SG pages */
	काष्ठा bfa_mem_dma_s	dma_seg[BFA_SGPG_DMA_SEGS];
	काष्ठा bfa_mem_kva_s	kva_seg;
पूर्ण;
#घोषणा BFA_SGPG_MOD(__bfa)	(&(__bfa)->modules.sgpg_mod)
#घोषणा BFA_MEM_SGPG_KVA(__bfa) (&(BFA_SGPG_MOD(__bfa)->kva_seg))

bfa_status_t bfa_sgpg_दो_स्मृति(काष्ठा bfa_s *bfa, काष्ठा list_head *sgpg_q,
			     पूर्णांक nsgpgs);
व्योम bfa_sgpg_mमुक्त(काष्ठा bfa_s *bfa, काष्ठा list_head *sgpg_q, पूर्णांक nsgpgs);
व्योम bfa_sgpg_winit(काष्ठा bfa_sgpg_wqe_s *wqe,
		    व्योम (*cbfn) (व्योम *cbarg), व्योम *cbarg);
व्योम bfa_sgpg_रुको(काष्ठा bfa_s *bfa, काष्ठा bfa_sgpg_wqe_s *wqe, पूर्णांक nsgpgs);
व्योम bfa_sgpg_wcancel(काष्ठा bfa_s *bfa, काष्ठा bfa_sgpg_wqe_s *wqe);


/*
 * FCXP related defines
 */
#घोषणा BFA_FCXP_MIN		(1)
#घोषणा BFA_FCXP_MAX		(256)
#घोषणा BFA_FCXP_MAX_IBUF_SZ	(2 * 1024 + 256)
#घोषणा BFA_FCXP_MAX_LBUF_SZ	(4 * 1024 + 256)

/* Max FCXP dma segs required */
#घोषणा BFA_FCXP_DMA_SEGS						\
	BFI_MEM_DMA_NSEGS(BFA_FCXP_MAX,					\
		(u32)BFA_FCXP_MAX_IBUF_SZ + BFA_FCXP_MAX_LBUF_SZ)

काष्ठा bfa_fcxp_mod_s अणु
	काष्ठा bfa_s      *bfa;		/* backpoपूर्णांकer to BFA */
	काष्ठा bfa_fcxp_s *fcxp_list;	/* array of FCXPs */
	u16	num_fcxps;	/* max num FCXP requests */
	काष्ठा list_head fcxp_req_मुक्त_q; /* मुक्त FCXPs used क्रम sending req */
	काष्ठा list_head fcxp_rsp_मुक्त_q; /* मुक्त FCXPs used क्रम sending req */
	काष्ठा list_head fcxp_active_q;	/* active FCXPs */
	काष्ठा list_head req_रुको_q;	/* रुको queue क्रम मुक्त req_fcxp */
	काष्ठा list_head rsp_रुको_q;	/* रुको queue क्रम मुक्त rsp_fcxp */
	काष्ठा list_head fcxp_req_unused_q;	/* unused req_fcxps */
	काष्ठा list_head fcxp_rsp_unused_q;	/* unused rsp_fcxps */
	u32	req_pld_sz;
	u32	rsp_pld_sz;
	काष्ठा bfa_mem_dma_s dma_seg[BFA_FCXP_DMA_SEGS];
	काष्ठा bfa_mem_kva_s kva_seg;
पूर्ण;

#घोषणा BFA_FCXP_MOD(__bfa)		(&(__bfa)->modules.fcxp_mod)
#घोषणा BFA_FCXP_FROM_TAG(__mod, __tag)	(&(__mod)->fcxp_list[__tag])
#घोषणा BFA_MEM_FCXP_KVA(__bfa) (&(BFA_FCXP_MOD(__bfa)->kva_seg))

प्रकार व्योम    (*fcxp_send_cb_t) (काष्ठा bfa_s *ioc, काष्ठा bfa_fcxp_s *fcxp,
				   व्योम *cb_arg, bfa_status_t req_status,
				   u32 rsp_len, u32 resid_len,
				   काष्ठा fchs_s *rsp_fchs);

प्रकार u64 (*bfa_fcxp_get_sgaddr_t) (व्योम *bfad_fcxp, पूर्णांक sgeid);
प्रकार u32 (*bfa_fcxp_get_sglen_t) (व्योम *bfad_fcxp, पूर्णांक sgeid);
प्रकार व्योम (*bfa_cb_fcxp_send_t) (व्योम *bfad_fcxp, काष्ठा bfa_fcxp_s *fcxp,
				    व्योम *cbarg, क्रमागत bfa_status req_status,
				    u32 rsp_len, u32 resid_len,
				    काष्ठा fchs_s *rsp_fchs);
प्रकार व्योम (*bfa_fcxp_alloc_cbfn_t) (व्योम *cbarg, काष्ठा bfa_fcxp_s *fcxp);



/*
 * Inक्रमmation needed क्रम a FCXP request
 */
काष्ठा bfa_fcxp_req_info_s अणु
	काष्ठा bfa_rport_s *bfa_rport;
					/* Poपूर्णांकer to the bfa rport that was
					 * वापसed from bfa_rport_create().
					 * This could be left शून्य क्रम WKA or
					 * क्रम FCXP पूर्णांकeractions beक्रमe the
					 * rport nexus is established
					 */
	काष्ठा fchs_s	fchs;	/*  request FC header काष्ठाure */
	u8		cts;	/*  continuous sequence */
	u8		class;	/*  FC class क्रम the request/response */
	u16	max_frmsz;	/*  max send frame size */
	u16	vf_id;	/*  vsan tag अगर applicable */
	u8		lp_tag;	/*  lport tag */
	u32	req_tot_len;	/*  request payload total length */
पूर्ण;

काष्ठा bfa_fcxp_rsp_info_s अणु
	काष्ठा fchs_s	rsp_fchs;
				/* Response frame's FC header will
				 * be sent back in this field */
	u8		rsp_समयout;
				/* समयout in seconds, 0-no response */
	u8		rsvd2[3];
	u32	rsp_maxlen;	/*  max response length expected */
पूर्ण;

काष्ठा bfa_fcxp_s अणु
	काष्ठा list_head	qe;		/*  fcxp queue element */
	bfa_sm_t	sm;		/*  state machine */
	व्योम		*caller;	/*  driver or fcs */
	काष्ठा bfa_fcxp_mod_s *fcxp_mod;
	/*  back poपूर्णांकer to fcxp mod */
	u16	fcxp_tag;	/*  पूर्णांकernal tag */
	काष्ठा bfa_fcxp_req_info_s req_info;
	/*  request info */
	काष्ठा bfa_fcxp_rsp_info_s rsp_info;
	/*  response info */
	u8	use_ireqbuf;	/*  use पूर्णांकernal req buf */
	u8		use_irspbuf;	/*  use पूर्णांकernal rsp buf */
	u32	nreq_sgles;	/*  num request SGLEs */
	u32	nrsp_sgles;	/*  num response SGLEs */
	काष्ठा list_head req_sgpg_q;	/*  SG pages क्रम request buf */
	काष्ठा list_head req_sgpg_wqe;	/*  रुको queue क्रम req SG page */
	काष्ठा list_head rsp_sgpg_q;	/*  SG pages क्रम response buf */
	काष्ठा list_head rsp_sgpg_wqe;	/*  रुको queue क्रम rsp SG page */

	bfa_fcxp_get_sgaddr_t req_sga_cbfn;
	/*  SG elem addr user function */
	bfa_fcxp_get_sglen_t req_sglen_cbfn;
	/*  SG elem len user function */
	bfa_fcxp_get_sgaddr_t rsp_sga_cbfn;
	/*  SG elem addr user function */
	bfa_fcxp_get_sglen_t rsp_sglen_cbfn;
	/*  SG elem len user function */
	bfa_cb_fcxp_send_t send_cbfn;   /*  send completion callback */
	व्योम		*send_cbarg;	/*  callback arg */
	काष्ठा bfa_sge_s   req_sge[BFA_FCXP_MAX_SGES];
	/*  req SG elems */
	काष्ठा bfa_sge_s   rsp_sge[BFA_FCXP_MAX_SGES];
	/*  rsp SG elems */
	u8		rsp_status;	/*  comp: rsp status */
	u32	rsp_len;	/*  comp: actual response len */
	u32	residue_len;	/*  comp: residual rsp length */
	काष्ठा fchs_s	rsp_fchs;	/*  comp: response fchs */
	काष्ठा bfa_cb_qe_s    hcb_qe;	/*  comp: callback qelem */
	काष्ठा bfa_reqq_रुको_s	reqq_wqe;
	bfa_boolean_t	reqq_रुकोing;
	bfa_boolean_t	req_rsp;	/* Used to track req/rsp fcxp */
पूर्ण;

काष्ठा bfa_fcxp_wqe_s अणु
	काष्ठा list_head		qe;
	bfa_fcxp_alloc_cbfn_t	alloc_cbfn;
	व्योम		*alloc_cbarg;
	व्योम		*caller;
	काष्ठा bfa_s	*bfa;
	पूर्णांक		nreq_sgles;
	पूर्णांक		nrsp_sgles;
	bfa_fcxp_get_sgaddr_t	req_sga_cbfn;
	bfa_fcxp_get_sglen_t	req_sglen_cbfn;
	bfa_fcxp_get_sgaddr_t	rsp_sga_cbfn;
	bfa_fcxp_get_sglen_t	rsp_sglen_cbfn;
पूर्ण;

#घोषणा BFA_FCXP_REQ_PLD(_fcxp)		(bfa_fcxp_get_reqbuf(_fcxp))
#घोषणा BFA_FCXP_RSP_FCHS(_fcxp)	(&((_fcxp)->rsp_info.fchs))
#घोषणा BFA_FCXP_RSP_PLD(_fcxp)		(bfa_fcxp_get_rspbuf(_fcxp))

#घोषणा BFA_FCXP_REQ_PLD_PA(_fcxp)					      \
	bfa_mem_get_dmabuf_pa((_fcxp)->fcxp_mod, (_fcxp)->fcxp_tag,	      \
		(_fcxp)->fcxp_mod->req_pld_sz + (_fcxp)->fcxp_mod->rsp_pld_sz)

/* fcxp_buf = req_buf + rsp_buf :- add req_buf_sz to get to rsp_buf */
#घोषणा BFA_FCXP_RSP_PLD_PA(_fcxp)					       \
	(bfa_mem_get_dmabuf_pa((_fcxp)->fcxp_mod, (_fcxp)->fcxp_tag,	       \
	      (_fcxp)->fcxp_mod->req_pld_sz + (_fcxp)->fcxp_mod->rsp_pld_sz) + \
	      (_fcxp)->fcxp_mod->req_pld_sz)

व्योम	bfa_fcxp_isr(काष्ठा bfa_s *bfa, काष्ठा bfi_msg_s *msg);


/*
 * RPORT related defines
 */
क्रमागत bfa_rport_event अणु
	BFA_RPORT_SM_CREATE	= 1,	/*  rport create event          */
	BFA_RPORT_SM_DELETE	= 2,	/*  deleting an existing rport  */
	BFA_RPORT_SM_ONLINE	= 3,	/*  rport is online             */
	BFA_RPORT_SM_OFFLINE	= 4,	/*  rport is offline            */
	BFA_RPORT_SM_FWRSP	= 5,	/*  firmware response           */
	BFA_RPORT_SM_HWFAIL	= 6,	/*  IOC h/w failure             */
	BFA_RPORT_SM_QOS_SCN	= 7,	/*  QoS SCN from firmware       */
	BFA_RPORT_SM_SET_SPEED	= 8,	/*  Set Rport Speed             */
	BFA_RPORT_SM_QRESUME	= 9,	/*  space in requeue queue      */
पूर्ण;

#घोषणा BFA_RPORT_MIN	4

काष्ठा bfa_rport_mod_s अणु
	काष्ठा bfa_rport_s *rps_list;	/*  list of rports	*/
	काष्ठा list_head	rp_मुक्त_q;	/*  मुक्त bfa_rports	*/
	काष्ठा list_head	rp_active_q;	/*  मुक्त bfa_rports	*/
	काष्ठा list_head	rp_unused_q;	/*  unused bfa rports  */
	u16	num_rports;	/*  number of rports	*/
	काष्ठा bfa_mem_kva_s	kva_seg;
पूर्ण;

#घोषणा BFA_RPORT_MOD(__bfa)	(&(__bfa)->modules.rport_mod)
#घोषणा BFA_MEM_RPORT_KVA(__bfa) (&(BFA_RPORT_MOD(__bfa)->kva_seg))

/*
 * Convert rport tag to RPORT
 */
#घोषणा BFA_RPORT_FROM_TAG(__bfa, _tag)				\
	(BFA_RPORT_MOD(__bfa)->rps_list +			\
	 ((_tag) & (BFA_RPORT_MOD(__bfa)->num_rports - 1)))

/*
 * रक्षित functions
 */
व्योम	bfa_rport_isr(काष्ठा bfa_s *bfa, काष्ठा bfi_msg_s *msg);
व्योम	bfa_rport_res_recfg(काष्ठा bfa_s *bfa, u16 num_rport_fw);

/*
 *	BFA rport inक्रमmation.
 */
काष्ठा bfa_rport_info_s अणु
	u16	max_frmsz;	/*  max rcv pdu size		    */
	u32	pid:24,	/*  remote port ID		    */
		lp_tag:8;	/*  tag			    */
	u32	local_pid:24,	/*  local port ID		    */
		cisc:8;	/*  CIRO supported		    */
	u8	fc_class;	/*  supported FC classes. क्रमागत fc_cos */
	u8	vf_en;		/*  भव fabric enable	    */
	u16	vf_id;		/*  भव fabric ID		    */
	क्रमागत bfa_port_speed speed;	/*  Rport's current speed	    */
पूर्ण;

/*
 * BFA rport data काष्ठाure
 */
काष्ठा bfa_rport_s अणु
	काष्ठा list_head	qe;	/*  queue element		    */
	bfa_sm_t	sm;		/*  state machine		    */
	काष्ठा bfa_s	*bfa;		/*  backpoपूर्णांकer to BFA		    */
	व्योम		*rport_drv;	/*  fcs/driver rport object	    */
	u16	fw_handle;	/*  firmware rport handle	    */
	u16	rport_tag;	/*  BFA rport tag		    */
	u8	lun_mask;	/*  LUN mask flag		    */
	काष्ठा bfa_rport_info_s rport_info; /*  rport info from fcs/driver */
	काष्ठा bfa_reqq_रुको_s reqq_रुको; /*  to रुको क्रम room in reqq     */
	काष्ठा bfa_cb_qe_s hcb_qe;	/*  BFA callback qelem		    */
	काष्ठा bfa_rport_hal_stats_s stats; /*  BFA rport statistics	    */
	काष्ठा bfa_rport_qos_attr_s qos_attr;
	जोड़ a अणु
		bfa_status_t	status;	/*  f/w status */
		व्योम		*fw_msg; /*  QoS scn event		    */
	पूर्ण event_arg;
पूर्ण;
#घोषणा BFA_RPORT_FC_COS(_rport)	((_rport)->rport_info.fc_class)


/*
 * UF - unsolicited receive related defines
 */

#घोषणा BFA_UF_MIN	(4)
#घोषणा BFA_UF_MAX	(256)

काष्ठा bfa_uf_s अणु
	काष्ठा list_head	qe;	/*  queue element		*/
	काष्ठा bfa_s		*bfa;	/*  bfa instance		*/
	u16	uf_tag;		/*  identअगरying tag fw msgs	*/
	u16	vf_id;
	u16	src_rport_handle;
	u16	rsvd;
	u8		*data_ptr;
	u16	data_len;	/*  actual receive length	*/
	u16	pb_len;		/*  posted buffer length	*/
	व्योम		*buf_kva;	/*  buffer भव address	*/
	u64	buf_pa;		/*  buffer physical address	*/
	काष्ठा bfa_cb_qe_s hcb_qe;	/*  comp: BFA comp qelem	*/
	काष्ठा bfa_sge_s sges[BFI_SGE_INLINE_MAX];
पूर्ण;

/*
 *      Callback prototype क्रम unsolicited frame receive handler.
 *
 * @param[in]           cbarg           callback arg क्रम receive handler
 * @param[in]           uf              unsolicited frame descriptor
 *
 * @वापस None
 */
प्रकार व्योम (*bfa_cb_uf_recv_t) (व्योम *cbarg, काष्ठा bfa_uf_s *uf);

#घोषणा BFA_UF_BUFSZ	(2 * 1024 + 256)

काष्ठा bfa_uf_buf_s अणु
	u8	d[BFA_UF_BUFSZ];
पूर्ण;

#घोषणा BFA_PER_UF_DMA_SZ	\
	(u32)BFA_ROUNDUP(माप(काष्ठा bfa_uf_buf_s), BFA_DMA_ALIGN_SZ)

/* Max UF dma segs required */
#घोषणा BFA_UF_DMA_SEGS BFI_MEM_DMA_NSEGS(BFA_UF_MAX, BFA_PER_UF_DMA_SZ)

काष्ठा bfa_uf_mod_s अणु
	काष्ठा bfa_s *bfa;		/*  back poपूर्णांकer to BFA */
	काष्ठा bfa_uf_s *uf_list;	/*  array of UFs */
	u16	num_ufs;	/*  num unsolicited rx frames */
	काष्ठा list_head	uf_मुक्त_q;	/*  मुक्त UFs */
	काष्ठा list_head	uf_posted_q;	/*  UFs posted to IOC */
	काष्ठा list_head	uf_unused_q;	/*  unused UF's */
	काष्ठा bfi_uf_buf_post_s *uf_buf_posts;
	/*  pre-built UF post msgs */
	bfa_cb_uf_recv_t ufrecv;	/*  uf recv handler function */
	व्योम		*cbarg;		/*  uf receive handler arg */
	काष्ठा bfa_mem_dma_s	dma_seg[BFA_UF_DMA_SEGS];
	काष्ठा bfa_mem_kva_s	kva_seg;
पूर्ण;

#घोषणा BFA_UF_MOD(__bfa)	(&(__bfa)->modules.uf_mod)
#घोषणा BFA_MEM_UF_KVA(__bfa)	(&(BFA_UF_MOD(__bfa)->kva_seg))

#घोषणा ufm_pbs_pa(_uभ_शेष, _uftag)					\
	bfa_mem_get_dmabuf_pa(_uभ_शेष, _uftag, BFA_PER_UF_DMA_SZ)

व्योम	bfa_uf_isr(काष्ठा bfa_s *bfa, काष्ठा bfi_msg_s *msg);
व्योम	bfa_uf_res_recfg(काष्ठा bfa_s *bfa, u16 num_uf_fw);

/*
 * LPS - bfa lport login/logout service पूर्णांकerface
 */
काष्ठा bfa_lps_s अणु
	काष्ठा list_head	qe;	/*  queue element		*/
	काष्ठा bfa_s	*bfa;		/*  parent bfa instance	*/
	bfa_sm_t	sm;		/*  finite state machine	*/
	u8		bfa_tag;	/*  lport tag		*/
	u8		fw_tag;		/*  lport fw tag                */
	u8		reqq;		/*  lport request queue	*/
	u8		alpa;		/*  ALPA क्रम loop topologies	*/
	u32	lp_pid;		/*  lport port ID		*/
	bfa_boolean_t	fdisc;		/*  snd FDISC instead of FLOGI	*/
	bfa_boolean_t	auth_en;	/*  enable authentication	*/
	bfa_boolean_t	auth_req;	/*  authentication required	*/
	bfa_boolean_t	npiv_en;	/*  NPIV is allowed by peer	*/
	bfa_boolean_t	fport;		/*  attached peer is F_PORT	*/
	bfa_boolean_t	brcd_चयन;	/*  attached peer is brcd sw	*/
	bfa_status_t	status;		/*  login status		*/
	u16		pdusz;		/*  max receive PDU size	*/
	u16		pr_bbcred;	/*  BB_CREDIT from peer		*/
	u8		lsrjt_rsn;	/*  LSRJT reason		*/
	u8		lsrjt_expl;	/*  LSRJT explanation		*/
	u8		lun_mask;	/*  LUN mask flag		*/
	wwn_t		pwwn;		/*  port wwn of lport		*/
	wwn_t		nwwn;		/*  node wwn of lport		*/
	wwn_t		pr_pwwn;	/*  port wwn of lport peer	*/
	wwn_t		pr_nwwn;	/*  node wwn of lport peer	*/
	mac_t		lp_mac;		/*  fpma/spma MAC क्रम lport	*/
	mac_t		fcf_mac;	/*  FCF MAC of lport		*/
	काष्ठा bfa_reqq_रुको_s	wqe;	/*  request रुको queue element	*/
	व्योम		*uarg;		/*  user callback arg		*/
	काष्ठा bfa_cb_qe_s hcb_qe;	/*  comp: callback qelem	*/
	काष्ठा bfi_lps_login_rsp_s *loginrsp;
	bfa_eproto_status_t ext_status;
पूर्ण;

काष्ठा bfa_lps_mod_s अणु
	काष्ठा list_head		lps_मुक्त_q;
	काष्ठा list_head		lps_active_q;
	काष्ठा list_head		lps_login_q;
	काष्ठा bfa_lps_s	*lps_arr;
	पूर्णांक			num_lps;
	काष्ठा bfa_mem_kva_s	kva_seg;
पूर्ण;

#घोषणा BFA_LPS_MOD(__bfa)		(&(__bfa)->modules.lps_mod)
#घोषणा BFA_LPS_FROM_TAG(__mod, __tag)	(&(__mod)->lps_arr[__tag])
#घोषणा BFA_MEM_LPS_KVA(__bfa)	(&(BFA_LPS_MOD(__bfa)->kva_seg))

/*
 * बाह्यal functions
 */
व्योम	bfa_lps_isr(काष्ठा bfa_s *bfa, काष्ठा bfi_msg_s *msg);


/*
 * FCPORT related defines
 */

#घोषणा BFA_FCPORT(_bfa)	(&((_bfa)->modules.port))

/*
 * Link notअगरication data काष्ठाure
 */
काष्ठा bfa_fcport_ln_s अणु
	काष्ठा bfa_fcport_s	*fcport;
	bfa_sm_t		sm;
	काष्ठा bfa_cb_qe_s	ln_qe;	/*  BFA callback queue elem क्रम ln */
	क्रमागत bfa_port_linkstate ln_event; /*  ln event क्रम callback */
पूर्ण;

काष्ठा bfa_fcport_trunk_s अणु
	काष्ठा bfa_trunk_attr_s	attr;
पूर्ण;

/*
 * BFA FC port data काष्ठाure
 */
काष्ठा bfa_fcport_s अणु
	काष्ठा bfa_s		*bfa;	/*  parent BFA instance */
	bfa_sm_t		sm;	/*  port state machine */
	wwn_t			nwwn;	/*  node wwn of physical port */
	wwn_t			pwwn;	/*  port wwn of physical oprt */
	क्रमागत bfa_port_speed speed_sup;
	/*  supported speeds */
	क्रमागत bfa_port_speed speed;	/*  current speed */
	क्रमागत bfa_port_topology topology;	/*  current topology */
	u8			rsvd[3];
	u8			myalpa;	/*  my ALPA in LOOP topology */
	u8			alpabm_valid; /* alpa biपंचांगap valid or not */
	काष्ठा fc_alpabm_s	alpabm;	/* alpa biपंचांगap */
	काष्ठा bfa_port_cfg_s	cfg;	/*  current port configuration */
	bfa_boolean_t		use_flash_cfg; /* get port cfg from flash */
	काष्ठा bfa_qos_attr_s  qos_attr;   /* QoS Attributes */
	काष्ठा bfa_qos_vc_attr_s qos_vc_attr;  /*  VC info from ELP */
	काष्ठा bfa_reqq_रुको_s	reqq_रुको;
	/*  to रुको क्रम room in reqq */
	काष्ठा bfa_reqq_रुको_s	svcreq_रुको;
	/*  to रुको क्रम room in reqq */
	काष्ठा bfa_reqq_रुको_s	stats_reqq_रुको;
	/*  to रुको क्रम room in reqq (stats) */
	व्योम			*event_cbarg;
	व्योम			(*event_cbfn) (व्योम *cbarg,
					       क्रमागत bfa_port_linkstate event);
	जोड़ अणु
		जोड़ bfi_fcport_i2h_msg_u i2hmsg;
	पूर्ण event_arg;
	व्योम			*bfad;	/*  BFA driver handle */
	काष्ठा bfa_fcport_ln_s	ln; /*  Link Notअगरication */
	काष्ठा bfa_cb_qe_s	hcb_qe;	/*  BFA callback queue elem */
	काष्ठा bfa_समयr_s	समयr;	/*  समयr */
	u32		msgtag;	/*  fimrware msg tag क्रम reply */
	u8			*stats_kva;
	u64		stats_pa;
	जोड़ bfa_fcport_stats_u *stats;
	bfa_status_t		stats_status; /*  stats/statsclr status */
	काष्ठा list_head	stats_pending_q;
	काष्ठा list_head	statsclr_pending_q;
	bfa_boolean_t		stats_qfull;
	समय64_t		stats_reset_समय; /*  stats reset समय stamp */
	bfa_boolean_t		diag_busy; /*  diag busy status */
	bfa_boolean_t		beacon; /*  port beacon status */
	bfa_boolean_t		link_e2e_beacon; /*  link beacon status */
	काष्ठा bfa_fcport_trunk_s trunk;
	u16		fcoe_vlan;
	काष्ठा bfa_mem_dma_s	fcport_dma;
	bfa_boolean_t		stats_dma_पढ़ोy;
	काष्ठा bfa_bbcr_attr_s	bbcr_attr;
	क्रमागत bfa_fec_state_s	fec_state;
पूर्ण;

#घोषणा BFA_FCPORT_MOD(__bfa)	(&(__bfa)->modules.fcport)
#घोषणा BFA_MEM_FCPORT_DMA(__bfa) (&(BFA_FCPORT_MOD(__bfa)->fcport_dma))

/*
 * रक्षित functions
 */
व्योम bfa_fcport_init(काष्ठा bfa_s *bfa);
व्योम bfa_fcport_isr(काष्ठा bfa_s *bfa, काष्ठा bfi_msg_s *msg);

/*
 * bfa fcport API functions
 */
bfa_status_t bfa_fcport_enable(काष्ठा bfa_s *bfa);
bfa_status_t bfa_fcport_disable(काष्ठा bfa_s *bfa);
bfa_status_t bfa_fcport_cfg_speed(काष्ठा bfa_s *bfa,
				  क्रमागत bfa_port_speed speed);
क्रमागत bfa_port_speed bfa_fcport_get_speed(काष्ठा bfa_s *bfa);
bfa_status_t bfa_fcport_cfg_topology(काष्ठा bfa_s *bfa,
				     क्रमागत bfa_port_topology topo);
क्रमागत bfa_port_topology bfa_fcport_get_topology(काष्ठा bfa_s *bfa);
क्रमागत bfa_port_topology bfa_fcport_get_cfg_topology(काष्ठा bfa_s *bfa);
bfa_status_t bfa_fcport_cfg_hardalpa(काष्ठा bfa_s *bfa, u8 alpa);
bfa_boolean_t bfa_fcport_get_hardalpa(काष्ठा bfa_s *bfa, u8 *alpa);
u8 bfa_fcport_get_myalpa(काष्ठा bfa_s *bfa);
bfa_status_t bfa_fcport_clr_hardalpa(काष्ठा bfa_s *bfa);
bfa_status_t bfa_fcport_cfg_maxfrsize(काष्ठा bfa_s *bfa, u16 maxsize);
u16 bfa_fcport_get_maxfrsize(काष्ठा bfa_s *bfa);
u8 bfa_fcport_get_rx_bbcredit(काष्ठा bfa_s *bfa);
व्योम bfa_fcport_get_attr(काष्ठा bfa_s *bfa, काष्ठा bfa_port_attr_s *attr);
wwn_t bfa_fcport_get_wwn(काष्ठा bfa_s *bfa, bfa_boolean_t node);
व्योम bfa_fcport_event_रेजिस्टर(काष्ठा bfa_s *bfa,
			व्योम (*event_cbfn) (व्योम *cbarg,
			क्रमागत bfa_port_linkstate event), व्योम *event_cbarg);
bfa_boolean_t bfa_fcport_is_disabled(काष्ठा bfa_s *bfa);
bfa_boolean_t bfa_fcport_is_dport(काष्ठा bfa_s *bfa);
bfa_boolean_t bfa_fcport_is_ddport(काष्ठा bfa_s *bfa);
bfa_status_t bfa_fcport_set_qos_bw(काष्ठा bfa_s *bfa,
				   काष्ठा bfa_qos_bw_s *qos_bw);
क्रमागत bfa_port_speed bfa_fcport_get_ratelim_speed(काष्ठा bfa_s *bfa);

व्योम bfa_fcport_set_tx_bbcredit(काष्ठा bfa_s *bfa, u16 tx_bbcredit);
bfa_boolean_t     bfa_fcport_is_ratelim(काष्ठा bfa_s *bfa);
व्योम bfa_fcport_beacon(व्योम *dev, bfa_boolean_t beacon,
			bfa_boolean_t link_e2e_beacon);
bfa_boolean_t	bfa_fcport_is_linkup(काष्ठा bfa_s *bfa);
bfa_status_t bfa_fcport_get_stats(काष्ठा bfa_s *bfa,
			काष्ठा bfa_cb_pending_q_s *cb);
bfa_status_t bfa_fcport_clear_stats(काष्ठा bfa_s *bfa,
			काष्ठा bfa_cb_pending_q_s *cb);
bfa_boolean_t bfa_fcport_is_qos_enabled(काष्ठा bfa_s *bfa);
bfa_boolean_t bfa_fcport_is_trunk_enabled(काष्ठा bfa_s *bfa);
व्योम bfa_fcport_dportenable(काष्ठा bfa_s *bfa);
व्योम bfa_fcport_dportdisable(काष्ठा bfa_s *bfa);
bfa_status_t bfa_fcport_is_pbcdisabled(काष्ठा bfa_s *bfa);
व्योम bfa_fcport_cfg_faa(काष्ठा bfa_s *bfa, u8 state);
bfa_status_t bfa_fcport_cfg_bbcr(काष्ठा bfa_s *bfa,
			bfa_boolean_t on_off, u8 bb_scn);
bfa_status_t bfa_fcport_get_bbcr_attr(काष्ठा bfa_s *bfa,
			काष्ठा bfa_bbcr_attr_s *bbcr_attr);

/*
 * bfa rport API functions
 */
काष्ठा bfa_rport_s *bfa_rport_create(काष्ठा bfa_s *bfa, व्योम *rport_drv);
व्योम bfa_rport_online(काष्ठा bfa_rport_s *rport,
		      काष्ठा bfa_rport_info_s *rport_info);
व्योम bfa_rport_speed(काष्ठा bfa_rport_s *rport, क्रमागत bfa_port_speed speed);
व्योम bfa_cb_rport_online(व्योम *rport);
व्योम bfa_cb_rport_offline(व्योम *rport);
व्योम bfa_cb_rport_qos_scn_flowid(व्योम *rport,
				 काष्ठा bfa_rport_qos_attr_s old_qos_attr,
				 काष्ठा bfa_rport_qos_attr_s new_qos_attr);
व्योम bfa_cb_rport_scn_online(काष्ठा bfa_s *bfa);
व्योम bfa_cb_rport_scn_offline(काष्ठा bfa_s *bfa);
व्योम bfa_cb_rport_scn_no_dev(व्योम *rp);
व्योम bfa_cb_rport_qos_scn_prio(व्योम *rport,
			       काष्ठा bfa_rport_qos_attr_s old_qos_attr,
			       काष्ठा bfa_rport_qos_attr_s new_qos_attr);

/*
 *	Rport LUN masking related
 */
#घोषणा BFA_RPORT_TAG_INVALID	0xffff
#घोषणा BFA_LP_TAG_INVALID	0xff
व्योम	bfa_rport_set_lunmask(काष्ठा bfa_s *bfa, काष्ठा bfa_rport_s *rp);
व्योम	bfa_rport_unset_lunmask(काष्ठा bfa_s *bfa, काष्ठा bfa_rport_s *rp);

/*
 * bfa fcxp API functions
 */
काष्ठा bfa_fcxp_s *bfa_fcxp_req_rsp_alloc(व्योम *bfad_fcxp, काष्ठा bfa_s *bfa,
				  पूर्णांक nreq_sgles, पूर्णांक nrsp_sgles,
				  bfa_fcxp_get_sgaddr_t get_req_sga,
				  bfa_fcxp_get_sglen_t get_req_sglen,
				  bfa_fcxp_get_sgaddr_t get_rsp_sga,
				  bfa_fcxp_get_sglen_t get_rsp_sglen,
				  bfa_boolean_t req);
व्योम bfa_fcxp_req_rsp_alloc_रुको(काष्ठा bfa_s *bfa, काष्ठा bfa_fcxp_wqe_s *wqe,
				bfa_fcxp_alloc_cbfn_t alloc_cbfn,
				व्योम *cbarg, व्योम *bfad_fcxp,
				पूर्णांक nreq_sgles, पूर्णांक nrsp_sgles,
				bfa_fcxp_get_sgaddr_t get_req_sga,
				bfa_fcxp_get_sglen_t get_req_sglen,
				bfa_fcxp_get_sgaddr_t get_rsp_sga,
				bfa_fcxp_get_sglen_t get_rsp_sglen,
				bfa_boolean_t req);
व्योम bfa_fcxp_walloc_cancel(काष्ठा bfa_s *bfa,
			    काष्ठा bfa_fcxp_wqe_s *wqe);
व्योम bfa_fcxp_discard(काष्ठा bfa_fcxp_s *fcxp);

व्योम *bfa_fcxp_get_reqbuf(काष्ठा bfa_fcxp_s *fcxp);
व्योम *bfa_fcxp_get_rspbuf(काष्ठा bfa_fcxp_s *fcxp);

व्योम bfa_fcxp_मुक्त(काष्ठा bfa_fcxp_s *fcxp);

व्योम bfa_fcxp_send(काष्ठा bfa_fcxp_s *fcxp, काष्ठा bfa_rport_s *rport,
		   u16 vf_id, u8 lp_tag,
		   bfa_boolean_t cts, क्रमागत fc_cos cos,
		   u32 reqlen, काष्ठा fchs_s *fchs,
		   bfa_cb_fcxp_send_t cbfn,
		   व्योम *cbarg,
		   u32 rsp_maxlen, u8 rsp_समयout);
bfa_status_t bfa_fcxp_पात(काष्ठा bfa_fcxp_s *fcxp);
u32 bfa_fcxp_get_reqbufsz(काष्ठा bfa_fcxp_s *fcxp);
u32 bfa_fcxp_get_maxrsp(काष्ठा bfa_s *bfa);
व्योम bfa_fcxp_res_recfg(काष्ठा bfa_s *bfa, u16 num_fcxp_fw);

अटल अंतरभूत व्योम *
bfa_uf_get_frmbuf(काष्ठा bfa_uf_s *uf)
अणु
	वापस uf->data_ptr;
पूर्ण

अटल अंतरभूत   u16
bfa_uf_get_frmlen(काष्ठा bfa_uf_s *uf)
अणु
	वापस uf->data_len;
पूर्ण

/*
 * bfa uf API functions
 */
व्योम bfa_uf_recv_रेजिस्टर(काष्ठा bfa_s *bfa, bfa_cb_uf_recv_t ufrecv,
			  व्योम *cbarg);
व्योम bfa_uf_मुक्त(काष्ठा bfa_uf_s *uf);

/*
 * bfa lport service api
 */

u32 bfa_lps_get_max_vport(काष्ठा bfa_s *bfa);
काष्ठा bfa_lps_s *bfa_lps_alloc(काष्ठा bfa_s *bfa);
व्योम bfa_lps_delete(काष्ठा bfa_lps_s *lps);
व्योम bfa_lps_flogi(काष्ठा bfa_lps_s *lps, व्योम *uarg, u8 alpa,
		   u16 pdusz, wwn_t pwwn, wwn_t nwwn,
		   bfa_boolean_t auth_en);
व्योम bfa_lps_fdisc(काष्ठा bfa_lps_s *lps, व्योम *uarg, u16 pdusz,
		   wwn_t pwwn, wwn_t nwwn);
व्योम bfa_lps_fdisclogo(काष्ठा bfa_lps_s *lps);
व्योम bfa_lps_set_n2n_pid(काष्ठा bfa_lps_s *lps, u32 n2n_pid);
u8 bfa_lps_get_fwtag(काष्ठा bfa_s *bfa, u8 lp_tag);
u32 bfa_lps_get_base_pid(काष्ठा bfa_s *bfa);
u8 bfa_lps_get_tag_from_pid(काष्ठा bfa_s *bfa, u32 pid);
व्योम bfa_cb_lps_flogi_comp(व्योम *bfad, व्योम *uarg, bfa_status_t status);
व्योम bfa_cb_lps_flogo_comp(व्योम *bfad, व्योम *uarg);
व्योम bfa_cb_lps_fdisc_comp(व्योम *bfad, व्योम *uarg, bfa_status_t status);
व्योम bfa_cb_lps_fdisclogo_comp(व्योम *bfad, व्योम *uarg);
व्योम bfa_cb_lps_cvl_event(व्योम *bfad, व्योम *uarg);

/* FAA specअगरic APIs */
bfa_status_t bfa_faa_query(काष्ठा bfa_s *bfa, काष्ठा bfa_faa_attr_s *attr,
			bfa_cb_iocfc_t cbfn, व्योम *cbarg);

/*
 *	FC DIAG data काष्ठाure
 */
काष्ठा bfa_fcdiag_qtest_s अणु
	काष्ठा bfa_diag_qtest_result_s *result;
	bfa_cb_diag_t	cbfn;
	व्योम		*cbarg;
	काष्ठा bfa_समयr_s	समयr;
	u32	status;
	u32	count;
	u8	lock;
	u8	queue;
	u8	all;
	u8	समयr_active;
पूर्ण;

काष्ठा bfa_fcdiag_lb_s अणु
	bfa_cb_diag_t   cbfn;
	व्योम            *cbarg;
	व्योम            *result;
	bfa_boolean_t   lock;
	u32        status;
पूर्ण;

काष्ठा bfa_dport_s अणु
	काष्ठा bfa_s	*bfa;		/* Back poपूर्णांकer to BFA	*/
	bfa_sm_t	sm;		/* finite state machine */
	काष्ठा bfa_reqq_रुको_s reqq_रुको;
	bfa_cb_diag_t	cbfn;
	व्योम		*cbarg;
	जोड़ bfi_diag_dport_msg_u i2hmsg;
	u8		test_state;	/* क्रमागत dport_test_state  */
	u8		dynamic;	/* boolean_t  */
	u8		rsvd[2];
	u32		lpcnt;
	u32		payload;	/* user defined payload pattern */
	wwn_t		rp_pwwn;
	wwn_t		rp_nwwn;
	काष्ठा bfa_diag_dport_result_s result;
पूर्ण;

काष्ठा bfa_fcdiag_s अणु
	काष्ठा bfa_s    *bfa;           /* Back poपूर्णांकer to BFA */
	काष्ठा bfa_trc_mod_s   *trcmod;
	काष्ठा bfa_fcdiag_lb_s lb;
	काष्ठा bfa_fcdiag_qtest_s qtest;
	काष्ठा bfa_dport_s	dport;
पूर्ण;

#घोषणा BFA_FCDIAG_MOD(__bfa)	(&(__bfa)->modules.fcdiag)

व्योम	bfa_fcdiag_पूर्णांकr(काष्ठा bfa_s *bfa, काष्ठा bfi_msg_s *msg);

bfa_status_t	bfa_fcdiag_loopback(काष्ठा bfa_s *bfa,
				क्रमागत bfa_port_opmode opmode,
				क्रमागत bfa_port_speed speed, u32 lpcnt, u32 pat,
				काष्ठा bfa_diag_loopback_result_s *result,
				bfa_cb_diag_t cbfn, व्योम *cbarg);
bfa_status_t	bfa_fcdiag_queuetest(काष्ठा bfa_s *bfa, u32 ignore,
			u32 queue, काष्ठा bfa_diag_qtest_result_s *result,
			bfa_cb_diag_t cbfn, व्योम *cbarg);
bfa_status_t	bfa_fcdiag_lb_is_running(काष्ठा bfa_s *bfa);
bfa_status_t	bfa_dport_enable(काष्ठा bfa_s *bfa, u32 lpcnt, u32 pat,
					bfa_cb_diag_t cbfn, व्योम *cbarg);
bfa_status_t	bfa_dport_disable(काष्ठा bfa_s *bfa, bfa_cb_diag_t cbfn,
				  व्योम *cbarg);
bfa_status_t	bfa_dport_start(काष्ठा bfa_s *bfa, u32 lpcnt, u32 pat,
				bfa_cb_diag_t cbfn, व्योम *cbarg);
bfa_status_t	bfa_dport_show(काष्ठा bfa_s *bfa,
				काष्ठा bfa_diag_dport_result_s *result);

#पूर्ण_अगर /* __BFA_SVC_H__ */
