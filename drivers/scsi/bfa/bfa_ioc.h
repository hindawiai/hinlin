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

#अगर_अघोषित __BFA_IOC_H__
#घोषणा __BFA_IOC_H__

#समावेश "bfad_drv.h"
#समावेश "bfa_cs.h"
#समावेश "bfi.h"

#घोषणा BFA_DBG_FWTRC_ENTS	(BFI_IOC_TRC_ENTS)
#घोषणा BFA_DBG_FWTRC_LEN					\
	(BFA_DBG_FWTRC_ENTS * माप(काष्ठा bfa_trc_s) +	\
	(माप(काष्ठा bfa_trc_mod_s) -				\
	BFA_TRC_MAX * माप(काष्ठा bfa_trc_s)))
/*
 * BFA समयr declarations
 */
प्रकार व्योम (*bfa_समयr_cbfn_t)(व्योम *);

/*
 * BFA समयr data काष्ठाure
 */
काष्ठा bfa_समयr_s अणु
	काष्ठा list_head	qe;
	bfa_समयr_cbfn_t समयrcb;
	व्योम		*arg;
	पूर्णांक		समयout;	/* in millisecs */
पूर्ण;

/*
 * Timer module काष्ठाure
 */
काष्ठा bfa_समयr_mod_s अणु
	काष्ठा list_head समयr_q;
पूर्ण;

#घोषणा BFA_TIMER_FREQ 200 /* specअगरied in millisecs */

व्योम bfa_समयr_beat(काष्ठा bfa_समयr_mod_s *mod);
व्योम bfa_समयr_begin(काष्ठा bfa_समयr_mod_s *mod, काष्ठा bfa_समयr_s *समयr,
			bfa_समयr_cbfn_t समयrcb, व्योम *arg,
			अचिन्हित पूर्णांक समयout);
व्योम bfa_समयr_stop(काष्ठा bfa_समयr_s *समयr);

/*
 * Generic Scatter Gather Element used by driver
 */
काष्ठा bfa_sge_s अणु
	u32	sg_len;
	व्योम		*sg_addr;
पूर्ण;

#घोषणा bfa_sge_word_swap(__sge) करो अणु					     \
	((u32 *)(__sge))[0] = swab32(((u32 *)(__sge))[0]);      \
	((u32 *)(__sge))[1] = swab32(((u32 *)(__sge))[1]);      \
	((u32 *)(__sge))[2] = swab32(((u32 *)(__sge))[2]);      \
पूर्ण जबतक (0)

#घोषणा bfa_swap_words(_x)  (	\
	((u64)(_x) << 32) | ((u64)(_x) >> 32))

#अगर_घोषित __BIG_ENDIAN
#घोषणा bfa_sge_to_be(_x)
#घोषणा bfa_sge_to_le(_x)	bfa_sge_word_swap(_x)
#घोषणा bfa_sgaddr_le(_x)	bfa_swap_words(_x)
#अन्यथा
#घोषणा	bfa_sge_to_be(_x)	bfa_sge_word_swap(_x)
#घोषणा bfa_sge_to_le(_x)
#घोषणा bfa_sgaddr_le(_x)	(_x)
#पूर्ण_अगर

/*
 * BFA memory resources
 */
काष्ठा bfa_mem_dma_s अणु
	काष्ठा list_head qe;		/* Queue of DMA elements */
	u32		mem_len;	/* Total Length in Bytes */
	u8		*kva;		/* kernel भव address */
	u64		dma;		/* dma address अगर DMA memory */
	u8		*kva_curp;	/* kva allocation cursor */
	u64		dma_curp;	/* dma allocation cursor */
पूर्ण;
#घोषणा bfa_mem_dma_t काष्ठा bfa_mem_dma_s

काष्ठा bfa_mem_kva_s अणु
	काष्ठा list_head qe;		/* Queue of KVA elements */
	u32		mem_len;	/* Total Length in Bytes */
	u8		*kva;		/* kernel भव address */
	u8		*kva_curp;	/* kva allocation cursor */
पूर्ण;
#घोषणा bfa_mem_kva_t काष्ठा bfa_mem_kva_s

काष्ठा bfa_meminfo_s अणु
	काष्ठा bfa_mem_dma_s dma_info;
	काष्ठा bfa_mem_kva_s kva_info;
पूर्ण;

/* BFA memory segment setup helpers */
अटल अंतरभूत व्योम bfa_mem_dma_setup(काष्ठा bfa_meminfo_s *meminfo,
				     काष्ठा bfa_mem_dma_s *dm_ptr,
				     माप_प्रकार seg_sz)
अणु
	dm_ptr->mem_len = seg_sz;
	अगर (seg_sz)
		list_add_tail(&dm_ptr->qe, &meminfo->dma_info.qe);
पूर्ण

अटल अंतरभूत व्योम bfa_mem_kva_setup(काष्ठा bfa_meminfo_s *meminfo,
				     काष्ठा bfa_mem_kva_s *kva_ptr,
				     माप_प्रकार seg_sz)
अणु
	kva_ptr->mem_len = seg_sz;
	अगर (seg_sz)
		list_add_tail(&kva_ptr->qe, &meminfo->kva_info.qe);
पूर्ण

/* BFA dma memory segments iterator */
#घोषणा bfa_mem_dma_sptr(_mod, _i)	(&(_mod)->dma_seg[(_i)])
#घोषणा bfa_mem_dma_seg_iter(_mod, _sptr, _nr, _i)			\
	क्रम (_i = 0, _sptr = bfa_mem_dma_sptr(_mod, _i); _i < (_nr);	\
	     _i++, _sptr = bfa_mem_dma_sptr(_mod, _i))

#घोषणा bfa_mem_kva_curp(_mod)	((_mod)->kva_seg.kva_curp)
#घोषणा bfa_mem_dma_virt(_sptr)	((_sptr)->kva_curp)
#घोषणा bfa_mem_dma_phys(_sptr)	((_sptr)->dma_curp)
#घोषणा bfa_mem_dma_len(_sptr)	((_sptr)->mem_len)

/* Get the corresponding dma buf kva क्रम a req - from the tag */
#घोषणा bfa_mem_get_dmabuf_kva(_mod, _tag, _rqsz)			      \
	(((u8 *)(_mod)->dma_seg[BFI_MEM_SEG_FROM_TAG(_tag, _rqsz)].kva_curp) +\
	 BFI_MEM_SEG_REQ_OFFSET(_tag, _rqsz) * (_rqsz))

/* Get the corresponding dma buf pa क्रम a req - from the tag */
#घोषणा bfa_mem_get_dmabuf_pa(_mod, _tag, _rqsz)			\
	((_mod)->dma_seg[BFI_MEM_SEG_FROM_TAG(_tag, _rqsz)].dma_curp +	\
	 BFI_MEM_SEG_REQ_OFFSET(_tag, _rqsz) * (_rqsz))

/*
 * PCI device inक्रमmation required by IOC
 */
काष्ठा bfa_pcidev_s अणु
	पूर्णांक		pci_slot;
	u8		pci_func;
	u16		device_id;
	u16		ssid;
	व्योम __iomem	*pci_bar_kva;
पूर्ण;

/*
 * Structure used to remember the DMA-able memory block's KVA and Physical
 * Address
 */
काष्ठा bfa_dma_s अणु
	व्योम		*kva;	/* ! Kernel भव address	*/
	u64	pa;	/* ! Physical address		*/
