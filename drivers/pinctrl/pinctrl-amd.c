<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * GPIO driver क्रम AMD
 *
 * Copyright (c) 2014,2015 AMD Corporation.
 * Authors: Ken Xue <Ken.Xue@amd.com>
 *      Wu, Jeff <Jeff.Wu@amd.com>
 *
 * Contact Inक्रमmation: Nehal Shah <Nehal-bakulchandra.Shah@amd.com>
 *			Shyam Sundar S K <Shyam-sundar.S-k@amd.com>
 */

#समावेश <linux/err.h>
#समावेश <linux/bug.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/compiler.h>
#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/log2.h>
#समावेश <linux/पन.स>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/slab.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/mutex.h>
#समावेश <linux/acpi.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/list.h>
#समावेश <linux/bitops.h>
#समावेश <linux/pinctrl/pinconf.h>
#समावेश <linux/pinctrl/pinconf-generic.h>

#समावेश "core.h"
#समावेश "pinctrl-utils.h"
#समावेश "pinctrl-amd.h"

अटल पूर्णांक amd_gpio_get_direction(काष्ठा gpio_chip *gc, अचिन्हित offset)
अणु
	अचिन्हित दीर्घ flags;
	u32 pin_reg;
	काष्ठा amd_gpio *gpio_dev = gpiochip_get_data(gc);

	raw_spin_lock_irqsave(&gpio_dev->lock, flags);
	pin_reg = पढ़ोl(gpio_dev->base + offset * 4);
	raw_spin_unlock_irqrestore(&gpio_dev->lock, flags);

	अगर (pin_reg & BIT(OUTPUT_ENABLE_OFF))
		वापस GPIO_LINE_सूचीECTION_OUT;

	वापस GPIO_LINE_सूचीECTION_IN;
पूर्ण

