<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Power supply driver क्रम ChromeOS EC based USB PD Charger.
 *
 * Copyright (c) 2014 - 2018 Google, Inc
 */

#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_data/cros_ec_commands.h>
#समावेश <linux/platक्रमm_data/cros_ec_proto.h>
#समावेश <linux/platक्रमm_data/cros_usbpd_notअगरy.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/घातer_supply.h>
#समावेश <linux/slab.h>

#घोषणा CHARGER_USBPD_सूची_NAME			"CROS_USBPD_CHARGER%d"
#घोषणा CHARGER_DEDICATED_सूची_NAME		"CROS_DEDICATED_CHARGER"
#घोषणा CHARGER_सूची_NAME_LENGTH		(माप(CHARGER_USBPD_सूची_NAME) >= \
					 माप(CHARGER_DEDICATED_सूची_NAME) ? \
					 माप(CHARGER_USBPD_सूची_NAME) : \
					 माप(CHARGER_DEDICATED_सूची_NAME))
#घोषणा CHARGER_CACHE_UPDATE_DELAY		msecs_to_jअगरfies(500)
#घोषणा CHARGER_MANUFACTURER_MODEL_LENGTH	32

#घोषणा DRV_NAME "cros-usbpd-charger"

काष्ठा port_data अणु
	पूर्णांक port_number;
	अक्षर name[CHARGER_सूची_NAME_LENGTH];
	अक्षर manufacturer[CHARGER_MANUFACTURER_MODEL_LENGTH];
	अक्षर model_name[CHARGER_MANUFACTURER_MODEL_LENGTH];
	काष्ठा घातer_supply *psy;
	काष्ठा घातer_supply_desc psy_desc;
	पूर्णांक psy_usb_type;
	पूर्णांक psy_online;
	पूर्णांक psy_status;
	पूर्णांक psy_current_max;
	पूर्णांक psy_voltage_max_design;
	पूर्णांक psy_voltage_now;
	पूर्णांक psy_घातer_max;
	काष्ठा अक्षरger_data *अक्षरger;
	अचिन्हित दीर्घ last_update;
पूर्ण;

काष्ठा अक्षरger_data अणु
	काष्ठा device *dev;
	काष्ठा cros_ec_dev *ec_dev;
	काष्ठा cros_ec_device *ec_device;
	पूर्णांक num_अक्षरger_ports;
	पूर्णांक num_usbpd_ports;
	पूर्णांक num_रेजिस्टरed_psy;
	काष्ठा port_data *ports[EC_USB_PD_MAX_PORTS];
	काष्ठा notअगरier_block notअगरier;
पूर्ण;

अटल क्रमागत घातer_supply_property cros_usbpd_अक्षरger_props[] = अणु
	POWER_SUPPLY_PROP_INPUT_CURRENT_LIMIT,
	POWER_SUPPLY_PROP_INPUT_VOLTAGE_LIMIT,
	POWER_SUPPLY_PROP_ONLINE,
	POWER_SUPPLY_PROP_STATUS,
	POWER_SUPPLY_PROP_CURRENT_MAX,
	POWER_SUPPLY_PROP_VOLTAGE_MAX_DESIGN,
	POWER_SUPPLY_PROP_VOLTAGE_NOW,
	POWER_SUPPLY_PROP_MODEL_NAME,
	POWER_SUPPLY_PROP_MANUFACTURER,
	POWER_SUPPLY_PROP_USB_TYPE
पूर्ण;

अटल क्रमागत घातer_supply_property cros_usbpd_dedicated_अक्षरger_props[] = अणु
	POWER_SUPPLY_PROP_ONLINE,
	POWER_SUPPLY_PROP_STATUS,
	POWER_SUPPLY_PROP_VOLTAGE_NOW,
पूर्ण;

