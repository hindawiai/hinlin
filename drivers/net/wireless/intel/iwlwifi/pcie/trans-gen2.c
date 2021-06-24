<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause
/*
 * Copyright (C) 2017 Intel Deutschland GmbH
 * Copyright (C) 2018-2021 Intel Corporation
 */
#समावेश "iwl-trans.h"
#समावेश "iwl-prph.h"
#समावेश "iwl-context-info.h"
#समावेश "iwl-context-info-gen3.h"
#समावेश "internal.h"
#समावेश "fw/dbg.h"

#घोषणा FW_RESET_TIMEOUT (HZ / 5)

/*
 * Start up NIC's basic functionality after it has been reset
 * (e.g. after platक्रमm boot, or shutकरोwn via iwl_pcie_apm_stop())
 * NOTE:  This करोes not load uCode nor start the embedded processor
 */
पूर्णांक iwl_pcie_gen2_apm_init(काष्ठा iwl_trans *trans)
अणु
	पूर्णांक ret = 0;

	IWL_DEBUG_INFO(trans, "Init card's basic functions\n");

	/*
	 * Use "set_bit" below rather than "write", to preserve any hardware
	 * bits alपढ़ोy set by शेष after reset.
	 */

	/*
	 * Disable L0s without affecting L1;
	 * करोn't रुको क्रम ICH L0s (ICH bug W/A)
	 */
	iwl_set_bit(trans, CSR_GIO_CHICKEN_BITS,
		    CSR_GIO_CHICKEN_BITS_REG_BIT_L1A_NO_L0S_RX);

	/* Set FH रुको threshold to maximum (HW error during stress W/A) */
	iwl_set_bit(trans, CSR_DBG_HPET_MEM_REG, CSR_DBG_HPET_MEM_REG_VAL);

	/*
	 * Enable HAP INTA (पूर्णांकerrupt from management bus) to
	 * wake device's PCI Express link L1a -> L0s
	 */
	iwl_set_bit(trans, CSR_HW_IF_CONFIG_REG,
		    CSR_HW_IF_CONFIG_REG_BIT_HAP_WAKE_L1A);

	iwl_pcie_apm_config(trans);

	ret = iwl_finish_nic_init(trans, trans->trans_cfg);
	अगर (ret)
		वापस ret;

	set_bit(STATUS_DEVICE_ENABLED, &trans->status);

	वापस 0;
पूर्ण

अटल व्योम iwl_pcie_gen2_apm_stop(काष्ठा iwl_trans *trans, bool op_mode_leave)
अणु
	IWL_DEBUG_INFO(trans, "Stop card, put in low power state\n");

	अगर (op_mode_leave) अणु
		अगर (!test_bit(STATUS_DEVICE_ENABLED, &trans->status))
			iwl_pcie_gen2_apm_init(trans);

		/* inक्रमm ME that we are leaving */
		iwl_set_bit(trans, CSR_DBG_LINK_PWR_MGMT_REG,
			    CSR_RESET_LINK_PWR_MGMT_DISABLED);
		iwl_set_bit(trans, CSR_HW_IF_CONFIG_REG,
			    CSR_HW_IF_CONFIG_REG_PREPARE |
			    CSR_HW_IF_CONFIG_REG_ENABLE_PME);
		mdelay(1);
		iwl_clear_bit(trans, CSR_DBG_LINK_PWR_MGMT_REG,
			      CSR_RESET_LINK_PWR_MGMT_DISABLED);
		mdelay(5);
	पूर्ण

	clear_bit(STATUS_DEVICE_ENABLED, &trans->status);

	/* Stop device's DMA activity */
	iwl_pcie_apm_stop_master(trans);

	iwl_trans_sw_reset(trans);

	/*
	 * Clear "initialization complete" bit to move adapter from
	 * D0A* (घातered-up Active) --> D0U* (Uninitialized) state.
	 */
	iwl_clear_bit(trans, CSR_GP_CNTRL, CSR_GP_CNTRL_REG_FLAG_INIT_DONE);
पूर्ण

