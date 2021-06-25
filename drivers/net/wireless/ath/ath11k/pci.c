<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause-Clear
/*
 * Copyright (c) 2019-2020 The Linux Foundation. All rights reserved.
 */

#समावेश <linux/module.h>
#समावेश <linux/msi.h>
#समावेश <linux/pci.h>

#समावेश "pci.h"
#समावेश "core.h"
#समावेश "hif.h"
#समावेश "mhi.h"
#समावेश "debug.h"

#घोषणा ATH11K_PCI_BAR_NUM		0
#घोषणा ATH11K_PCI_DMA_MASK		32

#घोषणा ATH11K_PCI_IRQ_CE0_OFFSET		3

#घोषणा WINDOW_ENABLE_BIT		0x40000000
#घोषणा WINDOW_REG_ADDRESS		0x310c
#घोषणा WINDOW_VALUE_MASK		GENMASK(24, 19)
#घोषणा WINDOW_START			0x80000
#घोषणा WINDOW_RANGE_MASK		GENMASK(18, 0)

#घोषणा TCSR_SOC_HW_VERSION		0x0224
#घोषणा TCSR_SOC_HW_VERSION_MAJOR_MASK	GENMASK(16, 8)
#घोषणा TCSR_SOC_HW_VERSION_MINOR_MASK	GENMASK(7, 0)

/* BAR0 + 4k is always accessible, and no
 * need to क्रमce wakeup.
 * 4K - 32 = 0xFE0
 */
#घोषणा ACCESS_ALWAYS_OFF 0xFE0

#घोषणा QCA6390_DEVICE_ID		0x1101
#घोषणा QCN9074_DEVICE_ID		0x1104

अटल स्थिर काष्ठा pci_device_id ath11k_pci_id_table[] = अणु
	अणु PCI_VDEVICE(QCOM, QCA6390_DEVICE_ID) पूर्ण,
	/* TODO: add QCN9074_DEVICE_ID) once firmware issues are resolved */
	अणु0पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, ath11k_pci_id_table);

अटल स्थिर काष्ठा ath11k_bus_params ath11k_pci_bus_params = अणु
	.mhi_support = true,
	.m3_fw_support = true,
	.fixed_bdf_addr = false,
	.fixed_mem_region = false,
पूर्ण;

अटल स्थिर काष्ठा ath11k_msi_config ath11k_msi_config[] = अणु
	अणु
		.total_vectors = 32,
		.total_users = 4,
		.users = (काष्ठा ath11k_msi_user[]) अणु
			अणु .name = "MHI", .num_vectors = 3, .base_vector = 0 पूर्ण,
			अणु .name = "CE", .num_vectors = 10, .base_vector = 3 पूर्ण,
			अणु .name = "WAKE", .num_vectors = 1, .base_vector = 13 पूर्ण,
			अणु .name = "DP", .num_vectors = 18, .base_vector = 14 पूर्ण,
		पूर्ण,
	पूर्ण,
	अणु
		.total_vectors = 16,
		.total_users = 3,
		.users = (काष्ठा ath11k_msi_user[]) अणु
			अणु .name = "MHI", .num_vectors = 3, .base_vector = 0 पूर्ण,
			अणु .name = "CE", .num_vectors = 5, .base_vector = 3 पूर्ण,
			अणु .name = "DP", .num_vectors = 8, .base_vector = 8 पूर्ण,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर अक्षर *irq_name[ATH11K_IRQ_NUM_MAX] = अणु
	"bhi",
	"mhi-er0",
	"mhi-er1",
	"ce0",
	"ce1",
	"ce2",
	"ce3",
	"ce4",
	"ce5",
	"ce6",
	"ce7",
	"ce8",
	"ce9",
	"ce10",
	"ce11",
	"host2wbm-desc-feed",
	"host2reo-re-injection",
	"host2reo-command",
	"host2rxdma-monitor-ring3",
	"host2rxdma-monitor-ring2",
	"host2rxdma-monitor-ring1",
	"reo2ost-exception",
	"wbm2host-rx-release",
	"reo2host-status",
	"reo2host-destination-ring4",
	"reo2host-destination-ring3",
	"reo2host-destination-ring2",
	"reo2host-destination-ring1",
	"rxdma2host-monitor-destination-mac3",
	"rxdma2host-monitor-destination-mac2",
	"rxdma2host-monitor-destination-mac1",
	"ppdu-end-interrupts-mac3",
	"ppdu-end-interrupts-mac2",
	"ppdu-end-interrupts-mac1",
	"rxdma2host-monitor-status-ring-mac3",
	"rxdma2host-monitor-status-ring-mac2",
	"rxdma2host-monitor-status-ring-mac1",
	"host2rxdma-host-buf-ring-mac3",
	"host2rxdma-host-buf-ring-mac2",
	"host2rxdma-host-buf-ring-mac1",
	"rxdma2host-destination-ring-mac3",
	"rxdma2host-destination-ring-mac2",
	"rxdma2host-destination-ring-mac1",
	"host2tcl-input-ring4",
	"host2tcl-input-ring3",
	"host2tcl-input-ring2",
	"host2tcl-input-ring1",
	"wbm2host-tx-completions-ring3",
	"wbm2host-tx-completions-ring2",
	"wbm2host-tx-completions-ring1",
	"tcl2host-status-ring",
पूर्ण;

अटल अंतरभूत व्योम ath11k_pci_select_winकरोw(काष्ठा ath11k_pci *ab_pci, u32 offset)
अणु
	काष्ठा ath11k_base *ab = ab_pci->ab;

	u32 winकरोw = FIELD_GET(WINDOW_VALUE_MASK, offset);

	lockdep_निश्चित_held(&ab_pci->winकरोw_lock);

	अगर (winकरोw != ab_pci->रेजिस्टर_winकरोw) अणु
		ioग_लिखो32(WINDOW_ENABLE_BIT | winकरोw,
			  ab->mem + WINDOW_REG_ADDRESS);
		ioपढ़ो32(ab->mem + WINDOW_REG_ADDRESS);
		ab_pci->रेजिस्टर_winकरोw = winकरोw;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम ath11k_pci_select_अटल_winकरोw(काष्ठा ath11k_pci *ab_pci)
अणु
	u32 umac_winकरोw = FIELD_GET(WINDOW_VALUE_MASK, HAL_SEQ_WCSS_UMAC_OFFSET);
	u32 ce_winकरोw = FIELD_GET(WINDOW_VALUE_MASK, HAL_CE_WFSS_CE_REG_BASE);
	u32 winकरोw;

	winकरोw = (umac_winकरोw << 12) | (ce_winकरोw << 6);

	ioग_लिखो32(WINDOW_ENABLE_BIT | winकरोw, ab_pci->ab->mem + WINDOW_REG_ADDRESS);
पूर्ण

अटल अंतरभूत u32 ath11k_pci_get_winकरोw_start(काष्ठा ath11k_base *ab,
					      u32 offset)
अणु
	u32 winकरोw_start;

	/* If offset lies within DP रेजिस्टर range, use 3rd winकरोw */
	अगर ((offset ^ HAL_SEQ_WCSS_UMAC_OFFSET) < WINDOW_RANGE_MASK)
		winकरोw_start = 3 * WINDOW_START;
	/* If offset lies within CE रेजिस्टर range, use 2nd winकरोw */
	अन्यथा अगर ((offset ^ HAL_CE_WFSS_CE_REG_BASE) < WINDOW_RANGE_MASK)
		winकरोw_start = 2 * WINDOW_START;
	अन्यथा
		winकरोw_start = WINDOW_START;

	वापस winकरोw_start;
