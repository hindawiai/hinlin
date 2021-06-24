<शैली गुरु>
/*
 * Copyright (c) 2006 Dave Airlie <airlied@linux.ie>
 * Copyright तऊ 2006-2008,2010 Intel Corporation
 *   Jesse Barnes <jesse.barnes@पूर्णांकel.com>
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 * Authors:
 *	Eric Anholt <eric@anholt.net>
 *	Chris Wilson <chris@chris-wilson.co.uk>
 */

#समावेश <linux/delay.h>
#समावेश <linux/i2c-algo-bit.h>
#समावेश <linux/i2c.h>
#समावेश <linux/module.h>

#समावेश "psb_drv.h"
#समावेश "psb_intel_drv.h"
#समावेश "psb_intel_reg.h"

#घोषणा _रुको_क्रम(COND, MS, W) (अणु \
	अचिन्हित दीर्घ समयout__ = jअगरfies + msecs_to_jअगरfies(MS);	\
	पूर्णांक ret__ = 0;							\
	जबतक (! (COND)) अणु						\
		अगर (समय_after(jअगरfies, समयout__)) अणु			\
			ret__ = -ETIMEDOUT;				\
			अवरोध;						\
		पूर्ण							\
		अगर (W && !(in_dbg_master()))				\
			msleep(W);					\
	पूर्ण								\
	ret__;								\
पूर्ण)

#घोषणा रुको_क्रम(COND, MS) _रुको_क्रम(COND, MS, 1)

#घोषणा GMBUS_REG_READ(reg) ioपढ़ो32(dev_priv->gmbus_reg + (reg))
#घोषणा GMBUS_REG_WRITE(reg, val) ioग_लिखो32((val), dev_priv->gmbus_reg + (reg))

/* Intel GPIO access functions */

#घोषणा I2C_RISEFALL_TIME 20

अटल अंतरभूत काष्ठा पूर्णांकel_gmbus *
to_पूर्णांकel_gmbus(काष्ठा i2c_adapter *i2c)
अणु
	वापस container_of(i2c, काष्ठा पूर्णांकel_gmbus, adapter);
पूर्ण

काष्ठा पूर्णांकel_gpio अणु
	काष्ठा i2c_adapter adapter;
	काष्ठा i2c_algo_bit_data algo;
	काष्ठा drm_psb_निजी *dev_priv;
	u32 reg;
पूर्ण;

व्योम
gma_पूर्णांकel_i2c_reset(काष्ठा drm_device *dev)
अणु
	काष्ठा drm_psb_निजी *dev_priv = dev->dev_निजी;
	GMBUS_REG_WRITE(GMBUS0, 0);
पूर्ण

अटल व्योम पूर्णांकel_i2c_quirk_set(काष्ठा drm_psb_निजी *dev_priv, bool enable)
अणु
	/* When using bit bashing क्रम I2C, this bit needs to be set to 1 */
	/* FIXME: We are never Pineview, right?

	u32 val;

	अगर (!IS_PINEVIEW(dev_priv->dev))
		वापस;

	val = REG_READ(DSPCLK_GATE_D);
	अगर (enable)
		val |= DPCUNIT_CLOCK_GATE_DISABLE;
	अन्यथा
		val &= ~DPCUNIT_CLOCK_GATE_DISABLE;
	REG_WRITE(DSPCLK_GATE_D, val);

	वापस;
	*/
पूर्ण

अटल u32 get_reserved(काष्ठा पूर्णांकel_gpio *gpio)
अणु
	काष्ठा drm_psb_निजी *dev_priv = gpio->dev_priv;
	u32 reserved = 0;

	/* On most chips, these bits must be preserved in software. */
	reserved = GMBUS_REG_READ(gpio->reg) &
				     (GPIO_DATA_PULLUP_DISABLE |
				      GPIO_CLOCK_PULLUP_DISABLE);

	वापस reserved;
पूर्ण

