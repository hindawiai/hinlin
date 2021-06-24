<शैली गुरु>
/*
 * MIPI DSI Bus
 *
 * Copyright (C) 2012-2013, Samsung Electronics, Co., Ltd.
 * Andrzej Hajda <a.hajda@samsung.com>
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modअगरy, merge, publish,
 * distribute, sub license, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to करो so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice (including the
 * next paragraph) shall be included in all copies or substantial portions
 * of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. IN NO EVENT SHALL
 * THE COPYRIGHT HOLDERS, AUTHORS AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
 * USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#समावेश <drm/drm_mipi_dsi.h>

#समावेश <linux/device.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/slab.h>

#समावेश <drm/drm_dsc.h>
#समावेश <drm/drm_prपूर्णांक.h>
#समावेश <video/mipi_display.h>

/**
 * DOC: dsi helpers
 *
 * These functions contain some common logic and helpers to deal with MIPI DSI
 * peripherals.
 *
 * Helpers are provided क्रम a number of standard MIPI DSI command as well as a
 * subset of the MIPI DCS command set.
 */

अटल पूर्णांक mipi_dsi_device_match(काष्ठा device *dev, काष्ठा device_driver *drv)
अणु
	काष्ठा mipi_dsi_device *dsi = to_mipi_dsi_device(dev);

	/* attempt OF style match */
	अगर (of_driver_match_device(dev, drv))
		वापस 1;

	/* compare DSI device and driver names */
	अगर (!म_भेद(dsi->name, drv->name))
		वापस 1;

	वापस 0;
पूर्ण

अटल पूर्णांक mipi_dsi_uevent(काष्ठा device *dev, काष्ठा kobj_uevent_env *env)
अणु
	काष्ठा mipi_dsi_device *dsi = to_mipi_dsi_device(dev);
	पूर्णांक err;

	err = of_device_uevent_modalias(dev, env);
	अगर (err != -ENODEV)
		वापस err;

	add_uevent_var(env, "MODALIAS=%s%s", MIPI_DSI_MODULE_PREFIX,
		       dsi->name);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops mipi_dsi_device_pm_ops = अणु
	.runसमय_suspend = pm_generic_runसमय_suspend,
	.runसमय_resume = pm_generic_runसमय_resume,
	.suspend = pm_generic_suspend,
	.resume = pm_generic_resume,
	.मुक्तze = pm_generic_मुक्तze,
	.thaw = pm_generic_thaw,
	.घातeroff = pm_generic_घातeroff,
	.restore = pm_generic_restore,
पूर्ण;

अटल काष्ठा bus_type mipi_dsi_bus_type = अणु
	.name = "mipi-dsi",
	.match = mipi_dsi_device_match,
	.uevent = mipi_dsi_uevent,
	.pm = &mipi_dsi_device_pm_ops,
पूर्ण;

/**
 * of_find_mipi_dsi_device_by_node() - find the MIPI DSI device matching a
 *    device tree node
 * @np: device tree node
 *
 * Return: A poपूर्णांकer to the MIPI DSI device corresponding to @np or शून्य अगर no
 *    such device exists (or has not been रेजिस्टरed yet).
 */
काष्ठा mipi_dsi_device *of_find_mipi_dsi_device_by_node(काष्ठा device_node *np)
अणु
	काष्ठा device *dev;

	dev = bus_find_device_by_of_node(&mipi_dsi_bus_type, np);

	वापस dev ? to_mipi_dsi_device(dev) : शून्य;
पूर्ण
EXPORT_SYMBOL(of_find_mipi_dsi_device_by_node);

अटल व्योम mipi_dsi_dev_release(काष्ठा device *dev)
अणु
	काष्ठा mipi_dsi_device *dsi = to_mipi_dsi_device(dev);

	of_node_put(dev->of_node);
	kमुक्त(dsi);
पूर्ण

अटल स्थिर काष्ठा device_type mipi_dsi_device_type = अणु
	.release = mipi_dsi_dev_release,
पूर्ण;

अटल काष्ठा mipi_dsi_device *mipi_dsi_device_alloc(काष्ठा mipi_dsi_host *host)
अणु
	काष्ठा mipi_dsi_device *dsi;

	dsi = kzalloc(माप(*dsi), GFP_KERNEL);
	अगर (!dsi)
		वापस ERR_PTR(-ENOMEM);

	dsi->host = host;
	dsi->dev.bus = &mipi_dsi_bus_type;
	dsi->dev.parent = host->dev;
	dsi->dev.type = &mipi_dsi_device_type;

	device_initialize(&dsi->dev);

	वापस dsi;
पूर्ण

अटल पूर्णांक mipi_dsi_device_add(काष्ठा mipi_dsi_device *dsi)
अणु
	काष्ठा mipi_dsi_host *host = dsi->host;

	dev_set_name(&dsi->dev, "%s.%d", dev_name(host->dev),  dsi->channel);

	वापस device_add(&dsi->dev);
पूर्ण

#अगर IS_ENABLED(CONFIG_OF)
अटल काष्ठा mipi_dsi_device *
of_mipi_dsi_device_add(काष्ठा mipi_dsi_host *host, काष्ठा device_node *node)
अणु
	काष्ठा mipi_dsi_device_info info = अणु पूर्ण;
	पूर्णांक ret;
	u32 reg;

	अगर (of_modalias_node(node, info.type, माप(info.type)) < 0) अणु
		drm_err(host, "modalias failure on %pOF\n", node);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	ret = of_property_पढ़ो_u32(node, "reg", &reg);
	अगर (ret) अणु
		drm_err(host, "device node %pOF has no valid reg property: %d\n",
			node, ret);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	info.channel = reg;
	info.node = of_node_get(node);

	वापस mipi_dsi_device_रेजिस्टर_full(host, &info);
