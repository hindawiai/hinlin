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
#समावेश "bfi_reg.h"

BFA_TRC_खाता(HAL, CORE);

/*
 * Message handlers क्रम various modules.
 */
अटल bfa_isr_func_t  bfa_isrs[BFI_MC_MAX] = अणु
	bfa_isr_unhandled,	/* NONE */
	bfa_isr_unhandled,	/* BFI_MC_IOC */
	bfa_fcdiag_पूर्णांकr,	/* BFI_MC_DIAG */
	bfa_isr_unhandled,	/* BFI_MC_FLASH */
	bfa_isr_unhandled,	/* BFI_MC_CEE */
	bfa_fcport_isr,		/* BFI_MC_FCPORT */
	bfa_isr_unhandled,	/* BFI_MC_IOCFC */
	bfa_isr_unhandled,	/* BFI_MC_LL */
	bfa_uf_isr,		/* BFI_MC_UF */
	bfa_fcxp_isr,		/* BFI_MC_FCXP */
	bfa_lps_isr,		/* BFI_MC_LPS */
	bfa_rport_isr,		/* BFI_MC_RPORT */
	bfa_itn_isr,		/* BFI_MC_ITN */
	bfa_isr_unhandled,	/* BFI_MC_IOIM_READ */
	bfa_isr_unhandled,	/* BFI_MC_IOIM_WRITE */
	bfa_isr_unhandled,	/* BFI_MC_IOIM_IO */
	bfa_ioim_isr,		/* BFI_MC_IOIM */
	bfa_ioim_good_comp_isr,	/* BFI_MC_IOIM_IOCOM */
	bfa_tskim_isr,		/* BFI_MC_TSKIM */
	bfa_isr_unhandled,	/* BFI_MC_SBOOT */
	bfa_isr_unhandled,	/* BFI_MC_IPFC */
	bfa_isr_unhandled,	/* BFI_MC_PORT */
	bfa_isr_unhandled,	/* --------- */
	bfa_isr_unhandled,	/* --------- */
	bfa_isr_unhandled,	/* --------- */
	bfa_isr_unhandled,	/* --------- */
	bfa_isr_unhandled,	/* --------- */
	bfa_isr_unhandled,	/* --------- */
	bfa_isr_unhandled,	/* --------- */
	bfa_isr_unhandled,	/* --------- */
	bfa_isr_unhandled,	/* --------- */
	bfa_isr_unhandled,	/* --------- */
पूर्ण;
/*
 * Message handlers क्रम mailbox command classes
 */
अटल bfa_ioc_mbox_mcfunc_t  bfa_mbox_isrs[BFI_MC_MAX] = अणु
	शून्य,
	शून्य,		/* BFI_MC_IOC   */
	शून्य,		/* BFI_MC_DIAG  */
	शून्य,		/* BFI_MC_FLASH */
	शून्य,		/* BFI_MC_CEE   */
	शून्य,		/* BFI_MC_PORT  */
	bfa_iocfc_isr,	/* BFI_MC_IOCFC */
	शून्य,
पूर्ण;



व्योम
__bfa_trc(काष्ठा bfa_trc_mod_s *trcm, पूर्णांक fileno, पूर्णांक line, u64 data)
अणु
	पूर्णांक		tail = trcm->tail;
	काष्ठा bfa_trc_s	*trc = &trcm->trc[tail];

	अगर (trcm->stopped)
		वापस;

	trc->fileno = (u16) fileno;
	trc->line = (u16) line;
	trc->data.u64 = data;
	trc->बारtamp = BFA_TRC_TS(trcm);

	trcm->tail = (trcm->tail + 1) & (BFA_TRC_MAX - 1);
	अगर (trcm->tail == trcm->head)
		trcm->head = (trcm->head + 1) & (BFA_TRC_MAX - 1);
पूर्ण

अटल व्योम
bfa_com_port_attach(काष्ठा bfa_s *bfa)
अणु
	काष्ठा bfa_port_s	*port = &bfa->modules.port;
	काष्ठा bfa_mem_dma_s	*port_dma = BFA_MEM_PORT_DMA(bfa);

	bfa_port_attach(port, &bfa->ioc, bfa, bfa->trcmod);
	bfa_port_mem_claim(port, port_dma->kva_curp, port_dma->dma_curp);
पूर्ण

/*
 * ablk module attach
 */
अटल व्योम
bfa_com_ablk_attach(काष्ठा bfa_s *bfa)
अणु
	काष्ठा bfa_ablk_s	*ablk = &bfa->modules.ablk;
	काष्ठा bfa_mem_dma_s	*ablk_dma = BFA_MEM_ABLK_DMA(bfa);

	bfa_ablk_attach(ablk, &bfa->ioc);
	bfa_ablk_memclaim(ablk, ablk_dma->kva_curp, ablk_dma->dma_curp);
पूर्ण

अटल व्योम
bfa_com_cee_attach(काष्ठा bfa_s *bfa)
अणु
	काष्ठा bfa_cee_s	*cee = &bfa->modules.cee;
	काष्ठा bfa_mem_dma_s	*cee_dma = BFA_MEM_CEE_DMA(bfa);

	cee->trcmod = bfa->trcmod;
	bfa_cee_attach(cee, &bfa->ioc, bfa);
	bfa_cee_mem_claim(cee, cee_dma->kva_curp, cee_dma->dma_curp);
पूर्ण

अटल व्योम
bfa_com_sfp_attach(काष्ठा bfa_s *bfa)
अणु
	काष्ठा bfa_sfp_s	*sfp = BFA_SFP_MOD(bfa);
	काष्ठा bfa_mem_dma_s	*sfp_dma = BFA_MEM_SFP_DMA(bfa);

	bfa_sfp_attach(sfp, &bfa->ioc, bfa, bfa->trcmod);
	bfa_sfp_memclaim(sfp, sfp_dma->kva_curp, sfp_dma->dma_curp);
पूर्ण

अटल व्योम
bfa_com_flash_attach(काष्ठा bfa_s *bfa, bfa_boolean_t mincfg)
अणु
	काष्ठा bfa_flash_s	*flash = BFA_FLASH(bfa);
	काष्ठा bfa_mem_dma_s	*flash_dma = BFA_MEM_FLASH_DMA(bfa);

	bfa_flash_attach(flash, &bfa->ioc, bfa, bfa->trcmod, mincfg);
	bfa_flash_memclaim(flash, flash_dma->kva_curp,
			   flash_dma->dma_curp, mincfg);
पूर्ण

अटल व्योम
bfa_com_diag_attach(काष्ठा bfa_s *bfa)
अणु
	काष्ठा bfa_diag_s	*diag = BFA_DIAG_MOD(bfa);
	काष्ठा bfa_mem_dma_s	*diag_dma = BFA_MEM_DIAG_DMA(bfa);

	bfa_diag_attach(diag, &bfa->ioc, bfa, bfa_fcport_beacon, bfa->trcmod);
	bfa_diag_memclaim(diag, diag_dma->kva_curp, diag_dma->dma_curp);
पूर्ण

अटल व्योम
bfa_com_phy_attach(काष्ठा bfa_s *bfa, bfa_boolean_t mincfg)
अणु
	काष्ठा bfa_phy_s	*phy = BFA_PHY(bfa);
	काष्ठा bfa_mem_dma_s	*phy_dma = BFA_MEM_PHY_DMA(bfa);

	bfa_phy_attach(phy, &bfa->ioc, bfa, bfa->trcmod, mincfg);
	bfa_phy_memclaim(phy, phy_dma->kva_curp, phy_dma->dma_curp, mincfg);
पूर्ण

अटल व्योम
bfa_com_fru_attach(काष्ठा bfa_s *bfa, bfa_boolean_t mincfg)
अणु
	काष्ठा bfa_fru_s	*fru = BFA_FRU(bfa);
	काष्ठा bfa_mem_dma_s	*fru_dma = BFA_MEM_FRU_DMA(bfa);

	bfa_fru_attach(fru, &bfa->ioc, bfa, bfa->trcmod, mincfg);
	bfa_fru_memclaim(fru, fru_dma->kva_curp, fru_dma->dma_curp, mincfg);
पूर्ण

/*
 * BFA IOC FC related definitions
 */

/*
 * IOC local definitions
 */
#घोषणा BFA_IOCFC_TOV		5000	/* msecs */

क्रमागत अणु
	BFA_IOCFC_ACT_NONE	= 0,
	BFA_IOCFC_ACT_INIT	= 1,
	BFA_IOCFC_ACT_STOP	= 2,
	BFA_IOCFC_ACT_DISABLE	= 3,
	BFA_IOCFC_ACT_ENABLE	= 4,
पूर्ण;

#घोषणा DEF_CFG_NUM_FABRICS		1
#घोषणा DEF_CFG_NUM_LPORTS		256
#घोषणा DEF_CFG_NUM_CQS			4
#घोषणा DEF_CFG_NUM_IOIM_REQS		(BFA_IOIM_MAX)
#घोषणा DEF_CFG_NUM_TSKIM_REQS		128
#घोषणा DEF_CFG_NUM_FCXP_REQS		64
#घोषणा DEF_CFG_NUM_UF_BUFS		64
#घोषणा DEF_CFG_NUM_RPORTS		1024
#घोषणा DEF_CFG_NUM_ITNIMS		(DEF_CFG_NUM_RPORTS)
#घोषणा DEF_CFG_NUM_TINS		256

#घोषणा DEF_CFG_NUM_SGPGS		2048
#घोषणा DEF_CFG_NUM_REQQ_ELEMS		256
#घोषणा DEF_CFG_NUM_RSPQ_ELEMS		64
#घोषणा DEF_CFG_NUM_SBOOT_TGTS		16
#घोषणा DEF_CFG_NUM_SBOOT_LUNS		16

/*
 * IOCFC state machine definitions/declarations
 */
bfa_fsm_state_decl(bfa_iocfc, stopped, काष्ठा bfa_iocfc_s, क्रमागत iocfc_event);
bfa_fsm_state_decl(bfa_iocfc, initing, काष्ठा bfa_iocfc_s, क्रमागत iocfc_event);
bfa_fsm_state_decl(bfa_iocfc, dconf_पढ़ो, काष्ठा bfa_iocfc_s, क्रमागत iocfc_event);
bfa_fsm_state_decl(bfa_iocfc, init_cfg_रुको,
		   काष्ठा bfa_iocfc_s, क्रमागत iocfc_event);
bfa_fsm_state_decl(bfa_iocfc, init_cfg_करोne,
		   काष्ठा bfa_iocfc_s, क्रमागत iocfc_event);
bfa_fsm_state_decl(bfa_iocfc, operational,
		   काष्ठा bfa_iocfc_s, क्रमागत iocfc_event);
bfa_fsm_state_decl(bfa_iocfc, dconf_ग_लिखो,
		   काष्ठा bfa_iocfc_s, क्रमागत iocfc_event);
bfa_fsm_state_decl(bfa_iocfc, stopping, काष्ठा bfa_iocfc_s, क्रमागत iocfc_event);
bfa_fsm_state_decl(bfa_iocfc, enabling, काष्ठा bfa_iocfc_s, क्रमागत iocfc_event);
bfa_fsm_state_decl(bfa_iocfc, cfg_रुको, काष्ठा bfa_iocfc_s, क्रमागत iocfc_event);
bfa_fsm_state_decl(bfa_iocfc, disabling, काष्ठा bfa_iocfc_s, क्रमागत iocfc_event);
bfa_fsm_state_decl(bfa_iocfc, disabled, काष्ठा bfa_iocfc_s, क्रमागत iocfc_event);
bfa_fsm_state_decl(bfa_iocfc, failed, काष्ठा bfa_iocfc_s, क्रमागत iocfc_event);
bfa_fsm_state_decl(bfa_iocfc, init_failed,
		   काष्ठा bfa_iocfc_s, क्रमागत iocfc_event);

