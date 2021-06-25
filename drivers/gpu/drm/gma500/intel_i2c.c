<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright तऊ 2006-2007 Intel Corporation
 *
 * Authors:
 *	Eric Anholt <eric@anholt.net>
 */

#समावेश <linux/delay.h>
#समावेश <linux/export.h>
#समावेश <linux/i2c-algo-bit.h>
#समावेश <linux/i2c.h>

#समावेश "psb_drv.h"
#समावेश "psb_intel_reg.h"

/*
 * Intel GPIO access functions
 */

#घोषणा I2C_RISEFALL_TIME 20

अटल पूर्णांक get_घड़ी(व्योम *data)
अणु
	काष्ठा psb_पूर्णांकel_i2c_chan *chan = data;
	काष्ठा drm_device *dev = chan->drm_dev;
	u32 val;

	val = REG_READ(chan->reg);
	वापस (val & GPIO_CLOCK_VAL_IN) != 0;
पूर्ण

अटल पूर्णांक get_data(व्योम *data)
अणु
	काष्ठा psb_पूर्णांकel_i2c_chan *chan = data;
	काष्ठा drm_device *dev = chan->drm_dev;
	u32 val;

	val = REG_READ(chan->reg);
	वापस (val & GPIO_DATA_VAL_IN) != 0;
पूर्ण

अटल व्योम set_घड़ी(व्योम *data, पूर्णांक state_high)
अणु
	काष्ठा psb_पूर्णांकel_i2c_chan *chan = data;
	काष्ठा drm_device *dev = chan->drm_dev;
	u32 reserved = 0, घड़ी_bits;

	/* On most chips, these bits must be preserved in software. */
	reserved =
		    REG_READ(chan->reg) & (GPIO_DATA_PULLUP_DISABLE |
					   GPIO_CLOCK_PULLUP_DISABLE);

	अगर (state_high)
		घड़ी_bits = GPIO_CLOCK_सूची_IN | GPIO_CLOCK_सूची_MASK;
	अन्यथा
		घड़ी_bits = GPIO_CLOCK_सूची_OUT | GPIO_CLOCK_सूची_MASK |
		    GPIO_CLOCK_VAL_MASK;
	REG_WRITE(chan->reg, reserved | घड़ी_bits);
	udelay(I2C_RISEFALL_TIME);	/* रुको क्रम the line to change state */
पूर्ण

अटल व्योम set_data(व्योम *data, पूर्णांक state_high)
अणु
	काष्ठा psb_पूर्णांकel_i2c_chan *chan = data;
	काष्ठा drm_device *dev = chan->drm_dev;
	u32 reserved = 0, data_bits;

	/* On most chips, these bits must be preserved in software. */
	reserved =
		    REG_READ(chan->reg) & (GPIO_DATA_PULLUP_DISABLE |
					   GPIO_CLOCK_PULLUP_DISABLE);

	अगर (state_high)
		data_bits = GPIO_DATA_सूची_IN | GPIO_DATA_सूची_MASK;
	अन्यथा
		data_bits =
		    GPIO_DATA_सूची_OUT | GPIO_DATA_सूची_MASK |
		    GPIO_DATA_VAL_MASK;

	REG_WRITE(chan->reg, reserved | data_bits);
	udelay(I2C_RISEFALL_TIME);	/* रुको क्रम the line to change state */
पूर्ण

/**
 * psb_पूर्णांकel_i2c_create - instantiate an Intel i2c bus using the specअगरied GPIO reg
 * @dev: DRM device
 * @reg: GPIO reg to use
 * @name: name क्रम this bus
 *
 * Creates and रेजिस्टरs a new i2c bus with the Linux i2c layer, क्रम use
 * in output probing and control (e.g. DDC or SDVO control functions).
 *
 * Possible values क्रम @reg include:
 *   %GPIOA
 *   %GPIOB
 *   %GPIOC
 *   %GPIOD
 *   %GPIOE
 *   %GPIOF
 *   %GPIOG
 *   %GPIOH
 * see PRM क्रम details on how these dअगरferent busses are used.
 */
काष्ठा psb_पूर्णांकel_i2c_chan *psb_पूर्णांकel_i2c_create(काष्ठा drm_device *dev,
					स्थिर u32 reg, स्थिर अक्षर *name)
अणु
	काष्ठा psb_पूर्णांकel_i2c_chan *chan;

	chan = kzalloc(माप(काष्ठा psb_पूर्णांकel_i2c_chan), GFP_KERNEL);
	अगर (!chan)
		जाओ out_मुक्त;

	chan->drm_dev = dev;
	chan->reg = reg;
	snम_लिखो(chan->adapter.name, I2C_NAME_SIZE, "intel drm %s", name);
	chan->adapter.owner = THIS_MODULE;
	chan->adapter.algo_data = &chan->algo;
	chan->adapter.dev.parent = dev->dev;
	chan->algo.setsda = set_data;
	chan->algo.setscl = set_घड़ी;
	chan->algo.माला_लोda = get_data;
	chan->algo.माला_लोcl = get_घड़ी;
	chan->algo.udelay = 20;
	chan->algo.समयout = usecs_to_jअगरfies(2200);
	chan->algo.data = chan;

	i2c_set_adapdata(&chan->adapter, chan);

	अगर (i2c_bit_add_bus(&chan->adapter))
		जाओ out_मुक्त;

	/* JJJ:  उठाओ SCL and SDA? */
	set_data(chan, 1);
	set_घड़ी(chan, 1);
	udelay(20);

	वापस chan;

out_मुक्त:
	kमुक्त(chan);
	वापस शून्य;
पूर्ण

/**
 * psb_पूर्णांकel_i2c_destroy - unरेजिस्टर and मुक्त i2c bus resources
 * @chan: channel to मुक्त
 *
 * Unरेजिस्टर the adapter from the i2c layer, then मुक्त the काष्ठाure.
 */
व्योम psb_पूर्णांकel_i2c_destroy(काष्ठा psb_पूर्णांकel_i2c_chan *chan)
अणु
	अगर (!chan)
		वापस;

	i2c_del_adapter(&chan->adapter);
	kमुक्त(chan);
पूर्ण
