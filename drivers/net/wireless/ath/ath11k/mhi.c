<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause-Clear
/* Copyright (c) 2020 The Linux Foundation. All rights reserved. */

#समावेश <linux/msi.h>
#समावेश <linux/pci.h>

#समावेश "core.h"
#समावेश "debug.h"
#समावेश "mhi.h"
#समावेश "pci.h"

#घोषणा MHI_TIMEOUT_DEFAULT_MS	90000

अटल काष्ठा mhi_channel_config ath11k_mhi_channels_qca6390[] = अणु
	अणु
		.num = 0,
		.name = "LOOPBACK",
		.num_elements = 32,
		.event_ring = 0,
		.dir = DMA_TO_DEVICE,
		.ee_mask = 0x4,
		.pollcfg = 0,
		.करोorbell = MHI_DB_BRST_DISABLE,
		.lpm_notअगरy = false,
		.offload_channel = false,
		.करोorbell_mode_चयन = false,
		.स्वतः_queue = false,
	पूर्ण,
	अणु
		.num = 1,
		.name = "LOOPBACK",
		.num_elements = 32,
		.event_ring = 0,
		.dir = DMA_FROM_DEVICE,
		.ee_mask = 0x4,
		.pollcfg = 0,
		.करोorbell = MHI_DB_BRST_DISABLE,
		.lpm_notअगरy = false,
		.offload_channel = false,
		.करोorbell_mode_चयन = false,
		.स्वतः_queue = false,
	पूर्ण,
	अणु
		.num = 20,
		.name = "IPCR",
		.num_elements = 64,
		.event_ring = 1,
		.dir = DMA_TO_DEVICE,
		.ee_mask = 0x4,
		.pollcfg = 0,
		.करोorbell = MHI_DB_BRST_DISABLE,
		.lpm_notअगरy = false,
		.offload_channel = false,
		.करोorbell_mode_चयन = false,
		.स्वतः_queue = false,
	पूर्ण,
	अणु
		.num = 21,
		.name = "IPCR",
		.num_elements = 64,
		.event_ring = 1,
		.dir = DMA_FROM_DEVICE,
		.ee_mask = 0x4,
		.pollcfg = 0,
		.करोorbell = MHI_DB_BRST_DISABLE,
		.lpm_notअगरy = false,
		.offload_channel = false,
		.करोorbell_mode_चयन = false,
		.स्वतः_queue = true,
	पूर्ण,
पूर्ण;

अटल काष्ठा mhi_event_config ath11k_mhi_events_qca6390[] = अणु
	अणु
		.num_elements = 32,
		.irq_moderation_ms = 0,
		.irq = 1,
		.mode = MHI_DB_BRST_DISABLE,
		.data_type = MHI_ER_CTRL,
		.hardware_event = false,
		.client_managed = false,
		.offload_channel = false,
	पूर्ण,
	अणु
		.num_elements = 256,
		.irq_moderation_ms = 1,
		.irq = 2,
		.mode = MHI_DB_BRST_DISABLE,
		.priority = 1,
		.hardware_event = false,
		.client_managed = false,
		.offload_channel = false,
	पूर्ण,
पूर्ण;

अटल काष्ठा mhi_controller_config ath11k_mhi_config_qca6390 = अणु
	.max_channels = 128,
	.समयout_ms = 2000,
	.use_bounce_buf = false,
	.buf_len = 0,
	.num_channels = ARRAY_SIZE(ath11k_mhi_channels_qca6390),
	.ch_cfg = ath11k_mhi_channels_qca6390,
	.num_events = ARRAY_SIZE(ath11k_mhi_events_qca6390),
	.event_cfg = ath11k_mhi_events_qca6390,
पूर्ण;

