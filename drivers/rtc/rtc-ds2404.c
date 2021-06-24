<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (C) 2012 Sven Schnelle <svens@stackframe.org>

#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/rtc.h>
#समावेश <linux/types.h>
#समावेश <linux/bcd.h>
#समावेश <linux/platक्रमm_data/rtc-ds2404.h>
#समावेश <linux/delay.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/slab.h>

#समावेश <linux/पन.स>

#घोषणा DS2404_STATUS_REG 0x200
#घोषणा DS2404_CONTROL_REG 0x201
#घोषणा DS2404_RTC_REG 0x202

#घोषणा DS2404_WRITE_SCRATCHPAD_CMD 0x0f
#घोषणा DS2404_READ_SCRATCHPAD_CMD 0xaa
#घोषणा DS2404_COPY_SCRATCHPAD_CMD 0x55
#घोषणा DS2404_READ_MEMORY_CMD 0xf0

#घोषणा DS2404_RST	0
#घोषणा DS2404_CLK	1
#घोषणा DS2404_DQ	2

काष्ठा ds2404_gpio अणु
	स्थिर अक्षर *name;
	अचिन्हित पूर्णांक gpio;
पूर्ण;

काष्ठा ds2404 अणु
	काष्ठा ds2404_gpio *gpio;
	काष्ठा rtc_device *rtc;
पूर्ण;

अटल काष्ठा ds2404_gpio ds2404_gpio[] = अणु
	अणु "RTC RST", 0 पूर्ण,
	अणु "RTC CLK", 0 पूर्ण,
	अणु "RTC DQ", 0 पूर्ण,
पूर्ण;

अटल पूर्णांक ds2404_gpio_map(काष्ठा ds2404 *chip, काष्ठा platक्रमm_device *pdev,
			  काष्ठा ds2404_platक्रमm_data *pdata)
अणु
	पूर्णांक i, err;

	ds2404_gpio[DS2404_RST].gpio = pdata->gpio_rst;
	ds2404_gpio[DS2404_CLK].gpio = pdata->gpio_clk;
	ds2404_gpio[DS2404_DQ].gpio = pdata->gpio_dq;

	क्रम (i = 0; i < ARRAY_SIZE(ds2404_gpio); i++) अणु
		err = gpio_request(ds2404_gpio[i].gpio, ds2404_gpio[i].name);
		अगर (err) अणु
			dev_err(&pdev->dev, "error mapping gpio %s: %d\n",
				ds2404_gpio[i].name, err);
			जाओ err_request;
		पूर्ण
		अगर (i != DS2404_DQ)
			gpio_direction_output(ds2404_gpio[i].gpio, 1);
	पूर्ण

	chip->gpio = ds2404_gpio;
	वापस 0;

err_request:
	जबतक (--i >= 0)
		gpio_मुक्त(ds2404_gpio[i].gpio);
	वापस err;
पूर्ण

अटल व्योम ds2404_gpio_unmap(व्योम *data)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(ds2404_gpio); i++)
		gpio_मुक्त(ds2404_gpio[i].gpio);
पूर्ण

अटल व्योम ds2404_reset(काष्ठा device *dev)
अणु
	gpio_set_value(ds2404_gpio[DS2404_RST].gpio, 0);
	udelay(1000);
	gpio_set_value(ds2404_gpio[DS2404_RST].gpio, 1);
	gpio_set_value(ds2404_gpio[DS2404_CLK].gpio, 0);
	gpio_direction_output(ds2404_gpio[DS2404_DQ].gpio, 0);
	udelay(10);
पूर्ण

अटल व्योम ds2404_ग_लिखो_byte(काष्ठा device *dev, u8 byte)
अणु
	पूर्णांक i;

	gpio_direction_output(ds2404_gpio[DS2404_DQ].gpio, 1);
	क्रम (i = 0; i < 8; i++) अणु
		gpio_set_value(ds2404_gpio[DS2404_DQ].gpio, byte & (1 << i));
		udelay(10);
		gpio_set_value(ds2404_gpio[DS2404_CLK].gpio, 1);
		udelay(10);
		gpio_set_value(ds2404_gpio[DS2404_CLK].gpio, 0);
		udelay(10);
	पूर्ण
पूर्ण

अटल u8 ds2404_पढ़ो_byte(काष्ठा device *dev)
अणु
	पूर्णांक i;
	u8 ret = 0;

	gpio_direction_input(ds2404_gpio[DS2404_DQ].gpio);

	क्रम (i = 0; i < 8; i++) अणु
		gpio_set_value(ds2404_gpio[DS2404_CLK].gpio, 0);
		udelay(10);
		अगर (gpio_get_value(ds2404_gpio[DS2404_DQ].gpio))
			ret |= 1 << i;
		gpio_set_value(ds2404_gpio[DS2404_CLK].gpio, 1);
		udelay(10);
	पूर्ण
	वापस ret;
पूर्ण

अटल व्योम ds2404_पढ़ो_memory(काष्ठा device *dev, u16 offset,
			       पूर्णांक length, u8 *out)
