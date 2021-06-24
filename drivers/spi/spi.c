<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
// SPI init/core code
//
// Copyright (C) 2005 David Brownell
// Copyright (C) 2008 Secret Lab Technologies Ltd.

#समावेश <linux/kernel.h>
#समावेश <linux/device.h>
#समावेश <linux/init.h>
#समावेश <linux/cache.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/mutex.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/clk/clk-conf.h>
#समावेश <linux/slab.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/spi/spi-स्मृति.स>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/pm_करोमुख्य.h>
#समावेश <linux/property.h>
#समावेश <linux/export.h>
#समावेश <linux/sched/rt.h>
#समावेश <uapi/linux/sched/types.h>
#समावेश <linux/delay.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/ioport.h>
#समावेश <linux/acpi.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/idr.h>
#समावेश <linux/platक्रमm_data/x86/apple.h>

#घोषणा CREATE_TRACE_POINTS
#समावेश <trace/events/spi.h>
EXPORT_TRACEPOINT_SYMBOL(spi_transfer_start);
EXPORT_TRACEPOINT_SYMBOL(spi_transfer_stop);

#समावेश "internals.h"

अटल DEFINE_IDR(spi_master_idr);

अटल व्योम spidev_release(काष्ठा device *dev)
अणु
	काष्ठा spi_device	*spi = to_spi_device(dev);

	spi_controller_put(spi->controller);
	kमुक्त(spi->driver_override);
	kमुक्त(spi);
पूर्ण

अटल sमाप_प्रकार
modalias_show(काष्ठा device *dev, काष्ठा device_attribute *a, अक्षर *buf)
अणु
	स्थिर काष्ठा spi_device	*spi = to_spi_device(dev);
	पूर्णांक len;

	len = acpi_device_modalias(dev, buf, PAGE_SIZE - 1);
	अगर (len != -ENODEV)
		वापस len;

	वापस प्र_लिखो(buf, "%s%s\n", SPI_MODULE_PREFIX, spi->modalias);
पूर्ण
अटल DEVICE_ATTR_RO(modalias);

अटल sमाप_प्रकार driver_override_store(काष्ठा device *dev,
				     काष्ठा device_attribute *a,
				     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा spi_device *spi = to_spi_device(dev);
	स्थिर अक्षर *end = स_प्रथम(buf, '\n', count);
	स्थिर माप_प्रकार len = end ? end - buf : count;
	स्थिर अक्षर *driver_override, *old;

	/* We need to keep extra room क्रम a newline when displaying value */
	अगर (len >= (PAGE_SIZE - 1))
		वापस -EINVAL;

	driver_override = kstrndup(buf, len, GFP_KERNEL);
	अगर (!driver_override)
		वापस -ENOMEM;

	device_lock(dev);
	old = spi->driver_override;
	अगर (len) अणु
		spi->driver_override = driver_override;
	पूर्ण अन्यथा अणु
		/* Empty string, disable driver override */
		spi->driver_override = शून्य;
		kमुक्त(driver_override);
	पूर्ण
	device_unlock(dev);
	kमुक्त(old);

	वापस count;
पूर्ण

अटल sमाप_प्रकार driver_override_show(काष्ठा device *dev,
				    काष्ठा device_attribute *a, अक्षर *buf)
अणु
	स्थिर काष्ठा spi_device *spi = to_spi_device(dev);
	sमाप_प्रकार len;

	device_lock(dev);
	len = snम_लिखो(buf, PAGE_SIZE, "%s\n", spi->driver_override ? : "");
	device_unlock(dev);
	वापस len;
पूर्ण
अटल DEVICE_ATTR_RW(driver_override);

#घोषणा SPI_STATISTICS_ATTRS(field, file)				\
अटल sमाप_प्रकार spi_controller_##field##_show(काष्ठा device *dev,	\
					     काष्ठा device_attribute *attr, \
					     अक्षर *buf)			\
अणु									\
	काष्ठा spi_controller *ctlr = container_of(dev,			\
					 काष्ठा spi_controller, dev);	\
	वापस spi_statistics_##field##_show(&ctlr->statistics, buf);	\
पूर्ण									\
अटल काष्ठा device_attribute dev_attr_spi_controller_##field = अणु	\
	.attr = अणु .name = file, .mode = 0444 पूर्ण,				\
	.show = spi_controller_##field##_show,				\
पूर्ण;									\
अटल sमाप_प्रकार spi_device_##field##_show(काष्ठा device *dev,		\
					 काष्ठा device_attribute *attr,	\
					अक्षर *buf)			\
अणु									\
	काष्ठा spi_device *spi = to_spi_device(dev);			\
	वापस spi_statistics_##field##_show(&spi->statistics, buf);	\
पूर्ण									\
अटल काष्ठा device_attribute dev_attr_spi_device_##field = अणु		\
	.attr = अणु .name = file, .mode = 0444 पूर्ण,				\
	.show = spi_device_##field##_show,				\
पूर्ण

#घोषणा SPI_STATISTICS_SHOW_NAME(name, file, field, क्रमmat_string)	\
अटल sमाप_प्रकार spi_statistics_##name##_show(काष्ठा spi_statistics *stat, \
					    अक्षर *buf)			\
अणु									\
	अचिन्हित दीर्घ flags;						\
	sमाप_प्रकार len;							\
	spin_lock_irqsave(&stat->lock, flags);				\
	len = प्र_लिखो(buf, क्रमmat_string, stat->field);			\
	spin_unlock_irqrestore(&stat->lock, flags);			\
	वापस len;							\
पूर्ण									\
SPI_STATISTICS_ATTRS(name, file)

#घोषणा SPI_STATISTICS_SHOW(field, क्रमmat_string)			\
	SPI_STATISTICS_SHOW_NAME(field, __stringअगरy(field),		\
				 field, क्रमmat_string)

SPI_STATISTICS_SHOW(messages, "%lu");
SPI_STATISTICS_SHOW(transfers, "%lu");
SPI_STATISTICS_SHOW(errors, "%lu");
SPI_STATISTICS_SHOW(समयकरोut, "%lu");

SPI_STATISTICS_SHOW(spi_sync, "%lu");
SPI_STATISTICS_SHOW(spi_sync_immediate, "%lu");
SPI_STATISTICS_SHOW(spi_async, "%lu");

SPI_STATISTICS_SHOW(bytes, "%llu");
SPI_STATISTICS_SHOW(bytes_rx, "%llu");
SPI_STATISTICS_SHOW(bytes_tx, "%llu");

#घोषणा SPI_STATISTICS_TRANSFER_BYTES_HISTO(index, number)		\
	SPI_STATISTICS_SHOW_NAME(transfer_bytes_histo##index,		\
				 "transfer_bytes_histo_" number,	\
				 transfer_bytes_histo[index],  "%lu")
SPI_STATISTICS_TRANSFER_BYTES_HISTO(0,  "0-1");
SPI_STATISTICS_TRANSFER_BYTES_HISTO(1,  "2-3");
SPI_STATISTICS_TRANSFER_BYTES_HISTO(2,  "4-7");
SPI_STATISTICS_TRANSFER_BYTES_HISTO(3,  "8-15");
SPI_STATISTICS_TRANSFER_BYTES_HISTO(4,  "16-31");
SPI_STATISTICS_TRANSFER_BYTES_HISTO(5,  "32-63");
SPI_STATISTICS_TRANSFER_BYTES_HISTO(6,  "64-127");
SPI_STATISTICS_TRANSFER_BYTES_HISTO(7,  "128-255");
SPI_STATISTICS_TRANSFER_BYTES_HISTO(8,  "256-511");
SPI_STATISTICS_TRANSFER_BYTES_HISTO(9,  "512-1023");
SPI_STATISTICS_TRANSFER_BYTES_HISTO(10, "1024-2047");
SPI_STATISTICS_TRANSFER_BYTES_HISTO(11, "2048-4095");
SPI_STATISTICS_TRANSFER_BYTES_HISTO(12, "4096-8191");
SPI_STATISTICS_TRANSFER_BYTES_HISTO(13, "8192-16383");
SPI_STATISTICS_TRANSFER_BYTES_HISTO(14, "16384-32767");
SPI_STATISTICS_TRANSFER_BYTES_HISTO(15, "32768-65535");
SPI_STATISTICS_TRANSFER_BYTES_HISTO(16, "65536+");

SPI_STATISTICS_SHOW(transfers_split_maxsize, "%lu");

अटल काष्ठा attribute *spi_dev_attrs[] = अणु
	&dev_attr_modalias.attr,
	&dev_attr_driver_override.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group spi_dev_group = अणु
	.attrs  = spi_dev_attrs,
पूर्ण;

अटल काष्ठा attribute *spi_device_statistics_attrs[] = अणु
	&dev_attr_spi_device_messages.attr,
	&dev_attr_spi_device_transfers.attr,
	&dev_attr_spi_device_errors.attr,
	&dev_attr_spi_device_समयकरोut.attr,
	&dev_attr_spi_device_spi_sync.attr,
	&dev_attr_spi_device_spi_sync_immediate.attr,
	&dev_attr_spi_device_spi_async.attr,
	&dev_attr_spi_device_bytes.attr,
	&dev_attr_spi_device_bytes_rx.attr,
	&dev_attr_spi_device_bytes_tx.attr,
	&dev_attr_spi_device_transfer_bytes_histo0.attr,
	&dev_attr_spi_device_transfer_bytes_histo1.attr,
	&dev_attr_spi_device_transfer_bytes_histo2.attr,
	&dev_attr_spi_device_transfer_bytes_histo3.attr,
	&dev_attr_spi_device_transfer_bytes_histo4.attr,
	&dev_attr_spi_device_transfer_bytes_histo5.attr,
	&dev_attr_spi_device_transfer_bytes_histo6.attr,
	&dev_attr_spi_device_transfer_bytes_histo7.attr,
	&dev_attr_spi_device_transfer_bytes_histo8.attr,
	&dev_attr_spi_device_transfer_bytes_histo9.attr,
	&dev_attr_spi_device_transfer_bytes_histo10.attr,
	&dev_attr_spi_device_transfer_bytes_histo11.attr,
	&dev_attr_spi_device_transfer_bytes_histo12.attr,
	&dev_attr_spi_device_transfer_bytes_histo13.attr,
	&dev_attr_spi_device_transfer_bytes_histo14.attr,
	&dev_attr_spi_device_transfer_bytes_histo15.attr,
	&dev_attr_spi_device_transfer_bytes_histo16.attr,
	&dev_attr_spi_device_transfers_split_maxsize.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group spi_device_statistics_group = अणु
	.name  = "statistics",
	.attrs  = spi_device_statistics_attrs,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *spi_dev_groups[] = अणु
	&spi_dev_group,
	&spi_device_statistics_group,
	शून्य,
पूर्ण;

अटल काष्ठा attribute *spi_controller_statistics_attrs[] = अणु
	&dev_attr_spi_controller_messages.attr,
	&dev_attr_spi_controller_transfers.attr,
	&dev_attr_spi_controller_errors.attr,
	&dev_attr_spi_controller_समयकरोut.attr,
	&dev_attr_spi_controller_spi_sync.attr,
	&dev_attr_spi_controller_spi_sync_immediate.attr,
	&dev_attr_spi_controller_spi_async.attr,
	&dev_attr_spi_controller_bytes.attr,
	&dev_attr_spi_controller_bytes_rx.attr,
	&dev_attr_spi_controller_bytes_tx.attr,
	&dev_attr_spi_controller_transfer_bytes_histo0.attr,
	&dev_attr_spi_controller_transfer_bytes_histo1.attr,
	&dev_attr_spi_controller_transfer_bytes_histo2.attr,
	&dev_attr_spi_controller_transfer_bytes_histo3.attr,
	&dev_attr_spi_controller_transfer_bytes_histo4.attr,
	&dev_attr_spi_controller_transfer_bytes_histo5.attr,
	&dev_attr_spi_controller_transfer_bytes_histo6.attr,
	&dev_attr_spi_controller_transfer_bytes_histo7.attr,
	&dev_attr_spi_controller_transfer_bytes_histo8.attr,
	&dev_attr_spi_controller_transfer_bytes_histo9.attr,
	&dev_attr_spi_controller_transfer_bytes_histo10.attr,
	&dev_attr_spi_controller_transfer_bytes_histo11.attr,
	&dev_attr_spi_controller_transfer_bytes_histo12.attr,
	&dev_attr_spi_controller_transfer_bytes_histo13.attr,
	&dev_attr_spi_controller_transfer_bytes_histo14.attr,
	&dev_attr_spi_controller_transfer_bytes_histo15.attr,
	&dev_attr_spi_controller_transfer_bytes_histo16.attr,
	&dev_attr_spi_controller_transfers_split_maxsize.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group spi_controller_statistics_group = अणु
	.name  = "statistics",
	.attrs  = spi_controller_statistics_attrs,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *spi_master_groups[] = अणु
	&spi_controller_statistics_group,
	शून्य,
पूर्ण;

व्योम spi_statistics_add_transfer_stats(काष्ठा spi_statistics *stats,
				       काष्ठा spi_transfer *xfer,
				       काष्ठा spi_controller *ctlr)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक l2len = min(fls(xfer->len), SPI_STATISTICS_HISTO_SIZE) - 1;

	अगर (l2len < 0)
		l2len = 0;

	spin_lock_irqsave(&stats->lock, flags);

	stats->transfers++;
	stats->transfer_bytes_histo[l2len]++;

	stats->bytes += xfer->len;
	अगर ((xfer->tx_buf) &&
	    (xfer->tx_buf != ctlr->dummy_tx))
		stats->bytes_tx += xfer->len;
	अगर ((xfer->rx_buf) &&
	    (xfer->rx_buf != ctlr->dummy_rx))
		stats->bytes_rx += xfer->len;

	spin_unlock_irqrestore(&stats->lock, flags);
पूर्ण
EXPORT_SYMBOL_GPL(spi_statistics_add_transfer_stats);

/* modalias support makes "modprobe $MODALIAS" new-style hotplug work,
 * and the sysfs version makes coldplug work too.
 */

अटल स्थिर काष्ठा spi_device_id *spi_match_id(स्थिर काष्ठा spi_device_id *id,
						स्थिर काष्ठा spi_device *sdev)
अणु
	जबतक (id->name[0]) अणु
		अगर (!म_भेद(sdev->modalias, id->name))
			वापस id;
		id++;
	पूर्ण
	वापस शून्य;
पूर्ण

स्थिर काष्ठा spi_device_id *spi_get_device_id(स्थिर काष्ठा spi_device *sdev)
अणु
	स्थिर काष्ठा spi_driver *sdrv = to_spi_driver(sdev->dev.driver);

	वापस spi_match_id(sdrv->id_table, sdev);
पूर्ण
EXPORT_SYMBOL_GPL(spi_get_device_id);

अटल पूर्णांक spi_match_device(काष्ठा device *dev, काष्ठा device_driver *drv)
अणु
	स्थिर काष्ठा spi_device	*spi = to_spi_device(dev);
	स्थिर काष्ठा spi_driver	*sdrv = to_spi_driver(drv);

	/* Check override first, and अगर set, only use the named driver */
	अगर (spi->driver_override)
		वापस म_भेद(spi->driver_override, drv->name) == 0;

	/* Attempt an OF style match */
	अगर (of_driver_match_device(dev, drv))
		वापस 1;

	/* Then try ACPI */
	अगर (acpi_driver_match_device(dev, drv))
		वापस 1;

	अगर (sdrv->id_table)
		वापस !!spi_match_id(sdrv->id_table, spi);

	वापस म_भेद(spi->modalias, drv->name) == 0;
पूर्ण

अटल पूर्णांक spi_uevent(काष्ठा device *dev, काष्ठा kobj_uevent_env *env)
अणु
	स्थिर काष्ठा spi_device		*spi = to_spi_device(dev);
	पूर्णांक rc;

	rc = acpi_device_uevent_modalias(dev, env);
	अगर (rc != -ENODEV)
		वापस rc;

	वापस add_uevent_var(env, "MODALIAS=%s%s", SPI_MODULE_PREFIX, spi->modalias);
पूर्ण

अटल पूर्णांक spi_probe(काष्ठा device *dev)
अणु
	स्थिर काष्ठा spi_driver		*sdrv = to_spi_driver(dev->driver);
	काष्ठा spi_device		*spi = to_spi_device(dev);
	पूर्णांक ret;

	ret = of_clk_set_शेषs(dev->of_node, false);
	अगर (ret)
		वापस ret;

	अगर (dev->of_node) अणु
		spi->irq = of_irq_get(dev->of_node, 0);
		अगर (spi->irq == -EPROBE_DEFER)
			वापस -EPROBE_DEFER;
		अगर (spi->irq < 0)
			spi->irq = 0;
	पूर्ण

	ret = dev_pm_करोमुख्य_attach(dev, true);
	अगर (ret)
		वापस ret;

	अगर (sdrv->probe) अणु
		ret = sdrv->probe(spi);
		अगर (ret)
			dev_pm_करोमुख्य_detach(dev, true);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक spi_हटाओ(काष्ठा device *dev)
अणु
	स्थिर काष्ठा spi_driver		*sdrv = to_spi_driver(dev->driver);

	अगर (sdrv->हटाओ) अणु
		पूर्णांक ret;

		ret = sdrv->हटाओ(to_spi_device(dev));
		अगर (ret)
			dev_warn(dev,
				 "Failed to unbind driver (%pe), ignoring\n",
				 ERR_PTR(ret));
	पूर्ण

	dev_pm_करोमुख्य_detach(dev, true);

	वापस 0;
पूर्ण

अटल व्योम spi_shutकरोwn(काष्ठा device *dev)
अणु
	अगर (dev->driver) अणु
		स्थिर काष्ठा spi_driver	*sdrv = to_spi_driver(dev->driver);

		अगर (sdrv->shutकरोwn)
			sdrv->shutकरोwn(to_spi_device(dev));
	पूर्ण
पूर्ण

काष्ठा bus_type spi_bus_type = अणु
	.name		= "spi",
	.dev_groups	= spi_dev_groups,
	.match		= spi_match_device,
	.uevent		= spi_uevent,
	.probe		= spi_probe,
	.हटाओ		= spi_हटाओ,
	.shutकरोwn	= spi_shutकरोwn,
पूर्ण;
EXPORT_SYMBOL_GPL(spi_bus_type);

/**
 * __spi_रेजिस्टर_driver - रेजिस्टर a SPI driver
 * @owner: owner module of the driver to रेजिस्टर
 * @sdrv: the driver to रेजिस्टर
 * Context: can sleep
 *
 * Return: zero on success, अन्यथा a negative error code.
 */
पूर्णांक __spi_रेजिस्टर_driver(काष्ठा module *owner, काष्ठा spi_driver *sdrv)
अणु
	sdrv->driver.owner = owner;
	sdrv->driver.bus = &spi_bus_type;
	वापस driver_रेजिस्टर(&sdrv->driver);
पूर्ण
EXPORT_SYMBOL_GPL(__spi_रेजिस्टर_driver);

/*-------------------------------------------------------------------------*/

/* SPI devices should normally not be created by SPI device drivers; that
 * would make them board-specअगरic.  Similarly with SPI controller drivers.
 * Device registration normally goes पूर्णांकo like arch/.../mach.../board-YYY.c
 * with other पढ़ोonly (flashable) inक्रमmation about मुख्यboard devices.
 */

काष्ठा boardinfo अणु
	काष्ठा list_head	list;
	काष्ठा spi_board_info	board_info;
पूर्ण;

अटल LIST_HEAD(board_list);
अटल LIST_HEAD(spi_controller_list);

/*
 * Used to protect add/del operation क्रम board_info list and
 * spi_controller list, and their matching process
 * also used to protect object of type काष्ठा idr
 */
अटल DEFINE_MUTEX(board_lock);

/*
 * Prevents addition of devices with same chip select and
 * addition of devices below an unरेजिस्टरing controller.
 */
अटल DEFINE_MUTEX(spi_add_lock);

