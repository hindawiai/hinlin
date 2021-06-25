<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  leds-blinkm.c
 *  (c) Jan-Simon Mथघller (dl9pf@gmx.de)
 */

#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/i2c.h>
#समावेश <linux/err.h>
#समावेश <linux/mutex.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/prपूर्णांकk.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/leds.h>
#समावेश <linux/delay.h>

/* Addresses to scan - BlinkM is on 0x09 by शेष*/
अटल स्थिर अचिन्हित लघु normal_i2c[] = अणु 0x09, I2C_CLIENT_END पूर्ण;

अटल पूर्णांक blinkm_transfer_hw(काष्ठा i2c_client *client, पूर्णांक cmd);
अटल पूर्णांक blinkm_test_run(काष्ठा i2c_client *client);

काष्ठा blinkm_led अणु
	काष्ठा i2c_client *i2c_client;
	काष्ठा led_classdev led_cdev;
	पूर्णांक id;
पूर्ण;

#घोषणा cdev_to_blmled(c)          container_of(c, काष्ठा blinkm_led, led_cdev)

काष्ठा blinkm_data अणु
	काष्ठा i2c_client *i2c_client;
	काष्ठा mutex update_lock;
	/* used क्रम led class पूर्णांकerface */
	काष्ठा blinkm_led blinkm_leds[3];
	/* used क्रम "blinkm" sysfs पूर्णांकerface */
	u8 red;			/* color red */
	u8 green;		/* color green */
	u8 blue;		/* color blue */
	/* next values to use क्रम transfer */
	u8 next_red;			/* color red */
	u8 next_green;		/* color green */
	u8 next_blue;		/* color blue */
	/* पूर्णांकernal use */
	u8 args[7];		/* set of args क्रम transmission */
	u8 i2c_addr;		/* i2c addr */
	u8 fw_ver;		/* firmware version */
	/* used, but not from userspace */
	u8 hue;			/* HSB  hue */
	u8 saturation;		/* HSB  saturation */
	u8 brightness;		/* HSB  brightness */
	u8 next_hue;			/* HSB  hue */
	u8 next_saturation;		/* HSB  saturation */
	u8 next_brightness;		/* HSB  brightness */
	/* currently unused / toकरो */
	u8 fade_speed;		/* fade speed     1 - 255 */
	s8 समय_adjust;		/* समय adjust -128 - 127 */
	u8 fade:1;		/* fade on = 1, off = 0 */
	u8 अक्रम:1;		/* अक्रम fade mode on = 1 */
	u8 script_id;		/* script ID */
	u8 script_repeats;	/* repeats of script */
	u8 script_startline;	/* line to start */
पूर्ण;

/* Colors */
#घोषणा RED   0
#घोषणा GREEN 1
#घोषणा BLUE  2

/* mapping command names to cmd अक्षरs - see datasheet */
#घोषणा BLM_GO_RGB            0
#घोषणा BLM_FADE_RGB          1
#घोषणा BLM_FADE_HSB          2
#घोषणा BLM_FADE_RAND_RGB     3
#घोषणा BLM_FADE_RAND_HSB     4
#घोषणा BLM_PLAY_SCRIPT       5
#घोषणा BLM_STOP_SCRIPT       6
#घोषणा BLM_SET_FADE_SPEED    7
#घोषणा BLM_SET_TIME_ADJ      8
#घोषणा BLM_GET_CUR_RGB       9
#घोषणा BLM_WRITE_SCRIPT_LINE 10
#घोषणा BLM_READ_SCRIPT_LINE  11
#घोषणा BLM_SET_SCRIPT_LR     12	/* Length & Repeats */
#घोषणा BLM_SET_ADDR          13
#घोषणा BLM_GET_ADDR          14
#घोषणा BLM_GET_FW_VER        15
#घोषणा BLM_SET_STARTUP_PARAM 16

