<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-2-Clause)
/*
 * LTC2992 - Dual Wide Range Power Monitor
 *
 * Copyright 2020 Analog Devices Inc.
 */

#समावेश <linux/bitfield.h>
#समावेश <linux/bitops.h>
#समावेश <linux/err.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/i2c.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/property.h>
#समावेश <linux/regmap.h>

#घोषणा LTC2992_CTRLB			0x01
#घोषणा LTC2992_FAULT1			0x03
#घोषणा LTC2992_POWER1			0x05
#घोषणा LTC2992_POWER1_MAX		0x08
#घोषणा LTC2992_POWER1_MIN		0x0B
#घोषणा LTC2992_POWER1_MAX_THRESH	0x0E
#घोषणा LTC2992_POWER1_MIN_THRESH	0x11
#घोषणा LTC2992_DSENSE1			0x14
#घोषणा LTC2992_DSENSE1_MAX		0x16
#घोषणा LTC2992_DSENSE1_MIN		0x18
#घोषणा LTC2992_DSENSE1_MAX_THRESH	0x1A
#घोषणा LTC2992_DSENSE1_MIN_THRESH	0x1C
#घोषणा LTC2992_SENSE1			0x1E
#घोषणा LTC2992_SENSE1_MAX		0x20
#घोषणा LTC2992_SENSE1_MIN		0x22
#घोषणा LTC2992_SENSE1_MAX_THRESH	0x24
#घोषणा LTC2992_SENSE1_MIN_THRESH	0x26
#घोषणा LTC2992_G1			0x28
#घोषणा LTC2992_G1_MAX			0x2A
#घोषणा LTC2992_G1_MIN			0x2C
#घोषणा LTC2992_G1_MAX_THRESH		0x2E
#घोषणा LTC2992_G1_MIN_THRESH		0x30
#घोषणा LTC2992_FAULT2			0x35
#घोषणा LTC2992_G2			0x5A
#घोषणा LTC2992_G2_MAX			0x5C
#घोषणा LTC2992_G2_MIN			0x5E
#घोषणा LTC2992_G2_MAX_THRESH		0x60
#घोषणा LTC2992_G2_MIN_THRESH		0x62
#घोषणा LTC2992_G3			0x64
#घोषणा LTC2992_G3_MAX			0x66
#घोषणा LTC2992_G3_MIN			0x68
#घोषणा LTC2992_G3_MAX_THRESH		0x6A
#घोषणा LTC2992_G3_MIN_THRESH		0x6C
#घोषणा LTC2992_G4			0x6E
#घोषणा LTC2992_G4_MAX			0x70
#घोषणा LTC2992_G4_MIN			0x72
#घोषणा LTC2992_G4_MAX_THRESH		0x74
#घोषणा LTC2992_G4_MIN_THRESH		0x76
#घोषणा LTC2992_FAULT3			0x92
#घोषणा LTC2992_GPIO_STATUS		0x95
#घोषणा LTC2992_GPIO_IO_CTRL		0x96
#घोषणा LTC2992_GPIO_CTRL		0x97

#घोषणा LTC2992_POWER(x)		(LTC2992_POWER1 + ((x) * 0x32))
#घोषणा LTC2992_POWER_MAX(x)		(LTC2992_POWER1_MAX + ((x) * 0x32))
#घोषणा LTC2992_POWER_MIN(x)		(LTC2992_POWER1_MIN + ((x) * 0x32))
#घोषणा LTC2992_POWER_MAX_THRESH(x)	(LTC2992_POWER1_MAX_THRESH + ((x) * 0x32))
#घोषणा LTC2992_POWER_MIN_THRESH(x)	(LTC2992_POWER1_MIN_THRESH + ((x) * 0x32))
#घोषणा LTC2992_DSENSE(x)		(LTC2992_DSENSE1 + ((x) * 0x32))
#घोषणा LTC2992_DSENSE_MAX(x)		(LTC2992_DSENSE1_MAX + ((x) * 0x32))
#घोषणा LTC2992_DSENSE_MIN(x)		(LTC2992_DSENSE1_MIN + ((x) * 0x32))
#घोषणा LTC2992_DSENSE_MAX_THRESH(x)	(LTC2992_DSENSE1_MAX_THRESH + ((x) * 0x32))
#घोषणा LTC2992_DSENSE_MIN_THRESH(x)	(LTC2992_DSENSE1_MIN_THRESH + ((x) * 0x32))
#घोषणा LTC2992_SENSE(x)		(LTC2992_SENSE1 + ((x) * 0x32))
#घोषणा LTC2992_SENSE_MAX(x)		(LTC2992_SENSE1_MAX + ((x) * 0x32))
#घोषणा LTC2992_SENSE_MIN(x)		(LTC2992_SENSE1_MIN + ((x) * 0x32))
#घोषणा LTC2992_SENSE_MAX_THRESH(x)	(LTC2992_SENSE1_MAX_THRESH + ((x) * 0x32))
#घोषणा LTC2992_SENSE_MIN_THRESH(x)	(LTC2992_SENSE1_MIN_THRESH + ((x) * 0x32))
#घोषणा LTC2992_POWER_FAULT(x)		(LTC2992_FAULT1 + ((x) * 0x32))
#घोषणा LTC2992_SENSE_FAULT(x)		(LTC2992_FAULT1 + ((x) * 0x32))
#घोषणा LTC2992_DSENSE_FAULT(x)		(LTC2992_FAULT1 + ((x) * 0x32))