/**
 * spi_alloc_device - Allocate a new SPI device
 * @ctlr: Controller to which device is connected
 * Context: can sleep
 *
 * Allows a driver to allocate and initialize a spi_device without
 * रेजिस्टरing it immediately.  This allows a driver to directly
 * fill the spi_device with device parameters beक्रमe calling
 * spi_add_device() on it.
 *
 * Caller is responsible to call spi_add_device() on the वापसed
 * spi_device काष्ठाure to add it to the SPI controller.  If the caller
 * needs to discard the spi_device without adding it, then it should
 * call spi_dev_put() on it.
 *
 * Return: a poपूर्णांकer to the new device, or शून्य.
 */
काष्ठा spi_device *spi_alloc_device(काष्ठा spi_controller *ctlr)
अणु
	काष्ठा spi_device	*spi;

	अगर (!spi_controller_get(ctlr))
		वापस शून्य;

	spi = kzalloc(माप(*spi), GFP_KERNEL);
	अगर (!spi) अणु
		spi_controller_put(ctlr);
		वापस शून्य;
	पूर्ण

	spi->master = spi->controller = ctlr;
	spi->dev.parent = &ctlr->dev;
	spi->dev.bus = &spi_bus_type;
	spi->dev.release = spidev_release;
	spi->cs_gpio = -ENOENT;
	spi->mode = ctlr->buswidth_override_bits;

	spin_lock_init(&spi->statistics.lock);

	device_initialize(&spi->dev);
	वापस spi;
पूर्ण
EXPORT_SYMBOL_GPL(spi_alloc_device);

अटल व्योम spi_dev_set_name(काष्ठा spi_device *spi)
अणु
	काष्ठा acpi_device *adev = ACPI_COMPANION(&spi->dev);

	अगर (adev) अणु
		dev_set_name(&spi->dev, "spi-%s", acpi_dev_name(adev));
		वापस;
	पूर्ण

	dev_set_name(&spi->dev, "%s.%u", dev_name(&spi->controller->dev),
		     spi->chip_select);
पूर्ण

अटल पूर्णांक spi_dev_check(काष्ठा device *dev, व्योम *data)
अणु
	काष्ठा spi_device *spi = to_spi_device(dev);
	काष्ठा spi_device *new_spi = data;

	अगर (spi->controller == new_spi->controller &&
	    spi->chip_select == new_spi->chip_select)
		वापस -EBUSY;
	वापस 0;
पूर्ण

अटल व्योम spi_cleanup(काष्ठा spi_device *spi)
अणु
	अगर (spi->controller->cleanup)
		spi->controller->cleanup(spi);
पूर्ण

/**
 * spi_add_device - Add spi_device allocated with spi_alloc_device
 * @spi: spi_device to रेजिस्टर
 *
 * Companion function to spi_alloc_device.  Devices allocated with
 * spi_alloc_device can be added onto the spi bus with this function.
 *
 * Return: 0 on success; negative त्रुटि_सं on failure
 */
पूर्णांक spi_add_device(काष्ठा spi_device *spi)
अणु
	काष्ठा spi_controller *ctlr = spi->controller;
	काष्ठा device *dev = ctlr->dev.parent;
	पूर्णांक status;

	/* Chipselects are numbered 0..max; validate. */
	अगर (spi->chip_select >= ctlr->num_chipselect) अणु
		dev_err(dev, "cs%d >= max %d\n", spi->chip_select,
			ctlr->num_chipselect);
		वापस -EINVAL;
	पूर्ण

	/* Set the bus ID string */
	spi_dev_set_name(spi);

	/* We need to make sure there's no other device with this
	 * chipselect **BEFORE** we call setup(), अन्यथा we'll trash
	 * its configuration.  Lock against concurrent add() calls.
	 */
	mutex_lock(&spi_add_lock);

	status = bus_क्रम_each_dev(&spi_bus_type, शून्य, spi, spi_dev_check);
	अगर (status) अणु
		dev_err(dev, "chipselect %d already in use\n",
				spi->chip_select);
		जाओ करोne;
	पूर्ण

	/* Controller may unरेजिस्टर concurrently */
	अगर (IS_ENABLED(CONFIG_SPI_DYNAMIC) &&
	    !device_is_रेजिस्टरed(&ctlr->dev)) अणु
		status = -ENODEV;
		जाओ करोne;
	पूर्ण

	/* Descriptors take precedence */
	अगर (ctlr->cs_gpiods)
		spi->cs_gpiod = ctlr->cs_gpiods[spi->chip_select];
	अन्यथा अगर (ctlr->cs_gpios)
		spi->cs_gpio = ctlr->cs_gpios[spi->chip_select];

	/* Drivers may modअगरy this initial i/o setup, but will
	 * normally rely on the device being setup.  Devices
	 * using SPI_CS_HIGH can't coexist well otherwise...
	 */
	status = spi_setup(spi);
	अगर (status < 0) अणु
		dev_err(dev, "can't setup %s, status %d\n",
				dev_name(&spi->dev), status);
		जाओ करोne;
	पूर्ण

	/* Device may be bound to an active driver when this वापसs */
	status = device_add(&spi->dev);
	अगर (status < 0) अणु
		dev_err(dev, "can't add %s, status %d\n",
				dev_name(&spi->dev), status);
		spi_cleanup(spi);
	पूर्ण अन्यथा अणु
		dev_dbg(dev, "registered child %s\n", dev_name(&spi->dev));
	पूर्ण

करोne:
	mutex_unlock(&spi_add_lock);
	वापस status;
पूर्ण
EXPORT_SYMBOL_GPL(spi_add_device);

/**
 * spi_new_device - instantiate one new SPI device
 * @ctlr: Controller to which device is connected
 * @chip: Describes the SPI device
 * Context: can sleep
 *
 * On typical मुख्यboards, this is purely पूर्णांकernal; and it's not needed
 * after board init creates the hard-wired devices.  Some development
 * platक्रमms may not be able to use spi_रेजिस्टर_board_info though, and
 * this is exported so that क्रम example a USB or parport based adapter
 * driver could add devices (which it would learn about out-of-band).
 *
 * Return: the new device, or शून्य.
 */
काष्ठा spi_device *spi_new_device(काष्ठा spi_controller *ctlr,
				  काष्ठा spi_board_info *chip)
अणु
	काष्ठा spi_device	*proxy;
	पूर्णांक			status;

	/* NOTE:  caller did any chip->bus_num checks necessary.
	 *
	 * Also, unless we change the वापस value convention to use
	 * error-or-poपूर्णांकer (not शून्य-or-poपूर्णांकer), troubleshootability
	 * suggests syslogged diagnostics are best here (ugh).
	 */

	proxy = spi_alloc_device(ctlr);
	अगर (!proxy)
		वापस शून्य;

	WARN_ON(म_माप(chip->modalias) >= माप(proxy->modalias));

	proxy->chip_select = chip->chip_select;
	proxy->max_speed_hz = chip->max_speed_hz;
	proxy->mode = chip->mode;
	proxy->irq = chip->irq;
	strlcpy(proxy->modalias, chip->modalias, माप(proxy->modalias));
	proxy->dev.platक्रमm_data = (व्योम *) chip->platक्रमm_data;
	proxy->controller_data = chip->controller_data;
	proxy->controller_state = शून्य;

	अगर (chip->swnode) अणु
		status = device_add_software_node(&proxy->dev, chip->swnode);
		अगर (status) अणु
			dev_err(&ctlr->dev, "failed to add software node to '%s': %d\n",
				chip->modalias, status);
			जाओ err_dev_put;
		पूर्ण
	पूर्ण

	status = spi_add_device(proxy);
	अगर (status < 0)
		जाओ err_dev_put;

	वापस proxy;

err_dev_put:
	device_हटाओ_software_node(&proxy->dev);
	spi_dev_put(proxy);
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(spi_new_device);

/**
 * spi_unरेजिस्टर_device - unरेजिस्टर a single SPI device
 * @spi: spi_device to unरेजिस्टर
 *
 * Start making the passed SPI device vanish. Normally this would be handled
 * by spi_unरेजिस्टर_controller().
 */
व्योम spi_unरेजिस्टर_device(काष्ठा spi_device *spi)
अणु
	अगर (!spi)
		वापस;

	अगर (spi->dev.of_node) अणु
		of_node_clear_flag(spi->dev.of_node, OF_POPULATED);
		of_node_put(spi->dev.of_node);
	पूर्ण
	अगर (ACPI_COMPANION(&spi->dev))
		acpi_device_clear_क्रमागतerated(ACPI_COMPANION(&spi->dev));
	device_हटाओ_software_node(&spi->dev);
	device_del(&spi->dev);
	spi_cleanup(spi);
	put_device(&spi->dev);
पूर्ण
EXPORT_SYMBOL_GPL(spi_unरेजिस्टर_device);

अटल व्योम spi_match_controller_to_boardinfo(काष्ठा spi_controller *ctlr,
					      काष्ठा spi_board_info *bi)
अणु
	काष्ठा spi_device *dev;

	अगर (ctlr->bus_num != bi->bus_num)
		वापस;

	dev = spi_new_device(ctlr, bi);
	अगर (!dev)
		dev_err(ctlr->dev.parent, "can't create new device for %s\n",
			bi->modalias);
पूर्ण

/**
 * spi_रेजिस्टर_board_info - रेजिस्टर SPI devices क्रम a given board
 * @info: array of chip descriptors
 * @n: how many descriptors are provided
 * Context: can sleep
 *
 * Board-specअगरic early init code calls this (probably during arch_initcall)
 * with segments of the SPI device table.  Any device nodes are created later,
 * after the relevant parent SPI controller (bus_num) is defined.  We keep
 * this table of devices क्रमever, so that reloading a controller driver will
 * not make Linux क्रमget about these hard-wired devices.
 *
 * Other code can also call this, e.g. a particular add-on board might provide
 * SPI devices through its expansion connector, so code initializing that board
 * would naturally declare its SPI devices.
 *
 * The board info passed can safely be __initdata ... but be careful of
 * any embedded poपूर्णांकers (platक्रमm_data, etc), they're copied as-is.
 *
 * Return: zero on success, अन्यथा a negative error code.
 */
पूर्णांक spi_रेजिस्टर_board_info(काष्ठा spi_board_info स्थिर *info, अचिन्हित n)
अणु
	काष्ठा boardinfo *bi;
	पूर्णांक i;

	अगर (!n)
		वापस 0;

	bi = kसुस्मृति(n, माप(*bi), GFP_KERNEL);
	अगर (!bi)
		वापस -ENOMEM;

	क्रम (i = 0; i < n; i++, bi++, info++) अणु
		काष्ठा spi_controller *ctlr;

		स_नकल(&bi->board_info, info, माप(*info));

		mutex_lock(&board_lock);
		list_add_tail(&bi->list, &board_list);
		list_क्रम_each_entry(ctlr, &spi_controller_list, list)
			spi_match_controller_to_boardinfo(ctlr,
							  &bi->board_info);
		mutex_unlock(&board_lock);
	पूर्ण

	वापस 0;
पूर्ण

/*-------------------------------------------------------------------------*/

अटल व्योम spi_set_cs(काष्ठा spi_device *spi, bool enable, bool क्रमce)
अणु
	bool activate = enable;

	/*
	 * Aव्योम calling पूर्णांकo the driver (or करोing delays) अगर the chip select
	 * isn't actually changing from the last समय this was called.
	 */
	अगर (!क्रमce && (spi->controller->last_cs_enable == enable) &&
	    (spi->controller->last_cs_mode_high == (spi->mode & SPI_CS_HIGH)))
		वापस;

	spi->controller->last_cs_enable = enable;
	spi->controller->last_cs_mode_high = spi->mode & SPI_CS_HIGH;

	अगर (spi->cs_gpiod || gpio_is_valid(spi->cs_gpio) ||
	    !spi->controller->set_cs_timing) अणु
		अगर (activate)
			spi_delay_exec(&spi->controller->cs_setup, शून्य);
		अन्यथा
			spi_delay_exec(&spi->controller->cs_hold, शून्य);
	पूर्ण

	अगर (spi->mode & SPI_CS_HIGH)
		enable = !enable;

	अगर (spi->cs_gpiod || gpio_is_valid(spi->cs_gpio)) अणु
		अगर (!(spi->mode & SPI_NO_CS)) अणु
			अगर (spi->cs_gpiod) अणु
				/*
				 * Historically ACPI has no means of the GPIO polarity and
				 * thus the SPISerialBus() resource defines it on the per-chip
				 * basis. In order to aव्योम a chain of negations, the GPIO
				 * polarity is considered being Active High. Even क्रम the हालs
				 * when _DSD() is involved (in the updated versions of ACPI)
				 * the GPIO CS polarity must be defined Active High to aव्योम
				 * ambiguity. That's why we use enable, that takes SPI_CS_HIGH
				 * पूर्णांकo account.
				 */
				अगर (has_acpi_companion(&spi->dev))
					gpiod_set_value_cansleep(spi->cs_gpiod, !enable);
				अन्यथा
					/* Polarity handled by GPIO library */
					gpiod_set_value_cansleep(spi->cs_gpiod, activate);
			पूर्ण अन्यथा अणु
				/*
				 * invert the enable line, as active low is
				 * शेष क्रम SPI.
				 */
				gpio_set_value_cansleep(spi->cs_gpio, !enable);
			पूर्ण
		पूर्ण
		/* Some SPI masters need both GPIO CS & slave_select */
		अगर ((spi->controller->flags & SPI_MASTER_GPIO_SS) &&
		    spi->controller->set_cs)
			spi->controller->set_cs(spi, !enable);
	पूर्ण अन्यथा अगर (spi->controller->set_cs) अणु
		spi->controller->set_cs(spi, !enable);
	पूर्ण

	अगर (spi->cs_gpiod || gpio_is_valid(spi->cs_gpio) ||
	    !spi->controller->set_cs_timing) अणु
		अगर (!activate)
			spi_delay_exec(&spi->controller->cs_inactive, शून्य);
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_HAS_DMA
पूर्णांक spi_map_buf(काष्ठा spi_controller *ctlr, काष्ठा device *dev,
		काष्ठा sg_table *sgt, व्योम *buf, माप_प्रकार len,
		क्रमागत dma_data_direction dir)
अणु
	स्थिर bool vदो_स्मृतिed_buf = is_vदो_स्मृति_addr(buf);
	अचिन्हित पूर्णांक max_seg_size = dma_get_max_seg_size(dev);
#अगर_घोषित CONFIG_HIGHMEM
	स्थिर bool kmap_buf = ((अचिन्हित दीर्घ)buf >= PKMAP_BASE &&
				(अचिन्हित दीर्घ)buf < (PKMAP_BASE +
					(LAST_PKMAP * PAGE_SIZE)));
#अन्यथा
	स्थिर bool kmap_buf = false;
#पूर्ण_अगर
	पूर्णांक desc_len;
	पूर्णांक sgs;
	काष्ठा page *vm_page;
	काष्ठा scatterlist *sg;
	व्योम *sg_buf;
	माप_प्रकार min;
	पूर्णांक i, ret;

	अगर (vदो_स्मृतिed_buf || kmap_buf) अणु
		desc_len = min_t(पूर्णांक, max_seg_size, PAGE_SIZE);
		sgs = DIV_ROUND_UP(len + offset_in_page(buf), desc_len);
	पूर्ण अन्यथा अगर (virt_addr_valid(buf)) अणु
		desc_len = min_t(पूर्णांक, max_seg_size, ctlr->max_dma_len);
		sgs = DIV_ROUND_UP(len, desc_len);
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण

	ret = sg_alloc_table(sgt, sgs, GFP_KERNEL);
	अगर (ret != 0)
		वापस ret;

	sg = &sgt->sgl[0];
	क्रम (i = 0; i < sgs; i++) अणु

		अगर (vदो_स्मृतिed_buf || kmap_buf) अणु
			/*
			 * Next scatterlist entry size is the minimum between
			 * the desc_len and the reमुख्यing buffer length that
			 * fits in a page.
			 */
			min = min_t(माप_प्रकार, desc_len,
				    min_t(माप_प्रकार, len,
					  PAGE_SIZE - offset_in_page(buf)));
			अगर (vदो_स्मृतिed_buf)
				vm_page = vदो_स्मृति_to_page(buf);
			अन्यथा
				vm_page = kmap_to_page(buf);
			अगर (!vm_page) अणु
				sg_मुक्त_table(sgt);
				वापस -ENOMEM;
			पूर्ण
			sg_set_page(sg, vm_page,
				    min, offset_in_page(buf));
		पूर्ण अन्यथा अणु
			min = min_t(माप_प्रकार, len, desc_len);
			sg_buf = buf;
			sg_set_buf(sg, sg_buf, min);
		पूर्ण

		buf += min;
		len -= min;
		sg = sg_next(sg);
	पूर्ण

	ret = dma_map_sg(dev, sgt->sgl, sgt->nents, dir);
	अगर (!ret)
		ret = -ENOMEM;
	अगर (ret < 0) अणु
		sg_मुक्त_table(sgt);
		वापस ret;
	पूर्ण

	sgt->nents = ret;

	वापस 0;
पूर्ण

व्योम spi_unmap_buf(काष्ठा spi_controller *ctlr, काष्ठा device *dev,
		   काष्ठा sg_table *sgt, क्रमागत dma_data_direction dir)
अणु
	अगर (sgt->orig_nents) अणु
		dma_unmap_sg(dev, sgt->sgl, sgt->orig_nents, dir);
		sg_मुक्त_table(sgt);
	पूर्ण
पूर्ण

अटल पूर्णांक __spi_map_msg(काष्ठा spi_controller *ctlr, काष्ठा spi_message *msg)
अणु
	काष्ठा device *tx_dev, *rx_dev;
	काष्ठा spi_transfer *xfer;
	पूर्णांक ret;

	अगर (!ctlr->can_dma)
		वापस 0;

	अगर (ctlr->dma_tx)
		tx_dev = ctlr->dma_tx->device->dev;
	अन्यथा
		tx_dev = ctlr->dev.parent;

	अगर (ctlr->dma_rx)
		rx_dev = ctlr->dma_rx->device->dev;
	अन्यथा
		rx_dev = ctlr->dev.parent;

	list_क्रम_each_entry(xfer, &msg->transfers, transfer_list) अणु
		अगर (!ctlr->can_dma(ctlr, msg->spi, xfer))
			जारी;

		अगर (xfer->tx_buf != शून्य) अणु
			ret = spi_map_buf(ctlr, tx_dev, &xfer->tx_sg,
					  (व्योम *)xfer->tx_buf, xfer->len,
					  DMA_TO_DEVICE);
			अगर (ret != 0)
				वापस ret;
		पूर्ण

		अगर (xfer->rx_buf != शून्य) अणु
			ret = spi_map_buf(ctlr, rx_dev, &xfer->rx_sg,
					  xfer->rx_buf, xfer->len,
					  DMA_FROM_DEVICE);
			अगर (ret != 0) अणु
				spi_unmap_buf(ctlr, tx_dev, &xfer->tx_sg,
					      DMA_TO_DEVICE);
				वापस ret;
			पूर्ण
		पूर्ण
	पूर्ण

	ctlr->cur_msg_mapped = true;

	वापस 0;
पूर्ण

अटल पूर्णांक __spi_unmap_msg(काष्ठा spi_controller *ctlr, काष्ठा spi_message *msg)
अणु
	काष्ठा spi_transfer *xfer;
	काष्ठा device *tx_dev, *rx_dev;

	अगर (!ctlr->cur_msg_mapped || !ctlr->can_dma)
		वापस 0;

	अगर (ctlr->dma_tx)
		tx_dev = ctlr->dma_tx->device->dev;
	अन्यथा
		tx_dev = ctlr->dev.parent;

	अगर (ctlr->dma_rx)
		rx_dev = ctlr->dma_rx->device->dev;
	अन्यथा
		rx_dev = ctlr->dev.parent;

	list_क्रम_each_entry(xfer, &msg->transfers, transfer_list) अणु
		अगर (!ctlr->can_dma(ctlr, msg->spi, xfer))
			जारी;

		spi_unmap_buf(ctlr, rx_dev, &xfer->rx_sg, DMA_FROM_DEVICE);
		spi_unmap_buf(ctlr, tx_dev, &xfer->tx_sg, DMA_TO_DEVICE);
	पूर्ण

	ctlr->cur_msg_mapped = false;

	वापस 0;
