<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * v4l2-spi - SPI helpers क्रम Video4Linux2
 */

#समावेश <linux/module.h>
#समावेश <linux/spi/spi.h>
#समावेश <media/v4l2-common.h>
#समावेश <media/v4l2-device.h>

व्योम v4l2_spi_subdev_unरेजिस्टर(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा spi_device *spi = v4l2_get_subdevdata(sd);

	अगर (spi && !spi->dev.of_node && !spi->dev.fwnode)
		spi_unरेजिस्टर_device(spi);
पूर्ण

व्योम v4l2_spi_subdev_init(काष्ठा v4l2_subdev *sd, काष्ठा spi_device *spi,
			  स्थिर काष्ठा v4l2_subdev_ops *ops)
अणु
	v4l2_subdev_init(sd, ops);
	sd->flags |= V4L2_SUBDEV_FL_IS_SPI;
	/* the owner is the same as the spi_device's driver owner */
	sd->owner = spi->dev.driver->owner;
	sd->dev = &spi->dev;
	/* spi_device and v4l2_subdev poपूर्णांक to one another */
	v4l2_set_subdevdata(sd, spi);
	spi_set_drvdata(spi, sd);
	/* initialize name */
	snम_लिखो(sd->name, माप(sd->name), "%s %s",
		 spi->dev.driver->name, dev_name(&spi->dev));
पूर्ण
EXPORT_SYMBOL_GPL(v4l2_spi_subdev_init);

काष्ठा v4l2_subdev *v4l2_spi_new_subdev(काष्ठा v4l2_device *v4l2_dev,
					काष्ठा spi_master *master,
					काष्ठा spi_board_info *info)
अणु
	काष्ठा v4l2_subdev *sd = शून्य;
	काष्ठा spi_device *spi = शून्य;

	अगर (!v4l2_dev)
		वापस शून्य;
	अगर (info->modalias[0])
		request_module(info->modalias);

	spi = spi_new_device(master, info);

	अगर (!spi || !spi->dev.driver)
		जाओ error;

	अगर (!try_module_get(spi->dev.driver->owner))
		जाओ error;

	sd = spi_get_drvdata(spi);

	/*
	 * Register with the v4l2_device which increases the module's
	 * use count as well.
	 */
	अगर (v4l2_device_रेजिस्टर_subdev(v4l2_dev, sd))
		sd = शून्य;

	/* Decrease the module use count to match the first try_module_get. */
	module_put(spi->dev.driver->owner);

error:
	/*
	 * If we have a client but no subdev, then something went wrong and
	 * we must unरेजिस्टर the client.
	 */
	अगर (!sd)
		spi_unरेजिस्टर_device(spi);

	वापस sd;
पूर्ण
EXPORT_SYMBOL_GPL(v4l2_spi_new_subdev);
