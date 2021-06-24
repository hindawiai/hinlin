<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Author: Dan Scally <djrscally@gmail.com> */

#समावेश <linux/acpi.h>
#समावेश <linux/device.h>
#समावेश <linux/pci.h>
#समावेश <linux/property.h>
#समावेश <media/v4l2-fwnode.h>

#समावेश "cio2-bridge.h"

/*
 * Extend this array with ACPI Hardware IDs of devices known to be working
 * plus the number of link-frequencies expected by their drivers, aदीर्घ with
 * the frequency values in hertz. This is somewhat opportunistic way of adding
 * support क्रम this क्रम now in the hopes of a better source क्रम the inक्रमmation
 * (possibly some encoded value in the SSDB buffer that we're unaware of)
 * becoming apparent in the future.
 *
 * Do not add an entry क्रम a sensor that is not actually supported.
 */
अटल स्थिर काष्ठा cio2_sensor_config cio2_supported_sensors[] = अणु
	/* Omnivision OV5693 */
	CIO2_SENSOR_CONFIG("INT33BE", 0),
	/* Omnivision OV2680 */
	CIO2_SENSOR_CONFIG("OVTI2680", 0),
पूर्ण;

अटल स्थिर काष्ठा cio2_property_names prop_names = अणु
	.घड़ी_frequency = "clock-frequency",
	.rotation = "rotation",
	.bus_type = "bus-type",
	.data_lanes = "data-lanes",
	.remote_endpoपूर्णांक = "remote-endpoint",
	.link_frequencies = "link-frequencies",
पूर्ण;

अटल पूर्णांक cio2_bridge_पढ़ो_acpi_buffer(काष्ठा acpi_device *adev, अक्षर *id,
					व्योम *data, u32 size)
अणु
	काष्ठा acpi_buffer buffer = अणु ACPI_ALLOCATE_BUFFER, शून्य पूर्ण;
	जोड़ acpi_object *obj;
	acpi_status status;
	पूर्णांक ret = 0;

	status = acpi_evaluate_object(adev->handle, id, शून्य, &buffer);
	अगर (ACPI_FAILURE(status))
		वापस -ENODEV;

	obj = buffer.poपूर्णांकer;
	अगर (!obj) अणु
		dev_err(&adev->dev, "Couldn't locate ACPI buffer\n");
		वापस -ENODEV;
	पूर्ण

	अगर (obj->type != ACPI_TYPE_BUFFER) अणु
		dev_err(&adev->dev, "Not an ACPI buffer\n");
		ret = -ENODEV;
		जाओ out_मुक्त_buff;
	पूर्ण

	अगर (obj->buffer.length > size) अणु
		dev_err(&adev->dev, "Given buffer is too small\n");
		ret = -EINVAL;
		जाओ out_मुक्त_buff;
	पूर्ण

	स_नकल(data, obj->buffer.poपूर्णांकer, obj->buffer.length);

out_मुक्त_buff:
	kमुक्त(buffer.poपूर्णांकer);
	वापस ret;
पूर्ण

अटल व्योम cio2_bridge_create_fwnode_properties(
	काष्ठा cio2_sensor *sensor,
	काष्ठा cio2_bridge *bridge,
	स्थिर काष्ठा cio2_sensor_config *cfg)
अणु
	sensor->prop_names = prop_names;

	sensor->local_ref[0] = SOFTWARE_NODE_REFERENCE(&sensor->swnodes[SWNODE_CIO2_ENDPOINT]);
	sensor->remote_ref[0] = SOFTWARE_NODE_REFERENCE(&sensor->swnodes[SWNODE_SENSOR_ENDPOINT]);

	sensor->dev_properties[0] = PROPERTY_ENTRY_U32(
					sensor->prop_names.घड़ी_frequency,
					sensor->ssdb.mclkspeed);
	sensor->dev_properties[1] = PROPERTY_ENTRY_U8(
					sensor->prop_names.rotation,
					sensor->ssdb.degree);

	sensor->ep_properties[0] = PROPERTY_ENTRY_U32(
					sensor->prop_names.bus_type,
					V4L2_FWNODE_BUS_TYPE_CSI2_DPHY);
	sensor->ep_properties[1] = PROPERTY_ENTRY_U32_ARRAY_LEN(
					sensor->prop_names.data_lanes,
					bridge->data_lanes,
					sensor->ssdb.lanes);
	sensor->ep_properties[2] = PROPERTY_ENTRY_REF_ARRAY(
					sensor->prop_names.remote_endpoपूर्णांक,
					sensor->local_ref);

	अगर (cfg->nr_link_freqs > 0)
		sensor->ep_properties[3] = PROPERTY_ENTRY_U64_ARRAY_LEN(
			sensor->prop_names.link_frequencies,
			cfg->link_freqs,
			cfg->nr_link_freqs);

	sensor->cio2_properties[0] = PROPERTY_ENTRY_U32_ARRAY_LEN(
					sensor->prop_names.data_lanes,
					bridge->data_lanes,
					sensor->ssdb.lanes);
	sensor->cio2_properties[1] = PROPERTY_ENTRY_REF_ARRAY(
					sensor->prop_names.remote_endpoपूर्णांक,
					sensor->remote_ref);
