<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * smsc47b397.c - Part of lm_sensors, Linux kernel modules
 * क्रम hardware monitoring
 *
 * Supports the SMSC LPC47B397-NC Super-I/O chip.
 *
 * Author/Maपूर्णांकainer: Mark M. Hoffman <mhoffman@lightlink.com>
 * Copyright (C) 2004 Utilitek Systems, Inc.
 *
 * derived in part from smsc47m1.c:
 * Copyright (C) 2002 Mark D. Studebaker <mdsxyz123@yahoo.com>
 * Copyright (C) 2004 Jean Delvare <jdelvare@suse.de>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/ioport.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/hwmon-sysfs.h>
#समावेश <linux/err.h>
#समावेश <linux/init.h>
#समावेश <linux/mutex.h>
#समावेश <linux/acpi.h>
#समावेश <linux/पन.स>

अटल अचिन्हित लघु क्रमce_id;
module_param(क्रमce_id, uलघु, 0);
MODULE_PARM_DESC(क्रमce_id, "Override the detected device ID");

अटल काष्ठा platक्रमm_device *pdev;

#घोषणा DRVNAME "smsc47b397"

/* Super-I/0 रेजिस्टरs and commands */

#घोषणा	REG	0x2e	/* The रेजिस्टर to पढ़ो/ग_लिखो */
#घोषणा	VAL	0x2f	/* The value to पढ़ो/ग_लिखो */

अटल अंतरभूत व्योम superio_outb(पूर्णांक reg, पूर्णांक val)
अणु
	outb(reg, REG);
	outb(val, VAL);
पूर्ण

अटल अंतरभूत पूर्णांक superio_inb(पूर्णांक reg)
अणु
	outb(reg, REG);
	वापस inb(VAL);
पूर्ण

/* select superio logical device */
अटल अंतरभूत व्योम superio_select(पूर्णांक ld)
अणु
	superio_outb(0x07, ld);
पूर्ण

अटल अंतरभूत पूर्णांक superio_enter(व्योम)
अणु
	अगर (!request_muxed_region(REG, 2, DRVNAME))
		वापस -EBUSY;

	outb(0x55, REG);
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम superio_निकास(व्योम)
अणु
	outb(0xAA, REG);
	release_region(REG, 2);
पूर्ण

#घोषणा SUPERIO_REG_DEVID	0x20
#घोषणा SUPERIO_REG_DEVREV	0x21
#घोषणा SUPERIO_REG_BASE_MSB	0x60
#घोषणा SUPERIO_REG_BASE_LSB	0x61
#घोषणा SUPERIO_REG_LD8		0x08

#घोषणा SMSC_EXTENT		0x02

/* 0 <= nr <= 3 */
अटल u8 smsc47b397_reg_temp[] = अणु0x25, 0x26, 0x27, 0x80पूर्ण;
#घोषणा SMSC47B397_REG_TEMP(nr)	(smsc47b397_reg_temp[(nr)])

/* 0 <= nr <= 3 */
#घोषणा SMSC47B397_REG_FAN_LSB(nr) (0x28 + 2 * (nr))
#घोषणा SMSC47B397_REG_FAN_MSB(nr) (0x29 + 2 * (nr))

काष्ठा smsc47b397_data अणु
	अचिन्हित लघु addr;
	काष्ठा mutex lock;

	काष्ठा mutex update_lock;
	अचिन्हित दीर्घ last_updated; /* in jअगरfies */
	पूर्णांक valid;

	/* रेजिस्टर values */
	u16 fan[4];
	u8 temp[4];
पूर्ण;

अटल पूर्णांक smsc47b397_पढ़ो_value(काष्ठा smsc47b397_data *data, u8 reg)
अणु
	पूर्णांक res;

	mutex_lock(&data->lock);
	outb(reg, data->addr);
	res = inb_p(data->addr + 1);
	mutex_unlock(&data->lock);
	वापस res;
पूर्ण

