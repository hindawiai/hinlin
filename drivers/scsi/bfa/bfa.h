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
#अगर_अघोषित __BFA_H__
#घोषणा __BFA_H__

#समावेश "bfad_drv.h"
#समावेश "bfa_cs.h"
#समावेश "bfa_plog.h"
#समावेश "bfa_defs_svc.h"
#समावेश "bfi.h"
#समावेश "bfa_ioc.h"

काष्ठा bfa_s;

प्रकार व्योम (*bfa_isr_func_t) (काष्ठा bfa_s *bfa, काष्ठा bfi_msg_s *m);
प्रकार व्योम (*bfa_cb_cbfn_status_t) (व्योम *cbarg, bfa_status_t status);

/*
 * Interrupt message handlers
 */
व्योम bfa_isr_unhandled(काष्ठा bfa_s *bfa, काष्ठा bfi_msg_s *m);

/*
 * Request and response queue related defines
 */
#घोषणा BFA_REQQ_NELEMS_MIN	(4)
#घोषणा BFA_RSPQ_NELEMS_MIN	(4)

#घोषणा bfa_reqq_pi(__bfa, __reqq)	((__bfa)->iocfc.req_cq_pi[__reqq])
#घोषणा bfa_reqq_ci(__bfa, __reqq)					\
	(*(u32 *)((__bfa)->iocfc.req_cq_shaकरोw_ci[__reqq].kva))

#घोषणा bfa_reqq_full(__bfa, __reqq)				\
	(((bfa_reqq_pi(__bfa, __reqq) + 1) &			\
	  ((__bfa)->iocfc.cfg.drvcfg.num_reqq_elems - 1)) ==	\
	 bfa_reqq_ci(__bfa, __reqq))

#घोषणा bfa_reqq_next(__bfa, __reqq)					\
	(bfa_reqq_full(__bfa, __reqq) ? शून्य :				\
	 ((व्योम *)((काष्ठा bfi_msg_s *)((__bfa)->iocfc.req_cq_ba[__reqq].kva) \
		   + bfa_reqq_pi((__bfa), (__reqq)))))

#घोषणा bfa_reqq_produce(__bfa, __reqq, __mh)  करो अणु			\
		(__mh).mtag.h2i.qid     = (__bfa)->iocfc.hw_qid[__reqq];\
		(__bfa)->iocfc.req_cq_pi[__reqq]++;			\
		(__bfa)->iocfc.req_cq_pi[__reqq] &=			\
			((__bfa)->iocfc.cfg.drvcfg.num_reqq_elems - 1); \
		ग_लिखोl((__bfa)->iocfc.req_cq_pi[__reqq],		\
			(__bfa)->iocfc.bfa_regs.cpe_q_pi[__reqq]);	\
		पूर्ण जबतक (0)

#घोषणा bfa_rspq_pi(__bfa, __rspq)					\
	(*(u32 *)((__bfa)->iocfc.rsp_cq_shaकरोw_pi[__rspq].kva))

#घोषणा bfa_rspq_ci(__bfa, __rspq)	((__bfa)->iocfc.rsp_cq_ci[__rspq])
#घोषणा bfa_rspq_elem(__bfa, __rspq, __ci)				\
	(&((काष्ठा bfi_msg_s *)((__bfa)->iocfc.rsp_cq_ba[__rspq].kva))[__ci])

#घोषणा CQ_INCR(__index, __size) करो अणु			\
	(__index)++;					\
	(__index) &= ((__size) - 1);			\
पूर्ण जबतक (0)

/*
 * Circular queue usage assignments
 */
