<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *
 * arch/xtensa/platक्रमm-iss/setup.c
 *
 * Platक्रमm specअगरic initialization.
 *
 * Authors: Chris Zankel <chris@zankel.net>
 *          Joe Taylor <joe@tensilica.com>
 *
 * Copyright 2001 - 2005 Tensilica Inc.
 * Copyright 2017 Cadence Design Systems Inc.
 */
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/prपूर्णांकk.h>
#समावेश <linux/माला.स>

#समावेश <यंत्र/platक्रमm.h>
#समावेश <यंत्र/setup.h>

#समावेश <platक्रमm/simcall.h>


व्योम platक्रमm_halt(व्योम)
अणु
	pr_info(" ** Called platform_halt() **\n");
	simc_निकास(0);
पूर्ण

व्योम platक्रमm_घातer_off(व्योम)
अणु
	pr_info(" ** Called platform_power_off() **\n");
	simc_निकास(0);
पूर्ण

व्योम platक्रमm_restart(व्योम)
अणु
	/* Flush and reset the mmu, simulate a processor reset, and
	 * jump to the reset vector. */
	cpu_reset();
	/* control never माला_लो here */
पूर्ण

अटल पूर्णांक
iss_panic_event(काष्ठा notअगरier_block *this, अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	simc_निकास(1);
	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा notअगरier_block iss_panic_block = अणु
	.notअगरier_call = iss_panic_event,
पूर्ण;

व्योम __init platक्रमm_setup(अक्षर **p_cmdline)
अणु
	अटल व्योम *argv[COMMAND_LINE_SIZE / माप(व्योम *)] __initdata;
	अटल अक्षर cmdline[COMMAND_LINE_SIZE] __initdata;
	पूर्णांक argc = simc_argc();
	पूर्णांक argv_size = simc_argv_size();

	अगर (argc > 1) अणु
		अगर (argv_size > माप(argv)) अणु
			pr_err("%s: command line too long: argv_size = %d\n",
			       __func__, argv_size);
		पूर्ण अन्यथा अणु
			पूर्णांक i;

			cmdline[0] = 0;
			simc_argv((व्योम *)argv);

			क्रम (i = 1; i < argc; ++i) अणु
				अगर (i > 1)
					म_जोड़ो(cmdline, " ");
				म_जोड़ो(cmdline, argv[i]);
			पूर्ण
			*p_cmdline = cmdline;
		पूर्ण
	पूर्ण

	atomic_notअगरier_chain_रेजिस्टर(&panic_notअगरier_list, &iss_panic_block);
पूर्ण
