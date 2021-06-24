<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Marvell 88E6xxx Switch Global 2 Scratch & Misc Registers support
 *
 * Copyright (c) 2008 Marvell Semiconductor
 *
 * Copyright (c) 2017 National Instruments
 *      Bअक्रमon Streअगरf <bअक्रमon.streअगरf@ni.com>
 */

#समावेश "chip.h"
#समावेश "global2.h"

/* Offset 0x1A: Scratch and Misc. Register */
अटल पूर्णांक mv88e6xxx_g2_scratch_पढ़ो(काष्ठा mv88e6xxx_chip *chip, पूर्णांक reg,
				     u8 *data)
अणु
	u16 value;
	पूर्णांक err;

	err = mv88e6xxx_g2_ग_लिखो(chip, MV88E6XXX_G2_SCRATCH_MISC_MISC,
				 reg << 8);
	अगर (err)
		वापस err;

	err = mv88e6xxx_g2_पढ़ो(chip, MV88E6XXX_G2_SCRATCH_MISC_MISC, &value);
	अगर (err)
		वापस err;

	*data = (value & MV88E6XXX_G2_SCRATCH_MISC_DATA_MASK);

	वापस 0;
पूर्ण

अटल पूर्णांक mv88e6xxx_g2_scratch_ग_लिखो(काष्ठा mv88e6xxx_chip *chip, पूर्णांक reg,
				      u8 data)
अणु
	u16 value = (reg << 8) | data;

	वापस mv88e6xxx_g2_ग_लिखो(chip, MV88E6XXX_G2_SCRATCH_MISC_MISC,
				  MV88E6XXX_G2_SCRATCH_MISC_UPDATE | value);
पूर्ण

/**
 * mv88e6xxx_g2_scratch_get_bit - get a bit
 * @chip: chip निजी data
 * @base_reg: base of scratch bits
 * @offset: index of bit within the रेजिस्टर
 * @set: is bit set?
 */
अटल पूर्णांक mv88e6xxx_g2_scratch_get_bit(काष्ठा mv88e6xxx_chip *chip,
					पूर्णांक base_reg, अचिन्हित पूर्णांक offset,
					पूर्णांक *set)
अणु
	पूर्णांक reg = base_reg + (offset / 8);
	u8 mask = (1 << (offset & 0x7));
	u8 val;
	पूर्णांक err;

	err = mv88e6xxx_g2_scratch_पढ़ो(chip, reg, &val);
	अगर (err)
		वापस err;

	*set = !!(mask & val);

	वापस 0;
पूर्ण

/**
 * mv88e6xxx_g2_scratch_set_bit - set (or clear) a bit
 * @chip: chip निजी data
 * @base_reg: base of scratch bits
 * @offset: index of bit within the रेजिस्टर
 * @set: should this bit be set?
 *
 * Helper function क्रम dealing with the direction and data रेजिस्टरs.
 */
अटल पूर्णांक mv88e6xxx_g2_scratch_set_bit(काष्ठा mv88e6xxx_chip *chip,
					पूर्णांक base_reg, अचिन्हित पूर्णांक offset,
					पूर्णांक set)
अणु
	पूर्णांक reg = base_reg + (offset / 8);
	u8 mask = (1 << (offset & 0x7));
	u8 val;
	पूर्णांक err;

	err = mv88e6xxx_g2_scratch_पढ़ो(chip, reg, &val);
	अगर (err)
		वापस err;

	अगर (set)
		val |= mask;
	अन्यथा
		val &= ~mask;

	वापस mv88e6xxx_g2_scratch_ग_लिखो(chip, reg, val);
पूर्ण

/**
 * mv88e6352_g2_scratch_gpio_get_data - get data on gpio pin
 * @chip: chip निजी data
 * @pin: gpio index
 *
 * Return: 0 क्रम low, 1 क्रम high, negative error
 */
