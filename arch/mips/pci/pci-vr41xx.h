<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *  pci-vr41xx.h, Include file क्रम PCI Control Unit of the NEC VR4100 series.
 *
 *  Copyright (C) 2002	MontaVista Software Inc.
 *    Author: Yoichi Yuasa <source@mvista.com>
 *  Copyright (C) 2004-2005  Yoichi Yuasa <yuasa@linux-mips.org>
 */
#अगर_अघोषित __PCI_VR41XX_H
#घोषणा __PCI_VR41XX_H

#घोषणा PCIU_BASE		0x0f000c00UL
#घोषणा PCIU_SIZE		0x200UL

#घोषणा PCIMMAW1REG		0x00
#घोषणा PCIMMAW2REG		0x04
#घोषणा PCITAW1REG		0x08
#घोषणा PCITAW2REG		0x0c
#घोषणा PCIMIOAWREG		0x10
 #घोषणा IBA(addr)		((addr) & 0xff000000U)
 #घोषणा MASTER_MSK(mask)	(((mask) >> 11) & 0x000fe000U)
 #घोषणा PCIA(addr)		(((addr) >> 24) & 0x000000ffU)
 #घोषणा TARGET_MSK(mask)	(((mask) >> 8) & 0x000fe000U)
 #घोषणा ITA(addr)		(((addr) >> 24) & 0x000000ffU)
 #घोषणा PCIIA(addr)		(((addr) >> 24) & 0x000000ffU)
 #घोषणा WINEN			0x1000U
#घोषणा PCICONFDREG		0x14
#घोषणा PCICONFAREG		0x18
#घोषणा PCIMAILREG		0x1c
#घोषणा BUSERRADREG		0x24
 #घोषणा EA(reg)		((reg) &0xfffffffc)

#घोषणा INTCNTSTAREG		0x28
 #घोषणा MABTCLR		0x80000000U
 #घोषणा TRDYCLR		0x40000000U
 #घोषणा PARCLR			0x20000000U
 #घोषणा MBCLR			0x10000000U
 #घोषणा SERRCLR		0x08000000U
 #घोषणा RTYCLR			0x04000000U
 #घोषणा MABCLR			0x02000000U
 #घोषणा TABCLR			0x01000000U
 /* RFU */
 #घोषणा MABTMSK		0x00008000U
 #घोषणा TRDYMSK		0x00004000U
 #घोषणा PARMSK			0x00002000U
 #घोषणा MBMSK			0x00001000U
 #घोषणा SERRMSK		0x00000800U
 #घोषणा RTYMSK			0x00000400U
 #घोषणा MABMSK			0x00000200U
 #घोषणा TABMSK			0x00000100U
 #घोषणा IBAMABT		0x00000080U
 #घोषणा TRDYRCH		0x00000040U
 #घोषणा PAR			0x00000020U
 #घोषणा MB			0x00000010U
 #घोषणा PCISERR		0x00000008U
 #घोषणा RTYRCH			0x00000004U
 #घोषणा MABORT			0x00000002U
 #घोषणा TABORT			0x00000001U

#घोषणा PCIEXACCREG		0x2c
 #घोषणा UNLOCK			0x2U
 #घोषणा EAREQ			0x1U
#घोषणा PCIRECONTREG		0x30
 #घोषणा RTRYCNT(reg)		((reg) & 0x000000ffU)
#घोषणा PCIENREG		0x34
 #घोषणा PCIU_CONFIG_DONE	0x4U
#घोषणा PCICLKSELREG		0x38
 #घोषणा EQUAL_VTCLOCK		0x2U
 #घोषणा HALF_VTCLOCK		0x0U
 #घोषणा ONE_THIRD_VTCLOCK	0x3U
 #घोषणा QUARTER_VTCLOCK	0x1U
#घोषणा PCITRDYVREG		0x3c
 #घोषणा TRDYV(val)		((uपूर्णांक32_t)(val) & 0xffU)
