<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/arch/arm/kernel/early_prपूर्णांकk.c
 *
 *  Copyright (C) 2009 Sascha Hauer <s.hauer@pengutronix.de>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/console.h>
#समावेश <linux/init.h>
#समावेश <linux/माला.स>

बाह्य व्योम prपूर्णांकascii(स्थिर अक्षर *);

अटल व्योम early_ग_लिखो(स्थिर अक्षर *s, अचिन्हित n)
अणु
	अक्षर buf[128];
	जबतक (n) अणु
		अचिन्हित l = min(n, माप(buf)-1);
		स_नकल(buf, s, l);
		buf[l] = 0;
		s += l;
		n -= l;
		prपूर्णांकascii(buf);
	पूर्ण
पूर्ण

अटल व्योम early_console_ग_लिखो(काष्ठा console *con, स्थिर अक्षर *s, अचिन्हित n)
अणु
	early_ग_लिखो(s, n);
पूर्ण

अटल काष्ठा console early_console_dev = अणु
	.name =		"earlycon",
	.ग_लिखो =	early_console_ग_लिखो,
	.flags =	CON_PRINTBUFFER | CON_BOOT,
	.index =	-1,
पूर्ण;

अटल पूर्णांक __init setup_early_prपूर्णांकk(अक्षर *buf)
अणु
	early_console = &early_console_dev;
	रेजिस्टर_console(&early_console_dev);
	वापस 0;
पूर्ण

early_param("earlyprintk", setup_early_prपूर्णांकk);
