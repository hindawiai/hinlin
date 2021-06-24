<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/console.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/माला.स>
#समावेश <linux/screen_info.h>
#समावेश <linux/usb/ch9.h>
#समावेश <linux/pci_regs.h>
#समावेश <linux/pci_ids.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/pgtable.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/fcntl.h>
#समावेश <यंत्र/setup.h>
#समावेश <xen/hvc-console.h>
#समावेश <यंत्र/pci-direct.h>
#समावेश <यंत्र/fixmap.h>
#समावेश <linux/usb/ehci_def.h>
#समावेश <linux/usb/xhci-dbgp.h>
#समावेश <यंत्र/pci_x86.h>

/* Simple VGA output */
#घोषणा VGABASE		(__ISA_IO_base + 0xb8000)

अटल पूर्णांक max_ypos = 25, max_xpos = 80;
अटल पूर्णांक current_ypos = 25, current_xpos;

अटल व्योम early_vga_ग_लिखो(काष्ठा console *con, स्थिर अक्षर *str, अचिन्हित n)
अणु
	अक्षर c;
	पूर्णांक  i, k, j;

	जबतक ((c = *str++) != '\0' && n-- > 0) अणु
		अगर (current_ypos >= max_ypos) अणु
			/* scroll 1 line up */
			क्रम (k = 1, j = 0; k < max_ypos; k++, j++) अणु
				क्रम (i = 0; i < max_xpos; i++) अणु
					ग_लिखोw(पढ़ोw(VGABASE+2*(max_xpos*k+i)),
					       VGABASE + 2*(max_xpos*j + i));
				पूर्ण
			पूर्ण
			क्रम (i = 0; i < max_xpos; i++)
				ग_लिखोw(0x720, VGABASE + 2*(max_xpos*j + i));
			current_ypos = max_ypos-1;
		पूर्ण
#अगर_घोषित CONFIG_KGDB_KDB
		अगर (c == '\b') अणु
			अगर (current_xpos > 0)
				current_xpos--;
		पूर्ण अन्यथा अगर (c == '\r') अणु
			current_xpos = 0;
		पूर्ण अन्यथा
#पूर्ण_अगर
		अगर (c == '\n') अणु
			current_xpos = 0;
			current_ypos++;
		पूर्ण अन्यथा अगर (c != '\r')  अणु
			ग_लिखोw(((0x7 << 8) | (अचिन्हित लघु) c),
			       VGABASE + 2*(max_xpos*current_ypos +
						current_xpos++));
			अगर (current_xpos >= max_xpos) अणु
				current_xpos = 0;
				current_ypos++;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल काष्ठा console early_vga_console = अणु
	.name =		"earlyvga",
	.ग_लिखो =	early_vga_ग_लिखो,
	.flags =	CON_PRINTBUFFER,
	.index =	-1,
पूर्ण;

/* Serial functions loosely based on a similar package from Klaus P. Gerlicher */

अटल अचिन्हित दीर्घ early_serial_base = 0x3f8;  /* ttyS0 */

#घोषणा XMTRDY          0x20

#घोषणा DLAB		0x80

#घोषणा TXR             0       /*  Transmit रेजिस्टर (WRITE) */
#घोषणा RXR             0       /*  Receive रेजिस्टर  (READ)  */
#घोषणा IER             1       /*  Interrupt Enable          */
#घोषणा IIR             2       /*  Interrupt ID              */
#घोषणा FCR             2       /*  FIFO control              */
#घोषणा LCR             3       /*  Line control              */
#घोषणा MCR             4       /*  Modem control             */
#घोषणा LSR             5       /*  Line Status               */
#घोषणा MSR             6       /*  Modem Status              */
#घोषणा DLL             0       /*  Divisor Latch Low         */
#घोषणा DLH             1       /*  Divisor latch High        */

