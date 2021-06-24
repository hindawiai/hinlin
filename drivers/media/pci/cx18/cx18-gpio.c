<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  cx18 gpio functions
 *
 *  Derived from ivtv-gpio.c
 *
 *  Copyright (C) 2007  Hans Verkuil <hverkuil@xs4all.nl>
 *  Copyright (C) 2008  Andy Walls <awalls@md.metrocast.net>
 */

#समावेश "cx18-driver.h"
#समावेश "cx18-io.h"
#समावेश "cx18-cards.h"
#समावेश "cx18-gpio.h"
#समावेश "tuner-xc2028.h"

/********************* GPIO stuffs *********************/

/* GPIO रेजिस्टरs */
#घोषणा CX18_REG_GPIO_IN     0xc72010
#घोषणा CX18_REG_GPIO_OUT1   0xc78100
#घोषणा CX18_REG_GPIO_सूची1   0xc78108
#घोषणा CX18_REG_GPIO_OUT2   0xc78104
#घोषणा CX18_REG_GPIO_सूची2   0xc7810c

/*
 * HVR-1600 GPIO pins, courtesy of Hauppauge:
 *
 * gpio0: zilog ir process reset pin
 * gpio1: zilog programming pin (you should never use this)
 * gpio12: cx24227 reset pin
 * gpio13: cs5345 reset pin
*/

/*
 * File scope utility functions
 */
अटल व्योम gpio_ग_लिखो(काष्ठा cx18 *cx)
अणु
	u32 dir_lo = cx->gpio_dir & 0xffff;
	u32 val_lo = cx->gpio_val & 0xffff;
	u32 dir_hi = cx->gpio_dir >> 16;
	u32 val_hi = cx->gpio_val >> 16;

	cx18_ग_लिखो_reg_expect(cx, dir_lo << 16,
					CX18_REG_GPIO_सूची1, ~dir_lo, dir_lo);
	cx18_ग_लिखो_reg_expect(cx, (dir_lo << 16) | val_lo,
					CX18_REG_GPIO_OUT1, val_lo, dir_lo);
	cx18_ग_लिखो_reg_expect(cx, dir_hi << 16,
					CX18_REG_GPIO_सूची2, ~dir_hi, dir_hi);
	cx18_ग_लिखो_reg_expect(cx, (dir_hi << 16) | val_hi,
					CX18_REG_GPIO_OUT2, val_hi, dir_hi);
पूर्ण

अटल व्योम gpio_update(काष्ठा cx18 *cx, u32 mask, u32 data)
अणु
	अगर (mask == 0)
		वापस;

	mutex_lock(&cx->gpio_lock);
	cx->gpio_val = (cx->gpio_val & ~mask) | (data & mask);
	gpio_ग_लिखो(cx);
	mutex_unlock(&cx->gpio_lock);
पूर्ण

अटल व्योम gpio_reset_seq(काष्ठा cx18 *cx, u32 active_lo, u32 active_hi,
			   अचिन्हित पूर्णांक निश्चित_msecs,
			   अचिन्हित पूर्णांक recovery_msecs)
अणु
	u32 mask;

	mask = active_lo | active_hi;
	अगर (mask == 0)
		वापस;

	/*
	 * Assuming that active_hi and active_lo are a subsets of the bits in
	 * gpio_dir.  Also assumes that active_lo and active_hi करोn't overlap
	 * in any bit position
	 */

	/* Assert */
	gpio_update(cx, mask, ~active_lo);
	schedule_समयout_unपूर्णांकerruptible(msecs_to_jअगरfies(निश्चित_msecs));

	/* Deनिश्चित */
	gpio_update(cx, mask, ~active_hi);
	schedule_समयout_unपूर्णांकerruptible(msecs_to_jअगरfies(recovery_msecs));
पूर्ण

/*
 * GPIO Multiplexer - logical device
 */
