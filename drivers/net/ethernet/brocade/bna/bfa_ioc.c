<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Linux network driver क्रम QLogic BR-series Converged Network Adapter.
 */
/*
 * Copyright (c) 2005-2014 Brocade Communications Systems, Inc.
 * Copyright (c) 2014-2015 QLogic Corporation
 * All rights reserved
 * www.qlogic.com
 */

#समावेश "bfa_ioc.h"
#समावेश "bfi_reg.h"
#समावेश "bfa_defs.h"

/* IOC local definitions */

/* Asic specअगरic macros : see bfa_hw_cb.c and bfa_hw_ct.c क्रम details. */

#घोषणा bfa_ioc_firmware_lock(__ioc)			\
			((__ioc)->ioc_hwअगर->ioc_firmware_lock(__ioc))
#घोषणा bfa_ioc_firmware_unlock(__ioc)			\
			((__ioc)->ioc_hwअगर->ioc_firmware_unlock(__ioc))
#घोषणा bfa_ioc_reg_init(__ioc) ((__ioc)->ioc_hwअगर->ioc_reg_init(__ioc))
#घोषणा bfa_ioc_map_port(__ioc) ((__ioc)->ioc_hwअगर->ioc_map_port(__ioc))
#घोषणा bfa_ioc_notअगरy_fail(__ioc)			\
			((__ioc)->ioc_hwअगर->ioc_notअगरy_fail(__ioc))
#घोषणा bfa_ioc_sync_start(__ioc)               \
			((__ioc)->ioc_hwअगर->ioc_sync_start(__ioc))
#घोषणा bfa_ioc_sync_join(__ioc)			\
			((__ioc)->ioc_hwअगर->ioc_sync_join(__ioc))
#घोषणा bfa_ioc_sync_leave(__ioc)			\
			((__ioc)->ioc_hwअगर->ioc_sync_leave(__ioc))
#घोषणा bfa_ioc_sync_ack(__ioc)				\
			((__ioc)->ioc_hwअगर->ioc_sync_ack(__ioc))
#घोषणा bfa_ioc_sync_complete(__ioc)			\
			((__ioc)->ioc_hwअगर->ioc_sync_complete(__ioc))
#घोषणा bfa_ioc_set_cur_ioc_fwstate(__ioc, __fwstate)		\
			((__ioc)->ioc_hwअगर->ioc_set_fwstate(__ioc, __fwstate))
#घोषणा bfa_ioc_get_cur_ioc_fwstate(__ioc)		\
			((__ioc)->ioc_hwअगर->ioc_get_fwstate(__ioc))
#घोषणा bfa_ioc_set_alt_ioc_fwstate(__ioc, __fwstate)		\
		((__ioc)->ioc_hwअगर->ioc_set_alt_fwstate(__ioc, __fwstate))

अटल bool bfa_nw_स्वतः_recover = true;

/*
 * क्रमward declarations
 */
अटल व्योम bfa_ioc_hw_sem_init(काष्ठा bfa_ioc *ioc);
अटल व्योम bfa_ioc_hw_sem_get(काष्ठा bfa_ioc *ioc);
अटल व्योम bfa_ioc_hw_sem_get_cancel(काष्ठा bfa_ioc *ioc);
अटल व्योम bfa_ioc_hwinit(काष्ठा bfa_ioc *ioc, bool क्रमce);
अटल व्योम bfa_ioc_poll_fwinit(काष्ठा bfa_ioc *ioc);
अटल व्योम bfa_ioc_send_enable(काष्ठा bfa_ioc *ioc);
अटल व्योम bfa_ioc_send_disable(काष्ठा bfa_ioc *ioc);
अटल व्योम bfa_ioc_send_getattr(काष्ठा bfa_ioc *ioc);
अटल व्योम bfa_ioc_hb_monitor(काष्ठा bfa_ioc *ioc);
अटल व्योम bfa_ioc_hb_stop(काष्ठा bfa_ioc *ioc);
अटल व्योम bfa_ioc_reset(काष्ठा bfa_ioc *ioc, bool क्रमce);
अटल व्योम bfa_ioc_mbox_poll(काष्ठा bfa_ioc *ioc);
अटल व्योम bfa_ioc_mbox_flush(काष्ठा bfa_ioc *ioc);
अटल व्योम bfa_ioc_recover(काष्ठा bfa_ioc *ioc);
अटल व्योम bfa_ioc_event_notअगरy(काष्ठा bfa_ioc *, क्रमागत bfa_ioc_event);
अटल व्योम bfa_ioc_disable_comp(काष्ठा bfa_ioc *ioc);
अटल व्योम bfa_ioc_lpu_stop(काष्ठा bfa_ioc *ioc);
अटल व्योम bfa_nw_ioc_debug_save_ftrc(काष्ठा bfa_ioc *ioc);
अटल व्योम bfa_ioc_fail_notअगरy(काष्ठा bfa_ioc *ioc);
अटल व्योम bfa_ioc_pf_enabled(काष्ठा bfa_ioc *ioc);
अटल व्योम bfa_ioc_pf_disabled(काष्ठा bfa_ioc *ioc);
अटल व्योम bfa_ioc_pf_failed(काष्ठा bfa_ioc *ioc);
अटल व्योम bfa_ioc_pf_hwfailed(काष्ठा bfa_ioc *ioc);
अटल व्योम bfa_ioc_pf_fwmismatch(काष्ठा bfa_ioc *ioc);
अटल क्रमागत bfa_status bfa_ioc_boot(काष्ठा bfa_ioc *ioc,
			क्रमागत bfi_fwboot_type boot_type, u32 boot_param);
अटल u32 bfa_ioc_smem_pgnum(काष्ठा bfa_ioc *ioc, u32 fmaddr);
अटल व्योम bfa_ioc_get_adapter_serial_num(काष्ठा bfa_ioc *ioc,
						अक्षर *serial_num);
अटल व्योम bfa_ioc_get_adapter_fw_ver(काष्ठा bfa_ioc *ioc,
						अक्षर *fw_ver);
अटल व्योम bfa_ioc_get_pci_chip_rev(काष्ठा bfa_ioc *ioc,
						अक्षर *chip_rev);
अटल व्योम bfa_ioc_get_adapter_optrom_ver(काष्ठा bfa_ioc *ioc,
						अक्षर *optrom_ver);
अटल व्योम bfa_ioc_get_adapter_manufacturer(काष्ठा bfa_ioc *ioc,
						अक्षर *manufacturer);
अटल व्योम bfa_ioc_get_adapter_model(काष्ठा bfa_ioc *ioc, अक्षर *model);
अटल u64 bfa_ioc_get_pwwn(काष्ठा bfa_ioc *ioc);

/* IOC state machine definitions/declarations */
क्रमागत ioc_event अणु
	IOC_E_RESET		= 1,	/*!< IOC reset request		*/
	IOC_E_ENABLE		= 2,	/*!< IOC enable request		*/
	IOC_E_DISABLE		= 3,	/*!< IOC disable request	*/
	IOC_E_DETACH		= 4,	/*!< driver detach cleanup	*/
	IOC_E_ENABLED		= 5,	/*!< f/w enabled		*/
	IOC_E_FWRSP_GETATTR	= 6,	/*!< IOC get attribute response	*/
	IOC_E_DISABLED		= 7,	/*!< f/w disabled		*/
	IOC_E_PFFAILED		= 8,	/*!< failure notice by iocpf sm	*/
	IOC_E_HBFAIL		= 9,	/*!< heartbeat failure		*/
	IOC_E_HWERROR		= 10,	/*!< hardware error पूर्णांकerrupt	*/
	IOC_E_TIMEOUT		= 11,	/*!< समयout			*/
	IOC_E_HWFAILED		= 12,	/*!< PCI mapping failure notice	*/
पूर्ण;

bfa_fsm_state_decl(bfa_ioc, uninit, काष्ठा bfa_ioc, क्रमागत ioc_event);
bfa_fsm_state_decl(bfa_ioc, reset, काष्ठा bfa_ioc, क्रमागत ioc_event);
bfa_fsm_state_decl(bfa_ioc, enabling, काष्ठा bfa_ioc, क्रमागत ioc_event);
bfa_fsm_state_decl(bfa_ioc, getattr, काष्ठा bfa_ioc, क्रमागत ioc_event);
bfa_fsm_state_decl(bfa_ioc, op, काष्ठा bfa_ioc, क्रमागत ioc_event);
bfa_fsm_state_decl(bfa_ioc, fail_retry, काष्ठा bfa_ioc, क्रमागत ioc_event);
bfa_fsm_state_decl(bfa_ioc, fail, काष्ठा bfa_ioc, क्रमागत ioc_event);
bfa_fsm_state_decl(bfa_ioc, disabling, काष्ठा bfa_ioc, क्रमागत ioc_event);
bfa_fsm_state_decl(bfa_ioc, disabled, काष्ठा bfa_ioc, क्रमागत ioc_event);
bfa_fsm_state_decl(bfa_ioc, hwfail, काष्ठा bfa_ioc, क्रमागत ioc_event);

अटल काष्ठा bfa_sm_table ioc_sm_table[] = अणु
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
 * Forward declareations क्रम iocpf state machine
 */
अटल व्योम bfa_iocpf_enable(काष्ठा bfa_ioc *ioc);
अटल व्योम bfa_iocpf_disable(काष्ठा bfa_ioc *ioc);
अटल व्योम bfa_iocpf_fail(काष्ठा bfa_ioc *ioc);
अटल व्योम bfa_iocpf_initfail(काष्ठा bfa_ioc *ioc);
अटल व्योम bfa_iocpf_getattrfail(काष्ठा bfa_ioc *ioc);
अटल व्योम bfa_iocpf_stop(काष्ठा bfa_ioc *ioc);

/* IOCPF state machine events */
क्रमागत iocpf_event अणु
	IOCPF_E_ENABLE		= 1,	/*!< IOCPF enable request	*/
	IOCPF_E_DISABLE		= 2,	/*!< IOCPF disable request	*/
	IOCPF_E_STOP		= 3,	/*!< stop on driver detach	*/
	IOCPF_E_FWREADY		= 4,	/*!< f/w initialization करोne	*/
	IOCPF_E_FWRSP_ENABLE	= 5,	/*!< enable f/w response	*/
	IOCPF_E_FWRSP_DISABLE	= 6,	/*!< disable f/w response	*/
	IOCPF_E_FAIL		= 7,	/*!< failure notice by ioc sm	*/
	IOCPF_E_INITFAIL	= 8,	/*!< init fail notice by ioc sm	*/
	IOCPF_E_GETATTRFAIL	= 9,	/*!< init fail notice by ioc sm	*/
	IOCPF_E_SEMLOCKED	= 10,   /*!< h/w semaphore is locked	*/
	IOCPF_E_TIMEOUT		= 11,   /*!< f/w response समयout	*/
	IOCPF_E_SEM_ERROR	= 12,   /*!< h/w sem mapping error	*/
पूर्ण;

/* IOCPF states */
क्रमागत bfa_iocpf_state अणु
	BFA_IOCPF_RESET		= 1,	/*!< IOC is in reset state */
	BFA_IOCPF_SEMWAIT	= 2,	/*!< Waiting क्रम IOC h/w semaphore */
	BFA_IOCPF_HWINIT	= 3,	/*!< IOC h/w is being initialized */
	BFA_IOCPF_READY		= 4,	/*!< IOCPF is initialized */
	BFA_IOCPF_INITFAIL	= 5,	/*!< IOCPF failed */
	BFA_IOCPF_FAIL		= 6,	/*!< IOCPF failed */
	BFA_IOCPF_DISABLING	= 7,	/*!< IOCPF is being disabled */
	BFA_IOCPF_DISABLED	= 8,	/*!< IOCPF is disabled */
	BFA_IOCPF_FWMISMATCH	= 9,	/*!< IOC f/w dअगरferent from drivers */
पूर्ण;

bfa_fsm_state_decl(bfa_iocpf, reset, काष्ठा bfa_iocpf, क्रमागत iocpf_event);
bfa_fsm_state_decl(bfa_iocpf, fwcheck, काष्ठा bfa_iocpf, क्रमागत iocpf_event);
bfa_fsm_state_decl(bfa_iocpf, mismatch, काष्ठा bfa_iocpf, क्रमागत iocpf_event);
bfa_fsm_state_decl(bfa_iocpf, semरुको, काष्ठा bfa_iocpf, क्रमागत iocpf_event);
bfa_fsm_state_decl(bfa_iocpf, hwinit, काष्ठा bfa_iocpf, क्रमागत iocpf_event);
bfa_fsm_state_decl(bfa_iocpf, enabling, काष्ठा bfa_iocpf, क्रमागत iocpf_event);
bfa_fsm_state_decl(bfa_iocpf, पढ़ोy, काष्ठा bfa_iocpf, क्रमागत iocpf_event);
bfa_fsm_state_decl(bfa_iocpf, initfail_sync, काष्ठा bfa_iocpf,
						क्रमागत iocpf_event);
bfa_fsm_state_decl(bfa_iocpf, initfail, काष्ठा bfa_iocpf, क्रमागत iocpf_event);
bfa_fsm_state_decl(bfa_iocpf, fail_sync, काष्ठा bfa_iocpf, क्रमागत iocpf_event);
bfa_fsm_state_decl(bfa_iocpf, fail, काष्ठा bfa_iocpf, क्रमागत iocpf_event);
bfa_fsm_state_decl(bfa_iocpf, disabling, काष्ठा bfa_iocpf, क्रमागत iocpf_event);
bfa_fsm_state_decl(bfa_iocpf, disabling_sync, काष्ठा bfa_iocpf,
						क्रमागत iocpf_event);
bfa_fsm_state_decl(bfa_iocpf, disabled, काष्ठा bfa_iocpf, क्रमागत iocpf_event);

अटल काष्ठा bfa_sm_table iocpf_sm_table[] = अणु
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

/* IOC State Machine */

/* Beginning state. IOC uninit state. */
अटल व्योम
bfa_ioc_sm_uninit_entry(काष्ठा bfa_ioc *ioc)
अणु
पूर्ण

/* IOC is in uninit state. */
अटल व्योम
bfa_ioc_sm_uninit(काष्ठा bfa_ioc *ioc, क्रमागत ioc_event event)
अणु
	चयन (event) अणु
	हाल IOC_E_RESET:
		bfa_fsm_set_state(ioc, bfa_ioc_sm_reset);
		अवरोध;

	शेष:
		bfa_sm_fault(event);
	पूर्ण
पूर्ण

/* Reset entry actions -- initialize state machine */
अटल व्योम
bfa_ioc_sm_reset_entry(काष्ठा bfa_ioc *ioc)
अणु
	bfa_fsm_set_state(&ioc->iocpf, bfa_iocpf_sm_reset);
