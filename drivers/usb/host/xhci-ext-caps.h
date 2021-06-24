<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * xHCI host controller driver
 *
 * Copyright (C) 2008 Intel Corp.
 *
 * Author: Sarah Sharp
 * Some code borrowed from the Linux EHCI driver.
 */

/* HC should halt within 16 ms, but use 32 ms as some hosts take दीर्घer */
#घोषणा XHCI_MAX_HALT_USEC	(32 * 1000)
/* HC not running - set to 1 when run/stop bit is cleared. */
#घोषणा XHCI_STS_HALT		(1<<0)

/* HCCPARAMS offset from PCI base address */
#घोषणा XHCI_HCC_PARAMS_OFFSET	0x10
/* HCCPARAMS contains the first extended capability poपूर्णांकer */
#घोषणा XHCI_HCC_EXT_CAPS(p)	(((p)>>16)&0xffff)

/* Command and Status रेजिस्टरs offset from the Operational Registers address */
#घोषणा XHCI_CMD_OFFSET		0x00
#घोषणा XHCI_STS_OFFSET		0x04

#घोषणा XHCI_MAX_EXT_CAPS		50

/* Capability Register */
/* bits 7:0 - how दीर्घ is the Capabilities रेजिस्टर */
#घोषणा XHCI_HC_LENGTH(p)	(((p)>>00)&0x00ff)

/* Extended capability रेजिस्टर fields */
#घोषणा XHCI_EXT_CAPS_ID(p)	(((p)>>0)&0xff)
#घोषणा XHCI_EXT_CAPS_NEXT(p)	(((p)>>8)&0xff)
#घोषणा	XHCI_EXT_CAPS_VAL(p)	((p)>>16)
/* Extended capability IDs - ID 0 reserved */
#घोषणा XHCI_EXT_CAPS_LEGACY	1
#घोषणा XHCI_EXT_CAPS_PROTOCOL	2
#घोषणा XHCI_EXT_CAPS_PM	3
#घोषणा XHCI_EXT_CAPS_VIRT	4
#घोषणा XHCI_EXT_CAPS_ROUTE	5
/* IDs 6-9 reserved */
#घोषणा XHCI_EXT_CAPS_DEBUG	10
/* Venकरोr caps */
#घोषणा XHCI_EXT_CAPS_VENDOR_INTEL	192
/* USB Legacy Support Capability - section 7.1.1 */
#घोषणा XHCI_HC_BIOS_OWNED	(1 << 16)
#घोषणा XHCI_HC_OS_OWNED	(1 << 24)

/* USB Legacy Support Capability - section 7.1.1 */
/* Add this offset, plus the value of xECP in HCCPARAMS to the base address */
#घोषणा XHCI_LEGACY_SUPPORT_OFFSET	(0x00)

/* USB Legacy Support Control and Status Register  - section 7.1.2 */
/* Add this offset, plus the value of xECP in HCCPARAMS to the base address */
#घोषणा XHCI_LEGACY_CONTROL_OFFSET	(0x04)
/* bits 1:3, 5:12, and 17:19 need to be preserved; bits 21:28 should be zero */
#घोषणा	XHCI_LEGACY_DISABLE_SMI		((0x7 << 1) + (0xff << 5) + (0x7 << 17))
#घोषणा XHCI_LEGACY_SMI_EVENTS		(0x7 << 29)

/* USB 2.0 xHCI 0.96 L1C capability - section 7.2.2.1.3.2 */
#घोषणा XHCI_L1C               (1 << 16)

/* USB 2.0 xHCI 1.0 hardware LMP capability - section 7.2.2.1.3.2 */
#घोषणा XHCI_HLC               (1 << 19)
#घोषणा XHCI_BLC               (1 << 20)

/* command रेजिस्टर values to disable पूर्णांकerrupts and halt the HC */
/* start/stop HC execution - करो not ग_लिखो unless HC is halted*/
#घोषणा XHCI_CMD_RUN		(1 << 0)
/* Event Interrupt Enable - get irq when EINT bit is set in USBSTS रेजिस्टर */
#घोषणा XHCI_CMD_EIE		(1 << 2)
/* Host System Error Interrupt Enable - get irq when HSEIE bit set in USBSTS */
#घोषणा XHCI_CMD_HSEIE		(1 << 3)
/* Enable Wrap Event - '1' means xHC generates an event when MFINDEX wraps. */
#घोषणा XHCI_CMD_EWE		(1 << 10)

#घोषणा XHCI_IRQS		(XHCI_CMD_EIE | XHCI_CMD_HSEIE | XHCI_CMD_EWE)

/* true: Controller Not Ready to accept करोorbell or op reg ग_लिखोs after reset */
#घोषणा XHCI_STS_CNR		(1 << 11)

#समावेश <linux/पन.स>

/**
 * Find the offset of the extended capabilities with capability ID id.
 *
 * @base	PCI MMIO रेजिस्टरs base address.
 * @start	address at which to start looking, (0 or HCC_PARAMS to start at
 *		beginning of list)
 * @id		Extended capability ID to search क्रम, or 0 क्रम the next
 *		capability
 *
 * Returns the offset of the next matching extended capability काष्ठाure.
 * Some capabilities can occur several बार, e.g., the XHCI_EXT_CAPS_PROTOCOL,
 * and this provides a way to find them all.
 */

अटल अंतरभूत पूर्णांक xhci_find_next_ext_cap(व्योम __iomem *base, u32 start, पूर्णांक id)
अणु
	u32 val;
	u32 next;
	u32 offset;

	offset = start;
	अगर (!start || start == XHCI_HCC_PARAMS_OFFSET) अणु
		val = पढ़ोl(base + XHCI_HCC_PARAMS_OFFSET);
		अगर (val == ~0)
			वापस 0;
		offset = XHCI_HCC_EXT_CAPS(val) << 2;
		अगर (!offset)
			वापस 0;
	पूर्ण
	करो अणु
		val = पढ़ोl(base + offset);
		अगर (val == ~0)
			वापस 0;
		अगर (offset != start && (id == 0 || XHCI_EXT_CAPS_ID(val) == id))
			वापस offset;

		next = XHCI_EXT_CAPS_NEXT(val);
		offset += next << 2;
	पूर्ण जबतक (next);

	वापस 0;
पूर्ण
