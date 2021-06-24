<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*      National Semiconductor NS87560UBD Super I/O controller used in
 *      HP [BCJ]x000 workstations.
 *
 *      This chip is a horrid piece of engineering, and National
 *      denies any knowledge of its existence. Thus no datasheet is
 *      available off www.national.com. 
 *
 *	(C) Copyright 2000 Linuxcare, Inc.
 * 	(C) Copyright 2000 Linuxcare Canada, Inc.
 *	(C) Copyright 2000 Martin K. Petersen <mkp@linuxcare.com>
 * 	(C) Copyright 2000 Alex deVries <alex@onefishtwo.ca>
 *      (C) Copyright 2001 John Marvin <jsm fc hp com>
 *      (C) Copyright 2003 Grant Grundler <grundler parisc-linux org>
 *	(C) Copyright 2005 Kyle McMartin <kyle@parisc-linux.org>
 *	(C) Copyright 2006 Helge Deller <deller@gmx.de>
 *
 *	The initial version of this is by Martin Peterson.  Alex deVries
 *	has spent a bit of समय trying to coax it पूर्णांकo working.
 *
 *      Major changes to get basic पूर्णांकerrupt infraकाष्ठाure working to
 *      hopefully be able to support all SuperIO devices. Currently
 *      works with serial. -- John Marvin <jsm@fc.hp.com>
 *
 *	Converted superio_init() to be a PCI_FIXUP_FINAL callee.
 *         -- Kyle McMartin <kyle@parisc-linux.org>
 */


/* NOTES:
 * 
 * Function 0 is an IDE controller. It is identical to a PC87415 IDE
 * controller (and identअगरies itself as such).
 *
 * Function 1 is a "Legacy I/O" controller. Under this function is a
 * whole mess of legacy I/O peripherals. Of course, HP hasn't enabled
 * all the functionality in hardware, but the following is available:
 *
 *      Two 16550A compatible serial controllers
 *      An IEEE 1284 compatible parallel port
 *      A floppy disk controller
 *
 * Function 2 is a USB controller.
 *
 * We must be incredibly careful during initialization.  Since all
 * पूर्णांकerrupts are routed through function 1 (which is not allowed by
 * the PCI spec), we need to program the PICs on the legacy I/O port
 * *beक्रमe* we attempt to set up IDE and USB.  @#$!&
 *
 * According to HP, devices are only enabled by firmware अगर they have
 * a physical device connected.
 *
 * Configuration रेजिस्टर bits:
 *     0x5A: FDC, SP1, IDE1, SP2, IDE2, PAR, Reserved, P92
 *     0x5B: RTC, 8259, 8254, DMA1, DMA2, KBC, P61, APM
 *
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/ioport.h>
#समावेश <linux/serial.h>
#समावेश <linux/pci.h>
#समावेश <linux/parport.h>
#समावेश <linux/parport_pc.h>
#समावेश <linux/termios.h>
#समावेश <linux/tty.h>
#समावेश <linux/serial_core.h>
#समावेश <linux/serial_8250.h>
#समावेश <linux/delay.h>

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/hardware.h>
#समावेश <यंत्र/superपन.स>

अटल काष्ठा superio_device sio_dev;


#अघोषित DEBUG_SUPERIO_INIT

#अगर_घोषित DEBUG_SUPERIO_INIT
#घोषणा DBG_INIT(x...)  prपूर्णांकk(x)
#अन्यथा
#घोषणा DBG_INIT(x...)
#पूर्ण_अगर

#घोषणा SUPERIO	"SuperIO"
#घोषणा PFX	SUPERIO ": "

अटल irqवापस_t
superio_पूर्णांकerrupt(पूर्णांक parent_irq, व्योम *devp)
अणु
	u8 results;
	u8 local_irq;

	/* Poll the 8259 to see अगर there's an पूर्णांकerrupt. */
	outb (OCW3_POLL,IC_PIC1+0);

	results = inb(IC_PIC1+0);

	/*
	 * Bit    7:	1 = active Interrupt; 0 = no Interrupt pending
	 * Bits 6-3:	zero
	 * Bits 2-0:	highest priority, active requesting पूर्णांकerrupt ID (0-7)
	 */
	अगर ((results & 0x80) == 0) अणु
		/* I suspect "spurious" पूर्णांकerrupts are from unmasking an IRQ.
		 * We करोn't know अगर an पूर्णांकerrupt was/is pending and thus
		 * just call the handler क्रम that IRQ as अगर it were pending.
		 */
		वापस IRQ_NONE;
	पूर्ण

	/* Check to see which device is पूर्णांकerrupting */
	local_irq = results & 0x0f;

	अगर (local_irq == 2 || local_irq > 7) अणु
		prपूर्णांकk(KERN_ERR PFX "slave interrupted!\n");
		वापस IRQ_HANDLED;
	पूर्ण

	अगर (local_irq == 7) अणु

		/* Could be spurious. Check in service bits */

		outb(OCW3_ISR,IC_PIC1+0);
		results = inb(IC_PIC1+0);
		अगर ((results & 0x80) == 0) अणु /* अगर ISR7 not set: spurious */
			prपूर्णांकk(KERN_WARNING PFX "spurious interrupt!\n");
			वापस IRQ_HANDLED;
		पूर्ण
	पूर्ण

	/* Call the appropriate device's पूर्णांकerrupt */
	generic_handle_irq(local_irq);

	/* set EOI - क्रमces a new पूर्णांकerrupt अगर a lower priority device
	 * still needs service.
	 */
	outb((OCW2_SEOI|local_irq),IC_PIC1 + 0);
	वापस IRQ_HANDLED;
