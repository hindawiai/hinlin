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

BFA_TRC_खाता(CNA, IOC_CT);

#घोषणा bfa_ioc_ct_sync_pos(__ioc)      \
		((uपूर्णांक32_t) (1 << bfa_ioc_pcअगरn(__ioc)))
#घोषणा BFA_IOC_SYNC_REQD_SH    16
#घोषणा bfa_ioc_ct_get_sync_ackd(__val) (__val & 0x0000ffff)
#घोषणा bfa_ioc_ct_clear_sync_ackd(__val)       (__val & 0xffff0000)
#घोषणा bfa_ioc_ct_get_sync_reqd(__val) (__val >> BFA_IOC_SYNC_REQD_SH)
#घोषणा bfa_ioc_ct_sync_reqd_pos(__ioc) \
			(bfa_ioc_ct_sync_pos(__ioc) << BFA_IOC_SYNC_REQD_SH)

/*
 * क्रमward declarations
 */
अटल bfa_boolean_t bfa_ioc_ct_firmware_lock(काष्ठा bfa_ioc_s *ioc);
अटल व्योम bfa_ioc_ct_firmware_unlock(काष्ठा bfa_ioc_s *ioc);
अटल व्योम bfa_ioc_ct_notअगरy_fail(काष्ठा bfa_ioc_s *ioc);
अटल व्योम bfa_ioc_ct_ownership_reset(काष्ठा bfa_ioc_s *ioc);
अटल bfa_boolean_t bfa_ioc_ct_sync_start(काष्ठा bfa_ioc_s *ioc);
अटल व्योम bfa_ioc_ct_sync_join(काष्ठा bfa_ioc_s *ioc);
अटल व्योम bfa_ioc_ct_sync_leave(काष्ठा bfa_ioc_s *ioc);
अटल व्योम bfa_ioc_ct_sync_ack(काष्ठा bfa_ioc_s *ioc);
अटल bfa_boolean_t bfa_ioc_ct_sync_complete(काष्ठा bfa_ioc_s *ioc);
अटल व्योम bfa_ioc_ct_set_cur_ioc_fwstate(
			काष्ठा bfa_ioc_s *ioc, क्रमागत bfi_ioc_state fwstate);
अटल क्रमागत bfi_ioc_state bfa_ioc_ct_get_cur_ioc_fwstate(काष्ठा bfa_ioc_s *ioc);
अटल व्योम bfa_ioc_ct_set_alt_ioc_fwstate(
			काष्ठा bfa_ioc_s *ioc, क्रमागत bfi_ioc_state fwstate);
अटल क्रमागत bfi_ioc_state bfa_ioc_ct_get_alt_ioc_fwstate(काष्ठा bfa_ioc_s *ioc);

अटल काष्ठा bfa_ioc_hwअगर_s hwअगर_ct;
अटल काष्ठा bfa_ioc_hwअगर_s hwअगर_ct2;

/*
 * Return true अगर firmware of current driver matches the running firmware.
 */
अटल bfa_boolean_t
bfa_ioc_ct_firmware_lock(काष्ठा bfa_ioc_s *ioc)
अणु
	क्रमागत bfi_ioc_state ioc_fwstate;
	u32 usecnt;
	काष्ठा bfi_ioc_image_hdr_s fwhdr;

	bfa_ioc_sem_get(ioc->ioc_regs.ioc_usage_sem_reg);
	usecnt = पढ़ोl(ioc->ioc_regs.ioc_usage_reg);

	/*
	 * If usage count is 0, always वापस TRUE.
	 */
	अगर (usecnt == 0) अणु
		ग_लिखोl(1, ioc->ioc_regs.ioc_usage_reg);
		पढ़ोl(ioc->ioc_regs.ioc_usage_sem_reg);
		ग_लिखोl(1, ioc->ioc_regs.ioc_usage_sem_reg);
		ग_लिखोl(0, ioc->ioc_regs.ioc_fail_sync);
		bfa_trc(ioc, usecnt);
		वापस BFA_TRUE;
	पूर्ण

	ioc_fwstate = पढ़ोl(ioc->ioc_regs.ioc_fwstate);
	bfa_trc(ioc, ioc_fwstate);

	/*
	 * Use count cannot be non-zero and chip in uninitialized state.
	 */
	WARN_ON(ioc_fwstate == BFI_IOC_UNINIT);

	/*
	 * Check अगर another driver with a dअगरferent firmware is active
	 */
	bfa_ioc_fwver_get(ioc, &fwhdr);
	अगर (!bfa_ioc_fwver_cmp(ioc, &fwhdr)) अणु
		पढ़ोl(ioc->ioc_regs.ioc_usage_sem_reg);
		ग_लिखोl(1, ioc->ioc_regs.ioc_usage_sem_reg);
		bfa_trc(ioc, usecnt);
		वापस BFA_FALSE;
	पूर्ण

	/*
	 * Same firmware version. Increment the reference count.
	 */
	usecnt++;
	ग_लिखोl(usecnt, ioc->ioc_regs.ioc_usage_reg);
	पढ़ोl(ioc->ioc_regs.ioc_usage_sem_reg);
	ग_लिखोl(1, ioc->ioc_regs.ioc_usage_sem_reg);
	bfa_trc(ioc, usecnt);
	वापस BFA_TRUE;
पूर्ण

अटल व्योम
bfa_ioc_ct_firmware_unlock(काष्ठा bfa_ioc_s *ioc)
अणु
	u32 usecnt;

	/*
	 * decrement usage count
	 */
	bfa_ioc_sem_get(ioc->ioc_regs.ioc_usage_sem_reg);
	usecnt = पढ़ोl(ioc->ioc_regs.ioc_usage_reg);
	WARN_ON(usecnt <= 0);

	usecnt--;
	ग_लिखोl(usecnt, ioc->ioc_regs.ioc_usage_reg);
	bfa_trc(ioc, usecnt);

	पढ़ोl(ioc->ioc_regs.ioc_usage_sem_reg);
	ग_लिखोl(1, ioc->ioc_regs.ioc_usage_sem_reg);
पूर्ण

/*
 * Notअगरy other functions on HB failure.
 */
