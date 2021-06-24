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
#समावेश "bfa_ioc.h"
#समावेश "bfi_reg.h"
#समावेश "bfa_defs.h"
#समावेश "bfa_defs_svc.h"
#समावेश "bfi.h"

BFA_TRC_खाता(CNA, IOC);

/*
 * IOC local definitions
 */
#घोषणा BFA_IOC_TOV		3000	/* msecs */
#घोषणा BFA_IOC_HWSEM_TOV	500	/* msecs */
#घोषणा BFA_IOC_HB_TOV		500	/* msecs */
#घोषणा BFA_IOC_TOV_RECOVER	 BFA_IOC_HB_TOV
#घोषणा BFA_IOC_POLL_TOV	BFA_TIMER_FREQ

#घोषणा bfa_ioc_समयr_start(__ioc)					\
	bfa_समयr_begin((__ioc)->समयr_mod, &(__ioc)->ioc_समयr,	\
			bfa_ioc_समयout, (__ioc), BFA_IOC_TOV)
#घोषणा bfa_ioc_समयr_stop(__ioc)   bfa_समयr_stop(&(__ioc)->ioc_समयr)

#घोषणा bfa_hb_समयr_start(__ioc)					\
	bfa_समयr_begin((__ioc)->समयr_mod, &(__ioc)->hb_समयr,		\
			bfa_ioc_hb_check, (__ioc), BFA_IOC_HB_TOV)
#घोषणा bfa_hb_समयr_stop(__ioc)	bfa_समयr_stop(&(__ioc)->hb_समयr)

#घोषणा BFA_DBG_FWTRC_OFF(_fn)	(BFI_IOC_TRC_OFF + BFA_DBG_FWTRC_LEN * (_fn))

#घोषणा bfa_ioc_state_disabled(__sm)		\
	(((__sm) == BFI_IOC_UNINIT) ||		\
	((__sm) == BFI_IOC_INITING) ||		\
	((__sm) == BFI_IOC_HWINIT) ||		\
	((__sm) == BFI_IOC_DISABLED) ||		\
	((__sm) == BFI_IOC_FAIL) ||		\
	((__sm) == BFI_IOC_CFG_DISABLED))

/*
 * Asic specअगरic macros : see bfa_hw_cb.c and bfa_hw_ct.c क्रम details.
 */

#घोषणा bfa_ioc_firmware_lock(__ioc)			\
			((__ioc)->ioc_hwअगर->ioc_firmware_lock(__ioc))
#घोषणा bfa_ioc_firmware_unlock(__ioc)			\
			((__ioc)->ioc_hwअगर->ioc_firmware_unlock(__ioc))
#घोषणा bfa_ioc_reg_init(__ioc) ((__ioc)->ioc_hwअगर->ioc_reg_init(__ioc))
#घोषणा bfa_ioc_map_port(__ioc) ((__ioc)->ioc_hwअगर->ioc_map_port(__ioc))
#घोषणा bfa_ioc_notअगरy_fail(__ioc)              \
			((__ioc)->ioc_hwअगर->ioc_notअगरy_fail(__ioc))
#घोषणा bfa_ioc_sync_start(__ioc)               \
			((__ioc)->ioc_hwअगर->ioc_sync_start(__ioc))
#घोषणा bfa_ioc_sync_join(__ioc)                \
			((__ioc)->ioc_hwअगर->ioc_sync_join(__ioc))
#घोषणा bfa_ioc_sync_leave(__ioc)               \
			((__ioc)->ioc_hwअगर->ioc_sync_leave(__ioc))
#घोषणा bfa_ioc_sync_ack(__ioc)                 \
			((__ioc)->ioc_hwअगर->ioc_sync_ack(__ioc))
#घोषणा bfa_ioc_sync_complete(__ioc)            \
			((__ioc)->ioc_hwअगर->ioc_sync_complete(__ioc))
#घोषणा bfa_ioc_set_cur_ioc_fwstate(__ioc, __fwstate)		\
			((__ioc)->ioc_hwअगर->ioc_set_fwstate(__ioc, __fwstate))
#घोषणा bfa_ioc_get_cur_ioc_fwstate(__ioc)		\
			((__ioc)->ioc_hwअगर->ioc_get_fwstate(__ioc))
#घोषणा bfa_ioc_set_alt_ioc_fwstate(__ioc, __fwstate)		\
		((__ioc)->ioc_hwअगर->ioc_set_alt_fwstate(__ioc, __fwstate))
#घोषणा bfa_ioc_get_alt_ioc_fwstate(__ioc)		\
			((__ioc)->ioc_hwअगर->ioc_get_alt_fwstate(__ioc))

#घोषणा bfa_ioc_mbox_cmd_pending(__ioc)		\
			(!list_empty(&((__ioc)->mbox_mod.cmd_q)) || \
			पढ़ोl((__ioc)->ioc_regs.hfn_mbox_cmd))

bfa_boolean_t bfa_स्वतः_recover = BFA_TRUE;

/*
 * क्रमward declarations
 */
अटल व्योम bfa_ioc_hw_sem_get(काष्ठा bfa_ioc_s *ioc);
अटल व्योम bfa_ioc_hwinit(काष्ठा bfa_ioc_s *ioc, bfa_boolean_t क्रमce);
अटल व्योम bfa_ioc_समयout(व्योम *ioc);
अटल व्योम bfa_ioc_poll_fwinit(काष्ठा bfa_ioc_s *ioc);
अटल व्योम bfa_ioc_send_enable(काष्ठा bfa_ioc_s *ioc);
अटल व्योम bfa_ioc_send_disable(काष्ठा bfa_ioc_s *ioc);
अटल व्योम bfa_ioc_send_getattr(काष्ठा bfa_ioc_s *ioc);
अटल व्योम bfa_ioc_hb_monitor(काष्ठा bfa_ioc_s *ioc);
अटल व्योम bfa_ioc_mbox_poll(काष्ठा bfa_ioc_s *ioc);
अटल व्योम bfa_ioc_mbox_flush(काष्ठा bfa_ioc_s *ioc);
अटल व्योम bfa_ioc_recover(काष्ठा bfa_ioc_s *ioc);
अटल व्योम bfa_ioc_event_notअगरy(काष्ठा bfa_ioc_s *ioc ,
				क्रमागत bfa_ioc_event_e event);
अटल व्योम bfa_ioc_disable_comp(काष्ठा bfa_ioc_s *ioc);
अटल व्योम bfa_ioc_lpu_stop(काष्ठा bfa_ioc_s *ioc);
अटल व्योम bfa_ioc_fail_notअगरy(काष्ठा bfa_ioc_s *ioc);
अटल व्योम bfa_ioc_pf_fwmismatch(काष्ठा bfa_ioc_s *ioc);
अटल क्रमागत bfi_ioc_img_ver_cmp_e bfa_ioc_fw_ver_patch_cmp(
				काष्ठा bfi_ioc_image_hdr_s *base_fwhdr,
				काष्ठा bfi_ioc_image_hdr_s *fwhdr_to_cmp);
अटल क्रमागत bfi_ioc_img_ver_cmp_e bfa_ioc_flash_fwver_cmp(
				काष्ठा bfa_ioc_s *ioc,
				काष्ठा bfi_ioc_image_hdr_s *base_fwhdr);

/*
 * IOC state machine definitions/declarations
 */
क्रमागत ioc_event अणु
	IOC_E_RESET		= 1,	/*  IOC reset request		*/
	IOC_E_ENABLE		= 2,	/*  IOC enable request		*/
	IOC_E_DISABLE		= 3,	/*  IOC disable request	*/
	IOC_E_DETACH		= 4,	/*  driver detach cleanup	*/
	IOC_E_ENABLED		= 5,	/*  f/w enabled		*/
	IOC_E_FWRSP_GETATTR	= 6,	/*  IOC get attribute response	*/
	IOC_E_DISABLED		= 7,	/*  f/w disabled		*/
	IOC_E_PFFAILED		= 8,	/*  failure notice by iocpf sm	*/
	IOC_E_HBFAIL		= 9,	/*  heartbeat failure		*/
	IOC_E_HWERROR		= 10,	/*  hardware error पूर्णांकerrupt	*/
	IOC_E_TIMEOUT		= 11,	/*  समयout			*/
	IOC_E_HWFAILED		= 12,	/*  PCI mapping failure notice	*/
पूर्ण;

bfa_fsm_state_decl(bfa_ioc, uninit, काष्ठा bfa_ioc_s, क्रमागत ioc_event);
bfa_fsm_state_decl(bfa_ioc, reset, काष्ठा bfa_ioc_s, क्रमागत ioc_event);
bfa_fsm_state_decl(bfa_ioc, enabling, काष्ठा bfa_ioc_s, क्रमागत ioc_event);
bfa_fsm_state_decl(bfa_ioc, getattr, काष्ठा bfa_ioc_s, क्रमागत ioc_event);
bfa_fsm_state_decl(bfa_ioc, op, काष्ठा bfa_ioc_s, क्रमागत ioc_event);
bfa_fsm_state_decl(bfa_ioc, fail_retry, काष्ठा bfa_ioc_s, क्रमागत ioc_event);
bfa_fsm_state_decl(bfa_ioc, fail, काष्ठा bfa_ioc_s, क्रमागत ioc_event);
bfa_fsm_state_decl(bfa_ioc, disabling, काष्ठा bfa_ioc_s, क्रमागत ioc_event);
bfa_fsm_state_decl(bfa_ioc, disabled, काष्ठा bfa_ioc_s, क्रमागत ioc_event);
bfa_fsm_state_decl(bfa_ioc, hwfail, काष्ठा bfa_ioc_s, क्रमागत ioc_event);

अटल काष्ठा bfa_sm_table_s ioc_sm_table[] = अणु
	अणुBFA_SM(bfa_ioc_sm_uninit), BFA_IOC_UNINITपूर्ण,
	अणुBFA_SM(bfa_ioc_sm_reset), BFA_IOC_RESETपूर्ण,
	अणुBFA_SM(bfa_ioc_sm_enabling), BFA_IOC_ENABLINGपूर्ण,
	अणुBFA_SM(bfa_ioc_sm_getattr), BFA_IOC_GETATTRपूर्ण,
	अणुBFA_SM(bfa_ioc_sm_op), BFA_IOC_OPERATIONALपूर्ण,
	अणुBFA_SM(bfa_ioc_sm_fail_retry), BFA_IOC_INITFAILपूर्ण,
	अणुBFA_SM(bfa_ioc_sm_fail), BFA_IOC_FAILपूर्ण,
	अणुBFA_SM(bfa_ioc_sm_disabling), BFA_IOC_DISABLINGपूर्ण,
	अणुBFA_SM(bfa_ioc_sm_disabled), BFA_IOC_DISABLEDपूर्ण,
	अणुBFA_SM(bfa_ioc_sm_hwfail), BFA_IOC_HWFAILपूर्ण,
पूर्ण;

/*
 * IOCPF state machine definitions/declarations
 */

#घोषणा bfa_iocpf_समयr_start(__ioc)					\
	bfa_समयr_begin((__ioc)->समयr_mod, &(__ioc)->ioc_समयr,	\
			bfa_iocpf_समयout, (__ioc), BFA_IOC_TOV)
#घोषणा bfa_iocpf_समयr_stop(__ioc)	bfa_समयr_stop(&(__ioc)->ioc_समयr)

#घोषणा bfa_iocpf_poll_समयr_start(__ioc)				\
	bfa_समयr_begin((__ioc)->समयr_mod, &(__ioc)->ioc_समयr,	\
			bfa_iocpf_poll_समयout, (__ioc), BFA_IOC_POLL_TOV)

#घोषणा bfa_sem_समयr_start(__ioc)					\
	bfa_समयr_begin((__ioc)->समयr_mod, &(__ioc)->sem_समयr,	\
			bfa_iocpf_sem_समयout, (__ioc), BFA_IOC_HWSEM_TOV)
#घोषणा bfa_sem_समयr_stop(__ioc)	bfa_समयr_stop(&(__ioc)->sem_समयr)

/*
 * Forward declareations क्रम iocpf state machine
 */
अटल व्योम bfa_iocpf_समयout(व्योम *ioc_arg);
अटल व्योम bfa_iocpf_sem_समयout(व्योम *ioc_arg);
अटल व्योम bfa_iocpf_poll_समयout(व्योम *ioc_arg);

/*
 * IOCPF state machine events
 */
क्रमागत iocpf_event अणु
	IOCPF_E_ENABLE		= 1,	/*  IOCPF enable request	*/
	IOCPF_E_DISABLE		= 2,	/*  IOCPF disable request	*/
	IOCPF_E_STOP		= 3,	/*  stop on driver detach	*/
	IOCPF_E_FWREADY		= 4,	/*  f/w initialization करोne	*/
	IOCPF_E_FWRSP_ENABLE	= 5,	/*  enable f/w response	*/
	IOCPF_E_FWRSP_DISABLE	= 6,	/*  disable f/w response	*/
	IOCPF_E_FAIL		= 7,	/*  failure notice by ioc sm	*/
	IOCPF_E_INITFAIL	= 8,	/*  init fail notice by ioc sm	*/
	IOCPF_E_GETATTRFAIL	= 9,	/*  init fail notice by ioc sm	*/
	IOCPF_E_SEMLOCKED	= 10,	/*  h/w semaphore is locked	*/
	IOCPF_E_TIMEOUT		= 11,	/*  f/w response समयout	*/
	IOCPF_E_SEM_ERROR	= 12,	/*  h/w sem mapping error	*/
पूर्ण;

/*
 * IOCPF states
 */
क्रमागत bfa_iocpf_state अणु
	BFA_IOCPF_RESET		= 1,	/*  IOC is in reset state */
	BFA_IOCPF_SEMWAIT	= 2,	/*  Waiting क्रम IOC h/w semaphore */
	BFA_IOCPF_HWINIT	= 3,	/*  IOC h/w is being initialized */
	BFA_IOCPF_READY		= 4,	/*  IOCPF is initialized */
	BFA_IOCPF_INITFAIL	= 5,	/*  IOCPF failed */
	BFA_IOCPF_FAIL		= 6,	/*  IOCPF failed */
	BFA_IOCPF_DISABLING	= 7,	/*  IOCPF is being disabled */
	BFA_IOCPF_DISABLED	= 8,	/*  IOCPF is disabled */
	BFA_IOCPF_FWMISMATCH	= 9,	/*  IOC f/w dअगरferent from drivers */
पूर्ण;

bfa_fsm_state_decl(bfa_iocpf, reset, काष्ठा bfa_iocpf_s, क्रमागत iocpf_event);
bfa_fsm_state_decl(bfa_iocpf, fwcheck, काष्ठा bfa_iocpf_s, क्रमागत iocpf_event);
bfa_fsm_state_decl(bfa_iocpf, mismatch, काष्ठा bfa_iocpf_s, क्रमागत iocpf_event);
bfa_fsm_state_decl(bfa_iocpf, semरुको, काष्ठा bfa_iocpf_s, क्रमागत iocpf_event);
bfa_fsm_state_decl(bfa_iocpf, hwinit, काष्ठा bfa_iocpf_s, क्रमागत iocpf_event);
bfa_fsm_state_decl(bfa_iocpf, enabling, काष्ठा bfa_iocpf_s, क्रमागत iocpf_event);
bfa_fsm_state_decl(bfa_iocpf, पढ़ोy, काष्ठा bfa_iocpf_s, क्रमागत iocpf_event);
bfa_fsm_state_decl(bfa_iocpf, initfail_sync, काष्ठा bfa_iocpf_s,
						क्रमागत iocpf_event);
bfa_fsm_state_decl(bfa_iocpf, initfail, काष्ठा bfa_iocpf_s, क्रमागत iocpf_event);
bfa_fsm_state_decl(bfa_iocpf, fail_sync, काष्ठा bfa_iocpf_s, क्रमागत iocpf_event);
bfa_fsm_state_decl(bfa_iocpf, fail, काष्ठा bfa_iocpf_s, क्रमागत iocpf_event);
bfa_fsm_state_decl(bfa_iocpf, disabling, काष्ठा bfa_iocpf_s, क्रमागत iocpf_event);
bfa_fsm_state_decl(bfa_iocpf, disabling_sync, काष्ठा bfa_iocpf_s,
						क्रमागत iocpf_event);
bfa_fsm_state_decl(bfa_iocpf, disabled, काष्ठा bfa_iocpf_s, क्रमागत iocpf_event);

अटल काष्ठा bfa_sm_table_s iocpf_sm_table[] = अणु
	अणुBFA_SM(bfa_iocpf_sm_reset), BFA_IOCPF_RESETपूर्ण,
	अणुBFA_SM(bfa_iocpf_sm_fwcheck), BFA_IOCPF_FWMISMATCHपूर्ण,
	अणुBFA_SM(bfa_iocpf_sm_mismatch), BFA_IOCPF_FWMISMATCHपूर्ण,
	अणुBFA_SM(bfa_iocpf_sm_semरुको), BFA_IOCPF_SEMWAITपूर्ण,
	अणुBFA_SM(bfa_iocpf_sm_hwinit), BFA_IOCPF_HWINITपूर्ण,
	अणुBFA_SM(bfa_iocpf_sm_enabling), BFA_IOCPF_HWINITपूर्ण,
	अणुBFA_SM(bfa_iocpf_sm_पढ़ोy), BFA_IOCPF_READYपूर्ण,
	अणुBFA_SM(bfa_iocpf_sm_initfail_sync), BFA_IOCPF_INITFAILपूर्ण,
	अणुBFA_SM(bfa_iocpf_sm_initfail), BFA_IOCPF_INITFAILपूर्ण,
	अणुBFA_SM(bfa_iocpf_sm_fail_sync), BFA_IOCPF_FAILपूर्ण,
	अणुBFA_SM(bfa_iocpf_sm_fail), BFA_IOCPF_FAILपूर्ण,
	अणुBFA_SM(bfa_iocpf_sm_disabling), BFA_IOCPF_DISABLINGपूर्ण,
	अणुBFA_SM(bfa_iocpf_sm_disabling_sync), BFA_IOCPF_DISABLINGपूर्ण,
	अणुBFA_SM(bfa_iocpf_sm_disabled), BFA_IOCPF_DISABLEDपूर्ण,
पूर्ण;

/*
 * IOC State Machine
 */

/*
 * Beginning state. IOC uninit state.
 */

अटल व्योम
bfa_ioc_sm_uninit_entry(काष्ठा bfa_ioc_s *ioc)
अणु
पूर्ण

/*
 * IOC is in uninit state.
 */
अटल व्योम
bfa_ioc_sm_uninit(काष्ठा bfa_ioc_s *ioc, क्रमागत ioc_event event)
अणु
	bfa_trc(ioc, event);

	चयन (event) अणु
	हाल IOC_E_RESET:
		bfa_fsm_set_state(ioc, bfa_ioc_sm_reset);
		अवरोध;

	शेष:
		bfa_sm_fault(ioc, event);
	पूर्ण
पूर्ण
/*
 * Reset entry actions -- initialize state machine
 */
अटल व्योम
bfa_ioc_sm_reset_entry(काष्ठा bfa_ioc_s *ioc)
अणु
	bfa_fsm_set_state(&ioc->iocpf, bfa_iocpf_sm_reset);
पूर्ण

/*
 * IOC is in reset state.
 */
अटल व्योम
bfa_ioc_sm_reset(काष्ठा bfa_ioc_s *ioc, क्रमागत ioc_event event)
अणु
	bfa_trc(ioc, event);

	चयन (event) अणु
	हाल IOC_E_ENABLE:
		bfa_fsm_set_state(ioc, bfa_ioc_sm_enabling);
		अवरोध;

	हाल IOC_E_DISABLE:
		bfa_ioc_disable_comp(ioc);
		अवरोध;

	हाल IOC_E_DETACH:
		bfa_fsm_set_state(ioc, bfa_ioc_sm_uninit);
		अवरोध;

	शेष:
		bfa_sm_fault(ioc, event);
	पूर्ण
पूर्ण


अटल व्योम
bfa_ioc_sm_enabling_entry(काष्ठा bfa_ioc_s *ioc)
अणु
	bfa_fsm_send_event(&ioc->iocpf, IOCPF_E_ENABLE);
पूर्ण

/*
 * Host IOC function is being enabled, aरुकोing response from firmware.
 * Semaphore is acquired.
 */
अटल व्योम
bfa_ioc_sm_enabling(काष्ठा bfa_ioc_s *ioc, क्रमागत ioc_event event)
अणु
	bfa_trc(ioc, event);

	चयन (event) अणु
	हाल IOC_E_ENABLED:
		bfa_fsm_set_state(ioc, bfa_ioc_sm_getattr);
		अवरोध;

	हाल IOC_E_PFFAILED:
		/* !!! fall through !!! */
	हाल IOC_E_HWERROR:
		ioc->cbfn->enable_cbfn(ioc->bfa, BFA_STATUS_IOC_FAILURE);
		bfa_fsm_set_state(ioc, bfa_ioc_sm_fail);
		अगर (event != IOC_E_PFFAILED)
			bfa_fsm_send_event(&ioc->iocpf, IOCPF_E_INITFAIL);
		अवरोध;

	हाल IOC_E_HWFAILED:
		ioc->cbfn->enable_cbfn(ioc->bfa, BFA_STATUS_IOC_FAILURE);
		bfa_fsm_set_state(ioc, bfa_ioc_sm_hwfail);
		अवरोध;

	हाल IOC_E_DISABLE:
		bfa_fsm_set_state(ioc, bfa_ioc_sm_disabling);
		अवरोध;

	हाल IOC_E_DETACH:
		bfa_fsm_set_state(ioc, bfa_ioc_sm_uninit);
		bfa_fsm_send_event(&ioc->iocpf, IOCPF_E_STOP);
		अवरोध;

	हाल IOC_E_ENABLE:
		अवरोध;

	शेष:
		bfa_sm_fault(ioc, event);
	पूर्ण
पूर्ण


अटल व्योम
bfa_ioc_sm_getattr_entry(काष्ठा bfa_ioc_s *ioc)
अणु
	bfa_ioc_समयr_start(ioc);
	bfa_ioc_send_getattr(ioc);
पूर्ण

/*
 * IOC configuration in progress. Timer is active.
 */
अटल व्योम
bfa_ioc_sm_getattr(काष्ठा bfa_ioc_s *ioc, क्रमागत ioc_event event)
अणु
	bfa_trc(ioc, event);

	चयन (event) अणु
	हाल IOC_E_FWRSP_GETATTR:
		bfa_ioc_समयr_stop(ioc);
		bfa_fsm_set_state(ioc, bfa_ioc_sm_op);
		अवरोध;

	हाल IOC_E_PFFAILED:
	हाल IOC_E_HWERROR:
		bfa_ioc_समयr_stop(ioc);
		fallthrough;
	हाल IOC_E_TIMEOUT:
		ioc->cbfn->enable_cbfn(ioc->bfa, BFA_STATUS_IOC_FAILURE);
		bfa_fsm_set_state(ioc, bfa_ioc_sm_fail);
		अगर (event != IOC_E_PFFAILED)
			bfa_fsm_send_event(&ioc->iocpf, IOCPF_E_GETATTRFAIL);
		अवरोध;

	हाल IOC_E_DISABLE:
		bfa_ioc_समयr_stop(ioc);
		bfa_fsm_set_state(ioc, bfa_ioc_sm_disabling);
		अवरोध;

	हाल IOC_E_ENABLE:
		अवरोध;

	शेष:
		bfa_sm_fault(ioc, event);
	पूर्ण
पूर्ण

अटल व्योम
bfa_ioc_sm_op_entry(काष्ठा bfa_ioc_s *ioc)
अणु
	काष्ठा bfad_s *bfad = (काष्ठा bfad_s *)ioc->bfa->bfad;

	ioc->cbfn->enable_cbfn(ioc->bfa, BFA_STATUS_OK);
	bfa_ioc_event_notअगरy(ioc, BFA_IOC_E_ENABLED);
	bfa_ioc_hb_monitor(ioc);
	BFA_LOG(KERN_INFO, bfad, bfa_log_level, "IOC enabled\n");
	bfa_ioc_aen_post(ioc, BFA_IOC_AEN_ENABLE);
पूर्ण

अटल व्योम
bfa_ioc_sm_op(काष्ठा bfa_ioc_s *ioc, क्रमागत ioc_event event)
अणु
	bfa_trc(ioc, event);

	चयन (event) अणु
	हाल IOC_E_ENABLE:
		अवरोध;

	हाल IOC_E_DISABLE:
		bfa_hb_समयr_stop(ioc);
		bfa_fsm_set_state(ioc, bfa_ioc_sm_disabling);
		अवरोध;

	हाल IOC_E_PFFAILED:
	हाल IOC_E_HWERROR:
		bfa_hb_समयr_stop(ioc);
		fallthrough;
	हाल IOC_E_HBFAIL:
		अगर (ioc->iocpf.स्वतः_recover)
			bfa_fsm_set_state(ioc, bfa_ioc_sm_fail_retry);
		अन्यथा
			bfa_fsm_set_state(ioc, bfa_ioc_sm_fail);

		bfa_ioc_fail_notअगरy(ioc);

		अगर (event != IOC_E_PFFAILED)
			bfa_fsm_send_event(&ioc->iocpf, IOCPF_E_FAIL);
		अवरोध;

	शेष:
		bfa_sm_fault(ioc, event);
	पूर्ण
पूर्ण


अटल व्योम
bfa_ioc_sm_disabling_entry(काष्ठा bfa_ioc_s *ioc)
अणु
	काष्ठा bfad_s *bfad = (काष्ठा bfad_s *)ioc->bfa->bfad;
	bfa_fsm_send_event(&ioc->iocpf, IOCPF_E_DISABLE);
	BFA_LOG(KERN_INFO, bfad, bfa_log_level, "IOC disabled\n");
	bfa_ioc_aen_post(ioc, BFA_IOC_AEN_DISABLE);
पूर्ण

/*
 * IOC is being disabled
 */
अटल व्योम
bfa_ioc_sm_disabling(काष्ठा bfa_ioc_s *ioc, क्रमागत ioc_event event)
अणु
	bfa_trc(ioc, event);

	चयन (event) अणु
	हाल IOC_E_DISABLED:
		bfa_fsm_set_state(ioc, bfa_ioc_sm_disabled);
		अवरोध;

	हाल IOC_E_HWERROR:
		/*
		 * No state change.  Will move to disabled state
		 * after iocpf sm completes failure processing and
		 * moves to disabled state.
		 */
		bfa_fsm_send_event(&ioc->iocpf, IOCPF_E_FAIL);
		अवरोध;

	हाल IOC_E_HWFAILED:
		bfa_fsm_set_state(ioc, bfa_ioc_sm_hwfail);
		bfa_ioc_disable_comp(ioc);
		अवरोध;

	शेष:
		bfa_sm_fault(ioc, event);
	पूर्ण
पूर्ण

/*
 * IOC disable completion entry.
 */
अटल व्योम
bfa_ioc_sm_disabled_entry(काष्ठा bfa_ioc_s *ioc)
अणु
	bfa_ioc_disable_comp(ioc);
पूर्ण

अटल व्योम
bfa_ioc_sm_disabled(काष्ठा bfa_ioc_s *ioc, क्रमागत ioc_event event)
अणु
	bfa_trc(ioc, event);

	चयन (event) अणु
	हाल IOC_E_ENABLE:
		bfa_fsm_set_state(ioc, bfa_ioc_sm_enabling);
		अवरोध;

	हाल IOC_E_DISABLE:
		ioc->cbfn->disable_cbfn(ioc->bfa);
		अवरोध;

	हाल IOC_E_DETACH:
		bfa_fsm_set_state(ioc, bfa_ioc_sm_uninit);
		bfa_fsm_send_event(&ioc->iocpf, IOCPF_E_STOP);
		अवरोध;

	शेष:
		bfa_sm_fault(ioc, event);
	पूर्ण
पूर्ण


अटल व्योम
bfa_ioc_sm_fail_retry_entry(काष्ठा bfa_ioc_s *ioc)
अणु
	bfa_trc(ioc, 0);
पूर्ण

/*
 * Hardware initialization retry.
 */
अटल व्योम
bfa_ioc_sm_fail_retry(काष्ठा bfa_ioc_s *ioc, क्रमागत ioc_event event)
अणु
	bfa_trc(ioc, event);

	चयन (event) अणु
	हाल IOC_E_ENABLED:
		bfa_fsm_set_state(ioc, bfa_ioc_sm_getattr);
		अवरोध;

	हाल IOC_E_PFFAILED:
	हाल IOC_E_HWERROR:
		/*
		 * Initialization retry failed.
		 */
		ioc->cbfn->enable_cbfn(ioc->bfa, BFA_STATUS_IOC_FAILURE);
		bfa_fsm_set_state(ioc, bfa_ioc_sm_fail);
		अगर (event != IOC_E_PFFAILED)
			bfa_fsm_send_event(&ioc->iocpf, IOCPF_E_INITFAIL);
		अवरोध;

	हाल IOC_E_HWFAILED:
		ioc->cbfn->enable_cbfn(ioc->bfa, BFA_STATUS_IOC_FAILURE);
		bfa_fsm_set_state(ioc, bfa_ioc_sm_hwfail);
		अवरोध;

	हाल IOC_E_ENABLE:
		अवरोध;

	हाल IOC_E_DISABLE:
		bfa_fsm_set_state(ioc, bfa_ioc_sm_disabling);
		अवरोध;

	हाल IOC_E_DETACH:
		bfa_fsm_set_state(ioc, bfa_ioc_sm_uninit);
		bfa_fsm_send_event(&ioc->iocpf, IOCPF_E_STOP);
		अवरोध;

	शेष:
		bfa_sm_fault(ioc, event);
	पूर्ण
पूर्ण


अटल व्योम
bfa_ioc_sm_fail_entry(काष्ठा bfa_ioc_s *ioc)
अणु
	bfa_trc(ioc, 0);
पूर्ण

/*
 * IOC failure.
 */
अटल व्योम
bfa_ioc_sm_fail(काष्ठा bfa_ioc_s *ioc, क्रमागत ioc_event event)
अणु
	bfa_trc(ioc, event);

	चयन (event) अणु

	हाल IOC_E_ENABLE:
		ioc->cbfn->enable_cbfn(ioc->bfa, BFA_STATUS_IOC_FAILURE);
		अवरोध;

	हाल IOC_E_DISABLE:
		bfa_fsm_set_state(ioc, bfa_ioc_sm_disabling);
		अवरोध;

	हाल IOC_E_DETACH:
		bfa_fsm_set_state(ioc, bfa_ioc_sm_uninit);
		bfa_fsm_send_event(&ioc->iocpf, IOCPF_E_STOP);
		अवरोध;

	हाल IOC_E_HWERROR:
	हाल IOC_E_HWFAILED:
		/*
		 * HB failure / HW error notअगरication, ignore.
		 */
		अवरोध;
	शेष:
		bfa_sm_fault(ioc, event);
	पूर्ण
पूर्ण

अटल व्योम
bfa_ioc_sm_hwfail_entry(काष्ठा bfa_ioc_s *ioc)
अणु
	bfa_trc(ioc, 0);
पूर्ण

अटल व्योम
bfa_ioc_sm_hwfail(काष्ठा bfa_ioc_s *ioc, क्रमागत ioc_event event)
अणु
	bfa_trc(ioc, event);

	चयन (event) अणु
	हाल IOC_E_ENABLE:
		ioc->cbfn->enable_cbfn(ioc->bfa, BFA_STATUS_IOC_FAILURE);
		अवरोध;

	हाल IOC_E_DISABLE:
		ioc->cbfn->disable_cbfn(ioc->bfa);
		अवरोध;

	हाल IOC_E_DETACH:
		bfa_fsm_set_state(ioc, bfa_ioc_sm_uninit);
		अवरोध;

	हाल IOC_E_HWERROR:
		/* Ignore - alपढ़ोy in hwfail state */
		अवरोध;

	शेष:
		bfa_sm_fault(ioc, event);
	पूर्ण
पूर्ण

/*
 * IOCPF State Machine
 */

/*
 * Reset entry actions -- initialize state machine
 */
अटल व्योम
bfa_iocpf_sm_reset_entry(काष्ठा bfa_iocpf_s *iocpf)
अणु
	iocpf->fw_mismatch_notअगरied = BFA_FALSE;
	iocpf->स्वतः_recover = bfa_स्वतः_recover;
पूर्ण

/*
 * Beginning state. IOC is in reset state.
 */
अटल व्योम
bfa_iocpf_sm_reset(काष्ठा bfa_iocpf_s *iocpf, क्रमागत iocpf_event event)
अणु
	काष्ठा bfa_ioc_s *ioc = iocpf->ioc;

	bfa_trc(ioc, event);

	चयन (event) अणु
	हाल IOCPF_E_ENABLE:
		bfa_fsm_set_state(iocpf, bfa_iocpf_sm_fwcheck);
		अवरोध;

	हाल IOCPF_E_STOP:
		अवरोध;

	शेष:
		bfa_sm_fault(ioc, event);
	पूर्ण
पूर्ण

/*
 * Semaphore should be acquired क्रम version check.
 */
अटल व्योम
bfa_iocpf_sm_fwcheck_entry(काष्ठा bfa_iocpf_s *iocpf)
अणु
	काष्ठा bfi_ioc_image_hdr_s	fwhdr;
	u32	r32, fwstate, pgnum, loff = 0;
	पूर्णांक	i;

	/*
	 * Spin on init semaphore to serialize.
	 */
	r32 = पढ़ोl(iocpf->ioc->ioc_regs.ioc_init_sem_reg);
	जबतक (r32 & 0x1) अणु
		udelay(20);
		r32 = पढ़ोl(iocpf->ioc->ioc_regs.ioc_init_sem_reg);
	पूर्ण

	/* h/w sem init */
	fwstate = bfa_ioc_get_cur_ioc_fwstate(iocpf->ioc);
	अगर (fwstate == BFI_IOC_UNINIT) अणु
		ग_लिखोl(1, iocpf->ioc->ioc_regs.ioc_init_sem_reg);
		जाओ sem_get;
	पूर्ण

	bfa_ioc_fwver_get(iocpf->ioc, &fwhdr);

	अगर (swab32(fwhdr.exec) == BFI_FWBOOT_TYPE_NORMAL) अणु
		ग_लिखोl(1, iocpf->ioc->ioc_regs.ioc_init_sem_reg);
		जाओ sem_get;
	पूर्ण

	/*
	 * Clear fwver hdr
	 */
	pgnum = PSS_SMEM_PGNUM(iocpf->ioc->ioc_regs.smem_pg0, loff);
	ग_लिखोl(pgnum, iocpf->ioc->ioc_regs.host_page_num_fn);

	क्रम (i = 0; i < माप(काष्ठा bfi_ioc_image_hdr_s) / माप(u32); i++) अणु
		bfa_mem_ग_लिखो(iocpf->ioc->ioc_regs.smem_page_start, loff, 0);
		loff += माप(u32);
	पूर्ण

	bfa_trc(iocpf->ioc, fwstate);
	bfa_trc(iocpf->ioc, swab32(fwhdr.exec));
	bfa_ioc_set_cur_ioc_fwstate(iocpf->ioc, BFI_IOC_UNINIT);
	bfa_ioc_set_alt_ioc_fwstate(iocpf->ioc, BFI_IOC_UNINIT);

	/*
	 * Unlock the hw semaphore. Should be here only once per boot.
	 */
	bfa_ioc_ownership_reset(iocpf->ioc);

	/*
	 * unlock init semaphore.
	 */
	ग_लिखोl(1, iocpf->ioc->ioc_regs.ioc_init_sem_reg);