पूर्ण;

#घोषणा BFA_DMA_ALIGN_SZ	256
#घोषणा BFA_ROUNDUP(_l, _s)	(((_l) + ((_s) - 1)) & ~((_s) - 1))

/*
 * smem size क्रम Crossbow and Catapult
 */
#घोषणा BFI_SMEM_CB_SIZE	0x200000U	/* ! 2MB क्रम crossbow	*/
#घोषणा BFI_SMEM_CT_SIZE	0x280000U	/* ! 2.5MB क्रम catapult	*/

#घोषणा bfa_dma_be_addr_set(dma_addr, pa)	\
		__bfa_dma_be_addr_set(&dma_addr, (u64)pa)
अटल अंतरभूत व्योम
__bfa_dma_be_addr_set(जोड़ bfi_addr_u *dma_addr, u64 pa)
अणु
	dma_addr->a32.addr_lo = cpu_to_be32(pa);
	dma_addr->a32.addr_hi = cpu_to_be32(pa >> 32);
पूर्ण

#घोषणा bfa_alen_set(__alen, __len, __pa)	\
	__bfa_alen_set(__alen, __len, (u64)__pa)

अटल अंतरभूत व्योम
__bfa_alen_set(काष्ठा bfi_alen_s *alen, u32 len, u64 pa)
अणु
	alen->al_len = cpu_to_be32(len);
	bfa_dma_be_addr_set(alen->al_addr, pa);
पूर्ण

काष्ठा bfa_ioc_regs_s अणु
	व्योम __iomem *hfn_mbox_cmd;
	व्योम __iomem *hfn_mbox;
	व्योम __iomem *lpu_mbox_cmd;
	व्योम __iomem *lpu_mbox;
	व्योम __iomem *lpu_पढ़ो_stat;
	व्योम __iomem *pss_ctl_reg;
	व्योम __iomem *pss_err_status_reg;
	व्योम __iomem *app_pll_fast_ctl_reg;
	व्योम __iomem *app_pll_slow_ctl_reg;
	व्योम __iomem *ioc_sem_reg;
	व्योम __iomem *ioc_usage_sem_reg;
	व्योम __iomem *ioc_init_sem_reg;
	व्योम __iomem *ioc_usage_reg;
	व्योम __iomem *host_page_num_fn;
	व्योम __iomem *heartbeat;
	व्योम __iomem *ioc_fwstate;
	व्योम __iomem *alt_ioc_fwstate;
	व्योम __iomem *ll_halt;
	व्योम __iomem *alt_ll_halt;
	व्योम __iomem *err_set;
	व्योम __iomem *ioc_fail_sync;
	व्योम __iomem *shirq_isr_next;
	व्योम __iomem *shirq_msk_next;
	व्योम __iomem *smem_page_start;
	u32	smem_pg0;
पूर्ण;

#घोषणा bfa_mem_पढ़ो(_raddr, _off)	swab32(पढ़ोl(((_raddr) + (_off))))
#घोषणा bfa_mem_ग_लिखो(_raddr, _off, _val)	\
			ग_लिखोl(swab32((_val)), ((_raddr) + (_off)))
/*
 * IOC Mailbox काष्ठाures
 */
काष्ठा bfa_mbox_cmd_s अणु
	काष्ठा list_head	qe;
	u32	msg[BFI_IOC_MSGSZ];
पूर्ण;

/*
 * IOC mailbox module
 */
प्रकार व्योम (*bfa_ioc_mbox_mcfunc_t)(व्योम *cbarg, काष्ठा bfi_mbmsg_s *m);
काष्ठा bfa_ioc_mbox_mod_s अणु
	काष्ठा list_head		cmd_q;	/*  pending mbox queue	*/
	पूर्णांक			nmclass;	/*  number of handlers */
	काष्ठा अणु
		bfa_ioc_mbox_mcfunc_t	cbfn;	/*  message handlers	*/
		व्योम			*cbarg;
	पूर्ण mbhdlr[BFI_MC_MAX];
पूर्ण;

/*
 * IOC callback function पूर्णांकerfaces
 */
प्रकार व्योम (*bfa_ioc_enable_cbfn_t)(व्योम *bfa, क्रमागत bfa_status status);
प्रकार व्योम (*bfa_ioc_disable_cbfn_t)(व्योम *bfa);
प्रकार व्योम (*bfa_ioc_hbfail_cbfn_t)(व्योम *bfa);
प्रकार व्योम (*bfa_ioc_reset_cbfn_t)(व्योम *bfa);
काष्ठा bfa_ioc_cbfn_s अणु
	bfa_ioc_enable_cbfn_t	enable_cbfn;
	bfa_ioc_disable_cbfn_t	disable_cbfn;
	bfa_ioc_hbfail_cbfn_t	hbfail_cbfn;
	bfa_ioc_reset_cbfn_t	reset_cbfn;
पूर्ण;

/*
 * IOC event notअगरication mechanism.
 */
क्रमागत bfa_ioc_event_e अणु
	BFA_IOC_E_ENABLED	= 1,
	BFA_IOC_E_DISABLED	= 2,
	BFA_IOC_E_FAILED	= 3,
पूर्ण;

प्रकार व्योम (*bfa_ioc_notअगरy_cbfn_t)(व्योम *, क्रमागत bfa_ioc_event_e);

काष्ठा bfa_ioc_notअगरy_s अणु
	काष्ठा list_head		qe;
	bfa_ioc_notअगरy_cbfn_t	cbfn;
	व्योम			*cbarg;
पूर्ण;

/*
 * Initialize a IOC event notअगरication काष्ठाure
 */
#घोषणा bfa_ioc_notअगरy_init(__notअगरy, __cbfn, __cbarg) करो अणु	\
	(__notअगरy)->cbfn = (__cbfn);      \
	(__notअगरy)->cbarg = (__cbarg);      \
पूर्ण जबतक (0)

काष्ठा bfa_iocpf_s अणु
	bfa_fsm_t		fsm;
	काष्ठा bfa_ioc_s	*ioc;
	bfa_boolean_t		fw_mismatch_notअगरied;
	bfa_boolean_t		स्वतः_recover;
	u32			poll_समय;
पूर्ण;

काष्ठा bfa_ioc_s अणु
	bfa_fsm_t		fsm;
	काष्ठा bfa_s		*bfa;
	काष्ठा bfa_pcidev_s	pcidev;
	काष्ठा bfa_समयr_mod_s	*समयr_mod;
	काष्ठा bfa_समयr_s	ioc_समयr;
	काष्ठा bfa_समयr_s	sem_समयr;
	काष्ठा bfa_समयr_s	hb_समयr;
	u32		hb_count;
	काष्ठा list_head	notअगरy_q;
	व्योम			*dbg_fwsave;
	पूर्णांक			dbg_fwsave_len;
	bfa_boolean_t		dbg_fwsave_once;
	क्रमागत bfi_pcअगरn_class	clscode;
	काष्ठा bfa_ioc_regs_s	ioc_regs;
	काष्ठा bfa_trc_mod_s	*trcmod;
	काष्ठा bfa_ioc_drv_stats_s	stats;
	bfa_boolean_t		fcmode;
	bfa_boolean_t		pllinit;
	bfa_boolean_t		stats_busy;	/*  outstanding stats */
	u8			port_id;
	काष्ठा bfa_dma_s	attr_dma;
	काष्ठा bfi_ioc_attr_s	*attr;
	काष्ठा bfa_ioc_cbfn_s	*cbfn;
	काष्ठा bfa_ioc_mbox_mod_s mbox_mod;
	काष्ठा bfa_ioc_hwअगर_s	*ioc_hwअगर;
	काष्ठा bfa_iocpf_s	iocpf;
	क्रमागत bfi_asic_gen	asic_gen;
	क्रमागत bfi_asic_mode	asic_mode;
	क्रमागत bfi_port_mode	port0_mode;
	क्रमागत bfi_port_mode	port1_mode;
	क्रमागत bfa_mode_s		port_mode;
	u8			ad_cap_bm;	/* adapter cap bit mask */
	u8			port_mode_cfg;	/* config port mode */
	पूर्णांक			ioc_aen_seq;
