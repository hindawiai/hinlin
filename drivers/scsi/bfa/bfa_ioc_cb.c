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
#समावेश "bfa_ioc.h"
#समावेश "bfi_reg.h"
#समावेश "bfa_defs.h"

BFA_TRC_खाता(CNA, IOC_CB);

#घोषणा bfa_ioc_cb_join_pos(__ioc) ((u32) (1 << BFA_IOC_CB_JOIN_SH))

/*
 * क्रमward declarations
 */
अटल bfa_boolean_t bfa_ioc_cb_firmware_lock(काष्ठा bfa_ioc_s *ioc);
अटल व्योम bfa_ioc_cb_firmware_unlock(काष्ठा bfa_ioc_s *ioc);
अटल व्योम bfa_ioc_cb_reg_init(काष्ठा bfa_ioc_s *ioc);
अटल व्योम bfa_ioc_cb_map_port(काष्ठा bfa_ioc_s *ioc);
अटल व्योम bfa_ioc_cb_isr_mode_set(काष्ठा bfa_ioc_s *ioc, bfa_boolean_t msix);
अटल व्योम bfa_ioc_cb_notअगरy_fail(काष्ठा bfa_ioc_s *ioc);
अटल व्योम bfa_ioc_cb_ownership_reset(काष्ठा bfa_ioc_s *ioc);
अटल bfa_boolean_t bfa_ioc_cb_sync_start(काष्ठा bfa_ioc_s *ioc);
अटल व्योम bfa_ioc_cb_sync_join(काष्ठा bfa_ioc_s *ioc);
अटल व्योम bfa_ioc_cb_sync_leave(काष्ठा bfa_ioc_s *ioc);
अटल व्योम bfa_ioc_cb_sync_ack(काष्ठा bfa_ioc_s *ioc);
अटल bfa_boolean_t bfa_ioc_cb_sync_complete(काष्ठा bfa_ioc_s *ioc);
अटल व्योम bfa_ioc_cb_set_cur_ioc_fwstate(
			काष्ठा bfa_ioc_s *ioc, क्रमागत bfi_ioc_state fwstate);
अटल क्रमागत bfi_ioc_state bfa_ioc_cb_get_cur_ioc_fwstate(काष्ठा bfa_ioc_s *ioc);
अटल व्योम bfa_ioc_cb_set_alt_ioc_fwstate(
			काष्ठा bfa_ioc_s *ioc, क्रमागत bfi_ioc_state fwstate);
अटल क्रमागत bfi_ioc_state bfa_ioc_cb_get_alt_ioc_fwstate(काष्ठा bfa_ioc_s *ioc);

अटल काष्ठा bfa_ioc_hwअगर_s hwअगर_cb;

/*
 * Called from bfa_ioc_attach() to map asic specअगरic calls.
 */
व्योम
bfa_ioc_set_cb_hwअगर(काष्ठा bfa_ioc_s *ioc)
अणु
	hwअगर_cb.ioc_pll_init = bfa_ioc_cb_pll_init;
	hwअगर_cb.ioc_firmware_lock = bfa_ioc_cb_firmware_lock;
	hwअगर_cb.ioc_firmware_unlock = bfa_ioc_cb_firmware_unlock;
	hwअगर_cb.ioc_reg_init = bfa_ioc_cb_reg_init;
	hwअगर_cb.ioc_map_port = bfa_ioc_cb_map_port;
	hwअगर_cb.ioc_isr_mode_set = bfa_ioc_cb_isr_mode_set;
	hwअगर_cb.ioc_notअगरy_fail = bfa_ioc_cb_notअगरy_fail;
	hwअगर_cb.ioc_ownership_reset = bfa_ioc_cb_ownership_reset;
	hwअगर_cb.ioc_sync_start = bfa_ioc_cb_sync_start;
	hwअगर_cb.ioc_sync_join = bfa_ioc_cb_sync_join;
	hwअगर_cb.ioc_sync_leave = bfa_ioc_cb_sync_leave;
	hwअगर_cb.ioc_sync_ack = bfa_ioc_cb_sync_ack;
	hwअगर_cb.ioc_sync_complete = bfa_ioc_cb_sync_complete;
	hwअगर_cb.ioc_set_fwstate = bfa_ioc_cb_set_cur_ioc_fwstate;
	hwअगर_cb.ioc_get_fwstate = bfa_ioc_cb_get_cur_ioc_fwstate;
	hwअगर_cb.ioc_set_alt_fwstate = bfa_ioc_cb_set_alt_ioc_fwstate;
	hwअगर_cb.ioc_get_alt_fwstate = bfa_ioc_cb_get_alt_ioc_fwstate;

	ioc->ioc_hwअगर = &hwअगर_cb;