पूर्ण
#अन्यथा
अटल काष्ठा mipi_dsi_device *
of_mipi_dsi_device_add(काष्ठा mipi_dsi_host *host, काष्ठा device_node *node)
अणु
	वापस ERR_PTR(-ENODEV);
पूर्ण
#पूर्ण_अगर

/**
 * mipi_dsi_device_रेजिस्टर_full - create a MIPI DSI device
 * @host: DSI host to which this device is connected
 * @info: poपूर्णांकer to ढाँचा containing DSI device inक्रमmation
 *
 * Create a MIPI DSI device by using the device inक्रमmation provided by
 * mipi_dsi_device_info ढाँचा
 *
 * Returns:
 * A poपूर्णांकer to the newly created MIPI DSI device, or, a poपूर्णांकer encoded
 * with an error
 */
काष्ठा mipi_dsi_device *
mipi_dsi_device_रेजिस्टर_full(काष्ठा mipi_dsi_host *host,
			      स्थिर काष्ठा mipi_dsi_device_info *info)
अणु
	काष्ठा mipi_dsi_device *dsi;
	पूर्णांक ret;

	अगर (!info) अणु
		drm_err(host, "invalid mipi_dsi_device_info pointer\n");
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	अगर (info->channel > 3) अणु
		drm_err(host, "invalid virtual channel: %u\n", info->channel);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	dsi = mipi_dsi_device_alloc(host);
	अगर (IS_ERR(dsi)) अणु
		drm_err(host, "failed to allocate DSI device %ld\n",
			PTR_ERR(dsi));
		वापस dsi;
	पूर्ण

	dsi->dev.of_node = info->node;
	dsi->channel = info->channel;
	strlcpy(dsi->name, info->type, माप(dsi->name));

	ret = mipi_dsi_device_add(dsi);
	अगर (ret) अणु
		drm_err(host, "failed to add DSI device %d\n", ret);
		kमुक्त(dsi);
		वापस ERR_PTR(ret);
	पूर्ण

	वापस dsi;
पूर्ण
EXPORT_SYMBOL(mipi_dsi_device_रेजिस्टर_full);

/**
 * mipi_dsi_device_unरेजिस्टर - unरेजिस्टर MIPI DSI device
 * @dsi: DSI peripheral device
 */
व्योम mipi_dsi_device_unरेजिस्टर(काष्ठा mipi_dsi_device *dsi)
अणु
	device_unरेजिस्टर(&dsi->dev);
पूर्ण
EXPORT_SYMBOL(mipi_dsi_device_unरेजिस्टर);

अटल DEFINE_MUTEX(host_lock);
अटल LIST_HEAD(host_list);

/**
 * of_find_mipi_dsi_host_by_node() - find the MIPI DSI host matching a
 *				     device tree node
 * @node: device tree node
 *
 * Returns:
 * A poपूर्णांकer to the MIPI DSI host corresponding to @node or शून्य अगर no
 * such device exists (or has not been रेजिस्टरed yet).
 */
काष्ठा mipi_dsi_host *of_find_mipi_dsi_host_by_node(काष्ठा device_node *node)
अणु
	काष्ठा mipi_dsi_host *host;

	mutex_lock(&host_lock);

	list_क्रम_each_entry(host, &host_list, list) अणु
		अगर (host->dev->of_node == node) अणु
			mutex_unlock(&host_lock);
			वापस host;
		पूर्ण
	पूर्ण

	mutex_unlock(&host_lock);

	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(of_find_mipi_dsi_host_by_node);

पूर्णांक mipi_dsi_host_रेजिस्टर(काष्ठा mipi_dsi_host *host)
अणु
	काष्ठा device_node *node;

	क्रम_each_available_child_of_node(host->dev->of_node, node) अणु
		/* skip nodes without reg property */
		अगर (!of_find_property(node, "reg", शून्य))
			जारी;
		of_mipi_dsi_device_add(host, node);
	पूर्ण

	mutex_lock(&host_lock);
	list_add_tail(&host->list, &host_list);
	mutex_unlock(&host_lock);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(mipi_dsi_host_रेजिस्टर);

अटल पूर्णांक mipi_dsi_हटाओ_device_fn(काष्ठा device *dev, व्योम *priv)
अणु
	काष्ठा mipi_dsi_device *dsi = to_mipi_dsi_device(dev);

	mipi_dsi_device_unरेजिस्टर(dsi);

	वापस 0;
पूर्ण

व्योम mipi_dsi_host_unरेजिस्टर(काष्ठा mipi_dsi_host *host)
अणु
	device_क्रम_each_child(host->dev, शून्य, mipi_dsi_हटाओ_device_fn);

	mutex_lock(&host_lock);
	list_del_init(&host->list);
	mutex_unlock(&host_lock);
पूर्ण
EXPORT_SYMBOL(mipi_dsi_host_unरेजिस्टर);

/**
 * mipi_dsi_attach - attach a DSI device to its DSI host
 * @dsi: DSI peripheral
 */
पूर्णांक mipi_dsi_attach(काष्ठा mipi_dsi_device *dsi)
अणु
	स्थिर काष्ठा mipi_dsi_host_ops *ops = dsi->host->ops;

	अगर (!ops || !ops->attach)
		वापस -ENOSYS;

	वापस ops->attach(dsi->host, dsi);
पूर्ण
EXPORT_SYMBOL(mipi_dsi_attach);

/**
 * mipi_dsi_detach - detach a DSI device from its DSI host
 * @dsi: DSI peripheral
 */