/*
 * क्रमward declaration क्रम IOC FC functions
 */
अटल व्योम bfa_iocfc_start_submod(काष्ठा bfa_s *bfa);
अटल व्योम bfa_iocfc_disable_submod(काष्ठा bfa_s *bfa);
अटल व्योम bfa_iocfc_send_cfg(व्योम *bfa_arg);
अटल व्योम bfa_iocfc_enable_cbfn(व्योम *bfa_arg, क्रमागत bfa_status status);
अटल व्योम bfa_iocfc_disable_cbfn(व्योम *bfa_arg);
अटल व्योम bfa_iocfc_hbfail_cbfn(व्योम *bfa_arg);
अटल व्योम bfa_iocfc_reset_cbfn(व्योम *bfa_arg);
अटल काष्ठा bfa_ioc_cbfn_s bfa_iocfc_cbfn;
अटल व्योम bfa_iocfc_init_cb(व्योम *bfa_arg, bfa_boolean_t complete);
अटल व्योम bfa_iocfc_stop_cb(व्योम *bfa_arg, bfa_boolean_t compl);
अटल व्योम bfa_iocfc_enable_cb(व्योम *bfa_arg, bfa_boolean_t compl);
अटल व्योम bfa_iocfc_disable_cb(व्योम *bfa_arg, bfa_boolean_t compl);

अटल व्योम
bfa_iocfc_sm_stopped_entry(काष्ठा bfa_iocfc_s *iocfc)
अणु
पूर्ण

अटल व्योम
bfa_iocfc_sm_stopped(काष्ठा bfa_iocfc_s *iocfc, क्रमागत iocfc_event event)
अणु
	bfa_trc(iocfc->bfa, event);

	चयन (event) अणु
	हाल IOCFC_E_INIT:
	हाल IOCFC_E_ENABLE:
		bfa_fsm_set_state(iocfc, bfa_iocfc_sm_initing);
		अवरोध;
	शेष:
		bfa_sm_fault(iocfc->bfa, event);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम
bfa_iocfc_sm_initing_entry(काष्ठा bfa_iocfc_s *iocfc)
अणु
	bfa_ioc_enable(&iocfc->bfa->ioc);
पूर्ण

अटल व्योम
bfa_iocfc_sm_initing(काष्ठा bfa_iocfc_s *iocfc, क्रमागत iocfc_event event)
अणु
	bfa_trc(iocfc->bfa, event);

	चयन (event) अणु
	हाल IOCFC_E_IOC_ENABLED:
		bfa_fsm_set_state(iocfc, bfa_iocfc_sm_dconf_पढ़ो);
		अवरोध;

	हाल IOCFC_E_DISABLE:
		bfa_fsm_set_state(iocfc, bfa_iocfc_sm_disabling);
		अवरोध;

	हाल IOCFC_E_STOP:
		bfa_fsm_set_state(iocfc, bfa_iocfc_sm_stopping);
		अवरोध;

	हाल IOCFC_E_IOC_FAILED:
		bfa_fsm_set_state(iocfc, bfa_iocfc_sm_init_failed);
		अवरोध;
	शेष:
		bfa_sm_fault(iocfc->bfa, event);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम
bfa_iocfc_sm_dconf_पढ़ो_entry(काष्ठा bfa_iocfc_s *iocfc)
अणु
	bfa_dconf_modinit(iocfc->bfa);
पूर्ण

अटल व्योम
bfa_iocfc_sm_dconf_पढ़ो(काष्ठा bfa_iocfc_s *iocfc, क्रमागत iocfc_event event)
अणु
	bfa_trc(iocfc->bfa, event);

	चयन (event) अणु
	हाल IOCFC_E_DCONF_DONE:
		bfa_fsm_set_state(iocfc, bfa_iocfc_sm_init_cfg_रुको);
		अवरोध;

	हाल IOCFC_E_DISABLE:
		bfa_fsm_set_state(iocfc, bfa_iocfc_sm_disabling);
		अवरोध;

	हाल IOCFC_E_STOP:
		bfa_fsm_set_state(iocfc, bfa_iocfc_sm_stopping);
		अवरोध;

	हाल IOCFC_E_IOC_FAILED:
		bfa_fsm_set_state(iocfc, bfa_iocfc_sm_init_failed);
		अवरोध;
	शेष:
		bfa_sm_fault(iocfc->bfa, event);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम
bfa_iocfc_sm_init_cfg_रुको_entry(काष्ठा bfa_iocfc_s *iocfc)
अणु
	bfa_iocfc_send_cfg(iocfc->bfa);
पूर्ण

अटल व्योम
bfa_iocfc_sm_init_cfg_रुको(काष्ठा bfa_iocfc_s *iocfc, क्रमागत iocfc_event event)
अणु
	bfa_trc(iocfc->bfa, event);

	चयन (event) अणु
	हाल IOCFC_E_CFG_DONE:
		bfa_fsm_set_state(iocfc, bfa_iocfc_sm_init_cfg_करोne);
		अवरोध;

	हाल IOCFC_E_DISABLE:
		bfa_fsm_set_state(iocfc, bfa_iocfc_sm_disabling);
		अवरोध;

	हाल IOCFC_E_STOP:
		bfa_fsm_set_state(iocfc, bfa_iocfc_sm_stopping);
		अवरोध;

	हाल IOCFC_E_IOC_FAILED:
		bfa_fsm_set_state(iocfc, bfa_iocfc_sm_init_failed);
		अवरोध;
	शेष:
		bfa_sm_fault(iocfc->bfa, event);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम
bfa_iocfc_sm_init_cfg_करोne_entry(काष्ठा bfa_iocfc_s *iocfc)
अणु
	iocfc->bfa->iocfc.op_status = BFA_STATUS_OK;
	bfa_cb_queue(iocfc->bfa, &iocfc->bfa->iocfc.init_hcb_qe,
		     bfa_iocfc_init_cb, iocfc->bfa);
पूर्ण

अटल व्योम
bfa_iocfc_sm_init_cfg_करोne(काष्ठा bfa_iocfc_s *iocfc, क्रमागत iocfc_event event)
अणु
	bfa_trc(iocfc->bfa, event);

	चयन (event) अणु
	हाल IOCFC_E_START:
		bfa_fsm_set_state(iocfc, bfa_iocfc_sm_operational);
		अवरोध;
	हाल IOCFC_E_STOP:
		bfa_fsm_set_state(iocfc, bfa_iocfc_sm_stopping);
		अवरोध;
	हाल IOCFC_E_DISABLE:
		bfa_fsm_set_state(iocfc, bfa_iocfc_sm_disabling);
		अवरोध;
	हाल IOCFC_E_IOC_FAILED:
		bfa_fsm_set_state(iocfc, bfa_iocfc_sm_failed);
		अवरोध;
	शेष:
		bfa_sm_fault(iocfc->bfa, event);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम
bfa_iocfc_sm_operational_entry(काष्ठा bfa_iocfc_s *iocfc)
अणु
	bfa_fcport_init(iocfc->bfa);
	bfa_iocfc_start_submod(iocfc->bfa);
पूर्ण

अटल व्योम
bfa_iocfc_sm_operational(काष्ठा bfa_iocfc_s *iocfc, क्रमागत iocfc_event event)
अणु
	bfa_trc(iocfc->bfa, event);

	चयन (event) अणु
	हाल IOCFC_E_STOP:
		bfa_fsm_set_state(iocfc, bfa_iocfc_sm_dconf_ग_लिखो);
		अवरोध;
	हाल IOCFC_E_DISABLE:
		bfa_fsm_set_state(iocfc, bfa_iocfc_sm_disabling);
		अवरोध;
	हाल IOCFC_E_IOC_FAILED:
		bfa_fsm_set_state(iocfc, bfa_iocfc_sm_failed);
		अवरोध;
	शेष:
		bfa_sm_fault(iocfc->bfa, event);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम
bfa_iocfc_sm_dconf_ग_लिखो_entry(काष्ठा bfa_iocfc_s *iocfc)
अणु
	bfa_dconf_modनिकास(iocfc->bfa);
पूर्ण

अटल व्योम
bfa_iocfc_sm_dconf_ग_लिखो(काष्ठा bfa_iocfc_s *iocfc, क्रमागत iocfc_event event)
अणु
	bfa_trc(iocfc->bfa, event);

	चयन (event) अणु
	हाल IOCFC_E_DCONF_DONE:
	हाल IOCFC_E_IOC_FAILED:
		bfa_fsm_set_state(iocfc, bfa_iocfc_sm_stopping);
		अवरोध;
	शेष:
		bfa_sm_fault(iocfc->bfa, event);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम
bfa_iocfc_sm_stopping_entry(काष्ठा bfa_iocfc_s *iocfc)
अणु
	bfa_ioc_disable(&iocfc->bfa->ioc);
पूर्ण

अटल व्योम
bfa_iocfc_sm_stopping(काष्ठा bfa_iocfc_s *iocfc, क्रमागत iocfc_event event)
अणु
	bfa_trc(iocfc->bfa, event);

	चयन (event) अणु
	हाल IOCFC_E_IOC_DISABLED:
		bfa_isr_disable(iocfc->bfa);
		bfa_iocfc_disable_submod(iocfc->bfa);
		bfa_fsm_set_state(iocfc, bfa_iocfc_sm_stopped);
		iocfc->bfa->iocfc.op_status = BFA_STATUS_OK;
		bfa_cb_queue(iocfc->bfa, &iocfc->bfa->iocfc.stop_hcb_qe,
			     bfa_iocfc_stop_cb, iocfc->bfa);
		अवरोध;

	हाल IOCFC_E_IOC_ENABLED:
	हाल IOCFC_E_DCONF_DONE:
	हाल IOCFC_E_CFG_DONE:
		अवरोध;

	शेष:
		bfa_sm_fault(iocfc->bfa, event);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम
bfa_iocfc_sm_enabling_entry(काष्ठा bfa_iocfc_s *iocfc)
अणु
	bfa_ioc_enable(&iocfc->bfa->ioc);
पूर्ण

अटल व्योम
bfa_iocfc_sm_enabling(काष्ठा bfa_iocfc_s *iocfc, क्रमागत iocfc_event event)
अणु
	bfa_trc(iocfc->bfa, event);

	चयन (event) अणु
	हाल IOCFC_E_IOC_ENABLED:
		bfa_fsm_set_state(iocfc, bfa_iocfc_sm_cfg_रुको);
		अवरोध;

	हाल IOCFC_E_DISABLE:
		bfa_fsm_set_state(iocfc, bfa_iocfc_sm_disabling);
		अवरोध;

	हाल IOCFC_E_STOP:
		bfa_fsm_set_state(iocfc, bfa_iocfc_sm_dconf_ग_लिखो);
		अवरोध;

	हाल IOCFC_E_IOC_FAILED:
		bfa_fsm_set_state(iocfc, bfa_iocfc_sm_failed);

		अगर (iocfc->bfa->iocfc.cb_reqd == BFA_FALSE)
			अवरोध;

		iocfc->bfa->iocfc.op_status = BFA_STATUS_FAILED;
		bfa_cb_queue(iocfc->bfa, &iocfc->bfa->iocfc.en_hcb_qe,
			     bfa_iocfc_enable_cb, iocfc->bfa);
		iocfc->bfa->iocfc.cb_reqd = BFA_FALSE;
		अवरोध;
	शेष:
		bfa_sm_fault(iocfc->bfa, event);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम
bfa_iocfc_sm_cfg_रुको_entry(काष्ठा bfa_iocfc_s *iocfc)
अणु
	bfa_iocfc_send_cfg(iocfc->bfa);
पूर्ण

