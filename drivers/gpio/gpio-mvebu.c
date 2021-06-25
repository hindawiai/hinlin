<शैली गुरु>
/*
 * GPIO driver क्रम Marvell SoCs
 *
 * Copyright (C) 2012 Marvell
 *
 * Thomas Petazzoni <thomas.petazzoni@मुक्त-electrons.com>
 * Andrew Lunn <andrew@lunn.ch>
 * Sebastian Hesselbarth <sebastian.hesselbarth@gmail.com>
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 *
 * This driver is a fairly straightक्रमward GPIO driver क्रम the
 * complete family of Marvell EBU SoC platक्रमms (Orion, Dove,
 * Kirkwood, Discovery, Armada 370/XP). The only complनिकासy of this
 * driver is the dअगरferent रेजिस्टर layout that exists between the
 * non-SMP platक्रमms (Orion, Dove, Kirkwood, Armada 370) and the SMP
 * platक्रमms (MV78200 from the Discovery family and the Armada
 * XP). Thereक्रमe, this driver handles three variants of the GPIO
 * block:
 * - the basic variant, called "orion-gpio", with the simplest
 *   रेजिस्टर set. Used on Orion, Dove, Kirkwoord, Armada 370 and
 *   non-SMP Discovery प्रणालीs
 * - the mv78200 variant क्रम MV78200 Discovery प्रणालीs. This variant
 *   turns the edge mask and level mask रेजिस्टरs पूर्णांकo CPU0 edge
 *   mask/level mask रेजिस्टरs, and adds CPU1 edge mask/level mask
 *   रेजिस्टरs.
 * - the armadaxp variant क्रम Armada XP प्रणालीs. This variant keeps
 *   the normal cause/edge mask/level mask रेजिस्टरs when the global
 *   पूर्णांकerrupts are used, but adds per-CPU cause/edge mask/level mask
 *   रेजिस्टरs n a separate memory area क्रम the per-CPU GPIO
 *   पूर्णांकerrupts.
 */

#समावेश <linux/bitops.h>
#समावेश <linux/clk.h>
#समावेश <linux/err.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/gpio/machine.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/irq.h>
#समावेश <linux/irqchip/chained_irq.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/of_device.h>
#समावेश <linux/pinctrl/consumer.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pwm.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>

/*
 * GPIO unit रेजिस्टर offsets.
 */
#घोषणा GPIO_OUT_OFF			0x0000
#घोषणा GPIO_IO_CONF_OFF		0x0004
#घोषणा GPIO_BLINK_EN_OFF		0x0008
#घोषणा GPIO_IN_POL_OFF			0x000c
#घोषणा GPIO_DATA_IN_OFF		0x0010
#घोषणा GPIO_EDGE_CAUSE_OFF		0x0014
#घोषणा GPIO_EDGE_MASK_OFF		0x0018
#घोषणा GPIO_LEVEL_MASK_OFF		0x001c
#घोषणा GPIO_BLINK_CNT_SELECT_OFF	0x0020

/*
 * PWM रेजिस्टर offsets.
 */
#घोषणा PWM_BLINK_ON_DURATION_OFF	0x0
#घोषणा PWM_BLINK_OFF_DURATION_OFF	0x4
#घोषणा PWM_BLINK_COUNTER_B_OFF		0x8

/* Armada 8k variant gpios रेजिस्टर offsets */
#घोषणा AP80X_GPIO0_OFF_A8K		0x1040
#घोषणा CP11X_GPIO0_OFF_A8K		0x100
#घोषणा CP11X_GPIO1_OFF_A8K		0x140

/* The MV78200 has per-CPU रेजिस्टरs क्रम edge mask and level mask */
#घोषणा GPIO_EDGE_MASK_MV78200_OFF(cpu)	  ((cpu) ? 0x30 : 0x18)
#घोषणा GPIO_LEVEL_MASK_MV78200_OFF(cpu)  ((cpu) ? 0x34 : 0x1C)

/*
 * The Armada XP has per-CPU रेजिस्टरs क्रम पूर्णांकerrupt cause, पूर्णांकerrupt
 * mask and पूर्णांकerrupt level mask. Those are in percpu_regs range.
 */
#घोषणा GPIO_EDGE_CAUSE_ARMADAXP_OFF(cpu) ((cpu) * 0x4)
#घोषणा GPIO_EDGE_MASK_ARMADAXP_OFF(cpu)  (0x10 + (cpu) * 0x4)
#घोषणा GPIO_LEVEL_MASK_ARMADAXP_OFF(cpu) (0x20 + (cpu) * 0x4)

#घोषणा MVEBU_GPIO_SOC_VARIANT_ORION	0x1
#घोषणा MVEBU_GPIO_SOC_VARIANT_MV78200	0x2
#घोषणा MVEBU_GPIO_SOC_VARIANT_ARMADAXP 0x3
#घोषणा MVEBU_GPIO_SOC_VARIANT_A8K	0x4

#घोषणा MVEBU_MAX_GPIO_PER_BANK		32

काष्ठा mvebu_pwm अणु
	काष्ठा regmap		*regs;
	u32			 offset;
	अचिन्हित दीर्घ		 clk_rate;
	काष्ठा gpio_desc	*gpiod;
	काष्ठा pwm_chip		 chip;
	spinlock_t		 lock;
	काष्ठा mvebu_gpio_chip	*mvchip;

	/* Used to preserve GPIO/PWM रेजिस्टरs across suspend/resume */
	u32			 blink_select;
	u32			 blink_on_duration;
	u32			 blink_off_duration;
पूर्ण;

काष्ठा mvebu_gpio_chip अणु
	काष्ठा gpio_chip   chip;
	काष्ठा regmap     *regs;
	u32		   offset;
	काष्ठा regmap     *percpu_regs;
	पूर्णांक		   irqbase;
	काष्ठा irq_करोमुख्य *करोमुख्य;
	पूर्णांक		   soc_variant;

	/* Used क्रम PWM support */
	काष्ठा clk	  *clk;
	काष्ठा mvebu_pwm  *mvpwm;

	/* Used to preserve GPIO रेजिस्टरs across suspend/resume */
	u32		   out_reg;
	u32		   io_conf_reg;
	u32		   blink_en_reg;
	u32		   in_pol_reg;
	u32		   edge_mask_regs[4];
	u32		   level_mask_regs[4];
पूर्ण;

/*
 * Functions वापसing addresses of inभागidual रेजिस्टरs क्रम a given
 * GPIO controller.
 */

अटल व्योम mvebu_gpioreg_edge_cause(काष्ठा mvebu_gpio_chip *mvchip,
			 काष्ठा regmap **map, अचिन्हित पूर्णांक *offset)
अणु
	पूर्णांक cpu;

	चयन (mvchip->soc_variant) अणु
	हाल MVEBU_GPIO_SOC_VARIANT_ORION:
	हाल MVEBU_GPIO_SOC_VARIANT_MV78200:
	हाल MVEBU_GPIO_SOC_VARIANT_A8K:
		*map = mvchip->regs;
		*offset = GPIO_EDGE_CAUSE_OFF + mvchip->offset;
		अवरोध;
	हाल MVEBU_GPIO_SOC_VARIANT_ARMADAXP:
		cpu = smp_processor_id();
		*map = mvchip->percpu_regs;
		*offset = GPIO_EDGE_CAUSE_ARMADAXP_OFF(cpu);
		अवरोध;
	शेष:
		BUG();
	पूर्ण
