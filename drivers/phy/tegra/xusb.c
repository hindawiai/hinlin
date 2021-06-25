<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2014-2016, NVIDIA CORPORATION.  All rights reserved.
 */

#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/mailbox_client.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/phy/tegra/xusb.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/reset.h>
#समावेश <linux/slab.h>
#समावेश <linux/workqueue.h>

#समावेश <soc/tegra/fuse.h>

#समावेश "xusb.h"

अटल काष्ठा phy *tegra_xusb_pad_of_xlate(काष्ठा device *dev,
					   काष्ठा of_phandle_args *args)
अणु
	काष्ठा tegra_xusb_pad *pad = dev_get_drvdata(dev);
	काष्ठा phy *phy = शून्य;
	अचिन्हित पूर्णांक i;

	अगर (args->args_count != 0)
		वापस ERR_PTR(-EINVAL);

	क्रम (i = 0; i < pad->soc->num_lanes; i++) अणु
		अगर (!pad->lanes[i])
			जारी;

		अगर (pad->lanes[i]->dev.of_node == args->np) अणु
			phy = pad->lanes[i];
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (phy == शून्य)
		phy = ERR_PTR(-ENODEV);

	वापस phy;
पूर्ण

अटल स्थिर काष्ठा of_device_id tegra_xusb_padctl_of_match[] = अणु
#अगर defined(CONFIG_ARCH_TEGRA_124_SOC) || defined(CONFIG_ARCH_TEGRA_132_SOC)
	अणु
		.compatible = "nvidia,tegra124-xusb-padctl",
		.data = &tegra124_xusb_padctl_soc,
	पूर्ण,
#पूर्ण_अगर
#अगर defined(CONFIG_ARCH_TEGRA_210_SOC)
	अणु
		.compatible = "nvidia,tegra210-xusb-padctl",
		.data = &tegra210_xusb_padctl_soc,
	पूर्ण,
#पूर्ण_अगर
#अगर defined(CONFIG_ARCH_TEGRA_186_SOC)
	अणु
		.compatible = "nvidia,tegra186-xusb-padctl",
		.data = &tegra186_xusb_padctl_soc,
	पूर्ण,
#पूर्ण_अगर
#अगर defined(CONFIG_ARCH_TEGRA_194_SOC)
	अणु
		.compatible = "nvidia,tegra194-xusb-padctl",
		.data = &tegra194_xusb_padctl_soc,
	पूर्ण,
#पूर्ण_अगर
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, tegra_xusb_padctl_of_match);

अटल काष्ठा device_node *
tegra_xusb_find_pad_node(काष्ठा tegra_xusb_padctl *padctl, स्थिर अक्षर *name)
अणु
	काष्ठा device_node *pads, *np;

	pads = of_get_child_by_name(padctl->dev->of_node, "pads");
	अगर (!pads)
		वापस शून्य;

	np = of_get_child_by_name(pads, name);
	of_node_put(pads);

	वापस np;
पूर्ण

अटल काष्ठा device_node *
tegra_xusb_pad_find_phy_node(काष्ठा tegra_xusb_pad *pad, अचिन्हित पूर्णांक index)
अणु
	काष्ठा device_node *np, *lanes;

	lanes = of_get_child_by_name(pad->dev.of_node, "lanes");
	अगर (!lanes)
		वापस शून्य;

	np = of_get_child_by_name(lanes, pad->soc->lanes[index].name);
	of_node_put(lanes);

	वापस np;
पूर्ण

पूर्णांक tegra_xusb_lane_parse_dt(काष्ठा tegra_xusb_lane *lane,
			     काष्ठा device_node *np)
अणु
	काष्ठा device *dev = &lane->pad->dev;
	स्थिर अक्षर *function;
	पूर्णांक err;

	err = of_property_पढ़ो_string(np, "nvidia,function", &function);
	अगर (err < 0)
		वापस err;

	err = match_string(lane->soc->funcs, lane->soc->num_funcs, function);
	अगर (err < 0) अणु
		dev_err(dev, "invalid function \"%s\" for lane \"%pOFn\"\n",
			function, np);
		वापस err;
	पूर्ण

	lane->function = err;

	वापस 0;
पूर्ण

अटल व्योम tegra_xusb_lane_destroy(काष्ठा phy *phy)
अणु
	अगर (phy) अणु
		काष्ठा tegra_xusb_lane *lane = phy_get_drvdata(phy);

		lane->pad->ops->हटाओ(lane);
		phy_destroy(phy);
	पूर्ण
पूर्ण

अटल व्योम tegra_xusb_pad_release(काष्ठा device *dev)
अणु
	काष्ठा tegra_xusb_pad *pad = to_tegra_xusb_pad(dev);

	pad->soc->ops->हटाओ(pad);
पूर्ण

अटल स्थिर काष्ठा device_type tegra_xusb_pad_type = अणु
	.release = tegra_xusb_pad_release,
पूर्ण;

पूर्णांक tegra_xusb_pad_init(काष्ठा tegra_xusb_pad *pad,
			काष्ठा tegra_xusb_padctl *padctl,
			काष्ठा device_node *np)
अणु
	पूर्णांक err;

	device_initialize(&pad->dev);
	INIT_LIST_HEAD(&pad->list);
	pad->dev.parent = padctl->dev;
	pad->dev.type = &tegra_xusb_pad_type;
	pad->dev.of_node = np;
	pad->padctl = padctl;

	err = dev_set_name(&pad->dev, "%s", pad->soc->name);
	अगर (err < 0)
		जाओ unरेजिस्टर;

	err = device_add(&pad->dev);
	अगर (err < 0)
		जाओ unरेजिस्टर;

	वापस 0;

unरेजिस्टर:
	device_unरेजिस्टर(&pad->dev);
	वापस err;
पूर्ण

पूर्णांक tegra_xusb_pad_रेजिस्टर(काष्ठा tegra_xusb_pad *pad,
			    स्थिर काष्ठा phy_ops *ops)
