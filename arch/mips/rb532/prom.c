<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  RouterBoard 500 specअगरic prom routines
 *
 *  Copyright (C) 2003, Peter Sadik <peter.sadik@idt.com>
 *  Copyright (C) 2005-2006, P.Christeas <p_christ@hol.gr>
 *  Copyright (C) 2007, Gabor Juhos <juhosg@खोलोwrt.org>
 *			Felix Fietkau <nbd@खोलोwrt.org>
 *			Florian Fainelli <florian@खोलोwrt.org>
 */

#समावेश <linux/init.h>
#समावेश <linux/mm.h>
#समावेश <linux/export.h>
#समावेश <linux/माला.स>
#समावेश <linux/console.h>
#समावेश <linux/memblock.h>
#समावेश <linux/ioport.h>
#समावेश <linux/blkdev.h>

#समावेश <यंत्र/bootinfo.h>
#समावेश <यंत्र/mach-rc32434/ddr.h>
#समावेश <यंत्र/mach-rc32434/prom.h>

अचिन्हित पूर्णांक idt_cpu_freq = 132000000;
EXPORT_SYMBOL(idt_cpu_freq);

अटल काष्ठा resource ddr_reg[] = अणु
	अणु
		.name = "ddr-reg",
		.start = DDR0_PHYS_ADDR,
		.end = DDR0_PHYS_ADDR + माप(काष्ठा ddr_ram),
		.flags = IORESOURCE_MEM,
	पूर्ण
पूर्ण;

अटल अंतरभूत पूर्णांक match_tag(अक्षर *arg, स्थिर अक्षर *tag)
अणु
	वापस म_भेदन(arg, tag, म_माप(tag)) == 0;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ tag2ul(अक्षर *arg, स्थिर अक्षर *tag)
अणु
	अक्षर *num;

	num = arg + म_माप(tag);
	वापस simple_म_से_अदीर्घ(num, 0, 10);
पूर्ण

व्योम __init prom_setup_cmdline(व्योम)
अणु
	अटल अक्षर cmd_line[COMMAND_LINE_SIZE] __initdata;
	अक्षर *cp, *board;
	पूर्णांक prom_argc;
	अक्षर **prom_argv;
	पूर्णांक i;

	prom_argc = fw_arg0;
	prom_argv = (अक्षर **) fw_arg1;

	cp = cmd_line;
		/* Note: it is common that parameters start
		 * at argv[1] and not argv[0],
		 * however, our elf loader starts at [0] */
	क्रम (i = 0; i < prom_argc; i++) अणु
		अगर (match_tag(prom_argv[i], FREQ_TAG)) अणु
			idt_cpu_freq = tag2ul(prom_argv[i], FREQ_TAG);
			जारी;
		पूर्ण
#अगर_घोषित IGNORE_CMDLINE_MEM
		/* parses out the "mem=xx" arg */
		अगर (match_tag(prom_argv[i], MEM_TAG))
			जारी;
#पूर्ण_अगर
		अगर (i > 0)
			*(cp++) = ' ';
		अगर (match_tag(prom_argv[i], BOARD_TAG)) अणु
			board = prom_argv[i] + म_माप(BOARD_TAG);

			अगर (match_tag(board, BOARD_RB532A))
				mips_machtype = MACH_MIKROTIK_RB532A;
			अन्यथा
				mips_machtype = MACH_MIKROTIK_RB532;
		पूर्ण

		म_नकल(cp, prom_argv[i]);
		cp += म_माप(prom_argv[i]);
	पूर्ण
	*(cp++) = ' ';

	i = म_माप(arcs_cmdline);
	अगर (i > 0) अणु
		*(cp++) = ' ';
		म_नकल(cp, arcs_cmdline);
		cp += म_माप(arcs_cmdline);
	पूर्ण
	cmd_line[COMMAND_LINE_SIZE - 1] = '\0';

	म_नकल(arcs_cmdline, cmd_line);
पूर्ण

व्योम __init prom_init(व्योम)
अणु
	काष्ठा ddr_ram __iomem *ddr;
	phys_addr_t memsize;
	phys_addr_t ddrbase;

	ddr = ioremap(ddr_reg[0].start,
			ddr_reg[0].end - ddr_reg[0].start);

	अगर (!ddr) अणु
		prपूर्णांकk(KERN_ERR "Unable to remap DDR register\n");
		वापस;
	पूर्ण

	ddrbase = (phys_addr_t)&ddr->ddrbase;
	memsize = (phys_addr_t)&ddr->ddrmask;
	memsize = 0 - memsize;

	prom_setup_cmdline();

	/* give all RAM to boot allocator,
	 * except क्रम the first 0x400 and the last 0x200 bytes */
	memblock_add(ddrbase + 0x400, memsize - 0x600);
पूर्ण
