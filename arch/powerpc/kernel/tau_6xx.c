<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * temp.c	Thermal management क्रम cpu's with Thermal Assist Units
 *
 * Written by Troy Benjegerdes <hozer@drgw.net>
 *
 * TODO:
 * dynamic घातer management to limit peak CPU temp (using ICTC)
 * calibration???
 *
 * Silly, crazy ideas: use cpu load (from scheduler) and ICTC to extend battery
 * lअगरe in portables, and add a 'performance/watt' metric somewhere in /proc
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/param.h>
#समावेश <linux/माला.स>
#समावेश <linux/mm.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/workqueue.h>

#समावेश <यंत्र/पूर्णांकerrupt.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/reg.h>
#समावेश <यंत्र/nvram.h>
#समावेश <यंत्र/cache.h>
#समावेश <यंत्र/8xx_immap.h>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/यंत्र-prototypes.h>

#समावेश "setup.h"

अटल काष्ठा tau_temp
अणु
	पूर्णांक पूर्णांकerrupts;
	अचिन्हित अक्षर low;
	अचिन्हित अक्षर high;
	अचिन्हित अक्षर grew;
पूर्ण tau[NR_CPUS];

अटल bool tau_पूर्णांक_enable;

/* TODO: put these in a /proc पूर्णांकerface, with some sanity checks, and maybe
 * dynamic adjusपंचांगent to minimize # of पूर्णांकerrupts */
/* configurable values क्रम step size and how much to expand the winकरोw when
 * we get an पूर्णांकerrupt. These are based on the limit that was out of range */
#घोषणा step_size		2	/* step size when temp goes out of range */
#घोषणा winकरोw_expand		1	/* expand the winकरोw by this much */
/* configurable values क्रम shrinking the winकरोw */
#घोषणा shrink_समयr	2000	/* period between shrinking the winकरोw */
#घोषणा min_winकरोw	2	/* minimum winकरोw size, degrees C */

अटल व्योम set_thresholds(अचिन्हित दीर्घ cpu)
अणु
	u32 maybe_tie = tau_पूर्णांक_enable ? THRM1_TIE : 0;

	/* setup THRM1, threshold, valid bit, पूर्णांकerrupt when below threshold */
	mtspr(SPRN_THRM1, THRM1_THRES(tau[cpu].low) | THRM1_V | maybe_tie | THRM1_TID);

	/* setup THRM2, threshold, valid bit, पूर्णांकerrupt when above threshold */
	mtspr(SPRN_THRM2, THRM1_THRES(tau[cpu].high) | THRM1_V | maybe_tie);
पूर्ण

अटल व्योम TAUupdate(पूर्णांक cpu)
अणु
	u32 thrm;
	u32 bits = THRM1_TIV | THRM1_TIN | THRM1_V;

	/* अगर both thresholds are crossed, the step_sizes cancel out
	 * and the winकरोw winds up getting expanded twice. */
	thrm = mfspr(SPRN_THRM1);
	अगर ((thrm & bits) == bits) अणु
		mtspr(SPRN_THRM1, 0);

		अगर (tau[cpu].low >= step_size) अणु
			tau[cpu].low -= step_size;
			tau[cpu].high -= (step_size - winकरोw_expand);
		पूर्ण
		tau[cpu].grew = 1;
		pr_debug("%s: low threshold crossed\n", __func__);
	पूर्ण
	thrm = mfspr(SPRN_THRM2);
	अगर ((thrm & bits) == bits) अणु
		mtspr(SPRN_THRM2, 0);

		अगर (tau[cpu].high <= 127 - step_size) अणु
			tau[cpu].low += (step_size - winकरोw_expand);
			tau[cpu].high += step_size;
		पूर्ण
		tau[cpu].grew = 1;
		pr_debug("%s: high threshold crossed\n", __func__);
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_TAU_INT
/*
 * TAU पूर्णांकerrupts - called when we have a thermal assist unit पूर्णांकerrupt
 * with पूर्णांकerrupts disabled
 */

DEFINE_INTERRUPT_HANDLER_ASYNC(TAUException)
अणु
	पूर्णांक cpu = smp_processor_id();

	tau[cpu].पूर्णांकerrupts++;

	TAUupdate(cpu);
पूर्ण
#पूर्ण_अगर /* CONFIG_TAU_INT */