क्रमागत अणु
	BFA_REQQ_IOC	= 0,	/*  all low-priority IOC msgs	*/
	BFA_REQQ_FCXP	= 0,	/*  all FCXP messages		*/
	BFA_REQQ_LPS	= 0,	/*  all lport service msgs	*/
	BFA_REQQ_PORT	= 0,	/*  all port messages		*/
	BFA_REQQ_FLASH	= 0,	/*  क्रम flash module		*/
	BFA_REQQ_DIAG	= 0,	/*  क्रम diag module		*/
	BFA_REQQ_RPORT	= 0,	/*  all port messages		*/
	BFA_REQQ_SBOOT	= 0,	/*  all san boot messages	*/
	BFA_REQQ_QOS_LO	= 1,	/*  all low priority IO	*/
	BFA_REQQ_QOS_MD	= 2,	/*  all medium priority IO	*/
	BFA_REQQ_QOS_HI	= 3,	/*  all high priority IO	*/
पूर्ण;

अटल अंतरभूत व्योम
bfa_reqq_winit(काष्ठा bfa_reqq_रुको_s *wqe, व्योम (*qresume) (व्योम *cbarg),
	       व्योम *cbarg)
अणु
	wqe->qresume = qresume;
	wqe->cbarg = cbarg;
पूर्ण

#घोषणा bfa_reqq(__bfa, __reqq)	(&(__bfa)->reqq_रुकोq[__reqq])

/*
 * अटल अंतरभूत व्योम
 * bfa_reqq_रुको(काष्ठा bfa_s *bfa, पूर्णांक reqq, काष्ठा bfa_reqq_रुको_s *wqe)
 */
#घोषणा bfa_reqq_रुको(__bfa, __reqq, __wqe) करो अणु			\
									\
		काष्ठा list_head *रुकोq = bfa_reqq(__bfa, __reqq);      \
									\
		WARN_ON(((__reqq) >= BFI_IOC_MAX_CQS));			\
		WARN_ON(!((__wqe)->qresume && (__wqe)->cbarg));		\
									\
		list_add_tail(&(__wqe)->qe, रुकोq);      \
	पूर्ण जबतक (0)

#घोषणा bfa_reqq_wcancel(__wqe)	list_del(&(__wqe)->qe)

#घोषणा bfa_cb_queue(__bfa, __hcb_qe, __cbfn, __cbarg) करो अणु	\
		(__hcb_qe)->cbfn  = (__cbfn);      \
		(__hcb_qe)->cbarg = (__cbarg);      \
		(__hcb_qe)->pre_rmv = BFA_FALSE;		\
		list_add_tail(&(__hcb_qe)->qe, &(__bfa)->comp_q);      \
	पूर्ण जबतक (0)

#घोषणा bfa_cb_dequeue(__hcb_qe)	list_del(&(__hcb_qe)->qe)

#घोषणा bfa_cb_queue_once(__bfa, __hcb_qe, __cbfn, __cbarg) करो अणु	\
		(__hcb_qe)->cbfn  = (__cbfn);      \
		(__hcb_qe)->cbarg = (__cbarg);      \
		अगर (!(__hcb_qe)->once) अणु      \
			list_add_tail(&(__hcb_qe)->qe, &(__bfa)->comp_q);      \
			(__hcb_qe)->once = BFA_TRUE;			\
		पूर्ण							\
	पूर्ण जबतक (0)

#घोषणा bfa_cb_queue_status(__bfa, __hcb_qe, __status) करो अणु		\
		(__hcb_qe)->fw_status = (__status);			\
		list_add_tail(&(__hcb_qe)->qe, &(__bfa)->comp_q);	\
पूर्ण जबतक (0)

#घोषणा bfa_cb_queue_करोne(__hcb_qe) करो अणु	\
		(__hcb_qe)->once = BFA_FALSE;	\
	पूर्ण जबतक (0)


/*
 * PCI devices supported by the current BFA
 */
काष्ठा bfa_pciid_s अणु
	u16	device_id;
	u16	venकरोr_id;
पूर्ण;

बाह्य अक्षर     bfa_version[];