/* CTRLB रेजिस्टर bitfields */
#घोषणा LTC2992_RESET_HISTORY		BIT(3)

/* FAULT1 FAULT2 रेजिस्टरs common bitfields */
#घोषणा LTC2992_POWER_FAULT_MSK(x)	(BIT(6) << (x))
#घोषणा LTC2992_DSENSE_FAULT_MSK(x)	(BIT(4) << (x))
#घोषणा LTC2992_SENSE_FAULT_MSK(x)	(BIT(2) << (x))

/* FAULT1 bitfields */
#घोषणा LTC2992_GPIO1_FAULT_MSK(x)	(BIT(0) << (x))

/* FAULT2 bitfields */
#घोषणा LTC2992_GPIO2_FAULT_MSK(x)	(BIT(0) << (x))

/* FAULT3 bitfields */
#घोषणा LTC2992_GPIO3_FAULT_MSK(x)	(BIT(6) << (x))
#घोषणा LTC2992_GPIO4_FAULT_MSK(x)	(BIT(4) << (x))

#घोषणा LTC2992_IADC_न_अंकOV_LSB		12500
#घोषणा LTC2992_VADC_UV_LSB		25000
#घोषणा LTC2992_VADC_GPIO_UV_LSB	500

#घोषणा LTC2992_GPIO_NR		4
#घोषणा LTC2992_GPIO1_BIT	7
#घोषणा LTC2992_GPIO2_BIT	6
#घोषणा LTC2992_GPIO3_BIT	0
#घोषणा LTC2992_GPIO4_BIT	6
#घोषणा LTC2992_GPIO_BIT(x)	(LTC2992_GPIO_NR - (x) - 1)

काष्ठा ltc2992_state अणु
	काष्ठा i2c_client		*client;
	काष्ठा gpio_chip		gc;
	काष्ठा mutex			gpio_mutex; /* lock क्रम gpio access */
	स्थिर अक्षर			*gpio_names[LTC2992_GPIO_NR];
	काष्ठा regmap			*regmap;
	u32				r_sense_uohm[2];
पूर्ण;

काष्ठा ltc2992_gpio_regs अणु
	u8	data;
	u8	max;
	u8	min;
	u8	max_thresh;
	u8	min_thresh;
	u8	alarm;
	u8	min_alarm_msk;
	u8	max_alarm_msk;
	u8	ctrl;
	u8	ctrl_bit;
पूर्ण;

अटल स्थिर काष्ठा ltc2992_gpio_regs ltc2992_gpio_addr_map[] = अणु
	अणु
		.data = LTC2992_G1,
		.max = LTC2992_G1_MAX,
		.min = LTC2992_G1_MIN,
		.max_thresh = LTC2992_G1_MAX_THRESH,
		.min_thresh = LTC2992_G1_MIN_THRESH,
		.alarm = LTC2992_FAULT1,
		.min_alarm_msk = LTC2992_GPIO1_FAULT_MSK(0),
		.max_alarm_msk = LTC2992_GPIO1_FAULT_MSK(1),
		.ctrl = LTC2992_GPIO_IO_CTRL,
		.ctrl_bit = LTC2992_GPIO1_BIT,
	पूर्ण,
	अणु
		.data = LTC2992_G2,
		.max = LTC2992_G2_MAX,
		.min = LTC2992_G2_MIN,
		.max_thresh = LTC2992_G2_MAX_THRESH,
		.min_thresh = LTC2992_G2_MIN_THRESH,
		.alarm = LTC2992_FAULT2,
		.min_alarm_msk = LTC2992_GPIO2_FAULT_MSK(0),
		.max_alarm_msk = LTC2992_GPIO2_FAULT_MSK(1),
		.ctrl = LTC2992_GPIO_IO_CTRL,
		.ctrl_bit = LTC2992_GPIO2_BIT,
	पूर्ण,
	अणु
		.data = LTC2992_G3,
		.max = LTC2992_G3_MAX,
		.min = LTC2992_G3_MIN,
		.max_thresh = LTC2992_G3_MAX_THRESH,
		.min_thresh = LTC2992_G3_MIN_THRESH,
		.alarm = LTC2992_FAULT3,
		.min_alarm_msk = LTC2992_GPIO3_FAULT_MSK(0),
		.max_alarm_msk = LTC2992_GPIO3_FAULT_MSK(1),
		.ctrl = LTC2992_GPIO_IO_CTRL,
		.ctrl_bit = LTC2992_GPIO3_BIT,
	पूर्ण,
	अणु
		.data = LTC2992_G4,
		.max = LTC2992_G4_MAX,
		.min = LTC2992_G4_MIN,
		.max_thresh = LTC2992_G4_MAX_THRESH,
		.min_thresh = LTC2992_G4_MIN_THRESH,
		.alarm = LTC2992_FAULT3,
		.min_alarm_msk = LTC2992_GPIO4_FAULT_MSK(0),
		.max_alarm_msk = LTC2992_GPIO4_FAULT_MSK(1),
		.ctrl = LTC2992_GPIO_CTRL,
		.ctrl_bit = LTC2992_GPIO4_BIT,
	पूर्ण,
पूर्ण;