पूर्ण

/* IOC is in reset state. */
अटल व्योम
bfa_ioc_sm_reset(काष्ठा bfa_ioc *ioc, क्रमागत ioc_event event)
अणु
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
		bfa_sm_fault(event);
	पूर्ण
पूर्ण

अटल व्योम
bfa_ioc_sm_enabling_entry(काष्ठा bfa_ioc *ioc)
अणु
	bfa_iocpf_enable(ioc);
पूर्ण

/* Host IOC function is being enabled, aरुकोing response from firmware.
 * Semaphore is acquired.
 */
अटल व्योम
bfa_ioc_sm_enabling(काष्ठा bfa_ioc *ioc, क्रमागत ioc_event event)
अणु
	चयन (event) अणु
	हाल IOC_E_ENABLED:
		bfa_fsm_set_state(ioc, bfa_ioc_sm_getattr);
		अवरोध;

	हाल IOC_E_PFFAILED:
		fallthrough;
	हाल IOC_E_HWERROR:
		ioc->cbfn->enable_cbfn(ioc->bfa, BFA_STATUS_IOC_FAILURE);
		bfa_fsm_set_state(ioc, bfa_ioc_sm_fail);
		अगर (event != IOC_E_PFFAILED)
			bfa_iocpf_initfail(ioc);
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
		bfa_iocpf_stop(ioc);
		अवरोध;

	हाल IOC_E_ENABLE:
		अवरोध;

	शेष:
		bfa_sm_fault(event);
	पूर्ण
पूर्ण

/* Semaphore should be acquired क्रम version check. */
अटल व्योम
bfa_ioc_sm_getattr_entry(काष्ठा bfa_ioc *ioc)
अणु
	mod_समयr(&ioc->ioc_समयr, jअगरfies +
		msecs_to_jअगरfies(BFA_IOC_TOV));
	bfa_ioc_send_getattr(ioc);
पूर्ण

/* IOC configuration in progress. Timer is active. */
अटल व्योम
bfa_ioc_sm_getattr(काष्ठा bfa_ioc *ioc, क्रमागत ioc_event event)
अणु
	चयन (event) अणु
	हाल IOC_E_FWRSP_GETATTR:
		del_समयr(&ioc->ioc_समयr);
		bfa_fsm_set_state(ioc, bfa_ioc_sm_op);
		अवरोध;

	हाल IOC_E_PFFAILED:
	हाल IOC_E_HWERROR:
		del_समयr(&ioc->ioc_समयr);
		fallthrough;
	हाल IOC_E_TIMEOUT:
		ioc->cbfn->enable_cbfn(ioc->bfa, BFA_STATUS_IOC_FAILURE);
		bfa_fsm_set_state(ioc, bfa_ioc_sm_fail);
		अगर (event != IOC_E_PFFAILED)
			bfa_iocpf_getattrfail(ioc);
		अवरोध;

	हाल IOC_E_DISABLE:
		del_समयr(&ioc->ioc_समयr);
		bfa_fsm_set_state(ioc, bfa_ioc_sm_disabling);
		अवरोध;

	हाल IOC_E_ENABLE:
		अवरोध;

	शेष:
		bfa_sm_fault(event);
	पूर्ण
पूर्ण

अटल व्योम
bfa_ioc_sm_op_entry(काष्ठा bfa_ioc *ioc)
अणु
	ioc->cbfn->enable_cbfn(ioc->bfa, BFA_STATUS_OK);
	bfa_ioc_event_notअगरy(ioc, BFA_IOC_E_ENABLED);
	bfa_ioc_hb_monitor(ioc);
पूर्ण

अटल व्योम
bfa_ioc_sm_op(काष्ठा bfa_ioc *ioc, क्रमागत ioc_event event)
अणु
	चयन (event) अणु
	हाल IOC_E_ENABLE:
		अवरोध;

	हाल IOC_E_DISABLE:
		bfa_ioc_hb_stop(ioc);
		bfa_fsm_set_state(ioc, bfa_ioc_sm_disabling);
		अवरोध;

	हाल IOC_E_PFFAILED:
	हाल IOC_E_HWERROR:
		bfa_ioc_hb_stop(ioc);
		fallthrough;

	हाल IOC_E_HBFAIL:
		अगर (ioc->iocpf.स्वतः_recover)
			bfa_fsm_set_state(ioc, bfa_ioc_sm_fail_retry);
		अन्यथा
			bfa_fsm_set_state(ioc, bfa_ioc_sm_fail);

		bfa_ioc_fail_notअगरy(ioc);

		अगर (event != IOC_E_PFFAILED)
			bfa_iocpf_fail(ioc);
		अवरोध;

	शेष:
		bfa_sm_fault(event);
	पूर्ण
पूर्ण

अटल व्योम
bfa_ioc_sm_disabling_entry(काष्ठा bfa_ioc *ioc)
अणु
	bfa_iocpf_disable(ioc);
पूर्ण

/* IOC is being disabled */
अटल व्योम
bfa_ioc_sm_disabling(काष्ठा bfa_ioc *ioc, क्रमागत ioc_event event)
अणु
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
		bfa_iocpf_fail(ioc);
		अवरोध;

	हाल IOC_E_HWFAILED:
		bfa_fsm_set_state(ioc, bfa_ioc_sm_hwfail);
		bfa_ioc_disable_comp(ioc);
		अवरोध;

	शेष:
		bfa_sm_fault(event);
	पूर्ण
पूर्ण

/* IOC disable completion entry. */
अटल व्योम
bfa_ioc_sm_disabled_entry(काष्ठा bfa_ioc *ioc)
अणु
	bfa_ioc_disable_comp(ioc);
पूर्ण

अटल व्योम
bfa_ioc_sm_disabled(काष्ठा bfa_ioc *ioc, क्रमागत ioc_event event)
अणु
	चयन (event) अणु
	हाल IOC_E_ENABLE:
		bfa_fsm_set_state(ioc, bfa_ioc_sm_enabling);
		अवरोध;

	हाल IOC_E_DISABLE:
		ioc->cbfn->disable_cbfn(ioc->bfa);
		अवरोध;

	हाल IOC_E_DETACH:
		bfa_fsm_set_state(ioc, bfa_ioc_sm_uninit);
		bfa_iocpf_stop(ioc);
		अवरोध;

	शेष:
		bfa_sm_fault(event);
	पूर्ण
पूर्ण

अटल व्योम
bfa_ioc_sm_fail_retry_entry(काष्ठा bfa_ioc *ioc)
अणु
पूर्ण

/* Hardware initialization retry. */
अटल व्योम
bfa_ioc_sm_fail_retry(काष्ठा bfa_ioc *ioc, क्रमागत ioc_event event)
अणु
	चयन (event) अणु
	हाल IOC_E_ENABLED:
		bfa_fsm_set_state(ioc, bfa_ioc_sm_getattr);
		अवरोध;

	हाल IOC_E_PFFAILED:
	हाल IOC_E_HWERROR:
		/**
		 * Initialization retry failed.
		 */
		ioc->cbfn->enable_cbfn(ioc->bfa, BFA_STATUS_IOC_FAILURE);
		bfa_fsm_set_state(ioc, bfa_ioc_sm_fail);
		अगर (event != IOC_E_PFFAILED)
			bfa_iocpf_initfail(ioc);
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
		bfa_iocpf_stop(ioc);
		अवरोध;

	शेष:
		bfa_sm_fault(event);
	पूर्ण
पूर्ण

अटल व्योम
bfa_ioc_sm_fail_entry(काष्ठा bfa_ioc *ioc)
अणु
पूर्ण

/* IOC failure. */
अटल व्योम
bfa_ioc_sm_fail(काष्ठा bfa_ioc *ioc, क्रमागत ioc_event event)
अणु
	चयन (event) अणु
	हाल IOC_E_ENABLE:
		ioc->cbfn->enable_cbfn(ioc->bfa, BFA_STATUS_IOC_FAILURE);
		अवरोध;

	हाल IOC_E_DISABLE:
		bfa_fsm_set_state(ioc, bfa_ioc_sm_disabling);
		अवरोध;

	हाल IOC_E_DETACH:
		bfa_fsm_set_state(ioc, bfa_ioc_sm_uninit);
		bfa_iocpf_stop(ioc);
		अवरोध;

	हाल IOC_E_HWERROR:
		/* HB failure notअगरication, ignore. */
		अवरोध;

	शेष:
		bfa_sm_fault(event);
	पूर्ण
पूर्ण

अटल व्योम
bfa_ioc_sm_hwfail_entry(काष्ठा bfa_ioc *ioc)
अणु
पूर्ण

/* IOC failure. */
अटल व्योम
bfa_ioc_sm_hwfail(काष्ठा bfa_ioc *ioc, क्रमागत ioc_event event)
अणु
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

	शेष:
		bfa_sm_fault(event);
	पूर्ण
पूर्ण

/* IOCPF State Machine */

/* Reset entry actions -- initialize state machine */
अटल व्योम
bfa_iocpf_sm_reset_entry(काष्ठा bfa_iocpf *iocpf)
अणु
	iocpf->fw_mismatch_notअगरied = false;
	iocpf->स्वतः_recover = bfa_nw_स्वतः_recover;
पूर्ण

/* Beginning state. IOC is in reset state. */
अटल व्योम
bfa_iocpf_sm_reset(काष्ठा bfa_iocpf *iocpf, क्रमागत iocpf_event event)
अणु
	चयन (event) अणु
	हाल IOCPF_E_ENABLE:
		bfa_fsm_set_state(iocpf, bfa_iocpf_sm_fwcheck);
		अवरोध;

	हाल IOCPF_E_STOP:
		अवरोध;

	शेष:
		bfa_sm_fault(event);
	पूर्ण
पूर्ण

/* Semaphore should be acquired क्रम version check. */
अटल व्योम
bfa_iocpf_sm_fwcheck_entry(काष्ठा bfa_iocpf *iocpf)
अणु
	bfa_ioc_hw_sem_init(iocpf->ioc);
	bfa_ioc_hw_sem_get(iocpf->ioc);
पूर्ण

/* Aरुकोing h/w semaphore to जारी with version check. */
अटल व्योम
bfa_iocpf_sm_fwcheck(काष्ठा bfa_iocpf *iocpf, क्रमागत iocpf_event event)
अणु
	काष्ठा bfa_ioc *ioc = iocpf->ioc;

	चयन (event) अणु
	हाल IOCPF_E_SEMLOCKED:
		अगर (bfa_ioc_firmware_lock(ioc)) अणु
			अगर (bfa_ioc_sync_start(ioc)) अणु
				bfa_ioc_sync_join(ioc);
				bfa_fsm_set_state(iocpf, bfa_iocpf_sm_hwinit);
			पूर्ण अन्यथा अणु
				bfa_ioc_firmware_unlock(ioc);
				bfa_nw_ioc_hw_sem_release(ioc);
				mod_समयr(&ioc->sem_समयr, jअगरfies +
					msecs_to_jअगरfies(BFA_IOC_HWSEM_TOV));
			पूर्ण
		पूर्ण अन्यथा अणु
			bfa_nw_ioc_hw_sem_release(ioc);
			bfa_fsm_set_state(iocpf, bfa_iocpf_sm_mismatch);
		पूर्ण
		अवरोध;

	हाल IOCPF_E_SEM_ERROR:
		bfa_fsm_set_state(iocpf, bfa_iocpf_sm_fail);
		bfa_ioc_pf_hwfailed(ioc);
		अवरोध;

	हाल IOCPF_E_DISABLE:
		bfa_ioc_hw_sem_get_cancel(ioc);
		bfa_fsm_set_state(iocpf, bfa_iocpf_sm_reset);
		bfa_ioc_pf_disabled(ioc);
		अवरोध;

	हाल IOCPF_E_STOP:
		bfa_ioc_hw_sem_get_cancel(ioc);
		bfa_fsm_set_state(iocpf, bfa_iocpf_sm_reset);
		अवरोध;

	शेष:
		bfa_sm_fault(event);
	पूर्ण
पूर्ण

/* Notअगरy enable completion callback */
अटल व्योम
bfa_iocpf_sm_mismatch_entry(काष्ठा bfa_iocpf *iocpf)
अणु
	/* Call only the first समय sm enters fwmismatch state. */
	अगर (!iocpf->fw_mismatch_notअगरied)
		bfa_ioc_pf_fwmismatch(iocpf->ioc);

	iocpf->fw_mismatch_notअगरied = true;
	mod_समयr(&(iocpf->ioc)->iocpf_समयr, jअगरfies +
		msecs_to_jअगरfies(BFA_IOC_TOV));
पूर्ण

/* Aरुकोing firmware version match. */
अटल व्योम
bfa_iocpf_sm_mismatch(काष्ठा bfa_iocpf *iocpf, क्रमागत iocpf_event event)
अणु
	काष्ठा bfa_ioc *ioc = iocpf->ioc;

	चयन (event) अणु
	हाल IOCPF_E_TIMEOUT:
		bfa_fsm_set_state(iocpf, bfa_iocpf_sm_fwcheck);
		अवरोध;

	हाल IOCPF_E_DISABLE:
		del_समयr(&ioc->iocpf_समयr);
		bfa_fsm_set_state(iocpf, bfa_iocpf_sm_reset);
		bfa_ioc_pf_disabled(ioc);
		अवरोध;

	हाल IOCPF_E_STOP:
		del_समयr(&ioc->iocpf_समयr);
		bfa_fsm_set_state(iocpf, bfa_iocpf_sm_reset);
		अवरोध;

	शेष:
		bfa_sm_fault(event);
	पूर्ण
पूर्ण

/* Request क्रम semaphore. */
अटल व्योम
bfa_iocpf_sm_semरुको_entry(काष्ठा bfa_iocpf *iocpf)
अणु
	bfa_ioc_hw_sem_get(iocpf->ioc);
पूर्ण

