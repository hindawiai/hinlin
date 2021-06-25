<शैली गुरु>
/* SPDX-License-Identअगरier: (BSD-3-Clause OR GPL-2.0-only) */
/* Copyright(c) 2020 Intel Corporation */
#अगर_अघोषित ADF_GEN4_HW_CSR_DATA_H_
#घोषणा ADF_GEN4_HW_CSR_DATA_H_

#समावेश "adf_accel_devices.h"

/* Transport access */
#घोषणा ADF_BANK_INT_SRC_SEL_MASK	0x44UL
#घोषणा ADF_RING_CSR_RING_CONFIG	0x1000
#घोषणा ADF_RING_CSR_RING_LBASE		0x1040
#घोषणा ADF_RING_CSR_RING_UBASE		0x1080
#घोषणा ADF_RING_CSR_RING_HEAD		0x0C0
#घोषणा ADF_RING_CSR_RING_TAIL		0x100
#घोषणा ADF_RING_CSR_E_STAT		0x14C
#घोषणा ADF_RING_CSR_INT_FLAG		0x170
#घोषणा ADF_RING_CSR_INT_SRCSEL		0x174
#घोषणा ADF_RING_CSR_INT_COL_CTL	0x180
#घोषणा ADF_RING_CSR_INT_FLAG_AND_COL	0x184
#घोषणा ADF_RING_CSR_INT_COL_CTL_ENABLE	0x80000000
#घोषणा ADF_RING_CSR_INT_COL_EN		0x17C
#घोषणा ADF_RING_CSR_ADDR_OFFSET	0x100000
#घोषणा ADF_RING_BUNDLE_SIZE		0x2000

#घोषणा BUILD_RING_BASE_ADDR(addr, size) \
	((((addr) >> 6) & (GENMASK_ULL(63, 0) << (size))) << 6)
#घोषणा READ_CSR_RING_HEAD(csr_base_addr, bank, ring) \
	ADF_CSR_RD((csr_base_addr) + ADF_RING_CSR_ADDR_OFFSET, \
		   ADF_RING_BUNDLE_SIZE * (bank) + \
		   ADF_RING_CSR_RING_HEAD + ((ring) << 2))
#घोषणा READ_CSR_RING_TAIL(csr_base_addr, bank, ring) \
	ADF_CSR_RD((csr_base_addr) + ADF_RING_CSR_ADDR_OFFSET, \
		   ADF_RING_BUNDLE_SIZE * (bank) + \
		   ADF_RING_CSR_RING_TAIL + ((ring) << 2))
#घोषणा READ_CSR_E_STAT(csr_base_addr, bank) \
	ADF_CSR_RD((csr_base_addr) + ADF_RING_CSR_ADDR_OFFSET, \
		   ADF_RING_BUNDLE_SIZE * (bank) + ADF_RING_CSR_E_STAT)
#घोषणा WRITE_CSR_RING_CONFIG(csr_base_addr, bank, ring, value) \
	ADF_CSR_WR((csr_base_addr) + ADF_RING_CSR_ADDR_OFFSET, \
		   ADF_RING_BUNDLE_SIZE * (bank) + \
		   ADF_RING_CSR_RING_CONFIG + ((ring) << 2), value)
#घोषणा WRITE_CSR_RING_BASE(csr_base_addr, bank, ring, value)	\
करो अणु \
	व्योम __iomem *_csr_base_addr = csr_base_addr; \
	u32 _bank = bank;						\
	u32 _ring = ring;						\
	dma_addr_t _value = value;					\
	u32 l_base = 0, u_base = 0;					\
	l_base = lower_32_bits(_value);					\
	u_base = upper_32_bits(_value);					\
	ADF_CSR_WR((_csr_base_addr) + ADF_RING_CSR_ADDR_OFFSET,		\
		   ADF_RING_BUNDLE_SIZE * (_bank) +			\
		   ADF_RING_CSR_RING_LBASE + ((_ring) << 2), l_base);	\
	ADF_CSR_WR((_csr_base_addr) + ADF_RING_CSR_ADDR_OFFSET,		\
		   ADF_RING_BUNDLE_SIZE * (_bank) +			\
		   ADF_RING_CSR_RING_UBASE + ((_ring) << 2), u_base);	\