अटल काष्ठा smsc47b397_data *smsc47b397_update_device(काष्ठा device *dev)
अणु
	काष्ठा smsc47b397_data *data = dev_get_drvdata(dev);
	पूर्णांक i;

	mutex_lock(&data->update_lock);

	अगर (समय_after(jअगरfies, data->last_updated + HZ) || !data->valid) अणु
		dev_dbg(dev, "starting device update...\n");

		/* 4 temperature inमाला_दो, 4 fan inमाला_दो */
		क्रम (i = 0; i < 4; i++) अणु
			data->temp[i] = smsc47b397_पढ़ो_value(data,
					SMSC47B397_REG_TEMP(i));

			/* must पढ़ो LSB first */
			data->fan[i]  = smsc47b397_पढ़ो_value(data,
					SMSC47B397_REG_FAN_LSB(i));
			data->fan[i] |= smsc47b397_पढ़ो_value(data,
					SMSC47B397_REG_FAN_MSB(i)) << 8;
		पूर्ण

		data->last_updated = jअगरfies;
		data->valid = 1;

		dev_dbg(dev, "... device update complete\n");
	पूर्ण

	mutex_unlock(&data->update_lock);

	वापस data;
पूर्ण

/*
 * TEMP: 0.001C/bit (-128C to +127C)
 * REG: 1C/bit, two's complement
 */
अटल पूर्णांक temp_from_reg(u8 reg)
अणु
	वापस (s8)reg * 1000;
पूर्ण