पूर्ण
#अन्यथा /* !CONFIG_HAS_DMA */
अटल अंतरभूत पूर्णांक __spi_map_msg(काष्ठा spi_controller *ctlr,
				काष्ठा spi_message *msg)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक __spi_unmap_msg(काष्ठा spi_controller *ctlr,
				  काष्ठा spi_message *msg)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर /* !CONFIG_HAS_DMA */

अटल अंतरभूत पूर्णांक spi_unmap_msg(काष्ठा spi_controller *ctlr,
				काष्ठा spi_message *msg)
अणु
	काष्ठा spi_transfer *xfer;

	list_क्रम_each_entry(xfer, &msg->transfers, transfer_list) अणु
		/*
		 * Restore the original value of tx_buf or rx_buf अगर they are
		 * शून्य.
		 */
		अगर (xfer->tx_buf == ctlr->dummy_tx)
			xfer->tx_buf = शून्य;
		अगर (xfer->rx_buf == ctlr->dummy_rx)
			xfer->rx_buf = शून्य;
	पूर्ण

	वापस __spi_unmap_msg(ctlr, msg);
पूर्ण

अटल पूर्णांक spi_map_msg(काष्ठा spi_controller *ctlr, काष्ठा spi_message *msg)
अणु
	काष्ठा spi_transfer *xfer;
	व्योम *पंचांगp;
	अचिन्हित पूर्णांक max_tx, max_rx;

	अगर ((ctlr->flags & (SPI_CONTROLLER_MUST_RX | SPI_CONTROLLER_MUST_TX))
		&& !(msg->spi->mode & SPI_3WIRE)) अणु
		max_tx = 0;
		max_rx = 0;

		list_क्रम_each_entry(xfer, &msg->transfers, transfer_list) अणु
			अगर ((ctlr->flags & SPI_CONTROLLER_MUST_TX) &&
			    !xfer->tx_buf)
				max_tx = max(xfer->len, max_tx);
			अगर ((ctlr->flags & SPI_CONTROLLER_MUST_RX) &&
			    !xfer->rx_buf)
				max_rx = max(xfer->len, max_rx);
		पूर्ण

		अगर (max_tx) अणु
			पंचांगp = kपुनः_स्मृति(ctlr->dummy_tx, max_tx,
				       GFP_KERNEL | GFP_DMA);
			अगर (!पंचांगp)
				वापस -ENOMEM;
			ctlr->dummy_tx = पंचांगp;
			स_रखो(पंचांगp, 0, max_tx);
		पूर्ण

		अगर (max_rx) अणु
			पंचांगp = kपुनः_स्मृति(ctlr->dummy_rx, max_rx,
				       GFP_KERNEL | GFP_DMA);
			अगर (!पंचांगp)
				वापस -ENOMEM;
			ctlr->dummy_rx = पंचांगp;
		पूर्ण

		अगर (max_tx || max_rx) अणु
			list_क्रम_each_entry(xfer, &msg->transfers,
					    transfer_list) अणु
				अगर (!xfer->len)
					जारी;
				अगर (!xfer->tx_buf)
					xfer->tx_buf = ctlr->dummy_tx;
				अगर (!xfer->rx_buf)
					xfer->rx_buf = ctlr->dummy_rx;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस __spi_map_msg(ctlr, msg);
पूर्ण

अटल पूर्णांक spi_transfer_रुको(काष्ठा spi_controller *ctlr,
			     काष्ठा spi_message *msg,
			     काष्ठा spi_transfer *xfer)
अणु
	काष्ठा spi_statistics *staपंचांग = &ctlr->statistics;
	काष्ठा spi_statistics *stats = &msg->spi->statistics;
	u32 speed_hz = xfer->speed_hz;
	अचिन्हित दीर्घ दीर्घ ms;

	अगर (spi_controller_is_slave(ctlr)) अणु
		अगर (रुको_क्रम_completion_पूर्णांकerruptible(&ctlr->xfer_completion)) अणु
			dev_dbg(&msg->spi->dev, "SPI transfer interrupted\n");
			वापस -EINTR;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (!speed_hz)
			speed_hz = 100000;

		ms = 8LL * 1000LL * xfer->len;
		करो_भाग(ms, speed_hz);
		ms += ms + 200; /* some tolerance */

		अगर (ms > अच_पूर्णांक_उच्च)
			ms = अच_पूर्णांक_उच्च;

		ms = रुको_क्रम_completion_समयout(&ctlr->xfer_completion,
						 msecs_to_jअगरfies(ms));

		अगर (ms == 0) अणु
			SPI_STATISTICS_INCREMENT_FIELD(staपंचांग, समयकरोut);
			SPI_STATISTICS_INCREMENT_FIELD(stats, समयकरोut);
			dev_err(&msg->spi->dev,
				"SPI transfer timed out\n");
			वापस -ETIMEDOUT;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम _spi_transfer_delay_ns(u32 ns)
अणु
	अगर (!ns)
		वापस;
	अगर (ns <= 1000) अणु
		ndelay(ns);
	पूर्ण अन्यथा अणु
		u32 us = DIV_ROUND_UP(ns, 1000);

		अगर (us <= 10)
			udelay(us);
		अन्यथा
			usleep_range(us, us + DIV_ROUND_UP(us, 10));
	पूर्ण
पूर्ण

पूर्णांक spi_delay_to_ns(काष्ठा spi_delay *_delay, काष्ठा spi_transfer *xfer)
अणु
	u32 delay = _delay->value;
	u32 unit = _delay->unit;
	u32 hz;

	अगर (!delay)
		वापस 0;

	चयन (unit) अणु
	हाल SPI_DELAY_UNIT_USECS:
		delay *= 1000;
		अवरोध;
	हाल SPI_DELAY_UNIT_NSECS: /* nothing to करो here */
		अवरोध;
	हाल SPI_DELAY_UNIT_SCK:
		/* घड़ी cycles need to be obtained from spi_transfer */
		अगर (!xfer)
			वापस -EINVAL;
		/* अगर there is no effective speed know, then approximate
		 * by underestimating with half the requested hz
		 */
		hz = xfer->effective_speed_hz ?: xfer->speed_hz / 2;
		अगर (!hz)
			वापस -EINVAL;
		delay *= DIV_ROUND_UP(1000000000, hz);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस delay;
पूर्ण
EXPORT_SYMBOL_GPL(spi_delay_to_ns);

पूर्णांक spi_delay_exec(काष्ठा spi_delay *_delay, काष्ठा spi_transfer *xfer)
अणु
	पूर्णांक delay;

	might_sleep();

	अगर (!_delay)
		वापस -EINVAL;

	delay = spi_delay_to_ns(_delay, xfer);
	अगर (delay < 0)
		वापस delay;

	_spi_transfer_delay_ns(delay);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(spi_delay_exec);

अटल व्योम _spi_transfer_cs_change_delay(काष्ठा spi_message *msg,
					  काष्ठा spi_transfer *xfer)
अणु
	u32 delay = xfer->cs_change_delay.value;
	u32 unit = xfer->cs_change_delay.unit;
	पूर्णांक ret;

	/* वापस early on "fast" mode - क्रम everything but USECS */
	अगर (!delay) अणु
		अगर (unit == SPI_DELAY_UNIT_USECS)
			_spi_transfer_delay_ns(10000);
		वापस;
	पूर्ण

	ret = spi_delay_exec(&xfer->cs_change_delay, xfer);
	अगर (ret) अणु
		dev_err_once(&msg->spi->dev,
			     "Use of unsupported delay unit %i, using default of 10us\n",
			     unit);
		_spi_transfer_delay_ns(10000);
	पूर्ण
पूर्ण

/*
 * spi_transfer_one_message - Default implementation of transfer_one_message()
 *
 * This is a standard implementation of transfer_one_message() क्रम
 * drivers which implement a transfer_one() operation.  It provides
 * standard handling of delays and chip select management.
 */
अटल पूर्णांक spi_transfer_one_message(काष्ठा spi_controller *ctlr,
				    काष्ठा spi_message *msg)
अणु
	काष्ठा spi_transfer *xfer;
	bool keep_cs = false;
	पूर्णांक ret = 0;
	काष्ठा spi_statistics *staपंचांग = &ctlr->statistics;
	काष्ठा spi_statistics *stats = &msg->spi->statistics;

	spi_set_cs(msg->spi, true, false);

	SPI_STATISTICS_INCREMENT_FIELD(staपंचांग, messages);
	SPI_STATISTICS_INCREMENT_FIELD(stats, messages);

	list_क्रम_each_entry(xfer, &msg->transfers, transfer_list) अणु
		trace_spi_transfer_start(msg, xfer);

		spi_statistics_add_transfer_stats(staपंचांग, xfer, ctlr);
		spi_statistics_add_transfer_stats(stats, xfer, ctlr);

		अगर (!ctlr->ptp_sts_supported) अणु
			xfer->ptp_sts_word_pre = 0;
			ptp_पढ़ो_प्रणाली_prets(xfer->ptp_sts);
		पूर्ण

		अगर ((xfer->tx_buf || xfer->rx_buf) && xfer->len) अणु
			reinit_completion(&ctlr->xfer_completion);

fallback_pio:
			ret = ctlr->transfer_one(ctlr, msg->spi, xfer);
			अगर (ret < 0) अणु
				अगर (ctlr->cur_msg_mapped &&
				   (xfer->error & SPI_TRANS_FAIL_NO_START)) अणु
					__spi_unmap_msg(ctlr, msg);
					ctlr->fallback = true;
					xfer->error &= ~SPI_TRANS_FAIL_NO_START;
					जाओ fallback_pio;
				पूर्ण

				SPI_STATISTICS_INCREMENT_FIELD(staपंचांग,
							       errors);
				SPI_STATISTICS_INCREMENT_FIELD(stats,
							       errors);
				dev_err(&msg->spi->dev,
					"SPI transfer failed: %d\n", ret);
				जाओ out;
			पूर्ण

			अगर (ret > 0) अणु
				ret = spi_transfer_रुको(ctlr, msg, xfer);
				अगर (ret < 0)
					msg->status = ret;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (xfer->len)
				dev_err(&msg->spi->dev,
					"Bufferless transfer has length %u\n",
					xfer->len);
		पूर्ण

		अगर (!ctlr->ptp_sts_supported) अणु
			ptp_पढ़ो_प्रणाली_postts(xfer->ptp_sts);
			xfer->ptp_sts_word_post = xfer->len;
		पूर्ण

		trace_spi_transfer_stop(msg, xfer);

		अगर (msg->status != -EINPROGRESS)
			जाओ out;

		spi_transfer_delay_exec(xfer);

		अगर (xfer->cs_change) अणु
			अगर (list_is_last(&xfer->transfer_list,
					 &msg->transfers)) अणु
				keep_cs = true;
			पूर्ण अन्यथा अणु
				spi_set_cs(msg->spi, false, false);
				_spi_transfer_cs_change_delay(msg, xfer);
				spi_set_cs(msg->spi, true, false);
			पूर्ण
		पूर्ण

		msg->actual_length += xfer->len;
	पूर्ण

out:
	अगर (ret != 0 || !keep_cs)
		spi_set_cs(msg->spi, false, false);

	अगर (msg->status == -EINPROGRESS)
		msg->status = ret;

	अगर (msg->status && ctlr->handle_err)
		ctlr->handle_err(ctlr, msg);

	spi_finalize_current_message(ctlr);

	वापस ret;
पूर्ण

/**
 * spi_finalize_current_transfer - report completion of a transfer
 * @ctlr: the controller reporting completion
 *
 * Called by SPI drivers using the core transfer_one_message()
 * implementation to notअगरy it that the current पूर्णांकerrupt driven
 * transfer has finished and the next one may be scheduled.
 */
व्योम spi_finalize_current_transfer(काष्ठा spi_controller *ctlr)
अणु
	complete(&ctlr->xfer_completion);
पूर्ण
EXPORT_SYMBOL_GPL(spi_finalize_current_transfer);

अटल व्योम spi_idle_runसमय_pm(काष्ठा spi_controller *ctlr)
अणु
	अगर (ctlr->स्वतः_runसमय_pm) अणु
		pm_runसमय_mark_last_busy(ctlr->dev.parent);
		pm_runसमय_put_स्वतःsuspend(ctlr->dev.parent);
	पूर्ण
पूर्ण

/**
 * __spi_pump_messages - function which processes spi message queue
 * @ctlr: controller to process queue क्रम
 * @in_kthपढ़ो: true अगर we are in the context of the message pump thपढ़ो
 *
 * This function checks अगर there is any spi message in the queue that
 * needs processing and अगर so call out to the driver to initialize hardware
 * and transfer each message.
 *
 * Note that it is called both from the kthपढ़ो itself and also from
 * inside spi_sync(); the queue extraction handling at the top of the
 * function should deal with this safely.
 */
अटल व्योम __spi_pump_messages(काष्ठा spi_controller *ctlr, bool in_kthपढ़ो)
अणु
	काष्ठा spi_transfer *xfer;
	काष्ठा spi_message *msg;
	bool was_busy = false;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	/* Lock queue */
	spin_lock_irqsave(&ctlr->queue_lock, flags);

	/* Make sure we are not alपढ़ोy running a message */
	अगर (ctlr->cur_msg) अणु
		spin_unlock_irqrestore(&ctlr->queue_lock, flags);
		वापस;
	पूर्ण

	/* If another context is idling the device then defer */
	अगर (ctlr->idling) अणु
		kthपढ़ो_queue_work(ctlr->kworker, &ctlr->pump_messages);
		spin_unlock_irqrestore(&ctlr->queue_lock, flags);
		वापस;
	पूर्ण

	/* Check अगर the queue is idle */
	अगर (list_empty(&ctlr->queue) || !ctlr->running) अणु
		अगर (!ctlr->busy) अणु
			spin_unlock_irqrestore(&ctlr->queue_lock, flags);
			वापस;
		पूर्ण

		/* Defer any non-atomic tearकरोwn to the thपढ़ो */
		अगर (!in_kthपढ़ो) अणु
			अगर (!ctlr->dummy_rx && !ctlr->dummy_tx &&
			    !ctlr->unprepare_transfer_hardware) अणु
				spi_idle_runसमय_pm(ctlr);
				ctlr->busy = false;
				trace_spi_controller_idle(ctlr);
			पूर्ण अन्यथा अणु
				kthपढ़ो_queue_work(ctlr->kworker,
						   &ctlr->pump_messages);
			पूर्ण
			spin_unlock_irqrestore(&ctlr->queue_lock, flags);
			वापस;
		पूर्ण

		ctlr->busy = false;
		ctlr->idling = true;
		spin_unlock_irqrestore(&ctlr->queue_lock, flags);

		kमुक्त(ctlr->dummy_rx);
		ctlr->dummy_rx = शून्य;
		kमुक्त(ctlr->dummy_tx);
		ctlr->dummy_tx = शून्य;
		अगर (ctlr->unprepare_transfer_hardware &&
		    ctlr->unprepare_transfer_hardware(ctlr))
			dev_err(&ctlr->dev,
				"failed to unprepare transfer hardware\n");
		spi_idle_runसमय_pm(ctlr);
		trace_spi_controller_idle(ctlr);

		spin_lock_irqsave(&ctlr->queue_lock, flags);
		ctlr->idling = false;
		spin_unlock_irqrestore(&ctlr->queue_lock, flags);
		वापस;
	पूर्ण

	/* Extract head of queue */
	msg = list_first_entry(&ctlr->queue, काष्ठा spi_message, queue);
	ctlr->cur_msg = msg;

	list_del_init(&msg->queue);
	अगर (ctlr->busy)
		was_busy = true;
	अन्यथा
		ctlr->busy = true;
	spin_unlock_irqrestore(&ctlr->queue_lock, flags);

	mutex_lock(&ctlr->io_mutex);

	अगर (!was_busy && ctlr->स्वतः_runसमय_pm) अणु
		ret = pm_runसमय_get_sync(ctlr->dev.parent);
		अगर (ret < 0) अणु
			pm_runसमय_put_noidle(ctlr->dev.parent);
			dev_err(&ctlr->dev, "Failed to power device: %d\n",
				ret);
			mutex_unlock(&ctlr->io_mutex);
			वापस;
		पूर्ण
	पूर्ण

	अगर (!was_busy)
		trace_spi_controller_busy(ctlr);

	अगर (!was_busy && ctlr->prepare_transfer_hardware) अणु
		ret = ctlr->prepare_transfer_hardware(ctlr);
		अगर (ret) अणु
			dev_err(&ctlr->dev,
				"failed to prepare transfer hardware: %d\n",
				ret);

			अगर (ctlr->स्वतः_runसमय_pm)
				pm_runसमय_put(ctlr->dev.parent);

			msg->status = ret;
			spi_finalize_current_message(ctlr);

			mutex_unlock(&ctlr->io_mutex);
			वापस;
		पूर्ण
	पूर्ण

	trace_spi_message_start(msg);

	अगर (ctlr->prepare_message) अणु
		ret = ctlr->prepare_message(ctlr, msg);
		अगर (ret) अणु
			dev_err(&ctlr->dev, "failed to prepare message: %d\n",
				ret);
			msg->status = ret;
			spi_finalize_current_message(ctlr);
			जाओ out;
		पूर्ण
		ctlr->cur_msg_prepared = true;
	पूर्ण

	ret = spi_map_msg(ctlr, msg);
	अगर (ret) अणु
		msg->status = ret;
		spi_finalize_current_message(ctlr);
		जाओ out;
	पूर्ण

	अगर (!ctlr->ptp_sts_supported && !ctlr->transfer_one) अणु
		list_क्रम_each_entry(xfer, &msg->transfers, transfer_list) अणु
			xfer->ptp_sts_word_pre = 0;
			ptp_पढ़ो_प्रणाली_prets(xfer->ptp_sts);
		पूर्ण
	पूर्ण

	ret = ctlr->transfer_one_message(ctlr, msg);
	अगर (ret) अणु
		dev_err(&ctlr->dev,
			"failed to transfer one message from queue\n");
		जाओ out;
	पूर्ण

out:
	mutex_unlock(&ctlr->io_mutex);

	/* Prod the scheduler in हाल transfer_one() was busy रुकोing */
	अगर (!ret)
		cond_resched();
पूर्ण

/**
 * spi_pump_messages - kthपढ़ो work function which processes spi message queue
 * @work: poपूर्णांकer to kthपढ़ो work काष्ठा contained in the controller काष्ठा
 */
अटल व्योम spi_pump_messages(काष्ठा kthपढ़ो_work *work)
अणु
	काष्ठा spi_controller *ctlr =
		container_of(work, काष्ठा spi_controller, pump_messages);

	__spi_pump_messages(ctlr, true);
पूर्ण

/**
 * spi_take_बारtamp_pre - helper क्रम drivers to collect the beginning of the
 *			    TX बारtamp क्रम the requested byte from the SPI
 *			    transfer. The frequency with which this function
 *			    must be called (once per word, once क्रम the whole
 *			    transfer, once per batch of words etc) is arbitrary
 *			    as दीर्घ as the @tx buffer offset is greater than or
 *			    equal to the requested byte at the समय of the
 *			    call. The बारtamp is only taken once, at the
 *			    first such call. It is assumed that the driver
 *			    advances its @tx buffer poपूर्णांकer monotonically.
 * @ctlr: Poपूर्णांकer to the spi_controller काष्ठाure of the driver
 * @xfer: Poपूर्णांकer to the transfer being बारtamped
 * @progress: How many words (not bytes) have been transferred so far
 * @irqs_off: If true, will disable IRQs and preemption क्रम the duration of the
 *	      transfer, क्रम less jitter in समय measurement. Only compatible
 *	      with PIO drivers. If true, must follow up with
 *	      spi_take_बारtamp_post or otherwise प्रणाली will crash.
 *	      WARNING: क्रम fully predictable results, the CPU frequency must
 *	      also be under control (governor).
 */
