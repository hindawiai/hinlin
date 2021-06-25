<शैली गुरु>
// SPDX-License-Identअगरier: (BSD-3-Clause OR GPL-2.0-only)
/* Copyright(c) 2020 Intel Corporation */
#समावेश "adf_accel_devices.h"
#समावेश "adf_gen4_hw_data.h"

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

अटल व्योम ग_लिखो_csr_ring_config(व्योम __iomem *csr_base_addr, u32 bank, u32 ring,
				  u32 value)
अणु
	WRITE_CSR_RING_CONFIG(csr_base_addr, bank, ring, value);
पूर्ण

अटल व्योम ग_लिखो_csr_ring_base(व्योम __iomem *csr_base_addr, u32 bank, u32 ring,
				dma_addr_t addr)
अणु
	WRITE_CSR_RING_BASE(csr_base_addr, bank, ring, addr);
पूर्ण

अटल व्योम ग_लिखो_csr_पूर्णांक_flag(व्योम __iomem *csr_base_addr, u32 bank,
			       u32 value)
अणु
	WRITE_CSR_INT_FLAG(csr_base_addr, bank, value);
पूर्ण

अटल व्योम ग_लिखो_csr_पूर्णांक_srcsel(व्योम __iomem *csr_base_addr, u32 bank)
अणु
	WRITE_CSR_INT_SRCSEL(csr_base_addr, bank);
पूर्ण

अटल व्योम ग_लिखो_csr_पूर्णांक_col_en(व्योम __iomem *csr_base_addr, u32 bank, u32 value)
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

व्योम adf_gen4_init_hw_csr_ops(काष्ठा adf_hw_csr_ops *csr_ops)
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
EXPORT_SYMBOL_GPL(adf_gen4_init_hw_csr_ops);

अटल अंतरभूत व्योम adf_gen4_unpack_ssm_wdसमयr(u64 value, u32 *upper,
					       u32 *lower)
अणु
	*lower = lower_32_bits(value);
	*upper = upper_32_bits(value);
पूर्ण

व्योम adf_gen4_set_ssm_wdसमयr(काष्ठा adf_accel_dev *accel_dev)
अणु
	काष्ठा adf_hw_device_data *hw_data = accel_dev->hw_device;
	u64 समयr_val_pke = ADF_SSM_WDT_PKE_DEFAULT_VALUE;
	u64 समयr_val = ADF_SSM_WDT_DEFAULT_VALUE;
	u32 ssm_wdt_pke_high = 0;
	u32 ssm_wdt_pke_low = 0;
	u32 ssm_wdt_high = 0;
	u32 ssm_wdt_low = 0;
	व्योम __iomem *pmisc_addr;
	काष्ठा adf_bar *pmisc;
	पूर्णांक pmisc_id;

	pmisc_id = hw_data->get_misc_bar_id(hw_data);
	pmisc = &GET_BARS(accel_dev)[pmisc_id];
	pmisc_addr = pmisc->virt_addr;

	/* Convert 64bit WDT समयr value पूर्णांकo 32bit values क्रम
	 * mmio ग_लिखो to 32bit CSRs.
	 */
	adf_gen4_unpack_ssm_wdसमयr(समयr_val, &ssm_wdt_high, &ssm_wdt_low);
	adf_gen4_unpack_ssm_wdसमयr(समयr_val_pke, &ssm_wdt_pke_high,
				    &ssm_wdt_pke_low);

	/* Enable WDT क्रम sym and dc */
	ADF_CSR_WR(pmisc_addr, ADF_SSMWDTL_OFFSET, ssm_wdt_low);
	ADF_CSR_WR(pmisc_addr, ADF_SSMWDTH_OFFSET, ssm_wdt_high);
	/* Enable WDT क्रम pke */
	ADF_CSR_WR(pmisc_addr, ADF_SSMWDTPKEL_OFFSET, ssm_wdt_pke_low);
	ADF_CSR_WR(pmisc_addr, ADF_SSMWDTPKEH_OFFSET, ssm_wdt_pke_high);
पूर्ण
EXPORT_SYMBOL_GPL(adf_gen4_set_ssm_wdसमयr);
