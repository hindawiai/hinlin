<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Driver क्रम Intel PMC USB mux control
 *
 * Copyright (C) 2020 Intel Corporation
 * Author: Heikki Krogerus <heikki.krogerus@linux.पूर्णांकel.com>
 */

#समावेश <linux/acpi.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/property.h>
#समावेश <linux/usb/pd.h>
#समावेश <linux/usb/role.h>
#समावेश <linux/usb/typec_mux.h>
#समावेश <linux/usb/typec_dp.h>
#समावेश <linux/usb/typec_tbt.h>

#समावेश <यंत्र/पूर्णांकel_scu_ipc.h>

#घोषणा PMC_USBC_CMD		0xa7

/* Response status bits */
#घोषणा PMC_USB_RESP_STATUS_FAILURE	BIT(0)
#घोषणा PMC_USB_RESP_STATUS_FATAL	BIT(1)

/* "Usage" OOB Message field values */
क्रमागत अणु
	PMC_USB_CONNECT,
	PMC_USB_DISCONNECT,
	PMC_USB_SAFE_MODE,
	PMC_USB_ALT_MODE,
	PMC_USB_DP_HPD,
पूर्ण;

#घोषणा PMC_USB_MSG_USB2_PORT_SHIFT	0
#घोषणा PMC_USB_MSG_USB3_PORT_SHIFT	4
#घोषणा PMC_USB_MSG_UFP_SHIFT		4
#घोषणा PMC_USB_MSG_ORI_HSL_SHIFT	5
#घोषणा PMC_USB_MSG_ORI_AUX_SHIFT	6

/* Alt Mode Request */
काष्ठा alपंचांगode_req अणु
	u8 usage;
	u8 mode_type;
	u8 mode_id;
	u8 reserved;
	u32 mode_data;
पूर्ण __packed;

#घोषणा PMC_USB_MODE_TYPE_SHIFT		4

क्रमागत अणु
	PMC_USB_MODE_TYPE_USB,
	PMC_USB_MODE_TYPE_DP,
	PMC_USB_MODE_TYPE_TBT,
पूर्ण;

/* Common Mode Data bits */
#घोषणा PMC_USB_ALTMODE_ACTIVE_CABLE	BIT(2)

#घोषणा PMC_USB_ALTMODE_ORI_SHIFT	1
#घोषणा PMC_USB_ALTMODE_UFP_SHIFT	3

/* DP specअगरic Mode Data bits */
#घोषणा PMC_USB_ALTMODE_DP_MODE_SHIFT	8

/* TBT specअगरic Mode Data bits */
#घोषणा PMC_USB_ALTMODE_TBT_TYPE	BIT(17)
#घोषणा PMC_USB_ALTMODE_CABLE_TYPE	BIT(18)
#घोषणा PMC_USB_ALTMODE_ACTIVE_LINK	BIT(20)
#घोषणा PMC_USB_ALTMODE_FORCE_LSR	BIT(23)
#घोषणा PMC_USB_ALTMODE_CABLE_SPD(_s_)	(((_s_) & GENMASK(2, 0)) << 25)
#घोषणा   PMC_USB_ALTMODE_CABLE_USB31	1
#घोषणा   PMC_USB_ALTMODE_CABLE_10GPS	2
#घोषणा   PMC_USB_ALTMODE_CABLE_20GPS	3
#घोषणा PMC_USB_ALTMODE_TBT_GEN(_g_)	(((_g_) & GENMASK(1, 0)) << 28)

/* Display HPD Request bits */
#घोषणा PMC_USB_DP_HPD_LVL		BIT(4)
#घोषणा PMC_USB_DP_HPD_IRQ		BIT(5)

/*
 * Input Output Manager (IOM) PORT STATUS
 */
#घोषणा IOM_PORT_STATUS_OFFSET				0x560