sem_get:
	bfa_ioc_hw_sem_get(iocpf->ioc);
पूर्ण

/*
 * Aरुकोing h/w semaphore to जारी with version check.
 */
अटल व्योम
bfa_iocpf_sm_fwcheck(काष्ठा bfa_iocpf_s *iocpf, क्रमागत iocpf_event event)
अणु
	काष्ठा bfa_ioc_s *ioc = iocpf->ioc;

	bfa_trc(ioc, event);

	चयन (event) अणु
	हाल IOCPF_E_SEMLOCKED:
		अगर (bfa_ioc_firmware_lock(ioc)) अणु
			अगर (bfa_ioc_sync_start(ioc)) अणु
				bfa_ioc_sync_join(ioc);
				bfa_fsm_set_state(iocpf, bfa_iocpf_sm_hwinit);
			पूर्ण अन्यथा अणु
				bfa_ioc_firmware_unlock(ioc);
				ग_लिखोl(1, ioc->ioc_regs.ioc_sem_reg);
				bfa_sem_समयr_start(ioc);
			पूर्ण
		पूर्ण अन्यथा अणु
			ग_लिखोl(1, ioc->ioc_regs.ioc_sem_reg);
			bfa_fsm_set_state(iocpf, bfa_iocpf_sm_mismatch);
		पूर्ण
		अवरोध;

	हाल IOCPF_E_SEM_ERROR:
		bfa_fsm_set_state(iocpf, bfa_iocpf_sm_fail);
		bfa_fsm_send_event(ioc, IOC_E_HWFAILED);
		अवरोध;

	हाल IOCPF_E_DISABLE:
		bfa_sem_समयr_stop(ioc);
		bfa_fsm_set_state(iocpf, bfa_iocpf_sm_reset);
		bfa_fsm_send_event(ioc, IOC_E_DISABLED);
		अवरोध;

	हाल IOCPF_E_STOP:
		bfa_sem_समयr_stop(ioc);
		bfa_fsm_set_state(iocpf, bfa_iocpf_sm_reset);
		अवरोध;

	शेष:
		bfa_sm_fault(ioc, event);
	पूर्ण
पूर्ण

/*
 * Notअगरy enable completion callback.
 */
अटल व्योम
bfa_iocpf_sm_mismatch_entry(काष्ठा bfa_iocpf_s *iocpf)
अणु
	/*
	 * Call only the first समय sm enters fwmismatch state.
	 */
	अगर (iocpf->fw_mismatch_notअगरied == BFA_FALSE)
		bfa_ioc_pf_fwmismatch(iocpf->ioc);

	iocpf->fw_mismatch_notअगरied = BFA_TRUE;
	bfa_iocpf_समयr_start(iocpf->ioc);
पूर्ण

/*
 * Aरुकोing firmware version match.
 */
अटल व्योम
bfa_iocpf_sm_mismatch(काष्ठा bfa_iocpf_s *iocpf, क्रमागत iocpf_event event)
अणु
	काष्ठा bfa_ioc_s *ioc = iocpf->ioc;

	bfa_trc(ioc, event);

	चयन (event) अणु
	हाल IOCPF_E_TIMEOUT:
		bfa_fsm_set_state(iocpf, bfa_iocpf_sm_fwcheck);
		अवरोध;

	हाल IOCPF_E_DISABLE:
		bfa_iocpf_समयr_stop(ioc);
		bfa_fsm_set_state(iocpf, bfa_iocpf_sm_reset);
		bfa_fsm_send_event(ioc, IOC_E_DISABLED);
		अवरोध;

	हाल IOCPF_E_STOP:
		bfa_iocpf_समयr_stop(ioc);
		bfa_fsm_set_state(iocpf, bfa_iocpf_sm_reset);
		अवरोध;

	शेष:
		bfa_sm_fault(ioc, event);
	पूर्ण
पूर्ण

/*
 * Request क्रम semaphore.
 */
अटल व्योम
bfa_iocpf_sm_semरुको_entry(काष्ठा bfa_iocpf_s *iocpf)
अणु
	bfa_ioc_hw_sem_get(iocpf->ioc);
पूर्ण

/*
 * Aरुकोing semaphore क्रम h/w initialzation.
 */
अटल व्योम
bfa_iocpf_sm_semरुको(काष्ठा bfa_iocpf_s *iocpf, क्रमागत iocpf_event event)
अणु
	काष्ठा bfa_ioc_s *ioc = iocpf->ioc;

	bfa_trc(ioc, event);

	चयन (event) अणु
	हाल IOCPF_E_SEMLOCKED:
		अगर (bfa_ioc_sync_complete(ioc)) अणु
			bfa_ioc_sync_join(ioc);
			bfa_fsm_set_state(iocpf, bfa_iocpf_sm_hwinit);
		पूर्ण अन्यथा अणु
			ग_लिखोl(1, ioc->ioc_regs.ioc_sem_reg);
			bfa_sem_समयr_start(ioc);
		पूर्ण
		अवरोध;

	हाल IOCPF_E_SEM_ERROR:
		bfa_fsm_set_state(iocpf, bfa_iocpf_sm_fail);
		bfa_fsm_send_event(ioc, IOC_E_HWFAILED);
		अवरोध;

	हाल IOCPF_E_DISABLE:
		bfa_sem_समयr_stop(ioc);
		bfa_fsm_set_state(iocpf, bfa_iocpf_sm_disabling_sync);
		अवरोध;

	शेष:
		bfa_sm_fault(ioc, event);
	पूर्ण
पूर्ण

अटल व्योम
bfa_iocpf_sm_hwinit_entry(काष्ठा bfa_iocpf_s *iocpf)
अणु
	iocpf->poll_समय = 0;
	bfa_ioc_hwinit(iocpf->ioc, BFA_FALSE);
पूर्ण

/*
 * Hardware is being initialized. Interrupts are enabled.
 * Holding hardware semaphore lock.
 */
अटल व्योम
bfa_iocpf_sm_hwinit(काष्ठा bfa_iocpf_s *iocpf, क्रमागत iocpf_event event)
अणु
	काष्ठा bfa_ioc_s *ioc = iocpf->ioc;

	bfa_trc(ioc, event);

	चयन (event) अणु
	हाल IOCPF_E_FWREADY:
		bfa_fsm_set_state(iocpf, bfa_iocpf_sm_enabling);
		अवरोध;

	हाल IOCPF_E_TIMEOUT:
		ग_लिखोl(1, ioc->ioc_regs.ioc_sem_reg);
		bfa_fsm_send_event(ioc, IOC_E_PFFAILED);
		bfa_fsm_set_state(iocpf, bfa_iocpf_sm_initfail_sync);
		अवरोध;

	हाल IOCPF_E_DISABLE:
		bfa_iocpf_समयr_stop(ioc);
		bfa_ioc_sync_leave(ioc);
		ग_लिखोl(1, ioc->ioc_regs.ioc_sem_reg);
		bfa_fsm_set_state(iocpf, bfa_iocpf_sm_disabled);
		अवरोध;

	शेष:
		bfa_sm_fault(ioc, event);
	पूर्ण
पूर्ण

अटल व्योम
bfa_iocpf_sm_enabling_entry(काष्ठा bfa_iocpf_s *iocpf)
अणु
	bfa_iocpf_समयr_start(iocpf->ioc);
	/*
	 * Enable Interrupts beक्रमe sending fw IOC ENABLE cmd.
	 */
	iocpf->ioc->cbfn->reset_cbfn(iocpf->ioc->bfa);
	bfa_ioc_send_enable(iocpf->ioc);
पूर्ण

/*
 * Host IOC function is being enabled, aरुकोing response from firmware.
 * Semaphore is acquired.
 */
अटल व्योम
bfa_iocpf_sm_enabling(काष्ठा bfa_iocpf_s *iocpf, क्रमागत iocpf_event event)
अणु
	काष्ठा bfa_ioc_s *ioc = iocpf->ioc;

	bfa_trc(ioc, event);

	चयन (event) अणु
	हाल IOCPF_E_FWRSP_ENABLE:
		bfa_iocpf_समयr_stop(ioc);
		ग_लिखोl(1, ioc->ioc_regs.ioc_sem_reg);
		bfa_fsm_set_state(iocpf, bfa_iocpf_sm_पढ़ोy);
		अवरोध;

	हाल IOCPF_E_INITFAIL:
		bfa_iocpf_समयr_stop(ioc);
		fallthrough;

	हाल IOCPF_E_TIMEOUT:
		ग_लिखोl(1, ioc->ioc_regs.ioc_sem_reg);
		अगर (event == IOCPF_E_TIMEOUT)
			bfa_fsm_send_event(ioc, IOC_E_PFFAILED);
		bfa_fsm_set_state(iocpf, bfa_iocpf_sm_initfail_sync);
		अवरोध;

	हाल IOCPF_E_DISABLE:
		bfa_iocpf_समयr_stop(ioc);
		ग_लिखोl(1, ioc->ioc_regs.ioc_sem_reg);
		bfa_fsm_set_state(iocpf, bfa_iocpf_sm_disabling);
		अवरोध;

	शेष:
		bfa_sm_fault(ioc, event);
	पूर्ण
पूर्ण

अटल व्योम
bfa_iocpf_sm_पढ़ोy_entry(काष्ठा bfa_iocpf_s *iocpf)
अणु
	bfa_fsm_send_event(iocpf->ioc, IOC_E_ENABLED);
पूर्ण

अटल व्योम
bfa_iocpf_sm_पढ़ोy(काष्ठा bfa_iocpf_s *iocpf, क्रमागत iocpf_event event)
अणु
	काष्ठा bfa_ioc_s *ioc = iocpf->ioc;

	bfa_trc(ioc, event);

	चयन (event) अणु
	हाल IOCPF_E_DISABLE:
		bfa_fsm_set_state(iocpf, bfa_iocpf_sm_disabling);
		अवरोध;

	हाल IOCPF_E_GETATTRFAIL:
		bfa_fsm_set_state(iocpf, bfa_iocpf_sm_initfail_sync);
		अवरोध;

	हाल IOCPF_E_FAIL:
		bfa_fsm_set_state(iocpf, bfa_iocpf_sm_fail_sync);
		अवरोध;

	शेष:
		bfa_sm_fault(ioc, event);
	पूर्ण
पूर्ण

अटल व्योम
bfa_iocpf_sm_disabling_entry(काष्ठा bfa_iocpf_s *iocpf)
अणु
	bfa_iocpf_समयr_start(iocpf->ioc);
	bfa_ioc_send_disable(iocpf->ioc);
पूर्ण

/*
 * IOC is being disabled
 */
अटल व्योम
bfa_iocpf_sm_disabling(काष्ठा bfa_iocpf_s *iocpf, क्रमागत iocpf_event event)
अणु
	काष्ठा bfa_ioc_s *ioc = iocpf->ioc;

	bfa_trc(ioc, event);

	चयन (event) अणु
	हाल IOCPF_E_FWRSP_DISABLE:
		bfa_iocpf_समयr_stop(ioc);
		bfa_fsm_set_state(iocpf, bfa_iocpf_sm_disabling_sync);
		अवरोध;

	हाल IOCPF_E_FAIL:
		bfa_iocpf_समयr_stop(ioc);
		fallthrough;

	हाल IOCPF_E_TIMEOUT:
		bfa_ioc_set_cur_ioc_fwstate(ioc, BFI_IOC_FAIL);
		bfa_fsm_set_state(iocpf, bfa_iocpf_sm_disabling_sync);
		अवरोध;

	हाल IOCPF_E_FWRSP_ENABLE:
		अवरोध;

	शेष:
		bfa_sm_fault(ioc, event);
	पूर्ण
पूर्ण

अटल व्योम
bfa_iocpf_sm_disabling_sync_entry(काष्ठा bfa_iocpf_s *iocpf)
अणु
	bfa_ioc_hw_sem_get(iocpf->ioc);
पूर्ण

/*
 * IOC hb ack request is being हटाओd.
 */
अटल व्योम
bfa_iocpf_sm_disabling_sync(काष्ठा bfa_iocpf_s *iocpf, क्रमागत iocpf_event event)
अणु
	काष्ठा bfa_ioc_s *ioc = iocpf->ioc;

	bfa_trc(ioc, event);

	चयन (event) अणु
	हाल IOCPF_E_SEMLOCKED:
		bfa_ioc_sync_leave(ioc);
		ग_लिखोl(1, ioc->ioc_regs.ioc_sem_reg);
		bfa_fsm_set_state(iocpf, bfa_iocpf_sm_disabled);
		अवरोध;

	हाल IOCPF_E_SEM_ERROR:
		bfa_fsm_set_state(iocpf, bfa_iocpf_sm_fail);
		bfa_fsm_send_event(ioc, IOC_E_HWFAILED);
		अवरोध;

	हाल IOCPF_E_FAIL:
		अवरोध;

	शेष:
		bfa_sm_fault(ioc, event);
	पूर्ण
पूर्ण

/*
 * IOC disable completion entry.
 */
अटल व्योम
bfa_iocpf_sm_disabled_entry(काष्ठा bfa_iocpf_s *iocpf)
अणु
	bfa_ioc_mbox_flush(iocpf->ioc);
	bfa_fsm_send_event(iocpf->ioc, IOC_E_DISABLED);
पूर्ण

अटल व्योम
bfa_iocpf_sm_disabled(काष्ठा bfa_iocpf_s *iocpf, क्रमागत iocpf_event event)
अणु
	काष्ठा bfa_ioc_s *ioc = iocpf->ioc;

	bfa_trc(ioc, event);

	चयन (event) अणु
	हाल IOCPF_E_ENABLE:
		bfa_fsm_set_state(iocpf, bfa_iocpf_sm_semरुको);
		अवरोध;

	हाल IOCPF_E_STOP:
		bfa_ioc_firmware_unlock(ioc);
		bfa_fsm_set_state(iocpf, bfa_iocpf_sm_reset);
		अवरोध;

	शेष:
		bfa_sm_fault(ioc, event);
	पूर्ण
पूर्ण

अटल व्योम
bfa_iocpf_sm_initfail_sync_entry(काष्ठा bfa_iocpf_s *iocpf)
अणु
	bfa_ioc_debug_save_ftrc(iocpf->ioc);
	bfa_ioc_hw_sem_get(iocpf->ioc);
पूर्ण

/*
 * Hardware initialization failed.
 */
अटल व्योम
bfa_iocpf_sm_initfail_sync(काष्ठा bfa_iocpf_s *iocpf, क्रमागत iocpf_event event)
अणु
	काष्ठा bfa_ioc_s *ioc = iocpf->ioc;

	bfa_trc(ioc, event);

	चयन (event) अणु
	हाल IOCPF_E_SEMLOCKED:
		bfa_ioc_notअगरy_fail(ioc);
		bfa_ioc_sync_leave(ioc);
		bfa_ioc_set_cur_ioc_fwstate(ioc, BFI_IOC_FAIL);
		ग_लिखोl(1, ioc->ioc_regs.ioc_sem_reg);
		bfa_fsm_set_state(iocpf, bfa_iocpf_sm_initfail);
		अवरोध;

	हाल IOCPF_E_SEM_ERROR:
		bfa_fsm_set_state(iocpf, bfa_iocpf_sm_fail);
		bfa_fsm_send_event(ioc, IOC_E_HWFAILED);
		अवरोध;

	हाल IOCPF_E_DISABLE:
		bfa_sem_समयr_stop(ioc);
		bfa_fsm_set_state(iocpf, bfa_iocpf_sm_disabling_sync);
		अवरोध;

	हाल IOCPF_E_STOP:
		bfa_sem_समयr_stop(ioc);
		bfa_ioc_firmware_unlock(ioc);
		bfa_fsm_set_state(iocpf, bfa_iocpf_sm_reset);
		अवरोध;

	हाल IOCPF_E_FAIL:
		अवरोध;

	शेष:
		bfa_sm_fault(ioc, event);
	पूर्ण
पूर्ण

अटल व्योम
bfa_iocpf_sm_initfail_entry(काष्ठा bfa_iocpf_s *iocpf)
अणु
	bfa_trc(iocpf->ioc, 0);
पूर्ण

/*
 * Hardware initialization failed.
 */
अटल व्योम
bfa_iocpf_sm_initfail(काष्ठा bfa_iocpf_s *iocpf, क्रमागत iocpf_event event)
अणु
	काष्ठा bfa_ioc_s *ioc = iocpf->ioc;

	bfa_trc(ioc, event);

	चयन (event) अणु
	हाल IOCPF_E_DISABLE:
		bfa_fsm_set_state(iocpf, bfa_iocpf_sm_disabled);
		अवरोध;

	हाल IOCPF_E_STOP:
		bfa_ioc_firmware_unlock(ioc);
		bfa_fsm_set_state(iocpf, bfa_iocpf_sm_reset);
		अवरोध;

	शेष:
		bfa_sm_fault(ioc, event);
	पूर्ण
पूर्ण

अटल व्योम
bfa_iocpf_sm_fail_sync_entry(काष्ठा bfa_iocpf_s *iocpf)
अणु
	/*
	 * Mark IOC as failed in hardware and stop firmware.
	 */
	bfa_ioc_lpu_stop(iocpf->ioc);

	/*
	 * Flush any queued up mailbox requests.
	 */
	bfa_ioc_mbox_flush(iocpf->ioc);

	bfa_ioc_hw_sem_get(iocpf->ioc);
पूर्ण

अटल व्योम
bfa_iocpf_sm_fail_sync(काष्ठा bfa_iocpf_s *iocpf, क्रमागत iocpf_event event)
अणु
	काष्ठा bfa_ioc_s *ioc = iocpf->ioc;

	bfa_trc(ioc, event);

	चयन (event) अणु
	हाल IOCPF_E_SEMLOCKED:
		bfa_ioc_sync_ack(ioc);
		bfa_ioc_notअगरy_fail(ioc);
		अगर (!iocpf->स्वतः_recover) अणु
			bfa_ioc_sync_leave(ioc);
			bfa_ioc_set_cur_ioc_fwstate(ioc, BFI_IOC_FAIL);
			ग_लिखोl(1, ioc->ioc_regs.ioc_sem_reg);
			bfa_fsm_set_state(iocpf, bfa_iocpf_sm_fail);
		पूर्ण अन्यथा अणु
			अगर (bfa_ioc_sync_complete(ioc))
				bfa_fsm_set_state(iocpf, bfa_iocpf_sm_hwinit);
			अन्यथा अणु
				ग_लिखोl(1, ioc->ioc_regs.ioc_sem_reg);
				bfa_fsm_set_state(iocpf, bfa_iocpf_sm_semरुको);
			पूर्ण
		पूर्ण
		अवरोध;

	हाल IOCPF_E_SEM_ERROR:
		bfa_fsm_set_state(iocpf, bfa_iocpf_sm_fail);
		bfa_fsm_send_event(ioc, IOC_E_HWFAILED);
		अवरोध;

	हाल IOCPF_E_DISABLE:
		bfa_sem_समयr_stop(ioc);
		bfa_fsm_set_state(iocpf, bfa_iocpf_sm_disabling_sync);
		अवरोध;

	हाल IOCPF_E_FAIL:
		अवरोध;

	शेष:
		bfa_sm_fault(ioc, event);
	पूर्ण
पूर्ण

अटल व्योम
bfa_iocpf_sm_fail_entry(काष्ठा bfa_iocpf_s *iocpf)
अणु
	bfa_trc(iocpf->ioc, 0);
पूर्ण

/*
 * IOC is in failed state.
 */
अटल व्योम
bfa_iocpf_sm_fail(काष्ठा bfa_iocpf_s *iocpf, क्रमागत iocpf_event event)
अणु
	काष्ठा bfa_ioc_s *ioc = iocpf->ioc;

	bfa_trc(ioc, event);

	चयन (event) अणु
	हाल IOCPF_E_DISABLE:
		bfa_fsm_set_state(iocpf, bfa_iocpf_sm_disabled);
		अवरोध;

	शेष:
		bfa_sm_fault(ioc, event);
	पूर्ण
पूर्ण

/*
 *  BFA IOC निजी functions
 */

/*
 * Notअगरy common modules रेजिस्टरed क्रम notअगरication.
 */
अटल व्योम
bfa_ioc_event_notअगरy(काष्ठा bfa_ioc_s *ioc, क्रमागत bfa_ioc_event_e event)
अणु
	काष्ठा bfa_ioc_notअगरy_s	*notअगरy;
	काष्ठा list_head	*qe;

	list_क्रम_each(qe, &ioc->notअगरy_q) अणु
		notअगरy = (काष्ठा bfa_ioc_notअगरy_s *)qe;
		notअगरy->cbfn(notअगरy->cbarg, event);
	पूर्ण
पूर्ण

अटल व्योम
bfa_ioc_disable_comp(काष्ठा bfa_ioc_s *ioc)
अणु
	ioc->cbfn->disable_cbfn(ioc->bfa);
	bfa_ioc_event_notअगरy(ioc, BFA_IOC_E_DISABLED);
पूर्ण

bfa_boolean_t
bfa_ioc_sem_get(व्योम __iomem *sem_reg)
अणु
	u32 r32;
	पूर्णांक cnt = 0;
#घोषणा BFA_SEM_SPINCNT	3000

	r32 = पढ़ोl(sem_reg);

	जबतक ((r32 & 1) && (cnt < BFA_SEM_SPINCNT)) अणु
		cnt++;
		udelay(2);
		r32 = पढ़ोl(sem_reg);
	पूर्ण

	अगर (!(r32 & 1))
		वापस BFA_TRUE;

	वापस BFA_FALSE;
पूर्ण

अटल व्योम
bfa_ioc_hw_sem_get(काष्ठा bfa_ioc_s *ioc)
अणु
	u32	r32;

	/*
	 * First पढ़ो to the semaphore रेजिस्टर will वापस 0, subsequent पढ़ोs
	 * will वापस 1. Semaphore is released by writing 1 to the रेजिस्टर
	 */
	r32 = पढ़ोl(ioc->ioc_regs.ioc_sem_reg);
	अगर (r32 == ~0) अणु
		WARN_ON(r32 == ~0);
		bfa_fsm_send_event(&ioc->iocpf, IOCPF_E_SEM_ERROR);
		वापस;
	पूर्ण
	अगर (!(r32 & 1)) अणु
		bfa_fsm_send_event(&ioc->iocpf, IOCPF_E_SEMLOCKED);
		वापस;
	पूर्ण

	bfa_sem_समयr_start(ioc);
पूर्ण

/*
 * Initialize LPU local memory (aka secondary memory / SRAM)
 */
अटल व्योम
bfa_ioc_lmem_init(काष्ठा bfa_ioc_s *ioc)
अणु
	u32	pss_ctl;
	पूर्णांक		i;
#घोषणा PSS_LMEM_INIT_TIME  10000

	pss_ctl = पढ़ोl(ioc->ioc_regs.pss_ctl_reg);
	pss_ctl &= ~__PSS_LMEM_RESET;
	pss_ctl |= __PSS_LMEM_INIT_EN;

	/*
	 * i2c workaround 12.5khz घड़ी
	 */
	pss_ctl |= __PSS_I2C_CLK_DIV(3UL);
	ग_लिखोl(pss_ctl, ioc->ioc_regs.pss_ctl_reg);

	/*
	 * रुको क्रम memory initialization to be complete
	 */
	i = 0;
	करो अणु
		pss_ctl = पढ़ोl(ioc->ioc_regs.pss_ctl_reg);
		i++;
	पूर्ण जबतक (!(pss_ctl & __PSS_LMEM_INIT_DONE) && (i < PSS_LMEM_INIT_TIME));

	/*
	 * If memory initialization is not successful, IOC समयout will catch
	 * such failures.
	 */
	WARN_ON(!(pss_ctl & __PSS_LMEM_INIT_DONE));
	bfa_trc(ioc, pss_ctl);

	pss_ctl &= ~(__PSS_LMEM_INIT_DONE | __PSS_LMEM_INIT_EN);
	ग_लिखोl(pss_ctl, ioc->ioc_regs.pss_ctl_reg);
पूर्ण

अटल व्योम
bfa_ioc_lpu_start(काष्ठा bfa_ioc_s *ioc)
अणु
	u32	pss_ctl;

	/*
	 * Take processor out of reset.
	 */
	pss_ctl = पढ़ोl(ioc->ioc_regs.pss_ctl_reg);
	pss_ctl &= ~__PSS_LPU0_RESET;

	ग_लिखोl(pss_ctl, ioc->ioc_regs.pss_ctl_reg);
पूर्ण

अटल व्योम
bfa_ioc_lpu_stop(काष्ठा bfa_ioc_s *ioc)
अणु
	u32	pss_ctl;

	/*
	 * Put processors in reset.
	 */
	pss_ctl = पढ़ोl(ioc->ioc_regs.pss_ctl_reg);
	pss_ctl |= (__PSS_LPU0_RESET | __PSS_LPU1_RESET);

	ग_लिखोl(pss_ctl, ioc->ioc_regs.pss_ctl_reg);
पूर्ण

/*
 * Get driver and firmware versions.
 */
व्योम
bfa_ioc_fwver_get(काष्ठा bfa_ioc_s *ioc, काष्ठा bfi_ioc_image_hdr_s *fwhdr)
अणु
	u32	pgnum;
	u32	loff = 0;
	पूर्णांक		i;
	u32	*fwsig = (u32 *) fwhdr;

	pgnum = PSS_SMEM_PGNUM(ioc->ioc_regs.smem_pg0, loff);
	ग_लिखोl(pgnum, ioc->ioc_regs.host_page_num_fn);

	क्रम (i = 0; i < (माप(काष्ठा bfi_ioc_image_hdr_s) / माप(u32));
	     i++) अणु
		fwsig[i] =
			bfa_mem_पढ़ो(ioc->ioc_regs.smem_page_start, loff);
		loff += माप(u32);
	पूर्ण
पूर्ण

/*
 * Returns TRUE अगर driver is willing to work with current smem f/w version.
 */
bfa_boolean_t
bfa_ioc_fwver_cmp(काष्ठा bfa_ioc_s *ioc,
		काष्ठा bfi_ioc_image_hdr_s *smem_fwhdr)
अणु
	काष्ठा bfi_ioc_image_hdr_s *drv_fwhdr;
	क्रमागत bfi_ioc_img_ver_cmp_e smem_flash_cmp, drv_smem_cmp;

	drv_fwhdr = (काष्ठा bfi_ioc_image_hdr_s *)
		bfa_cb_image_get_chunk(bfa_ioc_asic_gen(ioc), 0);

	/*
	 * If smem is incompatible or old, driver should not work with it.
	 */
	drv_smem_cmp = bfa_ioc_fw_ver_patch_cmp(drv_fwhdr, smem_fwhdr);
	अगर (drv_smem_cmp == BFI_IOC_IMG_VER_INCOMP ||
		drv_smem_cmp == BFI_IOC_IMG_VER_OLD) अणु
		वापस BFA_FALSE;
	पूर्ण

	/*
	 * IF Flash has a better F/W than smem करो not work with smem.
	 * If smem f/w == flash f/w, as smem f/w not old | incmp, work with it.
	 * If Flash is old or incomp work with smem अगरf smem f/w == drv f/w.
	 */
	smem_flash_cmp = bfa_ioc_flash_fwver_cmp(ioc, smem_fwhdr);

	अगर (smem_flash_cmp == BFI_IOC_IMG_VER_BETTER) अणु
		वापस BFA_FALSE;
	पूर्ण अन्यथा अगर (smem_flash_cmp == BFI_IOC_IMG_VER_SAME) अणु
		वापस BFA_TRUE;
	पूर्ण अन्यथा अणु
		वापस (drv_smem_cmp == BFI_IOC_IMG_VER_SAME) ?
			BFA_TRUE : BFA_FALSE;
	पूर्ण
पूर्ण

/*
 * Return true अगर current running version is valid. Firmware signature and
 * execution context (driver/bios) must match.
 */
अटल bfa_boolean_t
bfa_ioc_fwver_valid(काष्ठा bfa_ioc_s *ioc, u32 boot_env)
अणु
	काष्ठा bfi_ioc_image_hdr_s fwhdr;

	bfa_ioc_fwver_get(ioc, &fwhdr);

	अगर (swab32(fwhdr.bootenv) != boot_env) अणु
		bfa_trc(ioc, fwhdr.bootenv);
		bfa_trc(ioc, boot_env);
		वापस BFA_FALSE;
	पूर्ण

	वापस bfa_ioc_fwver_cmp(ioc, &fwhdr);
पूर्ण

अटल bfa_boolean_t
bfa_ioc_fwver_md5_check(काष्ठा bfi_ioc_image_hdr_s *fwhdr_1,
				काष्ठा bfi_ioc_image_hdr_s *fwhdr_2)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < BFI_IOC_MD5SUM_SZ; i++)
		अगर (fwhdr_1->md5sum[i] != fwhdr_2->md5sum[i])
			वापस BFA_FALSE;

	वापस BFA_TRUE;
पूर्ण

/*
 * Returns TRUE अगर major minor and मुख्यtainence are same.
 * If patch versions are same, check क्रम MD5 Checksum to be same.
 */
अटल bfa_boolean_t
bfa_ioc_fw_ver_compatible(काष्ठा bfi_ioc_image_hdr_s *drv_fwhdr,
				काष्ठा bfi_ioc_image_hdr_s *fwhdr_to_cmp)
अणु
	अगर (drv_fwhdr->signature != fwhdr_to_cmp->signature)
		वापस BFA_FALSE;

	अगर (drv_fwhdr->fwver.major != fwhdr_to_cmp->fwver.major)
		वापस BFA_FALSE;

	अगर (drv_fwhdr->fwver.minor != fwhdr_to_cmp->fwver.minor)
		वापस BFA_FALSE;

	अगर (drv_fwhdr->fwver.मुख्यt != fwhdr_to_cmp->fwver.मुख्यt)
		वापस BFA_FALSE;

	अगर (drv_fwhdr->fwver.patch == fwhdr_to_cmp->fwver.patch &&
		drv_fwhdr->fwver.phase == fwhdr_to_cmp->fwver.phase &&
		drv_fwhdr->fwver.build == fwhdr_to_cmp->fwver.build) अणु
		वापस bfa_ioc_fwver_md5_check(drv_fwhdr, fwhdr_to_cmp);
	पूर्ण

	वापस BFA_TRUE;
पूर्ण

अटल bfa_boolean_t
bfa_ioc_flash_fwver_valid(काष्ठा bfi_ioc_image_hdr_s *flash_fwhdr)
अणु
	अगर (flash_fwhdr->fwver.major == 0 || flash_fwhdr->fwver.major == 0xFF)
		वापस BFA_FALSE;

	वापस BFA_TRUE;
पूर्ण

अटल bfa_boolean_t fwhdr_is_ga(काष्ठा bfi_ioc_image_hdr_s *fwhdr)
अणु
	अगर (fwhdr->fwver.phase == 0 &&
		fwhdr->fwver.build == 0)
		वापस BFA_TRUE;

	वापस BFA_FALSE;
पूर्ण

/*
 * Returns TRUE अगर both are compatible and patch of fwhdr_to_cmp is better.
 */
अटल क्रमागत bfi_ioc_img_ver_cmp_e
bfa_ioc_fw_ver_patch_cmp(काष्ठा bfi_ioc_image_hdr_s *base_fwhdr,
				काष्ठा bfi_ioc_image_hdr_s *fwhdr_to_cmp)
अणु
	अगर (bfa_ioc_fw_ver_compatible(base_fwhdr, fwhdr_to_cmp) == BFA_FALSE)
		वापस BFI_IOC_IMG_VER_INCOMP;

	अगर (fwhdr_to_cmp->fwver.patch > base_fwhdr->fwver.patch)
		वापस BFI_IOC_IMG_VER_BETTER;

	अन्यथा अगर (fwhdr_to_cmp->fwver.patch < base_fwhdr->fwver.patch)
		वापस BFI_IOC_IMG_VER_OLD;

	/*
	 * GA takes priority over पूर्णांकernal builds of the same patch stream.
	 * At this poपूर्णांक major minor मुख्यt and patch numbers are same.
	 */

	अगर (fwhdr_is_ga(base_fwhdr) == BFA_TRUE) अणु
		अगर (fwhdr_is_ga(fwhdr_to_cmp))
			वापस BFI_IOC_IMG_VER_SAME;
		अन्यथा
			वापस BFI_IOC_IMG_VER_OLD;
	पूर्ण अन्यथा अणु
		अगर (fwhdr_is_ga(fwhdr_to_cmp))
			वापस BFI_IOC_IMG_VER_BETTER;
	पूर्ण

	अगर (fwhdr_to_cmp->fwver.phase > base_fwhdr->fwver.phase)
		वापस BFI_IOC_IMG_VER_BETTER;
	अन्यथा अगर (fwhdr_to_cmp->fwver.phase < base_fwhdr->fwver.phase)
		वापस BFI_IOC_IMG_VER_OLD;

	अगर (fwhdr_to_cmp->fwver.build > base_fwhdr->fwver.build)
		वापस BFI_IOC_IMG_VER_BETTER;
	अन्यथा अगर (fwhdr_to_cmp->fwver.build < base_fwhdr->fwver.build)
		वापस BFI_IOC_IMG_VER_OLD;

	/*
	 * All Version Numbers are equal.
	 * Md5 check to be करोne as a part of compatibility check.
	 */
	वापस BFI_IOC_IMG_VER_SAME;
पूर्ण

#घोषणा BFA_FLASH_PART_FWIMG_ADDR	0x100000 /* fw image address */

bfa_status_t
bfa_ioc_flash_img_get_chnk(काष्ठा bfa_ioc_s *ioc, u32 off,
				u32 *fwimg)
अणु
	वापस bfa_flash_raw_पढ़ो(ioc->pcidev.pci_bar_kva,
			BFA_FLASH_PART_FWIMG_ADDR + (off * माप(u32)),
			(अक्षर *)fwimg, BFI_FLASH_CHUNK_SZ);
पूर्ण

अटल क्रमागत bfi_ioc_img_ver_cmp_e
bfa_ioc_flash_fwver_cmp(काष्ठा bfa_ioc_s *ioc,
			काष्ठा bfi_ioc_image_hdr_s *base_fwhdr)
अणु
	काष्ठा bfi_ioc_image_hdr_s *flash_fwhdr;
	bfa_status_t status;
	u32 fwimg[BFI_FLASH_CHUNK_SZ_WORDS];

	status = bfa_ioc_flash_img_get_chnk(ioc, 0, fwimg);
	अगर (status != BFA_STATUS_OK)
		वापस BFI_IOC_IMG_VER_INCOMP;

	flash_fwhdr = (काष्ठा bfi_ioc_image_hdr_s *) fwimg;
	अगर (bfa_ioc_flash_fwver_valid(flash_fwhdr) == BFA_TRUE)
		वापस bfa_ioc_fw_ver_patch_cmp(base_fwhdr, flash_fwhdr);
	अन्यथा
		वापस BFI_IOC_IMG_VER_INCOMP;
पूर्ण


/*
 * Invalidate fwver signature
 */