पूर्ण

/* Initialize Super I/O device */
अटल व्योम
superio_init(काष्ठा pci_dev *pcidev)
अणु
	काष्ठा superio_device *sio = &sio_dev;
	काष्ठा pci_dev *pdev = sio->lio_pdev;
	u16 word;
	पूर्णांक ret;

	अगर (sio->suckyio_irq_enabled)
		वापस;

	BUG_ON(!pdev);
	BUG_ON(!sio->usb_pdev);

	/* use the IRQ iosapic found क्रम USB INT D... */
	pdev->irq = sio->usb_pdev->irq;

	/* ...then properly fixup the USB to poपूर्णांक at suckyio PIC */
	sio->usb_pdev->irq = superio_fixup_irq(sio->usb_pdev);

	prपूर्णांकk(KERN_INFO PFX "Found NS87560 Legacy I/O device at %s (IRQ %i)\n",
	       pci_name(pdev), pdev->irq);

	pci_पढ़ो_config_dword (pdev, SIO_SP1BAR, &sio->sp1_base);
	sio->sp1_base &= ~1;
	prपूर्णांकk(KERN_INFO PFX "Serial port 1 at 0x%x\n", sio->sp1_base);

	pci_पढ़ो_config_dword (pdev, SIO_SP2BAR, &sio->sp2_base);
	sio->sp2_base &= ~1;
	prपूर्णांकk(KERN_INFO PFX "Serial port 2 at 0x%x\n", sio->sp2_base);

	pci_पढ़ो_config_dword (pdev, SIO_PPBAR, &sio->pp_base);
	sio->pp_base &= ~1;
	prपूर्णांकk(KERN_INFO PFX "Parallel port at 0x%x\n", sio->pp_base);

	pci_पढ़ो_config_dword (pdev, SIO_FDCBAR, &sio->fdc_base);
	sio->fdc_base &= ~1;
	prपूर्णांकk(KERN_INFO PFX "Floppy controller at 0x%x\n", sio->fdc_base);
	pci_पढ़ो_config_dword (pdev, SIO_ACPIBAR, &sio->acpi_base);
	sio->acpi_base &= ~1;
	prपूर्णांकk(KERN_INFO PFX "ACPI at 0x%x\n", sio->acpi_base);

	request_region (IC_PIC1, 0x1f, "pic1");
	request_region (IC_PIC2, 0x1f, "pic2");
	request_region (sio->acpi_base, 0x1f, "acpi");

	/* Enable the legacy I/O function */
	pci_पढ़ो_config_word (pdev, PCI_COMMAND, &word);
	word |= PCI_COMMAND_SERR | PCI_COMMAND_PARITY | PCI_COMMAND_IO;
	pci_ग_लिखो_config_word (pdev, PCI_COMMAND, word);

	pci_set_master (pdev);
	ret = pci_enable_device(pdev);
	BUG_ON(ret < 0);	/* not too much we can करो about this... */

	/*
	 * Next project is programming the onboard पूर्णांकerrupt controllers.
	 * PDC hasn't done this for us, since it's using polled I/O.
	 *
	 * XXX Use dword ग_लिखोs to aव्योम bugs in Elroy or Suckyio Config
	 *     space access.  PCI is by nature a 32-bit bus and config
	 *     space can be sensitive to that.
	 */

	/* 0x64 - 0x67 :
		DMA Rtg 2
		DMA Rtg 3
		DMA Chan Ctl
		TRIGGER_1    == 0x82   USB & IDE level triggered, rest to edge
	*/
	pci_ग_लिखो_config_dword (pdev, 0x64,         0x82000000U);

	/* 0x68 - 0x6b :
		TRIGGER_2    == 0x00   all edge triggered (not used)
		CFG_IR_SER   == 0x43   SerPort1 = IRQ3, SerPort2 = IRQ4
		CFG_IR_PF    == 0x65   ParPort  = IRQ5, FloppyCtlr = IRQ6
		CFG_IR_IDE   == 0x07   IDE1 = IRQ7, reserved
	*/
	pci_ग_लिखो_config_dword (pdev, TRIGGER_2,    0x07654300U);

	/* 0x6c - 0x6f :
		CFG_IR_INTAB == 0x00
		CFG_IR_INTCD == 0x10   USB = IRQ1
		CFG_IR_PS2   == 0x00
		CFG_IR_FXBUS == 0x00
	*/
	pci_ग_लिखो_config_dword (pdev, CFG_IR_INTAB, 0x00001000U);

	/* 0x70 - 0x73 :
		CFG_IR_USB   == 0x00  not used. USB is connected to INTD.
		CFG_IR_ACPI  == 0x00  not used.
		DMA Priority == 0x4c88  Power on शेष value. NFC.
	*/
	pci_ग_लिखो_config_dword (pdev, CFG_IR_USB, 0x4c880000U);

	/* PIC1 Initialization Command Word रेजिस्टर programming */
	outb (0x11,IC_PIC1+0);	/* ICW1: ICW4 ग_लिखो req | ICW1 */
	outb (0x00,IC_PIC1+1);	/* ICW2: पूर्णांकerrupt vector table - not used */
	outb (0x04,IC_PIC1+1);	/* ICW3: Cascade */
	outb (0x01,IC_PIC1+1);	/* ICW4: x86 mode */

	/* PIC1 Program Operational Control Words */
	outb (0xff,IC_PIC1+1);	/* OCW1: Mask all पूर्णांकerrupts */
	outb (0xc2,IC_PIC1+0);  /* OCW2: priority (3-7,0-2) */

	/* PIC2 Initialization Command Word रेजिस्टर programming */
	outb (0x11,IC_PIC2+0);	/* ICW1: ICW4 ग_लिखो req | ICW1 */
	outb (0x00,IC_PIC2+1);	/* ICW2: N/A */
	outb (0x02,IC_PIC2+1);	/* ICW3: Slave ID code */
	outb (0x01,IC_PIC2+1);	/* ICW4: x86 mode */
		
	/* Program Operational Control Words */
	outb (0xff,IC_PIC1+1);	/* OCW1: Mask all पूर्णांकerrupts */
	outb (0x68,IC_PIC1+0);	/* OCW3: OCW3 select | ESMM | SMM */

	/* Write master mask reg */
	outb (0xff,IC_PIC1+1);

	/* Setup USB घातer regulation */
	outb(1, sio->acpi_base + USB_REG_CR);
	अगर (inb(sio->acpi_base + USB_REG_CR) & 1)
		prपूर्णांकk(KERN_INFO PFX "USB regulator enabled\n");
	अन्यथा
		prपूर्णांकk(KERN_ERR PFX "USB regulator not initialized!\n");

	अगर (request_irq(pdev->irq, superio_पूर्णांकerrupt, 0,
			SUPERIO, (व्योम *)sio)) अणु

		prपूर्णांकk(KERN_ERR PFX "could not get irq\n");
		BUG();
		वापस;
	पूर्ण

	sio->suckyio_irq_enabled = 1;
