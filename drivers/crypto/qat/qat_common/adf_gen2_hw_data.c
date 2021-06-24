<शैली गुरु>
// SPDX-License-Identअगरier: (BSD-3-Clause OR GPL-2.0-only)
/* Copyright(c) 2020 Intel Corporation */
#समावेश "adf_gen2_hw_data.h"
#समावेश "icp_qat_hw.h"
#समावेश <linux/pci.h>

व्योम adf_gen2_cfg_iov_thds(काष्ठा adf_accel_dev *accel_dev, bool enable,
			   पूर्णांक num_a_regs, पूर्णांक num_b_regs)
अणु
	काष्ठा adf_hw_device_data *hw_data = accel_dev->hw_device;
	व्योम __iomem *pmisc_addr;
	काष्ठा adf_bar *pmisc;
	पूर्णांक pmisc_id, i;
	u32 reg;

	pmisc_id = hw_data->get_misc_bar_id(hw_data);
	pmisc = &GET_BARS(accel_dev)[pmisc_id];
	pmisc_addr = pmisc->virt_addr;

	/* Set/Unset Valid bit in AE Thपढ़ो to PCIe Function Mapping Group A */
	क्रम (i = 0; i < num_a_regs; i++) अणु
		reg = READ_CSR_AE2FUNCTION_MAP_A(pmisc_addr, i);
		अगर (enable)
			reg |= AE2FUNCTION_MAP_VALID;
		अन्यथा
			reg &= ~AE2FUNCTION_MAP_VALID;
		WRITE_CSR_AE2FUNCTION_MAP_A(pmisc_addr, i, reg);
	पूर्ण

	/* Set/Unset Valid bit in AE Thपढ़ो to PCIe Function Mapping Group B */
	क्रम (i = 0; i < num_b_regs; i++) अणु
		reg = READ_CSR_AE2FUNCTION_MAP_B(pmisc_addr, i);
		अगर (enable)
			reg |= AE2FUNCTION_MAP_VALID;
		अन्यथा
			reg &= ~AE2FUNCTION_MAP_VALID;
		WRITE_CSR_AE2FUNCTION_MAP_B(pmisc_addr, i, reg);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(adf_gen2_cfg_iov_thds);

व्योम adf_gen2_get_admin_info(काष्ठा admin_info *admin_csrs_info)
अणु
	admin_csrs_info->mailbox_offset = ADF_MAILBOX_BASE_OFFSET;
	admin_csrs_info->admin_msg_ur = ADF_ADMINMSGUR_OFFSET;
	admin_csrs_info->admin_msg_lr = ADF_ADMINMSGLR_OFFSET;
पूर्ण
EXPORT_SYMBOL_GPL(adf_gen2_get_admin_info);

व्योम adf_gen2_get_arb_info(काष्ठा arb_info *arb_info)
अणु
	arb_info->arb_cfg = ADF_ARB_CONFIG;
	arb_info->arb_offset = ADF_ARB_OFFSET;
	arb_info->wt2sam_offset = ADF_ARB_WRK_2_SER_MAP_OFFSET;
पूर्ण
EXPORT_SYMBOL_GPL(adf_gen2_get_arb_info);

अटल u64 build_csr_ring_base_addr(dma_addr_t addr, u32 size)
अणु
	वापस BUILD_RING_BASE_ADDR(addr, size);
पूर्ण

अटल u32 पढ़ो_csr_ring_head(व्योम __iomem *csr_base_addr, u32 bank, u32 ring)
अणु
	वापस READ_CSR_RING_HEAD(csr_base_addr, bank, ring);
पूर्ण

अटल व्योम ग_लिखो_csr_ring_head(व्योम __iomem *csr_base_addr, u32 bank, u32 ring,
				u32 value)
अणु
	WRITE_CSR_RING_HEAD(csr_base_addr, bank, ring, value);
पूर्ण

