<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *
 *  Copyright (C) 2012 John Crispin <john@phrozen.org>
 */

#समावेश <linux/slab.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/mutex.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/पन.स>
#समावेश <linux/clk.h>
#समावेश <linux/err.h>

/*
 * The Serial To Parallel (STP) is found on MIPS based Lantiq socs. It is a
 * peripheral controller used to drive बाह्यal shअगरt रेजिस्टर cascades. At most
 * 3 groups of 8 bits can be driven. The hardware is able to allow the DSL modem
 * to drive the 2 LSBs of the cascade स्वतःmatically.
 */

/* control रेजिस्टर 0 */
#घोषणा XWAY_STP_CON0		0x00
/* control रेजिस्टर 1 */
#घोषणा XWAY_STP_CON1		0x04
/* data रेजिस्टर 0 */
#घोषणा XWAY_STP_CPU0		0x08
/* data रेजिस्टर 1 */
#घोषणा XWAY_STP_CPU1		0x0C
/* access रेजिस्टर */
#घोषणा XWAY_STP_AR		0x10

/* software or hardware update select bit */
#घोषणा XWAY_STP_CON_SWU	BIT(31)

/* स्वतःmatic update rates */
#घोषणा XWAY_STP_2HZ		0
#घोषणा XWAY_STP_4HZ		BIT(23)
#घोषणा XWAY_STP_8HZ		BIT(24)
#घोषणा XWAY_STP_10HZ		(BIT(24) | BIT(23))
#घोषणा XWAY_STP_SPEED_MASK	(BIT(23) | BIT(24) | BIT(25) | BIT(26) | BIT(27))

#घोषणा XWAY_STP_FPIS_VALUE	BIT(21)
#घोषणा XWAY_STP_FPIS_MASK	(BIT(20) | BIT(21))

/* घड़ी source क्रम स्वतःmatic update */
#घोषणा XWAY_STP_UPD_FPI	BIT(31)
#घोषणा XWAY_STP_UPD_MASK	(BIT(31) | BIT(30))

/* let the adsl core drive the 2 LSBs */
#घोषणा XWAY_STP_ADSL_SHIFT	24
#घोषणा XWAY_STP_ADSL_MASK	0x3

/* 2 groups of 3 bits can be driven by the phys */
#घोषणा XWAY_STP_PHY_MASK	0x7
#घोषणा XWAY_STP_PHY1_SHIFT	27
#घोषणा XWAY_STP_PHY2_SHIFT	3
#घोषणा XWAY_STP_PHY3_SHIFT	6
#घोषणा XWAY_STP_PHY4_SHIFT	15

/* STP has 3 groups of 8 bits */
#घोषणा XWAY_STP_GROUP0		BIT(0)
#घोषणा XWAY_STP_GROUP1		BIT(1)
#घोषणा XWAY_STP_GROUP2		BIT(2)
#घोषणा XWAY_STP_GROUP_MASK	(0x7)

/* Edge configuration bits */
#घोषणा XWAY_STP_FALLING	BIT(26)
#घोषणा XWAY_STP_EDGE_MASK	BIT(26)

#घोषणा xway_stp_r32(m, reg)		__raw_पढ़ोl(m + reg)
#घोषणा xway_stp_w32(m, val, reg)	__raw_ग_लिखोl(val, m + reg)
#घोषणा xway_stp_w32_mask(m, clear, set, reg) \
		xway_stp_w32(m, (xway_stp_r32(m, reg) & ~(clear)) | (set), reg)

काष्ठा xway_stp अणु
	काष्ठा gpio_chip gc;
	व्योम __iomem *virt;
	u32 edge;	/* rising or falling edge triggered shअगरt रेजिस्टर */
	u32 shaकरोw;	/* shaकरोw the shअगरt रेजिस्टरs state */
	u8 groups;	/* we can drive 1-3 groups of 8bit each */
	u8 dsl;		/* the 2 LSBs can be driven by the dsl core */
	u8 phy1;	/* 3 bits can be driven by phy1 */
	u8 phy2;	/* 3 bits can be driven by phy2 */
	u8 phy3;	/* 3 bits can be driven by phy3 */
	u8 phy4;	/* 3 bits can be driven by phy4 */
	u8 reserved;	/* mask out the hw driven bits in gpio_request */
पूर्ण;

/**
 * xway_stp_get() - gpio_chip->get - get gpios.
 * @gc:     Poपूर्णांकer to gpio_chip device काष्ठाure.
 * @gpio:   GPIO संकेत number.
 *
 * Gets the shaकरोw value.
 */
अटल पूर्णांक xway_stp_get(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक gpio)
अणु
	काष्ठा xway_stp *chip = gpiochip_get_data(gc);

	वापस (xway_stp_r32(chip->virt, XWAY_STP_CPU0) & BIT(gpio));
पूर्ण

/**
 * xway_stp_set() - gpio_chip->set - set gpios.
 * @gc:     Poपूर्णांकer to gpio_chip device काष्ठाure.
 * @gpio:   GPIO संकेत number.
 * @val:    Value to be written to specअगरied संकेत.
 *
 * Set the shaकरोw value and call ltq_ebu_apply.
 */
