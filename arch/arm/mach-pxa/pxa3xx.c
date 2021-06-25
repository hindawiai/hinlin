<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * linux/arch/arm/mach-pxa/pxa3xx.c
 *
 * code specअगरic to pxa3xx aka Monahans
 *
 * Copyright (C) 2006 Marvell International Ltd.
 *
 * 2007-09-02: eric miao <eric.miao@marvell.com>
 *             initial version
 */
#समावेश <linux/dmaengine.h>
#समावेश <linux/dma/pxa-dma.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/gpio-pxa.h>
#समावेश <linux/pm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/irq.h>
#समावेश <linux/irqchip.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/syscore_ops.h>
#समावेश <linux/platक्रमm_data/i2c-pxa.h>
#समावेश <linux/platक्रमm_data/mmp_dma.h>

#समावेश <यंत्र/mach/map.h>
#समावेश <यंत्र/suspend.h>
#समावेश <mach/hardware.h>
#समावेश <mach/pxa3xx-regs.h>
#समावेश <mach/reset.h>
#समावेश <linux/platक्रमm_data/usb-ohci-pxa27x.h>
#समावेश "pm.h"
#समावेश <mach/dma.h>
#समावेश <mach/smemc.h>
#समावेश <mach/irqs.h>

#समावेश "generic.h"
#समावेश "devices.h"

#घोषणा PECR_IE(n)	((1 << ((n) * 2)) << 28)
#घोषणा PECR_IS(n)	((1 << ((n) * 2)) << 29)

बाह्य व्योम __init pxa_dt_irq_init(पूर्णांक (*fn)(काष्ठा irq_data *, अचिन्हित पूर्णांक));

/*
 * न_अंकD NFC: DFI bus arbitration subset
 */
#घोषणा NDCR			(*(अस्थिर u32 __iomem*)(न_अंकD_VIRT + 0))
#घोषणा NDCR_ND_ARB_EN		(1 << 12)
#घोषणा NDCR_ND_ARB_CNTL	(1 << 19)

#अगर_घोषित CONFIG_PM

#घोषणा ISRAM_START	0x5c000000
#घोषणा ISRAM_SIZE	SZ_256K

अटल व्योम __iomem *sram;
अटल अचिन्हित दीर्घ wakeup_src;

/*
 * Enter a standby mode (S0D1C2 or S0D2C2).  Upon wakeup, the dynamic
 * memory controller has to be reinitialised, so we place some code
 * in the SRAM to perक्रमm this function.
 *
 * We disable FIQs across the standby - otherwise, we might receive a
 * FIQ जबतक the SDRAM is unavailable.
 */
अटल व्योम pxa3xx_cpu_standby(अचिन्हित पूर्णांक pwrmode)
अणु
	व्योम (*fn)(अचिन्हित पूर्णांक) = (व्योम __क्रमce *)(sram + 0x8000);

	स_नकल_toio(sram + 0x8000, pm_enter_standby_start,
		    pm_enter_standby_end - pm_enter_standby_start);

	AD2D0SR = ~0;
	AD2D1SR = ~0;
	AD2D0ER = wakeup_src;
	AD2D1ER = 0;
	ASCR = ASCR;
	ARSR = ARSR;

	local_fiq_disable();
	fn(pwrmode);
	local_fiq_enable();

	AD2D0ER = 0;
	AD2D1ER = 0;
पूर्ण

/*
 * NOTE:  currently, the OBM (OEM Boot Module) binary comes aदीर्घ with
 * PXA3xx development kits assumes that the resuming process जारीs
 * with the address stored within the first 4 bytes of SDRAM. The PSPR
 * रेजिस्टर is used निजीly by BootROM and OBM, and _must_ be set to
 * 0x5c014000 क्रम the moment.
 */
अटल व्योम pxa3xx_cpu_pm_suspend(व्योम)
अणु
	अस्थिर अचिन्हित दीर्घ *p = (अस्थिर व्योम *)0xc0000000;
	अचिन्हित दीर्घ saved_data = *p;