अटल व्योम
bfa_iocfc_sm_cfg_रुको(काष्ठा bfa_iocfc_s *iocfc, क्रमागत iocfc_event event)
अणु
	bfa_trc(iocfc->bfa, event);

	चयन (event) अणु
	हाल IOCFC_E_CFG_DONE:
		bfa_fsm_set_state(iocfc, bfa_iocfc_sm_operational);
		अगर (iocfc->bfa->iocfc.cb_reqd == BFA_FALSE)
			अवरोध;

		iocfc->bfa->iocfc.op_status = BFA_STATUS_OK;
		bfa_cb_queue(iocfc->bfa, &iocfc->bfa->iocfc.en_hcb_qe,
			     bfa_iocfc_enable_cb, iocfc->bfa);
		iocfc->bfa->iocfc.cb_reqd = BFA_FALSE;
		अवरोध;
	हाल IOCFC_E_DISABLE:
		bfa_fsm_set_state(iocfc, bfa_iocfc_sm_disabling);
		अवरोध;

	हाल IOCFC_E_STOP:
		bfa_fsm_set_state(iocfc, bfa_iocfc_sm_dconf_ग_लिखो);
		अवरोध;
	हाल IOCFC_E_IOC_FAILED:
		bfa_fsm_set_state(iocfc, bfa_iocfc_sm_failed);
		अगर (iocfc->bfa->iocfc.cb_reqd == BFA_FALSE)
			अवरोध;

		iocfc->bfa->iocfc.op_status = BFA_STATUS_FAILED;
		bfa_cb_queue(iocfc->bfa, &iocfc->bfa->iocfc.en_hcb_qe,
			     bfa_iocfc_enable_cb, iocfc->bfa);
		iocfc->bfa->iocfc.cb_reqd = BFA_FALSE;
		अवरोध;
	शेष:
		bfa_sm_fault(iocfc->bfa, event);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम
bfa_iocfc_sm_disabling_entry(काष्ठा bfa_iocfc_s *iocfc)
अणु
	bfa_ioc_disable(&iocfc->bfa->ioc);
पूर्ण

अटल व्योम
bfa_iocfc_sm_disabling(काष्ठा bfa_iocfc_s *iocfc, क्रमागत iocfc_event event)
अणु
	bfa_trc(iocfc->bfa, event);

	चयन (event) अणु
	हाल IOCFC_E_IOC_DISABLED:
		bfa_fsm_set_state(iocfc, bfa_iocfc_sm_disabled);
		अवरोध;
	हाल IOCFC_E_IOC_ENABLED:
	हाल IOCFC_E_DCONF_DONE:
	हाल IOCFC_E_CFG_DONE:
		अवरोध;
	शेष:
		bfa_sm_fault(iocfc->bfa, event);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम
bfa_iocfc_sm_disabled_entry(काष्ठा bfa_iocfc_s *iocfc)
अणु
	bfa_isr_disable(iocfc->bfa);
	bfa_iocfc_disable_submod(iocfc->bfa);
	iocfc->bfa->iocfc.op_status = BFA_STATUS_OK;
	bfa_cb_queue(iocfc->bfa, &iocfc->bfa->iocfc.dis_hcb_qe,
		     bfa_iocfc_disable_cb, iocfc->bfa);
पूर्ण

अटल व्योम
bfa_iocfc_sm_disabled(काष्ठा bfa_iocfc_s *iocfc, क्रमागत iocfc_event event)
अणु
	bfa_trc(iocfc->bfa, event);

	चयन (event) अणु
	हाल IOCFC_E_STOP:
		bfa_fsm_set_state(iocfc, bfa_iocfc_sm_dconf_ग_लिखो);
		अवरोध;
	हाल IOCFC_E_ENABLE:
		bfa_fsm_set_state(iocfc, bfa_iocfc_sm_enabling);
		अवरोध;
	शेष:
		bfa_sm_fault(iocfc->bfa, event);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम
bfa_iocfc_sm_failed_entry(काष्ठा bfa_iocfc_s *iocfc)
अणु
	bfa_isr_disable(iocfc->bfa);
	bfa_iocfc_disable_submod(iocfc->bfa);
पूर्ण

अटल व्योम
bfa_iocfc_sm_failed(काष्ठा bfa_iocfc_s *iocfc, क्रमागत iocfc_event event)
अणु
	bfa_trc(iocfc->bfa, event);

	चयन (event) अणु
	हाल IOCFC_E_STOP:
		bfa_fsm_set_state(iocfc, bfa_iocfc_sm_dconf_ग_लिखो);
		अवरोध;
	हाल IOCFC_E_DISABLE:
		bfa_fsm_set_state(iocfc, bfa_iocfc_sm_disabling);
		अवरोध;
	हाल IOCFC_E_IOC_ENABLED:
		bfa_fsm_set_state(iocfc, bfa_iocfc_sm_cfg_रुको);
		अवरोध;
	हाल IOCFC_E_IOC_FAILED:
		अवरोध;
	शेष:
		bfa_sm_fault(iocfc->bfa, event);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम
bfa_iocfc_sm_init_failed_entry(काष्ठा bfa_iocfc_s *iocfc)
अणु
	bfa_isr_disable(iocfc->bfa);
	iocfc->bfa->iocfc.op_status = BFA_STATUS_FAILED;
	bfa_cb_queue(iocfc->bfa, &iocfc->bfa->iocfc.init_hcb_qe,
		     bfa_iocfc_init_cb, iocfc->bfa);
पूर्ण

अटल व्योम
bfa_iocfc_sm_init_failed(काष्ठा bfa_iocfc_s *iocfc, क्रमागत iocfc_event event)
अणु
	bfa_trc(iocfc->bfa, event);

	चयन (event) अणु
	हाल IOCFC_E_STOP:
		bfa_fsm_set_state(iocfc, bfa_iocfc_sm_stopping);
		अवरोध;
	हाल IOCFC_E_DISABLE:
		bfa_ioc_disable(&iocfc->bfa->ioc);
		अवरोध;
	हाल IOCFC_E_IOC_ENABLED:
		bfa_fsm_set_state(iocfc, bfa_iocfc_sm_dconf_पढ़ो);
		अवरोध;
	हाल IOCFC_E_IOC_DISABLED:
		bfa_fsm_set_state(iocfc, bfa_iocfc_sm_stopped);
		iocfc->bfa->iocfc.op_status = BFA_STATUS_OK;
		bfa_cb_queue(iocfc->bfa, &iocfc->bfa->iocfc.dis_hcb_qe,
			     bfa_iocfc_disable_cb, iocfc->bfa);
		अवरोध;
	हाल IOCFC_E_IOC_FAILED:
		अवरोध;
	शेष:
		bfa_sm_fault(iocfc->bfa, event);
		अवरोध;
	पूर्ण
पूर्ण

/*
 * BFA Interrupt handling functions
 */
अटल व्योम
bfa_reqq_resume(काष्ठा bfa_s *bfa, पूर्णांक qid)
अणु
	काष्ठा list_head *रुकोq, *qe, *qen;
	काष्ठा bfa_reqq_रुको_s *wqe;

	रुकोq = bfa_reqq(bfa, qid);
	list_क्रम_each_safe(qe, qen, रुकोq) अणु
		/*
		 * Callback only as दीर्घ as there is room in request queue
		 */
		अगर (bfa_reqq_full(bfa, qid))
			अवरोध;

		list_del(qe);
		wqe = (काष्ठा bfa_reqq_रुको_s *) qe;
		wqe->qresume(wqe->cbarg);
	पूर्ण
पूर्ण

अटल bfa_boolean_t
bfa_isr_rspq(काष्ठा bfa_s *bfa, पूर्णांक qid)
अणु
	काष्ठा bfi_msg_s *m;
	u32	pi, ci;
	काष्ठा list_head *रुकोq;
	bfa_boolean_t ret;

	ci = bfa_rspq_ci(bfa, qid);
	pi = bfa_rspq_pi(bfa, qid);

	ret = (ci != pi);

	जबतक (ci != pi) अणु
		m = bfa_rspq_elem(bfa, qid, ci);
		WARN_ON(m->mhdr.msg_class >= BFI_MC_MAX);

		bfa_isrs[m->mhdr.msg_class] (bfa, m);
		CQ_INCR(ci, bfa->iocfc.cfg.drvcfg.num_rspq_elems);
	पूर्ण

	/*
	 * acknowledge RME completions and update CI
	 */
	bfa_isr_rspq_ack(bfa, qid, ci);

	/*
	 * Resume any pending requests in the corresponding reqq.
	 */
	रुकोq = bfa_reqq(bfa, qid);
	अगर (!list_empty(रुकोq))
		bfa_reqq_resume(bfa, qid);

	वापस ret;
पूर्ण

अटल अंतरभूत व्योम
bfa_isr_reqq(काष्ठा bfa_s *bfa, पूर्णांक qid)
अणु
	काष्ठा list_head *रुकोq;

	bfa_isr_reqq_ack(bfa, qid);

	/*
	 * Resume any pending requests in the corresponding reqq.
	 */
	रुकोq = bfa_reqq(bfa, qid);
	अगर (!list_empty(रुकोq))
		bfa_reqq_resume(bfa, qid);
पूर्ण

व्योम
bfa_msix_all(काष्ठा bfa_s *bfa, पूर्णांक vec)
अणु
	u32	पूर्णांकr, qपूर्णांकr;
	पूर्णांक	queue;

	पूर्णांकr = पढ़ोl(bfa->iocfc.bfa_regs.पूर्णांकr_status);
	अगर (!पूर्णांकr)
		वापस;

	/*
	 * RME completion queue पूर्णांकerrupt
	 */
	qपूर्णांकr = पूर्णांकr & __HFN_INT_RME_MASK;
	अगर (qपूर्णांकr && bfa->queue_process) अणु
		क्रम (queue = 0; queue < BFI_IOC_MAX_CQS; queue++)
			bfa_isr_rspq(bfa, queue);
	पूर्ण

	पूर्णांकr &= ~qपूर्णांकr;
	अगर (!पूर्णांकr)
		वापस;

	/*
	 * CPE completion queue पूर्णांकerrupt
	 */
	qपूर्णांकr = पूर्णांकr & __HFN_INT_CPE_MASK;
	अगर (qपूर्णांकr && bfa->queue_process) अणु
		क्रम (queue = 0; queue < BFI_IOC_MAX_CQS; queue++)
			bfa_isr_reqq(bfa, queue);
	पूर्ण
	पूर्णांकr &= ~qपूर्णांकr;
	अगर (!पूर्णांकr)
		वापस;

	bfa_msix_lpu_err(bfa, पूर्णांकr);
पूर्ण

bfa_boolean_t
bfa_पूर्णांकx(काष्ठा bfa_s *bfa)
अणु
	u32 पूर्णांकr, qपूर्णांकr;
	पूर्णांक queue;
	bfa_boolean_t rspq_comp = BFA_FALSE;

	पूर्णांकr = पढ़ोl(bfa->iocfc.bfa_regs.पूर्णांकr_status);

	qपूर्णांकr = पूर्णांकr & (__HFN_INT_RME_MASK | __HFN_INT_CPE_MASK);
	अगर (qपूर्णांकr)
		ग_लिखोl(qपूर्णांकr, bfa->iocfc.bfa_regs.पूर्णांकr_status);

	/*
	 * Unconditional RME completion queue पूर्णांकerrupt
	 */
	अगर (bfa->queue_process) अणु
		क्रम (queue = 0; queue < BFI_IOC_MAX_CQS; queue++)
			अगर (bfa_isr_rspq(bfa, queue))
				rspq_comp = BFA_TRUE;
	पूर्ण

	अगर (!पूर्णांकr)
		वापस (qपूर्णांकr | rspq_comp) ? BFA_TRUE : BFA_FALSE;

	/*
	 * CPE completion queue पूर्णांकerrupt
	 */
	qपूर्णांकr = पूर्णांकr & __HFN_INT_CPE_MASK;
	अगर (qपूर्णांकr && bfa->queue_process) अणु
		क्रम (queue = 0; queue < BFI_IOC_MAX_CQS; queue++)
			bfa_isr_reqq(bfa, queue);
	पूर्ण
	पूर्णांकr &= ~qपूर्णांकr;
	अगर (!पूर्णांकr)
		वापस BFA_TRUE;

	अगर (bfa->पूर्णांकr_enabled)
		bfa_msix_lpu_err(bfa, पूर्णांकr);

	वापस BFA_TRUE;