पूर्ण

व्योम ath11k_pci_ग_लिखो32(काष्ठा ath11k_base *ab, u32 offset, u32 value)
अणु
	काष्ठा ath11k_pci *ab_pci = ath11k_pci_priv(ab);
	u32 winकरोw_start;

	/* क्रम offset beyond BAR + 4K - 32, may
	 * need to wakeup MHI to access.
	 */
	अगर (test_bit(ATH11K_PCI_FLAG_INIT_DONE, &ab_pci->flags) &&
	    offset >= ACCESS_ALWAYS_OFF)
		mhi_device_get_sync(ab_pci->mhi_ctrl->mhi_dev);

	अगर (offset < WINDOW_START) अणु
		ioग_लिखो32(value, ab->mem  + offset);
	पूर्ण अन्यथा अणु
		अगर (ab->bus_params.अटल_winकरोw_map)
			winकरोw_start = ath11k_pci_get_winकरोw_start(ab, offset);
		अन्यथा
			winकरोw_start = WINDOW_START;

		अगर (winकरोw_start == WINDOW_START) अणु
			spin_lock_bh(&ab_pci->winकरोw_lock);
			ath11k_pci_select_winकरोw(ab_pci, offset);
			ioग_लिखो32(value, ab->mem + winकरोw_start +
				  (offset & WINDOW_RANGE_MASK));
			spin_unlock_bh(&ab_pci->winकरोw_lock);
		पूर्ण अन्यथा अणु
			ioग_लिखो32(value, ab->mem + winकरोw_start +
				  (offset & WINDOW_RANGE_MASK));
		पूर्ण
	पूर्ण

	अगर (test_bit(ATH11K_PCI_FLAG_INIT_DONE, &ab_pci->flags) &&
	    offset >= ACCESS_ALWAYS_OFF)
		mhi_device_put(ab_pci->mhi_ctrl->mhi_dev);
पूर्ण

u32 ath11k_pci_पढ़ो32(काष्ठा ath11k_base *ab, u32 offset)
अणु
	काष्ठा ath11k_pci *ab_pci = ath11k_pci_priv(ab);
	u32 val, winकरोw_start;

	/* क्रम offset beyond BAR + 4K - 32, may
	 * need to wakeup MHI to access.
	 */
	अगर (test_bit(ATH11K_PCI_FLAG_INIT_DONE, &ab_pci->flags) &&
	    offset >= ACCESS_ALWAYS_OFF)
		mhi_device_get_sync(ab_pci->mhi_ctrl->mhi_dev);

	अगर (offset < WINDOW_START) अणु
		val = ioपढ़ो32(ab->mem + offset);
	पूर्ण अन्यथा अणु
		अगर (ab->bus_params.अटल_winकरोw_map)
			winकरोw_start = ath11k_pci_get_winकरोw_start(ab, offset);
		अन्यथा
			winकरोw_start = WINDOW_START;

		अगर (winकरोw_start == WINDOW_START) अणु
			spin_lock_bh(&ab_pci->winकरोw_lock);
			ath11k_pci_select_winकरोw(ab_pci, offset);
			val = ioपढ़ो32(ab->mem + winकरोw_start +
				       (offset & WINDOW_RANGE_MASK));
			spin_unlock_bh(&ab_pci->winकरोw_lock);
		पूर्ण अन्यथा अणु
			val = ioपढ़ो32(ab->mem + winकरोw_start +
				       (offset & WINDOW_RANGE_MASK));
		पूर्ण
	पूर्ण

	अगर (test_bit(ATH11K_PCI_FLAG_INIT_DONE, &ab_pci->flags) &&
	    offset >= ACCESS_ALWAYS_OFF)
		mhi_device_put(ab_pci->mhi_ctrl->mhi_dev);

	वापस val;
पूर्ण

अटल व्योम ath11k_pci_soc_global_reset(काष्ठा ath11k_base *ab)
अणु
	u32 val, delay;

	val = ath11k_pci_पढ़ो32(ab, PCIE_SOC_GLOBAL_RESET);

	val |= PCIE_SOC_GLOBAL_RESET_V;

	ath11k_pci_ग_लिखो32(ab, PCIE_SOC_GLOBAL_RESET, val);

	/* TODO: exact समय to sleep is uncertain */
	delay = 10;
	mdelay(delay);

	/* Need to toggle V bit back otherwise stuck in reset status */
	val &= ~PCIE_SOC_GLOBAL_RESET_V;

	ath11k_pci_ग_लिखो32(ab, PCIE_SOC_GLOBAL_RESET, val);

	mdelay(delay);

	val = ath11k_pci_पढ़ो32(ab, PCIE_SOC_GLOBAL_RESET);
	अगर (val == 0xffffffff)
		ath11k_warn(ab, "link down error during global reset\n");
पूर्ण

अटल व्योम ath11k_pci_clear_dbg_रेजिस्टरs(काष्ठा ath11k_base *ab)
अणु
	u32 val;

	/* पढ़ो cookie */
	val = ath11k_pci_पढ़ो32(ab, PCIE_Q6_COOKIE_ADDR);
	ath11k_dbg(ab, ATH11K_DBG_PCI, "cookie:0x%x\n", val);

	val = ath11k_pci_पढ़ो32(ab, WLAON_WARM_SW_ENTRY);
	ath11k_dbg(ab, ATH11K_DBG_PCI, "WLAON_WARM_SW_ENTRY 0x%x\n", val);

	/* TODO: exact समय to sleep is uncertain */
	mdelay(10);

	/* ग_लिखो 0 to WLAON_WARM_SW_ENTRY to prevent Q6 from
	 * continuing warm path and entering dead loop.
	 */
	ath11k_pci_ग_लिखो32(ab, WLAON_WARM_SW_ENTRY, 0);
	mdelay(10);

	val = ath11k_pci_पढ़ो32(ab, WLAON_WARM_SW_ENTRY);
	ath11k_dbg(ab, ATH11K_DBG_PCI, "WLAON_WARM_SW_ENTRY 0x%x\n", val);

	/* A पढ़ो clear रेजिस्टर. clear the रेजिस्टर to prevent
	 * Q6 from entering wrong code path.
	 */
	val = ath11k_pci_पढ़ो32(ab, WLAON_SOC_RESET_CAUSE_REG);
	ath11k_dbg(ab, ATH11K_DBG_PCI, "soc reset cause:%d\n", val);
पूर्ण

अटल पूर्णांक ath11k_pci_set_link_reg(काष्ठा ath11k_base *ab,
				   u32 offset, u32 value, u32 mask)
अणु
	u32 v;
	पूर्णांक i;

	v = ath11k_pci_पढ़ो32(ab, offset);
	अगर ((v & mask) == value)
		वापस 0;

	क्रम (i = 0; i < 10; i++) अणु
		ath11k_pci_ग_लिखो32(ab, offset, (v & ~mask) | value);

		v = ath11k_pci_पढ़ो32(ab, offset);
		अगर ((v & mask) == value)
			वापस 0;

		mdelay(2);
	पूर्ण

	ath11k_warn(ab, "failed to set pcie link register 0x%08x: 0x%08x != 0x%08x\n",
		    offset, v & mask, value);

	वापस -ETIMEDOUT;
पूर्ण

