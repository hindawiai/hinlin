<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * A hwmon driver क्रम the IBM System Director Active Energy Manager (AEM)
 * temperature/घातer/energy sensors and capping functionality.
 * Copyright (C) 2008 IBM
 *
 * Author: Darrick J. Wong <darrick.wong@oracle.com>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/ipmi.h>
#समावेश <linux/module.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/hwmon-sysfs.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/mutex.h>
#समावेश <linux/kdev_t.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/idr.h>
#समावेश <linux/slab.h>
#समावेश <linux/sched.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/math64.h>
#समावेश <linux/समय.स>
#समावेश <linux/err.h>

#घोषणा REFRESH_INTERVAL	(HZ)
#घोषणा IPMI_TIMEOUT		(30 * HZ)
#घोषणा DRVNAME			"aem"

#घोषणा AEM_NETFN		0x2E

#घोषणा AEM_FIND_FW_CMD		0x80
#घोषणा AEM_ELEMENT_CMD		0x81
#घोषणा AEM_FW_INSTANCE_CMD	0x82

#घोषणा AEM_READ_ELEMENT_CFG	0x80
#घोषणा AEM_READ_BUFFER		0x81
#घोषणा AEM_READ_REGISTER	0x82
#घोषणा AEM_WRITE_REGISTER	0x83
#घोषणा AEM_SET_REG_MASK	0x84
#घोषणा AEM_CLEAR_REG_MASK	0x85
#घोषणा AEM_READ_ELEMENT_CFG2	0x86

#घोषणा AEM_CONTROL_ELEMENT	0
#घोषणा AEM_ENERGY_ELEMENT	1
#घोषणा AEM_CLOCK_ELEMENT	4
#घोषणा AEM_POWER_CAP_ELEMENT	7
#घोषणा AEM_EXHAUST_ELEMENT	9
#घोषणा AEM_POWER_ELEMENT	10

#घोषणा AEM_MODULE_TYPE_ID	0x0001

#घोषणा AEM2_NUM_ENERGY_REGS	2
#घोषणा AEM2_NUM_PCAP_REGS	6
#घोषणा AEM2_NUM_TEMP_REGS	2
#घोषणा AEM2_NUM_SENSORS	14

#घोषणा AEM1_NUM_ENERGY_REGS	1
#घोषणा AEM1_NUM_SENSORS	3

/* AEM 2.x has more energy रेजिस्टरs */
#घोषणा AEM_NUM_ENERGY_REGS	AEM2_NUM_ENERGY_REGS
/* AEM 2.x needs more sensor files */
#घोषणा AEM_NUM_SENSORS		AEM2_NUM_SENSORS

#घोषणा POWER_CAP		0
#घोषणा POWER_CAP_MAX_HOTPLUG	1
#घोषणा POWER_CAP_MAX		2
#घोषणा	POWER_CAP_MIN_WARNING	3
#घोषणा POWER_CAP_MIN		4
#घोषणा	POWER_AUX		5

#घोषणा AEM_DEFAULT_POWER_INTERVAL 1000
#घोषणा AEM_MIN_POWER_INTERVAL	200
#घोषणा UJ_PER_MJ		1000L

अटल DEFINE_IDA(aem_ida);

अटल काष्ठा platक्रमm_driver aem_driver = अणु
	.driver = अणु
		.name = DRVNAME,
		.bus = &platक्रमm_bus_type,
	पूर्ण
पूर्ण;

काष्ठा aem_ipmi_data अणु
	काष्ठा completion	पढ़ो_complete;
	काष्ठा ipmi_addr	address;
	काष्ठा ipmi_user	*user;
	पूर्णांक			पूर्णांकerface;

	काष्ठा kernel_ipmi_msg	tx_message;
	दीर्घ			tx_msgid;

	व्योम			*rx_msg_data;
	अचिन्हित लघु		rx_msg_len;
	अचिन्हित अक्षर		rx_result;
	पूर्णांक			rx_recv_type;

	काष्ठा device		*bmc_device;
पूर्ण;

काष्ठा aem_ro_sensor_ढाँचा अणु
	अक्षर *label;
	sमाप_प्रकार (*show)(काष्ठा device *dev,
			काष्ठा device_attribute *devattr,
			अक्षर *buf);
	पूर्णांक index;
पूर्ण;

काष्ठा aem_rw_sensor_ढाँचा अणु
	अक्षर *label;
	sमाप_प्रकार (*show)(काष्ठा device *dev,
			काष्ठा device_attribute *devattr,
			अक्षर *buf);
	sमाप_प्रकार (*set)(काष्ठा device *dev,
		       काष्ठा device_attribute *devattr,
		       स्थिर अक्षर *buf, माप_प्रकार count);
	पूर्णांक index;
पूर्ण;