पूर्ण
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_NS, PCI_DEVICE_ID_NS_87560_LIO, superio_init);

अटल व्योम superio_mask_irq(काष्ठा irq_data *d)
अणु
	अचिन्हित पूर्णांक irq = d->irq;
	u8 r8;

	अगर ((irq < 1) || (irq == 2) || (irq > 7)) अणु
		prपूर्णांकk(KERN_ERR PFX "Illegal irq number.\n");
		BUG();
		वापस;
	पूर्ण

	/* Mask पूर्णांकerrupt */

	r8 = inb(IC_PIC1+1);
	r8 |= (1 << irq);
	outb (r8,IC_PIC1+1);
पूर्ण

अटल व्योम superio_unmask_irq(काष्ठा irq_data *d)
अणु
	अचिन्हित पूर्णांक irq = d->irq;
	u8 r8;

	अगर ((irq < 1) || (irq == 2) || (irq > 7)) अणु
		prपूर्णांकk(KERN_ERR PFX "Illegal irq number (%d).\n", irq);
		BUG();
		वापस;
	पूर्ण

	/* Unmask पूर्णांकerrupt */
	r8 = inb(IC_PIC1+1);
	r8 &= ~(1 << irq);
	outb (r8,IC_PIC1+1);
पूर्ण

अटल काष्ठा irq_chip superio_पूर्णांकerrupt_type = अणु
	.name		=	SUPERIO,
	.irq_unmask	=	superio_unmask_irq,
	.irq_mask	=	superio_mask_irq,
