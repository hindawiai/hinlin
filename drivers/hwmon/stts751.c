<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * STTS751 sensor driver
 *
 * Copyright (C) 2016-2017 Istituto Italiano di Tecnologia - RBCS - EDL
 * Robotics, Brain and Cognitive Sciences deparपंचांगent
 * Electronic Design Laboratory
 *
 * Written by Andrea Merello <andrea.merello@gmail.com>
 *
 * Based on  LM95241 driver and LM90 driver
 */

#समावेश <linux/bitops.h>
#समावेश <linux/err.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/hwmon-sysfs.h>
#समावेश <linux/i2c.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/property.h>
#समावेश <linux/slab.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/util_macros.h>

#घोषणा DEVNAME "stts751"

अटल स्थिर अचिन्हित लघु normal_i2c[] = अणु
	0x48, 0x49, 0x38, 0x39,  /* STTS751-0 */
	0x4A, 0x4B, 0x3A, 0x3B,  /* STTS751-1 */
	I2C_CLIENT_END पूर्ण;

#घोषणा STTS751_REG_TEMP_H	0x00
#घोषणा STTS751_REG_STATUS	0x01
#घोषणा STTS751_STATUS_TRIPT	BIT(0)
#घोषणा STTS751_STATUS_TRIPL	BIT(5)
#घोषणा STTS751_STATUS_TRIPH	BIT(6)
#घोषणा STTS751_REG_TEMP_L	0x02
#घोषणा STTS751_REG_CONF	0x03
#घोषणा STTS751_CONF_RES_MASK	0x0C
#घोषणा STTS751_CONF_RES_SHIFT  2
#घोषणा STTS751_CONF_EVENT_DIS  BIT(7)
#घोषणा STTS751_CONF_STOP	BIT(6)
#घोषणा STTS751_REG_RATE	0x04
#घोषणा STTS751_REG_HLIM_H	0x05
#घोषणा STTS751_REG_HLIM_L	0x06
#घोषणा STTS751_REG_LLIM_H	0x07
#घोषणा STTS751_REG_LLIM_L	0x08
#घोषणा STTS751_REG_TLIM	0x20
#घोषणा STTS751_REG_HYST	0x21
#घोषणा STTS751_REG_SMBUS_TO	0x22

#घोषणा STTS751_REG_PROD_ID	0xFD
#घोषणा STTS751_REG_MAN_ID	0xFE
#घोषणा STTS751_REG_REV_ID	0xFF

#घोषणा STTS751_0_PROD_ID	0x00
#घोषणा STTS751_1_PROD_ID	0x01
#घोषणा ST_MAN_ID		0x53

/*
 * Possible update पूर्णांकervals are (in mS):
 * 16000, 8000, 4000, 2000, 1000, 500, 250, 125, 62.5, 31.25
 * However we are not going to complicate things too much and we stick to the
 * approx value in mS.
 */
अटल स्थिर पूर्णांक stts751_पूर्णांकervals[] = अणु
	16000, 8000, 4000, 2000, 1000, 500, 250, 125, 63, 31
पूर्ण;

अटल स्थिर काष्ठा i2c_device_id stts751_id[] = अणु
	अणु "stts751", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल स्थिर काष्ठा of_device_id __maybe_unused stts751_of_match[] = अणु
	अणु .compatible = "stts751" पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, stts751_of_match);

काष्ठा stts751_priv अणु
	काष्ठा device *dev;
	काष्ठा i2c_client *client;
	काष्ठा mutex access_lock;
	u8 पूर्णांकerval;
	पूर्णांक res;
	पूर्णांक event_max, event_min;
	पूर्णांक therm;
	पूर्णांक hyst;
	bool smbus_समयout;
	पूर्णांक temp;
	अचिन्हित दीर्घ last_update, last_alert_update;
	u8 config;
	bool min_alert, max_alert, therm_trip;
	bool data_valid, alert_valid;
	bool notअगरy_max, notअगरy_min;
पूर्ण;

