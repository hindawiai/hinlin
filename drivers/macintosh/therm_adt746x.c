<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Device driver क्रम the i2c thermostat found on the iBook G4, Albook G4
 *
 * Copyright (C) 2003, 2004 Colin Leroy, Rयंत्रus Rohde, Benjamin Herrenschmidt
 *
 * Documentation from 115254175ADT7467_pra.pdf and 3686221171167ADT7460_b.pdf
 * https://www.onsemi.com/PowerSolutions/product.करो?id=ADT7467
 * https://www.onsemi.com/PowerSolutions/product.करो?id=ADT7460
 *
 */

#समावेश <linux/types.h>
#समावेश <linux/module.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/delay.h>
#समावेश <linux/sched.h>
#समावेश <linux/i2c.h>
#समावेश <linux/slab.h>
#समावेश <linux/init.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/रुको.h>
#समावेश <linux/suspend.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/मुक्तzer.h>
#समावेश <linux/of_platक्रमm.h>

#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/sections.h>

#अघोषित DEBUG

#घोषणा CONFIG_REG   0x40
#घोषणा MANUAL_MASK  0xe0
#घोषणा AUTO_MASK    0x20
#घोषणा INVERT_MASK  0x10

अटल u8 TEMP_REG[3]    = अणु0x26, 0x25, 0x27पूर्ण; /* local, sensor1, sensor2 */
अटल u8 LIMIT_REG[3]   = अणु0x6b, 0x6a, 0x6cपूर्ण; /* local, sensor1, sensor2 */
अटल u8 MANUAL_MODE[2] = अणु0x5c, 0x5dपूर्ण;       
अटल u8 REM_CONTROL[2] = अणु0x00, 0x40पूर्ण;
अटल u8 FAN_SPEED[2]   = अणु0x28, 0x2aपूर्ण;
अटल u8 FAN_SPD_SET[2] = अणु0x30, 0x31पूर्ण;

अटल u8 शेष_limits_local[3] = अणु70, 50, 70पूर्ण;    /* local, sensor1, sensor2 */
अटल u8 शेष_limits_chip[3] = अणु80, 65, 80पूर्ण;    /* local, sensor1, sensor2 */
अटल स्थिर अक्षर *sensor_location[3] = अणु "?", "?", "?" पूर्ण;

अटल पूर्णांक limit_adjust;
अटल पूर्णांक fan_speed = -1;
अटल bool verbose;

MODULE_AUTHOR("Colin Leroy <colin@colino.net>");
MODULE_DESCRIPTION("Driver for ADT746x thermostat in iBook G4 and "
		   "Powerbook G4 Alu");
MODULE_LICENSE("GPL");

module_param(limit_adjust, पूर्णांक, 0644);
MODULE_PARM_DESC(limit_adjust,"Adjust maximum temperatures (50 sensor1, 70 sensor2) "
		 "by N degrees.");

module_param(fan_speed, पूर्णांक, 0644);
MODULE_PARM_DESC(fan_speed,"Specify starting fan speed (0-255) "
		 "(default 64)");

module_param(verbose, bool, 0);
MODULE_PARM_DESC(verbose,"Verbose log operations "
		 "(default 0)");

काष्ठा thermostat अणु
	काष्ठा i2c_client	*clt;
	u8			temps[3];
	u8			cached_temp[3];
	u8			initial_limits[3];
	u8			limits[3];
	पूर्णांक			last_speed[2];
	पूर्णांक			last_var[2];
	पूर्णांक			pwm_inv[2];
	काष्ठा task_काष्ठा	*thपढ़ो;
	काष्ठा platक्रमm_device	*pdev;
	क्रमागत अणु
		ADT7460,
		ADT7467
	पूर्ण			type;
पूर्ण;

अटल व्योम ग_लिखो_both_fan_speed(काष्ठा thermostat *th, पूर्णांक speed);
अटल व्योम ग_लिखो_fan_speed(काष्ठा thermostat *th, पूर्णांक speed, पूर्णांक fan);

अटल पूर्णांक
ग_लिखो_reg(काष्ठा thermostat* th, पूर्णांक reg, u8 data)
अणु
	u8 पंचांगp[2];
	पूर्णांक rc;
	
	पंचांगp[0] = reg;
	पंचांगp[1] = data;
	rc = i2c_master_send(th->clt, (स्थिर अक्षर *)पंचांगp, 2);
	अगर (rc < 0)
		वापस rc;
	अगर (rc != 2)
		वापस -ENODEV;
	वापस 0;
