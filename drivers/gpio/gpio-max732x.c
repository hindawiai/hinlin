<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  MAX732x I2C Port Expander with 8/16 I/O
 *
 *  Copyright (C) 2007 Marvell International Ltd.
 *  Copyright (C) 2008 Jack Ren <jack.ren@marvell.com>
 *  Copyright (C) 2008 Eric Miao <eric.miao@marvell.com>
 *  Copyright (C) 2015 Linus Walleij <linus.walleij@linaro.org>
 *
 *  Derived from drivers/gpio/pca953x.c
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/i2c.h>
#समावेश <linux/platक्रमm_data/max732x.h>
#समावेश <linux/of.h>


/*
 * Each port of MAX732x (including MAX7319) falls पूर्णांकo one of the
 * following three types:
 *
 *   - Push Pull Output
 *   - Input
 *   - Open Drain I/O
 *
 * designated by 'O', 'I' and 'P' individually according to MAXIM's
 * datasheets. 'I' and 'P' ports are पूर्णांकerrupt capables, some with
 * a dedicated पूर्णांकerrupt mask.
 *
 * There are two groups of I/O ports, each group usually includes
 * up to 8 I/O ports, and is accessed by a specअगरic I2C address:
 *
 *   - Group A : by I2C address 0b'110xxxx
 *   - Group B : by I2C address 0b'101xxxx
 *
 * where 'xxxx' is decided by the connections of pin AD2/AD0.  The
 * address used also affects the initial state of output संकेतs.
 *
 * Within each group of ports, there are five known combinations of
 * I/O ports: 4I4O, 4P4O, 8I, 8P, 8O, see the definitions below क्रम
 * the detailed organization of these ports. Only Goup A is पूर्णांकerrupt
 * capable.
 *
 * GPIO numbers start from 'gpio_base + 0' to 'gpio_base + 8/16',
 * and GPIOs from GROUP_A are numbered beक्रमe those from GROUP_B
 * (अगर there are two groups).
 *
 * NOTE: MAX7328/MAX7329 are drop-in replacements क्रम PCF8574/a, so
 * they are not supported by this driver.
 */

#घोषणा PORT_NONE	0x0	/* '/' No Port */
#घोषणा PORT_OUTPUT	0x1	/* 'O' Push-Pull, Output Only */
#घोषणा PORT_INPUT	0x2	/* 'I' Input Only */
#घोषणा PORT_OPENDRAIN	0x3	/* 'P' Open-Drain, I/O */

#घोषणा IO_4I4O		0x5AA5	/* O7 O6 I5 I4 I3 I2 O1 O0 */
#घोषणा IO_4P4O		0x5FF5	/* O7 O6 P5 P4 P3 P2 O1 O0 */
#घोषणा IO_8I		0xAAAA	/* I7 I6 I5 I4 I3 I2 I1 I0 */
#घोषणा IO_8P		0xFFFF	/* P7 P6 P5 P4 P3 P2 P1 P0 */
#घोषणा IO_8O		0x5555	/* O7 O6 O5 O4 O3 O2 O1 O0 */

#घोषणा GROUP_A(x)	((x) & 0xffff)	/* I2C Addr: 0b'110xxxx */
#घोषणा GROUP_B(x)	((x) << 16)	/* I2C Addr: 0b'101xxxx */

#घोषणा INT_NONE	0x0	/* No पूर्णांकerrupt capability */
#घोषणा INT_NO_MASK	0x1	/* Has पूर्णांकerrupts, no mask */
#घोषणा INT_INDEP_MASK	0x2	/* Has पूर्णांकerrupts, independent mask */
#घोषणा INT_MERGED_MASK 0x3	/* Has पूर्णांकerrupts, merged mask */

#घोषणा INT_CAPS(x)	(((uपूर्णांक64_t)(x)) << 32)

क्रमागत अणु
	MAX7319,
	MAX7320,
	MAX7321,
	MAX7322,
	MAX7323,
	MAX7324,
	MAX7325,
	MAX7326,
	MAX7327,
पूर्ण;