#अगर_अघोषित CONFIG_IWMMXT
	u64 acc0;

	यंत्र अस्थिर(".arch_extension xscale\n\t"
		     "mra %Q0, %R0, acc0" : "=r" (acc0));
#पूर्ण_अगर

	/* resuming from D2 requires the HSIO2/BOOT/TPM घड़ीs enabled */
	CKENA |= (1 << CKEN_BOOT) | (1 << CKEN_TPM);
	CKENB |= 1 << (CKEN_HSIO2 & 0x1f);

	/* clear and setup wakeup source */
	AD3SR = ~0;
	AD3ER = wakeup_src;
	ASCR = ASCR;
	ARSR = ARSR;

	PCFR |= (1u << 13);			/* L1_DIS */
	PCFR &= ~((1u << 12) | (1u << 1));	/* L0_EN | SL_ROD */

	PSPR = 0x5c014000;

	/* overग_लिखो with the resume address */
	*p = __pa_symbol(cpu_resume);

	cpu_suspend(0, pxa3xx_finish_suspend);

	*p = saved_data;

	AD3ER = 0;

#अगर_अघोषित CONFIG_IWMMXT
	यंत्र अस्थिर(".arch_extension xscale\n\t"
		     "mar acc0, %Q0, %R0" : "=r" (acc0));
#पूर्ण_अगर
पूर्ण

अटल व्योम pxa3xx_cpu_pm_enter(suspend_state_t state)
अणु
	/*
	 * Don't sleep अगर no wakeup sources are defined
	 */
	अगर (wakeup_src == 0) अणु
		prपूर्णांकk(KERN_ERR "Not suspending: no wakeup sources\n");
		वापस;
	पूर्ण

	चयन (state) अणु
	हाल PM_SUSPEND_STANDBY:
		pxa3xx_cpu_standby(PXA3xx_PM_S0D2C2);
		अवरोध;

	हाल PM_SUSPEND_MEM:
		pxa3xx_cpu_pm_suspend();
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक pxa3xx_cpu_pm_valid(suspend_state_t state)
अणु
	वापस state == PM_SUSPEND_MEM || state == PM_SUSPEND_STANDBY;
पूर्ण

अटल काष्ठा pxa_cpu_pm_fns pxa3xx_cpu_pm_fns = अणु
	.valid		= pxa3xx_cpu_pm_valid,
	.enter		= pxa3xx_cpu_pm_enter,
पूर्ण;

अटल व्योम __init pxa3xx_init_pm(व्योम)
अणु
	sram = ioremap(ISRAM_START, ISRAM_SIZE);
	अगर (!sram) अणु
		prपूर्णांकk(KERN_ERR "Unable to map ISRAM: disabling standby/suspend\n");
		वापस;
	पूर्ण

	/*
	 * Since we copy wakeup code पूर्णांकo the SRAM, we need to ensure
	 * that it is preserved over the low घातer modes.  Note: bit 8
	 * is unकरोcumented in the developer manual, but must be set.
	 */
	AD1R |= ADXR_L2 | ADXR_R0;
	AD2R |= ADXR_L2 | ADXR_R0;
	AD3R |= ADXR_L2 | ADXR_R0;

	/*
	 * Clear the resume enable रेजिस्टरs.
	 */
	AD1D0ER = 0;
	AD2D0ER = 0;
	AD2D1ER = 0;
	AD3ER = 0;

	pxa_cpu_pm_fns = &pxa3xx_cpu_pm_fns;
पूर्ण