पूर्ण;

काष्ठा bfa_ioc_hwअगर_s अणु
	bfa_status_t (*ioc_pll_init) (व्योम __iomem *rb, क्रमागत bfi_asic_mode m);
	bfa_boolean_t	(*ioc_firmware_lock)	(काष्ठा bfa_ioc_s *ioc);
	व्योम		(*ioc_firmware_unlock)	(काष्ठा bfa_ioc_s *ioc);
	व्योम		(*ioc_reg_init)	(काष्ठा bfa_ioc_s *ioc);
	व्योम		(*ioc_map_port)	(काष्ठा bfa_ioc_s *ioc);
	व्योम		(*ioc_isr_mode_set)	(काष्ठा bfa_ioc_s *ioc,
					bfa_boolean_t msix);
	व्योम		(*ioc_notअगरy_fail)	(काष्ठा bfa_ioc_s *ioc);
	व्योम		(*ioc_ownership_reset)	(काष्ठा bfa_ioc_s *ioc);
	bfa_boolean_t   (*ioc_sync_start)       (काष्ठा bfa_ioc_s *ioc);
	व्योम		(*ioc_sync_join)	(काष्ठा bfa_ioc_s *ioc);
	व्योम		(*ioc_sync_leave)	(काष्ठा bfa_ioc_s *ioc);
	व्योम		(*ioc_sync_ack)		(काष्ठा bfa_ioc_s *ioc);
	bfa_boolean_t	(*ioc_sync_complete)	(काष्ठा bfa_ioc_s *ioc);
	bfa_boolean_t	(*ioc_lpu_पढ़ो_stat)	(काष्ठा bfa_ioc_s *ioc);
	व्योम		(*ioc_set_fwstate)	(काष्ठा bfa_ioc_s *ioc,
					क्रमागत bfi_ioc_state fwstate);
	क्रमागत bfi_ioc_state	(*ioc_get_fwstate)	(काष्ठा bfa_ioc_s *ioc);
	व्योम		(*ioc_set_alt_fwstate)	(काष्ठा bfa_ioc_s *ioc,
					क्रमागत bfi_ioc_state fwstate);
	क्रमागत bfi_ioc_state	(*ioc_get_alt_fwstate)	(काष्ठा bfa_ioc_s *ioc);
पूर्ण;

/*
 * Queue element to रुको क्रम room in request queue. FIFO order is
 * मुख्यtained when fullfilling requests.
 */
काष्ठा bfa_reqq_रुको_s अणु
	काष्ठा list_head	qe;
	व्योम	(*qresume) (व्योम *cbarg);
	व्योम	*cbarg;
पूर्ण;

प्रकार व्योम	(*bfa_cb_cbfn_t) (व्योम *cbarg, bfa_boolean_t complete);

/*
 * Generic BFA callback element.
 */
काष्ठा bfa_cb_qe_s अणु
	काष्ठा list_head	qe;
	bfa_cb_cbfn_t	cbfn;
	bfa_boolean_t	once;
	bfa_boolean_t	pre_rmv;	/* set क्रम stack based qe(s) */
	bfa_status_t	fw_status;	/* to access fw status in comp proc */
	व्योम		*cbarg;
पूर्ण;

/*
 * IOCFC state machine definitions/declarations
 */
क्रमागत iocfc_event अणु
	IOCFC_E_INIT		= 1,	/* IOCFC init request		*/
	IOCFC_E_START		= 2,	/* IOCFC mod start request	*/
	IOCFC_E_STOP		= 3,	/* IOCFC stop request		*/
	IOCFC_E_ENABLE		= 4,	/* IOCFC enable request		*/
	IOCFC_E_DISABLE		= 5,	/* IOCFC disable request	*/
	IOCFC_E_IOC_ENABLED	= 6,	/* IOC enabled message		*/
	IOCFC_E_IOC_DISABLED	= 7,	/* IOC disabled message		*/
	IOCFC_E_IOC_FAILED	= 8,	/* failure notice by IOC sm	*/
	IOCFC_E_DCONF_DONE	= 9,	/* dconf पढ़ो/ग_लिखो करोne	*/
	IOCFC_E_CFG_DONE	= 10,	/* IOCFC config complete	*/
पूर्ण;

/*
 * ASIC block configurtion related
 */

प्रकार व्योम (*bfa_ablk_cbfn_t)(व्योम *, क्रमागत bfa_status);

काष्ठा bfa_ablk_s अणु
	काष्ठा bfa_ioc_s	*ioc;
	काष्ठा bfa_ablk_cfg_s	*cfg;
	u16			*pcअगरn;
	काष्ठा bfa_dma_s	dma_addr;
	bfa_boolean_t		busy;
	काष्ठा bfa_mbox_cmd_s	mb;
	bfa_ablk_cbfn_t		cbfn;
	व्योम			*cbarg;
	काष्ठा bfa_ioc_notअगरy_s	ioc_notअगरy;
	काष्ठा bfa_mem_dma_s	ablk_dma;
पूर्ण;
#घोषणा BFA_MEM_ABLK_DMA(__bfa)		(&((__bfa)->modules.ablk.ablk_dma))

/*
 *	SFP module specअगरic
 */
प्रकार व्योम	(*bfa_cb_sfp_t) (व्योम *cbarg, bfa_status_t status);

काष्ठा bfa_sfp_s अणु
	व्योम	*dev;
	काष्ठा bfa_ioc_s	*ioc;
	काष्ठा bfa_trc_mod_s	*trcmod;
	काष्ठा sfp_mem_s	*sfpmem;
	bfa_cb_sfp_t		cbfn;
	व्योम			*cbarg;
	क्रमागत bfi_sfp_mem_e	memtype; /* mem access type   */
	u32			status;
	काष्ठा bfa_mbox_cmd_s	mbcmd;
	u8			*dbuf_kva; /* dma buf भव address */
	u64			dbuf_pa;   /* dma buf physical address */
	काष्ठा bfa_ioc_notअगरy_s	ioc_notअगरy;
	क्रमागत bfa_defs_sfp_media_e *media;
	क्रमागत bfa_port_speed	portspeed;
	bfa_cb_sfp_t		state_query_cbfn;
	व्योम			*state_query_cbarg;
	u8			lock;
	u8			data_valid; /* data in dbuf is valid */
	u8			state;	    /* sfp state  */
	u8			state_query_lock;
	काष्ठा bfa_mem_dma_s	sfp_dma;
	u8			is_elb;	    /* eloopback  */
पूर्ण;

#घोषणा BFA_SFP_MOD(__bfa)	(&(__bfa)->modules.sfp)
#घोषणा BFA_MEM_SFP_DMA(__bfa)	(&(BFA_SFP_MOD(__bfa)->sfp_dma))