व्योम spi_take_बारtamp_pre(काष्ठा spi_controller *ctlr,
			    काष्ठा spi_transfer *xfer,
			    माप_प्रकार progress, bool irqs_off)
अणु
	अगर (!xfer->ptp_sts)
		वापस;

	अगर (xfer->बारtamped)
		वापस;

	अगर (progress > xfer->ptp_sts_word_pre)
		वापस;

	/* Capture the resolution of the बारtamp */
	xfer->ptp_sts_word_pre = progress;

	अगर (irqs_off) अणु
		local_irq_save(ctlr->irq_flags);
		preempt_disable();
	पूर्ण

	ptp_पढ़ो_प्रणाली_prets(xfer->ptp_sts);
पूर्ण
EXPORT_SYMBOL_GPL(spi_take_बारtamp_pre);

/**
 * spi_take_बारtamp_post - helper क्रम drivers to collect the end of the
 *			     TX बारtamp क्रम the requested byte from the SPI
 *			     transfer. Can be called with an arbitrary
 *			     frequency: only the first call where @tx exceeds
 *			     or is equal to the requested word will be
 *			     बारtamped.
 * @ctlr: Poपूर्णांकer to the spi_controller काष्ठाure of the driver
 * @xfer: Poपूर्णांकer to the transfer being बारtamped
 * @progress: How many words (not bytes) have been transferred so far
 * @irqs_off: If true, will re-enable IRQs and preemption क्रम the local CPU.
 */
व्योम spi_take_बारtamp_post(काष्ठा spi_controller *ctlr,
			     काष्ठा spi_transfer *xfer,
			     माप_प्रकार progress, bool irqs_off)
अणु
	अगर (!xfer->ptp_sts)
		वापस;

	अगर (xfer->बारtamped)
		वापस;

	अगर (progress < xfer->ptp_sts_word_post)
		वापस;

	ptp_पढ़ो_प्रणाली_postts(xfer->ptp_sts);

	अगर (irqs_off) अणु
		local_irq_restore(ctlr->irq_flags);
		preempt_enable();
	पूर्ण

	/* Capture the resolution of the बारtamp */
	xfer->ptp_sts_word_post = progress;

	xfer->बारtamped = true;
पूर्ण
EXPORT_SYMBOL_GPL(spi_take_बारtamp_post);

/**
 * spi_set_thपढ़ो_rt - set the controller to pump at realसमय priority
 * @ctlr: controller to boost priority of
 *
 * This can be called because the controller requested realसमय priority
 * (by setting the ->rt value beक्रमe calling spi_रेजिस्टर_controller()) or
 * because a device on the bus said that its transfers needed realसमय
 * priority.
 *
 * NOTE: at the moment अगर any device on a bus says it needs realसमय then
 * the thपढ़ो will be at realसमय priority क्रम all transfers on that
 * controller.  If this eventually becomes a problem we may see अगर we can
 * find a way to boost the priority only temporarily during relevant
 * transfers.
 */
अटल व्योम spi_set_thपढ़ो_rt(काष्ठा spi_controller *ctlr)
अणु
	dev_info(&ctlr->dev,
		"will run message pump with realtime priority\n");
	sched_set_fअगरo(ctlr->kworker->task);
पूर्ण

अटल पूर्णांक spi_init_queue(काष्ठा spi_controller *ctlr)
अणु
	ctlr->running = false;
	ctlr->busy = false;

	ctlr->kworker = kthपढ़ो_create_worker(0, dev_name(&ctlr->dev));
	अगर (IS_ERR(ctlr->kworker)) अणु
		dev_err(&ctlr->dev, "failed to create message pump kworker\n");
		वापस PTR_ERR(ctlr->kworker);
	पूर्ण

	kthपढ़ो_init_work(&ctlr->pump_messages, spi_pump_messages);

	/*
	 * Controller config will indicate अगर this controller should run the
	 * message pump with high (realसमय) priority to reduce the transfer
	 * latency on the bus by minimising the delay between a transfer
	 * request and the scheduling of the message pump thपढ़ो. Without this
	 * setting the message pump thपढ़ो will reमुख्य at शेष priority.
	 */
	अगर (ctlr->rt)
		spi_set_thपढ़ो_rt(ctlr);

	वापस 0;
पूर्ण

/**
 * spi_get_next_queued_message() - called by driver to check क्रम queued
 * messages
 * @ctlr: the controller to check क्रम queued messages
 *
 * If there are more messages in the queue, the next message is वापसed from
 * this call.
 *
 * Return: the next message in the queue, अन्यथा शून्य अगर the queue is empty.
 */
काष्ठा spi_message *spi_get_next_queued_message(काष्ठा spi_controller *ctlr)
अणु
	काष्ठा spi_message *next;
	अचिन्हित दीर्घ flags;

	/* get a poपूर्णांकer to the next message, अगर any */
	spin_lock_irqsave(&ctlr->queue_lock, flags);
	next = list_first_entry_or_null(&ctlr->queue, काष्ठा spi_message,
					queue);
	spin_unlock_irqrestore(&ctlr->queue_lock, flags);

	वापस next;
पूर्ण
EXPORT_SYMBOL_GPL(spi_get_next_queued_message);

/**
 * spi_finalize_current_message() - the current message is complete
 * @ctlr: the controller to वापस the message to
 *
 * Called by the driver to notअगरy the core that the message in the front of the
 * queue is complete and can be हटाओd from the queue.
 */
व्योम spi_finalize_current_message(काष्ठा spi_controller *ctlr)
अणु
	काष्ठा spi_transfer *xfer;
	काष्ठा spi_message *mesg;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	spin_lock_irqsave(&ctlr->queue_lock, flags);
	mesg = ctlr->cur_msg;
	spin_unlock_irqrestore(&ctlr->queue_lock, flags);

	अगर (!ctlr->ptp_sts_supported && !ctlr->transfer_one) अणु
		list_क्रम_each_entry(xfer, &mesg->transfers, transfer_list) अणु
			ptp_पढ़ो_प्रणाली_postts(xfer->ptp_sts);
			xfer->ptp_sts_word_post = xfer->len;
		पूर्ण
	पूर्ण

	अगर (unlikely(ctlr->ptp_sts_supported))
		list_क्रम_each_entry(xfer, &mesg->transfers, transfer_list)
			WARN_ON_ONCE(xfer->ptp_sts && !xfer->बारtamped);

	spi_unmap_msg(ctlr, mesg);

	/* In the prepare_messages callback the spi bus has the opportunity to
	 * split a transfer to smaller chunks.
	 * Release splited transfers here since spi_map_msg is करोne on the
	 * splited transfers.
	 */
	spi_res_release(ctlr, mesg);

	अगर (ctlr->cur_msg_prepared && ctlr->unprepare_message) अणु
		ret = ctlr->unprepare_message(ctlr, mesg);
		अगर (ret) अणु
			dev_err(&ctlr->dev, "failed to unprepare message: %d\n",
				ret);
		पूर्ण
	पूर्ण

	spin_lock_irqsave(&ctlr->queue_lock, flags);
	ctlr->cur_msg = शून्य;
	ctlr->cur_msg_prepared = false;
	ctlr->fallback = false;
	kthपढ़ो_queue_work(ctlr->kworker, &ctlr->pump_messages);
	spin_unlock_irqrestore(&ctlr->queue_lock, flags);

	trace_spi_message_करोne(mesg);

	mesg->state = शून्य;
	अगर (mesg->complete)
		mesg->complete(mesg->context);
पूर्ण
EXPORT_SYMBOL_GPL(spi_finalize_current_message);

अटल पूर्णांक spi_start_queue(काष्ठा spi_controller *ctlr)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ctlr->queue_lock, flags);

	अगर (ctlr->running || ctlr->busy) अणु
		spin_unlock_irqrestore(&ctlr->queue_lock, flags);
		वापस -EBUSY;
	पूर्ण

	ctlr->running = true;
	ctlr->cur_msg = शून्य;
	spin_unlock_irqrestore(&ctlr->queue_lock, flags);

	kthपढ़ो_queue_work(ctlr->kworker, &ctlr->pump_messages);

	वापस 0;
पूर्ण

अटल पूर्णांक spi_stop_queue(काष्ठा spi_controller *ctlr)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित limit = 500;
	पूर्णांक ret = 0;

	spin_lock_irqsave(&ctlr->queue_lock, flags);

	/*
	 * This is a bit lame, but is optimized क्रम the common execution path.
	 * A रुको_queue on the ctlr->busy could be used, but then the common
	 * execution path (pump_messages) would be required to call wake_up or
	 * मित्रs on every SPI message. Do this instead.
	 */
	जबतक ((!list_empty(&ctlr->queue) || ctlr->busy) && limit--) अणु
		spin_unlock_irqrestore(&ctlr->queue_lock, flags);
		usleep_range(10000, 11000);
		spin_lock_irqsave(&ctlr->queue_lock, flags);
	पूर्ण

	अगर (!list_empty(&ctlr->queue) || ctlr->busy)
		ret = -EBUSY;
	अन्यथा
		ctlr->running = false;

	spin_unlock_irqrestore(&ctlr->queue_lock, flags);

	अगर (ret) अणु
		dev_warn(&ctlr->dev, "could not stop message queue\n");
		वापस ret;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक spi_destroy_queue(काष्ठा spi_controller *ctlr)
अणु
	पूर्णांक ret;

	ret = spi_stop_queue(ctlr);

	/*
	 * kthपढ़ो_flush_worker will block until all work is करोne.
	 * If the reason that stop_queue समयd out is that the work will never
	 * finish, then it करोes no good to call flush/stop thपढ़ो, so
	 * वापस anyway.
	 */
	अगर (ret) अणु
		dev_err(&ctlr->dev, "problem destroying queue\n");
		वापस ret;
	पूर्ण

	kthपढ़ो_destroy_worker(ctlr->kworker);

	वापस 0;
पूर्ण

अटल पूर्णांक __spi_queued_transfer(काष्ठा spi_device *spi,
				 काष्ठा spi_message *msg,
				 bool need_pump)
अणु
	काष्ठा spi_controller *ctlr = spi->controller;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ctlr->queue_lock, flags);

	अगर (!ctlr->running) अणु
		spin_unlock_irqrestore(&ctlr->queue_lock, flags);
		वापस -ESHUTDOWN;
	पूर्ण
	msg->actual_length = 0;
	msg->status = -EINPROGRESS;

	list_add_tail(&msg->queue, &ctlr->queue);
	अगर (!ctlr->busy && need_pump)
		kthपढ़ो_queue_work(ctlr->kworker, &ctlr->pump_messages);

	spin_unlock_irqrestore(&ctlr->queue_lock, flags);
	वापस 0;
पूर्ण

/**
 * spi_queued_transfer - transfer function क्रम queued transfers
 * @spi: spi device which is requesting transfer
 * @msg: spi message which is to handled is queued to driver queue
 *
 * Return: zero on success, अन्यथा a negative error code.
 */
अटल पूर्णांक spi_queued_transfer(काष्ठा spi_device *spi, काष्ठा spi_message *msg)
अणु
	वापस __spi_queued_transfer(spi, msg, true);
पूर्ण

अटल पूर्णांक spi_controller_initialize_queue(काष्ठा spi_controller *ctlr)
अणु
	पूर्णांक ret;

	ctlr->transfer = spi_queued_transfer;
	अगर (!ctlr->transfer_one_message)
		ctlr->transfer_one_message = spi_transfer_one_message;

	/* Initialize and start queue */
	ret = spi_init_queue(ctlr);
	अगर (ret) अणु
		dev_err(&ctlr->dev, "problem initializing queue\n");
		जाओ err_init_queue;
	पूर्ण
	ctlr->queued = true;
	ret = spi_start_queue(ctlr);
	अगर (ret) अणु
		dev_err(&ctlr->dev, "problem starting queue\n");
		जाओ err_start_queue;
	पूर्ण

	वापस 0;

err_start_queue:
	spi_destroy_queue(ctlr);
err_init_queue:
	वापस ret;
पूर्ण

/**
 * spi_flush_queue - Send all pending messages in the queue from the callers'
 *		     context
 * @ctlr: controller to process queue क्रम
 *
 * This should be used when one wants to ensure all pending messages have been
 * sent beक्रमe करोing something. Is used by the spi-mem code to make sure SPI
 * memory operations करो not preempt regular SPI transfers that have been queued
 * beक्रमe the spi-mem operation.
 */
व्योम spi_flush_queue(काष्ठा spi_controller *ctlr)
अणु
	अगर (ctlr->transfer == spi_queued_transfer)
		__spi_pump_messages(ctlr, false);
पूर्ण

/*-------------------------------------------------------------------------*/

#अगर defined(CONFIG_OF)
अटल पूर्णांक of_spi_parse_dt(काष्ठा spi_controller *ctlr, काष्ठा spi_device *spi,
			   काष्ठा device_node *nc)
अणु
	u32 value;
	पूर्णांक rc;

	/* Mode (घड़ी phase/polarity/etc.) */
	अगर (of_property_पढ़ो_bool(nc, "spi-cpha"))
		spi->mode |= SPI_CPHA;
	अगर (of_property_पढ़ो_bool(nc, "spi-cpol"))
		spi->mode |= SPI_CPOL;
	अगर (of_property_पढ़ो_bool(nc, "spi-3wire"))
		spi->mode |= SPI_3WIRE;
	अगर (of_property_पढ़ो_bool(nc, "spi-lsb-first"))
		spi->mode |= SPI_LSB_FIRST;
	अगर (of_property_पढ़ो_bool(nc, "spi-cs-high"))
		spi->mode |= SPI_CS_HIGH;

	/* Device DUAL/QUAD mode */
	अगर (!of_property_पढ़ो_u32(nc, "spi-tx-bus-width", &value)) अणु
		चयन (value) अणु
		हाल 0:
			spi->mode |= SPI_NO_TX;
			अवरोध;
		हाल 1:
			अवरोध;
		हाल 2:
			spi->mode |= SPI_TX_DUAL;
			अवरोध;
		हाल 4:
			spi->mode |= SPI_TX_QUAD;
			अवरोध;
		हाल 8:
			spi->mode |= SPI_TX_OCTAL;
			अवरोध;
		शेष:
			dev_warn(&ctlr->dev,
				"spi-tx-bus-width %d not supported\n",
				value);
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!of_property_पढ़ो_u32(nc, "spi-rx-bus-width", &value)) अणु
		चयन (value) अणु
		हाल 0:
			spi->mode |= SPI_NO_RX;
			अवरोध;
		हाल 1:
			अवरोध;
		हाल 2:
			spi->mode |= SPI_RX_DUAL;
			अवरोध;
		हाल 4:
			spi->mode |= SPI_RX_QUAD;
			अवरोध;
		हाल 8:
			spi->mode |= SPI_RX_OCTAL;
			अवरोध;
		शेष:
			dev_warn(&ctlr->dev,
				"spi-rx-bus-width %d not supported\n",
				value);
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (spi_controller_is_slave(ctlr)) अणु
		अगर (!of_node_name_eq(nc, "slave")) अणु
			dev_err(&ctlr->dev, "%pOF is not called 'slave'\n",
				nc);
			वापस -EINVAL;
		पूर्ण
		वापस 0;
	पूर्ण

	/* Device address */
	rc = of_property_पढ़ो_u32(nc, "reg", &value);
	अगर (rc) अणु
		dev_err(&ctlr->dev, "%pOF has no valid 'reg' property (%d)\n",
			nc, rc);
		वापस rc;
	पूर्ण
	spi->chip_select = value;

	/* Device speed */
	अगर (!of_property_पढ़ो_u32(nc, "spi-max-frequency", &value))
		spi->max_speed_hz = value;

	वापस 0;
पूर्ण

अटल काष्ठा spi_device *
of_रेजिस्टर_spi_device(काष्ठा spi_controller *ctlr, काष्ठा device_node *nc)
अणु
	काष्ठा spi_device *spi;
	पूर्णांक rc;

	/* Alloc an spi_device */
	spi = spi_alloc_device(ctlr);
	अगर (!spi) अणु
		dev_err(&ctlr->dev, "spi_device alloc error for %pOF\n", nc);
		rc = -ENOMEM;
		जाओ err_out;
	पूर्ण

	/* Select device driver */
	rc = of_modalias_node(nc, spi->modalias,
				माप(spi->modalias));
	अगर (rc < 0) अणु
		dev_err(&ctlr->dev, "cannot find modalias for %pOF\n", nc);
		जाओ err_out;
	पूर्ण

	rc = of_spi_parse_dt(ctlr, spi, nc);
	अगर (rc)
		जाओ err_out;

	/* Store a poपूर्णांकer to the node in the device काष्ठाure */
	of_node_get(nc);
	spi->dev.of_node = nc;

	/* Register the new device */
	rc = spi_add_device(spi);
	अगर (rc) अणु
		dev_err(&ctlr->dev, "spi_device register error %pOF\n", nc);
		जाओ err_of_node_put;
	पूर्ण

	वापस spi;

err_of_node_put:
	of_node_put(nc);
err_out:
	spi_dev_put(spi);
	वापस ERR_PTR(rc);
पूर्ण

/**
 * of_रेजिस्टर_spi_devices() - Register child devices onto the SPI bus
 * @ctlr:	Poपूर्णांकer to spi_controller device
 *
 * Registers an spi_device क्रम each child node of controller node which
 * represents a valid SPI slave.
 */
अटल व्योम of_रेजिस्टर_spi_devices(काष्ठा spi_controller *ctlr)
अणु
	काष्ठा spi_device *spi;
	काष्ठा device_node *nc;

	अगर (!ctlr->dev.of_node)
		वापस;

	क्रम_each_available_child_of_node(ctlr->dev.of_node, nc) अणु
		अगर (of_node_test_and_set_flag(nc, OF_POPULATED))
			जारी;
		spi = of_रेजिस्टर_spi_device(ctlr, nc);
		अगर (IS_ERR(spi)) अणु
			dev_warn(&ctlr->dev,
				 "Failed to create SPI device for %pOF\n", nc);
			of_node_clear_flag(nc, OF_POPULATED);
		पूर्ण
	पूर्ण
पूर्ण
#अन्यथा
अटल व्योम of_रेजिस्टर_spi_devices(काष्ठा spi_controller *ctlr) अणु पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_ACPI
काष्ठा acpi_spi_lookup अणु
	काष्ठा spi_controller 	*ctlr;
	u32			max_speed_hz;
	u32			mode;
	पूर्णांक			irq;
	u8			bits_per_word;
	u8			chip_select;
पूर्ण;

अटल व्योम acpi_spi_parse_apple_properties(काष्ठा acpi_device *dev,
					    काष्ठा acpi_spi_lookup *lookup)
अणु
	स्थिर जोड़ acpi_object *obj;

	अगर (!x86_apple_machine)
		वापस;

	अगर (!acpi_dev_get_property(dev, "spiSclkPeriod", ACPI_TYPE_BUFFER, &obj)
	    && obj->buffer.length >= 4)
		lookup->max_speed_hz  = NSEC_PER_SEC / *(u32 *)obj->buffer.poपूर्णांकer;

	अगर (!acpi_dev_get_property(dev, "spiWordSize", ACPI_TYPE_BUFFER, &obj)
	    && obj->buffer.length == 8)
		lookup->bits_per_word = *(u64 *)obj->buffer.poपूर्णांकer;

	अगर (!acpi_dev_get_property(dev, "spiBitOrder", ACPI_TYPE_BUFFER, &obj)
	    && obj->buffer.length == 8 && !*(u64 *)obj->buffer.poपूर्णांकer)
		lookup->mode |= SPI_LSB_FIRST;

	अगर (!acpi_dev_get_property(dev, "spiSPO", ACPI_TYPE_BUFFER, &obj)
	    && obj->buffer.length == 8 &&  *(u64 *)obj->buffer.poपूर्णांकer)
		lookup->mode |= SPI_CPOL;

	अगर (!acpi_dev_get_property(dev, "spiSPH", ACPI_TYPE_BUFFER, &obj)
	    && obj->buffer.length == 8 &&  *(u64 *)obj->buffer.poपूर्णांकer)
		lookup->mode |= SPI_CPHA;
