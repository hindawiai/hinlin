<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Provides code common क्रम host and device side USB.
 *
 * If either host side (ie. CONFIG_USB=y) or device side USB stack
 * (ie. CONFIG_USB_GADGET=y) is compiled in the kernel, this module is
 * compiled-in as well.  Otherwise, अगर either of the two stacks is
 * compiled as module, this file is compiled as module as well.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/usb/ch9.h>
#समावेश <linux/usb/of.h>
#समावेश <linux/usb/otg.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/debugfs.h>
#समावेश "common.h"

अटल स्थिर अक्षर *स्थिर ep_type_names[] = अणु
	[USB_ENDPOINT_XFER_CONTROL] = "ctrl",
	[USB_ENDPOINT_XFER_ISOC] = "isoc",
	[USB_ENDPOINT_XFER_BULK] = "bulk",
	[USB_ENDPOINT_XFER_INT] = "intr",
पूर्ण;

/**
 * usb_ep_type_string() - Returns human पढ़ोable-name of the endpoपूर्णांक type.
 * @ep_type: The endpoपूर्णांक type to वापस human-पढ़ोable name क्रम.  If it's not
 *   any of the types: USB_ENDPOINT_XFER_अणुCONTROL, ISOC, BULK, INTपूर्ण,
 *   usually got by usb_endpoपूर्णांक_type(), the string 'unknown' will be वापसed.
 */
स्थिर अक्षर *usb_ep_type_string(पूर्णांक ep_type)
अणु
	अगर (ep_type < 0 || ep_type >= ARRAY_SIZE(ep_type_names))
		वापस "unknown";

	वापस ep_type_names[ep_type];
पूर्ण
EXPORT_SYMBOL_GPL(usb_ep_type_string);

स्थिर अक्षर *usb_otg_state_string(क्रमागत usb_otg_state state)
अणु
	अटल स्थिर अक्षर *स्थिर names[] = अणु
		[OTG_STATE_A_IDLE] = "a_idle",
		[OTG_STATE_A_WAIT_VRISE] = "a_wait_vrise",
		[OTG_STATE_A_WAIT_BCON] = "a_wait_bcon",
		[OTG_STATE_A_HOST] = "a_host",
		[OTG_STATE_A_SUSPEND] = "a_suspend",
		[OTG_STATE_A_PERIPHERAL] = "a_peripheral",
		[OTG_STATE_A_WAIT_VFALL] = "a_wait_vfall",
		[OTG_STATE_A_VBUS_ERR] = "a_vbus_err",
		[OTG_STATE_B_IDLE] = "b_idle",
		[OTG_STATE_B_SRP_INIT] = "b_srp_init",
		[OTG_STATE_B_PERIPHERAL] = "b_peripheral",
		[OTG_STATE_B_WAIT_ACON] = "b_wait_acon",
		[OTG_STATE_B_HOST] = "b_host",
	पूर्ण;

	अगर (state < 0 || state >= ARRAY_SIZE(names))
		वापस "UNDEFINED";

	वापस names[state];
पूर्ण
EXPORT_SYMBOL_GPL(usb_otg_state_string);

अटल स्थिर अक्षर *स्थिर speed_names[] = अणु
	[USB_SPEED_UNKNOWN] = "UNKNOWN",
	[USB_SPEED_LOW] = "low-speed",
	[USB_SPEED_FULL] = "full-speed",
	[USB_SPEED_HIGH] = "high-speed",
	[USB_SPEED_WIRELESS] = "wireless",
	[USB_SPEED_SUPER] = "super-speed",
	[USB_SPEED_SUPER_PLUS] = "super-speed-plus",
पूर्ण;

अटल स्थिर अक्षर *स्थिर ssp_rate[] = अणु
	[USB_SSP_GEN_UNKNOWN] = "UNKNOWN",
	[USB_SSP_GEN_2x1] = "super-speed-plus-gen2x1",
	[USB_SSP_GEN_1x2] = "super-speed-plus-gen1x2",
	[USB_SSP_GEN_2x2] = "super-speed-plus-gen2x2",
पूर्ण;

/**
 * usb_speed_string() - Returns human पढ़ोable-name of the speed.
 * @speed: The speed to वापस human-पढ़ोable name क्रम.  If it's not
 *   any of the speeds defined in usb_device_speed क्रमागत, string क्रम
 *   USB_SPEED_UNKNOWN will be वापसed.
 */
