<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * A hwmon driver क्रम the IBM PowerExecutive temperature/घातer sensors
 * Copyright (C) 2007 IBM
 *
 * Author: Darrick J. Wong <darrick.wong@oracle.com>
 */

#समावेश <linux/ipmi.h>
#समावेश <linux/module.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/hwmon-sysfs.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/mutex.h>
#समावेश <linux/slab.h>
#समावेश <linux/err.h>

#घोषणा REFRESH_INTERVAL	(2 * HZ)
#घोषणा DRVNAME			"ibmpex"

#घोषणा PEX_GET_VERSION		1
#घोषणा PEX_GET_SENSOR_COUNT	2
#घोषणा PEX_GET_SENSOR_NAME	3
#घोषणा PEX_RESET_HIGH_LOW	4
#घोषणा PEX_GET_SENSOR_DATA	6

#घोषणा PEX_NET_FUNCTION	0x3A
#घोषणा PEX_COMMAND		0x3C

अटल अंतरभूत u16 extract_value(स्थिर अक्षर *data, पूर्णांक offset)
अणु
	वापस be16_to_cpup((__be16 *)&data[offset]);
पूर्ण

#घोषणा TEMP_SENSOR		1
#घोषणा POWER_SENSOR		2

#घोषणा PEX_SENSOR_TYPE_LEN	3
अटल u8 स्थिर घातer_sensor_sig[] = अणु0x70, 0x77, 0x72पूर्ण;
अटल u8 स्थिर temp_sensor_sig[]  = अणु0x74, 0x65, 0x6Dपूर्ण;

#घोषणा PEX_MULT_LEN		2
अटल u8 स्थिर watt_sensor_sig[]  = अणु0x41, 0x43पूर्ण;

#घोषणा PEX_NUM_SENSOR_FUNCS	3
अटल स्थिर अक्षर * स्थिर sensor_name_suffixes[] = अणु
	"",
	"_lowest",
	"_highest"
पूर्ण;

अटल व्योम ibmpex_msg_handler(काष्ठा ipmi_recv_msg *msg, व्योम *user_msg_data);
अटल व्योम ibmpex_रेजिस्टर_bmc(पूर्णांक अगरace, काष्ठा device *dev);
अटल व्योम ibmpex_bmc_gone(पूर्णांक अगरace);

काष्ठा ibmpex_sensor_data अणु
	पूर्णांक			in_use;
	s16			values[PEX_NUM_SENSOR_FUNCS];
	पूर्णांक			multiplier;

	काष्ठा sensor_device_attribute_2	attr[PEX_NUM_SENSOR_FUNCS];
पूर्ण;

काष्ठा ibmpex_bmc_data अणु
	काष्ठा list_head	list;
	काष्ठा device		*hwmon_dev;
	काष्ठा device		*bmc_device;
	काष्ठा mutex		lock;
	अक्षर			valid;
	अचिन्हित दीर्घ		last_updated;	/* In jअगरfies */

	काष्ठा ipmi_addr	address;
	काष्ठा completion	पढ़ो_complete;
	काष्ठा ipmi_user	*user;
	पूर्णांक			पूर्णांकerface;

	काष्ठा kernel_ipmi_msg	tx_message;
	अचिन्हित अक्षर		tx_msg_data[IPMI_MAX_MSG_LENGTH];
	दीर्घ			tx_msgid;

	अचिन्हित अक्षर		rx_msg_data[IPMI_MAX_MSG_LENGTH];
	अचिन्हित दीर्घ		rx_msg_len;
	अचिन्हित अक्षर		rx_result;
	पूर्णांक			rx_recv_type;

	अचिन्हित अक्षर		sensor_major;
	अचिन्हित अक्षर		sensor_minor;

	अचिन्हित अक्षर		num_sensors;
	काष्ठा ibmpex_sensor_data	*sensors;
पूर्ण;

काष्ठा ibmpex_driver_data अणु
	काष्ठा list_head	bmc_data;
	काष्ठा ipmi_smi_watcher	bmc_events;
	काष्ठा ipmi_user_hndl	ipmi_hndlrs;
पूर्ण;

अटल काष्ठा ibmpex_driver_data driver_data = अणु
	.bmc_data = LIST_HEAD_INIT(driver_data.bmc_data),
	.bmc_events = अणु
		.owner = THIS_MODULE,
		.new_smi = ibmpex_रेजिस्टर_bmc,
		.smi_gone = ibmpex_bmc_gone,
	पूर्ण,
	.ipmi_hndlrs = अणु
		.ipmi_recv_hndl = ibmpex_msg_handler,
	पूर्ण,
