<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright 2020 Google LLC
 *
 * This driver provides the ability to view and manage Type C ports through the
 * Chrome OS EC.
 */

#समावेश <linux/acpi.h>
#समावेश <linux/list.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_data/cros_ec_commands.h>
#समावेश <linux/platक्रमm_data/cros_ec_proto.h>
#समावेश <linux/platक्रमm_data/cros_usbpd_notअगरy.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/usb/pd.h>
#समावेश <linux/usb/pd_vकरो.h>
#समावेश <linux/usb/typec.h>
#समावेश <linux/usb/typec_alपंचांगode.h>
#समावेश <linux/usb/typec_dp.h>
#समावेश <linux/usb/typec_mux.h>
#समावेश <linux/usb/typec_tbt.h>
#समावेश <linux/usb/role.h>

#घोषणा DRV_NAME "cros-ec-typec"

/* Supported alt modes. */
क्रमागत अणु
	CROS_EC_ALTMODE_DP = 0,
	CROS_EC_ALTMODE_TBT,
	CROS_EC_ALTMODE_MAX,
पूर्ण;

/* Container क्रम alपंचांगode poपूर्णांकer nodes. */
काष्ठा cros_typec_alपंचांगode_node अणु
	काष्ठा typec_alपंचांगode *amode;
	काष्ठा list_head list;
पूर्ण;

/* Per port data. */
काष्ठा cros_typec_port अणु
	काष्ठा typec_port *port;
	/* Initial capabilities क्रम the port. */
	काष्ठा typec_capability caps;
	काष्ठा typec_partner *partner;
	काष्ठा typec_cable *cable;
	/* SOP' plug. */
	काष्ठा typec_plug *plug;
	/* Port partner PD identity info. */
	काष्ठा usb_pd_identity p_identity;
	/* Port cable PD identity info. */
	काष्ठा usb_pd_identity c_identity;
	काष्ठा typec_चयन *ori_sw;
	काष्ठा typec_mux *mux;
	काष्ठा usb_role_चयन *role_sw;

	/* Variables keeping track of चयन state. */
	काष्ठा typec_mux_state state;
	uपूर्णांक8_t mux_flags;
	uपूर्णांक8_t role;

	/* Port alt modes. */
	काष्ठा typec_alपंचांगode p_alपंचांगode[CROS_EC_ALTMODE_MAX];

	/* Flag indicating that PD partner discovery data parsing is completed. */
	bool sop_disc_करोne;
	bool sop_prime_disc_करोne;
	काष्ठा ec_response_typec_discovery *disc_data;
	काष्ठा list_head partner_mode_list;
	काष्ठा list_head plug_mode_list;
पूर्ण;

/* Platक्रमm-specअगरic data क्रम the Chrome OS EC Type C controller. */
काष्ठा cros_typec_data अणु
	काष्ठा device *dev;
	काष्ठा cros_ec_device *ec;
	पूर्णांक num_ports;
	अचिन्हित पूर्णांक pd_ctrl_ver;
	/* Array of ports, indexed by port number. */
	काष्ठा cros_typec_port *ports[EC_USB_PD_MAX_PORTS];
	काष्ठा notअगरier_block nb;
	काष्ठा work_काष्ठा port_work;
	bool typec_cmd_supported;
	bool needs_mux_ack;
पूर्ण;

अटल पूर्णांक cros_typec_parse_port_props(काष्ठा typec_capability *cap,
				       काष्ठा fwnode_handle *fwnode,
				       काष्ठा device *dev)