अटल व्योम xway_stp_set(काष्ठा gpio_chip *gc, अचिन्हित gpio, पूर्णांक val)
अणु
	काष्ठा xway_stp *chip = gpiochip_get_data(gc);

	अगर (val)
		chip->shaकरोw |= BIT(gpio);
	अन्यथा
		chip->shaकरोw &= ~BIT(gpio);
	xway_stp_w32(chip->virt, chip->shaकरोw, XWAY_STP_CPU0);
	अगर (!chip->reserved)
		xway_stp_w32_mask(chip->virt, 0, XWAY_STP_CON_SWU, XWAY_STP_CON0);
पूर्ण

/**
 * xway_stp_dir_out() - gpio_chip->dir_out - set gpio direction.
 * @gc:     Poपूर्णांकer to gpio_chip device काष्ठाure.
 * @gpio:   GPIO संकेत number.
 * @val:    Value to be written to specअगरied संकेत.
 *
 * Same as xway_stp_set, always वापसs 0.
 */
अटल पूर्णांक xway_stp_dir_out(काष्ठा gpio_chip *gc, अचिन्हित gpio, पूर्णांक val)
अणु
	xway_stp_set(gc, gpio, val);

	वापस 0;
पूर्ण

/**
 * xway_stp_request() - gpio_chip->request
 * @gc:     Poपूर्णांकer to gpio_chip device काष्ठाure.
 * @gpio:   GPIO संकेत number.
 *
 * We mask out the HW driven pins
 */
अटल पूर्णांक xway_stp_request(काष्ठा gpio_chip *gc, अचिन्हित gpio)
अणु
	काष्ठा xway_stp *chip = gpiochip_get_data(gc);

	अगर ((gpio < 8) && (chip->reserved & BIT(gpio))) अणु
		dev_err(gc->parent, "GPIO %d is driven by hardware\n", gpio);
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * xway_stp_hw_init() - Configure the STP unit and enable the घड़ी gate
 * @chip: Poपूर्णांकer to the xway_stp chip काष्ठाure
 */
अटल व्योम xway_stp_hw_init(काष्ठा xway_stp *chip)
अणु
	/* sane शेषs */
	xway_stp_w32(chip->virt, 0, XWAY_STP_AR);
	xway_stp_w32(chip->virt, 0, XWAY_STP_CPU0);
	xway_stp_w32(chip->virt, 0, XWAY_STP_CPU1);
	xway_stp_w32(chip->virt, XWAY_STP_CON_SWU, XWAY_STP_CON0);
	xway_stp_w32(chip->virt, 0, XWAY_STP_CON1);

	/* apply edge trigger settings क्रम the shअगरt रेजिस्टर */
	xway_stp_w32_mask(chip->virt, XWAY_STP_EDGE_MASK,
				chip->edge, XWAY_STP_CON0);

	/* apply led group settings */
	xway_stp_w32_mask(chip->virt, XWAY_STP_GROUP_MASK,
				chip->groups, XWAY_STP_CON1);

	/* tell the hardware which pins are controlled by the dsl modem */
	xway_stp_w32_mask(chip->virt,
			XWAY_STP_ADSL_MASK << XWAY_STP_ADSL_SHIFT,
			chip->dsl << XWAY_STP_ADSL_SHIFT,
			XWAY_STP_CON0);

	/* tell the hardware which pins are controlled by the phys */
	xway_stp_w32_mask(chip->virt,
			XWAY_STP_PHY_MASK << XWAY_STP_PHY1_SHIFT,
			chip->phy1 << XWAY_STP_PHY1_SHIFT,
			XWAY_STP_CON0);
	xway_stp_w32_mask(chip->virt,
			XWAY_STP_PHY_MASK << XWAY_STP_PHY2_SHIFT,
			chip->phy2 << XWAY_STP_PHY2_SHIFT,
			XWAY_STP_CON1);

	अगर (of_machine_is_compatible("lantiq,grx390")
	    || of_machine_is_compatible("lantiq,ar10")) अणु
		xway_stp_w32_mask(chip->virt,
				XWAY_STP_PHY_MASK << XWAY_STP_PHY3_SHIFT,
				chip->phy3 << XWAY_STP_PHY3_SHIFT,
				XWAY_STP_CON1);
	पूर्ण

	अगर (of_machine_is_compatible("lantiq,grx390")) अणु
		xway_stp_w32_mask(chip->virt,
				XWAY_STP_PHY_MASK << XWAY_STP_PHY4_SHIFT,
				chip->phy4 << XWAY_STP_PHY4_SHIFT,
				XWAY_STP_CON1);
	पूर्ण

	/* mask out the hw driven bits in gpio_request */
	chip->reserved = (chip->phy4 << 11) | (chip->phy3 << 8) | (chip->phy2 << 5)
		| (chip->phy1 << 2) | chip->dsl;

	/*
	 * अगर we have pins that are driven by hw, we need to tell the stp what
	 * घड़ी to use as a समयr.
	 */
	अगर (chip->reserved) अणु
		xway_stp_w32_mask(chip->virt, XWAY_STP_UPD_MASK,
			XWAY_STP_UPD_FPI, XWAY_STP_CON1);
		xway_stp_w32_mask(chip->virt, XWAY_STP_SPEED_MASK,
			XWAY_STP_10HZ, XWAY_STP_CON1);
		xway_stp_w32_mask(chip->virt, XWAY_STP_FPIS_MASK,
			XWAY_STP_FPIS_VALUE, XWAY_STP_CON1);
	पूर्ण
