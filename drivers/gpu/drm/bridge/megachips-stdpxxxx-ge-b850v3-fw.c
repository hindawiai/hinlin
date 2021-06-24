<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Driver क्रम MegaChips STDP4028 with GE B850v3 firmware (LVDS-DP)
 * Driver क्रम MegaChips STDP2690 with GE B850v3 firmware (DP-DP++)

 * Copyright (c) 2017, Collabora Ltd.
 * Copyright (c) 2017, General Electric Company


 * This driver creates a drm_bridge and a drm_connector क्रम the LVDS to DP++
 * display bridge of the GE B850v3. There are two physical bridges on the video
 * संकेत pipeline: a STDP4028(LVDS to DP) and a STDP2690(DP to DP++). The
 * physical bridges are स्वतःmatically configured by the input video संकेत, and
 * the driver has no access to the video processing pipeline. The driver is
 * only needed to पढ़ो EDID from the STDP2690 and to handle HPD events from the
 * STDP4028. The driver communicates with both bridges over i2c. The video
 * संकेत pipeline is as follows:
 *
 *   Host -> LVDS|--(STDP4028)--|DP -> DP|--(STDP2690)--|DP++ -> Video output
 */

#समावेश <linux/i2c.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>

#समावेश <drm/drm_atomic.h>
#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_bridge.h>
#समावेश <drm/drm_edid.h>
#समावेश <drm/drm_prपूर्णांक.h>
#समावेश <drm/drm_probe_helper.h>

#घोषणा EDID_EXT_BLOCK_CNT 0x7E

#घोषणा STDP4028_IRQ_OUT_CONF_REG 0x02
#घोषणा STDP4028_DPTX_IRQ_EN_REG 0x3C
#घोषणा STDP4028_DPTX_IRQ_STS_REG 0x3D
#घोषणा STDP4028_DPTX_STS_REG 0x3E

#घोषणा STDP4028_DPTX_DP_IRQ_EN 0x1000

#घोषणा STDP4028_DPTX_HOTPLUG_IRQ_EN 0x0400
#घोषणा STDP4028_DPTX_LINK_CH_IRQ_EN 0x2000
#घोषणा STDP4028_DPTX_IRQ_CONFIG \
		(STDP4028_DPTX_LINK_CH_IRQ_EN | STDP4028_DPTX_HOTPLUG_IRQ_EN)

#घोषणा STDP4028_DPTX_HOTPLUG_STS 0x0200
#घोषणा STDP4028_DPTX_LINK_STS 0x1000
#घोषणा STDP4028_CON_STATE_CONNECTED \
		(STDP4028_DPTX_HOTPLUG_STS | STDP4028_DPTX_LINK_STS)

#घोषणा STDP4028_DPTX_HOTPLUG_CH_STS 0x0400
#घोषणा STDP4028_DPTX_LINK_CH_STS 0x2000
#घोषणा STDP4028_DPTX_IRQ_CLEAR \
		(STDP4028_DPTX_LINK_CH_STS | STDP4028_DPTX_HOTPLUG_CH_STS)

अटल DEFINE_MUTEX(ge_b850v3_lvds_dev_mutex);

काष्ठा ge_b850v3_lvds अणु
	काष्ठा drm_connector connector;
	काष्ठा drm_bridge bridge;
	काष्ठा i2c_client *stdp4028_i2c;
	काष्ठा i2c_client *stdp2690_i2c;
पूर्ण;

अटल काष्ठा ge_b850v3_lvds *ge_b850v3_lvds_ptr;

अटल u8 *stdp2690_get_edid(काष्ठा i2c_client *client)
अणु
	काष्ठा i2c_adapter *adapter = client->adapter;
	अचिन्हित अक्षर start = 0x00;
	अचिन्हित पूर्णांक total_size;
	u8 *block = kदो_स्मृति(EDID_LENGTH, GFP_KERNEL);

	काष्ठा i2c_msg msgs[] = अणु
		अणु
			.addr	= client->addr,
			.flags	= 0,
			.len	= 1,
			.buf	= &start,
		पूर्ण, अणु
			.addr	= client->addr,
			.flags	= I2C_M_RD,
			.len	= EDID_LENGTH,
			.buf	= block,
		पूर्ण
	पूर्ण;

	अगर (!block)
		वापस शून्य;

	अगर (i2c_transfer(adapter, msgs, 2) != 2) अणु
		DRM_ERROR("Unable to read EDID.\n");
		जाओ err;
	पूर्ण

	अगर (!drm_edid_block_valid(block, 0, false, शून्य)) अणु
		DRM_ERROR("Invalid EDID data\n");
		जाओ err;
	पूर्ण

	total_size = (block[EDID_EXT_BLOCK_CNT] + 1) * EDID_LENGTH;
	अगर (total_size > EDID_LENGTH) अणु
		kमुक्त(block);
		block = kदो_स्मृति(total_size, GFP_KERNEL);
		अगर (!block)
			वापस शून्य;

		/* Yes, पढ़ो the entire buffer, and करो not skip the first
		 * EDID_LENGTH bytes.
		 */
		start = 0x00;
		msgs[1].len = total_size;
		msgs[1].buf = block;

		अगर (i2c_transfer(adapter, msgs, 2) != 2) अणु
			DRM_ERROR("Unable to read EDID extension blocks.\n");
			जाओ err;
		पूर्ण
		अगर (!drm_edid_block_valid(block, 1, false, शून्य)) अणु
			DRM_ERROR("Invalid EDID data\n");
			जाओ err;
		पूर्ण
	पूर्ण

	वापस block;

