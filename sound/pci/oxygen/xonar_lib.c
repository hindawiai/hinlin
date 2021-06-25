<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * helper functions क्रम Asus Xonar cards
 *
 * Copyright (c) Clemens Ladisch <clemens@ladisch.de>
 */

#समावेश <linux/delay.h>
#समावेश <sound/core.h>
#समावेश <sound/control.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश "xonar.h"


#घोषणा GPIO_CS53x1_M_MASK	0x000c
#घोषणा GPIO_CS53x1_M_SINGLE	0x0000
#घोषणा GPIO_CS53x1_M_DOUBLE	0x0004
#घोषणा GPIO_CS53x1_M_QUAD	0x0008


व्योम xonar_enable_output(काष्ठा oxygen *chip)
अणु
	काष्ठा xonar_generic *data = chip->model_data;

	oxygen_set_bits16(chip, OXYGEN_GPIO_CONTROL, data->output_enable_bit);
	msleep(data->anti_pop_delay);
	oxygen_set_bits16(chip, OXYGEN_GPIO_DATA, data->output_enable_bit);
पूर्ण

व्योम xonar_disable_output(काष्ठा oxygen *chip)
अणु
	काष्ठा xonar_generic *data = chip->model_data;

	oxygen_clear_bits16(chip, OXYGEN_GPIO_DATA, data->output_enable_bit);
पूर्ण

अटल व्योम xonar_ext_घातer_gpio_changed(काष्ठा oxygen *chip)
अणु
	काष्ठा xonar_generic *data = chip->model_data;
	u8 has_घातer;

	has_घातer = !!(oxygen_पढ़ो8(chip, data->ext_घातer_reg)
		       & data->ext_घातer_bit);
	अगर (has_घातer != data->has_घातer) अणु
		data->has_घातer = has_घातer;
		अगर (has_घातer) अणु
			dev_notice(chip->card->dev, "power restored\n");
		पूर्ण अन्यथा अणु
			dev_crit(chip->card->dev,
				   "Hey! Don't unplug the power cable!\n");
			/* TODO: stop PCMs */
		पूर्ण
	पूर्ण
पूर्ण

व्योम xonar_init_ext_घातer(काष्ठा oxygen *chip)
अणु
	काष्ठा xonar_generic *data = chip->model_data;

	oxygen_set_bits8(chip, data->ext_घातer_पूर्णांक_reg,
			 data->ext_घातer_bit);
	chip->पूर्णांकerrupt_mask |= OXYGEN_INT_GPIO;
	chip->model.gpio_changed = xonar_ext_घातer_gpio_changed;
	data->has_घातer = !!(oxygen_पढ़ो8(chip, data->ext_घातer_reg)
			     & data->ext_घातer_bit);
पूर्ण

व्योम xonar_init_cs53x1(काष्ठा oxygen *chip)
अणु
	oxygen_set_bits16(chip, OXYGEN_GPIO_CONTROL, GPIO_CS53x1_M_MASK);
	oxygen_ग_लिखो16_masked(chip, OXYGEN_GPIO_DATA,
			      GPIO_CS53x1_M_SINGLE, GPIO_CS53x1_M_MASK);
पूर्ण

व्योम xonar_set_cs53x1_params(काष्ठा oxygen *chip,
			     काष्ठा snd_pcm_hw_params *params)
अणु
	अचिन्हित पूर्णांक value;

	अगर (params_rate(params) <= 54000)
		value = GPIO_CS53x1_M_SINGLE;
	अन्यथा अगर (params_rate(params) <= 108000)
		value = GPIO_CS53x1_M_DOUBLE;
	अन्यथा
		value = GPIO_CS53x1_M_QUAD;
	oxygen_ग_लिखो16_masked(chip, OXYGEN_GPIO_DATA,
			      value, GPIO_CS53x1_M_MASK);
पूर्ण

पूर्णांक xonar_gpio_bit_चयन_get(काष्ठा snd_kcontrol *ctl,
			      काष्ठा snd_ctl_elem_value *value)
अणु
	काष्ठा oxygen *chip = ctl->निजी_data;
	u16 bit = ctl->निजी_value;
	bool invert = ctl->निजी_value & XONAR_GPIO_BIT_INVERT;

	value->value.पूर्णांकeger.value[0] =
		!!(oxygen_पढ़ो16(chip, OXYGEN_GPIO_DATA) & bit) ^ invert;
	वापस 0;
पूर्ण

पूर्णांक xonar_gpio_bit_चयन_put(काष्ठा snd_kcontrol *ctl,
			      काष्ठा snd_ctl_elem_value *value)
अणु
	काष्ठा oxygen *chip = ctl->निजी_data;
	u16 bit = ctl->निजी_value;
	bool invert = ctl->निजी_value & XONAR_GPIO_BIT_INVERT;
	u16 old_bits, new_bits;
	पूर्णांक changed;

	spin_lock_irq(&chip->reg_lock);
	old_bits = oxygen_पढ़ो16(chip, OXYGEN_GPIO_DATA);
	अगर (!!value->value.पूर्णांकeger.value[0] ^ invert)
		new_bits = old_bits | bit;
	अन्यथा
		new_bits = old_bits & ~bit;
	changed = new_bits != old_bits;
	अगर (changed)
		oxygen_ग_लिखो16(chip, OXYGEN_GPIO_DATA, new_bits);
	spin_unlock_irq(&chip->reg_lock);
	वापस changed;
पूर्ण