अटल पूर्णांक mv88e6352_g2_scratch_gpio_get_data(काष्ठा mv88e6xxx_chip *chip,
					      अचिन्हित पूर्णांक pin)
अणु
	पूर्णांक val = 0;
	पूर्णांक err;

	err = mv88e6xxx_g2_scratch_get_bit(chip,
					   MV88E6352_G2_SCRATCH_GPIO_DATA0,
					   pin, &val);
	अगर (err)
		वापस err;

	वापस val;
पूर्ण

/**
 * mv88e6352_g2_scratch_gpio_set_data - set data on gpio pin
 * @chip: chip निजी data
 * @pin: gpio index
 * @value: value to set
 */
अटल पूर्णांक mv88e6352_g2_scratch_gpio_set_data(काष्ठा mv88e6xxx_chip *chip,
					      अचिन्हित पूर्णांक pin, पूर्णांक value)
अणु
	u8 mask = (1 << (pin & 0x7));
	पूर्णांक offset = (pin / 8);
	पूर्णांक reg;

	reg = MV88E6352_G2_SCRATCH_GPIO_DATA0 + offset;

	अगर (value)
		chip->gpio_data[offset] |= mask;
	अन्यथा
		chip->gpio_data[offset] &= ~mask;

	वापस mv88e6xxx_g2_scratch_ग_लिखो(chip, reg, chip->gpio_data[offset]);
पूर्ण

/**
 * mv88e6352_g2_scratch_gpio_get_dir - get direction of gpio pin
 * @chip: chip निजी data
 * @pin: gpio index
 *
 * Return: 0 क्रम output, 1 क्रम input (same as GPIOF_सूची_XXX).
 */
अटल पूर्णांक mv88e6352_g2_scratch_gpio_get_dir(काष्ठा mv88e6xxx_chip *chip,
					     अचिन्हित पूर्णांक pin)
अणु
	पूर्णांक val = 0;
	पूर्णांक err;

	err = mv88e6xxx_g2_scratch_get_bit(chip,
					   MV88E6352_G2_SCRATCH_GPIO_सूची0,
					   pin, &val);
	अगर (err)
		वापस err;

	वापस val;
पूर्ण

/**
 * mv88e6352_g2_scratch_gpio_set_dir - set direction of gpio pin
 * @chip: chip निजी data
 * @pin: gpio index
 * @input: should the gpio be an input, or an output?
 */
अटल पूर्णांक mv88e6352_g2_scratch_gpio_set_dir(काष्ठा mv88e6xxx_chip *chip,
					     अचिन्हित पूर्णांक pin, bool input)
अणु
	पूर्णांक value = (input ? MV88E6352_G2_SCRATCH_GPIO_सूची_IN :
			     MV88E6352_G2_SCRATCH_GPIO_सूची_OUT);

	वापस mv88e6xxx_g2_scratch_set_bit(chip,
					    MV88E6352_G2_SCRATCH_GPIO_सूची0,
					    pin, value);
पूर्ण

/**
 * mv88e6352_g2_scratch_gpio_get_pctl - get pin control setting
 * @chip: chip निजी data
 * @pin: gpio index
 * @func: function number
 *
 * Note that the function numbers themselves may vary by chipset.
 */
अटल पूर्णांक mv88e6352_g2_scratch_gpio_get_pctl(काष्ठा mv88e6xxx_chip *chip,
					      अचिन्हित पूर्णांक pin, पूर्णांक *func)
अणु
	पूर्णांक reg = MV88E6352_G2_SCRATCH_GPIO_PCTL0 + (pin / 2);
	पूर्णांक offset = (pin & 0x1) ? 4 : 0;
	u8 mask = (0x7 << offset);
	पूर्णांक err;
	u8 val;

	err = mv88e6xxx_g2_scratch_पढ़ो(chip, reg, &val);
	अगर (err)
		वापस err;

	*func = (val & mask) >> offset;

	वापस 0;
पूर्ण