अणु
	ds2404_reset(dev);
	ds2404_ग_लिखो_byte(dev, DS2404_READ_MEMORY_CMD);
	ds2404_ग_लिखो_byte(dev, offset & 0xff);
	ds2404_ग_लिखो_byte(dev, (offset >> 8) & 0xff);
	जबतक (length--)
		*out++ = ds2404_पढ़ो_byte(dev);
पूर्ण

अटल व्योम ds2404_ग_लिखो_memory(काष्ठा device *dev, u16 offset,
				पूर्णांक length, u8 *out)
अणु
	पूर्णांक i;
	u8 ta01, ta02, es;

	ds2404_reset(dev);
	ds2404_ग_लिखो_byte(dev, DS2404_WRITE_SCRATCHPAD_CMD);
	ds2404_ग_लिखो_byte(dev, offset & 0xff);
	ds2404_ग_लिखो_byte(dev, (offset >> 8) & 0xff);

	क्रम (i = 0; i < length; i++)
		ds2404_ग_लिखो_byte(dev, out[i]);

	ds2404_reset(dev);
	ds2404_ग_लिखो_byte(dev, DS2404_READ_SCRATCHPAD_CMD);

	ta01 = ds2404_पढ़ो_byte(dev);
	ta02 = ds2404_पढ़ो_byte(dev);
	es = ds2404_पढ़ो_byte(dev);

	क्रम (i = 0; i < length; i++) अणु
		अगर (out[i] != ds2404_पढ़ो_byte(dev)) अणु
			dev_err(dev, "read invalid data\n");
			वापस;
		पूर्ण
	पूर्ण

	ds2404_reset(dev);
	ds2404_ग_लिखो_byte(dev, DS2404_COPY_SCRATCHPAD_CMD);
	ds2404_ग_लिखो_byte(dev, ta01);
	ds2404_ग_लिखो_byte(dev, ta02);
	ds2404_ग_लिखो_byte(dev, es);

	gpio_direction_input(ds2404_gpio[DS2404_DQ].gpio);
	जबतक (gpio_get_value(ds2404_gpio[DS2404_DQ].gpio))
		;
पूर्ण

अटल व्योम ds2404_enable_osc(काष्ठा device *dev)
अणु
	u8 in[1] = अणु 0x10 पूर्ण; /* enable oscillator */
	ds2404_ग_लिखो_memory(dev, 0x201, 1, in);
पूर्ण

अटल पूर्णांक ds2404_पढ़ो_समय(काष्ठा device *dev, काष्ठा rtc_समय *dt)
अणु
	अचिन्हित दीर्घ समय = 0;
	__le32 hw_समय = 0;

	ds2404_पढ़ो_memory(dev, 0x203, 4, (u8 *)&hw_समय);
	समय = le32_to_cpu(hw_समय);

	rtc_समय64_to_पंचांग(समय, dt);
	वापस 0;
पूर्ण

अटल पूर्णांक ds2404_set_समय(काष्ठा device *dev, काष्ठा rtc_समय *dt)
अणु
	u32 समय = cpu_to_le32(rtc_पंचांग_to_समय64(dt));
	ds2404_ग_लिखो_memory(dev, 0x203, 4, (u8 *)&समय);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा rtc_class_ops ds2404_rtc_ops = अणु
	.पढ़ो_समय	= ds2404_पढ़ो_समय,
	.set_समय	= ds2404_set_समय,
पूर्ण;

अटल पूर्णांक rtc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ds2404_platक्रमm_data *pdata = dev_get_platdata(&pdev->dev);
	काष्ठा ds2404 *chip;
	पूर्णांक retval = -EBUSY;

	chip = devm_kzalloc(&pdev->dev, माप(काष्ठा ds2404), GFP_KERNEL);
	अगर (!chip)
		वापस -ENOMEM;

	chip->rtc = devm_rtc_allocate_device(&pdev->dev);
	अगर (IS_ERR(chip->rtc))
		वापस PTR_ERR(chip->rtc);

	retval = ds2404_gpio_map(chip, pdev, pdata);
	अगर (retval)
		वापस retval;

	retval = devm_add_action_or_reset(&pdev->dev, ds2404_gpio_unmap, chip);
	अगर (retval)
		वापस retval;

	dev_info(&pdev->dev, "using GPIOs RST:%d, CLK:%d, DQ:%d\n",
		 chip->gpio[DS2404_RST].gpio, chip->gpio[DS2404_CLK].gpio,
		 chip->gpio[DS2404_DQ].gpio);

	platक्रमm_set_drvdata(pdev, chip);

	chip->rtc->ops = &ds2404_rtc_ops;
	chip->rtc->range_max = U32_MAX;

	retval = devm_rtc_रेजिस्टर_device(chip->rtc);
	अगर (retval)
		वापस retval;

	ds2404_enable_osc(&pdev->dev);
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver rtc_device_driver = अणु
	.probe	= rtc_probe,
	.driver = अणु
		.name	= "ds2404",
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(rtc_device_driver);

MODULE_DESCRIPTION("DS2404 RTC");
MODULE_AUTHOR("Sven Schnelle");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:ds2404");
