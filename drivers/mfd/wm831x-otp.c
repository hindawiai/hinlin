<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * wm831x-otp.c  --  OTP क्रम Wolfson WM831x PMICs
 *
 * Copyright 2009 Wolfson Microelectronics PLC.
 *
 * Author: Mark Brown <broonie@खोलोsource.wolfsonmicro.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/i2c.h>
#समावेश <linux/bcd.h>
#समावेश <linux/delay.h>
#समावेश <linux/mfd/core.h>
#समावेश <linux/अक्रमom.h>

#समावेश <linux/mfd/wm831x/core.h>
#समावेश <linux/mfd/wm831x/otp.h>

/* In bytes */
#घोषणा WM831X_UNIQUE_ID_LEN 16

/* Read the unique ID from the chip पूर्णांकo id */
अटल पूर्णांक wm831x_unique_id_पढ़ो(काष्ठा wm831x *wm831x, अक्षर *id)
अणु
	पूर्णांक i, val;

	क्रम (i = 0; i < WM831X_UNIQUE_ID_LEN / 2; i++) अणु
		val = wm831x_reg_पढ़ो(wm831x, WM831X_UNIQUE_ID_1 + i);
		अगर (val < 0)
			वापस val;

		id[i * 2]       = (val >> 8) & 0xff;
		id[(i * 2) + 1] = val & 0xff;
	पूर्ण

	वापस 0;
पूर्ण

अटल sमाप_प्रकार wm831x_unique_id_show(काष्ठा device *dev,
				     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा wm831x *wm831x = dev_get_drvdata(dev);
	पूर्णांक rval;
	अक्षर id[WM831X_UNIQUE_ID_LEN];

	rval = wm831x_unique_id_पढ़ो(wm831x, id);
	अगर (rval < 0)
		वापस 0;

	वापस प्र_लिखो(buf, "%*phN\n", WM831X_UNIQUE_ID_LEN, id);
पूर्ण

अटल DEVICE_ATTR(unique_id, 0444, wm831x_unique_id_show, शून्य);

पूर्णांक wm831x_otp_init(काष्ठा wm831x *wm831x)
अणु
	अक्षर uuid[WM831X_UNIQUE_ID_LEN];
	पूर्णांक ret;

	ret = device_create_file(wm831x->dev, &dev_attr_unique_id);
	अगर (ret != 0)
		dev_err(wm831x->dev, "Unique ID attribute not created: %d\n",
			ret);

	ret = wm831x_unique_id_पढ़ो(wm831x, uuid);
	अगर (ret == 0)
		add_device_अक्रमomness(uuid, माप(uuid));
	अन्यथा
		dev_err(wm831x->dev, "Failed to read UUID: %d\n", ret);

	वापस ret;
पूर्ण

व्योम wm831x_otp_निकास(काष्ठा wm831x *wm831x)
अणु
	device_हटाओ_file(wm831x->dev, &dev_attr_unique_id);
पूर्ण

