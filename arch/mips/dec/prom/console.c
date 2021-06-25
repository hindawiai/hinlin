<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *	DECstation PROM-based early console support.
 *
 *	Copyright (C) 2004, 2007  Maciej W. Rozycki
 */
#समावेश <linux/console.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>

#समावेश <यंत्र/dec/prom.h>

अटल व्योम __init prom_console_ग_लिखो(काष्ठा console *con, स्थिर अक्षर *s,
				      अचिन्हित पूर्णांक c)
अणु
	अक्षर buf[81];
	अचिन्हित पूर्णांक chunk = माप(buf) - 1;

	जबतक (c > 0) अणु
		अगर (chunk > c)
			chunk = c;
		स_नकल(buf, s, chunk);
		buf[chunk] = '\0';
		prom_म_लिखो("%s", buf);
		s += chunk;
		c -= chunk;
	पूर्ण
पूर्ण

अटल काष्ठा console promcons __initdata = अणु
	.name	= "prom",
	.ग_लिखो	= prom_console_ग_लिखो,
	.flags	= CON_BOOT | CON_PRINTBUFFER,
	.index	= -1,
पूर्ण;

व्योम __init रेजिस्टर_prom_console(व्योम)
अणु
	रेजिस्टर_console(&promcons);
पूर्ण