/* BlinkM Commands
 *  as extracted out of the datasheet:
 *
 *  cmdअक्षर = command (ascii)
 *  cmdbyte = command in hex
 *  nr_args = number of arguments (to send)
 *  nr_ret  = number of वापस values (to पढ़ो)
 *  dir = direction (0 = पढ़ो, 1 = ग_लिखो, 2 = both)
 *
 */
अटल स्थिर काष्ठा अणु
	अक्षर cmdअक्षर;
	u8 cmdbyte;
	u8 nr_args;
	u8 nr_ret;
	u8 dir:2;
पूर्ण blinkm_cmds[17] = अणु
  /* cmdअक्षर, cmdbyte, nr_args, nr_ret,  dir */
	अणु 'n', 0x6e, 3, 0, 1पूर्ण,
	अणु 'c', 0x63, 3, 0, 1पूर्ण,
	अणु 'h', 0x68, 3, 0, 1पूर्ण,
	अणु 'C', 0x43, 3, 0, 1पूर्ण,
	अणु 'H', 0x48, 3, 0, 1पूर्ण,
	अणु 'p', 0x70, 3, 0, 1पूर्ण,
	अणु 'o', 0x6f, 0, 0, 1पूर्ण,
	अणु 'f', 0x66, 1, 0, 1पूर्ण,
	अणु 't', 0x74, 1, 0, 1पूर्ण,
	अणु 'g', 0x67, 0, 3, 0पूर्ण,
	अणु 'W', 0x57, 7, 0, 1पूर्ण,
	अणु 'R', 0x52, 2, 5, 2पूर्ण,
	अणु 'L', 0x4c, 3, 0, 1पूर्ण,
	अणु 'A', 0x41, 4, 0, 1पूर्ण,
	अणु 'a', 0x61, 0, 1, 0पूर्ण,
	अणु 'Z', 0x5a, 0, 1, 0पूर्ण,
	अणु 'B', 0x42, 5, 0, 1पूर्ण,
पूर्ण;

अटल sमाप_प्रकार show_color_common(काष्ठा device *dev, अक्षर *buf, पूर्णांक color)
अणु
	काष्ठा i2c_client *client;
	काष्ठा blinkm_data *data;
	पूर्णांक ret;

	client = to_i2c_client(dev);
	data = i2c_get_clientdata(client);

	ret = blinkm_transfer_hw(client, BLM_GET_CUR_RGB);
	अगर (ret < 0)
		वापस ret;
	चयन (color) अणु
	हाल RED:
		वापस scnम_लिखो(buf, PAGE_SIZE, "%02X\n", data->red);
	हाल GREEN:
		वापस scnम_लिखो(buf, PAGE_SIZE, "%02X\n", data->green);
	हाल BLUE:
		वापस scnम_लिखो(buf, PAGE_SIZE, "%02X\n", data->blue);
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक store_color_common(काष्ठा device *dev, स्थिर अक्षर *buf, पूर्णांक color)
अणु
	काष्ठा i2c_client *client;
	काष्ठा blinkm_data *data;
	पूर्णांक ret;
	u8 value;

	client = to_i2c_client(dev);
	data = i2c_get_clientdata(client);

	ret = kstrtou8(buf, 10, &value);
	अगर (ret < 0) अणु
		dev_err(dev, "BlinkM: value too large!\n");
		वापस ret;
	पूर्ण

	चयन (color) अणु
	हाल RED:
		data->next_red = value;
		अवरोध;
	हाल GREEN:
		data->next_green = value;
		अवरोध;
	हाल BLUE:
		data->next_blue = value;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	dev_dbg(dev, "next_red = %d, next_green = %d, next_blue = %d\n",
			data->next_red, data->next_green, data->next_blue);

	/* अगर mode ... */
	ret = blinkm_transfer_hw(client, BLM_GO_RGB);
	अगर (ret < 0) अणु
		dev_err(dev, "BlinkM: can't set RGB\n");
		वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल sमाप_प्रकार red_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			अक्षर *buf)