काष्ठा bfa_iocfc_regs_s अणु
	व्योम __iomem	*पूर्णांकr_status;
	व्योम __iomem	*पूर्णांकr_mask;
	व्योम __iomem	*cpe_q_pi[BFI_IOC_MAX_CQS];
	व्योम __iomem	*cpe_q_ci[BFI_IOC_MAX_CQS];
	व्योम __iomem	*cpe_q_ctrl[BFI_IOC_MAX_CQS];
	व्योम __iomem	*rme_q_ci[BFI_IOC_MAX_CQS];
	व्योम __iomem	*rme_q_pi[BFI_IOC_MAX_CQS];
	व्योम __iomem	*rme_q_ctrl[BFI_IOC_MAX_CQS];
पूर्ण;

/*
 * MSIX vector handlers
 */
#घोषणा BFA_MSIX_MAX_VECTORS	22
प्रकार व्योम (*bfa_msix_handler_t)(काष्ठा bfa_s *bfa, पूर्णांक vec);
काष्ठा bfa_msix_s अणु
	पूर्णांक	nvecs;
	bfa_msix_handler_t handler[BFA_MSIX_MAX_VECTORS];
पूर्ण;

/*
 * Chip specअगरic पूर्णांकerfaces
 */
काष्ठा bfa_hwअगर_s अणु
	व्योम (*hw_reginit)(काष्ठा bfa_s *bfa);
	व्योम (*hw_reqq_ack)(काष्ठा bfa_s *bfa, पूर्णांक reqq);
	व्योम (*hw_rspq_ack)(काष्ठा bfa_s *bfa, पूर्णांक rspq, u32 ci);
	व्योम (*hw_msix_init)(काष्ठा bfa_s *bfa, पूर्णांक nvecs);
	व्योम (*hw_msix_ctrl_install)(काष्ठा bfa_s *bfa);
	व्योम (*hw_msix_queue_install)(काष्ठा bfa_s *bfa);
	व्योम (*hw_msix_uninstall)(काष्ठा bfa_s *bfa);
	व्योम (*hw_isr_mode_set)(काष्ठा bfa_s *bfa, bfa_boolean_t msix);
	व्योम (*hw_msix_getvecs)(काष्ठा bfa_s *bfa, u32 *vecmap,
				u32 *nvecs, u32 *maxvec);
	व्योम (*hw_msix_get_rme_range) (काष्ठा bfa_s *bfa, u32 *start,
				       u32 *end);
	पूर्णांक	cpe_vec_q0;
	पूर्णांक	rme_vec_q0;
पूर्ण;
प्रकार व्योम (*bfa_cb_iocfc_t) (व्योम *cbarg, क्रमागत bfa_status status);

काष्ठा bfa_faa_cbfn_s अणु
	bfa_cb_iocfc_t	faa_cbfn;
	व्योम		*faa_cbarg;
पूर्ण;

#घोषणा BFA_FAA_ENABLED		1
#घोषणा BFA_FAA_DISABLED	2

/*
 *	FAA attributes
 */
काष्ठा bfa_faa_attr_s अणु
	wwn_t	faa;
	u8	faa_state;
	u8	pwwn_source;
	u8	rsvd[6];
पूर्ण;

काष्ठा bfa_faa_args_s अणु
	काष्ठा bfa_faa_attr_s	*faa_attr;
	काष्ठा bfa_faa_cbfn_s	faa_cb;
	u8			faa_state;
	bfa_boolean_t		busy;
पूर्ण;

