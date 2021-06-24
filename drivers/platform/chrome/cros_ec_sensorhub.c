<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Sensor HUB driver that discovers sensors behind a ChromeOS Embedded
 * Controller.
 *
 * Copyright 2019 Google LLC
 */

#समावेश <linux/init.h>
#समावेश <linux/device.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_data/cros_ec_commands.h>
#समावेश <linux/platक्रमm_data/cros_ec_proto.h>
#समावेश <linux/platक्रमm_data/cros_ec_sensorhub.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>

#घोषणा DRV_NAME		"cros-ec-sensorhub"

अटल व्योम cros_ec_sensorhub_मुक्त_sensor(व्योम *arg)
अणु
	काष्ठा platक्रमm_device *pdev = arg;

	platक्रमm_device_unरेजिस्टर(pdev);
पूर्ण

अटल पूर्णांक cros_ec_sensorhub_allocate_sensor(काष्ठा device *parent,
					     अक्षर *sensor_name,
					     पूर्णांक sensor_num)
अणु
	काष्ठा cros_ec_sensor_platक्रमm sensor_platक्रमms = अणु
		.sensor_num = sensor_num,
	पूर्ण;
	काष्ठा platक्रमm_device *pdev;

	pdev = platक्रमm_device_रेजिस्टर_data(parent, sensor_name,
					     PLATFORM_DEVID_AUTO,
					     &sensor_platक्रमms,
					     माप(sensor_platक्रमms));
	अगर (IS_ERR(pdev))
		वापस PTR_ERR(pdev);

	वापस devm_add_action_or_reset(parent,
					cros_ec_sensorhub_मुक्त_sensor,
					pdev);
पूर्ण

अटल पूर्णांक cros_ec_sensorhub_रेजिस्टर(काष्ठा device *dev,
				      काष्ठा cros_ec_sensorhub *sensorhub)
