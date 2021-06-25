<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2011-2012 Avionic Design GmbH
 */

#समावेश <linux/gpio/driver.h>
#समावेश <linux/i2c.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/slab.h>

#घोषणा GPIO_DDR(gpio) (0x00 << (gpio)->reg_shअगरt)
#घोषणा GPIO_PLR(gpio) (0x01 << (gpio)->reg_shअगरt)
#घोषणा GPIO_IER(gpio) (0x02 << (gpio)->reg_shअगरt)
#घोषणा GPIO_ISR(gpio) (0x03 << (gpio)->reg_shअगरt)
#घोषणा GPIO_PTR(gpio) (0x04 << (gpio)->reg_shअगरt)

काष्ठा adnp अणु
	काष्ठा i2c_client *client;
	काष्ठा gpio_chip gpio;
	अचिन्हित पूर्णांक reg_shअगरt;

	काष्ठा mutex i2c_lock;
	काष्ठा mutex irq_lock;

	u8 *irq_enable;
	u8 *irq_level;
	u8 *irq_rise;
	u8 *irq_fall;
	u8 *irq_high;
	u8 *irq_low;
पूर्ण;

अटल पूर्णांक adnp_पढ़ो(काष्ठा adnp *adnp, अचिन्हित offset, uपूर्णांक8_t *value)
अणु
	पूर्णांक err;

	err = i2c_smbus_पढ़ो_byte_data(adnp->client, offset);
	अगर (err < 0) अणु
		dev_err(adnp->gpio.parent, "%s failed: %d\n",
			"i2c_smbus_read_byte_data()", err);
		वापस err;
	पूर्ण

	*value = err;
	वापस 0;
पूर्ण