पूर्ण

अटल पूर्णांक
पढ़ो_reg(काष्ठा thermostat* th, पूर्णांक reg)
अणु
	u8 reg_addr, data;
	पूर्णांक rc;

	reg_addr = (u8)reg;
	rc = i2c_master_send(th->clt, &reg_addr, 1);
	अगर (rc < 0)
		वापस rc;
	अगर (rc != 1)
		वापस -ENODEV;
	rc = i2c_master_recv(th->clt, (अक्षर *)&data, 1);
	अगर (rc < 0)
		वापस rc;
	वापस data;
पूर्ण

अटल पूर्णांक पढ़ो_fan_speed(काष्ठा thermostat *th, u8 addr)
अणु
	u8 पंचांगp[2];
	u16 res;
	
	/* should start with low byte */
	पंचांगp[1] = पढ़ो_reg(th, addr);
	पंचांगp[0] = पढ़ो_reg(th, addr + 1);
	
	res = पंचांगp[1] + (पंचांगp[0] << 8);
	/* "a value of 0xffff means that the fan has stopped" */
	वापस (res == 0xffff ? 0 : (90000*60)/res);
पूर्ण

अटल व्योम ग_लिखो_both_fan_speed(काष्ठा thermostat *th, पूर्णांक speed)
अणु
	ग_लिखो_fan_speed(th, speed, 0);
	अगर (th->type == ADT7460)
		ग_लिखो_fan_speed(th, speed, 1);
पूर्ण

अटल व्योम ग_लिखो_fan_speed(काष्ठा thermostat *th, पूर्णांक speed, पूर्णांक fan)
अणु
	u8 manual;
	
	अगर (speed > 0xff) 
		speed = 0xff;
	अन्यथा अगर (speed < -1) 
		speed = 0;
	
	अगर (th->type == ADT7467 && fan == 1)
		वापस;
	
	अगर (th->last_speed[fan] != speed) अणु
		अगर (verbose) अणु
			अगर (speed == -1)
				prपूर्णांकk(KERN_DEBUG "adt746x: Setting speed to automatic "
					"for %s fan.\n", sensor_location[fan+1]);
			अन्यथा
				prपूर्णांकk(KERN_DEBUG "adt746x: Setting speed to %d "
					"for %s fan.\n", speed, sensor_location[fan+1]);
		पूर्ण
	पूर्ण अन्यथा
		वापस;
	
	अगर (speed >= 0) अणु
		manual = पढ़ो_reg(th, MANUAL_MODE[fan]);
		manual &= ~INVERT_MASK;
		ग_लिखो_reg(th, MANUAL_MODE[fan],
			manual | MANUAL_MASK | th->pwm_inv[fan]);
		ग_लिखो_reg(th, FAN_SPD_SET[fan], speed);
	पूर्ण अन्यथा अणु
		/* back to स्वतःmatic */
		अगर(th->type == ADT7460) अणु
			manual = पढ़ो_reg(th,
				MANUAL_MODE[fan]) & (~MANUAL_MASK);
			manual &= ~INVERT_MASK;
			manual |= th->pwm_inv[fan];
			ग_लिखो_reg(th,
				MANUAL_MODE[fan], manual|REM_CONTROL[fan]);
		पूर्ण अन्यथा अणु
			manual = पढ़ो_reg(th, MANUAL_MODE[fan]);
			manual &= ~INVERT_MASK;
			manual |= th->pwm_inv[fan];
			ग_लिखो_reg(th, MANUAL_MODE[fan], manual&(~AUTO_MASK));
		पूर्ण
	पूर्ण
	
	th->last_speed[fan] = speed;			
पूर्ण

अटल व्योम पढ़ो_sensors(काष्ठा thermostat *th)
अणु
	पूर्णांक i = 0;

	क्रम (i = 0; i < 3; i++)
		th->temps[i]  = पढ़ो_reg(th, TEMP_REG[i]);
पूर्ण

