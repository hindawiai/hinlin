<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Linux network driver क्रम QLogic BR-series Converged Network Adapter.
 */
/*
 * Copyright (c) 2005-2014 Brocade Communications Systems, Inc.
 * Copyright (c) 2014-2015 QLogic Corporation
 * All rights reserved
 * www.qlogic.com
 */

#अगर_अघोषित __BFA_IOC_H__
#घोषणा __BFA_IOC_H__

#समावेश "bfa_cs.h"
#समावेश "bfi.h"
#समावेश "cna.h"

#घोषणा BFA_IOC_TOV		3000	/* msecs */
#घोषणा BFA_IOC_HWSEM_TOV	500	/* msecs */
#घोषणा BFA_IOC_HB_TOV		500	/* msecs */
#घोषणा BFA_IOC_POLL_TOV	200	/* msecs */
#घोषणा BNA_DBG_FWTRC_LEN      (BFI_IOC_TRC_ENTS * BFI_IOC_TRC_ENT_SZ + \
				BFI_IOC_TRC_HDR_SZ)

/* PCI device inक्रमmation required by IOC */
काष्ठा bfa_pcidev अणु
	पूर्णांक	pci_slot;
	u8	pci_func;
	u16	device_id;
	u16	ssid;
	व्योम	__iomem *pci_bar_kva;
पूर्ण;

/* Structure used to remember the DMA-able memory block's KVA and Physical
 * Address
 */
काष्ठा bfa_dma अणु
	व्योम	*kva;	/* ! Kernel भव address	*/
	u64	pa;	/* ! Physical address		*/
पूर्ण;

#घोषणा BFA_DMA_ALIGN_SZ	256

/* smem size क्रम Crossbow and Catapult */
#घोषणा BFI_SMEM_CB_SIZE	0x200000U	/* ! 2MB क्रम crossbow	*/
#घोषणा BFI_SMEM_CT_SIZE	0x280000U	/* ! 2.5MB क्रम catapult	*/

/* BFA dma address assignment macro. (big endian क्रमmat) */
#घोषणा bfa_dma_be_addr_set(dma_addr, pa)	\
		__bfa_dma_be_addr_set(&dma_addr, (u64)pa)
अटल अंतरभूत व्योम
__bfa_dma_be_addr_set(जोड़ bfi_addr_u *dma_addr, u64 pa)
अणु
	dma_addr->a32.addr_lo = (u32) htonl(pa);
	dma_addr->a32.addr_hi = (u32) htonl(upper_32_bits(pa));
पूर्ण

#घोषणा bfa_alen_set(__alen, __len, __pa)	\
	__bfa_alen_set(__alen, __len, (u64)__pa)

अटल अंतरभूत व्योम
__bfa_alen_set(काष्ठा bfi_alen *alen, u32 len, u64 pa)
अणु
	alen->al_len = cpu_to_be32(len);
	bfa_dma_be_addr_set(alen->al_addr, pa);
पूर्ण

काष्ठा bfa_ioc_regs अणु
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

/* IOC Mailbox काष्ठाures */
प्रकार व्योम (*bfa_mbox_cmd_cbfn_t)(व्योम *cbarg);
काष्ठा bfa_mbox_cmd अणु
	काष्ठा list_head	qe;
	bfa_mbox_cmd_cbfn_t     cbfn;
	व्योम		    *cbarg;
	u32     msg[BFI_IOC_MSGSZ];
पूर्ण;

/* IOC mailbox module */
प्रकार व्योम (*bfa_ioc_mbox_mcfunc_t)(व्योम *cbarg, काष्ठा bfi_mbmsg *m);
काष्ठा bfa_ioc_mbox_mod अणु
	काष्ठा list_head	cmd_q;		/*!< pending mbox queue	*/
	पूर्णांक			nmclass;	/*!< number of handlers */
	काष्ठा अणु
		bfa_ioc_mbox_mcfunc_t	cbfn;	/*!< message handlers	*/
		व्योम			*cbarg;
	पूर्ण mbhdlr[BFI_MC_MAX];