bfa_status_t
bfa_ioc_fwsig_invalidate(काष्ठा bfa_ioc_s *ioc)
अणु

	u32	pgnum;
	u32	loff = 0;
	क्रमागत bfi_ioc_state ioc_fwstate;

	ioc_fwstate = bfa_ioc_get_cur_ioc_fwstate(ioc);
	अगर (!bfa_ioc_state_disabled(ioc_fwstate))
		वापस BFA_STATUS_ADAPTER_ENABLED;

	pgnum = PSS_SMEM_PGNUM(ioc->ioc_regs.smem_pg0, loff);
	ग_लिखोl(pgnum, ioc->ioc_regs.host_page_num_fn);
	bfa_mem_ग_लिखो(ioc->ioc_regs.smem_page_start, loff, BFA_IOC_FW_INV_SIGN);

	वापस BFA_STATUS_OK;
पूर्ण

/*
 * Conditionally flush any pending message from firmware at start.
 */
अटल व्योम
bfa_ioc_msgflush(काष्ठा bfa_ioc_s *ioc)
अणु
	u32	r32;

	r32 = पढ़ोl(ioc->ioc_regs.lpu_mbox_cmd);
	अगर (r32)
		ग_लिखोl(1, ioc->ioc_regs.lpu_mbox_cmd);
पूर्ण

अटल व्योम
bfa_ioc_hwinit(काष्ठा bfa_ioc_s *ioc, bfa_boolean_t क्रमce)
अणु
	क्रमागत bfi_ioc_state ioc_fwstate;
	bfa_boolean_t fwvalid;
	u32 boot_type;
	u32 boot_env;

	ioc_fwstate = bfa_ioc_get_cur_ioc_fwstate(ioc);

	अगर (क्रमce)
		ioc_fwstate = BFI_IOC_UNINIT;

	bfa_trc(ioc, ioc_fwstate);

	boot_type = BFI_FWBOOT_TYPE_NORMAL;
	boot_env = BFI_FWBOOT_ENV_OS;

	/*
	 * check अगर firmware is valid
	 */
	fwvalid = (ioc_fwstate == BFI_IOC_UNINIT) ?
		BFA_FALSE : bfa_ioc_fwver_valid(ioc, boot_env);

	अगर (!fwvalid) अणु
		अगर (bfa_ioc_boot(ioc, boot_type, boot_env) == BFA_STATUS_OK)
			bfa_ioc_poll_fwinit(ioc);
		वापस;
	पूर्ण

	/*
	 * If hardware initialization is in progress (initialized by other IOC),
	 * just रुको क्रम an initialization completion पूर्णांकerrupt.
	 */
	अगर (ioc_fwstate == BFI_IOC_INITING) अणु
		bfa_ioc_poll_fwinit(ioc);
		वापस;
	पूर्ण

	/*
	 * If IOC function is disabled and firmware version is same,
	 * just re-enable IOC.
	 *
	 * If option rom, IOC must not be in operational state. With
	 * convergence, IOC will be in operational state when 2nd driver
	 * is loaded.
	 */
	अगर (ioc_fwstate == BFI_IOC_DISABLED || ioc_fwstate == BFI_IOC_OP) अणु

		/*
		 * When using MSI-X any pending firmware पढ़ोy event should
		 * be flushed. Otherwise MSI-X पूर्णांकerrupts are not delivered.
		 */
		bfa_ioc_msgflush(ioc);
		bfa_fsm_send_event(&ioc->iocpf, IOCPF_E_FWREADY);
		वापस;
	पूर्ण

	/*
	 * Initialize the h/w क्रम any other states.
	 */
	अगर (bfa_ioc_boot(ioc, boot_type, boot_env) == BFA_STATUS_OK)
		bfa_ioc_poll_fwinit(ioc);
पूर्ण

अटल व्योम
bfa_ioc_समयout(व्योम *ioc_arg)
अणु
	काष्ठा bfa_ioc_s  *ioc = (काष्ठा bfa_ioc_s *) ioc_arg;

	bfa_trc(ioc, 0);
	bfa_fsm_send_event(ioc, IOC_E_TIMEOUT);
पूर्ण

व्योम
bfa_ioc_mbox_send(काष्ठा bfa_ioc_s *ioc, व्योम *ioc_msg, पूर्णांक len)
अणु
	u32 *msgp = (u32 *) ioc_msg;
	u32 i;

	bfa_trc(ioc, msgp[0]);
	bfa_trc(ioc, len);

	WARN_ON(len > BFI_IOC_MSGLEN_MAX);

	/*
	 * first ग_लिखो msg to mailbox रेजिस्टरs
	 */
	क्रम (i = 0; i < len / माप(u32); i++)
		ग_लिखोl(cpu_to_le32(msgp[i]),
			ioc->ioc_regs.hfn_mbox + i * माप(u32));

	क्रम (; i < BFI_IOC_MSGLEN_MAX / माप(u32); i++)
		ग_लिखोl(0, ioc->ioc_regs.hfn_mbox + i * माप(u32));

	/*
	 * ग_लिखो 1 to mailbox CMD to trigger LPU event
	 */
	ग_लिखोl(1, ioc->ioc_regs.hfn_mbox_cmd);
	(व्योम) पढ़ोl(ioc->ioc_regs.hfn_mbox_cmd);
पूर्ण

अटल व्योम
bfa_ioc_send_enable(काष्ठा bfa_ioc_s *ioc)
अणु
	काष्ठा bfi_ioc_ctrl_req_s enable_req;

	bfi_h2i_set(enable_req.mh, BFI_MC_IOC, BFI_IOC_H2I_ENABLE_REQ,
		    bfa_ioc_portid(ioc));
	enable_req.clscode = cpu_to_be16(ioc->clscode);
	/* अचिन्हित 32-bit समय_प्रकार overflow in y2106 */
	enable_req.tv_sec = be32_to_cpu(kसमय_get_real_seconds());
	bfa_ioc_mbox_send(ioc, &enable_req, माप(काष्ठा bfi_ioc_ctrl_req_s));
पूर्ण

अटल व्योम
bfa_ioc_send_disable(काष्ठा bfa_ioc_s *ioc)
अणु
	काष्ठा bfi_ioc_ctrl_req_s disable_req;

	bfi_h2i_set(disable_req.mh, BFI_MC_IOC, BFI_IOC_H2I_DISABLE_REQ,
		    bfa_ioc_portid(ioc));
	disable_req.clscode = cpu_to_be16(ioc->clscode);
	/* अचिन्हित 32-bit समय_प्रकार overflow in y2106 */
	disable_req.tv_sec = be32_to_cpu(kसमय_get_real_seconds());
	bfa_ioc_mbox_send(ioc, &disable_req, माप(काष्ठा bfi_ioc_ctrl_req_s));
पूर्ण

अटल व्योम
bfa_ioc_send_getattr(काष्ठा bfa_ioc_s *ioc)
अणु
	काष्ठा bfi_ioc_getattr_req_s	attr_req;

	bfi_h2i_set(attr_req.mh, BFI_MC_IOC, BFI_IOC_H2I_GETATTR_REQ,
		    bfa_ioc_portid(ioc));
	bfa_dma_be_addr_set(attr_req.attr_addr, ioc->attr_dma.pa);
	bfa_ioc_mbox_send(ioc, &attr_req, माप(attr_req));
पूर्ण

अटल व्योम
bfa_ioc_hb_check(व्योम *cbarg)
अणु
	काष्ठा bfa_ioc_s  *ioc = cbarg;
	u32	hb_count;

	hb_count = पढ़ोl(ioc->ioc_regs.heartbeat);
	अगर (ioc->hb_count == hb_count) अणु
		bfa_ioc_recover(ioc);
		वापस;
	पूर्ण अन्यथा अणु
		ioc->hb_count = hb_count;
	पूर्ण

	bfa_ioc_mbox_poll(ioc);
	bfa_hb_समयr_start(ioc);
पूर्ण

अटल व्योम
bfa_ioc_hb_monitor(काष्ठा bfa_ioc_s *ioc)
अणु
	ioc->hb_count = पढ़ोl(ioc->ioc_regs.heartbeat);
	bfa_hb_समयr_start(ioc);
पूर्ण

/*
 *	Initiate a full firmware करोwnload.
 */
अटल bfa_status_t
bfa_ioc_करोwnload_fw(काष्ठा bfa_ioc_s *ioc, u32 boot_type,
		    u32 boot_env)
अणु
	u32 *fwimg;
	u32 pgnum;
	u32 loff = 0;
	u32 chunkno = 0;
	u32 i;
	u32 asicmode;
	u32 fwimg_size;
	u32 fwimg_buf[BFI_FLASH_CHUNK_SZ_WORDS];
	bfa_status_t status;

	अगर (boot_env == BFI_FWBOOT_ENV_OS &&
		boot_type == BFI_FWBOOT_TYPE_FLASH) अणु
		fwimg_size = BFI_FLASH_IMAGE_SZ/माप(u32);

		status = bfa_ioc_flash_img_get_chnk(ioc,
			BFA_IOC_FLASH_CHUNK_ADDR(chunkno), fwimg_buf);
		अगर (status != BFA_STATUS_OK)
			वापस status;

		fwimg = fwimg_buf;
	पूर्ण अन्यथा अणु
		fwimg_size = bfa_cb_image_get_size(bfa_ioc_asic_gen(ioc));
		fwimg = bfa_cb_image_get_chunk(bfa_ioc_asic_gen(ioc),
					BFA_IOC_FLASH_CHUNK_ADDR(chunkno));
	पूर्ण

	bfa_trc(ioc, fwimg_size);


	pgnum = PSS_SMEM_PGNUM(ioc->ioc_regs.smem_pg0, loff);
	ग_लिखोl(pgnum, ioc->ioc_regs.host_page_num_fn);

	क्रम (i = 0; i < fwimg_size; i++) अणु

		अगर (BFA_IOC_FLASH_CHUNK_NO(i) != chunkno) अणु
			chunkno = BFA_IOC_FLASH_CHUNK_NO(i);

			अगर (boot_env == BFI_FWBOOT_ENV_OS &&
				boot_type == BFI_FWBOOT_TYPE_FLASH) अणु
				status = bfa_ioc_flash_img_get_chnk(ioc,
					BFA_IOC_FLASH_CHUNK_ADDR(chunkno),
					fwimg_buf);
				अगर (status != BFA_STATUS_OK)
					वापस status;

				fwimg = fwimg_buf;
			पूर्ण अन्यथा अणु
				fwimg = bfa_cb_image_get_chunk(
					bfa_ioc_asic_gen(ioc),
					BFA_IOC_FLASH_CHUNK_ADDR(chunkno));
			पूर्ण
		पूर्ण

		/*
		 * ग_लिखो smem
		 */
		bfa_mem_ग_लिखो(ioc->ioc_regs.smem_page_start, loff,
			      fwimg[BFA_IOC_FLASH_OFFSET_IN_CHUNK(i)]);

		loff += माप(u32);

		/*
		 * handle page offset wrap around
		 */
		loff = PSS_SMEM_PGOFF(loff);
		अगर (loff == 0) अणु
			pgnum++;
			ग_लिखोl(pgnum, ioc->ioc_regs.host_page_num_fn);
		पूर्ण
	पूर्ण

	ग_लिखोl(PSS_SMEM_PGNUM(ioc->ioc_regs.smem_pg0, 0),
			ioc->ioc_regs.host_page_num_fn);

	/*
	 * Set boot type, env and device mode at the end.
	 */
	अगर (boot_env == BFI_FWBOOT_ENV_OS &&
		boot_type == BFI_FWBOOT_TYPE_FLASH) अणु
		boot_type = BFI_FWBOOT_TYPE_NORMAL;
	पूर्ण
	asicmode = BFI_FWBOOT_DEVMODE(ioc->asic_gen, ioc->asic_mode,
				ioc->port0_mode, ioc->port1_mode);
	bfa_mem_ग_लिखो(ioc->ioc_regs.smem_page_start, BFI_FWBOOT_DEVMODE_OFF,
			swab32(asicmode));
	bfa_mem_ग_लिखो(ioc->ioc_regs.smem_page_start, BFI_FWBOOT_TYPE_OFF,
			swab32(boot_type));
	bfa_mem_ग_लिखो(ioc->ioc_regs.smem_page_start, BFI_FWBOOT_ENV_OFF,
			swab32(boot_env));
	वापस BFA_STATUS_OK;
पूर्ण


/*
 * Update BFA configuration from firmware configuration.
 */
अटल व्योम
bfa_ioc_getattr_reply(काष्ठा bfa_ioc_s *ioc)
अणु
	काष्ठा bfi_ioc_attr_s	*attr = ioc->attr;

	attr->adapter_prop  = be32_to_cpu(attr->adapter_prop);
	attr->card_type     = be32_to_cpu(attr->card_type);
	attr->maxfrsize	    = be16_to_cpu(attr->maxfrsize);
	ioc->fcmode	= (attr->port_mode == BFI_PORT_MODE_FC);
	attr->mfg_year	= be16_to_cpu(attr->mfg_year);

	bfa_fsm_send_event(ioc, IOC_E_FWRSP_GETATTR);
पूर्ण

/*
 * Attach समय initialization of mbox logic.
 */
अटल व्योम
bfa_ioc_mbox_attach(काष्ठा bfa_ioc_s *ioc)
अणु
	काष्ठा bfa_ioc_mbox_mod_s	*mod = &ioc->mbox_mod;
	पूर्णांक	mc;

	INIT_LIST_HEAD(&mod->cmd_q);
	क्रम (mc = 0; mc < BFI_MC_MAX; mc++) अणु
		mod->mbhdlr[mc].cbfn = शून्य;
		mod->mbhdlr[mc].cbarg = ioc->bfa;
	पूर्ण
पूर्ण

/*
 * Mbox poll समयr -- restarts any pending mailbox requests.
 */
अटल व्योम
bfa_ioc_mbox_poll(काष्ठा bfa_ioc_s *ioc)
अणु
	काष्ठा bfa_ioc_mbox_mod_s	*mod = &ioc->mbox_mod;
	काष्ठा bfa_mbox_cmd_s		*cmd;
	u32			stat;

	/*
	 * If no command pending, करो nothing
	 */
	अगर (list_empty(&mod->cmd_q))
		वापस;

	/*
	 * If previous command is not yet fetched by firmware, करो nothing
	 */
	stat = पढ़ोl(ioc->ioc_regs.hfn_mbox_cmd);
	अगर (stat)
		वापस;

	/*
	 * Enqueue command to firmware.
	 */
	bfa_q_deq(&mod->cmd_q, &cmd);
	bfa_ioc_mbox_send(ioc, cmd->msg, माप(cmd->msg));
पूर्ण

/*
 * Cleanup any pending requests.
 */
अटल व्योम
bfa_ioc_mbox_flush(काष्ठा bfa_ioc_s *ioc)
अणु
	काष्ठा bfa_ioc_mbox_mod_s	*mod = &ioc->mbox_mod;
	काष्ठा bfa_mbox_cmd_s		*cmd;

	जबतक (!list_empty(&mod->cmd_q))
		bfa_q_deq(&mod->cmd_q, &cmd);
पूर्ण

/*
 * Read data from SMEM to host through PCI memmap
 *
 * @param[in]	ioc	memory क्रम IOC
 * @param[in]	tbuf	app memory to store data from smem
 * @param[in]	soff	smem offset
 * @param[in]	sz	size of smem in bytes
 */
अटल bfa_status_t
bfa_ioc_smem_पढ़ो(काष्ठा bfa_ioc_s *ioc, व्योम *tbuf, u32 soff, u32 sz)
अणु
	u32 pgnum, loff;
	__be32 r32;
	पूर्णांक i, len;
	u32 *buf = tbuf;

	pgnum = PSS_SMEM_PGNUM(ioc->ioc_regs.smem_pg0, soff);
	loff = PSS_SMEM_PGOFF(soff);
	bfa_trc(ioc, pgnum);
	bfa_trc(ioc, loff);
	bfa_trc(ioc, sz);

	/*
	 *  Hold semaphore to serialize pll init and fwtrc.
	 */
	अगर (BFA_FALSE == bfa_ioc_sem_get(ioc->ioc_regs.ioc_init_sem_reg)) अणु
		bfa_trc(ioc, 0);
		वापस BFA_STATUS_FAILED;
	पूर्ण

	ग_लिखोl(pgnum, ioc->ioc_regs.host_page_num_fn);

	len = sz/माप(u32);
	bfa_trc(ioc, len);
	क्रम (i = 0; i < len; i++) अणु
		r32 = bfa_mem_पढ़ो(ioc->ioc_regs.smem_page_start, loff);
		buf[i] = swab32(r32);
		loff += माप(u32);

		/*
		 * handle page offset wrap around
		 */
		loff = PSS_SMEM_PGOFF(loff);
		अगर (loff == 0) अणु
			pgnum++;
			ग_लिखोl(pgnum, ioc->ioc_regs.host_page_num_fn);
		पूर्ण
	पूर्ण
	ग_लिखोl(PSS_SMEM_PGNUM(ioc->ioc_regs.smem_pg0, 0),
			ioc->ioc_regs.host_page_num_fn);
	/*
	 *  release semaphore.
	 */
	पढ़ोl(ioc->ioc_regs.ioc_init_sem_reg);
	ग_लिखोl(1, ioc->ioc_regs.ioc_init_sem_reg);

	bfa_trc(ioc, pgnum);
	वापस BFA_STATUS_OK;
पूर्ण

/*
 * Clear SMEM data from host through PCI memmap
 *
 * @param[in]	ioc	memory क्रम IOC
 * @param[in]	soff	smem offset
 * @param[in]	sz	size of smem in bytes
 */
अटल bfa_status_t
bfa_ioc_smem_clr(काष्ठा bfa_ioc_s *ioc, u32 soff, u32 sz)
अणु
	पूर्णांक i, len;
	u32 pgnum, loff;

	pgnum = PSS_SMEM_PGNUM(ioc->ioc_regs.smem_pg0, soff);
	loff = PSS_SMEM_PGOFF(soff);
	bfa_trc(ioc, pgnum);
	bfa_trc(ioc, loff);
	bfa_trc(ioc, sz);

	/*
	 *  Hold semaphore to serialize pll init and fwtrc.
	 */
	अगर (BFA_FALSE == bfa_ioc_sem_get(ioc->ioc_regs.ioc_init_sem_reg)) अणु
		bfa_trc(ioc, 0);
		वापस BFA_STATUS_FAILED;
	पूर्ण

	ग_लिखोl(pgnum, ioc->ioc_regs.host_page_num_fn);

	len = sz/माप(u32); /* len in words */
	bfa_trc(ioc, len);
	क्रम (i = 0; i < len; i++) अणु
		bfa_mem_ग_लिखो(ioc->ioc_regs.smem_page_start, loff, 0);
		loff += माप(u32);

		/*
		 * handle page offset wrap around
		 */
		loff = PSS_SMEM_PGOFF(loff);
		अगर (loff == 0) अणु
			pgnum++;
			ग_लिखोl(pgnum, ioc->ioc_regs.host_page_num_fn);
		पूर्ण
	पूर्ण
	ग_लिखोl(PSS_SMEM_PGNUM(ioc->ioc_regs.smem_pg0, 0),
			ioc->ioc_regs.host_page_num_fn);

	/*
	 *  release semaphore.
	 */
	पढ़ोl(ioc->ioc_regs.ioc_init_sem_reg);
	ग_लिखोl(1, ioc->ioc_regs.ioc_init_sem_reg);
	bfa_trc(ioc, pgnum);
	वापस BFA_STATUS_OK;
पूर्ण

अटल व्योम
bfa_ioc_fail_notअगरy(काष्ठा bfa_ioc_s *ioc)
अणु
	काष्ठा bfad_s *bfad = (काष्ठा bfad_s *)ioc->bfa->bfad;

	/*
	 * Notअगरy driver and common modules रेजिस्टरed क्रम notअगरication.
	 */
	ioc->cbfn->hbfail_cbfn(ioc->bfa);
	bfa_ioc_event_notअगरy(ioc, BFA_IOC_E_FAILED);

	bfa_ioc_debug_save_ftrc(ioc);

	BFA_LOG(KERN_CRIT, bfad, bfa_log_level,
		"Heart Beat of IOC has failed\n");
	bfa_ioc_aen_post(ioc, BFA_IOC_AEN_HBFAIL);

पूर्ण

अटल व्योम
bfa_ioc_pf_fwmismatch(काष्ठा bfa_ioc_s *ioc)
अणु
	काष्ठा bfad_s *bfad = (काष्ठा bfad_s *)ioc->bfa->bfad;
	/*
	 * Provide enable completion callback.
	 */
	ioc->cbfn->enable_cbfn(ioc->bfa, BFA_STATUS_IOC_FAILURE);
	BFA_LOG(KERN_WARNING, bfad, bfa_log_level,
		"Running firmware version is incompatible "
		"with the driver version\n");
	bfa_ioc_aen_post(ioc, BFA_IOC_AEN_FWMISMATCH);
पूर्ण

bfa_status_t
bfa_ioc_pll_init(काष्ठा bfa_ioc_s *ioc)
अणु

	/*
	 *  Hold semaphore so that nobody can access the chip during init.
	 */
	bfa_ioc_sem_get(ioc->ioc_regs.ioc_init_sem_reg);

	bfa_ioc_pll_init_asic(ioc);

	ioc->pllinit = BFA_TRUE;

	/*
	 * Initialize LMEM
	 */
	bfa_ioc_lmem_init(ioc);

	/*
	 *  release semaphore.
	 */
	पढ़ोl(ioc->ioc_regs.ioc_init_sem_reg);
	ग_लिखोl(1, ioc->ioc_regs.ioc_init_sem_reg);

	वापस BFA_STATUS_OK;
पूर्ण

/*
 * Interface used by diag module to करो firmware boot with memory test
 * as the entry vector.
 */
bfa_status_t
bfa_ioc_boot(काष्ठा bfa_ioc_s *ioc, u32 boot_type, u32 boot_env)
अणु
	काष्ठा bfi_ioc_image_hdr_s *drv_fwhdr;
	bfa_status_t status;
	bfa_ioc_stats(ioc, ioc_boots);

	अगर (bfa_ioc_pll_init(ioc) != BFA_STATUS_OK)
		वापस BFA_STATUS_FAILED;

	अगर (boot_env == BFI_FWBOOT_ENV_OS &&
		boot_type == BFI_FWBOOT_TYPE_NORMAL) अणु

		drv_fwhdr = (काष्ठा bfi_ioc_image_hdr_s *)
			bfa_cb_image_get_chunk(bfa_ioc_asic_gen(ioc), 0);

		/*
		 * Work with Flash अगरf flash f/w is better than driver f/w.
		 * Otherwise push drivers firmware.
		 */
		अगर (bfa_ioc_flash_fwver_cmp(ioc, drv_fwhdr) ==
						BFI_IOC_IMG_VER_BETTER)
			boot_type = BFI_FWBOOT_TYPE_FLASH;
	पूर्ण

	/*
	 * Initialize IOC state of all functions on a chip reset.
	 */
	अगर (boot_type == BFI_FWBOOT_TYPE_MEMTEST) अणु
		bfa_ioc_set_cur_ioc_fwstate(ioc, BFI_IOC_MEMTEST);
		bfa_ioc_set_alt_ioc_fwstate(ioc, BFI_IOC_MEMTEST);
	पूर्ण अन्यथा अणु
		bfa_ioc_set_cur_ioc_fwstate(ioc, BFI_IOC_INITING);
		bfa_ioc_set_alt_ioc_fwstate(ioc, BFI_IOC_INITING);
	पूर्ण

	bfa_ioc_msgflush(ioc);
	status = bfa_ioc_करोwnload_fw(ioc, boot_type, boot_env);
	अगर (status == BFA_STATUS_OK)
		bfa_ioc_lpu_start(ioc);
	अन्यथा अणु
		WARN_ON(boot_type == BFI_FWBOOT_TYPE_MEMTEST);
		bfa_iocpf_समयout(ioc);
	पूर्ण
	वापस status;
पूर्ण

/*
 * Enable/disable IOC failure स्वतः recovery.
 */
व्योम
bfa_ioc_स्वतः_recover(bfa_boolean_t स्वतः_recover)
अणु
	bfa_स्वतः_recover = स्वतः_recover;
पूर्ण



bfa_boolean_t
bfa_ioc_is_operational(काष्ठा bfa_ioc_s *ioc)
अणु
	वापस bfa_fsm_cmp_state(ioc, bfa_ioc_sm_op);
पूर्ण

bfa_boolean_t
bfa_ioc_is_initialized(काष्ठा bfa_ioc_s *ioc)
अणु
	u32 r32 = bfa_ioc_get_cur_ioc_fwstate(ioc);

	वापस ((r32 != BFI_IOC_UNINIT) &&
		(r32 != BFI_IOC_INITING) &&
		(r32 != BFI_IOC_MEMTEST));
पूर्ण

bfa_boolean_t
bfa_ioc_msgget(काष्ठा bfa_ioc_s *ioc, व्योम *mbmsg)
अणु
	__be32	*msgp = mbmsg;
	u32	r32;
	पूर्णांक		i;

	r32 = पढ़ोl(ioc->ioc_regs.lpu_mbox_cmd);
	अगर ((r32 & 1) == 0)
		वापस BFA_FALSE;

	/*
	 * पढ़ो the MBOX msg
	 */
	क्रम (i = 0; i < (माप(जोड़ bfi_ioc_i2h_msg_u) / माप(u32));
	     i++) अणु
		r32 = पढ़ोl(ioc->ioc_regs.lpu_mbox +
				   i * माप(u32));
		msgp[i] = cpu_to_be32(r32);
	पूर्ण

	/*
	 * turn off mailbox पूर्णांकerrupt by clearing mailbox status
	 */
	ग_लिखोl(1, ioc->ioc_regs.lpu_mbox_cmd);
	पढ़ोl(ioc->ioc_regs.lpu_mbox_cmd);

	वापस BFA_TRUE;
पूर्ण

व्योम
bfa_ioc_isr(काष्ठा bfa_ioc_s *ioc, काष्ठा bfi_mbmsg_s *m)
अणु
	जोड़ bfi_ioc_i2h_msg_u	*msg;
	काष्ठा bfa_iocpf_s *iocpf = &ioc->iocpf;

	msg = (जोड़ bfi_ioc_i2h_msg_u *) m;

	bfa_ioc_stats(ioc, ioc_isrs);

	चयन (msg->mh.msg_id) अणु
	हाल BFI_IOC_I2H_HBEAT:
		अवरोध;

	हाल BFI_IOC_I2H_ENABLE_REPLY:
		ioc->port_mode = ioc->port_mode_cfg =
				(क्रमागत bfa_mode_s)msg->fw_event.port_mode;
		ioc->ad_cap_bm = msg->fw_event.cap_bm;
		bfa_fsm_send_event(iocpf, IOCPF_E_FWRSP_ENABLE);
		अवरोध;

	हाल BFI_IOC_I2H_DISABLE_REPLY:
		bfa_fsm_send_event(iocpf, IOCPF_E_FWRSP_DISABLE);
		अवरोध;

	हाल BFI_IOC_I2H_GETATTR_REPLY:
		bfa_ioc_getattr_reply(ioc);
		अवरोध;

	शेष:
		bfa_trc(ioc, msg->mh.msg_id);
		WARN_ON(1);
	पूर्ण
पूर्ण

/*
 * IOC attach समय initialization and setup.
 *
 * @param[in]	ioc	memory क्रम IOC
 * @param[in]	bfa	driver instance काष्ठाure
 */
व्योम
bfa_ioc_attach(काष्ठा bfa_ioc_s *ioc, व्योम *bfa, काष्ठा bfa_ioc_cbfn_s *cbfn,
	       काष्ठा bfa_समयr_mod_s *समयr_mod)
अणु
	ioc->bfa	= bfa;
	ioc->cbfn	= cbfn;
	ioc->समयr_mod	= समयr_mod;
	ioc->fcmode	= BFA_FALSE;
	ioc->pllinit	= BFA_FALSE;
	ioc->dbg_fwsave_once = BFA_TRUE;
	ioc->iocpf.ioc	= ioc;

	bfa_ioc_mbox_attach(ioc);
	INIT_LIST_HEAD(&ioc->notअगरy_q);

	bfa_fsm_set_state(ioc, bfa_ioc_sm_uninit);
	bfa_fsm_send_event(ioc, IOC_E_RESET);
पूर्ण

/*
 * Driver detach समय IOC cleanup.
 */
व्योम
bfa_ioc_detach(काष्ठा bfa_ioc_s *ioc)
अणु
	bfa_fsm_send_event(ioc, IOC_E_DETACH);
	INIT_LIST_HEAD(&ioc->notअगरy_q);
पूर्ण

/*
 * Setup IOC PCI properties.
 *
 * @param[in]	pcidev	PCI device inक्रमmation क्रम this IOC
 */
व्योम
bfa_ioc_pci_init(काष्ठा bfa_ioc_s *ioc, काष्ठा bfa_pcidev_s *pcidev,
		क्रमागत bfi_pcअगरn_class clscode)
अणु
	ioc->clscode	= clscode;
	ioc->pcidev	= *pcidev;

	/*
	 * Initialize IOC and device personality
	 */
	ioc->port0_mode = ioc->port1_mode = BFI_PORT_MODE_FC;
	ioc->asic_mode  = BFI_ASIC_MODE_FC;

	चयन (pcidev->device_id) अणु
	हाल BFA_PCI_DEVICE_ID_FC_8G1P:
	हाल BFA_PCI_DEVICE_ID_FC_8G2P:
		ioc->asic_gen = BFI_ASIC_GEN_CB;
		ioc->fcmode = BFA_TRUE;
		ioc->port_mode = ioc->port_mode_cfg = BFA_MODE_HBA;
		ioc->ad_cap_bm = BFA_CM_HBA;
		अवरोध;

	हाल BFA_PCI_DEVICE_ID_CT:
		ioc->asic_gen = BFI_ASIC_GEN_CT;
		ioc->port0_mode = ioc->port1_mode = BFI_PORT_MODE_ETH;
		ioc->asic_mode  = BFI_ASIC_MODE_ETH;
		ioc->port_mode = ioc->port_mode_cfg = BFA_MODE_CNA;
		ioc->ad_cap_bm = BFA_CM_CNA;
		अवरोध;

	हाल BFA_PCI_DEVICE_ID_CT_FC:
		ioc->asic_gen = BFI_ASIC_GEN_CT;
		ioc->fcmode = BFA_TRUE;
		ioc->port_mode = ioc->port_mode_cfg = BFA_MODE_HBA;
		ioc->ad_cap_bm = BFA_CM_HBA;
		अवरोध;

	हाल BFA_PCI_DEVICE_ID_CT2:
	हाल BFA_PCI_DEVICE_ID_CT2_QUAD:
		ioc->asic_gen = BFI_ASIC_GEN_CT2;
		अगर (clscode == BFI_PCIFN_CLASS_FC &&
		    pcidev->ssid == BFA_PCI_CT2_SSID_FC) अणु
			ioc->asic_mode  = BFI_ASIC_MODE_FC16;
			ioc->fcmode = BFA_TRUE;
			ioc->port_mode = ioc->port_mode_cfg = BFA_MODE_HBA;
			ioc->ad_cap_bm = BFA_CM_HBA;
		पूर्ण अन्यथा अणु
			ioc->port0_mode = ioc->port1_mode = BFI_PORT_MODE_ETH;
			ioc->asic_mode  = BFI_ASIC_MODE_ETH;
			अगर (pcidev->ssid == BFA_PCI_CT2_SSID_FCoE) अणु
				ioc->port_mode =
				ioc->port_mode_cfg = BFA_MODE_CNA;
				ioc->ad_cap_bm = BFA_CM_CNA;
			पूर्ण अन्यथा अणु
				ioc->port_mode =
				ioc->port_mode_cfg = BFA_MODE_NIC;
				ioc->ad_cap_bm = BFA_CM_NIC;
			पूर्ण
		पूर्ण
		अवरोध;

	शेष:
		WARN_ON(1);
	पूर्ण

	/*
	 * Set asic specअगरic पूर्णांकerfaces. See bfa_ioc_cb.c and bfa_ioc_ct.c
	 */
	अगर (ioc->asic_gen == BFI_ASIC_GEN_CB)
		bfa_ioc_set_cb_hwअगर(ioc);
	अन्यथा अगर (ioc->asic_gen == BFI_ASIC_GEN_CT)
		bfa_ioc_set_ct_hwअगर(ioc);
	अन्यथा अणु
		WARN_ON(ioc->asic_gen != BFI_ASIC_GEN_CT2);
		bfa_ioc_set_ct2_hwअगर(ioc);
		bfa_ioc_ct2_घातeron(ioc);
	पूर्ण

	bfa_ioc_map_port(ioc);
	bfa_ioc_reg_init(ioc);
पूर्ण

/*
 * Initialize IOC dma memory
 *
 * @param[in]	dm_kva	kernel भव address of IOC dma memory
 * @param[in]	dm_pa	physical address of IOC dma memory
 */
व्योम
bfa_ioc_mem_claim(काष्ठा bfa_ioc_s *ioc,  u8 *dm_kva, u64 dm_pa)
अणु
	/*
	 * dma memory क्रम firmware attribute
	 */
	ioc->attr_dma.kva = dm_kva;
	ioc->attr_dma.pa = dm_pa;
	ioc->attr = (काष्ठा bfi_ioc_attr_s *) dm_kva;
पूर्ण

व्योम
bfa_ioc_enable(काष्ठा bfa_ioc_s *ioc)
अणु
	bfa_ioc_stats(ioc, ioc_enables);
	ioc->dbg_fwsave_once = BFA_TRUE;

	bfa_fsm_send_event(ioc, IOC_E_ENABLE);
पूर्ण

व्योम
bfa_ioc_disable(काष्ठा bfa_ioc_s *ioc)
अणु
	bfa_ioc_stats(ioc, ioc_disables);
	bfa_fsm_send_event(ioc, IOC_E_DISABLE);
पूर्ण

व्योम
bfa_ioc_suspend(काष्ठा bfa_ioc_s *ioc)
अणु
	ioc->dbg_fwsave_once = BFA_TRUE;
	bfa_fsm_send_event(ioc, IOC_E_HWERROR);
पूर्ण

/*
 * Initialize memory क्रम saving firmware trace. Driver must initialize
 * trace memory beक्रमe call bfa_ioc_enable().
 */
व्योम
bfa_ioc_debug_memclaim(काष्ठा bfa_ioc_s *ioc, व्योम *dbg_fwsave)
अणु
	ioc->dbg_fwsave	    = dbg_fwsave;
	ioc->dbg_fwsave_len = BFA_DBG_FWTRC_LEN;
पूर्ण

/*
 * Register mailbox message handler functions
 *
 * @param[in]	ioc		IOC instance
 * @param[in]	mcfuncs		message class handler functions
 */
व्योम
bfa_ioc_mbox_रेजिस्टर(काष्ठा bfa_ioc_s *ioc, bfa_ioc_mbox_mcfunc_t *mcfuncs)
अणु
	काष्ठा bfa_ioc_mbox_mod_s	*mod = &ioc->mbox_mod;
	पूर्णांक				mc;

	क्रम (mc = 0; mc < BFI_MC_MAX; mc++)
		mod->mbhdlr[mc].cbfn = mcfuncs[mc];
पूर्ण

