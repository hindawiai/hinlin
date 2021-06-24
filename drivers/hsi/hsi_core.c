<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * HSI core.
 *
 * Copyright (C) 2010 Nokia Corporation. All rights reserved.
 *
 * Contact: Carlos Chinea <carlos.chinea@nokia.com>
 */
#समावेश <linux/hsi/hsi.h>
#समावेश <linux/compiler.h>
#समावेश <linux/list.h>
#समावेश <linux/kobject.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश <linux/notअगरier.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश "hsi_core.h"

अटल sमाप_प्रकार modalias_show(काष्ठा device *dev,
			काष्ठा device_attribute *a __maybe_unused, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "hsi:%s\n", dev_name(dev));
पूर्ण
अटल DEVICE_ATTR_RO(modalias);

अटल काष्ठा attribute *hsi_bus_dev_attrs[] = अणु
	&dev_attr_modalias.attr,
	शून्य,
पूर्ण;
ATTRIBUTE_GROUPS(hsi_bus_dev);

अटल पूर्णांक hsi_bus_uevent(काष्ठा device *dev, काष्ठा kobj_uevent_env *env)
अणु
	add_uevent_var(env, "MODALIAS=hsi:%s", dev_name(dev));

	वापस 0;
पूर्ण

अटल पूर्णांक hsi_bus_match(काष्ठा device *dev, काष्ठा device_driver *driver)
अणु
	अगर (of_driver_match_device(dev, driver))
		वापस true;

	अगर (म_भेद(dev_name(dev), driver->name) == 0)
		वापस true;

	वापस false;
पूर्ण

अटल काष्ठा bus_type hsi_bus_type = अणु
	.name		= "hsi",
	.dev_groups	= hsi_bus_dev_groups,
	.match		= hsi_bus_match,
	.uevent		= hsi_bus_uevent,
पूर्ण;

अटल व्योम hsi_client_release(काष्ठा device *dev)
अणु
	काष्ठा hsi_client *cl = to_hsi_client(dev);

	kमुक्त(cl->tx_cfg.channels);
	kमुक्त(cl->rx_cfg.channels);
	kमुक्त(cl);
पूर्ण

काष्ठा hsi_client *hsi_new_client(काष्ठा hsi_port *port,
						काष्ठा hsi_board_info *info)
अणु
	काष्ठा hsi_client *cl;
	माप_प्रकार size;

	cl = kzalloc(माप(*cl), GFP_KERNEL);
	अगर (!cl)
		जाओ err;

	cl->tx_cfg = info->tx_cfg;
	अगर (cl->tx_cfg.channels) अणु
		size = cl->tx_cfg.num_channels * माप(*cl->tx_cfg.channels);
		cl->tx_cfg.channels = kmemdup(info->tx_cfg.channels, size,
					      GFP_KERNEL);
		अगर (!cl->tx_cfg.channels)
			जाओ err_tx;
	पूर्ण

	cl->rx_cfg = info->rx_cfg;
	अगर (cl->rx_cfg.channels) अणु
		size = cl->rx_cfg.num_channels * माप(*cl->rx_cfg.channels);
		cl->rx_cfg.channels = kmemdup(info->rx_cfg.channels, size,
					      GFP_KERNEL);
		अगर (!cl->rx_cfg.channels)
			जाओ err_rx;
	पूर्ण

	cl->device.bus = &hsi_bus_type;
	cl->device.parent = &port->device;
	cl->device.release = hsi_client_release;
	dev_set_name(&cl->device, "%s", info->name);
	cl->device.platक्रमm_data = info->platक्रमm_data;
	अगर (info->archdata)
		cl->device.archdata = *info->archdata;
	अगर (device_रेजिस्टर(&cl->device) < 0) अणु
		pr_err("hsi: failed to register client: %s\n", info->name);
		put_device(&cl->device);
	पूर्ण

	वापस cl;
err_rx:
	kमुक्त(cl->tx_cfg.channels);
err_tx:
	kमुक्त(cl);
err:
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(hsi_new_client);

अटल व्योम hsi_scan_board_info(काष्ठा hsi_controller *hsi)
अणु
	काष्ठा hsi_cl_info *cl_info;
	काष्ठा hsi_port	*p;

	list_क्रम_each_entry(cl_info, &hsi_board_list, list)
		अगर (cl_info->info.hsi_id == hsi->id) अणु
			p = hsi_find_port_num(hsi, cl_info->info.port);
			अगर (!p)
				जारी;
			hsi_new_client(p, &cl_info->info);
		पूर्ण