अटल क्रमागत घातer_supply_usb_type cros_usbpd_अक्षरger_usb_types[] = अणु
	POWER_SUPPLY_USB_TYPE_UNKNOWN,
	POWER_SUPPLY_USB_TYPE_SDP,
	POWER_SUPPLY_USB_TYPE_DCP,
	POWER_SUPPLY_USB_TYPE_CDP,
	POWER_SUPPLY_USB_TYPE_C,
	POWER_SUPPLY_USB_TYPE_PD,
	POWER_SUPPLY_USB_TYPE_PD_DRP,
	POWER_SUPPLY_USB_TYPE_APPLE_BRICK_ID
पूर्ण;

/* Input voltage/current limit in mV/mA. Default to none. */
अटल u16 input_voltage_limit = EC_POWER_LIMIT_NONE;
अटल u16 input_current_limit = EC_POWER_LIMIT_NONE;

अटल bool cros_usbpd_अक्षरger_port_is_dedicated(काष्ठा port_data *port)
अणु
	वापस port->port_number >= port->अक्षरger->num_usbpd_ports;
पूर्ण

अटल पूर्णांक cros_usbpd_अक्षरger_ec_command(काष्ठा अक्षरger_data *अक्षरger,
					 अचिन्हित पूर्णांक version,
					 अचिन्हित पूर्णांक command,
					 व्योम *outdata,
					 अचिन्हित पूर्णांक outsize,
					 व्योम *indata,
					 अचिन्हित पूर्णांक insize)
अणु
	काष्ठा cros_ec_dev *ec_dev = अक्षरger->ec_dev;
	काष्ठा cros_ec_command *msg;
	पूर्णांक ret;

	msg = kzalloc(माप(*msg) + max(outsize, insize), GFP_KERNEL);
	अगर (!msg)
		वापस -ENOMEM;

	msg->version = version;
	msg->command = ec_dev->cmd_offset + command;
	msg->outsize = outsize;
	msg->insize = insize;

	अगर (outsize)
		स_नकल(msg->data, outdata, outsize);

	ret = cros_ec_cmd_xfer_status(अक्षरger->ec_device, msg);
	अगर (ret >= 0 && insize)
		स_नकल(indata, msg->data, insize);

	kमुक्त(msg);
	वापस ret;
पूर्ण

अटल पूर्णांक cros_usbpd_अक्षरger_get_num_ports(काष्ठा अक्षरger_data *अक्षरger)
अणु
	काष्ठा ec_response_अक्षरge_port_count resp;
	पूर्णांक ret;

	ret = cros_usbpd_अक्षरger_ec_command(अक्षरger, 0,
					    EC_CMD_CHARGE_PORT_COUNT,
					    शून्य, 0, &resp, माप(resp));
	अगर (ret < 0)
		वापस ret;

	वापस resp.port_count;
पूर्ण

अटल पूर्णांक cros_usbpd_अक्षरger_get_usbpd_num_ports(काष्ठा अक्षरger_data *अक्षरger)
अणु
	काष्ठा ec_response_usb_pd_ports resp;
	पूर्णांक ret;

	ret = cros_usbpd_अक्षरger_ec_command(अक्षरger, 0, EC_CMD_USB_PD_PORTS,
					    शून्य, 0, &resp, माप(resp));
	अगर (ret < 0)
		वापस ret;

	वापस resp.num_ports;
पूर्ण

अटल पूर्णांक cros_usbpd_अक्षरger_get_discovery_info(काष्ठा port_data *port)
अणु
	काष्ठा अक्षरger_data *अक्षरger = port->अक्षरger;
	काष्ठा ec_params_usb_pd_discovery_entry resp;
	काष्ठा ec_params_usb_pd_info_request req;
	पूर्णांक ret;

	req.port = port->port_number;

	ret = cros_usbpd_अक्षरger_ec_command(अक्षरger, 0,
					    EC_CMD_USB_PD_DISCOVERY,
					    &req, माप(req),
					    &resp, माप(resp));
	अगर (ret < 0) अणु
		dev_err(अक्षरger->dev,
			"Unable to query discovery info (err:0x%x)\n", ret);
		वापस ret;
	पूर्ण

	dev_dbg(अक्षरger->dev, "Port %d: VID = 0x%x, PID=0x%x, PTYPE=0x%x\n",
		port->port_number, resp.vid, resp.pid, resp.ptype);

	snम_लिखो(port->manufacturer, माप(port->manufacturer), "%x",
		 resp.vid);
	snम_लिखो(port->model_name, माप(port->model_name), "%x", resp.pid);

	वापस 0;