err:
	kमुक्त(block);
	वापस शून्य;
पूर्ण

अटल काष्ठा edid *ge_b850v3_lvds_get_edid(काष्ठा drm_bridge *bridge,
					    काष्ठा drm_connector *connector)
अणु
	काष्ठा i2c_client *client;

	client = ge_b850v3_lvds_ptr->stdp2690_i2c;

	वापस (काष्ठा edid *)stdp2690_get_edid(client);
पूर्ण

अटल पूर्णांक ge_b850v3_lvds_get_modes(काष्ठा drm_connector *connector)
अणु
	काष्ठा edid *edid;
	पूर्णांक num_modes;

	edid = ge_b850v3_lvds_get_edid(&ge_b850v3_lvds_ptr->bridge, connector);

	drm_connector_update_edid_property(connector, edid);
	num_modes = drm_add_edid_modes(connector, edid);
	kमुक्त(edid);

	वापस num_modes;
पूर्ण

अटल क्रमागत drm_mode_status ge_b850v3_lvds_mode_valid(
		काष्ठा drm_connector *connector, काष्ठा drm_display_mode *mode)
अणु
	वापस MODE_OK;
पूर्ण

अटल स्थिर काष्ठा
drm_connector_helper_funcs ge_b850v3_lvds_connector_helper_funcs = अणु
	.get_modes = ge_b850v3_lvds_get_modes,
	.mode_valid = ge_b850v3_lvds_mode_valid,
पूर्ण;

अटल क्रमागत drm_connector_status ge_b850v3_lvds_bridge_detect(काष्ठा drm_bridge *bridge)
अणु
	काष्ठा i2c_client *stdp4028_i2c =
			ge_b850v3_lvds_ptr->stdp4028_i2c;
	s32 link_state;

	link_state = i2c_smbus_पढ़ो_word_data(stdp4028_i2c,
					      STDP4028_DPTX_STS_REG);

	अगर (link_state == STDP4028_CON_STATE_CONNECTED)
		वापस connector_status_connected;

	अगर (link_state == 0)
		वापस connector_status_disconnected;

	वापस connector_status_unknown;
पूर्ण

अटल क्रमागत drm_connector_status ge_b850v3_lvds_detect(काष्ठा drm_connector *connector,
						       bool क्रमce)
अणु
	वापस ge_b850v3_lvds_bridge_detect(&ge_b850v3_lvds_ptr->bridge);
पूर्ण

अटल स्थिर काष्ठा drm_connector_funcs ge_b850v3_lvds_connector_funcs = अणु
	.fill_modes = drm_helper_probe_single_connector_modes,
	.detect = ge_b850v3_lvds_detect,
	.destroy = drm_connector_cleanup,
	.reset = drm_atomic_helper_connector_reset,
	.atomic_duplicate_state = drm_atomic_helper_connector_duplicate_state,
	.atomic_destroy_state = drm_atomic_helper_connector_destroy_state,
पूर्ण;

अटल पूर्णांक ge_b850v3_lvds_create_connector(काष्ठा drm_bridge *bridge)
अणु
	काष्ठा drm_connector *connector = &ge_b850v3_lvds_ptr->connector;
	पूर्णांक ret;

	अगर (!bridge->encoder) अणु
		DRM_ERROR("Parent encoder object not found");
		वापस -ENODEV;
	पूर्ण

	connector->polled = DRM_CONNECTOR_POLL_HPD;

	drm_connector_helper_add(connector,
				 &ge_b850v3_lvds_connector_helper_funcs);

	ret = drm_connector_init(bridge->dev, connector,
				 &ge_b850v3_lvds_connector_funcs,
				 DRM_MODE_CONNECTOR_DisplayPort);
	अगर (ret) अणु
		DRM_ERROR("Failed to initialize connector with drm\n");
		वापस ret;
	पूर्ण

	वापस drm_connector_attach_encoder(connector, bridge->encoder);
