<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) ST-Ericsson SA 2013
 *
 * Author: Patrice Chotard <patrice.chotard@st.com>
 *
 * Driver allows to use AxB5xx unused pins to be used as GPIO
 */
#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/slab.h>
#समावेश <linux/init.h>
#समावेश <linux/err.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/irq.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/bitops.h>
#समावेश <linux/mfd/abx500.h>
#समावेश <linux/mfd/abx500/ab8500.h>
#समावेश <linux/pinctrl/pinctrl.h>
#समावेश <linux/pinctrl/consumer.h>
#समावेश <linux/pinctrl/pinmux.h>
#समावेश <linux/pinctrl/pinconf.h>
#समावेश <linux/pinctrl/pinconf-generic.h>
#समावेश <linux/pinctrl/machine.h>

#समावेश "pinctrl-abx500.h"
#समावेश "../core.h"
#समावेश "../pinconf.h"
#समावेश "../pinctrl-utils.h"

/*
 * GPIO रेजिस्टरs offset
 * Bank: 0x10
 */
#घोषणा AB8500_GPIO_SEL1_REG	0x00
#घोषणा AB8500_GPIO_SEL2_REG	0x01
#घोषणा AB8500_GPIO_SEL3_REG	0x02
#घोषणा AB8500_GPIO_SEL4_REG	0x03
#घोषणा AB8500_GPIO_SEL5_REG	0x04
#घोषणा AB8500_GPIO_SEL6_REG	0x05

#घोषणा AB8500_GPIO_सूची1_REG	0x10
#घोषणा AB8500_GPIO_सूची2_REG	0x11
#घोषणा AB8500_GPIO_सूची3_REG	0x12
#घोषणा AB8500_GPIO_सूची4_REG	0x13
#घोषणा AB8500_GPIO_सूची5_REG	0x14
#घोषणा AB8500_GPIO_सूची6_REG	0x15

#घोषणा AB8500_GPIO_OUT1_REG	0x20
#घोषणा AB8500_GPIO_OUT2_REG	0x21
#घोषणा AB8500_GPIO_OUT3_REG	0x22
#घोषणा AB8500_GPIO_OUT4_REG	0x23
#घोषणा AB8500_GPIO_OUT5_REG	0x24
#घोषणा AB8500_GPIO_OUT6_REG	0x25

#घोषणा AB8500_GPIO_PUD1_REG	0x30
#घोषणा AB8500_GPIO_PUD2_REG	0x31
#घोषणा AB8500_GPIO_PUD3_REG	0x32
#घोषणा AB8500_GPIO_PUD4_REG	0x33
#घोषणा AB8500_GPIO_PUD5_REG	0x34
#घोषणा AB8500_GPIO_PUD6_REG	0x35

#घोषणा AB8500_GPIO_IN1_REG	0x40
#घोषणा AB8500_GPIO_IN2_REG	0x41
#घोषणा AB8500_GPIO_IN3_REG	0x42
#घोषणा AB8500_GPIO_IN4_REG	0x43
#घोषणा AB8500_GPIO_IN5_REG	0x44
#घोषणा AB8500_GPIO_IN6_REG	0x45
#घोषणा AB8500_GPIO_ALTFUN_REG	0x50

#घोषणा ABX500_GPIO_INPUT	0
#घोषणा ABX500_GPIO_OUTPUT	1

काष्ठा abx500_pinctrl अणु
	काष्ठा device *dev;
	काष्ठा pinctrl_dev *pctldev;
	काष्ठा abx500_pinctrl_soc_data *soc;
	काष्ठा gpio_chip chip;
	काष्ठा ab8500 *parent;
	काष्ठा abx500_gpio_irq_cluster *irq_cluster;
	पूर्णांक irq_cluster_size;
पूर्ण;

अटल पूर्णांक abx500_gpio_get_bit(काष्ठा gpio_chip *chip, u8 reg,
			       अचिन्हित offset, bool *bit)
अणु
	काष्ठा abx500_pinctrl *pct = gpiochip_get_data(chip);
	u8 pos = offset % 8;
	u8 val;
	पूर्णांक ret;

	reg += offset / 8;
	ret = abx500_get_रेजिस्टर_पूर्णांकerruptible(pct->dev,
						AB8500_MISC, reg, &val);
	अगर (ret < 0) अणु
		dev_err(pct->dev,
			"%s read reg =%x, offset=%x failed (%d)\n",
			__func__, reg, offset, ret);
		वापस ret;
	पूर्ण

	*bit = !!(val & BIT(pos));

	वापस 0;
पूर्ण

अटल पूर्णांक abx500_gpio_set_bits(काष्ठा gpio_chip *chip, u8 reg,
				अचिन्हित offset, पूर्णांक val)
अणु
	काष्ठा abx500_pinctrl *pct = gpiochip_get_data(chip);
	u8 pos = offset % 8;
	पूर्णांक ret;

	reg += offset / 8;
	ret = abx500_mask_and_set_रेजिस्टर_पूर्णांकerruptible(pct->dev,
				AB8500_MISC, reg, BIT(pos), val << pos);
	अगर (ret < 0)
		dev_err(pct->dev, "%s write reg, %x offset %x failed (%d)\n",
				__func__, reg, offset, ret);

	वापस ret;
पूर्ण

/**
 * abx500_gpio_get() - Get the particular GPIO value
 * @chip:	Gpio device
 * @offset:	GPIO number to पढ़ो
 */