#घोषणा PCICLKRUNREG		0x60

#घोषणा VENDORIDREG		0x100
#घोषणा DEVICEIDREG		0x100
#घोषणा COMMANDREG		0x104
#घोषणा STATUSREG		0x104
#घोषणा REVIDREG		0x108
#घोषणा CLASSREG		0x108
#घोषणा CACHELSREG		0x10c
#घोषणा LATTIMEREG		0x10c
 #घोषणा MLTIM(val)		(((uपूर्णांक32_t)(val) << 7) & 0xff00U)
#घोषणा MAILBAREG		0x110
#घोषणा PCIMBA1REG		0x114
#घोषणा PCIMBA2REG		0x118
 #घोषणा MBADD(base)		((base) & 0xfffff800U)
 #घोषणा PMBA(base)		((base) & 0xffe00000U)
 #घोषणा PREF			0x8U
 #घोषणा PREF_APPROVAL		0x8U
 #घोषणा PREF_DISAPPROVAL	0x0U
 #घोषणा TYPE			0x6U
 #घोषणा TYPE_32BITSPACE	0x0U
 #घोषणा MSI			0x1U
 #घोषणा MSI_MEMORY		0x0U
#घोषणा INTLINEREG		0x13c
#घोषणा INTPINREG		0x13c
#घोषणा RETVALREG		0x140
#घोषणा PCIAPCNTREG		0x140
 #घोषणा TKYGNT			0x04000000U
 #घोषणा TKYGNT_ENABLE		0x04000000U
 #घोषणा TKYGNT_DISABLE		0x00000000U
 #घोषणा PAPC			0x03000000U
 #घोषणा PAPC_ALTERNATE_B	0x02000000U
 #घोषणा PAPC_ALTERNATE_0	0x01000000U
 #घोषणा PAPC_FAIR		0x00000000U
 #घोषणा RTYVAL(val)		(((uपूर्णांक32_t)(val) << 7) & 0xff00U)
 #घोषणा RTYVAL_MASK		0xff00U

#घोषणा PCI_CLOCK_MAX		33333333U

/*
 * Default setup
 */
#घोषणा PCI_MASTER_MEM1_BUS_BASE_ADDRESS	0x10000000U
#घोषणा PCI_MASTER_MEM1_ADDRESS_MASK		0x7c000000U
#घोषणा PCI_MASTER_MEM1_PCI_BASE_ADDRESS	0x10000000U

#घोषणा PCI_TARGET_MEM1_ADDRESS_MASK		0x08000000U
#घोषणा PCI_TARGET_MEM1_BUS_BASE_ADDRESS	0x00000000U

#घोषणा PCI_MASTER_IO_BUS_BASE_ADDRESS		0x16000000U
#घोषणा PCI_MASTER_IO_ADDRESS_MASK		0x7e000000U
#घोषणा PCI_MASTER_IO_PCI_BASE_ADDRESS		0x00000000U

#घोषणा PCI_MAILBOX_BASE_ADDRESS		0x00000000U

#घोषणा PCI_TARGET_WINDOW1_BASE_ADDRESS		0x00000000U

#घोषणा IO_PORT_BASE		KSEG1ADDR(PCI_MASTER_IO_BUS_BASE_ADDRESS)
#घोषणा IO_PORT_RESOURCE_START	PCI_MASTER_IO_PCI_BASE_ADDRESS
#घोषणा IO_PORT_RESOURCE_END	(~PCI_MASTER_IO_ADDRESS_MASK & PCI_MASTER_ADDRESS_MASK)

#घोषणा PCI_IO_RESOURCE_START	0x01000000UL
#घोषणा PCI_IO_RESOURCE_END	0x01ffffffUL

#घोषणा PCI_MEM_RESOURCE_START	0x11000000UL
#घोषणा PCI_MEM_RESOURCE_END	0x13ffffffUL

#पूर्ण_अगर /* __PCI_VR41XX_H */
