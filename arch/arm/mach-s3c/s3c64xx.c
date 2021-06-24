<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Copyright (c) 2011 Samsung Electronics Co., Ltd.
//		http://www.samsung.com
//
// Copyright 2008 Openmoko, Inc.
// Copyright 2008 Simtec Electronics
//	Ben Dooks <ben@simtec.co.uk>
//	http://armlinux.simtec.co.uk/
//
// Common Codes क्रम S3C64XX machines

/*
 * NOTE: Code in this file is not used when booting with Device Tree support.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/ioport.h>
#समावेश <linux/serial_core.h>
#समावेश <linux/serial_s3c.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/reboot.h>
#समावेश <linux/पन.स>
#समावेश <linux/clk/samsung.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/irq.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/irqchip/arm-vic.h>
#समावेश <घड़ीsource/samsung_pwm.h>

#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/map.h>
#समावेश <यंत्र/प्रणाली_misc.h>

#समावेश "map.h"
#समावेश <mach/irqs.h>
#समावेश "regs-gpio.h"
#समावेश "gpio-samsung.h"

#समावेश "cpu.h"
#समावेश "devs.h"
#समावेश "pm.h"
#समावेश "gpio-cfg.h"
#समावेश "pwm-core.h"
#समावेश "regs-irqtype.h"
#समावेश "s3c64xx.h"
#समावेश "irq-uart-s3c64xx.h"

/* External घड़ी frequency */
अटल अचिन्हित दीर्घ xtal_f __ro_after_init = 12000000;
अटल अचिन्हित दीर्घ xusbxti_f __ro_after_init = 48000000;

व्योम __init s3c64xx_set_xtal_freq(अचिन्हित दीर्घ freq)
अणु
	xtal_f = freq;
पूर्ण

व्योम __init s3c64xx_set_xusbxti_freq(अचिन्हित दीर्घ freq)
अणु
	xusbxti_f = freq;
पूर्ण

/* uart registration process */

अटल व्योम __init s3c64xx_init_uarts(काष्ठा s3c2410_uartcfg *cfg, पूर्णांक no)
अणु
	s3c24xx_init_uartdevs("s3c6400-uart", s3c64xx_uart_resources, cfg, no);
पूर्ण

/* table of supported CPUs */

अटल स्थिर अक्षर name_s3c6400[] = "S3C6400";
अटल स्थिर अक्षर name_s3c6410[] = "S3C6410";

अटल काष्ठा cpu_table cpu_ids[] __initdata = अणु
	अणु
		.idcode		= S3C6400_CPU_ID,
		.idmask		= S3C64XX_CPU_MASK,
		.map_io		= s3c6400_map_io,
		.init_uarts	= s3c64xx_init_uarts,
		.init		= s3c6400_init,
		.name		= name_s3c6400,
	पूर्ण, अणु
		.idcode		= S3C6410_CPU_ID,
		.idmask		= S3C64XX_CPU_MASK,
		.map_io		= s3c6410_map_io,
		.init_uarts	= s3c64xx_init_uarts,
		.init		= s3c6410_init,
		.name		= name_s3c6410,
	पूर्ण,
पूर्ण;

/* minimal IO mapping */

/*
 * note, क्रम the boot process to work we have to keep the UART
 * भव address aligned to an 1MiB boundary क्रम the L1
 * mapping the head code makes. We keep the UART भव address
 * aligned and add in the offset when we load the value here.
 */
#घोषणा UART_OFFS (S3C_PA_UART & 0xfffff)

