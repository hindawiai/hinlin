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

#अगर_अघोषित __NLM_HAL_IOMAP_H__
#घोषणा __NLM_HAL_IOMAP_H__

#घोषणा XLP_DEFAULT_IO_BASE		0x18000000
#घोषणा XLP_DEFAULT_PCI_ECFG_BASE	XLP_DEFAULT_IO_BASE
#घोषणा XLP_DEFAULT_PCI_CFG_BASE	0x1c000000

#घोषणा NMI_BASE			0xbfc00000
#घोषणा XLP_IO_CLK			133333333

#घोषणा XLP_PCIE_CFG_SIZE		0x1000		/* 4K */
#घोषणा XLP_PCIE_DEV_BLK_SIZE		(8 * XLP_PCIE_CFG_SIZE)
#घोषणा XLP_PCIE_BUS_BLK_SIZE		(256 * XLP_PCIE_DEV_BLK_SIZE)
#घोषणा XLP_IO_SIZE			(64 << 20)	/* ECFG space size */
#घोषणा XLP_IO_PCI_HDRSZ		0x100
#घोषणा XLP_IO_DEV(node, dev)		((dev) + (node) * 8)
#घोषणा XLP_IO_PCI_OFFSET(b, d, f)	(((b) << 20) | ((d) << 15) | ((f) << 12))

#घोषणा XLP_HDR_OFFSET(node, bus, dev, fn) \
		XLP_IO_PCI_OFFSET(bus, XLP_IO_DEV(node, dev), fn)

#घोषणा XLP_IO_BRIDGE_OFFSET(node)	XLP_HDR_OFFSET(node, 0, 0, 0)
/* coherent पूर्णांकer chip */
#घोषणा XLP_IO_CIC0_OFFSET(node)	XLP_HDR_OFFSET(node, 0, 0, 1)
#घोषणा XLP_IO_CIC1_OFFSET(node)	XLP_HDR_OFFSET(node, 0, 0, 2)
#घोषणा XLP_IO_CIC2_OFFSET(node)	XLP_HDR_OFFSET(node, 0, 0, 3)
#घोषणा XLP_IO_PIC_OFFSET(node)		XLP_HDR_OFFSET(node, 0, 0, 4)

#घोषणा XLP_IO_PCIE_OFFSET(node, i)	XLP_HDR_OFFSET(node, 0, 1, i)
#घोषणा XLP_IO_PCIE0_OFFSET(node)	XLP_HDR_OFFSET(node, 0, 1, 0)
#घोषणा XLP_IO_PCIE1_OFFSET(node)	XLP_HDR_OFFSET(node, 0, 1, 1)
#घोषणा XLP_IO_PCIE2_OFFSET(node)	XLP_HDR_OFFSET(node, 0, 1, 2)
#घोषणा XLP_IO_PCIE3_OFFSET(node)	XLP_HDR_OFFSET(node, 0, 1, 3)

#घोषणा XLP_IO_USB_OFFSET(node, i)	XLP_HDR_OFFSET(node, 0, 2, i)
#घोषणा XLP_IO_USB_EHCI0_OFFSET(node)	XLP_HDR_OFFSET(node, 0, 2, 0)
#घोषणा XLP_IO_USB_OHCI0_OFFSET(node)	XLP_HDR_OFFSET(node, 0, 2, 1)
#घोषणा XLP_IO_USB_OHCI1_OFFSET(node)	XLP_HDR_OFFSET(node, 0, 2, 2)
#घोषणा XLP_IO_USB_EHCI1_OFFSET(node)	XLP_HDR_OFFSET(node, 0, 2, 3)
#घोषणा XLP_IO_USB_OHCI2_OFFSET(node)	XLP_HDR_OFFSET(node, 0, 2, 4)
#घोषणा XLP_IO_USB_OHCI3_OFFSET(node)	XLP_HDR_OFFSET(node, 0, 2, 5)

#घोषणा XLP_IO_SATA_OFFSET(node)	XLP_HDR_OFFSET(node, 0, 3, 2)

/* XLP2xx has an updated USB block */
#घोषणा XLP2XX_IO_USB_OFFSET(node, i)	XLP_HDR_OFFSET(node, 0, 4, i)
#घोषणा XLP2XX_IO_USB_XHCI0_OFFSET(node)	XLP_HDR_OFFSET(node, 0, 4, 1)
#घोषणा XLP2XX_IO_USB_XHCI1_OFFSET(node)	XLP_HDR_OFFSET(node, 0, 4, 2)
#घोषणा XLP2XX_IO_USB_XHCI2_OFFSET(node)	XLP_HDR_OFFSET(node, 0, 4, 3)

#घोषणा XLP_IO_NAE_OFFSET(node)		XLP_HDR_OFFSET(node, 0, 3, 0)
#घोषणा XLP_IO_POE_OFFSET(node)		XLP_HDR_OFFSET(node, 0, 3, 1)

#घोषणा XLP_IO_CMS_OFFSET(node)		XLP_HDR_OFFSET(node, 0, 4, 0)

