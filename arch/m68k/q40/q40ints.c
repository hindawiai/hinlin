<शैली गुरु>
/*
 * arch/m68k/q40/q40पूर्णांकs.c
 *
 * Copyright (C) 1999,2001 Riअक्षरd Zidlicky
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file COPYING in the मुख्य directory of this archive
 * क्रम more details.
 *
 * .. used to be loosely based on bvme6000पूर्णांकs.c
 *
 */

#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>

#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/traps.h>

#समावेश <यंत्र/q40_master.h>
#समावेश <यंत्र/q40पूर्णांकs.h>

/*
 * Q40 IRQs are defined as follows:
 *            3,4,5,6,7,10,11,14,15 : ISA dev IRQs
 *            16-31: reserved
 *            32   : keyboard पूर्णांक
 *            33   : frame पूर्णांक (50/200 Hz periodic समयr)
 *            34   : sample पूर्णांक (10/20 KHz periodic समयr)
 *
*/

अटल व्योम q40_irq_handler(अचिन्हित पूर्णांक, काष्ठा pt_regs *fp);
अटल व्योम q40_irq_enable(काष्ठा irq_data *data);
अटल व्योम q40_irq_disable(काष्ठा irq_data *data);

अचिन्हित लघु q40_ablecount[35];
अचिन्हित लघु q40_state[35];

अटल अचिन्हित पूर्णांक q40_irq_startup(काष्ठा irq_data *data)
अणु
	अचिन्हित पूर्णांक irq = data->irq;

	/* test क्रम ISA पूर्णांकs not implemented by HW */
	चयन (irq) अणु
	हाल 1: हाल 2: हाल 8: हाल 9:
	हाल 11: हाल 12: हाल 13:
		pr_warn("%s: ISA IRQ %d not implemented by HW\n", __func__,
			irq);
		/* FIXME वापस -ENXIO; */
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम q40_irq_shutकरोwn(काष्ठा irq_data *data)
अणु
पूर्ण

अटल काष्ठा irq_chip q40_irq_chip = अणु
	.name		= "q40",
	.irq_startup	= q40_irq_startup,
	.irq_shutकरोwn	= q40_irq_shutकरोwn,
	.irq_enable	= q40_irq_enable,
	.irq_disable	= q40_irq_disable,
पूर्ण;

/*
 * व्योम q40_init_IRQ (व्योम)
 *
 * Parameters:	None
 *
 * Returns:	Nothing
 *
 * This function is called during kernel startup to initialize
 * the q40 IRQ handling routines.
 */

अटल पूर्णांक disabled;

व्योम __init q40_init_IRQ(व्योम)
अणु
	m68k_setup_irq_controller(&q40_irq_chip, handle_simple_irq, 1,
				  Q40_IRQ_MAX);

	/* setup handler क्रम ISA पूर्णांकs */
	m68k_setup_स्वतः_पूर्णांकerrupt(q40_irq_handler);

	m68k_irq_startup_irq(IRQ_AUTO_2);
	m68k_irq_startup_irq(IRQ_AUTO_4);

	/* now enable some पूर्णांकs.. */
	master_outb(1, EXT_ENABLE_REG);  /* ISA IRQ 5-15 */

	/* make sure keyboard IRQ is disabled */
	master_outb(0, KEY_IRQ_ENABLE_REG);
पूर्ण


/*
 * this stuff करोesn't really beदीर्घ here..
 */

पूर्णांक ql_ticks;              /* 200Hz ticks since last jअगरfie */
अटल पूर्णांक sound_ticks;

#घोषणा SVOL 45

व्योम q40_mksound(अचिन्हित पूर्णांक hz, अचिन्हित पूर्णांक ticks)
अणु
	/* क्रम now ignore hz, except that hz==0 चयनes off sound */
	/* simply alternate the ampl (128-SVOL)-(128+SVOL)-..-.. at 200Hz */
	अगर (hz == 0) अणु
		अगर (sound_ticks)
			sound_ticks = 1;

		*DAC_LEFT = 128;
		*DAC_RIGHT = 128;

		वापस;
	पूर्ण
	/* sound itself is करोne in q40_समयr_पूर्णांक */
	अगर (sound_ticks == 0)
		sound_ticks = 1000; /* pretty दीर्घ beep */
	sound_ticks = ticks << 1;
पूर्ण