u32	bfa_sfp_meminfo(व्योम);

व्योम	bfa_sfp_attach(काष्ठा bfa_sfp_s *sfp, काष्ठा bfa_ioc_s *ioc,
			व्योम *dev, काष्ठा bfa_trc_mod_s *trcmod);

व्योम	bfa_sfp_memclaim(काष्ठा bfa_sfp_s *diag, u8 *dm_kva, u64 dm_pa);
व्योम	bfa_sfp_पूर्णांकr(व्योम *bfaarg, काष्ठा bfi_mbmsg_s *msg);

bfa_status_t	bfa_sfp_show(काष्ठा bfa_sfp_s *sfp, काष्ठा sfp_mem_s *sfpmem,
			     bfa_cb_sfp_t cbfn, व्योम *cbarg);

bfa_status_t	bfa_sfp_media(काष्ठा bfa_sfp_s *sfp,
			क्रमागत bfa_defs_sfp_media_e *media,
			bfa_cb_sfp_t cbfn, व्योम *cbarg);

bfa_status_t	bfa_sfp_speed(काष्ठा bfa_sfp_s *sfp,
			क्रमागत bfa_port_speed portspeed,
			bfa_cb_sfp_t cbfn, व्योम *cbarg);

/*
 *	Flash module specअगरic
 */
प्रकार व्योम	(*bfa_cb_flash_t) (व्योम *cbarg, bfa_status_t status);

काष्ठा bfa_flash_s अणु
	काष्ठा bfa_ioc_s *ioc;		/* back poपूर्णांकer to ioc */
	काष्ठा bfa_trc_mod_s *trcmod;
	u32		type;           /* partition type */
	u8		instance;       /* partition instance */
	u8		rsv[3];
	u32		op_busy;        /*  operation busy flag */
	u32		residue;        /*  residual length */
	u32		offset;         /*  offset */
	bfa_status_t	status;         /*  status */
	u8		*dbuf_kva;      /*  dma buf भव address */
	u64		dbuf_pa;        /*  dma buf physical address */
	काष्ठा bfa_reqq_रुको_s	reqq_रुको; /*  to रुको क्रम room in reqq */
	bfa_cb_flash_t	cbfn;           /*  user callback function */
	व्योम		*cbarg;         /*  user callback arg */
	u8		*ubuf;          /*  user supplied buffer */
	काष्ठा bfa_cb_qe_s	hcb_qe; /*  comp: BFA callback qelem */
	u32		addr_off;       /*  partition address offset */
	काष्ठा bfa_mbox_cmd_s	mb;       /*  mailbox */
	काष्ठा bfa_ioc_notअगरy_s	ioc_notअगरy; /*  ioc event notअगरy */
	काष्ठा bfa_mem_dma_s	flash_dma;
पूर्ण;

#घोषणा BFA_FLASH(__bfa)		(&(__bfa)->modules.flash)
#घोषणा BFA_MEM_FLASH_DMA(__bfa)	(&(BFA_FLASH(__bfa)->flash_dma))

bfa_status_t bfa_flash_get_attr(काष्ठा bfa_flash_s *flash,
			काष्ठा bfa_flash_attr_s *attr,
			bfa_cb_flash_t cbfn, व्योम *cbarg);
bfa_status_t bfa_flash_erase_part(काष्ठा bfa_flash_s *flash,
			क्रमागत bfa_flash_part_type type, u8 instance,
			bfa_cb_flash_t cbfn, व्योम *cbarg);
bfa_status_t bfa_flash_update_part(काष्ठा bfa_flash_s *flash,
			क्रमागत bfa_flash_part_type type, u8 instance,
			व्योम *buf, u32 len, u32 offset,
			bfa_cb_flash_t cbfn, व्योम *cbarg);
bfa_status_t bfa_flash_पढ़ो_part(काष्ठा bfa_flash_s *flash,
			क्रमागत bfa_flash_part_type type, u8 instance, व्योम *buf,
			u32 len, u32 offset, bfa_cb_flash_t cbfn, व्योम *cbarg);
u32	bfa_flash_meminfo(bfa_boolean_t mincfg);
व्योम bfa_flash_attach(काष्ठा bfa_flash_s *flash, काष्ठा bfa_ioc_s *ioc,
		व्योम *dev, काष्ठा bfa_trc_mod_s *trcmod, bfa_boolean_t mincfg);
व्योम bfa_flash_memclaim(काष्ठा bfa_flash_s *flash,
		u8 *dm_kva, u64 dm_pa, bfa_boolean_t mincfg);
bfa_status_t    bfa_flash_raw_पढ़ो(व्योम __iomem *pci_bar_kva,
				u32 offset, अक्षर *buf, u32 len);

/*
 *	DIAG module specअगरic
 */

प्रकार व्योम (*bfa_cb_diag_t) (व्योम *cbarg, bfa_status_t status);
प्रकार व्योम (*bfa_cb_diag_beacon_t) (व्योम *dev, bfa_boolean_t beacon,
			bfa_boolean_t link_e2e_beacon);

/*
 *      Firmware ping test results
 */
काष्ठा bfa_diag_results_fwping अणु
	u32     data;   /* store the corrupted data */
	u32     status;
	u32     dmastatus;
	u8      rsvd[4];
पूर्ण;

काष्ठा bfa_diag_qtest_result_s अणु
	u32	status;
	u16	count;	/* successful queue test count */
	u8	queue;
	u8	rsvd;	/* 64-bit align */
पूर्ण;

/*
 * Firmware ping test results
 */
काष्ठा bfa_diag_fwping_s अणु
	काष्ठा bfa_diag_results_fwping *result;
	bfa_cb_diag_t  cbfn;
	व्योम            *cbarg;
	u32             data;
	u8              lock;
	u8              rsv[3];
	u32             status;
	u32             count;
	काष्ठा bfa_mbox_cmd_s   mbcmd;
	u8              *dbuf_kva;      /* dma buf भव address */
	u64             dbuf_pa;        /* dma buf physical address */
पूर्ण;

/*
 *      Temperature sensor query results
 */
काष्ठा bfa_diag_results_tempsensor_s अणु
	u32     status;
	u16     temp;           /* 10-bit A/D value */
	u16     brd_temp;       /* 9-bit board temp */
	u8      ts_junc;        /* show junction tempsensor   */
	u8      ts_brd;         /* show board tempsensor      */
	u8      rsvd[6];        /* keep 8 bytes alignment     */
पूर्ण;

काष्ठा bfa_diag_tsensor_s अणु
	bfa_cb_diag_t   cbfn;
	व्योम            *cbarg;
	काष्ठा bfa_diag_results_tempsensor_s *temp;
	u8              lock;
	u8              rsv[3];
	u32             status;
	काष्ठा bfa_mbox_cmd_s   mbcmd;
पूर्ण;

काष्ठा bfa_diag_sfpshow_s अणु
	काष्ठा sfp_mem_s        *sfpmem;
	bfa_cb_diag_t           cbfn;
	व्योम                    *cbarg;
	u8      lock;
	u8      अटल_data;
	u8      rsv[2];
	u32     status;
	काष्ठा bfa_mbox_cmd_s    mbcmd;
	u8      *dbuf_kva;      /* dma buf भव address */
	u64     dbuf_pa;        /* dma buf physical address */
