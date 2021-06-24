<शैली गुरु>
/*
 * linux/arch/arm/mach-omap1/समय.c
 *
 * OMAP Timers
 *
 * Copyright (C) 2004 Nokia Corporation
 * Partial समयr reग_लिखो and additional dynamic tick समयr support by
 * Tony Lindgen <tony@atomide.com> and
 * Tuukka Tikkanen <tuukka.tikkanen@elektrobit.com>
 *
 * MPU समयr code based on the older MPU समयr code क्रम OMAP
 * Copyright (C) 2000 RidgeRun, Inc.
 * Author: Greg Lonnon <glonnon@ridgerun.com>
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN
 * NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY सूचीECT, INसूचीECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
 * USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * You should have received a copy of the  GNU General Public License aदीर्घ
 * with this program; अगर not, ग_लिखो  to the Free Software Foundation, Inc.,
 * 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/clk.h>
#समावेश <linux/err.h>
#समावेश <linux/घड़ीsource.h>
#समावेश <linux/घड़ीchips.h>
#समावेश <linux/पन.स>
#समावेश <linux/sched_घड़ी.h>

#समावेश <यंत्र/irq.h>

#समावेश <mach/hardware.h>
#समावेश <यंत्र/mach/irq.h>
#समावेश <यंत्र/mach/समय.स>

#समावेश "iomap.h"
#समावेश "common.h"

#अगर_घोषित CONFIG_OMAP_MPU_TIMER

#घोषणा OMAP_MPU_TIMER_BASE		OMAP_MPU_TIMER1_BASE
#घोषणा OMAP_MPU_TIMER_OFFSET		0x100

प्रकार काष्ठा अणु
	u32 cntl;			/* CNTL_TIMER, R/W */
	u32 load_tim;			/* LOAD_TIM,   W */
	u32 पढ़ो_tim;			/* READ_TIM,   R */
पूर्ण omap_mpu_समयr_regs_t;

#घोषणा omap_mpu_समयr_base(n)							\
((omap_mpu_समयr_regs_t __iomem *)OMAP1_IO_ADDRESS(OMAP_MPU_TIMER_BASE +	\
				 (n)*OMAP_MPU_TIMER_OFFSET))

अटल अंतरभूत अचिन्हित दीर्घ notrace omap_mpu_समयr_पढ़ो(पूर्णांक nr)
अणु
	omap_mpu_समयr_regs_t __iomem *समयr = omap_mpu_समयr_base(nr);
	वापस पढ़ोl(&समयr->पढ़ो_tim);
पूर्ण

अटल अंतरभूत व्योम omap_mpu_set_स्वतःreset(पूर्णांक nr)
अणु
	omap_mpu_समयr_regs_t __iomem *समयr = omap_mpu_समयr_base(nr);

	ग_लिखोl(पढ़ोl(&समयr->cntl) | MPU_TIMER_AR, &समयr->cntl);
पूर्ण

अटल अंतरभूत व्योम omap_mpu_हटाओ_स्वतःreset(पूर्णांक nr)
अणु
	omap_mpu_समयr_regs_t __iomem *समयr = omap_mpu_समयr_base(nr);

	ग_लिखोl(पढ़ोl(&समयr->cntl) & ~MPU_TIMER_AR, &समयr->cntl);
पूर्ण

अटल अंतरभूत व्योम omap_mpu_समयr_start(पूर्णांक nr, अचिन्हित दीर्घ load_val,
					पूर्णांक स्वतःreset)
अणु
	omap_mpu_समयr_regs_t __iomem *समयr = omap_mpu_समयr_base(nr);
	अचिन्हित पूर्णांक समयrflags = MPU_TIMER_CLOCK_ENABLE | MPU_TIMER_ST;

	अगर (स्वतःreset)
		समयrflags |= MPU_TIMER_AR;

	ग_लिखोl(MPU_TIMER_CLOCK_ENABLE, &समयr->cntl);
	udelay(1);
	ग_लिखोl(load_val, &समयr->load_tim);
        udelay(1);
	ग_लिखोl(समयrflags, &समयr->cntl);
पूर्ण

अटल अंतरभूत व्योम omap_mpu_समयr_stop(पूर्णांक nr)
अणु
	omap_mpu_समयr_regs_t __iomem *समयr = omap_mpu_समयr_base(nr);

	ग_लिखोl(पढ़ोl(&समयr->cntl) & ~MPU_TIMER_ST, &समयr->cntl);
पूर्ण

