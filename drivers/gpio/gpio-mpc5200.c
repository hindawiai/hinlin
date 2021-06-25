<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * MPC52xx gpio driver
 *
 * Copyright (c) 2008 Sascha Hauer <s.hauer@pengutronix.de>, Pengutronix
 */

#समावेश <linux/of.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/पन.स>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/module.h>

#समावेश <यंत्र/mpc52xx.h>
#समावेश <sysdev/fsl_soc.h>

अटल DEFINE_SPINLOCK(gpio_lock);

काष्ठा mpc52xx_gpiochip अणु
	काष्ठा of_mm_gpio_chip mmchip;
	अचिन्हित पूर्णांक shaकरोw_dvo;
	अचिन्हित पूर्णांक shaकरोw_gpioe;
	अचिन्हित पूर्णांक shaकरोw_ddr;
पूर्ण;

/*
 * GPIO LIB API implementation क्रम wakeup GPIOs.
 *
 * There's a maximum of 8 wakeup GPIOs. Which of these are available
 * क्रम use depends on your board setup.
 *
 * 0 -> GPIO_WKUP_7
 * 1 -> GPIO_WKUP_6
 * 2 -> PSC6_1
 * 3 -> PSC6_0
 * 4 -> ETH_17
 * 5 -> PSC3_9
 * 6 -> PSC2_4
 * 7 -> PSC1_4
 *
 */
अटल पूर्णांक mpc52xx_wkup_gpio_get(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक gpio)
अणु
	काष्ठा of_mm_gpio_chip *mm_gc = to_of_mm_gpio_chip(gc);
	काष्ठा mpc52xx_gpio_wkup __iomem *regs = mm_gc->regs;
	अचिन्हित पूर्णांक ret;

	ret = (in_8(&regs->wkup_ival) >> (7 - gpio)) & 1;

	pr_debug("%s: gpio: %d ret: %d\n", __func__, gpio, ret);

	वापस ret;
पूर्ण

अटल अंतरभूत व्योम
__mpc52xx_wkup_gpio_set(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक gpio, पूर्णांक val)
अणु
	काष्ठा of_mm_gpio_chip *mm_gc = to_of_mm_gpio_chip(gc);
	काष्ठा mpc52xx_gpiochip *chip = gpiochip_get_data(gc);
	काष्ठा mpc52xx_gpio_wkup __iomem *regs = mm_gc->regs;

	अगर (val)
		chip->shaकरोw_dvo |= 1 << (7 - gpio);
	अन्यथा
		chip->shaकरोw_dvo &= ~(1 << (7 - gpio));

	out_8(&regs->wkup_dvo, chip->shaकरोw_dvo);
पूर्ण

अटल व्योम
mpc52xx_wkup_gpio_set(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक gpio, पूर्णांक val)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&gpio_lock, flags);

	__mpc52xx_wkup_gpio_set(gc, gpio, val);

	spin_unlock_irqrestore(&gpio_lock, flags);

	pr_debug("%s: gpio: %d val: %d\n", __func__, gpio, val);
पूर्ण

अटल पूर्णांक mpc52xx_wkup_gpio_dir_in(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक gpio)
अणु
	काष्ठा of_mm_gpio_chip *mm_gc = to_of_mm_gpio_chip(gc);
	काष्ठा mpc52xx_gpiochip *chip = gpiochip_get_data(gc);
	काष्ठा mpc52xx_gpio_wkup __iomem *regs = mm_gc->regs;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&gpio_lock, flags);

	/* set the direction */
	chip->shaकरोw_ddr &= ~(1 << (7 - gpio));
	out_8(&regs->wkup_ddr, chip->shaकरोw_ddr);

	/* and enable the pin */
	chip->shaकरोw_gpioe |= 1 << (7 - gpio);
	out_8(&regs->wkup_gpioe, chip->shaकरोw_gpioe);

	spin_unlock_irqrestore(&gpio_lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक
mpc52xx_wkup_gpio_dir_out(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक gpio, पूर्णांक val)
अणु
	काष्ठा of_mm_gpio_chip *mm_gc = to_of_mm_gpio_chip(gc);
	काष्ठा mpc52xx_gpio_wkup __iomem *regs = mm_gc->regs;
	काष्ठा mpc52xx_gpiochip *chip = gpiochip_get_data(gc);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&gpio_lock, flags);

	__mpc52xx_wkup_gpio_set(gc, gpio, val);

	/* Then set direction */
	chip->shaकरोw_ddr |= 1 << (7 - gpio);
	out_8(&regs->wkup_ddr, chip->shaकरोw_ddr);

	/* Finally enable the pin */
	chip->shaकरोw_gpioe |= 1 << (7 - gpio);
	out_8(&regs->wkup_gpioe, chip->shaकरोw_gpioe);

	spin_unlock_irqrestore(&gpio_lock, flags);

	pr_debug("%s: gpio: %d val: %d\n", __func__, gpio, val);

	वापस 0;