अटल व्योम iwl_trans_pcie_fw_reset_handshake(काष्ठा iwl_trans *trans)
अणु
	काष्ठा iwl_trans_pcie *trans_pcie = IWL_TRANS_GET_PCIE_TRANS(trans);
	पूर्णांक ret;

	trans_pcie->fw_reset_करोne = false;

	अगर (trans->trans_cfg->device_family < IWL_DEVICE_FAMILY_AX210)
		iwl_ग_लिखो_umac_prph(trans, UREG_NIC_SET_NMI_DRIVER,
				    UREG_NIC_SET_NMI_DRIVER_RESET_HANDSHAKE);
	अन्यथा
		iwl_ग_लिखो_umac_prph(trans, UREG_DOORBELL_TO_ISR6,
				    UREG_DOORBELL_TO_ISR6_RESET_HANDSHAKE);

	/* रुको 200ms */
	ret = रुको_event_समयout(trans_pcie->fw_reset_रुकोq,
				 trans_pcie->fw_reset_करोne, FW_RESET_TIMEOUT);
	अगर (!ret)
		IWL_INFO(trans,
			 "firmware didn't ACK the reset - continue anyway\n");
पूर्ण

व्योम _iwl_trans_pcie_gen2_stop_device(काष्ठा iwl_trans *trans)
अणु
	काष्ठा iwl_trans_pcie *trans_pcie = IWL_TRANS_GET_PCIE_TRANS(trans);

	lockdep_निश्चित_held(&trans_pcie->mutex);

	अगर (trans_pcie->is_करोwn)
		वापस;

	अगर (trans_pcie->fw_reset_handshake &&
	    trans->state >= IWL_TRANS_FW_STARTED)
		iwl_trans_pcie_fw_reset_handshake(trans);

	trans_pcie->is_करोwn = true;

	/* tell the device to stop sending पूर्णांकerrupts */
	iwl_disable_पूर्णांकerrupts(trans);

	/* device going करोwn, Stop using ICT table */
	iwl_pcie_disable_ict(trans);

	/*
	 * If a HW restart happens during firmware loading,
	 * then the firmware loading might call this function
	 * and later it might be called again due to the
	 * restart. So करोn't process again अगर the device is
	 * alपढ़ोy dead.
	 */
	अगर (test_and_clear_bit(STATUS_DEVICE_ENABLED, &trans->status)) अणु
		IWL_DEBUG_INFO(trans,
			       "DEVICE_ENABLED bit was set and is now cleared\n");
		iwl_txq_gen2_tx_मुक्त(trans);
		iwl_pcie_rx_stop(trans);
	पूर्ण

	iwl_pcie_ctxt_info_मुक्त_paging(trans);
	अगर (trans->trans_cfg->device_family >= IWL_DEVICE_FAMILY_AX210)
		iwl_pcie_ctxt_info_gen3_मुक्त(trans);
	अन्यथा
		iwl_pcie_ctxt_info_मुक्त(trans);

	/* Make sure (redundant) we've released our request to stay awake */
	iwl_clear_bit(trans, CSR_GP_CNTRL,
		      CSR_GP_CNTRL_REG_FLAG_MAC_ACCESS_REQ);

	/* Stop the device, and put it in low घातer state */
	iwl_pcie_gen2_apm_stop(trans, false);

	iwl_trans_sw_reset(trans);

	/*
	 * Upon stop, the IVAR table माला_लो erased, so msi-x won't
	 * work. This causes a bug in RF-KILL flows, since the पूर्णांकerrupt
	 * that enables radio won't fire on the correct irq, and the
	 * driver won't be able to handle the पूर्णांकerrupt.
	 * Configure the IVAR table again after reset.
	 */
	iwl_pcie_conf_msix_hw(trans_pcie);

	/*
	 * Upon stop, the APM issues an पूर्णांकerrupt अगर HW RF समाप्त is set.
	 * This is a bug in certain verions of the hardware.
	 * Certain devices also keep sending HW RF समाप्त पूर्णांकerrupt all
	 * the समय, unless the पूर्णांकerrupt is ACKed even अगर the पूर्णांकerrupt
	 * should be masked. Re-ACK all the पूर्णांकerrupts here.
	 */
	iwl_disable_पूर्णांकerrupts(trans);

	/* clear all status bits */
	clear_bit(STATUS_SYNC_HCMD_ACTIVE, &trans->status);
	clear_bit(STATUS_INT_ENABLED, &trans->status);
	clear_bit(STATUS_TPOWER_PMI, &trans->status);

	/*
	 * Even अगर we stop the HW, we still want the RF समाप्त
	 * पूर्णांकerrupt
	 */
	iwl_enable_rfसमाप्त_पूर्णांक(trans);

	/* re-take ownership to prevent other users from stealing the device */
	iwl_pcie_prepare_card_hw(trans);
पूर्ण