#अगर_घोषित DEBUG
अटल व्योम display_stats(काष्ठा thermostat *th)
अणु
	अगर (th->temps[0] != th->cached_temp[0]
	||  th->temps[1] != th->cached_temp[1]
	||  th->temps[2] != th->cached_temp[2]) अणु
		prपूर्णांकk(KERN_INFO "adt746x: Temperature infos:"
				 " thermostats: %d,%d,%d;"
				 " limits: %d,%d,%d;"
				 " fan speed: %d RPM\n",
				 th->temps[0], th->temps[1], th->temps[2],
				 th->limits[0],  th->limits[1],  th->limits[2],
				 पढ़ो_fan_speed(th, FAN_SPEED[0]));
	पूर्ण
	th->cached_temp[0] = th->temps[0];
	th->cached_temp[1] = th->temps[1];
	th->cached_temp[2] = th->temps[2];
पूर्ण
#पूर्ण_अगर

अटल व्योम update_fans_speed (काष्ठा thermostat *th)
अणु
	पूर्णांक lastvar = 0; /* last variation, क्रम iBook */
	पूर्णांक i = 0;

	/* we करोn't care about local sensor, so we start at sensor 1 */
	क्रम (i = 1; i < 3; i++) अणु
		bool started = false;
		पूर्णांक fan_number = (th->type == ADT7460 && i == 2);
		पूर्णांक var = th->temps[i] - th->limits[i];

		अगर (var > -1) अणु
			पूर्णांक step = (255 - fan_speed) / 7;
			पूर्णांक new_speed = 0;

			/* hysteresis : change fan speed only अगर variation is
			 * more than two degrees */
			अगर (असल(var - th->last_var[fan_number]) < 2)
				जारी;

			started = true;
			new_speed = fan_speed + ((var-1)*step);

			अगर (new_speed < fan_speed)
				new_speed = fan_speed;
			अगर (new_speed > 255)
				new_speed = 255;

			अगर (verbose)
				prपूर्णांकk(KERN_DEBUG "adt746x: Setting fans speed to %d "
						 "(limit exceeded by %d on %s)\n",
						new_speed, var,
						sensor_location[fan_number+1]);
			ग_लिखो_both_fan_speed(th, new_speed);
			th->last_var[fan_number] = var;
		पूर्ण अन्यथा अगर (var < -2) अणु
			/* करोn't stop fan अगर sensor2 is cold and sensor1 is not
			 * so cold (lastvar >= -1) */
			अगर (i == 2 && lastvar < -1) अणु
				अगर (th->last_speed[fan_number] != 0)
					अगर (verbose)
						prपूर्णांकk(KERN_DEBUG "adt746x: Stopping "
							"fans.\n");
				ग_लिखो_both_fan_speed(th, 0);
			पूर्ण
		पूर्ण

		lastvar = var;

		अगर (started)
			वापस; /* we करोn't want to re-stop the fan
				* अगर sensor1 is heating and sensor2 is not */
	पूर्ण
पूर्ण

अटल पूर्णांक monitor_task(व्योम *arg)
अणु
	काष्ठा thermostat* th = arg;

	set_मुक्तzable();
	जबतक(!kthपढ़ो_should_stop()) अणु
		try_to_मुक्तze();
		msleep_पूर्णांकerruptible(2000);

#अगर_अघोषित DEBUG
		अगर (fan_speed != -1)
			पढ़ो_sensors(th);
#अन्यथा
		पढ़ो_sensors(th);
#पूर्ण_अगर		

		अगर (fan_speed != -1)
			update_fans_speed(th);

#अगर_घोषित DEBUG
		display_stats(th);
#पूर्ण_अगर

	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम set_limit(काष्ठा thermostat *th, पूर्णांक i)
अणु
	/* Set sensor1 limit higher to aव्योम घातerकरोwns */
	th->limits[i] = शेष_limits_chip[i] + limit_adjust;
	ग_लिखो_reg(th, LIMIT_REG[i], th->limits[i]);
		
	/* set our limits to normal */
	th->limits[i] = शेष_limits_local[i] + limit_adjust;
पूर्ण

#घोषणा BUILD_SHOW_FUNC_INT(name, data)				\
अटल sमाप_प्रकार show_##name(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)	\
अणु								\
	काष्ठा thermostat *th = dev_get_drvdata(dev);		\
	वापस प्र_लिखो(buf, "%d\n", data);			\
पूर्ण

#घोषणा BUILD_SHOW_FUNC_INT_LITE(name, data)				\
अटल sमाप_प्रकार show_##name(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)	\
अणु								\
	वापस प्र_लिखो(buf, "%d\n", data);			\