अटल u32 पढ़ो_csr_ring_tail(व्योम __iomem *csr_base_addr, u32 bank, u32 ring)
अणु
	वापस READ_CSR_RING_TAIL(csr_base_addr, bank, ring);
पूर्ण

अटल व्योम ग_लिखो_csr_ring_tail(व्योम __iomem *csr_base_addr, u32 bank, u32 ring,
				u32 value)
अणु
	WRITE_CSR_RING_TAIL(csr_base_addr, bank, ring, value);
पूर्ण

अटल u32 पढ़ो_csr_e_stat(व्योम __iomem *csr_base_addr, u32 bank)
अणु
	वापस READ_CSR_E_STAT(csr_base_addr, bank);
पूर्ण

अटल व्योम ग_लिखो_csr_ring_config(व्योम __iomem *csr_base_addr, u32 bank,
				  u32 ring, u32 value)
अणु
	WRITE_CSR_RING_CONFIG(csr_base_addr, bank, ring, value);
पूर्ण

अटल व्योम ग_लिखो_csr_ring_base(व्योम __iomem *csr_base_addr, u32 bank, u32 ring,
				dma_addr_t addr)
अणु
	WRITE_CSR_RING_BASE(csr_base_addr, bank, ring, addr);
पूर्ण

अटल व्योम ग_लिखो_csr_पूर्णांक_flag(व्योम __iomem *csr_base_addr, u32 bank, u32 value)
अणु
	WRITE_CSR_INT_FLAG(csr_base_addr, bank, value);
पूर्ण

अटल व्योम ग_लिखो_csr_पूर्णांक_srcsel(व्योम __iomem *csr_base_addr, u32 bank)
अणु
	WRITE_CSR_INT_SRCSEL(csr_base_addr, bank);
पूर्ण

अटल व्योम ग_लिखो_csr_पूर्णांक_col_en(व्योम __iomem *csr_base_addr, u32 bank,
				 u32 value)
अणु
	WRITE_CSR_INT_COL_EN(csr_base_addr, bank, value);
पूर्ण

अटल व्योम ग_लिखो_csr_पूर्णांक_col_ctl(व्योम __iomem *csr_base_addr, u32 bank,
				  u32 value)
अणु
	WRITE_CSR_INT_COL_CTL(csr_base_addr, bank, value);
पूर्ण

अटल व्योम ग_लिखो_csr_पूर्णांक_flag_and_col(व्योम __iomem *csr_base_addr, u32 bank,
				       u32 value)
अणु
	WRITE_CSR_INT_FLAG_AND_COL(csr_base_addr, bank, value);
पूर्ण

अटल व्योम ग_लिखो_csr_ring_srv_arb_en(व्योम __iomem *csr_base_addr, u32 bank,
				      u32 value)
अणु
	WRITE_CSR_RING_SRV_ARB_EN(csr_base_addr, bank, value);
पूर्ण

व्योम adf_gen2_init_hw_csr_ops(काष्ठा adf_hw_csr_ops *csr_ops)
अणु
	csr_ops->build_csr_ring_base_addr = build_csr_ring_base_addr;
	csr_ops->पढ़ो_csr_ring_head = पढ़ो_csr_ring_head;
	csr_ops->ग_लिखो_csr_ring_head = ग_लिखो_csr_ring_head;
	csr_ops->पढ़ो_csr_ring_tail = पढ़ो_csr_ring_tail;
	csr_ops->ग_लिखो_csr_ring_tail = ग_लिखो_csr_ring_tail;
	csr_ops->पढ़ो_csr_e_stat = पढ़ो_csr_e_stat;
	csr_ops->ग_लिखो_csr_ring_config = ग_लिखो_csr_ring_config;
	csr_ops->ग_लिखो_csr_ring_base = ग_लिखो_csr_ring_base;
	csr_ops->ग_लिखो_csr_पूर्णांक_flag = ग_लिखो_csr_पूर्णांक_flag;
	csr_ops->ग_लिखो_csr_पूर्णांक_srcsel = ग_लिखो_csr_पूर्णांक_srcsel;
	csr_ops->ग_लिखो_csr_पूर्णांक_col_en = ग_लिखो_csr_पूर्णांक_col_en;
	csr_ops->ग_लिखो_csr_पूर्णांक_col_ctl = ग_लिखो_csr_पूर्णांक_col_ctl;
	csr_ops->ग_लिखो_csr_पूर्णांक_flag_and_col = ग_लिखो_csr_पूर्णांक_flag_and_col;
	csr_ops->ग_लिखो_csr_ring_srv_arb_en = ग_लिखो_csr_ring_srv_arb_en;
