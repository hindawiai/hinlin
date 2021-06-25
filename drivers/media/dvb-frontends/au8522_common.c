<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
    Auvitek AU8522 QAM/8VSB demodulator driver

    Copyright (C) 2008 Steven Toth <stoth@linuxtv.org>
    Copyright (C) 2008 Devin Heiपंचांगueller <dheiपंचांगueller@linuxtv.org>
    Copyright (C) 2005-2008 Auvitek International, Ltd.
    Copyright (C) 2012 Michael Krufky <mkrufky@linuxtv.org>


*/

#समावेश <linux/i2c.h>
#समावेश <media/dvb_frontend.h>
#समावेश "au8522_priv.h"

अटल पूर्णांक debug;

#घोषणा dprपूर्णांकk(arg...)\
  करो अणु अगर (debug)\
	 prपूर्णांकk(arg);\
  पूर्ण जबतक (0)

/* Despite the name "hybrid_tuner", the framework works just as well क्रम
   hybrid demodulators as well... */
अटल LIST_HEAD(hybrid_tuner_instance_list);
अटल DEFINE_MUTEX(au8522_list_mutex);

/* 16 bit रेजिस्टरs, 8 bit values */
पूर्णांक au8522_ग_लिखोreg(काष्ठा au8522_state *state, u16 reg, u8 data)
अणु
	पूर्णांक ret;
	u8 buf[] = अणु (reg >> 8) | 0x80, reg & 0xff, data पूर्ण;

	काष्ठा i2c_msg msg = अणु .addr = state->config.demod_address,
			       .flags = 0, .buf = buf, .len = 3 पूर्ण;

	ret = i2c_transfer(state->i2c, &msg, 1);

	अगर (ret != 1)
		prपूर्णांकk("%s: writereg error (reg == 0x%02x, val == 0x%04x, ret == %i)\n",
		       __func__, reg, data, ret);

	वापस (ret != 1) ? -1 : 0;
पूर्ण
EXPORT_SYMBOL(au8522_ग_लिखोreg);

u8 au8522_पढ़ोreg(काष्ठा au8522_state *state, u16 reg)
अणु
	पूर्णांक ret;
	u8 b0[] = अणु (reg >> 8) | 0x40, reg & 0xff पूर्ण;
	u8 b1[] = अणु 0 पूर्ण;

	काष्ठा i2c_msg msg[] = अणु
		अणु .addr = state->config.demod_address, .flags = 0,
		  .buf = b0, .len = 2 पूर्ण,
		अणु .addr = state->config.demod_address, .flags = I2C_M_RD,
		  .buf = b1, .len = 1 पूर्ण पूर्ण;

	ret = i2c_transfer(state->i2c, msg, 2);

	अगर (ret != 2)
		prपूर्णांकk(KERN_ERR "%s: readreg error (ret == %i)\n",
		       __func__, ret);
	वापस b1[0];
पूर्ण
EXPORT_SYMBOL(au8522_पढ़ोreg);

पूर्णांक au8522_i2c_gate_ctrl(काष्ठा dvb_frontend *fe, पूर्णांक enable)
अणु
	काष्ठा au8522_state *state = fe->demodulator_priv;

	dprपूर्णांकk("%s(%d)\n", __func__, enable);

	अगर (state->operational_mode == AU8522_ANALOG_MODE) अणु
		/* We're being asked to manage the gate even though we're
		   not in digital mode.  This can occur अगर we get चयनed
		   over to analog mode beक्रमe the dvb_frontend kernel thपढ़ो
		   has completely shutकरोwn */
		वापस 0;
	पूर्ण

	अगर (enable)
		वापस au8522_ग_लिखोreg(state, 0x106, 1);
	अन्यथा
		वापस au8522_ग_लिखोreg(state, 0x106, 0);
पूर्ण
EXPORT_SYMBOL(au8522_i2c_gate_ctrl);

पूर्णांक au8522_analog_i2c_gate_ctrl(काष्ठा dvb_frontend *fe, पूर्णांक enable)
अणु
	काष्ठा au8522_state *state = fe->demodulator_priv;

	dprपूर्णांकk("%s(%d)\n", __func__, enable);

	अगर (enable)
		वापस au8522_ग_लिखोreg(state, 0x106, 1);
	अन्यथा
		वापस au8522_ग_लिखोreg(state, 0x106, 0);
पूर्ण
EXPORT_SYMBOL(au8522_analog_i2c_gate_ctrl);

/* Reset the demod hardware and reset all of the configuration रेजिस्टरs
   to a शेष state. */
पूर्णांक au8522_get_state(काष्ठा au8522_state **state, काष्ठा i2c_adapter *i2c,
		     u8 client_address)
अणु
	पूर्णांक ret;

	mutex_lock(&au8522_list_mutex);
	ret = hybrid_tuner_request_state(काष्ठा au8522_state, (*state),
					 hybrid_tuner_instance_list,
					 i2c, client_address, "au8522");
	mutex_unlock(&au8522_list_mutex);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(au8522_get_state);