अटल uपूर्णांक64_t max732x_features[] = अणु
	[MAX7319] = GROUP_A(IO_8I) | INT_CAPS(INT_MERGED_MASK),
	[MAX7320] = GROUP_B(IO_8O),
	[MAX7321] = GROUP_A(IO_8P) | INT_CAPS(INT_NO_MASK),
	[MAX7322] = GROUP_A(IO_4I4O) | INT_CAPS(INT_MERGED_MASK),
	[MAX7323] = GROUP_A(IO_4P4O) | INT_CAPS(INT_INDEP_MASK),
	[MAX7324] = GROUP_A(IO_8I) | GROUP_B(IO_8O) | INT_CAPS(INT_MERGED_MASK),
	[MAX7325] = GROUP_A(IO_8P) | GROUP_B(IO_8O) | INT_CAPS(INT_NO_MASK),
	[MAX7326] = GROUP_A(IO_4I4O) | GROUP_B(IO_8O) | INT_CAPS(INT_MERGED_MASK),
	[MAX7327] = GROUP_A(IO_4P4O) | GROUP_B(IO_8O) | INT_CAPS(INT_NO_MASK),
पूर्ण;

अटल स्थिर काष्ठा i2c_device_id max732x_id[] = अणु
	अणु "max7319", MAX7319 पूर्ण,
	अणु "max7320", MAX7320 पूर्ण,
	अणु "max7321", MAX7321 पूर्ण,
	अणु "max7322", MAX7322 पूर्ण,
	अणु "max7323", MAX7323 पूर्ण,
	अणु "max7324", MAX7324 पूर्ण,
	अणु "max7325", MAX7325 पूर्ण,
	अणु "max7326", MAX7326 पूर्ण,
	अणु "max7327", MAX7327 पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(i2c, max732x_id);

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id max732x_of_table[] = अणु
	अणु .compatible = "maxim,max7319" पूर्ण,
	अणु .compatible = "maxim,max7320" पूर्ण,
	अणु .compatible = "maxim,max7321" पूर्ण,
	अणु .compatible = "maxim,max7322" पूर्ण,
	अणु .compatible = "maxim,max7323" पूर्ण,
	अणु .compatible = "maxim,max7324" पूर्ण,
	अणु .compatible = "maxim,max7325" पूर्ण,
	अणु .compatible = "maxim,max7326" पूर्ण,
	अणु .compatible = "maxim,max7327" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, max732x_of_table);
#पूर्ण_अगर

काष्ठा max732x_chip अणु
	काष्ठा gpio_chip gpio_chip;

	काष्ठा i2c_client *client;	/* "main" client */
	काष्ठा i2c_client *client_dummy;
	काष्ठा i2c_client *client_group_a;
	काष्ठा i2c_client *client_group_b;

	अचिन्हित पूर्णांक	mask_group_a;
	अचिन्हित पूर्णांक	dir_input;
	अचिन्हित पूर्णांक	dir_output;

	काष्ठा mutex	lock;
	uपूर्णांक8_t		reg_out[2];

#अगर_घोषित CONFIG_GPIO_MAX732X_IRQ
	काष्ठा mutex		irq_lock;
	uपूर्णांक8_t			irq_mask;
	uपूर्णांक8_t			irq_mask_cur;
	uपूर्णांक8_t			irq_trig_उठाओ;
	uपूर्णांक8_t			irq_trig_fall;
	uपूर्णांक8_t			irq_features;
#पूर्ण_अगर
पूर्ण;

अटल पूर्णांक max732x_ग_लिखोb(काष्ठा max732x_chip *chip, पूर्णांक group_a, uपूर्णांक8_t val)
अणु
	काष्ठा i2c_client *client;
	पूर्णांक ret;

	client = group_a ? chip->client_group_a : chip->client_group_b;
	ret = i2c_smbus_ग_लिखो_byte(client, val);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "failed writing\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक max732x_पढ़ोb(काष्ठा max732x_chip *chip, पूर्णांक group_a, uपूर्णांक8_t *val)