/* Aरुकोing semaphore क्रम h/w initialzation. */
अटल व्योम
bfa_iocpf_sm_semरुको(काष्ठा bfa_iocpf *iocpf, क्रमागत iocpf_event event)
अणु
	काष्ठा bfa_ioc *ioc = iocpf->ioc;

	चयन (event) अणु
	हाल IOCPF_E_SEMLOCKED:
		अगर (bfa_ioc_sync_complete(ioc)) अणु
			bfa_ioc_sync_join(ioc);
			bfa_fsm_set_state(iocpf, bfa_iocpf_sm_hwinit);
		पूर्ण अन्यथा अणु
			bfa_nw_ioc_hw_sem_release(ioc);
			mod_समयr(&ioc->sem_समयr, jअगरfies +
				msecs_to_jअगरfies(BFA_IOC_HWSEM_TOV));
		पूर्ण
		अवरोध;

	हाल IOCPF_E_SEM_ERROR:
		bfa_fsm_set_state(iocpf, bfa_iocpf_sm_fail);
		bfa_ioc_pf_hwfailed(ioc);
		अवरोध;

	हाल IOCPF_E_DISABLE:
		bfa_ioc_hw_sem_get_cancel(ioc);
		bfa_fsm_set_state(iocpf, bfa_iocpf_sm_disabling_sync);
		अवरोध;

	शेष:
		bfa_sm_fault(event);
	पूर्ण
पूर्ण

अटल व्योम
bfa_iocpf_sm_hwinit_entry(काष्ठा bfa_iocpf *iocpf)
अणु
	iocpf->poll_समय = 0;
	bfa_ioc_reset(iocpf->ioc, false);
पूर्ण

/* Hardware is being initialized. Interrupts are enabled.
 * Holding hardware semaphore lock.
 */
अटल व्योम
bfa_iocpf_sm_hwinit(काष्ठा bfa_iocpf *iocpf, क्रमागत iocpf_event event)
अणु
	काष्ठा bfa_ioc *ioc = iocpf->ioc;

	चयन (event) अणु
	हाल IOCPF_E_FWREADY:
		bfa_fsm_set_state(iocpf, bfa_iocpf_sm_enabling);
		अवरोध;

	हाल IOCPF_E_TIMEOUT:
		bfa_nw_ioc_hw_sem_release(ioc);
		bfa_ioc_pf_failed(ioc);
		bfa_fsm_set_state(iocpf, bfa_iocpf_sm_initfail_sync);
		अवरोध;

	हाल IOCPF_E_DISABLE:
		del_समयr(&ioc->iocpf_समयr);
		bfa_ioc_sync_leave(ioc);
		bfa_nw_ioc_hw_sem_release(ioc);
		bfa_fsm_set_state(iocpf, bfa_iocpf_sm_disabled);
		अवरोध;

	शेष:
		bfa_sm_fault(event);
	पूर्ण
पूर्ण

अटल व्योम
bfa_iocpf_sm_enabling_entry(काष्ठा bfa_iocpf *iocpf)
अणु
	mod_समयr(&(iocpf->ioc)->iocpf_समयr, jअगरfies +
		msecs_to_jअगरfies(BFA_IOC_TOV));
	/**
	 * Enable Interrupts beक्रमe sending fw IOC ENABLE cmd.
	 */
	iocpf->ioc->cbfn->reset_cbfn(iocpf->ioc->bfa);
	bfa_ioc_send_enable(iocpf->ioc);
पूर्ण

/* Host IOC function is being enabled, aरुकोing response from firmware.
 * Semaphore is acquired.
 */
अटल व्योम
bfa_iocpf_sm_enabling(काष्ठा bfa_iocpf *iocpf, क्रमागत iocpf_event event)
अणु
	काष्ठा bfa_ioc *ioc = iocpf->ioc;

	चयन (event) अणु
	हाल IOCPF_E_FWRSP_ENABLE:
		del_समयr(&ioc->iocpf_समयr);
		bfa_nw_ioc_hw_sem_release(ioc);
		bfa_fsm_set_state(iocpf, bfa_iocpf_sm_पढ़ोy);
		अवरोध;

	हाल IOCPF_E_INITFAIL:
		del_समयr(&ioc->iocpf_समयr);
		fallthrough;

	हाल IOCPF_E_TIMEOUT:
		bfa_nw_ioc_hw_sem_release(ioc);
		अगर (event == IOCPF_E_TIMEOUT)
			bfa_ioc_pf_failed(ioc);
		bfa_fsm_set_state(iocpf, bfa_iocpf_sm_initfail_sync);
		अवरोध;

	हाल IOCPF_E_DISABLE:
		del_समयr(&ioc->iocpf_समयr);
		bfa_nw_ioc_hw_sem_release(ioc);
		bfa_fsm_set_state(iocpf, bfa_iocpf_sm_disabling);
		अवरोध;

	शेष:
		bfa_sm_fault(event);
	पूर्ण
पूर्ण

अटल व्योम
bfa_iocpf_sm_पढ़ोy_entry(काष्ठा bfa_iocpf *iocpf)
अणु
	bfa_ioc_pf_enabled(iocpf->ioc);
पूर्ण

अटल व्योम
bfa_iocpf_sm_पढ़ोy(काष्ठा bfa_iocpf *iocpf, क्रमागत iocpf_event event)
अणु
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
		bfa_sm_fault(event);
	पूर्ण
पूर्ण

अटल व्योम
bfa_iocpf_sm_disabling_entry(काष्ठा bfa_iocpf *iocpf)
अणु
	mod_समयr(&(iocpf->ioc)->iocpf_समयr, jअगरfies +
		msecs_to_jअगरfies(BFA_IOC_TOV));
	bfa_ioc_send_disable(iocpf->ioc);
पूर्ण

/* IOC is being disabled */
अटल व्योम
bfa_iocpf_sm_disabling(काष्ठा bfa_iocpf *iocpf, क्रमागत iocpf_event event)
अणु
	काष्ठा bfa_ioc *ioc = iocpf->ioc;

	चयन (event) अणु
	हाल IOCPF_E_FWRSP_DISABLE:
		del_समयr(&ioc->iocpf_समयr);
		bfa_fsm_set_state(iocpf, bfa_iocpf_sm_disabling_sync);
		अवरोध;

	हाल IOCPF_E_FAIL:
		del_समयr(&ioc->iocpf_समयr);
		fallthrough;

	हाल IOCPF_E_TIMEOUT:
		bfa_ioc_set_cur_ioc_fwstate(ioc, BFI_IOC_FAIL);
		bfa_fsm_set_state(iocpf, bfa_iocpf_sm_disabling_sync);
		अवरोध;

	हाल IOCPF_E_FWRSP_ENABLE:
		अवरोध;

	शेष:
		bfa_sm_fault(event);
	पूर्ण
पूर्ण

अटल व्योम
bfa_iocpf_sm_disabling_sync_entry(काष्ठा bfa_iocpf *iocpf)
अणु
	bfa_ioc_hw_sem_get(iocpf->ioc);
पूर्ण

/* IOC hb ack request is being हटाओd. */
अटल व्योम
bfa_iocpf_sm_disabling_sync(काष्ठा bfa_iocpf *iocpf, क्रमागत iocpf_event event)
अणु
	काष्ठा bfa_ioc *ioc = iocpf->ioc;

	चयन (event) अणु
	हाल IOCPF_E_SEMLOCKED:
		bfa_ioc_sync_leave(ioc);
		bfa_nw_ioc_hw_sem_release(ioc);
		bfa_fsm_set_state(iocpf, bfa_iocpf_sm_disabled);
		अवरोध;

	हाल IOCPF_E_SEM_ERROR:
		bfa_fsm_set_state(iocpf, bfa_iocpf_sm_fail);
		bfa_ioc_pf_hwfailed(ioc);
		अवरोध;

	हाल IOCPF_E_FAIL:
		अवरोध;

	शेष:
		bfa_sm_fault(event);
	पूर्ण
पूर्ण

/* IOC disable completion entry. */
अटल व्योम
bfa_iocpf_sm_disabled_entry(काष्ठा bfa_iocpf *iocpf)
अणु
	bfa_ioc_mbox_flush(iocpf->ioc);
	bfa_ioc_pf_disabled(iocpf->ioc);
पूर्ण

अटल व्योम
bfa_iocpf_sm_disabled(काष्ठा bfa_iocpf *iocpf, क्रमागत iocpf_event event)
अणु
	काष्ठा bfa_ioc *ioc = iocpf->ioc;

	चयन (event) अणु
	हाल IOCPF_E_ENABLE:
		bfa_fsm_set_state(iocpf, bfa_iocpf_sm_semरुको);
		अवरोध;

	हाल IOCPF_E_STOP:
		bfa_ioc_firmware_unlock(ioc);
		bfa_fsm_set_state(iocpf, bfa_iocpf_sm_reset);
		अवरोध;

	शेष:
		bfa_sm_fault(event);
	पूर्ण
पूर्ण

अटल व्योम
bfa_iocpf_sm_initfail_sync_entry(काष्ठा bfa_iocpf *iocpf)
अणु
	bfa_nw_ioc_debug_save_ftrc(iocpf->ioc);
	bfa_ioc_hw_sem_get(iocpf->ioc);
पूर्ण

/* Hardware initialization failed. */
अटल व्योम
bfa_iocpf_sm_initfail_sync(काष्ठा bfa_iocpf *iocpf, क्रमागत iocpf_event event)
अणु
	काष्ठा bfa_ioc *ioc = iocpf->ioc;

	चयन (event) अणु
	हाल IOCPF_E_SEMLOCKED:
		bfa_ioc_notअगरy_fail(ioc);
		bfa_ioc_sync_leave(ioc);
		bfa_ioc_set_cur_ioc_fwstate(ioc, BFI_IOC_FAIL);
		bfa_nw_ioc_hw_sem_release(ioc);
		bfa_fsm_set_state(iocpf, bfa_iocpf_sm_initfail);
		अवरोध;

	हाल IOCPF_E_SEM_ERROR:
		bfa_fsm_set_state(iocpf, bfa_iocpf_sm_fail);
		bfa_ioc_pf_hwfailed(ioc);
		अवरोध;

	हाल IOCPF_E_DISABLE:
		bfa_ioc_hw_sem_get_cancel(ioc);
		bfa_fsm_set_state(iocpf, bfa_iocpf_sm_disabling_sync);
		अवरोध;

	हाल IOCPF_E_STOP:
		bfa_ioc_hw_sem_get_cancel(ioc);
		bfa_ioc_firmware_unlock(ioc);
		bfa_fsm_set_state(iocpf, bfa_iocpf_sm_reset);
		अवरोध;

	हाल IOCPF_E_FAIL:
		अवरोध;

	शेष:
		bfa_sm_fault(event);
	पूर्ण
पूर्ण

अटल व्योम
bfa_iocpf_sm_initfail_entry(काष्ठा bfa_iocpf *iocpf)
अणु
पूर्ण

/* Hardware initialization failed. */
अटल व्योम
bfa_iocpf_sm_initfail(काष्ठा bfa_iocpf *iocpf, क्रमागत iocpf_event event)
अणु
	काष्ठा bfa_ioc *ioc = iocpf->ioc;

	चयन (event) अणु
	हाल IOCPF_E_DISABLE:
		bfa_fsm_set_state(iocpf, bfa_iocpf_sm_disabled);
		अवरोध;

	हाल IOCPF_E_STOP:
		bfa_ioc_firmware_unlock(ioc);
		bfa_fsm_set_state(iocpf, bfa_iocpf_sm_reset);
		अवरोध;

	शेष:
		bfa_sm_fault(event);
	पूर्ण
पूर्ण

अटल व्योम
bfa_iocpf_sm_fail_sync_entry(काष्ठा bfa_iocpf *iocpf)
अणु
	/**
	 * Mark IOC as failed in hardware and stop firmware.
	 */
	bfa_ioc_lpu_stop(iocpf->ioc);

	/**
	 * Flush any queued up mailbox requests.
	 */
	bfa_ioc_mbox_flush(iocpf->ioc);
	bfa_ioc_hw_sem_get(iocpf->ioc);
पूर्ण

/* IOC is in failed state. */
अटल व्योम
bfa_iocpf_sm_fail_sync(काष्ठा bfa_iocpf *iocpf, क्रमागत iocpf_event event)
अणु
	काष्ठा bfa_ioc *ioc = iocpf->ioc;

	चयन (event) अणु
	हाल IOCPF_E_SEMLOCKED:
		bfa_ioc_sync_ack(ioc);
		bfa_ioc_notअगरy_fail(ioc);
		अगर (!iocpf->स्वतः_recover) अणु
			bfa_ioc_sync_leave(ioc);
			bfa_ioc_set_cur_ioc_fwstate(ioc, BFI_IOC_FAIL);
			bfa_nw_ioc_hw_sem_release(ioc);
			bfa_fsm_set_state(iocpf, bfa_iocpf_sm_fail);
		पूर्ण अन्यथा अणु
			अगर (bfa_ioc_sync_complete(ioc))
				bfa_fsm_set_state(iocpf, bfa_iocpf_sm_hwinit);
			अन्यथा अणु
				bfa_nw_ioc_hw_sem_release(ioc);
				bfa_fsm_set_state(iocpf, bfa_iocpf_sm_semरुको);
			पूर्ण
		पूर्ण
		अवरोध;

	हाल IOCPF_E_SEM_ERROR:
		bfa_fsm_set_state(iocpf, bfa_iocpf_sm_fail);
		bfa_ioc_pf_hwfailed(ioc);
		अवरोध;

	हाल IOCPF_E_DISABLE:
		bfa_ioc_hw_sem_get_cancel(ioc);
		bfa_fsm_set_state(iocpf, bfa_iocpf_sm_disabling_sync);
		अवरोध;

	हाल IOCPF_E_FAIL:
		अवरोध;

	शेष:
		bfa_sm_fault(event);
	पूर्ण
पूर्ण

अटल व्योम
bfa_iocpf_sm_fail_entry(काष्ठा bfa_iocpf *iocpf)
अणु
पूर्ण

/* IOC is in failed state. */
अटल व्योम
bfa_iocpf_sm_fail(काष्ठा bfa_iocpf *iocpf, क्रमागत iocpf_event event)
अणु
	चयन (event) अणु
	हाल IOCPF_E_DISABLE:
		bfa_fsm_set_state(iocpf, bfa_iocpf_sm_disabled);
		अवरोध;

	शेष:
		bfa_sm_fault(event);
	पूर्ण
पूर्ण

/* BFA IOC निजी functions */

/* Notअगरy common modules रेजिस्टरed क्रम notअगरication. */
अटल व्योम
bfa_ioc_event_notअगरy(काष्ठा bfa_ioc *ioc, क्रमागत bfa_ioc_event event)
अणु
	काष्ठा bfa_ioc_notअगरy *notअगरy;

	list_क्रम_each_entry(notअगरy, &ioc->notअगरy_q, qe)
		notअगरy->cbfn(notअगरy->cbarg, event);
पूर्ण

अटल व्योम
bfa_ioc_disable_comp(काष्ठा bfa_ioc *ioc)
अणु
	ioc->cbfn->disable_cbfn(ioc->bfa);
	bfa_ioc_event_notअगरy(ioc, BFA_IOC_E_DISABLED);
पूर्ण