पूर्ण

#घोषणा BUILD_SHOW_FUNC_STR(name, data)				\
अटल sमाप_प्रकार show_##name(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)       \
अणु								\
	वापस प्र_लिखो(buf, "%s\n", data);			\
पूर्ण

#घोषणा BUILD_SHOW_FUNC_FAN(name, data)				\
अटल sमाप_प्रकार show_##name(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)       \
अणु								\
	काष्ठा thermostat *th = dev_get_drvdata(dev);		\
	वापस प्र_लिखो(buf, "%d (%d rpm)\n", 			\
		th->last_speed[data],				\
		पढ़ो_fan_speed(th, FAN_SPEED[data])		\
		);						\
पूर्ण

#घोषणा BUILD_STORE_FUNC_DEG(name, data)			\
अटल sमाप_प्रकार store_##name(काष्ठा device *dev, काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार n) \
अणु								\
	काष्ठा thermostat *th = dev_get_drvdata(dev);		\
	पूर्णांक val;						\
	पूर्णांक i;							\
	val = simple_म_से_दीर्घ(buf, शून्य, 10);			\
	prपूर्णांकk(KERN_INFO "Adjusting limits by %d degrees\n", val);	\
	limit_adjust = val;					\
	क्रम (i=0; i < 3; i++)					\
		set_limit(th, i);				\
	वापस n;						\
पूर्ण

#घोषणा BUILD_STORE_FUNC_INT(name, data)			\
अटल sमाप_प्रकार store_##name(काष्ठा device *dev, काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार n) \
अणु								\
	पूर्णांक val;						\
	val = simple_म_से_दीर्घ(buf, शून्य, 10);			\
	अगर (val < 0 || val > 255)				\
		वापस -EINVAL;					\
	prपूर्णांकk(KERN_INFO "Setting specified fan speed to %d\n", val);	\
	data = val;						\
	वापस n;						\
पूर्ण

BUILD_SHOW_FUNC_INT(sensor1_temperature,	 (पढ़ो_reg(th, TEMP_REG[1])))
BUILD_SHOW_FUNC_INT(sensor2_temperature,	 (पढ़ो_reg(th, TEMP_REG[2])))
BUILD_SHOW_FUNC_INT(sensor1_limit,		 th->limits[1])
BUILD_SHOW_FUNC_INT(sensor2_limit,		 th->limits[2])
BUILD_SHOW_FUNC_STR(sensor1_location,		 sensor_location[1])
BUILD_SHOW_FUNC_STR(sensor2_location,		 sensor_location[2])

BUILD_SHOW_FUNC_INT_LITE(specअगरied_fan_speed, fan_speed)
BUILD_STORE_FUNC_INT(specअगरied_fan_speed,fan_speed)

BUILD_SHOW_FUNC_FAN(sensor1_fan_speed,	 0)
BUILD_SHOW_FUNC_FAN(sensor2_fan_speed,	 1)

BUILD_SHOW_FUNC_INT_LITE(limit_adjust,	 limit_adjust)
BUILD_STORE_FUNC_DEG(limit_adjust,	 th)
		
अटल DEVICE_ATTR(sensor1_temperature,	S_IRUGO,
		   show_sensor1_temperature,शून्य);
अटल DEVICE_ATTR(sensor2_temperature,	S_IRUGO,
		   show_sensor2_temperature,शून्य);
अटल DEVICE_ATTR(sensor1_limit, S_IRUGO,
		   show_sensor1_limit,	शून्य);
अटल DEVICE_ATTR(sensor2_limit, S_IRUGO,
		   show_sensor2_limit,	शून्य);
अटल DEVICE_ATTR(sensor1_location, S_IRUGO,
		   show_sensor1_location, शून्य);
अटल DEVICE_ATTR(sensor2_location, S_IRUGO,
		   show_sensor2_location, शून्य);

अटल DEVICE_ATTR(specअगरied_fan_speed,	S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH,
		   show_specअगरied_fan_speed,store_specअगरied_fan_speed);

अटल DEVICE_ATTR(sensor1_fan_speed,	S_IRUGO,
		   show_sensor1_fan_speed,	शून्य);
अटल DEVICE_ATTR(sensor2_fan_speed,	S_IRUGO,
		   show_sensor2_fan_speed,	शून्य);