अणु
	वापस show_color_common(dev, buf, RED);
पूर्ण

अटल sमाप_प्रकार red_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक ret;

	ret = store_color_common(dev, buf, RED);
	अगर (ret < 0)
		वापस ret;
	वापस count;
पूर्ण

अटल DEVICE_ATTR_RW(red);

अटल sमाप_प्रकार green_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			  अक्षर *buf)
अणु
	वापस show_color_common(dev, buf, GREEN);
पूर्ण

अटल sमाप_प्रकार green_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			   स्थिर अक्षर *buf, माप_प्रकार count)
अणु

	पूर्णांक ret;

	ret = store_color_common(dev, buf, GREEN);
	अगर (ret < 0)
		वापस ret;
	वापस count;
पूर्ण

अटल DEVICE_ATTR_RW(green);

अटल sमाप_प्रकार blue_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			 अक्षर *buf)
अणु
	वापस show_color_common(dev, buf, BLUE);
पूर्ण

अटल sमाप_प्रकार blue_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक ret;

	ret = store_color_common(dev, buf, BLUE);
	अगर (ret < 0)
		वापस ret;
	वापस count;
पूर्ण

अटल DEVICE_ATTR_RW(blue);

अटल sमाप_प्रकार test_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			 अक्षर *buf)
अणु
	वापस scnम_लिखो(buf, PAGE_SIZE,
			 "#Write into test to start test sequence!#\n");
पूर्ण

अटल sमाप_प्रकार test_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			  स्थिर अक्षर *buf, माप_प्रकार count)
अणु

	काष्ठा i2c_client *client;
	पूर्णांक ret;
	client = to_i2c_client(dev);

	/*test */
	ret = blinkm_test_run(client);
	अगर (ret < 0)
		वापस ret;

	वापस count;
पूर्ण

अटल DEVICE_ATTR_RW(test);

/* TODO: HSB, fade, समयadj, script ... */

अटल काष्ठा attribute *blinkm_attrs[] = अणु
	&dev_attr_red.attr,
	&dev_attr_green.attr,
	&dev_attr_blue.attr,
	&dev_attr_test.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group blinkm_group = अणु
	.name = "blinkm",
	.attrs = blinkm_attrs,
पूर्ण;

अटल पूर्णांक blinkm_ग_लिखो(काष्ठा i2c_client *client, पूर्णांक cmd, u8 *arg)
अणु
	पूर्णांक result;
	पूर्णांक i;
	पूर्णांक arglen = blinkm_cmds[cmd].nr_args;
	/* ग_लिखो out cmd to blinkm - always / शेष step */
	result = i2c_smbus_ग_लिखो_byte(client, blinkm_cmds[cmd].cmdbyte);
	अगर (result < 0)
		वापस result;
	/* no args to ग_लिखो out */
	अगर (arglen == 0)
		वापस 0;

	क्रम (i = 0; i < arglen; i++) अणु
		/* repeat क्रम arglen */
		result = i2c_smbus_ग_लिखो_byte(client, arg[i]);
		अगर (result < 0)
			वापस result;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक blinkm_पढ़ो(काष्ठा i2c_client *client, पूर्णांक cmd, u8 *arg)
अणु
	पूर्णांक result;
	पूर्णांक i;
	पूर्णांक retlen = blinkm_cmds[cmd].nr_ret;
	क्रम (i = 0; i < retlen; i++) अणु
		/* repeat क्रम retlen */
		result = i2c_smbus_पढ़ो_byte(client);
		अगर (result < 0)
			वापस result;
		arg[i] = result;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक blinkm_transfer_hw(काष्ठा i2c_client *client, पूर्णांक cmd)
