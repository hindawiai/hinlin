<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/arch/arm/mach-pxa/pxa25x.c
 *
 *  Author:	Nicolas Pitre
 *  Created:	Jun 15, 2001
 *  Copyright:	MontaVista Software Inc.
 *
 * Code specअगरic to PXA21x/25x/26x variants.
 *
 * Since this file should be linked beक्रमe any other machine specअगरic file,
 * the __initcall() here will be executed first.  This serves as शेष
 * initialization stuff क्रम PXA machines which can be overridden later अगर
 * need be.
 */
#समावेश <linux/dmaengine.h>
#समावेश <linux/dma/pxa-dma.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/gpio-pxa.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/suspend.h>
#समावेश <linux/syscore_ops.h>
#समावेश <linux/irq.h>
#समावेश <linux/irqchip.h>
#समावेश <linux/platक्रमm_data/mmp_dma.h>

#समावेश <यंत्र/mach/map.h>
#समावेश <यंत्र/suspend.h>
#समावेश <mach/hardware.h>
#समावेश <mach/irqs.h>
#समावेश "pxa25x.h"
#समावेश <mach/reset.h>
#समावेश "pm.h"
#समावेश <mach/dma.h>
#समावेश <mach/smemc.h>

#समावेश "generic.h"
#समावेश "devices.h"

/*
 * Various घड़ी factors driven by the CCCR रेजिस्टर.
 */

#अगर_घोषित CONFIG_PM

#घोषणा SAVE(x)		sleep_save[SLEEP_SAVE_##x] = x
#घोषणा RESTORE(x)	x = sleep_save[SLEEP_SAVE_##x]

/*
 * List of global PXA peripheral रेजिस्टरs to preserve.
 * More ones like CP and general purpose रेजिस्टर values are preserved
 * with the stack poपूर्णांकer in sleep.S.
 */
क्रमागत अणु
	SLEEP_SAVE_PSTR,
	SLEEP_SAVE_COUNT
पूर्ण;


अटल व्योम pxa25x_cpu_pm_save(अचिन्हित दीर्घ *sleep_save)
अणु
	SAVE(PSTR);
पूर्ण

अटल व्योम pxa25x_cpu_pm_restore(अचिन्हित दीर्घ *sleep_save)
अणु
	RESTORE(PSTR);
पूर्ण

अटल व्योम pxa25x_cpu_pm_enter(suspend_state_t state)
अणु
	/* Clear reset status */
	RCSR = RCSR_HWR | RCSR_WDR | RCSR_SMR | RCSR_GPR;

	चयन (state) अणु
	हाल PM_SUSPEND_MEM:
		cpu_suspend(PWRMODE_SLEEP, pxa25x_finish_suspend);
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक pxa25x_cpu_pm_prepare(व्योम)
अणु
	/* set resume वापस address */
	PSPR = __pa_symbol(cpu_resume);
	वापस 0;
पूर्ण

अटल व्योम pxa25x_cpu_pm_finish(व्योम)
अणु
	/* ensure not to come back here अगर it wasn't पूर्णांकended */
	PSPR = 0;
पूर्ण

अटल काष्ठा pxa_cpu_pm_fns pxa25x_cpu_pm_fns = अणु
	.save_count	= SLEEP_SAVE_COUNT,
	.valid		= suspend_valid_only_mem,
	.save		= pxa25x_cpu_pm_save,
	.restore	= pxa25x_cpu_pm_restore,
	.enter		= pxa25x_cpu_pm_enter,
	.prepare	= pxa25x_cpu_pm_prepare,
	.finish		= pxa25x_cpu_pm_finish,
पूर्ण;

अटल व्योम __init pxa25x_init_pm(व्योम)
अणु
	pxa_cpu_pm_fns = &pxa25x_cpu_pm_fns;
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम pxa25x_init_pm(व्योम) अणुपूर्ण
#पूर्ण_अगर

/* PXA25x: supports wakeup from GPIO0..GPIO15 and RTC alarm
 */

अटल पूर्णांक pxa25x_set_wake(काष्ठा irq_data *d, अचिन्हित पूर्णांक on)
अणु
	पूर्णांक gpio = pxa_irq_to_gpio(d->irq);
	uपूर्णांक32_t mask = 0;

	अगर (gpio >= 0 && gpio < 85)
		वापस gpio_set_wake(gpio, on);

	अगर (d->irq == IRQ_RTCAlrm) अणु
		mask = PWER_RTC;
		जाओ set_pwer;
	पूर्ण

	वापस -EINVAL;

set_pwer:
	अगर (on)
		PWER |= mask;
	अन्यथा
		PWER &=~mask;

	वापस 0;
पूर्ण

व्योम __init pxa25x_init_irq(व्योम)
अणु
	pxa_init_irq(32, pxa25x_set_wake);
पूर्ण

#अगर_घोषित CONFIG_CPU_PXA26x
व्योम __init pxa26x_init_irq(व्योम)
अणु
	pxa_init_irq(32, pxa25x_set_wake);
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक __init __init
pxa25x_dt_init_irq(काष्ठा device_node *node, काष्ठा device_node *parent)
अणु
	pxa_dt_irq_init(pxa25x_set_wake);
	set_handle_irq(icip_handle_irq);

	वापस 0;
पूर्ण
IRQCHIP_DECLARE(pxa25x_पूर्णांकc, "marvell,pxa-intc", pxa25x_dt_init_irq);

