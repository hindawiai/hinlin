<शैली गुरु>
/* SPDX-License-Identअगरier: (BSD-3-Clause OR GPL-2.0-only) */
/* Copyright(c) 2020 Intel Corporation */
#अगर_अघोषित ADF_GEN2_HW_DATA_H_
#घोषणा ADF_GEN2_HW_DATA_H_

#समावेश "adf_accel_devices.h"

/* Transport access */
#घोषणा ADF_BANK_INT_SRC_SEL_MASK_0	0x4444444CUL
#घोषणा ADF_BANK_INT_SRC_SEL_MASK_X	0x44444444UL
#घोषणा ADF_RING_CSR_RING_CONFIG	0x000
#घोषणा ADF_RING_CSR_RING_LBASE		0x040
#घोषणा ADF_RING_CSR_RING_UBASE		0x080
#घोषणा ADF_RING_CSR_RING_HEAD		0x0C0
#घोषणा ADF_RING_CSR_RING_TAIL		0x100
#घोषणा ADF_RING_CSR_E_STAT		0x14C
#घोषणा ADF_RING_CSR_INT_FLAG		0x170
#घोषणा ADF_RING_CSR_INT_SRCSEL		0x174
#घोषणा ADF_RING_CSR_INT_SRCSEL_2	0x178
#घोषणा ADF_RING_CSR_INT_COL_EN		0x17C
#घोषणा ADF_RING_CSR_INT_COL_CTL	0x180
#घोषणा ADF_RING_CSR_INT_FLAG_AND_COL	0x184
#घोषणा ADF_RING_CSR_INT_COL_CTL_ENABLE	0x80000000
#घोषणा ADF_RING_BUNDLE_SIZE		0x1000

#घोषणा BUILD_RING_BASE_ADDR(addr, size) \
	(((addr) >> 6) & (GENMASK_ULL(63, 0) << (size)))
#घोषणा READ_CSR_RING_HEAD(csr_base_addr, bank, ring) \
	ADF_CSR_RD(csr_base_addr, (ADF_RING_BUNDLE_SIZE * (bank)) + \
		   ADF_RING_CSR_RING_HEAD + ((ring) << 2))
#घोषणा READ_CSR_RING_TAIL(csr_base_addr, bank, ring) \
	ADF_CSR_RD(csr_base_addr, (ADF_RING_BUNDLE_SIZE * (bank)) + \
		   ADF_RING_CSR_RING_TAIL + ((ring) << 2))
#घोषणा READ_CSR_E_STAT(csr_base_addr, bank) \
	ADF_CSR_RD(csr_base_addr, (ADF_RING_BUNDLE_SIZE * (bank)) + \
		   ADF_RING_CSR_E_STAT)
#घोषणा WRITE_CSR_RING_CONFIG(csr_base_addr, bank, ring, value) \
	ADF_CSR_WR(csr_base_addr, (ADF_RING_BUNDLE_SIZE * (bank)) + \
		   ADF_RING_CSR_RING_CONFIG + ((ring) << 2), value)
#घोषणा WRITE_CSR_RING_BASE(csr_base_addr, bank, ring, value) \
करो अणु \
	u32 l_base = 0, u_base = 0; \
	l_base = (u32)((value) & 0xFFFFFFFF); \
	u_base = (u32)(((value) & 0xFFFFFFFF00000000ULL) >> 32); \
	ADF_CSR_WR(csr_base_addr, (ADF_RING_BUNDLE_SIZE * (bank)) + \
		   ADF_RING_CSR_RING_LBASE + ((ring) << 2), l_base); \
	ADF_CSR_WR(csr_base_addr, (ADF_RING_BUNDLE_SIZE * (bank)) + \
		   ADF_RING_CSR_RING_UBASE + ((ring) << 2), u_base); \
पूर्ण जबतक (0)

#घोषणा WRITE_CSR_RING_HEAD(csr_base_addr, bank, ring, value) \
	ADF_CSR_WR(csr_base_addr, (ADF_RING_BUNDLE_SIZE * (bank)) + \
		   ADF_RING_CSR_RING_HEAD + ((ring) << 2), value)
#घोषणा WRITE_CSR_RING_TAIL(csr_base_addr, bank, ring, value) \
	ADF_CSR_WR(csr_base_addr, (ADF_RING_BUNDLE_SIZE * (bank)) + \
		   ADF_RING_CSR_RING_TAIL + ((ring) << 2), value)
#घोषणा WRITE_CSR_INT_FLAG(csr_base_addr, bank, value) \
	ADF_CSR_WR(csr_base_addr, (ADF_RING_BUNDLE_SIZE * (bank)) + \
		   ADF_RING_CSR_INT_FLAG, value)
#घोषणा WRITE_CSR_INT_SRCSEL(csr_base_addr, bank) \
करो अणु \
	ADF_CSR_WR(csr_base_addr, (ADF_RING_BUNDLE_SIZE * (bank)) + \
	ADF_RING_CSR_INT_SRCSEL, ADF_BANK_INT_SRC_SEL_MASK_0); \
	ADF_CSR_WR(csr_base_addr, (ADF_RING_BUNDLE_SIZE * (bank)) + \
	ADF_RING_CSR_INT_SRCSEL_2, ADF_BANK_INT_SRC_SEL_MASK_X); \