अटल पूर्णांक get_घड़ी(व्योम *data)
अणु
	काष्ठा पूर्णांकel_gpio *gpio = data;
	काष्ठा drm_psb_निजी *dev_priv = gpio->dev_priv;
	u32 reserved = get_reserved(gpio);
	GMBUS_REG_WRITE(gpio->reg, reserved | GPIO_CLOCK_सूची_MASK);
	GMBUS_REG_WRITE(gpio->reg, reserved);
	वापस (GMBUS_REG_READ(gpio->reg) & GPIO_CLOCK_VAL_IN) != 0;
पूर्ण

अटल पूर्णांक get_data(व्योम *data)
अणु
	काष्ठा पूर्णांकel_gpio *gpio = data;
	काष्ठा drm_psb_निजी *dev_priv = gpio->dev_priv;
	u32 reserved = get_reserved(gpio);
	GMBUS_REG_WRITE(gpio->reg, reserved | GPIO_DATA_सूची_MASK);
	GMBUS_REG_WRITE(gpio->reg, reserved);
	वापस (GMBUS_REG_READ(gpio->reg) & GPIO_DATA_VAL_IN) != 0;
पूर्ण

अटल व्योम set_घड़ी(व्योम *data, पूर्णांक state_high)
अणु
	काष्ठा पूर्णांकel_gpio *gpio = data;
	काष्ठा drm_psb_निजी *dev_priv = gpio->dev_priv;
	u32 reserved = get_reserved(gpio);
	u32 घड़ी_bits;

	अगर (state_high)
		घड़ी_bits = GPIO_CLOCK_सूची_IN | GPIO_CLOCK_सूची_MASK;
	अन्यथा
		घड़ी_bits = GPIO_CLOCK_सूची_OUT | GPIO_CLOCK_सूची_MASK |
			GPIO_CLOCK_VAL_MASK;

	GMBUS_REG_WRITE(gpio->reg, reserved | घड़ी_bits);
	GMBUS_REG_READ(gpio->reg); /* Posting */
पूर्ण

अटल व्योम set_data(व्योम *data, पूर्णांक state_high)
अणु
	काष्ठा पूर्णांकel_gpio *gpio = data;
	काष्ठा drm_psb_निजी *dev_priv = gpio->dev_priv;
	u32 reserved = get_reserved(gpio);
	u32 data_bits;

	अगर (state_high)
		data_bits = GPIO_DATA_सूची_IN | GPIO_DATA_सूची_MASK;
	अन्यथा
		data_bits = GPIO_DATA_सूची_OUT | GPIO_DATA_सूची_MASK |
			GPIO_DATA_VAL_MASK;

	GMBUS_REG_WRITE(gpio->reg, reserved | data_bits);
	GMBUS_REG_READ(gpio->reg);
पूर्ण

अटल काष्ठा i2c_adapter *
पूर्णांकel_gpio_create(काष्ठा drm_psb_निजी *dev_priv, u32 pin)
अणु
	अटल स्थिर पूर्णांक map_pin_to_reg[] = अणु
		0,
		GPIOB,
		GPIOA,
		GPIOC,
		GPIOD,
		GPIOE,
		0,
		GPIOF,
	पूर्ण;
	काष्ठा पूर्णांकel_gpio *gpio;

	अगर (pin >= ARRAY_SIZE(map_pin_to_reg) || !map_pin_to_reg[pin])
		वापस शून्य;

	gpio = kzalloc(माप(काष्ठा पूर्णांकel_gpio), GFP_KERNEL);
	अगर (gpio == शून्य)
		वापस शून्य;

	gpio->reg = map_pin_to_reg[pin];
	gpio->dev_priv = dev_priv;

	snम_लिखो(gpio->adapter.name, माप(gpio->adapter.name),
		 "gma500 GPIO%c", "?BACDE?F"[pin]);
	gpio->adapter.owner = THIS_MODULE;
	gpio->adapter.algo_data	= &gpio->algo;
	gpio->adapter.dev.parent = dev_priv->dev->dev;
	gpio->algo.setsda = set_data;
	gpio->algo.setscl = set_घड़ी;
	gpio->algo.माला_लोda = get_data;
	gpio->algo.माला_लोcl = get_घड़ी;
	gpio->algo.udelay = I2C_RISEFALL_TIME;
	gpio->algo.समयout = usecs_to_jअगरfies(2200);
	gpio->algo.data = gpio;

	अगर (i2c_bit_add_bus(&gpio->adapter))
		जाओ out_मुक्त;

	वापस &gpio->adapter;

