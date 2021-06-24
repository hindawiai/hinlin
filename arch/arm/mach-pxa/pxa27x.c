<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/arch/arm/mach-pxa/pxa27x.c
 *
 *  Author:	Nicolas Pitre
 *  Created:	Nov 05, 2002
 *  Copyright:	MontaVista Software Inc.
 *
 * Code specअगरic to PXA27x aka Bulverde.
 */
#समावेश <linux/dmaengine.h>
#समावेश <linux/dma/pxa-dma.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/gpio-pxa.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/irqchip.h>
#समावेश <linux/suspend.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/syscore_ops.h>
#समावेश <linux/पन.स>
#समावेश <linux/irq.h>
#समावेश <linux/platक्रमm_data/i2c-pxa.h>
#समावेश <linux/platक्रमm_data/mmp_dma.h>

#समावेश <यंत्र/mach/map.h>
#समावेश <mach/hardware.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/suspend.h>
#समावेश <mach/irqs.h>
#समावेश "pxa27x.h"
#समावेश <mach/reset.h>
#समावेश <linux/platक्रमm_data/usb-ohci-pxa27x.h>
#समावेश "pm.h"
#समावेश <mach/dma.h>
#समावेश <mach/smemc.h>

#समावेश "generic.h"
#समावेश "devices.h"
#समावेश <linux/clk-provider.h>
#समावेश <linux/clkdev.h>

व्योम pxa27x_clear_otgph(व्योम)
अणु
	अगर (cpu_is_pxa27x() && (PSSR & PSSR_OTGPH))
		PSSR |= PSSR_OTGPH;
पूर्ण
EXPORT_SYMBOL(pxa27x_clear_otgph);

अटल अचिन्हित दीर्घ ac97_reset_config[] = अणु
	GPIO113_AC97_nRESET_GPIO_HIGH,
	GPIO113_AC97_nRESET,
	GPIO95_AC97_nRESET_GPIO_HIGH,
	GPIO95_AC97_nRESET,
पूर्ण;

व्योम pxa27x_configure_ac97reset(पूर्णांक reset_gpio, bool to_gpio)
अणु
	/*
	 * This helper function is used to work around a bug in the pxa27x's
	 * ac97 controller during a warm reset.  The configuration of the
	 * reset_gpio is changed as follows:
	 * to_gpio == true: configured to generic output gpio and driven high
	 * to_gpio == false: configured to ac97 controller alt fn AC97_nRESET
	 */

	अगर (reset_gpio == 113)
		pxa2xx_mfp_config(to_gpio ? &ac97_reset_config[0] :
				  &ac97_reset_config[1], 1);

	अगर (reset_gpio == 95)
		pxa2xx_mfp_config(to_gpio ? &ac97_reset_config[2] :
				  &ac97_reset_config[3], 1);
पूर्ण
EXPORT_SYMBOL_GPL(pxa27x_configure_ac97reset);

#अगर_घोषित CONFIG_PM

#घोषणा SAVE(x)		sleep_save[SLEEP_SAVE_##x] = x
#घोषणा RESTORE(x)	x = sleep_save[SLEEP_SAVE_##x]

/*
 * allow platक्रमms to override शेष PWRMODE setting used क्रम PM_SUSPEND_MEM
 */
अटल अचिन्हित पूर्णांक pwrmode = PWRMODE_SLEEP;

पूर्णांक pxa27x_set_pwrmode(अचिन्हित पूर्णांक mode)
अणु
	चयन (mode) अणु
	हाल PWRMODE_SLEEP:
	हाल PWRMODE_DEEPSLEEP:
		pwrmode = mode;
		वापस 0;
	पूर्ण

	वापस -EINVAL;
पूर्ण

/*
 * List of global PXA peripheral रेजिस्टरs to preserve.
 * More ones like CP and general purpose रेजिस्टर values are preserved
 * with the stack poपूर्णांकer in sleep.S.
 */
क्रमागत अणु
	SLEEP_SAVE_PSTR,
	SLEEP_SAVE_MDREFR,
	SLEEP_SAVE_PCFR,
	SLEEP_SAVE_COUNT
पूर्ण;

व्योम pxa27x_cpu_pm_save(अचिन्हित दीर्घ *sleep_save)
अणु
	sleep_save[SLEEP_SAVE_MDREFR] = __raw_पढ़ोl(MDREFR);
	SAVE(PCFR);

	SAVE(PSTR);
पूर्ण

व्योम pxa27x_cpu_pm_restore(अचिन्हित दीर्घ *sleep_save)
अणु
	__raw_ग_लिखोl(sleep_save[SLEEP_SAVE_MDREFR], MDREFR);
	RESTORE(PCFR);

	PSSR = PSSR_RDH | PSSR_PH;

	RESTORE(PSTR);
पूर्ण

व्योम pxa27x_cpu_pm_enter(suspend_state_t state)
अणु
	बाह्य व्योम pxa_cpu_standby(व्योम);