अटल व्योम tau_समयout(व्योम * info)
अणु
	पूर्णांक cpu;
	पूर्णांक size;
	पूर्णांक shrink;

	cpu = smp_processor_id();

	अगर (!tau_पूर्णांक_enable)
		TAUupdate(cpu);

	/* Stop thermal sensor comparisons and पूर्णांकerrupts */
	mtspr(SPRN_THRM3, 0);

	size = tau[cpu].high - tau[cpu].low;
	अगर (size > min_winकरोw && ! tau[cpu].grew) अणु
		/* करो an exponential shrink of half the amount currently over size */
		shrink = (2 + size - min_winकरोw) / 4;
		अगर (shrink) अणु
			tau[cpu].low += shrink;
			tau[cpu].high -= shrink;
		पूर्ण अन्यथा अणु /* size must have been min_winकरोw + 1 */
			tau[cpu].low += 1;
#अगर 1 /* debug */
			अगर ((tau[cpu].high - tau[cpu].low) != min_winकरोw)अणु
				prपूर्णांकk(KERN_ERR "temp.c: line %d, logic error\n", __LINE__);
			पूर्ण
#पूर्ण_अगर
		पूर्ण
	पूर्ण

	tau[cpu].grew = 0;

	set_thresholds(cpu);

	/* Restart thermal sensor comparisons and पूर्णांकerrupts.
	 * The "PowerPC 740 and PowerPC 750 Microprocessor Datasheet"
	 * recommends that "the maximum value be set in THRM3 under all
	 * conditions."
	 */
	mtspr(SPRN_THRM3, THRM3_SITV(0x1fff) | THRM3_E);
पूर्ण

अटल काष्ठा workqueue_काष्ठा *tau_workq;

अटल व्योम tau_work_func(काष्ठा work_काष्ठा *work)
अणु
	msleep(shrink_समयr);
	on_each_cpu(tau_समयout, शून्य, 0);
	/* schedule ourselves to be run again */
	queue_work(tau_workq, work);
पूर्ण

DECLARE_WORK(tau_work, tau_work_func);

/*
 * setup the TAU
 *
 * Set things up to use THRM1 as a temperature lower bound, and THRM2 as an upper bound.
 * Start off at zero
 */

पूर्णांक tau_initialized = 0;

अटल व्योम __init TAU_init_smp(व्योम *info)
अणु
	अचिन्हित दीर्घ cpu = smp_processor_id();

	/* set these to a reasonable value and let the समयr shrink the
	 * winकरोw */
	tau[cpu].low = 5;
	tau[cpu].high = 120;

	set_thresholds(cpu);
पूर्ण

अटल पूर्णांक __init TAU_init(व्योम)
अणु
	/* We assume in SMP that अगर one CPU has TAU support, they
	 * all have it --BenH
	 */
	अगर (!cpu_has_feature(CPU_FTR_TAU)) अणु
		prपूर्णांकk("Thermal assist unit not available\n");
		tau_initialized = 0;
		वापस 1;
	पूर्ण

	tau_पूर्णांक_enable = IS_ENABLED(CONFIG_TAU_INT) &&
			 !म_भेद(cur_cpu_spec->platक्रमm, "ppc750");

	tau_workq = alloc_workqueue("tau", WQ_UNBOUND, 1, 0);
	अगर (!tau_workq)
		वापस -ENOMEM;

	on_each_cpu(TAU_init_smp, शून्य, 0);

	queue_work(tau_workq, &tau_work);

	pr_info("Thermal assist unit using %s, shrink_timer: %d ms\n",
		tau_पूर्णांक_enable ? "interrupts" : "workqueue", shrink_समयr);
	tau_initialized = 1;

	वापस 0;
पूर्ण

__initcall(TAU_init);

/*
 * वापस current temp
 */

u32 cpu_temp_both(अचिन्हित दीर्घ cpu)
अणु
	वापस ((tau[cpu].high << 16) | tau[cpu].low);
पूर्ण

u32 cpu_temp(अचिन्हित दीर्घ cpu)
अणु
	वापस ((tau[cpu].high + tau[cpu].low) / 2);
पूर्ण

u32 tau_पूर्णांकerrupts(अचिन्हित दीर्घ cpu)
अणु
	वापस (tau[cpu].पूर्णांकerrupts);
पूर्ण