स्थिर अक्षर *usb_speed_string(क्रमागत usb_device_speed speed)
अणु
	अगर (speed < 0 || speed >= ARRAY_SIZE(speed_names))
		speed = USB_SPEED_UNKNOWN;
	वापस speed_names[speed];
पूर्ण
EXPORT_SYMBOL_GPL(usb_speed_string);

/**
 * usb_get_maximum_speed - Get maximum requested speed क्रम a given USB
 * controller.
 * @dev: Poपूर्णांकer to the given USB controller device
 *
 * The function माला_लो the maximum speed string from property "maximum-speed",
 * and वापसs the corresponding क्रमागत usb_device_speed.
 */
क्रमागत usb_device_speed usb_get_maximum_speed(काष्ठा device *dev)
अणु
	स्थिर अक्षर *maximum_speed;
	पूर्णांक ret;

	ret = device_property_पढ़ो_string(dev, "maximum-speed", &maximum_speed);
	अगर (ret < 0)
		वापस USB_SPEED_UNKNOWN;

	ret = match_string(ssp_rate, ARRAY_SIZE(ssp_rate), maximum_speed);
	अगर (ret > 0)
		वापस USB_SPEED_SUPER_PLUS;

	ret = match_string(speed_names, ARRAY_SIZE(speed_names), maximum_speed);
	वापस (ret < 0) ? USB_SPEED_UNKNOWN : ret;
पूर्ण
EXPORT_SYMBOL_GPL(usb_get_maximum_speed);

/**
 * usb_get_maximum_ssp_rate - Get the संकेतing rate generation and lane count
 *	of a SuperSpeed Plus capable device.
 * @dev: Poपूर्णांकer to the given USB controller device
 *
 * If the string from "maximum-speed" property is super-speed-plus-genXxY where
 * 'X' is the generation number and 'Y' is the number of lanes, then this
 * function वापसs the corresponding क्रमागत usb_ssp_rate.
 */
क्रमागत usb_ssp_rate usb_get_maximum_ssp_rate(काष्ठा device *dev)
अणु
	स्थिर अक्षर *maximum_speed;
	पूर्णांक ret;

	ret = device_property_पढ़ो_string(dev, "maximum-speed", &maximum_speed);
	अगर (ret < 0)
		वापस USB_SSP_GEN_UNKNOWN;

	ret = match_string(ssp_rate, ARRAY_SIZE(ssp_rate), maximum_speed);
	वापस (ret < 0) ? USB_SSP_GEN_UNKNOWN : ret;
पूर्ण
EXPORT_SYMBOL_GPL(usb_get_maximum_ssp_rate);

/**
 * usb_state_string - Returns human पढ़ोable name क्रम the state.
 * @state: The state to वापस a human-पढ़ोable name क्रम. If it's not
 *	any of the states devices in usb_device_state_string क्रमागत,
 *	the string UNKNOWN will be वापसed.
 */
स्थिर अक्षर *usb_state_string(क्रमागत usb_device_state state)
अणु
	अटल स्थिर अक्षर *स्थिर names[] = अणु
		[USB_STATE_NOTATTACHED] = "not attached",
		[USB_STATE_ATTACHED] = "attached",
		[USB_STATE_POWERED] = "powered",
		[USB_STATE_RECONNECTING] = "reconnecting",
		[USB_STATE_UNAUTHENTICATED] = "unauthenticated",
		[USB_STATE_DEFAULT] = "default",
		[USB_STATE_ADDRESS] = "addressed",
		[USB_STATE_CONFIGURED] = "configured",
		[USB_STATE_SUSPENDED] = "suspended",
	पूर्ण;

	अगर (state < 0 || state >= ARRAY_SIZE(names))
		वापस "UNKNOWN";

	वापस names[state];
पूर्ण
EXPORT_SYMBOL_GPL(usb_state_string);

अटल स्थिर अक्षर *स्थिर usb_dr_modes[] = अणु
	[USB_DR_MODE_UNKNOWN]		= "",
	[USB_DR_MODE_HOST]		= "host",
	[USB_DR_MODE_PERIPHERAL]	= "peripheral",
	[USB_DR_MODE_OTG]		= "otg",
पूर्ण;