अटल काष्ठा mhi_channel_config ath11k_mhi_channels_qcn9074[] = अणु
	अणु
		.num = 0,
		.name = "LOOPBACK",
		.num_elements = 32,
		.event_ring = 1,
		.dir = DMA_TO_DEVICE,
		.ee_mask = 0x14,
		.pollcfg = 0,
		.करोorbell = MHI_DB_BRST_DISABLE,
		.lpm_notअगरy = false,
		.offload_channel = false,
		.करोorbell_mode_चयन = false,
		.स्वतः_queue = false,
	पूर्ण,
	अणु
		.num = 1,
		.name = "LOOPBACK",
		.num_elements = 32,
		.event_ring = 1,
		.dir = DMA_FROM_DEVICE,
		.ee_mask = 0x14,
		.pollcfg = 0,
		.करोorbell = MHI_DB_BRST_DISABLE,
		.lpm_notअगरy = false,
		.offload_channel = false,
		.करोorbell_mode_चयन = false,
		.स्वतः_queue = false,
	पूर्ण,
	अणु
		.num = 20,
		.name = "IPCR",
		.num_elements = 32,
		.event_ring = 1,
		.dir = DMA_TO_DEVICE,
		.ee_mask = 0x14,
		.pollcfg = 0,
		.करोorbell = MHI_DB_BRST_DISABLE,
		.lpm_notअगरy = false,
		.offload_channel = false,
		.करोorbell_mode_चयन = false,
		.स्वतः_queue = false,
	पूर्ण,
	अणु
		.num = 21,
		.name = "IPCR",
		.num_elements = 32,
		.event_ring = 1,
		.dir = DMA_FROM_DEVICE,
		.ee_mask = 0x14,
		.pollcfg = 0,
		.करोorbell = MHI_DB_BRST_DISABLE,
		.lpm_notअगरy = false,
		.offload_channel = false,
		.करोorbell_mode_चयन = false,
		.स्वतः_queue = true,
	पूर्ण,
पूर्ण;

अटल काष्ठा mhi_event_config ath11k_mhi_events_qcn9074[] = अणु
	अणु
		.num_elements = 32,
		.irq_moderation_ms = 0,
		.irq = 1,
		.data_type = MHI_ER_CTRL,
		.mode = MHI_DB_BRST_DISABLE,
		.hardware_event = false,
		.client_managed = false,
		.offload_channel = false,
	पूर्ण,
	अणु
		.num_elements = 256,
		.irq_moderation_ms = 1,
		.irq = 2,
		.mode = MHI_DB_BRST_DISABLE,
		.priority = 1,
		.hardware_event = false,
		.client_managed = false,
		.offload_channel = false,
	पूर्ण,
पूर्ण;

अटल काष्ठा mhi_controller_config ath11k_mhi_config_qcn9074 = अणु
	.max_channels = 30,
	.समयout_ms = 10000,
	.use_bounce_buf = false,
	.buf_len = 0,
	.num_channels = ARRAY_SIZE(ath11k_mhi_channels_qcn9074),
	.ch_cfg = ath11k_mhi_channels_qcn9074,
	.num_events = ARRAY_SIZE(ath11k_mhi_events_qcn9074),
	.event_cfg = ath11k_mhi_events_qcn9074,
पूर्ण;

व्योम ath11k_mhi_set_mhictrl_reset(काष्ठा ath11k_base *ab)
अणु
	u32 val;

	val = ath11k_pci_पढ़ो32(ab, MHISTATUS);

	ath11k_dbg(ab, ATH11K_DBG_PCI, "MHISTATUS 0x%x\n", val);

	/* Observed on QCA6390 that after SOC_GLOBAL_RESET, MHISTATUS
	 * has SYSERR bit set and thus need to set MHICTRL_RESET
	 * to clear SYSERR.
	 */
	ath11k_pci_ग_लिखो32(ab, MHICTRL, MHICTRL_RESET_MASK);

	mdelay(10);
पूर्ण

अटल व्योम ath11k_mhi_reset_txvecdb(काष्ठा ath11k_base *ab)
अणु
	ath11k_pci_ग_लिखो32(ab, PCIE_TXVECDB, 0);
पूर्ण

अटल व्योम ath11k_mhi_reset_txvecstatus(काष्ठा ath11k_base *ab)
अणु
	ath11k_pci_ग_लिखो32(ab, PCIE_TXVECSTATUS, 0);
