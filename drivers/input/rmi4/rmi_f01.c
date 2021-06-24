<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2011-2016 Synaptics Incorporated
 * Copyright (c) 2011 Unixphere
 */

#समावेश <linux/kernel.h>
#समावेश <linux/rmi.h>
#समावेश <linux/slab.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/of.h>
#समावेश <यंत्र/unaligned.h>
#समावेश "rmi_driver.h"

#घोषणा RMI_PRODUCT_ID_LENGTH    10
#घोषणा RMI_PRODUCT_INFO_LENGTH   2

#घोषणा RMI_DATE_CODE_LENGTH      3

#घोषणा PRODUCT_ID_OFFSET 0x10
#घोषणा PRODUCT_INFO_OFFSET 0x1E


/* Force a firmware reset of the sensor */
#घोषणा RMI_F01_CMD_DEVICE_RESET	1

/* Various F01_RMI_QueryX bits */

#घोषणा RMI_F01_QRY1_CUSTOM_MAP		BIT(0)
#घोषणा RMI_F01_QRY1_NON_COMPLIANT	BIT(1)
#घोषणा RMI_F01_QRY1_HAS_LTS		BIT(2)
#घोषणा RMI_F01_QRY1_HAS_SENSOR_ID	BIT(3)
#घोषणा RMI_F01_QRY1_HAS_CHARGER_INP	BIT(4)
#घोषणा RMI_F01_QRY1_HAS_ADJ_DOZE	BIT(5)
#घोषणा RMI_F01_QRY1_HAS_ADJ_DOZE_HOFF	BIT(6)
#घोषणा RMI_F01_QRY1_HAS_QUERY42	BIT(7)

#घोषणा RMI_F01_QRY5_YEAR_MASK		0x1f
#घोषणा RMI_F01_QRY6_MONTH_MASK		0x0f
#घोषणा RMI_F01_QRY7_DAY_MASK		0x1f

#घोषणा RMI_F01_QRY2_PRODINFO_MASK	0x7f

#घोषणा RMI_F01_BASIC_QUERY_LEN		21 /* From Query 00 through 20 */

काष्ठा f01_basic_properties अणु
	u8 manufacturer_id;
	bool has_lts;
	bool has_adjustable_करोze;
	bool has_adjustable_करोze_holकरोff;
	अक्षर करोm[11]; /* YYYY/MM/DD + '\0' */
	u8 product_id[RMI_PRODUCT_ID_LENGTH + 1];
	u16 productinfo;
	u32 firmware_id;
	u32 package_id;
पूर्ण;

/* F01 device status bits */

/* Most recent device status event */
#घोषणा RMI_F01_STATUS_CODE(status)		((status) & 0x0f)
/* The device has lost its configuration क्रम some reason. */
#घोषणा RMI_F01_STATUS_UNCONFIGURED(status)	(!!((status) & 0x80))
/* The device is in bootloader mode */
#घोषणा RMI_F01_STATUS_BOOTLOADER(status)	((status) & 0x40)

/* Control रेजिस्टर bits */

/*
 * Sleep mode controls घातer management on the device and affects all
 * functions of the device.
 */
#घोषणा RMI_F01_CTRL0_SLEEP_MODE_MASK	0x03

#घोषणा RMI_SLEEP_MODE_NORMAL		0x00
#घोषणा RMI_SLEEP_MODE_SENSOR_SLEEP	0x01
#घोषणा RMI_SLEEP_MODE_RESERVED0	0x02
#घोषणा RMI_SLEEP_MODE_RESERVED1	0x03

/*
 * This bit disables whatever sleep mode may be selected by the sleep_mode
 * field and क्रमces the device to run at full घातer without sleeping.
 */
#घोषणा RMI_F01_CTRL0_NOSLEEP_BIT	BIT(2)

/*
 * When this bit is set, the touch controller employs a noise-filtering
 * algorithm deचिन्हित क्रम use with a connected battery अक्षरger.
 */
#घोषणा RMI_F01_CTRL0_CHARGER_BIT	BIT(5)

/*
 * Sets the report rate क्रम the device. The effect of this setting is
 * highly product dependent. Check the spec sheet क्रम your particular
 * touch sensor.
 */