पूर्ण जबतक (0)
#घोषणा WRITE_CSR_INT_COL_EN(csr_base_addr, bank, value) \
	ADF_CSR_WR(csr_base_addr, (ADF_RING_BUNDLE_SIZE * (bank)) + \
		   ADF_RING_CSR_INT_COL_EN, value)
#घोषणा WRITE_CSR_INT_COL_CTL(csr_base_addr, bank, value) \
	ADF_CSR_WR(csr_base_addr, (ADF_RING_BUNDLE_SIZE * (bank)) + \
		   ADF_RING_CSR_INT_COL_CTL, \
		   ADF_RING_CSR_INT_COL_CTL_ENABLE | (value))
#घोषणा WRITE_CSR_INT_FLAG_AND_COL(csr_base_addr, bank, value) \
	ADF_CSR_WR(csr_base_addr, (ADF_RING_BUNDLE_SIZE * (bank)) + \
		   ADF_RING_CSR_INT_FLAG_AND_COL, value)

/* AE to function map */
#घोषणा AE2FUNCTION_MAP_A_OFFSET	(0x3A400 + 0x190)
#घोषणा AE2FUNCTION_MAP_B_OFFSET	(0x3A400 + 0x310)
#घोषणा AE2FUNCTION_MAP_REG_SIZE	4
#घोषणा AE2FUNCTION_MAP_VALID		BIT(7)

#घोषणा READ_CSR_AE2FUNCTION_MAP_A(pmisc_bar_addr, index) \
	ADF_CSR_RD(pmisc_bar_addr, AE2FUNCTION_MAP_A_OFFSET + \
		   AE2FUNCTION_MAP_REG_SIZE * (index))
#घोषणा WRITE_CSR_AE2FUNCTION_MAP_A(pmisc_bar_addr, index, value) \
	ADF_CSR_WR(pmisc_bar_addr, AE2FUNCTION_MAP_A_OFFSET + \
		   AE2FUNCTION_MAP_REG_SIZE * (index), value)
#घोषणा READ_CSR_AE2FUNCTION_MAP_B(pmisc_bar_addr, index) \
	ADF_CSR_RD(pmisc_bar_addr, AE2FUNCTION_MAP_B_OFFSET + \
		   AE2FUNCTION_MAP_REG_SIZE * (index))
#घोषणा WRITE_CSR_AE2FUNCTION_MAP_B(pmisc_bar_addr, index, value) \
	ADF_CSR_WR(pmisc_bar_addr, AE2FUNCTION_MAP_B_OFFSET + \
		   AE2FUNCTION_MAP_REG_SIZE * (index), value)

/* Admin Interface Offsets */
#घोषणा ADF_ADMINMSGUR_OFFSET	(0x3A000 + 0x574)
#घोषणा ADF_ADMINMSGLR_OFFSET	(0x3A000 + 0x578)
#घोषणा ADF_MAILBOX_BASE_OFFSET	0x20970

/* Arbiter configuration */
#घोषणा ADF_ARB_OFFSET			0x30000
#घोषणा ADF_ARB_WRK_2_SER_MAP_OFFSET	0x180
#घोषणा ADF_ARB_CONFIG			(BIT(31) | BIT(6) | BIT(0))
#घोषणा ADF_ARB_REG_SLOT		0x1000
#घोषणा ADF_ARB_RINGSRVARBEN_OFFSET	0x19C

#घोषणा WRITE_CSR_RING_SRV_ARB_EN(csr_addr, index, value) \
	ADF_CSR_WR(csr_addr, ADF_ARB_RINGSRVARBEN_OFFSET + \
	(ADF_ARB_REG_SLOT * (index)), value)

/* Power gating */
#घोषणा ADF_POWERGATE_PKE		BIT(24)

/* WDT समयrs
 *
 * Timeout is in cycles. Clock speed may vary across products but this
 * value should be a few milli-seconds.
 */
#घोषणा ADF_SSM_WDT_DEFAULT_VALUE	0x200000
#घोषणा ADF_SSM_WDT_PKE_DEFAULT_VALUE	0x2000000
#घोषणा ADF_SSMWDT_OFFSET		0x54
#घोषणा ADF_SSMWDTPKE_OFFSET		0x58
#घोषणा ADF_SSMWDT(i)		(ADF_SSMWDT_OFFSET + ((i) * 0x4000))
#घोषणा ADF_SSMWDTPKE(i)	(ADF_SSMWDTPKE_OFFSET + ((i) * 0x4000))

व्योम adf_gen2_cfg_iov_thds(काष्ठा adf_accel_dev *accel_dev, bool enable,
			   पूर्णांक num_a_regs, पूर्णांक num_b_regs);
व्योम adf_gen2_init_hw_csr_ops(काष्ठा adf_hw_csr_ops *csr_ops);
व्योम adf_gen2_get_admin_info(काष्ठा admin_info *admin_csrs_info);
व्योम adf_gen2_get_arb_info(काष्ठा arb_info *arb_info);
u32 adf_gen2_get_accel_cap(काष्ठा adf_accel_dev *accel_dev);
व्योम adf_gen2_set_ssm_wdसमयr(काष्ठा adf_accel_dev *accel_dev);

#पूर्ण_अगर