पूर्ण

अटल पूर्णांक cros_usbpd_अक्षरger_get_घातer_info(काष्ठा port_data *port)
अणु
	काष्ठा अक्षरger_data *अक्षरger = port->अक्षरger;
	काष्ठा ec_response_usb_pd_घातer_info resp;
	काष्ठा ec_params_usb_pd_घातer_info req;
	पूर्णांक last_psy_status, last_psy_usb_type;
	काष्ठा device *dev = अक्षरger->dev;
	पूर्णांक ret;

	req.port = port->port_number;
	ret = cros_usbpd_अक्षरger_ec_command(अक्षरger, 0,
					    EC_CMD_USB_PD_POWER_INFO,
					    &req, माप(req),
					    &resp, माप(resp));
	अगर (ret < 0) अणु
		dev_err(dev, "Unable to query PD power info (err:0x%x)\n", ret);
		वापस ret;
	पूर्ण

	last_psy_status = port->psy_status;
	last_psy_usb_type = port->psy_usb_type;

	चयन (resp.role) अणु
	हाल USB_PD_PORT_POWER_DISCONNECTED:
		port->psy_status = POWER_SUPPLY_STATUS_NOT_CHARGING;
		port->psy_online = 0;
		अवरोध;
	हाल USB_PD_PORT_POWER_SOURCE:
		port->psy_status = POWER_SUPPLY_STATUS_NOT_CHARGING;
		port->psy_online = 0;
		अवरोध;
	हाल USB_PD_PORT_POWER_SINK:
		port->psy_status = POWER_SUPPLY_STATUS_CHARGING;
		port->psy_online = 1;
		अवरोध;
	हाल USB_PD_PORT_POWER_SINK_NOT_CHARGING:
		port->psy_status = POWER_SUPPLY_STATUS_NOT_CHARGING;
		port->psy_online = 1;
		अवरोध;
	शेष:
		dev_err(dev, "Unknown role %d\n", resp.role);
		अवरोध;
	पूर्ण

	port->psy_voltage_max_design = resp.meas.voltage_max;
	port->psy_voltage_now = resp.meas.voltage_now;
	port->psy_current_max = resp.meas.current_max;
	port->psy_घातer_max = resp.max_घातer;

	चयन (resp.type) अणु
	हाल USB_CHG_TYPE_BC12_SDP:
	हाल USB_CHG_TYPE_VBUS:
		port->psy_usb_type = POWER_SUPPLY_USB_TYPE_SDP;
		अवरोध;
	हाल USB_CHG_TYPE_NONE:
		/*
		 * For dual-role devices when we are a source, the firmware
		 * reports the type as NONE. Report such अक्षरgers as type
		 * USB_PD_DRP.
		 */
		अगर (resp.role == USB_PD_PORT_POWER_SOURCE && resp.dualrole)
			port->psy_usb_type = POWER_SUPPLY_USB_TYPE_PD_DRP;
		अन्यथा
			port->psy_usb_type = POWER_SUPPLY_USB_TYPE_SDP;
		अवरोध;
	हाल USB_CHG_TYPE_OTHER:
	हाल USB_CHG_TYPE_PROPRIETARY:
		port->psy_usb_type = POWER_SUPPLY_USB_TYPE_APPLE_BRICK_ID;
		अवरोध;
	हाल USB_CHG_TYPE_C:
		port->psy_usb_type = POWER_SUPPLY_USB_TYPE_C;
		अवरोध;
	हाल USB_CHG_TYPE_BC12_DCP:
		port->psy_usb_type = POWER_SUPPLY_USB_TYPE_DCP;
		अवरोध;
	हाल USB_CHG_TYPE_BC12_CDP:
		port->psy_usb_type = POWER_SUPPLY_USB_TYPE_CDP;
		अवरोध;
	हाल USB_CHG_TYPE_PD:
		अगर (resp.dualrole)
			port->psy_usb_type = POWER_SUPPLY_USB_TYPE_PD_DRP;
		अन्यथा
			port->psy_usb_type = POWER_SUPPLY_USB_TYPE_PD;
		अवरोध;
	हाल USB_CHG_TYPE_UNKNOWN:
		/*
		 * While the EC is trying to determine the type of अक्षरger that
		 * has been plugged in, it will report the अक्षरger type as
		 * unknown. Additionally since the घातer capabilities are
		 * unknown, report the max current and voltage as zero.
		 */
		port->psy_usb_type = POWER_SUPPLY_USB_TYPE_UNKNOWN;
		port->psy_voltage_max_design = 0;
		port->psy_current_max = 0;
		अवरोध;
	शेष:
		dev_err(dev, "Port %d: default case!\n", port->port_number);
		port->psy_usb_type = POWER_SUPPLY_USB_TYPE_SDP;
	पूर्ण

	अगर (cros_usbpd_अक्षरger_port_is_dedicated(port))
		port->psy_desc.type = POWER_SUPPLY_TYPE_MAINS;
	अन्यथा
		port->psy_desc.type = POWER_SUPPLY_TYPE_USB;

	dev_dbg(dev,
		"Port %d: type=%d vmax=%d vnow=%d cmax=%d clim=%d pmax=%d\n",
		port->port_number, resp.type, resp.meas.voltage_max,
		resp.meas.voltage_now, resp.meas.current_max,
		resp.meas.current_lim, resp.max_घातer);

	/*
	 * If घातer supply type or status changed, explicitly call
	 * घातer_supply_changed. This results in udev event getting generated
	 * and allows user mode apps to react quicker instead of रुकोing क्रम
	 * their next poll of घातer supply status.
	 */
	अगर (last_psy_usb_type != port->psy_usb_type ||
	    last_psy_status != port->psy_status)
		घातer_supply_changed(port->psy);

	वापस 0;
