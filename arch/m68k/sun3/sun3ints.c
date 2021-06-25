<शैली गुरु>
 /*
 * linux/arch/m68k/sun3/sun3पूर्णांकs.c -- Sun-3(x) Linux पूर्णांकerrupt handling code
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file COPYING in the मुख्य directory of this archive
 * क्रम more details.
 */

#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/kernel_स्थिति.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <यंत्र/segment.h>
#समावेश <यंत्र/पूर्णांकersil.h>
#समावेश <यंत्र/oplib.h>
#समावेश <यंत्र/sun3पूर्णांकs.h>
#समावेश <यंत्र/irq_regs.h>
#समावेश <linux/seq_file.h>

बाह्य व्योम sun3_leds (अचिन्हित अक्षर);

व्योम sun3_disable_पूर्णांकerrupts(व्योम)
अणु
	sun3_disable_irq(0);
पूर्ण

व्योम sun3_enable_पूर्णांकerrupts(व्योम)
अणु
	sun3_enable_irq(0);
पूर्ण

अटल पूर्णांक led_pattern[8] = अणु
       ~(0x80), ~(0x01),
       ~(0x40), ~(0x02),
       ~(0x20), ~(0x04),
       ~(0x10), ~(0x08)
पूर्ण;

अस्थिर अचिन्हित अक्षर* sun3_पूर्णांकreg;

व्योम sun3_enable_irq(अचिन्हित पूर्णांक irq)
अणु
	*sun3_पूर्णांकreg |=  (1 << irq);
पूर्ण

व्योम sun3_disable_irq(अचिन्हित पूर्णांक irq)
अणु
	*sun3_पूर्णांकreg &= ~(1 << irq);
पूर्ण

अटल irqवापस_t sun3_पूर्णांक7(पूर्णांक irq, व्योम *dev_id)
अणु
	अचिन्हित पूर्णांक cnt;

	cnt = kstat_irqs_cpu(irq, 0);
	अगर (!(cnt % 2000))
		sun3_leds(led_pattern[cnt % 16000 / 2000]);
	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t sun3_पूर्णांक5(पूर्णांक irq, व्योम *dev_id)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक cnt;

	local_irq_save(flags);
#अगर_घोषित CONFIG_SUN3
	पूर्णांकersil_clear();
#पूर्ण_अगर
	sun3_disable_irq(5);
	sun3_enable_irq(5);
#अगर_घोषित CONFIG_SUN3
	पूर्णांकersil_clear();
#पूर्ण_अगर
	legacy_समयr_tick(1);
	cnt = kstat_irqs_cpu(irq, 0);
	अगर (!(cnt % 20))
		sun3_leds(led_pattern[cnt % 160 / 20]);
	local_irq_restore(flags);
	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t sun3_vec255(पूर्णांक irq, व्योम *dev_id)
अणु
	वापस IRQ_HANDLED;
पूर्ण

व्योम __init sun3_init_IRQ(व्योम)
अणु
	*sun3_पूर्णांकreg = 1;

	m68k_setup_user_पूर्णांकerrupt(VEC_USER, 128);

	अगर (request_irq(IRQ_AUTO_5, sun3_पूर्णांक5, 0, "clock", शून्य))
		pr_err("Couldn't register %s interrupt\n", "int5");
	अगर (request_irq(IRQ_AUTO_7, sun3_पूर्णांक7, 0, "nmi", शून्य))
		pr_err("Couldn't register %s interrupt\n", "int7");
	अगर (request_irq(IRQ_USER+127, sun3_vec255, 0, "vec255", शून्य))
		pr_err("Couldn't register %s interrupt\n", "vec255");
पूर्ण