पूर्ण

अटल पूर्णांक mpc52xx_wkup_gpiochip_probe(काष्ठा platक्रमm_device *ofdev)
अणु
	काष्ठा mpc52xx_gpiochip *chip;
	काष्ठा mpc52xx_gpio_wkup __iomem *regs;
	काष्ठा gpio_chip *gc;
	पूर्णांक ret;

	chip = devm_kzalloc(&ofdev->dev, माप(*chip), GFP_KERNEL);
	अगर (!chip)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(ofdev, chip);

	gc = &chip->mmchip.gc;

	gc->ngpio            = 8;
	gc->direction_input  = mpc52xx_wkup_gpio_dir_in;
	gc->direction_output = mpc52xx_wkup_gpio_dir_out;
	gc->get              = mpc52xx_wkup_gpio_get;
	gc->set              = mpc52xx_wkup_gpio_set;

	ret = of_mm_gpiochip_add_data(ofdev->dev.of_node, &chip->mmchip, chip);
	अगर (ret)
		वापस ret;

	regs = chip->mmchip.regs;
	chip->shaकरोw_gpioe = in_8(&regs->wkup_gpioe);
	chip->shaकरोw_ddr = in_8(&regs->wkup_ddr);
	chip->shaकरोw_dvo = in_8(&regs->wkup_dvo);

	वापस 0;
पूर्ण

अटल पूर्णांक mpc52xx_gpiochip_हटाओ(काष्ठा platक्रमm_device *ofdev)
अणु
	काष्ठा mpc52xx_gpiochip *chip = platक्रमm_get_drvdata(ofdev);

	of_mm_gpiochip_हटाओ(&chip->mmchip);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id mpc52xx_wkup_gpiochip_match[] = अणु
	अणु .compatible = "fsl,mpc5200-gpio-wkup", पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver mpc52xx_wkup_gpiochip_driver = अणु
	.driver = अणु
		.name = "mpc5200-gpio-wkup",
		.of_match_table = mpc52xx_wkup_gpiochip_match,
	पूर्ण,
	.probe = mpc52xx_wkup_gpiochip_probe,
	.हटाओ = mpc52xx_gpiochip_हटाओ,
पूर्ण;

/*
 * GPIO LIB API implementation क्रम simple GPIOs
 *
 * There's a maximum of 32 simple GPIOs. Which of these are available
 * क्रम use depends on your board setup.
 * The numbering reflects the bit numbering in the port रेजिस्टरs:
 *
 *  0..1  > reserved
 *  2..3  > IRDA
 *  4..7  > ETHR
 *  8..11 > reserved
 * 12..15 > USB
 * 16..17 > reserved
 * 18..23 > PSC3
 * 24..27 > PSC2
 * 28..31 > PSC1
 */
अटल पूर्णांक mpc52xx_simple_gpio_get(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक gpio)
अणु
	काष्ठा of_mm_gpio_chip *mm_gc = to_of_mm_gpio_chip(gc);
	काष्ठा mpc52xx_gpio __iomem *regs = mm_gc->regs;
	अचिन्हित पूर्णांक ret;

	ret = (in_be32(&regs->simple_ival) >> (31 - gpio)) & 1;

	वापस ret;
पूर्ण

अटल अंतरभूत व्योम
__mpc52xx_simple_gpio_set(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक gpio, पूर्णांक val)
अणु
	काष्ठा of_mm_gpio_chip *mm_gc = to_of_mm_gpio_chip(gc);
	काष्ठा mpc52xx_gpiochip *chip = gpiochip_get_data(gc);
	काष्ठा mpc52xx_gpio __iomem *regs = mm_gc->regs;

	अगर (val)
		chip->shaकरोw_dvo |= 1 << (31 - gpio);
	अन्यथा
		chip->shaकरोw_dvo &= ~(1 << (31 - gpio));
	out_be32(&regs->simple_dvo, chip->shaकरोw_dvo);
पूर्ण

अटल व्योम
mpc52xx_simple_gpio_set(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक gpio, पूर्णांक val)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&gpio_lock, flags);

	__mpc52xx_simple_gpio_set(gc, gpio, val);

	spin_unlock_irqrestore(&gpio_lock, flags);

	pr_debug("%s: gpio: %d val: %d\n", __func__, gpio, val);
पूर्ण