पूर्ण

/*
 * Return true अगर firmware of current driver matches the running firmware.
 */
अटल bfa_boolean_t
bfa_ioc_cb_firmware_lock(काष्ठा bfa_ioc_s *ioc)
अणु
	क्रमागत bfi_ioc_state alt_fwstate, cur_fwstate;
	काष्ठा bfi_ioc_image_hdr_s fwhdr;

	cur_fwstate = bfa_ioc_cb_get_cur_ioc_fwstate(ioc);
	bfa_trc(ioc, cur_fwstate);
	alt_fwstate = bfa_ioc_cb_get_alt_ioc_fwstate(ioc);
	bfa_trc(ioc, alt_fwstate);

	/*
	 * Uninit implies this is the only driver as of now.
	 */
	अगर (cur_fwstate == BFI_IOC_UNINIT)
		वापस BFA_TRUE;
	/*
	 * Check अगर another driver with a dअगरferent firmware is active
	 */
	bfa_ioc_fwver_get(ioc, &fwhdr);
	अगर (!bfa_ioc_fwver_cmp(ioc, &fwhdr) &&
		alt_fwstate != BFI_IOC_DISABLED) अणु
		bfa_trc(ioc, alt_fwstate);
		वापस BFA_FALSE;
	पूर्ण

	वापस BFA_TRUE;
पूर्ण

अटल व्योम
bfa_ioc_cb_firmware_unlock(काष्ठा bfa_ioc_s *ioc)
अणु
पूर्ण

/*
 * Notअगरy other functions on HB failure.
 */
अटल व्योम
bfa_ioc_cb_notअगरy_fail(काष्ठा bfa_ioc_s *ioc)
अणु
	ग_लिखोl(~0U, ioc->ioc_regs.err_set);
	पढ़ोl(ioc->ioc_regs.err_set);
पूर्ण

/*
 * Host to LPU mailbox message addresses
 */
अटल काष्ठा अणु u32 hfn_mbox, lpu_mbox, hfn_pgn; पूर्ण iocreg_fnreg[] = अणु
	अणु HOSTFN0_LPU_MBOX0_0, LPU_HOSTFN0_MBOX0_0, HOST_PAGE_NUM_FN0 पूर्ण,
	अणु HOSTFN1_LPU_MBOX0_8, LPU_HOSTFN1_MBOX0_8, HOST_PAGE_NUM_FN1 पूर्ण
पूर्ण;

/*
 * Host <-> LPU mailbox command/status रेजिस्टरs
 */
अटल काष्ठा अणु u32 hfn, lpu; पूर्ण iocreg_mbcmd[] = अणु

	अणु HOSTFN0_LPU0_CMD_STAT, LPU0_HOSTFN0_CMD_STAT पूर्ण,
	अणु HOSTFN1_LPU1_CMD_STAT, LPU1_HOSTFN1_CMD_STAT पूर्ण
पूर्ण;