अटल व्योम
bfa_ioc_ct_notअगरy_fail(काष्ठा bfa_ioc_s *ioc)
अणु
	अगर (bfa_ioc_is_cna(ioc)) अणु
		ग_लिखोl(__FW_INIT_HALT_P, ioc->ioc_regs.ll_halt);
		ग_लिखोl(__FW_INIT_HALT_P, ioc->ioc_regs.alt_ll_halt);
		/* Wait क्रम halt to take effect */
		पढ़ोl(ioc->ioc_regs.ll_halt);
		पढ़ोl(ioc->ioc_regs.alt_ll_halt);
	पूर्ण अन्यथा अणु
		ग_लिखोl(~0U, ioc->ioc_regs.err_set);
		पढ़ोl(ioc->ioc_regs.err_set);
	पूर्ण
पूर्ण

/*
 * Host to LPU mailbox message addresses
 */
अटल काष्ठा अणु u32 hfn_mbox, lpu_mbox, hfn_pgn; पूर्ण ct_fnreg[] = अणु
	अणु HOSTFN0_LPU_MBOX0_0, LPU_HOSTFN0_MBOX0_0, HOST_PAGE_NUM_FN0 पूर्ण,
	अणु HOSTFN1_LPU_MBOX0_8, LPU_HOSTFN1_MBOX0_8, HOST_PAGE_NUM_FN1 पूर्ण,
	अणु HOSTFN2_LPU_MBOX0_0, LPU_HOSTFN2_MBOX0_0, HOST_PAGE_NUM_FN2 पूर्ण,
	अणु HOSTFN3_LPU_MBOX0_8, LPU_HOSTFN3_MBOX0_8, HOST_PAGE_NUM_FN3 पूर्ण
पूर्ण;

/*
 * Host <-> LPU mailbox command/status रेजिस्टरs - port 0
 */
अटल काष्ठा अणु u32 hfn, lpu; पूर्ण ct_p0reg[] = अणु
	अणु HOSTFN0_LPU0_CMD_STAT, LPU0_HOSTFN0_CMD_STAT पूर्ण,
	अणु HOSTFN1_LPU0_CMD_STAT, LPU0_HOSTFN1_CMD_STAT पूर्ण,
	अणु HOSTFN2_LPU0_CMD_STAT, LPU0_HOSTFN2_CMD_STAT पूर्ण,
	अणु HOSTFN3_LPU0_CMD_STAT, LPU0_HOSTFN3_CMD_STAT पूर्ण
पूर्ण;

/*
 * Host <-> LPU mailbox command/status रेजिस्टरs - port 1
 */
अटल काष्ठा अणु u32 hfn, lpu; पूर्ण ct_p1reg[] = अणु
	अणु HOSTFN0_LPU1_CMD_STAT, LPU1_HOSTFN0_CMD_STAT पूर्ण,
	अणु HOSTFN1_LPU1_CMD_STAT, LPU1_HOSTFN1_CMD_STAT पूर्ण,
	अणु HOSTFN2_LPU1_CMD_STAT, LPU1_HOSTFN2_CMD_STAT पूर्ण,
	अणु HOSTFN3_LPU1_CMD_STAT, LPU1_HOSTFN3_CMD_STAT पूर्ण
पूर्ण;

अटल काष्ठा अणु uपूर्णांक32_t hfn_mbox, lpu_mbox, hfn_pgn, hfn, lpu, lpu_पढ़ो; पूर्ण
	ct2_reg[] = अणु
	अणु CT2_HOSTFN_LPU0_MBOX0, CT2_LPU0_HOSTFN_MBOX0, CT2_HOSTFN_PAGE_NUM,
	  CT2_HOSTFN_LPU0_CMD_STAT, CT2_LPU0_HOSTFN_CMD_STAT,
	  CT2_HOSTFN_LPU0_READ_STATपूर्ण,
	अणु CT2_HOSTFN_LPU1_MBOX0, CT2_LPU1_HOSTFN_MBOX0, CT2_HOSTFN_PAGE_NUM,
	  CT2_HOSTFN_LPU1_CMD_STAT, CT2_LPU1_HOSTFN_CMD_STAT,
	  CT2_HOSTFN_LPU1_READ_STATपूर्ण,
पूर्ण;

अटल व्योम
bfa_ioc_ct_reg_init(काष्ठा bfa_ioc_s *ioc)
अणु
	व्योम __iomem *rb;
	पूर्णांक		pcअगरn = bfa_ioc_pcअगरn(ioc);

	rb = bfa_ioc_bar0(ioc);

	ioc->ioc_regs.hfn_mbox = rb + ct_fnreg[pcअगरn].hfn_mbox;
	ioc->ioc_regs.lpu_mbox = rb + ct_fnreg[pcअगरn].lpu_mbox;
	ioc->ioc_regs.host_page_num_fn = rb + ct_fnreg[pcअगरn].hfn_pgn;

	अगर (ioc->port_id == 0) अणु
		ioc->ioc_regs.heartbeat = rb + BFA_IOC0_HBEAT_REG;
		ioc->ioc_regs.ioc_fwstate = rb + BFA_IOC0_STATE_REG;
		ioc->ioc_regs.alt_ioc_fwstate = rb + BFA_IOC1_STATE_REG;
		ioc->ioc_regs.hfn_mbox_cmd = rb + ct_p0reg[pcअगरn].hfn;
		ioc->ioc_regs.lpu_mbox_cmd = rb + ct_p0reg[pcअगरn].lpu;
		ioc->ioc_regs.ll_halt = rb + FW_INIT_HALT_P0;
		ioc->ioc_regs.alt_ll_halt = rb + FW_INIT_HALT_P1;
	पूर्ण अन्यथा अणु
		ioc->ioc_regs.heartbeat = (rb + BFA_IOC1_HBEAT_REG);
		ioc->ioc_regs.ioc_fwstate = (rb + BFA_IOC1_STATE_REG);
		ioc->ioc_regs.alt_ioc_fwstate = rb + BFA_IOC0_STATE_REG;
		ioc->ioc_regs.hfn_mbox_cmd = rb + ct_p1reg[pcअगरn].hfn;
		ioc->ioc_regs.lpu_mbox_cmd = rb + ct_p1reg[pcअगरn].lpu;
		ioc->ioc_regs.ll_halt = rb + FW_INIT_HALT_P1;
		ioc->ioc_regs.alt_ll_halt = rb + FW_INIT_HALT_P0;
	पूर्ण

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
	ioc->ioc_regs.ioc_usage_sem_reg = (rb + HOST_SEM1_REG);
	ioc->ioc_regs.ioc_init_sem_reg = (rb + HOST_SEM2_REG);
	ioc->ioc_regs.ioc_usage_reg = (rb + BFA_FW_USE_COUNT);
	ioc->ioc_regs.ioc_fail_sync = (rb + BFA_IOC_FAIL_SYNC);

	/*
	 * sram memory access
	 */
	ioc->ioc_regs.smem_page_start = (rb + PSS_SMEM_PAGE_START);
	ioc->ioc_regs.smem_pg0 = BFI_IOC_SMEM_PG0_CT;

	/*
	 * err set reg : क्रम notअगरication of hb failure in fcmode
	 */
	ioc->ioc_regs.err_set = (rb + ERR_SET_REG);