पूर्ण

#अगर_घोषित CONFIG_OF
अटल काष्ठा hsi_board_info hsi_अक्षर_dev_info = अणु
	.name = "hsi_char",
पूर्ण;

अटल पूर्णांक hsi_of_property_parse_mode(काष्ठा device_node *client, अक्षर *name,
				      अचिन्हित पूर्णांक *result)
अणु
	स्थिर अक्षर *mode;
	पूर्णांक err;

	err = of_property_पढ़ो_string(client, name, &mode);
	अगर (err < 0)
		वापस err;

	अगर (म_भेद(mode, "stream") == 0)
		*result = HSI_MODE_STREAM;
	अन्यथा अगर (म_भेद(mode, "frame") == 0)
		*result = HSI_MODE_FRAME;
	अन्यथा
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक hsi_of_property_parse_flow(काष्ठा device_node *client, अक्षर *name,
				      अचिन्हित पूर्णांक *result)
अणु
	स्थिर अक्षर *flow;
	पूर्णांक err;

	err = of_property_पढ़ो_string(client, name, &flow);
	अगर (err < 0)
		वापस err;

	अगर (म_भेद(flow, "synchronized") == 0)
		*result = HSI_FLOW_SYNC;
	अन्यथा अगर (म_भेद(flow, "pipeline") == 0)
		*result = HSI_FLOW_PIPE;
	अन्यथा
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक hsi_of_property_parse_arb_mode(काष्ठा device_node *client,
					  अक्षर *name, अचिन्हित पूर्णांक *result)
अणु
	स्थिर अक्षर *arb_mode;
	पूर्णांक err;

	err = of_property_पढ़ो_string(client, name, &arb_mode);
	अगर (err < 0)
		वापस err;

	अगर (म_भेद(arb_mode, "round-robin") == 0)
		*result = HSI_ARB_RR;
	अन्यथा अगर (म_भेद(arb_mode, "priority") == 0)
		*result = HSI_ARB_PRIO;
	अन्यथा
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल व्योम hsi_add_client_from_dt(काष्ठा hsi_port *port,
						काष्ठा device_node *client)
अणु
	काष्ठा hsi_client *cl;
	काष्ठा hsi_channel channel;
	काष्ठा property *prop;
	अक्षर name[32];
	पूर्णांक length, cells, err, i, max_chan, mode;

	cl = kzalloc(माप(*cl), GFP_KERNEL);
	अगर (!cl)
		वापस;

	err = of_modalias_node(client, name, माप(name));
	अगर (err)
		जाओ err;

	err = hsi_of_property_parse_mode(client, "hsi-mode", &mode);
	अगर (err) अणु
		err = hsi_of_property_parse_mode(client, "hsi-rx-mode",
						 &cl->rx_cfg.mode);
		अगर (err)
			जाओ err;

		err = hsi_of_property_parse_mode(client, "hsi-tx-mode",
						 &cl->tx_cfg.mode);
		अगर (err)
			जाओ err;
	पूर्ण अन्यथा अणु
		cl->rx_cfg.mode = mode;
		cl->tx_cfg.mode = mode;
	पूर्ण

	err = of_property_पढ़ो_u32(client, "hsi-speed-kbps",
				   &cl->tx_cfg.speed);
	अगर (err)
		जाओ err;
	cl->rx_cfg.speed = cl->tx_cfg.speed;

	err = hsi_of_property_parse_flow(client, "hsi-flow",
					 &cl->rx_cfg.flow);
	अगर (err)
		जाओ err;

	err = hsi_of_property_parse_arb_mode(client, "hsi-arb-mode",
					     &cl->rx_cfg.arb_mode);
	अगर (err)
		जाओ err;

	prop = of_find_property(client, "hsi-channel-ids", &length);
	अगर (!prop) अणु
		err = -EINVAL;
		जाओ err;
	पूर्ण

	cells = length / माप(u32);

	cl->rx_cfg.num_channels = cells;
	cl->tx_cfg.num_channels = cells;
	cl->rx_cfg.channels = kसुस्मृति(cells, माप(channel), GFP_KERNEL);
	अगर (!cl->rx_cfg.channels) अणु
		err = -ENOMEM;
		जाओ err;
	पूर्ण

	cl->tx_cfg.channels = kसुस्मृति(cells, माप(channel), GFP_KERNEL);
	अगर (!cl->tx_cfg.channels) अणु
		err = -ENOMEM;
		जाओ err2;
	पूर्ण

	max_chan = 0;
	क्रम (i = 0; i < cells; i++) अणु
		err = of_property_पढ़ो_u32_index(client, "hsi-channel-ids", i,
						 &channel.id);
		अगर (err)
			जाओ err3;

		err = of_property_पढ़ो_string_index(client, "hsi-channel-names",
						    i, &channel.name);
		अगर (err)
			channel.name = शून्य;

		अगर (channel.id > max_chan)
			max_chan = channel.id;

		cl->rx_cfg.channels[i] = channel;
		cl->tx_cfg.channels[i] = channel;
	पूर्ण

	cl->rx_cfg.num_hw_channels = max_chan + 1;
	cl->tx_cfg.num_hw_channels = max_chan + 1;

	cl->device.bus = &hsi_bus_type;
	cl->device.parent = &port->device;
	cl->device.release = hsi_client_release;
	cl->device.of_node = client;

	dev_set_name(&cl->device, "%s", name);
	अगर (device_रेजिस्टर(&cl->device) < 0) अणु
		pr_err("hsi: failed to register client: %s\n", name);
		put_device(&cl->device);
	पूर्ण

	वापस;

