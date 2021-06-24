<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Parse the EFI PCDP table to locate the console device.
 *
 * (c) Copyright 2002, 2003, 2004 Hewlett-Packard Development Company, L.P.
 *	Khalid Aziz <khalid.aziz@hp.com>
 *	Alex Williamson <alex.williamson@hp.com>
 *	Bjorn Helgaas <bjorn.helgaas@hp.com>
 */

#समावेश <linux/acpi.h>
#समावेश <linux/console.h>
#समावेश <linux/efi.h>
#समावेश <linux/serial.h>
#समावेश <linux/serial_core.h>
#समावेश <यंत्र/vga.h>
#समावेश "pcdp.h"

अटल पूर्णांक __init
setup_serial_console(काष्ठा pcdp_uart *uart)
अणु
#अगर_घोषित CONFIG_SERIAL_8250_CONSOLE
	पूर्णांक mmio;
	अटल अक्षर options[64], *p = options;
	अक्षर parity;

	mmio = (uart->addr.space_id == ACPI_ADR_SPACE_SYSTEM_MEMORY);
	p += प्र_लिखो(p, "uart8250,%s,0x%llx",
		mmio ? "mmio" : "io", uart->addr.address);
	अगर (uart->baud) अणु
		p += प्र_लिखो(p, ",%llu", uart->baud);
		अगर (uart->bits) अणु
			चयन (uart->parity) अणु
			    हाल 0x2: parity = 'e'; अवरोध;
			    हाल 0x3: parity = 'o'; अवरोध;
			    शेष:  parity = 'n';
			पूर्ण
			p += प्र_लिखो(p, "%c%d", parity, uart->bits);
		पूर्ण
	पूर्ण

	add_preferred_console("uart", 8250, &options[9]);
	वापस setup_earlycon(options);
#अन्यथा
	वापस -ENODEV;
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक __init
setup_vga_console(काष्ठा pcdp_device *dev)
अणु
#अगर defined(CONFIG_VT) && defined(CONFIG_VGA_CONSOLE)
	u8 *अगर_ptr;

	अगर_ptr = ((u8 *)dev + माप(काष्ठा pcdp_device));
	अगर (अगर_ptr[0] == PCDP_IF_PCI) अणु
		काष्ठा pcdp_अगर_pci अगर_pci;

		/* काष्ठा copy since अगरptr might not be correctly aligned */

		स_नकल(&अगर_pci, अगर_ptr, माप(अगर_pci));

		अगर (अगर_pci.trans & PCDP_PCI_TRANS_IOPORT)
			vga_console_iobase = अगर_pci.ioport_tra;

		अगर (अगर_pci.trans & PCDP_PCI_TRANS_MMIO)
			vga_console_membase = अगर_pci.mmio_tra;
	पूर्ण

	अगर (efi_mem_type(vga_console_membase + 0xA0000) == EFI_CONVENTIONAL_MEMORY) अणु
		prपूर्णांकk(KERN_ERR "PCDP: VGA selected, but frame buffer is not MMIO!\n");
		वापस -ENODEV;
	पूर्ण

	conचयनp = &vga_con;
	prपूर्णांकk(KERN_INFO "PCDP: VGA console\n");
	वापस 0;
#अन्यथा
	वापस -ENODEV;
#पूर्ण_अगर
पूर्ण

बाह्य अचिन्हित दीर्घ hcdp_phys;

पूर्णांक __init
efi_setup_pcdp_console(अक्षर *cmdline)
अणु
	काष्ठा pcdp *pcdp;
	काष्ठा pcdp_uart *uart;
	काष्ठा pcdp_device *dev, *end;
	पूर्णांक i, serial = 0;
	पूर्णांक rc = -ENODEV;

	अगर (hcdp_phys == EFI_INVALID_TABLE_ADDR)
		वापस -ENODEV;

	pcdp = early_memremap(hcdp_phys, 4096);
	prपूर्णांकk(KERN_INFO "PCDP: v%d at 0x%lx\n", pcdp->rev, hcdp_phys);

	अगर (म_माला(cmdline, "console=hcdp")) अणु
		अगर (pcdp->rev < 3)
			serial = 1;
	पूर्ण अन्यथा अगर (म_माला(cmdline, "console=")) अणु
		prपूर्णांकk(KERN_INFO "Explicit \"console=\"; ignoring PCDP\n");
		जाओ out;
	पूर्ण

	अगर (pcdp->rev < 3 && efi_uart_console_only())
		serial = 1;

	क्रम (i = 0, uart = pcdp->uart; i < pcdp->num_uarts; i++, uart++) अणु
		अगर (uart->flags & PCDP_UART_PRIMARY_CONSOLE || serial) अणु
			अगर (uart->type == PCDP_CONSOLE_UART) अणु
				rc = setup_serial_console(uart);
				जाओ out;
			पूर्ण
		पूर्ण
	पूर्ण

	end = (काष्ठा pcdp_device *) ((u8 *) pcdp + pcdp->length);
	क्रम (dev = (काष्ठा pcdp_device *) (pcdp->uart + pcdp->num_uarts);
	     dev < end;
	     dev = (काष्ठा pcdp_device *) ((u8 *) dev + dev->length)) अणु
		अगर (dev->flags & PCDP_PRIMARY_CONSOLE) अणु
			अगर (dev->type == PCDP_CONSOLE_VGA) अणु
				rc = setup_vga_console(dev);
				जाओ out;
			पूर्ण
		पूर्ण
	पूर्ण

out:
	early_memunmap(pcdp, 4096);
	वापस rc;
पूर्ण