अणु
	/* the protocol is simple but non-standard:
	 * e.g.  cmd 'g' (= 0x67) क्रम "get device address"
	 * - which शेषs to 0x09 - would be the sequence:
	 *   a) ग_लिखो 0x67 to the device (byte ग_लिखो)
	 *   b) पढ़ो the value (0x09) back right after (byte पढ़ो)
	 *
	 * Watch out क्रम "unfinished" sequences (i.e. not enough पढ़ोs
	 * or ग_लिखोs after a command. It will make the blinkM misbehave.
	 * Sequence is key here.
	 */

	/* args / वापस are in निजी data काष्ठा */
	काष्ठा blinkm_data *data = i2c_get_clientdata(client);

	/* We start hardware transfers which are not to be
	 * mixed with other commands. Aquire a lock now. */
	अगर (mutex_lock_पूर्णांकerruptible(&data->update_lock) < 0)
		वापस -EAGAIN;

	/* चयन cmd - usually ग_लिखो beक्रमe पढ़ोs */
	चयन (cmd) अणु
	हाल BLM_FADE_RAND_RGB:
	हाल BLM_GO_RGB:
	हाल BLM_FADE_RGB:
		data->args[0] = data->next_red;
		data->args[1] = data->next_green;
		data->args[2] = data->next_blue;
		blinkm_ग_लिखो(client, cmd, data->args);
		data->red = data->args[0];
		data->green = data->args[1];
		data->blue = data->args[2];
		अवरोध;
	हाल BLM_FADE_HSB:
	हाल BLM_FADE_RAND_HSB:
		data->args[0] = data->next_hue;
		data->args[1] = data->next_saturation;
		data->args[2] = data->next_brightness;
		blinkm_ग_लिखो(client, cmd, data->args);
		data->hue = data->next_hue;
		data->saturation = data->next_saturation;
		data->brightness = data->next_brightness;
		अवरोध;
	हाल BLM_PLAY_SCRIPT:
		data->args[0] = data->script_id;
		data->args[1] = data->script_repeats;
		data->args[2] = data->script_startline;
		blinkm_ग_लिखो(client, cmd, data->args);
		अवरोध;
	हाल BLM_STOP_SCRIPT:
		blinkm_ग_लिखो(client, cmd, शून्य);
		अवरोध;
	हाल BLM_GET_CUR_RGB:
		data->args[0] = data->red;
		data->args[1] = data->green;
		data->args[2] = data->blue;
		blinkm_ग_लिखो(client, cmd, शून्य);
		blinkm_पढ़ो(client, cmd, data->args);
		data->red = data->args[0];
		data->green = data->args[1];
		data->blue = data->args[2];
		अवरोध;
	हाल BLM_GET_ADDR:
		data->args[0] = data->i2c_addr;
		blinkm_ग_लिखो(client, cmd, शून्य);
		blinkm_पढ़ो(client, cmd, data->args);
		data->i2c_addr = data->args[0];
		अवरोध;
	हाल BLM_SET_TIME_ADJ:
	हाल BLM_SET_FADE_SPEED:
	हाल BLM_READ_SCRIPT_LINE:
	हाल BLM_WRITE_SCRIPT_LINE:
	हाल BLM_SET_SCRIPT_LR:
	हाल BLM_SET_ADDR:
	हाल BLM_GET_FW_VER:
	हाल BLM_SET_STARTUP_PARAM:
		dev_err(&client->dev,
				"BlinkM: cmd %d not implemented yet.\n", cmd);
		अवरोध;
	शेष:
		dev_err(&client->dev, "BlinkM: unknown command %d\n", cmd);
		mutex_unlock(&data->update_lock);
		वापस -EINVAL;
	पूर्ण			/* end चयन(cmd) */

	/* transfers करोne, unlock */
	mutex_unlock(&data->update_lock);
	वापस 0;
पूर्ण

अटल पूर्णांक blinkm_led_common_set(काष्ठा led_classdev *led_cdev,
				 क्रमागत led_brightness value, पूर्णांक color)
