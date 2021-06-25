<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Intel CE4100  platक्रमm specअगरic setup code
 *
 * (C) Copyright 2010 Intel Corporation
 */
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/irq.h>
#समावेश <linux/reboot.h>
#समावेश <linux/serial_reg.h>
#समावेश <linux/serial_8250.h>

#समावेश <यंत्र/ce4100.h>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/i8259.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/io_apic.h>
#समावेश <यंत्र/emergency-restart.h>

/*
 * The CE4100 platक्रमm has an पूर्णांकernal 8051 Microcontroller which is
 * responsible क्रम संकेतing to the बाह्यal Power Management Unit the
 * पूर्णांकention to reset, reboot or घातer off the प्रणाली. This 8051 device has
 * its command रेजिस्टर mapped at I/O port 0xcf9 and the value 0x4 is used
 * to घातer off the प्रणाली.
 */
अटल व्योम ce4100_घातer_off(व्योम)
अणु
	outb(0x4, 0xcf9);
पूर्ण

#अगर_घोषित CONFIG_SERIAL_8250

अटल अचिन्हित पूर्णांक mem_serial_in(काष्ठा uart_port *p, पूर्णांक offset)
अणु
	offset = offset << p->regshअगरt;
	वापस पढ़ोl(p->membase + offset);
पूर्ण

/*
 * The UART Tx पूर्णांकerrupts are not set under some conditions and thereक्रमe serial
 * transmission hangs. This is a silicon issue and has not been root caused. The
 * workaround क्रम this silicon issue checks UART_LSR_THRE bit and UART_LSR_TEMT
 * bit of LSR रेजिस्टर in पूर्णांकerrupt handler to see whether at least one of these
 * two bits is set, अगर so then process the transmit request. If this workaround
 * is not applied, then the serial transmission may hang. This workaround is क्रम
 * errata number 9 in Errata - B step.
*/

अटल अचिन्हित पूर्णांक ce4100_mem_serial_in(काष्ठा uart_port *p, पूर्णांक offset)
अणु
	अचिन्हित पूर्णांक ret, ier, lsr;

	अगर (offset == UART_IIR) अणु
		offset = offset << p->regshअगरt;
		ret = पढ़ोl(p->membase + offset);
		अगर (ret & UART_IIR_NO_INT) अणु
			/* see अगर the TX पूर्णांकerrupt should have really set */
			ier = mem_serial_in(p, UART_IER);
			/* see अगर the UART's XMIT पूर्णांकerrupt is enabled */
			अगर (ier & UART_IER_THRI) अणु
				lsr = mem_serial_in(p, UART_LSR);
				/* now check to see अगर the UART should be
				   generating an पूर्णांकerrupt (but isn't) */
				अगर (lsr & (UART_LSR_THRE | UART_LSR_TEMT))
					ret &= ~UART_IIR_NO_INT;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा
		ret =  mem_serial_in(p, offset);
	वापस ret;
पूर्ण

अटल व्योम ce4100_mem_serial_out(काष्ठा uart_port *p, पूर्णांक offset, पूर्णांक value)
अणु
	offset = offset << p->regshअगरt;
	ग_लिखोl(value, p->membase + offset);
पूर्ण

अटल व्योम ce4100_serial_fixup(पूर्णांक port, काष्ठा uart_port *up,
	u32 *capabilities)
अणु
#अगर_घोषित CONFIG_EARLY_PRINTK
	/*
	 * Over ride the legacy port configuration that comes from
	 * यंत्र/serial.h. Using the ioport driver then चयनing to the
	 * PCI memmaped driver hangs the IOAPIC
	 */
	अगर (up->iotype !=  UPIO_MEM32) अणु
		up->uartclk  = 14745600;
		up->mapbase = 0xdffe0200;
		set_fixmap_nocache(FIX_EARLYCON_MEM_BASE,
				up->mapbase & PAGE_MASK);
		up->membase =
			(व्योम __iomem *)__fix_to_virt(FIX_EARLYCON_MEM_BASE);
		up->membase += up->mapbase & ~PAGE_MASK;
		up->mapbase += port * 0x100;
		up->membase += port * 0x100;
		up->iotype   = UPIO_MEM32;
		up->regshअगरt = 2;
		up->irq = 4;
	पूर्ण
#पूर्ण_अगर
	up->iobase = 0;
	up->serial_in = ce4100_mem_serial_in;
	up->serial_out = ce4100_mem_serial_out;

	*capabilities |= (1 << 12);
पूर्ण

अटल __init व्योम sdv_serial_fixup(व्योम)
अणु
	serial8250_set_isa_configurator(ce4100_serial_fixup);
पूर्ण

#अन्यथा
अटल अंतरभूत व्योम sdv_serial_fixup(व्योम) अणुपूर्ण;
#पूर्ण_अगर

अटल व्योम __init sdv_arch_setup(व्योम)
अणु
	sdv_serial_fixup();
पूर्ण

अटल व्योम sdv_pci_init(व्योम)
अणु
	x86_of_pci_init();
पूर्ण

/*
 * CE4100 specअगरic x86_init function overrides and early setup
 * calls.
 */
व्योम __init x86_ce4100_early_setup(व्योम)
अणु
	x86_init.oem.arch_setup = sdv_arch_setup;
	x86_init.resources.probe_roms = x86_init_noop;
	x86_init.mpparse.get_smp_config = x86_init_uपूर्णांक_noop;
	x86_init.mpparse.find_smp_config = x86_init_noop;
	x86_init.mpparse.setup_ioapic_ids = setup_ioapic_ids_from_mpc_nocheck;
	x86_init.pci.init = ce4100_pci_init;
	x86_init.pci.init_irq = sdv_pci_init;

	/*
	 * By शेष, the reboot method is ACPI which is supported by the
	 * CE4100 bootloader CEFDK using FADT.ResetReg Address and ResetValue
	 * the bootloader will however issue a प्रणाली घातer off instead of
	 * reboot. By using BOOT_KBD we ensure proper प्रणाली reboot as
	 * expected.
	 */
	reboot_type = BOOT_KBD;

	pm_घातer_off = ce4100_घातer_off;
पूर्ण