अटल irqवापस_t q40_समयr_पूर्णांक(पूर्णांक irq, व्योम *dev_id)
अणु
	ql_ticks = ql_ticks ? 0 : 1;
	अगर (sound_ticks) अणु
		अचिन्हित अक्षर sval=(sound_ticks & 1) ? 128-SVOL : 128+SVOL;
		sound_ticks--;
		*DAC_LEFT=sval;
		*DAC_RIGHT=sval;
	पूर्ण

	अगर (!ql_ticks) अणु
		अचिन्हित दीर्घ flags;

		local_irq_save(flags);
		legacy_समयr_tick(1);
		समयr_heartbeat();
		local_irq_restore(flags);
	पूर्ण
	वापस IRQ_HANDLED;
पूर्ण

व्योम q40_sched_init (व्योम)
अणु
	पूर्णांक समयr_irq;

	समयr_irq = Q40_IRQ_FRAME;

	अगर (request_irq(समयr_irq, q40_समयr_पूर्णांक, 0, "timer", शून्य))
		panic("Couldn't register timer int");

	master_outb(-1, FRAME_CLEAR_REG);
	master_outb( 1, FRAME_RATE_REG);
पूर्ण


/*
 * tables to translate bits पूर्णांकo IRQ numbers
 * it is a good idea to order the entries by priority
 *
*/

काष्ठा IRQ_TABLEअणु अचिन्हित mask; पूर्णांक irq ;पूर्ण;
#अगर 0
अटल काष्ठा IRQ_TABLE iirqs[]=अणु
  अणुQ40_IRQ_FRAME_MASK,Q40_IRQ_FRAMEपूर्ण,
  अणुQ40_IRQ_KEYB_MASK,Q40_IRQ_KEYBOARDपूर्ण,
  अणु0,0पूर्णपूर्ण;
#पूर्ण_अगर
अटल काष्ठा IRQ_TABLE eirqs[] = अणु
  अणु .mask = Q40_IRQ3_MASK,	.irq = 3 पूर्ण,	/* ser 1 */
  अणु .mask = Q40_IRQ4_MASK,	.irq = 4 पूर्ण,	/* ser 2 */
  अणु .mask = Q40_IRQ14_MASK,	.irq = 14 पूर्ण,	/* IDE 1 */
  अणु .mask = Q40_IRQ15_MASK,	.irq = 15 पूर्ण,	/* IDE 2 */
  अणु .mask = Q40_IRQ6_MASK,	.irq = 6 पूर्ण,	/* floppy, handled अन्यथाwhere */
  अणु .mask = Q40_IRQ7_MASK,	.irq = 7 पूर्ण,	/* par */
  अणु .mask = Q40_IRQ5_MASK,	.irq = 5 पूर्ण,
  अणु .mask = Q40_IRQ10_MASK,	.irq = 10 पूर्ण,
  अणु0,0पूर्ण
पूर्ण;

/* complain only this many बार about spurious पूर्णांकs : */
अटल पूर्णांक ccleirq=60;    /* ISA dev IRQs*/
/*अटल पूर्णांक cclirq=60;*/     /* पूर्णांकernal */

/* FIXME: add shared पूर्णांकs,mask,unmask,probing.... */

#घोषणा IRQ_INPROGRESS 1
/*अटल अचिन्हित लघु saved_mask;*/
//अटल पूर्णांक करो_tपूर्णांक=0;

#घोषणा DEBUG_Q40INT
/*#घोषणा IP_USE_DISABLE *//* would be nice, but crashes ???? */

अटल पूर्णांक mext_disabled=0;  /* ext irq disabled by master chip? */
अटल पूर्णांक aliased_irq=0;  /* how many बार inside handler ?*/


/* got पूर्णांकerrupt, dispatch to ISA or keyboard/समयr IRQs */
अटल व्योम q40_irq_handler(अचिन्हित पूर्णांक irq, काष्ठा pt_regs *fp)
अणु
	अचिन्हित mir, mer;
	पूर्णांक i;

//repeat:
	mir = master_inb(IIRQ_REG);
#अगर_घोषित CONFIG_BLK_DEV_FD
	अगर ((mir & Q40_IRQ_EXT_MASK) &&
	    (master_inb(EIRQ_REG) & Q40_IRQ6_MASK)) अणु
		floppy_hardपूर्णांक();
		वापस;
	पूर्ण