#अगर_अघोषित CONFIG_IWMMXT
	u64 acc0;

	यंत्र अस्थिर(".arch_extension xscale\n\t"
		     "mra %Q0, %R0, acc0" : "=r" (acc0));
#पूर्ण_अगर

	/* ensure voltage-change sequencer not initiated, which hangs */
	PCFR &= ~PCFR_FVC;

	/* Clear edge-detect status रेजिस्टर. */
	PEDR = 0xDF12FE1B;

	/* Clear reset status */
	RCSR = RCSR_HWR | RCSR_WDR | RCSR_SMR | RCSR_GPR;

	चयन (state) अणु
	हाल PM_SUSPEND_STANDBY:
		pxa_cpu_standby();
		अवरोध;
	हाल PM_SUSPEND_MEM:
		cpu_suspend(pwrmode, pxa27x_finish_suspend);
#अगर_अघोषित CONFIG_IWMMXT
		यंत्र अस्थिर(".arch_extension xscale\n\t"
			     "mar acc0, %Q0, %R0" : "=r" (acc0));
#पूर्ण_अगर
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक pxa27x_cpu_pm_valid(suspend_state_t state)
अणु
	वापस state == PM_SUSPEND_MEM || state == PM_SUSPEND_STANDBY;
पूर्ण

अटल पूर्णांक pxa27x_cpu_pm_prepare(व्योम)
अणु
	/* set resume वापस address */
	PSPR = __pa_symbol(cpu_resume);
	वापस 0;
पूर्ण

अटल व्योम pxa27x_cpu_pm_finish(व्योम)
अणु
	/* ensure not to come back here अगर it wasn't पूर्णांकended */
	PSPR = 0;
पूर्ण

अटल काष्ठा pxa_cpu_pm_fns pxa27x_cpu_pm_fns = अणु
	.save_count	= SLEEP_SAVE_COUNT,
	.save		= pxa27x_cpu_pm_save,
	.restore	= pxa27x_cpu_pm_restore,
	.valid		= pxa27x_cpu_pm_valid,
	.enter		= pxa27x_cpu_pm_enter,
	.prepare	= pxa27x_cpu_pm_prepare,
	.finish		= pxa27x_cpu_pm_finish,
पूर्ण;

अटल व्योम __init pxa27x_init_pm(व्योम)
अणु
	pxa_cpu_pm_fns = &pxa27x_cpu_pm_fns;
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम pxa27x_init_pm(व्योम) अणुपूर्ण
#पूर्ण_अगर

/* PXA27x:  Various gpios can issue wakeup events.  This logic only
 * handles the simple हालs, not the WEMUX2 and WEMUX3 options
 */
अटल पूर्णांक pxa27x_set_wake(काष्ठा irq_data *d, अचिन्हित पूर्णांक on)
अणु
	पूर्णांक gpio = pxa_irq_to_gpio(d->irq);
	uपूर्णांक32_t mask;

	अगर (gpio >= 0 && gpio < 128)
		वापस gpio_set_wake(gpio, on);

	अगर (d->irq == IRQ_KEYPAD)
		वापस keypad_set_wake(on);

	चयन (d->irq) अणु
	हाल IRQ_RTCAlrm:
		mask = PWER_RTC;
		अवरोध;
	हाल IRQ_USB:
		mask = 1u << 26;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (on)
		PWER |= mask;
	अन्यथा
		PWER &=~mask;

	वापस 0;
पूर्ण

व्योम __init pxa27x_init_irq(व्योम)
अणु
	pxa_init_irq(34, pxa27x_set_wake);
पूर्ण

अटल पूर्णांक __init
pxa27x_dt_init_irq(काष्ठा device_node *node, काष्ठा device_node *parent)
अणु
	pxa_dt_irq_init(pxa27x_set_wake);
	set_handle_irq(ichp_handle_irq);

	वापस 0;
पूर्ण
IRQCHIP_DECLARE(pxa27x_पूर्णांकc, "marvell,pxa-intc", pxa27x_dt_init_irq);

अटल काष्ठा map_desc pxa27x_io_desc[] __initdata = अणु
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

व्योम __init pxa27x_map_io(व्योम)
अणु
	pxa_map_io();
	iotable_init(ARRAY_AND_SIZE(pxa27x_io_desc));
	pxa27x_get_clk_frequency_khz(1);
पूर्ण

/*
 * device registration specअगरic to PXA27x.
 */
व्योम __init pxa27x_set_i2c_घातer_info(काष्ठा i2c_pxa_platक्रमm_data *info)
अणु
	local_irq_disable();
	PCFR |= PCFR_PI2CEN;
	local_irq_enable();
	pxa_रेजिस्टर_device(&pxa27x_device_i2c_घातer, info);
पूर्ण

अटल काष्ठा pxa_gpio_platक्रमm_data pxa27x_gpio_info __initdata = अणु
	.irq_base	= PXA_GPIO_TO_IRQ(0),
	.gpio_set_wake	= gpio_set_wake,
