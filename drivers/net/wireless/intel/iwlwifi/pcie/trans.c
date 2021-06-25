<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause
/*
 * Copyright (C) 2007-2015, 2018-2020 Intel Corporation
 * Copyright (C) 2013-2015 Intel Mobile Communications GmbH
 * Copyright (C) 2016-2017 Intel Deutschland GmbH
 */
#समावेश <linux/pci.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/sched.h>
#समावेश <linux/bitops.h>
#समावेश <linux/gfp.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/module.h>
#समावेश <linux/रुको.h>
#समावेश <linux/seq_file.h>

#समावेश "iwl-drv.h"
#समावेश "iwl-trans.h"
#समावेश "iwl-csr.h"
#समावेश "iwl-prph.h"
#समावेश "iwl-scd.h"
#समावेश "iwl-agn-hw.h"
#समावेश "fw/error-dump.h"
#समावेश "fw/dbg.h"
#समावेश "fw/api/tx.h"
#समावेश "internal.h"
#समावेश "iwl-fh.h"
#समावेश "iwl-context-info-gen3.h"

/* extended range in FW SRAM */
#घोषणा IWL_FW_MEM_EXTENDED_START	0x40000
#घोषणा IWL_FW_MEM_EXTENDED_END		0x57FFF

व्योम iwl_trans_pcie_dump_regs(काष्ठा iwl_trans *trans)
अणु
#घोषणा PCI_DUMP_SIZE		352
#घोषणा PCI_MEM_DUMP_SIZE	64
#घोषणा PCI_PARENT_DUMP_SIZE	524
#घोषणा PREFIX_LEN		32
	काष्ठा iwl_trans_pcie *trans_pcie = IWL_TRANS_GET_PCIE_TRANS(trans);
	काष्ठा pci_dev *pdev = trans_pcie->pci_dev;
	u32 i, pos, alloc_size, *ptr, *buf;
	अक्षर *prefix;

	अगर (trans_pcie->pcie_dbg_dumped_once)
		वापस;

	/* Should be a multiple of 4 */
	BUILD_BUG_ON(PCI_DUMP_SIZE > 4096 || PCI_DUMP_SIZE & 0x3);
	BUILD_BUG_ON(PCI_MEM_DUMP_SIZE > 4096 || PCI_MEM_DUMP_SIZE & 0x3);
	BUILD_BUG_ON(PCI_PARENT_DUMP_SIZE > 4096 || PCI_PARENT_DUMP_SIZE & 0x3);

	/* Alloc a max size buffer */
	alloc_size = PCI_ERR_ROOT_ERR_SRC +  4 + PREFIX_LEN;
	alloc_size = max_t(u32, alloc_size, PCI_DUMP_SIZE + PREFIX_LEN);
	alloc_size = max_t(u32, alloc_size, PCI_MEM_DUMP_SIZE + PREFIX_LEN);
	alloc_size = max_t(u32, alloc_size, PCI_PARENT_DUMP_SIZE + PREFIX_LEN);

	buf = kदो_स्मृति(alloc_size, GFP_ATOMIC);
	अगर (!buf)
		वापस;
	prefix = (अक्षर *)buf + alloc_size - PREFIX_LEN;

	IWL_ERR(trans, "iwlwifi transaction failed, dumping registers\n");

	/* Prपूर्णांक wअगरi device रेजिस्टरs */
	प्र_लिखो(prefix, "iwlwifi %s: ", pci_name(pdev));
	IWL_ERR(trans, "iwlwifi device config registers:\n");
	क्रम (i = 0, ptr = buf; i < PCI_DUMP_SIZE; i += 4, ptr++)
		अगर (pci_पढ़ो_config_dword(pdev, i, ptr))
			जाओ err_पढ़ो;
	prपूर्णांक_hex_dump(KERN_ERR, prefix, DUMP_PREFIX_OFFSET, 32, 4, buf, i, 0);

	IWL_ERR(trans, "iwlwifi device memory mapped registers:\n");
	क्रम (i = 0, ptr = buf; i < PCI_MEM_DUMP_SIZE; i += 4, ptr++)
		*ptr = iwl_पढ़ो32(trans, i);
	prपूर्णांक_hex_dump(KERN_ERR, prefix, DUMP_PREFIX_OFFSET, 32, 4, buf, i, 0);

	pos = pci_find_ext_capability(pdev, PCI_EXT_CAP_ID_ERR);
	अगर (pos) अणु
		IWL_ERR(trans, "iwlwifi device AER capability structure:\n");
		क्रम (i = 0, ptr = buf; i < PCI_ERR_ROOT_COMMAND; i += 4, ptr++)
			अगर (pci_पढ़ो_config_dword(pdev, pos + i, ptr))
				जाओ err_पढ़ो;
		prपूर्णांक_hex_dump(KERN_ERR, prefix, DUMP_PREFIX_OFFSET,
			       32, 4, buf, i, 0);
	पूर्ण

	/* Prपूर्णांक parent device रेजिस्टरs next */
	अगर (!pdev->bus->self)
		जाओ out;

	pdev = pdev->bus->self;
	प्र_लिखो(prefix, "iwlwifi %s: ", pci_name(pdev));

	IWL_ERR(trans, "iwlwifi parent port (%s) config registers:\n",
		pci_name(pdev));
	क्रम (i = 0, ptr = buf; i < PCI_PARENT_DUMP_SIZE; i += 4, ptr++)
		अगर (pci_पढ़ो_config_dword(pdev, i, ptr))
			जाओ err_पढ़ो;
	prपूर्णांक_hex_dump(KERN_ERR, prefix, DUMP_PREFIX_OFFSET, 32, 4, buf, i, 0);

	/* Prपूर्णांक root port AER रेजिस्टरs */
	pos = 0;
	pdev = pcie_find_root_port(pdev);
	अगर (pdev)
		pos = pci_find_ext_capability(pdev, PCI_EXT_CAP_ID_ERR);
	अगर (pos) अणु
		IWL_ERR(trans, "iwlwifi root port (%s) AER cap structure:\n",
			pci_name(pdev));
		प्र_लिखो(prefix, "iwlwifi %s: ", pci_name(pdev));
		क्रम (i = 0, ptr = buf; i <= PCI_ERR_ROOT_ERR_SRC; i += 4, ptr++)
			अगर (pci_पढ़ो_config_dword(pdev, pos + i, ptr))
				जाओ err_पढ़ो;
		prपूर्णांक_hex_dump(KERN_ERR, prefix, DUMP_PREFIX_OFFSET, 32,
			       4, buf, i, 0);
	पूर्ण
	जाओ out;

err_पढ़ो:
	prपूर्णांक_hex_dump(KERN_ERR, prefix, DUMP_PREFIX_OFFSET, 32, 4, buf, i, 0);
	IWL_ERR(trans, "Read failed at 0x%X\n", i);
out:
	trans_pcie->pcie_dbg_dumped_once = 1;
	kमुक्त(buf);
पूर्ण

अटल व्योम iwl_trans_pcie_sw_reset(काष्ठा iwl_trans *trans)
अणु
	/* Reset entire device - करो controller reset (results in SHRD_HW_RST) */
	iwl_set_bit(trans, CSR_RESET, CSR_RESET_REG_FLAG_SW_RESET);
	usleep_range(5000, 6000);
पूर्ण

अटल व्योम iwl_pcie_मुक्त_fw_monitor(काष्ठा iwl_trans *trans)
अणु
	काष्ठा iwl_dram_data *fw_mon = &trans->dbg.fw_mon;

	अगर (!fw_mon->size)
		वापस;

	dma_मुक्त_coherent(trans->dev, fw_mon->size, fw_mon->block,
			  fw_mon->physical);

	fw_mon->block = शून्य;
	fw_mon->physical = 0;
	fw_mon->size = 0;
पूर्ण

अटल व्योम iwl_pcie_alloc_fw_monitor_block(काष्ठा iwl_trans *trans,
					    u8 max_घातer, u8 min_घातer)
अणु
	काष्ठा iwl_dram_data *fw_mon = &trans->dbg.fw_mon;
	व्योम *block = शून्य;
	dma_addr_t physical = 0;
	u32 size = 0;
	u8 घातer;

	अगर (fw_mon->size)
		वापस;

	क्रम (घातer = max_घातer; घातer >= min_घातer; घातer--) अणु
		size = BIT(घातer);
		block = dma_alloc_coherent(trans->dev, size, &physical,
					   GFP_KERNEL | __GFP_NOWARN);
		अगर (!block)
			जारी;

		IWL_INFO(trans,
			 "Allocated 0x%08x bytes for firmware monitor.\n",
			 size);
		अवरोध;
	पूर्ण

	अगर (WARN_ON_ONCE(!block))
		वापस;

	अगर (घातer != max_घातer)
		IWL_ERR(trans,
			"Sorry - debug buffer is only %luK while you requested %luK\n",
			(अचिन्हित दीर्घ)BIT(घातer - 10),
			(अचिन्हित दीर्घ)BIT(max_घातer - 10));

	fw_mon->block = block;
	fw_mon->physical = physical;
	fw_mon->size = size;
पूर्ण

व्योम iwl_pcie_alloc_fw_monitor(काष्ठा iwl_trans *trans, u8 max_घातer)
अणु
	अगर (!max_घातer) अणु
		/* शेष max_घातer is maximum */
		max_घातer = 26;
	पूर्ण अन्यथा अणु
		max_घातer += 11;
	पूर्ण

	अगर (WARN(max_घातer > 26,
		 "External buffer size for monitor is too big %d, check the FW TLV\n",
		 max_घातer))
		वापस;

	अगर (trans->dbg.fw_mon.size)
		वापस;

	iwl_pcie_alloc_fw_monitor_block(trans, max_घातer, 11);
पूर्ण

अटल u32 iwl_trans_pcie_पढ़ो_shr(काष्ठा iwl_trans *trans, u32 reg)
अणु
	iwl_ग_लिखो32(trans, HEEP_CTRL_WRD_PCIEX_CTRL_REG,
		    ((reg & 0x0000ffff) | (2 << 28)));
	वापस iwl_पढ़ो32(trans, HEEP_CTRL_WRD_PCIEX_DATA_REG);
पूर्ण

अटल व्योम iwl_trans_pcie_ग_लिखो_shr(काष्ठा iwl_trans *trans, u32 reg, u32 val)
अणु
	iwl_ग_लिखो32(trans, HEEP_CTRL_WRD_PCIEX_DATA_REG, val);
	iwl_ग_लिखो32(trans, HEEP_CTRL_WRD_PCIEX_CTRL_REG,
		    ((reg & 0x0000ffff) | (3 << 28)));
पूर्ण

अटल व्योम iwl_pcie_set_pwr(काष्ठा iwl_trans *trans, bool vaux)
अणु
	अगर (trans->cfg->apmg_not_supported)
		वापस;

	अगर (vaux && pci_pme_capable(to_pci_dev(trans->dev), PCI_D3cold))
		iwl_set_bits_mask_prph(trans, APMG_PS_CTRL_REG,
				       APMG_PS_CTRL_VAL_PWR_SRC_VAUX,
				       ~APMG_PS_CTRL_MSK_PWR_SRC);
	अन्यथा
		iwl_set_bits_mask_prph(trans, APMG_PS_CTRL_REG,
				       APMG_PS_CTRL_VAL_PWR_SRC_VMAIN,
				       ~APMG_PS_CTRL_MSK_PWR_SRC);
पूर्ण

/* PCI रेजिस्टरs */
#घोषणा PCI_CFG_RETRY_TIMEOUT	0x041

व्योम iwl_pcie_apm_config(काष्ठा iwl_trans *trans)
अणु
	काष्ठा iwl_trans_pcie *trans_pcie = IWL_TRANS_GET_PCIE_TRANS(trans);
	u16 lctl;
	u16 cap;

	/*
	 * L0S states have been found to be unstable with our devices
	 * and in newer hardware they are not officially supported at
	 * all, so we must always set the L0S_DISABLED bit.
	 */
	iwl_set_bit(trans, CSR_GIO_REG, CSR_GIO_REG_VAL_L0S_DISABLED);

	pcie_capability_पढ़ो_word(trans_pcie->pci_dev, PCI_EXP_LNKCTL, &lctl);
	trans->pm_support = !(lctl & PCI_EXP_LNKCTL_ASPM_L0S);

	pcie_capability_पढ़ो_word(trans_pcie->pci_dev, PCI_EXP_DEVCTL2, &cap);
	trans->ltr_enabled = cap & PCI_EXP_DEVCTL2_LTR_EN;
	IWL_DEBUG_POWER(trans, "L1 %sabled - LTR %sabled\n",
			(lctl & PCI_EXP_LNKCTL_ASPM_L1) ? "En" : "Dis",
			trans->ltr_enabled ? "En" : "Dis");
पूर्ण

/*
 * Start up NIC's basic functionality after it has been reset
 * (e.g. after platक्रमm boot, or shutकरोwn via iwl_pcie_apm_stop())
 * NOTE:  This करोes not load uCode nor start the embedded processor
 */
अटल पूर्णांक iwl_pcie_apm_init(काष्ठा iwl_trans *trans)
अणु
	पूर्णांक ret;

	IWL_DEBUG_INFO(trans, "Init card's basic functions\n");

	/*
	 * Use "set_bit" below rather than "write", to preserve any hardware
	 * bits alपढ़ोy set by शेष after reset.
	 */

	/* Disable L0S निकास समयr (platक्रमm NMI Work/Around) */
	अगर (trans->trans_cfg->device_family < IWL_DEVICE_FAMILY_8000)
		iwl_set_bit(trans, CSR_GIO_CHICKEN_BITS,
			    CSR_GIO_CHICKEN_BITS_REG_BIT_DIS_L0S_EXIT_TIMER);

	/*
	 * Disable L0s without affecting L1;
	 *  करोn't रुको क्रम ICH L0s (ICH bug W/A)
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

	/* Configure analog phase-lock-loop beक्रमe activating to D0A */
	अगर (trans->trans_cfg->base_params->pll_cfg)
		iwl_set_bit(trans, CSR_ANA_PLL_CFG, CSR50_ANA_PLL_CFG_VAL);

	ret = iwl_finish_nic_init(trans, trans->trans_cfg);
	अगर (ret)
		वापस ret;

	अगर (trans->cfg->host_पूर्णांकerrupt_operation_mode) अणु
		/*
		 * This is a bit of an abuse - This is needed क्रम 7260 / 3160
		 * only check host_पूर्णांकerrupt_operation_mode even अगर this is
		 * not related to host_पूर्णांकerrupt_operation_mode.
		 *
		 * Enable the oscillator to count wake up समय क्रम L1 निकास. This
		 * consumes slightly more घातer (100uA) - but allows to be sure
		 * that we wake up from L1 on समय.
		 *
		 * This looks weird: पढ़ो twice the same रेजिस्टर, discard the
		 * value, set a bit, and yet again, पढ़ो that same रेजिस्टर
		 * just to discard the value. But that's the way the hardware
		 * seems to like it.
		 */
		iwl_पढ़ो_prph(trans, OSC_CLK);
		iwl_पढ़ो_prph(trans, OSC_CLK);
		iwl_set_bits_prph(trans, OSC_CLK, OSC_CLK_FORCE_CONTROL);
		iwl_पढ़ो_prph(trans, OSC_CLK);
		iwl_पढ़ो_prph(trans, OSC_CLK);
	पूर्ण

	/*
	 * Enable DMA घड़ी and रुको क्रम it to stabilize.
	 *
	 * Write to "CLK_EN_REG"; "1" bits enable घड़ीs, जबतक "0"
	 * bits करो not disable घड़ीs.  This preserves any hardware
	 * bits alपढ़ोy set by शेष in "CLK_CTRL_REG" after reset.
	 */
	अगर (!trans->cfg->apmg_not_supported) अणु
		iwl_ग_लिखो_prph(trans, APMG_CLK_EN_REG,
			       APMG_CLK_VAL_DMA_CLK_RQT);
		udelay(20);

		/* Disable L1-Active */
		iwl_set_bits_prph(trans, APMG_PCIDEV_STT_REG,
				  APMG_PCIDEV_STT_VAL_L1_ACT_DIS);

		/* Clear the पूर्णांकerrupt in APMG अगर the NIC is in RFKILL */
		iwl_ग_लिखो_prph(trans, APMG_RTC_INT_STT_REG,
			       APMG_RTC_INT_STT_RFKILL);
	पूर्ण

	set_bit(STATUS_DEVICE_ENABLED, &trans->status);

	वापस 0;
पूर्ण

/*
 * Enable LP XTAL to aव्योम HW bug where device may consume much घातer अगर
 * FW is not loaded after device reset. LP XTAL is disabled by शेष
 * after device HW reset. Do it only अगर XTAL is fed by पूर्णांकernal source.
 * Configure device's "persistence" mode to aव्योम resetting XTAL again when
 * SHRD_HW_RST occurs in S3.
 */
अटल व्योम iwl_pcie_apm_lp_xtal_enable(काष्ठा iwl_trans *trans)
अणु
	पूर्णांक ret;
	u32 apmg_gp1_reg;
	u32 apmg_xtal_cfg_reg;
	u32 dl_cfg_reg;

	/* Force XTAL ON */
	__iwl_trans_pcie_set_bit(trans, CSR_GP_CNTRL,
				 CSR_GP_CNTRL_REG_FLAG_XTAL_ON);

	iwl_trans_pcie_sw_reset(trans);

	ret = iwl_finish_nic_init(trans, trans->trans_cfg);
	अगर (WARN_ON(ret)) अणु
		/* Release XTAL ON request */
		__iwl_trans_pcie_clear_bit(trans, CSR_GP_CNTRL,
					   CSR_GP_CNTRL_REG_FLAG_XTAL_ON);
		वापस;
	पूर्ण

	/*
	 * Clear "disable persistence" to aव्योम LP XTAL resetting when
	 * SHRD_HW_RST is applied in S3.
	 */
	iwl_clear_bits_prph(trans, APMG_PCIDEV_STT_REG,
				    APMG_PCIDEV_STT_VAL_PERSIST_DIS);

	/*
	 * Force APMG XTAL to be active to prevent its disabling by HW
	 * caused by APMG idle state.
	 */
	apmg_xtal_cfg_reg = iwl_trans_pcie_पढ़ो_shr(trans,
						    SHR_APMG_XTAL_CFG_REG);
	iwl_trans_pcie_ग_लिखो_shr(trans, SHR_APMG_XTAL_CFG_REG,
				 apmg_xtal_cfg_reg |
				 SHR_APMG_XTAL_CFG_XTAL_ON_REQ);

	iwl_trans_pcie_sw_reset(trans);

	/* Enable LP XTAL by indirect access through CSR */
	apmg_gp1_reg = iwl_trans_pcie_पढ़ो_shr(trans, SHR_APMG_GP1_REG);
	iwl_trans_pcie_ग_लिखो_shr(trans, SHR_APMG_GP1_REG, apmg_gp1_reg |
				 SHR_APMG_GP1_WF_XTAL_LP_EN |
				 SHR_APMG_GP1_CHICKEN_BIT_SELECT);

	/* Clear delay line घड़ी घातer up */
	dl_cfg_reg = iwl_trans_pcie_पढ़ो_shr(trans, SHR_APMG_DL_CFG_REG);
	iwl_trans_pcie_ग_लिखो_shr(trans, SHR_APMG_DL_CFG_REG, dl_cfg_reg &
				 ~SHR_APMG_DL_CFG_DL_CLOCK_POWER_UP);

	/*
	 * Enable persistence mode to aव्योम LP XTAL resetting when
	 * SHRD_HW_RST is applied in S3.
	 */
	iwl_set_bit(trans, CSR_HW_IF_CONFIG_REG,
		    CSR_HW_IF_CONFIG_REG_PERSIST_MODE);

	/*
	 * Clear "initialization complete" bit to move adapter from
	 * D0A* (घातered-up Active) --> D0U* (Uninitialized) state.
	 */
	iwl_clear_bit(trans, CSR_GP_CNTRL, CSR_GP_CNTRL_REG_FLAG_INIT_DONE);

	/* Activates XTAL resources monitor */
	__iwl_trans_pcie_set_bit(trans, CSR_MONITOR_CFG_REG,
				 CSR_MONITOR_XTAL_RESOURCES);

	/* Release XTAL ON request */
	__iwl_trans_pcie_clear_bit(trans, CSR_GP_CNTRL,
				   CSR_GP_CNTRL_REG_FLAG_XTAL_ON);
	udelay(10);

	/* Release APMG XTAL */
	iwl_trans_pcie_ग_लिखो_shr(trans, SHR_APMG_XTAL_CFG_REG,
				 apmg_xtal_cfg_reg &
				 ~SHR_APMG_XTAL_CFG_XTAL_ON_REQ);
