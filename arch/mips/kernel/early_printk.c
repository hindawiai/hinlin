<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2002, 2003, 06, 07 Ralf Baechle (ralf@linux-mips.org)
 * Copyright (C) 2007 MIPS Technologies, Inc.
 *   written by Ralf Baechle (ralf@linux-mips.org)
 */
#समावेश <linux/kernel.h>
#समावेश <linux/console.h>
#समावेश <linux/prपूर्णांकk.h>
#समावेश <linux/init.h>

#समावेश <यंत्र/setup.h>

अटल व्योम early_console_ग_लिखो(काष्ठा console *con, स्थिर अक्षर *s, अचिन्हित n)
अणु
	जबतक (n-- && *s) अणु
		अगर (*s == '\n')
			prom_अक्षर_दो('\r');
		prom_अक्षर_दो(*s);
		s++;
	पूर्ण
पूर्ण

अटल काष्ठा console early_console_prom = अणु
	.name	= "early",
	.ग_लिखो	= early_console_ग_लिखो,
	.flags	= CON_PRINTBUFFER | CON_BOOT,
	.index	= -1
पूर्ण;

व्योम __init setup_early_prपूर्णांकk(व्योम)
अणु
	अगर (early_console)
		वापस;
	early_console = &early_console_prom;

	रेजिस्टर_console(&early_console_prom);
पूर्ण
