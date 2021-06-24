<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Driver क्रम TI BQ32000 RTC.
 *
 * Copyright (C) 2009 Semihalf.
 * Copyright (C) 2014 Pavel Machek <pavel@denx.de>
 *
 * You can get hardware description at
 * https://www.ti.com/lit/ds/symlink/bq32000.pdf
 */

#समावेश <linux/module.h>
#समावेश <linux/i2c.h>
#समावेश <linux/rtc.h>
#समावेश <linux/init.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/bcd.h>

#घोषणा BQ32K_SECONDS		0x00	/* Seconds रेजिस्टर address */
#घोषणा BQ32K_SECONDS_MASK	0x7F	/* Mask over seconds value */
#घोषणा BQ32K_STOP		0x80	/* Oscillator Stop flat */

#घोषणा BQ32K_MINUTES		0x01	/* Minutes रेजिस्टर address */
#घोषणा BQ32K_MINUTES_MASK	0x7F	/* Mask over minutes value */
#घोषणा BQ32K_OF		0x80	/* Oscillator Failure flag */

#घोषणा BQ32K_HOURS_MASK	0x3F	/* Mask over hours value */
#घोषणा BQ32K_CENT		0x40	/* Century flag */
#घोषणा BQ32K_CENT_EN		0x80	/* Century flag enable bit */

#घोषणा BQ32K_CALIBRATION	0x07	/* CAL_CFG1, calibration and control */
#घोषणा BQ32K_TCH2		0x08	/* Trickle अक्षरge enable */
#घोषणा BQ32K_CFG2		0x09	/* Trickle अक्षरger control */
#घोषणा BQ32K_TCFE		BIT(6)	/* Trickle अक्षरge FET bypass */

#घोषणा MAX_LEN			10	/* Maximum number of consecutive
					 * रेजिस्टर क्रम this particular RTC.
					 */

काष्ठा bq32k_regs अणु
	uपूर्णांक8_t		seconds;
	uपूर्णांक8_t		minutes;
	uपूर्णांक8_t		cent_hours;
	uपूर्णांक8_t		day;
	uपूर्णांक8_t		date;
	uपूर्णांक8_t		month;
	uपूर्णांक8_t		years;
पूर्ण;

अटल काष्ठा i2c_driver bq32k_driver;

अटल पूर्णांक bq32k_पढ़ो(काष्ठा device *dev, व्योम *data, uपूर्णांक8_t off, uपूर्णांक8_t len)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा i2c_msg msgs[] = अणु
		अणु
			.addr = client->addr,
			.flags = 0,
			.len = 1,
			.buf = &off,
		पूर्ण, अणु
			.addr = client->addr,
			.flags = I2C_M_RD,
			.len = len,
			.buf = data,
		पूर्ण
	पूर्ण;

	अगर (i2c_transfer(client->adapter, msgs, 2) == 2)
		वापस 0;

	वापस -EIO;
पूर्ण

अटल पूर्णांक bq32k_ग_लिखो(काष्ठा device *dev, व्योम *data, uपूर्णांक8_t off, uपूर्णांक8_t len)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	uपूर्णांक8_t buffer[MAX_LEN + 1];

	buffer[0] = off;
	स_नकल(&buffer[1], data, len);

	अगर (i2c_master_send(client, buffer, len + 1) == len + 1)
		वापस 0;

	वापस -EIO;
पूर्ण

अटल पूर्णांक bq32k_rtc_पढ़ो_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा bq32k_regs regs;
	पूर्णांक error;

	error = bq32k_पढ़ो(dev, &regs, 0, माप(regs));
	अगर (error)
		वापस error;

	/*
	 * In हाल of oscillator failure, the रेजिस्टर contents should be
	 * considered invalid. The flag is cleared the next समय the RTC is set.
	 */
	अगर (regs.minutes & BQ32K_OF)
		वापस -EINVAL;

	पंचांग->पंचांग_sec = bcd2bin(regs.seconds & BQ32K_SECONDS_MASK);
	पंचांग->पंचांग_min = bcd2bin(regs.minutes & BQ32K_MINUTES_MASK);
	पंचांग->पंचांग_hour = bcd2bin(regs.cent_hours & BQ32K_HOURS_MASK);
	पंचांग->पंचांग_mday = bcd2bin(regs.date);
	पंचांग->पंचांग_wday = bcd2bin(regs.day) - 1;
	पंचांग->पंचांग_mon = bcd2bin(regs.month) - 1;
	पंचांग->पंचांग_year = bcd2bin(regs.years) +
				((regs.cent_hours & BQ32K_CENT) ? 100 : 0);

	वापस 0;