अटल व्योम
bfa_ioc_cb_reg_init(काष्ठा bfa_ioc_s *ioc)
अणु
	व्योम __iomem *rb;
	पूर्णांक		pcअगरn = bfa_ioc_pcअगरn(ioc);

	rb = bfa_ioc_bar0(ioc);

	ioc->ioc_regs.hfn_mbox = rb + iocreg_fnreg[pcअगरn].hfn_mbox;
	ioc->ioc_regs.lpu_mbox = rb + iocreg_fnreg[pcअगरn].lpu_mbox;
	ioc->ioc_regs.host_page_num_fn = rb + iocreg_fnreg[pcअगरn].hfn_pgn;

	अगर (ioc->port_id == 0) अणु
		ioc->ioc_regs.heartbeat = rb + BFA_IOC0_HBEAT_REG;
		ioc->ioc_regs.ioc_fwstate = rb + BFA_IOC0_STATE_REG;
		ioc->ioc_regs.alt_ioc_fwstate = rb + BFA_IOC1_STATE_REG;
	पूर्ण अन्यथा अणु
		ioc->ioc_regs.heartbeat = (rb + BFA_IOC1_HBEAT_REG);
		ioc->ioc_regs.ioc_fwstate = (rb + BFA_IOC1_STATE_REG);
		ioc->ioc_regs.alt_ioc_fwstate = (rb + BFA_IOC0_STATE_REG);
	पूर्ण

	/*
	 * Host <-> LPU mailbox command/status रेजिस्टरs
	 */
	ioc->ioc_regs.hfn_mbox_cmd = rb + iocreg_mbcmd[pcअगरn].hfn;
	ioc->ioc_regs.lpu_mbox_cmd = rb + iocreg_mbcmd[pcअगरn].lpu;

	/*
	 * PSS control रेजिस्टरs
	 */
	ioc->ioc_regs.pss_ctl_reg = (rb + PSS_CTL_REG);
	ioc->ioc_regs.pss_err_status_reg = (rb + PSS_ERR_STATUS_REG);
	ioc->ioc_regs.app_pll_fast_ctl_reg = (rb + APP_PLL_LCLK_CTL_REG);
	ioc->ioc_regs.app_pll_slow_ctl_reg = (rb + APP_PLL_SCLK_CTL_REG);

	/*
	 * IOC semaphore रेजिस्टरs and serialization
	 */
	ioc->ioc_regs.ioc_sem_reg = (rb + HOST_SEM0_REG);
	ioc->ioc_regs.ioc_init_sem_reg = (rb + HOST_SEM2_REG);

	/*
	 * sram memory access
	 */
	ioc->ioc_regs.smem_page_start = (rb + PSS_SMEM_PAGE_START);
	ioc->ioc_regs.smem_pg0 = BFI_IOC_SMEM_PG0_CB;

	/*
	 * err set reg : क्रम notअगरication of hb failure
	 */
	ioc->ioc_regs.err_set = (rb + ERR_SET_REG);
पूर्ण

/*
 * Initialize IOC to port mapping.
 */

अटल व्योम
bfa_ioc_cb_map_port(काष्ठा bfa_ioc_s *ioc)
अणु
	/*
	 * For crossbow, port id is same as pci function.
	 */
	ioc->port_id = bfa_ioc_pcअगरn(ioc);

	bfa_trc(ioc, ioc->port_id);
पूर्ण

/*
 * Set पूर्णांकerrupt mode क्रम a function: INTX or MSIX
 */
अटल व्योम
bfa_ioc_cb_isr_mode_set(काष्ठा bfa_ioc_s *ioc, bfa_boolean_t msix)
अणु
पूर्ण

/*
 * Synchronized IOC failure processing routines
 */
अटल bfa_boolean_t
bfa_ioc_cb_sync_start(काष्ठा bfa_ioc_s *ioc)
अणु
	u32 ioc_fwstate = पढ़ोl(ioc->ioc_regs.ioc_fwstate);

	/**
	 * Driver load समय.  If the join bit is set,
	 * it is due to an unclean निकास by the driver क्रम this
	 * PCI fn in the previous incarnation. Whoever comes here first
	 * should clean it up, no matter which PCI fn.
	 */
	अगर (ioc_fwstate & BFA_IOC_CB_JOIN_MASK) अणु
		ग_लिखोl(BFI_IOC_UNINIT, ioc->ioc_regs.ioc_fwstate);
		ग_लिखोl(BFI_IOC_UNINIT, ioc->ioc_regs.alt_ioc_fwstate);
		वापस BFA_TRUE;
	पूर्ण

	वापस bfa_ioc_cb_sync_complete(ioc);
पूर्ण

/*
 * Cleanup hw semaphore and usecnt रेजिस्टरs
 */
अटल व्योम
bfa_ioc_cb_ownership_reset(काष्ठा bfa_ioc_s *ioc)
अणु

	/*
	 * Read the hw sem reg to make sure that it is locked
	 * beक्रमe we clear it. If it is not locked, writing 1
	 * will lock it instead of clearing it.
	 */
	पढ़ोl(ioc->ioc_regs.ioc_sem_reg);
	ग_लिखोl(1, ioc->ioc_regs.ioc_sem_reg);
पूर्ण

/*
 * Synchronized IOC failure processing routines
 */