अणु
	/* led_brightness is 0, 127 or 255 - we just use it here as-is */
	काष्ठा blinkm_led *led = cdev_to_blmled(led_cdev);
	काष्ठा blinkm_data *data = i2c_get_clientdata(led->i2c_client);

	चयन (color) अणु
	हाल RED:
		/* bail out अगर there's no change */
		अगर (data->next_red == (u8) value)
			वापस 0;
		data->next_red = (u8) value;
		अवरोध;
	हाल GREEN:
		/* bail out अगर there's no change */
		अगर (data->next_green == (u8) value)
			वापस 0;
		data->next_green = (u8) value;
		अवरोध;
	हाल BLUE:
		/* bail out अगर there's no change */
		अगर (data->next_blue == (u8) value)
			वापस 0;
		data->next_blue = (u8) value;
		अवरोध;

	शेष:
		dev_err(&led->i2c_client->dev, "BlinkM: unknown color.\n");
		वापस -EINVAL;
	पूर्ण

	blinkm_transfer_hw(led->i2c_client, BLM_GO_RGB);
	dev_dbg(&led->i2c_client->dev,
			"# DONE # next_red = %d, next_green = %d,"
			" next_blue = %d\n",
			data->next_red, data->next_green,
			data->next_blue);
	वापस 0;
पूर्ण

अटल पूर्णांक blinkm_led_red_set(काष्ठा led_classdev *led_cdev,
			       क्रमागत led_brightness value)
अणु
	वापस blinkm_led_common_set(led_cdev, value, RED);
पूर्ण

अटल पूर्णांक blinkm_led_green_set(काष्ठा led_classdev *led_cdev,
				 क्रमागत led_brightness value)
अणु
	वापस blinkm_led_common_set(led_cdev, value, GREEN);
पूर्ण

अटल पूर्णांक blinkm_led_blue_set(काष्ठा led_classdev *led_cdev,
				क्रमागत led_brightness value)
अणु
	वापस blinkm_led_common_set(led_cdev, value, BLUE);
पूर्ण

अटल व्योम blinkm_init_hw(काष्ठा i2c_client *client)
अणु
	पूर्णांक ret;
	ret = blinkm_transfer_hw(client, BLM_STOP_SCRIPT);
	ret = blinkm_transfer_hw(client, BLM_GO_RGB);
पूर्ण

अटल पूर्णांक blinkm_test_run(काष्ठा i2c_client *client)
अणु
	पूर्णांक ret;
	काष्ठा blinkm_data *data = i2c_get_clientdata(client);

	data->next_red = 0x01;
	data->next_green = 0x05;
	data->next_blue = 0x10;
	ret = blinkm_transfer_hw(client, BLM_GO_RGB);
	अगर (ret < 0)
		वापस ret;
	msleep(2000);

	data->next_red = 0x25;
	data->next_green = 0x10;
	data->next_blue = 0x31;
	ret = blinkm_transfer_hw(client, BLM_FADE_RGB);
	अगर (ret < 0)
		वापस ret;
	msleep(2000);

	data->next_hue = 0x50;
	data->next_saturation = 0x10;
	data->next_brightness = 0x20;
	ret = blinkm_transfer_hw(client, BLM_FADE_HSB);
	अगर (ret < 0)
		वापस ret;
	msleep(2000);

	वापस 0;
पूर्ण

