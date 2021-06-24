<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Intel Atom SOC Power Management Controller Header File
 * Copyright (c) 2014, Intel Corporation.
 */

#अगर_अघोषित PMC_ATOM_H
#घोषणा PMC_ATOM_H

/* ValleyView Power Control Unit PCI Device ID */
#घोषणा	PCI_DEVICE_ID_VLV_PMC	0x0F1C
/* CherryTrail Power Control Unit PCI Device ID */
#घोषणा	PCI_DEVICE_ID_CHT_PMC	0x229C

/* PMC Memory mapped IO रेजिस्टरs */
#घोषणा	PMC_BASE_ADDR_OFFSET	0x44
#घोषणा	PMC_BASE_ADDR_MASK	0xFFFFFE00
#घोषणा	PMC_MMIO_REG_LEN	0x100
#घोषणा	PMC_REG_BIT_WIDTH	32

/* BIOS uses FUNC_DIS to disable specअगरic function */
#घोषणा	PMC_FUNC_DIS		0x34
#घोषणा	PMC_FUNC_DIS_2		0x38

/* CHT specअगरic bits in FUNC_DIS2 रेजिस्टर */
#घोषणा	BIT_FD_GMM		BIT(3)
#घोषणा	BIT_FD_ISH		BIT(4)

/* S0ix wake event control */
#घोषणा	PMC_S0IX_WAKE_EN	0x3C

#घोषणा	BIT_LPC_CLOCK_RUN		BIT(4)
#घोषणा	BIT_SHARED_IRQ_GPSC		BIT(5)
#घोषणा	BIT_ORED_DEDICATED_IRQ_GPSS	BIT(18)
#घोषणा	BIT_ORED_DEDICATED_IRQ_GPSC	BIT(19)
#घोषणा	BIT_SHARED_IRQ_GPSS		BIT(20)

#घोषणा	PMC_WAKE_EN_SETTING	~(BIT_LPC_CLOCK_RUN | \
				BIT_SHARED_IRQ_GPSC | \
				BIT_ORED_DEDICATED_IRQ_GPSS | \
				BIT_ORED_DEDICATED_IRQ_GPSC | \
				BIT_SHARED_IRQ_GPSS)

/* The समयrs accumulate समय spent in sleep state */
#घोषणा	PMC_S0IR_TMR		0x80
#घोषणा	PMC_S0I1_TMR		0x84
#घोषणा	PMC_S0I2_TMR		0x88
#घोषणा	PMC_S0I3_TMR		0x8C
#घोषणा	PMC_S0_TMR		0x90
/* Sleep state counter is in units of of 32us */
#घोषणा	PMC_TMR_SHIFT		5

/* Power status of घातer islands */
#घोषणा	PMC_PSS			0x98

#घोषणा PMC_PSS_BIT_GBE			BIT(0)
#घोषणा PMC_PSS_BIT_SATA		BIT(1)
#घोषणा PMC_PSS_BIT_HDA			BIT(2)
#घोषणा PMC_PSS_BIT_SEC			BIT(3)
#घोषणा PMC_PSS_BIT_PCIE		BIT(4)
#घोषणा PMC_PSS_BIT_LPSS		BIT(5)
#घोषणा PMC_PSS_BIT_LPE			BIT(6)
#घोषणा PMC_PSS_BIT_DFX			BIT(7)
#घोषणा PMC_PSS_BIT_USH_CTRL		BIT(8)
#घोषणा PMC_PSS_BIT_USH_SUS		BIT(9)
#घोषणा PMC_PSS_BIT_USH_VCCS		BIT(10)
#घोषणा PMC_PSS_BIT_USH_VCCA		BIT(11)
#घोषणा PMC_PSS_BIT_OTG_CTRL		BIT(12)
#घोषणा PMC_PSS_BIT_OTG_VCCS		BIT(13)
#घोषणा PMC_PSS_BIT_OTG_VCCA_CLK	BIT(14)
#घोषणा PMC_PSS_BIT_OTG_VCCA		BIT(15)
#घोषणा PMC_PSS_BIT_USB			BIT(16)
#घोषणा PMC_PSS_BIT_USB_SUS		BIT(17)