काष्ठा aem_data अणु
	काष्ठा list_head	list;

	काष्ठा device		*hwmon_dev;
	काष्ठा platक्रमm_device	*pdev;
	काष्ठा mutex		lock;
	अक्षर			valid;
	अचिन्हित दीर्घ		last_updated;	/* In jअगरfies */
	u8			ver_major;
	u8			ver_minor;
	u8			module_handle;
	पूर्णांक			id;
	काष्ठा aem_ipmi_data	ipmi;

	/* Function and buffer to update sensors */
	व्योम (*update)(काष्ठा aem_data *data);
	काष्ठा aem_पढ़ो_sensor_resp *rs_resp;

	/*
	 * AEM 1.x sensors:
	 * Available sensors:
	 * Energy meter
	 * Power meter
	 *
	 * AEM 2.x sensors:
	 * Two energy meters
	 * Two घातer meters
	 * Two temperature sensors
	 * Six घातer cap रेजिस्टरs
	 */

	/* sysfs attrs */
	काष्ठा sensor_device_attribute	sensors[AEM_NUM_SENSORS];

	/* energy use in mJ */
	u64			energy[AEM_NUM_ENERGY_REGS];

	/* घातer sampling पूर्णांकerval in ms */
	अचिन्हित दीर्घ		घातer_period[AEM_NUM_ENERGY_REGS];

	/* Everything past here is क्रम AEM2 only */

	/* घातer caps in dW */
	u16			pcap[AEM2_NUM_PCAP_REGS];

	/* exhaust temperature in C */
	u8			temp[AEM2_NUM_TEMP_REGS];
पूर्ण;

/* Data काष्ठाures वापसed by the AEM firmware */
काष्ठा aem_iana_id अणु
	u8			bytes[3];
पूर्ण;
अटल काष्ठा aem_iana_id प्रणाली_x_id = अणु
	.bytes = अणु0x4D, 0x4F, 0x00पूर्ण
पूर्ण;

/* These are used to find AEM1 instances */
काष्ठा aem_find_firmware_req अणु
	काष्ठा aem_iana_id	id;
	u8			rsvd;
	__be16			index;
	__be16			module_type_id;
पूर्ण __packed;

काष्ठा aem_find_firmware_resp अणु
	काष्ठा aem_iana_id	id;
	u8			num_instances;
पूर्ण __packed;

/* These are used to find AEM2 instances */
काष्ठा aem_find_instance_req अणु
	काष्ठा aem_iana_id	id;
	u8			instance_number;
	__be16			module_type_id;
पूर्ण __packed;

काष्ठा aem_find_instance_resp अणु
	काष्ठा aem_iana_id	id;
	u8			num_instances;
	u8			major;
	u8			minor;
	u8			module_handle;
	u16			record_id;
पूर्ण __packed;

/* These are used to query sensors */
काष्ठा aem_पढ़ो_sensor_req अणु
	काष्ठा aem_iana_id	id;
	u8			module_handle;
	u8			element;
	u8			subcommand;
	u8			reg;
	u8			rx_buf_size;
पूर्ण __packed;

काष्ठा aem_पढ़ो_sensor_resp अणु
	काष्ठा aem_iana_id	id;
	u8			bytes[];
पूर्ण __packed;

/* Data काष्ठाures to talk to the IPMI layer */
काष्ठा aem_driver_data अणु
	काष्ठा list_head	aem_devices;
	काष्ठा ipmi_smi_watcher	bmc_events;
	काष्ठा ipmi_user_hndl	ipmi_hndlrs;
पूर्ण;

अटल व्योम aem_रेजिस्टर_bmc(पूर्णांक अगरace, काष्ठा device *dev);
अटल व्योम aem_bmc_gone(पूर्णांक अगरace);
अटल व्योम aem_msg_handler(काष्ठा ipmi_recv_msg *msg, व्योम *user_msg_data);

अटल व्योम aem_हटाओ_sensors(काष्ठा aem_data *data);
अटल पूर्णांक aem1_find_sensors(काष्ठा aem_data *data);
अटल पूर्णांक aem2_find_sensors(काष्ठा aem_data *data);
अटल व्योम update_aem1_sensors(काष्ठा aem_data *data);
अटल व्योम update_aem2_sensors(काष्ठा aem_data *data);

अटल काष्ठा aem_driver_data driver_data = अणु
	.aem_devices = LIST_HEAD_INIT(driver_data.aem_devices),
	.bmc_events = अणु
		.owner = THIS_MODULE,
		.new_smi = aem_रेजिस्टर_bmc,
		.smi_gone = aem_bmc_gone,
	पूर्ण,
	.ipmi_hndlrs = अणु
		.ipmi_recv_hndl = aem_msg_handler,
	पूर्ण,
पूर्ण;

/* Functions to talk to the IPMI layer */

/* Initialize IPMI address, message buffers and user data */
अटल पूर्णांक aem_init_ipmi_data(काष्ठा aem_ipmi_data *data, पूर्णांक अगरace,
			      काष्ठा device *bmc)