पूर्ण

व्योम iwl_pcie_apm_stop_master(काष्ठा iwl_trans *trans)
अणु
	पूर्णांक ret;

	/* stop device's busmaster DMA activity */
	iwl_set_bit(trans, CSR_RESET, CSR_RESET_REG_FLAG_STOP_MASTER);

	ret = iwl_poll_bit(trans, CSR_RESET,
			   CSR_RESET_REG_FLAG_MASTER_DISABLED,
			   CSR_RESET_REG_FLAG_MASTER_DISABLED, 100);
	अगर (ret < 0)
		IWL_WARN(trans, "Master Disable Timed Out, 100 usec\n");

	IWL_DEBUG_INFO(trans, "stop master\n");
पूर्ण

अटल व्योम iwl_pcie_apm_stop(काष्ठा iwl_trans *trans, bool op_mode_leave)
अणु
	IWL_DEBUG_INFO(trans, "Stop card, put in low power state\n");

	अगर (op_mode_leave) अणु
		अगर (!test_bit(STATUS_DEVICE_ENABLED, &trans->status))
			iwl_pcie_apm_init(trans);

		/* inक्रमm ME that we are leaving */
		अगर (trans->trans_cfg->device_family == IWL_DEVICE_FAMILY_7000)
			iwl_set_bits_prph(trans, APMG_PCIDEV_STT_REG,
					  APMG_PCIDEV_STT_VAL_WAKE_ME);
		अन्यथा अगर (trans->trans_cfg->device_family >=
			 IWL_DEVICE_FAMILY_8000) अणु
			iwl_set_bit(trans, CSR_DBG_LINK_PWR_MGMT_REG,
				    CSR_RESET_LINK_PWR_MGMT_DISABLED);
			iwl_set_bit(trans, CSR_HW_IF_CONFIG_REG,
				    CSR_HW_IF_CONFIG_REG_PREPARE |
				    CSR_HW_IF_CONFIG_REG_ENABLE_PME);
			mdelay(1);
			iwl_clear_bit(trans, CSR_DBG_LINK_PWR_MGMT_REG,
				      CSR_RESET_LINK_PWR_MGMT_DISABLED);
		पूर्ण
		mdelay(5);
	पूर्ण

	clear_bit(STATUS_DEVICE_ENABLED, &trans->status);

	/* Stop device's DMA activity */
	iwl_pcie_apm_stop_master(trans);

	अगर (trans->cfg->lp_xtal_workaround) अणु
		iwl_pcie_apm_lp_xtal_enable(trans);
		वापस;
	पूर्ण

	iwl_trans_pcie_sw_reset(trans);

	/*
	 * Clear "initialization complete" bit to move adapter from
	 * D0A* (घातered-up Active) --> D0U* (Uninitialized) state.
	 */
	iwl_clear_bit(trans, CSR_GP_CNTRL, CSR_GP_CNTRL_REG_FLAG_INIT_DONE);
पूर्ण

अटल पूर्णांक iwl_pcie_nic_init(काष्ठा iwl_trans *trans)
अणु
	काष्ठा iwl_trans_pcie *trans_pcie = IWL_TRANS_GET_PCIE_TRANS(trans);
	पूर्णांक ret;

	/* nic_init */
	spin_lock_bh(&trans_pcie->irq_lock);
	ret = iwl_pcie_apm_init(trans);
	spin_unlock_bh(&trans_pcie->irq_lock);

	अगर (ret)
		वापस ret;

	iwl_pcie_set_pwr(trans, false);

	iwl_op_mode_nic_config(trans->op_mode);

	/* Allocate the RX queue, or reset अगर it is alपढ़ोy allocated */
	ret = iwl_pcie_rx_init(trans);
	अगर (ret)
		वापस ret;

	/* Allocate or reset and init all Tx and Command queues */
	अगर (iwl_pcie_tx_init(trans)) अणु
		iwl_pcie_rx_मुक्त(trans);
		वापस -ENOMEM;
	पूर्ण

	अगर (trans->trans_cfg->base_params->shaकरोw_reg_enable) अणु
		/* enable shaकरोw regs in HW */
		iwl_set_bit(trans, CSR_MAC_SHADOW_REG_CTRL, 0x800FFFFF);
		IWL_DEBUG_INFO(trans, "Enabling shadow registers in device\n");
	पूर्ण

	वापस 0;
पूर्ण

#घोषणा HW_READY_TIMEOUT (50)

/* Note: वापसs poll_bit वापस value, which is >= 0 अगर success */
अटल पूर्णांक iwl_pcie_set_hw_पढ़ोy(काष्ठा iwl_trans *trans)
अणु
	पूर्णांक ret;

	iwl_set_bit(trans, CSR_HW_IF_CONFIG_REG,
		    CSR_HW_IF_CONFIG_REG_BIT_NIC_READY);

	/* See अगर we got it */
	ret = iwl_poll_bit(trans, CSR_HW_IF_CONFIG_REG,
			   CSR_HW_IF_CONFIG_REG_BIT_NIC_READY,
			   CSR_HW_IF_CONFIG_REG_BIT_NIC_READY,
			   HW_READY_TIMEOUT);

	अगर (ret >= 0)
		iwl_set_bit(trans, CSR_MBOX_SET_REG, CSR_MBOX_SET_REG_OS_ALIVE);

	IWL_DEBUG_INFO(trans, "hardware%s ready\n", ret < 0 ? " not" : "");
	वापस ret;
पूर्ण

/* Note: वापसs standard 0/-ERROR code */
पूर्णांक iwl_pcie_prepare_card_hw(काष्ठा iwl_trans *trans)
अणु
	पूर्णांक ret;
	पूर्णांक t = 0;
	पूर्णांक iter;

	IWL_DEBUG_INFO(trans, "iwl_trans_prepare_card_hw enter\n");

	ret = iwl_pcie_set_hw_पढ़ोy(trans);
	/* If the card is पढ़ोy, निकास 0 */
	अगर (ret >= 0)
		वापस 0;

	iwl_set_bit(trans, CSR_DBG_LINK_PWR_MGMT_REG,
		    CSR_RESET_LINK_PWR_MGMT_DISABLED);
	usleep_range(1000, 2000);

	क्रम (iter = 0; iter < 10; iter++) अणु
		/* If HW is not पढ़ोy, prepare the conditions to check again */
		iwl_set_bit(trans, CSR_HW_IF_CONFIG_REG,
			    CSR_HW_IF_CONFIG_REG_PREPARE);

		करो अणु
			ret = iwl_pcie_set_hw_पढ़ोy(trans);
			अगर (ret >= 0)
				वापस 0;

			usleep_range(200, 1000);
			t += 200;
		पूर्ण जबतक (t < 150000);
		msleep(25);
	पूर्ण

	IWL_ERR(trans, "Couldn't prepare the card\n");

	वापस ret;
पूर्ण

/*
 * ucode
 */
अटल व्योम iwl_pcie_load_firmware_chunk_fh(काष्ठा iwl_trans *trans,
					    u32 dst_addr, dma_addr_t phy_addr,
					    u32 byte_cnt)
अणु
	iwl_ग_लिखो32(trans, FH_TCSR_CHNL_TX_CONFIG_REG(FH_SRVC_CHNL),
		    FH_TCSR_TX_CONFIG_REG_VAL_DMA_CHNL_PAUSE);

	iwl_ग_लिखो32(trans, FH_SRVC_CHNL_SRAM_ADDR_REG(FH_SRVC_CHNL),
		    dst_addr);

	iwl_ग_लिखो32(trans, FH_TFDIB_CTRL0_REG(FH_SRVC_CHNL),
		    phy_addr & FH_MEM_TFDIB_DRAM_ADDR_LSB_MSK);

	iwl_ग_लिखो32(trans, FH_TFDIB_CTRL1_REG(FH_SRVC_CHNL),
		    (iwl_get_dma_hi_addr(phy_addr)
			<< FH_MEM_TFDIB_REG1_ADDR_BITSHIFT) | byte_cnt);

	iwl_ग_लिखो32(trans, FH_TCSR_CHNL_TX_BUF_STS_REG(FH_SRVC_CHNL),
		    BIT(FH_TCSR_CHNL_TX_BUF_STS_REG_POS_TB_NUM) |
		    BIT(FH_TCSR_CHNL_TX_BUF_STS_REG_POS_TB_IDX) |
		    FH_TCSR_CHNL_TX_BUF_STS_REG_VAL_TFDB_VALID);

	iwl_ग_लिखो32(trans, FH_TCSR_CHNL_TX_CONFIG_REG(FH_SRVC_CHNL),
		    FH_TCSR_TX_CONFIG_REG_VAL_DMA_CHNL_ENABLE |
		    FH_TCSR_TX_CONFIG_REG_VAL_DMA_CREDIT_DISABLE |
		    FH_TCSR_TX_CONFIG_REG_VAL_CIRQ_HOST_ENDTFD);
पूर्ण

अटल पूर्णांक iwl_pcie_load_firmware_chunk(काष्ठा iwl_trans *trans,
					u32 dst_addr, dma_addr_t phy_addr,
					u32 byte_cnt)
अणु
	काष्ठा iwl_trans_pcie *trans_pcie = IWL_TRANS_GET_PCIE_TRANS(trans);
	पूर्णांक ret;

	trans_pcie->ucode_ग_लिखो_complete = false;

	अगर (!iwl_trans_grab_nic_access(trans))
		वापस -EIO;

	iwl_pcie_load_firmware_chunk_fh(trans, dst_addr, phy_addr,
					byte_cnt);
	iwl_trans_release_nic_access(trans);

	ret = रुको_event_समयout(trans_pcie->ucode_ग_लिखो_रुकोq,
				 trans_pcie->ucode_ग_लिखो_complete, 5 * HZ);
	अगर (!ret) अणु
		IWL_ERR(trans, "Failed to load firmware chunk!\n");
		iwl_trans_pcie_dump_regs(trans);
		वापस -ETIMEDOUT;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक iwl_pcie_load_section(काष्ठा iwl_trans *trans, u8 section_num,
			    स्थिर काष्ठा fw_desc *section)
अणु
	u8 *v_addr;
	dma_addr_t p_addr;
	u32 offset, chunk_sz = min_t(u32, FH_MEM_TB_MAX_LENGTH, section->len);
	पूर्णांक ret = 0;

	IWL_DEBUG_FW(trans, "[%d] uCode section being loaded...\n",
		     section_num);

	v_addr = dma_alloc_coherent(trans->dev, chunk_sz, &p_addr,
				    GFP_KERNEL | __GFP_NOWARN);
	अगर (!v_addr) अणु
		IWL_DEBUG_INFO(trans, "Falling back to small chunks of DMA\n");
		chunk_sz = PAGE_SIZE;
		v_addr = dma_alloc_coherent(trans->dev, chunk_sz,
					    &p_addr, GFP_KERNEL);
		अगर (!v_addr)
			वापस -ENOMEM;
	पूर्ण

	क्रम (offset = 0; offset < section->len; offset += chunk_sz) अणु
		u32 copy_size, dst_addr;
		bool extended_addr = false;

		copy_size = min_t(u32, chunk_sz, section->len - offset);
		dst_addr = section->offset + offset;

		अगर (dst_addr >= IWL_FW_MEM_EXTENDED_START &&
		    dst_addr <= IWL_FW_MEM_EXTENDED_END)
			extended_addr = true;

		अगर (extended_addr)
			iwl_set_bits_prph(trans, LMPM_CHICK,
					  LMPM_CHICK_EXTENDED_ADDR_SPACE);

		स_नकल(v_addr, (u8 *)section->data + offset, copy_size);
		ret = iwl_pcie_load_firmware_chunk(trans, dst_addr, p_addr,
						   copy_size);

		अगर (extended_addr)
			iwl_clear_bits_prph(trans, LMPM_CHICK,
					    LMPM_CHICK_EXTENDED_ADDR_SPACE);

		अगर (ret) अणु
			IWL_ERR(trans,
				"Could not load the [%d] uCode section\n",
				section_num);
			अवरोध;
		पूर्ण
	पूर्ण

	dma_मुक्त_coherent(trans->dev, chunk_sz, v_addr, p_addr);
	वापस ret;
पूर्ण

अटल पूर्णांक iwl_pcie_load_cpu_sections_8000(काष्ठा iwl_trans *trans,
					   स्थिर काष्ठा fw_img *image,
					   पूर्णांक cpu,
					   पूर्णांक *first_ucode_section)
अणु
	पूर्णांक shअगरt_param;
	पूर्णांक i, ret = 0, sec_num = 0x1;
	u32 val, last_पढ़ो_idx = 0;

	अगर (cpu == 1) अणु
		shअगरt_param = 0;
		*first_ucode_section = 0;
	पूर्ण अन्यथा अणु
		shअगरt_param = 16;
		(*first_ucode_section)++;
	पूर्ण

	क्रम (i = *first_ucode_section; i < image->num_sec; i++) अणु
		last_पढ़ो_idx = i;

		/*
		 * CPU1_CPU2_SEPARATOR_SECTION delimiter - separate between
		 * CPU1 to CPU2.
		 * PAGING_SEPARATOR_SECTION delimiter - separate between
		 * CPU2 non paged to CPU2 paging sec.
		 */
		अगर (!image->sec[i].data ||
		    image->sec[i].offset == CPU1_CPU2_SEPARATOR_SECTION ||
		    image->sec[i].offset == PAGING_SEPARATOR_SECTION) अणु
			IWL_DEBUG_FW(trans,
				     "Break since Data not valid or Empty section, sec = %d\n",
				     i);
			अवरोध;
		पूर्ण

		ret = iwl_pcie_load_section(trans, i, &image->sec[i]);
		अगर (ret)
			वापस ret;

		/* Notअगरy ucode of loaded section number and status */
		val = iwl_पढ़ो_direct32(trans, FH_UCODE_LOAD_STATUS);
		val = val | (sec_num << shअगरt_param);
		iwl_ग_लिखो_direct32(trans, FH_UCODE_LOAD_STATUS, val);

		sec_num = (sec_num << 1) | 0x1;
	पूर्ण

	*first_ucode_section = last_पढ़ो_idx;

	iwl_enable_पूर्णांकerrupts(trans);

	अगर (trans->trans_cfg->use_tfh) अणु
		अगर (cpu == 1)
			iwl_ग_लिखो_prph(trans, UREG_UCODE_LOAD_STATUS,
				       0xFFFF);
		अन्यथा
			iwl_ग_लिखो_prph(trans, UREG_UCODE_LOAD_STATUS,
				       0xFFFFFFFF);
	पूर्ण अन्यथा अणु
		अगर (cpu == 1)
			iwl_ग_लिखो_direct32(trans, FH_UCODE_LOAD_STATUS,
					   0xFFFF);
		अन्यथा
			iwl_ग_लिखो_direct32(trans, FH_UCODE_LOAD_STATUS,
					   0xFFFFFFFF);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक iwl_pcie_load_cpu_sections(काष्ठा iwl_trans *trans,
				      स्थिर काष्ठा fw_img *image,
				      पूर्णांक cpu,
				      पूर्णांक *first_ucode_section)
अणु
	पूर्णांक i, ret = 0;
	u32 last_पढ़ो_idx = 0;

	अगर (cpu == 1)
		*first_ucode_section = 0;
	अन्यथा
		(*first_ucode_section)++;

	क्रम (i = *first_ucode_section; i < image->num_sec; i++) अणु
		last_पढ़ो_idx = i;

		/*
		 * CPU1_CPU2_SEPARATOR_SECTION delimiter - separate between
		 * CPU1 to CPU2.
		 * PAGING_SEPARATOR_SECTION delimiter - separate between
		 * CPU2 non paged to CPU2 paging sec.
		 */
		अगर (!image->sec[i].data ||
		    image->sec[i].offset == CPU1_CPU2_SEPARATOR_SECTION ||
		    image->sec[i].offset == PAGING_SEPARATOR_SECTION) अणु
			IWL_DEBUG_FW(trans,
				     "Break since Data not valid or Empty section, sec = %d\n",
				     i);
			अवरोध;
		पूर्ण

		ret = iwl_pcie_load_section(trans, i, &image->sec[i]);
		अगर (ret)
			वापस ret;
	पूर्ण

	*first_ucode_section = last_पढ़ो_idx;

	वापस 0;
पूर्ण

अटल व्योम iwl_pcie_apply_destination_ini(काष्ठा iwl_trans *trans)
अणु
	क्रमागत iwl_fw_ini_allocation_id alloc_id = IWL_FW_INI_ALLOCATION_ID_DBGC1;
	काष्ठा iwl_fw_ini_allocation_tlv *fw_mon_cfg =
		&trans->dbg.fw_mon_cfg[alloc_id];
	काष्ठा iwl_dram_data *frag;

	अगर (!iwl_trans_dbg_ini_valid(trans))
		वापस;

	अगर (le32_to_cpu(fw_mon_cfg->buf_location) ==
	    IWL_FW_INI_LOCATION_SRAM_PATH) अणु
		IWL_DEBUG_FW(trans, "WRT: Applying SMEM buffer destination\n");
		/* set sram monitor by enabling bit 7 */
		iwl_set_bit(trans, CSR_HW_IF_CONFIG_REG,
			    CSR_HW_IF_CONFIG_REG_BIT_MONITOR_SRAM);

		वापस;
	पूर्ण

	अगर (le32_to_cpu(fw_mon_cfg->buf_location) !=
	    IWL_FW_INI_LOCATION_DRAM_PATH ||
	    !trans->dbg.fw_mon_ini[alloc_id].num_frags)
		वापस;

	frag = &trans->dbg.fw_mon_ini[alloc_id].frags[0];

	IWL_DEBUG_FW(trans, "WRT: Applying DRAM destination (alloc_id=%u)\n",
		     alloc_id);

	iwl_ग_लिखो_umac_prph(trans, MON_BUFF_BASE_ADDR_VER2,
			    frag->physical >> MON_BUFF_SHIFT_VER2);
	iwl_ग_लिखो_umac_prph(trans, MON_BUFF_END_ADDR_VER2,
			    (frag->physical + frag->size - 256) >>
			    MON_BUFF_SHIFT_VER2);
पूर्ण