अटल पूर्णांक pxa3xx_set_wake(काष्ठा irq_data *d, अचिन्हित पूर्णांक on)
अणु
	अचिन्हित दीर्घ flags, mask = 0;

	चयन (d->irq) अणु
	हाल IRQ_SSP3:
		mask = ADXER_MFP_WSSP3;
		अवरोध;
	हाल IRQ_MSL:
		mask = ADXER_WMSL0;
		अवरोध;
	हाल IRQ_USBH2:
	हाल IRQ_USBH1:
		mask = ADXER_WUSBH;
		अवरोध;
	हाल IRQ_KEYPAD:
		mask = ADXER_WKP;
		अवरोध;
	हाल IRQ_AC97:
		mask = ADXER_MFP_WAC97;
		अवरोध;
	हाल IRQ_USIM:
		mask = ADXER_WUSIM0;
		अवरोध;
	हाल IRQ_SSP2:
		mask = ADXER_MFP_WSSP2;
		अवरोध;
	हाल IRQ_I2C:
		mask = ADXER_MFP_WI2C;
		अवरोध;
	हाल IRQ_STUART:
		mask = ADXER_MFP_WUART3;
		अवरोध;
	हाल IRQ_BTUART:
		mask = ADXER_MFP_WUART2;
		अवरोध;
	हाल IRQ_FFUART:
		mask = ADXER_MFP_WUART1;
		अवरोध;
	हाल IRQ_MMC:
		mask = ADXER_MFP_WMMC1;
		अवरोध;
	हाल IRQ_SSP:
		mask = ADXER_MFP_WSSP1;
		अवरोध;
	हाल IRQ_RTCAlrm:
		mask = ADXER_WRTC;
		अवरोध;
	हाल IRQ_SSP4:
		mask = ADXER_MFP_WSSP4;
		अवरोध;
	हाल IRQ_TSI:
		mask = ADXER_WTSI;
		अवरोध;
	हाल IRQ_USIM2:
		mask = ADXER_WUSIM1;
		अवरोध;
	हाल IRQ_MMC2:
		mask = ADXER_MFP_WMMC2;
		अवरोध;
	हाल IRQ_न_अंकD:
		mask = ADXER_MFP_WFLASH;
		अवरोध;
	हाल IRQ_USB2:
		mask = ADXER_WUSB2;
		अवरोध;
	हाल IRQ_WAKEUP0:
		mask = ADXER_WEXTWAKE0;
		अवरोध;
	हाल IRQ_WAKEUP1:
		mask = ADXER_WEXTWAKE1;
		अवरोध;
	हाल IRQ_MMC3:
		mask = ADXER_MFP_GEN12;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	local_irq_save(flags);
	अगर (on)
		wakeup_src |= mask;
	अन्यथा
		wakeup_src &= ~mask;
	local_irq_restore(flags);

	वापस 0;
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम pxa3xx_init_pm(व्योम) अणुपूर्ण
#घोषणा pxa3xx_set_wake	शून्य
#पूर्ण_अगर

अटल व्योम pxa_ack_ext_wakeup(काष्ठा irq_data *d)
अणु
	PECR |= PECR_IS(d->irq - IRQ_WAKEUP0);
पूर्ण

अटल व्योम pxa_mask_ext_wakeup(काष्ठा irq_data *d)
अणु
	pxa_mask_irq(d);
	PECR &= ~PECR_IE(d->irq - IRQ_WAKEUP0);
पूर्ण

अटल व्योम pxa_unmask_ext_wakeup(काष्ठा irq_data *d)
अणु
	pxa_unmask_irq(d);
	PECR |= PECR_IE(d->irq - IRQ_WAKEUP0);
पूर्ण

अटल पूर्णांक pxa_set_ext_wakeup_type(काष्ठा irq_data *d, अचिन्हित पूर्णांक flow_type)
अणु
	अगर (flow_type & IRQ_TYPE_EDGE_RISING)
		PWER |= 1 << (d->irq - IRQ_WAKEUP0);

	अगर (flow_type & IRQ_TYPE_EDGE_FALLING)
		PWER |= 1 << (d->irq - IRQ_WAKEUP0 + 2);

	वापस 0;
पूर्ण