पूर्ण

अटल पूर्णांक bq32k_rtc_set_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा bq32k_regs regs;

	regs.seconds = bin2bcd(पंचांग->पंचांग_sec);
	regs.minutes = bin2bcd(पंचांग->पंचांग_min);
	regs.cent_hours = bin2bcd(पंचांग->पंचांग_hour) | BQ32K_CENT_EN;
	regs.day = bin2bcd(पंचांग->पंचांग_wday + 1);
	regs.date = bin2bcd(पंचांग->पंचांग_mday);
	regs.month = bin2bcd(पंचांग->पंचांग_mon + 1);

	अगर (पंचांग->पंचांग_year >= 100) अणु
		regs.cent_hours |= BQ32K_CENT;
		regs.years = bin2bcd(पंचांग->पंचांग_year - 100);
	पूर्ण अन्यथा
		regs.years = bin2bcd(पंचांग->पंचांग_year);

	वापस bq32k_ग_लिखो(dev, &regs, 0, माप(regs));
पूर्ण

अटल स्थिर काष्ठा rtc_class_ops bq32k_rtc_ops = अणु
	.पढ़ो_समय	= bq32k_rtc_पढ़ो_समय,
	.set_समय	= bq32k_rtc_set_समय,
पूर्ण;

अटल पूर्णांक trickle_अक्षरger_of_init(काष्ठा device *dev, काष्ठा device_node *node)
अणु
	अचिन्हित अक्षर reg;
	पूर्णांक error;
	u32 ohms = 0;

	अगर (of_property_पढ़ो_u32(node, "trickle-resistor-ohms" , &ohms))
		वापस 0;

	चयन (ohms) अणु
	हाल 180+940:
		/*
		 * TCHE[3:0] == 0x05, TCH2 == 1, TCFE == 0 (अक्षरging
		 * over diode and 940ohm resistor)
		 */

		अगर (of_property_पढ़ो_bool(node, "trickle-diode-disable")) अणु
			dev_err(dev, "diode and resistor mismatch\n");
			वापस -EINVAL;
		पूर्ण
		reg = 0x05;
		अवरोध;

	हाल 180+20000:
		/* diode disabled */

		अगर (!of_property_पढ़ो_bool(node, "trickle-diode-disable")) अणु
			dev_err(dev, "bq32k: diode and resistor mismatch\n");
			वापस -EINVAL;
		पूर्ण
		reg = 0x45;
		अवरोध;

	शेष:
		dev_err(dev, "invalid resistor value (%d)\n", ohms);
		वापस -EINVAL;
	पूर्ण

	error = bq32k_ग_लिखो(dev, &reg, BQ32K_CFG2, 1);
	अगर (error)
		वापस error;

	reg = 0x20;
	error = bq32k_ग_लिखो(dev, &reg, BQ32K_TCH2, 1);
	अगर (error)
		वापस error;

	dev_info(dev, "Enabled trickle RTC battery charge.\n");
	वापस 0;
पूर्ण

अटल sमाप_प्रकार bq32k_sysfs_show_trickleअक्षरge_bypass(काष्ठा device *dev,
					       काष्ठा device_attribute *attr,
					       अक्षर *buf)
अणु
	पूर्णांक reg, error;

	error = bq32k_पढ़ो(dev, &reg, BQ32K_CFG2, 1);
	अगर (error)
		वापस error;

	वापस प्र_लिखो(buf, "%d\n", (reg & BQ32K_TCFE) ? 1 : 0);
पूर्ण