अणु
	काष्ठा device_node *children;
	काष्ठा phy *lane;
	अचिन्हित पूर्णांक i;
	पूर्णांक err;

	children = of_get_child_by_name(pad->dev.of_node, "lanes");
	अगर (!children)
		वापस -ENODEV;

	pad->lanes = devm_kसुस्मृति(&pad->dev, pad->soc->num_lanes, माप(lane),
				  GFP_KERNEL);
	अगर (!pad->lanes) अणु
		of_node_put(children);
		वापस -ENOMEM;
	पूर्ण

	क्रम (i = 0; i < pad->soc->num_lanes; i++) अणु
		काष्ठा device_node *np = tegra_xusb_pad_find_phy_node(pad, i);
		काष्ठा tegra_xusb_lane *lane;

		/* skip disabled lanes */
		अगर (!np || !of_device_is_available(np)) अणु
			of_node_put(np);
			जारी;
		पूर्ण

		pad->lanes[i] = phy_create(&pad->dev, np, ops);
		अगर (IS_ERR(pad->lanes[i])) अणु
			err = PTR_ERR(pad->lanes[i]);
			of_node_put(np);
			जाओ हटाओ;
		पूर्ण

		lane = pad->ops->probe(pad, np, i);
		अगर (IS_ERR(lane)) अणु
			phy_destroy(pad->lanes[i]);
			err = PTR_ERR(lane);
			जाओ हटाओ;
		पूर्ण

		list_add_tail(&lane->list, &pad->padctl->lanes);
		phy_set_drvdata(pad->lanes[i], lane);
	पूर्ण

	pad->provider = of_phy_provider_रेजिस्टर_full(&pad->dev, children,
						      tegra_xusb_pad_of_xlate);
	अगर (IS_ERR(pad->provider)) अणु
		err = PTR_ERR(pad->provider);
		जाओ हटाओ;
	पूर्ण

	वापस 0;

हटाओ:
	जबतक (i--)
		tegra_xusb_lane_destroy(pad->lanes[i]);

	of_node_put(children);

	वापस err;
पूर्ण

व्योम tegra_xusb_pad_unरेजिस्टर(काष्ठा tegra_xusb_pad *pad)
अणु
	अचिन्हित पूर्णांक i = pad->soc->num_lanes;

	of_phy_provider_unरेजिस्टर(pad->provider);

	जबतक (i--)
		tegra_xusb_lane_destroy(pad->lanes[i]);

	device_unरेजिस्टर(&pad->dev);
पूर्ण

अटल काष्ठा tegra_xusb_pad *
tegra_xusb_pad_create(काष्ठा tegra_xusb_padctl *padctl,
		      स्थिर काष्ठा tegra_xusb_pad_soc *soc)
अणु
	काष्ठा tegra_xusb_pad *pad;
	काष्ठा device_node *np;
	पूर्णांक err;

	np = tegra_xusb_find_pad_node(padctl, soc->name);
	अगर (!np || !of_device_is_available(np))
		वापस शून्य;

	pad = soc->ops->probe(padctl, soc, np);
	अगर (IS_ERR(pad)) अणु
		err = PTR_ERR(pad);
		dev_err(padctl->dev, "failed to create pad %s: %d\n",
			soc->name, err);
		वापस ERR_PTR(err);
	पूर्ण

	/* XXX move this पूर्णांकo ->probe() to aव्योम string comparison */
	अगर (म_भेद(soc->name, "pcie") == 0)
		padctl->pcie = pad;

	अगर (म_भेद(soc->name, "sata") == 0)
		padctl->sata = pad;

	अगर (म_भेद(soc->name, "usb2") == 0)
		padctl->usb2 = pad;

	अगर (म_भेद(soc->name, "ulpi") == 0)
		padctl->ulpi = pad;

	अगर (म_भेद(soc->name, "hsic") == 0)
		padctl->hsic = pad;

	वापस pad;
पूर्ण

अटल व्योम __tegra_xusb_हटाओ_pads(काष्ठा tegra_xusb_padctl *padctl)
अणु
	काष्ठा tegra_xusb_pad *pad, *पंचांगp;

	list_क्रम_each_entry_safe_reverse(pad, पंचांगp, &padctl->pads, list) अणु
		list_del(&pad->list);
		tegra_xusb_pad_unरेजिस्टर(pad);
	पूर्ण
पूर्ण

अटल व्योम tegra_xusb_हटाओ_pads(काष्ठा tegra_xusb_padctl *padctl)
अणु
	mutex_lock(&padctl->lock);
	__tegra_xusb_हटाओ_pads(padctl);
	mutex_unlock(&padctl->lock);
पूर्ण

अटल व्योम tegra_xusb_lane_program(काष्ठा tegra_xusb_lane *lane)
अणु
	काष्ठा tegra_xusb_padctl *padctl = lane->pad->padctl;
	स्थिर काष्ठा tegra_xusb_lane_soc *soc = lane->soc;
	u32 value;

	/* skip single function lanes */
	अगर (soc->num_funcs < 2)
		वापस;

	/* choose function */
	value = padctl_पढ़ोl(padctl, soc->offset);
	value &= ~(soc->mask << soc->shअगरt);
	value |= lane->function << soc->shअगरt;
	padctl_ग_लिखोl(padctl, value, soc->offset);
पूर्ण

अटल व्योम tegra_xusb_pad_program(काष्ठा tegra_xusb_pad *pad)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < pad->soc->num_lanes; i++) अणु
		काष्ठा tegra_xusb_lane *lane;

		अगर (pad->lanes[i]) अणु
			lane = phy_get_drvdata(pad->lanes[i]);
			tegra_xusb_lane_program(lane);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक tegra_xusb_setup_pads(काष्ठा tegra_xusb_padctl *padctl)
अणु
	काष्ठा tegra_xusb_pad *pad;
	अचिन्हित पूर्णांक i;

	mutex_lock(&padctl->lock);

	क्रम (i = 0; i < padctl->soc->num_pads; i++) अणु
		स्थिर काष्ठा tegra_xusb_pad_soc *soc = padctl->soc->pads[i];
		पूर्णांक err;

		pad = tegra_xusb_pad_create(padctl, soc);
		अगर (IS_ERR(pad)) अणु
			err = PTR_ERR(pad);
			dev_err(padctl->dev, "failed to create pad %s: %d\n",
				soc->name, err);
			__tegra_xusb_हटाओ_pads(padctl);
			mutex_unlock(&padctl->lock);
			वापस err;
		पूर्ण

		अगर (!pad)
			जारी;

		list_add_tail(&pad->list, &padctl->pads);
	पूर्ण

	list_क्रम_each_entry(pad, &padctl->pads, list)
		tegra_xusb_pad_program(pad);

	mutex_unlock(&padctl->lock);
	वापस 0;