अटल काष्ठा irq_chip pxa_ext_wakeup_chip = अणु
	.name		= "WAKEUP",
	.irq_ack	= pxa_ack_ext_wakeup,
	.irq_mask	= pxa_mask_ext_wakeup,
	.irq_unmask	= pxa_unmask_ext_wakeup,
	.irq_set_type	= pxa_set_ext_wakeup_type,
पूर्ण;

अटल व्योम __init pxa_init_ext_wakeup_irq(पूर्णांक (*fn)(काष्ठा irq_data *,
					   अचिन्हित पूर्णांक))
अणु
	पूर्णांक irq;

	क्रम (irq = IRQ_WAKEUP0; irq <= IRQ_WAKEUP1; irq++) अणु
		irq_set_chip_and_handler(irq, &pxa_ext_wakeup_chip,
					 handle_edge_irq);
		irq_clear_status_flags(irq, IRQ_NOREQUEST);
	पूर्ण

	pxa_ext_wakeup_chip.irq_set_wake = fn;
पूर्ण

अटल व्योम __init __pxa3xx_init_irq(व्योम)
अणु
	/* enable CP6 access */
	u32 value;
	__यंत्र__ __अस्थिर__("mrc p15, 0, %0, c15, c1, 0\n": "=r"(value));
	value |= (1 << 6);
	__यंत्र__ __अस्थिर__("mcr p15, 0, %0, c15, c1, 0\n": :"r"(value));

	pxa_init_ext_wakeup_irq(pxa3xx_set_wake);
पूर्ण

व्योम __init pxa3xx_init_irq(व्योम)
अणु
	__pxa3xx_init_irq();
	pxa_init_irq(56, pxa3xx_set_wake);
पूर्ण

#अगर_घोषित CONFIG_OF
अटल पूर्णांक __init __init
pxa3xx_dt_init_irq(काष्ठा device_node *node, काष्ठा device_node *parent)
अणु
	__pxa3xx_init_irq();
	pxa_dt_irq_init(pxa3xx_set_wake);
	set_handle_irq(ichp_handle_irq);

	वापस 0;
पूर्ण
IRQCHIP_DECLARE(pxa3xx_पूर्णांकc, "marvell,pxa-intc", pxa3xx_dt_init_irq);
#पूर्ण_अगर	/* CONFIG_OF */

अटल काष्ठा map_desc pxa3xx_io_desc[] __initdata = अणु
	अणु	/* Mem Ctl */
		.भव	= (अचिन्हित दीर्घ)SMEMC_VIRT,
		.pfn		= __phys_to_pfn(PXA3XX_SMEMC_BASE),
		.length		= SMEMC_SIZE,
		.type		= MT_DEVICE
	पूर्ण, अणु
		.भव	= (अचिन्हित दीर्घ)न_अंकD_VIRT,
		.pfn		= __phys_to_pfn(न_अंकD_PHYS),
		.length		= न_अंकD_SIZE,
		.type		= MT_DEVICE
	पूर्ण,
पूर्ण;

व्योम __init pxa3xx_map_io(व्योम)
अणु
	pxa_map_io();
	iotable_init(ARRAY_AND_SIZE(pxa3xx_io_desc));
	pxa3xx_get_clk_frequency_khz(1);
पूर्ण

/*
 * device registration specअगरic to PXA3xx.
 */

व्योम __init pxa3xx_set_i2c_घातer_info(काष्ठा i2c_pxa_platक्रमm_data *info)
अणु
	pxa_रेजिस्टर_device(&pxa3xx_device_i2c_घातer, info);
पूर्ण

अटल काष्ठा pxa_gpio_platक्रमm_data pxa3xx_gpio_pdata = अणु
	.irq_base	= PXA_GPIO_TO_IRQ(0),
पूर्ण;