/* Return 0 अगर detection is successful, -ENODEV otherwise */
अटल पूर्णांक blinkm_detect(काष्ठा i2c_client *client, काष्ठा i2c_board_info *info)
अणु
	काष्ठा i2c_adapter *adapter = client->adapter;
	पूर्णांक ret;
	पूर्णांक count = 99;
	u8 पंचांगpargs[7];

	अगर (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_BYTE_DATA
				     | I2C_FUNC_SMBUS_WORD_DATA
				     | I2C_FUNC_SMBUS_WRITE_BYTE))
		वापस -ENODEV;

	/* Now, we करो the reमुख्यing detection. Simple क्रम now. */
	/* We might need more guards to protect other i2c slaves */

	/* make sure the blinkM is balanced (पढ़ो/ग_लिखोs) */
	जबतक (count > 0) अणु
		ret = blinkm_ग_लिखो(client, BLM_GET_ADDR, शून्य);
		अगर (ret)
			वापस ret;
		usleep_range(5000, 10000);
		ret = blinkm_पढ़ो(client, BLM_GET_ADDR, पंचांगpargs);
		अगर (ret)
			वापस ret;
		usleep_range(5000, 10000);
		अगर (पंचांगpargs[0] == 0x09)
			count = 0;
		count--;
	पूर्ण

	/* Step 1: Read BlinkM address back  -  cmd_अक्षर 'a' */
	ret = blinkm_ग_लिखो(client, BLM_GET_ADDR, शून्य);
	अगर (ret < 0)
		वापस ret;
	usleep_range(20000, 30000);	/* allow a small delay */
	ret = blinkm_पढ़ो(client, BLM_GET_ADDR, पंचांगpargs);
	अगर (ret < 0)
		वापस ret;

	अगर (पंचांगpargs[0] != 0x09) अणु
		dev_err(&client->dev, "enodev DEV ADDR = 0x%02X\n", पंचांगpargs[0]);
		वापस -ENODEV;
	पूर्ण

	strlcpy(info->type, "blinkm", I2C_NAME_SIZE);
	वापस 0;
पूर्ण