व्योम iwl_pcie_apply_destination(काष्ठा iwl_trans *trans)
अणु
	स्थिर काष्ठा iwl_fw_dbg_dest_tlv_v1 *dest = trans->dbg.dest_tlv;
	स्थिर काष्ठा iwl_dram_data *fw_mon = &trans->dbg.fw_mon;
	पूर्णांक i;

	अगर (iwl_trans_dbg_ini_valid(trans)) अणु
		iwl_pcie_apply_destination_ini(trans);
		वापस;
	पूर्ण

	IWL_INFO(trans, "Applying debug destination %s\n",
		 get_fw_dbg_mode_string(dest->monitor_mode));

	अगर (dest->monitor_mode == EXTERNAL_MODE)
		iwl_pcie_alloc_fw_monitor(trans, dest->size_घातer);
	अन्यथा
		IWL_WARN(trans, "PCI should have external buffer debug\n");

	क्रम (i = 0; i < trans->dbg.n_dest_reg; i++) अणु
		u32 addr = le32_to_cpu(dest->reg_ops[i].addr);
		u32 val = le32_to_cpu(dest->reg_ops[i].val);

		चयन (dest->reg_ops[i].op) अणु
		हाल CSR_ASSIGN:
			iwl_ग_लिखो32(trans, addr, val);
			अवरोध;
		हाल CSR_SETBIT:
			iwl_set_bit(trans, addr, BIT(val));
			अवरोध;
		हाल CSR_CLEARBIT:
			iwl_clear_bit(trans, addr, BIT(val));
			अवरोध;
		हाल PRPH_ASSIGN:
			iwl_ग_लिखो_prph(trans, addr, val);
			अवरोध;
		हाल PRPH_SETBIT:
			iwl_set_bits_prph(trans, addr, BIT(val));
			अवरोध;
		हाल PRPH_CLEARBIT:
			iwl_clear_bits_prph(trans, addr, BIT(val));
			अवरोध;
		हाल PRPH_BLOCKBIT:
			अगर (iwl_पढ़ो_prph(trans, addr) & BIT(val)) अणु
				IWL_ERR(trans,
					"BIT(%u) in address 0x%x is 1, stopping FW configuration\n",
					val, addr);
				जाओ monitor;
			पूर्ण
			अवरोध;
		शेष:
			IWL_ERR(trans, "FW debug - unknown OP %d\n",
				dest->reg_ops[i].op);
			अवरोध;
		पूर्ण
	पूर्ण

monitor:
	अगर (dest->monitor_mode == EXTERNAL_MODE && fw_mon->size) अणु
		iwl_ग_लिखो_prph(trans, le32_to_cpu(dest->base_reg),
			       fw_mon->physical >> dest->base_shअगरt);
		अगर (trans->trans_cfg->device_family >= IWL_DEVICE_FAMILY_8000)
			iwl_ग_लिखो_prph(trans, le32_to_cpu(dest->end_reg),
				       (fw_mon->physical + fw_mon->size -
					256) >> dest->end_shअगरt);
		अन्यथा
			iwl_ग_लिखो_prph(trans, le32_to_cpu(dest->end_reg),
				       (fw_mon->physical + fw_mon->size) >>
				       dest->end_shअगरt);
	पूर्ण
पूर्ण

अटल पूर्णांक iwl_pcie_load_given_ucode(काष्ठा iwl_trans *trans,
				स्थिर काष्ठा fw_img *image)
