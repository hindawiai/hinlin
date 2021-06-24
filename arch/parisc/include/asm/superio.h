<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _PARISC_SUPERIO_H
#घोषणा _PARISC_SUPERIO_H

#घोषणा IC_PIC1    0x20		/* PCI I/O address of master 8259 */
#घोषणा IC_PIC2    0xA0		/* PCI I/O address of slave */

/* Config Space Offsets to configuration and base address रेजिस्टरs */
#घोषणा SIO_CR     0x5A		/* Configuration Register */
#घोषणा SIO_ACPIBAR 0x88	/* ACPI BAR */
#घोषणा SIO_FDCBAR 0x90		/* Floppy Disk Controller BAR */
#घोषणा SIO_SP1BAR 0x94		/* Serial 1 BAR */
#घोषणा SIO_SP2BAR 0x98		/* Serial 2 BAR */
#घोषणा SIO_PPBAR  0x9C		/* Parallel BAR */

#घोषणा TRIGGER_1  0x67		/* Edge/level trigger रेजिस्टर 1 */
#घोषणा TRIGGER_2  0x68		/* Edge/level trigger रेजिस्टर 2 */

/* Interrupt Routing Control रेजिस्टरs */
#घोषणा CFG_IR_SER    0x69	/* Serial 1 [0:3] and Serial 2 [4:7] */
#घोषणा CFG_IR_PFD    0x6a	/* Parallel [0:3] and Floppy [4:7] */
#घोषणा CFG_IR_IDE    0x6b	/* IDE1     [0:3] and IDE2 [4:7] */
#घोषणा CFG_IR_INTAB  0x6c	/* PCI INTA [0:3] and INT B [4:7] */
#घोषणा CFG_IR_INTCD  0x6d	/* PCI INTC [0:3] and INT D [4:7] */
#घोषणा CFG_IR_PS2    0x6e	/* PS/2 KBINT [0:3] and Mouse [4:7] */
#घोषणा CFG_IR_FXBUS  0x6f	/* FXIRQ[0] [0:3] and FXIRQ[1] [4:7] */
#घोषणा CFG_IR_USB    0x70	/* FXIRQ[2] [0:3] and USB [4:7] */
#घोषणा CFG_IR_ACPI   0x71	/* ACPI SCI [0:3] and reserved [4:7] */

#घोषणा CFG_IR_LOW     CFG_IR_SER	/* Lowest पूर्णांकerrupt routing reg */
#घोषणा CFG_IR_HIGH    CFG_IR_ACPI	/* Highest पूर्णांकerrupt routing reg */

/* 8259 operational control words */
#घोषणा OCW2_EOI   0x20		/* Non-specअगरic EOI */
#घोषणा OCW2_SEOI  0x60		/* Specअगरic EOI */
#घोषणा OCW3_IIR   0x0A		/* Read request रेजिस्टर */
#घोषणा OCW3_ISR   0x0B		/* Read service रेजिस्टर */
#घोषणा OCW3_POLL  0x0C		/* Poll the PIC क्रम an पूर्णांकerrupt vector */

/* Interrupt lines. Only PIC1 is used */
#घोषणा USB_IRQ    1		/* USB */
#घोषणा SP1_IRQ    3		/* Serial port 1 */
#घोषणा SP2_IRQ    4		/* Serial port 2 */
#घोषणा PAR_IRQ    5		/* Parallel port */
#घोषणा FDC_IRQ    6		/* Floppy controller */
#घोषणा IDE_IRQ    7		/* IDE (pri+sec) */

/* ACPI रेजिस्टरs */
#घोषणा USB_REG_CR	0x1f	/* USB Regulator Control Register */

#घोषणा SUPERIO_NIRQS   8

काष्ठा superio_device अणु
	u32 fdc_base;
	u32 sp1_base;
	u32 sp2_base;
	u32 pp_base;
	u32 acpi_base;
	पूर्णांक suckyio_irq_enabled;
	काष्ठा pci_dev *lio_pdev;       /* pci device क्रम legacy IO (fn 1) */
	काष्ठा pci_dev *usb_pdev;       /* pci device क्रम USB (fn 2) */
पूर्ण;

/*
 * Does NS make a 87415 based plug in PCI card? If so, because of this
 * macro we currently करोn't support it being plugged पूर्णांकo a machine
 * that contains a SuperIO chip AND has CONFIG_SUPERIO enabled.
 *
 * This could be fixed by checking to see अगर function 1 exists, and
 * अगर it is SuperIO Legacy IO; but really now, is this combination
 * going to EVER happen?
 */

#घोषणा SUPERIO_IDE_FN 0 /* Function number of IDE controller */
#घोषणा SUPERIO_LIO_FN 1 /* Function number of Legacy IO controller */
#घोषणा SUPERIO_USB_FN 2 /* Function number of USB controller */

#घोषणा is_superio_device(x) \
	(((x)->venकरोr == PCI_VENDOR_ID_NS) && \
	(  ((x)->device == PCI_DEVICE_ID_NS_87415) \
	|| ((x)->device == PCI_DEVICE_ID_NS_87560_LIO) \
	|| ((x)->device == PCI_DEVICE_ID_NS_87560_USB) ) )

बाह्य पूर्णांक superio_fixup_irq(काष्ठा pci_dev *pcidev); /* called by iosapic */

#पूर्ण_अगर /* _PARISC_SUPERIO_H */