err3:
	kमुक्त(cl->tx_cfg.channels);
err2:
	kमुक्त(cl->rx_cfg.channels);
err:
	kमुक्त(cl);
	pr_err("hsi client: missing or incorrect of property: err=%d\n", err);
पूर्ण

व्योम hsi_add_clients_from_dt(काष्ठा hsi_port *port, काष्ठा device_node *clients)
अणु
	काष्ठा device_node *child;

	/* रेजिस्टर hsi-अक्षर device */
	hsi_new_client(port, &hsi_अक्षर_dev_info);

	क्रम_each_available_child_of_node(clients, child)
		hsi_add_client_from_dt(port, child);
पूर्ण
EXPORT_SYMBOL_GPL(hsi_add_clients_from_dt);
#पूर्ण_अगर

पूर्णांक hsi_हटाओ_client(काष्ठा device *dev, व्योम *data __maybe_unused)
अणु
	device_unरेजिस्टर(dev);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(hsi_हटाओ_client);

अटल पूर्णांक hsi_हटाओ_port(काष्ठा device *dev, व्योम *data __maybe_unused)
अणु
	device_क्रम_each_child(dev, शून्य, hsi_हटाओ_client);
	device_unरेजिस्टर(dev);

	वापस 0;
पूर्ण

अटल व्योम hsi_controller_release(काष्ठा device *dev)
अणु
	काष्ठा hsi_controller *hsi = to_hsi_controller(dev);

	kमुक्त(hsi->port);
	kमुक्त(hsi);
पूर्ण

अटल व्योम hsi_port_release(काष्ठा device *dev)
अणु
	kमुक्त(to_hsi_port(dev));
पूर्ण

/**
 * hsi_port_unरेजिस्टर_clients - Unरेजिस्टर an HSI port
 * @port: The HSI port to unरेजिस्टर
 */
व्योम hsi_port_unरेजिस्टर_clients(काष्ठा hsi_port *port)
अणु
	device_क्रम_each_child(&port->device, शून्य, hsi_हटाओ_client);
पूर्ण
EXPORT_SYMBOL_GPL(hsi_port_unरेजिस्टर_clients);

/**
 * hsi_unरेजिस्टर_controller - Unरेजिस्टर an HSI controller
 * @hsi: The HSI controller to रेजिस्टर
 */
व्योम hsi_unरेजिस्टर_controller(काष्ठा hsi_controller *hsi)
अणु
	device_क्रम_each_child(&hsi->device, शून्य, hsi_हटाओ_port);
	device_unरेजिस्टर(&hsi->device);
पूर्ण
EXPORT_SYMBOL_GPL(hsi_unरेजिस्टर_controller);

/**
 * hsi_रेजिस्टर_controller - Register an HSI controller and its ports
 * @hsi: The HSI controller to रेजिस्टर
 *
 * Returns -त्रुटि_सं on failure, 0 on success.
 */
पूर्णांक hsi_रेजिस्टर_controller(काष्ठा hsi_controller *hsi)
अणु
	अचिन्हित पूर्णांक i;
	पूर्णांक err;

	err = device_add(&hsi->device);
	अगर (err < 0)
		वापस err;
	क्रम (i = 0; i < hsi->num_ports; i++) अणु
		hsi->port[i]->device.parent = &hsi->device;
		err = device_add(&hsi->port[i]->device);
		अगर (err < 0)
			जाओ out;
	पूर्ण
	/* Populate HSI bus with HSI clients */
	hsi_scan_board_info(hsi);

	वापस 0;