अटल व्योम
bfa_ioc_cb_sync_join(काष्ठा bfa_ioc_s *ioc)
अणु
	u32 r32 = पढ़ोl(ioc->ioc_regs.ioc_fwstate);
	u32 join_pos = bfa_ioc_cb_join_pos(ioc);

	ग_लिखोl((r32 | join_pos), ioc->ioc_regs.ioc_fwstate);
पूर्ण

अटल व्योम
bfa_ioc_cb_sync_leave(काष्ठा bfa_ioc_s *ioc)
अणु
	u32 r32 = पढ़ोl(ioc->ioc_regs.ioc_fwstate);
	u32 join_pos = bfa_ioc_cb_join_pos(ioc);

	ग_लिखोl((r32 & ~join_pos), ioc->ioc_regs.ioc_fwstate);
पूर्ण

अटल व्योम
bfa_ioc_cb_set_cur_ioc_fwstate(काष्ठा bfa_ioc_s *ioc,
			क्रमागत bfi_ioc_state fwstate)
अणु
	u32 r32 = पढ़ोl(ioc->ioc_regs.ioc_fwstate);

	ग_लिखोl((fwstate | (r32 & BFA_IOC_CB_JOIN_MASK)),
				ioc->ioc_regs.ioc_fwstate);
पूर्ण

अटल क्रमागत bfi_ioc_state
bfa_ioc_cb_get_cur_ioc_fwstate(काष्ठा bfa_ioc_s *ioc)
अणु
	वापस (क्रमागत bfi_ioc_state)(पढ़ोl(ioc->ioc_regs.ioc_fwstate) &
			BFA_IOC_CB_FWSTATE_MASK);
पूर्ण

अटल व्योम
bfa_ioc_cb_set_alt_ioc_fwstate(काष्ठा bfa_ioc_s *ioc,
			क्रमागत bfi_ioc_state fwstate)
अणु
	u32 r32 = पढ़ोl(ioc->ioc_regs.alt_ioc_fwstate);

	ग_लिखोl((fwstate | (r32 & BFA_IOC_CB_JOIN_MASK)),
				ioc->ioc_regs.alt_ioc_fwstate);
पूर्ण

अटल क्रमागत bfi_ioc_state
bfa_ioc_cb_get_alt_ioc_fwstate(काष्ठा bfa_ioc_s *ioc)
अणु
	वापस (क्रमागत bfi_ioc_state)(पढ़ोl(ioc->ioc_regs.alt_ioc_fwstate) &
			BFA_IOC_CB_FWSTATE_MASK);
पूर्ण

अटल व्योम
bfa_ioc_cb_sync_ack(काष्ठा bfa_ioc_s *ioc)
अणु
	bfa_ioc_cb_set_cur_ioc_fwstate(ioc, BFI_IOC_FAIL);
पूर्ण

अटल bfa_boolean_t
bfa_ioc_cb_sync_complete(काष्ठा bfa_ioc_s *ioc)
अणु
	u32 fwstate, alt_fwstate;
	fwstate = bfa_ioc_cb_get_cur_ioc_fwstate(ioc);

	/*
	 * At this poपूर्णांक, this IOC is hoding the hw sem in the
	 * start path (fwcheck) OR in the disable/enable path
	 * OR to check अगर the other IOC has acknowledged failure.
	 *
	 * So, this IOC can be in UNINIT, INITING, DISABLED, FAIL
	 * or in MEMTEST states. In a normal scenario, this IOC
	 * can not be in OP state when this function is called.
	 *
	 * However, this IOC could still be in OP state when
	 * the OS driver is starting up, अगर the OptROM code has
	 * left it in that state.
	 *
	 * If we had marked this IOC's fwstate as BFI_IOC_FAIL
	 * in the failure हाल and now, अगर the fwstate is not
	 * BFI_IOC_FAIL it implies that the other PCI fn have
	 * reinitialized the ASIC or this IOC got disabled, so
	 * वापस TRUE.
	 */
	अगर (fwstate == BFI_IOC_UNINIT ||
		fwstate == BFI_IOC_INITING ||
		fwstate == BFI_IOC_DISABLED ||
		fwstate == BFI_IOC_MEMTEST ||
		fwstate == BFI_IOC_OP)
		वापस BFA_TRUE;
	अन्यथा अणु
		alt_fwstate = bfa_ioc_cb_get_alt_ioc_fwstate(ioc);
		अगर (alt_fwstate == BFI_IOC_FAIL ||
			alt_fwstate == BFI_IOC_DISABLED ||
			alt_fwstate == BFI_IOC_UNINIT ||
			alt_fwstate == BFI_IOC_INITING ||
			alt_fwstate == BFI_IOC_MEMTEST)
			वापस BFA_TRUE;
		अन्यथा
			वापस BFA_FALSE;
	पूर्ण
