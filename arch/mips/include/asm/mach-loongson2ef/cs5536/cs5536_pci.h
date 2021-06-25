<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * the definition file of cs5536 Virtual Support Module(VSM).
 * pci configuration space can be accessed through the VSM, so
 * there is no need of the MSR पढ़ो/ग_लिखो now, except the spec.
 * MSR रेजिस्टरs which are not implemented yet.
 *
 * Copyright (C) 2007 Lemote Inc.
 * Author : jlliu, liujl@lemote.com
 */

#अगर_अघोषित _CS5536_PCI_H
#घोषणा _CS5536_PCI_H

#समावेश <linux/types.h>
#समावेश <linux/pci_regs.h>

बाह्य व्योम cs5536_pci_conf_ग_लिखो4(पूर्णांक function, पूर्णांक reg, u32 value);
बाह्य u32 cs5536_pci_conf_पढ़ो4(पूर्णांक function, पूर्णांक reg);

#घोषणा CS5536_ACC_INTR		9
#घोषणा CS5536_IDE_INTR		14
#घोषणा CS5536_USB_INTR		11
#घोषणा CS5536_MFGPT_INTR	5
#घोषणा CS5536_UART1_INTR	4
#घोषणा CS5536_UART2_INTR	3

/************** PCI BUS DEVICE FUNCTION ***************/

/*
 * PCI bus device function
 */
#घोषणा PCI_BUS_CS5536		0
#घोषणा PCI_IDSEL_CS5536	14

/********** STANDARD PCI-2.2 EXPANSION ****************/

/*
 * PCI configuration space
 * we have to भवize the PCI configure space head, so we should
 * define the necessary IDs and some others.
 */

/* CONFIG of PCI VENDOR ID*/
#घोषणा CFG_PCI_VENDOR_ID(mod_dev_id, sys_venकरोr_id) \
	(((mod_dev_id) << 16) | (sys_venकरोr_id))

/* VENDOR ID */
#घोषणा CS5536_VENDOR_ID	0x1022

/* DEVICE ID */
#घोषणा CS5536_ISA_DEVICE_ID		0x2090
#घोषणा CS5536_IDE_DEVICE_ID		0x209a
#घोषणा CS5536_ACC_DEVICE_ID		0x2093
#घोषणा CS5536_OHCI_DEVICE_ID		0x2094
#घोषणा CS5536_EHCI_DEVICE_ID		0x2095

/* CLASS CODE : CLASS SUB-CLASS INTERFACE */
#घोषणा CS5536_ISA_CLASS_CODE		0x060100
#घोषणा CS5536_IDE_CLASS_CODE		0x010180
#घोषणा CS5536_ACC_CLASS_CODE		0x040100
#घोषणा CS5536_OHCI_CLASS_CODE		0x0C0310
#घोषणा CS5536_EHCI_CLASS_CODE		0x0C0320

/* BHLC : BIST HEADER-TYPE LATENCY-TIMER CACHE-LINE-SIZE */

#घोषणा CFG_PCI_CACHE_LINE_SIZE(header_type, latency_समयr)	\
	((PCI_NONE_BIST << 24) | ((header_type) << 16) \
		| ((latency_समयr) << 8) | PCI_NORMAL_CACHE_LINE_SIZE);

#घोषणा PCI_NONE_BIST			0x00	/* RO not implemented yet. */
#घोषणा PCI_BRIDGE_HEADER_TYPE		0x80	/* RO */
#घोषणा PCI_NORMAL_HEADER_TYPE		0x00
#घोषणा PCI_NORMAL_LATENCY_TIMER	0x00
#घोषणा PCI_NORMAL_CACHE_LINE_SIZE	0x08	/* RW */

/* BAR */
#घोषणा PCI_BAR0_REG			0x10
#घोषणा PCI_BAR1_REG			0x14
#घोषणा PCI_BAR2_REG			0x18
#घोषणा PCI_BAR3_REG			0x1c
#घोषणा PCI_BAR4_REG			0x20
#घोषणा PCI_BAR5_REG			0x24
#घोषणा PCI_BAR_RANGE_MASK		0xFFFFFFFF

/* CARDBUS CIS POINTER */
#घोषणा PCI_CARDBUS_CIS_POINTER		0x00000000

/* SUBSYSTEM VENDOR ID	*/
#घोषणा CS5536_SUB_VENDOR_ID		CS5536_VENDOR_ID

/* SUBSYSTEM ID */
#घोषणा CS5536_ISA_SUB_ID		CS5536_ISA_DEVICE_ID
#घोषणा CS5536_IDE_SUB_ID		CS5536_IDE_DEVICE_ID
#घोषणा CS5536_ACC_SUB_ID		CS5536_ACC_DEVICE_ID
#घोषणा CS5536_OHCI_SUB_ID		CS5536_OHCI_DEVICE_ID
#घोषणा CS5536_EHCI_SUB_ID		CS5536_EHCI_DEVICE_ID

/* EXPANSION ROM BAR */
#घोषणा PCI_EXPANSION_ROM_BAR		0x00000000

/* CAPABILITIES POINTER */
#घोषणा PCI_CAPLIST_POINTER		0x00000000
#घोषणा PCI_CAPLIST_USB_POINTER		0x40
/* INTERRUPT */

#घोषणा CFG_PCI_INTERRUPT_LINE(pin, mod_पूर्णांकr) \
	((PCI_MAX_LATENCY << 24) | (PCI_MIN_GRANT << 16) | \
		((pin) << 8) | (mod_पूर्णांकr))

#घोषणा PCI_MAX_LATENCY			0x40
#घोषणा PCI_MIN_GRANT			0x00
#घोषणा PCI_DEFAULT_PIN			0x01

/*********** EXPANSION PCI REG ************************/

/*
 * ISA EXPANSION
 */
#घोषणा PCI_UART1_INT_REG	0x50
#घोषणा PCI_UART2_INT_REG	0x54
#घोषणा PCI_ISA_FIXUP_REG	0x58

/*
 * IDE EXPANSION
 */
#घोषणा PCI_IDE_CFG_REG		0x40
#घोषणा CS5536_IDE_FLASH_SIGNATURE	0xDEADBEEF
#घोषणा PCI_IDE_DTC_REG		0x48
#घोषणा PCI_IDE_CAST_REG	0x4C
#घोषणा PCI_IDE_ETC_REG		0x50
#घोषणा PCI_IDE_PM_REG		0x54
#घोषणा PCI_IDE_INT_REG		0x60

/*
 * ACC EXPANSION
 */
#घोषणा PCI_ACC_INT_REG		0x50

/*
 * OHCI EXPANSION : INTTERUPT IS IMPLEMENTED BY THE OHCI
 */
#घोषणा PCI_OHCI_PM_REG		0x40
#घोषणा PCI_OHCI_INT_REG	0x50

/*
 * EHCI EXPANSION
 */
#घोषणा PCI_EHCI_LEGSMIEN_REG	0x50
#घोषणा PCI_EHCI_LEGSMISTS_REG	0x54
#घोषणा PCI_EHCI_FLADJ_REG	0x60

#पूर्ण_अगर				/* _CS5536_PCI_H_ */