/*
 * These functions converts temperature from HW क्रमmat to पूर्णांकeger क्रमmat and
 * vice-vers. They are (mostly) taken from lm90 driver. Unit is in mC.
 */
अटल पूर्णांक stts751_to_deg(s16 hw_val)
अणु
	वापस hw_val * 125 / 32;
पूर्ण

अटल s32 stts751_to_hw(पूर्णांक val)
अणु
	वापस DIV_ROUND_CLOSEST(val, 125) * 32;
पूर्ण

अटल पूर्णांक stts751_adjust_resolution(काष्ठा stts751_priv *priv)
अणु
	u8 res;

	चयन (priv->पूर्णांकerval) अणु
	हाल 9:
		/* 10 bits */
		res = 0;
		अवरोध;
	हाल 8:
		/* 11 bits */
		res = 1;
		अवरोध;
	शेष:
		/* 12 bits */
		res = 3;
		अवरोध;
	पूर्ण

	अगर (priv->res == res)
		वापस 0;

	priv->config &= ~STTS751_CONF_RES_MASK;
	priv->config |= res << STTS751_CONF_RES_SHIFT;
	dev_dbg(&priv->client->dev, "setting res %d. config %x",
		res, priv->config);
	priv->res = res;

	वापस i2c_smbus_ग_लिखो_byte_data(priv->client,
				STTS751_REG_CONF, priv->config);
पूर्ण

अटल पूर्णांक stts751_update_temp(काष्ठा stts751_priv *priv)
अणु
	s32 पूर्णांकeger1, पूर्णांकeger2, frac;

	/*
	 * There is a trick here, like in the lm90 driver. We have to पढ़ो two
	 * रेजिस्टरs to get the sensor temperature, but we have to beware a
	 * conversion could occur between the पढ़ोings. We could use the
	 * one-shot conversion रेजिस्टर, but we करोn't want to करो this (disables
	 * hardware monitoring). So the solution used here is to पढ़ो the high
	 * byte once, then the low byte, then the high byte again. If the new
	 * high byte matches the old one, then we have a valid पढ़ोing. Else we
	 * have to पढ़ो the low byte again, and now we believe we have a correct
	 * पढ़ोing.
	 */
	पूर्णांकeger1 = i2c_smbus_पढ़ो_byte_data(priv->client, STTS751_REG_TEMP_H);
	अगर (पूर्णांकeger1 < 0) अणु
		dev_dbg(&priv->client->dev,
			"I2C read failed (temp H). ret: %x\n", पूर्णांकeger1);
		वापस पूर्णांकeger1;
	पूर्ण

	frac = i2c_smbus_पढ़ो_byte_data(priv->client, STTS751_REG_TEMP_L);
	अगर (frac < 0) अणु
		dev_dbg(&priv->client->dev,
			"I2C read failed (temp L). ret: %x\n", frac);
		वापस frac;
	पूर्ण

	पूर्णांकeger2 = i2c_smbus_पढ़ो_byte_data(priv->client, STTS751_REG_TEMP_H);
	अगर (पूर्णांकeger2 < 0) अणु
		dev_dbg(&priv->client->dev,
			"I2C 2nd read failed (temp H). ret: %x\n", पूर्णांकeger2);
		वापस पूर्णांकeger2;
	पूर्ण

	अगर (पूर्णांकeger1 != पूर्णांकeger2) अणु
		frac = i2c_smbus_पढ़ो_byte_data(priv->client,
						STTS751_REG_TEMP_L);
		अगर (frac < 0) अणु
			dev_dbg(&priv->client->dev,
				"I2C 2nd read failed (temp L). ret: %x\n",
				frac);
			वापस frac;
		पूर्ण
	पूर्ण

	priv->temp = stts751_to_deg((पूर्णांकeger1 << 8) | frac);
	वापस 0;
पूर्ण

अटल पूर्णांक stts751_set_temp_reg16(काष्ठा stts751_priv *priv, पूर्णांक temp,
				  u8 hreg, u8 lreg)