/**
 * mv88e6352_g2_scratch_gpio_set_pctl - set pin control setting
 * @chip: chip निजी data
 * @pin: gpio index
 * @func: function number
 */
अटल पूर्णांक mv88e6352_g2_scratch_gpio_set_pctl(काष्ठा mv88e6xxx_chip *chip,
					      अचिन्हित पूर्णांक pin, पूर्णांक func)
अणु
	पूर्णांक reg = MV88E6352_G2_SCRATCH_GPIO_PCTL0 + (pin / 2);
	पूर्णांक offset = (pin & 0x1) ? 4 : 0;
	u8 mask = (0x7 << offset);
	पूर्णांक err;
	u8 val;

	err = mv88e6xxx_g2_scratch_पढ़ो(chip, reg, &val);
	अगर (err)
		वापस err;

	val = (val & ~mask) | ((func & mask) << offset);

	वापस mv88e6xxx_g2_scratch_ग_लिखो(chip, reg, val);
पूर्ण

स्थिर काष्ठा mv88e6xxx_gpio_ops mv88e6352_gpio_ops = अणु
	.get_data = mv88e6352_g2_scratch_gpio_get_data,
	.set_data = mv88e6352_g2_scratch_gpio_set_data,
	.get_dir = mv88e6352_g2_scratch_gpio_get_dir,
	.set_dir = mv88e6352_g2_scratch_gpio_set_dir,
	.get_pctl = mv88e6352_g2_scratch_gpio_get_pctl,
	.set_pctl = mv88e6352_g2_scratch_gpio_set_pctl,
पूर्ण;

/**
 * mv88e6xxx_g2_scratch_gpio_set_smi - set gpio muxing क्रम बाह्यal smi
 * @chip: chip निजी data
 * @बाह्यal: set mux क्रम बाह्यal smi, or मुक्त क्रम gpio usage
 *
 * Some mv88e6xxx models have GPIO pins that may be configured as
 * an बाह्यal SMI पूर्णांकerface, or they may be made मुक्त क्रम other
 * GPIO uses.
 */
पूर्णांक mv88e6xxx_g2_scratch_gpio_set_smi(काष्ठा mv88e6xxx_chip *chip,
				      bool बाह्यal)
अणु
	पूर्णांक misc_cfg = MV88E6352_G2_SCRATCH_MISC_CFG;
	पूर्णांक config_data1 = MV88E6352_G2_SCRATCH_CONFIG_DATA1;
	पूर्णांक config_data2 = MV88E6352_G2_SCRATCH_CONFIG_DATA2;
	bool no_cpu;
	u8 p0_mode;
	पूर्णांक err;
	u8 val;

	err = mv88e6xxx_g2_scratch_पढ़ो(chip, config_data2, &val);
	अगर (err)
		वापस err;

	p0_mode = val & MV88E6352_G2_SCRATCH_CONFIG_DATA2_P0_MODE_MASK;

	अगर (p0_mode == 0x01 || p0_mode == 0x02)
		वापस -EBUSY;

	err = mv88e6xxx_g2_scratch_पढ़ो(chip, config_data1, &val);
	अगर (err)
		वापस err;

	no_cpu = !!(val & MV88E6352_G2_SCRATCH_CONFIG_DATA1_NO_CPU);

	err = mv88e6xxx_g2_scratch_पढ़ो(chip, misc_cfg, &val);
	अगर (err)
		वापस err;

	/* NO_CPU being 0 inverts the meaning of the bit */
	अगर (!no_cpu)
		बाह्यal = !बाह्यal;

	अगर (बाह्यal)
		val |= MV88E6352_G2_SCRATCH_MISC_CFG_NORMALSMI;
	अन्यथा
		val &= ~MV88E6352_G2_SCRATCH_MISC_CFG_NORMALSMI;

	वापस mv88e6xxx_g2_scratch_ग_लिखो(chip, misc_cfg, val);
पूर्ण