पूर्ण;

/* IOC callback function पूर्णांकerfaces */
प्रकार व्योम (*bfa_ioc_enable_cbfn_t)(व्योम *bfa, क्रमागत bfa_status status);
प्रकार व्योम (*bfa_ioc_disable_cbfn_t)(व्योम *bfa);
प्रकार व्योम (*bfa_ioc_hbfail_cbfn_t)(व्योम *bfa);
प्रकार व्योम (*bfa_ioc_reset_cbfn_t)(व्योम *bfa);
काष्ठा bfa_ioc_cbfn अणु
	bfa_ioc_enable_cbfn_t	enable_cbfn;
	bfa_ioc_disable_cbfn_t	disable_cbfn;
	bfa_ioc_hbfail_cbfn_t	hbfail_cbfn;
	bfa_ioc_reset_cbfn_t	reset_cbfn;
पूर्ण;

/* IOC event notअगरication mechanism. */
क्रमागत bfa_ioc_event अणु
	BFA_IOC_E_ENABLED	= 1,
	BFA_IOC_E_DISABLED	= 2,
	BFA_IOC_E_FAILED	= 3,
पूर्ण;

प्रकार व्योम (*bfa_ioc_notअगरy_cbfn_t)(व्योम *, क्रमागत bfa_ioc_event);

काष्ठा bfa_ioc_notअगरy अणु
	काष्ठा list_head	qe;
	bfa_ioc_notअगरy_cbfn_t	cbfn;
	व्योम			*cbarg;
पूर्ण;

/* Initialize a IOC event notअगरication काष्ठाure */
#घोषणा bfa_ioc_notअगरy_init(__notअगरy, __cbfn, __cbarg) करो अणु	\
	(__notअगरy)->cbfn = (__cbfn);				\
	(__notअगरy)->cbarg = (__cbarg);				\
पूर्ण जबतक (0)

काष्ठा bfa_iocpf अणु
	bfa_fsm_t		fsm;
	काष्ठा bfa_ioc		*ioc;
	bool			fw_mismatch_notअगरied;
	bool			स्वतः_recover;
	u32			poll_समय;
पूर्ण;

काष्ठा bfa_ioc अणु
	bfa_fsm_t		fsm;
	काष्ठा bfa		*bfa;
	काष्ठा bfa_pcidev	pcidev;
	काष्ठा समयr_list	ioc_समयr;
	काष्ठा समयr_list	iocpf_समयr;
	काष्ठा समयr_list	sem_समयr;
	काष्ठा समयr_list	hb_समयr;
	u32			hb_count;
	काष्ठा list_head	notअगरy_q;
	व्योम			*dbg_fwsave;
	पूर्णांक			dbg_fwsave_len;
	bool			dbg_fwsave_once;
	क्रमागत bfi_pcअगरn_class	clscode;
	काष्ठा bfa_ioc_regs	ioc_regs;
	काष्ठा bfa_ioc_drv_stats stats;
	bool			fcmode;
	bool			pllinit;
	bool			stats_busy;	/*!< outstanding stats */
	u8			port_id;

	काष्ठा bfa_dma		attr_dma;
	काष्ठा bfi_ioc_attr	*attr;
	काष्ठा bfa_ioc_cbfn	*cbfn;
	काष्ठा bfa_ioc_mbox_mod	mbox_mod;
	स्थिर काष्ठा bfa_ioc_hwअगर *ioc_hwअगर;
	काष्ठा bfa_iocpf	iocpf;
	क्रमागत bfi_asic_gen	asic_gen;
	क्रमागत bfi_asic_mode	asic_mode;
	क्रमागत bfi_port_mode	port0_mode;
	क्रमागत bfi_port_mode	port1_mode;
	क्रमागत bfa_mode		port_mode;
	u8			ad_cap_bm;	/*!< adapter cap bit mask */
	u8			port_mode_cfg;	/*!< config port mode */