अटल काष्ठा map_desc s3c_iodesc[] __initdata = अणु
	अणु
		.भव	= (अचिन्हित दीर्घ)S3C_VA_SYS,
		.pfn		= __phys_to_pfn(S3C64XX_PA_SYSCON),
		.length		= SZ_4K,
		.type		= MT_DEVICE,
	पूर्ण, अणु
		.भव	= (अचिन्हित दीर्घ)S3C_VA_MEM,
		.pfn		= __phys_to_pfn(S3C64XX_PA_SROM),
		.length		= SZ_4K,
		.type		= MT_DEVICE,
	पूर्ण, अणु
		.भव	= (अचिन्हित दीर्घ)(S3C_VA_UART + UART_OFFS),
		.pfn		= __phys_to_pfn(S3C_PA_UART),
		.length		= SZ_4K,
		.type		= MT_DEVICE,
	पूर्ण, अणु
		.भव	= (अचिन्हित दीर्घ)VA_VIC0,
		.pfn		= __phys_to_pfn(S3C64XX_PA_VIC0),
		.length		= SZ_16K,
		.type		= MT_DEVICE,
	पूर्ण, अणु
		.भव	= (अचिन्हित दीर्घ)VA_VIC1,
		.pfn		= __phys_to_pfn(S3C64XX_PA_VIC1),
		.length		= SZ_16K,
		.type		= MT_DEVICE,
	पूर्ण, अणु
		.भव	= (अचिन्हित दीर्घ)S3C_VA_TIMER,
		.pfn		= __phys_to_pfn(S3C_PA_TIMER),
		.length		= SZ_16K,
		.type		= MT_DEVICE,
	पूर्ण, अणु
		.भव	= (अचिन्हित दीर्घ)S3C64XX_VA_GPIO,
		.pfn		= __phys_to_pfn(S3C64XX_PA_GPIO),
		.length		= SZ_4K,
		.type		= MT_DEVICE,
	पूर्ण, अणु
		.भव	= (अचिन्हित दीर्घ)S3C64XX_VA_MODEM,
		.pfn		= __phys_to_pfn(S3C64XX_PA_MODEM),
		.length		= SZ_4K,
		.type		= MT_DEVICE,
	पूर्ण, अणु
		.भव	= (अचिन्हित दीर्घ)S3C_VA_WATCHDOG,
		.pfn		= __phys_to_pfn(S3C64XX_PA_WATCHDOG),
		.length		= SZ_4K,
		.type		= MT_DEVICE,
	पूर्ण, अणु
		.भव	= (अचिन्हित दीर्घ)S3C_VA_USB_HSPHY,
		.pfn		= __phys_to_pfn(S3C64XX_PA_USB_HSPHY),
		.length		= SZ_1K,
		.type		= MT_DEVICE,
	पूर्ण,
पूर्ण;

अटल काष्ठा bus_type s3c64xx_subsys = अणु
	.name		= "s3c64xx-core",
	.dev_name	= "s3c64xx-core",
पूर्ण;

अटल काष्ठा device s3c64xx_dev = अणु
	.bus	= &s3c64xx_subsys,
पूर्ण;

अटल काष्ठा samsung_pwm_variant s3c64xx_pwm_variant = अणु
	.bits		= 32,
	.भाग_base	= 0,
	.has_tपूर्णांक_cstat	= true,
	.tclk_mask	= (1 << 7) | (1 << 6) | (1 << 5),
पूर्ण;

व्योम __init s3c64xx_set_समयr_source(अचिन्हित पूर्णांक event, अचिन्हित पूर्णांक source)
अणु
	s3c64xx_pwm_variant.output_mask = BIT(SAMSUNG_PWM_NUM) - 1;
	s3c64xx_pwm_variant.output_mask &= ~(BIT(event) | BIT(source));
पूर्ण

व्योम __init s3c64xx_समयr_init(व्योम)
अणु
	अचिन्हित पूर्णांक समयr_irqs[SAMSUNG_PWM_NUM] = अणु
		IRQ_TIMER0_VIC, IRQ_TIMER1_VIC, IRQ_TIMER2_VIC,
		IRQ_TIMER3_VIC, IRQ_TIMER4_VIC,
	पूर्ण;

	samsung_pwm_घड़ीsource_init(S3C_VA_TIMER,
					समयr_irqs, &s3c64xx_pwm_variant);
पूर्ण

/* पढ़ो cpu identअगरication code */

व्योम __init s3c64xx_init_io(काष्ठा map_desc *mach_desc, पूर्णांक size)
अणु
	/* initialise the io descriptors we need क्रम initialisation */
	iotable_init(s3c_iodesc, ARRAY_SIZE(s3c_iodesc));
	iotable_init(mach_desc, size);

	/* detect cpu id */
	s3c64xx_init_cpu();

	s3c_init_cpu(samsung_cpu_id, cpu_ids, ARRAY_SIZE(cpu_ids));

	samsung_pwm_set_platdata(&s3c64xx_pwm_variant);
पूर्ण

अटल __init पूर्णांक s3c64xx_dev_init(व्योम)
अणु
	/* Not applicable when using DT. */
	अगर (of_have_populated_dt() || !soc_is_s3c64xx())
		वापस 0;

	subsys_प्रणाली_रेजिस्टर(&s3c64xx_subsys, शून्य);
	वापस device_रेजिस्टर(&s3c64xx_dev);
पूर्ण
core_initcall(s3c64xx_dev_init);

/*
 * setup the sources the vic should advertise resume
 * क्रम, even though it is not करोing the wake
 * (set_irq_wake needs to be valid)
 */