पूर्ण

अटल bool tegra_xusb_lane_check(काष्ठा tegra_xusb_lane *lane,
				  स्थिर अक्षर *function)
अणु
	स्थिर अक्षर *func = lane->soc->funcs[lane->function];

	वापस म_भेद(function, func) == 0;
पूर्ण

काष्ठा tegra_xusb_lane *tegra_xusb_find_lane(काष्ठा tegra_xusb_padctl *padctl,
					     स्थिर अक्षर *type,
					     अचिन्हित पूर्णांक index)
अणु
	काष्ठा tegra_xusb_lane *lane, *hit = ERR_PTR(-ENODEV);
	अक्षर *name;

	name = kaप्र_लिखो(GFP_KERNEL, "%s-%u", type, index);
	अगर (!name)
		वापस ERR_PTR(-ENOMEM);

	list_क्रम_each_entry(lane, &padctl->lanes, list) अणु
		अगर (म_भेद(lane->soc->name, name) == 0) अणु
			hit = lane;
			अवरोध;
		पूर्ण
	पूर्ण

	kमुक्त(name);
	वापस hit;
पूर्ण

काष्ठा tegra_xusb_lane *
tegra_xusb_port_find_lane(काष्ठा tegra_xusb_port *port,
			  स्थिर काष्ठा tegra_xusb_lane_map *map,
			  स्थिर अक्षर *function)
अणु
	काष्ठा tegra_xusb_lane *lane, *match = ERR_PTR(-ENODEV);

	क्रम (; map->type; map++) अणु
		अगर (port->index != map->port)
			जारी;

		lane = tegra_xusb_find_lane(port->padctl, map->type,
					    map->index);
		अगर (IS_ERR(lane))
			जारी;

		अगर (!tegra_xusb_lane_check(lane, function))
			जारी;

		अगर (!IS_ERR(match))
			dev_err(&port->dev, "conflicting match: %s-%u / %s\n",
				map->type, map->index, match->soc->name);
		अन्यथा
			match = lane;
	पूर्ण

	वापस match;
पूर्ण

अटल काष्ठा device_node *
tegra_xusb_find_port_node(काष्ठा tegra_xusb_padctl *padctl, स्थिर अक्षर *type,
			  अचिन्हित पूर्णांक index)
अणु
	काष्ठा device_node *ports, *np;
	अक्षर *name;

	ports = of_get_child_by_name(padctl->dev->of_node, "ports");
	अगर (!ports)
		वापस शून्य;

	name = kaप्र_लिखो(GFP_KERNEL, "%s-%u", type, index);
	अगर (!name) अणु
		of_node_put(ports);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण
	np = of_get_child_by_name(ports, name);
	kमुक्त(name);
	of_node_put(ports);

	वापस np;
पूर्ण

काष्ठा tegra_xusb_port *
tegra_xusb_find_port(काष्ठा tegra_xusb_padctl *padctl, स्थिर अक्षर *type,
		     अचिन्हित पूर्णांक index)
अणु
	काष्ठा tegra_xusb_port *port;
	काष्ठा device_node *np;

	np = tegra_xusb_find_port_node(padctl, type, index);
	अगर (!np)
		वापस शून्य;

	list_क्रम_each_entry(port, &padctl->ports, list) अणु
		अगर (np == port->dev.of_node) अणु
			of_node_put(np);
			वापस port;
		पूर्ण
	पूर्ण

	of_node_put(np);

	वापस शून्य;
पूर्ण

काष्ठा tegra_xusb_usb2_port *
tegra_xusb_find_usb2_port(काष्ठा tegra_xusb_padctl *padctl, अचिन्हित पूर्णांक index)
अणु
	काष्ठा tegra_xusb_port *port;

	port = tegra_xusb_find_port(padctl, "usb2", index);
	अगर (port)
		वापस to_usb2_port(port);

	वापस शून्य;
पूर्ण

काष्ठा tegra_xusb_usb3_port *
tegra_xusb_find_usb3_port(काष्ठा tegra_xusb_padctl *padctl, अचिन्हित पूर्णांक index)
अणु
	काष्ठा tegra_xusb_port *port;

	port = tegra_xusb_find_port(padctl, "usb3", index);
	अगर (port)
		वापस to_usb3_port(port);

	वापस शून्य;
पूर्ण

अटल व्योम tegra_xusb_port_release(काष्ठा device *dev)
अणु
	काष्ठा tegra_xusb_port *port = to_tegra_xusb_port(dev);

	अगर (port->ops->release)
		port->ops->release(port);
पूर्ण

अटल स्थिर काष्ठा device_type tegra_xusb_port_type = अणु
	.release = tegra_xusb_port_release,
पूर्ण;

अटल पूर्णांक tegra_xusb_port_init(काष्ठा tegra_xusb_port *port,
				काष्ठा tegra_xusb_padctl *padctl,
				काष्ठा device_node *np,
				स्थिर अक्षर *name,
				अचिन्हित पूर्णांक index)
अणु
	पूर्णांक err;

	INIT_LIST_HEAD(&port->list);
	port->padctl = padctl;
	port->index = index;

	device_initialize(&port->dev);
	port->dev.type = &tegra_xusb_port_type;
	port->dev.of_node = of_node_get(np);
	port->dev.parent = padctl->dev;

	err = dev_set_name(&port->dev, "%s-%u", name, index);
	अगर (err < 0)
		जाओ unरेजिस्टर;

	err = device_add(&port->dev);
	अगर (err < 0)
		जाओ unरेजिस्टर;

	वापस 0;

unरेजिस्टर:
	device_unरेजिस्टर(&port->dev);
	वापस err;
पूर्ण

अटल व्योम tegra_xusb_port_unरेजिस्टर(काष्ठा tegra_xusb_port *port)
अणु
	अगर (!IS_ERR_OR_शून्य(port->usb_role_sw)) अणु
		of_platक्रमm_depopulate(&port->dev);
		usb_role_चयन_unरेजिस्टर(port->usb_role_sw);
		cancel_work_sync(&port->usb_phy_work);
		usb_हटाओ_phy(&port->usb_phy);
	पूर्ण

	अगर (port->ops->हटाओ)
		port->ops->हटाओ(port);

	device_unरेजिस्टर(&port->dev);