अटल स्थिर अक्षर *ltc2992_gpio_names[LTC2992_GPIO_NR] = अणु
	"GPIO1", "GPIO2", "GPIO3", "GPIO4",
पूर्ण;

अटल पूर्णांक ltc2992_पढ़ो_reg(काष्ठा ltc2992_state *st, u8 addr, स्थिर u8 reg_len)
अणु
	u8 regvals[4];
	पूर्णांक val;
	पूर्णांक ret;
	पूर्णांक i;

	ret = regmap_bulk_पढ़ो(st->regmap, addr, regvals, reg_len);
	अगर (ret < 0)
		वापस ret;

	val = 0;
	क्रम (i = 0; i < reg_len; i++)
		val |= regvals[reg_len - i - 1] << (i * 8);

	वापस val;
पूर्ण

अटल पूर्णांक ltc2992_ग_लिखो_reg(काष्ठा ltc2992_state *st, u8 addr, स्थिर u8 reg_len, u32 val)
अणु
	u8 regvals[4];
	पूर्णांक i;

	क्रम (i = 0; i < reg_len; i++)
		regvals[reg_len - i - 1] = (val >> (i * 8)) & 0xFF;

	वापस regmap_bulk_ग_लिखो(st->regmap, addr, regvals, reg_len);
पूर्ण

अटल पूर्णांक ltc2992_gpio_get(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset)
अणु
	काष्ठा ltc2992_state *st = gpiochip_get_data(chip);
	अचिन्हित दीर्घ gpio_status;
	पूर्णांक reg;

	mutex_lock(&st->gpio_mutex);
	reg = ltc2992_पढ़ो_reg(st, LTC2992_GPIO_STATUS, 1);
	mutex_unlock(&st->gpio_mutex);

	अगर (reg < 0)
		वापस reg;

	gpio_status = reg;

	वापस !test_bit(LTC2992_GPIO_BIT(offset), &gpio_status);
पूर्ण

अटल पूर्णांक ltc2992_gpio_get_multiple(काष्ठा gpio_chip *chip, अचिन्हित दीर्घ *mask,
				     अचिन्हित दीर्घ *bits)
अणु
	काष्ठा ltc2992_state *st = gpiochip_get_data(chip);
	अचिन्हित दीर्घ gpio_status;
	अचिन्हित पूर्णांक gpio_nr;
	पूर्णांक reg;

	mutex_lock(&st->gpio_mutex);
	reg = ltc2992_पढ़ो_reg(st, LTC2992_GPIO_STATUS, 1);
	mutex_unlock(&st->gpio_mutex);

	अगर (reg < 0)
		वापस reg;

	gpio_status = reg;

	gpio_nr = 0;
	क्रम_each_set_bit_from(gpio_nr, mask, LTC2992_GPIO_NR) अणु
		अगर (test_bit(LTC2992_GPIO_BIT(gpio_nr), &gpio_status))
			set_bit(gpio_nr, bits);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम ltc2992_gpio_set(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset, पूर्णांक value)
अणु
	काष्ठा ltc2992_state *st = gpiochip_get_data(chip);
	अचिन्हित दीर्घ gpio_ctrl;
	पूर्णांक reg;

	mutex_lock(&st->gpio_mutex);
	reg = ltc2992_पढ़ो_reg(st, ltc2992_gpio_addr_map[offset].ctrl, 1);
	अगर (reg < 0) अणु
		mutex_unlock(&st->gpio_mutex);
		वापस;
	पूर्ण

	gpio_ctrl = reg;
	assign_bit(ltc2992_gpio_addr_map[offset].ctrl_bit, &gpio_ctrl, value);

	ltc2992_ग_लिखो_reg(st, ltc2992_gpio_addr_map[offset].ctrl, 1, gpio_ctrl);
	mutex_unlock(&st->gpio_mutex);
पूर्ण

अटल व्योम ltc2992_gpio_set_multiple(काष्ठा gpio_chip *chip, अचिन्हित दीर्घ *mask,
				      अचिन्हित दीर्घ *bits)
अणु
	काष्ठा ltc2992_state *st = gpiochip_get_data(chip);
	अचिन्हित दीर्घ gpio_ctrl_io = 0;
	अचिन्हित दीर्घ gpio_ctrl = 0;
	अचिन्हित पूर्णांक gpio_nr;

	क्रम_each_set_bit(gpio_nr, mask, LTC2992_GPIO_NR) अणु
		अगर (gpio_nr < 3)
			assign_bit(ltc2992_gpio_addr_map[gpio_nr].ctrl_bit, &gpio_ctrl_io, true);

		अगर (gpio_nr == 3)
			assign_bit(ltc2992_gpio_addr_map[gpio_nr].ctrl_bit, &gpio_ctrl, true);
	पूर्ण

	mutex_lock(&st->gpio_mutex);
	ltc2992_ग_लिखो_reg(st, LTC2992_GPIO_IO_CTRL, 1, gpio_ctrl_io);
	ltc2992_ग_लिखो_reg(st, LTC2992_GPIO_CTRL, 1, gpio_ctrl);
	mutex_unlock(&st->gpio_mutex);
पूर्ण