अणु
	s32 hwval;
	पूर्णांक ret;

	hwval = stts751_to_hw(temp);

	ret = i2c_smbus_ग_लिखो_byte_data(priv->client, hreg, hwval >> 8);
	अगर (ret)
		वापस ret;

	वापस i2c_smbus_ग_लिखो_byte_data(priv->client, lreg, hwval & 0xff);
पूर्ण

अटल पूर्णांक stts751_set_temp_reg8(काष्ठा stts751_priv *priv, पूर्णांक temp, u8 reg)
अणु
	s32 hwval;

	hwval = stts751_to_hw(temp);
	वापस i2c_smbus_ग_लिखो_byte_data(priv->client, reg, hwval >> 8);
पूर्ण

अटल पूर्णांक stts751_पढ़ो_reg16(काष्ठा stts751_priv *priv, पूर्णांक *temp,
			      u8 hreg, u8 lreg)
अणु
	पूर्णांक पूर्णांकeger, frac;

	पूर्णांकeger = i2c_smbus_पढ़ो_byte_data(priv->client, hreg);
	अगर (पूर्णांकeger < 0)
		वापस पूर्णांकeger;

	frac = i2c_smbus_पढ़ो_byte_data(priv->client, lreg);
	अगर (frac < 0)
		वापस frac;

	*temp = stts751_to_deg((पूर्णांकeger << 8) | frac);

	वापस 0;
पूर्ण

अटल पूर्णांक stts751_पढ़ो_reg8(काष्ठा stts751_priv *priv, पूर्णांक *temp, u8 reg)
अणु
	पूर्णांक पूर्णांकeger;

	पूर्णांकeger = i2c_smbus_पढ़ो_byte_data(priv->client, reg);
	अगर (पूर्णांकeger < 0)
		वापस पूर्णांकeger;

	*temp = stts751_to_deg(पूर्णांकeger << 8);

	वापस 0;
पूर्ण

/*
 * Update alert flags without रुकोing क्रम cache to expire. We detects alerts
 * immediately क्रम the sake of the alert handler; we still need to deal with
 * caching to workaround the fact that alarm flags पूर्णांक the status रेजिस्टर,
 * despite what the datasheet claims, माला_लो always cleared on पढ़ो.
 */
अटल पूर्णांक stts751_update_alert(काष्ठा stts751_priv *priv)
अणु
	पूर्णांक ret;
	bool conv_करोne;
	पूर्णांक cache_समय = msecs_to_jअगरfies(stts751_पूर्णांकervals[priv->पूर्णांकerval]);

	/*
	 * Add another 10% because अगर we run faster than the HW conversion
	 * rate we will end up in reporting incorrectly alarms.
	 */
	cache_समय += cache_समय / 10;

	ret = i2c_smbus_पढ़ो_byte_data(priv->client, STTS751_REG_STATUS);
	अगर (ret < 0)
		वापस ret;

	dev_dbg(&priv->client->dev, "status reg %x\n", ret);
	conv_करोne = ret & (STTS751_STATUS_TRIPH | STTS751_STATUS_TRIPL);
	/*
	 * Reset the cache अगर the cache समय expired, or अगर we are sure
	 * we have valid data from a device conversion, or अगर we know
	 * our cache has been never written.
	 *
	 * Note that when the cache has been never written the poपूर्णांक is
	 * to correctly initialize the बारtamp, rather than clearing
	 * the cache values.
	 *
	 * Note that updating the cache बारtamp when we get an alarm flag
	 * is required, otherwise we could incorrectly report alarms to be zero.
	 */
	अगर (समय_after(jअगरfies,	priv->last_alert_update + cache_समय) ||
	    conv_करोne || !priv->alert_valid) अणु
		priv->max_alert = false;
		priv->min_alert = false;
		priv->alert_valid = true;
		priv->last_alert_update = jअगरfies;
		dev_dbg(&priv->client->dev, "invalidating alert cache\n");
	पूर्ण

	priv->max_alert |= !!(ret & STTS751_STATUS_TRIPH);
	priv->min_alert |= !!(ret & STTS751_STATUS_TRIPL);
	priv->therm_trip = !!(ret & STTS751_STATUS_TRIPT);

	dev_dbg(&priv->client->dev, "max_alert: %d, min_alert: %d, therm_trip: %d\n",
		priv->max_alert, priv->min_alert, priv->therm_trip);

	वापस 0;
