<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *
 *  Copyright (C) 2012 John Crispin <john@phrozen.org>
 */

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/mutex.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/of.h>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/पन.स>
#समावेश <linux/slab.h>

#समावेश <lantiq_soc.h>

/*
 * By attaching hardware latches to the EBU it is possible to create output
 * only gpios. This driver configures a special memory address, which when
 * written to outमाला_दो 16 bit to the latches.
 */

#घोषणा LTQ_EBU_BUSCON	0x1e7ff		/* 16 bit access, slowest timing */
#घोषणा LTQ_EBU_WP	0x80000000	/* ग_लिखो protect bit */

काष्ठा ltq_mm अणु
	काष्ठा of_mm_gpio_chip mmchip;
	u16 shaकरोw;	/* shaकरोw the latches state */
पूर्ण;

/**
 * ltq_mm_apply() - ग_लिखो the shaकरोw value to the ebu address.
 * @chip:     Poपूर्णांकer to our निजी data काष्ठाure.
 *
 * Write the shaकरोw value to the EBU to set the gpios. We need to set the
 * global EBU lock to make sure that PCI/MTD करोn't अवरोध.
 */
अटल व्योम ltq_mm_apply(काष्ठा ltq_mm *chip)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ebu_lock, flags);
	ltq_ebu_w32(LTQ_EBU_BUSCON, LTQ_EBU_BUSCON1);
	__raw_ग_लिखोw(chip->shaकरोw, chip->mmchip.regs);
	ltq_ebu_w32(LTQ_EBU_BUSCON | LTQ_EBU_WP, LTQ_EBU_BUSCON1);
	spin_unlock_irqrestore(&ebu_lock, flags);
पूर्ण

/**
 * ltq_mm_set() - gpio_chip->set - set gpios.
 * @gc:     Poपूर्णांकer to gpio_chip device काष्ठाure.
 * @gpio:   GPIO संकेत number.
 * @val:    Value to be written to specअगरied संकेत.
 *
 * Set the shaकरोw value and call ltq_mm_apply.
 */
अटल व्योम ltq_mm_set(काष्ठा gpio_chip *gc, अचिन्हित offset, पूर्णांक value)
अणु
	काष्ठा ltq_mm *chip = gpiochip_get_data(gc);

	अगर (value)
		chip->shaकरोw |= (1 << offset);
	अन्यथा
		chip->shaकरोw &= ~(1 << offset);
	ltq_mm_apply(chip);
पूर्ण

/**
 * ltq_mm_dir_out() - gpio_chip->dir_out - set gpio direction.
 * @gc:     Poपूर्णांकer to gpio_chip device काष्ठाure.
 * @gpio:   GPIO संकेत number.
 * @val:    Value to be written to specअगरied संकेत.
 *
 * Same as ltq_mm_set, always वापसs 0.
 */
अटल पूर्णांक ltq_mm_dir_out(काष्ठा gpio_chip *gc, अचिन्हित offset, पूर्णांक value)
अणु
	ltq_mm_set(gc, offset, value);

	वापस 0;
पूर्ण

/**
 * ltq_mm_save_regs() - Set initial values of GPIO pins
 * @mm_gc: poपूर्णांकer to memory mapped GPIO chip काष्ठाure
 */
अटल व्योम ltq_mm_save_regs(काष्ठा of_mm_gpio_chip *mm_gc)
अणु
	काष्ठा ltq_mm *chip =
		container_of(mm_gc, काष्ठा ltq_mm, mmchip);

	/* tell the ebu controller which memory address we will be using */
	ltq_ebu_w32(CPHYSADDR(chip->mmchip.regs) | 0x1, LTQ_EBU_ADDRSEL1);

	ltq_mm_apply(chip);
पूर्ण

अटल पूर्णांक ltq_mm_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ltq_mm *chip;
	u32 shaकरोw;

	chip = devm_kzalloc(&pdev->dev, माप(*chip), GFP_KERNEL);
	अगर (!chip)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, chip);

	chip->mmchip.gc.ngpio = 16;
	chip->mmchip.gc.direction_output = ltq_mm_dir_out;
	chip->mmchip.gc.set = ltq_mm_set;
	chip->mmchip.save_regs = ltq_mm_save_regs;

	/* store the shaकरोw value अगर one was passed by the devicetree */
	अगर (!of_property_पढ़ो_u32(pdev->dev.of_node, "lantiq,shadow", &shaकरोw))
		chip->shaकरोw = shaकरोw;

	वापस of_mm_gpiochip_add_data(pdev->dev.of_node, &chip->mmchip, chip);
पूर्ण

अटल पूर्णांक ltq_mm_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ltq_mm *chip = platक्रमm_get_drvdata(pdev);

	of_mm_gpiochip_हटाओ(&chip->mmchip);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id ltq_mm_match[] = अणु
	अणु .compatible = "lantiq,gpio-mm" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, ltq_mm_match);

अटल काष्ठा platक्रमm_driver ltq_mm_driver = अणु
	.probe = ltq_mm_probe,
	.हटाओ = ltq_mm_हटाओ,
	.driver = अणु
		.name = "gpio-mm-ltq",
		.of_match_table = ltq_mm_match,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init ltq_mm_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&ltq_mm_driver);
पूर्ण

subsys_initcall(ltq_mm_init);

अटल व्योम __निकास ltq_mm_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&ltq_mm_driver);
पूर्ण
module_निकास(ltq_mm_निकास);
