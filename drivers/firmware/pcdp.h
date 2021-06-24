<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Definitions क्रम PCDP-defined console devices
 *
 * For DIG64_HCDPv10a_01.pdf and DIG64_PCDPv20.pdf (v1.0a and v2.0 resp.),
 * please see <http://www.dig64.org/specअगरications/>
 *
 * (c) Copyright 2002, 2004 Hewlett-Packard Development Company, L.P.
 *	Khalid Aziz <khalid.aziz@hp.com>
 *	Bjorn Helgaas <bjorn.helgaas@hp.com>
 */

#घोषणा PCDP_CONSOLE			0
#घोषणा PCDP_DEBUG			1
#घोषणा PCDP_CONSOLE_OUTPUT		2
#घोषणा PCDP_CONSOLE_INPUT		3

#घोषणा PCDP_UART			(0 << 3)
#घोषणा PCDP_VGA			(1 << 3)
#घोषणा PCDP_USB			(2 << 3)

/* pcdp_uart.type and pcdp_device.type */
#घोषणा PCDP_CONSOLE_UART		(PCDP_UART | PCDP_CONSOLE)
#घोषणा PCDP_DEBUG_UART			(PCDP_UART | PCDP_DEBUG)
#घोषणा PCDP_CONSOLE_VGA		(PCDP_VGA  | PCDP_CONSOLE_OUTPUT)
#घोषणा PCDP_CONSOLE_USB		(PCDP_USB  | PCDP_CONSOLE_INPUT)

/* pcdp_uart.flags */
#घोषणा PCDP_UART_EDGE_SENSITIVE	(1 << 0)
#घोषणा PCDP_UART_ACTIVE_LOW		(1 << 1)
#घोषणा PCDP_UART_PRIMARY_CONSOLE	(1 << 2)
#घोषणा PCDP_UART_IRQ			(1 << 6) /* in pci_func क्रम rev < 3 */
#घोषणा PCDP_UART_PCI			(1 << 7) /* in pci_func क्रम rev < 3 */

काष्ठा pcdp_uart अणु
	u8				type;
	u8				bits;
	u8				parity;
	u8				stop_bits;
	u8				pci_seg;
	u8				pci_bus;
	u8				pci_dev;
	u8				pci_func;
	u64				baud;
	काष्ठा acpi_generic_address	addr;
	u16				pci_dev_id;
	u16				pci_venकरोr_id;
	u32				gsi;
	u32				घड़ी_rate;
	u8				pci_prog_पूर्णांकfc;
	u8				flags;
	u16				conout_index;
	u32				reserved;
पूर्ण __attribute__((packed));

#घोषणा PCDP_IF_PCI	1

/* pcdp_अगर_pci.trans */
#घोषणा PCDP_PCI_TRANS_IOPORT	0x02
#घोषणा PCDP_PCI_TRANS_MMIO	0x01

काष्ठा pcdp_अगर_pci अणु
	u8			पूर्णांकerconnect;
	u8			reserved;
	u16			length;
	u8			segment;
	u8			bus;
	u8			dev;
	u8			fun;
	u16			dev_id;
	u16			venकरोr_id;
	u32			acpi_पूर्णांकerrupt;
	u64			mmio_tra;
	u64			ioport_tra;
	u8			flags;
	u8			trans;
पूर्ण __attribute__((packed));

काष्ठा pcdp_vga अणु
	u8			count;		/* address space descriptors */
पूर्ण __attribute__((packed));

/* pcdp_device.flags */
#घोषणा PCDP_PRIMARY_CONSOLE	1

काष्ठा pcdp_device अणु
	u8			type;
	u8			flags;
	u16			length;
	u16			efi_index;
	/* next data is pcdp_अगर_pci or pcdp_अगर_acpi (not yet supported) */
	/* next data is device specअगरic type (currently only pcdp_vga) */
पूर्ण __attribute__((packed));

काष्ठा pcdp अणु
	u8			signature[4];
	u32			length;
	u8			rev;		/* PCDP v2.0 is rev 3 */
	u8			chksum;
	u8			oemid[6];
	u8			oem_tabid[8];
	u32			oem_rev;
	u8			creator_id[4];
	u32			creator_rev;
	u32			num_uarts;
	काष्ठा pcdp_uart	uart[];	/* actual size is num_uarts */
	/* reमुख्यder of table is pcdp_device काष्ठाures */
पूर्ण __attribute__((packed));