पूर्ण;

काष्ठा bfa_diag_led_s अणु
	काष्ठा bfa_mbox_cmd_s   mbcmd;
	bfa_boolean_t   lock;   /* 1: ledtest is operating */
पूर्ण;

काष्ठा bfa_diag_beacon_s अणु
	काष्ठा bfa_mbox_cmd_s   mbcmd;
	bfa_boolean_t   state;          /* port beacon state */
	bfa_boolean_t   link_e2e;       /* link beacon state */
पूर्ण;

काष्ठा bfa_diag_s अणु
	व्योम	*dev;
	काष्ठा bfa_ioc_s		*ioc;
	काष्ठा bfa_trc_mod_s		*trcmod;
	काष्ठा bfa_diag_fwping_s	fwping;
	काष्ठा bfa_diag_tsensor_s	tsensor;
	काष्ठा bfa_diag_sfpshow_s	sfpshow;
	काष्ठा bfa_diag_led_s		ledtest;
	काष्ठा bfa_diag_beacon_s	beacon;
	व्योम	*result;
	काष्ठा bfa_समयr_s समयr;
	bfa_cb_diag_beacon_t  cbfn_beacon;
	bfa_cb_diag_t  cbfn;
	व्योम		*cbarg;
	u8		block;
	u8		समयr_active;
	u8		rsvd[2];
	u32		status;
	काष्ठा bfa_ioc_notअगरy_s	ioc_notअगरy;
	काष्ठा bfa_mem_dma_s	diag_dma;
पूर्ण;

#घोषणा BFA_DIAG_MOD(__bfa)     (&(__bfa)->modules.diag_mod)
#घोषणा BFA_MEM_DIAG_DMA(__bfa) (&(BFA_DIAG_MOD(__bfa)->diag_dma))

u32	bfa_diag_meminfo(व्योम);
व्योम bfa_diag_memclaim(काष्ठा bfa_diag_s *diag, u8 *dm_kva, u64 dm_pa);
व्योम bfa_diag_attach(काष्ठा bfa_diag_s *diag, काष्ठा bfa_ioc_s *ioc, व्योम *dev,
		     bfa_cb_diag_beacon_t cbfn_beacon,
		     काष्ठा bfa_trc_mod_s *trcmod);
bfa_status_t	bfa_diag_reg_पढ़ो(काष्ठा bfa_diag_s *diag, u32 offset,
			u32 len, u32 *buf, u32 क्रमce);
bfa_status_t	bfa_diag_reg_ग_लिखो(काष्ठा bfa_diag_s *diag, u32 offset,
			u32 len, u32 value, u32 क्रमce);
bfa_status_t	bfa_diag_tsensor_query(काष्ठा bfa_diag_s *diag,
			काष्ठा bfa_diag_results_tempsensor_s *result,
			bfa_cb_diag_t cbfn, व्योम *cbarg);
bfa_status_t	bfa_diag_fwping(काष्ठा bfa_diag_s *diag, u32 cnt,
			u32 pattern, काष्ठा bfa_diag_results_fwping *result,
			bfa_cb_diag_t cbfn, व्योम *cbarg);
bfa_status_t	bfa_diag_sfpshow(काष्ठा bfa_diag_s *diag,
			काष्ठा sfp_mem_s *sfpmem, u8 अटल_data,
			bfa_cb_diag_t cbfn, व्योम *cbarg);
bfa_status_t	bfa_diag_memtest(काष्ठा bfa_diag_s *diag,
			काष्ठा bfa_diag_memtest_s *memtest, u32 pattern,
			काष्ठा bfa_diag_memtest_result *result,
			bfa_cb_diag_t cbfn, व्योम *cbarg);
bfa_status_t	bfa_diag_ledtest(काष्ठा bfa_diag_s *diag,
			काष्ठा bfa_diag_ledtest_s *ledtest);
bfa_status_t	bfa_diag_beacon_port(काष्ठा bfa_diag_s *diag,
			bfa_boolean_t beacon, bfa_boolean_t link_e2e_beacon,
			u32 sec);

/*
 *	PHY module specअगरic
 */
प्रकार व्योम (*bfa_cb_phy_t) (व्योम *cbarg, bfa_status_t status);

काष्ठा bfa_phy_s अणु
	काष्ठा bfa_ioc_s *ioc;          /* back poपूर्णांकer to ioc */
	काष्ठा bfa_trc_mod_s *trcmod;   /* trace module */
	u8	instance;       /* port instance */
	u8	op_busy;        /* operation busy flag */
	u8	rsv[2];
	u32	residue;        /* residual length */
	u32	offset;         /* offset */
	bfa_status_t	status;         /* status */
	u8	*dbuf_kva;      /* dma buf भव address */
	u64	dbuf_pa;        /* dma buf physical address */
	काष्ठा bfa_reqq_रुको_s reqq_रुको; /* to रुको क्रम room in reqq */
	bfa_cb_phy_t	cbfn;           /* user callback function */
	व्योम		*cbarg;         /* user callback arg */
	u8		*ubuf;          /* user supplied buffer */
	काष्ठा bfa_cb_qe_s	hcb_qe; /* comp: BFA callback qelem */
	u32	addr_off;       /* phy address offset */
	काष्ठा bfa_mbox_cmd_s	mb;       /* mailbox */
	काष्ठा bfa_ioc_notअगरy_s	ioc_notअगरy; /* ioc event notअगरy */
	काष्ठा bfa_mem_dma_s	phy_dma;
पूर्ण;
#घोषणा BFA_PHY(__bfa)	(&(__bfa)->modules.phy)
#घोषणा BFA_MEM_PHY_DMA(__bfa)	(&(BFA_PHY(__bfa)->phy_dma))

bfa_boolean_t bfa_phy_busy(काष्ठा bfa_ioc_s *ioc);
bfa_status_t bfa_phy_get_attr(काष्ठा bfa_phy_s *phy, u8 instance,
			काष्ठा bfa_phy_attr_s *attr,
			bfa_cb_phy_t cbfn, व्योम *cbarg);
bfa_status_t bfa_phy_get_stats(काष्ठा bfa_phy_s *phy, u8 instance,
			काष्ठा bfa_phy_stats_s *stats,
			bfa_cb_phy_t cbfn, व्योम *cbarg);
bfa_status_t bfa_phy_update(काष्ठा bfa_phy_s *phy, u8 instance,
			व्योम *buf, u32 len, u32 offset,
			bfa_cb_phy_t cbfn, व्योम *cbarg);
bfa_status_t bfa_phy_पढ़ो(काष्ठा bfa_phy_s *phy, u8 instance,
			व्योम *buf, u32 len, u32 offset,
			bfa_cb_phy_t cbfn, व्योम *cbarg);

u32	bfa_phy_meminfo(bfa_boolean_t mincfg);
व्योम bfa_phy_attach(काष्ठा bfa_phy_s *phy, काष्ठा bfa_ioc_s *ioc,
		व्योम *dev, काष्ठा bfa_trc_mod_s *trcmod, bfa_boolean_t mincfg);
व्योम bfa_phy_memclaim(काष्ठा bfa_phy_s *phy,
		u8 *dm_kva, u64 dm_pa, bfa_boolean_t mincfg);
व्योम bfa_phy_पूर्णांकr(व्योम *phyarg, काष्ठा bfi_mbmsg_s *msg);

/*
 * FRU module specअगरic
 */