व्योम au8522_release_state(काष्ठा au8522_state *state)
अणु
	mutex_lock(&au8522_list_mutex);
	अगर (state != शून्य)
		hybrid_tuner_release_state(state);
	mutex_unlock(&au8522_list_mutex);
पूर्ण
EXPORT_SYMBOL(au8522_release_state);

अटल पूर्णांक au8522_led_gpio_enable(काष्ठा au8522_state *state, पूर्णांक onoff)
अणु
	काष्ठा au8522_led_config *led_config = state->config.led_cfg;
	u8 val;

	/* bail out अगर we can't control an LED */
	अगर (!led_config || !led_config->gpio_output ||
	    !led_config->gpio_output_enable || !led_config->gpio_output_disable)
		वापस 0;

	val = au8522_पढ़ोreg(state, 0x4000 |
			     (led_config->gpio_output & ~0xc000));
	अगर (onoff) अणु
		/* enable GPIO output */
		val &= ~((led_config->gpio_output_enable >> 8) & 0xff);
		val |=  (led_config->gpio_output_enable & 0xff);
	पूर्ण अन्यथा अणु
		/* disable GPIO output */
		val &= ~((led_config->gpio_output_disable >> 8) & 0xff);
		val |=  (led_config->gpio_output_disable & 0xff);
	पूर्ण
	वापस au8522_ग_लिखोreg(state, 0x8000 |
			       (led_config->gpio_output & ~0xc000), val);
पूर्ण

/* led = 0 | off
 * led = 1 | संकेत ok
 * led = 2 | संकेत strong
 * led < 0 | only light led अगर leds are currently off
 */
पूर्णांक au8522_led_ctrl(काष्ठा au8522_state *state, पूर्णांक led)
अणु
	काष्ठा au8522_led_config *led_config = state->config.led_cfg;
	पूर्णांक i, ret = 0;

	/* bail out अगर we can't control an LED */
	अगर (!led_config || !led_config->gpio_leds ||
	    !led_config->num_led_states || !led_config->led_states)
		वापस 0;

	अगर (led < 0) अणु
		/* अगर LED is alपढ़ोy lit, then leave it as-is */
		अगर (state->led_state)
			वापस 0;
		अन्यथा
			led *= -1;
	पूर्ण

	/* toggle LED अगर changing state */
	अगर (state->led_state != led) अणु
		u8 val;

		dprपूर्णांकk("%s: %d\n", __func__, led);

		au8522_led_gpio_enable(state, 1);

		val = au8522_पढ़ोreg(state, 0x4000 |
				     (led_config->gpio_leds & ~0xc000));

		/* start with all leds off */
		क्रम (i = 0; i < led_config->num_led_states; i++)
			val &= ~led_config->led_states[i];

		/* set selected LED state */
		अगर (led < led_config->num_led_states)
			val |= led_config->led_states[led];
		अन्यथा अगर (led_config->num_led_states)
			val |=
			led_config->led_states[led_config->num_led_states - 1];

		ret = au8522_ग_लिखोreg(state, 0x8000 |
				      (led_config->gpio_leds & ~0xc000), val);
		अगर (ret < 0)
			वापस ret;

		state->led_state = led;

		अगर (led == 0)
			au8522_led_gpio_enable(state, 0);
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(au8522_led_ctrl);

पूर्णांक au8522_init(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा au8522_state *state = fe->demodulator_priv;
	dprपूर्णांकk("%s()\n", __func__);

	state->operational_mode = AU8522_DIGITAL_MODE;

	/* Clear out any state associated with the digital side of the
	   chip, so that when it माला_लो घातered back up it won't think
	   that it is alपढ़ोy tuned */
	state->current_frequency = 0;
	state->current_modulation = VSB_8;

	au8522_ग_लिखोreg(state, 0xa4, 1 << 5);

	au8522_i2c_gate_ctrl(fe, 1);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(au8522_init);

पूर्णांक au8522_sleep(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा au8522_state *state = fe->demodulator_priv;
	dprपूर्णांकk("%s()\n", __func__);

	/* Only घातer करोwn अगर the digital side is currently using the chip */
	अगर (state->operational_mode == AU8522_ANALOG_MODE) अणु
		/* We're not in one of the expected घातer modes, which means
		   that the DVB thपढ़ो is probably telling us to go to sleep
		   even though the analog frontend has alपढ़ोy started using
		   the chip.  So ignore the request */
		वापस 0;
	पूर्ण

	/* turn off led */
	au8522_led_ctrl(state, 0);

	/* Power करोwn the chip */
	au8522_ग_लिखोreg(state, 0xa4, 1 << 5);

	state->current_frequency = 0;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(au8522_sleep);

module_param(debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug, "Enable verbose debug messages");

MODULE_DESCRIPTION("Auvitek AU8522 QAM-B/ATSC Demodulator driver");
MODULE_AUTHOR("Steven Toth");
MODULE_LICENSE("GPL");