पूर्ण

अटल पूर्णांक cros_usbpd_अक्षरger_get_port_status(काष्ठा port_data *port,
					      bool ratelimit)
अणु
	पूर्णांक ret;

	अगर (ratelimit &&
	    समय_is_after_jअगरfies(port->last_update +
				  CHARGER_CACHE_UPDATE_DELAY))
		वापस 0;

	ret = cros_usbpd_अक्षरger_get_घातer_info(port);
	अगर (ret < 0)
		वापस ret;

	अगर (!cros_usbpd_अक्षरger_port_is_dedicated(port))
		ret = cros_usbpd_अक्षरger_get_discovery_info(port);
	port->last_update = jअगरfies;

	वापस ret;
पूर्ण

अटल पूर्णांक cros_usbpd_अक्षरger_set_ext_घातer_limit(काष्ठा अक्षरger_data *अक्षरger,
						  u16 current_lim,
						  u16 voltage_lim)
अणु
	काष्ठा ec_params_बाह्यal_घातer_limit_v1 req;
	पूर्णांक ret;

	req.current_lim = current_lim;
	req.voltage_lim = voltage_lim;

	ret = cros_usbpd_अक्षरger_ec_command(अक्षरger, 0,
					    EC_CMD_EXTERNAL_POWER_LIMIT,
					    &req, माप(req), शून्य, 0);
	अगर (ret < 0)
		dev_err(अक्षरger->dev,
			"Unable to set the 'External Power Limit': %d\n", ret);

	वापस ret;