पूर्ण;

अटल पूर्णांक ibmpex_send_message(काष्ठा ibmpex_bmc_data *data)
अणु
	पूर्णांक err;

	err = ipmi_validate_addr(&data->address, माप(data->address));
	अगर (err)
		जाओ out;

	data->tx_msgid++;
	err = ipmi_request_समय_रखो(data->user, &data->address, data->tx_msgid,
				   &data->tx_message, data, 0, 0, 0);
	अगर (err)
		जाओ out1;

	वापस 0;
out1:
	dev_err(data->bmc_device, "request_settime=%x\n", err);
	वापस err;
out:
	dev_err(data->bmc_device, "validate_addr=%x\n", err);
	वापस err;
पूर्ण

अटल पूर्णांक ibmpex_ver_check(काष्ठा ibmpex_bmc_data *data)
अणु
	data->tx_msg_data[0] = PEX_GET_VERSION;
	data->tx_message.data_len = 1;
	ibmpex_send_message(data);

	रुको_क्रम_completion(&data->पढ़ो_complete);

	अगर (data->rx_result || data->rx_msg_len != 6)
		वापस -ENOENT;

	data->sensor_major = data->rx_msg_data[0];
	data->sensor_minor = data->rx_msg_data[1];

	dev_info(data->bmc_device,
		 "Found BMC with sensor interface v%d.%d %d-%02d-%02d on interface %d\n",
		 data->sensor_major,
		 data->sensor_minor,
		 extract_value(data->rx_msg_data, 2),
		 data->rx_msg_data[4],
		 data->rx_msg_data[5],
		 data->पूर्णांकerface);

	वापस 0;
पूर्ण

अटल पूर्णांक ibmpex_query_sensor_count(काष्ठा ibmpex_bmc_data *data)
अणु
	data->tx_msg_data[0] = PEX_GET_SENSOR_COUNT;
	data->tx_message.data_len = 1;
	ibmpex_send_message(data);

	रुको_क्रम_completion(&data->पढ़ो_complete);

	अगर (data->rx_result || data->rx_msg_len != 1)
		वापस -ENOENT;

	वापस data->rx_msg_data[0];
पूर्ण

अटल पूर्णांक ibmpex_query_sensor_name(काष्ठा ibmpex_bmc_data *data, पूर्णांक sensor)
अणु
	data->tx_msg_data[0] = PEX_GET_SENSOR_NAME;
	data->tx_msg_data[1] = sensor;
	data->tx_message.data_len = 2;
	ibmpex_send_message(data);

	रुको_क्रम_completion(&data->पढ़ो_complete);

	अगर (data->rx_result || data->rx_msg_len < 1)
		वापस -ENOENT;

	वापस 0;
पूर्ण

अटल पूर्णांक ibmpex_query_sensor_data(काष्ठा ibmpex_bmc_data *data, पूर्णांक sensor)
अणु
	data->tx_msg_data[0] = PEX_GET_SENSOR_DATA;
	data->tx_msg_data[1] = sensor;
	data->tx_message.data_len = 2;
	ibmpex_send_message(data);

	रुको_क्रम_completion(&data->पढ़ो_complete);

	अगर (data->rx_result || data->rx_msg_len < 26) अणु
		dev_err(data->bmc_device, "Error reading sensor %d.\n",
			sensor);
		वापस -ENOENT;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ibmpex_reset_high_low_data(काष्ठा ibmpex_bmc_data *data)
अणु
	data->tx_msg_data[0] = PEX_RESET_HIGH_LOW;
	data->tx_message.data_len = 1;
	ibmpex_send_message(data);

	रुको_क्रम_completion(&data->पढ़ो_complete);

	वापस 0;
पूर्ण

अटल व्योम ibmpex_update_device(काष्ठा ibmpex_bmc_data *data)
अणु
	पूर्णांक i, err;

	mutex_lock(&data->lock);
	अगर (समय_beक्रमe(jअगरfies, data->last_updated + REFRESH_INTERVAL) &&
	    data->valid)
		जाओ out;

	क्रम (i = 0; i < data->num_sensors; i++) अणु
		अगर (!data->sensors[i].in_use)
			जारी;
		err = ibmpex_query_sensor_data(data, i);
		अगर (err)
			जारी;
		data->sensors[i].values[0] =
			extract_value(data->rx_msg_data, 16);
		data->sensors[i].values[1] =
			extract_value(data->rx_msg_data, 18);
		data->sensors[i].values[2] =
			extract_value(data->rx_msg_data, 20);
	पूर्ण

	data->last_updated = jअगरfies;
	data->valid = 1;