/*
 * ---------------------------------------------------------------------------
 * MPU समयr 1 ... count करोwn to zero, पूर्णांकerrupt, reload
 * ---------------------------------------------------------------------------
 */
अटल पूर्णांक omap_mpu_set_next_event(अचिन्हित दीर्घ cycles,
				   काष्ठा घड़ी_event_device *evt)
अणु
	omap_mpu_समयr_start(0, cycles, 0);
	वापस 0;
पूर्ण

अटल पूर्णांक omap_mpu_set_oneshot(काष्ठा घड़ी_event_device *evt)
अणु
	omap_mpu_समयr_stop(0);
	omap_mpu_हटाओ_स्वतःreset(0);
	वापस 0;
पूर्ण

अटल पूर्णांक omap_mpu_set_periodic(काष्ठा घड़ी_event_device *evt)
अणु
	omap_mpu_set_स्वतःreset(0);
	वापस 0;
पूर्ण

अटल काष्ठा घड़ी_event_device घड़ीevent_mpu_समयr1 = अणु
	.name			= "mpu_timer1",
	.features		= CLOCK_EVT_FEAT_PERIODIC |
				  CLOCK_EVT_FEAT_ONESHOT,
	.set_next_event		= omap_mpu_set_next_event,
	.set_state_periodic	= omap_mpu_set_periodic,
	.set_state_oneshot	= omap_mpu_set_oneshot,
पूर्ण;

अटल irqवापस_t omap_mpu_समयr1_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा घड़ी_event_device *evt = &घड़ीevent_mpu_समयr1;

	evt->event_handler(evt);

	वापस IRQ_HANDLED;
पूर्ण

अटल __init व्योम omap_init_mpu_समयr(अचिन्हित दीर्घ rate)
अणु
	अगर (request_irq(INT_TIMER1, omap_mpu_समयr1_पूर्णांकerrupt,
			IRQF_TIMER | IRQF_IRQPOLL, "mpu_timer1", शून्य))
		pr_err("Failed to request irq %d (mpu_timer1)\n", INT_TIMER1);
	omap_mpu_समयr_start(0, (rate / HZ) - 1, 1);

	घड़ीevent_mpu_समयr1.cpumask = cpumask_of(0);
	घड़ीevents_config_and_रेजिस्टर(&घड़ीevent_mpu_समयr1, rate,
					1, -1);
पूर्ण


/*
 * ---------------------------------------------------------------------------
 * MPU समयr 2 ... मुक्त running 32-bit घड़ी source and scheduler घड़ी
 * ---------------------------------------------------------------------------
 */

अटल u64 notrace omap_mpu_पढ़ो_sched_घड़ी(व्योम)
अणु
	वापस ~omap_mpu_समयr_पढ़ो(1);
पूर्ण

अटल व्योम __init omap_init_घड़ीsource(अचिन्हित दीर्घ rate)
अणु
	omap_mpu_समयr_regs_t __iomem *समयr = omap_mpu_समयr_base(1);
	अटल अक्षर err[] __initdata = KERN_ERR
			"%s: can't register clocksource!\n";

	omap_mpu_समयr_start(1, ~0, 1);
	sched_घड़ी_रेजिस्टर(omap_mpu_पढ़ो_sched_घड़ी, 32, rate);

	अगर (घड़ीsource_mmio_init(&समयr->पढ़ो_tim, "mpu_timer2", rate,
			300, 32, घड़ीsource_mmio_पढ़ोl_करोwn))
		prपूर्णांकk(err, "mpu_timer2");
पूर्ण

अटल व्योम __init omap_mpu_समयr_init(व्योम)
अणु
	काष्ठा clk	*ck_ref = clk_get(शून्य, "ck_ref");
	अचिन्हित दीर्घ	rate;

	BUG_ON(IS_ERR(ck_ref));

	rate = clk_get_rate(ck_ref);
	clk_put(ck_ref);

	/* PTV = 0 */
	rate /= 2;

	omap_init_mpu_समयr(rate);
	omap_init_घड़ीsource(rate);
पूर्ण

#अन्यथा
अटल अंतरभूत व्योम omap_mpu_समयr_init(व्योम)
अणु
	pr_err("Bogus timer, should not happen\n");
पूर्ण
#पूर्ण_अगर	/* CONFIG_OMAP_MPU_TIMER */

/*
 * ---------------------------------------------------------------------------
 * Timer initialization
 * ---------------------------------------------------------------------------
 */
व्योम __init omap1_समयr_init(व्योम)
अणु
	अगर (omap_32k_समयr_init() != 0)
		omap_mpu_समयr_init();
पूर्ण
