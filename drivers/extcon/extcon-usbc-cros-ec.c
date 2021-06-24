<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// ChromeOS Embedded Controller extcon
//
// Copyright (C) 2017 Google, Inc.
// Author: Benson Leung <bleung@chromium.org>

#समावेश <linux/extcon-provider.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_data/cros_ec_commands.h>
#समावेश <linux/platक्रमm_data/cros_ec_proto.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/sched.h>

काष्ठा cros_ec_extcon_info अणु
	काष्ठा device *dev;
	काष्ठा extcon_dev *edev;

	पूर्णांक port_id;

	काष्ठा cros_ec_device *ec;

	काष्ठा notअगरier_block notअगरier;

	अचिन्हित पूर्णांक dr; /* data role */
	bool pr; /* घातer role (true अगर VBUS enabled) */
	bool dp; /* DisplayPort enabled */
	bool mux; /* SuperSpeed (usb3) enabled */
	अचिन्हित पूर्णांक घातer_type;
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक usb_type_c_cable[] = अणु
	EXTCON_USB,
	EXTCON_USB_HOST,
	EXTCON_DISP_DP,
	EXTCON_NONE,
पूर्ण;

क्रमागत usb_data_roles अणु
	DR_NONE,
	DR_HOST,
	DR_DEVICE,
पूर्ण;

/**
 * cros_ec_pd_command() - Send a command to the EC.
 * @info: poपूर्णांकer to काष्ठा cros_ec_extcon_info
 * @command: EC command
 * @version: EC command version
 * @outdata: EC command output data
 * @outsize: Size of outdata
 * @indata: EC command input data
 * @insize: Size of indata
 *
 * Return: 0 on success, <0 on failure.
 */
अटल पूर्णांक cros_ec_pd_command(काष्ठा cros_ec_extcon_info *info,
			      अचिन्हित पूर्णांक command,
			      अचिन्हित पूर्णांक version,
			      व्योम *outdata,
			      अचिन्हित पूर्णांक outsize,
			      व्योम *indata,
			      अचिन्हित पूर्णांक insize)
अणु
	काष्ठा cros_ec_command *msg;
	पूर्णांक ret;

	msg = kzalloc(माप(*msg) + max(outsize, insize), GFP_KERNEL);
	अगर (!msg)
		वापस -ENOMEM;

	msg->version = version;
	msg->command = command;
	msg->outsize = outsize;
	msg->insize = insize;

	अगर (outsize)
		स_नकल(msg->data, outdata, outsize);

	ret = cros_ec_cmd_xfer_status(info->ec, msg);
	अगर (ret >= 0 && insize)
		स_नकल(indata, msg->data, insize);

	kमुक्त(msg);
	वापस ret;
पूर्ण

/**
 * cros_ec_usb_get_घातer_type() - Get घातer type info about PD device attached
 * to given port.
 * @info: poपूर्णांकer to काष्ठा cros_ec_extcon_info
 *
 * Return: घातer type on success, <0 on failure.
 */
अटल पूर्णांक cros_ec_usb_get_घातer_type(काष्ठा cros_ec_extcon_info *info)
अणु
	काष्ठा ec_params_usb_pd_घातer_info req;
	काष्ठा ec_response_usb_pd_घातer_info resp;
	पूर्णांक ret;

	req.port = info->port_id;
	ret = cros_ec_pd_command(info, EC_CMD_USB_PD_POWER_INFO, 0,
				 &req, माप(req), &resp, माप(resp));
	अगर (ret < 0)
		वापस ret;

	वापस resp.type;
पूर्ण

/**
 * cros_ec_usb_get_pd_mux_state() - Get PD mux state क्रम given port.
 * @info: poपूर्णांकer to काष्ठा cros_ec_extcon_info
 *
 * Return: PD mux state on success, <0 on failure.
 */
अटल पूर्णांक cros_ec_usb_get_pd_mux_state(काष्ठा cros_ec_extcon_info *info)
अणु
	काष्ठा ec_params_usb_pd_mux_info req;
	काष्ठा ec_response_usb_pd_mux_info resp;
	पूर्णांक ret;

	req.port = info->port_id;
	ret = cros_ec_pd_command(info, EC_CMD_USB_PD_MUX_INFO, 0,
				 &req, माप(req),
				 &resp, माप(resp));
	अगर (ret < 0)
		वापस ret;

	वापस resp.flags;