पूर्ण
EXPORT_SYMBOL_GPL(adf_gen2_init_hw_csr_ops);

u32 adf_gen2_get_accel_cap(काष्ठा adf_accel_dev *accel_dev)
अणु
	काष्ठा adf_hw_device_data *hw_data = accel_dev->hw_device;
	काष्ठा pci_dev *pdev = accel_dev->accel_pci_dev.pci_dev;
	u32 straps = hw_data->straps;
	u32 fuses = hw_data->fuses;
	u32 legfuses;
	u32 capabilities = ICP_ACCEL_CAPABILITIES_CRYPTO_SYMMETRIC |
			   ICP_ACCEL_CAPABILITIES_CRYPTO_ASYMMETRIC |
			   ICP_ACCEL_CAPABILITIES_AUTHENTICATION;

	/* Read accelerator capabilities mask */
	pci_पढ़ो_config_dword(pdev, ADF_DEVICE_LEGFUSE_OFFSET, &legfuses);

	अगर (legfuses & ICP_ACCEL_MASK_CIPHER_SLICE)
		capabilities &= ~ICP_ACCEL_CAPABILITIES_CRYPTO_SYMMETRIC;
	अगर (legfuses & ICP_ACCEL_MASK_PKE_SLICE)
		capabilities &= ~ICP_ACCEL_CAPABILITIES_CRYPTO_ASYMMETRIC;
	अगर (legfuses & ICP_ACCEL_MASK_AUTH_SLICE)
		capabilities &= ~ICP_ACCEL_CAPABILITIES_AUTHENTICATION;

	अगर ((straps | fuses) & ADF_POWERGATE_PKE)
		capabilities &= ~ICP_ACCEL_CAPABILITIES_CRYPTO_ASYMMETRIC;

	वापस capabilities;
पूर्ण
EXPORT_SYMBOL_GPL(adf_gen2_get_accel_cap);

व्योम adf_gen2_set_ssm_wdसमयr(काष्ठा adf_accel_dev *accel_dev)
अणु
	काष्ठा adf_hw_device_data *hw_data = accel_dev->hw_device;
	u32 समयr_val_pke = ADF_SSM_WDT_PKE_DEFAULT_VALUE;
	u32 समयr_val = ADF_SSM_WDT_DEFAULT_VALUE;
	अचिन्हित दीर्घ accel_mask = hw_data->accel_mask;
	व्योम __iomem *pmisc_addr;
	काष्ठा adf_bar *pmisc;
	पूर्णांक pmisc_id;
	u32 i = 0;

	pmisc_id = hw_data->get_misc_bar_id(hw_data);
	pmisc = &GET_BARS(accel_dev)[pmisc_id];
	pmisc_addr = pmisc->virt_addr;

	/* Configures WDT समयrs */
	क्रम_each_set_bit(i, &accel_mask, hw_data->num_accel) अणु
		/* Enable WDT क्रम sym and dc */
		ADF_CSR_WR(pmisc_addr, ADF_SSMWDT(i), समयr_val);
		/* Enable WDT क्रम pke */
		ADF_CSR_WR(pmisc_addr, ADF_SSMWDTPKE(i), समयr_val_pke);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(adf_gen2_set_ssm_wdसमयr);
