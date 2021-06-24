<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/init.h>
#समावेश <linux/suspend.h>
#समावेश <linux/पन.स>
#समावेश <यंत्र/समय.स>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/mpc52xx.h>

/* these are defined in mpc52xx_sleep.S, and only used here */
बाह्य व्योम mpc52xx_deep_sleep(व्योम __iomem *sram, व्योम __iomem *sdram_regs,
		काष्ठा mpc52xx_cdm __iomem *, काष्ठा mpc52xx_पूर्णांकr __iomem*);
बाह्य व्योम mpc52xx_ds_sram(व्योम);
बाह्य स्थिर दीर्घ mpc52xx_ds_sram_size;
बाह्य व्योम mpc52xx_ds_cached(व्योम);
बाह्य स्थिर दीर्घ mpc52xx_ds_cached_size;

अटल व्योम __iomem *mbar;
अटल व्योम __iomem *sdram;
अटल काष्ठा mpc52xx_cdm __iomem *cdm;
अटल काष्ठा mpc52xx_पूर्णांकr __iomem *पूर्णांकr;
अटल काष्ठा mpc52xx_gpio_wkup __iomem *gpiow;
अटल व्योम __iomem *sram;
अटल पूर्णांक sram_size;

काष्ठा mpc52xx_suspend mpc52xx_suspend;

अटल पूर्णांक mpc52xx_pm_valid(suspend_state_t state)
अणु
	चयन (state) अणु
	हाल PM_SUSPEND_STANDBY:
		वापस 1;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

पूर्णांक mpc52xx_set_wakeup_gpio(u8 pin, u8 level)
अणु
	u16 पंचांगp;

	/* enable gpio */
	out_8(&gpiow->wkup_gpioe, in_8(&gpiow->wkup_gpioe) | (1 << pin));
	/* set as input */
	out_8(&gpiow->wkup_ddr, in_8(&gpiow->wkup_ddr) & ~(1 << pin));
	/* enable deep sleep पूर्णांकerrupt */
	out_8(&gpiow->wkup_पूर्णांकen, in_8(&gpiow->wkup_पूर्णांकen) | (1 << pin));
	/* low/high level creates wakeup पूर्णांकerrupt */
	पंचांगp = in_be16(&gpiow->wkup_itype);
	पंचांगp &= ~(0x3 << (pin * 2));
	पंचांगp |= (!level + 1) << (pin * 2);
	out_be16(&gpiow->wkup_itype, पंचांगp);
	/* master enable */
	out_8(&gpiow->wkup_maste, 1);

	वापस 0;
पूर्ण

पूर्णांक mpc52xx_pm_prepare(व्योम)
अणु
	काष्ठा device_node *np;
	स्थिर काष्ठा of_device_id immr_ids[] = अणु
		अणु .compatible = "fsl,mpc5200-immr", पूर्ण,
		अणु .compatible = "fsl,mpc5200b-immr", पूर्ण,
		अणु .type = "soc", .compatible = "mpc5200", पूर्ण, /* lite5200 */
		अणु .type = "builtin", .compatible = "mpc5200", पूर्ण, /* efika */
		अणुपूर्ण
	पूर्ण;
	काष्ठा resource res;

	/* map the whole रेजिस्टर space */
	np = of_find_matching_node(शून्य, immr_ids);

	अगर (of_address_to_resource(np, 0, &res)) अणु
		pr_err("mpc52xx_pm_prepare(): could not get IMMR address\n");
		of_node_put(np);
		वापस -ENOSYS;
	पूर्ण

	mbar = ioremap(res.start, 0xc000); /* we should map whole region including SRAM */

	of_node_put(np);
	अगर (!mbar) अणु
		pr_err("mpc52xx_pm_prepare(): could not map registers\n");
		वापस -ENOSYS;
	पूर्ण
	/* these offsets are from mpc5200 users manual */
	sdram	= mbar + 0x100;
	cdm	= mbar + 0x200;
	पूर्णांकr	= mbar + 0x500;
	gpiow	= mbar + 0xc00;
	sram	= mbar + 0x8000;	/* Those will be handled by the */
	sram_size = 0x4000;		/* bestcomm driver soon */

	/* call board suspend code, अगर applicable */
	अगर (mpc52xx_suspend.board_suspend_prepare)
		mpc52xx_suspend.board_suspend_prepare(mbar);
	अन्यथा अणु
		prपूर्णांकk(KERN_ALERT "%s: %i don't know how to wake up the board\n",
				__func__, __LINE__);
		जाओ out_unmap;
	पूर्ण

	वापस 0;

 out_unmap:
	iounmap(mbar);
	वापस -ENOSYS;