#घोषणा RMI_F01_CTRL0_REPORTRATE_BIT	BIT(6)

/*
 * Written by the host as an indicator that the device has been
 * successfully configured.
 */
#घोषणा RMI_F01_CTRL0_CONFIGURED_BIT	BIT(7)

/**
 * काष्ठा f01_device_control - controls basic sensor functions
 *
 * @ctrl0: see the bit definitions above.
 * @करोze_पूर्णांकerval: controls the पूर्णांकerval between checks क्रम finger presence
 *	when the touch sensor is in करोze mode, in units of 10ms.
 * @wakeup_threshold: controls the capacitance threshold at which the touch
 *	sensor will decide to wake up from that low घातer state.
 * @करोze_holकरोff: controls how दीर्घ the touch sensor रुकोs after the last
 *	finger lअगरts beक्रमe entering the करोze state, in units of 100ms.
 */
काष्ठा f01_device_control अणु
	u8 ctrl0;
	u8 करोze_पूर्णांकerval;
	u8 wakeup_threshold;
	u8 करोze_holकरोff;
पूर्ण;

काष्ठा f01_data अणु
	काष्ठा f01_basic_properties properties;
	काष्ठा f01_device_control device_control;

	u16 करोze_पूर्णांकerval_addr;
	u16 wakeup_threshold_addr;
	u16 करोze_holकरोff_addr;

	bool suspended;
	bool old_nosleep;

	अचिन्हित पूर्णांक num_of_irq_regs;
पूर्ण;

अटल पूर्णांक rmi_f01_पढ़ो_properties(काष्ठा rmi_device *rmi_dev,
				   u16 query_base_addr,
				   काष्ठा f01_basic_properties *props)
अणु
	u8 queries[RMI_F01_BASIC_QUERY_LEN];
	पूर्णांक ret;
	पूर्णांक query_offset = query_base_addr;
	bool has_ds4_queries = false;
	bool has_query42 = false;
	bool has_sensor_id = false;
	bool has_package_id_query = false;
	bool has_build_id_query = false;
	u16 prod_info_addr;
	u8 ds4_query_len;

	ret = rmi_पढ़ो_block(rmi_dev, query_offset,
			       queries, RMI_F01_BASIC_QUERY_LEN);
	अगर (ret) अणु
		dev_err(&rmi_dev->dev,
			"Failed to read device query registers: %d\n", ret);
		वापस ret;
	पूर्ण

	prod_info_addr = query_offset + 17;
	query_offset += RMI_F01_BASIC_QUERY_LEN;

	/* Now parse what we got */
	props->manufacturer_id = queries[0];

	props->has_lts = queries[1] & RMI_F01_QRY1_HAS_LTS;
	props->has_adjustable_करोze =
			queries[1] & RMI_F01_QRY1_HAS_ADJ_DOZE;
	props->has_adjustable_करोze_holकरोff =
			queries[1] & RMI_F01_QRY1_HAS_ADJ_DOZE_HOFF;
	has_query42 = queries[1] & RMI_F01_QRY1_HAS_QUERY42;
	has_sensor_id = queries[1] & RMI_F01_QRY1_HAS_SENSOR_ID;

	snम_लिखो(props->करोm, माप(props->करोm), "20%02d/%02d/%02d",
		 queries[5] & RMI_F01_QRY5_YEAR_MASK,
		 queries[6] & RMI_F01_QRY6_MONTH_MASK,
		 queries[7] & RMI_F01_QRY7_DAY_MASK);

	स_नकल(props->product_id, &queries[11],
		RMI_PRODUCT_ID_LENGTH);
	props->product_id[RMI_PRODUCT_ID_LENGTH] = '\0';

	props->productinfo =
			((queries[2] & RMI_F01_QRY2_PRODINFO_MASK) << 7) |
			(queries[3] & RMI_F01_QRY2_PRODINFO_MASK);

	अगर (has_sensor_id)
		query_offset++;

	अगर (has_query42) अणु
		ret = rmi_पढ़ो(rmi_dev, query_offset, queries);
		अगर (ret) अणु
			dev_err(&rmi_dev->dev,
				"Failed to read query 42 register: %d\n", ret);
			वापस ret;
		पूर्ण

		has_ds4_queries = !!(queries[0] & BIT(0));
		query_offset++;
	पूर्ण

	अगर (has_ds4_queries) अणु
		ret = rmi_पढ़ो(rmi_dev, query_offset, &ds4_query_len);
		अगर (ret) अणु
			dev_err(&rmi_dev->dev,
				"Failed to read DS4 queries length: %d\n", ret);
			वापस ret;
		पूर्ण
		query_offset++;

		अगर (ds4_query_len > 0) अणु
			ret = rmi_पढ़ो(rmi_dev, query_offset, queries);
			अगर (ret) अणु
				dev_err(&rmi_dev->dev,
					"Failed to read DS4 queries: %d\n",
					ret);
				वापस ret;
			पूर्ण

			has_package_id_query = !!(queries[0] & BIT(0));
			has_build_id_query = !!(queries[0] & BIT(1));
		पूर्ण

		अगर (has_package_id_query) अणु
			ret = rmi_पढ़ो_block(rmi_dev, prod_info_addr,
					     queries, माप(__le64));
			अगर (ret) अणु
				dev_err(&rmi_dev->dev,
					"Failed to read package info: %d\n",
					ret);
				वापस ret;
			पूर्ण

			props->package_id = get_unaligned_le64(queries);
			prod_info_addr++;
		पूर्ण

		अगर (has_build_id_query) अणु
			ret = rmi_पढ़ो_block(rmi_dev, prod_info_addr, queries,
					    3);
			अगर (ret) अणु
				dev_err(&rmi_dev->dev,
					"Failed to read product info: %d\n",
					ret);
				वापस ret;
			पूर्ण

			props->firmware_id = queries[1] << 8 | queries[0];
			props->firmware_id += queries[2] * 65536;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

