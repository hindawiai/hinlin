<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  Copyright (C) 1995  Linus Torvalds
 *  Adapted from 'alpha' version by Gary Thomas
 *  Modअगरied by Cort Dougan (cort@cs.nmt.edu)
 *  Modअगरied क्रम MBX using prep/chrp/pmac functions by Dan (dmalek@jlc.net)
 *  Further modअगरied क्रम generic 8xx by Dan.
 */

/*
 * bootup setup stuff..
 */

#समावेश <linux/kernel.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/init.h>
#समावेश <linux/समय.स>
#समावेश <linux/rtc.h>
#समावेश <linux/fsl_devices.h>

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/8xx_immap.h>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/fs_pd.h>
#समावेश <mm/mmu_decl.h>

#समावेश "pic.h"

#समावेश "mpc8xx.h"

बाह्य पूर्णांक cpm_pic_init(व्योम);
बाह्य पूर्णांक cpm_get_irq(व्योम);

/* A place holder क्रम समय base पूर्णांकerrupts, अगर they are ever enabled. */
अटल irqवापस_t समयbase_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev)
अणु
	prपूर्णांकk ("timebase_interrupt()\n");

	वापस IRQ_HANDLED;
पूर्ण

/* per-board overridable init_पूर्णांकernal_rtc() function. */
व्योम __init __attribute__ ((weak))
init_पूर्णांकernal_rtc(व्योम)
अणु
	sit8xx_t __iomem *sys_पंचांगr = immr_map(im_sit);

	/* Disable the RTC one second and alarm पूर्णांकerrupts. */
	clrbits16(&sys_पंचांगr->sit_rtcsc, (RTCSC_SIE | RTCSC_ALE));

	/* Enable the RTC */
	setbits16(&sys_पंचांगr->sit_rtcsc, (RTCSC_RTF | RTCSC_RTE));
	immr_unmap(sys_पंचांगr);
पूर्ण

अटल पूर्णांक __init get_freq(अक्षर *name, अचिन्हित दीर्घ *val)
अणु
	काष्ठा device_node *cpu;
	स्थिर अचिन्हित पूर्णांक *fp;
	पूर्णांक found = 0;

	/* The cpu node should have समयbase and घड़ी frequency properties */
	cpu = of_get_cpu_node(0, शून्य);

	अगर (cpu) अणु
		fp = of_get_property(cpu, name, शून्य);
		अगर (fp) अणु
			found = 1;
			*val = *fp;
		पूर्ण

		of_node_put(cpu);
	पूर्ण

	वापस found;
पूर्ण

/* The decrementer counts at the प्रणाली (पूर्णांकernal) घड़ी frequency भागided by
 * sixteen, or बाह्यal oscillator भागided by four.  We क्रमce the processor
 * to use प्रणाली घड़ी भागided by sixteen.
 */
व्योम __init mpc8xx_calibrate_decr(व्योम)
अणु
	काष्ठा device_node *cpu;
	cark8xx_t __iomem *clk_r1;
	car8xx_t __iomem *clk_r2;
	sitk8xx_t __iomem *sys_पंचांगr1;
	sit8xx_t __iomem *sys_पंचांगr2;
	पूर्णांक irq, virq;

	clk_r1 = immr_map(im_clkrstk);

	/* Unlock the SCCR. */
	out_be32(&clk_r1->cark_sccrk, ~KAPWR_KEY);
	out_be32(&clk_r1->cark_sccrk, KAPWR_KEY);
	immr_unmap(clk_r1);

	/* Force all 8xx processors to use भागide by 16 processor घड़ी. */
	clk_r2 = immr_map(im_clkrst);
	setbits32(&clk_r2->car_sccr, 0x02000000);
	immr_unmap(clk_r2);

	/* Processor frequency is MHz.
	 */
	ppc_proc_freq = 50000000;
	अगर (!get_freq("clock-frequency", &ppc_proc_freq))
		prपूर्णांकk(KERN_ERR "WARNING: Estimating processor frequency "
		                "(not found)\n");

	ppc_tb_freq = ppc_proc_freq / 16;
	prपूर्णांकk("Decrementer Frequency = 0x%lx\n", ppc_tb_freq);

	/* Perक्रमm some more समयr/समयbase initialization.  This used
	 * to be करोne अन्यथाwhere, but other changes caused it to get
	 * called more than once....that is a bad thing.
	 *
	 * First, unlock all of the रेजिस्टरs we are going to modअगरy.
	 * To protect them from corruption during घातer करोwn, रेजिस्टरs
	 * that are मुख्यtained by keep alive घातer are "locked".  To
	 * modअगरy these रेजिस्टरs we have to ग_लिखो the key value to
	 * the key location associated with the रेजिस्टर.
	 * Some boards घातer up with these unlocked, जबतक others
	 * are locked.  Writing anything (including the unlock code?)
	 * to the unlocked रेजिस्टरs will lock them again.  So, here
	 * we guarantee the रेजिस्टरs are locked, then we unlock them
	 * क्रम our use.
	 */
	sys_पंचांगr1 = immr_map(im_sitk);
	out_be32(&sys_पंचांगr1->sitk_tbscrk, ~KAPWR_KEY);
	out_be32(&sys_पंचांगr1->sitk_rtcsck, ~KAPWR_KEY);
	out_be32(&sys_पंचांगr1->sitk_tbk, ~KAPWR_KEY);
	out_be32(&sys_पंचांगr1->sitk_tbscrk, KAPWR_KEY);
	out_be32(&sys_पंचांगr1->sitk_rtcsck, KAPWR_KEY);
	out_be32(&sys_पंचांगr1->sitk_tbk, KAPWR_KEY);
	immr_unmap(sys_पंचांगr1);

	init_पूर्णांकernal_rtc();

	/* Enabling the decrementer also enables the समयbase पूर्णांकerrupts
	 * (or from the other poपूर्णांक of view, to get decrementer पूर्णांकerrupts
	 * we have to enable the समयbase).  The decrementer पूर्णांकerrupt
	 * is wired पूर्णांकo the vector table, nothing to करो here क्रम that.
	 */
	cpu = of_get_cpu_node(0, शून्य);
	virq= irq_of_parse_and_map(cpu, 0);
	of_node_put(cpu);
	irq = virq_to_hw(virq);

	sys_पंचांगr2 = immr_map(im_sit);
	out_be16(&sys_पंचांगr2->sit_tbscr, ((1 << (7 - (irq/2))) << 8) |
					(TBSCR_TBF | TBSCR_TBE));
	immr_unmap(sys_पंचांगr2);

	अगर (request_irq(virq, समयbase_पूर्णांकerrupt, IRQF_NO_THREAD, "tbint",
			शून्य))
		panic("Could not allocate timer IRQ!");