अटल DEVICE_ATTR(limit_adjust,	S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH,
		   show_limit_adjust,	store_limit_adjust);

अटल व्योम thermostat_create_files(काष्ठा thermostat *th)
अणु
	काष्ठा device_node *np = th->clt->dev.of_node;
	काष्ठा device *dev;
	पूर्णांक err;

	/* To मुख्यtain ABI compatibility with userspace, create
	 * the old style platक्रमm driver and attach the attributes
	 * to it here
	 */
	th->pdev = of_platक्रमm_device_create(np, "temperatures", शून्य);
	अगर (!th->pdev)
		वापस;
	dev = &th->pdev->dev;
	dev_set_drvdata(dev, th);
	err = device_create_file(dev, &dev_attr_sensor1_temperature);
	err |= device_create_file(dev, &dev_attr_sensor2_temperature);
	err |= device_create_file(dev, &dev_attr_sensor1_limit);
	err |= device_create_file(dev, &dev_attr_sensor2_limit);
	err |= device_create_file(dev, &dev_attr_sensor1_location);
	err |= device_create_file(dev, &dev_attr_sensor2_location);
	err |= device_create_file(dev, &dev_attr_limit_adjust);
	err |= device_create_file(dev, &dev_attr_specअगरied_fan_speed);
	err |= device_create_file(dev, &dev_attr_sensor1_fan_speed);
	अगर(th->type == ADT7460)
		err |= device_create_file(dev, &dev_attr_sensor2_fan_speed);
	अगर (err)
		prपूर्णांकk(KERN_WARNING
			"Failed to create temperature attribute file(s).\n");
पूर्ण

अटल व्योम thermostat_हटाओ_files(काष्ठा thermostat *th)
अणु
	काष्ठा device *dev;

	अगर (!th->pdev)
		वापस;
	dev = &th->pdev->dev;
	device_हटाओ_file(dev, &dev_attr_sensor1_temperature);
	device_हटाओ_file(dev, &dev_attr_sensor2_temperature);
	device_हटाओ_file(dev, &dev_attr_sensor1_limit);
	device_हटाओ_file(dev, &dev_attr_sensor2_limit);
	device_हटाओ_file(dev, &dev_attr_sensor1_location);
	device_हटाओ_file(dev, &dev_attr_sensor2_location);
	device_हटाओ_file(dev, &dev_attr_limit_adjust);
	device_हटाओ_file(dev, &dev_attr_specअगरied_fan_speed);
	device_हटाओ_file(dev, &dev_attr_sensor1_fan_speed);	
	अगर (th->type == ADT7460)
		device_हटाओ_file(dev, &dev_attr_sensor2_fan_speed);
	of_device_unरेजिस्टर(th->pdev);

पूर्ण