अटल पूर्णांक ath11k_pci_fix_l1ss(काष्ठा ath11k_base *ab)
अणु
	पूर्णांक ret;

	ret = ath11k_pci_set_link_reg(ab,
				      PCIE_QSERDES_COM_SYSCLK_EN_SEL_REG(ab),
				      PCIE_QSERDES_COM_SYSCLK_EN_SEL_VAL,
				      PCIE_QSERDES_COM_SYSCLK_EN_SEL_MSK);
	अगर (ret) अणु
		ath11k_warn(ab, "failed to set sysclk: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = ath11k_pci_set_link_reg(ab,
				      PCIE_PCS_OSC_DTCT_CONFIG1_REG(ab),
				      PCIE_PCS_OSC_DTCT_CONFIG1_VAL,
				      PCIE_PCS_OSC_DTCT_CONFIG_MSK);
	अगर (ret) अणु
		ath11k_warn(ab, "failed to set dtct config1 error: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = ath11k_pci_set_link_reg(ab,
				      PCIE_PCS_OSC_DTCT_CONFIG2_REG(ab),
				      PCIE_PCS_OSC_DTCT_CONFIG2_VAL,
				      PCIE_PCS_OSC_DTCT_CONFIG_MSK);
	अगर (ret) अणु
		ath11k_warn(ab, "failed to set dtct config2: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = ath11k_pci_set_link_reg(ab,
				      PCIE_PCS_OSC_DTCT_CONFIG4_REG(ab),
				      PCIE_PCS_OSC_DTCT_CONFIG4_VAL,
				      PCIE_PCS_OSC_DTCT_CONFIG_MSK);
	अगर (ret) अणु
		ath11k_warn(ab, "failed to set dtct config4: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम ath11k_pci_enable_ltssm(काष्ठा ath11k_base *ab)
अणु
	u32 val;
	पूर्णांक i;

	val = ath11k_pci_पढ़ो32(ab, PCIE_PCIE_PARF_LTSSM);

	/* PCIE link seems very unstable after the Hot Reset*/
	क्रम (i = 0; val != PARM_LTSSM_VALUE && i < 5; i++) अणु
		अगर (val == 0xffffffff)
			mdelay(5);

		ath11k_pci_ग_लिखो32(ab, PCIE_PCIE_PARF_LTSSM, PARM_LTSSM_VALUE);
		val = ath11k_pci_पढ़ो32(ab, PCIE_PCIE_PARF_LTSSM);
	पूर्ण

	ath11k_dbg(ab, ATH11K_DBG_PCI, "pci ltssm 0x%x\n", val);

	val = ath11k_pci_पढ़ो32(ab, GCC_GCC_PCIE_HOT_RST);
	val |= GCC_GCC_PCIE_HOT_RST_VAL;
	ath11k_pci_ग_लिखो32(ab, GCC_GCC_PCIE_HOT_RST, val);
	val = ath11k_pci_पढ़ो32(ab, GCC_GCC_PCIE_HOT_RST);

	ath11k_dbg(ab, ATH11K_DBG_PCI, "pci pcie_hot_rst 0x%x\n", val);

	mdelay(5);
पूर्ण

अटल व्योम ath11k_pci_clear_all_पूर्णांकrs(काष्ठा ath11k_base *ab)
अणु
	/* This is a WAR क्रम PCIE Hotreset.
	 * When target receive Hotreset, but will set the पूर्णांकerrupt.
	 * So when करोwnload SBL again, SBL will खोलो Interrupt and
	 * receive it, and crash immediately.
	 */
	ath11k_pci_ग_लिखो32(ab, PCIE_PCIE_INT_ALL_CLEAR, PCIE_INT_CLEAR_ALL);
पूर्ण

अटल व्योम ath11k_pci_set_wlaon_pwr_ctrl(काष्ठा ath11k_base *ab)
अणु
	u32 val;

	val = ath11k_pci_पढ़ो32(ab, WLAON_QFPROM_PWR_CTRL_REG);
	val &= ~QFPROM_PWR_CTRL_VDD4BLOW_MASK;
	ath11k_pci_ग_लिखो32(ab, WLAON_QFPROM_PWR_CTRL_REG, val);
पूर्ण

अटल व्योम ath11k_pci_क्रमce_wake(काष्ठा ath11k_base *ab)
अणु
	ath11k_pci_ग_लिखो32(ab, PCIE_SOC_WAKE_PCIE_LOCAL_REG, 1);
	mdelay(5);
पूर्ण

अटल व्योम ath11k_pci_sw_reset(काष्ठा ath11k_base *ab, bool घातer_on)
अणु
	अगर (घातer_on) अणु
		ath11k_pci_enable_ltssm(ab);
		ath11k_pci_clear_all_पूर्णांकrs(ab);
		ath11k_pci_set_wlaon_pwr_ctrl(ab);
		ath11k_pci_fix_l1ss(ab);
	पूर्ण

	ath11k_mhi_clear_vector(ab);
	ath11k_pci_soc_global_reset(ab);
	ath11k_mhi_set_mhictrl_reset(ab);
	ath11k_pci_clear_dbg_रेजिस्टरs(ab);
पूर्ण

पूर्णांक ath11k_pci_get_msi_irq(काष्ठा device *dev, अचिन्हित पूर्णांक vector)
अणु
	काष्ठा pci_dev *pci_dev = to_pci_dev(dev);

	वापस pci_irq_vector(pci_dev, vector);
पूर्ण

अटल व्योम ath11k_pci_get_msi_address(काष्ठा ath11k_base *ab, u32 *msi_addr_lo,
				       u32 *msi_addr_hi)
अणु
	काष्ठा ath11k_pci *ab_pci = ath11k_pci_priv(ab);
	काष्ठा pci_dev *pci_dev = to_pci_dev(ab->dev);

	pci_पढ़ो_config_dword(pci_dev, pci_dev->msi_cap + PCI_MSI_ADDRESS_LO,
			      msi_addr_lo);

	अगर (test_bit(ATH11K_PCI_FLAG_IS_MSI_64, &ab_pci->flags)) अणु
		pci_पढ़ो_config_dword(pci_dev, pci_dev->msi_cap + PCI_MSI_ADDRESS_HI,
				      msi_addr_hi);
	पूर्ण अन्यथा अणु
		*msi_addr_hi = 0;
	पूर्ण
पूर्ण

पूर्णांक ath11k_pci_get_user_msi_assignment(काष्ठा ath11k_pci *ab_pci, अक्षर *user_name,
				       पूर्णांक *num_vectors, u32 *user_base_data,
				       u32 *base_vector)
अणु
	काष्ठा ath11k_base *ab = ab_pci->ab;
	स्थिर काष्ठा ath11k_msi_config *msi_config = ab_pci->msi_config;
	पूर्णांक idx;

	क्रम (idx = 0; idx < msi_config->total_users; idx++) अणु
		अगर (म_भेद(user_name, msi_config->users[idx].name) == 0) अणु
			*num_vectors = msi_config->users[idx].num_vectors;
			*user_base_data = msi_config->users[idx].base_vector
				+ ab_pci->msi_ep_base_data;
			*base_vector = msi_config->users[idx].base_vector;

			ath11k_dbg(ab, ATH11K_DBG_PCI, "Assign MSI to user: %s, num_vectors: %d, user_base_data: %u, base_vector: %u\n",
				   user_name, *num_vectors, *user_base_data,
				   *base_vector);

			वापस 0;
		पूर्ण
	पूर्ण

	ath11k_err(ab, "Failed to find MSI assignment for %s!\n", user_name);

	वापस -EINVAL;
पूर्ण

अटल व्योम ath11k_pci_get_ce_msi_idx(काष्ठा ath11k_base *ab, u32 ce_id,
				      u32 *msi_idx)
अणु
	u32 i, msi_data_idx;

	क्रम (i = 0, msi_data_idx = 0; i < ab->hw_params.ce_count; i++) अणु
		अगर (ath11k_ce_get_attr_flags(ab, i) & CE_ATTR_DIS_INTR)
			जारी;

		अगर (ce_id == i)
			अवरोध;

		msi_data_idx++;
	पूर्ण
	*msi_idx = msi_data_idx;
पूर्ण

अटल पूर्णांक ath11k_get_user_msi_assignment(काष्ठा ath11k_base *ab, अक्षर *user_name,
					  पूर्णांक *num_vectors, u32 *user_base_data,
					  u32 *base_vector)
अणु
	काष्ठा ath11k_pci *ab_pci = ath11k_pci_priv(ab);

	वापस ath11k_pci_get_user_msi_assignment(ab_pci, user_name,
						  num_vectors, user_base_data,
						  base_vector);
पूर्ण

अटल व्योम ath11k_pci_मुक्त_ext_irq(काष्ठा ath11k_base *ab)
अणु
	पूर्णांक i, j;

	क्रम (i = 0; i < ATH11K_EXT_IRQ_GRP_NUM_MAX; i++) अणु
		काष्ठा ath11k_ext_irq_grp *irq_grp = &ab->ext_irq_grp[i];

		क्रम (j = 0; j < irq_grp->num_irq; j++)
			मुक्त_irq(ab->irq_num[irq_grp->irqs[j]], irq_grp);

		netअगर_napi_del(&irq_grp->napi);
	पूर्ण
पूर्ण

अटल व्योम ath11k_pci_मुक्त_irq(काष्ठा ath11k_base *ab)
अणु
	पूर्णांक i, irq_idx;

	क्रम (i = 0; i < ab->hw_params.ce_count; i++) अणु
		अगर (ath11k_ce_get_attr_flags(ab, i) & CE_ATTR_DIS_INTR)
			जारी;
		irq_idx = ATH11K_PCI_IRQ_CE0_OFFSET + i;
		मुक्त_irq(ab->irq_num[irq_idx], &ab->ce.ce_pipe[i]);
	पूर्ण

	ath11k_pci_मुक्त_ext_irq(ab);
पूर्ण

अटल व्योम ath11k_pci_ce_irq_enable(काष्ठा ath11k_base *ab, u16 ce_id)
अणु
	u32 irq_idx;

	irq_idx = ATH11K_PCI_IRQ_CE0_OFFSET + ce_id;
	enable_irq(ab->irq_num[irq_idx]);
पूर्ण

अटल व्योम ath11k_pci_ce_irq_disable(काष्ठा ath11k_base *ab, u16 ce_id)
अणु
	u32 irq_idx;

	irq_idx = ATH11K_PCI_IRQ_CE0_OFFSET + ce_id;
	disable_irq_nosync(ab->irq_num[irq_idx]);
पूर्ण

अटल व्योम ath11k_pci_ce_irqs_disable(काष्ठा ath11k_base *ab)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ab->hw_params.ce_count; i++) अणु
		अगर (ath11k_ce_get_attr_flags(ab, i) & CE_ATTR_DIS_INTR)
			जारी;
		ath11k_pci_ce_irq_disable(ab, i);
	पूर्ण