पूर्ण

अटल व्योम
bfa_ioc_ct2_reg_init(काष्ठा bfa_ioc_s *ioc)
अणु
	व्योम __iomem *rb;
	पूर्णांक	port = bfa_ioc_portid(ioc);

	rb = bfa_ioc_bar0(ioc);

	ioc->ioc_regs.hfn_mbox = rb + ct2_reg[port].hfn_mbox;
	ioc->ioc_regs.lpu_mbox = rb + ct2_reg[port].lpu_mbox;
	ioc->ioc_regs.host_page_num_fn = rb + ct2_reg[port].hfn_pgn;
	ioc->ioc_regs.hfn_mbox_cmd = rb + ct2_reg[port].hfn;
	ioc->ioc_regs.lpu_mbox_cmd = rb + ct2_reg[port].lpu;
	ioc->ioc_regs.lpu_पढ़ो_stat = rb + ct2_reg[port].lpu_पढ़ो;

	अगर (port == 0) अणु
		ioc->ioc_regs.heartbeat = rb + CT2_BFA_IOC0_HBEAT_REG;
		ioc->ioc_regs.ioc_fwstate = rb + CT2_BFA_IOC0_STATE_REG;
		ioc->ioc_regs.alt_ioc_fwstate = rb + CT2_BFA_IOC1_STATE_REG;
		ioc->ioc_regs.ll_halt = rb + FW_INIT_HALT_P0;
		ioc->ioc_regs.alt_ll_halt = rb + FW_INIT_HALT_P1;
	पूर्ण अन्यथा अणु
		ioc->ioc_regs.heartbeat = (rb + CT2_BFA_IOC1_HBEAT_REG);
		ioc->ioc_regs.ioc_fwstate = (rb + CT2_BFA_IOC1_STATE_REG);
		ioc->ioc_regs.alt_ioc_fwstate = rb + CT2_BFA_IOC0_STATE_REG;
		ioc->ioc_regs.ll_halt = rb + FW_INIT_HALT_P1;
		ioc->ioc_regs.alt_ll_halt = rb + FW_INIT_HALT_P0;
	पूर्ण

	/*
	 * PSS control रेजिस्टरs
	 */
	ioc->ioc_regs.pss_ctl_reg = (rb + PSS_CTL_REG);
	ioc->ioc_regs.pss_err_status_reg = (rb + PSS_ERR_STATUS_REG);
	ioc->ioc_regs.app_pll_fast_ctl_reg = (rb + CT2_APP_PLL_LCLK_CTL_REG);
	ioc->ioc_regs.app_pll_slow_ctl_reg = (rb + CT2_APP_PLL_SCLK_CTL_REG);

	/*
	 * IOC semaphore रेजिस्टरs and serialization
	 */
	ioc->ioc_regs.ioc_sem_reg = (rb + CT2_HOST_SEM0_REG);
	ioc->ioc_regs.ioc_usage_sem_reg = (rb + CT2_HOST_SEM1_REG);
	ioc->ioc_regs.ioc_init_sem_reg = (rb + CT2_HOST_SEM2_REG);
	ioc->ioc_regs.ioc_usage_reg = (rb + CT2_BFA_FW_USE_COUNT);
	ioc->ioc_regs.ioc_fail_sync = (rb + CT2_BFA_IOC_FAIL_SYNC);

	/*
	 * sram memory access
	 */
	ioc->ioc_regs.smem_page_start = (rb + PSS_SMEM_PAGE_START);
	ioc->ioc_regs.smem_pg0 = BFI_IOC_SMEM_PG0_CT;

	/*
	 * err set reg : क्रम notअगरication of hb failure in fcmode
	 */
	ioc->ioc_regs.err_set = (rb + ERR_SET_REG);
पूर्ण

/*
 * Initialize IOC to port mapping.
 */

#घोषणा FNC_PERS_FN_SHIFT(__fn)	((__fn) * 8)
अटल व्योम
bfa_ioc_ct_map_port(काष्ठा bfa_ioc_s *ioc)
अणु
	व्योम __iomem *rb = ioc->pcidev.pci_bar_kva;
	u32	r32;

	/*
	 * For catapult, base port id on personality रेजिस्टर and IOC type
	 */
	r32 = पढ़ोl(rb + FNC_PERS_REG);
	r32 >>= FNC_PERS_FN_SHIFT(bfa_ioc_pcअगरn(ioc));
	ioc->port_id = (r32 & __F0_PORT_MAP_MK) >> __F0_PORT_MAP_SH;

	bfa_trc(ioc, bfa_ioc_pcअगरn(ioc));
	bfa_trc(ioc, ioc->port_id);
पूर्ण

अटल व्योम
bfa_ioc_ct2_map_port(काष्ठा bfa_ioc_s *ioc)
अणु
	व्योम __iomem	*rb = ioc->pcidev.pci_bar_kva;
	u32	r32;

	r32 = पढ़ोl(rb + CT2_HOSTFN_PERSONALITY0);
	ioc->port_id = ((r32 & __FC_LL_PORT_MAP__MK) >> __FC_LL_PORT_MAP__SH);

	bfa_trc(ioc, bfa_ioc_pcअगरn(ioc));
	bfa_trc(ioc, ioc->port_id);
पूर्ण

/*
 * Set पूर्णांकerrupt mode क्रम a function: INTX or MSIX
 */
अटल व्योम
bfa_ioc_ct_isr_mode_set(काष्ठा bfa_ioc_s *ioc, bfa_boolean_t msix)
अणु
	व्योम __iomem *rb = ioc->pcidev.pci_bar_kva;
	u32	r32, mode;

	r32 = पढ़ोl(rb + FNC_PERS_REG);
	bfa_trc(ioc, r32);

	mode = (r32 >> FNC_PERS_FN_SHIFT(bfa_ioc_pcअगरn(ioc))) &
		__F0_INTX_STATUS;

	/*
	 * If alपढ़ोy in desired mode, करो not change anything
	 */
	अगर ((!msix && mode) || (msix && !mode))
		वापस;

	अगर (msix)
		mode = __F0_INTX_STATUS_MSIX;
	अन्यथा
		mode = __F0_INTX_STATUS_INTA;

	r32 &= ~(__F0_INTX_STATUS << FNC_PERS_FN_SHIFT(bfa_ioc_pcअगरn(ioc)));
	r32 |= (mode << FNC_PERS_FN_SHIFT(bfa_ioc_pcअगरn(ioc)));
	bfa_trc(ioc, r32);

	ग_लिखोl(r32, rb + FNC_PERS_REG);