पूर्ण

अटल व्योम stts751_alert(काष्ठा i2c_client *client,
			  क्रमागत i2c_alert_protocol type, अचिन्हित पूर्णांक data)
अणु
	पूर्णांक ret;
	काष्ठा stts751_priv *priv = i2c_get_clientdata(client);

	अगर (type != I2C_PROTOCOL_SMBUS_ALERT)
		वापस;

	dev_dbg(&client->dev, "alert!");

	mutex_lock(&priv->access_lock);
	ret = stts751_update_alert(priv);
	अगर (ret < 0) अणु
		/* शेष to worst हाल */
		priv->max_alert = true;
		priv->min_alert = true;

		dev_warn(priv->dev,
			 "Alert received, but can't communicate to the device. Triggering all alarms!");
	पूर्ण

	अगर (priv->max_alert) अणु
		अगर (priv->notअगरy_max)
			dev_notice(priv->dev, "got alert for HIGH temperature");
		priv->notअगरy_max = false;

		/* unblock alert poll */
		sysfs_notअगरy(&priv->dev->kobj, शून्य, "temp1_max_alarm");
	पूर्ण

	अगर (priv->min_alert) अणु
		अगर (priv->notअगरy_min)
			dev_notice(priv->dev, "got alert for LOW temperature");
		priv->notअगरy_min = false;

		/* unblock alert poll */
		sysfs_notअगरy(&priv->dev->kobj, शून्य, "temp1_min_alarm");
	पूर्ण

	अगर (priv->min_alert || priv->max_alert)
		kobject_uevent(&priv->dev->kobj, KOBJ_CHANGE);

	mutex_unlock(&priv->access_lock);
पूर्ण

अटल पूर्णांक stts751_update(काष्ठा stts751_priv *priv)
अणु
	पूर्णांक ret;
	पूर्णांक cache_समय = msecs_to_jअगरfies(stts751_पूर्णांकervals[priv->पूर्णांकerval]);

	अगर (समय_after(jअगरfies,	priv->last_update + cache_समय) ||
	    !priv->data_valid) अणु
		ret = stts751_update_temp(priv);
		अगर (ret)
			वापस ret;

		ret = stts751_update_alert(priv);
		अगर (ret)
			वापस ret;
		priv->data_valid = true;
		priv->last_update = jअगरfies;
	पूर्ण

	वापस 0;
पूर्ण

अटल sमाप_प्रकार max_alarm_show(काष्ठा device *dev,
			      काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	पूर्णांक ret;
	काष्ठा stts751_priv *priv = dev_get_drvdata(dev);

	mutex_lock(&priv->access_lock);
	ret = stts751_update(priv);
	अगर (!ret)
		priv->notअगरy_max = true;
	mutex_unlock(&priv->access_lock);
	अगर (ret < 0)
		वापस ret;

	वापस sysfs_emit(buf, "%d\n", priv->max_alert);
पूर्ण

अटल sमाप_प्रकार min_alarm_show(काष्ठा device *dev,
			      काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	पूर्णांक ret;
	काष्ठा stts751_priv *priv = dev_get_drvdata(dev);

	mutex_lock(&priv->access_lock);
	ret = stts751_update(priv);
	अगर (!ret)
		priv->notअगरy_min = true;
	mutex_unlock(&priv->access_lock);
	अगर (ret < 0)
		वापस ret;

	वापस sysfs_emit(buf, "%d\n", priv->min_alert);
पूर्ण

अटल sमाप_प्रकार input_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			  अक्षर *buf)
अणु
	पूर्णांक ret;
	काष्ठा stts751_priv *priv = dev_get_drvdata(dev);

	mutex_lock(&priv->access_lock);
	ret = stts751_update(priv);
	mutex_unlock(&priv->access_lock);
	अगर (ret < 0)
		वापस ret;

	वापस sysfs_emit(buf, "%d\n", priv->temp);
पूर्ण

अटल sमाप_प्रकार therm_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			  अक्षर *buf)
अणु
	काष्ठा stts751_priv *priv = dev_get_drvdata(dev);

	वापस sysfs_emit(buf, "%d\n", priv->therm);
