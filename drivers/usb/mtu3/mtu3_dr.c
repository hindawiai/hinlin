<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * mtu3_dr.c - dual role चयन and host glue layer
 *
 * Copyright (C) 2016 MediaTek Inc.
 *
 * Author: Chunfeng Yun <chunfeng.yun@mediatek.com>
 */

#समावेश <linux/usb/role.h>

#समावेश "mtu3.h"
#समावेश "mtu3_dr.h"
#समावेश "mtu3_debug.h"

#घोषणा USB2_PORT 2
#घोषणा USB3_PORT 3

क्रमागत mtu3_vbus_id_state अणु
	MTU3_ID_FLOAT = 1,
	MTU3_ID_GROUND,
	MTU3_VBUS_OFF,
	MTU3_VBUS_VALID,
पूर्ण;

अटल अक्षर *mailbox_state_string(क्रमागत mtu3_vbus_id_state state)
अणु
	चयन (state) अणु
	हाल MTU3_ID_FLOAT:
		वापस "ID_FLOAT";
	हाल MTU3_ID_GROUND:
		वापस "ID_GROUND";
	हाल MTU3_VBUS_OFF:
		वापस "VBUS_OFF";
	हाल MTU3_VBUS_VALID:
		वापस "VBUS_VALID";
	शेष:
		वापस "UNKNOWN";
	पूर्ण
पूर्ण

अटल व्योम toggle_opstate(काष्ठा ssusb_mtk *ssusb)
अणु
	अगर (!ssusb->otg_चयन.is_u3_drd) अणु
		mtu3_setbits(ssusb->mac_base, U3D_DEVICE_CONTROL, DC_SESSION);
		mtu3_setbits(ssusb->mac_base, U3D_POWER_MANAGEMENT, SOFT_CONN);
	पूर्ण
पूर्ण

/* only port0 supports dual-role mode */
अटल पूर्णांक ssusb_port0_चयन(काष्ठा ssusb_mtk *ssusb,
	पूर्णांक version, bool tohost)
अणु
	व्योम __iomem *ibase = ssusb->ippc_base;
	u32 value;

	dev_dbg(ssusb->dev, "%s (switch u%d port0 to %s)\n", __func__,
		version, tohost ? "host" : "device");

	अगर (version == USB2_PORT) अणु
		/* 1. घातer off and disable u2 port0 */
		value = mtu3_पढ़ोl(ibase, SSUSB_U2_CTRL(0));
		value |= SSUSB_U2_PORT_PDN | SSUSB_U2_PORT_DIS;
		mtu3_ग_लिखोl(ibase, SSUSB_U2_CTRL(0), value);

		/* 2. घातer on, enable u2 port0 and select its mode */
		value = mtu3_पढ़ोl(ibase, SSUSB_U2_CTRL(0));
		value &= ~(SSUSB_U2_PORT_PDN | SSUSB_U2_PORT_DIS);
		value = tohost ? (value | SSUSB_U2_PORT_HOST_SEL) :
			(value & (~SSUSB_U2_PORT_HOST_SEL));
		mtu3_ग_लिखोl(ibase, SSUSB_U2_CTRL(0), value);
	पूर्ण अन्यथा अणु
		/* 1. घातer off and disable u3 port0 */
		value = mtu3_पढ़ोl(ibase, SSUSB_U3_CTRL(0));
		value |= SSUSB_U3_PORT_PDN | SSUSB_U3_PORT_DIS;
		mtu3_ग_लिखोl(ibase, SSUSB_U3_CTRL(0), value);

		/* 2. घातer on, enable u3 port0 and select its mode */
		value = mtu3_पढ़ोl(ibase, SSUSB_U3_CTRL(0));
		value &= ~(SSUSB_U3_PORT_PDN | SSUSB_U3_PORT_DIS);
		value = tohost ? (value | SSUSB_U3_PORT_HOST_SEL) :
			(value & (~SSUSB_U3_PORT_HOST_SEL));
		mtu3_ग_लिखोl(ibase, SSUSB_U3_CTRL(0), value);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम चयन_port_to_host(काष्ठा ssusb_mtk *ssusb)