अटल पूर्णांक probe_thermostat(काष्ठा i2c_client *client,
			    स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा device_node *np = client->dev.of_node;
	काष्ठा thermostat* th;
	स्थिर __be32 *prop;
	पूर्णांक i, rc, vers, offset = 0;

	अगर (!np)
		वापस -ENXIO;
	prop = of_get_property(np, "hwsensor-params-version", शून्य);
	अगर (!prop)
		वापस -ENXIO;
	vers = be32_to_cpup(prop);
	prपूर्णांकk(KERN_INFO "adt746x: version %d (%ssupported)\n",
	       vers, vers == 1 ? "" : "un");
	अगर (vers != 1)
		वापस -ENXIO;

	अगर (of_get_property(np, "hwsensor-location", शून्य)) अणु
		क्रम (i = 0; i < 3; i++) अणु
			sensor_location[i] = of_get_property(np,
					"hwsensor-location", शून्य) + offset;

			अगर (sensor_location[i] == शून्य)
				sensor_location[i] = "";

			prपूर्णांकk(KERN_INFO "sensor %d: %s\n", i, sensor_location[i]);
			offset += म_माप(sensor_location[i]) + 1;
		पूर्ण
	पूर्ण

	th = kzalloc(माप(काष्ठा thermostat), GFP_KERNEL);
	अगर (!th)
		वापस -ENOMEM;

	i2c_set_clientdata(client, th);
	th->clt = client;
	th->type = id->driver_data;

	rc = पढ़ो_reg(th, CONFIG_REG);
	अगर (rc < 0) अणु
		dev_err(&client->dev, "Thermostat failed to read config!\n");
		kमुक्त(th);
		वापस -ENODEV;
	पूर्ण

	/* क्रमce manual control to start the fan quieter */
	अगर (fan_speed == -1)
		fan_speed = 64;
	
	अगर (th->type == ADT7460) अणु
		prपूर्णांकk(KERN_INFO "adt746x: ADT7460 initializing\n");
		/* The 7460 needs to be started explicitly */
		ग_लिखो_reg(th, CONFIG_REG, 1);
	पूर्ण अन्यथा
		prपूर्णांकk(KERN_INFO "adt746x: ADT7467 initializing\n");

	क्रम (i = 0; i < 3; i++) अणु
		th->initial_limits[i] = पढ़ो_reg(th, LIMIT_REG[i]);
		set_limit(th, i);
	पूर्ण

	prपूर्णांकk(KERN_INFO "adt746x: Lowering max temperatures from %d, %d, %d"
			 " to %d, %d, %d\n",
			 th->initial_limits[0], th->initial_limits[1],
			 th->initial_limits[2], th->limits[0], th->limits[1],
			 th->limits[2]);

	/* record invert bit status because fw can corrupt it after suspend */
	th->pwm_inv[0] = पढ़ो_reg(th, MANUAL_MODE[0]) & INVERT_MASK;
	th->pwm_inv[1] = पढ़ो_reg(th, MANUAL_MODE[1]) & INVERT_MASK;

	/* be sure to really ग_लिखो fan speed the first समय */
	th->last_speed[0] = -2;
	th->last_speed[1] = -2;
	th->last_var[0] = -80;
	th->last_var[1] = -80;

	अगर (fan_speed != -1) अणु
		/* manual mode, stop fans */
		ग_लिखो_both_fan_speed(th, 0);
	पूर्ण अन्यथा अणु
		/* स्वतःmatic mode */
		ग_लिखो_both_fan_speed(th, -1);
	पूर्ण
	
	th->thपढ़ो = kthपढ़ो_run(monitor_task, th, "kfand");
	अगर (th->thपढ़ो == ERR_PTR(-ENOMEM)) अणु
		prपूर्णांकk(KERN_INFO "adt746x: Kthread creation failed\n");
		th->thपढ़ो = शून्य;
		वापस -ENOMEM;
	पूर्ण

	thermostat_create_files(th);

	वापस 0;
पूर्ण

अटल पूर्णांक हटाओ_thermostat(काष्ठा i2c_client *client)
अणु
	काष्ठा thermostat *th = i2c_get_clientdata(client);
	पूर्णांक i;
	
	thermostat_हटाओ_files(th);

	अगर (th->thपढ़ो != शून्य)
		kthपढ़ो_stop(th->thपढ़ो);

	prपूर्णांकk(KERN_INFO "adt746x: Putting max temperatures back from "
			 "%d, %d, %d to %d, %d, %d\n",
		th->limits[0], th->limits[1], th->limits[2],
		th->initial_limits[0], th->initial_limits[1],
		th->initial_limits[2]);

	क्रम (i = 0; i < 3; i++)
		ग_लिखो_reg(th, LIMIT_REG[i], th->initial_limits[i]);

	ग_लिखो_both_fan_speed(th, -1);

	kमुक्त(th);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id therm_adt746x_id[] = अणु
	अणु "MAC,adt7460", ADT7460 पूर्ण,
	अणु "MAC,adt7467", ADT7467 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, therm_adt746x_id);

अटल काष्ठा i2c_driver thermostat_driver = अणु
	.driver = अणु
		.name	= "therm_adt746x",
	पूर्ण,
	.probe = probe_thermostat,
	.हटाओ = हटाओ_thermostat,
	.id_table = therm_adt746x_id,
पूर्ण;

अटल पूर्णांक __init thermostat_init(व्योम)
अणु
#अगर_अघोषित CONFIG_I2C_POWERMAC
	request_module("i2c-powermac");
#पूर्ण_अगर

	वापस i2c_add_driver(&thermostat_driver);
पूर्ण

अटल व्योम __निकास thermostat_निकास(व्योम)
अणु
	i2c_del_driver(&thermostat_driver);
पूर्ण

module_init(thermostat_init);
module_निकास(thermostat_निकास);