पूर्ण


अक्षर saved_sram[0x4000];

पूर्णांक mpc52xx_pm_enter(suspend_state_t state)
अणु
	u32 clk_enables;
	u32 msr, hid0;
	u32 पूर्णांकr_मुख्य_mask;
	व्योम __iomem * irq_0x500 = (व्योम __iomem *)CONFIG_KERNEL_START + 0x500;
	अचिन्हित दीर्घ irq_0x500_stop = (अचिन्हित दीर्घ)irq_0x500 + mpc52xx_ds_cached_size;
	अक्षर saved_0x500[0x600-0x500];

	अगर (WARN_ON(mpc52xx_ds_cached_size > माप(saved_0x500)))
		वापस -ENOMEM;

	/* disable all पूर्णांकerrupts in PIC */
	पूर्णांकr_मुख्य_mask = in_be32(&पूर्णांकr->मुख्य_mask);
	out_be32(&पूर्णांकr->मुख्य_mask, पूर्णांकr_मुख्य_mask | 0x1ffff);

	/* करोn't let DEC expire any समय soon */
	mtspr(SPRN_DEC, 0x7fffffff);

	/* save SRAM */
	स_नकल(saved_sram, sram, sram_size);

	/* copy low level suspend code to sram */
	स_नकल(sram, mpc52xx_ds_sram, mpc52xx_ds_sram_size);

	out_8(&cdm->ccs_sleep_enable, 1);
	out_8(&cdm->osc_sleep_enable, 1);
	out_8(&cdm->ccs_qreq_test, 1);

	/* disable all but SDRAM and bestcomm (SRAM) घड़ीs */
	clk_enables = in_be32(&cdm->clk_enables);
	out_be32(&cdm->clk_enables, clk_enables & 0x00088000);

	/* disable घातer management */
	msr = mfmsr();
	mपंचांगsr(msr & ~MSR_POW);

	/* enable sleep mode, disable others */
	hid0 = mfspr(SPRN_HID0);
	mtspr(SPRN_HID0, (hid0 & ~(HID0_DOZE | HID0_NAP | HID0_DPM)) | HID0_SLEEP);

	/* save original, copy our irq handler, flush from dcache and invalidate icache */
	स_नकल(saved_0x500, irq_0x500, mpc52xx_ds_cached_size);
	स_नकल(irq_0x500, mpc52xx_ds_cached, mpc52xx_ds_cached_size);
	flush_icache_range((अचिन्हित दीर्घ)irq_0x500, irq_0x500_stop);

	/* call low-level sleep code */
	mpc52xx_deep_sleep(sram, sdram, cdm, पूर्णांकr);

	/* restore original irq handler */
	स_नकल(irq_0x500, saved_0x500, mpc52xx_ds_cached_size);
	flush_icache_range((अचिन्हित दीर्घ)irq_0x500, irq_0x500_stop);

	/* restore old घातer mode */
	mपंचांगsr(msr & ~MSR_POW);
	mtspr(SPRN_HID0, hid0);
	mपंचांगsr(msr);

	out_be32(&cdm->clk_enables, clk_enables);
	out_8(&cdm->ccs_sleep_enable, 0);
	out_8(&cdm->osc_sleep_enable, 0);

	/* restore SRAM */
	स_नकल(sram, saved_sram, sram_size);

	/* reenable पूर्णांकerrupts in PIC */
	out_be32(&पूर्णांकr->मुख्य_mask, पूर्णांकr_मुख्य_mask);

	वापस 0;
पूर्ण

व्योम mpc52xx_pm_finish(व्योम)
अणु
	/* call board resume code */
	अगर (mpc52xx_suspend.board_resume_finish)
		mpc52xx_suspend.board_resume_finish(mbar);

	iounmap(mbar);
पूर्ण

अटल स्थिर काष्ठा platक्रमm_suspend_ops mpc52xx_pm_ops = अणु
	.valid		= mpc52xx_pm_valid,
	.prepare	= mpc52xx_pm_prepare,
	.enter		= mpc52xx_pm_enter,
	.finish		= mpc52xx_pm_finish,
पूर्ण;

पूर्णांक __init mpc52xx_pm_init(व्योम)
अणु
	suspend_set_ops(&mpc52xx_pm_ops);
	वापस 0;
पूर्ण