पूर्ण

अटल व्योम cros_usbpd_अक्षरger_घातer_changed(काष्ठा घातer_supply *psy)
अणु
	काष्ठा port_data *port = घातer_supply_get_drvdata(psy);
	काष्ठा अक्षरger_data *अक्षरger = port->अक्षरger;
	पूर्णांक i;

	क्रम (i = 0; i < अक्षरger->num_रेजिस्टरed_psy; i++)
		cros_usbpd_अक्षरger_get_port_status(अक्षरger->ports[i], false);
पूर्ण

अटल पूर्णांक cros_usbpd_अक्षरger_get_prop(काष्ठा घातer_supply *psy,
				       क्रमागत घातer_supply_property psp,
				       जोड़ घातer_supply_propval *val)
अणु
	काष्ठा port_data *port = घातer_supply_get_drvdata(psy);
	काष्ठा अक्षरger_data *अक्षरger = port->अक्षरger;
	काष्ठा cros_ec_device *ec_device = अक्षरger->ec_device;
	काष्ठा device *dev = अक्षरger->dev;
	पूर्णांक ret;

	/* Only refresh ec_port_status क्रम dynamic properties */
	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_ONLINE:
		/*
		 * If mkbp_event_supported, then we can be assured that
		 * the driver's state क्रम the online property is consistent
		 * with the hardware. However, अगर we aren't event driven,
		 * the optimization beक्रमe to skip an ec_port_status get
		 * and only वापसed cached values of the online property will
		 * cause a delay in detecting a cable attach until one of the
		 * other properties are पढ़ो.
		 *
		 * Allow an ec_port_status refresh क्रम online property check
		 * अगर we're not alपढ़ोy online to check क्रम plug events अगर
		 * not mkbp_event_supported.
		 */
		अगर (ec_device->mkbp_event_supported || port->psy_online)
			अवरोध;
		fallthrough;
	हाल POWER_SUPPLY_PROP_CURRENT_MAX:
	हाल POWER_SUPPLY_PROP_VOLTAGE_MAX_DESIGN:
	हाल POWER_SUPPLY_PROP_VOLTAGE_NOW:
		ret = cros_usbpd_अक्षरger_get_port_status(port, true);
		अगर (ret < 0) अणु
			dev_err(dev, "Failed to get port status (err:0x%x)\n",
				ret);
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_ONLINE:
		val->पूर्णांकval = port->psy_online;
		अवरोध;
	हाल POWER_SUPPLY_PROP_STATUS:
		val->पूर्णांकval = port->psy_status;
		अवरोध;
	हाल POWER_SUPPLY_PROP_CURRENT_MAX:
		val->पूर्णांकval = port->psy_current_max * 1000;
		अवरोध;
	हाल POWER_SUPPLY_PROP_VOLTAGE_MAX_DESIGN:
		val->पूर्णांकval = port->psy_voltage_max_design * 1000;
		अवरोध;
	हाल POWER_SUPPLY_PROP_VOLTAGE_NOW:
		val->पूर्णांकval = port->psy_voltage_now * 1000;
		अवरोध;
	हाल POWER_SUPPLY_PROP_USB_TYPE:
		val->पूर्णांकval = port->psy_usb_type;
		अवरोध;
	हाल POWER_SUPPLY_PROP_INPUT_CURRENT_LIMIT:
		अगर (input_current_limit == EC_POWER_LIMIT_NONE)
			val->पूर्णांकval = -1;
		अन्यथा
			val->पूर्णांकval = input_current_limit * 1000;
		अवरोध;
	हाल POWER_SUPPLY_PROP_INPUT_VOLTAGE_LIMIT:
		अगर (input_voltage_limit == EC_POWER_LIMIT_NONE)
			val->पूर्णांकval = -1;
		अन्यथा
			val->पूर्णांकval = input_voltage_limit * 1000;
		अवरोध;
	हाल POWER_SUPPLY_PROP_MODEL_NAME:
		val->strval = port->model_name;
		अवरोध;
	हाल POWER_SUPPLY_PROP_MANUFACTURER:
		val->strval = port->manufacturer;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cros_usbpd_अक्षरger_set_prop(काष्ठा घातer_supply *psy,
				       क्रमागत घातer_supply_property psp,
				       स्थिर जोड़ घातer_supply_propval *val)