स्थिर अक्षर *rmi_f01_get_product_ID(काष्ठा rmi_function *fn)
अणु
	काष्ठा f01_data *f01 = dev_get_drvdata(&fn->dev);

	वापस f01->properties.product_id;
पूर्ण

अटल sमाप_प्रकार rmi_driver_manufacturer_id_show(काष्ठा device *dev,
					       काष्ठा device_attribute *dattr,
					       अक्षर *buf)
अणु
	काष्ठा rmi_driver_data *data = dev_get_drvdata(dev);
	काष्ठा f01_data *f01 = dev_get_drvdata(&data->f01_container->dev);

	वापस scnम_लिखो(buf, PAGE_SIZE, "%d\n",
			 f01->properties.manufacturer_id);
पूर्ण

अटल DEVICE_ATTR(manufacturer_id, 0444,
		   rmi_driver_manufacturer_id_show, शून्य);

अटल sमाप_प्रकार rmi_driver_करोm_show(काष्ठा device *dev,
				   काष्ठा device_attribute *dattr, अक्षर *buf)
अणु
	काष्ठा rmi_driver_data *data = dev_get_drvdata(dev);
	काष्ठा f01_data *f01 = dev_get_drvdata(&data->f01_container->dev);

	वापस scnम_लिखो(buf, PAGE_SIZE, "%s\n", f01->properties.करोm);
पूर्ण

अटल DEVICE_ATTR(date_of_manufacture, 0444, rmi_driver_करोm_show, शून्य);

अटल sमाप_प्रकार rmi_driver_product_id_show(काष्ठा device *dev,
					  काष्ठा device_attribute *dattr,
					  अक्षर *buf)
अणु
	काष्ठा rmi_driver_data *data = dev_get_drvdata(dev);
	काष्ठा f01_data *f01 = dev_get_drvdata(&data->f01_container->dev);

	वापस scnम_लिखो(buf, PAGE_SIZE, "%s\n", f01->properties.product_id);
पूर्ण

अटल DEVICE_ATTR(product_id, 0444, rmi_driver_product_id_show, शून्य);

अटल sमाप_प्रकार rmi_driver_firmware_id_show(काष्ठा device *dev,
					   काष्ठा device_attribute *dattr,
					   अक्षर *buf)
अणु
	काष्ठा rmi_driver_data *data = dev_get_drvdata(dev);
	काष्ठा f01_data *f01 = dev_get_drvdata(&data->f01_container->dev);

	वापस scnम_लिखो(buf, PAGE_SIZE, "%d\n", f01->properties.firmware_id);