out:
	जबतक (i-- > 0)
		device_del(&hsi->port[i]->device);
	device_del(&hsi->device);

	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(hsi_रेजिस्टर_controller);

/**
 * hsi_रेजिस्टर_client_driver - Register an HSI client to the HSI bus
 * @drv: HSI client driver to रेजिस्टर
 *
 * Returns -त्रुटि_सं on failure, 0 on success.
 */
पूर्णांक hsi_रेजिस्टर_client_driver(काष्ठा hsi_client_driver *drv)
अणु
	drv->driver.bus = &hsi_bus_type;

	वापस driver_रेजिस्टर(&drv->driver);
पूर्ण
EXPORT_SYMBOL_GPL(hsi_रेजिस्टर_client_driver);

अटल अंतरभूत पूर्णांक hsi_dummy_msg(काष्ठा hsi_msg *msg __maybe_unused)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक hsi_dummy_cl(काष्ठा hsi_client *cl __maybe_unused)
अणु
	वापस 0;
पूर्ण

/**
 * hsi_put_controller - Free an HSI controller
 *
 * @hsi: Poपूर्णांकer to the HSI controller to मुक्तd
 *
 * HSI controller drivers should only use this function अगर they need
 * to मुक्त their allocated hsi_controller काष्ठाures beक्रमe a successful
 * call to hsi_रेजिस्टर_controller. Other use is not allowed.
 */
व्योम hsi_put_controller(काष्ठा hsi_controller *hsi)
अणु
	अचिन्हित पूर्णांक i;

	अगर (!hsi)
		वापस;

	क्रम (i = 0; i < hsi->num_ports; i++)
		अगर (hsi->port && hsi->port[i])
			put_device(&hsi->port[i]->device);
	put_device(&hsi->device);
पूर्ण
EXPORT_SYMBOL_GPL(hsi_put_controller);

/**
 * hsi_alloc_controller - Allocate an HSI controller and its ports
 * @n_ports: Number of ports on the HSI controller
 * @flags: Kernel allocation flags
 *
 * Return शून्य on failure or a poपूर्णांकer to an hsi_controller on success.
 */
काष्ठा hsi_controller *hsi_alloc_controller(अचिन्हित पूर्णांक n_ports, gfp_t flags)
अणु
	काष्ठा hsi_controller	*hsi;
	काष्ठा hsi_port		**port;
	अचिन्हित पूर्णांक		i;

	अगर (!n_ports)
		वापस शून्य;

	hsi = kzalloc(माप(*hsi), flags);
	अगर (!hsi)
		वापस शून्य;
	port = kसुस्मृति(n_ports, माप(*port), flags);
	अगर (!port) अणु
		kमुक्त(hsi);
		वापस शून्य;
	पूर्ण
	hsi->num_ports = n_ports;
	hsi->port = port;
	hsi->device.release = hsi_controller_release;
	device_initialize(&hsi->device);

	क्रम (i = 0; i < n_ports; i++) अणु
		port[i] = kzalloc(माप(**port), flags);
		अगर (port[i] == शून्य)
			जाओ out;
		port[i]->num = i;
		port[i]->async = hsi_dummy_msg;
		port[i]->setup = hsi_dummy_cl;
		port[i]->flush = hsi_dummy_cl;
		port[i]->start_tx = hsi_dummy_cl;
		port[i]->stop_tx = hsi_dummy_cl;
		port[i]->release = hsi_dummy_cl;
		mutex_init(&port[i]->lock);
		BLOCKING_INIT_NOTIFIER_HEAD(&port[i]->n_head);
		dev_set_name(&port[i]->device, "port%d", i);
		hsi->port[i]->device.release = hsi_port_release;
		device_initialize(&hsi->port[i]->device);
	पूर्ण

	वापस hsi;
out:
	hsi_put_controller(hsi);

	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(hsi_alloc_controller);

/**
 * hsi_मुक्त_msg - Free an HSI message
 * @msg: Poपूर्णांकer to the HSI message
 *
 * Client is responsible to मुक्त the buffers poपूर्णांकed by the scatterlists.
 */
व्योम hsi_मुक्त_msg(काष्ठा hsi_msg *msg)
अणु
	अगर (!msg)
		वापस;
	sg_मुक्त_table(&msg->sgt);
	kमुक्त(msg);
पूर्ण
EXPORT_SYMBOL_GPL(hsi_मुक्त_msg);