#पूर्ण_अगर
	चयन (irq) अणु
	हाल 4:
	हाल 6:
		करो_IRQ(Q40_IRQ_SAMPLE, fp);
		वापस;
	पूर्ण
	अगर (mir & Q40_IRQ_FRAME_MASK) अणु
		करो_IRQ(Q40_IRQ_FRAME, fp);
		master_outb(-1, FRAME_CLEAR_REG);
	पूर्ण
	अगर ((mir & Q40_IRQ_SER_MASK) || (mir & Q40_IRQ_EXT_MASK)) अणु
		mer = master_inb(EIRQ_REG);
		क्रम (i = 0; eirqs[i].mask; i++) अणु
			अगर (mer & eirqs[i].mask) अणु
				irq = eirqs[i].irq;
/*
 * There is a little mess wrt which IRQ really caused this irq request. The
 * मुख्य problem is that IIRQ_REG and EIRQ_REG reflect the state when they
 * are पढ़ो - which is दीर्घ after the request came in. In theory IRQs should
 * not just go away but they occasionally करो
 */
				अगर (irq > 4 && irq <= 15 && mext_disabled) अणु
					/*aliased_irq++;*/
					जाओ iirq;
				पूर्ण
				अगर (q40_state[irq] & IRQ_INPROGRESS) अणु
					/* some handlers करो local_irq_enable() क्रम irq latency reasons, */
					/* however reentering an active irq handler is not permitted */
#अगर_घोषित IP_USE_DISABLE
					/* in theory this is the better way to करो it because it still */
					/* lets through eg the serial irqs, unक्रमtunately it crashes */
					disable_irq(irq);
					disabled = 1;
#अन्यथा
					/*pr_warn("IRQ_INPROGRESS detected for irq %d, disabling - %s disabled\n",
						irq, disabled ? "already" : "not yet"); */
					fp->sr = (((fp->sr) & (~0x700))+0x200);
					disabled = 1;
#पूर्ण_अगर
					जाओ iirq;
				पूर्ण
				q40_state[irq] |= IRQ_INPROGRESS;
				करो_IRQ(irq, fp);
				q40_state[irq] &= ~IRQ_INPROGRESS;

				/* naively enable everything, अगर that fails than    */
				/* this function will be reentered immediately thus */
				/* getting another chance to disable the IRQ        */

				अगर (disabled) अणु
#अगर_घोषित IP_USE_DISABLE
					अगर (irq > 4) अणु
						disabled = 0;
						enable_irq(irq);
					पूर्ण
#अन्यथा
					disabled = 0;
					/*pr_info("reenabling irq %d\n", irq); */
#पूर्ण_अगर
				पूर्ण
// used to करो 'goto repeat;' here, this delayed bh processing too दीर्घ
				वापस;
			पूर्ण
		पूर्ण
		अगर (mer && ccleirq > 0 && !aliased_irq) अणु
			pr_warn("ISA interrupt from unknown source? EIRQ_REG = %x\n",
				mer);
			ccleirq--;
		पूर्ण
	पूर्ण
 iirq:
	mir = master_inb(IIRQ_REG);
	/* should test whether keyboard irq is really enabled, करोing it in defhand */
	अगर (mir & Q40_IRQ_KEYB_MASK)
		करो_IRQ(Q40_IRQ_KEYBOARD, fp);

	वापस;
पूर्ण

व्योम q40_irq_enable(काष्ठा irq_data *data)
अणु
	अचिन्हित पूर्णांक irq = data->irq;

	अगर (irq >= 5 && irq <= 15) अणु
		mext_disabled--;
		अगर (mext_disabled > 0)
			pr_warn("q40_irq_enable : nested disable/enable\n");
		अगर (mext_disabled == 0)
			master_outb(1, EXT_ENABLE_REG);
	पूर्ण
पूर्ण


व्योम q40_irq_disable(काष्ठा irq_data *data)
अणु
	अचिन्हित पूर्णांक irq = data->irq;

	/* disable ISA iqs : only करो something अगर the driver has been
	 * verअगरied to be Q40 "compatible" - right now IDE, NE2K
	 * Any driver should not attempt to sleep across disable_irq !!
	 */

	अगर (irq >= 5 && irq <= 15) अणु
		master_outb(0, EXT_ENABLE_REG);
		mext_disabled++;
		अगर (mext_disabled > 1)
			pr_info("disable_irq nesting count %d\n",
				mext_disabled);
	पूर्ण
पूर्ण
