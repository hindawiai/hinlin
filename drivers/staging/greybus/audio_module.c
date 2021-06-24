<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Greybus audio driver
 * Copyright 2015 Google Inc.
 * Copyright 2015 Linaro Ltd.
 */
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <sound/soc.h>
#समावेश <sound/pcm_params.h>

#समावेश "audio_codec.h"
#समावेश "audio_apbridgea.h"
#समावेश "audio_manager.h"

/*
 * gb_snd management functions
 */

अटल पूर्णांक gbaudio_request_jack(काष्ठा gbaudio_module_info *module,
				काष्ठा gb_audio_jack_event_request *req)
अणु
	पूर्णांक report;
	काष्ठा snd_jack *jack = module->headset.jack.jack;
	काष्ठा snd_jack *btn_jack = module->button.jack.jack;

	अगर (!jack) अणु
		dev_err_ratelimited(module->dev,
				    "Invalid jack event received:type: %u, event: %u\n",
				    req->jack_attribute, req->event);
		वापस -EINVAL;
	पूर्ण

	dev_warn_ratelimited(module->dev,
			     "Jack Event received: type: %u, event: %u\n",
			     req->jack_attribute, req->event);

	अगर (req->event == GB_AUDIO_JACK_EVENT_REMOVAL) अणु
		module->jack_type = 0;
		अगर (btn_jack && module->button_status) अणु
			snd_soc_jack_report(&module->button.jack, 0,
					    module->button_mask);
			module->button_status = 0;
		पूर्ण
		snd_soc_jack_report(&module->headset.jack, 0,
				    module->jack_mask);
		वापस 0;
	पूर्ण

	report = req->jack_attribute & module->jack_mask;
	अगर (!report) अणु
		dev_err_ratelimited(module->dev,
				    "Invalid jack event received:type: %u, event: %u\n",
				    req->jack_attribute, req->event);
		वापस -EINVAL;
	पूर्ण

	अगर (module->jack_type)
		dev_warn_ratelimited(module->dev,
				     "Modifying jack from %d to %d\n",
				     module->jack_type, report);

	module->jack_type = report;
	snd_soc_jack_report(&module->headset.jack, report, module->jack_mask);

	वापस 0;
पूर्ण

अटल पूर्णांक gbaudio_request_button(काष्ठा gbaudio_module_info *module,
				  काष्ठा gb_audio_button_event_request *req)
अणु
	पूर्णांक soc_button_id, report;
	काष्ठा snd_jack *btn_jack = module->button.jack.jack;

	अगर (!btn_jack) अणु
		dev_err_ratelimited(module->dev,
				    "Invalid button event received:type: %u, event: %u\n",
				    req->button_id, req->event);
		वापस -EINVAL;
	पूर्ण

	dev_warn_ratelimited(module->dev,
			     "Button Event received: id: %u, event: %u\n",
			     req->button_id, req->event);

	/* currently supports 4 buttons only */
	अगर (!module->jack_type) अणु
		dev_err_ratelimited(module->dev,
				    "Jack not present. Bogus event!!\n");
		वापस -EINVAL;
	पूर्ण

	report = module->button_status & module->button_mask;
	soc_button_id = 0;

	चयन (req->button_id) अणु
	हाल 1:
		soc_button_id = SND_JACK_BTN_0 & module->button_mask;
		अवरोध;

	हाल 2:
		soc_button_id = SND_JACK_BTN_1 & module->button_mask;
		अवरोध;

	हाल 3:
		soc_button_id = SND_JACK_BTN_2 & module->button_mask;
		अवरोध;

	हाल 4:
		soc_button_id = SND_JACK_BTN_3 & module->button_mask;
		अवरोध;
	पूर्ण

	अगर (!soc_button_id) अणु
		dev_err_ratelimited(module->dev,
				    "Invalid button request received\n");
		वापस -EINVAL;
	पूर्ण

	अगर (req->event == GB_AUDIO_BUTTON_EVENT_PRESS)
		report = report | soc_button_id;
	अन्यथा
		report = report & ~soc_button_id;

	module->button_status = report;

	snd_soc_jack_report(&module->button.jack, report, module->button_mask);

	वापस 0;
पूर्ण

अटल पूर्णांक gbaudio_request_stream(काष्ठा gbaudio_module_info *module,
				  काष्ठा gb_audio_streaming_event_request *req)