प्रकार व्योम (*bfa_cb_fru_t) (व्योम *cbarg, bfa_status_t status);

काष्ठा bfa_fru_s अणु
	काष्ठा bfa_ioc_s *ioc;		/* back poपूर्णांकer to ioc */
	काष्ठा bfa_trc_mod_s *trcmod;	/* trace module */
	u8		op_busy;	/* operation busy flag */
	u8		rsv[3];
	u32		residue;	/* residual length */
	u32		offset;		/* offset */
	bfa_status_t	status;		/* status */
	u8		*dbuf_kva;	/* dma buf भव address */
	u64		dbuf_pa;	/* dma buf physical address */
	काष्ठा bfa_reqq_रुको_s reqq_रुको; /* to रुको क्रम room in reqq */
	bfa_cb_fru_t	cbfn;		/* user callback function */
	व्योम		*cbarg;		/* user callback arg */
	u8		*ubuf;		/* user supplied buffer */
	काष्ठा bfa_cb_qe_s	hcb_qe;	/* comp: BFA callback qelem */
	u32		addr_off;	/* fru address offset */
	काष्ठा bfa_mbox_cmd_s mb;	/* mailbox */
	काष्ठा bfa_ioc_notअगरy_s ioc_notअगरy; /* ioc event notअगरy */
	काष्ठा bfa_mem_dma_s	fru_dma;
	u8		trfr_cmpl;
पूर्ण;

#घोषणा BFA_FRU(__bfa)	(&(__bfa)->modules.fru)
#घोषणा BFA_MEM_FRU_DMA(__bfa)	(&(BFA_FRU(__bfa)->fru_dma))

bfa_status_t bfa_fruvpd_update(काष्ठा bfa_fru_s *fru,
			व्योम *buf, u32 len, u32 offset,
			bfa_cb_fru_t cbfn, व्योम *cbarg, u8 trfr_cmpl);
bfa_status_t bfa_fruvpd_पढ़ो(काष्ठा bfa_fru_s *fru,
			व्योम *buf, u32 len, u32 offset,
			bfa_cb_fru_t cbfn, व्योम *cbarg);
bfa_status_t bfa_fruvpd_get_max_size(काष्ठा bfa_fru_s *fru, u32 *max_size);
bfa_status_t bfa_tfru_ग_लिखो(काष्ठा bfa_fru_s *fru,
			व्योम *buf, u32 len, u32 offset,
			bfa_cb_fru_t cbfn, व्योम *cbarg);
bfa_status_t bfa_tfru_पढ़ो(काष्ठा bfa_fru_s *fru,
			व्योम *buf, u32 len, u32 offset,
			bfa_cb_fru_t cbfn, व्योम *cbarg);
u32	bfa_fru_meminfo(bfa_boolean_t mincfg);
व्योम bfa_fru_attach(काष्ठा bfa_fru_s *fru, काष्ठा bfa_ioc_s *ioc,
		व्योम *dev, काष्ठा bfa_trc_mod_s *trcmod, bfa_boolean_t mincfg);
व्योम bfa_fru_memclaim(काष्ठा bfa_fru_s *fru,
		u8 *dm_kva, u64 dm_pa, bfa_boolean_t mincfg);
व्योम bfa_fru_पूर्णांकr(व्योम *fruarg, काष्ठा bfi_mbmsg_s *msg);

/*
 * Driver Config( dconf) specअगरic
 */
#घोषणा BFI_DCONF_SIGNATURE	0xabcdabcd
#घोषणा BFI_DCONF_VERSION	1

#आशय pack(1)
काष्ठा bfa_dconf_hdr_s अणु
	u32	signature;
	u32	version;
पूर्ण;

काष्ठा bfa_dconf_s अणु
	काष्ठा bfa_dconf_hdr_s		hdr;
	काष्ठा bfa_lunmask_cfg_s	lun_mask;
	काष्ठा bfa_throttle_cfg_s	throttle_cfg;
पूर्ण;
#आशय pack()

काष्ठा bfa_dconf_mod_s अणु
	bfa_sm_t		sm;
	u8			instance;
	bfa_boolean_t		पढ़ो_data_valid;
	bfa_boolean_t		min_cfg;
	काष्ठा bfa_समयr_s	समयr;
	काष्ठा bfa_s		*bfa;
	व्योम			*bfad;
	व्योम			*trcmod;
	काष्ठा bfa_dconf_s	*dconf;
	काष्ठा bfa_mem_kva_s	kva_seg;
पूर्ण;

#घोषणा BFA_DCONF_MOD(__bfa)	\
	(&(__bfa)->modules.dconf_mod)
#घोषणा BFA_MEM_DCONF_KVA(__bfa)	(&(BFA_DCONF_MOD(__bfa)->kva_seg))
#घोषणा bfa_dconf_पढ़ो_data_valid(__bfa)	\
	(BFA_DCONF_MOD(__bfa)->पढ़ो_data_valid)
#घोषणा BFA_DCONF_UPDATE_TOV	5000	/* memtest समयout in msec */
#घोषणा bfa_dconf_get_min_cfg(__bfa)	\
	(BFA_DCONF_MOD(__bfa)->min_cfg)

व्योम	bfa_dconf_modinit(काष्ठा bfa_s *bfa);
व्योम	bfa_dconf_modनिकास(काष्ठा bfa_s *bfa);
bfa_status_t	bfa_dconf_update(काष्ठा bfa_s *bfa);

/*
 *	IOC specfic macros
 */
#घोषणा bfa_ioc_pcअगरn(__ioc)		((__ioc)->pcidev.pci_func)
#घोषणा bfa_ioc_devid(__ioc)		((__ioc)->pcidev.device_id)
#घोषणा bfa_ioc_bar0(__ioc)		((__ioc)->pcidev.pci_bar_kva)
#घोषणा bfa_ioc_portid(__ioc)		((__ioc)->port_id)
#घोषणा bfa_ioc_asic_gen(__ioc)		((__ioc)->asic_gen)
#घोषणा bfa_ioc_is_cna(__ioc)	\
	((bfa_ioc_get_type(__ioc) == BFA_IOC_TYPE_FCoE) ||	\
	 (bfa_ioc_get_type(__ioc) == BFA_IOC_TYPE_LL))
#घोषणा bfa_ioc_fetch_stats(__ioc, __stats) \
		(((__stats)->drv_stats) = (__ioc)->stats)
#घोषणा bfa_ioc_clr_stats(__ioc)	\
		स_रखो(&(__ioc)->stats, 0, माप((__ioc)->stats))
#घोषणा bfa_ioc_maxfrsize(__ioc)	((__ioc)->attr->maxfrsize)
#घोषणा bfa_ioc_rx_bbcredit(__ioc)	((__ioc)->attr->rx_bbcredit)
#घोषणा bfa_ioc_speed_sup(__ioc)	\
	((bfa_ioc_is_cna(__ioc)) ? BFA_PORT_SPEED_10GBPS :	\
	 BFI_ADAPTER_GETP(SPEED, (__ioc)->attr->adapter_prop))
#घोषणा bfa_ioc_get_nports(__ioc)	\
	BFI_ADAPTER_GETP(NPORTS, (__ioc)->attr->adapter_prop)