पूर्ण

अटल sमाप_प्रकार therm_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			   स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक ret;
	दीर्घ temp;
	काष्ठा stts751_priv *priv = dev_get_drvdata(dev);

	अगर (kम_से_दीर्घ(buf, 10, &temp) < 0)
		वापस -EINVAL;

	/* HW works in range -64C to +127.937C */
	temp = clamp_val(temp, -64000, 127937);
	mutex_lock(&priv->access_lock);
	ret = stts751_set_temp_reg8(priv, temp, STTS751_REG_TLIM);
	अगर (ret)
		जाओ निकास;

	dev_dbg(&priv->client->dev, "setting therm %ld", temp);

	/*
	 * hysteresis reg is relative to therm, so the HW करोes not need to be
	 * adjusted, we need to update our local copy only.
	 */
	priv->hyst = temp - (priv->therm - priv->hyst);
	priv->therm = temp;

निकास:
	mutex_unlock(&priv->access_lock);
	अगर (ret)
		वापस ret;

	वापस count;
पूर्ण

अटल sमाप_प्रकार hyst_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			 अक्षर *buf)
अणु
	काष्ठा stts751_priv *priv = dev_get_drvdata(dev);

	वापस sysfs_emit(buf, "%d\n", priv->hyst);
पूर्ण

अटल sमाप_प्रकार hyst_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक ret;
	दीर्घ temp;

	काष्ठा stts751_priv *priv = dev_get_drvdata(dev);

	अगर (kम_से_दीर्घ(buf, 10, &temp) < 0)
		वापस -EINVAL;

	mutex_lock(&priv->access_lock);
	/* HW works in range -64C to +127.937C */
	temp = clamp_val(temp, -64000, priv->therm);
	priv->hyst = temp;
	dev_dbg(&priv->client->dev, "setting hyst %ld", temp);
	temp = priv->therm - temp;
	ret = stts751_set_temp_reg8(priv, temp, STTS751_REG_HYST);
	mutex_unlock(&priv->access_lock);
	अगर (ret)
		वापस ret;

	वापस count;
पूर्ण

अटल sमाप_प्रकार therm_trip_show(काष्ठा device *dev,
			       काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	पूर्णांक ret;
	काष्ठा stts751_priv *priv = dev_get_drvdata(dev);

	mutex_lock(&priv->access_lock);
	ret = stts751_update(priv);
	mutex_unlock(&priv->access_lock);
	अगर (ret < 0)
		वापस ret;

	वापस sysfs_emit(buf, "%d\n", priv->therm_trip);
पूर्ण

अटल sमाप_प्रकार max_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			अक्षर *buf)
अणु
	काष्ठा stts751_priv *priv = dev_get_drvdata(dev);

	वापस sysfs_emit(buf, "%d\n", priv->event_max);
पूर्ण

अटल sमाप_प्रकार max_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक ret;
	दीर्घ temp;
	काष्ठा stts751_priv *priv = dev_get_drvdata(dev);

	अगर (kम_से_दीर्घ(buf, 10, &temp) < 0)
		वापस -EINVAL;

	mutex_lock(&priv->access_lock);
	/* HW works in range -64C to +127.937C */
	temp = clamp_val(temp, priv->event_min, 127937);
	ret = stts751_set_temp_reg16(priv, temp,
				     STTS751_REG_HLIM_H, STTS751_REG_HLIM_L);
	अगर (ret)
		जाओ निकास;

	dev_dbg(&priv->client->dev, "setting event max %ld", temp);
	priv->event_max = temp;
	ret = count;