पूर्ण

अटल DEVICE_ATTR(firmware_id, 0444, rmi_driver_firmware_id_show, शून्य);

अटल sमाप_प्रकार rmi_driver_package_id_show(काष्ठा device *dev,
					  काष्ठा device_attribute *dattr,
					  अक्षर *buf)
अणु
	काष्ठा rmi_driver_data *data = dev_get_drvdata(dev);
	काष्ठा f01_data *f01 = dev_get_drvdata(&data->f01_container->dev);

	u32 package_id = f01->properties.package_id;

	वापस scnम_लिखो(buf, PAGE_SIZE, "%04x.%04x\n",
			 package_id & 0xffff, (package_id >> 16) & 0xffff);
पूर्ण

अटल DEVICE_ATTR(package_id, 0444, rmi_driver_package_id_show, शून्य);

अटल काष्ठा attribute *rmi_f01_attrs[] = अणु
	&dev_attr_manufacturer_id.attr,
	&dev_attr_date_of_manufacture.attr,
	&dev_attr_product_id.attr,
	&dev_attr_firmware_id.attr,
	&dev_attr_package_id.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group rmi_f01_attr_group = अणु
	.attrs = rmi_f01_attrs,
पूर्ण;

#अगर_घोषित CONFIG_OF
अटल पूर्णांक rmi_f01_of_probe(काष्ठा device *dev,
				काष्ठा rmi_device_platक्रमm_data *pdata)
अणु
	पूर्णांक retval;
	u32 val;

	retval = rmi_of_property_पढ़ो_u32(dev,
			(u32 *)&pdata->घातer_management.nosleep,
			"syna,nosleep-mode", 1);
	अगर (retval)
		वापस retval;

	retval = rmi_of_property_पढ़ो_u32(dev, &val,
			"syna,wakeup-threshold", 1);
	अगर (retval)
		वापस retval;

	pdata->घातer_management.wakeup_threshold = val;

	retval = rmi_of_property_पढ़ो_u32(dev, &val,
			"syna,doze-holdoff-ms", 1);
	अगर (retval)
		वापस retval;

	pdata->घातer_management.करोze_holकरोff = val * 100;

	retval = rmi_of_property_पढ़ो_u32(dev, &val,
			"syna,doze-interval-ms", 1);
	अगर (retval)
		वापस retval;

	pdata->घातer_management.करोze_पूर्णांकerval = val / 10;

	वापस 0;
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक rmi_f01_of_probe(काष्ठा device *dev,
					काष्ठा rmi_device_platक्रमm_data *pdata)
अणु
	वापस -ENODEV;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक rmi_f01_probe(काष्ठा rmi_function *fn)