पूर्ण

bfa_status_t
bfa_ioc_cb_pll_init(व्योम __iomem *rb, क्रमागत bfi_asic_mode fcmode)
अणु
	u32	pll_sclk, pll_fclk, join_bits;

	pll_sclk = __APP_PLL_SCLK_ENABLE | __APP_PLL_SCLK_LRESETN |
		__APP_PLL_SCLK_P0_1(3U) |
		__APP_PLL_SCLK_JITLMT0_1(3U) |
		__APP_PLL_SCLK_CNTLMT0_1(3U);
	pll_fclk = __APP_PLL_LCLK_ENABLE | __APP_PLL_LCLK_LRESETN |
		__APP_PLL_LCLK_RSEL200500 | __APP_PLL_LCLK_P0_1(3U) |
		__APP_PLL_LCLK_JITLMT0_1(3U) |
		__APP_PLL_LCLK_CNTLMT0_1(3U);
	join_bits = पढ़ोl(rb + BFA_IOC0_STATE_REG) &
			BFA_IOC_CB_JOIN_MASK;
	ग_लिखोl((BFI_IOC_UNINIT | join_bits), (rb + BFA_IOC0_STATE_REG));
	join_bits = पढ़ोl(rb + BFA_IOC1_STATE_REG) &
			BFA_IOC_CB_JOIN_MASK;
	ग_लिखोl((BFI_IOC_UNINIT | join_bits), (rb + BFA_IOC1_STATE_REG));
	ग_लिखोl(0xffffffffU, (rb + HOSTFN0_INT_MSK));
	ग_लिखोl(0xffffffffU, (rb + HOSTFN1_INT_MSK));
	ग_लिखोl(0xffffffffU, (rb + HOSTFN0_INT_STATUS));
	ग_लिखोl(0xffffffffU, (rb + HOSTFN1_INT_STATUS));
	ग_लिखोl(0xffffffffU, (rb + HOSTFN0_INT_MSK));
	ग_लिखोl(0xffffffffU, (rb + HOSTFN1_INT_MSK));
	ग_लिखोl(__APP_PLL_SCLK_LOGIC_SOFT_RESET, rb + APP_PLL_SCLK_CTL_REG);
	ग_लिखोl(__APP_PLL_SCLK_BYPASS | __APP_PLL_SCLK_LOGIC_SOFT_RESET,
			rb + APP_PLL_SCLK_CTL_REG);
	ग_लिखोl(__APP_PLL_LCLK_LOGIC_SOFT_RESET, rb + APP_PLL_LCLK_CTL_REG);
	ग_लिखोl(__APP_PLL_LCLK_BYPASS | __APP_PLL_LCLK_LOGIC_SOFT_RESET,
			rb + APP_PLL_LCLK_CTL_REG);
	udelay(2);
	ग_लिखोl(__APP_PLL_SCLK_LOGIC_SOFT_RESET, rb + APP_PLL_SCLK_CTL_REG);
	ग_लिखोl(__APP_PLL_LCLK_LOGIC_SOFT_RESET, rb + APP_PLL_LCLK_CTL_REG);
	ग_लिखोl(pll_sclk | __APP_PLL_SCLK_LOGIC_SOFT_RESET,
			rb + APP_PLL_SCLK_CTL_REG);
	ग_लिखोl(pll_fclk | __APP_PLL_LCLK_LOGIC_SOFT_RESET,
			rb + APP_PLL_LCLK_CTL_REG);
	udelay(2000);
	ग_लिखोl(0xffffffffU, (rb + HOSTFN0_INT_STATUS));
	ग_लिखोl(0xffffffffU, (rb + HOSTFN1_INT_STATUS));
	ग_लिखोl(pll_sclk, (rb + APP_PLL_SCLK_CTL_REG));
	ग_लिखोl(pll_fclk, (rb + APP_PLL_LCLK_CTL_REG));

	वापस BFA_STATUS_OK;
पूर्ण