अटल काष्ठा map_desc pxa25x_io_desc[] __initdata = अणु
	अणु	/* Mem Ctl */
		.भव	= (अचिन्हित दीर्घ)SMEMC_VIRT,
		.pfn		= __phys_to_pfn(PXA2XX_SMEMC_BASE),
		.length		= SMEMC_SIZE,
		.type		= MT_DEVICE
	पूर्ण, अणु	/* UNCACHED_PHYS_0 */
		.भव	= UNCACHED_PHYS_0,
		.pfn		= __phys_to_pfn(0x00000000),
		.length		= UNCACHED_PHYS_0_SIZE,
		.type		= MT_DEVICE
	पूर्ण,
पूर्ण;

व्योम __init pxa25x_map_io(व्योम)
अणु
	pxa_map_io();
	iotable_init(ARRAY_AND_SIZE(pxa25x_io_desc));
	pxa25x_get_clk_frequency_khz(1);
पूर्ण

अटल काष्ठा pxa_gpio_platक्रमm_data pxa25x_gpio_info __initdata = अणु
	.irq_base	= PXA_GPIO_TO_IRQ(0),
	.gpio_set_wake	= gpio_set_wake,
पूर्ण;

अटल काष्ठा platक्रमm_device *pxa25x_devices[] __initdata = अणु
	&pxa25x_device_udc,
	&pxa_device_pmu,
	&pxa_device_i2s,
	&sa1100_device_rtc,
	&pxa25x_device_ssp,
	&pxa25x_device_nssp,
	&pxa25x_device_assp,
	&pxa25x_device_pwm0,
	&pxa25x_device_pwm1,
	&pxa_device_asoc_platक्रमm,
पूर्ण;

अटल स्थिर काष्ठा dma_slave_map pxa25x_slave_map[] = अणु
	/* PXA25x, PXA27x and PXA3xx common entries */
	अणु "pxa2xx-ac97", "pcm_pcm_mic_mono", PDMA_FILTER_PARAM(LOWEST, 8) पूर्ण,
	अणु "pxa2xx-ac97", "pcm_pcm_aux_mono_in", PDMA_FILTER_PARAM(LOWEST, 9) पूर्ण,
	अणु "pxa2xx-ac97", "pcm_pcm_aux_mono_out",
	  PDMA_FILTER_PARAM(LOWEST, 10) पूर्ण,
	अणु "pxa2xx-ac97", "pcm_pcm_stereo_in", PDMA_FILTER_PARAM(LOWEST, 11) पूर्ण,
	अणु "pxa2xx-ac97", "pcm_pcm_stereo_out", PDMA_FILTER_PARAM(LOWEST, 12) पूर्ण,
	अणु "pxa-ssp-dai.1", "rx", PDMA_FILTER_PARAM(LOWEST, 13) पूर्ण,
	अणु "pxa-ssp-dai.1", "tx", PDMA_FILTER_PARAM(LOWEST, 14) पूर्ण,
	अणु "pxa-ssp-dai.2", "rx", PDMA_FILTER_PARAM(LOWEST, 15) पूर्ण,
	अणु "pxa-ssp-dai.2", "tx", PDMA_FILTER_PARAM(LOWEST, 16) पूर्ण,
	अणु "pxa2xx-ir", "rx", PDMA_FILTER_PARAM(LOWEST, 17) पूर्ण,
	अणु "pxa2xx-ir", "tx", PDMA_FILTER_PARAM(LOWEST, 18) पूर्ण,
	अणु "pxa2xx-mci.0", "rx", PDMA_FILTER_PARAM(LOWEST, 21) पूर्ण,
	अणु "pxa2xx-mci.0", "tx", PDMA_FILTER_PARAM(LOWEST, 22) पूर्ण,

	/* PXA25x specअगरic map */
	अणु "pxa25x-ssp.0", "rx", PDMA_FILTER_PARAM(LOWEST, 13) पूर्ण,
	अणु "pxa25x-ssp.0", "tx", PDMA_FILTER_PARAM(LOWEST, 14) पूर्ण,
	अणु "pxa25x-nssp.1", "rx", PDMA_FILTER_PARAM(LOWEST, 15) पूर्ण,
	अणु "pxa25x-nssp.1", "tx", PDMA_FILTER_PARAM(LOWEST, 16) पूर्ण,
	अणु "pxa25x-nssp.2", "rx", PDMA_FILTER_PARAM(LOWEST, 23) पूर्ण,
	अणु "pxa25x-nssp.2", "tx", PDMA_FILTER_PARAM(LOWEST, 24) पूर्ण,
पूर्ण;

अटल काष्ठा mmp_dma_platdata pxa25x_dma_pdata = अणु
	.dma_channels	= 16,
	.nb_requestors	= 40,
	.slave_map	= pxa25x_slave_map,
	.slave_map_cnt	= ARRAY_SIZE(pxa25x_slave_map),
पूर्ण;

अटल पूर्णांक __init pxa25x_init(व्योम)
अणु
	पूर्णांक ret = 0;

	अगर (cpu_is_pxa25x()) अणु

		reset_status = RCSR;

		pxa25x_init_pm();

		रेजिस्टर_syscore_ops(&pxa_irq_syscore_ops);
		रेजिस्टर_syscore_ops(&pxa2xx_mfp_syscore_ops);

		अगर (!of_have_populated_dt()) अणु
			pxa2xx_set_dmac_info(&pxa25x_dma_pdata);
			pxa_रेजिस्टर_device(&pxa25x_device_gpio, &pxa25x_gpio_info);
			ret = platक्रमm_add_devices(pxa25x_devices,
						   ARRAY_SIZE(pxa25x_devices));
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

postcore_initcall(pxa25x_init);