/*
 * Register mailbox message handler function, to be called by common modules
 */
व्योम
bfa_ioc_mbox_regisr(काष्ठा bfa_ioc_s *ioc, क्रमागत bfi_mclass mc,
		    bfa_ioc_mbox_mcfunc_t cbfn, व्योम *cbarg)
अणु
	काष्ठा bfa_ioc_mbox_mod_s	*mod = &ioc->mbox_mod;

	mod->mbhdlr[mc].cbfn	= cbfn;
	mod->mbhdlr[mc].cbarg	= cbarg;
पूर्ण

/*
 * Queue a mailbox command request to firmware. Waits अगर mailbox is busy.
 * Responsibility of caller to serialize
 *
 * @param[in]	ioc	IOC instance
 * @param[i]	cmd	Mailbox command
 */
व्योम
bfa_ioc_mbox_queue(काष्ठा bfa_ioc_s *ioc, काष्ठा bfa_mbox_cmd_s *cmd)
अणु
	काष्ठा bfa_ioc_mbox_mod_s	*mod = &ioc->mbox_mod;
	u32			stat;

	/*
	 * If a previous command is pending, queue new command
	 */
	अगर (!list_empty(&mod->cmd_q)) अणु
		list_add_tail(&cmd->qe, &mod->cmd_q);
		वापस;
	पूर्ण

	/*
	 * If mailbox is busy, queue command क्रम poll समयr
	 */
	stat = पढ़ोl(ioc->ioc_regs.hfn_mbox_cmd);
	अगर (stat) अणु
		list_add_tail(&cmd->qe, &mod->cmd_q);
		वापस;
	पूर्ण

	/*
	 * mailbox is मुक्त -- queue command to firmware
	 */
	bfa_ioc_mbox_send(ioc, cmd->msg, माप(cmd->msg));
पूर्ण

/*
 * Handle mailbox पूर्णांकerrupts
 */
व्योम
bfa_ioc_mbox_isr(काष्ठा bfa_ioc_s *ioc)
अणु
	काष्ठा bfa_ioc_mbox_mod_s	*mod = &ioc->mbox_mod;
	काष्ठा bfi_mbmsg_s		m;
	पूर्णांक				mc;

	अगर (bfa_ioc_msgget(ioc, &m)) अणु
		/*
		 * Treat IOC message class as special.
		 */
		mc = m.mh.msg_class;
		अगर (mc == BFI_MC_IOC) अणु
			bfa_ioc_isr(ioc, &m);
			वापस;
		पूर्ण

		अगर ((mc >= BFI_MC_MAX) || (mod->mbhdlr[mc].cbfn == शून्य))
			वापस;

		mod->mbhdlr[mc].cbfn(mod->mbhdlr[mc].cbarg, &m);
	पूर्ण

	bfa_ioc_lpu_पढ़ो_stat(ioc);

	/*
	 * Try to send pending mailbox commands
	 */
	bfa_ioc_mbox_poll(ioc);
पूर्ण

व्योम
bfa_ioc_error_isr(काष्ठा bfa_ioc_s *ioc)
अणु
	bfa_ioc_stats(ioc, ioc_hbfails);
	ioc->stats.hb_count = ioc->hb_count;
	bfa_fsm_send_event(ioc, IOC_E_HWERROR);
पूर्ण

/*
 * वापस true अगर IOC is disabled
 */
bfa_boolean_t
bfa_ioc_is_disabled(काष्ठा bfa_ioc_s *ioc)
अणु
	वापस bfa_fsm_cmp_state(ioc, bfa_ioc_sm_disabling) ||
		bfa_fsm_cmp_state(ioc, bfa_ioc_sm_disabled);
पूर्ण

/*
 * वापस true अगर IOC firmware is dअगरferent.
 */
bfa_boolean_t
bfa_ioc_fw_mismatch(काष्ठा bfa_ioc_s *ioc)
अणु
	वापस bfa_fsm_cmp_state(ioc, bfa_ioc_sm_reset) ||
		bfa_fsm_cmp_state(&ioc->iocpf, bfa_iocpf_sm_fwcheck) ||
		bfa_fsm_cmp_state(&ioc->iocpf, bfa_iocpf_sm_mismatch);
पूर्ण

/*
 * Check अगर adapter is disabled -- both IOCs should be in a disabled
 * state.
 */
bfa_boolean_t
bfa_ioc_adapter_is_disabled(काष्ठा bfa_ioc_s *ioc)
अणु
	u32	ioc_state;

	अगर (!bfa_fsm_cmp_state(ioc, bfa_ioc_sm_disabled))
		वापस BFA_FALSE;

	ioc_state = bfa_ioc_get_cur_ioc_fwstate(ioc);
	अगर (!bfa_ioc_state_disabled(ioc_state))
		वापस BFA_FALSE;

	अगर (ioc->pcidev.device_id != BFA_PCI_DEVICE_ID_FC_8G1P) अणु
		ioc_state = bfa_ioc_get_cur_ioc_fwstate(ioc);
		अगर (!bfa_ioc_state_disabled(ioc_state))
			वापस BFA_FALSE;
	पूर्ण

	वापस BFA_TRUE;
पूर्ण

/*
 * Reset IOC fwstate रेजिस्टरs.
 */
व्योम
bfa_ioc_reset_fwstate(काष्ठा bfa_ioc_s *ioc)
अणु
	bfa_ioc_set_cur_ioc_fwstate(ioc, BFI_IOC_UNINIT);
	bfa_ioc_set_alt_ioc_fwstate(ioc, BFI_IOC_UNINIT);
पूर्ण

#घोषणा BFA_MFG_NAME "QLogic"
व्योम
bfa_ioc_get_adapter_attr(काष्ठा bfa_ioc_s *ioc,
			 काष्ठा bfa_adapter_attr_s *ad_attr)
अणु
	काष्ठा bfi_ioc_attr_s	*ioc_attr;

	ioc_attr = ioc->attr;

	bfa_ioc_get_adapter_serial_num(ioc, ad_attr->serial_num);
	bfa_ioc_get_adapter_fw_ver(ioc, ad_attr->fw_ver);
	bfa_ioc_get_adapter_optrom_ver(ioc, ad_attr->optrom_ver);
	bfa_ioc_get_adapter_manufacturer(ioc, ad_attr->manufacturer);
	स_नकल(&ad_attr->vpd, &ioc_attr->vpd,
		      माप(काष्ठा bfa_mfg_vpd_s));

	ad_attr->nports = bfa_ioc_get_nports(ioc);
	ad_attr->max_speed = bfa_ioc_speed_sup(ioc);

	bfa_ioc_get_adapter_model(ioc, ad_attr->model);
	/* For now, model descr uses same model string */
	bfa_ioc_get_adapter_model(ioc, ad_attr->model_descr);

	ad_attr->card_type = ioc_attr->card_type;
	ad_attr->is_mezz = bfa_mfg_is_mezz(ioc_attr->card_type);

	अगर (BFI_ADAPTER_IS_SPECIAL(ioc_attr->adapter_prop))
		ad_attr->prototype = 1;
	अन्यथा
		ad_attr->prototype = 0;

	ad_attr->pwwn = ioc->attr->pwwn;
	ad_attr->mac  = bfa_ioc_get_mac(ioc);

	ad_attr->pcie_gen = ioc_attr->pcie_gen;
	ad_attr->pcie_lanes = ioc_attr->pcie_lanes;
	ad_attr->pcie_lanes_orig = ioc_attr->pcie_lanes_orig;
	ad_attr->asic_rev = ioc_attr->asic_rev;

	bfa_ioc_get_pci_chip_rev(ioc, ad_attr->hw_ver);

	ad_attr->cna_capable = bfa_ioc_is_cna(ioc);
	ad_attr->trunk_capable = (ad_attr->nports > 1) &&
				  !bfa_ioc_is_cna(ioc) && !ad_attr->is_mezz;
	ad_attr->mfg_day = ioc_attr->mfg_day;
	ad_attr->mfg_month = ioc_attr->mfg_month;
	ad_attr->mfg_year = ioc_attr->mfg_year;
	स_नकल(ad_attr->uuid, ioc_attr->uuid, BFA_ADAPTER_UUID_LEN);
पूर्ण

क्रमागत bfa_ioc_type_e
bfa_ioc_get_type(काष्ठा bfa_ioc_s *ioc)
अणु
	अगर (ioc->clscode == BFI_PCIFN_CLASS_ETH)
		वापस BFA_IOC_TYPE_LL;

	WARN_ON(ioc->clscode != BFI_PCIFN_CLASS_FC);

	वापस (ioc->attr->port_mode == BFI_PORT_MODE_FC)
		? BFA_IOC_TYPE_FC : BFA_IOC_TYPE_FCoE;
पूर्ण

व्योम
bfa_ioc_get_adapter_serial_num(काष्ठा bfa_ioc_s *ioc, अक्षर *serial_num)
अणु
	स_रखो((व्योम *)serial_num, 0, BFA_ADAPTER_SERIAL_NUM_LEN);
	स_नकल((व्योम *)serial_num,
			(व्योम *)ioc->attr->brcd_serialnum,
			BFA_ADAPTER_SERIAL_NUM_LEN);
पूर्ण

व्योम
bfa_ioc_get_adapter_fw_ver(काष्ठा bfa_ioc_s *ioc, अक्षर *fw_ver)
अणु
	स_रखो((व्योम *)fw_ver, 0, BFA_VERSION_LEN);
	स_नकल(fw_ver, ioc->attr->fw_version, BFA_VERSION_LEN);
पूर्ण

व्योम
bfa_ioc_get_pci_chip_rev(काष्ठा bfa_ioc_s *ioc, अक्षर *chip_rev)
अणु
	WARN_ON(!chip_rev);

	स_रखो((व्योम *)chip_rev, 0, BFA_IOC_CHIP_REV_LEN);

	chip_rev[0] = 'R';
	chip_rev[1] = 'e';
	chip_rev[2] = 'v';
	chip_rev[3] = '-';
	chip_rev[4] = ioc->attr->asic_rev;
	chip_rev[5] = '\0';
पूर्ण

व्योम
bfa_ioc_get_adapter_optrom_ver(काष्ठा bfa_ioc_s *ioc, अक्षर *optrom_ver)
अणु
	स_रखो((व्योम *)optrom_ver, 0, BFA_VERSION_LEN);
	स_नकल(optrom_ver, ioc->attr->optrom_version,
		      BFA_VERSION_LEN);
पूर्ण

व्योम
bfa_ioc_get_adapter_manufacturer(काष्ठा bfa_ioc_s *ioc, अक्षर *manufacturer)
अणु
	स_रखो((व्योम *)manufacturer, 0, BFA_ADAPTER_MFG_NAME_LEN);
	strlcpy(manufacturer, BFA_MFG_NAME, BFA_ADAPTER_MFG_NAME_LEN);
पूर्ण

व्योम
bfa_ioc_get_adapter_model(काष्ठा bfa_ioc_s *ioc, अक्षर *model)
अणु
	काष्ठा bfi_ioc_attr_s	*ioc_attr;
	u8 nports = bfa_ioc_get_nports(ioc);

	WARN_ON(!model);
	स_रखो((व्योम *)model, 0, BFA_ADAPTER_MODEL_NAME_LEN);

	ioc_attr = ioc->attr;

	अगर (bfa_asic_id_ct2(ioc->pcidev.device_id) &&
		(!bfa_mfg_is_mezz(ioc_attr->card_type)))
		snम_लिखो(model, BFA_ADAPTER_MODEL_NAME_LEN, "%s-%u-%u%s",
			BFA_MFG_NAME, ioc_attr->card_type, nports, "p");
	अन्यथा
		snम_लिखो(model, BFA_ADAPTER_MODEL_NAME_LEN, "%s-%u",
			BFA_MFG_NAME, ioc_attr->card_type);
पूर्ण

क्रमागत bfa_ioc_state
bfa_ioc_get_state(काष्ठा bfa_ioc_s *ioc)
अणु
	क्रमागत bfa_iocpf_state iocpf_st;
	क्रमागत bfa_ioc_state ioc_st = bfa_sm_to_state(ioc_sm_table, ioc->fsm);

	अगर (ioc_st == BFA_IOC_ENABLING ||
		ioc_st == BFA_IOC_FAIL || ioc_st == BFA_IOC_INITFAIL) अणु

		iocpf_st = bfa_sm_to_state(iocpf_sm_table, ioc->iocpf.fsm);

		चयन (iocpf_st) अणु
		हाल BFA_IOCPF_SEMWAIT:
			ioc_st = BFA_IOC_SEMWAIT;
			अवरोध;

		हाल BFA_IOCPF_HWINIT:
			ioc_st = BFA_IOC_HWINIT;
			अवरोध;

		हाल BFA_IOCPF_FWMISMATCH:
			ioc_st = BFA_IOC_FWMISMATCH;
			अवरोध;

		हाल BFA_IOCPF_FAIL:
			ioc_st = BFA_IOC_FAIL;
			अवरोध;

		हाल BFA_IOCPF_INITFAIL:
			ioc_st = BFA_IOC_INITFAIL;
			अवरोध;

		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	वापस ioc_st;
पूर्ण

व्योम
bfa_ioc_get_attr(काष्ठा bfa_ioc_s *ioc, काष्ठा bfa_ioc_attr_s *ioc_attr)
अणु
	स_रखो((व्योम *)ioc_attr, 0, माप(काष्ठा bfa_ioc_attr_s));

	ioc_attr->state = bfa_ioc_get_state(ioc);
	ioc_attr->port_id = bfa_ioc_portid(ioc);
	ioc_attr->port_mode = ioc->port_mode;
	ioc_attr->port_mode_cfg = ioc->port_mode_cfg;
	ioc_attr->cap_bm = ioc->ad_cap_bm;

	ioc_attr->ioc_type = bfa_ioc_get_type(ioc);

	bfa_ioc_get_adapter_attr(ioc, &ioc_attr->adapter_attr);

	ioc_attr->pci_attr.device_id = bfa_ioc_devid(ioc);
	ioc_attr->pci_attr.pcअगरn = bfa_ioc_pcअगरn(ioc);
	ioc_attr->def_fn = (bfa_ioc_pcअगरn(ioc) == bfa_ioc_portid(ioc));
	bfa_ioc_get_pci_chip_rev(ioc, ioc_attr->pci_attr.chip_rev);
पूर्ण

mac_t
bfa_ioc_get_mac(काष्ठा bfa_ioc_s *ioc)
अणु
	/*
	 * Check the IOC type and वापस the appropriate MAC
	 */
	अगर (bfa_ioc_get_type(ioc) == BFA_IOC_TYPE_FCoE)
		वापस ioc->attr->fcoe_mac;
	अन्यथा
		वापस ioc->attr->mac;
पूर्ण

mac_t
bfa_ioc_get_mfg_mac(काष्ठा bfa_ioc_s *ioc)
अणु
	mac_t	m;

	m = ioc->attr->mfg_mac;
	अगर (bfa_mfg_is_old_wwn_mac_model(ioc->attr->card_type))
		m.mac[MAC_ADDRLEN - 1] += bfa_ioc_pcअगरn(ioc);
	अन्यथा
		bfa_mfg_increment_wwn_mac(&(m.mac[MAC_ADDRLEN-3]),
			bfa_ioc_pcअगरn(ioc));

	वापस m;
पूर्ण

/*
 * Send AEN notअगरication
 */
व्योम
bfa_ioc_aen_post(काष्ठा bfa_ioc_s *ioc, क्रमागत bfa_ioc_aen_event event)
अणु
	काष्ठा bfad_s *bfad = (काष्ठा bfad_s *)ioc->bfa->bfad;
	काष्ठा bfa_aen_entry_s	*aen_entry;
	क्रमागत bfa_ioc_type_e ioc_type;

	bfad_get_aen_entry(bfad, aen_entry);
	अगर (!aen_entry)
		वापस;

	ioc_type = bfa_ioc_get_type(ioc);
	चयन (ioc_type) अणु
	हाल BFA_IOC_TYPE_FC:
		aen_entry->aen_data.ioc.pwwn = ioc->attr->pwwn;
		अवरोध;
	हाल BFA_IOC_TYPE_FCoE:
		aen_entry->aen_data.ioc.pwwn = ioc->attr->pwwn;
		aen_entry->aen_data.ioc.mac = bfa_ioc_get_mac(ioc);
		अवरोध;
	हाल BFA_IOC_TYPE_LL:
		aen_entry->aen_data.ioc.mac = bfa_ioc_get_mac(ioc);
		अवरोध;
	शेष:
		WARN_ON(ioc_type != BFA_IOC_TYPE_FC);
		अवरोध;
	पूर्ण

	/* Send the AEN notअगरication */
	aen_entry->aen_data.ioc.ioc_type = ioc_type;
	bfad_im_post_venकरोr_event(aen_entry, bfad, ++ioc->ioc_aen_seq,
				  BFA_AEN_CAT_IOC, event);
पूर्ण

/*
 * Retrieve saved firmware trace from a prior IOC failure.
 */
bfa_status_t
bfa_ioc_debug_fwsave(काष्ठा bfa_ioc_s *ioc, व्योम *trcdata, पूर्णांक *trclen)
अणु
	पूर्णांक	tlen;

	अगर (ioc->dbg_fwsave_len == 0)
		वापस BFA_STATUS_ENOFSAVE;

	tlen = *trclen;
	अगर (tlen > ioc->dbg_fwsave_len)
		tlen = ioc->dbg_fwsave_len;

	स_नकल(trcdata, ioc->dbg_fwsave, tlen);
	*trclen = tlen;
	वापस BFA_STATUS_OK;
पूर्ण


/*
 * Retrieve saved firmware trace from a prior IOC failure.
 */
bfa_status_t
bfa_ioc_debug_fwtrc(काष्ठा bfa_ioc_s *ioc, व्योम *trcdata, पूर्णांक *trclen)
अणु
	u32 loff = BFA_DBG_FWTRC_OFF(bfa_ioc_portid(ioc));
	पूर्णांक tlen;
	bfa_status_t status;

	bfa_trc(ioc, *trclen);

	tlen = *trclen;
	अगर (tlen > BFA_DBG_FWTRC_LEN)
		tlen = BFA_DBG_FWTRC_LEN;

	status = bfa_ioc_smem_पढ़ो(ioc, trcdata, loff, tlen);
	*trclen = tlen;
	वापस status;
पूर्ण

अटल व्योम
bfa_ioc_send_fwsync(काष्ठा bfa_ioc_s *ioc)
अणु
	काष्ठा bfa_mbox_cmd_s cmd;
	काष्ठा bfi_ioc_ctrl_req_s *req = (काष्ठा bfi_ioc_ctrl_req_s *) cmd.msg;

	bfi_h2i_set(req->mh, BFI_MC_IOC, BFI_IOC_H2I_DBG_SYNC,
		    bfa_ioc_portid(ioc));
	req->clscode = cpu_to_be16(ioc->clscode);
	bfa_ioc_mbox_queue(ioc, &cmd);
पूर्ण

अटल व्योम
bfa_ioc_fwsync(काष्ठा bfa_ioc_s *ioc)
अणु
	u32 fwsync_iter = 1000;

	bfa_ioc_send_fwsync(ioc);

	/*
	 * After sending a fw sync mbox command रुको क्रम it to
	 * take effect.  We will not रुको क्रम a response because
	 *    1. fw_sync mbox cmd करोesn't have a response.
	 *    2. Even अगर we implement that,  पूर्णांकerrupts might not
	 *	 be enabled when we call this function.
	 * So, just keep checking अगर any mbox cmd is pending, and
	 * after रुकोing क्रम a reasonable amount of समय, go ahead.
	 * It is possible that fw has crashed and the mbox command
	 * is never acknowledged.
	 */
	जबतक (bfa_ioc_mbox_cmd_pending(ioc) && fwsync_iter > 0)
		fwsync_iter--;
पूर्ण

/*
 * Dump firmware smem
 */
bfa_status_t
bfa_ioc_debug_fwcore(काष्ठा bfa_ioc_s *ioc, व्योम *buf,
				u32 *offset, पूर्णांक *buflen)
अणु
	u32 loff;
	पूर्णांक dlen;
	bfa_status_t status;
	u32 smem_len = BFA_IOC_FW_SMEM_SIZE(ioc);

	अगर (*offset >= smem_len) अणु
		*offset = *buflen = 0;
		वापस BFA_STATUS_EINVAL;
	पूर्ण

	loff = *offset;
	dlen = *buflen;

	/*
	 * First smem पढ़ो, sync smem beक्रमe proceeding
	 * No need to sync beक्रमe पढ़ोing every chunk.
	 */
	अगर (loff == 0)
		bfa_ioc_fwsync(ioc);

	अगर ((loff + dlen) >= smem_len)
		dlen = smem_len - loff;

	status = bfa_ioc_smem_पढ़ो(ioc, buf, loff, dlen);

	अगर (status != BFA_STATUS_OK) अणु
		*offset = *buflen = 0;
		वापस status;
	पूर्ण

	*offset += dlen;

	अगर (*offset >= smem_len)
		*offset = 0;

	*buflen = dlen;

	वापस status;
पूर्ण

/*
 * Firmware statistics
 */
bfa_status_t
bfa_ioc_fw_stats_get(काष्ठा bfa_ioc_s *ioc, व्योम *stats)
अणु
	u32 loff = BFI_IOC_FWSTATS_OFF + \
		BFI_IOC_FWSTATS_SZ * (bfa_ioc_portid(ioc));
	पूर्णांक tlen;
	bfa_status_t status;

	अगर (ioc->stats_busy) अणु
		bfa_trc(ioc, ioc->stats_busy);
		वापस BFA_STATUS_DEVBUSY;
	पूर्ण
	ioc->stats_busy = BFA_TRUE;

	tlen = माप(काष्ठा bfa_fw_stats_s);
	status = bfa_ioc_smem_पढ़ो(ioc, stats, loff, tlen);

	ioc->stats_busy = BFA_FALSE;
	वापस status;
पूर्ण

bfa_status_t
bfa_ioc_fw_stats_clear(काष्ठा bfa_ioc_s *ioc)
अणु
	u32 loff = BFI_IOC_FWSTATS_OFF + \
		BFI_IOC_FWSTATS_SZ * (bfa_ioc_portid(ioc));
	पूर्णांक tlen;
	bfa_status_t status;

	अगर (ioc->stats_busy) अणु
		bfa_trc(ioc, ioc->stats_busy);
		वापस BFA_STATUS_DEVBUSY;
	पूर्ण
	ioc->stats_busy = BFA_TRUE;

	tlen = माप(काष्ठा bfa_fw_stats_s);
	status = bfa_ioc_smem_clr(ioc, loff, tlen);

	ioc->stats_busy = BFA_FALSE;
	वापस status;
पूर्ण

/*
 * Save firmware trace अगर configured.
 */
व्योम
bfa_ioc_debug_save_ftrc(काष्ठा bfa_ioc_s *ioc)
अणु
	पूर्णांक		tlen;

	अगर (ioc->dbg_fwsave_once) अणु
		ioc->dbg_fwsave_once = BFA_FALSE;
		अगर (ioc->dbg_fwsave_len) अणु
			tlen = ioc->dbg_fwsave_len;
			bfa_ioc_debug_fwtrc(ioc, ioc->dbg_fwsave, &tlen);
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Firmware failure detected. Start recovery actions.
 */
अटल व्योम
bfa_ioc_recover(काष्ठा bfa_ioc_s *ioc)
अणु
	bfa_ioc_stats(ioc, ioc_hbfails);
	ioc->stats.hb_count = ioc->hb_count;
	bfa_fsm_send_event(ioc, IOC_E_HBFAIL);
पूर्ण

/*
 *  BFA IOC PF निजी functions
 */
अटल व्योम
bfa_iocpf_समयout(व्योम *ioc_arg)
अणु
	काष्ठा bfa_ioc_s  *ioc = (काष्ठा bfa_ioc_s *) ioc_arg;

	bfa_trc(ioc, 0);
	bfa_fsm_send_event(&ioc->iocpf, IOCPF_E_TIMEOUT);
पूर्ण

अटल व्योम
bfa_iocpf_sem_समयout(व्योम *ioc_arg)
अणु
	काष्ठा bfa_ioc_s  *ioc = (काष्ठा bfa_ioc_s *) ioc_arg;

	bfa_ioc_hw_sem_get(ioc);
पूर्ण

अटल व्योम
bfa_ioc_poll_fwinit(काष्ठा bfa_ioc_s *ioc)
अणु
	u32 fwstate = bfa_ioc_get_cur_ioc_fwstate(ioc);

	bfa_trc(ioc, fwstate);

	अगर (fwstate == BFI_IOC_DISABLED) अणु
		bfa_fsm_send_event(&ioc->iocpf, IOCPF_E_FWREADY);
		वापस;
	पूर्ण

	अगर (ioc->iocpf.poll_समय >= (3 * BFA_IOC_TOV))
		bfa_iocpf_समयout(ioc);
	अन्यथा अणु
		ioc->iocpf.poll_समय += BFA_IOC_POLL_TOV;
		bfa_iocpf_poll_समयr_start(ioc);
	पूर्ण
पूर्ण

अटल व्योम
bfa_iocpf_poll_समयout(व्योम *ioc_arg)
अणु
	काष्ठा bfa_ioc_s *ioc = (काष्ठा bfa_ioc_s *) ioc_arg;

	bfa_ioc_poll_fwinit(ioc);
पूर्ण

/*
 *  bfa समयr function
 */
व्योम
bfa_समयr_beat(काष्ठा bfa_समयr_mod_s *mod)
अणु
	काष्ठा list_head *qh = &mod->समयr_q;
	काष्ठा list_head *qe, *qe_next;
	काष्ठा bfa_समयr_s *elem;
	काष्ठा list_head समयकरोut_q;

	INIT_LIST_HEAD(&समयकरोut_q);

	qe = bfa_q_next(qh);

	जबतक (qe != qh) अणु
		qe_next = bfa_q_next(qe);

		elem = (काष्ठा bfa_समयr_s *) qe;
		अगर (elem->समयout <= BFA_TIMER_FREQ) अणु
			elem->समयout = 0;
			list_del(&elem->qe);
			list_add_tail(&elem->qe, &समयकरोut_q);
		पूर्ण अन्यथा अणु
			elem->समयout -= BFA_TIMER_FREQ;
		पूर्ण

		qe = qe_next;	/* go to next elem */
	पूर्ण

	/*
	 * Pop all the समयout entries
	 */
	जबतक (!list_empty(&समयकरोut_q)) अणु
		bfa_q_deq(&समयकरोut_q, &elem);
		elem->समयrcb(elem->arg);
	पूर्ण
पूर्ण

/*
 * Should be called with lock protection
 */
व्योम
bfa_समयr_begin(काष्ठा bfa_समयr_mod_s *mod, काष्ठा bfa_समयr_s *समयr,
		    व्योम (*समयrcb) (व्योम *), व्योम *arg, अचिन्हित पूर्णांक समयout)
अणु

	WARN_ON(समयrcb == शून्य);
	WARN_ON(bfa_q_is_on_q(&mod->समयr_q, समयr));

	समयr->समयout = समयout;
	समयr->समयrcb = समयrcb;
	समयr->arg = arg;

	list_add_tail(&समयr->qe, &mod->समयr_q);
पूर्ण

/*
 * Should be called with lock protection
 */
व्योम
bfa_समयr_stop(काष्ठा bfa_समयr_s *समयr)
अणु
	WARN_ON(list_empty(&समयr->qe));

	list_del(&समयr->qe);
पूर्ण

/*
 *	ASIC block related
 */
अटल व्योम
bfa_ablk_config_swap(काष्ठा bfa_ablk_cfg_s *cfg)
अणु
	काष्ठा bfa_ablk_cfg_inst_s *cfg_inst;
	पूर्णांक i, j;
	u16	be16;

	क्रम (i = 0; i < BFA_ABLK_MAX; i++) अणु
		cfg_inst = &cfg->inst[i];
		क्रम (j = 0; j < BFA_ABLK_MAX_PFS; j++) अणु
			be16 = cfg_inst->pf_cfg[j].pers;
			cfg_inst->pf_cfg[j].pers = be16_to_cpu(be16);
			be16 = cfg_inst->pf_cfg[j].num_qpairs;
			cfg_inst->pf_cfg[j].num_qpairs = be16_to_cpu(be16);
			be16 = cfg_inst->pf_cfg[j].num_vectors;
			cfg_inst->pf_cfg[j].num_vectors = be16_to_cpu(be16);
			be16 = cfg_inst->pf_cfg[j].bw_min;
			cfg_inst->pf_cfg[j].bw_min = be16_to_cpu(be16);
			be16 = cfg_inst->pf_cfg[j].bw_max;
			cfg_inst->pf_cfg[j].bw_max = be16_to_cpu(be16);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम
bfa_ablk_isr(व्योम *cbarg, काष्ठा bfi_mbmsg_s *msg)
अणु
	काष्ठा bfa_ablk_s *ablk = (काष्ठा bfa_ablk_s *)cbarg;
	काष्ठा bfi_ablk_i2h_rsp_s *rsp = (काष्ठा bfi_ablk_i2h_rsp_s *)msg;
	bfa_ablk_cbfn_t cbfn;

	WARN_ON(msg->mh.msg_class != BFI_MC_ABLK);
	bfa_trc(ablk->ioc, msg->mh.msg_id);

	चयन (msg->mh.msg_id) अणु
	हाल BFI_ABLK_I2H_QUERY:
		अगर (rsp->status == BFA_STATUS_OK) अणु
			स_नकल(ablk->cfg, ablk->dma_addr.kva,
				माप(काष्ठा bfa_ablk_cfg_s));
			bfa_ablk_config_swap(ablk->cfg);
			ablk->cfg = शून्य;
		पूर्ण
		अवरोध;

	हाल BFI_ABLK_I2H_ADPT_CONFIG:
	हाल BFI_ABLK_I2H_PORT_CONFIG:
		/* update config port mode */
		ablk->ioc->port_mode_cfg = rsp->port_mode;
		अवरोध;

	हाल BFI_ABLK_I2H_PF_DELETE:
	हाल BFI_ABLK_I2H_PF_UPDATE:
	हाल BFI_ABLK_I2H_OPTROM_ENABLE:
	हाल BFI_ABLK_I2H_OPTROM_DISABLE:
		/* No-op */
		अवरोध;

	हाल BFI_ABLK_I2H_PF_CREATE:
		*(ablk->pcअगरn) = rsp->pcअगरn;
		ablk->pcअगरn = शून्य;
		अवरोध;

	शेष:
		WARN_ON(1);
	पूर्ण

	ablk->busy = BFA_FALSE;
	अगर (ablk->cbfn) अणु
		cbfn = ablk->cbfn;
		ablk->cbfn = शून्य;
		cbfn(ablk->cbarg, rsp->status);
	पूर्ण
पूर्ण

अटल व्योम
bfa_ablk_notअगरy(व्योम *cbarg, क्रमागत bfa_ioc_event_e event)
अणु
	काष्ठा bfa_ablk_s *ablk = (काष्ठा bfa_ablk_s *)cbarg;

	bfa_trc(ablk->ioc, event);

	चयन (event) अणु
	हाल BFA_IOC_E_ENABLED:
		WARN_ON(ablk->busy != BFA_FALSE);
		अवरोध;

	हाल BFA_IOC_E_DISABLED:
	हाल BFA_IOC_E_FAILED:
		/* Fail any pending requests */
		ablk->pcअगरn = शून्य;
		अगर (ablk->busy) अणु
			अगर (ablk->cbfn)
				ablk->cbfn(ablk->cbarg, BFA_STATUS_FAILED);
			ablk->cbfn = शून्य;
			ablk->busy = BFA_FALSE;
		पूर्ण
		अवरोध;

	शेष:
		WARN_ON(1);
		अवरोध;
	पूर्ण
पूर्ण

u32
bfa_ablk_meminfo(व्योम)
अणु
	वापस BFA_ROUNDUP(माप(काष्ठा bfa_ablk_cfg_s), BFA_DMA_ALIGN_SZ);
पूर्ण

व्योम
bfa_ablk_memclaim(काष्ठा bfa_ablk_s *ablk, u8 *dma_kva, u64 dma_pa)
अणु
	ablk->dma_addr.kva = dma_kva;
	ablk->dma_addr.pa  = dma_pa;
पूर्ण

व्योम
bfa_ablk_attach(काष्ठा bfa_ablk_s *ablk, काष्ठा bfa_ioc_s *ioc)
अणु
	ablk->ioc = ioc;

	bfa_ioc_mbox_regisr(ablk->ioc, BFI_MC_ABLK, bfa_ablk_isr, ablk);
	bfa_q_qe_init(&ablk->ioc_notअगरy);
	bfa_ioc_notअगरy_init(&ablk->ioc_notअगरy, bfa_ablk_notअगरy, ablk);
	list_add_tail(&ablk->ioc_notअगरy.qe, &ablk->ioc->notअगरy_q);
पूर्ण

bfa_status_t
bfa_ablk_query(काष्ठा bfa_ablk_s *ablk, काष्ठा bfa_ablk_cfg_s *ablk_cfg,
		bfa_ablk_cbfn_t cbfn, व्योम *cbarg)
अणु
	काष्ठा bfi_ablk_h2i_query_s *m;

	WARN_ON(!ablk_cfg);

	अगर (!bfa_ioc_is_operational(ablk->ioc)) अणु
		bfa_trc(ablk->ioc, BFA_STATUS_IOC_FAILURE);
		वापस BFA_STATUS_IOC_FAILURE;
	पूर्ण

	अगर (ablk->busy) अणु
		bfa_trc(ablk->ioc, BFA_STATUS_DEVBUSY);
		वापस  BFA_STATUS_DEVBUSY;
	पूर्ण

	ablk->cfg = ablk_cfg;
	ablk->cbfn  = cbfn;
	ablk->cbarg = cbarg;
	ablk->busy  = BFA_TRUE;

	m = (काष्ठा bfi_ablk_h2i_query_s *)ablk->mb.msg;
	bfi_h2i_set(m->mh, BFI_MC_ABLK, BFI_ABLK_H2I_QUERY,
		    bfa_ioc_portid(ablk->ioc));
	bfa_dma_be_addr_set(m->addr, ablk->dma_addr.pa);
	bfa_ioc_mbox_queue(ablk->ioc, &ablk->mb);

	वापस BFA_STATUS_OK;
पूर्ण

bfa_status_t
bfa_ablk_pf_create(काष्ठा bfa_ablk_s *ablk, u16 *pcअगरn,
		u8 port, क्रमागत bfi_pcअगरn_class personality,
		u16 bw_min, u16 bw_max,
		bfa_ablk_cbfn_t cbfn, व्योम *cbarg)
अणु
	काष्ठा bfi_ablk_h2i_pf_req_s *m;

	अगर (!bfa_ioc_is_operational(ablk->ioc)) अणु
		bfa_trc(ablk->ioc, BFA_STATUS_IOC_FAILURE);
		वापस BFA_STATUS_IOC_FAILURE;
	पूर्ण

	अगर (ablk->busy) अणु
		bfa_trc(ablk->ioc, BFA_STATUS_DEVBUSY);
		वापस  BFA_STATUS_DEVBUSY;
	पूर्ण

	ablk->pcअगरn = pcअगरn;
	ablk->cbfn = cbfn;
	ablk->cbarg = cbarg;
	ablk->busy  = BFA_TRUE;

	m = (काष्ठा bfi_ablk_h2i_pf_req_s *)ablk->mb.msg;
	bfi_h2i_set(m->mh, BFI_MC_ABLK, BFI_ABLK_H2I_PF_CREATE,
		    bfa_ioc_portid(ablk->ioc));
	m->pers = cpu_to_be16((u16)personality);
	m->bw_min = cpu_to_be16(bw_min);
	m->bw_max = cpu_to_be16(bw_max);
	m->port = port;
	bfa_ioc_mbox_queue(ablk->ioc, &ablk->mb);

	वापस BFA_STATUS_OK;