पूर्ण

अटल स्थिर अक्षर *स्थिर modes[] = अणु
	[USB_DR_MODE_UNKNOWN] = "",
	[USB_DR_MODE_HOST] = "host",
	[USB_DR_MODE_PERIPHERAL] = "peripheral",
	[USB_DR_MODE_OTG] = "otg",
पूर्ण;

अटल स्थिर अक्षर * स्थिर usb_roles[] = अणु
	[USB_ROLE_NONE]		= "none",
	[USB_ROLE_HOST]		= "host",
	[USB_ROLE_DEVICE]	= "device",
पूर्ण;

अटल क्रमागत usb_phy_events to_usb_phy_event(क्रमागत usb_role role)
अणु
	चयन (role) अणु
	हाल USB_ROLE_DEVICE:
		वापस USB_EVENT_VBUS;

	हाल USB_ROLE_HOST:
		वापस USB_EVENT_ID;

	शेष:
		वापस USB_EVENT_NONE;
	पूर्ण
पूर्ण

अटल व्योम tegra_xusb_usb_phy_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा tegra_xusb_port *port = container_of(work,
						    काष्ठा tegra_xusb_port,
						    usb_phy_work);
	क्रमागत usb_role role = usb_role_चयन_get_role(port->usb_role_sw);

	usb_phy_set_event(&port->usb_phy, to_usb_phy_event(role));

	dev_dbg(&port->dev, "%s(): calling notifier for role %s\n", __func__,
		usb_roles[role]);

	atomic_notअगरier_call_chain(&port->usb_phy.notअगरier, 0, &port->usb_phy);
पूर्ण

अटल पूर्णांक tegra_xusb_role_sw_set(काष्ठा usb_role_चयन *sw,
				  क्रमागत usb_role role)
अणु
	काष्ठा tegra_xusb_port *port = usb_role_चयन_get_drvdata(sw);

	dev_dbg(&port->dev, "%s(): role %s\n", __func__, usb_roles[role]);

	schedule_work(&port->usb_phy_work);

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_xusb_set_peripheral(काष्ठा usb_otg *otg,
				     काष्ठा usb_gadget *gadget)
अणु
	काष्ठा tegra_xusb_port *port = container_of(otg->usb_phy,
						    काष्ठा tegra_xusb_port,
						    usb_phy);

	अगर (gadget != शून्य)
		schedule_work(&port->usb_phy_work);

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_xusb_set_host(काष्ठा usb_otg *otg, काष्ठा usb_bus *host)
अणु
	काष्ठा tegra_xusb_port *port = container_of(otg->usb_phy,
						    काष्ठा tegra_xusb_port,
						    usb_phy);

	अगर (host != शून्य)
		schedule_work(&port->usb_phy_work);

	वापस 0;
पूर्ण


अटल पूर्णांक tegra_xusb_setup_usb_role_चयन(काष्ठा tegra_xusb_port *port)
अणु
	काष्ठा tegra_xusb_lane *lane;
	काष्ठा usb_role_चयन_desc role_sx_desc = अणु
		.fwnode = dev_fwnode(&port->dev),
		.set = tegra_xusb_role_sw_set,
	पूर्ण;
	पूर्णांक err = 0;

	/*
	 * USB role चयन driver needs parent driver owner info. This is a
	 * suboptimal solution. TODO: Need to revisit this in a follow-up patch
	 * where an optimal solution is possible with changes to USB role
	 * चयन driver.
	 */
	port->dev.driver = devm_kzalloc(&port->dev,
					माप(काष्ठा device_driver),
					GFP_KERNEL);
	port->dev.driver->owner	 = THIS_MODULE;

	port->usb_role_sw = usb_role_चयन_रेजिस्टर(&port->dev,
						     &role_sx_desc);
	अगर (IS_ERR(port->usb_role_sw)) अणु
		err = PTR_ERR(port->usb_role_sw);
		dev_err(&port->dev, "failed to register USB role switch: %d",
			err);
		वापस err;
	पूर्ण

	INIT_WORK(&port->usb_phy_work, tegra_xusb_usb_phy_work);
	usb_role_चयन_set_drvdata(port->usb_role_sw, port);

	port->usb_phy.otg = devm_kzalloc(&port->dev, माप(काष्ठा usb_otg),
					 GFP_KERNEL);
	अगर (!port->usb_phy.otg)
		वापस -ENOMEM;

	lane = tegra_xusb_find_lane(port->padctl, "usb2", port->index);

	/*
	 * Assign phy dev to usb-phy dev. Host/device drivers can use phy
	 * reference to retrieve usb-phy details.
	 */
	port->usb_phy.dev = &lane->pad->lanes[port->index]->dev;
	port->usb_phy.dev->driver = port->dev.driver;
	port->usb_phy.otg->usb_phy = &port->usb_phy;
	port->usb_phy.otg->set_peripheral = tegra_xusb_set_peripheral;
	port->usb_phy.otg->set_host = tegra_xusb_set_host;

	err = usb_add_phy_dev(&port->usb_phy);
	अगर (err < 0) अणु
		dev_err(&port->dev, "Failed to add USB PHY: %d\n", err);
		वापस err;
	पूर्ण

	/* populate connector entry */
	of_platक्रमm_populate(port->dev.of_node, शून्य, शून्य, &port->dev);

	वापस err;
पूर्ण