अणु
	u32 check_clk = 0;

	dev_dbg(ssusb->dev, "%s\n", __func__);

	ssusb_port0_चयन(ssusb, USB2_PORT, true);

	अगर (ssusb->otg_चयन.is_u3_drd) अणु
		ssusb_port0_चयन(ssusb, USB3_PORT, true);
		check_clk = SSUSB_U3_MAC_RST_B_STS;
	पूर्ण

	ssusb_check_घड़ीs(ssusb, check_clk);

	/* after all घड़ीs are stable */
	toggle_opstate(ssusb);
पूर्ण

अटल व्योम चयन_port_to_device(काष्ठा ssusb_mtk *ssusb)
अणु
	u32 check_clk = 0;

	dev_dbg(ssusb->dev, "%s\n", __func__);

	ssusb_port0_चयन(ssusb, USB2_PORT, false);

	अगर (ssusb->otg_चयन.is_u3_drd) अणु
		ssusb_port0_चयन(ssusb, USB3_PORT, false);
		check_clk = SSUSB_U3_MAC_RST_B_STS;
	पूर्ण

	ssusb_check_घड़ीs(ssusb, check_clk);
पूर्ण

पूर्णांक ssusb_set_vbus(काष्ठा otg_चयन_mtk *otg_sx, पूर्णांक is_on)
अणु
	काष्ठा ssusb_mtk *ssusb =
		container_of(otg_sx, काष्ठा ssusb_mtk, otg_चयन);
	काष्ठा regulator *vbus = otg_sx->vbus;
	पूर्णांक ret;

	/* vbus is optional */
	अगर (!vbus)
		वापस 0;

	dev_dbg(ssusb->dev, "%s: turn %s\n", __func__, is_on ? "on" : "off");

	अगर (is_on) अणु
		ret = regulator_enable(vbus);
		अगर (ret) अणु
			dev_err(ssusb->dev, "vbus regulator enable failed\n");
			वापस ret;
		पूर्ण
	पूर्ण अन्यथा अणु
		regulator_disable(vbus);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * चयन to host: -> MTU3_VBUS_OFF --> MTU3_ID_GROUND
 * चयन to device: -> MTU3_ID_FLOAT --> MTU3_VBUS_VALID
 */
अटल व्योम ssusb_set_mailbox(काष्ठा otg_चयन_mtk *otg_sx,
	क्रमागत mtu3_vbus_id_state status)
अणु
	काष्ठा ssusb_mtk *ssusb =
		container_of(otg_sx, काष्ठा ssusb_mtk, otg_चयन);
	काष्ठा mtu3 *mtu = ssusb->u3d;

	dev_dbg(ssusb->dev, "mailbox %s\n", mailbox_state_string(status));
	mtu3_dbg_trace(ssusb->dev, "mailbox %s", mailbox_state_string(status));

	चयन (status) अणु
	हाल MTU3_ID_GROUND:
		चयन_port_to_host(ssusb);
		ssusb_set_vbus(otg_sx, 1);
		ssusb->is_host = true;
		अवरोध;
	हाल MTU3_ID_FLOAT:
		ssusb->is_host = false;
		ssusb_set_vbus(otg_sx, 0);
		चयन_port_to_device(ssusb);
		अवरोध;
	हाल MTU3_VBUS_OFF:
		mtu3_stop(mtu);
		pm_relax(ssusb->dev);
		अवरोध;
	हाल MTU3_VBUS_VALID:
		/* aव्योम suspend when works as device */
		pm_stay_awake(ssusb->dev);
		mtu3_start(mtu);
		अवरोध;
	शेष:
		dev_err(ssusb->dev, "invalid state\n");
	पूर्ण
पूर्ण

अटल व्योम ssusb_id_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा otg_चयन_mtk *otg_sx =
		container_of(work, काष्ठा otg_चयन_mtk, id_work);

	अगर (otg_sx->id_event)
		ssusb_set_mailbox(otg_sx, MTU3_ID_GROUND);
	अन्यथा
		ssusb_set_mailbox(otg_sx, MTU3_ID_FLOAT);
पूर्ण