अटल पूर्णांक mpc52xx_simple_gpio_dir_in(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक gpio)
अणु
	काष्ठा of_mm_gpio_chip *mm_gc = to_of_mm_gpio_chip(gc);
	काष्ठा mpc52xx_gpiochip *chip = gpiochip_get_data(gc);
	काष्ठा mpc52xx_gpio __iomem *regs = mm_gc->regs;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&gpio_lock, flags);

	/* set the direction */
	chip->shaकरोw_ddr &= ~(1 << (31 - gpio));
	out_be32(&regs->simple_ddr, chip->shaकरोw_ddr);

	/* and enable the pin */
	chip->shaकरोw_gpioe |= 1 << (31 - gpio);
	out_be32(&regs->simple_gpioe, chip->shaकरोw_gpioe);

	spin_unlock_irqrestore(&gpio_lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक
mpc52xx_simple_gpio_dir_out(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक gpio, पूर्णांक val)
अणु
	काष्ठा of_mm_gpio_chip *mm_gc = to_of_mm_gpio_chip(gc);
	काष्ठा mpc52xx_gpiochip *chip = gpiochip_get_data(gc);
	काष्ठा mpc52xx_gpio __iomem *regs = mm_gc->regs;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&gpio_lock, flags);

	/* First set initial value */
	__mpc52xx_simple_gpio_set(gc, gpio, val);

	/* Then set direction */
	chip->shaकरोw_ddr |= 1 << (31 - gpio);
	out_be32(&regs->simple_ddr, chip->shaकरोw_ddr);

	/* Finally enable the pin */
	chip->shaकरोw_gpioe |= 1 << (31 - gpio);
	out_be32(&regs->simple_gpioe, chip->shaकरोw_gpioe);

	spin_unlock_irqrestore(&gpio_lock, flags);

	pr_debug("%s: gpio: %d val: %d\n", __func__, gpio, val);

	वापस 0;
पूर्ण

अटल पूर्णांक mpc52xx_simple_gpiochip_probe(काष्ठा platक्रमm_device *ofdev)
अणु
	काष्ठा mpc52xx_gpiochip *chip;
	काष्ठा gpio_chip *gc;
	काष्ठा mpc52xx_gpio __iomem *regs;
	पूर्णांक ret;

	chip = devm_kzalloc(&ofdev->dev, माप(*chip), GFP_KERNEL);
	अगर (!chip)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(ofdev, chip);

	gc = &chip->mmchip.gc;

	gc->ngpio            = 32;
	gc->direction_input  = mpc52xx_simple_gpio_dir_in;
	gc->direction_output = mpc52xx_simple_gpio_dir_out;
	gc->get              = mpc52xx_simple_gpio_get;
	gc->set              = mpc52xx_simple_gpio_set;

	ret = of_mm_gpiochip_add_data(ofdev->dev.of_node, &chip->mmchip, chip);
	अगर (ret)
		वापस ret;

	regs = chip->mmchip.regs;
	chip->shaकरोw_gpioe = in_be32(&regs->simple_gpioe);
	chip->shaकरोw_ddr = in_be32(&regs->simple_ddr);
	chip->shaकरोw_dvo = in_be32(&regs->simple_dvo);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id mpc52xx_simple_gpiochip_match[] = अणु
	अणु .compatible = "fsl,mpc5200-gpio", पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver mpc52xx_simple_gpiochip_driver = अणु
	.driver = अणु
		.name = "mpc5200-gpio",
		.of_match_table = mpc52xx_simple_gpiochip_match,
	पूर्ण,
	.probe = mpc52xx_simple_gpiochip_probe,
	.हटाओ = mpc52xx_gpiochip_हटाओ,
पूर्ण;

अटल काष्ठा platक्रमm_driver * स्थिर drivers[] = अणु
	&mpc52xx_wkup_gpiochip_driver,
	&mpc52xx_simple_gpiochip_driver,
पूर्ण;

अटल पूर्णांक __init mpc52xx_gpio_init(व्योम)
अणु
	वापस platक्रमm_रेजिस्टर_drivers(drivers, ARRAY_SIZE(drivers));
पूर्ण

/* Make sure we get initialised beक्रमe anyone अन्यथा tries to use us */
subsys_initcall(mpc52xx_gpio_init);

अटल व्योम __निकास mpc52xx_gpio_निकास(व्योम)
अणु
	platक्रमm_unरेजिस्टर_drivers(drivers, ARRAY_SIZE(drivers));
पूर्ण
module_निकास(mpc52xx_gpio_निकास);

MODULE_DESCRIPTION("Freescale MPC52xx gpio driver");
MODULE_AUTHOR("Sascha Hauer <s.hauer@pengutronix.de");
MODULE_LICENSE("GPL v2");