अणु
	काष्ठा rmi_device *rmi_dev = fn->rmi_dev;
	काष्ठा rmi_driver_data *driver_data = dev_get_drvdata(&rmi_dev->dev);
	काष्ठा rmi_device_platक्रमm_data *pdata = rmi_get_platक्रमm_data(rmi_dev);
	काष्ठा f01_data *f01;
	पूर्णांक error;
	u16 ctrl_base_addr = fn->fd.control_base_addr;
	u8 device_status;
	u8 temp;

	अगर (fn->dev.of_node) अणु
		error = rmi_f01_of_probe(&fn->dev, pdata);
		अगर (error)
			वापस error;
	पूर्ण

	f01 = devm_kzalloc(&fn->dev, माप(काष्ठा f01_data), GFP_KERNEL);
	अगर (!f01)
		वापस -ENOMEM;

	f01->num_of_irq_regs = driver_data->num_of_irq_regs;

	/*
	 * Set the configured bit and (optionally) other important stuff
	 * in the device control रेजिस्टर.
	 */

	error = rmi_पढ़ो(rmi_dev, fn->fd.control_base_addr,
			 &f01->device_control.ctrl0);
	अगर (error) अणु
		dev_err(&fn->dev, "Failed to read F01 control: %d\n", error);
		वापस error;
	पूर्ण

	चयन (pdata->घातer_management.nosleep) अणु
	हाल RMI_REG_STATE_DEFAULT:
		अवरोध;
	हाल RMI_REG_STATE_OFF:
		f01->device_control.ctrl0 &= ~RMI_F01_CTRL0_NOSLEEP_BIT;
		अवरोध;
	हाल RMI_REG_STATE_ON:
		f01->device_control.ctrl0 |= RMI_F01_CTRL0_NOSLEEP_BIT;
		अवरोध;
	पूर्ण

	/*
	 * Sleep mode might be set as a hangover from a प्रणाली crash or
	 * reboot without घातer cycle.  If so, clear it so the sensor
	 * is certain to function.
	 */
	अगर ((f01->device_control.ctrl0 & RMI_F01_CTRL0_SLEEP_MODE_MASK) !=
			RMI_SLEEP_MODE_NORMAL) अणु
		dev_warn(&fn->dev,
			 "WARNING: Non-zero sleep mode found. Clearing...\n");
		f01->device_control.ctrl0 &= ~RMI_F01_CTRL0_SLEEP_MODE_MASK;
	पूर्ण

	f01->device_control.ctrl0 |= RMI_F01_CTRL0_CONFIGURED_BIT;

	error = rmi_ग_लिखो(rmi_dev, fn->fd.control_base_addr,
			  f01->device_control.ctrl0);
	अगर (error) अणु
		dev_err(&fn->dev, "Failed to write F01 control: %d\n", error);
		वापस error;
	पूर्ण

	/* Dummy पढ़ो in order to clear irqs */
	error = rmi_पढ़ो(rmi_dev, fn->fd.data_base_addr + 1, &temp);
	अगर (error < 0) अणु
		dev_err(&fn->dev, "Failed to read Interrupt Status.\n");
		वापस error;
	पूर्ण

	error = rmi_f01_पढ़ो_properties(rmi_dev, fn->fd.query_base_addr,
					&f01->properties);
	अगर (error < 0) अणु
		dev_err(&fn->dev, "Failed to read F01 properties.\n");
		वापस error;
	पूर्ण

	dev_info(&fn->dev, "found RMI device, manufacturer: %s, product: %s, fw id: %d\n",
		 f01->properties.manufacturer_id == 1 ? "Synaptics" : "unknown",
		 f01->properties.product_id, f01->properties.firmware_id);

	/* Advance to पूर्णांकerrupt control रेजिस्टरs, then skip over them. */
	ctrl_base_addr++;
	ctrl_base_addr += f01->num_of_irq_regs;

	/* पढ़ो control रेजिस्टर */
	अगर (f01->properties.has_adjustable_करोze) अणु
		f01->करोze_पूर्णांकerval_addr = ctrl_base_addr;
		ctrl_base_addr++;

		अगर (pdata->घातer_management.करोze_पूर्णांकerval) अणु
			f01->device_control.करोze_पूर्णांकerval =
				pdata->घातer_management.करोze_पूर्णांकerval;
			error = rmi_ग_लिखो(rmi_dev, f01->करोze_पूर्णांकerval_addr,
					  f01->device_control.करोze_पूर्णांकerval);
			अगर (error) अणु
				dev_err(&fn->dev,
					"Failed to configure F01 doze interval register: %d\n",
					error);
				वापस error;
			पूर्ण
		पूर्ण अन्यथा अणु
			error = rmi_पढ़ो(rmi_dev, f01->करोze_पूर्णांकerval_addr,
					 &f01->device_control.करोze_पूर्णांकerval);
			अगर (error) अणु
				dev_err(&fn->dev,
					"Failed to read F01 doze interval register: %d\n",
					error);
				वापस error;
			पूर्ण
		पूर्ण

		f01->wakeup_threshold_addr = ctrl_base_addr;
		ctrl_base_addr++;

		अगर (pdata->घातer_management.wakeup_threshold) अणु
			f01->device_control.wakeup_threshold =
				pdata->घातer_management.wakeup_threshold;
			error = rmi_ग_लिखो(rmi_dev, f01->wakeup_threshold_addr,
					  f01->device_control.wakeup_threshold);
			अगर (error) अणु
				dev_err(&fn->dev,
					"Failed to configure F01 wakeup threshold register: %d\n",
					error);
				वापस error;
			पूर्ण
		पूर्ण अन्यथा अणु
			error = rmi_पढ़ो(rmi_dev, f01->wakeup_threshold_addr,
					 &f01->device_control.wakeup_threshold);
			अगर (error < 0) अणु
				dev_err(&fn->dev,
					"Failed to read F01 wakeup threshold register: %d\n",
					error);
				वापस error;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (f01->properties.has_lts)
		ctrl_base_addr++;

	अगर (f01->properties.has_adjustable_करोze_holकरोff) अणु
		f01->करोze_holकरोff_addr = ctrl_base_addr;
		ctrl_base_addr++;

		अगर (pdata->घातer_management.करोze_holकरोff) अणु
			f01->device_control.करोze_holकरोff =
				pdata->घातer_management.करोze_holकरोff;
			error = rmi_ग_लिखो(rmi_dev, f01->करोze_holकरोff_addr,
					  f01->device_control.करोze_holकरोff);
			अगर (error) अणु
				dev_err(&fn->dev,
					"Failed to configure F01 doze holdoff register: %d\n",
					error);
				वापस error;
			पूर्ण
		पूर्ण अन्यथा अणु
			error = rmi_पढ़ो(rmi_dev, f01->करोze_holकरोff_addr,
					 &f01->device_control.करोze_holकरोff);
			अगर (error) अणु
				dev_err(&fn->dev,
					"Failed to read F01 doze holdoff register: %d\n",
					error);
				वापस error;
			पूर्ण
		पूर्ण
	पूर्ण

	error = rmi_पढ़ो(rmi_dev, fn->fd.data_base_addr, &device_status);
	अगर (error < 0) अणु
		dev_err(&fn->dev,
			"Failed to read device status: %d\n", error);
		वापस error;
	पूर्ण

	अगर (RMI_F01_STATUS_UNCONFIGURED(device_status)) अणु
		dev_err(&fn->dev,
			"Device was reset during configuration process, status: %#02x!\n",
			RMI_F01_STATUS_CODE(device_status));
		वापस -EINVAL;
	पूर्ण

	dev_set_drvdata(&fn->dev, f01);

	error = sysfs_create_group(&fn->rmi_dev->dev.kobj, &rmi_f01_attr_group);
	अगर (error)
		dev_warn(&fn->dev, "Failed to create sysfs group: %d\n", error);

	वापस 0;
