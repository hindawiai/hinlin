<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * linux/arch/arm/mach-sa1100/neponset.c
 */
#समावेश <linux/err.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/gpio/gpio-reg.h>
#समावेश <linux/gpio/machine.h>
#समावेश <linux/init.h>
#समावेश <linux/ioport.h>
#समावेश <linux/irq.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm.h>
#समावेश <linux/serial_core.h>
#समावेश <linux/slab.h>
#समावेश <linux/smc91x.h>

#समावेश <यंत्र/mach-types.h>
#समावेश <यंत्र/mach/map.h>
#समावेश <यंत्र/hardware/sa1111.h>
#समावेश <linux/sizes.h>

#समावेश <mach/hardware.h>
#समावेश <mach/assabet.h>
#समावेश <mach/neponset.h>
#समावेश <mach/irqs.h>

#घोषणा NEP_IRQ_SMC91X	0
#घोषणा NEP_IRQ_USAR	1
#घोषणा NEP_IRQ_SA1111	2
#घोषणा NEP_IRQ_NR	3

#घोषणा WHOAMI		0x00
#घोषणा LEDS		0x10
#घोषणा SWPK		0x20
#घोषणा IRR		0x24
#घोषणा KP_Y_IN		0x80
#घोषणा KP_X_OUT	0x90
#घोषणा NCR_0		0xa0
#घोषणा MDM_CTL_0	0xb0
#घोषणा MDM_CTL_1	0xb4
#घोषणा AUD_CTL		0xc0

#घोषणा IRR_ETHERNET	(1 << 0)
#घोषणा IRR_USAR	(1 << 1)
#घोषणा IRR_SA1111	(1 << 2)

#घोषणा NCR_NGPIO	7
#घोषणा MDM_CTL0_NGPIO	4
#घोषणा MDM_CTL1_NGPIO	6
#घोषणा AUD_NGPIO	2

बाह्य व्योम sa1110_mb_disable(व्योम);

#घोषणा to_neponset_gpio_chip(x) container_of(x, काष्ठा neponset_gpio_chip, gc)

अटल स्थिर अक्षर *neponset_ncr_names[] = अणु
	"gp01_off", "tp_power", "ms_power", "enet_osc",
	"spi_kb_wk_up", "a0vpp", "a1vpp"
पूर्ण;

अटल स्थिर अक्षर *neponset_mdmctl0_names[] = अणु
	"rts3", "dtr3", "rts1", "dtr1",
पूर्ण;

अटल स्थिर अक्षर *neponset_mdmctl1_names[] = अणु
	"cts3", "dsr3", "dcd3", "cts1", "dsr1", "dcd1"
पूर्ण;

अटल स्थिर अक्षर *neponset_aud_names[] = अणु
	"sel_1341", "mute_1341",
पूर्ण;

काष्ठा neponset_drvdata अणु
	व्योम __iomem *base;
	काष्ठा platक्रमm_device *sa1111;
	काष्ठा platक्रमm_device *smc91x;
	अचिन्हित irq_base;
	काष्ठा gpio_chip *gpio[4];
पूर्ण;