#घोषणा bfa_ioc_stats(_ioc, _stats)	((_ioc)->stats._stats++)
#घोषणा BFA_IOC_FWIMG_MINSZ	(16 * 1024)
#घोषणा BFA_IOC_FW_SMEM_SIZE(__ioc)			\
	((bfa_ioc_asic_gen(__ioc) == BFI_ASIC_GEN_CB)	\
	 ? BFI_SMEM_CB_SIZE : BFI_SMEM_CT_SIZE)
#घोषणा BFA_IOC_FLASH_CHUNK_NO(off)		(off / BFI_FLASH_CHUNK_SZ_WORDS)
#घोषणा BFA_IOC_FLASH_OFFSET_IN_CHUNK(off)	(off % BFI_FLASH_CHUNK_SZ_WORDS)
#घोषणा BFA_IOC_FLASH_CHUNK_ADDR(chunkno)  (chunkno * BFI_FLASH_CHUNK_SZ_WORDS)

/*
 * IOC mailbox पूर्णांकerface
 */
व्योम bfa_ioc_mbox_queue(काष्ठा bfa_ioc_s *ioc, काष्ठा bfa_mbox_cmd_s *cmd);
व्योम bfa_ioc_mbox_रेजिस्टर(काष्ठा bfa_ioc_s *ioc,
		bfa_ioc_mbox_mcfunc_t *mcfuncs);
व्योम bfa_ioc_mbox_isr(काष्ठा bfa_ioc_s *ioc);
व्योम bfa_ioc_mbox_send(काष्ठा bfa_ioc_s *ioc, व्योम *ioc_msg, पूर्णांक len);
bfa_boolean_t bfa_ioc_msgget(काष्ठा bfa_ioc_s *ioc, व्योम *mbmsg);
व्योम bfa_ioc_mbox_regisr(काष्ठा bfa_ioc_s *ioc, क्रमागत bfi_mclass mc,
		bfa_ioc_mbox_mcfunc_t cbfn, व्योम *cbarg);

/*
 * IOC पूर्णांकerfaces
 */

#घोषणा bfa_ioc_pll_init_asic(__ioc) \
	((__ioc)->ioc_hwअगर->ioc_pll_init((__ioc)->pcidev.pci_bar_kva, \
			   (__ioc)->asic_mode))

bfa_status_t bfa_ioc_pll_init(काष्ठा bfa_ioc_s *ioc);
bfa_status_t bfa_ioc_cb_pll_init(व्योम __iomem *rb, क्रमागत bfi_asic_mode mode);
bfa_status_t bfa_ioc_ct_pll_init(व्योम __iomem *rb, क्रमागत bfi_asic_mode mode);
bfa_status_t bfa_ioc_ct2_pll_init(व्योम __iomem *rb, क्रमागत bfi_asic_mode mode);

#घोषणा bfa_ioc_isr_mode_set(__ioc, __msix) करो अणु			\
	अगर ((__ioc)->ioc_hwअगर->ioc_isr_mode_set)			\
		((__ioc)->ioc_hwअगर->ioc_isr_mode_set(__ioc, __msix));	\
पूर्ण जबतक (0)
#घोषणा	bfa_ioc_ownership_reset(__ioc)				\
			((__ioc)->ioc_hwअगर->ioc_ownership_reset(__ioc))
#घोषणा bfa_ioc_get_fcmode(__ioc)	((__ioc)->fcmode)
#घोषणा bfa_ioc_lpu_पढ़ो_stat(__ioc) करो अणु			\
	अगर ((__ioc)->ioc_hwअगर->ioc_lpu_पढ़ो_stat)		\
		((__ioc)->ioc_hwअगर->ioc_lpu_पढ़ो_stat(__ioc));	\
पूर्ण जबतक (0)

व्योम bfa_ioc_set_cb_hwअगर(काष्ठा bfa_ioc_s *ioc);
व्योम bfa_ioc_set_ct_hwअगर(काष्ठा bfa_ioc_s *ioc);
व्योम bfa_ioc_set_ct2_hwअगर(काष्ठा bfa_ioc_s *ioc);
व्योम bfa_ioc_ct2_घातeron(काष्ठा bfa_ioc_s *ioc);

व्योम bfa_ioc_attach(काष्ठा bfa_ioc_s *ioc, व्योम *bfa,
		काष्ठा bfa_ioc_cbfn_s *cbfn, काष्ठा bfa_समयr_mod_s *समयr_mod);
व्योम bfa_ioc_स्वतः_recover(bfa_boolean_t स्वतः_recover);
व्योम bfa_ioc_detach(काष्ठा bfa_ioc_s *ioc);
व्योम bfa_ioc_suspend(काष्ठा bfa_ioc_s *ioc);
व्योम bfa_ioc_pci_init(काष्ठा bfa_ioc_s *ioc, काष्ठा bfa_pcidev_s *pcidev,
		क्रमागत bfi_pcअगरn_class clscode);
व्योम bfa_ioc_mem_claim(काष्ठा bfa_ioc_s *ioc,  u8 *dm_kva, u64 dm_pa);
व्योम bfa_ioc_enable(काष्ठा bfa_ioc_s *ioc);
व्योम bfa_ioc_disable(काष्ठा bfa_ioc_s *ioc);
bfa_boolean_t bfa_ioc_पूर्णांकx_claim(काष्ठा bfa_ioc_s *ioc);

bfa_status_t bfa_ioc_boot(काष्ठा bfa_ioc_s *ioc, u32 boot_type,
		u32 boot_env);
व्योम bfa_ioc_isr(काष्ठा bfa_ioc_s *ioc, काष्ठा bfi_mbmsg_s *msg);
व्योम bfa_ioc_error_isr(काष्ठा bfa_ioc_s *ioc);
bfa_boolean_t bfa_ioc_is_operational(काष्ठा bfa_ioc_s *ioc);
bfa_boolean_t bfa_ioc_is_initialized(काष्ठा bfa_ioc_s *ioc);
bfa_boolean_t bfa_ioc_is_disabled(काष्ठा bfa_ioc_s *ioc);
bfa_boolean_t bfa_ioc_is_acq_addr(काष्ठा bfa_ioc_s *ioc);
bfa_boolean_t bfa_ioc_fw_mismatch(काष्ठा bfa_ioc_s *ioc);
bfa_boolean_t bfa_ioc_adapter_is_disabled(काष्ठा bfa_ioc_s *ioc);
व्योम bfa_ioc_reset_fwstate(काष्ठा bfa_ioc_s *ioc);
क्रमागत bfa_ioc_type_e bfa_ioc_get_type(काष्ठा bfa_ioc_s *ioc);
व्योम bfa_ioc_get_adapter_serial_num(काष्ठा bfa_ioc_s *ioc, अक्षर *serial_num);
व्योम bfa_ioc_get_adapter_fw_ver(काष्ठा bfa_ioc_s *ioc, अक्षर *fw_ver);
व्योम bfa_ioc_get_adapter_optrom_ver(काष्ठा bfa_ioc_s *ioc, अक्षर *optrom_ver);
व्योम bfa_ioc_get_adapter_model(काष्ठा bfa_ioc_s *ioc, अक्षर *model);
व्योम bfa_ioc_get_adapter_manufacturer(काष्ठा bfa_ioc_s *ioc,
		अक्षर *manufacturer);
व्योम bfa_ioc_get_pci_chip_rev(काष्ठा bfa_ioc_s *ioc, अक्षर *chip_rev);
क्रमागत bfa_ioc_state bfa_ioc_get_state(काष्ठा bfa_ioc_s *ioc);

