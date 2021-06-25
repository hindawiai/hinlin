<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * ACPI Ambient Light Sensor Driver
 *
 * Based on ALS driver:
 * Copyright (C) 2009 Zhang Rui <rui.zhang@पूर्णांकel.com>
 *
 * Rework क्रम IIO subप्रणाली:
 * Copyright (C) 2012-2013 Martin Liska <marxin.liska@gmail.com>
 *
 * Final cleanup and debugging:
 * Copyright (C) 2013-2014 Marek Vasut <marex@denx.de>
 * Copyright (C) 2015 Gabriele Mazzotta <gabriele.mzt@gmail.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/acpi.h>
#समावेश <linux/err.h>
#समावेश <linux/irq.h>
#समावेश <linux/mutex.h>

#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/buffer.h>
#समावेश <linux/iio/trigger.h>
#समावेश <linux/iio/triggered_buffer.h>
#समावेश <linux/iio/trigger_consumer.h>

#घोषणा ACPI_ALS_CLASS			"als"
#घोषणा ACPI_ALS_DEVICE_NAME		"acpi-als"
#घोषणा ACPI_ALS_NOTIFY_ILLUMIन_अंकCE	0x80

/*
 * So far, there's only one channel in here, but the specअगरication क्रम
 * ACPI0008 says there can be more to what the block can report. Like
 * chromaticity and such. We are पढ़ोy क्रम incoming additions!
 */
अटल स्थिर काष्ठा iio_chan_spec acpi_als_channels[] = अणु
	अणु
		.type		= IIO_LIGHT,
		.scan_type	= अणु
			.sign		= 's',
			.realbits	= 32,
			.storagebits	= 32,
		पूर्ण,
		/* _RAW is here क्रम backward ABI compatibility */
		.info_mask_separate	= BIT(IIO_CHAN_INFO_RAW) |
					  BIT(IIO_CHAN_INFO_PROCESSED),
	पूर्ण,
	IIO_CHAN_SOFT_TIMESTAMP(1),
पूर्ण;

/*
 * The event buffer contains बारtamp and all the data from
 * the ACPI0008 block. There are multiple, but so far we only
 * support _ALI (illuminance): One channel, padding and बारtamp.
 */
#घोषणा ACPI_ALS_EVT_BUFFER_SIZE		\
	(माप(s32) + माप(s32) + माप(s64))

काष्ठा acpi_als अणु
	काष्ठा acpi_device	*device;
	काष्ठा mutex		lock;
	काष्ठा iio_trigger	*trig;

	s32 evt_buffer[ACPI_ALS_EVT_BUFFER_SIZE / माप(s32)]  __aligned(8);
पूर्ण;

/*
 * All types of properties the ACPI0008 block can report. The ALI, ALC, ALT
 * and ALP can all be handled by acpi_als_पढ़ो_value() below, जबतक the ALR is
 * special.
 *
 * The _ALR property वापसs tables that can be used to fine-tune the values
 * reported by the other props based on the particular hardware type and it's
 * location (it contains tables क्रम "rainy", "bright inhouse lighting" etc.).
 *
 * So far, we support only ALI (illuminance).
 */
#घोषणा ACPI_ALS_ILLUMIन_अंकCE	"_ALI"
#घोषणा ACPI_ALS_CHROMATICITY	"_ALC"
#घोषणा ACPI_ALS_COLOR_TEMP	"_ALT"
#घोषणा ACPI_ALS_POLLING	"_ALP"
#घोषणा ACPI_ALS_TABLES		"_ALR"

अटल पूर्णांक acpi_als_पढ़ो_value(काष्ठा acpi_als *als, अक्षर *prop, s32 *val)
अणु
	अचिन्हित दीर्घ दीर्घ temp_val;
	acpi_status status;

	status = acpi_evaluate_पूर्णांकeger(als->device->handle, prop, शून्य,
				       &temp_val);

	अगर (ACPI_FAILURE(status)) अणु
		acpi_evaluation_failure_warn(als->device->handle, prop, status);
		वापस -EIO;
	पूर्ण

	*val = temp_val;

	वापस 0;
पूर्ण