पूर्ण

/**
 * cros_ec_usb_get_role() - Get role info about possible PD device attached to a
 * given port.
 * @info: poपूर्णांकer to काष्ठा cros_ec_extcon_info
 * @polarity: poपूर्णांकer to cable polarity (वापस value)
 *
 * Return: role info on success, -ENOTCONN अगर no cable is connected, <0 on
 * failure.
 */
अटल पूर्णांक cros_ec_usb_get_role(काष्ठा cros_ec_extcon_info *info,
				bool *polarity)
अणु
	काष्ठा ec_params_usb_pd_control pd_control;
	काष्ठा ec_response_usb_pd_control_v1 resp;
	पूर्णांक ret;

	pd_control.port = info->port_id;
	pd_control.role = USB_PD_CTRL_ROLE_NO_CHANGE;
	pd_control.mux = USB_PD_CTRL_MUX_NO_CHANGE;
	pd_control.swap = USB_PD_CTRL_SWAP_NONE;
	ret = cros_ec_pd_command(info, EC_CMD_USB_PD_CONTROL, 1,
				 &pd_control, माप(pd_control),
				 &resp, माप(resp));
	अगर (ret < 0)
		वापस ret;

	अगर (!(resp.enabled & PD_CTRL_RESP_ENABLED_CONNECTED))
		वापस -ENOTCONN;

	*polarity = resp.polarity;

	वापस resp.role;
पूर्ण

/**
 * cros_ec_pd_get_num_ports() - Get number of EC अक्षरge ports.
 * @info: poपूर्णांकer to काष्ठा cros_ec_extcon_info
 *
 * Return: number of ports on success, <0 on failure.
 */
अटल पूर्णांक cros_ec_pd_get_num_ports(काष्ठा cros_ec_extcon_info *info)
अणु
	काष्ठा ec_response_usb_pd_ports resp;
	पूर्णांक ret;

	ret = cros_ec_pd_command(info, EC_CMD_USB_PD_PORTS,
				 0, शून्य, 0, &resp, माप(resp));
	अगर (ret < 0)
		वापस ret;

	वापस resp.num_ports;
पूर्ण

अटल स्थिर अक्षर *cros_ec_usb_role_string(अचिन्हित पूर्णांक role)
अणु
	वापस role == DR_NONE ? "DISCONNECTED" :
		(role == DR_HOST ? "DFP" : "UFP");
पूर्ण

अटल स्थिर अक्षर *cros_ec_usb_घातer_type_string(अचिन्हित पूर्णांक type)
अणु
	चयन (type) अणु
	हाल USB_CHG_TYPE_NONE:
		वापस "USB_CHG_TYPE_NONE";
	हाल USB_CHG_TYPE_PD:
		वापस "USB_CHG_TYPE_PD";
	हाल USB_CHG_TYPE_PROPRIETARY:
		वापस "USB_CHG_TYPE_PROPRIETARY";
	हाल USB_CHG_TYPE_C:
		वापस "USB_CHG_TYPE_C";
	हाल USB_CHG_TYPE_BC12_DCP:
		वापस "USB_CHG_TYPE_BC12_DCP";
	हाल USB_CHG_TYPE_BC12_CDP:
		वापस "USB_CHG_TYPE_BC12_CDP";
	हाल USB_CHG_TYPE_BC12_SDP:
		वापस "USB_CHG_TYPE_BC12_SDP";
	हाल USB_CHG_TYPE_OTHER:
		वापस "USB_CHG_TYPE_OTHER";
	हाल USB_CHG_TYPE_VBUS:
		वापस "USB_CHG_TYPE_VBUS";
	हाल USB_CHG_TYPE_UNKNOWN:
		वापस "USB_CHG_TYPE_UNKNOWN";
	शेष:
		वापस "USB_CHG_TYPE_UNKNOWN";
	पूर्ण
पूर्ण

अटल bool cros_ec_usb_घातer_type_is_wall_wart(अचिन्हित पूर्णांक type,
						अचिन्हित पूर्णांक role)