पूर्ण

अटल व्योम rmi_f01_हटाओ(काष्ठा rmi_function *fn)
अणु
	/* Note that the bus device is used, not the F01 device */
	sysfs_हटाओ_group(&fn->rmi_dev->dev.kobj, &rmi_f01_attr_group);
पूर्ण

अटल पूर्णांक rmi_f01_config(काष्ठा rmi_function *fn)
अणु
	काष्ठा f01_data *f01 = dev_get_drvdata(&fn->dev);
	पूर्णांक error;

	error = rmi_ग_लिखो(fn->rmi_dev, fn->fd.control_base_addr,
			  f01->device_control.ctrl0);
	अगर (error) अणु
		dev_err(&fn->dev,
			"Failed to write device_control register: %d\n", error);
		वापस error;
	पूर्ण

	अगर (f01->properties.has_adjustable_करोze) अणु
		error = rmi_ग_लिखो(fn->rmi_dev, f01->करोze_पूर्णांकerval_addr,
				  f01->device_control.करोze_पूर्णांकerval);
		अगर (error) अणु
			dev_err(&fn->dev,
				"Failed to write doze interval: %d\n", error);
			वापस error;
		पूर्ण

		error = rmi_ग_लिखो_block(fn->rmi_dev,
					 f01->wakeup_threshold_addr,
					 &f01->device_control.wakeup_threshold,
					 माप(u8));
		अगर (error) अणु
			dev_err(&fn->dev,
				"Failed to write wakeup threshold: %d\n",
				error);
			वापस error;
		पूर्ण
	पूर्ण

	अगर (f01->properties.has_adjustable_करोze_holकरोff) अणु
		error = rmi_ग_लिखो(fn->rmi_dev, f01->करोze_holकरोff_addr,
				  f01->device_control.करोze_holकरोff);
		अगर (error) अणु
			dev_err(&fn->dev,
				"Failed to write doze holdoff: %d\n", error);
			वापस error;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rmi_f01_suspend(काष्ठा rmi_function *fn)