पूर्ण

व्योम
bfa_isr_enable(काष्ठा bfa_s *bfa)
अणु
	u32 umsk;
	पूर्णांक port_id = bfa_ioc_portid(&bfa->ioc);

	bfa_trc(bfa, bfa_ioc_pcअगरn(&bfa->ioc));
	bfa_trc(bfa, port_id);

	bfa_msix_ctrl_install(bfa);

	अगर (bfa_asic_id_ct2(bfa->ioc.pcidev.device_id)) अणु
		umsk = __HFN_INT_ERR_MASK_CT2;
		umsk |= port_id == 0 ?
			__HFN_INT_FN0_MASK_CT2 : __HFN_INT_FN1_MASK_CT2;
	पूर्ण अन्यथा अणु
		umsk = __HFN_INT_ERR_MASK;
		umsk |= port_id == 0 ? __HFN_INT_FN0_MASK : __HFN_INT_FN1_MASK;
	पूर्ण

	ग_लिखोl(umsk, bfa->iocfc.bfa_regs.पूर्णांकr_status);
	ग_लिखोl(~umsk, bfa->iocfc.bfa_regs.पूर्णांकr_mask);
	bfa->iocfc.पूर्णांकr_mask = ~umsk;
	bfa_isr_mode_set(bfa, bfa->msix.nvecs != 0);

	/*
	 * Set the flag indicating successful enabling of पूर्णांकerrupts
	 */
	bfa->पूर्णांकr_enabled = BFA_TRUE;
पूर्ण

व्योम
bfa_isr_disable(काष्ठा bfa_s *bfa)
अणु
	bfa->पूर्णांकr_enabled = BFA_FALSE;
	bfa_isr_mode_set(bfa, BFA_FALSE);
	ग_लिखोl(-1L, bfa->iocfc.bfa_regs.पूर्णांकr_mask);
	bfa_msix_uninstall(bfa);
पूर्ण

व्योम
bfa_msix_reqq(काष्ठा bfa_s *bfa, पूर्णांक vec)
अणु
	bfa_isr_reqq(bfa, vec - bfa->iocfc.hwअगर.cpe_vec_q0);
पूर्ण

व्योम
bfa_isr_unhandled(काष्ठा bfa_s *bfa, काष्ठा bfi_msg_s *m)
अणु
	bfa_trc(bfa, m->mhdr.msg_class);
	bfa_trc(bfa, m->mhdr.msg_id);
	bfa_trc(bfa, m->mhdr.mtag.i2htok);
	WARN_ON(1);
	bfa_trc_stop(bfa->trcmod);
पूर्ण

व्योम
bfa_msix_rspq(काष्ठा bfa_s *bfa, पूर्णांक vec)
अणु
	bfa_isr_rspq(bfa, vec - bfa->iocfc.hwअगर.rme_vec_q0);
पूर्ण

व्योम
bfa_msix_lpu_err(काष्ठा bfa_s *bfa, पूर्णांक vec)
अणु
	u32 पूर्णांकr, curr_value;
	bfa_boolean_t lpu_isr, halt_isr, pss_isr;

	पूर्णांकr = पढ़ोl(bfa->iocfc.bfa_regs.पूर्णांकr_status);

	अगर (bfa_asic_id_ct2(bfa->ioc.pcidev.device_id)) अणु
		halt_isr = पूर्णांकr & __HFN_INT_CPQ_HALT_CT2;
		pss_isr  = पूर्णांकr & __HFN_INT_ERR_PSS_CT2;
		lpu_isr  = पूर्णांकr & (__HFN_INT_MBOX_LPU0_CT2 |
				   __HFN_INT_MBOX_LPU1_CT2);
		पूर्णांकr    &= __HFN_INT_ERR_MASK_CT2;
	पूर्ण अन्यथा अणु
		halt_isr = bfa_asic_id_ct(bfa->ioc.pcidev.device_id) ?
					  (पूर्णांकr & __HFN_INT_LL_HALT) : 0;
		pss_isr  = पूर्णांकr & __HFN_INT_ERR_PSS;
		lpu_isr  = पूर्णांकr & (__HFN_INT_MBOX_LPU0 | __HFN_INT_MBOX_LPU1);
		पूर्णांकr    &= __HFN_INT_ERR_MASK;
	पूर्ण

	अगर (lpu_isr)
		bfa_ioc_mbox_isr(&bfa->ioc);

	अगर (पूर्णांकr) अणु
		अगर (halt_isr) अणु
			/*
			 * If LL_HALT bit is set then FW Init Halt LL Port
			 * Register needs to be cleared as well so Interrupt
			 * Status Register will be cleared.
			 */
			curr_value = पढ़ोl(bfa->ioc.ioc_regs.ll_halt);
			curr_value &= ~__FW_INIT_HALT_P;
			ग_लिखोl(curr_value, bfa->ioc.ioc_regs.ll_halt);
		पूर्ण

		अगर (pss_isr) अणु
			/*
			 * ERR_PSS bit needs to be cleared as well in हाल
			 * पूर्णांकerrups are shared so driver's पूर्णांकerrupt handler is
			 * still called even though it is alपढ़ोy masked out.
			 */
			curr_value = पढ़ोl(
					bfa->ioc.ioc_regs.pss_err_status_reg);
			ग_लिखोl(curr_value,
				bfa->ioc.ioc_regs.pss_err_status_reg);
		पूर्ण

		ग_लिखोl(पूर्णांकr, bfa->iocfc.bfa_regs.पूर्णांकr_status);
		bfa_ioc_error_isr(&bfa->ioc);
	पूर्ण
पूर्ण

/*
 * BFA IOC FC related functions
 */

/*
 *  BFA IOC निजी functions
 */

/*
 * Use the Mailbox पूर्णांकerface to send BFI_IOCFC_H2I_CFG_REQ
 */
अटल व्योम
bfa_iocfc_send_cfg(व्योम *bfa_arg)
अणु
	काष्ठा bfa_s *bfa = bfa_arg;
	काष्ठा bfa_iocfc_s *iocfc = &bfa->iocfc;
	काष्ठा bfi_iocfc_cfg_req_s cfg_req;
	काष्ठा bfi_iocfc_cfg_s *cfg_info = iocfc->cfginfo;
	काष्ठा bfa_iocfc_cfg_s	*cfg = &iocfc->cfg;
	पूर्णांक		i;

	WARN_ON(cfg->fwcfg.num_cqs > BFI_IOC_MAX_CQS);
	bfa_trc(bfa, cfg->fwcfg.num_cqs);

	bfa_iocfc_reset_queues(bfa);

	/*
	 * initialize IOC configuration info
	 */
	cfg_info->single_msix_vec = 0;
	अगर (bfa->msix.nvecs == 1)
		cfg_info->single_msix_vec = 1;
	cfg_info->endian_sig = BFI_IOC_ENDIAN_SIG;
	cfg_info->num_cqs = cfg->fwcfg.num_cqs;
	cfg_info->num_ioim_reqs = cpu_to_be16(bfa_fcpim_get_throttle_cfg(bfa,
					       cfg->fwcfg.num_ioim_reqs));
	cfg_info->num_fwtio_reqs = cpu_to_be16(cfg->fwcfg.num_fwtio_reqs);

	bfa_dma_be_addr_set(cfg_info->cfgrsp_addr, iocfc->cfgrsp_dma.pa);
	/*
	 * dma map REQ and RSP circular queues and shaकरोw poपूर्णांकers
	 */
	क्रम (i = 0; i < cfg->fwcfg.num_cqs; i++) अणु
		bfa_dma_be_addr_set(cfg_info->req_cq_ba[i],
				    iocfc->req_cq_ba[i].pa);
		bfa_dma_be_addr_set(cfg_info->req_shaकरोw_ci[i],
				    iocfc->req_cq_shaकरोw_ci[i].pa);
		cfg_info->req_cq_elems[i] =
			cpu_to_be16(cfg->drvcfg.num_reqq_elems);

		bfa_dma_be_addr_set(cfg_info->rsp_cq_ba[i],
				    iocfc->rsp_cq_ba[i].pa);
		bfa_dma_be_addr_set(cfg_info->rsp_shaकरोw_pi[i],
				    iocfc->rsp_cq_shaकरोw_pi[i].pa);
		cfg_info->rsp_cq_elems[i] =
			cpu_to_be16(cfg->drvcfg.num_rspq_elems);
	पूर्ण

	/*
	 * Enable पूर्णांकerrupt coalescing अगर it is driver init path
	 * and not ioc disable/enable path.
	 */
	अगर (bfa_fsm_cmp_state(iocfc, bfa_iocfc_sm_init_cfg_रुको))
		cfg_info->पूर्णांकr_attr.coalesce = BFA_TRUE;

	/*
	 * dma map IOC configuration itself
	 */
	bfi_h2i_set(cfg_req.mh, BFI_MC_IOCFC, BFI_IOCFC_H2I_CFG_REQ,
		    bfa_fn_lpu(bfa));
	bfa_dma_be_addr_set(cfg_req.ioc_cfg_dma_addr, iocfc->cfg_info.pa);

	bfa_ioc_mbox_send(&bfa->ioc, &cfg_req,
			  माप(काष्ठा bfi_iocfc_cfg_req_s));
पूर्ण

अटल व्योम
bfa_iocfc_init_mem(काष्ठा bfa_s *bfa, व्योम *bfad, काष्ठा bfa_iocfc_cfg_s *cfg,
		   काष्ठा bfa_pcidev_s *pcidev)