पूर्ण

अटल व्योम cio2_bridge_init_swnode_names(काष्ठा cio2_sensor *sensor)
अणु
	snम_लिखो(sensor->node_names.remote_port,
		 माप(sensor->node_names.remote_port),
		 SWNODE_GRAPH_PORT_NAME_FMT, sensor->ssdb.link);
	snम_लिखो(sensor->node_names.port,
		 माप(sensor->node_names.port),
		 SWNODE_GRAPH_PORT_NAME_FMT, 0); /* Always port 0 */
	snम_लिखो(sensor->node_names.endpoपूर्णांक,
		 माप(sensor->node_names.endpoपूर्णांक),
		 SWNODE_GRAPH_ENDPOINT_NAME_FMT, 0); /* And endpoपूर्णांक 0 */
पूर्ण

अटल व्योम cio2_bridge_create_connection_swnodes(काष्ठा cio2_bridge *bridge,
						  काष्ठा cio2_sensor *sensor)
अणु
	काष्ठा software_node *nodes = sensor->swnodes;

	cio2_bridge_init_swnode_names(sensor);

	nodes[SWNODE_SENSOR_HID] = NODE_SENSOR(sensor->name,
					       sensor->dev_properties);
	nodes[SWNODE_SENSOR_PORT] = NODE_PORT(sensor->node_names.port,
					      &nodes[SWNODE_SENSOR_HID]);
	nodes[SWNODE_SENSOR_ENDPOINT] = NODE_ENDPOINT(
						sensor->node_names.endpoपूर्णांक,
						&nodes[SWNODE_SENSOR_PORT],
						sensor->ep_properties);
	nodes[SWNODE_CIO2_PORT] = NODE_PORT(sensor->node_names.remote_port,
					    &bridge->cio2_hid_node);
	nodes[SWNODE_CIO2_ENDPOINT] = NODE_ENDPOINT(
						sensor->node_names.endpoपूर्णांक,
						&nodes[SWNODE_CIO2_PORT],
						sensor->cio2_properties);
पूर्ण

अटल व्योम cio2_bridge_unरेजिस्टर_sensors(काष्ठा cio2_bridge *bridge)
अणु
	काष्ठा cio2_sensor *sensor;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < bridge->n_sensors; i++) अणु
		sensor = &bridge->sensors[i];
		software_node_unरेजिस्टर_nodes(sensor->swnodes);
		acpi_dev_put(sensor->adev);
	पूर्ण
पूर्ण

अटल पूर्णांक cio2_bridge_connect_sensor(स्थिर काष्ठा cio2_sensor_config *cfg,
				      काष्ठा cio2_bridge *bridge,
				      काष्ठा pci_dev *cio2)