पूर्ण

अटल व्योम ath11k_mhi_reset_rxvecdb(काष्ठा ath11k_base *ab)
अणु
	ath11k_pci_ग_लिखो32(ab, PCIE_RXVECDB, 0);
पूर्ण

अटल व्योम ath11k_mhi_reset_rxvecstatus(काष्ठा ath11k_base *ab)
अणु
	ath11k_pci_ग_लिखो32(ab, PCIE_RXVECSTATUS, 0);
पूर्ण

व्योम ath11k_mhi_clear_vector(काष्ठा ath11k_base *ab)
अणु
	ath11k_mhi_reset_txvecdb(ab);
	ath11k_mhi_reset_txvecstatus(ab);
	ath11k_mhi_reset_rxvecdb(ab);
	ath11k_mhi_reset_rxvecstatus(ab);
पूर्ण

अटल पूर्णांक ath11k_mhi_get_msi(काष्ठा ath11k_pci *ab_pci)
अणु
	काष्ठा ath11k_base *ab = ab_pci->ab;
	u32 user_base_data, base_vector;
	पूर्णांक ret, num_vectors, i;
	पूर्णांक *irq;

	ret = ath11k_pci_get_user_msi_assignment(ab_pci,
						 "MHI", &num_vectors,
						 &user_base_data, &base_vector);
	अगर (ret)
		वापस ret;

	ath11k_dbg(ab, ATH11K_DBG_PCI, "Number of assigned MSI for MHI is %d, base vector is %d\n",
		   num_vectors, base_vector);

	irq = kसुस्मृति(num_vectors, माप(पूर्णांक), GFP_KERNEL);
	अगर (!irq)
		वापस -ENOMEM;

	क्रम (i = 0; i < num_vectors; i++)
		irq[i] = ath11k_pci_get_msi_irq(ab->dev,
						base_vector + i);

	ab_pci->mhi_ctrl->irq = irq;
	ab_pci->mhi_ctrl->nr_irqs = num_vectors;

	वापस 0;
पूर्ण

अटल पूर्णांक ath11k_mhi_op_runसमय_get(काष्ठा mhi_controller *mhi_cntrl)
अणु
	वापस 0;
पूर्ण

अटल व्योम ath11k_mhi_op_runसमय_put(काष्ठा mhi_controller *mhi_cntrl)
अणु
पूर्ण

अटल व्योम ath11k_mhi_op_status_cb(काष्ठा mhi_controller *mhi_cntrl,
				    क्रमागत mhi_callback cb)
अणु
	काष्ठा ath11k_base *ab = dev_get_drvdata(mhi_cntrl->cntrl_dev);

	चयन (cb) अणु
	हाल MHI_CB_SYS_ERROR:
		ath11k_warn(ab, "firmware crashed: MHI_CB_SYS_ERROR\n");
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक ath11k_mhi_op_पढ़ो_reg(काष्ठा mhi_controller *mhi_cntrl,
				  व्योम __iomem *addr,
				  u32 *out)
अणु
	*out = पढ़ोl(addr);

	वापस 0;
पूर्ण

अटल व्योम ath11k_mhi_op_ग_लिखो_reg(काष्ठा mhi_controller *mhi_cntrl,
				    व्योम __iomem *addr,
				    u32 val)
अणु
	ग_लिखोl(val, addr);
पूर्ण