अणु
	काष्ठा i2c_client *client;
	पूर्णांक ret;

	client = group_a ? chip->client_group_a : chip->client_group_b;
	ret = i2c_smbus_पढ़ो_byte(client);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "failed reading\n");
		वापस ret;
	पूर्ण

	*val = (uपूर्णांक8_t)ret;
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक is_group_a(काष्ठा max732x_chip *chip, अचिन्हित off)
अणु
	वापस (1u << off) & chip->mask_group_a;
पूर्ण

अटल पूर्णांक max732x_gpio_get_value(काष्ठा gpio_chip *gc, अचिन्हित off)
अणु
	काष्ठा max732x_chip *chip = gpiochip_get_data(gc);
	uपूर्णांक8_t reg_val;
	पूर्णांक ret;

	ret = max732x_पढ़ोb(chip, is_group_a(chip, off), &reg_val);
	अगर (ret < 0)
		वापस ret;

	वापस !!(reg_val & (1u << (off & 0x7)));
पूर्ण

अटल व्योम max732x_gpio_set_mask(काष्ठा gpio_chip *gc, अचिन्हित off, पूर्णांक mask,
				  पूर्णांक val)
अणु
	काष्ठा max732x_chip *chip = gpiochip_get_data(gc);
	uपूर्णांक8_t reg_out;
	पूर्णांक ret;

	mutex_lock(&chip->lock);

	reg_out = (off > 7) ? chip->reg_out[1] : chip->reg_out[0];
	reg_out = (reg_out & ~mask) | (val & mask);

	ret = max732x_ग_लिखोb(chip, is_group_a(chip, off), reg_out);
	अगर (ret < 0)
		जाओ out;

	/* update the shaकरोw रेजिस्टर then */
	अगर (off > 7)
		chip->reg_out[1] = reg_out;
	अन्यथा
		chip->reg_out[0] = reg_out;
out:
	mutex_unlock(&chip->lock);
पूर्ण

अटल व्योम max732x_gpio_set_value(काष्ठा gpio_chip *gc, अचिन्हित off, पूर्णांक val)
अणु
	अचिन्हित base = off & ~0x7;
	uपूर्णांक8_t mask = 1u << (off & 0x7);

	max732x_gpio_set_mask(gc, base, mask, val << (off & 0x7));
पूर्ण

अटल व्योम max732x_gpio_set_multiple(काष्ठा gpio_chip *gc,
				      अचिन्हित दीर्घ *mask, अचिन्हित दीर्घ *bits)
अणु
	अचिन्हित mask_lo = mask[0] & 0xff;
	अचिन्हित mask_hi = (mask[0] >> 8) & 0xff;

	अगर (mask_lo)
		max732x_gpio_set_mask(gc, 0, mask_lo, bits[0] & 0xff);
	अगर (mask_hi)
		max732x_gpio_set_mask(gc, 8, mask_hi, (bits[0] >> 8) & 0xff);
पूर्ण

अटल पूर्णांक max732x_gpio_direction_input(काष्ठा gpio_chip *gc, अचिन्हित off)
अणु
	काष्ठा max732x_chip *chip = gpiochip_get_data(gc);
	अचिन्हित पूर्णांक mask = 1u << off;

	अगर ((mask & chip->dir_input) == 0) अणु
		dev_dbg(&chip->client->dev, "%s port %d is output only\n",
			chip->client->name, off);
		वापस -EACCES;
	पूर्ण

	/*
	 * Open-drain pins must be set to high impedance (which is
	 * equivalent to output-high) to be turned पूर्णांकo an input.
	 */
	अगर ((mask & chip->dir_output))
		max732x_gpio_set_value(gc, off, 1);

	वापस 0;
पूर्ण

अटल पूर्णांक max732x_gpio_direction_output(काष्ठा gpio_chip *gc,
		अचिन्हित off, पूर्णांक val)
