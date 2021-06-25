<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * HID Sensors Driver
 * Copyright (c) 2012, Intel Corporation.
 */
#समावेश <linux/device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/slab.h>
#समावेश <linux/delay.h>
#समावेश <linux/hid-sensor-hub.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/trigger.h>
#समावेश <linux/iio/triggered_buffer.h>
#समावेश <linux/iio/trigger_consumer.h>
#समावेश <linux/iio/buffer.h>
#समावेश <linux/iio/sysfs.h>
#समावेश "hid-sensor-trigger.h"

अटल sमाप_प्रकार _hid_sensor_set_report_latency(काष्ठा device *dev,
					      काष्ठा device_attribute *attr,
					      स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा iio_dev *indio_dev = dev_to_iio_dev(dev);
	काष्ठा hid_sensor_common *attrb = iio_device_get_drvdata(indio_dev);
	पूर्णांक पूर्णांकeger, fract, ret;
	पूर्णांक latency;

	ret = iio_str_to_fixpoपूर्णांक(buf, 100000, &पूर्णांकeger, &fract);
	अगर (ret)
		वापस ret;

	latency = पूर्णांकeger * 1000 + fract / 1000;
	ret = hid_sensor_set_report_latency(attrb, latency);
	अगर (ret < 0)
		वापस len;

	attrb->latency_ms = hid_sensor_get_report_latency(attrb);

	वापस len;
पूर्ण

अटल sमाप_प्रकार _hid_sensor_get_report_latency(काष्ठा device *dev,
					      काष्ठा device_attribute *attr,
					      अक्षर *buf)
अणु
	काष्ठा iio_dev *indio_dev = dev_to_iio_dev(dev);
	काष्ठा hid_sensor_common *attrb = iio_device_get_drvdata(indio_dev);
	पूर्णांक latency;

	latency = hid_sensor_get_report_latency(attrb);
	अगर (latency < 0)
		वापस latency;

	वापस प्र_लिखो(buf, "%d.%06u\n", latency / 1000, (latency % 1000) * 1000);
पूर्ण

अटल sमाप_प्रकार _hid_sensor_get_fअगरo_state(काष्ठा device *dev,
					  काष्ठा device_attribute *attr,
					  अक्षर *buf)
अणु
	काष्ठा iio_dev *indio_dev = dev_to_iio_dev(dev);
	काष्ठा hid_sensor_common *attrb = iio_device_get_drvdata(indio_dev);
	पूर्णांक latency;

	latency = hid_sensor_get_report_latency(attrb);
	अगर (latency < 0)
		वापस latency;

	वापस प्र_लिखो(buf, "%d\n", !!latency);
पूर्ण

अटल IIO_DEVICE_ATTR(hwfअगरo_समयout, 0644,
		       _hid_sensor_get_report_latency,
		       _hid_sensor_set_report_latency, 0);
अटल IIO_DEVICE_ATTR(hwfअगरo_enabled, 0444,
		       _hid_sensor_get_fअगरo_state, शून्य, 0);

अटल स्थिर काष्ठा attribute *hid_sensor_fअगरo_attributes[] = अणु
	&iio_dev_attr_hwfअगरo_समयout.dev_attr.attr,
	&iio_dev_attr_hwfअगरo_enabled.dev_attr.attr,
	शून्य,
पूर्ण;

अटल पूर्णांक _hid_sensor_घातer_state(काष्ठा hid_sensor_common *st, bool state)
अणु
	पूर्णांक state_val;
	पूर्णांक report_val;
	s32 poll_value = 0;

	अगर (state) अणु
		अगर (sensor_hub_device_खोलो(st->hsdev))
			वापस -EIO;

		atomic_inc(&st->data_पढ़ोy);

		state_val = hid_sensor_get_usage_index(st->hsdev,
			st->घातer_state.report_id,
			st->घातer_state.index,
			HID_USAGE_SENSOR_PROP_POWER_STATE_D0_FULL_POWER_ENUM);
		report_val = hid_sensor_get_usage_index(st->hsdev,
			st->report_state.report_id,
			st->report_state.index,
			HID_USAGE_SENSOR_PROP_REPORTING_STATE_ALL_EVENTS_ENUM);

		poll_value = hid_sensor_पढ़ो_poll_value(st);
	पूर्ण अन्यथा अणु
		पूर्णांक val;

		val = atomic_dec_अगर_positive(&st->data_पढ़ोy);
		अगर (val < 0)
			वापस 0;

		sensor_hub_device_बंद(st->hsdev);
		state_val = hid_sensor_get_usage_index(st->hsdev,
			st->घातer_state.report_id,
			st->घातer_state.index,
			HID_USAGE_SENSOR_PROP_POWER_STATE_D4_POWER_OFF_ENUM);
		report_val = hid_sensor_get_usage_index(st->hsdev,
			st->report_state.report_id,
			st->report_state.index,
			HID_USAGE_SENSOR_PROP_REPORTING_STATE_NO_EVENTS_ENUM);
	पूर्ण

	अगर (state_val >= 0) अणु
		state_val += st->घातer_state.logical_minimum;
		sensor_hub_set_feature(st->hsdev, st->घातer_state.report_id,
				       st->घातer_state.index, माप(state_val),
				       &state_val);
	पूर्ण

	अगर (report_val >= 0) अणु
		report_val += st->report_state.logical_minimum;
		sensor_hub_set_feature(st->hsdev, st->report_state.report_id,
				       st->report_state.index,
				       माप(report_val),
				       &report_val);
	पूर्ण

	pr_debug("HID_SENSOR %s set power_state %d report_state %d\n",
		 st->pdev->name, state_val, report_val);

	sensor_hub_get_feature(st->hsdev, st->घातer_state.report_id,
			       st->घातer_state.index,
			       माप(state_val), &state_val);
	अगर (state && poll_value)
		msleep_पूर्णांकerruptible(poll_value * 2);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(hid_sensor_घातer_state);

पूर्णांक hid_sensor_घातer_state(काष्ठा hid_sensor_common *st, bool state)
अणु

#अगर_घोषित CONFIG_PM
	पूर्णांक ret;

	अगर (atomic_add_unless(&st->runसमय_pm_enable, 1, 1))
		pm_runसमय_enable(&st->pdev->dev);

	अगर (state) अणु
		atomic_inc(&st->user_requested_state);
		ret = pm_runसमय_get_sync(&st->pdev->dev);
	पूर्ण अन्यथा अणु
		atomic_dec(&st->user_requested_state);
		pm_runसमय_mark_last_busy(&st->pdev->dev);
		pm_runसमय_use_स्वतःsuspend(&st->pdev->dev);
		ret = pm_runसमय_put_स्वतःsuspend(&st->pdev->dev);
	पूर्ण
	अगर (ret < 0) अणु
		अगर (state)
			pm_runसमय_put_noidle(&st->pdev->dev);
		वापस ret;
	पूर्ण

	वापस 0;
#अन्यथा
	atomic_set(&st->user_requested_state, state);
	वापस _hid_sensor_घातer_state(st, state);
#पूर्ण_अगर
पूर्ण

अटल व्योम hid_sensor_set_घातer_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा hid_sensor_common *attrb = container_of(work,
						       काष्ठा hid_sensor_common,
						       work);

	अगर (attrb->poll_पूर्णांकerval >= 0)
		sensor_hub_set_feature(attrb->hsdev, attrb->poll.report_id,
				       attrb->poll.index,
				       माप(attrb->poll_पूर्णांकerval),
				       &attrb->poll_पूर्णांकerval);

	अगर (attrb->raw_hystersis >= 0)
		sensor_hub_set_feature(attrb->hsdev,
				       attrb->sensitivity.report_id,
				       attrb->sensitivity.index,
				       माप(attrb->raw_hystersis),
				       &attrb->raw_hystersis);

	अगर (attrb->latency_ms > 0)
		hid_sensor_set_report_latency(attrb, attrb->latency_ms);

	अगर (atomic_पढ़ो(&attrb->user_requested_state))
		_hid_sensor_घातer_state(attrb, true);
पूर्ण

अटल पूर्णांक hid_sensor_data_rdy_trigger_set_state(काष्ठा iio_trigger *trig,
						bool state)
अणु
	वापस hid_sensor_घातer_state(iio_trigger_get_drvdata(trig), state);
पूर्ण

व्योम hid_sensor_हटाओ_trigger(काष्ठा iio_dev *indio_dev,
			       काष्ठा hid_sensor_common *attrb)
अणु
	अगर (atomic_पढ़ो(&attrb->runसमय_pm_enable))
		pm_runसमय_disable(&attrb->pdev->dev);

	pm_runसमय_set_suspended(&attrb->pdev->dev);
	pm_runसमय_put_noidle(&attrb->pdev->dev);

	cancel_work_sync(&attrb->work);
	iio_trigger_unरेजिस्टर(attrb->trigger);
	iio_trigger_मुक्त(attrb->trigger);
	iio_triggered_buffer_cleanup(indio_dev);
पूर्ण
EXPORT_SYMBOL(hid_sensor_हटाओ_trigger);

अटल स्थिर काष्ठा iio_trigger_ops hid_sensor_trigger_ops = अणु
	.set_trigger_state = &hid_sensor_data_rdy_trigger_set_state,
पूर्ण;

पूर्णांक hid_sensor_setup_trigger(काष्ठा iio_dev *indio_dev, स्थिर अक्षर *name,
				काष्ठा hid_sensor_common *attrb)
अणु
	स्थिर काष्ठा attribute **fअगरo_attrs;
	पूर्णांक ret;
	काष्ठा iio_trigger *trig;

	अगर (hid_sensor_batch_mode_supported(attrb))
		fअगरo_attrs = hid_sensor_fअगरo_attributes;
	अन्यथा
		fअगरo_attrs = शून्य;

	ret = iio_triggered_buffer_setup_ext(indio_dev,
					     &iio_pollfunc_store_समय,
					     शून्य, शून्य, fअगरo_attrs);
	अगर (ret) अणु
		dev_err(&indio_dev->dev, "Triggered Buffer Setup Failed\n");
		वापस ret;
	पूर्ण

	trig = iio_trigger_alloc(indio_dev->dev.parent,
				 "%s-dev%d", name, indio_dev->id);
	अगर (trig == शून्य) अणु
		dev_err(&indio_dev->dev, "Trigger Allocate Failed\n");
		ret = -ENOMEM;
		जाओ error_triggered_buffer_cleanup;
	पूर्ण

	iio_trigger_set_drvdata(trig, attrb);
	trig->ops = &hid_sensor_trigger_ops;
	ret = iio_trigger_रेजिस्टर(trig);

	अगर (ret) अणु
		dev_err(&indio_dev->dev, "Trigger Register Failed\n");
		जाओ error_मुक्त_trig;
	पूर्ण
	attrb->trigger = trig;
	indio_dev->trig = iio_trigger_get(trig);

	ret = pm_runसमय_set_active(&indio_dev->dev);
	अगर (ret)
		जाओ error_unreg_trigger;

	iio_device_set_drvdata(indio_dev, attrb);

	INIT_WORK(&attrb->work, hid_sensor_set_घातer_work);

	pm_suspend_ignore_children(&attrb->pdev->dev, true);
	/* Default to 3 seconds, but can be changed from sysfs */
	pm_runसमय_set_स्वतःsuspend_delay(&attrb->pdev->dev,
					 3000);
	वापस ret;
error_unreg_trigger:
	iio_trigger_unरेजिस्टर(trig);
error_मुक्त_trig:
	iio_trigger_मुक्त(trig);
error_triggered_buffer_cleanup:
	iio_triggered_buffer_cleanup(indio_dev);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(hid_sensor_setup_trigger);

अटल पूर्णांक __maybe_unused hid_sensor_suspend(काष्ठा device *dev)
अणु
	काष्ठा iio_dev *indio_dev = dev_get_drvdata(dev);
	काष्ठा hid_sensor_common *attrb = iio_device_get_drvdata(indio_dev);

	वापस _hid_sensor_घातer_state(attrb, false);
पूर्ण

अटल पूर्णांक __maybe_unused hid_sensor_resume(काष्ठा device *dev)
अणु
	काष्ठा iio_dev *indio_dev = dev_get_drvdata(dev);
	काष्ठा hid_sensor_common *attrb = iio_device_get_drvdata(indio_dev);
	schedule_work(&attrb->work);
	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused hid_sensor_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा iio_dev *indio_dev = dev_get_drvdata(dev);
	काष्ठा hid_sensor_common *attrb = iio_device_get_drvdata(indio_dev);
	वापस _hid_sensor_घातer_state(attrb, true);
पूर्ण

स्थिर काष्ठा dev_pm_ops hid_sensor_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(hid_sensor_suspend, hid_sensor_resume)
	SET_RUNTIME_PM_OPS(hid_sensor_suspend,
			   hid_sensor_runसमय_resume, शून्य)
पूर्ण;
EXPORT_SYMBOL(hid_sensor_pm_ops);

MODULE_AUTHOR("Srinivas Pandruvada <srinivas.pandruvada@intel.com>");
MODULE_DESCRIPTION("HID Sensor trigger processing");
MODULE_LICENSE("GPL");