पूर्ण

अटल u32
mvebu_gpio_पढ़ो_edge_cause(काष्ठा mvebu_gpio_chip *mvchip)
अणु
	काष्ठा regmap *map;
	अचिन्हित पूर्णांक offset;
	u32 val;

	mvebu_gpioreg_edge_cause(mvchip, &map, &offset);
	regmap_पढ़ो(map, offset, &val);

	वापस val;
पूर्ण

अटल व्योम
mvebu_gpio_ग_लिखो_edge_cause(काष्ठा mvebu_gpio_chip *mvchip, u32 val)
अणु
	काष्ठा regmap *map;
	अचिन्हित पूर्णांक offset;

	mvebu_gpioreg_edge_cause(mvchip, &map, &offset);
	regmap_ग_लिखो(map, offset, val);
पूर्ण

अटल अंतरभूत व्योम
mvebu_gpioreg_edge_mask(काष्ठा mvebu_gpio_chip *mvchip,
			काष्ठा regmap **map, अचिन्हित पूर्णांक *offset)
अणु
	पूर्णांक cpu;

	चयन (mvchip->soc_variant) अणु
	हाल MVEBU_GPIO_SOC_VARIANT_ORION:
	हाल MVEBU_GPIO_SOC_VARIANT_A8K:
		*map = mvchip->regs;
		*offset = GPIO_EDGE_MASK_OFF + mvchip->offset;
		अवरोध;
	हाल MVEBU_GPIO_SOC_VARIANT_MV78200:
		cpu = smp_processor_id();
		*map = mvchip->regs;
		*offset = GPIO_EDGE_MASK_MV78200_OFF(cpu);
		अवरोध;
	हाल MVEBU_GPIO_SOC_VARIANT_ARMADAXP:
		cpu = smp_processor_id();
		*map = mvchip->percpu_regs;
		*offset = GPIO_EDGE_MASK_ARMADAXP_OFF(cpu);
		अवरोध;
	शेष:
		BUG();
	पूर्ण
पूर्ण

अटल u32
mvebu_gpio_पढ़ो_edge_mask(काष्ठा mvebu_gpio_chip *mvchip)
अणु
	काष्ठा regmap *map;
	अचिन्हित पूर्णांक offset;
	u32 val;

	mvebu_gpioreg_edge_mask(mvchip, &map, &offset);
	regmap_पढ़ो(map, offset, &val);

	वापस val;
पूर्ण

अटल व्योम
mvebu_gpio_ग_लिखो_edge_mask(काष्ठा mvebu_gpio_chip *mvchip, u32 val)
अणु
	काष्ठा regmap *map;
	अचिन्हित पूर्णांक offset;

	mvebu_gpioreg_edge_mask(mvchip, &map, &offset);
	regmap_ग_लिखो(map, offset, val);
पूर्ण

अटल व्योम
mvebu_gpioreg_level_mask(काष्ठा mvebu_gpio_chip *mvchip,
			 काष्ठा regmap **map, अचिन्हित पूर्णांक *offset)
अणु
	पूर्णांक cpu;

	चयन (mvchip->soc_variant) अणु
	हाल MVEBU_GPIO_SOC_VARIANT_ORION:
	हाल MVEBU_GPIO_SOC_VARIANT_A8K:
		*map = mvchip->regs;
		*offset = GPIO_LEVEL_MASK_OFF + mvchip->offset;
		अवरोध;
	हाल MVEBU_GPIO_SOC_VARIANT_MV78200:
		cpu = smp_processor_id();
		*map = mvchip->regs;
		*offset = GPIO_LEVEL_MASK_MV78200_OFF(cpu);
		अवरोध;
	हाल MVEBU_GPIO_SOC_VARIANT_ARMADAXP:
		cpu = smp_processor_id();
		*map = mvchip->percpu_regs;
		*offset = GPIO_LEVEL_MASK_ARMADAXP_OFF(cpu);
		अवरोध;
	शेष:
		BUG();
	पूर्ण
पूर्ण

अटल u32
mvebu_gpio_पढ़ो_level_mask(काष्ठा mvebu_gpio_chip *mvchip)
अणु
	काष्ठा regmap *map;
	अचिन्हित पूर्णांक offset;
	u32 val;

	mvebu_gpioreg_level_mask(mvchip, &map, &offset);
	regmap_पढ़ो(map, offset, &val);

	वापस val;
पूर्ण

अटल व्योम
mvebu_gpio_ग_लिखो_level_mask(काष्ठा mvebu_gpio_chip *mvchip, u32 val)
अणु
	काष्ठा regmap *map;
	अचिन्हित पूर्णांक offset;

	mvebu_gpioreg_level_mask(mvchip, &map, &offset);
	regmap_ग_लिखो(map, offset, val);
पूर्ण

/*
 * Functions वापसing offsets of inभागidual रेजिस्टरs क्रम a given
 * PWM controller.
 */
अटल अचिन्हित पूर्णांक mvebu_pwmreg_blink_on_duration(काष्ठा mvebu_pwm *mvpwm)
अणु
	वापस mvpwm->offset + PWM_BLINK_ON_DURATION_OFF;
पूर्ण

अटल अचिन्हित पूर्णांक mvebu_pwmreg_blink_off_duration(काष्ठा mvebu_pwm *mvpwm)
अणु
	वापस mvpwm->offset + PWM_BLINK_OFF_DURATION_OFF;
पूर्ण

/*
 * Functions implementing the gpio_chip methods
 */
अटल व्योम mvebu_gpio_set(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक pin, पूर्णांक value)
अणु
	काष्ठा mvebu_gpio_chip *mvchip = gpiochip_get_data(chip);

	regmap_update_bits(mvchip->regs, GPIO_OUT_OFF + mvchip->offset,
			   BIT(pin), value ? BIT(pin) : 0);
पूर्ण

अटल पूर्णांक mvebu_gpio_get(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक pin)
अणु
	काष्ठा mvebu_gpio_chip *mvchip = gpiochip_get_data(chip);
	u32 u;

	regmap_पढ़ो(mvchip->regs, GPIO_IO_CONF_OFF + mvchip->offset, &u);

	अगर (u & BIT(pin)) अणु
		u32 data_in, in_pol;

		regmap_पढ़ो(mvchip->regs, GPIO_DATA_IN_OFF + mvchip->offset,
			    &data_in);
		regmap_पढ़ो(mvchip->regs, GPIO_IN_POL_OFF + mvchip->offset,
			    &in_pol);
		u = data_in ^ in_pol;
	पूर्ण अन्यथा अणु
		regmap_पढ़ो(mvchip->regs, GPIO_OUT_OFF + mvchip->offset, &u);
	पूर्ण

	वापस (u >> pin) & 1;
पूर्ण