निकास:
	mutex_unlock(&priv->access_lock);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार min_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			अक्षर *buf)
अणु
	काष्ठा stts751_priv *priv = dev_get_drvdata(dev);

	वापस sysfs_emit(buf, "%d\n", priv->event_min);
पूर्ण

अटल sमाप_प्रकार min_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक ret;
	दीर्घ temp;
	काष्ठा stts751_priv *priv = dev_get_drvdata(dev);

	अगर (kम_से_दीर्घ(buf, 10, &temp) < 0)
		वापस -EINVAL;

	mutex_lock(&priv->access_lock);
	/* HW works in range -64C to +127.937C */
	temp = clamp_val(temp, -64000, priv->event_max);
	ret = stts751_set_temp_reg16(priv, temp,
				     STTS751_REG_LLIM_H, STTS751_REG_LLIM_L);
	अगर (ret)
		जाओ निकास;

	dev_dbg(&priv->client->dev, "setting event min %ld", temp);
	priv->event_min = temp;
	ret = count;
निकास:
	mutex_unlock(&priv->access_lock);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार पूर्णांकerval_show(काष्ठा device *dev,
			     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा stts751_priv *priv = dev_get_drvdata(dev);

	वापस sysfs_emit(buf, "%d\n",
			  stts751_पूर्णांकervals[priv->पूर्णांकerval]);
पूर्ण

अटल sमाप_प्रकार पूर्णांकerval_store(काष्ठा device *dev,
			      काष्ठा device_attribute *attr, स्थिर अक्षर *buf,
			      माप_प्रकार count)
अणु
	अचिन्हित दीर्घ val;
	पूर्णांक idx;
	पूर्णांक ret = count;
	काष्ठा stts751_priv *priv = dev_get_drvdata(dev);

	अगर (kम_से_अदीर्घ(buf, 10, &val) < 0)
		वापस -EINVAL;

	idx = find_बंदst_descending(val, stts751_पूर्णांकervals,
				      ARRAY_SIZE(stts751_पूर्णांकervals));

	dev_dbg(&priv->client->dev, "setting interval. req:%lu, idx: %d, val: %d",
		val, idx, stts751_पूर्णांकervals[idx]);

	mutex_lock(&priv->access_lock);
	अगर (priv->पूर्णांकerval == idx)
		जाओ निकास;

	/*
	 * In early development stages I've become suspicious about the chip
	 * starting to misbehave अगर I ever set, even briefly, an invalid
	 * configuration. While I'm not sure this is really needed, be
	 * conservative and set rate/resolution in such an order that aव्योमs
	 * passing through an invalid configuration.
	 */

	/* speed up: lower the resolution, then modअगरy convrate */
	अगर (priv->पूर्णांकerval < idx) अणु
		dev_dbg(&priv->client->dev, "lower resolution, then modify convrate");
		priv->पूर्णांकerval = idx;
		ret = stts751_adjust_resolution(priv);
		अगर (ret)
			जाओ निकास;
	पूर्ण

	ret = i2c_smbus_ग_लिखो_byte_data(priv->client, STTS751_REG_RATE, idx);
	अगर (ret)
		जाओ निकास;
	/* slow करोwn: modअगरy convrate, then उठाओ resolution */
	अगर (priv->पूर्णांकerval != idx) अणु
		dev_dbg(&priv->client->dev, "modify convrate, then raise resolution");
		priv->पूर्णांकerval = idx;
		ret = stts751_adjust_resolution(priv);
		अगर (ret)
			जाओ निकास;
	पूर्ण
	ret = count;
निकास:
	mutex_unlock(&priv->access_lock);

	वापस ret;
पूर्ण

अटल पूर्णांक stts751_detect(काष्ठा i2c_client *new_client,
			  काष्ठा i2c_board_info *info)
अणु
	काष्ठा i2c_adapter *adapter = new_client->adapter;
	स्थिर अक्षर *name;
	पूर्णांक पंचांगp;

	अगर (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_BYTE_DATA))
		वापस -ENODEV;

	पंचांगp = i2c_smbus_पढ़ो_byte_data(new_client, STTS751_REG_MAN_ID);
	अगर (पंचांगp != ST_MAN_ID)
		वापस -ENODEV;

	/* lower temperaure रेजिस्टरs always have bits 0-3 set to zero */
	पंचांगp = i2c_smbus_पढ़ो_byte_data(new_client, STTS751_REG_TEMP_L);
	अगर (पंचांगp & 0xf)
		वापस -ENODEV;

	पंचांगp = i2c_smbus_पढ़ो_byte_data(new_client, STTS751_REG_HLIM_L);
	अगर (पंचांगp & 0xf)
		वापस -ENODEV;

	पंचांगp = i2c_smbus_पढ़ो_byte_data(new_client, STTS751_REG_LLIM_L);
	अगर (पंचांगp & 0xf)
		वापस -ENODEV;

	/* smbus समयout रेजिस्टर always have bits 0-7 set to zero */
	पंचांगp = i2c_smbus_पढ़ो_byte_data(new_client, STTS751_REG_SMBUS_TO);
	अगर (पंचांगp & 0x7f)
		वापस -ENODEV;

	पंचांगp = i2c_smbus_पढ़ो_byte_data(new_client, STTS751_REG_PROD_ID);

	चयन (पंचांगp) अणु
	हाल STTS751_0_PROD_ID:
		name = "STTS751-0";
		अवरोध;
	हाल STTS751_1_PROD_ID:
		name = "STTS751-1";
		अवरोध;
	शेष:
		वापस -ENODEV;
	पूर्ण
	dev_dbg(&new_client->dev, "Chip %s detected", name);

	strlcpy(info->type, stts751_id[0].name, I2C_NAME_SIZE);
	वापस 0;