#घोषणा IOM_PORT_STATUS_ACTIVITY_TYPE_MASK		GENMASK(9, 6)
#घोषणा IOM_PORT_STATUS_ACTIVITY_TYPE_SHIFT		6
#घोषणा IOM_PORT_STATUS_ACTIVITY_TYPE_USB		0x03
/* activity type: Safe Mode */
#घोषणा IOM_PORT_STATUS_ACTIVITY_TYPE_SAFE_MODE		0x04
/* activity type: Display Port */
#घोषणा IOM_PORT_STATUS_ACTIVITY_TYPE_DP		0x05
/* activity type: Display Port Multi Function Device */
#घोषणा IOM_PORT_STATUS_ACTIVITY_TYPE_DP_MFD		0x06
/* activity type: Thunderbolt */
#घोषणा IOM_PORT_STATUS_ACTIVITY_TYPE_TBT		0x07
#घोषणा IOM_PORT_STATUS_ACTIVITY_TYPE_ALT_MODE_USB	0x0c
#घोषणा IOM_PORT_STATUS_ACTIVITY_TYPE_ALT_MODE_TBT_USB	0x0d
/* Upstream Facing Port Inक्रमmation */
#घोषणा IOM_PORT_STATUS_UFP				BIT(10)
/* Display Port Hot Plug Detect status */
#घोषणा IOM_PORT_STATUS_DHPD_HPD_STATUS_MASK		GENMASK(13, 12)
#घोषणा IOM_PORT_STATUS_DHPD_HPD_STATUS_SHIFT		12
#घोषणा IOM_PORT_STATUS_DHPD_HPD_STATUS_ASSERT		0x01
#घोषणा IOM_PORT_STATUS_DHPD_HPD_SOURCE_TBT		BIT(14)
#घोषणा IOM_PORT_STATUS_CONNECTED			BIT(31)