अटल व्योम mvebu_gpio_blink(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक pin,
			     पूर्णांक value)
अणु
	काष्ठा mvebu_gpio_chip *mvchip = gpiochip_get_data(chip);

	regmap_update_bits(mvchip->regs, GPIO_BLINK_EN_OFF + mvchip->offset,
			   BIT(pin), value ? BIT(pin) : 0);
पूर्ण

अटल पूर्णांक mvebu_gpio_direction_input(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक pin)
अणु
	काष्ठा mvebu_gpio_chip *mvchip = gpiochip_get_data(chip);
	पूर्णांक ret;

	/*
	 * Check with the pinctrl driver whether this pin is usable as
	 * an input GPIO
	 */
	ret = pinctrl_gpio_direction_input(chip->base + pin);
	अगर (ret)
		वापस ret;

	regmap_update_bits(mvchip->regs, GPIO_IO_CONF_OFF + mvchip->offset,
			   BIT(pin), BIT(pin));

	वापस 0;
पूर्ण

अटल पूर्णांक mvebu_gpio_direction_output(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक pin,
				       पूर्णांक value)
अणु
	काष्ठा mvebu_gpio_chip *mvchip = gpiochip_get_data(chip);
	पूर्णांक ret;

	/*
	 * Check with the pinctrl driver whether this pin is usable as
	 * an output GPIO
	 */
	ret = pinctrl_gpio_direction_output(chip->base + pin);
	अगर (ret)
		वापस ret;

	mvebu_gpio_blink(chip, pin, 0);
	mvebu_gpio_set(chip, pin, value);

	regmap_update_bits(mvchip->regs, GPIO_IO_CONF_OFF + mvchip->offset,
			   BIT(pin), 0);

	वापस 0;
पूर्ण

अटल पूर्णांक mvebu_gpio_get_direction(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक pin)
अणु
	काष्ठा mvebu_gpio_chip *mvchip = gpiochip_get_data(chip);
	u32 u;

	regmap_पढ़ो(mvchip->regs, GPIO_IO_CONF_OFF + mvchip->offset, &u);

	अगर (u & BIT(pin))
		वापस GPIO_LINE_सूचीECTION_IN;

	वापस GPIO_LINE_सूचीECTION_OUT;
पूर्ण

अटल पूर्णांक mvebu_gpio_to_irq(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक pin)
अणु
	काष्ठा mvebu_gpio_chip *mvchip = gpiochip_get_data(chip);

	वापस irq_create_mapping(mvchip->करोमुख्य, pin);
पूर्ण

/*
 * Functions implementing the irq_chip methods
 */
अटल व्योम mvebu_gpio_irq_ack(काष्ठा irq_data *d)
अणु
	काष्ठा irq_chip_generic *gc = irq_data_get_irq_chip_data(d);
	काष्ठा mvebu_gpio_chip *mvchip = gc->निजी;
	u32 mask = d->mask;

	irq_gc_lock(gc);
	mvebu_gpio_ग_लिखो_edge_cause(mvchip, ~mask);
	irq_gc_unlock(gc);
पूर्ण

अटल व्योम mvebu_gpio_edge_irq_mask(काष्ठा irq_data *d)
अणु
	काष्ठा irq_chip_generic *gc = irq_data_get_irq_chip_data(d);
	काष्ठा mvebu_gpio_chip *mvchip = gc->निजी;
	काष्ठा irq_chip_type *ct = irq_data_get_chip_type(d);
	u32 mask = d->mask;

	irq_gc_lock(gc);
	ct->mask_cache_priv &= ~mask;
	mvebu_gpio_ग_लिखो_edge_mask(mvchip, ct->mask_cache_priv);
	irq_gc_unlock(gc);
पूर्ण

अटल व्योम mvebu_gpio_edge_irq_unmask(काष्ठा irq_data *d)
अणु
	काष्ठा irq_chip_generic *gc = irq_data_get_irq_chip_data(d);
	काष्ठा mvebu_gpio_chip *mvchip = gc->निजी;
	काष्ठा irq_chip_type *ct = irq_data_get_chip_type(d);
	u32 mask = d->mask;

	irq_gc_lock(gc);
	mvebu_gpio_ग_लिखो_edge_cause(mvchip, ~mask);
	ct->mask_cache_priv |= mask;
	mvebu_gpio_ग_लिखो_edge_mask(mvchip, ct->mask_cache_priv);
	irq_gc_unlock(gc);
पूर्ण

अटल व्योम mvebu_gpio_level_irq_mask(काष्ठा irq_data *d)
अणु
	काष्ठा irq_chip_generic *gc = irq_data_get_irq_chip_data(d);
	काष्ठा mvebu_gpio_chip *mvchip = gc->निजी;
	काष्ठा irq_chip_type *ct = irq_data_get_chip_type(d);
	u32 mask = d->mask;

	irq_gc_lock(gc);
	ct->mask_cache_priv &= ~mask;
	mvebu_gpio_ग_लिखो_level_mask(mvchip, ct->mask_cache_priv);
	irq_gc_unlock(gc);
पूर्ण

अटल व्योम mvebu_gpio_level_irq_unmask(काष्ठा irq_data *d)
अणु
	काष्ठा irq_chip_generic *gc = irq_data_get_irq_chip_data(d);
	काष्ठा mvebu_gpio_chip *mvchip = gc->निजी;
	काष्ठा irq_chip_type *ct = irq_data_get_chip_type(d);
	u32 mask = d->mask;

	irq_gc_lock(gc);
	ct->mask_cache_priv |= mask;
	mvebu_gpio_ग_लिखो_level_mask(mvchip, ct->mask_cache_priv);
	irq_gc_unlock(gc);
पूर्ण

/*****************************************************************************
 * MVEBU GPIO IRQ
 *
 * GPIO_IN_POL रेजिस्टर controls whether GPIO_DATA_IN will hold the same
 * value of the line or the opposite value.
 *
 * Level IRQ handlers: DATA_IN is used directly as cause रेजिस्टर.
 *		       Interrupt are masked by LEVEL_MASK रेजिस्टरs.
 * Edge IRQ handlers:  Change in DATA_IN are latched in EDGE_CAUSE.
 *		       Interrupt are masked by EDGE_MASK रेजिस्टरs.
 * Both-edge handlers: Similar to regular Edge handlers, but also swaps
 *		       the polarity to catch the next line transaction.
 *		       This is a race condition that might not perfectly
 *		       work on some use हालs.
 *
 * Every eight GPIO lines are grouped (OR'ed) beक्रमe going up to मुख्य
 * cause रेजिस्टर.
 *
 *		      EDGE  cause    mask
 *	  data-in   /--------| |-----| |----\
 *     -----| |-----			     ---- to मुख्य cause reg
 *	     X	    \----------------| |----/
 *	  polarity    LEVEL	     mask
 *
 ****************************************************************************/