पूर्ण;

काष्ठा bfa_ioc_hwअगर अणु
	क्रमागत bfa_status (*ioc_pll_init) (व्योम __iomem *rb,
						क्रमागत bfi_asic_mode m);
	bool		(*ioc_firmware_lock)	(काष्ठा bfa_ioc *ioc);
	व्योम		(*ioc_firmware_unlock)	(काष्ठा bfa_ioc *ioc);
	व्योम		(*ioc_reg_init)	(काष्ठा bfa_ioc *ioc);
	व्योम		(*ioc_map_port)	(काष्ठा bfa_ioc *ioc);
	व्योम		(*ioc_isr_mode_set)	(काष्ठा bfa_ioc *ioc,
					bool msix);
	व्योम		(*ioc_notअगरy_fail)	(काष्ठा bfa_ioc *ioc);
	व्योम		(*ioc_ownership_reset)	(काष्ठा bfa_ioc *ioc);
	bool		(*ioc_sync_start)       (काष्ठा bfa_ioc *ioc);
	व्योम		(*ioc_sync_join)	(काष्ठा bfa_ioc *ioc);
	व्योम		(*ioc_sync_leave)	(काष्ठा bfa_ioc *ioc);
	व्योम		(*ioc_sync_ack)		(काष्ठा bfa_ioc *ioc);
	bool		(*ioc_sync_complete)	(काष्ठा bfa_ioc *ioc);
	bool		(*ioc_lpu_पढ़ो_stat)	(काष्ठा bfa_ioc *ioc);
	व्योम		(*ioc_set_fwstate)	(काष्ठा bfa_ioc *ioc,
					क्रमागत bfi_ioc_state fwstate);
	क्रमागत bfi_ioc_state (*ioc_get_fwstate) (काष्ठा bfa_ioc *ioc);
	व्योम		(*ioc_set_alt_fwstate)	(काष्ठा bfa_ioc *ioc,
					क्रमागत bfi_ioc_state fwstate);
	क्रमागत bfi_ioc_state (*ioc_get_alt_fwstate) (काष्ठा bfa_ioc *ioc);

पूर्ण;

#घोषणा bfa_ioc_pcअगरn(__ioc)		((__ioc)->pcidev.pci_func)
#घोषणा bfa_ioc_devid(__ioc)		((__ioc)->pcidev.device_id)
#घोषणा bfa_ioc_bar0(__ioc)		((__ioc)->pcidev.pci_bar_kva)
#घोषणा bfa_ioc_portid(__ioc)		((__ioc)->port_id)
#घोषणा bfa_ioc_asic_gen(__ioc)		((__ioc)->asic_gen)
#घोषणा bfa_ioc_is_शेष(__ioc)	\
	(bfa_ioc_pcअगरn(__ioc) == bfa_ioc_portid(__ioc))
#घोषणा bfa_ioc_speed_sup(__ioc)	\
	BFI_ADAPTER_GETP(SPEED, (__ioc)->attr->adapter_prop)
#घोषणा bfa_ioc_get_nports(__ioc)	\
	BFI_ADAPTER_GETP(NPORTS, (__ioc)->attr->adapter_prop)

#घोषणा bfa_ioc_stats(_ioc, _stats)	((_ioc)->stats._stats++)
#घोषणा bfa_ioc_stats_hb_count(_ioc, _hb_count)	\
	((_ioc)->stats.hb_count = (_hb_count))
#घोषणा BFA_IOC_FWIMG_MINSZ	(16 * 1024)
#घोषणा BFA_IOC_FW_SMEM_SIZE(__ioc)					\
	((bfa_ioc_asic_gen(__ioc) == BFI_ASIC_GEN_CB)			\
	? BFI_SMEM_CB_SIZE : BFI_SMEM_CT_SIZE)