अणु
	पूर्णांक err;

	init_completion(&data->पढ़ो_complete);
	data->bmc_device = bmc;

	/* Initialize IPMI address */
	data->address.addr_type = IPMI_SYSTEM_INTERFACE_ADDR_TYPE;
	data->address.channel = IPMI_BMC_CHANNEL;
	data->address.data[0] = 0;
	data->पूर्णांकerface = अगरace;

	/* Initialize message buffers */
	data->tx_msgid = 0;
	data->tx_message.netfn = AEM_NETFN;

	/* Create IPMI messaging पूर्णांकerface user */
	err = ipmi_create_user(data->पूर्णांकerface, &driver_data.ipmi_hndlrs,
			       data, &data->user);
	अगर (err < 0) अणु
		dev_err(bmc,
			"Unable to register user with IPMI interface %d\n",
			data->पूर्णांकerface);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

/* Send an IPMI command */
अटल पूर्णांक aem_send_message(काष्ठा aem_ipmi_data *data)
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

/* Dispatch IPMI messages to callers */
अटल व्योम aem_msg_handler(काष्ठा ipmi_recv_msg *msg, व्योम *user_msg_data)
अणु
	अचिन्हित लघु rx_len;
	काष्ठा aem_ipmi_data *data = user_msg_data;

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
		rx_len = msg->msg.data_len - 1;
		अगर (data->rx_msg_len < rx_len)
			rx_len = data->rx_msg_len;
		data->rx_msg_len = rx_len;
		स_नकल(data->rx_msg_data, msg->msg.data + 1, data->rx_msg_len);
	पूर्ण अन्यथा
		data->rx_msg_len = 0;

	ipmi_मुक्त_recv_msg(msg);
	complete(&data->पढ़ो_complete);
पूर्ण

/* Sensor support functions */

/* Read a sensor value; must be called with data->lock held */
अटल पूर्णांक aem_पढ़ो_sensor(काष्ठा aem_data *data, u8 elt, u8 reg,
			   व्योम *buf, माप_प्रकार size)
अणु
	पूर्णांक rs_size, res;
	काष्ठा aem_पढ़ो_sensor_req rs_req;
	/* Use pपुनः_स्मृतिated rx buffer */
	काष्ठा aem_पढ़ो_sensor_resp *rs_resp = data->rs_resp;
	काष्ठा aem_ipmi_data *ipmi = &data->ipmi;

	/* AEM रेजिस्टरs are 1, 2, 4 or 8 bytes */
	चयन (size) अणु
	हाल 1:
	हाल 2:
	हाल 4:
	हाल 8:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	rs_req.id = प्रणाली_x_id;
	rs_req.module_handle = data->module_handle;
	rs_req.element = elt;
	rs_req.subcommand = AEM_READ_REGISTER;
	rs_req.reg = reg;
	rs_req.rx_buf_size = size;

	ipmi->tx_message.cmd = AEM_ELEMENT_CMD;
	ipmi->tx_message.data = (अक्षर *)&rs_req;
	ipmi->tx_message.data_len = माप(rs_req);

	rs_size = माप(*rs_resp) + size;
	ipmi->rx_msg_data = rs_resp;
	ipmi->rx_msg_len = rs_size;

	aem_send_message(ipmi);

	res = रुको_क्रम_completion_समयout(&ipmi->पढ़ो_complete, IPMI_TIMEOUT);
	अगर (!res) अणु
		res = -ETIMEDOUT;
		जाओ out;
	पूर्ण

	अगर (ipmi->rx_result || ipmi->rx_msg_len != rs_size ||
	    स_भेद(&rs_resp->id, &प्रणाली_x_id, माप(प्रणाली_x_id))) अणु
		res = -ENOENT;
		जाओ out;
	पूर्ण

	चयन (size) अणु
	हाल 1: अणु
		u8 *x = buf;
		*x = rs_resp->bytes[0];
		अवरोध;
	पूर्ण
	हाल 2: अणु
		u16 *x = buf;
		*x = be16_to_cpup((__be16 *)rs_resp->bytes);
		अवरोध;
	पूर्ण
	हाल 4: अणु
		u32 *x = buf;
		*x = be32_to_cpup((__be32 *)rs_resp->bytes);
		अवरोध;
	पूर्ण
	हाल 8: अणु
		u64 *x = buf;
		*x = be64_to_cpup((__be64 *)rs_resp->bytes);
		अवरोध;
	पूर्ण
	पूर्ण
	res = 0;

out:
	वापस res;
पूर्ण

/* Update AEM energy रेजिस्टरs */
अटल व्योम update_aem_energy_one(काष्ठा aem_data *data, पूर्णांक which)
अणु
	aem_पढ़ो_sensor(data, AEM_ENERGY_ELEMENT, which,
			&data->energy[which], 8);
पूर्ण

अटल व्योम update_aem_energy(काष्ठा aem_data *data)
अणु
	update_aem_energy_one(data, 0);
	अगर (data->ver_major < 2)
		वापस;
	update_aem_energy_one(data, 1);
पूर्ण

/* Update all AEM1 sensors */
अटल व्योम update_aem1_sensors(काष्ठा aem_data *data)
अणु
	mutex_lock(&data->lock);
	अगर (समय_beक्रमe(jअगरfies, data->last_updated + REFRESH_INTERVAL) &&
	    data->valid)
		जाओ out;

	update_aem_energy(data);