पूर्ण

अटल bfa_boolean_t
bfa_ioc_ct2_lpu_पढ़ो_stat(काष्ठा bfa_ioc_s *ioc)
अणु
	u32	r32;

	r32 = पढ़ोl(ioc->ioc_regs.lpu_पढ़ो_stat);
	अगर (r32) अणु
		ग_लिखोl(1, ioc->ioc_regs.lpu_पढ़ो_stat);
		वापस BFA_TRUE;
	पूर्ण

	वापस BFA_FALSE;
पूर्ण

/*
 * Cleanup hw semaphore and usecnt रेजिस्टरs
 */
अटल व्योम
bfa_ioc_ct_ownership_reset(काष्ठा bfa_ioc_s *ioc)
अणु

	bfa_ioc_sem_get(ioc->ioc_regs.ioc_usage_sem_reg);
	ग_लिखोl(0, ioc->ioc_regs.ioc_usage_reg);
	पढ़ोl(ioc->ioc_regs.ioc_usage_sem_reg);
	ग_लिखोl(1, ioc->ioc_regs.ioc_usage_sem_reg);

	ग_लिखोl(0, ioc->ioc_regs.ioc_fail_sync);
	/*
	 * Read the hw sem reg to make sure that it is locked
	 * beक्रमe we clear it. If it is not locked, writing 1
	 * will lock it instead of clearing it.
	 */
	पढ़ोl(ioc->ioc_regs.ioc_sem_reg);
	ग_लिखोl(1, ioc->ioc_regs.ioc_sem_reg);
पूर्ण

अटल bfa_boolean_t
bfa_ioc_ct_sync_start(काष्ठा bfa_ioc_s *ioc)
अणु
	uपूर्णांक32_t r32 = पढ़ोl(ioc->ioc_regs.ioc_fail_sync);
	uपूर्णांक32_t sync_reqd = bfa_ioc_ct_get_sync_reqd(r32);

	/*
	 * Driver load समय.  If the sync required bit क्रम this PCI fn
	 * is set, it is due to an unclean निकास by the driver क्रम this
	 * PCI fn in the previous incarnation. Whoever comes here first
	 * should clean it up, no matter which PCI fn.
	 */

	अगर (sync_reqd & bfa_ioc_ct_sync_pos(ioc)) अणु
		ग_लिखोl(0, ioc->ioc_regs.ioc_fail_sync);
		ग_लिखोl(1, ioc->ioc_regs.ioc_usage_reg);
		ग_लिखोl(BFI_IOC_UNINIT, ioc->ioc_regs.ioc_fwstate);
		ग_लिखोl(BFI_IOC_UNINIT, ioc->ioc_regs.alt_ioc_fwstate);
		वापस BFA_TRUE;
	पूर्ण

	वापस bfa_ioc_ct_sync_complete(ioc);
पूर्ण

/*
 * Synchronized IOC failure processing routines
 */
अटल व्योम
bfa_ioc_ct_sync_join(काष्ठा bfa_ioc_s *ioc)
अणु
	uपूर्णांक32_t r32 = पढ़ोl(ioc->ioc_regs.ioc_fail_sync);
	uपूर्णांक32_t sync_pos = bfa_ioc_ct_sync_reqd_pos(ioc);

	ग_लिखोl((r32 | sync_pos), ioc->ioc_regs.ioc_fail_sync);
पूर्ण

अटल व्योम
bfa_ioc_ct_sync_leave(काष्ठा bfa_ioc_s *ioc)
अणु
	uपूर्णांक32_t r32 = पढ़ोl(ioc->ioc_regs.ioc_fail_sync);
	uपूर्णांक32_t sync_msk = bfa_ioc_ct_sync_reqd_pos(ioc) |
					bfa_ioc_ct_sync_pos(ioc);

	ग_लिखोl((r32 & ~sync_msk), ioc->ioc_regs.ioc_fail_sync);
पूर्ण

अटल व्योम
bfa_ioc_ct_sync_ack(काष्ठा bfa_ioc_s *ioc)
अणु
	uपूर्णांक32_t r32 = पढ़ोl(ioc->ioc_regs.ioc_fail_sync);

	ग_लिखोl((r32 | bfa_ioc_ct_sync_pos(ioc)),
		ioc->ioc_regs.ioc_fail_sync);
पूर्ण

अटल bfa_boolean_t
bfa_ioc_ct_sync_complete(काष्ठा bfa_ioc_s *ioc)
अणु
	uपूर्णांक32_t r32 = पढ़ोl(ioc->ioc_regs.ioc_fail_sync);
	uपूर्णांक32_t sync_reqd = bfa_ioc_ct_get_sync_reqd(r32);
	uपूर्णांक32_t sync_ackd = bfa_ioc_ct_get_sync_ackd(r32);
	uपूर्णांक32_t पंचांगp_ackd;

	अगर (sync_ackd == 0)
		वापस BFA_TRUE;

	/*
	 * The check below is to see whether any other PCI fn
	 * has reinitialized the ASIC (reset sync_ackd bits)
	 * and failed again जबतक this IOC was रुकोing क्रम hw
	 * semaphore (in bfa_iocpf_sm_semरुको()).
	 */
	पंचांगp_ackd = sync_ackd;
	अगर ((sync_reqd &  bfa_ioc_ct_sync_pos(ioc)) &&
		!(sync_ackd & bfa_ioc_ct_sync_pos(ioc)))
		sync_ackd |= bfa_ioc_ct_sync_pos(ioc);

	अगर (sync_reqd == sync_ackd) अणु
		ग_लिखोl(bfa_ioc_ct_clear_sync_ackd(r32),
			ioc->ioc_regs.ioc_fail_sync);
		ग_लिखोl(BFI_IOC_FAIL, ioc->ioc_regs.ioc_fwstate);
		ग_लिखोl(BFI_IOC_FAIL, ioc->ioc_regs.alt_ioc_fwstate);
		वापस BFA_TRUE;
	पूर्ण

	/*
	 * If another PCI fn reinitialized and failed again जबतक
	 * this IOC was रुकोing क्रम hw sem, the sync_ackd bit क्रम
	 * this IOC need to be set again to allow reinitialization.
	 */
	अगर (पंचांगp_ackd != sync_ackd)
		ग_लिखोl((r32 | sync_ackd), ioc->ioc_regs.ioc_fail_sync);

	वापस BFA_FALSE;