अटल पूर्णांक ltc2992_config_gpio(काष्ठा ltc2992_state *st)
अणु
	स्थिर अक्षर *name = dev_name(&st->client->dev);
	अक्षर *gpio_name;
	पूर्णांक ret;
	पूर्णांक i;

	ret = ltc2992_ग_लिखो_reg(st, LTC2992_GPIO_IO_CTRL, 1, 0);
	अगर (ret < 0)
		वापस ret;

	mutex_init(&st->gpio_mutex);

	क्रम (i = 0; i < ARRAY_SIZE(st->gpio_names); i++) अणु
		gpio_name = devm_kaप्र_लिखो(&st->client->dev, GFP_KERNEL, "ltc2992-%x-%s",
					   st->client->addr, ltc2992_gpio_names[i]);
		अगर (!gpio_name)
			वापस -ENOMEM;

		st->gpio_names[i] = gpio_name;
	पूर्ण

	st->gc.label = name;
	st->gc.parent = &st->client->dev;
	st->gc.owner = THIS_MODULE;
	st->gc.base = -1;
	st->gc.names = st->gpio_names;
	st->gc.ngpio = ARRAY_SIZE(st->gpio_names);
	st->gc.get = ltc2992_gpio_get;
	st->gc.get_multiple = ltc2992_gpio_get_multiple;
	st->gc.set = ltc2992_gpio_set;
	st->gc.set_multiple = ltc2992_gpio_set_multiple;

	ret = devm_gpiochip_add_data(&st->client->dev, &st->gc, st);
	अगर (ret)
		dev_err(&st->client->dev, "GPIO registering failed (%d)\n", ret);

	वापस ret;
पूर्ण

अटल umode_t ltc2992_is_visible(स्थिर व्योम *data, क्रमागत hwmon_sensor_types type, u32 attr,
				  पूर्णांक channel)
अणु
	स्थिर काष्ठा ltc2992_state *st = data;

	चयन (type) अणु
	हाल hwmon_chip:
		चयन (attr) अणु
		हाल hwmon_chip_in_reset_history:
			वापस 0200;
		पूर्ण
		अवरोध;
	हाल hwmon_in:
		चयन (attr) अणु
		हाल hwmon_in_input:
		हाल hwmon_in_lowest:
		हाल hwmon_in_highest:
		हाल hwmon_in_min_alarm:
		हाल hwmon_in_max_alarm:
			वापस 0444;
		हाल hwmon_in_min:
		हाल hwmon_in_max:
			वापस 0644;
		पूर्ण
		अवरोध;
	हाल hwmon_curr:
		चयन (attr) अणु
		हाल hwmon_curr_input:
		हाल hwmon_curr_lowest:
		हाल hwmon_curr_highest:
		हाल hwmon_curr_min_alarm:
		हाल hwmon_curr_max_alarm:
			अगर (st->r_sense_uohm[channel])
				वापस 0444;
			अवरोध;
		हाल hwmon_curr_min:
		हाल hwmon_curr_max:
			अगर (st->r_sense_uohm[channel])
				वापस 0644;
			अवरोध;
		पूर्ण
		अवरोध;
	हाल hwmon_घातer:
		चयन (attr) अणु
		हाल hwmon_घातer_input:
		हाल hwmon_घातer_input_lowest:
		हाल hwmon_घातer_input_highest:
		हाल hwmon_घातer_min_alarm:
		हाल hwmon_घातer_max_alarm:
			अगर (st->r_sense_uohm[channel])
				वापस 0444;
			अवरोध;
		हाल hwmon_घातer_min:
		हाल hwmon_घातer_max:
			अगर (st->r_sense_uohm[channel])
				वापस 0644;
			अवरोध;
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ltc2992_get_voltage(काष्ठा ltc2992_state *st, u32 reg, u32 scale, दीर्घ *val)
अणु
	पूर्णांक reg_val;

	reg_val = ltc2992_पढ़ो_reg(st, reg, 2);
	अगर (reg_val < 0)
		वापस reg_val;

	reg_val = reg_val >> 4;
	*val = DIV_ROUND_CLOSEST(reg_val * scale, 1000);

	वापस 0;
पूर्ण

अटल पूर्णांक ltc2992_set_voltage(काष्ठा ltc2992_state *st, u32 reg, u32 scale, दीर्घ val)
अणु
	val = DIV_ROUND_CLOSEST(val * 1000, scale);
	val = val << 4;

	वापस ltc2992_ग_लिखो_reg(st, reg, 2, val);
पूर्ण

अटल पूर्णांक ltc2992_पढ़ो_gpio_alarm(काष्ठा ltc2992_state *st, पूर्णांक nr_gpio, u32 attr, दीर्घ *val)
अणु
	पूर्णांक reg_val;
	u32 mask;

	अगर (attr == hwmon_in_max_alarm)
		mask = ltc2992_gpio_addr_map[nr_gpio].max_alarm_msk;
	अन्यथा
		mask = ltc2992_gpio_addr_map[nr_gpio].min_alarm_msk;

	reg_val = ltc2992_पढ़ो_reg(st, ltc2992_gpio_addr_map[nr_gpio].alarm, 1);
	अगर (reg_val < 0)
		वापस reg_val;

	*val = !!(reg_val & mask);
	reg_val &= ~mask;

	वापस ltc2992_ग_लिखो_reg(st, ltc2992_gpio_addr_map[nr_gpio].alarm, 1, reg_val);
पूर्ण

