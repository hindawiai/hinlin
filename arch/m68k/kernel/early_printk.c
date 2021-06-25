<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (c) 2014 Finn Thain
 */

#समावेश <linux/kernel.h>
#समावेश <linux/console.h>
#समावेश <linux/init.h>
#समावेश <linux/माला.स>
#समावेश <यंत्र/setup.h>

बाह्य व्योम mvme16x_cons_ग_लिखो(काष्ठा console *co,
			       स्थिर अक्षर *str, अचिन्हित count);

यंत्रlinkage व्योम __init debug_cons_nमाला_दो(स्थिर अक्षर *s, अचिन्हित n);

अटल व्योम __ref debug_cons_ग_लिखो(काष्ठा console *c,
				   स्थिर अक्षर *s, अचिन्हित n)
अणु
#अगर !(defined(CONFIG_SUN3) || defined(CONFIG_M68000) || \
      defined(CONFIG_COLDFIRE))
	अगर (MACH_IS_MVME16x)
		mvme16x_cons_ग_लिखो(c, s, n);
	अन्यथा
		debug_cons_nमाला_दो(s, n);
#पूर्ण_अगर
पूर्ण

अटल काष्ठा console early_console_instance = अणु
	.name  = "debug",
	.ग_लिखो = debug_cons_ग_लिखो,
	.flags = CON_PRINTBUFFER | CON_BOOT,
	.index = -1
पूर्ण;

अटल पूर्णांक __init setup_early_prपूर्णांकk(अक्षर *buf)
अणु
	अगर (early_console || buf)
		वापस 0;

	early_console = &early_console_instance;
	रेजिस्टर_console(early_console);

	वापस 0;
पूर्ण
early_param("earlyprintk", setup_early_prपूर्णांकk);

/*
 * debug_cons_nमाला_दो() defined in arch/m68k/kernel/head.S cannot be called
 * after init sections are discarded (क्रम platक्रमms that use it).
 */
#अगर !(defined(CONFIG_SUN3) || defined(CONFIG_M68000) || \
      defined(CONFIG_COLDFIRE))

अटल पूर्णांक __init unरेजिस्टर_early_console(व्योम)
अणु
	अगर (!early_console || MACH_IS_MVME16x)
		वापस 0;

	वापस unरेजिस्टर_console(early_console);
पूर्ण
late_initcall(unरेजिस्टर_early_console);

#पूर्ण_अगर