#घोषणा BFA_IOC_FLASH_CHUNK_NO(off)		(off / BFI_FLASH_CHUNK_SZ_WORDS)
#घोषणा BFA_IOC_FLASH_OFFSET_IN_CHUNK(off)	(off % BFI_FLASH_CHUNK_SZ_WORDS)
#घोषणा BFA_IOC_FLASH_CHUNK_ADDR(chunkno)  (chunkno * BFI_FLASH_CHUNK_SZ_WORDS)

/* IOC mailbox पूर्णांकerface */
bool bfa_nw_ioc_mbox_queue(काष्ठा bfa_ioc *ioc,
			काष्ठा bfa_mbox_cmd *cmd,
			bfa_mbox_cmd_cbfn_t cbfn, व्योम *cbarg);
व्योम bfa_nw_ioc_mbox_isr(काष्ठा bfa_ioc *ioc);
व्योम bfa_nw_ioc_mbox_regisr(काष्ठा bfa_ioc *ioc, क्रमागत bfi_mclass mc,
		bfa_ioc_mbox_mcfunc_t cbfn, व्योम *cbarg);

/* IOC पूर्णांकerfaces */

#घोषणा bfa_ioc_pll_init_asic(__ioc) \
	((__ioc)->ioc_hwअगर->ioc_pll_init((__ioc)->pcidev.pci_bar_kva, \
			   (__ioc)->asic_mode))

#घोषणा bfa_ioc_lpu_पढ़ो_stat(__ioc) करो अणु				\
		अगर ((__ioc)->ioc_hwअगर->ioc_lpu_पढ़ो_stat)		\
			((__ioc)->ioc_hwअगर->ioc_lpu_पढ़ो_stat(__ioc));	\
पूर्ण जबतक (0)

व्योम bfa_nw_ioc_set_ct_hwअगर(काष्ठा bfa_ioc *ioc);
व्योम bfa_nw_ioc_set_ct2_hwअगर(काष्ठा bfa_ioc *ioc);
व्योम bfa_nw_ioc_ct2_घातeron(काष्ठा bfa_ioc *ioc);

व्योम bfa_nw_ioc_attach(काष्ठा bfa_ioc *ioc, व्योम *bfa,
		काष्ठा bfa_ioc_cbfn *cbfn);
व्योम bfa_nw_ioc_स्वतः_recover(bool स्वतः_recover);
व्योम bfa_nw_ioc_detach(काष्ठा bfa_ioc *ioc);
व्योम bfa_nw_ioc_pci_init(काष्ठा bfa_ioc *ioc, काष्ठा bfa_pcidev *pcidev,
		क्रमागत bfi_pcअगरn_class clscode);
u32 bfa_nw_ioc_meminfo(व्योम);
व्योम bfa_nw_ioc_mem_claim(काष्ठा bfa_ioc *ioc,  u8 *dm_kva, u64 dm_pa);
व्योम bfa_nw_ioc_enable(काष्ठा bfa_ioc *ioc);
व्योम bfa_nw_ioc_disable(काष्ठा bfa_ioc *ioc);

व्योम bfa_nw_ioc_error_isr(काष्ठा bfa_ioc *ioc);
bool bfa_nw_ioc_is_disabled(काष्ठा bfa_ioc *ioc);
bool bfa_nw_ioc_is_operational(काष्ठा bfa_ioc *ioc);
व्योम bfa_nw_ioc_get_attr(काष्ठा bfa_ioc *ioc, काष्ठा bfa_ioc_attr *ioc_attr);
क्रमागत bfa_status bfa_nw_ioc_fwsig_invalidate(काष्ठा bfa_ioc *ioc);
व्योम bfa_nw_ioc_notअगरy_रेजिस्टर(काष्ठा bfa_ioc *ioc,
	काष्ठा bfa_ioc_notअगरy *notअगरy);
bool bfa_nw_ioc_sem_get(व्योम __iomem *sem_reg);
व्योम bfa_nw_ioc_sem_release(व्योम __iomem *sem_reg);
व्योम bfa_nw_ioc_hw_sem_release(काष्ठा bfa_ioc *ioc);
व्योम bfa_nw_ioc_fwver_get(काष्ठा bfa_ioc *ioc,
			काष्ठा bfi_ioc_image_hdr *fwhdr);
