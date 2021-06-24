<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * ip22-setup.c: SGI specअगरic setup, including init of the feature काष्ठा.
 *
 * Copyright (C) 1996 David S. Miller (davem@davemloft.net)
 * Copyright (C) 1997, 1998 Ralf Baechle (ralf@gnu.org)
 */
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/kdev_t.h>
#समावेश <linux/types.h>
#समावेश <linux/console.h>
#समावेश <linux/sched.h>
#समावेश <linux/tty.h>

#समावेश <यंत्र/addrspace.h>
#समावेश <यंत्र/bcache.h>
#समावेश <यंत्र/bootinfo.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/reboot.h>
#समावेश <यंत्र/समय.स>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/traps.h>
#समावेश <यंत्र/sgialib.h>
#समावेश <यंत्र/sgi/mc.h>
#समावेश <यंत्र/sgi/hpc3.h>
#समावेश <यंत्र/sgi/ip22.h>

बाह्य व्योम ip22_be_init(व्योम) __init;

व्योम __init plat_mem_setup(व्योम)
अणु
	अक्षर *ctype;
	अक्षर *cserial;

	board_be_init = ip22_be_init;

	/* Init the INDY HPC I/O controller.  Need to call this beक्रमe
	 * fucking with the memory controller because it needs to know the
	 * boardID and whether this is a Guiness or a FullHouse machine.
	 */
	sgihpc_init();

	/* Init INDY memory controller. */
	sgimc_init();

#अगर_घोषित CONFIG_BOARD_SCACHE
	/* Now enable boardcaches, अगर any. */
	indy_sc_init();
#पूर्ण_अगर

	/* Set EISA IO port base क्रम Indigo2
	 * ioremap cannot fail */
	set_io_port_base((अचिन्हित दीर्घ)ioremap(0x00080000,
						0x1fffffff - 0x00080000));
	/* ARCS console environment variable is set to "g?" क्रम
	 * graphics console, it is set to "d" क्रम the first serial
	 * line and "d2" क्रम the second serial line.
	 *
	 * Need to check अगर the हाल is 'g' but no keyboard:
	 * (ConsoleIn/Out = serial)
	 */
	ctype = ArcGetEnvironmentVariable("console");
	cserial = ArcGetEnvironmentVariable("ConsoleOut");

	अगर ((ctype && *ctype == 'd') || (cserial && *cserial == 's')) अणु
		अटल अक्षर options[8] __initdata;
		अक्षर *baud = ArcGetEnvironmentVariable("dbaud");
		अगर (baud)
			म_नकल(options, baud);
		add_preferred_console("ttyS", *(ctype + 1) == '2' ? 1 : 0,
				      baud ? options : शून्य);
	पूर्ण अन्यथा अगर (!ctype || *ctype != 'g') अणु
		/* Use ARC अगर we करोn't want serial ('d') or graphics ('g'). */
		prom_flags |= PROM_FLAG_USE_AS_CONSOLE;
		add_preferred_console("arc", 0, शून्य);
	पूर्ण
पूर्ण