पूर्ण

/*
 * Called from bfa_ioc_attach() to map asic specअगरic calls.
 */
अटल व्योम
bfa_ioc_set_ctx_hwअगर(काष्ठा bfa_ioc_s *ioc, काष्ठा bfa_ioc_hwअगर_s *hwअगर)
अणु
	hwअगर->ioc_firmware_lock = bfa_ioc_ct_firmware_lock;
	hwअगर->ioc_firmware_unlock = bfa_ioc_ct_firmware_unlock;
	hwअगर->ioc_notअगरy_fail = bfa_ioc_ct_notअगरy_fail;
	hwअगर->ioc_ownership_reset = bfa_ioc_ct_ownership_reset;
	hwअगर->ioc_sync_start = bfa_ioc_ct_sync_start;
	hwअगर->ioc_sync_join = bfa_ioc_ct_sync_join;
	hwअगर->ioc_sync_leave = bfa_ioc_ct_sync_leave;
	hwअगर->ioc_sync_ack = bfa_ioc_ct_sync_ack;
	hwअगर->ioc_sync_complete = bfa_ioc_ct_sync_complete;
	hwअगर->ioc_set_fwstate = bfa_ioc_ct_set_cur_ioc_fwstate;
	hwअगर->ioc_get_fwstate = bfa_ioc_ct_get_cur_ioc_fwstate;
	hwअगर->ioc_set_alt_fwstate = bfa_ioc_ct_set_alt_ioc_fwstate;
	hwअगर->ioc_get_alt_fwstate = bfa_ioc_ct_get_alt_ioc_fwstate;
पूर्ण

/*
 * Called from bfa_ioc_attach() to map asic specअगरic calls.
 */
व्योम
bfa_ioc_set_ct_hwअगर(काष्ठा bfa_ioc_s *ioc)
अणु
	bfa_ioc_set_ctx_hwअगर(ioc, &hwअगर_ct);

	hwअगर_ct.ioc_pll_init = bfa_ioc_ct_pll_init;
	hwअगर_ct.ioc_reg_init = bfa_ioc_ct_reg_init;
	hwअगर_ct.ioc_map_port = bfa_ioc_ct_map_port;
	hwअगर_ct.ioc_isr_mode_set = bfa_ioc_ct_isr_mode_set;
	ioc->ioc_hwअगर = &hwअगर_ct;
पूर्ण

/*
 * Called from bfa_ioc_attach() to map asic specअगरic calls.
 */
व्योम
bfa_ioc_set_ct2_hwअगर(काष्ठा bfa_ioc_s *ioc)
अणु
	bfa_ioc_set_ctx_hwअगर(ioc, &hwअगर_ct2);

	hwअगर_ct2.ioc_pll_init = bfa_ioc_ct2_pll_init;
	hwअगर_ct2.ioc_reg_init = bfa_ioc_ct2_reg_init;
	hwअगर_ct2.ioc_map_port = bfa_ioc_ct2_map_port;
	hwअगर_ct2.ioc_lpu_पढ़ो_stat = bfa_ioc_ct2_lpu_पढ़ो_stat;
	hwअगर_ct2.ioc_isr_mode_set = शून्य;
	ioc->ioc_hwअगर = &hwअगर_ct2;
पूर्ण

/*
 * Workaround क्रम MSI-X resource allocation क्रम catapult-2 with no asic block
 */
#घोषणा HOSTFN_MSIX_DEFAULT		64
#घोषणा HOSTFN_MSIX_VT_INDEX_MBOX_ERR	0x30138
#घोषणा HOSTFN_MSIX_VT_OFST_NUMVT	0x3013c
#घोषणा __MSIX_VT_NUMVT__MK		0x003ff800
#घोषणा __MSIX_VT_NUMVT__SH		11
#घोषणा __MSIX_VT_NUMVT_(_v)		((_v) << __MSIX_VT_NUMVT__SH)
#घोषणा __MSIX_VT_OFST_			0x000007ff
व्योम
bfa_ioc_ct2_घातeron(काष्ठा bfa_ioc_s *ioc)
अणु
	व्योम __iomem *rb = ioc->pcidev.pci_bar_kva;
	u32	r32;

	r32 = पढ़ोl(rb + HOSTFN_MSIX_VT_OFST_NUMVT);
	अगर (r32 & __MSIX_VT_NUMVT__MK) अणु
		ग_लिखोl(r32 & __MSIX_VT_OFST_,
			rb + HOSTFN_MSIX_VT_INDEX_MBOX_ERR);
		वापस;
	पूर्ण

	ग_लिखोl(__MSIX_VT_NUMVT_(HOSTFN_MSIX_DEFAULT - 1) |
		HOSTFN_MSIX_DEFAULT * bfa_ioc_pcअगरn(ioc),
		rb + HOSTFN_MSIX_VT_OFST_NUMVT);
	ग_लिखोl(HOSTFN_MSIX_DEFAULT * bfa_ioc_pcअगरn(ioc),
		rb + HOSTFN_MSIX_VT_INDEX_MBOX_ERR);
पूर्ण