पूर्ण

अटल पूर्णांक acpi_spi_add_resource(काष्ठा acpi_resource *ares, व्योम *data)
अणु
	काष्ठा acpi_spi_lookup *lookup = data;
	काष्ठा spi_controller *ctlr = lookup->ctlr;

	अगर (ares->type == ACPI_RESOURCE_TYPE_SERIAL_BUS) अणु
		काष्ठा acpi_resource_spi_serialbus *sb;
		acpi_handle parent_handle;
		acpi_status status;

		sb = &ares->data.spi_serial_bus;
		अगर (sb->type == ACPI_RESOURCE_SERIAL_TYPE_SPI) अणु

			status = acpi_get_handle(शून्य,
						 sb->resource_source.string_ptr,
						 &parent_handle);

			अगर (ACPI_FAILURE(status) ||
			    ACPI_HANDLE(ctlr->dev.parent) != parent_handle)
				वापस -ENODEV;

			/*
			 * ACPI DeviceSelection numbering is handled by the
			 * host controller driver in Winकरोws and can vary
			 * from driver to driver. In Linux we always expect
			 * 0 .. max - 1 so we need to ask the driver to
			 * translate between the two schemes.
			 */
			अगर (ctlr->fw_translate_cs) अणु
				पूर्णांक cs = ctlr->fw_translate_cs(ctlr,
						sb->device_selection);
				अगर (cs < 0)
					वापस cs;
				lookup->chip_select = cs;
			पूर्ण अन्यथा अणु
				lookup->chip_select = sb->device_selection;
			पूर्ण

			lookup->max_speed_hz = sb->connection_speed;
			lookup->bits_per_word = sb->data_bit_length;

			अगर (sb->घड़ी_phase == ACPI_SPI_SECOND_PHASE)
				lookup->mode |= SPI_CPHA;
			अगर (sb->घड़ी_polarity == ACPI_SPI_START_HIGH)
				lookup->mode |= SPI_CPOL;
			अगर (sb->device_polarity == ACPI_SPI_ACTIVE_HIGH)
				lookup->mode |= SPI_CS_HIGH;
		पूर्ण
	पूर्ण अन्यथा अगर (lookup->irq < 0) अणु
		काष्ठा resource r;

		अगर (acpi_dev_resource_पूर्णांकerrupt(ares, 0, &r))
			lookup->irq = r.start;
	पूर्ण

	/* Always tell the ACPI core to skip this resource */
	वापस 1;
पूर्ण

अटल acpi_status acpi_रेजिस्टर_spi_device(काष्ठा spi_controller *ctlr,
					    काष्ठा acpi_device *adev)
अणु
	acpi_handle parent_handle = शून्य;
	काष्ठा list_head resource_list;
	काष्ठा acpi_spi_lookup lookup = अणुपूर्ण;
	काष्ठा spi_device *spi;
	पूर्णांक ret;

	अगर (acpi_bus_get_status(adev) || !adev->status.present ||
	    acpi_device_क्रमागतerated(adev))
		वापस AE_OK;

	lookup.ctlr		= ctlr;
	lookup.irq		= -1;

	INIT_LIST_HEAD(&resource_list);
	ret = acpi_dev_get_resources(adev, &resource_list,
				     acpi_spi_add_resource, &lookup);
	acpi_dev_मुक्त_resource_list(&resource_list);

	अगर (ret < 0)
		/* found SPI in _CRS but it poपूर्णांकs to another controller */
		वापस AE_OK;

	अगर (!lookup.max_speed_hz &&
	    ACPI_SUCCESS(acpi_get_parent(adev->handle, &parent_handle)) &&
	    ACPI_HANDLE(ctlr->dev.parent) == parent_handle) अणु
		/* Apple करोes not use _CRS but nested devices क्रम SPI slaves */
		acpi_spi_parse_apple_properties(adev, &lookup);
	पूर्ण

	अगर (!lookup.max_speed_hz)
		वापस AE_OK;

	spi = spi_alloc_device(ctlr);
	अगर (!spi) अणु
		dev_err(&ctlr->dev, "failed to allocate SPI device for %s\n",
			dev_name(&adev->dev));
		वापस AE_NO_MEMORY;
	पूर्ण


	ACPI_COMPANION_SET(&spi->dev, adev);
	spi->max_speed_hz	= lookup.max_speed_hz;
	spi->mode		|= lookup.mode;
	spi->irq		= lookup.irq;
	spi->bits_per_word	= lookup.bits_per_word;
	spi->chip_select	= lookup.chip_select;

	acpi_set_modalias(adev, acpi_device_hid(adev), spi->modalias,
			  माप(spi->modalias));

	अगर (spi->irq < 0)
		spi->irq = acpi_dev_gpio_irq_get(adev, 0);

	acpi_device_set_क्रमागतerated(adev);

	adev->घातer.flags.ignore_parent = true;
	अगर (spi_add_device(spi)) अणु
		adev->घातer.flags.ignore_parent = false;
		dev_err(&ctlr->dev, "failed to add SPI device %s from ACPI\n",
			dev_name(&adev->dev));
		spi_dev_put(spi);
	पूर्ण

	वापस AE_OK;
पूर्ण

अटल acpi_status acpi_spi_add_device(acpi_handle handle, u32 level,
				       व्योम *data, व्योम **वापस_value)
अणु
	काष्ठा spi_controller *ctlr = data;
	काष्ठा acpi_device *adev;

	अगर (acpi_bus_get_device(handle, &adev))
		वापस AE_OK;

	वापस acpi_रेजिस्टर_spi_device(ctlr, adev);
पूर्ण

#घोषणा SPI_ACPI_ENUMERATE_MAX_DEPTH		32

अटल व्योम acpi_रेजिस्टर_spi_devices(काष्ठा spi_controller *ctlr)
अणु
	acpi_status status;
	acpi_handle handle;

	handle = ACPI_HANDLE(ctlr->dev.parent);
	अगर (!handle)
		वापस;

	status = acpi_walk_namespace(ACPI_TYPE_DEVICE, ACPI_ROOT_OBJECT,
				     SPI_ACPI_ENUMERATE_MAX_DEPTH,
				     acpi_spi_add_device, शून्य, ctlr, शून्य);
	अगर (ACPI_FAILURE(status))
		dev_warn(&ctlr->dev, "failed to enumerate SPI slaves\n");
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम acpi_रेजिस्टर_spi_devices(काष्ठा spi_controller *ctlr) अणुपूर्ण
#पूर्ण_अगर /* CONFIG_ACPI */

अटल व्योम spi_controller_release(काष्ठा device *dev)
अणु
	काष्ठा spi_controller *ctlr;

	ctlr = container_of(dev, काष्ठा spi_controller, dev);
	kमुक्त(ctlr);
पूर्ण

अटल काष्ठा class spi_master_class = अणु
	.name		= "spi_master",
	.owner		= THIS_MODULE,
	.dev_release	= spi_controller_release,
	.dev_groups	= spi_master_groups,
पूर्ण;

#अगर_घोषित CONFIG_SPI_SLAVE
/**
 * spi_slave_पात - पात the ongoing transfer request on an SPI slave
 *		     controller
 * @spi: device used क्रम the current transfer
 */
पूर्णांक spi_slave_पात(काष्ठा spi_device *spi)
अणु
	काष्ठा spi_controller *ctlr = spi->controller;

	अगर (spi_controller_is_slave(ctlr) && ctlr->slave_पात)
		वापस ctlr->slave_पात(ctlr);

	वापस -ENOTSUPP;
पूर्ण
EXPORT_SYMBOL_GPL(spi_slave_पात);

अटल पूर्णांक match_true(काष्ठा device *dev, व्योम *data)
अणु
	वापस 1;
पूर्ण

अटल sमाप_प्रकार slave_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			  अक्षर *buf)
अणु
	काष्ठा spi_controller *ctlr = container_of(dev, काष्ठा spi_controller,
						   dev);
	काष्ठा device *child;

	child = device_find_child(&ctlr->dev, शून्य, match_true);
	वापस प्र_लिखो(buf, "%s\n",
		       child ? to_spi_device(child)->modalias : शून्य);
पूर्ण

अटल sमाप_प्रकार slave_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			   स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा spi_controller *ctlr = container_of(dev, काष्ठा spi_controller,
						   dev);
	काष्ठा spi_device *spi;
	काष्ठा device *child;
	अक्षर name[32];
	पूर्णांक rc;

	rc = माला_पूछो(buf, "%31s", name);
	अगर (rc != 1 || !name[0])
		वापस -EINVAL;

	child = device_find_child(&ctlr->dev, शून्य, match_true);
	अगर (child) अणु
		/* Remove रेजिस्टरed slave */
		device_unरेजिस्टर(child);
		put_device(child);
	पूर्ण

	अगर (म_भेद(name, "(null)")) अणु
		/* Register new slave */
		spi = spi_alloc_device(ctlr);
		अगर (!spi)
			वापस -ENOMEM;

		strlcpy(spi->modalias, name, माप(spi->modalias));

		rc = spi_add_device(spi);
		अगर (rc) अणु
			spi_dev_put(spi);
			वापस rc;
		पूर्ण
	पूर्ण

	वापस count;
पूर्ण

अटल DEVICE_ATTR_RW(slave);

अटल काष्ठा attribute *spi_slave_attrs[] = अणु
	&dev_attr_slave.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group spi_slave_group = अणु
	.attrs = spi_slave_attrs,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *spi_slave_groups[] = अणु
	&spi_controller_statistics_group,
	&spi_slave_group,
	शून्य,
पूर्ण;

अटल काष्ठा class spi_slave_class = अणु
	.name		= "spi_slave",
	.owner		= THIS_MODULE,
	.dev_release	= spi_controller_release,
	.dev_groups	= spi_slave_groups,
पूर्ण;
#अन्यथा
बाह्य काष्ठा class spi_slave_class;	/* dummy */
#पूर्ण_अगर

/**
 * __spi_alloc_controller - allocate an SPI master or slave controller
 * @dev: the controller, possibly using the platक्रमm_bus
 * @size: how much zeroed driver-निजी data to allocate; the poपूर्णांकer to this
 *	memory is in the driver_data field of the वापसed device, accessible
 *	with spi_controller_get_devdata(); the memory is cacheline aligned;
 *	drivers granting DMA access to portions of their निजी data need to
 *	round up @size using ALIGN(size, dma_get_cache_alignment()).
 * @slave: flag indicating whether to allocate an SPI master (false) or SPI
 *	slave (true) controller
 * Context: can sleep
 *
 * This call is used only by SPI controller drivers, which are the
 * only ones directly touching chip रेजिस्टरs.  It's how they allocate
 * an spi_controller काष्ठाure, prior to calling spi_रेजिस्टर_controller().
 *
 * This must be called from context that can sleep.
 *
 * The caller is responsible क्रम assigning the bus number and initializing the
 * controller's methods beक्रमe calling spi_रेजिस्टर_controller(); and (after
 * errors adding the device) calling spi_controller_put() to prevent a memory
 * leak.
 *
 * Return: the SPI controller काष्ठाure on success, अन्यथा शून्य.
 */
काष्ठा spi_controller *__spi_alloc_controller(काष्ठा device *dev,
					      अचिन्हित पूर्णांक size, bool slave)
अणु
	काष्ठा spi_controller	*ctlr;
	माप_प्रकार ctlr_size = ALIGN(माप(*ctlr), dma_get_cache_alignment());

	अगर (!dev)
		वापस शून्य;

	ctlr = kzalloc(size + ctlr_size, GFP_KERNEL);
	अगर (!ctlr)
		वापस शून्य;

	device_initialize(&ctlr->dev);
	ctlr->bus_num = -1;
	ctlr->num_chipselect = 1;
	ctlr->slave = slave;
	अगर (IS_ENABLED(CONFIG_SPI_SLAVE) && slave)
		ctlr->dev.class = &spi_slave_class;
	अन्यथा
		ctlr->dev.class = &spi_master_class;
	ctlr->dev.parent = dev;
	pm_suspend_ignore_children(&ctlr->dev, true);
	spi_controller_set_devdata(ctlr, (व्योम *)ctlr + ctlr_size);

	वापस ctlr;
पूर्ण
EXPORT_SYMBOL_GPL(__spi_alloc_controller);

अटल व्योम devm_spi_release_controller(काष्ठा device *dev, व्योम *ctlr)
अणु
	spi_controller_put(*(काष्ठा spi_controller **)ctlr);
पूर्ण

/**
 * __devm_spi_alloc_controller - resource-managed __spi_alloc_controller()
 * @dev: physical device of SPI controller
 * @size: how much zeroed driver-निजी data to allocate
 * @slave: whether to allocate an SPI master (false) or SPI slave (true)
 * Context: can sleep
 *
 * Allocate an SPI controller and स्वतःmatically release a reference on it
 * when @dev is unbound from its driver.  Drivers are thus relieved from
 * having to call spi_controller_put().
 *
 * The arguments to this function are identical to __spi_alloc_controller().
 *
 * Return: the SPI controller काष्ठाure on success, अन्यथा शून्य.
 */
काष्ठा spi_controller *__devm_spi_alloc_controller(काष्ठा device *dev,
						   अचिन्हित पूर्णांक size,
						   bool slave)
अणु
	काष्ठा spi_controller **ptr, *ctlr;

	ptr = devres_alloc(devm_spi_release_controller, माप(*ptr),
			   GFP_KERNEL);
	अगर (!ptr)
		वापस शून्य;

	ctlr = __spi_alloc_controller(dev, size, slave);
	अगर (ctlr) अणु
		ctlr->devm_allocated = true;
		*ptr = ctlr;
		devres_add(dev, ptr);
	पूर्ण अन्यथा अणु
		devres_मुक्त(ptr);
	पूर्ण

	वापस ctlr;
पूर्ण
EXPORT_SYMBOL_GPL(__devm_spi_alloc_controller);

#अगर_घोषित CONFIG_OF
अटल पूर्णांक of_spi_get_gpio_numbers(काष्ठा spi_controller *ctlr)
अणु
	पूर्णांक nb, i, *cs;
	काष्ठा device_node *np = ctlr->dev.of_node;

	अगर (!np)
		वापस 0;

	nb = of_gpio_named_count(np, "cs-gpios");
	ctlr->num_chipselect = max_t(पूर्णांक, nb, ctlr->num_chipselect);

	/* Return error only क्रम an incorrectly क्रमmed cs-gpios property */
	अगर (nb == 0 || nb == -ENOENT)
		वापस 0;
	अन्यथा अगर (nb < 0)
		वापस nb;

	cs = devm_kसुस्मृति(&ctlr->dev, ctlr->num_chipselect, माप(पूर्णांक),
			  GFP_KERNEL);
	ctlr->cs_gpios = cs;

	अगर (!ctlr->cs_gpios)
		वापस -ENOMEM;

	क्रम (i = 0; i < ctlr->num_chipselect; i++)
		cs[i] = -ENOENT;

	क्रम (i = 0; i < nb; i++)
		cs[i] = of_get_named_gpio(np, "cs-gpios", i);

	वापस 0;
पूर्ण
#अन्यथा
अटल पूर्णांक of_spi_get_gpio_numbers(काष्ठा spi_controller *ctlr)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

/**
 * spi_get_gpio_descs() - grab chip select GPIOs क्रम the master
 * @ctlr: The SPI master to grab GPIO descriptors क्रम
 */