अटल पूर्णांक ltc2992_पढ़ो_gpios_in(काष्ठा device *dev, u32 attr, पूर्णांक nr_gpio, दीर्घ *val)
अणु
	काष्ठा ltc2992_state *st = dev_get_drvdata(dev);
	u32 reg;

	चयन (attr) अणु
	हाल hwmon_in_input:
		reg = ltc2992_gpio_addr_map[nr_gpio].data;
		अवरोध;
	हाल hwmon_in_lowest:
		reg = ltc2992_gpio_addr_map[nr_gpio].min;
		अवरोध;
	हाल hwmon_in_highest:
		reg = ltc2992_gpio_addr_map[nr_gpio].max;
		अवरोध;
	हाल hwmon_in_min:
		reg = ltc2992_gpio_addr_map[nr_gpio].min_thresh;
		अवरोध;
	हाल hwmon_in_max:
		reg = ltc2992_gpio_addr_map[nr_gpio].max_thresh;
		अवरोध;
	हाल hwmon_in_min_alarm:
	हाल hwmon_in_max_alarm:
		वापस ltc2992_पढ़ो_gpio_alarm(st, nr_gpio, attr, val);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस ltc2992_get_voltage(st, reg, LTC2992_VADC_GPIO_UV_LSB, val);
पूर्ण

अटल पूर्णांक ltc2992_पढ़ो_in_alarm(काष्ठा ltc2992_state *st, पूर्णांक channel, दीर्घ *val, u32 attr)
अणु
	पूर्णांक reg_val;
	u32 mask;

	अगर (attr == hwmon_in_max_alarm)
		mask = LTC2992_SENSE_FAULT_MSK(1);
	अन्यथा
		mask = LTC2992_SENSE_FAULT_MSK(0);

	reg_val = ltc2992_पढ़ो_reg(st, LTC2992_SENSE_FAULT(channel), 1);
	अगर (reg_val < 0)
		वापस reg_val;

	*val = !!(reg_val & mask);
	reg_val &= ~mask;

	वापस ltc2992_ग_लिखो_reg(st, LTC2992_SENSE_FAULT(channel), 1, reg_val);
पूर्ण

अटल पूर्णांक ltc2992_पढ़ो_in(काष्ठा device *dev, u32 attr, पूर्णांक channel, दीर्घ *val)
अणु
	काष्ठा ltc2992_state *st = dev_get_drvdata(dev);
	u32 reg;

	अगर (channel > 1)
		वापस ltc2992_पढ़ो_gpios_in(dev, attr, channel - 2, val);

	चयन (attr) अणु
	हाल hwmon_in_input:
		reg = LTC2992_SENSE(channel);
		अवरोध;
	हाल hwmon_in_lowest:
		reg = LTC2992_SENSE_MIN(channel);
		अवरोध;
	हाल hwmon_in_highest:
		reg = LTC2992_SENSE_MAX(channel);
		अवरोध;
	हाल hwmon_in_min:
		reg = LTC2992_SENSE_MIN_THRESH(channel);
		अवरोध;
	हाल hwmon_in_max:
		reg = LTC2992_SENSE_MAX_THRESH(channel);
		अवरोध;
	हाल hwmon_in_min_alarm:
	हाल hwmon_in_max_alarm:
		वापस ltc2992_पढ़ो_in_alarm(st, channel, val, attr);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस ltc2992_get_voltage(st, reg, LTC2992_VADC_UV_LSB, val);
पूर्ण

अटल पूर्णांक ltc2992_get_current(काष्ठा ltc2992_state *st, u32 reg, u32 channel, दीर्घ *val)
अणु
	पूर्णांक reg_val;

	reg_val = ltc2992_पढ़ो_reg(st, reg, 2);
	अगर (reg_val < 0)
		वापस reg_val;

	reg_val = reg_val >> 4;
	*val = DIV_ROUND_CLOSEST(reg_val * LTC2992_IADC_न_अंकOV_LSB, st->r_sense_uohm[channel]);

	वापस 0;
पूर्ण

अटल पूर्णांक ltc2992_set_current(काष्ठा ltc2992_state *st, u32 reg, u32 channel, दीर्घ val)
अणु
	u32 reg_val;

	reg_val = DIV_ROUND_CLOSEST(val * st->r_sense_uohm[channel], LTC2992_IADC_न_अंकOV_LSB);
	reg_val = reg_val << 4;

	वापस ltc2992_ग_लिखो_reg(st, reg, 2, reg_val);
पूर्ण

अटल पूर्णांक ltc2992_पढ़ो_curr_alarm(काष्ठा ltc2992_state *st, पूर्णांक channel, दीर्घ *val, u32 attr)
अणु
	पूर्णांक reg_val;
	u32 mask;

	अगर (attr == hwmon_curr_max_alarm)
		mask = LTC2992_DSENSE_FAULT_MSK(1);
	अन्यथा
		mask = LTC2992_DSENSE_FAULT_MSK(0);

	reg_val = ltc2992_पढ़ो_reg(st, LTC2992_DSENSE_FAULT(channel), 1);
	अगर (reg_val < 0)
		वापस reg_val;

	*val = !!(reg_val & mask);

	reg_val &= ~mask;
	वापस ltc2992_ग_लिखो_reg(st, LTC2992_DSENSE_FAULT(channel), 1, reg_val);
पूर्ण