काष्ठा bfa_iocfc_s अणु
	bfa_fsm_t		fsm;
	काष्ठा bfa_s		*bfa;
	काष्ठा bfa_iocfc_cfg_s	cfg;
	u32		req_cq_pi[BFI_IOC_MAX_CQS];
	u32		rsp_cq_ci[BFI_IOC_MAX_CQS];
	u8		hw_qid[BFI_IOC_MAX_CQS];
	काष्ठा bfa_cb_qe_s	init_hcb_qe;
	काष्ठा bfa_cb_qe_s	stop_hcb_qe;
	काष्ठा bfa_cb_qe_s	dis_hcb_qe;
	काष्ठा bfa_cb_qe_s	en_hcb_qe;
	काष्ठा bfa_cb_qe_s	stats_hcb_qe;
	bfa_boolean_t		submod_enabled;
	bfa_boolean_t		cb_reqd;	/* Driver call back reqd */
	bfa_status_t		op_status;	/* Status of bfa iocfc op */

	काष्ठा bfa_dma_s	cfg_info;
	काष्ठा bfi_iocfc_cfg_s *cfginfo;
	काष्ठा bfa_dma_s	cfgrsp_dma;
	काष्ठा bfi_iocfc_cfgrsp_s *cfgrsp;
	काष्ठा bfa_dma_s	req_cq_ba[BFI_IOC_MAX_CQS];
	काष्ठा bfa_dma_s	req_cq_shaकरोw_ci[BFI_IOC_MAX_CQS];
	काष्ठा bfa_dma_s	rsp_cq_ba[BFI_IOC_MAX_CQS];
	काष्ठा bfa_dma_s	rsp_cq_shaकरोw_pi[BFI_IOC_MAX_CQS];
	काष्ठा bfa_iocfc_regs_s	bfa_regs;	/*  BFA device रेजिस्टरs */
	काष्ठा bfa_hwअगर_s	hwअगर;
	bfa_cb_iocfc_t		updateq_cbfn; /*  bios callback function */
	व्योम			*updateq_cbarg;	/*  bios callback arg */
	u32	पूर्णांकr_mask;
	काष्ठा bfa_faa_args_s	faa_args;
	काष्ठा bfa_mem_dma_s	ioc_dma;
	काष्ठा bfa_mem_dma_s	iocfc_dma;
	काष्ठा bfa_mem_dma_s	reqq_dma[BFI_IOC_MAX_CQS];
	काष्ठा bfa_mem_dma_s	rspq_dma[BFI_IOC_MAX_CQS];
	काष्ठा bfa_mem_kva_s	kva_seg;
पूर्ण;

#घोषणा BFA_MEM_IOC_DMA(_bfa)		(&((_bfa)->iocfc.ioc_dma))
#घोषणा BFA_MEM_IOCFC_DMA(_bfa)		(&((_bfa)->iocfc.iocfc_dma))
#घोषणा BFA_MEM_REQQ_DMA(_bfa, _qno)	(&((_bfa)->iocfc.reqq_dma[(_qno)]))
#घोषणा BFA_MEM_RSPQ_DMA(_bfa, _qno)	(&((_bfa)->iocfc.rspq_dma[(_qno)]))
#घोषणा BFA_MEM_IOCFC_KVA(_bfa)		(&((_bfa)->iocfc.kva_seg))

#घोषणा bfa_fn_lpu(__bfa)	\
	bfi_fn_lpu(bfa_ioc_pcअगरn(&(__bfa)->ioc), bfa_ioc_portid(&(__bfa)->ioc))
#घोषणा bfa_msix_init(__bfa, __nvecs)					\
	((__bfa)->iocfc.hwअगर.hw_msix_init(__bfa, __nvecs))
#घोषणा bfa_msix_ctrl_install(__bfa)					\
	((__bfa)->iocfc.hwअगर.hw_msix_ctrl_install(__bfa))
#घोषणा bfa_msix_queue_install(__bfa)					\
	((__bfa)->iocfc.hwअगर.hw_msix_queue_install(__bfa))
#घोषणा bfa_msix_uninstall(__bfa)					\
	((__bfa)->iocfc.hwअगर.hw_msix_uninstall(__bfa))
#घोषणा bfa_isr_rspq_ack(__bfa, __queue, __ci)				\
	((__bfa)->iocfc.hwअगर.hw_rspq_ack(__bfa, __queue, __ci))
#घोषणा bfa_isr_reqq_ack(__bfa, __queue) करो अणु				\
	अगर ((__bfa)->iocfc.hwअगर.hw_reqq_ack)				\
		(__bfa)->iocfc.hwअगर.hw_reqq_ack(__bfa, __queue);	\