अणु
	काष्ठा max732x_chip *chip = gpiochip_get_data(gc);
	अचिन्हित पूर्णांक mask = 1u << off;

	अगर ((mask & chip->dir_output) == 0) अणु
		dev_dbg(&chip->client->dev, "%s port %d is input only\n",
			chip->client->name, off);
		वापस -EACCES;
	पूर्ण

	max732x_gpio_set_value(gc, off, val);
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_GPIO_MAX732X_IRQ
अटल पूर्णांक max732x_ग_लिखोw(काष्ठा max732x_chip *chip, uपूर्णांक16_t val)
अणु
	पूर्णांक ret;

	val = cpu_to_le16(val);

	ret = i2c_master_send(chip->client_group_a, (अक्षर *)&val, 2);
	अगर (ret < 0) अणु
		dev_err(&chip->client_group_a->dev, "failed writing\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक max732x_पढ़ोw(काष्ठा max732x_chip *chip, uपूर्णांक16_t *val)
अणु
	पूर्णांक ret;

	ret = i2c_master_recv(chip->client_group_a, (अक्षर *)val, 2);
	अगर (ret < 0) अणु
		dev_err(&chip->client_group_a->dev, "failed reading\n");
		वापस ret;
	पूर्ण

	*val = le16_to_cpu(*val);
	वापस 0;
पूर्ण

अटल व्योम max732x_irq_update_mask(काष्ठा max732x_chip *chip)
अणु
	uपूर्णांक16_t msg;

	अगर (chip->irq_mask == chip->irq_mask_cur)
		वापस;

	chip->irq_mask = chip->irq_mask_cur;

	अगर (chip->irq_features == INT_NO_MASK)
		वापस;

	mutex_lock(&chip->lock);

	चयन (chip->irq_features) अणु
	हाल INT_INDEP_MASK:
		msg = (chip->irq_mask << 8) | chip->reg_out[0];
		max732x_ग_लिखोw(chip, msg);
		अवरोध;

	हाल INT_MERGED_MASK:
		msg = chip->irq_mask | chip->reg_out[0];
		max732x_ग_लिखोb(chip, 1, (uपूर्णांक8_t)msg);
		अवरोध;
	पूर्ण

	mutex_unlock(&chip->lock);
पूर्ण

अटल व्योम max732x_irq_mask(काष्ठा irq_data *d)
अणु
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(d);
	काष्ठा max732x_chip *chip = gpiochip_get_data(gc);

	chip->irq_mask_cur &= ~(1 << d->hwirq);
पूर्ण

अटल व्योम max732x_irq_unmask(काष्ठा irq_data *d)
अणु
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(d);
	काष्ठा max732x_chip *chip = gpiochip_get_data(gc);

	chip->irq_mask_cur |= 1 << d->hwirq;
पूर्ण

अटल व्योम max732x_irq_bus_lock(काष्ठा irq_data *d)
अणु
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(d);
	काष्ठा max732x_chip *chip = gpiochip_get_data(gc);

	mutex_lock(&chip->irq_lock);
	chip->irq_mask_cur = chip->irq_mask;
पूर्ण

अटल व्योम max732x_irq_bus_sync_unlock(काष्ठा irq_data *d)
अणु
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(d);
	काष्ठा max732x_chip *chip = gpiochip_get_data(gc);
	uपूर्णांक16_t new_irqs;
	uपूर्णांक16_t level;

	max732x_irq_update_mask(chip);

	new_irqs = chip->irq_trig_fall | chip->irq_trig_उठाओ;
	जबतक (new_irqs) अणु
		level = __ffs(new_irqs);
		max732x_gpio_direction_input(&chip->gpio_chip, level);
		new_irqs &= ~(1 << level);
	पूर्ण

	mutex_unlock(&chip->irq_lock);
पूर्ण

अटल पूर्णांक max732x_irq_set_type(काष्ठा irq_data *d, अचिन्हित पूर्णांक type)
अणु
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(d);
	काष्ठा max732x_chip *chip = gpiochip_get_data(gc);
	uपूर्णांक16_t off = d->hwirq;
	uपूर्णांक16_t mask = 1 << off;

	अगर (!(mask & chip->dir_input)) अणु
		dev_dbg(&chip->client->dev, "%s port %d is output only\n",
			chip->client->name, off);
		वापस -EACCES;
	पूर्ण

	अगर (!(type & IRQ_TYPE_EDGE_BOTH)) अणु
		dev_err(&chip->client->dev, "irq %d: unsupported type %d\n",
			d->irq, type);
		वापस -EINVAL;
	पूर्ण

	अगर (type & IRQ_TYPE_EDGE_FALLING)
		chip->irq_trig_fall |= mask;
	अन्यथा
		chip->irq_trig_fall &= ~mask;

	अगर (type & IRQ_TYPE_EDGE_RISING)
		chip->irq_trig_उठाओ |= mask;
	अन्यथा
		chip->irq_trig_उठाओ &= ~mask;

	वापस 0;
पूर्ण

अटल पूर्णांक max732x_irq_set_wake(काष्ठा irq_data *data, अचिन्हित पूर्णांक on)
अणु
	काष्ठा max732x_chip *chip = irq_data_get_irq_chip_data(data);

	irq_set_irq_wake(chip->client->irq, on);
	वापस 0;
पूर्ण

अटल काष्ठा irq_chip max732x_irq_chip = अणु
	.name			= "max732x",
	.irq_mask		= max732x_irq_mask,
	.irq_unmask		= max732x_irq_unmask,
	.irq_bus_lock		= max732x_irq_bus_lock,
	.irq_bus_sync_unlock	= max732x_irq_bus_sync_unlock,
	.irq_set_type		= max732x_irq_set_type,
	.irq_set_wake		= max732x_irq_set_wake,
पूर्ण;

अटल uपूर्णांक8_t max732x_irq_pending(काष्ठा max732x_chip *chip)
अणु
	uपूर्णांक8_t cur_stat;
	uपूर्णांक8_t old_stat;
	uपूर्णांक8_t trigger;
	uपूर्णांक8_t pending;
	uपूर्णांक16_t status;
	पूर्णांक ret;

	ret = max732x_पढ़ोw(chip, &status);
	अगर (ret)
		वापस 0;

	trigger = status >> 8;
	trigger &= chip->irq_mask;

	अगर (!trigger)
		वापस 0;

	cur_stat = status & 0xFF;
	cur_stat &= chip->irq_mask;

	old_stat = cur_stat ^ trigger;

	pending = (old_stat & chip->irq_trig_fall) |
		  (cur_stat & chip->irq_trig_उठाओ);
	pending &= trigger;

	वापस pending;
पूर्ण

अटल irqवापस_t max732x_irq_handler(पूर्णांक irq, व्योम *devid)
अणु
	काष्ठा max732x_chip *chip = devid;
	uपूर्णांक8_t pending;
	uपूर्णांक8_t level;

	pending = max732x_irq_pending(chip);

	अगर (!pending)
		वापस IRQ_HANDLED;

	करो अणु
		level = __ffs(pending);
		handle_nested_irq(irq_find_mapping(chip->gpio_chip.irq.करोमुख्य,
						   level));

		pending &= ~(1 << level);
	पूर्ण जबतक (pending);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक max732x_irq_setup(काष्ठा max732x_chip *chip,
			     स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा i2c_client *client = chip->client;
	काष्ठा max732x_platक्रमm_data *pdata = dev_get_platdata(&client->dev);
	पूर्णांक has_irq = max732x_features[id->driver_data] >> 32;
	पूर्णांक irq_base = 0;
	पूर्णांक ret;

	अगर (((pdata && pdata->irq_base) || client->irq)
			&& has_irq != INT_NONE) अणु
		काष्ठा gpio_irq_chip *girq;

		अगर (pdata)
			irq_base = pdata->irq_base;
		chip->irq_features = has_irq;
		mutex_init(&chip->irq_lock);

		ret = devm_request_thपढ़ोed_irq(&client->dev, client->irq,
				शून्य, max732x_irq_handler, IRQF_ONESHOT |
				IRQF_TRIGGER_FALLING | IRQF_SHARED,
				dev_name(&client->dev), chip);
		अगर (ret) अणु
			dev_err(&client->dev, "failed to request irq %d\n",
				client->irq);
			वापस ret;
		पूर्ण

		girq = &chip->gpio_chip.irq;
		girq->chip = &max732x_irq_chip;
		/* This will let us handle the parent IRQ in the driver */
		girq->parent_handler = शून्य;
		girq->num_parents = 0;
		girq->parents = शून्य;
		girq->शेष_type = IRQ_TYPE_NONE;
		girq->handler = handle_simple_irq;
		girq->thपढ़ोed = true;
		girq->first = irq_base; /* FIXME: get rid of this */
	पूर्ण

	वापस 0;
पूर्ण

#अन्यथा /* CONFIG_GPIO_MAX732X_IRQ */
अटल पूर्णांक max732x_irq_setup(काष्ठा max732x_chip *chip,
			     स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा i2c_client *client = chip->client;
	काष्ठा max732x_platक्रमm_data *pdata = dev_get_platdata(&client->dev);
	पूर्णांक has_irq = max732x_features[id->driver_data] >> 32;

	अगर (((pdata && pdata->irq_base) || client->irq) && has_irq != INT_NONE)
		dev_warn(&client->dev, "interrupt support not compiled in\n");

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक max732x_setup_gpio(काष्ठा max732x_chip *chip,
					स्थिर काष्ठा i2c_device_id *id,
					अचिन्हित gpio_start)
अणु
	काष्ठा gpio_chip *gc = &chip->gpio_chip;
	uपूर्णांक32_t id_data = (uपूर्णांक32_t)max732x_features[id->driver_data];
	पूर्णांक i, port = 0;

	क्रम (i = 0; i < 16; i++, id_data >>= 2) अणु
		अचिन्हित पूर्णांक mask = 1 << port;

		चयन (id_data & 0x3) अणु
		हाल PORT_OUTPUT:
			chip->dir_output |= mask;
			अवरोध;
		हाल PORT_INPUT:
			chip->dir_input |= mask;
			अवरोध;
		हाल PORT_OPENDRAIN:
			chip->dir_output |= mask;
			chip->dir_input |= mask;
			अवरोध;
		शेष:
			जारी;
		पूर्ण

		अगर (i < 8)
			chip->mask_group_a |= mask;
		port++;
	पूर्ण

	अगर (chip->dir_input)
		gc->direction_input = max732x_gpio_direction_input;
	अगर (chip->dir_output) अणु
		gc->direction_output = max732x_gpio_direction_output;
		gc->set = max732x_gpio_set_value;
		gc->set_multiple = max732x_gpio_set_multiple;
	पूर्ण
	gc->get = max732x_gpio_get_value;
	gc->can_sleep = true;

	gc->base = gpio_start;
	gc->ngpio = port;
	gc->label = chip->client->name;
	gc->parent = &chip->client->dev;
	gc->owner = THIS_MODULE;

	वापस port;
पूर्ण

अटल काष्ठा max732x_platक्रमm_data *of_gpio_max732x(काष्ठा device *dev)
अणु
	काष्ठा max732x_platक्रमm_data *pdata;

	pdata = devm_kzalloc(dev, माप(*pdata), GFP_KERNEL);
	अगर (!pdata)
		वापस शून्य;

	pdata->gpio_base = -1;

	वापस pdata;
पूर्ण

अटल पूर्णांक max732x_probe(काष्ठा i2c_client *client,
				   स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा max732x_platक्रमm_data *pdata;
	काष्ठा device_node *node;
	काष्ठा max732x_chip *chip;
	काष्ठा i2c_client *c;
	uपूर्णांक16_t addr_a, addr_b;
	पूर्णांक ret, nr_port;

	pdata = dev_get_platdata(&client->dev);
	node = client->dev.of_node;

	अगर (!pdata && node)
		pdata = of_gpio_max732x(&client->dev);

	अगर (!pdata) अणु
		dev_dbg(&client->dev, "no platform data\n");
		वापस -EINVAL;
	पूर्ण

	chip = devm_kzalloc(&client->dev, माप(*chip), GFP_KERNEL);
	अगर (chip == शून्य)
		वापस -ENOMEM;
	chip->client = client;

	nr_port = max732x_setup_gpio(chip, id, pdata->gpio_base);
	chip->gpio_chip.parent = &client->dev;

	addr_a = (client->addr & 0x0f) | 0x60;
	addr_b = (client->addr & 0x0f) | 0x50;

	चयन (client->addr & 0x70) अणु
	हाल 0x60:
		chip->client_group_a = client;
		अगर (nr_port > 8) अणु
			c = devm_i2c_new_dummy_device(&client->dev,
						      client->adapter, addr_b);
			अगर (IS_ERR(c)) अणु
				dev_err(&client->dev,
					"Failed to allocate I2C device\n");
				वापस PTR_ERR(c);
			पूर्ण
			chip->client_group_b = chip->client_dummy = c;
		पूर्ण
		अवरोध;
	हाल 0x50:
		chip->client_group_b = client;
		अगर (nr_port > 8) अणु
			c = devm_i2c_new_dummy_device(&client->dev,
						      client->adapter, addr_a);
			अगर (IS_ERR(c)) अणु
				dev_err(&client->dev,
					"Failed to allocate I2C device\n");
				वापस PTR_ERR(c);
			पूर्ण
			chip->client_group_a = chip->client_dummy = c;
		पूर्ण
		अवरोध;
	शेष:
		dev_err(&client->dev, "invalid I2C address specified %02x\n",
				client->addr);
		वापस -EINVAL;
	पूर्ण

	अगर (nr_port > 8 && !chip->client_dummy) अणु
		dev_err(&client->dev,
			"Failed to allocate second group I2C device\n");
		वापस -ENODEV;
	पूर्ण

	mutex_init(&chip->lock);

	ret = max732x_पढ़ोb(chip, is_group_a(chip, 0), &chip->reg_out[0]);
	अगर (ret)
		वापस ret;
	अगर (nr_port > 8) अणु
		ret = max732x_पढ़ोb(chip, is_group_a(chip, 8), &chip->reg_out[1]);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = max732x_irq_setup(chip, id);
	अगर (ret)
		वापस ret;

	ret = devm_gpiochip_add_data(&client->dev, &chip->gpio_chip, chip);
	अगर (ret)
		वापस ret;

	अगर (pdata->setup) अणु
		ret = pdata->setup(client, chip->gpio_chip.base,
				chip->gpio_chip.ngpio, pdata->context);
		अगर (ret < 0)
			dev_warn(&client->dev, "setup failed, %d\n", ret);
	पूर्ण

	i2c_set_clientdata(client, chip);
	वापस 0;
पूर्ण

अटल पूर्णांक max732x_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा max732x_platक्रमm_data *pdata = dev_get_platdata(&client->dev);
	काष्ठा max732x_chip *chip = i2c_get_clientdata(client);

	अगर (pdata && pdata->tearकरोwn) अणु
		पूर्णांक ret;

		ret = pdata->tearकरोwn(client, chip->gpio_chip.base,
				chip->gpio_chip.ngpio, pdata->context);
		अगर (ret < 0) अणु
			dev_err(&client->dev, "%s failed, %d\n",
					"teardown", ret);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा i2c_driver max732x_driver = अणु
	.driver = अणु
		.name		= "max732x",
		.of_match_table	= of_match_ptr(max732x_of_table),
	पूर्ण,
	.probe		= max732x_probe,
	.हटाओ		= max732x_हटाओ,
	.id_table	= max732x_id,
पूर्ण;

अटल पूर्णांक __init max732x_init(व्योम)
अणु
	वापस i2c_add_driver(&max732x_driver);
पूर्ण
/* रेजिस्टर after i2c postcore initcall and beक्रमe
 * subsys initcalls that may rely on these GPIOs
 */
subsys_initcall(max732x_init);

अटल व्योम __निकास max732x_निकास(व्योम)
अणु
	i2c_del_driver(&max732x_driver);
पूर्ण
module_निकास(max732x_निकास);

MODULE_AUTHOR("Eric Miao <eric.miao@marvell.com>");
MODULE_DESCRIPTION("GPIO expander driver for MAX732X");
MODULE_LICENSE("GPL");