अटल पूर्णांक ltc2992_पढ़ो_curr(काष्ठा device *dev, u32 attr, पूर्णांक channel, दीर्घ *val)
अणु
	काष्ठा ltc2992_state *st = dev_get_drvdata(dev);
	u32 reg;

	चयन (attr) अणु
	हाल hwmon_curr_input:
		reg = LTC2992_DSENSE(channel);
		अवरोध;
	हाल hwmon_curr_lowest:
		reg = LTC2992_DSENSE_MIN(channel);
		अवरोध;
	हाल hwmon_curr_highest:
		reg = LTC2992_DSENSE_MAX(channel);
		अवरोध;
	हाल hwmon_curr_min:
		reg = LTC2992_DSENSE_MIN_THRESH(channel);
		अवरोध;
	हाल hwmon_curr_max:
		reg = LTC2992_DSENSE_MAX_THRESH(channel);
		अवरोध;
	हाल hwmon_curr_min_alarm:
	हाल hwmon_curr_max_alarm:
		वापस ltc2992_पढ़ो_curr_alarm(st, channel, val, attr);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस ltc2992_get_current(st, reg, channel, val);
पूर्ण

अटल पूर्णांक ltc2992_get_घातer(काष्ठा ltc2992_state *st, u32 reg, u32 channel, दीर्घ *val)
अणु
	पूर्णांक reg_val;

	reg_val = ltc2992_पढ़ो_reg(st, reg, 3);
	अगर (reg_val < 0)
		वापस reg_val;

	*val = mul_u64_u32_भाग(reg_val, LTC2992_VADC_UV_LSB * LTC2992_IADC_न_अंकOV_LSB,
			       st->r_sense_uohm[channel] * 1000);

	वापस 0;
पूर्ण

अटल पूर्णांक ltc2992_set_घातer(काष्ठा ltc2992_state *st, u32 reg, u32 channel, दीर्घ val)
अणु
	u32 reg_val;

	reg_val = mul_u64_u32_भाग(val, st->r_sense_uohm[channel] * 1000,
				  LTC2992_VADC_UV_LSB * LTC2992_IADC_न_अंकOV_LSB);

	वापस ltc2992_ग_लिखो_reg(st, reg, 3, reg_val);
पूर्ण

अटल पूर्णांक ltc2992_पढ़ो_घातer_alarm(काष्ठा ltc2992_state *st, पूर्णांक channel, दीर्घ *val, u32 attr)
अणु
	पूर्णांक reg_val;
	u32 mask;

	अगर (attr == hwmon_घातer_max_alarm)
		mask = LTC2992_POWER_FAULT_MSK(1);
	अन्यथा
		mask = LTC2992_POWER_FAULT_MSK(0);

	reg_val = ltc2992_पढ़ो_reg(st, LTC2992_POWER_FAULT(channel), 1);
	अगर (reg_val < 0)
		वापस reg_val;

	*val = !!(reg_val & mask);
	reg_val &= ~mask;

	वापस ltc2992_ग_लिखो_reg(st, LTC2992_POWER_FAULT(channel), 1, reg_val);
पूर्ण

अटल पूर्णांक ltc2992_पढ़ो_घातer(काष्ठा device *dev, u32 attr, पूर्णांक channel, दीर्घ *val)
अणु
	काष्ठा ltc2992_state *st = dev_get_drvdata(dev);
	u32 reg;

	चयन (attr) अणु
	हाल hwmon_घातer_input:
		reg = LTC2992_POWER(channel);
		अवरोध;
	हाल hwmon_घातer_input_lowest:
		reg = LTC2992_POWER_MIN(channel);
		अवरोध;
	हाल hwmon_घातer_input_highest:
		reg = LTC2992_POWER_MAX(channel);
		अवरोध;
	हाल hwmon_घातer_min:
		reg = LTC2992_POWER_MIN_THRESH(channel);
		अवरोध;
	हाल hwmon_घातer_max:
		reg = LTC2992_POWER_MAX_THRESH(channel);
		अवरोध;
	हाल hwmon_घातer_min_alarm:
	हाल hwmon_घातer_max_alarm:
		वापस ltc2992_पढ़ो_घातer_alarm(st, channel, val, attr);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस ltc2992_get_घातer(st, reg, channel, val);
पूर्ण

अटल पूर्णांक ltc2992_पढ़ो(काष्ठा device *dev, क्रमागत hwmon_sensor_types type, u32 attr, पूर्णांक channel,
			दीर्घ *val)
अणु
	चयन (type) अणु
	हाल hwmon_in:
		वापस ltc2992_पढ़ो_in(dev, attr, channel, val);
	हाल hwmon_curr:
		वापस ltc2992_पढ़ो_curr(dev, attr, channel, val);
	हाल hwmon_घातer:
		वापस ltc2992_पढ़ो_घातer(dev, attr, channel, val);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक ltc2992_ग_लिखो_curr(काष्ठा device *dev, u32 attr, पूर्णांक channel, दीर्घ val)
अणु
	काष्ठा ltc2992_state *st = dev_get_drvdata(dev);
	u32 reg;

	चयन (attr) अणु
	हाल hwmon_curr_min:
		reg = LTC2992_DSENSE_MIN_THRESH(channel);
		अवरोध;
	हाल hwmon_curr_max:
		reg = LTC2992_DSENSE_MAX_THRESH(channel);
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस ltc2992_set_current(st, reg, channel, val);
पूर्ण