out:
	mutex_unlock(&data->lock);
पूर्ण

/* Update all AEM2 sensors */
अटल व्योम update_aem2_sensors(काष्ठा aem_data *data)
अणु
	पूर्णांक i;

	mutex_lock(&data->lock);
	अगर (समय_beक्रमe(jअगरfies, data->last_updated + REFRESH_INTERVAL) &&
	    data->valid)
		जाओ out;

	update_aem_energy(data);
	aem_पढ़ो_sensor(data, AEM_EXHAUST_ELEMENT, 0, &data->temp[0], 1);
	aem_पढ़ो_sensor(data, AEM_EXHAUST_ELEMENT, 1, &data->temp[1], 1);

	क्रम (i = POWER_CAP; i <= POWER_AUX; i++)
		aem_पढ़ो_sensor(data, AEM_POWER_CAP_ELEMENT, i,
				&data->pcap[i], 2);
out:
	mutex_unlock(&data->lock);
पूर्ण

/* Delete an AEM instance */
अटल व्योम aem_delete(काष्ठा aem_data *data)
अणु
	list_del(&data->list);
	aem_हटाओ_sensors(data);
	kमुक्त(data->rs_resp);
	hwmon_device_unरेजिस्टर(data->hwmon_dev);
	ipmi_destroy_user(data->ipmi.user);
	platक्रमm_set_drvdata(data->pdev, शून्य);
	platक्रमm_device_unरेजिस्टर(data->pdev);
	ida_simple_हटाओ(&aem_ida, data->id);
	kमुक्त(data);
पूर्ण

/* Probe functions क्रम AEM1 devices */

/* Retrieve version and module handle क्रम an AEM1 instance */
अटल पूर्णांक aem_find_aem1_count(काष्ठा aem_ipmi_data *data)
अणु
	पूर्णांक res;
	काष्ठा aem_find_firmware_req	ff_req;
	काष्ठा aem_find_firmware_resp	ff_resp;

	ff_req.id = प्रणाली_x_id;
	ff_req.index = 0;
	ff_req.module_type_id = cpu_to_be16(AEM_MODULE_TYPE_ID);

	data->tx_message.cmd = AEM_FIND_FW_CMD;
	data->tx_message.data = (अक्षर *)&ff_req;
	data->tx_message.data_len = माप(ff_req);

	data->rx_msg_data = &ff_resp;
	data->rx_msg_len = माप(ff_resp);

	aem_send_message(data);

	res = रुको_क्रम_completion_समयout(&data->पढ़ो_complete, IPMI_TIMEOUT);
	अगर (!res)
		वापस -ETIMEDOUT;

	अगर (data->rx_result || data->rx_msg_len != माप(ff_resp) ||
	    स_भेद(&ff_resp.id, &प्रणाली_x_id, माप(प्रणाली_x_id)))
		वापस -ENOENT;

	वापस ff_resp.num_instances;
पूर्ण