पूर्णांक ath11k_mhi_रेजिस्टर(काष्ठा ath11k_pci *ab_pci)
अणु
	काष्ठा ath11k_base *ab = ab_pci->ab;
	काष्ठा mhi_controller *mhi_ctrl;
	काष्ठा mhi_controller_config *ath11k_mhi_config;
	पूर्णांक ret;

	mhi_ctrl = mhi_alloc_controller();
	अगर (!mhi_ctrl)
		वापस -ENOMEM;

	ath11k_core_create_firmware_path(ab, ATH11K_AMSS_खाता,
					 ab_pci->amss_path,
					 माप(ab_pci->amss_path));

	ab_pci->mhi_ctrl = mhi_ctrl;
	mhi_ctrl->cntrl_dev = ab->dev;
	mhi_ctrl->fw_image = ab_pci->amss_path;
	mhi_ctrl->regs = ab->mem;

	ret = ath11k_mhi_get_msi(ab_pci);
	अगर (ret) अणु
		ath11k_err(ab, "failed to get msi for mhi\n");
		mhi_मुक्त_controller(mhi_ctrl);
		वापस ret;
	पूर्ण

	mhi_ctrl->ioबहु_शुरू = 0;
	mhi_ctrl->iova_stop = 0xffffffff;
	mhi_ctrl->sbl_size = SZ_512K;
	mhi_ctrl->seg_len = SZ_512K;
	mhi_ctrl->fbc_करोwnload = true;
	mhi_ctrl->runसमय_get = ath11k_mhi_op_runसमय_get;
	mhi_ctrl->runसमय_put = ath11k_mhi_op_runसमय_put;
	mhi_ctrl->status_cb = ath11k_mhi_op_status_cb;
	mhi_ctrl->पढ़ो_reg = ath11k_mhi_op_पढ़ो_reg;
	mhi_ctrl->ग_लिखो_reg = ath11k_mhi_op_ग_लिखो_reg;

	चयन (ab->hw_rev) अणु
	हाल ATH11K_HW_QCN9074_HW10:
		ath11k_mhi_config = &ath11k_mhi_config_qcn9074;
		अवरोध;
	हाल ATH11K_HW_QCA6390_HW20:
		ath11k_mhi_config = &ath11k_mhi_config_qca6390;
		अवरोध;
	शेष:
		ath11k_err(ab, "failed assign mhi_config for unknown hw rev %d\n",
			   ab->hw_rev);
		mhi_मुक्त_controller(mhi_ctrl);
		वापस -EINVAL;
	पूर्ण

	ret = mhi_रेजिस्टर_controller(mhi_ctrl, ath11k_mhi_config);
	अगर (ret) अणु
		ath11k_err(ab, "failed to register to mhi bus, err = %d\n", ret);
		mhi_मुक्त_controller(mhi_ctrl);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

व्योम ath11k_mhi_unरेजिस्टर(काष्ठा ath11k_pci *ab_pci)
अणु
	काष्ठा mhi_controller *mhi_ctrl = ab_pci->mhi_ctrl;

	mhi_unरेजिस्टर_controller(mhi_ctrl);
	kमुक्त(mhi_ctrl->irq);
	mhi_मुक्त_controller(mhi_ctrl);
पूर्ण

अटल अक्षर *ath11k_mhi_state_to_str(क्रमागत ath11k_mhi_state mhi_state)
अणु
	चयन (mhi_state) अणु
	हाल ATH11K_MHI_INIT:
		वापस "INIT";
	हाल ATH11K_MHI_DEINIT:
		वापस "DEINIT";
	हाल ATH11K_MHI_POWER_ON:
		वापस "POWER_ON";
	हाल ATH11K_MHI_POWER_OFF:
		वापस "POWER_OFF";
	हाल ATH11K_MHI_FORCE_POWER_OFF:
		वापस "FORCE_POWER_OFF";
	हाल ATH11K_MHI_SUSPEND:
		वापस "SUSPEND";
	हाल ATH11K_MHI_RESUME:
		वापस "RESUME";
	हाल ATH11K_MHI_TRIGGER_RDDM:
		वापस "TRIGGER_RDDM";
	हाल ATH11K_MHI_RDDM_DONE:
		वापस "RDDM_DONE";
	शेष:
		वापस "UNKNOWN";
	पूर्ण
पूर्ण;

अटल व्योम ath11k_mhi_set_state_bit(काष्ठा ath11k_pci *ab_pci,
				     क्रमागत ath11k_mhi_state mhi_state)
