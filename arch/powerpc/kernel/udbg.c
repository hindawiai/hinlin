<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * polling mode stateless debugging stuff, originally क्रम NS16550 Serial Ports
 *
 * c 2001 PPC 64 Team, IBM Corp
 */

#समावेश <मानकतर्क.स>
#समावेश <linux/types.h>
#समावेश <linux/sched.h>
#समावेश <linux/console.h>
#समावेश <linux/init.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/udbg.h>

व्योम (*udbg_अ_दो)(अक्षर c);
व्योम (*udbg_flush)(व्योम);
पूर्णांक (*udbg_अ_लो)(व्योम);
पूर्णांक (*udbg_अ_लो_poll)(व्योम);

/*
 * Early debugging facilities. You can enable _one_ of these via .config,
 * अगर you करो so your kernel _will not boot_ on anything अन्यथा. Be careful.
 */
व्योम __init udbg_early_init(व्योम)
अणु
#अगर defined(CONFIG_PPC_EARLY_DEBUG_LPAR)
	/* For LPAR machines that have an HVC console on vterm 0 */
	udbg_init_debug_lpar();
#या_अगर defined(CONFIG_PPC_EARLY_DEBUG_LPAR_HVSI)
	/* For LPAR machines that have an HVSI console on vterm 0 */
	udbg_init_debug_lpar_hvsi();
#या_अगर defined(CONFIG_PPC_EARLY_DEBUG_G5)
	/* For use on Apple G5 machines */
	udbg_init_pmac_realmode();
#या_अगर defined(CONFIG_PPC_EARLY_DEBUG_RTAS_PANEL)
	/* RTAS panel debug */
	udbg_init_rtas_panel();
#या_अगर defined(CONFIG_PPC_EARLY_DEBUG_RTAS_CONSOLE)
	/* RTAS console debug */
	udbg_init_rtas_console();
#या_अगर defined(CONFIG_PPC_EARLY_DEBUG_MAPLE)
	/* Maple real mode debug */
	udbg_init_maple_realmode();
#या_अगर defined(CONFIG_PPC_EARLY_DEBUG_PAS_REALMODE)
	udbg_init_pas_realmode();
#या_अगर defined(CONFIG_PPC_EARLY_DEBUG_BOOTX)
	udbg_init_btext();
#या_अगर defined(CONFIG_PPC_EARLY_DEBUG_44x)
	/* PPC44x debug */
	udbg_init_44x_as1();
#या_अगर defined(CONFIG_PPC_EARLY_DEBUG_40x)
	/* PPC40x debug */
	udbg_init_40x_realmode();
#या_अगर defined(CONFIG_PPC_EARLY_DEBUG_CPM)
	udbg_init_cpm();
#या_अगर defined(CONFIG_PPC_EARLY_DEBUG_USBGECKO)
	udbg_init_usbgecko();
#या_अगर defined(CONFIG_PPC_EARLY_DEBUG_MEMCONS)
	/* In memory console */
	udbg_init_memcons();
#या_अगर defined(CONFIG_PPC_EARLY_DEBUG_EHV_BC)
	udbg_init_ehv_bc();
#या_अगर defined(CONFIG_PPC_EARLY_DEBUG_PS3GELIC)
	udbg_init_ps3gelic();
#या_अगर defined(CONFIG_PPC_EARLY_DEBUG_OPAL_RAW)
	udbg_init_debug_opal_raw();
#या_अगर defined(CONFIG_PPC_EARLY_DEBUG_OPAL_HVSI)
	udbg_init_debug_opal_hvsi();
#पूर्ण_अगर

#अगर_घोषित CONFIG_PPC_EARLY_DEBUG
	console_loglevel = CONSOLE_LOGLEVEL_DEBUG;

	रेजिस्टर_early_udbg_console();
#पूर्ण_अगर
पूर्ण

/* udbg library, used by xmon et al */
व्योम udbg_माला_दो(स्थिर अक्षर *s)
अणु
	अगर (udbg_अ_दो) अणु
		अक्षर c;

		अगर (s && *s != '\0') अणु
			जबतक ((c = *s++) != '\0')
				udbg_अ_दो(c);
		पूर्ण

		अगर (udbg_flush)
			udbg_flush();
	पूर्ण
#अगर 0
	अन्यथा अणु
		prपूर्णांकk("%s", s);
	पूर्ण
#पूर्ण_अगर
पूर्ण

पूर्णांक udbg_ग_लिखो(स्थिर अक्षर *s, पूर्णांक n)
अणु
	पूर्णांक reमुख्य = n;
	अक्षर c;

	अगर (!udbg_अ_दो)
		वापस 0;

	अगर (s && *s != '\0') अणु
		जबतक (((c = *s++) != '\0') && (reमुख्य-- > 0)) अणु
			udbg_अ_दो(c);
		पूर्ण
	पूर्ण

	अगर (udbg_flush)
		udbg_flush();

	वापस n - reमुख्य;
पूर्ण

#घोषणा UDBG_बफ_मानE 256
व्योम udbg_म_लिखो(स्थिर अक्षर *fmt, ...)
अणु
	अगर (udbg_अ_दो) अणु
		अक्षर buf[UDBG_बफ_मानE];
		बहु_सूची args;

		बहु_शुरू(args, fmt);
		vsnम_लिखो(buf, UDBG_बफ_मानE, fmt, args);
		udbg_माला_दो(buf);
		बहु_पूर्ण(args);
	पूर्ण
पूर्ण

व्योम __init udbg_progress(अक्षर *s, अचिन्हित लघु hex)
अणु
	udbg_माला_दो(s);
	udbg_माला_दो("\n");
पूर्ण

/*
 * Early boot console based on udbg
 */
अटल व्योम udbg_console_ग_लिखो(काष्ठा console *con, स्थिर अक्षर *s,
		अचिन्हित पूर्णांक n)
अणु
	udbg_ग_लिखो(s, n);
पूर्ण

अटल काष्ठा console udbg_console = अणु
	.name	= "udbg",
	.ग_लिखो	= udbg_console_ग_लिखो,
	.flags	= CON_PRINTBUFFER | CON_ENABLED | CON_BOOT | CON_ANYTIME,
	.index	= 0,
पूर्ण;

/*
 * Called by setup_प्रणाली after ppc_md->probe and ppc_md->early_init.
 * Call it again after setting udbg_अ_दो in ppc_md->setup_arch.
 */
व्योम __init रेजिस्टर_early_udbg_console(व्योम)
अणु
	अगर (early_console)
		वापस;

	अगर (!udbg_अ_दो)
		वापस;

	अगर (म_माला(boot_command_line, "udbg-immortal")) अणु
		prपूर्णांकk(KERN_INFO "early console immortal !\n");
		udbg_console.flags &= ~CON_BOOT;
	पूर्ण
	early_console = &udbg_console;
	रेजिस्टर_console(&udbg_console);
पूर्ण

#अगर 0   /* अगर you want to use this as a regular output console */
console_initcall(रेजिस्टर_udbg_console);
#पूर्ण_अगर
