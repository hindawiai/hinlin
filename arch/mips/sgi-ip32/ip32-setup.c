<शैली गुरु>
/*
 * IP32 basic setup
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2000 Harald Koerfgen
 * Copyright (C) 2002, 2003, 2005 Ilya A. Volynets
 * Copyright (C) 2006 Ralf Baechle <ralf@linux-mips.org>
 */
#समावेश <linux/console.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/param.h>
#समावेश <linux/sched.h>

#समावेश <यंत्र/bootinfo.h>
#समावेश <यंत्र/mipsregs.h>
#समावेश <यंत्र/mmu_context.h>
#समावेश <यंत्र/sgialib.h>
#समावेश <यंत्र/समय.स>
#समावेश <यंत्र/traps.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/ip32/crime.h>
#समावेश <यंत्र/ip32/mace.h>
#समावेश <यंत्र/ip32/ip32_पूर्णांकs.h>

बाह्य व्योम ip32_be_init(व्योम);
बाह्य व्योम crime_init(व्योम);

#अगर_घोषित CONFIG_SGI_O2MACE_ETH
/*
 * This is taken care of in here 'cause they say using Arc later on is
 * problematic
 */
बाह्य अक्षर o2meth_eaddr[8];
अटल अंतरभूत अचिन्हित अक्षर str2hexnum(अचिन्हित अक्षर c)
अणु
	अगर (c >= '0' && c <= '9')
		वापस c - '0';
	अगर (c >= 'a' && c <= 'f')
		वापस c - 'a' + 10;
	वापस 0; /* foo */
पूर्ण

अटल अंतरभूत व्योम str2eaddr(अचिन्हित अक्षर *ea, अचिन्हित अक्षर *str)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 6; i++) अणु
		अचिन्हित अक्षर num;

		अगर(*str == ':')
			str++;
		num = str2hexnum(*str++) << 4;
		num |= (str2hexnum(*str++));
		ea[i] = num;
	पूर्ण
पूर्ण
#पूर्ण_अगर

/* An arbitrary समय; this can be decreased अगर reliability looks good */
#घोषणा WAIT_MS 10

व्योम __init plat_समय_init(व्योम)
अणु
	prपूर्णांकk(KERN_INFO "Calibrating system timer... ");
	ग_लिखो_c0_count(0);
	crime->समयr = 0;
	जबतक (crime->समयr < CRIME_MASTER_FREQ * WAIT_MS / 1000) ;
	mips_hpt_frequency = पढ़ो_c0_count() * 1000 / WAIT_MS;
	prपूर्णांकk("%d MHz CPU detected\n", mips_hpt_frequency * 2 / 1000000);
पूर्ण

व्योम __init plat_mem_setup(व्योम)
अणु
	board_be_init = ip32_be_init;

#अगर_घोषित CONFIG_SGI_O2MACE_ETH
	अणु
		अक्षर *mac = ArcGetEnvironmentVariable("eaddr");
		str2eaddr(o2meth_eaddr, mac);
	पूर्ण
#पूर्ण_अगर

#अगर defined(CONFIG_SERIAL_CORE_CONSOLE)
	अणु
		अक्षर* con = ArcGetEnvironmentVariable("console");
		अगर (con && *con == 'd') अणु
			अटल अक्षर options[8] __initdata;
			अक्षर *baud = ArcGetEnvironmentVariable("dbaud");
			अगर (baud)
				म_नकल(options, baud);
			add_preferred_console("ttyS", *(con + 1) == '2' ? 1 : 0,
					      baud ? options : शून्य);
		पूर्ण
	पूर्ण
#पूर्ण_अगर
पूर्ण