अणु
	काष्ठा fwnode_handle *fwnode;
	काष्ठा cio2_sensor *sensor;
	काष्ठा acpi_device *adev;
	पूर्णांक ret;

	क्रम_each_acpi_dev_match(adev, cfg->hid, शून्य, -1) अणु
		अगर (!adev->status.enabled)
			जारी;

		अगर (bridge->n_sensors >= CIO2_NUM_PORTS) अणु
			dev_err(&cio2->dev, "Exceeded available CIO2 ports\n");
			cio2_bridge_unरेजिस्टर_sensors(bridge);
			ret = -EINVAL;
			जाओ err_out;
		पूर्ण

		sensor = &bridge->sensors[bridge->n_sensors];
		sensor->adev = adev;
		strscpy(sensor->name, cfg->hid, माप(sensor->name));

		ret = cio2_bridge_पढ़ो_acpi_buffer(adev, "SSDB",
						   &sensor->ssdb,
						   माप(sensor->ssdb));
		अगर (ret)
			जाओ err_put_adev;

		अगर (sensor->ssdb.lanes > CIO2_MAX_LANES) अणु
			dev_err(&adev->dev,
				"Number of lanes in SSDB is invalid\n");
			ret = -EINVAL;
			जाओ err_put_adev;
		पूर्ण

		cio2_bridge_create_fwnode_properties(sensor, bridge, cfg);
		cio2_bridge_create_connection_swnodes(bridge, sensor);

		ret = software_node_रेजिस्टर_nodes(sensor->swnodes);
		अगर (ret)
			जाओ err_put_adev;

		fwnode = software_node_fwnode(&sensor->swnodes[
						      SWNODE_SENSOR_HID]);
		अगर (!fwnode) अणु
			ret = -ENODEV;
			जाओ err_मुक्त_swnodes;
		पूर्ण

		adev->fwnode.secondary = fwnode;

		dev_info(&cio2->dev, "Found supported sensor %s\n",
			 acpi_dev_name(adev));

		bridge->n_sensors++;
	पूर्ण

	वापस 0;

err_मुक्त_swnodes:
	software_node_unरेजिस्टर_nodes(sensor->swnodes);
err_put_adev:
	acpi_dev_put(sensor->adev);
err_out:
	वापस ret;
पूर्ण

अटल पूर्णांक cio2_bridge_connect_sensors(काष्ठा cio2_bridge *bridge,
				       काष्ठा pci_dev *cio2)
अणु
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	क्रम (i = 0; i < ARRAY_SIZE(cio2_supported_sensors); i++) अणु
		स्थिर काष्ठा cio2_sensor_config *cfg =
			&cio2_supported_sensors[i];

		ret = cio2_bridge_connect_sensor(cfg, bridge, cio2);
		अगर (ret)
			जाओ err_unरेजिस्टर_sensors;
	पूर्ण

	वापस 0;

err_unरेजिस्टर_sensors:
	cio2_bridge_unरेजिस्टर_sensors(bridge);
	वापस ret;
पूर्ण

पूर्णांक cio2_bridge_init(काष्ठा pci_dev *cio2)
अणु
	काष्ठा device *dev = &cio2->dev;
	काष्ठा fwnode_handle *fwnode;
	काष्ठा cio2_bridge *bridge;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	bridge = kzalloc(माप(*bridge), GFP_KERNEL);
	अगर (!bridge)
		वापस -ENOMEM;

	strscpy(bridge->cio2_node_name, CIO2_HID,
		माप(bridge->cio2_node_name));
	bridge->cio2_hid_node.name = bridge->cio2_node_name;

	ret = software_node_रेजिस्टर(&bridge->cio2_hid_node);
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to register the CIO2 HID node\n");
		जाओ err_मुक्त_bridge;
	पूर्ण

	/*
	 * Map the lane arrangement, which is fixed क्रम the IPU3 (meaning we
	 * only need one, rather than one per sensor). We include it as a
	 * member of the काष्ठा cio2_bridge rather than a global variable so
	 * that it survives अगर the module is unloaded aदीर्घ with the rest of
	 * the काष्ठा.
	 */
	क्रम (i = 0; i < CIO2_MAX_LANES; i++)
		bridge->data_lanes[i] = i + 1;

	ret = cio2_bridge_connect_sensors(bridge, cio2);
	अगर (ret || bridge->n_sensors == 0)
		जाओ err_unरेजिस्टर_cio2;

	dev_info(dev, "Connected %d cameras\n", bridge->n_sensors);

	fwnode = software_node_fwnode(&bridge->cio2_hid_node);
	अगर (!fwnode) अणु
		dev_err(dev, "Error getting fwnode from cio2 software_node\n");
		ret = -ENODEV;
		जाओ err_unरेजिस्टर_sensors;
	पूर्ण

	set_secondary_fwnode(dev, fwnode);

	वापस 0;

err_unरेजिस्टर_sensors:
	cio2_bridge_unरेजिस्टर_sensors(bridge);
err_unरेजिस्टर_cio2:
	software_node_unरेजिस्टर(&bridge->cio2_hid_node);
err_मुक्त_bridge:
	kमुक्त(bridge);

	वापस ret;
पूर्ण