/* CHT specअगरic bits in PSS रेजिस्टर */
#घोषणा	PMC_PSS_BIT_CHT_UFS		BIT(7)
#घोषणा	PMC_PSS_BIT_CHT_UXD		BIT(11)
#घोषणा	PMC_PSS_BIT_CHT_UXD_FD		BIT(12)
#घोषणा	PMC_PSS_BIT_CHT_UX_ENG		BIT(15)
#घोषणा	PMC_PSS_BIT_CHT_USB_SUS		BIT(16)
#घोषणा	PMC_PSS_BIT_CHT_GMM		BIT(17)
#घोषणा	PMC_PSS_BIT_CHT_ISH		BIT(18)
#घोषणा	PMC_PSS_BIT_CHT_DFX_MASTER	BIT(26)
#घोषणा	PMC_PSS_BIT_CHT_DFX_CLUSTER1	BIT(27)
#घोषणा	PMC_PSS_BIT_CHT_DFX_CLUSTER2	BIT(28)
#घोषणा	PMC_PSS_BIT_CHT_DFX_CLUSTER3	BIT(29)
#घोषणा	PMC_PSS_BIT_CHT_DFX_CLUSTER4	BIT(30)
#घोषणा	PMC_PSS_BIT_CHT_DFX_CLUSTER5	BIT(31)

/* These रेजिस्टरs reflect D3 status of functions */
#घोषणा	PMC_D3_STS_0		0xA0

#घोषणा	BIT_LPSS1_F0_DMA	BIT(0)
#घोषणा	BIT_LPSS1_F1_PWM1	BIT(1)
#घोषणा	BIT_LPSS1_F2_PWM2	BIT(2)
#घोषणा	BIT_LPSS1_F3_HSUART1	BIT(3)
#घोषणा	BIT_LPSS1_F4_HSUART2	BIT(4)
#घोषणा	BIT_LPSS1_F5_SPI	BIT(5)
#घोषणा	BIT_LPSS1_F6_XXX	BIT(6)
#घोषणा	BIT_LPSS1_F7_XXX	BIT(7)
#घोषणा	BIT_SCC_EMMC		BIT(8)
#घोषणा	BIT_SCC_SDIO		BIT(9)
#घोषणा	BIT_SCC_SDCARD		BIT(10)
#घोषणा	BIT_SCC_MIPI		BIT(11)
#घोषणा	BIT_HDA			BIT(12)
#घोषणा	BIT_LPE			BIT(13)
#घोषणा	BIT_OTG			BIT(14)
#घोषणा	BIT_USH			BIT(15)
#घोषणा	BIT_GBE			BIT(16)
#घोषणा	BIT_SATA		BIT(17)
#घोषणा	BIT_USB_EHCI		BIT(18)
#घोषणा	BIT_SEC			BIT(19)
#घोषणा	BIT_PCIE_PORT0		BIT(20)
#घोषणा	BIT_PCIE_PORT1		BIT(21)
#घोषणा	BIT_PCIE_PORT2		BIT(22)
#घोषणा	BIT_PCIE_PORT3		BIT(23)
#घोषणा	BIT_LPSS2_F0_DMA	BIT(24)
#घोषणा	BIT_LPSS2_F1_I2C1	BIT(25)
#घोषणा	BIT_LPSS2_F2_I2C2	BIT(26)
#घोषणा	BIT_LPSS2_F3_I2C3	BIT(27)
#घोषणा	BIT_LPSS2_F4_I2C4	BIT(28)
#घोषणा	BIT_LPSS2_F5_I2C5	BIT(29)
#घोषणा	BIT_LPSS2_F6_I2C6	BIT(30)
#घोषणा	BIT_LPSS2_F7_I2C7	BIT(31)

#घोषणा	PMC_D3_STS_1		0xA4
#घोषणा	BIT_SMB			BIT(0)
#घोषणा	BIT_OTG_SS_PHY		BIT(1)
#घोषणा	BIT_USH_SS_PHY		BIT(2)
#घोषणा	BIT_DFX			BIT(3)

/* CHT specअगरic bits in PMC_D3_STS_1 रेजिस्टर */
#घोषणा	BIT_STS_GMM		BIT(1)
#घोषणा	BIT_STS_ISH		BIT(2)

/* PMC I/O Registers */
#घोषणा	ACPI_BASE_ADDR_OFFSET	0x40
#घोषणा	ACPI_BASE_ADDR_MASK	0xFFFFFE00
#घोषणा	ACPI_MMIO_REG_LEN	0x100

#घोषणा	PM1_CNT			0x4
#घोषणा	SLEEP_TYPE_MASK		0xFFFFECFF
#घोषणा	SLEEP_TYPE_S5		0x1C00
#घोषणा	SLEEP_ENABLE		0x2000

बाह्य पूर्णांक pmc_atom_पढ़ो(पूर्णांक offset, u32 *value);
बाह्य पूर्णांक pmc_atom_ग_लिखो(पूर्णांक offset, u32 value);

#पूर्ण_अगर /* PMC_ATOM_H */