out_मुक्त:
	kमुक्त(gpio);
	वापस शून्य;
पूर्ण

अटल पूर्णांक
पूर्णांकel_i2c_quirk_xfer(काष्ठा drm_psb_निजी *dev_priv,
		     काष्ठा i2c_adapter *adapter,
		     काष्ठा i2c_msg *msgs,
		     पूर्णांक num)
अणु
	काष्ठा पूर्णांकel_gpio *gpio = container_of(adapter,
					       काष्ठा पूर्णांकel_gpio,
					       adapter);
	पूर्णांक ret;

	gma_पूर्णांकel_i2c_reset(dev_priv->dev);

	पूर्णांकel_i2c_quirk_set(dev_priv, true);
	set_data(gpio, 1);
	set_घड़ी(gpio, 1);
	udelay(I2C_RISEFALL_TIME);

	ret = adapter->algo->master_xfer(adapter, msgs, num);

	set_data(gpio, 1);
	set_घड़ी(gpio, 1);
	पूर्णांकel_i2c_quirk_set(dev_priv, false);

	वापस ret;
पूर्ण

अटल पूर्णांक
gmbus_xfer(काष्ठा i2c_adapter *adapter,
	   काष्ठा i2c_msg *msgs,
	   पूर्णांक num)
अणु
	काष्ठा पूर्णांकel_gmbus *bus = container_of(adapter,
					       काष्ठा पूर्णांकel_gmbus,
					       adapter);
	काष्ठा drm_psb_निजी *dev_priv = adapter->algo_data;
	पूर्णांक i, reg_offset;

	अगर (bus->क्रमce_bit)
		वापस पूर्णांकel_i2c_quirk_xfer(dev_priv,
					    bus->क्रमce_bit, msgs, num);

	reg_offset = 0;

	GMBUS_REG_WRITE(GMBUS0 + reg_offset, bus->reg0);

	क्रम (i = 0; i < num; i++) अणु
		u16 len = msgs[i].len;
		u8 *buf = msgs[i].buf;

		अगर (msgs[i].flags & I2C_M_RD) अणु
			GMBUS_REG_WRITE(GMBUS1 + reg_offset,
					GMBUS_CYCLE_WAIT |
					(i + 1 == num ? GMBUS_CYCLE_STOP : 0) |
					(len << GMBUS_BYTE_COUNT_SHIFT) |
					(msgs[i].addr << GMBUS_SLAVE_ADDR_SHIFT) |
					GMBUS_SLAVE_READ | GMBUS_SW_RDY);
			GMBUS_REG_READ(GMBUS2+reg_offset);
			करो अणु
				u32 val, loop = 0;

				अगर (रुको_क्रम(GMBUS_REG_READ(GMBUS2 + reg_offset) &
					     (GMBUS_SATOER | GMBUS_HW_RDY), 50))
					जाओ समयout;
				अगर (GMBUS_REG_READ(GMBUS2 + reg_offset) & GMBUS_SATOER)
					जाओ clear_err;

				val = GMBUS_REG_READ(GMBUS3 + reg_offset);
				करो अणु
					*buf++ = val & 0xff;
					val >>= 8;
				पूर्ण जबतक (--len && ++loop < 4);
			पूर्ण जबतक (len);
		पूर्ण अन्यथा अणु
			u32 val, loop;

			val = loop = 0;
			करो अणु
				val |= *buf++ << (8 * loop);
			पूर्ण जबतक (--len && ++loop < 4);

			GMBUS_REG_WRITE(GMBUS3 + reg_offset, val);
			GMBUS_REG_WRITE(GMBUS1 + reg_offset,
				   (i + 1 == num ? GMBUS_CYCLE_STOP : GMBUS_CYCLE_WAIT) |
				   (msgs[i].len << GMBUS_BYTE_COUNT_SHIFT) |
				   (msgs[i].addr << GMBUS_SLAVE_ADDR_SHIFT) |
				   GMBUS_SLAVE_WRITE | GMBUS_SW_RDY);
			GMBUS_REG_READ(GMBUS2+reg_offset);

			जबतक (len) अणु
				अगर (रुको_क्रम(GMBUS_REG_READ(GMBUS2 + reg_offset) &
					     (GMBUS_SATOER | GMBUS_HW_RDY), 50))
					जाओ समयout;
				अगर (GMBUS_REG_READ(GMBUS2 + reg_offset) &
				    GMBUS_SATOER)
					जाओ clear_err;

				val = loop = 0;
				करो अणु
					val |= *buf++ << (8 * loop);
				पूर्ण जबतक (--len && ++loop < 4);

				GMBUS_REG_WRITE(GMBUS3 + reg_offset, val);
				GMBUS_REG_READ(GMBUS2+reg_offset);
			पूर्ण
		पूर्ण

		अगर (i + 1 < num && रुको_क्रम(GMBUS_REG_READ(GMBUS2 + reg_offset) & (GMBUS_SATOER | GMBUS_HW_WAIT_PHASE), 50))
			जाओ समयout;
		अगर (GMBUS_REG_READ(GMBUS2 + reg_offset) & GMBUS_SATOER)
			जाओ clear_err;
	पूर्ण

	जाओ करोne;