अटल क्रमागत usb_dr_mode usb_get_dr_mode_from_string(स्थिर अक्षर *str)
अणु
	पूर्णांक ret;

	ret = match_string(usb_dr_modes, ARRAY_SIZE(usb_dr_modes), str);
	वापस (ret < 0) ? USB_DR_MODE_UNKNOWN : ret;
पूर्ण

क्रमागत usb_dr_mode usb_get_dr_mode(काष्ठा device *dev)
अणु
	स्थिर अक्षर *dr_mode;
	पूर्णांक err;

	err = device_property_पढ़ो_string(dev, "dr_mode", &dr_mode);
	अगर (err < 0)
		वापस USB_DR_MODE_UNKNOWN;

	वापस usb_get_dr_mode_from_string(dr_mode);
पूर्ण
EXPORT_SYMBOL_GPL(usb_get_dr_mode);

/**
 * usb_decode_पूर्णांकerval - Decode bInterval पूर्णांकo the समय expressed in 1us unit
 * @epd: The descriptor of the endpoपूर्णांक
 * @speed: The speed that the endpoपूर्णांक works as
 *
 * Function वापसs the पूर्णांकerval expressed in 1us unit क्रम servicing
 * endpoपूर्णांक क्रम data transfers.
 */
अचिन्हित पूर्णांक usb_decode_पूर्णांकerval(स्थिर काष्ठा usb_endpoपूर्णांक_descriptor *epd,
				 क्रमागत usb_device_speed speed)
अणु
	अचिन्हित पूर्णांक पूर्णांकerval = 0;

	चयन (usb_endpoपूर्णांक_type(epd)) अणु
	हाल USB_ENDPOINT_XFER_CONTROL:
		/* uframes per NAK */
		अगर (speed == USB_SPEED_HIGH)
			पूर्णांकerval = epd->bInterval;
		अवरोध;
	हाल USB_ENDPOINT_XFER_ISOC:
		पूर्णांकerval = 1 << (epd->bInterval - 1);
		अवरोध;
	हाल USB_ENDPOINT_XFER_BULK:
		/* uframes per NAK */
		अगर (speed == USB_SPEED_HIGH && usb_endpoपूर्णांक_dir_out(epd))
			पूर्णांकerval = epd->bInterval;
		अवरोध;
	हाल USB_ENDPOINT_XFER_INT:
		अगर (speed >= USB_SPEED_HIGH)
			पूर्णांकerval = 1 << (epd->bInterval - 1);
		अन्यथा
			पूर्णांकerval = epd->bInterval;
		अवरोध;
	पूर्ण

	पूर्णांकerval *= (speed >= USB_SPEED_HIGH) ? 125 : 1000;

	वापस पूर्णांकerval;
पूर्ण
EXPORT_SYMBOL_GPL(usb_decode_पूर्णांकerval);

#अगर_घोषित CONFIG_OF
/**
 * of_usb_get_dr_mode_by_phy - Get dual role mode क्रम the controller device
 * which is associated with the given phy device_node
 * @np:	Poपूर्णांकer to the given phy device_node
 * @arg0: phandle args[0] क्रम phy's with #phy-cells >= 1, or -1 क्रम
 *        phys which करो not have phy-cells
 *
 * In dts a usb controller associates with phy devices.  The function माला_लो
 * the string from property 'dr_mode' of the controller associated with the
 * given phy device node, and वापसs the correspondig क्रमागत usb_dr_mode.
 */
क्रमागत usb_dr_mode of_usb_get_dr_mode_by_phy(काष्ठा device_node *np, पूर्णांक arg0)
अणु
	काष्ठा device_node *controller = शून्य;
	काष्ठा of_phandle_args args;
	स्थिर अक्षर *dr_mode;
	पूर्णांक index;
	पूर्णांक err;

	करो अणु
		controller = of_find_node_with_property(controller, "phys");
		अगर (!of_device_is_available(controller))
			जारी;
		index = 0;
		करो अणु
			अगर (arg0 == -1) अणु
				args.np = of_parse_phandle(controller, "phys",
							index);
				args.args_count = 0;
			पूर्ण अन्यथा अणु
				err = of_parse_phandle_with_args(controller,
							"phys", "#phy-cells",
							index, &args);
				अगर (err)
					अवरोध;
			पूर्ण

			of_node_put(args.np);
			अगर (args.np == np && (args.args_count == 0 ||
					      args.args[0] == arg0))
				जाओ finish;
			index++;
		पूर्ण जबतक (args.np);
	पूर्ण जबतक (controller);