पूर्ण

bfa_status_t
bfa_ablk_pf_delete(काष्ठा bfa_ablk_s *ablk, पूर्णांक pcअगरn,
		bfa_ablk_cbfn_t cbfn, व्योम *cbarg)
अणु
	काष्ठा bfi_ablk_h2i_pf_req_s *m;

	अगर (!bfa_ioc_is_operational(ablk->ioc)) अणु
		bfa_trc(ablk->ioc, BFA_STATUS_IOC_FAILURE);
		वापस BFA_STATUS_IOC_FAILURE;
	पूर्ण

	अगर (ablk->busy) अणु
		bfa_trc(ablk->ioc, BFA_STATUS_DEVBUSY);
		वापस  BFA_STATUS_DEVBUSY;
	पूर्ण

	ablk->cbfn  = cbfn;
	ablk->cbarg = cbarg;
	ablk->busy  = BFA_TRUE;

	m = (काष्ठा bfi_ablk_h2i_pf_req_s *)ablk->mb.msg;
	bfi_h2i_set(m->mh, BFI_MC_ABLK, BFI_ABLK_H2I_PF_DELETE,
		    bfa_ioc_portid(ablk->ioc));
	m->pcअगरn = (u8)pcअगरn;
	bfa_ioc_mbox_queue(ablk->ioc, &ablk->mb);

	वापस BFA_STATUS_OK;
पूर्ण

bfa_status_t
bfa_ablk_adapter_config(काष्ठा bfa_ablk_s *ablk, क्रमागत bfa_mode_s mode,
		पूर्णांक max_pf, पूर्णांक max_vf, bfa_ablk_cbfn_t cbfn, व्योम *cbarg)
अणु
	काष्ठा bfi_ablk_h2i_cfg_req_s *m;

	अगर (!bfa_ioc_is_operational(ablk->ioc)) अणु
		bfa_trc(ablk->ioc, BFA_STATUS_IOC_FAILURE);
		वापस BFA_STATUS_IOC_FAILURE;
	पूर्ण

	अगर (ablk->busy) अणु
		bfa_trc(ablk->ioc, BFA_STATUS_DEVBUSY);
		वापस  BFA_STATUS_DEVBUSY;
	पूर्ण

	ablk->cbfn  = cbfn;
	ablk->cbarg = cbarg;
	ablk->busy  = BFA_TRUE;

	m = (काष्ठा bfi_ablk_h2i_cfg_req_s *)ablk->mb.msg;
	bfi_h2i_set(m->mh, BFI_MC_ABLK, BFI_ABLK_H2I_ADPT_CONFIG,
		    bfa_ioc_portid(ablk->ioc));
	m->mode = (u8)mode;
	m->max_pf = (u8)max_pf;
	m->max_vf = (u8)max_vf;
	bfa_ioc_mbox_queue(ablk->ioc, &ablk->mb);

	वापस BFA_STATUS_OK;
पूर्ण

bfa_status_t
bfa_ablk_port_config(काष्ठा bfa_ablk_s *ablk, पूर्णांक port, क्रमागत bfa_mode_s mode,
		पूर्णांक max_pf, पूर्णांक max_vf, bfa_ablk_cbfn_t cbfn, व्योम *cbarg)
अणु
	काष्ठा bfi_ablk_h2i_cfg_req_s *m;

	अगर (!bfa_ioc_is_operational(ablk->ioc)) अणु
		bfa_trc(ablk->ioc, BFA_STATUS_IOC_FAILURE);
		वापस BFA_STATUS_IOC_FAILURE;
	पूर्ण

	अगर (ablk->busy) अणु
		bfa_trc(ablk->ioc, BFA_STATUS_DEVBUSY);
		वापस  BFA_STATUS_DEVBUSY;
	पूर्ण

	ablk->cbfn  = cbfn;
	ablk->cbarg = cbarg;
	ablk->busy  = BFA_TRUE;

	m = (काष्ठा bfi_ablk_h2i_cfg_req_s *)ablk->mb.msg;
	bfi_h2i_set(m->mh, BFI_MC_ABLK, BFI_ABLK_H2I_PORT_CONFIG,
		bfa_ioc_portid(ablk->ioc));
	m->port = (u8)port;
	m->mode = (u8)mode;
	m->max_pf = (u8)max_pf;
	m->max_vf = (u8)max_vf;
	bfa_ioc_mbox_queue(ablk->ioc, &ablk->mb);

	वापस BFA_STATUS_OK;
पूर्ण

bfa_status_t
bfa_ablk_pf_update(काष्ठा bfa_ablk_s *ablk, पूर्णांक pcअगरn, u16 bw_min,
		   u16 bw_max, bfa_ablk_cbfn_t cbfn, व्योम *cbarg)
अणु
	काष्ठा bfi_ablk_h2i_pf_req_s *m;

	अगर (!bfa_ioc_is_operational(ablk->ioc)) अणु
		bfa_trc(ablk->ioc, BFA_STATUS_IOC_FAILURE);
		वापस BFA_STATUS_IOC_FAILURE;
	पूर्ण

	अगर (ablk->busy) अणु
		bfa_trc(ablk->ioc, BFA_STATUS_DEVBUSY);
		वापस  BFA_STATUS_DEVBUSY;
	पूर्ण

	ablk->cbfn  = cbfn;
	ablk->cbarg = cbarg;
	ablk->busy  = BFA_TRUE;

	m = (काष्ठा bfi_ablk_h2i_pf_req_s *)ablk->mb.msg;
	bfi_h2i_set(m->mh, BFI_MC_ABLK, BFI_ABLK_H2I_PF_UPDATE,
		bfa_ioc_portid(ablk->ioc));
	m->pcअगरn = (u8)pcअगरn;
	m->bw_min = cpu_to_be16(bw_min);
	m->bw_max = cpu_to_be16(bw_max);
	bfa_ioc_mbox_queue(ablk->ioc, &ablk->mb);

	वापस BFA_STATUS_OK;
पूर्ण

bfa_status_t
bfa_ablk_optrom_en(काष्ठा bfa_ablk_s *ablk, bfa_ablk_cbfn_t cbfn, व्योम *cbarg)
अणु
	काष्ठा bfi_ablk_h2i_optrom_s *m;

	अगर (!bfa_ioc_is_operational(ablk->ioc)) अणु
		bfa_trc(ablk->ioc, BFA_STATUS_IOC_FAILURE);
		वापस BFA_STATUS_IOC_FAILURE;
	पूर्ण

	अगर (ablk->busy) अणु
		bfa_trc(ablk->ioc, BFA_STATUS_DEVBUSY);
		वापस  BFA_STATUS_DEVBUSY;
	पूर्ण

	ablk->cbfn  = cbfn;
	ablk->cbarg = cbarg;
	ablk->busy  = BFA_TRUE;

	m = (काष्ठा bfi_ablk_h2i_optrom_s *)ablk->mb.msg;
	bfi_h2i_set(m->mh, BFI_MC_ABLK, BFI_ABLK_H2I_OPTROM_ENABLE,
		bfa_ioc_portid(ablk->ioc));
	bfa_ioc_mbox_queue(ablk->ioc, &ablk->mb);

	वापस BFA_STATUS_OK;
पूर्ण

bfa_status_t
bfa_ablk_optrom_dis(काष्ठा bfa_ablk_s *ablk, bfa_ablk_cbfn_t cbfn, व्योम *cbarg)
अणु
	काष्ठा bfi_ablk_h2i_optrom_s *m;

	अगर (!bfa_ioc_is_operational(ablk->ioc)) अणु
		bfa_trc(ablk->ioc, BFA_STATUS_IOC_FAILURE);
		वापस BFA_STATUS_IOC_FAILURE;
	पूर्ण

	अगर (ablk->busy) अणु
		bfa_trc(ablk->ioc, BFA_STATUS_DEVBUSY);
		वापस  BFA_STATUS_DEVBUSY;
	पूर्ण

	ablk->cbfn  = cbfn;
	ablk->cbarg = cbarg;
	ablk->busy  = BFA_TRUE;

	m = (काष्ठा bfi_ablk_h2i_optrom_s *)ablk->mb.msg;
	bfi_h2i_set(m->mh, BFI_MC_ABLK, BFI_ABLK_H2I_OPTROM_DISABLE,
		bfa_ioc_portid(ablk->ioc));
	bfa_ioc_mbox_queue(ablk->ioc, &ablk->mb);

	वापस BFA_STATUS_OK;
पूर्ण

/*
 *	SFP module specअगरic
 */

/* क्रमward declarations */
अटल व्योम bfa_sfp_getdata_send(काष्ठा bfa_sfp_s *sfp);
अटल व्योम bfa_sfp_media_get(काष्ठा bfa_sfp_s *sfp);
अटल bfa_status_t bfa_sfp_speed_valid(काष्ठा bfa_sfp_s *sfp,
				क्रमागत bfa_port_speed portspeed);

अटल व्योम
bfa_cb_sfp_show(काष्ठा bfa_sfp_s *sfp)
अणु
	bfa_trc(sfp, sfp->lock);
	अगर (sfp->cbfn)
		sfp->cbfn(sfp->cbarg, sfp->status);
	sfp->lock = 0;
	sfp->cbfn = शून्य;
पूर्ण

अटल व्योम
bfa_cb_sfp_state_query(काष्ठा bfa_sfp_s *sfp)
अणु
	bfa_trc(sfp, sfp->portspeed);
	अगर (sfp->media) अणु
		bfa_sfp_media_get(sfp);
		अगर (sfp->state_query_cbfn)
			sfp->state_query_cbfn(sfp->state_query_cbarg,
					sfp->status);
		sfp->media = शून्य;
	पूर्ण

	अगर (sfp->portspeed) अणु
		sfp->status = bfa_sfp_speed_valid(sfp, sfp->portspeed);
		अगर (sfp->state_query_cbfn)
			sfp->state_query_cbfn(sfp->state_query_cbarg,
					sfp->status);
		sfp->portspeed = BFA_PORT_SPEED_UNKNOWN;
	पूर्ण

	sfp->state_query_lock = 0;
	sfp->state_query_cbfn = शून्य;
पूर्ण

/*
 *	IOC event handler.
 */
अटल व्योम
bfa_sfp_notअगरy(व्योम *sfp_arg, क्रमागत bfa_ioc_event_e event)
अणु
	काष्ठा bfa_sfp_s *sfp = sfp_arg;

	bfa_trc(sfp, event);
	bfa_trc(sfp, sfp->lock);
	bfa_trc(sfp, sfp->state_query_lock);

	चयन (event) अणु
	हाल BFA_IOC_E_DISABLED:
	हाल BFA_IOC_E_FAILED:
		अगर (sfp->lock) अणु
			sfp->status = BFA_STATUS_IOC_FAILURE;
			bfa_cb_sfp_show(sfp);
		पूर्ण

		अगर (sfp->state_query_lock) अणु
			sfp->status = BFA_STATUS_IOC_FAILURE;
			bfa_cb_sfp_state_query(sfp);
		पूर्ण
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण
पूर्ण

/*
 * SFP's State Change Notअगरication post to AEN
 */
अटल व्योम
bfa_sfp_scn_aen_post(काष्ठा bfa_sfp_s *sfp, काष्ठा bfi_sfp_scn_s *rsp)
अणु
	काष्ठा bfad_s *bfad = (काष्ठा bfad_s *)sfp->ioc->bfa->bfad;
	काष्ठा bfa_aen_entry_s  *aen_entry;
	क्रमागत bfa_port_aen_event aen_evt = 0;

	bfa_trc(sfp, (((u64)rsp->pomlvl) << 16) | (((u64)rsp->sfpid) << 8) |
		      ((u64)rsp->event));

	bfad_get_aen_entry(bfad, aen_entry);
	अगर (!aen_entry)
		वापस;

	aen_entry->aen_data.port.ioc_type = bfa_ioc_get_type(sfp->ioc);
	aen_entry->aen_data.port.pwwn = sfp->ioc->attr->pwwn;
	aen_entry->aen_data.port.mac = bfa_ioc_get_mac(sfp->ioc);

	चयन (rsp->event) अणु
	हाल BFA_SFP_SCN_INSERTED:
		aen_evt = BFA_PORT_AEN_SFP_INSERT;
		अवरोध;
	हाल BFA_SFP_SCN_REMOVED:
		aen_evt = BFA_PORT_AEN_SFP_REMOVE;
		अवरोध;
	हाल BFA_SFP_SCN_FAILED:
		aen_evt = BFA_PORT_AEN_SFP_ACCESS_ERROR;
		अवरोध;
	हाल BFA_SFP_SCN_UNSUPPORT:
		aen_evt = BFA_PORT_AEN_SFP_UNSUPPORT;
		अवरोध;
	हाल BFA_SFP_SCN_POM:
		aen_evt = BFA_PORT_AEN_SFP_POM;
		aen_entry->aen_data.port.level = rsp->pomlvl;
		अवरोध;
	शेष:
		bfa_trc(sfp, rsp->event);
		WARN_ON(1);
	पूर्ण

	/* Send the AEN notअगरication */
	bfad_im_post_venकरोr_event(aen_entry, bfad, ++sfp->ioc->ioc_aen_seq,
				  BFA_AEN_CAT_PORT, aen_evt);
पूर्ण

/*
 *	SFP get data send
 */
अटल व्योम
bfa_sfp_getdata_send(काष्ठा bfa_sfp_s *sfp)
अणु
	काष्ठा bfi_sfp_req_s *req = (काष्ठा bfi_sfp_req_s *)sfp->mbcmd.msg;

	bfa_trc(sfp, req->memtype);

	/* build host command */
	bfi_h2i_set(req->mh, BFI_MC_SFP, BFI_SFP_H2I_SHOW,
			bfa_ioc_portid(sfp->ioc));

	/* send mbox cmd */
	bfa_ioc_mbox_queue(sfp->ioc, &sfp->mbcmd);
पूर्ण

/*
 *	SFP is valid, पढ़ो sfp data
 */
अटल व्योम
bfa_sfp_getdata(काष्ठा bfa_sfp_s *sfp, क्रमागत bfi_sfp_mem_e memtype)
अणु
	काष्ठा bfi_sfp_req_s *req = (काष्ठा bfi_sfp_req_s *)sfp->mbcmd.msg;

	WARN_ON(sfp->lock != 0);
	bfa_trc(sfp, sfp->state);

	sfp->lock = 1;
	sfp->memtype = memtype;
	req->memtype = memtype;

	/* Setup SG list */
	bfa_alen_set(&req->alen, माप(काष्ठा sfp_mem_s), sfp->dbuf_pa);

	bfa_sfp_getdata_send(sfp);
पूर्ण

/*
 *	SFP scn handler
 */
अटल व्योम
bfa_sfp_scn(काष्ठा bfa_sfp_s *sfp, काष्ठा bfi_mbmsg_s *msg)
अणु
	काष्ठा bfi_sfp_scn_s *rsp = (काष्ठा bfi_sfp_scn_s *) msg;

	चयन (rsp->event) अणु
	हाल BFA_SFP_SCN_INSERTED:
		sfp->state = BFA_SFP_STATE_INSERTED;
		sfp->data_valid = 0;
		bfa_sfp_scn_aen_post(sfp, rsp);
		अवरोध;
	हाल BFA_SFP_SCN_REMOVED:
		sfp->state = BFA_SFP_STATE_REMOVED;
		sfp->data_valid = 0;
		bfa_sfp_scn_aen_post(sfp, rsp);
		अवरोध;
	हाल BFA_SFP_SCN_FAILED:
		sfp->state = BFA_SFP_STATE_FAILED;
		sfp->data_valid = 0;
		bfa_sfp_scn_aen_post(sfp, rsp);
		अवरोध;
	हाल BFA_SFP_SCN_UNSUPPORT:
		sfp->state = BFA_SFP_STATE_UNSUPPORT;
		bfa_sfp_scn_aen_post(sfp, rsp);
		अगर (!sfp->lock)
			bfa_sfp_getdata(sfp, BFI_SFP_MEM_ALL);
		अवरोध;
	हाल BFA_SFP_SCN_POM:
		bfa_sfp_scn_aen_post(sfp, rsp);
		अवरोध;
	हाल BFA_SFP_SCN_VALID:
		sfp->state = BFA_SFP_STATE_VALID;
		अगर (!sfp->lock)
			bfa_sfp_getdata(sfp, BFI_SFP_MEM_ALL);
		अवरोध;
	शेष:
		bfa_trc(sfp, rsp->event);
		WARN_ON(1);
	पूर्ण
पूर्ण

/*
 * SFP show complete
 */
अटल व्योम
bfa_sfp_show_comp(काष्ठा bfa_sfp_s *sfp, काष्ठा bfi_mbmsg_s *msg)
अणु
	काष्ठा bfi_sfp_rsp_s *rsp = (काष्ठा bfi_sfp_rsp_s *) msg;

	अगर (!sfp->lock) अणु
		/*
		 * receiving response after ioc failure
		 */
		bfa_trc(sfp, sfp->lock);
		वापस;
	पूर्ण

	bfa_trc(sfp, rsp->status);
	अगर (rsp->status == BFA_STATUS_OK) अणु
		sfp->data_valid = 1;
		अगर (sfp->state == BFA_SFP_STATE_VALID)
			sfp->status = BFA_STATUS_OK;
		अन्यथा अगर (sfp->state == BFA_SFP_STATE_UNSUPPORT)
			sfp->status = BFA_STATUS_SFP_UNSUPP;
		अन्यथा
			bfa_trc(sfp, sfp->state);
	पूर्ण अन्यथा अणु
		sfp->data_valid = 0;
		sfp->status = rsp->status;
		/* sfpshow shouldn't change sfp state */
	पूर्ण

	bfa_trc(sfp, sfp->memtype);
	अगर (sfp->memtype == BFI_SFP_MEM_DIAGEXT) अणु
		bfa_trc(sfp, sfp->data_valid);
		अगर (sfp->data_valid) अणु
			u32	size = माप(काष्ठा sfp_mem_s);
			u8 *des = (u8 *)(sfp->sfpmem);
			स_नकल(des, sfp->dbuf_kva, size);
		पूर्ण
		/*
		 * Queue completion callback.
		 */
		bfa_cb_sfp_show(sfp);
	पूर्ण अन्यथा
		sfp->lock = 0;

	bfa_trc(sfp, sfp->state_query_lock);
	अगर (sfp->state_query_lock) अणु
		sfp->state = rsp->state;
		/* Complete callback */
		bfa_cb_sfp_state_query(sfp);
	पूर्ण
पूर्ण

/*
 *	SFP query fw sfp state
 */
अटल व्योम
bfa_sfp_state_query(काष्ठा bfa_sfp_s *sfp)
अणु
	काष्ठा bfi_sfp_req_s *req = (काष्ठा bfi_sfp_req_s *)sfp->mbcmd.msg;

	/* Should not be करोing query अगर not in _INIT state */
	WARN_ON(sfp->state != BFA_SFP_STATE_INIT);
	WARN_ON(sfp->state_query_lock != 0);
	bfa_trc(sfp, sfp->state);

	sfp->state_query_lock = 1;
	req->memtype = 0;

	अगर (!sfp->lock)
		bfa_sfp_getdata(sfp, BFI_SFP_MEM_ALL);
पूर्ण

अटल व्योम
bfa_sfp_media_get(काष्ठा bfa_sfp_s *sfp)
अणु
	क्रमागत bfa_defs_sfp_media_e *media = sfp->media;

	*media = BFA_SFP_MEDIA_UNKNOWN;

	अगर (sfp->state == BFA_SFP_STATE_UNSUPPORT)
		*media = BFA_SFP_MEDIA_UNSUPPORT;
	अन्यथा अगर (sfp->state == BFA_SFP_STATE_VALID) अणु
		जोड़ sfp_xcvr_e10g_code_u e10g;
		काष्ठा sfp_mem_s *sfpmem = (काष्ठा sfp_mem_s *)sfp->dbuf_kva;
		u16 xmtr_tech = (sfpmem->srlid_base.xcvr[4] & 0x3) << 7 |
				(sfpmem->srlid_base.xcvr[5] >> 1);

		e10g.b = sfpmem->srlid_base.xcvr[0];
		bfa_trc(sfp, e10g.b);
		bfa_trc(sfp, xmtr_tech);
		/* check fc transmitter tech */
		अगर ((xmtr_tech & SFP_XMTR_TECH_CU) ||
		    (xmtr_tech & SFP_XMTR_TECH_CP) ||
		    (xmtr_tech & SFP_XMTR_TECH_CA))
			*media = BFA_SFP_MEDIA_CU;
		अन्यथा अगर ((xmtr_tech & SFP_XMTR_TECH_EL_INTRA) ||
			 (xmtr_tech & SFP_XMTR_TECH_EL_INTER))
			*media = BFA_SFP_MEDIA_EL;
		अन्यथा अगर ((xmtr_tech & SFP_XMTR_TECH_LL) ||
			 (xmtr_tech & SFP_XMTR_TECH_LC))
			*media = BFA_SFP_MEDIA_LW;
		अन्यथा अगर ((xmtr_tech & SFP_XMTR_TECH_SL) ||
			 (xmtr_tech & SFP_XMTR_TECH_SN) ||
			 (xmtr_tech & SFP_XMTR_TECH_SA))
			*media = BFA_SFP_MEDIA_SW;
		/* Check 10G Ethernet Compilance code */
		अन्यथा अगर (e10g.r.e10g_sr)
			*media = BFA_SFP_MEDIA_SW;
		अन्यथा अगर (e10g.r.e10g_lrm && e10g.r.e10g_lr)
			*media = BFA_SFP_MEDIA_LW;
		अन्यथा अगर (e10g.r.e10g_unall)
			*media = BFA_SFP_MEDIA_UNKNOWN;
		अन्यथा
			bfa_trc(sfp, 0);
	पूर्ण अन्यथा
		bfa_trc(sfp, sfp->state);
पूर्ण

अटल bfa_status_t
bfa_sfp_speed_valid(काष्ठा bfa_sfp_s *sfp, क्रमागत bfa_port_speed portspeed)
अणु
	काष्ठा sfp_mem_s *sfpmem = (काष्ठा sfp_mem_s *)sfp->dbuf_kva;
	काष्ठा sfp_xcvr_s *xcvr = (काष्ठा sfp_xcvr_s *) sfpmem->srlid_base.xcvr;
	जोड़ sfp_xcvr_fc3_code_u fc3 = xcvr->fc3;
	जोड़ sfp_xcvr_e10g_code_u e10g = xcvr->e10g;

	अगर (portspeed == BFA_PORT_SPEED_10GBPS) अणु
		अगर (e10g.r.e10g_sr || e10g.r.e10g_lr)
			वापस BFA_STATUS_OK;
		अन्यथा अणु
			bfa_trc(sfp, e10g.b);
			वापस BFA_STATUS_UNSUPP_SPEED;
		पूर्ण
	पूर्ण
	अगर (((portspeed & BFA_PORT_SPEED_16GBPS) && fc3.r.mb1600) ||
	    ((portspeed & BFA_PORT_SPEED_8GBPS) && fc3.r.mb800) ||
	    ((portspeed & BFA_PORT_SPEED_4GBPS) && fc3.r.mb400) ||
	    ((portspeed & BFA_PORT_SPEED_2GBPS) && fc3.r.mb200) ||
	    ((portspeed & BFA_PORT_SPEED_1GBPS) && fc3.r.mb100))
		वापस BFA_STATUS_OK;
	अन्यथा अणु
		bfa_trc(sfp, portspeed);
		bfa_trc(sfp, fc3.b);
		bfa_trc(sfp, e10g.b);
		वापस BFA_STATUS_UNSUPP_SPEED;
	पूर्ण
पूर्ण

/*
 *	SFP hmbox handler
 */
व्योम
bfa_sfp_पूर्णांकr(व्योम *sfparg, काष्ठा bfi_mbmsg_s *msg)
अणु
	काष्ठा bfa_sfp_s *sfp = sfparg;

	चयन (msg->mh.msg_id) अणु
	हाल BFI_SFP_I2H_SHOW:
		bfa_sfp_show_comp(sfp, msg);
		अवरोध;

	हाल BFI_SFP_I2H_SCN:
		bfa_sfp_scn(sfp, msg);
		अवरोध;

	शेष:
		bfa_trc(sfp, msg->mh.msg_id);
		WARN_ON(1);
	पूर्ण
पूर्ण

/*
 *	Return DMA memory needed by sfp module.
 */
u32
bfa_sfp_meminfo(व्योम)
अणु
	वापस BFA_ROUNDUP(माप(काष्ठा sfp_mem_s), BFA_DMA_ALIGN_SZ);
पूर्ण

/*
 *	Attach भव and physical memory क्रम SFP.
 */
व्योम
bfa_sfp_attach(काष्ठा bfa_sfp_s *sfp, काष्ठा bfa_ioc_s *ioc, व्योम *dev,
		काष्ठा bfa_trc_mod_s *trcmod)
अणु
	sfp->dev = dev;
	sfp->ioc = ioc;
	sfp->trcmod = trcmod;

	sfp->cbfn = शून्य;
	sfp->cbarg = शून्य;
	sfp->sfpmem = शून्य;
	sfp->lock = 0;
	sfp->data_valid = 0;
	sfp->state = BFA_SFP_STATE_INIT;
	sfp->state_query_lock = 0;
	sfp->state_query_cbfn = शून्य;
	sfp->state_query_cbarg = शून्य;
	sfp->media = शून्य;
	sfp->portspeed = BFA_PORT_SPEED_UNKNOWN;
	sfp->is_elb = BFA_FALSE;

	bfa_ioc_mbox_regisr(sfp->ioc, BFI_MC_SFP, bfa_sfp_पूर्णांकr, sfp);
	bfa_q_qe_init(&sfp->ioc_notअगरy);
	bfa_ioc_notअगरy_init(&sfp->ioc_notअगरy, bfa_sfp_notअगरy, sfp);
	list_add_tail(&sfp->ioc_notअगरy.qe, &sfp->ioc->notअगरy_q);
पूर्ण

/*
 *	Claim Memory क्रम SFP
 */
व्योम
bfa_sfp_memclaim(काष्ठा bfa_sfp_s *sfp, u8 *dm_kva, u64 dm_pa)
अणु
	sfp->dbuf_kva   = dm_kva;
	sfp->dbuf_pa    = dm_pa;
	स_रखो(sfp->dbuf_kva, 0, माप(काष्ठा sfp_mem_s));

	dm_kva += BFA_ROUNDUP(माप(काष्ठा sfp_mem_s), BFA_DMA_ALIGN_SZ);
	dm_pa += BFA_ROUNDUP(माप(काष्ठा sfp_mem_s), BFA_DMA_ALIGN_SZ);
पूर्ण

/*
 * Show SFP eeprom content
 *
 * @param[in] sfp   - bfa sfp module
 *
 * @param[out] sfpmem - sfp eeprom data
 *
 */
bfa_status_t
bfa_sfp_show(काष्ठा bfa_sfp_s *sfp, काष्ठा sfp_mem_s *sfpmem,
		bfa_cb_sfp_t cbfn, व्योम *cbarg)
अणु

	अगर (!bfa_ioc_is_operational(sfp->ioc)) अणु
		bfa_trc(sfp, 0);
		वापस BFA_STATUS_IOC_NON_OP;
	पूर्ण

	अगर (sfp->lock) अणु
		bfa_trc(sfp, 0);
		वापस BFA_STATUS_DEVBUSY;
	पूर्ण

	sfp->cbfn = cbfn;
	sfp->cbarg = cbarg;
	sfp->sfpmem = sfpmem;

	bfa_sfp_getdata(sfp, BFI_SFP_MEM_DIAGEXT);
	वापस BFA_STATUS_OK;
पूर्ण

/*
 * Return SFP Media type
 *
 * @param[in] sfp   - bfa sfp module
 *
 * @param[out] media - port speed from user
 *
 */
bfa_status_t
bfa_sfp_media(काष्ठा bfa_sfp_s *sfp, क्रमागत bfa_defs_sfp_media_e *media,
		bfa_cb_sfp_t cbfn, व्योम *cbarg)
अणु
	अगर (!bfa_ioc_is_operational(sfp->ioc)) अणु
		bfa_trc(sfp, 0);
		वापस BFA_STATUS_IOC_NON_OP;
	पूर्ण

	sfp->media = media;
	अगर (sfp->state == BFA_SFP_STATE_INIT) अणु
		अगर (sfp->state_query_lock) अणु
			bfa_trc(sfp, 0);
			वापस BFA_STATUS_DEVBUSY;
		पूर्ण अन्यथा अणु
			sfp->state_query_cbfn = cbfn;
			sfp->state_query_cbarg = cbarg;
			bfa_sfp_state_query(sfp);
			वापस BFA_STATUS_SFP_NOT_READY;
		पूर्ण
	पूर्ण

	bfa_sfp_media_get(sfp);
	वापस BFA_STATUS_OK;
पूर्ण

/*
 * Check अगर user set port speed is allowed by the SFP
 *
 * @param[in] sfp   - bfa sfp module
 * @param[in] portspeed - port speed from user
 *
 */
bfa_status_t
bfa_sfp_speed(काष्ठा bfa_sfp_s *sfp, क्रमागत bfa_port_speed portspeed,
		bfa_cb_sfp_t cbfn, व्योम *cbarg)
अणु
	WARN_ON(portspeed == BFA_PORT_SPEED_UNKNOWN);

	अगर (!bfa_ioc_is_operational(sfp->ioc))
		वापस BFA_STATUS_IOC_NON_OP;

	/* For Mezz card, all speed is allowed */
	अगर (bfa_mfg_is_mezz(sfp->ioc->attr->card_type))
		वापस BFA_STATUS_OK;

	/* Check SFP state */
	sfp->portspeed = portspeed;
	अगर (sfp->state == BFA_SFP_STATE_INIT) अणु
		अगर (sfp->state_query_lock) अणु
			bfa_trc(sfp, 0);
			वापस BFA_STATUS_DEVBUSY;
		पूर्ण अन्यथा अणु
			sfp->state_query_cbfn = cbfn;
			sfp->state_query_cbarg = cbarg;
			bfa_sfp_state_query(sfp);
			वापस BFA_STATUS_SFP_NOT_READY;
		पूर्ण
	पूर्ण

	अगर (sfp->state == BFA_SFP_STATE_REMOVED ||
	    sfp->state == BFA_SFP_STATE_FAILED) अणु
		bfa_trc(sfp, sfp->state);
		वापस BFA_STATUS_NO_SFP_DEV;
	पूर्ण

	अगर (sfp->state == BFA_SFP_STATE_INSERTED) अणु
		bfa_trc(sfp, sfp->state);
		वापस BFA_STATUS_DEVBUSY;  /* sfp is पढ़ोing data */
	पूर्ण

	/* For eloopback, all speed is allowed */
	अगर (sfp->is_elb)
		वापस BFA_STATUS_OK;

	वापस bfa_sfp_speed_valid(sfp, portspeed);
पूर्ण

/*
 *	Flash module specअगरic
 */

/*
 * FLASH DMA buffer should be big enough to hold both MFG block and
 * asic block(64k) at the same समय and also should be 2k aligned to
 * aव्योम ग_लिखो segement to cross sector boundary.
 */
#घोषणा BFA_FLASH_SEG_SZ	2048
#घोषणा BFA_FLASH_DMA_BUF_SZ	\
	BFA_ROUNDUP(0x010000 + माप(काष्ठा bfa_mfg_block_s), BFA_FLASH_SEG_SZ)

अटल व्योम
bfa_flash_aen_audit_post(काष्ठा bfa_ioc_s *ioc, क्रमागत bfa_audit_aen_event event,
			पूर्णांक inst, पूर्णांक type)
अणु
	काष्ठा bfad_s *bfad = (काष्ठा bfad_s *)ioc->bfa->bfad;
	काष्ठा bfa_aen_entry_s  *aen_entry;

	bfad_get_aen_entry(bfad, aen_entry);
	अगर (!aen_entry)
		वापस;

	aen_entry->aen_data.audit.pwwn = ioc->attr->pwwn;
	aen_entry->aen_data.audit.partition_inst = inst;
	aen_entry->aen_data.audit.partition_type = type;

	/* Send the AEN notअगरication */
	bfad_im_post_venकरोr_event(aen_entry, bfad, ++ioc->ioc_aen_seq,
				  BFA_AEN_CAT_AUDIT, event);
पूर्ण

अटल व्योम
bfa_flash_cb(काष्ठा bfa_flash_s *flash)
अणु
	flash->op_busy = 0;
	अगर (flash->cbfn)
		flash->cbfn(flash->cbarg, flash->status);
पूर्ण

अटल व्योम
bfa_flash_notअगरy(व्योम *cbarg, क्रमागत bfa_ioc_event_e event)
अणु
	काष्ठा bfa_flash_s	*flash = cbarg;

	bfa_trc(flash, event);
	चयन (event) अणु
	हाल BFA_IOC_E_DISABLED:
	हाल BFA_IOC_E_FAILED:
		अगर (flash->op_busy) अणु
			flash->status = BFA_STATUS_IOC_FAILURE;
			flash->cbfn(flash->cbarg, flash->status);
			flash->op_busy = 0;
		पूर्ण
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण
पूर्ण

/*
 * Send flash attribute query request.
 *
 * @param[in] cbarg - callback argument
 */
अटल व्योम
bfa_flash_query_send(व्योम *cbarg)
अणु
	काष्ठा bfa_flash_s *flash = cbarg;
	काष्ठा bfi_flash_query_req_s *msg =
			(काष्ठा bfi_flash_query_req_s *) flash->mb.msg;

	bfi_h2i_set(msg->mh, BFI_MC_FLASH, BFI_FLASH_H2I_QUERY_REQ,
		bfa_ioc_portid(flash->ioc));
	bfa_alen_set(&msg->alen, माप(काष्ठा bfa_flash_attr_s),
		flash->dbuf_pa);
	bfa_ioc_mbox_queue(flash->ioc, &flash->mb);
पूर्ण

/*
 * Send flash ग_लिखो request.
 *
 * @param[in] cbarg - callback argument
 */
अटल व्योम
bfa_flash_ग_लिखो_send(काष्ठा bfa_flash_s *flash)
अणु
	काष्ठा bfi_flash_ग_लिखो_req_s *msg =
			(काष्ठा bfi_flash_ग_लिखो_req_s *) flash->mb.msg;
	u32	len;

	msg->type = be32_to_cpu(flash->type);
	msg->instance = flash->instance;
	msg->offset = be32_to_cpu(flash->addr_off + flash->offset);
	len = (flash->residue < BFA_FLASH_DMA_BUF_SZ) ?
		flash->residue : BFA_FLASH_DMA_BUF_SZ;
	msg->length = be32_to_cpu(len);

	/* indicate अगर it's the last msg of the whole ग_लिखो operation */
	msg->last = (len == flash->residue) ? 1 : 0;

	bfi_h2i_set(msg->mh, BFI_MC_FLASH, BFI_FLASH_H2I_WRITE_REQ,
			bfa_ioc_portid(flash->ioc));
	bfa_alen_set(&msg->alen, len, flash->dbuf_pa);
	स_नकल(flash->dbuf_kva, flash->ubuf + flash->offset, len);
	bfa_ioc_mbox_queue(flash->ioc, &flash->mb);

	flash->residue -= len;
	flash->offset += len;
