<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2011 Jonathan Cameron
 *
 * Buffer handling elements of industrial I/O reference driver.
 * Uses the kfअगरo buffer.
 *
 * To test without hardware use the sysfs trigger.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/export.h>
#समावेश <linux/slab.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/biपंचांगap.h>

#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/buffer.h>
#समावेश <linux/iio/trigger_consumer.h>
#समावेश <linux/iio/triggered_buffer.h>

#समावेश "iio_simple_dummy.h"

/* Some fake data */

अटल स्थिर s16 fakedata[] = अणु
	[DUMMY_INDEX_VOLTAGE_0] = 7,
	[DUMMY_INDEX_DIFFVOLTAGE_1M2] = -33,
	[DUMMY_INDEX_DIFFVOLTAGE_3M4] = -2,
	[DUMMY_INDEX_ACCELX] = 344,
पूर्ण;

/**
 * iio_simple_dummy_trigger_h() - the trigger handler function
 * @irq: the पूर्णांकerrupt number
 * @p: निजी data - always a poपूर्णांकer to the poll func.
 *
 * This is the guts of buffered capture. On a trigger event occurring,
 * अगर the pollfunc is attached then this handler is called as a thपढ़ोed
 * पूर्णांकerrupt (and hence may sleep). It is responsible क्रम grabbing data
 * from the device and pushing it पूर्णांकo the associated buffer.
 */
अटल irqवापस_t iio_simple_dummy_trigger_h(पूर्णांक irq, व्योम *p)
अणु
	काष्ठा iio_poll_func *pf = p;
	काष्ठा iio_dev *indio_dev = pf->indio_dev;
	पूर्णांक len = 0;
	u16 *data;

	data = kदो_स्मृति(indio_dev->scan_bytes, GFP_KERNEL);
	अगर (!data)
		जाओ करोne;

	अगर (!biपंचांगap_empty(indio_dev->active_scan_mask, indio_dev->masklength)) अणु
		/*
		 * Three common options here:
		 * hardware scans: certain combinations of channels make
		 *   up a fast पढ़ो.  The capture will consist of all of them.
		 *   Hence we just call the grab data function and fill the
		 *   buffer without processing.
		 * software scans: can be considered to be अक्रमom access
		 *   so efficient पढ़ोing is just a हाल of minimal bus
		 *   transactions.
		 * software culled hardware scans:
		 *   occasionally a driver may process the nearest hardware
		 *   scan to aव्योम storing elements that are not desired. This
		 *   is the fiddliest option by far.
		 * Here let's pretend we have अक्रमom access. And the values are
		 * in the स्थिरant table fakedata.
		 */
		पूर्णांक i, j;

		क्रम (i = 0, j = 0;
		     i < biपंचांगap_weight(indio_dev->active_scan_mask,
				       indio_dev->masklength);
		     i++, j++) अणु
			j = find_next_bit(indio_dev->active_scan_mask,
					  indio_dev->masklength, j);
			/* अक्रमom access पढ़ो from the 'device' */
			data[i] = fakedata[j];
			len += 2;
		पूर्ण
	पूर्ण

	iio_push_to_buffers_with_बारtamp(indio_dev, data,
					   iio_get_समय_ns(indio_dev));

	kमुक्त(data);

करोne:
	/*
	 * Tell the core we are करोne with this trigger and पढ़ोy क्रम the
	 * next one.
	 */
	iio_trigger_notअगरy_करोne(indio_dev->trig);

	वापस IRQ_HANDLED;
पूर्ण

अटल स्थिर काष्ठा iio_buffer_setup_ops iio_simple_dummy_buffer_setup_ops = अणु
पूर्ण;

पूर्णांक iio_simple_dummy_configure_buffer(काष्ठा iio_dev *indio_dev)
अणु
	वापस iio_triggered_buffer_setup(indio_dev, शून्य,
					  iio_simple_dummy_trigger_h,
					  &iio_simple_dummy_buffer_setup_ops);
पूर्ण

/**
 * iio_simple_dummy_unconfigure_buffer() - release buffer resources
 * @indio_dev: device instance state
 */
व्योम iio_simple_dummy_unconfigure_buffer(काष्ठा iio_dev *indio_dev)
अणु
	iio_triggered_buffer_cleanup(indio_dev);
पूर्ण