अणु
	चयन (type) अणु
	/* FIXME : Guppy, Donnettes, and other अक्षरgers will be miscategorized
	 * because they identअगरy with USB_CHG_TYPE_C, but we can't वापस true
	 * here from that code because that अवरोधs Suzy-Q and other kinds of
	 * USB Type-C cables and peripherals.
	 */
	हाल USB_CHG_TYPE_PROPRIETARY:
	हाल USB_CHG_TYPE_BC12_DCP:
		वापस true;
	हाल USB_CHG_TYPE_PD:
	हाल USB_CHG_TYPE_C:
	हाल USB_CHG_TYPE_BC12_CDP:
	हाल USB_CHG_TYPE_BC12_SDP:
	हाल USB_CHG_TYPE_OTHER:
	हाल USB_CHG_TYPE_VBUS:
	हाल USB_CHG_TYPE_UNKNOWN:
	हाल USB_CHG_TYPE_NONE:
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल पूर्णांक extcon_cros_ec_detect_cable(काष्ठा cros_ec_extcon_info *info,
				       bool क्रमce)
अणु
	काष्ठा device *dev = info->dev;
	पूर्णांक role, घातer_type;
	अचिन्हित पूर्णांक dr = DR_NONE;
	bool pr = false;
	bool polarity = false;
	bool dp = false;
	bool mux = false;
	bool hpd = false;

	घातer_type = cros_ec_usb_get_घातer_type(info);
	अगर (घातer_type < 0) अणु
		dev_err(dev, "failed getting power type err = %d\n",
			घातer_type);
		वापस घातer_type;
	पूर्ण

	role = cros_ec_usb_get_role(info, &polarity);
	अगर (role < 0) अणु
		अगर (role != -ENOTCONN) अणु
			dev_err(dev, "failed getting role err = %d\n", role);
			वापस role;
		पूर्ण
		dev_dbg(dev, "disconnected\n");
	पूर्ण अन्यथा अणु
		पूर्णांक pd_mux_state;

		dr = (role & PD_CTRL_RESP_ROLE_DATA) ? DR_HOST : DR_DEVICE;
		pr = (role & PD_CTRL_RESP_ROLE_POWER);
		pd_mux_state = cros_ec_usb_get_pd_mux_state(info);
		अगर (pd_mux_state < 0)
			pd_mux_state = USB_PD_MUX_USB_ENABLED;

		dp = pd_mux_state & USB_PD_MUX_DP_ENABLED;
		mux = pd_mux_state & USB_PD_MUX_USB_ENABLED;
		hpd = pd_mux_state & USB_PD_MUX_HPD_IRQ;

		dev_dbg(dev,
			"connected role 0x%x pwr type %d dr %d pr %d pol %d mux %d dp %d hpd %d\n",
			role, घातer_type, dr, pr, polarity, mux, dp, hpd);
	पूर्ण

	/*
	 * When there is no USB host (e.g. USB PD अक्षरger),
	 * we are not really a UFP क्रम the AP.
	 */
	अगर (dr == DR_DEVICE &&
	    cros_ec_usb_घातer_type_is_wall_wart(घातer_type, role))
		dr = DR_NONE;

	अगर (क्रमce || info->dr != dr || info->pr != pr || info->dp != dp ||
	    info->mux != mux || info->घातer_type != घातer_type) अणु
		bool host_connected = false, device_connected = false;

		dev_dbg(dev, "Type/Role switch! type = %s role = %s\n",
			cros_ec_usb_घातer_type_string(घातer_type),
			cros_ec_usb_role_string(dr));
		info->dr = dr;
		info->pr = pr;
		info->dp = dp;
		info->mux = mux;
		info->घातer_type = घातer_type;

		अगर (dr == DR_DEVICE)
			device_connected = true;
		अन्यथा अगर (dr == DR_HOST)
			host_connected = true;

		extcon_set_state(info->edev, EXTCON_USB, device_connected);
		extcon_set_state(info->edev, EXTCON_USB_HOST, host_connected);
		extcon_set_state(info->edev, EXTCON_DISP_DP, dp);
		extcon_set_property(info->edev, EXTCON_USB,
				    EXTCON_PROP_USB_VBUS,
				    (जोड़ extcon_property_value)(पूर्णांक)pr);
		extcon_set_property(info->edev, EXTCON_USB_HOST,
				    EXTCON_PROP_USB_VBUS,
				    (जोड़ extcon_property_value)(पूर्णांक)pr);
		extcon_set_property(info->edev, EXTCON_USB,
				    EXTCON_PROP_USB_TYPEC_POLARITY,
				    (जोड़ extcon_property_value)(पूर्णांक)polarity);
		extcon_set_property(info->edev, EXTCON_USB_HOST,
				    EXTCON_PROP_USB_TYPEC_POLARITY,
				    (जोड़ extcon_property_value)(पूर्णांक)polarity);
		extcon_set_property(info->edev, EXTCON_DISP_DP,
				    EXTCON_PROP_USB_TYPEC_POLARITY,
				    (जोड़ extcon_property_value)(पूर्णांक)polarity);
		extcon_set_property(info->edev, EXTCON_USB,
				    EXTCON_PROP_USB_SS,
				    (जोड़ extcon_property_value)(पूर्णांक)mux);
		extcon_set_property(info->edev, EXTCON_USB_HOST,
				    EXTCON_PROP_USB_SS,
				    (जोड़ extcon_property_value)(पूर्णांक)mux);
		extcon_set_property(info->edev, EXTCON_DISP_DP,
				    EXTCON_PROP_USB_SS,
				    (जोड़ extcon_property_value)(पूर्णांक)mux);
		extcon_set_property(info->edev, EXTCON_DISP_DP,
				    EXTCON_PROP_DISP_HPD,
				    (जोड़ extcon_property_value)(पूर्णांक)hpd);

		extcon_sync(info->edev, EXTCON_USB);
		extcon_sync(info->edev, EXTCON_USB_HOST);
		extcon_sync(info->edev, EXTCON_DISP_DP);

	पूर्ण अन्यथा अगर (hpd) अणु
		extcon_set_property(info->edev, EXTCON_DISP_DP,
				    EXTCON_PROP_DISP_HPD,
				    (जोड़ extcon_property_value)(पूर्णांक)hpd);
		extcon_sync(info->edev, EXTCON_DISP_DP);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक extcon_cros_ec_event(काष्ठा notअगरier_block *nb,
				अचिन्हित दीर्घ queued_during_suspend,
				व्योम *_notअगरy)