अणु
	काष्ठा port_data *port = घातer_supply_get_drvdata(psy);
	काष्ठा अक्षरger_data *अक्षरger = port->अक्षरger;
	काष्ठा device *dev = अक्षरger->dev;
	u16 पूर्णांकval;
	पूर्णांक ret;

	/* U16_MAX in mV/mA is the maximum supported value */
	अगर (val->पूर्णांकval >= U16_MAX * 1000)
		वापस -EINVAL;
	/* A negative number is used to clear the limit */
	अगर (val->पूर्णांकval < 0)
		पूर्णांकval = EC_POWER_LIMIT_NONE;
	अन्यथा	/* Convert from uA/uV to mA/mV */
		पूर्णांकval = val->पूर्णांकval / 1000;

	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_INPUT_CURRENT_LIMIT:
		ret = cros_usbpd_अक्षरger_set_ext_घातer_limit(अक्षरger, पूर्णांकval,
							input_voltage_limit);
		अगर (ret < 0)
			अवरोध;

		input_current_limit = पूर्णांकval;
		अगर (input_current_limit == EC_POWER_LIMIT_NONE)
			dev_info(dev,
			  "External Current Limit cleared for all ports\n");
		अन्यथा
			dev_info(dev,
			  "External Current Limit set to %dmA for all ports\n",
			  input_current_limit);
		अवरोध;
	हाल POWER_SUPPLY_PROP_INPUT_VOLTAGE_LIMIT:
		ret = cros_usbpd_अक्षरger_set_ext_घातer_limit(अक्षरger,
							input_current_limit,
							पूर्णांकval);
		अगर (ret < 0)
			अवरोध;

		input_voltage_limit = पूर्णांकval;
		अगर (input_voltage_limit == EC_POWER_LIMIT_NONE)
			dev_info(dev,
			  "External Voltage Limit cleared for all ports\n");
		अन्यथा
			dev_info(dev,
			  "External Voltage Limit set to %dmV for all ports\n",
			  input_voltage_limit);
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक cros_usbpd_अक्षरger_property_is_ग_लिखोable(काष्ठा घातer_supply *psy,
						क्रमागत घातer_supply_property psp)
अणु
	पूर्णांक ret;

	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_INPUT_CURRENT_LIMIT:
	हाल POWER_SUPPLY_PROP_INPUT_VOLTAGE_LIMIT:
		ret = 1;
		अवरोध;
	शेष:
		ret = 0;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक cros_usbpd_अक्षरger_ec_event(काष्ठा notअगरier_block *nb,
				       अचिन्हित दीर्घ host_event,
				       व्योम *_notअगरy)
अणु
	काष्ठा अक्षरger_data *अक्षरger = container_of(nb, काष्ठा अक्षरger_data,
						    notअगरier);

	cros_usbpd_अक्षरger_घातer_changed(अक्षरger->ports[0]->psy);
	वापस NOTIFY_OK;
पूर्ण

अटल व्योम cros_usbpd_अक्षरger_unरेजिस्टर_notअगरier(व्योम *data)
अणु
	काष्ठा अक्षरger_data *अक्षरger = data;

	cros_usbpd_unरेजिस्टर_notअगरy(&अक्षरger->notअगरier);
पूर्ण