अटल पूर्णांक ltc2992_ग_लिखो_gpios_in(काष्ठा device *dev, u32 attr, पूर्णांक nr_gpio, दीर्घ val)
अणु
	काष्ठा ltc2992_state *st = dev_get_drvdata(dev);
	u32 reg;

	चयन (attr) अणु
	हाल hwmon_in_min:
		reg = ltc2992_gpio_addr_map[nr_gpio].min_thresh;
		अवरोध;
	हाल hwmon_in_max:
		reg = ltc2992_gpio_addr_map[nr_gpio].max_thresh;
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस ltc2992_set_voltage(st, reg, LTC2992_VADC_GPIO_UV_LSB, val);
पूर्ण

अटल पूर्णांक ltc2992_ग_लिखो_in(काष्ठा device *dev, u32 attr, पूर्णांक channel, दीर्घ val)
अणु
	काष्ठा ltc2992_state *st = dev_get_drvdata(dev);
	u32 reg;

	अगर (channel > 1)
		वापस ltc2992_ग_लिखो_gpios_in(dev, attr, channel - 2, val);

	चयन (attr) अणु
	हाल hwmon_in_min:
		reg = LTC2992_SENSE_MIN_THRESH(channel);
		अवरोध;
	हाल hwmon_in_max:
		reg = LTC2992_SENSE_MAX_THRESH(channel);
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस ltc2992_set_voltage(st, reg, LTC2992_VADC_UV_LSB, val);
पूर्ण

अटल पूर्णांक ltc2992_ग_लिखो_घातer(काष्ठा device *dev, u32 attr, पूर्णांक channel, दीर्घ val)
अणु
	काष्ठा ltc2992_state *st = dev_get_drvdata(dev);
	u32 reg;

	चयन (attr) अणु
	हाल hwmon_घातer_min:
		reg = LTC2992_POWER_MIN_THRESH(channel);
		अवरोध;
	हाल hwmon_घातer_max:
		reg = LTC2992_POWER_MAX_THRESH(channel);
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस ltc2992_set_घातer(st, reg, channel, val);
पूर्ण

अटल पूर्णांक ltc2992_ग_लिखो_chip(काष्ठा device *dev, u32 attr, पूर्णांक channel, दीर्घ val)
अणु
	काष्ठा ltc2992_state *st = dev_get_drvdata(dev);

	चयन (attr) अणु
	हाल hwmon_chip_in_reset_history:
		वापस regmap_update_bits(st->regmap, LTC2992_CTRLB, LTC2992_RESET_HISTORY,
					  LTC2992_RESET_HISTORY);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक ltc2992_ग_लिखो(काष्ठा device *dev, क्रमागत hwmon_sensor_types type, u32 attr, पूर्णांक channel,
			 दीर्घ val)
अणु
	चयन (type) अणु
	हाल hwmon_chip:
		वापस ltc2992_ग_लिखो_chip(dev, attr, channel, val);
	हाल hwmon_in:
		वापस ltc2992_ग_लिखो_in(dev, attr, channel, val);
	हाल hwmon_curr:
		वापस ltc2992_ग_लिखो_curr(dev, attr, channel, val);
	हाल hwmon_घातer:
		वापस ltc2992_ग_लिखो_घातer(dev, attr, channel, val);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा hwmon_ops ltc2992_hwmon_ops = अणु
	.is_visible = ltc2992_is_visible,
	.पढ़ो = ltc2992_पढ़ो,
	.ग_लिखो = ltc2992_ग_लिखो,
पूर्ण;

अटल स्थिर u32 ltc2992_chip_config[] = अणु
	HWMON_C_IN_RESET_HISTORY,
	0
पूर्ण;

अटल स्थिर काष्ठा hwmon_channel_info ltc2992_chip = अणु
	.type = hwmon_chip,
	.config = ltc2992_chip_config,
पूर्ण;

अटल स्थिर u32 ltc2992_in_config[] = अणु
	HWMON_I_INPUT | HWMON_I_LOWEST | HWMON_I_HIGHEST | HWMON_I_MIN | HWMON_I_MAX |
	HWMON_I_MIN_ALARM | HWMON_I_MAX_ALARM,
	HWMON_I_INPUT | HWMON_I_LOWEST | HWMON_I_HIGHEST | HWMON_I_MIN | HWMON_I_MAX |
	HWMON_I_MIN_ALARM | HWMON_I_MAX_ALARM,
	HWMON_I_INPUT | HWMON_I_LOWEST | HWMON_I_HIGHEST | HWMON_I_MIN | HWMON_I_MAX |
	HWMON_I_MIN_ALARM | HWMON_I_MAX_ALARM,
	HWMON_I_INPUT | HWMON_I_LOWEST | HWMON_I_HIGHEST | HWMON_I_MIN | HWMON_I_MAX |
	HWMON_I_MIN_ALARM | HWMON_I_MAX_ALARM,
	HWMON_I_INPUT | HWMON_I_LOWEST | HWMON_I_HIGHEST | HWMON_I_MIN | HWMON_I_MAX |
	HWMON_I_MIN_ALARM | HWMON_I_MAX_ALARM,
	HWMON_I_INPUT | HWMON_I_LOWEST | HWMON_I_HIGHEST | HWMON_I_MIN | HWMON_I_MAX |
	HWMON_I_MIN_ALARM | HWMON_I_MAX_ALARM,
	0