पूर्ण

अटल व्योम ath11k_pci_sync_ce_irqs(काष्ठा ath11k_base *ab)
अणु
	पूर्णांक i;
	पूर्णांक irq_idx;

	क्रम (i = 0; i < ab->hw_params.ce_count; i++) अणु
		अगर (ath11k_ce_get_attr_flags(ab, i) & CE_ATTR_DIS_INTR)
			जारी;

		irq_idx = ATH11K_PCI_IRQ_CE0_OFFSET + i;
		synchronize_irq(ab->irq_num[irq_idx]);
	पूर्ण
पूर्ण

अटल व्योम ath11k_pci_ce_tasklet(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा ath11k_ce_pipe *ce_pipe = from_tasklet(ce_pipe, t, पूर्णांकr_tq);

	ath11k_ce_per_engine_service(ce_pipe->ab, ce_pipe->pipe_num);

	ath11k_pci_ce_irq_enable(ce_pipe->ab, ce_pipe->pipe_num);
पूर्ण

अटल irqवापस_t ath11k_pci_ce_पूर्णांकerrupt_handler(पूर्णांक irq, व्योम *arg)
अणु
	काष्ठा ath11k_ce_pipe *ce_pipe = arg;

	/* last पूर्णांकerrupt received क्रम this CE */
	ce_pipe->बारtamp = jअगरfies;

	ath11k_pci_ce_irq_disable(ce_pipe->ab, ce_pipe->pipe_num);
	tasklet_schedule(&ce_pipe->पूर्णांकr_tq);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम ath11k_pci_ext_grp_disable(काष्ठा ath11k_ext_irq_grp *irq_grp)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < irq_grp->num_irq; i++)
		disable_irq_nosync(irq_grp->ab->irq_num[irq_grp->irqs[i]]);
पूर्ण

अटल व्योम __ath11k_pci_ext_irq_disable(काष्ठा ath11k_base *sc)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ATH11K_EXT_IRQ_GRP_NUM_MAX; i++) अणु
		काष्ठा ath11k_ext_irq_grp *irq_grp = &sc->ext_irq_grp[i];

		ath11k_pci_ext_grp_disable(irq_grp);

		napi_synchronize(&irq_grp->napi);
		napi_disable(&irq_grp->napi);
	पूर्ण
पूर्ण

अटल व्योम ath11k_pci_ext_grp_enable(काष्ठा ath11k_ext_irq_grp *irq_grp)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < irq_grp->num_irq; i++)
		enable_irq(irq_grp->ab->irq_num[irq_grp->irqs[i]]);
पूर्ण

अटल व्योम ath11k_pci_ext_irq_enable(काष्ठा ath11k_base *ab)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ATH11K_EXT_IRQ_GRP_NUM_MAX; i++) अणु
		काष्ठा ath11k_ext_irq_grp *irq_grp = &ab->ext_irq_grp[i];

		napi_enable(&irq_grp->napi);
		ath11k_pci_ext_grp_enable(irq_grp);
	पूर्ण
पूर्ण

अटल व्योम ath11k_pci_sync_ext_irqs(काष्ठा ath11k_base *ab)
अणु
	पूर्णांक i, j, irq_idx;

	क्रम (i = 0; i < ATH11K_EXT_IRQ_GRP_NUM_MAX; i++) अणु
		काष्ठा ath11k_ext_irq_grp *irq_grp = &ab->ext_irq_grp[i];

		क्रम (j = 0; j < irq_grp->num_irq; j++) अणु
			irq_idx = irq_grp->irqs[j];
			synchronize_irq(ab->irq_num[irq_idx]);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम ath11k_pci_ext_irq_disable(काष्ठा ath11k_base *ab)
अणु
	__ath11k_pci_ext_irq_disable(ab);
	ath11k_pci_sync_ext_irqs(ab);
पूर्ण