अटल पूर्णांक gpiomux_log_status(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा cx18 *cx = v4l2_get_subdevdata(sd);

	mutex_lock(&cx->gpio_lock);
	CX18_INFO_DEV(sd, "GPIO:  direction 0x%08x, value 0x%08x\n",
		      cx->gpio_dir, cx->gpio_val);
	mutex_unlock(&cx->gpio_lock);
	वापस 0;
पूर्ण

अटल पूर्णांक gpiomux_s_radio(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा cx18 *cx = v4l2_get_subdevdata(sd);

	/*
	 * FIXME - work out the cx->active/audio_input mess - this is
	 * पूर्णांकended to handle the चयन to radio mode and set the
	 * audio routing, but we need to update the state in cx
	 */
	gpio_update(cx, cx->card->gpio_audio_input.mask,
			cx->card->gpio_audio_input.radio);
	वापस 0;
पूर्ण

अटल पूर्णांक gpiomux_s_std(काष्ठा v4l2_subdev *sd, v4l2_std_id norm)
अणु
	काष्ठा cx18 *cx = v4l2_get_subdevdata(sd);
	u32 data;

	चयन (cx->card->audio_inमाला_दो[cx->audio_input].muxer_input) अणु
	हाल 1:
		data = cx->card->gpio_audio_input.linein;
		अवरोध;
	हाल 0:
		data = cx->card->gpio_audio_input.tuner;
		अवरोध;
	शेष:
		/*
		 * FIXME - work out the cx->active/audio_input mess - this is
		 * पूर्णांकended to handle the चयन from radio mode and set the
		 * audio routing, but we need to update the state in cx
		 */
		data = cx->card->gpio_audio_input.tuner;
		अवरोध;
	पूर्ण
	gpio_update(cx, cx->card->gpio_audio_input.mask, data);
	वापस 0;
पूर्ण

अटल पूर्णांक gpiomux_s_audio_routing(काष्ठा v4l2_subdev *sd,
				   u32 input, u32 output, u32 config)
अणु
	काष्ठा cx18 *cx = v4l2_get_subdevdata(sd);
	u32 data;

	चयन (input) अणु
	हाल 0:
		data = cx->card->gpio_audio_input.tuner;
		अवरोध;
	हाल 1:
		data = cx->card->gpio_audio_input.linein;
		अवरोध;
	हाल 2:
		data = cx->card->gpio_audio_input.radio;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	gpio_update(cx, cx->card->gpio_audio_input.mask, data);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_subdev_core_ops gpiomux_core_ops = अणु
	.log_status = gpiomux_log_status,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_tuner_ops gpiomux_tuner_ops = अणु
	.s_radio = gpiomux_s_radio,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_audio_ops gpiomux_audio_ops = अणु
	.s_routing = gpiomux_s_audio_routing,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_video_ops gpiomux_video_ops = अणु
	.s_std = gpiomux_s_std,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ops gpiomux_ops = अणु
	.core = &gpiomux_core_ops,
	.tuner = &gpiomux_tuner_ops,
	.audio = &gpiomux_audio_ops,
	.video = &gpiomux_video_ops,
पूर्ण;

/*
 * GPIO Reset Controller - logical device
 */
अटल पूर्णांक resetctrl_log_status(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा cx18 *cx = v4l2_get_subdevdata(sd);

	mutex_lock(&cx->gpio_lock);
	CX18_INFO_DEV(sd, "GPIO:  direction 0x%08x, value 0x%08x\n",
		      cx->gpio_dir, cx->gpio_val);
	mutex_unlock(&cx->gpio_lock);
	वापस 0;
पूर्ण

अटल पूर्णांक resetctrl_reset(काष्ठा v4l2_subdev *sd, u32 val)
अणु
	काष्ठा cx18 *cx = v4l2_get_subdevdata(sd);
	स्थिर काष्ठा cx18_gpio_i2c_slave_reset *p;

	p = &cx->card->gpio_i2c_slave_reset;
	चयन (val) अणु
	हाल CX18_GPIO_RESET_I2C:
		gpio_reset_seq(cx, p->active_lo_mask, p->active_hi_mask,
			       p->msecs_निश्चितed, p->msecs_recovery);
		अवरोध;
	हाल CX18_GPIO_RESET_Z8F0811:
		/*
		 * Assert timing क्रम the Z8F0811 on HVR-1600 boards:
		 * 1. Assert RESET क्रम min of 4 घड़ी cycles at 18.432 MHz to
		 *    initiate
		 * 2. Reset then takes 66 WDT cycles at 10 kHz + 16 xtal घड़ी
		 *    cycles (6,601,085 nanoseconds ~= 7 milliseconds)
		 * 3. DBG pin must be high beक्रमe chip निकासs reset क्रम normal
		 *    operation.  DBG is खोलो drain and hopefully pulled high
		 *    since we करोn't normally drive it (GPIO 1?) क्रम the
		 *    HVR-1600
		 * 4. Z8F0811 won't निकास reset until RESET is deनिश्चितed
		 * 5. Zilog comes out of reset, loads reset vector address and
		 *    executes from there. Required recovery delay unknown.
		 */
		gpio_reset_seq(cx, p->ir_reset_mask, 0,
			       p->msecs_निश्चितed, p->msecs_recovery);
		अवरोध;
	हाल CX18_GPIO_RESET_XC2028:
		अगर (cx->card->tuners[0].tuner == TUNER_XC2028)
			gpio_reset_seq(cx, (1 << cx->card->xceive_pin), 0,
				       1, 1);
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_subdev_core_ops resetctrl_core_ops = अणु
	.log_status = resetctrl_log_status,
	.reset = resetctrl_reset,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ops resetctrl_ops = अणु
	.core = &resetctrl_core_ops,
पूर्ण;

/*
 * External entry poपूर्णांकs
 */
व्योम cx18_gpio_init(काष्ठा cx18 *cx)
अणु
	mutex_lock(&cx->gpio_lock);
	cx->gpio_dir = cx->card->gpio_init.direction;
	cx->gpio_val = cx->card->gpio_init.initial_value;

	अगर (cx->card->tuners[0].tuner == TUNER_XC2028) अणु
		cx->gpio_dir |= 1 << cx->card->xceive_pin;
		cx->gpio_val |= 1 << cx->card->xceive_pin;
	पूर्ण

	अगर (cx->gpio_dir == 0) अणु
		mutex_unlock(&cx->gpio_lock);
		वापस;
	पूर्ण

	CX18_DEBUG_INFO("GPIO initial dir: %08x/%08x out: %08x/%08x\n",
			cx18_पढ़ो_reg(cx, CX18_REG_GPIO_सूची1),
			cx18_पढ़ो_reg(cx, CX18_REG_GPIO_सूची2),
			cx18_पढ़ो_reg(cx, CX18_REG_GPIO_OUT1),
			cx18_पढ़ो_reg(cx, CX18_REG_GPIO_OUT2));

	gpio_ग_लिखो(cx);
	mutex_unlock(&cx->gpio_lock);
पूर्ण

पूर्णांक cx18_gpio_रेजिस्टर(काष्ठा cx18 *cx, u32 hw)
अणु
	काष्ठा v4l2_subdev *sd;
	स्थिर काष्ठा v4l2_subdev_ops *ops;
	अक्षर *str;

	चयन (hw) अणु
	हाल CX18_HW_GPIO_MUX:
		sd = &cx->sd_gpiomux;
		ops = &gpiomux_ops;
		str = "gpio-mux";
		अवरोध;
	हाल CX18_HW_GPIO_RESET_CTRL:
		sd = &cx->sd_resetctrl;
		ops = &resetctrl_ops;
		str = "gpio-reset-ctrl";
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	v4l2_subdev_init(sd, ops);
	v4l2_set_subdevdata(sd, cx);
	snम_लिखो(sd->name, माप(sd->name), "%s %s", cx->v4l2_dev.name, str);
	sd->grp_id = hw;
	वापस v4l2_device_रेजिस्टर_subdev(&cx->v4l2_dev, sd);
पूर्ण

व्योम cx18_reset_ir_gpio(व्योम *data)
अणु
	काष्ठा cx18 *cx = to_cx18((काष्ठा v4l2_device *)data);

	अगर (cx->card->gpio_i2c_slave_reset.ir_reset_mask == 0)
		वापस;

	CX18_DEBUG_INFO("Resetting IR microcontroller\n");

	v4l2_subdev_call(&cx->sd_resetctrl,
			 core, reset, CX18_GPIO_RESET_Z8F0811);
पूर्ण
EXPORT_SYMBOL(cx18_reset_ir_gpio);
/* This symbol is exported क्रम use by lirc_pvr150 क्रम the IR-blaster */

/* Xceive tuner reset function */
पूर्णांक cx18_reset_tuner_gpio(व्योम *dev, पूर्णांक component, पूर्णांक cmd, पूर्णांक value)
अणु
	काष्ठा i2c_algo_bit_data *algo = dev;
	काष्ठा cx18_i2c_algo_callback_data *cb_data = algo->data;
	काष्ठा cx18 *cx = cb_data->cx;

	अगर (cmd != XC2028_TUNER_RESET ||
	    cx->card->tuners[0].tuner != TUNER_XC2028)
		वापस 0;

	CX18_DEBUG_INFO("Resetting XCeive tuner\n");
	वापस v4l2_subdev_call(&cx->sd_resetctrl,
				core, reset, CX18_GPIO_RESET_XC2028);
पूर्ण