अणु
	पूर्णांक ret = 0;
	पूर्णांक first_ucode_section;

	IWL_DEBUG_FW(trans, "working with %s CPU\n",
		     image->is_dual_cpus ? "Dual" : "Single");

	/* load to FW the binary non secured sections of CPU1 */
	ret = iwl_pcie_load_cpu_sections(trans, image, 1, &first_ucode_section);
	अगर (ret)
		वापस ret;

	अगर (image->is_dual_cpus) अणु
		/* set CPU2 header address */
		iwl_ग_लिखो_prph(trans,
			       LMPM_SECURE_UCODE_LOAD_CPU2_HDR_ADDR,
			       LMPM_SECURE_CPU2_HDR_MEM_SPACE);

		/* load to FW the binary sections of CPU2 */
		ret = iwl_pcie_load_cpu_sections(trans, image, 2,
						 &first_ucode_section);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (iwl_pcie_dbg_on(trans))
		iwl_pcie_apply_destination(trans);

	iwl_enable_पूर्णांकerrupts(trans);

	/* release CPU reset */
	iwl_ग_लिखो32(trans, CSR_RESET, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक iwl_pcie_load_given_ucode_8000(काष्ठा iwl_trans *trans,
					  स्थिर काष्ठा fw_img *image)
अणु
	पूर्णांक ret = 0;
	पूर्णांक first_ucode_section;

	IWL_DEBUG_FW(trans, "working with %s CPU\n",
		     image->is_dual_cpus ? "Dual" : "Single");

	अगर (iwl_pcie_dbg_on(trans))
		iwl_pcie_apply_destination(trans);

	IWL_DEBUG_POWER(trans, "Original WFPM value = 0x%08X\n",
			iwl_पढ़ो_prph(trans, WFPM_GP2));

	/*
	 * Set शेष value. On resume पढ़ोing the values that were
	 * zeored can provide debug data on the resume flow.
	 * This is क्रम debugging only and has no functional impact.
	 */
	iwl_ग_लिखो_prph(trans, WFPM_GP2, 0x01010101);

	/* configure the ucode to be पढ़ोy to get the secured image */
	/* release CPU reset */
	iwl_ग_लिखो_prph(trans, RELEASE_CPU_RESET, RELEASE_CPU_RESET_BIT);

	/* load to FW the binary Secured sections of CPU1 */
	ret = iwl_pcie_load_cpu_sections_8000(trans, image, 1,
					      &first_ucode_section);
	अगर (ret)
		वापस ret;

	/* load to FW the binary sections of CPU2 */
	वापस iwl_pcie_load_cpu_sections_8000(trans, image, 2,
					       &first_ucode_section);
पूर्ण

bool iwl_pcie_check_hw_rf_समाप्त(काष्ठा iwl_trans *trans)
अणु
	काष्ठा iwl_trans_pcie *trans_pcie =  IWL_TRANS_GET_PCIE_TRANS(trans);
	bool hw_rfसमाप्त = iwl_is_rfसमाप्त_set(trans);
	bool prev = test_bit(STATUS_RFKILL_OPMODE, &trans->status);
	bool report;

	अगर (hw_rfसमाप्त) अणु
		set_bit(STATUS_RFKILL_HW, &trans->status);
		set_bit(STATUS_RFKILL_OPMODE, &trans->status);
	पूर्ण अन्यथा अणु
		clear_bit(STATUS_RFKILL_HW, &trans->status);
		अगर (trans_pcie->opmode_करोwn)
			clear_bit(STATUS_RFKILL_OPMODE, &trans->status);
	पूर्ण

	report = test_bit(STATUS_RFKILL_OPMODE, &trans->status);

	अगर (prev != report)
		iwl_trans_pcie_rf_समाप्त(trans, report);

	वापस hw_rfसमाप्त;
पूर्ण

काष्ठा iwl_causes_list अणु
	u32 cause_num;
	u32 mask_reg;
	u8 addr;
पूर्ण;

अटल काष्ठा iwl_causes_list causes_list[] = अणु
	अणुMSIX_FH_INT_CAUSES_D2S_CH0_NUM,	CSR_MSIX_FH_INT_MASK_AD, 0पूर्ण,
	अणुMSIX_FH_INT_CAUSES_D2S_CH1_NUM,	CSR_MSIX_FH_INT_MASK_AD, 0x1पूर्ण,
	अणुMSIX_FH_INT_CAUSES_S2D,		CSR_MSIX_FH_INT_MASK_AD, 0x3पूर्ण,
	अणुMSIX_FH_INT_CAUSES_FH_ERR,		CSR_MSIX_FH_INT_MASK_AD, 0x5पूर्ण,
	अणुMSIX_HW_INT_CAUSES_REG_ALIVE,		CSR_MSIX_HW_INT_MASK_AD, 0x10पूर्ण,
	अणुMSIX_HW_INT_CAUSES_REG_WAKEUP,		CSR_MSIX_HW_INT_MASK_AD, 0x11पूर्ण,
	अणुMSIX_HW_INT_CAUSES_REG_RESET_DONE,	CSR_MSIX_HW_INT_MASK_AD, 0x12पूर्ण,
	अणुMSIX_HW_INT_CAUSES_REG_CT_KILL,	CSR_MSIX_HW_INT_MASK_AD, 0x16पूर्ण,
	अणुMSIX_HW_INT_CAUSES_REG_RF_KILL,	CSR_MSIX_HW_INT_MASK_AD, 0x17पूर्ण,
	अणुMSIX_HW_INT_CAUSES_REG_PERIODIC,	CSR_MSIX_HW_INT_MASK_AD, 0x18पूर्ण,
	अणुMSIX_HW_INT_CAUSES_REG_SW_ERR,		CSR_MSIX_HW_INT_MASK_AD, 0x29पूर्ण,
	अणुMSIX_HW_INT_CAUSES_REG_SCD,		CSR_MSIX_HW_INT_MASK_AD, 0x2Aपूर्ण,
	अणुMSIX_HW_INT_CAUSES_REG_FH_TX,		CSR_MSIX_HW_INT_MASK_AD, 0x2Bपूर्ण,
	अणुMSIX_HW_INT_CAUSES_REG_HW_ERR,		CSR_MSIX_HW_INT_MASK_AD, 0x2Dपूर्ण,
	अणुMSIX_HW_INT_CAUSES_REG_HAP,		CSR_MSIX_HW_INT_MASK_AD, 0x2Eपूर्ण,
पूर्ण;

अटल व्योम iwl_pcie_map_non_rx_causes(काष्ठा iwl_trans *trans)
अणु
	काष्ठा iwl_trans_pcie *trans_pcie =  IWL_TRANS_GET_PCIE_TRANS(trans);
	पूर्णांक val = trans_pcie->def_irq | MSIX_NON_AUTO_CLEAR_CAUSE;
	पूर्णांक i, arr_size = ARRAY_SIZE(causes_list);
	काष्ठा iwl_causes_list *causes = causes_list;

	/*
	 * Access all non RX causes and map them to the शेष irq.
	 * In हाल we are missing at least one पूर्णांकerrupt vector,
	 * the first पूर्णांकerrupt vector will serve non-RX and FBQ causes.
	 */
	क्रम (i = 0; i < arr_size; i++) अणु
		iwl_ग_लिखो8(trans, CSR_MSIX_IVAR(causes[i].addr), val);
		iwl_clear_bit(trans, causes[i].mask_reg,
			      causes[i].cause_num);
	पूर्ण
पूर्ण

अटल व्योम iwl_pcie_map_rx_causes(काष्ठा iwl_trans *trans)
अणु
	काष्ठा iwl_trans_pcie *trans_pcie = IWL_TRANS_GET_PCIE_TRANS(trans);
	u32 offset =
		trans_pcie->shared_vec_mask & IWL_SHARED_IRQ_FIRST_RSS ? 1 : 0;
	u32 val, idx;

	/*
	 * The first RX queue - fallback queue, which is designated क्रम
	 * management frame, command responses etc, is always mapped to the
	 * first पूर्णांकerrupt vector. The other RX queues are mapped to
	 * the other (N - 2) पूर्णांकerrupt vectors.
	 */
	val = BIT(MSIX_FH_INT_CAUSES_Q(0));
	क्रम (idx = 1; idx < trans->num_rx_queues; idx++) अणु
		iwl_ग_लिखो8(trans, CSR_MSIX_RX_IVAR(idx),
			   MSIX_FH_INT_CAUSES_Q(idx - offset));
		val |= BIT(MSIX_FH_INT_CAUSES_Q(idx));
	पूर्ण
	iwl_ग_लिखो32(trans, CSR_MSIX_FH_INT_MASK_AD, ~val);

	val = MSIX_FH_INT_CAUSES_Q(0);
	अगर (trans_pcie->shared_vec_mask & IWL_SHARED_IRQ_NON_RX)
		val |= MSIX_NON_AUTO_CLEAR_CAUSE;
	iwl_ग_लिखो8(trans, CSR_MSIX_RX_IVAR(0), val);

	अगर (trans_pcie->shared_vec_mask & IWL_SHARED_IRQ_FIRST_RSS)
		iwl_ग_लिखो8(trans, CSR_MSIX_RX_IVAR(1), val);
पूर्ण

व्योम iwl_pcie_conf_msix_hw(काष्ठा iwl_trans_pcie *trans_pcie)
अणु
	काष्ठा iwl_trans *trans = trans_pcie->trans;

	अगर (!trans_pcie->msix_enabled) अणु
		अगर (trans->trans_cfg->mq_rx_supported &&
		    test_bit(STATUS_DEVICE_ENABLED, &trans->status))
			iwl_ग_लिखो_umac_prph(trans, UREG_CHICK,
					    UREG_CHICK_MSI_ENABLE);
		वापस;
	पूर्ण
	/*
	 * The IVAR table needs to be configured again after reset,
	 * but अगर the device is disabled, we can't ग_लिखो to
	 * prph.
	 */
	अगर (test_bit(STATUS_DEVICE_ENABLED, &trans->status))
		iwl_ग_लिखो_umac_prph(trans, UREG_CHICK, UREG_CHICK_MSIX_ENABLE);

	/*
	 * Each cause from the causes list above and the RX causes is
	 * represented as a byte in the IVAR table. The first nibble
	 * represents the bound पूर्णांकerrupt vector of the cause, the second
	 * represents no स्वतः clear क्रम this cause. This will be set अगर its
	 * पूर्णांकerrupt vector is bound to serve other causes.
	 */
	iwl_pcie_map_rx_causes(trans);

	iwl_pcie_map_non_rx_causes(trans);
पूर्ण

अटल व्योम iwl_pcie_init_msix(काष्ठा iwl_trans_pcie *trans_pcie)
अणु
	काष्ठा iwl_trans *trans = trans_pcie->trans;

	iwl_pcie_conf_msix_hw(trans_pcie);

	अगर (!trans_pcie->msix_enabled)
		वापस;

	trans_pcie->fh_init_mask = ~iwl_पढ़ो32(trans, CSR_MSIX_FH_INT_MASK_AD);
	trans_pcie->fh_mask = trans_pcie->fh_init_mask;
	trans_pcie->hw_init_mask = ~iwl_पढ़ो32(trans, CSR_MSIX_HW_INT_MASK_AD);
	trans_pcie->hw_mask = trans_pcie->hw_init_mask;
पूर्ण

अटल व्योम _iwl_trans_pcie_stop_device(काष्ठा iwl_trans *trans)
अणु
	काष्ठा iwl_trans_pcie *trans_pcie = IWL_TRANS_GET_PCIE_TRANS(trans);

	lockdep_निश्चित_held(&trans_pcie->mutex);

	अगर (trans_pcie->is_करोwn)
		वापस;

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
		iwl_pcie_tx_stop(trans);
		iwl_pcie_rx_stop(trans);

		/* Power-करोwn device's busmaster DMA घड़ीs */
		अगर (!trans->cfg->apmg_not_supported) अणु
			iwl_ग_लिखो_prph(trans, APMG_CLK_DIS_REG,
				       APMG_CLK_VAL_DMA_CLK_RQT);
			udelay(5);
		पूर्ण
	पूर्ण

	/* Make sure (redundant) we've released our request to stay awake */
	iwl_clear_bit(trans, CSR_GP_CNTRL,
		      CSR_GP_CNTRL_REG_FLAG_MAC_ACCESS_REQ);

	/* Stop the device, and put it in low घातer state */
	iwl_pcie_apm_stop(trans, false);

	iwl_trans_pcie_sw_reset(trans);

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

व्योम iwl_pcie_synchronize_irqs(काष्ठा iwl_trans *trans)
अणु
	काष्ठा iwl_trans_pcie *trans_pcie = IWL_TRANS_GET_PCIE_TRANS(trans);

	अगर (trans_pcie->msix_enabled) अणु
		पूर्णांक i;

		क्रम (i = 0; i < trans_pcie->alloc_vecs; i++)
			synchronize_irq(trans_pcie->msix_entries[i].vector);
	पूर्ण अन्यथा अणु
		synchronize_irq(trans_pcie->pci_dev->irq);
	पूर्ण
पूर्ण

अटल पूर्णांक iwl_trans_pcie_start_fw(काष्ठा iwl_trans *trans,
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

	ret = iwl_pcie_nic_init(trans);
	अगर (ret) अणु
		IWL_ERR(trans, "Unable to init nic\n");
		जाओ out;
	पूर्ण

	/*
	 * Now, we load the firmware and करोn't want to be पूर्णांकerrupted, even
	 * by the RF-Kill पूर्णांकerrupt (hence mask all the पूर्णांकerrupt besides the
	 * FH_TX पूर्णांकerrupt which is needed to load the firmware). If the
	 * RF-Kill चयन is toggled, we will find out after having loaded
	 * the firmware and वापस the proper value to the caller.
	 */
	iwl_enable_fw_load_पूर्णांक(trans);

	/* really make sure rfसमाप्त handshake bits are cleared */
	iwl_ग_लिखो32(trans, CSR_UCODE_DRV_GP1_CLR, CSR_UCODE_SW_BIT_RFKILL);
	iwl_ग_लिखो32(trans, CSR_UCODE_DRV_GP1_CLR, CSR_UCODE_SW_BIT_RFKILL);

	/* Load the given image to the HW */
	अगर (trans->trans_cfg->device_family >= IWL_DEVICE_FAMILY_8000)
		ret = iwl_pcie_load_given_ucode_8000(trans, fw);
	अन्यथा
		ret = iwl_pcie_load_given_ucode(trans, fw);

	/* re-check RF-Kill state since we may have missed the पूर्णांकerrupt */
	hw_rfसमाप्त = iwl_pcie_check_hw_rf_समाप्त(trans);
	अगर (hw_rfसमाप्त && !run_in_rfसमाप्त)
		ret = -ERFKILL;

out:
	mutex_unlock(&trans_pcie->mutex);
	वापस ret;
पूर्ण

अटल व्योम iwl_trans_pcie_fw_alive(काष्ठा iwl_trans *trans, u32 scd_addr)
अणु
	iwl_pcie_reset_ict(trans);
	iwl_pcie_tx_start(trans, scd_addr);
पूर्ण

व्योम iwl_trans_pcie_handle_stop_rfसमाप्त(काष्ठा iwl_trans *trans,
				       bool was_in_rfसमाप्त)
अणु
	bool hw_rfसमाप्त;

	/*
	 * Check again since the RF समाप्त state may have changed जबतक
	 * all the पूर्णांकerrupts were disabled, in this हाल we couldn't
	 * receive the RF समाप्त पूर्णांकerrupt and update the state in the
	 * op_mode.
	 * Don't call the op_mode if the rkfill state hasn't changed.
	 * This allows the op_mode to call stop_device from the rfसमाप्त
	 * notअगरication without endless recursion. Under very rare
	 * circumstances, we might have a small recursion अगर the rfसमाप्त
	 * state changed exactly now जबतक we were called from stop_device.
	 * This is very unlikely but can happen and is supported.
	 */
	hw_rfसमाप्त = iwl_is_rfसमाप्त_set(trans);
	अगर (hw_rfसमाप्त) अणु
		set_bit(STATUS_RFKILL_HW, &trans->status);
		set_bit(STATUS_RFKILL_OPMODE, &trans->status);
	पूर्ण अन्यथा अणु
		clear_bit(STATUS_RFKILL_HW, &trans->status);
		clear_bit(STATUS_RFKILL_OPMODE, &trans->status);
	पूर्ण
	अगर (hw_rfसमाप्त != was_in_rfसमाप्त)
		iwl_trans_pcie_rf_समाप्त(trans, hw_rfसमाप्त);
पूर्ण

अटल व्योम iwl_trans_pcie_stop_device(काष्ठा iwl_trans *trans)
अणु
	काष्ठा iwl_trans_pcie *trans_pcie = IWL_TRANS_GET_PCIE_TRANS(trans);
	bool was_in_rfसमाप्त;

	iwl_op_mode_समय_poपूर्णांक(trans->op_mode,
			       IWL_FW_INI_TIME_POINT_HOST_DEVICE_DISABLE,
			       शून्य);

	mutex_lock(&trans_pcie->mutex);
	trans_pcie->opmode_करोwn = true;
	was_in_rfसमाप्त = test_bit(STATUS_RFKILL_OPMODE, &trans->status);
	_iwl_trans_pcie_stop_device(trans);
	iwl_trans_pcie_handle_stop_rfसमाप्त(trans, was_in_rfसमाप्त);
	mutex_unlock(&trans_pcie->mutex);
पूर्ण

व्योम iwl_trans_pcie_rf_समाप्त(काष्ठा iwl_trans *trans, bool state)
अणु
	काष्ठा iwl_trans_pcie __maybe_unused *trans_pcie =
		IWL_TRANS_GET_PCIE_TRANS(trans);

	lockdep_निश्चित_held(&trans_pcie->mutex);

	IWL_WARN(trans, "reporting RF_KILL (radio %s)\n",
		 state ? "disabled" : "enabled");
	अगर (iwl_op_mode_hw_rf_समाप्त(trans->op_mode, state)) अणु
		अगर (trans->trans_cfg->gen2)
			_iwl_trans_pcie_gen2_stop_device(trans);
		अन्यथा
			_iwl_trans_pcie_stop_device(trans);
	पूर्ण
पूर्ण

व्योम iwl_pcie_d3_complete_suspend(काष्ठा iwl_trans *trans,
				  bool test, bool reset)
अणु
	iwl_disable_पूर्णांकerrupts(trans);

	/*
	 * in testing mode, the host stays awake and the
	 * hardware won't be reset (not even partially)
	 */
	अगर (test)
		वापस;

	iwl_pcie_disable_ict(trans);

	iwl_pcie_synchronize_irqs(trans);

	iwl_clear_bit(trans, CSR_GP_CNTRL,
		      CSR_GP_CNTRL_REG_FLAG_MAC_ACCESS_REQ);
	iwl_clear_bit(trans, CSR_GP_CNTRL, CSR_GP_CNTRL_REG_FLAG_INIT_DONE);

	अगर (reset) अणु
		/*
		 * reset TX queues -- some of their रेजिस्टरs reset during S3
		 * so अगर we करोn't reset everything here the D3 image would try
		 * to execute some invalid memory upon resume
		 */
		iwl_trans_pcie_tx_reset(trans);
	पूर्ण

	iwl_pcie_set_pwr(trans, true);
पूर्ण

अटल पूर्णांक iwl_trans_pcie_d3_suspend(काष्ठा iwl_trans *trans, bool test,
				     bool reset)
अणु
	पूर्णांक ret;
	काष्ठा iwl_trans_pcie *trans_pcie =  IWL_TRANS_GET_PCIE_TRANS(trans);

	अगर (!reset)
		/* Enable persistence mode to aव्योम reset */
		iwl_set_bit(trans, CSR_HW_IF_CONFIG_REG,
			    CSR_HW_IF_CONFIG_REG_PERSIST_MODE);

	अगर (trans->trans_cfg->device_family >= IWL_DEVICE_FAMILY_AX210) अणु
		iwl_ग_लिखो_umac_prph(trans, UREG_DOORBELL_TO_ISR6,
				    UREG_DOORBELL_TO_ISR6_SUSPEND);

		ret = रुको_event_समयout(trans_pcie->sx_रुकोq,
					 trans_pcie->sx_complete, 2 * HZ);
		/*
		 * Invalidate it toward resume.
		 */
		trans_pcie->sx_complete = false;

		अगर (!ret) अणु
			IWL_ERR(trans, "Timeout entering D3\n");
			वापस -ETIMEDOUT;
		पूर्ण
	पूर्ण
	iwl_pcie_d3_complete_suspend(trans, test, reset);

	वापस 0;
पूर्ण

अटल पूर्णांक iwl_trans_pcie_d3_resume(काष्ठा iwl_trans *trans,
				    क्रमागत iwl_d3_status *status,
				    bool test,  bool reset)
अणु
	काष्ठा iwl_trans_pcie *trans_pcie =  IWL_TRANS_GET_PCIE_TRANS(trans);
	u32 val;
	पूर्णांक ret;

	अगर (test) अणु
		iwl_enable_पूर्णांकerrupts(trans);
		*status = IWL_D3_STATUS_ALIVE;
		जाओ out;
	पूर्ण

	iwl_set_bit(trans, CSR_GP_CNTRL,
		    CSR_GP_CNTRL_REG_FLAG_MAC_ACCESS_REQ);

	ret = iwl_finish_nic_init(trans, trans->trans_cfg);
	अगर (ret)
		वापस ret;

	/*
	 * Reconfigure IVAR table in हाल of MSIX or reset ict table in
	 * MSI mode since HW reset erased it.
	 * Also enables पूर्णांकerrupts - none will happen as
	 * the device करोesn't know we're waking it up, only when
	 * the opmode actually tells it after this call.
	 */
	iwl_pcie_conf_msix_hw(trans_pcie);
	अगर (!trans_pcie->msix_enabled)
		iwl_pcie_reset_ict(trans);
	iwl_enable_पूर्णांकerrupts(trans);

	iwl_pcie_set_pwr(trans, false);

	अगर (!reset) अणु
		iwl_clear_bit(trans, CSR_GP_CNTRL,
			      CSR_GP_CNTRL_REG_FLAG_MAC_ACCESS_REQ);
	पूर्ण अन्यथा अणु
		iwl_trans_pcie_tx_reset(trans);

		ret = iwl_pcie_rx_init(trans);
		अगर (ret) अणु
			IWL_ERR(trans,
				"Failed to resume the device (RX reset)\n");
			वापस ret;
		पूर्ण
	पूर्ण

	IWL_DEBUG_POWER(trans, "WFPM value upon resume = 0x%08X\n",
			iwl_पढ़ो_umac_prph(trans, WFPM_GP2));

	val = iwl_पढ़ो32(trans, CSR_RESET);
	अगर (val & CSR_RESET_REG_FLAG_NEVO_RESET)
		*status = IWL_D3_STATUS_RESET;
	अन्यथा
		*status = IWL_D3_STATUS_ALIVE;

out:
	अगर (*status == IWL_D3_STATUS_ALIVE &&
	    trans->trans_cfg->device_family >= IWL_DEVICE_FAMILY_AX210) अणु
		trans_pcie->sx_complete = false;
		iwl_ग_लिखो_umac_prph(trans, UREG_DOORBELL_TO_ISR6,
				    UREG_DOORBELL_TO_ISR6_RESUME);

		ret = रुको_event_समयout(trans_pcie->sx_रुकोq,
					 trans_pcie->sx_complete, 2 * HZ);
		/*
		 * Invalidate it toward next suspend.
		 */
		trans_pcie->sx_complete = false;

		अगर (!ret) अणु
			IWL_ERR(trans, "Timeout exiting D3\n");
			वापस -ETIMEDOUT;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम
iwl_pcie_set_पूर्णांकerrupt_capa(काष्ठा pci_dev *pdev,
			    काष्ठा iwl_trans *trans,
			    स्थिर काष्ठा iwl_cfg_trans_params *cfg_trans)
अणु
	काष्ठा iwl_trans_pcie *trans_pcie = IWL_TRANS_GET_PCIE_TRANS(trans);
	पूर्णांक max_irqs, num_irqs, i, ret;
	u16 pci_cmd;
	u32 max_rx_queues = IWL_MAX_RX_HW_QUEUES;

	अगर (!cfg_trans->mq_rx_supported)
		जाओ enable_msi;

	अगर (cfg_trans->device_family <= IWL_DEVICE_FAMILY_9000)
		max_rx_queues = IWL_9000_MAX_RX_HW_QUEUES;

	max_irqs = min_t(u32, num_online_cpus() + 2, max_rx_queues);
	क्रम (i = 0; i < max_irqs; i++)
		trans_pcie->msix_entries[i].entry = i;

	num_irqs = pci_enable_msix_range(pdev, trans_pcie->msix_entries,
					 MSIX_MIN_INTERRUPT_VECTORS,
					 max_irqs);
	अगर (num_irqs < 0) अणु
		IWL_DEBUG_INFO(trans,
			       "Failed to enable msi-x mode (ret %d). Moving to msi mode.\n",
			       num_irqs);
		जाओ enable_msi;
	पूर्ण
	trans_pcie->def_irq = (num_irqs == max_irqs) ? num_irqs - 1 : 0;

	IWL_DEBUG_INFO(trans,
		       "MSI-X enabled. %d interrupt vectors were allocated\n",
		       num_irqs);

	/*
	 * In हाल the OS provides fewer पूर्णांकerrupts than requested, dअगरferent
	 * causes will share the same पूर्णांकerrupt vector as follows:
	 * One पूर्णांकerrupt less: non rx causes shared with FBQ.
	 * Two पूर्णांकerrupts less: non rx causes shared with FBQ and RSS.
	 * More than two पूर्णांकerrupts: we will use fewer RSS queues.
	 */
	अगर (num_irqs <= max_irqs - 2) अणु
		trans_pcie->trans->num_rx_queues = num_irqs + 1;
		trans_pcie->shared_vec_mask = IWL_SHARED_IRQ_NON_RX |
			IWL_SHARED_IRQ_FIRST_RSS;
	पूर्ण अन्यथा अगर (num_irqs == max_irqs - 1) अणु
		trans_pcie->trans->num_rx_queues = num_irqs;
		trans_pcie->shared_vec_mask = IWL_SHARED_IRQ_NON_RX;
	पूर्ण अन्यथा अणु
		trans_pcie->trans->num_rx_queues = num_irqs - 1;
	पूर्ण

	IWL_DEBUG_INFO(trans,
		       "MSI-X enabled with rx queues %d, vec mask 0x%x\n",
		       trans_pcie->trans->num_rx_queues, trans_pcie->shared_vec_mask);

	WARN_ON(trans_pcie->trans->num_rx_queues > IWL_MAX_RX_HW_QUEUES);

	trans_pcie->alloc_vecs = num_irqs;
	trans_pcie->msix_enabled = true;
	वापस;

enable_msi:
	ret = pci_enable_msi(pdev);
	अगर (ret) अणु
		dev_err(&pdev->dev, "pci_enable_msi failed - %d\n", ret);
		/* enable rfसमाप्त पूर्णांकerrupt: hw bug w/a */
		pci_पढ़ो_config_word(pdev, PCI_COMMAND, &pci_cmd);
		अगर (pci_cmd & PCI_COMMAND_INTX_DISABLE) अणु
			pci_cmd &= ~PCI_COMMAND_INTX_DISABLE;
			pci_ग_लिखो_config_word(pdev, PCI_COMMAND, pci_cmd);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम iwl_pcie_irq_set_affinity(काष्ठा iwl_trans *trans)
अणु
	पूर्णांक iter_rx_q, i, ret, cpu, offset;
	काष्ठा iwl_trans_pcie *trans_pcie = IWL_TRANS_GET_PCIE_TRANS(trans);

	i = trans_pcie->shared_vec_mask & IWL_SHARED_IRQ_FIRST_RSS ? 0 : 1;
	iter_rx_q = trans_pcie->trans->num_rx_queues - 1 + i;
	offset = 1 + i;
	क्रम (; i < iter_rx_q ; i++) अणु
		/*
		 * Get the cpu prior to the place to search
		 * (i.e. वापस will be > i - 1).
		 */
		cpu = cpumask_next(i - offset, cpu_online_mask);
		cpumask_set_cpu(cpu, &trans_pcie->affinity_mask[i]);
		ret = irq_set_affinity_hपूर्णांक(trans_pcie->msix_entries[i].vector,
					    &trans_pcie->affinity_mask[i]);
		अगर (ret)
			IWL_ERR(trans_pcie->trans,
				"Failed to set affinity mask for IRQ %d\n",
				i);
	पूर्ण
पूर्ण

अटल पूर्णांक iwl_pcie_init_msix_handler(काष्ठा pci_dev *pdev,
				      काष्ठा iwl_trans_pcie *trans_pcie)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < trans_pcie->alloc_vecs; i++) अणु
		पूर्णांक ret;
		काष्ठा msix_entry *msix_entry;
		स्थिर अक्षर *qname = queue_name(&pdev->dev, trans_pcie, i);

		अगर (!qname)
			वापस -ENOMEM;

		msix_entry = &trans_pcie->msix_entries[i];
		ret = devm_request_thपढ़ोed_irq(&pdev->dev,
						msix_entry->vector,
						iwl_pcie_msix_isr,
						(i == trans_pcie->def_irq) ?
						iwl_pcie_irq_msix_handler :
						iwl_pcie_irq_rx_msix_handler,
						IRQF_SHARED,
						qname,
						msix_entry);
		अगर (ret) अणु
			IWL_ERR(trans_pcie->trans,
				"Error allocating IRQ %d\n", i);

			वापस ret;
		पूर्ण
	पूर्ण
	iwl_pcie_irq_set_affinity(trans_pcie->trans);

	वापस 0;
पूर्ण

अटल पूर्णांक iwl_trans_pcie_clear_persistence_bit(काष्ठा iwl_trans *trans)
अणु
	u32 hpm, wprot;

	चयन (trans->trans_cfg->device_family) अणु
	हाल IWL_DEVICE_FAMILY_9000:
		wprot = PREG_PRPH_WPROT_9000;
		अवरोध;
	हाल IWL_DEVICE_FAMILY_22000:
		wprot = PREG_PRPH_WPROT_22000;
		अवरोध;
	शेष:
		वापस 0;
	पूर्ण

	hpm = iwl_पढ़ो_umac_prph_no_grab(trans, HPM_DEBUG);
	अगर (hpm != 0xa5a5a5a0 && (hpm & PERSISTENCE_BIT)) अणु
		u32 wprot_val = iwl_पढ़ो_umac_prph_no_grab(trans, wprot);

		अगर (wprot_val & PREG_WFPM_ACCESS) अणु
			IWL_ERR(trans,
				"Error, can not clear persistence bit\n");
			वापस -EPERM;
		पूर्ण
		iwl_ग_लिखो_umac_prph_no_grab(trans, HPM_DEBUG,
					    hpm & ~PERSISTENCE_BIT);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक iwl_pcie_gen2_क्रमce_घातer_gating(काष्ठा iwl_trans *trans)
अणु
	पूर्णांक ret;

	ret = iwl_finish_nic_init(trans, trans->trans_cfg);
	अगर (ret < 0)
		वापस ret;

	iwl_set_bits_prph(trans, HPM_HIPM_GEN_CFG,
			  HPM_HIPM_GEN_CFG_CR_FORCE_ACTIVE);
	udelay(20);
	iwl_set_bits_prph(trans, HPM_HIPM_GEN_CFG,
			  HPM_HIPM_GEN_CFG_CR_PG_EN |
			  HPM_HIPM_GEN_CFG_CR_SLP_EN);
	udelay(20);
	iwl_clear_bits_prph(trans, HPM_HIPM_GEN_CFG,
			    HPM_HIPM_GEN_CFG_CR_FORCE_ACTIVE);

	iwl_trans_pcie_sw_reset(trans);

	वापस 0;
पूर्ण

अटल पूर्णांक _iwl_trans_pcie_start_hw(काष्ठा iwl_trans *trans)
अणु
	काष्ठा iwl_trans_pcie *trans_pcie = IWL_TRANS_GET_PCIE_TRANS(trans);
	पूर्णांक err;

	lockdep_निश्चित_held(&trans_pcie->mutex);

	err = iwl_pcie_prepare_card_hw(trans);
	अगर (err) अणु
		IWL_ERR(trans, "Error while preparing HW: %d\n", err);
		वापस err;
	पूर्ण

	err = iwl_trans_pcie_clear_persistence_bit(trans);
	अगर (err)
		वापस err;

	iwl_trans_pcie_sw_reset(trans);

	अगर (trans->trans_cfg->device_family == IWL_DEVICE_FAMILY_22000 &&
	    trans->trans_cfg->पूर्णांकegrated) अणु
		err = iwl_pcie_gen2_क्रमce_घातer_gating(trans);
		अगर (err)
			वापस err;
	पूर्ण

	err = iwl_pcie_apm_init(trans);
	अगर (err)
		वापस err;

	iwl_pcie_init_msix(trans_pcie);

	/* From now on, the op_mode will be kept updated about RF समाप्त state */
	iwl_enable_rfसमाप्त_पूर्णांक(trans);

	trans_pcie->opmode_करोwn = false;

	/* Set is_करोwn to false here so that...*/
	trans_pcie->is_करोwn = false;

	/* ...rfसमाप्त can call stop_device and set it false अगर needed */
	iwl_pcie_check_hw_rf_समाप्त(trans);

	वापस 0;
पूर्ण

अटल पूर्णांक iwl_trans_pcie_start_hw(काष्ठा iwl_trans *trans)
अणु
	काष्ठा iwl_trans_pcie *trans_pcie = IWL_TRANS_GET_PCIE_TRANS(trans);
	पूर्णांक ret;

	mutex_lock(&trans_pcie->mutex);
	ret = _iwl_trans_pcie_start_hw(trans);
	mutex_unlock(&trans_pcie->mutex);

	वापस ret;
पूर्ण

अटल व्योम iwl_trans_pcie_op_mode_leave(काष्ठा iwl_trans *trans)
अणु
	काष्ठा iwl_trans_pcie *trans_pcie = IWL_TRANS_GET_PCIE_TRANS(trans);

	mutex_lock(&trans_pcie->mutex);

	/* disable पूर्णांकerrupts - करोn't enable HW RF समाप्त पूर्णांकerrupt */
	iwl_disable_पूर्णांकerrupts(trans);

	iwl_pcie_apm_stop(trans, true);

	iwl_disable_पूर्णांकerrupts(trans);

	iwl_pcie_disable_ict(trans);

	mutex_unlock(&trans_pcie->mutex);

	iwl_pcie_synchronize_irqs(trans);
पूर्ण

अटल व्योम iwl_trans_pcie_ग_लिखो8(काष्ठा iwl_trans *trans, u32 ofs, u8 val)
अणु
	ग_लिखोb(val, IWL_TRANS_GET_PCIE_TRANS(trans)->hw_base + ofs);
पूर्ण

अटल व्योम iwl_trans_pcie_ग_लिखो32(काष्ठा iwl_trans *trans, u32 ofs, u32 val)
अणु
	ग_लिखोl(val, IWL_TRANS_GET_PCIE_TRANS(trans)->hw_base + ofs);
पूर्ण

अटल u32 iwl_trans_pcie_पढ़ो32(काष्ठा iwl_trans *trans, u32 ofs)
अणु
	वापस पढ़ोl(IWL_TRANS_GET_PCIE_TRANS(trans)->hw_base + ofs);
पूर्ण

अटल u32 iwl_trans_pcie_prph_msk(काष्ठा iwl_trans *trans)
अणु
	अगर (trans->trans_cfg->device_family >= IWL_DEVICE_FAMILY_AX210)
		वापस 0x00FFFFFF;
	अन्यथा
		वापस 0x000FFFFF;
पूर्ण

अटल u32 iwl_trans_pcie_पढ़ो_prph(काष्ठा iwl_trans *trans, u32 reg)
अणु
	u32 mask = iwl_trans_pcie_prph_msk(trans);

	iwl_trans_pcie_ग_लिखो32(trans, HBUS_TARG_PRPH_RADDR,
			       ((reg & mask) | (3 << 24)));
	वापस iwl_trans_pcie_पढ़ो32(trans, HBUS_TARG_PRPH_RDAT);
पूर्ण

अटल व्योम iwl_trans_pcie_ग_लिखो_prph(काष्ठा iwl_trans *trans, u32 addr,
				      u32 val)
अणु
	u32 mask = iwl_trans_pcie_prph_msk(trans);

	iwl_trans_pcie_ग_लिखो32(trans, HBUS_TARG_PRPH_WADDR,
			       ((addr & mask) | (3 << 24)));
	iwl_trans_pcie_ग_लिखो32(trans, HBUS_TARG_PRPH_WDAT, val);
पूर्ण

अटल व्योम iwl_trans_pcie_configure(काष्ठा iwl_trans *trans,
				     स्थिर काष्ठा iwl_trans_config *trans_cfg)
अणु
	काष्ठा iwl_trans_pcie *trans_pcie = IWL_TRANS_GET_PCIE_TRANS(trans);

	trans->txqs.cmd.q_id = trans_cfg->cmd_queue;
	trans->txqs.cmd.fअगरo = trans_cfg->cmd_fअगरo;
	trans->txqs.cmd.wdg_समयout = trans_cfg->cmd_q_wdg_समयout;
	trans->txqs.page_offs = trans_cfg->cb_data_offs;
	trans->txqs.dev_cmd_offs = trans_cfg->cb_data_offs + माप(व्योम *);

	अगर (WARN_ON(trans_cfg->n_no_reclaim_cmds > MAX_NO_RECLAIM_CMDS))
		trans_pcie->n_no_reclaim_cmds = 0;
	अन्यथा
		trans_pcie->n_no_reclaim_cmds = trans_cfg->n_no_reclaim_cmds;
	अगर (trans_pcie->n_no_reclaim_cmds)
		स_नकल(trans_pcie->no_reclaim_cmds, trans_cfg->no_reclaim_cmds,
		       trans_pcie->n_no_reclaim_cmds * माप(u8));

	trans_pcie->rx_buf_size = trans_cfg->rx_buf_size;
	trans_pcie->rx_page_order =
		iwl_trans_get_rb_size_order(trans_pcie->rx_buf_size);
	trans_pcie->rx_buf_bytes =
		iwl_trans_get_rb_size(trans_pcie->rx_buf_size);
	trans_pcie->supported_dma_mask = DMA_BIT_MASK(12);
	अगर (trans->trans_cfg->device_family >= IWL_DEVICE_FAMILY_AX210)
		trans_pcie->supported_dma_mask = DMA_BIT_MASK(11);

	trans->txqs.bc_table_dword = trans_cfg->bc_table_dword;
	trans_pcie->scd_set_active = trans_cfg->scd_set_active;

	trans->command_groups = trans_cfg->command_groups;
	trans->command_groups_size = trans_cfg->command_groups_size;

	/* Initialize NAPI here - it should be beक्रमe रेजिस्टरing to mac80211
	 * in the opmode but after the HW काष्ठा is allocated.
	 * As this function may be called again in some corner हालs करोn't
	 * करो anything अगर NAPI was alपढ़ोy initialized.
	 */
	अगर (trans_pcie->napi_dev.reg_state != NETREG_DUMMY)
		init_dummy_netdev(&trans_pcie->napi_dev);

	trans_pcie->fw_reset_handshake = trans_cfg->fw_reset_handshake;
पूर्ण

व्योम iwl_trans_pcie_मुक्त(काष्ठा iwl_trans *trans)
अणु
	काष्ठा iwl_trans_pcie *trans_pcie = IWL_TRANS_GET_PCIE_TRANS(trans);
	पूर्णांक i;

	iwl_pcie_synchronize_irqs(trans);

	अगर (trans->trans_cfg->gen2)
		iwl_txq_gen2_tx_मुक्त(trans);
	अन्यथा
		iwl_pcie_tx_मुक्त(trans);
	iwl_pcie_rx_मुक्त(trans);

	अगर (trans_pcie->rba.alloc_wq) अणु
		destroy_workqueue(trans_pcie->rba.alloc_wq);
		trans_pcie->rba.alloc_wq = शून्य;
	पूर्ण

	अगर (trans_pcie->msix_enabled) अणु
		क्रम (i = 0; i < trans_pcie->alloc_vecs; i++) अणु
			irq_set_affinity_hपूर्णांक(
				trans_pcie->msix_entries[i].vector,
				शून्य);
		पूर्ण

		trans_pcie->msix_enabled = false;
	पूर्ण अन्यथा अणु
		iwl_pcie_मुक्त_ict(trans);
	पूर्ण

	iwl_pcie_मुक्त_fw_monitor(trans);

	अगर (trans_pcie->pnvm_dram.size)
		dma_मुक्त_coherent(trans->dev, trans_pcie->pnvm_dram.size,
				  trans_pcie->pnvm_dram.block,
				  trans_pcie->pnvm_dram.physical);

	mutex_destroy(&trans_pcie->mutex);
	iwl_trans_मुक्त(trans);
पूर्ण

अटल व्योम iwl_trans_pcie_set_pmi(काष्ठा iwl_trans *trans, bool state)
अणु
	अगर (state)
		set_bit(STATUS_TPOWER_PMI, &trans->status);
	अन्यथा
		clear_bit(STATUS_TPOWER_PMI, &trans->status);
पूर्ण

काष्ठा iwl_trans_pcie_removal अणु
	काष्ठा pci_dev *pdev;
	काष्ठा work_काष्ठा work;
पूर्ण;

अटल व्योम iwl_trans_pcie_removal_wk(काष्ठा work_काष्ठा *wk)
अणु
	काष्ठा iwl_trans_pcie_removal *removal =
		container_of(wk, काष्ठा iwl_trans_pcie_removal, work);
	काष्ठा pci_dev *pdev = removal->pdev;
	अटल अक्षर *prop[] = अणु"EVENT=INACCESSIBLE", शून्यपूर्ण;

	dev_err(&pdev->dev, "Device gone - attempting removal\n");
	kobject_uevent_env(&pdev->dev.kobj, KOBJ_CHANGE, prop);
	pci_lock_rescan_हटाओ();
	pci_dev_put(pdev);
	pci_stop_and_हटाओ_bus_device(pdev);
	pci_unlock_rescan_हटाओ();

	kमुक्त(removal);
	module_put(THIS_MODULE);
पूर्ण

/*
 * This version करोesn't disable BHs but rather assumes they're
 * alपढ़ोy disabled.
 */
bool __iwl_trans_pcie_grab_nic_access(काष्ठा iwl_trans *trans)
अणु
	पूर्णांक ret;
	काष्ठा iwl_trans_pcie *trans_pcie = IWL_TRANS_GET_PCIE_TRANS(trans);

	spin_lock(&trans_pcie->reg_lock);

	अगर (trans_pcie->cmd_hold_nic_awake)
		जाओ out;

	/* this bit wakes up the NIC */
	__iwl_trans_pcie_set_bit(trans, CSR_GP_CNTRL,
				 CSR_GP_CNTRL_REG_FLAG_MAC_ACCESS_REQ);
	अगर (trans->trans_cfg->device_family >= IWL_DEVICE_FAMILY_8000)
		udelay(2);

	/*
	 * These bits say the device is running, and should keep running क्रम
	 * at least a लघु जबतक (at least as दीर्घ as MAC_ACCESS_REQ stays 1),
	 * but they करो not indicate that embedded SRAM is restored yet;
	 * HW with अस्थिर SRAM must save/restore contents to/from
	 * host DRAM when sleeping/waking क्रम घातer-saving.
	 * Each direction takes approximately 1/4 millisecond; with this
	 * overhead, it's a good idea to grab and hold MAC_ACCESS_REQUEST अगर a
	 * series of रेजिस्टर accesses are expected (e.g. पढ़ोing Event Log),
	 * to keep device from sleeping.
	 *
	 * CSR_UCODE_DRV_GP1 रेजिस्टर bit MAC_SLEEP == 0 indicates that
	 * SRAM is okay/restored.  We करोn't check that here because this call
	 * is just क्रम hardware रेजिस्टर access; but GP1 MAC_SLEEP
	 * check is a good idea beक्रमe accessing the SRAM of HW with
	 * अस्थिर SRAM (e.g. पढ़ोing Event Log).
	 *
	 * 5000 series and later (including 1000 series) have non-अस्थिर SRAM,
	 * and करो not save/restore SRAM when घातer cycling.
	 */
	ret = iwl_poll_bit(trans, CSR_GP_CNTRL,
			   CSR_GP_CNTRL_REG_VAL_MAC_ACCESS_EN,
			   (CSR_GP_CNTRL_REG_FLAG_MAC_CLOCK_READY |
			    CSR_GP_CNTRL_REG_FLAG_GOING_TO_SLEEP), 15000);
	अगर (unlikely(ret < 0)) अणु
		u32 cntrl = iwl_पढ़ो32(trans, CSR_GP_CNTRL);

		WARN_ONCE(1,
			  "Timeout waiting for hardware access (CSR_GP_CNTRL 0x%08x)\n",
			  cntrl);

		iwl_trans_pcie_dump_regs(trans);

		अगर (iwlwअगरi_mod_params.हटाओ_when_gone && cntrl == ~0U) अणु
			काष्ठा iwl_trans_pcie_removal *removal;

			अगर (test_bit(STATUS_TRANS_DEAD, &trans->status))
				जाओ err;

			IWL_ERR(trans, "Device gone - scheduling removal!\n");

			/*
			 * get a module reference to aव्योम करोing this
			 * जबतक unloading anyway and to aव्योम
			 * scheduling a work with code that's being
			 * हटाओd.
			 */
			अगर (!try_module_get(THIS_MODULE)) अणु
				IWL_ERR(trans,
					"Module is being unloaded - abort\n");
				जाओ err;
			पूर्ण

			removal = kzalloc(माप(*removal), GFP_ATOMIC);
			अगर (!removal) अणु
				module_put(THIS_MODULE);
				जाओ err;
			पूर्ण
			/*
			 * we करोn't need to clear this flag, because
			 * the trans will be मुक्तd and पुनः_स्मृतिated.
			*/
			set_bit(STATUS_TRANS_DEAD, &trans->status);

			removal->pdev = to_pci_dev(trans->dev);
			INIT_WORK(&removal->work, iwl_trans_pcie_removal_wk);
			pci_dev_get(removal->pdev);
			schedule_work(&removal->work);
		पूर्ण अन्यथा अणु
			iwl_ग_लिखो32(trans, CSR_RESET,
				    CSR_RESET_REG_FLAG_FORCE_NMI);
		पूर्ण

err:
		spin_unlock(&trans_pcie->reg_lock);
		वापस false;
	पूर्ण

out:
	/*
	 * Fool sparse by faking we release the lock - sparse will
	 * track nic_access anyway.
	 */
	__release(&trans_pcie->reg_lock);
	वापस true;
पूर्ण

अटल bool iwl_trans_pcie_grab_nic_access(काष्ठा iwl_trans *trans)
अणु
	bool ret;

	local_bh_disable();
	ret = __iwl_trans_pcie_grab_nic_access(trans);
	अगर (ret) अणु
		/* keep BHs disabled until iwl_trans_pcie_release_nic_access */
		वापस ret;
	पूर्ण
	local_bh_enable();
	वापस false;
पूर्ण

अटल व्योम iwl_trans_pcie_release_nic_access(काष्ठा iwl_trans *trans)
अणु
	काष्ठा iwl_trans_pcie *trans_pcie = IWL_TRANS_GET_PCIE_TRANS(trans);

	lockdep_निश्चित_held(&trans_pcie->reg_lock);

	/*
	 * Fool sparse by faking we acquiring the lock - sparse will
	 * track nic_access anyway.
	 */
	__acquire(&trans_pcie->reg_lock);

	अगर (trans_pcie->cmd_hold_nic_awake)
		जाओ out;

	__iwl_trans_pcie_clear_bit(trans, CSR_GP_CNTRL,
				   CSR_GP_CNTRL_REG_FLAG_MAC_ACCESS_REQ);
	/*
	 * Above we पढ़ो the CSR_GP_CNTRL रेजिस्टर, which will flush
	 * any previous ग_लिखोs, but we need the ग_लिखो that clears the
	 * MAC_ACCESS_REQ bit to be perक्रमmed beक्रमe any other ग_लिखोs
	 * scheduled on dअगरferent CPUs (after we drop reg_lock).
	 */
out:
	spin_unlock_bh(&trans_pcie->reg_lock);
पूर्ण

अटल पूर्णांक iwl_trans_pcie_पढ़ो_mem(काष्ठा iwl_trans *trans, u32 addr,
				   व्योम *buf, पूर्णांक dwords)
अणु
	पूर्णांक offs = 0;
	u32 *vals = buf;

	जबतक (offs < dwords) अणु
		/* limit the समय we spin here under lock to 1/2s */
		अचिन्हित दीर्घ end = jअगरfies + HZ / 2;
		bool resched = false;

		अगर (iwl_trans_grab_nic_access(trans)) अणु
			iwl_ग_लिखो32(trans, HBUS_TARG_MEM_RADDR,
				    addr + 4 * offs);

			जबतक (offs < dwords) अणु
				vals[offs] = iwl_पढ़ो32(trans,
							HBUS_TARG_MEM_RDAT);
				offs++;

				अगर (समय_after(jअगरfies, end)) अणु
					resched = true;
					अवरोध;
				पूर्ण
			पूर्ण
			iwl_trans_release_nic_access(trans);

			अगर (resched)
				cond_resched();
		पूर्ण अन्यथा अणु
			वापस -EBUSY;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक iwl_trans_pcie_ग_लिखो_mem(काष्ठा iwl_trans *trans, u32 addr,
				    स्थिर व्योम *buf, पूर्णांक dwords)
अणु
	पूर्णांक offs, ret = 0;
	स्थिर u32 *vals = buf;

	अगर (iwl_trans_grab_nic_access(trans)) अणु
		iwl_ग_लिखो32(trans, HBUS_TARG_MEM_WADDR, addr);
		क्रम (offs = 0; offs < dwords; offs++)
			iwl_ग_लिखो32(trans, HBUS_TARG_MEM_WDAT,
				    vals ? vals[offs] : 0);
		iwl_trans_release_nic_access(trans);
	पूर्ण अन्यथा अणु
		ret = -EBUSY;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक iwl_trans_pcie_पढ़ो_config32(काष्ठा iwl_trans *trans, u32 ofs,
					u32 *val)
अणु
	वापस pci_पढ़ो_config_dword(IWL_TRANS_GET_PCIE_TRANS(trans)->pci_dev,
				     ofs, val);
पूर्ण

अटल व्योम iwl_trans_pcie_block_txq_ptrs(काष्ठा iwl_trans *trans, bool block)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < trans->trans_cfg->base_params->num_of_queues; i++) अणु
		काष्ठा iwl_txq *txq = trans->txqs.txq[i];

		अगर (i == trans->txqs.cmd.q_id)
			जारी;

		spin_lock_bh(&txq->lock);

		अगर (!block && !(WARN_ON_ONCE(!txq->block))) अणु
			txq->block--;
			अगर (!txq->block) अणु
				iwl_ग_लिखो32(trans, HBUS_TARG_WRPTR,
					    txq->ग_लिखो_ptr | (i << 8));
			पूर्ण
		पूर्ण अन्यथा अगर (block) अणु
			txq->block++;
		पूर्ण

		spin_unlock_bh(&txq->lock);
	पूर्ण