out:
	mutex_unlock(&data->lock);
पूर्ण

अटल काष्ठा ibmpex_bmc_data *get_bmc_data(पूर्णांक अगरace)
अणु
	काष्ठा ibmpex_bmc_data *p, *next;

	list_क्रम_each_entry_safe(p, next, &driver_data.bmc_data, list)
		अगर (p->पूर्णांकerface == अगरace)
			वापस p;

	वापस शून्य;
पूर्ण

अटल sमाप_प्रकार name_show(काष्ठा device *dev, काष्ठा device_attribute *devattr,
			 अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%s\n", DRVNAME);
पूर्ण
अटल SENSOR_DEVICE_ATTR_RO(name, name, 0);

अटल sमाप_प्रकार ibmpex_show_sensor(काष्ठा device *dev,
				  काष्ठा device_attribute *devattr,
				  अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute_2 *attr = to_sensor_dev_attr_2(devattr);
	काष्ठा ibmpex_bmc_data *data = dev_get_drvdata(dev);
	पूर्णांक mult = data->sensors[attr->index].multiplier;
	ibmpex_update_device(data);

	वापस प्र_लिखो(buf, "%d\n",
		       data->sensors[attr->index].values[attr->nr] * mult);
पूर्ण

अटल sमाप_प्रकार ibmpex_high_low_store(काष्ठा device *dev,
				     काष्ठा device_attribute *devattr,
				     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा ibmpex_bmc_data *data = dev_get_drvdata(dev);

	ibmpex_reset_high_low_data(data);

	वापस count;
पूर्ण

अटल SENSOR_DEVICE_ATTR_WO(reset_high_low, ibmpex_high_low, 0);

अटल पूर्णांक is_घातer_sensor(स्थिर अक्षर *sensor_id, पूर्णांक len)
अणु
	अगर (len < PEX_SENSOR_TYPE_LEN)
		वापस 0;

	अगर (!स_भेद(sensor_id, घातer_sensor_sig, PEX_SENSOR_TYPE_LEN))
		वापस 1;
	वापस 0;
पूर्ण

अटल पूर्णांक is_temp_sensor(स्थिर अक्षर *sensor_id, पूर्णांक len)
अणु
	अगर (len < PEX_SENSOR_TYPE_LEN)
		वापस 0;

	अगर (!स_भेद(sensor_id, temp_sensor_sig, PEX_SENSOR_TYPE_LEN))
		वापस 1;
	वापस 0;
पूर्ण

अटल पूर्णांक घातer_sensor_multiplier(काष्ठा ibmpex_bmc_data *data,
				   स्थिर अक्षर *sensor_id, पूर्णांक len)
अणु
	पूर्णांक i;

	अगर (data->sensor_major == 2)
		वापस 1000000;

	क्रम (i = PEX_SENSOR_TYPE_LEN; i < len - 1; i++)
		अगर (!स_भेद(&sensor_id[i], watt_sensor_sig, PEX_MULT_LEN))
			वापस 1000000;

	वापस 100000;
पूर्ण

अटल पूर्णांक create_sensor(काष्ठा ibmpex_bmc_data *data, पूर्णांक type,
			 पूर्णांक counter, पूर्णांक sensor, पूर्णांक func)
अणु
	पूर्णांक err;
	अक्षर *n;

	n = kदो_स्मृति(32, GFP_KERNEL);
	अगर (!n)
		वापस -ENOMEM;

	अगर (type == TEMP_SENSOR)
		प्र_लिखो(n, "temp%d_input%s",
			counter, sensor_name_suffixes[func]);
	अन्यथा अगर (type == POWER_SENSOR)
		प्र_लिखो(n, "power%d_average%s",
			counter, sensor_name_suffixes[func]);

	sysfs_attr_init(&data->sensors[sensor].attr[func].dev_attr.attr);
	data->sensors[sensor].attr[func].dev_attr.attr.name = n;
	data->sensors[sensor].attr[func].dev_attr.attr.mode = 0444;
	data->sensors[sensor].attr[func].dev_attr.show = ibmpex_show_sensor;
	data->sensors[sensor].attr[func].index = sensor;
	data->sensors[sensor].attr[func].nr = func;

	err = device_create_file(data->bmc_device,
				 &data->sensors[sensor].attr[func].dev_attr);
	अगर (err) अणु
		data->sensors[sensor].attr[func].dev_attr.attr.name = शून्य;
		kमुक्त(n);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ibmpex_find_sensors(काष्ठा ibmpex_bmc_data *data)
अणु
	पूर्णांक i, j, err;
	पूर्णांक sensor_type;
	पूर्णांक sensor_counter;
	पूर्णांक num_घातer = 0;
	पूर्णांक num_temp = 0;

	err = ibmpex_query_sensor_count(data);
	अगर (err <= 0)
		वापस -ENOENT;
	data->num_sensors = err;

	data->sensors = kसुस्मृति(data->num_sensors, माप(*data->sensors),
				GFP_KERNEL);
	अगर (!data->sensors)
		वापस -ENOMEM;

	क्रम (i = 0; i < data->num_sensors; i++) अणु
		err = ibmpex_query_sensor_name(data, i);
		अगर (err)
			जारी;

		अगर (is_घातer_sensor(data->rx_msg_data, data->rx_msg_len)) अणु
			sensor_type = POWER_SENSOR;
			num_घातer++;
			sensor_counter = num_घातer;
			data->sensors[i].multiplier =
				घातer_sensor_multiplier(data,
							data->rx_msg_data,
							data->rx_msg_len);
		पूर्ण अन्यथा अगर (is_temp_sensor(data->rx_msg_data,
					  data->rx_msg_len)) अणु
			sensor_type = TEMP_SENSOR;
			num_temp++;
			sensor_counter = num_temp;
			data->sensors[i].multiplier = 1000;
		पूर्ण अन्यथा
			जारी;

		data->sensors[i].in_use = 1;

		/* Create attributes */
		क्रम (j = 0; j < PEX_NUM_SENSOR_FUNCS; j++) अणु
			err = create_sensor(data, sensor_type, sensor_counter,
					    i, j);
			अगर (err)
				जाओ निकास_हटाओ;
		पूर्ण
	पूर्ण

	err = device_create_file(data->bmc_device,
			&sensor_dev_attr_reset_high_low.dev_attr);
	अगर (err)
		जाओ निकास_हटाओ;

	err = device_create_file(data->bmc_device,
			&sensor_dev_attr_name.dev_attr);
	अगर (err)
		जाओ निकास_हटाओ;

	वापस 0;

निकास_हटाओ:
	device_हटाओ_file(data->bmc_device,
			   &sensor_dev_attr_reset_high_low.dev_attr);
	device_हटाओ_file(data->bmc_device, &sensor_dev_attr_name.dev_attr);
	क्रम (i = 0; i < data->num_sensors; i++)
		क्रम (j = 0; j < PEX_NUM_SENSOR_FUNCS; j++) अणु
			अगर (!data->sensors[i].attr[j].dev_attr.attr.name)
				जारी;
			device_हटाओ_file(data->bmc_device,
				&data->sensors[i].attr[j].dev_attr);
			kमुक्त(data->sensors[i].attr[j].dev_attr.attr.name);
		पूर्ण

	kमुक्त(data->sensors);
	वापस err;
पूर्ण

अटल व्योम ibmpex_रेजिस्टर_bmc(पूर्णांक अगरace, काष्ठा device *dev)
अणु
	काष्ठा ibmpex_bmc_data *data;
	पूर्णांक err;

	data = kzalloc(माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस;

	data->address.addr_type = IPMI_SYSTEM_INTERFACE_ADDR_TYPE;
	data->address.channel = IPMI_BMC_CHANNEL;
	data->address.data[0] = 0;
	data->पूर्णांकerface = अगरace;
	data->bmc_device = dev;

	/* Create IPMI messaging पूर्णांकerface user */
	err = ipmi_create_user(data->पूर्णांकerface, &driver_data.ipmi_hndlrs,
			       data, &data->user);
	अगर (err < 0) अणु
		dev_err(dev,
			"Unable to register user with IPMI interface %d\n",
			data->पूर्णांकerface);
		जाओ out;
	पूर्ण

	mutex_init(&data->lock);

	/* Initialize message */
	data->tx_msgid = 0;
	init_completion(&data->पढ़ो_complete);
	data->tx_message.netfn = PEX_NET_FUNCTION;
	data->tx_message.cmd = PEX_COMMAND;
	data->tx_message.data = data->tx_msg_data;

	/* Does this BMC support PowerExecutive? */
	err = ibmpex_ver_check(data);
	अगर (err)
		जाओ out_user;

	/* Register the BMC as a HWMON class device */
	data->hwmon_dev = hwmon_device_रेजिस्टर(data->bmc_device);

	अगर (IS_ERR(data->hwmon_dev)) अणु
		dev_err(data->bmc_device,
			"Unable to register hwmon device for IPMI interface %d\n",
			data->पूर्णांकerface);
		जाओ out_user;
	पूर्ण

	/* finally add the new bmc data to the bmc data list */
	dev_set_drvdata(dev, data);
	list_add_tail(&data->list, &driver_data.bmc_data);

	/* Now go find all the sensors */
	err = ibmpex_find_sensors(data);
	अगर (err) अणु
		dev_err(data->bmc_device, "Error %d finding sensors\n", err);
		जाओ out_रेजिस्टर;
	पूर्ण

	वापस;

out_रेजिस्टर:
	hwmon_device_unरेजिस्टर(data->hwmon_dev);
out_user:
	ipmi_destroy_user(data->user);
out:
	kमुक्त(data);
पूर्ण

अटल व्योम ibmpex_bmc_delete(काष्ठा ibmpex_bmc_data *data)
अणु
	पूर्णांक i, j;

	device_हटाओ_file(data->bmc_device,
			   &sensor_dev_attr_reset_high_low.dev_attr);
	device_हटाओ_file(data->bmc_device, &sensor_dev_attr_name.dev_attr);
	क्रम (i = 0; i < data->num_sensors; i++)
		क्रम (j = 0; j < PEX_NUM_SENSOR_FUNCS; j++) अणु
			अगर (!data->sensors[i].attr[j].dev_attr.attr.name)
				जारी;
			device_हटाओ_file(data->bmc_device,
				&data->sensors[i].attr[j].dev_attr);
			kमुक्त(data->sensors[i].attr[j].dev_attr.attr.name);
		पूर्ण

	list_del(&data->list);
	dev_set_drvdata(data->bmc_device, शून्य);
	hwmon_device_unरेजिस्टर(data->hwmon_dev);
	ipmi_destroy_user(data->user);
	kमुक्त(data->sensors);
	kमुक्त(data);
पूर्ण

अटल व्योम ibmpex_bmc_gone(पूर्णांक अगरace)
अणु
	काष्ठा ibmpex_bmc_data *data = get_bmc_data(अगरace);

	अगर (!data)
		वापस;

	ibmpex_bmc_delete(data);
पूर्ण

अटल व्योम ibmpex_msg_handler(काष्ठा ipmi_recv_msg *msg, व्योम *user_msg_data)
अणु
	काष्ठा ibmpex_bmc_data *data = (काष्ठा ibmpex_bmc_data *)user_msg_data;

	अगर (msg->msgid != data->tx_msgid) अणु
		dev_err(data->bmc_device,
			"Mismatch between received msgid (%02x) and transmitted msgid (%02x)!\n",
			(पूर्णांक)msg->msgid,
			(पूर्णांक)data->tx_msgid);
		ipmi_मुक्त_recv_msg(msg);
		वापस;
	पूर्ण

	data->rx_recv_type = msg->recv_type;
	अगर (msg->msg.data_len > 0)
		data->rx_result = msg->msg.data[0];
	अन्यथा
		data->rx_result = IPMI_UNKNOWN_ERR_COMPLETION_CODE;

	अगर (msg->msg.data_len > 1) अणु
		data->rx_msg_len = msg->msg.data_len - 1;
		स_नकल(data->rx_msg_data, msg->msg.data + 1, data->rx_msg_len);
	पूर्ण अन्यथा
		data->rx_msg_len = 0;

	ipmi_मुक्त_recv_msg(msg);
	complete(&data->पढ़ो_complete);
पूर्ण

अटल पूर्णांक __init ibmpex_init(व्योम)
अणु
	वापस ipmi_smi_watcher_रेजिस्टर(&driver_data.bmc_events);
पूर्ण

अटल व्योम __निकास ibmpex_निकास(व्योम)
अणु
	काष्ठा ibmpex_bmc_data *p, *next;

	ipmi_smi_watcher_unरेजिस्टर(&driver_data.bmc_events);
	list_क्रम_each_entry_safe(p, next, &driver_data.bmc_data, list)
		ibmpex_bmc_delete(p);
पूर्ण

MODULE_AUTHOR("Darrick J. Wong <darrick.wong@oracle.com>");
MODULE_DESCRIPTION("IBM PowerExecutive power/temperature sensor driver");
MODULE_LICENSE("GPL");

module_init(ibmpex_init);
module_निकास(ibmpex_निकास);

MODULE_ALIAS("dmi:bvnIBM:*:pnIBMSystemx3350-*");
MODULE_ALIAS("dmi:bvnIBM:*:pnIBMSystemx3550-*");
MODULE_ALIAS("dmi:bvnIBM:*:pnIBMSystemx3650-*");
MODULE_ALIAS("dmi:bvnIBM:*:pnIBMSystemx3655-*");
MODULE_ALIAS("dmi:bvnIBM:*:pnIBMSystemx3755-*");