पूर्ण

अटल पूर्णांक stts751_पढ़ो_chip_config(काष्ठा stts751_priv *priv)
अणु
	पूर्णांक ret;
	पूर्णांक पंचांगp;

	ret = i2c_smbus_पढ़ो_byte_data(priv->client, STTS751_REG_CONF);
	अगर (ret < 0)
		वापस ret;
	priv->config = ret;
	priv->res = (ret & STTS751_CONF_RES_MASK) >> STTS751_CONF_RES_SHIFT;

	ret = i2c_smbus_पढ़ो_byte_data(priv->client, STTS751_REG_RATE);
	अगर (ret < 0)
		वापस ret;
	अगर (ret >= ARRAY_SIZE(stts751_पूर्णांकervals)) अणु
		dev_err(priv->dev, "Unrecognized conversion rate 0x%x\n", ret);
		वापस -ENODEV;
	पूर्ण
	priv->पूर्णांकerval = ret;

	ret = stts751_पढ़ो_reg16(priv, &priv->event_max,
				 STTS751_REG_HLIM_H, STTS751_REG_HLIM_L);
	अगर (ret)
		वापस ret;

	ret = stts751_पढ़ो_reg16(priv, &priv->event_min,
				 STTS751_REG_LLIM_H, STTS751_REG_LLIM_L);
	अगर (ret)
		वापस ret;

	ret = stts751_पढ़ो_reg8(priv, &priv->therm, STTS751_REG_TLIM);
	अगर (ret)
		वापस ret;

	ret = stts751_पढ़ो_reg8(priv, &पंचांगp, STTS751_REG_HYST);
	अगर (ret)
		वापस ret;
	priv->hyst = priv->therm - पंचांगp;

	वापस 0;
पूर्ण