पूर्ण

/*
 * Send flash पढ़ो request.
 *
 * @param[in] cbarg - callback argument
 */
अटल व्योम
bfa_flash_पढ़ो_send(व्योम *cbarg)
अणु
	काष्ठा bfa_flash_s *flash = cbarg;
	काष्ठा bfi_flash_पढ़ो_req_s *msg =
			(काष्ठा bfi_flash_पढ़ो_req_s *) flash->mb.msg;
	u32	len;

	msg->type = be32_to_cpu(flash->type);
	msg->instance = flash->instance;
	msg->offset = be32_to_cpu(flash->addr_off + flash->offset);
	len = (flash->residue < BFA_FLASH_DMA_BUF_SZ) ?
			flash->residue : BFA_FLASH_DMA_BUF_SZ;
	msg->length = be32_to_cpu(len);
	bfi_h2i_set(msg->mh, BFI_MC_FLASH, BFI_FLASH_H2I_READ_REQ,
		bfa_ioc_portid(flash->ioc));
	bfa_alen_set(&msg->alen, len, flash->dbuf_pa);
	bfa_ioc_mbox_queue(flash->ioc, &flash->mb);
पूर्ण

/*
 * Send flash erase request.
 *
 * @param[in] cbarg - callback argument
 */
अटल व्योम
bfa_flash_erase_send(व्योम *cbarg)
अणु
	काष्ठा bfa_flash_s *flash = cbarg;
	काष्ठा bfi_flash_erase_req_s *msg =
			(काष्ठा bfi_flash_erase_req_s *) flash->mb.msg;

	msg->type = be32_to_cpu(flash->type);
	msg->instance = flash->instance;
	bfi_h2i_set(msg->mh, BFI_MC_FLASH, BFI_FLASH_H2I_ERASE_REQ,
			bfa_ioc_portid(flash->ioc));
	bfa_ioc_mbox_queue(flash->ioc, &flash->mb);
पूर्ण

/*
 * Process flash response messages upon receiving पूर्णांकerrupts.
 *
 * @param[in] flasharg - flash काष्ठाure
 * @param[in] msg - message काष्ठाure
 */
अटल व्योम
bfa_flash_पूर्णांकr(व्योम *flasharg, काष्ठा bfi_mbmsg_s *msg)
अणु
	काष्ठा bfa_flash_s *flash = flasharg;
	u32	status;

	जोड़ अणु
		काष्ठा bfi_flash_query_rsp_s *query;
		काष्ठा bfi_flash_erase_rsp_s *erase;
		काष्ठा bfi_flash_ग_लिखो_rsp_s *ग_लिखो;
		काष्ठा bfi_flash_पढ़ो_rsp_s *पढ़ो;
		काष्ठा bfi_flash_event_s *event;
		काष्ठा bfi_mbmsg_s   *msg;
	पूर्ण m;

	m.msg = msg;
	bfa_trc(flash, msg->mh.msg_id);

	अगर (!flash->op_busy && msg->mh.msg_id != BFI_FLASH_I2H_EVENT) अणु
		/* receiving response after ioc failure */
		bfa_trc(flash, 0x9999);
		वापस;
	पूर्ण

	चयन (msg->mh.msg_id) अणु
	हाल BFI_FLASH_I2H_QUERY_RSP:
		status = be32_to_cpu(m.query->status);
		bfa_trc(flash, status);
		अगर (status == BFA_STATUS_OK) अणु
			u32	i;
			काष्ठा bfa_flash_attr_s *attr, *f;

			attr = (काष्ठा bfa_flash_attr_s *) flash->ubuf;
			f = (काष्ठा bfa_flash_attr_s *) flash->dbuf_kva;
			attr->status = be32_to_cpu(f->status);
			attr->npart = be32_to_cpu(f->npart);
			bfa_trc(flash, attr->status);
			bfa_trc(flash, attr->npart);
			क्रम (i = 0; i < attr->npart; i++) अणु
				attr->part[i].part_type =
					be32_to_cpu(f->part[i].part_type);
				attr->part[i].part_instance =
					be32_to_cpu(f->part[i].part_instance);
				attr->part[i].part_off =
					be32_to_cpu(f->part[i].part_off);
				attr->part[i].part_size =
					be32_to_cpu(f->part[i].part_size);
				attr->part[i].part_len =
					be32_to_cpu(f->part[i].part_len);
				attr->part[i].part_status =
					be32_to_cpu(f->part[i].part_status);
			पूर्ण
		पूर्ण
		flash->status = status;
		bfa_flash_cb(flash);
		अवरोध;
	हाल BFI_FLASH_I2H_ERASE_RSP:
		status = be32_to_cpu(m.erase->status);
		bfa_trc(flash, status);
		flash->status = status;
		bfa_flash_cb(flash);
		अवरोध;
	हाल BFI_FLASH_I2H_WRITE_RSP:
		status = be32_to_cpu(m.ग_लिखो->status);
		bfa_trc(flash, status);
		अगर (status != BFA_STATUS_OK || flash->residue == 0) अणु
			flash->status = status;
			bfa_flash_cb(flash);
		पूर्ण अन्यथा अणु
			bfa_trc(flash, flash->offset);
			bfa_flash_ग_लिखो_send(flash);
		पूर्ण
		अवरोध;
	हाल BFI_FLASH_I2H_READ_RSP:
		status = be32_to_cpu(m.पढ़ो->status);
		bfa_trc(flash, status);
		अगर (status != BFA_STATUS_OK) अणु
			flash->status = status;
			bfa_flash_cb(flash);
		पूर्ण अन्यथा अणु
			u32 len = be32_to_cpu(m.पढ़ो->length);
			bfa_trc(flash, flash->offset);
			bfa_trc(flash, len);
			स_नकल(flash->ubuf + flash->offset,
				flash->dbuf_kva, len);
			flash->residue -= len;
			flash->offset += len;
			अगर (flash->residue == 0) अणु
				flash->status = status;
				bfa_flash_cb(flash);
			पूर्ण अन्यथा
				bfa_flash_पढ़ो_send(flash);
		पूर्ण
		अवरोध;
	हाल BFI_FLASH_I2H_BOOT_VER_RSP:
		अवरोध;
	हाल BFI_FLASH_I2H_EVENT:
		status = be32_to_cpu(m.event->status);
		bfa_trc(flash, status);
		अगर (status == BFA_STATUS_BAD_FWCFG)
			bfa_ioc_aen_post(flash->ioc, BFA_IOC_AEN_FWCFG_ERROR);
		अन्यथा अगर (status == BFA_STATUS_INVALID_VENDOR) अणु
			u32 param;
			param = be32_to_cpu(m.event->param);
			bfa_trc(flash, param);
			bfa_ioc_aen_post(flash->ioc,
				BFA_IOC_AEN_INVALID_VENDOR);
		पूर्ण
		अवरोध;

	शेष:
		WARN_ON(1);
	पूर्ण
पूर्ण

/*
 * Flash memory info API.
 *
 * @param[in] mincfg - minimal cfg variable
 */
u32
bfa_flash_meminfo(bfa_boolean_t mincfg)
अणु
	/* min driver करोesn't need flash */
	अगर (mincfg)
		वापस 0;
	वापस BFA_ROUNDUP(BFA_FLASH_DMA_BUF_SZ, BFA_DMA_ALIGN_SZ);
पूर्ण

/*
 * Flash attach API.
 *
 * @param[in] flash - flash काष्ठाure
 * @param[in] ioc  - ioc काष्ठाure
 * @param[in] dev  - device काष्ठाure
 * @param[in] trcmod - trace module
 * @param[in] logmod - log module
 */
व्योम
bfa_flash_attach(काष्ठा bfa_flash_s *flash, काष्ठा bfa_ioc_s *ioc, व्योम *dev,
		काष्ठा bfa_trc_mod_s *trcmod, bfa_boolean_t mincfg)
अणु
	flash->ioc = ioc;
	flash->trcmod = trcmod;
	flash->cbfn = शून्य;
	flash->cbarg = शून्य;
	flash->op_busy = 0;

	bfa_ioc_mbox_regisr(flash->ioc, BFI_MC_FLASH, bfa_flash_पूर्णांकr, flash);
	bfa_q_qe_init(&flash->ioc_notअगरy);
	bfa_ioc_notअगरy_init(&flash->ioc_notअगरy, bfa_flash_notअगरy, flash);
	list_add_tail(&flash->ioc_notअगरy.qe, &flash->ioc->notअगरy_q);

	/* min driver करोesn't need flash */
	अगर (mincfg) अणु
		flash->dbuf_kva = शून्य;
		flash->dbuf_pa = 0;
	पूर्ण
पूर्ण

/*
 * Claim memory क्रम flash
 *
 * @param[in] flash - flash काष्ठाure
 * @param[in] dm_kva - poपूर्णांकer to भव memory address
 * @param[in] dm_pa - physical memory address
 * @param[in] mincfg - minimal cfg variable
 */
व्योम
bfa_flash_memclaim(काष्ठा bfa_flash_s *flash, u8 *dm_kva, u64 dm_pa,
		bfa_boolean_t mincfg)
अणु
	अगर (mincfg)
		वापस;

	flash->dbuf_kva = dm_kva;
	flash->dbuf_pa = dm_pa;
	स_रखो(flash->dbuf_kva, 0, BFA_FLASH_DMA_BUF_SZ);
	dm_kva += BFA_ROUNDUP(BFA_FLASH_DMA_BUF_SZ, BFA_DMA_ALIGN_SZ);
	dm_pa += BFA_ROUNDUP(BFA_FLASH_DMA_BUF_SZ, BFA_DMA_ALIGN_SZ);
पूर्ण

/*
 * Get flash attribute.
 *
 * @param[in] flash - flash काष्ठाure
 * @param[in] attr - flash attribute काष्ठाure
 * @param[in] cbfn - callback function
 * @param[in] cbarg - callback argument
 *
 * Return status.
 */
bfa_status_t
bfa_flash_get_attr(काष्ठा bfa_flash_s *flash, काष्ठा bfa_flash_attr_s *attr,
		bfa_cb_flash_t cbfn, व्योम *cbarg)
अणु
	bfa_trc(flash, BFI_FLASH_H2I_QUERY_REQ);

	अगर (!bfa_ioc_is_operational(flash->ioc))
		वापस BFA_STATUS_IOC_NON_OP;

	अगर (flash->op_busy) अणु
		bfa_trc(flash, flash->op_busy);
		वापस BFA_STATUS_DEVBUSY;
	पूर्ण

	flash->op_busy = 1;
	flash->cbfn = cbfn;
	flash->cbarg = cbarg;
	flash->ubuf = (u8 *) attr;
	bfa_flash_query_send(flash);

	वापस BFA_STATUS_OK;
पूर्ण

/*
 * Erase flash partition.
 *
 * @param[in] flash - flash काष्ठाure
 * @param[in] type - flash partition type
 * @param[in] instance - flash partition instance
 * @param[in] cbfn - callback function
 * @param[in] cbarg - callback argument
 *
 * Return status.
 */
bfa_status_t
bfa_flash_erase_part(काष्ठा bfa_flash_s *flash, क्रमागत bfa_flash_part_type type,
		u8 instance, bfa_cb_flash_t cbfn, व्योम *cbarg)
अणु
	bfa_trc(flash, BFI_FLASH_H2I_ERASE_REQ);
	bfa_trc(flash, type);
	bfa_trc(flash, instance);

	अगर (!bfa_ioc_is_operational(flash->ioc))
		वापस BFA_STATUS_IOC_NON_OP;

	अगर (flash->op_busy) अणु
		bfa_trc(flash, flash->op_busy);
		वापस BFA_STATUS_DEVBUSY;
	पूर्ण

	flash->op_busy = 1;
	flash->cbfn = cbfn;
	flash->cbarg = cbarg;
	flash->type = type;
	flash->instance = instance;

	bfa_flash_erase_send(flash);
	bfa_flash_aen_audit_post(flash->ioc, BFA_AUDIT_AEN_FLASH_ERASE,
				instance, type);
	वापस BFA_STATUS_OK;
पूर्ण

/*
 * Update flash partition.
 *
 * @param[in] flash - flash काष्ठाure
 * @param[in] type - flash partition type
 * @param[in] instance - flash partition instance
 * @param[in] buf - update data buffer
 * @param[in] len - data buffer length
 * @param[in] offset - offset relative to the partition starting address
 * @param[in] cbfn - callback function
 * @param[in] cbarg - callback argument
 *
 * Return status.
 */
bfa_status_t
bfa_flash_update_part(काष्ठा bfa_flash_s *flash, क्रमागत bfa_flash_part_type type,
		u8 instance, व्योम *buf, u32 len, u32 offset,
		bfa_cb_flash_t cbfn, व्योम *cbarg)
अणु
	bfa_trc(flash, BFI_FLASH_H2I_WRITE_REQ);
	bfa_trc(flash, type);
	bfa_trc(flash, instance);
	bfa_trc(flash, len);
	bfa_trc(flash, offset);

	अगर (!bfa_ioc_is_operational(flash->ioc))
		वापस BFA_STATUS_IOC_NON_OP;

	/*
	 * 'len' must be in word (4-byte) boundary
	 * 'offset' must be in sector (16kb) boundary
	 */
	अगर (!len || (len & 0x03) || (offset & 0x00003FFF))
		वापस BFA_STATUS_FLASH_BAD_LEN;

	अगर (type == BFA_FLASH_PART_MFG)
		वापस BFA_STATUS_EINVAL;

	अगर (flash->op_busy) अणु
		bfa_trc(flash, flash->op_busy);
		वापस BFA_STATUS_DEVBUSY;
	पूर्ण

	flash->op_busy = 1;
	flash->cbfn = cbfn;
	flash->cbarg = cbarg;
	flash->type = type;
	flash->instance = instance;
	flash->residue = len;
	flash->offset = 0;
	flash->addr_off = offset;
	flash->ubuf = buf;

	bfa_flash_ग_लिखो_send(flash);
	वापस BFA_STATUS_OK;
पूर्ण

/*
 * Read flash partition.
 *
 * @param[in] flash - flash काष्ठाure
 * @param[in] type - flash partition type
 * @param[in] instance - flash partition instance
 * @param[in] buf - पढ़ो data buffer
 * @param[in] len - data buffer length
 * @param[in] offset - offset relative to the partition starting address
 * @param[in] cbfn - callback function
 * @param[in] cbarg - callback argument
 *
 * Return status.
 */
bfa_status_t
bfa_flash_पढ़ो_part(काष्ठा bfa_flash_s *flash, क्रमागत bfa_flash_part_type type,
		u8 instance, व्योम *buf, u32 len, u32 offset,
		bfa_cb_flash_t cbfn, व्योम *cbarg)
अणु
	bfa_trc(flash, BFI_FLASH_H2I_READ_REQ);
	bfa_trc(flash, type);
	bfa_trc(flash, instance);
	bfa_trc(flash, len);
	bfa_trc(flash, offset);

	अगर (!bfa_ioc_is_operational(flash->ioc))
		वापस BFA_STATUS_IOC_NON_OP;

	/*
	 * 'len' must be in word (4-byte) boundary
	 * 'offset' must be in sector (16kb) boundary
	 */
	अगर (!len || (len & 0x03) || (offset & 0x00003FFF))
		वापस BFA_STATUS_FLASH_BAD_LEN;

	अगर (flash->op_busy) अणु
		bfa_trc(flash, flash->op_busy);
		वापस BFA_STATUS_DEVBUSY;
	पूर्ण

	flash->op_busy = 1;
	flash->cbfn = cbfn;
	flash->cbarg = cbarg;
	flash->type = type;
	flash->instance = instance;
	flash->residue = len;
	flash->offset = 0;
	flash->addr_off = offset;
	flash->ubuf = buf;
	bfa_flash_पढ़ो_send(flash);

	वापस BFA_STATUS_OK;
पूर्ण

/*
 *	DIAG module specअगरic
 */

#घोषणा BFA_DIAG_MEMTEST_TOV	50000	/* memtest समयout in msec */
#घोषणा CT2_BFA_DIAG_MEMTEST_TOV	(9*30*1000)  /* 4.5 min */

/* IOC event handler */
अटल व्योम
bfa_diag_notअगरy(व्योम *diag_arg, क्रमागत bfa_ioc_event_e event)
अणु
	काष्ठा bfa_diag_s *diag = diag_arg;

	bfa_trc(diag, event);
	bfa_trc(diag, diag->block);
	bfa_trc(diag, diag->fwping.lock);
	bfa_trc(diag, diag->tsensor.lock);

	चयन (event) अणु
	हाल BFA_IOC_E_DISABLED:
	हाल BFA_IOC_E_FAILED:
		अगर (diag->fwping.lock) अणु
			diag->fwping.status = BFA_STATUS_IOC_FAILURE;
			diag->fwping.cbfn(diag->fwping.cbarg,
					diag->fwping.status);
			diag->fwping.lock = 0;
		पूर्ण

		अगर (diag->tsensor.lock) अणु
			diag->tsensor.status = BFA_STATUS_IOC_FAILURE;
			diag->tsensor.cbfn(diag->tsensor.cbarg,
					   diag->tsensor.status);
			diag->tsensor.lock = 0;
		पूर्ण

		अगर (diag->block) अणु
			अगर (diag->समयr_active) अणु
				bfa_समयr_stop(&diag->समयr);
				diag->समयr_active = 0;
			पूर्ण

			diag->status = BFA_STATUS_IOC_FAILURE;
			diag->cbfn(diag->cbarg, diag->status);
			diag->block = 0;
		पूर्ण
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम
bfa_diag_memtest_करोne(व्योम *cbarg)
अणु
	काष्ठा bfa_diag_s *diag = cbarg;
	काष्ठा bfa_ioc_s  *ioc = diag->ioc;
	काष्ठा bfa_diag_memtest_result *res = diag->result;
	u32	loff = BFI_BOOT_MEMTEST_RES_ADDR;
	u32	pgnum, i;

	pgnum = PSS_SMEM_PGNUM(ioc->ioc_regs.smem_pg0, loff);
	ग_लिखोl(pgnum, ioc->ioc_regs.host_page_num_fn);

	क्रम (i = 0; i < (माप(काष्ठा bfa_diag_memtest_result) /
			 माप(u32)); i++) अणु
		/* पढ़ो test result from smem */
		*((u32 *) res + i) =
			bfa_mem_पढ़ो(ioc->ioc_regs.smem_page_start, loff);
		loff += माप(u32);
	पूर्ण

	/* Reset IOC fwstates to BFI_IOC_UNINIT */
	bfa_ioc_reset_fwstate(ioc);

	res->status = swab32(res->status);
	bfa_trc(diag, res->status);

	अगर (res->status == BFI_BOOT_MEMTEST_RES_SIG)
		diag->status = BFA_STATUS_OK;
	अन्यथा अणु
		diag->status = BFA_STATUS_MEMTEST_FAILED;
		res->addr = swab32(res->addr);
		res->exp = swab32(res->exp);
		res->act = swab32(res->act);
		res->err_status = swab32(res->err_status);
		res->err_status1 = swab32(res->err_status1);
		res->err_addr = swab32(res->err_addr);
		bfa_trc(diag, res->addr);
		bfa_trc(diag, res->exp);
		bfa_trc(diag, res->act);
		bfa_trc(diag, res->err_status);
		bfa_trc(diag, res->err_status1);
		bfa_trc(diag, res->err_addr);
	पूर्ण
	diag->समयr_active = 0;
	diag->cbfn(diag->cbarg, diag->status);
	diag->block = 0;
पूर्ण

/*
 * Firmware ping
 */

/*
 * Perक्रमm DMA test directly
 */
अटल व्योम
diag_fwping_send(काष्ठा bfa_diag_s *diag)
अणु
	काष्ठा bfi_diag_fwping_req_s *fwping_req;
	u32	i;

	bfa_trc(diag, diag->fwping.dbuf_pa);

	/* fill DMA area with pattern */
	क्रम (i = 0; i < (BFI_DIAG_DMA_BUF_SZ >> 2); i++)
		*((u32 *)diag->fwping.dbuf_kva + i) = diag->fwping.data;

	/* Fill mbox msg */
	fwping_req = (काष्ठा bfi_diag_fwping_req_s *)diag->fwping.mbcmd.msg;

	/* Setup SG list */
	bfa_alen_set(&fwping_req->alen, BFI_DIAG_DMA_BUF_SZ,
			diag->fwping.dbuf_pa);
	/* Set up dma count */
	fwping_req->count = cpu_to_be32(diag->fwping.count);
	/* Set up data pattern */
	fwping_req->data = diag->fwping.data;

	/* build host command */
	bfi_h2i_set(fwping_req->mh, BFI_MC_DIAG, BFI_DIAG_H2I_FWPING,
		bfa_ioc_portid(diag->ioc));

	/* send mbox cmd */
	bfa_ioc_mbox_queue(diag->ioc, &diag->fwping.mbcmd);
पूर्ण

अटल व्योम
diag_fwping_comp(काष्ठा bfa_diag_s *diag,
		 काष्ठा bfi_diag_fwping_rsp_s *diag_rsp)
अणु
	u32	rsp_data = diag_rsp->data;
	u8	rsp_dma_status = diag_rsp->dma_status;

	bfa_trc(diag, rsp_data);
	bfa_trc(diag, rsp_dma_status);

	अगर (rsp_dma_status == BFA_STATUS_OK) अणु
		u32	i, pat;
		pat = (diag->fwping.count & 0x1) ? ~(diag->fwping.data) :
			diag->fwping.data;
		/* Check mbox data */
		अगर (diag->fwping.data != rsp_data) अणु
			bfa_trc(diag, rsp_data);
			diag->fwping.result->dmastatus =
					BFA_STATUS_DATACORRUPTED;
			diag->fwping.status = BFA_STATUS_DATACORRUPTED;
			diag->fwping.cbfn(diag->fwping.cbarg,
					diag->fwping.status);
			diag->fwping.lock = 0;
			वापस;
		पूर्ण
		/* Check dma pattern */
		क्रम (i = 0; i < (BFI_DIAG_DMA_BUF_SZ >> 2); i++) अणु
			अगर (*((u32 *)diag->fwping.dbuf_kva + i) != pat) अणु
				bfa_trc(diag, i);
				bfa_trc(diag, pat);
				bfa_trc(diag,
					*((u32 *)diag->fwping.dbuf_kva + i));
				diag->fwping.result->dmastatus =
						BFA_STATUS_DATACORRUPTED;
				diag->fwping.status = BFA_STATUS_DATACORRUPTED;
				diag->fwping.cbfn(diag->fwping.cbarg,
						diag->fwping.status);
				diag->fwping.lock = 0;
				वापस;
			पूर्ण
		पूर्ण
		diag->fwping.result->dmastatus = BFA_STATUS_OK;
		diag->fwping.status = BFA_STATUS_OK;
		diag->fwping.cbfn(diag->fwping.cbarg, diag->fwping.status);
		diag->fwping.lock = 0;
	पूर्ण अन्यथा अणु
		diag->fwping.status = BFA_STATUS_HDMA_FAILED;
		diag->fwping.cbfn(diag->fwping.cbarg, diag->fwping.status);
		diag->fwping.lock = 0;
	पूर्ण
पूर्ण

/*
 * Temperature Sensor
 */

अटल व्योम
diag_tempsensor_send(काष्ठा bfa_diag_s *diag)
अणु
	काष्ठा bfi_diag_ts_req_s *msg;

	msg = (काष्ठा bfi_diag_ts_req_s *)diag->tsensor.mbcmd.msg;
	bfa_trc(diag, msg->temp);
	/* build host command */
	bfi_h2i_set(msg->mh, BFI_MC_DIAG, BFI_DIAG_H2I_TEMPSENSOR,
		bfa_ioc_portid(diag->ioc));
	/* send mbox cmd */
	bfa_ioc_mbox_queue(diag->ioc, &diag->tsensor.mbcmd);
पूर्ण

अटल व्योम
diag_tempsensor_comp(काष्ठा bfa_diag_s *diag, bfi_diag_ts_rsp_t *rsp)
अणु
	अगर (!diag->tsensor.lock) अणु
		/* receiving response after ioc failure */
		bfa_trc(diag, diag->tsensor.lock);
		वापस;
	पूर्ण

	/*
	 * ASIC junction tempsensor is a reg पढ़ो operation
	 * it will always वापस OK
	 */
	diag->tsensor.temp->temp = be16_to_cpu(rsp->temp);
	diag->tsensor.temp->ts_junc = rsp->ts_junc;
	diag->tsensor.temp->ts_brd = rsp->ts_brd;

	अगर (rsp->ts_brd) अणु
		/* tsensor.temp->status is brd_temp status */
		diag->tsensor.temp->status = rsp->status;
		अगर (rsp->status == BFA_STATUS_OK) अणु
			diag->tsensor.temp->brd_temp =
				be16_to_cpu(rsp->brd_temp);
		पूर्ण अन्यथा
			diag->tsensor.temp->brd_temp = 0;
	पूर्ण

	bfa_trc(diag, rsp->status);
	bfa_trc(diag, rsp->ts_junc);
	bfa_trc(diag, rsp->temp);
	bfa_trc(diag, rsp->ts_brd);
	bfa_trc(diag, rsp->brd_temp);

	/* tsensor status is always good bcos we always have junction temp */
	diag->tsensor.status = BFA_STATUS_OK;
	diag->tsensor.cbfn(diag->tsensor.cbarg, diag->tsensor.status);
	diag->tsensor.lock = 0;
पूर्ण

/*
 *	LED Test command
 */
अटल व्योम
diag_ledtest_send(काष्ठा bfa_diag_s *diag, काष्ठा bfa_diag_ledtest_s *ledtest)
अणु
	काष्ठा bfi_diag_ledtest_req_s  *msg;

	msg = (काष्ठा bfi_diag_ledtest_req_s *)diag->ledtest.mbcmd.msg;
	/* build host command */
	bfi_h2i_set(msg->mh, BFI_MC_DIAG, BFI_DIAG_H2I_LEDTEST,
			bfa_ioc_portid(diag->ioc));

	/*
	 * convert the freq from N blinks per 10 sec to
	 * crossbow onसमय value. We करो it here because भागision is need
	 */
	अगर (ledtest->freq)
		ledtest->freq = 500 / ledtest->freq;

	अगर (ledtest->freq == 0)
		ledtest->freq = 1;

	bfa_trc(diag, ledtest->freq);
	/* mcpy(&ledtest_req->req, ledtest, माप(bfa_diag_ledtest_t)); */
	msg->cmd = (u8) ledtest->cmd;
	msg->color = (u8) ledtest->color;
	msg->portid = bfa_ioc_portid(diag->ioc);
	msg->led = ledtest->led;
	msg->freq = cpu_to_be16(ledtest->freq);

	/* send mbox cmd */
	bfa_ioc_mbox_queue(diag->ioc, &diag->ledtest.mbcmd);
पूर्ण

अटल व्योम
diag_ledtest_comp(काष्ठा bfa_diag_s *diag, काष्ठा bfi_diag_ledtest_rsp_s *msg)
अणु
	bfa_trc(diag, diag->ledtest.lock);
	diag->ledtest.lock = BFA_FALSE;
	/* no bfa_cb_queue is needed because driver is not रुकोing */
पूर्ण

/*
 * Port beaconing
 */
अटल व्योम
diag_portbeacon_send(काष्ठा bfa_diag_s *diag, bfa_boolean_t beacon, u32 sec)
अणु
	काष्ठा bfi_diag_portbeacon_req_s *msg;

	msg = (काष्ठा bfi_diag_portbeacon_req_s *)diag->beacon.mbcmd.msg;
	/* build host command */
	bfi_h2i_set(msg->mh, BFI_MC_DIAG, BFI_DIAG_H2I_PORTBEACON,
		bfa_ioc_portid(diag->ioc));
	msg->beacon = beacon;
	msg->period = cpu_to_be32(sec);
	/* send mbox cmd */
	bfa_ioc_mbox_queue(diag->ioc, &diag->beacon.mbcmd);
पूर्ण

अटल व्योम
diag_portbeacon_comp(काष्ठा bfa_diag_s *diag)
अणु
	bfa_trc(diag, diag->beacon.state);
	diag->beacon.state = BFA_FALSE;
	अगर (diag->cbfn_beacon)
		diag->cbfn_beacon(diag->dev, BFA_FALSE, diag->beacon.link_e2e);
पूर्ण

/*
 *	Diag hmbox handler
 */
अटल व्योम
bfa_diag_पूर्णांकr(व्योम *diagarg, काष्ठा bfi_mbmsg_s *msg)
अणु
	काष्ठा bfa_diag_s *diag = diagarg;

	चयन (msg->mh.msg_id) अणु
	हाल BFI_DIAG_I2H_PORTBEACON:
		diag_portbeacon_comp(diag);
		अवरोध;
	हाल BFI_DIAG_I2H_FWPING:
		diag_fwping_comp(diag, (काष्ठा bfi_diag_fwping_rsp_s *) msg);
		अवरोध;
	हाल BFI_DIAG_I2H_TEMPSENSOR:
		diag_tempsensor_comp(diag, (bfi_diag_ts_rsp_t *) msg);
		अवरोध;
	हाल BFI_DIAG_I2H_LEDTEST:
		diag_ledtest_comp(diag, (काष्ठा bfi_diag_ledtest_rsp_s *) msg);
		अवरोध;
	शेष:
		bfa_trc(diag, msg->mh.msg_id);
		WARN_ON(1);
	पूर्ण
पूर्ण

/*
 * Gen RAM Test
 *
 *   @param[in] *diag           - diag data काष्ठा
 *   @param[in] *memtest        - mem test params input from upper layer,
 *   @param[in] pattern         - mem test pattern
 *   @param[in] *result         - mem test result
 *   @param[in] cbfn            - mem test callback functioin
 *   @param[in] cbarg           - callback functioin arg
 *
 *   @param[out]
 */
bfa_status_t
bfa_diag_memtest(काष्ठा bfa_diag_s *diag, काष्ठा bfa_diag_memtest_s *memtest,
		u32 pattern, काष्ठा bfa_diag_memtest_result *result,
		bfa_cb_diag_t cbfn, व्योम *cbarg)
अणु
	u32	memtest_tov;

	bfa_trc(diag, pattern);

	अगर (!bfa_ioc_adapter_is_disabled(diag->ioc))
		वापस BFA_STATUS_ADAPTER_ENABLED;

	/* check to see अगर there is another deकाष्ठाive diag cmd running */
	अगर (diag->block) अणु
		bfa_trc(diag, diag->block);
		वापस BFA_STATUS_DEVBUSY;
	पूर्ण अन्यथा
		diag->block = 1;

	diag->result = result;
	diag->cbfn = cbfn;
	diag->cbarg = cbarg;

	/* करोwnload memtest code and take LPU0 out of reset */
	bfa_ioc_boot(diag->ioc, BFI_FWBOOT_TYPE_MEMTEST, BFI_FWBOOT_ENV_OS);

	memtest_tov = (bfa_ioc_asic_gen(diag->ioc) == BFI_ASIC_GEN_CT2) ?
		       CT2_BFA_DIAG_MEMTEST_TOV : BFA_DIAG_MEMTEST_TOV;
	bfa_समयr_begin(diag->ioc->समयr_mod, &diag->समयr,
			bfa_diag_memtest_करोne, diag, memtest_tov);
	diag->समयr_active = 1;
	वापस BFA_STATUS_OK;
पूर्ण

/*
 * DIAG firmware ping command
 *
 *   @param[in] *diag           - diag data काष्ठा
 *   @param[in] cnt             - dma loop count क्रम testing PCIE
 *   @param[in] data            - data pattern to pass in fw
 *   @param[in] *result         - pt to bfa_diag_fwping_result_t data काष्ठा
 *   @param[in] cbfn            - callback function
 *   @param[in] *cbarg          - callback functioin arg
 *
 *   @param[out]
 */
bfa_status_t
bfa_diag_fwping(काष्ठा bfa_diag_s *diag, u32 cnt, u32 data,
		काष्ठा bfa_diag_results_fwping *result, bfa_cb_diag_t cbfn,
		व्योम *cbarg)
अणु
	bfa_trc(diag, cnt);
	bfa_trc(diag, data);

	अगर (!bfa_ioc_is_operational(diag->ioc))
		वापस BFA_STATUS_IOC_NON_OP;

	अगर (bfa_asic_id_ct2(bfa_ioc_devid((diag->ioc))) &&
	    ((diag->ioc)->clscode == BFI_PCIFN_CLASS_ETH))
		वापस BFA_STATUS_CMD_NOTSUPP;

	/* check to see अगर there is another deकाष्ठाive diag cmd running */
	अगर (diag->block || diag->fwping.lock) अणु
		bfa_trc(diag, diag->block);
		bfa_trc(diag, diag->fwping.lock);
		वापस BFA_STATUS_DEVBUSY;
	पूर्ण

	/* Initialization */
	diag->fwping.lock = 1;
	diag->fwping.cbfn = cbfn;
	diag->fwping.cbarg = cbarg;
	diag->fwping.result = result;
	diag->fwping.data = data;
	diag->fwping.count = cnt;

	/* Init test results */
	diag->fwping.result->data = 0;
	diag->fwping.result->status = BFA_STATUS_OK;

	/* kick off the first ping */
	diag_fwping_send(diag);
	वापस BFA_STATUS_OK;
पूर्ण

/*
 * Read Temperature Sensor
 *
 *   @param[in] *diag           - diag data काष्ठा
 *   @param[in] *result         - pt to bfa_diag_temp_t data काष्ठा
 *   @param[in] cbfn            - callback function
 *   @param[in] *cbarg          - callback functioin arg
 *
 *   @param[out]
 */
bfa_status_t
bfa_diag_tsensor_query(काष्ठा bfa_diag_s *diag,
		काष्ठा bfa_diag_results_tempsensor_s *result,
		bfa_cb_diag_t cbfn, व्योम *cbarg)
अणु
	/* check to see अगर there is a deकाष्ठाive diag cmd running */
	अगर (diag->block || diag->tsensor.lock) अणु
		bfa_trc(diag, diag->block);
		bfa_trc(diag, diag->tsensor.lock);
		वापस BFA_STATUS_DEVBUSY;
	पूर्ण

	अगर (!bfa_ioc_is_operational(diag->ioc))
		वापस BFA_STATUS_IOC_NON_OP;

	/* Init diag mod params */
	diag->tsensor.lock = 1;
	diag->tsensor.temp = result;
	diag->tsensor.cbfn = cbfn;
	diag->tsensor.cbarg = cbarg;
	diag->tsensor.status = BFA_STATUS_OK;

	/* Send msg to fw */
	diag_tempsensor_send(diag);

	वापस BFA_STATUS_OK;
पूर्ण

/*
 * LED Test command
 *
 *   @param[in] *diag           - diag data काष्ठा
 *   @param[in] *ledtest        - pt to ledtest data काष्ठाure
 *
 *   @param[out]
 */