clear_err:
	/* Toggle the Software Clear Interrupt bit. This has the effect
	 * of resetting the GMBUS controller and so clearing the
	 * BUS_ERROR उठाओd by the slave's NAK.
	 */
	GMBUS_REG_WRITE(GMBUS1 + reg_offset, GMBUS_SW_CLR_INT);
	GMBUS_REG_WRITE(GMBUS1 + reg_offset, 0);

करोne:
	/* Mark the GMBUS पूर्णांकerface as disabled. We will re-enable it at the
	 * start of the next xfer, till then let it sleep.
	 */
	GMBUS_REG_WRITE(GMBUS0 + reg_offset, 0);
	वापस i;

समयout:
	DRM_INFO("GMBUS timed out, falling back to bit banging on pin %d [%s]\n",
		 bus->reg0 & 0xff, bus->adapter.name);
	GMBUS_REG_WRITE(GMBUS0 + reg_offset, 0);

	/* Hardware may not support GMBUS over these pins? Try GPIO bitbanging instead. */
	bus->क्रमce_bit = पूर्णांकel_gpio_create(dev_priv, bus->reg0 & 0xff);
	अगर (!bus->क्रमce_bit)
		वापस -ENOMEM;

	वापस पूर्णांकel_i2c_quirk_xfer(dev_priv, bus->क्रमce_bit, msgs, num);
पूर्ण

अटल u32 gmbus_func(काष्ठा i2c_adapter *adapter)
अणु
	काष्ठा पूर्णांकel_gmbus *bus = container_of(adapter,
					       काष्ठा पूर्णांकel_gmbus,
					       adapter);

	अगर (bus->क्रमce_bit)
		bus->क्रमce_bit->algo->functionality(bus->क्रमce_bit);

	वापस (I2C_FUNC_I2C | I2C_FUNC_SMBUS_EMUL |
		/* I2C_FUNC_10BIT_ADDR | */
		I2C_FUNC_SMBUS_READ_BLOCK_DATA |
		I2C_FUNC_SMBUS_BLOCK_PROC_CALL);
पूर्ण

अटल स्थिर काष्ठा i2c_algorithm gmbus_algorithm = अणु
	.master_xfer	= gmbus_xfer,
	.functionality	= gmbus_func
पूर्ण;

/**
 * पूर्णांकel_gmbus_setup - instantiate all Intel i2c GMBuses
 * @dev: DRM device
 */
