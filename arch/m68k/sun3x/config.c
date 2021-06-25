<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Setup kernel क्रम a Sun3x machine
 *
 * (C) 1999 Thomas Bogenकरोerfer (tsbogend@alpha.franken.de)
 *
 * based on code from Oliver Jowett <oliver@jowett.manawatu.gen.nz>
 */

#समावेश <linux/types.h>
#समावेश <linux/mm.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/console.h>
#समावेश <linux/init.h>

#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/sun3xprom.h>
#समावेश <यंत्र/sun3पूर्णांकs.h>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/oplib.h>

#समावेश "time.h"

अस्थिर अक्षर *घड़ी_va;

बाह्य व्योम sun3_get_model(अक्षर *model);

व्योम sun3_leds(अचिन्हित पूर्णांक i)
अणु

पूर्ण

अटल व्योम sun3x_get_hardware_list(काष्ठा seq_file *m)
अणु
	seq_म_लिखो(m, "PROM Revision:\t%s\n", romvec->pv_monid);
पूर्ण

/*
 *  Setup the sun3x configuration info
 */
व्योम __init config_sun3x(व्योम)
अणु

	sun3x_prom_init();

	mach_sched_init      = sun3x_sched_init;
	mach_init_IRQ        = sun3_init_IRQ;

	mach_reset           = sun3x_reboot;

	mach_hwclk           = sun3x_hwclk;
	mach_get_model       = sun3_get_model;
	mach_get_hardware_list = sun3x_get_hardware_list;

	sun3_पूर्णांकreg = (अचिन्हित अक्षर *)SUN3X_INTREG;

	/* only the serial console is known to work anyway... */
#अगर 0
	चयन (*(अचिन्हित अक्षर *)SUN3X_EEPROM_CONS) अणु
	हाल 0x10:
		serial_console = 1;
		conचयनp = शून्य;
		अवरोध;
	हाल 0x11:
		serial_console = 2;
		conचयनp = शून्य;
		अवरोध;
	शेष:
		serial_console = 0;
		अवरोध;
	पूर्ण
#पूर्ण_अगर

पूर्ण