पूर्णांक mipi_dsi_detach(काष्ठा mipi_dsi_device *dsi)
अणु
	स्थिर काष्ठा mipi_dsi_host_ops *ops = dsi->host->ops;

	अगर (!ops || !ops->detach)
		वापस -ENOSYS;

	वापस ops->detach(dsi->host, dsi);
पूर्ण
EXPORT_SYMBOL(mipi_dsi_detach);

अटल sमाप_प्रकार mipi_dsi_device_transfer(काष्ठा mipi_dsi_device *dsi,
					काष्ठा mipi_dsi_msg *msg)
अणु
	स्थिर काष्ठा mipi_dsi_host_ops *ops = dsi->host->ops;

	अगर (!ops || !ops->transfer)
		वापस -ENOSYS;

	अगर (dsi->mode_flags & MIPI_DSI_MODE_LPM)
		msg->flags |= MIPI_DSI_MSG_USE_LPM;

	वापस ops->transfer(dsi->host, msg);
पूर्ण

/**
 * mipi_dsi_packet_क्रमmat_is_लघु - check अगर a packet is of the लघु क्रमmat
 * @type: MIPI DSI data type of the packet
 *
 * Return: true अगर the packet क्रम the given data type is a लघु packet, false
 * otherwise.
 */
bool mipi_dsi_packet_क्रमmat_is_लघु(u8 type)
अणु
	चयन (type) अणु
	हाल MIPI_DSI_V_SYNC_START:
	हाल MIPI_DSI_V_SYNC_END:
	हाल MIPI_DSI_H_SYNC_START:
	हाल MIPI_DSI_H_SYNC_END:
	हाल MIPI_DSI_COMPRESSION_MODE:
	हाल MIPI_DSI_END_OF_TRANSMISSION:
	हाल MIPI_DSI_COLOR_MODE_OFF:
	हाल MIPI_DSI_COLOR_MODE_ON:
	हाल MIPI_DSI_SHUTDOWN_PERIPHERAL:
	हाल MIPI_DSI_TURN_ON_PERIPHERAL:
	हाल MIPI_DSI_GENERIC_SHORT_WRITE_0_PARAM:
	हाल MIPI_DSI_GENERIC_SHORT_WRITE_1_PARAM:
	हाल MIPI_DSI_GENERIC_SHORT_WRITE_2_PARAM:
	हाल MIPI_DSI_GENERIC_READ_REQUEST_0_PARAM:
	हाल MIPI_DSI_GENERIC_READ_REQUEST_1_PARAM:
	हाल MIPI_DSI_GENERIC_READ_REQUEST_2_PARAM:
	हाल MIPI_DSI_DCS_SHORT_WRITE:
	हाल MIPI_DSI_DCS_SHORT_WRITE_PARAM:
	हाल MIPI_DSI_DCS_READ:
	हाल MIPI_DSI_EXECUTE_QUEUE:
	हाल MIPI_DSI_SET_MAXIMUM_RETURN_PACKET_SIZE:
		वापस true;
	पूर्ण

	वापस false;
पूर्ण
EXPORT_SYMBOL(mipi_dsi_packet_क्रमmat_is_लघु);

/**
 * mipi_dsi_packet_क्रमmat_is_दीर्घ - check अगर a packet is of the दीर्घ क्रमmat
 * @type: MIPI DSI data type of the packet
 *
 * Return: true अगर the packet क्रम the given data type is a दीर्घ packet, false
 * otherwise.
 */
bool mipi_dsi_packet_क्रमmat_is_दीर्घ(u8 type)
अणु
	चयन (type) अणु
	हाल MIPI_DSI_शून्य_PACKET:
	हाल MIPI_DSI_BLANKING_PACKET:
	हाल MIPI_DSI_GENERIC_LONG_WRITE:
	हाल MIPI_DSI_DCS_LONG_WRITE:
	हाल MIPI_DSI_PICTURE_PARAMETER_SET:
	हाल MIPI_DSI_COMPRESSED_PIXEL_STREAM:
	हाल MIPI_DSI_LOOSELY_PACKED_PIXEL_STREAM_YCBCR20:
	हाल MIPI_DSI_PACKED_PIXEL_STREAM_YCBCR24:
	हाल MIPI_DSI_PACKED_PIXEL_STREAM_YCBCR16:
	हाल MIPI_DSI_PACKED_PIXEL_STREAM_30:
	हाल MIPI_DSI_PACKED_PIXEL_STREAM_36:
	हाल MIPI_DSI_PACKED_PIXEL_STREAM_YCBCR12:
	हाल MIPI_DSI_PACKED_PIXEL_STREAM_16:
	हाल MIPI_DSI_PACKED_PIXEL_STREAM_18:
	हाल MIPI_DSI_PIXEL_STREAM_3BYTE_18:
	हाल MIPI_DSI_PACKED_PIXEL_STREAM_24:
		वापस true;
	पूर्ण

	वापस false;
पूर्ण
EXPORT_SYMBOL(mipi_dsi_packet_क्रमmat_is_दीर्घ);

/**
 * mipi_dsi_create_packet - create a packet from a message according to the
 *     DSI protocol
 * @packet: poपूर्णांकer to a DSI packet काष्ठाure
 * @msg: message to translate पूर्णांकo a packet
 *
 * Return: 0 on success or a negative error code on failure.
 */
पूर्णांक mipi_dsi_create_packet(काष्ठा mipi_dsi_packet *packet,
			   स्थिर काष्ठा mipi_dsi_msg *msg)