अटल पूर्णांक ath11k_pci_ext_grp_napi_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा ath11k_ext_irq_grp *irq_grp = container_of(napi,
						काष्ठा ath11k_ext_irq_grp,
						napi);
	काष्ठा ath11k_base *ab = irq_grp->ab;
	पूर्णांक work_करोne;

	work_करोne = ath11k_dp_service_srng(ab, irq_grp, budget);
	अगर (work_करोne < budget) अणु
		napi_complete_करोne(napi, work_करोne);
		ath11k_pci_ext_grp_enable(irq_grp);
	पूर्ण

	अगर (work_करोne > budget)
		work_करोne = budget;

	वापस work_करोne;
पूर्ण

अटल irqवापस_t ath11k_pci_ext_पूर्णांकerrupt_handler(पूर्णांक irq, व्योम *arg)
अणु
	काष्ठा ath11k_ext_irq_grp *irq_grp = arg;

	ath11k_dbg(irq_grp->ab, ATH11K_DBG_PCI, "ext irq:%d\n", irq);

	/* last पूर्णांकerrupt received क्रम this group */
	irq_grp->बारtamp = jअगरfies;

	ath11k_pci_ext_grp_disable(irq_grp);

	napi_schedule(&irq_grp->napi);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक ath11k_pci_ext_irq_config(काष्ठा ath11k_base *ab)
अणु
	पूर्णांक i, j, ret, num_vectors = 0;
	u32 user_base_data = 0, base_vector = 0, base_idx;

	base_idx = ATH11K_PCI_IRQ_CE0_OFFSET + CE_COUNT_MAX;
	ret = ath11k_pci_get_user_msi_assignment(ath11k_pci_priv(ab), "DP",
						 &num_vectors,
						 &user_base_data,
						 &base_vector);
	अगर (ret < 0)
		वापस ret;

	क्रम (i = 0; i < ATH11K_EXT_IRQ_GRP_NUM_MAX; i++) अणु
		काष्ठा ath11k_ext_irq_grp *irq_grp = &ab->ext_irq_grp[i];
		u32 num_irq = 0;

		irq_grp->ab = ab;
		irq_grp->grp_id = i;
		init_dummy_netdev(&irq_grp->napi_ndev);
		netअगर_napi_add(&irq_grp->napi_ndev, &irq_grp->napi,
			       ath11k_pci_ext_grp_napi_poll, NAPI_POLL_WEIGHT);

		अगर (ab->hw_params.ring_mask->tx[i] ||
		    ab->hw_params.ring_mask->rx[i] ||
		    ab->hw_params.ring_mask->rx_err[i] ||
		    ab->hw_params.ring_mask->rx_wbm_rel[i] ||
		    ab->hw_params.ring_mask->reo_status[i] ||
		    ab->hw_params.ring_mask->rxdma2host[i] ||
		    ab->hw_params.ring_mask->host2rxdma[i] ||
		    ab->hw_params.ring_mask->rx_mon_status[i]) अणु
			num_irq = 1;
		पूर्ण

		irq_grp->num_irq = num_irq;
		irq_grp->irqs[0] = base_idx + i;

		क्रम (j = 0; j < irq_grp->num_irq; j++) अणु
			पूर्णांक irq_idx = irq_grp->irqs[j];
			पूर्णांक vector = (i % num_vectors) + base_vector;
			पूर्णांक irq = ath11k_pci_get_msi_irq(ab->dev, vector);

			ab->irq_num[irq_idx] = irq;

			ath11k_dbg(ab, ATH11K_DBG_PCI,
				   "irq:%d group:%d\n", irq, i);

			irq_set_status_flags(irq, IRQ_DISABLE_UNLAZY);
			ret = request_irq(irq, ath11k_pci_ext_पूर्णांकerrupt_handler,
					  IRQF_SHARED,
					  "DP_EXT_IRQ", irq_grp);
			अगर (ret) अणु
				ath11k_err(ab, "failed request irq %d: %d\n",
					   vector, ret);
				वापस ret;
			पूर्ण

			disable_irq_nosync(ab->irq_num[irq_idx]);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ath11k_pci_config_irq(काष्ठा ath11k_base *ab)
अणु
	काष्ठा ath11k_ce_pipe *ce_pipe;
	u32 msi_data_start;
	u32 msi_data_count, msi_data_idx;
	u32 msi_irq_start;
	अचिन्हित पूर्णांक msi_data;
	पूर्णांक irq, i, ret, irq_idx;

	ret = ath11k_pci_get_user_msi_assignment(ath11k_pci_priv(ab),
						 "CE", &msi_data_count,
						 &msi_data_start, &msi_irq_start);
	अगर (ret)
		वापस ret;

	/* Configure CE irqs */
	क्रम (i = 0, msi_data_idx = 0; i < ab->hw_params.ce_count; i++) अणु
		अगर (ath11k_ce_get_attr_flags(ab, i) & CE_ATTR_DIS_INTR)
			जारी;

		msi_data = (msi_data_idx % msi_data_count) + msi_irq_start;
		irq = ath11k_pci_get_msi_irq(ab->dev, msi_data);
		ce_pipe = &ab->ce.ce_pipe[i];

		irq_idx = ATH11K_PCI_IRQ_CE0_OFFSET + i;

		tasklet_setup(&ce_pipe->पूर्णांकr_tq, ath11k_pci_ce_tasklet);

		ret = request_irq(irq, ath11k_pci_ce_पूर्णांकerrupt_handler,
				  IRQF_SHARED, irq_name[irq_idx],
				  ce_pipe);
		अगर (ret) अणु
			ath11k_err(ab, "failed to request irq %d: %d\n",
				   irq_idx, ret);
			वापस ret;
		पूर्ण

		ab->irq_num[irq_idx] = irq;
		msi_data_idx++;

		ath11k_pci_ce_irq_disable(ab, i);
	पूर्ण

	ret = ath11k_pci_ext_irq_config(ab);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल व्योम ath11k_pci_init_qmi_ce_config(काष्ठा ath11k_base *ab)
अणु
	काष्ठा ath11k_qmi_ce_cfg *cfg = &ab->qmi.ce_cfg;

	cfg->tgt_ce = ab->hw_params.target_ce_config;
	cfg->tgt_ce_len = ab->hw_params.target_ce_count;

	cfg->svc_to_ce_map = ab->hw_params.svc_to_ce_map;
	cfg->svc_to_ce_map_len = ab->hw_params.svc_to_ce_map_len;
	ab->qmi.service_ins_id = ab->hw_params.qmi_service_ins_id;

	ath11k_ce_get_shaकरोw_config(ab, &cfg->shaकरोw_reg_v2,
				    &cfg->shaकरोw_reg_v2_len);
पूर्ण

अटल व्योम ath11k_pci_ce_irqs_enable(काष्ठा ath11k_base *ab)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ab->hw_params.ce_count; i++) अणु
		अगर (ath11k_ce_get_attr_flags(ab, i) & CE_ATTR_DIS_INTR)
			जारी;
		ath11k_pci_ce_irq_enable(ab, i);
	पूर्ण
पूर्ण