bfa_status_t
bfa_ioc_ct_pll_init(व्योम __iomem *rb, क्रमागत bfi_asic_mode mode)
अणु
	u32	pll_sclk, pll_fclk, r32;
	bfa_boolean_t fcmode = (mode == BFI_ASIC_MODE_FC);

	pll_sclk = __APP_PLL_SCLK_LRESETN | __APP_PLL_SCLK_ENARST |
		__APP_PLL_SCLK_RSEL200500 | __APP_PLL_SCLK_P0_1(3U) |
		__APP_PLL_SCLK_JITLMT0_1(3U) |
		__APP_PLL_SCLK_CNTLMT0_1(1U);
	pll_fclk = __APP_PLL_LCLK_LRESETN | __APP_PLL_LCLK_ENARST |
		__APP_PLL_LCLK_RSEL200500 | __APP_PLL_LCLK_P0_1(3U) |
		__APP_PLL_LCLK_JITLMT0_1(3U) |
		__APP_PLL_LCLK_CNTLMT0_1(1U);

	अगर (fcmode) अणु
		ग_लिखोl(0, (rb + OP_MODE));
		ग_लिखोl(__APP_EMS_CMLCKSEL | __APP_EMS_REFCKBUFEN2 |
			 __APP_EMS_CHANNEL_SEL, (rb + ETH_MAC_SER_REG));
	पूर्ण अन्यथा अणु
		ग_लिखोl(__GLOBAL_FCOE_MODE, (rb + OP_MODE));
		ग_लिखोl(__APP_EMS_REFCKBUFEN1, (rb + ETH_MAC_SER_REG));
	पूर्ण
	ग_लिखोl(BFI_IOC_UNINIT, (rb + BFA_IOC0_STATE_REG));
	ग_लिखोl(BFI_IOC_UNINIT, (rb + BFA_IOC1_STATE_REG));
	ग_लिखोl(0xffffffffU, (rb + HOSTFN0_INT_MSK));
	ग_लिखोl(0xffffffffU, (rb + HOSTFN1_INT_MSK));
	ग_लिखोl(0xffffffffU, (rb + HOSTFN0_INT_STATUS));
	ग_लिखोl(0xffffffffU, (rb + HOSTFN1_INT_STATUS));
	ग_लिखोl(0xffffffffU, (rb + HOSTFN0_INT_MSK));
	ग_लिखोl(0xffffffffU, (rb + HOSTFN1_INT_MSK));
	ग_लिखोl(pll_sclk | __APP_PLL_SCLK_LOGIC_SOFT_RESET,
			rb + APP_PLL_SCLK_CTL_REG);
	ग_लिखोl(pll_fclk | __APP_PLL_LCLK_LOGIC_SOFT_RESET,
			rb + APP_PLL_LCLK_CTL_REG);
	ग_लिखोl(pll_sclk | __APP_PLL_SCLK_LOGIC_SOFT_RESET |
		__APP_PLL_SCLK_ENABLE, rb + APP_PLL_SCLK_CTL_REG);
	ग_लिखोl(pll_fclk | __APP_PLL_LCLK_LOGIC_SOFT_RESET |
		__APP_PLL_LCLK_ENABLE, rb + APP_PLL_LCLK_CTL_REG);
	पढ़ोl(rb + HOSTFN0_INT_MSK);
	udelay(2000);
	ग_लिखोl(0xffffffffU, (rb + HOSTFN0_INT_STATUS));
	ग_लिखोl(0xffffffffU, (rb + HOSTFN1_INT_STATUS));
	ग_लिखोl(pll_sclk | __APP_PLL_SCLK_ENABLE, rb + APP_PLL_SCLK_CTL_REG);
	ग_लिखोl(pll_fclk | __APP_PLL_LCLK_ENABLE, rb + APP_PLL_LCLK_CTL_REG);

	अगर (!fcmode) अणु
		ग_लिखोl(__PMM_1T_RESET_P, (rb + PMM_1T_RESET_REG_P0));
		ग_लिखोl(__PMM_1T_RESET_P, (rb + PMM_1T_RESET_REG_P1));
	पूर्ण
	r32 = पढ़ोl((rb + PSS_CTL_REG));
	r32 &= ~__PSS_LMEM_RESET;
	ग_लिखोl(r32, (rb + PSS_CTL_REG));
	udelay(1000);
	अगर (!fcmode) अणु
		ग_लिखोl(0, (rb + PMM_1T_RESET_REG_P0));
		ग_लिखोl(0, (rb + PMM_1T_RESET_REG_P1));
	पूर्ण

	ग_लिखोl(__EDRAM_BISTR_START, (rb + MBIST_CTL_REG));
	udelay(1000);
	r32 = पढ़ोl((rb + MBIST_STAT_REG));
	ग_लिखोl(0, (rb + MBIST_CTL_REG));
	वापस BFA_STATUS_OK;
पूर्ण

अटल व्योम
bfa_ioc_ct2_sclk_init(व्योम __iomem *rb)
अणु
	u32 r32;

	/*
	 * put s_clk PLL and PLL FSM in reset
	 */
	r32 = पढ़ोl((rb + CT2_APP_PLL_SCLK_CTL_REG));
	r32 &= ~(__APP_PLL_SCLK_ENABLE | __APP_PLL_SCLK_LRESETN);
	r32 |= (__APP_PLL_SCLK_ENARST | __APP_PLL_SCLK_BYPASS |
		__APP_PLL_SCLK_LOGIC_SOFT_RESET);
	ग_लिखोl(r32, (rb + CT2_APP_PLL_SCLK_CTL_REG));

	/*
	 * Ignore mode and program क्रम the max घड़ी (which is FC16)
	 * Firmware/NFC will करो the PLL init appropiately
	 */
	r32 = पढ़ोl((rb + CT2_APP_PLL_SCLK_CTL_REG));
	r32 &= ~(__APP_PLL_SCLK_REFCLK_SEL | __APP_PLL_SCLK_CLK_DIV2);
	ग_लिखोl(r32, (rb + CT2_APP_PLL_SCLK_CTL_REG));

	/*
	 * जबतक करोing PLL init करोnt घड़ी gate ethernet subप्रणाली
	 */
	r32 = पढ़ोl((rb + CT2_CHIP_MISC_PRG));
	ग_लिखोl(r32 | __ETH_CLK_ENABLE_PORT0, (rb + CT2_CHIP_MISC_PRG));

	r32 = पढ़ोl((rb + CT2_PCIE_MISC_REG));
	ग_लिखोl(r32 | __ETH_CLK_ENABLE_PORT1, (rb + CT2_PCIE_MISC_REG));

	/*
	 * set sclk value
	 */
	r32 = पढ़ोl((rb + CT2_APP_PLL_SCLK_CTL_REG));
	r32 &= (__P_SCLK_PLL_LOCK | __APP_PLL_SCLK_REFCLK_SEL |
		__APP_PLL_SCLK_CLK_DIV2);
	ग_लिखोl(r32 | 0x1061731b, (rb + CT2_APP_PLL_SCLK_CTL_REG));

	/*
	 * poll क्रम s_clk lock or delay 1ms
	 */
	udelay(1000);
पूर्ण