पूर्ण

अटल irqवापस_t ge_b850v3_lvds_irq_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा i2c_client *stdp4028_i2c
			= ge_b850v3_lvds_ptr->stdp4028_i2c;

	i2c_smbus_ग_लिखो_word_data(stdp4028_i2c,
				  STDP4028_DPTX_IRQ_STS_REG,
				  STDP4028_DPTX_IRQ_CLEAR);

	अगर (ge_b850v3_lvds_ptr->bridge.dev)
		drm_kms_helper_hotplug_event(ge_b850v3_lvds_ptr->bridge.dev);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक ge_b850v3_lvds_attach(काष्ठा drm_bridge *bridge,
				 क्रमागत drm_bridge_attach_flags flags)
अणु
	काष्ठा i2c_client *stdp4028_i2c
			= ge_b850v3_lvds_ptr->stdp4028_i2c;

	/* Configures the bridge to re-enable पूर्णांकerrupts after each ack. */
	i2c_smbus_ग_लिखो_word_data(stdp4028_i2c,
				  STDP4028_IRQ_OUT_CONF_REG,
				  STDP4028_DPTX_DP_IRQ_EN);

	/* Enable पूर्णांकerrupts */
	i2c_smbus_ग_लिखो_word_data(stdp4028_i2c,
				  STDP4028_DPTX_IRQ_EN_REG,
				  STDP4028_DPTX_IRQ_CONFIG);

	अगर (flags & DRM_BRIDGE_ATTACH_NO_CONNECTOR)
		वापस 0;

	वापस ge_b850v3_lvds_create_connector(bridge);
पूर्ण

अटल स्थिर काष्ठा drm_bridge_funcs ge_b850v3_lvds_funcs = अणु
	.attach = ge_b850v3_lvds_attach,
	.detect = ge_b850v3_lvds_bridge_detect,
	.get_edid = ge_b850v3_lvds_get_edid,
पूर्ण;

अटल पूर्णांक ge_b850v3_lvds_init(काष्ठा device *dev)
अणु
	mutex_lock(&ge_b850v3_lvds_dev_mutex);

	अगर (ge_b850v3_lvds_ptr)
		जाओ success;

	ge_b850v3_lvds_ptr = devm_kzalloc(dev,
					  माप(*ge_b850v3_lvds_ptr),
					  GFP_KERNEL);

	अगर (!ge_b850v3_lvds_ptr) अणु
		mutex_unlock(&ge_b850v3_lvds_dev_mutex);
		वापस -ENOMEM;
	पूर्ण

success:
	mutex_unlock(&ge_b850v3_lvds_dev_mutex);
	वापस 0;
पूर्ण

अटल व्योम ge_b850v3_lvds_हटाओ(व्योम)
अणु
	mutex_lock(&ge_b850v3_lvds_dev_mutex);
	/*
	 * This check is to aव्योम both the drivers
	 * removing the bridge in their हटाओ() function
	 */
	अगर (!ge_b850v3_lvds_ptr)
		जाओ out;

	drm_bridge_हटाओ(&ge_b850v3_lvds_ptr->bridge);

	ge_b850v3_lvds_ptr = शून्य;
out:
	mutex_unlock(&ge_b850v3_lvds_dev_mutex);
पूर्ण

