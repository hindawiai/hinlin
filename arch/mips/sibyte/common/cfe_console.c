<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/init.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/console.h>

#समावेश <यंत्र/sibyte/board.h>

#समावेश <यंत्र/fw/cfe/cfe_api.h>
#समावेश <यंत्र/fw/cfe/cfe_error.h>

बाह्य पूर्णांक cfe_cons_handle;

अटल व्योम cfe_console_ग_लिखो(काष्ठा console *cons, स्थिर अक्षर *str,
		       अचिन्हित पूर्णांक count)
अणु
	पूर्णांक i, last, written;

	क्रम (i=0, last=0; i<count; i++) अणु
		अगर (!str[i])
			/* XXXKW can/should this ever happen? */
			वापस;
		अगर (str[i] == '\n') अणु
			करो अणु
				written = cfe_ग_लिखो(cfe_cons_handle, &str[last], i-last);
				अगर (written < 0)
					;
				last += written;
			पूर्ण जबतक (last < i);
			जबतक (cfe_ग_लिखो(cfe_cons_handle, "\r", 1) <= 0)
				;
		पूर्ण
	पूर्ण
	अगर (last != count) अणु
		करो अणु
			written = cfe_ग_लिखो(cfe_cons_handle, &str[last], count-last);
			अगर (written < 0)
				;
			last += written;
		पूर्ण जबतक (last < count);
	पूर्ण

पूर्ण

अटल पूर्णांक cfe_console_setup(काष्ठा console *cons, अक्षर *str)
अणु
	अक्षर consdev[32];
	/* XXXKW think about पूर्णांकeraction with 'console=' cmdline arg */
	/* If none of the console options are configured, the build will अवरोध. */
	अगर (cfe_दो_पर्या("BOOT_CONSOLE", consdev, 32) >= 0) अणु
#अगर_घोषित CONFIG_SERIAL_SB1250_DUART
		अगर (!म_भेद(consdev, "uart0")) अणु
			setleds("u0cn");
		पूर्ण अन्यथा अगर (!म_भेद(consdev, "uart1")) अणु
			setleds("u1cn");
		पूर्ण अन्यथा
#पूर्ण_अगर
#अगर_घोषित CONFIG_VGA_CONSOLE
		       अगर (!म_भेद(consdev, "pcconsole0")) अणु
				setleds("pccn");
		पूर्ण अन्यथा
#पूर्ण_अगर
			वापस -ENODEV;
	पूर्ण
	वापस 0;
पूर्ण

अटल काष्ठा console sb1250_cfe_cons = अणु
	.name		= "cfe",
	.ग_लिखो		= cfe_console_ग_लिखो,
	.setup		= cfe_console_setup,
	.flags		= CON_PRINTBUFFER,
	.index		= -1,
पूर्ण;

अटल पूर्णांक __init sb1250_cfe_console_init(व्योम)
अणु
	रेजिस्टर_console(&sb1250_cfe_cons);
	वापस 0;
पूर्ण

console_initcall(sb1250_cfe_console_init);