अटल व्योम
bfa_ioc_ct2_lclk_init(व्योम __iomem *rb)
अणु
	u32 r32;

	/*
	 * put l_clk PLL and PLL FSM in reset
	 */
	r32 = पढ़ोl((rb + CT2_APP_PLL_LCLK_CTL_REG));
	r32 &= ~(__APP_PLL_LCLK_ENABLE | __APP_PLL_LCLK_LRESETN);
	r32 |= (__APP_PLL_LCLK_ENARST | __APP_PLL_LCLK_BYPASS |
		__APP_PLL_LCLK_LOGIC_SOFT_RESET);
	ग_लिखोl(r32, (rb + CT2_APP_PLL_LCLK_CTL_REG));

	/*
	 * set LPU speed (set क्रम FC16 which will work क्रम other modes)
	 */
	r32 = पढ़ोl((rb + CT2_CHIP_MISC_PRG));
	ग_लिखोl(r32, (rb + CT2_CHIP_MISC_PRG));

	/*
	 * set LPU half speed (set क्रम FC16 which will work क्रम other modes)
	 */
	r32 = पढ़ोl((rb + CT2_APP_PLL_LCLK_CTL_REG));
	ग_लिखोl(r32, (rb + CT2_APP_PLL_LCLK_CTL_REG));

	/*
	 * set lclk क्रम mode (set क्रम FC16)
	 */
	r32 = पढ़ोl((rb + CT2_APP_PLL_LCLK_CTL_REG));
	r32 &= (__P_LCLK_PLL_LOCK | __APP_LPUCLK_HALFSPEED);
	r32 |= 0x20c1731b;
	ग_लिखोl(r32, (rb + CT2_APP_PLL_LCLK_CTL_REG));

	/*
	 * poll क्रम s_clk lock or delay 1ms
	 */
	udelay(1000);
पूर्ण

अटल व्योम
bfa_ioc_ct2_mem_init(व्योम __iomem *rb)
अणु
	u32	r32;

	r32 = पढ़ोl((rb + PSS_CTL_REG));
	r32 &= ~__PSS_LMEM_RESET;
	ग_लिखोl(r32, (rb + PSS_CTL_REG));
	udelay(1000);

	ग_लिखोl(__EDRAM_BISTR_START, (rb + CT2_MBIST_CTL_REG));
	udelay(1000);
	ग_लिखोl(0, (rb + CT2_MBIST_CTL_REG));
पूर्ण

अटल व्योम
bfa_ioc_ct2_mac_reset(व्योम __iomem *rb)
अणु
	/* put port0, port1 MAC & AHB in reset */
	ग_लिखोl((__CSI_MAC_RESET | __CSI_MAC_AHB_RESET),
		rb + CT2_CSI_MAC_CONTROL_REG(0));
	ग_लिखोl((__CSI_MAC_RESET | __CSI_MAC_AHB_RESET),
		rb + CT2_CSI_MAC_CONTROL_REG(1));
पूर्ण

अटल व्योम
bfa_ioc_ct2_enable_flash(व्योम __iomem *rb)
अणु
	u32 r32;

	r32 = पढ़ोl((rb + PSS_GPIO_OUT_REG));
	ग_लिखोl(r32 & ~1, (rb + PSS_GPIO_OUT_REG));
	r32 = पढ़ोl((rb + PSS_GPIO_OE_REG));
	ग_लिखोl(r32 | 1, (rb + PSS_GPIO_OE_REG));
पूर्ण

#घोषणा CT2_NFC_MAX_DELAY	1000
#घोषणा CT2_NFC_PAUSE_MAX_DELAY 4000
#घोषणा CT2_NFC_VER_VALID	0x147
#घोषणा CT2_NFC_STATE_RUNNING   0x20000001
#घोषणा BFA_IOC_PLL_POLL	1000000

अटल bfa_boolean_t
bfa_ioc_ct2_nfc_halted(व्योम __iomem *rb)
अणु
	u32	r32;

	r32 = पढ़ोl(rb + CT2_NFC_CSR_SET_REG);
	अगर (r32 & __NFC_CONTROLLER_HALTED)
		वापस BFA_TRUE;

	वापस BFA_FALSE;
पूर्ण

अटल व्योम
bfa_ioc_ct2_nfc_halt(व्योम __iomem *rb)
अणु
	पूर्णांक	i;

	ग_लिखोl(__HALT_NFC_CONTROLLER, rb + CT2_NFC_CSR_SET_REG);
	क्रम (i = 0; i < CT2_NFC_MAX_DELAY; i++) अणु
		अगर (bfa_ioc_ct2_nfc_halted(rb))
			अवरोध;
		udelay(1000);
	पूर्ण
	WARN_ON(!bfa_ioc_ct2_nfc_halted(rb));
पूर्ण

अटल व्योम
bfa_ioc_ct2_nfc_resume(व्योम __iomem *rb)
अणु
	u32	r32;
	पूर्णांक i;

	ग_लिखोl(__HALT_NFC_CONTROLLER, rb + CT2_NFC_CSR_CLR_REG);
	क्रम (i = 0; i < CT2_NFC_MAX_DELAY; i++) अणु
		r32 = पढ़ोl(rb + CT2_NFC_CSR_SET_REG);
		अगर (!(r32 & __NFC_CONTROLLER_HALTED))
			वापस;
		udelay(1000);
	पूर्ण
	WARN_ON(1);
पूर्ण

अटल व्योम
bfa_ioc_ct2_clk_reset(व्योम __iomem *rb)
अणु
	u32 r32;

	bfa_ioc_ct2_sclk_init(rb);
	bfa_ioc_ct2_lclk_init(rb);

	/*
	 * release soft reset on s_clk & l_clk
	 */
	r32 = पढ़ोl((rb + CT2_APP_PLL_SCLK_CTL_REG));
	ग_लिखोl(r32 & ~__APP_PLL_SCLK_LOGIC_SOFT_RESET,
			(rb + CT2_APP_PLL_SCLK_CTL_REG));

	r32 = पढ़ोl((rb + CT2_APP_PLL_LCLK_CTL_REG));
	ग_लिखोl(r32 & ~__APP_PLL_LCLK_LOGIC_SOFT_RESET,
			(rb + CT2_APP_PLL_LCLK_CTL_REG));

पूर्ण

अटल व्योम
bfa_ioc_ct2_nfc_clk_reset(व्योम __iomem *rb)
अणु
	u32 r32, i;

	r32 = पढ़ोl((rb + PSS_CTL_REG));
	r32 |= (__PSS_LPU0_RESET | __PSS_LPU1_RESET);
	ग_लिखोl(r32, (rb + PSS_CTL_REG));

	ग_लिखोl(__RESET_AND_START_SCLK_LCLK_PLLS, rb + CT2_CSI_FW_CTL_SET_REG);

	क्रम (i = 0; i < BFA_IOC_PLL_POLL; i++) अणु
		r32 = पढ़ोl(rb + CT2_NFC_FLASH_STS_REG);

		अगर ((r32 & __FLASH_PLL_INIT_AND_RESET_IN_PROGRESS))
			अवरोध;
	पूर्ण
	WARN_ON(!(r32 & __FLASH_PLL_INIT_AND_RESET_IN_PROGRESS));

	क्रम (i = 0; i < BFA_IOC_PLL_POLL; i++) अणु
		r32 = पढ़ोl(rb + CT2_NFC_FLASH_STS_REG);

		अगर (!(r32 & __FLASH_PLL_INIT_AND_RESET_IN_PROGRESS))
			अवरोध;
	पूर्ण
	WARN_ON((r32 & __FLASH_PLL_INIT_AND_RESET_IN_PROGRESS));

	r32 = पढ़ोl(rb + CT2_CSI_FW_CTL_REG);
	WARN_ON((r32 & __RESET_AND_START_SCLK_LCLK_PLLS));