bool bfa_nw_ioc_fwver_cmp(काष्ठा bfa_ioc *ioc,
			काष्ठा bfi_ioc_image_hdr *fwhdr);
व्योम bfa_nw_ioc_get_mac(काष्ठा bfa_ioc *ioc, u8 *mac);
व्योम bfa_nw_ioc_debug_memclaim(काष्ठा bfa_ioc *ioc, व्योम *dbg_fwsave);
पूर्णांक bfa_nw_ioc_debug_fwtrc(काष्ठा bfa_ioc *ioc, व्योम *trcdata, पूर्णांक *trclen);
पूर्णांक bfa_nw_ioc_debug_fwsave(काष्ठा bfa_ioc *ioc, व्योम *trcdata, पूर्णांक *trclen);

/*
 * Timeout APIs
 */
व्योम bfa_nw_ioc_समयout(काष्ठा bfa_ioc *ioc);
व्योम bfa_nw_ioc_hb_check(काष्ठा bfa_ioc *ioc);
व्योम bfa_nw_iocpf_समयout(काष्ठा bfa_ioc *ioc);
व्योम bfa_nw_iocpf_sem_समयout(काष्ठा bfa_ioc *ioc);

/*
 * F/W Image Size & Chunk
 */
u32 *bfa_cb_image_get_chunk(क्रमागत bfi_asic_gen asic_gen, u32 off);
u32 bfa_cb_image_get_size(क्रमागत bfi_asic_gen asic_gen);

/*
 *	Flash module specअगरic
 */
प्रकार व्योम	(*bfa_cb_flash) (व्योम *cbarg, क्रमागत bfa_status status);

काष्ठा bfa_flash अणु
	काष्ठा bfa_ioc *ioc;		/* back poपूर्णांकer to ioc */
	u32		type;		/* partition type */
	u8		instance;	/* partition instance */
	u8		rsv[3];
	u32		op_busy;	/*  operation busy flag */
	u32		residue;	/*  residual length */
	u32		offset;		/*  offset */
	क्रमागत bfa_status	status;		/*  status */
	u8		*dbuf_kva;	/*  dma buf भव address */
	u64		dbuf_pa;	/*  dma buf physical address */
	bfa_cb_flash	cbfn;		/*  user callback function */
	व्योम		*cbarg;		/*  user callback arg */
	u8		*ubuf;		/*  user supplied buffer */
	u32		addr_off;	/*  partition address offset */
	काष्ठा bfa_mbox_cmd mb;		/*  mailbox */
	काष्ठा bfa_ioc_notअगरy ioc_notअगरy; /*  ioc event notअगरy */
पूर्ण;

क्रमागत bfa_status bfa_nw_flash_get_attr(काष्ठा bfa_flash *flash,
			काष्ठा bfa_flash_attr *attr,
			bfa_cb_flash cbfn, व्योम *cbarg);
क्रमागत bfa_status bfa_nw_flash_update_part(काष्ठा bfa_flash *flash,
			u32 type, u8 instance, व्योम *buf, u32 len, u32 offset,
			bfa_cb_flash cbfn, व्योम *cbarg);
क्रमागत bfa_status bfa_nw_flash_पढ़ो_part(काष्ठा bfa_flash *flash,
			u32 type, u8 instance, व्योम *buf, u32 len, u32 offset,
			bfa_cb_flash cbfn, व्योम *cbarg);
u32	bfa_nw_flash_meminfo(व्योम);
व्योम	bfa_nw_flash_attach(काष्ठा bfa_flash *flash,
			    काष्ठा bfa_ioc *ioc, व्योम *dev);
व्योम	bfa_nw_flash_memclaim(काष्ठा bfa_flash *flash, u8 *dm_kva, u64 dm_pa);

#पूर्ण_अगर /* __BFA_IOC_H__ */