अटल पूर्णांक cros_usbpd_अक्षरger_probe(काष्ठा platक्रमm_device *pd)
अणु
	काष्ठा cros_ec_dev *ec_dev = dev_get_drvdata(pd->dev.parent);
	काष्ठा cros_ec_device *ec_device = ec_dev->ec_dev;
	काष्ठा घातer_supply_desc *psy_desc;
	काष्ठा device *dev = &pd->dev;
	काष्ठा अक्षरger_data *अक्षरger;
	काष्ठा घातer_supply *psy;
	काष्ठा port_data *port;
	पूर्णांक ret = -EINVAL;
	पूर्णांक i;

	अक्षरger = devm_kzalloc(dev, माप(काष्ठा अक्षरger_data),
			       GFP_KERNEL);
	अगर (!अक्षरger)
		वापस -ENOMEM;

	अक्षरger->dev = dev;
	अक्षरger->ec_dev = ec_dev;
	अक्षरger->ec_device = ec_device;

	platक्रमm_set_drvdata(pd, अक्षरger);

	/*
	 * We need to know the number of USB PD ports in order to know whether
	 * there is a dedicated port. The dedicated port will always be
	 * after the USB PD ports, and there should be only one.
	 */
	अक्षरger->num_usbpd_ports =
		cros_usbpd_अक्षरger_get_usbpd_num_ports(अक्षरger);
	अगर (अक्षरger->num_usbpd_ports <= 0) अणु
		/*
		 * This can happen on a प्रणाली that करोesn't support USB PD.
		 * Log a message, but no need to warn.
		 */
		dev_info(dev, "No USB PD charging ports found\n");
	पूर्ण

	अक्षरger->num_अक्षरger_ports = cros_usbpd_अक्षरger_get_num_ports(अक्षरger);
	अगर (अक्षरger->num_अक्षरger_ports < 0) अणु
		/*
		 * This can happen on a प्रणाली that करोesn't support USB PD.
		 * Log a message, but no need to warn.
		 * Older ECs करो not support the above command, in that हाल
		 * let's set up the number of अक्षरger ports equal to the number
		 * of USB PD ports
		 */
		dev_info(dev, "Could not get charger port count\n");
		अक्षरger->num_अक्षरger_ports = अक्षरger->num_usbpd_ports;
	पूर्ण

	अगर (अक्षरger->num_अक्षरger_ports <= 0) अणु
		/*
		 * This can happen on a प्रणाली that करोesn't support USB PD and
		 * करोesn't have a dedicated port.
		 * Log a message, but no need to warn.
		 */
		dev_info(dev, "No charging ports found\n");
		ret = -ENODEV;
		जाओ fail_nowarn;
	पूर्ण

	/*
	 * Sanity checks on the number of ports:
	 *  there should be at most 1 dedicated port
	 */
	अगर (अक्षरger->num_अक्षरger_ports < अक्षरger->num_usbpd_ports ||
	    अक्षरger->num_अक्षरger_ports > (अक्षरger->num_usbpd_ports + 1)) अणु
		dev_err(dev, "Unexpected number of charge port count\n");
		ret = -EPROTO;
		जाओ fail_nowarn;
	पूर्ण

	क्रम (i = 0; i < अक्षरger->num_अक्षरger_ports; i++) अणु
		काष्ठा घातer_supply_config psy_cfg = अणुपूर्ण;

		port = devm_kzalloc(dev, माप(काष्ठा port_data), GFP_KERNEL);
		अगर (!port) अणु
			ret = -ENOMEM;
			जाओ fail;
		पूर्ण

		port->अक्षरger = अक्षरger;
		port->port_number = i;

		psy_desc = &port->psy_desc;
		psy_desc->get_property = cros_usbpd_अक्षरger_get_prop;
		psy_desc->set_property = cros_usbpd_अक्षरger_set_prop;
		psy_desc->property_is_ग_लिखोable =
				cros_usbpd_अक्षरger_property_is_ग_लिखोable;
		psy_desc->बाह्यal_घातer_changed =
					cros_usbpd_अक्षरger_घातer_changed;
		psy_cfg.drv_data = port;

		अगर (cros_usbpd_अक्षरger_port_is_dedicated(port)) अणु
			प्र_लिखो(port->name, CHARGER_DEDICATED_सूची_NAME);
			psy_desc->type = POWER_SUPPLY_TYPE_MAINS;
			psy_desc->properties =
				cros_usbpd_dedicated_अक्षरger_props;
			psy_desc->num_properties =
				ARRAY_SIZE(cros_usbpd_dedicated_अक्षरger_props);
		पूर्ण अन्यथा अणु
			प्र_लिखो(port->name, CHARGER_USBPD_सूची_NAME, i);
			psy_desc->type = POWER_SUPPLY_TYPE_USB;
			psy_desc->properties = cros_usbpd_अक्षरger_props;
			psy_desc->num_properties =
				ARRAY_SIZE(cros_usbpd_अक्षरger_props);
			psy_desc->usb_types = cros_usbpd_अक्षरger_usb_types;
			psy_desc->num_usb_types =
				ARRAY_SIZE(cros_usbpd_अक्षरger_usb_types);
		पूर्ण

		psy_desc->name = port->name;

		psy = devm_घातer_supply_रेजिस्टर_no_ws(dev, psy_desc,
						       &psy_cfg);
		अगर (IS_ERR(psy)) अणु
			dev_err(dev, "Failed to register power supply\n");
			जारी;
		पूर्ण
		port->psy = psy;

		अक्षरger->ports[अक्षरger->num_रेजिस्टरed_psy++] = port;
	पूर्ण

	अगर (!अक्षरger->num_रेजिस्टरed_psy) अणु
		ret = -ENODEV;
		dev_err(dev, "No power supplies registered\n");
		जाओ fail;
	पूर्ण

	/* Get PD events from the EC */
	अक्षरger->notअगरier.notअगरier_call = cros_usbpd_अक्षरger_ec_event;
	ret = cros_usbpd_रेजिस्टर_notअगरy(&अक्षरger->notअगरier);
	अगर (ret < 0) अणु
		dev_warn(dev, "failed to register notifier\n");
	पूर्ण अन्यथा अणु
		ret = devm_add_action_or_reset(dev,
				cros_usbpd_अक्षरger_unरेजिस्टर_notअगरier,
				अक्षरger);
		अगर (ret < 0)
			जाओ fail;
	पूर्ण

	वापस 0;