अटल व्योम acpi_als_notअगरy(काष्ठा acpi_device *device, u32 event)
अणु
	काष्ठा iio_dev *indio_dev = acpi_driver_data(device);
	काष्ठा acpi_als *als = iio_priv(indio_dev);

	अगर (iio_buffer_enabled(indio_dev) && iio_trigger_using_own(indio_dev)) अणु
		चयन (event) अणु
		हाल ACPI_ALS_NOTIFY_ILLUMIन_अंकCE:
			iio_trigger_poll_chained(als->trig);
			अवरोध;
		शेष:
			/* Unhandled event */
			dev_dbg(&device->dev,
				"Unhandled ACPI ALS event (%08x)!\n",
				event);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक acpi_als_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			     काष्ठा iio_chan_spec स्थिर *chan, पूर्णांक *val,
			     पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा acpi_als *als = iio_priv(indio_dev);
	s32 temp_val;
	पूर्णांक ret;

	अगर ((mask != IIO_CHAN_INFO_PROCESSED) && (mask != IIO_CHAN_INFO_RAW))
		वापस -EINVAL;

	/* we support only illumination (_ALI) so far. */
	अगर (chan->type != IIO_LIGHT)
		वापस -EINVAL;

	ret = acpi_als_पढ़ो_value(als, ACPI_ALS_ILLUMIन_अंकCE, &temp_val);
	अगर (ret < 0)
		वापस ret;

	*val = temp_val;

	वापस IIO_VAL_INT;
पूर्ण

अटल स्थिर काष्ठा iio_info acpi_als_info = अणु
	.पढ़ो_raw		= acpi_als_पढ़ो_raw,
पूर्ण;

अटल irqवापस_t acpi_als_trigger_handler(पूर्णांक irq, व्योम *p)
अणु
	काष्ठा iio_poll_func *pf = p;
	काष्ठा iio_dev *indio_dev = pf->indio_dev;
	काष्ठा acpi_als *als = iio_priv(indio_dev);
	s32 *buffer = als->evt_buffer;
	s32 val;
	पूर्णांक ret;

	mutex_lock(&als->lock);

	ret = acpi_als_पढ़ो_value(als, ACPI_ALS_ILLUMIन_अंकCE, &val);
	अगर (ret < 0)
		जाओ out;
	*buffer = val;

	/*
	 * When coming from own trigger via polls, set polling function
	 * बारtamp here. Given ACPI notअगरier is alपढ़ोy in a thपढ़ो and call
	 * function directly, there is no need to set the बारtamp in the
	 * notअगरy function.
	 *
	 * If the बारtamp was actually 0, the बारtamp is set one more समय.
	 */
	अगर (!pf->बारtamp)
		pf->बारtamp = iio_get_समय_ns(indio_dev);

	iio_push_to_buffers_with_बारtamp(indio_dev, buffer, pf->बारtamp);
out:
	mutex_unlock(&als->lock);
	iio_trigger_notअगरy_करोne(indio_dev->trig);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक acpi_als_add(काष्ठा acpi_device *device)
अणु
	काष्ठा device *dev = &device->dev;
	काष्ठा iio_dev *indio_dev;
	काष्ठा acpi_als *als;
	पूर्णांक ret;

	indio_dev = devm_iio_device_alloc(dev, माप(*als));
	अगर (!indio_dev)
		वापस -ENOMEM;

	als = iio_priv(indio_dev);

	device->driver_data = indio_dev;
	als->device = device;
	mutex_init(&als->lock);

	indio_dev->name = ACPI_ALS_DEVICE_NAME;
	indio_dev->info = &acpi_als_info;
	indio_dev->channels = acpi_als_channels;
	indio_dev->num_channels = ARRAY_SIZE(acpi_als_channels);

	als->trig = devm_iio_trigger_alloc(dev, "%s-dev%d", indio_dev->name, indio_dev->id);
	अगर (!als->trig)
		वापस -ENOMEM;

	ret = devm_iio_trigger_रेजिस्टर(dev, als->trig);
	अगर (ret)
		वापस ret;
	/*
	 * Set hardware trigger by शेष to let events flow when
	 * BIOS support notअगरication.
	 */
	indio_dev->trig = iio_trigger_get(als->trig);

	ret = devm_iio_triggered_buffer_setup(dev, indio_dev,
					      iio_pollfunc_store_समय,
					      acpi_als_trigger_handler,
					      शून्य);
	अगर (ret)
		वापस ret;

	वापस devm_iio_device_रेजिस्टर(dev, indio_dev);
पूर्ण

अटल स्थिर काष्ठा acpi_device_id acpi_als_device_ids[] = अणु
	अणु"ACPI0008", 0पूर्ण,
	अणुपूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(acpi, acpi_als_device_ids);

अटल काष्ठा acpi_driver acpi_als_driver = अणु
	.name	= "acpi_als",
	.class	= ACPI_ALS_CLASS,
	.ids	= acpi_als_device_ids,
	.ops = अणु
		.add	= acpi_als_add,
		.notअगरy	= acpi_als_notअगरy,
	पूर्ण,
पूर्ण;

module_acpi_driver(acpi_als_driver);

MODULE_AUTHOR("Zhang Rui <rui.zhang@intel.com>");
MODULE_AUTHOR("Martin Liska <marxin.liska@gmail.com>");
MODULE_AUTHOR("Marek Vasut <marex@denx.de>");
MODULE_DESCRIPTION("ACPI Ambient Light Sensor Driver");
MODULE_LICENSE("GPL");