#घोषणा XLP_IO_DMA_OFFSET(node)		XLP_HDR_OFFSET(node, 0, 5, 1)
#घोषणा XLP_IO_SEC_OFFSET(node)		XLP_HDR_OFFSET(node, 0, 5, 2)
#घोषणा XLP_IO_CMP_OFFSET(node)		XLP_HDR_OFFSET(node, 0, 5, 3)

#घोषणा XLP_IO_UART_OFFSET(node, i)	XLP_HDR_OFFSET(node, 0, 6, i)
#घोषणा XLP_IO_UART0_OFFSET(node)	XLP_HDR_OFFSET(node, 0, 6, 0)
#घोषणा XLP_IO_UART1_OFFSET(node)	XLP_HDR_OFFSET(node, 0, 6, 1)
#घोषणा XLP_IO_I2C_OFFSET(node, i)	XLP_HDR_OFFSET(node, 0, 6, 2 + i)
#घोषणा XLP_IO_I2C0_OFFSET(node)	XLP_HDR_OFFSET(node, 0, 6, 2)
#घोषणा XLP_IO_I2C1_OFFSET(node)	XLP_HDR_OFFSET(node, 0, 6, 3)
#घोषणा XLP_IO_GPIO_OFFSET(node)	XLP_HDR_OFFSET(node, 0, 6, 4)
/* on 2XX, all I2C busses are on the same block */
#घोषणा XLP2XX_IO_I2C_OFFSET(node)	XLP_HDR_OFFSET(node, 0, 6, 7)

/* प्रणाली management */
#घोषणा XLP_IO_SYS_OFFSET(node)		XLP_HDR_OFFSET(node, 0, 6, 5)
#घोषणा XLP_IO_JTAG_OFFSET(node)	XLP_HDR_OFFSET(node, 0, 6, 6)

/* Flash */
#घोषणा XLP_IO_NOR_OFFSET(node)		XLP_HDR_OFFSET(node, 0, 7, 0)
#घोषणा XLP_IO_न_अंकD_OFFSET(node)	XLP_HDR_OFFSET(node, 0, 7, 1)
#घोषणा XLP_IO_SPI_OFFSET(node)		XLP_HDR_OFFSET(node, 0, 7, 2)
#घोषणा XLP_IO_MMC_OFFSET(node)		XLP_HDR_OFFSET(node, 0, 7, 3)

/* Things have changed drastically in XLP 9XX */
#घोषणा XLP9XX_HDR_OFFSET(n, d, f)	\
			XLP_IO_PCI_OFFSET(xlp9xx_get_socbus(n), d, f)

#घोषणा XLP9XX_IO_BRIDGE_OFFSET(node)	XLP_IO_PCI_OFFSET(0, 0, node)
#घोषणा XLP9XX_IO_PIC_OFFSET(node)	XLP9XX_HDR_OFFSET(node, 2, 0)
#घोषणा XLP9XX_IO_UART_OFFSET(node)	XLP9XX_HDR_OFFSET(node, 2, 2)
#घोषणा XLP9XX_IO_SYS_OFFSET(node)	XLP9XX_HDR_OFFSET(node, 6, 0)
#घोषणा XLP9XX_IO_FUSE_OFFSET(node)	XLP9XX_HDR_OFFSET(node, 6, 1)
#घोषणा XLP9XX_IO_CLOCK_OFFSET(node)	XLP9XX_HDR_OFFSET(node, 6, 2)
#घोषणा XLP9XX_IO_POWER_OFFSET(node)	XLP9XX_HDR_OFFSET(node, 6, 3)
#घोषणा XLP9XX_IO_JTAG_OFFSET(node)	XLP9XX_HDR_OFFSET(node, 6, 4)

#घोषणा XLP9XX_IO_PCIE_OFFSET(node, i)	XLP9XX_HDR_OFFSET(node, 1, i)
#घोषणा XLP9XX_IO_PCIE0_OFFSET(node)	XLP9XX_HDR_OFFSET(node, 1, 0)
#घोषणा XLP9XX_IO_PCIE2_OFFSET(node)	XLP9XX_HDR_OFFSET(node, 1, 2)
#घोषणा XLP9XX_IO_PCIE3_OFFSET(node)	XLP9XX_HDR_OFFSET(node, 1, 3)

/* XLP9xx USB block */
#घोषणा XLP9XX_IO_USB_OFFSET(node, i)		XLP9XX_HDR_OFFSET(node, 4, i)
#घोषणा XLP9XX_IO_USB_XHCI0_OFFSET(node)	XLP9XX_HDR_OFFSET(node, 4, 1)
#घोषणा XLP9XX_IO_USB_XHCI1_OFFSET(node)	XLP9XX_HDR_OFFSET(node, 4, 2)

/* XLP9XX on-chip SATA controller */
#घोषणा XLP9XX_IO_SATA_OFFSET(node)		XLP9XX_HDR_OFFSET(node, 3, 2)