अटल पूर्णांक tegra_xusb_usb2_port_parse_dt(काष्ठा tegra_xusb_usb2_port *usb2)
अणु
	काष्ठा tegra_xusb_port *port = &usb2->base;
	काष्ठा device_node *np = port->dev.of_node;
	स्थिर अक्षर *mode;
	पूर्णांक err;

	usb2->पूर्णांकernal = of_property_पढ़ो_bool(np, "nvidia,internal");

	अगर (!of_property_पढ़ो_string(np, "mode", &mode)) अणु
		पूर्णांक err = match_string(modes, ARRAY_SIZE(modes), mode);
		अगर (err < 0) अणु
			dev_err(&port->dev, "invalid value %s for \"mode\"\n",
				mode);
			usb2->mode = USB_DR_MODE_UNKNOWN;
		पूर्ण अन्यथा अणु
			usb2->mode = err;
		पूर्ण
	पूर्ण अन्यथा अणु
		usb2->mode = USB_DR_MODE_HOST;
	पूर्ण

	/* usb-role-चयन property is mandatory क्रम OTG/Peripheral modes */
	अगर (usb2->mode == USB_DR_MODE_PERIPHERAL ||
	    usb2->mode == USB_DR_MODE_OTG) अणु
		अगर (of_property_पढ़ो_bool(np, "usb-role-switch")) अणु
			err = tegra_xusb_setup_usb_role_चयन(port);
			अगर (err < 0)
				वापस err;
		पूर्ण अन्यथा अणु
			dev_err(&port->dev, "usb-role-switch not found for %s mode",
				modes[usb2->mode]);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	usb2->supply = regulator_get(&port->dev, "vbus");
	वापस PTR_ERR_OR_ZERO(usb2->supply);
पूर्ण

अटल पूर्णांक tegra_xusb_add_usb2_port(काष्ठा tegra_xusb_padctl *padctl,
				    अचिन्हित पूर्णांक index)
अणु
	काष्ठा tegra_xusb_usb2_port *usb2;
	काष्ठा device_node *np;
	पूर्णांक err = 0;

	/*
	 * USB2 ports करोn't require additional properties, but अगर the port is
	 * marked as disabled there is no reason to रेजिस्टर it.
	 */
	np = tegra_xusb_find_port_node(padctl, "usb2", index);
	अगर (!np || !of_device_is_available(np))
		जाओ out;

	usb2 = kzalloc(माप(*usb2), GFP_KERNEL);
	अगर (!usb2) अणु
		err = -ENOMEM;
		जाओ out;
	पूर्ण

	err = tegra_xusb_port_init(&usb2->base, padctl, np, "usb2", index);
	अगर (err < 0)
		जाओ out;

	usb2->base.ops = padctl->soc->ports.usb2.ops;

	usb2->base.lane = usb2->base.ops->map(&usb2->base);
	अगर (IS_ERR(usb2->base.lane)) अणु
		err = PTR_ERR(usb2->base.lane);
		जाओ out;
	पूर्ण

	err = tegra_xusb_usb2_port_parse_dt(usb2);
	अगर (err < 0) अणु
		tegra_xusb_port_unरेजिस्टर(&usb2->base);
		जाओ out;
	पूर्ण

	list_add_tail(&usb2->base.list, &padctl->ports);

out:
	of_node_put(np);
	वापस err;
पूर्ण

व्योम tegra_xusb_usb2_port_release(काष्ठा tegra_xusb_port *port)
अणु
	काष्ठा tegra_xusb_usb2_port *usb2 = to_usb2_port(port);

	kमुक्त(usb2);
पूर्ण

व्योम tegra_xusb_usb2_port_हटाओ(काष्ठा tegra_xusb_port *port)
अणु
	काष्ठा tegra_xusb_usb2_port *usb2 = to_usb2_port(port);

	regulator_put(usb2->supply);
पूर्ण

अटल पूर्णांक tegra_xusb_ulpi_port_parse_dt(काष्ठा tegra_xusb_ulpi_port *ulpi)
अणु
	काष्ठा tegra_xusb_port *port = &ulpi->base;
	काष्ठा device_node *np = port->dev.of_node;

	ulpi->पूर्णांकernal = of_property_पढ़ो_bool(np, "nvidia,internal");

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_xusb_add_ulpi_port(काष्ठा tegra_xusb_padctl *padctl,
				    अचिन्हित पूर्णांक index)
अणु
	काष्ठा tegra_xusb_ulpi_port *ulpi;
	काष्ठा device_node *np;
	पूर्णांक err = 0;

	np = tegra_xusb_find_port_node(padctl, "ulpi", index);
	अगर (!np || !of_device_is_available(np))
		जाओ out;

	ulpi = kzalloc(माप(*ulpi), GFP_KERNEL);
	अगर (!ulpi) अणु
		err = -ENOMEM;
		जाओ out;
	पूर्ण

	err = tegra_xusb_port_init(&ulpi->base, padctl, np, "ulpi", index);
	अगर (err < 0)
		जाओ out;

	ulpi->base.ops = padctl->soc->ports.ulpi.ops;

	ulpi->base.lane = ulpi->base.ops->map(&ulpi->base);
	अगर (IS_ERR(ulpi->base.lane)) अणु
		err = PTR_ERR(ulpi->base.lane);
		जाओ out;
	पूर्ण

	err = tegra_xusb_ulpi_port_parse_dt(ulpi);
	अगर (err < 0) अणु
		tegra_xusb_port_unरेजिस्टर(&ulpi->base);
		जाओ out;
	पूर्ण

	list_add_tail(&ulpi->base.list, &padctl->ports);

out:
	of_node_put(np);
	वापस err;
पूर्ण

व्योम tegra_xusb_ulpi_port_release(काष्ठा tegra_xusb_port *port)
अणु
	काष्ठा tegra_xusb_ulpi_port *ulpi = to_ulpi_port(port);

	kमुक्त(ulpi);
पूर्ण

अटल पूर्णांक tegra_xusb_hsic_port_parse_dt(काष्ठा tegra_xusb_hsic_port *hsic)
अणु
	/* XXX */
	वापस 0;
पूर्ण

अटल पूर्णांक tegra_xusb_add_hsic_port(काष्ठा tegra_xusb_padctl *padctl,
				    अचिन्हित पूर्णांक index)
अणु
	काष्ठा tegra_xusb_hsic_port *hsic;
	काष्ठा device_node *np;
	पूर्णांक err = 0;

	np = tegra_xusb_find_port_node(padctl, "hsic", index);
	अगर (!np || !of_device_is_available(np))
		जाओ out;

	hsic = kzalloc(माप(*hsic), GFP_KERNEL);
	अगर (!hsic) अणु
		err = -ENOMEM;
		जाओ out;
	पूर्ण

	err = tegra_xusb_port_init(&hsic->base, padctl, np, "hsic", index);
	अगर (err < 0)
		जाओ out;

	hsic->base.ops = padctl->soc->ports.hsic.ops;

	hsic->base.lane = hsic->base.ops->map(&hsic->base);
	अगर (IS_ERR(hsic->base.lane)) अणु
		err = PTR_ERR(hsic->base.lane);
		जाओ out;
	पूर्ण

	err = tegra_xusb_hsic_port_parse_dt(hsic);
	अगर (err < 0) अणु
		tegra_xusb_port_unरेजिस्टर(&hsic->base);
		जाओ out;
	पूर्ण

	list_add_tail(&hsic->base.list, &padctl->ports);