bool
bfa_nw_ioc_sem_get(व्योम __iomem *sem_reg)
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
		वापस true;

	वापस false;
पूर्ण

व्योम
bfa_nw_ioc_sem_release(व्योम __iomem *sem_reg)
अणु
	पढ़ोl(sem_reg);
	ग_लिखोl(1, sem_reg);
पूर्ण

/* Clear fwver hdr */
अटल व्योम
bfa_ioc_fwver_clear(काष्ठा bfa_ioc *ioc)
अणु
	u32 pgnum, loff = 0;
	पूर्णांक i;

	pgnum = PSS_SMEM_PGNUM(ioc->ioc_regs.smem_pg0, loff);
	ग_लिखोl(pgnum, ioc->ioc_regs.host_page_num_fn);

	क्रम (i = 0; i < (माप(काष्ठा bfi_ioc_image_hdr) / माप(u32)); i++) अणु
		ग_लिखोl(0, ioc->ioc_regs.smem_page_start + loff);
		loff += माप(u32);
	पूर्ण
पूर्ण


अटल व्योम
bfa_ioc_hw_sem_init(काष्ठा bfa_ioc *ioc)
अणु
	काष्ठा bfi_ioc_image_hdr fwhdr;
	u32 fwstate, r32;

	/* Spin on init semaphore to serialize. */
	r32 = पढ़ोl(ioc->ioc_regs.ioc_init_sem_reg);
	जबतक (r32 & 0x1) अणु
		udelay(20);
		r32 = पढ़ोl(ioc->ioc_regs.ioc_init_sem_reg);
	पूर्ण

	fwstate = bfa_ioc_get_cur_ioc_fwstate(ioc);
	अगर (fwstate == BFI_IOC_UNINIT) अणु
		ग_लिखोl(1, ioc->ioc_regs.ioc_init_sem_reg);
		वापस;
	पूर्ण

	bfa_nw_ioc_fwver_get(ioc, &fwhdr);

	अगर (swab32(fwhdr.exec) == BFI_FWBOOT_TYPE_NORMAL) अणु
		ग_लिखोl(1, ioc->ioc_regs.ioc_init_sem_reg);
		वापस;
	पूर्ण

	bfa_ioc_fwver_clear(ioc);
	bfa_ioc_set_cur_ioc_fwstate(ioc, BFI_IOC_UNINIT);
	bfa_ioc_set_alt_ioc_fwstate(ioc, BFI_IOC_UNINIT);

	/*
	 * Try to lock and then unlock the semaphore.
	 */
	पढ़ोl(ioc->ioc_regs.ioc_sem_reg);
	ग_लिखोl(1, ioc->ioc_regs.ioc_sem_reg);

	/* Unlock init semaphore */
	ग_लिखोl(1, ioc->ioc_regs.ioc_init_sem_reg);
पूर्ण

अटल व्योम
bfa_ioc_hw_sem_get(काष्ठा bfa_ioc *ioc)
अणु
	u32	r32;

	/**
	 * First पढ़ो to the semaphore रेजिस्टर will वापस 0, subsequent पढ़ोs
	 * will वापस 1. Semaphore is released by writing 1 to the रेजिस्टर
	 */
	r32 = पढ़ोl(ioc->ioc_regs.ioc_sem_reg);
	अगर (r32 == ~0) अणु
		bfa_fsm_send_event(&ioc->iocpf, IOCPF_E_SEM_ERROR);
		वापस;
	पूर्ण
	अगर (!(r32 & 1)) अणु
		bfa_fsm_send_event(&ioc->iocpf, IOCPF_E_SEMLOCKED);
		वापस;
	पूर्ण

	mod_समयr(&ioc->sem_समयr, jअगरfies +
		msecs_to_jअगरfies(BFA_IOC_HWSEM_TOV));
पूर्ण

व्योम
bfa_nw_ioc_hw_sem_release(काष्ठा bfa_ioc *ioc)
अणु
	ग_लिखोl(1, ioc->ioc_regs.ioc_sem_reg);
पूर्ण

अटल व्योम
bfa_ioc_hw_sem_get_cancel(काष्ठा bfa_ioc *ioc)
अणु
	del_समयr(&ioc->sem_समयr);
पूर्ण

/* Initialize LPU local memory (aka secondary memory / SRAM) */
अटल व्योम
bfa_ioc_lmem_init(काष्ठा bfa_ioc *ioc)
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

	/**
	 * रुको क्रम memory initialization to be complete
	 */
	i = 0;
	करो अणु
		pss_ctl = पढ़ोl(ioc->ioc_regs.pss_ctl_reg);
		i++;
	पूर्ण जबतक (!(pss_ctl & __PSS_LMEM_INIT_DONE) && (i < PSS_LMEM_INIT_TIME));

	/**
	 * If memory initialization is not successful, IOC समयout will catch
	 * such failures.
	 */
	BUG_ON(!(pss_ctl & __PSS_LMEM_INIT_DONE));

	pss_ctl &= ~(__PSS_LMEM_INIT_DONE | __PSS_LMEM_INIT_EN);
	ग_लिखोl(pss_ctl, ioc->ioc_regs.pss_ctl_reg);
पूर्ण

अटल व्योम
bfa_ioc_lpu_start(काष्ठा bfa_ioc *ioc)
अणु
	u32	pss_ctl;

	/**
	 * Take processor out of reset.
	 */
	pss_ctl = पढ़ोl(ioc->ioc_regs.pss_ctl_reg);
	pss_ctl &= ~__PSS_LPU0_RESET;

	ग_लिखोl(pss_ctl, ioc->ioc_regs.pss_ctl_reg);
पूर्ण

अटल व्योम
bfa_ioc_lpu_stop(काष्ठा bfa_ioc *ioc)
अणु
	u32	pss_ctl;

	/**
	 * Put processors in reset.
	 */
	pss_ctl = पढ़ोl(ioc->ioc_regs.pss_ctl_reg);
	pss_ctl |= (__PSS_LPU0_RESET | __PSS_LPU1_RESET);

	ग_लिखोl(pss_ctl, ioc->ioc_regs.pss_ctl_reg);
पूर्ण

/* Get driver and firmware versions. */
व्योम
bfa_nw_ioc_fwver_get(काष्ठा bfa_ioc *ioc, काष्ठा bfi_ioc_image_hdr *fwhdr)
अणु
	u32	pgnum;
	u32	loff = 0;
	पूर्णांक		i;
	u32	*fwsig = (u32 *) fwhdr;

	pgnum = bfa_ioc_smem_pgnum(ioc, loff);
	ग_लिखोl(pgnum, ioc->ioc_regs.host_page_num_fn);

	क्रम (i = 0; i < (माप(काष्ठा bfi_ioc_image_hdr) / माप(u32));
	     i++) अणु
		fwsig[i] =
			swab32(पढ़ोl(loff + ioc->ioc_regs.smem_page_start));
		loff += माप(u32);
	पूर्ण
पूर्ण

अटल bool
bfa_ioc_fwver_md5_check(काष्ठा bfi_ioc_image_hdr *fwhdr_1,
			काष्ठा bfi_ioc_image_hdr *fwhdr_2)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < BFI_IOC_MD5SUM_SZ; i++) अणु
		अगर (fwhdr_1->md5sum[i] != fwhdr_2->md5sum[i])
			वापस false;
	पूर्ण

	वापस true;
पूर्ण

/* Returns TRUE अगर major minor and मुख्यtenance are same.
 * If patch version are same, check क्रम MD5 Checksum to be same.
 */
अटल bool
bfa_ioc_fw_ver_compatible(काष्ठा bfi_ioc_image_hdr *drv_fwhdr,
			  काष्ठा bfi_ioc_image_hdr *fwhdr_to_cmp)
अणु
	अगर (drv_fwhdr->signature != fwhdr_to_cmp->signature)
		वापस false;
	अगर (drv_fwhdr->fwver.major != fwhdr_to_cmp->fwver.major)
		वापस false;
	अगर (drv_fwhdr->fwver.minor != fwhdr_to_cmp->fwver.minor)
		वापस false;
	अगर (drv_fwhdr->fwver.मुख्यt != fwhdr_to_cmp->fwver.मुख्यt)
		वापस false;
	अगर (drv_fwhdr->fwver.patch == fwhdr_to_cmp->fwver.patch &&
	    drv_fwhdr->fwver.phase == fwhdr_to_cmp->fwver.phase &&
	    drv_fwhdr->fwver.build == fwhdr_to_cmp->fwver.build)
		वापस bfa_ioc_fwver_md5_check(drv_fwhdr, fwhdr_to_cmp);

	वापस true;
पूर्ण

अटल bool
bfa_ioc_flash_fwver_valid(काष्ठा bfi_ioc_image_hdr *flash_fwhdr)
अणु
	अगर (flash_fwhdr->fwver.major == 0 || flash_fwhdr->fwver.major == 0xFF)
		वापस false;

	वापस true;
पूर्ण

अटल bool
fwhdr_is_ga(काष्ठा bfi_ioc_image_hdr *fwhdr)
अणु
	अगर (fwhdr->fwver.phase == 0 &&
	    fwhdr->fwver.build == 0)
		वापस false;

	वापस true;
पूर्ण

/* Returns TRUE अगर both are compatible and patch of fwhdr_to_cmp is better. */
अटल क्रमागत bfi_ioc_img_ver_cmp
bfa_ioc_fw_ver_patch_cmp(काष्ठा bfi_ioc_image_hdr *base_fwhdr,
			 काष्ठा bfi_ioc_image_hdr *fwhdr_to_cmp)
अणु
	अगर (!bfa_ioc_fw_ver_compatible(base_fwhdr, fwhdr_to_cmp))
		वापस BFI_IOC_IMG_VER_INCOMP;

	अगर (fwhdr_to_cmp->fwver.patch > base_fwhdr->fwver.patch)
		वापस BFI_IOC_IMG_VER_BETTER;
	अन्यथा अगर (fwhdr_to_cmp->fwver.patch < base_fwhdr->fwver.patch)
		वापस BFI_IOC_IMG_VER_OLD;

	/* GA takes priority over पूर्णांकernal builds of the same patch stream.
	 * At this poपूर्णांक major minor मुख्यt and patch numbers are same.
	 */
	अगर (fwhdr_is_ga(base_fwhdr))
		अगर (fwhdr_is_ga(fwhdr_to_cmp))
			वापस BFI_IOC_IMG_VER_SAME;
		अन्यथा
			वापस BFI_IOC_IMG_VER_OLD;
	अन्यथा
		अगर (fwhdr_is_ga(fwhdr_to_cmp))
			वापस BFI_IOC_IMG_VER_BETTER;

	अगर (fwhdr_to_cmp->fwver.phase > base_fwhdr->fwver.phase)
		वापस BFI_IOC_IMG_VER_BETTER;
	अन्यथा अगर (fwhdr_to_cmp->fwver.phase < base_fwhdr->fwver.phase)
		वापस BFI_IOC_IMG_VER_OLD;

	अगर (fwhdr_to_cmp->fwver.build > base_fwhdr->fwver.build)
		वापस BFI_IOC_IMG_VER_BETTER;
	अन्यथा अगर (fwhdr_to_cmp->fwver.build < base_fwhdr->fwver.build)
		वापस BFI_IOC_IMG_VER_OLD;

	/* All Version Numbers are equal.
	 * Md5 check to be करोne as a part of compatibility check.
	 */
	वापस BFI_IOC_IMG_VER_SAME;
पूर्ण

/* रेजिस्टर definitions */
#घोषणा FLI_CMD_REG			0x0001d000
#घोषणा FLI_WRDATA_REG			0x0001d00c
#घोषणा FLI_RDDATA_REG			0x0001d010
#घोषणा FLI_ADDR_REG			0x0001d004
#घोषणा FLI_DEV_STATUS_REG		0x0001d014

#घोषणा BFA_FLASH_FIFO_SIZE		128	/* fअगरo size */
#घोषणा BFA_FLASH_CHECK_MAX		10000	/* max # of status check */
#घोषणा BFA_FLASH_BLOCKING_OP_MAX	1000000	/* max # of blocking op check */
#घोषणा BFA_FLASH_WIP_MASK		0x01	/* ग_लिखो in progress bit mask */

#घोषणा NFC_STATE_RUNNING		0x20000001
#घोषणा NFC_STATE_PAUSED		0x00004560
#घोषणा NFC_VER_VALID			0x147

क्रमागत bfa_flash_cmd अणु
	BFA_FLASH_FAST_READ	= 0x0b,	/* fast पढ़ो */
	BFA_FLASH_WRITE_ENABLE	= 0x06,	/* ग_लिखो enable */
	BFA_FLASH_SECTOR_ERASE	= 0xd8,	/* sector erase */
	BFA_FLASH_WRITE		= 0x02,	/* ग_लिखो */
	BFA_FLASH_READ_STATUS	= 0x05,	/* पढ़ो status */
पूर्ण;

/* hardware error definition */
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

/* flash command रेजिस्टर data काष्ठाure */
जोड़ bfa_flash_cmd_reg अणु
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

/* flash device status रेजिस्टर data काष्ठाure */
जोड़ bfa_flash_dev_status_reg अणु
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

/* flash address रेजिस्टर data काष्ठाure */
जोड़ bfa_flash_addr_reg अणु
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

/* Flash raw निजी functions */
अटल व्योम
bfa_flash_set_cmd(व्योम __iomem *pci_bar, u8 wr_cnt,
		  u8 rd_cnt, u8 ad_cnt, u8 op)
अणु
	जोड़ bfa_flash_cmd_reg cmd;

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
	जोड़ bfa_flash_addr_reg addr;

	addr.r.addr = address & 0x00ffffff;
	addr.r.dummy = 0;
	ग_लिखोl(addr.i, (pci_bar + FLI_ADDR_REG));
पूर्ण

अटल पूर्णांक
bfa_flash_cmd_act_check(व्योम __iomem *pci_bar)
अणु
	जोड़ bfa_flash_cmd_reg cmd;

	cmd.i = पढ़ोl(pci_bar + FLI_CMD_REG);

	अगर (cmd.r.act)
		वापस BFA_FLASH_ERR_CMD_ACT;

	वापस 0;
पूर्ण

