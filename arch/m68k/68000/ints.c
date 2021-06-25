<शैली गुरु>
/*
 * पूर्णांकs.c - Generic पूर्णांकerrupt controller support
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file COPYING in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright 1996 Roman Zippel
 * Copyright 1999 D. Jeff Dionne <jeff@rt-control.com>
 */

#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <यंत्र/traps.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/machdep.h>

#अगर defined(CONFIG_M68328)
#समावेश <यंत्र/MC68328.h>
#या_अगर defined(CONFIG_M68EZ328)
#समावेश <यंत्र/MC68EZ328.h>
#या_अगर defined(CONFIG_M68VZ328)
#समावेश <यंत्र/MC68VZ328.h>
#पूर्ण_अगर

/* assembler routines */
यंत्रlinkage व्योम प्रणाली_call(व्योम);
यंत्रlinkage व्योम buserr(व्योम);
यंत्रlinkage व्योम trap(व्योम);
यंत्रlinkage व्योम trap3(व्योम);
यंत्रlinkage व्योम trap4(व्योम);
यंत्रlinkage व्योम trap5(व्योम);
यंत्रlinkage व्योम trap6(व्योम);
यंत्रlinkage व्योम trap7(व्योम);
यंत्रlinkage व्योम trap8(व्योम);
यंत्रlinkage व्योम trap9(व्योम);
यंत्रlinkage व्योम trap10(व्योम);
यंत्रlinkage व्योम trap11(व्योम);
यंत्रlinkage व्योम trap12(व्योम);
यंत्रlinkage व्योम trap13(व्योम);
यंत्रlinkage व्योम trap14(व्योम);
यंत्रlinkage व्योम trap15(व्योम);
यंत्रlinkage व्योम trap33(व्योम);
यंत्रlinkage व्योम trap34(व्योम);
यंत्रlinkage व्योम trap35(व्योम);
यंत्रlinkage व्योम trap36(व्योम);
यंत्रlinkage व्योम trap37(व्योम);
यंत्रlinkage व्योम trap38(व्योम);
यंत्रlinkage व्योम trap39(व्योम);
यंत्रlinkage व्योम trap40(व्योम);
यंत्रlinkage व्योम trap41(व्योम);
यंत्रlinkage व्योम trap42(व्योम);
यंत्रlinkage व्योम trap43(व्योम);
यंत्रlinkage व्योम trap44(व्योम);
यंत्रlinkage व्योम trap45(व्योम);
यंत्रlinkage व्योम trap46(व्योम);
यंत्रlinkage व्योम trap47(व्योम);
यंत्रlinkage irqवापस_t bad_पूर्णांकerrupt(पूर्णांक, व्योम *);
यंत्रlinkage irqवापस_t पूर्णांकhandler(व्योम);
यंत्रlinkage irqवापस_t पूर्णांकhandler1(व्योम);
यंत्रlinkage irqवापस_t पूर्णांकhandler2(व्योम);
यंत्रlinkage irqवापस_t पूर्णांकhandler3(व्योम);
यंत्रlinkage irqवापस_t पूर्णांकhandler4(व्योम);
यंत्रlinkage irqवापस_t पूर्णांकhandler5(व्योम);
यंत्रlinkage irqवापस_t पूर्णांकhandler6(व्योम);
यंत्रlinkage irqवापस_t पूर्णांकhandler7(व्योम);

/* The 68k family did not have a good way to determine the source
 * of पूर्णांकerrupts until later in the family.  The EC000 core करोes
 * not provide the vector number on the stack, we vector everything
 * पूर्णांकo one vector and look in the blasted mask रेजिस्टर...
 * This code is deचिन्हित to be fast, almost स्थिरant समय, not clean!
 */
व्योम process_पूर्णांक(पूर्णांक vec, काष्ठा pt_regs *fp)
अणु
	पूर्णांक irq;
	पूर्णांक mask;

	अचिन्हित दीर्घ pend = ISR;

	जबतक (pend) अणु
		अगर (pend & 0x0000ffff) अणु
			अगर (pend & 0x000000ff) अणु
				अगर (pend & 0x0000000f) अणु
					mask = 0x00000001;
					irq = 0;
				पूर्ण अन्यथा अणु
					mask = 0x00000010;
					irq = 4;
				पूर्ण
			पूर्ण अन्यथा अणु
				अगर (pend & 0x00000f00) अणु
					mask = 0x00000100;
					irq = 8;
				पूर्ण अन्यथा अणु
					mask = 0x00001000;
					irq = 12;
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (pend & 0x00ff0000) अणु
				अगर (pend & 0x000f0000) अणु
					mask = 0x00010000;
					irq = 16;
				पूर्ण अन्यथा अणु
					mask = 0x00100000;
					irq = 20;
				पूर्ण
			पूर्ण अन्यथा अणु
				अगर (pend & 0x0f000000) अणु
					mask = 0x01000000;
					irq = 24;
				पूर्ण अन्यथा अणु
					mask = 0x10000000;
					irq = 28;
				पूर्ण
			पूर्ण
		पूर्ण

		जबतक (! (mask & pend)) अणु
			mask <<=1;
			irq++;
		पूर्ण

		करो_IRQ(irq, fp);
		pend &= ~mask;
	पूर्ण
पूर्ण

अटल व्योम पूर्णांकc_irq_unmask(काष्ठा irq_data *d)
अणु
	IMR &= ~(1 << d->irq);
पूर्ण

अटल व्योम पूर्णांकc_irq_mask(काष्ठा irq_data *d)
अणु
	IMR |= (1 << d->irq);
पूर्ण

अटल काष्ठा irq_chip पूर्णांकc_irq_chip = अणु
	.name		= "M68K-INTC",
	.irq_mask	= पूर्णांकc_irq_mask,
	.irq_unmask	= पूर्णांकc_irq_unmask,
पूर्ण;

/*
 * This function should be called during kernel startup to initialize
 * the machine vector table.
 */
व्योम __init trap_init(व्योम)
अणु
	पूर्णांक i;

	/* set up the vectors */
	क्रम (i = 72; i < 256; ++i)
		_ramvec[i] = (e_vector) bad_पूर्णांकerrupt;

	_ramvec[32] = प्रणाली_call;

	_ramvec[65] = (e_vector) पूर्णांकhandler1;
	_ramvec[66] = (e_vector) पूर्णांकhandler2;
	_ramvec[67] = (e_vector) पूर्णांकhandler3;
	_ramvec[68] = (e_vector) पूर्णांकhandler4;
	_ramvec[69] = (e_vector) पूर्णांकhandler5;
	_ramvec[70] = (e_vector) पूर्णांकhandler6;
	_ramvec[71] = (e_vector) पूर्णांकhandler7;
पूर्ण

व्योम __init init_IRQ(व्योम)
अणु
	पूर्णांक i;

	IVR = 0x40; /* Set DragonBall IVR (पूर्णांकerrupt base) to 64 */

	/* turn off all पूर्णांकerrupts */
	IMR = ~0;

	क्रम (i = 0; (i < NR_IRQS); i++) अणु
		irq_set_chip(i, &पूर्णांकc_irq_chip);
		irq_set_handler(i, handle_level_irq);
	पूर्ण
पूर्ण