out:
	of_node_put(np);
	वापस err;
पूर्ण

व्योम tegra_xusb_hsic_port_release(काष्ठा tegra_xusb_port *port)
अणु
	काष्ठा tegra_xusb_hsic_port *hsic = to_hsic_port(port);

	kमुक्त(hsic);
पूर्ण

अटल पूर्णांक tegra_xusb_usb3_port_parse_dt(काष्ठा tegra_xusb_usb3_port *usb3)
अणु
	काष्ठा tegra_xusb_port *port = &usb3->base;
	काष्ठा device_node *np = port->dev.of_node;
	क्रमागत usb_device_speed maximum_speed;
	u32 value;
	पूर्णांक err;

	err = of_property_पढ़ो_u32(np, "nvidia,usb2-companion", &value);
	अगर (err < 0) अणु
		dev_err(&port->dev, "failed to read port: %d\n", err);
		वापस err;
	पूर्ण

	usb3->port = value;

	usb3->पूर्णांकernal = of_property_पढ़ो_bool(np, "nvidia,internal");

	अगर (device_property_present(&port->dev, "maximum-speed")) अणु
		maximum_speed =  usb_get_maximum_speed(&port->dev);
		अगर (maximum_speed == USB_SPEED_SUPER)
			usb3->disable_gen2 = true;
		अन्यथा अगर (maximum_speed == USB_SPEED_SUPER_PLUS)
			usb3->disable_gen2 = false;
		अन्यथा
			वापस -EINVAL;
	पूर्ण

	usb3->supply = regulator_get(&port->dev, "vbus");
	वापस PTR_ERR_OR_ZERO(usb3->supply);
पूर्ण

अटल पूर्णांक tegra_xusb_add_usb3_port(काष्ठा tegra_xusb_padctl *padctl,
				    अचिन्हित पूर्णांक index)
अणु
	काष्ठा tegra_xusb_usb3_port *usb3;
	काष्ठा device_node *np;
	पूर्णांक err = 0;

	/*
	 * If there is no supplemental configuration in the device tree the
	 * port is unusable. But it is valid to configure only a single port,
	 * hence वापस 0 instead of an error to allow ports to be optional.
	 */
	np = tegra_xusb_find_port_node(padctl, "usb3", index);
	अगर (!np || !of_device_is_available(np))
		जाओ out;

	usb3 = kzalloc(माप(*usb3), GFP_KERNEL);
	अगर (!usb3) अणु
		err = -ENOMEM;
		जाओ out;
	पूर्ण

	err = tegra_xusb_port_init(&usb3->base, padctl, np, "usb3", index);
	अगर (err < 0)
		जाओ out;

	usb3->base.ops = padctl->soc->ports.usb3.ops;

	usb3->base.lane = usb3->base.ops->map(&usb3->base);
	अगर (IS_ERR(usb3->base.lane)) अणु
		err = PTR_ERR(usb3->base.lane);
		जाओ out;
	पूर्ण

	err = tegra_xusb_usb3_port_parse_dt(usb3);
	अगर (err < 0) अणु
		tegra_xusb_port_unरेजिस्टर(&usb3->base);
		जाओ out;
	पूर्ण

	list_add_tail(&usb3->base.list, &padctl->ports);

out:
	of_node_put(np);
	वापस err;
पूर्ण

व्योम tegra_xusb_usb3_port_release(काष्ठा tegra_xusb_port *port)
अणु
	काष्ठा tegra_xusb_usb3_port *usb3 = to_usb3_port(port);

	kमुक्त(usb3);
पूर्ण

व्योम tegra_xusb_usb3_port_हटाओ(काष्ठा tegra_xusb_port *port)
अणु
	काष्ठा tegra_xusb_usb3_port *usb3 = to_usb3_port(port);

	regulator_put(usb3->supply);
पूर्ण

अटल व्योम __tegra_xusb_हटाओ_ports(काष्ठा tegra_xusb_padctl *padctl)
अणु
	काष्ठा tegra_xusb_port *port, *पंचांगp;

	list_क्रम_each_entry_safe_reverse(port, पंचांगp, &padctl->ports, list) अणु
		list_del(&port->list);
		tegra_xusb_port_unरेजिस्टर(port);
	पूर्ण
पूर्ण

अटल पूर्णांक tegra_xusb_find_unused_usb3_port(काष्ठा tegra_xusb_padctl *padctl)
अणु
	काष्ठा device_node *np;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < padctl->soc->ports.usb3.count; i++) अणु
		np = tegra_xusb_find_port_node(padctl, "usb3", i);
		अगर (!np || !of_device_is_available(np))
			वापस i;
	पूर्ण

	वापस -ENODEV;
पूर्ण

अटल bool tegra_xusb_port_is_companion(काष्ठा tegra_xusb_usb2_port *usb2)
अणु
	अचिन्हित पूर्णांक i;
	काष्ठा tegra_xusb_usb3_port *usb3;
	काष्ठा tegra_xusb_padctl *padctl = usb2->base.padctl;

	क्रम (i = 0; i < padctl->soc->ports.usb3.count; i++) अणु
		usb3 = tegra_xusb_find_usb3_port(padctl, i);
		अगर (usb3 && usb3->port == usb2->base.index)
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल पूर्णांक tegra_xusb_update_usb3_fake_port(काष्ठा tegra_xusb_usb2_port *usb2)
अणु
	पूर्णांक fake;

	/* Disable usb3_port_fake usage by शेष and assign अगर needed */
	usb2->usb3_port_fake = -1;

	अगर ((usb2->mode == USB_DR_MODE_OTG ||
	     usb2->mode == USB_DR_MODE_PERIPHERAL) &&
		!tegra_xusb_port_is_companion(usb2)) अणु
		fake = tegra_xusb_find_unused_usb3_port(usb2->base.padctl);
		अगर (fake < 0) अणु
			dev_err(&usb2->base.dev, "no unused USB3 ports available\n");
			वापस -ENODEV;
		पूर्ण

		dev_dbg(&usb2->base.dev, "Found unused usb3 port: %d\n", fake);
		usb2->usb3_port_fake = fake;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_xusb_setup_ports(काष्ठा tegra_xusb_padctl *padctl)