अटल पूर्णांक ath11k_pci_enable_msi(काष्ठा ath11k_pci *ab_pci)
अणु
	काष्ठा ath11k_base *ab = ab_pci->ab;
	स्थिर काष्ठा ath11k_msi_config *msi_config = ab_pci->msi_config;
	काष्ठा msi_desc *msi_desc;
	पूर्णांक num_vectors;
	पूर्णांक ret;

	num_vectors = pci_alloc_irq_vectors(ab_pci->pdev,
					    msi_config->total_vectors,
					    msi_config->total_vectors,
					    PCI_IRQ_MSI);
	अगर (num_vectors != msi_config->total_vectors) अणु
		ath11k_err(ab, "failed to get %d MSI vectors, only %d available",
			   msi_config->total_vectors, num_vectors);

		अगर (num_vectors >= 0)
			वापस -EINVAL;
		अन्यथा
			वापस num_vectors;
	पूर्ण

	msi_desc = irq_get_msi_desc(ab_pci->pdev->irq);
	अगर (!msi_desc) अणु
		ath11k_err(ab, "msi_desc is NULL!\n");
		ret = -EINVAL;
		जाओ मुक्त_msi_vector;
	पूर्ण

	ab_pci->msi_ep_base_data = msi_desc->msg.data;
	अगर (msi_desc->msi_attrib.is_64)
		set_bit(ATH11K_PCI_FLAG_IS_MSI_64, &ab_pci->flags);

	ath11k_dbg(ab, ATH11K_DBG_PCI, "msi base data is %d\n", ab_pci->msi_ep_base_data);

	वापस 0;

मुक्त_msi_vector:
	pci_मुक्त_irq_vectors(ab_pci->pdev);

	वापस ret;
पूर्ण

अटल व्योम ath11k_pci_disable_msi(काष्ठा ath11k_pci *ab_pci)
अणु
	pci_मुक्त_irq_vectors(ab_pci->pdev);
पूर्ण

अटल पूर्णांक ath11k_pci_claim(काष्ठा ath11k_pci *ab_pci, काष्ठा pci_dev *pdev)
अणु
	काष्ठा ath11k_base *ab = ab_pci->ab;
	u16 device_id;
	पूर्णांक ret = 0;

	pci_पढ़ो_config_word(pdev, PCI_DEVICE_ID, &device_id);
	अगर (device_id != ab_pci->dev_id)  अणु
		ath11k_err(ab, "pci device id mismatch: 0x%x 0x%x\n",
			   device_id, ab_pci->dev_id);
		ret = -EIO;
		जाओ out;
	पूर्ण

	ret = pci_assign_resource(pdev, ATH11K_PCI_BAR_NUM);
	अगर (ret) अणु
		ath11k_err(ab, "failed to assign pci resource: %d\n", ret);
		जाओ out;
	पूर्ण

	ret = pci_enable_device(pdev);
	अगर (ret) अणु
		ath11k_err(ab, "failed to enable pci device: %d\n", ret);
		जाओ out;
	पूर्ण

	ret = pci_request_region(pdev, ATH11K_PCI_BAR_NUM, "ath11k_pci");
	अगर (ret) अणु
		ath11k_err(ab, "failed to request pci region: %d\n", ret);
		जाओ disable_device;
	पूर्ण

	ret = pci_set_dma_mask(pdev, DMA_BIT_MASK(ATH11K_PCI_DMA_MASK));
	अगर (ret) अणु
		ath11k_err(ab, "failed to set pci dma mask to %d: %d\n",
			   ATH11K_PCI_DMA_MASK, ret);
		जाओ release_region;
	पूर्ण

	ret = pci_set_consistent_dma_mask(pdev, DMA_BIT_MASK(ATH11K_PCI_DMA_MASK));
	अगर (ret) अणु
		ath11k_err(ab, "failed to set pci consistent dma mask to %d: %d\n",
			   ATH11K_PCI_DMA_MASK, ret);
		जाओ release_region;
	पूर्ण

	pci_set_master(pdev);

	ab->mem_len = pci_resource_len(pdev, ATH11K_PCI_BAR_NUM);
	ab->mem = pci_iomap(pdev, ATH11K_PCI_BAR_NUM, 0);
	अगर (!ab->mem) अणु
		ath11k_err(ab, "failed to map pci bar %d\n", ATH11K_PCI_BAR_NUM);
		ret = -EIO;
		जाओ clear_master;
	पूर्ण

	ath11k_dbg(ab, ATH11K_DBG_BOOT, "boot pci_mem 0x%pK\n", ab->mem);
	वापस 0;

clear_master:
	pci_clear_master(pdev);
release_region:
	pci_release_region(pdev, ATH11K_PCI_BAR_NUM);
disable_device:
	pci_disable_device(pdev);
out:
	वापस ret;
पूर्ण

अटल व्योम ath11k_pci_मुक्त_region(काष्ठा ath11k_pci *ab_pci)
अणु
	काष्ठा ath11k_base *ab = ab_pci->ab;
	काष्ठा pci_dev *pci_dev = ab_pci->pdev;

	pci_iounmap(pci_dev, ab->mem);
	ab->mem = शून्य;
	pci_clear_master(pci_dev);
	pci_release_region(pci_dev, ATH11K_PCI_BAR_NUM);
	अगर (pci_is_enabled(pci_dev))
		pci_disable_device(pci_dev);
पूर्ण

अटल व्योम ath11k_pci_aspm_disable(काष्ठा ath11k_pci *ab_pci)
अणु
	काष्ठा ath11k_base *ab = ab_pci->ab;

	pcie_capability_पढ़ो_word(ab_pci->pdev, PCI_EXP_LNKCTL,
				  &ab_pci->link_ctl);

	ath11k_dbg(ab, ATH11K_DBG_PCI, "pci link_ctl 0x%04x L0s %d L1 %d\n",
		   ab_pci->link_ctl,
		   u16_get_bits(ab_pci->link_ctl, PCI_EXP_LNKCTL_ASPM_L0S),
		   u16_get_bits(ab_pci->link_ctl, PCI_EXP_LNKCTL_ASPM_L1));

	/* disable L0s and L1 */
	pcie_capability_ग_लिखो_word(ab_pci->pdev, PCI_EXP_LNKCTL,
				   ab_pci->link_ctl & ~PCI_EXP_LNKCTL_ASPMC);

	set_bit(ATH11K_PCI_ASPM_RESTORE, &ab_pci->flags);
पूर्ण

अटल व्योम ath11k_pci_aspm_restore(काष्ठा ath11k_pci *ab_pci)
अणु
	अगर (test_and_clear_bit(ATH11K_PCI_ASPM_RESTORE, &ab_pci->flags))
		pcie_capability_ग_लिखो_word(ab_pci->pdev, PCI_EXP_LNKCTL,
					   ab_pci->link_ctl);
पूर्ण

अटल पूर्णांक ath11k_pci_घातer_up(काष्ठा ath11k_base *ab)
अणु
	काष्ठा ath11k_pci *ab_pci = ath11k_pci_priv(ab);
	पूर्णांक ret;

	ab_pci->रेजिस्टर_winकरोw = 0;
	clear_bit(ATH11K_PCI_FLAG_INIT_DONE, &ab_pci->flags);
	ath11k_pci_sw_reset(ab_pci->ab, true);

	/* Disable ASPM during firmware करोwnload due to problems चयनing
	 * to AMSS state.
	 */
	ath11k_pci_aspm_disable(ab_pci);

	ret = ath11k_mhi_start(ab_pci);
	अगर (ret) अणु
		ath11k_err(ab, "failed to start mhi: %d\n", ret);
		वापस ret;
	पूर्ण

	अगर (ab->bus_params.अटल_winकरोw_map)
		ath11k_pci_select_अटल_winकरोw(ab_pci);

	वापस 0;
पूर्ण