अटल अचिन्हित पूर्णांक io_serial_in(अचिन्हित दीर्घ addr, पूर्णांक offset)
अणु
	वापस inb(addr + offset);
पूर्ण

अटल व्योम io_serial_out(अचिन्हित दीर्घ addr, पूर्णांक offset, पूर्णांक value)
अणु
	outb(value, addr + offset);
पूर्ण

अटल अचिन्हित पूर्णांक (*serial_in)(अचिन्हित दीर्घ addr, पूर्णांक offset) = io_serial_in;
अटल व्योम (*serial_out)(अचिन्हित दीर्घ addr, पूर्णांक offset, पूर्णांक value) = io_serial_out;

अटल पूर्णांक early_serial_अ_दो(अचिन्हित अक्षर ch)
अणु
	अचिन्हित समयout = 0xffff;

	जबतक ((serial_in(early_serial_base, LSR) & XMTRDY) == 0 && --समयout)
		cpu_relax();
	serial_out(early_serial_base, TXR, ch);
	वापस समयout ? 0 : -1;
पूर्ण

अटल व्योम early_serial_ग_लिखो(काष्ठा console *con, स्थिर अक्षर *s, अचिन्हित n)
अणु
	जबतक (*s && n-- > 0) अणु
		अगर (*s == '\n')
			early_serial_अ_दो('\r');
		early_serial_अ_दो(*s);
		s++;
	पूर्ण
पूर्ण

अटल __init व्योम early_serial_hw_init(अचिन्हित भागisor)
अणु
	अचिन्हित अक्षर c;

	serial_out(early_serial_base, LCR, 0x3);	/* 8n1 */
	serial_out(early_serial_base, IER, 0);	/* no पूर्णांकerrupt */
	serial_out(early_serial_base, FCR, 0);	/* no fअगरo */
	serial_out(early_serial_base, MCR, 0x3);	/* DTR + RTS */

	c = serial_in(early_serial_base, LCR);
	serial_out(early_serial_base, LCR, c | DLAB);
	serial_out(early_serial_base, DLL, भागisor & 0xff);
	serial_out(early_serial_base, DLH, (भागisor >> 8) & 0xff);
	serial_out(early_serial_base, LCR, c & ~DLAB);
पूर्ण

#घोषणा DEFAULT_BAUD 9600

अटल __init व्योम early_serial_init(अक्षर *s)
अणु
	अचिन्हित भागisor;
	अचिन्हित दीर्घ baud = DEFAULT_BAUD;
	अक्षर *e;

	अगर (*s == ',')
		++s;

	अगर (*s) अणु
		अचिन्हित port;
		अगर (!म_भेदन(s, "0x", 2)) अणु
			early_serial_base = simple_म_से_अदीर्घ(s, &e, 16);
		पूर्ण अन्यथा अणु
			अटल स्थिर पूर्णांक __initस्थिर bases[] = अणु 0x3f8, 0x2f8 पूर्ण;

			अगर (!म_भेदन(s, "ttyS", 4))
				s += 4;
			port = simple_म_से_अदीर्घ(s, &e, 10);
			अगर (port > 1 || s == e)
				port = 0;
			early_serial_base = bases[port];
		पूर्ण
		s += म_खोज(s, ",");
		अगर (*s == ',')
			s++;
	पूर्ण

	अगर (*s) अणु
		baud = simple_म_से_अदीर्घl(s, &e, 0);

		अगर (baud == 0 || s == e)
			baud = DEFAULT_BAUD;
	पूर्ण

	/* Convert from baud to भागisor value */
	भागisor = 115200 / baud;

	/* These will always be IO based ports */
	serial_in = io_serial_in;
	serial_out = io_serial_out;

	/* Set up the HW */
	early_serial_hw_init(भागisor);
पूर्ण