अणु
	काष्ठा cros_ec_extcon_info *info;
	काष्ठा cros_ec_device *ec;
	u32 host_event;

	info = container_of(nb, काष्ठा cros_ec_extcon_info, notअगरier);
	ec = info->ec;

	host_event = cros_ec_get_host_event(ec);
	अगर (host_event & (EC_HOST_EVENT_MASK(EC_HOST_EVENT_PD_MCU) |
			  EC_HOST_EVENT_MASK(EC_HOST_EVENT_USB_MUX))) अणु
		extcon_cros_ec_detect_cable(info, false);
		वापस NOTIFY_OK;
	पूर्ण

	वापस NOTIFY_DONE;
पूर्ण

अटल पूर्णांक extcon_cros_ec_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा cros_ec_extcon_info *info;
	काष्ठा cros_ec_device *ec = dev_get_drvdata(pdev->dev.parent);
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *np = dev->of_node;
	पूर्णांक numports, ret;

	info = devm_kzalloc(dev, माप(*info), GFP_KERNEL);
	अगर (!info)
		वापस -ENOMEM;

	info->dev = dev;
	info->ec = ec;

	अगर (np) अणु
		u32 port;

		ret = of_property_पढ़ो_u32(np, "google,usb-port-id", &port);
		अगर (ret < 0) अणु
			dev_err(dev, "Missing google,usb-port-id property\n");
			वापस ret;
		पूर्ण
		info->port_id = port;
	पूर्ण अन्यथा अणु
		info->port_id = pdev->id;
	पूर्ण

	numports = cros_ec_pd_get_num_ports(info);
	अगर (numports < 0) अणु
		dev_err(dev, "failed getting number of ports! ret = %d\n",
			numports);
		वापस numports;
	पूर्ण

	अगर (info->port_id >= numports) अणु
		dev_err(dev, "This system only supports %d ports\n", numports);
		वापस -ENODEV;
	पूर्ण

	info->edev = devm_extcon_dev_allocate(dev, usb_type_c_cable);
	अगर (IS_ERR(info->edev)) अणु
		dev_err(dev, "failed to allocate extcon device\n");
		वापस -ENOMEM;
	पूर्ण

	ret = devm_extcon_dev_रेजिस्टर(dev, info->edev);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to register extcon device\n");
		वापस ret;
	पूर्ण

	extcon_set_property_capability(info->edev, EXTCON_USB,
				       EXTCON_PROP_USB_VBUS);
	extcon_set_property_capability(info->edev, EXTCON_USB_HOST,
				       EXTCON_PROP_USB_VBUS);
	extcon_set_property_capability(info->edev, EXTCON_USB,
				       EXTCON_PROP_USB_TYPEC_POLARITY);
	extcon_set_property_capability(info->edev, EXTCON_USB_HOST,
				       EXTCON_PROP_USB_TYPEC_POLARITY);
	extcon_set_property_capability(info->edev, EXTCON_DISP_DP,
				       EXTCON_PROP_USB_TYPEC_POLARITY);
	extcon_set_property_capability(info->edev, EXTCON_USB,
				       EXTCON_PROP_USB_SS);
	extcon_set_property_capability(info->edev, EXTCON_USB_HOST,
				       EXTCON_PROP_USB_SS);
	extcon_set_property_capability(info->edev, EXTCON_DISP_DP,
				       EXTCON_PROP_USB_SS);
	extcon_set_property_capability(info->edev, EXTCON_DISP_DP,
				       EXTCON_PROP_DISP_HPD);

	info->dr = DR_NONE;
	info->pr = false;

	platक्रमm_set_drvdata(pdev, info);

	/* Get PD events from the EC */
	info->notअगरier.notअगरier_call = extcon_cros_ec_event;
	ret = blocking_notअगरier_chain_रेजिस्टर(&info->ec->event_notअगरier,
					       &info->notअगरier);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to register notifier\n");
		वापस ret;
	पूर्ण

	/* Perक्रमm initial detection */
	ret = extcon_cros_ec_detect_cable(info, true);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to detect initial cable state\n");
		जाओ unरेजिस्टर_notअगरier;
	पूर्ण

	वापस 0;