पूर्ण

#घोषणा IWL_FLUSH_WAIT_MS	2000

अटल पूर्णांक iwl_trans_pcie_rxq_dma_data(काष्ठा iwl_trans *trans, पूर्णांक queue,
				       काष्ठा iwl_trans_rxq_dma_data *data)
अणु
	काष्ठा iwl_trans_pcie *trans_pcie = IWL_TRANS_GET_PCIE_TRANS(trans);

	अगर (queue >= trans->num_rx_queues || !trans_pcie->rxq)
		वापस -EINVAL;

	data->fr_bd_cb = trans_pcie->rxq[queue].bd_dma;
	data->urbd_stts_wrptr = trans_pcie->rxq[queue].rb_stts_dma;
	data->ur_bd_cb = trans_pcie->rxq[queue].used_bd_dma;
	data->fr_bd_wid = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक iwl_trans_pcie_रुको_txq_empty(काष्ठा iwl_trans *trans, पूर्णांक txq_idx)
अणु
	काष्ठा iwl_txq *txq;
	अचिन्हित दीर्घ now = jअगरfies;
	bool overflow_tx;
	u8 wr_ptr;

	/* Make sure the NIC is still alive in the bus */
	अगर (test_bit(STATUS_TRANS_DEAD, &trans->status))
		वापस -ENODEV;

	अगर (!test_bit(txq_idx, trans->txqs.queue_used))
		वापस -EINVAL;

	IWL_DEBUG_TX_QUEUES(trans, "Emptying queue %d...\n", txq_idx);
	txq = trans->txqs.txq[txq_idx];

	spin_lock_bh(&txq->lock);
	overflow_tx = txq->overflow_tx ||
		      !skb_queue_empty(&txq->overflow_q);
	spin_unlock_bh(&txq->lock);

	wr_ptr = READ_ONCE(txq->ग_लिखो_ptr);

	जबतक ((txq->पढ़ो_ptr != READ_ONCE(txq->ग_लिखो_ptr) ||
		overflow_tx) &&
	       !समय_after(jअगरfies,
			   now + msecs_to_jअगरfies(IWL_FLUSH_WAIT_MS))) अणु
		u8 ग_लिखो_ptr = READ_ONCE(txq->ग_लिखो_ptr);

		/*
		 * If ग_लिखो poपूर्णांकer moved during the रुको, warn only
		 * अगर the TX came from op mode. In हाल TX came from
		 * trans layer (overflow TX) करोn't warn.
		 */
		अगर (WARN_ONCE(wr_ptr != ग_लिखो_ptr && !overflow_tx,
			      "WR pointer moved while flushing %d -> %d\n",
			      wr_ptr, ग_लिखो_ptr))
			वापस -ETIMEDOUT;
		wr_ptr = ग_लिखो_ptr;

		usleep_range(1000, 2000);

		spin_lock_bh(&txq->lock);
		overflow_tx = txq->overflow_tx ||
			      !skb_queue_empty(&txq->overflow_q);
		spin_unlock_bh(&txq->lock);
	पूर्ण

	अगर (txq->पढ़ो_ptr != txq->ग_लिखो_ptr) अणु
		IWL_ERR(trans,
			"fail to flush all tx fifo queues Q %d\n", txq_idx);
		iwl_txq_log_scd_error(trans, txq);
		वापस -ETIMEDOUT;
	पूर्ण

	IWL_DEBUG_TX_QUEUES(trans, "Queue %d is now empty.\n", txq_idx);

	वापस 0;
