<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Wrap-around code क्रम a console using the
 * ARC io-routines.
 *
 * Copyright (c) 1998 Harald Koerfgen
 * Copyright (c) 2001 Ralf Baechle
 * Copyright (c) 2002 Thiemo Seufer
 */
#समावेश <linux/tty.h>
#समावेश <linux/major.h>
#समावेश <linux/init.h>
#समावेश <linux/console.h>
#समावेश <linux/fs.h>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/sgialib.h>

अटल व्योम prom_console_ग_लिखो(काष्ठा console *co, स्थिर अक्षर *s,
			       अचिन्हित count)
अणु
	/* Do each अक्षरacter */
	जबतक (count--) अणु
		अगर (*s == '\n')
			prom_अक्षर_दो('\r');
		prom_अक्षर_दो(*s++);
	पूर्ण
पूर्ण

अटल पूर्णांक prom_console_setup(काष्ठा console *co, अक्षर *options)
अणु
	अगर (prom_flags & PROM_FLAG_USE_AS_CONSOLE)
		वापस 0;
	वापस -ENODEV;
पूर्ण

अटल काष्ठा console arc_cons = अणु
	.name		= "arc",
	.ग_लिखो		= prom_console_ग_लिखो,
	.setup		= prom_console_setup,
	.flags		= CON_PRINTBUFFER,
	.index		= -1,
पूर्ण;

/*
 *    Register console.
 */

अटल पूर्णांक __init arc_console_init(व्योम)
अणु
	रेजिस्टर_console(&arc_cons);

	वापस 0;
पूर्ण
console_initcall(arc_console_init);