व्योम bfa_ioc_get_attr(काष्ठा bfa_ioc_s *ioc, काष्ठा bfa_ioc_attr_s *ioc_attr);
व्योम bfa_ioc_get_adapter_attr(काष्ठा bfa_ioc_s *ioc,
		काष्ठा bfa_adapter_attr_s *ad_attr);
व्योम bfa_ioc_debug_memclaim(काष्ठा bfa_ioc_s *ioc, व्योम *dbg_fwsave);
bfa_status_t bfa_ioc_debug_fwsave(काष्ठा bfa_ioc_s *ioc, व्योम *trcdata,
		पूर्णांक *trclen);
bfa_status_t bfa_ioc_debug_fwtrc(काष्ठा bfa_ioc_s *ioc, व्योम *trcdata,
				 पूर्णांक *trclen);
bfa_status_t bfa_ioc_debug_fwcore(काष्ठा bfa_ioc_s *ioc, व्योम *buf,
	u32 *offset, पूर्णांक *buflen);
bfa_status_t bfa_ioc_fwsig_invalidate(काष्ठा bfa_ioc_s *ioc);
bfa_boolean_t bfa_ioc_sem_get(व्योम __iomem *sem_reg);
व्योम bfa_ioc_fwver_get(काष्ठा bfa_ioc_s *ioc,
			काष्ठा bfi_ioc_image_hdr_s *fwhdr);
bfa_boolean_t bfa_ioc_fwver_cmp(काष्ठा bfa_ioc_s *ioc,
			काष्ठा bfi_ioc_image_hdr_s *fwhdr);
व्योम bfa_ioc_aen_post(काष्ठा bfa_ioc_s *ioc, क्रमागत bfa_ioc_aen_event event);
bfa_status_t bfa_ioc_fw_stats_get(काष्ठा bfa_ioc_s *ioc, व्योम *stats);
bfa_status_t bfa_ioc_fw_stats_clear(काष्ठा bfa_ioc_s *ioc);
व्योम bfa_ioc_debug_save_ftrc(काष्ठा bfa_ioc_s *ioc);

/*
 * asic block configuration related APIs
 */
u32	bfa_ablk_meminfo(व्योम);
व्योम bfa_ablk_memclaim(काष्ठा bfa_ablk_s *ablk, u8 *dma_kva, u64 dma_pa);
व्योम bfa_ablk_attach(काष्ठा bfa_ablk_s *ablk, काष्ठा bfa_ioc_s *ioc);
bfa_status_t bfa_ablk_query(काष्ठा bfa_ablk_s *ablk,
		काष्ठा bfa_ablk_cfg_s *ablk_cfg,
		bfa_ablk_cbfn_t cbfn, व्योम *cbarg);
bfa_status_t bfa_ablk_adapter_config(काष्ठा bfa_ablk_s *ablk,
		क्रमागत bfa_mode_s mode, पूर्णांक max_pf, पूर्णांक max_vf,
		bfa_ablk_cbfn_t cbfn, व्योम *cbarg);
bfa_status_t bfa_ablk_port_config(काष्ठा bfa_ablk_s *ablk, पूर्णांक port,
		क्रमागत bfa_mode_s mode, पूर्णांक max_pf, पूर्णांक max_vf,
		bfa_ablk_cbfn_t cbfn, व्योम *cbarg);
bfa_status_t bfa_ablk_pf_create(काष्ठा bfa_ablk_s *ablk, u16 *pcअगरn,
		u8 port, क्रमागत bfi_pcअगरn_class personality,
		u16 bw_min, u16 bw_max, bfa_ablk_cbfn_t cbfn, व्योम *cbarg);
bfa_status_t bfa_ablk_pf_delete(काष्ठा bfa_ablk_s *ablk, पूर्णांक pcअगरn,
		bfa_ablk_cbfn_t cbfn, व्योम *cbarg);
bfa_status_t bfa_ablk_pf_update(काष्ठा bfa_ablk_s *ablk, पूर्णांक pcअगरn,
		u16 bw_min, u16 bw_max, bfa_ablk_cbfn_t cbfn, व्योम *cbarg);
bfa_status_t bfa_ablk_optrom_en(काष्ठा bfa_ablk_s *ablk,
		bfa_ablk_cbfn_t cbfn, व्योम *cbarg);
bfa_status_t bfa_ablk_optrom_dis(काष्ठा bfa_ablk_s *ablk,
		bfa_ablk_cbfn_t cbfn, व्योम *cbarg);

bfa_status_t bfa_ioc_flash_img_get_chnk(काष्ठा bfa_ioc_s *ioc, u32 off,
				u32 *fwimg);
/*
 * bfa mfg wwn API functions
 */
mac_t bfa_ioc_get_mac(काष्ठा bfa_ioc_s *ioc);
mac_t bfa_ioc_get_mfg_mac(काष्ठा bfa_ioc_s *ioc);

/*
 * F/W Image Size & Chunk
 */
बाह्य u32 bfi_image_cb_size;
बाह्य u32 bfi_image_ct_size;
बाह्य u32 bfi_image_ct2_size;
बाह्य u32 *bfi_image_cb;
बाह्य u32 *bfi_image_ct;
बाह्य u32 *bfi_image_ct2;

अटल अंतरभूत u32 *
bfi_image_cb_get_chunk(u32 off)
अणु
	वापस (u32 *)(bfi_image_cb + off);
पूर्ण

अटल अंतरभूत u32 *
bfi_image_ct_get_chunk(u32 off)
अणु
	वापस (u32 *)(bfi_image_ct + off);
पूर्ण

अटल अंतरभूत u32 *
bfi_image_ct2_get_chunk(u32 off)
अणु
	वापस (u32 *)(bfi_image_ct2 + off);
पूर्ण

अटल अंतरभूत u32*
bfa_cb_image_get_chunk(क्रमागत bfi_asic_gen asic_gen, u32 off)
अणु
	चयन (asic_gen) अणु
	हाल BFI_ASIC_GEN_CB:
		वापस bfi_image_cb_get_chunk(off);
		अवरोध;
	हाल BFI_ASIC_GEN_CT:
		वापस bfi_image_ct_get_chunk(off);
		अवरोध;
	हाल BFI_ASIC_GEN_CT2:
		वापस bfi_image_ct2_get_chunk(off);
		अवरोध;
	शेष:
		वापस शून्य;
	पूर्ण
पूर्ण

अटल अंतरभूत u32
bfa_cb_image_get_size(क्रमागत bfi_asic_gen asic_gen)
अणु
	चयन (asic_gen) अणु
	हाल BFI_ASIC_GEN_CB:
		वापस bfi_image_cb_size;
		अवरोध;
	हाल BFI_ASIC_GEN_CT:
		वापस bfi_image_ct_size;
		अवरोध;
	हाल BFI_ASIC_GEN_CT2:
		वापस bfi_image_ct2_size;
		अवरोध;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

/*
 * CNA TRCMOD declaration
 */
/*
 * !!! Only append to the क्रमागतs defined here to aव्योम any versioning
 * !!! needed between trace utility and driver version
 */
क्रमागत अणु
	BFA_TRC_CNA_PORT	= 1,
	BFA_TRC_CNA_IOC		= 2,
	BFA_TRC_CNA_IOC_CB	= 3,
	BFA_TRC_CNA_IOC_CT	= 4,
पूर्ण;

#पूर्ण_अगर /* __BFA_IOC_H__ */