पूर्ण

अटल पूर्णांक iwl_trans_pcie_रुको_txqs_empty(काष्ठा iwl_trans *trans, u32 txq_bm)
अणु
	पूर्णांक cnt;
	पूर्णांक ret = 0;

	/* रुकोing क्रम all the tx frames complete might take a जबतक */
	क्रम (cnt = 0;
	     cnt < trans->trans_cfg->base_params->num_of_queues;
	     cnt++) अणु

		अगर (cnt == trans->txqs.cmd.q_id)
			जारी;
		अगर (!test_bit(cnt, trans->txqs.queue_used))
			जारी;
		अगर (!(BIT(cnt) & txq_bm))
			जारी;

		ret = iwl_trans_pcie_रुको_txq_empty(trans, cnt);
		अगर (ret)
			अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम iwl_trans_pcie_set_bits_mask(काष्ठा iwl_trans *trans, u32 reg,
					 u32 mask, u32 value)
अणु
	काष्ठा iwl_trans_pcie *trans_pcie = IWL_TRANS_GET_PCIE_TRANS(trans);

	spin_lock_bh(&trans_pcie->reg_lock);
	__iwl_trans_pcie_set_bits_mask(trans, reg, mask, value);
	spin_unlock_bh(&trans_pcie->reg_lock);
पूर्ण

अटल स्थिर अक्षर *get_csr_string(पूर्णांक cmd)
अणु
#घोषणा IWL_CMD(x) हाल x: वापस #x
	चयन (cmd) अणु
	IWL_CMD(CSR_HW_IF_CONFIG_REG);
	IWL_CMD(CSR_INT_COALESCING);
	IWL_CMD(CSR_INT);
	IWL_CMD(CSR_INT_MASK);
	IWL_CMD(CSR_FH_INT_STATUS);
	IWL_CMD(CSR_GPIO_IN);
	IWL_CMD(CSR_RESET);
	IWL_CMD(CSR_GP_CNTRL);
	IWL_CMD(CSR_HW_REV);
	IWL_CMD(CSR_EEPROM_REG);
	IWL_CMD(CSR_EEPROM_GP);
	IWL_CMD(CSR_OTP_GP_REG);
	IWL_CMD(CSR_GIO_REG);
	IWL_CMD(CSR_GP_UCODE_REG);
	IWL_CMD(CSR_GP_DRIVER_REG);
	IWL_CMD(CSR_UCODE_DRV_GP1);
	IWL_CMD(CSR_UCODE_DRV_GP2);
	IWL_CMD(CSR_LED_REG);
	IWL_CMD(CSR_DRAM_INT_TBL_REG);
	IWL_CMD(CSR_GIO_CHICKEN_BITS);
	IWL_CMD(CSR_ANA_PLL_CFG);
	IWL_CMD(CSR_HW_REV_WA_REG);
	IWL_CMD(CSR_MONITOR_STATUS_REG);
	IWL_CMD(CSR_DBG_HPET_MEM_REG);
	शेष:
		वापस "UNKNOWN";
	पूर्ण
#अघोषित IWL_CMD
पूर्ण