अटल पूर्णांक mvebu_gpio_irq_set_type(काष्ठा irq_data *d, अचिन्हित पूर्णांक type)
अणु
	काष्ठा irq_chip_generic *gc = irq_data_get_irq_chip_data(d);
	काष्ठा irq_chip_type *ct = irq_data_get_chip_type(d);
	काष्ठा mvebu_gpio_chip *mvchip = gc->निजी;
	पूर्णांक pin;
	u32 u;

	pin = d->hwirq;

	regmap_पढ़ो(mvchip->regs, GPIO_IO_CONF_OFF + mvchip->offset, &u);
	अगर ((u & BIT(pin)) == 0)
		वापस -EINVAL;

	type &= IRQ_TYPE_SENSE_MASK;
	अगर (type == IRQ_TYPE_NONE)
		वापस -EINVAL;

	/* Check अगर we need to change chip and handler */
	अगर (!(ct->type & type))
		अगर (irq_setup_alt_chip(d, type))
			वापस -EINVAL;

	/*
	 * Configure पूर्णांकerrupt polarity.
	 */
	चयन (type) अणु
	हाल IRQ_TYPE_EDGE_RISING:
	हाल IRQ_TYPE_LEVEL_HIGH:
		regmap_update_bits(mvchip->regs,
				   GPIO_IN_POL_OFF + mvchip->offset,
				   BIT(pin), 0);
		अवरोध;
	हाल IRQ_TYPE_EDGE_FALLING:
	हाल IRQ_TYPE_LEVEL_LOW:
		regmap_update_bits(mvchip->regs,
				   GPIO_IN_POL_OFF + mvchip->offset,
				   BIT(pin), BIT(pin));
		अवरोध;
	हाल IRQ_TYPE_EDGE_BOTH: अणु
		u32 data_in, in_pol, val;

		regmap_पढ़ो(mvchip->regs,
			    GPIO_IN_POL_OFF + mvchip->offset, &in_pol);
		regmap_पढ़ो(mvchip->regs,
			    GPIO_DATA_IN_OFF + mvchip->offset, &data_in);

		/*
		 * set initial polarity based on current input level
		 */
		अगर ((data_in ^ in_pol) & BIT(pin))
			val = BIT(pin); /* falling */
		अन्यथा
			val = 0; /* raising */

		regmap_update_bits(mvchip->regs,
				   GPIO_IN_POL_OFF + mvchip->offset,
				   BIT(pin), val);
		अवरोध;
	पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम mvebu_gpio_irq_handler(काष्ठा irq_desc *desc)
अणु
	काष्ठा mvebu_gpio_chip *mvchip = irq_desc_get_handler_data(desc);
	काष्ठा irq_chip *chip = irq_desc_get_chip(desc);
	u32 cause, type, data_in, level_mask, edge_cause, edge_mask;
	पूर्णांक i;

	अगर (mvchip == शून्य)
		वापस;

	chained_irq_enter(chip, desc);

	regmap_पढ़ो(mvchip->regs, GPIO_DATA_IN_OFF + mvchip->offset, &data_in);
	level_mask = mvebu_gpio_पढ़ो_level_mask(mvchip);
	edge_cause = mvebu_gpio_पढ़ो_edge_cause(mvchip);
	edge_mask  = mvebu_gpio_पढ़ो_edge_mask(mvchip);

	cause = (data_in & level_mask) | (edge_cause & edge_mask);

	क्रम (i = 0; i < mvchip->chip.ngpio; i++) अणु
		पूर्णांक irq;

		irq = irq_find_mapping(mvchip->करोमुख्य, i);

		अगर (!(cause & BIT(i)))
			जारी;

		type = irq_get_trigger_type(irq);
		अगर ((type & IRQ_TYPE_SENSE_MASK) == IRQ_TYPE_EDGE_BOTH) अणु
			/* Swap polarity (race with GPIO line) */
			u32 polarity;

			regmap_पढ़ो(mvchip->regs,
				    GPIO_IN_POL_OFF + mvchip->offset,
				    &polarity);
			polarity ^= BIT(i);
			regmap_ग_लिखो(mvchip->regs,
				     GPIO_IN_POL_OFF + mvchip->offset,
				     polarity);
		पूर्ण

		generic_handle_irq(irq);
	पूर्ण

	chained_irq_निकास(chip, desc);
पूर्ण

अटल स्थिर काष्ठा regmap_config mvebu_gpio_regmap_config = अणु
	.reg_bits = 32,
	.reg_stride = 4,
	.val_bits = 32,
	.fast_io = true,
पूर्ण;

/*
 * Functions implementing the pwm_chip methods
 */
अटल काष्ठा mvebu_pwm *to_mvebu_pwm(काष्ठा pwm_chip *chip)
अणु
	वापस container_of(chip, काष्ठा mvebu_pwm, chip);
पूर्ण

अटल पूर्णांक mvebu_pwm_request(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm)
अणु
	काष्ठा mvebu_pwm *mvpwm = to_mvebu_pwm(chip);
	काष्ठा mvebu_gpio_chip *mvchip = mvpwm->mvchip;
	काष्ठा gpio_desc *desc;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;

	spin_lock_irqsave(&mvpwm->lock, flags);

	अगर (mvpwm->gpiod) अणु
		ret = -EBUSY;
	पूर्ण अन्यथा अणु
		desc = gpiochip_request_own_desc(&mvchip->chip,
						 pwm->hwpwm, "mvebu-pwm",
						 GPIO_ACTIVE_HIGH,
						 GPIOD_OUT_LOW);
		अगर (IS_ERR(desc)) अणु
			ret = PTR_ERR(desc);
			जाओ out;
		पूर्ण

		mvpwm->gpiod = desc;
	पूर्ण
out:
	spin_unlock_irqrestore(&mvpwm->lock, flags);
	वापस ret;
पूर्ण

अटल व्योम mvebu_pwm_मुक्त(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm)
अणु
	काष्ठा mvebu_pwm *mvpwm = to_mvebu_pwm(chip);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&mvpwm->lock, flags);
	gpiochip_मुक्त_own_desc(mvpwm->gpiod);
	mvpwm->gpiod = शून्य;
	spin_unlock_irqrestore(&mvpwm->lock, flags);
पूर्ण

अटल व्योम mvebu_pwm_get_state(काष्ठा pwm_chip *chip,
				काष्ठा pwm_device *pwm,
				काष्ठा pwm_state *state) अणु

	काष्ठा mvebu_pwm *mvpwm = to_mvebu_pwm(chip);
	काष्ठा mvebu_gpio_chip *mvchip = mvpwm->mvchip;
	अचिन्हित दीर्घ दीर्घ val;
	अचिन्हित दीर्घ flags;
	u32 u;

	spin_lock_irqsave(&mvpwm->lock, flags);

	regmap_पढ़ो(mvpwm->regs, mvebu_pwmreg_blink_on_duration(mvpwm), &u);
	/* Hardware treats zero as 2^32. See mvebu_pwm_apply(). */
	अगर (u > 0)
		val = u;
	अन्यथा
		val = अच_पूर्णांक_उच्च + 1ULL;
	state->duty_cycle = DIV_ROUND_UP_ULL(val * NSEC_PER_SEC,
			mvpwm->clk_rate);

	regmap_पढ़ो(mvpwm->regs, mvebu_pwmreg_blink_off_duration(mvpwm), &u);
	/* period = on + off duration */
	अगर (u > 0)
		val += u;
	अन्यथा
		val += अच_पूर्णांक_उच्च + 1ULL;
	state->period = DIV_ROUND_UP_ULL(val * NSEC_PER_SEC, mvpwm->clk_rate);

	regmap_पढ़ो(mvchip->regs, GPIO_BLINK_EN_OFF + mvchip->offset, &u);
	अगर (u)
		state->enabled = true;
	अन्यथा
		state->enabled = false;

	spin_unlock_irqrestore(&mvpwm->lock, flags);