#घोषणा IOM_PORT_ACTIVITY_IS(_status_, _type_)				\
	((((_status_) & IOM_PORT_STATUS_ACTIVITY_TYPE_MASK) >>		\
	  IOM_PORT_STATUS_ACTIVITY_TYPE_SHIFT) ==			\
	 (IOM_PORT_STATUS_ACTIVITY_TYPE_##_type_))

#घोषणा IOM_PORT_HPD_ASSERTED(_status_)					\
	((((_status_) & IOM_PORT_STATUS_DHPD_HPD_STATUS_MASK) >>	\
	  IOM_PORT_STATUS_DHPD_HPD_STATUS_SHIFT) &			\
	 IOM_PORT_STATUS_DHPD_HPD_STATUS_ASSERT)

काष्ठा pmc_usb;

काष्ठा pmc_usb_port अणु
	पूर्णांक num;
	u32 iom_status;
	काष्ठा pmc_usb *pmc;
	काष्ठा typec_mux *typec_mux;
	काष्ठा typec_चयन *typec_sw;
	काष्ठा usb_role_चयन *usb_sw;

	क्रमागत typec_orientation orientation;
	क्रमागत usb_role role;

	u8 usb2_port;
	u8 usb3_port;

	क्रमागत typec_orientation sbu_orientation;
	क्रमागत typec_orientation hsl_orientation;
पूर्ण;

काष्ठा pmc_usb अणु
	u8 num_ports;
	काष्ठा device *dev;
	काष्ठा पूर्णांकel_scu_ipc_dev *ipc;
	काष्ठा pmc_usb_port *port;
	काष्ठा acpi_device *iom_adev;
	व्योम __iomem *iom_base;
पूर्ण;

अटल व्योम update_port_status(काष्ठा pmc_usb_port *port)
अणु
	u8 port_num;

	/* SoC expects the USB Type-C port numbers to start with 0 */
	port_num = port->usb3_port - 1;

	port->iom_status = पढ़ोl(port->pmc->iom_base + IOM_PORT_STATUS_OFFSET +
				 port_num * माप(u32));
पूर्ण

अटल पूर्णांक sbu_orientation(काष्ठा pmc_usb_port *port)
अणु
	अगर (port->sbu_orientation)
		वापस port->sbu_orientation - 1;

	वापस port->orientation - 1;
पूर्ण

अटल पूर्णांक hsl_orientation(काष्ठा pmc_usb_port *port)
अणु
	अगर (port->hsl_orientation)
		वापस port->hsl_orientation - 1;

	वापस port->orientation - 1;
पूर्ण

अटल पूर्णांक pmc_usb_command(काष्ठा pmc_usb_port *port, u8 *msg, u32 len)
अणु
	u8 response[4];
	u8 status_res;
	पूर्णांक ret;

	/*
	 * Error bit will always be 0 with the USBC command.
	 * Status can be checked from the response message अगर the
	 * function पूर्णांकel_scu_ipc_dev_command succeeds.
	 */
	ret = पूर्णांकel_scu_ipc_dev_command(port->pmc->ipc, PMC_USBC_CMD, 0, msg,
					len, response, माप(response));

	अगर (ret)
		वापस ret;

	status_res = (msg[0] & 0xf) < PMC_USB_SAFE_MODE ?
		     response[2] : response[1];

	अगर (status_res & PMC_USB_RESP_STATUS_FAILURE) अणु
		अगर (status_res & PMC_USB_RESP_STATUS_FATAL)
			वापस -EIO;

		वापस -EBUSY;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
pmc_usb_mux_dp_hpd(काष्ठा pmc_usb_port *port, काष्ठा typec_displayport_data *dp)
अणु
	u8 msg[2] = अणु पूर्ण;
	पूर्णांक ret;

	msg[0] = PMC_USB_DP_HPD;
	msg[0] |= port->usb3_port << PMC_USB_MSG_USB3_PORT_SHIFT;

	/* Configure HPD first अगर HPD,IRQ comes together */
	अगर (!IOM_PORT_HPD_ASSERTED(port->iom_status) &&
	    dp->status & DP_STATUS_IRQ_HPD &&
	    dp->status & DP_STATUS_HPD_STATE) अणु
		msg[1] = PMC_USB_DP_HPD_LVL;
		ret = pmc_usb_command(port, msg, माप(msg));
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (dp->status & DP_STATUS_IRQ_HPD)
		msg[1] = PMC_USB_DP_HPD_IRQ;

	अगर (dp->status & DP_STATUS_HPD_STATE)
		msg[1] |= PMC_USB_DP_HPD_LVL;

	वापस pmc_usb_command(port, msg, माप(msg));
पूर्ण

अटल पूर्णांक
pmc_usb_mux_dp(काष्ठा pmc_usb_port *port, काष्ठा typec_mux_state *state)
अणु
	काष्ठा typec_displayport_data *data = state->data;
	काष्ठा alपंचांगode_req req = अणु पूर्ण;
	पूर्णांक ret;

	अगर (IOM_PORT_ACTIVITY_IS(port->iom_status, DP) ||
	    IOM_PORT_ACTIVITY_IS(port->iom_status, DP_MFD)) अणु
		अगर (IOM_PORT_HPD_ASSERTED(port->iom_status) &&
		    (!(data->status & DP_STATUS_IRQ_HPD) &&
		     data->status & DP_STATUS_HPD_STATE))
			वापस 0;

		वापस pmc_usb_mux_dp_hpd(port, state->data);
	पूर्ण

	req.usage = PMC_USB_ALT_MODE;
	req.usage |= port->usb3_port << PMC_USB_MSG_USB3_PORT_SHIFT;
	req.mode_type = PMC_USB_MODE_TYPE_DP << PMC_USB_MODE_TYPE_SHIFT;

	req.mode_data = (port->orientation - 1) << PMC_USB_ALTMODE_ORI_SHIFT;
	req.mode_data |= (port->role - 1) << PMC_USB_ALTMODE_UFP_SHIFT;

	req.mode_data |= (state->mode - TYPEC_STATE_MODAL) <<
			 PMC_USB_ALTMODE_DP_MODE_SHIFT;

	ret = pmc_usb_command(port, (व्योम *)&req, माप(req));
	अगर (ret)
		वापस ret;

	अगर (data->status & (DP_STATUS_IRQ_HPD | DP_STATUS_HPD_STATE))
		वापस pmc_usb_mux_dp_hpd(port, state->data);

	वापस 0;
पूर्ण

अटल पूर्णांक
pmc_usb_mux_tbt(काष्ठा pmc_usb_port *port, काष्ठा typec_mux_state *state)
अणु
	काष्ठा typec_thunderbolt_data *data = state->data;
	u8 cable_rounded = TBT_CABLE_ROUNDED_SUPPORT(data->cable_mode);
	u8 cable_speed = TBT_CABLE_SPEED(data->cable_mode);
	काष्ठा alपंचांगode_req req = अणु पूर्ण;

	अगर (IOM_PORT_ACTIVITY_IS(port->iom_status, TBT) ||
	    IOM_PORT_ACTIVITY_IS(port->iom_status, ALT_MODE_TBT_USB))
		वापस 0;

	req.usage = PMC_USB_ALT_MODE;
	req.usage |= port->usb3_port << PMC_USB_MSG_USB3_PORT_SHIFT;
	req.mode_type = PMC_USB_MODE_TYPE_TBT << PMC_USB_MODE_TYPE_SHIFT;

	req.mode_data = (port->orientation - 1) << PMC_USB_ALTMODE_ORI_SHIFT;
	req.mode_data |= (port->role - 1) << PMC_USB_ALTMODE_UFP_SHIFT;

	अगर (TBT_ADAPTER(data->device_mode) == TBT_ADAPTER_TBT3)
		req.mode_data |= PMC_USB_ALTMODE_TBT_TYPE;

	अगर (data->cable_mode & TBT_CABLE_OPTICAL)
		req.mode_data |= PMC_USB_ALTMODE_CABLE_TYPE;

	अगर (data->cable_mode & TBT_CABLE_LINK_TRAINING)
		req.mode_data |= PMC_USB_ALTMODE_ACTIVE_LINK;

	अगर (data->enter_vकरो & TBT_ENTER_MODE_ACTIVE_CABLE)
		req.mode_data |= PMC_USB_ALTMODE_ACTIVE_CABLE;

	req.mode_data |= PMC_USB_ALTMODE_CABLE_SPD(cable_speed);

	req.mode_data |= PMC_USB_ALTMODE_TBT_GEN(cable_rounded);

	वापस pmc_usb_command(port, (व्योम *)&req, माप(req));
पूर्ण

अटल पूर्णांक
pmc_usb_mux_usb4(काष्ठा pmc_usb_port *port, काष्ठा typec_mux_state *state)
अणु
	काष्ठा enter_usb_data *data = state->data;
	काष्ठा alपंचांगode_req req = अणु पूर्ण;
	u8 cable_speed;

	अगर (IOM_PORT_ACTIVITY_IS(port->iom_status, TBT) ||
	    IOM_PORT_ACTIVITY_IS(port->iom_status, ALT_MODE_TBT_USB))
		वापस 0;

	req.usage = PMC_USB_ALT_MODE;
	req.usage |= port->usb3_port << PMC_USB_MSG_USB3_PORT_SHIFT;
	req.mode_type = PMC_USB_MODE_TYPE_TBT << PMC_USB_MODE_TYPE_SHIFT;

	/* USB4 Mode */
	req.mode_data = PMC_USB_ALTMODE_FORCE_LSR;

	अगर (data->active_link_training)
		req.mode_data |= PMC_USB_ALTMODE_ACTIVE_LINK;

	req.mode_data |= (port->orientation - 1) << PMC_USB_ALTMODE_ORI_SHIFT;
	req.mode_data |= (port->role - 1) << PMC_USB_ALTMODE_UFP_SHIFT;

	चयन ((data->euकरो & EUDO_CABLE_TYPE_MASK) >> EUDO_CABLE_TYPE_SHIFT) अणु
	हाल EUDO_CABLE_TYPE_PASSIVE:
		अवरोध;
	हाल EUDO_CABLE_TYPE_OPTICAL:
		req.mode_data |= PMC_USB_ALTMODE_CABLE_TYPE;
		fallthrough;
	शेष:
		req.mode_data |= PMC_USB_ALTMODE_ACTIVE_CABLE;

		/* Configure data rate to rounded in the हाल of Active TBT3
		 * and USB4 cables.
		 */
		req.mode_data |= PMC_USB_ALTMODE_TBT_GEN(1);
		अवरोध;
	पूर्ण

	cable_speed = (data->euकरो & EUDO_CABLE_SPEED_MASK) >> EUDO_CABLE_SPEED_SHIFT;
	req.mode_data |= PMC_USB_ALTMODE_CABLE_SPD(cable_speed);

	वापस pmc_usb_command(port, (व्योम *)&req, माप(req));
पूर्ण

अटल पूर्णांक pmc_usb_mux_safe_state(काष्ठा pmc_usb_port *port)
अणु
	u8 msg;

	अगर (IOM_PORT_ACTIVITY_IS(port->iom_status, SAFE_MODE))
		वापस 0;

	msg = PMC_USB_SAFE_MODE;
	msg |= port->usb3_port << PMC_USB_MSG_USB3_PORT_SHIFT;

	वापस pmc_usb_command(port, &msg, माप(msg));
पूर्ण

अटल पूर्णांक pmc_usb_disconnect(काष्ठा pmc_usb_port *port)
अणु
	काष्ठा typec_displayport_data data = अणु पूर्ण;
	u8 msg[2];

	अगर (!(port->iom_status & IOM_PORT_STATUS_CONNECTED))
		वापस 0;

	/* Clear DisplayPort HPD अगर it's still निश्चितed. */
	अगर (IOM_PORT_HPD_ASSERTED(port->iom_status))
		pmc_usb_mux_dp_hpd(port, &data);

	msg[0] = PMC_USB_DISCONNECT;
	msg[0] |= port->usb3_port << PMC_USB_MSG_USB3_PORT_SHIFT;

	msg[1] = port->usb2_port << PMC_USB_MSG_USB2_PORT_SHIFT;

	वापस pmc_usb_command(port, msg, माप(msg));
पूर्ण

अटल पूर्णांक pmc_usb_connect(काष्ठा pmc_usb_port *port, क्रमागत usb_role role)
अणु
	u8 ufp = role == USB_ROLE_DEVICE ? 1 : 0;
	u8 msg[2];
	पूर्णांक ret;

	अगर (port->orientation == TYPEC_ORIENTATION_NONE)
		वापस -EINVAL;

	अगर (port->iom_status & IOM_PORT_STATUS_CONNECTED) अणु
		अगर (port->role == role || port->role == USB_ROLE_NONE)
			वापस 0;

		/* Role swap */
		ret = pmc_usb_disconnect(port);
		अगर (ret)
			वापस ret;
	पूर्ण

	msg[0] = PMC_USB_CONNECT;
	msg[0] |= port->usb3_port << PMC_USB_MSG_USB3_PORT_SHIFT;

	msg[1] = port->usb2_port << PMC_USB_MSG_USB2_PORT_SHIFT;
	msg[1] |= ufp << PMC_USB_MSG_UFP_SHIFT;
	msg[1] |= hsl_orientation(port) << PMC_USB_MSG_ORI_HSL_SHIFT;
	msg[1] |= sbu_orientation(port) << PMC_USB_MSG_ORI_AUX_SHIFT;

	वापस pmc_usb_command(port, msg, माप(msg));
पूर्ण

अटल पूर्णांक
pmc_usb_mux_set(काष्ठा typec_mux *mux, काष्ठा typec_mux_state *state)
अणु
	काष्ठा pmc_usb_port *port = typec_mux_get_drvdata(mux);

	update_port_status(port);

	अगर (port->orientation == TYPEC_ORIENTATION_NONE || port->role == USB_ROLE_NONE)
		वापस 0;

	अगर (state->mode == TYPEC_STATE_SAFE)
		वापस pmc_usb_mux_safe_state(port);
	अगर (state->mode == TYPEC_STATE_USB)
		वापस pmc_usb_connect(port, port->role);

	अगर (state->alt) अणु
		चयन (state->alt->svid) अणु
		हाल USB_TYPEC_TBT_SID:
			वापस pmc_usb_mux_tbt(port, state);
		हाल USB_TYPEC_DP_SID:
			वापस pmc_usb_mux_dp(port, state);
		पूर्ण
	पूर्ण अन्यथा अणु
		चयन (state->mode) अणु
		हाल TYPEC_MODE_USB2:
			/* REVISIT: Try with usb3_port set to 0? */
			अवरोध;
		हाल TYPEC_MODE_USB3:
			वापस pmc_usb_connect(port, port->role);
		हाल TYPEC_MODE_USB4:
			वापस pmc_usb_mux_usb4(port, state);
		पूर्ण
	पूर्ण

	वापस -EOPNOTSUPP;
पूर्ण

अटल पूर्णांक pmc_usb_set_orientation(काष्ठा typec_चयन *sw,
				   क्रमागत typec_orientation orientation)
अणु
	काष्ठा pmc_usb_port *port = typec_चयन_get_drvdata(sw);

	update_port_status(port);

	port->orientation = orientation;

	वापस 0;
पूर्ण

अटल पूर्णांक pmc_usb_set_role(काष्ठा usb_role_चयन *sw, क्रमागत usb_role role)
अणु
	काष्ठा pmc_usb_port *port = usb_role_चयन_get_drvdata(sw);
	पूर्णांक ret;

	update_port_status(port);

	अगर (role == USB_ROLE_NONE)
		ret = pmc_usb_disconnect(port);
	अन्यथा
		ret = pmc_usb_connect(port, role);

	port->role = role;

	वापस ret;
पूर्ण

अटल पूर्णांक pmc_usb_रेजिस्टर_port(काष्ठा pmc_usb *pmc, पूर्णांक index,
				 काष्ठा fwnode_handle *fwnode)
अणु
	काष्ठा pmc_usb_port *port = &pmc->port[index];
	काष्ठा usb_role_चयन_desc desc = अणु पूर्ण;
	काष्ठा typec_चयन_desc sw_desc = अणु पूर्ण;
	काष्ठा typec_mux_desc mux_desc = अणु पूर्ण;
	स्थिर अक्षर *str;
	पूर्णांक ret;

	ret = fwnode_property_पढ़ो_u8(fwnode, "usb2-port-number", &port->usb2_port);
	अगर (ret)
		वापस ret;

	ret = fwnode_property_पढ़ो_u8(fwnode, "usb3-port-number", &port->usb3_port);
	अगर (ret)
		वापस ret;

	ret = fwnode_property_पढ़ो_string(fwnode, "sbu-orientation", &str);
	अगर (!ret)
		port->sbu_orientation = typec_find_orientation(str);

	ret = fwnode_property_पढ़ो_string(fwnode, "hsl-orientation", &str);
	अगर (!ret)
		port->hsl_orientation = typec_find_orientation(str);

	port->num = index;
	port->pmc = pmc;

	sw_desc.fwnode = fwnode;
	sw_desc.drvdata = port;
	sw_desc.name = fwnode_get_name(fwnode);
	sw_desc.set = pmc_usb_set_orientation;

	port->typec_sw = typec_चयन_रेजिस्टर(pmc->dev, &sw_desc);
	अगर (IS_ERR(port->typec_sw))
		वापस PTR_ERR(port->typec_sw);

	mux_desc.fwnode = fwnode;
	mux_desc.drvdata = port;
	mux_desc.name = fwnode_get_name(fwnode);
	mux_desc.set = pmc_usb_mux_set;

	port->typec_mux = typec_mux_रेजिस्टर(pmc->dev, &mux_desc);
	अगर (IS_ERR(port->typec_mux)) अणु
		ret = PTR_ERR(port->typec_mux);
		जाओ err_unरेजिस्टर_चयन;
	पूर्ण

	desc.fwnode = fwnode;
	desc.driver_data = port;
	desc.name = fwnode_get_name(fwnode);
	desc.set = pmc_usb_set_role;

	port->usb_sw = usb_role_चयन_रेजिस्टर(pmc->dev, &desc);
	अगर (IS_ERR(port->usb_sw)) अणु
		ret = PTR_ERR(port->usb_sw);
		जाओ err_unरेजिस्टर_mux;
	पूर्ण

	वापस 0;

err_unरेजिस्टर_mux:
	typec_mux_unरेजिस्टर(port->typec_mux);

err_unरेजिस्टर_चयन:
	typec_चयन_unरेजिस्टर(port->typec_sw);

	वापस ret;
पूर्ण

अटल पूर्णांक is_memory(काष्ठा acpi_resource *res, व्योम *data)
अणु
	काष्ठा resource r;

	वापस !acpi_dev_resource_memory(res, &r);
पूर्ण

अटल पूर्णांक pmc_usb_probe_iom(काष्ठा pmc_usb *pmc)
अणु
	काष्ठा list_head resource_list;
	काष्ठा resource_entry *rentry;
	काष्ठा acpi_device *adev;
	पूर्णांक ret;

	adev = acpi_dev_get_first_match_dev("INTC1072", शून्य, -1);
	अगर (!adev)
		वापस -ENODEV;

	INIT_LIST_HEAD(&resource_list);
	ret = acpi_dev_get_resources(adev, &resource_list, is_memory, शून्य);
	अगर (ret < 0)
		वापस ret;

	rentry = list_first_entry_or_null(&resource_list, काष्ठा resource_entry, node);
	अगर (rentry)
		pmc->iom_base = devm_ioremap_resource(pmc->dev, rentry->res);

	acpi_dev_मुक्त_resource_list(&resource_list);

	अगर (!pmc->iom_base) अणु
		acpi_dev_put(adev);
		वापस -ENOMEM;
	पूर्ण

	अगर (IS_ERR(pmc->iom_base)) अणु
		acpi_dev_put(adev);
		वापस PTR_ERR(pmc->iom_base);
	पूर्ण

	pmc->iom_adev = adev;

	वापस 0;
पूर्ण

अटल पूर्णांक pmc_usb_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा fwnode_handle *fwnode = शून्य;
	काष्ठा pmc_usb *pmc;
	पूर्णांक i = 0;
	पूर्णांक ret;

	pmc = devm_kzalloc(&pdev->dev, माप(*pmc), GFP_KERNEL);
	अगर (!pmc)
		वापस -ENOMEM;

	device_क्रम_each_child_node(&pdev->dev, fwnode)
		pmc->num_ports++;

	/* The IOM microcontroller has a limitation of max 4 ports. */
	अगर (pmc->num_ports > 4) अणु
		dev_err(&pdev->dev, "driver limited to 4 ports\n");
		वापस -दुस्फल;
	पूर्ण

	pmc->port = devm_kसुस्मृति(&pdev->dev, pmc->num_ports,
				 माप(काष्ठा pmc_usb_port), GFP_KERNEL);
	अगर (!pmc->port)
		वापस -ENOMEM;

	pmc->ipc = devm_पूर्णांकel_scu_ipc_dev_get(&pdev->dev);
	अगर (!pmc->ipc)
		वापस -ENODEV;

	pmc->dev = &pdev->dev;

	ret = pmc_usb_probe_iom(pmc);
	अगर (ret)
		वापस ret;

	/*
	 * For every physical USB connector (USB2 and USB3 combo) there is a
	 * child ACPI device node under the PMC mux ACPI device object.
	 */
	क्रम (i = 0; i < pmc->num_ports; i++) अणु
		fwnode = device_get_next_child_node(pmc->dev, fwnode);
		अगर (!fwnode)
			अवरोध;

		ret = pmc_usb_रेजिस्टर_port(pmc, i, fwnode);
		अगर (ret) अणु
			fwnode_handle_put(fwnode);
			जाओ err_हटाओ_ports;
		पूर्ण
	पूर्ण

	platक्रमm_set_drvdata(pdev, pmc);

	वापस 0;

err_हटाओ_ports:
	क्रम (i = 0; i < pmc->num_ports; i++) अणु
		typec_चयन_unरेजिस्टर(pmc->port[i].typec_sw);
		typec_mux_unरेजिस्टर(pmc->port[i].typec_mux);
		usb_role_चयन_unरेजिस्टर(pmc->port[i].usb_sw);
	पूर्ण

	acpi_dev_put(pmc->iom_adev);

	वापस ret;
पूर्ण

अटल पूर्णांक pmc_usb_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा pmc_usb *pmc = platक्रमm_get_drvdata(pdev);
	पूर्णांक i;

	क्रम (i = 0; i < pmc->num_ports; i++) अणु
		typec_चयन_unरेजिस्टर(pmc->port[i].typec_sw);
		typec_mux_unरेजिस्टर(pmc->port[i].typec_mux);
		usb_role_चयन_unरेजिस्टर(pmc->port[i].usb_sw);
	पूर्ण

	acpi_dev_put(pmc->iom_adev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा acpi_device_id pmc_usb_acpi_ids[] = अणु
	अणु "INTC105C", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(acpi, pmc_usb_acpi_ids);

अटल काष्ठा platक्रमm_driver pmc_usb_driver = अणु
	.driver = अणु
		.name = "intel_pmc_usb",
		.acpi_match_table = ACPI_PTR(pmc_usb_acpi_ids),
	पूर्ण,
	.probe = pmc_usb_probe,
	.हटाओ = pmc_usb_हटाओ,
पूर्ण;

module_platक्रमm_driver(pmc_usb_driver);

MODULE_AUTHOR("Heikki Krogerus <heikki.krogerus@linux.intel.com>");
MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("Intel PMC USB mux control");