पूर्ण

/* The RTC on the MPC8xx is an पूर्णांकernal रेजिस्टर.
 * We want to protect this during घातer करोwn, so we need to unlock,
 * modअगरy, and re-lock.
 */

पूर्णांक mpc8xx_set_rtc_समय(काष्ठा rtc_समय *पंचांग)
अणु
	sitk8xx_t __iomem *sys_पंचांगr1;
	sit8xx_t __iomem *sys_पंचांगr2;
	समय64_t समय;

	sys_पंचांगr1 = immr_map(im_sitk);
	sys_पंचांगr2 = immr_map(im_sit);
	समय = rtc_पंचांग_to_समय64(पंचांग);

	out_be32(&sys_पंचांगr1->sitk_rtck, KAPWR_KEY);
	out_be32(&sys_पंचांगr2->sit_rtc, (u32)समय);
	out_be32(&sys_पंचांगr1->sitk_rtck, ~KAPWR_KEY);

	immr_unmap(sys_पंचांगr2);
	immr_unmap(sys_पंचांगr1);
	वापस 0;
पूर्ण

व्योम mpc8xx_get_rtc_समय(काष्ठा rtc_समय *पंचांग)
अणु
	अचिन्हित दीर्घ data;
	sit8xx_t __iomem *sys_पंचांगr = immr_map(im_sit);

	/* Get समय from the RTC. */
	data = in_be32(&sys_पंचांगr->sit_rtc);
	rtc_समय64_to_पंचांग(data, पंचांग);
	immr_unmap(sys_पंचांगr);
	वापस;
पूर्ण

व्योम __noवापस mpc8xx_restart(अक्षर *cmd)
अणु
	car8xx_t __iomem *clk_r = immr_map(im_clkrst);


	local_irq_disable();

	setbits32(&clk_r->car_plprcr, 0x00000080);
	/* Clear the ME bit in MSR to cause checkstop on machine check
	*/
	mपंचांगsr(mfmsr() & ~0x1000);

	in_8(&clk_r->res[0]);
	panic("Restart failed\n");
पूर्ण

अटल व्योम cpm_cascade(काष्ठा irq_desc *desc)
अणु
	generic_handle_irq(cpm_get_irq());
पूर्ण

/* Initialize the पूर्णांकernal पूर्णांकerrupt controllers.  The number of
 * पूर्णांकerrupts supported can vary with the processor type, and the
 * 82xx family can have up to 64.
 * External पूर्णांकerrupts can be either edge or level triggered, and
 * need to be initialized by the appropriate driver.
 */
व्योम __init mpc8xx_pics_init(व्योम)
अणु
	पूर्णांक irq;

	अगर (mpc8xx_pic_init()) अणु
		prपूर्णांकk(KERN_ERR "Failed interrupt 8xx controller  initialization\n");
		वापस;
	पूर्ण

	irq = cpm_pic_init();
	अगर (irq)
		irq_set_chained_handler(irq, cpm_cascade);
पूर्ण