पूर्ण;

#अगर_घोषित DEBUG_SUPERIO_INIT
अटल अचिन्हित लघु expected_device[3] = अणु
	PCI_DEVICE_ID_NS_87415,
	PCI_DEVICE_ID_NS_87560_LIO,
	PCI_DEVICE_ID_NS_87560_USB
पूर्ण;
#पूर्ण_अगर

पूर्णांक superio_fixup_irq(काष्ठा pci_dev *pcidev)
अणु
	पूर्णांक local_irq, i;

#अगर_घोषित DEBUG_SUPERIO_INIT
	पूर्णांक fn;
	fn = PCI_FUNC(pcidev->devfn);

	/* Verअगरy the function number matches the expected device id. */
	अगर (expected_device[fn] != pcidev->device) अणु
		BUG();
		वापस -1;
	पूर्ण
	prपूर्णांकk(KERN_DEBUG "superio_fixup_irq(%s) ven 0x%x dev 0x%x from %ps\n",
		pci_name(pcidev),
		pcidev->venकरोr, pcidev->device,
		__builtin_वापस_address(0));
#पूर्ण_अगर

	क्रम (i = 0; i < 16; i++) अणु
		irq_set_chip_and_handler(i, &superio_पूर्णांकerrupt_type,
					 handle_simple_irq);
	पूर्ण

	/*
	 * We करोn't allocate a SuperIO irq क्रम the legacy IO function,
	 * since it is a "bridge". Instead, we will allocate irq's क्रम
	 * each legacy device as they are initialized.
	 */

	चयन(pcidev->device) अणु
	हाल PCI_DEVICE_ID_NS_87415:		/* Function 0 */
		local_irq = IDE_IRQ;
		अवरोध;
	हाल PCI_DEVICE_ID_NS_87560_LIO:	/* Function 1 */
		sio_dev.lio_pdev = pcidev;	/* save क्रम superio_init() */
		वापस -1;
	हाल PCI_DEVICE_ID_NS_87560_USB:	/* Function 2 */
		sio_dev.usb_pdev = pcidev;	/* save क्रम superio_init() */
		local_irq = USB_IRQ;
		अवरोध;
	शेष:
		local_irq = -1;
		BUG();
		अवरोध;
	पूर्ण

	वापस local_irq;
पूर्ण

अटल व्योम __init superio_serial_init(व्योम)
अणु
#अगर_घोषित CONFIG_SERIAL_8250
	पूर्णांक retval;
	काष्ठा uart_port serial_port;

	स_रखो(&serial_port, 0, माप(serial_port));
	serial_port.iotype	= UPIO_PORT;
	serial_port.type	= PORT_16550A;
	serial_port.uartclk	= 115200*16;
	serial_port.flags	= UPF_FIXED_PORT | UPF_FIXED_TYPE |
				  UPF_BOOT_AUTOCONF;

	/* serial port #1 */
	serial_port.iobase	= sio_dev.sp1_base;
	serial_port.irq		= SP1_IRQ;
	serial_port.line	= 0;
	retval = early_serial_setup(&serial_port);
	अगर (retval < 0) अणु
		prपूर्णांकk(KERN_WARNING PFX "Register Serial #0 failed.\n");
		वापस;
	पूर्ण

	/* serial port #2 */
	serial_port.iobase	= sio_dev.sp2_base;
	serial_port.irq		= SP2_IRQ;
	serial_port.line	= 1;
	retval = early_serial_setup(&serial_port);
	अगर (retval < 0)
		prपूर्णांकk(KERN_WARNING PFX "Register Serial #1 failed.\n");