अटल व्योम ath11k_pci_घातer_करोwn(काष्ठा ath11k_base *ab)
अणु
	काष्ठा ath11k_pci *ab_pci = ath11k_pci_priv(ab);

	/* restore aspm in हाल firmware bootup fails */
	ath11k_pci_aspm_restore(ab_pci);

	ath11k_pci_क्रमce_wake(ab_pci->ab);
	ath11k_mhi_stop(ab_pci);
	clear_bit(ATH11K_PCI_FLAG_INIT_DONE, &ab_pci->flags);
	ath11k_pci_sw_reset(ab_pci->ab, false);
पूर्ण

अटल पूर्णांक ath11k_pci_hअगर_suspend(काष्ठा ath11k_base *ab)
अणु
	काष्ठा ath11k_pci *ar_pci = ath11k_pci_priv(ab);

	ath11k_mhi_suspend(ar_pci);

	वापस 0;
पूर्ण

अटल पूर्णांक ath11k_pci_hअगर_resume(काष्ठा ath11k_base *ab)
अणु
	काष्ठा ath11k_pci *ar_pci = ath11k_pci_priv(ab);

	ath11k_mhi_resume(ar_pci);

	वापस 0;
पूर्ण

अटल व्योम ath11k_pci_समाप्त_tasklets(काष्ठा ath11k_base *ab)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ab->hw_params.ce_count; i++) अणु
		काष्ठा ath11k_ce_pipe *ce_pipe = &ab->ce.ce_pipe[i];

		अगर (ath11k_ce_get_attr_flags(ab, i) & CE_ATTR_DIS_INTR)
			जारी;

		tasklet_समाप्त(&ce_pipe->पूर्णांकr_tq);
	पूर्ण
पूर्ण

अटल व्योम ath11k_pci_ce_irq_disable_sync(काष्ठा ath11k_base *ab)
अणु
	ath11k_pci_ce_irqs_disable(ab);
	ath11k_pci_sync_ce_irqs(ab);
	ath11k_pci_समाप्त_tasklets(ab);
पूर्ण

अटल व्योम ath11k_pci_stop(काष्ठा ath11k_base *ab)
अणु
	ath11k_pci_ce_irq_disable_sync(ab);
	ath11k_ce_cleanup_pipes(ab);
पूर्ण

अटल पूर्णांक ath11k_pci_start(काष्ठा ath11k_base *ab)
अणु
	काष्ठा ath11k_pci *ab_pci = ath11k_pci_priv(ab);

	set_bit(ATH11K_PCI_FLAG_INIT_DONE, &ab_pci->flags);

	ath11k_pci_aspm_restore(ab_pci);

	ath11k_pci_ce_irqs_enable(ab);
	ath11k_ce_rx_post_buf(ab);

	वापस 0;
पूर्ण

अटल व्योम ath11k_pci_hअगर_ce_irq_enable(काष्ठा ath11k_base *ab)
अणु
	ath11k_pci_ce_irqs_enable(ab);
पूर्ण

अटल व्योम ath11k_pci_hअगर_ce_irq_disable(काष्ठा ath11k_base *ab)
अणु
	ath11k_pci_ce_irq_disable_sync(ab);
पूर्ण

अटल पूर्णांक ath11k_pci_map_service_to_pipe(काष्ठा ath11k_base *ab, u16 service_id,
					  u8 *ul_pipe, u8 *dl_pipe)
अणु
	स्थिर काष्ठा service_to_pipe *entry;
	bool ul_set = false, dl_set = false;
	पूर्णांक i;

	क्रम (i = 0; i < ab->hw_params.svc_to_ce_map_len; i++) अणु
		entry = &ab->hw_params.svc_to_ce_map[i];

		अगर (__le32_to_cpu(entry->service_id) != service_id)
			जारी;

		चयन (__le32_to_cpu(entry->pipedir)) अणु
		हाल PIPEसूची_NONE:
			अवरोध;
		हाल PIPEसूची_IN:
			WARN_ON(dl_set);
			*dl_pipe = __le32_to_cpu(entry->pipक्रमागत);
			dl_set = true;
			अवरोध;
		हाल PIPEसूची_OUT:
			WARN_ON(ul_set);
			*ul_pipe = __le32_to_cpu(entry->pipक्रमागत);
			ul_set = true;
			अवरोध;
		हाल PIPEसूची_INOUT:
			WARN_ON(dl_set);
			WARN_ON(ul_set);
			*dl_pipe = __le32_to_cpu(entry->pipक्रमागत);
			*ul_pipe = __le32_to_cpu(entry->pipक्रमागत);
			dl_set = true;
			ul_set = true;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (WARN_ON(!ul_set || !dl_set))
		वापस -ENOENT;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा ath11k_hअगर_ops ath11k_pci_hअगर_ops = अणु
	.start = ath11k_pci_start,
	.stop = ath11k_pci_stop,
	.पढ़ो32 = ath11k_pci_पढ़ो32,
	.ग_लिखो32 = ath11k_pci_ग_लिखो32,
	.घातer_करोwn = ath11k_pci_घातer_करोwn,
	.घातer_up = ath11k_pci_घातer_up,
	.suspend = ath11k_pci_hअगर_suspend,
	.resume = ath11k_pci_hअगर_resume,
	.irq_enable = ath11k_pci_ext_irq_enable,
	.irq_disable = ath11k_pci_ext_irq_disable,
	.get_msi_address =  ath11k_pci_get_msi_address,
	.get_user_msi_vector = ath11k_get_user_msi_assignment,
	.map_service_to_pipe = ath11k_pci_map_service_to_pipe,
	.ce_irq_enable = ath11k_pci_hअगर_ce_irq_enable,
	.ce_irq_disable = ath11k_pci_hअगर_ce_irq_disable,
	.get_ce_msi_idx = ath11k_pci_get_ce_msi_idx,
पूर्ण;

अटल पूर्णांक ath11k_pci_probe(काष्ठा pci_dev *pdev,
			    स्थिर काष्ठा pci_device_id *pci_dev)