अणु
	काष्ठा bfa_iocfc_s	*iocfc = &bfa->iocfc;

	bfa->bfad = bfad;
	iocfc->bfa = bfa;
	iocfc->cfg = *cfg;

	/*
	 * Initialize chip specअगरic handlers.
	 */
	अगर (bfa_asic_id_ctc(bfa_ioc_devid(&bfa->ioc))) अणु
		iocfc->hwअगर.hw_reginit = bfa_hwct_reginit;
		iocfc->hwअगर.hw_reqq_ack = bfa_hwct_reqq_ack;
		iocfc->hwअगर.hw_rspq_ack = bfa_hwct_rspq_ack;
		iocfc->hwअगर.hw_msix_init = bfa_hwct_msix_init;
		iocfc->hwअगर.hw_msix_ctrl_install = bfa_hwct_msix_ctrl_install;
		iocfc->hwअगर.hw_msix_queue_install = bfa_hwct_msix_queue_install;
		iocfc->hwअगर.hw_msix_uninstall = bfa_hwct_msix_uninstall;
		iocfc->hwअगर.hw_isr_mode_set = bfa_hwct_isr_mode_set;
		iocfc->hwअगर.hw_msix_getvecs = bfa_hwct_msix_getvecs;
		iocfc->hwअगर.hw_msix_get_rme_range = bfa_hwct_msix_get_rme_range;
		iocfc->hwअगर.rme_vec_q0 = BFI_MSIX_RME_QMIN_CT;
		iocfc->hwअगर.cpe_vec_q0 = BFI_MSIX_CPE_QMIN_CT;
	पूर्ण अन्यथा अणु
		iocfc->hwअगर.hw_reginit = bfa_hwcb_reginit;
		iocfc->hwअगर.hw_reqq_ack = शून्य;
		iocfc->hwअगर.hw_rspq_ack = bfa_hwcb_rspq_ack;
		iocfc->hwअगर.hw_msix_init = bfa_hwcb_msix_init;
		iocfc->hwअगर.hw_msix_ctrl_install = bfa_hwcb_msix_ctrl_install;
		iocfc->hwअगर.hw_msix_queue_install = bfa_hwcb_msix_queue_install;
		iocfc->hwअगर.hw_msix_uninstall = bfa_hwcb_msix_uninstall;
		iocfc->hwअगर.hw_isr_mode_set = bfa_hwcb_isr_mode_set;
		iocfc->hwअगर.hw_msix_getvecs = bfa_hwcb_msix_getvecs;
		iocfc->hwअगर.hw_msix_get_rme_range = bfa_hwcb_msix_get_rme_range;
		iocfc->hwअगर.rme_vec_q0 = BFI_MSIX_RME_QMIN_CB +
			bfa_ioc_pcअगरn(&bfa->ioc) * BFI_IOC_MAX_CQS;
		iocfc->hwअगर.cpe_vec_q0 = BFI_MSIX_CPE_QMIN_CB +
			bfa_ioc_pcअगरn(&bfa->ioc) * BFI_IOC_MAX_CQS;
	पूर्ण

	अगर (bfa_asic_id_ct2(bfa_ioc_devid(&bfa->ioc))) अणु
		iocfc->hwअगर.hw_reginit = bfa_hwct2_reginit;
		iocfc->hwअगर.hw_isr_mode_set = शून्य;
		iocfc->hwअगर.hw_rspq_ack = bfa_hwct2_rspq_ack;
	पूर्ण

	iocfc->hwअगर.hw_reginit(bfa);
	bfa->msix.nvecs = 0;
पूर्ण

अटल व्योम
bfa_iocfc_mem_claim(काष्ठा bfa_s *bfa, काष्ठा bfa_iocfc_cfg_s *cfg)
अणु
	u8	*dm_kva = शून्य;
	u64	dm_pa = 0;
	पूर्णांक	i, per_reqq_sz, per_rspq_sz;
	काष्ठा bfa_iocfc_s  *iocfc = &bfa->iocfc;
	काष्ठा bfa_mem_dma_s *ioc_dma = BFA_MEM_IOC_DMA(bfa);
	काष्ठा bfa_mem_dma_s *iocfc_dma = BFA_MEM_IOCFC_DMA(bfa);
	काष्ठा bfa_mem_dma_s *reqq_dma, *rspq_dma;

	/* First allocate dma memory क्रम IOC */
	bfa_ioc_mem_claim(&bfa->ioc, bfa_mem_dma_virt(ioc_dma),
			bfa_mem_dma_phys(ioc_dma));

	/* Claim DMA-able memory क्रम the request/response queues */
	per_reqq_sz = BFA_ROUNDUP((cfg->drvcfg.num_reqq_elems * BFI_LMSG_SZ),
				BFA_DMA_ALIGN_SZ);
	per_rspq_sz = BFA_ROUNDUP((cfg->drvcfg.num_rspq_elems * BFI_LMSG_SZ),
				BFA_DMA_ALIGN_SZ);

	क्रम (i = 0; i < cfg->fwcfg.num_cqs; i++) अणु
		reqq_dma = BFA_MEM_REQQ_DMA(bfa, i);
		iocfc->req_cq_ba[i].kva = bfa_mem_dma_virt(reqq_dma);
		iocfc->req_cq_ba[i].pa = bfa_mem_dma_phys(reqq_dma);
		स_रखो(iocfc->req_cq_ba[i].kva, 0, per_reqq_sz);

		rspq_dma = BFA_MEM_RSPQ_DMA(bfa, i);
		iocfc->rsp_cq_ba[i].kva = bfa_mem_dma_virt(rspq_dma);
		iocfc->rsp_cq_ba[i].pa = bfa_mem_dma_phys(rspq_dma);
		स_रखो(iocfc->rsp_cq_ba[i].kva, 0, per_rspq_sz);
	पूर्ण

	/* Claim IOCFC dma memory - क्रम shaकरोw CI/PI */
	dm_kva = bfa_mem_dma_virt(iocfc_dma);
	dm_pa  = bfa_mem_dma_phys(iocfc_dma);

	क्रम (i = 0; i < cfg->fwcfg.num_cqs; i++) अणु
		iocfc->req_cq_shaकरोw_ci[i].kva = dm_kva;
		iocfc->req_cq_shaकरोw_ci[i].pa = dm_pa;
		dm_kva += BFA_CACHELINE_SZ;
		dm_pa += BFA_CACHELINE_SZ;

		iocfc->rsp_cq_shaकरोw_pi[i].kva = dm_kva;
		iocfc->rsp_cq_shaकरोw_pi[i].pa = dm_pa;
		dm_kva += BFA_CACHELINE_SZ;
		dm_pa += BFA_CACHELINE_SZ;
	पूर्ण

	/* Claim IOCFC dma memory - क्रम the config info page */
	bfa->iocfc.cfg_info.kva = dm_kva;
	bfa->iocfc.cfg_info.pa = dm_pa;
	bfa->iocfc.cfginfo = (काष्ठा bfi_iocfc_cfg_s *) dm_kva;
	dm_kva += BFA_ROUNDUP(माप(काष्ठा bfi_iocfc_cfg_s), BFA_CACHELINE_SZ);
	dm_pa += BFA_ROUNDUP(माप(काष्ठा bfi_iocfc_cfg_s), BFA_CACHELINE_SZ);

	/* Claim IOCFC dma memory - क्रम the config response */
	bfa->iocfc.cfgrsp_dma.kva = dm_kva;
	bfa->iocfc.cfgrsp_dma.pa = dm_pa;
	bfa->iocfc.cfgrsp = (काष्ठा bfi_iocfc_cfgrsp_s *) dm_kva;
	dm_kva += BFA_ROUNDUP(माप(काष्ठा bfi_iocfc_cfgrsp_s),
			BFA_CACHELINE_SZ);
	dm_pa += BFA_ROUNDUP(माप(काष्ठा bfi_iocfc_cfgrsp_s),
			BFA_CACHELINE_SZ);

	/* Claim IOCFC kva memory */
	bfa_ioc_debug_memclaim(&bfa->ioc, bfa_mem_kva_curp(iocfc));
	bfa_mem_kva_curp(iocfc) += BFA_DBG_FWTRC_LEN;
पूर्ण

/*
 * Start BFA submodules.
 */
अटल व्योम
bfa_iocfc_start_submod(काष्ठा bfa_s *bfa)
अणु
	पूर्णांक		i;

	bfa->queue_process = BFA_TRUE;
	क्रम (i = 0; i < BFI_IOC_MAX_CQS; i++)
		bfa_isr_rspq_ack(bfa, i, bfa_rspq_ci(bfa, i));

	bfa_fcport_start(bfa);
	bfa_uf_start(bfa);
	/*
	 * bfa_init() with flash पढ़ो is complete. now invalidate the stale
	 * content of lun mask like unit attention, rp tag and lp tag.
	 */
	bfa_ioim_lm_init(BFA_FCP_MOD(bfa)->bfa);

	bfa->iocfc.submod_enabled = BFA_TRUE;
पूर्ण

/*
 * Disable BFA submodules.
 */
अटल व्योम
bfa_iocfc_disable_submod(काष्ठा bfa_s *bfa)
अणु
	अगर (bfa->iocfc.submod_enabled == BFA_FALSE)
		वापस;

	bfa_fcdiag_iocdisable(bfa);
	bfa_fcport_iocdisable(bfa);
	bfa_fcxp_iocdisable(bfa);
	bfa_lps_iocdisable(bfa);
	bfa_rport_iocdisable(bfa);
	bfa_fcp_iocdisable(bfa);
	bfa_dconf_iocdisable(bfa);

	bfa->iocfc.submod_enabled = BFA_FALSE;
पूर्ण

अटल व्योम
bfa_iocfc_init_cb(व्योम *bfa_arg, bfa_boolean_t complete)
अणु
	काष्ठा bfa_s	*bfa = bfa_arg;

	अगर (complete)
		bfa_cb_init(bfa->bfad, bfa->iocfc.op_status);
पूर्ण

अटल व्योम
bfa_iocfc_stop_cb(व्योम *bfa_arg, bfa_boolean_t compl)
अणु
	काष्ठा bfa_s  *bfa = bfa_arg;
	काष्ठा bfad_s *bfad = bfa->bfad;

	अगर (compl)
		complete(&bfad->comp);
पूर्ण

अटल व्योम
bfa_iocfc_enable_cb(व्योम *bfa_arg, bfa_boolean_t compl)
अणु
	काष्ठा bfa_s	*bfa = bfa_arg;
	काष्ठा bfad_s *bfad = bfa->bfad;

	अगर (compl)
		complete(&bfad->enable_comp);
पूर्ण

अटल व्योम
bfa_iocfc_disable_cb(व्योम *bfa_arg, bfa_boolean_t compl)
अणु
	काष्ठा bfa_s  *bfa = bfa_arg;
	काष्ठा bfad_s *bfad = bfa->bfad;

	अगर (compl)
		complete(&bfad->disable_comp);
पूर्ण

/*
 * configure queue रेजिस्टरs from firmware response
 */
अटल व्योम
bfa_iocfc_qreg(काष्ठा bfa_s *bfa, काष्ठा bfi_iocfc_qreg_s *qreg)
अणु
	पूर्णांक     i;
	काष्ठा bfa_iocfc_regs_s *r = &bfa->iocfc.bfa_regs;
	व्योम __iomem *kva = bfa_ioc_bar0(&bfa->ioc);

	क्रम (i = 0; i < BFI_IOC_MAX_CQS; i++) अणु
		bfa->iocfc.hw_qid[i] = qreg->hw_qid[i];
		r->cpe_q_ci[i] = kva + be32_to_cpu(qreg->cpe_q_ci_off[i]);
		r->cpe_q_pi[i] = kva + be32_to_cpu(qreg->cpe_q_pi_off[i]);
		r->cpe_q_ctrl[i] = kva + be32_to_cpu(qreg->cpe_qctl_off[i]);
		r->rme_q_ci[i] = kva + be32_to_cpu(qreg->rme_q_ci_off[i]);
		r->rme_q_pi[i] = kva + be32_to_cpu(qreg->rme_q_pi_off[i]);
		r->rme_q_ctrl[i] = kva + be32_to_cpu(qreg->rme_qctl_off[i]);
	पूर्ण
पूर्ण

अटल व्योम
bfa_iocfc_res_recfg(काष्ठा bfa_s *bfa, काष्ठा bfa_iocfc_fwcfg_s *fwcfg)
अणु
	काष्ठा bfa_iocfc_s	*iocfc   = &bfa->iocfc;
	काष्ठा bfi_iocfc_cfg_s	*cfg_info = iocfc->cfginfo;

	bfa_fcxp_res_recfg(bfa, fwcfg->num_fcxp_reqs);
	bfa_uf_res_recfg(bfa, fwcfg->num_uf_bufs);
	bfa_rport_res_recfg(bfa, fwcfg->num_rports);
	bfa_fcp_res_recfg(bfa, cpu_to_be16(cfg_info->num_ioim_reqs),
			  fwcfg->num_ioim_reqs);
	bfa_tskim_res_recfg(bfa, fwcfg->num_tskim_reqs);
पूर्ण

/*
 * Update BFA configuration from firmware configuration.
 */