अणु
	पूर्णांक sensor_type[MOTIONSENSE_TYPE_MAX] = अणु 0 पूर्ण;
	काष्ठा cros_ec_command *msg = sensorhub->msg;
	काष्ठा cros_ec_dev *ec = sensorhub->ec;
	पूर्णांक ret, i;
	अक्षर *name;


	msg->version = 1;
	msg->insize = माप(काष्ठा ec_response_motion_sense);
	msg->outsize = माप(काष्ठा ec_params_motion_sense);

	क्रम (i = 0; i < sensorhub->sensor_num; i++) अणु
		sensorhub->params->cmd = MOTIONSENSE_CMD_INFO;
		sensorhub->params->info.sensor_num = i;

		ret = cros_ec_cmd_xfer_status(ec->ec_dev, msg);
		अगर (ret < 0) अणु
			dev_warn(dev, "no info for EC sensor %d : %d/%d\n",
				 i, ret, msg->result);
			जारी;
		पूर्ण

		चयन (sensorhub->resp->info.type) अणु
		हाल MOTIONSENSE_TYPE_ACCEL:
			name = "cros-ec-accel";
			अवरोध;
		हाल MOTIONSENSE_TYPE_BARO:
			name = "cros-ec-baro";
			अवरोध;
		हाल MOTIONSENSE_TYPE_GYRO:
			name = "cros-ec-gyro";
			अवरोध;
		हाल MOTIONSENSE_TYPE_MAG:
			name = "cros-ec-mag";
			अवरोध;
		हाल MOTIONSENSE_TYPE_PROX:
			name = "cros-ec-prox";
			अवरोध;
		हाल MOTIONSENSE_TYPE_LIGHT:
			name = "cros-ec-light";
			अवरोध;
		हाल MOTIONSENSE_TYPE_ACTIVITY:
			name = "cros-ec-activity";
			अवरोध;
		शेष:
			dev_warn(dev, "unknown type %d\n",
				 sensorhub->resp->info.type);
			जारी;
		पूर्ण

		ret = cros_ec_sensorhub_allocate_sensor(dev, name, i);
		अगर (ret)
			वापस ret;

		sensor_type[sensorhub->resp->info.type]++;
	पूर्ण

	अगर (sensor_type[MOTIONSENSE_TYPE_ACCEL] >= 2)
		ec->has_kb_wake_angle = true;

	अगर (cros_ec_check_features(ec,
				   EC_FEATURE_REFINED_TABLET_MODE_HYSTERESIS)) अणु
		ret = cros_ec_sensorhub_allocate_sensor(dev,
							"cros-ec-lid-angle",
							0);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cros_ec_sensorhub_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा cros_ec_dev *ec = dev_get_drvdata(dev->parent);
	काष्ठा cros_ec_sensorhub *data;
	काष्ठा cros_ec_command *msg;
	पूर्णांक ret, i, sensor_num;

	msg = devm_kzalloc(dev, माप(काष्ठा cros_ec_command) +
			   max((u16)माप(काष्ठा ec_params_motion_sense),
			       ec->ec_dev->max_response), GFP_KERNEL);
	अगर (!msg)
		वापस -ENOMEM;

	msg->command = EC_CMD_MOTION_SENSE_CMD + ec->cmd_offset;

	data = devm_kzalloc(dev, माप(काष्ठा cros_ec_sensorhub), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	mutex_init(&data->cmd_lock);

	data->dev = dev;
	data->ec = ec;
	data->msg = msg;
	data->params = (काष्ठा ec_params_motion_sense *)msg->data;
	data->resp = (काष्ठा ec_response_motion_sense *)msg->data;

	dev_set_drvdata(dev, data);

	/* Check whether this EC is a sensor hub. */
	अगर (cros_ec_check_features(ec, EC_FEATURE_MOTION_SENSE)) अणु
		sensor_num = cros_ec_get_sensor_count(ec);
		अगर (sensor_num < 0) अणु
			dev_err(dev,
				"Unable to retrieve sensor information (err:%d)\n",
				sensor_num);
			वापस sensor_num;
		पूर्ण
		अगर (sensor_num == 0) अणु
			dev_err(dev, "Zero sensors reported.\n");
			वापस -EINVAL;
		पूर्ण
		data->sensor_num = sensor_num;

		/*
		 * Prepare the ring handler beक्रमe क्रमागतering the
		 * sensors.
		 */
		अगर (cros_ec_check_features(ec, EC_FEATURE_MOTION_SENSE_FIFO)) अणु
			ret = cros_ec_sensorhub_ring_allocate(data);
			अगर (ret)
				वापस ret;
		पूर्ण

		/* Enumerate the sensors.*/
		ret = cros_ec_sensorhub_रेजिस्टर(dev, data);
		अगर (ret)
			वापस ret;

		/*
		 * When the EC करोes not have a FIFO, the sensors will query
		 * their data themselves via sysfs or a software trigger.
		 */
		अगर (cros_ec_check_features(ec, EC_FEATURE_MOTION_SENSE_FIFO)) अणु
			ret = cros_ec_sensorhub_ring_add(data);
			अगर (ret)
				वापस ret;
			/*
			 * The msg and its data is not under the control of the
			 * ring handler.
			 */
			वापस devm_add_action_or_reset(dev,
					cros_ec_sensorhub_ring_हटाओ,
					data);
		पूर्ण

	पूर्ण अन्यथा अणु
		/*
		 * If the device has sensors but करोes not claim to
		 * be a sensor hub, we are in legacy mode.
		 */
		data->sensor_num = 2;
		क्रम (i = 0; i < data->sensor_num; i++) अणु
			ret = cros_ec_sensorhub_allocate_sensor(dev,
						"cros-ec-accel-legacy", i);
			अगर (ret)
				वापस ret;
		पूर्ण
	पूर्ण


	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
/*
 * When the EC is suspending, we must stop sending पूर्णांकerrupt,
 * we may use the same पूर्णांकerrupt line क्रम waking up the device.
 * Tell the EC to stop sending non-पूर्णांकerrupt event on the iio ring.
 */
अटल पूर्णांक cros_ec_sensorhub_suspend(काष्ठा device *dev)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा cros_ec_sensorhub *sensorhub = platक्रमm_get_drvdata(pdev);
	काष्ठा cros_ec_dev *ec = sensorhub->ec;

	अगर (cros_ec_check_features(ec, EC_FEATURE_MOTION_SENSE_FIFO))
		वापस cros_ec_sensorhub_ring_fअगरo_enable(sensorhub, false);
	वापस 0;
पूर्ण

अटल पूर्णांक cros_ec_sensorhub_resume(काष्ठा device *dev)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा cros_ec_sensorhub *sensorhub = platक्रमm_get_drvdata(pdev);
	काष्ठा cros_ec_dev *ec = sensorhub->ec;

	अगर (cros_ec_check_features(ec, EC_FEATURE_MOTION_SENSE_FIFO))
		वापस cros_ec_sensorhub_ring_fअगरo_enable(sensorhub, true);
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(cros_ec_sensorhub_pm_ops,
		cros_ec_sensorhub_suspend,
		cros_ec_sensorhub_resume);

अटल काष्ठा platक्रमm_driver cros_ec_sensorhub_driver = अणु
	.driver = अणु
		.name = DRV_NAME,
		.pm = &cros_ec_sensorhub_pm_ops,
	पूर्ण,
	.probe = cros_ec_sensorhub_probe,
पूर्ण;

module_platक्रमm_driver(cros_ec_sensorhub_driver);

MODULE_ALIAS("platform:" DRV_NAME);
MODULE_AUTHOR("Gwendal Grignou <gwendal@chromium.org>");
MODULE_DESCRIPTION("ChromeOS EC MEMS Sensor Hub Driver");
MODULE_LICENSE("GPL");