अटल पूर्णांक amd_gpio_direction_input(काष्ठा gpio_chip *gc, अचिन्हित offset)
अणु
	अचिन्हित दीर्घ flags;
	u32 pin_reg;
	काष्ठा amd_gpio *gpio_dev = gpiochip_get_data(gc);

	raw_spin_lock_irqsave(&gpio_dev->lock, flags);
	pin_reg = पढ़ोl(gpio_dev->base + offset * 4);
	pin_reg &= ~BIT(OUTPUT_ENABLE_OFF);
	ग_लिखोl(pin_reg, gpio_dev->base + offset * 4);
	raw_spin_unlock_irqrestore(&gpio_dev->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक amd_gpio_direction_output(काष्ठा gpio_chip *gc, अचिन्हित offset,
		पूर्णांक value)
अणु
	u32 pin_reg;
	अचिन्हित दीर्घ flags;
	काष्ठा amd_gpio *gpio_dev = gpiochip_get_data(gc);

	raw_spin_lock_irqsave(&gpio_dev->lock, flags);
	pin_reg = पढ़ोl(gpio_dev->base + offset * 4);
	pin_reg |= BIT(OUTPUT_ENABLE_OFF);
	अगर (value)
		pin_reg |= BIT(OUTPUT_VALUE_OFF);
	अन्यथा
		pin_reg &= ~BIT(OUTPUT_VALUE_OFF);
	ग_लिखोl(pin_reg, gpio_dev->base + offset * 4);
	raw_spin_unlock_irqrestore(&gpio_dev->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक amd_gpio_get_value(काष्ठा gpio_chip *gc, अचिन्हित offset)
अणु
	u32 pin_reg;
	अचिन्हित दीर्घ flags;
	काष्ठा amd_gpio *gpio_dev = gpiochip_get_data(gc);

	raw_spin_lock_irqsave(&gpio_dev->lock, flags);
	pin_reg = पढ़ोl(gpio_dev->base + offset * 4);
	raw_spin_unlock_irqrestore(&gpio_dev->lock, flags);

	वापस !!(pin_reg & BIT(PIN_STS_OFF));
पूर्ण

अटल व्योम amd_gpio_set_value(काष्ठा gpio_chip *gc, अचिन्हित offset, पूर्णांक value)
अणु
	u32 pin_reg;
	अचिन्हित दीर्घ flags;
	काष्ठा amd_gpio *gpio_dev = gpiochip_get_data(gc);

	raw_spin_lock_irqsave(&gpio_dev->lock, flags);
	pin_reg = पढ़ोl(gpio_dev->base + offset * 4);
	अगर (value)
		pin_reg |= BIT(OUTPUT_VALUE_OFF);
	अन्यथा
		pin_reg &= ~BIT(OUTPUT_VALUE_OFF);
	ग_लिखोl(pin_reg, gpio_dev->base + offset * 4);
	raw_spin_unlock_irqrestore(&gpio_dev->lock, flags);
पूर्ण

अटल पूर्णांक amd_gpio_set_debounce(काष्ठा gpio_chip *gc, अचिन्हित offset,
		अचिन्हित debounce)
अणु
	u32 समय;
	u32 pin_reg;
	पूर्णांक ret = 0;
	अचिन्हित दीर्घ flags;
	काष्ठा amd_gpio *gpio_dev = gpiochip_get_data(gc);

	raw_spin_lock_irqsave(&gpio_dev->lock, flags);
	pin_reg = पढ़ोl(gpio_dev->base + offset * 4);

	अगर (debounce) अणु
		pin_reg |= DB_TYPE_REMOVE_GLITCH << DB_CNTRL_OFF;
		pin_reg &= ~DB_TMR_OUT_MASK;
		/*
		Debounce	Debounce	Timer	Max
		TmrLarge	TmrOutUnit	Unit	Debounce
							Time
		0	0	61 usec (2 RtcClk)	976 usec
		0	1	244 usec (8 RtcClk)	3.9 msec
		1	0	15.6 msec (512 RtcClk)	250 msec
		1	1	62.5 msec (2048 RtcClk)	1 sec
		*/

		अगर (debounce < 61) अणु
			pin_reg |= 1;
			pin_reg &= ~BIT(DB_TMR_OUT_UNIT_OFF);
			pin_reg &= ~BIT(DB_TMR_LARGE_OFF);
		पूर्ण अन्यथा अगर (debounce < 976) अणु
			समय = debounce / 61;
			pin_reg |= समय & DB_TMR_OUT_MASK;
			pin_reg &= ~BIT(DB_TMR_OUT_UNIT_OFF);
			pin_reg &= ~BIT(DB_TMR_LARGE_OFF);
		पूर्ण अन्यथा अगर (debounce < 3900) अणु
			समय = debounce / 244;
			pin_reg |= समय & DB_TMR_OUT_MASK;
			pin_reg |= BIT(DB_TMR_OUT_UNIT_OFF);
			pin_reg &= ~BIT(DB_TMR_LARGE_OFF);
		पूर्ण अन्यथा अगर (debounce < 250000) अणु
			समय = debounce / 15625;
			pin_reg |= समय & DB_TMR_OUT_MASK;
			pin_reg &= ~BIT(DB_TMR_OUT_UNIT_OFF);
			pin_reg |= BIT(DB_TMR_LARGE_OFF);
		पूर्ण अन्यथा अगर (debounce < 1000000) अणु
			समय = debounce / 62500;
			pin_reg |= समय & DB_TMR_OUT_MASK;
			pin_reg |= BIT(DB_TMR_OUT_UNIT_OFF);
			pin_reg |= BIT(DB_TMR_LARGE_OFF);
		पूर्ण अन्यथा अणु
			pin_reg &= ~(DB_CNTRl_MASK << DB_CNTRL_OFF);
			ret = -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अणु
		pin_reg &= ~BIT(DB_TMR_OUT_UNIT_OFF);
		pin_reg &= ~BIT(DB_TMR_LARGE_OFF);
		pin_reg &= ~DB_TMR_OUT_MASK;
		pin_reg &= ~(DB_CNTRl_MASK << DB_CNTRL_OFF);
	पूर्ण
	ग_लिखोl(pin_reg, gpio_dev->base + offset * 4);
	raw_spin_unlock_irqrestore(&gpio_dev->lock, flags);

	वापस ret;
पूर्ण

अटल पूर्णांक amd_gpio_set_config(काष्ठा gpio_chip *gc, अचिन्हित offset,
			       अचिन्हित दीर्घ config)
अणु
	u32 debounce;

	अगर (pinconf_to_config_param(config) != PIN_CONFIG_INPUT_DEBOUNCE)
		वापस -ENOTSUPP;

	debounce = pinconf_to_config_argument(config);
	वापस amd_gpio_set_debounce(gc, offset, debounce);
पूर्ण

#अगर_घोषित CONFIG_DEBUG_FS
अटल व्योम amd_gpio_dbg_show(काष्ठा seq_file *s, काष्ठा gpio_chip *gc)
अणु
	u32 pin_reg;
	u32 db_cntrl;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक bank, i, pin_num;
	काष्ठा amd_gpio *gpio_dev = gpiochip_get_data(gc);

	bool पंचांगr_out_unit;
	अचिन्हित पूर्णांक समय;
	अचिन्हित पूर्णांक unit;
	bool पंचांगr_large;

	अक्षर *level_trig;
	अक्षर *active_level;
	अक्षर *पूर्णांकerrupt_enable;
	अक्षर *पूर्णांकerrupt_mask;
	अक्षर *wake_cntrl0;
	अक्षर *wake_cntrl1;
	अक्षर *wake_cntrl2;
	अक्षर *pin_sts;
	अक्षर *pull_up_sel;
	अक्षर *pull_up_enable;
	अक्षर *pull_करोwn_enable;
	अक्षर *output_value;
	अक्षर *output_enable;
	अक्षर debounce_value[40];
	अक्षर *debounce_enable;

	क्रम (bank = 0; bank < gpio_dev->hwbank_num; bank++) अणु
		seq_म_लिखो(s, "GPIO bank%d\t", bank);

		चयन (bank) अणु
		हाल 0:
			i = 0;
			pin_num = AMD_GPIO_PINS_BANK0;
			अवरोध;
		हाल 1:
			i = 64;
			pin_num = AMD_GPIO_PINS_BANK1 + i;
			अवरोध;
		हाल 2:
			i = 128;
			pin_num = AMD_GPIO_PINS_BANK2 + i;
			अवरोध;
		हाल 3:
			i = 192;
			pin_num = AMD_GPIO_PINS_BANK3 + i;
			अवरोध;
		शेष:
			/* Illegal bank number, ignore */
			जारी;
		पूर्ण
		क्रम (; i < pin_num; i++) अणु
			seq_म_लिखो(s, "pin%d\t", i);
			raw_spin_lock_irqsave(&gpio_dev->lock, flags);
			pin_reg = पढ़ोl(gpio_dev->base + i * 4);
			raw_spin_unlock_irqrestore(&gpio_dev->lock, flags);

			अगर (pin_reg & BIT(INTERRUPT_ENABLE_OFF)) अणु
				u8 level = (pin_reg >> ACTIVE_LEVEL_OFF) &
						ACTIVE_LEVEL_MASK;
				पूर्णांकerrupt_enable = "interrupt is enabled|";

				अगर (level == ACTIVE_LEVEL_HIGH)
					active_level = "Active high|";
				अन्यथा अगर (level == ACTIVE_LEVEL_LOW)
					active_level = "Active low|";
				अन्यथा अगर (!(pin_reg & BIT(LEVEL_TRIG_OFF)) &&
					 level == ACTIVE_LEVEL_BOTH)
					active_level = "Active on both|";
				अन्यथा
					active_level = "Unknown Active level|";

				अगर (pin_reg & BIT(LEVEL_TRIG_OFF))
					level_trig = "Level trigger|";
				अन्यथा
					level_trig = "Edge trigger|";

			पूर्ण अन्यथा अणु
				पूर्णांकerrupt_enable =
					"interrupt is disabled|";
				active_level = " ";
				level_trig = " ";
			पूर्ण

			अगर (pin_reg & BIT(INTERRUPT_MASK_OFF))
				पूर्णांकerrupt_mask =
					"interrupt is unmasked|";
			अन्यथा
				पूर्णांकerrupt_mask =
					"interrupt is masked|";

			अगर (pin_reg & BIT(WAKE_CNTRL_OFF_S0I3))
				wake_cntrl0 = "enable wakeup in S0i3 state|";
			अन्यथा
				wake_cntrl0 = "disable wakeup in S0i3 state|";

			अगर (pin_reg & BIT(WAKE_CNTRL_OFF_S3))
				wake_cntrl1 = "enable wakeup in S3 state|";
			अन्यथा
				wake_cntrl1 = "disable wakeup in S3 state|";

			अगर (pin_reg & BIT(WAKE_CNTRL_OFF_S4))
				wake_cntrl2 = "enable wakeup in S4/S5 state|";
			अन्यथा
				wake_cntrl2 = "disable wakeup in S4/S5 state|";

			अगर (pin_reg & BIT(PULL_UP_ENABLE_OFF)) अणु
				pull_up_enable = "pull-up is enabled|";
				अगर (pin_reg & BIT(PULL_UP_SEL_OFF))
					pull_up_sel = "8k pull-up|";
				अन्यथा
					pull_up_sel = "4k pull-up|";
			पूर्ण अन्यथा अणु
				pull_up_enable = "pull-up is disabled|";
				pull_up_sel = " ";
			पूर्ण

			अगर (pin_reg & BIT(PULL_DOWN_ENABLE_OFF))
				pull_करोwn_enable = "pull-down is enabled|";
			अन्यथा
				pull_करोwn_enable = "Pull-down is disabled|";

			अगर (pin_reg & BIT(OUTPUT_ENABLE_OFF)) अणु
				pin_sts = " ";
				output_enable = "output is enabled|";
				अगर (pin_reg & BIT(OUTPUT_VALUE_OFF))
					output_value = "output is high|";
				अन्यथा
					output_value = "output is low|";
			पूर्ण अन्यथा अणु
				output_enable = "output is disabled|";
				output_value = " ";

				अगर (pin_reg & BIT(PIN_STS_OFF))
					pin_sts = "input is high|";
				अन्यथा
					pin_sts = "input is low|";
			पूर्ण

			db_cntrl = (DB_CNTRl_MASK << DB_CNTRL_OFF) & pin_reg;
			अगर (db_cntrl) अणु
				पंचांगr_out_unit = pin_reg & BIT(DB_TMR_OUT_UNIT_OFF);
				पंचांगr_large = pin_reg & BIT(DB_TMR_LARGE_OFF);
				समय = pin_reg & DB_TMR_OUT_MASK;
				अगर (पंचांगr_large) अणु
					अगर (पंचांगr_out_unit)
						unit = 62500;
					अन्यथा
						unit = 15625;
				पूर्ण अन्यथा अणु
					अगर (पंचांगr_out_unit)
						unit = 244;
					अन्यथा
						unit = 61;
				पूर्ण
				अगर ((DB_TYPE_REMOVE_GLITCH << DB_CNTRL_OFF) == db_cntrl)
					debounce_enable = "debouncing filter (high and low) enabled|";
				अन्यथा अगर ((DB_TYPE_PRESERVE_LOW_GLITCH << DB_CNTRL_OFF) == db_cntrl)
					debounce_enable = "debouncing filter (low) enabled|";
				अन्यथा
					debounce_enable = "debouncing filter (high) enabled|";

				snम_लिखो(debounce_value, माप(debounce_value),
					 "debouncing timeout is %u (us)|", समय * unit);
			पूर्ण अन्यथा अणु
				debounce_enable = "debouncing filter disabled|";
				snम_लिखो(debounce_value, माप(debounce_value), " ");
			पूर्ण

			seq_म_लिखो(s, "%s %s %s %s %s %s\n"
				" %s %s %s %s %s %s %s %s %s 0x%x\n",
				level_trig, active_level, पूर्णांकerrupt_enable,
				पूर्णांकerrupt_mask, wake_cntrl0, wake_cntrl1,
				wake_cntrl2, pin_sts, pull_up_sel,
				pull_up_enable, pull_करोwn_enable,
				output_value, output_enable,
				debounce_enable, debounce_value, pin_reg);
		पूर्ण
	पूर्ण
पूर्ण
#अन्यथा
#घोषणा amd_gpio_dbg_show शून्य
#पूर्ण_अगर

अटल व्योम amd_gpio_irq_enable(काष्ठा irq_data *d)
अणु
	u32 pin_reg;
	अचिन्हित दीर्घ flags;
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(d);
	काष्ठा amd_gpio *gpio_dev = gpiochip_get_data(gc);

	raw_spin_lock_irqsave(&gpio_dev->lock, flags);
	pin_reg = पढ़ोl(gpio_dev->base + (d->hwirq)*4);
	pin_reg |= BIT(INTERRUPT_ENABLE_OFF);
	pin_reg |= BIT(INTERRUPT_MASK_OFF);
	ग_लिखोl(pin_reg, gpio_dev->base + (d->hwirq)*4);
	raw_spin_unlock_irqrestore(&gpio_dev->lock, flags);
पूर्ण

अटल व्योम amd_gpio_irq_disable(काष्ठा irq_data *d)
अणु
	u32 pin_reg;
	अचिन्हित दीर्घ flags;
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(d);
	काष्ठा amd_gpio *gpio_dev = gpiochip_get_data(gc);

	raw_spin_lock_irqsave(&gpio_dev->lock, flags);
	pin_reg = पढ़ोl(gpio_dev->base + (d->hwirq)*4);
	pin_reg &= ~BIT(INTERRUPT_ENABLE_OFF);
	pin_reg &= ~BIT(INTERRUPT_MASK_OFF);
	ग_लिखोl(pin_reg, gpio_dev->base + (d->hwirq)*4);
	raw_spin_unlock_irqrestore(&gpio_dev->lock, flags);
पूर्ण

अटल व्योम amd_gpio_irq_mask(काष्ठा irq_data *d)
अणु
	u32 pin_reg;
	अचिन्हित दीर्घ flags;
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(d);
	काष्ठा amd_gpio *gpio_dev = gpiochip_get_data(gc);

	raw_spin_lock_irqsave(&gpio_dev->lock, flags);
	pin_reg = पढ़ोl(gpio_dev->base + (d->hwirq)*4);
	pin_reg &= ~BIT(INTERRUPT_MASK_OFF);
	ग_लिखोl(pin_reg, gpio_dev->base + (d->hwirq)*4);
	raw_spin_unlock_irqrestore(&gpio_dev->lock, flags);
पूर्ण

अटल व्योम amd_gpio_irq_unmask(काष्ठा irq_data *d)
अणु
	u32 pin_reg;
	अचिन्हित दीर्घ flags;
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(d);
	काष्ठा amd_gpio *gpio_dev = gpiochip_get_data(gc);

	raw_spin_lock_irqsave(&gpio_dev->lock, flags);
	pin_reg = पढ़ोl(gpio_dev->base + (d->hwirq)*4);
	pin_reg |= BIT(INTERRUPT_MASK_OFF);
	ग_लिखोl(pin_reg, gpio_dev->base + (d->hwirq)*4);
	raw_spin_unlock_irqrestore(&gpio_dev->lock, flags);
पूर्ण

अटल व्योम amd_gpio_irq_eoi(काष्ठा irq_data *d)
अणु
	u32 reg;
	अचिन्हित दीर्घ flags;
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(d);
	काष्ठा amd_gpio *gpio_dev = gpiochip_get_data(gc);

	raw_spin_lock_irqsave(&gpio_dev->lock, flags);
	reg = पढ़ोl(gpio_dev->base + WAKE_INT_MASTER_REG);
	reg |= EOI_MASK;
	ग_लिखोl(reg, gpio_dev->base + WAKE_INT_MASTER_REG);
	raw_spin_unlock_irqrestore(&gpio_dev->lock, flags);
पूर्ण

अटल पूर्णांक amd_gpio_irq_set_type(काष्ठा irq_data *d, अचिन्हित पूर्णांक type)
अणु
	पूर्णांक ret = 0;
	u32 pin_reg, pin_reg_irq_en, mask;
	अचिन्हित दीर्घ flags;
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(d);
	काष्ठा amd_gpio *gpio_dev = gpiochip_get_data(gc);

	raw_spin_lock_irqsave(&gpio_dev->lock, flags);
	pin_reg = पढ़ोl(gpio_dev->base + (d->hwirq)*4);

	चयन (type & IRQ_TYPE_SENSE_MASK) अणु
	हाल IRQ_TYPE_EDGE_RISING:
		pin_reg &= ~BIT(LEVEL_TRIG_OFF);
		pin_reg &= ~(ACTIVE_LEVEL_MASK << ACTIVE_LEVEL_OFF);
		pin_reg |= ACTIVE_HIGH << ACTIVE_LEVEL_OFF;
		irq_set_handler_locked(d, handle_edge_irq);
		अवरोध;

	हाल IRQ_TYPE_EDGE_FALLING:
		pin_reg &= ~BIT(LEVEL_TRIG_OFF);
		pin_reg &= ~(ACTIVE_LEVEL_MASK << ACTIVE_LEVEL_OFF);
		pin_reg |= ACTIVE_LOW << ACTIVE_LEVEL_OFF;
		irq_set_handler_locked(d, handle_edge_irq);
		अवरोध;

	हाल IRQ_TYPE_EDGE_BOTH:
		pin_reg &= ~BIT(LEVEL_TRIG_OFF);
		pin_reg &= ~(ACTIVE_LEVEL_MASK << ACTIVE_LEVEL_OFF);
		pin_reg |= BOTH_EADGE << ACTIVE_LEVEL_OFF;
		irq_set_handler_locked(d, handle_edge_irq);
		अवरोध;

	हाल IRQ_TYPE_LEVEL_HIGH:
		pin_reg |= LEVEL_TRIGGER << LEVEL_TRIG_OFF;
		pin_reg &= ~(ACTIVE_LEVEL_MASK << ACTIVE_LEVEL_OFF);
		pin_reg |= ACTIVE_HIGH << ACTIVE_LEVEL_OFF;
		irq_set_handler_locked(d, handle_level_irq);
		अवरोध;

	हाल IRQ_TYPE_LEVEL_LOW:
		pin_reg |= LEVEL_TRIGGER << LEVEL_TRIG_OFF;
		pin_reg &= ~(ACTIVE_LEVEL_MASK << ACTIVE_LEVEL_OFF);
		pin_reg |= ACTIVE_LOW << ACTIVE_LEVEL_OFF;
		irq_set_handler_locked(d, handle_level_irq);
		अवरोध;

	हाल IRQ_TYPE_NONE:
		अवरोध;

	शेष:
		dev_err(&gpio_dev->pdev->dev, "Invalid type value\n");
		ret = -EINVAL;
	पूर्ण

	pin_reg |= CLR_INTR_STAT << INTERRUPT_STS_OFF;
	/*
	 * If WAKE_INT_MASTER_REG.MaskStsEn is set, a software ग_लिखो to the
	 * debounce रेजिस्टरs of any GPIO will block wake/पूर्णांकerrupt status
	 * generation क्रम *all* GPIOs क्रम a length of समय that depends on
	 * WAKE_INT_MASTER_REG.MaskStsLength[11:0].  During this period the
	 * INTERRUPT_ENABLE bit will पढ़ो as 0.
	 *
	 * We temporarily enable irq क्रम the GPIO whose configuration is
	 * changing, and then रुको क्रम it to पढ़ो back as 1 to know when
	 * debounce has settled and then disable the irq again.
	 * We करो this polling with the spinlock held to ensure other GPIO
	 * access routines करो not पढ़ो an incorrect value क्रम the irq enable
	 * bit of other GPIOs.  We keep the GPIO masked जबतक polling to aव्योम
	 * spurious irqs, and disable the irq again after polling.
	 */
	mask = BIT(INTERRUPT_ENABLE_OFF);
	pin_reg_irq_en = pin_reg;
	pin_reg_irq_en |= mask;
	pin_reg_irq_en &= ~BIT(INTERRUPT_MASK_OFF);
	ग_लिखोl(pin_reg_irq_en, gpio_dev->base + (d->hwirq)*4);
	जबतक ((पढ़ोl(gpio_dev->base + (d->hwirq)*4) & mask) != mask)
		जारी;
	ग_लिखोl(pin_reg, gpio_dev->base + (d->hwirq)*4);
	raw_spin_unlock_irqrestore(&gpio_dev->lock, flags);

	वापस ret;
पूर्ण

अटल व्योम amd_irq_ack(काष्ठा irq_data *d)
अणु
	/*
	 * based on HW design,there is no need to ack HW
	 * beक्रमe handle current irq. But this routine is
	 * necessary क्रम handle_edge_irq
	*/
पूर्ण

अटल काष्ठा irq_chip amd_gpio_irqchip = अणु
	.name         = "amd_gpio",
	.irq_ack      = amd_irq_ack,
	.irq_enable   = amd_gpio_irq_enable,
	.irq_disable  = amd_gpio_irq_disable,
	.irq_mask     = amd_gpio_irq_mask,
	.irq_unmask   = amd_gpio_irq_unmask,
	.irq_eoi      = amd_gpio_irq_eoi,
	.irq_set_type = amd_gpio_irq_set_type,
	.flags        = IRQCHIP_SKIP_SET_WAKE,
पूर्ण;

#घोषणा PIN_IRQ_PENDING	(BIT(INTERRUPT_STS_OFF) | BIT(WAKE_STS_OFF))

अटल irqवापस_t amd_gpio_irq_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा amd_gpio *gpio_dev = dev_id;
	काष्ठा gpio_chip *gc = &gpio_dev->gc;
	irqवापस_t ret = IRQ_NONE;
	अचिन्हित पूर्णांक i, irqnr;
	अचिन्हित दीर्घ flags;
	u32 __iomem *regs;
	u32  regval;
	u64 status, mask;

	/* Read the wake status */
	raw_spin_lock_irqsave(&gpio_dev->lock, flags);
	status = पढ़ोl(gpio_dev->base + WAKE_INT_STATUS_REG1);
	status <<= 32;
	status |= पढ़ोl(gpio_dev->base + WAKE_INT_STATUS_REG0);
	raw_spin_unlock_irqrestore(&gpio_dev->lock, flags);

	/* Bit 0-45 contain the relevant status bits */
	status &= (1ULL << 46) - 1;
	regs = gpio_dev->base;
	क्रम (mask = 1, irqnr = 0; status; mask <<= 1, regs += 4, irqnr += 4) अणु
		अगर (!(status & mask))
			जारी;
		status &= ~mask;

		/* Each status bit covers four pins */
		क्रम (i = 0; i < 4; i++) अणु
			regval = पढ़ोl(regs + i);
			अगर (!(regval & PIN_IRQ_PENDING) ||
			    !(regval & BIT(INTERRUPT_MASK_OFF)))
				जारी;
			irq = irq_find_mapping(gc->irq.करोमुख्य, irqnr + i);
			अगर (irq != 0)
				generic_handle_irq(irq);

			/* Clear पूर्णांकerrupt.
			 * We must पढ़ो the pin रेजिस्टर again, in हाल the
			 * value was changed जबतक executing
			 * generic_handle_irq() above.
			 * If we didn't find a mapping क्रम the पूर्णांकerrupt,
			 * disable it in order to aव्योम a प्रणाली hang caused
			 * by an पूर्णांकerrupt storm.
			 */
			raw_spin_lock_irqsave(&gpio_dev->lock, flags);
			regval = पढ़ोl(regs + i);
			अगर (irq == 0) अणु
				regval &= ~BIT(INTERRUPT_ENABLE_OFF);
				dev_dbg(&gpio_dev->pdev->dev,
					"Disabling spurious GPIO IRQ %d\n",
					irqnr + i);
			पूर्ण
			ग_लिखोl(regval, regs + i);
			raw_spin_unlock_irqrestore(&gpio_dev->lock, flags);
			ret = IRQ_HANDLED;
		पूर्ण
	पूर्ण

	/* Signal EOI to the GPIO unit */
	raw_spin_lock_irqsave(&gpio_dev->lock, flags);
	regval = पढ़ोl(gpio_dev->base + WAKE_INT_MASTER_REG);
	regval |= EOI_MASK;
	ग_लिखोl(regval, gpio_dev->base + WAKE_INT_MASTER_REG);
	raw_spin_unlock_irqrestore(&gpio_dev->lock, flags);

	वापस ret;
पूर्ण

अटल पूर्णांक amd_get_groups_count(काष्ठा pinctrl_dev *pctldev)
अणु
	काष्ठा amd_gpio *gpio_dev = pinctrl_dev_get_drvdata(pctldev);

	वापस gpio_dev->ngroups;
पूर्ण

अटल स्थिर अक्षर *amd_get_group_name(काष्ठा pinctrl_dev *pctldev,
				      अचिन्हित group)
अणु
	काष्ठा amd_gpio *gpio_dev = pinctrl_dev_get_drvdata(pctldev);

	वापस gpio_dev->groups[group].name;
पूर्ण

अटल पूर्णांक amd_get_group_pins(काष्ठा pinctrl_dev *pctldev,
			      अचिन्हित group,
			      स्थिर अचिन्हित **pins,
			      अचिन्हित *num_pins)
अणु
	काष्ठा amd_gpio *gpio_dev = pinctrl_dev_get_drvdata(pctldev);

	*pins = gpio_dev->groups[group].pins;
	*num_pins = gpio_dev->groups[group].npins;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pinctrl_ops amd_pinctrl_ops = अणु
	.get_groups_count	= amd_get_groups_count,
	.get_group_name		= amd_get_group_name,
	.get_group_pins		= amd_get_group_pins,
#अगर_घोषित CONFIG_OF
	.dt_node_to_map		= pinconf_generic_dt_node_to_map_group,
	.dt_मुक्त_map		= pinctrl_utils_मुक्त_map,
#पूर्ण_अगर
पूर्ण;

अटल पूर्णांक amd_pinconf_get(काष्ठा pinctrl_dev *pctldev,
			  अचिन्हित पूर्णांक pin,
			  अचिन्हित दीर्घ *config)
अणु
	u32 pin_reg;
	अचिन्हित arg;
	अचिन्हित दीर्घ flags;
	काष्ठा amd_gpio *gpio_dev = pinctrl_dev_get_drvdata(pctldev);
	क्रमागत pin_config_param param = pinconf_to_config_param(*config);

	raw_spin_lock_irqsave(&gpio_dev->lock, flags);
	pin_reg = पढ़ोl(gpio_dev->base + pin*4);
	raw_spin_unlock_irqrestore(&gpio_dev->lock, flags);
	चयन (param) अणु
	हाल PIN_CONFIG_INPUT_DEBOUNCE:
		arg = pin_reg & DB_TMR_OUT_MASK;
		अवरोध;

	हाल PIN_CONFIG_BIAS_PULL_DOWN:
		arg = (pin_reg >> PULL_DOWN_ENABLE_OFF) & BIT(0);
		अवरोध;

	हाल PIN_CONFIG_BIAS_PULL_UP:
		arg = (pin_reg >> PULL_UP_SEL_OFF) & (BIT(0) | BIT(1));
		अवरोध;

	हाल PIN_CONFIG_DRIVE_STRENGTH:
		arg = (pin_reg >> DRV_STRENGTH_SEL_OFF) & DRV_STRENGTH_SEL_MASK;
		अवरोध;

	शेष:
		dev_err(&gpio_dev->pdev->dev, "Invalid config param %04x\n",
			param);
		वापस -ENOTSUPP;
	पूर्ण

	*config = pinconf_to_config_packed(param, arg);

	वापस 0;
पूर्ण

अटल पूर्णांक amd_pinconf_set(काष्ठा pinctrl_dev *pctldev, अचिन्हित पूर्णांक pin,
				अचिन्हित दीर्घ *configs, अचिन्हित num_configs)
अणु
	पूर्णांक i;
	u32 arg;
	पूर्णांक ret = 0;
	u32 pin_reg;
	अचिन्हित दीर्घ flags;
	क्रमागत pin_config_param param;
	काष्ठा amd_gpio *gpio_dev = pinctrl_dev_get_drvdata(pctldev);

	raw_spin_lock_irqsave(&gpio_dev->lock, flags);
	क्रम (i = 0; i < num_configs; i++) अणु
		param = pinconf_to_config_param(configs[i]);
		arg = pinconf_to_config_argument(configs[i]);
		pin_reg = पढ़ोl(gpio_dev->base + pin*4);

		चयन (param) अणु
		हाल PIN_CONFIG_INPUT_DEBOUNCE:
			pin_reg &= ~DB_TMR_OUT_MASK;
			pin_reg |= arg & DB_TMR_OUT_MASK;
			अवरोध;

		हाल PIN_CONFIG_BIAS_PULL_DOWN:
			pin_reg &= ~BIT(PULL_DOWN_ENABLE_OFF);
			pin_reg |= (arg & BIT(0)) << PULL_DOWN_ENABLE_OFF;
			अवरोध;

		हाल PIN_CONFIG_BIAS_PULL_UP:
			pin_reg &= ~BIT(PULL_UP_SEL_OFF);
			pin_reg |= (arg & BIT(0)) << PULL_UP_SEL_OFF;
			pin_reg &= ~BIT(PULL_UP_ENABLE_OFF);
			pin_reg |= ((arg>>1) & BIT(0)) << PULL_UP_ENABLE_OFF;
			अवरोध;

		हाल PIN_CONFIG_DRIVE_STRENGTH:
			pin_reg &= ~(DRV_STRENGTH_SEL_MASK
					<< DRV_STRENGTH_SEL_OFF);
			pin_reg |= (arg & DRV_STRENGTH_SEL_MASK)
					<< DRV_STRENGTH_SEL_OFF;
			अवरोध;

		शेष:
			dev_err(&gpio_dev->pdev->dev,
				"Invalid config param %04x\n", param);
			ret = -ENOTSUPP;
		पूर्ण

		ग_लिखोl(pin_reg, gpio_dev->base + pin*4);
	पूर्ण
	raw_spin_unlock_irqrestore(&gpio_dev->lock, flags);

	वापस ret;
पूर्ण

अटल पूर्णांक amd_pinconf_group_get(काष्ठा pinctrl_dev *pctldev,
				अचिन्हित पूर्णांक group,
				अचिन्हित दीर्घ *config)
अणु
	स्थिर अचिन्हित *pins;
	अचिन्हित npins;
	पूर्णांक ret;

	ret = amd_get_group_pins(pctldev, group, &pins, &npins);
	अगर (ret)
		वापस ret;

	अगर (amd_pinconf_get(pctldev, pins[0], config))
			वापस -ENOTSUPP;

	वापस 0;
पूर्ण

अटल पूर्णांक amd_pinconf_group_set(काष्ठा pinctrl_dev *pctldev,
				अचिन्हित group, अचिन्हित दीर्घ *configs,
				अचिन्हित num_configs)
अणु
	स्थिर अचिन्हित *pins;
	अचिन्हित npins;
	पूर्णांक i, ret;

	ret = amd_get_group_pins(pctldev, group, &pins, &npins);
	अगर (ret)
		वापस ret;
	क्रम (i = 0; i < npins; i++) अणु
		अगर (amd_pinconf_set(pctldev, pins[i], configs, num_configs))
			वापस -ENOTSUPP;
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pinconf_ops amd_pinconf_ops = अणु
	.pin_config_get		= amd_pinconf_get,
	.pin_config_set		= amd_pinconf_set,
	.pin_config_group_get = amd_pinconf_group_get,
	.pin_config_group_set = amd_pinconf_group_set,
पूर्ण;

#अगर_घोषित CONFIG_PM_SLEEP
अटल bool amd_gpio_should_save(काष्ठा amd_gpio *gpio_dev, अचिन्हित पूर्णांक pin)
अणु
	स्थिर काष्ठा pin_desc *pd = pin_desc_get(gpio_dev->pctrl, pin);

	अगर (!pd)
		वापस false;

	/*
	 * Only restore the pin अगर it is actually in use by the kernel (or
	 * by userspace).
	 */
	अगर (pd->mux_owner || pd->gpio_owner ||
	    gpiochip_line_is_irq(&gpio_dev->gc, pin))
		वापस true;

	वापस false;
पूर्ण

अटल पूर्णांक amd_gpio_suspend(काष्ठा device *dev)
अणु
	काष्ठा amd_gpio *gpio_dev = dev_get_drvdata(dev);
	काष्ठा pinctrl_desc *desc = gpio_dev->pctrl->desc;
	पूर्णांक i;

	क्रम (i = 0; i < desc->npins; i++) अणु
		पूर्णांक pin = desc->pins[i].number;

		अगर (!amd_gpio_should_save(gpio_dev, pin))
			जारी;

		gpio_dev->saved_regs[i] = पढ़ोl(gpio_dev->base + pin*4);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक amd_gpio_resume(काष्ठा device *dev)
अणु
	काष्ठा amd_gpio *gpio_dev = dev_get_drvdata(dev);
	काष्ठा pinctrl_desc *desc = gpio_dev->pctrl->desc;
	पूर्णांक i;

	क्रम (i = 0; i < desc->npins; i++) अणु
		पूर्णांक pin = desc->pins[i].number;

		अगर (!amd_gpio_should_save(gpio_dev, pin))
			जारी;

		ग_लिखोl(gpio_dev->saved_regs[i], gpio_dev->base + pin*4);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops amd_gpio_pm_ops = अणु
	SET_LATE_SYSTEM_SLEEP_PM_OPS(amd_gpio_suspend,
				     amd_gpio_resume)
पूर्ण;
#पूर्ण_अगर

अटल काष्ठा pinctrl_desc amd_pinctrl_desc = अणु
	.pins	= kerncz_pins,
	.npins = ARRAY_SIZE(kerncz_pins),
	.pctlops = &amd_pinctrl_ops,
	.confops = &amd_pinconf_ops,
	.owner = THIS_MODULE,
पूर्ण;

अटल पूर्णांक amd_gpio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret = 0;
	पूर्णांक irq_base;
	काष्ठा resource *res;
	काष्ठा amd_gpio *gpio_dev;
	काष्ठा gpio_irq_chip *girq;

	gpio_dev = devm_kzalloc(&pdev->dev,
				माप(काष्ठा amd_gpio), GFP_KERNEL);
	अगर (!gpio_dev)
		वापस -ENOMEM;

	raw_spin_lock_init(&gpio_dev->lock);

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!res) अणु
		dev_err(&pdev->dev, "Failed to get gpio io resource.\n");
		वापस -EINVAL;
	पूर्ण

	gpio_dev->base = devm_ioremap(&pdev->dev, res->start,
						resource_size(res));
	अगर (!gpio_dev->base)
		वापस -ENOMEM;

	irq_base = platक्रमm_get_irq(pdev, 0);
	अगर (irq_base < 0)
		वापस irq_base;

#अगर_घोषित CONFIG_PM_SLEEP
	gpio_dev->saved_regs = devm_kसुस्मृति(&pdev->dev, amd_pinctrl_desc.npins,
					    माप(*gpio_dev->saved_regs),
					    GFP_KERNEL);
	अगर (!gpio_dev->saved_regs)
		वापस -ENOMEM;
#पूर्ण_अगर

	gpio_dev->pdev = pdev;
	gpio_dev->gc.get_direction	= amd_gpio_get_direction;
	gpio_dev->gc.direction_input	= amd_gpio_direction_input;
	gpio_dev->gc.direction_output	= amd_gpio_direction_output;
	gpio_dev->gc.get			= amd_gpio_get_value;
	gpio_dev->gc.set			= amd_gpio_set_value;
	gpio_dev->gc.set_config		= amd_gpio_set_config;
	gpio_dev->gc.dbg_show		= amd_gpio_dbg_show;

	gpio_dev->gc.base		= -1;
	gpio_dev->gc.label			= pdev->name;
	gpio_dev->gc.owner			= THIS_MODULE;
	gpio_dev->gc.parent			= &pdev->dev;
	gpio_dev->gc.ngpio			= resource_size(res) / 4;
#अगर defined(CONFIG_OF_GPIO)
	gpio_dev->gc.of_node			= pdev->dev.of_node;
#पूर्ण_अगर

	gpio_dev->hwbank_num = gpio_dev->gc.ngpio / 64;
	gpio_dev->groups = kerncz_groups;
	gpio_dev->ngroups = ARRAY_SIZE(kerncz_groups);

	amd_pinctrl_desc.name = dev_name(&pdev->dev);
	gpio_dev->pctrl = devm_pinctrl_रेजिस्टर(&pdev->dev, &amd_pinctrl_desc,
						gpio_dev);
	अगर (IS_ERR(gpio_dev->pctrl)) अणु
		dev_err(&pdev->dev, "Couldn't register pinctrl driver\n");
		वापस PTR_ERR(gpio_dev->pctrl);
	पूर्ण

	girq = &gpio_dev->gc.irq;
	girq->chip = &amd_gpio_irqchip;
	/* This will let us handle the parent IRQ in the driver */
	girq->parent_handler = शून्य;
	girq->num_parents = 0;
	girq->parents = शून्य;
	girq->शेष_type = IRQ_TYPE_NONE;
	girq->handler = handle_simple_irq;

	ret = gpiochip_add_data(&gpio_dev->gc, gpio_dev);
	अगर (ret)
		वापस ret;

	ret = gpiochip_add_pin_range(&gpio_dev->gc, dev_name(&pdev->dev),
				0, 0, gpio_dev->gc.ngpio);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Failed to add pin range\n");
		जाओ out2;
	पूर्ण

	ret = devm_request_irq(&pdev->dev, irq_base, amd_gpio_irq_handler,
			       IRQF_SHARED, KBUILD_MODNAME, gpio_dev);
	अगर (ret)
		जाओ out2;

	platक्रमm_set_drvdata(pdev, gpio_dev);

	dev_dbg(&pdev->dev, "amd gpio driver loaded\n");
	वापस ret;

out2:
	gpiochip_हटाओ(&gpio_dev->gc);

	वापस ret;
पूर्ण

अटल पूर्णांक amd_gpio_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा amd_gpio *gpio_dev;

	gpio_dev = platक्रमm_get_drvdata(pdev);

	gpiochip_हटाओ(&gpio_dev->gc);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_ACPI
अटल स्थिर काष्ठा acpi_device_id amd_gpio_acpi_match[] = अणु
	अणु "AMD0030", 0 पूर्ण,
	अणु "AMDI0030", 0पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, amd_gpio_acpi_match);
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver amd_gpio_driver = अणु
	.driver		= अणु
		.name	= "amd_gpio",
		.acpi_match_table = ACPI_PTR(amd_gpio_acpi_match),
#अगर_घोषित CONFIG_PM_SLEEP
		.pm	= &amd_gpio_pm_ops,
#पूर्ण_अगर
	पूर्ण,
	.probe		= amd_gpio_probe,
	.हटाओ		= amd_gpio_हटाओ,
पूर्ण;

module_platक्रमm_driver(amd_gpio_driver);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Ken Xue <Ken.Xue@amd.com>, Jeff Wu <Jeff.Wu@amd.com>");
MODULE_DESCRIPTION("AMD GPIO pinctrl driver");