व्योम iwl_trans_pcie_gen2_stop_device(काष्ठा iwl_trans *trans)
अणु
	काष्ठा iwl_trans_pcie *trans_pcie = IWL_TRANS_GET_PCIE_TRANS(trans);
	bool was_in_rfसमाप्त;

	iwl_op_mode_समय_poपूर्णांक(trans->op_mode,
			       IWL_FW_INI_TIME_POINT_HOST_DEVICE_DISABLE,
			       शून्य);

	mutex_lock(&trans_pcie->mutex);
	trans_pcie->opmode_करोwn = true;
	was_in_rfसमाप्त = test_bit(STATUS_RFKILL_OPMODE, &trans->status);
	_iwl_trans_pcie_gen2_stop_device(trans);
	iwl_trans_pcie_handle_stop_rfसमाप्त(trans, was_in_rfसमाप्त);
	mutex_unlock(&trans_pcie->mutex);
पूर्ण

अटल पूर्णांक iwl_pcie_gen2_nic_init(काष्ठा iwl_trans *trans)
अणु
	काष्ठा iwl_trans_pcie *trans_pcie = IWL_TRANS_GET_PCIE_TRANS(trans);
	पूर्णांक queue_size = max_t(u32, IWL_CMD_QUEUE_SIZE,
			       trans->cfg->min_txq_size);

	/* TODO: most of the logic can be हटाओd in A0 - but not in Z0 */
	spin_lock_bh(&trans_pcie->irq_lock);
	iwl_pcie_gen2_apm_init(trans);
	spin_unlock_bh(&trans_pcie->irq_lock);

	iwl_op_mode_nic_config(trans->op_mode);

	/* Allocate the RX queue, or reset अगर it is alपढ़ोy allocated */
	अगर (iwl_pcie_gen2_rx_init(trans))
		वापस -ENOMEM;

	/* Allocate or reset and init all Tx and Command queues */
	अगर (iwl_txq_gen2_init(trans, trans->txqs.cmd.q_id, queue_size))
		वापस -ENOMEM;

	/* enable shaकरोw regs in HW */
	iwl_set_bit(trans, CSR_MAC_SHADOW_REG_CTRL, 0x800FFFFF);
	IWL_DEBUG_INFO(trans, "Enabling shadow registers in device\n");

	वापस 0;
पूर्ण

व्योम iwl_trans_pcie_gen2_fw_alive(काष्ठा iwl_trans *trans, u32 scd_addr)
अणु
	काष्ठा iwl_trans_pcie *trans_pcie = IWL_TRANS_GET_PCIE_TRANS(trans);

	iwl_pcie_reset_ict(trans);

	/* make sure all queue are not stopped/used */
	स_रखो(trans->txqs.queue_stopped, 0,
	       माप(trans->txqs.queue_stopped));
	स_रखो(trans->txqs.queue_used, 0, माप(trans->txqs.queue_used));

	/* now that we got alive we can मुक्त the fw image & the context info.
	 * paging memory cannot be मुक्तd included since FW will still use it
	 */
	iwl_pcie_ctxt_info_मुक्त(trans);

	/*
	 * Re-enable all the पूर्णांकerrupts, including the RF-Kill one, now that
	 * the firmware is alive.
	 */
	iwl_enable_पूर्णांकerrupts(trans);
	mutex_lock(&trans_pcie->mutex);
	iwl_pcie_check_hw_rf_समाप्त(trans);
	mutex_unlock(&trans_pcie->mutex);
पूर्ण

अटल व्योम iwl_pcie_set_ltr(काष्ठा iwl_trans *trans)
अणु
	u32 ltr_val = CSR_LTR_LONG_VAL_AD_NO_SNOOP_REQ |
		      u32_encode_bits(CSR_LTR_LONG_VAL_AD_SCALE_USEC,
				      CSR_LTR_LONG_VAL_AD_NO_SNOOP_SCALE) |
		      u32_encode_bits(250,
				      CSR_LTR_LONG_VAL_AD_NO_SNOOP_VAL) |
		      CSR_LTR_LONG_VAL_AD_SNOOP_REQ |
		      u32_encode_bits(CSR_LTR_LONG_VAL_AD_SCALE_USEC,
				      CSR_LTR_LONG_VAL_AD_SNOOP_SCALE) |
		      u32_encode_bits(250, CSR_LTR_LONG_VAL_AD_SNOOP_VAL);

	/*
	 * To workaround hardware latency issues during the boot process,
	 * initialize the LTR to ~250 usec (see ltr_val above).
	 * The firmware initializes this again later (to a smaller value).
	 */
	अगर ((trans->trans_cfg->device_family == IWL_DEVICE_FAMILY_AX210 ||
	     trans->trans_cfg->device_family == IWL_DEVICE_FAMILY_22000) &&
	    !trans->trans_cfg->पूर्णांकegrated) अणु
		iwl_ग_लिखो32(trans, CSR_LTR_LONG_VAL_AD, ltr_val);
	पूर्ण अन्यथा अगर (trans->trans_cfg->पूर्णांकegrated &&
		   trans->trans_cfg->device_family == IWL_DEVICE_FAMILY_22000) अणु
		iwl_ग_लिखो_prph(trans, HPM_MAC_LTR_CSR, HPM_MAC_LRT_ENABLE_ALL);
		iwl_ग_लिखो_prph(trans, HPM_UMAC_LTR, ltr_val);
	पूर्ण