पूर्ण

अटल पूर्णांक mvebu_pwm_apply(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm,
			   स्थिर काष्ठा pwm_state *state)
अणु
	काष्ठा mvebu_pwm *mvpwm = to_mvebu_pwm(chip);
	काष्ठा mvebu_gpio_chip *mvchip = mvpwm->mvchip;
	अचिन्हित दीर्घ दीर्घ val;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक on, off;

	val = (अचिन्हित दीर्घ दीर्घ) mvpwm->clk_rate * state->duty_cycle;
	करो_भाग(val, NSEC_PER_SEC);
	अगर (val > अच_पूर्णांक_उच्च + 1ULL)
		वापस -EINVAL;
	/*
	 * Zero on/off values करोn't work as expected. Experimentation shows
	 * that zero value is treated as 2^32. This behavior is not करोcumented.
	 */
	अगर (val == अच_पूर्णांक_उच्च + 1ULL)
		on = 0;
	अन्यथा अगर (val)
		on = val;
	अन्यथा
		on = 1;

	val = (अचिन्हित दीर्घ दीर्घ) mvpwm->clk_rate * state->period;
	करो_भाग(val, NSEC_PER_SEC);
	val -= on;
	अगर (val > अच_पूर्णांक_उच्च + 1ULL)
		वापस -EINVAL;
	अगर (val == अच_पूर्णांक_उच्च + 1ULL)
		off = 0;
	अन्यथा अगर (val)
		off = val;
	अन्यथा
		off = 1;

	spin_lock_irqsave(&mvpwm->lock, flags);

	regmap_ग_लिखो(mvpwm->regs, mvebu_pwmreg_blink_on_duration(mvpwm), on);
	regmap_ग_लिखो(mvpwm->regs, mvebu_pwmreg_blink_off_duration(mvpwm), off);
	अगर (state->enabled)
		mvebu_gpio_blink(&mvchip->chip, pwm->hwpwm, 1);
	अन्यथा
		mvebu_gpio_blink(&mvchip->chip, pwm->hwpwm, 0);

	spin_unlock_irqrestore(&mvpwm->lock, flags);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pwm_ops mvebu_pwm_ops = अणु
	.request = mvebu_pwm_request,
	.मुक्त = mvebu_pwm_मुक्त,
	.get_state = mvebu_pwm_get_state,
	.apply = mvebu_pwm_apply,
	.owner = THIS_MODULE,
पूर्ण;

अटल व्योम __maybe_unused mvebu_pwm_suspend(काष्ठा mvebu_gpio_chip *mvchip)
अणु
	काष्ठा mvebu_pwm *mvpwm = mvchip->mvpwm;

	regmap_पढ़ो(mvchip->regs, GPIO_BLINK_CNT_SELECT_OFF + mvchip->offset,
		    &mvpwm->blink_select);
	regmap_पढ़ो(mvpwm->regs, mvebu_pwmreg_blink_on_duration(mvpwm),
		    &mvpwm->blink_on_duration);
	regmap_पढ़ो(mvpwm->regs, mvebu_pwmreg_blink_off_duration(mvpwm),
		    &mvpwm->blink_off_duration);
पूर्ण

अटल व्योम __maybe_unused mvebu_pwm_resume(काष्ठा mvebu_gpio_chip *mvchip)
अणु
	काष्ठा mvebu_pwm *mvpwm = mvchip->mvpwm;

	regmap_ग_लिखो(mvchip->regs, GPIO_BLINK_CNT_SELECT_OFF + mvchip->offset,
		     mvpwm->blink_select);
	regmap_ग_लिखो(mvpwm->regs, mvebu_pwmreg_blink_on_duration(mvpwm),
		     mvpwm->blink_on_duration);
	regmap_ग_लिखो(mvpwm->regs, mvebu_pwmreg_blink_off_duration(mvpwm),
		     mvpwm->blink_off_duration);
पूर्ण

अटल पूर्णांक mvebu_pwm_probe(काष्ठा platक्रमm_device *pdev,
			   काष्ठा mvebu_gpio_chip *mvchip,
			   पूर्णांक id)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा mvebu_pwm *mvpwm;
	व्योम __iomem *base;
	u32 offset;
	u32 set;

	अगर (of_device_is_compatible(mvchip->chip.of_node,
				    "marvell,armada-370-gpio")) अणु
		/*
		 * There are only two sets of PWM configuration रेजिस्टरs क्रम
		 * all the GPIO lines on those SoCs which this driver reserves
		 * क्रम the first two GPIO chips. So अगर the resource is missing
		 * we can't treat it as an error.
		 */
		अगर (!platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "pwm"))
			वापस 0;
		offset = 0;
	पूर्ण अन्यथा अगर (mvchip->soc_variant == MVEBU_GPIO_SOC_VARIANT_A8K) अणु
		पूर्णांक ret = of_property_पढ़ो_u32(dev->of_node,
					       "marvell,pwm-offset", &offset);
		अगर (ret < 0)
			वापस 0;
	पूर्ण अन्यथा अणु
		वापस 0;
	पूर्ण

	अगर (IS_ERR(mvchip->clk))
		वापस PTR_ERR(mvchip->clk);

	mvpwm = devm_kzalloc(dev, माप(काष्ठा mvebu_pwm), GFP_KERNEL);
	अगर (!mvpwm)
		वापस -ENOMEM;
	mvchip->mvpwm = mvpwm;
	mvpwm->mvchip = mvchip;
	mvpwm->offset = offset;

	अगर (mvchip->soc_variant == MVEBU_GPIO_SOC_VARIANT_A8K) अणु
		mvpwm->regs = mvchip->regs;

		चयन (mvchip->offset) अणु
		हाल AP80X_GPIO0_OFF_A8K:
		हाल CP11X_GPIO0_OFF_A8K:
			/* Blink counter A */
			set = 0;
			अवरोध;
		हाल CP11X_GPIO1_OFF_A8K:
			/* Blink counter B */
			set = U32_MAX;
			mvpwm->offset += PWM_BLINK_COUNTER_B_OFF;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अणु
		base = devm_platक्रमm_ioremap_resource_byname(pdev, "pwm");
		अगर (IS_ERR(base))
			वापस PTR_ERR(base);

		mvpwm->regs = devm_regmap_init_mmio(&pdev->dev, base,
						    &mvebu_gpio_regmap_config);
		अगर (IS_ERR(mvpwm->regs))
			वापस PTR_ERR(mvpwm->regs);

		/*
		 * Use set A क्रम lines of GPIO chip with id 0, B क्रम GPIO chip
		 * with id 1. Don't allow further GPIO chips to be used क्रम PWM.
		 */
		अगर (id == 0)
			set = 0;
		अन्यथा अगर (id == 1)
			set = U32_MAX;
		अन्यथा
			वापस -EINVAL;
	पूर्ण

	regmap_ग_लिखो(mvchip->regs,
		     GPIO_BLINK_CNT_SELECT_OFF + mvchip->offset, set);

	mvpwm->clk_rate = clk_get_rate(mvchip->clk);
	अगर (!mvpwm->clk_rate) अणु
		dev_err(dev, "failed to get clock rate\n");
		वापस -EINVAL;
	पूर्ण

	mvpwm->chip.dev = dev;
	mvpwm->chip.ops = &mvebu_pwm_ops;
	mvpwm->chip.npwm = mvchip->chip.ngpio;
	/*
	 * There may alपढ़ोy be some PWM allocated, so we can't क्रमce
	 * mvpwm->chip.base to a fixed poपूर्णांक like mvchip->chip.base.
	 * So, we let pwmchip_add() करो the numbering and take the next मुक्त
	 * region.
	 */
	mvpwm->chip.base = -1;

	spin_lock_init(&mvpwm->lock);

	वापस pwmchip_add(&mvpwm->chip);