अटल व्योम
bfa_iocfc_cfgrsp(काष्ठा bfa_s *bfa)
अणु
	काष्ठा bfa_iocfc_s		*iocfc	 = &bfa->iocfc;
	काष्ठा bfi_iocfc_cfgrsp_s	*cfgrsp	 = iocfc->cfgrsp;
	काष्ठा bfa_iocfc_fwcfg_s	*fwcfg	 = &cfgrsp->fwcfg;

	fwcfg->num_cqs	      = fwcfg->num_cqs;
	fwcfg->num_ioim_reqs  = be16_to_cpu(fwcfg->num_ioim_reqs);
	fwcfg->num_fwtio_reqs = be16_to_cpu(fwcfg->num_fwtio_reqs);
	fwcfg->num_tskim_reqs = be16_to_cpu(fwcfg->num_tskim_reqs);
	fwcfg->num_fcxp_reqs  = be16_to_cpu(fwcfg->num_fcxp_reqs);
	fwcfg->num_uf_bufs    = be16_to_cpu(fwcfg->num_uf_bufs);
	fwcfg->num_rports     = be16_to_cpu(fwcfg->num_rports);

	/*
	 * configure queue रेजिस्टर offsets as learnt from firmware
	 */
	bfa_iocfc_qreg(bfa, &cfgrsp->qreg);

	/*
	 * Re-configure resources as learnt from Firmware
	 */
	bfa_iocfc_res_recfg(bfa, fwcfg);

	/*
	 * Install MSIX queue handlers
	 */
	bfa_msix_queue_install(bfa);

	अगर (bfa->iocfc.cfgrsp->pbc_cfg.pbc_pwwn != 0) अणु
		bfa->ioc.attr->pwwn = bfa->iocfc.cfgrsp->pbc_cfg.pbc_pwwn;
		bfa->ioc.attr->nwwn = bfa->iocfc.cfgrsp->pbc_cfg.pbc_nwwn;
		bfa_fsm_send_event(iocfc, IOCFC_E_CFG_DONE);
	पूर्ण
पूर्ण

व्योम
bfa_iocfc_reset_queues(काष्ठा bfa_s *bfa)
अणु
	पूर्णांक		q;

	क्रम (q = 0; q < BFI_IOC_MAX_CQS; q++) अणु
		bfa_reqq_ci(bfa, q) = 0;
		bfa_reqq_pi(bfa, q) = 0;
		bfa_rspq_ci(bfa, q) = 0;
		bfa_rspq_pi(bfa, q) = 0;
	पूर्ण
पूर्ण

/*
 *	Process FAA pwwn msg from fw.
 */
अटल व्योम
bfa_iocfc_process_faa_addr(काष्ठा bfa_s *bfa, काष्ठा bfi_faa_addr_msg_s *msg)
अणु
	काष्ठा bfa_iocfc_s		*iocfc   = &bfa->iocfc;
	काष्ठा bfi_iocfc_cfgrsp_s	*cfgrsp  = iocfc->cfgrsp;

	cfgrsp->pbc_cfg.pbc_pwwn = msg->pwwn;
	cfgrsp->pbc_cfg.pbc_nwwn = msg->nwwn;

	bfa->ioc.attr->pwwn = msg->pwwn;
	bfa->ioc.attr->nwwn = msg->nwwn;
	bfa_fsm_send_event(iocfc, IOCFC_E_CFG_DONE);
पूर्ण

/* Fabric Asचिन्हित Address specअगरic functions */

/*
 *	Check whether IOC is पढ़ोy beक्रमe sending command करोwn
 */
अटल bfa_status_t
bfa_faa_validate_request(काष्ठा bfa_s *bfa)
अणु
	क्रमागत bfa_ioc_type_e	ioc_type = bfa_get_type(bfa);
	u32	card_type = bfa->ioc.attr->card_type;

	अगर (bfa_ioc_is_operational(&bfa->ioc)) अणु
		अगर ((ioc_type != BFA_IOC_TYPE_FC) || bfa_mfg_is_mezz(card_type))
			वापस BFA_STATUS_FEATURE_NOT_SUPPORTED;
	पूर्ण अन्यथा अणु
		वापस BFA_STATUS_IOC_NON_OP;
	पूर्ण

	वापस BFA_STATUS_OK;
पूर्ण

bfa_status_t
bfa_faa_query(काष्ठा bfa_s *bfa, काष्ठा bfa_faa_attr_s *attr,
		bfa_cb_iocfc_t cbfn, व्योम *cbarg)
अणु
	काष्ठा bfi_faa_query_s  faa_attr_req;
	काष्ठा bfa_iocfc_s      *iocfc = &bfa->iocfc;
	bfa_status_t            status;

	status = bfa_faa_validate_request(bfa);
	अगर (status != BFA_STATUS_OK)
		वापस status;

	अगर (iocfc->faa_args.busy == BFA_TRUE)
		वापस BFA_STATUS_DEVBUSY;

	iocfc->faa_args.faa_attr = attr;
	iocfc->faa_args.faa_cb.faa_cbfn = cbfn;
	iocfc->faa_args.faa_cb.faa_cbarg = cbarg;

	iocfc->faa_args.busy = BFA_TRUE;
	स_रखो(&faa_attr_req, 0, माप(काष्ठा bfi_faa_query_s));
	bfi_h2i_set(faa_attr_req.mh, BFI_MC_IOCFC,
		BFI_IOCFC_H2I_FAA_QUERY_REQ, bfa_fn_lpu(bfa));

	bfa_ioc_mbox_send(&bfa->ioc, &faa_attr_req,
		माप(काष्ठा bfi_faa_query_s));

	वापस BFA_STATUS_OK;
पूर्ण

/*
 *	FAA query response
 */
अटल व्योम
bfa_faa_query_reply(काष्ठा bfa_iocfc_s *iocfc,
		bfi_faa_query_rsp_t *rsp)
अणु
	व्योम	*cbarg = iocfc->faa_args.faa_cb.faa_cbarg;

	अगर (iocfc->faa_args.faa_attr) अणु
		iocfc->faa_args.faa_attr->faa = rsp->faa;
		iocfc->faa_args.faa_attr->faa_state = rsp->faa_status;
		iocfc->faa_args.faa_attr->pwwn_source = rsp->addr_source;
	पूर्ण

	WARN_ON(!iocfc->faa_args.faa_cb.faa_cbfn);

	iocfc->faa_args.faa_cb.faa_cbfn(cbarg, BFA_STATUS_OK);
	iocfc->faa_args.busy = BFA_FALSE;
पूर्ण

/*
 * IOC enable request is complete
 */
अटल व्योम
bfa_iocfc_enable_cbfn(व्योम *bfa_arg, क्रमागत bfa_status status)
अणु
	काष्ठा bfa_s	*bfa = bfa_arg;

	अगर (status == BFA_STATUS_OK)
		bfa_fsm_send_event(&bfa->iocfc, IOCFC_E_IOC_ENABLED);
	अन्यथा
		bfa_fsm_send_event(&bfa->iocfc, IOCFC_E_IOC_FAILED);
पूर्ण

/*
 * IOC disable request is complete
 */
अटल व्योम
bfa_iocfc_disable_cbfn(व्योम *bfa_arg)
अणु
	काष्ठा bfa_s	*bfa = bfa_arg;

	bfa->queue_process = BFA_FALSE;
	bfa_fsm_send_event(&bfa->iocfc, IOCFC_E_IOC_DISABLED);
पूर्ण

/*
 * Notअगरy sub-modules of hardware failure.
 */
अटल व्योम
bfa_iocfc_hbfail_cbfn(व्योम *bfa_arg)
अणु
	काष्ठा bfa_s	*bfa = bfa_arg;

	bfa->queue_process = BFA_FALSE;
	bfa_fsm_send_event(&bfa->iocfc, IOCFC_E_IOC_FAILED);
पूर्ण

/*
 * Actions on chip-reset completion.
 */
अटल व्योम
bfa_iocfc_reset_cbfn(व्योम *bfa_arg)
अणु
	काष्ठा bfa_s	*bfa = bfa_arg;

	bfa_iocfc_reset_queues(bfa);
	bfa_isr_enable(bfa);
पूर्ण

/*
 * Query IOC memory requirement inक्रमmation.
 */
व्योम
bfa_iocfc_meminfo(काष्ठा bfa_iocfc_cfg_s *cfg, काष्ठा bfa_meminfo_s *meminfo,
		  काष्ठा bfa_s *bfa)
अणु
	पूर्णांक q, per_reqq_sz, per_rspq_sz;
	काष्ठा bfa_mem_dma_s *ioc_dma = BFA_MEM_IOC_DMA(bfa);
	काष्ठा bfa_mem_dma_s *iocfc_dma = BFA_MEM_IOCFC_DMA(bfa);
	काष्ठा bfa_mem_kva_s *iocfc_kva = BFA_MEM_IOCFC_KVA(bfa);
	u32	dm_len = 0;

	/* dma memory setup क्रम IOC */
	bfa_mem_dma_setup(meminfo, ioc_dma,
		BFA_ROUNDUP(माप(काष्ठा bfi_ioc_attr_s), BFA_DMA_ALIGN_SZ));

	/* dma memory setup क्रम REQ/RSP queues */
	per_reqq_sz = BFA_ROUNDUP((cfg->drvcfg.num_reqq_elems * BFI_LMSG_SZ),
				BFA_DMA_ALIGN_SZ);
	per_rspq_sz = BFA_ROUNDUP((cfg->drvcfg.num_rspq_elems * BFI_LMSG_SZ),
				BFA_DMA_ALIGN_SZ);

	क्रम (q = 0; q < cfg->fwcfg.num_cqs; q++) अणु
		bfa_mem_dma_setup(meminfo, BFA_MEM_REQQ_DMA(bfa, q),
				per_reqq_sz);
		bfa_mem_dma_setup(meminfo, BFA_MEM_RSPQ_DMA(bfa, q),
				per_rspq_sz);
	पूर्ण

	/* IOCFC dma memory - calculate Shaकरोw CI/PI size */
	क्रम (q = 0; q < cfg->fwcfg.num_cqs; q++)
		dm_len += (2 * BFA_CACHELINE_SZ);

	/* IOCFC dma memory - calculate config info / rsp size */
	dm_len += BFA_ROUNDUP(माप(काष्ठा bfi_iocfc_cfg_s), BFA_CACHELINE_SZ);
	dm_len += BFA_ROUNDUP(माप(काष्ठा bfi_iocfc_cfgrsp_s),
			BFA_CACHELINE_SZ);

	/* dma memory setup क्रम IOCFC */
	bfa_mem_dma_setup(meminfo, iocfc_dma, dm_len);

	/* kva memory setup क्रम IOCFC */
	bfa_mem_kva_setup(meminfo, iocfc_kva, BFA_DBG_FWTRC_LEN);
पूर्ण

/*
 * Query IOC memory requirement inक्रमmation.
 */
व्योम
bfa_iocfc_attach(काष्ठा bfa_s *bfa, व्योम *bfad, काष्ठा bfa_iocfc_cfg_s *cfg,
		 काष्ठा bfa_pcidev_s *pcidev)
अणु
	पूर्णांक		i;
	काष्ठा bfa_ioc_s *ioc = &bfa->ioc;

	bfa_iocfc_cbfn.enable_cbfn = bfa_iocfc_enable_cbfn;
	bfa_iocfc_cbfn.disable_cbfn = bfa_iocfc_disable_cbfn;
	bfa_iocfc_cbfn.hbfail_cbfn = bfa_iocfc_hbfail_cbfn;
	bfa_iocfc_cbfn.reset_cbfn = bfa_iocfc_reset_cbfn;

	ioc->trcmod = bfa->trcmod;
	bfa_ioc_attach(&bfa->ioc, bfa, &bfa_iocfc_cbfn, &bfa->समयr_mod);

	bfa_ioc_pci_init(&bfa->ioc, pcidev, BFI_PCIFN_CLASS_FC);
	bfa_ioc_mbox_रेजिस्टर(&bfa->ioc, bfa_mbox_isrs);

	bfa_iocfc_init_mem(bfa, bfad, cfg, pcidev);
	bfa_iocfc_mem_claim(bfa, cfg);
	INIT_LIST_HEAD(&bfa->समयr_mod.समयr_q);

	INIT_LIST_HEAD(&bfa->comp_q);
	क्रम (i = 0; i < BFI_IOC_MAX_CQS; i++)
		INIT_LIST_HEAD(&bfa->reqq_रुकोq[i]);

	bfa->iocfc.cb_reqd = BFA_FALSE;
	bfa->iocfc.op_status = BFA_STATUS_OK;
	bfa->iocfc.submod_enabled = BFA_FALSE;

	bfa_fsm_set_state(&bfa->iocfc, bfa_iocfc_sm_stopped);