अणु
	अगर (!packet || !msg)
		वापस -EINVAL;

	/* करो some minimum sanity checking */
	अगर (!mipi_dsi_packet_क्रमmat_is_लघु(msg->type) &&
	    !mipi_dsi_packet_क्रमmat_is_दीर्घ(msg->type))
		वापस -EINVAL;

	अगर (msg->channel > 3)
		वापस -EINVAL;

	स_रखो(packet, 0, माप(*packet));
	packet->header[0] = ((msg->channel & 0x3) << 6) | (msg->type & 0x3f);

	/* TODO: compute ECC अगर hardware support is not available */

	/*
	 * Long ग_लिखो packets contain the word count in header bytes 1 and 2.
	 * The payload follows the header and is word count bytes दीर्घ.
	 *
	 * Short ग_लिखो packets encode up to two parameters in header bytes 1
	 * and 2.
	 */
	अगर (mipi_dsi_packet_क्रमmat_is_दीर्घ(msg->type)) अणु
		packet->header[1] = (msg->tx_len >> 0) & 0xff;
		packet->header[2] = (msg->tx_len >> 8) & 0xff;

		packet->payload_length = msg->tx_len;
		packet->payload = msg->tx_buf;
	पूर्ण अन्यथा अणु
		स्थिर u8 *tx = msg->tx_buf;

		packet->header[1] = (msg->tx_len > 0) ? tx[0] : 0;
		packet->header[2] = (msg->tx_len > 1) ? tx[1] : 0;
	पूर्ण

	packet->size = माप(packet->header) + packet->payload_length;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(mipi_dsi_create_packet);

/**
 * mipi_dsi_shutकरोwn_peripheral() - sends a Shutकरोwn Peripheral command
 * @dsi: DSI peripheral device
 *
 * Return: 0 on success or a negative error code on failure.
 */
पूर्णांक mipi_dsi_shutकरोwn_peripheral(काष्ठा mipi_dsi_device *dsi)
अणु
	काष्ठा mipi_dsi_msg msg = अणु
		.channel = dsi->channel,
		.type = MIPI_DSI_SHUTDOWN_PERIPHERAL,
		.tx_buf = (u8 [2]) अणु 0, 0 पूर्ण,
		.tx_len = 2,
	पूर्ण;
	पूर्णांक ret = mipi_dsi_device_transfer(dsi, &msg);

	वापस (ret < 0) ? ret : 0;
पूर्ण
EXPORT_SYMBOL(mipi_dsi_shutकरोwn_peripheral);

/**
 * mipi_dsi_turn_on_peripheral() - sends a Turn On Peripheral command
 * @dsi: DSI peripheral device
 *
 * Return: 0 on success or a negative error code on failure.
 */
पूर्णांक mipi_dsi_turn_on_peripheral(काष्ठा mipi_dsi_device *dsi)
अणु
	काष्ठा mipi_dsi_msg msg = अणु
		.channel = dsi->channel,
		.type = MIPI_DSI_TURN_ON_PERIPHERAL,
		.tx_buf = (u8 [2]) अणु 0, 0 पूर्ण,
		.tx_len = 2,
	पूर्ण;
	पूर्णांक ret = mipi_dsi_device_transfer(dsi, &msg);

	वापस (ret < 0) ? ret : 0;
पूर्ण
EXPORT_SYMBOL(mipi_dsi_turn_on_peripheral);

/*
 * mipi_dsi_set_maximum_वापस_packet_size() - specअगरy the maximum size of the
 *    the payload in a दीर्घ packet transmitted from the peripheral back to the
 *    host processor
 * @dsi: DSI peripheral device
 * @value: the maximum size of the payload
 *
 * Return: 0 on success or a negative error code on failure.
 */
पूर्णांक mipi_dsi_set_maximum_वापस_packet_size(काष्ठा mipi_dsi_device *dsi,
					    u16 value)
अणु
	u8 tx[2] = अणु value & 0xff, value >> 8 पूर्ण;
	काष्ठा mipi_dsi_msg msg = अणु
		.channel = dsi->channel,
		.type = MIPI_DSI_SET_MAXIMUM_RETURN_PACKET_SIZE,
		.tx_len = माप(tx),
		.tx_buf = tx,
	पूर्ण;
	पूर्णांक ret = mipi_dsi_device_transfer(dsi, &msg);

	वापस (ret < 0) ? ret : 0;
पूर्ण
EXPORT_SYMBOL(mipi_dsi_set_maximum_वापस_packet_size);

/**
 * mipi_dsi_compression_mode() - enable/disable DSC on the peripheral
 * @dsi: DSI peripheral device
 * @enable: Whether to enable or disable the DSC
 *
 * Enable or disable Display Stream Compression on the peripheral using the
 * शेष Picture Parameter Set and VESA DSC 1.1 algorithm.
 *
 * Return: 0 on success or a negative error code on failure.
 */
sमाप_प्रकार mipi_dsi_compression_mode(काष्ठा mipi_dsi_device *dsi, bool enable)
अणु
	/* Note: Needs updating क्रम non-शेष PPS or algorithm */
	u8 tx[2] = अणु enable << 0, 0 पूर्ण;
	काष्ठा mipi_dsi_msg msg = अणु
		.channel = dsi->channel,
		.type = MIPI_DSI_COMPRESSION_MODE,
		.tx_len = माप(tx),
		.tx_buf = tx,
	पूर्ण;
	पूर्णांक ret = mipi_dsi_device_transfer(dsi, &msg);

	वापस (ret < 0) ? ret : 0;
पूर्ण
EXPORT_SYMBOL(mipi_dsi_compression_mode);

/**
 * mipi_dsi_picture_parameter_set() - transmit the DSC PPS to the peripheral
 * @dsi: DSI peripheral device
 * @pps: VESA DSC 1.1 Picture Parameter Set
 *
 * Transmit the VESA DSC 1.1 Picture Parameter Set to the peripheral.
 *
 * Return: 0 on success or a negative error code on failure.
 */