अणु
	dev_warn(module->dev, "Audio Event received: cport: %u, event: %u\n",
		 le16_to_cpu(req->data_cport), req->event);

	वापस 0;
पूर्ण

अटल पूर्णांक gbaudio_codec_request_handler(काष्ठा gb_operation *op)
अणु
	काष्ठा gb_connection *connection = op->connection;
	काष्ठा gbaudio_module_info *module =
		greybus_get_drvdata(connection->bundle);
	काष्ठा gb_operation_msg_hdr *header = op->request->header;
	काष्ठा gb_audio_streaming_event_request *stream_req;
	काष्ठा gb_audio_jack_event_request *jack_req;
	काष्ठा gb_audio_button_event_request *button_req;
	पूर्णांक ret;

	चयन (header->type) अणु
	हाल GB_AUDIO_TYPE_STREAMING_EVENT:
		stream_req = op->request->payload;
		ret = gbaudio_request_stream(module, stream_req);
		अवरोध;

	हाल GB_AUDIO_TYPE_JACK_EVENT:
		jack_req = op->request->payload;
		ret = gbaudio_request_jack(module, jack_req);
		अवरोध;

	हाल GB_AUDIO_TYPE_BUTTON_EVENT:
		button_req = op->request->payload;
		ret = gbaudio_request_button(module, button_req);
		अवरोध;

	शेष:
		dev_err_ratelimited(&connection->bundle->dev,
				    "Invalid Audio Event received\n");
		वापस -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक gb_audio_add_mgmt_connection(काष्ठा gbaudio_module_info *gbmodule,
					काष्ठा greybus_descriptor_cport *cport_desc,
					काष्ठा gb_bundle *bundle)
अणु
	काष्ठा gb_connection *connection;

	/* Management Cport */
	अगर (gbmodule->mgmt_connection) अणु
		dev_err(&bundle->dev,
			"Can't have multiple Management connections\n");
		वापस -ENODEV;
	पूर्ण

	connection = gb_connection_create(bundle, le16_to_cpu(cport_desc->id),
					  gbaudio_codec_request_handler);
	अगर (IS_ERR(connection))
		वापस PTR_ERR(connection);

	greybus_set_drvdata(bundle, gbmodule);
	gbmodule->mgmt_connection = connection;

	वापस 0;
पूर्ण

अटल पूर्णांक gb_audio_add_data_connection(काष्ठा gbaudio_module_info *gbmodule,
					काष्ठा greybus_descriptor_cport *cport_desc,
					काष्ठा gb_bundle *bundle)
अणु
	काष्ठा gb_connection *connection;
	काष्ठा gbaudio_data_connection *dai;

	dai = devm_kzalloc(gbmodule->dev, माप(*dai), GFP_KERNEL);
	अगर (!dai)
		वापस -ENOMEM;

	connection = gb_connection_create_offloaded(bundle,
						    le16_to_cpu(cport_desc->id),
						    GB_CONNECTION_FLAG_CSD);
	अगर (IS_ERR(connection)) अणु
		devm_kमुक्त(gbmodule->dev, dai);
		वापस PTR_ERR(connection);
	पूर्ण

	greybus_set_drvdata(bundle, gbmodule);
	dai->id = 0;
	dai->data_cport = cpu_to_le16(connection->पूर्णांकf_cport_id);
	dai->connection = connection;
	list_add(&dai->list, &gbmodule->data_list);

	वापस 0;
पूर्ण

/*
 * This is the basic hook get things initialized and रेजिस्टरed w/ gb
 */

अटल पूर्णांक gb_audio_probe(काष्ठा gb_bundle *bundle,
			  स्थिर काष्ठा greybus_bundle_id *id)