अटल व्योम ssusb_vbus_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा otg_चयन_mtk *otg_sx =
		container_of(work, काष्ठा otg_चयन_mtk, vbus_work);

	अगर (otg_sx->vbus_event)
		ssusb_set_mailbox(otg_sx, MTU3_VBUS_VALID);
	अन्यथा
		ssusb_set_mailbox(otg_sx, MTU3_VBUS_OFF);
पूर्ण

/*
 * @ssusb_id_notअगरier is called in atomic context, but @ssusb_set_mailbox
 * may sleep, so use work queue here
 */
अटल पूर्णांक ssusb_id_notअगरier(काष्ठा notअगरier_block *nb,
	अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	काष्ठा otg_चयन_mtk *otg_sx =
		container_of(nb, काष्ठा otg_चयन_mtk, id_nb);

	otg_sx->id_event = event;
	schedule_work(&otg_sx->id_work);

	वापस NOTIFY_DONE;
पूर्ण

अटल पूर्णांक ssusb_vbus_notअगरier(काष्ठा notअगरier_block *nb,
	अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	काष्ठा otg_चयन_mtk *otg_sx =
		container_of(nb, काष्ठा otg_चयन_mtk, vbus_nb);

	otg_sx->vbus_event = event;
	schedule_work(&otg_sx->vbus_work);

	वापस NOTIFY_DONE;
पूर्ण

अटल पूर्णांक ssusb_extcon_रेजिस्टर(काष्ठा otg_चयन_mtk *otg_sx)
अणु
	काष्ठा ssusb_mtk *ssusb =
		container_of(otg_sx, काष्ठा ssusb_mtk, otg_चयन);
	काष्ठा extcon_dev *edev = otg_sx->edev;
	पूर्णांक ret;

	/* extcon is optional */
	अगर (!edev)
		वापस 0;

	otg_sx->vbus_nb.notअगरier_call = ssusb_vbus_notअगरier;
	ret = devm_extcon_रेजिस्टर_notअगरier(ssusb->dev, edev, EXTCON_USB,
					&otg_sx->vbus_nb);
	अगर (ret < 0) अणु
		dev_err(ssusb->dev, "failed to register notifier for USB\n");
		वापस ret;
	पूर्ण

	otg_sx->id_nb.notअगरier_call = ssusb_id_notअगरier;
	ret = devm_extcon_रेजिस्टर_notअगरier(ssusb->dev, edev, EXTCON_USB_HOST,
					&otg_sx->id_nb);
	अगर (ret < 0) अणु
		dev_err(ssusb->dev, "failed to register notifier for USB-HOST\n");
		वापस ret;
	पूर्ण

	dev_dbg(ssusb->dev, "EXTCON_USB: %d, EXTCON_USB_HOST: %d\n",
		extcon_get_state(edev, EXTCON_USB),
		extcon_get_state(edev, EXTCON_USB_HOST));

	/* शेष as host, चयन to device mode अगर needed */
	अगर (extcon_get_state(edev, EXTCON_USB_HOST) == false)
		ssusb_set_mailbox(otg_sx, MTU3_ID_FLOAT);
	अगर (extcon_get_state(edev, EXTCON_USB) == true)
		ssusb_set_mailbox(otg_sx, MTU3_VBUS_VALID);

	वापस 0;
पूर्ण

/*
 * We provide an पूर्णांकerface via debugfs to चयन between host and device modes
 * depending on user input.
 * This is useful in special हालs, such as uses TYPE-A receptacle but also
 * wants to support dual-role mode.
 */
व्योम ssusb_mode_चयन(काष्ठा ssusb_mtk *ssusb, पूर्णांक to_host)
अणु
	काष्ठा otg_चयन_mtk *otg_sx = &ssusb->otg_चयन;

	अगर (to_host) अणु
		ssusb_set_क्रमce_mode(ssusb, MTU3_DR_FORCE_HOST);
		ssusb_set_mailbox(otg_sx, MTU3_VBUS_OFF);
		ssusb_set_mailbox(otg_sx, MTU3_ID_GROUND);
	पूर्ण अन्यथा अणु
		ssusb_set_क्रमce_mode(ssusb, MTU3_DR_FORCE_DEVICE);
		ssusb_set_mailbox(otg_sx, MTU3_ID_FLOAT);
		ssusb_set_mailbox(otg_sx, MTU3_VBUS_VALID);
	पूर्ण
पूर्ण

व्योम ssusb_set_क्रमce_mode(काष्ठा ssusb_mtk *ssusb,
			  क्रमागत mtu3_dr_क्रमce_mode mode)
अणु
	u32 value;

	value = mtu3_पढ़ोl(ssusb->ippc_base, SSUSB_U2_CTRL(0));
	चयन (mode) अणु
	हाल MTU3_DR_FORCE_DEVICE:
		value |= SSUSB_U2_PORT_FORCE_IDDIG | SSUSB_U2_PORT_RG_IDDIG;
		अवरोध;
	हाल MTU3_DR_FORCE_HOST:
		value |= SSUSB_U2_PORT_FORCE_IDDIG;
		value &= ~SSUSB_U2_PORT_RG_IDDIG;
		अवरोध;
	हाल MTU3_DR_FORCE_NONE:
		value &= ~(SSUSB_U2_PORT_FORCE_IDDIG | SSUSB_U2_PORT_RG_IDDIG);
		अवरोध;
	शेष:
		वापस;
	पूर्ण
	mtu3_ग_लिखोl(ssusb->ippc_base, SSUSB_U2_CTRL(0), value);
पूर्ण

अटल पूर्णांक ssusb_role_sw_set(काष्ठा usb_role_चयन *sw, क्रमागत usb_role role)
अणु
	काष्ठा ssusb_mtk *ssusb = usb_role_चयन_get_drvdata(sw);
	bool to_host = false;

	अगर (role == USB_ROLE_HOST)
		to_host = true;

	अगर (to_host ^ ssusb->is_host)
		ssusb_mode_चयन(ssusb, to_host);

	वापस 0;
पूर्ण

अटल क्रमागत usb_role ssusb_role_sw_get(काष्ठा usb_role_चयन *sw)
अणु
	काष्ठा ssusb_mtk *ssusb = usb_role_चयन_get_drvdata(sw);
	क्रमागत usb_role role;

	role = ssusb->is_host ? USB_ROLE_HOST : USB_ROLE_DEVICE;

	वापस role;
पूर्ण

अटल पूर्णांक ssusb_role_sw_रेजिस्टर(काष्ठा otg_चयन_mtk *otg_sx)
अणु
	काष्ठा usb_role_चयन_desc role_sx_desc = अणु 0 पूर्ण;
	काष्ठा ssusb_mtk *ssusb =
		container_of(otg_sx, काष्ठा ssusb_mtk, otg_चयन);

	अगर (!otg_sx->role_sw_used)
		वापस 0;

	role_sx_desc.set = ssusb_role_sw_set;
	role_sx_desc.get = ssusb_role_sw_get;
	role_sx_desc.fwnode = dev_fwnode(ssusb->dev);
	role_sx_desc.driver_data = ssusb;
	otg_sx->role_sw = usb_role_चयन_रेजिस्टर(ssusb->dev, &role_sx_desc);

	वापस PTR_ERR_OR_ZERO(otg_sx->role_sw);
पूर्ण

पूर्णांक ssusb_otg_चयन_init(काष्ठा ssusb_mtk *ssusb)
अणु
	काष्ठा otg_चयन_mtk *otg_sx = &ssusb->otg_चयन;
	पूर्णांक ret = 0;

	INIT_WORK(&otg_sx->id_work, ssusb_id_work);
	INIT_WORK(&otg_sx->vbus_work, ssusb_vbus_work);

	अगर (otg_sx->manual_drd_enabled)
		ssusb_dr_debugfs_init(ssusb);
	अन्यथा अगर (otg_sx->role_sw_used)
		ret = ssusb_role_sw_रेजिस्टर(otg_sx);
	अन्यथा
		ret = ssusb_extcon_रेजिस्टर(otg_sx);

	वापस ret;
पूर्ण

व्योम ssusb_otg_चयन_निकास(काष्ठा ssusb_mtk *ssusb)
अणु
	काष्ठा otg_चयन_mtk *otg_sx = &ssusb->otg_चयन;

	cancel_work_sync(&otg_sx->id_work);
	cancel_work_sync(&otg_sx->vbus_work);
	usb_role_चयन_unरेजिस्टर(otg_sx->role_sw);
पूर्ण