#अगर_घोषित CONFIG_PCI
अटल व्योम mem32_serial_out(अचिन्हित दीर्घ addr, पूर्णांक offset, पूर्णांक value)
अणु
	u32 __iomem *vaddr = (u32 __iomem *)addr;
	/* shअगरt implied by poपूर्णांकer type */
	ग_लिखोl(value, vaddr + offset);
पूर्ण

अटल अचिन्हित पूर्णांक mem32_serial_in(अचिन्हित दीर्घ addr, पूर्णांक offset)
अणु
	u32 __iomem *vaddr = (u32 __iomem *)addr;
	/* shअगरt implied by poपूर्णांकer type */
	वापस पढ़ोl(vaddr + offset);
पूर्ण

/*
 * early_pci_serial_init()
 *
 * This function is invoked when the early_prपूर्णांकk param starts with "pciserial"
 * The rest of the param should be "[force],B:D.F,baud", where B, D & F describe
 * the location of a PCI device that must be a UART device. "force" is optional
 * and overrides the use of an UART device with a wrong PCI class code.
 */
अटल __init व्योम early_pci_serial_init(अक्षर *s)
अणु
	अचिन्हित भागisor;
	अचिन्हित दीर्घ baud = DEFAULT_BAUD;
	u8 bus, slot, func;
	u32 classcode, bar0;
	u16 cmdreg;
	अक्षर *e;
	पूर्णांक क्रमce = 0;

	अगर (*s == ',')
		++s;

	अगर (*s == 0)
		वापस;

	/* Force the use of an UART device with wrong class code */
	अगर (!म_भेदन(s, "force,", 6)) अणु
		क्रमce = 1;
		s += 6;
	पूर्ण

	/*
	 * Part the param to get the BDF values
	 */
	bus = (u8)simple_म_से_अदीर्घ(s, &e, 16);
	s = e;
	अगर (*s != ':')
		वापस;
	++s;
	slot = (u8)simple_म_से_अदीर्घ(s, &e, 16);
	s = e;
	अगर (*s != '.')
		वापस;
	++s;
	func = (u8)simple_म_से_अदीर्घ(s, &e, 16);
	s = e;

	/* A baud might be following */
	अगर (*s == ',')
		s++;

	/*
	 * Find the device from the BDF
	 */
	cmdreg = पढ़ो_pci_config(bus, slot, func, PCI_COMMAND);
	classcode = पढ़ो_pci_config(bus, slot, func, PCI_CLASS_REVISION);
	bar0 = पढ़ो_pci_config(bus, slot, func, PCI_BASE_ADDRESS_0);

	/*
	 * Verअगरy it is a UART type device
	 */
	अगर (((classcode >> 16 != PCI_CLASS_COMMUNICATION_MODEM) &&
	     (classcode >> 16 != PCI_CLASS_COMMUNICATION_SERIAL)) ||
	   (((classcode >> 8) & 0xff) != 0x02)) /* 16550 I/F at BAR0 */ अणु
		अगर (!क्रमce)
			वापस;
	पूर्ण

	/*
	 * Determine अगर it is IO or memory mapped
	 */
	अगर (bar0 & 0x01) अणु
		/* it is IO mapped */
		serial_in = io_serial_in;
		serial_out = io_serial_out;
		early_serial_base = bar0&0xfffffffc;
		ग_लिखो_pci_config(bus, slot, func, PCI_COMMAND,
						cmdreg|PCI_COMMAND_IO);
	पूर्ण अन्यथा अणु
		/* It is memory mapped - assume 32-bit alignment */
		serial_in = mem32_serial_in;
		serial_out = mem32_serial_out;
		/* WARNING! assuming the address is always in the first 4G */
		early_serial_base =
			(अचिन्हित दीर्घ)early_ioremap(bar0 & 0xfffffff0, 0x10);
		ग_लिखो_pci_config(bus, slot, func, PCI_COMMAND,
						cmdreg|PCI_COMMAND_MEMORY);
	पूर्ण

	/*
	 * Initialize the hardware
	 */
	अगर (*s) अणु
		अगर (म_भेद(s, "nocfg") == 0)
			/* Someबार, we want to leave the UART alone
			 * and assume the BIOS has set it up correctly.
			 * "nocfg" tells us this is the हाल, and we
			 * should करो no more setup.
			 */
			वापस;
		अगर (kम_से_अदीर्घ(s, 0, &baud) < 0 || baud == 0)
			baud = DEFAULT_BAUD;
	पूर्ण

	/* Convert from baud to भागisor value */
	भागisor = 115200 / baud;

	/* Set up the HW */
	early_serial_hw_init(भागisor);