अणु
	काष्ठा f01_data *f01 = dev_get_drvdata(&fn->dev);
	पूर्णांक error;

	f01->old_nosleep =
		f01->device_control.ctrl0 & RMI_F01_CTRL0_NOSLEEP_BIT;
	f01->device_control.ctrl0 &= ~RMI_F01_CTRL0_NOSLEEP_BIT;

	f01->device_control.ctrl0 &= ~RMI_F01_CTRL0_SLEEP_MODE_MASK;
	अगर (device_may_wakeup(fn->rmi_dev->xport->dev))
		f01->device_control.ctrl0 |= RMI_SLEEP_MODE_RESERVED1;
	अन्यथा
		f01->device_control.ctrl0 |= RMI_SLEEP_MODE_SENSOR_SLEEP;

	error = rmi_ग_लिखो(fn->rmi_dev, fn->fd.control_base_addr,
			  f01->device_control.ctrl0);
	अगर (error) अणु
		dev_err(&fn->dev, "Failed to write sleep mode: %d.\n", error);
		अगर (f01->old_nosleep)
			f01->device_control.ctrl0 |= RMI_F01_CTRL0_NOSLEEP_BIT;
		f01->device_control.ctrl0 &= ~RMI_F01_CTRL0_SLEEP_MODE_MASK;
		f01->device_control.ctrl0 |= RMI_SLEEP_MODE_NORMAL;
		वापस error;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rmi_f01_resume(काष्ठा rmi_function *fn)
अणु
	काष्ठा f01_data *f01 = dev_get_drvdata(&fn->dev);
	पूर्णांक error;

	अगर (f01->old_nosleep)
		f01->device_control.ctrl0 |= RMI_F01_CTRL0_NOSLEEP_BIT;

	f01->device_control.ctrl0 &= ~RMI_F01_CTRL0_SLEEP_MODE_MASK;
	f01->device_control.ctrl0 |= RMI_SLEEP_MODE_NORMAL;

	error = rmi_ग_लिखो(fn->rmi_dev, fn->fd.control_base_addr,
			  f01->device_control.ctrl0);
	अगर (error) अणु
		dev_err(&fn->dev,
			"Failed to restore normal operation: %d.\n", error);
		वापस error;
	पूर्ण

	वापस 0;
पूर्ण

अटल irqवापस_t rmi_f01_attention(पूर्णांक irq, व्योम *ctx)
अणु
	काष्ठा rmi_function *fn = ctx;
	काष्ठा rmi_device *rmi_dev = fn->rmi_dev;
	पूर्णांक error;
	u8 device_status;

	error = rmi_पढ़ो(rmi_dev, fn->fd.data_base_addr, &device_status);
	अगर (error) अणु
		dev_err(&fn->dev,
			"Failed to read device status: %d.\n", error);
		वापस IRQ_RETVAL(error);
	पूर्ण

	अगर (RMI_F01_STATUS_BOOTLOADER(device_status))
		dev_warn(&fn->dev,
			 "Device in bootloader mode, please update firmware\n");

	अगर (RMI_F01_STATUS_UNCONFIGURED(device_status)) अणु
		dev_warn(&fn->dev, "Device reset detected.\n");
		error = rmi_dev->driver->reset_handler(rmi_dev);
		अगर (error) अणु
			dev_err(&fn->dev, "Device reset failed: %d\n", error);
			वापस IRQ_RETVAL(error);
		पूर्ण
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

काष्ठा rmi_function_handler rmi_f01_handler = अणु
	.driver = अणु
		.name	= "rmi4_f01",
		/*
		 * Do not allow user unbinding F01 as it is critical
		 * function.
		 */
		.suppress_bind_attrs = true,
	पूर्ण,
	.func		= 0x01,
	.probe		= rmi_f01_probe,
	.हटाओ		= rmi_f01_हटाओ,
	.config		= rmi_f01_config,
	.attention	= rmi_f01_attention,
	.suspend	= rmi_f01_suspend,
	.resume		= rmi_f01_resume,
पूर्ण;
