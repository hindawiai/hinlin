<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/console.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/माला.स>

#समावेश "console_cmdline.h"
#समावेश "braille.h"

पूर्णांक _braille_console_setup(अक्षर **str, अक्षर **brl_options)
अणु
	माप_प्रकार len;

	len = str_has_prefix(*str, "brl,");
	अगर (len) अणु
		*brl_options = "";
		*str += len;
		वापस 0;
	पूर्ण

	len = str_has_prefix(*str, "brl=");
	अगर (len) अणु
		*brl_options = *str + len;
		*str = म_अक्षर(*brl_options, ',');
		अगर (!*str) अणु
			pr_err("need port name after brl=\n");
			वापस -EINVAL;
		पूर्ण
		*((*str)++) = 0;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक
_braille_रेजिस्टर_console(काष्ठा console *console, काष्ठा console_cmdline *c)
अणु
	पूर्णांक rtn = 0;

	अगर (c->brl_options) अणु
		console->flags |= CON_BRL;
		rtn = braille_रेजिस्टर_console(console, c->index, c->options,
					       c->brl_options);
	पूर्ण

	वापस rtn;
पूर्ण

पूर्णांक
_braille_unरेजिस्टर_console(काष्ठा console *console)
अणु
	अगर (console->flags & CON_BRL)
		वापस braille_unरेजिस्टर_console(console);

	वापस 0;
पूर्ण