पूर्ण
#पूर्ण_अगर

अटल काष्ठा console early_serial_console = अणु
	.name =		"earlyser",
	.ग_लिखो =	early_serial_ग_लिखो,
	.flags =	CON_PRINTBUFFER,
	.index =	-1,
पूर्ण;

अटल व्योम early_console_रेजिस्टर(काष्ठा console *con, पूर्णांक keep_early)
अणु
	अगर (con->index != -1) अणु
		prपूर्णांकk(KERN_CRIT "ERROR: earlyprintk= %s already used\n",
		       con->name);
		वापस;
	पूर्ण
	early_console = con;
	अगर (keep_early)
		early_console->flags &= ~CON_BOOT;
	अन्यथा
		early_console->flags |= CON_BOOT;
	रेजिस्टर_console(early_console);
पूर्ण

अटल पूर्णांक __init setup_early_prपूर्णांकk(अक्षर *buf)
अणु
	पूर्णांक keep;

	अगर (!buf)
		वापस 0;

	अगर (early_console)
		वापस 0;

	keep = (म_माला(buf, "keep") != शून्य);

	जबतक (*buf != '\0') अणु
		अगर (!म_भेदन(buf, "serial", 6)) अणु
			buf += 6;
			early_serial_init(buf);
			early_console_रेजिस्टर(&early_serial_console, keep);
			अगर (!म_भेदन(buf, ",ttyS", 5))
				buf += 5;
		पूर्ण
		अगर (!म_भेदन(buf, "ttyS", 4)) अणु
			early_serial_init(buf + 4);
			early_console_रेजिस्टर(&early_serial_console, keep);
		पूर्ण
#अगर_घोषित CONFIG_PCI
		अगर (!म_भेदन(buf, "pciserial", 9)) अणु
			early_pci_serial_init(buf + 9);
			early_console_रेजिस्टर(&early_serial_console, keep);
			buf += 9; /* Keep from match the above "serial" */
		पूर्ण
#पूर्ण_अगर
		अगर (!म_भेदन(buf, "vga", 3) &&
		    boot_params.screen_info.orig_video_isVGA == 1) अणु
			max_xpos = boot_params.screen_info.orig_video_cols;
			max_ypos = boot_params.screen_info.orig_video_lines;
			current_ypos = boot_params.screen_info.orig_y;
			early_console_रेजिस्टर(&early_vga_console, keep);
		पूर्ण
#अगर_घोषित CONFIG_EARLY_PRINTK_DBGP
		अगर (!म_भेदन(buf, "dbgp", 4) && !early_dbgp_init(buf + 4))
			early_console_रेजिस्टर(&early_dbgp_console, keep);
#पूर्ण_अगर
#अगर_घोषित CONFIG_HVC_XEN
		अगर (!म_भेदन(buf, "xen", 3))
			early_console_रेजिस्टर(&xenboot_console, keep);
#पूर्ण_अगर
#अगर_घोषित CONFIG_EARLY_PRINTK_USB_XDBC
		अगर (!म_भेदन(buf, "xdbc", 4))
			early_xdbc_parse_parameter(buf + 4);
#पूर्ण_अगर

		buf++;
	पूर्ण
	वापस 0;
पूर्ण

early_param("earlyprintk", setup_early_prपूर्णांकk);