पूर्ण

/*
 * Query IOC memory requirement inक्रमmation.
 */
व्योम
bfa_iocfc_init(काष्ठा bfa_s *bfa)
अणु
	bfa_fsm_send_event(&bfa->iocfc, IOCFC_E_INIT);
पूर्ण

/*
 * IOC start called from bfa_start(). Called to start IOC operations
 * at driver instantiation क्रम this instance.
 */
व्योम
bfa_iocfc_start(काष्ठा bfa_s *bfa)
अणु
	bfa_fsm_send_event(&bfa->iocfc, IOCFC_E_START);
पूर्ण

/*
 * IOC stop called from bfa_stop(). Called only when driver is unloaded
 * क्रम this instance.
 */
व्योम
bfa_iocfc_stop(काष्ठा bfa_s *bfa)
अणु
	bfa_fsm_send_event(&bfa->iocfc, IOCFC_E_STOP);
पूर्ण

व्योम
bfa_iocfc_isr(व्योम *bfaarg, काष्ठा bfi_mbmsg_s *m)
अणु
	काष्ठा bfa_s		*bfa = bfaarg;
	काष्ठा bfa_iocfc_s	*iocfc = &bfa->iocfc;
	जोड़ bfi_iocfc_i2h_msg_u	*msg;

	msg = (जोड़ bfi_iocfc_i2h_msg_u *) m;
	bfa_trc(bfa, msg->mh.msg_id);

	चयन (msg->mh.msg_id) अणु
	हाल BFI_IOCFC_I2H_CFG_REPLY:
		bfa_iocfc_cfgrsp(bfa);
		अवरोध;
	हाल BFI_IOCFC_I2H_UPDATEQ_RSP:
		iocfc->updateq_cbfn(iocfc->updateq_cbarg, BFA_STATUS_OK);
		अवरोध;
	हाल BFI_IOCFC_I2H_ADDR_MSG:
		bfa_iocfc_process_faa_addr(bfa,
				(काष्ठा bfi_faa_addr_msg_s *)msg);
		अवरोध;
	हाल BFI_IOCFC_I2H_FAA_QUERY_RSP:
		bfa_faa_query_reply(iocfc, (bfi_faa_query_rsp_t *)msg);
		अवरोध;
	शेष:
		WARN_ON(1);
	पूर्ण
पूर्ण

व्योम
bfa_iocfc_get_attr(काष्ठा bfa_s *bfa, काष्ठा bfa_iocfc_attr_s *attr)
अणु
	काष्ठा bfa_iocfc_s	*iocfc = &bfa->iocfc;

	attr->पूर्णांकr_attr.coalesce = iocfc->cfginfo->पूर्णांकr_attr.coalesce;

	attr->पूर्णांकr_attr.delay = iocfc->cfginfo->पूर्णांकr_attr.delay ?
				be16_to_cpu(iocfc->cfginfo->पूर्णांकr_attr.delay) :
				be16_to_cpu(iocfc->cfgrsp->पूर्णांकr_attr.delay);

	attr->पूर्णांकr_attr.latency = iocfc->cfginfo->पूर्णांकr_attr.latency ?
			be16_to_cpu(iocfc->cfginfo->पूर्णांकr_attr.latency) :
			be16_to_cpu(iocfc->cfgrsp->पूर्णांकr_attr.latency);

	attr->config	= iocfc->cfg;
पूर्ण

bfa_status_t
bfa_iocfc_israttr_set(काष्ठा bfa_s *bfa, काष्ठा bfa_iocfc_पूर्णांकr_attr_s *attr)
अणु
	काष्ठा bfa_iocfc_s		*iocfc = &bfa->iocfc;
	काष्ठा bfi_iocfc_set_पूर्णांकr_req_s *m;

	iocfc->cfginfo->पूर्णांकr_attr.coalesce = attr->coalesce;
	iocfc->cfginfo->पूर्णांकr_attr.delay = cpu_to_be16(attr->delay);
	iocfc->cfginfo->पूर्णांकr_attr.latency = cpu_to_be16(attr->latency);

	अगर (!bfa_iocfc_is_operational(bfa))
		वापस BFA_STATUS_OK;

	m = bfa_reqq_next(bfa, BFA_REQQ_IOC);
	अगर (!m)
		वापस BFA_STATUS_DEVBUSY;

	bfi_h2i_set(m->mh, BFI_MC_IOCFC, BFI_IOCFC_H2I_SET_INTR_REQ,
		    bfa_fn_lpu(bfa));
	m->coalesce = iocfc->cfginfo->पूर्णांकr_attr.coalesce;
	m->delay    = iocfc->cfginfo->पूर्णांकr_attr.delay;
	m->latency  = iocfc->cfginfo->पूर्णांकr_attr.latency;

	bfa_trc(bfa, attr->delay);
	bfa_trc(bfa, attr->latency);

	bfa_reqq_produce(bfa, BFA_REQQ_IOC, m->mh);
	वापस BFA_STATUS_OK;
पूर्ण

व्योम
bfa_iocfc_set_snsbase(काष्ठा bfa_s *bfa, पूर्णांक seg_no, u64 snsbase_pa)
अणु
	काष्ठा bfa_iocfc_s	*iocfc = &bfa->iocfc;

	iocfc->cfginfo->sense_buf_len = (BFI_IOIM_SNSLEN - 1);
	bfa_dma_be_addr_set(iocfc->cfginfo->ioim_snsbase[seg_no], snsbase_pa);
पूर्ण
/*
 * Enable IOC after it is disabled.
 */
व्योम
bfa_iocfc_enable(काष्ठा bfa_s *bfa)
अणु
	bfa_plog_str(bfa->plog, BFA_PL_MID_HAL, BFA_PL_EID_MISC, 0,
		     "IOC Enable");
	bfa->iocfc.cb_reqd = BFA_TRUE;
	bfa_fsm_send_event(&bfa->iocfc, IOCFC_E_ENABLE);
पूर्ण

व्योम
bfa_iocfc_disable(काष्ठा bfa_s *bfa)
अणु
	bfa_plog_str(bfa->plog, BFA_PL_MID_HAL, BFA_PL_EID_MISC, 0,
		     "IOC Disable");

	bfa_fsm_send_event(&bfa->iocfc, IOCFC_E_DISABLE);
पूर्ण

bfa_boolean_t
bfa_iocfc_is_operational(काष्ठा bfa_s *bfa)
अणु
	वापस bfa_ioc_is_operational(&bfa->ioc) &&
		bfa_fsm_cmp_state(&bfa->iocfc, bfa_iocfc_sm_operational);
पूर्ण

/*
 * Return boot target port wwns -- पढ़ो from boot inक्रमmation in flash.
 */
व्योम
bfa_iocfc_get_bootwwns(काष्ठा bfa_s *bfa, u8 *nwwns, wwn_t *wwns)
अणु
	काष्ठा bfa_iocfc_s *iocfc = &bfa->iocfc;
	काष्ठा bfi_iocfc_cfgrsp_s *cfgrsp = iocfc->cfgrsp;
	पूर्णांक i;

	अगर (cfgrsp->pbc_cfg.boot_enabled && cfgrsp->pbc_cfg.nbluns) अणु
		bfa_trc(bfa, cfgrsp->pbc_cfg.nbluns);
		*nwwns = cfgrsp->pbc_cfg.nbluns;
		क्रम (i = 0; i < cfgrsp->pbc_cfg.nbluns; i++)
			wwns[i] = cfgrsp->pbc_cfg.blun[i].tgt_pwwn;

		वापस;
	पूर्ण

	*nwwns = cfgrsp->bootwwns.nwwns;
	स_नकल(wwns, cfgrsp->bootwwns.wwn, माप(cfgrsp->bootwwns.wwn));
पूर्ण

पूर्णांक
bfa_iocfc_get_pbc_vports(काष्ठा bfa_s *bfa, काष्ठा bfi_pbc_vport_s *pbc_vport)
अणु
	काष्ठा bfa_iocfc_s *iocfc = &bfa->iocfc;
	काष्ठा bfi_iocfc_cfgrsp_s *cfgrsp = iocfc->cfgrsp;

	स_नकल(pbc_vport, cfgrsp->pbc_cfg.vport, माप(cfgrsp->pbc_cfg.vport));
	वापस cfgrsp->pbc_cfg.nvports;
पूर्ण


/*
 * Use this function query the memory requirement of the BFA library.
 * This function needs to be called beक्रमe bfa_attach() to get the
 * memory required of the BFA layer क्रम a given driver configuration.
 *
 * This call will fail, अगर the cap is out of range compared to pre-defined
 * values within the BFA library
 *
 * @param[in] cfg -	poपूर्णांकer to bfa_ioc_cfg_t. Driver layer should indicate
 *			its configuration in this काष्ठाure.
 *			The शेष values क्रम काष्ठा bfa_iocfc_cfg_s can be
 *			fetched using bfa_cfg_get_शेष() API.
 *
 *			If cap's boundary check fails, the library will use
 *			the शेष bfa_cap_t values (and log a warning msg).
 *
 * @param[out] meminfo - poपूर्णांकer to bfa_meminfo_t. This content
 *			indicates the memory type (see bfa_mem_type_t) and
 *			amount of memory required.
 *
 *			Driver should allocate the memory, populate the
 *			starting address क्रम each block and provide the same
 *			काष्ठाure as input parameter to bfa_attach() call.
 *
 * @param[in] bfa -	poपूर्णांकer to the bfa काष्ठाure, used जबतक fetching the
 *			dma, kva memory inक्रमmation of the bfa sub-modules.
 *
 * @वापस व्योम
 *
 * Special Considerations: @note
 */
व्योम
bfa_cfg_get_meminfo(काष्ठा bfa_iocfc_cfg_s *cfg, काष्ठा bfa_meminfo_s *meminfo,
		काष्ठा bfa_s *bfa)