अणु
	काष्ठा tegra_xusb_port *port;
	काष्ठा tegra_xusb_usb2_port *usb2;
	अचिन्हित पूर्णांक i;
	पूर्णांक err = 0;

	mutex_lock(&padctl->lock);

	क्रम (i = 0; i < padctl->soc->ports.usb2.count; i++) अणु
		err = tegra_xusb_add_usb2_port(padctl, i);
		अगर (err < 0)
			जाओ हटाओ_ports;
	पूर्ण

	क्रम (i = 0; i < padctl->soc->ports.ulpi.count; i++) अणु
		err = tegra_xusb_add_ulpi_port(padctl, i);
		अगर (err < 0)
			जाओ हटाओ_ports;
	पूर्ण

	क्रम (i = 0; i < padctl->soc->ports.hsic.count; i++) अणु
		err = tegra_xusb_add_hsic_port(padctl, i);
		अगर (err < 0)
			जाओ हटाओ_ports;
	पूर्ण

	क्रम (i = 0; i < padctl->soc->ports.usb3.count; i++) अणु
		err = tegra_xusb_add_usb3_port(padctl, i);
		अगर (err < 0)
			जाओ हटाओ_ports;
	पूर्ण

	अगर (padctl->soc->need_fake_usb3_port) अणु
		क्रम (i = 0; i < padctl->soc->ports.usb2.count; i++) अणु
			usb2 = tegra_xusb_find_usb2_port(padctl, i);
			अगर (!usb2)
				जारी;

			err = tegra_xusb_update_usb3_fake_port(usb2);
			अगर (err < 0)
				जाओ हटाओ_ports;
		पूर्ण
	पूर्ण

	list_क्रम_each_entry(port, &padctl->ports, list) अणु
		err = port->ops->enable(port);
		अगर (err < 0)
			dev_err(padctl->dev, "failed to enable port %s: %d\n",
				dev_name(&port->dev), err);
	पूर्ण

	जाओ unlock;

हटाओ_ports:
	__tegra_xusb_हटाओ_ports(padctl);
unlock:
	mutex_unlock(&padctl->lock);
	वापस err;
पूर्ण

अटल व्योम tegra_xusb_हटाओ_ports(काष्ठा tegra_xusb_padctl *padctl)
अणु
	mutex_lock(&padctl->lock);
	__tegra_xusb_हटाओ_ports(padctl);
	mutex_unlock(&padctl->lock);
पूर्ण

अटल पूर्णांक tegra_xusb_padctl_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	स्थिर काष्ठा tegra_xusb_padctl_soc *soc;
	काष्ठा tegra_xusb_padctl *padctl;
	स्थिर काष्ठा of_device_id *match;
	पूर्णांक err;

	/* क्रम backwards compatibility with old device trees */
	np = of_get_child_by_name(np, "pads");
	अगर (!np) अणु
		dev_warn(&pdev->dev, "deprecated DT, using legacy driver\n");
		वापस tegra_xusb_padctl_legacy_probe(pdev);
	पूर्ण

	of_node_put(np);

	match = of_match_node(tegra_xusb_padctl_of_match, pdev->dev.of_node);
	soc = match->data;

	padctl = soc->ops->probe(&pdev->dev, soc);
	अगर (IS_ERR(padctl))
		वापस PTR_ERR(padctl);

	platक्रमm_set_drvdata(pdev, padctl);
	INIT_LIST_HEAD(&padctl->ports);
	INIT_LIST_HEAD(&padctl->lanes);
	INIT_LIST_HEAD(&padctl->pads);
	mutex_init(&padctl->lock);

	padctl->regs = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(padctl->regs)) अणु
		err = PTR_ERR(padctl->regs);
		जाओ हटाओ;
	पूर्ण

	padctl->rst = devm_reset_control_get(&pdev->dev, शून्य);
	अगर (IS_ERR(padctl->rst)) अणु
		err = PTR_ERR(padctl->rst);
		जाओ हटाओ;
	पूर्ण

	padctl->supplies = devm_kसुस्मृति(&pdev->dev, padctl->soc->num_supplies,
					माप(*padctl->supplies), GFP_KERNEL);
	अगर (!padctl->supplies) अणु
		err = -ENOMEM;
		जाओ हटाओ;
	पूर्ण

	regulator_bulk_set_supply_names(padctl->supplies,
					padctl->soc->supply_names,
					padctl->soc->num_supplies);

	err = devm_regulator_bulk_get(&pdev->dev, padctl->soc->num_supplies,
				      padctl->supplies);
	अगर (err < 0) अणु
		dev_err_probe(&pdev->dev, err, "failed to get regulators\n");
		जाओ हटाओ;
	पूर्ण

	err = reset_control_deनिश्चित(padctl->rst);
	अगर (err < 0)
		जाओ हटाओ;

	err = regulator_bulk_enable(padctl->soc->num_supplies,
				    padctl->supplies);
	अगर (err < 0) अणु
		dev_err(&pdev->dev, "failed to enable supplies: %d\n", err);
		जाओ reset;
	पूर्ण

	err = tegra_xusb_setup_pads(padctl);
	अगर (err < 0) अणु
		dev_err(&pdev->dev, "failed to setup pads: %d\n", err);
		जाओ घातer_करोwn;
	पूर्ण

	err = tegra_xusb_setup_ports(padctl);
	अगर (err) अणु
		स्थिर अक्षर *level = KERN_ERR;

		अगर (err == -EPROBE_DEFER)
			level = KERN_DEBUG;

		dev_prपूर्णांकk(level, &pdev->dev,
			   dev_fmt("failed to setup XUSB ports: %d\n"), err);
		जाओ हटाओ_pads;
	पूर्ण

	वापस 0;

हटाओ_pads:
	tegra_xusb_हटाओ_pads(padctl);
घातer_करोwn:
	regulator_bulk_disable(padctl->soc->num_supplies, padctl->supplies);
reset:
	reset_control_निश्चित(padctl->rst);
हटाओ:
	platक्रमm_set_drvdata(pdev, शून्य);
	soc->ops->हटाओ(padctl);
	वापस err;