अणु
	काष्ठा ath11k_base *ab = ab_pci->ab;

	चयन (mhi_state) अणु
	हाल ATH11K_MHI_INIT:
		set_bit(ATH11K_MHI_INIT, &ab_pci->mhi_state);
		अवरोध;
	हाल ATH11K_MHI_DEINIT:
		clear_bit(ATH11K_MHI_INIT, &ab_pci->mhi_state);
		अवरोध;
	हाल ATH11K_MHI_POWER_ON:
		set_bit(ATH11K_MHI_POWER_ON, &ab_pci->mhi_state);
		अवरोध;
	हाल ATH11K_MHI_POWER_OFF:
	हाल ATH11K_MHI_FORCE_POWER_OFF:
		clear_bit(ATH11K_MHI_POWER_ON, &ab_pci->mhi_state);
		clear_bit(ATH11K_MHI_TRIGGER_RDDM, &ab_pci->mhi_state);
		clear_bit(ATH11K_MHI_RDDM_DONE, &ab_pci->mhi_state);
		अवरोध;
	हाल ATH11K_MHI_SUSPEND:
		set_bit(ATH11K_MHI_SUSPEND, &ab_pci->mhi_state);
		अवरोध;
	हाल ATH11K_MHI_RESUME:
		clear_bit(ATH11K_MHI_SUSPEND, &ab_pci->mhi_state);
		अवरोध;
	हाल ATH11K_MHI_TRIGGER_RDDM:
		set_bit(ATH11K_MHI_TRIGGER_RDDM, &ab_pci->mhi_state);
		अवरोध;
	हाल ATH11K_MHI_RDDM_DONE:
		set_bit(ATH11K_MHI_RDDM_DONE, &ab_pci->mhi_state);
		अवरोध;
	शेष:
		ath11k_err(ab, "unhandled mhi state (%d)\n", mhi_state);
	पूर्ण
पूर्ण

अटल पूर्णांक ath11k_mhi_check_state_bit(काष्ठा ath11k_pci *ab_pci,
				      क्रमागत ath11k_mhi_state mhi_state)
अणु
	काष्ठा ath11k_base *ab = ab_pci->ab;

	चयन (mhi_state) अणु
	हाल ATH11K_MHI_INIT:
		अगर (!test_bit(ATH11K_MHI_INIT, &ab_pci->mhi_state))
			वापस 0;
		अवरोध;
	हाल ATH11K_MHI_DEINIT:
	हाल ATH11K_MHI_POWER_ON:
		अगर (test_bit(ATH11K_MHI_INIT, &ab_pci->mhi_state) &&
		    !test_bit(ATH11K_MHI_POWER_ON, &ab_pci->mhi_state))
			वापस 0;
		अवरोध;
	हाल ATH11K_MHI_FORCE_POWER_OFF:
		अगर (test_bit(ATH11K_MHI_POWER_ON, &ab_pci->mhi_state))
			वापस 0;
		अवरोध;
	हाल ATH11K_MHI_POWER_OFF:
	हाल ATH11K_MHI_SUSPEND:
		अगर (test_bit(ATH11K_MHI_POWER_ON, &ab_pci->mhi_state) &&
		    !test_bit(ATH11K_MHI_SUSPEND, &ab_pci->mhi_state))
			वापस 0;
		अवरोध;
	हाल ATH11K_MHI_RESUME:
		अगर (test_bit(ATH11K_MHI_SUSPEND, &ab_pci->mhi_state))
			वापस 0;
		अवरोध;
	हाल ATH11K_MHI_TRIGGER_RDDM:
		अगर (test_bit(ATH11K_MHI_POWER_ON, &ab_pci->mhi_state) &&
		    !test_bit(ATH11K_MHI_TRIGGER_RDDM, &ab_pci->mhi_state))
			वापस 0;
		अवरोध;
	हाल ATH11K_MHI_RDDM_DONE:
		वापस 0;
	शेष:
		ath11k_err(ab, "unhandled mhi state: %s(%d)\n",
			   ath11k_mhi_state_to_str(mhi_state), mhi_state);
	पूर्ण

	ath11k_err(ab, "failed to set mhi state %s(%d) in current mhi state (0x%lx)\n",
		   ath11k_mhi_state_to_str(mhi_state), mhi_state,
		   ab_pci->mhi_state);

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक ath11k_mhi_set_state(काष्ठा ath11k_pci *ab_pci,
				क्रमागत ath11k_mhi_state mhi_state)