अटल पूर्णांक abx500_gpio_get(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	काष्ठा abx500_pinctrl *pct = gpiochip_get_data(chip);
	bool bit;
	bool is_out;
	u8 gpio_offset = offset - 1;
	पूर्णांक ret;

	ret = abx500_gpio_get_bit(chip, AB8500_GPIO_सूची1_REG,
			gpio_offset, &is_out);
	अगर (ret < 0)
		जाओ out;

	अगर (is_out)
		ret = abx500_gpio_get_bit(chip, AB8500_GPIO_OUT1_REG,
				gpio_offset, &bit);
	अन्यथा
		ret = abx500_gpio_get_bit(chip, AB8500_GPIO_IN1_REG,
				gpio_offset, &bit);
out:
	अगर (ret < 0) अणु
		dev_err(pct->dev, "%s failed (%d)\n", __func__, ret);
		वापस ret;
	पूर्ण

	वापस bit;
पूर्ण

अटल व्योम abx500_gpio_set(काष्ठा gpio_chip *chip, अचिन्हित offset, पूर्णांक val)
अणु
	काष्ठा abx500_pinctrl *pct = gpiochip_get_data(chip);
	पूर्णांक ret;

	ret = abx500_gpio_set_bits(chip, AB8500_GPIO_OUT1_REG, offset, val);
	अगर (ret < 0)
		dev_err(pct->dev, "%s write failed (%d)\n", __func__, ret);
पूर्ण

अटल पूर्णांक abx500_gpio_direction_output(काष्ठा gpio_chip *chip,
					अचिन्हित offset,
					पूर्णांक val)
अणु
	काष्ठा abx500_pinctrl *pct = gpiochip_get_data(chip);
	पूर्णांक ret;

	/* set direction as output */
	ret = abx500_gpio_set_bits(chip,
				AB8500_GPIO_सूची1_REG,
				offset,
				ABX500_GPIO_OUTPUT);
	अगर (ret < 0)
		जाओ out;

	/* disable pull करोwn */
	ret = abx500_gpio_set_bits(chip,
				AB8500_GPIO_PUD1_REG,
				offset,
				ABX500_GPIO_PULL_NONE);

out:
	अगर (ret < 0) अणु
		dev_err(pct->dev, "%s failed (%d)\n", __func__, ret);
		वापस ret;
	पूर्ण

	/* set the output as 1 or 0 */
	वापस abx500_gpio_set_bits(chip, AB8500_GPIO_OUT1_REG, offset, val);
पूर्ण

अटल पूर्णांक abx500_gpio_direction_input(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	/* set the रेजिस्टर as input */
	वापस abx500_gpio_set_bits(chip,
				AB8500_GPIO_सूची1_REG,
				offset,
				ABX500_GPIO_INPUT);
पूर्ण

अटल पूर्णांक abx500_gpio_to_irq(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	काष्ठा abx500_pinctrl *pct = gpiochip_get_data(chip);
	/* The AB8500 GPIO numbers are off by one */
	पूर्णांक gpio = offset + 1;
	पूर्णांक hwirq;
	पूर्णांक i;

	क्रम (i = 0; i < pct->irq_cluster_size; i++) अणु
		काष्ठा abx500_gpio_irq_cluster *cluster =
			&pct->irq_cluster[i];

		अगर (gpio >= cluster->start && gpio <= cluster->end) अणु
			/*
			 * The ABx500 GPIO's associated IRQs are clustered together
			 * throughout the पूर्णांकerrupt numbers at irregular पूर्णांकervals.
			 * To solve this quandry, we have placed the पढ़ो-in values
			 * पूर्णांकo the cluster inक्रमmation table.
			 */
			hwirq = gpio - cluster->start + cluster->to_irq;
			वापस irq_create_mapping(pct->parent->करोमुख्य, hwirq);
		पूर्ण
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक abx500_set_mode(काष्ठा pinctrl_dev *pctldev, काष्ठा gpio_chip *chip,
			   अचिन्हित gpio, पूर्णांक alt_setting)
अणु
	काष्ठा abx500_pinctrl *pct = pinctrl_dev_get_drvdata(pctldev);
	काष्ठा alternate_functions af = pct->soc->alternate_functions[gpio];
	पूर्णांक ret;
	पूर्णांक val;
	अचिन्हित offset;

	स्थिर अक्षर *modes[] = अणु
		[ABX500_DEFAULT]	= "default",
		[ABX500_ALT_A]		= "altA",
		[ABX500_ALT_B]		= "altB",
		[ABX500_ALT_C]		= "altC",
	पूर्ण;

	/* sanity check */
	अगर (((alt_setting == ABX500_ALT_A) && (af.gpiosel_bit == UNUSED)) ||
	    ((alt_setting == ABX500_ALT_B) && (af.alt_bit1 == UNUSED)) ||
	    ((alt_setting == ABX500_ALT_C) && (af.alt_bit2 == UNUSED))) अणु
		dev_dbg(pct->dev, "pin %d doesn't support %s mode\n", gpio,
				modes[alt_setting]);
		वापस -EINVAL;
	पूर्ण

	/* on ABx5xx, there is no GPIO0, so adjust the offset */
	offset = gpio - 1;

	चयन (alt_setting) अणु
	हाल ABX500_DEFAULT:
		/*
		 * क्रम ABx5xx family, शेष mode is always selected by
		 * writing 0 to GPIOSELx रेजिस्टर, except क्रम pins which
		 * support at least ALT_B mode, शेष mode is selected
		 * by writing 1 to GPIOSELx रेजिस्टर
		 */
		val = 0;
		अगर (af.alt_bit1 != UNUSED)
			val++;

		ret = abx500_gpio_set_bits(chip, AB8500_GPIO_SEL1_REG,
					   offset, val);
		अवरोध;

	हाल ABX500_ALT_A:
		/*
		 * क्रम ABx5xx family, alt_a mode is always selected by
		 * writing 1 to GPIOSELx रेजिस्टर, except क्रम pins which
		 * support at least ALT_B mode, alt_a mode is selected
		 * by writing 0 to GPIOSELx रेजिस्टर and 0 in ALTFUNC
		 * रेजिस्टर
		 */
		अगर (af.alt_bit1 != UNUSED) अणु
			ret = abx500_gpio_set_bits(chip, AB8500_GPIO_SEL1_REG,
					offset, 0);
			अगर (ret < 0)
				जाओ out;

			ret = abx500_gpio_set_bits(chip,
					AB8500_GPIO_ALTFUN_REG,
					af.alt_bit1,
					!!(af.alta_val & BIT(0)));
			अगर (ret < 0)
				जाओ out;

			अगर (af.alt_bit2 != UNUSED)
				ret = abx500_gpio_set_bits(chip,
					AB8500_GPIO_ALTFUN_REG,
					af.alt_bit2,
					!!(af.alta_val & BIT(1)));
		पूर्ण अन्यथा
			ret = abx500_gpio_set_bits(chip, AB8500_GPIO_SEL1_REG,
					offset, 1);
		अवरोध;

	हाल ABX500_ALT_B:
		ret = abx500_gpio_set_bits(chip, AB8500_GPIO_SEL1_REG,
				offset, 0);
		अगर (ret < 0)
			जाओ out;

		ret = abx500_gpio_set_bits(chip, AB8500_GPIO_ALTFUN_REG,
				af.alt_bit1, !!(af.altb_val & BIT(0)));
		अगर (ret < 0)
			जाओ out;

		अगर (af.alt_bit2 != UNUSED)
			ret = abx500_gpio_set_bits(chip,
					AB8500_GPIO_ALTFUN_REG,
					af.alt_bit2,
					!!(af.altb_val & BIT(1)));
		अवरोध;

	हाल ABX500_ALT_C:
		ret = abx500_gpio_set_bits(chip, AB8500_GPIO_SEL1_REG,
				offset, 0);
		अगर (ret < 0)
			जाओ out;

		ret = abx500_gpio_set_bits(chip, AB8500_GPIO_ALTFUN_REG,
				af.alt_bit2, !!(af.altc_val & BIT(0)));
		अगर (ret < 0)
			जाओ out;

		ret = abx500_gpio_set_bits(chip, AB8500_GPIO_ALTFUN_REG,
				af.alt_bit2, !!(af.altc_val & BIT(1)));
		अवरोध;

	शेष:
		dev_dbg(pct->dev, "unknown alt_setting %d\n", alt_setting);

		वापस -EINVAL;
	पूर्ण
out:
	अगर (ret < 0)
		dev_err(pct->dev, "%s failed (%d)\n", __func__, ret);

	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_DEBUG_FS
अटल पूर्णांक abx500_get_mode(काष्ठा pinctrl_dev *pctldev, काष्ठा gpio_chip *chip,
			  अचिन्हित gpio)
अणु
	u8 mode;
	bool bit_mode;
	bool alt_bit1;
	bool alt_bit2;
	काष्ठा abx500_pinctrl *pct = pinctrl_dev_get_drvdata(pctldev);
	काष्ठा alternate_functions af = pct->soc->alternate_functions[gpio];
	/* on ABx5xx, there is no GPIO0, so adjust the offset */
	अचिन्हित offset = gpio - 1;
	पूर्णांक ret;

	/*
	 * अगर gpiosel_bit is set to unused,
	 * it means no GPIO or special हाल
	 */
	अगर (af.gpiosel_bit == UNUSED)
		वापस ABX500_DEFAULT;

	/* पढ़ो GpioSelx रेजिस्टर */
	ret = abx500_gpio_get_bit(chip, AB8500_GPIO_SEL1_REG + (offset / 8),
			af.gpiosel_bit, &bit_mode);
	अगर (ret < 0)
		जाओ out;

	mode = bit_mode;

	/* sanity check */
	अगर ((af.alt_bit1 < UNUSED) || (af.alt_bit1 > 7) ||
	    (af.alt_bit2 < UNUSED) || (af.alt_bit2 > 7)) अणु
		dev_err(pct->dev,
			"alt_bitX value not in correct range (-1 to 7)\n");
		वापस -EINVAL;
	पूर्ण

	/* अगर alt_bit2 is used, alt_bit1 must be used too */
	अगर ((af.alt_bit2 != UNUSED) && (af.alt_bit1 == UNUSED)) अणु
		dev_err(pct->dev,
			"if alt_bit2 is used, alt_bit1 can't be unused\n");
		वापस -EINVAL;
	पूर्ण

	/* check अगर pin use AlternateFunction रेजिस्टर */
	अगर ((af.alt_bit1 == UNUSED) && (af.alt_bit2 == UNUSED))
		वापस mode;
	/*
	 * अगर pin GPIOSEL bit is set and pin supports alternate function,
	 * it means DEFAULT mode
	 */
	अगर (mode)
		वापस ABX500_DEFAULT;

	/*
	 * pin use the AlternatFunction रेजिस्टर
	 * पढ़ो alt_bit1 value
	 */
	ret = abx500_gpio_get_bit(chip, AB8500_GPIO_ALTFUN_REG,
			    af.alt_bit1, &alt_bit1);
	अगर (ret < 0)
		जाओ out;

	अगर (af.alt_bit2 != UNUSED) अणु
		/* पढ़ो alt_bit2 value */
		ret = abx500_gpio_get_bit(chip, AB8500_GPIO_ALTFUN_REG,
				af.alt_bit2,
				&alt_bit2);
		अगर (ret < 0)
			जाओ out;
	पूर्ण अन्यथा
		alt_bit2 = 0;

	mode = (alt_bit2 << 1) + alt_bit1;
	अगर (mode == af.alta_val)
		वापस ABX500_ALT_A;
	अन्यथा अगर (mode == af.altb_val)
		वापस ABX500_ALT_B;
	अन्यथा
		वापस ABX500_ALT_C;

out:
	dev_err(pct->dev, "%s failed (%d)\n", __func__, ret);
	वापस ret;
पूर्ण

#समावेश <linux/seq_file.h>

अटल व्योम abx500_gpio_dbg_show_one(काष्ठा seq_file *s,
				     काष्ठा pinctrl_dev *pctldev,
				     काष्ठा gpio_chip *chip,
				     अचिन्हित offset, अचिन्हित gpio)
अणु
	काष्ठा abx500_pinctrl *pct = pinctrl_dev_get_drvdata(pctldev);
	स्थिर अक्षर *label = gpiochip_is_requested(chip, offset - 1);
	u8 gpio_offset = offset - 1;
	पूर्णांक mode = -1;
	bool is_out;
	bool pd;
	पूर्णांक ret;

	स्थिर अक्षर *modes[] = अणु
		[ABX500_DEFAULT]	= "default",
		[ABX500_ALT_A]		= "altA",
		[ABX500_ALT_B]		= "altB",
		[ABX500_ALT_C]		= "altC",
	पूर्ण;

	स्थिर अक्षर *pull_up_करोwn[] = अणु
		[ABX500_GPIO_PULL_DOWN]		= "pull down",
		[ABX500_GPIO_PULL_NONE]		= "pull none",
		[ABX500_GPIO_PULL_NONE + 1]	= "pull none",
		[ABX500_GPIO_PULL_UP]		= "pull up",
	पूर्ण;

	ret = abx500_gpio_get_bit(chip, AB8500_GPIO_सूची1_REG,
			gpio_offset, &is_out);
	अगर (ret < 0)
		जाओ out;

	seq_म_लिखो(s, " gpio-%-3d (%-20.20s) %-3s",
		   gpio, label ?: "(none)",
		   is_out ? "out" : "in ");

	अगर (!is_out) अणु
		ret = abx500_gpio_get_bit(chip, AB8500_GPIO_PUD1_REG,
				gpio_offset, &pd);
		अगर (ret < 0)
			जाओ out;

		seq_म_लिखो(s, " %-9s", pull_up_करोwn[pd]);
	पूर्ण अन्यथा
		seq_म_लिखो(s, " %-9s", chip->get(chip, offset) ? "hi" : "lo");

	mode = abx500_get_mode(pctldev, chip, offset);

	seq_म_लिखो(s, " %s", (mode < 0) ? "unknown" : modes[mode]);

out:
	अगर (ret < 0)
		dev_err(pct->dev, "%s failed (%d)\n", __func__, ret);
पूर्ण

अटल व्योम abx500_gpio_dbg_show(काष्ठा seq_file *s, काष्ठा gpio_chip *chip)
अणु
	अचिन्हित i;
	अचिन्हित gpio = chip->base;
	काष्ठा abx500_pinctrl *pct = gpiochip_get_data(chip);
	काष्ठा pinctrl_dev *pctldev = pct->pctldev;

	क्रम (i = 0; i < chip->ngpio; i++, gpio++) अणु
		/* On AB8500, there is no GPIO0, the first is the GPIO 1 */
		abx500_gpio_dbg_show_one(s, pctldev, chip, i + 1, gpio);
		seq_अ_दो(s, '\n');
	पूर्ण
पूर्ण

#अन्यथा
अटल अंतरभूत व्योम abx500_gpio_dbg_show_one(काष्ठा seq_file *s,
					    काष्ठा pinctrl_dev *pctldev,
					    काष्ठा gpio_chip *chip,
					    अचिन्हित offset, अचिन्हित gpio)
अणु
पूर्ण
#घोषणा abx500_gpio_dbg_show	शून्य
#पूर्ण_अगर

अटल स्थिर काष्ठा gpio_chip abx500gpio_chip = अणु
	.label			= "abx500-gpio",
	.owner			= THIS_MODULE,
	.request		= gpiochip_generic_request,
	.मुक्त			= gpiochip_generic_मुक्त,
	.direction_input	= abx500_gpio_direction_input,
	.get			= abx500_gpio_get,
	.direction_output	= abx500_gpio_direction_output,
	.set			= abx500_gpio_set,
	.to_irq			= abx500_gpio_to_irq,
	.dbg_show		= abx500_gpio_dbg_show,
पूर्ण;

अटल पूर्णांक abx500_pmx_get_funcs_cnt(काष्ठा pinctrl_dev *pctldev)
अणु
	काष्ठा abx500_pinctrl *pct = pinctrl_dev_get_drvdata(pctldev);

	वापस pct->soc->nfunctions;
पूर्ण

अटल स्थिर अक्षर *abx500_pmx_get_func_name(काष्ठा pinctrl_dev *pctldev,
					 अचिन्हित function)
अणु
	काष्ठा abx500_pinctrl *pct = pinctrl_dev_get_drvdata(pctldev);

	वापस pct->soc->functions[function].name;
पूर्ण

अटल पूर्णांक abx500_pmx_get_func_groups(काष्ठा pinctrl_dev *pctldev,
				      अचिन्हित function,
				      स्थिर अक्षर * स्थिर **groups,
				      अचिन्हित * स्थिर num_groups)
अणु
	काष्ठा abx500_pinctrl *pct = pinctrl_dev_get_drvdata(pctldev);

	*groups = pct->soc->functions[function].groups;
	*num_groups = pct->soc->functions[function].ngroups;

	वापस 0;
पूर्ण

अटल पूर्णांक abx500_pmx_set(काष्ठा pinctrl_dev *pctldev, अचिन्हित function,
			  अचिन्हित group)
अणु
	काष्ठा abx500_pinctrl *pct = pinctrl_dev_get_drvdata(pctldev);
	काष्ठा gpio_chip *chip = &pct->chip;
	स्थिर काष्ठा abx500_pingroup *g;
	पूर्णांक i;
	पूर्णांक ret = 0;

	g = &pct->soc->groups[group];
	अगर (g->altsetting < 0)
		वापस -EINVAL;

	dev_dbg(pct->dev, "enable group %s, %u pins\n", g->name, g->npins);

	क्रम (i = 0; i < g->npins; i++) अणु
		dev_dbg(pct->dev, "setting pin %d to altsetting %d\n",
			g->pins[i], g->altsetting);

		ret = abx500_set_mode(pctldev, chip, g->pins[i], g->altsetting);
	पूर्ण

	अगर (ret < 0)
		dev_err(pct->dev, "%s failed (%d)\n", __func__, ret);

	वापस ret;
पूर्ण

अटल पूर्णांक abx500_gpio_request_enable(काष्ठा pinctrl_dev *pctldev,
			       काष्ठा pinctrl_gpio_range *range,
			       अचिन्हित offset)
अणु
	काष्ठा abx500_pinctrl *pct = pinctrl_dev_get_drvdata(pctldev);
	स्थिर काष्ठा abx500_pinrange *p;
	पूर्णांक ret;
	पूर्णांक i;

	/*
	 * Dअगरferent ranges have dअगरferent ways to enable GPIO function on a
	 * pin, so refer back to our local range type, where we handily define
	 * what altfunc enables GPIO क्रम a certain pin.
	 */
	क्रम (i = 0; i < pct->soc->gpio_num_ranges; i++) अणु
		p = &pct->soc->gpio_ranges[i];
		अगर ((offset >= p->offset) &&
		    (offset < (p->offset + p->npins)))
		  अवरोध;
	पूर्ण

	अगर (i == pct->soc->gpio_num_ranges) अणु
		dev_err(pct->dev, "%s failed to locate range\n", __func__);
		वापस -ENODEV;
	पूर्ण

	dev_dbg(pct->dev, "enable GPIO by altfunc %d at gpio %d\n",
		p->altfunc, offset);

	ret = abx500_set_mode(pct->pctldev, &pct->chip,
			      offset, p->altfunc);
	अगर (ret < 0)
		dev_err(pct->dev, "%s setting altfunc failed\n", __func__);

	वापस ret;
पूर्ण

अटल व्योम abx500_gpio_disable_मुक्त(काष्ठा pinctrl_dev *pctldev,
				     काष्ठा pinctrl_gpio_range *range,
				     अचिन्हित offset)
अणु
पूर्ण

अटल स्थिर काष्ठा pinmux_ops abx500_pinmux_ops = अणु
	.get_functions_count = abx500_pmx_get_funcs_cnt,
	.get_function_name = abx500_pmx_get_func_name,
	.get_function_groups = abx500_pmx_get_func_groups,
	.set_mux = abx500_pmx_set,
	.gpio_request_enable = abx500_gpio_request_enable,
	.gpio_disable_मुक्त = abx500_gpio_disable_मुक्त,
पूर्ण;

अटल पूर्णांक abx500_get_groups_cnt(काष्ठा pinctrl_dev *pctldev)
अणु
	काष्ठा abx500_pinctrl *pct = pinctrl_dev_get_drvdata(pctldev);

	वापस pct->soc->ngroups;
पूर्ण

अटल स्थिर अक्षर *abx500_get_group_name(काष्ठा pinctrl_dev *pctldev,
					 अचिन्हित selector)
अणु
	काष्ठा abx500_pinctrl *pct = pinctrl_dev_get_drvdata(pctldev);

	वापस pct->soc->groups[selector].name;
पूर्ण

अटल पूर्णांक abx500_get_group_pins(काष्ठा pinctrl_dev *pctldev,
				 अचिन्हित selector,
				 स्थिर अचिन्हित **pins,
				 अचिन्हित *num_pins)
अणु
	काष्ठा abx500_pinctrl *pct = pinctrl_dev_get_drvdata(pctldev);

	*pins = pct->soc->groups[selector].pins;
	*num_pins = pct->soc->groups[selector].npins;

	वापस 0;
पूर्ण

अटल व्योम abx500_pin_dbg_show(काष्ठा pinctrl_dev *pctldev,
				काष्ठा seq_file *s, अचिन्हित offset)
अणु
	काष्ठा abx500_pinctrl *pct = pinctrl_dev_get_drvdata(pctldev);
	काष्ठा gpio_chip *chip = &pct->chip;

	abx500_gpio_dbg_show_one(s, pctldev, chip, offset,
				 chip->base + offset - 1);
पूर्ण

अटल पूर्णांक abx500_dt_add_map_mux(काष्ठा pinctrl_map **map,
		अचिन्हित *reserved_maps,
		अचिन्हित *num_maps, स्थिर अक्षर *group,
		स्थिर अक्षर *function)
अणु
	अगर (*num_maps == *reserved_maps)
		वापस -ENOSPC;

	(*map)[*num_maps].type = PIN_MAP_TYPE_MUX_GROUP;
	(*map)[*num_maps].data.mux.group = group;
	(*map)[*num_maps].data.mux.function = function;
	(*num_maps)++;

	वापस 0;
पूर्ण

अटल पूर्णांक abx500_dt_add_map_configs(काष्ठा pinctrl_map **map,
		अचिन्हित *reserved_maps,
		अचिन्हित *num_maps, स्थिर अक्षर *group,
		अचिन्हित दीर्घ *configs, अचिन्हित num_configs)
अणु
	अचिन्हित दीर्घ *dup_configs;

	अगर (*num_maps == *reserved_maps)
		वापस -ENOSPC;

	dup_configs = kmemdup(configs, num_configs * माप(*dup_configs),
			      GFP_KERNEL);
	अगर (!dup_configs)
		वापस -ENOMEM;

	(*map)[*num_maps].type = PIN_MAP_TYPE_CONFIGS_PIN;

	(*map)[*num_maps].data.configs.group_or_pin = group;
	(*map)[*num_maps].data.configs.configs = dup_configs;
	(*map)[*num_maps].data.configs.num_configs = num_configs;
	(*num_maps)++;

	वापस 0;
पूर्ण

अटल स्थिर अक्षर *abx500_find_pin_name(काष्ठा pinctrl_dev *pctldev,
					स्थिर अक्षर *pin_name)
अणु
	पूर्णांक i, pin_number;
	काष्ठा abx500_pinctrl *npct = pinctrl_dev_get_drvdata(pctldev);

	अगर (माला_पूछो((अक्षर *)pin_name, "GPIO%d", &pin_number) == 1)
		क्रम (i = 0; i < npct->soc->npins; i++)
			अगर (npct->soc->pins[i].number == pin_number)
				वापस npct->soc->pins[i].name;
	वापस शून्य;
पूर्ण

अटल पूर्णांक abx500_dt_subnode_to_map(काष्ठा pinctrl_dev *pctldev,
		काष्ठा device_node *np,
		काष्ठा pinctrl_map **map,
		अचिन्हित *reserved_maps,
		अचिन्हित *num_maps)
अणु
	पूर्णांक ret;
	स्थिर अक्षर *function = शून्य;
	अचिन्हित दीर्घ *configs;
	अचिन्हित पूर्णांक nconfigs = 0;
	काष्ठा property *prop;

	ret = of_property_पढ़ो_string(np, "function", &function);
	अगर (ret >= 0) अणु
		स्थिर अक्षर *group;

		ret = of_property_count_strings(np, "groups");
		अगर (ret < 0)
			जाओ निकास;

		ret = pinctrl_utils_reserve_map(pctldev, map, reserved_maps,
						num_maps, ret);
		अगर (ret < 0)
			जाओ निकास;

		of_property_क्रम_each_string(np, "groups", prop, group) अणु
			ret = abx500_dt_add_map_mux(map, reserved_maps,
					num_maps, group, function);
			अगर (ret < 0)
				जाओ निकास;
		पूर्ण
	पूर्ण

	ret = pinconf_generic_parse_dt_config(np, pctldev, &configs, &nconfigs);
	अगर (nconfigs) अणु
		स्थिर अक्षर *gpio_name;
		स्थिर अक्षर *pin;

		ret = of_property_count_strings(np, "pins");
		अगर (ret < 0)
			जाओ निकास;

		ret = pinctrl_utils_reserve_map(pctldev, map,
						reserved_maps,
						num_maps, ret);
		अगर (ret < 0)
			जाओ निकास;

		of_property_क्रम_each_string(np, "pins", prop, pin) अणु
			gpio_name = abx500_find_pin_name(pctldev, pin);

			ret = abx500_dt_add_map_configs(map, reserved_maps,
					num_maps, gpio_name, configs, 1);
			अगर (ret < 0)
				जाओ निकास;
		पूर्ण
	पूर्ण

निकास:
	वापस ret;
पूर्ण

अटल पूर्णांक abx500_dt_node_to_map(काष्ठा pinctrl_dev *pctldev,
				 काष्ठा device_node *np_config,
				 काष्ठा pinctrl_map **map, अचिन्हित *num_maps)
अणु
	अचिन्हित reserved_maps;
	काष्ठा device_node *np;
	पूर्णांक ret;

	reserved_maps = 0;
	*map = शून्य;
	*num_maps = 0;

	क्रम_each_child_of_node(np_config, np) अणु
		ret = abx500_dt_subnode_to_map(pctldev, np, map,
				&reserved_maps, num_maps);
		अगर (ret < 0) अणु
			pinctrl_utils_मुक्त_map(pctldev, *map, *num_maps);
			of_node_put(np);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pinctrl_ops abx500_pinctrl_ops = अणु
	.get_groups_count = abx500_get_groups_cnt,
	.get_group_name = abx500_get_group_name,
	.get_group_pins = abx500_get_group_pins,
	.pin_dbg_show = abx500_pin_dbg_show,
	.dt_node_to_map = abx500_dt_node_to_map,
	.dt_मुक्त_map = pinctrl_utils_मुक्त_map,
पूर्ण;

अटल पूर्णांक abx500_pin_config_get(काष्ठा pinctrl_dev *pctldev,
			  अचिन्हित pin,
			  अचिन्हित दीर्घ *config)
अणु
	वापस -ENOSYS;
पूर्ण

अटल पूर्णांक abx500_pin_config_set(काष्ठा pinctrl_dev *pctldev,
			  अचिन्हित pin,
			  अचिन्हित दीर्घ *configs,
			  अचिन्हित num_configs)
अणु
	काष्ठा abx500_pinctrl *pct = pinctrl_dev_get_drvdata(pctldev);
	काष्ठा gpio_chip *chip = &pct->chip;
	अचिन्हित offset;
	पूर्णांक ret = -EINVAL;
	पूर्णांक i;
	क्रमागत pin_config_param param;
	क्रमागत pin_config_param argument;

	क्रम (i = 0; i < num_configs; i++) अणु
		param = pinconf_to_config_param(configs[i]);
		argument = pinconf_to_config_argument(configs[i]);

		dev_dbg(chip->parent, "pin %d [%#lx]: %s %s\n",
			pin, configs[i],
			(param == PIN_CONFIG_OUTPUT) ? "output " : "input",
			(param == PIN_CONFIG_OUTPUT) ?
			(argument ? "high" : "low") :
			(argument ? "pull up" : "pull down"));

		/* on ABx500, there is no GPIO0, so adjust the offset */
		offset = pin - 1;

		चयन (param) अणु
		हाल PIN_CONFIG_BIAS_DISABLE:
			ret = abx500_gpio_direction_input(chip, offset);
			अगर (ret < 0)
				जाओ out;

			/* Chip only supports pull करोwn */
			ret = abx500_gpio_set_bits(chip,
				AB8500_GPIO_PUD1_REG, offset,
				ABX500_GPIO_PULL_NONE);
			अवरोध;

		हाल PIN_CONFIG_BIAS_PULL_DOWN:
			ret = abx500_gpio_direction_input(chip, offset);
			अगर (ret < 0)
				जाओ out;
			/*
			 * अगर argument = 1 set the pull करोwn
			 * अन्यथा clear the pull करोwn
			 * Chip only supports pull करोwn
			 */
			ret = abx500_gpio_set_bits(chip,
			AB8500_GPIO_PUD1_REG,
				offset,
				argument ? ABX500_GPIO_PULL_DOWN :
				ABX500_GPIO_PULL_NONE);
			अवरोध;

		हाल PIN_CONFIG_BIAS_PULL_UP:
			ret = abx500_gpio_direction_input(chip, offset);
			अगर (ret < 0)
				जाओ out;
			/*
			 * अगर argument = 1 set the pull up
			 * अन्यथा clear the pull up
			 */
			ret = abx500_gpio_direction_input(chip, offset);
			अवरोध;

		हाल PIN_CONFIG_OUTPUT:
			ret = abx500_gpio_direction_output(chip, offset,
				argument);
			अवरोध;

		शेष:
			dev_err(chip->parent,
				"illegal configuration requested\n");
		पूर्ण
	पूर्ण /* क्रम each config */
out:
	अगर (ret < 0)
		dev_err(pct->dev, "%s failed (%d)\n", __func__, ret);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा pinconf_ops abx500_pinconf_ops = अणु
	.pin_config_get = abx500_pin_config_get,
	.pin_config_set = abx500_pin_config_set,
	.is_generic = true,
पूर्ण;

अटल काष्ठा pinctrl_desc abx500_pinctrl_desc = अणु
	.name = "pinctrl-abx500",
	.pctlops = &abx500_pinctrl_ops,
	.pmxops = &abx500_pinmux_ops,
	.confops = &abx500_pinconf_ops,
	.owner = THIS_MODULE,
पूर्ण;

अटल पूर्णांक abx500_get_gpio_num(काष्ठा abx500_pinctrl_soc_data *soc)
अणु
	अचिन्हित पूर्णांक lowest = 0;
	अचिन्हित पूर्णांक highest = 0;
	अचिन्हित पूर्णांक npins = 0;
	पूर्णांक i;

	/*
	 * Compute number of GPIOs from the last SoC gpio range descriptors
	 * These ranges may include "holes" but the GPIO number space shall
	 * still be homogeneous, so we need to detect and account क्रम any
	 * such holes so that these are included in the number of GPIO pins.
	 */
	क्रम (i = 0; i < soc->gpio_num_ranges; i++) अणु
		अचिन्हित gstart;
		अचिन्हित gend;
		स्थिर काष्ठा abx500_pinrange *p;

		p = &soc->gpio_ranges[i];
		gstart = p->offset;
		gend = p->offset + p->npins - 1;

		अगर (i == 0) अणु
			/* First iteration, set start values */
			lowest = gstart;
			highest = gend;
		पूर्ण अन्यथा अणु
			अगर (gstart < lowest)
				lowest = gstart;
			अगर (gend > highest)
				highest = gend;
		पूर्ण
	पूर्ण
	/* this gives the असलolute number of pins */
	npins = highest - lowest + 1;
	वापस npins;
पूर्ण

अटल स्थिर काष्ठा of_device_id abx500_gpio_match[] = अणु
	अणु .compatible = "stericsson,ab8500-gpio", .data = (व्योम *)PINCTRL_AB8500, पूर्ण,
	अणु .compatible = "stericsson,ab8505-gpio", .data = (व्योम *)PINCTRL_AB8505, पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल पूर्णांक abx500_gpio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	स्थिर काष्ठा of_device_id *match;
	काष्ठा abx500_pinctrl *pct;
	अचिन्हित पूर्णांक id = -1;
	पूर्णांक ret;
	पूर्णांक i;

	अगर (!np) अणु
		dev_err(&pdev->dev, "gpio dt node missing\n");
		वापस -ENODEV;
	पूर्ण

	pct = devm_kzalloc(&pdev->dev, माप(*pct), GFP_KERNEL);
	अगर (!pct)
		वापस -ENOMEM;

	pct->dev = &pdev->dev;
	pct->parent = dev_get_drvdata(pdev->dev.parent);
	pct->chip = abx500gpio_chip;
	pct->chip.parent = &pdev->dev;
	pct->chip.base = -1; /* Dynamic allocation */

	match = of_match_device(abx500_gpio_match, &pdev->dev);
	अगर (!match) अणु
		dev_err(&pdev->dev, "gpio dt not matching\n");
		वापस -ENODEV;
	पूर्ण
	id = (अचिन्हित दीर्घ)match->data;

	/* Poke in other ASIC variants here */
	चयन (id) अणु
	हाल PINCTRL_AB8500:
		abx500_pinctrl_ab8500_init(&pct->soc);
		अवरोध;
	हाल PINCTRL_AB8505:
		abx500_pinctrl_ab8505_init(&pct->soc);
		अवरोध;
	शेष:
		dev_err(&pdev->dev, "Unsupported pinctrl sub driver (%d)\n", id);
		वापस -EINVAL;
	पूर्ण

	अगर (!pct->soc) अणु
		dev_err(&pdev->dev, "Invalid SOC data\n");
		वापस -EINVAL;
	पूर्ण

	pct->chip.ngpio = abx500_get_gpio_num(pct->soc);
	pct->irq_cluster = pct->soc->gpio_irq_cluster;
	pct->irq_cluster_size = pct->soc->ngpio_irq_cluster;

	ret = gpiochip_add_data(&pct->chip, pct);
	अगर (ret) अणु
		dev_err(&pdev->dev, "unable to add gpiochip: %d\n", ret);
		वापस ret;
	पूर्ण
	dev_info(&pdev->dev, "added gpiochip\n");

	abx500_pinctrl_desc.pins = pct->soc->pins;
	abx500_pinctrl_desc.npins = pct->soc->npins;
	pct->pctldev = devm_pinctrl_रेजिस्टर(&pdev->dev, &abx500_pinctrl_desc,
					     pct);
	अगर (IS_ERR(pct->pctldev)) अणु
		dev_err(&pdev->dev,
			"could not register abx500 pinctrl driver\n");
		ret = PTR_ERR(pct->pctldev);
		जाओ out_rem_chip;
	पूर्ण
	dev_info(&pdev->dev, "registered pin controller\n");

	/* We will handle a range of GPIO pins */
	क्रम (i = 0; i < pct->soc->gpio_num_ranges; i++) अणु
		स्थिर काष्ठा abx500_pinrange *p = &pct->soc->gpio_ranges[i];

		ret = gpiochip_add_pin_range(&pct->chip,
					dev_name(&pdev->dev),
					p->offset - 1, p->offset, p->npins);
		अगर (ret < 0)
			जाओ out_rem_chip;
	पूर्ण

	platक्रमm_set_drvdata(pdev, pct);
	dev_info(&pdev->dev, "initialized abx500 pinctrl driver\n");

	वापस 0;

out_rem_chip:
	gpiochip_हटाओ(&pct->chip);
	वापस ret;
पूर्ण

/**
 * abx500_gpio_हटाओ() - हटाओ Ab8500-gpio driver
 * @pdev:	Platक्रमm device रेजिस्टरed
 */
अटल पूर्णांक abx500_gpio_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा abx500_pinctrl *pct = platक्रमm_get_drvdata(pdev);

	gpiochip_हटाओ(&pct->chip);
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver abx500_gpio_driver = अणु
	.driver = अणु
		.name = "abx500-gpio",
		.of_match_table = abx500_gpio_match,
	पूर्ण,
	.probe = abx500_gpio_probe,
	.हटाओ = abx500_gpio_हटाओ,
पूर्ण;

अटल पूर्णांक __init abx500_gpio_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&abx500_gpio_driver);
पूर्ण
core_initcall(abx500_gpio_init);