अणु
	स्थिर अक्षर *buf;
	पूर्णांक ret;

	स_रखो(cap, 0, माप(*cap));
	ret = fwnode_property_पढ़ो_string(fwnode, "power-role", &buf);
	अगर (ret) अणु
		dev_err(dev, "power-role not found: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = typec_find_port_घातer_role(buf);
	अगर (ret < 0)
		वापस ret;
	cap->type = ret;

	ret = fwnode_property_पढ़ो_string(fwnode, "data-role", &buf);
	अगर (ret) अणु
		dev_err(dev, "data-role not found: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = typec_find_port_data_role(buf);
	अगर (ret < 0)
		वापस ret;
	cap->data = ret;

	ret = fwnode_property_पढ़ो_string(fwnode, "try-power-role", &buf);
	अगर (ret) अणु
		dev_err(dev, "try-power-role not found: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = typec_find_घातer_role(buf);
	अगर (ret < 0)
		वापस ret;
	cap->prefer_role = ret;

	cap->fwnode = fwnode;

	वापस 0;
पूर्ण

अटल पूर्णांक cros_typec_get_चयन_handles(काष्ठा cros_typec_port *port,
					 काष्ठा fwnode_handle *fwnode,
					 काष्ठा device *dev)
अणु
	port->mux = fwnode_typec_mux_get(fwnode, शून्य);
	अगर (IS_ERR(port->mux)) अणु
		dev_dbg(dev, "Mux handle not found.\n");
		जाओ mux_err;
	पूर्ण

	port->ori_sw = fwnode_typec_चयन_get(fwnode);
	अगर (IS_ERR(port->ori_sw)) अणु
		dev_dbg(dev, "Orientation switch handle not found.\n");
		जाओ ori_sw_err;
	पूर्ण

	port->role_sw = fwnode_usb_role_चयन_get(fwnode);
	अगर (IS_ERR(port->role_sw)) अणु
		dev_dbg(dev, "USB role switch handle not found.\n");
		जाओ role_sw_err;
	पूर्ण

	वापस 0;

role_sw_err:
	usb_role_चयन_put(port->role_sw);
ori_sw_err:
	typec_चयन_put(port->ori_sw);
mux_err:
	typec_mux_put(port->mux);

	वापस -ENODEV;
पूर्ण

अटल पूर्णांक cros_typec_add_partner(काष्ठा cros_typec_data *typec, पूर्णांक port_num,
				  bool pd_en)
अणु
	काष्ठा cros_typec_port *port = typec->ports[port_num];
	काष्ठा typec_partner_desc p_desc = अणु
		.usb_pd = pd_en,
	पूर्ण;
	पूर्णांक ret = 0;

	/*
	 * Fill an initial PD identity, which will then be updated with info
	 * from the EC.
	 */
	p_desc.identity = &port->p_identity;

	port->partner = typec_रेजिस्टर_partner(port->port, &p_desc);
	अगर (IS_ERR(port->partner)) अणु
		ret = PTR_ERR(port->partner);
		port->partner = शून्य;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम cros_typec_unरेजिस्टर_alपंचांगodes(काष्ठा cros_typec_data *typec, पूर्णांक port_num,
					   bool is_partner)
अणु
	काष्ठा cros_typec_port *port = typec->ports[port_num];
	काष्ठा cros_typec_alपंचांगode_node *node, *पंचांगp;
	काष्ठा list_head *head;

	head = is_partner ? &port->partner_mode_list : &port->plug_mode_list;
	list_क्रम_each_entry_safe(node, पंचांगp, head, list) अणु
		list_del(&node->list);
		typec_unरेजिस्टर_alपंचांगode(node->amode);
		devm_kमुक्त(typec->dev, node);
	पूर्ण
पूर्ण

अटल पूर्णांक cros_typec_usb_disconnect_state(काष्ठा cros_typec_port *port)
अणु
	port->state.alt = शून्य;
	port->state.mode = TYPEC_STATE_USB;
	port->state.data = शून्य;

	usb_role_चयन_set_role(port->role_sw, USB_ROLE_NONE);
	typec_चयन_set(port->ori_sw, TYPEC_ORIENTATION_NONE);

	वापस typec_mux_set(port->mux, &port->state);
पूर्ण

अटल व्योम cros_typec_हटाओ_partner(काष्ठा cros_typec_data *typec,
				      पूर्णांक port_num)
अणु
	काष्ठा cros_typec_port *port = typec->ports[port_num];

	अगर (!port->partner)
		वापस;

	cros_typec_unरेजिस्टर_alपंचांगodes(typec, port_num, true);

	cros_typec_usb_disconnect_state(port);

	typec_unरेजिस्टर_partner(port->partner);
	port->partner = शून्य;
	स_रखो(&port->p_identity, 0, माप(port->p_identity));
	port->sop_disc_करोne = false;
पूर्ण

अटल व्योम cros_typec_हटाओ_cable(काष्ठा cros_typec_data *typec,
				    पूर्णांक port_num)
अणु
	काष्ठा cros_typec_port *port = typec->ports[port_num];

	अगर (!port->cable)
		वापस;

	cros_typec_unरेजिस्टर_alपंचांगodes(typec, port_num, false);

	typec_unरेजिस्टर_plug(port->plug);
	port->plug = शून्य;
	typec_unरेजिस्टर_cable(port->cable);
	port->cable = शून्य;
	स_रखो(&port->c_identity, 0, माप(port->c_identity));
	port->sop_prime_disc_करोne = false;
पूर्ण

अटल व्योम cros_unरेजिस्टर_ports(काष्ठा cros_typec_data *typec)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < typec->num_ports; i++) अणु
		अगर (!typec->ports[i])
			जारी;

		cros_typec_हटाओ_partner(typec, i);
		cros_typec_हटाओ_cable(typec, i);

		usb_role_चयन_put(typec->ports[i]->role_sw);
		typec_चयन_put(typec->ports[i]->ori_sw);
		typec_mux_put(typec->ports[i]->mux);
		typec_unरेजिस्टर_port(typec->ports[i]->port);
	पूर्ण
पूर्ण

/*
 * Fake the alt mode काष्ठाs until we actually start रेजिस्टरing Type C port
 * and partner alt modes.
 */
अटल व्योम cros_typec_रेजिस्टर_port_alपंचांगodes(काष्ठा cros_typec_data *typec,
					      पूर्णांक port_num)
अणु
	काष्ठा cros_typec_port *port = typec->ports[port_num];

	/* All PD capable CrOS devices are assumed to support DP alपंचांगode. */
	port->p_alपंचांगode[CROS_EC_ALTMODE_DP].svid = USB_TYPEC_DP_SID;
	port->p_alपंचांगode[CROS_EC_ALTMODE_DP].mode = USB_TYPEC_DP_MODE;

	/*
	 * Register TBT compatibility alt mode. The EC will not enter the mode
	 * अगर it करोesn't support it, so it's safe to रेजिस्टर it unconditionally
	 * here क्रम now.
	 */
	port->p_alपंचांगode[CROS_EC_ALTMODE_TBT].svid = USB_TYPEC_TBT_SID;
	port->p_alपंचांगode[CROS_EC_ALTMODE_TBT].mode = TYPEC_ANY_MODE;

	port->state.alt = शून्य;
	port->state.mode = TYPEC_STATE_USB;
	port->state.data = शून्य;
पूर्ण

अटल पूर्णांक cros_typec_init_ports(काष्ठा cros_typec_data *typec)
अणु
	काष्ठा device *dev = typec->dev;
	काष्ठा typec_capability *cap;
	काष्ठा fwnode_handle *fwnode;
	काष्ठा cros_typec_port *cros_port;
	स्थिर अक्षर *port_prop;
	पूर्णांक ret;
	पूर्णांक nports;
	u32 port_num = 0;

	nports = device_get_child_node_count(dev);
	अगर (nports == 0) अणु
		dev_err(dev, "No port entries found.\n");
		वापस -ENODEV;
	पूर्ण

	अगर (nports > typec->num_ports) अणु
		dev_err(dev, "More ports listed than can be supported.\n");
		वापस -EINVAL;
	पूर्ण

	/* DT uses "reg" to specअगरy port number. */
	port_prop = dev->of_node ? "reg" : "port-number";
	device_क्रम_each_child_node(dev, fwnode) अणु
		अगर (fwnode_property_पढ़ो_u32(fwnode, port_prop, &port_num)) अणु
			ret = -EINVAL;
			dev_err(dev, "No port-number for port, aborting.\n");
			जाओ unरेजिस्टर_ports;
		पूर्ण

		अगर (port_num >= typec->num_ports) अणु
			dev_err(dev, "Invalid port number.\n");
			ret = -EINVAL;
			जाओ unरेजिस्टर_ports;
		पूर्ण

		dev_dbg(dev, "Registering port %d\n", port_num);

		cros_port = devm_kzalloc(dev, माप(*cros_port), GFP_KERNEL);
		अगर (!cros_port) अणु
			ret = -ENOMEM;
			जाओ unरेजिस्टर_ports;
		पूर्ण

		typec->ports[port_num] = cros_port;
		cap = &cros_port->caps;

		ret = cros_typec_parse_port_props(cap, fwnode, dev);
		अगर (ret < 0)
			जाओ unरेजिस्टर_ports;

		cros_port->port = typec_रेजिस्टर_port(dev, cap);
		अगर (IS_ERR(cros_port->port)) अणु
			dev_err(dev, "Failed to register port %d\n", port_num);
			ret = PTR_ERR(cros_port->port);
			जाओ unरेजिस्टर_ports;
		पूर्ण

		ret = cros_typec_get_चयन_handles(cros_port, fwnode, dev);
		अगर (ret)
			dev_dbg(dev, "No switch control for port %d\n",
				port_num);

		cros_typec_रेजिस्टर_port_alपंचांगodes(typec, port_num);

		cros_port->disc_data = devm_kzalloc(dev, EC_PROTO2_MAX_RESPONSE_SIZE, GFP_KERNEL);
		अगर (!cros_port->disc_data) अणु
			ret = -ENOMEM;
			जाओ unरेजिस्टर_ports;
		पूर्ण

		INIT_LIST_HEAD(&cros_port->partner_mode_list);
		INIT_LIST_HEAD(&cros_port->plug_mode_list);
	पूर्ण

	वापस 0;

unरेजिस्टर_ports:
	cros_unरेजिस्टर_ports(typec);
	वापस ret;
पूर्ण

अटल पूर्णांक cros_typec_ec_command(काष्ठा cros_typec_data *typec,
				 अचिन्हित पूर्णांक version,
				 अचिन्हित पूर्णांक command,
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

	ret = cros_ec_cmd_xfer_status(typec->ec, msg);
	अगर (ret >= 0 && insize)
		स_नकल(indata, msg->data, insize);

	kमुक्त(msg);
	वापस ret;
पूर्ण

अटल पूर्णांक cros_typec_usb_safe_state(काष्ठा cros_typec_port *port)
अणु
	port->state.mode = TYPEC_STATE_SAFE;

	वापस typec_mux_set(port->mux, &port->state);
पूर्ण

/*
 * Spoof the VDOs that were likely communicated by the partner क्रम TBT alt
 * mode.
 */
अटल पूर्णांक cros_typec_enable_tbt(काष्ठा cros_typec_data *typec,
				 पूर्णांक port_num,
				 काष्ठा ec_response_usb_pd_control_v2 *pd_ctrl)
अणु
	काष्ठा cros_typec_port *port = typec->ports[port_num];
	काष्ठा typec_thunderbolt_data data;
	पूर्णांक ret;

	अगर (typec->pd_ctrl_ver < 2) अणु
		dev_err(typec->dev,
			"PD_CTRL version too old: %d\n", typec->pd_ctrl_ver);
		वापस -ENOTSUPP;
	पूर्ण

	/* Device Discover Mode VDO */
	data.device_mode = TBT_MODE;

	अगर (pd_ctrl->control_flags & USB_PD_CTRL_TBT_LEGACY_ADAPTER)
		data.device_mode = TBT_SET_ADAPTER(TBT_ADAPTER_TBT3);

	/* Cable Discover Mode VDO */
	data.cable_mode = TBT_MODE;
	data.cable_mode |= TBT_SET_CABLE_SPEED(pd_ctrl->cable_speed);

	अगर (pd_ctrl->control_flags & USB_PD_CTRL_OPTICAL_CABLE)
		data.cable_mode |= TBT_CABLE_OPTICAL;

	अगर (pd_ctrl->control_flags & USB_PD_CTRL_ACTIVE_LINK_UNIसूची)
		data.cable_mode |= TBT_CABLE_LINK_TRAINING;

	data.cable_mode |= TBT_SET_CABLE_ROUNDED(pd_ctrl->cable_gen);

	/* Enter Mode VDO */
	data.enter_vकरो = TBT_SET_CABLE_SPEED(pd_ctrl->cable_speed);

	अगर (pd_ctrl->control_flags & USB_PD_CTRL_ACTIVE_CABLE)
		data.enter_vकरो |= TBT_ENTER_MODE_ACTIVE_CABLE;

	अगर (!port->state.alt) अणु
		port->state.alt = &port->p_alपंचांगode[CROS_EC_ALTMODE_TBT];
		ret = cros_typec_usb_safe_state(port);
		अगर (ret)
			वापस ret;
	पूर्ण

	port->state.data = &data;
	port->state.mode = TYPEC_TBT_MODE;

	वापस typec_mux_set(port->mux, &port->state);
पूर्ण

/* Spoof the VDOs that were likely communicated by the partner. */
अटल पूर्णांक cros_typec_enable_dp(काष्ठा cros_typec_data *typec,
				पूर्णांक port_num,
				काष्ठा ec_response_usb_pd_control_v2 *pd_ctrl)
अणु
	काष्ठा cros_typec_port *port = typec->ports[port_num];
	काष्ठा typec_displayport_data dp_data;
	पूर्णांक ret;

	अगर (typec->pd_ctrl_ver < 2) अणु
		dev_err(typec->dev,
			"PD_CTRL version too old: %d\n", typec->pd_ctrl_ver);
		वापस -ENOTSUPP;
	पूर्ण

	अगर (!pd_ctrl->dp_mode) अणु
		dev_err(typec->dev, "No valid DP mode provided.\n");
		वापस -EINVAL;
	पूर्ण

	/* Status VDO. */
	dp_data.status = DP_STATUS_ENABLED;
	अगर (port->mux_flags & USB_PD_MUX_HPD_IRQ)
		dp_data.status |= DP_STATUS_IRQ_HPD;
	अगर (port->mux_flags & USB_PD_MUX_HPD_LVL)
		dp_data.status |= DP_STATUS_HPD_STATE;

	/* Configuration VDO. */
	dp_data.conf = DP_CONF_SET_PIN_ASSIGN(pd_ctrl->dp_mode);
	अगर (!port->state.alt) अणु
		port->state.alt = &port->p_alपंचांगode[CROS_EC_ALTMODE_DP];
		ret = cros_typec_usb_safe_state(port);
		अगर (ret)
			वापस ret;
	पूर्ण

	port->state.data = &dp_data;
	port->state.mode = TYPEC_MODAL_STATE(ffs(pd_ctrl->dp_mode));

	वापस typec_mux_set(port->mux, &port->state);
पूर्ण

अटल पूर्णांक cros_typec_enable_usb4(काष्ठा cros_typec_data *typec,
				  पूर्णांक port_num,
				  काष्ठा ec_response_usb_pd_control_v2 *pd_ctrl)
अणु
	काष्ठा cros_typec_port *port = typec->ports[port_num];
	काष्ठा enter_usb_data data;

	data.euकरो = EUDO_USB_MODE_USB4 << EUDO_USB_MODE_SHIFT;

	/* Cable Speed */
	data.euकरो |= pd_ctrl->cable_speed << EUDO_CABLE_SPEED_SHIFT;

	/* Cable Type */
	अगर (pd_ctrl->control_flags & USB_PD_CTRL_OPTICAL_CABLE)
		data.euकरो |= EUDO_CABLE_TYPE_OPTICAL << EUDO_CABLE_TYPE_SHIFT;
	अन्यथा अगर (pd_ctrl->control_flags & USB_PD_CTRL_ACTIVE_CABLE)
		data.euकरो |= EUDO_CABLE_TYPE_RE_TIMER << EUDO_CABLE_TYPE_SHIFT;

	data.active_link_training = !!(pd_ctrl->control_flags &
				       USB_PD_CTRL_ACTIVE_LINK_UNIसूची);

	port->state.alt = शून्य;
	port->state.data = &data;
	port->state.mode = TYPEC_MODE_USB4;

	वापस typec_mux_set(port->mux, &port->state);
पूर्ण

अटल पूर्णांक cros_typec_configure_mux(काष्ठा cros_typec_data *typec, पूर्णांक port_num,
				uपूर्णांक8_t mux_flags,
				काष्ठा ec_response_usb_pd_control_v2 *pd_ctrl)
अणु
	काष्ठा cros_typec_port *port = typec->ports[port_num];
	काष्ठा ec_params_usb_pd_mux_ack mux_ack;
	क्रमागत typec_orientation orientation;
	पूर्णांक ret;

	अगर (mux_flags == USB_PD_MUX_NONE) अणु
		ret = cros_typec_usb_disconnect_state(port);
		जाओ mux_ack;
	पूर्ण

	अगर (mux_flags & USB_PD_MUX_POLARITY_INVERTED)
		orientation = TYPEC_ORIENTATION_REVERSE;
	अन्यथा
		orientation = TYPEC_ORIENTATION_NORMAL;

	ret = typec_चयन_set(port->ori_sw, orientation);
	अगर (ret)
		वापस ret;

	ret = usb_role_चयन_set_role(typec->ports[port_num]->role_sw,
					pd_ctrl->role & PD_CTRL_RESP_ROLE_DATA
					? USB_ROLE_HOST : USB_ROLE_DEVICE);
	अगर (ret)
		वापस ret;

	अगर (mux_flags & USB_PD_MUX_USB4_ENABLED) अणु
		ret = cros_typec_enable_usb4(typec, port_num, pd_ctrl);
	पूर्ण अन्यथा अगर (mux_flags & USB_PD_MUX_TBT_COMPAT_ENABLED) अणु
		ret = cros_typec_enable_tbt(typec, port_num, pd_ctrl);
	पूर्ण अन्यथा अगर (mux_flags & USB_PD_MUX_DP_ENABLED) अणु
		ret = cros_typec_enable_dp(typec, port_num, pd_ctrl);
	पूर्ण अन्यथा अगर (mux_flags & USB_PD_MUX_SAFE_MODE) अणु
		ret = cros_typec_usb_safe_state(port);
	पूर्ण अन्यथा अगर (mux_flags & USB_PD_MUX_USB_ENABLED) अणु
		port->state.alt = शून्य;
		port->state.mode = TYPEC_STATE_USB;
		ret = typec_mux_set(port->mux, &port->state);
	पूर्ण अन्यथा अणु
		dev_dbg(typec->dev,
			"Unrecognized mode requested, mux flags: %x\n",
			mux_flags);
	पूर्ण

mux_ack:
	अगर (!typec->needs_mux_ack)
		वापस ret;

	/* Sending Acknowledgment to EC */
	mux_ack.port = port_num;

	अगर (cros_typec_ec_command(typec, 0, EC_CMD_USB_PD_MUX_ACK, &mux_ack,
				  माप(mux_ack), शून्य, 0) < 0)
		dev_warn(typec->dev,
			 "Failed to send Mux ACK to EC for port: %d\n",
			 port_num);

	वापस ret;
पूर्ण

अटल व्योम cros_typec_set_port_params_v0(काष्ठा cros_typec_data *typec,
		पूर्णांक port_num, काष्ठा ec_response_usb_pd_control *resp)
अणु
	काष्ठा typec_port *port = typec->ports[port_num]->port;
	क्रमागत typec_orientation polarity;

	अगर (!resp->enabled)
		polarity = TYPEC_ORIENTATION_NONE;
	अन्यथा अगर (!resp->polarity)
		polarity = TYPEC_ORIENTATION_NORMAL;
	अन्यथा
		polarity = TYPEC_ORIENTATION_REVERSE;

	typec_set_pwr_role(port, resp->role ? TYPEC_SOURCE : TYPEC_SINK);
	typec_set_orientation(port, polarity);
पूर्ण

अटल व्योम cros_typec_set_port_params_v1(काष्ठा cros_typec_data *typec,
		पूर्णांक port_num, काष्ठा ec_response_usb_pd_control_v1 *resp)
अणु
	काष्ठा typec_port *port = typec->ports[port_num]->port;
	क्रमागत typec_orientation polarity;
	bool pd_en;
	पूर्णांक ret;

	अगर (!(resp->enabled & PD_CTRL_RESP_ENABLED_CONNECTED))
		polarity = TYPEC_ORIENTATION_NONE;
	अन्यथा अगर (!resp->polarity)
		polarity = TYPEC_ORIENTATION_NORMAL;
	अन्यथा
		polarity = TYPEC_ORIENTATION_REVERSE;
	typec_set_orientation(port, polarity);
	typec_set_data_role(port, resp->role & PD_CTRL_RESP_ROLE_DATA ?
			TYPEC_HOST : TYPEC_DEVICE);
	typec_set_pwr_role(port, resp->role & PD_CTRL_RESP_ROLE_POWER ?
			TYPEC_SOURCE : TYPEC_SINK);
	typec_set_vconn_role(port, resp->role & PD_CTRL_RESP_ROLE_VCONN ?
			TYPEC_SOURCE : TYPEC_SINK);

	/* Register/हटाओ partners when a connect/disconnect occurs. */
	अगर (resp->enabled & PD_CTRL_RESP_ENABLED_CONNECTED) अणु
		अगर (typec->ports[port_num]->partner)
			वापस;

		pd_en = resp->enabled & PD_CTRL_RESP_ENABLED_PD_CAPABLE;
		ret = cros_typec_add_partner(typec, port_num, pd_en);
		अगर (ret)
			dev_warn(typec->dev,
				 "Failed to register partner on port: %d\n",
				 port_num);
	पूर्ण अन्यथा अणु
		cros_typec_हटाओ_partner(typec, port_num);
		cros_typec_हटाओ_cable(typec, port_num);
	पूर्ण
पूर्ण

अटल पूर्णांक cros_typec_get_mux_info(काष्ठा cros_typec_data *typec, पूर्णांक port_num,
				   काष्ठा ec_response_usb_pd_mux_info *resp)
अणु
	काष्ठा ec_params_usb_pd_mux_info req = अणु
		.port = port_num,
	पूर्ण;

	वापस cros_typec_ec_command(typec, 0, EC_CMD_USB_PD_MUX_INFO, &req,
				     माप(req), resp, माप(*resp));
पूर्ण

/*
 * Helper function to रेजिस्टर partner/plug alपंचांगodes.
 */
अटल पूर्णांक cros_typec_रेजिस्टर_alपंचांगodes(काष्ठा cros_typec_data *typec, पूर्णांक port_num,
					bool is_partner)
अणु
	काष्ठा cros_typec_port *port = typec->ports[port_num];
	काष्ठा ec_response_typec_discovery *sop_disc = port->disc_data;
	काष्ठा cros_typec_alपंचांगode_node *node;
	काष्ठा typec_alपंचांगode_desc desc;
	काष्ठा typec_alपंचांगode *amode;
	पूर्णांक num_alपंचांगodes = 0;
	पूर्णांक ret = 0;
	पूर्णांक i, j;

	क्रम (i = 0; i < sop_disc->svid_count; i++) अणु
		क्रम (j = 0; j < sop_disc->svids[i].mode_count; j++) अणु
			स_रखो(&desc, 0, माप(desc));
			desc.svid = sop_disc->svids[i].svid;
			desc.mode = j;
			desc.vकरो = sop_disc->svids[i].mode_vकरो[j];

			अगर (is_partner)
				amode = typec_partner_रेजिस्टर_alपंचांगode(port->partner, &desc);
			अन्यथा
				amode = typec_plug_रेजिस्टर_alपंचांगode(port->plug, &desc);

			अगर (IS_ERR(amode)) अणु
				ret = PTR_ERR(amode);
				जाओ err_cleanup;
			पूर्ण

			/* If no memory is available we should unरेजिस्टर and निकास. */
			node = devm_kzalloc(typec->dev, माप(*node), GFP_KERNEL);
			अगर (!node) अणु
				ret = -ENOMEM;
				typec_unरेजिस्टर_alपंचांगode(amode);
				जाओ err_cleanup;
			पूर्ण

			node->amode = amode;

			अगर (is_partner)
				list_add_tail(&node->list, &port->partner_mode_list);
			अन्यथा
				list_add_tail(&node->list, &port->plug_mode_list);
			num_alपंचांगodes++;
		पूर्ण
	पूर्ण

	अगर (is_partner)
		ret = typec_partner_set_num_alपंचांगodes(port->partner, num_alपंचांगodes);
	अन्यथा
		ret = typec_plug_set_num_alपंचांगodes(port->plug, num_alपंचांगodes);

	अगर (ret < 0) अणु
		dev_err(typec->dev, "Unable to set %s num_altmodes for port: %d\n",
			is_partner ? "partner" : "plug", port_num);
		जाओ err_cleanup;
	पूर्ण

	वापस 0;

err_cleanup:
	cros_typec_unरेजिस्टर_alपंचांगodes(typec, port_num, is_partner);
	वापस ret;
पूर्ण

/*
 * Parse the PD identity data from the EC PD discovery responses and copy that to the supplied
 * PD identity काष्ठा.
 */
अटल व्योम cros_typec_parse_pd_identity(काष्ठा usb_pd_identity *id,
					 काष्ठा ec_response_typec_discovery *disc)
अणु
	पूर्णांक i;

	/* First, update the PD identity VDOs क्रम the partner. */
	अगर (disc->identity_count > 0)
		id->id_header = disc->discovery_vकरो[0];
	अगर (disc->identity_count > 1)
		id->cert_stat = disc->discovery_vकरो[1];
	अगर (disc->identity_count > 2)
		id->product = disc->discovery_vकरो[2];

	/* Copy the reमुख्यing identity VDOs till a maximum of 6. */
	क्रम (i = 3; i < disc->identity_count && i < VDO_MAX_OBJECTS; i++)
		id->vकरो[i - 3] = disc->discovery_vकरो[i];
पूर्ण

अटल पूर्णांक cros_typec_handle_sop_prime_disc(काष्ठा cros_typec_data *typec, पूर्णांक port_num, u16 pd_revision)
अणु
	काष्ठा cros_typec_port *port = typec->ports[port_num];
	काष्ठा ec_response_typec_discovery *disc = port->disc_data;
	काष्ठा typec_cable_desc c_desc = अणुपूर्ण;
	काष्ठा typec_plug_desc p_desc;
	काष्ठा ec_params_typec_discovery req = अणु
		.port = port_num,
		.partner_type = TYPEC_PARTNER_SOP_PRIME,
	पूर्ण;
	u32 cable_plug_type;
	पूर्णांक ret = 0;

	स_रखो(disc, 0, EC_PROTO2_MAX_RESPONSE_SIZE);
	ret = cros_typec_ec_command(typec, 0, EC_CMD_TYPEC_DISCOVERY, &req, माप(req),
				    disc, EC_PROTO2_MAX_RESPONSE_SIZE);
	अगर (ret < 0) अणु
		dev_err(typec->dev, "Failed to get SOP' discovery data for port: %d\n", port_num);
		जाओ sop_prime_disc_निकास;
	पूर्ण

	/* Parse the PD identity data, even अगर only 0s were वापसed. */
	cros_typec_parse_pd_identity(&port->c_identity, disc);

	अगर (disc->identity_count != 0) अणु
		cable_plug_type = VDO_TYPEC_CABLE_TYPE(port->c_identity.vकरो[0]);
		चयन (cable_plug_type) अणु
		हाल CABLE_ATYPE:
			c_desc.type = USB_PLUG_TYPE_A;
			अवरोध;
		हाल CABLE_BTYPE:
			c_desc.type = USB_PLUG_TYPE_B;
			अवरोध;
		हाल CABLE_CTYPE:
			c_desc.type = USB_PLUG_TYPE_C;
			अवरोध;
		हाल CABLE_CAPTIVE:
			c_desc.type = USB_PLUG_CAPTIVE;
			अवरोध;
		शेष:
			c_desc.type = USB_PLUG_NONE;
		पूर्ण
		c_desc.active = PD_IDH_PTYPE(port->c_identity.id_header) == IDH_PTYPE_ACABLE;
	पूर्ण

	c_desc.identity = &port->c_identity;
	c_desc.pd_revision = pd_revision;

	port->cable = typec_रेजिस्टर_cable(port->port, &c_desc);
	अगर (IS_ERR(port->cable)) अणु
		ret = PTR_ERR(port->cable);
		port->cable = शून्य;
		जाओ sop_prime_disc_निकास;
	पूर्ण

	p_desc.index = TYPEC_PLUG_SOP_P;
	port->plug = typec_रेजिस्टर_plug(port->cable, &p_desc);
	अगर (IS_ERR(port->plug)) अणु
		ret = PTR_ERR(port->plug);
		port->plug = शून्य;
		जाओ sop_prime_disc_निकास;
	पूर्ण

	ret = cros_typec_रेजिस्टर_alपंचांगodes(typec, port_num, false);
	अगर (ret < 0) अणु
		dev_err(typec->dev, "Failed to register plug altmodes, port: %d\n", port_num);
		जाओ sop_prime_disc_निकास;
	पूर्ण

	वापस 0;

sop_prime_disc_निकास:
	cros_typec_हटाओ_cable(typec, port_num);
	वापस ret;
पूर्ण

अटल पूर्णांक cros_typec_handle_sop_disc(काष्ठा cros_typec_data *typec, पूर्णांक port_num, u16 pd_revision)
अणु
	काष्ठा cros_typec_port *port = typec->ports[port_num];
	काष्ठा ec_response_typec_discovery *sop_disc = port->disc_data;
	काष्ठा ec_params_typec_discovery req = अणु
		.port = port_num,
		.partner_type = TYPEC_PARTNER_SOP,
	पूर्ण;
	पूर्णांक ret = 0;

	अगर (!port->partner) अणु
		dev_err(typec->dev,
			"SOP Discovery received without partner registered, port: %d\n",
			port_num);
		ret = -EINVAL;
		जाओ disc_निकास;
	पूर्ण

	typec_partner_set_pd_revision(port->partner, pd_revision);

	स_रखो(sop_disc, 0, EC_PROTO2_MAX_RESPONSE_SIZE);
	ret = cros_typec_ec_command(typec, 0, EC_CMD_TYPEC_DISCOVERY, &req, माप(req),
				    sop_disc, EC_PROTO2_MAX_RESPONSE_SIZE);
	अगर (ret < 0) अणु
		dev_err(typec->dev, "Failed to get SOP discovery data for port: %d\n", port_num);
		जाओ disc_निकास;
	पूर्ण

	cros_typec_parse_pd_identity(&port->p_identity, sop_disc);

	ret = typec_partner_set_identity(port->partner);
	अगर (ret < 0) अणु
		dev_err(typec->dev, "Failed to update partner PD identity, port: %d\n", port_num);
		जाओ disc_निकास;
	पूर्ण

	ret = cros_typec_रेजिस्टर_alपंचांगodes(typec, port_num, true);
	अगर (ret < 0) अणु
		dev_err(typec->dev, "Failed to register partner altmodes, port: %d\n", port_num);
		जाओ disc_निकास;
	पूर्ण

disc_निकास:
	वापस ret;
पूर्ण

अटल पूर्णांक cros_typec_send_clear_event(काष्ठा cros_typec_data *typec, पूर्णांक port_num, u32 events_mask)
अणु
	काष्ठा ec_params_typec_control req = अणु
		.port = port_num,
		.command = TYPEC_CONTROL_COMMAND_CLEAR_EVENTS,
		.clear_events_mask = events_mask,
	पूर्ण;

	वापस cros_typec_ec_command(typec, 0, EC_CMD_TYPEC_CONTROL, &req,
				     माप(req), शून्य, 0);
पूर्ण

अटल व्योम cros_typec_handle_status(काष्ठा cros_typec_data *typec, पूर्णांक port_num)
अणु
	काष्ठा ec_response_typec_status resp;
	काष्ठा ec_params_typec_status req = अणु
		.port = port_num,
	पूर्ण;
	पूर्णांक ret;

	ret = cros_typec_ec_command(typec, 0, EC_CMD_TYPEC_STATUS, &req, माप(req),
				    &resp, माप(resp));
	अगर (ret < 0) अणु
		dev_warn(typec->dev, "EC_CMD_TYPEC_STATUS failed for port: %d\n", port_num);
		वापस;
	पूर्ण

	/* If we got a hard reset, unरेजिस्टर everything and वापस. */
	अगर (resp.events & PD_STATUS_EVENT_HARD_RESET) अणु
		cros_typec_हटाओ_partner(typec, port_num);
		cros_typec_हटाओ_cable(typec, port_num);

		ret = cros_typec_send_clear_event(typec, port_num,
						  PD_STATUS_EVENT_HARD_RESET);
		अगर (ret < 0)
			dev_warn(typec->dev,
				 "Failed hard reset event clear, port: %d\n", port_num);
		वापस;
	पूर्ण

	/* Handle any events appropriately. */
	अगर (resp.events & PD_STATUS_EVENT_SOP_DISC_DONE && !typec->ports[port_num]->sop_disc_करोne) अणु
		u16 sop_revision;

		/* Convert BCD to the क्रमmat preferred by the TypeC framework */
		sop_revision = (le16_to_cpu(resp.sop_revision) & 0xff00) >> 4;
		ret = cros_typec_handle_sop_disc(typec, port_num, sop_revision);
		अगर (ret < 0)
			dev_err(typec->dev, "Couldn't parse SOP Disc data, port: %d\n", port_num);
		अन्यथा अणु
			typec->ports[port_num]->sop_disc_करोne = true;
			ret = cros_typec_send_clear_event(typec, port_num,
							  PD_STATUS_EVENT_SOP_DISC_DONE);
			अगर (ret < 0)
				dev_warn(typec->dev,
					 "Failed SOP Disc event clear, port: %d\n", port_num);
		पूर्ण
		अगर (resp.sop_connected)
			typec_set_pwr_opmode(typec->ports[port_num]->port, TYPEC_PWR_MODE_PD);
	पूर्ण

	अगर (resp.events & PD_STATUS_EVENT_SOP_PRIME_DISC_DONE &&
	    !typec->ports[port_num]->sop_prime_disc_करोne) अणु
		u16 sop_prime_revision;

		/* Convert BCD to the क्रमmat preferred by the TypeC framework */
		sop_prime_revision = (le16_to_cpu(resp.sop_prime_revision) & 0xff00) >> 4;
		ret = cros_typec_handle_sop_prime_disc(typec, port_num, sop_prime_revision);
		अगर (ret < 0)
			dev_err(typec->dev, "Couldn't parse SOP' Disc data, port: %d\n", port_num);
		अन्यथा अणु
			typec->ports[port_num]->sop_prime_disc_करोne = true;
			ret = cros_typec_send_clear_event(typec, port_num,
							  PD_STATUS_EVENT_SOP_PRIME_DISC_DONE);
			अगर (ret < 0)
				dev_warn(typec->dev,
					 "Failed SOP Disc event clear, port: %d\n", port_num);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक cros_typec_port_update(काष्ठा cros_typec_data *typec, पूर्णांक port_num)
अणु
	काष्ठा ec_params_usb_pd_control req;
	काष्ठा ec_response_usb_pd_control_v2 resp;
	काष्ठा ec_response_usb_pd_mux_info mux_resp;
	पूर्णांक ret;

	अगर (port_num < 0 || port_num >= typec->num_ports) अणु
		dev_err(typec->dev, "cannot get status for invalid port %d\n",
			port_num);
		वापस -EINVAL;
	पूर्ण

	req.port = port_num;
	req.role = USB_PD_CTRL_ROLE_NO_CHANGE;
	req.mux = USB_PD_CTRL_MUX_NO_CHANGE;
	req.swap = USB_PD_CTRL_SWAP_NONE;

	ret = cros_typec_ec_command(typec, typec->pd_ctrl_ver,
				    EC_CMD_USB_PD_CONTROL, &req, माप(req),
				    &resp, माप(resp));
	अगर (ret < 0)
		वापस ret;

	dev_dbg(typec->dev, "Enabled %d: 0x%hhx\n", port_num, resp.enabled);
	dev_dbg(typec->dev, "Role %d: 0x%hhx\n", port_num, resp.role);
	dev_dbg(typec->dev, "Polarity %d: 0x%hhx\n", port_num, resp.polarity);
	dev_dbg(typec->dev, "State %d: %s\n", port_num, resp.state);

	अगर (typec->pd_ctrl_ver != 0)
		cros_typec_set_port_params_v1(typec, port_num,
			(काष्ठा ec_response_usb_pd_control_v1 *)&resp);
	अन्यथा
		cros_typec_set_port_params_v0(typec, port_num,
			(काष्ठा ec_response_usb_pd_control *) &resp);

	अगर (typec->typec_cmd_supported)
		cros_typec_handle_status(typec, port_num);

	/* Update the चयनes अगर they exist, according to requested state */
	ret = cros_typec_get_mux_info(typec, port_num, &mux_resp);
	अगर (ret < 0) अणु
		dev_warn(typec->dev,
			 "Failed to get mux info for port: %d, err = %d\n",
			 port_num, ret);
		वापस 0;
	पूर्ण

	/* No change needs to be made, let's निकास early. */
	अगर (typec->ports[port_num]->mux_flags == mux_resp.flags &&
	    typec->ports[port_num]->role == resp.role)
		वापस 0;

	typec->ports[port_num]->mux_flags = mux_resp.flags;
	typec->ports[port_num]->role = resp.role;
	ret = cros_typec_configure_mux(typec, port_num, mux_resp.flags, &resp);
	अगर (ret)
		dev_warn(typec->dev, "Configure muxes failed, err = %d\n", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक cros_typec_get_cmd_version(काष्ठा cros_typec_data *typec)
अणु
	काष्ठा ec_params_get_cmd_versions_v1 req_v1;
	काष्ठा ec_response_get_cmd_versions resp;
	पूर्णांक ret;

	/* We're पूर्णांकerested in the PD control command version. */
	req_v1.cmd = EC_CMD_USB_PD_CONTROL;
	ret = cros_typec_ec_command(typec, 1, EC_CMD_GET_CMD_VERSIONS,
				    &req_v1, माप(req_v1), &resp,
				    माप(resp));
	अगर (ret < 0)
		वापस ret;

	अगर (resp.version_mask & EC_VER_MASK(2))
		typec->pd_ctrl_ver = 2;
	अन्यथा अगर (resp.version_mask & EC_VER_MASK(1))
		typec->pd_ctrl_ver = 1;
	अन्यथा
		typec->pd_ctrl_ver = 0;

	dev_dbg(typec->dev, "PD Control has version mask 0x%02x\n",
		typec->pd_ctrl_ver & 0xff);

	वापस 0;
पूर्ण

/* Check the EC feature flags to see अगर TYPEC_* features are supported. */
अटल पूर्णांक cros_typec_feature_supported(काष्ठा cros_typec_data *typec, क्रमागत ec_feature_code feature)
अणु
	काष्ठा ec_response_get_features resp = अणुपूर्ण;
	पूर्णांक ret;

	ret = cros_typec_ec_command(typec, 0, EC_CMD_GET_FEATURES, शून्य, 0,
				    &resp, माप(resp));
	अगर (ret < 0) अणु
		dev_warn(typec->dev,
			 "Failed to get features, assuming typec feature=%d unsupported.\n",
			 feature);
		वापस 0;
	पूर्ण

	वापस resp.flags[feature / 32] & EC_FEATURE_MASK_1(feature);
पूर्ण

अटल व्योम cros_typec_port_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा cros_typec_data *typec = container_of(work, काष्ठा cros_typec_data, port_work);
	पूर्णांक ret, i;

	क्रम (i = 0; i < typec->num_ports; i++) अणु
		ret = cros_typec_port_update(typec, i);
		अगर (ret < 0)
			dev_warn(typec->dev, "Update failed for port: %d\n", i);
	पूर्ण
पूर्ण

अटल पूर्णांक cros_ec_typec_event(काष्ठा notअगरier_block *nb,
			       अचिन्हित दीर्घ host_event, व्योम *_notअगरy)
अणु
	काष्ठा cros_typec_data *typec = container_of(nb, काष्ठा cros_typec_data, nb);

	flush_work(&typec->port_work);
	schedule_work(&typec->port_work);

	वापस NOTIFY_OK;
पूर्ण

#अगर_घोषित CONFIG_ACPI
अटल स्थिर काष्ठा acpi_device_id cros_typec_acpi_id[] = अणु
	अणु "GOOG0014", 0 पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(acpi, cros_typec_acpi_id);
#पूर्ण_अगर

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id cros_typec_of_match[] = अणु
	अणु .compatible = "google,cros-ec-typec", पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, cros_typec_of_match);
#पूर्ण_अगर

अटल पूर्णांक cros_typec_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा cros_typec_data *typec;
	काष्ठा ec_response_usb_pd_ports resp;
	पूर्णांक ret, i;

	typec = devm_kzalloc(dev, माप(*typec), GFP_KERNEL);
	अगर (!typec)
		वापस -ENOMEM;

	typec->dev = dev;
	typec->ec = dev_get_drvdata(pdev->dev.parent);
	platक्रमm_set_drvdata(pdev, typec);

	ret = cros_typec_get_cmd_version(typec);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to get PD command version info\n");
		वापस ret;
	पूर्ण

	typec->typec_cmd_supported = !!cros_typec_feature_supported(typec,
					EC_FEATURE_TYPEC_CMD);
	typec->needs_mux_ack = !!cros_typec_feature_supported(typec,
					EC_FEATURE_TYPEC_MUX_REQUIRE_AP_ACK);

	ret = cros_typec_ec_command(typec, 0, EC_CMD_USB_PD_PORTS, शून्य, 0,
				    &resp, माप(resp));
	अगर (ret < 0)
		वापस ret;

	typec->num_ports = resp.num_ports;
	अगर (typec->num_ports > EC_USB_PD_MAX_PORTS) अणु
		dev_warn(typec->dev,
			 "Too many ports reported: %d, limiting to max: %d\n",
			 typec->num_ports, EC_USB_PD_MAX_PORTS);
		typec->num_ports = EC_USB_PD_MAX_PORTS;
	पूर्ण

	ret = cros_typec_init_ports(typec);
	अगर (ret < 0)
		वापस ret;

	INIT_WORK(&typec->port_work, cros_typec_port_work);

	/*
	 * Safe to call port update here, since we haven't रेजिस्टरed the
	 * PD notअगरier yet.
	 */
	क्रम (i = 0; i < typec->num_ports; i++) अणु
		ret = cros_typec_port_update(typec, i);
		अगर (ret < 0)
			जाओ unरेजिस्टर_ports;
	पूर्ण

	typec->nb.notअगरier_call = cros_ec_typec_event;
	ret = cros_usbpd_रेजिस्टर_notअगरy(&typec->nb);
	अगर (ret < 0)
		जाओ unरेजिस्टर_ports;

	वापस 0;

unरेजिस्टर_ports:
	cros_unरेजिस्टर_ports(typec);
	वापस ret;
पूर्ण

अटल पूर्णांक __maybe_unused cros_typec_suspend(काष्ठा device *dev)
अणु
	काष्ठा cros_typec_data *typec = dev_get_drvdata(dev);

	cancel_work_sync(&typec->port_work);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused cros_typec_resume(काष्ठा device *dev)
अणु
	काष्ठा cros_typec_data *typec = dev_get_drvdata(dev);

	/* Refresh port state. */
	schedule_work(&typec->port_work);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops cros_typec_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(cros_typec_suspend, cros_typec_resume)
पूर्ण;

अटल काष्ठा platक्रमm_driver cros_typec_driver = अणु
	.driver	= अणु
		.name = DRV_NAME,
		.acpi_match_table = ACPI_PTR(cros_typec_acpi_id),
		.of_match_table = of_match_ptr(cros_typec_of_match),
		.pm = &cros_typec_pm_ops,
	पूर्ण,
	.probe = cros_typec_probe,
पूर्ण;

module_platक्रमm_driver(cros_typec_driver);

MODULE_AUTHOR("Prashant Malani <pmalani@chromium.org>");
MODULE_DESCRIPTION("Chrome OS EC Type C control");
MODULE_LICENSE("GPL");