पूर्णांक gma_पूर्णांकel_setup_gmbus(काष्ठा drm_device *dev)
अणु
	अटल स्थिर अक्षर *names[GMBUS_NUM_PORTS] = अणु
		"disabled",
		"ssc",
		"vga",
		"panel",
		"dpc",
		"dpb",
		"reserved",
		"dpd",
	पूर्ण;
	काष्ठा drm_psb_निजी *dev_priv = dev->dev_निजी;
	पूर्णांक ret, i;

	dev_priv->gmbus = kसुस्मृति(GMBUS_NUM_PORTS, माप(काष्ठा पूर्णांकel_gmbus),
				  GFP_KERNEL);
	अगर (dev_priv->gmbus == शून्य)
		वापस -ENOMEM;

	अगर (IS_MRST(dev))
		dev_priv->gmbus_reg = dev_priv->aux_reg;
	अन्यथा
		dev_priv->gmbus_reg = dev_priv->vdc_reg;

	क्रम (i = 0; i < GMBUS_NUM_PORTS; i++) अणु
		काष्ठा पूर्णांकel_gmbus *bus = &dev_priv->gmbus[i];

		bus->adapter.owner = THIS_MODULE;
		bus->adapter.class = I2C_CLASS_DDC;
		snम_लिखो(bus->adapter.name,
			 माप(bus->adapter.name),
			 "gma500 gmbus %s",
			 names[i]);

		bus->adapter.dev.parent = dev->dev;
		bus->adapter.algo_data	= dev_priv;

		bus->adapter.algo = &gmbus_algorithm;
		ret = i2c_add_adapter(&bus->adapter);
		अगर (ret)
			जाओ err;

		/* By शेष use a conservative घड़ी rate */
		bus->reg0 = i | GMBUS_RATE_100KHZ;

		/* XXX क्रमce bit banging until GMBUS is fully debugged */
		bus->क्रमce_bit = पूर्णांकel_gpio_create(dev_priv, i);
	पूर्ण

	gma_पूर्णांकel_i2c_reset(dev_priv->dev);

	वापस 0;

err:
	जबतक (i--) अणु
		काष्ठा पूर्णांकel_gmbus *bus = &dev_priv->gmbus[i];
		i2c_del_adapter(&bus->adapter);
	पूर्ण
	kमुक्त(dev_priv->gmbus);
	dev_priv->gmbus = शून्य;
	वापस ret;
पूर्ण

व्योम gma_पूर्णांकel_gmbus_set_speed(काष्ठा i2c_adapter *adapter, पूर्णांक speed)
अणु
	काष्ठा पूर्णांकel_gmbus *bus = to_पूर्णांकel_gmbus(adapter);

	/* speed:
	 * 0x0 = 100 KHz
	 * 0x1 = 50 KHz
	 * 0x2 = 400 KHz
	 * 0x3 = 1000 Khz
	 */
	bus->reg0 = (bus->reg0 & ~(0x3 << 8)) | (speed << 8);
पूर्ण

व्योम gma_पूर्णांकel_gmbus_क्रमce_bit(काष्ठा i2c_adapter *adapter, bool क्रमce_bit)
अणु
	काष्ठा पूर्णांकel_gmbus *bus = to_पूर्णांकel_gmbus(adapter);

	अगर (क्रमce_bit) अणु
		अगर (bus->क्रमce_bit == शून्य) अणु
			काष्ठा drm_psb_निजी *dev_priv = adapter->algo_data;
			bus->क्रमce_bit = पूर्णांकel_gpio_create(dev_priv,
							   bus->reg0 & 0xff);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (bus->क्रमce_bit) अणु
			i2c_del_adapter(bus->क्रमce_bit);
			kमुक्त(bus->क्रमce_bit);
			bus->क्रमce_bit = शून्य;
		पूर्ण
	पूर्ण
पूर्ण

व्योम gma_पूर्णांकel_tearकरोwn_gmbus(काष्ठा drm_device *dev)
अणु
	काष्ठा drm_psb_निजी *dev_priv = dev->dev_निजी;
	पूर्णांक i;

	अगर (dev_priv->gmbus == शून्य)
		वापस;

	क्रम (i = 0; i < GMBUS_NUM_PORTS; i++) अणु
		काष्ठा पूर्णांकel_gmbus *bus = &dev_priv->gmbus[i];
		अगर (bus->क्रमce_bit) अणु
			i2c_del_adapter(bus->क्रमce_bit);
			kमुक्त(bus->क्रमce_bit);
		पूर्ण
		i2c_del_adapter(&bus->adapter);
	पूर्ण

	dev_priv->gmbus_reg = शून्य; /* iounmap is करोne in driver_unload */
	kमुक्त(dev_priv->gmbus);
	dev_priv->gmbus = शून्य;
पूर्ण