अटल पूर्णांक adnp_ग_लिखो(काष्ठा adnp *adnp, अचिन्हित offset, uपूर्णांक8_t value)
अणु
	पूर्णांक err;

	err = i2c_smbus_ग_लिखो_byte_data(adnp->client, offset, value);
	अगर (err < 0) अणु
		dev_err(adnp->gpio.parent, "%s failed: %d\n",
			"i2c_smbus_write_byte_data()", err);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक adnp_gpio_get(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	काष्ठा adnp *adnp = gpiochip_get_data(chip);
	अचिन्हित पूर्णांक reg = offset >> adnp->reg_shअगरt;
	अचिन्हित पूर्णांक pos = offset & 7;
	u8 value;
	पूर्णांक err;

	err = adnp_पढ़ो(adnp, GPIO_PLR(adnp) + reg, &value);
	अगर (err < 0)
		वापस err;

	वापस (value & BIT(pos)) ? 1 : 0;
पूर्ण

अटल व्योम __adnp_gpio_set(काष्ठा adnp *adnp, अचिन्हित offset, पूर्णांक value)
अणु
	अचिन्हित पूर्णांक reg = offset >> adnp->reg_shअगरt;
	अचिन्हित पूर्णांक pos = offset & 7;
	पूर्णांक err;
	u8 val;

	err = adnp_पढ़ो(adnp, GPIO_PLR(adnp) + reg, &val);
	अगर (err < 0)
		वापस;

	अगर (value)
		val |= BIT(pos);
	अन्यथा
		val &= ~BIT(pos);

	adnp_ग_लिखो(adnp, GPIO_PLR(adnp) + reg, val);
पूर्ण

अटल व्योम adnp_gpio_set(काष्ठा gpio_chip *chip, अचिन्हित offset, पूर्णांक value)
अणु
	काष्ठा adnp *adnp = gpiochip_get_data(chip);

	mutex_lock(&adnp->i2c_lock);
	__adnp_gpio_set(adnp, offset, value);
	mutex_unlock(&adnp->i2c_lock);
पूर्ण

अटल पूर्णांक adnp_gpio_direction_input(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	काष्ठा adnp *adnp = gpiochip_get_data(chip);
	अचिन्हित पूर्णांक reg = offset >> adnp->reg_shअगरt;
	अचिन्हित पूर्णांक pos = offset & 7;
	u8 value;
	पूर्णांक err;

	mutex_lock(&adnp->i2c_lock);

	err = adnp_पढ़ो(adnp, GPIO_DDR(adnp) + reg, &value);
	अगर (err < 0)
		जाओ out;

	value &= ~BIT(pos);

	err = adnp_ग_लिखो(adnp, GPIO_DDR(adnp) + reg, value);
	अगर (err < 0)
		जाओ out;

	err = adnp_पढ़ो(adnp, GPIO_DDR(adnp) + reg, &value);
	अगर (err < 0)
		जाओ out;

	अगर (value & BIT(pos)) अणु
		err = -EPERM;
		जाओ out;
	पूर्ण

	err = 0;

out:
	mutex_unlock(&adnp->i2c_lock);
	वापस err;
पूर्ण

अटल पूर्णांक adnp_gpio_direction_output(काष्ठा gpio_chip *chip, अचिन्हित offset,
				      पूर्णांक value)
अणु
	काष्ठा adnp *adnp = gpiochip_get_data(chip);
	अचिन्हित पूर्णांक reg = offset >> adnp->reg_shअगरt;
	अचिन्हित पूर्णांक pos = offset & 7;
	पूर्णांक err;
	u8 val;

	mutex_lock(&adnp->i2c_lock);

	err = adnp_पढ़ो(adnp, GPIO_DDR(adnp) + reg, &val);
	अगर (err < 0)
		जाओ out;

	val |= BIT(pos);

	err = adnp_ग_लिखो(adnp, GPIO_DDR(adnp) + reg, val);
	अगर (err < 0)
		जाओ out;

	err = adnp_पढ़ो(adnp, GPIO_DDR(adnp) + reg, &val);
	अगर (err < 0)
		जाओ out;

	अगर (!(val & BIT(pos))) अणु
		err = -EPERM;
		जाओ out;
	पूर्ण

	__adnp_gpio_set(adnp, offset, value);
	err = 0;

out:
	mutex_unlock(&adnp->i2c_lock);
	वापस err;
पूर्ण

अटल व्योम adnp_gpio_dbg_show(काष्ठा seq_file *s, काष्ठा gpio_chip *chip)
अणु
	काष्ठा adnp *adnp = gpiochip_get_data(chip);
	अचिन्हित पूर्णांक num_regs = 1 << adnp->reg_shअगरt, i, j;
	पूर्णांक err;

	क्रम (i = 0; i < num_regs; i++) अणु
		u8 ddr, plr, ier, isr;

		mutex_lock(&adnp->i2c_lock);

		err = adnp_पढ़ो(adnp, GPIO_DDR(adnp) + i, &ddr);
		अगर (err < 0)
			जाओ unlock;

		err = adnp_पढ़ो(adnp, GPIO_PLR(adnp) + i, &plr);
		अगर (err < 0)
			जाओ unlock;

		err = adnp_पढ़ो(adnp, GPIO_IER(adnp) + i, &ier);
		अगर (err < 0)
			जाओ unlock;

		err = adnp_पढ़ो(adnp, GPIO_ISR(adnp) + i, &isr);
		अगर (err < 0)
			जाओ unlock;

		mutex_unlock(&adnp->i2c_lock);

		क्रम (j = 0; j < 8; j++) अणु
			अचिन्हित पूर्णांक bit = (i << adnp->reg_shअगरt) + j;
			स्थिर अक्षर *direction = "input ";
			स्थिर अक्षर *level = "low ";
			स्थिर अक्षर *पूर्णांकerrupt = "disabled";
			स्थिर अक्षर *pending = "";

			अगर (ddr & BIT(j))
				direction = "output";

			अगर (plr & BIT(j))
				level = "high";

			अगर (ier & BIT(j))
				पूर्णांकerrupt = "enabled ";

			अगर (isr & BIT(j))
				pending = "pending";

			seq_म_लिखो(s, "%2u: %s %s IRQ %s %s\n", bit,
				   direction, level, पूर्णांकerrupt, pending);
		पूर्ण
	पूर्ण

	वापस;

unlock:
	mutex_unlock(&adnp->i2c_lock);
पूर्ण

अटल irqवापस_t adnp_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा adnp *adnp = data;
	अचिन्हित पूर्णांक num_regs, i;

	num_regs = 1 << adnp->reg_shअगरt;

	क्रम (i = 0; i < num_regs; i++) अणु
		अचिन्हित पूर्णांक base = i << adnp->reg_shअगरt, bit;
		u8 changed, level, isr, ier;
		अचिन्हित दीर्घ pending;
		पूर्णांक err;

		mutex_lock(&adnp->i2c_lock);

		err = adnp_पढ़ो(adnp, GPIO_PLR(adnp) + i, &level);
		अगर (err < 0) अणु
			mutex_unlock(&adnp->i2c_lock);
			जारी;
		पूर्ण

		err = adnp_पढ़ो(adnp, GPIO_ISR(adnp) + i, &isr);
		अगर (err < 0) अणु
			mutex_unlock(&adnp->i2c_lock);
			जारी;
		पूर्ण

		err = adnp_पढ़ो(adnp, GPIO_IER(adnp) + i, &ier);
		अगर (err < 0) अणु
			mutex_unlock(&adnp->i2c_lock);
			जारी;
		पूर्ण

		mutex_unlock(&adnp->i2c_lock);

		/* determine pins that changed levels */
		changed = level ^ adnp->irq_level[i];

		/* compute edge-triggered पूर्णांकerrupts */
		pending = changed & ((adnp->irq_fall[i] & ~level) |
				     (adnp->irq_rise[i] & level));

		/* add in level-triggered पूर्णांकerrupts */
		pending |= (adnp->irq_high[i] & level) |
			   (adnp->irq_low[i] & ~level);

		/* mask out non-pending and disabled पूर्णांकerrupts */
		pending &= isr & ier;

		क्रम_each_set_bit(bit, &pending, 8) अणु
			अचिन्हित पूर्णांक child_irq;
			child_irq = irq_find_mapping(adnp->gpio.irq.करोमुख्य,
						     base + bit);
			handle_nested_irq(child_irq);
		पूर्ण
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम adnp_irq_mask(काष्ठा irq_data *d)
अणु
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(d);
	काष्ठा adnp *adnp = gpiochip_get_data(gc);
	अचिन्हित पूर्णांक reg = d->hwirq >> adnp->reg_shअगरt;
	अचिन्हित पूर्णांक pos = d->hwirq & 7;

	adnp->irq_enable[reg] &= ~BIT(pos);
पूर्ण

अटल व्योम adnp_irq_unmask(काष्ठा irq_data *d)
अणु
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(d);
	काष्ठा adnp *adnp = gpiochip_get_data(gc);
	अचिन्हित पूर्णांक reg = d->hwirq >> adnp->reg_shअगरt;
	अचिन्हित पूर्णांक pos = d->hwirq & 7;

	adnp->irq_enable[reg] |= BIT(pos);
पूर्ण

अटल पूर्णांक adnp_irq_set_type(काष्ठा irq_data *d, अचिन्हित पूर्णांक type)
अणु
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(d);
	काष्ठा adnp *adnp = gpiochip_get_data(gc);
	अचिन्हित पूर्णांक reg = d->hwirq >> adnp->reg_shअगरt;
	अचिन्हित पूर्णांक pos = d->hwirq & 7;

	अगर (type & IRQ_TYPE_EDGE_RISING)
		adnp->irq_rise[reg] |= BIT(pos);
	अन्यथा
		adnp->irq_rise[reg] &= ~BIT(pos);

	अगर (type & IRQ_TYPE_EDGE_FALLING)
		adnp->irq_fall[reg] |= BIT(pos);
	अन्यथा
		adnp->irq_fall[reg] &= ~BIT(pos);

	अगर (type & IRQ_TYPE_LEVEL_HIGH)
		adnp->irq_high[reg] |= BIT(pos);
	अन्यथा
		adnp->irq_high[reg] &= ~BIT(pos);

	अगर (type & IRQ_TYPE_LEVEL_LOW)
		adnp->irq_low[reg] |= BIT(pos);
	अन्यथा
		adnp->irq_low[reg] &= ~BIT(pos);

	वापस 0;
पूर्ण

अटल व्योम adnp_irq_bus_lock(काष्ठा irq_data *d)
अणु
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(d);
	काष्ठा adnp *adnp = gpiochip_get_data(gc);

	mutex_lock(&adnp->irq_lock);
पूर्ण

अटल व्योम adnp_irq_bus_unlock(काष्ठा irq_data *d)
अणु
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(d);
	काष्ठा adnp *adnp = gpiochip_get_data(gc);
	अचिन्हित पूर्णांक num_regs = 1 << adnp->reg_shअगरt, i;

	mutex_lock(&adnp->i2c_lock);

	क्रम (i = 0; i < num_regs; i++)
		adnp_ग_लिखो(adnp, GPIO_IER(adnp) + i, adnp->irq_enable[i]);

	mutex_unlock(&adnp->i2c_lock);
	mutex_unlock(&adnp->irq_lock);
पूर्ण

अटल काष्ठा irq_chip adnp_irq_chip = अणु
	.name = "gpio-adnp",
	.irq_mask = adnp_irq_mask,
	.irq_unmask = adnp_irq_unmask,
	.irq_set_type = adnp_irq_set_type,
	.irq_bus_lock = adnp_irq_bus_lock,
	.irq_bus_sync_unlock = adnp_irq_bus_unlock,
पूर्ण;

अटल पूर्णांक adnp_irq_setup(काष्ठा adnp *adnp)
अणु
	अचिन्हित पूर्णांक num_regs = 1 << adnp->reg_shअगरt, i;
	काष्ठा gpio_chip *chip = &adnp->gpio;
	पूर्णांक err;

	mutex_init(&adnp->irq_lock);

	/*
	 * Allocate memory to keep track of the current level and trigger
	 * modes of the पूर्णांकerrupts. To aव्योम multiple allocations, a single
	 * large buffer is allocated and poपूर्णांकers are setup to poपूर्णांक at the
	 * corresponding offsets. For consistency, the layout of the buffer
	 * is chosen to match the रेजिस्टर layout of the hardware in that
	 * each segment contains the corresponding bits क्रम all पूर्णांकerrupts.
	 */
	adnp->irq_enable = devm_kसुस्मृति(chip->parent, num_regs, 6,
					GFP_KERNEL);
	अगर (!adnp->irq_enable)
		वापस -ENOMEM;

	adnp->irq_level = adnp->irq_enable + (num_regs * 1);
	adnp->irq_rise = adnp->irq_enable + (num_regs * 2);
	adnp->irq_fall = adnp->irq_enable + (num_regs * 3);
	adnp->irq_high = adnp->irq_enable + (num_regs * 4);
	adnp->irq_low = adnp->irq_enable + (num_regs * 5);

	क्रम (i = 0; i < num_regs; i++) अणु
		/*
		 * Read the initial level of all pins to allow the emulation
		 * of edge triggered पूर्णांकerrupts.
		 */
		err = adnp_पढ़ो(adnp, GPIO_PLR(adnp) + i, &adnp->irq_level[i]);
		अगर (err < 0)
			वापस err;

		/* disable all पूर्णांकerrupts */
		err = adnp_ग_लिखो(adnp, GPIO_IER(adnp) + i, 0);
		अगर (err < 0)
			वापस err;

		adnp->irq_enable[i] = 0x00;
	पूर्ण

	err = devm_request_thपढ़ोed_irq(chip->parent, adnp->client->irq,
					शून्य, adnp_irq,
					IRQF_TRIGGER_RISING | IRQF_ONESHOT,
					dev_name(chip->parent), adnp);
	अगर (err != 0) अणु
		dev_err(chip->parent, "can't request IRQ#%d: %d\n",
			adnp->client->irq, err);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक adnp_gpio_setup(काष्ठा adnp *adnp, अचिन्हित पूर्णांक num_gpios,
			   bool is_irq_controller)
अणु
	काष्ठा gpio_chip *chip = &adnp->gpio;
	पूर्णांक err;

	adnp->reg_shअगरt = get_count_order(num_gpios) - 3;

	chip->direction_input = adnp_gpio_direction_input;
	chip->direction_output = adnp_gpio_direction_output;
	chip->get = adnp_gpio_get;
	chip->set = adnp_gpio_set;
	chip->can_sleep = true;

	अगर (IS_ENABLED(CONFIG_DEBUG_FS))
		chip->dbg_show = adnp_gpio_dbg_show;

	chip->base = -1;
	chip->ngpio = num_gpios;
	chip->label = adnp->client->name;
	chip->parent = &adnp->client->dev;
	chip->of_node = chip->parent->of_node;
	chip->owner = THIS_MODULE;

	अगर (is_irq_controller) अणु
		काष्ठा gpio_irq_chip *girq;

		err = adnp_irq_setup(adnp);
		अगर (err)
			वापस err;

		girq = &chip->irq;
		girq->chip = &adnp_irq_chip;
		/* This will let us handle the parent IRQ in the driver */
		girq->parent_handler = शून्य;
		girq->num_parents = 0;
		girq->parents = शून्य;
		girq->शेष_type = IRQ_TYPE_NONE;
		girq->handler = handle_simple_irq;
		girq->thपढ़ोed = true;
	पूर्ण

	err = devm_gpiochip_add_data(&adnp->client->dev, chip, adnp);
	अगर (err)
		वापस err;

	वापस 0;
पूर्ण

अटल पूर्णांक adnp_i2c_probe(काष्ठा i2c_client *client,
				    स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा device_node *np = client->dev.of_node;
	काष्ठा adnp *adnp;
	u32 num_gpios;
	पूर्णांक err;

	err = of_property_पढ़ो_u32(np, "nr-gpios", &num_gpios);
	अगर (err < 0)
		वापस err;

	client->irq = irq_of_parse_and_map(np, 0);
	अगर (!client->irq)
		वापस -EPROBE_DEFER;

	adnp = devm_kzalloc(&client->dev, माप(*adnp), GFP_KERNEL);
	अगर (!adnp)
		वापस -ENOMEM;

	mutex_init(&adnp->i2c_lock);
	adnp->client = client;

	err = adnp_gpio_setup(adnp, num_gpios,
			of_property_पढ़ो_bool(np, "interrupt-controller"));
	अगर (err)
		वापस err;

	i2c_set_clientdata(client, adnp);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id adnp_i2c_id[] = अणु
	अणु "gpio-adnp" पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(i2c, adnp_i2c_id);

अटल स्थिर काष्ठा of_device_id adnp_of_match[] = अणु
	अणु .compatible = "ad,gpio-adnp", पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, adnp_of_match);

अटल काष्ठा i2c_driver adnp_i2c_driver = अणु
	.driver = अणु
		.name = "gpio-adnp",
		.of_match_table = adnp_of_match,
	पूर्ण,
	.probe = adnp_i2c_probe,
	.id_table = adnp_i2c_id,
पूर्ण;
module_i2c_driver(adnp_i2c_driver);

MODULE_DESCRIPTION("Avionic Design N-bit GPIO expander");
MODULE_AUTHOR("Thierry Reding <thierry.reding@avionic-design.de>");
MODULE_LICENSE("GPL");
