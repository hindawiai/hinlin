<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित LINUX_BCMA_REGS_H_
#घोषणा LINUX_BCMA_REGS_H_

/* Some single रेजिस्टरs are shared between many cores */
/* BCMA_CLKCTLST: ChipCommon (rev >= 20), PCIe, 80211 */
#घोषणा BCMA_CLKCTLST			0x01E0 /* Clock control and status */
#घोषणा  BCMA_CLKCTLST_FORCEALP		0x00000001 /* Force ALP request */
#घोषणा  BCMA_CLKCTLST_FORCEHT		0x00000002 /* Force HT request */
#घोषणा  BCMA_CLKCTLST_FORCEILP		0x00000004 /* Force ILP request */
#घोषणा  BCMA_CLKCTLST_HAVEALPREQ	0x00000008 /* ALP available request */
#घोषणा  BCMA_CLKCTLST_HAVEHTREQ	0x00000010 /* HT available request */
#घोषणा  BCMA_CLKCTLST_HWCROFF		0x00000020 /* Force HW घड़ी request off */
#घोषणा  BCMA_CLKCTLST_HQCLKREQ		0x00000040 /* HQ Clock */
#घोषणा  BCMA_CLKCTLST_EXTRESREQ	0x00000700 /* Mask of बाह्यal resource requests */
#घोषणा  BCMA_CLKCTLST_EXTRESREQ_SHIFT	8
#घोषणा  BCMA_CLKCTLST_HAVEALP		0x00010000 /* ALP available */
#घोषणा  BCMA_CLKCTLST_HAVEHT		0x00020000 /* HT available */
#घोषणा  BCMA_CLKCTLST_BP_ON_ALP	0x00040000 /* RO: running on ALP घड़ी */
#घोषणा  BCMA_CLKCTLST_BP_ON_HT		0x00080000 /* RO: running on HT घड़ी */
#घोषणा  BCMA_CLKCTLST_EXTRESST		0x07000000 /* Mask of बाह्यal resource status */
#घोषणा  BCMA_CLKCTLST_EXTRESST_SHIFT	24
/* Is there any BCM4328 on BCMA bus? */
#घोषणा  BCMA_CLKCTLST_4328A0_HAVEHT	0x00010000 /* 4328a0 has reversed bits */
#घोषणा  BCMA_CLKCTLST_4328A0_HAVEALP	0x00020000 /* 4328a0 has reversed bits */

/* Agent रेजिस्टरs (common क्रम every core) */
#घोषणा BCMA_OOB_SEL_OUT_A30		0x0100
#घोषणा BCMA_IOCTL			0x0408 /* IO control */
#घोषणा  BCMA_IOCTL_CLK			0x0001
#घोषणा  BCMA_IOCTL_FGC			0x0002
#घोषणा  BCMA_IOCTL_CORE_BITS		0x3FFC
#घोषणा  BCMA_IOCTL_PME_EN		0x4000
#घोषणा  BCMA_IOCTL_BIST_EN		0x8000
#घोषणा BCMA_IOST			0x0500 /* IO status */
#घोषणा  BCMA_IOST_CORE_BITS		0x0FFF
#घोषणा  BCMA_IOST_DMA64		0x1000
#घोषणा  BCMA_IOST_GATED_CLK		0x2000
#घोषणा  BCMA_IOST_BIST_ERROR		0x4000
#घोषणा  BCMA_IOST_BIST_DONE		0x8000
#घोषणा BCMA_RESET_CTL			0x0800
#घोषणा  BCMA_RESET_CTL_RESET		0x0001
#घोषणा BCMA_RESET_ST			0x0804

#घोषणा BCMA_NS_ROM_IOST_BOOT_DEV_MASK	0x0003
#घोषणा BCMA_NS_ROM_IOST_BOOT_DEV_NOR	0x0000
#घोषणा BCMA_NS_ROM_IOST_BOOT_DEV_न_अंकD	0x0001
#घोषणा BCMA_NS_ROM_IOST_BOOT_DEV_ROM	0x0002