/* Flash */
#घोषणा XLP9XX_IO_NOR_OFFSET(node)		XLP9XX_HDR_OFFSET(node, 7, 0)
#घोषणा XLP9XX_IO_न_अंकD_OFFSET(node)		XLP9XX_HDR_OFFSET(node, 7, 1)
#घोषणा XLP9XX_IO_SPI_OFFSET(node)		XLP9XX_HDR_OFFSET(node, 7, 2)
#घोषणा XLP9XX_IO_MMC_OFFSET(node)		XLP9XX_HDR_OFFSET(node, 7, 3)

/* PCI config header रेजिस्टर id's */
#घोषणा XLP_PCI_CFGREG0			0x00
#घोषणा XLP_PCI_CFGREG1			0x01
#घोषणा XLP_PCI_CFGREG2			0x02
#घोषणा XLP_PCI_CFGREG3			0x03
#घोषणा XLP_PCI_CFGREG4			0x04
#घोषणा XLP_PCI_CFGREG5			0x05
#घोषणा XLP_PCI_DEVINFO_REG0		0x30
#घोषणा XLP_PCI_DEVINFO_REG1		0x31
#घोषणा XLP_PCI_DEVINFO_REG2		0x32
#घोषणा XLP_PCI_DEVINFO_REG3		0x33
#घोषणा XLP_PCI_DEVINFO_REG4		0x34
#घोषणा XLP_PCI_DEVINFO_REG5		0x35
#घोषणा XLP_PCI_DEVINFO_REG6		0x36
#घोषणा XLP_PCI_DEVINFO_REG7		0x37
#घोषणा XLP_PCI_DEVSCRATCH_REG0		0x38
#घोषणा XLP_PCI_DEVSCRATCH_REG1		0x39
#घोषणा XLP_PCI_DEVSCRATCH_REG2		0x3a
#घोषणा XLP_PCI_DEVSCRATCH_REG3		0x3b
#घोषणा XLP_PCI_MSGSTN_REG		0x3c
#घोषणा XLP_PCI_IRTINFO_REG		0x3d
#घोषणा XLP_PCI_UCODEINFO_REG		0x3e
#घोषणा XLP_PCI_SBB_WT_REG		0x3f

/* PCI IDs क्रम SoC device */
#घोषणा PCI_VENDOR_NETLOGIC		0x184e

#घोषणा PCI_DEVICE_ID_NLM_ROOT		0x1001
#घोषणा PCI_DEVICE_ID_NLM_ICI		0x1002
#घोषणा PCI_DEVICE_ID_NLM_PIC		0x1003
#घोषणा PCI_DEVICE_ID_NLM_PCIE		0x1004
#घोषणा PCI_DEVICE_ID_NLM_EHCI		0x1007
#घोषणा PCI_DEVICE_ID_NLM_OHCI		0x1008
#घोषणा PCI_DEVICE_ID_NLM_NAE		0x1009
#घोषणा PCI_DEVICE_ID_NLM_POE		0x100A
#घोषणा PCI_DEVICE_ID_NLM_FMN		0x100B
#घोषणा PCI_DEVICE_ID_NLM_RAID		0x100D
#घोषणा PCI_DEVICE_ID_NLM_SAE		0x100D
#घोषणा PCI_DEVICE_ID_NLM_RSA		0x100E
#घोषणा PCI_DEVICE_ID_NLM_CMP		0x100F
#घोषणा PCI_DEVICE_ID_NLM_UART		0x1010
#घोषणा PCI_DEVICE_ID_NLM_I2C		0x1011
#घोषणा PCI_DEVICE_ID_NLM_NOR		0x1015
#घोषणा PCI_DEVICE_ID_NLM_न_अंकD		0x1016
#घोषणा PCI_DEVICE_ID_NLM_MMC		0x1018
#घोषणा PCI_DEVICE_ID_NLM_SATA		0x101A
#घोषणा PCI_DEVICE_ID_NLM_XHCI		0x101D

#घोषणा PCI_DEVICE_ID_XLP9XX_MMC	0x9018
#घोषणा PCI_DEVICE_ID_XLP9XX_SATA	0x901A
#घोषणा PCI_DEVICE_ID_XLP9XX_XHCI	0x901D

#अगर_अघोषित __ASSEMBLY__

#घोषणा nlm_पढ़ो_pci_reg(b, r)		nlm_पढ़ो_reg(b, r)
#घोषणा nlm_ग_लिखो_pci_reg(b, r, v)	nlm_ग_लिखो_reg(b, r, v)

अटल अंतरभूत पूर्णांक xlp9xx_get_socbus(पूर्णांक node)
अणु
	uपूर्णांक64_t socbridge;

	अगर (node == 0)
		वापस 1;
	socbridge = nlm_pcicfg_base(XLP9XX_IO_BRIDGE_OFFSET(node));
	वापस (nlm_पढ़ो_pci_reg(socbridge, 0x6) >> 8) & 0xff;
पूर्ण
#पूर्ण_अगर /* !__ASSEMBLY */

#पूर्ण_अगर /* __NLM_HAL_IOMAP_H__ */
