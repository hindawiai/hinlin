<शैली गुरु>
/*
 * Copyright 2003-2011 NetLogic Microप्रणालीs, Inc. (NetLogic). All rights
 * reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the NetLogic
 * license below:
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary क्रमm must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the करोcumentation and/or other materials provided with the
 *    distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY NETLOGIC ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL NETLOGIC OR CONTRIBUTORS BE LIABLE
 * FOR ANY सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
 * IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#अगर_अघोषित _NLM_HAL_XLP_H
#घोषणा _NLM_HAL_XLP_H

#घोषणा PIC_UART_0_IRQ			17
#घोषणा PIC_UART_1_IRQ			18

#घोषणा PIC_PCIE_LINK_LEGACY_IRQ_BASE	19
#घोषणा PIC_PCIE_LINK_LEGACY_IRQ(i)	(19 + (i))

#घोषणा PIC_EHCI_0_IRQ			23
#घोषणा PIC_EHCI_1_IRQ			24
#घोषणा PIC_OHCI_0_IRQ			25
#घोषणा PIC_OHCI_1_IRQ			26
#घोषणा PIC_OHCI_2_IRQ			27
#घोषणा PIC_OHCI_3_IRQ			28
#घोषणा PIC_2XX_XHCI_0_IRQ		23
#घोषणा PIC_2XX_XHCI_1_IRQ		24
#घोषणा PIC_2XX_XHCI_2_IRQ		25
#घोषणा PIC_9XX_XHCI_0_IRQ		23
#घोषणा PIC_9XX_XHCI_1_IRQ		24
#घोषणा PIC_9XX_XHCI_2_IRQ		25

#घोषणा PIC_MMC_IRQ			29
#घोषणा PIC_I2C_0_IRQ			30
#घोषणा PIC_I2C_1_IRQ			31
#घोषणा PIC_I2C_2_IRQ			32
#घोषणा PIC_I2C_3_IRQ			33
#घोषणा PIC_SPI_IRQ			34
#घोषणा PIC_न_अंकD_IRQ			37
#घोषणा PIC_SATA_IRQ			38
#घोषणा PIC_GPIO_IRQ			39

#घोषणा PIC_PCIE_LINK_MSI_IRQ_BASE	44	/* 44 - 47 MSI IRQ */
#घोषणा PIC_PCIE_LINK_MSI_IRQ(i)	(44 + (i))

/* MSI-X with second link-level dispatch */
#घोषणा PIC_PCIE_MSIX_IRQ_BASE		48	/* 48 - 51 MSI-X IRQ */
#घोषणा PIC_PCIE_MSIX_IRQ(i)		(48 + (i))

/* XLP9xx and XLP8xx has 128 and 32 MSIX vectors respectively */
#घोषणा NLM_MSIX_VEC_BASE		96	/* 96 - 223 - MSIX mapped */
#घोषणा NLM_MSI_VEC_BASE		224	/* 224 -351 - MSI mapped */

#घोषणा NLM_PIC_INसूचीECT_VEC_BASE	512
#घोषणा NLM_GPIO_VEC_BASE		768

#घोषणा PIC_IRQ_BASE			8
#घोषणा PIC_IRT_FIRST_IRQ		PIC_IRQ_BASE
#घोषणा PIC_IRT_LAST_IRQ		63

#अगर_अघोषित __ASSEMBLY__

/* SMP support functions */
व्योम xlp_boot_core0_siblings(व्योम);
व्योम xlp_wakeup_secondary_cpus(व्योम);

व्योम xlp_mmu_init(व्योम);
व्योम nlm_hal_init(व्योम);
पूर्णांक nlm_get_dram_map(पूर्णांक node, uपूर्णांक64_t *dram_map, पूर्णांक nentries);

काष्ठा pci_dev;
पूर्णांक xlp_socdev_to_node(स्थिर काष्ठा pci_dev *dev);

/* Device tree related */
व्योम xlp_early_init_devtree(व्योम);
व्योम *xlp_dt_init(व्योम *fdtp);

अटल अंतरभूत पूर्णांक cpu_is_xlpii(व्योम)
अणु
	पूर्णांक chip = पढ़ो_c0_prid() & PRID_IMP_MASK;

	वापस chip == PRID_IMP_NETLOGIC_XLP2XX ||
		chip == PRID_IMP_NETLOGIC_XLP9XX ||
		chip == PRID_IMP_NETLOGIC_XLP5XX;
पूर्ण

अटल अंतरभूत पूर्णांक cpu_is_xlp9xx(व्योम)
अणु
	पूर्णांक chip = पढ़ो_c0_prid() & PRID_IMP_MASK;

	वापस chip == PRID_IMP_NETLOGIC_XLP9XX ||
		chip == PRID_IMP_NETLOGIC_XLP5XX;
पूर्ण
#पूर्ण_अगर /* !__ASSEMBLY__ */
#पूर्ण_अगर /* _ASM_NLM_XLP_H */