unरेजिस्टर_notअगरier:
	blocking_notअगरier_chain_unरेजिस्टर(&info->ec->event_notअगरier,
					   &info->notअगरier);
	वापस ret;
पूर्ण

अटल पूर्णांक extcon_cros_ec_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा cros_ec_extcon_info *info = platक्रमm_get_drvdata(pdev);

	blocking_notअगरier_chain_unरेजिस्टर(&info->ec->event_notअगरier,
					   &info->notअगरier);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक extcon_cros_ec_suspend(काष्ठा device *dev)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक extcon_cros_ec_resume(काष्ठा device *dev)
अणु
	पूर्णांक ret;
	काष्ठा cros_ec_extcon_info *info = dev_get_drvdata(dev);

	ret = extcon_cros_ec_detect_cable(info, true);
	अगर (ret < 0)
		dev_err(dev, "failed to detect cable state on resume\n");

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops extcon_cros_ec_dev_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(extcon_cros_ec_suspend, extcon_cros_ec_resume)
पूर्ण;

#घोषणा DEV_PM_OPS	(&extcon_cros_ec_dev_pm_ops)
#अन्यथा
#घोषणा DEV_PM_OPS	शून्य
#पूर्ण_अगर /* CONFIG_PM_SLEEP */

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id extcon_cros_ec_of_match[] = अणु
	अणु .compatible = "google,extcon-usbc-cros-ec" पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, extcon_cros_ec_of_match);
#पूर्ण_अगर /* CONFIG_OF */

अटल काष्ठा platक्रमm_driver extcon_cros_ec_driver = अणु
	.driver = अणु
		.name  = "extcon-usbc-cros-ec",
		.of_match_table = of_match_ptr(extcon_cros_ec_of_match),
		.pm = DEV_PM_OPS,
	पूर्ण,
	.हटाओ  = extcon_cros_ec_हटाओ,
	.probe   = extcon_cros_ec_probe,
पूर्ण;

module_platक्रमm_driver(extcon_cros_ec_driver);

MODULE_DESCRIPTION("ChromeOS Embedded Controller extcon driver");
MODULE_AUTHOR("Benson Leung <bleung@chromium.org>");
MODULE_LICENSE("GPL v2");