अटल काष्ठा gpiod_lookup_table neponset_uart1_gpio_table = अणु
	.dev_id = "sa11x0-uart.1",
	.table = अणु
		GPIO_LOOKUP("neponset-mdm-ctl0", 2, "rts", GPIO_ACTIVE_LOW),
		GPIO_LOOKUP("neponset-mdm-ctl0", 3, "dtr", GPIO_ACTIVE_LOW),
		GPIO_LOOKUP("neponset-mdm-ctl1", 3, "cts", GPIO_ACTIVE_LOW),
		GPIO_LOOKUP("neponset-mdm-ctl1", 4, "dsr", GPIO_ACTIVE_LOW),
		GPIO_LOOKUP("neponset-mdm-ctl1", 5, "dcd", GPIO_ACTIVE_LOW),
		अणु पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा gpiod_lookup_table neponset_uart3_gpio_table = अणु
	.dev_id = "sa11x0-uart.3",
	.table = अणु
		GPIO_LOOKUP("neponset-mdm-ctl0", 0, "rts", GPIO_ACTIVE_LOW),
		GPIO_LOOKUP("neponset-mdm-ctl0", 1, "dtr", GPIO_ACTIVE_LOW),
		GPIO_LOOKUP("neponset-mdm-ctl1", 0, "cts", GPIO_ACTIVE_LOW),
		GPIO_LOOKUP("neponset-mdm-ctl1", 1, "dsr", GPIO_ACTIVE_LOW),
		GPIO_LOOKUP("neponset-mdm-ctl1", 2, "dcd", GPIO_ACTIVE_LOW),
		अणु पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा gpiod_lookup_table neponset_pcmcia_table = अणु
	.dev_id = "1800",
	.table = अणु
		GPIO_LOOKUP("sa1111", 1, "a0vcc", GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP("sa1111", 0, "a1vcc", GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP("neponset-ncr", 5, "a0vpp", GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP("neponset-ncr", 6, "a1vpp", GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP("sa1111", 2, "b0vcc", GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP("sa1111", 3, "b1vcc", GPIO_ACTIVE_HIGH),
		अणु पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा neponset_drvdata *nep;

व्योम neponset_ncr_frob(अचिन्हित पूर्णांक mask, अचिन्हित पूर्णांक val)
अणु
	काष्ठा neponset_drvdata *n = nep;
	अचिन्हित दीर्घ m = mask, v = val;

	अगर (nep)
		n->gpio[0]->set_multiple(n->gpio[0], &m, &v);
	अन्यथा
		WARN(1, "nep unset\n");
पूर्ण
EXPORT_SYMBOL(neponset_ncr_frob);

/*
 * Install handler क्रम Neponset IRQ.  Note that we have to loop here
 * since the ETHERNET and USAR IRQs are level based, and we need to
 * ensure that the IRQ संकेत is deनिश्चितed beक्रमe वापसing.  This
 * is rather unक्रमtunate.
 */
अटल व्योम neponset_irq_handler(काष्ठा irq_desc *desc)
अणु
	काष्ठा neponset_drvdata *d = irq_desc_get_handler_data(desc);
	अचिन्हित पूर्णांक irr;

	जबतक (1) अणु
		/*
		 * Acknowledge the parent IRQ.
		 */
		desc->irq_data.chip->irq_ack(&desc->irq_data);

		/*
		 * Read the पूर्णांकerrupt reason रेजिस्टर.  Let's have all
		 * active IRQ bits high.  Note: there is a typo in the
		 * Neponset user's guide क्रम the SA1111 IRR level.
		 */
		irr = पढ़ोb_relaxed(d->base + IRR);
		irr ^= IRR_ETHERNET | IRR_USAR;

		अगर ((irr & (IRR_ETHERNET | IRR_USAR | IRR_SA1111)) == 0)
			अवरोध;

		/*
		 * Since there is no inभागidual mask, we have to
		 * mask the parent IRQ.  This is safe, since we'll
		 * recheck the रेजिस्टर क्रम any pending IRQs.
		 */
		अगर (irr & (IRR_ETHERNET | IRR_USAR)) अणु
			desc->irq_data.chip->irq_mask(&desc->irq_data);

			/*
			 * Ack the पूर्णांकerrupt now to prevent re-entering
			 * this neponset handler.  Again, this is safe
			 * since we'll check the IRR रेजिस्टर prior to
			 * leaving.
			 */
			desc->irq_data.chip->irq_ack(&desc->irq_data);

			अगर (irr & IRR_ETHERNET)
				generic_handle_irq(d->irq_base + NEP_IRQ_SMC91X);

			अगर (irr & IRR_USAR)
				generic_handle_irq(d->irq_base + NEP_IRQ_USAR);

			desc->irq_data.chip->irq_unmask(&desc->irq_data);
		पूर्ण

		अगर (irr & IRR_SA1111)
			generic_handle_irq(d->irq_base + NEP_IRQ_SA1111);
	पूर्ण
पूर्ण

/* Yes, we really करो not have any kind of masking or unmasking */
अटल व्योम nochip_noop(काष्ठा irq_data *irq)
अणु
पूर्ण

अटल काष्ठा irq_chip nochip = अणु
	.name = "neponset",
	.irq_ack = nochip_noop,
	.irq_mask = nochip_noop,
	.irq_unmask = nochip_noop,
पूर्ण;

अटल पूर्णांक neponset_init_gpio(काष्ठा gpio_chip **gcp,
	काष्ठा device *dev, स्थिर अक्षर *label, व्योम __iomem *reg,
	अचिन्हित num, bool in, स्थिर अक्षर *स्थिर * names)
अणु
	काष्ठा gpio_chip *gc;

	gc = gpio_reg_init(dev, reg, -1, num, label, in ? 0xffffffff : 0,
			   पढ़ोl_relaxed(reg), names, शून्य, शून्य);
	अगर (IS_ERR(gc))
		वापस PTR_ERR(gc);

	*gcp = gc;

	वापस 0;
पूर्ण

अटल काष्ठा sa1111_platक्रमm_data sa1111_info = अणु
	.disable_devs	= SA1111_DEVID_PS2_MSE,
पूर्ण;

अटल पूर्णांक neponset_probe(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा neponset_drvdata *d;
	काष्ठा resource *nep_res, *sa1111_res, *smc91x_res;
	काष्ठा resource sa1111_resources[] = अणु
		DEFINE_RES_MEM(0x40000000, SZ_8K),
		अणु .flags = IORESOURCE_IRQ पूर्ण,
	पूर्ण;
	काष्ठा platक्रमm_device_info sa1111_devinfo = अणु
		.parent = &dev->dev,
		.name = "sa1111",
		.id = 0,
		.res = sa1111_resources,
		.num_res = ARRAY_SIZE(sa1111_resources),
		.data = &sa1111_info,
		.size_data = माप(sa1111_info),
		.dma_mask = 0xffffffffUL,
	पूर्ण;
	काष्ठा resource smc91x_resources[] = अणु
		DEFINE_RES_MEM_NAMED(SA1100_CS3_PHYS,
			0x02000000, "smc91x-regs"),
		DEFINE_RES_MEM_NAMED(SA1100_CS3_PHYS + 0x02000000,
			0x02000000, "smc91x-attrib"),
		अणु .flags = IORESOURCE_IRQ पूर्ण,
	पूर्ण;
	काष्ठा smc91x_platdata smc91x_platdata = अणु
		.flags = SMC91X_USE_8BIT | SMC91X_IO_SHIFT_2 | SMC91X_NOWAIT,
	पूर्ण;
	काष्ठा platक्रमm_device_info smc91x_devinfo = अणु
		.parent = &dev->dev,
		.name = "smc91x",
		.id = 0,
		.res = smc91x_resources,
		.num_res = ARRAY_SIZE(smc91x_resources),
		.data = &smc91x_platdata,
		.size_data = माप(smc91x_platdata),
	पूर्ण;
	पूर्णांक ret, irq;

	अगर (nep)
		वापस -EBUSY;

	irq = ret = platक्रमm_get_irq(dev, 0);
	अगर (ret < 0)
		जाओ err_alloc;

	nep_res = platक्रमm_get_resource(dev, IORESOURCE_MEM, 0);
	smc91x_res = platक्रमm_get_resource(dev, IORESOURCE_MEM, 1);
	sa1111_res = platक्रमm_get_resource(dev, IORESOURCE_MEM, 2);
	अगर (!nep_res || !smc91x_res || !sa1111_res) अणु
		ret = -ENXIO;
		जाओ err_alloc;
	पूर्ण

	d = kzalloc(माप(*d), GFP_KERNEL);
	अगर (!d) अणु
		ret = -ENOMEM;
		जाओ err_alloc;
	पूर्ण

	d->base = ioremap(nep_res->start, SZ_4K);
	अगर (!d->base) अणु
		ret = -ENOMEM;
		जाओ err_ioremap;
	पूर्ण

	अगर (पढ़ोb_relaxed(d->base + WHOAMI) != 0x11) अणु
		dev_warn(&dev->dev, "Neponset board detected, but wrong ID: %02x\n",
			 पढ़ोb_relaxed(d->base + WHOAMI));
		ret = -ENODEV;
		जाओ err_id;
	पूर्ण

	ret = irq_alloc_descs(-1, IRQ_BOARD_START, NEP_IRQ_NR, -1);
	अगर (ret <= 0) अणु
		dev_err(&dev->dev, "unable to allocate %u irqs: %d\n",
			NEP_IRQ_NR, ret);
		अगर (ret == 0)
			ret = -ENOMEM;
		जाओ err_irq_alloc;
	पूर्ण

	d->irq_base = ret;

	irq_set_chip_and_handler(d->irq_base + NEP_IRQ_SMC91X, &nochip,
		handle_simple_irq);
	irq_clear_status_flags(d->irq_base + NEP_IRQ_SMC91X, IRQ_NOREQUEST | IRQ_NOPROBE);
	irq_set_chip_and_handler(d->irq_base + NEP_IRQ_USAR, &nochip,
		handle_simple_irq);
	irq_clear_status_flags(d->irq_base + NEP_IRQ_USAR, IRQ_NOREQUEST | IRQ_NOPROBE);
	irq_set_chip(d->irq_base + NEP_IRQ_SA1111, &nochip);

	irq_set_irq_type(irq, IRQ_TYPE_EDGE_RISING);
	irq_set_chained_handler_and_data(irq, neponset_irq_handler, d);

	/* Disable GPIO 0/1 drivers so the buttons work on the Assabet */
	ग_लिखोb_relaxed(NCR_GP01_OFF, d->base + NCR_0);

	neponset_init_gpio(&d->gpio[0], &dev->dev, "neponset-ncr",
			   d->base + NCR_0, NCR_NGPIO, false,
			   neponset_ncr_names);
	neponset_init_gpio(&d->gpio[1], &dev->dev, "neponset-mdm-ctl0",
			   d->base + MDM_CTL_0, MDM_CTL0_NGPIO, false,
			   neponset_mdmctl0_names);
	neponset_init_gpio(&d->gpio[2], &dev->dev, "neponset-mdm-ctl1",
			   d->base + MDM_CTL_1, MDM_CTL1_NGPIO, true,
			   neponset_mdmctl1_names);
	neponset_init_gpio(&d->gpio[3], &dev->dev, "neponset-aud-ctl",
			   d->base + AUD_CTL, AUD_NGPIO, false,
			   neponset_aud_names);

	gpiod_add_lookup_table(&neponset_uart1_gpio_table);
	gpiod_add_lookup_table(&neponset_uart3_gpio_table);
	gpiod_add_lookup_table(&neponset_pcmcia_table);

	/*
	 * We would set IRQ_GPIO25 to be a wake-up IRQ, but unक्रमtunately
	 * something on the Neponset activates this IRQ on sleep (eth?)
	 */
#अगर 0
	enable_irq_wake(irq);
#पूर्ण_अगर

	dev_info(&dev->dev, "Neponset daughter board, providing IRQ%u-%u\n",
		 d->irq_base, d->irq_base + NEP_IRQ_NR - 1);
	nep = d;

	/* Ensure that the memory bus request/grant संकेतs are setup */
	sa1110_mb_disable();

	sa1111_resources[0].parent = sa1111_res;
	sa1111_resources[1].start = d->irq_base + NEP_IRQ_SA1111;
	sa1111_resources[1].end = d->irq_base + NEP_IRQ_SA1111;
	d->sa1111 = platक्रमm_device_रेजिस्टर_full(&sa1111_devinfo);

	smc91x_resources[0].parent = smc91x_res;
	smc91x_resources[1].parent = smc91x_res;
	smc91x_resources[2].start = d->irq_base + NEP_IRQ_SMC91X;
	smc91x_resources[2].end = d->irq_base + NEP_IRQ_SMC91X;
	d->smc91x = platक्रमm_device_रेजिस्टर_full(&smc91x_devinfo);

	platक्रमm_set_drvdata(dev, d);

	वापस 0;

 err_irq_alloc:
 err_id:
	iounmap(d->base);
 err_ioremap:
	kमुक्त(d);
 err_alloc:
	वापस ret;
पूर्ण

अटल पूर्णांक neponset_हटाओ(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा neponset_drvdata *d = platक्रमm_get_drvdata(dev);
	पूर्णांक irq = platक्रमm_get_irq(dev, 0);

	अगर (!IS_ERR(d->sa1111))
		platक्रमm_device_unरेजिस्टर(d->sa1111);
	अगर (!IS_ERR(d->smc91x))
		platक्रमm_device_unरेजिस्टर(d->smc91x);

	gpiod_हटाओ_lookup_table(&neponset_pcmcia_table);
	gpiod_हटाओ_lookup_table(&neponset_uart3_gpio_table);
	gpiod_हटाओ_lookup_table(&neponset_uart1_gpio_table);

	irq_set_chained_handler(irq, शून्य);
	irq_मुक्त_descs(d->irq_base, NEP_IRQ_NR);
	nep = शून्य;
	iounmap(d->base);
	kमुक्त(d);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक neponset_resume(काष्ठा device *dev)
अणु
	काष्ठा neponset_drvdata *d = dev_get_drvdata(dev);
	पूर्णांक i, ret = 0;

	क्रम (i = 0; i < ARRAY_SIZE(d->gpio); i++) अणु
		ret = gpio_reg_resume(d->gpio[i]);
		अगर (ret)
			अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops neponset_pm_ops = अणु
	.resume_noirq = neponset_resume,
	.restore_noirq = neponset_resume,
पूर्ण;
#घोषणा PM_OPS &neponset_pm_ops
#अन्यथा
#घोषणा PM_OPS शून्य
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver neponset_device_driver = अणु
	.probe		= neponset_probe,
	.हटाओ		= neponset_हटाओ,
	.driver		= अणु
		.name	= "neponset",
		.pm	= PM_OPS,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init neponset_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&neponset_device_driver);
पूर्ण

subsys_initcall(neponset_init);
