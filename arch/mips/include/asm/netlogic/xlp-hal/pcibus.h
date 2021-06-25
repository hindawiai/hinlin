<शैली गुरु>
/*
 * Copyright (c) 2003-2012 Broadcom Corporation
 * All Rights Reserved
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the Broadcom
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
 * THIS SOFTWARE IS PROVIDED BY BROADCOM ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL BROADCOM OR CONTRIBUTORS BE LIABLE
 * FOR ANY सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
 * IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#अगर_अघोषित __NLM_HAL_PCIBUS_H__
#घोषणा __NLM_HAL_PCIBUS_H__

/* PCIE Memory and IO regions */
#घोषणा PCIE_MEM_BASE			0xd0000000ULL
#घोषणा PCIE_MEM_LIMIT			0xdfffffffULL
#घोषणा PCIE_IO_BASE			0x14000000ULL
#घोषणा PCIE_IO_LIMIT			0x15ffffffULL

#घोषणा PCIE_BRIDGE_CMD			0x1
#घोषणा PCIE_BRIDGE_MSI_CAP		0x14
#घोषणा PCIE_BRIDGE_MSI_ADDRL		0x15
#घोषणा PCIE_BRIDGE_MSI_ADDRH		0x16
#घोषणा PCIE_BRIDGE_MSI_DATA		0x17

/* XLP Global PCIE configuration space रेजिस्टरs */
#घोषणा PCIE_BYTE_SWAP_MEM_BASE		0x247
#घोषणा PCIE_BYTE_SWAP_MEM_LIM		0x248
#घोषणा PCIE_BYTE_SWAP_IO_BASE		0x249
#घोषणा PCIE_BYTE_SWAP_IO_LIM		0x24A

#घोषणा PCIE_BRIDGE_MSIX_ADDR_BASE	0x24F
#घोषणा PCIE_BRIDGE_MSIX_ADDR_LIMIT	0x250
#घोषणा PCIE_MSI_STATUS			0x25A
#घोषणा PCIE_MSI_EN			0x25B
#घोषणा PCIE_MSIX_STATUS		0x25D
#घोषणा PCIE_INT_STATUS0		0x25F
#घोषणा PCIE_INT_STATUS1		0x260
#घोषणा PCIE_INT_EN0			0x261
#घोषणा PCIE_INT_EN1			0x262

/* XLP9XX has basic changes */
#घोषणा PCIE_9XX_BYTE_SWAP_MEM_BASE	0x25c
#घोषणा PCIE_9XX_BYTE_SWAP_MEM_LIM	0x25d
#घोषणा PCIE_9XX_BYTE_SWAP_IO_BASE	0x25e
#घोषणा PCIE_9XX_BYTE_SWAP_IO_LIM	0x25f

#घोषणा PCIE_9XX_BRIDGE_MSIX_ADDR_BASE	0x264
#घोषणा PCIE_9XX_BRIDGE_MSIX_ADDR_LIMIT	0x265
#घोषणा PCIE_9XX_MSI_STATUS		0x283
#घोषणा PCIE_9XX_MSI_EN			0x284
/* 128 MSIX vectors available in 9xx */
#घोषणा PCIE_9XX_MSIX_STATUS0		0x286
#घोषणा PCIE_9XX_MSIX_STATUSX(n)	(n + 0x286)
#घोषणा PCIE_9XX_MSIX_VEC		0x296
#घोषणा PCIE_9XX_MSIX_VECX(n)		(n + 0x296)
#घोषणा PCIE_9XX_INT_STATUS0		0x397
#घोषणा PCIE_9XX_INT_STATUS1		0x398
#घोषणा PCIE_9XX_INT_EN0		0x399
#घोषणा PCIE_9XX_INT_EN1		0x39a

/* other */
#घोषणा PCIE_NLINKS			4

/* MSI addresses */
#घोषणा MSI_ADDR_BASE			0xfffee00000ULL
#घोषणा MSI_ADDR_SZ			0x10000
#घोषणा MSI_LINK_ADDR(n, l)		(MSI_ADDR_BASE + \
				(PCIE_NLINKS * (n) + (l)) * MSI_ADDR_SZ)
#घोषणा MSIX_ADDR_BASE			0xfffef00000ULL
#घोषणा MSIX_LINK_ADDR(n, l)		(MSIX_ADDR_BASE + \
				(PCIE_NLINKS * (n) + (l)) * MSI_ADDR_SZ)
#अगर_अघोषित __ASSEMBLY__

#घोषणा nlm_पढ़ो_pcie_reg(b, r)		nlm_पढ़ो_reg(b, r)
#घोषणा nlm_ग_लिखो_pcie_reg(b, r, v)	nlm_ग_लिखो_reg(b, r, v)
#घोषणा nlm_get_pcie_base(node, inst)	nlm_pcicfg_base(cpu_is_xlp9xx() ? \
	XLP9XX_IO_PCIE_OFFSET(node, inst) : XLP_IO_PCIE_OFFSET(node, inst))

#अगर_घोषित CONFIG_PCI_MSI
व्योम xlp_init_node_msi_irqs(पूर्णांक node, पूर्णांक link);
#अन्यथा
अटल अंतरभूत व्योम xlp_init_node_msi_irqs(पूर्णांक node, पूर्णांक link) अणुपूर्ण
#पूर्ण_अगर

काष्ठा pci_dev *xlp_get_pcie_link(स्थिर काष्ठा pci_dev *dev);

#पूर्ण_अगर
#पूर्ण_अगर /* __NLM_HAL_PCIBUS_H__ */