अणु
	काष्ठा device *dev = &bundle->dev;
	काष्ठा gbaudio_module_info *gbmodule;
	काष्ठा greybus_descriptor_cport *cport_desc;
	काष्ठा gb_audio_manager_module_descriptor desc;
	काष्ठा gbaudio_data_connection *dai, *_dai;
	पूर्णांक ret, i;
	काष्ठा gb_audio_topology *topology;

	/* There should be at least one Management and one Data cport */
	अगर (bundle->num_cports < 2)
		वापस -ENODEV;

	/*
	 * There can be only one Management connection and any number of data
	 * connections.
	 */
	gbmodule = devm_kzalloc(dev, माप(*gbmodule), GFP_KERNEL);
	अगर (!gbmodule)
		वापस -ENOMEM;

	gbmodule->num_data_connections = bundle->num_cports - 1;
	INIT_LIST_HEAD(&gbmodule->data_list);
	INIT_LIST_HEAD(&gbmodule->widget_list);
	INIT_LIST_HEAD(&gbmodule->ctl_list);
	INIT_LIST_HEAD(&gbmodule->widget_ctl_list);
	INIT_LIST_HEAD(&gbmodule->jack_list);
	gbmodule->dev = dev;
	snम_लिखो(gbmodule->name, माप(gbmodule->name), "%s.%s", dev->driver->name,
		 dev_name(dev));
	greybus_set_drvdata(bundle, gbmodule);

	/* Create all connections */
	क्रम (i = 0; i < bundle->num_cports; i++) अणु
		cport_desc = &bundle->cport_desc[i];

		चयन (cport_desc->protocol_id) अणु
		हाल GREYBUS_PROTOCOL_AUDIO_MGMT:
			ret = gb_audio_add_mgmt_connection(gbmodule, cport_desc,
							   bundle);
			अगर (ret)
				जाओ destroy_connections;
			अवरोध;
		हाल GREYBUS_PROTOCOL_AUDIO_DATA:
			ret = gb_audio_add_data_connection(gbmodule, cport_desc,
							   bundle);
			अगर (ret)
				जाओ destroy_connections;
			अवरोध;
		शेष:
			dev_err(dev, "Unsupported protocol: 0x%02x\n",
				cport_desc->protocol_id);
			ret = -ENODEV;
			जाओ destroy_connections;
		पूर्ण
	पूर्ण

	/* There must be a management cport */
	अगर (!gbmodule->mgmt_connection) अणु
		ret = -EINVAL;
		dev_err(dev, "Missing management connection\n");
		जाओ destroy_connections;
	पूर्ण

	/* Initialize management connection */
	ret = gb_connection_enable(gbmodule->mgmt_connection);
	अगर (ret) अणु
		dev_err(dev, "%d: Error while enabling mgmt connection\n", ret);
		जाओ destroy_connections;
	पूर्ण
	gbmodule->dev_id = gbmodule->mgmt_connection->पूर्णांकf->पूर्णांकerface_id;

	/*
	 * FIXME: दो_स्मृति क्रम topology happens via audio_gb driver
	 * should be करोne within codec driver itself
	 */
	ret = gb_audio_gb_get_topology(gbmodule->mgmt_connection, &topology);
	अगर (ret) अणु
		dev_err(dev, "%d:Error while fetching topology\n", ret);
		जाओ disable_connection;
	पूर्ण

	/* process topology data */
	ret = gbaudio_tplg_parse_data(gbmodule, topology);
	अगर (ret) अणु
		dev_err(dev, "%d:Error while parsing topology data\n",
			ret);
		जाओ मुक्त_topology;
	पूर्ण
	gbmodule->topology = topology;

	/* Initialize data connections */
	list_क्रम_each_entry(dai, &gbmodule->data_list, list) अणु
		ret = gb_connection_enable(dai->connection);
		अगर (ret) अणु
			dev_err(dev,
				"%d:Error while enabling %d:data connection\n",
				ret, le16_to_cpu(dai->data_cport));
			जाओ disable_data_connection;
		पूर्ण
	पूर्ण

	/* रेजिस्टर module with gbcodec */
	ret = gbaudio_रेजिस्टर_module(gbmodule);
	अगर (ret)
		जाओ disable_data_connection;

	/* inक्रमm above layer क्रम uevent */
	dev_dbg(dev, "Inform set_event:%d to above layer\n", 1);
	/* prepare क्रम the audio manager */
	strscpy(desc.name, gbmodule->name, माप(desc.name));
	desc.vid = 2; /* toकरो */
	desc.pid = 3; /* toकरो */
	desc.पूर्णांकf_id = gbmodule->dev_id;
	desc.op_devices = gbmodule->op_devices;
	desc.ip_devices = gbmodule->ip_devices;
	gbmodule->manager_id = gb_audio_manager_add(&desc);

	dev_dbg(dev, "Add GB Audio device:%s\n", gbmodule->name);

	gb_pm_runसमय_put_स्वतःsuspend(bundle);

	वापस 0;

disable_data_connection:
	list_क्रम_each_entry_safe(dai, _dai, &gbmodule->data_list, list)
		gb_connection_disable(dai->connection);
	gbaudio_tplg_release(gbmodule);
	gbmodule->topology = शून्य;