/* Flush FLI data fअगरo. */
अटल पूर्णांक
bfa_flash_fअगरo_flush(व्योम __iomem *pci_bar)
अणु
	u32 i;
	जोड़ bfa_flash_dev_status_reg dev_status;

	dev_status.i = पढ़ोl(pci_bar + FLI_DEV_STATUS_REG);

	अगर (!dev_status.r.fअगरo_cnt)
		वापस 0;

	/* fअगरo counter in terms of words */
	क्रम (i = 0; i < dev_status.r.fअगरo_cnt; i++)
		पढ़ोl(pci_bar + FLI_RDDATA_REG);

	/* Check the device status. It may take some समय. */
	क्रम (i = 0; i < BFA_FLASH_CHECK_MAX; i++) अणु
		dev_status.i = पढ़ोl(pci_bar + FLI_DEV_STATUS_REG);
		अगर (!dev_status.r.fअगरo_cnt)
			अवरोध;
	पूर्ण

	अगर (dev_status.r.fअगरo_cnt)
		वापस BFA_FLASH_ERR_FIFO_CNT;

	वापस 0;
पूर्ण

/* Read flash status. */
अटल पूर्णांक
bfa_flash_status_पढ़ो(व्योम __iomem *pci_bar)
अणु
	जोड़ bfa_flash_dev_status_reg	dev_status;
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

/* Start flash पढ़ो operation. */
अटल पूर्णांक
bfa_flash_पढ़ो_start(व्योम __iomem *pci_bar, u32 offset, u32 len,
		     अक्षर *buf)
अणु
	पूर्णांक status;

	/* len must be mutiple of 4 and not exceeding fअगरo size */
	अगर (len == 0 || len > BFA_FLASH_FIFO_SIZE || (len & 0x03) != 0)
		वापस BFA_FLASH_ERR_LEN;

	/* check status */
	status = bfa_flash_status_पढ़ो(pci_bar);
	अगर (status == BFA_FLASH_BUSY)
		status = bfa_flash_status_पढ़ो(pci_bar);

	अगर (status < 0)
		वापस status;

	/* check अगर ग_लिखो-in-progress bit is cleared */
	अगर (status & BFA_FLASH_WIP_MASK)
		वापस BFA_FLASH_ERR_WIP;

	bfa_flash_set_addr(pci_bar, offset);

	bfa_flash_set_cmd(pci_bar, 0, (u8)len, 4, BFA_FLASH_FAST_READ);

	वापस 0;
पूर्ण

/* Check flash पढ़ो operation. */
अटल u32
bfa_flash_पढ़ो_check(व्योम __iomem *pci_bar)
अणु
	अगर (bfa_flash_cmd_act_check(pci_bar))
		वापस 1;

	वापस 0;
पूर्ण

/* End flash पढ़ो operation. */
अटल व्योम
bfa_flash_पढ़ो_end(व्योम __iomem *pci_bar, u32 len, अक्षर *buf)
अणु
	u32 i;

	/* पढ़ो data fअगरo up to 32 words */
	क्रम (i = 0; i < len; i += 4) अणु
		u32 w = पढ़ोl(pci_bar + FLI_RDDATA_REG);
		*((u32 *)(buf + i)) = swab32(w);
	पूर्ण

	bfa_flash_fअगरo_flush(pci_bar);
पूर्ण

/* Perक्रमm flash raw पढ़ो. */

#घोषणा FLASH_BLOCKING_OP_MAX   500
#घोषणा FLASH_SEM_LOCK_REG	0x18820

अटल पूर्णांक
bfa_raw_sem_get(व्योम __iomem *bar)
अणु
	पूर्णांक	locked;

	locked = पढ़ोl(bar + FLASH_SEM_LOCK_REG);

	वापस !locked;
पूर्ण

अटल क्रमागत bfa_status
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

अटल क्रमागत bfa_status
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

#घोषणा BFA_FLASH_PART_FWIMG_ADDR	0x100000 /* fw image address */

अटल क्रमागत bfa_status
bfa_nw_ioc_flash_img_get_chnk(काष्ठा bfa_ioc *ioc, u32 off,
			      u32 *fwimg)
अणु
	वापस bfa_flash_raw_पढ़ो(ioc->pcidev.pci_bar_kva,
			BFA_FLASH_PART_FWIMG_ADDR + (off * माप(u32)),
			(अक्षर *)fwimg, BFI_FLASH_CHUNK_SZ);
पूर्ण

अटल क्रमागत bfi_ioc_img_ver_cmp
bfa_ioc_flash_fwver_cmp(काष्ठा bfa_ioc *ioc,
			काष्ठा bfi_ioc_image_hdr *base_fwhdr)
अणु
	काष्ठा bfi_ioc_image_hdr *flash_fwhdr;
	क्रमागत bfa_status status;
	u32 fwimg[BFI_FLASH_CHUNK_SZ_WORDS];

	status = bfa_nw_ioc_flash_img_get_chnk(ioc, 0, fwimg);
	अगर (status != BFA_STATUS_OK)
		वापस BFI_IOC_IMG_VER_INCOMP;

	flash_fwhdr = (काष्ठा bfi_ioc_image_hdr *)fwimg;
	अगर (bfa_ioc_flash_fwver_valid(flash_fwhdr))
		वापस bfa_ioc_fw_ver_patch_cmp(base_fwhdr, flash_fwhdr);
	अन्यथा
		वापस BFI_IOC_IMG_VER_INCOMP;
पूर्ण

/*
 * Returns TRUE अगर driver is willing to work with current smem f/w version.
 */
bool
bfa_nw_ioc_fwver_cmp(काष्ठा bfa_ioc *ioc, काष्ठा bfi_ioc_image_hdr *fwhdr)
अणु
	काष्ठा bfi_ioc_image_hdr *drv_fwhdr;
	क्रमागत bfi_ioc_img_ver_cmp smem_flash_cmp, drv_smem_cmp;

	drv_fwhdr = (काष्ठा bfi_ioc_image_hdr *)
		bfa_cb_image_get_chunk(bfa_ioc_asic_gen(ioc), 0);

	/* If smem is incompatible or old, driver should not work with it. */
	drv_smem_cmp = bfa_ioc_fw_ver_patch_cmp(drv_fwhdr, fwhdr);
	अगर (drv_smem_cmp == BFI_IOC_IMG_VER_INCOMP ||
	    drv_smem_cmp == BFI_IOC_IMG_VER_OLD) अणु
		वापस false;
	पूर्ण

	/* IF Flash has a better F/W than smem करो not work with smem.
	 * If smem f/w == flash f/w, as smem f/w not old | incmp, work with it.
	 * If Flash is old or incomp work with smem अगरf smem f/w == drv f/w.
	 */
	smem_flash_cmp = bfa_ioc_flash_fwver_cmp(ioc, fwhdr);

	अगर (smem_flash_cmp == BFI_IOC_IMG_VER_BETTER)
		वापस false;
	अन्यथा अगर (smem_flash_cmp == BFI_IOC_IMG_VER_SAME)
		वापस true;
	अन्यथा
		वापस (drv_smem_cmp == BFI_IOC_IMG_VER_SAME) ?
			true : false;
पूर्ण

/* Return true अगर current running version is valid. Firmware signature and
 * execution context (driver/bios) must match.
 */
अटल bool
bfa_ioc_fwver_valid(काष्ठा bfa_ioc *ioc, u32 boot_env)
अणु
	काष्ठा bfi_ioc_image_hdr fwhdr;

	bfa_nw_ioc_fwver_get(ioc, &fwhdr);
	अगर (swab32(fwhdr.bootenv) != boot_env)
		वापस false;

	वापस bfa_nw_ioc_fwver_cmp(ioc, &fwhdr);
पूर्ण

/* Conditionally flush any pending message from firmware at start. */
अटल व्योम
bfa_ioc_msgflush(काष्ठा bfa_ioc *ioc)
अणु
	u32	r32;

	r32 = पढ़ोl(ioc->ioc_regs.lpu_mbox_cmd);
	अगर (r32)
		ग_लिखोl(1, ioc->ioc_regs.lpu_mbox_cmd);
पूर्ण

अटल व्योम
bfa_ioc_hwinit(काष्ठा bfa_ioc *ioc, bool क्रमce)
अणु
	क्रमागत bfi_ioc_state ioc_fwstate;
	bool fwvalid;
	u32 boot_env;

	ioc_fwstate = bfa_ioc_get_cur_ioc_fwstate(ioc);

	अगर (क्रमce)
		ioc_fwstate = BFI_IOC_UNINIT;

	boot_env = BFI_FWBOOT_ENV_OS;

	/**
	 * check अगर firmware is valid
	 */
	fwvalid = (ioc_fwstate == BFI_IOC_UNINIT) ?
		false : bfa_ioc_fwver_valid(ioc, boot_env);

	अगर (!fwvalid) अणु
		अगर (bfa_ioc_boot(ioc, BFI_FWBOOT_TYPE_NORMAL, boot_env) ==
								BFA_STATUS_OK)
			bfa_ioc_poll_fwinit(ioc);

		वापस;
	पूर्ण

	/**
	 * If hardware initialization is in progress (initialized by other IOC),
	 * just रुको क्रम an initialization completion पूर्णांकerrupt.
	 */
	अगर (ioc_fwstate == BFI_IOC_INITING) अणु
		bfa_ioc_poll_fwinit(ioc);
		वापस;
	पूर्ण

	/**
	 * If IOC function is disabled and firmware version is same,
	 * just re-enable IOC.
	 */
	अगर (ioc_fwstate == BFI_IOC_DISABLED || ioc_fwstate == BFI_IOC_OP) अणु
		/**
		 * When using MSI-X any pending firmware पढ़ोy event should
		 * be flushed. Otherwise MSI-X पूर्णांकerrupts are not delivered.
		 */
		bfa_ioc_msgflush(ioc);
		bfa_fsm_send_event(&ioc->iocpf, IOCPF_E_FWREADY);
		वापस;
	पूर्ण

	/**
	 * Initialize the h/w क्रम any other states.
	 */
	अगर (bfa_ioc_boot(ioc, BFI_FWBOOT_TYPE_NORMAL, boot_env) ==
							BFA_STATUS_OK)
		bfa_ioc_poll_fwinit(ioc);
पूर्ण

व्योम
bfa_nw_ioc_समयout(काष्ठा bfa_ioc *ioc)
अणु
	bfa_fsm_send_event(ioc, IOC_E_TIMEOUT);
पूर्ण

अटल व्योम
bfa_ioc_mbox_send(काष्ठा bfa_ioc *ioc, व्योम *ioc_msg, पूर्णांक len)
अणु
	u32 *msgp = (u32 *) ioc_msg;
	u32 i;

	BUG_ON(!(len <= BFI_IOC_MSGLEN_MAX));

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
bfa_ioc_send_enable(काष्ठा bfa_ioc *ioc)
अणु
	काष्ठा bfi_ioc_ctrl_req enable_req;

	bfi_h2i_set(enable_req.mh, BFI_MC_IOC, BFI_IOC_H2I_ENABLE_REQ,
		    bfa_ioc_portid(ioc));
	enable_req.clscode = htons(ioc->clscode);
	enable_req.rsvd = htons(0);
	/* overflow in 2106 */
	enable_req.tv_sec = ntohl(kसमय_get_real_seconds());
	bfa_ioc_mbox_send(ioc, &enable_req, माप(काष्ठा bfi_ioc_ctrl_req));
पूर्ण

अटल व्योम
bfa_ioc_send_disable(काष्ठा bfa_ioc *ioc)
अणु
	काष्ठा bfi_ioc_ctrl_req disable_req;

	bfi_h2i_set(disable_req.mh, BFI_MC_IOC, BFI_IOC_H2I_DISABLE_REQ,
		    bfa_ioc_portid(ioc));
	disable_req.clscode = htons(ioc->clscode);
	disable_req.rsvd = htons(0);
	/* overflow in 2106 */
	disable_req.tv_sec = ntohl(kसमय_get_real_seconds());
	bfa_ioc_mbox_send(ioc, &disable_req, माप(काष्ठा bfi_ioc_ctrl_req));
पूर्ण

अटल व्योम
bfa_ioc_send_getattr(काष्ठा bfa_ioc *ioc)
अणु
	काष्ठा bfi_ioc_getattr_req attr_req;

	bfi_h2i_set(attr_req.mh, BFI_MC_IOC, BFI_IOC_H2I_GETATTR_REQ,
		    bfa_ioc_portid(ioc));
	bfa_dma_be_addr_set(attr_req.attr_addr, ioc->attr_dma.pa);
	bfa_ioc_mbox_send(ioc, &attr_req, माप(attr_req));
पूर्ण

व्योम
bfa_nw_ioc_hb_check(काष्ठा bfa_ioc *ioc)
अणु
	u32 hb_count;

	hb_count = पढ़ोl(ioc->ioc_regs.heartbeat);
	अगर (ioc->hb_count == hb_count) अणु
		bfa_ioc_recover(ioc);
		वापस;
	पूर्ण अन्यथा अणु
		ioc->hb_count = hb_count;
	पूर्ण

	bfa_ioc_mbox_poll(ioc);
	mod_समयr(&ioc->hb_समयr, jअगरfies +
		msecs_to_jअगरfies(BFA_IOC_HB_TOV));
पूर्ण

अटल व्योम
bfa_ioc_hb_monitor(काष्ठा bfa_ioc *ioc)
अणु
	ioc->hb_count = पढ़ोl(ioc->ioc_regs.heartbeat);
	mod_समयr(&ioc->hb_समयr, jअगरfies +
		msecs_to_jअगरfies(BFA_IOC_HB_TOV));
पूर्ण

अटल व्योम
bfa_ioc_hb_stop(काष्ठा bfa_ioc *ioc)
अणु
	del_समयr(&ioc->hb_समयr);
पूर्ण