पूर्ण जबतक (0)
#घोषणा bfa_isr_mode_set(__bfa, __msix) करो अणु				\
	अगर ((__bfa)->iocfc.hwअगर.hw_isr_mode_set)			\
		(__bfa)->iocfc.hwअगर.hw_isr_mode_set(__bfa, __msix);	\
पूर्ण जबतक (0)
#घोषणा bfa_msix_getvecs(__bfa, __vecmap, __nvecs, __maxvec)		\
	((__bfa)->iocfc.hwअगर.hw_msix_getvecs(__bfa, __vecmap,		\
					__nvecs, __maxvec))
#घोषणा bfa_msix_get_rme_range(__bfa, __start, __end)			\
	((__bfa)->iocfc.hwअगर.hw_msix_get_rme_range(__bfa, __start, __end))
#घोषणा bfa_msix(__bfa, __vec)						\
	((__bfa)->msix.handler[__vec](__bfa, __vec))

/*
 * FC specअगरic IOC functions.
 */
व्योम bfa_iocfc_meminfo(काष्ठा bfa_iocfc_cfg_s *cfg,
			काष्ठा bfa_meminfo_s *meminfo,
			काष्ठा bfa_s *bfa);
व्योम bfa_iocfc_attach(काष्ठा bfa_s *bfa, व्योम *bfad,
		      काष्ठा bfa_iocfc_cfg_s *cfg,
		      काष्ठा bfa_pcidev_s *pcidev);
व्योम bfa_iocfc_init(काष्ठा bfa_s *bfa);
व्योम bfa_iocfc_start(काष्ठा bfa_s *bfa);
व्योम bfa_iocfc_stop(काष्ठा bfa_s *bfa);
व्योम bfa_iocfc_isr(व्योम *bfa, काष्ठा bfi_mbmsg_s *msg);
व्योम bfa_iocfc_set_snsbase(काष्ठा bfa_s *bfa, पूर्णांक seg_no, u64 snsbase_pa);
bfa_boolean_t bfa_iocfc_is_operational(काष्ठा bfa_s *bfa);
व्योम bfa_iocfc_reset_queues(काष्ठा bfa_s *bfa);

व्योम bfa_msix_all(काष्ठा bfa_s *bfa, पूर्णांक vec);
व्योम bfa_msix_reqq(काष्ठा bfa_s *bfa, पूर्णांक vec);
व्योम bfa_msix_rspq(काष्ठा bfa_s *bfa, पूर्णांक vec);
व्योम bfa_msix_lpu_err(काष्ठा bfa_s *bfa, पूर्णांक vec);

व्योम bfa_hwcb_reginit(काष्ठा bfa_s *bfa);
व्योम bfa_hwcb_rspq_ack(काष्ठा bfa_s *bfa, पूर्णांक rspq, u32 ci);
व्योम bfa_hwcb_msix_init(काष्ठा bfa_s *bfa, पूर्णांक nvecs);
व्योम bfa_hwcb_msix_ctrl_install(काष्ठा bfa_s *bfa);
व्योम bfa_hwcb_msix_queue_install(काष्ठा bfa_s *bfa);
व्योम bfa_hwcb_msix_uninstall(काष्ठा bfa_s *bfa);
व्योम bfa_hwcb_isr_mode_set(काष्ठा bfa_s *bfa, bfa_boolean_t msix);
व्योम bfa_hwcb_msix_getvecs(काष्ठा bfa_s *bfa, u32 *vecmap, u32 *nvecs,
			   u32 *maxvec);
व्योम bfa_hwcb_msix_get_rme_range(काष्ठा bfa_s *bfa, u32 *start,
				 u32 *end);