#घोषणा IRQ_VIC0_RESUME (1 << (IRQ_RTC_TIC - IRQ_VIC0_BASE))
#घोषणा IRQ_VIC1_RESUME (1 << (IRQ_RTC_ALARM - IRQ_VIC1_BASE) |	\
			 1 << (IRQ_PENDN - IRQ_VIC1_BASE) |	\
			 1 << (IRQ_HSMMC0 - IRQ_VIC1_BASE) |	\
			 1 << (IRQ_HSMMC1 - IRQ_VIC1_BASE) |	\
			 1 << (IRQ_HSMMC2 - IRQ_VIC1_BASE))

व्योम __init s3c64xx_init_irq(u32 vic0_valid, u32 vic1_valid)
अणु
	s3c64xx_clk_init(शून्य, xtal_f, xusbxti_f, soc_is_s3c6400(), S3C_VA_SYS);

	prपूर्णांकk(KERN_DEBUG "%s: initialising interrupts\n", __func__);

	/* initialise the pair of VICs */
	vic_init(VA_VIC0, IRQ_VIC0_BASE, vic0_valid, IRQ_VIC0_RESUME);
	vic_init(VA_VIC1, IRQ_VIC1_BASE, vic1_valid, IRQ_VIC1_RESUME);
पूर्ण

#घोषणा eपूर्णांक_offset(irq)	((irq) - IRQ_EINT(0))
#घोषणा eपूर्णांक_irq_to_bit(irq)	((u32)(1 << eपूर्णांक_offset(irq)))

अटल अंतरभूत व्योम s3c_irq_eपूर्णांक_mask(काष्ठा irq_data *data)
अणु
	u32 mask;

	mask = __raw_पढ़ोl(S3C64XX_EINT0MASK);
	mask |= (u32)data->chip_data;
	__raw_ग_लिखोl(mask, S3C64XX_EINT0MASK);
पूर्ण

अटल व्योम s3c_irq_eपूर्णांक_unmask(काष्ठा irq_data *data)
अणु
	u32 mask;

	mask = __raw_पढ़ोl(S3C64XX_EINT0MASK);
	mask &= ~((u32)data->chip_data);
	__raw_ग_लिखोl(mask, S3C64XX_EINT0MASK);
पूर्ण

अटल अंतरभूत व्योम s3c_irq_eपूर्णांक_ack(काष्ठा irq_data *data)
अणु
	__raw_ग_लिखोl((u32)data->chip_data, S3C64XX_EINT0PEND);
पूर्ण

अटल व्योम s3c_irq_eपूर्णांक_maskack(काष्ठा irq_data *data)
अणु
	/* compiler should in-line these */
	s3c_irq_eपूर्णांक_mask(data);
	s3c_irq_eपूर्णांक_ack(data);
पूर्ण

अटल पूर्णांक s3c_irq_eपूर्णांक_set_type(काष्ठा irq_data *data, अचिन्हित पूर्णांक type)
अणु
	पूर्णांक offs = eपूर्णांक_offset(data->irq);
	पूर्णांक pin, pin_val;
	पूर्णांक shअगरt;
	u32 ctrl, mask;
	u32 newvalue = 0;
	व्योम __iomem *reg;

	अगर (offs > 27)
		वापस -EINVAL;

	अगर (offs <= 15)
		reg = S3C64XX_EINT0CON0;
	अन्यथा
		reg = S3C64XX_EINT0CON1;

	चयन (type) अणु
	हाल IRQ_TYPE_NONE:
		prपूर्णांकk(KERN_WARNING "No edge setting!\n");
		अवरोध;

	हाल IRQ_TYPE_EDGE_RISING:
		newvalue = S3C2410_EXTINT_RISEEDGE;
		अवरोध;

	हाल IRQ_TYPE_EDGE_FALLING:
		newvalue = S3C2410_EXTINT_FALLEDGE;
		अवरोध;

	हाल IRQ_TYPE_EDGE_BOTH:
		newvalue = S3C2410_EXTINT_BOTHEDGE;
		अवरोध;

	हाल IRQ_TYPE_LEVEL_LOW:
		newvalue = S3C2410_EXTINT_LOWLEV;
		अवरोध;

	हाल IRQ_TYPE_LEVEL_HIGH:
		newvalue = S3C2410_EXTINT_HILEV;
		अवरोध;

	शेष:
		prपूर्णांकk(KERN_ERR "No such irq type %d", type);
		वापस -1;
	पूर्ण

	अगर (offs <= 15)
		shअगरt = (offs / 2) * 4;
	अन्यथा
		shअगरt = ((offs - 16) / 2) * 4;
	mask = 0x7 << shअगरt;

	ctrl = __raw_पढ़ोl(reg);
	ctrl &= ~mask;
	ctrl |= newvalue << shअगरt;
	__raw_ग_लिखोl(ctrl, reg);

	/* set the GPIO pin appropriately */

	अगर (offs < 16) अणु
		pin = S3C64XX_GPN(offs);
		pin_val = S3C_GPIO_SFN(2);
	पूर्ण अन्यथा अगर (offs < 23) अणु
		pin = S3C64XX_GPL(offs + 8 - 16);
		pin_val = S3C_GPIO_SFN(3);
	पूर्ण अन्यथा अणु
		pin = S3C64XX_GPM(offs - 23);
		pin_val = S3C_GPIO_SFN(3);
	पूर्ण

	s3c_gpio_cfgpin(pin, pin_val);

	वापस 0;