पूर्ण

अटल पूर्णांक tegra_xusb_padctl_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा tegra_xusb_padctl *padctl = platक्रमm_get_drvdata(pdev);
	पूर्णांक err;

	tegra_xusb_हटाओ_ports(padctl);
	tegra_xusb_हटाओ_pads(padctl);

	err = regulator_bulk_disable(padctl->soc->num_supplies,
				     padctl->supplies);
	अगर (err < 0)
		dev_err(&pdev->dev, "failed to disable supplies: %d\n", err);

	err = reset_control_निश्चित(padctl->rst);
	अगर (err < 0)
		dev_err(&pdev->dev, "failed to assert reset: %d\n", err);

	padctl->soc->ops->हटाओ(padctl);

	वापस err;
पूर्ण

अटल काष्ठा platक्रमm_driver tegra_xusb_padctl_driver = अणु
	.driver = अणु
		.name = "tegra-xusb-padctl",
		.of_match_table = tegra_xusb_padctl_of_match,
	पूर्ण,
	.probe = tegra_xusb_padctl_probe,
	.हटाओ = tegra_xusb_padctl_हटाओ,
पूर्ण;
module_platक्रमm_driver(tegra_xusb_padctl_driver);

काष्ठा tegra_xusb_padctl *tegra_xusb_padctl_get(काष्ठा device *dev)
अणु
	काष्ठा tegra_xusb_padctl *padctl;
	काष्ठा platक्रमm_device *pdev;
	काष्ठा device_node *np;

	np = of_parse_phandle(dev->of_node, "nvidia,xusb-padctl", 0);
	अगर (!np)
		वापस ERR_PTR(-EINVAL);

	/*
	 * This is slightly ugly. A better implementation would be to keep a
	 * registry of pad controllers, but since there will almost certainly
	 * only ever be one per SoC that would be a little overसमाप्त.
	 */
	pdev = of_find_device_by_node(np);
	अगर (!pdev) अणु
		of_node_put(np);
		वापस ERR_PTR(-ENODEV);
	पूर्ण

	of_node_put(np);

	padctl = platक्रमm_get_drvdata(pdev);
	अगर (!padctl) अणु
		put_device(&pdev->dev);
		वापस ERR_PTR(-EPROBE_DEFER);
	पूर्ण

	वापस padctl;
पूर्ण
EXPORT_SYMBOL_GPL(tegra_xusb_padctl_get);

व्योम tegra_xusb_padctl_put(काष्ठा tegra_xusb_padctl *padctl)
अणु
	अगर (padctl)
		put_device(padctl->dev);
पूर्ण
EXPORT_SYMBOL_GPL(tegra_xusb_padctl_put);

पूर्णांक tegra_xusb_padctl_usb3_save_context(काष्ठा tegra_xusb_padctl *padctl,
					अचिन्हित पूर्णांक port)
अणु
	अगर (padctl->soc->ops->usb3_save_context)
		वापस padctl->soc->ops->usb3_save_context(padctl, port);

	वापस -ENOSYS;
पूर्ण
EXPORT_SYMBOL_GPL(tegra_xusb_padctl_usb3_save_context);

पूर्णांक tegra_xusb_padctl_hsic_set_idle(काष्ठा tegra_xusb_padctl *padctl,
				    अचिन्हित पूर्णांक port, bool idle)
अणु
	अगर (padctl->soc->ops->hsic_set_idle)
		वापस padctl->soc->ops->hsic_set_idle(padctl, port, idle);

	वापस -ENOSYS;
पूर्ण
EXPORT_SYMBOL_GPL(tegra_xusb_padctl_hsic_set_idle);

पूर्णांक tegra_xusb_padctl_usb3_set_lfps_detect(काष्ठा tegra_xusb_padctl *padctl,
					   अचिन्हित पूर्णांक port, bool enable)
अणु
	अगर (padctl->soc->ops->usb3_set_lfps_detect)
		वापस padctl->soc->ops->usb3_set_lfps_detect(padctl, port,
							      enable);

	वापस -ENOSYS;
पूर्ण
EXPORT_SYMBOL_GPL(tegra_xusb_padctl_usb3_set_lfps_detect);

पूर्णांक tegra_xusb_padctl_set_vbus_override(काष्ठा tegra_xusb_padctl *padctl,
							bool val)
अणु
	अगर (padctl->soc->ops->vbus_override)
		वापस padctl->soc->ops->vbus_override(padctl, val);

	वापस -ENOTSUPP;
पूर्ण
EXPORT_SYMBOL_GPL(tegra_xusb_padctl_set_vbus_override);

पूर्णांक tegra_phy_xusb_uपंचांगi_port_reset(काष्ठा phy *phy)
अणु
	काष्ठा tegra_xusb_lane *lane = phy_get_drvdata(phy);
	काष्ठा tegra_xusb_padctl *padctl = lane->pad->padctl;

	अगर (padctl->soc->ops->uपंचांगi_port_reset)
		वापस padctl->soc->ops->uपंचांगi_port_reset(phy);

	वापस -ENOTSUPP;
पूर्ण
EXPORT_SYMBOL_GPL(tegra_phy_xusb_uपंचांगi_port_reset);

पूर्णांक tegra_xusb_padctl_get_usb3_companion(काष्ठा tegra_xusb_padctl *padctl,
				    अचिन्हित पूर्णांक port)
अणु
	काष्ठा tegra_xusb_usb2_port *usb2;
	काष्ठा tegra_xusb_usb3_port *usb3;
	पूर्णांक i;

	usb2 = tegra_xusb_find_usb2_port(padctl, port);
	अगर (!usb2)
		वापस -EINVAL;

	क्रम (i = 0; i < padctl->soc->ports.usb3.count; i++) अणु
		usb3 = tegra_xusb_find_usb3_port(padctl, i);
		अगर (usb3 && usb3->port == usb2->base.index)
			वापस usb3->base.index;
	पूर्ण

	वापस -ENODEV;
पूर्ण
EXPORT_SYMBOL_GPL(tegra_xusb_padctl_get_usb3_companion);

MODULE_AUTHOR("Thierry Reding <treding@nvidia.com>");
MODULE_DESCRIPTION("Tegra XUSB Pad Controller driver");
MODULE_LICENSE("GPL v2");