पूर्ण

#अगर_घोषित CONFIG_DEBUG_FS
#समावेश <linux/seq_file.h>

अटल व्योम mvebu_gpio_dbg_show(काष्ठा seq_file *s, काष्ठा gpio_chip *chip)
अणु
	काष्ठा mvebu_gpio_chip *mvchip = gpiochip_get_data(chip);
	u32 out, io_conf, blink, in_pol, data_in, cause, edg_msk, lvl_msk;
	स्थिर अक्षर *label;
	पूर्णांक i;

	regmap_पढ़ो(mvchip->regs, GPIO_OUT_OFF + mvchip->offset, &out);
	regmap_पढ़ो(mvchip->regs, GPIO_IO_CONF_OFF + mvchip->offset, &io_conf);
	regmap_पढ़ो(mvchip->regs, GPIO_BLINK_EN_OFF + mvchip->offset, &blink);
	regmap_पढ़ो(mvchip->regs, GPIO_IN_POL_OFF + mvchip->offset, &in_pol);
	regmap_पढ़ो(mvchip->regs, GPIO_DATA_IN_OFF + mvchip->offset, &data_in);
	cause	= mvebu_gpio_पढ़ो_edge_cause(mvchip);
	edg_msk	= mvebu_gpio_पढ़ो_edge_mask(mvchip);
	lvl_msk	= mvebu_gpio_पढ़ो_level_mask(mvchip);

	क्रम_each_requested_gpio(chip, i, label) अणु
		u32 msk;
		bool is_out;

		msk = BIT(i);
		is_out = !(io_conf & msk);

		seq_म_लिखो(s, " gpio-%-3d (%-20.20s)", chip->base + i, label);

		अगर (is_out) अणु
			seq_म_लिखो(s, " out %s %s\n",
				   out & msk ? "hi" : "lo",
				   blink & msk ? "(blink )" : "");
			जारी;
		पूर्ण

		seq_म_लिखो(s, " in  %s (act %s) - IRQ",
			   (data_in ^ in_pol) & msk  ? "hi" : "lo",
			   in_pol & msk ? "lo" : "hi");
		अगर (!((edg_msk | lvl_msk) & msk)) अणु
			seq_माला_दो(s, " disabled\n");
			जारी;
		पूर्ण
		अगर (edg_msk & msk)
			seq_माला_दो(s, " edge ");
		अगर (lvl_msk & msk)
			seq_माला_दो(s, " level");
		seq_म_लिखो(s, " (%s)\n", cause & msk ? "pending" : "clear  ");
	पूर्ण
पूर्ण
#अन्यथा
#घोषणा mvebu_gpio_dbg_show शून्य
#पूर्ण_अगर

अटल स्थिर काष्ठा of_device_id mvebu_gpio_of_match[] = अणु
	अणु
		.compatible = "marvell,orion-gpio",
		.data	    = (व्योम *) MVEBU_GPIO_SOC_VARIANT_ORION,
	पूर्ण,
	अणु
		.compatible = "marvell,mv78200-gpio",
		.data	    = (व्योम *) MVEBU_GPIO_SOC_VARIANT_MV78200,
	पूर्ण,
	अणु
		.compatible = "marvell,armadaxp-gpio",
		.data	    = (व्योम *) MVEBU_GPIO_SOC_VARIANT_ARMADAXP,
	पूर्ण,
	अणु
		.compatible = "marvell,armada-370-gpio",
		.data	    = (व्योम *) MVEBU_GPIO_SOC_VARIANT_ORION,
	पूर्ण,
	अणु
		.compatible = "marvell,armada-8k-gpio",
		.data       = (व्योम *) MVEBU_GPIO_SOC_VARIANT_A8K,
	पूर्ण,
	अणु
		/* sentinel */
	पूर्ण,
पूर्ण;

अटल पूर्णांक mvebu_gpio_suspend(काष्ठा platक्रमm_device *pdev, pm_message_t state)
अणु
	काष्ठा mvebu_gpio_chip *mvchip = platक्रमm_get_drvdata(pdev);
	पूर्णांक i;

	regmap_पढ़ो(mvchip->regs, GPIO_OUT_OFF + mvchip->offset,
		    &mvchip->out_reg);
	regmap_पढ़ो(mvchip->regs, GPIO_IO_CONF_OFF + mvchip->offset,
		    &mvchip->io_conf_reg);
	regmap_पढ़ो(mvchip->regs, GPIO_BLINK_EN_OFF + mvchip->offset,
		    &mvchip->blink_en_reg);
	regmap_पढ़ो(mvchip->regs, GPIO_IN_POL_OFF + mvchip->offset,
		    &mvchip->in_pol_reg);

	चयन (mvchip->soc_variant) अणु
	हाल MVEBU_GPIO_SOC_VARIANT_ORION:
	हाल MVEBU_GPIO_SOC_VARIANT_A8K:
		regmap_पढ़ो(mvchip->regs, GPIO_EDGE_MASK_OFF + mvchip->offset,
			    &mvchip->edge_mask_regs[0]);
		regmap_पढ़ो(mvchip->regs, GPIO_LEVEL_MASK_OFF + mvchip->offset,
			    &mvchip->level_mask_regs[0]);
		अवरोध;
	हाल MVEBU_GPIO_SOC_VARIANT_MV78200:
		क्रम (i = 0; i < 2; i++) अणु
			regmap_पढ़ो(mvchip->regs,
				    GPIO_EDGE_MASK_MV78200_OFF(i),
				    &mvchip->edge_mask_regs[i]);
			regmap_पढ़ो(mvchip->regs,
				    GPIO_LEVEL_MASK_MV78200_OFF(i),
				    &mvchip->level_mask_regs[i]);
		पूर्ण
		अवरोध;
	हाल MVEBU_GPIO_SOC_VARIANT_ARMADAXP:
		क्रम (i = 0; i < 4; i++) अणु
			regmap_पढ़ो(mvchip->regs,
				    GPIO_EDGE_MASK_ARMADAXP_OFF(i),
				    &mvchip->edge_mask_regs[i]);
			regmap_पढ़ो(mvchip->regs,
				    GPIO_LEVEL_MASK_ARMADAXP_OFF(i),
				    &mvchip->level_mask_regs[i]);
		पूर्ण
		अवरोध;
	शेष:
		BUG();
	पूर्ण

	अगर (IS_ENABLED(CONFIG_PWM))
		mvebu_pwm_suspend(mvchip);

	वापस 0;