अटल SENSOR_DEVICE_ATTR_RO(temp1_input, input, 0);
अटल SENSOR_DEVICE_ATTR_RW(temp1_min, min, 0);
अटल SENSOR_DEVICE_ATTR_RW(temp1_max, max, 0);
अटल SENSOR_DEVICE_ATTR_RO(temp1_min_alarm, min_alarm, 0);
अटल SENSOR_DEVICE_ATTR_RO(temp1_max_alarm, max_alarm, 0);
अटल SENSOR_DEVICE_ATTR_RW(temp1_crit, therm, 0);
अटल SENSOR_DEVICE_ATTR_RW(temp1_crit_hyst, hyst, 0);
अटल SENSOR_DEVICE_ATTR_RO(temp1_crit_alarm, therm_trip, 0);
अटल SENSOR_DEVICE_ATTR_RW(update_पूर्णांकerval, पूर्णांकerval, 0);

अटल काष्ठा attribute *stts751_attrs[] = अणु
	&sensor_dev_attr_temp1_input.dev_attr.attr,
	&sensor_dev_attr_temp1_min.dev_attr.attr,
	&sensor_dev_attr_temp1_max.dev_attr.attr,
	&sensor_dev_attr_temp1_min_alarm.dev_attr.attr,
	&sensor_dev_attr_temp1_max_alarm.dev_attr.attr,
	&sensor_dev_attr_temp1_crit.dev_attr.attr,
	&sensor_dev_attr_temp1_crit_hyst.dev_attr.attr,
	&sensor_dev_attr_temp1_crit_alarm.dev_attr.attr,
	&sensor_dev_attr_update_पूर्णांकerval.dev_attr.attr,
	शून्य
पूर्ण;
ATTRIBUTE_GROUPS(stts751);

अटल पूर्णांक stts751_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा stts751_priv *priv;
	पूर्णांक ret;
	bool smbus_nto;
	पूर्णांक rev_id;

	priv = devm_kzalloc(&client->dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->client = client;
	priv->notअगरy_max = true;
	priv->notअगरy_min = true;
	i2c_set_clientdata(client, priv);
	mutex_init(&priv->access_lock);

	अगर (device_property_present(&client->dev,
				    "smbus-timeout-disable")) अणु
		smbus_nto = device_property_पढ़ो_bool(&client->dev,
						      "smbus-timeout-disable");

		ret = i2c_smbus_ग_लिखो_byte_data(client,	STTS751_REG_SMBUS_TO,
						smbus_nto ? 0 : 0x80);
		अगर (ret)
			वापस ret;
	पूर्ण

	rev_id = i2c_smbus_पढ़ो_byte_data(client, STTS751_REG_REV_ID);
	अगर (rev_id < 0)
		वापस -ENODEV;
	अगर (rev_id != 0x1) अणु
		dev_dbg(&client->dev, "Chip revision 0x%x is untested\n",
			rev_id);
	पूर्ण

	ret = stts751_पढ़ो_chip_config(priv);
	अगर (ret)
		वापस ret;

	priv->config &= ~(STTS751_CONF_STOP | STTS751_CONF_EVENT_DIS);
	ret = i2c_smbus_ग_लिखो_byte_data(client,	STTS751_REG_CONF, priv->config);
	अगर (ret)
		वापस ret;

	priv->dev = devm_hwmon_device_रेजिस्टर_with_groups(&client->dev,
							client->name, priv,
							stts751_groups);
	वापस PTR_ERR_OR_ZERO(priv->dev);
पूर्ण

MODULE_DEVICE_TABLE(i2c, stts751_id);

अटल काष्ठा i2c_driver stts751_driver = अणु
	.class		= I2C_CLASS_HWMON,
	.driver = अणु
		.name	= DEVNAME,
		.of_match_table = of_match_ptr(stts751_of_match),
	पूर्ण,
	.probe_new	= stts751_probe,
	.id_table	= stts751_id,
	.detect		= stts751_detect,
	.alert		= stts751_alert,
	.address_list	= normal_i2c,
पूर्ण;

module_i2c_driver(stts751_driver);

MODULE_AUTHOR("Andrea Merello <andrea.merello@gmail.com>");
MODULE_DESCRIPTION("STTS751 sensor driver");
MODULE_LICENSE("GPL");