पूर्ण;

अटल स्थिर काष्ठा hwmon_channel_info ltc2992_in = अणु
	.type = hwmon_in,
	.config = ltc2992_in_config,
पूर्ण;

अटल स्थिर u32 ltc2992_curr_config[] = अणु
	HWMON_C_INPUT | HWMON_C_LOWEST | HWMON_C_HIGHEST | HWMON_C_MIN | HWMON_C_MAX |
	HWMON_C_MIN_ALARM | HWMON_C_MAX_ALARM,
	HWMON_C_INPUT | HWMON_C_LOWEST | HWMON_C_HIGHEST | HWMON_C_MIN | HWMON_C_MAX |
	HWMON_C_MIN_ALARM | HWMON_C_MAX_ALARM,
	0
पूर्ण;

अटल स्थिर काष्ठा hwmon_channel_info ltc2992_curr = अणु
	.type = hwmon_curr,
	.config = ltc2992_curr_config,
पूर्ण;

अटल स्थिर u32 ltc2992_घातer_config[] = अणु
	HWMON_P_INPUT | HWMON_P_INPUT_LOWEST | HWMON_P_INPUT_HIGHEST | HWMON_P_MIN | HWMON_P_MAX |
	HWMON_P_MIN_ALARM | HWMON_P_MAX_ALARM,
	HWMON_P_INPUT | HWMON_P_INPUT_LOWEST | HWMON_P_INPUT_HIGHEST | HWMON_P_MIN | HWMON_P_MAX |
	HWMON_P_MIN_ALARM | HWMON_P_MAX_ALARM,
	0
पूर्ण;

अटल स्थिर काष्ठा hwmon_channel_info ltc2992_घातer = अणु
	.type = hwmon_घातer,
	.config = ltc2992_घातer_config,
पूर्ण;

अटल स्थिर काष्ठा hwmon_channel_info *ltc2992_info[] = अणु
	&ltc2992_chip,
	&ltc2992_in,
	&ltc2992_curr,
	&ltc2992_घातer,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा hwmon_chip_info ltc2992_chip_info = अणु
	.ops = &ltc2992_hwmon_ops,
	.info = ltc2992_info,
पूर्ण;

अटल स्थिर काष्ठा regmap_config ltc2992_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,
	.max_रेजिस्टर = 0xE8,
पूर्ण;

अटल पूर्णांक ltc2992_parse_dt(काष्ठा ltc2992_state *st)
अणु
	काष्ठा fwnode_handle *fwnode;
	काष्ठा fwnode_handle *child;
	u32 addr;
	u32 val;
	पूर्णांक ret;

	fwnode = dev_fwnode(&st->client->dev);

	fwnode_क्रम_each_available_child_node(fwnode, child) अणु
		ret = fwnode_property_पढ़ो_u32(child, "reg", &addr);
		अगर (ret < 0) अणु
			fwnode_handle_put(child);
			वापस ret;
		पूर्ण

		अगर (addr > 1) अणु
			fwnode_handle_put(child);
			वापस -EINVAL;
		पूर्ण

		ret = fwnode_property_पढ़ो_u32(child, "shunt-resistor-micro-ohms", &val);
		अगर (!ret)
			st->r_sense_uohm[addr] = val;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ltc2992_i2c_probe(काष्ठा i2c_client *client, स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा device *hwmon_dev;
	काष्ठा ltc2992_state *st;
	पूर्णांक ret;

	st = devm_kzalloc(&client->dev, माप(*st), GFP_KERNEL);
	अगर (!st)
		वापस -ENOMEM;

	st->client = client;
	st->regmap = devm_regmap_init_i2c(client, &ltc2992_regmap_config);
	अगर (IS_ERR(st->regmap))
		वापस PTR_ERR(st->regmap);

	ret = ltc2992_parse_dt(st);
	अगर (ret < 0)
		वापस ret;

	ret = ltc2992_config_gpio(st);
	अगर (ret < 0)
		वापस ret;

	hwmon_dev = devm_hwmon_device_रेजिस्टर_with_info(&client->dev, client->name, st,
							 &ltc2992_chip_info, शून्य);

	वापस PTR_ERR_OR_ZERO(hwmon_dev);
पूर्ण

अटल स्थिर काष्ठा of_device_id ltc2992_of_match[] = अणु
	अणु .compatible = "adi,ltc2992" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, ltc2992_of_match);

अटल स्थिर काष्ठा i2c_device_id ltc2992_i2c_id[] = अणु
	अणु"ltc2992", 0पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, ltc2992_i2c_id);

अटल काष्ठा i2c_driver ltc2992_i2c_driver = अणु
	.driver = अणु
		.name = "ltc2992",
		.of_match_table = ltc2992_of_match,
	पूर्ण,
	.probe    = ltc2992_i2c_probe,
	.id_table = ltc2992_i2c_id,
पूर्ण;

module_i2c_driver(ltc2992_i2c_driver);

MODULE_AUTHOR("Alexandru Tachici <alexandru.tachici@analog.com>");
MODULE_DESCRIPTION("Hwmon driver for Linear Technology 2992");
MODULE_LICENSE("Dual BSD/GPL");