अटल पूर्णांक blinkm_probe(काष्ठा i2c_client *client,
			स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा blinkm_data *data;
	काष्ठा blinkm_led *led[3];
	पूर्णांक err, i;
	अक्षर blinkm_led_name[28];

	data = devm_kzalloc(&client->dev,
			माप(काष्ठा blinkm_data), GFP_KERNEL);
	अगर (!data) अणु
		err = -ENOMEM;
		जाओ निकास;
	पूर्ण

	data->i2c_addr = 0x08;
	/* i2c addr  - use fake addr of 0x08 initially (real is 0x09) */
	data->fw_ver = 0xfe;
	/* firmware version - use fake until we पढ़ो real value
	 * (currently broken - BlinkM confused!) */
	data->script_id = 0x01;
	data->i2c_client = client;

	i2c_set_clientdata(client, data);
	mutex_init(&data->update_lock);

	/* Register sysfs hooks */
	err = sysfs_create_group(&client->dev.kobj, &blinkm_group);
	अगर (err < 0) अणु
		dev_err(&client->dev, "couldn't register sysfs group\n");
		जाओ निकास;
	पूर्ण

	क्रम (i = 0; i < 3; i++) अणु
		/* RED = 0, GREEN = 1, BLUE = 2 */
		led[i] = &data->blinkm_leds[i];
		led[i]->i2c_client = client;
		led[i]->id = i;
		led[i]->led_cdev.max_brightness = 255;
		led[i]->led_cdev.flags = LED_CORE_SUSPENDRESUME;
		चयन (i) अणु
		हाल RED:
			snम_लिखो(blinkm_led_name, माप(blinkm_led_name),
					 "blinkm-%d-%d-red",
					 client->adapter->nr,
					 client->addr);
			led[i]->led_cdev.name = blinkm_led_name;
			led[i]->led_cdev.brightness_set_blocking =
							blinkm_led_red_set;
			err = led_classdev_रेजिस्टर(&client->dev,
						    &led[i]->led_cdev);
			अगर (err < 0) अणु
				dev_err(&client->dev,
					"couldn't register LED %s\n",
					led[i]->led_cdev.name);
				जाओ failred;
			पूर्ण
			अवरोध;
		हाल GREEN:
			snम_लिखो(blinkm_led_name, माप(blinkm_led_name),
					 "blinkm-%d-%d-green",
					 client->adapter->nr,
					 client->addr);
			led[i]->led_cdev.name = blinkm_led_name;
			led[i]->led_cdev.brightness_set_blocking =
							blinkm_led_green_set;
			err = led_classdev_रेजिस्टर(&client->dev,
						    &led[i]->led_cdev);
			अगर (err < 0) अणु
				dev_err(&client->dev,
					"couldn't register LED %s\n",
					led[i]->led_cdev.name);
				जाओ failgreen;
			पूर्ण
			अवरोध;
		हाल BLUE:
			snम_लिखो(blinkm_led_name, माप(blinkm_led_name),
					 "blinkm-%d-%d-blue",
					 client->adapter->nr,
					 client->addr);
			led[i]->led_cdev.name = blinkm_led_name;
			led[i]->led_cdev.brightness_set_blocking =
							blinkm_led_blue_set;
			err = led_classdev_रेजिस्टर(&client->dev,
						    &led[i]->led_cdev);
			अगर (err < 0) अणु
				dev_err(&client->dev,
					"couldn't register LED %s\n",
					led[i]->led_cdev.name);
				जाओ failblue;
			पूर्ण
			अवरोध;
		पूर्ण		/* end चयन */
	पूर्ण			/* end क्रम */

	/* Initialize the blinkm */
	blinkm_init_hw(client);

	वापस 0;

failblue:
	led_classdev_unरेजिस्टर(&led[GREEN]->led_cdev);

failgreen:
	led_classdev_unरेजिस्टर(&led[RED]->led_cdev);

failred:
	sysfs_हटाओ_group(&client->dev.kobj, &blinkm_group);
निकास:
	वापस err;
पूर्ण

अटल पूर्णांक blinkm_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा blinkm_data *data = i2c_get_clientdata(client);
	पूर्णांक ret = 0;
	पूर्णांक i;

	/* make sure no workqueue entries are pending */
	क्रम (i = 0; i < 3; i++)
		led_classdev_unरेजिस्टर(&data->blinkm_leds[i].led_cdev);

	/* reset rgb */
	data->next_red = 0x00;
	data->next_green = 0x00;
	data->next_blue = 0x00;
	ret = blinkm_transfer_hw(client, BLM_FADE_RGB);
	अगर (ret < 0)
		dev_err(&client->dev, "Failure in blinkm_remove ignored. Continuing.\n");

	/* reset hsb */
	data->next_hue = 0x00;
	data->next_saturation = 0x00;
	data->next_brightness = 0x00;
	ret = blinkm_transfer_hw(client, BLM_FADE_HSB);
	अगर (ret < 0)
		dev_err(&client->dev, "Failure in blinkm_remove ignored. Continuing.\n");

	/* red fade to off */
	data->next_red = 0xff;
	ret = blinkm_transfer_hw(client, BLM_GO_RGB);
	अगर (ret < 0)
		dev_err(&client->dev, "Failure in blinkm_remove ignored. Continuing.\n");

	/* off */
	data->next_red = 0x00;
	ret = blinkm_transfer_hw(client, BLM_FADE_RGB);
	अगर (ret < 0)
		dev_err(&client->dev, "Failure in blinkm_remove ignored. Continuing.\n");

	sysfs_हटाओ_group(&client->dev.kobj, &blinkm_group);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id blinkm_id[] = अणु
	अणु"blinkm", 0पूर्ण,
	अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(i2c, blinkm_id);

  /* This is the driver that will be inserted */
अटल काष्ठा i2c_driver blinkm_driver = अणु
	.class = I2C_CLASS_HWMON,
	.driver = अणु
		   .name = "blinkm",
		   पूर्ण,
	.probe = blinkm_probe,
	.हटाओ = blinkm_हटाओ,
	.id_table = blinkm_id,
	.detect = blinkm_detect,
	.address_list = normal_i2c,
पूर्ण;

module_i2c_driver(blinkm_driver);

MODULE_AUTHOR("Jan-Simon Moeller <dl9pf@gmx.de>");
MODULE_DESCRIPTION("BlinkM RGB LED driver");
MODULE_LICENSE("GPL");