पूर्ण

अटल काष्ठा irq_chip s3c_irq_eपूर्णांक = अणु
	.name		= "s3c-eint",
	.irq_mask	= s3c_irq_eपूर्णांक_mask,
	.irq_unmask	= s3c_irq_eपूर्णांक_unmask,
	.irq_mask_ack	= s3c_irq_eपूर्णांक_maskack,
	.irq_ack	= s3c_irq_eपूर्णांक_ack,
	.irq_set_type	= s3c_irq_eपूर्णांक_set_type,
	.irq_set_wake	= s3c_irqext_wake,
पूर्ण;

/* s3c_irq_demux_eपूर्णांक
 *
 * This function demuxes the IRQ from the group0 बाह्यal पूर्णांकerrupts,
 * from IRQ_EINT(0) to IRQ_EINT(27). It is deचिन्हित to be अंतरभूतd पूर्णांकo
 * the specअगरic handlers s3c_irq_demux_eपूर्णांकX_Y.
 */
अटल अंतरभूत व्योम s3c_irq_demux_eपूर्णांक(अचिन्हित पूर्णांक start, अचिन्हित पूर्णांक end)
अणु
	u32 status = __raw_पढ़ोl(S3C64XX_EINT0PEND);
	u32 mask = __raw_पढ़ोl(S3C64XX_EINT0MASK);
	अचिन्हित पूर्णांक irq;

	status &= ~mask;
	status >>= start;
	status &= (1 << (end - start + 1)) - 1;

	क्रम (irq = IRQ_EINT(start); irq <= IRQ_EINT(end); irq++) अणु
		अगर (status & 1)
			generic_handle_irq(irq);

		status >>= 1;
	पूर्ण
पूर्ण

अटल व्योम s3c_irq_demux_eपूर्णांक0_3(काष्ठा irq_desc *desc)
अणु
	s3c_irq_demux_eपूर्णांक(0, 3);
पूर्ण

अटल व्योम s3c_irq_demux_eपूर्णांक4_11(काष्ठा irq_desc *desc)
अणु
	s3c_irq_demux_eपूर्णांक(4, 11);
पूर्ण

अटल व्योम s3c_irq_demux_eपूर्णांक12_19(काष्ठा irq_desc *desc)
अणु
	s3c_irq_demux_eपूर्णांक(12, 19);
पूर्ण

अटल व्योम s3c_irq_demux_eपूर्णांक20_27(काष्ठा irq_desc *desc)
अणु
	s3c_irq_demux_eपूर्णांक(20, 27);
पूर्ण

अटल पूर्णांक __init s3c64xx_init_irq_eपूर्णांक(व्योम)
अणु
	पूर्णांक irq;

	/* On DT-enabled प्रणालीs EINTs are handled by pinctrl-s3c64xx driver. */
	अगर (of_have_populated_dt() || !soc_is_s3c64xx())
		वापस -ENODEV;

	क्रम (irq = IRQ_EINT(0); irq <= IRQ_EINT(27); irq++) अणु
		irq_set_chip_and_handler(irq, &s3c_irq_eपूर्णांक, handle_level_irq);
		irq_set_chip_data(irq, (व्योम *)eपूर्णांक_irq_to_bit(irq));
		irq_clear_status_flags(irq, IRQ_NOREQUEST);
	पूर्ण

	irq_set_chained_handler(IRQ_EINT0_3, s3c_irq_demux_eपूर्णांक0_3);
	irq_set_chained_handler(IRQ_EINT4_11, s3c_irq_demux_eपूर्णांक4_11);
	irq_set_chained_handler(IRQ_EINT12_19, s3c_irq_demux_eपूर्णांक12_19);
	irq_set_chained_handler(IRQ_EINT20_27, s3c_irq_demux_eपूर्णांक20_27);

	वापस 0;
पूर्ण
arch_initcall(s3c64xx_init_irq_eपूर्णांक);
