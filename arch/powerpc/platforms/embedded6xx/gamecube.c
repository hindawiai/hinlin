<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * arch/घातerpc/platक्रमms/embedded6xx/gamecube.c
 *
 * Nपूर्णांकenकरो GameCube board-specअगरic support
 * Copyright (C) 2004-2009 The GameCube Linux Team
 * Copyright (C) 2007,2008,2009 Albert Herranz
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/irq.h>
#समावेश <linux/kexec.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/of_platक्रमm.h>

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/समय.स>
#समावेश <यंत्र/udbg.h>

#समावेश "flipper-pic.h"
#समावेश "usbgecko_udbg.h"


अटल व्योम __noवापस gamecube_spin(व्योम)
अणु
	/* spin until घातer button pressed */
	क्रम (;;)
		cpu_relax();
पूर्ण

अटल व्योम __noवापस gamecube_restart(अक्षर *cmd)
अणु
	local_irq_disable();
	flipper_platक्रमm_reset();
	gamecube_spin();
पूर्ण

अटल व्योम gamecube_घातer_off(व्योम)
अणु
	local_irq_disable();
	gamecube_spin();
पूर्ण

अटल व्योम __noवापस gamecube_halt(व्योम)
अणु
	gamecube_restart(शून्य);
पूर्ण

अटल पूर्णांक __init gamecube_probe(व्योम)
अणु
	अगर (!of_machine_is_compatible("nintendo,gamecube"))
		वापस 0;

	pm_घातer_off = gamecube_घातer_off;

	ug_udbg_init();

	वापस 1;
पूर्ण

अटल व्योम gamecube_shutकरोwn(व्योम)
अणु
	flipper_quiesce();
पूर्ण

define_machine(gamecube) अणु
	.name			= "gamecube",
	.probe			= gamecube_probe,
	.restart		= gamecube_restart,
	.halt			= gamecube_halt,
	.init_IRQ		= flipper_pic_probe,
	.get_irq		= flipper_pic_get_irq,
	.calibrate_decr		= generic_calibrate_decr,
	.progress		= udbg_progress,
	.machine_shutकरोwn	= gamecube_shutकरोwn,
पूर्ण;


अटल स्थिर काष्ठा of_device_id gamecube_of_bus[] = अणु
	अणु .compatible = "nintendo,flipper", पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल पूर्णांक __init gamecube_device_probe(व्योम)
अणु
	अगर (!machine_is(gamecube))
		वापस 0;

	of_platक्रमm_bus_probe(शून्य, gamecube_of_bus, शून्य);
	वापस 0;
पूर्ण
device_initcall(gamecube_device_probe);