bfa_status_t
bfa_diag_ledtest(काष्ठा bfa_diag_s *diag, काष्ठा bfa_diag_ledtest_s *ledtest)
अणु
	bfa_trc(diag, ledtest->cmd);

	अगर (!bfa_ioc_is_operational(diag->ioc))
		वापस BFA_STATUS_IOC_NON_OP;

	अगर (diag->beacon.state)
		वापस BFA_STATUS_BEACON_ON;

	अगर (diag->ledtest.lock)
		वापस BFA_STATUS_LEDTEST_OP;

	/* Send msg to fw */
	diag->ledtest.lock = BFA_TRUE;
	diag_ledtest_send(diag, ledtest);

	वापस BFA_STATUS_OK;
पूर्ण

/*
 * Port beaconing command
 *
 *   @param[in] *diag           - diag data काष्ठा
 *   @param[in] beacon          - port beaconing 1:ON   0:OFF
 *   @param[in] link_e2e_beacon - link beaconing 1:ON   0:OFF
 *   @param[in] sec             - beaconing duration in seconds
 *
 *   @param[out]
 */
bfa_status_t
bfa_diag_beacon_port(काष्ठा bfa_diag_s *diag, bfa_boolean_t beacon,
		bfa_boolean_t link_e2e_beacon, uपूर्णांक32_t sec)
अणु
	bfa_trc(diag, beacon);
	bfa_trc(diag, link_e2e_beacon);
	bfa_trc(diag, sec);

	अगर (!bfa_ioc_is_operational(diag->ioc))
		वापस BFA_STATUS_IOC_NON_OP;

	अगर (diag->ledtest.lock)
		वापस BFA_STATUS_LEDTEST_OP;

	अगर (diag->beacon.state && beacon)       /* beacon alपढ़ो on */
		वापस BFA_STATUS_BEACON_ON;

	diag->beacon.state	= beacon;
	diag->beacon.link_e2e	= link_e2e_beacon;
	अगर (diag->cbfn_beacon)
		diag->cbfn_beacon(diag->dev, beacon, link_e2e_beacon);

	/* Send msg to fw */
	diag_portbeacon_send(diag, beacon, sec);

	वापस BFA_STATUS_OK;
पूर्ण

/*
 * Return DMA memory needed by diag module.
 */
u32
bfa_diag_meminfo(व्योम)
अणु
	वापस BFA_ROUNDUP(BFI_DIAG_DMA_BUF_SZ, BFA_DMA_ALIGN_SZ);
पूर्ण

/*
 *	Attach भव and physical memory क्रम Diag.
 */
व्योम
bfa_diag_attach(काष्ठा bfa_diag_s *diag, काष्ठा bfa_ioc_s *ioc, व्योम *dev,
	bfa_cb_diag_beacon_t cbfn_beacon, काष्ठा bfa_trc_mod_s *trcmod)
अणु
	diag->dev = dev;
	diag->ioc = ioc;
	diag->trcmod = trcmod;

	diag->block = 0;
	diag->cbfn = शून्य;
	diag->cbarg = शून्य;
	diag->result = शून्य;
	diag->cbfn_beacon = cbfn_beacon;

	bfa_ioc_mbox_regisr(diag->ioc, BFI_MC_DIAG, bfa_diag_पूर्णांकr, diag);
	bfa_q_qe_init(&diag->ioc_notअगरy);
	bfa_ioc_notअगरy_init(&diag->ioc_notअगरy, bfa_diag_notअगरy, diag);
	list_add_tail(&diag->ioc_notअगरy.qe, &diag->ioc->notअगरy_q);
पूर्ण

व्योम
bfa_diag_memclaim(काष्ठा bfa_diag_s *diag, u8 *dm_kva, u64 dm_pa)
अणु
	diag->fwping.dbuf_kva = dm_kva;
	diag->fwping.dbuf_pa = dm_pa;
	स_रखो(diag->fwping.dbuf_kva, 0, BFI_DIAG_DMA_BUF_SZ);
पूर्ण

/*
 *	PHY module specअगरic
 */
#घोषणा BFA_PHY_DMA_BUF_SZ	0x02000         /* 8k dma buffer */
#घोषणा BFA_PHY_LOCK_STATUS	0x018878        /* phy semaphore status reg */

अटल व्योम
bfa_phy_ntoh32(u32 *obuf, u32 *ibuf, पूर्णांक sz)
अणु
	पूर्णांक i, m = sz >> 2;

	क्रम (i = 0; i < m; i++)
		obuf[i] = be32_to_cpu(ibuf[i]);
पूर्ण

अटल bfa_boolean_t
bfa_phy_present(काष्ठा bfa_phy_s *phy)
अणु
	वापस (phy->ioc->attr->card_type == BFA_MFG_TYPE_LIGHTNING);
पूर्ण

अटल व्योम
bfa_phy_notअगरy(व्योम *cbarg, क्रमागत bfa_ioc_event_e event)
अणु
	काष्ठा bfa_phy_s *phy = cbarg;

	bfa_trc(phy, event);

	चयन (event) अणु
	हाल BFA_IOC_E_DISABLED:
	हाल BFA_IOC_E_FAILED:
		अगर (phy->op_busy) अणु
			phy->status = BFA_STATUS_IOC_FAILURE;
			phy->cbfn(phy->cbarg, phy->status);
			phy->op_busy = 0;
		पूर्ण
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण
पूर्ण

/*
 * Send phy attribute query request.
 *
 * @param[in] cbarg - callback argument
 */
अटल व्योम
bfa_phy_query_send(व्योम *cbarg)
अणु
	काष्ठा bfa_phy_s *phy = cbarg;
	काष्ठा bfi_phy_query_req_s *msg =
			(काष्ठा bfi_phy_query_req_s *) phy->mb.msg;

	msg->instance = phy->instance;
	bfi_h2i_set(msg->mh, BFI_MC_PHY, BFI_PHY_H2I_QUERY_REQ,
		bfa_ioc_portid(phy->ioc));
	bfa_alen_set(&msg->alen, माप(काष्ठा bfa_phy_attr_s), phy->dbuf_pa);
	bfa_ioc_mbox_queue(phy->ioc, &phy->mb);
पूर्ण

/*
 * Send phy ग_लिखो request.
 *
 * @param[in] cbarg - callback argument
 */
अटल व्योम
bfa_phy_ग_लिखो_send(व्योम *cbarg)
अणु
	काष्ठा bfa_phy_s *phy = cbarg;
	काष्ठा bfi_phy_ग_लिखो_req_s *msg =
			(काष्ठा bfi_phy_ग_लिखो_req_s *) phy->mb.msg;
	u32	len;
	u16	*buf, *dbuf;
	पूर्णांक	i, sz;

	msg->instance = phy->instance;
	msg->offset = cpu_to_be32(phy->addr_off + phy->offset);
	len = (phy->residue < BFA_PHY_DMA_BUF_SZ) ?
			phy->residue : BFA_PHY_DMA_BUF_SZ;
	msg->length = cpu_to_be32(len);

	/* indicate अगर it's the last msg of the whole ग_लिखो operation */
	msg->last = (len == phy->residue) ? 1 : 0;

	bfi_h2i_set(msg->mh, BFI_MC_PHY, BFI_PHY_H2I_WRITE_REQ,
		bfa_ioc_portid(phy->ioc));
	bfa_alen_set(&msg->alen, len, phy->dbuf_pa);

	buf = (u16 *) (phy->ubuf + phy->offset);
	dbuf = (u16 *)phy->dbuf_kva;
	sz = len >> 1;
	क्रम (i = 0; i < sz; i++)
		buf[i] = cpu_to_be16(dbuf[i]);

	bfa_ioc_mbox_queue(phy->ioc, &phy->mb);

	phy->residue -= len;
	phy->offset += len;
पूर्ण

/*
 * Send phy पढ़ो request.
 *
 * @param[in] cbarg - callback argument
 */
अटल व्योम
bfa_phy_पढ़ो_send(व्योम *cbarg)
अणु
	काष्ठा bfa_phy_s *phy = cbarg;
	काष्ठा bfi_phy_पढ़ो_req_s *msg =
			(काष्ठा bfi_phy_पढ़ो_req_s *) phy->mb.msg;
	u32	len;

	msg->instance = phy->instance;
	msg->offset = cpu_to_be32(phy->addr_off + phy->offset);
	len = (phy->residue < BFA_PHY_DMA_BUF_SZ) ?
			phy->residue : BFA_PHY_DMA_BUF_SZ;
	msg->length = cpu_to_be32(len);
	bfi_h2i_set(msg->mh, BFI_MC_PHY, BFI_PHY_H2I_READ_REQ,
		bfa_ioc_portid(phy->ioc));
	bfa_alen_set(&msg->alen, len, phy->dbuf_pa);
	bfa_ioc_mbox_queue(phy->ioc, &phy->mb);
पूर्ण

/*
 * Send phy stats request.
 *
 * @param[in] cbarg - callback argument
 */
अटल व्योम
bfa_phy_stats_send(व्योम *cbarg)
अणु
	काष्ठा bfa_phy_s *phy = cbarg;
	काष्ठा bfi_phy_stats_req_s *msg =
			(काष्ठा bfi_phy_stats_req_s *) phy->mb.msg;

	msg->instance = phy->instance;
	bfi_h2i_set(msg->mh, BFI_MC_PHY, BFI_PHY_H2I_STATS_REQ,
		bfa_ioc_portid(phy->ioc));
	bfa_alen_set(&msg->alen, माप(काष्ठा bfa_phy_stats_s), phy->dbuf_pa);
	bfa_ioc_mbox_queue(phy->ioc, &phy->mb);
पूर्ण

/*
 * Flash memory info API.
 *
 * @param[in] mincfg - minimal cfg variable
 */
u32
bfa_phy_meminfo(bfa_boolean_t mincfg)
अणु
	/* min driver करोesn't need phy */
	अगर (mincfg)
		वापस 0;

	वापस BFA_ROUNDUP(BFA_PHY_DMA_BUF_SZ, BFA_DMA_ALIGN_SZ);
पूर्ण

/*
 * Flash attach API.
 *
 * @param[in] phy - phy काष्ठाure
 * @param[in] ioc  - ioc काष्ठाure
 * @param[in] dev  - device काष्ठाure
 * @param[in] trcmod - trace module
 * @param[in] logmod - log module
 */
व्योम
bfa_phy_attach(काष्ठा bfa_phy_s *phy, काष्ठा bfa_ioc_s *ioc, व्योम *dev,
		काष्ठा bfa_trc_mod_s *trcmod, bfa_boolean_t mincfg)
अणु
	phy->ioc = ioc;
	phy->trcmod = trcmod;
	phy->cbfn = शून्य;
	phy->cbarg = शून्य;
	phy->op_busy = 0;

	bfa_ioc_mbox_regisr(phy->ioc, BFI_MC_PHY, bfa_phy_पूर्णांकr, phy);
	bfa_q_qe_init(&phy->ioc_notअगरy);
	bfa_ioc_notअगरy_init(&phy->ioc_notअगरy, bfa_phy_notअगरy, phy);
	list_add_tail(&phy->ioc_notअगरy.qe, &phy->ioc->notअगरy_q);

	/* min driver करोesn't need phy */
	अगर (mincfg) अणु
		phy->dbuf_kva = शून्य;
		phy->dbuf_pa = 0;
	पूर्ण
पूर्ण

/*
 * Claim memory क्रम phy
 *
 * @param[in] phy - phy काष्ठाure
 * @param[in] dm_kva - poपूर्णांकer to भव memory address
 * @param[in] dm_pa - physical memory address
 * @param[in] mincfg - minimal cfg variable
 */
व्योम
bfa_phy_memclaim(काष्ठा bfa_phy_s *phy, u8 *dm_kva, u64 dm_pa,
		bfa_boolean_t mincfg)
अणु
	अगर (mincfg)
		वापस;

	phy->dbuf_kva = dm_kva;
	phy->dbuf_pa = dm_pa;
	स_रखो(phy->dbuf_kva, 0, BFA_PHY_DMA_BUF_SZ);
	dm_kva += BFA_ROUNDUP(BFA_PHY_DMA_BUF_SZ, BFA_DMA_ALIGN_SZ);
	dm_pa += BFA_ROUNDUP(BFA_PHY_DMA_BUF_SZ, BFA_DMA_ALIGN_SZ);
पूर्ण

bfa_boolean_t
bfa_phy_busy(काष्ठा bfa_ioc_s *ioc)
अणु
	व्योम __iomem	*rb;

	rb = bfa_ioc_bar0(ioc);
	वापस पढ़ोl(rb + BFA_PHY_LOCK_STATUS);
पूर्ण

/*
 * Get phy attribute.
 *
 * @param[in] phy - phy काष्ठाure
 * @param[in] attr - phy attribute काष्ठाure
 * @param[in] cbfn - callback function
 * @param[in] cbarg - callback argument
 *
 * Return status.
 */
bfa_status_t
bfa_phy_get_attr(काष्ठा bfa_phy_s *phy, u8 instance,
		काष्ठा bfa_phy_attr_s *attr, bfa_cb_phy_t cbfn, व्योम *cbarg)
अणु
	bfa_trc(phy, BFI_PHY_H2I_QUERY_REQ);
	bfa_trc(phy, instance);

	अगर (!bfa_phy_present(phy))
		वापस BFA_STATUS_PHY_NOT_PRESENT;

	अगर (!bfa_ioc_is_operational(phy->ioc))
		वापस BFA_STATUS_IOC_NON_OP;

	अगर (phy->op_busy || bfa_phy_busy(phy->ioc)) अणु
		bfa_trc(phy, phy->op_busy);
		वापस BFA_STATUS_DEVBUSY;
	पूर्ण

	phy->op_busy = 1;
	phy->cbfn = cbfn;
	phy->cbarg = cbarg;
	phy->instance = instance;
	phy->ubuf = (uपूर्णांक8_t *) attr;
	bfa_phy_query_send(phy);

	वापस BFA_STATUS_OK;
पूर्ण

/*
 * Get phy stats.
 *
 * @param[in] phy - phy काष्ठाure
 * @param[in] instance - phy image instance
 * @param[in] stats - poपूर्णांकer to phy stats
 * @param[in] cbfn - callback function
 * @param[in] cbarg - callback argument
 *
 * Return status.
 */
bfa_status_t
bfa_phy_get_stats(काष्ठा bfa_phy_s *phy, u8 instance,
		काष्ठा bfa_phy_stats_s *stats,
		bfa_cb_phy_t cbfn, व्योम *cbarg)
अणु
	bfa_trc(phy, BFI_PHY_H2I_STATS_REQ);
	bfa_trc(phy, instance);

	अगर (!bfa_phy_present(phy))
		वापस BFA_STATUS_PHY_NOT_PRESENT;

	अगर (!bfa_ioc_is_operational(phy->ioc))
		वापस BFA_STATUS_IOC_NON_OP;

	अगर (phy->op_busy || bfa_phy_busy(phy->ioc)) अणु
		bfa_trc(phy, phy->op_busy);
		वापस BFA_STATUS_DEVBUSY;
	पूर्ण

	phy->op_busy = 1;
	phy->cbfn = cbfn;
	phy->cbarg = cbarg;
	phy->instance = instance;
	phy->ubuf = (u8 *) stats;
	bfa_phy_stats_send(phy);

	वापस BFA_STATUS_OK;
पूर्ण

/*
 * Update phy image.
 *
 * @param[in] phy - phy काष्ठाure
 * @param[in] instance - phy image instance
 * @param[in] buf - update data buffer
 * @param[in] len - data buffer length
 * @param[in] offset - offset relative to starting address
 * @param[in] cbfn - callback function
 * @param[in] cbarg - callback argument
 *
 * Return status.
 */
bfa_status_t
bfa_phy_update(काष्ठा bfa_phy_s *phy, u8 instance,
		व्योम *buf, u32 len, u32 offset,
		bfa_cb_phy_t cbfn, व्योम *cbarg)
अणु
	bfa_trc(phy, BFI_PHY_H2I_WRITE_REQ);
	bfa_trc(phy, instance);
	bfa_trc(phy, len);
	bfa_trc(phy, offset);

	अगर (!bfa_phy_present(phy))
		वापस BFA_STATUS_PHY_NOT_PRESENT;

	अगर (!bfa_ioc_is_operational(phy->ioc))
		वापस BFA_STATUS_IOC_NON_OP;

	/* 'len' must be in word (4-byte) boundary */
	अगर (!len || (len & 0x03))
		वापस BFA_STATUS_FAILED;

	अगर (phy->op_busy || bfa_phy_busy(phy->ioc)) अणु
		bfa_trc(phy, phy->op_busy);
		वापस BFA_STATUS_DEVBUSY;
	पूर्ण

	phy->op_busy = 1;
	phy->cbfn = cbfn;
	phy->cbarg = cbarg;
	phy->instance = instance;
	phy->residue = len;
	phy->offset = 0;
	phy->addr_off = offset;
	phy->ubuf = buf;

	bfa_phy_ग_लिखो_send(phy);
	वापस BFA_STATUS_OK;
पूर्ण

/*
 * Read phy image.
 *
 * @param[in] phy - phy काष्ठाure
 * @param[in] instance - phy image instance
 * @param[in] buf - पढ़ो data buffer
 * @param[in] len - data buffer length
 * @param[in] offset - offset relative to starting address
 * @param[in] cbfn - callback function
 * @param[in] cbarg - callback argument
 *
 * Return status.
 */
bfa_status_t
bfa_phy_पढ़ो(काष्ठा bfa_phy_s *phy, u8 instance,
		व्योम *buf, u32 len, u32 offset,
		bfa_cb_phy_t cbfn, व्योम *cbarg)
अणु
	bfa_trc(phy, BFI_PHY_H2I_READ_REQ);
	bfa_trc(phy, instance);
	bfa_trc(phy, len);
	bfa_trc(phy, offset);

	अगर (!bfa_phy_present(phy))
		वापस BFA_STATUS_PHY_NOT_PRESENT;

	अगर (!bfa_ioc_is_operational(phy->ioc))
		वापस BFA_STATUS_IOC_NON_OP;

	/* 'len' must be in word (4-byte) boundary */
	अगर (!len || (len & 0x03))
		वापस BFA_STATUS_FAILED;

	अगर (phy->op_busy || bfa_phy_busy(phy->ioc)) अणु
		bfa_trc(phy, phy->op_busy);
		वापस BFA_STATUS_DEVBUSY;
	पूर्ण

	phy->op_busy = 1;
	phy->cbfn = cbfn;
	phy->cbarg = cbarg;
	phy->instance = instance;
	phy->residue = len;
	phy->offset = 0;
	phy->addr_off = offset;
	phy->ubuf = buf;
	bfa_phy_पढ़ो_send(phy);

	वापस BFA_STATUS_OK;
पूर्ण

/*
 * Process phy response messages upon receiving पूर्णांकerrupts.
 *
 * @param[in] phyarg - phy काष्ठाure
 * @param[in] msg - message काष्ठाure
 */
व्योम
bfa_phy_पूर्णांकr(व्योम *phyarg, काष्ठा bfi_mbmsg_s *msg)
अणु
	काष्ठा bfa_phy_s *phy = phyarg;
	u32	status;

	जोड़ अणु
		काष्ठा bfi_phy_query_rsp_s *query;
		काष्ठा bfi_phy_stats_rsp_s *stats;
		काष्ठा bfi_phy_ग_लिखो_rsp_s *ग_लिखो;
		काष्ठा bfi_phy_पढ़ो_rsp_s *पढ़ो;
		काष्ठा bfi_mbmsg_s   *msg;
	पूर्ण m;

	m.msg = msg;
	bfa_trc(phy, msg->mh.msg_id);

	अगर (!phy->op_busy) अणु
		/* receiving response after ioc failure */
		bfa_trc(phy, 0x9999);
		वापस;
	पूर्ण

	चयन (msg->mh.msg_id) अणु
	हाल BFI_PHY_I2H_QUERY_RSP:
		status = be32_to_cpu(m.query->status);
		bfa_trc(phy, status);

		अगर (status == BFA_STATUS_OK) अणु
			काष्ठा bfa_phy_attr_s *attr =
				(काष्ठा bfa_phy_attr_s *) phy->ubuf;
			bfa_phy_ntoh32((u32 *)attr, (u32 *)phy->dbuf_kva,
					माप(काष्ठा bfa_phy_attr_s));
			bfa_trc(phy, attr->status);
			bfa_trc(phy, attr->length);
		पूर्ण

		phy->status = status;
		phy->op_busy = 0;
		अगर (phy->cbfn)
			phy->cbfn(phy->cbarg, phy->status);
		अवरोध;
	हाल BFI_PHY_I2H_STATS_RSP:
		status = be32_to_cpu(m.stats->status);
		bfa_trc(phy, status);

		अगर (status == BFA_STATUS_OK) अणु
			काष्ठा bfa_phy_stats_s *stats =
				(काष्ठा bfa_phy_stats_s *) phy->ubuf;
			bfa_phy_ntoh32((u32 *)stats, (u32 *)phy->dbuf_kva,
				माप(काष्ठा bfa_phy_stats_s));
			bfa_trc(phy, stats->status);
		पूर्ण

		phy->status = status;
		phy->op_busy = 0;
		अगर (phy->cbfn)
			phy->cbfn(phy->cbarg, phy->status);
		अवरोध;
	हाल BFI_PHY_I2H_WRITE_RSP:
		status = be32_to_cpu(m.ग_लिखो->status);
		bfa_trc(phy, status);

		अगर (status != BFA_STATUS_OK || phy->residue == 0) अणु
			phy->status = status;
			phy->op_busy = 0;
			अगर (phy->cbfn)
				phy->cbfn(phy->cbarg, phy->status);
		पूर्ण अन्यथा अणु
			bfa_trc(phy, phy->offset);
			bfa_phy_ग_लिखो_send(phy);
		पूर्ण
		अवरोध;
	हाल BFI_PHY_I2H_READ_RSP:
		status = be32_to_cpu(m.पढ़ो->status);
		bfa_trc(phy, status);

		अगर (status != BFA_STATUS_OK) अणु
			phy->status = status;
			phy->op_busy = 0;
			अगर (phy->cbfn)
				phy->cbfn(phy->cbarg, phy->status);
		पूर्ण अन्यथा अणु
			u32 len = be32_to_cpu(m.पढ़ो->length);
			u16 *buf = (u16 *)(phy->ubuf + phy->offset);
			u16 *dbuf = (u16 *)phy->dbuf_kva;
			पूर्णांक i, sz = len >> 1;

			bfa_trc(phy, phy->offset);
			bfa_trc(phy, len);

			क्रम (i = 0; i < sz; i++)
				buf[i] = be16_to_cpu(dbuf[i]);

			phy->residue -= len;
			phy->offset += len;

			अगर (phy->residue == 0) अणु
				phy->status = status;
				phy->op_busy = 0;
				अगर (phy->cbfn)
					phy->cbfn(phy->cbarg, phy->status);
			पूर्ण अन्यथा
				bfa_phy_पढ़ो_send(phy);
		पूर्ण
		अवरोध;
	शेष:
		WARN_ON(1);
	पूर्ण
पूर्ण

/*
 * DCONF state machine events
 */
क्रमागत bfa_dconf_event अणु
	BFA_DCONF_SM_INIT		= 1,	/* dconf Init */
	BFA_DCONF_SM_FLASH_COMP		= 2,	/* पढ़ो/ग_लिखो to flash */
	BFA_DCONF_SM_WR			= 3,	/* binding change, map */
	BFA_DCONF_SM_TIMEOUT		= 4,	/* Start समयr */
	BFA_DCONF_SM_EXIT		= 5,	/* निकास dconf module */
	BFA_DCONF_SM_IOCDISABLE		= 6,	/* IOC disable event */
पूर्ण;

/* क्रमward declaration of DCONF state machine */
अटल व्योम bfa_dconf_sm_uninit(काष्ठा bfa_dconf_mod_s *dconf,
				क्रमागत bfa_dconf_event event);
अटल व्योम bfa_dconf_sm_flash_पढ़ो(काष्ठा bfa_dconf_mod_s *dconf,
				क्रमागत bfa_dconf_event event);
अटल व्योम bfa_dconf_sm_पढ़ोy(काष्ठा bfa_dconf_mod_s *dconf,
				क्रमागत bfa_dconf_event event);
अटल व्योम bfa_dconf_sm_dirty(काष्ठा bfa_dconf_mod_s *dconf,
				क्रमागत bfa_dconf_event event);
अटल व्योम bfa_dconf_sm_sync(काष्ठा bfa_dconf_mod_s *dconf,
				क्रमागत bfa_dconf_event event);
अटल व्योम bfa_dconf_sm_final_sync(काष्ठा bfa_dconf_mod_s *dconf,
				क्रमागत bfa_dconf_event event);
अटल व्योम bfa_dconf_sm_iocकरोwn_dirty(काष्ठा bfa_dconf_mod_s *dconf,
				क्रमागत bfa_dconf_event event);

अटल व्योम bfa_dconf_cbfn(व्योम *dconf, bfa_status_t status);
अटल व्योम bfa_dconf_समयr(व्योम *cbarg);
अटल bfa_status_t bfa_dconf_flash_ग_लिखो(काष्ठा bfa_dconf_mod_s *dconf);
अटल व्योम bfa_dconf_init_cb(व्योम *arg, bfa_status_t status);

/*
 * Beginning state of dconf module. Waiting क्रम an event to start.
 */
अटल व्योम
bfa_dconf_sm_uninit(काष्ठा bfa_dconf_mod_s *dconf, क्रमागत bfa_dconf_event event)
अणु
	bfa_status_t bfa_status;
	bfa_trc(dconf->bfa, event);

	चयन (event) अणु
	हाल BFA_DCONF_SM_INIT:
		अगर (dconf->min_cfg) अणु
			bfa_trc(dconf->bfa, dconf->min_cfg);
			bfa_fsm_send_event(&dconf->bfa->iocfc,
					IOCFC_E_DCONF_DONE);
			वापस;
		पूर्ण
		bfa_sm_set_state(dconf, bfa_dconf_sm_flash_पढ़ो);
		bfa_समयr_start(dconf->bfa, &dconf->समयr,
			bfa_dconf_समयr, dconf, 2 * BFA_DCONF_UPDATE_TOV);
		bfa_status = bfa_flash_पढ़ो_part(BFA_FLASH(dconf->bfa),
					BFA_FLASH_PART_DRV, dconf->instance,
					dconf->dconf,
					माप(काष्ठा bfa_dconf_s), 0,
					bfa_dconf_init_cb, dconf->bfa);
		अगर (bfa_status != BFA_STATUS_OK) अणु
			bfa_समयr_stop(&dconf->समयr);
			bfa_dconf_init_cb(dconf->bfa, BFA_STATUS_FAILED);
			bfa_sm_set_state(dconf, bfa_dconf_sm_uninit);
			वापस;
		पूर्ण
		अवरोध;
	हाल BFA_DCONF_SM_EXIT:
		bfa_fsm_send_event(&dconf->bfa->iocfc, IOCFC_E_DCONF_DONE);
		अवरोध;
	हाल BFA_DCONF_SM_IOCDISABLE:
	हाल BFA_DCONF_SM_WR:
	हाल BFA_DCONF_SM_FLASH_COMP:
		अवरोध;
	शेष:
		bfa_sm_fault(dconf->bfa, event);
	पूर्ण
पूर्ण

/*
 * Read flash क्रम dconf entries and make a call back to the driver once करोne.
 */
अटल व्योम
bfa_dconf_sm_flash_पढ़ो(काष्ठा bfa_dconf_mod_s *dconf,
			क्रमागत bfa_dconf_event event)
अणु
	bfa_trc(dconf->bfa, event);

	चयन (event) अणु
	हाल BFA_DCONF_SM_FLASH_COMP:
		bfa_समयr_stop(&dconf->समयr);
		bfa_sm_set_state(dconf, bfa_dconf_sm_पढ़ोy);
		अवरोध;
	हाल BFA_DCONF_SM_TIMEOUT:
		bfa_sm_set_state(dconf, bfa_dconf_sm_पढ़ोy);
		bfa_ioc_suspend(&dconf->bfa->ioc);
		अवरोध;
	हाल BFA_DCONF_SM_EXIT:
		bfa_समयr_stop(&dconf->समयr);
		bfa_sm_set_state(dconf, bfa_dconf_sm_uninit);
		bfa_fsm_send_event(&dconf->bfa->iocfc, IOCFC_E_DCONF_DONE);
		अवरोध;
	हाल BFA_DCONF_SM_IOCDISABLE:
		bfa_समयr_stop(&dconf->समयr);
		bfa_sm_set_state(dconf, bfa_dconf_sm_uninit);
		अवरोध;
	शेष:
		bfa_sm_fault(dconf->bfa, event);
	पूर्ण
पूर्ण

/*
 * DCONF Module is in पढ़ोy state. Has completed the initialization.
 */
अटल व्योम
bfa_dconf_sm_पढ़ोy(काष्ठा bfa_dconf_mod_s *dconf, क्रमागत bfa_dconf_event event)
अणु
	bfa_trc(dconf->bfa, event);

	चयन (event) अणु
	हाल BFA_DCONF_SM_WR:
		bfa_समयr_start(dconf->bfa, &dconf->समयr,
			bfa_dconf_समयr, dconf, BFA_DCONF_UPDATE_TOV);
		bfa_sm_set_state(dconf, bfa_dconf_sm_dirty);
		अवरोध;
	हाल BFA_DCONF_SM_EXIT:
		bfa_sm_set_state(dconf, bfa_dconf_sm_uninit);
		bfa_fsm_send_event(&dconf->bfa->iocfc, IOCFC_E_DCONF_DONE);
		अवरोध;
	हाल BFA_DCONF_SM_INIT:
	हाल BFA_DCONF_SM_IOCDISABLE:
		अवरोध;
	शेष:
		bfa_sm_fault(dconf->bfa, event);
	पूर्ण
पूर्ण

/*
 * entries are dirty, ग_लिखो back to the flash.
 */

अटल व्योम
bfa_dconf_sm_dirty(काष्ठा bfa_dconf_mod_s *dconf, क्रमागत bfa_dconf_event event)
अणु
	bfa_trc(dconf->bfa, event);

	चयन (event) अणु
	हाल BFA_DCONF_SM_TIMEOUT:
		bfa_sm_set_state(dconf, bfa_dconf_sm_sync);
		bfa_dconf_flash_ग_लिखो(dconf);
		अवरोध;
	हाल BFA_DCONF_SM_WR:
		bfa_समयr_stop(&dconf->समयr);
		bfa_समयr_start(dconf->bfa, &dconf->समयr,
			bfa_dconf_समयr, dconf, BFA_DCONF_UPDATE_TOV);
		अवरोध;
	हाल BFA_DCONF_SM_EXIT:
		bfa_समयr_stop(&dconf->समयr);
		bfa_समयr_start(dconf->bfa, &dconf->समयr,
			bfa_dconf_समयr, dconf, BFA_DCONF_UPDATE_TOV);
		bfa_sm_set_state(dconf, bfa_dconf_sm_final_sync);
		bfa_dconf_flash_ग_लिखो(dconf);
		अवरोध;
	हाल BFA_DCONF_SM_FLASH_COMP:
		अवरोध;
	हाल BFA_DCONF_SM_IOCDISABLE:
		bfa_समयr_stop(&dconf->समयr);
		bfa_sm_set_state(dconf, bfa_dconf_sm_iocकरोwn_dirty);
		अवरोध;
	शेष:
		bfa_sm_fault(dconf->bfa, event);
	पूर्ण
पूर्ण

/*
 * Sync the dconf entries to the flash.
 */
अटल व्योम
bfa_dconf_sm_final_sync(काष्ठा bfa_dconf_mod_s *dconf,
			क्रमागत bfa_dconf_event event)
अणु
	bfa_trc(dconf->bfa, event);

	चयन (event) अणु
	हाल BFA_DCONF_SM_IOCDISABLE:
	हाल BFA_DCONF_SM_FLASH_COMP:
		bfa_समयr_stop(&dconf->समयr);
		fallthrough;
	हाल BFA_DCONF_SM_TIMEOUT:
		bfa_sm_set_state(dconf, bfa_dconf_sm_uninit);
		bfa_fsm_send_event(&dconf->bfa->iocfc, IOCFC_E_DCONF_DONE);
		अवरोध;
	शेष:
		bfa_sm_fault(dconf->bfa, event);
	पूर्ण
पूर्ण

अटल व्योम
bfa_dconf_sm_sync(काष्ठा bfa_dconf_mod_s *dconf, क्रमागत bfa_dconf_event event)
अणु
	bfa_trc(dconf->bfa, event);

	चयन (event) अणु
	हाल BFA_DCONF_SM_FLASH_COMP:
		bfa_sm_set_state(dconf, bfa_dconf_sm_पढ़ोy);
		अवरोध;
	हाल BFA_DCONF_SM_WR:
		bfa_समयr_start(dconf->bfa, &dconf->समयr,
			bfa_dconf_समयr, dconf, BFA_DCONF_UPDATE_TOV);
		bfa_sm_set_state(dconf, bfa_dconf_sm_dirty);
		अवरोध;
	हाल BFA_DCONF_SM_EXIT:
		bfa_समयr_start(dconf->bfa, &dconf->समयr,
			bfa_dconf_समयr, dconf, BFA_DCONF_UPDATE_TOV);
		bfa_sm_set_state(dconf, bfa_dconf_sm_final_sync);
		अवरोध;
	हाल BFA_DCONF_SM_IOCDISABLE:
		bfa_sm_set_state(dconf, bfa_dconf_sm_iocकरोwn_dirty);
		अवरोध;
	शेष:
		bfa_sm_fault(dconf->bfa, event);
	पूर्ण
पूर्ण

अटल व्योम
bfa_dconf_sm_iocकरोwn_dirty(काष्ठा bfa_dconf_mod_s *dconf,
			क्रमागत bfa_dconf_event event)
अणु
	bfa_trc(dconf->bfa, event);

	चयन (event) अणु
	हाल BFA_DCONF_SM_INIT:
		bfa_समयr_start(dconf->bfa, &dconf->समयr,
			bfa_dconf_समयr, dconf, BFA_DCONF_UPDATE_TOV);
		bfa_sm_set_state(dconf, bfa_dconf_sm_dirty);
		अवरोध;
	हाल BFA_DCONF_SM_EXIT:
		bfa_sm_set_state(dconf, bfa_dconf_sm_uninit);
		bfa_fsm_send_event(&dconf->bfa->iocfc, IOCFC_E_DCONF_DONE);
		अवरोध;
	हाल BFA_DCONF_SM_IOCDISABLE:
		अवरोध;
	शेष:
		bfa_sm_fault(dconf->bfa, event);
	पूर्ण
पूर्ण

/*
 * Compute and वापस memory needed by DRV_CFG module.
 */
व्योम
bfa_dconf_meminfo(काष्ठा bfa_iocfc_cfg_s *cfg, काष्ठा bfa_meminfo_s *meminfo,
		  काष्ठा bfa_s *bfa)