sमाप_प्रकार mipi_dsi_picture_parameter_set(काष्ठा mipi_dsi_device *dsi,
				       स्थिर काष्ठा drm_dsc_picture_parameter_set *pps)
अणु
	काष्ठा mipi_dsi_msg msg = अणु
		.channel = dsi->channel,
		.type = MIPI_DSI_PICTURE_PARAMETER_SET,
		.tx_len = माप(*pps),
		.tx_buf = pps,
	पूर्ण;
	पूर्णांक ret = mipi_dsi_device_transfer(dsi, &msg);

	वापस (ret < 0) ? ret : 0;
पूर्ण
EXPORT_SYMBOL(mipi_dsi_picture_parameter_set);

/**
 * mipi_dsi_generic_ग_लिखो() - transmit data using a generic ग_लिखो packet
 * @dsi: DSI peripheral device
 * @payload: buffer containing the payload
 * @size: size of payload buffer
 *
 * This function will स्वतःmatically choose the right data type depending on
 * the payload length.
 *
 * Return: The number of bytes transmitted on success or a negative error code
 * on failure.
 */
sमाप_प्रकार mipi_dsi_generic_ग_लिखो(काष्ठा mipi_dsi_device *dsi, स्थिर व्योम *payload,
			       माप_प्रकार size)
अणु
	काष्ठा mipi_dsi_msg msg = अणु
		.channel = dsi->channel,
		.tx_buf = payload,
		.tx_len = size
	पूर्ण;

	चयन (size) अणु
	हाल 0:
		msg.type = MIPI_DSI_GENERIC_SHORT_WRITE_0_PARAM;
		अवरोध;

	हाल 1:
		msg.type = MIPI_DSI_GENERIC_SHORT_WRITE_1_PARAM;
		अवरोध;

	हाल 2:
		msg.type = MIPI_DSI_GENERIC_SHORT_WRITE_2_PARAM;
		अवरोध;

	शेष:
		msg.type = MIPI_DSI_GENERIC_LONG_WRITE;
		अवरोध;
	पूर्ण

	वापस mipi_dsi_device_transfer(dsi, &msg);
पूर्ण
EXPORT_SYMBOL(mipi_dsi_generic_ग_लिखो);

/**
 * mipi_dsi_generic_पढ़ो() - receive data using a generic पढ़ो packet
 * @dsi: DSI peripheral device
 * @params: buffer containing the request parameters
 * @num_params: number of request parameters
 * @data: buffer in which to वापस the received data
 * @size: size of receive buffer
 *
 * This function will स्वतःmatically choose the right data type depending on
 * the number of parameters passed in.
 *
 * Return: The number of bytes successfully पढ़ो or a negative error code on
 * failure.
 */
sमाप_प्रकार mipi_dsi_generic_पढ़ो(काष्ठा mipi_dsi_device *dsi, स्थिर व्योम *params,
			      माप_प्रकार num_params, व्योम *data, माप_प्रकार size)
अणु
	काष्ठा mipi_dsi_msg msg = अणु
		.channel = dsi->channel,
		.tx_len = num_params,
		.tx_buf = params,
		.rx_len = size,
		.rx_buf = data
	पूर्ण;

	चयन (num_params) अणु
	हाल 0:
		msg.type = MIPI_DSI_GENERIC_READ_REQUEST_0_PARAM;
		अवरोध;

	हाल 1:
		msg.type = MIPI_DSI_GENERIC_READ_REQUEST_1_PARAM;
		अवरोध;

	हाल 2:
		msg.type = MIPI_DSI_GENERIC_READ_REQUEST_2_PARAM;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस mipi_dsi_device_transfer(dsi, &msg);
पूर्ण
EXPORT_SYMBOL(mipi_dsi_generic_पढ़ो);

/**
 * mipi_dsi_dcs_ग_लिखो_buffer() - transmit a DCS command with payload
 * @dsi: DSI peripheral device
 * @data: buffer containing data to be transmitted
 * @len: size of transmission buffer
 *
 * This function will स्वतःmatically choose the right data type depending on
 * the command payload length.
 *
 * Return: The number of bytes successfully transmitted or a negative error
 * code on failure.
 */
sमाप_प्रकार mipi_dsi_dcs_ग_लिखो_buffer(काष्ठा mipi_dsi_device *dsi,
				  स्थिर व्योम *data, माप_प्रकार len)
अणु
	काष्ठा mipi_dsi_msg msg = अणु
		.channel = dsi->channel,
		.tx_buf = data,
		.tx_len = len
	पूर्ण;

	चयन (len) अणु
	हाल 0:
		वापस -EINVAL;

	हाल 1:
		msg.type = MIPI_DSI_DCS_SHORT_WRITE;
		अवरोध;

	हाल 2:
		msg.type = MIPI_DSI_DCS_SHORT_WRITE_PARAM;
		अवरोध;

	शेष:
		msg.type = MIPI_DSI_DCS_LONG_WRITE;
		अवरोध;
	पूर्ण

	वापस mipi_dsi_device_transfer(dsi, &msg);
पूर्ण
EXPORT_SYMBOL(mipi_dsi_dcs_ग_लिखो_buffer);

/**
 * mipi_dsi_dcs_ग_लिखो() - send DCS ग_लिखो command
 * @dsi: DSI peripheral device
 * @cmd: DCS command
 * @data: buffer containing the command payload
 * @len: command payload length
 *
 * This function will स्वतःmatically choose the right data type depending on
 * the command payload length.
 *
 * Return: The number of bytes successfully transmitted or a negative error
 * code on failure.
 */