व्योम bfa_hwct_reginit(काष्ठा bfa_s *bfa);
व्योम bfa_hwct2_reginit(काष्ठा bfa_s *bfa);
व्योम bfa_hwct_reqq_ack(काष्ठा bfa_s *bfa, पूर्णांक rspq);
व्योम bfa_hwct_rspq_ack(काष्ठा bfa_s *bfa, पूर्णांक rspq, u32 ci);
व्योम bfa_hwct2_rspq_ack(काष्ठा bfa_s *bfa, पूर्णांक rspq, u32 ci);
व्योम bfa_hwct_msix_init(काष्ठा bfa_s *bfa, पूर्णांक nvecs);
व्योम bfa_hwct_msix_ctrl_install(काष्ठा bfa_s *bfa);
व्योम bfa_hwct_msix_queue_install(काष्ठा bfa_s *bfa);
व्योम bfa_hwct_msix_uninstall(काष्ठा bfa_s *bfa);
व्योम bfa_hwct_isr_mode_set(काष्ठा bfa_s *bfa, bfa_boolean_t msix);
व्योम bfa_hwct_msix_getvecs(काष्ठा bfa_s *bfa, u32 *vecmap, u32 *nvecs,
			   u32 *maxvec);
व्योम bfa_hwct_msix_get_rme_range(काष्ठा bfa_s *bfa, u32 *start,
				 u32 *end);
व्योम bfa_iocfc_get_bootwwns(काष्ठा bfa_s *bfa, u8 *nwwns, wwn_t *wwns);
पूर्णांक bfa_iocfc_get_pbc_vports(काष्ठा bfa_s *bfa,
				काष्ठा bfi_pbc_vport_s *pbc_vport);


/*
 *----------------------------------------------------------------------
 *		BFA खुला पूर्णांकerfaces
 *----------------------------------------------------------------------
 */
#घोषणा bfa_stats(_mod, _stats)	((_mod)->stats._stats++)
#घोषणा bfa_ioc_get_stats(__bfa, __ioc_stats)		\
	bfa_ioc_fetch_stats(&(__bfa)->ioc, __ioc_stats)
#घोषणा bfa_ioc_clear_stats(__bfa)		\
	bfa_ioc_clr_stats(&(__bfa)->ioc)
#घोषणा bfa_get_nports(__bfa)			\
	bfa_ioc_get_nports(&(__bfa)->ioc)
#घोषणा bfa_get_adapter_manufacturer(__bfa, __manufacturer)		\
	bfa_ioc_get_adapter_manufacturer(&(__bfa)->ioc, __manufacturer)
#घोषणा bfa_get_adapter_model(__bfa, __model)			\
	bfa_ioc_get_adapter_model(&(__bfa)->ioc, __model)
#घोषणा bfa_get_adapter_serial_num(__bfa, __serial_num)			\
	bfa_ioc_get_adapter_serial_num(&(__bfa)->ioc, __serial_num)
#घोषणा bfa_get_adapter_fw_ver(__bfa, __fw_ver)			\
	bfa_ioc_get_adapter_fw_ver(&(__bfa)->ioc, __fw_ver)
#घोषणा bfa_get_adapter_optrom_ver(__bfa, __optrom_ver)			\
	bfa_ioc_get_adapter_optrom_ver(&(__bfa)->ioc, __optrom_ver)
#घोषणा bfa_get_pci_chip_rev(__bfa, __chip_rev)			\
	bfa_ioc_get_pci_chip_rev(&(__bfa)->ioc, __chip_rev)
#घोषणा bfa_get_ioc_state(__bfa)		\
	bfa_ioc_get_state(&(__bfa)->ioc)
#घोषणा bfa_get_type(__bfa)			\
	bfa_ioc_get_type(&(__bfa)->ioc)
#घोषणा bfa_get_mac(__bfa)			\
	bfa_ioc_get_mac(&(__bfa)->ioc)
#घोषणा bfa_get_mfg_mac(__bfa)			\
	bfa_ioc_get_mfg_mac(&(__bfa)->ioc)
#घोषणा bfa_get_fw_घड़ी_res(__bfa)		\
	((__bfa)->iocfc.cfgrsp->fwcfg.fw_tick_res)

/*
 * lun mask macros वापस शून्य when min cfg is enabled and there is
 * no memory allocated क्रम lunmask.
 */
