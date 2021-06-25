<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Prom access routines क्रम the sun3x */

#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/tty.h>
#समावेश <linux/console.h>
#समावेश <linux/init.h>
#समावेश <linux/mm.h>
#समावेश <linux/माला.स>

#समावेश <यंत्र/page.h>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/traps.h>
#समावेश <यंत्र/sun3xprom.h>
#समावेश <यंत्र/idprom.h>
#समावेश <यंत्र/segment.h>
#समावेश <यंत्र/sun3पूर्णांकs.h>
#समावेश <यंत्र/खोलोprom.h>
#समावेश <यंत्र/machines.h>

व्योम (*sun3x_अक्षर_दो)(पूर्णांक);
पूर्णांक (*sun3x_अक्षर_लो)(व्योम);
पूर्णांक (*sun3x_mayget)(व्योम);
पूर्णांक (*sun3x_mayput)(पूर्णांक);
व्योम (*sun3x_prom_reboot)(व्योम);
e_vector sun3x_prom_पात;
काष्ठा linux_romvec *romvec;

/* prom vector table */
e_vector *sun3x_prom_vbr;

/* Handle वापसing to the prom */
व्योम sun3x_halt(व्योम)
अणु
	अचिन्हित दीर्घ flags;

	/* Disable पूर्णांकerrupts जबतक we mess with things */
	local_irq_save(flags);

	/* Restore prom vbr */
	यंत्र अस्थिर ("movec %0,%%vbr" : : "r" ((व्योम*)sun3x_prom_vbr));

	/* Restore prom NMI घड़ी */
//	sun3x_disable_पूर्णांकreg(5);
	sun3_enable_irq(7);

	/* Let 'er rip */
	यंत्र अस्थिर ("trap #14");

	/* Restore everything */
	sun3_disable_irq(7);
	sun3_enable_irq(5);

	यंत्र अस्थिर ("movec %0,%%vbr" : : "r" ((व्योम*)vectors));
	local_irq_restore(flags);
पूर्ण

व्योम sun3x_reboot(व्योम)
अणु
	/* This never वापसs, करोn't bother saving things */
	local_irq_disable();

	/* Restore prom vbr */
	यंत्र अस्थिर ("movec %0,%%vbr" : : "r" ((व्योम*)sun3x_prom_vbr));

	/* Restore prom NMI घड़ी */
	sun3_disable_irq(5);
	sun3_enable_irq(7);

	/* Let 'er rip */
	(*romvec->pv_reboot)("vmlinux");
पूर्ण

अटल व्योम sun3x_prom_ग_लिखो(काष्ठा console *co, स्थिर अक्षर *s,
                             अचिन्हित पूर्णांक count)
अणु
	जबतक (count--) अणु
		अगर (*s == '\n')
			sun3x_अक्षर_दो('\r');
		sun3x_अक्षर_दो(*s++);
	पूर्ण
पूर्ण

/* debug console - ग_लिखो-only */

अटल काष्ठा console sun3x_debug = अणु
	.name	= "debug",
	.ग_लिखो	= sun3x_prom_ग_लिखो,
	.flags	= CON_PRINTBUFFER,
	.index	= -1,
पूर्ण;

व्योम __init sun3x_prom_init(व्योम)
अणु
	/* Read the vector table */

	sun3x_अक्षर_दो = *(व्योम (**)(पूर्णांक)) (SUN3X_P_PUTCHAR);
	sun3x_अक्षर_लो = *(पूर्णांक (**)(व्योम)) (SUN3X_P_GETCHAR);
	sun3x_mayget = *(पूर्णांक (**)(व्योम))  (SUN3X_P_MAYGET);
	sun3x_mayput = *(पूर्णांक (**)(पूर्णांक))   (SUN3X_P_MAYPUT);
	sun3x_prom_reboot = *(व्योम (**)(व्योम)) (SUN3X_P_REBOOT);
	sun3x_prom_पात = *(e_vector *)  (SUN3X_P_ABORT);
	romvec = (काष्ठा linux_romvec *)SUN3X_PROM_BASE;

	idprom_init();

	अगर (!((idprom->id_machtype & SM_ARCH_MASK) == SM_SUN3X)) अणु
		pr_warn("Machine reports strange type %02x\n",
			idprom->id_machtype);
		pr_warn("Pretending it's a 3/80, but very afraid...\n");
		idprom->id_machtype = SM_SUN3X | SM_3_80;
	पूर्ण

	/* poपूर्णांक trap #14 at पात.
	 * XXX this is futile since we restore the vbr first - oops
	 */
	vectors[VEC_TRAP14] = sun3x_prom_पात;
पूर्ण

अटल पूर्णांक __init sun3x_debug_setup(अक्षर *arg)
अणु
	/* If debug=prom was specअगरied, start the debug console */
	अगर (MACH_IS_SUN3X && !म_भेद(arg, "prom"))
		रेजिस्टर_console(&sun3x_debug);
	वापस 0;
पूर्ण

early_param("debug", sun3x_debug_setup);

/* some prom functions to export */
पूर्णांक prom_getपूर्णांकशेष(पूर्णांक node, अक्षर *property, पूर्णांक deflt)
अणु
	वापस deflt;
पूर्ण

पूर्णांक prom_getbool (पूर्णांक node, अक्षर *prop)
अणु
	वापस 1;
पूर्ण

व्योम prom_म_लिखो(अक्षर *fmt, ...)
अणु
पूर्ण

व्योम prom_halt (व्योम)
अणु
	sun3x_halt();
पूर्ण

/* Get the idprom and stuff it पूर्णांकo buffer 'idbuf'.  Returns the
 * क्रमmat type.  'num_bytes' is the number of bytes that your idbuf
 * has space क्रम.  Returns 0xff on error.
 */
अचिन्हित अक्षर
prom_get_idprom(अक्षर *idbuf, पूर्णांक num_bytes)
अणु
        पूर्णांक i;

	/* make a copy of the idprom काष्ठाure */
	क्रम (i = 0; i < num_bytes; i++)
		idbuf[i] = ((अक्षर *)SUN3X_IDPROM)[i];

        वापस idbuf[0];
पूर्ण