/* Initiate a full firmware करोwnload. */
अटल क्रमागत bfa_status
bfa_ioc_करोwnload_fw(काष्ठा bfa_ioc *ioc, u32 boot_type,
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
	क्रमागत bfa_status status;

	अगर (boot_env == BFI_FWBOOT_ENV_OS &&
	    boot_type == BFI_FWBOOT_TYPE_FLASH) अणु
		fwimg_size = BFI_FLASH_IMAGE_SZ/माप(u32);

		status = bfa_nw_ioc_flash_img_get_chnk(ioc,
			BFA_IOC_FLASH_CHUNK_ADDR(chunkno), fwimg_buf);
		अगर (status != BFA_STATUS_OK)
			वापस status;

		fwimg = fwimg_buf;
	पूर्ण अन्यथा अणु
		fwimg_size = bfa_cb_image_get_size(bfa_ioc_asic_gen(ioc));
		fwimg = bfa_cb_image_get_chunk(bfa_ioc_asic_gen(ioc),
					BFA_IOC_FLASH_CHUNK_ADDR(chunkno));
	पूर्ण

	pgnum = bfa_ioc_smem_pgnum(ioc, loff);

	ग_लिखोl(pgnum, ioc->ioc_regs.host_page_num_fn);

	क्रम (i = 0; i < fwimg_size; i++) अणु
		अगर (BFA_IOC_FLASH_CHUNK_NO(i) != chunkno) अणु
			chunkno = BFA_IOC_FLASH_CHUNK_NO(i);
			अगर (boot_env == BFI_FWBOOT_ENV_OS &&
			    boot_type == BFI_FWBOOT_TYPE_FLASH) अणु
				status = bfa_nw_ioc_flash_img_get_chnk(ioc,
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

		/**
		 * ग_लिखो smem
		 */
		ग_लिखोl(swab32(fwimg[BFA_IOC_FLASH_OFFSET_IN_CHUNK(i)]),
		       ioc->ioc_regs.smem_page_start + loff);

		loff += माप(u32);

		/**
		 * handle page offset wrap around
		 */
		loff = PSS_SMEM_PGOFF(loff);
		अगर (loff == 0) अणु
			pgnum++;
			ग_लिखोl(pgnum,
				      ioc->ioc_regs.host_page_num_fn);
		पूर्ण
	पूर्ण

	ग_लिखोl(bfa_ioc_smem_pgnum(ioc, 0),
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
	ग_लिखोl(asicmode, ((ioc->ioc_regs.smem_page_start)
			+ BFI_FWBOOT_DEVMODE_OFF));
	ग_लिखोl(boot_type, ((ioc->ioc_regs.smem_page_start)
			+ (BFI_FWBOOT_TYPE_OFF)));
	ग_लिखोl(boot_env, ((ioc->ioc_regs.smem_page_start)
			+ (BFI_FWBOOT_ENV_OFF)));
	वापस BFA_STATUS_OK;
पूर्ण

अटल व्योम
bfa_ioc_reset(काष्ठा bfa_ioc *ioc, bool क्रमce)
अणु
	bfa_ioc_hwinit(ioc, क्रमce);
पूर्ण

/* BFA ioc enable reply by firmware */
अटल व्योम
bfa_ioc_enable_reply(काष्ठा bfa_ioc *ioc, क्रमागत bfa_mode port_mode,
			u8 cap_bm)
अणु
	काष्ठा bfa_iocpf *iocpf = &ioc->iocpf;

	ioc->port_mode = ioc->port_mode_cfg = port_mode;
	ioc->ad_cap_bm = cap_bm;
	bfa_fsm_send_event(iocpf, IOCPF_E_FWRSP_ENABLE);
पूर्ण

/* Update BFA configuration from firmware configuration. */
अटल व्योम
bfa_ioc_getattr_reply(काष्ठा bfa_ioc *ioc)
अणु
	काष्ठा bfi_ioc_attr *attr = ioc->attr;

	attr->adapter_prop  = ntohl(attr->adapter_prop);
	attr->card_type     = ntohl(attr->card_type);
	attr->maxfrsize	    = ntohs(attr->maxfrsize);

	bfa_fsm_send_event(ioc, IOC_E_FWRSP_GETATTR);
पूर्ण

/* Attach समय initialization of mbox logic. */
अटल व्योम
bfa_ioc_mbox_attach(काष्ठा bfa_ioc *ioc)
अणु
	काष्ठा bfa_ioc_mbox_mod *mod = &ioc->mbox_mod;
	पूर्णांक	mc;

	INIT_LIST_HEAD(&mod->cmd_q);
	क्रम (mc = 0; mc < BFI_MC_MAX; mc++) अणु
		mod->mbhdlr[mc].cbfn = शून्य;
		mod->mbhdlr[mc].cbarg = ioc->bfa;
	पूर्ण
पूर्ण

/* Mbox poll समयr -- restarts any pending mailbox requests. */
अटल व्योम
bfa_ioc_mbox_poll(काष्ठा bfa_ioc *ioc)
अणु
	काष्ठा bfa_ioc_mbox_mod *mod = &ioc->mbox_mod;
	काष्ठा bfa_mbox_cmd *cmd;
	bfa_mbox_cmd_cbfn_t cbfn;
	व्योम *cbarg;
	u32 stat;

	/**
	 * If no command pending, करो nothing
	 */
	अगर (list_empty(&mod->cmd_q))
		वापस;

	/**
	 * If previous command is not yet fetched by firmware, करो nothing
	 */
	stat = पढ़ोl(ioc->ioc_regs.hfn_mbox_cmd);
	अगर (stat)
		वापस;

	/**
	 * Enqueue command to firmware.
	 */
	cmd = list_first_entry(&mod->cmd_q, काष्ठा bfa_mbox_cmd, qe);
	list_del(&cmd->qe);
	bfa_ioc_mbox_send(ioc, cmd->msg, माप(cmd->msg));

	/**
	 * Give a callback to the client, indicating that the command is sent
	 */
	अगर (cmd->cbfn) अणु
		cbfn = cmd->cbfn;
		cbarg = cmd->cbarg;
		cmd->cbfn = शून्य;
		cbfn(cbarg);
	पूर्ण
पूर्ण

/* Cleanup any pending requests. */
अटल व्योम
bfa_ioc_mbox_flush(काष्ठा bfa_ioc *ioc)
अणु
	काष्ठा bfa_ioc_mbox_mod *mod = &ioc->mbox_mod;
	काष्ठा bfa_mbox_cmd *cmd;

	जबतक (!list_empty(&mod->cmd_q)) अणु
		cmd = list_first_entry(&mod->cmd_q, काष्ठा bfa_mbox_cmd, qe);
		list_del(&cmd->qe);
	पूर्ण
पूर्ण

/**
 * bfa_nw_ioc_smem_पढ़ो - Read data from SMEM to host through PCI memmap
 *
 * @ioc:     memory क्रम IOC
 * @tbuf:    app memory to store data from smem
 * @soff:    smem offset
 * @sz:      size of smem in bytes
 */
अटल पूर्णांक
bfa_nw_ioc_smem_पढ़ो(काष्ठा bfa_ioc *ioc, व्योम *tbuf, u32 soff, u32 sz)
अणु
	u32 pgnum, loff, r32;
	पूर्णांक i, len;
	u32 *buf = tbuf;

	pgnum = PSS_SMEM_PGNUM(ioc->ioc_regs.smem_pg0, soff);
	loff = PSS_SMEM_PGOFF(soff);

	/*
	 *  Hold semaphore to serialize pll init and fwtrc.
	*/
	अगर (!bfa_nw_ioc_sem_get(ioc->ioc_regs.ioc_init_sem_reg))
		वापस 1;

	ग_लिखोl(pgnum, ioc->ioc_regs.host_page_num_fn);

	len = sz/माप(u32);
	क्रम (i = 0; i < len; i++) अणु
		r32 = swab32(पढ़ोl(loff + ioc->ioc_regs.smem_page_start));
		buf[i] = be32_to_cpu(r32);
		loff += माप(u32);

		/**
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
	 * release semaphore
	 */
	पढ़ोl(ioc->ioc_regs.ioc_init_sem_reg);
	ग_लिखोl(1, ioc->ioc_regs.ioc_init_sem_reg);
	वापस 0;
पूर्ण

/* Retrieve saved firmware trace from a prior IOC failure. */
पूर्णांक
bfa_nw_ioc_debug_fwtrc(काष्ठा bfa_ioc *ioc, व्योम *trcdata, पूर्णांक *trclen)
अणु
	u32 loff = BFI_IOC_TRC_OFF + BNA_DBG_FWTRC_LEN * ioc->port_id;
	पूर्णांक tlen, status = 0;

	tlen = *trclen;
	अगर (tlen > BNA_DBG_FWTRC_LEN)
		tlen = BNA_DBG_FWTRC_LEN;

	status = bfa_nw_ioc_smem_पढ़ो(ioc, trcdata, loff, tlen);
	*trclen = tlen;
	वापस status;
पूर्ण

/* Save firmware trace अगर configured. */
अटल व्योम
bfa_nw_ioc_debug_save_ftrc(काष्ठा bfa_ioc *ioc)
अणु
	पूर्णांक tlen;

	अगर (ioc->dbg_fwsave_once) अणु
		ioc->dbg_fwsave_once = false;
		अगर (ioc->dbg_fwsave_len) अणु
			tlen = ioc->dbg_fwsave_len;
			bfa_nw_ioc_debug_fwtrc(ioc, ioc->dbg_fwsave, &tlen);
		पूर्ण
	पूर्ण
पूर्ण

/* Retrieve saved firmware trace from a prior IOC failure. */
पूर्णांक
bfa_nw_ioc_debug_fwsave(काष्ठा bfa_ioc *ioc, व्योम *trcdata, पूर्णांक *trclen)
अणु
	पूर्णांक tlen;

	अगर (ioc->dbg_fwsave_len == 0)
		वापस BFA_STATUS_ENOFSAVE;

	tlen = *trclen;
	अगर (tlen > ioc->dbg_fwsave_len)
		tlen = ioc->dbg_fwsave_len;

	स_नकल(trcdata, ioc->dbg_fwsave, tlen);
	*trclen = tlen;
	वापस BFA_STATUS_OK;
पूर्ण

अटल व्योम
bfa_ioc_fail_notअगरy(काष्ठा bfa_ioc *ioc)
अणु
	/**
	 * Notअगरy driver and common modules रेजिस्टरed क्रम notअगरication.
	 */
	ioc->cbfn->hbfail_cbfn(ioc->bfa);
	bfa_ioc_event_notअगरy(ioc, BFA_IOC_E_FAILED);
	bfa_nw_ioc_debug_save_ftrc(ioc);
पूर्ण

/* IOCPF to IOC पूर्णांकerface */
अटल व्योम
bfa_ioc_pf_enabled(काष्ठा bfa_ioc *ioc)
अणु
	bfa_fsm_send_event(ioc, IOC_E_ENABLED);
पूर्ण

अटल व्योम
bfa_ioc_pf_disabled(काष्ठा bfa_ioc *ioc)
अणु
	bfa_fsm_send_event(ioc, IOC_E_DISABLED);
पूर्ण

अटल व्योम
bfa_ioc_pf_failed(काष्ठा bfa_ioc *ioc)
अणु
	bfa_fsm_send_event(ioc, IOC_E_PFFAILED);
पूर्ण

अटल व्योम
bfa_ioc_pf_hwfailed(काष्ठा bfa_ioc *ioc)
अणु
	bfa_fsm_send_event(ioc, IOC_E_HWFAILED);
पूर्ण

अटल व्योम
bfa_ioc_pf_fwmismatch(काष्ठा bfa_ioc *ioc)
अणु
	/**
	 * Provide enable completion callback and AEN notअगरication.
	 */
	ioc->cbfn->enable_cbfn(ioc->bfa, BFA_STATUS_IOC_FAILURE);
पूर्ण

/* IOC खुला */
अटल क्रमागत bfa_status
bfa_ioc_pll_init(काष्ठा bfa_ioc *ioc)
अणु
	/*
	 *  Hold semaphore so that nobody can access the chip during init.
	 */
	bfa_nw_ioc_sem_get(ioc->ioc_regs.ioc_init_sem_reg);

	bfa_ioc_pll_init_asic(ioc);

	ioc->pllinit = true;

	/* Initialize LMEM */
	bfa_ioc_lmem_init(ioc);

	/*
	 *  release semaphore.
	 */
	bfa_nw_ioc_sem_release(ioc->ioc_regs.ioc_init_sem_reg);

	वापस BFA_STATUS_OK;
पूर्ण

/* Interface used by diag module to करो firmware boot with memory test
 * as the entry vector.
 */
अटल क्रमागत bfa_status
bfa_ioc_boot(काष्ठा bfa_ioc *ioc, क्रमागत bfi_fwboot_type boot_type,
		u32 boot_env)
अणु
	काष्ठा bfi_ioc_image_hdr *drv_fwhdr;
	क्रमागत bfa_status status;
	bfa_ioc_stats(ioc, ioc_boots);

	अगर (bfa_ioc_pll_init(ioc) != BFA_STATUS_OK)
		वापस BFA_STATUS_FAILED;
	अगर (boot_env == BFI_FWBOOT_ENV_OS &&
	    boot_type == BFI_FWBOOT_TYPE_NORMAL) अणु
		drv_fwhdr = (काष्ठा bfi_ioc_image_hdr *)
			bfa_cb_image_get_chunk(bfa_ioc_asic_gen(ioc), 0);
		/* Work with Flash अगरf flash f/w is better than driver f/w.
		 * Otherwise push drivers firmware.
		 */
		अगर (bfa_ioc_flash_fwver_cmp(ioc, drv_fwhdr) ==
			BFI_IOC_IMG_VER_BETTER)
			boot_type = BFI_FWBOOT_TYPE_FLASH;
	पूर्ण

	/**
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
	अन्यथा
		bfa_fsm_send_event(&ioc->iocpf, IOCPF_E_TIMEOUT);

	वापस status;
पूर्ण

/* Enable/disable IOC failure स्वतः recovery. */
व्योम
bfa_nw_ioc_स्वतः_recover(bool स्वतः_recover)
अणु
	bfa_nw_स्वतः_recover = स्वतः_recover;
पूर्ण

अटल bool
bfa_ioc_msgget(काष्ठा bfa_ioc *ioc, व्योम *mbmsg)
अणु
	u32	*msgp = mbmsg;
	u32	r32;
	पूर्णांक		i;

	r32 = पढ़ोl(ioc->ioc_regs.lpu_mbox_cmd);
	अगर ((r32 & 1) == 0)
		वापस false;

	/**
	 * पढ़ो the MBOX msg
	 */
	क्रम (i = 0; i < (माप(जोड़ bfi_ioc_i2h_msg_u) / माप(u32));
	     i++) अणु
		r32 = पढ़ोl(ioc->ioc_regs.lpu_mbox +
				   i * माप(u32));
		msgp[i] = htonl(r32);
	पूर्ण

	/**
	 * turn off mailbox पूर्णांकerrupt by clearing mailbox status
	 */
	ग_लिखोl(1, ioc->ioc_regs.lpu_mbox_cmd);
	पढ़ोl(ioc->ioc_regs.lpu_mbox_cmd);

	वापस true;
पूर्ण

अटल व्योम
bfa_ioc_isr(काष्ठा bfa_ioc *ioc, काष्ठा bfi_mbmsg *m)
अणु
	जोड़ bfi_ioc_i2h_msg_u	*msg;
	काष्ठा bfa_iocpf *iocpf = &ioc->iocpf;

	msg = (जोड़ bfi_ioc_i2h_msg_u *) m;

	bfa_ioc_stats(ioc, ioc_isrs);

	चयन (msg->mh.msg_id) अणु
	हाल BFI_IOC_I2H_HBEAT:
		अवरोध;

	हाल BFI_IOC_I2H_ENABLE_REPLY:
		bfa_ioc_enable_reply(ioc,
			(क्रमागत bfa_mode)msg->fw_event.port_mode,
			msg->fw_event.cap_bm);
		अवरोध;

	हाल BFI_IOC_I2H_DISABLE_REPLY:
		bfa_fsm_send_event(iocpf, IOCPF_E_FWRSP_DISABLE);
		अवरोध;

	हाल BFI_IOC_I2H_GETATTR_REPLY:
		bfa_ioc_getattr_reply(ioc);
		अवरोध;

	शेष:
		BUG_ON(1);
	पूर्ण
पूर्ण

/**
 * bfa_nw_ioc_attach - IOC attach समय initialization and setup.
 *
 * @ioc:	memory क्रम IOC
 * @bfa:	driver instance काष्ठाure
 * @cbfn:	callback function
 */
व्योम
bfa_nw_ioc_attach(काष्ठा bfa_ioc *ioc, व्योम *bfa, काष्ठा bfa_ioc_cbfn *cbfn)
अणु
	ioc->bfa	= bfa;
	ioc->cbfn	= cbfn;
	ioc->fcmode	= false;
	ioc->pllinit	= false;
	ioc->dbg_fwsave_once = true;
	ioc->iocpf.ioc  = ioc;

	bfa_ioc_mbox_attach(ioc);
	INIT_LIST_HEAD(&ioc->notअगरy_q);

	bfa_fsm_set_state(ioc, bfa_ioc_sm_uninit);
	bfa_fsm_send_event(ioc, IOC_E_RESET);
पूर्ण

/* Driver detach समय IOC cleanup. */
व्योम
bfa_nw_ioc_detach(काष्ठा bfa_ioc *ioc)
अणु
	bfa_fsm_send_event(ioc, IOC_E_DETACH);

	/* Done with detach, empty the notअगरy_q. */
	INIT_LIST_HEAD(&ioc->notअगरy_q);
पूर्ण

/**
 * bfa_nw_ioc_pci_init - Setup IOC PCI properties.
 *
 * @ioc:	memory क्रम IOC
 * @pcidev:	PCI device inक्रमmation क्रम this IOC
 * @clscode:	class code
 */
व्योम
bfa_nw_ioc_pci_init(काष्ठा bfa_ioc *ioc, काष्ठा bfa_pcidev *pcidev,
		 क्रमागत bfi_pcअगरn_class clscode)
अणु
	ioc->clscode	= clscode;
	ioc->pcidev	= *pcidev;

	/**
	 * Initialize IOC and device personality
	 */
	ioc->port0_mode = ioc->port1_mode = BFI_PORT_MODE_FC;
	ioc->asic_mode  = BFI_ASIC_MODE_FC;

	चयन (pcidev->device_id) अणु
	हाल PCI_DEVICE_ID_BROCADE_CT:
		ioc->asic_gen = BFI_ASIC_GEN_CT;
		ioc->port0_mode = ioc->port1_mode = BFI_PORT_MODE_ETH;
		ioc->asic_mode  = BFI_ASIC_MODE_ETH;
		ioc->port_mode = ioc->port_mode_cfg = BFA_MODE_CNA;
		ioc->ad_cap_bm = BFA_CM_CNA;
		अवरोध;

	हाल BFA_PCI_DEVICE_ID_CT2:
		ioc->asic_gen = BFI_ASIC_GEN_CT2;
		अगर (clscode == BFI_PCIFN_CLASS_FC &&
			pcidev->ssid == BFA_PCI_CT2_SSID_FC) अणु
			ioc->asic_mode  = BFI_ASIC_MODE_FC16;
			ioc->fcmode = true;
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
		BUG_ON(1);
	पूर्ण

	/**
	 * Set asic specअगरic पूर्णांकerfaces.
	 */
	अगर (ioc->asic_gen == BFI_ASIC_GEN_CT)
		bfa_nw_ioc_set_ct_hwअगर(ioc);
	अन्यथा अणु
		WARN_ON(ioc->asic_gen != BFI_ASIC_GEN_CT2);
		bfa_nw_ioc_set_ct2_hwअगर(ioc);
		bfa_nw_ioc_ct2_घातeron(ioc);
	पूर्ण

	bfa_ioc_map_port(ioc);
	bfa_ioc_reg_init(ioc);
पूर्ण

/**
 * bfa_nw_ioc_mem_claim - Initialize IOC dma memory
 *
 * @ioc:	memory क्रम IOC
 * @dm_kva:	kernel भव address of IOC dma memory
 * @dm_pa:	physical address of IOC dma memory
 */
व्योम
bfa_nw_ioc_mem_claim(काष्ठा bfa_ioc *ioc,  u8 *dm_kva, u64 dm_pa)
अणु
	/**
	 * dma memory क्रम firmware attribute
	 */
	ioc->attr_dma.kva = dm_kva;
	ioc->attr_dma.pa = dm_pa;
	ioc->attr = (काष्ठा bfi_ioc_attr *) dm_kva;
पूर्ण

/* Return size of dma memory required. */
u32
bfa_nw_ioc_meminfo(व्योम)
अणु
	वापस roundup(माप(काष्ठा bfi_ioc_attr), BFA_DMA_ALIGN_SZ);
पूर्ण

व्योम
bfa_nw_ioc_enable(काष्ठा bfa_ioc *ioc)
अणु
	bfa_ioc_stats(ioc, ioc_enables);
	ioc->dbg_fwsave_once = true;

	bfa_fsm_send_event(ioc, IOC_E_ENABLE);
पूर्ण

व्योम
bfa_nw_ioc_disable(काष्ठा bfa_ioc *ioc)
अणु
	bfa_ioc_stats(ioc, ioc_disables);
	bfa_fsm_send_event(ioc, IOC_E_DISABLE);
पूर्ण

/* Initialize memory क्रम saving firmware trace. */
व्योम
bfa_nw_ioc_debug_memclaim(काष्ठा bfa_ioc *ioc, व्योम *dbg_fwsave)
अणु
	ioc->dbg_fwsave = dbg_fwsave;
	ioc->dbg_fwsave_len = ioc->iocpf.स्वतः_recover ? BNA_DBG_FWTRC_LEN : 0;
पूर्ण

अटल u32
bfa_ioc_smem_pgnum(काष्ठा bfa_ioc *ioc, u32 fmaddr)
अणु
	वापस PSS_SMEM_PGNUM(ioc->ioc_regs.smem_pg0, fmaddr);
पूर्ण

/* Register mailbox message handler function, to be called by common modules */
व्योम
bfa_nw_ioc_mbox_regisr(काष्ठा bfa_ioc *ioc, क्रमागत bfi_mclass mc,
		    bfa_ioc_mbox_mcfunc_t cbfn, व्योम *cbarg)
अणु
	काष्ठा bfa_ioc_mbox_mod *mod = &ioc->mbox_mod;

	mod->mbhdlr[mc].cbfn	= cbfn;
	mod->mbhdlr[mc].cbarg = cbarg;
पूर्ण

/**
 * bfa_nw_ioc_mbox_queue - Queue a mailbox command request to firmware.
 *
 * @ioc:	IOC instance
 * @cmd:	Mailbox command
 * @cbfn:	callback function
 * @cbarg:	arguments to callback
 *
 * Waits अगर mailbox is busy. Responsibility of caller to serialize
 */
bool
bfa_nw_ioc_mbox_queue(काष्ठा bfa_ioc *ioc, काष्ठा bfa_mbox_cmd *cmd,
			bfa_mbox_cmd_cbfn_t cbfn, व्योम *cbarg)
अणु
	काष्ठा bfa_ioc_mbox_mod *mod = &ioc->mbox_mod;
	u32			stat;

	cmd->cbfn = cbfn;
	cmd->cbarg = cbarg;

	/**
	 * If a previous command is pending, queue new command
	 */
	अगर (!list_empty(&mod->cmd_q)) अणु
		list_add_tail(&cmd->qe, &mod->cmd_q);
		वापस true;
	पूर्ण

	/**
	 * If mailbox is busy, queue command क्रम poll समयr
	 */
	stat = पढ़ोl(ioc->ioc_regs.hfn_mbox_cmd);
	अगर (stat) अणु
		list_add_tail(&cmd->qe, &mod->cmd_q);
		वापस true;
	पूर्ण

	/**
	 * mailbox is मुक्त -- queue command to firmware
	 */
	bfa_ioc_mbox_send(ioc, cmd->msg, माप(cmd->msg));

	वापस false;
पूर्ण

/* Handle mailbox पूर्णांकerrupts */
व्योम
bfa_nw_ioc_mbox_isr(काष्ठा bfa_ioc *ioc)
अणु
	काष्ठा bfa_ioc_mbox_mod *mod = &ioc->mbox_mod;
	काष्ठा bfi_mbmsg m;
	पूर्णांक				mc;

	अगर (bfa_ioc_msgget(ioc, &m)) अणु
		/**
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

	/**
	 * Try to send pending mailbox commands
	 */
	bfa_ioc_mbox_poll(ioc);
पूर्ण

व्योम
bfa_nw_ioc_error_isr(काष्ठा bfa_ioc *ioc)
अणु
	bfa_ioc_stats(ioc, ioc_hbfails);
	bfa_ioc_stats_hb_count(ioc, ioc->hb_count);
	bfa_fsm_send_event(ioc, IOC_E_HWERROR);
पूर्ण

/* वापस true अगर IOC is disabled */
bool
bfa_nw_ioc_is_disabled(काष्ठा bfa_ioc *ioc)
अणु
	वापस bfa_fsm_cmp_state(ioc, bfa_ioc_sm_disabling) ||
		bfa_fsm_cmp_state(ioc, bfa_ioc_sm_disabled);
पूर्ण

/* वापस true अगर IOC is operational */
bool
bfa_nw_ioc_is_operational(काष्ठा bfa_ioc *ioc)
अणु
	वापस bfa_fsm_cmp_state(ioc, bfa_ioc_sm_op);
पूर्ण

/* Add to IOC heartbeat failure notअगरication queue. To be used by common
 * modules such as cee, port, diag.
 */
व्योम
bfa_nw_ioc_notअगरy_रेजिस्टर(काष्ठा bfa_ioc *ioc,
			काष्ठा bfa_ioc_notअगरy *notअगरy)
अणु
	list_add_tail(&notअगरy->qe, &ioc->notअगरy_q);
पूर्ण

#घोषणा BFA_MFG_NAME "QLogic"
अटल व्योम
bfa_ioc_get_adapter_attr(काष्ठा bfa_ioc *ioc,
			 काष्ठा bfa_adapter_attr *ad_attr)
अणु
	काष्ठा bfi_ioc_attr *ioc_attr;

	ioc_attr = ioc->attr;

	bfa_ioc_get_adapter_serial_num(ioc, ad_attr->serial_num);
	bfa_ioc_get_adapter_fw_ver(ioc, ad_attr->fw_ver);
	bfa_ioc_get_adapter_optrom_ver(ioc, ad_attr->optrom_ver);
	bfa_ioc_get_adapter_manufacturer(ioc, ad_attr->manufacturer);
	स_नकल(&ad_attr->vpd, &ioc_attr->vpd,
		      माप(काष्ठा bfa_mfg_vpd));

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

	ad_attr->pwwn = bfa_ioc_get_pwwn(ioc);
	bfa_nw_ioc_get_mac(ioc, ad_attr->mac);

	ad_attr->pcie_gen = ioc_attr->pcie_gen;
	ad_attr->pcie_lanes = ioc_attr->pcie_lanes;
	ad_attr->pcie_lanes_orig = ioc_attr->pcie_lanes_orig;
	ad_attr->asic_rev = ioc_attr->asic_rev;

	bfa_ioc_get_pci_chip_rev(ioc, ad_attr->hw_ver);
पूर्ण

अटल क्रमागत bfa_ioc_type
bfa_ioc_get_type(काष्ठा bfa_ioc *ioc)
अणु
	अगर (ioc->clscode == BFI_PCIFN_CLASS_ETH)
		वापस BFA_IOC_TYPE_LL;

	BUG_ON(!(ioc->clscode == BFI_PCIFN_CLASS_FC));

	वापस (ioc->attr->port_mode == BFI_PORT_MODE_FC)
		? BFA_IOC_TYPE_FC : BFA_IOC_TYPE_FCoE;
पूर्ण

अटल व्योम
bfa_ioc_get_adapter_serial_num(काष्ठा bfa_ioc *ioc, अक्षर *serial_num)
अणु
	स_नकल(serial_num,
			(व्योम *)ioc->attr->brcd_serialnum,
			BFA_ADAPTER_SERIAL_NUM_LEN);
पूर्ण

अटल व्योम
bfa_ioc_get_adapter_fw_ver(काष्ठा bfa_ioc *ioc, अक्षर *fw_ver)
अणु
	स_नकल(fw_ver, ioc->attr->fw_version, BFA_VERSION_LEN);
पूर्ण

अटल व्योम
bfa_ioc_get_pci_chip_rev(काष्ठा bfa_ioc *ioc, अक्षर *chip_rev)
अणु
	BUG_ON(!(chip_rev));

	स_रखो(chip_rev, 0, BFA_IOC_CHIP_REV_LEN);

	chip_rev[0] = 'R';
	chip_rev[1] = 'e';
	chip_rev[2] = 'v';
	chip_rev[3] = '-';
	chip_rev[4] = ioc->attr->asic_rev;
	chip_rev[5] = '\0';
पूर्ण

अटल व्योम
bfa_ioc_get_adapter_optrom_ver(काष्ठा bfa_ioc *ioc, अक्षर *optrom_ver)
अणु
	स_नकल(optrom_ver, ioc->attr->optrom_version,
		      BFA_VERSION_LEN);
पूर्ण

अटल व्योम
bfa_ioc_get_adapter_manufacturer(काष्ठा bfa_ioc *ioc, अक्षर *manufacturer)
अणु
	म_नकलन(manufacturer, BFA_MFG_NAME, BFA_ADAPTER_MFG_NAME_LEN);
पूर्ण

अटल व्योम
bfa_ioc_get_adapter_model(काष्ठा bfa_ioc *ioc, अक्षर *model)
अणु
	काष्ठा bfi_ioc_attr *ioc_attr;

	BUG_ON(!(model));
	स_रखो(model, 0, BFA_ADAPTER_MODEL_NAME_LEN);

	ioc_attr = ioc->attr;

	snम_लिखो(model, BFA_ADAPTER_MODEL_NAME_LEN, "%s-%u",
		BFA_MFG_NAME, ioc_attr->card_type);
पूर्ण

अटल क्रमागत bfa_ioc_state
bfa_ioc_get_state(काष्ठा bfa_ioc *ioc)
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
bfa_nw_ioc_get_attr(काष्ठा bfa_ioc *ioc, काष्ठा bfa_ioc_attr *ioc_attr)
अणु
	स_रखो((व्योम *)ioc_attr, 0, माप(काष्ठा bfa_ioc_attr));

	ioc_attr->state = bfa_ioc_get_state(ioc);
	ioc_attr->port_id = bfa_ioc_portid(ioc);
	ioc_attr->port_mode = ioc->port_mode;

	ioc_attr->port_mode_cfg = ioc->port_mode_cfg;
	ioc_attr->cap_bm = ioc->ad_cap_bm;

	ioc_attr->ioc_type = bfa_ioc_get_type(ioc);

	bfa_ioc_get_adapter_attr(ioc, &ioc_attr->adapter_attr);

	ioc_attr->pci_attr.device_id = bfa_ioc_devid(ioc);
	ioc_attr->pci_attr.pcअगरn = bfa_ioc_pcअगरn(ioc);
	ioc_attr->def_fn = bfa_ioc_is_शेष(ioc);
	bfa_ioc_get_pci_chip_rev(ioc, ioc_attr->pci_attr.chip_rev);
पूर्ण

/* WWN खुला */
अटल u64
bfa_ioc_get_pwwn(काष्ठा bfa_ioc *ioc)
अणु
	वापस ioc->attr->pwwn;
पूर्ण

व्योम
bfa_nw_ioc_get_mac(काष्ठा bfa_ioc *ioc, u8 *mac)
अणु
	ether_addr_copy(mac, ioc->attr->mac);
पूर्ण

/* Firmware failure detected. Start recovery actions. */
अटल व्योम
bfa_ioc_recover(काष्ठा bfa_ioc *ioc)
अणु
	pr_crit("Heart Beat of IOC has failed\n");
	bfa_ioc_stats(ioc, ioc_hbfails);
	bfa_ioc_stats_hb_count(ioc, ioc->hb_count);
	bfa_fsm_send_event(ioc, IOC_E_HBFAIL);
पूर्ण

/* BFA IOC PF निजी functions */

अटल व्योम
bfa_iocpf_enable(काष्ठा bfa_ioc *ioc)
अणु
	bfa_fsm_send_event(&ioc->iocpf, IOCPF_E_ENABLE);
पूर्ण

अटल व्योम
bfa_iocpf_disable(काष्ठा bfa_ioc *ioc)
अणु
	bfa_fsm_send_event(&ioc->iocpf, IOCPF_E_DISABLE);
पूर्ण

अटल व्योम
bfa_iocpf_fail(काष्ठा bfa_ioc *ioc)
अणु
	bfa_fsm_send_event(&ioc->iocpf, IOCPF_E_FAIL);
पूर्ण

अटल व्योम
bfa_iocpf_initfail(काष्ठा bfa_ioc *ioc)
अणु
	bfa_fsm_send_event(&ioc->iocpf, IOCPF_E_INITFAIL);
पूर्ण

अटल व्योम
bfa_iocpf_getattrfail(काष्ठा bfa_ioc *ioc)
अणु
	bfa_fsm_send_event(&ioc->iocpf, IOCPF_E_GETATTRFAIL);
पूर्ण

अटल व्योम
bfa_iocpf_stop(काष्ठा bfa_ioc *ioc)
अणु
	bfa_fsm_send_event(&ioc->iocpf, IOCPF_E_STOP);
पूर्ण

व्योम
bfa_nw_iocpf_समयout(काष्ठा bfa_ioc *ioc)
अणु
	क्रमागत bfa_iocpf_state iocpf_st;

	iocpf_st = bfa_sm_to_state(iocpf_sm_table, ioc->iocpf.fsm);

	अगर (iocpf_st == BFA_IOCPF_HWINIT)
		bfa_ioc_poll_fwinit(ioc);
	अन्यथा
		bfa_fsm_send_event(&ioc->iocpf, IOCPF_E_TIMEOUT);
पूर्ण

व्योम
bfa_nw_iocpf_sem_समयout(काष्ठा bfa_ioc *ioc)
अणु
	bfa_ioc_hw_sem_get(ioc);
पूर्ण

अटल व्योम
bfa_ioc_poll_fwinit(काष्ठा bfa_ioc *ioc)
अणु
	u32 fwstate = bfa_ioc_get_cur_ioc_fwstate(ioc);

	अगर (fwstate == BFI_IOC_DISABLED) अणु
		bfa_fsm_send_event(&ioc->iocpf, IOCPF_E_FWREADY);
		वापस;
	पूर्ण

	अगर (ioc->iocpf.poll_समय >= BFA_IOC_TOV) अणु
		bfa_fsm_send_event(&ioc->iocpf, IOCPF_E_TIMEOUT);
	पूर्ण अन्यथा अणु
		ioc->iocpf.poll_समय += BFA_IOC_POLL_TOV;
		mod_समयr(&ioc->iocpf_समयr, jअगरfies +
			msecs_to_jअगरfies(BFA_IOC_POLL_TOV));
	पूर्ण
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
	roundup(0x010000 + माप(काष्ठा bfa_mfg_block), BFA_FLASH_SEG_SZ)

अटल व्योम
bfa_flash_cb(काष्ठा bfa_flash *flash)
अणु
	flash->op_busy = 0;
	अगर (flash->cbfn)
		flash->cbfn(flash->cbarg, flash->status);
पूर्ण

अटल व्योम
bfa_flash_notअगरy(व्योम *cbarg, क्रमागत bfa_ioc_event event)
अणु
	काष्ठा bfa_flash *flash = cbarg;

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
 * Send flash ग_लिखो request.
 */
अटल व्योम
bfa_flash_ग_लिखो_send(काष्ठा bfa_flash *flash)
अणु
	काष्ठा bfi_flash_ग_लिखो_req *msg =
			(काष्ठा bfi_flash_ग_लिखो_req *) flash->mb.msg;
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
	bfa_nw_ioc_mbox_queue(flash->ioc, &flash->mb, शून्य, शून्य);

	flash->residue -= len;
	flash->offset += len;
पूर्ण

/**
 * bfa_flash_पढ़ो_send - Send flash पढ़ो request.
 *
 * @cbarg: callback argument
 */
अटल व्योम
bfa_flash_पढ़ो_send(व्योम *cbarg)
अणु
	काष्ठा bfa_flash *flash = cbarg;
	काष्ठा bfi_flash_पढ़ो_req *msg =
			(काष्ठा bfi_flash_पढ़ो_req *) flash->mb.msg;
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
	bfa_nw_ioc_mbox_queue(flash->ioc, &flash->mb, शून्य, शून्य);
पूर्ण

/**
 * bfa_flash_पूर्णांकr - Process flash response messages upon receiving पूर्णांकerrupts.
 *
 * @flasharg: flash काष्ठाure
 * @msg: message काष्ठाure
 */
अटल व्योम
bfa_flash_पूर्णांकr(व्योम *flasharg, काष्ठा bfi_mbmsg *msg)
अणु
	काष्ठा bfa_flash *flash = flasharg;
	u32	status;

	जोड़ अणु
		काष्ठा bfi_flash_query_rsp *query;
		काष्ठा bfi_flash_ग_लिखो_rsp *ग_लिखो;
		काष्ठा bfi_flash_पढ़ो_rsp *पढ़ो;
		काष्ठा bfi_mbmsg   *msg;
	पूर्ण m;

	m.msg = msg;

	/* receiving response after ioc failure */
	अगर (!flash->op_busy && msg->mh.msg_id != BFI_FLASH_I2H_EVENT)
		वापस;

	चयन (msg->mh.msg_id) अणु
	हाल BFI_FLASH_I2H_QUERY_RSP:
		status = be32_to_cpu(m.query->status);
		अगर (status == BFA_STATUS_OK) अणु
			u32	i;
			काष्ठा bfa_flash_attr *attr, *f;

			attr = (काष्ठा bfa_flash_attr *) flash->ubuf;
			f = (काष्ठा bfa_flash_attr *) flash->dbuf_kva;
			attr->status = be32_to_cpu(f->status);
			attr->npart = be32_to_cpu(f->npart);
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
	हाल BFI_FLASH_I2H_WRITE_RSP:
		status = be32_to_cpu(m.ग_लिखो->status);
		अगर (status != BFA_STATUS_OK || flash->residue == 0) अणु
			flash->status = status;
			bfa_flash_cb(flash);
		पूर्ण अन्यथा
			bfa_flash_ग_लिखो_send(flash);
		अवरोध;
	हाल BFI_FLASH_I2H_READ_RSP:
		status = be32_to_cpu(m.पढ़ो->status);
		अगर (status != BFA_STATUS_OK) अणु
			flash->status = status;
			bfa_flash_cb(flash);
		पूर्ण अन्यथा अणु
			u32 len = be32_to_cpu(m.पढ़ो->length);
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
	हाल BFI_FLASH_I2H_EVENT:
		अवरोध;
	शेष:
		WARN_ON(1);
	पूर्ण
पूर्ण

/*
 * Flash memory info API.
 */
u32
bfa_nw_flash_meminfo(व्योम)
अणु
	वापस roundup(BFA_FLASH_DMA_BUF_SZ, BFA_DMA_ALIGN_SZ);
पूर्ण

/**
 * bfa_nw_flash_attach - Flash attach API.
 *
 * @flash: flash काष्ठाure
 * @ioc: ioc काष्ठाure
 * @dev: device काष्ठाure
 */
व्योम
bfa_nw_flash_attach(काष्ठा bfa_flash *flash, काष्ठा bfa_ioc *ioc, व्योम *dev)
अणु
	flash->ioc = ioc;
	flash->cbfn = शून्य;
	flash->cbarg = शून्य;
	flash->op_busy = 0;

	bfa_nw_ioc_mbox_regisr(flash->ioc, BFI_MC_FLASH, bfa_flash_पूर्णांकr, flash);
	bfa_ioc_notअगरy_init(&flash->ioc_notअगरy, bfa_flash_notअगरy, flash);
	list_add_tail(&flash->ioc_notअगरy.qe, &flash->ioc->notअगरy_q);
पूर्ण

/**
 * bfa_nw_flash_memclaim - Claim memory क्रम flash
 *
 * @flash: flash काष्ठाure
 * @dm_kva: poपूर्णांकer to भव memory address
 * @dm_pa: physical memory address
 */
व्योम
bfa_nw_flash_memclaim(काष्ठा bfa_flash *flash, u8 *dm_kva, u64 dm_pa)
अणु
	flash->dbuf_kva = dm_kva;
	flash->dbuf_pa = dm_pa;
	स_रखो(flash->dbuf_kva, 0, BFA_FLASH_DMA_BUF_SZ);
	dm_kva += roundup(BFA_FLASH_DMA_BUF_SZ, BFA_DMA_ALIGN_SZ);
	dm_pa += roundup(BFA_FLASH_DMA_BUF_SZ, BFA_DMA_ALIGN_SZ);
पूर्ण

/**
 * bfa_nw_flash_get_attr - Get flash attribute.
 *
 * @flash: flash काष्ठाure
 * @attr: flash attribute काष्ठाure
 * @cbfn: callback function
 * @cbarg: callback argument
 *
 * Return status.
 */
क्रमागत bfa_status
bfa_nw_flash_get_attr(काष्ठा bfa_flash *flash, काष्ठा bfa_flash_attr *attr,
		      bfa_cb_flash cbfn, व्योम *cbarg)
अणु
	काष्ठा bfi_flash_query_req *msg =
			(काष्ठा bfi_flash_query_req *) flash->mb.msg;

	अगर (!bfa_nw_ioc_is_operational(flash->ioc))
		वापस BFA_STATUS_IOC_NON_OP;

	अगर (flash->op_busy)
		वापस BFA_STATUS_DEVBUSY;

	flash->op_busy = 1;
	flash->cbfn = cbfn;
	flash->cbarg = cbarg;
	flash->ubuf = (u8 *) attr;

	bfi_h2i_set(msg->mh, BFI_MC_FLASH, BFI_FLASH_H2I_QUERY_REQ,
		    bfa_ioc_portid(flash->ioc));
	bfa_alen_set(&msg->alen, माप(काष्ठा bfa_flash_attr), flash->dbuf_pa);
	bfa_nw_ioc_mbox_queue(flash->ioc, &flash->mb, शून्य, शून्य);

	वापस BFA_STATUS_OK;
पूर्ण

/**
 * bfa_nw_flash_update_part - Update flash partition.
 *
 * @flash: flash काष्ठाure
 * @type: flash partition type
 * @instance: flash partition instance
 * @buf: update data buffer
 * @len: data buffer length
 * @offset: offset relative to the partition starting address
 * @cbfn: callback function
 * @cbarg: callback argument
 *
 * Return status.
 */
क्रमागत bfa_status
bfa_nw_flash_update_part(काष्ठा bfa_flash *flash, u32 type, u8 instance,
			 व्योम *buf, u32 len, u32 offset,
			 bfa_cb_flash cbfn, व्योम *cbarg)
अणु
	अगर (!bfa_nw_ioc_is_operational(flash->ioc))
		वापस BFA_STATUS_IOC_NON_OP;

	/*
	 * 'len' must be in word (4-byte) boundary
	 */
	अगर (!len || (len & 0x03))
		वापस BFA_STATUS_FLASH_BAD_LEN;

	अगर (type == BFA_FLASH_PART_MFG)
		वापस BFA_STATUS_EINVAL;

	अगर (flash->op_busy)
		वापस BFA_STATUS_DEVBUSY;

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

/**
 * bfa_nw_flash_पढ़ो_part - Read flash partition.
 *
 * @flash: flash काष्ठाure
 * @type: flash partition type
 * @instance: flash partition instance
 * @buf: पढ़ो data buffer
 * @len: data buffer length
 * @offset: offset relative to the partition starting address
 * @cbfn: callback function
 * @cbarg: callback argument
 *
 * Return status.
 */
क्रमागत bfa_status
bfa_nw_flash_पढ़ो_part(काष्ठा bfa_flash *flash, u32 type, u8 instance,
		       व्योम *buf, u32 len, u32 offset,
		       bfa_cb_flash cbfn, व्योम *cbarg)
अणु
	अगर (!bfa_nw_ioc_is_operational(flash->ioc))
		वापस BFA_STATUS_IOC_NON_OP;

	/*
	 * 'len' must be in word (4-byte) boundary
	 */
	अगर (!len || (len & 0x03))
		वापस BFA_STATUS_FLASH_BAD_LEN;

	अगर (flash->op_busy)
		वापस BFA_STATUS_DEVBUSY;

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