पूर्ण जबतक (0)

#घोषणा WRITE_CSR_RING_HEAD(csr_base_addr, bank, ring, value) \
	ADF_CSR_WR((csr_base_addr) + ADF_RING_CSR_ADDR_OFFSET, \
		   ADF_RING_BUNDLE_SIZE * (bank) + \
		   ADF_RING_CSR_RING_HEAD + ((ring) << 2), value)
#घोषणा WRITE_CSR_RING_TAIL(csr_base_addr, bank, ring, value) \
	ADF_CSR_WR((csr_base_addr) + ADF_RING_CSR_ADDR_OFFSET, \
		   ADF_RING_BUNDLE_SIZE * (bank) + \
		   ADF_RING_CSR_RING_TAIL + ((ring) << 2), value)
#घोषणा WRITE_CSR_INT_FLAG(csr_base_addr, bank, value) \
	ADF_CSR_WR((csr_base_addr) + ADF_RING_CSR_ADDR_OFFSET, \
		   ADF_RING_BUNDLE_SIZE * (bank) + \
		   ADF_RING_CSR_INT_FLAG, (value))
#घोषणा WRITE_CSR_INT_SRCSEL(csr_base_addr, bank) \
	ADF_CSR_WR((csr_base_addr) + ADF_RING_CSR_ADDR_OFFSET, \
		   ADF_RING_BUNDLE_SIZE * (bank) + \
		   ADF_RING_CSR_INT_SRCSEL, ADF_BANK_INT_SRC_SEL_MASK)
#घोषणा WRITE_CSR_INT_COL_EN(csr_base_addr, bank, value) \
	ADF_CSR_WR((csr_base_addr) + ADF_RING_CSR_ADDR_OFFSET, \
		   ADF_RING_BUNDLE_SIZE * (bank) + \
		   ADF_RING_CSR_INT_COL_EN, (value))
#घोषणा WRITE_CSR_INT_COL_CTL(csr_base_addr, bank, value) \
	ADF_CSR_WR((csr_base_addr) + ADF_RING_CSR_ADDR_OFFSET, \
		   ADF_RING_BUNDLE_SIZE * (bank) + \
		   ADF_RING_CSR_INT_COL_CTL, \
		   ADF_RING_CSR_INT_COL_CTL_ENABLE | (value))
#घोषणा WRITE_CSR_INT_FLAG_AND_COL(csr_base_addr, bank, value) \
	ADF_CSR_WR((csr_base_addr) + ADF_RING_CSR_ADDR_OFFSET, \
		   ADF_RING_BUNDLE_SIZE * (bank) + \
		   ADF_RING_CSR_INT_FLAG_AND_COL, (value))

/* Arbiter configuration */
#घोषणा ADF_RING_CSR_RING_SRV_ARB_EN 0x19C

#घोषणा WRITE_CSR_RING_SRV_ARB_EN(csr_base_addr, bank, value) \
	ADF_CSR_WR((csr_base_addr) + ADF_RING_CSR_ADDR_OFFSET, \
		   ADF_RING_BUNDLE_SIZE * (bank) + \
		   ADF_RING_CSR_RING_SRV_ARB_EN, (value))

/* WDT समयrs
 *
 * Timeout is in cycles. Clock speed may vary across products but this
 * value should be a few milli-seconds.
 */
#घोषणा ADF_SSM_WDT_DEFAULT_VALUE	0x200000
#घोषणा ADF_SSM_WDT_PKE_DEFAULT_VALUE	0x8000000
#घोषणा ADF_SSMWDTL_OFFSET		0x54
#घोषणा ADF_SSMWDTH_OFFSET		0x5C
#घोषणा ADF_SSMWDTPKEL_OFFSET		0x58
#घोषणा ADF_SSMWDTPKEH_OFFSET		0x60

व्योम adf_gen4_set_ssm_wdसमयr(काष्ठा adf_accel_dev *accel_dev);
व्योम adf_gen4_init_hw_csr_ops(काष्ठा adf_hw_csr_ops *csr_ops);
#पूर्ण_अगर