अटल sमाप_प्रकार temp_show(काष्ठा device *dev, काष्ठा device_attribute *devattr,
			 अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	काष्ठा smsc47b397_data *data = smsc47b397_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", temp_from_reg(data->temp[attr->index]));
पूर्ण

अटल SENSOR_DEVICE_ATTR_RO(temp1_input, temp, 0);
अटल SENSOR_DEVICE_ATTR_RO(temp2_input, temp, 1);
अटल SENSOR_DEVICE_ATTR_RO(temp3_input, temp, 2);
अटल SENSOR_DEVICE_ATTR_RO(temp4_input, temp, 3);

/*
 * FAN: 1 RPM/bit
 * REG: count of 90kHz pulses / revolution
 */
अटल पूर्णांक fan_from_reg(u16 reg)
अणु
	अगर (reg == 0 || reg == 0xffff)
		वापस 0;
	वापस 90000 * 60 / reg;
पूर्ण

अटल sमाप_प्रकार fan_show(काष्ठा device *dev, काष्ठा device_attribute *devattr,
			अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	काष्ठा smsc47b397_data *data = smsc47b397_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", fan_from_reg(data->fan[attr->index]));
पूर्ण
अटल SENSOR_DEVICE_ATTR_RO(fan1_input, fan, 0);
अटल SENSOR_DEVICE_ATTR_RO(fan2_input, fan, 1);
अटल SENSOR_DEVICE_ATTR_RO(fan3_input, fan, 2);
अटल SENSOR_DEVICE_ATTR_RO(fan4_input, fan, 3);

अटल काष्ठा attribute *smsc47b397_attrs[] = अणु
	&sensor_dev_attr_temp1_input.dev_attr.attr,
	&sensor_dev_attr_temp2_input.dev_attr.attr,
	&sensor_dev_attr_temp3_input.dev_attr.attr,
	&sensor_dev_attr_temp4_input.dev_attr.attr,
	&sensor_dev_attr_fan1_input.dev_attr.attr,
	&sensor_dev_attr_fan2_input.dev_attr.attr,
	&sensor_dev_attr_fan3_input.dev_attr.attr,
	&sensor_dev_attr_fan4_input.dev_attr.attr,

	शून्य
पूर्ण;

ATTRIBUTE_GROUPS(smsc47b397);

अटल पूर्णांक smsc47b397_probe(काष्ठा platक्रमm_device *pdev);

अटल काष्ठा platक्रमm_driver smsc47b397_driver = अणु
	.driver = अणु
		.name	= DRVNAME,
	पूर्ण,
	.probe		= smsc47b397_probe,
पूर्ण;

अटल पूर्णांक smsc47b397_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा smsc47b397_data *data;
	काष्ठा device *hwmon_dev;
	काष्ठा resource *res;

	res = platक्रमm_get_resource(pdev, IORESOURCE_IO, 0);
	अगर (!devm_request_region(dev, res->start, SMSC_EXTENT,
				 smsc47b397_driver.driver.name)) अणु
		dev_err(dev, "Region 0x%lx-0x%lx already in use!\n",
			(अचिन्हित दीर्घ)res->start,
			(अचिन्हित दीर्घ)res->start + SMSC_EXTENT - 1);
		वापस -EBUSY;
	पूर्ण

	data = devm_kzalloc(dev, माप(काष्ठा smsc47b397_data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	data->addr = res->start;
	mutex_init(&data->lock);
	mutex_init(&data->update_lock);

	hwmon_dev = devm_hwmon_device_रेजिस्टर_with_groups(dev, "smsc47b397",
							   data,
							   smsc47b397_groups);
	वापस PTR_ERR_OR_ZERO(hwmon_dev);
पूर्ण

अटल पूर्णांक __init smsc47b397_device_add(अचिन्हित लघु address)
अणु
	काष्ठा resource res = अणु
		.start	= address,
		.end	= address + SMSC_EXTENT - 1,
		.name	= DRVNAME,
		.flags	= IORESOURCE_IO,
	पूर्ण;
	पूर्णांक err;

	err = acpi_check_resource_conflict(&res);
	अगर (err)
		जाओ निकास;

	pdev = platक्रमm_device_alloc(DRVNAME, address);
	अगर (!pdev) अणु
		err = -ENOMEM;
		pr_err("Device allocation failed\n");
		जाओ निकास;
	पूर्ण

	err = platक्रमm_device_add_resources(pdev, &res, 1);
	अगर (err) अणु
		pr_err("Device resource addition failed (%d)\n", err);
		जाओ निकास_device_put;
	पूर्ण

	err = platक्रमm_device_add(pdev);
	अगर (err) अणु
		pr_err("Device addition failed (%d)\n", err);
		जाओ निकास_device_put;
	पूर्ण

	वापस 0;

निकास_device_put:
	platक्रमm_device_put(pdev);
निकास:
	वापस err;
पूर्ण

अटल पूर्णांक __init smsc47b397_find(व्योम)
अणु
	u8 id, rev;
	अक्षर *name;
	अचिन्हित लघु addr;
	पूर्णांक err;

	err = superio_enter();
	अगर (err)
		वापस err;

	id = क्रमce_id ? क्रमce_id : superio_inb(SUPERIO_REG_DEVID);

	चयन (id) अणु
	हाल 0x81:
		name = "SCH5307-NS";
		अवरोध;
	हाल 0x6f:
		name = "LPC47B397-NC";
		अवरोध;
	हाल 0x85:
	हाल 0x8c:
		name = "SCH5317";
		अवरोध;
	शेष:
		superio_निकास();
		वापस -ENODEV;
	पूर्ण

	rev = superio_inb(SUPERIO_REG_DEVREV);

	superio_select(SUPERIO_REG_LD8);
	addr = (superio_inb(SUPERIO_REG_BASE_MSB) << 8)
		 |  superio_inb(SUPERIO_REG_BASE_LSB);

	pr_info("found SMSC %s (base address 0x%04x, revision %u)\n",
		name, addr, rev);

	superio_निकास();
	वापस addr;
पूर्ण

अटल पूर्णांक __init smsc47b397_init(व्योम)
अणु
	अचिन्हित लघु address;
	पूर्णांक ret;

	ret = smsc47b397_find();
	अगर (ret < 0)
		वापस ret;
	address = ret;

	ret = platक्रमm_driver_रेजिस्टर(&smsc47b397_driver);
	अगर (ret)
		जाओ निकास;

	/* Sets global pdev as a side effect */
	ret = smsc47b397_device_add(address);
	अगर (ret)
		जाओ निकास_driver;

	वापस 0;

निकास_driver:
	platक्रमm_driver_unरेजिस्टर(&smsc47b397_driver);
निकास:
	वापस ret;
पूर्ण

अटल व्योम __निकास smsc47b397_निकास(व्योम)
अणु
	platक्रमm_device_unरेजिस्टर(pdev);
	platक्रमm_driver_unरेजिस्टर(&smsc47b397_driver);
पूर्ण

MODULE_AUTHOR("Mark M. Hoffman <mhoffman@lightlink.com>");
MODULE_DESCRIPTION("SMSC LPC47B397 driver");
MODULE_LICENSE("GPL");

module_init(smsc47b397_init);
module_निकास(smsc47b397_निकास);