sमाप_प्रकार mipi_dsi_dcs_ग_लिखो(काष्ठा mipi_dsi_device *dsi, u8 cmd,
			   स्थिर व्योम *data, माप_प्रकार len)
अणु
	sमाप_प्रकार err;
	माप_प्रकार size;
	u8 stack_tx[8];
	u8 *tx;

	size = 1 + len;
	अगर (len > ARRAY_SIZE(stack_tx) - 1) अणु
		tx = kदो_स्मृति(size, GFP_KERNEL);
		अगर (!tx)
			वापस -ENOMEM;
	पूर्ण अन्यथा अणु
		tx = stack_tx;
	पूर्ण

	/* concatenate the DCS command byte and the payload */
	tx[0] = cmd;
	अगर (data)
		स_नकल(&tx[1], data, len);

	err = mipi_dsi_dcs_ग_लिखो_buffer(dsi, tx, size);

	अगर (tx != stack_tx)
		kमुक्त(tx);

	वापस err;
पूर्ण
EXPORT_SYMBOL(mipi_dsi_dcs_ग_लिखो);

/**
 * mipi_dsi_dcs_पढ़ो() - send DCS पढ़ो request command
 * @dsi: DSI peripheral device
 * @cmd: DCS command
 * @data: buffer in which to receive data
 * @len: size of receive buffer
 *
 * Return: The number of bytes पढ़ो or a negative error code on failure.
 */
sमाप_प्रकार mipi_dsi_dcs_पढ़ो(काष्ठा mipi_dsi_device *dsi, u8 cmd, व्योम *data,
			  माप_प्रकार len)
अणु
	काष्ठा mipi_dsi_msg msg = अणु
		.channel = dsi->channel,
		.type = MIPI_DSI_DCS_READ,
		.tx_buf = &cmd,
		.tx_len = 1,
		.rx_buf = data,
		.rx_len = len
	पूर्ण;

	वापस mipi_dsi_device_transfer(dsi, &msg);
पूर्ण
EXPORT_SYMBOL(mipi_dsi_dcs_पढ़ो);

/**
 * mipi_dsi_dcs_nop() - send DCS nop packet
 * @dsi: DSI peripheral device
 *
 * Return: 0 on success or a negative error code on failure.
 */
पूर्णांक mipi_dsi_dcs_nop(काष्ठा mipi_dsi_device *dsi)
अणु
	sमाप_प्रकार err;

	err = mipi_dsi_dcs_ग_लिखो(dsi, MIPI_DCS_NOP, शून्य, 0);
	अगर (err < 0)
		वापस err;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(mipi_dsi_dcs_nop);

/**
 * mipi_dsi_dcs_soft_reset() - perक्रमm a software reset of the display module
 * @dsi: DSI peripheral device
 *
 * Return: 0 on success or a negative error code on failure.
 */
पूर्णांक mipi_dsi_dcs_soft_reset(काष्ठा mipi_dsi_device *dsi)
अणु
	sमाप_प्रकार err;

	err = mipi_dsi_dcs_ग_लिखो(dsi, MIPI_DCS_SOFT_RESET, शून्य, 0);
	अगर (err < 0)
		वापस err;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(mipi_dsi_dcs_soft_reset);

/**
 * mipi_dsi_dcs_get_घातer_mode() - query the display module's current घातer
 *    mode
 * @dsi: DSI peripheral device
 * @mode: वापस location क्रम the current घातer mode
 *
 * Return: 0 on success or a negative error code on failure.
 */
पूर्णांक mipi_dsi_dcs_get_घातer_mode(काष्ठा mipi_dsi_device *dsi, u8 *mode)
अणु
	sमाप_प्रकार err;

	err = mipi_dsi_dcs_पढ़ो(dsi, MIPI_DCS_GET_POWER_MODE, mode,
				माप(*mode));
	अगर (err <= 0) अणु
		अगर (err == 0)
			err = -ENODATA;

		वापस err;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(mipi_dsi_dcs_get_घातer_mode);

/**
 * mipi_dsi_dcs_get_pixel_क्रमmat() - माला_लो the pixel क्रमmat क्रम the RGB image
 *    data used by the पूर्णांकerface
 * @dsi: DSI peripheral device
 * @क्रमmat: वापस location क्रम the pixel क्रमmat
 *
 * Return: 0 on success or a negative error code on failure.
 */
पूर्णांक mipi_dsi_dcs_get_pixel_क्रमmat(काष्ठा mipi_dsi_device *dsi, u8 *क्रमmat)
अणु
	sमाप_प्रकार err;

	err = mipi_dsi_dcs_पढ़ो(dsi, MIPI_DCS_GET_PIXEL_FORMAT, क्रमmat,
				माप(*क्रमmat));
	अगर (err <= 0) अणु
		अगर (err == 0)
			err = -ENODATA;

		वापस err;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(mipi_dsi_dcs_get_pixel_क्रमmat);

/**
 * mipi_dsi_dcs_enter_sleep_mode() - disable all unnecessary blocks inside the
 *    display module except पूर्णांकerface communication
 * @dsi: DSI peripheral device
 *
 * Return: 0 on success or a negative error code on failure.
 */
पूर्णांक mipi_dsi_dcs_enter_sleep_mode(काष्ठा mipi_dsi_device *dsi)
अणु
	sमाप_प्रकार err;

	err = mipi_dsi_dcs_ग_लिखो(dsi, MIPI_DCS_ENTER_SLEEP_MODE, शून्य, 0);
	अगर (err < 0)
		वापस err;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(mipi_dsi_dcs_enter_sleep_mode);