/**
 * hsi_alloc_msg - Allocate an HSI message
 * @nents: Number of memory entries
 * @flags: Kernel allocation flags
 *
 * nents can be 0. This मुख्यly makes sense क्रम पढ़ो transfer.
 * In that हाल, HSI drivers will call the complete callback when
 * there is data to be पढ़ो without consuming it.
 *
 * Return शून्य on failure or a poपूर्णांकer to an hsi_msg on success.
 */
काष्ठा hsi_msg *hsi_alloc_msg(अचिन्हित पूर्णांक nents, gfp_t flags)
अणु
	काष्ठा hsi_msg *msg;
	पूर्णांक err;

	msg = kzalloc(माप(*msg), flags);
	अगर (!msg)
		वापस शून्य;

	अगर (!nents)
		वापस msg;

	err = sg_alloc_table(&msg->sgt, nents, flags);
	अगर (unlikely(err)) अणु
		kमुक्त(msg);
		msg = शून्य;
	पूर्ण

	वापस msg;
पूर्ण
EXPORT_SYMBOL_GPL(hsi_alloc_msg);

/**
 * hsi_async - Submit an HSI transfer to the controller
 * @cl: HSI client sending the transfer
 * @msg: The HSI transfer passed to controller
 *
 * The HSI message must have the channel, ttype, complete and deकाष्ठाor
 * fields set beक्रमehand. If nents > 0 then the client has to initialize
 * also the scatterlists to poपूर्णांक to the buffers to ग_लिखो to or पढ़ो from.
 *
 * HSI controllers relay on pre-allocated buffers from their clients and they
 * करो not allocate buffers on their own.
 *
 * Once the HSI message transfer finishes, the HSI controller calls the
 * complete callback with the status and actual_len fields of the HSI message
 * updated. The complete callback can be called beक्रमe वापसing from
 * hsi_async.
 *
 * Returns -त्रुटि_सं on failure or 0 on success
 */
पूर्णांक hsi_async(काष्ठा hsi_client *cl, काष्ठा hsi_msg *msg)
अणु
	काष्ठा hsi_port *port = hsi_get_port(cl);

	अगर (!hsi_port_claimed(cl))
		वापस -EACCES;

	WARN_ON_ONCE(!msg->deकाष्ठाor || !msg->complete);
	msg->cl = cl;

	वापस port->async(msg);
पूर्ण
EXPORT_SYMBOL_GPL(hsi_async);

/**
 * hsi_claim_port - Claim the HSI client's port
 * @cl: HSI client that wants to claim its port
 * @share: Flag to indicate अगर the client wants to share the port or not.
 *
 * Returns -त्रुटि_सं on failure, 0 on success.
 */
पूर्णांक hsi_claim_port(काष्ठा hsi_client *cl, अचिन्हित पूर्णांक share)
अणु
	काष्ठा hsi_port *port = hsi_get_port(cl);
	पूर्णांक err = 0;

	mutex_lock(&port->lock);
	अगर ((port->claimed) && (!port->shared || !share)) अणु
		err = -EBUSY;
		जाओ out;
	पूर्ण
	अगर (!try_module_get(to_hsi_controller(port->device.parent)->owner)) अणु
		err = -ENODEV;
		जाओ out;
	पूर्ण
	port->claimed++;
	port->shared = !!share;
	cl->pclaimed = 1;
out:
	mutex_unlock(&port->lock);

	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(hsi_claim_port);

/**
 * hsi_release_port - Release the HSI client's port
 * @cl: HSI client which previously claimed its port
 */
व्योम hsi_release_port(काष्ठा hsi_client *cl)
अणु
	काष्ठा hsi_port *port = hsi_get_port(cl);

	mutex_lock(&port->lock);
	/* Allow HW driver to करो some cleanup */
	port->release(cl);
	अगर (cl->pclaimed)
		port->claimed--;
	BUG_ON(port->claimed < 0);
	cl->pclaimed = 0;
	अगर (!port->claimed)
		port->shared = 0;
	module_put(to_hsi_controller(port->device.parent)->owner);
	mutex_unlock(&port->lock);
पूर्ण
EXPORT_SYMBOL_GPL(hsi_release_port);

अटल पूर्णांक hsi_event_notअगरier_call(काष्ठा notअगरier_block *nb,
				अचिन्हित दीर्घ event, व्योम *data __maybe_unused)
अणु
	काष्ठा hsi_client *cl = container_of(nb, काष्ठा hsi_client, nb);

	(*cl->ehandler)(cl, event);

	वापस 0;