#घोषणा bfa_get_lun_mask(__bfa)					\
	((&(__bfa)->modules.dconf_mod)->min_cfg) ? शून्य :	\
	 (&(BFA_DCONF_MOD(__bfa)->dconf->lun_mask))

#घोषणा bfa_get_lun_mask_list(_bfa)				\
	((&(_bfa)->modules.dconf_mod)->min_cfg) ? शून्य :	\
	 (bfa_get_lun_mask(_bfa)->lun_list)

#घोषणा bfa_get_lun_mask_status(_bfa)				\
	(((&(_bfa)->modules.dconf_mod)->min_cfg)		\
	 ? BFA_LUNMASK_MINCFG : ((bfa_get_lun_mask(_bfa))->status))

व्योम bfa_get_pciids(काष्ठा bfa_pciid_s **pciids, पूर्णांक *npciids);
व्योम bfa_cfg_get_शेष(काष्ठा bfa_iocfc_cfg_s *cfg);
व्योम bfa_cfg_get_min(काष्ठा bfa_iocfc_cfg_s *cfg);
व्योम bfa_cfg_get_meminfo(काष्ठा bfa_iocfc_cfg_s *cfg,
			काष्ठा bfa_meminfo_s *meminfo,
			काष्ठा bfa_s *bfa);
व्योम bfa_attach(काष्ठा bfa_s *bfa, व्योम *bfad, काष्ठा bfa_iocfc_cfg_s *cfg,
		काष्ठा bfa_meminfo_s *meminfo,
		काष्ठा bfa_pcidev_s *pcidev);
व्योम bfa_detach(काष्ठा bfa_s *bfa);
व्योम bfa_cb_init(व्योम *bfad, bfa_status_t status);
व्योम bfa_cb_updateq(व्योम *bfad, bfa_status_t status);

bfa_boolean_t bfa_पूर्णांकx(काष्ठा bfa_s *bfa);
व्योम bfa_isr_enable(काष्ठा bfa_s *bfa);
व्योम bfa_isr_disable(काष्ठा bfa_s *bfa);

व्योम bfa_comp_deq(काष्ठा bfa_s *bfa, काष्ठा list_head *comp_q);
व्योम bfa_comp_process(काष्ठा bfa_s *bfa, काष्ठा list_head *comp_q);
व्योम bfa_comp_मुक्त(काष्ठा bfa_s *bfa, काष्ठा list_head *comp_q);

प्रकार व्योम (*bfa_cb_ioc_t) (व्योम *cbarg, क्रमागत bfa_status status);
व्योम bfa_iocfc_get_attr(काष्ठा bfa_s *bfa, काष्ठा bfa_iocfc_attr_s *attr);


bfa_status_t bfa_iocfc_israttr_set(काष्ठा bfa_s *bfa,
				   काष्ठा bfa_iocfc_पूर्णांकr_attr_s *attr);

व्योम bfa_iocfc_enable(काष्ठा bfa_s *bfa);
व्योम bfa_iocfc_disable(काष्ठा bfa_s *bfa);
#घोषणा bfa_समयr_start(_bfa, _समयr, _समयrcb, _arg, _समयout)		\
	bfa_समयr_begin(&(_bfa)->समयr_mod, _समयr, _समयrcb, _arg, _समयout)

काष्ठा bfa_cb_pending_q_s अणु
	काष्ठा bfa_cb_qe_s	hcb_qe;
	व्योम			*data;  /* Driver buffer */
पूर्ण;

/* Common macros to operate on pending stats/attr apis */
#घोषणा bfa_pending_q_init(__qe, __cbfn, __cbarg, __data) करो अणु	\
	bfa_q_qe_init(&((__qe)->hcb_qe.qe));			\
	(__qe)->hcb_qe.cbfn = (__cbfn);				\
	(__qe)->hcb_qe.cbarg = (__cbarg);			\
	(__qe)->hcb_qe.pre_rmv = BFA_TRUE;			\
	(__qe)->data = (__data);				\
पूर्ण जबतक (0)

#पूर्ण_अगर /* __BFA_H__ */
