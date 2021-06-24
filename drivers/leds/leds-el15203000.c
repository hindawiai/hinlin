<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (c) 2019 Crane Merchandising Systems. All rights reserved.
// Copyright (C) 2019 Oleh Kravchenko <oleg@kaa.org.ua>

#समावेश <linux/delay.h>
#समावेश <linux/leds.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/spi/spi.h>

/*
 * EL15203000 SPI protocol description:
 * +-----+---------+
 * | LED | COMMAND |
 * +-----+---------+
 * |  1  |    1    |
 * +-----+---------+
 * (*) LEDs MCU board expects 20 msec delay per byte.
 *
 * LEDs:
 * +----------+--------------+-------------------------------------------+
 * |    ID    |     NAME     |         DESCRIPTION                       |
 * +----------+--------------+-------------------------------------------+
 * | 'P' 0x50 |     Pipe     | Consists from 5 LEDs, controlled by board |
 * +----------+--------------+-------------------------------------------+
 * | 'S' 0x53 | Screen frame | Light tube around the screen              |
 * +----------+--------------+-------------------------------------------+
 * | 'V' 0x56 | Vending area | Highlights a cup of coffee                |
 * +----------+--------------+-------------------------------------------+
 *
 * COMMAND:
 * +----------+-----------------+--------------+--------------+
 * |  VALUES  |       PIPE      | SCREEN FRAME | VENDING AREA |
 * +----------+-----------------+--------------+--------------+
 * | '0' 0x30 |                      Off                      |
 * +----------+-----------------------------------------------+
 * | '1' 0x31 |                      On                       |
 * +----------+-----------------+--------------+--------------+
 * | '2' 0x32 |     Cascade     |   Breathing  |
 * +----------+-----------------+--------------+
 * | '3' 0x33 | Inverse cascade |
 * +----------+-----------------+
 * | '4' 0x34 |     Bounce      |
 * +----------+-----------------+
 * | '5' 0x35 | Inverse bounce  |
 * +----------+-----------------+
 */

/* EL15203000 शेष settings */
#घोषणा EL_FW_DELAY_USEC	20000ul
#घोषणा EL_PATTERN_DELAY_MSEC	800u
#घोषणा EL_PATTERN_LEN		10u
#घोषणा EL_PATTERN_HALF_LEN	(EL_PATTERN_LEN / 2)

क्रमागत el15203000_command अणु
	/* क्रम all LEDs */
	EL_OFF			= '0',
	EL_ON			= '1',

	/* क्रम Screen LED */
	EL_SCREEN_BREATHING	= '2',

	/* क्रम Pipe LED */
	EL_PIPE_CASCADE		= '2',
	EL_PIPE_INV_CASCADE	= '3',
	EL_PIPE_BOUNCE		= '4',
	EL_PIPE_INV_BOUNCE	= '5',
पूर्ण;

काष्ठा el15203000_led अणु
	काष्ठा el15203000	*priv;
	काष्ठा led_classdev	ldev;
	u32			reg;
पूर्ण;

काष्ठा el15203000 अणु
	काष्ठा device		*dev;
	काष्ठा mutex		lock;
	काष्ठा spi_device	*spi;
	अचिन्हित दीर्घ		delay;
	माप_प्रकार			count;
	काष्ठा el15203000_led	leds[];
पूर्ण;