अणु
	काष्ठा ath11k_base *ab;
	काष्ठा ath11k_pci *ab_pci;
	u32 soc_hw_version, soc_hw_version_major, soc_hw_version_minor;
	पूर्णांक ret;

	ab = ath11k_core_alloc(&pdev->dev, माप(*ab_pci), ATH11K_BUS_PCI,
			       &ath11k_pci_bus_params);
	अगर (!ab) अणु
		dev_err(&pdev->dev, "failed to allocate ath11k base\n");
		वापस -ENOMEM;
	पूर्ण

	ab->dev = &pdev->dev;
	pci_set_drvdata(pdev, ab);
	ab_pci = ath11k_pci_priv(ab);
	ab_pci->dev_id = pci_dev->device;
	ab_pci->ab = ab;
	ab_pci->pdev = pdev;
	ab->hअगर.ops = &ath11k_pci_hअगर_ops;
	pci_set_drvdata(pdev, ab);
	spin_lock_init(&ab_pci->winकरोw_lock);

	ret = ath11k_pci_claim(ab_pci, pdev);
	अगर (ret) अणु
		ath11k_err(ab, "failed to claim device: %d\n", ret);
		जाओ err_मुक्त_core;
	पूर्ण

	चयन (pci_dev->device) अणु
	हाल QCA6390_DEVICE_ID:
		soc_hw_version = ath11k_pci_पढ़ो32(ab, TCSR_SOC_HW_VERSION);
		soc_hw_version_major = FIELD_GET(TCSR_SOC_HW_VERSION_MAJOR_MASK,
						 soc_hw_version);
		soc_hw_version_minor = FIELD_GET(TCSR_SOC_HW_VERSION_MINOR_MASK,
						 soc_hw_version);

		ath11k_dbg(ab, ATH11K_DBG_PCI, "pci tcsr_soc_hw_version major %d minor %d\n",
			   soc_hw_version_major, soc_hw_version_minor);

		चयन (soc_hw_version_major) अणु
		हाल 2:
			ab->hw_rev = ATH11K_HW_QCA6390_HW20;
			अवरोध;
		शेष:
			dev_err(&pdev->dev, "Unsupported QCA6390 SOC hardware version: %d %d\n",
				soc_hw_version_major, soc_hw_version_minor);
			ret = -EOPNOTSUPP;
			जाओ err_pci_मुक्त_region;
		पूर्ण
		ab_pci->msi_config = &ath11k_msi_config[0];
		अवरोध;
	हाल QCN9074_DEVICE_ID:
		ab_pci->msi_config = &ath11k_msi_config[1];
		ab->bus_params.अटल_winकरोw_map = true;
		ab->hw_rev = ATH11K_HW_QCN9074_HW10;
		अवरोध;
	शेष:
		dev_err(&pdev->dev, "Unknown PCI device found: 0x%x\n",
			pci_dev->device);
		ret = -EOPNOTSUPP;
		जाओ err_pci_मुक्त_region;
	पूर्ण

	ret = ath11k_pci_enable_msi(ab_pci);
	अगर (ret) अणु
		ath11k_err(ab, "failed to enable msi: %d\n", ret);
		जाओ err_pci_मुक्त_region;
	पूर्ण

	ret = ath11k_core_pre_init(ab);
	अगर (ret)
		जाओ err_pci_disable_msi;

	ret = ath11k_mhi_रेजिस्टर(ab_pci);
	अगर (ret) अणु
		ath11k_err(ab, "failed to register mhi: %d\n", ret);
		जाओ err_pci_disable_msi;
	पूर्ण

	ret = ath11k_hal_srng_init(ab);
	अगर (ret)
		जाओ err_mhi_unरेजिस्टर;

	ret = ath11k_ce_alloc_pipes(ab);
	अगर (ret) अणु
		ath11k_err(ab, "failed to allocate ce pipes: %d\n", ret);
		जाओ err_hal_srng_deinit;
	पूर्ण

	ath11k_pci_init_qmi_ce_config(ab);

	ret = ath11k_pci_config_irq(ab);
	अगर (ret) अणु
		ath11k_err(ab, "failed to config irq: %d\n", ret);
		जाओ err_ce_मुक्त;
	पूर्ण

	ret = ath11k_core_init(ab);
	अगर (ret) अणु
		ath11k_err(ab, "failed to init core: %d\n", ret);
		जाओ err_मुक्त_irq;
	पूर्ण
	वापस 0;

err_मुक्त_irq:
	ath11k_pci_मुक्त_irq(ab);

err_ce_मुक्त:
	ath11k_ce_मुक्त_pipes(ab);

err_hal_srng_deinit:
	ath11k_hal_srng_deinit(ab);

err_mhi_unरेजिस्टर:
	ath11k_mhi_unरेजिस्टर(ab_pci);

err_pci_disable_msi:
	ath11k_pci_disable_msi(ab_pci);

err_pci_मुक्त_region:
	ath11k_pci_मुक्त_region(ab_pci);

err_मुक्त_core:
	ath11k_core_मुक्त(ab);

	वापस ret;
पूर्ण

अटल व्योम ath11k_pci_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा ath11k_base *ab = pci_get_drvdata(pdev);
	काष्ठा ath11k_pci *ab_pci = ath11k_pci_priv(ab);

	अगर (test_bit(ATH11K_FLAG_QMI_FAIL, &ab->dev_flags)) अणु
		ath11k_pci_घातer_करोwn(ab);
		ath11k_debugfs_soc_destroy(ab);
		ath11k_qmi_deinit_service(ab);
		जाओ qmi_fail;
	पूर्ण

	set_bit(ATH11K_FLAG_UNREGISTERING, &ab->dev_flags);

	ath11k_core_deinit(ab);

qmi_fail:
	ath11k_mhi_unरेजिस्टर(ab_pci);

	ath11k_pci_मुक्त_irq(ab);
	ath11k_pci_disable_msi(ab_pci);
	ath11k_pci_मुक्त_region(ab_pci);

	ath11k_hal_srng_deinit(ab);
	ath11k_ce_मुक्त_pipes(ab);
	ath11k_core_मुक्त(ab);
पूर्ण

अटल व्योम ath11k_pci_shutकरोwn(काष्ठा pci_dev *pdev)
अणु
	काष्ठा ath11k_base *ab = pci_get_drvdata(pdev);

	ath11k_pci_घातer_करोwn(ab);
पूर्ण

अटल __maybe_unused पूर्णांक ath11k_pci_pm_suspend(काष्ठा device *dev)
अणु
	काष्ठा ath11k_base *ab = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = ath11k_core_suspend(ab);
	अगर (ret)
		ath11k_warn(ab, "failed to suspend core: %d\n", ret);

	वापस ret;
पूर्ण

अटल __maybe_unused पूर्णांक ath11k_pci_pm_resume(काष्ठा device *dev)
अणु
	काष्ठा ath11k_base *ab = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = ath11k_core_resume(ab);
	अगर (ret)
		ath11k_warn(ab, "failed to resume core: %d\n", ret);

	वापस ret;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(ath11k_pci_pm_ops,
			 ath11k_pci_pm_suspend,
			 ath11k_pci_pm_resume);

अटल काष्ठा pci_driver ath11k_pci_driver = अणु
	.name = "ath11k_pci",
	.id_table = ath11k_pci_id_table,
	.probe = ath11k_pci_probe,
	.हटाओ = ath11k_pci_हटाओ,
	.shutकरोwn = ath11k_pci_shutकरोwn,
#अगर_घोषित CONFIG_PM
	.driver.pm = &ath11k_pci_pm_ops,
#पूर्ण_अगर
पूर्ण;

अटल पूर्णांक ath11k_pci_init(व्योम)
अणु
	पूर्णांक ret;

	ret = pci_रेजिस्टर_driver(&ath11k_pci_driver);
	अगर (ret)
		pr_err("failed to register ath11k pci driver: %d\n",
		       ret);

	वापस ret;
पूर्ण
module_init(ath11k_pci_init);

अटल व्योम ath11k_pci_निकास(व्योम)
अणु
	pci_unरेजिस्टर_driver(&ath11k_pci_driver);
पूर्ण

module_निकास(ath11k_pci_निकास);

MODULE_DESCRIPTION("Driver support for Qualcomm Technologies 802.11ax WLAN PCIe devices");
MODULE_LICENSE("Dual BSD/GPL");

/* QCA639x 2.0 firmware files */
MODULE_FIRMWARE(ATH11K_FW_सूची "/QCA6390/hw2.0/" ATH11K_BOARD_API2_खाता);
MODULE_FIRMWARE(ATH11K_FW_सूची "/QCA6390/hw2.0/" ATH11K_AMSS_खाता);
MODULE_FIRMWARE(ATH11K_FW_सूची "/QCA6390/hw2.0/" ATH11K_M3_खाता);