अणु
	काष्ठा bfa_mem_dma_s *port_dma = BFA_MEM_PORT_DMA(bfa);
	काष्ठा bfa_mem_dma_s *ablk_dma = BFA_MEM_ABLK_DMA(bfa);
	काष्ठा bfa_mem_dma_s *cee_dma = BFA_MEM_CEE_DMA(bfa);
	काष्ठा bfa_mem_dma_s *sfp_dma = BFA_MEM_SFP_DMA(bfa);
	काष्ठा bfa_mem_dma_s *flash_dma = BFA_MEM_FLASH_DMA(bfa);
	काष्ठा bfa_mem_dma_s *diag_dma = BFA_MEM_DIAG_DMA(bfa);
	काष्ठा bfa_mem_dma_s *phy_dma = BFA_MEM_PHY_DMA(bfa);
	काष्ठा bfa_mem_dma_s *fru_dma = BFA_MEM_FRU_DMA(bfa);

	WARN_ON((cfg == शून्य) || (meminfo == शून्य));

	स_रखो((व्योम *)meminfo, 0, माप(काष्ठा bfa_meminfo_s));

	/* Initialize the DMA & KVA meminfo queues */
	INIT_LIST_HEAD(&meminfo->dma_info.qe);
	INIT_LIST_HEAD(&meminfo->kva_info.qe);

	bfa_iocfc_meminfo(cfg, meminfo, bfa);
	bfa_sgpg_meminfo(cfg, meminfo, bfa);
	bfa_fcport_meminfo(cfg, meminfo, bfa);
	bfa_fcxp_meminfo(cfg, meminfo, bfa);
	bfa_lps_meminfo(cfg, meminfo, bfa);
	bfa_uf_meminfo(cfg, meminfo, bfa);
	bfa_rport_meminfo(cfg, meminfo, bfa);
	bfa_fcp_meminfo(cfg, meminfo, bfa);
	bfa_dconf_meminfo(cfg, meminfo, bfa);

	/* dma info setup */
	bfa_mem_dma_setup(meminfo, port_dma, bfa_port_meminfo());
	bfa_mem_dma_setup(meminfo, ablk_dma, bfa_ablk_meminfo());
	bfa_mem_dma_setup(meminfo, cee_dma, bfa_cee_meminfo());
	bfa_mem_dma_setup(meminfo, sfp_dma, bfa_sfp_meminfo());
	bfa_mem_dma_setup(meminfo, flash_dma,
			  bfa_flash_meminfo(cfg->drvcfg.min_cfg));
	bfa_mem_dma_setup(meminfo, diag_dma, bfa_diag_meminfo());
	bfa_mem_dma_setup(meminfo, phy_dma,
			  bfa_phy_meminfo(cfg->drvcfg.min_cfg));
	bfa_mem_dma_setup(meminfo, fru_dma,
			  bfa_fru_meminfo(cfg->drvcfg.min_cfg));
पूर्ण

/*
 * Use this function to करो attach the driver instance with the BFA
 * library. This function will not trigger any HW initialization
 * process (which will be करोne in bfa_init() call)
 *
 * This call will fail, अगर the cap is out of range compared to
 * pre-defined values within the BFA library
 *
 * @param[out]	bfa	Poपूर्णांकer to bfa_t.
 * @param[in]	bfad	Opaque handle back to the driver's IOC काष्ठाure
 * @param[in]	cfg	Poपूर्णांकer to bfa_ioc_cfg_t. Should be same काष्ठाure
 *			that was used in bfa_cfg_get_meminfo().
 * @param[in]	meminfo	Poपूर्णांकer to bfa_meminfo_t. The driver should
 *			use the bfa_cfg_get_meminfo() call to
 *			find the memory blocks required, allocate the
 *			required memory and provide the starting addresses.
 * @param[in]	pcidev	poपूर्णांकer to काष्ठा bfa_pcidev_s
 *
 * @वापस
 * व्योम
 *
 * Special Considerations:
 *
 * @note
 *
 */
व्योम
bfa_attach(काष्ठा bfa_s *bfa, व्योम *bfad, काष्ठा bfa_iocfc_cfg_s *cfg,
	       काष्ठा bfa_meminfo_s *meminfo, काष्ठा bfa_pcidev_s *pcidev)
अणु
	काष्ठा bfa_mem_dma_s *dma_info, *dma_elem;
	काष्ठा bfa_mem_kva_s *kva_info, *kva_elem;
	काष्ठा list_head *dm_qe, *km_qe;

	bfa->fcs = BFA_FALSE;

	WARN_ON((cfg == शून्य) || (meminfo == शून्य));

	/* Initialize memory poपूर्णांकers क्रम iterative allocation */
	dma_info = &meminfo->dma_info;
	dma_info->kva_curp = dma_info->kva;
	dma_info->dma_curp = dma_info->dma;

	kva_info = &meminfo->kva_info;
	kva_info->kva_curp = kva_info->kva;

	list_क्रम_each(dm_qe, &dma_info->qe) अणु
		dma_elem = (काष्ठा bfa_mem_dma_s *) dm_qe;
		dma_elem->kva_curp = dma_elem->kva;
		dma_elem->dma_curp = dma_elem->dma;
	पूर्ण

	list_क्रम_each(km_qe, &kva_info->qe) अणु
		kva_elem = (काष्ठा bfa_mem_kva_s *) km_qe;
		kva_elem->kva_curp = kva_elem->kva;
	पूर्ण

	bfa_iocfc_attach(bfa, bfad, cfg, pcidev);
	bfa_fcdiag_attach(bfa, bfad, cfg, pcidev);
	bfa_sgpg_attach(bfa, bfad, cfg, pcidev);
	bfa_fcport_attach(bfa, bfad, cfg, pcidev);
	bfa_fcxp_attach(bfa, bfad, cfg, pcidev);
	bfa_lps_attach(bfa, bfad, cfg, pcidev);
	bfa_uf_attach(bfa, bfad, cfg, pcidev);
	bfa_rport_attach(bfa, bfad, cfg, pcidev);
	bfa_fcp_attach(bfa, bfad, cfg, pcidev);
	bfa_dconf_attach(bfa, bfad, cfg);
	bfa_com_port_attach(bfa);
	bfa_com_ablk_attach(bfa);
	bfa_com_cee_attach(bfa);
	bfa_com_sfp_attach(bfa);
	bfa_com_flash_attach(bfa, cfg->drvcfg.min_cfg);
	bfa_com_diag_attach(bfa);
	bfa_com_phy_attach(bfa, cfg->drvcfg.min_cfg);
	bfa_com_fru_attach(bfa, cfg->drvcfg.min_cfg);
पूर्ण

/*
 * Use this function to delete a BFA IOC. IOC should be stopped (by
 * calling bfa_stop()) beक्रमe this function call.
 *
 * @param[in] bfa - poपूर्णांकer to bfa_t.
 *
 * @वापस
 * व्योम
 *
 * Special Considerations:
 *
 * @note
 */
व्योम
bfa_detach(काष्ठा bfa_s *bfa)
अणु
	bfa_ioc_detach(&bfa->ioc);
पूर्ण

व्योम
bfa_comp_deq(काष्ठा bfa_s *bfa, काष्ठा list_head *comp_q)
अणु
	INIT_LIST_HEAD(comp_q);
	list_splice_tail_init(&bfa->comp_q, comp_q);
पूर्ण

व्योम
bfa_comp_process(काष्ठा bfa_s *bfa, काष्ठा list_head *comp_q)
अणु
	काष्ठा list_head		*qe;
	काष्ठा list_head		*qen;
	काष्ठा bfa_cb_qe_s	*hcb_qe;
	bfa_cb_cbfn_status_t	cbfn;

	list_क्रम_each_safe(qe, qen, comp_q) अणु
		hcb_qe = (काष्ठा bfa_cb_qe_s *) qe;
		अगर (hcb_qe->pre_rmv) अणु
			/* qe is invalid after वापस, dequeue beक्रमe cbfn() */
			list_del(qe);
			cbfn = (bfa_cb_cbfn_status_t)(hcb_qe->cbfn);
			cbfn(hcb_qe->cbarg, hcb_qe->fw_status);
		पूर्ण अन्यथा
			hcb_qe->cbfn(hcb_qe->cbarg, BFA_TRUE);
	पूर्ण
पूर्ण

व्योम
bfa_comp_मुक्त(काष्ठा bfa_s *bfa, काष्ठा list_head *comp_q)
अणु
	काष्ठा list_head		*qe;
	काष्ठा bfa_cb_qe_s	*hcb_qe;

	जबतक (!list_empty(comp_q)) अणु
		bfa_q_deq(comp_q, &qe);
		hcb_qe = (काष्ठा bfa_cb_qe_s *) qe;
		WARN_ON(hcb_qe->pre_rmv);
		hcb_qe->cbfn(hcb_qe->cbarg, BFA_FALSE);
	पूर्ण
पूर्ण

/*
 * Return the list of PCI venकरोr/device id lists supported by this
 * BFA instance.
 */
व्योम
bfa_get_pciids(काष्ठा bfa_pciid_s **pciids, पूर्णांक *npciids)
अणु
	अटल काष्ठा bfa_pciid_s __pciids[] = अणु
		अणुBFA_PCI_VENDOR_ID_BROCADE, BFA_PCI_DEVICE_ID_FC_8G2Pपूर्ण,
		अणुBFA_PCI_VENDOR_ID_BROCADE, BFA_PCI_DEVICE_ID_FC_8G1Pपूर्ण,
		अणुBFA_PCI_VENDOR_ID_BROCADE, BFA_PCI_DEVICE_ID_CTपूर्ण,
		अणुBFA_PCI_VENDOR_ID_BROCADE, BFA_PCI_DEVICE_ID_CT_FCपूर्ण,
	पूर्ण;

	*npciids = ARRAY_SIZE(__pciids);
	*pciids = __pciids;
पूर्ण

/*
 * Use this function query the शेष काष्ठा bfa_iocfc_cfg_s value (compiled
 * पूर्णांकo BFA layer). The OS driver can then turn back and overग_लिखो entries that
 * have been configured by the user.
 *
 * @param[in] cfg - poपूर्णांकer to bfa_ioc_cfg_t
 *
 * @वापस
 *	व्योम
 *
 * Special Considerations:
 * note
 */
व्योम
bfa_cfg_get_शेष(काष्ठा bfa_iocfc_cfg_s *cfg)
अणु
	cfg->fwcfg.num_fabrics = DEF_CFG_NUM_FABRICS;
	cfg->fwcfg.num_lports = DEF_CFG_NUM_LPORTS;
	cfg->fwcfg.num_rports = DEF_CFG_NUM_RPORTS;
	cfg->fwcfg.num_ioim_reqs = DEF_CFG_NUM_IOIM_REQS;
	cfg->fwcfg.num_tskim_reqs = DEF_CFG_NUM_TSKIM_REQS;
	cfg->fwcfg.num_fcxp_reqs = DEF_CFG_NUM_FCXP_REQS;
	cfg->fwcfg.num_uf_bufs = DEF_CFG_NUM_UF_BUFS;
	cfg->fwcfg.num_cqs = DEF_CFG_NUM_CQS;
	cfg->fwcfg.num_fwtio_reqs = 0;

	cfg->drvcfg.num_reqq_elems = DEF_CFG_NUM_REQQ_ELEMS;
	cfg->drvcfg.num_rspq_elems = DEF_CFG_NUM_RSPQ_ELEMS;
	cfg->drvcfg.num_sgpgs = DEF_CFG_NUM_SGPGS;
	cfg->drvcfg.num_sboot_tgts = DEF_CFG_NUM_SBOOT_TGTS;
	cfg->drvcfg.num_sboot_luns = DEF_CFG_NUM_SBOOT_LUNS;
	cfg->drvcfg.path_tov = BFA_FCPIM_PATHTOV_DEF;
	cfg->drvcfg.ioc_recover = BFA_FALSE;
	cfg->drvcfg.delay_comp = BFA_FALSE;

पूर्ण

व्योम
bfa_cfg_get_min(काष्ठा bfa_iocfc_cfg_s *cfg)
अणु
	bfa_cfg_get_शेष(cfg);
	cfg->fwcfg.num_ioim_reqs   = BFA_IOIM_MIN;
	cfg->fwcfg.num_tskim_reqs  = BFA_TSKIM_MIN;
	cfg->fwcfg.num_fcxp_reqs   = BFA_FCXP_MIN;
	cfg->fwcfg.num_uf_bufs     = BFA_UF_MIN;
	cfg->fwcfg.num_rports      = BFA_RPORT_MIN;
	cfg->fwcfg.num_fwtio_reqs = 0;

	cfg->drvcfg.num_sgpgs      = BFA_SGPG_MIN;
	cfg->drvcfg.num_reqq_elems = BFA_REQQ_NELEMS_MIN;
	cfg->drvcfg.num_rspq_elems = BFA_RSPQ_NELEMS_MIN;
	cfg->drvcfg.min_cfg	   = BFA_TRUE;
पूर्ण