/**
 * mipi_dsi_dcs_निकास_sleep_mode() - enable all blocks inside the display
 *    module
 * @dsi: DSI peripheral device
 *
 * Return: 0 on success or a negative error code on failure.
 */
पूर्णांक mipi_dsi_dcs_निकास_sleep_mode(काष्ठा mipi_dsi_device *dsi)
अणु
	sमाप_प्रकार err;

	err = mipi_dsi_dcs_ग_लिखो(dsi, MIPI_DCS_EXIT_SLEEP_MODE, शून्य, 0);
	अगर (err < 0)
		वापस err;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(mipi_dsi_dcs_निकास_sleep_mode);

/**
 * mipi_dsi_dcs_set_display_off() - stop displaying the image data on the
 *    display device
 * @dsi: DSI peripheral device
 *
 * Return: 0 on success or a negative error code on failure.
 */
पूर्णांक mipi_dsi_dcs_set_display_off(काष्ठा mipi_dsi_device *dsi)
अणु
	sमाप_प्रकार err;

	err = mipi_dsi_dcs_ग_लिखो(dsi, MIPI_DCS_SET_DISPLAY_OFF, शून्य, 0);
	अगर (err < 0)
		वापस err;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(mipi_dsi_dcs_set_display_off);

/**
 * mipi_dsi_dcs_set_display_on() - start displaying the image data on the
 *    display device
 * @dsi: DSI peripheral device
 *
 * Return: 0 on success or a negative error code on failure
 */
पूर्णांक mipi_dsi_dcs_set_display_on(काष्ठा mipi_dsi_device *dsi)
अणु
	sमाप_प्रकार err;

	err = mipi_dsi_dcs_ग_लिखो(dsi, MIPI_DCS_SET_DISPLAY_ON, शून्य, 0);
	अगर (err < 0)
		वापस err;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(mipi_dsi_dcs_set_display_on);

/**
 * mipi_dsi_dcs_set_column_address() - define the column extent of the frame
 *    memory accessed by the host processor
 * @dsi: DSI peripheral device
 * @start: first column of frame memory
 * @end: last column of frame memory
 *
 * Return: 0 on success or a negative error code on failure.
 */
पूर्णांक mipi_dsi_dcs_set_column_address(काष्ठा mipi_dsi_device *dsi, u16 start,
				    u16 end)
अणु
	u8 payload[4] = अणु start >> 8, start & 0xff, end >> 8, end & 0xff पूर्ण;
	sमाप_प्रकार err;

	err = mipi_dsi_dcs_ग_लिखो(dsi, MIPI_DCS_SET_COLUMN_ADDRESS, payload,
				 माप(payload));
	अगर (err < 0)
		वापस err;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(mipi_dsi_dcs_set_column_address);

/**
 * mipi_dsi_dcs_set_page_address() - define the page extent of the frame
 *    memory accessed by the host processor
 * @dsi: DSI peripheral device
 * @start: first page of frame memory
 * @end: last page of frame memory
 *
 * Return: 0 on success or a negative error code on failure.
 */
पूर्णांक mipi_dsi_dcs_set_page_address(काष्ठा mipi_dsi_device *dsi, u16 start,
				  u16 end)
अणु
	u8 payload[4] = अणु start >> 8, start & 0xff, end >> 8, end & 0xff पूर्ण;
	sमाप_प्रकार err;

	err = mipi_dsi_dcs_ग_लिखो(dsi, MIPI_DCS_SET_PAGE_ADDRESS, payload,
				 माप(payload));
	अगर (err < 0)
		वापस err;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(mipi_dsi_dcs_set_page_address);

/**
 * mipi_dsi_dcs_set_tear_off() - turn off the display module's Tearing Effect
 *    output संकेत on the TE संकेत line
 * @dsi: DSI peripheral device
 *
 * Return: 0 on success or a negative error code on failure
 */
पूर्णांक mipi_dsi_dcs_set_tear_off(काष्ठा mipi_dsi_device *dsi)
अणु
	sमाप_प्रकार err;

	err = mipi_dsi_dcs_ग_लिखो(dsi, MIPI_DCS_SET_TEAR_OFF, शून्य, 0);
	अगर (err < 0)
		वापस err;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(mipi_dsi_dcs_set_tear_off);

/**
 * mipi_dsi_dcs_set_tear_on() - turn on the display module's Tearing Effect
 *    output संकेत on the TE संकेत line.
 * @dsi: DSI peripheral device
 * @mode: the Tearing Effect Output Line mode
 *
 * Return: 0 on success or a negative error code on failure
 */
पूर्णांक mipi_dsi_dcs_set_tear_on(काष्ठा mipi_dsi_device *dsi,
			     क्रमागत mipi_dsi_dcs_tear_mode mode)
अणु
	u8 value = mode;
	sमाप_प्रकार err;

	err = mipi_dsi_dcs_ग_लिखो(dsi, MIPI_DCS_SET_TEAR_ON, &value,
				 माप(value));
	अगर (err < 0)
		वापस err;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(mipi_dsi_dcs_set_tear_on);

/**
 * mipi_dsi_dcs_set_pixel_क्रमmat() - sets the pixel क्रमmat क्रम the RGB image
 *    data used by the पूर्णांकerface
 * @dsi: DSI peripheral device
 * @क्रमmat: pixel क्रमmat
 *
 * Return: 0 on success or a negative error code on failure.
 */
पूर्णांक mipi_dsi_dcs_set_pixel_क्रमmat(काष्ठा mipi_dsi_device *dsi, u8 क्रमmat)
अणु
	sमाप_प्रकार err;

	err = mipi_dsi_dcs_ग_लिखो(dsi, MIPI_DCS_SET_PIXEL_FORMAT, &क्रमmat,
				 माप(क्रमmat));
	अगर (err < 0)
		वापस err;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(mipi_dsi_dcs_set_pixel_क्रमmat);