पूर्ण;

अटल काष्ठा platक्रमm_device *devices[] __initdata = अणु
	&pxa27x_device_udc,
	&pxa_device_pmu,
	&pxa_device_i2s,
	&pxa_device_asoc_ssp1,
	&pxa_device_asoc_ssp2,
	&pxa_device_asoc_ssp3,
	&pxa_device_asoc_platक्रमm,
	&pxa_device_rtc,
	&pxa27x_device_ssp1,
	&pxa27x_device_ssp2,
	&pxa27x_device_ssp3,
	&pxa27x_device_pwm0,
	&pxa27x_device_pwm1,
पूर्ण;

अटल स्थिर काष्ठा dma_slave_map pxa27x_slave_map[] = अणु
	/* PXA25x, PXA27x and PXA3xx common entries */
	अणु "pxa2xx-ac97", "pcm_pcm_mic_mono", PDMA_FILTER_PARAM(LOWEST, 8) पूर्ण,
	अणु "pxa2xx-ac97", "pcm_pcm_aux_mono_in", PDMA_FILTER_PARAM(LOWEST, 9) पूर्ण,
	अणु "pxa2xx-ac97", "pcm_pcm_aux_mono_out",
	  PDMA_FILTER_PARAM(LOWEST, 10) पूर्ण,
	अणु "pxa2xx-ac97", "pcm_pcm_stereo_in", PDMA_FILTER_PARAM(LOWEST, 11) पूर्ण,
	अणु "pxa2xx-ac97", "pcm_pcm_stereo_out", PDMA_FILTER_PARAM(LOWEST, 12) पूर्ण,
	अणु "pxa-ssp-dai.0", "rx", PDMA_FILTER_PARAM(LOWEST, 13) पूर्ण,
	अणु "pxa-ssp-dai.0", "tx", PDMA_FILTER_PARAM(LOWEST, 14) पूर्ण,
	अणु "pxa-ssp-dai.1", "rx", PDMA_FILTER_PARAM(LOWEST, 15) पूर्ण,
	अणु "pxa-ssp-dai.1", "tx", PDMA_FILTER_PARAM(LOWEST, 16) पूर्ण,
	अणु "pxa2xx-ir", "rx", PDMA_FILTER_PARAM(LOWEST, 17) पूर्ण,
	अणु "pxa2xx-ir", "tx", PDMA_FILTER_PARAM(LOWEST, 18) पूर्ण,
	अणु "pxa2xx-mci.0", "rx", PDMA_FILTER_PARAM(LOWEST, 21) पूर्ण,
	अणु "pxa2xx-mci.0", "tx", PDMA_FILTER_PARAM(LOWEST, 22) पूर्ण,
	अणु "pxa-ssp-dai.2", "rx", PDMA_FILTER_PARAM(LOWEST, 66) पूर्ण,
	अणु "pxa-ssp-dai.2", "tx", PDMA_FILTER_PARAM(LOWEST, 67) पूर्ण,

	/* PXA27x specअगरic map */
	अणु "pxa2xx-i2s", "rx", PDMA_FILTER_PARAM(LOWEST, 2) पूर्ण,
	अणु "pxa2xx-i2s", "tx", PDMA_FILTER_PARAM(LOWEST, 3) पूर्ण,
	अणु "pxa27x-camera.0", "CI_Y", PDMA_FILTER_PARAM(HIGHEST, 68) पूर्ण,
	अणु "pxa27x-camera.0", "CI_U", PDMA_FILTER_PARAM(HIGHEST, 69) पूर्ण,
	अणु "pxa27x-camera.0", "CI_V", PDMA_FILTER_PARAM(HIGHEST, 70) पूर्ण,
पूर्ण;

अटल काष्ठा mmp_dma_platdata pxa27x_dma_pdata = अणु
	.dma_channels	= 32,
	.nb_requestors	= 75,
	.slave_map	= pxa27x_slave_map,
	.slave_map_cnt	= ARRAY_SIZE(pxa27x_slave_map),
पूर्ण;

अटल पूर्णांक __init pxa27x_init(व्योम)
अणु
	पूर्णांक ret = 0;

	अगर (cpu_is_pxa27x()) अणु

		reset_status = RCSR;

		pxa27x_init_pm();

		रेजिस्टर_syscore_ops(&pxa_irq_syscore_ops);
		रेजिस्टर_syscore_ops(&pxa2xx_mfp_syscore_ops);

		अगर (!of_have_populated_dt()) अणु
			pxa_रेजिस्टर_device(&pxa27x_device_gpio,
					    &pxa27x_gpio_info);
			pxa2xx_set_dmac_info(&pxa27x_dma_pdata);
			ret = platक्रमm_add_devices(devices,
						   ARRAY_SIZE(devices));
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

postcore_initcall(pxa27x_init);