मुक्त_topology:
	kमुक्त(topology);

disable_connection:
	gb_connection_disable(gbmodule->mgmt_connection);

destroy_connections:
	list_क्रम_each_entry_safe(dai, _dai, &gbmodule->data_list, list) अणु
		gb_connection_destroy(dai->connection);
		list_del(&dai->list);
		devm_kमुक्त(dev, dai);
	पूर्ण

	अगर (gbmodule->mgmt_connection)
		gb_connection_destroy(gbmodule->mgmt_connection);

	devm_kमुक्त(dev, gbmodule);

	वापस ret;
पूर्ण

अटल व्योम gb_audio_disconnect(काष्ठा gb_bundle *bundle)
अणु
	काष्ठा gbaudio_module_info *gbmodule = greybus_get_drvdata(bundle);
	काष्ठा gbaudio_data_connection *dai, *_dai;

	gb_pm_runसमय_get_sync(bundle);

	/* cleanup module related resources first */
	gbaudio_unरेजिस्टर_module(gbmodule);

	/* inक्रमm uevent to above layers */
	gb_audio_manager_हटाओ(gbmodule->manager_id);

	gbaudio_tplg_release(gbmodule);
	kमुक्त(gbmodule->topology);
	gbmodule->topology = शून्य;
	gb_connection_disable(gbmodule->mgmt_connection);
	list_क्रम_each_entry_safe(dai, _dai, &gbmodule->data_list, list) अणु
		gb_connection_disable(dai->connection);
		gb_connection_destroy(dai->connection);
		list_del(&dai->list);
		devm_kमुक्त(gbmodule->dev, dai);
	पूर्ण
	gb_connection_destroy(gbmodule->mgmt_connection);
	gbmodule->mgmt_connection = शून्य;

	devm_kमुक्त(&bundle->dev, gbmodule);
पूर्ण

अटल स्थिर काष्ठा greybus_bundle_id gb_audio_id_table[] = अणु
	अणु GREYBUS_DEVICE_CLASS(GREYBUS_CLASS_AUDIO) पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(greybus, gb_audio_id_table);

#अगर_घोषित CONFIG_PM
अटल पूर्णांक gb_audio_suspend(काष्ठा device *dev)
अणु
	काष्ठा gb_bundle *bundle = to_gb_bundle(dev);
	काष्ठा gbaudio_module_info *gbmodule = greybus_get_drvdata(bundle);
	काष्ठा gbaudio_data_connection *dai;

	list_क्रम_each_entry(dai, &gbmodule->data_list, list)
		gb_connection_disable(dai->connection);

	gb_connection_disable(gbmodule->mgmt_connection);

	वापस 0;
पूर्ण

अटल पूर्णांक gb_audio_resume(काष्ठा device *dev)
अणु
	काष्ठा gb_bundle *bundle = to_gb_bundle(dev);
	काष्ठा gbaudio_module_info *gbmodule = greybus_get_drvdata(bundle);
	काष्ठा gbaudio_data_connection *dai;
	पूर्णांक ret;

	ret = gb_connection_enable(gbmodule->mgmt_connection);
	अगर (ret) अणु
		dev_err(dev, "%d:Error while enabling mgmt connection\n", ret);
		वापस ret;
	पूर्ण

	list_क्रम_each_entry(dai, &gbmodule->data_list, list) अणु
		ret = gb_connection_enable(dai->connection);
		अगर (ret) अणु
			dev_err(dev,
				"%d:Error while enabling %d:data connection\n",
				ret, le16_to_cpu(dai->data_cport));
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा dev_pm_ops gb_audio_pm_ops = अणु
	SET_RUNTIME_PM_OPS(gb_audio_suspend, gb_audio_resume, शून्य)
पूर्ण;

अटल काष्ठा greybus_driver gb_audio_driver = अणु
	.name		= "gb-audio",
	.probe		= gb_audio_probe,
	.disconnect	= gb_audio_disconnect,
	.id_table	= gb_audio_id_table,
	.driver.pm	= &gb_audio_pm_ops,
पूर्ण;
module_greybus_driver(gb_audio_driver);

MODULE_DESCRIPTION("Greybus Audio module driver");
MODULE_AUTHOR("Vaibhav Agarwal <vaibhav.agarwal@linaro.org>");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:gbaudio-module");