पूर्ण

अटल पूर्णांक xway_stp_probe(काष्ठा platक्रमm_device *pdev)
अणु
	u32 shaकरोw, groups, dsl, phy;
	काष्ठा xway_stp *chip;
	काष्ठा clk *clk;
	पूर्णांक ret = 0;

	chip = devm_kzalloc(&pdev->dev, माप(*chip), GFP_KERNEL);
	अगर (!chip)
		वापस -ENOMEM;

	chip->virt = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(chip->virt))
		वापस PTR_ERR(chip->virt);

	chip->gc.parent = &pdev->dev;
	chip->gc.label = "stp-xway";
	chip->gc.direction_output = xway_stp_dir_out;
	chip->gc.get = xway_stp_get;
	chip->gc.set = xway_stp_set;
	chip->gc.request = xway_stp_request;
	chip->gc.base = -1;
	chip->gc.owner = THIS_MODULE;

	/* store the shaकरोw value अगर one was passed by the devicetree */
	अगर (!of_property_पढ़ो_u32(pdev->dev.of_node, "lantiq,shadow", &shaकरोw))
		chip->shaकरोw = shaकरोw;

	/* find out which gpio groups should be enabled */
	अगर (!of_property_पढ़ो_u32(pdev->dev.of_node, "lantiq,groups", &groups))
		chip->groups = groups & XWAY_STP_GROUP_MASK;
	अन्यथा
		chip->groups = XWAY_STP_GROUP0;
	chip->gc.ngpio = fls(chip->groups) * 8;

	/* find out which gpios are controlled by the dsl core */
	अगर (!of_property_पढ़ो_u32(pdev->dev.of_node, "lantiq,dsl", &dsl))
		chip->dsl = dsl & XWAY_STP_ADSL_MASK;

	/* find out which gpios are controlled by the phys */
	अगर (of_machine_is_compatible("lantiq,ar9") ||
			of_machine_is_compatible("lantiq,gr9") ||
			of_machine_is_compatible("lantiq,vr9") ||
			of_machine_is_compatible("lantiq,ar10") ||
			of_machine_is_compatible("lantiq,grx390")) अणु
		अगर (!of_property_पढ़ो_u32(pdev->dev.of_node, "lantiq,phy1", &phy))
			chip->phy1 = phy & XWAY_STP_PHY_MASK;
		अगर (!of_property_पढ़ो_u32(pdev->dev.of_node, "lantiq,phy2", &phy))
			chip->phy2 = phy & XWAY_STP_PHY_MASK;
	पूर्ण

	अगर (of_machine_is_compatible("lantiq,ar10") ||
			of_machine_is_compatible("lantiq,grx390")) अणु
		अगर (!of_property_पढ़ो_u32(pdev->dev.of_node, "lantiq,phy3", &phy))
			chip->phy3 = phy & XWAY_STP_PHY_MASK;
	पूर्ण

	अगर (of_machine_is_compatible("lantiq,grx390")) अणु
		अगर (!of_property_पढ़ो_u32(pdev->dev.of_node, "lantiq,phy4", &phy))
			chip->phy4 = phy & XWAY_STP_PHY_MASK;
	पूर्ण

	/* check which edge trigger we should use, शेष to a falling edge */
	अगर (!of_find_property(pdev->dev.of_node, "lantiq,rising", शून्य))
		chip->edge = XWAY_STP_FALLING;

	clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(clk)) अणु
		dev_err(&pdev->dev, "Failed to get clock\n");
		वापस PTR_ERR(clk);
	पूर्ण

	ret = clk_prepare_enable(clk);
	अगर (ret)
		वापस ret;

	xway_stp_hw_init(chip);

	ret = devm_gpiochip_add_data(&pdev->dev, &chip->gc, chip);
	अगर (ret) अणु
		clk_disable_unprepare(clk);
		वापस ret;
	पूर्ण

	dev_info(&pdev->dev, "Init done\n");

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id xway_stp_match[] = अणु
	अणु .compatible = "lantiq,gpio-stp-xway" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, xway_stp_match);

अटल काष्ठा platक्रमm_driver xway_stp_driver = अणु
	.probe = xway_stp_probe,
	.driver = अणु
		.name = "gpio-stp-xway",
		.of_match_table = xway_stp_match,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init xway_stp_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&xway_stp_driver);
पूर्ण

subsys_initcall(xway_stp_init);