अटल पूर्णांक stdp4028_ge_b850v3_fw_probe(काष्ठा i2c_client *stdp4028_i2c,
				       स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा device *dev = &stdp4028_i2c->dev;
	पूर्णांक ret;

	ret = ge_b850v3_lvds_init(dev);

	अगर (ret)
		वापस ret;

	ge_b850v3_lvds_ptr->stdp4028_i2c = stdp4028_i2c;
	i2c_set_clientdata(stdp4028_i2c, ge_b850v3_lvds_ptr);

	/* drm bridge initialization */
	ge_b850v3_lvds_ptr->bridge.funcs = &ge_b850v3_lvds_funcs;
	ge_b850v3_lvds_ptr->bridge.ops = DRM_BRIDGE_OP_DETECT |
					 DRM_BRIDGE_OP_EDID;
	ge_b850v3_lvds_ptr->bridge.type = DRM_MODE_CONNECTOR_DisplayPort;
	ge_b850v3_lvds_ptr->bridge.of_node = dev->of_node;
	drm_bridge_add(&ge_b850v3_lvds_ptr->bridge);

	/* Clear pending पूर्णांकerrupts since घातer up. */
	i2c_smbus_ग_लिखो_word_data(stdp4028_i2c,
				  STDP4028_DPTX_IRQ_STS_REG,
				  STDP4028_DPTX_IRQ_CLEAR);

	अगर (!stdp4028_i2c->irq)
		वापस 0;

	वापस devm_request_thपढ़ोed_irq(&stdp4028_i2c->dev,
			stdp4028_i2c->irq, शून्य,
			ge_b850v3_lvds_irq_handler,
			IRQF_TRIGGER_HIGH | IRQF_ONESHOT,
			"ge-b850v3-lvds-dp", ge_b850v3_lvds_ptr);
पूर्ण

अटल पूर्णांक stdp4028_ge_b850v3_fw_हटाओ(काष्ठा i2c_client *stdp4028_i2c)
अणु
	ge_b850v3_lvds_हटाओ();

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id stdp4028_ge_b850v3_fw_i2c_table[] = अणु
	अणु"stdp4028_ge_fw", 0पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(i2c, stdp4028_ge_b850v3_fw_i2c_table);

अटल स्थिर काष्ठा of_device_id stdp4028_ge_b850v3_fw_match[] = अणु
	अणु .compatible = "megachips,stdp4028-ge-b850v3-fw" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, stdp4028_ge_b850v3_fw_match);

अटल काष्ठा i2c_driver stdp4028_ge_b850v3_fw_driver = अणु
	.id_table	= stdp4028_ge_b850v3_fw_i2c_table,
	.probe		= stdp4028_ge_b850v3_fw_probe,
	.हटाओ		= stdp4028_ge_b850v3_fw_हटाओ,
	.driver		= अणु
		.name		= "stdp4028-ge-b850v3-fw",
		.of_match_table = stdp4028_ge_b850v3_fw_match,
	पूर्ण,
पूर्ण;

अटल पूर्णांक stdp2690_ge_b850v3_fw_probe(काष्ठा i2c_client *stdp2690_i2c,
				       स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा device *dev = &stdp2690_i2c->dev;
	पूर्णांक ret;

	ret = ge_b850v3_lvds_init(dev);

	अगर (ret)
		वापस ret;

	ge_b850v3_lvds_ptr->stdp2690_i2c = stdp2690_i2c;
	i2c_set_clientdata(stdp2690_i2c, ge_b850v3_lvds_ptr);

	वापस 0;
पूर्ण

अटल पूर्णांक stdp2690_ge_b850v3_fw_हटाओ(काष्ठा i2c_client *stdp2690_i2c)
अणु
	ge_b850v3_lvds_हटाओ();

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id stdp2690_ge_b850v3_fw_i2c_table[] = अणु
	अणु"stdp2690_ge_fw", 0पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(i2c, stdp2690_ge_b850v3_fw_i2c_table);

अटल स्थिर काष्ठा of_device_id stdp2690_ge_b850v3_fw_match[] = अणु
	अणु .compatible = "megachips,stdp2690-ge-b850v3-fw" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, stdp2690_ge_b850v3_fw_match);

अटल काष्ठा i2c_driver stdp2690_ge_b850v3_fw_driver = अणु
	.id_table	= stdp2690_ge_b850v3_fw_i2c_table,
	.probe		= stdp2690_ge_b850v3_fw_probe,
	.हटाओ		= stdp2690_ge_b850v3_fw_हटाओ,
	.driver		= अणु
		.name		= "stdp2690-ge-b850v3-fw",
		.of_match_table = stdp2690_ge_b850v3_fw_match,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init stdpxxxx_ge_b850v3_init(व्योम)
अणु
	पूर्णांक ret;

	ret = i2c_add_driver(&stdp4028_ge_b850v3_fw_driver);
	अगर (ret)
		वापस ret;

	वापस i2c_add_driver(&stdp2690_ge_b850v3_fw_driver);
पूर्ण
module_init(stdpxxxx_ge_b850v3_init);

अटल व्योम __निकास stdpxxxx_ge_b850v3_निकास(व्योम)
अणु
	i2c_del_driver(&stdp2690_ge_b850v3_fw_driver);
	i2c_del_driver(&stdp4028_ge_b850v3_fw_driver);
पूर्ण
module_निकास(stdpxxxx_ge_b850v3_निकास);

MODULE_AUTHOR("Peter Senna Tschudin <peter.senna@collabora.com>");
MODULE_AUTHOR("Martyn Welch <martyn.welch@collabora.co.uk>");
MODULE_DESCRIPTION("GE LVDS to DP++ display bridge)");
MODULE_LICENSE("GPL v2");