/**
 * mipi_dsi_dcs_set_tear_scanline() - set the scanline to use as trigger क्रम
 *    the Tearing Effect output संकेत of the display module
 * @dsi: DSI peripheral device
 * @scanline: scanline to use as trigger
 *
 * Return: 0 on success or a negative error code on failure
 */
पूर्णांक mipi_dsi_dcs_set_tear_scanline(काष्ठा mipi_dsi_device *dsi, u16 scanline)
अणु
	u8 payload[2] = अणु scanline >> 8, scanline & 0xff पूर्ण;
	sमाप_प्रकार err;

	err = mipi_dsi_dcs_ग_लिखो(dsi, MIPI_DCS_SET_TEAR_SCANLINE, payload,
				 माप(payload));
	अगर (err < 0)
		वापस err;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(mipi_dsi_dcs_set_tear_scanline);

/**
 * mipi_dsi_dcs_set_display_brightness() - sets the brightness value of the
 *    display
 * @dsi: DSI peripheral device
 * @brightness: brightness value
 *
 * Return: 0 on success or a negative error code on failure.
 */
पूर्णांक mipi_dsi_dcs_set_display_brightness(काष्ठा mipi_dsi_device *dsi,
					u16 brightness)
अणु
	u8 payload[2] = अणु brightness & 0xff, brightness >> 8 पूर्ण;
	sमाप_प्रकार err;

	err = mipi_dsi_dcs_ग_लिखो(dsi, MIPI_DCS_SET_DISPLAY_BRIGHTNESS,
				 payload, माप(payload));
	अगर (err < 0)
		वापस err;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(mipi_dsi_dcs_set_display_brightness);

/**
 * mipi_dsi_dcs_get_display_brightness() - माला_लो the current brightness value
 *    of the display
 * @dsi: DSI peripheral device
 * @brightness: brightness value
 *
 * Return: 0 on success or a negative error code on failure.
 */
पूर्णांक mipi_dsi_dcs_get_display_brightness(काष्ठा mipi_dsi_device *dsi,
					u16 *brightness)
अणु
	sमाप_प्रकार err;

	err = mipi_dsi_dcs_पढ़ो(dsi, MIPI_DCS_GET_DISPLAY_BRIGHTNESS,
				brightness, माप(*brightness));
	अगर (err <= 0) अणु
		अगर (err == 0)
			err = -ENODATA;

		वापस err;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(mipi_dsi_dcs_get_display_brightness);

अटल पूर्णांक mipi_dsi_drv_probe(काष्ठा device *dev)
अणु
	काष्ठा mipi_dsi_driver *drv = to_mipi_dsi_driver(dev->driver);
	काष्ठा mipi_dsi_device *dsi = to_mipi_dsi_device(dev);

	वापस drv->probe(dsi);
पूर्ण

अटल पूर्णांक mipi_dsi_drv_हटाओ(काष्ठा device *dev)
अणु
	काष्ठा mipi_dsi_driver *drv = to_mipi_dsi_driver(dev->driver);
	काष्ठा mipi_dsi_device *dsi = to_mipi_dsi_device(dev);

	वापस drv->हटाओ(dsi);
पूर्ण

अटल व्योम mipi_dsi_drv_shutकरोwn(काष्ठा device *dev)
अणु
	काष्ठा mipi_dsi_driver *drv = to_mipi_dsi_driver(dev->driver);
	काष्ठा mipi_dsi_device *dsi = to_mipi_dsi_device(dev);

	drv->shutकरोwn(dsi);
पूर्ण

/**
 * mipi_dsi_driver_रेजिस्टर_full() - रेजिस्टर a driver क्रम DSI devices
 * @drv: DSI driver काष्ठाure
 * @owner: owner module
 *
 * Return: 0 on success or a negative error code on failure.
 */
पूर्णांक mipi_dsi_driver_रेजिस्टर_full(काष्ठा mipi_dsi_driver *drv,
				  काष्ठा module *owner)
अणु
	drv->driver.bus = &mipi_dsi_bus_type;
	drv->driver.owner = owner;

	अगर (drv->probe)
		drv->driver.probe = mipi_dsi_drv_probe;
	अगर (drv->हटाओ)
		drv->driver.हटाओ = mipi_dsi_drv_हटाओ;
	अगर (drv->shutकरोwn)
		drv->driver.shutकरोwn = mipi_dsi_drv_shutकरोwn;

	वापस driver_रेजिस्टर(&drv->driver);
पूर्ण
EXPORT_SYMBOL(mipi_dsi_driver_रेजिस्टर_full);

/**
 * mipi_dsi_driver_unरेजिस्टर() - unरेजिस्टर a driver क्रम DSI devices
 * @drv: DSI driver काष्ठाure
 *
 * Return: 0 on success or a negative error code on failure.
 */
व्योम mipi_dsi_driver_unरेजिस्टर(काष्ठा mipi_dsi_driver *drv)
अणु
	driver_unरेजिस्टर(&drv->driver);
पूर्ण
EXPORT_SYMBOL(mipi_dsi_driver_unरेजिस्टर);

अटल पूर्णांक __init mipi_dsi_bus_init(व्योम)
अणु
	वापस bus_रेजिस्टर(&mipi_dsi_bus_type);
पूर्ण
postcore_initcall(mipi_dsi_bus_init);

MODULE_AUTHOR("Andrzej Hajda <a.hajda@samsung.com>");
MODULE_DESCRIPTION("MIPI DSI Bus");
MODULE_LICENSE("GPL and additional rights");