/* BCMA PCI config space रेजिस्टरs. */
#घोषणा BCMA_PCI_PMCSR			0x44
#घोषणा  BCMA_PCI_PE			0x100
#घोषणा BCMA_PCI_BAR0_WIN		0x80	/* Backplane address space 0 */
#घोषणा BCMA_PCI_BAR1_WIN		0x84	/* Backplane address space 1 */
#घोषणा BCMA_PCI_SPROMCTL		0x88	/* SPROM control */
#घोषणा  BCMA_PCI_SPROMCTL_WE		0x10	/* SPROM ग_लिखो enable */
#घोषणा BCMA_PCI_BAR1_CONTROL		0x8c	/* Address space 1 burst control */
#घोषणा BCMA_PCI_IRQS			0x90	/* PCI पूर्णांकerrupts */
#घोषणा BCMA_PCI_IRQMASK		0x94	/* PCI IRQ control and mask (pcirev >= 6 only) */
#घोषणा BCMA_PCI_BACKPLANE_IRQS		0x98	/* Backplane Interrupts */
#घोषणा BCMA_PCI_BAR0_WIN2		0xAC
#घोषणा BCMA_PCI_GPIO_IN		0xB0	/* GPIO Input (pcirev >= 3 only) */
#घोषणा BCMA_PCI_GPIO_OUT		0xB4	/* GPIO Output (pcirev >= 3 only) */
#घोषणा BCMA_PCI_GPIO_OUT_ENABLE	0xB8	/* GPIO Output Enable/Disable (pcirev >= 3 only) */
#घोषणा  BCMA_PCI_GPIO_SCS		0x10	/* PCI config space bit 4 क्रम 4306c0 slow घड़ी source */
#घोषणा  BCMA_PCI_GPIO_HWRAD		0x20	/* PCI config space GPIO 13 क्रम hw radio disable */
#घोषणा  BCMA_PCI_GPIO_XTAL		0x40	/* PCI config space GPIO 14 क्रम Xtal घातerup */
#घोषणा  BCMA_PCI_GPIO_PLL		0x80	/* PCI config space GPIO 15 क्रम PLL घातerकरोwn */

#घोषणा BCMA_PCIE2_BAR0_WIN2		0x70

/* SiliconBackplane Address Map.
 * All regions may not exist on all chips.
 */
#घोषणा BCMA_SOC_SDRAM_BASE		0x00000000U	/* Physical SDRAM */
#घोषणा BCMA_SOC_PCI_MEM		0x08000000U	/* Host Mode sb2pcitranslation0 (64 MB) */
#घोषणा BCMA_SOC_PCI_MEM_SZ		(64 * 1024 * 1024)
#घोषणा BCMA_SOC_PCI_CFG		0x0c000000U	/* Host Mode sb2pcitranslation1 (64 MB) */
#घोषणा BCMA_SOC_SDRAM_SWAPPED		0x10000000U	/* Byteswapped Physical SDRAM */
#घोषणा BCMA_SOC_SDRAM_R2		0x80000000U	/* Region 2 क्रम sdram (512 MB) */


#घोषणा BCMA_SOC_PCI_DMA		0x40000000U	/* Client Mode sb2pcitranslation2 (1 GB) */
#घोषणा BCMA_SOC_PCI_DMA2		0x80000000U	/* Client Mode sb2pcitranslation2 (1 GB) */
#घोषणा BCMA_SOC_PCI_DMA_SZ		0x40000000U	/* Client Mode sb2pcitranslation2 size in bytes */
#घोषणा BCMA_SOC_PCIE_DMA_L32		0x00000000U	/* PCIE Client Mode sb2pcitranslation2
							 * (2 ZettaBytes), low 32 bits
							 */
#घोषणा BCMA_SOC_PCIE_DMA_H32		0x80000000U	/* PCIE Client Mode sb2pcitranslation2
							 * (2 ZettaBytes), high 32 bits
							 */

#घोषणा BCMA_SOC_PCI1_MEM		0x40000000U	/* Host Mode sb2pcitranslation0 (64 MB) */
#घोषणा BCMA_SOC_PCI1_CFG		0x44000000U	/* Host Mode sb2pcitranslation1 (64 MB) */
#घोषणा BCMA_SOC_PCIE1_DMA_H32		0xc0000000U	/* PCIE Client Mode sb2pcitranslation2
							 * (2 ZettaBytes), high 32 bits
							 */

#घोषणा BCMA_SOC_FLASH1			0x1fc00000	/* MIPS Flash Region 1 */
#घोषणा BCMA_SOC_FLASH1_SZ		0x00400000	/* MIPS Size of Flash Region 1 */
#घोषणा BCMA_SOC_FLASH2			0x1c000000	/* Flash Region 2 (region 1 shaकरोwed here) */
#घोषणा BCMA_SOC_FLASH2_SZ		0x02000000	/* Size of Flash Region 2 */

#पूर्ण_अगर /* LINUX_BCMA_REGS_H_ */