अटल sमाप_प्रकार bq32k_sysfs_store_trickleअक्षरge_bypass(काष्ठा device *dev,
						काष्ठा device_attribute *attr,
						स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक reg, enable, error;

	अगर (kstrtoपूर्णांक(buf, 0, &enable))
		वापस -EINVAL;

	error = bq32k_पढ़ो(dev, &reg, BQ32K_CFG2, 1);
	अगर (error)
		वापस error;

	अगर (enable) अणु
		reg |= BQ32K_TCFE;
		error = bq32k_ग_लिखो(dev, &reg, BQ32K_CFG2, 1);
		अगर (error)
			वापस error;

		dev_info(dev, "Enabled trickle charge FET bypass.\n");
	पूर्ण अन्यथा अणु
		reg &= ~BQ32K_TCFE;
		error = bq32k_ग_लिखो(dev, &reg, BQ32K_CFG2, 1);
		अगर (error)
			वापस error;

		dev_info(dev, "Disabled trickle charge FET bypass.\n");
	पूर्ण

	वापस count;
पूर्ण

अटल DEVICE_ATTR(trickle_अक्षरge_bypass, 0644,
		   bq32k_sysfs_show_trickleअक्षरge_bypass,
		   bq32k_sysfs_store_trickleअक्षरge_bypass);

अटल पूर्णांक bq32k_sysfs_रेजिस्टर(काष्ठा device *dev)
अणु
	वापस device_create_file(dev, &dev_attr_trickle_अक्षरge_bypass);
पूर्ण

अटल व्योम bq32k_sysfs_unरेजिस्टर(काष्ठा device *dev)
अणु
	device_हटाओ_file(dev, &dev_attr_trickle_अक्षरge_bypass);
पूर्ण

अटल पूर्णांक bq32k_probe(काष्ठा i2c_client *client,
				स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा device *dev = &client->dev;
	काष्ठा rtc_device *rtc;
	uपूर्णांक8_t reg;
	पूर्णांक error;

	अगर (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C))
		वापस -ENODEV;

	/* Check Oscillator Stop flag */
	error = bq32k_पढ़ो(dev, &reg, BQ32K_SECONDS, 1);
	अगर (!error && (reg & BQ32K_STOP)) अणु
		dev_warn(dev, "Oscillator was halted. Restarting...\n");
		reg &= ~BQ32K_STOP;
		error = bq32k_ग_लिखो(dev, &reg, BQ32K_SECONDS, 1);
	पूर्ण
	अगर (error)
		वापस error;

	/* Check Oscillator Failure flag */
	error = bq32k_पढ़ो(dev, &reg, BQ32K_MINUTES, 1);
	अगर (error)
		वापस error;
	अगर (reg & BQ32K_OF)
		dev_warn(dev, "Oscillator Failure. Check RTC battery.\n");

	अगर (client->dev.of_node)
		trickle_अक्षरger_of_init(dev, client->dev.of_node);

	rtc = devm_rtc_device_रेजिस्टर(&client->dev, bq32k_driver.driver.name,
						&bq32k_rtc_ops, THIS_MODULE);
	अगर (IS_ERR(rtc))
		वापस PTR_ERR(rtc);

	error = bq32k_sysfs_रेजिस्टर(&client->dev);
	अगर (error) अणु
		dev_err(&client->dev,
			"Unable to create sysfs entries for rtc bq32000\n");
		वापस error;
	पूर्ण


	i2c_set_clientdata(client, rtc);

	वापस 0;
पूर्ण

अटल पूर्णांक bq32k_हटाओ(काष्ठा i2c_client *client)
अणु
	bq32k_sysfs_unरेजिस्टर(&client->dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id bq32k_id[] = अणु
	अणु "bq32000", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, bq32k_id);

अटल स्थिर __maybe_unused काष्ठा of_device_id bq32k_of_match[] = अणु
	अणु .compatible = "ti,bq32000" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, bq32k_of_match);

अटल काष्ठा i2c_driver bq32k_driver = अणु
	.driver = अणु
		.name	= "bq32k",
		.of_match_table = of_match_ptr(bq32k_of_match),
	पूर्ण,
	.probe		= bq32k_probe,
	.हटाओ		= bq32k_हटाओ,
	.id_table	= bq32k_id,
पूर्ण;

module_i2c_driver(bq32k_driver);

MODULE_AUTHOR("Semihalf, Piotr Ziecik <kosmo@semihalf.com>");
MODULE_DESCRIPTION("TI BQ32000 I2C RTC driver");
MODULE_LICENSE("GPL");