अटल काष्ठा platक्रमm_device *devices[] __initdata = अणु
	&pxa27x_device_udc,
	&pxa_device_pmu,
	&pxa_device_i2s,
	&pxa_device_asoc_ssp1,
	&pxa_device_asoc_ssp2,
	&pxa_device_asoc_ssp3,
	&pxa_device_asoc_ssp4,
	&pxa_device_asoc_platक्रमm,
	&pxa_device_rtc,
	&pxa3xx_device_ssp1,
	&pxa3xx_device_ssp2,
	&pxa3xx_device_ssp3,
	&pxa3xx_device_ssp4,
	&pxa27x_device_pwm0,
	&pxa27x_device_pwm1,
पूर्ण;

अटल स्थिर काष्ठा dma_slave_map pxa3xx_slave_map[] = अणु
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

	/* PXA3xx specअगरic map */
	अणु "pxa-ssp-dai.3", "rx", PDMA_FILTER_PARAM(LOWEST, 2) पूर्ण,
	अणु "pxa-ssp-dai.3", "tx", PDMA_FILTER_PARAM(LOWEST, 3) पूर्ण,
	अणु "pxa2xx-mci.1", "rx", PDMA_FILTER_PARAM(LOWEST, 93) पूर्ण,
	अणु "pxa2xx-mci.1", "tx", PDMA_FILTER_PARAM(LOWEST, 94) पूर्ण,
	अणु "pxa3xx-nand", "data", PDMA_FILTER_PARAM(LOWEST, 97) पूर्ण,
	अणु "pxa2xx-mci.2", "rx", PDMA_FILTER_PARAM(LOWEST, 100) पूर्ण,
	अणु "pxa2xx-mci.2", "tx", PDMA_FILTER_PARAM(LOWEST, 101) पूर्ण,
पूर्ण;

अटल काष्ठा mmp_dma_platdata pxa3xx_dma_pdata = अणु
	.dma_channels	= 32,
	.nb_requestors	= 100,
	.slave_map	= pxa3xx_slave_map,
	.slave_map_cnt	= ARRAY_SIZE(pxa3xx_slave_map),
पूर्ण;

अटल पूर्णांक __init pxa3xx_init(व्योम)
अणु
	पूर्णांक ret = 0;

	अगर (cpu_is_pxa3xx()) अणु

		reset_status = ARSR;

		/*
		 * clear RDH bit every समय after reset
		 *
		 * Note: the last 3 bits DxS are ग_लिखो-1-to-clear so carefully
		 * preserve them here in हाल they will be referenced later
		 */
		ASCR &= ~(ASCR_RDH | ASCR_D1S | ASCR_D2S | ASCR_D3S);

		/*
		 * Disable DFI bus arbitration, to prevent a प्रणाली bus lock अगर
		 * somebody disables the न_अंकD घड़ी (unused घड़ी) जबतक this
		 * bit reमुख्यs set.
		 */
		NDCR = (NDCR & ~NDCR_ND_ARB_EN) | NDCR_ND_ARB_CNTL;

		pxa3xx_init_pm();

		enable_irq_wake(IRQ_WAKEUP0);
		अगर (cpu_is_pxa320())
			enable_irq_wake(IRQ_WAKEUP1);

		रेजिस्टर_syscore_ops(&pxa_irq_syscore_ops);
		रेजिस्टर_syscore_ops(&pxa3xx_mfp_syscore_ops);

		अगर (of_have_populated_dt())
			वापस 0;

		pxa2xx_set_dmac_info(&pxa3xx_dma_pdata);
		ret = platक्रमm_add_devices(devices, ARRAY_SIZE(devices));
		अगर (ret)
			वापस ret;
		अगर (cpu_is_pxa300() || cpu_is_pxa310() || cpu_is_pxa320()) अणु
			platक्रमm_device_add_data(&pxa3xx_device_gpio,
						 &pxa3xx_gpio_pdata,
						 माप(pxa3xx_gpio_pdata));
			ret = platक्रमm_device_रेजिस्टर(&pxa3xx_device_gpio);
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

postcore_initcall(pxa3xx_init);