पूर्ण

पूर्णांक iwl_trans_pcie_gen2_start_fw(काष्ठा iwl_trans *trans,
				 स्थिर काष्ठा fw_img *fw, bool run_in_rfसमाप्त)
अणु
	काष्ठा iwl_trans_pcie *trans_pcie = IWL_TRANS_GET_PCIE_TRANS(trans);
	bool hw_rfसमाप्त;
	पूर्णांक ret;

	/* This may fail अगर AMT took ownership of the device */
	अगर (iwl_pcie_prepare_card_hw(trans)) अणु
		IWL_WARN(trans, "Exit HW not ready\n");
		ret = -EIO;
		जाओ out;
	पूर्ण

	iwl_enable_rfसमाप्त_पूर्णांक(trans);

	iwl_ग_लिखो32(trans, CSR_INT, 0xFFFFFFFF);

	/*
	 * We enabled the RF-Kill पूर्णांकerrupt and the handler may very
	 * well be running. Disable the पूर्णांकerrupts to make sure no other
	 * पूर्णांकerrupt can be fired.
	 */
	iwl_disable_पूर्णांकerrupts(trans);

	/* Make sure it finished running */
	iwl_pcie_synchronize_irqs(trans);

	mutex_lock(&trans_pcie->mutex);

	/* If platक्रमm's RF_KILL चयन is NOT set to KILL */
	hw_rfसमाप्त = iwl_pcie_check_hw_rf_समाप्त(trans);
	अगर (hw_rfसमाप्त && !run_in_rfसमाप्त) अणु
		ret = -ERFKILL;
		जाओ out;
	पूर्ण

	/* Someone called stop_device, करोn't try to start_fw */
	अगर (trans_pcie->is_करोwn) अणु
		IWL_WARN(trans,
			 "Can't start_fw since the HW hasn't been started\n");
		ret = -EIO;
		जाओ out;
	पूर्ण

	/* make sure rfसमाप्त handshake bits are cleared */
	iwl_ग_लिखो32(trans, CSR_UCODE_DRV_GP1_CLR, CSR_UCODE_SW_BIT_RFKILL);
	iwl_ग_लिखो32(trans, CSR_UCODE_DRV_GP1_CLR,
		    CSR_UCODE_DRV_GP1_BIT_CMD_BLOCKED);

	/* clear (again), then enable host पूर्णांकerrupts */
	iwl_ग_लिखो32(trans, CSR_INT, 0xFFFFFFFF);

	ret = iwl_pcie_gen2_nic_init(trans);
	अगर (ret) अणु
		IWL_ERR(trans, "Unable to init nic\n");
		जाओ out;
	पूर्ण

	अगर (trans->trans_cfg->device_family >= IWL_DEVICE_FAMILY_AX210)
		ret = iwl_pcie_ctxt_info_gen3_init(trans, fw);
	अन्यथा
		ret = iwl_pcie_ctxt_info_init(trans, fw);
	अगर (ret)
		जाओ out;

	iwl_pcie_set_ltr(trans);

	अगर (trans->trans_cfg->device_family >= IWL_DEVICE_FAMILY_AX210)
		iwl_ग_लिखो_umac_prph(trans, UREG_CPU_INIT_RUN, 1);
	अन्यथा
		iwl_ग_लिखो_prph(trans, UREG_CPU_INIT_RUN, 1);

	/* re-check RF-Kill state since we may have missed the पूर्णांकerrupt */
	hw_rfसमाप्त = iwl_pcie_check_hw_rf_समाप्त(trans);
	अगर (hw_rfसमाप्त && !run_in_rfसमाप्त)
		ret = -ERFKILL;

out:
	mutex_unlock(&trans_pcie->mutex);
	वापस ret;
पूर्ण