अणु
	काष्ठा ath11k_base *ab = ab_pci->ab;
	पूर्णांक ret;

	ret = ath11k_mhi_check_state_bit(ab_pci, mhi_state);
	अगर (ret)
		जाओ out;

	ath11k_dbg(ab, ATH11K_DBG_PCI, "setting mhi state: %s(%d)\n",
		   ath11k_mhi_state_to_str(mhi_state), mhi_state);

	चयन (mhi_state) अणु
	हाल ATH11K_MHI_INIT:
		ret = mhi_prepare_क्रम_घातer_up(ab_pci->mhi_ctrl);
		अवरोध;
	हाल ATH11K_MHI_DEINIT:
		mhi_unprepare_after_घातer_करोwn(ab_pci->mhi_ctrl);
		ret = 0;
		अवरोध;
	हाल ATH11K_MHI_POWER_ON:
		ret = mhi_async_घातer_up(ab_pci->mhi_ctrl);
		अवरोध;
	हाल ATH11K_MHI_POWER_OFF:
		mhi_घातer_करोwn(ab_pci->mhi_ctrl, true);
		ret = 0;
		अवरोध;
	हाल ATH11K_MHI_FORCE_POWER_OFF:
		mhi_घातer_करोwn(ab_pci->mhi_ctrl, false);
		ret = 0;
		अवरोध;
	हाल ATH11K_MHI_SUSPEND:
		ret = mhi_pm_suspend(ab_pci->mhi_ctrl);
		अवरोध;
	हाल ATH11K_MHI_RESUME:
		ret = mhi_pm_resume(ab_pci->mhi_ctrl);
		अवरोध;
	हाल ATH11K_MHI_TRIGGER_RDDM:
		ret = mhi_क्रमce_rddm_mode(ab_pci->mhi_ctrl);
		अवरोध;
	हाल ATH11K_MHI_RDDM_DONE:
		अवरोध;
	शेष:
		ath11k_err(ab, "unhandled MHI state (%d)\n", mhi_state);
		ret = -EINVAL;
	पूर्ण

	अगर (ret)
		जाओ out;

	ath11k_mhi_set_state_bit(ab_pci, mhi_state);

	वापस 0;

out:
	ath11k_err(ab, "failed to set mhi state: %s(%d)\n",
		   ath11k_mhi_state_to_str(mhi_state), mhi_state);
	वापस ret;
पूर्ण

पूर्णांक ath11k_mhi_start(काष्ठा ath11k_pci *ab_pci)
अणु
	पूर्णांक ret;

	ab_pci->mhi_ctrl->समयout_ms = MHI_TIMEOUT_DEFAULT_MS;

	ret = ath11k_mhi_set_state(ab_pci, ATH11K_MHI_INIT);
	अगर (ret)
		जाओ out;

	ret = ath11k_mhi_set_state(ab_pci, ATH11K_MHI_POWER_ON);
	अगर (ret)
		जाओ out;

	वापस 0;

out:
	वापस ret;
पूर्ण

व्योम ath11k_mhi_stop(काष्ठा ath11k_pci *ab_pci)
अणु
	ath11k_mhi_set_state(ab_pci, ATH11K_MHI_POWER_OFF);
	ath11k_mhi_set_state(ab_pci, ATH11K_MHI_DEINIT);
पूर्ण

व्योम ath11k_mhi_suspend(काष्ठा ath11k_pci *ab_pci)
अणु
	ath11k_mhi_set_state(ab_pci, ATH11K_MHI_SUSPEND);
पूर्ण

व्योम ath11k_mhi_resume(काष्ठा ath11k_pci *ab_pci)
अणु
	ath11k_mhi_set_state(ab_pci, ATH11K_MHI_RESUME);
पूर्ण