/* Find and initialize one AEM1 instance */
अटल पूर्णांक aem_init_aem1_inst(काष्ठा aem_ipmi_data *probe, u8 module_handle)
अणु
	काष्ठा aem_data *data;
	पूर्णांक i;
	पूर्णांक res = -ENOMEM;

	data = kzalloc(माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस res;
	mutex_init(&data->lock);

	/* Copy instance data */
	data->ver_major = 1;
	data->ver_minor = 0;
	data->module_handle = module_handle;
	क्रम (i = 0; i < AEM1_NUM_ENERGY_REGS; i++)
		data->घातer_period[i] = AEM_DEFAULT_POWER_INTERVAL;

	/* Create sub-device क्रम this fw instance */
	data->id = ida_simple_get(&aem_ida, 0, 0, GFP_KERNEL);
	अगर (data->id < 0)
		जाओ id_err;

	data->pdev = platक्रमm_device_alloc(DRVNAME, data->id);
	अगर (!data->pdev)
		जाओ dev_err;
	data->pdev->dev.driver = &aem_driver.driver;

	res = platक्रमm_device_add(data->pdev);
	अगर (res)
		जाओ ipmi_err;

	platक्रमm_set_drvdata(data->pdev, data);

	/* Set up IPMI पूर्णांकerface */
	res = aem_init_ipmi_data(&data->ipmi, probe->पूर्णांकerface,
				 probe->bmc_device);
	अगर (res)
		जाओ ipmi_err;

	/* Register with hwmon */
	data->hwmon_dev = hwmon_device_रेजिस्टर(&data->pdev->dev);
	अगर (IS_ERR(data->hwmon_dev)) अणु
		dev_err(&data->pdev->dev,
			"Unable to register hwmon device for IPMI interface %d\n",
			probe->पूर्णांकerface);
		res = PTR_ERR(data->hwmon_dev);
		जाओ hwmon_reg_err;
	पूर्ण

	data->update = update_aem1_sensors;
	data->rs_resp = kzalloc(माप(*(data->rs_resp)) + 8, GFP_KERNEL);
	अगर (!data->rs_resp) अणु
		res = -ENOMEM;
		जाओ alloc_resp_err;
	पूर्ण

	/* Find sensors */
	res = aem1_find_sensors(data);
	अगर (res)
		जाओ sensor_err;

	/* Add to our list of AEM devices */
	list_add_tail(&data->list, &driver_data.aem_devices);

	dev_info(data->ipmi.bmc_device, "Found AEM v%d.%d at 0x%X\n",
		 data->ver_major, data->ver_minor,
		 data->module_handle);
	वापस 0;

sensor_err:
	kमुक्त(data->rs_resp);
alloc_resp_err:
	hwmon_device_unरेजिस्टर(data->hwmon_dev);
hwmon_reg_err:
	ipmi_destroy_user(data->ipmi.user);
ipmi_err:
	platक्रमm_set_drvdata(data->pdev, शून्य);
	platक्रमm_device_unरेजिस्टर(data->pdev);
dev_err:
	ida_simple_हटाओ(&aem_ida, data->id);
id_err:
	kमुक्त(data);

	वापस res;
पूर्ण

/* Find and initialize all AEM1 instances */
अटल व्योम aem_init_aem1(काष्ठा aem_ipmi_data *probe)
अणु
	पूर्णांक num, i, err;

	num = aem_find_aem1_count(probe);
	क्रम (i = 0; i < num; i++) अणु
		err = aem_init_aem1_inst(probe, i);
		अगर (err) अणु
			dev_err(probe->bmc_device,
				"Error %d initializing AEM1 0x%X\n",
				err, i);
		पूर्ण
	पूर्ण
पूर्ण

/* Probe functions क्रम AEM2 devices */

/* Retrieve version and module handle क्रम an AEM2 instance */
अटल पूर्णांक aem_find_aem2(काष्ठा aem_ipmi_data *data,
			    काष्ठा aem_find_instance_resp *fi_resp,
			    पूर्णांक instance_num)
अणु
	पूर्णांक res;
	काष्ठा aem_find_instance_req fi_req;

	fi_req.id = प्रणाली_x_id;
	fi_req.instance_number = instance_num;
	fi_req.module_type_id = cpu_to_be16(AEM_MODULE_TYPE_ID);

	data->tx_message.cmd = AEM_FW_INSTANCE_CMD;
	data->tx_message.data = (अक्षर *)&fi_req;
	data->tx_message.data_len = माप(fi_req);

	data->rx_msg_data = fi_resp;
	data->rx_msg_len = माप(*fi_resp);

	aem_send_message(data);

	res = रुको_क्रम_completion_समयout(&data->पढ़ो_complete, IPMI_TIMEOUT);
	अगर (!res)
		वापस -ETIMEDOUT;

	अगर (data->rx_result || data->rx_msg_len != माप(*fi_resp) ||
	    स_भेद(&fi_resp->id, &प्रणाली_x_id, माप(प्रणाली_x_id)) ||
	    fi_resp->num_instances <= instance_num)
		वापस -ENOENT;

	वापस 0;
पूर्ण

/* Find and initialize one AEM2 instance */
अटल पूर्णांक aem_init_aem2_inst(काष्ठा aem_ipmi_data *probe,
			      काष्ठा aem_find_instance_resp *fi_resp)
अणु
	काष्ठा aem_data *data;
	पूर्णांक i;
	पूर्णांक res = -ENOMEM;

	data = kzalloc(माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस res;
	mutex_init(&data->lock);

	/* Copy instance data */
	data->ver_major = fi_resp->major;
	data->ver_minor = fi_resp->minor;
	data->module_handle = fi_resp->module_handle;
	क्रम (i = 0; i < AEM2_NUM_ENERGY_REGS; i++)
		data->घातer_period[i] = AEM_DEFAULT_POWER_INTERVAL;

	/* Create sub-device क्रम this fw instance */
	data->id = ida_simple_get(&aem_ida, 0, 0, GFP_KERNEL);
	अगर (data->id < 0)
		जाओ id_err;

	data->pdev = platक्रमm_device_alloc(DRVNAME, data->id);
	अगर (!data->pdev)
		जाओ dev_err;
	data->pdev->dev.driver = &aem_driver.driver;

	res = platक्रमm_device_add(data->pdev);
	अगर (res)
		जाओ ipmi_err;

	platक्रमm_set_drvdata(data->pdev, data);

	/* Set up IPMI पूर्णांकerface */
	res = aem_init_ipmi_data(&data->ipmi, probe->पूर्णांकerface,
				 probe->bmc_device);
	अगर (res)
		जाओ ipmi_err;

	/* Register with hwmon */
	data->hwmon_dev = hwmon_device_रेजिस्टर(&data->pdev->dev);
	अगर (IS_ERR(data->hwmon_dev)) अणु
		dev_err(&data->pdev->dev,
			"Unable to register hwmon device for IPMI interface %d\n",
			probe->पूर्णांकerface);
		res = PTR_ERR(data->hwmon_dev);
		जाओ hwmon_reg_err;
	पूर्ण

	data->update = update_aem2_sensors;
	data->rs_resp = kzalloc(माप(*(data->rs_resp)) + 8, GFP_KERNEL);
	अगर (!data->rs_resp) अणु
		res = -ENOMEM;
		जाओ alloc_resp_err;
	पूर्ण

	/* Find sensors */
	res = aem2_find_sensors(data);
	अगर (res)
		जाओ sensor_err;

	/* Add to our list of AEM devices */
	list_add_tail(&data->list, &driver_data.aem_devices);

	dev_info(data->ipmi.bmc_device, "Found AEM v%d.%d at 0x%X\n",
		 data->ver_major, data->ver_minor,
		 data->module_handle);
	वापस 0;

sensor_err:
	kमुक्त(data->rs_resp);
alloc_resp_err:
	hwmon_device_unरेजिस्टर(data->hwmon_dev);
hwmon_reg_err:
	ipmi_destroy_user(data->ipmi.user);
ipmi_err:
	platक्रमm_set_drvdata(data->pdev, शून्य);
	platक्रमm_device_unरेजिस्टर(data->pdev);
dev_err:
	ida_simple_हटाओ(&aem_ida, data->id);
id_err:
	kमुक्त(data);

	वापस res;
पूर्ण

/* Find and initialize all AEM2 instances */
अटल व्योम aem_init_aem2(काष्ठा aem_ipmi_data *probe)
अणु
	काष्ठा aem_find_instance_resp fi_resp;
	पूर्णांक err;
	पूर्णांक i = 0;

	जबतक (!aem_find_aem2(probe, &fi_resp, i)) अणु
		अगर (fi_resp.major != 2) अणु
			dev_err(probe->bmc_device,
				"Unknown AEM v%d; please report this to the maintainer.\n",
				fi_resp.major);
			i++;
			जारी;
		पूर्ण
		err = aem_init_aem2_inst(probe, &fi_resp);
		अगर (err) अणु
			dev_err(probe->bmc_device,
				"Error %d initializing AEM2 0x%X\n",
				err, fi_resp.module_handle);
		पूर्ण
		i++;
	पूर्ण
पूर्ण

/* Probe a BMC क्रम AEM firmware instances */
अटल व्योम aem_रेजिस्टर_bmc(पूर्णांक अगरace, काष्ठा device *dev)
अणु
	काष्ठा aem_ipmi_data probe;

	अगर (aem_init_ipmi_data(&probe, अगरace, dev))
		वापस;

	/* Ignore probe errors; they won't cause problems */
	aem_init_aem1(&probe);
	aem_init_aem2(&probe);

	ipmi_destroy_user(probe.user);
पूर्ण

/* Handle BMC deletion */
अटल व्योम aem_bmc_gone(पूर्णांक अगरace)
अणु
	काष्ठा aem_data *p1, *next1;

	list_क्रम_each_entry_safe(p1, next1, &driver_data.aem_devices, list)
		अगर (p1->ipmi.पूर्णांकerface == अगरace)
			aem_delete(p1);
पूर्ण

/* sysfs support functions */

/* AEM device name */
अटल sमाप_प्रकार name_show(काष्ठा device *dev, काष्ठा device_attribute *devattr,
			 अक्षर *buf)
अणु
	काष्ठा aem_data *data = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%s%d\n", DRVNAME, data->ver_major);
पूर्ण
अटल SENSOR_DEVICE_ATTR_RO(name, name, 0);

/* AEM device version */
अटल sमाप_प्रकार version_show(काष्ठा device *dev,
			    काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	काष्ठा aem_data *data = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%d.%d\n", data->ver_major, data->ver_minor);
पूर्ण
अटल SENSOR_DEVICE_ATTR_RO(version, version, 0);

/* Display घातer use */
अटल sमाप_प्रकार aem_show_घातer(काष्ठा device *dev,
			      काष्ठा device_attribute *devattr,
			      अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	काष्ठा aem_data *data = dev_get_drvdata(dev);
	u64 beक्रमe, after, delta, समय;
	चिन्हित दीर्घ leftover;

	mutex_lock(&data->lock);
	update_aem_energy_one(data, attr->index);
	समय = kसमय_get_ns();
	beक्रमe = data->energy[attr->index];

	leftover = schedule_समयout_पूर्णांकerruptible(
			msecs_to_jअगरfies(data->घातer_period[attr->index])
		   );
	अगर (leftover) अणु
		mutex_unlock(&data->lock);
		वापस 0;
	पूर्ण

	update_aem_energy_one(data, attr->index);
	समय = kसमय_get_ns() - समय;
	after = data->energy[attr->index];
	mutex_unlock(&data->lock);

	delta = (after - beक्रमe) * UJ_PER_MJ;

	वापस प्र_लिखो(buf, "%llu\n",
		(अचिन्हित दीर्घ दीर्घ)भाग64_u64(delta * NSEC_PER_SEC, समय));
पूर्ण

/* Display energy use */
अटल sमाप_प्रकार aem_show_energy(काष्ठा device *dev,
			       काष्ठा device_attribute *devattr,
			       अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	काष्ठा aem_data *a = dev_get_drvdata(dev);
	mutex_lock(&a->lock);
	update_aem_energy_one(a, attr->index);
	mutex_unlock(&a->lock);

	वापस प्र_लिखो(buf, "%llu\n",
			(अचिन्हित दीर्घ दीर्घ)a->energy[attr->index] * 1000);
पूर्ण

/* Display घातer पूर्णांकerval रेजिस्टरs */
अटल sमाप_प्रकार aem_show_घातer_period(काष्ठा device *dev,
				     काष्ठा device_attribute *devattr,
				     अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	काष्ठा aem_data *a = dev_get_drvdata(dev);
	a->update(a);

	वापस प्र_लिखो(buf, "%lu\n", a->घातer_period[attr->index]);
पूर्ण

/* Set घातer पूर्णांकerval रेजिस्टरs */
अटल sमाप_प्रकार aem_set_घातer_period(काष्ठा device *dev,
				    काष्ठा device_attribute *devattr,
				    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	काष्ठा aem_data *a = dev_get_drvdata(dev);
	अचिन्हित दीर्घ temp;
	पूर्णांक res;

	res = kम_से_अदीर्घ(buf, 10, &temp);
	अगर (res)
		वापस res;

	अगर (temp < AEM_MIN_POWER_INTERVAL)
		वापस -EINVAL;

	mutex_lock(&a->lock);
	a->घातer_period[attr->index] = temp;
	mutex_unlock(&a->lock);

	वापस count;
पूर्ण

/* Discover sensors on an AEM device */
अटल पूर्णांक aem_रेजिस्टर_sensors(काष्ठा aem_data *data,
				स्थिर काष्ठा aem_ro_sensor_ढाँचा *ro,
				स्थिर काष्ठा aem_rw_sensor_ढाँचा *rw)
अणु
	काष्ठा device *dev = &data->pdev->dev;
	काष्ठा sensor_device_attribute *sensors = data->sensors;
	पूर्णांक err;

	/* Set up पढ़ो-only sensors */
	जबतक (ro->label) अणु
		sysfs_attr_init(&sensors->dev_attr.attr);
		sensors->dev_attr.attr.name = ro->label;
		sensors->dev_attr.attr.mode = 0444;
		sensors->dev_attr.show = ro->show;
		sensors->index = ro->index;

		err = device_create_file(dev, &sensors->dev_attr);
		अगर (err) अणु
			sensors->dev_attr.attr.name = शून्य;
			जाओ error;
		पूर्ण
		sensors++;
		ro++;
	पूर्ण

	/* Set up पढ़ो-ग_लिखो sensors */
	जबतक (rw->label) अणु
		sysfs_attr_init(&sensors->dev_attr.attr);
		sensors->dev_attr.attr.name = rw->label;
		sensors->dev_attr.attr.mode = 0644;
		sensors->dev_attr.show = rw->show;
		sensors->dev_attr.store = rw->set;
		sensors->index = rw->index;

		err = device_create_file(dev, &sensors->dev_attr);
		अगर (err) अणु
			sensors->dev_attr.attr.name = शून्य;
			जाओ error;
		पूर्ण
		sensors++;
		rw++;
	पूर्ण

	err = device_create_file(dev, &sensor_dev_attr_name.dev_attr);
	अगर (err)
		जाओ error;
	err = device_create_file(dev, &sensor_dev_attr_version.dev_attr);
	वापस err;

error:
	aem_हटाओ_sensors(data);
	वापस err;
पूर्ण

/* sysfs support functions क्रम AEM2 sensors */

/* Display temperature use */
अटल sमाप_प्रकार aem2_show_temp(काष्ठा device *dev,
			      काष्ठा device_attribute *devattr,
			      अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	काष्ठा aem_data *a = dev_get_drvdata(dev);
	a->update(a);

	वापस प्र_लिखो(buf, "%u\n", a->temp[attr->index] * 1000);
पूर्ण

/* Display घातer-capping रेजिस्टरs */
अटल sमाप_प्रकार aem2_show_pcap_value(काष्ठा device *dev,
				    काष्ठा device_attribute *devattr,
				    अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	काष्ठा aem_data *a = dev_get_drvdata(dev);
	a->update(a);

	वापस प्र_लिखो(buf, "%u\n", a->pcap[attr->index] * 100000);
पूर्ण

/* Remove sensors attached to an AEM device */
अटल व्योम aem_हटाओ_sensors(काष्ठा aem_data *data)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < AEM_NUM_SENSORS; i++) अणु
		अगर (!data->sensors[i].dev_attr.attr.name)
			जारी;
		device_हटाओ_file(&data->pdev->dev,
				   &data->sensors[i].dev_attr);
	पूर्ण

	device_हटाओ_file(&data->pdev->dev,
			   &sensor_dev_attr_name.dev_attr);
	device_हटाओ_file(&data->pdev->dev,
			   &sensor_dev_attr_version.dev_attr);
पूर्ण

/* Sensor probe functions */

/* Description of AEM1 sensors */
अटल स्थिर काष्ठा aem_ro_sensor_ढाँचा aem1_ro_sensors[] = अणु
अणु"energy1_input",  aem_show_energy, 0पूर्ण,
अणु"power1_average", aem_show_घातer,  0पूर्ण,
अणुशून्य,		   शून्य,	    0पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा aem_rw_sensor_ढाँचा aem1_rw_sensors[] = अणु
अणु"power1_average_interval", aem_show_घातer_period, aem_set_घातer_period, 0पूर्ण,
अणुशून्य,			    शून्य,                  शून्य,                 0पूर्ण,
पूर्ण;

/* Description of AEM2 sensors */
अटल स्थिर काष्ठा aem_ro_sensor_ढाँचा aem2_ro_sensors[] = अणु
अणु"energy1_input",	  aem_show_energy,	0पूर्ण,
अणु"energy2_input",	  aem_show_energy,	1पूर्ण,
अणु"power1_average",	  aem_show_घातer,	0पूर्ण,
अणु"power2_average",	  aem_show_घातer,	1पूर्ण,
अणु"temp1_input",		  aem2_show_temp,	0पूर्ण,
अणु"temp2_input",		  aem2_show_temp,	1पूर्ण,

अणु"power4_average",	  aem2_show_pcap_value,	POWER_CAP_MAX_HOTPLUGपूर्ण,
अणु"power5_average",	  aem2_show_pcap_value,	POWER_CAP_MAXपूर्ण,
अणु"power6_average",	  aem2_show_pcap_value,	POWER_CAP_MIN_WARNINGपूर्ण,
अणु"power7_average",	  aem2_show_pcap_value,	POWER_CAP_MINपूर्ण,

अणु"power3_average",	  aem2_show_pcap_value,	POWER_AUXपूर्ण,
अणु"power_cap",		  aem2_show_pcap_value,	POWER_CAPपूर्ण,
अणुशून्य,                    शून्य,                 0पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा aem_rw_sensor_ढाँचा aem2_rw_sensors[] = अणु
अणु"power1_average_interval", aem_show_घातer_period, aem_set_घातer_period, 0पूर्ण,
अणु"power2_average_interval", aem_show_घातer_period, aem_set_घातer_period, 1पूर्ण,
अणुशून्य,			    शून्य,                  शून्य,                 0पूर्ण,
पूर्ण;

/* Set up AEM1 sensor attrs */
अटल पूर्णांक aem1_find_sensors(काष्ठा aem_data *data)
अणु
	वापस aem_रेजिस्टर_sensors(data, aem1_ro_sensors, aem1_rw_sensors);
पूर्ण

/* Set up AEM2 sensor attrs */
अटल पूर्णांक aem2_find_sensors(काष्ठा aem_data *data)
अणु
	वापस aem_रेजिस्टर_sensors(data, aem2_ro_sensors, aem2_rw_sensors);
पूर्ण

/* Module init/निकास routines */

अटल पूर्णांक __init aem_init(व्योम)
अणु
	पूर्णांक res;

	res = driver_रेजिस्टर(&aem_driver.driver);
	अगर (res) अणु
		pr_err("Can't register aem driver\n");
		वापस res;
	पूर्ण

	res = ipmi_smi_watcher_रेजिस्टर(&driver_data.bmc_events);
	अगर (res)
		जाओ ipmi_reg_err;
	वापस 0;

ipmi_reg_err:
	driver_unरेजिस्टर(&aem_driver.driver);
	वापस res;

पूर्ण

अटल व्योम __निकास aem_निकास(व्योम)
अणु
	काष्ठा aem_data *p1, *next1;

	ipmi_smi_watcher_unरेजिस्टर(&driver_data.bmc_events);
	driver_unरेजिस्टर(&aem_driver.driver);
	list_क्रम_each_entry_safe(p1, next1, &driver_data.aem_devices, list)
		aem_delete(p1);
पूर्ण

MODULE_AUTHOR("Darrick J. Wong <darrick.wong@oracle.com>");
MODULE_DESCRIPTION("IBM AEM power/temp/energy sensor driver");
MODULE_LICENSE("GPL");

module_init(aem_init);
module_निकास(aem_निकास);

MODULE_ALIAS("dmi:bvnIBM:*:pnIBMSystemx3350-*");
MODULE_ALIAS("dmi:bvnIBM:*:pnIBMSystemx3550-*");
MODULE_ALIAS("dmi:bvnIBM:*:pnIBMSystemx3650-*");
MODULE_ALIAS("dmi:bvnIBM:*:pnIBMSystemx3655-*");
MODULE_ALIAS("dmi:bvnIBM:*:pnIBMSystemx3755-*");
MODULE_ALIAS("dmi:bvnIBM:*:pnIBM3850M2/x3950M2-*");
MODULE_ALIAS("dmi:bvnIBM:*:pnIBMBladeHC10-*");