अटल पूर्णांक el15203000_cmd(काष्ठा el15203000_led *led, u8 brightness)
अणु
	पूर्णांक		ret;
	u8		cmd[2];
	माप_प्रकार		i;

	mutex_lock(&led->priv->lock);

	dev_dbg(led->priv->dev, "Set brightness of 0x%02x(%c) to 0x%02x(%c)",
		led->reg, led->reg, brightness, brightness);

	/* to aव्योम SPI mistiming with firmware we should रुको some समय */
	अगर (समय_after(led->priv->delay, jअगरfies)) अणु
		dev_dbg(led->priv->dev, "Wait %luus to sync",
			EL_FW_DELAY_USEC);

		usleep_range(EL_FW_DELAY_USEC,
			     EL_FW_DELAY_USEC + 1);
	पूर्ण

	cmd[0] = led->reg;
	cmd[1] = brightness;

	क्रम (i = 0; i < ARRAY_SIZE(cmd); i++) अणु
		अगर (i)
			usleep_range(EL_FW_DELAY_USEC,
				     EL_FW_DELAY_USEC + 1);

		ret = spi_ग_लिखो(led->priv->spi, &cmd[i], माप(cmd[i]));
		अगर (ret) अणु
			dev_err(led->priv->dev,
				"spi_write() error %d", ret);
			अवरोध;
		पूर्ण
	पूर्ण

	led->priv->delay = jअगरfies + usecs_to_jअगरfies(EL_FW_DELAY_USEC);

	mutex_unlock(&led->priv->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक el15203000_set_blocking(काष्ठा led_classdev *ldev,
				   क्रमागत led_brightness brightness)
अणु
	काष्ठा el15203000_led *led = container_of(ldev,
						  काष्ठा el15203000_led,
						  ldev);

	वापस el15203000_cmd(led, brightness == LED_OFF ? EL_OFF : EL_ON);
पूर्ण

अटल पूर्णांक el15203000_pattern_set_S(काष्ठा led_classdev *ldev,
				    काष्ठा led_pattern *pattern,
				    u32 len, पूर्णांक repeat)
अणु
	काष्ठा el15203000_led *led = container_of(ldev,
						  काष्ठा el15203000_led,
						  ldev);

	अगर (repeat > 0 || len != 2 ||
	    pattern[0].delta_t != 4000 || pattern[0].brightness != 0 ||
	    pattern[1].delta_t != 4000 || pattern[1].brightness != 1)
		वापस -EINVAL;

	dev_dbg(led->priv->dev, "Breathing mode for 0x%02x(%c)",
		led->reg, led->reg);

	वापस el15203000_cmd(led, EL_SCREEN_BREATHING);
पूर्ण

अटल bool is_cascade(स्थिर काष्ठा led_pattern *pattern, u32 len,
		       bool inv, bool right)
अणु
	पूर्णांक val, t;
	u32 i;

	अगर (len != EL_PATTERN_HALF_LEN)
		वापस false;

	val = right ? BIT(4) : BIT(0);

	क्रम (i = 0; i < len; i++) अणु
		t = inv ? ~val & GENMASK(4, 0) : val;

		अगर (pattern[i].delta_t != EL_PATTERN_DELAY_MSEC ||
		    pattern[i].brightness != t)
			वापस false;

		val = right ? val >> 1 : val << 1;
	पूर्ण

	वापस true;
पूर्ण

अटल bool is_bounce(स्थिर काष्ठा led_pattern *pattern, u32 len, bool inv)
अणु
	अगर (len != EL_PATTERN_LEN)
		वापस false;

	वापस is_cascade(pattern, EL_PATTERN_HALF_LEN, inv, false) &&
	       is_cascade(pattern + EL_PATTERN_HALF_LEN,
			  EL_PATTERN_HALF_LEN, inv, true);
पूर्ण

अटल पूर्णांक el15203000_pattern_set_P(काष्ठा led_classdev *ldev,
				    काष्ठा led_pattern *pattern,
				    u32 len, पूर्णांक repeat)
अणु
	u8			cmd;
	काष्ठा el15203000_led	*led = container_of(ldev,
						    काष्ठा el15203000_led,
						    ldev);

	अगर (repeat > 0)
		वापस -EINVAL;

	अगर (is_cascade(pattern, len, false, false)) अणु
		dev_dbg(led->priv->dev, "Cascade mode for 0x%02x(%c)",
			led->reg, led->reg);

		cmd = EL_PIPE_CASCADE;
	पूर्ण अन्यथा अगर (is_cascade(pattern, len, true, false)) अणु
		dev_dbg(led->priv->dev, "Inverse cascade mode for 0x%02x(%c)",
			led->reg, led->reg);

		cmd = EL_PIPE_INV_CASCADE;
	पूर्ण अन्यथा अगर (is_bounce(pattern, len, false)) अणु
		dev_dbg(led->priv->dev, "Bounce mode for 0x%02x(%c)",
			led->reg, led->reg);

		cmd = EL_PIPE_BOUNCE;
	पूर्ण अन्यथा अगर (is_bounce(pattern, len, true)) अणु
		dev_dbg(led->priv->dev, "Inverse bounce mode for 0x%02x(%c)",
			led->reg, led->reg);

		cmd = EL_PIPE_INV_BOUNCE;
	पूर्ण अन्यथा अणु
		dev_err(led->priv->dev, "Invalid hw_pattern for 0x%02x(%c)!",
			led->reg, led->reg);

		वापस -EINVAL;
	पूर्ण

	वापस el15203000_cmd(led, cmd);
पूर्ण

अटल पूर्णांक el15203000_pattern_clear(काष्ठा led_classdev *ldev)
अणु
	काष्ठा el15203000_led	*led = container_of(ldev,
						    काष्ठा el15203000_led,
						    ldev);

	वापस el15203000_cmd(led, EL_OFF);
पूर्ण

अटल पूर्णांक el15203000_probe_dt(काष्ठा el15203000 *priv)
अणु
	काष्ठा el15203000_led	*led = priv->leds;
	काष्ठा fwnode_handle	*child;
	पूर्णांक			ret;

	device_क्रम_each_child_node(priv->dev, child) अणु
		काष्ठा led_init_data init_data = अणुपूर्ण;

		ret = fwnode_property_पढ़ो_u32(child, "reg", &led->reg);
		अगर (ret) अणु
			dev_err(priv->dev, "LED without ID number");
			fwnode_handle_put(child);

			अवरोध;
		पूर्ण

		अगर (led->reg > U8_MAX) अणु
			dev_err(priv->dev, "LED value %d is invalid", led->reg);
			fwnode_handle_put(child);

			वापस -EINVAL;
		पूर्ण

		led->priv			  = priv;
		led->ldev.max_brightness	  = LED_ON;
		led->ldev.brightness_set_blocking = el15203000_set_blocking;

		अगर (led->reg == 'S') अणु
			led->ldev.pattern_set	= el15203000_pattern_set_S;
			led->ldev.pattern_clear	= el15203000_pattern_clear;
		पूर्ण अन्यथा अगर (led->reg == 'P') अणु
			led->ldev.pattern_set	= el15203000_pattern_set_P;
			led->ldev.pattern_clear	= el15203000_pattern_clear;
		पूर्ण

		init_data.fwnode = child;
		ret = devm_led_classdev_रेजिस्टर_ext(priv->dev, &led->ldev,
						     &init_data);
		अगर (ret) अणु
			dev_err(priv->dev,
				"failed to register LED device %s, err %d",
				led->ldev.name, ret);
			fwnode_handle_put(child);

			अवरोध;
		पूर्ण

		led++;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक el15203000_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा el15203000	*priv;
	माप_प्रकार			count;

	count = device_get_child_node_count(&spi->dev);
	अगर (!count) अणु
		dev_err(&spi->dev, "LEDs are not defined in device tree!");
		वापस -ENODEV;
	पूर्ण

	priv = devm_kzalloc(&spi->dev, काष्ठा_size(priv, leds, count),
			    GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	mutex_init(&priv->lock);
	priv->count	= count;
	priv->dev	= &spi->dev;
	priv->spi	= spi;
	priv->delay	= jअगरfies -
			  usecs_to_jअगरfies(EL_FW_DELAY_USEC);

	spi_set_drvdata(spi, priv);

	वापस el15203000_probe_dt(priv);
पूर्ण

अटल पूर्णांक el15203000_हटाओ(काष्ठा spi_device *spi)
अणु
	काष्ठा el15203000 *priv = spi_get_drvdata(spi);

	mutex_destroy(&priv->lock);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id el15203000_dt_ids[] = अणु
	अणु .compatible = "crane,el15203000", पूर्ण,
	अणुपूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(of, el15203000_dt_ids);

अटल काष्ठा spi_driver el15203000_driver = अणु
	.probe		= el15203000_probe,
	.हटाओ		= el15203000_हटाओ,
	.driver = अणु
		.name		= KBUILD_MODNAME,
		.of_match_table	= el15203000_dt_ids,
	पूर्ण,
पूर्ण;

module_spi_driver(el15203000_driver);

MODULE_AUTHOR("Oleh Kravchenko <oleg@kaa.org.ua>");
MODULE_DESCRIPTION("el15203000 LED driver");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("spi:el15203000");
