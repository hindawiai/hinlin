<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/console.h>

#समावेश "chan_user.h"

/* ----------------------------------------------------------------------------- */
/* trivial console driver -- simply dump everything to मानक_त्रुटि                    */

/*
 * Don't रेजिस्टर by शेष -- as this रेजिस्टरs very early in the
 * boot process it becomes the शेष console.
 *
 * Initialized at init समय.
 */
अटल पूर्णांक use_मानक_त्रुटि_console = 0;

अटल व्योम मानक_त्रुटि_console_ग_लिखो(काष्ठा console *console, स्थिर अक्षर *string,
				 अचिन्हित len)
अणु
	generic_ग_लिखो(2 /* मानक_त्रुटि */, string, len, शून्य);
पूर्ण

अटल काष्ठा console मानक_त्रुटि_console = अणु
	.name		= "stderr",
	.ग_लिखो		= मानक_त्रुटि_console_ग_लिखो,
	.flags		= CON_PRINTBUFFER,
पूर्ण;

अटल पूर्णांक __init मानक_त्रुटि_console_init(व्योम)
अणु
	अगर (use_मानक_त्रुटि_console)
		रेजिस्टर_console(&मानक_त्रुटि_console);
	वापस 0;
पूर्ण
console_initcall(मानक_त्रुटि_console_init);

अटल पूर्णांक मानक_त्रुटि_setup(अक्षर *str)
अणु
	अगर (!str)
		वापस 0;
	use_मानक_त्रुटि_console = simple_म_से_अदीर्घ(str,&str,0);
	वापस 1;
पूर्ण
__setup("stderr=", मानक_त्रुटि_setup);

/* The previous behavior of not unरेजिस्टरing led to /dev/console being
 * impossible to खोलो.  My FC5 fileप्रणाली started having init die, and the
 * प्रणाली panicing because of this.  Unरेजिस्टरing causes the real
 * console to become the शेष console, and /dev/console can then be
 * खोलोed.  Making this an initcall makes this happen late enough that
 * there is no added value in dumping everything to मानक_त्रुटि, and the
 * normal console is good enough to show you all available output.
 */
अटल पूर्णांक __init unरेजिस्टर_मानक_त्रुटि(व्योम)
अणु
	unरेजिस्टर_console(&मानक_त्रुटि_console);

	वापस 0;
पूर्ण

__initcall(unरेजिस्टर_मानक_त्रुटि);