#पूर्ण_अगर /* CONFIG_SERIAL_8250 */
पूर्ण


अटल व्योम __init superio_parport_init(व्योम)
अणु
#अगर_घोषित CONFIG_PARPORT_PC
	अगर (!parport_pc_probe_port(sio_dev.pp_base,
			0 /*base_hi*/,
			PAR_IRQ, 
			PARPORT_DMA_NONE /* dma */,
			शून्य /*काष्ठा pci_dev* */,
			0 /* shared irq flags */))

		prपूर्णांकk(KERN_WARNING PFX "Probing parallel port failed.\n");
#पूर्ण_अगर	/* CONFIG_PARPORT_PC */
पूर्ण


अटल व्योम superio_fixup_pci(काष्ठा pci_dev *pdev)
अणु
	u8 prog;

	pdev->class |= 0x5;
	pci_ग_लिखो_config_byte(pdev, PCI_CLASS_PROG, pdev->class);

	pci_पढ़ो_config_byte(pdev, PCI_CLASS_PROG, &prog);
	prपूर्णांकk("PCI: Enabled native mode for NS87415 (pif=0x%x)\n", prog);
पूर्ण
DECLARE_PCI_FIXUP_EARLY(PCI_VENDOR_ID_NS, PCI_DEVICE_ID_NS_87415, superio_fixup_pci);


अटल पूर्णांक __init
superio_probe(काष्ठा pci_dev *dev, स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा superio_device *sio = &sio_dev;

	/*
	** superio_probe(00:0e.0) ven 0x100b dev 0x2 sv 0x0 sd 0x0 class 0x1018a
	** superio_probe(00:0e.1) ven 0x100b dev 0xe sv 0x0 sd 0x0 class 0x68000
	** superio_probe(00:0e.2) ven 0x100b dev 0x12 sv 0x0 sd 0x0 class 0xc0310
	*/
	DBG_INIT("superio_probe(%s) ven 0x%x dev 0x%x sv 0x%x sd 0x%x class 0x%x\n",
		pci_name(dev),
		dev->venकरोr, dev->device,
		dev->subप्रणाली_venकरोr, dev->subप्रणाली_device,
		dev->class);

	BUG_ON(!sio->suckyio_irq_enabled);	/* Enabled by PCI_FIXUP_FINAL */

	अगर (dev->device == PCI_DEVICE_ID_NS_87560_LIO) अणु	/* Function 1 */
		superio_parport_init();
		superio_serial_init();
		/* REVISIT XXX : superio_fdc_init() ? */
		वापस 0;
	पूर्ण अन्यथा अगर (dev->device == PCI_DEVICE_ID_NS_87415) अणु	/* Function 0 */
		DBG_INIT("superio_probe: ignoring IDE 87415\n");
	पूर्ण अन्यथा अगर (dev->device == PCI_DEVICE_ID_NS_87560_USB) अणु	/* Function 2 */
		DBG_INIT("superio_probe: ignoring USB OHCI controller\n");
	पूर्ण अन्यथा अणु
		DBG_INIT("superio_probe: WTF? Fire Extinguisher?\n");
	पूर्ण

	/* Let appropriate other driver claim this device. */
	वापस -ENODEV;
पूर्ण

अटल स्थिर काष्ठा pci_device_id superio_tbl[] __initस्थिर = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_NS, PCI_DEVICE_ID_NS_87560_LIO) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_NS, PCI_DEVICE_ID_NS_87560_USB) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_NS, PCI_DEVICE_ID_NS_87415) पूर्ण,
	अणु 0, पूर्ण
पूर्ण;

अटल काष्ठा pci_driver superio_driver __refdata = अणु
	.name =         SUPERIO,
	.id_table =     superio_tbl,
	.probe =        superio_probe,
पूर्ण;

module_pci_driver(superio_driver);
