<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * v4l2-i2c - I2C helpers क्रम Video4Linux2
 */

#समावेश <linux/i2c.h>
#समावेश <linux/module.h>
#समावेश <media/v4l2-common.h>
#समावेश <media/v4l2-device.h>

व्योम v4l2_i2c_subdev_unरेजिस्टर(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);

	/*
	 * We need to unरेजिस्टर the i2c client
	 * explicitly. We cannot rely on
	 * i2c_del_adapter to always unरेजिस्टर
	 * clients क्रम us, since अगर the i2c bus is a
	 * platक्रमm bus, then it is never deleted.
	 *
	 * Device tree or ACPI based devices must not
	 * be unरेजिस्टरed as they have not been
	 * रेजिस्टरed by us, and would not be
	 * re-created by just probing the V4L2 driver.
	 */
	अगर (client && !client->dev.of_node && !client->dev.fwnode)
		i2c_unरेजिस्टर_device(client);
पूर्ण

व्योम v4l2_i2c_subdev_set_name(काष्ठा v4l2_subdev *sd,
			      काष्ठा i2c_client *client,
			      स्थिर अक्षर *devname, स्थिर अक्षर *postfix)
अणु
	अगर (!devname)
		devname = client->dev.driver->name;
	अगर (!postfix)
		postfix = "";

	snम_लिखो(sd->name, माप(sd->name), "%s%s %d-%04x", devname, postfix,
		 i2c_adapter_id(client->adapter), client->addr);
पूर्ण
EXPORT_SYMBOL_GPL(v4l2_i2c_subdev_set_name);

व्योम v4l2_i2c_subdev_init(काष्ठा v4l2_subdev *sd, काष्ठा i2c_client *client,
			  स्थिर काष्ठा v4l2_subdev_ops *ops)
अणु
	v4l2_subdev_init(sd, ops);
	sd->flags |= V4L2_SUBDEV_FL_IS_I2C;
	/* the owner is the same as the i2c_client's driver owner */
	sd->owner = client->dev.driver->owner;
	sd->dev = &client->dev;
	/* i2c_client and v4l2_subdev poपूर्णांक to one another */
	v4l2_set_subdevdata(sd, client);
	i2c_set_clientdata(client, sd);
	v4l2_i2c_subdev_set_name(sd, client, शून्य, शून्य);
पूर्ण
EXPORT_SYMBOL_GPL(v4l2_i2c_subdev_init);

/* Load an i2c sub-device. */
काष्ठा v4l2_subdev
*v4l2_i2c_new_subdev_board(काष्ठा v4l2_device *v4l2_dev,
			   काष्ठा i2c_adapter *adapter,
			   काष्ठा i2c_board_info *info,
			   स्थिर अचिन्हित लघु *probe_addrs)
अणु
	काष्ठा v4l2_subdev *sd = शून्य;
	काष्ठा i2c_client *client;

	अगर (!v4l2_dev)
		वापस शून्य;

	request_module(I2C_MODULE_PREFIX "%s", info->type);

	/* Create the i2c client */
	अगर (info->addr == 0 && probe_addrs)
		client = i2c_new_scanned_device(adapter, info, probe_addrs,
						शून्य);
	अन्यथा
		client = i2c_new_client_device(adapter, info);

	/*
	 * Note: by loading the module first we are certain that c->driver
	 * will be set अगर the driver was found. If the module was not loaded
	 * first, then the i2c core tries to delay-load the module क्रम us,
	 * and then c->driver is still शून्य until the module is finally
	 * loaded. This delay-load mechanism करोesn't work अगर other drivers
	 * want to use the i2c device, so explicitly loading the module
	 * is the best alternative.
	 */
	अगर (!i2c_client_has_driver(client))
		जाओ error;

	/* Lock the module so we can safely get the v4l2_subdev poपूर्णांकer */
	अगर (!try_module_get(client->dev.driver->owner))
		जाओ error;
	sd = i2c_get_clientdata(client);

	/*
	 * Register with the v4l2_device which increases the module's
	 * use count as well.
	 */
	अगर (v4l2_device_रेजिस्टर_subdev(v4l2_dev, sd))
		sd = शून्य;
	/* Decrease the module use count to match the first try_module_get. */
	module_put(client->dev.driver->owner);

error:
	/*
	 * If we have a client but no subdev, then something went wrong and
	 * we must unरेजिस्टर the client.
	 */
	अगर (!IS_ERR(client) && !sd)
		i2c_unरेजिस्टर_device(client);
	वापस sd;
पूर्ण
EXPORT_SYMBOL_GPL(v4l2_i2c_new_subdev_board);

काष्ठा v4l2_subdev *v4l2_i2c_new_subdev(काष्ठा v4l2_device *v4l2_dev,
					काष्ठा i2c_adapter *adapter,
					स्थिर अक्षर *client_type,
					u8 addr,
					स्थिर अचिन्हित लघु *probe_addrs)
अणु
	काष्ठा i2c_board_info info;

	/*
	 * Setup the i2c board info with the device type and
	 * the device address.
	 */
	स_रखो(&info, 0, माप(info));
	strscpy(info.type, client_type, माप(info.type));
	info.addr = addr;

	वापस v4l2_i2c_new_subdev_board(v4l2_dev, adapter, &info,
					 probe_addrs);
पूर्ण
EXPORT_SYMBOL_GPL(v4l2_i2c_new_subdev);

/* Return i2c client address of v4l2_subdev. */
अचिन्हित लघु v4l2_i2c_subdev_addr(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);

	वापस client ? client->addr : I2C_CLIENT_END;
पूर्ण
EXPORT_SYMBOL_GPL(v4l2_i2c_subdev_addr);

/*
 * Return a list of I2C tuner addresses to probe. Use only अगर the tuner
 * addresses are unknown.
 */
स्थिर अचिन्हित लघु *v4l2_i2c_tuner_addrs(क्रमागत v4l2_i2c_tuner_type type)
अणु
	अटल स्थिर अचिन्हित लघु radio_addrs[] = अणु
#अगर IS_ENABLED(CONFIG_MEDIA_TUNER_TEA5761)
		0x10,
#पूर्ण_अगर
		0x60,
		I2C_CLIENT_END
	पूर्ण;
	अटल स्थिर अचिन्हित लघु demod_addrs[] = अणु
		0x42, 0x43, 0x4a, 0x4b,
		I2C_CLIENT_END
	पूर्ण;
	अटल स्थिर अचिन्हित लघु tv_addrs[] = अणु
		0x42, 0x43, 0x4a, 0x4b,		/* tda8290 */
		0x60, 0x61, 0x62, 0x63, 0x64,
		I2C_CLIENT_END
	पूर्ण;

	चयन (type) अणु
	हाल ADDRS_RADIO:
		वापस radio_addrs;
	हाल ADDRS_DEMOD:
		वापस demod_addrs;
	हाल ADDRS_TV:
		वापस tv_addrs;
	हाल ADDRS_TV_WITH_DEMOD:
		वापस tv_addrs + 4;
	पूर्ण
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(v4l2_i2c_tuner_addrs);