finish:
	err = of_property_पढ़ो_string(controller, "dr_mode", &dr_mode);
	of_node_put(controller);

	अगर (err < 0)
		वापस USB_DR_MODE_UNKNOWN;

	वापस usb_get_dr_mode_from_string(dr_mode);
पूर्ण
EXPORT_SYMBOL_GPL(of_usb_get_dr_mode_by_phy);

/**
 * of_usb_host_tpl_support - to get अगर Targeted Peripheral List is supported
 * क्रम given targeted hosts (non-PC hosts)
 * @np: Poपूर्णांकer to the given device_node
 *
 * The function माला_लो अगर the targeted hosts support TPL or not
 */
bool of_usb_host_tpl_support(काष्ठा device_node *np)
अणु
	वापस of_property_पढ़ो_bool(np, "tpl-support");
पूर्ण
EXPORT_SYMBOL_GPL(of_usb_host_tpl_support);

/**
 * of_usb_update_otg_caps - to update usb otg capabilities according to
 * the passed properties in DT.
 * @np: Poपूर्णांकer to the given device_node
 * @otg_caps: Poपूर्णांकer to the target usb_otg_caps to be set
 *
 * The function updates the otg capabilities
 */
पूर्णांक of_usb_update_otg_caps(काष्ठा device_node *np,
			काष्ठा usb_otg_caps *otg_caps)
अणु
	u32 otg_rev;

	अगर (!otg_caps)
		वापस -EINVAL;

	अगर (!of_property_पढ़ो_u32(np, "otg-rev", &otg_rev)) अणु
		चयन (otg_rev) अणु
		हाल 0x0100:
		हाल 0x0120:
		हाल 0x0130:
		हाल 0x0200:
			/* Choose the lesser one अगर it's alपढ़ोy been set */
			अगर (otg_caps->otg_rev)
				otg_caps->otg_rev = min_t(u16, otg_rev,
							otg_caps->otg_rev);
			अन्यथा
				otg_caps->otg_rev = otg_rev;
			अवरोध;
		शेष:
			pr_err("%pOF: unsupported otg-rev: 0x%x\n",
						np, otg_rev);
			वापस -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अणु
		/*
		 * otg-rev is mandatory क्रम otg properties, अगर not passed
		 * we set it to be 0 and assume it's a legacy otg device.
		 * Non-dt platक्रमm can set it afterwards.
		 */
		otg_caps->otg_rev = 0;
	पूर्ण

	अगर (of_property_पढ़ो_bool(np, "hnp-disable"))
		otg_caps->hnp_support = false;
	अगर (of_property_पढ़ो_bool(np, "srp-disable"))
		otg_caps->srp_support = false;
	अगर (of_property_पढ़ो_bool(np, "adp-disable") ||
				(otg_caps->otg_rev < 0x0200))
		otg_caps->adp_support = false;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(of_usb_update_otg_caps);

/**
 * usb_of_get_companion_dev - Find the companion device
 * @dev: the device poपूर्णांकer to find a companion
 *
 * Find the companion device from platक्रमm bus.
 *
 * Takes a reference to the वापसed काष्ठा device which needs to be dropped
 * after use.
 *
 * Return: On success, a poपूर्णांकer to the companion device, %शून्य on failure.
 */
काष्ठा device *usb_of_get_companion_dev(काष्ठा device *dev)
अणु
	काष्ठा device_node *node;
	काष्ठा platक्रमm_device *pdev = शून्य;

	node = of_parse_phandle(dev->of_node, "companion", 0);
	अगर (node)
		pdev = of_find_device_by_node(node);

	of_node_put(node);

	वापस pdev ? &pdev->dev : शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(usb_of_get_companion_dev);
#पूर्ण_अगर

काष्ठा dentry *usb_debug_root;
EXPORT_SYMBOL_GPL(usb_debug_root);

अटल पूर्णांक __init usb_common_init(व्योम)
अणु
	usb_debug_root = debugfs_create_dir("usb", शून्य);
	ledtrig_usb_init();
	वापस 0;
पूर्ण

अटल व्योम __निकास usb_common_निकास(व्योम)
अणु
	ledtrig_usb_निकास();
	debugfs_हटाओ_recursive(usb_debug_root);
पूर्ण

subsys_initcall(usb_common_init);
module_निकास(usb_common_निकास);

MODULE_LICENSE("GPL");