पूर्ण

अटल व्योम
bfa_ioc_ct2_रुको_till_nfc_running(व्योम __iomem *rb)
अणु
	u32 r32;
	पूर्णांक i;

	अगर (bfa_ioc_ct2_nfc_halted(rb))
		bfa_ioc_ct2_nfc_resume(rb);
	क्रम (i = 0; i < CT2_NFC_PAUSE_MAX_DELAY; i++) अणु
		r32 = पढ़ोl(rb + CT2_NFC_STS_REG);
		अगर (r32 == CT2_NFC_STATE_RUNNING)
			वापस;
		udelay(1000);
	पूर्ण

	r32 = पढ़ोl(rb + CT2_NFC_STS_REG);
	WARN_ON(!(r32 == CT2_NFC_STATE_RUNNING));
पूर्ण

bfa_status_t
bfa_ioc_ct2_pll_init(व्योम __iomem *rb, क्रमागत bfi_asic_mode mode)
अणु
	u32 wgn, r32, nfc_ver;

	wgn = पढ़ोl(rb + CT2_WGN_STATUS);

	अगर (wgn == (__WGN_READY | __GLBL_PF_VF_CFG_RDY)) अणु
		/*
		 * If flash is corrupted, enable flash explicitly
		 */
		bfa_ioc_ct2_clk_reset(rb);
		bfa_ioc_ct2_enable_flash(rb);

		bfa_ioc_ct2_mac_reset(rb);

		bfa_ioc_ct2_clk_reset(rb);
		bfa_ioc_ct2_enable_flash(rb);

	पूर्ण अन्यथा अणु
		nfc_ver = पढ़ोl(rb + CT2_RSC_GPR15_REG);

		अगर ((nfc_ver >= CT2_NFC_VER_VALID) &&
		    (wgn == (__A2T_AHB_LOAD | __WGN_READY))) अणु

			bfa_ioc_ct2_रुको_till_nfc_running(rb);

			bfa_ioc_ct2_nfc_clk_reset(rb);
		पूर्ण अन्यथा अणु
			bfa_ioc_ct2_nfc_halt(rb);

			bfa_ioc_ct2_clk_reset(rb);
			bfa_ioc_ct2_mac_reset(rb);
			bfa_ioc_ct2_clk_reset(rb);

		पूर्ण
	पूर्ण
	/*
	* The very first PCIe DMA Read करोne by LPU fails with a fatal error,
	* when Address Translation Cache (ATC) has been enabled by प्रणाली BIOS.
	*
	* Workaround:
	* Disable Invalidated Tag Match Enable capability by setting the bit 26
	* of CHIP_MISC_PRG to 0, by शेष it is set to 1.
	*/
	r32 = पढ़ोl(rb + CT2_CHIP_MISC_PRG);
	ग_लिखोl((r32 & 0xfbffffff), (rb + CT2_CHIP_MISC_PRG));

	/*
	 * Mask the पूर्णांकerrupts and clear any
	 * pending पूर्णांकerrupts left by BIOS/EFI
	 */

	ग_लिखोl(1, (rb + CT2_LPU0_HOSTFN_MBOX0_MSK));
	ग_लिखोl(1, (rb + CT2_LPU1_HOSTFN_MBOX0_MSK));

	/* For first समय initialization, no need to clear पूर्णांकerrupts */
	r32 = पढ़ोl(rb + HOST_SEM5_REG);
	अगर (r32 & 0x1) अणु
		r32 = पढ़ोl((rb + CT2_LPU0_HOSTFN_CMD_STAT));
		अगर (r32 == 1) अणु
			ग_लिखोl(1, (rb + CT2_LPU0_HOSTFN_CMD_STAT));
			पढ़ोl((rb + CT2_LPU0_HOSTFN_CMD_STAT));
		पूर्ण
		r32 = पढ़ोl((rb + CT2_LPU1_HOSTFN_CMD_STAT));
		अगर (r32 == 1) अणु
			ग_लिखोl(1, (rb + CT2_LPU1_HOSTFN_CMD_STAT));
			पढ़ोl((rb + CT2_LPU1_HOSTFN_CMD_STAT));
		पूर्ण
	पूर्ण

	bfa_ioc_ct2_mem_init(rb);

	ग_लिखोl(BFI_IOC_UNINIT, (rb + CT2_BFA_IOC0_STATE_REG));
	ग_लिखोl(BFI_IOC_UNINIT, (rb + CT2_BFA_IOC1_STATE_REG));

	वापस BFA_STATUS_OK;
पूर्ण

अटल व्योम
bfa_ioc_ct_set_cur_ioc_fwstate(काष्ठा bfa_ioc_s *ioc,
		क्रमागत bfi_ioc_state fwstate)
अणु
	ग_लिखोl(fwstate, ioc->ioc_regs.ioc_fwstate);
पूर्ण

अटल क्रमागत bfi_ioc_state
bfa_ioc_ct_get_cur_ioc_fwstate(काष्ठा bfa_ioc_s *ioc)
अणु
	वापस (क्रमागत bfi_ioc_state)पढ़ोl(ioc->ioc_regs.ioc_fwstate);
पूर्ण

अटल व्योम
bfa_ioc_ct_set_alt_ioc_fwstate(काष्ठा bfa_ioc_s *ioc,
		क्रमागत bfi_ioc_state fwstate)
अणु
	ग_लिखोl(fwstate, ioc->ioc_regs.alt_ioc_fwstate);
पूर्ण

अटल क्रमागत bfi_ioc_state
bfa_ioc_ct_get_alt_ioc_fwstate(काष्ठा bfa_ioc_s *ioc)
अणु
	वापस (क्रमागत bfi_ioc_state) पढ़ोl(ioc->ioc_regs.alt_ioc_fwstate);
पूर्ण