अटल पूर्णांक spi_get_gpio_descs(काष्ठा spi_controller *ctlr)
अणु
	पूर्णांक nb, i;
	काष्ठा gpio_desc **cs;
	काष्ठा device *dev = &ctlr->dev;
	अचिन्हित दीर्घ native_cs_mask = 0;
	अचिन्हित पूर्णांक num_cs_gpios = 0;

	nb = gpiod_count(dev, "cs");
	अगर (nb < 0) अणु
		/* No GPIOs at all is fine, अन्यथा वापस the error */
		अगर (nb == -ENOENT)
			वापस 0;
		वापस nb;
	पूर्ण

	ctlr->num_chipselect = max_t(पूर्णांक, nb, ctlr->num_chipselect);

	cs = devm_kसुस्मृति(dev, ctlr->num_chipselect, माप(*cs),
			  GFP_KERNEL);
	अगर (!cs)
		वापस -ENOMEM;
	ctlr->cs_gpiods = cs;

	क्रम (i = 0; i < nb; i++) अणु
		/*
		 * Most chipselects are active low, the inverted
		 * semantics are handled by special quirks in gpiolib,
		 * so initializing them GPIOD_OUT_LOW here means
		 * "unasserted", in most हालs this will drive the physical
		 * line high.
		 */
		cs[i] = devm_gpiod_get_index_optional(dev, "cs", i,
						      GPIOD_OUT_LOW);
		अगर (IS_ERR(cs[i]))
			वापस PTR_ERR(cs[i]);

		अगर (cs[i]) अणु
			/*
			 * If we find a CS GPIO, name it after the device and
			 * chip select line.
			 */
			अक्षर *gpioname;

			gpioname = devm_kaप्र_लिखो(dev, GFP_KERNEL, "%s CS%d",
						  dev_name(dev), i);
			अगर (!gpioname)
				वापस -ENOMEM;
			gpiod_set_consumer_name(cs[i], gpioname);
			num_cs_gpios++;
			जारी;
		पूर्ण

		अगर (ctlr->max_native_cs && i >= ctlr->max_native_cs) अणु
			dev_err(dev, "Invalid native chip select %d\n", i);
			वापस -EINVAL;
		पूर्ण
		native_cs_mask |= BIT(i);
	पूर्ण

	ctlr->unused_native_cs = ffz(native_cs_mask);
	अगर (num_cs_gpios && ctlr->max_native_cs &&
	    ctlr->unused_native_cs >= ctlr->max_native_cs) अणु
		dev_err(dev, "No unused native chip select available\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक spi_controller_check_ops(काष्ठा spi_controller *ctlr)
अणु
	/*
	 * The controller may implement only the high-level SPI-memory like
	 * operations अगर it करोes not support regular SPI transfers, and this is
	 * valid use हाल.
	 * If ->mem_ops is शून्य, we request that at least one of the
	 * ->transfer_xxx() method be implemented.
	 */
	अगर (ctlr->mem_ops) अणु
		अगर (!ctlr->mem_ops->exec_op)
			वापस -EINVAL;
	पूर्ण अन्यथा अगर (!ctlr->transfer && !ctlr->transfer_one &&
		   !ctlr->transfer_one_message) अणु
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * spi_रेजिस्टर_controller - रेजिस्टर SPI master or slave controller
 * @ctlr: initialized master, originally from spi_alloc_master() or
 *	spi_alloc_slave()
 * Context: can sleep
 *
 * SPI controllers connect to their drivers using some non-SPI bus,
 * such as the platक्रमm bus.  The final stage of probe() in that code
 * includes calling spi_रेजिस्टर_controller() to hook up to this SPI bus glue.
 *
 * SPI controllers use board specअगरic (often SOC specअगरic) bus numbers,
 * and board-specअगरic addressing क्रम SPI devices combines those numbers
 * with chip select numbers.  Since SPI करोes not directly support dynamic
 * device identअगरication, boards need configuration tables telling which
 * chip is at which address.
 *
 * This must be called from context that can sleep.  It वापसs zero on
 * success, अन्यथा a negative error code (dropping the controller's refcount).
 * After a successful वापस, the caller is responsible क्रम calling
 * spi_unरेजिस्टर_controller().
 *
 * Return: zero on success, अन्यथा a negative error code.
 */
पूर्णांक spi_रेजिस्टर_controller(काष्ठा spi_controller *ctlr)
अणु
	काष्ठा device		*dev = ctlr->dev.parent;
	काष्ठा boardinfo	*bi;
	पूर्णांक			status;
	पूर्णांक			id, first_dynamic;

	अगर (!dev)
		वापस -ENODEV;

	/*
	 * Make sure all necessary hooks are implemented beक्रमe रेजिस्टरing
	 * the SPI controller.
	 */
	status = spi_controller_check_ops(ctlr);
	अगर (status)
		वापस status;

	अगर (ctlr->bus_num >= 0) अणु
		/* devices with a fixed bus num must check-in with the num */
		mutex_lock(&board_lock);
		id = idr_alloc(&spi_master_idr, ctlr, ctlr->bus_num,
			ctlr->bus_num + 1, GFP_KERNEL);
		mutex_unlock(&board_lock);
		अगर (WARN(id < 0, "couldn't get idr"))
			वापस id == -ENOSPC ? -EBUSY : id;
		ctlr->bus_num = id;
	पूर्ण अन्यथा अगर (ctlr->dev.of_node) अणु
		/* allocate dynamic bus number using Linux idr */
		id = of_alias_get_id(ctlr->dev.of_node, "spi");
		अगर (id >= 0) अणु
			ctlr->bus_num = id;
			mutex_lock(&board_lock);
			id = idr_alloc(&spi_master_idr, ctlr, ctlr->bus_num,
				       ctlr->bus_num + 1, GFP_KERNEL);
			mutex_unlock(&board_lock);
			अगर (WARN(id < 0, "couldn't get idr"))
				वापस id == -ENOSPC ? -EBUSY : id;
		पूर्ण
	पूर्ण
	अगर (ctlr->bus_num < 0) अणु
		first_dynamic = of_alias_get_highest_id("spi");
		अगर (first_dynamic < 0)
			first_dynamic = 0;
		अन्यथा
			first_dynamic++;

		mutex_lock(&board_lock);
		id = idr_alloc(&spi_master_idr, ctlr, first_dynamic,
			       0, GFP_KERNEL);
		mutex_unlock(&board_lock);
		अगर (WARN(id < 0, "couldn't get idr"))
			वापस id;
		ctlr->bus_num = id;
	पूर्ण
	INIT_LIST_HEAD(&ctlr->queue);
	spin_lock_init(&ctlr->queue_lock);
	spin_lock_init(&ctlr->bus_lock_spinlock);
	mutex_init(&ctlr->bus_lock_mutex);
	mutex_init(&ctlr->io_mutex);
	ctlr->bus_lock_flag = 0;
	init_completion(&ctlr->xfer_completion);
	अगर (!ctlr->max_dma_len)
		ctlr->max_dma_len = पूर्णांक_उच्च;

	/* रेजिस्टर the device, then userspace will see it.
	 * registration fails अगर the bus ID is in use.
	 */
	dev_set_name(&ctlr->dev, "spi%u", ctlr->bus_num);

	अगर (!spi_controller_is_slave(ctlr)) अणु
		अगर (ctlr->use_gpio_descriptors) अणु
			status = spi_get_gpio_descs(ctlr);
			अगर (status)
				जाओ मुक्त_bus_id;
			/*
			 * A controller using GPIO descriptors always
			 * supports SPI_CS_HIGH अगर need be.
			 */
			ctlr->mode_bits |= SPI_CS_HIGH;
		पूर्ण अन्यथा अणु
			/* Legacy code path क्रम GPIOs from DT */
			status = of_spi_get_gpio_numbers(ctlr);
			अगर (status)
				जाओ मुक्त_bus_id;
		पूर्ण
	पूर्ण

	/*
	 * Even अगर it's just one always-selected device, there must
	 * be at least one chipselect.
	 */
	अगर (!ctlr->num_chipselect) अणु
		status = -EINVAL;
		जाओ मुक्त_bus_id;
	पूर्ण

	status = device_add(&ctlr->dev);
	अगर (status < 0)
		जाओ मुक्त_bus_id;
	dev_dbg(dev, "registered %s %s\n",
			spi_controller_is_slave(ctlr) ? "slave" : "master",
			dev_name(&ctlr->dev));

	/*
	 * If we're using a queued driver, start the queue. Note that we don't
	 * need the queueing logic अगर the driver is only supporting high-level
	 * memory operations.
	 */
	अगर (ctlr->transfer) अणु
		dev_info(dev, "controller is unqueued, this is deprecated\n");
	पूर्ण अन्यथा अगर (ctlr->transfer_one || ctlr->transfer_one_message) अणु
		status = spi_controller_initialize_queue(ctlr);
		अगर (status) अणु
			device_del(&ctlr->dev);
			जाओ मुक्त_bus_id;
		पूर्ण
	पूर्ण
	/* add statistics */
	spin_lock_init(&ctlr->statistics.lock);

	mutex_lock(&board_lock);
	list_add_tail(&ctlr->list, &spi_controller_list);
	list_क्रम_each_entry(bi, &board_list, list)
		spi_match_controller_to_boardinfo(ctlr, &bi->board_info);
	mutex_unlock(&board_lock);

	/* Register devices from the device tree and ACPI */
	of_रेजिस्टर_spi_devices(ctlr);
	acpi_रेजिस्टर_spi_devices(ctlr);
	वापस status;

मुक्त_bus_id:
	mutex_lock(&board_lock);
	idr_हटाओ(&spi_master_idr, ctlr->bus_num);
	mutex_unlock(&board_lock);
	वापस status;
पूर्ण
EXPORT_SYMBOL_GPL(spi_रेजिस्टर_controller);

अटल व्योम devm_spi_unरेजिस्टर(व्योम *ctlr)
अणु
	spi_unरेजिस्टर_controller(ctlr);
पूर्ण

/**
 * devm_spi_रेजिस्टर_controller - रेजिस्टर managed SPI master or slave
 *	controller
 * @dev:    device managing SPI controller
 * @ctlr: initialized controller, originally from spi_alloc_master() or
 *	spi_alloc_slave()
 * Context: can sleep
 *
 * Register a SPI device as with spi_रेजिस्टर_controller() which will
 * स्वतःmatically be unरेजिस्टरed and मुक्तd.
 *
 * Return: zero on success, अन्यथा a negative error code.
 */
पूर्णांक devm_spi_रेजिस्टर_controller(काष्ठा device *dev,
				 काष्ठा spi_controller *ctlr)
अणु
	पूर्णांक ret;

	ret = spi_रेजिस्टर_controller(ctlr);
	अगर (ret)
		वापस ret;

	वापस devm_add_action_or_reset(dev, devm_spi_unरेजिस्टर, ctlr);
पूर्ण
EXPORT_SYMBOL_GPL(devm_spi_रेजिस्टर_controller);

अटल पूर्णांक __unरेजिस्टर(काष्ठा device *dev, व्योम *null)
अणु
	spi_unरेजिस्टर_device(to_spi_device(dev));
	वापस 0;
पूर्ण

/**
 * spi_unरेजिस्टर_controller - unरेजिस्टर SPI master or slave controller
 * @ctlr: the controller being unरेजिस्टरed
 * Context: can sleep
 *
 * This call is used only by SPI controller drivers, which are the
 * only ones directly touching chip रेजिस्टरs.
 *
 * This must be called from context that can sleep.
 *
 * Note that this function also drops a reference to the controller.
 */
व्योम spi_unरेजिस्टर_controller(काष्ठा spi_controller *ctlr)
अणु
	काष्ठा spi_controller *found;
	पूर्णांक id = ctlr->bus_num;

	/* Prevent addition of new devices, unरेजिस्टर existing ones */
	अगर (IS_ENABLED(CONFIG_SPI_DYNAMIC))
		mutex_lock(&spi_add_lock);

	device_क्रम_each_child(&ctlr->dev, शून्य, __unरेजिस्टर);

	/* First make sure that this controller was ever added */
	mutex_lock(&board_lock);
	found = idr_find(&spi_master_idr, id);
	mutex_unlock(&board_lock);
	अगर (ctlr->queued) अणु
		अगर (spi_destroy_queue(ctlr))
			dev_err(&ctlr->dev, "queue remove failed\n");
	पूर्ण
	mutex_lock(&board_lock);
	list_del(&ctlr->list);
	mutex_unlock(&board_lock);

	device_del(&ctlr->dev);

	/* Release the last reference on the controller अगर its driver
	 * has not yet been converted to devm_spi_alloc_master/slave().
	 */
	अगर (!ctlr->devm_allocated)
		put_device(&ctlr->dev);

	/* मुक्त bus id */
	mutex_lock(&board_lock);
	अगर (found == ctlr)
		idr_हटाओ(&spi_master_idr, id);
	mutex_unlock(&board_lock);

	अगर (IS_ENABLED(CONFIG_SPI_DYNAMIC))
		mutex_unlock(&spi_add_lock);
पूर्ण
EXPORT_SYMBOL_GPL(spi_unरेजिस्टर_controller);

पूर्णांक spi_controller_suspend(काष्ठा spi_controller *ctlr)
अणु
	पूर्णांक ret;

	/* Basically no-ops क्रम non-queued controllers */
	अगर (!ctlr->queued)
		वापस 0;

	ret = spi_stop_queue(ctlr);
	अगर (ret)
		dev_err(&ctlr->dev, "queue stop failed\n");

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(spi_controller_suspend);

पूर्णांक spi_controller_resume(काष्ठा spi_controller *ctlr)
अणु
	पूर्णांक ret;

	अगर (!ctlr->queued)
		वापस 0;

	ret = spi_start_queue(ctlr);
	अगर (ret)
		dev_err(&ctlr->dev, "queue restart failed\n");

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(spi_controller_resume);

अटल पूर्णांक __spi_controller_match(काष्ठा device *dev, स्थिर व्योम *data)
अणु
	काष्ठा spi_controller *ctlr;
	स्थिर u16 *bus_num = data;

	ctlr = container_of(dev, काष्ठा spi_controller, dev);
	वापस ctlr->bus_num == *bus_num;
पूर्ण

/**
 * spi_busnum_to_master - look up master associated with bus_num
 * @bus_num: the master's bus number
 * Context: can sleep
 *
 * This call may be used with devices that are रेजिस्टरed after
 * arch init समय.  It वापसs a refcounted poपूर्णांकer to the relevant
 * spi_controller (which the caller must release), or शून्य अगर there is
 * no such master रेजिस्टरed.
 *
 * Return: the SPI master काष्ठाure on success, अन्यथा शून्य.
 */
काष्ठा spi_controller *spi_busnum_to_master(u16 bus_num)
अणु
	काष्ठा device		*dev;
	काष्ठा spi_controller	*ctlr = शून्य;

	dev = class_find_device(&spi_master_class, शून्य, &bus_num,
				__spi_controller_match);
	अगर (dev)
		ctlr = container_of(dev, काष्ठा spi_controller, dev);
	/* reference got in class_find_device */
	वापस ctlr;
पूर्ण
EXPORT_SYMBOL_GPL(spi_busnum_to_master);

/*-------------------------------------------------------------------------*/

/* Core methods क्रम SPI resource management */

/**
 * spi_res_alloc - allocate a spi resource that is lअगरe-cycle managed
 *                 during the processing of a spi_message जबतक using
 *                 spi_transfer_one
 * @spi:     the spi device क्रम which we allocate memory
 * @release: the release code to execute क्रम this resource
 * @size:    size to alloc and वापस
 * @gfp:     GFP allocation flags
 *
 * Return: the poपूर्णांकer to the allocated data
 *
 * This may get enhanced in the future to allocate from a memory pool
 * of the @spi_device or @spi_controller to aव्योम repeated allocations.
 */
व्योम *spi_res_alloc(काष्ठा spi_device *spi,
		    spi_res_release_t release,
		    माप_प्रकार size, gfp_t gfp)
अणु
	काष्ठा spi_res *sres;

	sres = kzalloc(माप(*sres) + size, gfp);
	अगर (!sres)
		वापस शून्य;

	INIT_LIST_HEAD(&sres->entry);
	sres->release = release;

	वापस sres->data;
पूर्ण
EXPORT_SYMBOL_GPL(spi_res_alloc);

/**
 * spi_res_मुक्त - मुक्त an spi resource
 * @res: poपूर्णांकer to the custom data of a resource
 *
 */
व्योम spi_res_मुक्त(व्योम *res)
अणु
	काष्ठा spi_res *sres = container_of(res, काष्ठा spi_res, data);

	अगर (!res)
		वापस;

	WARN_ON(!list_empty(&sres->entry));
	kमुक्त(sres);
पूर्ण
EXPORT_SYMBOL_GPL(spi_res_मुक्त);

/**
 * spi_res_add - add a spi_res to the spi_message
 * @message: the spi message
 * @res:     the spi_resource
 */
व्योम spi_res_add(काष्ठा spi_message *message, व्योम *res)
अणु
	काष्ठा spi_res *sres = container_of(res, काष्ठा spi_res, data);

	WARN_ON(!list_empty(&sres->entry));
	list_add_tail(&sres->entry, &message->resources);
पूर्ण
EXPORT_SYMBOL_GPL(spi_res_add);

/**
 * spi_res_release - release all spi resources क्रम this message
 * @ctlr:  the @spi_controller
 * @message: the @spi_message
 */
व्योम spi_res_release(काष्ठा spi_controller *ctlr, काष्ठा spi_message *message)
अणु
	काष्ठा spi_res *res, *पंचांगp;

	list_क्रम_each_entry_safe_reverse(res, पंचांगp, &message->resources, entry) अणु
		अगर (res->release)
			res->release(ctlr, message, res->data);

		list_del(&res->entry);

		kमुक्त(res);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(spi_res_release);

/*-------------------------------------------------------------------------*/

/* Core methods क्रम spi_message alterations */

अटल व्योम __spi_replace_transfers_release(काष्ठा spi_controller *ctlr,
					    काष्ठा spi_message *msg,
					    व्योम *res)
अणु
	काष्ठा spi_replaced_transfers *rxfer = res;
	माप_प्रकार i;

	/* call extra callback अगर requested */
	अगर (rxfer->release)
		rxfer->release(ctlr, msg, res);

	/* insert replaced transfers back पूर्णांकo the message */
	list_splice(&rxfer->replaced_transfers, rxfer->replaced_after);

	/* हटाओ the क्रमmerly inserted entries */
	क्रम (i = 0; i < rxfer->inserted; i++)
		list_del(&rxfer->inserted_transfers[i].transfer_list);
पूर्ण

/**
 * spi_replace_transfers - replace transfers with several transfers
 *                         and रेजिस्टर change with spi_message.resources
 * @msg:           the spi_message we work upon
 * @xfer_first:    the first spi_transfer we want to replace
 * @हटाओ:        number of transfers to हटाओ
 * @insert:        the number of transfers we want to insert instead
 * @release:       extra release code necessary in some circumstances
 * @extradatasize: extra data to allocate (with alignment guarantees
 *                 of काष्ठा @spi_transfer)
 * @gfp:           gfp flags
 *
 * Returns: poपूर्णांकer to @spi_replaced_transfers,
 *          PTR_ERR(...) in हाल of errors.
 */
काष्ठा spi_replaced_transfers *spi_replace_transfers(
	काष्ठा spi_message *msg,
	काष्ठा spi_transfer *xfer_first,
	माप_प्रकार हटाओ,
	माप_प्रकार insert,
	spi_replaced_release_t release,
	माप_प्रकार extradatasize,
	gfp_t gfp)
अणु
	काष्ठा spi_replaced_transfers *rxfer;
	काष्ठा spi_transfer *xfer;
	माप_प्रकार i;

	/* allocate the काष्ठाure using spi_res */
	rxfer = spi_res_alloc(msg->spi, __spi_replace_transfers_release,
			      काष्ठा_size(rxfer, inserted_transfers, insert)
			      + extradatasize,
			      gfp);
	अगर (!rxfer)
		वापस ERR_PTR(-ENOMEM);

	/* the release code to invoke beक्रमe running the generic release */
	rxfer->release = release;

	/* assign extradata */
	अगर (extradatasize)
		rxfer->extradata =
			&rxfer->inserted_transfers[insert];

	/* init the replaced_transfers list */
	INIT_LIST_HEAD(&rxfer->replaced_transfers);

	/* assign the list_entry after which we should reinsert
	 * the @replaced_transfers - it may be spi_message.messages!
	 */
	rxfer->replaced_after = xfer_first->transfer_list.prev;

	/* हटाओ the requested number of transfers */
	क्रम (i = 0; i < हटाओ; i++) अणु
		/* अगर the entry after replaced_after it is msg->transfers
		 * then we have been requested to हटाओ more transfers
		 * than are in the list
		 */
		अगर (rxfer->replaced_after->next == &msg->transfers) अणु
			dev_err(&msg->spi->dev,
				"requested to remove more spi_transfers than are available\n");
			/* insert replaced transfers back पूर्णांकo the message */
			list_splice(&rxfer->replaced_transfers,
				    rxfer->replaced_after);

			/* मुक्त the spi_replace_transfer काष्ठाure */
			spi_res_मुक्त(rxfer);

			/* and वापस with an error */
			वापस ERR_PTR(-EINVAL);
		पूर्ण

		/* हटाओ the entry after replaced_after from list of
		 * transfers and add it to list of replaced_transfers
		 */
		list_move_tail(rxfer->replaced_after->next,
			       &rxfer->replaced_transfers);
	पूर्ण

	/* create copy of the given xfer with identical settings
	 * based on the first transfer to get हटाओd
	 */
	क्रम (i = 0; i < insert; i++) अणु
		/* we need to run in reverse order */
		xfer = &rxfer->inserted_transfers[insert - 1 - i];

		/* copy all spi_transfer data */
		स_नकल(xfer, xfer_first, माप(*xfer));

		/* add to list */
		list_add(&xfer->transfer_list, rxfer->replaced_after);

		/* clear cs_change and delay क्रम all but the last */
		अगर (i) अणु
			xfer->cs_change = false;
			xfer->delay.value = 0;
		पूर्ण
	पूर्ण

	/* set up inserted */
	rxfer->inserted = insert;

	/* and रेजिस्टर it with spi_res/spi_message */
	spi_res_add(msg, rxfer);

	वापस rxfer;
पूर्ण
EXPORT_SYMBOL_GPL(spi_replace_transfers);

अटल पूर्णांक __spi_split_transfer_maxsize(काष्ठा spi_controller *ctlr,
					काष्ठा spi_message *msg,
					काष्ठा spi_transfer **xferp,
					माप_प्रकार maxsize,
					gfp_t gfp)
अणु
	काष्ठा spi_transfer *xfer = *xferp, *xfers;
	काष्ठा spi_replaced_transfers *srt;
	माप_प्रकार offset;
	माप_प्रकार count, i;

	/* calculate how many we have to replace */
	count = DIV_ROUND_UP(xfer->len, maxsize);

	/* create replacement */
	srt = spi_replace_transfers(msg, xfer, 1, count, शून्य, 0, gfp);
	अगर (IS_ERR(srt))
		वापस PTR_ERR(srt);
	xfers = srt->inserted_transfers;

	/* now handle each of those newly inserted spi_transfers
	 * note that the replacements spi_transfers all are preset
	 * to the same values as *xferp, so tx_buf, rx_buf and len
	 * are all identical (as well as most others)
	 * so we just have to fix up len and the poपूर्णांकers.
	 *
	 * this also includes support क्रम the depreciated
	 * spi_message.is_dma_mapped पूर्णांकerface
	 */

	/* the first transfer just needs the length modअगरied, so we
	 * run it outside the loop
	 */
	xfers[0].len = min_t(माप_प्रकार, maxsize, xfer[0].len);

	/* all the others need rx_buf/tx_buf also set */
	क्रम (i = 1, offset = maxsize; i < count; offset += maxsize, i++) अणु
		/* update rx_buf, tx_buf and dma */
		अगर (xfers[i].rx_buf)
			xfers[i].rx_buf += offset;
		अगर (xfers[i].rx_dma)
			xfers[i].rx_dma += offset;
		अगर (xfers[i].tx_buf)
			xfers[i].tx_buf += offset;
		अगर (xfers[i].tx_dma)
			xfers[i].tx_dma += offset;

		/* update length */
		xfers[i].len = min(maxsize, xfers[i].len - offset);
	पूर्ण

	/* we set up xferp to the last entry we have inserted,
	 * so that we skip those alपढ़ोy split transfers
	 */
	*xferp = &xfers[count - 1];

	/* increment statistics counters */
	SPI_STATISTICS_INCREMENT_FIELD(&ctlr->statistics,
				       transfers_split_maxsize);
	SPI_STATISTICS_INCREMENT_FIELD(&msg->spi->statistics,
				       transfers_split_maxsize);

	वापस 0;
पूर्ण

/**
 * spi_split_transfers_maxsize - split spi transfers पूर्णांकo multiple transfers
 *                               when an inभागidual transfer exceeds a
 *                               certain size
 * @ctlr:    the @spi_controller क्रम this transfer
 * @msg:   the @spi_message to transक्रमm
 * @maxsize:  the maximum when to apply this
 * @gfp: GFP allocation flags
 *
 * Return: status of transक्रमmation
 */
पूर्णांक spi_split_transfers_maxsize(काष्ठा spi_controller *ctlr,
				काष्ठा spi_message *msg,
				माप_प्रकार maxsize,
				gfp_t gfp)
अणु
	काष्ठा spi_transfer *xfer;
	पूर्णांक ret;

	/* iterate over the transfer_list,
	 * but note that xfer is advanced to the last transfer inserted
	 * to aव्योम checking sizes again unnecessarily (also xfer करोes
	 * potentiall beदीर्घ to a dअगरferent list by the समय the
	 * replacement has happened
	 */
	list_क्रम_each_entry(xfer, &msg->transfers, transfer_list) अणु
		अगर (xfer->len > maxsize) अणु
			ret = __spi_split_transfer_maxsize(ctlr, msg, &xfer,
							   maxsize, gfp);
			अगर (ret)
				वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(spi_split_transfers_maxsize);

/*-------------------------------------------------------------------------*/

/* Core methods क्रम SPI controller protocol drivers.  Some of the
 * other core methods are currently defined as अंतरभूत functions.
 */

अटल पूर्णांक __spi_validate_bits_per_word(काष्ठा spi_controller *ctlr,
					u8 bits_per_word)
अणु
	अगर (ctlr->bits_per_word_mask) अणु
		/* Only 32 bits fit in the mask */
		अगर (bits_per_word > 32)
			वापस -EINVAL;
		अगर (!(ctlr->bits_per_word_mask & SPI_BPW_MASK(bits_per_word)))
			वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * spi_setup - setup SPI mode and घड़ी rate
 * @spi: the device whose settings are being modअगरied
 * Context: can sleep, and no requests are queued to the device
 *
 * SPI protocol drivers may need to update the transfer mode अगर the
 * device करोesn't work with its शेष.  They may likewise need
 * to update घड़ी rates or word sizes from initial values.  This function
 * changes those settings, and must be called from a context that can sleep.
 * Except क्रम SPI_CS_HIGH, which takes effect immediately, the changes take
 * effect the next समय the device is selected and data is transferred to
 * or from it.  When this function वापसs, the spi device is deselected.
 *
 * Note that this call will fail अगर the protocol driver specअगरies an option
 * that the underlying controller or its driver करोes not support.  For
 * example, not all hardware supports wire transfers using nine bit words,
 * LSB-first wire encoding, or active-high chipselects.
 *
 * Return: zero on success, अन्यथा a negative error code.
 */
पूर्णांक spi_setup(काष्ठा spi_device *spi)
अणु
	अचिन्हित	bad_bits, ugly_bits;
	पूर्णांक		status;

	/*
	 * check mode to prevent that any two of DUAL, QUAD and NO_MOSI/MISO
	 * are set at the same समय
	 */
	अगर ((hweight_दीर्घ(spi->mode &
		(SPI_TX_DUAL | SPI_TX_QUAD | SPI_NO_TX)) > 1) ||
	    (hweight_दीर्घ(spi->mode &
		(SPI_RX_DUAL | SPI_RX_QUAD | SPI_NO_RX)) > 1)) अणु
		dev_err(&spi->dev,
		"setup: can not select any two of dual, quad and no-rx/tx at the same time\n");
		वापस -EINVAL;
	पूर्ण
	/* अगर it is SPI_3WIRE mode, DUAL and QUAD should be क्रमbidden
	 */
	अगर ((spi->mode & SPI_3WIRE) && (spi->mode &
		(SPI_TX_DUAL | SPI_TX_QUAD | SPI_TX_OCTAL |
		 SPI_RX_DUAL | SPI_RX_QUAD | SPI_RX_OCTAL)))
		वापस -EINVAL;
	/* help drivers fail *cleanly* when they need options
	 * that aren't supported with their current controller
	 * SPI_CS_WORD has a fallback software implementation,
	 * so it is ignored here.
	 */
	bad_bits = spi->mode & ~(spi->controller->mode_bits | SPI_CS_WORD |
				 SPI_NO_TX | SPI_NO_RX);
	/* nothing prevents from working with active-high CS in हाल अगर it
	 * is driven by GPIO.
	 */
	अगर (gpio_is_valid(spi->cs_gpio))
		bad_bits &= ~SPI_CS_HIGH;
	ugly_bits = bad_bits &
		    (SPI_TX_DUAL | SPI_TX_QUAD | SPI_TX_OCTAL |
		     SPI_RX_DUAL | SPI_RX_QUAD | SPI_RX_OCTAL);
	अगर (ugly_bits) अणु
		dev_warn(&spi->dev,
			 "setup: ignoring unsupported mode bits %x\n",
			 ugly_bits);
		spi->mode &= ~ugly_bits;
		bad_bits &= ~ugly_bits;
	पूर्ण
	अगर (bad_bits) अणु
		dev_err(&spi->dev, "setup: unsupported mode bits %x\n",
			bad_bits);
		वापस -EINVAL;
	पूर्ण

	अगर (!spi->bits_per_word)
		spi->bits_per_word = 8;

	status = __spi_validate_bits_per_word(spi->controller,
					      spi->bits_per_word);
	अगर (status)
		वापस status;

	अगर (spi->controller->max_speed_hz &&
	    (!spi->max_speed_hz ||
	     spi->max_speed_hz > spi->controller->max_speed_hz))
		spi->max_speed_hz = spi->controller->max_speed_hz;

	mutex_lock(&spi->controller->io_mutex);

	अगर (spi->controller->setup) अणु
		status = spi->controller->setup(spi);
		अगर (status) अणु
			mutex_unlock(&spi->controller->io_mutex);
			dev_err(&spi->controller->dev, "Failed to setup device: %d\n",
				status);
			वापस status;
		पूर्ण
	पूर्ण

	अगर (spi->controller->स्वतः_runसमय_pm && spi->controller->set_cs) अणु
		status = pm_runसमय_get_sync(spi->controller->dev.parent);
		अगर (status < 0) अणु
			mutex_unlock(&spi->controller->io_mutex);
			pm_runसमय_put_noidle(spi->controller->dev.parent);
			dev_err(&spi->controller->dev, "Failed to power device: %d\n",
				status);
			वापस status;
		पूर्ण

		/*
		 * We करो not want to वापस positive value from pm_runसमय_get,
		 * there are many instances of devices calling spi_setup() and
		 * checking क्रम a non-zero वापस value instead of a negative
		 * वापस value.
		 */
		status = 0;

		spi_set_cs(spi, false, true);
		pm_runसमय_mark_last_busy(spi->controller->dev.parent);
		pm_runसमय_put_स्वतःsuspend(spi->controller->dev.parent);
	पूर्ण अन्यथा अणु
		spi_set_cs(spi, false, true);
	पूर्ण

	mutex_unlock(&spi->controller->io_mutex);

	अगर (spi->rt && !spi->controller->rt) अणु
		spi->controller->rt = true;
		spi_set_thपढ़ो_rt(spi->controller);
	पूर्ण

	dev_dbg(&spi->dev, "setup mode %d, %s%s%s%s%u bits/w, %u Hz max --> %d\n",
			(पूर्णांक) (spi->mode & (SPI_CPOL | SPI_CPHA)),
			(spi->mode & SPI_CS_HIGH) ? "cs_high, " : "",
			(spi->mode & SPI_LSB_FIRST) ? "lsb, " : "",
			(spi->mode & SPI_3WIRE) ? "3wire, " : "",
			(spi->mode & SPI_LOOP) ? "loopback, " : "",
			spi->bits_per_word, spi->max_speed_hz,
			status);

	वापस status;
पूर्ण
EXPORT_SYMBOL_GPL(spi_setup);

/**
 * spi_set_cs_timing - configure CS setup, hold, and inactive delays
 * @spi: the device that requires specअगरic CS timing configuration
 * @setup: CS setup समय specअगरied via @spi_delay
 * @hold: CS hold समय specअगरied via @spi_delay
 * @inactive: CS inactive delay between transfers specअगरied via @spi_delay
 *
 * Return: zero on success, अन्यथा a negative error code.
 */
पूर्णांक spi_set_cs_timing(काष्ठा spi_device *spi, काष्ठा spi_delay *setup,
		      काष्ठा spi_delay *hold, काष्ठा spi_delay *inactive)
अणु
	काष्ठा device *parent = spi->controller->dev.parent;
	माप_प्रकार len;
	पूर्णांक status;

	अगर (spi->controller->set_cs_timing &&
	    !(spi->cs_gpiod || gpio_is_valid(spi->cs_gpio))) अणु
		mutex_lock(&spi->controller->io_mutex);

		अगर (spi->controller->स्वतः_runसमय_pm) अणु
			status = pm_runसमय_get_sync(parent);
			अगर (status < 0) अणु
				mutex_unlock(&spi->controller->io_mutex);
				pm_runसमय_put_noidle(parent);
				dev_err(&spi->controller->dev, "Failed to power device: %d\n",
					status);
				वापस status;
			पूर्ण

			status = spi->controller->set_cs_timing(spi, setup,
								hold, inactive);
			pm_runसमय_mark_last_busy(parent);
			pm_runसमय_put_स्वतःsuspend(parent);
		पूर्ण अन्यथा अणु
			status = spi->controller->set_cs_timing(spi, setup, hold,
							      inactive);
		पूर्ण

		mutex_unlock(&spi->controller->io_mutex);
		वापस status;
	पूर्ण

	अगर ((setup && setup->unit == SPI_DELAY_UNIT_SCK) ||
	    (hold && hold->unit == SPI_DELAY_UNIT_SCK) ||
	    (inactive && inactive->unit == SPI_DELAY_UNIT_SCK)) अणु
		dev_err(&spi->dev,
			"Clock-cycle delays for CS not supported in SW mode\n");
		वापस -ENOTSUPP;
	पूर्ण

	len = माप(काष्ठा spi_delay);

	/* copy delays to controller */
	अगर (setup)
		स_नकल(&spi->controller->cs_setup, setup, len);
	अन्यथा
		स_रखो(&spi->controller->cs_setup, 0, len);

	अगर (hold)
		स_नकल(&spi->controller->cs_hold, hold, len);
	अन्यथा
		स_रखो(&spi->controller->cs_hold, 0, len);

	अगर (inactive)
		स_नकल(&spi->controller->cs_inactive, inactive, len);
	अन्यथा
		स_रखो(&spi->controller->cs_inactive, 0, len);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(spi_set_cs_timing);

अटल पूर्णांक _spi_xfer_word_delay_update(काष्ठा spi_transfer *xfer,
				       काष्ठा spi_device *spi)
अणु
	पूर्णांक delay1, delay2;

	delay1 = spi_delay_to_ns(&xfer->word_delay, xfer);
	अगर (delay1 < 0)
		वापस delay1;

	delay2 = spi_delay_to_ns(&spi->word_delay, xfer);
	अगर (delay2 < 0)
		वापस delay2;

	अगर (delay1 < delay2)
		स_नकल(&xfer->word_delay, &spi->word_delay,
		       माप(xfer->word_delay));

	वापस 0;
पूर्ण

अटल पूर्णांक __spi_validate(काष्ठा spi_device *spi, काष्ठा spi_message *message)
अणु
	काष्ठा spi_controller *ctlr = spi->controller;
	काष्ठा spi_transfer *xfer;
	पूर्णांक w_size;

	अगर (list_empty(&message->transfers))
		वापस -EINVAL;

	/* If an SPI controller करोes not support toggling the CS line on each
	 * transfer (indicated by the SPI_CS_WORD flag) or we are using a GPIO
	 * क्रम the CS line, we can emulate the CS-per-word hardware function by
	 * splitting transfers पूर्णांकo one-word transfers and ensuring that
	 * cs_change is set क्रम each transfer.
	 */
	अगर ((spi->mode & SPI_CS_WORD) && (!(ctlr->mode_bits & SPI_CS_WORD) ||
					  spi->cs_gpiod ||
					  gpio_is_valid(spi->cs_gpio))) अणु
		माप_प्रकार maxsize;
		पूर्णांक ret;

		maxsize = (spi->bits_per_word + 7) / 8;

		/* spi_split_transfers_maxsize() requires message->spi */
		message->spi = spi;

		ret = spi_split_transfers_maxsize(ctlr, message, maxsize,
						  GFP_KERNEL);
		अगर (ret)
			वापस ret;

		list_क्रम_each_entry(xfer, &message->transfers, transfer_list) अणु
			/* करोn't change cs_change on the last entry in the list */
			अगर (list_is_last(&xfer->transfer_list, &message->transfers))
				अवरोध;
			xfer->cs_change = 1;
		पूर्ण
	पूर्ण

	/* Half-duplex links include original MicroWire, and ones with
	 * only one data pin like SPI_3WIRE (चयनes direction) or where
	 * either MOSI or MISO is missing.  They can also be caused by
	 * software limitations.
	 */
	अगर ((ctlr->flags & SPI_CONTROLLER_HALF_DUPLEX) ||
	    (spi->mode & SPI_3WIRE)) अणु
		अचिन्हित flags = ctlr->flags;

		list_क्रम_each_entry(xfer, &message->transfers, transfer_list) अणु
			अगर (xfer->rx_buf && xfer->tx_buf)
				वापस -EINVAL;
			अगर ((flags & SPI_CONTROLLER_NO_TX) && xfer->tx_buf)
				वापस -EINVAL;
			अगर ((flags & SPI_CONTROLLER_NO_RX) && xfer->rx_buf)
				वापस -EINVAL;
		पूर्ण
	पूर्ण

	/**
	 * Set transfer bits_per_word and max speed as spi device शेष अगर
	 * it is not set क्रम this transfer.
	 * Set transfer tx_nbits and rx_nbits as single transfer शेष
	 * (SPI_NBITS_SINGLE) अगर it is not set क्रम this transfer.
	 * Ensure transfer word_delay is at least as दीर्घ as that required by
	 * device itself.
	 */
	message->frame_length = 0;
	list_क्रम_each_entry(xfer, &message->transfers, transfer_list) अणु
		xfer->effective_speed_hz = 0;
		message->frame_length += xfer->len;
		अगर (!xfer->bits_per_word)
			xfer->bits_per_word = spi->bits_per_word;

		अगर (!xfer->speed_hz)
			xfer->speed_hz = spi->max_speed_hz;

		अगर (ctlr->max_speed_hz && xfer->speed_hz > ctlr->max_speed_hz)
			xfer->speed_hz = ctlr->max_speed_hz;

		अगर (__spi_validate_bits_per_word(ctlr, xfer->bits_per_word))
			वापस -EINVAL;

		/*
		 * SPI transfer length should be multiple of SPI word size
		 * where SPI word size should be घातer-of-two multiple
		 */
		अगर (xfer->bits_per_word <= 8)
			w_size = 1;
		अन्यथा अगर (xfer->bits_per_word <= 16)
			w_size = 2;
		अन्यथा
			w_size = 4;

		/* No partial transfers accepted */
		अगर (xfer->len % w_size)
			वापस -EINVAL;

		अगर (xfer->speed_hz && ctlr->min_speed_hz &&
		    xfer->speed_hz < ctlr->min_speed_hz)
			वापस -EINVAL;

		अगर (xfer->tx_buf && !xfer->tx_nbits)
			xfer->tx_nbits = SPI_NBITS_SINGLE;
		अगर (xfer->rx_buf && !xfer->rx_nbits)
			xfer->rx_nbits = SPI_NBITS_SINGLE;
		/* check transfer tx/rx_nbits:
		 * 1. check the value matches one of single, dual and quad
		 * 2. check tx/rx_nbits match the mode in spi_device
		 */
		अगर (xfer->tx_buf) अणु
			अगर (spi->mode & SPI_NO_TX)
				वापस -EINVAL;
			अगर (xfer->tx_nbits != SPI_NBITS_SINGLE &&
				xfer->tx_nbits != SPI_NBITS_DUAL &&
				xfer->tx_nbits != SPI_NBITS_QUAD)
				वापस -EINVAL;
			अगर ((xfer->tx_nbits == SPI_NBITS_DUAL) &&
				!(spi->mode & (SPI_TX_DUAL | SPI_TX_QUAD)))
				वापस -EINVAL;
			अगर ((xfer->tx_nbits == SPI_NBITS_QUAD) &&
				!(spi->mode & SPI_TX_QUAD))
				वापस -EINVAL;
		पूर्ण
		/* check transfer rx_nbits */
		अगर (xfer->rx_buf) अणु
			अगर (spi->mode & SPI_NO_RX)
				वापस -EINVAL;
			अगर (xfer->rx_nbits != SPI_NBITS_SINGLE &&
				xfer->rx_nbits != SPI_NBITS_DUAL &&
				xfer->rx_nbits != SPI_NBITS_QUAD)
				वापस -EINVAL;
			अगर ((xfer->rx_nbits == SPI_NBITS_DUAL) &&
				!(spi->mode & (SPI_RX_DUAL | SPI_RX_QUAD)))
				वापस -EINVAL;
			अगर ((xfer->rx_nbits == SPI_NBITS_QUAD) &&
				!(spi->mode & SPI_RX_QUAD))
				वापस -EINVAL;
		पूर्ण

		अगर (_spi_xfer_word_delay_update(xfer, spi))
			वापस -EINVAL;
	पूर्ण

	message->status = -EINPROGRESS;

	वापस 0;
पूर्ण

अटल पूर्णांक __spi_async(काष्ठा spi_device *spi, काष्ठा spi_message *message)
अणु
	काष्ठा spi_controller *ctlr = spi->controller;
	काष्ठा spi_transfer *xfer;

	/*
	 * Some controllers करो not support करोing regular SPI transfers. Return
	 * ENOTSUPP when this is the हाल.
	 */
	अगर (!ctlr->transfer)
		वापस -ENOTSUPP;

	message->spi = spi;

	SPI_STATISTICS_INCREMENT_FIELD(&ctlr->statistics, spi_async);
	SPI_STATISTICS_INCREMENT_FIELD(&spi->statistics, spi_async);

	trace_spi_message_submit(message);

	अगर (!ctlr->ptp_sts_supported) अणु
		list_क्रम_each_entry(xfer, &message->transfers, transfer_list) अणु
			xfer->ptp_sts_word_pre = 0;
			ptp_पढ़ो_प्रणाली_prets(xfer->ptp_sts);
		पूर्ण
	पूर्ण

	वापस ctlr->transfer(spi, message);
पूर्ण

/**
 * spi_async - asynchronous SPI transfer
 * @spi: device with which data will be exchanged
 * @message: describes the data transfers, including completion callback
 * Context: any (irqs may be blocked, etc)
 *
 * This call may be used in_irq and other contexts which can't sleep,
 * as well as from task contexts which can sleep.
 *
 * The completion callback is invoked in a context which can't sleep.
 * Beक्रमe that invocation, the value of message->status is undefined.
 * When the callback is issued, message->status holds either zero (to
 * indicate complete success) or a negative error code.  After that
 * callback वापसs, the driver which issued the transfer request may
 * deallocate the associated memory; it's no दीर्घer in use by any SPI
 * core or controller driver code.
 *
 * Note that although all messages to a spi_device are handled in
 * FIFO order, messages may go to dअगरferent devices in other orders.
 * Some device might be higher priority, or have various "hard" access
 * समय requirements, क्रम example.
 *
 * On detection of any fault during the transfer, processing of
 * the entire message is पातed, and the device is deselected.
 * Until वापसing from the associated message completion callback,
 * no other spi_message queued to that device will be processed.
 * (This rule applies equally to all the synchronous transfer calls,
 * which are wrappers around this core asynchronous primitive.)
 *
 * Return: zero on success, अन्यथा a negative error code.
 */
पूर्णांक spi_async(काष्ठा spi_device *spi, काष्ठा spi_message *message)
अणु
	काष्ठा spi_controller *ctlr = spi->controller;
	पूर्णांक ret;
	अचिन्हित दीर्घ flags;

	ret = __spi_validate(spi, message);
	अगर (ret != 0)
		वापस ret;

	spin_lock_irqsave(&ctlr->bus_lock_spinlock, flags);

	अगर (ctlr->bus_lock_flag)
		ret = -EBUSY;
	अन्यथा
		ret = __spi_async(spi, message);

	spin_unlock_irqrestore(&ctlr->bus_lock_spinlock, flags);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(spi_async);

/**
 * spi_async_locked - version of spi_async with exclusive bus usage
 * @spi: device with which data will be exchanged
 * @message: describes the data transfers, including completion callback
 * Context: any (irqs may be blocked, etc)
 *
 * This call may be used in_irq and other contexts which can't sleep,
 * as well as from task contexts which can sleep.
 *
 * The completion callback is invoked in a context which can't sleep.
 * Beक्रमe that invocation, the value of message->status is undefined.
 * When the callback is issued, message->status holds either zero (to
 * indicate complete success) or a negative error code.  After that
 * callback वापसs, the driver which issued the transfer request may
 * deallocate the associated memory; it's no दीर्घer in use by any SPI
 * core or controller driver code.
 *
 * Note that although all messages to a spi_device are handled in
 * FIFO order, messages may go to dअगरferent devices in other orders.
 * Some device might be higher priority, or have various "hard" access
 * समय requirements, क्रम example.
 *
 * On detection of any fault during the transfer, processing of
 * the entire message is पातed, and the device is deselected.
 * Until वापसing from the associated message completion callback,
 * no other spi_message queued to that device will be processed.
 * (This rule applies equally to all the synchronous transfer calls,
 * which are wrappers around this core asynchronous primitive.)
 *
 * Return: zero on success, अन्यथा a negative error code.
 */
पूर्णांक spi_async_locked(काष्ठा spi_device *spi, काष्ठा spi_message *message)
अणु
	काष्ठा spi_controller *ctlr = spi->controller;
	पूर्णांक ret;
	अचिन्हित दीर्घ flags;

	ret = __spi_validate(spi, message);
	अगर (ret != 0)
		वापस ret;

	spin_lock_irqsave(&ctlr->bus_lock_spinlock, flags);

	ret = __spi_async(spi, message);

	spin_unlock_irqrestore(&ctlr->bus_lock_spinlock, flags);

	वापस ret;

पूर्ण
EXPORT_SYMBOL_GPL(spi_async_locked);

/*-------------------------------------------------------------------------*/

/* Utility methods क्रम SPI protocol drivers, layered on
 * top of the core.  Some other utility methods are defined as
 * अंतरभूत functions.
 */

अटल व्योम spi_complete(व्योम *arg)
अणु
	complete(arg);
पूर्ण

अटल पूर्णांक __spi_sync(काष्ठा spi_device *spi, काष्ठा spi_message *message)
अणु
	DECLARE_COMPLETION_ONSTACK(करोne);
	पूर्णांक status;
	काष्ठा spi_controller *ctlr = spi->controller;
	अचिन्हित दीर्घ flags;

	status = __spi_validate(spi, message);
	अगर (status != 0)
		वापस status;

	message->complete = spi_complete;
	message->context = &करोne;
	message->spi = spi;

	SPI_STATISTICS_INCREMENT_FIELD(&ctlr->statistics, spi_sync);
	SPI_STATISTICS_INCREMENT_FIELD(&spi->statistics, spi_sync);

	/* If we're not using the legacy transfer method then we will
	 * try to transfer in the calling context so special हाल.
	 * This code would be less tricky अगर we could हटाओ the
	 * support क्रम driver implemented message queues.
	 */
	अगर (ctlr->transfer == spi_queued_transfer) अणु
		spin_lock_irqsave(&ctlr->bus_lock_spinlock, flags);

		trace_spi_message_submit(message);

		status = __spi_queued_transfer(spi, message, false);

		spin_unlock_irqrestore(&ctlr->bus_lock_spinlock, flags);
	पूर्ण अन्यथा अणु
		status = spi_async_locked(spi, message);
	पूर्ण

	अगर (status == 0) अणु
		/* Push out the messages in the calling context अगर we
		 * can.
		 */
		अगर (ctlr->transfer == spi_queued_transfer) अणु
			SPI_STATISTICS_INCREMENT_FIELD(&ctlr->statistics,
						       spi_sync_immediate);
			SPI_STATISTICS_INCREMENT_FIELD(&spi->statistics,
						       spi_sync_immediate);
			__spi_pump_messages(ctlr, false);
		पूर्ण

		रुको_क्रम_completion(&करोne);
		status = message->status;
	पूर्ण
	message->context = शून्य;
	वापस status;
पूर्ण

/**
 * spi_sync - blocking/synchronous SPI data transfers
 * @spi: device with which data will be exchanged
 * @message: describes the data transfers
 * Context: can sleep
 *
 * This call may only be used from a context that may sleep.  The sleep
 * is non-पूर्णांकerruptible, and has no समयout.  Low-overhead controller
 * drivers may DMA directly पूर्णांकo and out of the message buffers.
 *
 * Note that the SPI device's chip select is active during the message,
 * and then is normally disabled between messages.  Drivers क्रम some
 * frequently-used devices may want to minimize costs of selecting a chip,
 * by leaving it selected in anticipation that the next message will go
 * to the same chip.  (That may increase घातer usage.)
 *
 * Also, the caller is guaranteeing that the memory associated with the
 * message will not be मुक्तd beक्रमe this call वापसs.
 *
 * Return: zero on success, अन्यथा a negative error code.
 */
पूर्णांक spi_sync(काष्ठा spi_device *spi, काष्ठा spi_message *message)
अणु
	पूर्णांक ret;

	mutex_lock(&spi->controller->bus_lock_mutex);
	ret = __spi_sync(spi, message);
	mutex_unlock(&spi->controller->bus_lock_mutex);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(spi_sync);

/**
 * spi_sync_locked - version of spi_sync with exclusive bus usage
 * @spi: device with which data will be exchanged
 * @message: describes the data transfers
 * Context: can sleep
 *
 * This call may only be used from a context that may sleep.  The sleep
 * is non-पूर्णांकerruptible, and has no समयout.  Low-overhead controller
 * drivers may DMA directly पूर्णांकo and out of the message buffers.
 *
 * This call should be used by drivers that require exclusive access to the
 * SPI bus. It has to be preceded by a spi_bus_lock call. The SPI bus must
 * be released by a spi_bus_unlock call when the exclusive access is over.
 *
 * Return: zero on success, अन्यथा a negative error code.
 */
पूर्णांक spi_sync_locked(काष्ठा spi_device *spi, काष्ठा spi_message *message)
अणु
	वापस __spi_sync(spi, message);
पूर्ण
EXPORT_SYMBOL_GPL(spi_sync_locked);

/**
 * spi_bus_lock - obtain a lock क्रम exclusive SPI bus usage
 * @ctlr: SPI bus master that should be locked क्रम exclusive bus access
 * Context: can sleep
 *
 * This call may only be used from a context that may sleep.  The sleep
 * is non-पूर्णांकerruptible, and has no समयout.
 *
 * This call should be used by drivers that require exclusive access to the
 * SPI bus. The SPI bus must be released by a spi_bus_unlock call when the
 * exclusive access is over. Data transfer must be करोne by spi_sync_locked
 * and spi_async_locked calls when the SPI bus lock is held.
 *
 * Return: always zero.
 */
पूर्णांक spi_bus_lock(काष्ठा spi_controller *ctlr)
अणु
	अचिन्हित दीर्घ flags;

	mutex_lock(&ctlr->bus_lock_mutex);

	spin_lock_irqsave(&ctlr->bus_lock_spinlock, flags);
	ctlr->bus_lock_flag = 1;
	spin_unlock_irqrestore(&ctlr->bus_lock_spinlock, flags);

	/* mutex reमुख्यs locked until spi_bus_unlock is called */

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(spi_bus_lock);

/**
 * spi_bus_unlock - release the lock क्रम exclusive SPI bus usage
 * @ctlr: SPI bus master that was locked क्रम exclusive bus access
 * Context: can sleep
 *
 * This call may only be used from a context that may sleep.  The sleep
 * is non-पूर्णांकerruptible, and has no समयout.
 *
 * This call releases an SPI bus lock previously obtained by an spi_bus_lock
 * call.
 *
 * Return: always zero.
 */
पूर्णांक spi_bus_unlock(काष्ठा spi_controller *ctlr)
अणु
	ctlr->bus_lock_flag = 0;

	mutex_unlock(&ctlr->bus_lock_mutex);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(spi_bus_unlock);

/* portable code must never pass more than 32 bytes */
#घोषणा	SPI_बफ_मान	max(32, SMP_CACHE_BYTES)

अटल u8	*buf;

/**
 * spi_ग_लिखो_then_पढ़ो - SPI synchronous ग_लिखो followed by पढ़ो
 * @spi: device with which data will be exchanged
 * @txbuf: data to be written (need not be dma-safe)
 * @n_tx: size of txbuf, in bytes
 * @rxbuf: buffer पूर्णांकo which data will be पढ़ो (need not be dma-safe)
 * @n_rx: size of rxbuf, in bytes
 * Context: can sleep
 *
 * This perक्रमms a half duplex MicroWire style transaction with the
 * device, sending txbuf and then पढ़ोing rxbuf.  The वापस value
 * is zero क्रम success, अन्यथा a negative त्रुटि_सं status code.
 * This call may only be used from a context that may sleep.
 *
 * Parameters to this routine are always copied using a small buffer.
 * Perक्रमmance-sensitive or bulk transfer code should instead use
 * spi_अणुasync,syncपूर्ण() calls with dma-safe buffers.
 *
 * Return: zero on success, अन्यथा a negative error code.
 */
पूर्णांक spi_ग_लिखो_then_पढ़ो(काष्ठा spi_device *spi,
		स्थिर व्योम *txbuf, अचिन्हित n_tx,
		व्योम *rxbuf, अचिन्हित n_rx)
अणु
	अटल DEFINE_MUTEX(lock);

	पूर्णांक			status;
	काष्ठा spi_message	message;
	काष्ठा spi_transfer	x[2];
	u8			*local_buf;

	/* Use pपुनः_स्मृतिated DMA-safe buffer अगर we can.  We can't aव्योम
	 * copying here, (as a pure convenience thing), but we can
	 * keep heap costs out of the hot path unless someone अन्यथा is
	 * using the pre-allocated buffer or the transfer is too large.
	 */
	अगर ((n_tx + n_rx) > SPI_बफ_मान || !mutex_trylock(&lock)) अणु
		local_buf = kदो_स्मृति(max((अचिन्हित)SPI_बफ_मान, n_tx + n_rx),
				    GFP_KERNEL | GFP_DMA);
		अगर (!local_buf)
			वापस -ENOMEM;
	पूर्ण अन्यथा अणु
		local_buf = buf;
	पूर्ण

	spi_message_init(&message);
	स_रखो(x, 0, माप(x));
	अगर (n_tx) अणु
		x[0].len = n_tx;
		spi_message_add_tail(&x[0], &message);
	पूर्ण
	अगर (n_rx) अणु
		x[1].len = n_rx;
		spi_message_add_tail(&x[1], &message);
	पूर्ण

	स_नकल(local_buf, txbuf, n_tx);
	x[0].tx_buf = local_buf;
	x[1].rx_buf = local_buf + n_tx;

	/* करो the i/o */
	status = spi_sync(spi, &message);
	अगर (status == 0)
		स_नकल(rxbuf, x[1].rx_buf, n_rx);

	अगर (x[0].tx_buf == buf)
		mutex_unlock(&lock);
	अन्यथा
		kमुक्त(local_buf);

	वापस status;
पूर्ण
EXPORT_SYMBOL_GPL(spi_ग_लिखो_then_पढ़ो);

/*-------------------------------------------------------------------------*/

#अगर IS_ENABLED(CONFIG_OF)
/* must call put_device() when करोne with वापसed spi_device device */
काष्ठा spi_device *of_find_spi_device_by_node(काष्ठा device_node *node)
अणु
	काष्ठा device *dev = bus_find_device_by_of_node(&spi_bus_type, node);

	वापस dev ? to_spi_device(dev) : शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(of_find_spi_device_by_node);
#पूर्ण_अगर /* IS_ENABLED(CONFIG_OF) */

#अगर IS_ENABLED(CONFIG_OF_DYNAMIC)
/* the spi controllers are not using spi_bus, so we find it with another way */
अटल काष्ठा spi_controller *of_find_spi_controller_by_node(काष्ठा device_node *node)
अणु
	काष्ठा device *dev;

	dev = class_find_device_by_of_node(&spi_master_class, node);
	अगर (!dev && IS_ENABLED(CONFIG_SPI_SLAVE))
		dev = class_find_device_by_of_node(&spi_slave_class, node);
	अगर (!dev)
		वापस शून्य;

	/* reference got in class_find_device */
	वापस container_of(dev, काष्ठा spi_controller, dev);
पूर्ण

अटल पूर्णांक of_spi_notअगरy(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ action,
			 व्योम *arg)
अणु
	काष्ठा of_reconfig_data *rd = arg;
	काष्ठा spi_controller *ctlr;
	काष्ठा spi_device *spi;

	चयन (of_reconfig_get_state_change(action, arg)) अणु
	हाल OF_RECONFIG_CHANGE_ADD:
		ctlr = of_find_spi_controller_by_node(rd->dn->parent);
		अगर (ctlr == शून्य)
			वापस NOTIFY_OK;	/* not क्रम us */

		अगर (of_node_test_and_set_flag(rd->dn, OF_POPULATED)) अणु
			put_device(&ctlr->dev);
			वापस NOTIFY_OK;
		पूर्ण

		spi = of_रेजिस्टर_spi_device(ctlr, rd->dn);
		put_device(&ctlr->dev);

		अगर (IS_ERR(spi)) अणु
			pr_err("%s: failed to create for '%pOF'\n",
					__func__, rd->dn);
			of_node_clear_flag(rd->dn, OF_POPULATED);
			वापस notअगरier_from_त्रुटि_सं(PTR_ERR(spi));
		पूर्ण
		अवरोध;

	हाल OF_RECONFIG_CHANGE_REMOVE:
		/* alपढ़ोy depopulated? */
		अगर (!of_node_check_flag(rd->dn, OF_POPULATED))
			वापस NOTIFY_OK;

		/* find our device by node */
		spi = of_find_spi_device_by_node(rd->dn);
		अगर (spi == शून्य)
			वापस NOTIFY_OK;	/* no? not meant क्रम us */

		/* unरेजिस्टर takes one ref away */
		spi_unरेजिस्टर_device(spi);

		/* and put the reference of the find */
		put_device(&spi->dev);
		अवरोध;
	पूर्ण

	वापस NOTIFY_OK;
पूर्ण

अटल काष्ठा notअगरier_block spi_of_notअगरier = अणु
	.notअगरier_call = of_spi_notअगरy,
पूर्ण;
#अन्यथा /* IS_ENABLED(CONFIG_OF_DYNAMIC) */
बाह्य काष्ठा notअगरier_block spi_of_notअगरier;
#पूर्ण_अगर /* IS_ENABLED(CONFIG_OF_DYNAMIC) */

#अगर IS_ENABLED(CONFIG_ACPI)
अटल पूर्णांक spi_acpi_controller_match(काष्ठा device *dev, स्थिर व्योम *data)
अणु
	वापस ACPI_COMPANION(dev->parent) == data;
पूर्ण

अटल काष्ठा spi_controller *acpi_spi_find_controller_by_adev(काष्ठा acpi_device *adev)
अणु
	काष्ठा device *dev;

	dev = class_find_device(&spi_master_class, शून्य, adev,
				spi_acpi_controller_match);
	अगर (!dev && IS_ENABLED(CONFIG_SPI_SLAVE))
		dev = class_find_device(&spi_slave_class, शून्य, adev,
					spi_acpi_controller_match);
	अगर (!dev)
		वापस शून्य;

	वापस container_of(dev, काष्ठा spi_controller, dev);
पूर्ण

अटल काष्ठा spi_device *acpi_spi_find_device_by_adev(काष्ठा acpi_device *adev)
अणु
	काष्ठा device *dev;

	dev = bus_find_device_by_acpi_dev(&spi_bus_type, adev);
	वापस to_spi_device(dev);
पूर्ण

अटल पूर्णांक acpi_spi_notअगरy(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ value,
			   व्योम *arg)
अणु
	काष्ठा acpi_device *adev = arg;
	काष्ठा spi_controller *ctlr;
	काष्ठा spi_device *spi;

	चयन (value) अणु
	हाल ACPI_RECONFIG_DEVICE_ADD:
		ctlr = acpi_spi_find_controller_by_adev(adev->parent);
		अगर (!ctlr)
			अवरोध;

		acpi_रेजिस्टर_spi_device(ctlr, adev);
		put_device(&ctlr->dev);
		अवरोध;
	हाल ACPI_RECONFIG_DEVICE_REMOVE:
		अगर (!acpi_device_क्रमागतerated(adev))
			अवरोध;

		spi = acpi_spi_find_device_by_adev(adev);
		अगर (!spi)
			अवरोध;

		spi_unरेजिस्टर_device(spi);
		put_device(&spi->dev);
		अवरोध;
	पूर्ण

	वापस NOTIFY_OK;
पूर्ण

अटल काष्ठा notअगरier_block spi_acpi_notअगरier = अणु
	.notअगरier_call = acpi_spi_notअगरy,
पूर्ण;
#अन्यथा
बाह्य काष्ठा notअगरier_block spi_acpi_notअगरier;
#पूर्ण_अगर

अटल पूर्णांक __init spi_init(व्योम)
अणु
	पूर्णांक	status;

	buf = kदो_स्मृति(SPI_बफ_मान, GFP_KERNEL);
	अगर (!buf) अणु
		status = -ENOMEM;
		जाओ err0;
	पूर्ण

	status = bus_रेजिस्टर(&spi_bus_type);
	अगर (status < 0)
		जाओ err1;

	status = class_रेजिस्टर(&spi_master_class);
	अगर (status < 0)
		जाओ err2;

	अगर (IS_ENABLED(CONFIG_SPI_SLAVE)) अणु
		status = class_रेजिस्टर(&spi_slave_class);
		अगर (status < 0)
			जाओ err3;
	पूर्ण

	अगर (IS_ENABLED(CONFIG_OF_DYNAMIC))
		WARN_ON(of_reconfig_notअगरier_रेजिस्टर(&spi_of_notअगरier));
	अगर (IS_ENABLED(CONFIG_ACPI))
		WARN_ON(acpi_reconfig_notअगरier_रेजिस्टर(&spi_acpi_notअगरier));

	वापस 0;

err3:
	class_unरेजिस्टर(&spi_master_class);
err2:
	bus_unरेजिस्टर(&spi_bus_type);
err1:
	kमुक्त(buf);
	buf = शून्य;
err0:
	वापस status;
पूर्ण

/* board_info is normally रेजिस्टरed in arch_initcall(),
 * but even essential drivers रुको till later
 *
 * REVISIT only boardinfo really needs अटल linking. the rest (device and
 * driver registration) _could_ be dynamically linked (modular) ... costs
 * include needing to have boardinfo data काष्ठाures be much more खुला.
 */
postcore_initcall(spi_init);