व्योम iwl_pcie_dump_csr(काष्ठा iwl_trans *trans)
अणु
	पूर्णांक i;
	अटल स्थिर u32 csr_tbl[] = अणु
		CSR_HW_IF_CONFIG_REG,
		CSR_INT_COALESCING,
		CSR_INT,
		CSR_INT_MASK,
		CSR_FH_INT_STATUS,
		CSR_GPIO_IN,
		CSR_RESET,
		CSR_GP_CNTRL,
		CSR_HW_REV,
		CSR_EEPROM_REG,
		CSR_EEPROM_GP,
		CSR_OTP_GP_REG,
		CSR_GIO_REG,
		CSR_GP_UCODE_REG,
		CSR_GP_DRIVER_REG,
		CSR_UCODE_DRV_GP1,
		CSR_UCODE_DRV_GP2,
		CSR_LED_REG,
		CSR_DRAM_INT_TBL_REG,
		CSR_GIO_CHICKEN_BITS,
		CSR_ANA_PLL_CFG,
		CSR_MONITOR_STATUS_REG,
		CSR_HW_REV_WA_REG,
		CSR_DBG_HPET_MEM_REG
	पूर्ण;
	IWL_ERR(trans, "CSR values:\n");
	IWL_ERR(trans, "(2nd byte of CSR_INT_COALESCING is "
		"CSR_INT_PERIODIC_REG)\n");
	क्रम (i = 0; i <  ARRAY_SIZE(csr_tbl); i++) अणु
		IWL_ERR(trans, "  %25s: 0X%08x\n",
			get_csr_string(csr_tbl[i]),
			iwl_पढ़ो32(trans, csr_tbl[i]));
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_IWLWIFI_DEBUGFS
/* create and हटाओ of files */
#घोषणा DEBUGFS_ADD_खाता(name, parent, mode) करो अणु			\
	debugfs_create_file(#name, mode, parent, trans,			\
			    &iwl_dbgfs_##name##_ops);			\
पूर्ण जबतक (0)

/* file operation */
#घोषणा DEBUGFS_READ_खाता_OPS(name)					\
अटल स्थिर काष्ठा file_operations iwl_dbgfs_##name##_ops = अणु		\
	.पढ़ो = iwl_dbgfs_##name##_पढ़ो,				\
	.खोलो = simple_खोलो,						\
	.llseek = generic_file_llseek,					\
पूर्ण;

#घोषणा DEBUGFS_WRITE_खाता_OPS(name)                                    \
अटल स्थिर काष्ठा file_operations iwl_dbgfs_##name##_ops = अणु          \
	.ग_लिखो = iwl_dbgfs_##name##_ग_लिखो,                              \
	.खोलो = simple_खोलो,						\
	.llseek = generic_file_llseek,					\
पूर्ण;

#घोषणा DEBUGFS_READ_WRITE_खाता_OPS(name)				\
अटल स्थिर काष्ठा file_operations iwl_dbgfs_##name##_ops = अणु		\
	.ग_लिखो = iwl_dbgfs_##name##_ग_लिखो,				\
	.पढ़ो = iwl_dbgfs_##name##_पढ़ो,				\
	.खोलो = simple_खोलो,						\
	.llseek = generic_file_llseek,					\
पूर्ण;

काष्ठा iwl_dbgfs_tx_queue_priv अणु
	काष्ठा iwl_trans *trans;
पूर्ण;

काष्ठा iwl_dbgfs_tx_queue_state अणु
	loff_t pos;
पूर्ण;

अटल व्योम *iwl_dbgfs_tx_queue_seq_start(काष्ठा seq_file *seq, loff_t *pos)
अणु
	काष्ठा iwl_dbgfs_tx_queue_priv *priv = seq->निजी;
	काष्ठा iwl_dbgfs_tx_queue_state *state;

	अगर (*pos >= priv->trans->trans_cfg->base_params->num_of_queues)
		वापस शून्य;

	state = kदो_स्मृति(माप(*state), GFP_KERNEL);
	अगर (!state)
		वापस शून्य;
	state->pos = *pos;
	वापस state;
पूर्ण

अटल व्योम *iwl_dbgfs_tx_queue_seq_next(काष्ठा seq_file *seq,
					 व्योम *v, loff_t *pos)
अणु
	काष्ठा iwl_dbgfs_tx_queue_priv *priv = seq->निजी;
	काष्ठा iwl_dbgfs_tx_queue_state *state = v;

	*pos = ++state->pos;

	अगर (*pos >= priv->trans->trans_cfg->base_params->num_of_queues)
		वापस शून्य;

	वापस state;
पूर्ण

अटल व्योम iwl_dbgfs_tx_queue_seq_stop(काष्ठा seq_file *seq, व्योम *v)
अणु
	kमुक्त(v);
पूर्ण

अटल पूर्णांक iwl_dbgfs_tx_queue_seq_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा iwl_dbgfs_tx_queue_priv *priv = seq->निजी;
	काष्ठा iwl_dbgfs_tx_queue_state *state = v;
	काष्ठा iwl_trans *trans = priv->trans;
	काष्ठा iwl_txq *txq = trans->txqs.txq[state->pos];

	seq_म_लिखो(seq, "hwq %.3u: used=%d stopped=%d ",
		   (अचिन्हित पूर्णांक)state->pos,
		   !!test_bit(state->pos, trans->txqs.queue_used),
		   !!test_bit(state->pos, trans->txqs.queue_stopped));
	अगर (txq)
		seq_म_लिखो(seq,
			   "read=%u write=%u need_update=%d frozen=%d n_window=%d ampdu=%d",
			   txq->पढ़ो_ptr, txq->ग_लिखो_ptr,
			   txq->need_update, txq->frozen,
			   txq->n_winकरोw, txq->ampdu);
	अन्यथा
		seq_माला_दो(seq, "(unallocated)");

	अगर (state->pos == trans->txqs.cmd.q_id)
		seq_माला_दो(seq, " (HCMD)");
	seq_माला_दो(seq, "\n");

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा seq_operations iwl_dbgfs_tx_queue_seq_ops = अणु
	.start = iwl_dbgfs_tx_queue_seq_start,
	.next = iwl_dbgfs_tx_queue_seq_next,
	.stop = iwl_dbgfs_tx_queue_seq_stop,
	.show = iwl_dbgfs_tx_queue_seq_show,
पूर्ण;

अटल पूर्णांक iwl_dbgfs_tx_queue_खोलो(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा iwl_dbgfs_tx_queue_priv *priv;

	priv = __seq_खोलो_निजी(filp, &iwl_dbgfs_tx_queue_seq_ops,
				  माप(*priv));

	अगर (!priv)
		वापस -ENOMEM;

	priv->trans = inode->i_निजी;
	वापस 0;
पूर्ण

अटल sमाप_प्रकार iwl_dbgfs_rx_queue_पढ़ो(काष्ठा file *file,
				       अक्षर __user *user_buf,
				       माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा iwl_trans *trans = file->निजी_data;
	काष्ठा iwl_trans_pcie *trans_pcie = IWL_TRANS_GET_PCIE_TRANS(trans);
	अक्षर *buf;
	पूर्णांक pos = 0, i, ret;
	माप_प्रकार bufsz;

	bufsz = माप(अक्षर) * 121 * trans->num_rx_queues;

	अगर (!trans_pcie->rxq)
		वापस -EAGAIN;

	buf = kzalloc(bufsz, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	क्रम (i = 0; i < trans->num_rx_queues && pos < bufsz; i++) अणु
		काष्ठा iwl_rxq *rxq = &trans_pcie->rxq[i];

		pos += scnम_लिखो(buf + pos, bufsz - pos, "queue#: %2d\n",
				 i);
		pos += scnम_लिखो(buf + pos, bufsz - pos, "\tread: %u\n",
				 rxq->पढ़ो);
		pos += scnम_लिखो(buf + pos, bufsz - pos, "\twrite: %u\n",
				 rxq->ग_लिखो);
		pos += scnम_लिखो(buf + pos, bufsz - pos, "\twrite_actual: %u\n",
				 rxq->ग_लिखो_actual);
		pos += scnम_लिखो(buf + pos, bufsz - pos, "\tneed_update: %2d\n",
				 rxq->need_update);
		pos += scnम_लिखो(buf + pos, bufsz - pos, "\tfree_count: %u\n",
				 rxq->मुक्त_count);
		अगर (rxq->rb_stts) अणु
			u32 r =	__le16_to_cpu(iwl_get_बंदd_rb_stts(trans,
								     rxq));
			pos += scnम_लिखो(buf + pos, bufsz - pos,
					 "\tclosed_rb_num: %u\n",
					 r & 0x0FFF);
		पूर्ण अन्यथा अणु
			pos += scnम_लिखो(buf + pos, bufsz - pos,
					 "\tclosed_rb_num: Not Allocated\n");
		पूर्ण
	पूर्ण
	ret = simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, pos);
	kमुक्त(buf);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार iwl_dbgfs_पूर्णांकerrupt_पढ़ो(काष्ठा file *file,
					अक्षर __user *user_buf,
					माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा iwl_trans *trans = file->निजी_data;
	काष्ठा iwl_trans_pcie *trans_pcie = IWL_TRANS_GET_PCIE_TRANS(trans);
	काष्ठा isr_statistics *isr_stats = &trans_pcie->isr_stats;

	पूर्णांक pos = 0;
	अक्षर *buf;
	पूर्णांक bufsz = 24 * 64; /* 24 items * 64 अक्षर per item */
	sमाप_प्रकार ret;

	buf = kzalloc(bufsz, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	pos += scnम_लिखो(buf + pos, bufsz - pos,
			"Interrupt Statistics Report:\n");

	pos += scnम_लिखो(buf + pos, bufsz - pos, "HW Error:\t\t\t %u\n",
		isr_stats->hw);
	pos += scnम_लिखो(buf + pos, bufsz - pos, "SW Error:\t\t\t %u\n",
		isr_stats->sw);
	अगर (isr_stats->sw || isr_stats->hw) अणु
		pos += scnम_लिखो(buf + pos, bufsz - pos,
			"\tLast Restarting Code:  0x%X\n",
			isr_stats->err_code);
	पूर्ण
#अगर_घोषित CONFIG_IWLWIFI_DEBUG
	pos += scnम_लिखो(buf + pos, bufsz - pos, "Frame transmitted:\t\t %u\n",
		isr_stats->sch);
	pos += scnम_लिखो(buf + pos, bufsz - pos, "Alive interrupt:\t\t %u\n",
		isr_stats->alive);
#पूर्ण_अगर
	pos += scnम_लिखो(buf + pos, bufsz - pos,
		"HW RF KILL switch toggled:\t %u\n", isr_stats->rfसमाप्त);

	pos += scnम_लिखो(buf + pos, bufsz - pos, "CT KILL:\t\t\t %u\n",
		isr_stats->ctसमाप्त);

	pos += scnम_लिखो(buf + pos, bufsz - pos, "Wakeup Interrupt:\t\t %u\n",
		isr_stats->wakeup);

	pos += scnम_लिखो(buf + pos, bufsz - pos,
		"Rx command responses:\t\t %u\n", isr_stats->rx);

	pos += scnम_लिखो(buf + pos, bufsz - pos, "Tx/FH interrupt:\t\t %u\n",
		isr_stats->tx);

	pos += scnम_लिखो(buf + pos, bufsz - pos, "Unexpected INTA:\t\t %u\n",
		isr_stats->unhandled);

	ret = simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, pos);
	kमुक्त(buf);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार iwl_dbgfs_पूर्णांकerrupt_ग_लिखो(काष्ठा file *file,
					 स्थिर अक्षर __user *user_buf,
					 माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा iwl_trans *trans = file->निजी_data;
	काष्ठा iwl_trans_pcie *trans_pcie = IWL_TRANS_GET_PCIE_TRANS(trans);
	काष्ठा isr_statistics *isr_stats = &trans_pcie->isr_stats;
	u32 reset_flag;
	पूर्णांक ret;

	ret = kstrtou32_from_user(user_buf, count, 16, &reset_flag);
	अगर (ret)
		वापस ret;
	अगर (reset_flag == 0)
		स_रखो(isr_stats, 0, माप(*isr_stats));

	वापस count;
पूर्ण

अटल sमाप_प्रकार iwl_dbgfs_csr_ग_लिखो(काष्ठा file *file,
				   स्थिर अक्षर __user *user_buf,
				   माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा iwl_trans *trans = file->निजी_data;

	iwl_pcie_dump_csr(trans);

	वापस count;
पूर्ण

अटल sमाप_प्रकार iwl_dbgfs_fh_reg_पढ़ो(काष्ठा file *file,
				     अक्षर __user *user_buf,
				     माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा iwl_trans *trans = file->निजी_data;
	अक्षर *buf = शून्य;
	sमाप_प्रकार ret;

	ret = iwl_dump_fh(trans, &buf);
	अगर (ret < 0)
		वापस ret;
	अगर (!buf)
		वापस -EINVAL;
	ret = simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, ret);
	kमुक्त(buf);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार iwl_dbgfs_rfसमाप्त_पढ़ो(काष्ठा file *file,
				     अक्षर __user *user_buf,
				     माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा iwl_trans *trans = file->निजी_data;
	काष्ठा iwl_trans_pcie *trans_pcie = IWL_TRANS_GET_PCIE_TRANS(trans);
	अक्षर buf[100];
	पूर्णांक pos;

	pos = scnम_लिखो(buf, माप(buf), "debug: %d\nhw: %d\n",
			trans_pcie->debug_rfसमाप्त,
			!(iwl_पढ़ो32(trans, CSR_GP_CNTRL) &
				CSR_GP_CNTRL_REG_FLAG_HW_RF_KILL_SW));

	वापस simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, pos);
पूर्ण

अटल sमाप_प्रकार iwl_dbgfs_rfसमाप्त_ग_लिखो(काष्ठा file *file,
				      स्थिर अक्षर __user *user_buf,
				      माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा iwl_trans *trans = file->निजी_data;
	काष्ठा iwl_trans_pcie *trans_pcie = IWL_TRANS_GET_PCIE_TRANS(trans);
	bool new_value;
	पूर्णांक ret;

	ret = kstrtobool_from_user(user_buf, count, &new_value);
	अगर (ret)
		वापस ret;
	अगर (new_value == trans_pcie->debug_rfसमाप्त)
		वापस count;
	IWL_WARN(trans, "changing debug rfkill %d->%d\n",
		 trans_pcie->debug_rfसमाप्त, new_value);
	trans_pcie->debug_rfसमाप्त = new_value;
	iwl_pcie_handle_rfसमाप्त_irq(trans);

	वापस count;
पूर्ण

अटल पूर्णांक iwl_dbgfs_monitor_data_खोलो(काष्ठा inode *inode,
				       काष्ठा file *file)
अणु
	काष्ठा iwl_trans *trans = inode->i_निजी;
	काष्ठा iwl_trans_pcie *trans_pcie = IWL_TRANS_GET_PCIE_TRANS(trans);

	अगर (!trans->dbg.dest_tlv ||
	    trans->dbg.dest_tlv->monitor_mode != EXTERNAL_MODE) अणु
		IWL_ERR(trans, "Debug destination is not set to DRAM\n");
		वापस -ENOENT;
	पूर्ण

	अगर (trans_pcie->fw_mon_data.state != IWL_FW_MON_DBGFS_STATE_CLOSED)
		वापस -EBUSY;

	trans_pcie->fw_mon_data.state = IWL_FW_MON_DBGFS_STATE_OPEN;
	वापस simple_खोलो(inode, file);
पूर्ण

अटल पूर्णांक iwl_dbgfs_monitor_data_release(काष्ठा inode *inode,
					  काष्ठा file *file)
अणु
	काष्ठा iwl_trans_pcie *trans_pcie =
		IWL_TRANS_GET_PCIE_TRANS(inode->i_निजी);

	अगर (trans_pcie->fw_mon_data.state == IWL_FW_MON_DBGFS_STATE_OPEN)
		trans_pcie->fw_mon_data.state = IWL_FW_MON_DBGFS_STATE_CLOSED;
	वापस 0;
पूर्ण

अटल bool iwl_ग_लिखो_to_user_buf(अक्षर __user *user_buf, sमाप_प्रकार count,
				  व्योम *buf, sमाप_प्रकार *size,
				  sमाप_प्रकार *bytes_copied)
अणु
	पूर्णांक buf_size_left = count - *bytes_copied;

	buf_size_left = buf_size_left - (buf_size_left % माप(u32));
	अगर (*size > buf_size_left)
		*size = buf_size_left;

	*size -= copy_to_user(user_buf, buf, *size);
	*bytes_copied += *size;

	अगर (buf_size_left == *size)
		वापस true;
	वापस false;
पूर्ण

अटल sमाप_प्रकार iwl_dbgfs_monitor_data_पढ़ो(काष्ठा file *file,
					   अक्षर __user *user_buf,
					   माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा iwl_trans *trans = file->निजी_data;
	काष्ठा iwl_trans_pcie *trans_pcie = IWL_TRANS_GET_PCIE_TRANS(trans);
	व्योम *cpu_addr = (व्योम *)trans->dbg.fw_mon.block, *curr_buf;
	काष्ठा cont_rec *data = &trans_pcie->fw_mon_data;
	u32 ग_लिखो_ptr_addr, wrap_cnt_addr, ग_लिखो_ptr, wrap_cnt;
	sमाप_प्रकार size, bytes_copied = 0;
	bool b_full;

	अगर (trans->dbg.dest_tlv) अणु
		ग_लिखो_ptr_addr =
			le32_to_cpu(trans->dbg.dest_tlv->ग_लिखो_ptr_reg);
		wrap_cnt_addr = le32_to_cpu(trans->dbg.dest_tlv->wrap_count);
	पूर्ण अन्यथा अणु
		ग_लिखो_ptr_addr = MON_BUFF_WRPTR;
		wrap_cnt_addr = MON_BUFF_CYCLE_CNT;
	पूर्ण

	अगर (unlikely(!trans->dbg.rec_on))
		वापस 0;

	mutex_lock(&data->mutex);
	अगर (data->state ==
	    IWL_FW_MON_DBGFS_STATE_DISABLED) अणु
		mutex_unlock(&data->mutex);
		वापस 0;
	पूर्ण

	/* ग_लिखो_ptr position in bytes rather then DW */
	ग_लिखो_ptr = iwl_पढ़ो_prph(trans, ग_लिखो_ptr_addr) * माप(u32);
	wrap_cnt = iwl_पढ़ो_prph(trans, wrap_cnt_addr);

	अगर (data->prev_wrap_cnt == wrap_cnt) अणु
		size = ग_लिखो_ptr - data->prev_wr_ptr;
		curr_buf = cpu_addr + data->prev_wr_ptr;
		b_full = iwl_ग_लिखो_to_user_buf(user_buf, count,
					       curr_buf, &size,
					       &bytes_copied);
		data->prev_wr_ptr += size;

	पूर्ण अन्यथा अगर (data->prev_wrap_cnt == wrap_cnt - 1 &&
		   ग_लिखो_ptr < data->prev_wr_ptr) अणु
		size = trans->dbg.fw_mon.size - data->prev_wr_ptr;
		curr_buf = cpu_addr + data->prev_wr_ptr;
		b_full = iwl_ग_लिखो_to_user_buf(user_buf, count,
					       curr_buf, &size,
					       &bytes_copied);
		data->prev_wr_ptr += size;

		अगर (!b_full) अणु
			size = ग_लिखो_ptr;
			b_full = iwl_ग_लिखो_to_user_buf(user_buf, count,
						       cpu_addr, &size,
						       &bytes_copied);
			data->prev_wr_ptr = size;
			data->prev_wrap_cnt++;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (data->prev_wrap_cnt == wrap_cnt - 1 &&
		    ग_लिखो_ptr > data->prev_wr_ptr)
			IWL_WARN(trans,
				 "write pointer passed previous write pointer, start copying from the beginning\n");
		अन्यथा अगर (!unlikely(data->prev_wrap_cnt == 0 &&
				   data->prev_wr_ptr == 0))
			IWL_WARN(trans,
				 "monitor data is out of sync, start copying from the beginning\n");

		size = ग_लिखो_ptr;
		b_full = iwl_ग_लिखो_to_user_buf(user_buf, count,
					       cpu_addr, &size,
					       &bytes_copied);
		data->prev_wr_ptr = size;
		data->prev_wrap_cnt = wrap_cnt;
	पूर्ण

	mutex_unlock(&data->mutex);

	वापस bytes_copied;
पूर्ण

DEBUGFS_READ_WRITE_खाता_OPS(पूर्णांकerrupt);
DEBUGFS_READ_खाता_OPS(fh_reg);
DEBUGFS_READ_खाता_OPS(rx_queue);
DEBUGFS_WRITE_खाता_OPS(csr);
DEBUGFS_READ_WRITE_खाता_OPS(rfसमाप्त);
अटल स्थिर काष्ठा file_operations iwl_dbgfs_tx_queue_ops = अणु
	.owner = THIS_MODULE,
	.खोलो = iwl_dbgfs_tx_queue_खोलो,
	.पढ़ो = seq_पढ़ो,
	.llseek = seq_lseek,
	.release = seq_release_निजी,
पूर्ण;

अटल स्थिर काष्ठा file_operations iwl_dbgfs_monitor_data_ops = अणु
	.पढ़ो = iwl_dbgfs_monitor_data_पढ़ो,
	.खोलो = iwl_dbgfs_monitor_data_खोलो,
	.release = iwl_dbgfs_monitor_data_release,
पूर्ण;

/* Create the debugfs files and directories */
व्योम iwl_trans_pcie_dbgfs_रेजिस्टर(काष्ठा iwl_trans *trans)
अणु
	काष्ठा dentry *dir = trans->dbgfs_dir;

	DEBUGFS_ADD_खाता(rx_queue, dir, 0400);
	DEBUGFS_ADD_खाता(tx_queue, dir, 0400);
	DEBUGFS_ADD_खाता(पूर्णांकerrupt, dir, 0600);
	DEBUGFS_ADD_खाता(csr, dir, 0200);
	DEBUGFS_ADD_खाता(fh_reg, dir, 0400);
	DEBUGFS_ADD_खाता(rfसमाप्त, dir, 0600);
	DEBUGFS_ADD_खाता(monitor_data, dir, 0400);
पूर्ण

अटल व्योम iwl_trans_pcie_debugfs_cleanup(काष्ठा iwl_trans *trans)
अणु
	काष्ठा iwl_trans_pcie *trans_pcie = IWL_TRANS_GET_PCIE_TRANS(trans);
	काष्ठा cont_rec *data = &trans_pcie->fw_mon_data;

	mutex_lock(&data->mutex);
	data->state = IWL_FW_MON_DBGFS_STATE_DISABLED;
	mutex_unlock(&data->mutex);
पूर्ण
#पूर्ण_अगर /*CONFIG_IWLWIFI_DEBUGFS */

अटल u32 iwl_trans_pcie_get_cmdlen(काष्ठा iwl_trans *trans, व्योम *tfd)
अणु
	u32 cmdlen = 0;
	पूर्णांक i;

	क्रम (i = 0; i < trans->txqs.tfd.max_tbs; i++)
		cmdlen += iwl_txq_gen1_tfd_tb_get_len(trans, tfd, i);

	वापस cmdlen;
पूर्ण

अटल u32 iwl_trans_pcie_dump_rbs(काष्ठा iwl_trans *trans,
				   काष्ठा iwl_fw_error_dump_data **data,
				   पूर्णांक allocated_rb_nums)
अणु
	काष्ठा iwl_trans_pcie *trans_pcie = IWL_TRANS_GET_PCIE_TRANS(trans);
	पूर्णांक max_len = trans_pcie->rx_buf_bytes;
	/* Dump RBs is supported only क्रम pre-9000 devices (1 queue) */
	काष्ठा iwl_rxq *rxq = &trans_pcie->rxq[0];
	u32 i, r, j, rb_len = 0;

	spin_lock(&rxq->lock);

	r = le16_to_cpu(iwl_get_बंदd_rb_stts(trans, rxq)) & 0x0FFF;

	क्रम (i = rxq->पढ़ो, j = 0;
	     i != r && j < allocated_rb_nums;
	     i = (i + 1) & RX_QUEUE_MASK, j++) अणु
		काष्ठा iwl_rx_mem_buffer *rxb = rxq->queue[i];
		काष्ठा iwl_fw_error_dump_rb *rb;

		dma_unmap_page(trans->dev, rxb->page_dma, max_len,
			       DMA_FROM_DEVICE);

		rb_len += माप(**data) + माप(*rb) + max_len;

		(*data)->type = cpu_to_le32(IWL_FW_ERROR_DUMP_RB);
		(*data)->len = cpu_to_le32(माप(*rb) + max_len);
		rb = (व्योम *)(*data)->data;
		rb->index = cpu_to_le32(i);
		स_नकल(rb->data, page_address(rxb->page), max_len);
		/* remap the page क्रम the मुक्त benefit */
		rxb->page_dma = dma_map_page(trans->dev, rxb->page,
					     rxb->offset, max_len,
					     DMA_FROM_DEVICE);

		*data = iwl_fw_error_next_data(*data);
	पूर्ण

	spin_unlock(&rxq->lock);

	वापस rb_len;
पूर्ण
#घोषणा IWL_CSR_TO_DUMP (0x250)

अटल u32 iwl_trans_pcie_dump_csr(काष्ठा iwl_trans *trans,
				   काष्ठा iwl_fw_error_dump_data **data)
अणु
	u32 csr_len = माप(**data) + IWL_CSR_TO_DUMP;
	__le32 *val;
	पूर्णांक i;

	(*data)->type = cpu_to_le32(IWL_FW_ERROR_DUMP_CSR);
	(*data)->len = cpu_to_le32(IWL_CSR_TO_DUMP);
	val = (व्योम *)(*data)->data;

	क्रम (i = 0; i < IWL_CSR_TO_DUMP; i += 4)
		*val++ = cpu_to_le32(iwl_trans_pcie_पढ़ो32(trans, i));

	*data = iwl_fw_error_next_data(*data);

	वापस csr_len;
पूर्ण

अटल u32 iwl_trans_pcie_fh_regs_dump(काष्ठा iwl_trans *trans,
				       काष्ठा iwl_fw_error_dump_data **data)
अणु
	u32 fh_regs_len = FH_MEM_UPPER_BOUND - FH_MEM_LOWER_BOUND;
	__le32 *val;
	पूर्णांक i;

	अगर (!iwl_trans_grab_nic_access(trans))
		वापस 0;

	(*data)->type = cpu_to_le32(IWL_FW_ERROR_DUMP_FH_REGS);
	(*data)->len = cpu_to_le32(fh_regs_len);
	val = (व्योम *)(*data)->data;

	अगर (!trans->trans_cfg->gen2)
		क्रम (i = FH_MEM_LOWER_BOUND; i < FH_MEM_UPPER_BOUND;
		     i += माप(u32))
			*val++ = cpu_to_le32(iwl_trans_pcie_पढ़ो32(trans, i));
	अन्यथा
		क्रम (i = iwl_umac_prph(trans, FH_MEM_LOWER_BOUND_GEN2);
		     i < iwl_umac_prph(trans, FH_MEM_UPPER_BOUND_GEN2);
		     i += माप(u32))
			*val++ = cpu_to_le32(iwl_trans_pcie_पढ़ो_prph(trans,
								      i));

	iwl_trans_release_nic_access(trans);

	*data = iwl_fw_error_next_data(*data);

	वापस माप(**data) + fh_regs_len;
पूर्ण

अटल u32
iwl_trans_pci_dump_marbh_monitor(काष्ठा iwl_trans *trans,
				 काष्ठा iwl_fw_error_dump_fw_mon *fw_mon_data,
				 u32 monitor_len)
अणु
	u32 buf_size_in_dwords = (monitor_len >> 2);
	u32 *buffer = (u32 *)fw_mon_data->data;
	u32 i;

	अगर (!iwl_trans_grab_nic_access(trans))
		वापस 0;

	iwl_ग_लिखो_umac_prph_no_grab(trans, MON_DMARB_RD_CTL_ADDR, 0x1);
	क्रम (i = 0; i < buf_size_in_dwords; i++)
		buffer[i] = iwl_पढ़ो_umac_prph_no_grab(trans,
						       MON_DMARB_RD_DATA_ADDR);
	iwl_ग_लिखो_umac_prph_no_grab(trans, MON_DMARB_RD_CTL_ADDR, 0x0);

	iwl_trans_release_nic_access(trans);

	वापस monitor_len;
पूर्ण

अटल व्योम
iwl_trans_pcie_dump_poपूर्णांकers(काष्ठा iwl_trans *trans,
			     काष्ठा iwl_fw_error_dump_fw_mon *fw_mon_data)
अणु
	u32 base, base_high, ग_लिखो_ptr, ग_लिखो_ptr_val, wrap_cnt;

	अगर (trans->trans_cfg->device_family >= IWL_DEVICE_FAMILY_AX210) अणु
		base = DBGC_CUR_DBGBUF_BASE_ADDR_LSB;
		base_high = DBGC_CUR_DBGBUF_BASE_ADDR_MSB;
		ग_लिखो_ptr = DBGC_CUR_DBGBUF_STATUS;
		wrap_cnt = DBGC_DBGBUF_WRAP_AROUND;
	पूर्ण अन्यथा अगर (trans->dbg.dest_tlv) अणु
		ग_लिखो_ptr = le32_to_cpu(trans->dbg.dest_tlv->ग_लिखो_ptr_reg);
		wrap_cnt = le32_to_cpu(trans->dbg.dest_tlv->wrap_count);
		base = le32_to_cpu(trans->dbg.dest_tlv->base_reg);
	पूर्ण अन्यथा अणु
		base = MON_BUFF_BASE_ADDR;
		ग_लिखो_ptr = MON_BUFF_WRPTR;
		wrap_cnt = MON_BUFF_CYCLE_CNT;
	पूर्ण

	ग_लिखो_ptr_val = iwl_पढ़ो_prph(trans, ग_लिखो_ptr);
	fw_mon_data->fw_mon_cycle_cnt =
		cpu_to_le32(iwl_पढ़ो_prph(trans, wrap_cnt));
	fw_mon_data->fw_mon_base_ptr =
		cpu_to_le32(iwl_पढ़ो_prph(trans, base));
	अगर (trans->trans_cfg->device_family >= IWL_DEVICE_FAMILY_AX210) अणु
		fw_mon_data->fw_mon_base_high_ptr =
			cpu_to_le32(iwl_पढ़ो_prph(trans, base_high));
		ग_लिखो_ptr_val &= DBGC_CUR_DBGBUF_STATUS_OFFSET_MSK;
		/* convert wrtPtr to DWs, to align with all HWs */
		ग_लिखो_ptr_val >>= 2;
	पूर्ण
	fw_mon_data->fw_mon_wr_ptr = cpu_to_le32(ग_लिखो_ptr_val);
पूर्ण

अटल u32
iwl_trans_pcie_dump_monitor(काष्ठा iwl_trans *trans,
			    काष्ठा iwl_fw_error_dump_data **data,
			    u32 monitor_len)
अणु
	काष्ठा iwl_dram_data *fw_mon = &trans->dbg.fw_mon;
	u32 len = 0;

	अगर (trans->dbg.dest_tlv ||
	    (fw_mon->size &&
	     (trans->trans_cfg->device_family == IWL_DEVICE_FAMILY_7000 ||
	      trans->trans_cfg->device_family >= IWL_DEVICE_FAMILY_AX210))) अणु
		काष्ठा iwl_fw_error_dump_fw_mon *fw_mon_data;

		(*data)->type = cpu_to_le32(IWL_FW_ERROR_DUMP_FW_MONITOR);
		fw_mon_data = (व्योम *)(*data)->data;

		iwl_trans_pcie_dump_poपूर्णांकers(trans, fw_mon_data);

		len += माप(**data) + माप(*fw_mon_data);
		अगर (fw_mon->size) अणु
			स_नकल(fw_mon_data->data, fw_mon->block, fw_mon->size);
			monitor_len = fw_mon->size;
		पूर्ण अन्यथा अगर (trans->dbg.dest_tlv->monitor_mode == SMEM_MODE) अणु
			u32 base = le32_to_cpu(fw_mon_data->fw_mon_base_ptr);
			/*
			 * Update poपूर्णांकers to reflect actual values after
			 * shअगरting
			 */
			अगर (trans->dbg.dest_tlv->version) अणु
				base = (iwl_पढ़ो_prph(trans, base) &
					IWL_LDBG_M2S_BUF_BA_MSK) <<
				       trans->dbg.dest_tlv->base_shअगरt;
				base *= IWL_M2S_UNIT_SIZE;
				base += trans->cfg->smem_offset;
			पूर्ण अन्यथा अणु
				base = iwl_पढ़ो_prph(trans, base) <<
				       trans->dbg.dest_tlv->base_shअगरt;
			पूर्ण

			iwl_trans_पढ़ो_mem(trans, base, fw_mon_data->data,
					   monitor_len / माप(u32));
		पूर्ण अन्यथा अगर (trans->dbg.dest_tlv->monitor_mode == MARBH_MODE) अणु
			monitor_len =
				iwl_trans_pci_dump_marbh_monitor(trans,
								 fw_mon_data,
								 monitor_len);
		पूर्ण अन्यथा अणु
			/* Didn't match anything - output no monitor data */
			monitor_len = 0;
		पूर्ण

		len += monitor_len;
		(*data)->len = cpu_to_le32(monitor_len + माप(*fw_mon_data));
	पूर्ण

	वापस len;
पूर्ण

अटल पूर्णांक iwl_trans_get_fw_monitor_len(काष्ठा iwl_trans *trans, u32 *len)
अणु
	अगर (trans->dbg.fw_mon.size) अणु
		*len += माप(काष्ठा iwl_fw_error_dump_data) +
			माप(काष्ठा iwl_fw_error_dump_fw_mon) +
			trans->dbg.fw_mon.size;
		वापस trans->dbg.fw_mon.size;
	पूर्ण अन्यथा अगर (trans->dbg.dest_tlv) अणु
		u32 base, end, cfg_reg, monitor_len;

		अगर (trans->dbg.dest_tlv->version == 1) अणु
			cfg_reg = le32_to_cpu(trans->dbg.dest_tlv->base_reg);
			cfg_reg = iwl_पढ़ो_prph(trans, cfg_reg);
			base = (cfg_reg & IWL_LDBG_M2S_BUF_BA_MSK) <<
				trans->dbg.dest_tlv->base_shअगरt;
			base *= IWL_M2S_UNIT_SIZE;
			base += trans->cfg->smem_offset;

			monitor_len =
				(cfg_reg & IWL_LDBG_M2S_BUF_SIZE_MSK) >>
				trans->dbg.dest_tlv->end_shअगरt;
			monitor_len *= IWL_M2S_UNIT_SIZE;
		पूर्ण अन्यथा अणु
			base = le32_to_cpu(trans->dbg.dest_tlv->base_reg);
			end = le32_to_cpu(trans->dbg.dest_tlv->end_reg);

			base = iwl_पढ़ो_prph(trans, base) <<
			       trans->dbg.dest_tlv->base_shअगरt;
			end = iwl_पढ़ो_prph(trans, end) <<
			      trans->dbg.dest_tlv->end_shअगरt;

			/* Make "end" poपूर्णांक to the actual end */
			अगर (trans->trans_cfg->device_family >=
			    IWL_DEVICE_FAMILY_8000 ||
			    trans->dbg.dest_tlv->monitor_mode == MARBH_MODE)
				end += (1 << trans->dbg.dest_tlv->end_shअगरt);
			monitor_len = end - base;
		पूर्ण
		*len += माप(काष्ठा iwl_fw_error_dump_data) +
			माप(काष्ठा iwl_fw_error_dump_fw_mon) +
			monitor_len;
		वापस monitor_len;
	पूर्ण
	वापस 0;
पूर्ण

अटल काष्ठा iwl_trans_dump_data
*iwl_trans_pcie_dump_data(काष्ठा iwl_trans *trans,
			  u32 dump_mask)
अणु
	काष्ठा iwl_trans_pcie *trans_pcie = IWL_TRANS_GET_PCIE_TRANS(trans);
	काष्ठा iwl_fw_error_dump_data *data;
	काष्ठा iwl_txq *cmdq = trans->txqs.txq[trans->txqs.cmd.q_id];
	काष्ठा iwl_fw_error_dump_txcmd *txcmd;
	काष्ठा iwl_trans_dump_data *dump_data;
	u32 len, num_rbs = 0, monitor_len = 0;
	पूर्णांक i, ptr;
	bool dump_rbs = test_bit(STATUS_FW_ERROR, &trans->status) &&
			!trans->trans_cfg->mq_rx_supported &&
			dump_mask & BIT(IWL_FW_ERROR_DUMP_RB);

	अगर (!dump_mask)
		वापस शून्य;

	/* transport dump header */
	len = माप(*dump_data);

	/* host commands */
	अगर (dump_mask & BIT(IWL_FW_ERROR_DUMP_TXCMD) && cmdq)
		len += माप(*data) +
			cmdq->n_winकरोw * (माप(*txcmd) +
					  TFD_MAX_PAYLOAD_SIZE);

	/* FW monitor */
	अगर (dump_mask & BIT(IWL_FW_ERROR_DUMP_FW_MONITOR))
		monitor_len = iwl_trans_get_fw_monitor_len(trans, &len);

	/* CSR रेजिस्टरs */
	अगर (dump_mask & BIT(IWL_FW_ERROR_DUMP_CSR))
		len += माप(*data) + IWL_CSR_TO_DUMP;

	/* FH रेजिस्टरs */
	अगर (dump_mask & BIT(IWL_FW_ERROR_DUMP_FH_REGS)) अणु
		अगर (trans->trans_cfg->gen2)
			len += माप(*data) +
			       (iwl_umac_prph(trans, FH_MEM_UPPER_BOUND_GEN2) -
				iwl_umac_prph(trans, FH_MEM_LOWER_BOUND_GEN2));
		अन्यथा
			len += माप(*data) +
			       (FH_MEM_UPPER_BOUND -
				FH_MEM_LOWER_BOUND);
	पूर्ण

	अगर (dump_rbs) अणु
		/* Dump RBs is supported only क्रम pre-9000 devices (1 queue) */
		काष्ठा iwl_rxq *rxq = &trans_pcie->rxq[0];
		/* RBs */
		num_rbs =
			le16_to_cpu(iwl_get_बंदd_rb_stts(trans, rxq))
			& 0x0FFF;
		num_rbs = (num_rbs - rxq->पढ़ो) & RX_QUEUE_MASK;
		len += num_rbs * (माप(*data) +
				  माप(काष्ठा iwl_fw_error_dump_rb) +
				  (PAGE_SIZE << trans_pcie->rx_page_order));
	पूर्ण

	/* Paged memory क्रम gen2 HW */
	अगर (trans->trans_cfg->gen2 && dump_mask & BIT(IWL_FW_ERROR_DUMP_PAGING))
		क्रम (i = 0; i < trans->init_dram.paging_cnt; i++)
			len += माप(*data) +
			       माप(काष्ठा iwl_fw_error_dump_paging) +
			       trans->init_dram.paging[i].size;

	dump_data = vzalloc(len);
	अगर (!dump_data)
		वापस शून्य;

	len = 0;
	data = (व्योम *)dump_data->data;

	अगर (dump_mask & BIT(IWL_FW_ERROR_DUMP_TXCMD) && cmdq) अणु
		u16 tfd_size = trans->txqs.tfd.size;

		data->type = cpu_to_le32(IWL_FW_ERROR_DUMP_TXCMD);
		txcmd = (व्योम *)data->data;
		spin_lock_bh(&cmdq->lock);
		ptr = cmdq->ग_लिखो_ptr;
		क्रम (i = 0; i < cmdq->n_winकरोw; i++) अणु
			u8 idx = iwl_txq_get_cmd_index(cmdq, ptr);
			u8 tfdidx;
			u32 caplen, cmdlen;

			अगर (trans->trans_cfg->use_tfh)
				tfdidx = idx;
			अन्यथा
				tfdidx = ptr;

			cmdlen = iwl_trans_pcie_get_cmdlen(trans,
							   (u8 *)cmdq->tfds +
							   tfd_size * tfdidx);
			caplen = min_t(u32, TFD_MAX_PAYLOAD_SIZE, cmdlen);

			अगर (cmdlen) अणु
				len += माप(*txcmd) + caplen;
				txcmd->cmdlen = cpu_to_le32(cmdlen);
				txcmd->caplen = cpu_to_le32(caplen);
				स_नकल(txcmd->data, cmdq->entries[idx].cmd,
				       caplen);
				txcmd = (व्योम *)((u8 *)txcmd->data + caplen);
			पूर्ण

			ptr = iwl_txq_dec_wrap(trans, ptr);
		पूर्ण
		spin_unlock_bh(&cmdq->lock);

		data->len = cpu_to_le32(len);
		len += माप(*data);
		data = iwl_fw_error_next_data(data);
	पूर्ण

	अगर (dump_mask & BIT(IWL_FW_ERROR_DUMP_CSR))
		len += iwl_trans_pcie_dump_csr(trans, &data);
	अगर (dump_mask & BIT(IWL_FW_ERROR_DUMP_FH_REGS))
		len += iwl_trans_pcie_fh_regs_dump(trans, &data);
	अगर (dump_rbs)
		len += iwl_trans_pcie_dump_rbs(trans, &data, num_rbs);

	/* Paged memory क्रम gen2 HW */
	अगर (trans->trans_cfg->gen2 &&
	    dump_mask & BIT(IWL_FW_ERROR_DUMP_PAGING)) अणु
		क्रम (i = 0; i < trans->init_dram.paging_cnt; i++) अणु
			काष्ठा iwl_fw_error_dump_paging *paging;
			u32 page_len = trans->init_dram.paging[i].size;

			data->type = cpu_to_le32(IWL_FW_ERROR_DUMP_PAGING);
			data->len = cpu_to_le32(माप(*paging) + page_len);
			paging = (व्योम *)data->data;
			paging->index = cpu_to_le32(i);
			स_नकल(paging->data,
			       trans->init_dram.paging[i].block, page_len);
			data = iwl_fw_error_next_data(data);

			len += माप(*data) + माप(*paging) + page_len;
		पूर्ण
	पूर्ण
	अगर (dump_mask & BIT(IWL_FW_ERROR_DUMP_FW_MONITOR))
		len += iwl_trans_pcie_dump_monitor(trans, &data, monitor_len);

	dump_data->len = len;

	वापस dump_data;
पूर्ण

अटल व्योम iwl_trans_pci_पूर्णांकerrupts(काष्ठा iwl_trans *trans, bool enable)
अणु
	अगर (enable)
		iwl_enable_पूर्णांकerrupts(trans);
	अन्यथा
		iwl_disable_पूर्णांकerrupts(trans);
पूर्ण

अटल व्योम iwl_trans_pcie_sync_nmi(काष्ठा iwl_trans *trans)
अणु
	u32 पूर्णांकa_addr, sw_err_bit;
	काष्ठा iwl_trans_pcie *trans_pcie = IWL_TRANS_GET_PCIE_TRANS(trans);

	अगर (trans_pcie->msix_enabled) अणु
		पूर्णांकa_addr = CSR_MSIX_HW_INT_CAUSES_AD;
		sw_err_bit = MSIX_HW_INT_CAUSES_REG_SW_ERR;
	पूर्ण अन्यथा अणु
		पूर्णांकa_addr = CSR_INT;
		sw_err_bit = CSR_INT_BIT_SW_ERR;
	पूर्ण

	iwl_trans_sync_nmi_with_addr(trans, पूर्णांकa_addr, sw_err_bit);
पूर्ण

#घोषणा IWL_TRANS_COMMON_OPS						\
	.op_mode_leave = iwl_trans_pcie_op_mode_leave,			\
	.ग_लिखो8 = iwl_trans_pcie_ग_लिखो8,				\
	.ग_लिखो32 = iwl_trans_pcie_ग_लिखो32,				\
	.पढ़ो32 = iwl_trans_pcie_पढ़ो32,				\
	.पढ़ो_prph = iwl_trans_pcie_पढ़ो_prph,				\
	.ग_लिखो_prph = iwl_trans_pcie_ग_लिखो_prph,			\
	.पढ़ो_mem = iwl_trans_pcie_पढ़ो_mem,				\
	.ग_लिखो_mem = iwl_trans_pcie_ग_लिखो_mem,				\
	.पढ़ो_config32 = iwl_trans_pcie_पढ़ो_config32,			\
	.configure = iwl_trans_pcie_configure,				\
	.set_pmi = iwl_trans_pcie_set_pmi,				\
	.sw_reset = iwl_trans_pcie_sw_reset,				\
	.grab_nic_access = iwl_trans_pcie_grab_nic_access,		\
	.release_nic_access = iwl_trans_pcie_release_nic_access,	\
	.set_bits_mask = iwl_trans_pcie_set_bits_mask,			\
	.dump_data = iwl_trans_pcie_dump_data,				\
	.d3_suspend = iwl_trans_pcie_d3_suspend,			\
	.d3_resume = iwl_trans_pcie_d3_resume,				\
	.पूर्णांकerrupts = iwl_trans_pci_पूर्णांकerrupts,				\
	.sync_nmi = iwl_trans_pcie_sync_nmi				\

अटल स्थिर काष्ठा iwl_trans_ops trans_ops_pcie = अणु
	IWL_TRANS_COMMON_OPS,
	.start_hw = iwl_trans_pcie_start_hw,
	.fw_alive = iwl_trans_pcie_fw_alive,
	.start_fw = iwl_trans_pcie_start_fw,
	.stop_device = iwl_trans_pcie_stop_device,

	.send_cmd = iwl_pcie_enqueue_hcmd,

	.tx = iwl_trans_pcie_tx,
	.reclaim = iwl_txq_reclaim,

	.txq_disable = iwl_trans_pcie_txq_disable,
	.txq_enable = iwl_trans_pcie_txq_enable,

	.txq_set_shared_mode = iwl_trans_pcie_txq_set_shared_mode,

	.रुको_tx_queues_empty = iwl_trans_pcie_रुको_txqs_empty,

	.मुक्तze_txq_समयr = iwl_trans_txq_मुक्तze_समयr,
	.block_txq_ptrs = iwl_trans_pcie_block_txq_ptrs,
#अगर_घोषित CONFIG_IWLWIFI_DEBUGFS
	.debugfs_cleanup = iwl_trans_pcie_debugfs_cleanup,
#पूर्ण_अगर
पूर्ण;

अटल स्थिर काष्ठा iwl_trans_ops trans_ops_pcie_gen2 = अणु
	IWL_TRANS_COMMON_OPS,
	.start_hw = iwl_trans_pcie_start_hw,
	.fw_alive = iwl_trans_pcie_gen2_fw_alive,
	.start_fw = iwl_trans_pcie_gen2_start_fw,
	.stop_device = iwl_trans_pcie_gen2_stop_device,

	.send_cmd = iwl_pcie_gen2_enqueue_hcmd,

	.tx = iwl_txq_gen2_tx,
	.reclaim = iwl_txq_reclaim,

	.set_q_ptrs = iwl_txq_set_q_ptrs,

	.txq_alloc = iwl_txq_dyn_alloc,
	.txq_मुक्त = iwl_txq_dyn_मुक्त,
	.रुको_txq_empty = iwl_trans_pcie_रुको_txq_empty,
	.rxq_dma_data = iwl_trans_pcie_rxq_dma_data,
	.set_pnvm = iwl_trans_pcie_ctx_info_gen3_set_pnvm,
#अगर_घोषित CONFIG_IWLWIFI_DEBUGFS
	.debugfs_cleanup = iwl_trans_pcie_debugfs_cleanup,
#पूर्ण_अगर
पूर्ण;

काष्ठा iwl_trans *iwl_trans_pcie_alloc(काष्ठा pci_dev *pdev,
			       स्थिर काष्ठा pci_device_id *ent,
			       स्थिर काष्ठा iwl_cfg_trans_params *cfg_trans)
अणु
	काष्ठा iwl_trans_pcie *trans_pcie;
	काष्ठा iwl_trans *trans;
	पूर्णांक ret, addr_size;
	स्थिर काष्ठा iwl_trans_ops *ops = &trans_ops_pcie_gen2;

	अगर (!cfg_trans->gen2)
		ops = &trans_ops_pcie;

	ret = pcim_enable_device(pdev);
	अगर (ret)
		वापस ERR_PTR(ret);

	trans = iwl_trans_alloc(माप(काष्ठा iwl_trans_pcie), &pdev->dev, ops,
				cfg_trans);
	अगर (!trans)
		वापस ERR_PTR(-ENOMEM);

	trans_pcie = IWL_TRANS_GET_PCIE_TRANS(trans);

	trans_pcie->trans = trans;
	trans_pcie->opmode_करोwn = true;
	spin_lock_init(&trans_pcie->irq_lock);
	spin_lock_init(&trans_pcie->reg_lock);
	spin_lock_init(&trans_pcie->alloc_page_lock);
	mutex_init(&trans_pcie->mutex);
	init_रुकोqueue_head(&trans_pcie->ucode_ग_लिखो_रुकोq);
	init_रुकोqueue_head(&trans_pcie->fw_reset_रुकोq);

	trans_pcie->rba.alloc_wq = alloc_workqueue("rb_allocator",
						   WQ_HIGHPRI | WQ_UNBOUND, 1);
	अगर (!trans_pcie->rba.alloc_wq) अणु
		ret = -ENOMEM;
		जाओ out_मुक्त_trans;
	पूर्ण
	INIT_WORK(&trans_pcie->rba.rx_alloc, iwl_pcie_rx_allocator_work);

	trans_pcie->debug_rfसमाप्त = -1;

	अगर (!cfg_trans->base_params->pcie_l1_allowed) अणु
		/*
		 * W/A - seems to solve weird behavior. We need to हटाओ this
		 * अगर we करोn't want to stay in L1 all the समय. This wastes a
		 * lot of घातer.
		 */
		pci_disable_link_state(pdev, PCIE_LINK_STATE_L0S |
				       PCIE_LINK_STATE_L1 |
				       PCIE_LINK_STATE_CLKPM);
	पूर्ण

	trans_pcie->def_rx_queue = 0;

	pci_set_master(pdev);

	addr_size = trans->txqs.tfd.addr_size;
	ret = pci_set_dma_mask(pdev, DMA_BIT_MASK(addr_size));
	अगर (!ret)
		ret = pci_set_consistent_dma_mask(pdev,
						  DMA_BIT_MASK(addr_size));
	अगर (ret) अणु
		ret = pci_set_dma_mask(pdev, DMA_BIT_MASK(32));
		अगर (!ret)
			ret = pci_set_consistent_dma_mask(pdev,
							  DMA_BIT_MASK(32));
		/* both attempts failed: */
		अगर (ret) अणु
			dev_err(&pdev->dev, "No suitable DMA available\n");
			जाओ out_no_pci;
		पूर्ण
	पूर्ण

	ret = pcim_iomap_regions_request_all(pdev, BIT(0), DRV_NAME);
	अगर (ret) अणु
		dev_err(&pdev->dev, "pcim_iomap_regions_request_all failed\n");
		जाओ out_no_pci;
	पूर्ण

	trans_pcie->hw_base = pcim_iomap_table(pdev)[0];
	अगर (!trans_pcie->hw_base) अणु
		dev_err(&pdev->dev, "pcim_iomap_table failed\n");
		ret = -ENODEV;
		जाओ out_no_pci;
	पूर्ण

	/* We disable the RETRY_TIMEOUT रेजिस्टर (0x41) to keep
	 * PCI Tx retries from पूर्णांकerfering with C3 CPU state */
	pci_ग_लिखो_config_byte(pdev, PCI_CFG_RETRY_TIMEOUT, 0x00);

	trans_pcie->pci_dev = pdev;
	iwl_disable_पूर्णांकerrupts(trans);

	trans->hw_rev = iwl_पढ़ो32(trans, CSR_HW_REV);
	अगर (trans->hw_rev == 0xffffffff) अणु
		dev_err(&pdev->dev, "HW_REV=0xFFFFFFFF, PCI issues?\n");
		ret = -EIO;
		जाओ out_no_pci;
	पूर्ण

	/*
	 * In the 8000 HW family the क्रमmat of the 4 bytes of CSR_HW_REV have
	 * changed, and now the revision step also includes bit 0-1 (no more
	 * "dash" value). To keep hw_rev backwards compatible - we'll store it
	 * in the old क्रमmat.
	 */
	अगर (cfg_trans->device_family >= IWL_DEVICE_FAMILY_8000)
		trans->hw_rev = (trans->hw_rev & 0xfff0) |
				(CSR_HW_REV_STEP(trans->hw_rev << 2) << 2);

	IWL_DEBUG_INFO(trans, "HW REV: 0x%0x\n", trans->hw_rev);

	iwl_pcie_set_पूर्णांकerrupt_capa(pdev, trans, cfg_trans);
	trans->hw_id = (pdev->device << 16) + pdev->subप्रणाली_device;
	snम_लिखो(trans->hw_id_str, माप(trans->hw_id_str),
		 "PCI ID: 0x%04X:0x%04X", pdev->device, pdev->subप्रणाली_device);

	init_रुकोqueue_head(&trans_pcie->sx_रुकोq);


	अगर (trans_pcie->msix_enabled) अणु
		ret = iwl_pcie_init_msix_handler(pdev, trans_pcie);
		अगर (ret)
			जाओ out_no_pci;
	 पूर्ण अन्यथा अणु
		ret = iwl_pcie_alloc_ict(trans);
		अगर (ret)
			जाओ out_no_pci;

		ret = devm_request_thपढ़ोed_irq(&pdev->dev, pdev->irq,
						iwl_pcie_isr,
						iwl_pcie_irq_handler,
						IRQF_SHARED, DRV_NAME, trans);
		अगर (ret) अणु
			IWL_ERR(trans, "Error allocating IRQ %d\n", pdev->irq);
			जाओ out_मुक्त_ict;
		पूर्ण
	 पूर्ण

#अगर_घोषित CONFIG_IWLWIFI_DEBUGFS
	trans_pcie->fw_mon_data.state = IWL_FW_MON_DBGFS_STATE_CLOSED;
	mutex_init(&trans_pcie->fw_mon_data.mutex);
#पूर्ण_अगर

	iwl_dbg_tlv_init(trans);

	वापस trans;

out_मुक्त_ict:
	iwl_pcie_मुक्त_ict(trans);
out_no_pci:
	destroy_workqueue(trans_pcie->rba.alloc_wq);
out_मुक्त_trans:
	iwl_trans_मुक्त(trans);
	वापस ERR_PTR(ret);
पूर्ण
