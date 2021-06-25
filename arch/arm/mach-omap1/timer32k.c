<शैली गुरु>
/*
 * linux/arch/arm/mach-omap1/समयr32k.c
 *
 * OMAP 32K Timer
 *
 * Copyright (C) 2004 - 2005 Nokia Corporation
 * Partial समयr reग_लिखो and additional dynamic tick समयr support by
 * Tony Lindgen <tony@atomide.com> and
 * Tuukka Tikkanen <tuukka.tikkanen@elektrobit.com>
 * OMAP Dual-mode समयr framework support by Timo Teras
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
#समावेश <linux/sched.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/err.h>
#समावेश <linux/clk.h>
#समावेश <linux/घड़ीsource.h>
#समावेश <linux/घड़ीchips.h>
#समावेश <linux/पन.स>

#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/mach/irq.h>
#समावेश <यंत्र/mach/समय.स>

#समावेश <plat/counter-32k.h>

#समावेश <mach/hardware.h>

#समावेश "common.h"

/*
 * ---------------------------------------------------------------------------
 * 32KHz OS समयr
 *
 * This currently works only on 16xx, as 1510 करोes not have the continuous
 * 32KHz synchronous समयr. The 32KHz synchronous समयr is used to keep track
 * of समय in addition to the 32KHz OS समयr. Using only the 32KHz OS समयr
 * on 1510 would be possible, but the समयr would not be as accurate as
 * with the 32KHz synchronized समयr.
 * ---------------------------------------------------------------------------
 */

/* 16xx specअगरic defines */
#घोषणा OMAP1_32K_TIMER_BASE		0xfffb9000
#घोषणा OMAP1_32KSYNC_TIMER_BASE	0xfffbc400
#घोषणा OMAP1_32K_TIMER_CR		0x08
#घोषणा OMAP1_32K_TIMER_TVR		0x00
#घोषणा OMAP1_32K_TIMER_TCR		0x04

#घोषणा OMAP_32K_TICKS_PER_SEC		(32768)

/*
 * TRM says 1 / HZ = ( TVR + 1) / 32768, so TRV = (32768 / HZ) - 1
 * so with HZ = 128, TVR = 255.
 */
#घोषणा OMAP_32K_TIMER_TICK_PERIOD	((OMAP_32K_TICKS_PER_SEC / HZ) - 1)

#घोषणा JIFFIES_TO_HW_TICKS(nr_jअगरfies, घड़ी_rate)			\
				(((nr_jअगरfies) * (घड़ी_rate)) / HZ)

अटल अंतरभूत व्योम omap_32k_समयr_ग_लिखो(पूर्णांक val, पूर्णांक reg)
अणु
	omap_ग_लिखोw(val, OMAP1_32K_TIMER_BASE + reg);
पूर्ण

अटल अंतरभूत व्योम omap_32k_समयr_start(अचिन्हित दीर्घ load_val)
अणु
	अगर (!load_val)
		load_val = 1;
	omap_32k_समयr_ग_लिखो(load_val, OMAP1_32K_TIMER_TVR);
	omap_32k_समयr_ग_लिखो(0x0f, OMAP1_32K_TIMER_CR);
पूर्ण

अटल अंतरभूत व्योम omap_32k_समयr_stop(व्योम)
अणु
	omap_32k_समयr_ग_लिखो(0x0, OMAP1_32K_TIMER_CR);
पूर्ण

#घोषणा omap_32k_समयr_ack_irq()

अटल पूर्णांक omap_32k_समयr_set_next_event(अचिन्हित दीर्घ delta,
					 काष्ठा घड़ी_event_device *dev)
अणु
	omap_32k_समयr_start(delta);

	वापस 0;
पूर्ण

अटल पूर्णांक omap_32k_समयr_shutकरोwn(काष्ठा घड़ी_event_device *evt)
अणु
	omap_32k_समयr_stop();
	वापस 0;
पूर्ण

अटल पूर्णांक omap_32k_समयr_set_periodic(काष्ठा घड़ी_event_device *evt)
अणु
	omap_32k_समयr_stop();
	omap_32k_समयr_start(OMAP_32K_TIMER_TICK_PERIOD);
	वापस 0;
पूर्ण

अटल काष्ठा घड़ी_event_device घड़ीevent_32k_समयr = अणु
	.name			= "32k-timer",
	.features		= CLOCK_EVT_FEAT_PERIODIC |
				  CLOCK_EVT_FEAT_ONESHOT,
	.set_next_event		= omap_32k_समयr_set_next_event,
	.set_state_shutकरोwn	= omap_32k_समयr_shutकरोwn,
	.set_state_periodic	= omap_32k_समयr_set_periodic,
	.set_state_oneshot	= omap_32k_समयr_shutकरोwn,
	.tick_resume		= omap_32k_समयr_shutकरोwn,
पूर्ण;

अटल irqवापस_t omap_32k_समयr_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा घड़ी_event_device *evt = &घड़ीevent_32k_समयr;
	omap_32k_समयr_ack_irq();

	evt->event_handler(evt);

	वापस IRQ_HANDLED;
पूर्ण

अटल __init व्योम omap_init_32k_समयr(व्योम)
अणु
	अगर (request_irq(INT_OS_TIMER, omap_32k_समयr_पूर्णांकerrupt,
			IRQF_TIMER | IRQF_IRQPOLL, "32KHz timer", शून्य))
		pr_err("Failed to request irq %d(32KHz timer)\n", INT_OS_TIMER);

	घड़ीevent_32k_समयr.cpumask = cpumask_of(0);
	घड़ीevents_config_and_रेजिस्टर(&घड़ीevent_32k_समयr,
					OMAP_32K_TICKS_PER_SEC, 1, 0xfffffffe);
पूर्ण

/*
 * ---------------------------------------------------------------------------
 * Timer initialization
 * ---------------------------------------------------------------------------
 */
पूर्णांक __init omap_32k_समयr_init(व्योम)
अणु
	पूर्णांक ret = -ENODEV;

	अगर (cpu_is_omap16xx()) अणु
		व्योम __iomem *base;
		काष्ठा clk *sync32k_ick;

		base = ioremap(OMAP1_32KSYNC_TIMER_BASE, SZ_1K);
		अगर (!base) अणु
			pr_err("32k_counter: failed to map base addr\n");
			वापस -ENODEV;
		पूर्ण

		sync32k_ick = clk_get(शून्य, "omap_32ksync_ick");
		अगर (!IS_ERR(sync32k_ick))
			clk_enable(sync32k_ick);

		ret = omap_init_घड़ीsource_32k(base);
	पूर्ण

	अगर (!ret)
		omap_init_32k_समयr();

	वापस ret;
पूर्ण