पूर्ण

अटल पूर्णांक mvebu_gpio_resume(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mvebu_gpio_chip *mvchip = platक्रमm_get_drvdata(pdev);
	पूर्णांक i;

	regmap_ग_लिखो(mvchip->regs, GPIO_OUT_OFF + mvchip->offset,
		     mvchip->out_reg);
	regmap_ग_लिखो(mvchip->regs, GPIO_IO_CONF_OFF + mvchip->offset,
		     mvchip->io_conf_reg);
	regmap_ग_लिखो(mvchip->regs, GPIO_BLINK_EN_OFF + mvchip->offset,
		     mvchip->blink_en_reg);
	regmap_ग_लिखो(mvchip->regs, GPIO_IN_POL_OFF + mvchip->offset,
		     mvchip->in_pol_reg);

	चयन (mvchip->soc_variant) अणु
	हाल MVEBU_GPIO_SOC_VARIANT_ORION:
	हाल MVEBU_GPIO_SOC_VARIANT_A8K:
		regmap_ग_लिखो(mvchip->regs, GPIO_EDGE_MASK_OFF + mvchip->offset,
			     mvchip->edge_mask_regs[0]);
		regmap_ग_लिखो(mvchip->regs, GPIO_LEVEL_MASK_OFF + mvchip->offset,
			     mvchip->level_mask_regs[0]);
		अवरोध;
	हाल MVEBU_GPIO_SOC_VARIANT_MV78200:
		क्रम (i = 0; i < 2; i++) अणु
			regmap_ग_लिखो(mvchip->regs,
				     GPIO_EDGE_MASK_MV78200_OFF(i),
				     mvchip->edge_mask_regs[i]);
			regmap_ग_लिखो(mvchip->regs,
				     GPIO_LEVEL_MASK_MV78200_OFF(i),
				     mvchip->level_mask_regs[i]);
		पूर्ण
		अवरोध;
	हाल MVEBU_GPIO_SOC_VARIANT_ARMADAXP:
		क्रम (i = 0; i < 4; i++) अणु
			regmap_ग_लिखो(mvchip->regs,
				     GPIO_EDGE_MASK_ARMADAXP_OFF(i),
				     mvchip->edge_mask_regs[i]);
			regmap_ग_लिखो(mvchip->regs,
				     GPIO_LEVEL_MASK_ARMADAXP_OFF(i),
				     mvchip->level_mask_regs[i]);
		पूर्ण
		अवरोध;
	शेष:
		BUG();
	पूर्ण

	अगर (IS_ENABLED(CONFIG_PWM))
		mvebu_pwm_resume(mvchip);

	वापस 0;
पूर्ण

अटल पूर्णांक mvebu_gpio_probe_raw(काष्ठा platक्रमm_device *pdev,
				काष्ठा mvebu_gpio_chip *mvchip)
अणु
	व्योम __iomem *base;

	base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(base))
		वापस PTR_ERR(base);

	mvchip->regs = devm_regmap_init_mmio(&pdev->dev, base,
					     &mvebu_gpio_regmap_config);
	अगर (IS_ERR(mvchip->regs))
		वापस PTR_ERR(mvchip->regs);

	/*
	 * For the legacy SoCs, the regmap directly maps to the GPIO
	 * रेजिस्टरs, so no offset is needed.
	 */
	mvchip->offset = 0;

	/*
	 * The Armada XP has a second range of रेजिस्टरs क्रम the
	 * per-CPU रेजिस्टरs
	 */
	अगर (mvchip->soc_variant == MVEBU_GPIO_SOC_VARIANT_ARMADAXP) अणु
		base = devm_platक्रमm_ioremap_resource(pdev, 1);
		अगर (IS_ERR(base))
			वापस PTR_ERR(base);

		mvchip->percpu_regs =
			devm_regmap_init_mmio(&pdev->dev, base,
					      &mvebu_gpio_regmap_config);
		अगर (IS_ERR(mvchip->percpu_regs))
			वापस PTR_ERR(mvchip->percpu_regs);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mvebu_gpio_probe_syscon(काष्ठा platक्रमm_device *pdev,
				   काष्ठा mvebu_gpio_chip *mvchip)
