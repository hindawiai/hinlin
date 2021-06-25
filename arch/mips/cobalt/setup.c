<शैली गुरु>
/*
 * Setup poपूर्णांकers to hardware dependent routines.
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 1996, 1997, 2004, 05 by Ralf Baechle (ralf@linux-mips.org)
 * Copyright (C) 2001, 2002, 2003 by Liam Davies (ldavies@agile.tv)
 *
 */
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/ioport.h>
#समावेश <linux/memblock.h>
#समावेश <linux/pm.h>

#समावेश <यंत्र/bootinfo.h>
#समावेश <यंत्र/reboot.h>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/gt64120.h>

#समावेश <cobalt.h>

बाह्य व्योम cobalt_machine_restart(अक्षर *command);
बाह्य व्योम cobalt_machine_halt(व्योम);

स्थिर अक्षर *get_प्रणाली_type(व्योम)
अणु
	चयन (cobalt_board_id) अणु
		हाल COBALT_BRD_ID_QUBE1:
			वापस "Cobalt Qube";
		हाल COBALT_BRD_ID_RAQ1:
			वापस "Cobalt RaQ";
		हाल COBALT_BRD_ID_QUBE2:
			वापस "Cobalt Qube2";
		हाल COBALT_BRD_ID_RAQ2:
			वापस "Cobalt RaQ2";
	पूर्ण
	वापस "MIPS Cobalt";
पूर्ण

/*
 * Cobalt करोesn't have PS/2 keyboard/mouse पूर्णांकerfaces,
 * keyboard controller is never used.
 * Also PCI-ISA bridge DMA controller is never used.
 */
अटल काष्ठा resource cobalt_reserved_resources[] = अणु
	अणु	/* dma1 */
		.start	= 0x00,
		.end	= 0x1f,
		.name	= "reserved",
		.flags	= IORESOURCE_BUSY | IORESOURCE_IO,
	पूर्ण,
	अणु	/* keyboard */
		.start	= 0x60,
		.end	= 0x6f,
		.name	= "reserved",
		.flags	= IORESOURCE_BUSY | IORESOURCE_IO,
	पूर्ण,
	अणु	/* dma page reg */
		.start	= 0x80,
		.end	= 0x8f,
		.name	= "reserved",
		.flags	= IORESOURCE_BUSY | IORESOURCE_IO,
	पूर्ण,
	अणु	/* dma2 */
		.start	= 0xc0,
		.end	= 0xdf,
		.name	= "reserved",
		.flags	= IORESOURCE_BUSY | IORESOURCE_IO,
	पूर्ण,
पूर्ण;

व्योम __init plat_mem_setup(व्योम)
अणु
	पूर्णांक i;

	_machine_restart = cobalt_machine_restart;
	_machine_halt = cobalt_machine_halt;
	pm_घातer_off = cobalt_machine_halt;

	set_io_port_base(CKSEG1ADDR(GT_DEF_PCI0_IO_BASE));

	/* I/O port resource */
	ioport_resource.end = 0x01ffffff;

	/* These resources have been reserved by VIA SuperI/O chip. */
	क्रम (i = 0; i < ARRAY_SIZE(cobalt_reserved_resources); i++)
		request_resource(&ioport_resource, cobalt_reserved_resources + i);
पूर्ण

/*
 * Prom init. We पढ़ो our one and only communication with the firmware.
 * Grab the amount of installed memory.
 * Better boot loaders (CoLo) pass a command line too :-)
 */

व्योम __init prom_init(व्योम)
अणु
	अचिन्हित दीर्घ memsz;
	पूर्णांक argc, i;
	अक्षर **argv;

	memsz = fw_arg0 & 0x7fff0000;
	argc = fw_arg0 & 0x0000ffff;
	argv = (अक्षर **)fw_arg1;

	क्रम (i = 1; i < argc; i++) अणु
		strlcat(arcs_cmdline, argv[i], COMMAND_LINE_SIZE);
		अगर (i < (argc - 1))
			strlcat(arcs_cmdline, " ", COMMAND_LINE_SIZE);
	पूर्ण

	memblock_add(0, memsz);

	setup_8250_early_prपूर्णांकk_port(CKSEG1ADDR(0x1c800000), 0, 0);
पूर्ण