अणु
	काष्ठा bfa_mem_kva_s *dconf_kva = BFA_MEM_DCONF_KVA(bfa);

	अगर (cfg->drvcfg.min_cfg)
		bfa_mem_kva_setup(meminfo, dconf_kva,
				माप(काष्ठा bfa_dconf_hdr_s));
	अन्यथा
		bfa_mem_kva_setup(meminfo, dconf_kva,
				माप(काष्ठा bfa_dconf_s));
पूर्ण

व्योम
bfa_dconf_attach(काष्ठा bfa_s *bfa, व्योम *bfad, काष्ठा bfa_iocfc_cfg_s *cfg)
अणु
	काष्ठा bfa_dconf_mod_s *dconf = BFA_DCONF_MOD(bfa);

	dconf->bfad = bfad;
	dconf->bfa = bfa;
	dconf->instance = bfa->ioc.port_id;
	bfa_trc(bfa, dconf->instance);

	dconf->dconf = (काष्ठा bfa_dconf_s *) bfa_mem_kva_curp(dconf);
	अगर (cfg->drvcfg.min_cfg) अणु
		bfa_mem_kva_curp(dconf) += माप(काष्ठा bfa_dconf_hdr_s);
		dconf->min_cfg = BFA_TRUE;
	पूर्ण अन्यथा अणु
		dconf->min_cfg = BFA_FALSE;
		bfa_mem_kva_curp(dconf) += माप(काष्ठा bfa_dconf_s);
	पूर्ण

	bfa_dconf_पढ़ो_data_valid(bfa) = BFA_FALSE;
	bfa_sm_set_state(dconf, bfa_dconf_sm_uninit);
पूर्ण

अटल व्योम
bfa_dconf_init_cb(व्योम *arg, bfa_status_t status)
अणु
	काष्ठा bfa_s *bfa = arg;
	काष्ठा bfa_dconf_mod_s *dconf = BFA_DCONF_MOD(bfa);

	अगर (status == BFA_STATUS_OK) अणु
		bfa_dconf_पढ़ो_data_valid(bfa) = BFA_TRUE;
		अगर (dconf->dconf->hdr.signature != BFI_DCONF_SIGNATURE)
			dconf->dconf->hdr.signature = BFI_DCONF_SIGNATURE;
		अगर (dconf->dconf->hdr.version != BFI_DCONF_VERSION)
			dconf->dconf->hdr.version = BFI_DCONF_VERSION;
	पूर्ण
	bfa_sm_send_event(dconf, BFA_DCONF_SM_FLASH_COMP);
	bfa_fsm_send_event(&bfa->iocfc, IOCFC_E_DCONF_DONE);
पूर्ण

व्योम
bfa_dconf_modinit(काष्ठा bfa_s *bfa)
अणु
	काष्ठा bfa_dconf_mod_s *dconf = BFA_DCONF_MOD(bfa);
	bfa_sm_send_event(dconf, BFA_DCONF_SM_INIT);
पूर्ण

अटल व्योम bfa_dconf_समयr(व्योम *cbarg)
अणु
	काष्ठा bfa_dconf_mod_s *dconf = cbarg;
	bfa_sm_send_event(dconf, BFA_DCONF_SM_TIMEOUT);
पूर्ण

व्योम
bfa_dconf_iocdisable(काष्ठा bfa_s *bfa)
अणु
	काष्ठा bfa_dconf_mod_s *dconf = BFA_DCONF_MOD(bfa);
	bfa_sm_send_event(dconf, BFA_DCONF_SM_IOCDISABLE);
पूर्ण

अटल bfa_status_t
bfa_dconf_flash_ग_लिखो(काष्ठा bfa_dconf_mod_s *dconf)
अणु
	bfa_status_t bfa_status;
	bfa_trc(dconf->bfa, 0);

	bfa_status = bfa_flash_update_part(BFA_FLASH(dconf->bfa),
				BFA_FLASH_PART_DRV, dconf->instance,
				dconf->dconf,  माप(काष्ठा bfa_dconf_s), 0,
				bfa_dconf_cbfn, dconf);
	अगर (bfa_status != BFA_STATUS_OK)
		WARN_ON(bfa_status);
	bfa_trc(dconf->bfa, bfa_status);

	वापस bfa_status;
पूर्ण

bfa_status_t
bfa_dconf_update(काष्ठा bfa_s *bfa)
अणु
	काष्ठा bfa_dconf_mod_s *dconf = BFA_DCONF_MOD(bfa);
	bfa_trc(dconf->bfa, 0);
	अगर (bfa_sm_cmp_state(dconf, bfa_dconf_sm_iocकरोwn_dirty))
		वापस BFA_STATUS_FAILED;

	अगर (dconf->min_cfg) अणु
		bfa_trc(dconf->bfa, dconf->min_cfg);
		वापस BFA_STATUS_FAILED;
	पूर्ण

	bfa_sm_send_event(dconf, BFA_DCONF_SM_WR);
	वापस BFA_STATUS_OK;
पूर्ण

अटल व्योम
bfa_dconf_cbfn(व्योम *arg, bfa_status_t status)
अणु
	काष्ठा bfa_dconf_mod_s *dconf = arg;
	WARN_ON(status);
	bfa_sm_send_event(dconf, BFA_DCONF_SM_FLASH_COMP);
पूर्ण

व्योम
bfa_dconf_modनिकास(काष्ठा bfa_s *bfa)
अणु
	काष्ठा bfa_dconf_mod_s *dconf = BFA_DCONF_MOD(bfa);
	bfa_sm_send_event(dconf, BFA_DCONF_SM_EXIT);
पूर्ण

/*
 * FRU specअगरic functions
 */

#घोषणा BFA_FRU_DMA_BUF_SZ	0x02000		/* 8k dma buffer */
#घोषणा BFA_FRU_CHINOOK_MAX_SIZE 0x10000
#घोषणा BFA_FRU_LIGHTNING_MAX_SIZE 0x200

अटल व्योम
bfa_fru_notअगरy(व्योम *cbarg, क्रमागत bfa_ioc_event_e event)
अणु
	काष्ठा bfa_fru_s *fru = cbarg;

	bfa_trc(fru, event);

	चयन (event) अणु
	हाल BFA_IOC_E_DISABLED:
	हाल BFA_IOC_E_FAILED:
		अगर (fru->op_busy) अणु
			fru->status = BFA_STATUS_IOC_FAILURE;
			fru->cbfn(fru->cbarg, fru->status);
			fru->op_busy = 0;
		पूर्ण
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण
पूर्ण

/*
 * Send fru ग_लिखो request.
 *
 * @param[in] cbarg - callback argument
 */
अटल व्योम
bfa_fru_ग_लिखो_send(व्योम *cbarg, क्रमागत bfi_fru_h2i_msgs msg_type)
अणु
	काष्ठा bfa_fru_s *fru = cbarg;
	काष्ठा bfi_fru_ग_लिखो_req_s *msg =
			(काष्ठा bfi_fru_ग_लिखो_req_s *) fru->mb.msg;
	u32 len;

	msg->offset = cpu_to_be32(fru->addr_off + fru->offset);
	len = (fru->residue < BFA_FRU_DMA_BUF_SZ) ?
				fru->residue : BFA_FRU_DMA_BUF_SZ;
	msg->length = cpu_to_be32(len);

	/*
	 * indicate अगर it's the last msg of the whole ग_लिखो operation
	 */
	msg->last = (len == fru->residue) ? 1 : 0;

	msg->trfr_cmpl = (len == fru->residue) ? fru->trfr_cmpl : 0;
	bfi_h2i_set(msg->mh, BFI_MC_FRU, msg_type, bfa_ioc_portid(fru->ioc));
	bfa_alen_set(&msg->alen, len, fru->dbuf_pa);

	स_नकल(fru->dbuf_kva, fru->ubuf + fru->offset, len);
	bfa_ioc_mbox_queue(fru->ioc, &fru->mb);

	fru->residue -= len;
	fru->offset += len;
पूर्ण

/*
 * Send fru पढ़ो request.
 *
 * @param[in] cbarg - callback argument
 */
अटल व्योम
bfa_fru_पढ़ो_send(व्योम *cbarg, क्रमागत bfi_fru_h2i_msgs msg_type)
अणु
	काष्ठा bfa_fru_s *fru = cbarg;
	काष्ठा bfi_fru_पढ़ो_req_s *msg =
			(काष्ठा bfi_fru_पढ़ो_req_s *) fru->mb.msg;
	u32 len;

	msg->offset = cpu_to_be32(fru->addr_off + fru->offset);
	len = (fru->residue < BFA_FRU_DMA_BUF_SZ) ?
				fru->residue : BFA_FRU_DMA_BUF_SZ;
	msg->length = cpu_to_be32(len);
	bfi_h2i_set(msg->mh, BFI_MC_FRU, msg_type, bfa_ioc_portid(fru->ioc));
	bfa_alen_set(&msg->alen, len, fru->dbuf_pa);
	bfa_ioc_mbox_queue(fru->ioc, &fru->mb);
पूर्ण

/*
 * Flash memory info API.
 *
 * @param[in] mincfg - minimal cfg variable
 */
u32
bfa_fru_meminfo(bfa_boolean_t mincfg)
अणु
	/* min driver करोesn't need fru */
	अगर (mincfg)
		वापस 0;

	वापस BFA_ROUNDUP(BFA_FRU_DMA_BUF_SZ, BFA_DMA_ALIGN_SZ);
पूर्ण

/*
 * Flash attach API.
 *
 * @param[in] fru - fru काष्ठाure
 * @param[in] ioc  - ioc काष्ठाure
 * @param[in] dev  - device काष्ठाure
 * @param[in] trcmod - trace module
 * @param[in] logmod - log module
 */
व्योम
bfa_fru_attach(काष्ठा bfa_fru_s *fru, काष्ठा bfa_ioc_s *ioc, व्योम *dev,
	काष्ठा bfa_trc_mod_s *trcmod, bfa_boolean_t mincfg)
अणु
	fru->ioc = ioc;
	fru->trcmod = trcmod;
	fru->cbfn = शून्य;
	fru->cbarg = शून्य;
	fru->op_busy = 0;

	bfa_ioc_mbox_regisr(fru->ioc, BFI_MC_FRU, bfa_fru_पूर्णांकr, fru);
	bfa_q_qe_init(&fru->ioc_notअगरy);
	bfa_ioc_notअगरy_init(&fru->ioc_notअगरy, bfa_fru_notअगरy, fru);
	list_add_tail(&fru->ioc_notअगरy.qe, &fru->ioc->notअगरy_q);

	/* min driver करोesn't need fru */
	अगर (mincfg) अणु
		fru->dbuf_kva = शून्य;
		fru->dbuf_pa = 0;
	पूर्ण
पूर्ण

/*
 * Claim memory क्रम fru
 *
 * @param[in] fru - fru काष्ठाure
 * @param[in] dm_kva - poपूर्णांकer to भव memory address
 * @param[in] dm_pa - frusical memory address
 * @param[in] mincfg - minimal cfg variable
 */
व्योम
bfa_fru_memclaim(काष्ठा bfa_fru_s *fru, u8 *dm_kva, u64 dm_pa,
	bfa_boolean_t mincfg)
अणु
	अगर (mincfg)
		वापस;

	fru->dbuf_kva = dm_kva;
	fru->dbuf_pa = dm_pa;
	स_रखो(fru->dbuf_kva, 0, BFA_FRU_DMA_BUF_SZ);
	dm_kva += BFA_ROUNDUP(BFA_FRU_DMA_BUF_SZ, BFA_DMA_ALIGN_SZ);
	dm_pa += BFA_ROUNDUP(BFA_FRU_DMA_BUF_SZ, BFA_DMA_ALIGN_SZ);
पूर्ण

/*
 * Update fru vpd image.
 *
 * @param[in] fru - fru काष्ठाure
 * @param[in] buf - update data buffer
 * @param[in] len - data buffer length
 * @param[in] offset - offset relative to starting address
 * @param[in] cbfn - callback function
 * @param[in] cbarg - callback argument
 *
 * Return status.
 */
bfa_status_t
bfa_fruvpd_update(काष्ठा bfa_fru_s *fru, व्योम *buf, u32 len, u32 offset,
		  bfa_cb_fru_t cbfn, व्योम *cbarg, u8 trfr_cmpl)
अणु
	bfa_trc(fru, BFI_FRUVPD_H2I_WRITE_REQ);
	bfa_trc(fru, len);
	bfa_trc(fru, offset);

	अगर (fru->ioc->asic_gen != BFI_ASIC_GEN_CT2 &&
		fru->ioc->attr->card_type != BFA_MFG_TYPE_CHINOOK2)
		वापस BFA_STATUS_FRU_NOT_PRESENT;

	अगर (fru->ioc->attr->card_type != BFA_MFG_TYPE_CHINOOK)
		वापस BFA_STATUS_CMD_NOTSUPP;

	अगर (!bfa_ioc_is_operational(fru->ioc))
		वापस BFA_STATUS_IOC_NON_OP;

	अगर (fru->op_busy) अणु
		bfa_trc(fru, fru->op_busy);
		वापस BFA_STATUS_DEVBUSY;
	पूर्ण

	fru->op_busy = 1;

	fru->cbfn = cbfn;
	fru->cbarg = cbarg;
	fru->residue = len;
	fru->offset = 0;
	fru->addr_off = offset;
	fru->ubuf = buf;
	fru->trfr_cmpl = trfr_cmpl;

	bfa_fru_ग_लिखो_send(fru, BFI_FRUVPD_H2I_WRITE_REQ);

	वापस BFA_STATUS_OK;
पूर्ण

/*
 * Read fru vpd image.
 *
 * @param[in] fru - fru काष्ठाure
 * @param[in] buf - पढ़ो data buffer
 * @param[in] len - data buffer length
 * @param[in] offset - offset relative to starting address
 * @param[in] cbfn - callback function
 * @param[in] cbarg - callback argument
 *
 * Return status.
 */
bfa_status_t
bfa_fruvpd_पढ़ो(काष्ठा bfa_fru_s *fru, व्योम *buf, u32 len, u32 offset,
		bfa_cb_fru_t cbfn, व्योम *cbarg)
अणु
	bfa_trc(fru, BFI_FRUVPD_H2I_READ_REQ);
	bfa_trc(fru, len);
	bfa_trc(fru, offset);

	अगर (fru->ioc->asic_gen != BFI_ASIC_GEN_CT2)
		वापस BFA_STATUS_FRU_NOT_PRESENT;

	अगर (fru->ioc->attr->card_type != BFA_MFG_TYPE_CHINOOK &&
		fru->ioc->attr->card_type != BFA_MFG_TYPE_CHINOOK2)
		वापस BFA_STATUS_CMD_NOTSUPP;

	अगर (!bfa_ioc_is_operational(fru->ioc))
		वापस BFA_STATUS_IOC_NON_OP;

	अगर (fru->op_busy) अणु
		bfa_trc(fru, fru->op_busy);
		वापस BFA_STATUS_DEVBUSY;
	पूर्ण

	fru->op_busy = 1;

	fru->cbfn = cbfn;
	fru->cbarg = cbarg;
	fru->residue = len;
	fru->offset = 0;
	fru->addr_off = offset;
	fru->ubuf = buf;
	bfa_fru_पढ़ो_send(fru, BFI_FRUVPD_H2I_READ_REQ);

	वापस BFA_STATUS_OK;
पूर्ण

/*
 * Get maximum size fru vpd image.
 *
 * @param[in] fru - fru काष्ठाure
 * @param[out] size - maximum size of fru vpd data
 *
 * Return status.
 */
bfa_status_t
bfa_fruvpd_get_max_size(काष्ठा bfa_fru_s *fru, u32 *max_size)
अणु
	अगर (fru->ioc->asic_gen != BFI_ASIC_GEN_CT2)
		वापस BFA_STATUS_FRU_NOT_PRESENT;

	अगर (!bfa_ioc_is_operational(fru->ioc))
		वापस BFA_STATUS_IOC_NON_OP;

	अगर (fru->ioc->attr->card_type == BFA_MFG_TYPE_CHINOOK ||
		fru->ioc->attr->card_type == BFA_MFG_TYPE_CHINOOK2)
		*max_size = BFA_FRU_CHINOOK_MAX_SIZE;
	अन्यथा
		वापस BFA_STATUS_CMD_NOTSUPP;
	वापस BFA_STATUS_OK;
पूर्ण
/*
 * tfru ग_लिखो.
 *
 * @param[in] fru - fru काष्ठाure
 * @param[in] buf - update data buffer
 * @param[in] len - data buffer length
 * @param[in] offset - offset relative to starting address
 * @param[in] cbfn - callback function
 * @param[in] cbarg - callback argument
 *
 * Return status.
 */
bfa_status_t
bfa_tfru_ग_लिखो(काष्ठा bfa_fru_s *fru, व्योम *buf, u32 len, u32 offset,
	       bfa_cb_fru_t cbfn, व्योम *cbarg)
अणु
	bfa_trc(fru, BFI_TFRU_H2I_WRITE_REQ);
	bfa_trc(fru, len);
	bfa_trc(fru, offset);
	bfa_trc(fru, *((u8 *) buf));

	अगर (fru->ioc->asic_gen != BFI_ASIC_GEN_CT2)
		वापस BFA_STATUS_FRU_NOT_PRESENT;

	अगर (!bfa_ioc_is_operational(fru->ioc))
		वापस BFA_STATUS_IOC_NON_OP;

	अगर (fru->op_busy) अणु
		bfa_trc(fru, fru->op_busy);
		वापस BFA_STATUS_DEVBUSY;
	पूर्ण

	fru->op_busy = 1;

	fru->cbfn = cbfn;
	fru->cbarg = cbarg;
	fru->residue = len;
	fru->offset = 0;
	fru->addr_off = offset;
	fru->ubuf = buf;

	bfa_fru_ग_लिखो_send(fru, BFI_TFRU_H2I_WRITE_REQ);

	वापस BFA_STATUS_OK;
पूर्ण

/*
 * tfru पढ़ो.
 *
 * @param[in] fru - fru काष्ठाure
 * @param[in] buf - पढ़ो data buffer
 * @param[in] len - data buffer length
 * @param[in] offset - offset relative to starting address
 * @param[in] cbfn - callback function
 * @param[in] cbarg - callback argument
 *
 * Return status.
 */
bfa_status_t
bfa_tfru_पढ़ो(काष्ठा bfa_fru_s *fru, व्योम *buf, u32 len, u32 offset,
	      bfa_cb_fru_t cbfn, व्योम *cbarg)
अणु
	bfa_trc(fru, BFI_TFRU_H2I_READ_REQ);
	bfa_trc(fru, len);
	bfa_trc(fru, offset);

	अगर (fru->ioc->asic_gen != BFI_ASIC_GEN_CT2)
		वापस BFA_STATUS_FRU_NOT_PRESENT;

	अगर (!bfa_ioc_is_operational(fru->ioc))
		वापस BFA_STATUS_IOC_NON_OP;

	अगर (fru->op_busy) अणु
		bfa_trc(fru, fru->op_busy);
		वापस BFA_STATUS_DEVBUSY;
	पूर्ण

	fru->op_busy = 1;

	fru->cbfn = cbfn;
	fru->cbarg = cbarg;
	fru->residue = len;
	fru->offset = 0;
	fru->addr_off = offset;
	fru->ubuf = buf;
	bfa_fru_पढ़ो_send(fru, BFI_TFRU_H2I_READ_REQ);

	वापस BFA_STATUS_OK;
पूर्ण

/*
 * Process fru response messages upon receiving पूर्णांकerrupts.
 *
 * @param[in] fruarg - fru काष्ठाure
 * @param[in] msg - message काष्ठाure
 */
व्योम
bfa_fru_पूर्णांकr(व्योम *fruarg, काष्ठा bfi_mbmsg_s *msg)
अणु
	काष्ठा bfa_fru_s *fru = fruarg;
	काष्ठा bfi_fru_rsp_s *rsp = (काष्ठा bfi_fru_rsp_s *)msg;
	u32 status;

	bfa_trc(fru, msg->mh.msg_id);

	अगर (!fru->op_busy) अणु
		/*
		 * receiving response after ioc failure
		 */
		bfa_trc(fru, 0x9999);
		वापस;
	पूर्ण

	चयन (msg->mh.msg_id) अणु
	हाल BFI_FRUVPD_I2H_WRITE_RSP:
	हाल BFI_TFRU_I2H_WRITE_RSP:
		status = be32_to_cpu(rsp->status);
		bfa_trc(fru, status);

		अगर (status != BFA_STATUS_OK || fru->residue == 0) अणु
			fru->status = status;
			fru->op_busy = 0;
			अगर (fru->cbfn)
				fru->cbfn(fru->cbarg, fru->status);
		पूर्ण अन्यथा अणु
			bfa_trc(fru, fru->offset);
			अगर (msg->mh.msg_id == BFI_FRUVPD_I2H_WRITE_RSP)
				bfa_fru_ग_लिखो_send(fru,
					BFI_FRUVPD_H2I_WRITE_REQ);
			अन्यथा
				bfa_fru_ग_लिखो_send(fru,
					BFI_TFRU_H2I_WRITE_REQ);
		पूर्ण
		अवरोध;
	हाल BFI_FRUVPD_I2H_READ_RSP:
	हाल BFI_TFRU_I2H_READ_RSP:
		status = be32_to_cpu(rsp->status);
		bfa_trc(fru, status);

		अगर (status != BFA_STATUS_OK) अणु
			fru->status = status;
			fru->op_busy = 0;
			अगर (fru->cbfn)
				fru->cbfn(fru->cbarg, fru->status);
		पूर्ण अन्यथा अणु
			u32 len = be32_to_cpu(rsp->length);

			bfa_trc(fru, fru->offset);
			bfa_trc(fru, len);

			स_नकल(fru->ubuf + fru->offset, fru->dbuf_kva, len);
			fru->residue -= len;
			fru->offset += len;

			अगर (fru->residue == 0) अणु
				fru->status = status;
				fru->op_busy = 0;
				अगर (fru->cbfn)
					fru->cbfn(fru->cbarg, fru->status);
			पूर्ण अन्यथा अणु
				अगर (msg->mh.msg_id == BFI_FRUVPD_I2H_READ_RSP)
					bfa_fru_पढ़ो_send(fru,
						BFI_FRUVPD_H2I_READ_REQ);
				अन्यथा
					bfa_fru_पढ़ो_send(fru,
						BFI_TFRU_H2I_READ_REQ);
			पूर्ण
		पूर्ण
		अवरोध;
	शेष:
		WARN_ON(1);
	पूर्ण
पूर्ण

/*
 * रेजिस्टर definitions
 */
#घोषणा FLI_CMD_REG			0x0001d000
#घोषणा FLI_RDDATA_REG			0x0001d010
#घोषणा FLI_ADDR_REG			0x0001d004
#घोषणा FLI_DEV_STATUS_REG		0x0001d014

#घोषणा BFA_FLASH_FIFO_SIZE		128	/* fअगरo size */
#घोषणा BFA_FLASH_CHECK_MAX		10000	/* max # of status check */
#घोषणा BFA_FLASH_BLOCKING_OP_MAX	1000000	/* max # of blocking op check */
#घोषणा BFA_FLASH_WIP_MASK		0x01	/* ग_लिखो in progress bit mask */

क्रमागत bfa_flash_cmd अणु
	BFA_FLASH_FAST_READ	= 0x0b,	/* fast पढ़ो */
	BFA_FLASH_READ_STATUS	= 0x05,	/* पढ़ो status */
पूर्ण;

/*
 * Hardware error definition
 */
क्रमागत bfa_flash_err अणु
	BFA_FLASH_NOT_PRESENT	= -1,	/*!< flash not present */
	BFA_FLASH_UNINIT	= -2,	/*!< flash not initialized */
	BFA_FLASH_BAD		= -3,	/*!< flash bad */
	BFA_FLASH_BUSY		= -4,	/*!< flash busy */
	BFA_FLASH_ERR_CMD_ACT	= -5,	/*!< command active never cleared */
	BFA_FLASH_ERR_FIFO_CNT	= -6,	/*!< fअगरo count never cleared */
	BFA_FLASH_ERR_WIP	= -7,	/*!< ग_लिखो-in-progress never cleared */
	BFA_FLASH_ERR_TIMEOUT	= -8,	/*!< fli समयout */
	BFA_FLASH_ERR_LEN	= -9,	/*!< invalid length */
पूर्ण;

/*
 * Flash command रेजिस्टर data काष्ठाure
 */
जोड़ bfa_flash_cmd_reg_u अणु
	काष्ठा अणु
#अगर_घोषित __BIG_ENDIAN
		u32	act:1;
		u32	rsv:1;
		u32	ग_लिखो_cnt:9;
		u32	पढ़ो_cnt:9;
		u32	addr_cnt:4;
		u32	cmd:8;
#अन्यथा
		u32	cmd:8;
		u32	addr_cnt:4;
		u32	पढ़ो_cnt:9;
		u32	ग_लिखो_cnt:9;
		u32	rsv:1;
		u32	act:1;
#पूर्ण_अगर
	पूर्ण r;
	u32	i;
पूर्ण;

/*
 * Flash device status रेजिस्टर data काष्ठाure
 */
जोड़ bfa_flash_dev_status_reg_u अणु
	काष्ठा अणु
#अगर_घोषित __BIG_ENDIAN
		u32	rsv:21;
		u32	fअगरo_cnt:6;
		u32	busy:1;
		u32	init_status:1;
		u32	present:1;
		u32	bad:1;
		u32	good:1;
#अन्यथा
		u32	good:1;
		u32	bad:1;
		u32	present:1;
		u32	init_status:1;
		u32	busy:1;
		u32	fअगरo_cnt:6;
		u32	rsv:21;
#पूर्ण_अगर
	पूर्ण r;
	u32	i;
पूर्ण;

/*
 * Flash address रेजिस्टर data काष्ठाure
 */
जोड़ bfa_flash_addr_reg_u अणु
	काष्ठा अणु
#अगर_घोषित __BIG_ENDIAN
		u32	addr:24;
		u32	dummy:8;
#अन्यथा
		u32	dummy:8;
		u32	addr:24;
#पूर्ण_अगर
	पूर्ण r;
	u32	i;
पूर्ण;

/*
 * dg flash_raw_निजी Flash raw निजी functions
 */
अटल व्योम
bfa_flash_set_cmd(व्योम __iomem *pci_bar, u8 wr_cnt,
		  u8 rd_cnt, u8 ad_cnt, u8 op)
अणु
	जोड़ bfa_flash_cmd_reg_u cmd;

	cmd.i = 0;
	cmd.r.act = 1;
	cmd.r.ग_लिखो_cnt = wr_cnt;
	cmd.r.पढ़ो_cnt = rd_cnt;
	cmd.r.addr_cnt = ad_cnt;
	cmd.r.cmd = op;
	ग_लिखोl(cmd.i, (pci_bar + FLI_CMD_REG));
पूर्ण

अटल व्योम
bfa_flash_set_addr(व्योम __iomem *pci_bar, u32 address)
अणु
	जोड़ bfa_flash_addr_reg_u addr;

	addr.r.addr = address & 0x00ffffff;
	addr.r.dummy = 0;
	ग_लिखोl(addr.i, (pci_bar + FLI_ADDR_REG));
पूर्ण

अटल पूर्णांक
bfa_flash_cmd_act_check(व्योम __iomem *pci_bar)
अणु
	जोड़ bfa_flash_cmd_reg_u cmd;

	cmd.i = पढ़ोl(pci_bar + FLI_CMD_REG);

	अगर (cmd.r.act)
		वापस BFA_FLASH_ERR_CMD_ACT;

	वापस 0;
पूर्ण

/*
 * @brief
 * Flush FLI data fअगरo.
 *
 * @param[in] pci_bar - pci bar address
 * @param[in] dev_status - device status
 *
 * Return 0 on success, negative error number on error.
 */
अटल u32
bfa_flash_fअगरo_flush(व्योम __iomem *pci_bar)
अणु
	u32 i;
	जोड़ bfa_flash_dev_status_reg_u dev_status;

	dev_status.i = पढ़ोl(pci_bar + FLI_DEV_STATUS_REG);

	अगर (!dev_status.r.fअगरo_cnt)
		वापस 0;

	/* fअगरo counter in terms of words */
	क्रम (i = 0; i < dev_status.r.fअगरo_cnt; i++)
		पढ़ोl(pci_bar + FLI_RDDATA_REG);

	/*
	 * Check the device status. It may take some समय.
	 */
	क्रम (i = 0; i < BFA_FLASH_CHECK_MAX; i++) अणु
		dev_status.i = पढ़ोl(pci_bar + FLI_DEV_STATUS_REG);
		अगर (!dev_status.r.fअगरo_cnt)
			अवरोध;
	पूर्ण

	अगर (dev_status.r.fअगरo_cnt)
		वापस BFA_FLASH_ERR_FIFO_CNT;

	वापस 0;
पूर्ण

/*
 * @brief
 * Read flash status.
 *
 * @param[in] pci_bar - pci bar address
 *
 * Return 0 on success, negative error number on error.
*/
अटल u32
bfa_flash_status_पढ़ो(व्योम __iomem *pci_bar)
अणु
	जोड़ bfa_flash_dev_status_reg_u	dev_status;
	पूर्णांक				status;
	u32			ret_status;
	पूर्णांक				i;

	status = bfa_flash_fअगरo_flush(pci_bar);
	अगर (status < 0)
		वापस status;

	bfa_flash_set_cmd(pci_bar, 0, 4, 0, BFA_FLASH_READ_STATUS);

	क्रम (i = 0; i < BFA_FLASH_CHECK_MAX; i++) अणु
		status = bfa_flash_cmd_act_check(pci_bar);
		अगर (!status)
			अवरोध;
	पूर्ण

	अगर (status)
		वापस status;

	dev_status.i = पढ़ोl(pci_bar + FLI_DEV_STATUS_REG);
	अगर (!dev_status.r.fअगरo_cnt)
		वापस BFA_FLASH_BUSY;

	ret_status = पढ़ोl(pci_bar + FLI_RDDATA_REG);
	ret_status >>= 24;

	status = bfa_flash_fअगरo_flush(pci_bar);
	अगर (status < 0)
		वापस status;

	वापस ret_status;
पूर्ण

/*
 * @brief
 * Start flash पढ़ो operation.
 *
 * @param[in] pci_bar - pci bar address
 * @param[in] offset - flash address offset
 * @param[in] len - पढ़ो data length
 * @param[in] buf - पढ़ो data buffer
 *
 * Return 0 on success, negative error number on error.
 */
अटल u32
bfa_flash_पढ़ो_start(व्योम __iomem *pci_bar, u32 offset, u32 len,
			 अक्षर *buf)
अणु
	पूर्णांक status;

	/*
	 * len must be mutiple of 4 and not exceeding fअगरo size
	 */
	अगर (len == 0 || len > BFA_FLASH_FIFO_SIZE || (len & 0x03) != 0)
		वापस BFA_FLASH_ERR_LEN;

	/*
	 * check status
	 */
	status = bfa_flash_status_पढ़ो(pci_bar);
	अगर (status == BFA_FLASH_BUSY)
		status = bfa_flash_status_पढ़ो(pci_bar);

	अगर (status < 0)
		वापस status;

	/*
	 * check अगर ग_लिखो-in-progress bit is cleared
	 */
	अगर (status & BFA_FLASH_WIP_MASK)
		वापस BFA_FLASH_ERR_WIP;

	bfa_flash_set_addr(pci_bar, offset);

	bfa_flash_set_cmd(pci_bar, 0, (u8)len, 4, BFA_FLASH_FAST_READ);

	वापस 0;
पूर्ण

/*
 * @brief
 * Check flash पढ़ो operation.
 *
 * @param[in] pci_bar - pci bar address
 *
 * Return flash device status, 1 अगर busy, 0 अगर not.
 */
अटल u32
bfa_flash_पढ़ो_check(व्योम __iomem *pci_bar)
अणु
	अगर (bfa_flash_cmd_act_check(pci_bar))
		वापस 1;

	वापस 0;
पूर्ण

/*
 * @brief
 * End flash पढ़ो operation.
 *
 * @param[in] pci_bar - pci bar address
 * @param[in] len - पढ़ो data length
 * @param[in] buf - पढ़ो data buffer
 *
 */
अटल व्योम
bfa_flash_पढ़ो_end(व्योम __iomem *pci_bar, u32 len, अक्षर *buf)
अणु

	u32 i;

	/*
	 * पढ़ो data fअगरo up to 32 words
	 */
	क्रम (i = 0; i < len; i += 4) अणु
		u32 w = पढ़ोl(pci_bar + FLI_RDDATA_REG);
		*((u32 *) (buf + i)) = swab32(w);
	पूर्ण

	bfa_flash_fअगरo_flush(pci_bar);
पूर्ण

/*
 * @brief
 * Perक्रमm flash raw पढ़ो.
 *
 * @param[in] pci_bar - pci bar address
 * @param[in] offset - flash partition address offset
 * @param[in] buf - पढ़ो data buffer
 * @param[in] len - पढ़ो data length
 *
 * Return status.
 */


#घोषणा FLASH_BLOCKING_OP_MAX   500
#घोषणा FLASH_SEM_LOCK_REG	0x18820

अटल पूर्णांक
bfa_raw_sem_get(व्योम __iomem *bar)
अणु
	पूर्णांक	locked;

	locked = पढ़ोl((bar + FLASH_SEM_LOCK_REG));
	वापस !locked;

पूर्ण

अटल bfa_status_t
bfa_flash_sem_get(व्योम __iomem *bar)
अणु
	u32 n = FLASH_BLOCKING_OP_MAX;

	जबतक (!bfa_raw_sem_get(bar)) अणु
		अगर (--n <= 0)
			वापस BFA_STATUS_BADFLASH;
		mdelay(10);
	पूर्ण
	वापस BFA_STATUS_OK;
पूर्ण

अटल व्योम
bfa_flash_sem_put(व्योम __iomem *bar)
अणु
	ग_लिखोl(0, (bar + FLASH_SEM_LOCK_REG));
पूर्ण

bfa_status_t
bfa_flash_raw_पढ़ो(व्योम __iomem *pci_bar, u32 offset, अक्षर *buf,
		       u32 len)
अणु
	u32 n;
	पूर्णांक status;
	u32 off, l, s, residue, fअगरo_sz;

	residue = len;
	off = 0;
	fअगरo_sz = BFA_FLASH_FIFO_SIZE;
	status = bfa_flash_sem_get(pci_bar);
	अगर (status != BFA_STATUS_OK)
		वापस status;

	जबतक (residue) अणु
		s = offset + off;
		n = s / fअगरo_sz;
		l = (n + 1) * fअगरo_sz - s;
		अगर (l > residue)
			l = residue;

		status = bfa_flash_पढ़ो_start(pci_bar, offset + off, l,
								&buf[off]);
		अगर (status < 0) अणु
			bfa_flash_sem_put(pci_bar);
			वापस BFA_STATUS_FAILED;
		पूर्ण

		n = BFA_FLASH_BLOCKING_OP_MAX;
		जबतक (bfa_flash_पढ़ो_check(pci_bar)) अणु
			अगर (--n <= 0) अणु
				bfa_flash_sem_put(pci_bar);
				वापस BFA_STATUS_FAILED;
			पूर्ण
		पूर्ण

		bfa_flash_पढ़ो_end(pci_bar, l, &buf[off]);

		residue -= l;
		off += l;
	पूर्ण
	bfa_flash_sem_put(pci_bar);

	वापस BFA_STATUS_OK;
पूर्ण