अणु
	mvchip->regs = syscon_node_to_regmap(pdev->dev.parent->of_node);
	अगर (IS_ERR(mvchip->regs))
		वापस PTR_ERR(mvchip->regs);

	अगर (of_property_पढ़ो_u32(pdev->dev.of_node, "offset", &mvchip->offset))
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक mvebu_gpio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mvebu_gpio_chip *mvchip;
	स्थिर काष्ठा of_device_id *match;
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा irq_chip_generic *gc;
	काष्ठा irq_chip_type *ct;
	अचिन्हित पूर्णांक ngpios;
	bool have_irqs;
	पूर्णांक soc_variant;
	पूर्णांक i, cpu, id;
	पूर्णांक err;

	match = of_match_device(mvebu_gpio_of_match, &pdev->dev);
	अगर (match)
		soc_variant = (अचिन्हित दीर्घ) match->data;
	अन्यथा
		soc_variant = MVEBU_GPIO_SOC_VARIANT_ORION;

	/* Some gpio controllers करो not provide irq support */
	err = platक्रमm_irq_count(pdev);
	अगर (err < 0)
		वापस err;

	have_irqs = err != 0;

	mvchip = devm_kzalloc(&pdev->dev, माप(काष्ठा mvebu_gpio_chip),
			      GFP_KERNEL);
	अगर (!mvchip)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, mvchip);

	अगर (of_property_पढ़ो_u32(pdev->dev.of_node, "ngpios", &ngpios)) अणु
		dev_err(&pdev->dev, "Missing ngpios OF property\n");
		वापस -ENODEV;
	पूर्ण

	id = of_alias_get_id(pdev->dev.of_node, "gpio");
	अगर (id < 0) अणु
		dev_err(&pdev->dev, "Couldn't get OF id\n");
		वापस id;
	पूर्ण

	mvchip->clk = devm_clk_get(&pdev->dev, शून्य);
	/* Not all SoCs require a घड़ी.*/
	अगर (!IS_ERR(mvchip->clk))
		clk_prepare_enable(mvchip->clk);

	mvchip->soc_variant = soc_variant;
	mvchip->chip.label = dev_name(&pdev->dev);
	mvchip->chip.parent = &pdev->dev;
	mvchip->chip.request = gpiochip_generic_request;
	mvchip->chip.मुक्त = gpiochip_generic_मुक्त;
	mvchip->chip.get_direction = mvebu_gpio_get_direction;
	mvchip->chip.direction_input = mvebu_gpio_direction_input;
	mvchip->chip.get = mvebu_gpio_get;
	mvchip->chip.direction_output = mvebu_gpio_direction_output;
	mvchip->chip.set = mvebu_gpio_set;
	अगर (have_irqs)
		mvchip->chip.to_irq = mvebu_gpio_to_irq;
	mvchip->chip.base = id * MVEBU_MAX_GPIO_PER_BANK;
	mvchip->chip.ngpio = ngpios;
	mvchip->chip.can_sleep = false;
	mvchip->chip.of_node = np;
	mvchip->chip.dbg_show = mvebu_gpio_dbg_show;

	अगर (soc_variant == MVEBU_GPIO_SOC_VARIANT_A8K)
		err = mvebu_gpio_probe_syscon(pdev, mvchip);
	अन्यथा
		err = mvebu_gpio_probe_raw(pdev, mvchip);

	अगर (err)
		वापस err;

	/*
	 * Mask and clear GPIO पूर्णांकerrupts.
	 */
	चयन (soc_variant) अणु
	हाल MVEBU_GPIO_SOC_VARIANT_ORION:
	हाल MVEBU_GPIO_SOC_VARIANT_A8K:
		regmap_ग_लिखो(mvchip->regs,
			     GPIO_EDGE_CAUSE_OFF + mvchip->offset, 0);
		regmap_ग_लिखो(mvchip->regs,
			     GPIO_EDGE_MASK_OFF + mvchip->offset, 0);
		regmap_ग_लिखो(mvchip->regs,
			     GPIO_LEVEL_MASK_OFF + mvchip->offset, 0);
		अवरोध;
	हाल MVEBU_GPIO_SOC_VARIANT_MV78200:
		regmap_ग_लिखो(mvchip->regs, GPIO_EDGE_CAUSE_OFF, 0);
		क्रम (cpu = 0; cpu < 2; cpu++) अणु
			regmap_ग_लिखो(mvchip->regs,
				     GPIO_EDGE_MASK_MV78200_OFF(cpu), 0);
			regmap_ग_लिखो(mvchip->regs,
				     GPIO_LEVEL_MASK_MV78200_OFF(cpu), 0);
		पूर्ण
		अवरोध;
	हाल MVEBU_GPIO_SOC_VARIANT_ARMADAXP:
		regmap_ग_लिखो(mvchip->regs, GPIO_EDGE_CAUSE_OFF, 0);
		regmap_ग_लिखो(mvchip->regs, GPIO_EDGE_MASK_OFF, 0);
		regmap_ग_लिखो(mvchip->regs, GPIO_LEVEL_MASK_OFF, 0);
		क्रम (cpu = 0; cpu < 4; cpu++) अणु
			regmap_ग_लिखो(mvchip->percpu_regs,
				     GPIO_EDGE_CAUSE_ARMADAXP_OFF(cpu), 0);
			regmap_ग_लिखो(mvchip->percpu_regs,
				     GPIO_EDGE_MASK_ARMADAXP_OFF(cpu), 0);
			regmap_ग_लिखो(mvchip->percpu_regs,
				     GPIO_LEVEL_MASK_ARMADAXP_OFF(cpu), 0);
		पूर्ण
		अवरोध;
	शेष:
		BUG();
	पूर्ण

	devm_gpiochip_add_data(&pdev->dev, &mvchip->chip, mvchip);

	/* Some MVEBU SoCs have simple PWM support क्रम GPIO lines */
	अगर (IS_ENABLED(CONFIG_PWM)) अणु
		err = mvebu_pwm_probe(pdev, mvchip, id);
		अगर (err)
			वापस err;
	पूर्ण

	/* Some gpio controllers करो not provide irq support */
	अगर (!have_irqs)
		वापस 0;

	mvchip->करोमुख्य =
	    irq_करोमुख्य_add_linear(np, ngpios, &irq_generic_chip_ops, शून्य);
	अगर (!mvchip->करोमुख्य) अणु
		dev_err(&pdev->dev, "couldn't allocate irq domain %s (DT).\n",
			mvchip->chip.label);
		err = -ENODEV;
		जाओ err_pwm;
	पूर्ण

	err = irq_alloc_करोमुख्य_generic_chips(
	    mvchip->करोमुख्य, ngpios, 2, np->name, handle_level_irq,
	    IRQ_NOREQUEST | IRQ_NOPROBE | IRQ_LEVEL, 0, 0);
	अगर (err) अणु
		dev_err(&pdev->dev, "couldn't allocate irq chips %s (DT).\n",
			mvchip->chip.label);
		जाओ err_करोमुख्य;
	पूर्ण

	/*
	 * NOTE: The common accessors cannot be used because of the percpu
	 * access to the mask रेजिस्टरs
	 */
	gc = irq_get_करोमुख्य_generic_chip(mvchip->करोमुख्य, 0);
	gc->निजी = mvchip;
	ct = &gc->chip_types[0];
	ct->type = IRQ_TYPE_LEVEL_HIGH | IRQ_TYPE_LEVEL_LOW;
	ct->chip.irq_mask = mvebu_gpio_level_irq_mask;
	ct->chip.irq_unmask = mvebu_gpio_level_irq_unmask;
	ct->chip.irq_set_type = mvebu_gpio_irq_set_type;
	ct->chip.name = mvchip->chip.label;

	ct = &gc->chip_types[1];
	ct->type = IRQ_TYPE_EDGE_RISING | IRQ_TYPE_EDGE_FALLING;
	ct->chip.irq_ack = mvebu_gpio_irq_ack;
	ct->chip.irq_mask = mvebu_gpio_edge_irq_mask;
	ct->chip.irq_unmask = mvebu_gpio_edge_irq_unmask;
	ct->chip.irq_set_type = mvebu_gpio_irq_set_type;
	ct->handler = handle_edge_irq;
	ct->chip.name = mvchip->chip.label;

	/*
	 * Setup the पूर्णांकerrupt handlers. Each chip can have up to 4
	 * पूर्णांकerrupt handlers, with each handler dealing with 8 GPIO
	 * pins.
	 */
	क्रम (i = 0; i < 4; i++) अणु
		पूर्णांक irq = platक्रमm_get_irq_optional(pdev, i);

		अगर (irq < 0)
			जारी;
		irq_set_chained_handler_and_data(irq, mvebu_gpio_irq_handler,
						 mvchip);
	पूर्ण

	वापस 0;

err_करोमुख्य:
	irq_करोमुख्य_हटाओ(mvchip->करोमुख्य);
err_pwm:
	pwmchip_हटाओ(&mvchip->mvpwm->chip);

	वापस err;
पूर्ण

अटल काष्ठा platक्रमm_driver mvebu_gpio_driver = अणु
	.driver		= अणु
		.name		= "mvebu-gpio",
		.of_match_table = mvebu_gpio_of_match,
	पूर्ण,
	.probe		= mvebu_gpio_probe,
	.suspend        = mvebu_gpio_suspend,
	.resume         = mvebu_gpio_resume,
पूर्ण;
builtin_platक्रमm_driver(mvebu_gpio_driver);