fail:
	WARN(1, "%s: Failing probe (err:0x%x)\n", dev_name(dev), ret);

fail_nowarn:
	dev_info(dev, "Failing probe (err:0x%x)\n", ret);
	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक cros_usbpd_अक्षरger_resume(काष्ठा device *dev)
अणु
	काष्ठा अक्षरger_data *अक्षरger = dev_get_drvdata(dev);
	पूर्णांक i;

	अगर (!अक्षरger)
		वापस 0;

	क्रम (i = 0; i < अक्षरger->num_रेजिस्टरed_psy; i++) अणु
		घातer_supply_changed(अक्षरger->ports[i]->psy);
		अक्षरger->ports[i]->last_update =
				jअगरfies - CHARGER_CACHE_UPDATE_DELAY;
	पूर्ण

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(cros_usbpd_अक्षरger_pm_ops, शून्य,
			 cros_usbpd_अक्षरger_resume);

अटल काष्ठा platक्रमm_driver cros_usbpd_अक्षरger_driver = अणु
	.driver = अणु
		.name = DRV_NAME,
		.pm = &cros_usbpd_अक्षरger_pm_ops,
	पूर्ण,
	.probe = cros_usbpd_अक्षरger_probe
पूर्ण;

module_platक्रमm_driver(cros_usbpd_अक्षरger_driver);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("ChromeOS EC USBPD charger");
MODULE_ALIAS("platform:" DRV_NAME);