पूर्ण

/**
 * hsi_रेजिस्टर_port_event - Register a client to receive port events
 * @cl: HSI client that wants to receive port events
 * @handler: Event handler callback
 *
 * Clients should रेजिस्टर a callback to be able to receive
 * events from the ports. Registration should happen after
 * claiming the port.
 * The handler can be called in पूर्णांकerrupt context.
 *
 * Returns -त्रुटि_सं on error, or 0 on success.
 */
पूर्णांक hsi_रेजिस्टर_port_event(काष्ठा hsi_client *cl,
			व्योम (*handler)(काष्ठा hsi_client *, अचिन्हित दीर्घ))
अणु
	काष्ठा hsi_port *port = hsi_get_port(cl);

	अगर (!handler || cl->ehandler)
		वापस -EINVAL;
	अगर (!hsi_port_claimed(cl))
		वापस -EACCES;
	cl->ehandler = handler;
	cl->nb.notअगरier_call = hsi_event_notअगरier_call;

	वापस blocking_notअगरier_chain_रेजिस्टर(&port->n_head, &cl->nb);
पूर्ण
EXPORT_SYMBOL_GPL(hsi_रेजिस्टर_port_event);

/**
 * hsi_unरेजिस्टर_port_event - Stop receiving port events क्रम a client
 * @cl: HSI client that wants to stop receiving port events
 *
 * Clients should call this function beक्रमe releasing their associated
 * port.
 *
 * Returns -त्रुटि_सं on error, or 0 on success.
 */
पूर्णांक hsi_unरेजिस्टर_port_event(काष्ठा hsi_client *cl)
अणु
	काष्ठा hsi_port *port = hsi_get_port(cl);
	पूर्णांक err;

	WARN_ON(!hsi_port_claimed(cl));

	err = blocking_notअगरier_chain_unरेजिस्टर(&port->n_head, &cl->nb);
	अगर (!err)
		cl->ehandler = शून्य;

	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(hsi_unरेजिस्टर_port_event);

/**
 * hsi_event - Notअगरies clients about port events
 * @port: Port where the event occurred
 * @event: The event type
 *
 * Clients should not be concerned about wake line behavior. However, due
 * to a race condition in HSI HW protocol, clients need to be notअगरied
 * about wake line changes, so they can implement a workaround क्रम it.
 *
 * Events:
 * HSI_EVENT_START_RX - Incoming wake line high
 * HSI_EVENT_STOP_RX - Incoming wake line करोwn
 *
 * Returns -त्रुटि_सं on error, or 0 on success.
 */
पूर्णांक hsi_event(काष्ठा hsi_port *port, अचिन्हित दीर्घ event)
अणु
	वापस blocking_notअगरier_call_chain(&port->n_head, event, शून्य);
पूर्ण
EXPORT_SYMBOL_GPL(hsi_event);

/**
 * hsi_get_channel_id_by_name - acquire channel id by channel name
 * @cl: HSI client, which uses the channel
 * @name: name the channel is known under
 *
 * Clients can call this function to get the hsi channel ids similar to
 * requesting IRQs or GPIOs by name. This function assumes the same
 * channel configuration is used क्रम RX and TX.
 *
 * Returns -त्रुटि_सं on error or channel id on success.
 */
पूर्णांक hsi_get_channel_id_by_name(काष्ठा hsi_client *cl, अक्षर *name)
अणु
	पूर्णांक i;

	अगर (!cl->rx_cfg.channels)
		वापस -ENOENT;

	क्रम (i = 0; i < cl->rx_cfg.num_channels; i++)
		अगर (!म_भेद(cl->rx_cfg.channels[i].name, name))
			वापस cl->rx_cfg.channels[i].id;

	वापस -ENXIO;
पूर्ण
EXPORT_SYMBOL_GPL(hsi_get_channel_id_by_name);

अटल पूर्णांक __init hsi_init(व्योम)
अणु
	वापस bus_रेजिस्टर(&hsi_bus_type);
पूर्ण
postcore_initcall(hsi_init);

अटल व्योम __निकास hsi_निकास(व्योम)
अणु
	bus_unरेजिस्टर(&hsi_bus_type);
पूर्ण
module_निकास(hsi_निकास);

MODULE_AUTHOR("Carlos Chinea <carlos.chinea@nokia.com>");
MODULE_DESCRIPTION("High-speed Synchronous Serial Interface (HSI) framework");
MODULE_LICENSE("GPL v2");
